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
// Filename:	Invasion.cpp
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

#define ID_CUSTOM_OBJECT_0810 0x001
#define ID_CUSTOM_OBJECT_0811 0x002
#define ID_CUSTOM_OBJECT_0812 0x003
#define ID_CUSTOM_OBJECT_0813 0x004
#define ID_CUSTOM_OBJECT_0876 0x005
#define ID_CUSTOM_OBJECT_0875 0x006
#define ID_CUSTOM_OBJECT_0859 0x007
#define ID_CUSTOM_OBJECT_085A 0x008

#define ID_TRIGGER_0009 0x009
#define ID_TRIGGER_0008 0x00a
#define ID_TRIGGER_0007 0x00b
#define ID_TRIGGER_0006 0x00c
#define ID_TRIGGER_0003 0x00d
#define ID_TRIGGER_0002 0x00e
#define ID_TRIGGER_0001 0x00f
#define ID_TRIGGER_0000 0x010
#define ID_TRIGGER_000B 0x011
#define ID_TRIGGER_000A 0x012
#define ID_TRIGGER_0005 0x013
#define ID_TRIGGER_0004 0x014

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

class CustomObjectScript_0810 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0811 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0812 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0813 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0876 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0875 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0859 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_085A : public BaseScript {
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

class TriggerScript_0001 : public BaseScript {
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

class TriggerScript_000A : public BaseScript {
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

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_023 = 0;
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
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_023 = 0;
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
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
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
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here

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

#define NUM_OBJECT_NAMES 10
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "BlueVirusSpark", "RedVirusSpark", "RSwitch-12", "RSwitch-11", "RSwitch-22",
    "RSwitch-21",     "BSwitch-22",    "BSwitch-21", "BSwitch-12", "BSwitch-11"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 10
static const char *const Room_names[NUM_ROOM_NAMES] = {"BlueSpark", "BlueAccess-1", "RedSpark",  "RedAccess-1",
                                                       "Wind-2",    "Wind-1",       "RZapper-1", "RZapper-2",
                                                       "BZapper-2", "BZapper-1"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 12
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {"BStatic-4", "BStatic-3", "BStatic-2", "BStatic-1",
                                                             "Static-4",  "Static-3",  "Static-2",  "Static-1",
                                                             "BZapper-2", "BZapper-1", "Zapper-2",  "Zapper-1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 5
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbPlasma21", "Lightning", "expMissilePlasmic1",
                                                         "AmbSwitch31", "AmbSwitch11"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 0
static const char **Path_names = NULL;
static int *Path_indexes = NULL;

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 0
static const char **Goal_names = NULL;
static int *Goal_indexes = NULL;

#define NUM_MESSAGE_NAMES 0
static const char **Message_names = NULL;
static const char **Message_strings = NULL;

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
    strcpy(filename, "Invasion.msg");
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
  case ID_CUSTOM_OBJECT_0810:
    return new CustomObjectScript_0810;
    break;
  case ID_CUSTOM_OBJECT_0811:
    return new CustomObjectScript_0811;
    break;
  case ID_CUSTOM_OBJECT_0812:
    return new CustomObjectScript_0812;
    break;
  case ID_CUSTOM_OBJECT_0813:
    return new CustomObjectScript_0813;
    break;
  case ID_CUSTOM_OBJECT_0876:
    return new CustomObjectScript_0876;
    break;
  case ID_CUSTOM_OBJECT_0875:
    return new CustomObjectScript_0875;
    break;
  case ID_CUSTOM_OBJECT_0859:
    return new CustomObjectScript_0859;
    break;
  case ID_CUSTOM_OBJECT_085A:
    return new CustomObjectScript_085A;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
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
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
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
  case ID_CUSTOM_OBJECT_0810:
    delete ((CustomObjectScript_0810 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0811:
    delete ((CustomObjectScript_0811 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0812:
    delete ((CustomObjectScript_0812 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0813:
    delete ((CustomObjectScript_0813 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0876:
    delete ((CustomObjectScript_0876 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0875:
    delete ((CustomObjectScript_0875 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0859:
    delete ((CustomObjectScript_0859 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_085A:
    delete ((CustomObjectScript_085A *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
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
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
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
  case ID_CUSTOM_OBJECT_0810:
  case ID_CUSTOM_OBJECT_0811:
  case ID_CUSTOM_OBJECT_0812:
  case ID_CUSTOM_OBJECT_0813:
  case ID_CUSTOM_OBJECT_0876:
  case ID_CUSTOM_OBJECT_0875:
  case ID_CUSTOM_OBJECT_0859:
  case ID_CUSTOM_OBJECT_085A:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
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
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0004;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[8];
  static int cust_id_list[8] = {ID_CUSTOM_OBJECT_0810, ID_CUSTOM_OBJECT_0811, ID_CUSTOM_OBJECT_0812,
                                ID_CUSTOM_OBJECT_0813, ID_CUSTOM_OBJECT_0876, ID_CUSTOM_OBJECT_0875,
                                ID_CUSTOM_OBJECT_0859, ID_CUSTOM_OBJECT_085A};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[2];
  cust_handle_list[1] = Object_handles[3];
  cust_handle_list[2] = Object_handles[4];
  cust_handle_list[3] = Object_handles[5];
  cust_handle_list[4] = Object_handles[6];
  cust_handle_list[5] = Object_handles[7];
  cust_handle_list[6] = Object_handles[8];
  cust_handle_list[7] = Object_handles[9];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 8;
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

    // Script 002: BlueUnSpark
    if ((qUserFlag(0) == true) && (qRoomHasPlayer(Room_indexes[0]) == false)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[0], 1.000000f);
      aObjSpark(Object_handles[0], 10.000000f, 999999.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[1]);
      aRoomSetWind(Room_indexes[1], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aUserFlagSet(0, 0);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 000: BlueSpark
    if ((qUserFlag(0) == false) && (qRoomHasPlayer(Room_indexes[0]) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[0], 1.000000f);
      aObjSpark(Object_handles[0], 50.000000f, 999999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[1]);
      aRoomSetWind(Room_indexes[1], 0.000000f, qUserVarValue(0), 0.000000f, -1.000000f);
      aUserFlagSet(0, 1);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 004: RedUnSpark
    if ((qUserFlag(1) == true) && (qRoomHasPlayer(Room_indexes[2]) == false)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[1], 1.000000f);
      aObjSpark(Object_handles[1], 10.000000f, 999999.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[3]);
      aRoomSetWind(Room_indexes[3], 0.000000f, qUserVarValue(0), 0.000000f, -1.000000f);
      aUserFlagSet(1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 003: RedSpark
    if ((qUserFlag(1) == false) && (qRoomHasPlayer(Room_indexes[2]) == true)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[1], 1.000000f);
      aObjSpark(Object_handles[1], 50.000000f, 999999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[3]);
      aRoomSetWind(Room_indexes[3], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aUserFlagSet(1, 1);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 001: SetDefaultWinds
    if (1) {
      aObjGhostSet(1, Object_handles[1]);
      aObjGhostSet(1, Object_handles[0]);
      aObjSpark(Object_handles[0], 10.000000f, 999999.000000f);
      aObjSpark(Object_handles[1], 10.000000f, 999999.000000f);
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);
      aUserVarSet(0, 30.000000f);
      aRoomSetWind(Room_indexes[1], 0.000000f, qUserVarValue(0), 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, qUserVarValue(0), 0.000000f, -1.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, qUserVarValue(0), 0.000000f, -0.700000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, qUserVarValue(0), 0.000000f, 0.700000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0810::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Switch-12 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[3]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[6], 0.000000f, qUserVarValue(0), 0.000000f, -0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 016: Switch-12 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 014: Switch-12 Off
    if (1) {
      aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[6]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0811::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Switch-11 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[2]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[6], 0.000000f, qUserVarValue(0), 0.000000f, -0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 015: Switch-11 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 013: Switch-11 Off
    if (1) {
      aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[6]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0812::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Switch-22 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[5]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[7], 0.000000f, qUserVarValue(0), 0.000000f, -0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[7]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 026: Switch-22 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 027: Switch-22 Off
    if (1) {
      aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[7]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0813::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Switch-21 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[4]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[7], 0.000000f, qUserVarValue(0), 0.000000f, -0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[7]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 023: Switch-21 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 024: Switch-21 Off
    if (1) {
      aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[7]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0876::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: BSwitch-22 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[7]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[8], 0.000000f, qUserVarValue(0), 0.000000f, 0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 032: BSwitch-22 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 036: BSwitch-22 Off
    if (1) {
      aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[8]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0875::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: BSwitch-21 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[6]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[8], 0.000000f, qUserVarValue(0), 0.000000f, 0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 031: BSwitch-21 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 035: BSwitch-21 Off
    if (1) {
      aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[8]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0859::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: BSwitch-12 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[9]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[9], 0.000000f, qUserVarValue(0), 0.000000f, 0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[9]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 030: BSwitch-12 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 034: BSwitch-12 Off
    if (1) {
      aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[9]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_085A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: BSwitch-11 On
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 6.000000f)) {
      aSetObjectTimer(data->me_handle, 8.000000f, -1);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 2.000000f, 0);
      if (qObjAnimFrame(Object_handles[8]) <= 3.000000f) {
        aRoomSetWind(Room_indexes[9], 0.000000f, qUserVarValue(0), 0.000000f, 0.300000f);
        aRoomSetLightingFlicker(1, Room_indexes[9]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 029: BSwitch-11 Initialize
    if (1) {
      aObjPlayAnim(data->me_handle, 3, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 033: BSwitch-11 Off
    if (1) {
      aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetLightingFlicker(0, Room_indexes[9]);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: BStatic-4
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: BStatic-3
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: BStatic-2
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: BStatic-1
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Static-4
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Static-3
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Static-2
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Static-1
    if (1) {
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aObjSpark(event_data->it_handle, 50.000000f, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: BZapper-2
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMiscShakeArea(event_data->it_handle, 70.000000f, 200.000000f);
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aObjDestroy(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: BZapper-1
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMiscShakeArea(event_data->it_handle, 70.000000f, 200.000000f);
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aObjDestroy(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Zapper-2
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMiscShakeArea(event_data->it_handle, 70.000000f, 200.000000f);
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aObjDestroy(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Zapper-1
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMiscShakeArea(event_data->it_handle, 70.000000f, 200.000000f);
      aSoundPlayObject(Sound_indexes[2], event_data->it_handle, 1.000000f);
      aObjDestroy(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
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
NEXT_ID		41

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:WindDefault
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:BlueSparked
1:RedSparked
2:RSwitch11
3:RSwitch12
4:RSwitch21
5:RSwitch22
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:Init
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
BlueVirusSpark
RedVirusSpark
RSwitch-12
RSwitch-11
RSwitch-22
RSwitch-21
BSwitch-22
BSwitch-21
BSwitch-12
BSwitch-11
$$OBJECT_LIST_END

$$ROOM_LIST_START
BlueSpark
BlueAccess-1
RedSpark
RedAccess-1
Wind-2
Wind-1
RZapper-1
RZapper-2
BZapper-2
BZapper-1
$$ROOM_LIST_END

$$TRIGGER_LIST_START
BStatic-4
BStatic-3
BStatic-2
BStatic-1
Static-4
Static-3
Static-2
Static-1
BZapper-2
BZapper-1
Zapper-2
Zapper-1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbPlasma21
Lightning
expMissilePlasmic1
AmbSwitch31
AmbSwitch11
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:2:BlueUnSpark
        $$CHILD_BLOCK_START
        01:2:0
        02:5
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:10.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:BlueSpark
        $$CHILD_BLOCK_START
        01:2:0
        02:5
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
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:50.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:-1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:RedUnSpark
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:10.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:3:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:-1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:RedSpark
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
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
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:50.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:3:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:SetDefaultWinds
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
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:10.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:10.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:30.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
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
                        10:2:3:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:-1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:-0.700000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        06:qUserVarValue:Y
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:6:0.000000:Z
                        10:6:0.700000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:BStatic-4
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:BStatic-3
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:BStatic-2
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:BStatic-1
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Static-4
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Static-3
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Static-2
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Static-1
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
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:BZapper-2
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:70.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:BZapper-1
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:70.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Zapper-2
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:70.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Zapper-1
        $$CHILD_BLOCK_START
        01:0:11
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:70.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Switch-12 On
        $$CHILD_BLOCK_START
        01:1:2
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
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:-0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:6:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Switch-11 On
        $$CHILD_BLOCK_START
        01:1:3
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
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:2:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:-0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:6:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Switch-12 Off
        $$CHILD_BLOCK_START
        01:1:2
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:6:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Switch-11 Off
        $$CHILD_BLOCK_START
        01:1:3
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:6:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Switch-12 Initialize
        $$CHILD_BLOCK_START
        01:1:2
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Switch-11 Initialize
        $$CHILD_BLOCK_START
        01:1:3
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Switch-22 On
        $$CHILD_BLOCK_START
        01:1:4
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
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:5:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:-0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:7:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Switch-21 On
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:4:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:-0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:7:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Switch-22 Off
        $$CHILD_BLOCK_START
        01:1:4
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:7:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Switch-21 Off
        $$CHILD_BLOCK_START
        01:1:5
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:7:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Switch-22 Initialize
        $$CHILD_BLOCK_START
        01:1:4
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Switch-21 Initialize
        $$CHILD_BLOCK_START
        01:1:5
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:BSwitch-22 On
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:7:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:8:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:BSwitch-21 On
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:8:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:BSwitch-12 On
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:9:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:9:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:BSwitch-11 On
        $$CHILD_BLOCK_START
        01:1:9
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
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:8.000000:Time
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
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:8:Object
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:9:Room
                                10:6:0.000000:X
                                06:qUserVarValue:Y
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:Z
                                10:6:0.300000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:9:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:BSwitch-22 Off
        $$CHILD_BLOCK_START
        01:1:6
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:8:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:BSwitch-21 Off
        $$CHILD_BLOCK_START
        01:1:7
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:8:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:BSwitch-12 Off
        $$CHILD_BLOCK_START
        01:1:8
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:9:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:BSwitch-11 Off
        $$CHILD_BLOCK_START
        01:1:9
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:9:Room
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:BSwitch-22 Initialize
        $$CHILD_BLOCK_START
        01:1:6
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:BSwitch-21 Initialize
        $$CHILD_BLOCK_START
        01:1:7
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:BSwitch-12 Initialize
        $$CHILD_BLOCK_START
        01:1:8
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:BSwitch-11 Initialize
        $$CHILD_BLOCK_START
        01:1:9
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
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
