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
// Filename:	level11.cpp
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

#define ID_CUSTOM_OBJECT_0985 0x001
#define ID_CUSTOM_OBJECT_0942 0x002
#define ID_CUSTOM_OBJECT_0941 0x003
#define ID_CUSTOM_OBJECT_092B 0x004
#define ID_CUSTOM_OBJECT_093E 0x005
#define ID_CUSTOM_OBJECT_0940 0x006
#define ID_CUSTOM_OBJECT_093F 0x007
#define ID_CUSTOM_OBJECT_0954 0x008
#define ID_CUSTOM_OBJECT_3951 0x009
#define ID_CUSTOM_OBJECT_08CF 0x00a
#define ID_CUSTOM_OBJECT_08CC 0x00b
#define ID_CUSTOM_OBJECT_10D2 0x00c
#define ID_CUSTOM_OBJECT_0943 0x00d
#define ID_CUSTOM_OBJECT_0944 0x00e
#define ID_CUSTOM_OBJECT_08CE 0x00f
#define ID_CUSTOM_OBJECT_0952 0x010
#define ID_CUSTOM_OBJECT_0953 0x011
#define ID_CUSTOM_OBJECT_1826 0x012
#define ID_CUSTOM_OBJECT_1180 0x013
#define ID_CUSTOM_OBJECT_1919 0x014
#define ID_CUSTOM_OBJECT_0911 0x015
#define ID_CUSTOM_OBJECT_310B 0x016
#define ID_CUSTOM_OBJECT_10D0 0x017
#define ID_CUSTOM_OBJECT_08D1 0x018
#define ID_CUSTOM_OBJECT_0A12 0x019
#define ID_CUSTOM_OBJECT_097C 0x01a
#define ID_CUSTOM_OBJECT_097D 0x01b
#define ID_CUSTOM_OBJECT_097E 0x01c
#define ID_CUSTOM_OBJECT_097B 0x01d
#define ID_CUSTOM_OBJECT_097A 0x01e
#define ID_CUSTOM_OBJECT_0976 0x01f
#define ID_CUSTOM_OBJECT_0977 0x020
#define ID_CUSTOM_OBJECT_0978 0x021
#define ID_CUSTOM_OBJECT_0979 0x022
#define ID_CUSTOM_OBJECT_0975 0x023
#define ID_CUSTOM_OBJECT_0974 0x024
#define ID_CUSTOM_OBJECT_0973 0x025
#define ID_CUSTOM_OBJECT_0972 0x026
#define ID_CUSTOM_OBJECT_0971 0x027
#define ID_CUSTOM_OBJECT_0970 0x028
#define ID_CUSTOM_OBJECT_096F 0x029
#define ID_CUSTOM_OBJECT_096E 0x02a
#define ID_CUSTOM_OBJECT_1182 0x02b
#define ID_CUSTOM_OBJECT_1181 0x02c
#define ID_CUSTOM_OBJECT_110A 0x02d
#define ID_CUSTOM_OBJECT_1109 0x02e
#define ID_CUSTOM_OBJECT_1108 0x02f
#define ID_CUSTOM_OBJECT_10DF 0x030
#define ID_CUSTOM_OBJECT_10DE 0x031
#define ID_CUSTOM_OBJECT_10DD 0x032
#define ID_CUSTOM_OBJECT_10DC 0x033
#define ID_CUSTOM_OBJECT_10DB 0x034
#define ID_CUSTOM_OBJECT_10D6 0x035
#define ID_CUSTOM_OBJECT_10D7 0x036
#define ID_CUSTOM_OBJECT_10D8 0x037
#define ID_CUSTOM_OBJECT_116C 0x038
#define ID_CUSTOM_OBJECT_10D5 0x039
#define ID_CUSTOM_OBJECT_10DA 0x03a
#define ID_CUSTOM_OBJECT_18D4 0x03b
#define ID_CUSTOM_OBJECT_18CD 0x03c
#define ID_CUSTOM_OBJECT_18D3 0x03d
#define ID_CUSTOM_OBJECT_10EA 0x03e
#define ID_CUSTOM_OBJECT_18EC 0x03f
#define ID_CUSTOM_OBJECT_10EB 0x040
#define ID_CUSTOM_OBJECT_18E6 0x041
#define ID_CUSTOM_OBJECT_10E8 0x042
#define ID_CUSTOM_OBJECT_10E9 0x043
#define ID_CUSTOM_OBJECT_10E7 0x044
#define ID_CUSTOM_OBJECT_10E3 0x045
#define ID_CUSTOM_OBJECT_10E5 0x046
#define ID_CUSTOM_OBJECT_10E4 0x047
#define ID_CUSTOM_OBJECT_18E2 0x048
#define ID_CUSTOM_OBJECT_10EE 0x049
#define ID_CUSTOM_OBJECT_18ED 0x04a
#define ID_CUSTOM_OBJECT_10F6 0x04b
#define ID_CUSTOM_OBJECT_10F7 0x04c
#define ID_CUSTOM_OBJECT_10F5 0x04d
#define ID_CUSTOM_OBJECT_10F8 0x04e
#define ID_CUSTOM_OBJECT_18EF 0x04f
#define ID_CUSTOM_OBJECT_18F0 0x050
#define ID_CUSTOM_OBJECT_10F9 0x051
#define ID_CUSTOM_OBJECT_10FA 0x052
#define ID_CUSTOM_OBJECT_10FB 0x053
#define ID_CUSTOM_OBJECT_10FD 0x054
#define ID_CUSTOM_OBJECT_10FC 0x055
#define ID_CUSTOM_OBJECT_10FE 0x056
#define ID_CUSTOM_OBJECT_10FF 0x057
#define ID_CUSTOM_OBJECT_20F1 0x058
#define ID_CUSTOM_OBJECT_10F4 0x059
#define ID_CUSTOM_OBJECT_10F3 0x05a
#define ID_CUSTOM_OBJECT_10F2 0x05b
#define ID_CUSTOM_OBJECT_1101 0x05c
#define ID_CUSTOM_OBJECT_1100 0x05d
#define ID_CUSTOM_OBJECT_1102 0x05e
#define ID_CUSTOM_OBJECT_1103 0x05f
#define ID_CUSTOM_OBJECT_1106 0x060
#define ID_CUSTOM_OBJECT_1107 0x061
#define ID_CUSTOM_OBJECT_1104 0x062
#define ID_CUSTOM_OBJECT_1105 0x063
#define ID_CUSTOM_OBJECT_0A53 0x064
#define ID_CUSTOM_OBJECT_080F 0x065
#define ID_CUSTOM_OBJECT_096A 0x066
#define ID_CUSTOM_OBJECT_0A66 0x067
#define ID_CUSTOM_OBJECT_0A65 0x068
#define ID_CUSTOM_OBJECT_0A64 0x069
#define ID_CUSTOM_OBJECT_0A63 0x06a
#define ID_CUSTOM_OBJECT_0A62 0x06b
#define ID_CUSTOM_OBJECT_1221 0x06c
#define ID_CUSTOM_OBJECT_096B 0x06d
#define ID_CUSTOM_OBJECT_0969 0x06e
#define ID_CUSTOM_OBJECT_1A7F 0x06f
#define ID_CUSTOM_OBJECT_227E 0x070

#define ID_TRIGGER_0007 0x071
#define ID_TRIGGER_0006 0x072
#define ID_TRIGGER_0008 0x073
#define ID_TRIGGER_0000 0x074
#define ID_TRIGGER_0001 0x075
#define ID_TRIGGER_0002 0x076
#define ID_TRIGGER_0005 0x077
#define ID_TRIGGER_0004 0x078
#define ID_TRIGGER_0003 0x079
#define ID_TRIGGER_0009 0x07a
#define ID_TRIGGER_0024 0x07b
#define ID_TRIGGER_000B 0x07c
#define ID_TRIGGER_0010 0x07d
#define ID_TRIGGER_000D 0x07e
#define ID_TRIGGER_000C 0x07f
#define ID_TRIGGER_0011 0x080
#define ID_TRIGGER_0013 0x081
#define ID_TRIGGER_001B 0x082
#define ID_TRIGGER_001C 0x083
#define ID_TRIGGER_0020 0x084
#define ID_TRIGGER_001F 0x085
#define ID_TRIGGER_0015 0x086
#define ID_TRIGGER_0014 0x087
#define ID_TRIGGER_001D 0x088
#define ID_TRIGGER_0022 0x089
#define ID_TRIGGER_0018 0x08a
#define ID_TRIGGER_0017 0x08b
#define ID_TRIGGER_001A 0x08c
#define ID_TRIGGER_0019 0x08d
#define ID_TRIGGER_0016 0x08e
#define ID_TRIGGER_0012 0x08f
#define ID_TRIGGER_0021 0x090
#define ID_TRIGGER_001E 0x091
#define ID_TRIGGER_0025 0x092
#define ID_TRIGGER_0023 0x093
#define ID_TRIGGER_0026 0x094

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

class CustomObjectScript_0985 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0942 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0941 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_092B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_093E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0940 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_093F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0954 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3951 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08CF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08CC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0943 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0944 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08CE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0952 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0953 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1826 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1180 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1919 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0911 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_310B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A12 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0976 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0977 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0978 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0979 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0975 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0974 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0973 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0972 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0971 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0970 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1182 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1181 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_110A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1109 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1108 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_116C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18D4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18CD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18D3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10EA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18EC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10EB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18E6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18E2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10EE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18ED : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18EF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18F0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20F1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1101 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1100 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1102 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1103 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1106 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1107 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1104 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1105 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A53 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A66 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A65 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A64 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A63 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A62 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1221 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0969 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1A7F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_227E : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
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

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0024 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0010 : public BaseScript {
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

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0022 : public BaseScript {
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

class TriggerScript_001A : public BaseScript {
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

class TriggerScript_0012 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0021 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0025 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0023 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0026 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_130 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_171 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_125 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_131 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_075 = 0;
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
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_156 = 0;
static int ScriptActionCtr_132 = 0;
static int ScriptActionCtr_129 = 0;
static int ScriptActionCtr_153 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_136 = 0;
static int ScriptActionCtr_133 = 0;
static int ScriptActionCtr_134 = 0;
static int ScriptActionCtr_140 = 0;
static int ScriptActionCtr_149 = 0;
static int ScriptActionCtr_139 = 0;
static int ScriptActionCtr_150 = 0;
static int ScriptActionCtr_145 = 0;
static int ScriptActionCtr_138 = 0;
static int ScriptActionCtr_137 = 0;
static int ScriptActionCtr_135 = 0;
static int ScriptActionCtr_141 = 0;
static int ScriptActionCtr_148 = 0;
static int ScriptActionCtr_147 = 0;
static int ScriptActionCtr_144 = 0;
static int ScriptActionCtr_143 = 0;
static int ScriptActionCtr_142 = 0;
static int ScriptActionCtr_146 = 0;
static int ScriptActionCtr_152 = 0;
static int ScriptActionCtr_151 = 0;
static int ScriptActionCtr_155 = 0;
static int ScriptActionCtr_154 = 0;
static int ScriptActionCtr_160 = 0;
static int ScriptActionCtr_159 = 0;
static int ScriptActionCtr_158 = 0;
static int ScriptActionCtr_157 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_165 = 0;
static int ScriptActionCtr_164 = 0;
static int ScriptActionCtr_163 = 0;
static int ScriptActionCtr_162 = 0;
static int ScriptActionCtr_161 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_166 = 0;
static int ScriptActionCtr_169 = 0;
static int ScriptActionCtr_168 = 0;
static int ScriptActionCtr_167 = 0;
static int ScriptActionCtr_170 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_130 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_171 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_125 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_131 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_078 = 0;
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
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_156 = 0;
  ScriptActionCtr_132 = 0;
  ScriptActionCtr_129 = 0;
  ScriptActionCtr_153 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_136 = 0;
  ScriptActionCtr_133 = 0;
  ScriptActionCtr_134 = 0;
  ScriptActionCtr_140 = 0;
  ScriptActionCtr_149 = 0;
  ScriptActionCtr_139 = 0;
  ScriptActionCtr_150 = 0;
  ScriptActionCtr_145 = 0;
  ScriptActionCtr_138 = 0;
  ScriptActionCtr_137 = 0;
  ScriptActionCtr_135 = 0;
  ScriptActionCtr_141 = 0;
  ScriptActionCtr_148 = 0;
  ScriptActionCtr_147 = 0;
  ScriptActionCtr_144 = 0;
  ScriptActionCtr_143 = 0;
  ScriptActionCtr_142 = 0;
  ScriptActionCtr_146 = 0;
  ScriptActionCtr_152 = 0;
  ScriptActionCtr_151 = 0;
  ScriptActionCtr_155 = 0;
  ScriptActionCtr_154 = 0;
  ScriptActionCtr_160 = 0;
  ScriptActionCtr_159 = 0;
  ScriptActionCtr_158 = 0;
  ScriptActionCtr_157 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_165 = 0;
  ScriptActionCtr_164 = 0;
  ScriptActionCtr_163 = 0;
  ScriptActionCtr_162 = 0;
  ScriptActionCtr_161 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_166 = 0;
  ScriptActionCtr_169 = 0;
  ScriptActionCtr_168 = 0;
  ScriptActionCtr_167 = 0;
  ScriptActionCtr_170 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_130, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_171, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
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
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_156, file_ptr);
  File_WriteInt(ScriptActionCtr_132, file_ptr);
  File_WriteInt(ScriptActionCtr_129, file_ptr);
  File_WriteInt(ScriptActionCtr_153, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_136, file_ptr);
  File_WriteInt(ScriptActionCtr_133, file_ptr);
  File_WriteInt(ScriptActionCtr_134, file_ptr);
  File_WriteInt(ScriptActionCtr_140, file_ptr);
  File_WriteInt(ScriptActionCtr_149, file_ptr);
  File_WriteInt(ScriptActionCtr_139, file_ptr);
  File_WriteInt(ScriptActionCtr_150, file_ptr);
  File_WriteInt(ScriptActionCtr_145, file_ptr);
  File_WriteInt(ScriptActionCtr_138, file_ptr);
  File_WriteInt(ScriptActionCtr_137, file_ptr);
  File_WriteInt(ScriptActionCtr_135, file_ptr);
  File_WriteInt(ScriptActionCtr_141, file_ptr);
  File_WriteInt(ScriptActionCtr_148, file_ptr);
  File_WriteInt(ScriptActionCtr_147, file_ptr);
  File_WriteInt(ScriptActionCtr_144, file_ptr);
  File_WriteInt(ScriptActionCtr_143, file_ptr);
  File_WriteInt(ScriptActionCtr_142, file_ptr);
  File_WriteInt(ScriptActionCtr_146, file_ptr);
  File_WriteInt(ScriptActionCtr_152, file_ptr);
  File_WriteInt(ScriptActionCtr_151, file_ptr);
  File_WriteInt(ScriptActionCtr_155, file_ptr);
  File_WriteInt(ScriptActionCtr_154, file_ptr);
  File_WriteInt(ScriptActionCtr_160, file_ptr);
  File_WriteInt(ScriptActionCtr_159, file_ptr);
  File_WriteInt(ScriptActionCtr_158, file_ptr);
  File_WriteInt(ScriptActionCtr_157, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_165, file_ptr);
  File_WriteInt(ScriptActionCtr_164, file_ptr);
  File_WriteInt(ScriptActionCtr_163, file_ptr);
  File_WriteInt(ScriptActionCtr_162, file_ptr);
  File_WriteInt(ScriptActionCtr_161, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_166, file_ptr);
  File_WriteInt(ScriptActionCtr_169, file_ptr);
  File_WriteInt(ScriptActionCtr_168, file_ptr);
  File_WriteInt(ScriptActionCtr_167, file_ptr);
  File_WriteInt(ScriptActionCtr_170, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_130 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_171 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_156 = File_ReadInt(file_ptr);
  ScriptActionCtr_132 = File_ReadInt(file_ptr);
  ScriptActionCtr_129 = File_ReadInt(file_ptr);
  ScriptActionCtr_153 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_136 = File_ReadInt(file_ptr);
  ScriptActionCtr_133 = File_ReadInt(file_ptr);
  ScriptActionCtr_134 = File_ReadInt(file_ptr);
  ScriptActionCtr_140 = File_ReadInt(file_ptr);
  ScriptActionCtr_149 = File_ReadInt(file_ptr);
  ScriptActionCtr_139 = File_ReadInt(file_ptr);
  ScriptActionCtr_150 = File_ReadInt(file_ptr);
  ScriptActionCtr_145 = File_ReadInt(file_ptr);
  ScriptActionCtr_138 = File_ReadInt(file_ptr);
  ScriptActionCtr_137 = File_ReadInt(file_ptr);
  ScriptActionCtr_135 = File_ReadInt(file_ptr);
  ScriptActionCtr_141 = File_ReadInt(file_ptr);
  ScriptActionCtr_148 = File_ReadInt(file_ptr);
  ScriptActionCtr_147 = File_ReadInt(file_ptr);
  ScriptActionCtr_144 = File_ReadInt(file_ptr);
  ScriptActionCtr_143 = File_ReadInt(file_ptr);
  ScriptActionCtr_142 = File_ReadInt(file_ptr);
  ScriptActionCtr_146 = File_ReadInt(file_ptr);
  ScriptActionCtr_152 = File_ReadInt(file_ptr);
  ScriptActionCtr_151 = File_ReadInt(file_ptr);
  ScriptActionCtr_155 = File_ReadInt(file_ptr);
  ScriptActionCtr_154 = File_ReadInt(file_ptr);
  ScriptActionCtr_160 = File_ReadInt(file_ptr);
  ScriptActionCtr_159 = File_ReadInt(file_ptr);
  ScriptActionCtr_158 = File_ReadInt(file_ptr);
  ScriptActionCtr_157 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_165 = File_ReadInt(file_ptr);
  ScriptActionCtr_164 = File_ReadInt(file_ptr);
  ScriptActionCtr_163 = File_ReadInt(file_ptr);
  ScriptActionCtr_162 = File_ReadInt(file_ptr);
  ScriptActionCtr_161 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_166 = File_ReadInt(file_ptr);
  ScriptActionCtr_169 = File_ReadInt(file_ptr);
  ScriptActionCtr_168 = File_ReadInt(file_ptr);
  ScriptActionCtr_167 = File_ReadInt(file_ptr);
  ScriptActionCtr_170 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
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
2:Cave
3:MineCar
4:FirstMain
5:SecondMain
6:Key
7:PreShip
8:RescueShip
9:Dungeon
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

#define NUM_DOOR_NAMES 19
static const char *const Door_names[NUM_DOOR_NAMES] = {
    "ExitDoor-1",   "VertShaft",       "LockedDoor-3",    "LockedDoor-4", "LockedDoor-1",
    "LockedDoor-2", "SecondaryDoor-1", "SecondaryDoor-2", "EX-Right-2",   "EX-Left-1",
    "EX-Right-3",   "EX-Left-2",       "EX-Right-4",      "EX-Left-3",    "EX-Right-1",
    "EX-Left-4",    "AnotherDoor-2",   "AnotherDoor-1",   "EscapeDoor-1"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 137
static const char *const Object_names[NUM_OBJECT_NAMES] = {"EndLevelCam",
                                                           "KeyCard",
                                                           "BackSmallPipe-2",
                                                           "BackSmallPipe-1",
                                                           "FirstFFPipe",
                                                           "MainFFPipe-1",
                                                           "MainFFPipe-3",
                                                           "MainFFPipe-2",
                                                           "HWFFPipe-1",
                                                           "HWFFPipe-2",
                                                           "FFPipeExtra-2",
                                                           "FFPipeExtra-1",
                                                           "SmallPipePrison-2",
                                                           "PrisonSmallPipe-3",
                                                           "SmallPipePrison-1",
                                                           "SlaveGun-41",
                                                           "SlaveGun-44",
                                                           "SlaveGun-42",
                                                           "SlaveGun-43",
                                                           "SlaveGun-34",
                                                           "SlaveGun-33",
                                                           "SlaveGun-31",
                                                           "SlaveGun-32",
                                                           "SlaveGun-21",
                                                           "SlaveGun-23",
                                                           "SlaveGun-22",
                                                           "SlaveGun-51",
                                                           "SlaveGun-52",
                                                           "SlaveGun-72",
                                                           "SlaveGun-71",
                                                           "SlaveGun-B4",
                                                           "SlaveGun-B1",
                                                           "SlaveGun-B2",
                                                           "SlaveGun-B3",
                                                           "SlaveGun-62",
                                                           "SlaveGun-64",
                                                           "SlaveGun-63",
                                                           "SlaveGun-61",
                                                           "SlaveGun-81",
                                                           "SlaveGun-83",
                                                           "SlaveGun-82",
                                                           "SlaveGun-92",
                                                           "SlaveGun-93",
                                                           "SlaveGun-91",
                                                           "SlaveGun-A1",
                                                           "SlaveGun-C1",
                                                           "SlaveGun-C2",
                                                           "SlaveGun-D2",
                                                           "SlaveGun-D1",
                                                           "SlaveGun-F2",
                                                           "SlaveGun-F1",
                                                           "SlaveGun-E2",
                                                           "SlaveGun-E1",
                                                           "SlaveGun-12",
                                                           "SlaveGun-11",
                                                           "Camera-1",
                                                           "FFControlHW-1",
                                                           "HW-1",
                                                           "FFControlHW-2",
                                                           "HW-2",
                                                           "FFControlFirst",
                                                           "FirstPopUp",
                                                           "FFControlMain-1",
                                                           "Main-1",
                                                           "FFControlMain-2",
                                                           "Main-2",
                                                           "FFControlMain-3",
                                                           "Main-3",
                                                           "FFControlExtra-2",
                                                           "Extra-2",
                                                           "FFControlExtra-1",
                                                           "Extra-1",
                                                           "PrisonShip",
                                                           "MineSwitch-1",
                                                           "MineCart-1",
                                                           "MineSwitch-2",
                                                           "MineCart-2",
                                                           "RockWallTop-1",
                                                           "RockWallBottom-1",
                                                           "RockWallBottom-2",
                                                           "RockWallBottom-3",
                                                           "RockWallBottom-4",
                                                           "RockWallTop-6",
                                                           "RockWallTop-2",
                                                           "WindowPump-1",
                                                           "WindowPump-2",
                                                           "GenericSpew-18",
                                                           "GSpew17",
                                                           "GSpew16",
                                                           "GSpew15",
                                                           "GSpew14",
                                                           "GSpew13",
                                                           "GSpew12",
                                                           "GSpew11",
                                                           "GSpew10",
                                                           "GSpew9",
                                                           "GSpew8",
                                                           "GSpew7",
                                                           "GSpew6",
                                                           "GSpew5",
                                                           "GSpew4",
                                                           "GSpew3",
                                                           "GSpew2",
                                                           "GSpew1",
                                                           "AnotherSwitch-2",
                                                           "AnotherSwitch-1",
                                                           "Camera-F",
                                                           "Camera-E",
                                                           "Camera-D",
                                                           "Camera-C",
                                                           "Camera-B",
                                                           "Camera-A",
                                                           "Camera-9",
                                                           "Camera-8",
                                                           "Camera-7",
                                                           "Camera-6",
                                                           "Camera-5",
                                                           "Camera-4",
                                                           "Camera-3",
                                                           "Camera-2",
                                                           "Sparker-1",
                                                           "Sparker-2",
                                                           "Sparker-3",
                                                           "Sparker-4",
                                                           "PrisonFreeSwitch",
                                                           "PSpark-1",
                                                           "PSpark-2",
                                                           "PSpark-3",
                                                           "ExitDoor-1",
                                                           "PSwitch6",
                                                           "PSwitch5",
                                                           "PSwitch4",
                                                           "PSwitch3",
                                                           "PFSwitch2",
                                                           "PFSwitch1",
                                                           "SEFFSwitch-2",
                                                           "SEFFSwitch-1"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 10
static const char *const Room_names[NUM_ROOM_NAMES] = {"HugeWHouse-2", "HugeWHouse-1",  "FirstFFRoom", "MainFFRoom",
                                                       "Extra-1",      "Extra-2",       "Prisoner-3",  "Prisoner-2",
                                                       "Prisoner-1",   "SecretElevator"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 36
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "NearingTop-2",   "NearingTop-1",   "EnteredMine",    "X-Left-1",      "X-Left-2",       "X-Left-3",
    "X-Right-1",      "X-Right-2",      "X-Right-3",      "AboutToLeave",  "PipeDemoBackup", "PipeDemo",
    "EscapeDoor-Bar", "EscapeDoor-2",   "EscapeDoor-1",   "Music-Cave",    "Music-Terrain",  "Music-MineCar2",
    "Music-MineCar1", "Music-Main5",    "Music-Main4",    "Music-Main3",   "Music-Main2",    "Music-Main1",
    "Music-Second1",  "Music-PreShip2", "Music-PreShip1", "Music-Key4",    "Music-Key3",     "Music-Key2",
    "Music-Key1",     "Music-Dungeon2", "Music-Dungeon1", "PlayerCheat-3", "PlayerCheat-1",  "PrisonCinema"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 7
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "AmbEnergyPumpB", "AmbSwitch41", "Powerup pickup", "AmbSwitch31", "AmbMineCar", "AmbFurn21", "Siren"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 10
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCam",   "IntroShip",   "CameraShow",  "EscapeRoute-1",
                                                       "MineCart-1", "MineCart-2",  "CapturedCam", "Captured",
                                                       "PipeDemo",   "PrisonCinema"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 8
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Destroy secondary forcefield generator",
                                                       "Shoot switches to avoid forcefield",
                                                       "Destroy primary forcefield generators",
                                                       "Disable secondary forcefield controls",
                                                       "Disable primary forcefield controls",
                                                       "Get past the blocked entrance",
                                                       "Rescue the Prisoner",
                                                       "Release the prisoner"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 16
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"Work",
                                                             "FirstCamera",
                                                             "ForcefieldDisabled",
                                                             "MainDestroyed",
                                                             "ForcefieldsDisabled",
                                                             "ForcefieldFirst",
                                                             "PickupKey",
                                                             "DoorUnlocked",
                                                             "Spotted",
                                                             "GotHim",
                                                             "FreeAtLast",
                                                             "GoUpLeft",
                                                             "PipeDemo",
                                                             "Reroute",
                                                             "All6Deactive",
                                                             "DestroyThese"};
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
    strcpy(filename, "level11.msg");
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
  case ID_CUSTOM_OBJECT_0985:
    return new CustomObjectScript_0985;
    break;
  case ID_CUSTOM_OBJECT_0942:
    return new CustomObjectScript_0942;
    break;
  case ID_CUSTOM_OBJECT_0941:
    return new CustomObjectScript_0941;
    break;
  case ID_CUSTOM_OBJECT_092B:
    return new CustomObjectScript_092B;
    break;
  case ID_CUSTOM_OBJECT_093E:
    return new CustomObjectScript_093E;
    break;
  case ID_CUSTOM_OBJECT_0940:
    return new CustomObjectScript_0940;
    break;
  case ID_CUSTOM_OBJECT_093F:
    return new CustomObjectScript_093F;
    break;
  case ID_CUSTOM_OBJECT_0954:
    return new CustomObjectScript_0954;
    break;
  case ID_CUSTOM_OBJECT_3951:
    return new CustomObjectScript_3951;
    break;
  case ID_CUSTOM_OBJECT_08CF:
    return new CustomObjectScript_08CF;
    break;
  case ID_CUSTOM_OBJECT_08CC:
    return new CustomObjectScript_08CC;
    break;
  case ID_CUSTOM_OBJECT_10D2:
    return new CustomObjectScript_10D2;
    break;
  case ID_CUSTOM_OBJECT_0943:
    return new CustomObjectScript_0943;
    break;
  case ID_CUSTOM_OBJECT_0944:
    return new CustomObjectScript_0944;
    break;
  case ID_CUSTOM_OBJECT_08CE:
    return new CustomObjectScript_08CE;
    break;
  case ID_CUSTOM_OBJECT_0952:
    return new CustomObjectScript_0952;
    break;
  case ID_CUSTOM_OBJECT_0953:
    return new CustomObjectScript_0953;
    break;
  case ID_CUSTOM_OBJECT_1826:
    return new CustomObjectScript_1826;
    break;
  case ID_CUSTOM_OBJECT_1180:
    return new CustomObjectScript_1180;
    break;
  case ID_CUSTOM_OBJECT_1919:
    return new CustomObjectScript_1919;
    break;
  case ID_CUSTOM_OBJECT_0911:
    return new CustomObjectScript_0911;
    break;
  case ID_CUSTOM_OBJECT_310B:
    return new CustomObjectScript_310B;
    break;
  case ID_CUSTOM_OBJECT_10D0:
    return new CustomObjectScript_10D0;
    break;
  case ID_CUSTOM_OBJECT_08D1:
    return new CustomObjectScript_08D1;
    break;
  case ID_CUSTOM_OBJECT_0A12:
    return new CustomObjectScript_0A12;
    break;
  case ID_CUSTOM_OBJECT_097C:
    return new CustomObjectScript_097C;
    break;
  case ID_CUSTOM_OBJECT_097D:
    return new CustomObjectScript_097D;
    break;
  case ID_CUSTOM_OBJECT_097E:
    return new CustomObjectScript_097E;
    break;
  case ID_CUSTOM_OBJECT_097B:
    return new CustomObjectScript_097B;
    break;
  case ID_CUSTOM_OBJECT_097A:
    return new CustomObjectScript_097A;
    break;
  case ID_CUSTOM_OBJECT_0976:
    return new CustomObjectScript_0976;
    break;
  case ID_CUSTOM_OBJECT_0977:
    return new CustomObjectScript_0977;
    break;
  case ID_CUSTOM_OBJECT_0978:
    return new CustomObjectScript_0978;
    break;
  case ID_CUSTOM_OBJECT_0979:
    return new CustomObjectScript_0979;
    break;
  case ID_CUSTOM_OBJECT_0975:
    return new CustomObjectScript_0975;
    break;
  case ID_CUSTOM_OBJECT_0974:
    return new CustomObjectScript_0974;
    break;
  case ID_CUSTOM_OBJECT_0973:
    return new CustomObjectScript_0973;
    break;
  case ID_CUSTOM_OBJECT_0972:
    return new CustomObjectScript_0972;
    break;
  case ID_CUSTOM_OBJECT_0971:
    return new CustomObjectScript_0971;
    break;
  case ID_CUSTOM_OBJECT_0970:
    return new CustomObjectScript_0970;
    break;
  case ID_CUSTOM_OBJECT_096F:
    return new CustomObjectScript_096F;
    break;
  case ID_CUSTOM_OBJECT_096E:
    return new CustomObjectScript_096E;
    break;
  case ID_CUSTOM_OBJECT_1182:
    return new CustomObjectScript_1182;
    break;
  case ID_CUSTOM_OBJECT_1181:
    return new CustomObjectScript_1181;
    break;
  case ID_CUSTOM_OBJECT_110A:
    return new CustomObjectScript_110A;
    break;
  case ID_CUSTOM_OBJECT_1109:
    return new CustomObjectScript_1109;
    break;
  case ID_CUSTOM_OBJECT_1108:
    return new CustomObjectScript_1108;
    break;
  case ID_CUSTOM_OBJECT_10DF:
    return new CustomObjectScript_10DF;
    break;
  case ID_CUSTOM_OBJECT_10DE:
    return new CustomObjectScript_10DE;
    break;
  case ID_CUSTOM_OBJECT_10DD:
    return new CustomObjectScript_10DD;
    break;
  case ID_CUSTOM_OBJECT_10DC:
    return new CustomObjectScript_10DC;
    break;
  case ID_CUSTOM_OBJECT_10DB:
    return new CustomObjectScript_10DB;
    break;
  case ID_CUSTOM_OBJECT_10D6:
    return new CustomObjectScript_10D6;
    break;
  case ID_CUSTOM_OBJECT_10D7:
    return new CustomObjectScript_10D7;
    break;
  case ID_CUSTOM_OBJECT_10D8:
    return new CustomObjectScript_10D8;
    break;
  case ID_CUSTOM_OBJECT_116C:
    return new CustomObjectScript_116C;
    break;
  case ID_CUSTOM_OBJECT_10D5:
    return new CustomObjectScript_10D5;
    break;
  case ID_CUSTOM_OBJECT_10DA:
    return new CustomObjectScript_10DA;
    break;
  case ID_CUSTOM_OBJECT_18D4:
    return new CustomObjectScript_18D4;
    break;
  case ID_CUSTOM_OBJECT_18CD:
    return new CustomObjectScript_18CD;
    break;
  case ID_CUSTOM_OBJECT_18D3:
    return new CustomObjectScript_18D3;
    break;
  case ID_CUSTOM_OBJECT_10EA:
    return new CustomObjectScript_10EA;
    break;
  case ID_CUSTOM_OBJECT_18EC:
    return new CustomObjectScript_18EC;
    break;
  case ID_CUSTOM_OBJECT_10EB:
    return new CustomObjectScript_10EB;
    break;
  case ID_CUSTOM_OBJECT_18E6:
    return new CustomObjectScript_18E6;
    break;
  case ID_CUSTOM_OBJECT_10E8:
    return new CustomObjectScript_10E8;
    break;
  case ID_CUSTOM_OBJECT_10E9:
    return new CustomObjectScript_10E9;
    break;
  case ID_CUSTOM_OBJECT_10E7:
    return new CustomObjectScript_10E7;
    break;
  case ID_CUSTOM_OBJECT_10E3:
    return new CustomObjectScript_10E3;
    break;
  case ID_CUSTOM_OBJECT_10E5:
    return new CustomObjectScript_10E5;
    break;
  case ID_CUSTOM_OBJECT_10E4:
    return new CustomObjectScript_10E4;
    break;
  case ID_CUSTOM_OBJECT_18E2:
    return new CustomObjectScript_18E2;
    break;
  case ID_CUSTOM_OBJECT_10EE:
    return new CustomObjectScript_10EE;
    break;
  case ID_CUSTOM_OBJECT_18ED:
    return new CustomObjectScript_18ED;
    break;
  case ID_CUSTOM_OBJECT_10F6:
    return new CustomObjectScript_10F6;
    break;
  case ID_CUSTOM_OBJECT_10F7:
    return new CustomObjectScript_10F7;
    break;
  case ID_CUSTOM_OBJECT_10F5:
    return new CustomObjectScript_10F5;
    break;
  case ID_CUSTOM_OBJECT_10F8:
    return new CustomObjectScript_10F8;
    break;
  case ID_CUSTOM_OBJECT_18EF:
    return new CustomObjectScript_18EF;
    break;
  case ID_CUSTOM_OBJECT_18F0:
    return new CustomObjectScript_18F0;
    break;
  case ID_CUSTOM_OBJECT_10F9:
    return new CustomObjectScript_10F9;
    break;
  case ID_CUSTOM_OBJECT_10FA:
    return new CustomObjectScript_10FA;
    break;
  case ID_CUSTOM_OBJECT_10FB:
    return new CustomObjectScript_10FB;
    break;
  case ID_CUSTOM_OBJECT_10FD:
    return new CustomObjectScript_10FD;
    break;
  case ID_CUSTOM_OBJECT_10FC:
    return new CustomObjectScript_10FC;
    break;
  case ID_CUSTOM_OBJECT_10FE:
    return new CustomObjectScript_10FE;
    break;
  case ID_CUSTOM_OBJECT_10FF:
    return new CustomObjectScript_10FF;
    break;
  case ID_CUSTOM_OBJECT_20F1:
    return new CustomObjectScript_20F1;
    break;
  case ID_CUSTOM_OBJECT_10F4:
    return new CustomObjectScript_10F4;
    break;
  case ID_CUSTOM_OBJECT_10F3:
    return new CustomObjectScript_10F3;
    break;
  case ID_CUSTOM_OBJECT_10F2:
    return new CustomObjectScript_10F2;
    break;
  case ID_CUSTOM_OBJECT_1101:
    return new CustomObjectScript_1101;
    break;
  case ID_CUSTOM_OBJECT_1100:
    return new CustomObjectScript_1100;
    break;
  case ID_CUSTOM_OBJECT_1102:
    return new CustomObjectScript_1102;
    break;
  case ID_CUSTOM_OBJECT_1103:
    return new CustomObjectScript_1103;
    break;
  case ID_CUSTOM_OBJECT_1106:
    return new CustomObjectScript_1106;
    break;
  case ID_CUSTOM_OBJECT_1107:
    return new CustomObjectScript_1107;
    break;
  case ID_CUSTOM_OBJECT_1104:
    return new CustomObjectScript_1104;
    break;
  case ID_CUSTOM_OBJECT_1105:
    return new CustomObjectScript_1105;
    break;
  case ID_CUSTOM_OBJECT_0A53:
    return new CustomObjectScript_0A53;
    break;
  case ID_CUSTOM_OBJECT_080F:
    return new CustomObjectScript_080F;
    break;
  case ID_CUSTOM_OBJECT_096A:
    return new CustomObjectScript_096A;
    break;
  case ID_CUSTOM_OBJECT_0A66:
    return new CustomObjectScript_0A66;
    break;
  case ID_CUSTOM_OBJECT_0A65:
    return new CustomObjectScript_0A65;
    break;
  case ID_CUSTOM_OBJECT_0A64:
    return new CustomObjectScript_0A64;
    break;
  case ID_CUSTOM_OBJECT_0A63:
    return new CustomObjectScript_0A63;
    break;
  case ID_CUSTOM_OBJECT_0A62:
    return new CustomObjectScript_0A62;
    break;
  case ID_CUSTOM_OBJECT_1221:
    return new CustomObjectScript_1221;
    break;
  case ID_CUSTOM_OBJECT_096B:
    return new CustomObjectScript_096B;
    break;
  case ID_CUSTOM_OBJECT_0969:
    return new CustomObjectScript_0969;
    break;
  case ID_CUSTOM_OBJECT_1A7F:
    return new CustomObjectScript_1A7F;
    break;
  case ID_CUSTOM_OBJECT_227E:
    return new CustomObjectScript_227E;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
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
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0024:
    return new TriggerScript_0024;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_0022:
    return new TriggerScript_0022;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0021:
    return new TriggerScript_0021;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_0025:
    return new TriggerScript_0025;
    break;
  case ID_TRIGGER_0023:
    return new TriggerScript_0023;
    break;
  case ID_TRIGGER_0026:
    return new TriggerScript_0026;
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
  case ID_CUSTOM_OBJECT_0985:
    delete ((CustomObjectScript_0985 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0942:
    delete ((CustomObjectScript_0942 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0941:
    delete ((CustomObjectScript_0941 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_092B:
    delete ((CustomObjectScript_092B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_093E:
    delete ((CustomObjectScript_093E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0940:
    delete ((CustomObjectScript_0940 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_093F:
    delete ((CustomObjectScript_093F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0954:
    delete ((CustomObjectScript_0954 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3951:
    delete ((CustomObjectScript_3951 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08CF:
    delete ((CustomObjectScript_08CF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08CC:
    delete ((CustomObjectScript_08CC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D2:
    delete ((CustomObjectScript_10D2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0943:
    delete ((CustomObjectScript_0943 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0944:
    delete ((CustomObjectScript_0944 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08CE:
    delete ((CustomObjectScript_08CE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0952:
    delete ((CustomObjectScript_0952 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0953:
    delete ((CustomObjectScript_0953 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1826:
    delete ((CustomObjectScript_1826 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1180:
    delete ((CustomObjectScript_1180 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1919:
    delete ((CustomObjectScript_1919 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0911:
    delete ((CustomObjectScript_0911 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_310B:
    delete ((CustomObjectScript_310B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D0:
    delete ((CustomObjectScript_10D0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D1:
    delete ((CustomObjectScript_08D1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A12:
    delete ((CustomObjectScript_0A12 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097C:
    delete ((CustomObjectScript_097C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097D:
    delete ((CustomObjectScript_097D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097E:
    delete ((CustomObjectScript_097E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097B:
    delete ((CustomObjectScript_097B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097A:
    delete ((CustomObjectScript_097A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0976:
    delete ((CustomObjectScript_0976 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0977:
    delete ((CustomObjectScript_0977 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0978:
    delete ((CustomObjectScript_0978 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0979:
    delete ((CustomObjectScript_0979 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0975:
    delete ((CustomObjectScript_0975 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0974:
    delete ((CustomObjectScript_0974 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0973:
    delete ((CustomObjectScript_0973 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0972:
    delete ((CustomObjectScript_0972 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0971:
    delete ((CustomObjectScript_0971 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0970:
    delete ((CustomObjectScript_0970 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096F:
    delete ((CustomObjectScript_096F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096E:
    delete ((CustomObjectScript_096E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1182:
    delete ((CustomObjectScript_1182 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1181:
    delete ((CustomObjectScript_1181 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_110A:
    delete ((CustomObjectScript_110A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1109:
    delete ((CustomObjectScript_1109 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1108:
    delete ((CustomObjectScript_1108 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DF:
    delete ((CustomObjectScript_10DF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DE:
    delete ((CustomObjectScript_10DE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DD:
    delete ((CustomObjectScript_10DD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DC:
    delete ((CustomObjectScript_10DC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DB:
    delete ((CustomObjectScript_10DB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D6:
    delete ((CustomObjectScript_10D6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D7:
    delete ((CustomObjectScript_10D7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D8:
    delete ((CustomObjectScript_10D8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_116C:
    delete ((CustomObjectScript_116C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D5:
    delete ((CustomObjectScript_10D5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DA:
    delete ((CustomObjectScript_10DA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18D4:
    delete ((CustomObjectScript_18D4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18CD:
    delete ((CustomObjectScript_18CD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18D3:
    delete ((CustomObjectScript_18D3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10EA:
    delete ((CustomObjectScript_10EA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18EC:
    delete ((CustomObjectScript_18EC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10EB:
    delete ((CustomObjectScript_10EB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18E6:
    delete ((CustomObjectScript_18E6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E8:
    delete ((CustomObjectScript_10E8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E9:
    delete ((CustomObjectScript_10E9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E7:
    delete ((CustomObjectScript_10E7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E3:
    delete ((CustomObjectScript_10E3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E5:
    delete ((CustomObjectScript_10E5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E4:
    delete ((CustomObjectScript_10E4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18E2:
    delete ((CustomObjectScript_18E2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10EE:
    delete ((CustomObjectScript_10EE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18ED:
    delete ((CustomObjectScript_18ED *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F6:
    delete ((CustomObjectScript_10F6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F7:
    delete ((CustomObjectScript_10F7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F5:
    delete ((CustomObjectScript_10F5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F8:
    delete ((CustomObjectScript_10F8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18EF:
    delete ((CustomObjectScript_18EF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18F0:
    delete ((CustomObjectScript_18F0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F9:
    delete ((CustomObjectScript_10F9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FA:
    delete ((CustomObjectScript_10FA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FB:
    delete ((CustomObjectScript_10FB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FD:
    delete ((CustomObjectScript_10FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FC:
    delete ((CustomObjectScript_10FC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FE:
    delete ((CustomObjectScript_10FE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FF:
    delete ((CustomObjectScript_10FF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20F1:
    delete ((CustomObjectScript_20F1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F4:
    delete ((CustomObjectScript_10F4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F3:
    delete ((CustomObjectScript_10F3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F2:
    delete ((CustomObjectScript_10F2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1101:
    delete ((CustomObjectScript_1101 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1100:
    delete ((CustomObjectScript_1100 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1102:
    delete ((CustomObjectScript_1102 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1103:
    delete ((CustomObjectScript_1103 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1106:
    delete ((CustomObjectScript_1106 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1107:
    delete ((CustomObjectScript_1107 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1104:
    delete ((CustomObjectScript_1104 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1105:
    delete ((CustomObjectScript_1105 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A53:
    delete ((CustomObjectScript_0A53 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080F:
    delete ((CustomObjectScript_080F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096A:
    delete ((CustomObjectScript_096A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A66:
    delete ((CustomObjectScript_0A66 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A65:
    delete ((CustomObjectScript_0A65 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A64:
    delete ((CustomObjectScript_0A64 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A63:
    delete ((CustomObjectScript_0A63 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A62:
    delete ((CustomObjectScript_0A62 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1221:
    delete ((CustomObjectScript_1221 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096B:
    delete ((CustomObjectScript_096B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0969:
    delete ((CustomObjectScript_0969 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1A7F:
    delete ((CustomObjectScript_1A7F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_227E:
    delete ((CustomObjectScript_227E *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
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
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0024:
    delete ((TriggerScript_0024 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_0022:
    delete ((TriggerScript_0022 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0021:
    delete ((TriggerScript_0021 *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_0025:
    delete ((TriggerScript_0025 *)ptr);
    break;
  case ID_TRIGGER_0023:
    delete ((TriggerScript_0023 *)ptr);
    break;
  case ID_TRIGGER_0026:
    delete ((TriggerScript_0026 *)ptr);
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
  case ID_CUSTOM_OBJECT_0985:
  case ID_CUSTOM_OBJECT_0942:
  case ID_CUSTOM_OBJECT_0941:
  case ID_CUSTOM_OBJECT_092B:
  case ID_CUSTOM_OBJECT_093E:
  case ID_CUSTOM_OBJECT_0940:
  case ID_CUSTOM_OBJECT_093F:
  case ID_CUSTOM_OBJECT_0954:
  case ID_CUSTOM_OBJECT_3951:
  case ID_CUSTOM_OBJECT_08CF:
  case ID_CUSTOM_OBJECT_08CC:
  case ID_CUSTOM_OBJECT_10D2:
  case ID_CUSTOM_OBJECT_0943:
  case ID_CUSTOM_OBJECT_0944:
  case ID_CUSTOM_OBJECT_08CE:
  case ID_CUSTOM_OBJECT_0952:
  case ID_CUSTOM_OBJECT_0953:
  case ID_CUSTOM_OBJECT_1826:
  case ID_CUSTOM_OBJECT_1180:
  case ID_CUSTOM_OBJECT_1919:
  case ID_CUSTOM_OBJECT_0911:
  case ID_CUSTOM_OBJECT_310B:
  case ID_CUSTOM_OBJECT_10D0:
  case ID_CUSTOM_OBJECT_08D1:
  case ID_CUSTOM_OBJECT_0A12:
  case ID_CUSTOM_OBJECT_097C:
  case ID_CUSTOM_OBJECT_097D:
  case ID_CUSTOM_OBJECT_097E:
  case ID_CUSTOM_OBJECT_097B:
  case ID_CUSTOM_OBJECT_097A:
  case ID_CUSTOM_OBJECT_0976:
  case ID_CUSTOM_OBJECT_0977:
  case ID_CUSTOM_OBJECT_0978:
  case ID_CUSTOM_OBJECT_0979:
  case ID_CUSTOM_OBJECT_0975:
  case ID_CUSTOM_OBJECT_0974:
  case ID_CUSTOM_OBJECT_0973:
  case ID_CUSTOM_OBJECT_0972:
  case ID_CUSTOM_OBJECT_0971:
  case ID_CUSTOM_OBJECT_0970:
  case ID_CUSTOM_OBJECT_096F:
  case ID_CUSTOM_OBJECT_096E:
  case ID_CUSTOM_OBJECT_1182:
  case ID_CUSTOM_OBJECT_1181:
  case ID_CUSTOM_OBJECT_110A:
  case ID_CUSTOM_OBJECT_1109:
  case ID_CUSTOM_OBJECT_1108:
  case ID_CUSTOM_OBJECT_10DF:
  case ID_CUSTOM_OBJECT_10DE:
  case ID_CUSTOM_OBJECT_10DD:
  case ID_CUSTOM_OBJECT_10DC:
  case ID_CUSTOM_OBJECT_10DB:
  case ID_CUSTOM_OBJECT_10D6:
  case ID_CUSTOM_OBJECT_10D7:
  case ID_CUSTOM_OBJECT_10D8:
  case ID_CUSTOM_OBJECT_116C:
  case ID_CUSTOM_OBJECT_10D5:
  case ID_CUSTOM_OBJECT_10DA:
  case ID_CUSTOM_OBJECT_18D4:
  case ID_CUSTOM_OBJECT_18CD:
  case ID_CUSTOM_OBJECT_18D3:
  case ID_CUSTOM_OBJECT_10EA:
  case ID_CUSTOM_OBJECT_18EC:
  case ID_CUSTOM_OBJECT_10EB:
  case ID_CUSTOM_OBJECT_18E6:
  case ID_CUSTOM_OBJECT_10E8:
  case ID_CUSTOM_OBJECT_10E9:
  case ID_CUSTOM_OBJECT_10E7:
  case ID_CUSTOM_OBJECT_10E3:
  case ID_CUSTOM_OBJECT_10E5:
  case ID_CUSTOM_OBJECT_10E4:
  case ID_CUSTOM_OBJECT_18E2:
  case ID_CUSTOM_OBJECT_10EE:
  case ID_CUSTOM_OBJECT_18ED:
  case ID_CUSTOM_OBJECT_10F6:
  case ID_CUSTOM_OBJECT_10F7:
  case ID_CUSTOM_OBJECT_10F5:
  case ID_CUSTOM_OBJECT_10F8:
  case ID_CUSTOM_OBJECT_18EF:
  case ID_CUSTOM_OBJECT_18F0:
  case ID_CUSTOM_OBJECT_10F9:
  case ID_CUSTOM_OBJECT_10FA:
  case ID_CUSTOM_OBJECT_10FB:
  case ID_CUSTOM_OBJECT_10FD:
  case ID_CUSTOM_OBJECT_10FC:
  case ID_CUSTOM_OBJECT_10FE:
  case ID_CUSTOM_OBJECT_10FF:
  case ID_CUSTOM_OBJECT_20F1:
  case ID_CUSTOM_OBJECT_10F4:
  case ID_CUSTOM_OBJECT_10F3:
  case ID_CUSTOM_OBJECT_10F2:
  case ID_CUSTOM_OBJECT_1101:
  case ID_CUSTOM_OBJECT_1100:
  case ID_CUSTOM_OBJECT_1102:
  case ID_CUSTOM_OBJECT_1103:
  case ID_CUSTOM_OBJECT_1106:
  case ID_CUSTOM_OBJECT_1107:
  case ID_CUSTOM_OBJECT_1104:
  case ID_CUSTOM_OBJECT_1105:
  case ID_CUSTOM_OBJECT_0A53:
  case ID_CUSTOM_OBJECT_080F:
  case ID_CUSTOM_OBJECT_096A:
  case ID_CUSTOM_OBJECT_0A66:
  case ID_CUSTOM_OBJECT_0A65:
  case ID_CUSTOM_OBJECT_0A64:
  case ID_CUSTOM_OBJECT_0A63:
  case ID_CUSTOM_OBJECT_0A62:
  case ID_CUSTOM_OBJECT_1221:
  case ID_CUSTOM_OBJECT_096B:
  case ID_CUSTOM_OBJECT_0969:
  case ID_CUSTOM_OBJECT_1A7F:
  case ID_CUSTOM_OBJECT_227E:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0024:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_0022:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0021:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_0025:
  case ID_TRIGGER_0023:
  case ID_TRIGGER_0026:
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
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0024;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0022;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[29] && trigger_face == Trigger_faces[29])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[30] && trigger_face == Trigger_faces[30])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[31] && trigger_face == Trigger_faces[31])
    return ID_TRIGGER_0021;

  if (trigger_room == Trigger_rooms[32] && trigger_face == Trigger_faces[32])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[33] && trigger_face == Trigger_faces[33])
    return ID_TRIGGER_0025;

  if (trigger_room == Trigger_rooms[34] && trigger_face == Trigger_faces[34])
    return ID_TRIGGER_0023;

  if (trigger_room == Trigger_rooms[35] && trigger_face == Trigger_faces[35])
    return ID_TRIGGER_0026;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[112];
  static int cust_id_list[112] = {
      ID_CUSTOM_OBJECT_0985, ID_CUSTOM_OBJECT_0942, ID_CUSTOM_OBJECT_0941, ID_CUSTOM_OBJECT_092B, ID_CUSTOM_OBJECT_093E,
      ID_CUSTOM_OBJECT_0940, ID_CUSTOM_OBJECT_093F, ID_CUSTOM_OBJECT_0954, ID_CUSTOM_OBJECT_3951, ID_CUSTOM_OBJECT_08CF,
      ID_CUSTOM_OBJECT_08CC, ID_CUSTOM_OBJECT_10D2, ID_CUSTOM_OBJECT_0943, ID_CUSTOM_OBJECT_0944, ID_CUSTOM_OBJECT_08CE,
      ID_CUSTOM_OBJECT_0952, ID_CUSTOM_OBJECT_0953, ID_CUSTOM_OBJECT_1826, ID_CUSTOM_OBJECT_1180, ID_CUSTOM_OBJECT_1919,
      ID_CUSTOM_OBJECT_0911, ID_CUSTOM_OBJECT_310B, ID_CUSTOM_OBJECT_10D0, ID_CUSTOM_OBJECT_08D1, ID_CUSTOM_OBJECT_0A12,
      ID_CUSTOM_OBJECT_097C, ID_CUSTOM_OBJECT_097D, ID_CUSTOM_OBJECT_097E, ID_CUSTOM_OBJECT_097B, ID_CUSTOM_OBJECT_097A,
      ID_CUSTOM_OBJECT_0976, ID_CUSTOM_OBJECT_0977, ID_CUSTOM_OBJECT_0978, ID_CUSTOM_OBJECT_0979, ID_CUSTOM_OBJECT_0975,
      ID_CUSTOM_OBJECT_0974, ID_CUSTOM_OBJECT_0973, ID_CUSTOM_OBJECT_0972, ID_CUSTOM_OBJECT_0971, ID_CUSTOM_OBJECT_0970,
      ID_CUSTOM_OBJECT_096F, ID_CUSTOM_OBJECT_096E, ID_CUSTOM_OBJECT_1182, ID_CUSTOM_OBJECT_1181, ID_CUSTOM_OBJECT_110A,
      ID_CUSTOM_OBJECT_1109, ID_CUSTOM_OBJECT_1108, ID_CUSTOM_OBJECT_10DF, ID_CUSTOM_OBJECT_10DE, ID_CUSTOM_OBJECT_10DD,
      ID_CUSTOM_OBJECT_10DC, ID_CUSTOM_OBJECT_10DB, ID_CUSTOM_OBJECT_10D6, ID_CUSTOM_OBJECT_10D7, ID_CUSTOM_OBJECT_10D8,
      ID_CUSTOM_OBJECT_116C, ID_CUSTOM_OBJECT_10D5, ID_CUSTOM_OBJECT_10DA, ID_CUSTOM_OBJECT_18D4, ID_CUSTOM_OBJECT_18CD,
      ID_CUSTOM_OBJECT_18D3, ID_CUSTOM_OBJECT_10EA, ID_CUSTOM_OBJECT_18EC, ID_CUSTOM_OBJECT_10EB, ID_CUSTOM_OBJECT_18E6,
      ID_CUSTOM_OBJECT_10E8, ID_CUSTOM_OBJECT_10E9, ID_CUSTOM_OBJECT_10E7, ID_CUSTOM_OBJECT_10E3, ID_CUSTOM_OBJECT_10E5,
      ID_CUSTOM_OBJECT_10E4, ID_CUSTOM_OBJECT_18E2, ID_CUSTOM_OBJECT_10EE, ID_CUSTOM_OBJECT_18ED, ID_CUSTOM_OBJECT_10F6,
      ID_CUSTOM_OBJECT_10F7, ID_CUSTOM_OBJECT_10F5, ID_CUSTOM_OBJECT_10F8, ID_CUSTOM_OBJECT_18EF, ID_CUSTOM_OBJECT_18F0,
      ID_CUSTOM_OBJECT_10F9, ID_CUSTOM_OBJECT_10FA, ID_CUSTOM_OBJECT_10FB, ID_CUSTOM_OBJECT_10FD, ID_CUSTOM_OBJECT_10FC,
      ID_CUSTOM_OBJECT_10FE, ID_CUSTOM_OBJECT_10FF, ID_CUSTOM_OBJECT_20F1, ID_CUSTOM_OBJECT_10F4, ID_CUSTOM_OBJECT_10F3,
      ID_CUSTOM_OBJECT_10F2, ID_CUSTOM_OBJECT_1101, ID_CUSTOM_OBJECT_1100, ID_CUSTOM_OBJECT_1102, ID_CUSTOM_OBJECT_1103,
      ID_CUSTOM_OBJECT_1106, ID_CUSTOM_OBJECT_1107, ID_CUSTOM_OBJECT_1104, ID_CUSTOM_OBJECT_1105, ID_CUSTOM_OBJECT_0A53,
      ID_CUSTOM_OBJECT_080F, ID_CUSTOM_OBJECT_096A, ID_CUSTOM_OBJECT_0A66, ID_CUSTOM_OBJECT_0A65, ID_CUSTOM_OBJECT_0A64,
      ID_CUSTOM_OBJECT_0A63, ID_CUSTOM_OBJECT_0A62, ID_CUSTOM_OBJECT_1221, ID_CUSTOM_OBJECT_096B, ID_CUSTOM_OBJECT_0969,
      ID_CUSTOM_OBJECT_1A7F, ID_CUSTOM_OBJECT_227E};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[9];
  cust_handle_list[2] = Object_handles[8];
  cust_handle_list[3] = Object_handles[4];
  cust_handle_list[4] = Object_handles[5];
  cust_handle_list[5] = Object_handles[7];
  cust_handle_list[6] = Object_handles[6];
  cust_handle_list[7] = Object_handles[11];
  cust_handle_list[8] = Object_handles[10];
  cust_handle_list[9] = Object_handles[56];
  cust_handle_list[10] = Object_handles[58];
  cust_handle_list[11] = Object_handles[60];
  cust_handle_list[12] = Object_handles[62];
  cust_handle_list[13] = Object_handles[64];
  cust_handle_list[14] = Object_handles[66];
  cust_handle_list[15] = Object_handles[68];
  cust_handle_list[16] = Object_handles[70];
  cust_handle_list[17] = Object_handles[1];
  cust_handle_list[18] = Object_handles[73];
  cust_handle_list[19] = Object_handles[75];
  cust_handle_list[20] = Object_handles[77];
  cust_handle_list[21] = Object_handles[74];
  cust_handle_list[22] = Object_handles[84];
  cust_handle_list[23] = Object_handles[85];
  cust_handle_list[24] = Object_handles[86];
  cust_handle_list[25] = Object_handles[87];
  cust_handle_list[26] = Object_handles[88];
  cust_handle_list[27] = Object_handles[89];
  cust_handle_list[28] = Object_handles[90];
  cust_handle_list[29] = Object_handles[91];
  cust_handle_list[30] = Object_handles[92];
  cust_handle_list[31] = Object_handles[93];
  cust_handle_list[32] = Object_handles[94];
  cust_handle_list[33] = Object_handles[95];
  cust_handle_list[34] = Object_handles[96];
  cust_handle_list[35] = Object_handles[97];
  cust_handle_list[36] = Object_handles[98];
  cust_handle_list[37] = Object_handles[99];
  cust_handle_list[38] = Object_handles[100];
  cust_handle_list[39] = Object_handles[101];
  cust_handle_list[40] = Object_handles[102];
  cust_handle_list[41] = Object_handles[103];
  cust_handle_list[42] = Object_handles[104];
  cust_handle_list[43] = Object_handles[105];
  cust_handle_list[44] = Object_handles[55];
  cust_handle_list[45] = Object_handles[54];
  cust_handle_list[46] = Object_handles[53];
  cust_handle_list[47] = Object_handles[106];
  cust_handle_list[48] = Object_handles[107];
  cust_handle_list[49] = Object_handles[108];
  cust_handle_list[50] = Object_handles[109];
  cust_handle_list[51] = Object_handles[110];
  cust_handle_list[52] = Object_handles[111];
  cust_handle_list[53] = Object_handles[112];
  cust_handle_list[54] = Object_handles[113];
  cust_handle_list[55] = Object_handles[114];
  cust_handle_list[56] = Object_handles[115];
  cust_handle_list[57] = Object_handles[116];
  cust_handle_list[58] = Object_handles[117];
  cust_handle_list[59] = Object_handles[118];
  cust_handle_list[60] = Object_handles[119];
  cust_handle_list[61] = Object_handles[23];
  cust_handle_list[62] = Object_handles[25];
  cust_handle_list[63] = Object_handles[24];
  cust_handle_list[64] = Object_handles[19];
  cust_handle_list[65] = Object_handles[21];
  cust_handle_list[66] = Object_handles[22];
  cust_handle_list[67] = Object_handles[20];
  cust_handle_list[68] = Object_handles[16];
  cust_handle_list[69] = Object_handles[18];
  cust_handle_list[70] = Object_handles[17];
  cust_handle_list[71] = Object_handles[15];
  cust_handle_list[72] = Object_handles[27];
  cust_handle_list[73] = Object_handles[26];
  cust_handle_list[74] = Object_handles[35];
  cust_handle_list[75] = Object_handles[36];
  cust_handle_list[76] = Object_handles[34];
  cust_handle_list[77] = Object_handles[37];
  cust_handle_list[78] = Object_handles[28];
  cust_handle_list[79] = Object_handles[29];
  cust_handle_list[80] = Object_handles[38];
  cust_handle_list[81] = Object_handles[39];
  cust_handle_list[82] = Object_handles[40];
  cust_handle_list[83] = Object_handles[42];
  cust_handle_list[84] = Object_handles[41];
  cust_handle_list[85] = Object_handles[43];
  cust_handle_list[86] = Object_handles[44];
  cust_handle_list[87] = Object_handles[30];
  cust_handle_list[88] = Object_handles[33];
  cust_handle_list[89] = Object_handles[32];
  cust_handle_list[90] = Object_handles[31];
  cust_handle_list[91] = Object_handles[46];
  cust_handle_list[92] = Object_handles[45];
  cust_handle_list[93] = Object_handles[47];
  cust_handle_list[94] = Object_handles[48];
  cust_handle_list[95] = Object_handles[51];
  cust_handle_list[96] = Object_handles[52];
  cust_handle_list[97] = Object_handles[49];
  cust_handle_list[98] = Object_handles[50];
  cust_handle_list[99] = Object_handles[124];
  cust_handle_list[100] = Object_handles[128];
  cust_handle_list[101] = Object_handles[13];
  cust_handle_list[102] = Object_handles[129];
  cust_handle_list[103] = Object_handles[130];
  cust_handle_list[104] = Object_handles[131];
  cust_handle_list[105] = Object_handles[132];
  cust_handle_list[106] = Object_handles[133];
  cust_handle_list[107] = Object_handles[134];
  cust_handle_list[108] = Object_handles[14];
  cust_handle_list[109] = Object_handles[12];
  cust_handle_list[110] = Object_handles[135];
  cust_handle_list[111] = Object_handles[136];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 112;
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

    // Script 027: All 3 Primary Controls
    if ((ScriptActionCtr_027 < 1) && (((ScriptActionCtr_056 > 0) == true) && ((ScriptActionCtr_055 > 0) == true) &&
                                      ((ScriptActionCtr_054 > 0) == true))) {
      aGoalCompleted(Goal_indexes[4], 1);
      aGoalEnableDisable(1, Goal_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 023: Initialize Level
    if (1) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[2], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[3], 1.000000f);
      aLightningTurnOn(0.100000f, 0.050000f);
      aRainTurnOn(0.700000f);
      aDoorLockUnlock(1, Door_handles[0]);
      aMusicSetRegionAll(1);
      aSetLevelTimer(25.000000f, 1);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aUserVarSet(3, 0.000000f);
      aUserVarSet(0, 0.000000f);
      aObjSetLightingDist(Object_handles[3], 35.000000f);
      aObjSetLightingDist(Object_handles[2], 35.000000f);
      aObjPlayAnim(Object_handles[3], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[2], 1, 3, 2.000000f, 1);
      aObjMakeInvuln(Object_handles[4], 999999);
      aObjMakeInvuln(Object_handles[5], 999999);
      aObjMakeInvuln(Object_handles[6], 999999);
      aObjMakeInvuln(Object_handles[7], 999999);
      aObjMakeInvuln(Object_handles[8], 999999);
      aObjMakeInvuln(Object_handles[9], 999999);
      aObjMakeInvuln(Object_handles[10], 999999);
      aObjMakeInvuln(Object_handles[11], 999999);
      aObjMakeInvuln(Object_handles[12], 999999);
      aObjMakeInvuln(Object_handles[13], 999999);
      aObjMakeInvuln(Object_handles[14], 999999);
      aAISetState(0, Object_handles[15]);
      aAISetState(0, Object_handles[16]);
      aAISetState(0, Object_handles[17]);
      aAISetState(0, Object_handles[18]);
      aAISetState(0, Object_handles[19]);
      aAISetState(0, Object_handles[20]);
      aAISetState(0, Object_handles[21]);
      aAISetState(0, Object_handles[22]);
      aAISetState(0, Object_handles[23]);
      aAISetState(0, Object_handles[24]);
      aAISetState(0, Object_handles[25]);
      aAISetState(0, Object_handles[26]);
      aAISetState(0, Object_handles[27]);
      aAISetState(0, Object_handles[28]);
      aAISetState(0, Object_handles[29]);
      aAISetState(0, Object_handles[30]);
      aAISetState(0, Object_handles[31]);
      aAISetState(0, Object_handles[32]);
      aAISetState(0, Object_handles[33]);
      aAISetState(0, Object_handles[34]);
      aAISetState(0, Object_handles[35]);
      aAISetState(0, Object_handles[36]);
      aAISetState(0, Object_handles[37]);
      aAISetState(0, Object_handles[38]);
      aAISetState(0, Object_handles[39]);
      aAISetState(0, Object_handles[40]);
      aAISetState(0, Object_handles[41]);
      aAISetState(0, Object_handles[42]);
      aAISetState(0, Object_handles[43]);
      aAISetState(0, Object_handles[44]);
      aAISetState(0, Object_handles[45]);
      aAISetState(0, Object_handles[46]);
      aAISetState(0, Object_handles[47]);
      aAISetState(0, Object_handles[48]);
      aAISetState(0, Object_handles[49]);
      aAISetState(0, Object_handles[50]);
      aAISetState(0, Object_handles[51]);
      aAISetState(0, Object_handles[52]);
      aAISetState(0, Object_handles[53]);
      aAISetState(0, Object_handles[54]);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 130: Mission Message
    if ((ScriptActionCtr_130 < 1) && (1)) {
      aSoundPlaySteaming("VoxLev11StartLevel.osf", 1.000000f);
      aObjPlayAnim(Object_handles[12], 1, 3, 2.000000f, 0);
      aObjPlayAnim(Object_handles[13], 1, 3, 2.000000f, 0);
      aObjPlayAnim(Object_handles[14], 1, 3, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0985::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 120: IntroCam
    if ((ScriptActionCtr_120 < 1) && (1 == true)) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[1], Path_indexes[1], 22.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0942::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 001: Disable HugeWH FF (2)
    if ((ScriptActionCtr_001 < 1) && (1)) {
      aPortalRenderSet(0, 0, Room_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0941::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 000: Disable HugeWH FF (1)
    if ((ScriptActionCtr_000 < 1) && (1)) {
      aPortalRenderSet(0, 0, Room_indexes[1], 1);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_092B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 049: Disable First FF
    if (1) {
      aGoalCompleted(Goal_indexes[0], 1);
      aShowHUDMessage(Message_strings[2]);
      aSetWaypoint(2);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_093E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 050: Disable Main1 FF
    if ((qObjExists(Object_handles[6]) == false) && (qObjExists(Object_handles[7]) == false)) {
      if (qDoorLocked(Door_handles[1]) == true) {
        aGoalEnableDisable(0, Goal_indexes[1]);
      }
      aGoalCompleted(Goal_indexes[2], 1);
      aSetWaypoint(3);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0940::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 051: Disable Main2 FF
    if ((qObjExists(Object_handles[6]) == false) && (qObjExists(Object_handles[5]) == false)) {
      if (qDoorLocked(Door_handles[1]) == true) {
        aGoalEnableDisable(0, Goal_indexes[1]);
      }
      aGoalCompleted(Goal_indexes[2], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aShowHUDMessage(Message_strings[3]);
      aSetWaypoint(3);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_093F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 011: Disable Main3 FF
    if ((qObjExists(Object_handles[5]) == false) && (qObjExists(Object_handles[7]) == false)) {
      if (qDoorLocked(Door_handles[1]) == true) {
        aGoalEnableDisable(0, Goal_indexes[1]);
      }
      aGoalCompleted(Goal_indexes[2], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aSetWaypoint(3);
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0954::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 053: Disable Extra1 FF
    if (1) {
      aShowHUDMessage(Message_strings[4]);
      aPortalRenderSet(0, 0, Room_indexes[4], 1);
      aPortalRenderSet(0, 1, Room_indexes[4], 1);
      aPortalRenderSet(0, 3, Room_indexes[4], 1);
      aPortalRenderSet(0, 4, Room_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3951::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 052: Disable Extra2 FF
    if (1) {
      aShowHUDMessage(Message_strings[4]);
      aPortalRenderSet(0, 2, Room_indexes[5], 1);
      aPortalRenderSet(0, 3, Room_indexes[5], 1);
      aPortalRenderSet(0, 4, Room_indexes[5], 1);
      aPortalRenderSet(0, 5, Room_indexes[5], 1);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08CF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: HWController 1
    if ((ScriptActionCtr_022 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[8], 1.000000f);
      aObjSetLightingDist(Object_handles[8], 40.000000f);
      aCreatePopupView(0, Object_handles[57], 5.000000f, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aObjPlayAnim(Object_handles[8], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[8]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08CC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: HWController 2
    if ((ScriptActionCtr_003 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjSetLightingDist(Object_handles[9], 40.000000f);
      aObjPlayAnim(Object_handles[9], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[9]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aCreatePopupView(0, Object_handles[59], 5.000000f, 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[9], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: FirstController
    if ((ScriptActionCtr_024 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[3], 1);
      aGoalEnableDisable(1, Goal_indexes[0]);
      aSoundPlayObject(Sound_indexes[0], Object_handles[4], 1.000000f);
      aObjSetLightingDist(Object_handles[4], 40.000000f);
      aObjPlayAnim(Object_handles[4], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[4]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aCreatePopupView(0, Object_handles[61], 8.000000f, 1.000000f);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0943::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Main1Controller
    if ((ScriptActionCtr_056 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[5], 1.000000f);
      aObjSetLightingDist(Object_handles[5], 40.000000f);
      aObjPlayAnim(Object_handles[5], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[5]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aCreatePopupView(0, Object_handles[63], 8.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0944::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Main2Controller
    if ((ScriptActionCtr_055 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[7], 1.000000f);
      aObjSetLightingDist(Object_handles[7], 40.000000f);
      aObjPlayAnim(Object_handles[7], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[7]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aCreatePopupView(0, Object_handles[65], 8.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08CE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Main3Controller
    if ((ScriptActionCtr_054 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[6], 1.000000f);
      aObjSetLightingDist(Object_handles[6], 40.000000f);
      aObjPlayAnim(Object_handles[6], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[6]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aCreatePopupView(0, Object_handles[67], 8.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0952::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Extra2Controller
    if ((ScriptActionCtr_058 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[10], 1.000000f);
      aObjSetLightingDist(Object_handles[10], 40.000000f);
      aObjPlayAnim(Object_handles[10], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[10]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aCreatePopupView(0, Object_handles[69], 8.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0953::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Extra1Controller
    if ((ScriptActionCtr_057 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[11], 1.000000f);
      aObjSetLightingDist(Object_handles[11], 40.000000f);
      aObjPlayAnim(Object_handles[11], 1, 3, 2.000000f, 1);
      aObjMakeVulnerable(Object_handles[11]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aCreatePopupView(0, Object_handles[71], 8.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1826::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: KeyCard
    if ((ScriptActionCtr_004 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetWaypoint(4);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[6]);
      aObjDelete(data->me_handle);
      aDoorLockUnlock(0, Door_handles[2]);
      aDoorLockUnlock(0, Door_handles[3]);
      aDoorLockUnlock(0, Door_handles[4]);
      aDoorLockUnlock(0, Door_handles[5]);
      aDoorLockUnlock(0, Door_handles[6]);
      aDoorLockUnlock(0, Door_handles[7]);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1180::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Mine Cart Start (1)
    if ((ScriptActionCtr_016 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSetObjectTimer(Object_handles[74], 9.850000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[4], Object_handles[74], 1.000000f);
      aAIGoalFollowPathSimple(Object_handles[74], Path_indexes[4], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1919::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: Mine Cart Start (2)
    if ((ScriptActionCtr_048 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSetObjectTimer(data->me_handle, 7.250000f, 4);
      aSetObjectTimer(data->me_handle, 8.120000f, 5);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[4], Object_handles[76], 1.000000f);
      aAIGoalFollowPathSimple(Object_handles[76], Path_indexes[5], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 171: Mine Cart 2 Flyer
    if (event_data->id == 4) {
      aObjSetMovementType(Object_handles[76], 1);

      // Increment the script action counter
      if (ScriptActionCtr_171 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_171++;
    }

    // Script 021: RockWallBottomExplode
    if (event_data->id == 5) {
      aGoalCompleted(Goal_indexes[5], 1);
      aObjMakeVulnerable(Object_handles[78]);
      aObjMakeVulnerable(Object_handles[79]);
      aObjMakeVulnerable(Object_handles[80]);
      aObjMakeVulnerable(Object_handles[81]);
      aObjDestroy(Object_handles[80]);
      aObjDestroy(Object_handles[79]);
      aObjDestroy(Object_handles[81]);
      aObjMakeVulnerable(Object_handles[76]);
      aObjDestroy(Object_handles[76]);
      aObjDestroy(Object_handles[78]);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0911::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 017: RockWallALL Invulnerable
    if (1) {
      aObjMakeInvuln(Object_handles[78], 999999);
      aObjMakeInvuln(Object_handles[79], 999999);
      aObjMakeInvuln(Object_handles[80], 999999);
      aObjMakeInvuln(Object_handles[81], 999999);
      aObjMakeInvuln(Object_handles[74], 999999);
      aObjMakeInvuln(Object_handles[76], 999999);
      aObjMakeInvuln(Object_handles[82], 999999);
      aObjMakeInvuln(Object_handles[77], 999999);
      aObjMakeInvuln(Object_handles[83], 999999);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_310B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 018: RockWallTopExplode(1)
    if ((ScriptActionCtr_018 < 1) && (1)) {
      aObjMakeVulnerable(Object_handles[83]);
      aObjMakeVulnerable(Object_handles[77]);
      aObjMakeVulnerable(Object_handles[82]);
      aObjDestroy(Object_handles[83]);
      aObjDestroy(Object_handles[82]);
      aObjDestroy(Object_handles[77]);
      aObjMakeVulnerable(Object_handles[74]);
      aObjDestroy(Object_handles[74]);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 002: ValvePump-1
    if ((ScriptActionCtr_002 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(100.000000f);
      aTurnOnSpew(data->me_handle, 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.600000f, 0.120000f, 20.000000f, 3.000000f,
                  15.000000f, 1, -1);
      aTurnOnSpew(data->me_handle, 1, 8, 0.000000f, 0.000000f, 65536, 0, 1.600000f, 0.120000f, 20.000000f, 3.000000f,
                  15.000000f, 1, -1);
      aObjPlayAnim(data->me_handle, 0, 2, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[5], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: ValvePump-2
    if ((ScriptActionCtr_012 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(100.000000f);
      aTurnOnSpew(data->me_handle, 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.600000f, 0.120000f, 20.000000f, 3.000000f,
                  15.000000f, 1, -1);
      aTurnOnSpew(data->me_handle, 1, 8, 0.000000f, 0.000000f, 65536, 0, 1.600000f, 0.120000f, 20.000000f, 3.000000f,
                  15.000000f, 1, -1);
      aObjPlayAnim(data->me_handle, 0, 2, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[5], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A12::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 125: GenericSpewer-18
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 047: GenericSpewer-17
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 046: GenericSpewer-16
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 045: GenericSpewer-15
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 044: GenericSpewer-14
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 043: GenericSpewer-13
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0976::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 042: GenericSpewer-12
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0977::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 041: GenericSpewer-11
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0978::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 040: GenericSpewer-10
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0979::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 039: GenericSpewer-9
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0975::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 038: GenericSpewer-8
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0974::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 037: GenericSpewer-7
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0973::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 036: GenericSpewer-6
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0972::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 035: GenericSpewer-5
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0971::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 034: GenericSpewer-4
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0970::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 015: GenericSpewer-3
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 014: GenericSpewer-2
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 013: GenericSpewer-1
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.700000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1182::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: AnotherSwitch-2
    if ((ScriptActionCtr_063 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[7]);
      aDoorLockUnlock(0, Door_handles[16]);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1181::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: AnotherSwitch-1
    if ((ScriptActionCtr_062 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[7]);
      aDoorLockUnlock(0, Door_handles[17]);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_110A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 019: Security Alert-1
    if ((ScriptActionCtr_019 < 1) &&
        ((qObjCanSeePlayer(65, data->me_handle, 240.000000f) == true) && ((ScriptActionCtr_131 > 0) == true))) {
      aAISetState(1, Object_handles[54]);
      aAISetState(1, Object_handles[53]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 131: Security-1 Timer
    if ((ScriptActionCtr_131 < 1) && (1)) {

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1109::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: SlaveGun Hit-11
    if ((ScriptActionCtr_020 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[54]);
      aAISetState(1, Object_handles[53]);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1108::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: SlaveGun Hit-12
    if ((ScriptActionCtr_064 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[54]);
      aAISetState(1, Object_handles[53]);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 078: Security Alert-F
    if ((ScriptActionCtr_078 < 1) && (qObjCanSeePlayer(50, data->me_handle, 150.000000f) == true)) {
      aAISetState(1, Object_handles[50]);
      aAISetState(1, Object_handles[49]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 077: Security Alert-E
    if ((ScriptActionCtr_077 < 1) && (qObjCanSeePlayer(50, data->me_handle, 150.000000f) == true)) {
      aAISetState(1, Object_handles[51]);
      aAISetState(1, Object_handles[52]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 076: Security Alert-D
    if ((ScriptActionCtr_076 < 1) && (qObjCanSeePlayer(50, data->me_handle, 150.000000f) == true)) {
      aAISetState(1, Object_handles[48]);
      aAISetState(1, Object_handles[47]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 075: Security Alert-C
    if ((ScriptActionCtr_075 < 1) && (qObjCanSeePlayer(65, data->me_handle, 150.000000f) == true)) {
      aAISetState(1, Object_handles[45]);
      aAISetState(1, Object_handles[46]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 074: Security Alert-B
    if ((ScriptActionCtr_074 < 1) && (qObjCanSeePlayer(90, data->me_handle, 200.000000f) == true)) {
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aAISetState(1, Object_handles[33]);
      aAISetState(1, Object_handles[30]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 073: Security Alert-A
    if ((ScriptActionCtr_073 < 1) && (qObjCanSeePlayer(30, data->me_handle, 60.000000f) == true)) {
      aAISetState(1, Object_handles[44]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 072: Security Alert-9
    if ((ScriptActionCtr_072 < 1) && (qObjCanSeePlayer(50, data->me_handle, 300.000000f) == true)) {
      aAISetState(1, Object_handles[43]);
      aAISetState(1, Object_handles[41]);
      aAISetState(1, Object_handles[42]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 071: Security Alert-8
    if ((ScriptActionCtr_071 < 1) && (qObjCanSeePlayer(50, data->me_handle, 300.000000f) == true)) {
      aAISetState(1, Object_handles[38]);
      aAISetState(1, Object_handles[40]);
      aAISetState(1, Object_handles[39]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_116C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 070: Security Alert-7
    if ((ScriptActionCtr_070 < 1) && (qObjCanSeePlayer(90, data->me_handle, 70.000000f) == true)) {
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[28]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 069: Security Alert-6
    if ((ScriptActionCtr_069 < 1) && (qObjCanSeePlayer(55, data->me_handle, 200.000000f) == true)) {
      aAISetState(1, Object_handles[37]);
      aAISetState(1, Object_handles[34]);
      aAISetState(1, Object_handles[36]);
      aAISetState(1, Object_handles[35]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 068: Security Alert-5
    if ((ScriptActionCtr_068 < 1) && (qObjCanSeePlayer(90, data->me_handle, 80.000000f) == true)) {
      aAISetState(1, Object_handles[26]);
      aAISetState(1, Object_handles[27]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18D4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 067: Security Alert-4
    if ((ScriptActionCtr_067 < 1) && (qObjCanSeePlayer(70, data->me_handle, 250.000000f) == true)) {
      aAISetState(1, Object_handles[15]);
      aAISetState(1, Object_handles[17]);
      aAISetState(1, Object_handles[18]);
      aAISetState(1, Object_handles[16]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18CD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 066: Security Alert-3
    if ((ScriptActionCtr_066 < 1) && (qObjCanSeePlayer(70, data->me_handle, 250.000000f) == true)) {
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[22]);
      aAISetState(1, Object_handles[20]);
      aAISetState(1, Object_handles[19]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18D3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 065: Security Alert-2
    if ((ScriptActionCtr_065 < 1) && (qObjCanSeePlayer(50, data->me_handle, 220.000000f) == true)) {
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[24]);
      aShowHUDMessage(Message_strings[8]);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10EA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: SlaveGun Hit-21
    if ((ScriptActionCtr_079 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[24]);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18EC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: SlaveGun Hit-22
    if ((ScriptActionCtr_081 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[24]);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10EB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: SlaveGun Hit-23
    if ((ScriptActionCtr_080 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[24]);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18E6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: SlaveGun Hit-34
    if ((ScriptActionCtr_082 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[19]);
      aAISetState(1, Object_handles[20]);
      aAISetState(1, Object_handles[22]);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: SlaveGun Hit-31
    if ((ScriptActionCtr_085 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[19]);
      aAISetState(1, Object_handles[20]);
      aAISetState(1, Object_handles[22]);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 084: SlaveGun Hit-32
    if ((ScriptActionCtr_084 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[19]);
      aAISetState(1, Object_handles[20]);
      aAISetState(1, Object_handles[22]);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: SlaveGun Hit-33
    if ((ScriptActionCtr_083 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[19]);
      aAISetState(1, Object_handles[20]);
      aAISetState(1, Object_handles[22]);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 089: SlaveGun Hit-44
    if ((ScriptActionCtr_089 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[15]);
      aAISetState(1, Object_handles[16]);
      aAISetState(1, Object_handles[17]);
      aAISetState(1, Object_handles[18]);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 088: SlaveGun Hit-43
    if ((ScriptActionCtr_088 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[15]);
      aAISetState(1, Object_handles[16]);
      aAISetState(1, Object_handles[17]);
      aAISetState(1, Object_handles[18]);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 087: SlaveGun Hit-42
    if ((ScriptActionCtr_087 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[15]);
      aAISetState(1, Object_handles[16]);
      aAISetState(1, Object_handles[17]);
      aAISetState(1, Object_handles[18]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18E2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 086: SlaveGun Hit-41
    if ((ScriptActionCtr_086 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[15]);
      aAISetState(1, Object_handles[16]);
      aAISetState(1, Object_handles[17]);
      aAISetState(1, Object_handles[18]);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10EE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 091: SlaveGun Hit-52
    if ((ScriptActionCtr_091 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[26]);
      aAISetState(1, Object_handles[27]);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18ED::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 090: SlaveGun Hit-51
    if ((ScriptActionCtr_090 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[26]);
      aAISetState(1, Object_handles[27]);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 095: SlaveGun Hit-64
    if ((ScriptActionCtr_095 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[37]);
      aAISetState(1, Object_handles[34]);
      aAISetState(1, Object_handles[36]);
      aAISetState(1, Object_handles[35]);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 094: SlaveGun Hit-63
    if ((ScriptActionCtr_094 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[37]);
      aAISetState(1, Object_handles[34]);
      aAISetState(1, Object_handles[36]);
      aAISetState(1, Object_handles[35]);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 093: SlaveGun Hit-62
    if ((ScriptActionCtr_093 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[37]);
      aAISetState(1, Object_handles[34]);
      aAISetState(1, Object_handles[36]);
      aAISetState(1, Object_handles[35]);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 092: SlaveGun Hit-61
    if ((ScriptActionCtr_092 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[37]);
      aAISetState(1, Object_handles[34]);
      aAISetState(1, Object_handles[36]);
      aAISetState(1, Object_handles[35]);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18EF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 097: SlaveGun Hit-72
    if ((ScriptActionCtr_097 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[28]);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18F0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 096: SlaveGun Hit-71
    if ((ScriptActionCtr_096 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[28]);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 098: SlaveGun Hit-81
    if ((ScriptActionCtr_098 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[38]);
      aAISetState(1, Object_handles[39]);
      aAISetState(1, Object_handles[40]);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 100: SlaveGun Hit-83
    if ((ScriptActionCtr_100 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[38]);
      aAISetState(1, Object_handles[39]);
      aAISetState(1, Object_handles[40]);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 099: SlaveGun Hit-82
    if ((ScriptActionCtr_099 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[38]);
      aAISetState(1, Object_handles[39]);
      aAISetState(1, Object_handles[40]);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 103: SlaveGun Hit-93
    if ((ScriptActionCtr_103 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[43]);
      aAISetState(1, Object_handles[41]);
      aAISetState(1, Object_handles[42]);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 102: SlaveGun Hit-92
    if ((ScriptActionCtr_102 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[43]);
      aAISetState(1, Object_handles[41]);
      aAISetState(1, Object_handles[42]);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 101: SlaveGun Hit-91
    if ((ScriptActionCtr_101 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[43]);
      aAISetState(1, Object_handles[41]);
      aAISetState(1, Object_handles[42]);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 104: SlaveGun Hit-A1
    if ((ScriptActionCtr_104 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[44]);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20F1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 108: SlaveGun Hit-B4
    if ((ScriptActionCtr_108 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aAISetState(1, Object_handles[33]);
      aAISetState(1, Object_handles[30]);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 107: SlaveGun Hit-B3
    if ((ScriptActionCtr_107 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aAISetState(1, Object_handles[33]);
      aAISetState(1, Object_handles[30]);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 106: SlaveGun Hit-B2
    if ((ScriptActionCtr_106 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aAISetState(1, Object_handles[33]);
      aAISetState(1, Object_handles[30]);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 105: SlaveGun Hit-B1
    if ((ScriptActionCtr_105 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aAISetState(1, Object_handles[33]);
      aAISetState(1, Object_handles[30]);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1101::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 110: SlaveGun Hit-C2
    if ((ScriptActionCtr_110 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[45]);
      aAISetState(1, Object_handles[46]);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1100::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 109: SlaveGun Hit-C1
    if ((ScriptActionCtr_109 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[45]);
      aAISetState(1, Object_handles[46]);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1102::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 112: SlaveGun Hit-D2
    if ((ScriptActionCtr_112 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[48]);
      aAISetState(1, Object_handles[47]);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1103::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 111: SlaveGun Hit-D1
    if ((ScriptActionCtr_111 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[48]);
      aAISetState(1, Object_handles[47]);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1106::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 114: SlaveGun Hit-E2
    if ((ScriptActionCtr_114 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[51]);
      aAISetState(1, Object_handles[52]);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1107::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 113: SlaveGun Hit-E1
    if ((ScriptActionCtr_113 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[51]);
      aAISetState(1, Object_handles[52]);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1104::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 116: SlaveGun Hit-F2
    if ((ScriptActionCtr_116 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[50]);
      aAISetState(1, Object_handles[49]);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1105::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 115: SlaveGun Hit-F1
    if ((ScriptActionCtr_115 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[50]);
      aAISetState(1, Object_handles[49]);

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A53::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 127: PrisonSwitch Activate
    if ((ScriptActionCtr_127 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[7], 1);
      aTurnOffSpew(0);
      aTurnOffSpew(1);
      aTurnOffSpew(2);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[0]);
      aSoundPlaySteaming("VoxLev11SpecificB.osf", 1.000000f);
      aAIGoalFollowPath(Object_handles[72], Path_indexes[3], 1, 23, 1, 3, 4352, -1);
      aShowHUDMessage(Message_strings[10]);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 126: PrisonSwitch Create
    if (1) {
      aTurnOnSpew(Object_handles[125], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.070000f, -1.000000f,
                  3.000000f, 25.000000f, 0, 0);
      aTurnOnSpew(Object_handles[126], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.070000f, -1.000000f,
                  3.000000f, 25.000000f, 0, 1);
      aTurnOnSpew(Object_handles[127], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.070000f, -1.000000f,
                  3.000000f, 25.000000f, 0, 2);
      aSetObjectTimer(data->me_handle, 4.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 136: Exit Abort Timer
    if (1) {
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_136 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_136++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 133: RescueMusic
    if (1) {
      aMusicSetRegionAll(8);

      // Increment the script action counter
      if (ScriptActionCtr_133 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_133++;
    }

    // Script 169: PPipeDestroyed 3
    if (1) {
      aShowHUDMessage(Message_strings[2]);
      aPortalRenderSet(0, 0, Room_indexes[6], 1);

      // Increment the script action counter
      if (ScriptActionCtr_169 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_169++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A66::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 160: PSwitch6 Hit
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(6) == 0.000000f)) {
      aShowHUDMessage(Message_strings[13]);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[14], 0.000000f, -1);
      aSetObjectTimer(data->me_handle, 20.000000f, 2);
      aUserVarInc(7);
      aUserVarSet(6, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_160 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_160++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 165: PSwitch6 Timer
    if (qUserVarValue(7) < 6.000000f) {
      if (event_data->id == 2) {
        aSetObjectTimer(data->me_handle, 2.000000f, 3);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 3, 6, 2.000000f, 0);
        aUserVarDec(7);
      } else {
        aUserVarSet(6, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_165 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_165++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A65::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 159: PSwitch5 Hit
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(5) == 0.000000f)) {
      aShowHUDMessage(Message_strings[13]);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[14], 0.000000f, -1);
      aSetObjectTimer(data->me_handle, 20.000000f, 2);
      aUserVarInc(7);
      aUserVarSet(5, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_159 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_159++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 164: PSwitch5 Timer
    if (qUserVarValue(7) < 6.000000f) {
      if (event_data->id == 2) {
        aSetObjectTimer(data->me_handle, 2.000000f, 3);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 3, 6, 2.000000f, 0);
        aUserVarDec(7);
      } else {
        aUserVarSet(5, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_164 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_164++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A64::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 158: PSwitch4 Hit
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(4) == 0.000000f)) {
      aShowHUDMessage(Message_strings[13]);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[14], 0.000000f, -1);
      aSetObjectTimer(data->me_handle, 20.000000f, 2);
      aUserVarInc(7);
      aUserVarSet(4, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_158 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_158++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 163: PSwitch4 Timer
    if (qUserVarValue(7) < 6.000000f) {
      if (event_data->id == 2) {
        aSetObjectTimer(data->me_handle, 2.000000f, 3);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 3, 6, 2.000000f, 0);
        aUserVarDec(7);
      } else {
        aUserVarSet(4, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_163 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_163++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A63::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 157: PSwitch3 Hit
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(3) == 0.000000f)) {
      aShowHUDMessage(Message_strings[13]);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[14], 0.000000f, -1);
      aSetObjectTimer(data->me_handle, 20.000000f, 2);
      aUserVarInc(7);
      aUserVarSet(3, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_157 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_157++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 162: PSwitch3 Timer
    if (qUserVarValue(7) < 6.000000f) {
      if (event_data->id == 2) {
        aSetObjectTimer(data->me_handle, 2.000000f, 3);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 3, 6, 2.000000f, 0);
        aUserVarDec(7);
      } else {
        aUserVarSet(3, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_162 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_162++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A62::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: PSwitch2 Hit
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(2) == 0.000000f)) {
      aShowHUDMessage(Message_strings[13]);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[14], 0.000000f, -1);
      aSetObjectTimer(data->me_handle, 20.000000f, 2);
      aUserVarInc(7);
      aUserVarSet(2, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 161: PSwitch2 Timer
    if (qUserVarValue(7) < 6.000000f) {
      if (event_data->id == 2) {
        aSetObjectTimer(data->me_handle, 2.000000f, 3);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 3, 6, 2.000000f, 0);
        aUserVarDec(7);
      } else {
        aUserVarSet(2, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_161 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_161++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1221::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: PSwitch1 Hit
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(1) == 0.000000f)) {
      aShowHUDMessage(Message_strings[13]);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[14], 0.000000f, -1);
      aSetObjectTimer(data->me_handle, 20.000000f, 2);
      aUserVarInc(7);
      aUserVarSet(1, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 060: PSwitch1 Timer
    if (qUserVarValue(7) < 6.000000f) {
      if (event_data->id == 2) {
        aSetObjectTimer(data->me_handle, 2.000000f, 3);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 3, 6, 2.000000f, 0);
        aUserVarDec(7);
      } else {
        aUserVarSet(1, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 167: PPipeDestroyed 1
    if (1) {
      aShowHUDMessage(Message_strings[2]);
      aPortalRenderSet(0, 0, Room_indexes[8], 1);

      // Increment the script action counter
      if (ScriptActionCtr_167 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_167++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 166: You got all 6!
    if (qUserVarValue(7) == 6.000000f) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[12], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[13], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[14], 1.000000f);
      aShowHUDMessage(Message_strings[14]);
      aObjPlayAnim(Object_handles[14], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[13], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[12], 1, 3, 2.000000f, 1);
      aObjSetLightingDist(Object_handles[14], 35.000000f);
      aObjSetLightingDist(Object_handles[12], 35.000000f);
      aObjSetLightingDist(Object_handles[13], 35.000000f);
      aObjMakeVulnerable(Object_handles[14]);
      aObjMakeVulnerable(Object_handles[12]);
      aObjMakeVulnerable(Object_handles[13]);

      // Increment the script action counter
      if (ScriptActionCtr_166 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_166++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0969::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 168: PPipeDestroyed 2
    if (1) {
      aShowHUDMessage(Message_strings[2]);
      aPortalRenderSet(0, 0, Room_indexes[7], 1);

      // Increment the script action counter
      if (ScriptActionCtr_168 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_168++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1A7F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: SEFFS-2
    if ((ScriptActionCtr_026 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aPortalRenderSet(0, 0, Room_indexes[9], 1);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[2]);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_227E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: SEFFS-1
    if ((ScriptActionCtr_025 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aPortalRenderSet(0, 1, Room_indexes[9], 1);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[2]);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 124: WayPoint-Last2
    if (1) {
      aSetWaypoint(5);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 123: WayPoint-Last1
    if (1) {
      aSetWaypoint(5);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 122: WayPoint-1
    if ((ScriptActionCtr_122 < 1) && (1)) {
      aCinematicSimple(Path_indexes[2], Message_strings[1], Object_handles[55], 10.000000f, 1);
      aSetObjectTimer(Object_handles[55], 14.000000f, -1);
      aSetWaypoint(1);

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

    // Script 005: Cross (LR) Doors-1
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorLockUnlock(0, Door_handles[8]);
      aDoorActivate(Door_handles[8]);
      aDoorSetPos(Door_handles[9], 0.000000f);
      aDoorLockUnlock(1, Door_handles[9]);
      aAIGoalFollowPath(Object_handles[72], Path_indexes[3], 23, 24, 23, 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Cross (LR) Doors-2
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorLockUnlock(0, Door_handles[10]);
      aDoorActivate(Door_handles[10]);
      aDoorSetPos(Door_handles[11], 0.000000f);
      aDoorLockUnlock(1, Door_handles[11]);
      aAIGoalFollowPath(Object_handles[72], Path_indexes[3], 24, 25, 24, 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Cross (LR) Doors-3
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorLockUnlock(0, Door_handles[12]);
      aDoorActivate(Door_handles[12]);
      aDoorSetPos(Door_handles[13], 0.000000f);
      aDoorLockUnlock(1, Door_handles[13]);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 119: CaptureMe!
    if ((ScriptActionCtr_119 < 1) && (1)) {
      aGoalCompleted(Goal_indexes[6], 1);
      aSoundPlaySteaming("VoxLev11EndLevel.osf", 1.000000f);
      aTurnOnSpew(Object_handles[120], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.070000f, 30.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[121], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.070000f, 30.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[122], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.070000f, 30.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[123], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.070000f, 30.000000f,
                  3.000000f, 25.000000f, 0, -1);
      aStartEndlevelSequencePath(Path_indexes[6], Path_indexes[7], 8.000000f, Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Cross (RL) Doors-1
    if (0.000000f == 0.000000f) {
      aDoorLockUnlock(0, Door_handles[11]);
      aDoorActivate(Door_handles[11]);
      aDoorSetPos(Door_handles[14], 0.000000f);
      aDoorLockUnlock(1, Door_handles[14]);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Cross (RL) Doors-2
    if (1) {
      aDoorLockUnlock(0, Door_handles[13]);
      aDoorActivate(Door_handles[13]);
      aDoorSetPos(Door_handles[8], 0.000000f);
      aDoorLockUnlock(1, Door_handles[8]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Cross (RL) Doors-3
    if (1) {
      aDoorLockUnlock(0, Door_handles[15]);
      aDoorActivate(Door_handles[15]);
      aDoorSetPos(Door_handles[10], 0.000000f);
      aDoorLockUnlock(1, Door_handles[10]);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 128: GoLeft
    if ((ScriptActionCtr_128 < 1) && (event_data->it_handle == Object_handles[72])) {
      aDoorLockUnlock(0, Door_handles[14]);
      aDoorLockUnlock(0, Door_handles[9]);
      aSoundPlaySteaming("VoxLev11SpecificC.osf", 1.000000f);
      aShowHUDMessage(Message_strings[11]);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0024::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 156: PipeDemo 2
    if ((ScriptActionCtr_156 < 1) &&
        ((qObjExists(Object_handles[3]) == true) && ((ScriptActionCtr_132 > 0) == false))) {
      aCinematicSimple(Path_indexes[8], Message_strings[12], Object_handles[3], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_156 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_156++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 132: PipeDemo 1
    if ((ScriptActionCtr_132 < 1) &&
        ((qObjExists(Object_handles[3]) == true) && ((ScriptActionCtr_156 > 0) == false))) {
      aCinematicSimple(Path_indexes[8], Message_strings[12], Object_handles[3], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_132 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_132++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 129: EscapeDoor-Bar
    if ((ScriptActionCtr_129 < 1) && ((ScriptActionCtr_127 > 0) == true)) {
      aDoorSetPos(Door_handles[0], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 153: EscapeDoor-2
    if ((ScriptActionCtr_153 < 1) && ((ScriptActionCtr_127 > 0) == true)) {
      aDoorSetPos(Door_handles[14], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_153 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_153++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 118: EscapeDoor-1
    if ((ScriptActionCtr_118 < 1) && ((ScriptActionCtr_127 > 0) == true)) {
      aDoorSetPos(Door_handles[18], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 134: Music-Cave
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_134 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_134++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 140: Music-Terrain
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_140 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_140++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 149: Music-MineCar2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_149 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_149++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 139: Music-MineCar1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_139 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_139++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 150: Music-Main5
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_150 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_150++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 145: Music-Main4
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_145 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_145++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 138: Music-Main3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_138 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_138++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 137: Music-Main2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_137 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_137++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 135: Music-Main1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_135 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_135++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 141: Music-Second1
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_141 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_141++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 148: Music-PreShip2
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_148 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_148++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 147: Music-PreShip1
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_147 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_147++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 144: Music-Key4
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_144 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_144++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 143: Music-Key3
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_143 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_143++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 142: Music-Key2
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_142 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_142++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 146: Music-Key1
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_146 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_146++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 152: Music-Dungeon2
    if (1) {
      aMusicSetRegion(9, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_152 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_152++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 151: Music-Dungeon1
    if (1) {
      aMusicSetRegion(9, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_151 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_151++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 155: PlayerCheat-2
    if (1) {
      aDoorSetPos(Door_handles[14], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_155 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_155++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0023::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 154: PlayerCheat-1
    if (1) {
      aDoorSetPos(Door_handles[14], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_154 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_154++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0026::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 170: Prison Cinema
    if ((ScriptActionCtr_170 < 1) && (1)) {
      aCinematicSimple(Path_indexes[9], Message_strings[15], Object_handles[13], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_170 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_170++;
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
NEXT_ID		181

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:NumSwitches
1:Prison1
2:Prison2
3:Prison3
4:Prison4
5:Prison5
6:Prison6
7:TotalPrison
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:Spark1
1:Spark2
2:Spark3
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:PrisonRoamer
1:MissionMessage
2:PSwitchON
3:PSwitchOFF
4:MC2Flyer
5:MC2Explode
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:Patrol2
1:Patrol1
2:Patrol3
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
ExitDoor-1
VertShaft
LockedDoor-3
LockedDoor-4
LockedDoor-1
LockedDoor-2
SecondaryDoor-1
SecondaryDoor-2
EX-Right-2
EX-Left-1
EX-Right-3
EX-Left-2
EX-Right-4
EX-Left-3
EX-Right-1
EX-Left-4
AnotherDoor-2
AnotherDoor-1
EscapeDoor-1
$$DOOR_LIST_END

$$OBJECT_LIST_START
EndLevelCam
KeyCard
BackSmallPipe-2
BackSmallPipe-1
FirstFFPipe
MainFFPipe-1
MainFFPipe-3
MainFFPipe-2
HWFFPipe-1
HWFFPipe-2
FFPipeExtra-2
FFPipeExtra-1
SmallPipePrison-2
PrisonSmallPipe-3
SmallPipePrison-1
SlaveGun-41
SlaveGun-44
SlaveGun-42
SlaveGun-43
SlaveGun-34
SlaveGun-33
SlaveGun-31
SlaveGun-32
SlaveGun-21
SlaveGun-23
SlaveGun-22
SlaveGun-51
SlaveGun-52
SlaveGun-72
SlaveGun-71
SlaveGun-B4
SlaveGun-B1
SlaveGun-B2
SlaveGun-B3
SlaveGun-62
SlaveGun-64
SlaveGun-63
SlaveGun-61
SlaveGun-81
SlaveGun-83
SlaveGun-82
SlaveGun-92
SlaveGun-93
SlaveGun-91
SlaveGun-A1
SlaveGun-C1
SlaveGun-C2
SlaveGun-D2
SlaveGun-D1
SlaveGun-F2
SlaveGun-F1
SlaveGun-E2
SlaveGun-E1
SlaveGun-12
SlaveGun-11
Camera-1
FFControlHW-1
HW-1
FFControlHW-2
HW-2
FFControlFirst
FirstPopUp
FFControlMain-1
Main-1
FFControlMain-2
Main-2
FFControlMain-3
Main-3
FFControlExtra-2
Extra-2
FFControlExtra-1
Extra-1
PrisonShip
MineSwitch-1
MineCart-1
MineSwitch-2
MineCart-2
RockWallTop-1
RockWallBottom-1
RockWallBottom-2
RockWallBottom-3
RockWallBottom-4
RockWallTop-6
RockWallTop-2
WindowPump-1
WindowPump-2
GenericSpew-18
GSpew17
GSpew16
GSpew15
GSpew14
GSpew13
GSpew12
GSpew11
GSpew10
GSpew9
GSpew8
GSpew7
GSpew6
GSpew5
GSpew4
GSpew3
GSpew2
GSpew1
AnotherSwitch-2
AnotherSwitch-1
Camera-F
Camera-E
Camera-D
Camera-C
Camera-B
Camera-A
Camera-9
Camera-8
Camera-7
Camera-6
Camera-5
Camera-4
Camera-3
Camera-2
Sparker-1
Sparker-2
Sparker-3
Sparker-4
PrisonFreeSwitch
PSpark-1
PSpark-2
PSpark-3
ExitDoor-1
PSwitch6
PSwitch5
PSwitch4
PSwitch3
PFSwitch2
PFSwitch1
SEFFSwitch-2
SEFFSwitch-1
$$OBJECT_LIST_END

$$ROOM_LIST_START
HugeWHouse-2
HugeWHouse-1
FirstFFRoom
MainFFRoom
Extra-1
Extra-2
Prisoner-3
Prisoner-2
Prisoner-1
SecretElevator
$$ROOM_LIST_END

$$TRIGGER_LIST_START
NearingTop-2
NearingTop-1
EnteredMine
X-Left-1
X-Left-2
X-Left-3
X-Right-1
X-Right-2
X-Right-3
AboutToLeave
PipeDemoBackup
PipeDemo
EscapeDoor-Bar
EscapeDoor-2
EscapeDoor-1
Music-Cave
Music-Terrain
Music-MineCar2
Music-MineCar1
Music-Main5
Music-Main4
Music-Main3
Music-Main2
Music-Main1
Music-Second1
Music-PreShip2
Music-PreShip1
Music-Key4
Music-Key3
Music-Key2
Music-Key1
Music-Dungeon2
Music-Dungeon1
PlayerCheat-3
PlayerCheat-1
PrisonCinema
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbEnergyPumpB
AmbSwitch41
Powerup pickup
AmbSwitch31
AmbMineCar
AmbFurn21
Siren
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
CameraShow
EscapeRoute-1
MineCart-1
MineCart-2
CapturedCam
Captured
PipeDemo
PrisonCinema
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Destroy secondary forcefield generator
Shoot switches to avoid forcefield
Destroy primary forcefield generators
Disable secondary forcefield controls
Disable primary forcefield controls
Get past the blocked entrance
Rescue the Prisoner
Release the prisoner
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxLev11StartLevel.osf
VoxLev11EndLevel.osf
VoxLev11SpecificB.osf
VoxLev11SpecificC.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:120:IntroCam
        $$CHILD_BLOCK_START
        01:1:0
        02:2
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
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:Work:Text
                        10:1:0:1:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:22.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Initialize Level
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:2:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:3:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Seconds
                        10:9:0.050000:Probability
                        $$CHILD_BLOCK_END
                08:aRainTurnOn
                        $$CHILD_BLOCK_START
                        10:9:0.700000:Density
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:25.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:35.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:35.000000:Distance
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
                        10:1:0:2:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
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
                        10:1:0:6:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:44:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:45:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:46:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:Mission Message
        $$CHILD_BLOCK_START
        01:2:0
        02:28
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:124:WayPoint-Last2
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
                        10:4:5:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:WayPoint-Last1
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
                        10:4:5:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:WayPoint-1
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:FirstCamera:Text
                        10:1:0:55:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:6:14.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Disable HugeWH FF (2)
        $$CHILD_BLOCK_START
        01:1:9
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Disable HugeWH FF (1)
        $$CHILD_BLOCK_START
        01:1:8
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Disable First FF
        $$CHILD_BLOCK_START
        01:1:4
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:2:Number
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Disable Main1 FF
        $$CHILD_BLOCK_START
        01:1:5
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:7:Object
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
                                06:qDoorLocked:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:0:1:Door
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:18:0:1:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:3:Number
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainDestroyed:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Disable Main2 FF
        $$CHILD_BLOCK_START
        01:1:7
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:5:Object
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
                                06:qDoorLocked:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:0:1:Door
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:18:0:1:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:3:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Disable Main3 FF
        $$CHILD_BLOCK_START
        01:1:6
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:5:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:7:Object
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
                                06:qDoorLocked:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:0:1:Door
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:18:0:1:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:3:Number
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainDestroyed:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Disable Extra1 FF
        $$CHILD_BLOCK_START
        01:1:11
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldsDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Disable Extra2 FF
        $$CHILD_BLOCK_START
        01:1:10
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldsDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:5:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:HWController 1
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
                        10:12:0:Sound
                        10:1:0:8:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:57:Object
                        10:6:5.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:HWController 2
        $$CHILD_BLOCK_START
        01:1:58
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
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:59:Object
                        10:6:5.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:9:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:FirstController
        $$CHILD_BLOCK_START
        01:1:60
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
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:0:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:4:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:61:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Main1Controller
        $$CHILD_BLOCK_START
        01:1:62
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
                        10:12:0:Sound
                        10:1:0:5:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:63:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Main2Controller
        $$CHILD_BLOCK_START
        01:1:64
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
                        10:12:0:Sound
                        10:1:0:7:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:65:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Main3Controller
        $$CHILD_BLOCK_START
        01:1:66
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
                        10:12:0:Sound
                        10:1:0:6:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:67:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:All 3 Primary Controls
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
                                        10:11:56:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:55:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:54:ScriptID
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
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Extra2Controller
        $$CHILD_BLOCK_START
        01:1:68
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
                        10:12:0:Sound
                        10:1:0:10:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:69:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Extra1Controller
        $$CHILD_BLOCK_START
        01:1:70
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
                        10:12:0:Sound
                        10:1:0:11:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldFirst:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:71:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:KeyCard
        $$CHILD_BLOCK_START
        01:1:1
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
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PickupKey:Message
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:5:DoorName
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Cross (LR) Doors-1
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
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:8:Door
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:9:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:9:DoorName
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:16:3:Path
                        10:4:23:FirstNode
                        10:4:24:LastNode
                        10:4:23:StartNode
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Cross (LR) Doors-2
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
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:10:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:10:Door
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:11:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:11:DoorName
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:16:3:Path
                        10:4:24:FirstNode
                        10:4:25:LastNode
                        10:4:24:StartNode
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Cross (LR) Doors-3
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
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:12:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:12:Door
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:13:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:13:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Cross (RL) Doors-1
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Literal
                        07:1:0
                        10:6:0.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:11:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:11:Door
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:14:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:14:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Cross (RL) Doors-2
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:13:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:13:Door
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:8:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Cross (RL) Doors-3
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:15:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:15:Door
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:10:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:10:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Mine Cart Start (1)
        $$CHILD_BLOCK_START
        01:1:73
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
                        10:1:0:74:Object
                        10:6:9.850000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:74:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:16:4:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Mine Cart Start (2)
        $$CHILD_BLOCK_START
        01:1:75
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
                        10:1:2:-1:Object
                        10:6:7.250000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.120000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:76:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:16:5:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:RockWallALL Invulnerable
        $$CHILD_BLOCK_START
        01:1:77
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:RockWallTopExplode(1)
        $$CHILD_BLOCK_START
        01:1:74
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:171:Mine Cart 2 Flyer
        $$CHILD_BLOCK_START
        01:1:75
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:RockWallBottomExplode
        $$CHILD_BLOCK_START
        01:1:75
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:ValvePump-1
        $$CHILD_BLOCK_START
        01:1:84
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
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.600000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.600000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
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
                        10:12:5:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:ValvePump-2
        $$CHILD_BLOCK_START
        01:1:85
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
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.600000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.600000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
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
                        10:12:5:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:GenericSpewer-18
        $$CHILD_BLOCK_START
        01:1:86
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:GenericSpewer-17
        $$CHILD_BLOCK_START
        01:1:87
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:GenericSpewer-16
        $$CHILD_BLOCK_START
        01:1:88
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:GenericSpewer-15
        $$CHILD_BLOCK_START
        01:1:89
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:GenericSpewer-14
        $$CHILD_BLOCK_START
        01:1:90
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:GenericSpewer-13
        $$CHILD_BLOCK_START
        01:1:91
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:GenericSpewer-12
        $$CHILD_BLOCK_START
        01:1:92
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:GenericSpewer-11
        $$CHILD_BLOCK_START
        01:1:93
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:GenericSpewer-10
        $$CHILD_BLOCK_START
        01:1:94
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:GenericSpewer-9
        $$CHILD_BLOCK_START
        01:1:95
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:GenericSpewer-8
        $$CHILD_BLOCK_START
        01:1:96
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:GenericSpewer-7
        $$CHILD_BLOCK_START
        01:1:97
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:GenericSpewer-6
        $$CHILD_BLOCK_START
        01:1:98
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:GenericSpewer-5
        $$CHILD_BLOCK_START
        01:1:99
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:GenericSpewer-4
        $$CHILD_BLOCK_START
        01:1:100
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:GenericSpewer-3
        $$CHILD_BLOCK_START
        01:1:101
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:GenericSpewer-2
        $$CHILD_BLOCK_START
        01:1:102
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:GenericSpewer-1
        $$CHILD_BLOCK_START
        01:1:103
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
                        10:6:1.700000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:AnotherSwitch-2
        $$CHILD_BLOCK_START
        01:1:104
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
                        10:8:DoorUnlocked:Message
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:16:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
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
00:62:AnotherSwitch-1
        $$CHILD_BLOCK_START
        01:1:105
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
                        10:8:DoorUnlocked:Message
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:17:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
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
00:131:Security-1 Timer
        $$CHILD_BLOCK_START
        01:1:55
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Security Alert-1
        $$CHILD_BLOCK_START
        01:1:55
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:65:Cone
                                        10:1:2:-1:Object
                                        10:6:240.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:131:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:SlaveGun Hit-11
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:SlaveGun Hit-12
        $$CHILD_BLOCK_START
        01:1:53
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Security Alert-F
        $$CHILD_BLOCK_START
        01:1:106
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:50:Cone
                                10:1:2:-1:Object
                                10:6:150.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Security Alert-E
        $$CHILD_BLOCK_START
        01:1:107
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:50:Cone
                                10:1:2:-1:Object
                                10:6:150.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Security Alert-D
        $$CHILD_BLOCK_START
        01:1:108
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:50:Cone
                                10:1:2:-1:Object
                                10:6:150.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:Security Alert-C
        $$CHILD_BLOCK_START
        01:1:109
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:65:Cone
                                10:1:2:-1:Object
                                10:6:150.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:45:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:46:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Security Alert-B
        $$CHILD_BLOCK_START
        01:1:110
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:90:Cone
                                10:1:2:-1:Object
                                10:6:200.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Security Alert-A
        $$CHILD_BLOCK_START
        01:1:111
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:30:Cone
                                10:1:2:-1:Object
                                10:6:60.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:44:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:Security Alert-9
        $$CHILD_BLOCK_START
        01:1:112
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:50:Cone
                                10:1:2:-1:Object
                                10:6:300.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Security Alert-8
        $$CHILD_BLOCK_START
        01:1:113
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:50:Cone
                                10:1:2:-1:Object
                                10:6:300.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Security Alert-7
        $$CHILD_BLOCK_START
        01:1:114
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:90:Cone
                                10:1:2:-1:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Security Alert-6
        $$CHILD_BLOCK_START
        01:1:115
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:55:Cone
                                10:1:2:-1:Object
                                10:6:200.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Security Alert-5
        $$CHILD_BLOCK_START
        01:1:116
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:90:Cone
                                10:1:2:-1:Object
                                10:6:80.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Security Alert-4
        $$CHILD_BLOCK_START
        01:1:117
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:70:Cone
                                10:1:2:-1:Object
                                10:6:250.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Security Alert-3
        $$CHILD_BLOCK_START
        01:1:118
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:70:Cone
                                10:1:2:-1:Object
                                10:6:250.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Security Alert-2
        $$CHILD_BLOCK_START
        01:1:119
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjCanSeePlayer:Bool
                                $$CHILD_BLOCK_START
                                10:4:50:Cone
                                10:1:2:-1:Object
                                10:6:220.000000:Distance
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Spotted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:SlaveGun Hit-21
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:SlaveGun Hit-22
        $$CHILD_BLOCK_START
        01:1:25
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:SlaveGun Hit-23
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:SlaveGun Hit-34
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:SlaveGun Hit-31
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:SlaveGun Hit-32
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:SlaveGun Hit-33
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:SlaveGun Hit-44
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:SlaveGun Hit-43
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:SlaveGun Hit-42
        $$CHILD_BLOCK_START
        01:1:17
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:SlaveGun Hit-41
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:SlaveGun Hit-52
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:SlaveGun Hit-51
        $$CHILD_BLOCK_START
        01:1:26
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:SlaveGun Hit-64
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:SlaveGun Hit-63
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:SlaveGun Hit-62
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:SlaveGun Hit-61
        $$CHILD_BLOCK_START
        01:1:37
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:SlaveGun Hit-72
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:SlaveGun Hit-71
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:SlaveGun Hit-81
        $$CHILD_BLOCK_START
        01:1:38
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:SlaveGun Hit-83
        $$CHILD_BLOCK_START
        01:1:39
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:SlaveGun Hit-82
        $$CHILD_BLOCK_START
        01:1:40
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:SlaveGun Hit-93
        $$CHILD_BLOCK_START
        01:1:42
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:SlaveGun Hit-92
        $$CHILD_BLOCK_START
        01:1:41
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:SlaveGun Hit-91
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:SlaveGun Hit-A1
        $$CHILD_BLOCK_START
        01:1:44
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:44:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:SlaveGun Hit-B4
        $$CHILD_BLOCK_START
        01:1:30
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:SlaveGun Hit-B3
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:SlaveGun Hit-B2
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:SlaveGun Hit-B1
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:SlaveGun Hit-C2
        $$CHILD_BLOCK_START
        01:1:46
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:45:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:46:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:SlaveGun Hit-C1
        $$CHILD_BLOCK_START
        01:1:45
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:45:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:46:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:SlaveGun Hit-D2
        $$CHILD_BLOCK_START
        01:1:47
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:SlaveGun Hit-D1
        $$CHILD_BLOCK_START
        01:1:48
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:SlaveGun Hit-E2
        $$CHILD_BLOCK_START
        01:1:51
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:SlaveGun Hit-E1
        $$CHILD_BLOCK_START
        01:1:52
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:SlaveGun Hit-F2
        $$CHILD_BLOCK_START
        01:1:49
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:SlaveGun Hit-F1
        $$CHILD_BLOCK_START
        01:1:50
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:CaptureMe!
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:120:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:121:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:123:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:16:7:PlayerPath
                        10:6:8.000000:Time
                        10:8:GotHim:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:PrisonSwitch Create
        $$CHILD_BLOCK_START
        01:1:124
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:125:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:126:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:127:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.070000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:PrisonSwitch Activate
        $$CHILD_BLOCK_START
        01:1:124
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
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
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
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:16:3:Path
                        10:4:1:FirstNode
                        10:4:23:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FreeAtLast:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:GoLeft
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        07:1:0
                        10:1:0:72:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:14:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:9:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoUpLeft:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:156:PipeDemo 2
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:132:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:8:CameraPath
                        10:8:PipeDemo:Text
                        10:1:0:3:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:132:PipeDemo 1
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:156:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:8:CameraPath
                        10:8:PipeDemo:Text
                        10:1:0:3:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:EscapeDoor-Bar
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:127:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:153:EscapeDoor-2
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:127:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:14:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:EscapeDoor-1
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:127:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:18:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:136:Exit Abort Timer
        $$CHILD_BLOCK_START
        01:1:128
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:133:RescueMusic
        $$CHILD_BLOCK_START
        01:1:13
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:8:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:134:Music-Cave
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
00:140:Music-Terrain
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:149:Music-MineCar2
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
00:139:Music-MineCar1
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
00:150:Music-Main5
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
00:145:Music-Main4
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
00:138:Music-Main3
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
00:137:Music-Main2
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
00:135:Music-Main1
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
00:141:Music-Second1
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:148:Music-PreShip2
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:147:Music-PreShip1
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:144:Music-Key4
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:143:Music-Key3
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:142:Music-Key2
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:146:Music-Key1
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:152:Music-Dungeon2
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
                        10:10:0:9:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:151:Music-Dungeon1
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
                        10:10:0:9:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:155:PlayerCheat-2
        $$CHILD_BLOCK_START
        01:0:33
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:14:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:154:PlayerCheat-1
        $$CHILD_BLOCK_START
        01:0:34
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:14:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:160:PSwitch6 Hit
        $$CHILD_BLOCK_START
        01:1:129
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
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
                        10:8:Reroute:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:159:PSwitch5 Hit
        $$CHILD_BLOCK_START
        01:1:130
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
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
                        10:8:Reroute:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:158:PSwitch4 Hit
        $$CHILD_BLOCK_START
        01:1:131
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reroute:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:157:PSwitch3 Hit
        $$CHILD_BLOCK_START
        01:1:132
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
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
                        10:8:Reroute:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:PSwitch2 Hit
        $$CHILD_BLOCK_START
        01:1:133
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
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
                        10:8:Reroute:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:PSwitch1 Hit
        $$CHILD_BLOCK_START
        01:1:134
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
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
                        10:8:Reroute:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:165:PSwitch6 Timer
        $$CHILD_BLOCK_START
        01:1:129
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:6.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarDec
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:164:PSwitch5 Timer
        $$CHILD_BLOCK_START
        01:1:130
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:6.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarDec
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:163:PSwitch4 Timer
        $$CHILD_BLOCK_START
        01:1:131
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:6.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarDec
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:162:PSwitch3 Timer
        $$CHILD_BLOCK_START
        01:1:132
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:6.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarDec
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
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
00:161:PSwitch2 Timer
        $$CHILD_BLOCK_START
        01:1:133
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:6.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarDec
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
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
00:60:PSwitch1 Timer
        $$CHILD_BLOCK_START
        01:1:134
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:6.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarDec
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
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
00:166:You got all 6!
        $$CHILD_BLOCK_START
        01:1:14
        02:9
        03:0
                $$CHILD_BLOCK_START
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:12:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:13:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:14:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:All6Deactive:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:35.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:35.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:35.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:169:PPipeDestroyed 3
        $$CHILD_BLOCK_START
        01:1:13
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
                        10:4:0:PortalNum
                        10:2:6:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:168:PPipeDestroyed 2
        $$CHILD_BLOCK_START
        01:1:12
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
                        10:4:0:PortalNum
                        10:2:7:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:167:PPipeDestroyed 1
        $$CHILD_BLOCK_START
        01:1:14
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
                        10:4:0:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:170:Prison Cinema
        $$CHILD_BLOCK_START
        01:0:35
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:9:CameraPath
                        10:8:DestroyThese:Text
                        10:1:0:13:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:SEFFS-2
        $$CHILD_BLOCK_START
        01:1:135
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
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
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:SEFFS-1
        $$CHILD_BLOCK_START
        01:1:136
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
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
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
