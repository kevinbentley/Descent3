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
// Filename:	RudeAwakening.cpp
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

#define ID_CUSTOM_OBJECT_1017 0x001
#define ID_CUSTOM_OBJECT_101A 0x002
#define ID_CUSTOM_OBJECT_1019 0x003
#define ID_CUSTOM_OBJECT_1016 0x004
#define ID_CUSTOM_OBJECT_1015 0x005
#define ID_CUSTOM_OBJECT_1018 0x006
#define ID_CUSTOM_OBJECT_1813 0x007
#define ID_CUSTOM_OBJECT_1014 0x008

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

class CustomObjectScript_1017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_101A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1019 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1813 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_008 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_008 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
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

#define NUM_DOOR_NAMES 8
static const char *const Door_names[NUM_DOOR_NAMES] = {"DoorH", "DoorG", "DoorF", "DoorE",
                                                       "DoorD", "DoorC", "DoorB", "DoorA"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 15
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "SwitchH",     "SwitchG",      "SwitchF",      "SwitchE",      "SwitchD",
    "SwitchC",     "SwitchB",      "SwitchA",      "SewerSoundA",  "SewerSoundB",
    "SewerSoundC", "EnergySoundA", "EnergySoundB", "RedGoalSound", "BlueGoalSound"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 0
static const char **Room_names = NULL;
static int *Room_indexes = NULL;

#define NUM_TRIGGER_NAMES 0
static const char **Trigger_names = NULL;
static int *Trigger_indexes = NULL;
static int *Trigger_faces = NULL;
static int *Trigger_rooms = NULL;

#define NUM_SOUND_NAMES 5
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSwitch21", "AmbSwitch11", "AmbDroneN", "AmbDroneL",
                                                         "AmbDroneK"};
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
    strcpy(filename, "RudeAwakening.msg");
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
  case ID_CUSTOM_OBJECT_1017:
    return new CustomObjectScript_1017;
    break;
  case ID_CUSTOM_OBJECT_101A:
    return new CustomObjectScript_101A;
    break;
  case ID_CUSTOM_OBJECT_1019:
    return new CustomObjectScript_1019;
    break;
  case ID_CUSTOM_OBJECT_1016:
    return new CustomObjectScript_1016;
    break;
  case ID_CUSTOM_OBJECT_1015:
    return new CustomObjectScript_1015;
    break;
  case ID_CUSTOM_OBJECT_1018:
    return new CustomObjectScript_1018;
    break;
  case ID_CUSTOM_OBJECT_1813:
    return new CustomObjectScript_1813;
    break;
  case ID_CUSTOM_OBJECT_1014:
    return new CustomObjectScript_1014;
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
  case ID_CUSTOM_OBJECT_1017:
    delete ((CustomObjectScript_1017 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_101A:
    delete ((CustomObjectScript_101A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1019:
    delete ((CustomObjectScript_1019 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1016:
    delete ((CustomObjectScript_1016 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1015:
    delete ((CustomObjectScript_1015 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1018:
    delete ((CustomObjectScript_1018 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1813:
    delete ((CustomObjectScript_1813 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1014:
    delete ((CustomObjectScript_1014 *)ptr);
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
  case ID_CUSTOM_OBJECT_1017:
  case ID_CUSTOM_OBJECT_101A:
  case ID_CUSTOM_OBJECT_1019:
  case ID_CUSTOM_OBJECT_1016:
  case ID_CUSTOM_OBJECT_1015:
  case ID_CUSTOM_OBJECT_1018:
  case ID_CUSTOM_OBJECT_1813:
  case ID_CUSTOM_OBJECT_1014:
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
  static int cust_handle_list[8];
  static int cust_id_list[8] = {ID_CUSTOM_OBJECT_1017, ID_CUSTOM_OBJECT_101A, ID_CUSTOM_OBJECT_1019,
                                ID_CUSTOM_OBJECT_1016, ID_CUSTOM_OBJECT_1015, ID_CUSTOM_OBJECT_1018,
                                ID_CUSTOM_OBJECT_1813, ID_CUSTOM_OBJECT_1014};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[1];
  cust_handle_list[2] = Object_handles[2];
  cust_handle_list[3] = Object_handles[3];
  cust_handle_list[4] = Object_handles[4];
  cust_handle_list[5] = Object_handles[5];
  cust_handle_list[6] = Object_handles[6];
  cust_handle_list[7] = Object_handles[7];

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
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 008: Room Sounds Start
    if (1) {
      aSoundPlayObject(Sound_indexes[2], Object_handles[8], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[9], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[10], 1.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[11], 1.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[12], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[13], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[14], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Door H Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(7) == false) {
        aDoorLockUnlock(1, Door_handles[0]);
        aObjPlayAnim(Object_handles[0], 0, 1, 1.000000f, 0);
        aUserFlagSet(7, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[0]);
        aObjPlayAnim(Object_handles[0], 1, 2, 1.000000f, 0);
        aUserFlagSet(7, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_101A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Door G Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(6) == false) {
        aDoorLockUnlock(1, Door_handles[1]);
        aObjPlayAnim(Object_handles[1], 0, 1, 1.000000f, 0);
        aUserFlagSet(6, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[1]);
        aObjPlayAnim(Object_handles[1], 1, 2, 1.000000f, 0);
        aUserFlagSet(6, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Door F Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(5) == false) {
        aDoorLockUnlock(1, Door_handles[2]);
        aObjPlayAnim(Object_handles[2], 0, 1, 1.000000f, 0);
        aUserFlagSet(5, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[2]);
        aObjPlayAnim(Object_handles[2], 1, 2, 1.000000f, 0);
        aUserFlagSet(5, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Door E Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(4) == false) {
        aDoorLockUnlock(1, Door_handles[3]);
        aObjPlayAnim(Object_handles[3], 0, 1, 1.000000f, 0);
        aUserFlagSet(4, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[3]);
        aObjPlayAnim(Object_handles[3], 1, 2, 1.000000f, 0);
        aUserFlagSet(4, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Door D Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(3) == false) {
        aDoorLockUnlock(1, Door_handles[4]);
        aObjPlayAnim(Object_handles[4], 0, 1, 1.000000f, 0);
        aUserFlagSet(3, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[4]);
        aObjPlayAnim(Object_handles[4], 1, 2, 1.000000f, 0);
        aUserFlagSet(3, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 002: Door C Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(2) == false) {
        aDoorLockUnlock(1, Door_handles[5]);
        aObjPlayAnim(Object_handles[5], 0, 1, 1.000000f, 0);
        aUserFlagSet(2, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[5]);
        aObjPlayAnim(Object_handles[5], 1, 2, 1.000000f, 0);
        aUserFlagSet(2, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1813::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Door B Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(1) == false) {
        aDoorLockUnlock(1, Door_handles[6]);
        aObjPlayAnim(Object_handles[6], 0, 1, 1.000000f, 0);
        aUserFlagSet(1, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[6]);
        aObjPlayAnim(Object_handles[6], 1, 2, 1.000000f, 0);
        aUserFlagSet(1, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 000: Door A Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(0) == false) {
        aDoorLockUnlock(1, Door_handles[7]);
        aObjPlayAnim(Object_handles[7], 0, 1, 1.000000f, 0);
        aUserFlagSet(0, 1);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aDoorLockUnlock(0, Door_handles[7]);
        aObjPlayAnim(Object_handles[7], 1, 2, 1.000000f, 0);
        aUserFlagSet(0, 0);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
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
NEXT_ID		10

// UserType value blocks
$$UTYPE_VALS_START UserVar
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:DoorALOCKED
1:DoorBLOCKED
2:DoorCLOCKED
3:DoorDLOCKED
4:DoorELOCKED
5:DoorFLOCKED
6:DoorGLOCKED
7:DoorHLOCKED
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
DoorH
DoorG
DoorF
DoorE
DoorD
DoorC
DoorB
DoorA
$$DOOR_LIST_END

$$OBJECT_LIST_START
SwitchH
SwitchG
SwitchF
SwitchE
SwitchD
SwitchC
SwitchB
SwitchA
SewerSoundA
SewerSoundB
SewerSoundC
EnergySoundA
EnergySoundB
RedGoalSound
BlueGoalSound
$$OBJECT_LIST_END

$$ROOM_LIST_START
$$ROOM_LIST_END

$$TRIGGER_LIST_START
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch21
AmbSwitch11
AmbDroneN
AmbDroneL
AmbDroneK
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
00:7:Door H Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Door G Switch
        $$CHILD_BLOCK_START
        01:1:1
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
                                        10:10:0:6:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Door F Switch
        $$CHILD_BLOCK_START
        01:1:2
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
                                        10:10:0:5:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:2:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:2:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Door E Switch
        $$CHILD_BLOCK_START
        01:1:3
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
                                        10:10:0:4:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:3:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:3:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Door D Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:4:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:4:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Door C Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:5:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:5:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Door B Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:6:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:6:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Door A Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:7:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:7:DoorName
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Room Sounds Start
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
                        10:12:2:Sound
                        10:1:0:8:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:9:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:10:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:11:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:12:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:13:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:14:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
