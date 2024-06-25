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
// Filename:	orbital.cpp
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

#define ID_CUSTOM_OBJECT_0903 0x001
#define ID_CUSTOM_OBJECT_10F9 0x002

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

class CustomObjectScript_0903 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10F9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_005 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_005 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

/*
$$ENUM Region
0:Intro
1:Top
2:Mid
3:Bottom
4:Wing
$$END
*/

// Enter your custom script code here
struct tTextureInfo {
  const char *room_name;
  int room_id;
  int face_num;
};

#define NUM_MONITORS 11

static bool TextureInfoInitialized = false;

static tTextureInfo texture_info[NUM_MONITORS] = {
    {"Beam Emitter Rm", 0, 1775}, {"EmitterRm DataTerm", 0, 50}, {"Room 51", 0, 2},
    {"SubObs DataTerm", 0, 50},   {"SubObs Console2", 0, 50},    {"Emitter Generator", 0, 286},
    {"Dock Console", 0, 50},      {"West Dock Console", 0, 50},  {"Room 69", 0, 125},
    {"Room 82", 0, 125},          {"Control DataTerm", 0, 50}};

struct tMatcenInfo {
  const char *matcen_name;
  int matcen_id;
};

#define NUM_MATCENS 14

static bool MatcenInfoInitialized = false;

static tMatcenInfo matcen_info[NUM_MATCENS] = {{"StartingDock Matcen", 0}, {"West Dock", 0},      {"Parts Room", 0},
                                               {"Con Room Matcen1", 0},    {"Powerup Rm1", 0},    {"Powerup Rm2", 0},
                                               {"Powerup Rm3", 0},         {"Powerup Rm4", 0},    {"Powerup Rm5", 0},
                                               {"SubObs Matcen1", 0},      {"SubObs Matcen2", 0}, {"SubObs Matcen3", 0},
                                               {"Emitter Room Matcen", 0}, {"Radio Rm", 0}};

/*
$$CATEGORIES
Custom
$$END

$$ACTION
Custom
Set texture on monitors to [u:Texture]
aSetTextureForMonitors
Sets all the monitors to a given texture

Parameters:
  TextureName: the texture to assign
$$END
*/
void aSetTextureForMonitors(int texture_id) {
  int j;

  if (!TextureInfoInitialized) {
    for (j = 0; j < NUM_MONITORS; j++)
      texture_info[j].room_id = Scrpt_FindRoomName(texture_info[j].room_name);
    TextureInfoInitialized = true;
  }

  for (j = 0; j < NUM_MONITORS; j++)
    aRoomSetFaceTexture(texture_info[j].room_id, texture_info[j].face_num, texture_id);
}

/*
$$ACTION
Custom
[e:Enable/Disable] level matcen group A
aMatcenGroupASetEnableState
Enable/disable matcen
Enable or disable a matcen group, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
$$END
*/
void aMatcenGroupASetEnableState(int state) {
  int j;

  if (!MatcenInfoInitialized) {
    for (j = 0; j < NUM_MATCENS; j++)
      matcen_info[j].matcen_id = Scrpt_FindMatcenName(matcen_info[j].matcen_name);
    MatcenInfoInitialized = true;
  }

  for (j = 0; j < 4; j++)
    aMatcenSetEnableState(state, matcen_info[j].matcen_id);
}

/*
$$ACTION
Custom
[e:Enable/Disable] level matcen group B
aMatcenGroupBSetEnableState
Enable/disable matcen
Enable or disable a matcen group, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
$$END
*/
void aMatcenGroupBSetEnableState(int state) {
  int j;

  if (!MatcenInfoInitialized) {
    for (j = 0; j < NUM_MATCENS; j++)
      matcen_info[j].matcen_id = Scrpt_FindMatcenName(matcen_info[j].matcen_name);
    MatcenInfoInitialized = true;
  }

  for (j = 4; j < 9; j++)
    aMatcenSetEnableState(state, matcen_info[j].matcen_id);
}

/*
$$ACTION
Custom
[e:Enable/Disable] level matcen group C
aMatcenGroupCSetEnableState
Enable/disable matcen
Enable or disable a matcen group, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
$$END
*/
void aMatcenGroupCSetEnableState(int state) {
  int j;

  if (!MatcenInfoInitialized) {
    for (j = 0; j < NUM_MATCENS; j++)
      matcen_info[j].matcen_id = Scrpt_FindMatcenName(matcen_info[j].matcen_name);
    MatcenInfoInitialized = true;
  }

  for (j = 9; j < NUM_MATCENS; j++)
    aMatcenSetEnableState(state, matcen_info[j].matcen_id);
}

/*
$$ACTION
Custom
Initialize Bypass Connector display
aInitBypassConnDisplay
Intialize Bypass Connector display
  Initializes the HUD bypass connector display

$$END
*/
void aInitBypassConnDisplay() {}

/*
$$ACTION
Custom
Update Bypass Connector display with [s:Message] at [i:Number]
aUpdateBypassConnDisplay
Update Bypass Connector display
  Updates the HUD Bypass Connector display

$$END
*/
void aUpdateBypassConnDisplay(const char *text, int level) {
  msafe_struct mstruct;

  mstruct.color = GR_RGB(0, 255, 0);
  snprintf(mstruct.message, sizeof(mstruct.message), text, level);
  MSafe_CallFunction(MSAFE_MISC_UPDATE_HUD_ITEM, &mstruct);
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

#define NUM_OBJECT_NAMES 27
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "Spew1",  "Spew2",  "Spew3",  "Spew4",  "Spew5",     "Spew6",     "Spew7",     "Spew8",       "Spew9",
    "Spew10", "Spew11", "Spew12", "Spew13", "Spew14",    "Spew15",    "Spew16",    "Spew17",      "Spew18",
    "Spew19", "Spew20", "Spew21", "Spew22", "Big Spew1", "Big Spew2", "Big Spew3", "Repair Unit", "Wind Sound1"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 9
static const char *const Room_names[NUM_ROOM_NAMES] = {"203", "201", "204", "198", "207", "206", "205", "195", "208"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 0
static const char **Trigger_names = NULL;
static int *Trigger_indexes = NULL;
static int *Trigger_faces = NULL;
static int *Trigger_rooms = NULL;

#define NUM_SOUND_NAMES 3
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbExplosionFarC", "Briefstartup1", "AmbDroneCaveWind"};
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
    strcpy(filename, "orbital.msg");
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
  case ID_CUSTOM_OBJECT_0903:
    return new CustomObjectScript_0903;
    break;
  case ID_CUSTOM_OBJECT_10F9:
    return new CustomObjectScript_10F9;
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
  case ID_CUSTOM_OBJECT_0903:
    delete ((CustomObjectScript_0903 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10F9:
    delete ((CustomObjectScript_10F9 *)ptr);
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
  case ID_CUSTOM_OBJECT_0903:
  case ID_CUSTOM_OBJECT_10F9:
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
  static int cust_handle_list[2];
  static int cust_id_list[2] = {ID_CUSTOM_OBJECT_0903, ID_CUSTOM_OBJECT_10F9};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[25];
  cust_handle_list[1] = Object_handles[26];

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

    // Script 007: Level Start Spew Timer
    if (1) {
      aSetLevelTimer(20.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 005: Wind Tunnels
    if (1) {
      aRoomSetWind(Room_indexes[0], -0.284000f, -0.592000f, -0.753000f, 33.000000f);
      aRoomSetWind(Room_indexes[1], -0.704000f, -0.472000f, -0.532000f, 33.000000f);
      aRoomSetWind(Room_indexes[2], 0.633000f, 0.619000f, 0.466000f, 33.000000f);
      aRoomSetWind(Room_indexes[3], 0.283000f, 0.437000f, -0.854000f, 33.000000f);
      aRoomSetWind(Room_indexes[4], 0.918000f, -0.077000f, -0.389000f, 33.000000f);
      aRoomSetWind(Room_indexes[5], -0.087000f, -0.047000f, -0.995000f, 33.000000f);
      aRoomSetWind(Room_indexes[6], -0.975000f, -0.006000f, -0.219000f, 33.000000f);
      aRoomSetWind(Room_indexes[7], -0.516000f, -0.028000f, 0.856000f, 33.000000f);
      aRoomSetWind(Room_indexes[8], 0.653000f, -0.065000f, 0.755000f, 33.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 066: Dan's Spewer System
    if (event_data->id == 10) {
      aSoundPlay2D(Sound_indexes[0], 1.000000f);
      aTurnOnSpew(Object_handles[0], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[1], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[2], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[3], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[4], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[5], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[6], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[7], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[8], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[9], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[10], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[11], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[12], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[13], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[14], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[15], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[16], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[17], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[18], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[19], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[20], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[21], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[22], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 5.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[23], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 5.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[24], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 5.250000f,
                  36.000000f, 1, 0);
      aSetLevelTimer(20.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0903::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Repair Player Unit
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjSetShields(event_data->it_handle, 50.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10F9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 006: SoundSource 1
    if (1) {
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
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
NEXT_ID		69

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:Closest to
1:Shade Open
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:Shade Open
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:Breathers
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
10:StartSpewers
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
Spew1
Spew2
Spew3
Spew4
Spew5
Spew6
Spew7
Spew8
Spew9
Spew10
Spew11
Spew12
Spew13
Spew14
Spew15
Spew16
Spew17
Spew18
Spew19
Spew20
Spew21
Spew22
Big Spew1
Big Spew2
Big Spew3
Repair Unit
Wind Sound1
$$OBJECT_LIST_END

$$ROOM_LIST_START
203
201
204
198
207
206
205
195
208
$$ROOM_LIST_END

$$TRIGGER_LIST_START
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbExplosionFarC
Briefstartup1
AmbDroneCaveWind
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
00:66:Dan's Spewer System
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:5.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:5.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:5.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Repair Player Unit
        $$CHILD_BLOCK_START
        01:1:25
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:SoundSource 1
        $$CHILD_BLOCK_START
        01:1:26
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Level Start Spew Timer
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Wind Tunnels
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:-0.284000:X
                        10:6:-0.592000:Y
                        10:6:-0.753000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:-0.704000:X
                        10:6:-0.472000:Y
                        10:6:-0.532000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.633000:X
                        10:6:0.619000:Y
                        10:6:0.466000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.283000:X
                        10:6:0.437000:Y
                        10:6:-0.854000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.918000:X
                        10:6:-0.077000:Y
                        10:6:-0.389000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:-0.087000:X
                        10:6:-0.047000:Y
                        10:6:-0.995000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:-0.975000:X
                        10:6:-0.006000:Y
                        10:6:-0.219000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:-0.516000:X
                        10:6:-0.028000:Y
                        10:6:0.856000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.653000:X
                        10:6:-0.065000:Y
                        10:6:0.755000:Z
                        10:6:33.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
