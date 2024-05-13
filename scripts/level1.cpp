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
// Filename:	Level1.cpp
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

#define ID_CUSTOM_OBJECT_3855 0x001
#define ID_CUSTOM_OBJECT_10DC 0x002
#define ID_CUSTOM_OBJECT_10E0 0x003
#define ID_CUSTOM_OBJECT_10DF 0x004
#define ID_CUSTOM_OBJECT_08E8 0x005
#define ID_CUSTOM_OBJECT_584D 0x006
#define ID_CUSTOM_OBJECT_0816 0x007
#define ID_CUSTOM_OBJECT_100D 0x008
#define ID_CUSTOM_OBJECT_301B 0x009
#define ID_CUSTOM_OBJECT_18DB 0x00a

#define ID_TRIGGER_000C 0x00b
#define ID_TRIGGER_0011 0x00c
#define ID_TRIGGER_0000 0x00d
#define ID_TRIGGER_0001 0x00e
#define ID_TRIGGER_0002 0x00f
#define ID_TRIGGER_0003 0x010
#define ID_TRIGGER_0004 0x011
#define ID_TRIGGER_0006 0x012
#define ID_TRIGGER_0005 0x013
#define ID_TRIGGER_000A 0x014
#define ID_TRIGGER_000B 0x015
#define ID_TRIGGER_0008 0x016
#define ID_TRIGGER_0007 0x017
#define ID_TRIGGER_0009 0x018

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

class CustomObjectScript_3855 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10E0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10DF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08E8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_584D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0816 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_100D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_301B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18DB : public BaseScript {
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

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
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

class TriggerScript_0009 : public BaseScript {
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
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_034 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_034 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Inside-1
2:Outside
3:Inside-2
4:Inside-3
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

#define NUM_DOOR_NAMES 3
static const char *const Door_names[NUM_DOOR_NAMES] = {"MainTowerRingDoorA", "MainTowerRingDoorB", "FireDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 63
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "FirstForcefieldSwi", "BackupPowerup",      "StartSpewerA",       "StartSpewerB",       "FirstDoubleSpewerA",
    "FirstDoubleSpewerB", "2ndDoubleSpewerA",   "2ndDoubleSpewerB",   "SphereRoomSpewerA",  "SphereRoomSpewerB",
    "SphereRoomSpewerC",  "SphereRoomSpewerD",  "SRADDoorKey",        "LeftConsoleSwitch",  "LeftSecondaryDataC",
    "RightConsoleSwitch", "RightSecondaryData", "PrimaryLoginSwitch", "PrimaryDataClaw",    "RotatorA",
    "RotatorB",           "RotatorC",           "RotatorD",           "RotatorE",           "RotatorF",
    "RotatorG",           "RotatorH",           "RotatorI",           "RotatorJ",           "RotatorK",
    "RotatorL",           "RotatorM",           "RotatorN",           "EndSquidA",          "EndSquidB",
    "EndSquidC",          "EndSquidD",          "FinalBlastableDoor", "SRADDoor",           "EmergencyHatchRele",
    "RightFireSwitch",    "LeftFireSwitch",     "FirstFoggyCorridor", "HangarDoorSound",    "FirstBlackSmokeHal",
    "SecondBlackSmokeHa", "FirstUpperTowerSou", "SecondUpperTowerSo", "FlameChamberSound",  "EnergyCenterSound",
    "MechanicalRoomSoun", "MainTowerInsideSou", "LeftComputerPipesS", "RightComputerPipes", "CenterComputerPipe",
    "CenterUpperPipesSo", "CenterClawSound",    "LeftClawSound",      "RightClawSound",     "CenterPlasmaCoreSo",
    "LeftPlasmaCoreSoun", "RightPlasmaCoreSou", "RearPlasmaCoreSoun"};
int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 9
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "TerrainAccessRoom", "LeftConsoleRoom",    "RightConsoleRoom",   "RingEntranceRight", "RingEntranceLeft",
    "EscapeTubeExit",    "PrimaryObjectiveRo", "FireSphereRoomUppe", "FireSphereRoomLowe"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 14
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EndLevelTrigger",  "FireRoomTrap",     "GoalZeroCompleted",   "Waypoint1Trigger",    "Waypoint2Trigger",
    "Waypoint4Trigger", "Waypoint5Trigger", "Waypoint6LeftTrigge", "Waypoint6RightTrigg", "Music-Inside-3-1",
    "Music-Inside-2-2", "Music-Inside-2-1", "Music-Inside-1-1",    "Music-Outside"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 12
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "AmbSirenBRedAcrop", "AmbDroneHollow", "AmbDroneHallway",  "AmbDroneO", "AmbDroneX", "AmbDroneU",
    "AmbDroneL",         "AmbDroneS",      "Indoor Ambient 5", "AmbDroneN", "AmbDroneE", "AmbDroneM"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 11
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"DataScroll",  "DataCED",     "DataBoss",  "DataPlogo",
                                                             "DataDrav",    "DataLab",     "DataCrash", "DataSwit",
                                                             "DataSecAlrt", "DataClasLog", "DataMatDef"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 4
static const char *const Path_names[NUM_PATH_NAMES] = {"CameraEndPath", "PlayerEndPath", "IntroCam", "IntroShip"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 1
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"CoreMatCen"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 6
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Deactivate the Containment Forcefield",
                                                       "Get the Restricted Access Passkey",
                                                       "Access the Mainframe",
                                                       "Find Data on Sweitzer's Location",
                                                       "Escape the Facility",
                                                       "Find the Main Data Retention Complex"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 23
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"FirstForcefield",
                                                             "ClassifiedAccessPass",
                                                             "LeftConsoleSwitch",
                                                             "RightConsoleSwitch",
                                                             "PrimaryLoginSwitch",
                                                             "EndLevel",
                                                             "AccessDenied",
                                                             "CEDData",
                                                             "ShipMessageLog",
                                                             "BossData",
                                                             "PTMCdisconnected",
                                                             "DravisData",
                                                             "SRADLabData",
                                                             "ConsoleCrash",
                                                             "SweitzerData",
                                                             "SecurityAlert",
                                                             "LockDown",
                                                             "MDData",
                                                             "EmergencySwitchOpen",
                                                             "EmergencySwitch",
                                                             "SingleFireSwitch",
                                                             "BothFireSwitches",
                                                             "IntroMessage"};
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
    strcpy(filename, "Level1.msg");
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
  case ID_CUSTOM_OBJECT_3855:
    return new CustomObjectScript_3855;
    break;
  case ID_CUSTOM_OBJECT_10DC:
    return new CustomObjectScript_10DC;
    break;
  case ID_CUSTOM_OBJECT_10E0:
    return new CustomObjectScript_10E0;
    break;
  case ID_CUSTOM_OBJECT_10DF:
    return new CustomObjectScript_10DF;
    break;
  case ID_CUSTOM_OBJECT_08E8:
    return new CustomObjectScript_08E8;
    break;
  case ID_CUSTOM_OBJECT_584D:
    return new CustomObjectScript_584D;
    break;
  case ID_CUSTOM_OBJECT_0816:
    return new CustomObjectScript_0816;
    break;
  case ID_CUSTOM_OBJECT_100D:
    return new CustomObjectScript_100D;
    break;
  case ID_CUSTOM_OBJECT_301B:
    return new CustomObjectScript_301B;
    break;
  case ID_CUSTOM_OBJECT_18DB:
    return new CustomObjectScript_18DB;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
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
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
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
  case ID_CUSTOM_OBJECT_3855:
    delete ((CustomObjectScript_3855 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DC:
    delete ((CustomObjectScript_10DC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10E0:
    delete ((CustomObjectScript_10E0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10DF:
    delete ((CustomObjectScript_10DF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08E8:
    delete ((CustomObjectScript_08E8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_584D:
    delete ((CustomObjectScript_584D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0816:
    delete ((CustomObjectScript_0816 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_100D:
    delete ((CustomObjectScript_100D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_301B:
    delete ((CustomObjectScript_301B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18DB:
    delete ((CustomObjectScript_18DB *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
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
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
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
  case ID_CUSTOM_OBJECT_3855:
  case ID_CUSTOM_OBJECT_10DC:
  case ID_CUSTOM_OBJECT_10E0:
  case ID_CUSTOM_OBJECT_10DF:
  case ID_CUSTOM_OBJECT_08E8:
  case ID_CUSTOM_OBJECT_584D:
  case ID_CUSTOM_OBJECT_0816:
  case ID_CUSTOM_OBJECT_100D:
  case ID_CUSTOM_OBJECT_301B:
  case ID_CUSTOM_OBJECT_18DB:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0009:
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
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0009;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[10];
  static int cust_id_list[10] = {ID_CUSTOM_OBJECT_3855, ID_CUSTOM_OBJECT_10DC, ID_CUSTOM_OBJECT_10E0,
                                 ID_CUSTOM_OBJECT_10DF, ID_CUSTOM_OBJECT_08E8, ID_CUSTOM_OBJECT_584D,
                                 ID_CUSTOM_OBJECT_0816, ID_CUSTOM_OBJECT_100D, ID_CUSTOM_OBJECT_301B,
                                 ID_CUSTOM_OBJECT_18DB};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[12];
  cust_handle_list[2] = Object_handles[13];
  cust_handle_list[3] = Object_handles[15];
  cust_handle_list[4] = Object_handles[17];
  cust_handle_list[5] = Object_handles[1];
  cust_handle_list[6] = Object_handles[38];
  cust_handle_list[7] = Object_handles[39];
  cust_handle_list[8] = Object_handles[40];
  cust_handle_list[9] = Object_handles[41];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 10;
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

    // Script 001: Level Start Flags & Vars
    if (1) {
      aObjHide(Object_handles[1]);
      aSetLevelTimer(5.000000f, 10);
      aUserFlagSet(1, 0);
      aUserFlagSet(0, 1);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 002: Spewers Galore
    if (1) {
      aTurnOnSpew(Object_handles[2], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 0);
      aTurnOnSpew(Object_handles[3], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 1);
      aTurnOnSpew(Object_handles[4], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 3);
      aTurnOnSpew(Object_handles[5], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 2);
      aTurnOnSpew(Object_handles[6], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 4);
      aTurnOnSpew(Object_handles[7], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 5);
      aObjGhostSet(1, Object_handles[8]);
      aObjGhostSet(1, Object_handles[9]);
      aObjGhostSet(1, Object_handles[10]);
      aObjGhostSet(1, Object_handles[11]);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 011: Fire Switches Start
    if (1) {
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aRoomSetFog(Room_indexes[7], 1.000000f, 0.700000f, 0.400000f, 6000.000000f);
      aRoomSetFog(Room_indexes[8], 1.000000f, 0.700000f, 0.400000f, 6000.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 029: IntroCam
    if (1) {
      aCinematicIntro(Path_indexes[2], Message_strings[22], Object_handles[1], Path_indexes[3], 12.000000f);
      aSetLevelTimer(15.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 023: Ambient Sounds From Hell
    if (1) {
      aSoundPlayObject(Sound_indexes[1], Object_handles[42], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[43], 0.500000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[44], 1.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[45], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[46], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[47], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[48], 1.000000f);
      aSoundPlayObject(Sound_indexes[6], Object_handles[49], 1.000000f);
      aSoundPlayObject(Sound_indexes[7], Object_handles[50], 1.000000f);
      aSoundPlayObject(Sound_indexes[8], Object_handles[51], 1.000000f);
      aSoundPlayObject(Sound_indexes[9], Object_handles[52], 1.000000f);
      aSoundPlayObject(Sound_indexes[9], Object_handles[53], 1.000000f);
      aSoundPlayObject(Sound_indexes[9], Object_handles[54], 1.000000f);
      aSoundPlayObject(Sound_indexes[10], Object_handles[55], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[56], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[57], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[58], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[59], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[60], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[61], 1.000000f);
      aSoundPlayObject(Sound_indexes[11], Object_handles[62], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 032: Music-Inside
    if ((ScriptActionCtr_032 < 1) && (1)) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 033: Rotating Light Starts
    if (1) {
      aObjSetLightingDist(Object_handles[19], 0.000000f);
      aObjSetLightingDist(Object_handles[20], 0.000000f);
      aObjSetLightingDist(Object_handles[21], 0.000000f);
      aObjSetLightingDist(Object_handles[22], 0.000000f);
      aObjSetLightingDist(Object_handles[23], 0.000000f);
      aObjSetLightingDist(Object_handles[24], 0.000000f);
      aObjSetLightingDist(Object_handles[25], 0.000000f);
      aObjSetLightingDist(Object_handles[26], 0.000000f);
      aObjSetLightingDist(Object_handles[27], 0.000000f);
      aObjSetLightingDist(Object_handles[28], 0.000000f);
      aObjSetLightingDist(Object_handles[29], 0.000000f);
      aObjSetLightingDist(Object_handles[30], 0.000000f);
      aObjSetLightingDist(Object_handles[31], 0.000000f);
      aObjSetLightingDist(Object_handles[32], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 037: Ghost Squids Start
    if (1) {
      aObjGhostSet(1, Object_handles[33]);
      aObjGhostSet(1, Object_handles[34]);
      aObjGhostSet(1, Object_handles[35]);
      aObjGhostSet(1, Object_handles[36]);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 015: Left Console Level Timers
    if (1) {
      if (event_data->id == 4) {
        aAddGameMessage(Message_strings[7], Message_strings[8]);
        aRoomSetFaceTexture(Room_indexes[1], 148, Texture_indexes[1]);
        aObjPlayAnim(Object_handles[14], 7, 15, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 8);
      }
      if (event_data->id == 8) {
        aAddGameMessage(Message_strings[9], Message_strings[8]);
        aRoomSetFaceTexture(Room_indexes[1], 148, Texture_indexes[2]);
        aObjPlayAnim(Object_handles[14], 15, 22, 4.000000f, 0);
        aSetLevelTimer(4.000000f, 9);
      }
      if (event_data->id == 9) {
        aShowHUDMessage(Message_strings[10]);
        aRoomSetFaceTexture(Room_indexes[1], 148, Texture_indexes[3]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 014: Right Console Level Timers
    if (1) {
      if (event_data->id == 3) {
        aAddGameMessage(Message_strings[11], Message_strings[8]);
        aRoomSetFaceTexture(Room_indexes[2], 148, Texture_indexes[4]);
        aObjPlayAnim(Object_handles[16], 7, 15, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 5);
      }
      if (event_data->id == 5) {
        aAddGameMessage(Message_strings[12], Message_strings[8]);
        aRoomSetFaceTexture(Room_indexes[2], 148, Texture_indexes[5]);
        aObjPlayAnim(Object_handles[16], 15, 22, 4.000000f, 0);
        aSetLevelTimer(4.000000f, 6);
      }
      if (event_data->id == 6) {
        aShowHUDMessage(Message_strings[13]);
        aRoomSetFaceTexture(Room_indexes[2], 148, Texture_indexes[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 007: Primary Console Timers
    if (1) {
      if (event_data->id == 0) {
        aAddGameMessage(Message_strings[14], Message_strings[8]);
        aRoomSetFaceTexture(Room_indexes[6], 148, Texture_indexes[7]);
        aObjPlayAnim(Object_handles[18], 7, 15, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 1);
      }
      if (event_data->id == 7) {
        aShowHUDMessage(Message_strings[15]);
        aRoomSetFaceTexture(Room_indexes[6], 148, Texture_indexes[8]);
        aObjPlayAnim(Object_handles[18], 15, 22, 4.000000f, 0);
        aSetLevelTimer(4.000000f, 2);
      }
      if (event_data->id == 2) {
        aShowHUDMessage(Message_strings[16]);
        aRoomSetFaceTexture(Room_indexes[6], 148, Texture_indexes[9]);
        aMatcenSetEnableState(1, Matcen_indexes[0]);
        aMatcenSetState(1, Matcen_indexes[0]);
      }
      if (event_data->id == 1) {
        aObjPlayAnim(Object_handles[18], 0, 7, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 7);
        aRoomSetFaceTexture(Room_indexes[6], 148, Texture_indexes[10]);
        aAddGameMessage(Message_strings[17], Message_strings[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 034: Intro VOX
    if (11 == event_data->id) {
      aSoundPlaySteaming("VoxL01StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3855::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 000: Forcefield Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(0) == true) {
        aGoalCompleted(Goal_indexes[0], 1);
        aObjPlayAnim(Object_handles[0], 0, 4, 2.000000f, 0);
        aPortalRenderSet(0, 1, Room_indexes[0], 1);
        aShowHUDMessage(Message_strings[0]);
        aUserFlagSet(0, 0);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Restricted Access Passkey
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalCompleted(Goal_indexes[1], 1);
      aObjectPlayerGiveKey(event_data->it_handle, Object_handles[12], 1, Message_strings[1], 1);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10E0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Left Secondary Console Switch Activated
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(5) == false) {
        aUserFlagSet(5, 1);
        aObjPlayAnim(Object_handles[13], 0, 7, 4.000000f, 0);
        aRoomSetFaceTexture(Room_indexes[1], 148, Texture_indexes[0]);
        aShowHUDMessage(Message_strings[2]);
        aObjPlayAnim(Object_handles[14], 0, 7, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 4);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10DF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Right Secondary Console Switch Activated
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(4) == false) {
        aUserFlagSet(4, 1);
        aObjPlayAnim(Object_handles[15], 0, 7, 4.000000f, 0);
        aRoomSetFaceTexture(Room_indexes[2], 148, Texture_indexes[0]);
        aShowHUDMessage(Message_strings[3]);
        aObjPlayAnim(Object_handles[16], 0, 7, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 3);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08E8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Primary Switch Activated
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(1) == false) {
        aPortalRenderSet(0, 3, Room_indexes[3], 1);
        aPortalRenderSet(0, 3, Room_indexes[4], 1);
        aPortalRenderSet(0, 0, Room_indexes[5], 1);
        aDoorLockUnlock(1, Door_handles[0]);
        aDoorLockUnlock(1, Door_handles[1]);
        aGoalCompleted(Goal_indexes[2], 1);
        aGoalCompleted(Goal_indexes[3], 1);
        aUserFlagSet(1, 1);
        aObjPlayAnim(Object_handles[17], 0, 7, 4.000000f, 0);
        aRoomSetFaceTexture(Room_indexes[6], 148, Texture_indexes[0]);
        aShowHUDMessage(Message_strings[4]);
        aObjPlayAnim(Object_handles[18], 0, 7, 3.000000f, 0);
        aSetLevelTimer(6.000000f, 0);
        aObjSetLightingDist(Object_handles[19], 70.000000f);
        aObjSetLightingDist(Object_handles[20], 70.000000f);
        aObjSetLightingDist(Object_handles[21], 70.000000f);
        aObjSetLightingDist(Object_handles[22], 70.000000f);
        aObjSetLightingDist(Object_handles[23], 70.000000f);
        aObjSetLightingDist(Object_handles[24], 70.000000f);
        aObjSetLightingDist(Object_handles[25], 70.000000f);
        aObjSetLightingDist(Object_handles[26], 70.000000f);
        aObjSetLightingDist(Object_handles[27], 70.000000f);
        aObjSetLightingDist(Object_handles[28], 70.000000f);
        aObjSetLightingDist(Object_handles[29], 70.000000f);
        aObjSetLightingDist(Object_handles[30], 70.000000f);
        aObjSetLightingDist(Object_handles[31], 70.000000f);
        aObjSetLightingDist(Object_handles[32], 70.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[19], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[20], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[21], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[22], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[23], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[24], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[25], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[26], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[27], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[28], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[29], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[30], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[31], 1.000000f);
        aSoundPlayObject(Sound_indexes[0], Object_handles[32], 1.000000f);
        aObjGhostSet(0, Object_handles[33]);
        aObjGhostSet(0, Object_handles[34]);
        aObjGhostSet(0, Object_handles[35]);
        aObjGhostSet(0, Object_handles[36]);
        aObjPlayAnim(Object_handles[19], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[20], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[21], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[22], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[23], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[24], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[25], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[26], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[27], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[28], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[29], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[30], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[31], 0, 64, 1.000000f, 1);
        aObjPlayAnim(Object_handles[32], 0, 64, 1.000000f, 1);
        aSoundPlaySteaming("VoxL01EndLevel.osf", 0.750000f);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_584D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: End Level Sequence Backup
    if ((ScriptActionCtr_031 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_005 > 0) == false))) {
      aGoalCompleted(Goal_indexes[4], 1);
      aObjDestroy(Object_handles[37]);
      aStartEndlevelSequencePath(Path_indexes[0], Path_indexes[1], 10.000000f, Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0816::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Restricted Access Door Locked
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if ((ScriptActionCtr_003 > 0) == false) {
        aShowHUDMessageI(Message_strings[6], 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_100D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: Emergency Hatch Release Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(6) == true) {
        aObjPlayAnim(Object_handles[39], 0, 2, 2.000000f, 0);
        aTurnOffSpew(6);
        aTurnOffSpew(7);
        aTurnOffSpew(8);
        aTurnOffSpew(9);
        aTurnOffSpew(10);
        aTurnOffSpew(11);
        aTurnOffSpew(12);
        aTurnOffSpew(13);
        aUserFlagSet(6, 0);
        aDoorLockUnlock(0, Door_handles[2]);
        aDoorActivate(Door_handles[2]);
        aShowHUDMessage(Message_strings[18]);
      } else {
        aShowHUDMessage(Message_strings[19]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_301B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Fire Room Switch Right
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(3) == false) {
        aObjPlayAnim(Object_handles[40], 0, 4, 2.000000f, 0);
        aUserFlagSet(3, 1);
        aShowHUDMessage(Message_strings[20]);
      }
      if ((qUserFlag(2) == true) && (qUserFlag(3) == true)) {
        aTurnOffSpew(6);
        aTurnOffSpew(7);
        aTurnOffSpew(8);
        aTurnOffSpew(9);
        aTurnOffSpew(10);
        aTurnOffSpew(11);
        aTurnOffSpew(12);
        aTurnOffSpew(13);
        aRoomChangeFog(Room_indexes[7], 1.000000f, 0.700000f, 0.400000f, 6000.000000f, 20.000000f);
        aRoomChangeFog(Room_indexes[8], 1.000000f, 0.700000f, 0.400000f, 6000.000000f, 20.000000f);
        aShowHUDMessage(Message_strings[21]);
        aDoorLockUnlock(0, Door_handles[2]);
        aDoorActivate(Door_handles[2]);
        aUserFlagSet(6, 0);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18DB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Fire Room Switch Left
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(2) == false) {
        aObjPlayAnim(Object_handles[41], 0, 4, 2.000000f, 0);
        aUserFlagSet(2, 1);
        aShowHUDMessage(Message_strings[20]);
      }
      if ((qUserFlag(2) == true) && (qUserFlag(3) == true)) {
        aTurnOffSpew(6);
        aTurnOffSpew(7);
        aTurnOffSpew(8);
        aTurnOffSpew(9);
        aTurnOffSpew(10);
        aTurnOffSpew(11);
        aTurnOffSpew(12);
        aTurnOffSpew(13);
        aRoomChangeFog(Room_indexes[7], 1.000000f, 0.700000f, 0.400000f, 6000.000000f, 20.000000f);
        aRoomChangeFog(Room_indexes[8], 1.000000f, 0.700000f, 0.400000f, 6000.000000f, 20.000000f);
        aShowHUDMessage(Message_strings[21]);
        aDoorLockUnlock(0, Door_handles[2]);
        aDoorActivate(Door_handles[2]);
        aUserFlagSet(6, 0);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: End Level Sequence
    if ((ScriptActionCtr_005 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_031 > 0) == false))) {
      aGoalCompleted(Goal_indexes[4], 1);
      aObjDestroy(Object_handles[37]);
      aStartEndlevelSequencePath(Path_indexes[0], Path_indexes[1], 10.000000f, Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Fire Sphere Room
    if (1) {
      aRoomChangeFog(Room_indexes[7], 1.000000f, 0.700000f, 0.400000f, 500.000000f, 10.000000f);
      aRoomChangeFog(Room_indexes[8], 1.000000f, 0.700000f, 0.400000f, 500.000000f, 10.000000f);
      aTurnOnSpew(Object_handles[8], 0, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 6);
      aTurnOnSpew(Object_handles[9], 0, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 7);
      aTurnOnSpew(Object_handles[10], 0, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 8);
      aTurnOnSpew(Object_handles[11], 0, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.150000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 9);
      aTurnOnSpew(Object_handles[8], 0, 2, 0.000000f, 0.000000f, 0, 1, 2.000000f, 0.500000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 10);
      aTurnOnSpew(Object_handles[9], 0, 2, 0.000000f, 0.000000f, 0, 1, 2.000000f, 0.500000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 11);
      aTurnOnSpew(Object_handles[10], 0, 2, 0.000000f, 0.000000f, 0, 1, 2.000000f, 0.500000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 12);
      aTurnOnSpew(Object_handles[11], 0, 2, 0.000000f, 0.000000f, 0, 1, 2.000000f, 0.500000f, -1.000000f, 6.000000f,
                  30.000000f, 0, 13);
      aUserFlagSet(6, 1);
      aDoorLockUnlock(1, Door_handles[2]);
      aDoorSetPos(Door_handles[2], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Goal Zero Completed & Waypoint 3
    if (1) {
      aGoalCompleted(Goal_indexes[5], 1);
      aSetWaypoint(3);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Waypoint 1
    if (1) {
      aSetWaypoint(1);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Waypoint 2
    if (1) {
      aSetWaypoint(2);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 030: Music-Outside-Way
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Waypoint 4
    if (1) {
      aSetWaypoint(4);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: Waypoint 5
    if (1) {
      aSetWaypoint(5);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Waypoint 6 Left
    if (1) {
      aSetWaypoint(6);

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

    // Script 022: Waypoint 6 Right
    if (1) {
      aSetWaypoint(6);

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

    // Script 028: Music-Inside-3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Music-Inside-2-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Music-Inside-2-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Music-Inside-1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Music-Outside
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
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
NEXT_ID		39

// UserType value blocks
$$UTYPE_VALS_START UserVar
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:FirstForcefieldON
1:LoginSwitchON
2:LeftFireSwitchON
3:RightFireSwitchON
4:RightLoginSwitchON
5:LeftLoginSwitchON
6:FlamesON
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:StartSpewerAON
1:StartSpewerBON
2:FirstDoubleSpewerBON
3:FirstDoubleSpewerAON
4:2ndDoubleSpewerAON
5:2ndDoubleSpewerBON
6:SphereRoomSpewerA
7:SphereRoomSpewerB
8:SphereRoomSpewerC
9:SphereRoomSpewerD
10:SphereFlamesA
11:SphereFlamesB
12:SphereFlamesC
13:SphereFlamesD
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:ScrollTexTimer
1:SweitzerTexTimer
2:SecurityTexTimer
3:ScrollTexTimerRight
4:ScrollTexTimerLeft
5:DravisTexTimer
6:SRADLabTexTimer
7:MDTexTimer
8:CEDTexTimer
9:BossTexTimer
10:SoundPlay
11:IntroVOXdelayTimer
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
MainTowerRingDoorA
MainTowerRingDoorB
FireDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
FirstForcefieldSwi
BackupPowerup
StartSpewerA
StartSpewerB
FirstDoubleSpewerA
FirstDoubleSpewerB
2ndDoubleSpewerA
2ndDoubleSpewerB
SphereRoomSpewerA
SphereRoomSpewerB
SphereRoomSpewerC
SphereRoomSpewerD
SRADDoorKey
LeftConsoleSwitch
LeftSecondaryDataC
RightConsoleSwitch
RightSecondaryData
PrimaryLoginSwitch
PrimaryDataClaw
RotatorA
RotatorB
RotatorC
RotatorD
RotatorE
RotatorF
RotatorG
RotatorH
RotatorI
RotatorJ
RotatorK
RotatorL
RotatorM
RotatorN
EndSquidA
EndSquidB
EndSquidC
EndSquidD
FinalBlastableDoor
SRADDoor
EmergencyHatchRele
RightFireSwitch
LeftFireSwitch
FirstFoggyCorridor
HangarDoorSound
FirstBlackSmokeHal
SecondBlackSmokeHa
FirstUpperTowerSou
SecondUpperTowerSo
FlameChamberSound
EnergyCenterSound
MechanicalRoomSoun
MainTowerInsideSou
LeftComputerPipesS
RightComputerPipes
CenterComputerPipe
CenterUpperPipesSo
CenterClawSound
LeftClawSound
RightClawSound
CenterPlasmaCoreSo
LeftPlasmaCoreSoun
RightPlasmaCoreSou
RearPlasmaCoreSoun
$$OBJECT_LIST_END

$$ROOM_LIST_START
TerrainAccessRoom
LeftConsoleRoom
RightConsoleRoom
RingEntranceRight
RingEntranceLeft
EscapeTubeExit
PrimaryObjectiveRo
FireSphereRoomUppe
FireSphereRoomLowe
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EndLevelTrigger
FireRoomTrap
GoalZeroCompleted
Waypoint1Trigger
Waypoint2Trigger
Waypoint4Trigger
Waypoint5Trigger
Waypoint6LeftTrigge
Waypoint6RightTrigg
Music-Inside-3-1
Music-Inside-2-2
Music-Inside-2-1
Music-Inside-1-1
Music-Outside
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSirenBRedAcrop
AmbDroneHollow
AmbDroneHallway
AmbDroneO
AmbDroneX
AmbDroneU
AmbDroneL
AmbDroneS
Indoor Ambient 5
AmbDroneN
AmbDroneE
AmbDroneM
$$SOUND_LIST_END

$$TEXTURE_LIST_START
DataScroll
DataCED
DataBoss
DataPlogo
DataDrav
DataLab
DataCrash
DataSwit
DataSecAlrt
DataClasLog
DataMatDef
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
CameraEndPath
PlayerEndPath
IntroCam
IntroShip
$$PATH_LIST_END

$$MATCEN_LIST_START
CoreMatCen
$$MATCEN_LIST_END

$$GOAL_LIST_START
Deactivate the Containment Forcefield
Get the Restricted Access Passkey
Access the Mainframe
Find Data on Sweitzer's Location
Escape the Facility
Find the Main Data Retention Complex
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL01EndLevel.osf
VoxL01StartLevel.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Forcefield Switch
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
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:4:0:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FirstForcefield:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Level Start Flags & Vars
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Spewers Galore
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
                        10:1:0:2:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Restricted Access Passkey
        $$CHILD_BLOCK_START
        01:1:12
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:0:12:KeyObject
                        10:4:1:KeyNum
                        10:8:ClassifiedAccessPass:KeyName
                        10:10:0:1:Yes/No
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Left Secondary Console Switch Activated
        $$CHILD_BLOCK_START
        01:1:13
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:13:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:4:148:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LeftConsoleSwitch:Message
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:14:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Right Secondary Console Switch Activated
        $$CHILD_BLOCK_START
        01:1:15
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:15:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:4:148:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RightConsoleSwitch:Message
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:16:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Primary Switch Activated
        $$CHILD_BLOCK_START
        01:1:17
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
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
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:3:PortalNum
                                10:2:3:Room
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
                                10:4:0:PortalNum
                                10:2:5:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:3:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:17:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:4:148:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:PrimaryLoginSwitch:Message
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:22:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:25:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:26:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:29:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:30:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:31:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:32:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:19:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:20:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:21:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:22:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:23:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:24:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:25:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:26:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:27:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:28:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:29:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:30:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:31:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:0:32:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:33:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:34:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:35:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:36:Object
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:22:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:25:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:26:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:29:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:30:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:31:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:32:Object
                                10:4:0:StartFrame
                                10:4:64:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:0:Sound
                                10:9:0.750000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:End Level Sequence Backup
        $$CHILD_BLOCK_START
        01:1:1
        02:0
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:5:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
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
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:16:1:PlayerPath
                        10:6:10.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:End Level Sequence
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:31:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
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
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:16:1:PlayerPath
                        10:6:10.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Restricted Access Door Locked
        $$CHILD_BLOCK_START
        01:1:38
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:3:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageI
                                $$CHILD_BLOCK_START
                                10:8:AccessDenied:Message
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Left Console Level Timers
        $$CHILD_BLOCK_START
        01:2:0
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
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:CEDData:GameMessage
                                10:8:ShipMessageLog:HUDMessage
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:4:148:FaceNum
                                10:14:1:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:14:Object
                                10:4:7:StartFrame
                                10:4:15:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:BossData:GameMessage
                                10:8:ShipMessageLog:HUDMessage
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:4:148:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:14:Object
                                10:4:15:StartFrame
                                10:4:22:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:PTMCdisconnected:Message
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:4:148:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Right Console Level Timers
        $$CHILD_BLOCK_START
        01:2:0
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
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:DravisData:GameMessage
                                10:8:ShipMessageLog:HUDMessage
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:4:148:FaceNum
                                10:14:4:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:16:Object
                                10:4:7:StartFrame
                                10:4:15:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:5:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:5:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:SRADLabData:GameMessage
                                10:8:ShipMessageLog:HUDMessage
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:4:148:FaceNum
                                10:14:5:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:16:Object
                                10:4:15:StartFrame
                                10:4:22:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ConsoleCrash:Message
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:4:148:FaceNum
                                10:14:6:Texture
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Primary Console Timers
        $$CHILD_BLOCK_START
        01:2:0
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
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:SweitzerData:GameMessage
                                10:8:ShipMessageLog:HUDMessage
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:4:148:FaceNum
                                10:14:7:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:7:StartFrame
                                10:4:15:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SecurityAlert:Message
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:4:148:FaceNum
                                10:14:8:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:15:StartFrame
                                10:4:22:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LockDown:Message
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:4:148:FaceNum
                                10:14:9:Texture
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:0:StartFrame
                                10:4:7:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:4:148:FaceNum
                                10:14:10:Texture
                                $$CHILD_BLOCK_END
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:MDData:GameMessage
                                10:8:ShipMessageLog:HUDMessage
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Fire Sphere Room
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:1.000000:Red
                        10:6:0.700000:Green
                        10:6:0.400000:Blue
                        10:6:500.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:1.000000:Red
                        10:6:0.700000:Green
                        10:6:0.400000:Blue
                        10:6:500.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:11:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:12:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.500000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:13:SpewHandle
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:2:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Emergency Hatch Release Switch
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
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:39:Object
                                10:4:0:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:6:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:7:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:8:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:9:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:10:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:11:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:12:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:13:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EmergencySwitchOpen:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EmergencySwitch:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Fire Room Switch Right
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
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:40:Object
                                10:4:0:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SingleFireSwitch:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:6:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:7:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:8:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:9:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:10:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:11:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:12:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:13:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:1.000000:Red
                                10:6:0.700000:Green
                                10:6:0.400000:Blue
                                10:6:6000.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:1.000000:Red
                                10:6:0.700000:Green
                                10:6:0.400000:Blue
                                10:6:6000.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:BothFireSwitches:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Fire Room Switch Left
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
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:41:Object
                                10:4:0:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SingleFireSwitch:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:6:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:7:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:8:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:9:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:10:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:11:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:12:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:13:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:1.000000:Red
                                10:6:0.700000:Green
                                10:6:0.400000:Blue
                                10:6:6000.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:1.000000:Red
                                10:6:0.700000:Green
                                10:6:0.400000:Blue
                                10:6:6000.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:BothFireSwitches:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Fire Switches Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:1.000000:Red
                        10:6:0.700000:Green
                        10:6:0.400000:Blue
                        10:6:6000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:1.000000:Red
                        10:6:0.700000:Green
                        10:6:0.400000:Blue
                        10:6:6000.000000:Depth
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Goal Zero Completed & Waypoint 3
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:3:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Waypoint 1
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Waypoint 2
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:2:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Waypoint 4
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Waypoint 5
        $$CHILD_BLOCK_START
        01:0:6
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
00:21:Waypoint 6 Left
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:6:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Waypoint 6 Right
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:6:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Music-Inside-3
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Music-Inside-2-2
        $$CHILD_BLOCK_START
        01:0:10
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
00:26:Music-Inside-2-1
        $$CHILD_BLOCK_START
        01:0:11
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
00:25:Music-Inside-1
        $$CHILD_BLOCK_START
        01:0:12
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
00:30:Music-Outside-Way
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
00:24:Music-Outside
        $$CHILD_BLOCK_START
        01:0:13
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
00:29:IntroCam
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:1:TotallyNotUsedTarget
                        10:16:3:PlayerPath
                        10:6:12.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Ambient Sounds From Hell
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
                        10:12:1:Sound
                        10:1:0:42:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:43:Object
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:44:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:45:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:46:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:47:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:48:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:49:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:0:50:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:0:51:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
                        10:1:0:52:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
                        10:1:0:53:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
                        10:1:0:54:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:10:Sound
                        10:1:0:55:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:56:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:57:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:58:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:59:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:60:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:61:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:62:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Music-Inside
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Rotating Light Starts
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Ghost Squids Start
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
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Intro VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:11:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
