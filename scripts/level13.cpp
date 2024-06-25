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
// Filename:	level13.cpp
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

#define ID_CUSTOM_OBJECT_1074 0x001
#define ID_CUSTOM_OBJECT_0878 0x002
#define ID_CUSTOM_OBJECT_0877 0x003
#define ID_CUSTOM_OBJECT_0879 0x004
#define ID_CUSTOM_OBJECT_6813 0x005
#define ID_CUSTOM_OBJECT_083A 0x006
#define ID_CUSTOM_OBJECT_0853 0x007
#define ID_CUSTOM_OBJECT_0837 0x008
#define ID_CUSTOM_OBJECT_0852 0x009
#define ID_CUSTOM_OBJECT_2027 0x00a
#define ID_CUSTOM_OBJECT_087E 0x00b
#define ID_CUSTOM_OBJECT_9021 0x00c
#define ID_CUSTOM_OBJECT_282A 0x00d
#define ID_CUSTOM_OBJECT_0838 0x00e
#define ID_CUSTOM_OBJECT_083D 0x00f
#define ID_CUSTOM_OBJECT_084E 0x010
#define ID_CUSTOM_OBJECT_085F 0x011
#define ID_CUSTOM_OBJECT_085D 0x012
#define ID_CUSTOM_OBJECT_085A 0x013
#define ID_CUSTOM_OBJECT_0844 0x014
#define ID_CUSTOM_OBJECT_0835 0x015
#define ID_CUSTOM_OBJECT_1816 0x016
#define ID_CUSTOM_OBJECT_0825 0x017
#define ID_CUSTOM_OBJECT_084B 0x018
#define ID_CUSTOM_OBJECT_0839 0x019
#define ID_CUSTOM_OBJECT_1847 0x01a
#define ID_CUSTOM_OBJECT_10C6 0x01b
#define ID_CUSTOM_OBJECT_11F6 0x01c
#define ID_CUSTOM_OBJECT_0A24 0x01d
#define ID_CUSTOM_OBJECT_0A23 0x01e
#define ID_CUSTOM_OBJECT_18A0 0x01f
#define ID_CUSTOM_OBJECT_1090 0x020
#define ID_CUSTOM_OBJECT_18B0 0x021
#define ID_CUSTOM_OBJECT_08B6 0x022
#define ID_CUSTOM_OBJECT_08B5 0x023
#define ID_CUSTOM_OBJECT_08A9 0x024
#define ID_CUSTOM_OBJECT_10BD 0x025
#define ID_CUSTOM_OBJECT_08BE 0x026
#define ID_CUSTOM_OBJECT_105C 0x027
#define ID_CUSTOM_OBJECT_084D 0x028
#define ID_CUSTOM_OBJECT_295F 0x029
#define ID_CUSTOM_OBJECT_182C 0x02a
#define ID_CUSTOM_OBJECT_2023 0x02b
#define ID_CUSTOM_OBJECT_0840 0x02c
#define ID_CUSTOM_OBJECT_30C7 0x02d
#define ID_CUSTOM_OBJECT_0A5C 0x02e
#define ID_CUSTOM_OBJECT_1134 0x02f
#define ID_CUSTOM_OBJECT_0887 0x030
#define ID_CUSTOM_OBJECT_095B 0x031
#define ID_CUSTOM_OBJECT_295E 0x032
#define ID_CUSTOM_OBJECT_09F0 0x033
#define ID_CUSTOM_OBJECT_09D3 0x034
#define ID_CUSTOM_OBJECT_087D 0x035
#define ID_CUSTOM_OBJECT_0869 0x036
#define ID_CUSTOM_OBJECT_09F9 0x037
#define ID_CUSTOM_OBJECT_193B 0x038
#define ID_CUSTOM_OBJECT_0A08 0x039
#define ID_CUSTOM_OBJECT_0A14 0x03a
#define ID_CUSTOM_OBJECT_08CB 0x03b
#define ID_CUSTOM_OBJECT_0A35 0x03c
#define ID_CUSTOM_OBJECT_9233 0x03d
#define ID_CUSTOM_OBJECT_092B 0x03e
#define ID_CUSTOM_OBJECT_0929 0x03f
#define ID_CUSTOM_OBJECT_112A 0x040
#define ID_CUSTOM_OBJECT_0928 0x041
#define ID_CUSTOM_OBJECT_29E9 0x042

#define ID_TRIGGER_0000 0x043
#define ID_TRIGGER_000B 0x044
#define ID_TRIGGER_0005 0x045
#define ID_TRIGGER_000C 0x046
#define ID_TRIGGER_0002 0x047
#define ID_TRIGGER_0004 0x048
#define ID_TRIGGER_0009 0x049
#define ID_TRIGGER_000A 0x04a
#define ID_TRIGGER_0006 0x04b
#define ID_TRIGGER_0028 0x04c
#define ID_TRIGGER_0026 0x04d
#define ID_TRIGGER_0023 0x04e
#define ID_TRIGGER_0021 0x04f
#define ID_TRIGGER_0020 0x050
#define ID_TRIGGER_001D 0x051
#define ID_TRIGGER_001C 0x052
#define ID_TRIGGER_0019 0x053
#define ID_TRIGGER_0018 0x054
#define ID_TRIGGER_0015 0x055
#define ID_TRIGGER_0010 0x056
#define ID_TRIGGER_000E 0x057
#define ID_TRIGGER_0013 0x058
#define ID_TRIGGER_0012 0x059
#define ID_TRIGGER_000F 0x05a
#define ID_TRIGGER_000D 0x05b
#define ID_TRIGGER_0027 0x05c
#define ID_TRIGGER_0025 0x05d
#define ID_TRIGGER_0024 0x05e
#define ID_TRIGGER_0022 0x05f
#define ID_TRIGGER_001F 0x060
#define ID_TRIGGER_0016 0x061
#define ID_TRIGGER_001E 0x062
#define ID_TRIGGER_001B 0x063
#define ID_TRIGGER_001A 0x064
#define ID_TRIGGER_0017 0x065
#define ID_TRIGGER_0014 0x066
#define ID_TRIGGER_0011 0x067
#define ID_TRIGGER_0029 0x068
#define ID_TRIGGER_002A 0x069
#define ID_TRIGGER_002B 0x06a

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

class CustomObjectScript_1074 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0878 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0877 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0879 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_6813 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0853 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0837 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0852 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2027 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_9021 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_282A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0838 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0844 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0835 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1816 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0825 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0839 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1847 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10C6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11F6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A24 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A23 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1090 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18B0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10BD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08BE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_105C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_295F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_182C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2023 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0840 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_30C7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A5C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1134 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0887 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_095B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_295E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09F0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09D3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0869 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09F9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_193B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A08 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A14 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08CB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A35 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_9233 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_092B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0929 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_112A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0928 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_29E9 : public BaseScript {
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

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
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

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0028 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0026 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0023 : public BaseScript {
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

class TriggerScript_001D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001C : public BaseScript {
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

class TriggerScript_0015 : public BaseScript {
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

class TriggerScript_0013 : public BaseScript {
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

class TriggerScript_0027 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0025 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0024 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0022 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001B : public BaseScript {
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

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0029 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_133 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_125 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_130 = 0;
static int ScriptActionCtr_129 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_131 = 0;
static int ScriptActionCtr_132 = 0;
static int ScriptActionCtr_134 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_133 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_125 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_130 = 0;
  ScriptActionCtr_129 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_131 = 0;
  ScriptActionCtr_132 = 0;
  ScriptActionCtr_134 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_133, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_130, file_ptr);
  File_WriteInt(ScriptActionCtr_129, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
  File_WriteInt(ScriptActionCtr_132, file_ptr);
  File_WriteInt(ScriptActionCtr_134, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_133 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_130 = File_ReadInt(file_ptr);
  ScriptActionCtr_129 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
  ScriptActionCtr_132 = File_ReadInt(file_ptr);
  ScriptActionCtr_134 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Stern
2:Hull
3:Aft
4:Cargo
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

#define NUM_DOOR_NAMES 1
static const char *const Door_names[NUM_DOOR_NAMES] = {"Engine Core Aux Do"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 88
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Bay 62 FusableLink",
                                                           "Bay 62 Lance1",
                                                           "Bay 62 Lance2",
                                                           "Engine Spew 1",
                                                           "Engine Spew 2",
                                                           "Intake1",
                                                           "Intake2",
                                                           "Engine1",
                                                           "Engine2",
                                                           "Engine3",
                                                           "Engine Spew 3",
                                                           "Core Switch3",
                                                           "Core Switch2",
                                                           "Core Switch1",
                                                           "Q Door Eng",
                                                           "Lvl E Q Door",
                                                           "Leader Trooper",
                                                           "Eng Cam2",
                                                           "Eng Viewer",
                                                           "Primer Spew 1",
                                                           "Primer Spew 2",
                                                           "Primer Spew 3",
                                                           "Primer Fuse",
                                                           "Exhaust Cooler",
                                                           "Exhaust Patrol1",
                                                           "Exhaust Patrol2",
                                                           "Acc FloorSpew",
                                                           "Aft Well Turret1",
                                                           "Aft Well Commander",
                                                           "Aft Well Turret2",
                                                           "Aft Matcen Switch",
                                                           "Q Door",
                                                           "Q Door D deck",
                                                           "Q Door Exp Well",
                                                           "Q Door B Deck",
                                                           "Q Door C Acc",
                                                           "Q Door Acc1",
                                                           "Q Door Acc2",
                                                           "Q Door Core Acc",
                                                           "Q Door E Deck",
                                                           "Q Door 4way Acc",
                                                           "Q Door Acc0",
                                                           "Q Door A Deck",
                                                           "Q Door D Deck2",
                                                           "Bay62 Landing Door",
                                                           "62Banging",
                                                           "Core Link",
                                                           "Bay 36 Link",
                                                           "Main Deck Link",
                                                           "Bay 62 Data Link",
                                                           "AftMatcen Head Lin",
                                                           "Stern Data Arm",
                                                           "Bad White",
                                                           "Bad White Cage",
                                                           "Bad Tailbot",
                                                           "Bad Tailbot Cage",
                                                           "Air Spewer1",
                                                           "Air Spewer2",
                                                           "Floor Grid Spewer",
                                                           "Floor Spewer",
                                                           "Jeffrey1 Spew",
                                                           "Jeffry 2 Spew",
                                                           "Engine Core Aux Do",
                                                           "Jugg Storage",
                                                           "Recon Interface",
                                                           "ST Hall Monitor",
                                                           "Bay 36 Cam",
                                                           "Aft Well Cam",
                                                           "Saw U Cam",
                                                           "DeathStar Hall Cam",
                                                           "Main Hall Josh",
                                                           "A Deck Cam",
                                                           "Informant Scrubber",
                                                           "Aft Matcen Cam",
                                                           "Main Deck Cam",
                                                           "Core Cam",
                                                           "Bay 62 Matcen Fuse",
                                                           "Missile Exhaust",
                                                           "Spyhunter1",
                                                           "Sub Squid",
                                                           "Josh Act",
                                                           "FlameRas1",
                                                           "FlameRas2",
                                                           "ST Hall Monitor2",
                                                           "ST Hallmonitor3",
                                                           "ST HallMonitor4",
                                                           "DatShip1",
                                                           "Aft Matcen Hole"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 3
static const char *const Room_names[NUM_ROOM_NAMES] = {"Engine", "Core Acc", "Primer Chamber"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 40
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {"Bay 62 PersonDr",
                                                             "Main Deck Ppl Door",
                                                             "Person Door2",
                                                             "Ppl Door Sub",
                                                             "Primer Damaged",
                                                             "CoreEffect",
                                                             "E Acc Matcen Trigge",
                                                             "Core Forcefield Acc",
                                                             "Missile1a",
                                                             "MHull-C",
                                                             "MHull-B",
                                                             "MHull-A",
                                                             "MHull-9",
                                                             "MHull-8",
                                                             "MHull-7",
                                                             "MHull-6",
                                                             "MHull-5",
                                                             "MHull-4",
                                                             "MHull-3",
                                                             "MHull-2",
                                                             "MHull-1",
                                                             "MCargo-4",
                                                             "MCargo-3",
                                                             "MCargo-2",
                                                             "MCargo-1",
                                                             "MStern-5",
                                                             "MStern-4",
                                                             "MStern-3",
                                                             "MStern-2",
                                                             "MStern-1",
                                                             "MAft-7",
                                                             "MAft-6",
                                                             "MAft-5",
                                                             "MAft-4",
                                                             "MAft-3",
                                                             "MAft-2",
                                                             "MAft-1",
                                                             "FlameRasTrigger",
                                                             "StreamAudio1",
                                                             "StreamAudio2"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 4
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbExplosionFarC", "AmbDistantBangMany", "Powerup pickup",
                                                         "HudMessage"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 13
static const char *const Path_names[NUM_PATH_NAMES] = {
    "AFTMatcen Cine", "EndLevelCamPath", "PlayerEndPath",  "Aft Matcen1",   "AftMatcenArt2",
    "AftMatcenArt3",  "AftMatcenArt1",   "AftMatcenSwCam", "LeaderCamPath", "StormtrooperCine",
    "CamIntroPath",   "PlayerIntroPath", "Dat Ship1"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 9
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Aft Matcen1",    "Aft Matcen2",      "Aft Matcen3",
                                                           "Bay 62 Matcen1", "Bay 62 Matcen2",   "Bay 62 Matcen3",
                                                           "Bay 62 Matcen4", "Cargo Acc Matcen", "Aft Matcen4"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 5
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "ShutdownEngineCore", "Disable Aft Matcen", "Destroy StormTrooper Leader", "Eliminate Remaining StormTroopers",
    "Reduce Infected Robot Threat"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 39
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "PplDoors1",      "Bay62Lance",        "EngineDown",   "NoEntry",        "EngineMisfire",  "SecondaryObjective",
    "EngineTakover",  "PrimerDamage",      "CoreRads",     "LevelObjA",      "NoEntry62",      "CoreInfo2",
    "CoreInfo1",      "BayInfoGame",       "BayInfoHud",   "MainDeckGame",   "MainDeckHud",    "Bay62Game",
    "Bay62Hud",       "ShipInfo2",         "ShipInfo1",    "AftMatcenCheck", "AuxCoreDoor",    "CoreAccFF",
    "EndMission",     "GotReconInterface", "RobotCount",   "EndCine",        "LevelObjtives1", "LevelObjtives2",
    "LevelObjtives3", "LeaderTaunt1",      "LeaderTaunt2", "LeaderTaunt3",   "LeaderTaunt4",   "LeaderTaunt5",
    "IntroText",      "Bay62Fuse",         "SpyPlead"};
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
    strcpy(filename, "level13.msg");
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
  case ID_CUSTOM_OBJECT_1074:
    return new CustomObjectScript_1074;
    break;
  case ID_CUSTOM_OBJECT_0878:
    return new CustomObjectScript_0878;
    break;
  case ID_CUSTOM_OBJECT_0877:
    return new CustomObjectScript_0877;
    break;
  case ID_CUSTOM_OBJECT_0879:
    return new CustomObjectScript_0879;
    break;
  case ID_CUSTOM_OBJECT_6813:
    return new CustomObjectScript_6813;
    break;
  case ID_CUSTOM_OBJECT_083A:
    return new CustomObjectScript_083A;
    break;
  case ID_CUSTOM_OBJECT_0853:
    return new CustomObjectScript_0853;
    break;
  case ID_CUSTOM_OBJECT_0837:
    return new CustomObjectScript_0837;
    break;
  case ID_CUSTOM_OBJECT_0852:
    return new CustomObjectScript_0852;
    break;
  case ID_CUSTOM_OBJECT_2027:
    return new CustomObjectScript_2027;
    break;
  case ID_CUSTOM_OBJECT_087E:
    return new CustomObjectScript_087E;
    break;
  case ID_CUSTOM_OBJECT_9021:
    return new CustomObjectScript_9021;
    break;
  case ID_CUSTOM_OBJECT_282A:
    return new CustomObjectScript_282A;
    break;
  case ID_CUSTOM_OBJECT_0838:
    return new CustomObjectScript_0838;
    break;
  case ID_CUSTOM_OBJECT_083D:
    return new CustomObjectScript_083D;
    break;
  case ID_CUSTOM_OBJECT_084E:
    return new CustomObjectScript_084E;
    break;
  case ID_CUSTOM_OBJECT_085F:
    return new CustomObjectScript_085F;
    break;
  case ID_CUSTOM_OBJECT_085D:
    return new CustomObjectScript_085D;
    break;
  case ID_CUSTOM_OBJECT_085A:
    return new CustomObjectScript_085A;
    break;
  case ID_CUSTOM_OBJECT_0844:
    return new CustomObjectScript_0844;
    break;
  case ID_CUSTOM_OBJECT_0835:
    return new CustomObjectScript_0835;
    break;
  case ID_CUSTOM_OBJECT_1816:
    return new CustomObjectScript_1816;
    break;
  case ID_CUSTOM_OBJECT_0825:
    return new CustomObjectScript_0825;
    break;
  case ID_CUSTOM_OBJECT_084B:
    return new CustomObjectScript_084B;
    break;
  case ID_CUSTOM_OBJECT_0839:
    return new CustomObjectScript_0839;
    break;
  case ID_CUSTOM_OBJECT_1847:
    return new CustomObjectScript_1847;
    break;
  case ID_CUSTOM_OBJECT_10C6:
    return new CustomObjectScript_10C6;
    break;
  case ID_CUSTOM_OBJECT_11F6:
    return new CustomObjectScript_11F6;
    break;
  case ID_CUSTOM_OBJECT_0A24:
    return new CustomObjectScript_0A24;
    break;
  case ID_CUSTOM_OBJECT_0A23:
    return new CustomObjectScript_0A23;
    break;
  case ID_CUSTOM_OBJECT_18A0:
    return new CustomObjectScript_18A0;
    break;
  case ID_CUSTOM_OBJECT_1090:
    return new CustomObjectScript_1090;
    break;
  case ID_CUSTOM_OBJECT_18B0:
    return new CustomObjectScript_18B0;
    break;
  case ID_CUSTOM_OBJECT_08B6:
    return new CustomObjectScript_08B6;
    break;
  case ID_CUSTOM_OBJECT_08B5:
    return new CustomObjectScript_08B5;
    break;
  case ID_CUSTOM_OBJECT_08A9:
    return new CustomObjectScript_08A9;
    break;
  case ID_CUSTOM_OBJECT_10BD:
    return new CustomObjectScript_10BD;
    break;
  case ID_CUSTOM_OBJECT_08BE:
    return new CustomObjectScript_08BE;
    break;
  case ID_CUSTOM_OBJECT_105C:
    return new CustomObjectScript_105C;
    break;
  case ID_CUSTOM_OBJECT_084D:
    return new CustomObjectScript_084D;
    break;
  case ID_CUSTOM_OBJECT_295F:
    return new CustomObjectScript_295F;
    break;
  case ID_CUSTOM_OBJECT_182C:
    return new CustomObjectScript_182C;
    break;
  case ID_CUSTOM_OBJECT_2023:
    return new CustomObjectScript_2023;
    break;
  case ID_CUSTOM_OBJECT_0840:
    return new CustomObjectScript_0840;
    break;
  case ID_CUSTOM_OBJECT_30C7:
    return new CustomObjectScript_30C7;
    break;
  case ID_CUSTOM_OBJECT_0A5C:
    return new CustomObjectScript_0A5C;
    break;
  case ID_CUSTOM_OBJECT_1134:
    return new CustomObjectScript_1134;
    break;
  case ID_CUSTOM_OBJECT_0887:
    return new CustomObjectScript_0887;
    break;
  case ID_CUSTOM_OBJECT_095B:
    return new CustomObjectScript_095B;
    break;
  case ID_CUSTOM_OBJECT_295E:
    return new CustomObjectScript_295E;
    break;
  case ID_CUSTOM_OBJECT_09F0:
    return new CustomObjectScript_09F0;
    break;
  case ID_CUSTOM_OBJECT_09D3:
    return new CustomObjectScript_09D3;
    break;
  case ID_CUSTOM_OBJECT_087D:
    return new CustomObjectScript_087D;
    break;
  case ID_CUSTOM_OBJECT_0869:
    return new CustomObjectScript_0869;
    break;
  case ID_CUSTOM_OBJECT_09F9:
    return new CustomObjectScript_09F9;
    break;
  case ID_CUSTOM_OBJECT_193B:
    return new CustomObjectScript_193B;
    break;
  case ID_CUSTOM_OBJECT_0A08:
    return new CustomObjectScript_0A08;
    break;
  case ID_CUSTOM_OBJECT_0A14:
    return new CustomObjectScript_0A14;
    break;
  case ID_CUSTOM_OBJECT_08CB:
    return new CustomObjectScript_08CB;
    break;
  case ID_CUSTOM_OBJECT_0A35:
    return new CustomObjectScript_0A35;
    break;
  case ID_CUSTOM_OBJECT_9233:
    return new CustomObjectScript_9233;
    break;
  case ID_CUSTOM_OBJECT_092B:
    return new CustomObjectScript_092B;
    break;
  case ID_CUSTOM_OBJECT_0929:
    return new CustomObjectScript_0929;
    break;
  case ID_CUSTOM_OBJECT_112A:
    return new CustomObjectScript_112A;
    break;
  case ID_CUSTOM_OBJECT_0928:
    return new CustomObjectScript_0928;
    break;
  case ID_CUSTOM_OBJECT_29E9:
    return new CustomObjectScript_29E9;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0028:
    return new TriggerScript_0028;
    break;
  case ID_TRIGGER_0026:
    return new TriggerScript_0026;
    break;
  case ID_TRIGGER_0023:
    return new TriggerScript_0023;
    break;
  case ID_TRIGGER_0021:
    return new TriggerScript_0021;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
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
  case ID_TRIGGER_0027:
    return new TriggerScript_0027;
    break;
  case ID_TRIGGER_0025:
    return new TriggerScript_0025;
    break;
  case ID_TRIGGER_0024:
    return new TriggerScript_0024;
    break;
  case ID_TRIGGER_0022:
    return new TriggerScript_0022;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0029:
    return new TriggerScript_0029;
    break;
  case ID_TRIGGER_002A:
    return new TriggerScript_002A;
    break;
  case ID_TRIGGER_002B:
    return new TriggerScript_002B;
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
  case ID_CUSTOM_OBJECT_1074:
    delete ((CustomObjectScript_1074 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0878:
    delete ((CustomObjectScript_0878 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0877:
    delete ((CustomObjectScript_0877 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0879:
    delete ((CustomObjectScript_0879 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_6813:
    delete ((CustomObjectScript_6813 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083A:
    delete ((CustomObjectScript_083A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0853:
    delete ((CustomObjectScript_0853 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0837:
    delete ((CustomObjectScript_0837 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0852:
    delete ((CustomObjectScript_0852 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2027:
    delete ((CustomObjectScript_2027 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087E:
    delete ((CustomObjectScript_087E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_9021:
    delete ((CustomObjectScript_9021 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_282A:
    delete ((CustomObjectScript_282A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0838:
    delete ((CustomObjectScript_0838 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083D:
    delete ((CustomObjectScript_083D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084E:
    delete ((CustomObjectScript_084E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085F:
    delete ((CustomObjectScript_085F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085D:
    delete ((CustomObjectScript_085D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085A:
    delete ((CustomObjectScript_085A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0844:
    delete ((CustomObjectScript_0844 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0835:
    delete ((CustomObjectScript_0835 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1816:
    delete ((CustomObjectScript_1816 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0825:
    delete ((CustomObjectScript_0825 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084B:
    delete ((CustomObjectScript_084B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0839:
    delete ((CustomObjectScript_0839 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1847:
    delete ((CustomObjectScript_1847 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10C6:
    delete ((CustomObjectScript_10C6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11F6:
    delete ((CustomObjectScript_11F6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A24:
    delete ((CustomObjectScript_0A24 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A23:
    delete ((CustomObjectScript_0A23 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A0:
    delete ((CustomObjectScript_18A0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1090:
    delete ((CustomObjectScript_1090 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18B0:
    delete ((CustomObjectScript_18B0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B6:
    delete ((CustomObjectScript_08B6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B5:
    delete ((CustomObjectScript_08B5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A9:
    delete ((CustomObjectScript_08A9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10BD:
    delete ((CustomObjectScript_10BD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08BE:
    delete ((CustomObjectScript_08BE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_105C:
    delete ((CustomObjectScript_105C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084D:
    delete ((CustomObjectScript_084D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_295F:
    delete ((CustomObjectScript_295F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_182C:
    delete ((CustomObjectScript_182C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2023:
    delete ((CustomObjectScript_2023 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0840:
    delete ((CustomObjectScript_0840 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_30C7:
    delete ((CustomObjectScript_30C7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A5C:
    delete ((CustomObjectScript_0A5C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1134:
    delete ((CustomObjectScript_1134 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0887:
    delete ((CustomObjectScript_0887 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_095B:
    delete ((CustomObjectScript_095B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_295E:
    delete ((CustomObjectScript_295E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09F0:
    delete ((CustomObjectScript_09F0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09D3:
    delete ((CustomObjectScript_09D3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087D:
    delete ((CustomObjectScript_087D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0869:
    delete ((CustomObjectScript_0869 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09F9:
    delete ((CustomObjectScript_09F9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_193B:
    delete ((CustomObjectScript_193B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A08:
    delete ((CustomObjectScript_0A08 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A14:
    delete ((CustomObjectScript_0A14 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08CB:
    delete ((CustomObjectScript_08CB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A35:
    delete ((CustomObjectScript_0A35 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_9233:
    delete ((CustomObjectScript_9233 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_092B:
    delete ((CustomObjectScript_092B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0929:
    delete ((CustomObjectScript_0929 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_112A:
    delete ((CustomObjectScript_112A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0928:
    delete ((CustomObjectScript_0928 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_29E9:
    delete ((CustomObjectScript_29E9 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0028:
    delete ((TriggerScript_0028 *)ptr);
    break;
  case ID_TRIGGER_0026:
    delete ((TriggerScript_0026 *)ptr);
    break;
  case ID_TRIGGER_0023:
    delete ((TriggerScript_0023 *)ptr);
    break;
  case ID_TRIGGER_0021:
    delete ((TriggerScript_0021 *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
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
  case ID_TRIGGER_0027:
    delete ((TriggerScript_0027 *)ptr);
    break;
  case ID_TRIGGER_0025:
    delete ((TriggerScript_0025 *)ptr);
    break;
  case ID_TRIGGER_0024:
    delete ((TriggerScript_0024 *)ptr);
    break;
  case ID_TRIGGER_0022:
    delete ((TriggerScript_0022 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0029:
    delete ((TriggerScript_0029 *)ptr);
    break;
  case ID_TRIGGER_002A:
    delete ((TriggerScript_002A *)ptr);
    break;
  case ID_TRIGGER_002B:
    delete ((TriggerScript_002B *)ptr);
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
  case ID_CUSTOM_OBJECT_1074:
  case ID_CUSTOM_OBJECT_0878:
  case ID_CUSTOM_OBJECT_0877:
  case ID_CUSTOM_OBJECT_0879:
  case ID_CUSTOM_OBJECT_6813:
  case ID_CUSTOM_OBJECT_083A:
  case ID_CUSTOM_OBJECT_0853:
  case ID_CUSTOM_OBJECT_0837:
  case ID_CUSTOM_OBJECT_0852:
  case ID_CUSTOM_OBJECT_2027:
  case ID_CUSTOM_OBJECT_087E:
  case ID_CUSTOM_OBJECT_9021:
  case ID_CUSTOM_OBJECT_282A:
  case ID_CUSTOM_OBJECT_0838:
  case ID_CUSTOM_OBJECT_083D:
  case ID_CUSTOM_OBJECT_084E:
  case ID_CUSTOM_OBJECT_085F:
  case ID_CUSTOM_OBJECT_085D:
  case ID_CUSTOM_OBJECT_085A:
  case ID_CUSTOM_OBJECT_0844:
  case ID_CUSTOM_OBJECT_0835:
  case ID_CUSTOM_OBJECT_1816:
  case ID_CUSTOM_OBJECT_0825:
  case ID_CUSTOM_OBJECT_084B:
  case ID_CUSTOM_OBJECT_0839:
  case ID_CUSTOM_OBJECT_1847:
  case ID_CUSTOM_OBJECT_10C6:
  case ID_CUSTOM_OBJECT_11F6:
  case ID_CUSTOM_OBJECT_0A24:
  case ID_CUSTOM_OBJECT_0A23:
  case ID_CUSTOM_OBJECT_18A0:
  case ID_CUSTOM_OBJECT_1090:
  case ID_CUSTOM_OBJECT_18B0:
  case ID_CUSTOM_OBJECT_08B6:
  case ID_CUSTOM_OBJECT_08B5:
  case ID_CUSTOM_OBJECT_08A9:
  case ID_CUSTOM_OBJECT_10BD:
  case ID_CUSTOM_OBJECT_08BE:
  case ID_CUSTOM_OBJECT_105C:
  case ID_CUSTOM_OBJECT_084D:
  case ID_CUSTOM_OBJECT_295F:
  case ID_CUSTOM_OBJECT_182C:
  case ID_CUSTOM_OBJECT_2023:
  case ID_CUSTOM_OBJECT_0840:
  case ID_CUSTOM_OBJECT_30C7:
  case ID_CUSTOM_OBJECT_0A5C:
  case ID_CUSTOM_OBJECT_1134:
  case ID_CUSTOM_OBJECT_0887:
  case ID_CUSTOM_OBJECT_095B:
  case ID_CUSTOM_OBJECT_295E:
  case ID_CUSTOM_OBJECT_09F0:
  case ID_CUSTOM_OBJECT_09D3:
  case ID_CUSTOM_OBJECT_087D:
  case ID_CUSTOM_OBJECT_0869:
  case ID_CUSTOM_OBJECT_09F9:
  case ID_CUSTOM_OBJECT_193B:
  case ID_CUSTOM_OBJECT_0A08:
  case ID_CUSTOM_OBJECT_0A14:
  case ID_CUSTOM_OBJECT_08CB:
  case ID_CUSTOM_OBJECT_0A35:
  case ID_CUSTOM_OBJECT_9233:
  case ID_CUSTOM_OBJECT_092B:
  case ID_CUSTOM_OBJECT_0929:
  case ID_CUSTOM_OBJECT_112A:
  case ID_CUSTOM_OBJECT_0928:
  case ID_CUSTOM_OBJECT_29E9:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0028:
  case ID_TRIGGER_0026:
  case ID_TRIGGER_0023:
  case ID_TRIGGER_0021:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_0027:
  case ID_TRIGGER_0025:
  case ID_TRIGGER_0024:
  case ID_TRIGGER_0022:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0029:
  case ID_TRIGGER_002A:
  case ID_TRIGGER_002B:
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
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0028;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0026;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0023;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0021;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_0027;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_0025;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_0024;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_0022;

  if (trigger_room == Trigger_rooms[29] && trigger_face == Trigger_faces[29])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[30] && trigger_face == Trigger_faces[30])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[31] && trigger_face == Trigger_faces[31])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[32] && trigger_face == Trigger_faces[32])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[33] && trigger_face == Trigger_faces[33])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[34] && trigger_face == Trigger_faces[34])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[35] && trigger_face == Trigger_faces[35])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[36] && trigger_face == Trigger_faces[36])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[37] && trigger_face == Trigger_faces[37])
    return ID_TRIGGER_0029;

  if (trigger_room == Trigger_rooms[38] && trigger_face == Trigger_faces[38])
    return ID_TRIGGER_002A;

  if (trigger_room == Trigger_rooms[39] && trigger_face == Trigger_faces[39])
    return ID_TRIGGER_002B;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[66];
  static int cust_id_list[66] = {
      ID_CUSTOM_OBJECT_1074, ID_CUSTOM_OBJECT_0878, ID_CUSTOM_OBJECT_0877, ID_CUSTOM_OBJECT_0879, ID_CUSTOM_OBJECT_6813,
      ID_CUSTOM_OBJECT_083A, ID_CUSTOM_OBJECT_0853, ID_CUSTOM_OBJECT_0837, ID_CUSTOM_OBJECT_0852, ID_CUSTOM_OBJECT_2027,
      ID_CUSTOM_OBJECT_087E, ID_CUSTOM_OBJECT_9021, ID_CUSTOM_OBJECT_282A, ID_CUSTOM_OBJECT_0838, ID_CUSTOM_OBJECT_083D,
      ID_CUSTOM_OBJECT_084E, ID_CUSTOM_OBJECT_085F, ID_CUSTOM_OBJECT_085D, ID_CUSTOM_OBJECT_085A, ID_CUSTOM_OBJECT_0844,
      ID_CUSTOM_OBJECT_0835, ID_CUSTOM_OBJECT_1816, ID_CUSTOM_OBJECT_0825, ID_CUSTOM_OBJECT_084B, ID_CUSTOM_OBJECT_0839,
      ID_CUSTOM_OBJECT_1847, ID_CUSTOM_OBJECT_10C6, ID_CUSTOM_OBJECT_11F6, ID_CUSTOM_OBJECT_0A24, ID_CUSTOM_OBJECT_0A23,
      ID_CUSTOM_OBJECT_18A0, ID_CUSTOM_OBJECT_1090, ID_CUSTOM_OBJECT_18B0, ID_CUSTOM_OBJECT_08B6, ID_CUSTOM_OBJECT_08B5,
      ID_CUSTOM_OBJECT_08A9, ID_CUSTOM_OBJECT_10BD, ID_CUSTOM_OBJECT_08BE, ID_CUSTOM_OBJECT_105C, ID_CUSTOM_OBJECT_084D,
      ID_CUSTOM_OBJECT_295F, ID_CUSTOM_OBJECT_182C, ID_CUSTOM_OBJECT_2023, ID_CUSTOM_OBJECT_0840, ID_CUSTOM_OBJECT_30C7,
      ID_CUSTOM_OBJECT_0A5C, ID_CUSTOM_OBJECT_1134, ID_CUSTOM_OBJECT_0887, ID_CUSTOM_OBJECT_095B, ID_CUSTOM_OBJECT_295E,
      ID_CUSTOM_OBJECT_09F0, ID_CUSTOM_OBJECT_09D3, ID_CUSTOM_OBJECT_087D, ID_CUSTOM_OBJECT_0869, ID_CUSTOM_OBJECT_09F9,
      ID_CUSTOM_OBJECT_193B, ID_CUSTOM_OBJECT_0A08, ID_CUSTOM_OBJECT_0A14, ID_CUSTOM_OBJECT_08CB, ID_CUSTOM_OBJECT_0A35,
      ID_CUSTOM_OBJECT_9233, ID_CUSTOM_OBJECT_092B, ID_CUSTOM_OBJECT_0929, ID_CUSTOM_OBJECT_112A, ID_CUSTOM_OBJECT_0928,
      ID_CUSTOM_OBJECT_29E9};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[11];
  cust_handle_list[2] = Object_handles[12];
  cust_handle_list[3] = Object_handles[13];
  cust_handle_list[4] = Object_handles[14];
  cust_handle_list[5] = Object_handles[15];
  cust_handle_list[6] = Object_handles[22];
  cust_handle_list[7] = Object_handles[23];
  cust_handle_list[8] = Object_handles[26];
  cust_handle_list[9] = Object_handles[27];
  cust_handle_list[10] = Object_handles[29];
  cust_handle_list[11] = Object_handles[30];
  cust_handle_list[12] = Object_handles[31];
  cust_handle_list[13] = Object_handles[32];
  cust_handle_list[14] = Object_handles[33];
  cust_handle_list[15] = Object_handles[34];
  cust_handle_list[16] = Object_handles[35];
  cust_handle_list[17] = Object_handles[36];
  cust_handle_list[18] = Object_handles[37];
  cust_handle_list[19] = Object_handles[38];
  cust_handle_list[20] = Object_handles[39];
  cust_handle_list[21] = Object_handles[40];
  cust_handle_list[22] = Object_handles[41];
  cust_handle_list[23] = Object_handles[42];
  cust_handle_list[24] = Object_handles[43];
  cust_handle_list[25] = Object_handles[44];
  cust_handle_list[26] = Object_handles[46];
  cust_handle_list[27] = Object_handles[47];
  cust_handle_list[28] = Object_handles[48];
  cust_handle_list[29] = Object_handles[49];
  cust_handle_list[30] = Object_handles[50];
  cust_handle_list[31] = Object_handles[51];
  cust_handle_list[32] = Object_handles[52];
  cust_handle_list[33] = Object_handles[54];
  cust_handle_list[34] = Object_handles[55];
  cust_handle_list[35] = Object_handles[53];
  cust_handle_list[36] = Object_handles[56];
  cust_handle_list[37] = Object_handles[57];
  cust_handle_list[38] = Object_handles[58];
  cust_handle_list[39] = Object_handles[59];
  cust_handle_list[40] = Object_handles[60];
  cust_handle_list[41] = Object_handles[61];
  cust_handle_list[42] = Object_handles[62];
  cust_handle_list[43] = Object_handles[63];
  cust_handle_list[44] = Object_handles[16];
  cust_handle_list[45] = Object_handles[64];
  cust_handle_list[46] = Object_handles[66];
  cust_handle_list[47] = Object_handles[67];
  cust_handle_list[48] = Object_handles[68];
  cust_handle_list[49] = Object_handles[69];
  cust_handle_list[50] = Object_handles[70];
  cust_handle_list[51] = Object_handles[71];
  cust_handle_list[52] = Object_handles[72];
  cust_handle_list[53] = Object_handles[73];
  cust_handle_list[54] = Object_handles[74];
  cust_handle_list[55] = Object_handles[76];
  cust_handle_list[56] = Object_handles[78];
  cust_handle_list[57] = Object_handles[79];
  cust_handle_list[58] = Object_handles[80];
  cust_handle_list[59] = Object_handles[81];
  cust_handle_list[60] = Object_handles[82];
  cust_handle_list[61] = Object_handles[65];
  cust_handle_list[62] = Object_handles[83];
  cust_handle_list[63] = Object_handles[84];
  cust_handle_list[64] = Object_handles[85];
  cust_handle_list[65] = Object_handles[86];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 66;
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
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 119: Level Start - Initialize Variables
    if (1) {
      aUserFlagSet(0, 0);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }

    // Script 007: Engine Malfunction Random Timer
    if (1) {
      aSetLevelTimer(qRandomValue(500.000000f, 650.000000f), 2);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 013: Create Primer Room Wind
    if (1) {
      aRoomSetWind(Room_indexes[2], 0.007000f, 0.287000f, -0.957000f, 5.000000f);
      aTurnOnSpew(Object_handles[19], -1, 8, 0.000000f, 0.000000f, 65536, 0, 4.500000f, 0.100000f, -1.000000f,
                  14.000000f, 18.000000f, 1, 0);
      aTurnOnSpew(Object_handles[20], -1, 8, 0.000000f, 0.000000f, 65536, 0, 4.500000f, 0.100000f, -1.000000f,
                  14.000000f, 18.000000f, 1, 1);
      aTurnOnSpew(Object_handles[21], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  9.000000f, 80.000000f, 0, 2);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }

    // Script 052: LevelStart Robot Count
    if (1) {
      aSetLevelTimer(2.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }

    // Script 054: Aft Matcen Production
    if (1) {
      aMatcenSetState(1, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[1]);
      aMatcenSetState(1, Matcen_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 062: IntroLevel
    if ((ScriptActionCtr_062 < 1) && (1)) {
      aCinematicIntro(Path_indexes[10], Message_strings[36], Object_handles[75], Path_indexes[11], 20.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }

    // Script 088: Music Intro Init
    if (1) {
      aMusicSetRegionAll(2);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }

    // Script 134: Make Invisible PowerUp Invisible
    if (1) {
      aObjHide(Object_handles[87]);

      // Increment the script action counter
      if (ScriptActionCtr_134 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_134++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 005: Engine Wind Timer
    if (1) {
      if ((event_data->id == 1) && ((ScriptActionCtr_010 > 0) == false)) {
        aRoomChangeWind(Room_indexes[0], 0.014000f, 0.095000f, -0.995000f, 1.000000f, 1.000000f);
        aSetLevelTimer(5.000000f, 0);
      }
      if ((event_data->id == 0) && ((ScriptActionCtr_010 > 0) == false)) {
        aRoomChangeWind(Room_indexes[0], 0.014000f, 0.095000f, -0.995000f, 35.000000f, 0.500000f);
        aSetLevelTimer(6.000000f, 1);
        aTurnOnSpew(Object_handles[3], -1, 6, 0.000000f, 0.000000f, 65536, 0, 0.200000f, 0.090000f, 6.000000f,
                    100.000000f, 190.000000f, 0, -1);
        aTurnOnSpew(Object_handles[4], -1, 6, 0.000000f, 0.000000f, 65536, 0, 0.200000f, 0.090000f, 6.000000f,
                    90.000000f, 190.000000f, 0, -1);
        aMiscViewerShake(70.000000f);
        aTurnOnSpew(Object_handles[5], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.900000f, 1.200000f, 4.000000f,
                    100.000000f, 1, 6);
        aTurnOnSpew(Object_handles[6], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 1.000000f, 1.000000f, 4.000000f,
                    90.000000f, 1, 6);
        aSoundPlayObject(Sound_indexes[0], Object_handles[7], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[8], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[9], 1.000000f);
        aTurnOnSpew(Object_handles[10], -1, 6, 0.000000f, 0.000000f, 65536, 0, 0.200000f, 0.090000f, 6.000000f,
                    90.000000f, 190.000000f, 0, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 009: Engine Misfire Viewer Shake
    if ((2 == event_data->id) && (qObjExists(Object_handles[16]) == true) && (qUserFlag(0) == false)) {
      aMiscViewerShake(100.000000f);
      aSetLevelTimer(1.000000f, 0);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[4]);
      aCreatePopupView(0, Object_handles[17], 8.000000f, 1.000000f);
      aAddGameMessage(Message_strings[5], Message_strings[6]);
      aGoalEnableDisable(1, Goal_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 010: EngineShutdown
    if (3 == event_data->id) {
      aUserFlagSet(0, 1);
      aRoomChangeWind(Room_indexes[0], 0.000000f, 0.000000f, 0.000000f, 1.000000f, 11.000000f);
      aTurnOffSpew(3);
      aTurnOffSpew(1);
      aTurnOffSpew(5);
      aGoalCompleted(Goal_indexes[0], 1);
      aPortalRenderSet(0, 5, Room_indexes[1], 1);
      aCreatePopupView(0, Object_handles[18], 10.000000f, 1.000000f);
      aDoorLockUnlock(0, Door_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }

    // Script 051: Count Robots
    if (event_data->id == 5) {
      if (qMathAddInt(qMathAddInt(qObjCountTypeID(2, "stormtrooperred"), qObjCountTypeID(2, "stormtrooperwhite")),
                      qObjCountTypeID(2, "stormtroopergreen")) <= 3) {
        aGoalCompleted(Goal_indexes[3], 1);
        aGoalCompleted(Goal_indexes[4], 1);
        aShowColoredHUDMessage(0, 255, 232, Message_strings[24]);
        aSetLevelTimer(10.000000f, 6);
      } else {
        aSetLevelTimer(2.000000f, 5);
      }

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }

    // Script 053: End level Timer
    if (event_data->id == 6) {
      aStartEndlevelSequencePath(Path_indexes[1], Path_indexes[2], 9.000000f, Message_strings[27]);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 076: Aft Matcen Path Controller
    if (event_data->id == Matcen_indexes[0]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[3], 4096, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }

    // Script 075: Aft Matcen Path Controller
    if (event_data->id == Matcen_indexes[1]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[4], 4096, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }

    // Script 074: Aft Matcen Path Controller
    if (event_data->id == Matcen_indexes[2]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[5], 4096, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }

    // Script 055: Aft Matcen Path Controller
    if (event_data->id == Matcen_indexes[8]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[6], 4096, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 049: Start Level Objectives Messege
    if ((ScriptActionCtr_049 < 1) && (1)) {
      aCinematicSimple(Path_indexes[7], Message_strings[28], Object_handles[30], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1074::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Bay 62 Fusable Link
    if ((ScriptActionCtr_001 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[1]);
      aObjDestroy(data->me_handle);
      aAISetState(0, Object_handles[1]);
      aAISetState(0, Object_handles[2]);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0878::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Core Shutdown Switch3
    if ((ScriptActionCtr_012 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      if (((ScriptActionCtr_006 > 0) == true) && ((ScriptActionCtr_011 > 0) == true)) {
        aSetLevelTimer(0.000000f, 3);
        aShowHUDMessage(Message_strings[2]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0877::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Core Shutdown Switch2
    if ((ScriptActionCtr_011 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      if (((ScriptActionCtr_006 > 0) == true) && ((ScriptActionCtr_012 > 0) == true)) {
        aSetLevelTimer(0.000000f, 3);
        aShowHUDMessage(Message_strings[2]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0879::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Core Shutdown Switch1
    if ((ScriptActionCtr_006 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      if (((ScriptActionCtr_011 > 0) == true) && ((ScriptActionCtr_012 > 0) == true)) {
        aSetLevelTimer(0.000000f, 3);
        aShowHUDMessage(Message_strings[2]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_6813::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0853::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Primer Room Trigger
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aObjDestroy(data->me_handle);
      aRoomChangeWind(Room_indexes[2], 0.082000f, 0.997000f, -0.022000f, 5.000000f, 1.000000f);
      aTurnOffSpew(0);
      aTurnOffSpew(1);
      aTurnOffSpew(2);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0837::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Coolant Sensor
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aAISetMode(Object_handles[24], 1);
      aAISetMode(Object_handles[25], 6);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0852::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 019: Acc Floor Spewer
    if (1) {
      aTurnOnSpew(Object_handles[26], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.500000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2027::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 023: Turret Controller
    if (qObjExists(Object_handles[28]) == false) {
      aAISetState(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 022: Turret Controller
    if (qObjExists(Object_handles[28]) == false) {
      aAISetState(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_9021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: Aft Matcen Goal
    if ((ScriptActionCtr_031 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[1], 1);
      aObjPlayAnim(data->me_handle, 0, 2, 1.000000f, 0);
      aShowColoredHUDMessage(0, 150, 255, Message_strings[9]);
      aMatcenSetValues(Matcen_indexes[0], 0, 1.000000f, 1);
      aMatcenSetValues(Matcen_indexes[1], 0, 1.000000f, 1);
      aMatcenSetValues(Matcen_indexes[2], 0, 1.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 056: Start Level Objectives Messege 2
    if ((ScriptActionCtr_056 < 1) && (1)) {
      aCinematicSimple(Path_indexes[8], Message_strings[29], Object_handles[16], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_282A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0838::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0844::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0835::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1816::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0825::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 120: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0839::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: NonPlayer Entry
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1847::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: NonPlayer Entry - 62 Acc Door
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aSoundPlayObject(Sound_indexes[1], Object_handles[45], 1.000000f);
      aShowHUDMessage(Message_strings[10]);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10C6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Core Hall Data Link
    if ((ScriptActionCtr_030 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aAddGameMessage(Message_strings[11], Message_strings[12]);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11F6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Bay 36 Data Link
    if ((ScriptActionCtr_085 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aAddGameMessage(Message_strings[13], Message_strings[14]);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A24::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 087: Main Deck Data Link
    if ((ScriptActionCtr_087 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aAddGameMessage(Message_strings[15], Message_strings[16]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A23::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 086: Bay 62 Data Link
    if ((ScriptActionCtr_086 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aAddGameMessage(Message_strings[17], Message_strings[18]);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Aft Matcen Data Link
    if ((ScriptActionCtr_077 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aAddGameMessage(Message_strings[19], Message_strings[20]);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1090::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Stern Data Link
    if ((ScriptActionCtr_033 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aCinematicSimple(Path_indexes[0], Message_strings[21], Object_handles[30], 8.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18B0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 028: Bad White Cage Exists
    if (qObjExists(Object_handles[53]) == true) {
      aAISetState(0, Object_handles[52]);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 029: Bad TailbotCage Exists
    if (qObjExists(Object_handles[53]) == true) {
      aAISetState(0, Object_handles[54]);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 026: Bad TailbotCage Destroyed
    if (1) {
      aAISetState(1, Object_handles[54]);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;

      return CONTINUE_DEFAULT;
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

    // Script 027: Bad White Cage Destroyed
    if (1) {
      aAISetState(1, Object_handles[52]);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10BD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 032: Air Spewers
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f, 5.000000f,
                  60.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08BE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 041: Air Spewers
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f, 5.000000f,
                  60.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_105C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 050: Air Spewers
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f, 5.000000f,
                  60.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 072: Air Spewers
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.150000f, -1.000000f, 10.000000f,
                  50.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_295F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 123: Air Spewers
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.900000f, 0.150000f, -1.000000f, 14.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 069: Leader Taunt Cam
    if ((ScriptActionCtr_069 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[33]);
      aShowHUDMessage(Message_strings[34]);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_182C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 064: Air Spewers
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.900000f, 0.150000f, -1.000000f, 14.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2023::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: Aux Core Access
    if ((ScriptActionCtr_034 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == false))) {
      aShowHUDMessage(Message_strings[22]);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0840::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 035: Jugg AI
    if (1) {
      aAISetState(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_30C7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 040: Stormtrooper Leader Death
    if (1) {
      aGoalCompleted(Goal_indexes[2], 1);
      aMatcenSetEnableState(0, Matcen_indexes[3]);
      aMatcenSetEnableState(0, Matcen_indexes[4]);
      aMatcenSetEnableState(0, Matcen_indexes[5]);
      aMatcenSetEnableState(0, Matcen_indexes[6]);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 073: Start Level Objectives Messege 3
    if ((ScriptActionCtr_073 < 1) && (1)) {
      aSoundPlaySteaming("VoxL13StartLevel.osf", 1.000000f);
      aCinematicSimple(Path_indexes[9], Message_strings[30], Object_handles[65], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A5C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 089: Picked Up Recon Interface
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessageObj(Message_strings[25], event_data->it_handle);
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 124: Used Recon Interface
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjGhostSet(0, data->me_handle);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aShowHUDMessageI(Message_strings[26], qMathAddInt(qMathAddInt(qObjCountTypeID(2, "stormtrooperred"),
                                                                    qObjCountTypeID(2, "stormtroopergreen")),
                                                        qObjCountTypeID(2, "stormtrooperwhite")));
      aSoundPlay2D(Sound_indexes[3], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1134::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 058: Leader Taunt Cam
    if ((ScriptActionCtr_058 < 2) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[31]);
      aShowHUDMessage(Message_strings[32]);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0887::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 059: Leader Taunt Cam
    if ((ScriptActionCtr_059 < 2) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[33]);
      aShowHUDMessage(Message_strings[34]);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_095B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 068: Leader Taunt Cam
    if ((ScriptActionCtr_068 < 4) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[33]);
      aShowHUDMessage(Message_strings[34]);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_295E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 070: Leader Taunt Cam
    if ((ScriptActionCtr_070 < 2) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[31]);
      aShowHUDMessage(Message_strings[33]);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09F0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 071: Leader Taunt Cam
    if ((ScriptActionCtr_071 < 2) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[33]);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09D3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 060: Leader Taunt Cam
    if ((ScriptActionCtr_060 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[31]);
      aShowHUDMessage(Message_strings[34]);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 067: Leader Taunt Cam
    if ((ScriptActionCtr_067 < 2) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[33]);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0869::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 048: Leader Taunt Cam
    if ((ScriptActionCtr_048 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[35]);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09F9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 057: Leader Taunt Cam
    if ((ScriptActionCtr_057 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[31]);
      aShowHUDMessage(Message_strings[32]);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_193B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Bay  62 Matcen Fuse
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatcenSetEnableState(0, Matcen_indexes[3]);
      aMatcenSetEnableState(0, Matcen_indexes[6]);
      aShowHUDMessage(Message_strings[37]);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A08::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: SpyHunter_Stay
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aAISetState(1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 082: Spy Hunter Off
    if (1) {
      aAISetState(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 083: SpyHunter_Plead
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAISetMode(data->me_handle, 1);
      aShowHUDMessage(Message_strings[38]);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A14::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: Sub Squid
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aAISetState(1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 081: Sub Squid Off
    if (1) {
      aAISetState(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08CB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 084: Josh Attack
    if (qObjIsPlayer(event_data->it_handle) == true) {

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A35::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 133: FlameRas Created
    if (1) {
      aObjSetMovementType(data->me_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_133 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_133++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_9233::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 118: FlameRas Created
    if (1) {
      aObjSetMovementType(data->me_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_092B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 127: ST Monitor - Sleep
    if (1) {
      aObjSetMovementType(data->me_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 130: ST Monitor - Awaken
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0929::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 126: ST Monitor2 - Sleep
    if (1) {
      aObjSetMovementType(data->me_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 129: ST Monitor2 - Awaken
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_112A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 125: ST Monitor3 - Sleep
    if (1) {
      aObjSetMovementType(data->me_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 128: ST Monitor3 - Awaken
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0928::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 002: ST Monitor4 - Sleep
    if (1) {
      aObjSetMovementType(data->me_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 121: ST Monitor4 - Awaken
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_29E9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 122: DatShip1 --  Path On Creation
    if (1) {
      aAIGoalFollowPath(Object_handles[86], Path_indexes[12], 1, 19, 1, 3, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: Personell Acc Doors
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowColoredHUDMessage(100, 100, 255, Message_strings[0]);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Personell Acc Doors
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowColoredHUDMessage(100, 100, 255, Message_strings[0]);

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

    // Script 078: Personell Acc Doors
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowColoredHUDMessage(100, 100, 255, Message_strings[0]);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 000: Personell Acc Doors
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowColoredHUDMessage(100, 100, 255, Message_strings[0]);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: PrimerDamage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 33.330002f);
      aShowHUDMessage(Message_strings[7]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: CoreRoom Microwave Effect
    if ((ScriptActionCtr_020 < 15) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjDeform(event_data->it_handle, 0.300000f, 2.500000f);
      aShowColoredHUDMessage(255, 25, 0, Message_strings[8]);
      aObjApplyDamage(event_data->it_handle, 5.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: Cargo Acc Matcen
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMatcenSetState(1, Matcen_indexes[7]);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: Core Acc Forcefield
    if ((ScriptActionCtr_047 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[23]);

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

    // Script 004: Missile Smoke
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aTurnOnSpew(Object_handles[77], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.070000f, 10.000000f,
                  2.200000f, 90.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0028::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 101: Music Hull-C
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0026::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 100: Music Hull-B
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0023::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 099: Music Hull-A
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 098: Music Hull-9
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 096: Music Hull-8
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 097: Music Hull-7
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 095: Music Hull-6
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 094: Music Hull-5
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 093: Music Hull-4
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 092: Music Hull-3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 091: Music Hull-2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 090: Music Hull-1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 105: Music Cargo-4
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 104: Music Cargo-3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 103: Music Cargo-2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 102: Music Cargo-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0027::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 110: Music Stern-5
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 109: Music Stern-4
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0024::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 108: Music Stern-3
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 107: Music Stern-2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 106: Music Stern-1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 117: Music Aft-7
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 116: Music Aft-6
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 115: Music Aft-5
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 114: Music Aft-4
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 113: Music Aft-3
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 112: Music Aft-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 111: Music Aft-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0029::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Flame Ras Ambush
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjSetMovementType(Object_handles[81], 1);
      aObjSetMovementType(Object_handles[82], 1);
      aAIGoalGotoObject(Object_handles[81], qPlayerClosest(Object_handles[81], -1), 3, 4352, -1);
      aAIGoalGotoObject(Object_handles[82], qPlayerClosest(Object_handles[82], -1), 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 131: Streamin Audio Misc 1 - Trigger
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aSoundPlaySteaming("VoxL13GeneralA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 132: Streamin Audio Misc 2 - Trigger
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aSoundPlaySteaming("VoxL13GeneralB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_132 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_132++;
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
NEXT_ID		135

// UserType value blocks
$$UTYPE_VALS_START UserVar
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:EngineShutdown
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:PrimerSpew1
1:PrimerSpew2
2:PrimerSpew3
3:Condspew1
4:Condspew2
5:Condspew3
6:IntakeSpew
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:WindRampUp
1:WindRampDown
2:EngineMisfire
3:EngineShutdown
4:PestSpawn
5:CountRobots
6:Endlevel
7:ObjHudMessage1
8:ObjHudMessage2
9:ObjHudMessage3
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:Aft Matcen Trigger
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
Engine Core Aux Do
$$DOOR_LIST_END

$$OBJECT_LIST_START
Bay 62 FusableLink
Bay 62 Lance1
Bay 62 Lance2
Engine Spew 1
Engine Spew 2
Intake1
Intake2
Engine1
Engine2
Engine3
Engine Spew 3
Core Switch3
Core Switch2
Core Switch1
Q Door Eng
Lvl E Q Door
Leader Trooper
Eng Cam2
Eng Viewer
Primer Spew 1
Primer Spew 2
Primer Spew 3
Primer Fuse
Exhaust Cooler
Exhaust Patrol1
Exhaust Patrol2
Acc FloorSpew
Aft Well Turret1
Aft Well Commander
Aft Well Turret2
Aft Matcen Switch
Q Door
Q Door D deck
Q Door Exp Well
Q Door B Deck
Q Door C Acc
Q Door Acc1
Q Door Acc2
Q Door Core Acc
Q Door E Deck
Q Door 4way Acc
Q Door Acc0
Q Door A Deck
Q Door D Deck2
Bay62 Landing Door
62Banging
Core Link
Bay 36 Link
Main Deck Link
Bay 62 Data Link
AftMatcen Head Lin
Stern Data Arm
Bad White
Bad White Cage
Bad Tailbot
Bad Tailbot Cage
Air Spewer1
Air Spewer2
Floor Grid Spewer
Floor Spewer
Jeffrey1 Spew
Jeffry 2 Spew
Engine Core Aux Do
Jugg Storage
Recon Interface
ST Hall Monitor
Bay 36 Cam
Aft Well Cam
Saw U Cam
DeathStar Hall Cam
Main Hall Josh
A Deck Cam
Informant Scrubber
Aft Matcen Cam
Main Deck Cam
Core Cam
Bay 62 Matcen Fuse
Missile Exhaust
Spyhunter1
Sub Squid
Josh Act
FlameRas1
FlameRas2
ST Hall Monitor2
ST Hallmonitor3
ST HallMonitor4
DatShip1
Aft Matcen Hole
$$OBJECT_LIST_END

$$ROOM_LIST_START
Engine
Core Acc
Primer Chamber
$$ROOM_LIST_END

$$TRIGGER_LIST_START
Bay 62 PersonDr
Main Deck Ppl Door
Person Door2
Ppl Door Sub
Primer Damaged
CoreEffect
E Acc Matcen Trigge
Core Forcefield Acc
Missile1a
MHull-C
MHull-B
MHull-A
MHull-9
MHull-8
MHull-7
MHull-6
MHull-5
MHull-4
MHull-3
MHull-2
MHull-1
MCargo-4
MCargo-3
MCargo-2
MCargo-1
MStern-5
MStern-4
MStern-3
MStern-2
MStern-1
MAft-7
MAft-6
MAft-5
MAft-4
MAft-3
MAft-2
MAft-1
FlameRasTrigger
StreamAudio1
StreamAudio2
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbExplosionFarC
AmbDistantBangMany
Powerup pickup
HudMessage
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
stormtrooperred
stormtrooperwhite
stormtroopergreen
$$SPECNAME_LIST_END

$$PATH_LIST_START
AFTMatcen Cine
EndLevelCamPath
PlayerEndPath
Aft Matcen1
AftMatcenArt2
AftMatcenArt3
AftMatcenArt1
AftMatcenSwCam
LeaderCamPath
StormtrooperCine
CamIntroPath
PlayerIntroPath
Dat Ship1
$$PATH_LIST_END

$$MATCEN_LIST_START
Aft Matcen1
Aft Matcen2
Aft Matcen3
Bay 62 Matcen1
Bay 62 Matcen2
Bay 62 Matcen3
Bay 62 Matcen4
Cargo Acc Matcen
Aft Matcen4
$$MATCEN_LIST_END

$$GOAL_LIST_START
ShutdownEngineCore
Disable Aft Matcen
Destroy StormTrooper Leader
Eliminate Remaining StormTroopers
Reduce Infected Robot Threat
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL13StartLevel.osf
VoxL13GeneralA.osf
VoxL13GeneralB.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:119:Level Start - Initialize Variables
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Personell Acc Doors
        $$CHILD_BLOCK_START
        01:0:0
        02:1
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
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:100:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:8:PplDoors1:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Personell Acc Doors
        $$CHILD_BLOCK_START
        01:0:1
        02:1
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
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:100:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:8:PplDoors1:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Personell Acc Doors
        $$CHILD_BLOCK_START
        01:0:2
        02:1
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
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:100:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:8:PplDoors1:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Personell Acc Doors
        $$CHILD_BLOCK_START
        01:0:3
        02:1
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
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:100:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:8:PplDoors1:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Bay 62 Fusable Link
        $$CHILD_BLOCK_START
        01:1:0
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
                        10:8:Bay62Lance:Message
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Engine Wind Timer
        $$CHILD_BLOCK_START
        01:2:0
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        10:10:2:0:TimerID
                                        07:1:0
                                        10:10:0:1:TimerID
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:10:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.014000:X
                                10:6:0.095000:Y
                                10:6:-0.995000:Z
                                10:6:1.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
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
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:10:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.014000:X
                                10:6:0.095000:Y
                                10:6:-0.995000:Z
                                10:6:35.000000:Speed
                                10:6:0.500000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:4:-1:GunNum
                                10:10:0:6:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.200000:BlobLifetime
                                10:6:0.090000:BlobInterval
                                10:6:6.000000:SpewLife
                                10:6:100.000000:BlobSize
                                10:6:190.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:4:-1:GunNum
                                10:10:0:6:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.200000:BlobLifetime
                                10:6:0.090000:BlobInterval
                                10:6:6.000000:SpewLife
                                10:6:90.000000:BlobSize
                                10:6:190.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aMiscViewerShake
                                $$CHILD_BLOCK_START
                                10:6:70.000000:Amount
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
                                10:6:1.000000:BlobLifetime
                                10:6:0.900000:BlobInterval
                                10:6:1.200000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:100.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:6:SpewHandle
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
                                10:6:1.000000:BlobLifetime
                                10:6:1.000000:BlobInterval
                                10:6:1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:90.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:6:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:7:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:8:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:9:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                10:4:-1:GunNum
                                10:10:0:6:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.200000:BlobLifetime
                                10:6:0.090000:BlobInterval
                                10:6:6.000000:SpewLife
                                10:6:90.000000:BlobSize
                                10:6:190.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Core Shutdown Switch3
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
                03:1
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
                                                10:11:11:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EngineDown:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Core Shutdown Switch2
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
                03:1
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
                                                10:11:12:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EngineDown:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Core Shutdown Switch1
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
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
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
                                                10:11:12:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EngineDown:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Engine Malfunction Random Timer
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
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:500.000000:LowerLimit
                                10:6:650.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:NonPlayer Entry
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:NonPlayer Entry
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
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Engine Misfire Viewer Shake
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:2:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:16:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:EngineMisfire:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:17:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:SecondaryObjective:GameMessage
                        10:8:EngineTakover:HUDMessage
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:0:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:EngineShutdown
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        10:6:11.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:5:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:18:Object
                        10:6:10.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Create Primer Room Wind
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
                        10:2:2:Room
                        10:6:0.007000:X
                        10:6:0.287000:Y
                        10:6:-0.957000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:14.000000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:14.000000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:9.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Primer Room Trigger
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
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.082000:X
                        10:6:0.997000:Y
                        10:6:-0.022000:Z
                        10:6:5.000000:Speed
                        10:6:1.000000:Time
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:PrimerDamage
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
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:33.330002:DamageAmount
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PrimerDamage:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Coolant Sensor
        $$CHILD_BLOCK_START
        01:1:23
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
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:10:0:1:AIModeType
                        $$CHILD_BLOCK_END
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:10:0:6:AIModeType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:CoreRoom Microwave Effect
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
        04:0:0:15
                $$CHILD_BLOCK_START
                08:aObjDeform
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.300000:Amount
                        10:6:2.500000:Time
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:25:Green
                        10:4:0:Blue
                        10:8:CoreRads:Message
                        $$CHILD_BLOCK_END
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:5.000000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Acc Floor Spewer
        $$CHILD_BLOCK_START
        01:1:26
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Turret Controller
        $$CHILD_BLOCK_START
        01:1:27
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Turret Controller
        $$CHILD_BLOCK_START
        01:1:29
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Aft Matcen Goal
        $$CHILD_BLOCK_START
        01:1:30
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
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:0:Red
                        10:4:150:Green
                        10:4:255:Blue
                        10:8:LevelObjA:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetValues
                        $$CHILD_BLOCK_START
                        10:17:0:0:Matcen
                        10:4:0:MaxProduced
                        10:6:1.000000:Multiplier
                        10:4:1:MaxAlive
                        $$CHILD_BLOCK_END
                08:aMatcenSetValues
                        $$CHILD_BLOCK_START
                        10:17:0:1:Matcen
                        10:4:0:MaxProduced
                        10:6:1.000000:Multiplier
                        10:4:1:MaxAlive
                        $$CHILD_BLOCK_END
                08:aMatcenSetValues
                        $$CHILD_BLOCK_START
                        10:17:0:2:Matcen
                        10:4:0:MaxProduced
                        10:6:1.000000:Multiplier
                        10:4:1:MaxAlive
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:NonPlayer Entry
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:32
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:NonPlayer Entry
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
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:34
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:35
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:36
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:37
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:38
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:39
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:40
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:41
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:42
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:NonPlayer Entry
        $$CHILD_BLOCK_START
        01:1:43
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
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:NonPlayer Entry - 62 Acc Door
        $$CHILD_BLOCK_START
        01:1:44
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:45:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:NoEntry62:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Core Hall Data Link
        $$CHILD_BLOCK_START
        01:1:46
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:CoreInfo2:GameMessage
                        10:8:CoreInfo1:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Bay 36 Data Link
        $$CHILD_BLOCK_START
        01:1:47
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:BayInfoGame:GameMessage
                        10:8:BayInfoHud:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Main Deck Data Link
        $$CHILD_BLOCK_START
        01:1:48
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:MainDeckGame:GameMessage
                        10:8:MainDeckHud:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Bay 62 Data Link
        $$CHILD_BLOCK_START
        01:1:49
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:Bay62Game:GameMessage
                        10:8:Bay62Hud:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Aft Matcen Data Link
        $$CHILD_BLOCK_START
        01:1:50
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:ShipInfo2:GameMessage
                        10:8:ShipInfo1:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Stern Data Link
        $$CHILD_BLOCK_START
        01:1:51
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:AftMatcenCheck:Text
                        10:1:0:30:Target
                        10:6:8.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Bad White Cage Exists
        $$CHILD_BLOCK_START
        01:1:52
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:53:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Bad TailbotCage Exists
        $$CHILD_BLOCK_START
        01:1:54
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:53:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Bad TailbotCage Destroyed
        $$CHILD_BLOCK_START
        01:1:55
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Bad White Cage Destroyed
        $$CHILD_BLOCK_START
        01:1:53
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Air Spewers
        $$CHILD_BLOCK_START
        01:1:56
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
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Air Spewers
        $$CHILD_BLOCK_START
        01:1:57
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
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Air Spewers
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
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:Air Spewers
        $$CHILD_BLOCK_START
        01:1:59
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
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:Air Spewers
        $$CHILD_BLOCK_START
        01:1:60
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
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.900000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:14.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Air Spewers
        $$CHILD_BLOCK_START
        01:1:61
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
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.900000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:14.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Aux Core Access
        $$CHILD_BLOCK_START
        01:1:62
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
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:AuxCoreDoor:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Jugg AI
        $$CHILD_BLOCK_START
        01:1:63
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Stormtrooper Leader Death
        $$CHILD_BLOCK_START
        01:1:16
        02:4
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
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Cargo Acc Matcen
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:7:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Core Acc Forcefield
        $$CHILD_BLOCK_START
        01:0:7
        02:1
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CoreAccFF:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Count Robots
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qMathAddInt:Integer
                                        $$CHILD_BLOCK_START
                                        06:qMathAddInt:Integer1
                                                $$CHILD_BLOCK_START
                                                06:qObjCountTypeID:Integer1
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:ObjectType
                                                        10:13:0:ObjectIDName
                                                        $$CHILD_BLOCK_END
                                                06:qObjCountTypeID:Integer2
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:ObjectType
                                                        10:13:1:ObjectIDName
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        06:qObjCountTypeID:Integer2
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:ObjectType
                                                10:13:2:ObjectIDName
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
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
                        08:aShowColoredHUDMessage
                                $$CHILD_BLOCK_START
                                10:4:0:Red
                                10:4:255:Green
                                10:4:232:Blue
                                10:8:EndMission:Message
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:10.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:5:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:LevelStart Robot Count
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
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Picked Up Recon Interface
        $$CHILD_BLOCK_START
        01:1:64
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
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:GotReconInterface:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
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
00:124:Used Recon Interface
        $$CHILD_BLOCK_START
        01:1:64
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
                08:aShowHUDMessageI
                        $$CHILD_BLOCK_START
                        10:8:RobotCount:Message
                        06:qMathAddInt:Integer
                                $$CHILD_BLOCK_START
                                06:qMathAddInt:Integer1
                                        $$CHILD_BLOCK_START
                                        06:qObjCountTypeID:Integer1
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:ObjectType
                                                10:13:0:ObjectIDName
                                                $$CHILD_BLOCK_END
                                        06:qObjCountTypeID:Integer2
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:ObjectType
                                                10:13:2:ObjectIDName
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                06:qObjCountTypeID:Integer2
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:ObjectType
                                        10:13:1:ObjectIDName
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:End level Timer
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
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:1:CameraPath
                        10:16:2:PlayerPath
                        10:6:9.000000:Time
                        10:8:EndCine:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Aft Matcen Production
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Aft Matcen Path Controller
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:3:Path
                        10:15:4096:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:Aft Matcen Path Controller
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:4:Path
                        10:15:4096:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Aft Matcen Path Controller
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:5:Path
                        10:15:4096:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Aft Matcen Path Controller
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:8:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:6:Path
                        10:15:4096:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Start Level Objectives Messege
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:7:CameraPath
                        10:8:LevelObjtives1:Text
                        10:1:0:30:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Start Level Objectives Messege 2
        $$CHILD_BLOCK_START
        01:1:30
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:8:CameraPath
                        10:8:LevelObjtives2:Text
                        10:1:0:16:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Start Level Objectives Messege 3
        $$CHILD_BLOCK_START
        01:1:16
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:9:CameraPath
                        10:8:LevelObjtives3:Text
                        10:1:0:65:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:66
        02:11
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
        04:0:0:2
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt1:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt2:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:67
        02:11
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
        04:0:0:2
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt3:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt4:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:68
        02:11
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
        04:0:0:4
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt3:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt4:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:60
        02:11
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt3:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt4:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:69
        02:11
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
        04:0:0:2
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt1:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt3:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:70
        02:11
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
        04:0:0:2
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt3:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:71
        02:11
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt1:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt4:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:72
        02:11
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
        04:0:0:2
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt3:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:73
        02:11
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt5:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Leader Taunt Cam
        $$CHILD_BLOCK_START
        01:1:74
        02:11
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt1:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaderTaunt2:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:IntroLevel
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:10:CameraPath
                        10:8:IntroText:Text
                        10:1:0:75:TotallyNotUsedTarget
                        10:16:11:PlayerPath
                        10:6:20.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Bay  62 Matcen Fuse
        $$CHILD_BLOCK_START
        01:1:76
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Bay62Fuse:Message
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Missile Smoke
        $$CHILD_BLOCK_START
        01:0:8
        02:1
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:2.200000:BlobSize
                        10:6:90.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:SpyHunter_Plead
        $$CHILD_BLOCK_START
        01:1:78
        02:11
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
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:AIModeType
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SpyPlead:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:SpyHunter_Stay
        $$CHILD_BLOCK_START
        01:1:78
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Spy Hunter Off
        $$CHILD_BLOCK_START
        01:1:78
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Sub Squid Off
        $$CHILD_BLOCK_START
        01:1:79
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Sub Squid
        $$CHILD_BLOCK_START
        01:1:79
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Josh Attack
        $$CHILD_BLOCK_START
        01:1:80
        02:11
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
00:88:Music Intro Init
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
00:101:Music Hull-C
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
00:100:Music Hull-B
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
00:99:Music Hull-A
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
00:98:Music Hull-9
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
00:96:Music Hull-8
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
00:97:Music Hull-7
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
00:95:Music Hull-6
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
00:94:Music Hull-5
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
00:93:Music Hull-4
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
00:92:Music Hull-3
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
00:91:Music Hull-2
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
00:90:Music Hull-1
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
00:105:Music Cargo-4
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
00:104:Music Cargo-3
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:Music Cargo-2
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:Music Cargo-1
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Music Stern-5
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:Music Stern-4
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:Music Stern-3
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:Music Stern-2
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:Music Stern-1
        $$CHILD_BLOCK_START
        01:0:29
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
00:117:Music Aft-7
        $$CHILD_BLOCK_START
        01:0:30
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
00:116:Music Aft-6
        $$CHILD_BLOCK_START
        01:0:31
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
00:115:Music Aft-5
        $$CHILD_BLOCK_START
        01:0:32
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
00:114:Music Aft-4
        $$CHILD_BLOCK_START
        01:0:33
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
00:113:Music Aft-3
        $$CHILD_BLOCK_START
        01:0:34
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
00:112:Music Aft-2
        $$CHILD_BLOCK_START
        01:0:35
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
00:111:Music Aft-1
        $$CHILD_BLOCK_START
        01:0:36
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
00:65:Flame Ras Ambush
        $$CHILD_BLOCK_START
        01:0:37
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        06:qPlayerClosest:Target
                                $$CHILD_BLOCK_START
                                10:1:0:81:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        06:qPlayerClosest:Target
                                $$CHILD_BLOCK_START
                                10:1:0:82:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:133:FlameRas Created
        $$CHILD_BLOCK_START
        01:1:81
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:FlameRas Created
        $$CHILD_BLOCK_START
        01:1:82
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:ST Monitor - Sleep
        $$CHILD_BLOCK_START
        01:1:65
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:ST Monitor2 - Sleep
        $$CHILD_BLOCK_START
        01:1:83
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:ST Monitor3 - Sleep
        $$CHILD_BLOCK_START
        01:1:84
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:ST Monitor4 - Sleep
        $$CHILD_BLOCK_START
        01:1:85
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:ST Monitor - Awaken
        $$CHILD_BLOCK_START
        01:1:65
        02:11
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:ST Monitor2 - Awaken
        $$CHILD_BLOCK_START
        01:1:83
        02:11
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:ST Monitor3 - Awaken
        $$CHILD_BLOCK_START
        01:1:84
        02:11
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:ST Monitor4 - Awaken
        $$CHILD_BLOCK_START
        01:1:85
        02:11
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:DatShip1 --  Path On Creation
        $$CHILD_BLOCK_START
        01:1:86
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:86:Object
                        10:16:12:Path
                        10:4:1:FirstNode
                        10:4:19:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:131:Streamin Audio Misc 1 - Trigger
        $$CHILD_BLOCK_START
        01:0:38
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:132:Streamin Audio Misc 2 - Trigger
        $$CHILD_BLOCK_START
        01:0:39
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:134:Make Invisible PowerUp Invisible
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
                        10:1:0:87:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
