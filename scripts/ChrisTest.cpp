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
// Filename:	Train03.cpp
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

#define ID_CUSTOM_OBJECT_1004 0x001

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

class CustomObjectScript_1004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_003 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_003 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
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

#define NUM_OBJECT_NAMES 1
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Train1Position"};
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

#define NUM_PATH_NAMES 1
static const char *const Path_names[NUM_PATH_NAMES] = {"Train1"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 1
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Train 1"};
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
    strcpy(filename, "Train03.msg");
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
  case ID_CUSTOM_OBJECT_1004:
    return new CustomObjectScript_1004;
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
  case ID_CUSTOM_OBJECT_1004:
    delete ((CustomObjectScript_1004 *)ptr);
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
  case ID_CUSTOM_OBJECT_1004:
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
  static int cust_handle_list[1];
  static int cust_id_list[1] = {ID_CUSTOM_OBJECT_1004};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 1;
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

    // Script 000: Level Start - Misc
    if (1 == false) {
      aObjGhostSet(1, Object_handles[0]);
      aMatcenSetState(1, Matcen_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 002: Train1 Done
    if (event_data->goal_uid == 0) {
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aAIGoalFollowPath(Object_handles[0], Path_indexes[0], 1, 2, 1, 3, 131328, 0);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 001: Train1 Matcen Produced a Train
    if (1 == false) {
      aStoreObjectInPositionClipboard(Object_handles[0]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aAIGoalFollowPath(event_data->it_handle, Path_indexes[0], 1, 2, 1, 3, 131328, 0);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 003: Script Description Goes Here
    if (1) {
      aStoreObjectInPositionClipboard(Object_handles[0]);
      aMoveObjectToPositionClipboard(Object_handles[0]);
      aAIGoalFollowPath(Object_handles[0], Path_indexes[0], 1, 2, 1, 3, 131328, 0);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
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
NEXT_ID		4

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
0:Train1Done
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
Train1Position
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
Train1
$$PATH_LIST_END

$$MATCEN_LIST_START
Train 1
$$MATCEN_LIST_END

$$GOAL_LIST_START
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Level Start - Misc
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Train1 Matcen Produced a Train
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:0:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:131328:AIGoalFlags
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Train1 Done
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
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:0:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:131328:AIGoalFlags
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Script Description Goes Here
        $$CHILD_BLOCK_START
        01:1:0
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:0:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:131328:AIGoalFlags
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
