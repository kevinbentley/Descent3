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
// Filename:	levels2.cpp
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

#define ID_CUSTOM_OBJECT_0821 0x001
#define ID_CUSTOM_OBJECT_0820 0x002
#define ID_CUSTOM_OBJECT_181E 0x003
#define ID_CUSTOM_OBJECT_081F 0x004
#define ID_CUSTOM_OBJECT_0814 0x005
#define ID_CUSTOM_OBJECT_0815 0x006
#define ID_CUSTOM_OBJECT_0816 0x007
#define ID_CUSTOM_OBJECT_0818 0x008
#define ID_CUSTOM_OBJECT_0819 0x009
#define ID_CUSTOM_OBJECT_0817 0x00a
#define ID_CUSTOM_OBJECT_1024 0x00b
#define ID_CUSTOM_OBJECT_0826 0x00c
#define ID_CUSTOM_OBJECT_0828 0x00d
#define ID_CUSTOM_OBJECT_0827 0x00e
#define ID_CUSTOM_OBJECT_086A 0x00f
#define ID_CUSTOM_OBJECT_086B 0x010
#define ID_CUSTOM_OBJECT_0829 0x011
#define ID_CUSTOM_OBJECT_08C4 0x012
#define ID_CUSTOM_OBJECT_10CE 0x013
#define ID_CUSTOM_OBJECT_0809 0x014
#define ID_CUSTOM_OBJECT_0808 0x015
#define ID_CUSTOM_OBJECT_1007 0x016
#define ID_CUSTOM_OBJECT_1006 0x017
#define ID_CUSTOM_OBJECT_0805 0x018
#define ID_CUSTOM_OBJECT_1004 0x019
#define ID_CUSTOM_OBJECT_1003 0x01a
#define ID_CUSTOM_OBJECT_100E 0x01b
#define ID_CUSTOM_OBJECT_0845 0x01c
#define ID_CUSTOM_OBJECT_0844 0x01d
#define ID_CUSTOM_OBJECT_0843 0x01e
#define ID_CUSTOM_OBJECT_0842 0x01f
#define ID_CUSTOM_OBJECT_0841 0x020
#define ID_CUSTOM_OBJECT_0840 0x021
#define ID_CUSTOM_OBJECT_083F 0x022
#define ID_CUSTOM_OBJECT_083E 0x023
#define ID_CUSTOM_OBJECT_083D 0x024
#define ID_CUSTOM_OBJECT_083C 0x025
#define ID_CUSTOM_OBJECT_083B 0x026
#define ID_CUSTOM_OBJECT_083A 0x027
#define ID_CUSTOM_OBJECT_0851 0x028
#define ID_CUSTOM_OBJECT_0850 0x029
#define ID_CUSTOM_OBJECT_084F 0x02a
#define ID_CUSTOM_OBJECT_084E 0x02b
#define ID_CUSTOM_OBJECT_084D 0x02c
#define ID_CUSTOM_OBJECT_084C 0x02d
#define ID_CUSTOM_OBJECT_084B 0x02e
#define ID_CUSTOM_OBJECT_084A 0x02f
#define ID_CUSTOM_OBJECT_0849 0x030
#define ID_CUSTOM_OBJECT_0848 0x031
#define ID_CUSTOM_OBJECT_0847 0x032
#define ID_CUSTOM_OBJECT_0846 0x033
#define ID_CUSTOM_OBJECT_085D 0x034
#define ID_CUSTOM_OBJECT_085C 0x035
#define ID_CUSTOM_OBJECT_085B 0x036
#define ID_CUSTOM_OBJECT_085A 0x037
#define ID_CUSTOM_OBJECT_0859 0x038
#define ID_CUSTOM_OBJECT_0858 0x039
#define ID_CUSTOM_OBJECT_0857 0x03a
#define ID_CUSTOM_OBJECT_0856 0x03b
#define ID_CUSTOM_OBJECT_0855 0x03c
#define ID_CUSTOM_OBJECT_0854 0x03d
#define ID_CUSTOM_OBJECT_0853 0x03e
#define ID_CUSTOM_OBJECT_0852 0x03f
#define ID_CUSTOM_OBJECT_0869 0x040
#define ID_CUSTOM_OBJECT_0868 0x041
#define ID_CUSTOM_OBJECT_0867 0x042
#define ID_CUSTOM_OBJECT_0866 0x043
#define ID_CUSTOM_OBJECT_0865 0x044
#define ID_CUSTOM_OBJECT_0864 0x045
#define ID_CUSTOM_OBJECT_0863 0x046
#define ID_CUSTOM_OBJECT_0862 0x047
#define ID_CUSTOM_OBJECT_0861 0x048
#define ID_CUSTOM_OBJECT_0860 0x049
#define ID_CUSTOM_OBJECT_085F 0x04a
#define ID_CUSTOM_OBJECT_085E 0x04b

#define ID_TRIGGER_003B 0x04c
#define ID_TRIGGER_003A 0x04d
#define ID_TRIGGER_0035 0x04e
#define ID_TRIGGER_0034 0x04f
#define ID_TRIGGER_0031 0x050
#define ID_TRIGGER_002F 0x051
#define ID_TRIGGER_002E 0x052
#define ID_TRIGGER_0023 0x053
#define ID_TRIGGER_0022 0x054
#define ID_TRIGGER_0021 0x055
#define ID_TRIGGER_0020 0x056
#define ID_TRIGGER_001B 0x057
#define ID_TRIGGER_001A 0x058
#define ID_TRIGGER_0017 0x059
#define ID_TRIGGER_0016 0x05a
#define ID_TRIGGER_0015 0x05b
#define ID_TRIGGER_0014 0x05c
#define ID_TRIGGER_0013 0x05d
#define ID_TRIGGER_0012 0x05e
#define ID_TRIGGER_0011 0x05f
#define ID_TRIGGER_0010 0x060
#define ID_TRIGGER_000B 0x061
#define ID_TRIGGER_000A 0x062
#define ID_TRIGGER_0009 0x063
#define ID_TRIGGER_0008 0x064
#define ID_TRIGGER_0005 0x065
#define ID_TRIGGER_0004 0x066
#define ID_TRIGGER_0001 0x067
#define ID_TRIGGER_0000 0x068
#define ID_TRIGGER_003D 0x069
#define ID_TRIGGER_003C 0x06a
#define ID_TRIGGER_0039 0x06b
#define ID_TRIGGER_0038 0x06c
#define ID_TRIGGER_0037 0x06d
#define ID_TRIGGER_0036 0x06e
#define ID_TRIGGER_0033 0x06f
#define ID_TRIGGER_0032 0x070
#define ID_TRIGGER_0030 0x071
#define ID_TRIGGER_002C 0x072
#define ID_TRIGGER_0027 0x073
#define ID_TRIGGER_0026 0x074
#define ID_TRIGGER_0025 0x075
#define ID_TRIGGER_0024 0x076
#define ID_TRIGGER_001F 0x077
#define ID_TRIGGER_001E 0x078
#define ID_TRIGGER_001D 0x079
#define ID_TRIGGER_001C 0x07a
#define ID_TRIGGER_0019 0x07b
#define ID_TRIGGER_0018 0x07c
#define ID_TRIGGER_000F 0x07d
#define ID_TRIGGER_000E 0x07e
#define ID_TRIGGER_000D 0x07f
#define ID_TRIGGER_000C 0x080
#define ID_TRIGGER_0007 0x081
#define ID_TRIGGER_0006 0x082
#define ID_TRIGGER_0003 0x083
#define ID_TRIGGER_0002 0x084
#define ID_TRIGGER_0040 0x085

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

class CustomObjectScript_0821 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0820 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_181E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0814 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0815 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0816 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0818 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0819 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0817 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1024 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0826 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0828 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0827 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_086A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_086B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0829 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08C4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10CE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0809 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0808 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0805 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_100E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0845 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0844 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0843 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0842 : public BaseScript {
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

class CustomObjectScript_083F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083A : public BaseScript {
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

class CustomObjectScript_084F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084E : public BaseScript {
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

class CustomObjectScript_084A : public BaseScript {
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

class CustomObjectScript_0846 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0859 : public BaseScript {
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

class CustomObjectScript_0854 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0853 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0852 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0869 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0868 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0867 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0866 : public BaseScript {
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

class CustomObjectScript_0861 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0860 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_003B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_003A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0035 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0034 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0031 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0023 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0022 : public BaseScript {
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

class TriggerScript_0016 : public BaseScript {
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

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
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

class TriggerScript_0001 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_003D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_003C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0039 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0038 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0037 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0036 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0033 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0032 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0030 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0027 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0026 : public BaseScript {
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

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
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

class TriggerScript_000F : public BaseScript {
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

class TriggerScript_0007 : public BaseScript {
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

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0040 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_016 = 0;
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
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_048 = 0;
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
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_125 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_139 = 0;
static int ScriptActionCtr_138 = 0;
static int ScriptActionCtr_137 = 0;
static int ScriptActionCtr_136 = 0;
static int ScriptActionCtr_135 = 0;
static int ScriptActionCtr_134 = 0;
static int ScriptActionCtr_133 = 0;
static int ScriptActionCtr_132 = 0;
static int ScriptActionCtr_131 = 0;
static int ScriptActionCtr_130 = 0;
static int ScriptActionCtr_129 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_140 = 0;
static int ScriptActionCtr_141 = 0;
static int ScriptActionCtr_142 = 0;
static int ScriptActionCtr_143 = 0;
static int ScriptActionCtr_144 = 0;
static int ScriptActionCtr_145 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_016 = 0;
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
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_048 = 0;
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
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_125 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_139 = 0;
  ScriptActionCtr_138 = 0;
  ScriptActionCtr_137 = 0;
  ScriptActionCtr_136 = 0;
  ScriptActionCtr_135 = 0;
  ScriptActionCtr_134 = 0;
  ScriptActionCtr_133 = 0;
  ScriptActionCtr_132 = 0;
  ScriptActionCtr_131 = 0;
  ScriptActionCtr_130 = 0;
  ScriptActionCtr_129 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_140 = 0;
  ScriptActionCtr_141 = 0;
  ScriptActionCtr_142 = 0;
  ScriptActionCtr_143 = 0;
  ScriptActionCtr_144 = 0;
  ScriptActionCtr_145 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
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
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
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
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_139, file_ptr);
  File_WriteInt(ScriptActionCtr_138, file_ptr);
  File_WriteInt(ScriptActionCtr_137, file_ptr);
  File_WriteInt(ScriptActionCtr_136, file_ptr);
  File_WriteInt(ScriptActionCtr_135, file_ptr);
  File_WriteInt(ScriptActionCtr_134, file_ptr);
  File_WriteInt(ScriptActionCtr_133, file_ptr);
  File_WriteInt(ScriptActionCtr_132, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
  File_WriteInt(ScriptActionCtr_130, file_ptr);
  File_WriteInt(ScriptActionCtr_129, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_140, file_ptr);
  File_WriteInt(ScriptActionCtr_141, file_ptr);
  File_WriteInt(ScriptActionCtr_142, file_ptr);
  File_WriteInt(ScriptActionCtr_143, file_ptr);
  File_WriteInt(ScriptActionCtr_144, file_ptr);
  File_WriteInt(ScriptActionCtr_145, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_139 = File_ReadInt(file_ptr);
  ScriptActionCtr_138 = File_ReadInt(file_ptr);
  ScriptActionCtr_137 = File_ReadInt(file_ptr);
  ScriptActionCtr_136 = File_ReadInt(file_ptr);
  ScriptActionCtr_135 = File_ReadInt(file_ptr);
  ScriptActionCtr_134 = File_ReadInt(file_ptr);
  ScriptActionCtr_133 = File_ReadInt(file_ptr);
  ScriptActionCtr_132 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
  ScriptActionCtr_130 = File_ReadInt(file_ptr);
  ScriptActionCtr_129 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_140 = File_ReadInt(file_ptr);
  ScriptActionCtr_141 = File_ReadInt(file_ptr);
  ScriptActionCtr_142 = File_ReadInt(file_ptr);
  ScriptActionCtr_143 = File_ReadInt(file_ptr);
  ScriptActionCtr_144 = File_ReadInt(file_ptr);
  ScriptActionCtr_145 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Blue Key
2:Red Key
3:Reactor
4:Escape
5:Main
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

#define NUM_DOOR_NAMES 0
static const char **Door_names = NULL;
static int *Door_handles = NULL;

#define NUM_OBJECT_NAMES 104
static const char *const Object_names[NUM_OBJECT_NAMES] = {"RedFlame-2",
                                                           "RedFlame-1",
                                                           "BlueFlame-2",
                                                           "BlueFlame-1",
                                                           "RedSwitch-2",
                                                           "RedSwitch-1",
                                                           "BlueSwitch-2",
                                                           "BlueSwitch-1",
                                                           "MiniReactorBlue-2",
                                                           "MiniReactorBlue-1",
                                                           "WarningLightBlue",
                                                           "ACB-12",
                                                           "ACB-11",
                                                           "ACB-10",
                                                           "ACB-9",
                                                           "ACB-8",
                                                           "ACB-7",
                                                           "ACB-6",
                                                           "ACB-5",
                                                           "ACB-4",
                                                           "ACB-3",
                                                           "ACB-2",
                                                           "ACB-1",
                                                           "MiniReactorWhite-2",
                                                           "MiniReactorWhite-1",
                                                           "WarningLightWhite",
                                                           "ACW-12",
                                                           "ACW-11",
                                                           "ACW-10",
                                                           "ACW-9",
                                                           "ACW-8",
                                                           "ACW-7",
                                                           "ACW-6",
                                                           "ACW-5",
                                                           "ACW-4",
                                                           "ACW-3",
                                                           "ACW-2",
                                                           "ACW-1",
                                                           "RedKey",
                                                           "BlueKey",
                                                           "MiniReactorRed-2",
                                                           "MiniReactorRed-1",
                                                           "ReactorSmoke",
                                                           "MiniLightRed-2",
                                                           "MiniLightRed-1",
                                                           "ACS-12",
                                                           "ACS-11",
                                                           "ACS-10",
                                                           "ACS-9",
                                                           "ACS-8",
                                                           "ACS-7",
                                                           "ACS-6",
                                                           "ACS-5",
                                                           "ACS-4",
                                                           "ACS-3",
                                                           "ACS-2",
                                                           "ACS-1",
                                                           "ACR-12",
                                                           "ACR-11",
                                                           "ACR-10",
                                                           "ACR-9",
                                                           "ACR-8",
                                                           "ACR-7",
                                                           "ACR-6",
                                                           "ACR-5",
                                                           "ACR-4",
                                                           "ACR-3",
                                                           "ACR-2",
                                                           "ACR-1",
                                                           "RNode-1",
                                                           "Reactor",
                                                           "RNode-2",
                                                           "RNode-3",
                                                           "RNode-4",
                                                           "BaseThing",
                                                           "Flames-11",
                                                           "Flames-15",
                                                           "Flames-45",
                                                           "Flames-35",
                                                           "Flames-25",
                                                           "Flames-14",
                                                           "Flames-44",
                                                           "Flames-34",
                                                           "Flames-24",
                                                           "Flames-13",
                                                           "Flames-23",
                                                           "Flames-33",
                                                           "Flames-43",
                                                           "Flames-12",
                                                           "Flames-42",
                                                           "Flames-32",
                                                           "Flames-22",
                                                           "Flames-41",
                                                           "Flames-31",
                                                           "Flames-21",
                                                           "RedDoor-2",
                                                           "RedDoor-1",
                                                           "BlueDoor",
                                                           "FOV",
                                                           "RNode-5",
                                                           "RNode-6",
                                                           "RNode-7",
                                                           "RNode-8",
                                                           "Reflector"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 82
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "MainStop",     "OutStop-4",   "OutStop-3",   "OutStop-2",   "OutStop-1",   "SpeederStop-2", "SpeederStop-1",
    "Standard-8",   "Standard-7",  "Standard-6",  "Standard-5",  "Standard-4",  "Standard-3",    "Standard-2",
    "Standard-1",   "InnerDown-8", "InnerDown-7", "InnerDown-6", "InnerDown-5", "InnerDown-4",   "InnerDown-3",
    "InnerDown-2",  "InnerDown-1", "InnerUp-2",   "InnerUp-1",   "AccessUp-1",  "AccessUp-2",    "AccessDown-1",
    "AccessDown-2", "Escape-2",    "Escape-1",    "Out-12",      "Out-11",      "Out-10",        "Out-9",
    "Out-8",        "Out-7",       "Out-6",       "Out-5",       "Out-4",       "Out-3",         "Out-2",
    "Out-1",        "Speeder-23",  "Speeder-22",  "Speeder-21",  "Speeder-13",  "Speeder-12",    "Speed-11",
    "MainTube-4",   "MainTube-3",  "MainTube-2",  "MainTube-1",  "UpMain-2",    "UpMain-1",      "RedFlame-1",
    "RedFlame-2",   "BlueFlame-1", "BlueFlame-2", "RedKeyRoom",  "BlueKeyRoom", "Reactor",       "Flames-15",
    "Flames-25",    "Flames-35",   "Flames-45",   "Flames-12",   "Flames-22",   "Flames-32",     "Flames-42",
    "Flames-14",    "Flames-24",   "Flames-34",   "Flames-44",   "Flames-11",   "Flames-21",     "Flames-31",
    "Flames-41",    "Flames-13",   "Flames-23",   "Flames-33",   "Flames-43"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 58
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "StartMini-4",     "StartMini-3",     "StartMini-2",     "StartMini-1",     "StartMain-1",     "StartMain-2",
    "StartEscape-1",   "StartSpeed-2",    "StartSpeed-1",    "StartInUp-2",     "StartInUp-1",     "StartOffMain-2",
    "StartOffMain-1",  "StartIn-4",       "StartIn-3",       "StartIn-2",       "StartIn-1",       "StartOut-4",
    "StartOut-3",      "StartOut-2",      "StartOut-1",      "StartStandard-8", "StartStandard-7", "StartStandard-6",
    "StartStandard-5", "StartStandard-4", "StartStandard-3", "StartStandard-2", "StartStandard-1", "StopSpeed-2",
    "StopSpeed-1",     "StopMini-2",      "StopMini-1",      "StopMini-4",      "StopMini-3",      "StopOffMain-2",
    "StopOffMain-1",   "StopMain-1",      "StopMain-2",      "StopOut-4",       "StopOut-3",       "StopOut-2",
    "StopOut-1",       "StopIn-4",        "StopIn-3",        "StopIn-2",        "StopIn-1",        "StopInUp-2",
    "StopInUp-1",      "StopStandard-8",  "StopStandard-7",  "StopStandard-6",  "StopStandard-5",  "StopStandard-4",
    "StopStandard-3",  "StopStandard-2",  "StopStandard-1",  "EndLevel"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 9
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "LevSecAccelStart", "LevSecAccelRelease", "AmbSwitch11",      "PupC1", "AmbSirenBRedAcrop", "wallofire1",
    "HitEnergy",        "Lightning",          "Forcefield bounce"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 1
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffect5"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 2
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCam", "IntroShip"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 8
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Destroy Red Key Forcefield Generators",
                                                       "Destroy Blue Key Forcefield Generators",
                                                       "Acquire the Red Key",
                                                       "Acquire the Blue Key",
                                                       "Destroy Reactor Forcefield Generators",
                                                       "Destroy the Reactor",
                                                       "Escape the Research Center",
                                                       "Destroy the Research Center"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 11
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "FlameDeactivated", "RedKeyFF", "BlueKeyFF", "NameRedKey", "NameBlueKey",  "ReactorFF",
    "ReactorDestroyed", "RedDoor",  "BlueDoor",  "IntroCam",   "ReactorPrimed"};
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
    strcpy(filename, "levels2.msg");
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
  case ID_CUSTOM_OBJECT_0821:
    return new CustomObjectScript_0821;
    break;
  case ID_CUSTOM_OBJECT_0820:
    return new CustomObjectScript_0820;
    break;
  case ID_CUSTOM_OBJECT_181E:
    return new CustomObjectScript_181E;
    break;
  case ID_CUSTOM_OBJECT_081F:
    return new CustomObjectScript_081F;
    break;
  case ID_CUSTOM_OBJECT_0814:
    return new CustomObjectScript_0814;
    break;
  case ID_CUSTOM_OBJECT_0815:
    return new CustomObjectScript_0815;
    break;
  case ID_CUSTOM_OBJECT_0816:
    return new CustomObjectScript_0816;
    break;
  case ID_CUSTOM_OBJECT_0818:
    return new CustomObjectScript_0818;
    break;
  case ID_CUSTOM_OBJECT_0819:
    return new CustomObjectScript_0819;
    break;
  case ID_CUSTOM_OBJECT_0817:
    return new CustomObjectScript_0817;
    break;
  case ID_CUSTOM_OBJECT_1024:
    return new CustomObjectScript_1024;
    break;
  case ID_CUSTOM_OBJECT_0826:
    return new CustomObjectScript_0826;
    break;
  case ID_CUSTOM_OBJECT_0828:
    return new CustomObjectScript_0828;
    break;
  case ID_CUSTOM_OBJECT_0827:
    return new CustomObjectScript_0827;
    break;
  case ID_CUSTOM_OBJECT_086A:
    return new CustomObjectScript_086A;
    break;
  case ID_CUSTOM_OBJECT_086B:
    return new CustomObjectScript_086B;
    break;
  case ID_CUSTOM_OBJECT_0829:
    return new CustomObjectScript_0829;
    break;
  case ID_CUSTOM_OBJECT_08C4:
    return new CustomObjectScript_08C4;
    break;
  case ID_CUSTOM_OBJECT_10CE:
    return new CustomObjectScript_10CE;
    break;
  case ID_CUSTOM_OBJECT_0809:
    return new CustomObjectScript_0809;
    break;
  case ID_CUSTOM_OBJECT_0808:
    return new CustomObjectScript_0808;
    break;
  case ID_CUSTOM_OBJECT_1007:
    return new CustomObjectScript_1007;
    break;
  case ID_CUSTOM_OBJECT_1006:
    return new CustomObjectScript_1006;
    break;
  case ID_CUSTOM_OBJECT_0805:
    return new CustomObjectScript_0805;
    break;
  case ID_CUSTOM_OBJECT_1004:
    return new CustomObjectScript_1004;
    break;
  case ID_CUSTOM_OBJECT_1003:
    return new CustomObjectScript_1003;
    break;
  case ID_CUSTOM_OBJECT_100E:
    return new CustomObjectScript_100E;
    break;
  case ID_CUSTOM_OBJECT_0845:
    return new CustomObjectScript_0845;
    break;
  case ID_CUSTOM_OBJECT_0844:
    return new CustomObjectScript_0844;
    break;
  case ID_CUSTOM_OBJECT_0843:
    return new CustomObjectScript_0843;
    break;
  case ID_CUSTOM_OBJECT_0842:
    return new CustomObjectScript_0842;
    break;
  case ID_CUSTOM_OBJECT_0841:
    return new CustomObjectScript_0841;
    break;
  case ID_CUSTOM_OBJECT_0840:
    return new CustomObjectScript_0840;
    break;
  case ID_CUSTOM_OBJECT_083F:
    return new CustomObjectScript_083F;
    break;
  case ID_CUSTOM_OBJECT_083E:
    return new CustomObjectScript_083E;
    break;
  case ID_CUSTOM_OBJECT_083D:
    return new CustomObjectScript_083D;
    break;
  case ID_CUSTOM_OBJECT_083C:
    return new CustomObjectScript_083C;
    break;
  case ID_CUSTOM_OBJECT_083B:
    return new CustomObjectScript_083B;
    break;
  case ID_CUSTOM_OBJECT_083A:
    return new CustomObjectScript_083A;
    break;
  case ID_CUSTOM_OBJECT_0851:
    return new CustomObjectScript_0851;
    break;
  case ID_CUSTOM_OBJECT_0850:
    return new CustomObjectScript_0850;
    break;
  case ID_CUSTOM_OBJECT_084F:
    return new CustomObjectScript_084F;
    break;
  case ID_CUSTOM_OBJECT_084E:
    return new CustomObjectScript_084E;
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
  case ID_CUSTOM_OBJECT_084A:
    return new CustomObjectScript_084A;
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
  case ID_CUSTOM_OBJECT_0846:
    return new CustomObjectScript_0846;
    break;
  case ID_CUSTOM_OBJECT_085D:
    return new CustomObjectScript_085D;
    break;
  case ID_CUSTOM_OBJECT_085C:
    return new CustomObjectScript_085C;
    break;
  case ID_CUSTOM_OBJECT_085B:
    return new CustomObjectScript_085B;
    break;
  case ID_CUSTOM_OBJECT_085A:
    return new CustomObjectScript_085A;
    break;
  case ID_CUSTOM_OBJECT_0859:
    return new CustomObjectScript_0859;
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
  case ID_CUSTOM_OBJECT_0854:
    return new CustomObjectScript_0854;
    break;
  case ID_CUSTOM_OBJECT_0853:
    return new CustomObjectScript_0853;
    break;
  case ID_CUSTOM_OBJECT_0852:
    return new CustomObjectScript_0852;
    break;
  case ID_CUSTOM_OBJECT_0869:
    return new CustomObjectScript_0869;
    break;
  case ID_CUSTOM_OBJECT_0868:
    return new CustomObjectScript_0868;
    break;
  case ID_CUSTOM_OBJECT_0867:
    return new CustomObjectScript_0867;
    break;
  case ID_CUSTOM_OBJECT_0866:
    return new CustomObjectScript_0866;
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
  case ID_CUSTOM_OBJECT_0861:
    return new CustomObjectScript_0861;
    break;
  case ID_CUSTOM_OBJECT_0860:
    return new CustomObjectScript_0860;
    break;
  case ID_CUSTOM_OBJECT_085F:
    return new CustomObjectScript_085F;
    break;
  case ID_CUSTOM_OBJECT_085E:
    return new CustomObjectScript_085E;
    break;
  case ID_TRIGGER_003B:
    return new TriggerScript_003B;
    break;
  case ID_TRIGGER_003A:
    return new TriggerScript_003A;
    break;
  case ID_TRIGGER_0035:
    return new TriggerScript_0035;
    break;
  case ID_TRIGGER_0034:
    return new TriggerScript_0034;
    break;
  case ID_TRIGGER_0031:
    return new TriggerScript_0031;
    break;
  case ID_TRIGGER_002F:
    return new TriggerScript_002F;
    break;
  case ID_TRIGGER_002E:
    return new TriggerScript_002E;
    break;
  case ID_TRIGGER_0023:
    return new TriggerScript_0023;
    break;
  case ID_TRIGGER_0022:
    return new TriggerScript_0022;
    break;
  case ID_TRIGGER_0021:
    return new TriggerScript_0021;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
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
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
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
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_003D:
    return new TriggerScript_003D;
    break;
  case ID_TRIGGER_003C:
    return new TriggerScript_003C;
    break;
  case ID_TRIGGER_0039:
    return new TriggerScript_0039;
    break;
  case ID_TRIGGER_0038:
    return new TriggerScript_0038;
    break;
  case ID_TRIGGER_0037:
    return new TriggerScript_0037;
    break;
  case ID_TRIGGER_0036:
    return new TriggerScript_0036;
    break;
  case ID_TRIGGER_0033:
    return new TriggerScript_0033;
    break;
  case ID_TRIGGER_0032:
    return new TriggerScript_0032;
    break;
  case ID_TRIGGER_0030:
    return new TriggerScript_0030;
    break;
  case ID_TRIGGER_002C:
    return new TriggerScript_002C;
    break;
  case ID_TRIGGER_0027:
    return new TriggerScript_0027;
    break;
  case ID_TRIGGER_0026:
    return new TriggerScript_0026;
    break;
  case ID_TRIGGER_0025:
    return new TriggerScript_0025;
    break;
  case ID_TRIGGER_0024:
    return new TriggerScript_0024;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
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
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
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
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0040:
    return new TriggerScript_0040;
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
  case ID_CUSTOM_OBJECT_0821:
    delete ((CustomObjectScript_0821 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0820:
    delete ((CustomObjectScript_0820 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_181E:
    delete ((CustomObjectScript_181E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081F:
    delete ((CustomObjectScript_081F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0814:
    delete ((CustomObjectScript_0814 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0815:
    delete ((CustomObjectScript_0815 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0816:
    delete ((CustomObjectScript_0816 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0818:
    delete ((CustomObjectScript_0818 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0819:
    delete ((CustomObjectScript_0819 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0817:
    delete ((CustomObjectScript_0817 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1024:
    delete ((CustomObjectScript_1024 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0826:
    delete ((CustomObjectScript_0826 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0828:
    delete ((CustomObjectScript_0828 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0827:
    delete ((CustomObjectScript_0827 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_086A:
    delete ((CustomObjectScript_086A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_086B:
    delete ((CustomObjectScript_086B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0829:
    delete ((CustomObjectScript_0829 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08C4:
    delete ((CustomObjectScript_08C4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10CE:
    delete ((CustomObjectScript_10CE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0809:
    delete ((CustomObjectScript_0809 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0808:
    delete ((CustomObjectScript_0808 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1007:
    delete ((CustomObjectScript_1007 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1006:
    delete ((CustomObjectScript_1006 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0805:
    delete ((CustomObjectScript_0805 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1004:
    delete ((CustomObjectScript_1004 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1003:
    delete ((CustomObjectScript_1003 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_100E:
    delete ((CustomObjectScript_100E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0845:
    delete ((CustomObjectScript_0845 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0844:
    delete ((CustomObjectScript_0844 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0843:
    delete ((CustomObjectScript_0843 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0842:
    delete ((CustomObjectScript_0842 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0841:
    delete ((CustomObjectScript_0841 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0840:
    delete ((CustomObjectScript_0840 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083F:
    delete ((CustomObjectScript_083F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083E:
    delete ((CustomObjectScript_083E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083D:
    delete ((CustomObjectScript_083D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083C:
    delete ((CustomObjectScript_083C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083B:
    delete ((CustomObjectScript_083B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083A:
    delete ((CustomObjectScript_083A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0851:
    delete ((CustomObjectScript_0851 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0850:
    delete ((CustomObjectScript_0850 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084F:
    delete ((CustomObjectScript_084F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084E:
    delete ((CustomObjectScript_084E *)ptr);
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
  case ID_CUSTOM_OBJECT_084A:
    delete ((CustomObjectScript_084A *)ptr);
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
  case ID_CUSTOM_OBJECT_0846:
    delete ((CustomObjectScript_0846 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085D:
    delete ((CustomObjectScript_085D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085C:
    delete ((CustomObjectScript_085C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085B:
    delete ((CustomObjectScript_085B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085A:
    delete ((CustomObjectScript_085A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0859:
    delete ((CustomObjectScript_0859 *)ptr);
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
  case ID_CUSTOM_OBJECT_0854:
    delete ((CustomObjectScript_0854 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0853:
    delete ((CustomObjectScript_0853 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0852:
    delete ((CustomObjectScript_0852 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0869:
    delete ((CustomObjectScript_0869 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0868:
    delete ((CustomObjectScript_0868 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0867:
    delete ((CustomObjectScript_0867 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0866:
    delete ((CustomObjectScript_0866 *)ptr);
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
  case ID_CUSTOM_OBJECT_0861:
    delete ((CustomObjectScript_0861 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0860:
    delete ((CustomObjectScript_0860 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085F:
    delete ((CustomObjectScript_085F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085E:
    delete ((CustomObjectScript_085E *)ptr);
    break;
  case ID_TRIGGER_003B:
    delete ((TriggerScript_003B *)ptr);
    break;
  case ID_TRIGGER_003A:
    delete ((TriggerScript_003A *)ptr);
    break;
  case ID_TRIGGER_0035:
    delete ((TriggerScript_0035 *)ptr);
    break;
  case ID_TRIGGER_0034:
    delete ((TriggerScript_0034 *)ptr);
    break;
  case ID_TRIGGER_0031:
    delete ((TriggerScript_0031 *)ptr);
    break;
  case ID_TRIGGER_002F:
    delete ((TriggerScript_002F *)ptr);
    break;
  case ID_TRIGGER_002E:
    delete ((TriggerScript_002E *)ptr);
    break;
  case ID_TRIGGER_0023:
    delete ((TriggerScript_0023 *)ptr);
    break;
  case ID_TRIGGER_0022:
    delete ((TriggerScript_0022 *)ptr);
    break;
  case ID_TRIGGER_0021:
    delete ((TriggerScript_0021 *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
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
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
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
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_003D:
    delete ((TriggerScript_003D *)ptr);
    break;
  case ID_TRIGGER_003C:
    delete ((TriggerScript_003C *)ptr);
    break;
  case ID_TRIGGER_0039:
    delete ((TriggerScript_0039 *)ptr);
    break;
  case ID_TRIGGER_0038:
    delete ((TriggerScript_0038 *)ptr);
    break;
  case ID_TRIGGER_0037:
    delete ((TriggerScript_0037 *)ptr);
    break;
  case ID_TRIGGER_0036:
    delete ((TriggerScript_0036 *)ptr);
    break;
  case ID_TRIGGER_0033:
    delete ((TriggerScript_0033 *)ptr);
    break;
  case ID_TRIGGER_0032:
    delete ((TriggerScript_0032 *)ptr);
    break;
  case ID_TRIGGER_0030:
    delete ((TriggerScript_0030 *)ptr);
    break;
  case ID_TRIGGER_002C:
    delete ((TriggerScript_002C *)ptr);
    break;
  case ID_TRIGGER_0027:
    delete ((TriggerScript_0027 *)ptr);
    break;
  case ID_TRIGGER_0026:
    delete ((TriggerScript_0026 *)ptr);
    break;
  case ID_TRIGGER_0025:
    delete ((TriggerScript_0025 *)ptr);
    break;
  case ID_TRIGGER_0024:
    delete ((TriggerScript_0024 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
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
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
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
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0040:
    delete ((TriggerScript_0040 *)ptr);
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
  case ID_CUSTOM_OBJECT_0821:
  case ID_CUSTOM_OBJECT_0820:
  case ID_CUSTOM_OBJECT_181E:
  case ID_CUSTOM_OBJECT_081F:
  case ID_CUSTOM_OBJECT_0814:
  case ID_CUSTOM_OBJECT_0815:
  case ID_CUSTOM_OBJECT_0816:
  case ID_CUSTOM_OBJECT_0818:
  case ID_CUSTOM_OBJECT_0819:
  case ID_CUSTOM_OBJECT_0817:
  case ID_CUSTOM_OBJECT_1024:
  case ID_CUSTOM_OBJECT_0826:
  case ID_CUSTOM_OBJECT_0828:
  case ID_CUSTOM_OBJECT_0827:
  case ID_CUSTOM_OBJECT_086A:
  case ID_CUSTOM_OBJECT_086B:
  case ID_CUSTOM_OBJECT_0829:
  case ID_CUSTOM_OBJECT_08C4:
  case ID_CUSTOM_OBJECT_10CE:
  case ID_CUSTOM_OBJECT_0809:
  case ID_CUSTOM_OBJECT_0808:
  case ID_CUSTOM_OBJECT_1007:
  case ID_CUSTOM_OBJECT_1006:
  case ID_CUSTOM_OBJECT_0805:
  case ID_CUSTOM_OBJECT_1004:
  case ID_CUSTOM_OBJECT_1003:
  case ID_CUSTOM_OBJECT_100E:
  case ID_CUSTOM_OBJECT_0845:
  case ID_CUSTOM_OBJECT_0844:
  case ID_CUSTOM_OBJECT_0843:
  case ID_CUSTOM_OBJECT_0842:
  case ID_CUSTOM_OBJECT_0841:
  case ID_CUSTOM_OBJECT_0840:
  case ID_CUSTOM_OBJECT_083F:
  case ID_CUSTOM_OBJECT_083E:
  case ID_CUSTOM_OBJECT_083D:
  case ID_CUSTOM_OBJECT_083C:
  case ID_CUSTOM_OBJECT_083B:
  case ID_CUSTOM_OBJECT_083A:
  case ID_CUSTOM_OBJECT_0851:
  case ID_CUSTOM_OBJECT_0850:
  case ID_CUSTOM_OBJECT_084F:
  case ID_CUSTOM_OBJECT_084E:
  case ID_CUSTOM_OBJECT_084D:
  case ID_CUSTOM_OBJECT_084C:
  case ID_CUSTOM_OBJECT_084B:
  case ID_CUSTOM_OBJECT_084A:
  case ID_CUSTOM_OBJECT_0849:
  case ID_CUSTOM_OBJECT_0848:
  case ID_CUSTOM_OBJECT_0847:
  case ID_CUSTOM_OBJECT_0846:
  case ID_CUSTOM_OBJECT_085D:
  case ID_CUSTOM_OBJECT_085C:
  case ID_CUSTOM_OBJECT_085B:
  case ID_CUSTOM_OBJECT_085A:
  case ID_CUSTOM_OBJECT_0859:
  case ID_CUSTOM_OBJECT_0858:
  case ID_CUSTOM_OBJECT_0857:
  case ID_CUSTOM_OBJECT_0856:
  case ID_CUSTOM_OBJECT_0855:
  case ID_CUSTOM_OBJECT_0854:
  case ID_CUSTOM_OBJECT_0853:
  case ID_CUSTOM_OBJECT_0852:
  case ID_CUSTOM_OBJECT_0869:
  case ID_CUSTOM_OBJECT_0868:
  case ID_CUSTOM_OBJECT_0867:
  case ID_CUSTOM_OBJECT_0866:
  case ID_CUSTOM_OBJECT_0865:
  case ID_CUSTOM_OBJECT_0864:
  case ID_CUSTOM_OBJECT_0863:
  case ID_CUSTOM_OBJECT_0862:
  case ID_CUSTOM_OBJECT_0861:
  case ID_CUSTOM_OBJECT_0860:
  case ID_CUSTOM_OBJECT_085F:
  case ID_CUSTOM_OBJECT_085E:
  case ID_TRIGGER_003B:
  case ID_TRIGGER_003A:
  case ID_TRIGGER_0035:
  case ID_TRIGGER_0034:
  case ID_TRIGGER_0031:
  case ID_TRIGGER_002F:
  case ID_TRIGGER_002E:
  case ID_TRIGGER_0023:
  case ID_TRIGGER_0022:
  case ID_TRIGGER_0021:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_003D:
  case ID_TRIGGER_003C:
  case ID_TRIGGER_0039:
  case ID_TRIGGER_0038:
  case ID_TRIGGER_0037:
  case ID_TRIGGER_0036:
  case ID_TRIGGER_0033:
  case ID_TRIGGER_0032:
  case ID_TRIGGER_0030:
  case ID_TRIGGER_002C:
  case ID_TRIGGER_0027:
  case ID_TRIGGER_0026:
  case ID_TRIGGER_0025:
  case ID_TRIGGER_0024:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0040:
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
    return ID_TRIGGER_003B;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_003A;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0035;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0034;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0031;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_002F;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_002E;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0023;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0022;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0021;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[29] && trigger_face == Trigger_faces[29])
    return ID_TRIGGER_003D;

  if (trigger_room == Trigger_rooms[30] && trigger_face == Trigger_faces[30])
    return ID_TRIGGER_003C;

  if (trigger_room == Trigger_rooms[31] && trigger_face == Trigger_faces[31])
    return ID_TRIGGER_0039;

  if (trigger_room == Trigger_rooms[32] && trigger_face == Trigger_faces[32])
    return ID_TRIGGER_0038;

  if (trigger_room == Trigger_rooms[33] && trigger_face == Trigger_faces[33])
    return ID_TRIGGER_0037;

  if (trigger_room == Trigger_rooms[34] && trigger_face == Trigger_faces[34])
    return ID_TRIGGER_0036;

  if (trigger_room == Trigger_rooms[35] && trigger_face == Trigger_faces[35])
    return ID_TRIGGER_0033;

  if (trigger_room == Trigger_rooms[36] && trigger_face == Trigger_faces[36])
    return ID_TRIGGER_0032;

  if (trigger_room == Trigger_rooms[37] && trigger_face == Trigger_faces[37])
    return ID_TRIGGER_0030;

  if (trigger_room == Trigger_rooms[38] && trigger_face == Trigger_faces[38])
    return ID_TRIGGER_002C;

  if (trigger_room == Trigger_rooms[39] && trigger_face == Trigger_faces[39])
    return ID_TRIGGER_0027;

  if (trigger_room == Trigger_rooms[40] && trigger_face == Trigger_faces[40])
    return ID_TRIGGER_0026;

  if (trigger_room == Trigger_rooms[41] && trigger_face == Trigger_faces[41])
    return ID_TRIGGER_0025;

  if (trigger_room == Trigger_rooms[42] && trigger_face == Trigger_faces[42])
    return ID_TRIGGER_0024;

  if (trigger_room == Trigger_rooms[43] && trigger_face == Trigger_faces[43])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[44] && trigger_face == Trigger_faces[44])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[45] && trigger_face == Trigger_faces[45])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[46] && trigger_face == Trigger_faces[46])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[47] && trigger_face == Trigger_faces[47])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[48] && trigger_face == Trigger_faces[48])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[49] && trigger_face == Trigger_faces[49])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[50] && trigger_face == Trigger_faces[50])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[51] && trigger_face == Trigger_faces[51])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[52] && trigger_face == Trigger_faces[52])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[53] && trigger_face == Trigger_faces[53])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[54] && trigger_face == Trigger_faces[54])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[55] && trigger_face == Trigger_faces[55])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[56] && trigger_face == Trigger_faces[56])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[57] && trigger_face == Trigger_faces[57])
    return ID_TRIGGER_0040;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[75];
  static int cust_id_list[75] = {
      ID_CUSTOM_OBJECT_0821, ID_CUSTOM_OBJECT_0820, ID_CUSTOM_OBJECT_181E, ID_CUSTOM_OBJECT_081F,
      ID_CUSTOM_OBJECT_0814, ID_CUSTOM_OBJECT_0815, ID_CUSTOM_OBJECT_0816, ID_CUSTOM_OBJECT_0818,
      ID_CUSTOM_OBJECT_0819, ID_CUSTOM_OBJECT_0817, ID_CUSTOM_OBJECT_1024, ID_CUSTOM_OBJECT_0826,
      ID_CUSTOM_OBJECT_0828, ID_CUSTOM_OBJECT_0827, ID_CUSTOM_OBJECT_086A, ID_CUSTOM_OBJECT_086B,
      ID_CUSTOM_OBJECT_0829, ID_CUSTOM_OBJECT_08C4, ID_CUSTOM_OBJECT_10CE, ID_CUSTOM_OBJECT_0809,
      ID_CUSTOM_OBJECT_0808, ID_CUSTOM_OBJECT_1007, ID_CUSTOM_OBJECT_1006, ID_CUSTOM_OBJECT_0805,
      ID_CUSTOM_OBJECT_1004, ID_CUSTOM_OBJECT_1003, ID_CUSTOM_OBJECT_100E, ID_CUSTOM_OBJECT_0845,
      ID_CUSTOM_OBJECT_0844, ID_CUSTOM_OBJECT_0843, ID_CUSTOM_OBJECT_0842, ID_CUSTOM_OBJECT_0841,
      ID_CUSTOM_OBJECT_0840, ID_CUSTOM_OBJECT_083F, ID_CUSTOM_OBJECT_083E, ID_CUSTOM_OBJECT_083D,
      ID_CUSTOM_OBJECT_083C, ID_CUSTOM_OBJECT_083B, ID_CUSTOM_OBJECT_083A, ID_CUSTOM_OBJECT_0851,
      ID_CUSTOM_OBJECT_0850, ID_CUSTOM_OBJECT_084F, ID_CUSTOM_OBJECT_084E, ID_CUSTOM_OBJECT_084D,
      ID_CUSTOM_OBJECT_084C, ID_CUSTOM_OBJECT_084B, ID_CUSTOM_OBJECT_084A, ID_CUSTOM_OBJECT_0849,
      ID_CUSTOM_OBJECT_0848, ID_CUSTOM_OBJECT_0847, ID_CUSTOM_OBJECT_0846, ID_CUSTOM_OBJECT_085D,
      ID_CUSTOM_OBJECT_085C, ID_CUSTOM_OBJECT_085B, ID_CUSTOM_OBJECT_085A, ID_CUSTOM_OBJECT_0859,
      ID_CUSTOM_OBJECT_0858, ID_CUSTOM_OBJECT_0857, ID_CUSTOM_OBJECT_0856, ID_CUSTOM_OBJECT_0855,
      ID_CUSTOM_OBJECT_0854, ID_CUSTOM_OBJECT_0853, ID_CUSTOM_OBJECT_0852, ID_CUSTOM_OBJECT_0869,
      ID_CUSTOM_OBJECT_0868, ID_CUSTOM_OBJECT_0867, ID_CUSTOM_OBJECT_0866, ID_CUSTOM_OBJECT_0865,
      ID_CUSTOM_OBJECT_0864, ID_CUSTOM_OBJECT_0863, ID_CUSTOM_OBJECT_0862, ID_CUSTOM_OBJECT_0861,
      ID_CUSTOM_OBJECT_0860, ID_CUSTOM_OBJECT_085F, ID_CUSTOM_OBJECT_085E};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[4];
  cust_handle_list[1] = Object_handles[5];
  cust_handle_list[2] = Object_handles[6];
  cust_handle_list[3] = Object_handles[7];
  cust_handle_list[4] = Object_handles[8];
  cust_handle_list[5] = Object_handles[9];
  cust_handle_list[6] = Object_handles[10];
  cust_handle_list[7] = Object_handles[23];
  cust_handle_list[8] = Object_handles[24];
  cust_handle_list[9] = Object_handles[25];
  cust_handle_list[10] = Object_handles[38];
  cust_handle_list[11] = Object_handles[39];
  cust_handle_list[12] = Object_handles[40];
  cust_handle_list[13] = Object_handles[41];
  cust_handle_list[14] = Object_handles[43];
  cust_handle_list[15] = Object_handles[44];
  cust_handle_list[16] = Object_handles[42];
  cust_handle_list[17] = Object_handles[70];
  cust_handle_list[18] = Object_handles[74];
  cust_handle_list[19] = Object_handles[76];
  cust_handle_list[20] = Object_handles[80];
  cust_handle_list[21] = Object_handles[84];
  cust_handle_list[22] = Object_handles[88];
  cust_handle_list[23] = Object_handles[75];
  cust_handle_list[24] = Object_handles[95];
  cust_handle_list[25] = Object_handles[96];
  cust_handle_list[26] = Object_handles[97];
  cust_handle_list[27] = Object_handles[26];
  cust_handle_list[28] = Object_handles[27];
  cust_handle_list[29] = Object_handles[28];
  cust_handle_list[30] = Object_handles[29];
  cust_handle_list[31] = Object_handles[30];
  cust_handle_list[32] = Object_handles[31];
  cust_handle_list[33] = Object_handles[32];
  cust_handle_list[34] = Object_handles[33];
  cust_handle_list[35] = Object_handles[34];
  cust_handle_list[36] = Object_handles[35];
  cust_handle_list[37] = Object_handles[36];
  cust_handle_list[38] = Object_handles[37];
  cust_handle_list[39] = Object_handles[11];
  cust_handle_list[40] = Object_handles[12];
  cust_handle_list[41] = Object_handles[13];
  cust_handle_list[42] = Object_handles[14];
  cust_handle_list[43] = Object_handles[15];
  cust_handle_list[44] = Object_handles[16];
  cust_handle_list[45] = Object_handles[17];
  cust_handle_list[46] = Object_handles[18];
  cust_handle_list[47] = Object_handles[19];
  cust_handle_list[48] = Object_handles[20];
  cust_handle_list[49] = Object_handles[21];
  cust_handle_list[50] = Object_handles[22];
  cust_handle_list[51] = Object_handles[57];
  cust_handle_list[52] = Object_handles[58];
  cust_handle_list[53] = Object_handles[59];
  cust_handle_list[54] = Object_handles[60];
  cust_handle_list[55] = Object_handles[61];
  cust_handle_list[56] = Object_handles[62];
  cust_handle_list[57] = Object_handles[63];
  cust_handle_list[58] = Object_handles[64];
  cust_handle_list[59] = Object_handles[65];
  cust_handle_list[60] = Object_handles[66];
  cust_handle_list[61] = Object_handles[67];
  cust_handle_list[62] = Object_handles[68];
  cust_handle_list[63] = Object_handles[45];
  cust_handle_list[64] = Object_handles[46];
  cust_handle_list[65] = Object_handles[47];
  cust_handle_list[66] = Object_handles[48];
  cust_handle_list[67] = Object_handles[49];
  cust_handle_list[68] = Object_handles[50];
  cust_handle_list[69] = Object_handles[51];
  cust_handle_list[70] = Object_handles[52];
  cust_handle_list[71] = Object_handles[53];
  cust_handle_list[72] = Object_handles[54];
  cust_handle_list[73] = Object_handles[55];
  cust_handle_list[74] = Object_handles[56];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 75;
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

    // Script 000: Wind
    if (1) {
      aUserVarSet(3, -50.000000f);
      aUserVarSet(2, -120.000000f);
      aUserVarSet(1, 50.000000f);
      aUserVarSet(0, 120.000000f);
      aRoomSetWind(Room_indexes[0], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[1], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[2], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[9], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[12], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[13], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[14], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[15], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[16], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[17], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[18], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[19], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[20], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[21], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[22], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[23], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[24], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[25], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[26], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[27], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[28], 0.000000f, qUserVarValue(3), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[29], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[30], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[31], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[32], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[33], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[34], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[35], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[36], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[37], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[38], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[39], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[40], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[41], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[42], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[43], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[44], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[45], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[46], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[47], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[48], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[49], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[50], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[51], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[52], 0.000000f, qUserVarValue(2), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[53], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[54], 0.000000f, qUserVarValue(1), 0.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 058: StartSecretFlames
    if (1) {
      aRoomSetDamage(Room_indexes[55], 15.000000f, 4);
      aRoomSetDamage(Room_indexes[56], 15.000000f, 4);
      aRoomSetDamage(Room_indexes[57], 15.000000f, 4);
      aRoomSetDamage(Room_indexes[58], 15.000000f, 4);
      aTurnOnSpew(Object_handles[0], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, -1.000000f, 5.000000f,
                  60.000000f, 0, 3);
      aTurnOnSpew(Object_handles[1], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, -1.000000f, 5.000000f,
                  60.000000f, 0, 2);
      aTurnOnSpew(Object_handles[2], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, -1.000000f, 5.000000f,
                  60.000000f, 0, 1);
      aTurnOnSpew(Object_handles[3], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, -1.000000f, 5.000000f,
                  60.000000f, 0, 0);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }

    // Script 078: StartMiniReactors
    if (1) {
      aObjPlayAnim(Object_handles[40], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[41], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[23], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[24], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[8], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[9], 1, 3, 2.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }

    // Script 084: StartFlames
    if (1) {
      aSetObjectTimer(Object_handles[75], 5.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }

    // Script 140: IntroCam
    if (1 == true) {
      aCinematicIntro(Path_indexes[0], Message_strings[9], Object_handles[38], Path_indexes[1], 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_140 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_140++;
    }

    // Script 141: StartMusic
    if (1) {
      aMusicSetRegionAll(5);

      // Increment the script action counter
      if (ScriptActionCtr_141 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_141++;
    }

    // Script 145: Set visited flag
    if (1) {
      aMissionSetFlag(30, 1);

      // Increment the script action counter
      if (ScriptActionCtr_145 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_145++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 076: Reactor Blows
    if (event_data->id == 0) {
      if ((ScriptActionCtr_077 > 0) == false) {
        aGoalFailed(Goal_indexes[6], 1);
        aGoalCompleted(Goal_indexes[7], 1);
        aEndLevel();
      }

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0821::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: RedSwitch-2
    if ((ScriptActionCtr_062 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[0]);
      aTurnOffSpew(3);
      aRoomSetDamage(Room_indexes[56], 0.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0820::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: RedSwitch-1
    if ((ScriptActionCtr_061 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[0]);
      aTurnOffSpew(2);
      aRoomSetDamage(Room_indexes[55], 0.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_181E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: BlueSwitch-2
    if ((ScriptActionCtr_060 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[0]);
      aTurnOffSpew(1);
      aRoomSetDamage(Room_indexes[58], 0.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: BlueSwitch-1
    if ((ScriptActionCtr_059 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[0]);
      aTurnOffSpew(0);
      aRoomSetDamage(Room_indexes[57], 0.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0814::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 064: MiniReactorBlue-2
    if (qObjExists(Object_handles[9]) == false) {
      aSetObjectTimer(Object_handles[10], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0815::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 063: MiniReactorBlue-1
    if (qObjExists(Object_handles[8]) == false) {
      aSetObjectTimer(Object_handles[10], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0816::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 101: MiniReactorBlue TimerChain
    if ((ScriptActionCtr_101 < 1) && (1)) {
      aSetObjectTimer(Object_handles[11], 6.000000f, -1);
      aSetObjectTimer(Object_handles[12], 5.500000f, -1);
      aSetObjectTimer(Object_handles[13], 5.000000f, -1);
      aSetObjectTimer(Object_handles[14], 4.500000f, -1);
      aSetObjectTimer(Object_handles[15], 4.000000f, -1);
      aSetObjectTimer(Object_handles[16], 3.500000f, -1);
      aSetObjectTimer(Object_handles[17], 3.000000f, -1);
      aSetObjectTimer(Object_handles[18], 2.500000f, -1);
      aSetObjectTimer(Object_handles[19], 2.000000f, -1);
      aSetObjectTimer(Object_handles[20], 1.500000f, -1);
      aSetObjectTimer(Object_handles[21], 1.000000f, -1);
      aSetObjectTimer(Object_handles[22], 0.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }

    // Script 065: MiniReactorBlue Timer
    if ((ScriptActionCtr_065 < 1) && (1)) {
      aGoalCompleted(Goal_indexes[0], 1);
      aPortalRenderSet(0, 0, Room_indexes[59], 1);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0818::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 067: MiniReactorWhite-2
    if (qObjExists(Object_handles[24]) == false) {
      aSetObjectTimer(Object_handles[25], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0819::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 066: MiniReactorWhite-1
    if (qObjExists(Object_handles[23]) == false) {
      aSetObjectTimer(Object_handles[25], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0817::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 100: MiniReactorWhite TimerChain
    if ((ScriptActionCtr_100 < 1) && (1)) {
      aSetObjectTimer(Object_handles[26], 6.000000f, -1);
      aSetObjectTimer(Object_handles[27], 5.500000f, -1);
      aSetObjectTimer(Object_handles[28], 5.000000f, -1);
      aSetObjectTimer(Object_handles[29], 4.500000f, -1);
      aSetObjectTimer(Object_handles[30], 4.000000f, -1);
      aSetObjectTimer(Object_handles[31], 3.500000f, -1);
      aSetObjectTimer(Object_handles[32], 3.000000f, -1);
      aSetObjectTimer(Object_handles[33], 2.500000f, -1);
      aSetObjectTimer(Object_handles[34], 2.000000f, -1);
      aSetObjectTimer(Object_handles[35], 1.500000f, -1);
      aSetObjectTimer(Object_handles[36], 1.000000f, -1);
      aSetObjectTimer(Object_handles[37], 0.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }

    // Script 068: MiniReactorWhite Timer
    if ((ScriptActionCtr_068 < 1) && (1)) {
      aGoalCompleted(Goal_indexes[1], 1);
      aPortalRenderSet(0, 0, Room_indexes[60], 1);
      aShowHUDMessage(Message_strings[2]);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1024::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Red Key
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMusicSetRegion(2, event_data->it_handle);
      aGoalCompleted(Goal_indexes[2], 1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 2, Message_strings[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0826::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Blue Key
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMusicSetRegion(1, event_data->it_handle);
      aGoalCompleted(Goal_indexes[3], 1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 1, Message_strings[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0828::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 072: MiniReactorRed-2
    if (1) {
      if (qObjExists(Object_handles[41]) == false) {
        aSetObjectTimer(Object_handles[42], 0.000000f, -1);
      }
      aSetObjectTimer(Object_handles[43], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0827::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 071: MiniReactorRed-1
    if (1) {
      if (qObjExists(Object_handles[40]) == false) {
        aSetObjectTimer(Object_handles[42], 0.000000f, -1);
      }
      aSetObjectTimer(Object_handles[44], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_086A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 103: MiniReactorRed-2 Timer Chain
    if ((ScriptActionCtr_103 < 1) && (1)) {
      aSetObjectTimer(Object_handles[45], 6.000000f, -1);
      aSetObjectTimer(Object_handles[46], 5.500000f, -1);
      aSetObjectTimer(Object_handles[47], 5.000000f, -1);
      aSetObjectTimer(Object_handles[48], 4.500000f, -1);
      aSetObjectTimer(Object_handles[49], 4.000000f, -1);
      aSetObjectTimer(Object_handles[50], 3.500000f, -1);
      aSetObjectTimer(Object_handles[51], 3.000000f, -1);
      aSetObjectTimer(Object_handles[52], 2.500000f, -1);
      aSetObjectTimer(Object_handles[53], 2.000000f, -1);
      aSetObjectTimer(Object_handles[54], 1.500000f, -1);
      aSetObjectTimer(Object_handles[55], 1.000000f, -1);
      aSetObjectTimer(Object_handles[56], 0.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_086B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 102: MiniReactorRed-1 Timer Chain
    if ((ScriptActionCtr_102 < 1) && (1)) {
      aSetObjectTimer(Object_handles[57], 6.000000f, -1);
      aSetObjectTimer(Object_handles[58], 5.500000f, -1);
      aSetObjectTimer(Object_handles[59], 5.000000f, -1);
      aSetObjectTimer(Object_handles[60], 4.500000f, -1);
      aSetObjectTimer(Object_handles[61], 4.000000f, -1);
      aSetObjectTimer(Object_handles[62], 3.500000f, -1);
      aSetObjectTimer(Object_handles[63], 3.000000f, -1);
      aSetObjectTimer(Object_handles[64], 2.500000f, -1);
      aSetObjectTimer(Object_handles[65], 2.000000f, -1);
      aSetObjectTimer(Object_handles[66], 1.500000f, -1);
      aSetObjectTimer(Object_handles[67], 1.000000f, -1);
      aSetObjectTimer(Object_handles[68], 0.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0829::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 073: MiniReactorRed Timer
    if ((ScriptActionCtr_073 < 1) && (1)) {
      aLightningCreate(Object_handles[69], Object_handles[70], 9999.000000f, 3.000000f, 1, Texture_indexes[0],
                       0.300000f, 5, 255, 30, 20, 0);
      aLightningCreate(Object_handles[71], Object_handles[70], 9999.000000f, 3.000000f, 1, Texture_indexes[0],
                       0.300000f, 5, 255, 30, 20, 0);
      aLightningCreate(Object_handles[72], Object_handles[70], 9999.000000f, 3.000000f, 1, Texture_indexes[0],
                       0.300000f, 5, 255, 30, 20, 0);
      aLightningCreate(Object_handles[73], Object_handles[70], 9999.000000f, 3.000000f, 1, Texture_indexes[0],
                       0.300000f, 5, 255, 30, 20, 0);
      aGoalCompleted(Goal_indexes[4], 1);
      aPortalRenderSet(0, 0, Room_indexes[61], 1);
      aShowHUDMessage(Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08C4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 144: Reactor Discharge
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == true)) {
      aObjSaveHandle(qPlayerClosest(data->me_handle, -1), 0);
      aUserFlagSet(0, 0);
      if (qObjCanSeeObjAdvanced(qObjSavedHandle(0), 180, Object_handles[98], 1024) == true) {
        aObjApplyDamage(qObjSavedHandle(0), 5.000000f);
        aLightningCreate(Object_handles[99], qObjSavedHandle(0), 0.600000f, 3.000000f, 1, Texture_indexes[0],
                         -0.700000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[100], qObjSavedHandle(0), 0.600000f, 3.000000f, 1, Texture_indexes[0],
                         -0.700000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[101], qObjSavedHandle(0), 0.600000f, 3.000000f, 1, Texture_indexes[0],
                         -0.700000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[102], qObjSavedHandle(0), 0.600000f, 3.000000f, 1, Texture_indexes[0],
                         -0.700000f, 5, 255, 30, 20, 0);
        aSoundPlayObject(Sound_indexes[6], qObjSavedHandle(0), 1.000000f);
        aSoundPlayObject(Sound_indexes[7], Object_handles[98], 1.000000f);
        aObjSpark(qObjSavedHandle(0), 30.000000f, 0.800000f);
        aMiscShakeArea(Object_handles[98], 50.000000f, 300.000000f);
      } else {
        aUserVarInc(4);
        aSoundPlayObject(Sound_indexes[8], Object_handles[103], 1.000000f);
        aSoundPlayObject(Sound_indexes[7], Object_handles[98], 1.000000f);
        aObjSpark(Object_handles[70], qMathPercentage(10.000000f, qUserVarValue(4)), qUserVarValue(4));
        aMiscShakeArea(Object_handles[98], 25.000000f, 300.000000f);
        aLightningCreate(Object_handles[103], Object_handles[98], 0.600000f, 6.000000f, 1, Texture_indexes[0],
                         0.700000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[99], Object_handles[103], 0.600000f, 4.000000f, 1, Texture_indexes[0],
                         0.700000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[100], Object_handles[103], 0.600000f, 4.000000f, 1, Texture_indexes[0],
                         0.400000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[101], Object_handles[103], 0.600000f, 4.000000f, 1, Texture_indexes[0],
                         0.700000f, 5, 255, 30, 20, 0);
        aLightningCreate(Object_handles[102], Object_handles[103], 0.600000f, 4.000000f, 1, Texture_indexes[0],
                         0.700000f, 5, 255, 30, 20, 0);
      }
      aSetObjectTimer(data->me_handle, 1.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_144 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_144++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 142: ReactorInit
    if (1) {
      aObjMakeInvuln(data->me_handle, 99999);
      aUserFlagSet(0, 1);
      aUserVarSet(4, 1.000000f);
      aAISetState(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_142 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_142++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 074: Reactor Destroyed
    if ((ScriptActionCtr_074 < 1) && (1)) {
      aMusicSetRegionAll(4);
      aGoalCompleted(Goal_indexes[5], 1);
      aSoundPlay2D(Sound_indexes[4], 1.000000f);
      aShowHUDMessage(Message_strings[6]);
      aPortalRenderSet(0, 0, Room_indexes[30], 1);
      aSetObjectTimer(Object_handles[74], 0.500000f, -1);
      aTurnOnSpew(Object_handles[74], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 25.000000f,
                  4.000000f, 40.000000f, 0, -1);
      aSetLevelTimer(30.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 143: ReactorStartCharge
    if (1) {
      if (qUserVarValue(4) > 6.000000f) {
        aShowHUDMessage(Message_strings[10]);
        aObjMakeVulnerable(data->me_handle);
        aObjDelete(Object_handles[73]);
        aObjDelete(Object_handles[72]);
        aObjDelete(Object_handles[71]);
        aObjDelete(Object_handles[69]);
      } else {
        aUserFlagSet(0, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_143 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_143++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10CE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 075: ReactorShake
    if (1) {
      aSetObjectTimer(data->me_handle, qRandomValue(0.500000f, 1.600000f), -1);
      aMiscShakeArea(data->me_handle, qRandomValue(10.000000f, 50.000000f), 2000.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0809::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 083: CycleFlames-5
    if (1) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[77], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[78], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[79], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[76], 1.000000f);
      aTurnOnSpew(Object_handles[76], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[79], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[78], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[77], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aRoomSetDamage(Room_indexes[62], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[63], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[64], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[65], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[66], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[67], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[68], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[69], 0.000000f, 4);
      aSetObjectTimer(Object_handles[75], 3.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0808::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 082: CycleFlames-4
    if (1) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[81], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[82], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[83], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[80], 1.000000f);
      aTurnOnSpew(Object_handles[80], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[83], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[82], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[81], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aRoomSetDamage(Room_indexes[70], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[71], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[72], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[73], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[74], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[75], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[76], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[77], 0.000000f, 4);
      aSetObjectTimer(Object_handles[76], 3.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 081: CycleFlames-3
    if (1) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[84], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[85], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[86], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[87], 1.000000f);
      aTurnOnSpew(Object_handles[84], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[85], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[86], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[87], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aRoomSetDamage(Room_indexes[78], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[79], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[80], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[81], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[62], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[63], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[64], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[65], 0.000000f, 4);
      aSetObjectTimer(Object_handles[80], 3.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 080: CycleFlames-2
    if (1) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[89], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[90], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[91], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[88], 1.000000f);
      aTurnOnSpew(Object_handles[89], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[90], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[91], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[88], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aRoomSetDamage(Room_indexes[66], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[67], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[68], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[69], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[70], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[71], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[72], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[73], 0.000000f, 4);
      aSetObjectTimer(Object_handles[84], 3.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0805::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 079: CycleFlames-1
    if (1) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[92], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[93], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[94], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[75], 1.000000f);
      aTurnOnSpew(Object_handles[92], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[93], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[94], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aTurnOnSpew(Object_handles[75], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 9.000000f, 5.000000f,
                  60.000000f, 0, -1);
      aRoomSetDamage(Room_indexes[77], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[76], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[75], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[74], 10.000000f, 4);
      aRoomSetDamage(Room_indexes[81], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[80], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[79], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[78], 0.000000f, 4);
      aSetObjectTimer(Object_handles[88], 3.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 087: RedDoor-2 Lock Message
    if ((ScriptActionCtr_070 > 0) == false) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[7], event_data->it_handle);
      } else {
        if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
          aShowHUDMessageObj(Message_strings[7], qObjParent(event_data->it_handle));
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 086: RedDoor-1 Lock Message
    if ((ScriptActionCtr_070 > 0) == false) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[7], event_data->it_handle);
      } else {
        if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
          aShowHUDMessageObj(Message_strings[7], qObjParent(event_data->it_handle));
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_100E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: BlueDoor Lock Message
    if ((ScriptActionCtr_069 > 0) == false) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
      } else {
        if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
          aShowHUDMessageObj(Message_strings[8], qObjParent(event_data->it_handle));
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0845::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 099: Blow Up Child ACW-12
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0844::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 098: Blow Up Child ACW-11
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0843::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 097: Blow Up Child ACW-10
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0842::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 096: Blow Up Child ACW-9
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0841::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 095: Blow Up Child ACW-8
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0840::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 094: Blow Up Child ACW-7
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 093: Blow Up Child ACW-6
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 092: Blow Up Child ACW-5
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 091: Blow Up Child ACW-4
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 090: Blow Up Child ACW-3
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 089: Blow Up Child ACW-2
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 088: Blow Up Child ACW-1
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0851::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 115: Blow Up Child ACB-12
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0850::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 114: Blow Up Child ACB-11
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 113: Blow Up Child ACB-10
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 112: Blow Up Child ACB-9
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 111: Blow Up Child ACB-8
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 110: Blow Up Child ACB-7
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 109: Blow Up Child ACB-6
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 108: Blow Up Child ACB-5
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0849::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 107: Blow Up Child ACB-4
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0848::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 106: Blow Up Child ACB-3
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0847::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 105: Blow Up Child ACB-2
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0846::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 104: Blow Up Child ACB-1
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 127: Blow Up Child ACR-12
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 126: Blow Up Child ACR-11
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 125: Blow Up Child ACR-10
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 124: Blow Up Child ACR-9
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0859::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 123: Blow Up Child ACR-8
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0858::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 122: Blow Up Child ACR-7
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0857::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 121: Blow Up Child ACR-6
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0856::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 120: Blow Up Child ACR-5
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0855::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 119: Blow Up Child ACR-4
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0854::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 118: Blow Up Child ACR-3
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0853::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 117: Blow Up Child ACR-2
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0852::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 116: Blow Up Child ACR-1
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0869::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 139: Blow Up Child ACS-12
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_139 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_139++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0868::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 138: Blow Up Child ACS-11
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_138 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_138++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0867::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 137: Blow Up Child ACS-10
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_137 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_137++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0866::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 136: Blow Up Child ACS-9
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_136 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_136++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0865::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 135: Blow Up Child ACS-8
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_135 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_135++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0864::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 134: Blow Up Child ACS-7
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_134 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_134++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0863::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 133: Blow Up Child ACS-6
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_133 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_133++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0862::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 132: Blow Up Child ACS-5
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_132 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_132++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0861::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 131: Blow Up Child ACS-4
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0860::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 130: Blow Up Child ACS-3
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 129: Blow Up Child ACS-2
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 128: Blow Up Child ACS-1
    if (1) {
      aObjDestroy(qGetAtachedChild(data->me_handle, 0));

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_003B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Start-29
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_003A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: Start-28
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0035::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Start-27
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0034::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Start-26
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0031::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Start-25
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Start-24
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Start-23
    if (qPortalIsOn(0, Room_indexes[30]) == false) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0023::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Start-22
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Start-21
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Start-20
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: Start-19
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Start-18
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Start-17
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Start-16
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Start-15
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Start-14
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Start-13
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Start-12
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Start-11
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Start-10
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Start-9
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Start-8
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Start-7
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Start-6
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Start-5
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Start-4
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Start-3
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Start-2
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

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

    // Script 001: Start-1
    if (1) {
      aMiscViewerShake(70.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_003D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Stop-28
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_003C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Stop-27
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0039::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Stop-26
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0038::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Stop-25
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0037::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Stop-24
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0036::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Stop-23
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0033::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Stop-22
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0032::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: Stop-21
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0030::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: Stop-20
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: Stop-19 (Reactor Music)
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0027::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: Stop-18
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0026::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: Stop-17
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: Stop-16
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0024::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Stop-15
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Stop-14
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Stop-13
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: Stop-12
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: Stop-11
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: Stop-10
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: Stop-9
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: Stop-8
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: Stop-7
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: Stop-6
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: Stop-5
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Stop-4
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Stop-3
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: Stop-2
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 002: Stop-1
    if (1) {
      aMiscViewerShake(45.000000f);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0040::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: End Level Camera
    if ((ScriptActionCtr_077 < 1) && (1)) {
      aGoalCompleted(Goal_indexes[6], 1);
      aGoalCompleted(Goal_indexes[7], 1);
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
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
NEXT_ID		146

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:UpFast
1:UpSlow
2:DownFast
3:DownSlow
4:ReactorDamage
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:ReactorOK
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:BlueFire1
1:BlueFire2
2:RedFire1
3:RedFire2
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:ReactorBlows
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:CloseDude
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
RedFlame-2
RedFlame-1
BlueFlame-2
BlueFlame-1
RedSwitch-2
RedSwitch-1
BlueSwitch-2
BlueSwitch-1
MiniReactorBlue-2
MiniReactorBlue-1
WarningLightBlue
ACB-12
ACB-11
ACB-10
ACB-9
ACB-8
ACB-7
ACB-6
ACB-5
ACB-4
ACB-3
ACB-2
ACB-1
MiniReactorWhite-2
MiniReactorWhite-1
WarningLightWhite
ACW-12
ACW-11
ACW-10
ACW-9
ACW-8
ACW-7
ACW-6
ACW-5
ACW-4
ACW-3
ACW-2
ACW-1
RedKey
BlueKey
MiniReactorRed-2
MiniReactorRed-1
ReactorSmoke
MiniLightRed-2
MiniLightRed-1
ACS-12
ACS-11
ACS-10
ACS-9
ACS-8
ACS-7
ACS-6
ACS-5
ACS-4
ACS-3
ACS-2
ACS-1
ACR-12
ACR-11
ACR-10
ACR-9
ACR-8
ACR-7
ACR-6
ACR-5
ACR-4
ACR-3
ACR-2
ACR-1
RNode-1
Reactor
RNode-2
RNode-3
RNode-4
BaseThing
Flames-11
Flames-15
Flames-45
Flames-35
Flames-25
Flames-14
Flames-44
Flames-34
Flames-24
Flames-13
Flames-23
Flames-33
Flames-43
Flames-12
Flames-42
Flames-32
Flames-22
Flames-41
Flames-31
Flames-21
RedDoor-2
RedDoor-1
BlueDoor
FOV
RNode-5
RNode-6
RNode-7
RNode-8
Reflector
$$OBJECT_LIST_END

$$ROOM_LIST_START
MainStop
OutStop-4
OutStop-3
OutStop-2
OutStop-1
SpeederStop-2
SpeederStop-1
Standard-8
Standard-7
Standard-6
Standard-5
Standard-4
Standard-3
Standard-2
Standard-1
InnerDown-8
InnerDown-7
InnerDown-6
InnerDown-5
InnerDown-4
InnerDown-3
InnerDown-2
InnerDown-1
InnerUp-2
InnerUp-1
AccessUp-1
AccessUp-2
AccessDown-1
AccessDown-2
Escape-2
Escape-1
Out-12
Out-11
Out-10
Out-9
Out-8
Out-7
Out-6
Out-5
Out-4
Out-3
Out-2
Out-1
Speeder-23
Speeder-22
Speeder-21
Speeder-13
Speeder-12
Speed-11
MainTube-4
MainTube-3
MainTube-2
MainTube-1
UpMain-2
UpMain-1
RedFlame-1
RedFlame-2
BlueFlame-1
BlueFlame-2
RedKeyRoom
BlueKeyRoom
Reactor
Flames-15
Flames-25
Flames-35
Flames-45
Flames-12
Flames-22
Flames-32
Flames-42
Flames-14
Flames-24
Flames-34
Flames-44
Flames-11
Flames-21
Flames-31
Flames-41
Flames-13
Flames-23
Flames-33
Flames-43
$$ROOM_LIST_END

$$TRIGGER_LIST_START
StartMini-4
StartMini-3
StartMini-2
StartMini-1
StartMain-1
StartMain-2
StartEscape-1
StartSpeed-2
StartSpeed-1
StartInUp-2
StartInUp-1
StartOffMain-2
StartOffMain-1
StartIn-4
StartIn-3
StartIn-2
StartIn-1
StartOut-4
StartOut-3
StartOut-2
StartOut-1
StartStandard-8
StartStandard-7
StartStandard-6
StartStandard-5
StartStandard-4
StartStandard-3
StartStandard-2
StartStandard-1
StopSpeed-2
StopSpeed-1
StopMini-2
StopMini-1
StopMini-4
StopMini-3
StopOffMain-2
StopOffMain-1
StopMain-1
StopMain-2
StopOut-4
StopOut-3
StopOut-2
StopOut-1
StopIn-4
StopIn-3
StopIn-2
StopIn-1
StopInUp-2
StopInUp-1
StopStandard-8
StopStandard-7
StopStandard-6
StopStandard-5
StopStandard-4
StopStandard-3
StopStandard-2
StopStandard-1
EndLevel
$$TRIGGER_LIST_END

$$SOUND_LIST_START
LevSecAccelStart
LevSecAccelRelease
AmbSwitch11
PupC1
AmbSirenBRedAcrop
wallofire1
HitEnergy
Lightning
Forcefield bounce
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffect5
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Destroy Red Key Forcefield Generators
Destroy Blue Key Forcefield Generators
Acquire the Red Key
Acquire the Blue Key
Destroy Reactor Forcefield Generators
Destroy the Reactor
Escape the Research Center
Destroy the Research Center
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Wind
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
                        10:10:0:3:UserVar
                        10:6:-50.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:-120.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:50.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:120.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:17:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:18:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:20:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:21:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:22:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:24:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:25:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:26:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:27:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:28:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:29:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:32:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:33:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:34:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:35:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:36:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:37:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:38:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:39:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:40:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:41:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:42:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:43:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:44:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:45:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:46:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:47:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:48:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:49:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:50:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:51:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:52:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:53:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:54:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Start-29
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Start-28
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Start-27
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Start-26
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Start-25
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Start-24
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Start-23
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qPortalIsOn:Bool
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:30:Room
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Start-22
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Start-21
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Start-20
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Start-19
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Start-18
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Start-17
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Start-16
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Start-15
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Start-14
        $$CHILD_BLOCK_START
        01:0:15
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Start-13
        $$CHILD_BLOCK_START
        01:0:16
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Start-12
        $$CHILD_BLOCK_START
        01:0:17
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Start-11
        $$CHILD_BLOCK_START
        01:0:18
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Start-10
        $$CHILD_BLOCK_START
        01:0:19
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Start-9
        $$CHILD_BLOCK_START
        01:0:20
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Start-8
        $$CHILD_BLOCK_START
        01:0:21
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Start-7
        $$CHILD_BLOCK_START
        01:0:22
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Start-6
        $$CHILD_BLOCK_START
        01:0:23
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Start-5
        $$CHILD_BLOCK_START
        01:0:24
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Start-4
        $$CHILD_BLOCK_START
        01:0:25
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Start-3
        $$CHILD_BLOCK_START
        01:0:26
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Start-2
        $$CHILD_BLOCK_START
        01:0:27
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Start-1
        $$CHILD_BLOCK_START
        01:0:28
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Stop-28
        $$CHILD_BLOCK_START
        01:0:29
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Stop-27
        $$CHILD_BLOCK_START
        01:0:30
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Stop-26
        $$CHILD_BLOCK_START
        01:0:31
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Stop-25
        $$CHILD_BLOCK_START
        01:0:32
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Stop-24
        $$CHILD_BLOCK_START
        01:0:33
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Stop-23
        $$CHILD_BLOCK_START
        01:0:34
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Stop-22
        $$CHILD_BLOCK_START
        01:0:35
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Stop-21
        $$CHILD_BLOCK_START
        01:0:36
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Stop-20
        $$CHILD_BLOCK_START
        01:0:37
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Stop-19 (Reactor Music)
        $$CHILD_BLOCK_START
        01:0:38
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Stop-18
        $$CHILD_BLOCK_START
        01:0:39
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Stop-17
        $$CHILD_BLOCK_START
        01:0:40
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Stop-16
        $$CHILD_BLOCK_START
        01:0:41
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Stop-15
        $$CHILD_BLOCK_START
        01:0:42
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Stop-14
        $$CHILD_BLOCK_START
        01:0:43
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Stop-13
        $$CHILD_BLOCK_START
        01:0:44
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Stop-12
        $$CHILD_BLOCK_START
        01:0:45
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Stop-11
        $$CHILD_BLOCK_START
        01:0:46
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Stop-10
        $$CHILD_BLOCK_START
        01:0:47
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Stop-9
        $$CHILD_BLOCK_START
        01:0:48
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Stop-8
        $$CHILD_BLOCK_START
        01:0:49
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Stop-7
        $$CHILD_BLOCK_START
        01:0:50
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Stop-6
        $$CHILD_BLOCK_START
        01:0:51
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Stop-5
        $$CHILD_BLOCK_START
        01:0:52
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Stop-4
        $$CHILD_BLOCK_START
        01:0:53
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Stop-3
        $$CHILD_BLOCK_START
        01:0:54
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Stop-2
        $$CHILD_BLOCK_START
        01:0:55
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Stop-1
        $$CHILD_BLOCK_START
        01:0:56
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:45.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:StartSecretFlames
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
                        10:2:55:Room
                        10:6:15.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:56:Room
                        10:6:15.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:57:Room
                        10:6:15.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:58:Room
                        10:6:15.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
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
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
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
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
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
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:RedSwitch-2
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FlameDeactivated:Message
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:56:Room
                        10:6:0.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:RedSwitch-1
        $$CHILD_BLOCK_START
        01:1:5
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FlameDeactivated:Message
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:55:Room
                        10:6:0.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:BlueSwitch-2
        $$CHILD_BLOCK_START
        01:1:6
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FlameDeactivated:Message
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:58:Room
                        10:6:0.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:BlueSwitch-1
        $$CHILD_BLOCK_START
        01:1:7
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FlameDeactivated:Message
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:57:Room
                        10:6:0.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:MiniReactorBlue-2
        $$CHILD_BLOCK_START
        01:1:8
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:9:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:MiniReactorBlue-1
        $$CHILD_BLOCK_START
        01:1:9
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:MiniReactorBlue TimerChain
        $$CHILD_BLOCK_START
        01:1:10
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:5.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:4.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:3.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:MiniReactorBlue Timer
        $$CHILD_BLOCK_START
        01:1:10
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:59:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RedKeyFF:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:MiniReactorWhite-2
        $$CHILD_BLOCK_START
        01:1:23
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:MiniReactorWhite-1
        $$CHILD_BLOCK_START
        01:1:24
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:MiniReactorWhite TimerChain
        $$CHILD_BLOCK_START
        01:1:25
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:5.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:6:4.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:3.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:MiniReactorWhite Timer
        $$CHILD_BLOCK_START
        01:1:25
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:60:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BlueKeyFF:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Red Key
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:2:KeyNum
                        10:8:NameRedKey:KeyName
                        10:10:0:1:Yes/No
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Blue Key
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:1:KeyNum
                        10:8:NameBlueKey:KeyName
                        10:10:0:1:Yes/No
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:MiniReactorRed-2
        $$CHILD_BLOCK_START
        01:1:40
        02:4
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
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:41:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:42:Object
                                10:6:0.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:MiniReactorRed-1
        $$CHILD_BLOCK_START
        01:1:41
        02:4
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
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:40:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:42:Object
                                10:6:0.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:MiniReactorRed-2 Timer Chain
        $$CHILD_BLOCK_START
        01:1:43
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:6:5.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:6:4.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:6:3.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:MiniReactorRed-1 Timer Chain
        $$CHILD_BLOCK_START
        01:1:44
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:6:5.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:6:4.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:6:3.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:MiniReactorRed Timer
        $$CHILD_BLOCK_START
        01:1:42
        02:9
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
                        10:6:9999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:5:TimesDrawn
                        10:4:255:Red
                        10:4:30:Green
                        10:4:20:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object1
                        10:1:0:70:Object2
                        10:6:9999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:5:TimesDrawn
                        10:4:255:Red
                        10:4:30:Green
                        10:4:20:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object1
                        10:1:0:70:Object2
                        10:6:9999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:5:TimesDrawn
                        10:4:255:Red
                        10:4:30:Green
                        10:4:20:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object1
                        10:1:0:70:Object2
                        10:6:9999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:5:TimesDrawn
                        10:4:255:Red
                        10:4:30:Green
                        10:4:20:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:61:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ReactorFF:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Reactor Destroyed
        $$CHILD_BLOCK_START
        01:1:70
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:4:Region
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ReactorDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:30:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:25.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:ReactorShake
        $$CHILD_BLOCK_START
        01:1:74
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:0.500000:LowerLimit
                                10:6:1.600000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:50.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:6:2000.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Reactor Blows
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:77:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalFailed
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:10:0:1:Failed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:7:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aEndLevel
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:End Level Camera
        $$CHILD_BLOCK_START
        01:0:57
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:StartMiniReactors
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
                        10:1:0:40:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:StartFlames
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:CycleFlames-5
        $$CHILD_BLOCK_START
        01:1:76
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:77:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:78:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:79:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:76:Object
                        10:9:1.000000:Volume
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:62:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:63:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:64:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:65:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:66:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:67:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:68:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:69:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:CycleFlames-4
        $$CHILD_BLOCK_START
        01:1:80
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:81:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:82:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:83:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:80:Object
                        10:9:1.000000:Volume
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:70:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:71:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:72:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:73:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:74:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:75:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:76:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:77:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:CycleFlames-3
        $$CHILD_BLOCK_START
        01:1:84
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:84:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:85:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:86:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:87:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:86:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:78:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:79:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:80:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:81:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:62:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:63:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:64:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:65:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:CycleFlames-2
        $$CHILD_BLOCK_START
        01:1:88
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:89:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:90:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:91:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:88:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:90:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:66:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:67:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:68:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:69:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:70:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:71:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:72:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:73:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:CycleFlames-1
        $$CHILD_BLOCK_START
        01:1:75
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:92:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:93:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:94:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:75:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:92:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:93:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:94:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:9.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:77:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:76:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:75:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:74:Room
                        10:6:10.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:81:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:80:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:79:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:78:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:RedDoor-2 Lock Message
        $$CHILD_BLOCK_START
        01:1:95
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:70:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:RedDoor:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:RedDoor:Message
                                        06:qObjParent:PlayerObject
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:RedDoor-1 Lock Message
        $$CHILD_BLOCK_START
        01:1:96
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:70:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:RedDoor:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:RedDoor:Message
                                        06:qObjParent:PlayerObject
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:BlueDoor Lock Message
        $$CHILD_BLOCK_START
        01:1:97
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:69:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:BlueDoor:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:BlueDoor:Message
                                        06:qObjParent:PlayerObject
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:Blow Up Child ACW-12
        $$CHILD_BLOCK_START
        01:1:26
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:Blow Up Child ACW-11
        $$CHILD_BLOCK_START
        01:1:27
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:Blow Up Child ACW-10
        $$CHILD_BLOCK_START
        01:1:28
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Blow Up Child ACW-9
        $$CHILD_BLOCK_START
        01:1:29
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:Blow Up Child ACW-8
        $$CHILD_BLOCK_START
        01:1:30
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Blow Up Child ACW-7
        $$CHILD_BLOCK_START
        01:1:31
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Blow Up Child ACW-6
        $$CHILD_BLOCK_START
        01:1:32
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Blow Up Child ACW-5
        $$CHILD_BLOCK_START
        01:1:33
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Blow Up Child ACW-4
        $$CHILD_BLOCK_START
        01:1:34
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Blow Up Child ACW-3
        $$CHILD_BLOCK_START
        01:1:35
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Blow Up Child ACW-2
        $$CHILD_BLOCK_START
        01:1:36
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Blow Up Child ACW-1
        $$CHILD_BLOCK_START
        01:1:37
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:Blow Up Child ACB-12
        $$CHILD_BLOCK_START
        01:1:11
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:Blow Up Child ACB-11
        $$CHILD_BLOCK_START
        01:1:12
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:Blow Up Child ACB-10
        $$CHILD_BLOCK_START
        01:1:13
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:Blow Up Child ACB-9
        $$CHILD_BLOCK_START
        01:1:14
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:Blow Up Child ACB-8
        $$CHILD_BLOCK_START
        01:1:15
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Blow Up Child ACB-7
        $$CHILD_BLOCK_START
        01:1:16
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:Blow Up Child ACB-6
        $$CHILD_BLOCK_START
        01:1:17
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:Blow Up Child ACB-5
        $$CHILD_BLOCK_START
        01:1:18
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:Blow Up Child ACB-4
        $$CHILD_BLOCK_START
        01:1:19
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:Blow Up Child ACB-3
        $$CHILD_BLOCK_START
        01:1:20
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:Blow Up Child ACB-2
        $$CHILD_BLOCK_START
        01:1:21
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:Blow Up Child ACB-1
        $$CHILD_BLOCK_START
        01:1:22
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:Blow Up Child ACR-12
        $$CHILD_BLOCK_START
        01:1:57
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:Blow Up Child ACR-11
        $$CHILD_BLOCK_START
        01:1:58
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:Blow Up Child ACR-10
        $$CHILD_BLOCK_START
        01:1:59
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:124:Blow Up Child ACR-9
        $$CHILD_BLOCK_START
        01:1:60
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:Blow Up Child ACR-8
        $$CHILD_BLOCK_START
        01:1:61
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:Blow Up Child ACR-7
        $$CHILD_BLOCK_START
        01:1:62
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:Blow Up Child ACR-6
        $$CHILD_BLOCK_START
        01:1:63
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:Blow Up Child ACR-5
        $$CHILD_BLOCK_START
        01:1:64
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:Blow Up Child ACR-4
        $$CHILD_BLOCK_START
        01:1:65
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:Blow Up Child ACR-3
        $$CHILD_BLOCK_START
        01:1:66
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:Blow Up Child ACR-2
        $$CHILD_BLOCK_START
        01:1:67
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:Blow Up Child ACR-1
        $$CHILD_BLOCK_START
        01:1:68
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:139:Blow Up Child ACS-12
        $$CHILD_BLOCK_START
        01:1:45
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:138:Blow Up Child ACS-11
        $$CHILD_BLOCK_START
        01:1:46
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:137:Blow Up Child ACS-10
        $$CHILD_BLOCK_START
        01:1:47
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:136:Blow Up Child ACS-9
        $$CHILD_BLOCK_START
        01:1:48
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:135:Blow Up Child ACS-8
        $$CHILD_BLOCK_START
        01:1:49
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:134:Blow Up Child ACS-7
        $$CHILD_BLOCK_START
        01:1:50
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:133:Blow Up Child ACS-6
        $$CHILD_BLOCK_START
        01:1:51
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:132:Blow Up Child ACS-5
        $$CHILD_BLOCK_START
        01:1:52
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:131:Blow Up Child ACS-4
        $$CHILD_BLOCK_START
        01:1:53
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:Blow Up Child ACS-3
        $$CHILD_BLOCK_START
        01:1:54
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:Blow Up Child ACS-2
        $$CHILD_BLOCK_START
        01:1:55
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:Blow Up Child ACS-1
        $$CHILD_BLOCK_START
        01:1:56
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:140:IntroCam
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
                        10:8:IntroCam:Text
                        10:1:0:38:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:141:StartMusic
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
                        10:10:0:5:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:142:ReactorInit
        $$CHILD_BLOCK_START
        01:1:70
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:143:ReactorStartCharge
        $$CHILD_BLOCK_START
        01:1:70
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
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ReactorPrimed:Message
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:0:73:Object
                                $$CHILD_BLOCK_END
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:0:72:Object
                                $$CHILD_BLOCK_END
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:0:71:Object
                                $$CHILD_BLOCK_END
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:0:69:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:144:Reactor Discharge
        $$CHILD_BLOCK_START
        01:1:70
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
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qPlayerClosest:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeeObjAdvanced:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:TargetObject
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:4:180:Cone
                                        10:1:0:98:Object
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
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:5.000000:DamageAmount
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:99:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.600000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:-0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:100:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.600000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:-0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:101:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.600000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:-0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:102:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.600000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:-0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:6:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:7:Sound
                                10:1:0:98:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:30.000000:SparkRate
                                10:6:0.800000:Time
                                $$CHILD_BLOCK_END
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:98:Object
                                10:6:50.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:8:Sound
                                10:1:0:103:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:7:Sound
                                10:1:0:98:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:70:Object
                                06:qMathPercentage:SparkRate
                                        $$CHILD_BLOCK_START
                                        10:9:10.000000:Percent
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:98:Object
                                10:6:25.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:103:Object1
                                10:1:0:98:Object2
                                10:6:0.600000:Lifetime
                                10:6:6.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:99:Object1
                                10:1:0:103:Object2
                                10:6:0.600000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:100:Object1
                                10:1:0:103:Object2
                                10:6:0.600000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:0.400000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:101:Object1
                                10:1:0:103:Object2
                                10:6:0.600000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:102:Object1
                                10:1:0:103:Object2
                                10:6:0.600000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:0.700000:SlideTime
                                10:4:5:TimesDrawn
                                10:4:255:Red
                                10:4:30:Green
                                10:4:20:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:145:Set visited flag
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMissionSetFlag
                        $$CHILD_BLOCK_START
                        10:4:30:FlagNum
                        10:5:1:State
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
