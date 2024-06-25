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
// Filename:	SewerRat.cpp
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

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_001 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
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

#define NUM_OBJECT_NAMES 27
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "FallC10", "DamB10", "3FallsA3", "3FallsB3", "3FallsC3", "MainC3", "MainE3", "BowlFat3", "DamFat4",
    "RingA2",  "RingB2", "RingE2",   "RingF3",   "MainB5",   "MainA5", "MainD5", "RingC5",   "RingD5",
    "RingG5",  "RingH5", "BowlA5",   "bowlB7",   "BowlE4",   "BowlD1", "BowlC1", "BowlF2",   "BowlG2"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 0
static const char **Room_names = NULL;
static int *Room_indexes = NULL;

#define NUM_TRIGGER_NAMES 0
static const char **Trigger_names = NULL;
static int *Trigger_indexes = NULL;
static int *Trigger_faces = NULL;
static int *Trigger_rooms = NULL;

#define NUM_SOUND_NAMES 0
static const char **Sound_names = NULL;
static int *Sound_indexes = NULL;

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 0
static const char **Path_names = NULL;
static int *Path_indexes = NULL;

#define NUM_MATCEN_NAMES 6
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Matcen 1", "Matcen 2", "Matcen 3",
                                                           "Matcen 4", "Matcen 5", "Matcen 6"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

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
    strcpy(filename, "SewerRat.msg");
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
int STDCALL GetTriggerScriptID(int trigger_room, int trigger_face) { return -1; }

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int *cust_handle_list = NULL;
  static int *cust_id_list = NULL;

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 0;
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

    // Script 000: Start Spewers
    if (1) {
      aTurnOnSpew(Object_handles[0], -1, 7, 0.000000f, 0.000000f, 65536, 0, 7.000000f, 0.500000f, -1.000000f,
                  19.000000f, 24.000000f, 1, -1);
      aTurnOnSpew(Object_handles[1], -1, 7, 0.000000f, 0.000000f, 65536, 0, 5.000000f, 0.500000f, -1.000000f,
                  12.000000f, 20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[2], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.200000f, -1.000000f, 2.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[3], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.200000f, -1.000000f, 2.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[4], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.200000f, -1.000000f, 2.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[5], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.200000f, -1.000000f, 2.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[6], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.200000f, -1.000000f, 2.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[7], -1, 7, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.500000f, -1.000000f, 9.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[8], -1, 7, 0.000000f, 0.000000f, 65536, 0, 5.000000f, 0.100000f, -1.000000f, 9.000000f,
                  9.000000f, 1, -1);
      aTurnOnSpew(Object_handles[9], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.200000f, -1.000000f, 2.000000f,
                  8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[10], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[11], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[12], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[13], -1, 7, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[14], -1, 7, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[15], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.200000f, 0.200000f, -1.000000f,
                  2.500000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[16], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.800000f, 0.200000f, -1.000000f,
                  2.500000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[17], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.800000f, 0.200000f, -1.000000f,
                  2.500000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[18], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.800000f, 0.200000f, -1.000000f,
                  2.500000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[19], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.800000f, 0.200000f, -1.000000f,
                  2.500000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[20], -1, 7, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.200000f, -1.000000f,
                  2.500000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[21], -1, 7, 0.000000f, 0.000000f, 65536, 0, 6.000000f, 0.200000f, -1.000000f,
                  2.200000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[22], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.500000f, 0.200000f, -1.000000f,
                  4.200000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[23], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.900000f, 0.200000f, -1.000000f,
                  2.800000f, 4.000000f, 1, -1);
      aTurnOnSpew(Object_handles[24], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.800000f, 0.200000f, -1.000000f,
                  2.800000f, 3.000000f, 1, -1);
      aTurnOnSpew(Object_handles[25], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.700000f, 0.200000f, -1.000000f,
                  2.800000f, 4.000000f, 1, -1);
      aTurnOnSpew(Object_handles[26], -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.200000f, -1.000000f,
                  2.400000f, 4.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 001: Start Matcens
    if (1) {
      aMatcenSetState(1, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[1]);
      aMatcenSetState(1, Matcen_indexes[2]);
      aMatcenSetState(1, Matcen_indexes[3]);
      aMatcenSetState(1, Matcen_indexes[4]);
      aMatcenSetState(1, Matcen_indexes[5]);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
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
NEXT_ID		2

// UserType value blocks
$$UTYPE_VALS_START UserVar
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
FallC10
DamB10
3FallsA3
3FallsB3
3FallsC3
MainC3
MainE3
BowlFat3
DamFat4
RingA2
RingB2
RingE2
RingF3
MainB5
MainA5
MainD5
RingC5
RingD5
RingG5
RingH5
BowlA5
bowlB7
BowlE4
BowlD1
BowlC1
BowlF2
BowlG2
$$OBJECT_LIST_END

$$ROOM_LIST_START
$$ROOM_LIST_END

$$TRIGGER_LIST_START
$$TRIGGER_LIST_END

$$SOUND_LIST_START
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
$$PATH_LIST_END

$$MATCEN_LIST_START
Matcen 1
Matcen 2
Matcen 3
Matcen 4
Matcen 5
Matcen 6
$$MATCEN_LIST_END

$$GOAL_LIST_START
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Start Spewers
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
                        10:1:0:0:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:7.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:19.000000:BlobSize
                        10:6:24.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:5.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:9.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:5.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:9.000000:BlobSize
                        10:6:9.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.200000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:3.800000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:3.800000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:3.800000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:3.800000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:4.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:6.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.200000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:2.500000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.200000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:1.900000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.800000:BlobSize
                        10:6:4.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:1.800000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.800000:BlobSize
                        10:6:3.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:2.700000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.800000:BlobSize
                        10:6:4.000000:BlobSpeed
                        10:5:1:Randomize
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
                        10:6:2.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.400000:BlobSize
                        10:6:4.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Start Matcens
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

$$SCRIPT_BLOCK_END
*********************************************************/
