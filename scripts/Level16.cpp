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
// Filename:	Level16.cpp
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

#define ID_CUSTOM_OBJECT_4010 0x001
#define ID_CUSTOM_OBJECT_0804 0x002

#define ID_TRIGGER_0001 0x003
#define ID_TRIGGER_0002 0x004
#define ID_TRIGGER_0004 0x005
#define ID_TRIGGER_0003 0x006

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

class CustomObjectScript_4010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0804 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_013 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_013 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
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

#define NUM_OBJECT_NAMES 2
static const char *const Object_names[NUM_OBJECT_NAMES] = {"SwitchTube1", "EntranceDoor"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 41
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "EyeballMatcen", "Tube310",    "StartWind",    "Conn03E",    "Conn03Hub",  "Conn03W",      "Conn02E",
    "Conn02Hub",     "Conn02W",    "Conn01E",      "Conn01Hub",  "Conn01W",    "AltConn01W",   "AltConn01Hub",
    "AltConn01E",    "AltConn02W", "AltConn02Hub", "AltConn02E", "AltConn03E", "AltConn03Hub", "AltConn03W",
    "EndWind",       "Curve01",    "Curve02",      "Curve03",    "Curve04",    "Curve05",      "Curve06",
    "Curve07",       "Curve08",    "Curve09",      "Tube102",    "Tube202",    "Tube302",      "ControlRoom",
    "Tube101",       "Tube103",    "Tube104",      "Tube105",    "Tube106",    "AltConn01N"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 4
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {"WindTrigger", "MainRoom1", "MainRoom3", "MainRoom2"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 2
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSwitch31", "DoorIsLocked"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 2
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"Reddataup", "Ready1"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 0
static const char **Path_names = NULL;
static int *Path_indexes = NULL;

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 1
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Explore the hidden base"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 8
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "IntroHUDmessage", "IntroBriefingMessage", "Area1Active", "EntranceDoorMessage", "Area1", "Area3",
    "Area2",           "EndLevelMessage"};
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
    strcpy(filename, "Level16.msg");
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
  case ID_CUSTOM_OBJECT_4010:
    return new CustomObjectScript_4010;
    break;
  case ID_CUSTOM_OBJECT_0804:
    return new CustomObjectScript_0804;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
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
  case ID_CUSTOM_OBJECT_4010:
    delete ((CustomObjectScript_4010 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0804:
    delete ((CustomObjectScript_0804 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
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
  case ID_CUSTOM_OBJECT_4010:
  case ID_CUSTOM_OBJECT_0804:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0003:
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
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0003;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[2];
  static int cust_id_list[2] = {ID_CUSTOM_OBJECT_4010, ID_CUSTOM_OBJECT_0804};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[1];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 2;
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

    // Script 011: AreasVisited
    if (qUserVarValueInt(4) == 3) {
      aSetLevelTimer(200.000000f, 3);
      aGoalCompleted(Goal_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 001: LevelStart
    if ((ScriptActionCtr_001 < 1) && (1)) {
      aRoomSetWind(Room_indexes[0], 0.400000f, 0.000000f, 0.100000f, 45.000000f);
      aAddGameMessage(Message_strings[0], Message_strings[1]);
      aUserVarSet(0, 0.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aUserVarSet(3, 0.000000f);
      aUserVarSet(4, 0.000000f);
      aRoomSetWind(Room_indexes[1], -0.440000f, 0.821000f, -0.367000f, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 012: EndTheLevel
    if (event_data->id == 3) {
      aShowHUDMessage(Message_strings[7]);
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_4010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Switch1
    if ((ScriptActionCtr_005 < 1) && ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) &&
                                      (qUserVarValueInt(0) == 0) && (qUserVarValueInt(1) == 0) && (0 == true))) {
      aUserVarSet(0, 1.000000f);
      aUserVarSet(1, 1.000000f);
      aRoomSetFaceTexture(Room_indexes[34], 160, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[34], 151, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[34], 142, Texture_indexes[1]);
      aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 008: Switch1back
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) && (qUserVarValueInt(1) == 1) && (0 == true)) {
      aSetObjectTimer(Object_handles[0], 2.100000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 006: Switch1 Returns To Off
    if ((event_data->id == 0) && (0 == true)) {
      aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aUserVarSet(1, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0804::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: EntranceDoorMessage
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) {
      aShowHUDMessageObj(Message_strings[3], event_data->it_handle);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

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

    // Script 000: DefaultWindTunnelDirection
    if ((ScriptActionCtr_000 < 1) && ((qObjIsPlayer(event_data->it_handle) == true) && (0 == true))) {
      aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[12], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[13], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[14], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[15], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[16], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[17], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[18], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[19], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[20], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[21], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[22], -0.080000f, 0.000000f, 1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[23], -0.600000f, 0.000000f, 0.800000f, 30.000000f);
      aRoomSetWind(Room_indexes[24], -0.900000f, 0.000000f, 0.460000f, 30.000000f);
      aRoomSetWind(Room_indexes[25], -1.000000f, 0.000000f, 0.140000f, 30.000000f);
      aRoomSetWind(Room_indexes[26], -1.000000f, 0.000000f, 0.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[27], -0.900000f, 0.000000f, -0.400000f, 30.000000f);
      aRoomSetWind(Room_indexes[28], -0.660000f, 0.000000f, -0.760000f, 30.000000f);
      aRoomSetWind(Room_indexes[29], -0.460000f, 0.000000f, -0.880000f, 30.000000f);
      aRoomSetWind(Room_indexes[30], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[31], -1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[32], -1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[33], -1.000000f, 0.000000f, 0.000000f, 20.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 002: Area1Wind
    if ((qUserVarValueInt(1) == 1) && (qObjIsPlayer(event_data->it_handle) == true) && (0 == true)) {
      aShowHUDMessage(Message_strings[2]);
      aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, 0.000000f, 1.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[12], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[13], 1.000000f, 0.000000f, 0.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[14], 0.000000f, 0.000000f, 1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[15], 0.000000f, 0.000000f, 1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[16], 0.000000f, 0.000000f, 1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[16], 0.000000f, 0.000000f, 1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[18], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[22], -0.080000f, 0.000000f, 1.000000f, 15.000000f);
      aRoomSetWind(Room_indexes[23], -0.600000f, 0.000000f, 0.800000f, 15.000000f);
      aRoomSetWind(Room_indexes[24], -0.900000f, 0.000000f, 0.460000f, 15.000000f);
      aRoomSetWind(Room_indexes[25], -1.000000f, 0.000000f, 0.140000f, 15.000000f);
      aRoomSetWind(Room_indexes[26], -1.000000f, 0.000000f, 0.000000f, 15.000000f);
      aRoomSetWind(Room_indexes[27], -0.900000f, 0.000000f, -0.400000f, 15.000000f);
      aRoomSetWind(Room_indexes[28], -0.660000f, 0.000000f, -0.760000f, 15.000000f);
      aRoomSetWind(Room_indexes[29], -0.460000f, 0.000000f, -0.880000f, 15.000000f);
      aRoomSetWind(Room_indexes[30], 0.000000f, 0.000000f, -1.000000f, 15.000000f);
      aRoomSetWind(Room_indexes[35], 1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[31], 1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[36], 1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[37], 0.790000f, 0.320000f, 0.520000f, 20.000000f);
      aRoomSetWind(Room_indexes[38], 0.816000f, 0.310000f, 0.500000f, 20.000000f);
      aRoomSetWind(Room_indexes[39], 1.000000f, 0.000000f, -0.200000f, 20.000000f);
      aRoomSetWind(Room_indexes[40], 1.000000f, 0.000000f, 0.000000f, 20.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: MainRoom1Entered
    if ((ScriptActionCtr_007 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aUserVarInc(4);
      aShowHUDMessageObj(Message_strings[4], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 013: DefaultWindTunnelDirection 1
    if ((ScriptActionCtr_013 < 1) && (0 == true)) {
      aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, 0.000000f, 1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[12], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[13], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[14], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[15], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[16], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[17], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[18], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[19], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[20], 0.000000f, 0.000000f, -1.000000f, 5.000000f);
      aRoomSetWind(Room_indexes[21], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[22], -0.080000f, 0.000000f, 1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[23], -0.600000f, 0.000000f, 0.800000f, 30.000000f);
      aRoomSetWind(Room_indexes[24], -0.900000f, 0.000000f, 0.460000f, 30.000000f);
      aRoomSetWind(Room_indexes[25], -1.000000f, 0.000000f, 0.140000f, 30.000000f);
      aRoomSetWind(Room_indexes[26], -1.000000f, 0.000000f, 0.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[27], -0.900000f, 0.000000f, -0.400000f, 30.000000f);
      aRoomSetWind(Room_indexes[28], -0.660000f, 0.000000f, -0.760000f, 30.000000f);
      aRoomSetWind(Room_indexes[29], -0.460000f, 0.000000f, -0.880000f, 30.000000f);
      aRoomSetWind(Room_indexes[30], 0.000000f, 0.000000f, -1.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[31], -1.000000f, 0.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[32], -1.000000f, 0.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[36], -1.000000f, 0.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[37], -1.000000f, 0.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[38], -1.000000f, 0.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[39], -1.000000f, 0.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[33], -1.000000f, 0.000000f, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: MainRoom3Entered
    if ((ScriptActionCtr_010 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aUserVarInc(4);
      aShowHUDMessageObj(Message_strings[5], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: MainRoom2Entered
    if ((ScriptActionCtr_009 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aUserVarInc(4);
      aShowHUDMessageObj(Message_strings[6], event_data->it_handle);

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
NEXT_ID		1

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:SwitchActive
1:Tube1Active
2:Tube2Active
3:Tube3Active
4:AreasVisited
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:Switch1
1:Switch2
2:Switch3
3:EndLevelTimer
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
SwitchTube1
EntranceDoor
$$OBJECT_LIST_END

$$ROOM_LIST_START
EyeballMatcen
Tube310
StartWind
Conn03E
Conn03Hub
Conn03W
Conn02E
Conn02Hub
Conn02W
Conn01E
Conn01Hub
Conn01W
AltConn01W
AltConn01Hub
AltConn01E
AltConn02W
AltConn02Hub
AltConn02E
AltConn03E
AltConn03Hub
AltConn03W
EndWind
Curve01
Curve02
Curve03
Curve04
Curve05
Curve06
Curve07
Curve08
Curve09
Tube102
Tube202
Tube302
ControlRoom
Tube101
Tube103
Tube104
Tube105
Tube106
AltConn01N
$$ROOM_LIST_END

$$TRIGGER_LIST_START
WindTrigger
MainRoom1
MainRoom3
MainRoom2
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch31
DoorIsLocked
$$SOUND_LIST_END

$$TEXTURE_LIST_START
Reddataup
Ready1
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Explore the hidden base
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:1:LevelStart
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.400000:X
                        10:6:0.000000:Y
                        10:6:0.100000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:IntroHUDmessage:GameMessage
                        10:8:IntroBriefingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
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
                        10:10:0:4:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:-0.440000:X
                        10:6:0.821000:Y
                        10:6:-0.367000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:DefaultWindTunnelDirection
        $$CHILD_BLOCK_START
        01:0:0
        02:1
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
                        05:1
                                $$CHILD_BLOCK_START
                                10:5:0:Literal
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:17:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:18:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:20:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:21:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:22:Room
                        10:6:-0.080000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:6:-0.600000:X
                        10:6:0.000000:Y
                        10:6:0.800000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:24:Room
                        10:6:-0.900000:X
                        10:6:0.000000:Y
                        10:6:0.460000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:25:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.140000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:26:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:27:Room
                        10:6:-0.900000:X
                        10:6:0.000000:Y
                        10:6:-0.400000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:28:Room
                        10:6:-0.660000:X
                        10:6:0.000000:Y
                        10:6:-0.760000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:29:Room
                        10:6:-0.460000:X
                        10:6:0.000000:Y
                        10:6:-0.880000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:32:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:33:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Switch1
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerOrPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                10:5:0:Literal
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:34:Room
                        10:4:160:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:34:Room
                        10:4:151:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:34:Room
                        10:4:142:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Switch1back
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerOrPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                10:5:0:Literal
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:2.100000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Switch1 Returns To Off
        $$CHILD_BLOCK_START
        01:1:0
        02:9
        03:0
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
                                10:5:0:Literal
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Area1Wind
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
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
                                10:5:0:Literal
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Area1Active:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:18:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:22:Room
                        10:6:-0.080000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:6:-0.600000:X
                        10:6:0.000000:Y
                        10:6:0.800000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:24:Room
                        10:6:-0.900000:X
                        10:6:0.000000:Y
                        10:6:0.460000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:25:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.140000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:26:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:27:Room
                        10:6:-0.900000:X
                        10:6:0.000000:Y
                        10:6:-0.400000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:28:Room
                        10:6:-0.660000:X
                        10:6:0.000000:Y
                        10:6:-0.760000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:29:Room
                        10:6:-0.460000:X
                        10:6:0.000000:Y
                        10:6:-0.880000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:35:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:36:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:37:Room
                        10:6:0.790000:X
                        10:6:0.320000:Y
                        10:6:0.520000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:38:Room
                        10:6:0.816000:X
                        10:6:0.310000:Y
                        10:6:0.500000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:39:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:-0.200000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:40:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:EntranceDoorMessage
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:EntranceDoorMessage:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:MainRoom1Entered
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:Area1:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:MainRoom3Entered
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:Area3:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:MainRoom2Entered
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:Area2:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:AreasVisited
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValueInt:Integer
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:4:3:Integer
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:200.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:EndTheLevel
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EndLevelMessage:Message
                        $$CHILD_BLOCK_END
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:DefaultWindTunnelDirection 1
        $$CHILD_BLOCK_START
        01:0:1
        02:1
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
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:17:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:18:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:20:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:21:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:22:Room
                        10:6:-0.080000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:6:-0.600000:X
                        10:6:0.000000:Y
                        10:6:0.800000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:24:Room
                        10:6:-0.900000:X
                        10:6:0.000000:Y
                        10:6:0.460000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:25:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.140000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:26:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:27:Room
                        10:6:-0.900000:X
                        10:6:0.000000:Y
                        10:6:-0.400000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:28:Room
                        10:6:-0.660000:X
                        10:6:0.000000:Y
                        10:6:-0.760000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:29:Room
                        10:6:-0.460000:X
                        10:6:0.000000:Y
                        10:6:-0.880000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:32:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:36:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:37:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:38:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:39:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:33:Room
                        10:6:-1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
