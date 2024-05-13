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
// Filename:	Merc1.cpp
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

#define ID_CUSTOM_OBJECT_2027 0x001
#define ID_CUSTOM_OBJECT_0820 0x002
#define ID_CUSTOM_OBJECT_0831 0x003
#define ID_CUSTOM_OBJECT_0832 0x004
#define ID_CUSTOM_OBJECT_0836 0x005
#define ID_CUSTOM_OBJECT_0888 0x006
#define ID_CUSTOM_OBJECT_0887 0x007
#define ID_CUSTOM_OBJECT_0886 0x008
#define ID_CUSTOM_OBJECT_182A 0x009
#define ID_CUSTOM_OBJECT_088A 0x00a
#define ID_CUSTOM_OBJECT_0889 0x00b
#define ID_CUSTOM_OBJECT_188C 0x00c
#define ID_CUSTOM_OBJECT_0885 0x00d
#define ID_CUSTOM_OBJECT_096D 0x00e
#define ID_CUSTOM_OBJECT_0877 0x00f
#define ID_CUSTOM_OBJECT_0878 0x010
#define ID_CUSTOM_OBJECT_0879 0x011
#define ID_CUSTOM_OBJECT_1171 0x012
#define ID_CUSTOM_OBJECT_087A 0x013
#define ID_CUSTOM_OBJECT_087B 0x014
#define ID_CUSTOM_OBJECT_087C 0x015
#define ID_CUSTOM_OBJECT_087D 0x016
#define ID_CUSTOM_OBJECT_1170 0x017
#define ID_CUSTOM_OBJECT_0988 0x018
#define ID_CUSTOM_OBJECT_0981 0x019
#define ID_CUSTOM_OBJECT_0980 0x01a
#define ID_CUSTOM_OBJECT_097F 0x01b
#define ID_CUSTOM_OBJECT_097E 0x01c
#define ID_CUSTOM_OBJECT_097D 0x01d
#define ID_CUSTOM_OBJECT_097C 0x01e
#define ID_CUSTOM_OBJECT_117B 0x01f
#define ID_CUSTOM_OBJECT_097A 0x020
#define ID_CUSTOM_OBJECT_1984 0x021
#define ID_CUSTOM_OBJECT_0875 0x022
#define ID_CUSTOM_OBJECT_0865 0x023
#define ID_CUSTOM_OBJECT_0864 0x024
#define ID_CUSTOM_OBJECT_0863 0x025
#define ID_CUSTOM_OBJECT_0862 0x026
#define ID_CUSTOM_OBJECT_08A1 0x027
#define ID_CUSTOM_OBJECT_08A0 0x028
#define ID_CUSTOM_OBJECT_089F 0x029
#define ID_CUSTOM_OBJECT_109E 0x02a
#define ID_CUSTOM_OBJECT_109C 0x02b
#define ID_CUSTOM_OBJECT_08AE 0x02c
#define ID_CUSTOM_OBJECT_18A6 0x02d
#define ID_CUSTOM_OBJECT_18A5 0x02e
#define ID_CUSTOM_OBJECT_18A4 0x02f
#define ID_CUSTOM_OBJECT_18A7 0x030
#define ID_CUSTOM_OBJECT_18A9 0x031
#define ID_CUSTOM_OBJECT_20A3 0x032
#define ID_CUSTOM_OBJECT_28A2 0x033
#define ID_CUSTOM_OBJECT_18A8 0x034
#define ID_CUSTOM_OBJECT_08DA 0x035
#define ID_CUSTOM_OBJECT_08D9 0x036
#define ID_CUSTOM_OBJECT_08D8 0x037
#define ID_CUSTOM_OBJECT_08D7 0x038
#define ID_CUSTOM_OBJECT_08D6 0x039
#define ID_CUSTOM_OBJECT_08D5 0x03a
#define ID_CUSTOM_OBJECT_08D4 0x03b
#define ID_CUSTOM_OBJECT_08D3 0x03c
#define ID_CUSTOM_OBJECT_08D2 0x03d
#define ID_CUSTOM_OBJECT_08D1 0x03e
#define ID_CUSTOM_OBJECT_08D0 0x03f
#define ID_CUSTOM_OBJECT_08CF 0x040
#define ID_CUSTOM_OBJECT_105C 0x041
#define ID_CUSTOM_OBJECT_2059 0x042
#define ID_CUSTOM_OBJECT_0858 0x043
#define ID_CUSTOM_OBJECT_0857 0x044
#define ID_CUSTOM_OBJECT_1030 0x045
#define ID_CUSTOM_OBJECT_402F 0x046
#define ID_CUSTOM_OBJECT_1871 0x047
#define ID_CUSTOM_OBJECT_091A 0x048
#define ID_CUSTOM_OBJECT_0919 0x049
#define ID_CUSTOM_OBJECT_0918 0x04a
#define ID_CUSTOM_OBJECT_0917 0x04b
#define ID_CUSTOM_OBJECT_0925 0x04c
#define ID_CUSTOM_OBJECT_0924 0x04d
#define ID_CUSTOM_OBJECT_0923 0x04e
#define ID_CUSTOM_OBJECT_0922 0x04f
#define ID_CUSTOM_OBJECT_0921 0x050
#define ID_CUSTOM_OBJECT_1120 0x051
#define ID_CUSTOM_OBJECT_111F 0x052
#define ID_CUSTOM_OBJECT_111E 0x053
#define ID_CUSTOM_OBJECT_112E 0x054
#define ID_CUSTOM_OBJECT_0932 0x055
#define ID_CUSTOM_OBJECT_0931 0x056
#define ID_CUSTOM_OBJECT_080F 0x057
#define ID_CUSTOM_OBJECT_0967 0x058
#define ID_CUSTOM_OBJECT_0966 0x059
#define ID_CUSTOM_OBJECT_0809 0x05a

#define ID_TRIGGER_000B 0x05b
#define ID_TRIGGER_000A 0x05c
#define ID_TRIGGER_0007 0x05d
#define ID_TRIGGER_0006 0x05e
#define ID_TRIGGER_0004 0x05f
#define ID_TRIGGER_0003 0x060
#define ID_TRIGGER_0001 0x061
#define ID_TRIGGER_000D 0x062
#define ID_TRIGGER_000C 0x063
#define ID_TRIGGER_0009 0x064
#define ID_TRIGGER_0008 0x065
#define ID_TRIGGER_0005 0x066
#define ID_TRIGGER_0002 0x067
#define ID_TRIGGER_0000 0x068
#define ID_TRIGGER_0013 0x069
#define ID_TRIGGER_0012 0x06a
#define ID_TRIGGER_000F 0x06b
#define ID_TRIGGER_000E 0x06c
#define ID_TRIGGER_0011 0x06d
#define ID_TRIGGER_0010 0x06e
#define ID_TRIGGER_0014 0x06f
#define ID_TRIGGER_0015 0x070

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

class CustomObjectScript_2027 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0820 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0831 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0832 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0836 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0888 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0887 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0886 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_182A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_088A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0889 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_188C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0885 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0877 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0878 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0879 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1171 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1170 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0988 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0981 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0980 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_117B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1984 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0875 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0865 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0864 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0863 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0862 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_089F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_109E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_109C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08AE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20A3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_28A2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08DA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08CF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_105C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2059 : public BaseScript {
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

class CustomObjectScript_1030 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_402F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1871 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_091A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0919 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0918 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0917 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0925 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0924 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0923 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0922 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0921 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1120 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_111F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_111E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_112E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0932 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0931 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0967 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0966 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0809 : public BaseScript {
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

class TriggerScript_0007 : public BaseScript {
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

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0001 : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
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

class TriggerScript_000E : public BaseScript {
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

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_194 = 0;
static int ScriptActionCtr_209 = 0;
static int ScriptActionCtr_195 = 0;
static int ScriptActionCtr_193 = 0;
static int ScriptActionCtr_199 = 0;
static int ScriptActionCtr_192 = 0;
static int ScriptActionCtr_191 = 0;
static int ScriptActionCtr_190 = 0;
static int ScriptActionCtr_196 = 0;
static int ScriptActionCtr_171 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_169 = 0;
static int ScriptActionCtr_168 = 0;
static int ScriptActionCtr_167 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_170 = 0;
static int ScriptActionCtr_179 = 0;
static int ScriptActionCtr_178 = 0;
static int ScriptActionCtr_177 = 0;
static int ScriptActionCtr_176 = 0;
static int ScriptActionCtr_175 = 0;
static int ScriptActionCtr_174 = 0;
static int ScriptActionCtr_173 = 0;
static int ScriptActionCtr_172 = 0;
static int ScriptActionCtr_180 = 0;
static int ScriptActionCtr_189 = 0;
static int ScriptActionCtr_188 = 0;
static int ScriptActionCtr_187 = 0;
static int ScriptActionCtr_186 = 0;
static int ScriptActionCtr_185 = 0;
static int ScriptActionCtr_184 = 0;
static int ScriptActionCtr_183 = 0;
static int ScriptActionCtr_182 = 0;
static int ScriptActionCtr_181 = 0;
static int ScriptActionCtr_198 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_210 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_125 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_129 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_130 = 0;
static int ScriptActionCtr_138 = 0;
static int ScriptActionCtr_137 = 0;
static int ScriptActionCtr_136 = 0;
static int ScriptActionCtr_131 = 0;
static int ScriptActionCtr_135 = 0;
static int ScriptActionCtr_134 = 0;
static int ScriptActionCtr_133 = 0;
static int ScriptActionCtr_132 = 0;
static int ScriptActionCtr_141 = 0;
static int ScriptActionCtr_156 = 0;
static int ScriptActionCtr_155 = 0;
static int ScriptActionCtr_154 = 0;
static int ScriptActionCtr_153 = 0;
static int ScriptActionCtr_152 = 0;
static int ScriptActionCtr_151 = 0;
static int ScriptActionCtr_150 = 0;
static int ScriptActionCtr_139 = 0;
static int ScriptActionCtr_142 = 0;
static int ScriptActionCtr_158 = 0;
static int ScriptActionCtr_157 = 0;
static int ScriptActionCtr_149 = 0;
static int ScriptActionCtr_148 = 0;
static int ScriptActionCtr_147 = 0;
static int ScriptActionCtr_146 = 0;
static int ScriptActionCtr_145 = 0;
static int ScriptActionCtr_144 = 0;
static int ScriptActionCtr_143 = 0;
static int ScriptActionCtr_140 = 0;
static int ScriptActionCtr_159 = 0;
static int ScriptActionCtr_160 = 0;
static int ScriptActionCtr_161 = 0;
static int ScriptActionCtr_162 = 0;
static int ScriptActionCtr_164 = 0;
static int ScriptActionCtr_163 = 0;
static int ScriptActionCtr_166 = 0;
static int ScriptActionCtr_165 = 0;
static int ScriptActionCtr_197 = 0;
static int ScriptActionCtr_200 = 0;
static int ScriptActionCtr_207 = 0;
static int ScriptActionCtr_206 = 0;
static int ScriptActionCtr_205 = 0;
static int ScriptActionCtr_204 = 0;
static int ScriptActionCtr_203 = 0;
static int ScriptActionCtr_202 = 0;
static int ScriptActionCtr_201 = 0;
static int ScriptActionCtr_208 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_194 = 0;
  ScriptActionCtr_209 = 0;
  ScriptActionCtr_195 = 0;
  ScriptActionCtr_193 = 0;
  ScriptActionCtr_199 = 0;
  ScriptActionCtr_192 = 0;
  ScriptActionCtr_191 = 0;
  ScriptActionCtr_190 = 0;
  ScriptActionCtr_196 = 0;
  ScriptActionCtr_171 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_169 = 0;
  ScriptActionCtr_168 = 0;
  ScriptActionCtr_167 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_170 = 0;
  ScriptActionCtr_179 = 0;
  ScriptActionCtr_178 = 0;
  ScriptActionCtr_177 = 0;
  ScriptActionCtr_176 = 0;
  ScriptActionCtr_175 = 0;
  ScriptActionCtr_174 = 0;
  ScriptActionCtr_173 = 0;
  ScriptActionCtr_172 = 0;
  ScriptActionCtr_180 = 0;
  ScriptActionCtr_189 = 0;
  ScriptActionCtr_188 = 0;
  ScriptActionCtr_187 = 0;
  ScriptActionCtr_186 = 0;
  ScriptActionCtr_185 = 0;
  ScriptActionCtr_184 = 0;
  ScriptActionCtr_183 = 0;
  ScriptActionCtr_182 = 0;
  ScriptActionCtr_181 = 0;
  ScriptActionCtr_198 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_210 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_125 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_129 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_130 = 0;
  ScriptActionCtr_138 = 0;
  ScriptActionCtr_137 = 0;
  ScriptActionCtr_136 = 0;
  ScriptActionCtr_131 = 0;
  ScriptActionCtr_135 = 0;
  ScriptActionCtr_134 = 0;
  ScriptActionCtr_133 = 0;
  ScriptActionCtr_132 = 0;
  ScriptActionCtr_141 = 0;
  ScriptActionCtr_156 = 0;
  ScriptActionCtr_155 = 0;
  ScriptActionCtr_154 = 0;
  ScriptActionCtr_153 = 0;
  ScriptActionCtr_152 = 0;
  ScriptActionCtr_151 = 0;
  ScriptActionCtr_150 = 0;
  ScriptActionCtr_139 = 0;
  ScriptActionCtr_142 = 0;
  ScriptActionCtr_158 = 0;
  ScriptActionCtr_157 = 0;
  ScriptActionCtr_149 = 0;
  ScriptActionCtr_148 = 0;
  ScriptActionCtr_147 = 0;
  ScriptActionCtr_146 = 0;
  ScriptActionCtr_145 = 0;
  ScriptActionCtr_144 = 0;
  ScriptActionCtr_143 = 0;
  ScriptActionCtr_140 = 0;
  ScriptActionCtr_159 = 0;
  ScriptActionCtr_160 = 0;
  ScriptActionCtr_161 = 0;
  ScriptActionCtr_162 = 0;
  ScriptActionCtr_164 = 0;
  ScriptActionCtr_163 = 0;
  ScriptActionCtr_166 = 0;
  ScriptActionCtr_165 = 0;
  ScriptActionCtr_197 = 0;
  ScriptActionCtr_200 = 0;
  ScriptActionCtr_207 = 0;
  ScriptActionCtr_206 = 0;
  ScriptActionCtr_205 = 0;
  ScriptActionCtr_204 = 0;
  ScriptActionCtr_203 = 0;
  ScriptActionCtr_202 = 0;
  ScriptActionCtr_201 = 0;
  ScriptActionCtr_208 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_194, file_ptr);
  File_WriteInt(ScriptActionCtr_209, file_ptr);
  File_WriteInt(ScriptActionCtr_195, file_ptr);
  File_WriteInt(ScriptActionCtr_193, file_ptr);
  File_WriteInt(ScriptActionCtr_199, file_ptr);
  File_WriteInt(ScriptActionCtr_192, file_ptr);
  File_WriteInt(ScriptActionCtr_191, file_ptr);
  File_WriteInt(ScriptActionCtr_190, file_ptr);
  File_WriteInt(ScriptActionCtr_196, file_ptr);
  File_WriteInt(ScriptActionCtr_171, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_169, file_ptr);
  File_WriteInt(ScriptActionCtr_168, file_ptr);
  File_WriteInt(ScriptActionCtr_167, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_170, file_ptr);
  File_WriteInt(ScriptActionCtr_179, file_ptr);
  File_WriteInt(ScriptActionCtr_178, file_ptr);
  File_WriteInt(ScriptActionCtr_177, file_ptr);
  File_WriteInt(ScriptActionCtr_176, file_ptr);
  File_WriteInt(ScriptActionCtr_175, file_ptr);
  File_WriteInt(ScriptActionCtr_174, file_ptr);
  File_WriteInt(ScriptActionCtr_173, file_ptr);
  File_WriteInt(ScriptActionCtr_172, file_ptr);
  File_WriteInt(ScriptActionCtr_180, file_ptr);
  File_WriteInt(ScriptActionCtr_189, file_ptr);
  File_WriteInt(ScriptActionCtr_188, file_ptr);
  File_WriteInt(ScriptActionCtr_187, file_ptr);
  File_WriteInt(ScriptActionCtr_186, file_ptr);
  File_WriteInt(ScriptActionCtr_185, file_ptr);
  File_WriteInt(ScriptActionCtr_184, file_ptr);
  File_WriteInt(ScriptActionCtr_183, file_ptr);
  File_WriteInt(ScriptActionCtr_182, file_ptr);
  File_WriteInt(ScriptActionCtr_181, file_ptr);
  File_WriteInt(ScriptActionCtr_198, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_210, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_129, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_130, file_ptr);
  File_WriteInt(ScriptActionCtr_138, file_ptr);
  File_WriteInt(ScriptActionCtr_137, file_ptr);
  File_WriteInt(ScriptActionCtr_136, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
  File_WriteInt(ScriptActionCtr_135, file_ptr);
  File_WriteInt(ScriptActionCtr_134, file_ptr);
  File_WriteInt(ScriptActionCtr_133, file_ptr);
  File_WriteInt(ScriptActionCtr_132, file_ptr);
  File_WriteInt(ScriptActionCtr_141, file_ptr);
  File_WriteInt(ScriptActionCtr_156, file_ptr);
  File_WriteInt(ScriptActionCtr_155, file_ptr);
  File_WriteInt(ScriptActionCtr_154, file_ptr);
  File_WriteInt(ScriptActionCtr_153, file_ptr);
  File_WriteInt(ScriptActionCtr_152, file_ptr);
  File_WriteInt(ScriptActionCtr_151, file_ptr);
  File_WriteInt(ScriptActionCtr_150, file_ptr);
  File_WriteInt(ScriptActionCtr_139, file_ptr);
  File_WriteInt(ScriptActionCtr_142, file_ptr);
  File_WriteInt(ScriptActionCtr_158, file_ptr);
  File_WriteInt(ScriptActionCtr_157, file_ptr);
  File_WriteInt(ScriptActionCtr_149, file_ptr);
  File_WriteInt(ScriptActionCtr_148, file_ptr);
  File_WriteInt(ScriptActionCtr_147, file_ptr);
  File_WriteInt(ScriptActionCtr_146, file_ptr);
  File_WriteInt(ScriptActionCtr_145, file_ptr);
  File_WriteInt(ScriptActionCtr_144, file_ptr);
  File_WriteInt(ScriptActionCtr_143, file_ptr);
  File_WriteInt(ScriptActionCtr_140, file_ptr);
  File_WriteInt(ScriptActionCtr_159, file_ptr);
  File_WriteInt(ScriptActionCtr_160, file_ptr);
  File_WriteInt(ScriptActionCtr_161, file_ptr);
  File_WriteInt(ScriptActionCtr_162, file_ptr);
  File_WriteInt(ScriptActionCtr_164, file_ptr);
  File_WriteInt(ScriptActionCtr_163, file_ptr);
  File_WriteInt(ScriptActionCtr_166, file_ptr);
  File_WriteInt(ScriptActionCtr_165, file_ptr);
  File_WriteInt(ScriptActionCtr_197, file_ptr);
  File_WriteInt(ScriptActionCtr_200, file_ptr);
  File_WriteInt(ScriptActionCtr_207, file_ptr);
  File_WriteInt(ScriptActionCtr_206, file_ptr);
  File_WriteInt(ScriptActionCtr_205, file_ptr);
  File_WriteInt(ScriptActionCtr_204, file_ptr);
  File_WriteInt(ScriptActionCtr_203, file_ptr);
  File_WriteInt(ScriptActionCtr_202, file_ptr);
  File_WriteInt(ScriptActionCtr_201, file_ptr);
  File_WriteInt(ScriptActionCtr_208, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_194 = File_ReadInt(file_ptr);
  ScriptActionCtr_209 = File_ReadInt(file_ptr);
  ScriptActionCtr_195 = File_ReadInt(file_ptr);
  ScriptActionCtr_193 = File_ReadInt(file_ptr);
  ScriptActionCtr_199 = File_ReadInt(file_ptr);
  ScriptActionCtr_192 = File_ReadInt(file_ptr);
  ScriptActionCtr_191 = File_ReadInt(file_ptr);
  ScriptActionCtr_190 = File_ReadInt(file_ptr);
  ScriptActionCtr_196 = File_ReadInt(file_ptr);
  ScriptActionCtr_171 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_169 = File_ReadInt(file_ptr);
  ScriptActionCtr_168 = File_ReadInt(file_ptr);
  ScriptActionCtr_167 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_170 = File_ReadInt(file_ptr);
  ScriptActionCtr_179 = File_ReadInt(file_ptr);
  ScriptActionCtr_178 = File_ReadInt(file_ptr);
  ScriptActionCtr_177 = File_ReadInt(file_ptr);
  ScriptActionCtr_176 = File_ReadInt(file_ptr);
  ScriptActionCtr_175 = File_ReadInt(file_ptr);
  ScriptActionCtr_174 = File_ReadInt(file_ptr);
  ScriptActionCtr_173 = File_ReadInt(file_ptr);
  ScriptActionCtr_172 = File_ReadInt(file_ptr);
  ScriptActionCtr_180 = File_ReadInt(file_ptr);
  ScriptActionCtr_189 = File_ReadInt(file_ptr);
  ScriptActionCtr_188 = File_ReadInt(file_ptr);
  ScriptActionCtr_187 = File_ReadInt(file_ptr);
  ScriptActionCtr_186 = File_ReadInt(file_ptr);
  ScriptActionCtr_185 = File_ReadInt(file_ptr);
  ScriptActionCtr_184 = File_ReadInt(file_ptr);
  ScriptActionCtr_183 = File_ReadInt(file_ptr);
  ScriptActionCtr_182 = File_ReadInt(file_ptr);
  ScriptActionCtr_181 = File_ReadInt(file_ptr);
  ScriptActionCtr_198 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_210 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_129 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_130 = File_ReadInt(file_ptr);
  ScriptActionCtr_138 = File_ReadInt(file_ptr);
  ScriptActionCtr_137 = File_ReadInt(file_ptr);
  ScriptActionCtr_136 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
  ScriptActionCtr_135 = File_ReadInt(file_ptr);
  ScriptActionCtr_134 = File_ReadInt(file_ptr);
  ScriptActionCtr_133 = File_ReadInt(file_ptr);
  ScriptActionCtr_132 = File_ReadInt(file_ptr);
  ScriptActionCtr_141 = File_ReadInt(file_ptr);
  ScriptActionCtr_156 = File_ReadInt(file_ptr);
  ScriptActionCtr_155 = File_ReadInt(file_ptr);
  ScriptActionCtr_154 = File_ReadInt(file_ptr);
  ScriptActionCtr_153 = File_ReadInt(file_ptr);
  ScriptActionCtr_152 = File_ReadInt(file_ptr);
  ScriptActionCtr_151 = File_ReadInt(file_ptr);
  ScriptActionCtr_150 = File_ReadInt(file_ptr);
  ScriptActionCtr_139 = File_ReadInt(file_ptr);
  ScriptActionCtr_142 = File_ReadInt(file_ptr);
  ScriptActionCtr_158 = File_ReadInt(file_ptr);
  ScriptActionCtr_157 = File_ReadInt(file_ptr);
  ScriptActionCtr_149 = File_ReadInt(file_ptr);
  ScriptActionCtr_148 = File_ReadInt(file_ptr);
  ScriptActionCtr_147 = File_ReadInt(file_ptr);
  ScriptActionCtr_146 = File_ReadInt(file_ptr);
  ScriptActionCtr_145 = File_ReadInt(file_ptr);
  ScriptActionCtr_144 = File_ReadInt(file_ptr);
  ScriptActionCtr_143 = File_ReadInt(file_ptr);
  ScriptActionCtr_140 = File_ReadInt(file_ptr);
  ScriptActionCtr_159 = File_ReadInt(file_ptr);
  ScriptActionCtr_160 = File_ReadInt(file_ptr);
  ScriptActionCtr_161 = File_ReadInt(file_ptr);
  ScriptActionCtr_162 = File_ReadInt(file_ptr);
  ScriptActionCtr_164 = File_ReadInt(file_ptr);
  ScriptActionCtr_163 = File_ReadInt(file_ptr);
  ScriptActionCtr_166 = File_ReadInt(file_ptr);
  ScriptActionCtr_165 = File_ReadInt(file_ptr);
  ScriptActionCtr_197 = File_ReadInt(file_ptr);
  ScriptActionCtr_200 = File_ReadInt(file_ptr);
  ScriptActionCtr_207 = File_ReadInt(file_ptr);
  ScriptActionCtr_206 = File_ReadInt(file_ptr);
  ScriptActionCtr_205 = File_ReadInt(file_ptr);
  ScriptActionCtr_204 = File_ReadInt(file_ptr);
  ScriptActionCtr_203 = File_ReadInt(file_ptr);
  ScriptActionCtr_202 = File_ReadInt(file_ptr);
  ScriptActionCtr_201 = File_ReadInt(file_ptr);
  ScriptActionCtr_208 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
// Got from Nate

/*
$$ENUM Region
0:Intro
1:City
2:Maintenence
3:Industrial
4:PreReactor
5:Reactor
6:FinalCountdown
$$END
*/

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

#define NUM_DOOR_NAMES 13
static const char *const Door_names[NUM_DOOR_NAMES] = {
    "EntranceDoor", "BlastDoor1",  "BlastDoor4",  "AmbushSide1", "AmbushSide2", "AmbushDoor", "CityDoor1",
    "CityDoor2",    "CityUp1Door", "CityUp2Door", "FirstDoor1",  "FirstDoor2",  "ReakTop"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 277
static const char *const Object_names[NUM_OBJECT_NAMES] = {"BumPipe1",
                                                           "BumPipe2",
                                                           "BumPipe3",
                                                           "BumPipe4",
                                                           "EPipe1",
                                                           "EPipe2",
                                                           "EPipe3",
                                                           "EPipe4",
                                                           "HSLast",
                                                           "HSCity1",
                                                           "HSCity2",
                                                           "HSCity3",
                                                           "HSCity4",
                                                           "HSCity5",
                                                           "HSCity6",
                                                           "CityE4",
                                                           "CityE3",
                                                           "CityE2",
                                                           "CityE1",
                                                           "Stack5",
                                                           "Stack6",
                                                           "Stack7",
                                                           "Stack4",
                                                           "Stack3",
                                                           "Stack2",
                                                           "Stack1",
                                                           "Stack8",
                                                           "WindSpew1",
                                                           "WindSpew2",
                                                           "WindSpew3",
                                                           "WindSpew4",
                                                           "Phoenix2",
                                                           "Phoenix1",
                                                           "Assault-1",
                                                           "Assault-2",
                                                           "Assault-3",
                                                           "CameraJupiterTarge",
                                                           "SlideLeftTarget",
                                                           "SlideLeftHighTarge",
                                                           "EDTop1",
                                                           "EDTop2",
                                                           "EDTop3",
                                                           "EDTop4",
                                                           "SmokerIntro1",
                                                           "SmokerIntro2",
                                                           "FinalSlideTarget",
                                                           "EntranceDoor",
                                                           "EDBottom1",
                                                           "EDBottom2",
                                                           "EDBottom3",
                                                           "EDBottom4",
                                                           "DoorOpenTarget",
                                                           "FollowCEDTarget",
                                                           "SmokerIntro3",
                                                           "SmokerIntro4",
                                                           "NodeNRG1",
                                                           "NodeNRG2",
                                                           "NRGhost1",
                                                           "NRGhost2",
                                                           "NRGBeam2",
                                                           "NRGBeam1",
                                                           "NRGSmoke12",
                                                           "NRGSmoke11",
                                                           "Vaporizer1",
                                                           "VaporizerPoint1",
                                                           "NRGSmoke21",
                                                           "NRGSmoke22",
                                                           "Vaporizer2",
                                                           "VaporizerNode2",
                                                           "NNode6",
                                                           "NSmoke6",
                                                           "NNode5",
                                                           "NSmoke5",
                                                           "NNode4",
                                                           "NSmoke4",
                                                           "NNode3",
                                                           "NSmoke3",
                                                           "NNode2",
                                                           "NSmoke2",
                                                           "NNode1",
                                                           "NSmoke1",
                                                           "MainReakNode",
                                                           "NMain",
                                                           "BombInventory",
                                                           "EmergLight1",
                                                           "EmergLight2",
                                                           "BombRender",
                                                           "EFLifter1",
                                                           "EF3Tail1",
                                                           "EF3Tail2",
                                                           "GTarget1",
                                                           "GTarget2",
                                                           "GTarget3",
                                                           "GTarget4",
                                                           "ExplodeTarget1",
                                                           "EFSpew1",
                                                           "EFSpew2",
                                                           "NodeFire1",
                                                           "NodeFire6",
                                                           "NodeFire2",
                                                           "NodeFire5",
                                                           "NodeFire3",
                                                           "NodeFire4",
                                                           "AELow8",
                                                           "AELow7",
                                                           "AELow6",
                                                           "AELow5",
                                                           "AELow1",
                                                           "AELow2",
                                                           "AELow3",
                                                           "EFLifterSpot",
                                                           "ExplodeTarget2",
                                                           "EFB-C",
                                                           "LoThresh6",
                                                           "EFB-B",
                                                           "LoThresh1",
                                                           "LoThresh2",
                                                           "LoThresh3",
                                                           "LoThresh4",
                                                           "EFB-A",
                                                           "AmbushSmoke1",
                                                           "AmbushSmoke2",
                                                           "LoThresh8",
                                                           "LoThresh7",
                                                           "LoThresh5",
                                                           "EFB-5",
                                                           "EFB-6",
                                                           "EFB-7",
                                                           "EFB-8",
                                                           "EF3-D",
                                                           "EF3-9",
                                                           "EF3-8",
                                                           "EF3-7",
                                                           "EF3-6",
                                                           "EF3-5",
                                                           "EF3-4",
                                                           "EF3-3",
                                                           "EF3-2",
                                                           "EF3-1",
                                                           "EFTarget3",
                                                           "EF3-A",
                                                           "EF3-B",
                                                           "EF3-C",
                                                           "WDLightXXX",
                                                           "EF4Smoke1",
                                                           "EF4Smoke2",
                                                           "EF4Smoke3",
                                                           "EF4Smoke4",
                                                           "LNipple5",
                                                           "LNBall5",
                                                           "LNipple4",
                                                           "LNBall4",
                                                           "LNipple3",
                                                           "LNBall3",
                                                           "LNipple2",
                                                           "LNBall2",
                                                           "LNipple1",
                                                           "LNBall1",
                                                           "AMNode2",
                                                           "AMNode1",
                                                           "AELow4",
                                                           "CoolS4",
                                                           "CoolS3",
                                                           "CoolS2",
                                                           "CoolS1",
                                                           "HangSwitch",
                                                           "HangSmoke1",
                                                           "HangSmoke2",
                                                           "Hang8",
                                                           "Hang7",
                                                           "Hang6",
                                                           "Hang5",
                                                           "Hang4",
                                                           "Hang3",
                                                           "Hang2",
                                                           "Hang1",
                                                           "NB8",
                                                           "NB7",
                                                           "NB6",
                                                           "NB5",
                                                           "NB4",
                                                           "NB3",
                                                           "NB2",
                                                           "NB1",
                                                           "CityMoveF4",
                                                           "CityFMove3",
                                                           "CityFMove2",
                                                           "CityFMove1",
                                                           "CityEMove3",
                                                           "CityEMove2",
                                                           "CityEMove1",
                                                           "CityDMove7",
                                                           "CityDMove6",
                                                           "CityDMove5",
                                                           "CityDMove4",
                                                           "CityDMove3",
                                                           "CityDMove2",
                                                           "CityDMove1",
                                                           "CityCMove5",
                                                           "CityCMove4",
                                                           "CityCMove3",
                                                           "CityCMove2",
                                                           "CityCMove1",
                                                           "CityBMove6",
                                                           "CityBMove5",
                                                           "CityBMove4",
                                                           "CityBMove3",
                                                           "CityBMove2",
                                                           "CityBMove1",
                                                           "CityAMove6",
                                                           "CityAMove5",
                                                           "CityAMove4",
                                                           "CityAMove3",
                                                           "CityAMove2",
                                                           "CityAMove1",
                                                           "Guard51",
                                                           "Guard52",
                                                           "Guard31",
                                                           "Guard32",
                                                           "Guard41",
                                                           "Guard42",
                                                           "Guard61",
                                                           "Guard62",
                                                           "Guard11",
                                                           "Guard12",
                                                           "Guard22",
                                                           "Guard21",
                                                           "HStinger5",
                                                           "HStinger4",
                                                           "HStinger3",
                                                           "HStinger2",
                                                           "HSquid2",
                                                           "HSquid1",
                                                           "HStinger1",
                                                           "HSickle8",
                                                           "HSickle6",
                                                           "HSickle5",
                                                           "HSickle2",
                                                           "HSickle4",
                                                           "ThreshWeld-1",
                                                           "WeldingPoint",
                                                           "ThreshGuard-3",
                                                           "ThreshGuard-2",
                                                           "ThreshGuard-1",
                                                           "LoBall8",
                                                           "LoBall7",
                                                           "LoBall6",
                                                           "LoBall5",
                                                           "LoBall4",
                                                           "LoBall3",
                                                           "LoBall2",
                                                           "LoBall1",
                                                           "AmbushCenter",
                                                           "AMTarget1",
                                                           "AMTarget2",
                                                           "AmbushSwitch2",
                                                           "AmbushSwitch1",
                                                           "BlastDoor1",
                                                           "Garbage1",
                                                           "Garbage2",
                                                           "Garbage3",
                                                           "Garbage4",
                                                           "PatrolC3",
                                                           "PatrolC2",
                                                           "PatrolC1",
                                                           "PatrolB2",
                                                           "PatrolB1",
                                                           "PatrolA4",
                                                           "PatrolA1",
                                                           "LastGuard1",
                                                           "LastGuard2",
                                                           "LastGuard3",
                                                           "LastGuard4",
                                                           "LastDoorSwitch2",
                                                           "LastSmoke2",
                                                           "LastDoorSwitch1",
                                                           "LastSmoke1"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 13
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "WindPoles",  "CityUp2",      "CityUp1",     "IndustryUp2", "IndustryUp1",  "IndustryDown", "CityDown2",
    "CityDown01", "EntranceRoom", "ReactorMain", "AmbushLo",    "PipeUpxplode", "WasteDisposal"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 22
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "WBECityDown2", "WBECityDown1", "WBEWideUp2",     "WBEWideUp1",         "WBEIndustryDown", "WBEMidDown",
    "WBEMidUp",     "WBSCityDown1", "WBSCityDown2",   "WBSWideUp1",         "WBSWideUp2",      "WBSIndustryDown",
    "WBSMidDown",   "WBSMidUp",     "BetrayalNotice", "EnterWasteDisposal", "HSide12",         "HSide11",
    "HSide22",      "HSide21",      "MusicReactor-1", "MusicPreReactor-1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 17
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "windMid1",     "LevSecAccelRelease", "LevSecAccelStart", "DorCedWideClsD",    "ExpHellion", "RapidFireOn",
    "RapidFireOff", "Lightning",          "Wall fade ???",    "AmbSirenIntense",   "HitEnergy",  "AmbSwitch31",
    "RbtTubbsHa!1", "BaseAlertedSiren",   "RbtThreshRoar",    "AmbSirenBRedAcrop", "AmbSwitch11"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 4
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffect2", "FunkyEffect5", "FunkyEffectGreen",
                                                             "FunkyEffect3"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 40
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCam-SlideUpJupiter",
                                                       "AssaultDrop-1",
                                                       "IntroCam-SlideRight",
                                                       "AssaultDrop-2",
                                                       "IntroCam-SlideLeftHigh",
                                                       "IntroCam-FinalSlide",
                                                       "IntroCamInt-DoorClose",
                                                       "IntroCamInt-CED1",
                                                       "IntroCamInt-CED2",
                                                       "IntroCamInt-FollowCED",
                                                       "AssaultLift-1",
                                                       "IntroCam-FinalFinal",
                                                       "IntroShip",
                                                       "Lifter-1",
                                                       "LifterCarry-1",
                                                       "LifterCarry-2",
                                                       "ExplodeFinal1",
                                                       "EFLifter",
                                                       "ExplodeFinal2",
                                                       "EF3-Tail1",
                                                       "EF3-Tail2",
                                                       "ExplodeFinal3",
                                                       "EF4Camera",
                                                       "EF4Player",
                                                       "CityLeft-3",
                                                       "CityLeft-1",
                                                       "CityLeft-2",
                                                       "CityTop-2",
                                                       "CityTop-1",
                                                       "CityRight-3",
                                                       "CityRight-2",
                                                       "CityRight-1",
                                                       "CityBottom-2",
                                                       "CityBottom-1",
                                                       "HSquid12",
                                                       "HStinger1",
                                                       "HStinger23",
                                                       "HStinger45",
                                                       "IndustryPatrol2",
                                                       "IndustryPatrol1"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 4
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"NRGMatcen1", "NRGMatcen2", "LifterCreator2",
                                                           "LifterCreator1"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 9
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Locate Industrial Power Ducts",  "Disrupt Primary Nuclear Reactor Beam",
    "Hide In Waste Disposal System",  "Rendevous with CED Assault Ship",
    "Destroy the Mars PTMC Colony",   "Unlock Colony Access Doors",
    "Locate Maintenence Power Ducts", "Unlock Security Doors",
    "Override Emergency Duct Doors"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 17
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroCam1",
                                                             "BlankMessage",
                                                             "BombName",
                                                             "NuclearDisruption",
                                                             "NuclearDisruptorFail",
                                                             "FCOneMinute",
                                                             "GameGetToWasteDisposal",
                                                             "FCFindBombShelter",
                                                             "FCAbandoned",
                                                             "FCNoContact",
                                                             "FCGetOut",
                                                             "CityAccessDoors",
                                                             "Trap",
                                                             "Last1",
                                                             "Last2",
                                                             "WallHint",
                                                             "GetAwayFromExit"};
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
    strcpy(filename, "Merc1.msg");
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
  case ID_CUSTOM_OBJECT_2027:
    return new CustomObjectScript_2027;
    break;
  case ID_CUSTOM_OBJECT_0820:
    return new CustomObjectScript_0820;
    break;
  case ID_CUSTOM_OBJECT_0831:
    return new CustomObjectScript_0831;
    break;
  case ID_CUSTOM_OBJECT_0832:
    return new CustomObjectScript_0832;
    break;
  case ID_CUSTOM_OBJECT_0836:
    return new CustomObjectScript_0836;
    break;
  case ID_CUSTOM_OBJECT_0888:
    return new CustomObjectScript_0888;
    break;
  case ID_CUSTOM_OBJECT_0887:
    return new CustomObjectScript_0887;
    break;
  case ID_CUSTOM_OBJECT_0886:
    return new CustomObjectScript_0886;
    break;
  case ID_CUSTOM_OBJECT_182A:
    return new CustomObjectScript_182A;
    break;
  case ID_CUSTOM_OBJECT_088A:
    return new CustomObjectScript_088A;
    break;
  case ID_CUSTOM_OBJECT_0889:
    return new CustomObjectScript_0889;
    break;
  case ID_CUSTOM_OBJECT_188C:
    return new CustomObjectScript_188C;
    break;
  case ID_CUSTOM_OBJECT_0885:
    return new CustomObjectScript_0885;
    break;
  case ID_CUSTOM_OBJECT_096D:
    return new CustomObjectScript_096D;
    break;
  case ID_CUSTOM_OBJECT_0877:
    return new CustomObjectScript_0877;
    break;
  case ID_CUSTOM_OBJECT_0878:
    return new CustomObjectScript_0878;
    break;
  case ID_CUSTOM_OBJECT_0879:
    return new CustomObjectScript_0879;
    break;
  case ID_CUSTOM_OBJECT_1171:
    return new CustomObjectScript_1171;
    break;
  case ID_CUSTOM_OBJECT_087A:
    return new CustomObjectScript_087A;
    break;
  case ID_CUSTOM_OBJECT_087B:
    return new CustomObjectScript_087B;
    break;
  case ID_CUSTOM_OBJECT_087C:
    return new CustomObjectScript_087C;
    break;
  case ID_CUSTOM_OBJECT_087D:
    return new CustomObjectScript_087D;
    break;
  case ID_CUSTOM_OBJECT_1170:
    return new CustomObjectScript_1170;
    break;
  case ID_CUSTOM_OBJECT_0988:
    return new CustomObjectScript_0988;
    break;
  case ID_CUSTOM_OBJECT_0981:
    return new CustomObjectScript_0981;
    break;
  case ID_CUSTOM_OBJECT_0980:
    return new CustomObjectScript_0980;
    break;
  case ID_CUSTOM_OBJECT_097F:
    return new CustomObjectScript_097F;
    break;
  case ID_CUSTOM_OBJECT_097E:
    return new CustomObjectScript_097E;
    break;
  case ID_CUSTOM_OBJECT_097D:
    return new CustomObjectScript_097D;
    break;
  case ID_CUSTOM_OBJECT_097C:
    return new CustomObjectScript_097C;
    break;
  case ID_CUSTOM_OBJECT_117B:
    return new CustomObjectScript_117B;
    break;
  case ID_CUSTOM_OBJECT_097A:
    return new CustomObjectScript_097A;
    break;
  case ID_CUSTOM_OBJECT_1984:
    return new CustomObjectScript_1984;
    break;
  case ID_CUSTOM_OBJECT_0875:
    return new CustomObjectScript_0875;
    break;
  case ID_CUSTOM_OBJECT_0865:
    return new CustomObjectScript_0865;
    break;
  case ID_CUSTOM_OBJECT_0864:
    return new CustomObjectScript_0864;
    break;
  case ID_CUSTOM_OBJECT_0863:
    return new CustomObjectScript_0863;
    break;
  case ID_CUSTOM_OBJECT_0862:
    return new CustomObjectScript_0862;
    break;
  case ID_CUSTOM_OBJECT_08A1:
    return new CustomObjectScript_08A1;
    break;
  case ID_CUSTOM_OBJECT_08A0:
    return new CustomObjectScript_08A0;
    break;
  case ID_CUSTOM_OBJECT_089F:
    return new CustomObjectScript_089F;
    break;
  case ID_CUSTOM_OBJECT_109E:
    return new CustomObjectScript_109E;
    break;
  case ID_CUSTOM_OBJECT_109C:
    return new CustomObjectScript_109C;
    break;
  case ID_CUSTOM_OBJECT_08AE:
    return new CustomObjectScript_08AE;
    break;
  case ID_CUSTOM_OBJECT_18A6:
    return new CustomObjectScript_18A6;
    break;
  case ID_CUSTOM_OBJECT_18A5:
    return new CustomObjectScript_18A5;
    break;
  case ID_CUSTOM_OBJECT_18A4:
    return new CustomObjectScript_18A4;
    break;
  case ID_CUSTOM_OBJECT_18A7:
    return new CustomObjectScript_18A7;
    break;
  case ID_CUSTOM_OBJECT_18A9:
    return new CustomObjectScript_18A9;
    break;
  case ID_CUSTOM_OBJECT_20A3:
    return new CustomObjectScript_20A3;
    break;
  case ID_CUSTOM_OBJECT_28A2:
    return new CustomObjectScript_28A2;
    break;
  case ID_CUSTOM_OBJECT_18A8:
    return new CustomObjectScript_18A8;
    break;
  case ID_CUSTOM_OBJECT_08DA:
    return new CustomObjectScript_08DA;
    break;
  case ID_CUSTOM_OBJECT_08D9:
    return new CustomObjectScript_08D9;
    break;
  case ID_CUSTOM_OBJECT_08D8:
    return new CustomObjectScript_08D8;
    break;
  case ID_CUSTOM_OBJECT_08D7:
    return new CustomObjectScript_08D7;
    break;
  case ID_CUSTOM_OBJECT_08D6:
    return new CustomObjectScript_08D6;
    break;
  case ID_CUSTOM_OBJECT_08D5:
    return new CustomObjectScript_08D5;
    break;
  case ID_CUSTOM_OBJECT_08D4:
    return new CustomObjectScript_08D4;
    break;
  case ID_CUSTOM_OBJECT_08D3:
    return new CustomObjectScript_08D3;
    break;
  case ID_CUSTOM_OBJECT_08D2:
    return new CustomObjectScript_08D2;
    break;
  case ID_CUSTOM_OBJECT_08D1:
    return new CustomObjectScript_08D1;
    break;
  case ID_CUSTOM_OBJECT_08D0:
    return new CustomObjectScript_08D0;
    break;
  case ID_CUSTOM_OBJECT_08CF:
    return new CustomObjectScript_08CF;
    break;
  case ID_CUSTOM_OBJECT_105C:
    return new CustomObjectScript_105C;
    break;
  case ID_CUSTOM_OBJECT_2059:
    return new CustomObjectScript_2059;
    break;
  case ID_CUSTOM_OBJECT_0858:
    return new CustomObjectScript_0858;
    break;
  case ID_CUSTOM_OBJECT_0857:
    return new CustomObjectScript_0857;
    break;
  case ID_CUSTOM_OBJECT_1030:
    return new CustomObjectScript_1030;
    break;
  case ID_CUSTOM_OBJECT_402F:
    return new CustomObjectScript_402F;
    break;
  case ID_CUSTOM_OBJECT_1871:
    return new CustomObjectScript_1871;
    break;
  case ID_CUSTOM_OBJECT_091A:
    return new CustomObjectScript_091A;
    break;
  case ID_CUSTOM_OBJECT_0919:
    return new CustomObjectScript_0919;
    break;
  case ID_CUSTOM_OBJECT_0918:
    return new CustomObjectScript_0918;
    break;
  case ID_CUSTOM_OBJECT_0917:
    return new CustomObjectScript_0917;
    break;
  case ID_CUSTOM_OBJECT_0925:
    return new CustomObjectScript_0925;
    break;
  case ID_CUSTOM_OBJECT_0924:
    return new CustomObjectScript_0924;
    break;
  case ID_CUSTOM_OBJECT_0923:
    return new CustomObjectScript_0923;
    break;
  case ID_CUSTOM_OBJECT_0922:
    return new CustomObjectScript_0922;
    break;
  case ID_CUSTOM_OBJECT_0921:
    return new CustomObjectScript_0921;
    break;
  case ID_CUSTOM_OBJECT_1120:
    return new CustomObjectScript_1120;
    break;
  case ID_CUSTOM_OBJECT_111F:
    return new CustomObjectScript_111F;
    break;
  case ID_CUSTOM_OBJECT_111E:
    return new CustomObjectScript_111E;
    break;
  case ID_CUSTOM_OBJECT_112E:
    return new CustomObjectScript_112E;
    break;
  case ID_CUSTOM_OBJECT_0932:
    return new CustomObjectScript_0932;
    break;
  case ID_CUSTOM_OBJECT_0931:
    return new CustomObjectScript_0931;
    break;
  case ID_CUSTOM_OBJECT_080F:
    return new CustomObjectScript_080F;
    break;
  case ID_CUSTOM_OBJECT_0967:
    return new CustomObjectScript_0967;
    break;
  case ID_CUSTOM_OBJECT_0966:
    return new CustomObjectScript_0966;
    break;
  case ID_CUSTOM_OBJECT_0809:
    return new CustomObjectScript_0809;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
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
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
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
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
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
  case ID_CUSTOM_OBJECT_2027:
    delete ((CustomObjectScript_2027 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0820:
    delete ((CustomObjectScript_0820 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0831:
    delete ((CustomObjectScript_0831 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0832:
    delete ((CustomObjectScript_0832 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0836:
    delete ((CustomObjectScript_0836 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0888:
    delete ((CustomObjectScript_0888 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0887:
    delete ((CustomObjectScript_0887 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0886:
    delete ((CustomObjectScript_0886 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_182A:
    delete ((CustomObjectScript_182A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_088A:
    delete ((CustomObjectScript_088A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0889:
    delete ((CustomObjectScript_0889 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_188C:
    delete ((CustomObjectScript_188C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0885:
    delete ((CustomObjectScript_0885 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096D:
    delete ((CustomObjectScript_096D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0877:
    delete ((CustomObjectScript_0877 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0878:
    delete ((CustomObjectScript_0878 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0879:
    delete ((CustomObjectScript_0879 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1171:
    delete ((CustomObjectScript_1171 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087A:
    delete ((CustomObjectScript_087A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087B:
    delete ((CustomObjectScript_087B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087C:
    delete ((CustomObjectScript_087C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087D:
    delete ((CustomObjectScript_087D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1170:
    delete ((CustomObjectScript_1170 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0988:
    delete ((CustomObjectScript_0988 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0981:
    delete ((CustomObjectScript_0981 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0980:
    delete ((CustomObjectScript_0980 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097F:
    delete ((CustomObjectScript_097F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097E:
    delete ((CustomObjectScript_097E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097D:
    delete ((CustomObjectScript_097D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097C:
    delete ((CustomObjectScript_097C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_117B:
    delete ((CustomObjectScript_117B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097A:
    delete ((CustomObjectScript_097A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1984:
    delete ((CustomObjectScript_1984 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0875:
    delete ((CustomObjectScript_0875 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0865:
    delete ((CustomObjectScript_0865 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0864:
    delete ((CustomObjectScript_0864 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0863:
    delete ((CustomObjectScript_0863 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0862:
    delete ((CustomObjectScript_0862 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A1:
    delete ((CustomObjectScript_08A1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A0:
    delete ((CustomObjectScript_08A0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_089F:
    delete ((CustomObjectScript_089F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_109E:
    delete ((CustomObjectScript_109E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_109C:
    delete ((CustomObjectScript_109C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08AE:
    delete ((CustomObjectScript_08AE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A6:
    delete ((CustomObjectScript_18A6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A5:
    delete ((CustomObjectScript_18A5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A4:
    delete ((CustomObjectScript_18A4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A7:
    delete ((CustomObjectScript_18A7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A9:
    delete ((CustomObjectScript_18A9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20A3:
    delete ((CustomObjectScript_20A3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_28A2:
    delete ((CustomObjectScript_28A2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A8:
    delete ((CustomObjectScript_18A8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08DA:
    delete ((CustomObjectScript_08DA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D9:
    delete ((CustomObjectScript_08D9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D8:
    delete ((CustomObjectScript_08D8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D7:
    delete ((CustomObjectScript_08D7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D6:
    delete ((CustomObjectScript_08D6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D5:
    delete ((CustomObjectScript_08D5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D4:
    delete ((CustomObjectScript_08D4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D3:
    delete ((CustomObjectScript_08D3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D2:
    delete ((CustomObjectScript_08D2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D1:
    delete ((CustomObjectScript_08D1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D0:
    delete ((CustomObjectScript_08D0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08CF:
    delete ((CustomObjectScript_08CF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_105C:
    delete ((CustomObjectScript_105C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2059:
    delete ((CustomObjectScript_2059 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0858:
    delete ((CustomObjectScript_0858 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0857:
    delete ((CustomObjectScript_0857 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1030:
    delete ((CustomObjectScript_1030 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_402F:
    delete ((CustomObjectScript_402F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1871:
    delete ((CustomObjectScript_1871 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_091A:
    delete ((CustomObjectScript_091A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0919:
    delete ((CustomObjectScript_0919 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0918:
    delete ((CustomObjectScript_0918 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0917:
    delete ((CustomObjectScript_0917 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0925:
    delete ((CustomObjectScript_0925 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0924:
    delete ((CustomObjectScript_0924 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0923:
    delete ((CustomObjectScript_0923 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0922:
    delete ((CustomObjectScript_0922 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0921:
    delete ((CustomObjectScript_0921 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1120:
    delete ((CustomObjectScript_1120 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_111F:
    delete ((CustomObjectScript_111F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_111E:
    delete ((CustomObjectScript_111E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_112E:
    delete ((CustomObjectScript_112E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0932:
    delete ((CustomObjectScript_0932 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0931:
    delete ((CustomObjectScript_0931 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080F:
    delete ((CustomObjectScript_080F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0967:
    delete ((CustomObjectScript_0967 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0966:
    delete ((CustomObjectScript_0966 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0809:
    delete ((CustomObjectScript_0809 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
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
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
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
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
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
  case ID_CUSTOM_OBJECT_2027:
  case ID_CUSTOM_OBJECT_0820:
  case ID_CUSTOM_OBJECT_0831:
  case ID_CUSTOM_OBJECT_0832:
  case ID_CUSTOM_OBJECT_0836:
  case ID_CUSTOM_OBJECT_0888:
  case ID_CUSTOM_OBJECT_0887:
  case ID_CUSTOM_OBJECT_0886:
  case ID_CUSTOM_OBJECT_182A:
  case ID_CUSTOM_OBJECT_088A:
  case ID_CUSTOM_OBJECT_0889:
  case ID_CUSTOM_OBJECT_188C:
  case ID_CUSTOM_OBJECT_0885:
  case ID_CUSTOM_OBJECT_096D:
  case ID_CUSTOM_OBJECT_0877:
  case ID_CUSTOM_OBJECT_0878:
  case ID_CUSTOM_OBJECT_0879:
  case ID_CUSTOM_OBJECT_1171:
  case ID_CUSTOM_OBJECT_087A:
  case ID_CUSTOM_OBJECT_087B:
  case ID_CUSTOM_OBJECT_087C:
  case ID_CUSTOM_OBJECT_087D:
  case ID_CUSTOM_OBJECT_1170:
  case ID_CUSTOM_OBJECT_0988:
  case ID_CUSTOM_OBJECT_0981:
  case ID_CUSTOM_OBJECT_0980:
  case ID_CUSTOM_OBJECT_097F:
  case ID_CUSTOM_OBJECT_097E:
  case ID_CUSTOM_OBJECT_097D:
  case ID_CUSTOM_OBJECT_097C:
  case ID_CUSTOM_OBJECT_117B:
  case ID_CUSTOM_OBJECT_097A:
  case ID_CUSTOM_OBJECT_1984:
  case ID_CUSTOM_OBJECT_0875:
  case ID_CUSTOM_OBJECT_0865:
  case ID_CUSTOM_OBJECT_0864:
  case ID_CUSTOM_OBJECT_0863:
  case ID_CUSTOM_OBJECT_0862:
  case ID_CUSTOM_OBJECT_08A1:
  case ID_CUSTOM_OBJECT_08A0:
  case ID_CUSTOM_OBJECT_089F:
  case ID_CUSTOM_OBJECT_109E:
  case ID_CUSTOM_OBJECT_109C:
  case ID_CUSTOM_OBJECT_08AE:
  case ID_CUSTOM_OBJECT_18A6:
  case ID_CUSTOM_OBJECT_18A5:
  case ID_CUSTOM_OBJECT_18A4:
  case ID_CUSTOM_OBJECT_18A7:
  case ID_CUSTOM_OBJECT_18A9:
  case ID_CUSTOM_OBJECT_20A3:
  case ID_CUSTOM_OBJECT_28A2:
  case ID_CUSTOM_OBJECT_18A8:
  case ID_CUSTOM_OBJECT_08DA:
  case ID_CUSTOM_OBJECT_08D9:
  case ID_CUSTOM_OBJECT_08D8:
  case ID_CUSTOM_OBJECT_08D7:
  case ID_CUSTOM_OBJECT_08D6:
  case ID_CUSTOM_OBJECT_08D5:
  case ID_CUSTOM_OBJECT_08D4:
  case ID_CUSTOM_OBJECT_08D3:
  case ID_CUSTOM_OBJECT_08D2:
  case ID_CUSTOM_OBJECT_08D1:
  case ID_CUSTOM_OBJECT_08D0:
  case ID_CUSTOM_OBJECT_08CF:
  case ID_CUSTOM_OBJECT_105C:
  case ID_CUSTOM_OBJECT_2059:
  case ID_CUSTOM_OBJECT_0858:
  case ID_CUSTOM_OBJECT_0857:
  case ID_CUSTOM_OBJECT_1030:
  case ID_CUSTOM_OBJECT_402F:
  case ID_CUSTOM_OBJECT_1871:
  case ID_CUSTOM_OBJECT_091A:
  case ID_CUSTOM_OBJECT_0919:
  case ID_CUSTOM_OBJECT_0918:
  case ID_CUSTOM_OBJECT_0917:
  case ID_CUSTOM_OBJECT_0925:
  case ID_CUSTOM_OBJECT_0924:
  case ID_CUSTOM_OBJECT_0923:
  case ID_CUSTOM_OBJECT_0922:
  case ID_CUSTOM_OBJECT_0921:
  case ID_CUSTOM_OBJECT_1120:
  case ID_CUSTOM_OBJECT_111F:
  case ID_CUSTOM_OBJECT_111E:
  case ID_CUSTOM_OBJECT_112E:
  case ID_CUSTOM_OBJECT_0932:
  case ID_CUSTOM_OBJECT_0931:
  case ID_CUSTOM_OBJECT_080F:
  case ID_CUSTOM_OBJECT_0967:
  case ID_CUSTOM_OBJECT_0966:
  case ID_CUSTOM_OBJECT_0809:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0015:
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
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0015;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[90];
  static int cust_id_list[90] = {
      ID_CUSTOM_OBJECT_2027, ID_CUSTOM_OBJECT_0820, ID_CUSTOM_OBJECT_0831, ID_CUSTOM_OBJECT_0832,
      ID_CUSTOM_OBJECT_0836, ID_CUSTOM_OBJECT_0888, ID_CUSTOM_OBJECT_0887, ID_CUSTOM_OBJECT_0886,
      ID_CUSTOM_OBJECT_182A, ID_CUSTOM_OBJECT_088A, ID_CUSTOM_OBJECT_0889, ID_CUSTOM_OBJECT_188C,
      ID_CUSTOM_OBJECT_0885, ID_CUSTOM_OBJECT_096D, ID_CUSTOM_OBJECT_0877, ID_CUSTOM_OBJECT_0878,
      ID_CUSTOM_OBJECT_0879, ID_CUSTOM_OBJECT_1171, ID_CUSTOM_OBJECT_087A, ID_CUSTOM_OBJECT_087B,
      ID_CUSTOM_OBJECT_087C, ID_CUSTOM_OBJECT_087D, ID_CUSTOM_OBJECT_1170, ID_CUSTOM_OBJECT_0988,
      ID_CUSTOM_OBJECT_0981, ID_CUSTOM_OBJECT_0980, ID_CUSTOM_OBJECT_097F, ID_CUSTOM_OBJECT_097E,
      ID_CUSTOM_OBJECT_097D, ID_CUSTOM_OBJECT_097C, ID_CUSTOM_OBJECT_117B, ID_CUSTOM_OBJECT_097A,
      ID_CUSTOM_OBJECT_1984, ID_CUSTOM_OBJECT_0875, ID_CUSTOM_OBJECT_0865, ID_CUSTOM_OBJECT_0864,
      ID_CUSTOM_OBJECT_0863, ID_CUSTOM_OBJECT_0862, ID_CUSTOM_OBJECT_08A1, ID_CUSTOM_OBJECT_08A0,
      ID_CUSTOM_OBJECT_089F, ID_CUSTOM_OBJECT_109E, ID_CUSTOM_OBJECT_109C, ID_CUSTOM_OBJECT_08AE,
      ID_CUSTOM_OBJECT_18A6, ID_CUSTOM_OBJECT_18A5, ID_CUSTOM_OBJECT_18A4, ID_CUSTOM_OBJECT_18A7,
      ID_CUSTOM_OBJECT_18A9, ID_CUSTOM_OBJECT_20A3, ID_CUSTOM_OBJECT_28A2, ID_CUSTOM_OBJECT_18A8,
      ID_CUSTOM_OBJECT_08DA, ID_CUSTOM_OBJECT_08D9, ID_CUSTOM_OBJECT_08D8, ID_CUSTOM_OBJECT_08D7,
      ID_CUSTOM_OBJECT_08D6, ID_CUSTOM_OBJECT_08D5, ID_CUSTOM_OBJECT_08D4, ID_CUSTOM_OBJECT_08D3,
      ID_CUSTOM_OBJECT_08D2, ID_CUSTOM_OBJECT_08D1, ID_CUSTOM_OBJECT_08D0, ID_CUSTOM_OBJECT_08CF,
      ID_CUSTOM_OBJECT_105C, ID_CUSTOM_OBJECT_2059, ID_CUSTOM_OBJECT_0858, ID_CUSTOM_OBJECT_0857,
      ID_CUSTOM_OBJECT_1030, ID_CUSTOM_OBJECT_402F, ID_CUSTOM_OBJECT_1871, ID_CUSTOM_OBJECT_091A,
      ID_CUSTOM_OBJECT_0919, ID_CUSTOM_OBJECT_0918, ID_CUSTOM_OBJECT_0917, ID_CUSTOM_OBJECT_0925,
      ID_CUSTOM_OBJECT_0924, ID_CUSTOM_OBJECT_0923, ID_CUSTOM_OBJECT_0922, ID_CUSTOM_OBJECT_0921,
      ID_CUSTOM_OBJECT_1120, ID_CUSTOM_OBJECT_111F, ID_CUSTOM_OBJECT_111E, ID_CUSTOM_OBJECT_112E,
      ID_CUSTOM_OBJECT_0932, ID_CUSTOM_OBJECT_0931, ID_CUSTOM_OBJECT_080F, ID_CUSTOM_OBJECT_0967,
      ID_CUSTOM_OBJECT_0966, ID_CUSTOM_OBJECT_0809};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[36];
  cust_handle_list[1] = Object_handles[37];
  cust_handle_list[2] = Object_handles[38];
  cust_handle_list[3] = Object_handles[45];
  cust_handle_list[4] = Object_handles[51];
  cust_handle_list[5] = Object_handles[69];
  cust_handle_list[6] = Object_handles[71];
  cust_handle_list[7] = Object_handles[73];
  cust_handle_list[8] = Object_handles[75];
  cust_handle_list[9] = Object_handles[77];
  cust_handle_list[10] = Object_handles[79];
  cust_handle_list[11] = Object_handles[83];
  cust_handle_list[12] = Object_handles[81];
  cust_handle_list[13] = Object_handles[94];
  cust_handle_list[14] = Object_handles[109];
  cust_handle_list[15] = Object_handles[108];
  cust_handle_list[16] = Object_handles[107];
  cust_handle_list[17] = Object_handles[87];
  cust_handle_list[18] = Object_handles[106];
  cust_handle_list[19] = Object_handles[105];
  cust_handle_list[20] = Object_handles[104];
  cust_handle_list[21] = Object_handles[103];
  cust_handle_list[22] = Object_handles[111];
  cust_handle_list[23] = Object_handles[129];
  cust_handle_list[24] = Object_handles[130];
  cust_handle_list[25] = Object_handles[131];
  cust_handle_list[26] = Object_handles[132];
  cust_handle_list[27] = Object_handles[133];
  cust_handle_list[28] = Object_handles[134];
  cust_handle_list[29] = Object_handles[135];
  cust_handle_list[30] = Object_handles[136];
  cust_handle_list[31] = Object_handles[137];
  cust_handle_list[32] = Object_handles[139];
  cust_handle_list[33] = Object_handles[148];
  cust_handle_list[34] = Object_handles[150];
  cust_handle_list[35] = Object_handles[152];
  cust_handle_list[36] = Object_handles[154];
  cust_handle_list[37] = Object_handles[156];
  cust_handle_list[38] = Object_handles[149];
  cust_handle_list[39] = Object_handles[151];
  cust_handle_list[40] = Object_handles[153];
  cust_handle_list[41] = Object_handles[155];
  cust_handle_list[42] = Object_handles[157];
  cust_handle_list[43] = Object_handles[165];
  cust_handle_list[44] = Object_handles[168];
  cust_handle_list[45] = Object_handles[169];
  cust_handle_list[46] = Object_handles[170];
  cust_handle_list[47] = Object_handles[171];
  cust_handle_list[48] = Object_handles[172];
  cust_handle_list[49] = Object_handles[173];
  cust_handle_list[50] = Object_handles[174];
  cust_handle_list[51] = Object_handles[175];
  cust_handle_list[52] = Object_handles[215];
  cust_handle_list[53] = Object_handles[216];
  cust_handle_list[54] = Object_handles[217];
  cust_handle_list[55] = Object_handles[218];
  cust_handle_list[56] = Object_handles[219];
  cust_handle_list[57] = Object_handles[220];
  cust_handle_list[58] = Object_handles[221];
  cust_handle_list[59] = Object_handles[222];
  cust_handle_list[60] = Object_handles[223];
  cust_handle_list[61] = Object_handles[224];
  cust_handle_list[62] = Object_handles[225];
  cust_handle_list[63] = Object_handles[226];
  cust_handle_list[64] = Object_handles[14];
  cust_handle_list[65] = Object_handles[13];
  cust_handle_list[66] = Object_handles[12];
  cust_handle_list[67] = Object_handles[11];
  cust_handle_list[68] = Object_handles[10];
  cust_handle_list[69] = Object_handles[9];
  cust_handle_list[70] = Object_handles[164];
  cust_handle_list[71] = Object_handles[241];
  cust_handle_list[72] = Object_handles[242];
  cust_handle_list[73] = Object_handles[243];
  cust_handle_list[74] = Object_handles[239];
  cust_handle_list[75] = Object_handles[122];
  cust_handle_list[76] = Object_handles[123];
  cust_handle_list[77] = Object_handles[113];
  cust_handle_list[78] = Object_handles[124];
  cust_handle_list[79] = Object_handles[118];
  cust_handle_list[80] = Object_handles[117];
  cust_handle_list[81] = Object_handles[116];
  cust_handle_list[82] = Object_handles[115];
  cust_handle_list[83] = Object_handles[252];
  cust_handle_list[84] = Object_handles[255];
  cust_handle_list[85] = Object_handles[256];
  cust_handle_list[86] = Object_handles[257];
  cust_handle_list[87] = Object_handles[273];
  cust_handle_list[88] = Object_handles[275];
  cust_handle_list[89] = Object_handles[46];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 90;
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

    // Script 197: WallHint (Rookie or Trainee only!)
    if ((ScriptActionCtr_197 < 1) && ((qRoomHasPlayer(Room_indexes[0]) == true) && (qGetDifficulty() < 2))) {
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_197 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_197++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 060: INIT Difficulty Values
    if (1) {
      if (qGetDifficulty() == 0) {
        aUserVarSet(1, 3.000000f);
      } else {
        if (qGetDifficulty() == 1) {
          aUserVarSet(1, 6.000000f);
        } else {
          if (qGetDifficulty() == 2) {
            aUserVarSet(1, 8.000000f);
          } else {
            if (qGetDifficulty() == 3) {
              aUserVarSet(1, 10.000000f);
            } else {
              aUserVarSet(1, 10.000000f);
            }
          }
        }
      }
      aUserVarSet(2, qMathMulFloat(qMathSubFloat(4.000000f, qMathIntToFloat(qGetDifficulty())), 20.000000f));

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 031: INIT Smoke Stacks
    if (1 == true) {
      aTurnOnSpew(Object_handles[15], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[16], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[17], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[18], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[19], -1, 7, 0.000000f, 0.000000f, 65536, 0, 5.000000f, 0.180000f, 55.000000f,
                  15.000000f, 60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[20], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.500000f, 0.150000f, 55.000000f,
                  9.000000f, 50.000000f, 0, -1);
      aTurnOnSpew(Object_handles[21], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.100000f, 55.000000f,
                  15.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[22], -1, 7, 0.000000f, 0.000000f, 65536, 0, 6.000000f, 0.130000f, 55.000000f,
                  10.000000f, 50.000000f, 0, -1);
      aTurnOnSpew(Object_handles[23], -1, 7, 0.000000f, 0.000000f, 65536, 0, 5.000000f, 0.200000f, 55.000000f,
                  8.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[24], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, 55.000000f,
                  9.000000f, 50.000000f, 0, -1);
      aTurnOnSpew(Object_handles[25], -1, 7, 0.000000f, 0.000000f, 65536, 0, 6.000000f, 0.200000f, 55.000000f,
                  20.000000f, 60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[26], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, 55.000000f,
                  12.000000f, 50.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 000: INIT Winds
    if (1) {
      aUserVarSet(0, 50.000000f);
      aRoomSetWind(Room_indexes[0], 0.000000f, 1.000000f, 0.000000f, 4.500000f);
      aRoomSetWind(Room_indexes[1], 0.000000f, -1.000000f, 0.000000f, qUserVarValue(0));
      aRoomSetWind(Room_indexes[2], 0.000000f, 1.000000f, 0.000000f, qUserVarValue(0));
      aRoomSetWind(Room_indexes[3], 0.000000f, 1.000000f, 0.000000f, qUserVarValue(0));
      aRoomSetWind(Room_indexes[4], 0.000000f, 1.000000f, 0.000000f, qUserVarValue(0));
      aRoomSetWind(Room_indexes[5], 0.000000f, -1.000000f, 0.000000f, qUserVarValue(0));
      aRoomSetWind(Room_indexes[6], 0.000000f, -1.000000f, 0.000000f, qUserVarValue(0));
      aRoomSetWind(Room_indexes[7], 0.000000f, -1.000000f, 0.000000f, qUserVarValue(0));

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 016: IntroCamera-1
    if (1 == true) {
      aObjGhostSet(1, Object_handles[31]);
      aObjGhostSet(1, Object_handles[32]);
      aObjGhostSet(1, Object_handles[33]);
      aObjGhostSet(1, Object_handles[34]);
      aObjGhostSet(1, Object_handles[35]);
      aCinematicSimple(Path_indexes[0], Message_strings[0], Object_handles[36], 8.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 021: INIT Lifter Sequence (create first Rods)
    if (1) {
      aObjMakeInvuln(Object_handles[55], 99999);
      aObjMakeInvuln(Object_handles[56], 99999);
      aSetLevelTimer(0.000000f, 0);
      aSetLevelTimer(25.000000f, 7);
      aObjGhostSet(1, Object_handles[57]);
      aObjGhostSet(1, Object_handles[58]);
      aMatcenSetState(1, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 043: INIT ReactorBeams
    if ((ScriptActionCtr_043 < 1) && (1)) {
      aLightningCreate(Object_handles[69], Object_handles[70], 99999.000000f, 6.000000f, 2, Texture_indexes[2],
                       0.400000f, 3, 150, 250, 220, 0);
      aLightningCreate(Object_handles[71], Object_handles[72], 99999.000000f, 6.000000f, 2, Texture_indexes[2],
                       0.400000f, 3, 150, 250, 220, 0);
      aLightningCreate(Object_handles[73], Object_handles[74], 99999.000000f, 6.000000f, 2, Texture_indexes[2],
                       0.400000f, 3, 150, 250, 220, 0);
      aLightningCreate(Object_handles[75], Object_handles[76], 99999.000000f, 6.000000f, 2, Texture_indexes[2],
                       0.400000f, 3, 150, 250, 220, 0);
      aLightningCreate(Object_handles[77], Object_handles[78], 99999.000000f, 6.000000f, 2, Texture_indexes[2],
                       0.400000f, 3, 150, 250, 220, 0);
      aLightningCreate(Object_handles[79], Object_handles[80], 99999.000000f, 6.000000f, 2, Texture_indexes[2],
                       0.400000f, 3, 150, 250, 220, 0);
      aLightningCreate(Object_handles[81], Object_handles[82], 99999.000000f, 9.000000f, 1, Texture_indexes[2],
                       0.400000f, 2, 120, 220, 200, 0);
      aLightningCreate(Object_handles[81], Object_handles[82], 99999.000000f, 3.000000f, 1, Texture_indexes[2],
                       0.200000f, 2, 120, 220, 200, 0);
      aLightningCreate(Object_handles[82], Object_handles[81], 99999.000000f, 6.000000f, 1, Texture_indexes[2],
                       0.300000f, 2, 120, 220, 200, 0);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }

    // Script 171: INIT Final Explosion
    if (1) {
      aObjGhostSet(1, Object_handles[87]);
      aObjGhostSet(1, Object_handles[88]);
      aObjGhostSet(1, Object_handles[89]);

      // Increment the script action counter
      if (ScriptActionCtr_171 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_171++;
    }

    // Script 125: INIT HiddenSewer
    if (1) {
      aCloakObject(Object_handles[227], 99999.000000f);
      aCloakObject(Object_handles[228], 99999.000000f);
      aCloakObject(Object_handles[229], 99999.000000f);
      aCloakObject(Object_handles[230], 99999.000000f);
      aCloakObject(Object_handles[231], 99999.000000f);
      aCloakObject(Object_handles[232], 99999.000000f);
      aCloakObject(Object_handles[233], 99999.000000f);
      aCloakObject(Object_handles[234], 99999.000000f);
      aCloakObject(Object_handles[235], 99999.000000f);
      aCloakObject(Object_handles[236], 99999.000000f);
      aCloakObject(Object_handles[237], 99999.000000f);
      aCloakObject(Object_handles[238], 99999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }

    // Script 141: INIT Goofy General
    if (1) {
      aObjMakeInvuln(Object_handles[103], 99999);
      aObjMakeInvuln(Object_handles[104], 99999);
      aObjMakeInvuln(Object_handles[105], 99999);
      aObjMakeInvuln(Object_handles[106], 99999);
      aObjMakeInvuln(Object_handles[160], 99999);
      aObjMakeInvuln(Object_handles[109], 99999);
      aObjMakeInvuln(Object_handles[108], 99999);
      aObjMakeInvuln(Object_handles[107], 99999);

      // Increment the script action counter
      if (ScriptActionCtr_141 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_141++;
    }

    // Script 162: INIT Last Area
    if (1) {
      aCloakObject(Object_handles[269], 99999.000000f);
      aCloakObject(Object_handles[270], 99999.000000f);
      aCloakObject(Object_handles[271], 99999.000000f);
      aCloakObject(Object_handles[272], 99999.000000f);
      aObjGhostSet(1, Object_handles[269]);
      aObjGhostSet(1, Object_handles[270]);
      aObjGhostSet(1, Object_handles[272]);
      aObjGhostSet(1, Object_handles[271]);

      // Increment the script action counter
      if (ScriptActionCtr_162 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_162++;
    }

    // Script 200: MusicIntro
    if (1) {
      aMusicSetRegionAll(0);

      // Increment the script action counter
      if (ScriptActionCtr_200 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_200++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 030: Open Entrance Door (INTRO)
    if ((ScriptActionCtr_030 < 1) && (event_data->id == 2)) {
      aEmitSparks(20.000000f, Object_handles[47]);
      aEmitSparks(10.000000f, Object_handles[48]);
      aEmitSparks(30.000000f, Object_handles[49]);
      aEmitSparks(50.000000f, Object_handles[50]);
      aDoorSetPos(Door_handles[0], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }

    // Script 029: Close Entrance Door (INTRO)
    if ((ScriptActionCtr_029 < 1) && (event_data->id == 1)) {
      aEmitSparks(40.000000f, Object_handles[39]);
      aEmitSparks(30.000000f, Object_handles[40]);
      aEmitSparks(10.000000f, Object_handles[41]);
      aEmitSparks(60.000000f, Object_handles[42]);
      aDoorSetPos(Door_handles[0], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 042: INIT Lifter Sequence (create second Lifters)
    if ((ScriptActionCtr_042 < 1) && (event_data->id == 0)) {
      aMatcenSetState(1, Matcen_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 022: INIT Lifter Sequence (create first Lifters)
    if ((ScriptActionCtr_022 < 1) && (event_data->id == 0)) {
      aLightningCreate(Object_handles[56], Object_handles[59], 99999.000000f, 9.000000f, 2, Texture_indexes[0],
                       0.300000f, 3, 200, 50, 150, 0);
      aLightningCreate(Object_handles[55], Object_handles[60], 99999.000000f, 9.000000f, 2, Texture_indexes[0],
                       0.300000f, 3, 200, 50, 150, 0);
      aMatcenSetState(1, Matcen_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 033: Lifter Sequence (Rod 1 Smoking)
    if (event_data->id == 3) {
      aObjSpark(qObjSavedHandle(2), 20.000000f, 9999.000000f);
      aSoundPlayObject(Sound_indexes[6], Object_handles[55], 1.000000f);
      aObjPlayAnim(Object_handles[55], 2, 3, 2.000000f, 0);
      aTurnOnSpew(Object_handles[61], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 12.000000f,
                  3.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[62], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 12.000000f,
                  3.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[55], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 8.000000f, 2.000000f,
                  10.000000f, 0, -1);
      aTurnOnSpew(Object_handles[60], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 6.000000f, 2.000000f,
                  7.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 026: Lifter Sequence (Destroy Lifter-1)
    if (event_data->id == 4) {
      aObjMakeVulnerable(qObjSavedHandle(0));
      aSoundPlayObject(Sound_indexes[7], Object_handles[63], 1.000000f);
      aMiscShakeArea(Object_handles[63], 80.000000f, 150.000000f);
      aLightningCreate(Object_handles[64], Object_handles[63], 2.000000f, 6.000000f, 1, Texture_indexes[1], 0.300000f,
                       3, 120, 120, 220, 0);
      aObjSpark(Object_handles[63], 50.000000f, 4.000000f);
      aObjSpark(qObjSavedHandle(0), 150.000000f, 9999.000000f);
      aEmitSparks(50.000000f, qObjSavedHandle(2));
      aEmitSparks(20.000000f, Object_handles[64]);
      aObjKill(qObjSavedHandle(0), 1, 1, 2228464, 2.000000f, 2.000000f);
      aObjDelete(qObjSavedHandle(2));

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 036: Lifter Sequence (Rod 2 Smoking)
    if (event_data->id == 5) {
      aObjSpark(qObjSavedHandle(3), 20.000000f, 9999.000000f);
      aSoundPlayObject(Sound_indexes[6], Object_handles[56], 1.000000f);
      aObjPlayAnim(Object_handles[56], 2, 3, 2.000000f, 0);
      aTurnOnSpew(Object_handles[65], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 12.000000f,
                  3.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[66], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 12.000000f,
                  3.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[56], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 8.000000f, 2.000000f,
                  10.000000f, 0, -1);
      aTurnOnSpew(Object_handles[59], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 6.000000f, 2.000000f,
                  7.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 041: Lifter Sequence (Destroy Lifter-2)
    if (event_data->id == 6) {
      aObjMakeVulnerable(qObjSavedHandle(1));
      aSoundPlayObject(Sound_indexes[7], Object_handles[67], 1.000000f);
      aMiscShakeArea(Object_handles[67], 80.000000f, 150.000000f);
      aLightningCreate(Object_handles[68], Object_handles[67], 2.000000f, 6.000000f, 1, Texture_indexes[1], 0.300000f,
                       3, 120, 120, 220, 0);
      aObjSpark(Object_handles[67], 50.000000f, 4.000000f);
      aObjSpark(qObjSavedHandle(1), 150.000000f, 9999.000000f);
      aEmitSparks(50.000000f, qObjSavedHandle(3));
      aEmitSparks(20.000000f, Object_handles[68]);
      aObjKill(qObjSavedHandle(1), 1, 1, 2228464, 2.000000f, 2.000000f);
      aObjDelete(qObjSavedHandle(3));

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }

    // Script 054: USED Bomb Danger1
    if ((ScriptActionCtr_054 < 1) && (event_data->id == 8)) {
      aSetLevelTimer(qRandomValue(3.000000f, 7.000000f), 14);
      aShowHUDMessage(Message_strings[5]);
      aSoundPlayObject(Sound_indexes[9], Object_handles[81], 1.000000f);
      aEmitSparks(30.000000f, Object_handles[86]);
      aMiscViewerShake(100.000000f);
      aObjSetMovementType(Object_handles[84], 1);
      aObjSetMovementType(Object_handles[85], 1);
      aObjSetLightingColor(Object_handles[85], 1.000000f, 0.000000f, 0.000000f);
      aObjSetLightingColor(Object_handles[84], 1.000000f, 0.000000f, 0.000000f);
      aObjSetLightingDist(Object_handles[85], 90.000000f);
      aObjSetLightingDist(Object_handles[84], 90.000000f);
      aLightningCreate(Object_handles[81], Object_handles[86], 99999.000000f, 10.000000f, 1, Texture_indexes[3],
                       0.200000f, 3, 255, 100, 100, 0);
      aLightningCreate(Object_handles[82], Object_handles[86], 99999.000000f, 10.000000f, 1, Texture_indexes[3],
                       0.200000f, 3, 255, 100, 100, 0);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 194: Bomb Shake Me!
    if (event_data->id == 14) {
      aSoundPlay2D(Sound_indexes[4], 0.500000f);
      aSetLevelTimer(qRandomValue(1.000000f, 5.000000f), 14);
      aMiscViewerShake(qRandomValue(30.000000f, 70.000000f));

      // Increment the script action counter
      if (ScriptActionCtr_194 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_194++;
    }

    // Script 209: Final Countdown YouFailed!
    if ((ScriptActionCtr_209 < 1) && (event_data->id == 16)) {
      aGoalFailed(Goal_indexes[2], 1);
      aFailLevel();

      // Increment the script action counter
      if (ScriptActionCtr_209 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_209++;
    }

    // Script 195: Final Countdown Complete
    if ((ScriptActionCtr_195 < 1) && (event_data->id == 11)) {
      aSetLevelTimer(3.800000f, 16);
      aFadeWhiteAndEndlevel(4.000000f, Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_195 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_195++;
    }

    // Script 193: Final Countdown 4
    if ((ScriptActionCtr_193 < 1) && (event_data->id == 13)) {
      aAddGameMessage(Message_strings[6], Message_strings[6]);
      aShowHUDMessage(Message_strings[7]);

      // Increment the script action counter
      if (ScriptActionCtr_193 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_193++;
    }

    // Script 192: Final Countdown 3
    if ((ScriptActionCtr_192 < 1) && (event_data->id == 12)) {
      aSoundPlaySteaming("VoxMerc1Terminated.osf", 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[2]);
      aGoalEnableDisable(0, Goal_indexes[3]);
      aSetLevelTimer(7.000000f, 13);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[8]);

      // Increment the script action counter
      if (ScriptActionCtr_192 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_192++;
    }

    // Script 191: Final Countdown 2
    if ((ScriptActionCtr_191 < 1) && (event_data->id == 10)) {
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_191 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_191++;
    }

    // Script 190: Final Countdown 1
    if ((ScriptActionCtr_190 < 1) && (event_data->id == 9)) {
      aShowHUDMessage(Message_strings[10]);

      // Increment the script action counter
      if (ScriptActionCtr_190 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_190++;
    }

    // Script 124: EF1 Start
    if ((ScriptActionCtr_124 < 1) && (event_data->id == 15)) {
      aObjDelete(Object_handles[90]);
      aObjDelete(Object_handles[91]);
      aObjDelete(Object_handles[92]);
      aObjDelete(Object_handles[93]);
      if ((ScriptActionCtr_054 > 0) == false) {
        aLightningCreate(Object_handles[82], Object_handles[86], 99999.000000f, 10.000000f, 1, Texture_indexes[3],
                         0.200000f, 3, 255, 100, 100, 0);
        aLightningCreate(Object_handles[81], Object_handles[86], 99999.000000f, 10.000000f, 1, Texture_indexes[3],
                         0.200000f, 3, 255, 100, 100, 0);
        aCancelTimer(14);
        aCancelTimer(8);
      }
      aDoorLockUnlock(1, Door_handles[1]);
      aObjDelete(qObjSavedHandle(3));
      aObjDelete(qObjSavedHandle(2));
      aObjDelete(qObjSavedHandle(1));
      aObjDelete(qObjSavedHandle(0));
      aDoorLockUnlock(1, Door_handles[2]);
      aDoorLockUnlock(1, Door_handles[3]);
      aDoorLockUnlock(1, Door_handles[4]);
      aDoorSetPos(Door_handles[5], 0.000000f);
      aDoorSetPos(Door_handles[1], 0.000000f);
      aDoorSetPos(Door_handles[2], 0.000000f);
      aRoomFogSetState(1, Room_indexes[9]);
      aRoomChangeFog(Room_indexes[9], 0.800000f, 0.400000f, 0.200000f, 100.000000f, 18.000000f);
      aSetObjectTimer(Object_handles[73], 5.000000f, -1);
      aSetObjectTimer(Object_handles[75], 7.500000f, -1);
      aSetObjectTimer(Object_handles[77], 10.000000f, -1);
      aSetObjectTimer(Object_handles[79], 12.500000f, -1);
      aSetObjectTimer(Object_handles[81], 14.000000f, -1);
      aCinematicSimple(Path_indexes[16], Message_strings[1], Object_handles[94], 18.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 024: Lifter Sequence (Pick Up Rod-1)
    if (event_data->goal_uid == 0) {
      aAIGoalPickUpObjectRad(event_data->it_handle, 0, qObjSavedHandle(2), 1.000000f, 3, 65792, 2);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 025: Lifter Sequence (Transport Rod-1)
    if (event_data->goal_uid == 2) {
      aAISetMaxSpeed(event_data->it_handle, 30.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[14], 4356, 4, 3);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 034: Lifter Sequence (Go to wait with Rod-1)
    if (event_data->goal_uid == 4) {
      aObjFireWeapon("BlackShark", 0, Object_handles[63]);
      aMiscShakeArea(Object_handles[63], 40.000000f, 150.000000f);
      aSoundPlayObject(Sound_indexes[7], Object_handles[63], 0.600000f);
      aLightningCreate(event_data->it_handle, Object_handles[63], 3.000000f, 4.000000f, 1, Texture_indexes[1],
                       0.200000f, 2, 100, 100, 180, 0);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aObjSpark(qObjSavedHandle(0), 60.000000f, 9999.000000f);
      aAISetState(0, event_data->it_handle);
      aEmitSparks(20.000000f, qObjSavedHandle(2));
      aObjSpark(Object_handles[63], 20.000000f, 4.000000f);
      aObjDeform(qObjSavedHandle(2), 0.100000f, 5.000000f);
      aSetLevelTimer(3.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 038: Lifter Sequence (Pick Up Rod-2)
    if (event_data->goal_uid == 1) {
      aAIGoalPickUpObjectRad(event_data->it_handle, 0, qObjSavedHandle(3), 1.000000f, 3, 65792, 3);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 039: Lifter Sequence (Transport Rod-2)
    if (event_data->goal_uid == 3) {
      aAISetMaxSpeed(event_data->it_handle, 30.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[15], 4356, 5, 3);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 040: Lifter Sequence (Go to wait with Rod-2)
    if (event_data->goal_uid == 5) {
      aObjFireWeapon("BlackShark", 0, Object_handles[67]);
      aMiscShakeArea(Object_handles[67], 40.000000f, 150.000000f);
      aSoundPlayObject(Sound_indexes[7], Object_handles[67], 0.600000f);
      aLightningCreate(event_data->it_handle, Object_handles[67], 3.000000f, 4.000000f, 1, Texture_indexes[1],
                       0.200000f, 2, 100, 100, 180, 0);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aObjSpark(qObjSavedHandle(1), 60.000000f, 9999.000000f);
      aAISetState(0, event_data->it_handle);
      aEmitSparks(20.000000f, qObjSavedHandle(3));
      aObjSpark(Object_handles[67], 20.000000f, 4.000000f);
      aObjDeform(qObjSavedHandle(3), 0.100000f, 5.000000f);
      aSetLevelTimer(3.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 123: City Move BottomToLeft
    if (event_data->goal_uid == 9) {
      if (qRandomValue(0.000000f, 1.000000f) > 0.330000f) {
        if (qRandomValue(0.000000f, 1.000000f) > 0.500000f) {
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[25], 4096, 6, 3);
        } else {
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[26], 4096, 6, 3);
        }
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[24], 4096, 6, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }

    // Script 122: City Move RightToBottom
    if (event_data->goal_uid == 8) {
      if (qRandomValue(0.000000f, 1.000000f) > 0.500000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[33], 4096, 9, 3);
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[32], 4096, 9, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }

    // Script 121: City Move TopToRight
    if (event_data->goal_uid == 7) {
      if (qRandomValue(0.000000f, 1.000000f) > 0.330000f) {
        if (qRandomValue(0.000000f, 1.000000f) > 0.500000f) {
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[31], 4096, 8, 3);
        } else {
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[30], 4096, 8, 3);
        }
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[29], 4096, 8, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }

    // Script 084: City Move LeftToTop
    if (event_data->goal_uid == 6) {
      if (qRandomValue(0.000000f, 1.000000f) > 0.500000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[28], 4096, 7, 3);
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[27], 4096, 7, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }

    // Script 161: Patrol Repeat
    if (event_data->goal_uid == 10) {
      if (qRandomChance(0.500000f) == true) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[39], 4096, 10, 0);
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[38], 4096, 10, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_161 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_161++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 023: Lifter Sequence (Rod Created-1)
    if ((event_data->id == Matcen_indexes[0]) && (1)) {
      aMiscShakeArea(event_data->it_handle, 50.000000f, 150.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[55], 1.000000f);
      aObjPlayAnim(Object_handles[55], 3, 4, 2.000000f, 0);
      aStoreObjectInPositionClipboard(Object_handles[57]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 2);
      aObjDeform(event_data->it_handle, 0.200000f, 0.500000f);
      aLightningCreate(event_data->it_handle, Object_handles[55], 25.000000f, 7.000000f, 1, Texture_indexes[0],
                       0.400000f, 3, 60, 200, 45, 0);
      aLightningCreate(event_data->it_handle, Object_handles[60], 25.000000f, 7.000000f, 1, Texture_indexes[0],
                       0.300000f, 3, 60, 200, 45, 0);
      aEmitSparks(50.000000f, event_data->it_handle);
      aSetLevelTimer(24.000000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 020: Lifter Sequence (Created-1)
    if ((event_data->id == Matcen_indexes[3]) && (1)) {
      aObjMakeInvuln(event_data->it_handle, 9999);
      aAISetMaxSpeed(event_data->it_handle, 40.000000f);
      aObjSaveHandle(event_data->it_handle, 0);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[13], 4352, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 035: Lifter Sequence (Rod Created-2)
    if ((event_data->id == Matcen_indexes[1]) && (1)) {
      aMiscShakeArea(event_data->it_handle, 50.000000f, 150.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[56], 1.000000f);
      aObjPlayAnim(Object_handles[56], 3, 4, 2.000000f, 0);
      aStoreObjectInPositionClipboard(Object_handles[58]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 3);
      aObjDeform(event_data->it_handle, 0.200000f, 0.500000f);
      aLightningCreate(event_data->it_handle, Object_handles[56], 25.000000f, 7.000000f, 1, Texture_indexes[0],
                       0.400000f, 3, 60, 200, 45, 0);
      aLightningCreate(event_data->it_handle, Object_handles[59], 25.000000f, 7.000000f, 1, Texture_indexes[0],
                       0.300000f, 3, 60, 200, 45, 0);
      aEmitSparks(50.000000f, event_data->it_handle);
      aSetLevelTimer(24.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }

    // Script 037: Lifter Sequence (Created-2)
    if ((event_data->id == Matcen_indexes[2]) && (1)) {
      aObjMakeInvuln(event_data->it_handle, 9999);
      aAISetMaxSpeed(event_data->it_handle, 40.000000f);
      aObjSaveHandle(event_data->it_handle, 1);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[13], 4352, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_LEVEL_GOAL_COMPLETE: {
    tOSIRISEVTLEVELGOALCOMPLETE *event_data = &data->evt_level_goal_complete;

    // Script 001: INIT SoftWind
    if (qGoalCompleted(Goal_indexes[0]) == true) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[27], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[28], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[29], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[30], 1.000000f);
      aTurnOnSpew(Object_handles[27], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  8.000000f, 60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[28], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  8.000000f, 60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[29], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  8.000000f, 60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[30], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  8.000000f, 60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 083: INIT City Ambient Movement
    if ((ScriptActionCtr_083 < 1) && (qGoalCompleted(Goal_indexes[5]) == 1)) {
      aAIGoalFollowPathSimple(Object_handles[184], Path_indexes[24], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[185], Path_indexes[25], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[186], Path_indexes[26], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[187], Path_indexes[25], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[188], Path_indexes[27], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[189], Path_indexes[27], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[190], Path_indexes[27], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[191], Path_indexes[27], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[192], Path_indexes[27], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[193], Path_indexes[27], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[194], Path_indexes[28], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[195], Path_indexes[28], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[196], Path_indexes[28], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[197], Path_indexes[28], 4352, 7, 3);
      aAIGoalFollowPathSimple(Object_handles[198], Path_indexes[29], 4352, 8, 3);
      aAIGoalFollowPathSimple(Object_handles[199], Path_indexes[30], 4352, 8, 3);
      aAIGoalFollowPathSimple(Object_handles[200], Path_indexes[31], 4352, 8, 3);
      aAIGoalFollowPathSimple(Object_handles[201], Path_indexes[31], 4352, 8, 3);
      aAIGoalFollowPathSimple(Object_handles[202], Path_indexes[30], 4352, 8, 3);
      aAIGoalFollowPathSimple(Object_handles[203], Path_indexes[32], 4352, 9, 3);
      aAIGoalFollowPathSimple(Object_handles[204], Path_indexes[32], 4352, 9, 3);
      aAIGoalFollowPathSimple(Object_handles[205], Path_indexes[32], 4352, 9, 3);
      aAIGoalFollowPathSimple(Object_handles[206], Path_indexes[33], 4352, 9, 3);
      aAIGoalFollowPathSimple(Object_handles[207], Path_indexes[33], 4352, 9, 3);
      aAIGoalFollowPathSimple(Object_handles[208], Path_indexes[33], 4352, 9, 3);
      aAIGoalFollowPathSimple(Object_handles[209], Path_indexes[24], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[210], Path_indexes[26], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[211], Path_indexes[25], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[212], Path_indexes[24], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[213], Path_indexes[26], 4352, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[214], Path_indexes[25], 4352, 6, 3);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }

    // Script 130: INIT Welders Area
    if ((ScriptActionCtr_130 < 1) && (qGoalCompleted(Goal_indexes[6]) == 1)) {
      aTurnOnSpew(Object_handles[239], 1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.080000f, -1.000000f,
                  2.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[239], 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.080000f, -1.000000f,
                  2.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[240], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.150000f, -1.000000f,
                  3.000000f, 35.000000f, 0, -1);
      aObjSpark(Object_handles[164], 30.000000f, 99999.000000f);
      aObjMakeInvuln(Object_handles[164], 99999);
      aObjMakeInvuln(Object_handles[163], 99999);
      aObjMakeInvuln(Object_handles[162], 99999);
      aObjMakeInvuln(Object_handles[161], 99999);
      aPhysFlags(1, 58722304, Object_handles[239]);
      aAISetMaxSpeed(Object_handles[239], 0.000000f);
      aAISetTeam(196608, Object_handles[239]);
      aAISetTeam(196608, Object_handles[241]);
      aAISetTeam(196608, Object_handles[242]);
      aAISetTeam(196608, Object_handles[243]);

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }

    // Script 160: INIT Patrols
    if ((ScriptActionCtr_160 < 1) && (qGoalCompleted(Goal_indexes[6]) == 1)) {
      aAIGoalFollowPathSimple(Object_handles[262], Path_indexes[38], 4352, 10, 0);
      aAIGoalFollowPathSimple(Object_handles[263], Path_indexes[38], 4352, 10, 0);
      aAIGoalFollowPathSimple(Object_handles[264], Path_indexes[38], 4352, 10, 0);
      aAIGoalFollowPathSimple(Object_handles[265], Path_indexes[39], 4352, 10, 0);
      aAIGoalFollowPathSimple(Object_handles[266], Path_indexes[39], 4352, 10, 0);
      aAIGoalFollowPathSimple(Object_handles[267], Path_indexes[39], 4352, 10, 0);
      aAIGoalFollowPathSimple(Object_handles[268], Path_indexes[39], 4352, 10, 0);

      // Increment the script action counter
      if (ScriptActionCtr_160 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_160++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 082: INIT Random Ambient Stuff
    if ((ScriptActionCtr_082 < 1) && (1)) {
      aObjPlayAnim(Object_handles[0], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[1], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[2], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[3], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[4], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[5], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[6], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[7], 1, 3, 2.000000f, 1);
      aObjSetShields(Object_handles[8], 800.000000f);
      aObjSetShields(Object_handles[9], 800.000000f);
      aObjSetShields(Object_handles[10], 800.000000f);
      aObjSetShields(Object_handles[11], 800.000000f);
      aObjSetShields(Object_handles[12], 800.000000f);
      aObjSetShields(Object_handles[13], 800.000000f);
      aObjSetShields(Object_handles[14], 800.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }

    // Script 032: Intro PostEvents
    if ((ScriptActionCtr_032 < 1) && (1)) {
      aObjGhostSet(1, Object_handles[35]);
      aRoomChangeFog(Room_indexes[8], 0.600000f, 0.200000f, 0.100000f, 1500.000000f, 60.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2027::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 053: IntroCamera-1.5
    if ((ScriptActionCtr_053 < 1) && (1 == true)) {
      aMusicSetRegionAll(1);
      aObjGhostSet(0, Object_handles[33]);
      aAISetMaxSpeed(Object_handles[33], 60.000000f);
      aAIGoalFollowPathSimple(Object_handles[33], Path_indexes[1], 1048832, -1, 3);
      aCinematicSimple(Path_indexes[2], Message_strings[1], Object_handles[37], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0820::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 017: IntroCamera-2
    if ((ScriptActionCtr_017 < 1) && (1 == true)) {
      aObjGhostSet(1, Object_handles[33]);
      aAISetMaxSpeed(Object_handles[34], 20.000000f);
      aObjGhostSet(0, Object_handles[34]);
      aAIGoalFollowPathSimple(Object_handles[34], Path_indexes[3], 1048832, -1, 3);
      aSoundPlaySteaming("VoxMerc1Airlock.osf", 1.000000f);
      aCinematicSimple(Path_indexes[4], Message_strings[1], Object_handles[38], 7.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0831::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 018: IntroCamera-3
    if ((ScriptActionCtr_018 < 1) && (1 == true)) {
      aObjGhostSet(1, Object_handles[34]);
      aObjGhostSet(0, Object_handles[35]);
      aTurnOnSpew(Object_handles[39], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 19.000000f,
                  3.000000f, 10.000000f, 0, 7);
      aTurnOnSpew(Object_handles[40], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 19.000000f,
                  3.000000f, 10.000000f, 0, 6);
      aTurnOnSpew(Object_handles[41], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 19.000000f,
                  3.000000f, 10.000000f, 0, 5);
      aTurnOnSpew(Object_handles[42], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 19.000000f,
                  3.000000f, 10.000000f, 0, 4);
      aTurnOnSpew(Object_handles[43], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 15.000000f,
                  5.000000f, 40.000000f, 0, 3);
      aTurnOnSpew(Object_handles[44], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 15.000000f,
                  5.000000f, 40.000000f, 0, 2);
      aCinematicSimple(Path_indexes[5], Message_strings[1], Object_handles[45], 6.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0832::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 019: IntroCamera-4
    if ((ScriptActionCtr_019 < 1) && (1 == true)) {
      aRoomSetFog(Room_indexes[8], 0.500000f, 0.150000f, 0.050000f, 1500.000000f);
      aRoomFogSetState(1, Room_indexes[8]);
      aRoomChangeFog(Room_indexes[8], 0.600000f, 0.200000f, 0.100000f, 300.000000f, 12.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[46], 1.000000f);
      aTurnOnSpew(Object_handles[47], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, 17.000000f,
                  2.000000f, 11.000000f, 0, 11);
      aTurnOnSpew(Object_handles[48], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, 17.000000f,
                  2.000000f, 11.000000f, 0, 10);
      aTurnOnSpew(Object_handles[49], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, 17.000000f,
                  2.000000f, 11.000000f, 0, 9);
      aTurnOnSpew(Object_handles[50], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, 17.000000f,
                  2.000000f, 11.000000f, 0, 8);
      aSetLevelTimer(3.000000f, 2);
      aCinematicSimple(Path_indexes[6], Message_strings[1], Object_handles[51], 6.500000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0836::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 027: IntroCamera-5 (DISABLED)
    if ((ScriptActionCtr_027 < 1) && (0 == true)) {
      aObjGhostSet(0, Object_handles[32]);
      aObjGhostSet(0, Object_handles[31]);
      aAISetMaxSpeed(Object_handles[32], 40.000000f);
      aAISetMaxSpeed(Object_handles[31], 40.000000f);
      aAIGoalFollowPathSimple(Object_handles[32], Path_indexes[7], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[31], Path_indexes[8], 4352, -1, 3);
      aCinematicSimple(Path_indexes[9], Message_strings[1], Object_handles[52], 5.500000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 028: IntroCamera-6
    if ((ScriptActionCtr_028 < 1) && (1 == true)) {
      aObjGhostSet(1, Object_handles[32]);
      aObjGhostSet(1, Object_handles[31]);
      aTurnOnSpew(Object_handles[53], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 1.000000f, 5.000000f,
                  20.000000f, 0, 3);
      aTurnOnSpew(Object_handles[54], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 1.000000f, 5.000000f,
                  20.000000f, 0, 2);
      aSoundPlayObject(Sound_indexes[4], Object_handles[35], 1.000000f);
      aAISetMaxSpeed(Object_handles[35], 10.000000f);
      aAIGoalFollowPathSimple(Object_handles[35], Path_indexes[10], 1048832, -1, 3);
      aDoorLockUnlock(1, Door_handles[0]);
      aSetLevelTimer(4.000000f, 1);
      aCinematicIntro(Path_indexes[11], Message_strings[1], Object_handles[33], Path_indexes[12], 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0888::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 049: INIT Node 6
    if (1) {
      aObjPlayAnim(data->me_handle, 1, 3, 2.000000f, 1);
      aObjMakeInvuln(data->me_handle, 99999);
      aObjSetLightingDist(data->me_handle, 30.000000f);
      aObjSetLightingColor(data->me_handle, 0.000000f, 1.000000f, 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0887::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 048: INIT Node 5
    if (1) {
      aObjPlayAnim(data->me_handle, 1, 3, 2.000000f, 1);
      aObjMakeInvuln(data->me_handle, 99999);
      aObjSetLightingDist(data->me_handle, 30.000000f);
      aObjSetLightingColor(data->me_handle, 0.000000f, 1.000000f, 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0886::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 047: INIT Node 4
    if (1) {
      aObjPlayAnim(data->me_handle, 1, 3, 2.000000f, 1);
      aObjMakeInvuln(data->me_handle, 99999);
      aObjSetLightingDist(data->me_handle, 30.000000f);
      aObjSetLightingColor(data->me_handle, 0.000000f, 1.000000f, 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 055: EF1 Part1
    if ((ScriptActionCtr_055 < 1) && (1)) {
      aTurnOnSpew(Object_handles[102], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 3);
      aTurnOnSpew(Object_handles[74], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  10.000000f, 60.000000f, 0, 2);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(data->me_handle, 1, 2, 3145968, 0.600000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_182A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 046: INIT Node 3
    if (1) {
      aObjPlayAnim(data->me_handle, 1, 3, 2.000000f, 1);
      aObjMakeInvuln(data->me_handle, 99999);
      aObjSetLightingDist(data->me_handle, 30.000000f);
      aObjSetLightingColor(data->me_handle, 0.000000f, 1.000000f, 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 167: EF1 Part2
    if ((ScriptActionCtr_167 < 1) && (1)) {
      aTurnOnSpew(Object_handles[100], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 7);
      aTurnOnSpew(Object_handles[101], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 6);
      aTurnOnSpew(Object_handles[72], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  10.000000f, 60.000000f, 0, 5);
      aTurnOnSpew(Object_handles[76], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  10.000000f, 60.000000f, 0, 4);
      aObjMakeVulnerable(Object_handles[71]);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(Object_handles[71], 1, 2, 3145968, 0.600000f, 1.000000f);
      aObjKill(data->me_handle, 1, 2, 3145968, 0.500000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_167 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_167++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_088A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 045: INIT Node 2
    if (1) {
      aObjPlayAnim(data->me_handle, 1, 3, 2.000000f, 1);
      aObjMakeInvuln(data->me_handle, 99999);
      aObjSetLightingDist(data->me_handle, 30.000000f);
      aObjSetLightingColor(data->me_handle, 0.000000f, 1.000000f, 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 168: EF1 Part3
    if ((ScriptActionCtr_168 < 1) && (1)) {
      aTurnOnSpew(Object_handles[98], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  26.000000f, 80.000000f, 0, 11);
      aTurnOnSpew(Object_handles[99], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  26.000000f, 80.000000f, 0, 10);
      aTurnOnSpew(Object_handles[70], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  10.000000f, 60.000000f, 0, 9);
      aTurnOnSpew(Object_handles[78], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  10.000000f, 60.000000f, 0, 8);
      aObjMakeVulnerable(Object_handles[69]);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(Object_handles[69], 1, 2, 3145968, 0.600000f, 1.000000f);
      aObjKill(data->me_handle, 1, 2, 3145968, 1.000000f, 1.200000f);

      // Increment the script action counter
      if (ScriptActionCtr_168 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_168++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0889::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 044: INIT Node 1
    if (1) {
      aObjPlayAnim(data->me_handle, 1, 3, 2.000000f, 1);
      aObjMakeInvuln(data->me_handle, 99999);
      aObjSetLightingDist(data->me_handle, 30.000000f);
      aObjSetLightingColor(data->me_handle, 0.000000f, 1.000000f, 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 169: EF1 Part4
    if ((ScriptActionCtr_169 < 1) && (1)) {
      aTurnOnSpew(Object_handles[97], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  22.000000f, 80.000000f, 0, 13);
      aTurnOnSpew(Object_handles[80], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  8.000000f, 60.000000f, 0, 12);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(data->me_handle, 1, 2, 3145968, 0.800000f, 1.200000f);

      // Increment the script action counter
      if (ScriptActionCtr_169 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_169++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_188C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: PICKUP Bomb
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAddObjectToInventoryNamed(data->me_handle, qPlayerClosest(data->me_handle, -1), Message_strings[2], 0);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 050: INIT Bomb
    if (1) {
      aUserFlagSet(0, 0);
      aObjSetMovementType(Object_handles[84], 0);
      aObjSetMovementType(Object_handles[85], 0);
      aObjSetLightingDist(Object_handles[84], 0.000000f);
      aObjSetLightingDist(Object_handles[85], 0.000000f);
      aObjGhostSet(1, Object_handles[86]);
      aAddObjectToInventoryNamed(data->me_handle, qPlayerClosest(data->me_handle, -1), Message_strings[2], 0);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 051: USED Bomb
    if ((qObjIsPlayer(event_data->it_handle) == true) && (1)) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[86]) < 40.000000f) {
        aMusicSetRegionAll(6);
        aGoalCompleted(Goal_indexes[1], 1);
        aUserFlagSet(0, 1);
        aObjGhostSet(0, Object_handles[86]);
        aMiscViewerShake(100.000000f);
        aEmitSparks(50.000000f, Object_handles[86]);
        aLightningCreate(Object_handles[69], Object_handles[86], 99999.000000f, 5.000000f, 2, Texture_indexes[3],
                         0.300000f, 3, 255, 100, 100, 0);
        aLightningCreate(Object_handles[71], Object_handles[86], 99999.000000f, 5.000000f, 2, Texture_indexes[3],
                         0.300000f, 3, 255, 100, 100, 0);
        aLightningCreate(Object_handles[73], Object_handles[86], 99999.000000f, 5.000000f, 2, Texture_indexes[3],
                         0.300000f, 3, 255, 100, 100, 0);
        aLightningCreate(Object_handles[75], Object_handles[86], 99999.000000f, 5.000000f, 2, Texture_indexes[3],
                         0.300000f, 3, 255, 100, 100, 0);
        aLightningCreate(Object_handles[77], Object_handles[86], 99999.000000f, 5.000000f, 2, Texture_indexes[3],
                         0.300000f, 3, 255, 100, 100, 0);
        aLightningCreate(Object_handles[79], Object_handles[86], 99999.000000f, 5.000000f, 2, Texture_indexes[3],
                         0.300000f, 3, 255, 100, 100, 0);
        aSetLevelTimer(qMathAddFloat(120.000000f, qUserVarValue(2)), 11);
        aTimerShow(11);
        aSetLevelTimer(3.000000f, 9);
        aSetLevelTimer(20.000000f, 10);
        aSetLevelTimer(45.000000f, 12);
        aSetLevelTimer(qMathAddFloat(60.000000f, qUserVarValue(2)), 8);
        aShowHUDMessage(Message_strings[3]);
        aSoundPlayObject(Sound_indexes[8], event_data->it_handle, 1.000000f);
      } else {
        aShowColoredHUDMessageObj(255, 0, 0, Message_strings[4], event_data->it_handle);
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }

    // Script 210: Testing Clutter DELETE
    if ((ScriptActionCtr_210 < 1) && (0 == true)) {
      aObjDelete(Object_handles[158]);
      aObjDelete(Object_handles[159]);
      aObjDelete(Object_handles[67]);
      aObjDelete(Object_handles[63]);
      aObjDelete(Object_handles[143]);
      aObjDelete(Object_handles[56]);
      aObjDelete(Object_handles[55]);
      aObjDelete(Object_handles[85]);
      aObjDelete(Object_handles[84]);
      aObjDelete(Object_handles[3]);
      aObjDelete(Object_handles[2]);
      aObjDelete(Object_handles[1]);
      aObjDelete(Object_handles[0]);
      aObjDelete(Object_handles[8]);
      aObjDelete(Object_handles[69]);
      aObjDelete(Object_handles[71]);
      aObjDelete(Object_handles[73]);
      aObjDelete(Object_handles[75]);
      aObjDelete(Object_handles[77]);
      aObjDelete(Object_handles[79]);
      aObjDelete(Object_handles[103]);
      aObjDelete(Object_handles[104]);
      aObjDelete(Object_handles[105]);
      aObjDelete(Object_handles[106]);
      aObjDelete(Object_handles[160]);
      aObjDelete(Object_handles[109]);
      aObjDelete(Object_handles[108]);
      aObjDelete(Object_handles[107]);
      aObjDelete(Object_handles[9]);
      aObjDelete(Object_handles[10]);
      aObjDelete(Object_handles[11]);
      aObjDelete(Object_handles[12]);
      aObjDelete(Object_handles[13]);
      aObjDelete(Object_handles[14]);
      aObjDelete(Object_handles[7]);
      aObjDelete(Object_handles[6]);
      aObjDelete(Object_handles[5]);
      aObjDelete(Object_handles[4]);
      aObjDelete(Object_handles[161]);
      aObjDelete(Object_handles[162]);
      aObjDelete(Object_handles[163]);
      aObjDelete(Object_handles[164]);

      // Increment the script action counter
      if (ScriptActionCtr_210 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_210++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0885::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 056: EF1 Part5
    if ((ScriptActionCtr_056 < 1) && (1)) {
      aTurnOnSpew(Object_handles[95], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 20.000000f,
                  30.000000f, 70.000000f, 0, 14);
      aTurnOnSpew(Object_handles[96], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 20.000000f,
                  30.000000f, 70.000000f, 0, 15);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 170: EF2 Start
    if (1) {
      aSetObjectTimer(Object_handles[103], 2.000000f, -1);
      aSetObjectTimer(Object_handles[104], 2.500000f, -1);
      aSetObjectTimer(Object_handles[105], 3.000000f, -1);
      aSetObjectTimer(Object_handles[106], 3.500000f, -1);
      aSetObjectTimer(Object_handles[87], 5.250000f, -1);
      aSetObjectTimer(Object_handles[107], 6.500000f, -1);
      aSetObjectTimer(Object_handles[108], 7.000000f, -1);
      aSetObjectTimer(Object_handles[109], 7.500000f, -1);
      aObjGhostSet(0, Object_handles[87]);
      aStoreObjectInPositionClipboard(Object_handles[110]);
      aMoveObjectToPositionClipboard(Object_handles[87]);
      aAIGoalFollowPathSimple(Object_handles[87], Path_indexes[17], 4352, -1, 3);
      aRoomFogSetState(1, Room_indexes[10]);
      aRoomChangeFog(Room_indexes[10], 0.800000f, 0.500000f, 0.200000f, 200.000000f, 10.000000f);
      aCinematicSimple(Path_indexes[18], Message_strings[1], Object_handles[111], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_170 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_170++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0877::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 179: EFPart8
    if ((ScriptActionCtr_179 < 1) && (1)) {
      aTurnOnSpew(Object_handles[112], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.200000f, 0.200000f, 20.000000f,
                  50.000000f, 60.000000f, 0, 10);

      // Increment the script action counter
      if (ScriptActionCtr_179 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_179++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0878::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 178: EFPart7
    if ((ScriptActionCtr_178 < 1) && (1)) {
      aObjKill(Object_handles[113], 1, 2, 2294000, 0.000000f, 0.200000f);
      aTurnOnSpew(Object_handles[114], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.200000f, 0.200000f, 20.000000f,
                  50.000000f, 60.000000f, 0, 9);

      // Increment the script action counter
      if (ScriptActionCtr_178 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_178++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0879::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 177: EFPart6
    if ((ScriptActionCtr_177 < 1) && (1)) {
      aObjKill(Object_handles[115], 1, 2, 2294000, 0.000000f, 0.700000f);
      aObjKill(Object_handles[116], 1, 2, 2294000, 0.000000f, 0.700000f);
      aObjKill(Object_handles[117], 1, 2, 2294000, 0.000000f, 0.700000f);
      aObjKill(Object_handles[118], 1, 2, 2294000, 0.000000f, 0.700000f);
      aTurnOnSpew(Object_handles[119], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 8);

      // Increment the script action counter
      if (ScriptActionCtr_177 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_177++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1171::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 176: EFPart5
    if ((ScriptActionCtr_176 < 1) && (1)) {
      aDoorSetPos(Door_handles[5], 1.000000f);
      aTurnOnSpew(Object_handles[120], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.200000f, 0.250000f, 20.000000f,
                  55.000000f, 60.000000f, 0, 7);
      aTurnOnSpew(Object_handles[121], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.600000f, 0.150000f, 20.000000f,
                  20.000000f, 80.000000f, 0, 6);
      aRoomSetWind(Room_indexes[10], 0.000000f, -1.000000f, 0.000000f, 25.000000f);
      aObjKill(data->me_handle, 1, 2, 2294000, 0.400000f, 0.400000f);
      aObjKill(Object_handles[122], 1, 2, 2228448, 0.600000f, 0.700000f);
      aObjKill(Object_handles[123], 0, 2, 2097328, 0.350000f, 1.000000f);
      aObjKill(Object_handles[124], 1, 2, 196816, 0.350000f, 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_176 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_176++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 175: EFPart4
    if ((ScriptActionCtr_175 < 1) && (1)) {
      aTurnOnSpew(Object_handles[125], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 5);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(data->me_handle, 0, 2, 65696, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_175 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_175++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 174: EFPart3
    if ((ScriptActionCtr_174 < 1) && (1)) {
      aTurnOnSpew(Object_handles[126], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 4);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(data->me_handle, 0, 2, 65696, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_174 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_174++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 173: EFPart2
    if ((ScriptActionCtr_173 < 1) && (1)) {
      aTurnOnSpew(Object_handles[127], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 3);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(data->me_handle, 0, 2, 65696, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_173 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_173++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 172: EFPart1
    if ((ScriptActionCtr_172 < 1) && (1)) {
      aTurnOnSpew(Object_handles[128], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, 20.000000f,
                  30.000000f, 80.000000f, 0, 2);
      aObjMakeVulnerable(data->me_handle);
      aObjKill(data->me_handle, 0, 2, 65696, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_172 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_172++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1170::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 180: EF3 Start
    if (1) {
      aSetObjectTimer(Object_handles[129], 7.400000f, -1);
      aSetObjectTimer(Object_handles[130], 6.800000f, -1);
      aSetObjectTimer(Object_handles[131], 6.400000f, -1);
      aSetObjectTimer(Object_handles[132], 5.600000f, -1);
      aSetObjectTimer(Object_handles[133], 4.800000f, -1);
      aSetObjectTimer(Object_handles[134], 4.000000f, -1);
      aSetObjectTimer(Object_handles[135], 3.000000f, -1);
      aSetObjectTimer(Object_handles[136], 2.000000f, -1);
      aSetObjectTimer(Object_handles[137], 1.000000f, -1);
      aRoomFogSetState(1, Room_indexes[11]);
      aRoomChangeFog(Room_indexes[11], 0.800000f, 0.400000f, 0.100000f, 250.000000f, 9.000000f);
      aAISetMaxSpeed(Object_handles[88], 16.000000f);
      aAISetMaxSpeed(Object_handles[89], 16.000000f);
      aObjGhostSet(0, Object_handles[89]);
      aObjGhostSet(0, Object_handles[88]);
      aTurnOnSpew(Object_handles[138], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 3);
      aTurnOnSpew(Object_handles[137], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 2);
      aAIGoalFollowPathSimple(Object_handles[88], Path_indexes[19], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[89], Path_indexes[20], 4352, -1, 3);
      aCinematicSimple(Path_indexes[21], Message_strings[1], Object_handles[139], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_180 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_180++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0988::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 189: EF3Part9
    if ((ScriptActionCtr_189 < 1) && (1)) {
      aTurnOnSpew(Object_handles[129], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.150000f, 6.000000f,
                  45.000000f, 90.000000f, 0, 6);

      // Increment the script action counter
      if (ScriptActionCtr_189 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_189++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0981::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 188: EF3Part8
    if ((ScriptActionCtr_188 < 1) && (1)) {
      aTurnOnSpew(Object_handles[130], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.160000f, 6.000000f,
                  60.000000f, 90.000000f, 0, 5);
      aTurnOnSpew(Object_handles[140], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 5.000000f,
                  70.000000f, 150.000000f, 0, 4);
      aTurnOnSpew(Object_handles[141], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 5.000000f,
                  70.000000f, 150.000000f, 0, 3);
      aTurnOnSpew(Object_handles[142], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 5.000000f,
                  70.000000f, 150.000000f, 0, 2);

      // Increment the script action counter
      if (ScriptActionCtr_188 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_188++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0980::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 187: EF3Part7
    if ((ScriptActionCtr_187 < 1) && (1)) {
      aObjKill(Object_handles[88], 1, 1, 2162832, 0.650000f, 0.650000f);
      aObjKill(Object_handles[89], 1, 1, 2097296, 0.500000f, 0.500000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      aTurnOnSpew(Object_handles[131], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 17);
      aTurnOnSpew(Object_handles[130], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.160000f, 5.000000f,
                  25.000000f, 90.000000f, 0, 16);

      // Increment the script action counter
      if (ScriptActionCtr_187 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_187++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 186: EF3Part6
    if ((ScriptActionCtr_186 < 1) && (1)) {
      aTurnOnSpew(Object_handles[132], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 15);
      aTurnOnSpew(Object_handles[131], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 14);

      // Increment the script action counter
      if (ScriptActionCtr_186 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_186++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 185: EF3Part5
    if ((ScriptActionCtr_185 < 1) && (1)) {
      aTurnOnSpew(Object_handles[133], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 13);
      aTurnOnSpew(Object_handles[132], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 12);

      // Increment the script action counter
      if (ScriptActionCtr_185 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_185++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 184: EF3Part4
    if ((ScriptActionCtr_184 < 1) && (1)) {
      aTurnOnSpew(Object_handles[134], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 11);
      aTurnOnSpew(Object_handles[133], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 10);

      // Increment the script action counter
      if (ScriptActionCtr_184 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_184++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 183: EF3Part3
    if ((ScriptActionCtr_183 < 1) && (1)) {
      aTurnOnSpew(Object_handles[135], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 9);
      aTurnOnSpew(Object_handles[134], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 8);

      // Increment the script action counter
      if (ScriptActionCtr_183 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_183++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_117B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 182: EF3Part2
    if ((ScriptActionCtr_182 < 1) && (1)) {
      aTurnOnSpew(Object_handles[136], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 7);
      aTurnOnSpew(Object_handles[135], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 6);

      // Increment the script action counter
      if (ScriptActionCtr_182 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_182++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 181: EF3Part1
    if ((ScriptActionCtr_181 < 1) && (1)) {
      aTurnOnSpew(Object_handles[137], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 6.000000f,
                  60.000000f, 80.000000f, 0, 5);
      aTurnOnSpew(Object_handles[136], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 5.000000f,
                  30.000000f, 150.000000f, 0, 4);

      // Increment the script action counter
      if (ScriptActionCtr_181 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_181++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1984::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 198: EF4 Start
    if ((ScriptActionCtr_198 < 1) && (1)) {
      aObjSetLightingDist(Object_handles[143], 140.000000f);
      aRoomChangeFog(Room_indexes[12], 0.000000f, 0.000000f, 0.000000f, 175.000000f, 8.000000f);
      aTurnOnSpew(Object_handles[144], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, 2);
      aTurnOnSpew(Object_handles[145], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, 2);
      aTurnOnSpew(Object_handles[146], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, 2);
      aTurnOnSpew(Object_handles[147], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, 2);
      aStartEndlevelSequencePath(Path_indexes[22], Path_indexes[23], 8.000000f, Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_198 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_198++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0875::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 072: INIT LNipple 5
    if (1) {
      aObjGhostSet(1, Object_handles[149]);
      aObjMakeInvuln(data->me_handle, 99999);
      aSetObjectTimer(data->me_handle, 91.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 064: Lightning Nipple 5
    if (1) {
      aMiscShakeArea(data->me_handle, 40.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[149], 80.000000f, 2.600000f);
      aLightningCreate(Object_handles[149], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aLightningCreate(data->me_handle, Object_handles[149], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[149], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0865::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 071: INIT LNipple 4
    if (1) {
      aObjGhostSet(1, Object_handles[151]);
      aObjMakeInvuln(data->me_handle, 99999);
      aSetObjectTimer(data->me_handle, 92.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 063: Lightning Nipple 4
    if (1) {
      aMiscShakeArea(data->me_handle, 40.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[151], 80.000000f, 2.600000f);
      aLightningCreate(Object_handles[151], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aLightningCreate(data->me_handle, Object_handles[151], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[151], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0864::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 070: INIT LNipple 3
    if (1) {
      aObjGhostSet(1, Object_handles[153]);
      aObjMakeInvuln(data->me_handle, 99999);
      aSetObjectTimer(data->me_handle, 93.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 062: Lightning Nipple 3
    if (1) {
      aMiscShakeArea(data->me_handle, 40.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[153], 80.000000f, 2.600000f);
      aLightningCreate(Object_handles[153], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aLightningCreate(data->me_handle, Object_handles[153], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[153], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0863::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 069: INIT LNipple 2
    if (1) {
      aObjGhostSet(1, Object_handles[155]);
      aObjMakeInvuln(data->me_handle, 99999);
      aSetObjectTimer(data->me_handle, 94.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 061: Lightning Nipple 2
    if (1) {
      aMiscShakeArea(data->me_handle, 40.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[155], 80.000000f, 2.600000f);
      aLightningCreate(Object_handles[155], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aLightningCreate(data->me_handle, Object_handles[155], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[155], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0862::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 058: INIT LNipple 1
    if (1) {
      aObjGhostSet(1, Object_handles[157]);
      aObjMakeInvuln(data->me_handle, 99999);
      aSetObjectTimer(data->me_handle, 95.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 057: Lightning Nipple 1
    if (1) {
      aMiscShakeArea(data->me_handle, 40.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[157], 80.000000f, 2.600000f);
      aLightningCreate(Object_handles[157], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aLightningCreate(data->me_handle, Object_handles[157], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[157], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 068: Lightning Ball 5
    if (1) {
      if (qObjCanSeePlayerAdvancedWithStore(4, 360, data->me_handle, 160.000000f, 1024) == true) {
        aObjApplyDamage(qObjSavedHandle(4), qUserVarValue(1));
        aSoundPlayObject(Sound_indexes[10], qObjSavedHandle(4), 1.000000f);
        aObjSpark(qObjSavedHandle(4), 40.000000f, 1.000000f);
        aLightningCreate(qObjSavedHandle(4), data->me_handle, 0.500000f, 2.500000f, 2, Texture_indexes[1], 0.300000f, 3,
                         120, 120, 220, 0);
      }
      aMiscShakeArea(data->me_handle, 60.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[148], 100.000000f, 2.600000f);
      aLightningCreate(data->me_handle, Object_handles[148], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aLightningCreate(Object_handles[148], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[148], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 067: Lightning Ball 4
    if (1) {
      if (qObjCanSeePlayerAdvancedWithStore(4, 360, data->me_handle, 160.000000f, 1024) == true) {
        aObjApplyDamage(qObjSavedHandle(4), qUserVarValue(1));
        aSoundPlayObject(Sound_indexes[10], qObjSavedHandle(4), 1.000000f);
        aObjSpark(qObjSavedHandle(4), 40.000000f, 1.000000f);
        aLightningCreate(qObjSavedHandle(4), data->me_handle, 0.500000f, 2.500000f, 2, Texture_indexes[1], 0.300000f, 3,
                         120, 120, 220, 0);
      }
      aMiscShakeArea(data->me_handle, 60.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[150], 100.000000f, 2.600000f);
      aLightningCreate(data->me_handle, Object_handles[150], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aLightningCreate(Object_handles[150], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[150], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_089F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 066: Lightning Ball 3
    if (1) {
      if (qObjCanSeePlayerAdvancedWithStore(4, 360, data->me_handle, 160.000000f, 1024) == true) {
        aObjApplyDamage(qObjSavedHandle(4), qUserVarValue(1));
        aSoundPlayObject(Sound_indexes[10], qObjSavedHandle(4), 1.000000f);
        aObjSpark(qObjSavedHandle(4), 40.000000f, 1.000000f);
        aLightningCreate(qObjSavedHandle(4), data->me_handle, 0.500000f, 2.500000f, 2, Texture_indexes[1], 0.300000f, 3,
                         120, 120, 220, 0);
      }
      aMiscShakeArea(data->me_handle, 60.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[152], 100.000000f, 2.600000f);
      aLightningCreate(data->me_handle, Object_handles[152], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aLightningCreate(Object_handles[152], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[152], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_109E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 065: Lightning Ball 2
    if (1) {
      if (qObjCanSeePlayerAdvancedWithStore(4, 360, data->me_handle, 160.000000f, 1024) == true) {
        aObjApplyDamage(qObjSavedHandle(4), qUserVarValue(1));
        aSoundPlayObject(Sound_indexes[10], qObjSavedHandle(4), 1.000000f);
        aObjSpark(qObjSavedHandle(4), 40.000000f, 1.000000f);
        aLightningCreate(qObjSavedHandle(4), data->me_handle, 0.500000f, 2.500000f, 2, Texture_indexes[1], 0.300000f, 3,
                         120, 120, 220, 0);
      }
      aMiscShakeArea(data->me_handle, 60.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[154], 100.000000f, 2.600000f);
      aLightningCreate(data->me_handle, Object_handles[154], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aLightningCreate(Object_handles[154], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[154], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_109C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 059: Lightning Ball 1
    if (1) {
      if (qObjCanSeePlayerAdvancedWithStore(4, 360, data->me_handle, 160.000000f, 1024) == true) {
        aObjApplyDamage(qObjSavedHandle(4), qUserVarValue(1));
        aSoundPlayObject(Sound_indexes[10], qObjSavedHandle(4), 1.000000f);
        aObjSpark(qObjSavedHandle(4), 40.000000f, 1.000000f);
        aLightningCreate(qObjSavedHandle(4), data->me_handle, 0.500000f, 2.500000f, 2, Texture_indexes[1], 0.300000f, 3,
                         120, 120, 220, 0);
      }
      aMiscShakeArea(data->me_handle, 60.000000f, 250.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aObjSpark(Object_handles[156], 100.000000f, 2.600000f);
      aLightningCreate(data->me_handle, Object_handles[156], 0.500000f, 2.000000f, 2, Texture_indexes[1], 0.500000f, 3,
                       220, 220, 220, 0);
      aLightningCreate(Object_handles[156], data->me_handle, 0.650000f, 3.500000f, 2, Texture_indexes[1], 0.300000f, 2,
                       120, 120, 220, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 0.500000f);
      aSetObjectTimer(Object_handles[156], 2.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08AE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: HangSwitch Hit
    if ((ScriptActionCtr_073 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[5], 1);
      aShowHUDMessage(Message_strings[11]);
      aDoorLockUnlock(0, Door_handles[6]);
      aDoorLockUnlock(0, Door_handles[7]);
      aTurnOnSpew(Object_handles[166], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 10.000000f,
                  3.000000f, 20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[167], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 10.000000f,
                  3.000000f, 20.000000f, 0, -1);
      aSetObjectTimer(Object_handles[168], 8.000000f, -1);
      aSetObjectTimer(Object_handles[169], 7.000000f, -1);
      aSetObjectTimer(Object_handles[170], 6.000000f, -1);
      aSetObjectTimer(Object_handles[171], 5.000000f, -1);
      aSetObjectTimer(Object_handles[172], 4.000000f, -1);
      aSetObjectTimer(Object_handles[173], 3.000000f, -1);
      aSetObjectTimer(Object_handles[174], 2.000000f, -1);
      aSetObjectTimer(Object_handles[175], 1.000000f, -1);
      aSoundPlayObject(Sound_indexes[11], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 081: HangExplodeMe 8
    if ((ScriptActionCtr_081 < 1) && (1)) {
      aObjKill(Object_handles[176], 1, 1, 2097392, 3.000000f, 3.000000f);
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 080: HangExplodeMe 7
    if ((ScriptActionCtr_080 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[177], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 079: HangExplodeMe 6
    if ((ScriptActionCtr_079 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[178], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 078: HangExplodeMe 5
    if ((ScriptActionCtr_078 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[179], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 077: HangExplodeMe 4
    if ((ScriptActionCtr_077 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[180], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20A3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 076: HangExplodeMe 3
    if ((ScriptActionCtr_076 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[181], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_28A2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 075: HangExplodeMe 2
    if ((ScriptActionCtr_075 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[182], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 074: HangExplodeMe 1
    if ((ScriptActionCtr_074 < 1) && (1)) {
      aObjKill(data->me_handle, 1, 1, 2097392, 1.000000f, 1.000000f);
      aObjKill(Object_handles[183], 1, 1, 2097392, 3.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08DA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 117: HSGuard Hit-51
    if ((ScriptActionCtr_117 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 096: INIT CityHS Guard-12
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 118: HSGuard Hit-52
    if ((ScriptActionCtr_118 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 095: INIT CityHS Guard-11
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 113: HSGuard Hit-31
    if ((ScriptActionCtr_113 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 094: INIT CityHS Guard-10
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 114: HSGuard Hit-32
    if ((ScriptActionCtr_114 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 093: INIT CityHS Guard-9
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 115: HSGuard Hit-41
    if ((ScriptActionCtr_115 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 092: INIT CityHS Guard-8
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 116: HSGuard Hit-42
    if ((ScriptActionCtr_116 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 091: INIT CityHS Guard-7
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 119: HSGuard Hit-61
    if ((ScriptActionCtr_119 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 090: INIT CityHS Guard-6
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 120: HSGuard Hit-62
    if ((ScriptActionCtr_120 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 089: INIT CityHS Guard-5
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 109: HSGuard Hit-11
    if ((ScriptActionCtr_109 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetTeam(0, data->me_handle);
      aAISetMaxSpeed(data->me_handle, 60.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 088: INIT CityHS Guard-4
    if (1) {
      aAISetTeam(196608, data->me_handle);
      aAISetMaxSpeed(data->me_handle, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 110: HSGuard Hit-12
    if ((ScriptActionCtr_110 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 087: INIT CityHS Guard-3
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 112: HSGuard Hit-22
    if ((ScriptActionCtr_112 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 086: INIT CityHS Guard-2
    if (1) {
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08CF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 111: HSGuard Hit-21
    if ((ScriptActionCtr_111 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[12], data->me_handle, 1.000000f);
      aAISetMaxSpeed(data->me_handle, 60.000000f);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 085: INIT CityHS Guard-1
    if (1) {
      aAISetTeam(196608, data->me_handle);
      aAISetMaxSpeed(data->me_handle, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_105C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 103: CityHS GotHit 6
    if ((ScriptActionCtr_103 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetMaxSpeed(Object_handles[222], 60.000000f);
      aAISetMaxSpeed(Object_handles[221], 60.000000f);
      aAISetTeam(0, Object_handles[221]);
      aAISetTeam(0, Object_handles[222]);
      aSoundPlayObject(Sound_indexes[13], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 108: CityHS GotDestroyed6
    if (1) {
      aEnableVirusInfection(0, Object_handles[221]);
      aEnableVirusInfection(0, Object_handles[222]);
      aObjMakeVulnerable(Object_handles[221]);
      aObjMakeVulnerable(Object_handles[222]);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2059::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 102: CityHS GotHit 5
    if ((ScriptActionCtr_102 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetMaxSpeed(Object_handles[215], 60.000000f);
      aAISetMaxSpeed(Object_handles[216], 60.000000f);
      aAISetTeam(0, Object_handles[216]);
      aAISetTeam(0, Object_handles[215]);
      aSoundPlayObject(Sound_indexes[13], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 107: CityHS GotDestroyed5
    if (1) {
      aEnableVirusInfection(0, Object_handles[215]);
      aEnableVirusInfection(0, Object_handles[216]);
      aObjMakeVulnerable(Object_handles[215]);
      aObjMakeVulnerable(Object_handles[216]);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0858::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 101: CityHS GotHit 4
    if ((ScriptActionCtr_101 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetMaxSpeed(Object_handles[219], 60.000000f);
      aAISetMaxSpeed(Object_handles[220], 60.000000f);
      aAISetTeam(0, Object_handles[219]);
      aAISetTeam(0, Object_handles[220]);
      aSoundPlayObject(Sound_indexes[13], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 106: CityHS GotDestroyed4
    if (1) {
      aEnableVirusInfection(0, Object_handles[219]);
      aEnableVirusInfection(0, Object_handles[220]);
      aObjMakeVulnerable(Object_handles[219]);
      aObjMakeVulnerable(Object_handles[220]);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0857::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 100: CityHS GotHit 3
    if ((ScriptActionCtr_100 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetMaxSpeed(Object_handles[218], 60.000000f);
      aAISetMaxSpeed(Object_handles[217], 60.000000f);
      aAISetTeam(0, Object_handles[217]);
      aAISetTeam(0, Object_handles[218]);
      aSoundPlayObject(Sound_indexes[13], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 105: CityHS GotDestroyed3
    if (1) {
      aEnableVirusInfection(0, Object_handles[217]);
      aEnableVirusInfection(0, Object_handles[218]);
      aObjMakeVulnerable(Object_handles[217]);
      aObjMakeVulnerable(Object_handles[218]);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1030::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 099: CityHS GotHit 2
    if ((ScriptActionCtr_099 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetMaxSpeed(Object_handles[226], 60.000000f);
      aAISetMaxSpeed(Object_handles[225], 60.000000f);
      aAISetTeam(0, Object_handles[226]);
      aAISetTeam(0, Object_handles[225]);
      aSoundPlayObject(Sound_indexes[13], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 104: CityHS GotDestroyed2
    if (1) {
      aEnableVirusInfection(0, Object_handles[226]);
      aEnableVirusInfection(0, Object_handles[225]);
      aObjMakeVulnerable(Object_handles[226]);
      aObjMakeVulnerable(Object_handles[225]);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_402F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 097: CityHS GotHit 1
    if ((ScriptActionCtr_097 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetMaxSpeed(Object_handles[224], 60.000000f);
      aAISetMaxSpeed(Object_handles[223], 60.000000f);
      aAISetTeam(0, Object_handles[223]);
      aAISetTeam(0, Object_handles[224]);
      aSoundPlayObject(Sound_indexes[13], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 098: CityHS GotDestroyed1
    if (1) {
      aEnableVirusInfection(0, Object_handles[223]);
      aEnableVirusInfection(0, Object_handles[224]);
      aObjMakeVulnerable(Object_handles[223]);
      aObjMakeVulnerable(Object_handles[224]);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1871::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 138: Pissed off CoolGuards
    if ((ScriptActionCtr_138 < 1) && (1)) {
      aSetObjectTimer(Object_handles[241], 2.000000f, -1);
      aSetObjectTimer(Object_handles[242], 1.000000f, -1);
      aSetObjectTimer(Object_handles[243], 0.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_138 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_138++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_091A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 135: HitGuard-3
    if ((ScriptActionCtr_135 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSetObjectTimer(Object_handles[164], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_135 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_135++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 137: Pissed off Guard-3
    if ((ScriptActionCtr_137 < 1) && (1)) {
      aAISetTeam(0, data->me_handle);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 40.000000f, 3.000000f);
      aCloakObject(data->me_handle, 99999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_137 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_137++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0919::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 134: HitGuard-2
    if ((ScriptActionCtr_134 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSetObjectTimer(Object_handles[164], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_134 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_134++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 136: Pissed off Guard-2
    if ((ScriptActionCtr_136 < 1) && (1)) {
      aAISetTeam(0, data->me_handle);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 40.000000f, 3.000000f);
      aCloakObject(data->me_handle, 99999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_136 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_136++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0918::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 133: HitGuard-1
    if ((ScriptActionCtr_133 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSetObjectTimer(Object_handles[164], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_133 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_133++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 131: Pissed off Guard-1
    if ((ScriptActionCtr_131 < 1) && (1)) {
      aAISetTeam(0, data->me_handle);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 40.000000f, 3.000000f);
      aCloakObject(data->me_handle, 99999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0917::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 132: HitWelder
    if ((ScriptActionCtr_132 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSetObjectTimer(Object_handles[164], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_132 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_132++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0925::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 156: INIT Goofy Threshers-8
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[244], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_156 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_156++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 149: Goofy Thresher Attack-8
    if ((ScriptActionCtr_149 < 1) && (1)) {
      aObjDelete(Object_handles[244]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_149 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_149++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0924::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 155: INIT Goofy Threshers-7
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[245], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_155 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_155++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 148: Goofy Thresher Attack-7
    if ((ScriptActionCtr_148 < 1) && (1)) {
      aObjDelete(Object_handles[245]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_148 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_148++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0923::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 154: INIT Goofy Threshers-6
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[246], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_154 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_154++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 147: Goofy Thresher Attack-6
    if ((ScriptActionCtr_147 < 1) && (1)) {
      aObjDelete(Object_handles[246]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_147 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_147++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0922::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 153: INIT Goofy Threshers-5
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[247], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_153 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_153++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 146: Goofy Thresher Attack-5
    if ((ScriptActionCtr_146 < 1) && (1)) {
      aObjDelete(Object_handles[247]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_146 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_146++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0921::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 152: INIT Goofy Threshers-4
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[248], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_152 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_152++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 145: Goofy Thresher Attack-4
    if ((ScriptActionCtr_145 < 1) && (1)) {
      aObjDelete(Object_handles[248]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_145 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_145++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1120::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 151: INIT Goofy Threshers-3
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[249], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_151 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_151++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 144: Goofy Thresher Attack-3
    if ((ScriptActionCtr_144 < 1) && (1)) {
      aObjDelete(Object_handles[249]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_144 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_144++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_111F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 150: INIT Goofy Threshers-2
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[250], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_150 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_150++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 143: Goofy Thresher Attack-2
    if ((ScriptActionCtr_143 < 1) && (1)) {
      aObjDelete(Object_handles[250]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_143 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_143++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_111E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 139: INIT Goofy Threshers-1
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aLightningCreate(data->me_handle, Object_handles[251], 99999.000000f, 5.000000f, 1, Texture_indexes[3], 0.350000f,
                       3, 50, 200, 220, 0);
      aAISetTeam(196608, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_139 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_139++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 140: Goofy Thresher Attack-1
    if ((ScriptActionCtr_140 < 1) && (1)) {
      aObjDelete(Object_handles[251]);
      aSoundPlayObject(Sound_indexes[14], data->me_handle, 1.000000f);
      aObjSpark(data->me_handle, 30.000000f, 2.000000f);
      aCloakObject(data->me_handle, 99999.000000f);
      aAISetTeam(0, data->me_handle);
      aObjMakeVulnerable(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_140 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_140++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_112E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 142: Ambush!
    if ((ScriptActionCtr_142 < 1) && (qObjCanSeePlayer(360, Object_handles[252], 140.000000f) == true)) {
      aGoalEnableDisable(1, Goal_indexes[7]);
      aShowHUDMessage(Message_strings[12]);
      aLightningCreate(Object_handles[159], Object_handles[253], 99999.000000f, 3.000000f, 1, Texture_indexes[3],
                       0.400000f, 3, 50, 200, 220, 0);
      aLightningCreate(Object_handles[158], Object_handles[254], 99999.000000f, 3.000000f, 1, Texture_indexes[3],
                       0.400000f, 3, 50, 200, 220, 0);
      aDoorSetPos(Door_handles[1], 0.000000f);
      aDoorSetPos(Door_handles[4], 0.000000f);
      aDoorSetPos(Door_handles[3], 0.000000f);
      aDoorSetPos(Door_handles[5], 0.000000f);
      aEmitSparks(50.000000f, Object_handles[159]);
      aEmitSparks(50.000000f, Object_handles[158]);
      aDoorLockUnlock(1, Door_handles[5]);
      aDoorLockUnlock(1, Door_handles[1]);
      aDoorLockUnlock(1, Door_handles[4]);
      aDoorLockUnlock(1, Door_handles[3]);
      aRoomSetLightingFlicker(1, Room_indexes[10]);
      aSoundPlayObject(Sound_indexes[15], data->me_handle, 1.000000f);
      aTurnOnSpew(Object_handles[120], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 35.000000f, 0, 0);
      aTurnOnSpew(Object_handles[121], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 35.000000f, 0, 1);
      aSetObjectTimer(Object_handles[115], 2.000000f, -1);
      aSetObjectTimer(Object_handles[116], 3.000000f, -1);
      aSetObjectTimer(Object_handles[117], 4.000000f, -1);
      aSetObjectTimer(Object_handles[118], 5.000000f, -1);
      aSetObjectTimer(Object_handles[124], 6.000000f, -1);
      aSetObjectTimer(Object_handles[113], 7.000000f, -1);
      aSetObjectTimer(Object_handles[123], 8.000000f, -1);
      aSetObjectTimer(Object_handles[122], 9.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_142 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_142++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0932::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 158: Ambush Reverser-2
    if ((ScriptActionCtr_158 < 1) &&
        (((ScriptActionCtr_142 > 0) == true) && (qObjIsPlayerWeapon(event_data->it_handle) == true))) {
      if ((ScriptActionCtr_157 > 0) == true) {
        aRoomSetLightingFlicker(0, Room_indexes[10]);
      }
      aSoundPlayObject(Sound_indexes[16], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aObjDelete(Object_handles[254]);
      aEmitSparks(30.000000f, Object_handles[159]);
      aEmitSparks(30.000000f, Object_handles[158]);
      aSoundStopObj(Object_handles[252]);
      aObjSpark(Object_handles[158], 30.000000f, 2.000000f);
      aUnCloakObject(Object_handles[122]);
      aUnCloakObject(Object_handles[123]);
      aUnCloakObject(Object_handles[113]);
      aUnCloakObject(Object_handles[124]);
      aUnCloakObject(Object_handles[118]);
      aUnCloakObject(Object_handles[117]);
      aUnCloakObject(Object_handles[116]);
      aUnCloakObject(Object_handles[115]);

      // Increment the script action counter
      if (ScriptActionCtr_158 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_158++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0931::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 157: Ambush Reverser-1
    if ((ScriptActionCtr_157 < 1) &&
        (((ScriptActionCtr_142 > 0) == true) && (qObjIsPlayerWeapon(event_data->it_handle) == true))) {
      if ((ScriptActionCtr_158 > 0) == true) {
        aRoomSetLightingFlicker(0, Room_indexes[10]);
      }
      aSoundPlayObject(Sound_indexes[16], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aGoalCompleted(Goal_indexes[7], 1);
      aDoorLockUnlock(0, Door_handles[5]);
      aDoorLockUnlock(0, Door_handles[1]);
      aDoorLockUnlock(0, Door_handles[4]);
      aDoorLockUnlock(0, Door_handles[3]);
      aObjSpark(Object_handles[159], 30.000000f, 2.000000f);
      aTurnOffSpew(0);
      aTurnOffSpew(1);
      aEmitSparks(30.000000f, Object_handles[159]);
      aEmitSparks(30.000000f, Object_handles[158]);
      aObjDelete(Object_handles[253]);

      // Increment the script action counter
      if (ScriptActionCtr_157 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_157++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 159: INIT GarbageFires
    if ((ScriptActionCtr_159 < 1) && ((ScriptActionCtr_142 > 0) == true)) {
      aObjSetLightingDist(Object_handles[143], 140.000000f);
      aLightningCreate(Object_handles[90], Object_handles[258], 99999.000000f, 6.000000f, 1, Texture_indexes[3],
                       0.300000f, 3, 255, 150, 0, 0);
      aLightningCreate(Object_handles[91], Object_handles[259], 99999.000000f, 6.000000f, 1, Texture_indexes[3],
                       0.300000f, 3, 255, 150, 0, 0);
      aLightningCreate(Object_handles[92], Object_handles[260], 99999.000000f, 6.000000f, 1, Texture_indexes[3],
                       0.300000f, 3, 255, 150, 0, 0);
      aLightningCreate(Object_handles[93], Object_handles[261], 99999.000000f, 6.000000f, 1, Texture_indexes[3],
                       0.300000f, 3, 255, 150, 0, 0);

      // Increment the script action counter
      if (ScriptActionCtr_159 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_159++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0967::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 164: Last Switch2
    if ((ScriptActionCtr_164 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_163 > 0) == true) {
        aSetObjectTimer(Object_handles[273], 0.000000f, -1);
      } else {
        aShowHUDMessage(Message_strings[13]);
      }
      aTurnOnSpew(Object_handles[274], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 35.000000f, 0, -1);
      aSetObjectTimer(Object_handles[275], 4.000000f, -1);
      aSoundPlayObject(Sound_indexes[16], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_164 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_164++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 166: LastAmbush Part2
    if ((ScriptActionCtr_166 < 1) && (1)) {
      aGoalCompleted(Goal_indexes[8], 1);
      aShowHUDMessage(Message_strings[14]);
      aDoorLockUnlock(0, Door_handles[8]);
      aDoorLockUnlock(0, Door_handles[9]);
      aDoorLockUnlock(1, Door_handles[10]);
      aDoorLockUnlock(1, Door_handles[11]);
      aDoorSetPos(Door_handles[12], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_166 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_166++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0966::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 163: Last Switch1
    if ((ScriptActionCtr_163 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_164 > 0) == true) {
        aSetObjectTimer(Object_handles[273], 0.000000f, -1);
      } else {
        aShowHUDMessage(Message_strings[13]);
      }
      aTurnOnSpew(Object_handles[276], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 35.000000f, 0, -1);
      aSoundPlayObject(Sound_indexes[16], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[275], 2.000000f, -1);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_163 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_163++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 165: LastAmbush
    if ((ScriptActionCtr_165 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[14], Object_handles[269], 1.000000f);
      aSoundPlayObject(Sound_indexes[14], Object_handles[270], 1.000000f);
      aObjGhostSet(0, Object_handles[269]);
      aObjGhostSet(0, Object_handles[270]);
      aObjGhostSet(0, Object_handles[271]);
      aObjGhostSet(0, Object_handles[272]);
      aObjSpark(Object_handles[272], 30.000000f, 2.000000f);
      aObjSpark(Object_handles[271], 30.000000f, 2.000000f);
      aObjSpark(Object_handles[270], 30.000000f, 2.000000f);
      aObjSpark(Object_handles[269], 30.000000f, 2.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_165 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_165++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0809::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 208: HitExitDoorAfterBeingToldToGoDown
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_193 > 0) == true)) {
      aShowHUDMessage(Message_strings[16]);

      // Increment the script action counter
      if (ScriptActionCtr_208 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_208++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Wind Barrier End-7
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Wind Barrier End-6
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Wind Barrier End-5
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Wind Barrier End-4
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Wind Barrier End-3
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Wind Barrier End-2
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Wind Barrier End-1
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Wind Barrier Start-7
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 201: MusicMaintenence-1
    if (qUserFlag(0) == false) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_201 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_201++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Wind Barrier Start-6
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 202: MusicMaintenence-2
    if (qUserFlag(0) == false) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_202 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_202++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Wind Barrier Start-5
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 203: MusicIndustrial-1
    if (qUserFlag(0) == false) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_203 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_203++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Wind Barrier Start-4
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 204: MusicIndustrial-2
    if (qUserFlag(0) == false) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_204 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_204++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Wind Barrier Start-3
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 205: MusicPreReactor-1
    if (qUserFlag(0) == false) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_205 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_205++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Wind Barrier Start-2
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 002: Wind Barrier Start-1
    if (1) {
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 60.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 199: Final Countdown 3 Alternate
    if ((ScriptActionCtr_199 < 1) && ((ScriptActionCtr_192 > 0) == false)) {
      aSoundPlaySteaming("VoxMerc1Terminated.osf", 1.000000f);
      aCancelTimer(12);
      aGoalEnableDisable(1, Goal_indexes[2]);
      aGoalEnableDisable(0, Goal_indexes[3]);
      aSetLevelTimer(7.000000f, 13);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[8]);

      // Increment the script action counter
      if (ScriptActionCtr_199 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_199++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 196: ReachedWasteDisposal
    if ((ScriptActionCtr_196 < 1) && ((qUserFlag(0) == true) && (1))) {
      aGoalCompleted(Goal_indexes[4], 1);
      aGoalCompleted(Goal_indexes[2], 1);
      aCancelTimer(11);
      aSetLevelTimer(0.000000f, 15);

      // Increment the script action counter
      if (ScriptActionCtr_196 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_196++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 127: HiddenEntry Side12
    if ((ScriptActionCtr_127 < 1) && ((ScriptActionCtr_126 > 0) == false)) {
      aAIGoalFollowPathSimple(Object_handles[231], Path_indexes[34], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[232], Path_indexes[34], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[233], Path_indexes[35], 4352, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 126: HiddenEntry Side11
    if ((ScriptActionCtr_126 < 1) && ((ScriptActionCtr_127 > 0) == false)) {
      aAIGoalFollowPathSimple(Object_handles[231], Path_indexes[34], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[232], Path_indexes[34], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[233], Path_indexes[35], 4352, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 129: HiddenEntry Side22
    if ((ScriptActionCtr_129 < 1) && ((ScriptActionCtr_128 > 0) == false)) {
      aAIGoalFollowPathSimple(Object_handles[230], Path_indexes[36], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[229], Path_indexes[36], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[228], Path_indexes[37], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[227], Path_indexes[37], 4352, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 128: HiddenEntry Side21
    if ((ScriptActionCtr_128 < 1) && ((ScriptActionCtr_129 > 0) == false)) {
      aAIGoalFollowPathSimple(Object_handles[230], Path_indexes[36], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[229], Path_indexes[36], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[228], Path_indexes[37], 4352, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[227], Path_indexes[37], 4352, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 207: MusicReactor-1
    if (qUserFlag(0) == false) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_207 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_207++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 206: MusicPreReactor-2
    if (qUserFlag(0) == false) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_206 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_206++;
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
NEXT_ID		211

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:WindStrength
1:NippleDamage
2:ExtraCDTime
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:SetBomb
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:Ambush1
1:Ambush2
2:Guaranteed1
3:Guaranteed2
4:Guaranteed3
5:Guaranteed4
6:Guaranteed5
7:Guaranteed6
8:Guaranteed7
9:Guaranteed8
10:Guaranteed9
11:Guaranteed10
12:Guaranteed11
13:Guaranteed12
14:Guaranteed13
15:Guaranteed14
16:Guaranteed15
17:Guaranteed16
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:CreateFirstLifters
1:CloseEntrance
2:OpenEntrance
3:Rod1Smoker
4:Lifter1Wait
5:Rod2Smoker
6:Lifter2Wait
7:CreateSecondLifters
8:BombDanger1
9:BombDanger2
10:BombDanger3
11:FinalCountdown
12:BombDanger4
13:BombDanger5
14:BombShaker
15:ReachedSafety
16:Failed
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:Lifter1
1:Lifter2
2:Rod1
3:Rod2
4:NipplePlayer
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:GetRod1
1:GetRod2
2:PickUpRod1
3:PickUpRod2
4:TransportRod1
5:TransportRod2
6:LeftSide
7:TopSide
8:RightSide
9:BottomSide
10:Patrol
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
EntranceDoor
BlastDoor1
BlastDoor4
AmbushSide1
AmbushSide2
AmbushDoor
CityDoor1
CityDoor2
CityUp1Door
CityUp2Door
FirstDoor1
FirstDoor2
ReakTop
$$DOOR_LIST_END

$$OBJECT_LIST_START
BumPipe1
BumPipe2
BumPipe3
BumPipe4
EPipe1
EPipe2
EPipe3
EPipe4
HSLast
HSCity1
HSCity2
HSCity3
HSCity4
HSCity5
HSCity6
CityE4
CityE3
CityE2
CityE1
Stack5
Stack6
Stack7
Stack4
Stack3
Stack2
Stack1
Stack8
WindSpew1
WindSpew2
WindSpew3
WindSpew4
Phoenix2
Phoenix1
Assault-1
Assault-2
Assault-3
CameraJupiterTarge
SlideLeftTarget
SlideLeftHighTarge
EDTop1
EDTop2
EDTop3
EDTop4
SmokerIntro1
SmokerIntro2
FinalSlideTarget
EntranceDoor
EDBottom1
EDBottom2
EDBottom3
EDBottom4
DoorOpenTarget
FollowCEDTarget
SmokerIntro3
SmokerIntro4
NodeNRG1
NodeNRG2
NRGhost1
NRGhost2
NRGBeam2
NRGBeam1
NRGSmoke12
NRGSmoke11
Vaporizer1
VaporizerPoint1
NRGSmoke21
NRGSmoke22
Vaporizer2
VaporizerNode2
NNode6
NSmoke6
NNode5
NSmoke5
NNode4
NSmoke4
NNode3
NSmoke3
NNode2
NSmoke2
NNode1
NSmoke1
MainReakNode
NMain
BombInventory
EmergLight1
EmergLight2
BombRender
EFLifter1
EF3Tail1
EF3Tail2
GTarget1
GTarget2
GTarget3
GTarget4
ExplodeTarget1
EFSpew1
EFSpew2
NodeFire1
NodeFire6
NodeFire2
NodeFire5
NodeFire3
NodeFire4
AELow8
AELow7
AELow6
AELow5
AELow1
AELow2
AELow3
EFLifterSpot
ExplodeTarget2
EFB-C
LoThresh6
EFB-B
LoThresh1
LoThresh2
LoThresh3
LoThresh4
EFB-A
AmbushSmoke1
AmbushSmoke2
LoThresh8
LoThresh7
LoThresh5
EFB-5
EFB-6
EFB-7
EFB-8
EF3-D
EF3-9
EF3-8
EF3-7
EF3-6
EF3-5
EF3-4
EF3-3
EF3-2
EF3-1
EFTarget3
EF3-A
EF3-B
EF3-C
WDLightXXX
EF4Smoke1
EF4Smoke2
EF4Smoke3
EF4Smoke4
LNipple5
LNBall5
LNipple4
LNBall4
LNipple3
LNBall3
LNipple2
LNBall2
LNipple1
LNBall1
AMNode2
AMNode1
AELow4
CoolS4
CoolS3
CoolS2
CoolS1
HangSwitch
HangSmoke1
HangSmoke2
Hang8
Hang7
Hang6
Hang5
Hang4
Hang3
Hang2
Hang1
NB8
NB7
NB6
NB5
NB4
NB3
NB2
NB1
CityMoveF4
CityFMove3
CityFMove2
CityFMove1
CityEMove3
CityEMove2
CityEMove1
CityDMove7
CityDMove6
CityDMove5
CityDMove4
CityDMove3
CityDMove2
CityDMove1
CityCMove5
CityCMove4
CityCMove3
CityCMove2
CityCMove1
CityBMove6
CityBMove5
CityBMove4
CityBMove3
CityBMove2
CityBMove1
CityAMove6
CityAMove5
CityAMove4
CityAMove3
CityAMove2
CityAMove1
Guard51
Guard52
Guard31
Guard32
Guard41
Guard42
Guard61
Guard62
Guard11
Guard12
Guard22
Guard21
HStinger5
HStinger4
HStinger3
HStinger2
HSquid2
HSquid1
HStinger1
HSickle8
HSickle6
HSickle5
HSickle2
HSickle4
ThreshWeld-1
WeldingPoint
ThreshGuard-3
ThreshGuard-2
ThreshGuard-1
LoBall8
LoBall7
LoBall6
LoBall5
LoBall4
LoBall3
LoBall2
LoBall1
AmbushCenter
AMTarget1
AMTarget2
AmbushSwitch2
AmbushSwitch1
BlastDoor1
Garbage1
Garbage2
Garbage3
Garbage4
PatrolC3
PatrolC2
PatrolC1
PatrolB2
PatrolB1
PatrolA4
PatrolA1
LastGuard1
LastGuard2
LastGuard3
LastGuard4
LastDoorSwitch2
LastSmoke2
LastDoorSwitch1
LastSmoke1
$$OBJECT_LIST_END

$$ROOM_LIST_START
WindPoles
CityUp2
CityUp1
IndustryUp2
IndustryUp1
IndustryDown
CityDown2
CityDown01
EntranceRoom
ReactorMain
AmbushLo
PipeUpxplode
WasteDisposal
$$ROOM_LIST_END

$$TRIGGER_LIST_START
WBECityDown2
WBECityDown1
WBEWideUp2
WBEWideUp1
WBEIndustryDown
WBEMidDown
WBEMidUp
WBSCityDown1
WBSCityDown2
WBSWideUp1
WBSWideUp2
WBSIndustryDown
WBSMidDown
WBSMidUp
BetrayalNotice
EnterWasteDisposal
HSide12
HSide11
HSide22
HSide21
MusicReactor-1
MusicPreReactor-1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
windMid1
LevSecAccelRelease
LevSecAccelStart
DorCedWideClsD
ExpHellion
RapidFireOn
RapidFireOff
Lightning
Wall fade ???
AmbSirenIntense
HitEnergy
AmbSwitch31
RbtTubbsHa!1
BaseAlertedSiren
RbtThreshRoar
AmbSirenBRedAcrop
AmbSwitch11
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffect2
FunkyEffect5
FunkyEffectGreen
FunkyEffect3
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
BlackShark
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam-SlideUpJupiter
AssaultDrop-1
IntroCam-SlideRight
AssaultDrop-2
IntroCam-SlideLeftHigh
IntroCam-FinalSlide
IntroCamInt-DoorClose
IntroCamInt-CED1
IntroCamInt-CED2
IntroCamInt-FollowCED
AssaultLift-1
IntroCam-FinalFinal
IntroShip
Lifter-1
LifterCarry-1
LifterCarry-2
ExplodeFinal1
EFLifter
ExplodeFinal2
EF3-Tail1
EF3-Tail2
ExplodeFinal3
EF4Camera
EF4Player
CityLeft-3
CityLeft-1
CityLeft-2
CityTop-2
CityTop-1
CityRight-3
CityRight-2
CityRight-1
CityBottom-2
CityBottom-1
HSquid12
HStinger1
HStinger23
HStinger45
IndustryPatrol2
IndustryPatrol1
$$PATH_LIST_END

$$MATCEN_LIST_START
NRGMatcen1
NRGMatcen2
LifterCreator2
LifterCreator1
$$MATCEN_LIST_END

$$GOAL_LIST_START
Locate Industrial Power Ducts
Disrupt Primary Nuclear Reactor Beam
Hide In Waste Disposal System
Rendevous with CED Assault Ship
Destroy the Mars PTMC Colony
Unlock Colony Access Doors
Locate Maintenence Power Ducts
Unlock Security Doors
Override Emergency Duct Doors
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxMerc1Airlock.osf
VoxMerc1Terminated.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:60:INIT Difficulty Values
        $$CHILD_BLOCK_START
        01:2:0
        02:6
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
                                06:qGetDifficulty:Integer
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qGetDifficulty:Integer
                                        07:1:0
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        10:6:6.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qGetDifficulty:Integer
                                                07:1:0
                                                10:4:2:Integer
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                10:6:8.000000:value
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qGetDifficulty:Integer
                                                        07:1:0
                                                        10:4:3:Integer
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:UserVar
                                                        10:6:10.000000:value
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:UserVar
                                                        10:6:10.000000:value
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        06:qMathMulFloat:value
                                $$CHILD_BLOCK_START
                                06:qMathSubFloat:Float1
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:Float1
                                        06:qMathIntToFloat:Float2
                                                $$CHILD_BLOCK_START
                                                06:qGetDifficulty:Int
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:20.000000:Float2
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:INIT Random Ambient Stuff
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
                        10:1:0:0:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:800.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:INIT Smoke Stacks
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:5.000000:BlobLifetime
                        10:6:0.180000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
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
                        10:6:3.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:9.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:6.000000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:50.000000:BlobSpeed
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
                        10:6:5.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:9.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:6.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:55.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:INIT Winds
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
                        10:6:50.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:4.500000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        06:qUserVarValue:Speed
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:INIT SoftWind
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qGoalCompleted:Bool
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        07:0:6
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:30:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Wind Barrier End-7
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Wind Barrier End-6
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Wind Barrier End-5
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Wind Barrier End-4
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Wind Barrier End-3
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Wind Barrier End-2
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Wind Barrier End-1
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Wind Barrier Start-7
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Wind Barrier Start-6
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Wind Barrier Start-5
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Wind Barrier Start-4
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Wind Barrier Start-3
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Wind Barrier Start-2
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Wind Barrier Start-1
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:60.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:IntroCamera-1
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
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:IntroCam1:Text
                        10:1:0:36:Target
                        10:6:8.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:IntroCamera-1.5
        $$CHILD_BLOCK_START
        01:1:36
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:16:1:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:37:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:IntroCamera-2
        $$CHILD_BLOCK_START
        01:1:37
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:6:20.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:16:3:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:4:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:38:Target
                        10:6:7.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:IntroCamera-3
        $$CHILD_BLOCK_START
        01:1:38
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:19.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:19.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
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
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:19.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
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
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:19.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:15.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:15.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:5:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:45:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:IntroCamera-4
        $$CHILD_BLOCK_START
        01:1:45
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.500000:Red
                        10:6:0.150000:Green
                        10:6:0.050000:Blue
                        10:6:1500.000000:Depth
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
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:300.000000:Depth
                        10:6:12.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:46:Object
                        10:9:1.000000:Volume
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
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:17.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:11.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:11:SpewHandle
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
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:17.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:11.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
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
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:17.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:11.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
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
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:17.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:11.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:51:Target
                        10:6:6.500000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:IntroCamera-5 (DISABLED)
        $$CHILD_BLOCK_START
        01:1:51
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:0:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:16:7:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:16:8:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:9:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:52:Target
                        10:6:5.500000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:IntroCamera-6
        $$CHILD_BLOCK_START
        01:1:51
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:31:Object
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:35:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:10.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:16:10:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:11:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:33:TotallyNotUsedTarget
                        10:16:12:PlayerPath
                        10:6:8.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Intro PostEvents
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
                        10:10:0:1:Ghost/Unghost
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.600000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:1500.000000:Depth
                        10:6:60.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Open Entrance Door (INTRO)
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Number
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Number
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Close Entrance Door (INTRO)
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
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Number
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Number
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Number
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:INIT Lifter Sequence (create first Rods)
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
                        10:1:0:55:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:25.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:58:Object
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
00:42:INIT Lifter Sequence (create second Lifters)
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:INIT Lifter Sequence (create first Lifters)
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object1
                        10:1:0:59:Object2
                        10:6:99999.000000:Lifetime
                        10:6:9.000000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:50:Green
                        10:4:150:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object1
                        10:1:0:60:Object2
                        10:6:99999.000000:Lifetime
                        10:6:9.000000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:50:Green
                        10:4:150:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Lifter Sequence (Rod Created-1)
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:0:Matcen
                                07:1:0
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:Amount
                        10:6:150.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:55:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:3:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjDeform
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.200000:Amount
                        10:6:0.500000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:0:55:Object2
                        10:6:25.000000:Lifetime
                        10:6:7.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:60:Red
                        10:4:200:Green
                        10:4:45:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:0:60:Object2
                        10:6:25.000000:Lifetime
                        10:6:7.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:60:Red
                        10:4:200:Green
                        10:4:45:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:24.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Lifter Sequence (Rod 1 Smoking)
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:20.000000:SparkRate
                        10:6:9999.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:55:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:2:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:12.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:12.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:7.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Lifter Sequence (Created-1)
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:0:Matcen
                                07:1:0
                                10:17:0:3:Matcen
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:4:9999:Time
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:13:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Lifter Sequence (Pick Up Rod-1)
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aAIGoalPickUpObjectRad
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Picker
                        10:4:0:PickerPoint
                        06:qObjSavedHandle:Pickee
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:RadiusRatio
                        10:10:0:3:GoalPriority
                        10:15:65792:AIGoalFlags
                        10:10:0:2:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Lifter Sequence (Transport Rod-1)
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:14:Path
                        10:15:4356:AIGoalFlags
                        10:10:0:4:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Lifter Sequence (Go to wait with Rod-1)
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
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:0:WeaponName
                        10:4:0:GunNum
                        10:1:0:63:Object
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:6:40.000000:Amount
                        10:6:150.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:0:63:Object
                        10:9:0.600000:Volume
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:0:63:Object2
                        10:6:3.000000:Lifetime
                        10:6:4.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.200000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:100:Green
                        10:4:180:Blue
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:60.000000:SparkRate
                        10:6:9999.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Number
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:6:20.000000:SparkRate
                        10:6:4.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjDeform
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:0.100000:Amount
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Lifter Sequence (Destroy Lifter-1)
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
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:0:63:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:6:80.000000:Amount
                        10:6:150.000000:Dist
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object1
                        10:1:0:63:Object2
                        10:6:2.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:6:50.000000:SparkRate
                        10:6:4.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:150.000000:SparkRate
                        10:6:9999.000000:Time
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Number
                        10:1:0:64:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2228464:DeathFlags
                        10:6:2.000000:MinDelay
                        10:6:2.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Lifter Sequence (Rod Created-2)
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:0:Matcen
                                07:1:0
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:Amount
                        10:6:150.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:56:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:3:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjDeform
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.200000:Amount
                        10:6:0.500000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:0:56:Object2
                        10:6:25.000000:Lifetime
                        10:6:7.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:60:Red
                        10:4:200:Green
                        10:4:45:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:0:59:Object2
                        10:6:25.000000:Lifetime
                        10:6:7.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:60:Red
                        10:4:200:Green
                        10:4:45:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:24.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Lifter Sequence (Rod 2 Smoking)
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:20.000000:SparkRate
                        10:6:9999.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:56:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:2:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:12.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:12.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:7.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Lifter Sequence (Created-2)
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:0:Matcen
                                07:1:0
                                10:17:0:2:Matcen
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:4:9999:Time
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:13:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Lifter Sequence (Pick Up Rod-2)
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
                08:aAIGoalPickUpObjectRad
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Picker
                        10:4:0:PickerPoint
                        06:qObjSavedHandle:Pickee
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:RadiusRatio
                        10:10:0:3:GoalPriority
                        10:15:65792:AIGoalFlags
                        10:10:0:3:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Lifter Sequence (Transport Rod-2)
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:15:Path
                        10:15:4356:AIGoalFlags
                        10:10:0:5:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Lifter Sequence (Go to wait with Rod-2)
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
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:0:WeaponName
                        10:4:0:GunNum
                        10:1:0:67:Object
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:40.000000:Amount
                        10:6:150.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:0:67:Object
                        10:9:0.600000:Volume
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:0:67:Object2
                        10:6:3.000000:Lifetime
                        10:6:4.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.200000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:100:Green
                        10:4:180:Blue
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:60.000000:SparkRate
                        10:6:9999.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Number
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:20.000000:SparkRate
                        10:6:4.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjDeform
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:0.100000:Amount
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Lifter Sequence (Destroy Lifter-2)
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
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:0:67:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:80.000000:Amount
                        10:6:150.000000:Dist
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object1
                        10:1:0:67:Object2
                        10:6:2.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:50.000000:SparkRate
                        10:6:4.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:150.000000:SparkRate
                        10:6:9999.000000:Time
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Number
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2228464:DeathFlags
                        10:6:2.000000:MinDelay
                        10:6:2.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:INIT ReactorBeams
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object1
                        10:1:0:70:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:2:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:150:Red
                        10:4:250:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object1
                        10:1:0:72:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:2:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:150:Red
                        10:4:250:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object1
                        10:1:0:74:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:2:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:150:Red
                        10:4:250:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object1
                        10:1:0:76:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:2:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:150:Red
                        10:4:250:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object1
                        10:1:0:78:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:2:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:150:Red
                        10:4:250:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object1
                        10:1:0:80:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:2:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:150:Red
                        10:4:250:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object1
                        10:1:0:82:Object2
                        10:6:99999.000000:Lifetime
                        10:6:9.000000:Thickness
                        10:4:1:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:220:Green
                        10:4:200:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object1
                        10:1:0:82:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:2:Texture
                        10:6:0.200000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:220:Green
                        10:4:200:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object1
                        10:1:0:81:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:2:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:220:Green
                        10:4:200:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:INIT Node 6
        $$CHILD_BLOCK_START
        01:1:69
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.750000:Blue
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:INIT Node 5
        $$CHILD_BLOCK_START
        01:1:71
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.750000:Blue
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:INIT Node 4
        $$CHILD_BLOCK_START
        01:1:73
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.750000:Blue
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:INIT Node 3
        $$CHILD_BLOCK_START
        01:1:75
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.750000:Blue
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:INIT Node 2
        $$CHILD_BLOCK_START
        01:1:77
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.750000:Blue
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:INIT Node 1
        $$CHILD_BLOCK_START
        01:1:79
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.750000:Blue
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:INIT Bomb
        $$CHILD_BLOCK_START
        01:1:83
        02:2
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:86:Object
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:8:BombName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:USED Bomb
        $$CHILD_BLOCK_START
        01:1:83
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
                        05:0
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
                                        10:1:0:86:Object2
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:40.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:6:Region
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:86:Object
                                $$CHILD_BLOCK_END
                        08:aMiscViewerShake
                                $$CHILD_BLOCK_START
                                10:6:100.000000:Amount
                                $$CHILD_BLOCK_END
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:50.000000:Number
                                10:1:0:86:Object
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:69:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:71:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:73:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:75:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:77:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:79:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qMathAddFloat:Time
                                        $$CHILD_BLOCK_START
                                        10:6:120.000000:Float1
                                        06:qUserVarValue:Float2
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        08:aTimerShow
                                $$CHILD_BLOCK_START
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Time
                                10:10:0:10:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:45.000000:Time
                                10:10:0:12:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qMathAddFloat:Time
                                        $$CHILD_BLOCK_START
                                        10:6:60.000000:Float1
                                        06:qUserVarValue:Float2
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:NuclearDisruption:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:8:Sound
                                10:1:1:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowColoredHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:4:255:Red
                                10:4:0:Green
                                10:4:0:Blue
                                10:8:NuclearDisruptorFail:Message
                                10:1:1:-1:PlayerObject
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
00:54:USED Bomb Danger1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:3.000000:LowerLimit
                                10:6:7.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FCOneMinute:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
                        10:1:0:81:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:86:Object
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:6:1.000000:Red
                        10:6:0.000000:Green
                        10:6:0.000000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:6:1.000000:Red
                        10:6:0.000000:Green
                        10:6:0.000000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:6:90.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:6:90.000000:Distance
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object1
                        10:1:0:86:Object2
                        10:6:99999.000000:Lifetime
                        10:6:10.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.200000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:255:Red
                        10:4:100:Green
                        10:4:100:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object1
                        10:1:0:86:Object2
                        10:6:99999.000000:Lifetime
                        10:6:10.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.200000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:255:Red
                        10:4:100:Green
                        10:4:100:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:194:Bomb Shake Me!
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
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:1.000000:LowerLimit
                                10:6:5.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:30.000000:LowerLimit
                                10:6:70.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:209:Final Countdown YouFailed!
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
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                08:aFailLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:195:Final Countdown Complete
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.800000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                08:aFadeWhiteAndEndlevel
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:8:BlankMessage:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:193:Final Countdown 4
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:GameGetToWasteDisposal:GameMessage
                        10:8:GameGetToWasteDisposal:HUDMessage
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FCFindBombShelter:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:199:Final Countdown 3 Alternate
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:192:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:7.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:FCAbandoned:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:192:Final Countdown 3
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:7.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:FCAbandoned:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:191:Final Countdown 2
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FCNoContact:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:190:Final Countdown 1
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FCGetOut:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:196:ReachedWasteDisposal
        $$CHILD_BLOCK_START
        01:0:15
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:171:INIT Final Explosion
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:87:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:88:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:89:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:124:EF1 Start
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:90:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:92:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:93:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:54:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:82:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:3:Texture
                                10:6:0.200000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:81:Object1
                                10:1:0:86:Object2
                                10:6:99999.000000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:3:Texture
                                10:6:0.200000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:100:Green
                                10:4:100:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aCancelTimer
                                $$CHILD_BLOCK_START
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        08:aCancelTimer
                                $$CHILD_BLOCK_START
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:5:Door
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
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:9:Room
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.800000:Red
                        10:6:0.400000:Green
                        10:6:0.200000:Blue
                        10:6:100.000000:Depth
                        10:6:18.000000:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:6:7.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:6:10.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:6:12.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:6:14.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:16:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:94:Target
                        10:6:18.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:EF1 Part5
        $$CHILD_BLOCK_START
        01:1:81
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:95:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:14:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:96:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:15:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:169:EF1 Part4
        $$CHILD_BLOCK_START
        01:1:79
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:97:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:13:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:12:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:3145968:DeathFlags
                        10:6:0.800000:MinDelay
                        10:6:1.200000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:168:EF1 Part3
        $$CHILD_BLOCK_START
        01:1:77
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:98:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:26.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:11:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:99:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:26.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:3145968:DeathFlags
                        10:6:0.600000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:3145968:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.200000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:167:EF1 Part2
        $$CHILD_BLOCK_START
        01:1:75
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:100:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:101:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:3145968:DeathFlags
                        10:6:0.600000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:3145968:DeathFlags
                        10:6:0.500000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:EF1 Part1
        $$CHILD_BLOCK_START
        01:1:73
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:102:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:3145968:DeathFlags
                        10:6:0.600000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:170:EF2 Start
        $$CHILD_BLOCK_START
        01:1:94
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:103:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:104:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:105:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:106:Object
                        10:6:3.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:6:5.250000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:107:Object
                        10:6:6.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:108:Object
                        10:6:7.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        10:6:7.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:87:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:16:17:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:10:Room
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.800000:Red
                        10:6:0.500000:Green
                        10:6:0.200000:Blue
                        10:6:200.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:18:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:111:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:179:EFPart8
        $$CHILD_BLOCK_START
        01:1:109
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.200000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:50.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:178:EFPart7
        $$CHILD_BLOCK_START
        01:1:108
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:113:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.200000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.200000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:50.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:177:EFPart6
        $$CHILD_BLOCK_START
        01:1:107
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.700000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.700000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:117:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.700000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:118:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.700000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:119:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:176:EFPart5
        $$CHILD_BLOCK_START
        01:1:87
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:5:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:120:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.200000:BlobLifetime
                        10:6:0.250000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:55.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:121:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.600000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:25.000000:Speed
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:0.400000:MinDelay
                        10:6:0.400000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2228448:DeathFlags
                        10:6:0.600000:MinDelay
                        10:6:0.700000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:123:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2097328:DeathFlags
                        10:6:0.350000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:124:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:196816:DeathFlags
                        10:6:0.350000:MinDelay
                        10:6:0.500000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:175:EFPart4
        $$CHILD_BLOCK_START
        01:1:106
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:125:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:65696:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:174:EFPart3
        $$CHILD_BLOCK_START
        01:1:105
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:126:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:65696:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:173:EFPart2
        $$CHILD_BLOCK_START
        01:1:104
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:127:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:65696:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:172:EFPart1
        $$CHILD_BLOCK_START
        01:1:103
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:128:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:65696:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:180:EF3 Start
        $$CHILD_BLOCK_START
        01:1:111
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:129:Object
                        10:6:7.400000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:6:6.800000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:131:Object
                        10:6:6.400000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:132:Object
                        10:6:5.600000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:133:Object
                        10:6:4.800000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:134:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:135:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:136:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:11:Room
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.800000:Red
                        10:6:0.400000:Green
                        10:6:0.100000:Blue
                        10:6:250.000000:Depth
                        10:6:9.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:6:16.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:6:16.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:89:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:88:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:138:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:16:19:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:16:20:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:21:CameraPath
                        10:8:BlankMessage:Text
                        10:1:0:139:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:189:EF3Part9
        $$CHILD_BLOCK_START
        01:1:129
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:129:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:45.000000:BlobSize
                        10:6:90.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:188:EF3Part8
        $$CHILD_BLOCK_START
        01:1:130
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:90.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:70.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:141:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:70.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:142:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:70.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:187:EF3Part7
        $$CHILD_BLOCK_START
        01:1:131
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2162832:DeathFlags
                        10:6:0.650000:MinDelay
                        10:6:0.650000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097296:DeathFlags
                        10:6:0.500000:MinDelay
                        10:6:0.500000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:131:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:17:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:25.000000:BlobSize
                        10:6:90.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:16:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:186:EF3Part6
        $$CHILD_BLOCK_START
        01:1:132
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:132:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:15:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:131:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:14:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:185:EF3Part5
        $$CHILD_BLOCK_START
        01:1:133
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:133:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:13:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:132:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:12:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:184:EF3Part4
        $$CHILD_BLOCK_START
        01:1:134
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:134:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:11:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:133:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:183:EF3Part3
        $$CHILD_BLOCK_START
        01:1:135
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:135:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:134:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:182:EF3Part2
        $$CHILD_BLOCK_START
        01:1:136
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:136:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:135:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:181:EF3Part1
        $$CHILD_BLOCK_START
        01:1:137
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:136:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:198:EF4 Start
        $$CHILD_BLOCK_START
        01:1:139
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object
                        10:6:140.000000:Distance
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:Red
                        10:6:0.000000:Green
                        10:6:0.000000:Blue
                        10:6:175.000000:Depth
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:144:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:145:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:146:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:147:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:22:CameraPath
                        10:16:23:PlayerPath
                        10:6:8.000000:Time
                        10:8:BlankMessage:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:PICKUP Bomb
        $$CHILD_BLOCK_START
        01:1:83
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
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:8:BombName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:INIT LNipple 5
        $$CHILD_BLOCK_START
        01:1:148
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
                        10:1:0:149:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:91.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:INIT LNipple 4
        $$CHILD_BLOCK_START
        01:1:150
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
                        10:1:0:151:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:92.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:INIT LNipple 3
        $$CHILD_BLOCK_START
        01:1:152
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
                        10:1:0:153:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:93.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:INIT LNipple 2
        $$CHILD_BLOCK_START
        01:1:154
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
                        10:1:0:155:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:94.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:INIT LNipple 1
        $$CHILD_BLOCK_START
        01:1:156
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
                        10:1:0:157:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:95.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Lightning Nipple 5
        $$CHILD_BLOCK_START
        01:1:148
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object
                        10:6:80.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:149:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Lightning Nipple 4
        $$CHILD_BLOCK_START
        01:1:150
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:151:Object
                        10:6:80.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:151:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:151:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:151:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Lightning Nipple 3
        $$CHILD_BLOCK_START
        01:1:152
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:153:Object
                        10:6:80.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:153:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:153:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:153:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Lightning Nipple 2
        $$CHILD_BLOCK_START
        01:1:154
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:155:Object
                        10:6:80.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:155:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:155:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:155:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Lightning Nipple 1
        $$CHILD_BLOCK_START
        01:1:156
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:157:Object
                        10:6:80.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:157:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:157:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:157:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Lightning Ball 5
        $$CHILD_BLOCK_START
        01:1:149
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
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:2:-1:Object
                                        10:6:160.000000:Distance
                                        10:15:1024:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjApplyDamage
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                06:qUserVarValue:DamageAmount
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:SparkRate
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:2:-1:Object2
                                10:6:0.500000:Lifetime
                                10:6:2.500000:Thickness
                                10:4:2:NumTiles
                                10:14:1:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:120:Red
                                10:4:120:Green
                                10:4:220:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:148:Object
                        10:6:100.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:148:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:148:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:148:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Lightning Ball 4
        $$CHILD_BLOCK_START
        01:1:151
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
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:2:-1:Object
                                        10:6:160.000000:Distance
                                        10:15:1024:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjApplyDamage
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                06:qUserVarValue:DamageAmount
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:SparkRate
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:2:-1:Object2
                                10:6:0.500000:Lifetime
                                10:6:2.500000:Thickness
                                10:4:2:NumTiles
                                10:14:1:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:120:Red
                                10:4:120:Green
                                10:4:220:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object
                        10:6:100.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:150:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Lightning Ball 3
        $$CHILD_BLOCK_START
        01:1:153
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
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:2:-1:Object
                                        10:6:160.000000:Distance
                                        10:15:1024:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjApplyDamage
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                06:qUserVarValue:DamageAmount
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:SparkRate
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:2:-1:Object2
                                10:6:0.500000:Lifetime
                                10:6:2.500000:Thickness
                                10:4:2:NumTiles
                                10:14:1:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:120:Red
                                10:4:120:Green
                                10:4:220:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:152:Object
                        10:6:100.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:152:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:152:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:152:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Lightning Ball 2
        $$CHILD_BLOCK_START
        01:1:155
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
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:2:-1:Object
                                        10:6:160.000000:Distance
                                        10:15:1024:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjApplyDamage
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                06:qUserVarValue:DamageAmount
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:SparkRate
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:2:-1:Object2
                                10:6:0.500000:Lifetime
                                10:6:2.500000:Thickness
                                10:4:2:NumTiles
                                10:14:1:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:120:Red
                                10:4:120:Green
                                10:4:220:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:154:Object
                        10:6:100.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:154:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:154:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:154:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Lightning Ball 1
        $$CHILD_BLOCK_START
        01:1:157
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
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:2:-1:Object
                                        10:6:160.000000:Distance
                                        10:15:1024:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjApplyDamage
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                06:qUserVarValue:DamageAmount
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:SparkRate
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:2:-1:Object2
                                10:6:0.500000:Lifetime
                                10:6:2.500000:Thickness
                                10:4:2:NumTiles
                                10:14:1:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:120:Red
                                10:4:120:Green
                                10:4:220:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Amount
                        10:6:250.000000:Dist
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:156:Object
                        10:6:100.000000:SparkRate
                        10:6:2.600000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:156:Object2
                        10:6:0.500000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:220:Red
                        10:4:220:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:156:Object1
                        10:1:2:-1:Object2
                        10:6:0.650000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.300000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:120:Red
                        10:4:120:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:156:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:210:Testing Clutter DELETE
        $$CHILD_BLOCK_START
        01:1:83
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:0:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:158:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:159:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:103:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:104:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:105:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:106:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:160:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:108:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:107:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:161:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:162:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:163:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:HangSwitch Hit
        $$CHILD_BLOCK_START
        01:1:165
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
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CityAccessDoors:Message
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:7:DoorName
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:168:Object
                        10:6:8.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:169:Object
                        10:6:7.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:170:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:171:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:172:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:173:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:174:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:175:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
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
00:81:HangExplodeMe 8
        $$CHILD_BLOCK_START
        01:1:168
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:176:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:HangExplodeMe 7
        $$CHILD_BLOCK_START
        01:1:169
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:177:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:HangExplodeMe 6
        $$CHILD_BLOCK_START
        01:1:170
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:178:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:HangExplodeMe 5
        $$CHILD_BLOCK_START
        01:1:171
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:179:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:HangExplodeMe 4
        $$CHILD_BLOCK_START
        01:1:172
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:180:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:HangExplodeMe 3
        $$CHILD_BLOCK_START
        01:1:173
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:181:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:HangExplodeMe 2
        $$CHILD_BLOCK_START
        01:1:174
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:182:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:HangExplodeMe 1
        $$CHILD_BLOCK_START
        01:1:175
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:183:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2097392:DeathFlags
                        10:6:3.000000:MinDelay
                        10:6:3.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:INIT City Ambient Movement
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qGoalCompleted:Bool
                                $$CHILD_BLOCK_START
                                10:18:0:5:LevelGoal
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:184:Object
                        10:16:24:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:185:Object
                        10:16:25:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:186:Object
                        10:16:26:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:187:Object
                        10:16:25:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:188:Object
                        10:16:27:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:189:Object
                        10:16:27:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:190:Object
                        10:16:27:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:191:Object
                        10:16:27:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:192:Object
                        10:16:27:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:193:Object
                        10:16:27:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:194:Object
                        10:16:28:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:195:Object
                        10:16:28:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:196:Object
                        10:16:28:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:197:Object
                        10:16:28:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:198:Object
                        10:16:29:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:199:Object
                        10:16:30:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:200:Object
                        10:16:31:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:201:Object
                        10:16:31:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:202:Object
                        10:16:30:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:203:Object
                        10:16:32:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:204:Object
                        10:16:32:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:205:Object
                        10:16:32:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:206:Object
                        10:16:33:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:207:Object
                        10:16:33:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:208:Object
                        10:16:33:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:209:Object
                        10:16:24:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:210:Object
                        10:16:26:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:211:Object
                        10:16:25:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:212:Object
                        10:16:24:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:213:Object
                        10:16:26:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:214:Object
                        10:16:25:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:City Move BottomToLeft
        $$CHILD_BLOCK_START
        01:2:0
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:0.000000:LowerLimit
                                        10:6:1.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.330000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRandomValue:Float
                                                $$CHILD_BLOCK_START
                                                10:6:0.000000:LowerLimit
                                                10:6:1.000000:UpperLimit
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.500000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:25:Path
                                        10:15:4096:AIGoalFlags
                                        10:10:0:6:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:26:Path
                                        10:15:4096:AIGoalFlags
                                        10:10:0:6:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:24:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:6:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:City Move RightToBottom
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
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:0.000000:LowerLimit
                                        10:6:1.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.500000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:33:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:9:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:32:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:9:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:City Move TopToRight
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
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:0.000000:LowerLimit
                                        10:6:1.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.330000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRandomValue:Float
                                                $$CHILD_BLOCK_START
                                                10:6:0.000000:LowerLimit
                                                10:6:1.000000:UpperLimit
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.500000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:31:Path
                                        10:15:4096:AIGoalFlags
                                        10:10:0:8:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:30:Path
                                        10:15:4096:AIGoalFlags
                                        10:10:0:8:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:29:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:8:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:City Move LeftToTop
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
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:0.000000:LowerLimit
                                        10:6:1.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.500000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:28:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:7:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:27:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:7:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:INIT CityHS Guard-12
        $$CHILD_BLOCK_START
        01:1:215
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:INIT CityHS Guard-11
        $$CHILD_BLOCK_START
        01:1:216
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:INIT CityHS Guard-10
        $$CHILD_BLOCK_START
        01:1:217
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:INIT CityHS Guard-9
        $$CHILD_BLOCK_START
        01:1:218
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:INIT CityHS Guard-8
        $$CHILD_BLOCK_START
        01:1:219
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:INIT CityHS Guard-7
        $$CHILD_BLOCK_START
        01:1:220
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:INIT CityHS Guard-6
        $$CHILD_BLOCK_START
        01:1:221
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:INIT CityHS Guard-5
        $$CHILD_BLOCK_START
        01:1:222
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:INIT CityHS Guard-4
        $$CHILD_BLOCK_START
        01:1:223
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:INIT CityHS Guard-3
        $$CHILD_BLOCK_START
        01:1:224
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:INIT CityHS Guard-2
        $$CHILD_BLOCK_START
        01:1:225
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:INIT CityHS Guard-1
        $$CHILD_BLOCK_START
        01:1:226
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:HSGuard Hit-62
        $$CHILD_BLOCK_START
        01:1:222
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:HSGuard Hit-61
        $$CHILD_BLOCK_START
        01:1:221
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:HSGuard Hit-52
        $$CHILD_BLOCK_START
        01:1:216
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:HSGuard Hit-51
        $$CHILD_BLOCK_START
        01:1:215
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:HSGuard Hit-42
        $$CHILD_BLOCK_START
        01:1:220
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:HSGuard Hit-41
        $$CHILD_BLOCK_START
        01:1:219
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:HSGuard Hit-32
        $$CHILD_BLOCK_START
        01:1:218
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:HSGuard Hit-31
        $$CHILD_BLOCK_START
        01:1:217
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:HSGuard Hit-22
        $$CHILD_BLOCK_START
        01:1:225
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:HSGuard Hit-21
        $$CHILD_BLOCK_START
        01:1:226
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:HSGuard Hit-12
        $$CHILD_BLOCK_START
        01:1:224
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:HSGuard Hit-11
        $$CHILD_BLOCK_START
        01:1:223
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
                        10:12:12:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:CityHS GotHit 6
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:222:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:221:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:221:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:222:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:13:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:CityHS GotHit 5
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:215:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:216:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:216:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:215:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:13:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:CityHS GotHit 4
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:219:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:220:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:219:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:220:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:13:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:CityHS GotHit 3
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:218:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:217:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:217:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:218:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:13:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:CityHS GotHit 2
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:226:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:225:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:226:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:225:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:13:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:CityHS GotHit 1
        $$CHILD_BLOCK_START
        01:1:9
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:224:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:223:Object
                        10:6:60.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:223:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:224:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:13:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:CityHS GotDestroyed6
        $$CHILD_BLOCK_START
        01:1:14
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:221:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:222:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:221:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:222:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:CityHS GotDestroyed5
        $$CHILD_BLOCK_START
        01:1:13
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:215:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:216:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:215:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:216:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:CityHS GotDestroyed4
        $$CHILD_BLOCK_START
        01:1:12
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:219:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:220:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:219:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:220:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:CityHS GotDestroyed3
        $$CHILD_BLOCK_START
        01:1:11
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:217:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:218:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:217:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:218:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:CityHS GotDestroyed2
        $$CHILD_BLOCK_START
        01:1:10
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:226:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:225:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:226:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:225:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:CityHS GotDestroyed1
        $$CHILD_BLOCK_START
        01:1:9
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:223:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:0:224:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:223:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:224:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:INIT HiddenSewer
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
                        10:1:0:227:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:228:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:229:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:230:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:231:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:232:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:233:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:234:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:235:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:236:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:237:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:238:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:HiddenEntry Side12
        $$CHILD_BLOCK_START
        01:0:16
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:126:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:231:Object
                        10:16:34:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:232:Object
                        10:16:34:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:233:Object
                        10:16:35:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:HiddenEntry Side11
        $$CHILD_BLOCK_START
        01:0:17
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:127:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:231:Object
                        10:16:34:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:232:Object
                        10:16:34:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:233:Object
                        10:16:35:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:HiddenEntry Side22
        $$CHILD_BLOCK_START
        01:0:18
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:128:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:230:Object
                        10:16:36:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:229:Object
                        10:16:36:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:228:Object
                        10:16:37:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:227:Object
                        10:16:37:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:HiddenEntry Side21
        $$CHILD_BLOCK_START
        01:0:19
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:129:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:230:Object
                        10:16:36:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:229:Object
                        10:16:36:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:228:Object
                        10:16:37:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:227:Object
                        10:16:37:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:INIT Welders Area
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qGoalCompleted:Bool
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:239:Object
                        10:4:1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.080000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:239:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.080000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:240:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:35.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:6:30.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:163:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:162:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:161:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aPhysFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:58722304:PhysicsFlags
                        10:1:0:239:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:239:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:239:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:241:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:242:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:243:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:138:Pissed off CoolGuards
        $$CHILD_BLOCK_START
        01:1:164
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:241:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:242:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:243:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:137:Pissed off Guard-3
        $$CHILD_BLOCK_START
        01:1:241
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:136:Pissed off Guard-2
        $$CHILD_BLOCK_START
        01:1:242
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:131:Pissed off Guard-1
        $$CHILD_BLOCK_START
        01:1:243
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:135:HitGuard-3
        $$CHILD_BLOCK_START
        01:1:241
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:134:HitGuard-2
        $$CHILD_BLOCK_START
        01:1:242
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:133:HitGuard-1
        $$CHILD_BLOCK_START
        01:1:243
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:132:HitWelder
        $$CHILD_BLOCK_START
        01:1:239
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:141:INIT Goofy General
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
                        10:1:0:103:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:104:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:105:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:106:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:160:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:108:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:107:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:156:INIT Goofy Threshers-8
        $$CHILD_BLOCK_START
        01:1:122
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:244:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:155:INIT Goofy Threshers-7
        $$CHILD_BLOCK_START
        01:1:123
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:245:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:154:INIT Goofy Threshers-6
        $$CHILD_BLOCK_START
        01:1:113
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:246:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:153:INIT Goofy Threshers-5
        $$CHILD_BLOCK_START
        01:1:124
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:247:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:152:INIT Goofy Threshers-4
        $$CHILD_BLOCK_START
        01:1:118
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:248:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:151:INIT Goofy Threshers-3
        $$CHILD_BLOCK_START
        01:1:117
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:249:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:150:INIT Goofy Threshers-2
        $$CHILD_BLOCK_START
        01:1:116
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:250:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:139:INIT Goofy Threshers-1
        $$CHILD_BLOCK_START
        01:1:115
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:251:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.350000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:142:Ambush!
        $$CHILD_BLOCK_START
        01:1:252
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:360:Cone
                                10:1:0:252:Object
                                10:6:140.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:7:LevelGoal
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Trap:Message
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:159:Object1
                        10:1:0:253:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:158:Object1
                        10:1:0:254:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:200:Green
                        10:4:220:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:4:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:3:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:5:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:0:159:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:0:158:Object
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:10:Room
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:15:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:120:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:35.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:121:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:35.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:117:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:118:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:124:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:113:Object
                        10:6:7.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:123:Object
                        10:6:8.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        10:6:9.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:158:Ambush Reverser-2
        $$CHILD_BLOCK_START
        01:1:255
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:142:ScriptID
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
                                        10:11:157:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:2:10:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:16:Sound
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:254:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:159:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:158:Object
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:252:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:158:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:123:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:113:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:124:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:118:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:117:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:157:Ambush Reverser-1
        $$CHILD_BLOCK_START
        01:1:256
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:142:ScriptID
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
                                        10:11:158:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:2:10:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:16:Sound
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:159:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:159:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:158:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:253:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:149:Goofy Thresher Attack-8
        $$CHILD_BLOCK_START
        01:1:122
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:244:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:148:Goofy Thresher Attack-7
        $$CHILD_BLOCK_START
        01:1:123
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:245:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:147:Goofy Thresher Attack-6
        $$CHILD_BLOCK_START
        01:1:113
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:246:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:146:Goofy Thresher Attack-5
        $$CHILD_BLOCK_START
        01:1:124
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:247:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:145:Goofy Thresher Attack-4
        $$CHILD_BLOCK_START
        01:1:118
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:248:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:144:Goofy Thresher Attack-3
        $$CHILD_BLOCK_START
        01:1:117
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:249:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:143:Goofy Thresher Attack-2
        $$CHILD_BLOCK_START
        01:1:116
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:250:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:140:Goofy Thresher Attack-1
        $$CHILD_BLOCK_START
        01:1:115
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:251:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:159:INIT GarbageFires
        $$CHILD_BLOCK_START
        01:1:257
        02:0
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
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object
                        10:6:140.000000:Distance
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:90:Object1
                        10:1:0:258:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:255:Red
                        10:4:150:Green
                        10:4:0:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object1
                        10:1:0:259:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:255:Red
                        10:4:150:Green
                        10:4:0:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:92:Object1
                        10:1:0:260:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:255:Red
                        10:4:150:Green
                        10:4:0:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:93:Object1
                        10:1:0:261:Object2
                        10:6:99999.000000:Lifetime
                        10:6:6.000000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:255:Red
                        10:4:150:Green
                        10:4:0:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:160:INIT Patrols
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qGoalCompleted:Bool
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:262:Object
                        10:16:38:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:263:Object
                        10:16:38:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:264:Object
                        10:16:38:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:265:Object
                        10:16:39:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:266:Object
                        10:16:39:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:267:Object
                        10:16:39:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:268:Object
                        10:16:39:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:161:Patrol Repeat
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:10:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.500000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:39:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:10:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:38:Path
                                10:15:4096:AIGoalFlags
                                10:10:0:10:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:162:INIT Last Area
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
                        10:1:0:269:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:270:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:271:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:272:Object
                        10:6:99999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:269:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:270:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:272:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:271:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:164:Last Switch2
        $$CHILD_BLOCK_START
        01:1:273
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
                                        10:11:163:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:273:Object
                                10:6:0.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Last1:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:274:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:35.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:275:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:16:Sound
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
00:163:Last Switch1
        $$CHILD_BLOCK_START
        01:1:275
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
                                        10:11:164:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:273:Object
                                10:6:0.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Last1:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:276:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:35.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:16:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:275:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
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
00:166:LastAmbush Part2
        $$CHILD_BLOCK_START
        01:1:273
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:8:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Last2:Message
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:9:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:10:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:11:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:12:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:165:LastAmbush
        $$CHILD_BLOCK_START
        01:1:275
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:0:269:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:1:0:270:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:269:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:270:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:271:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:272:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:272:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:271:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:270:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:269:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:197:WallHint (Rookie or Trainee only!)
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
                                        10:2:0:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qGetDifficulty:Integer
                                07:1:3
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:WallHint:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:200:MusicIntro
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
00:207:MusicReactor-1
        $$CHILD_BLOCK_START
        01:0:20
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
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
00:206:MusicPreReactor-2
        $$CHILD_BLOCK_START
        01:0:21
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
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
00:205:MusicPreReactor-1
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
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
00:204:MusicIndustrial-2
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
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
00:203:MusicIndustrial-1
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
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
00:202:MusicMaintenence-2
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:201:MusicMaintenence-1
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:208:HitExitDoorAfterBeingToldToGoDown
        $$CHILD_BLOCK_START
        01:1:46
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
                                        10:11:193:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GetAwayFromExit:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
