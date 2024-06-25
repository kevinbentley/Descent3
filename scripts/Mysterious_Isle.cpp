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
// Filename:	Mysterious_Isle.cpp
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

#define ID_CUSTOM_OBJECT_481D 0x001
#define ID_CUSTOM_OBJECT_101E 0x002
#define ID_CUSTOM_OBJECT_1021 0x003
#define ID_CUSTOM_OBJECT_1022 0x004
#define ID_CUSTOM_OBJECT_1035 0x005
#define ID_CUSTOM_OBJECT_1020 0x006
#define ID_CUSTOM_OBJECT_1823 0x007
#define ID_CUSTOM_OBJECT_182A 0x008
#define ID_CUSTOM_OBJECT_101F 0x009
#define ID_CUSTOM_OBJECT_2828 0x00a
#define ID_CUSTOM_OBJECT_0829 0x00b

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

class CustomObjectScript_481D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_101E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1021 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1022 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1035 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1823 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_182A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_101F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2828 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0829 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

int Erruption_sound = -1;

/*
$$ACTION
Custom
Start Erruption sound
aStartErruptionSound
Starts the erruption sound
$$END
*/
void aStartErruptionSound() { Erruption_sound = Sound_Play2d(OBJECT_HANDLE_NONE, Sound_FindId("ErruptionLoop")); }

/*
$$ACTION
Custom
End Erruption sound
aEndErruptionSound
Ends the erruption sound
$$END
*/
void aEndErruptionSound() {
  if (Erruption_sound != -1) {
    Sound_Stop(Erruption_sound);
  }
}

/*
$$QUERY
Custom
i:Get the index of the tablefile entery for [s:ObjName]
qCustomGetID
Gets the tablefile index of this object name
$$END
*/
int qCustomGetID(const char *name) { return Obj_FindID(name); }

/*
$$QUERY
Custom
o:Create an object of type [e:ObjectType] and ID [i:ObjectID] at object [o:ObjectDest]
qCustomCreateObjectAtObject
Creates an object of a specified type/id at the location of a specified object
$$END
*/
int qCustomCreateObjectAtObject(int type, int id, int handle) {
  int handletype;
  int room;
  vector pos;
  matrix orient;

  if ((type != OBJ_ROBOT && type != OBJ_CLUTTER && type != OBJ_BUILDING && type != OBJ_POWERUP) || (id < 0))
    return OBJECT_HANDLE_NONE;

  Obj_Value(handle, VF_GET, OBJV_I_TYPE, &handletype);
  if (handletype == OBJ_NONE)
    return OBJECT_HANDLE_NONE;

  Obj_Value(handle, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(handle, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(handle, VF_GET, OBJV_M_ORIENT, &orient);

  return Obj_Create(type, id, room, &pos, &orient, OBJECT_HANDLE_NONE);
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

#define NUM_DOOR_NAMES 0
static const char **Door_names = NULL;
static int *Door_handles = NULL;

#define NUM_OBJECT_NAMES 18
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "Nemo Fire 1",    "Nemo Fire 2",       "Nemo Fire 3",  "Nemo Fire 4",  "Nemo_Lamp1",    "Nemo_Lamp2",
    "Nemo_Lamp3",     "Nemo_Lamp4",        "Nemo_Lamp5",   "Grotto_Lamp1", "Grotto_Lamp2",  "Grotto_Lamp3",
    "Nemo_JuncLamp1", "Red Ballon Camera", "Nemo_Switch2", "Nemo_Switch1", "Valcano Spew1", "Valcano Spew2"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 4
static const char *const Room_names[NUM_ROOM_NAMES] = {"Valcanic Shaft", "Death Reach 2", "Death's Viel",
                                                       "Death's Reach"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 0
static const char **Trigger_names = NULL;
static int *Trigger_indexes = NULL;
static int *Trigger_faces = NULL;
static int *Trigger_rooms = NULL;

#define NUM_SOUND_NAMES 2
static const char *const Sound_names[NUM_SOUND_NAMES] = {"Drop weapon", "AmbVolcanoErupt"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 1
static const char *const Path_names[NUM_PATH_NAMES] = {"BallonCrazyPath"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 0
static const char **Goal_names = NULL;
static int *Goal_indexes = NULL;

#define NUM_MESSAGE_NAMES 2
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"HackBot", "Message1"};
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
    strcpy(filename, "Mysterious_Isle.msg");
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
  case ID_CUSTOM_OBJECT_481D:
    return new CustomObjectScript_481D;
    break;
  case ID_CUSTOM_OBJECT_101E:
    return new CustomObjectScript_101E;
    break;
  case ID_CUSTOM_OBJECT_1021:
    return new CustomObjectScript_1021;
    break;
  case ID_CUSTOM_OBJECT_1022:
    return new CustomObjectScript_1022;
    break;
  case ID_CUSTOM_OBJECT_1035:
    return new CustomObjectScript_1035;
    break;
  case ID_CUSTOM_OBJECT_1020:
    return new CustomObjectScript_1020;
    break;
  case ID_CUSTOM_OBJECT_1823:
    return new CustomObjectScript_1823;
    break;
  case ID_CUSTOM_OBJECT_182A:
    return new CustomObjectScript_182A;
    break;
  case ID_CUSTOM_OBJECT_101F:
    return new CustomObjectScript_101F;
    break;
  case ID_CUSTOM_OBJECT_2828:
    return new CustomObjectScript_2828;
    break;
  case ID_CUSTOM_OBJECT_0829:
    return new CustomObjectScript_0829;
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
  case ID_CUSTOM_OBJECT_481D:
    delete ((CustomObjectScript_481D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_101E:
    delete ((CustomObjectScript_101E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1021:
    delete ((CustomObjectScript_1021 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1022:
    delete ((CustomObjectScript_1022 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1035:
    delete ((CustomObjectScript_1035 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1020:
    delete ((CustomObjectScript_1020 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1823:
    delete ((CustomObjectScript_1823 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_182A:
    delete ((CustomObjectScript_182A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_101F:
    delete ((CustomObjectScript_101F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2828:
    delete ((CustomObjectScript_2828 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0829:
    delete ((CustomObjectScript_0829 *)ptr);
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
  case ID_CUSTOM_OBJECT_481D:
  case ID_CUSTOM_OBJECT_101E:
  case ID_CUSTOM_OBJECT_1021:
  case ID_CUSTOM_OBJECT_1022:
  case ID_CUSTOM_OBJECT_1035:
  case ID_CUSTOM_OBJECT_1020:
  case ID_CUSTOM_OBJECT_1823:
  case ID_CUSTOM_OBJECT_182A:
  case ID_CUSTOM_OBJECT_101F:
  case ID_CUSTOM_OBJECT_2828:
  case ID_CUSTOM_OBJECT_0829:
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
  static int cust_handle_list[11];
  static int cust_id_list[11] = {ID_CUSTOM_OBJECT_481D, ID_CUSTOM_OBJECT_101E, ID_CUSTOM_OBJECT_1021,
                                 ID_CUSTOM_OBJECT_1022, ID_CUSTOM_OBJECT_1035, ID_CUSTOM_OBJECT_1020,
                                 ID_CUSTOM_OBJECT_1823, ID_CUSTOM_OBJECT_182A, ID_CUSTOM_OBJECT_101F,
                                 ID_CUSTOM_OBJECT_2828, ID_CUSTOM_OBJECT_0829};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[4];
  cust_handle_list[1] = Object_handles[5];
  cust_handle_list[2] = Object_handles[6];
  cust_handle_list[3] = Object_handles[7];
  cust_handle_list[4] = Object_handles[8];
  cust_handle_list[5] = Object_handles[9];
  cust_handle_list[6] = Object_handles[10];
  cust_handle_list[7] = Object_handles[11];
  cust_handle_list[8] = Object_handles[12];
  cust_handle_list[9] = Object_handles[14];
  cust_handle_list[10] = Object_handles[15];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 11;
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

    // Script 017: Init Level Variables
    if (1) {
      aUserVarSet(0, 0.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aSetLevelTimer(qRandomValue(10.000000f, 30.000000f), 7);
      aObjSaveHandle(qCustomCreateObjectAtObject(2, qCustomGetID(Message_strings[0]), Object_handles[0]), 0);
      aObjSaveHandle(qCustomCreateObjectAtObject(2, qCustomGetID(Message_strings[0]), Object_handles[1]), 1);
      aObjSaveHandle(qCustomCreateObjectAtObject(2, qCustomGetID(Message_strings[0]), Object_handles[2]), 2);
      aObjSaveHandle(qCustomCreateObjectAtObject(2, qCustomGetID(Message_strings[0]), Object_handles[3]), 3);
      aObjHide(qObjSavedHandle(0));
      aObjHide(qObjSavedHandle(1));
      aObjHide(qObjSavedHandle(2));
      aObjHide(qObjSavedHandle(3));

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 003: Eruption Sequence When Timer ID
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 013: Balloon creation and init
    if (1) {
      aAIGoalFollowPathSimple(qCustomCreateObjectAtObject(2, qCustomGetID(Message_strings[1]), Object_handles[13]),
                              Path_indexes[0], 8392965, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }

    // Script 014: Death's Reach
    if (1) {
      aRoomSetDamage(Room_indexes[1], 40.000000f, 0);
      aRoomSetWind(Room_indexes[1], -0.030000f, -0.998000f, -0.038000f, 30.000000f);
      aRoomSetWind(Room_indexes[2], -0.030000f, -0.998000f, -0.038000f, 3.800000f);
      aRoomSetWind(Room_indexes[3], -0.030000f, -0.998000f, -0.038000f, 45.000000f);
      aRoomSetDamage(Room_indexes[3], 30.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 026: End Erruption
    if (event_data->id == 2) {
      aUserVarSet(2, 0.000000f);
      aRoomSetDamage(Room_indexes[0], 0.000000f, 0);
      aRoomChangeWind(Room_indexes[0], 0.000000f, 0.000000f, 1.000000f, 0.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 015: Start Erruption
    if (event_data->id == 0) {
      aSetLevelTimer(0.500000f, 1);
      aMiscViewerShake(40.000000f);
      aUserVarSet(2, 1.000000f);
      aRoomSetDamage(Room_indexes[0], 40.000000f, 0);
      aRoomChangeWind(Room_indexes[0], 0.000000f, 0.000000f, 1.000000f, 60.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 016: Continue Erruption
    if ((event_data->id == 1) && (qUserVarValueInt(2) == 1)) {
      aSetLevelTimer(1.000000f, 1);
      aMiscViewerShake(80.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 022: Namo Switch 2 Effect Reset
    if (event_data->id == 6) {
      aUserVarSet(1, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 020: Namo Switch 1 Effect Reset
    if (event_data->id == 5) {
      aUserVarSet(0, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 023: Namo Switch 2 Up
    if (event_data->id == 4) {
      aSetLevelTimer(1.100000f, 6);
      aObjPlayAnim(Object_handles[14], 1, 2, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 019: Namo Switch 1 Up
    if (event_data->id == 3) {
      aSetLevelTimer(1.100000f, 5);
      aObjPlayAnim(Object_handles[15], 1, 2, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 024: Start Raining
    if (event_data->id == 7) {
      aSetLevelTimer(qRandomValue(50.000000f, 300.000000f), 8);
      aRainTurnOn(0.500000f);
      if (qRandomChance(0.850000f) == true) {
        aLightningTurnOn(qRandomValue(0.300000f, 2.500000f), 0.500000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 025: Stop Raining
    if (event_data->id == 8) {
      aRainTurnOff();
      aSetLevelTimer(qRandomValue(40.000000f, 300.000000f), 7);
      aLightningTurnOff();

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_481D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 011: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, -1.000000f, 4.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_101E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 010: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, -1.000000f, 4.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 009: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, -1.000000f, 4.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 012: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, -1.000000f, 4.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1035::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 008: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, -1.000000f, 4.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 007: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.400000f, 0.060000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1823::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 006: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.400000f, 0.060000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_182A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 005: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.400000f, 0.060000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_101F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 004: Torchlites
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, -1.000000f, 4.000000f,
                  30.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2828::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Nemo Switch 2 Shot
    if (qUserVarValue(1) == 0.000000f) {
      aUserVarSet(1, 1.000000f);
      aSetLevelTimer(10.000000f, 4);
      aObjPlayAnim(data->me_handle, 0, 1, 1.000000f, 0);
      aObjFireWeapon("Impact Mortar", 0, qObjSavedHandle(0));
      aObjFireWeapon("Impact Mortar", 0, qObjSavedHandle(1));
      aObjFireWeapon("Impact Mortar", 0, qObjSavedHandle(2));
      aObjFireWeapon("Impact Mortar", 0, qObjSavedHandle(3));
      aSoundPlayObject(Sound_indexes[0], Object_handles[0], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[1], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[2], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[3], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0829::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Nemo Switch 1 Shot
    if (qUserVarValue(0) == 0.000000f) {
      aUserVarSet(0, 1.000000f);
      aSetLevelTimer(30.000000f, 3);
      aSetLevelTimer(15.000000f, 2);
      aSetLevelTimer(5.000000f, 0);
      aObjPlayAnim(data->me_handle, 0, 1, 1.000000f, 0);
      aTurnOnSpew(Object_handles[16], -1, 8, 0.000000f, 0.000000f, 65536, 0, 12.000000f, 0.170000f, 30.000000f,
                  60.000000f, 65.000000f, 1, -1);
      aTurnOnSpew(Object_handles[17], -1, 7, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.100000f, 30.000000f,
                  50.000000f, 65.000000f, 1, -1);
      aSoundPlay2D(Sound_indexes[1], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
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
NEXT_ID		28

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:Nemo Switch 1 Depressed
1:Nemo Switch 2 Depressed
2:Continue Erruption
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:Start Erruption Timer
1:Erruption Shake Interval Timer
2:End Erruption Timer
3:Nemo Switch 1 Up
4:Nemo Switch 2 Up
5:Reset Nemo Effect 1
6:Reset Nemo Effect 2
7:Start Rain
8:Stop Rain
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:hb1
1:hb2
2:hb3
3:hb4
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
Nemo Fire 1
Nemo Fire 2
Nemo Fire 3
Nemo Fire 4
Nemo_Lamp1
Nemo_Lamp2
Nemo_Lamp3
Nemo_Lamp4
Nemo_Lamp5
Grotto_Lamp1
Grotto_Lamp2
Grotto_Lamp3
Nemo_JuncLamp1
Red Ballon Camera
Nemo_Switch2
Nemo_Switch1
Valcano Spew1
Valcano Spew2
$$OBJECT_LIST_END

$$ROOM_LIST_START
Valcanic Shaft
Death Reach 2
Death's Viel
Death's Reach
$$ROOM_LIST_END

$$TRIGGER_LIST_START
$$TRIGGER_LIST_END

$$SOUND_LIST_START
Drop weapon
AmbVolcanoErupt
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
Impact Mortar
$$SPECNAME_LIST_END

$$PATH_LIST_START
BallonCrazyPath
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:17:Init Level Variables
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:30.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qCustomCreateObjectAtObject:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:ObjectType
                                06:qCustomGetID:ObjectID
                                        $$CHILD_BLOCK_START
                                        10:8:HackBot:ObjName
                                        $$CHILD_BLOCK_END
                                10:1:0:0:ObjectDest
                                $$CHILD_BLOCK_END
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qCustomCreateObjectAtObject:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:ObjectType
                                06:qCustomGetID:ObjectID
                                        $$CHILD_BLOCK_START
                                        10:8:HackBot:ObjName
                                        $$CHILD_BLOCK_END
                                10:1:0:1:ObjectDest
                                $$CHILD_BLOCK_END
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qCustomCreateObjectAtObject:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:ObjectType
                                06:qCustomGetID:ObjectID
                                        $$CHILD_BLOCK_START
                                        10:8:HackBot:ObjName
                                        $$CHILD_BLOCK_END
                                10:1:0:2:ObjectDest
                                $$CHILD_BLOCK_END
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qCustomCreateObjectAtObject:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:ObjectType
                                06:qCustomGetID:ObjectID
                                        $$CHILD_BLOCK_START
                                        10:8:HackBot:ObjName
                                        $$CHILD_BLOCK_END
                                10:1:0:3:ObjectDest
                                $$CHILD_BLOCK_END
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:End Erruption
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:0.000000:Speed
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Start Erruption
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:40.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:1.000000:Z
                        10:6:60.000000:Speed
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Eruption Sequence When Timer ID
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Torchlites
        $$CHILD_BLOCK_START
        01:1:4
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Torchlites
        $$CHILD_BLOCK_START
        01:1:5
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Torchlites
        $$CHILD_BLOCK_START
        01:1:6
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Torchlites
        $$CHILD_BLOCK_START
        01:1:7
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Torchlites
        $$CHILD_BLOCK_START
        01:1:8
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Torchlites
        $$CHILD_BLOCK_START
        01:1:9
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.400000:BlobLifetime
                        10:6:0.060000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Torchlites
        $$CHILD_BLOCK_START
        01:1:10
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.400000:BlobLifetime
                        10:6:0.060000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Torchlites
        $$CHILD_BLOCK_START
        01:1:11
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.400000:BlobLifetime
                        10:6:0.060000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Torchlites
        $$CHILD_BLOCK_START
        01:1:12
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
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Balloon creation and init
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qCustomCreateObjectAtObject:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:ObjectType
                                06:qCustomGetID:ObjectID
                                        $$CHILD_BLOCK_START
                                        10:8:Message1:ObjName
                                        $$CHILD_BLOCK_END
                                10:1:0:13:ObjectDest
                                $$CHILD_BLOCK_END
                        10:16:0:Path
                        10:15:8392965:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Death's Reach
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
                        10:2:1:Room
                        10:6:40.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:-0.030000:X
                        10:6:-0.998000:Y
                        10:6:-0.038000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:-0.030000:X
                        10:6:-0.998000:Y
                        10:6:-0.038000:Z
                        10:6:3.800000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:-0.030000:X
                        10:6:-0.998000:Y
                        10:6:-0.038000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:30.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Continue Erruption
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Nemo Switch 2 Shot
        $$CHILD_BLOCK_START
        01:1:14
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:0.000000:Float
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:0:WeaponName
                        10:4:0:GunNum
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:0:WeaponName
                        10:4:0:GunNum
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:0:WeaponName
                        10:4:0:GunNum
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:0:WeaponName
                        10:4:0:GunNum
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Nemo Switch 1 Shot
        $$CHILD_BLOCK_START
        01:1:15
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:0.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:12.000000:BlobLifetime
                        10:6:0.170000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:65.000000:BlobSpeed
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
                        10:6:10.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:50.000000:BlobSize
                        10:6:65.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Namo Switch 2 Effect Reset
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Namo Switch 1 Effect Reset
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Namo Switch 2 Up
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
                        10:6:1.100000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Namo Switch 1 Up
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.100000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Start Raining
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:50.000000:LowerLimit
                                10:6:300.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                08:aRainTurnOn
                        $$CHILD_BLOCK_START
                        10:9:0.500000:Density
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.850000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningTurnOn
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:0.300000:LowerLimit
                                        10:6:2.500000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:9:0.500000:Probability
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Stop Raining
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRainTurnOff
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:40.000000:LowerLimit
                                10:6:300.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aLightningTurnOff
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
