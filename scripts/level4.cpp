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
// Filename:	level4.cpp
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

#define ID_CUSTOM_OBJECT_08B3 0x001
#define ID_CUSTOM_OBJECT_08AE 0x002
#define ID_CUSTOM_OBJECT_1213 0x003
#define ID_CUSTOM_OBJECT_117D 0x004

#define ID_TRIGGER_0000 0x005
#define ID_TRIGGER_0001 0x006
#define ID_TRIGGER_0003 0x007
#define ID_TRIGGER_0005 0x008
#define ID_TRIGGER_0002 0x009
#define ID_TRIGGER_0009 0x00a
#define ID_TRIGGER_0007 0x00b
#define ID_TRIGGER_0006 0x00c
#define ID_TRIGGER_0004 0x00d
#define ID_TRIGGER_0008 0x00e

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

class CustomObjectScript_08B3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08AE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1213 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_117D : public BaseScript {
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

class TriggerScript_0003 : public BaseScript {
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

class TriggerScript_0009 : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_014 = 0;
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
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_014 = 0;
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
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
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
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Train
2:CityFirst
3:Sewer
4:CitySecond
5:Suzuki
6:Ambush
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
static const char *const Door_names[NUM_DOOR_NAMES] = {"PlazaEntrance"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 38
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "DataCartridge", "Train1",        "Train2",        "Train3",        "Train4",    "ElectricDown1", "ElectricDown2",
    "ElectricDown3", "ElectricDown4", "ElectricDown5", "ElectricDown6", "Electric1", "Electric2",     "Electric3",
    "Electric4",     "UploadMiddle",  "DataHolder",    "Upload4",       "Upload3",   "Upload2",       "Upload1",
    "TorchA",        "TorchB",        "TorchC",        "TorchD",        "SteamA",    "SteamB",        "SteamC",
    "SteamD",        "SteamE",        "CloakMerc",     "MercTarget",    "BPMain",    "BPSideKick",    "CarGoal2",
    "CarGoal-1",     "GardenSpew-2",  "GardenSpew-1"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 0
static const char **Room_names = NULL;
static int *Room_indexes = NULL;

#define NUM_TRIGGER_NAMES 10
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EnterUpload",   "ExitUpload",    "MTrain",   "MCityFirst-2", "MCityFirst",
    "MCitySecond-2", "MCitySecond-1", "MSewer-2", "MSewer-1",     "MSuzukiTower"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 2
static const char *const Sound_names[NUM_SOUND_NAMES] = {"Lev4TrainTest", "PupC1"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 1
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffectAntiV"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 13
static const char *const Path_names[NUM_PATH_NAMES] = {
    "IntroCam",   "IntroShip",  "Train1",    "Train2",     "Train3", "Train4", "UploadWatch",
    "Merc1Intro", "Merc2Intro", "MercWatch", "CloakMerc1", "EndCam", "EndShip"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 6
static const char *Matcen_names[NUM_MATCEN_NAMES] = {"Cars-1",    "Cars-2",    "TrainCen1",
                                                     "TrainCen2", "TrainCen3", "TrainCen4"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 3
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Upload the data to Suzuki", "Defeat the PTMC Mercenaries",
                                                       "Give the Data to Suzuki and Return Safely"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 8
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "CinematicIntroCam", "PutTheCartridge", "CinematicDataCart", "CartridgeError", "GetOut",
    "CinematicAmbush",   "BPDefeated",      "CinematicEndCam"};
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
    strcpy(filename, "level4.msg");
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
  case ID_CUSTOM_OBJECT_08B3:
    return new CustomObjectScript_08B3;
    break;
  case ID_CUSTOM_OBJECT_08AE:
    return new CustomObjectScript_08AE;
    break;
  case ID_CUSTOM_OBJECT_1213:
    return new CustomObjectScript_1213;
    break;
  case ID_CUSTOM_OBJECT_117D:
    return new CustomObjectScript_117D;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
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
  case ID_CUSTOM_OBJECT_08B3:
    delete ((CustomObjectScript_08B3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08AE:
    delete ((CustomObjectScript_08AE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1213:
    delete ((CustomObjectScript_1213 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_117D:
    delete ((CustomObjectScript_117D *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
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
  case ID_CUSTOM_OBJECT_08B3:
  case ID_CUSTOM_OBJECT_08AE:
  case ID_CUSTOM_OBJECT_1213:
  case ID_CUSTOM_OBJECT_117D:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0004:
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
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0008;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[4];
  static int cust_id_list[4] = {ID_CUSTOM_OBJECT_08B3, ID_CUSTOM_OBJECT_08AE, ID_CUSTOM_OBJECT_1213,
                                ID_CUSTOM_OBJECT_117D};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[15];
  cust_handle_list[2] = Object_handles[33];
  cust_handle_list[3] = Object_handles[32];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 4;
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

    // Script 033: Level Start Intro Cam
    if (1 == true) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[0], Path_indexes[1], 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 000: Level Start - Trains INIT
    if (1 == true) {
      aSetLevelTimer(0.100000f, 4);
      aUserVarSet(0, 1.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aUserVarSet(3, 1.000000f);
      aUserVarSet(4, 0.000000f);
      aObjGhostSet(1, Object_handles[1]);
      aObjGhostSet(1, Object_handles[2]);
      aObjGhostSet(1, Object_handles[3]);
      aObjGhostSet(1, Object_handles[4]);
      aMatcenSetState(1, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[1]);
      aMatcenSetState(1, Matcen_indexes[2]);
      aMatcenSetState(1, Matcen_indexes[3]);
      aMatcenSetState(1, Matcen_indexes[4]);
      aMatcenSetState(1, Matcen_indexes[5]);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 034: Sean's Flaming Torches!
    if (1) {
      aTurnOnSpew(Object_handles[21], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.250000f, -1.000000f,
                  8.000000f, 15.000000f, 1, 0);
      aTurnOnSpew(Object_handles[22], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.250000f, -1.000000f,
                  8.000000f, 15.000000f, 1, 1);
      aTurnOnSpew(Object_handles[23], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.250000f, -1.000000f,
                  8.000000f, 15.000000f, 1, 2);
      aTurnOnSpew(Object_handles[24], -1, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.250000f, -1.000000f,
                  8.000000f, 15.000000f, 1, 3);
      aTurnOnSpew(Object_handles[25], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                  4.000000f, 20.000000f, 0, 4);
      aTurnOnSpew(Object_handles[26], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                  4.000000f, 20.000000f, 0, 5);
      aTurnOnSpew(Object_handles[27], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                  4.000000f, 20.000000f, 0, 6);
      aTurnOnSpew(Object_handles[28], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                  4.000000f, 20.000000f, 0, 7);
      aTurnOnSpew(Object_handles[29], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                  4.000000f, 20.000000f, 0, 8);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 036: Mercenary INIT
    if (1) {
      aObjGhostSet(1, Object_handles[30]);
      aObjGhostSet(1, Object_handles[31]);
      aObjGhostSet(1, Object_handles[32]);
      aObjGhostSet(1, Object_handles[33]);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 040: MusicStart (Train)
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 053: Secret Garden Spew
    if (1) {
      aTurnOnSpew(Object_handles[36], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                  3.000000f, 30.000000f, 1, 9);
      aTurnOnSpew(Object_handles[37], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                  6.000000f, 40.000000f, 1, 9);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 003: Train1 Matcen Delay
    if (event_data->id == 0) {
      aMatcenSetEnableState(1, Matcen_indexes[2]);
      aObjGhostSet(0, qObjSavedHandle(0));
      aStoreObjectInPositionClipboard(Object_handles[1]);
      aMoveObjectToPositionClipboard(qObjSavedHandle(0));
      aSoundPlayObject(Sound_indexes[0], qObjSavedHandle(0), 1.000000f);
      aAIGoalFollowPathSimple(qObjSavedHandle(0), Path_indexes[2], 2101504, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 005: Train1 Next Delay Time
    if (event_data->id == 0) {
      if (qUserVarValue(1) == 0.000000f) {
        aUserVarSet(1, 4.000000f);
      } else {
        if (qUserVarValue(1) == 4.000000f) {
          aUserVarSet(1, 3.000000f);
        } else {
          if (qUserVarValue(1) == 3.000000f) {
            aUserVarSet(1, 5.000000f);
          } else {
            if (qUserVarValue(1) == 5.000000f) {
              aUserVarSet(1, 2.000000f);
            } else {
              aUserVarSet(1, 0.000000f);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 006: Train2 Matcen Delay
    if (event_data->id == 1) {
      aMatcenSetEnableState(1, Matcen_indexes[3]);
      aObjGhostSet(0, qObjSavedHandle(1));
      aStoreObjectInPositionClipboard(Object_handles[2]);
      aMoveObjectToPositionClipboard(qObjSavedHandle(1));
      aSoundPlayObject(Sound_indexes[0], qObjSavedHandle(1), 1.000000f);
      aAIGoalFollowPathSimple(qObjSavedHandle(1), Path_indexes[3], 2101504, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 007: Train2 Next Delay Time
    if (event_data->id == 1) {
      if (qUserVarValue(2) == 0.000000f) {
        aUserVarSet(2, 3.000000f);
      } else {
        if (qUserVarValue(2) == 3.000000f) {
          aUserVarSet(2, 10.000000f);
        } else {
          if (qUserVarValue(2) == 10.000000f) {
            aUserVarSet(2, 4.000000f);
          } else {
            if (qUserVarValue(2) == 4.000000f) {
              aUserVarSet(2, 2.000000f);
            } else {
              if (qUserVarValue(2) == 2.000000f) {
                aUserVarSet(2, 12.000000f);
              } else {
                aUserVarSet(2, 0.000000f);
              }
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 009: Train3 Matcen Delay
    if (event_data->id == 2) {
      aMatcenSetEnableState(1, Matcen_indexes[4]);
      aObjGhostSet(0, qObjSavedHandle(2));
      aStoreObjectInPositionClipboard(Object_handles[3]);
      aMoveObjectToPositionClipboard(qObjSavedHandle(2));
      aSoundPlayObject(Sound_indexes[0], qObjSavedHandle(2), 1.000000f);
      aAIGoalFollowPathSimple(qObjSavedHandle(2), Path_indexes[4], 2101504, 2, 3);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 010: Train3 Next Delay Time
    if (event_data->id == 2) {
      if (qUserVarValue(3) == 1.000000f) {
        aUserVarSet(3, 4.000000f);
      } else {
        if (qUserVarValue(3) == 4.000000f) {
          aUserVarSet(3, 15.000000f);
        } else {
          if (qUserVarValue(3) == 15.000000f) {
            aUserVarSet(3, 6.000000f);
          } else {
            aUserVarSet(3, 1.000000f);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }

    // Script 012: Train4 Matcen Delay
    if (event_data->id == 3) {
      aMatcenSetEnableState(1, Matcen_indexes[5]);
      aObjGhostSet(0, qObjSavedHandle(3));
      aStoreObjectInPositionClipboard(Object_handles[4]);
      aMoveObjectToPositionClipboard(qObjSavedHandle(3));
      aSoundPlayObject(Sound_indexes[0], qObjSavedHandle(3), 1.000000f);
      aAIGoalFollowPathSimple(qObjSavedHandle(3), Path_indexes[5], 2101504, 3, 3);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 011: Train4 Next Delay Time
    if (event_data->id == 3) {
      if (qUserVarValue(4) == 0.000000f) {
        aUserVarSet(4, 4.000000f);
      } else {
        if (qUserVarValue(4) == 4.000000f) {
          aUserVarSet(4, 18.000000f);
        } else {
          if (qUserVarValue(4) == 18.000000f) {
            aUserVarSet(4, 5.000000f);
          } else {
            if (qUserVarValue(4) == 5.000000f) {
              aUserVarSet(4, 1.000000f);
            } else {
              if (qUserVarValue(4) == 1.000000f) {
                aUserVarSet(4, 16.000000f);
              } else {
                if (qUserVarValue(4) == 16.000000f) {
                  aUserVarSet(4, 3.000000f);
                } else {
                  aUserVarSet(4, 0.000000f);
                }
              }
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 028: Train Shakers Add 4
    if (event_data->id == 3) {
      if (qUserVarValue(0) == 1.000000f) {
        aObjSaveHandle(qObjSavedHandle(3), 4);
        aUserVarSet(0, 2.000000f);
      } else {
        if (qUserVarValue(0) == 2.000000f) {
          aObjSaveHandle(qObjSavedHandle(3), 5);
          aUserVarSet(0, 3.000000f);
        } else {
          if (qUserVarValue(0) == 3.000000f) {
            aObjSaveHandle(qObjSavedHandle(3), 6);
            aUserVarSet(0, 4.000000f);
          } else {
            if (qUserVarValue(0) == 4.000000f) {
              aObjSaveHandle(qObjSavedHandle(3), 7);
              aUserVarSet(0, 5.000000f);
            } else {
              if (qUserVarValue(0) == 5.000000f) {
                aObjSaveHandle(qObjSavedHandle(3), 8);
                aUserVarSet(0, 6.000000f);
              } else {
                if (qUserVarValue(0) == 6.000000f) {
                  aObjSaveHandle(qObjSavedHandle(3), 9);
                  aUserVarSet(0, 7.000000f);
                } else {
                  if (qUserVarValue(0) == 7.000000f) {
                    aObjSaveHandle(qObjSavedHandle(3), 10);
                    aUserVarSet(0, 8.000000f);
                  } else {
                    if (qUserVarValue(0) == 8.000000f) {
                      aObjSaveHandle(qObjSavedHandle(3), 11);
                      aUserVarSet(0, 9.000000f);
                    } else {
                      if (qUserVarValue(0) == 9.000000f) {
                        aObjSaveHandle(qObjSavedHandle(3), 12);
                        aUserVarSet(0, 10.000000f);
                      } else {
                        if (qUserVarValue(0) == 10.000000f) {
                          aObjSaveHandle(qObjSavedHandle(3), 13);
                          aUserVarSet(0, 1.000000f);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }

    // Script 027: Train Shakers Add 3
    if (event_data->id == 2) {
      if (qUserVarValue(0) == 1.000000f) {
        aObjSaveHandle(qObjSavedHandle(2), 4);
        aUserVarSet(0, 2.000000f);
      } else {
        if (qUserVarValue(0) == 2.000000f) {
          aObjSaveHandle(qObjSavedHandle(2), 5);
          aUserVarSet(0, 3.000000f);
        } else {
          if (qUserVarValue(0) == 3.000000f) {
            aObjSaveHandle(qObjSavedHandle(2), 6);
            aUserVarSet(0, 4.000000f);
          } else {
            if (qUserVarValue(0) == 4.000000f) {
              aObjSaveHandle(qObjSavedHandle(2), 7);
              aUserVarSet(0, 5.000000f);
            } else {
              if (qUserVarValue(0) == 5.000000f) {
                aObjSaveHandle(qObjSavedHandle(6), 8);
                aUserVarSet(0, 6.000000f);
              } else {
                if (qUserVarValue(0) == 6.000000f) {
                  aObjSaveHandle(qObjSavedHandle(2), 9);
                  aUserVarSet(0, 7.000000f);
                } else {
                  if (qUserVarValue(0) == 7.000000f) {
                    aObjSaveHandle(qObjSavedHandle(2), 10);
                    aUserVarSet(0, 8.000000f);
                  } else {
                    if (qUserVarValue(0) == 8.000000f) {
                      aObjSaveHandle(qObjSavedHandle(2), 11);
                      aUserVarSet(0, 9.000000f);
                    } else {
                      if (qUserVarValue(0) == 9.000000f) {
                        aObjSaveHandle(qObjSavedHandle(2), 12);
                        aUserVarSet(0, 10.000000f);
                      } else {
                        if (qUserVarValue(0) == 10.000000f) {
                          aObjSaveHandle(qObjSavedHandle(2), 13);
                          aUserVarSet(0, 1.000000f);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 026: Train Shakers Add 2
    if (event_data->id == 1) {
      if (qUserVarValue(0) == 1.000000f) {
        aObjSaveHandle(qObjSavedHandle(1), 4);
        aUserVarSet(0, 2.000000f);
      } else {
        if (qUserVarValue(0) == 2.000000f) {
          aObjSaveHandle(qObjSavedHandle(1), 5);
          aUserVarSet(0, 3.000000f);
        } else {
          if (qUserVarValue(0) == 3.000000f) {
            aObjSaveHandle(qObjSavedHandle(1), 6);
            aUserVarSet(0, 4.000000f);
          } else {
            if (qUserVarValue(0) == 4.000000f) {
              aObjSaveHandle(qObjSavedHandle(1), 7);
              aUserVarSet(0, 5.000000f);
            } else {
              if (qUserVarValue(0) == 5.000000f) {
                aObjSaveHandle(qObjSavedHandle(1), 8);
                aUserVarSet(0, 6.000000f);
              } else {
                if (qUserVarValue(0) == 6.000000f) {
                  aObjSaveHandle(qObjSavedHandle(1), 9);
                  aUserVarSet(0, 7.000000f);
                } else {
                  if (qUserVarValue(0) == 7.000000f) {
                    aObjSaveHandle(qObjSavedHandle(1), 10);
                    aUserVarSet(0, 8.000000f);
                  } else {
                    if (qUserVarValue(0) == 8.000000f) {
                      aObjSaveHandle(qObjSavedHandle(1), 11);
                      aUserVarSet(0, 9.000000f);
                    } else {
                      if (qUserVarValue(0) == 9.000000f) {
                        aObjSaveHandle(qObjSavedHandle(1), 12);
                        aUserVarSet(0, 10.000000f);
                      } else {
                        if (qUserVarValue(0) == 10.000000f) {
                          aObjSaveHandle(qObjSavedHandle(1), 13);
                          aUserVarSet(0, 1.000000f);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 014: Train Shakers Add 1
    if (event_data->id == 0) {
      if (qUserVarValue(0) == 1.000000f) {
        aObjSaveHandle(qObjSavedHandle(0), 4);
        aUserVarSet(0, 2.000000f);
      } else {
        if (qUserVarValue(0) == 2.000000f) {
          aObjSaveHandle(qObjSavedHandle(0), 5);
          aUserVarSet(0, 3.000000f);
        } else {
          if (qUserVarValue(0) == 3.000000f) {
            aObjSaveHandle(qObjSavedHandle(0), 6);
            aUserVarSet(0, 4.000000f);
          } else {
            if (qUserVarValue(0) == 4.000000f) {
              aObjSaveHandle(qObjSavedHandle(0), 7);
              aUserVarSet(0, 5.000000f);
            } else {
              if (qUserVarValue(0) == 5.000000f) {
                aObjSaveHandle(qObjSavedHandle(0), 8);
                aUserVarSet(0, 6.000000f);
              } else {
                if (qUserVarValue(0) == 6.000000f) {
                  aObjSaveHandle(qObjSavedHandle(0), 9);
                  aUserVarSet(0, 7.000000f);
                } else {
                  if (qUserVarValue(0) == 7.000000f) {
                    aObjSaveHandle(qObjSavedHandle(0), 10);
                    aUserVarSet(0, 8.000000f);
                  } else {
                    if (qUserVarValue(0) == 8.000000f) {
                      aObjSaveHandle(qObjSavedHandle(0), 11);
                      aUserVarSet(0, 9.000000f);
                    } else {
                      if (qUserVarValue(0) == 9.000000f) {
                        aObjSaveHandle(qObjSavedHandle(0), 12);
                        aUserVarSet(0, 10.000000f);
                      } else {
                        if (qUserVarValue(0) == 10.000000f) {
                          aObjSaveHandle(qObjSavedHandle(0), 13);
                          aUserVarSet(0, 1.000000f);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 025: Train Shaker Timer Recycle
    if (event_data->id == 4) {
      aSetLevelTimer(0.100000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 024: Train Shaker 10
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(13), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(13), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 023: Train Shaker 9
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(12), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(12), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 022: Train Shaker 8
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(11), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(11), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 021: Train Shaker 7
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(10), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(10), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 020: Train Shaker 6
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(9), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(9), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 019: Train Shaker 5
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(8), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(8), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 018: Train Shaker 4
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(7), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(7), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 017: Train Shaker 3
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(6), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(6), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 016: Train Shaker 2
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(5), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(5), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 015: Train Shaker 1
    if (event_data->id == 4) {
      if (qObjCanSeePlayer(90, qObjSavedHandle(4), 300.000000f) == true) {
        aMiscShakeArea(qObjSavedHandle(4), 40.000000f, 300.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 037: EndLevel Cam
    if (5 == event_data->id) {
      aGoalCompleted(Goal_indexes[2], 1);
      aObjGhostSet(0, Object_handles[30]);
      aCloakObject(Object_handles[30], 10.000000f);
      aAISetMaxSpeed(Object_handles[30], 40.000000f);
      aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[10], 4352, -1, 3);
      aStartEndlevelSequencePath(Path_indexes[11], Path_indexes[12], 10.000000f, Message_strings[7]);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 002: Train Any Done (so delete IT)
    if ((event_data->goal_uid == 0) || (event_data->goal_uid == 1) || (event_data->goal_uid == 2) ||
        (event_data->goal_uid == 3)) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 050: CarDestroy
    if (event_data->goal_uid == 6) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 052: Determine Difficult Adjustment (on Matcen Creations)
    if (1) {
      if (qGetDifficulty() == 0) {
        aUserVarSet(5, 4.000000f);
      } else {
        if (qGetDifficulty() == 1) {
          aUserVarSet(5, 2.000000f);
        } else {
          if (qGetDifficulty() == 2) {
            aUserVarSet(5, 0.800000f);
          } else {
            if (qGetDifficulty() == 3) {
              aUserVarSet(5, 0.400000f);
            } else {
              aUserVarSet(5, 0.000000f);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }

    // Script 001: Train1 Matcen Produced a Train
    if (event_data->id == Matcen_indexes[2]) {
      aMatcenSetEnableState(0, Matcen_indexes[2]);
      aObjGhostSet(1, event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 0);
      if (qUserVarValue(1) > 3.000000f) {
        aSetLevelTimer(qMathAddFloat(qUserVarValue(1), qUserVarValue(5)), 0);
      } else {
        aSetLevelTimer(qUserVarValue(1), 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 004: Train2 Matcen Produced a Train
    if (event_data->id == Matcen_indexes[3]) {
      aMatcenSetEnableState(0, Matcen_indexes[3]);
      aObjGhostSet(1, event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 1);
      if (qUserVarValue(2) > 9.000000f) {
        aSetLevelTimer(qMathAddFloat(qUserVarValue(2), qMathPercentage(1.750000f, qUserVarValue(5))), 1);
      } else {
        aSetLevelTimer(qUserVarValue(2), 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 008: Train3 Matcen Produced a Train
    if (event_data->id == Matcen_indexes[4]) {
      aMatcenSetEnableState(0, Matcen_indexes[4]);
      aObjGhostSet(1, event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 2);
      if (qUserVarValue(3) > 10.000000f) {
        aSetLevelTimer(qMathAddFloat(qUserVarValue(3), qMathPercentage(2.500000f, qUserVarValue(5))), 2);
      } else {
        aSetLevelTimer(qUserVarValue(3), 2);
      }

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 013: Train4 Matcen Produced a Train
    if (event_data->id == Matcen_indexes[5]) {
      aMatcenSetEnableState(0, Matcen_indexes[5]);
      aObjGhostSet(1, event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 3);
      if (qUserVarValue(4) > 10.000000f) {
        aSetLevelTimer(qMathAddFloat(qUserVarValue(4), qMathPercentage(3.500000f, qUserVarValue(5))), 3);
      } else {
        aSetLevelTimer(qUserVarValue(4), 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }

    // Script 051: Car Go Home 2
    if (event_data->id == Matcen_indexes[1]) {
      aAIGoalGotoObject(event_data->it_handle, Object_handles[34], 3, 4352, 6);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }

    // Script 049: Car Go Home
    if (event_data->id == Matcen_indexes[0]) {
      aAIGoalGotoObject(event_data->it_handle, Object_handles[35], 3, 4352, 6);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 054: After Intro Movie
    if ((ScriptActionCtr_054 < 1) && (1)) {
      aSoundPlaySteaming("VoxL04StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Data Cartridge PICKUP (Coop)
    if (qGoalCompleted(Goal_indexes[0]) == false) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 030: Data Cartridge INIT
    if (1) {
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
      aObjSpark(Object_handles[11], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[12], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[13], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[14], 5.000000f, 99999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 055: Data Cartridge ADD
    if ((ScriptActionCtr_055 < 1) && (qObjType(qPlayerClosest(data->me_handle, -1)) == 4)) {
      aAddObjectToInventory(data->me_handle, qPlayerClosest(data->me_handle, -1), 0);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 031: Data Cartridge USE
    if (1) {
      if (qObjGetDistance(Object_handles[15], event_data->it_handle) < 35.000000f) {
        aCinematicSimple(Path_indexes[6], Message_strings[2], Object_handles[15], 10.000000f, 1);
        aStoreObjectInPositionClipboard(Object_handles[16]);
        aMoveObjectToPositionClipboard(data->me_handle);
        aObjGhostSet(0, data->me_handle);
        aGoalCompleted(Goal_indexes[0], 1);
        aDoorLockUnlock(1, Door_handles[0]);
        aObjSpark(data->me_handle, 25.000000f, 14.000000f);
        aObjSpark(Object_handles[5], 15.000000f, 9.000000f);
        aObjSpark(Object_handles[6], 15.000000f, 8.000000f);
        aObjSpark(Object_handles[7], 15.000000f, 7.000000f);
        aObjSpark(Object_handles[8], 15.000000f, 6.000000f);
        aObjSpark(Object_handles[9], 15.000000f, 5.000000f);
        aObjSpark(Object_handles[10], 15.000000f, 4.000000f);
        aObjSpark(Object_handles[14], 20.000000f, 14.000000f);
        aObjSpark(Object_handles[13], 20.000000f, 14.000000f);
        aObjSpark(Object_handles[12], 20.000000f, 14.000000f);
        aObjSpark(Object_handles[11], 20.000000f, 14.000000f);
        aLightningCreate(Object_handles[17], data->me_handle, 10.000000f, 3.000000f, 1, Texture_indexes[0], 1.000000f,
                         3, 115, 115, 255, 0);
        aLightningCreate(Object_handles[18], data->me_handle, 10.000000f, 3.000000f, 1, Texture_indexes[0], 1.000000f,
                         3, 115, 115, 255, 0);
        aLightningCreate(Object_handles[19], data->me_handle, 10.000000f, 3.000000f, 1, Texture_indexes[0], 1.000000f,
                         3, 115, 115, 255, 0);
        aLightningCreate(Object_handles[20], data->me_handle, 10.000000f, 3.000000f, 1, Texture_indexes[0], 1.000000f,
                         3, 115, 115, 255, 0);
      } else {
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
        aShowHUDMessageObj(Message_strings[3], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08AE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 032: After Upload Movie
    if (1) {
      aShowHUDMessage(Message_strings[4]);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1213::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 039: Merc Died 2
    if (qObjExists(Object_handles[32]) == false) {
      aGoalCompleted(Goal_indexes[1], 1);
      aShowHUDMessage(Message_strings[6]);
      aSetLevelTimer(3.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_117D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 038: Merc Died 1
    if (qObjExists(Object_handles[33]) == false) {
      aGoalCompleted(Goal_indexes[1], 1);
      aShowHUDMessage(Message_strings[6]);
      aSetLevelTimer(3.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: Entered Suzuki
    if ((ScriptActionCtr_029 < 1) && (1)) {
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: Mercenary Intro
    if ((ScriptActionCtr_035 < 1) && ((ScriptActionCtr_032 > 0) == true)) {
      aMusicSetRegionAll(6);
      aGoalEnableDisable(1, Goal_indexes[1]);
      aObjGhostSet(0, Object_handles[33]);
      aObjGhostSet(0, Object_handles[32]);
      aAIGoalFollowPathSimple(Object_handles[33], Path_indexes[7], 1048832, 4, 3);
      aAIGoalFollowPathSimple(Object_handles[32], Path_indexes[8], 1048832, 5, 3);
      aCinematicSimple(Path_indexes[9], Message_strings[5], Object_handles[31], 5.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: MusicTrain
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Music CityFirst-2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Music CityFirst-1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: Music CitySecond-2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Music CitySecond-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: Music Sewer-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: Music Sewer-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: Music Suzuki
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
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
NEXT_ID		57

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:NextTrainShakerSlot
1:Train1Pattern
2:Train2Pattern
3:Train3Pattern
4:Train4Pattern
5:DifficultyAdjustment
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:TorchA
1:TorchB
2:TorchC
3:TorchD
4:SteamA
5:SteamB
6:SteamC
7:SteamD
8:SteamE
9:SecretGarden
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:Train1Delay
1:Train2Delay
2:Train3Delay
3:Train4Delay
4:TrainShaker
5:EndLevelTimer
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:Train1
1:Train2
2:Train3
3:Train4
4:Shaker1
5:Shaker2
6:Shaker3
7:Shaker4
8:Shaker5
9:Shaker6
10:Shaker7
11:Shaker8
12:Shaker9
13:Shaker10
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:Train1
1:Train2
2:Train3
3:Train4
4:Merc1
5:Merc2
6:Car1
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
PlazaEntrance
$$DOOR_LIST_END

$$OBJECT_LIST_START
DataCartridge
Train1
Train2
Train3
Train4
ElectricDown1
ElectricDown2
ElectricDown3
ElectricDown4
ElectricDown5
ElectricDown6
Electric1
Electric2
Electric3
Electric4
UploadMiddle
DataHolder
Upload4
Upload3
Upload2
Upload1
TorchA
TorchB
TorchC
TorchD
SteamA
SteamB
SteamC
SteamD
SteamE
CloakMerc
MercTarget
BPMain
BPSideKick
CarGoal2
CarGoal-1
GardenSpew-2
GardenSpew-1
$$OBJECT_LIST_END

$$ROOM_LIST_START
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EnterUpload
ExitUpload
MTrain
MCityFirst-2
MCityFirst
MCitySecond-2
MCitySecond-1
MSewer-2
MSewer-1
MSuzukiTower
$$TRIGGER_LIST_END

$$SOUND_LIST_START
Lev4TrainTest
PupC1
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffectAntiV
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
Train1
Train2
Train3
Train4
UploadWatch
Merc1Intro
Merc2Intro
MercWatch
CloakMerc1
EndCam
EndShip
$$PATH_LIST_END

$$MATCEN_LIST_START
Cars-1
Cars-2
TrainCen1
TrainCen2
TrainCen3
TrainCen4
$$MATCEN_LIST_END

$$GOAL_LIST_START
Upload the data to Suzuki
Defeat the PTMC Mercenaries
Give the Data to Suzuki and Return Safely
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL04StartLevel.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:33:Level Start Intro Cam
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
                        10:8:CinematicIntroCam:Text
                        10:1:0:0:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Level Start - Trains INIT
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:1.000000:value
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
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:0.000000:value
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Determine Difficult Adjustment (on Matcen Creations)
        $$CHILD_BLOCK_START
        01:2:0
        02:21
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
                                10:10:0:5:UserVar
                                10:6:4.000000:value
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
                                        10:10:0:5:UserVar
                                        10:6:2.000000:value
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
                                                10:10:0:5:UserVar
                                                10:6:0.800000:value
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
                                                        10:10:0:5:UserVar
                                                        10:6:0.400000:value
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
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Train1 Matcen Produced a Train
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qMathAddFloat:Time
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float1
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qUserVarValue:Float2
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Train1 Matcen Delay
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:2:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Train1 Next Delay Time
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:4.000000:value
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
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
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
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                10:6:5.000000:value
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
                                                                10:10:0:1:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:UserVar
                                                        10:6:2.000000:value
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
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Train2 Matcen Produced a Train
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:9.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qMathAddFloat:Time
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float1
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qMathPercentage:Float2
                                                $$CHILD_BLOCK_START
                                                10:9:1.750000:Percent
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:5:UserVar
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Train2 Matcen Delay
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:3:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Train2 Next Delay Time
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:3.000000:value
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
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        10:6:10.000000:value
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
                                                        10:10:0:2:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:10.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                10:6:4.000000:value
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
                                                                10:10:0:2:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:UserVar
                                                        10:6:2.000000:value
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
                                                                        10:10:0:2:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:2.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:2:UserVar
                                                                10:6:12.000000:value
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
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Train3 Matcen Produced a Train
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:2:SavedObjectSlot
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
                                10:6:10.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qMathAddFloat:Time
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float1
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qMathPercentage:Float2
                                                $$CHILD_BLOCK_START
                                                10:9:2.500000:Percent
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:5:UserVar
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Train3 Matcen Delay
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:4:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:2:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Train3 Next Delay Time
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                10:6:4.000000:value
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
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        10:6:15.000000:value
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
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserVar
                                                10:6:6.000000:value
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserVar
                                                10:6:1.000000:value
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Train4 Matcen Produced a Train
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:10.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qMathAddFloat:Time
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float1
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qMathPercentage:Float2
                                                $$CHILD_BLOCK_START
                                                10:9:3.500000:Percent
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:5:UserVar
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Train4 Matcen Delay
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:5:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Train4 Next Delay Time
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:4.000000:value
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
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        10:6:18.000000:value
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
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:18.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                10:6:5.000000:value
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
                                                                10:10:0:4:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        10:6:1.000000:value
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
                                                                        10:10:0:4:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:1.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:4:UserVar
                                                                10:6:16.000000:value
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
                                                                                10:10:0:4:UserVar
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:6:16.000000:Literal
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aUserVarSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:4:UserVar
                                                                        10:6:3.000000:value
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
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Train Any Done (so delete IT)
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
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:1:0:GoalID
                                07:1:0
                                10:10:0:3:GoalID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Train Shakers Add 4
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:10:0:4:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:2.000000:value
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
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:5:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        10:6:3.000000:value
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
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:6:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:4.000000:value
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
                                                        07:1:0
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aObjSaveHandle
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:UserVar
                                                        10:6:5.000000:value
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
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aObjSaveHandle
                                                                $$CHILD_BLOCK_START
                                                                06:qObjSavedHandle:Object
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:3:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                10:10:0:8:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:UserVar
                                                                10:6:6.000000:value
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
                                                                        07:1:0
                                                                        10:6:6.000000:Literal
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aObjSaveHandle
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjSavedHandle:Object
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:3:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        10:10:0:9:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserVarSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:UserVar
                                                                        10:6:7.000000:value
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
                                                                                07:1:0
                                                                                10:6:7.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aObjSaveHandle
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:3:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                10:10:0:10:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        08:aUserVarSet
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:0:UserVar
                                                                                10:6:8.000000:value
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
                                                                                        07:1:0
                                                                                        10:6:8.000000:Literal
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        04:1:0:0
                                                                                $$CHILD_BLOCK_START
                                                                                08:aObjSaveHandle
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjSavedHandle:Object
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:3:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        10:10:0:11:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                08:aUserVarSet
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:0:UserVar
                                                                                        10:6:9.000000:value
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
                                                                                                07:1:0
                                                                                                10:6:9.000000:Literal
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                04:1:0:0
                                                                                        $$CHILD_BLOCK_START
                                                                                        08:aObjSaveHandle
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:3:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                10:10:0:12:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        08:aUserVarSet
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:0:UserVar
                                                                                                10:6:10.000000:value
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
                                                                                                        07:1:0
                                                                                                        10:6:10.000000:Literal
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        04:1:0:0
                                                                                                $$CHILD_BLOCK_START
                                                                                                08:aObjSaveHandle
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjSavedHandle:Object
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                10:10:0:3:SavedObjectSlot
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        10:10:0:13:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                08:aUserVarSet
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:0:UserVar
                                                                                                        10:6:1.000000:value
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Train Shakers Add 3
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:10:0:4:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:2.000000:value
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
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:5:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        10:6:3.000000:value
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
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:6:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:4.000000:value
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
                                                        07:1:0
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aObjSaveHandle
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:2:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:UserVar
                                                        10:6:5.000000:value
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
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aObjSaveHandle
                                                                $$CHILD_BLOCK_START
                                                                06:qObjSavedHandle:Object
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:6:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                10:10:0:8:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:UserVar
                                                                10:6:6.000000:value
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
                                                                        07:1:0
                                                                        10:6:6.000000:Literal
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aObjSaveHandle
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjSavedHandle:Object
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:2:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        10:10:0:9:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserVarSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:UserVar
                                                                        10:6:7.000000:value
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
                                                                                07:1:0
                                                                                10:6:7.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aObjSaveHandle
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:2:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                10:10:0:10:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        08:aUserVarSet
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:0:UserVar
                                                                                10:6:8.000000:value
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
                                                                                        07:1:0
                                                                                        10:6:8.000000:Literal
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        04:1:0:0
                                                                                $$CHILD_BLOCK_START
                                                                                08:aObjSaveHandle
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjSavedHandle:Object
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:2:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        10:10:0:11:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                08:aUserVarSet
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:0:UserVar
                                                                                        10:6:9.000000:value
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
                                                                                                07:1:0
                                                                                                10:6:9.000000:Literal
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                04:1:0:0
                                                                                        $$CHILD_BLOCK_START
                                                                                        08:aObjSaveHandle
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:2:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                10:10:0:12:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        08:aUserVarSet
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:0:UserVar
                                                                                                10:6:10.000000:value
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
                                                                                                        07:1:0
                                                                                                        10:6:10.000000:Literal
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        04:1:0:0
                                                                                                $$CHILD_BLOCK_START
                                                                                                08:aObjSaveHandle
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjSavedHandle:Object
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                10:10:0:2:SavedObjectSlot
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        10:10:0:13:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                08:aUserVarSet
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:0:UserVar
                                                                                                        10:6:1.000000:value
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Train Shakers Add 2
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:10:0:4:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:2.000000:value
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
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:5:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        10:6:3.000000:value
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
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:6:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:4.000000:value
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
                                                        07:1:0
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aObjSaveHandle
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:UserVar
                                                        10:6:5.000000:value
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
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aObjSaveHandle
                                                                $$CHILD_BLOCK_START
                                                                06:qObjSavedHandle:Object
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:1:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                10:10:0:8:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:UserVar
                                                                10:6:6.000000:value
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
                                                                        07:1:0
                                                                        10:6:6.000000:Literal
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aObjSaveHandle
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjSavedHandle:Object
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:1:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        10:10:0:9:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserVarSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:UserVar
                                                                        10:6:7.000000:value
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
                                                                                07:1:0
                                                                                10:6:7.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aObjSaveHandle
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:1:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                10:10:0:10:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        08:aUserVarSet
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:0:UserVar
                                                                                10:6:8.000000:value
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
                                                                                        07:1:0
                                                                                        10:6:8.000000:Literal
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        04:1:0:0
                                                                                $$CHILD_BLOCK_START
                                                                                08:aObjSaveHandle
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjSavedHandle:Object
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:1:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        10:10:0:11:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                08:aUserVarSet
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:0:UserVar
                                                                                        10:6:9.000000:value
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
                                                                                                07:1:0
                                                                                                10:6:9.000000:Literal
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                04:1:0:0
                                                                                        $$CHILD_BLOCK_START
                                                                                        08:aObjSaveHandle
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:1:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                10:10:0:12:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        08:aUserVarSet
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:0:UserVar
                                                                                                10:6:10.000000:value
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
                                                                                                        07:1:0
                                                                                                        10:6:10.000000:Literal
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        04:1:0:0
                                                                                                $$CHILD_BLOCK_START
                                                                                                08:aObjSaveHandle
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjSavedHandle:Object
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                10:10:0:1:SavedObjectSlot
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        10:10:0:13:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                08:aUserVarSet
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:0:UserVar
                                                                                                        10:6:1.000000:value
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Train Shakers Add 1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:10:0:4:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:2.000000:value
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
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:5:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        10:6:3.000000:value
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
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:6:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:4.000000:value
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
                                                        07:1:0
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aObjSaveHandle
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:UserVar
                                                        10:6:5.000000:value
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
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aObjSaveHandle
                                                                $$CHILD_BLOCK_START
                                                                06:qObjSavedHandle:Object
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                10:10:0:8:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:UserVar
                                                                10:6:6.000000:value
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
                                                                        07:1:0
                                                                        10:6:6.000000:Literal
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aObjSaveHandle
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjSavedHandle:Object
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:0:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        10:10:0:9:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserVarSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:UserVar
                                                                        10:6:7.000000:value
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
                                                                                07:1:0
                                                                                10:6:7.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aObjSaveHandle
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:0:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                10:10:0:10:SavedObjectSlot
                                                                                $$CHILD_BLOCK_END
                                                                        08:aUserVarSet
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:0:UserVar
                                                                                10:6:8.000000:value
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
                                                                                        07:1:0
                                                                                        10:6:8.000000:Literal
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        04:1:0:0
                                                                                $$CHILD_BLOCK_START
                                                                                08:aObjSaveHandle
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjSavedHandle:Object
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:0:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        10:10:0:11:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                08:aUserVarSet
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:0:UserVar
                                                                                        10:6:9.000000:value
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
                                                                                                07:1:0
                                                                                                10:6:9.000000:Literal
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                04:1:0:0
                                                                                        $$CHILD_BLOCK_START
                                                                                        08:aObjSaveHandle
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:0:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                10:10:0:12:SavedObjectSlot
                                                                                                $$CHILD_BLOCK_END
                                                                                        08:aUserVarSet
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:10:0:0:UserVar
                                                                                                10:6:10.000000:value
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
                                                                                                        07:1:0
                                                                                                        10:6:10.000000:Literal
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        04:1:0:0
                                                                                                $$CHILD_BLOCK_START
                                                                                                08:aObjSaveHandle
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjSavedHandle:Object
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                10:10:0:0:SavedObjectSlot
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        10:10:0:13:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                08:aUserVarSet
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:0:UserVar
                                                                                                        10:6:1.000000:value
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Train Shaker Timer Recycle
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Train Shaker 10
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:13:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Train Shaker 9
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Train Shaker 8
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Train Shaker 7
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Train Shaker 6
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Train Shaker 5
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Train Shaker 4
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Train Shaker 3
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Train Shaker 2
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Train Shaker 1
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:90:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:300.000000:Distance
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:40.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Entered Suzuki
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PutTheCartridge:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Data Cartridge ADD
        $$CHILD_BLOCK_START
        01:1:0
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
                                        10:10:0:-1:UserVar
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
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Data Cartridge INIT
        $$CHILD_BLOCK_START
        01:1:0
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Data Cartridge PICKUP (Coop)
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qGoalCompleted:Bool
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
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
00:31:Data Cartridge USE
        $$CHILD_BLOCK_START
        01:1:0
        02:25
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
                                06:qObjGetDistance:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:15:Object1
                                        10:1:1:-1:Object2
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:35.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:6:CameraPath
                                10:8:CinematicDataCart:Text
                                10:1:0:15:Target
                                10:6:10.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:16:Object
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
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:25.000000:SparkRate
                                10:6:14.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:6:15.000000:SparkRate
                                10:6:9.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:6:15.000000:SparkRate
                                10:6:8.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:6:15.000000:SparkRate
                                10:6:7.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                10:6:15.000000:SparkRate
                                10:6:6.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:9:Object
                                10:6:15.000000:SparkRate
                                10:6:5.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                10:6:15.000000:SparkRate
                                10:6:4.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:14:Object
                                10:6:20.000000:SparkRate
                                10:6:14.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:13:Object
                                10:6:20.000000:SparkRate
                                10:6:14.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:12:Object
                                10:6:20.000000:SparkRate
                                10:6:14.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:11:Object
                                10:6:20.000000:SparkRate
                                10:6:14.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:17:Object1
                                10:1:2:-1:Object2
                                10:6:10.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:1.000000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:115:Red
                                10:4:115:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object1
                                10:1:2:-1:Object2
                                10:6:10.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:1.000000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:115:Red
                                10:4:115:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object1
                                10:1:2:-1:Object2
                                10:6:10.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:1.000000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:115:Red
                                10:4:115:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object1
                                10:1:2:-1:Object2
                                10:6:10.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:0:Texture
                                10:6:1.000000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:115:Red
                                10:4:115:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
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
                                10:8:CartridgeError:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:After Upload Movie
        $$CHILD_BLOCK_START
        01:1:15
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GetOut:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Sean's Flaming Torches!
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
                        10:1:0:21:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.250000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.250000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.250000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.250000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:3:SpewHandle
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Mercenary INIT
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
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Mercenary Intro
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:32:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:6:Region
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:1:LevelGoal
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:16:7:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:4:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:16:8:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:5:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:9:CameraPath
                        10:8:CinematicAmbush:Text
                        10:1:0:31:Target
                        10:6:5.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Merc Died 2
        $$CHILD_BLOCK_START
        01:1:33
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:32:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BPDefeated:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Merc Died 1
        $$CHILD_BLOCK_START
        01:1:32
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjExists:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:33:Object
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BPDefeated:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:EndLevel Cam
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:5:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:16:10:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:11:CameraPath
                        10:16:12:PlayerPath
                        10:6:10.000000:Time
                        10:8:CinematicEndCam:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:MusicStart (Train)
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
00:41:MusicTrain
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
00:43:Music CityFirst-2
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
00:42:Music CityFirst-1
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
00:45:Music CitySecond-2
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
00:44:Music CitySecond-1
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
00:47:Music Sewer-2
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
00:46:Music Sewer-1
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Music Suzuki
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Car Go Home 2
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:4:Matcen
                        07:1:0
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:1:0:34:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Car Go Home
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:4:Matcen
                        07:1:0
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:1:0:35:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:CarDestroy
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Secret Garden Spew
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
                        10:1:0:36:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:After Intro Movie
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
