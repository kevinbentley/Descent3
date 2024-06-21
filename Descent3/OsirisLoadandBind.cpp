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

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/main/OsirisLoadandBind.cpp $
 * $Revision: 116 $
 * $Date: 4/04/00 12:40p $
 * $Author: Matt $
 *
 * OSIRIS functions to load a script DLL and bind to objects
 *
 * $Log: /DescentIII/main/OsirisLoadandBind.cpp $
 *
 * 116   4/04/00 12:40p Matt
 * Fixed mem leak in debugging code
 *
 * 115   10/25/99 11:57a Jeff
 * ifdef'd some Macintosh pragmas
 *
 * 114   10/22/99 11:33a Matt
 * Mac merge
 *
 * 113   9/29/99 8:04a Kevin
 * Demo playback fixes
 *
 * 112   5/19/99 3:54p Jeff
 * error is scripts are being bound to an object more than once
 *
 * 111   5/19/99 11:26a Matt
 * Added multisafe functions & Dallas actions for showing a timer on the
 * screen and adding custom HUD messages.
 *
 * 110   5/12/99 2:24p Jeff
 * Descent3 now has a setable temp directory for all temp files
 *
 * 109   5/10/99 11:55a 3dsmax
 * removed an int3
 *
 * 108   5/08/99 6:45p Chris
 * safety precausion to unload modules if they are not already
 *
 * 107   5/08/99 4:31a Jeff
 * don't int3 on multiplayer modules
 *
 * 106   5/07/99 8:27p Jeff
 * trying to hunt down why some modules hang around after they are done
 *
 * 105   5/02/99 6:41a Jeff
 * created 'test/temp' function to force unload all osiris modules
 *
 * 104   5/01/99 1:40a Jeff
 * put in hack to keep levelscripts from even being attempted to be called
 * by a client during disconnect
 *
 * 103   4/24/99 12:09a Jeff
 * added path value functions
 *
 * 102   4/20/99 8:56p Chris
 * Fixed problem with robots not being able to open locked doors that a
 * player has the key for.
 *
 * 101   4/20/99 12:59p Jeff
 * fixed loading script bug
 *
 * 100   4/20/99 12:02a Jeff
 * made linux filename friendly
 *
 * 99    4/16/99 12:19a Jeff
 * linux wants stdcall modifiers before parens, unlike windows
 *
 * 98    4/14/99 4:19a Jeff
 * more case mismatch fixes in #includes
 *
 * 97    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 96    3/17/99 11:48a Jeff
 * exported function to get what language we are using
 *
 * 95    3/11/99 9:10p Jeff
 * int3 only when restore system state if not playing back demo (because
 * scripts are not really used in demos)
 *
 * 94    3/10/99 6:44p Jeff
 * fixed exported game cinematic function for canned cinematics, so it's
 * prototype doesn't change (oem patch friendly)
 *
 * 93    3/10/99 6:21p Jeff
 * many fixes to demo system.  Fixed IGC so cameras move...fixed osiris to
 * be restored correctly, and it handles errors on restore
 *
 * 92    3/09/99 12:34p Jeff
 * extract scripts to custom\cache
 *
 * 91    3/05/99 5:25p Jeff
 * fixed saving demos in multiplayer...required adding a parameter to
 * Osiris_LoadMissionModule() to pass in the name of the d3m file (for
 * storage)
 *
 * 90    3/03/99 5:13a Jeff
 * fix bug loading dlls from hog files (wouldn't load..comparing something
 * like aigame to aigame.dll)
 *
 * 89    3/03/99 3:01a Chris
 * Exported the difficulty stuff to OSIRIS
 *
 * 88    3/03/99 12:12a Chris
 *
 * 87    3/03/99 12:07a Chris
 * Added the two new OSIRIS predefs for AI path finding
 *
 * 86    3/01/99 3:45p Jeff
 * fixed up save and restore a little bit
 *
 * 85    3/01/99 11:50a Jeff
 * call EVT_SAVESTATE and EVT_RESTORESTATE for levels
 *
 * 84    2/28/99 11:30p Chris
 * FindObjOfType and OSIRIS controllable deaths
 *
 * 83    2/28/99 8:52p Jeff
 * added functions to enable/disable creation events
 *
 * 82    2/23/99 12:54p Matt
 * Removed Int3() (Jeff on MattT's machine)
 *
 * 81    2/22/99 8:17p Chris
 * Added the LGoal_Value() function to OSIRIS
 *
 * 80    2/21/99 8:36p Jeff
 * misc changes to handle new matcen and path types of dallas
 *
 * 79    2/21/99 8:04p Jeff
 * better handling of out-of-sync scripts
 *
 * 78    2/21/99 5:51p Chris
 * FIxed a bug with OBJV_C_TYPE (It should have been OBJV_I_TYPE).  Added
 * Obj_FindType()
 *
 * 77    2/18/99 4:28p Jeff
 * added lookup functions for matcen, paths, level goals
 *
 * 76    2/18/99 11:06a Jeff
 * added event masks (so you can enable/disable object/trigger/level
 * events)
 *
 * 75    2/17/99 3:27a Jeff
 * added game checksum function to handle out-of-sync dlls
 *
 * 74    2/15/99 11:38a Jeff
 * debug mprintfs when extracting dlls
 *
 * 73    2/14/99 1:16a Jeff
 * exported canned cinematic
 *
 * 72    2/13/99 6:11p Jeff
 * fixed bug when extracting scripts for the second+ time
 *
 * 71    2/12/99 6:24p Kevin
 *
 * 70    2/12/99 6:22p Kevin
 * Fixed a thingy for Jeffy
 *
 * 69    2/11/99 2:56a Jeff
 * improvements to introcam
 *
 * 68    2/10/99 7:12p Jeff
 * oops...OpenLibrary returns 0 not -1
 *
 * 67    2/10/99 6:56p Jeff
 * handle invalid libraries when extracting scripts
 *
 * 66    2/10/99 3:41p Jeff
 * removed unneeded assert
 *
 * 65    2/10/99 3:29p Jeff
 * extracted dll manager knows the difference between game hogs and
 * mission hogs
 *
 * 64    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 63    2/08/99 2:51p Jeff
 * removed dead evt_ain events that were commented out
 *
 * 62    2/06/99 7:05p Jeff
 * turned off osiris debug messages by default
 *
 * 61    2/05/99 9:06p Jeff
 * added aux events for a couple new ainotify's
 *
 * 60    2/03/99 1:51a Jeff
 * added predefs for ship permissions
 *
 * 59    2/03/99 12:43a Chris
 * Added Obj_GetGroundPos
 *
 * 58    2/02/99 12:46p Jeff
 * handy mprintfs on save/restore state
 *
 * 57    2/01/99 5:29p Jeff
 * obj_dummy's can be assigned scripts
 *
 * 56    1/31/99 10:40p Jeff
 * exported Osiris_CancelTimerID to DLLs
 *
 * 55    1/31/99 10:16p Matt
 * Added Osiris_CancelTimerID()
 *
 * 54    1/31/99 8:52p Jeff
 * new in game cinematics system finished
 *
 * 51    1/25/99 8:18a Chris
 * Made the AUX Notify remap more obvious
 *
 * 50    1/25/99 8:13a Chris
 * Made the AUX goal remap more obvious...
 *
 * 49    1/24/99 8:18p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 48    1/24/99 6:36p Jeff
 * fixed trigger call event bug (wasn't using the correct DLLid)
 *
 * 47    1/22/99 8:54p Jeff
 * added custom-default script overrides
 *
 * 46    1/22/99 6:53p Chris
 * Fixed LoadandBind Aux notify problems, fixed static path problems,
 * fixed AIF_FORCE_AWARE Problems, improved path code
 *
 * 45    1/22/99 5:15p Jeff
 * added a key to toggle osiris debug messages
 *
 * 44    1/22/99 4:47p Jeff
 *
 * 43    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 42    1/20/99 4:17p Jeff
 * added ai notify child events and predefs to get ids of sound, room,
 * trigger, object names
 *
 * 41    1/20/99 3:46a Jeff
 * exported boss introduction functions
 *
 * 39    1/16/99 2:19p Jeff
 * only save and use the base filename of a dll (to keep it platform
 * independent)
 *
 * 38    1/16/99 1:29p Jeff
 * updated the OMMS system to be faster.  Removed the event for restoring
 * it, since it is require to surround code in attach/detach blocks.
 *
 * 37    1/16/99 10:39a Jeff
 * added mission memory management to Osiris...only slightly tested.  Need
 * to solve game save/restore problem still
 *
 * 36    1/15/99 5:59p Chris
 *
 * 35    1/13/99 5:20p Jeff
 * added 4 new file operation predefs
 *
 * 34    1/13/99 4:05p Jeff
 * when loading a script dll, a string table is looked for and
 * automatically loaded and passed to the newly loaded dll on init for
 * use.
 *
 * 33    1/13/99 3:25a Chris
 * Added Obj_Burning and Obj_IsEffect to OSIRIS
 *
 * 32    1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 31    1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 30    1/11/99 12:53p Jeff
 * added a function that given a module name it will make sure it has an
 * extension.  Made Osiris friendly with modules with no extension
 *
 * 29    1/08/99 2:02p Jeff
 * handle the case of extracting too many scripts
 *
 * 28    1/08/99 2:00p Jeff
 * fixed minor bug with hog extraction (mem leak) and made it so you can
 * keep calling ExtractScripts for multiple hogs
 *
 * 27    1/08/99 1:50p Jeff
 * finished support on loading scripts from hogs
 *
 * 26    1/07/99 10:52p Jeff
 * wrote skeleton of hog script file extraction
 *
 * 25    1/04/99 6:43p Jeff
 * added support to get/set mission flag values
 *
 * 24    1/04/99 12:42p Chris
 * Updated OSIRIS with "xxxx_external.h" files and Obj_Value, and
 * Matcen_XXX functions
 *
 * 23    1/04/99 12:23p Jeff
 * added to evt_use and support for mission module scripts
 *
 * 22    12/31/98 7:33p Jeff
 * improved Osiris timers to have unique IDs, along with adding an
 * EVT_TIMERCANCEL and a new flag to autodestruct the timer if a given
 * object handle dies.
 *
 * 21    12/31/98 2:37p Jeff
 * added SaveRestoreState import function
 *
 * 20    12/30/98 5:17p Jeff
 * changes made to handle script name override, to override the name of
 * the script to use in a module.
 *
 * 19    12/30/98 3:46p Chris
 * Incremental AI changes
 *
 * 18    12/30/98 12:31p Jeff
 * when freeing object scripts, the type is changed before it's freed in
 * ObjDelete.  Also, when destroyed, OBJ_ROBOT becomes OBJ_DEBRIS and
 * Osiris was not handling this.
 *
 * 17    12/23/98 12:10p Chris
 * Added Gametime and Frametime to OSIRIS
 *
 * 16    12/22/98 4:51p Chris
 * Added a ObjCreate predefined function
 *
 * 15    12/22/98 4:19p Jeff
 * exported msafe_DoPowerup
 *
 * 14    12/22/98 2:46p Chris
 * Added the AIValue predefined function
 *
 * 13    12/18/98 6:00p Jeff
 * added support for door scripts in new osiris
 *
 * 12    12/18/98 3:10p Mark
 * removed int3
 *
 * 11    12/18/98 11:07a Jeff
 * triggers are implemented
 *
 * 10    12/18/98 10:42a Jeff
 * added timer support and auto-save memory manager for new osiris.  New
 * events evt_memrestore state added also
 *
 * 9     12/17/98 7:26p Jeff
 * added memory manager for autosaving script data
 *
 * 8     12/17/98 5:44p Jeff
 * created timer system for osiris and save restore events
 *
 * 7     12/17/98 2:27p Keneta
 * Commented out an Int3(), as per Jeff's directions.  (MattT)
 *
 * 6     12/17/98 12:08p Jeff
 * first checkin of new implementation of OSIRIS (old OSIRIS no longer
 * works)
 *
 * 5     12/16/98 10:21p Jeff
 * added level and trigger event call functions.  added trigger script
 * functionality (still primative)
 *
 * 4     12/16/98 5:37p Jason
 * added new multisafe architecture
 *
 * 3     12/16/98 10:58a Jeff
 * checked in so Jason can use
 *
 * 2     12/14/98 11:32a Jeff
 * started work on osiris load and bind functions
 *
 * $NoKeywords: $
 */

#include "osiris_dll.h"
#include "pserror.h"
#include "mono.h"
#include "cfile.h"
#include "ddio.h"
#include "manage.h"
#include <stdlib.h>
#include "mem.h"
#include "DllWrappers.h"
#include "objinfo.h"
#include "multisafe.h"
#include "osiris_predefs.h"
#include "trigger.h"
#include "game.h"
#include "multi.h"
#include "door.h"
#include "localization.h"
#include "player.h"
#include "gamecinematics.h"
#include "demofile.h"

#ifdef _DEBUG
#define OSIRISDEBUG
#endif


bool Show_osiris_debug = false;

#define MAX_LOADED_MODULES 96 // maximum number of dlls that can be loaded at a time

#define OSIMF_INUSE 0x1        // slot in use
#define OSIMF_LEVEL 0x2        // level module
#define OSIMF_DLLELSEWHERE 0x4 // mission module
#define OSIMF_INTEMPDIR 0x8    // the dll was extracted from a hog and it is in a temp file
#define OSIMF_NOUNLOAD                                                                                                 \
  0x10 // the dll should not be unloaded if the reference count is
       // 0, only when the level ends

// The exported DLL function call prototypes
#if defined(__LINUX__) || defined(ANDROID)
typedef char DLLFUNCCALL (*InitializeDLL_fp)(tOSIRISModuleInit *function_list);
typedef void DLLFUNCCALL (*ShutdownDLL_fp)(void);
typedef int DLLFUNCCALL (*GetGOScriptID_fp)(const char *name, uint8_t isdoor);
typedef void DLLFUNCCALL *(*CreateInstance_fp)(int id);
typedef void DLLFUNCCALL (*DestroyInstance_fp)(int id, void *ptr);
typedef int16_t DLLFUNCCALL (*CallInstanceEvent_fp)(int id, void *ptr, int event, tOSIRISEventInfo *data);
typedef int DLLFUNCCALL (*GetTriggerScriptID_fp)(int trigger_room, int trigger_face);
typedef int DLLFUNCCALL (*GetCOScriptList_fp)(int **list, int **id_list);
typedef int DLLFUNCCALL (*SaveRestoreState_fp)(void *file_ptr, uint8_t saving_state);
#else
typedef char(DLLFUNCCALL *InitializeDLL_fp)(tOSIRISModuleInit *function_list);
typedef void(DLLFUNCCALL *ShutdownDLL_fp)(void);
typedef int(DLLFUNCCALL *GetGOScriptID_fp)(const char *name, uint8_t isdoor);
typedef void *(DLLFUNCCALL *CreateInstance_fp)(int id);
typedef void(DLLFUNCCALL *DestroyInstance_fp)(int id, void *ptr);
typedef int16_t(DLLFUNCCALL *CallInstanceEvent_fp)(int id, void *ptr, int event, tOSIRISEventInfo *data);
typedef int(DLLFUNCCALL *GetTriggerScriptID_fp)(int trigger_room, int trigger_face);
typedef int(DLLFUNCCALL *GetCOScriptList_fp)(int **list, int **id_list);
typedef int(DLLFUNCCALL *SaveRestoreState_fp)(void *file_ptr, uint8_t saving_state);
#endif

struct tRefObj {
  int objnum;
  int type, id;
  bool dummy;
  tRefObj *next;
};

struct tOSIRISModule {
  uint8_t flags;
  uint8_t extracted_id;
  uint16_t reference_count;
  InitializeDLL_fp InitializeDLL;
  ShutdownDLL_fp ShutdownDLL;
  GetGOScriptID_fp GetGOScriptID;
  CreateInstance_fp CreateInstance;
  DestroyInstance_fp DestroyInstance;
  CallInstanceEvent_fp CallInstanceEvent;
  GetTriggerScriptID_fp GetTriggerScriptID;
  GetCOScriptList_fp GetCOScriptList;
  SaveRestoreState_fp SaveRestoreState;
  module mod;
  char *module_name;
  char **string_table;
  int strings_loaded;

#ifdef OSIRISDEBUG
  tRefObj *RefRoot;
#endif
};

static tOSIRISModule OSIRIS_loaded_modules[MAX_LOADED_MODULES];
tOSIRISModuleInit Osiris_module_init;

struct {
  bool level_loaded;
  uint16_t num_customs;
  uint16_t dll_id;
  int *custom_ids;
  int *custom_handles;
  void *instance;
} tOSIRISCurrentLevel;

struct {
  bool mission_loaded;
  uint16_t dll_id;
} tOSIRISCurrentMission;

#define OESF_USED 0x0001
#define OESF_MISSION 0x0002 // mission dlls
struct tExtractedScriptInfo {
  uint8_t flags;
  char *temp_filename;
  char *real_filename;
};
static tExtractedScriptInfo OSIRIS_Extracted_scripts[MAX_LOADED_MODULES];
static char *OSIRIS_Extracted_script_dir = NULL;

//	Osiris_CreateModuleInitStruct
//	Purpose:
//		This function initializes a Module Init Struct with all the needed data to get sent
//	to the module during initialization.
extern void Osiris_CreateModuleInitStruct(tOSIRISModuleInit *mi);

static void Osiris_RestoreOMMS(CFILE *file);
static void Osiris_SaveOMMS(CFILE *file);

//	Osiris_CreateGameChecksum
//	Purpose:
//		Generates a checksum of the game's structures, to give to the modules
//	so they can use to compare to the time when they were compiled, to see
//	if they are compatible.
uint32_t Osiris_CreateGameChecksum(void);
//	Osiris_IsEventEnabled
//	Purpose:
//		Returns true if the event is allowed to be called
static bool Osiris_IsEventEnabled(int event);

extern void Cinematic_StartCannedScript(tCannedCinematicInfo *info);

//	Osiris_DumpLoadedObjects
//
//	Debug.  Dumps all loaded objects to given file
static void Osiris_DumpLoadedObjects(char *file);
static void Osiris_ForceUnloadModules(void);

uint32_t Osiris_game_checksum;

static uint8_t Osiris_event_mask = OEM_OBJECTS | OEM_TRIGGERS | OEM_LEVELS;
static bool Osiris_create_events_disabled = false;
static bool Osiris_level_script_loaded = false;

#define HAVECUSTOMONLY(type) (type == OBJ_CAMERA)
#define CANBEASSIGNEDSCRIPT(obj)                                                                                       \
  ((obj) &&                                                                                                            \
   ((obj->type == OBJ_ROBOT) || (obj->type == OBJ_BUILDING) || (obj->type == OBJ_POWERUP) ||                           \
    (obj->type == OBJ_CLUTTER) || (obj->type == OBJ_DOOR) || (obj->type == OBJ_CAMERA) || (obj->type == OBJ_DUMMY)))
#define CANHAVEANYSCRIPT(obj)                                                                                          \
  (CANBEASSIGNEDSCRIPT(obj) || (obj && ((obj->type == OBJ_DEBRIS) || (obj->type == OBJ_GHOST))))
#define CANTYPEBEASSIGNEDSCRIPT(type)                                                                                  \
  ((type == OBJ_ROBOT) || (type == OBJ_BUILDING) || (type == OBJ_POWERUP) || (type == OBJ_CLUTTER) ||                  \
   (type == OBJ_DOOR) || (type == OBJ_CAMERA))
//========================================================================

//	Osiris_ShutdownModuleLoader
//	Purpose:
//		Closes down the OSIRIS module loader and handling system
void Osiris_ShutdownModuleLoader(void) {
  mprintf(0, "OSIRIS: Shutting down module manager\n");
  int i;
  for (i = 0; i < MAX_LOADED_MODULES; i++) {
    Osiris_FreeModule(i);
  }
}

//	Osiris_InitModuleLoader
//	Purpose:
//		Initializes the OSIRIS module loader and handling system
void Osiris_InitModuleLoader(void) {
  mprintf(0, "OSIRIS: Initializing module manager\n");
  int i;
  for (i = 0; i < MAX_LOADED_MODULES; i++) {
    OSIRIS_loaded_modules[i].flags = 0;
    OSIRIS_loaded_modules[i].reference_count = 0;
    OSIRIS_loaded_modules[i].module_name = NULL;
    OSIRIS_loaded_modules[i].CallInstanceEvent = NULL;
    OSIRIS_loaded_modules[i].CreateInstance = NULL;
    OSIRIS_loaded_modules[i].DestroyInstance = NULL;
    OSIRIS_loaded_modules[i].GetCOScriptList = NULL;
    OSIRIS_loaded_modules[i].GetGOScriptID = NULL;
    OSIRIS_loaded_modules[i].GetTriggerScriptID = NULL;
    OSIRIS_loaded_modules[i].InitializeDLL = NULL;
    OSIRIS_loaded_modules[i].SaveRestoreState = NULL;
    OSIRIS_loaded_modules[i].string_table = NULL;
    OSIRIS_loaded_modules[i].strings_loaded = 0;

#ifdef OSIRISDEBUG
    ASSERT(OSIRIS_loaded_modules[i].RefRoot == NULL);
    OSIRIS_loaded_modules[i].RefRoot = NULL;
#endif
  }

  Osiris_CreateModuleInitStruct(&Osiris_module_init);
  Osiris_game_checksum = Osiris_CreateGameChecksum();
  Osiris_module_init.game_checksum = Osiris_game_checksum;

  tOSIRISCurrentLevel.level_loaded = false;
  tOSIRISCurrentLevel.num_customs = 0;
  tOSIRISCurrentLevel.dll_id = 0;
  tOSIRISCurrentLevel.custom_ids = NULL;
  tOSIRISCurrentLevel.custom_handles = NULL;
  tOSIRISCurrentLevel.instance = NULL;

  tOSIRISCurrentMission.mission_loaded = false;
  tOSIRISCurrentMission.dll_id = 0;

  Osiris_InitMemoryManager();
  Osiris_InitOMMS();

  OSIRIS_Extracted_script_dir = NULL;

  atexit(Osiris_ShutdownModuleLoader);
}

//	Osiris_CreateGameChecksum
//	Purpose:
//		Generates a checksum of the game's structures, to give to the modules
//	so they can use to compare to the time when they were compiled, to see
//	if they are compatible.
uint32_t Osiris_CreateGameChecksum(void) {
  uint32_t value = 0xe1e1b0b0;

  value += sizeof(object);
  value += sizeof(player) * 2;
  value += sizeof(tOSIRISModuleInit) * 3;
  value += sizeof(tOSIRISEventInfo) * 5;
  value += sizeof(tOSIRISTIMER) * 7;
  value += sizeof(tOSIRISSCRIPTID) * 11;
  value += sizeof(tOSIRISMEMCHUNK) * 13;
  value += sizeof(msafe_struct) * 17;
  value += sizeof(ray_info) * 19;
  value += sizeof(vector) * 23;
  value += sizeof(matrix) * 29;
  value += sizeof(tGameCinematic) * 31;
  value += sizeof(tCannedCinematicInfo) * 37;

  value = value << 2;

  int index = 0;
  while (Osiris_module_init.fp[index]) {
    value++;
    index++;
  }

  return value;
}

//	Osiris_FreeModule
//	Purpose:
//		Removes a currently loaded module from the OSIRIS system
void Osiris_FreeModule(int id) {
  if (id < 0 || id >= MAX_LOADED_MODULES)
    return;

  if (OSIRIS_loaded_modules[id].flags & OSIMF_INUSE) {

#ifdef OSIRISDEBUG
    ASSERT(OSIRIS_loaded_modules[id].RefRoot == NULL); // not all objects freed
#endif

    if (OSIRIS_loaded_modules[id].flags & OSIMF_LEVEL) {
      // we're freeing the level dll
      tOSIRISCurrentLevel.level_loaded = false;
      tOSIRISCurrentLevel.num_customs = 0;
      tOSIRISCurrentLevel.dll_id = 0;
      tOSIRISCurrentLevel.custom_ids = NULL;
      tOSIRISCurrentLevel.custom_handles = NULL;
      tOSIRISCurrentLevel.instance = NULL;
    }

    if (!(OSIRIS_loaded_modules[id].flags & OSIMF_DLLELSEWHERE)) {

      // this is a DLL belonging to us
      if (OSIRIS_loaded_modules[id].ShutdownDLL) {
        // call the shutdown function so the DLL can perform what it needs
        OSIRIS_loaded_modules[id].ShutdownDLL();
      }

      if (OSIRIS_loaded_modules[id].string_table != NULL) {
        DestroyStringTable(OSIRIS_loaded_modules[id].string_table, OSIRIS_loaded_modules[id].strings_loaded);
      }
      mod_FreeModule(&OSIRIS_loaded_modules[id].mod);
    }

    if (tOSIRISCurrentMission.mission_loaded && id == tOSIRISCurrentMission.dll_id) {
      // we're freeing the mission dll
      tOSIRISCurrentMission.mission_loaded = false;
      tOSIRISCurrentMission.dll_id = 0;
    }

    OSIRIS_loaded_modules[id].CallInstanceEvent = NULL;
    OSIRIS_loaded_modules[id].CreateInstance = NULL;
    OSIRIS_loaded_modules[id].DestroyInstance = NULL;
    OSIRIS_loaded_modules[id].GetCOScriptList = NULL;
    OSIRIS_loaded_modules[id].GetGOScriptID = NULL;
    OSIRIS_loaded_modules[id].GetTriggerScriptID = NULL;
    OSIRIS_loaded_modules[id].InitializeDLL = NULL;
    OSIRIS_loaded_modules[id].SaveRestoreState = NULL;
    OSIRIS_loaded_modules[id].string_table = NULL;
    OSIRIS_loaded_modules[id].strings_loaded = 0;
    OSIRIS_loaded_modules[id].flags = 0;
    OSIRIS_loaded_modules[id].reference_count = 0;

#ifdef OSIRISDEBUG
    ASSERT(OSIRIS_loaded_modules[id].RefRoot == NULL);
    OSIRIS_loaded_modules[id].RefRoot = NULL;
#endif

    if (OSIRIS_loaded_modules[id].module_name) {
      mem_free(OSIRIS_loaded_modules[id].module_name);
      OSIRIS_loaded_modules[id].module_name = NULL;
    }
  }
}

void Osiris_ForceUnloadModules(void) {
  for (int j = 0; j < MAX_LOADED_MODULES; j++) {
    if (OSIRIS_loaded_modules[j].flags & OSIMF_INUSE) {
      Osiris_FreeModule(j);
    }
  }
}

//	Osiris_DumpLoadedObjects
//
//	Debug.  Dumps all loaded objects to given file
void Osiris_DumpLoadedObjects(char *file) {
#ifndef OSIRISDEBUG
  return;
#else
  CFILE *f = cfopen(file, "wt");
  if (!f) {
    Int3();
    return;
  }

  char buffy[1024];

  for (int j = 0; j < MAX_LOADED_MODULES; j++) {
    if (OSIRIS_loaded_modules[j].flags & OSIMF_INUSE && OSIRIS_loaded_modules[j].RefRoot != NULL) {
      // uh oh! scripts were not completely decremented
      tRefObj *node = OSIRIS_loaded_modules[j].RefRoot;
      while (node) {
        snprintf(buffy, sizeof(buffy), "Module: \"%s\" Objnum: %d Type: %d%s Id:%d\n",
                 OSIRIS_loaded_modules[j].module_name, node->objnum, node->type, (node->dummy) ? "(Dummy)" : "",
                 node->id);
        cf_WriteString(f, buffy);
        node = node->next;
      }
    }
  }

  cfclose(f);
#endif
}

//	Osiris_FindLoadedModule
//	Purpose:
//		Given the name of a module, it returns the id of a loaded OSIRIS module.  -1 if it isn't loaded.
int Osiris_FindLoadedModule(char *module_name) {
  // search through the list of loaded modules and see if we can find a match
  // strip off the extension
  char real_name[_MAX_PATH];
  ddio_SplitPath(module_name, NULL, real_name, NULL);

  int i;
  for (i = 0; i < MAX_LOADED_MODULES; i++) {
    if (OSIRIS_loaded_modules[i].flags & OSIMF_INUSE) {
      if (OSIRIS_loaded_modules[i].module_name && (!stricmp(OSIRIS_loaded_modules[i].module_name, real_name))) {
        // we found a match
        return i;
      }
    }
  }

  return -1;
}

//	Osiris_UnloadModule
//	Purpose:
//		Given a module id, it will decrement the reference count to that module by one.  If the reference
//	count becomes zero, the module will be unloaded from memory.
void Osiris_UnloadModule(int module_id) {
  if (module_id < 0 || module_id >= MAX_LOADED_MODULES)
    return;
  if (OSIRIS_loaded_modules[module_id].flags & OSIMF_INUSE) {
    // the module is in use
    if (Show_osiris_debug) {
      mprintf(0, "OSIRIS: Decrementing reference count for module (%s)\n", OSIRIS_loaded_modules[module_id].module_name);
    }
    OSIRIS_loaded_modules[module_id].reference_count--;

    ASSERT(OSIRIS_loaded_modules[module_id].reference_count >= 0);

    if (OSIRIS_loaded_modules[module_id].reference_count <= 0) {

      if (OSIRIS_loaded_modules[module_id].flags & OSIMF_NOUNLOAD) {

        ASSERT(!(OSIRIS_loaded_modules[module_id].flags & OSIMF_LEVEL));        // level modules cannot be set static
        ASSERT(!(OSIRIS_loaded_modules[module_id].flags & OSIMF_DLLELSEWHERE)); // mission modules cannot be set static

        // do not unload this module, due to the forced stay in memory
        mprintf(0, "OSIRIS: Module (%s) staying in memory due to static flag\n",
                 OSIRIS_loaded_modules[module_id].module_name);
      } else {
        // time to unload this module
        if (Show_osiris_debug) {
          mprintf(0, "OSIRIS: Module (%s) reference count is at 0, unloading\n",
                   OSIRIS_loaded_modules[module_id].module_name);
        }
        Osiris_FreeModule(module_id);
      }
    }
  } else {
    mprintf(0, "OSIRIS: Trying to unload a module (%d) that is not in use!\n", module_id);
    Int3();
  }
}

//	Osiris_UnloadLevelModule
//	Purpose:
//		Instead of saving the handle returned from Osiris_LoadLevelModule() and calling
//	Osiris_UnloadModule() with that handle, you can just call this, instead of the call
//	to Osiris_UnloadModule().
void Osiris_UnloadLevelModule(void) {
  Osiris_level_script_loaded = false;

  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return;
  }

  // free allocated scripts (we can do this, because the root node will just become
  // NULL and once the first call to allocate memory is used, it'll automatically work)
  Osiris_CloseMemoryManager();

  if (tOSIRISCurrentLevel.level_loaded) {
    int dll_id = tOSIRISCurrentLevel.dll_id;

    // free up all instances of trigger scripts still around
    for (int i = 0; i < Num_triggers; i++) {
      if (Triggers[i].osiris_script.script_instance) {
        OSIRIS_loaded_modules[dll_id].DestroyInstance(Triggers[i].osiris_script.script_id,
                                                      Triggers[i].osiris_script.script_instance);
      }
      Triggers[i].osiris_script.script_id = -1;
      Triggers[i].osiris_script.script_instance = NULL;
    }

    Osiris_UnloadModule(dll_id);
  }

  // go through the remaining modules and unload those with the OSIMF_NOUNLOAD set
  for (int j = 0; j < MAX_LOADED_MODULES; j++) {

    if (OSIRIS_loaded_modules[j].flags & OSIMF_INUSE && OSIRIS_loaded_modules[j].flags & OSIMF_NOUNLOAD) {
      // unload this module
      mprintf(0, "OSIRIS: Unloading static module (%s) due to level end\n", OSIRIS_loaded_modules[j].module_name);
      Osiris_FreeModule(j);
    }

    if (OSIRIS_loaded_modules[j].flags & OSIMF_INUSE && (!(OSIRIS_loaded_modules[j].flags & OSIMF_DLLELSEWHERE))) {
      // Please get Jeff
      // We are done with the level and all modules should be unloaded at this point,
      // however, this module is still in use....
      Osiris_FreeModule(j);
    }
  }
}

//	returns:	-2 if not found
//				-1 if it is in data\scripts
//				0-x which extracted script id it is
int _get_full_path_to_module(char *module_name, char *fullpath, char *basename) {
  char modfilename[_MAX_PATH];
  char ppath[_MAX_PATH], pext[256];
  char adjusted_name[_MAX_PATH], adjusted_fname[_MAX_PATH];
  char *p;

  ddio_SplitPath(module_name, ppath, basename, pext);

  // make sure filename/ext is all lowercase, requirement for Linux, doesn't hurt Windows
  p = basename;
  while (p && *p) {
    *p = tolower(*p);
    p++;
  }
  p = pext;
  while (p && *p) {
    *p = tolower(*p);
    p++;
  }
  strcpy(adjusted_fname, basename);
  strcat(adjusted_fname, pext);

  if (strlen(ppath) > 0) {
    ddio_MakePath(adjusted_name, ppath, adjusted_fname, NULL);
  } else {
    strcpy(adjusted_name, adjusted_fname);
  }

  // determine real name of script
  mod_GetRealModuleName(adjusted_name, modfilename);

  int exist = cfexist(modfilename);
  switch (exist) {
  case CFES_ON_DISK:
    ddio_MakePath(fullpath, LocalScriptDir, modfilename, NULL);
    return -1;
    break;
  case CFES_IN_LIBRARY: {
    ASSERT(OSIRIS_Extracted_script_dir);
    if (!OSIRIS_Extracted_script_dir)
      return -2;

    // search through our list of extracted files to find it...
    for (int i = 0; i < MAX_LOADED_MODULES; i++) {
      if (OSIRIS_Extracted_scripts[i].flags & OESF_USED) {
        if (!stricmp(basename, OSIRIS_Extracted_scripts[i].real_filename)) {
          // this is it
          ddio_MakePath(fullpath, OSIRIS_Extracted_script_dir, OSIRIS_Extracted_scripts[i].temp_filename, NULL);
          return i;
        }
      }
    }
    Int3(); // this file was supposed to exist
  } break;
  default:
    *fullpath = '\0';
    return -2;
  };
  return -2;
}

//	Osiris_LoadLevelModule
//	Purpose:
//		Given a module name, it will attempt to load the module as a level module.  If it succeeds
//	it will return the id of the module where it has been loaded.  If the module was already loaded
//	before calling this function, it will return the id to where the module is, and will not reload
//	the module.  Returns -1 if the module does not exist.  Returns -2 if the module couldn't initialize.
//	Returns -3 if the module is not a level module. Returns -4 if no module slots are available.
int Osiris_LoadLevelModule(char *module_name) {
  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return -2;
  }

  ASSERT(!tOSIRISCurrentLevel.level_loaded);
  if (tOSIRISCurrentLevel.level_loaded) {
    mprintf(0, "OSIRIS: Trying to load a level dll, when one has already been loaded\n");
    return tOSIRISCurrentLevel.dll_id;
  }

  int loaded_id;
  loaded_id = Osiris_FindLoadedModule(module_name);
  if (loaded_id != -1) {
    // the module is already loaded
    OSIRIS_loaded_modules[loaded_id].reference_count++;
    if (Show_osiris_debug) {
      mprintf(0, "OSIRIS: Level Module (%s) reference count increased to %d\n", module_name,
               OSIRIS_loaded_modules[loaded_id].reference_count);
    }
    return loaded_id;
  }

  // the module hasn't been loaded yet, find an available slot.
  for (loaded_id = 0; loaded_id < MAX_LOADED_MODULES; loaded_id++) {
    if (!(OSIRIS_loaded_modules[loaded_id].flags & OSIMF_INUSE)) {
      // we found a free slot
      break;
    }
  }

  if (loaded_id >= MAX_LOADED_MODULES) {
    // no slots available
    mprintf(0, "OSIRIS: Osiris_LoadLevelModule(%s): No available slots\n", module_name);
    Int3();
    return -4;
  }

  OSIRIS_loaded_modules[loaded_id].flags = 0; // set this to 0 as we fill in the data

  char fullpath[_MAX_PATH], basename[_MAX_PATH];
  int ret_val = _get_full_path_to_module(module_name, fullpath, basename);
  switch (ret_val) {
  case -2:
    // the module does not exist
    mprintf(0, "OSIRIS: Osiris_LoadLevelModule(%s): Module doesn't exist\n", module_name);
    return -1;
    break;
  case -1:
    // the module is in data\scripts
    break;
  default:
    // the module was an extracted file
    mprintf(0, "OSIRIS: Found module (%s) in a temp file\n", basename);
    OSIRIS_loaded_modules[loaded_id].flags |= OSIMF_INTEMPDIR;
    OSIRIS_loaded_modules[loaded_id].extracted_id = ret_val;
    break;
  }

  // the module exists, now attempt to load it
  if (!mod_LoadModule(&OSIRIS_loaded_modules[loaded_id].mod, fullpath)) {
    // there was an error trying to load the module
    mprintf(0, "OSIRIS: Osiris_LoadLevelModule(%s): Unable to load module\n", module_name);
    Int3();
    return -3;
  }

  // the module has loaded, attempt to import all the level functions
  tOSIRISModule *osm = &OSIRIS_loaded_modules[loaded_id];
  module *mod = &osm->mod;

  // there are 9 functions we need to import
  // InitializeDLL@4
  // ShutdownDLL@0
  // GetGOScriptID@4
  // GetTriggerScriptID@4
  // GetCOScriptList@8
  // CreateInstance@4
  // DestroyInstance@8
  // CallInstanceEvent@16
  // SaveRestoreState@8

  osm->InitializeDLL = (InitializeDLL_fp)mod_GetSymbol(mod, "InitializeDLL", 4);
  osm->ShutdownDLL = (ShutdownDLL_fp)mod_GetSymbol(mod, "ShutdownDLL", 0);
  osm->GetGOScriptID = (GetGOScriptID_fp)mod_GetSymbol(mod, "GetGOScriptID", 8);
  osm->GetTriggerScriptID = (GetTriggerScriptID_fp)mod_GetSymbol(mod, "GetTriggerScriptID", 8);
  osm->GetCOScriptList = (GetCOScriptList_fp)mod_GetSymbol(mod, "GetCOScriptList", 8);
  osm->CreateInstance = (CreateInstance_fp)mod_GetSymbol(mod, "CreateInstance", 4);
  osm->DestroyInstance = (DestroyInstance_fp)mod_GetSymbol(mod, "DestroyInstance", 8);
  osm->CallInstanceEvent = (CallInstanceEvent_fp)mod_GetSymbol(mod, "CallInstanceEvent", 16);
  osm->SaveRestoreState = (SaveRestoreState_fp)mod_GetSymbol(mod, "SaveRestoreState", 8);

  osm->flags |= OSIMF_INUSE | OSIMF_LEVEL;
  osm->module_name = mem_strdup(basename);
  osm->reference_count = 1;

#ifdef OSIRISDEBUG
  ASSERT(osm->RefRoot == NULL);
  osm->RefRoot = NULL;
#endif

  // make sure all of the functions imported ok
  if (!osm->InitializeDLL || !osm->ShutdownDLL || !osm->GetGOScriptID || !osm->GetTriggerScriptID ||
      !osm->GetCOScriptList || !osm->CreateInstance || !osm->DestroyInstance || !osm->SaveRestoreState ||
      !osm->CallInstanceEvent) {
    // there was an error importing a function
    mprintf(0, "OSIRIS: Osiris_LoadLevelModule(%s) couldn't import function.\n", module_name);
    Int3();
    osm->flags = 0;
    if (osm->module_name)
      mem_free(osm->module_name);
    osm->module_name = NULL;
    mod_FreeModule(mod);
    return -3;
  }

  // check to see if there is a corresponding string table to load
  char stringtablename[_MAX_PATH];
  strcpy(stringtablename, basename);
  strcat(stringtablename, ".str");

  if (cfexist(stringtablename)) {
    // there is a string table, load it up
    bool ret = CreateStringTable(stringtablename, &osm->string_table, &osm->strings_loaded);
    if (!ret) {
      mprintf(0, "OSIRIS: Unable to load string table (%s) for (%s)\n", stringtablename, basename);
      Int3();
      osm->string_table = NULL;
      osm->strings_loaded = 0;
    }
  } else {
    osm->string_table = NULL;
    osm->strings_loaded = 0;
  }

  Osiris_module_init.string_count = osm->strings_loaded;
  Osiris_module_init.string_table = osm->string_table;
  Osiris_module_init.module_is_static = false;
  Osiris_module_init.script_identifier = osm->module_name;
  Osiris_module_init.module_identifier = loaded_id;

  // when we get to this point we nearly have a loaded module, we just need to initialize it
  if (!osm->InitializeDLL(&Osiris_module_init)) {
    // there was an error initializing the module
    mprintf(0, "OSIRIS: Osiris_LoadLevelModule(%s) error initializing module.\n", basename);
    if (osm->string_table) {
      DestroyStringTable(osm->string_table, osm->strings_loaded);
    }
    osm->flags = 0;
    if (osm->module_name)
      mem_free(osm->module_name);
    osm->module_name = NULL;
    osm->string_table = NULL;
    osm->strings_loaded = 0;
    mod_FreeModule(mod);
    return -2;
  }

  // intialize trigger scripts
  for (int i = 0; i < Num_triggers; i++) {
    int script_id;
    void *instance;

    Triggers[i].osiris_script.script_id = -1;
    Triggers[i].osiris_script.script_instance = NULL;

    script_id = osm->GetTriggerScriptID(Triggers[i].roomnum, Triggers[i].facenum);
    if (script_id != -1) {
      // the trigger was found
      instance = osm->CreateInstance(script_id);
      if (!instance) {
        mprintf(0, "OSIRIS: Unable to create instance for trigger script (%d)\n", i);
      } else {
        Triggers[i].osiris_script.script_id = script_id;
        Triggers[i].osiris_script.script_instance = instance;
      }
    }
  }

  // we have a successful module load
  tOSIRISCurrentLevel.level_loaded = true;
  tOSIRISCurrentLevel.dll_id = loaded_id;
  tOSIRISCurrentLevel.num_customs = OSIRIS_loaded_modules[loaded_id].GetCOScriptList(
      &tOSIRISCurrentLevel.custom_handles, &tOSIRISCurrentLevel.custom_ids);
  tOSIRISCurrentLevel.instance =
      OSIRIS_loaded_modules[loaded_id].CreateInstance(0); // level scripts always have id of 0 in a level dll

  mprintf(0, "OSIRIS: Level Module (%s) loaded successfully (%d custom handles)\n", basename,
           tOSIRISCurrentLevel.num_customs);
  Osiris_level_script_loaded = true;
  return loaded_id;
}

//	Osiris_LoadGameModule
//	Purpose:
//		Given a module name, it will attempt to load the module as a game module.  If it succeeds
//	it will return the id of the module where it has been loaded.  If the module was already loaded
//	before calling this function, it will return the id to where the module is, and will not reload
//	the module.  Returns -1 if the module does not exist.  Returns -2 if the module couldn't initialize.
//	Returns -3 if the module is not a game module. Returns -4 if no module slots are available.
int Osiris_LoadGameModule(char *module_name) {
  if (module_name[0] == '\0') {
    return -1;
  }

  int loaded_id;
  loaded_id = Osiris_FindLoadedModule(module_name);
  if (loaded_id != -1) {
    // the module is already loaded
    OSIRIS_loaded_modules[loaded_id].reference_count++;
    if (Show_osiris_debug) {
      mprintf(0, "OSIRIS: Game Module (%s) reference count increased to %d\n", module_name,
               OSIRIS_loaded_modules[loaded_id].reference_count);
    }
    return loaded_id;
  }

  // the module hasn't been loaded yet, find an available slot.
  for (loaded_id = 0; loaded_id < MAX_LOADED_MODULES; loaded_id++) {
    if (!(OSIRIS_loaded_modules[loaded_id].flags & OSIMF_INUSE)) {
      // we found a free slot
      break;
    }
  }

  if (loaded_id >= MAX_LOADED_MODULES) {
    // no slots available
    mprintf(0, "OSIRIS: Osiris_LoadGameModule(%s): No available slots\n", module_name);
    Int3();
    return -4;
  }

  OSIRIS_loaded_modules[loaded_id].flags = 0; // set this to 0 as we fill in the data

  char fullpath[_MAX_PATH], basename[_MAX_PATH];
  int ret_val = _get_full_path_to_module(module_name, fullpath, basename);
  switch (ret_val) {
  case -2:
    // the module does not exist
    mprintf(0, "OSIRIS: Osiris_LoadLevelModule(%s): Module doesn't exist\n", module_name);
    return -1;
    break;
  case -1:
    // the module is in data\scripts
    break;
  default:
    // the module was an extracted file
    mprintf(0, "OSIRIS: Found module (%s) in a temp file\n", basename);
    OSIRIS_loaded_modules[loaded_id].flags |= OSIMF_INTEMPDIR;
    OSIRIS_loaded_modules[loaded_id].extracted_id = ret_val;
    break;
  }

  // the module exists, now attempt to load it
  if (!mod_LoadModule(&OSIRIS_loaded_modules[loaded_id].mod, fullpath)) {
    // there was an error trying to load the module
    mprintf(0, "OSIRIS: Osiris_LoadGameModule(%s): Unable to load module\n", module_name);
    Int3();
    return -3;
  }

  // the module has loaded, attempt to import all the level functions
  tOSIRISModule *osm = &OSIRIS_loaded_modules[loaded_id];
  module *mod = &osm->mod;

  // there are 7 functions we need to import
  // InitializeDLL@4
  // ShutdownDLL@0
  // GetGOScriptID@4
  // CreateInstance@4
  // DestroyInstance@8
  // CallInstanceEvent@16
  // SaveRestoreState@8

  osm->InitializeDLL = (InitializeDLL_fp)mod_GetSymbol(mod, "InitializeDLL", 4);
  osm->ShutdownDLL = (ShutdownDLL_fp)mod_GetSymbol(mod, "ShutdownDLL", 0);
  osm->GetGOScriptID = (GetGOScriptID_fp)mod_GetSymbol(mod, "GetGOScriptID", 8);
  osm->GetTriggerScriptID = NULL;
  osm->GetCOScriptList = NULL;
  osm->CreateInstance = (CreateInstance_fp)mod_GetSymbol(mod, "CreateInstance", 4);
  osm->DestroyInstance = (DestroyInstance_fp)mod_GetSymbol(mod, "DestroyInstance", 8);
  osm->CallInstanceEvent = (CallInstanceEvent_fp)mod_GetSymbol(mod, "CallInstanceEvent", 16);
  osm->SaveRestoreState = (SaveRestoreState_fp)mod_GetSymbol(mod, "SaveRestoreState", 8);

  osm->flags |= OSIMF_INUSE;
  osm->module_name = mem_strdup(basename);
  osm->reference_count = 1;

#ifdef OSIRISDEBUG
  ASSERT(osm->RefRoot == NULL);
  osm->RefRoot = NULL;
#endif

  // make sure all of the functions imported ok
  if (!osm->InitializeDLL || !osm->ShutdownDLL || !osm->GetGOScriptID || !osm->CreateInstance ||
      !osm->DestroyInstance || !osm->SaveRestoreState || !osm->CallInstanceEvent) {
    // there was an error importing a function
    mprintf(0, "OSIRIS: Osiris_LoadGameModule(%s) couldn't import function.\n", basename);
    Int3();
    osm->flags = 0;
    if (osm->module_name)
      mem_free(osm->module_name);
    osm->module_name = NULL;
    mod_FreeModule(mod);
    return -3;
  }

  // check to see if there is a corresponding string table to load
  char stringtablename[_MAX_PATH];
  strcpy(stringtablename, basename);
  strcat(stringtablename, ".str");

  if (cfexist(stringtablename)) {
    // there is a string table, load it up
    bool ret = CreateStringTable(stringtablename, &osm->string_table, &osm->strings_loaded);
    if (!ret) {
      mprintf(0, "OSIRIS: Unable to load string table (%s) for (%s)\n", stringtablename, basename);
      Int3();
      osm->string_table = NULL;
      osm->strings_loaded = 0;
    }
  } else {
    osm->string_table = NULL;
    osm->strings_loaded = 0;
  }
  Osiris_module_init.string_count = osm->strings_loaded;
  Osiris_module_init.string_table = osm->string_table;
  Osiris_module_init.module_is_static = false; // set this to false to avoid a fake true
  Osiris_module_init.script_identifier = osm->module_name;
  Osiris_module_init.module_identifier = loaded_id;

  // when we get to this point we nearly have a loaded module, we just need to initialize it
  if (!osm->InitializeDLL(&Osiris_module_init)) {
    // there was an error initializing the module
    mprintf(0, "OSIRIS: Osiris_LoadGameModule(%s) error initializing module.\n", basename);
    if (osm->string_table) {
      DestroyStringTable(osm->string_table, osm->strings_loaded);
    }
    osm->string_table = NULL;
    osm->strings_loaded = 0;
    osm->flags = 0;
    if (osm->module_name)
      mem_free(osm->module_name);
    osm->module_name = NULL;
    mod_FreeModule(mod);
    return -2;
  }

  if (Osiris_module_init.module_is_static) {
    // the module is requesting to be static
    mprintf(0, "OSIRIS: Module (%s) is requesting to be static\n", osm->module_name);
    osm->flags |= OSIMF_NOUNLOAD;
  }

  // we have a successful module load
  mprintf(0, "OSIRIS: Game Module (%s) loaded successfully\n", basename);
  return loaded_id;
}

//	Osiris_LoadMissionModule
//	Purpose:
//		It will attempt to load the module as a game module.  If it succeeds
//	it will return the id of the module where it has been loaded.  If the module was already loaded
//	before calling this function, it will return the id to where the module is, and will not reload
//	the module.  Returns -1 if the module does not exist.  Returns -2 if the module couldn't initialize.
//	Returns -3 if the module is not a game module. Returns -4 if no module slots are available.
//	This technically doesn't load a mission module, as it should already be loaded by
//	Descent 3 prior.
int Osiris_LoadMissionModule(module *module_handle, const char *filename) {
  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return -1;
  }

  if (!module_handle) {
    return -1;
  }

  int loaded_id;

  // find an available slot.
  for (loaded_id = 0; loaded_id < MAX_LOADED_MODULES; loaded_id++) {
    if (!(OSIRIS_loaded_modules[loaded_id].flags & OSIMF_INUSE)) {
      // we found a free slot
      break;
    }
  }

  if (loaded_id >= MAX_LOADED_MODULES) {
    // no slots available
    mprintf(0, "OSIRIS: Osiris_LoadMissionModule(%s): No available slots\n", filename);
    Int3();
    return -4;
  }

  // make sure the module exists so we can load it
  if (!module_handle->handle) {
    // the module does not exist
    mprintf(0, "OSIRIS: Osiris_LoadMissionModule(%s): Module doesn't exist\n", filename);
    // Int3();
    return -1;
  }

  // the module has loaded, attempt to import all the game functions
  tOSIRISModule *osm = &OSIRIS_loaded_modules[loaded_id];
  memcpy(&osm->mod, module_handle, sizeof(module));
  module *mod = &osm->mod;

  // there are 5 functions we need to import
  // GetGOScriptID@4
  // CreateInstance@4
  // DestroyInstance@8
  // CallInstanceEvent@16
  // SaveRestoreState@8

  osm->InitializeDLL = NULL;
  osm->ShutdownDLL = NULL;
  osm->GetTriggerScriptID = NULL;
  osm->GetCOScriptList = NULL;
  osm->GetGOScriptID = (GetGOScriptID_fp)mod_GetSymbol(mod, "GetGOScriptID", 8);
  osm->CreateInstance = (CreateInstance_fp)mod_GetSymbol(mod, "CreateInstance", 4);
  osm->DestroyInstance = (DestroyInstance_fp)mod_GetSymbol(mod, "DestroyInstance", 8);
  osm->CallInstanceEvent = (CallInstanceEvent_fp)mod_GetSymbol(mod, "CallInstanceEvent", 16);
  osm->SaveRestoreState = (SaveRestoreState_fp)mod_GetSymbol(mod, "SaveRestoreState", 8);

  osm->flags = OSIMF_INUSE | OSIMF_DLLELSEWHERE;
  osm->module_name = mem_strdup(filename);
  osm->reference_count = 1;

#ifdef OSIRISDEBUG
  ASSERT(osm->RefRoot == NULL);
  osm->RefRoot = NULL;
#endif

  // make sure all of the functions imported ok
  if (!osm->GetGOScriptID || !osm->CreateInstance || !osm->DestroyInstance || !osm->SaveRestoreState ||
      !osm->CallInstanceEvent) {
    // there was an error importing a function
    mprintf(0, "OSIRIS: Osiris_LoadMissionModule(%s) couldn't import function.\n", filename);
    osm->flags = 0;
    tOSIRISCurrentMission.mission_loaded = false;
    Int3();
    // mod_FreeModule(mod);	//don't unload it! it's needed by the mission
    return -3;
  }

  // we have a successful module load
  tOSIRISCurrentMission.mission_loaded = true;
  tOSIRISCurrentMission.dll_id = loaded_id;
  if (Show_osiris_debug) {
    mprintf(0, "OSIRIS: Mission Game Module (%s) loaded successfully\n", filename);
  }
  return loaded_id;
}

//	Osiris_UnloadMissionModule
//	Purpose:
//		Instead of saving the handle returned from Osiris_LoadMissionModule() and calling
//	Osiris_UnloadModule() with that handle, you can just call this, instead of the call
//	to Osiris_UnloadModule().
void Osiris_UnloadMissionModule(void) {
  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return;
  }

  if (!tOSIRISCurrentMission.mission_loaded)
    return;

  int dll_id = tOSIRISCurrentMission.dll_id;

  Osiris_FreeModule(dll_id);
}

//	Osiris_BindScriptsToObject
//	Purpose:
//		Call this function after an object has been created to bind all the scripts associated
//	with it to the object.  This function must be called near the end of it's initialization,
//	to make sure that all fields have been filled in.  This function does not call any events.
//	This function will also load any dll's needed for it's game script.
//	returns false if nothing was bound.
bool Osiris_BindScriptsToObject(object *obj) {
  ASSERT(obj->osiris_script == NULL);
  if (obj->osiris_script) // already has a script bound!
    return true;

  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return false;
  }

  // make sure the object is valid
  if (!CANBEASSIGNEDSCRIPT(obj)) {
    // invalid object
    return false;
  }
  int real_type;
  real_type = (obj->type == OBJ_DUMMY) ? obj->dummy_type : obj->type;

  if (!CANTYPEBEASSIGNEDSCRIPT(real_type)) {
    // invalid type
    return false;
  }

  int dll_id, gos_id;
  void *gos_instance;
  tOSIRISScript *os;

  bool isdoor = (bool)(real_type == OBJ_DOOR);
  bool iscustomonly = (bool)HAVECUSTOMONLY(real_type);
  char *default_module_name;
  char *page_name;

  if (iscustomonly) {
    // this object can only have a custom script for it (i.e. OBJ_CAMERA)
    default_module_name = NULL;
    page_name = NULL;
  } else {
    if (isdoor) {
      default_module_name = Doors[obj->id].module_name;
      page_name = Doors[obj->id].name;
    } else {
      if (obj->custom_default_module_name) {
        // we have a custom default script
        default_module_name = obj->custom_default_module_name;
      } else {
        // use what was set in Object_info
        default_module_name = Object_info[obj->id].module_name;
      }

      if (obj->custom_default_script_name) {
        // we have a custom default script
        page_name = obj->custom_default_script_name;
      } else {
        // use what was set in Object_info
        if (Object_info[obj->id].script_name_override[0] != '\0')
          page_name = Object_info[obj->id].script_name_override;
        else
          page_name = Object_info[obj->id].name;
      }
    }
  }

  if (!iscustomonly) {
    // this object can have a default script
    ASSERT(default_module_name);
    ASSERT(page_name);

    // load up the dllname associated with the object and get the id
    dll_id = Osiris_LoadGameModule(default_module_name);
    if (dll_id < 0) {
      // there was an error finding this object's dll
      if (Show_osiris_debug) {
        mprintf(0, "OSIRIS: Unable to load module (%s) to bind to object (%s)\n", default_module_name, page_name);
      }
    } else {
      // allocate the memory for the object's scripts
      obj->osiris_script = (tOSIRISScript *)mem_malloc(sizeof(tOSIRISScript));
      if (!obj->osiris_script) {
        // out of memory
        mprintf(0, "OSIRIS: Out of memory trying to bind script\n");
        return false;
      }

      obj->osiris_script->default_script.script_instance = NULL;
      obj->osiris_script->custom_script.script_instance = NULL;
      obj->osiris_script->mission_script.script_instance = NULL;
      obj->osiris_script->level_script.script_instance = NULL;
      os = obj->osiris_script;

      // we have the module loaded for the object, now we need to setup it's default script
      gos_id = OSIRIS_loaded_modules[dll_id].GetGOScriptID(page_name, isdoor);

      if (gos_id == -1) {
        // the default script for this object does not exist in the dll set for it
        mprintf(0, "OSIRIS: Unable to find GOS ID for (%s) in (%s)!\n", page_name, default_module_name);
        Int3();
        Osiris_UnloadModule(dll_id);
      } else {

        // we now have the GOS ID for the script.  All future communication with the default script-dll is
        // to use this GOS ID.  Now try to create an instance of the object.  Hopefully we have enough memory.
        gos_instance = OSIRIS_loaded_modules[dll_id].CreateInstance(gos_id);
        if (!gos_instance) {
          // we had an error obtaining the instance of the GOS...ugh
          mprintf(0, "OSIRIS: Unable to create GOS instance for (%s)\n", page_name);
          Int3();
          Osiris_UnloadModule(dll_id);
        } else {

          // all looks good! we're guaranteed to have at least one script for this object
          // setup default script values
          os->default_script.DLLID = dll_id;
          os->default_script.script_id = gos_id;
          os->default_script.script_instance = gos_instance;

          // add to the list for this object
#ifdef OSIRISDEBUG
          tRefObj *node;
          if (OSIRIS_loaded_modules[dll_id].RefRoot == NULL) {
            node = OSIRIS_loaded_modules[dll_id].RefRoot = (tRefObj *)mem_malloc(sizeof(tRefObj));
          } else {
            node = OSIRIS_loaded_modules[dll_id].RefRoot;
            while (node->next)
              node = node->next;
            node->next = (tRefObj *)mem_malloc(sizeof(tRefObj));
            node = node->next;
          }
          node->objnum = OBJNUM(obj);
          node->id = obj->id;
          node->dummy = (obj->type == OBJ_DUMMY) ? true : false;
          node->type = (node->dummy == false) ? obj->type : obj->dummy_type;
          node->next = NULL;
#endif
        }
      }
    }
  }

  // now check for a GOS and COS in the level dll (if available)
  if (tOSIRISCurrentLevel.level_loaded) {
    dll_id = tOSIRISCurrentLevel.dll_id;

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      // check first for a GOS
      if (!iscustomonly) {
        // this script can have a GOS in the level script
        ASSERT(page_name);

        gos_id = OSIRIS_loaded_modules[dll_id].GetGOScriptID(page_name, isdoor);
        if (gos_id != -1) {
          if (!obj->osiris_script) {
            // we need to allocate memory for a script
            obj->osiris_script = (tOSIRISScript *)mem_malloc(sizeof(tOSIRISScript));
            if (!obj->osiris_script) {
              // out of memory
              mprintf(0, "OSIRIS: Out of memory trying to bind script\n");
              return false;
            }

            obj->osiris_script->default_script.script_instance = NULL;
            obj->osiris_script->custom_script.script_instance = NULL;
            obj->osiris_script->mission_script.script_instance = NULL;
            obj->osiris_script->level_script.script_instance = NULL;
          }
          os = obj->osiris_script;

          // ok, the level dll has a script for us
          gos_instance = OSIRIS_loaded_modules[dll_id].CreateInstance(gos_id);
          if (!gos_instance) {
            // we had an error obtaining the instance of the GOS...ick
            mprintf(0, "OSIRIS: Unable to create GOS instance from level dll for (%s)\n", page_name);
            Int3();
          } else {
            // ok, we got a valid instance
            os->level_script.DLLID = dll_id;
            os->level_script.script_id = gos_id;
            os->level_script.script_instance = gos_instance;

#ifdef OSIRISDEBUG
            tRefObj *node;
            if (OSIRIS_loaded_modules[dll_id].RefRoot == NULL) {
              node = OSIRIS_loaded_modules[dll_id].RefRoot = (tRefObj *)mem_malloc(sizeof(tRefObj));
            } else {
              node = OSIRIS_loaded_modules[dll_id].RefRoot;
              while (node->next)
                node = node->next;
              node->next = (tRefObj *)mem_malloc(sizeof(tRefObj));
              node = node->next;
            }
            node->objnum = OBJNUM(obj);
            node->id = obj->id;
            node->dummy = (obj->type == OBJ_DUMMY) ? true : false;
            node->type = (node->dummy == false) ? obj->type : obj->dummy_type;
            node->next = NULL;
#endif
          }
        }
      } // end if(!iscustomonly)

      // now check to see if we have a custom script for our handle
      int i;
      for (i = 0; i < tOSIRISCurrentLevel.num_customs; i++) {
        if (obj->handle == tOSIRISCurrentLevel.custom_handles[i]) {
          // we found a matching handle, connect it to the script
          gos_id = tOSIRISCurrentLevel.custom_ids[i];
          if (gos_id != -1) {

            if (!obj->osiris_script) {
              // we need to allocate memory for a script
              obj->osiris_script = (tOSIRISScript *)mem_malloc(sizeof(tOSIRISScript));
              if (!obj->osiris_script) {
                // out of memory
                mprintf(0, "OSIRIS: Out of memory trying to bind script\n");
                return false;
              }

              obj->osiris_script->default_script.script_instance = NULL;
              obj->osiris_script->custom_script.script_instance = NULL;
              obj->osiris_script->mission_script.script_instance = NULL;
              obj->osiris_script->level_script.script_instance = NULL;
            }
            os = obj->osiris_script;

            gos_instance = OSIRIS_loaded_modules[dll_id].CreateInstance(gos_id);
            if (!gos_instance) {
              // we had an error obtaining the instance of the COS...doh!
              mprintf(0, "OSIRIS: Unable to create COS instance from level dll for (%s)\n",
                       (page_name) ? (page_name) : "<No Name>");
              Int3();
            } else {
              // ok, everything is valid
              os->custom_script.DLLID = dll_id;
              os->custom_script.script_id = gos_id;
              os->custom_script.script_instance = gos_instance;

#ifdef OSIRISDEBUG
              tRefObj *node;
              if (OSIRIS_loaded_modules[dll_id].RefRoot == NULL) {
                node = OSIRIS_loaded_modules[dll_id].RefRoot = (tRefObj *)mem_malloc(sizeof(tRefObj));
              } else {
                node = OSIRIS_loaded_modules[dll_id].RefRoot;
                while (node->next)
                  node = node->next;
                node->next = (tRefObj *)mem_malloc(sizeof(tRefObj));
                node = node->next;
              }
              node->objnum = OBJNUM(obj);
              node->id = obj->id;
              node->dummy = (obj->type == OBJ_DUMMY) ? true : false;
              node->type = (node->dummy == false) ? obj->type : obj->dummy_type;
              node->next = NULL;
#endif

              if (iscustomonly) {
                mprintf(0, "OSIRIS: Attached custom script to 'custom only' object 0x%x\n", obj->handle);
              }
            }
          }
        }
      }
    }
  }

  // last we need to check the mission dll
  if (!iscustomonly) {
    // this object can have a script in the mission dll
    ASSERT(page_name);

    if (tOSIRISCurrentMission.mission_loaded) {
      dll_id = tOSIRISCurrentMission.dll_id;

      ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
      if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

        // check first for a GOS
        gos_id = OSIRIS_loaded_modules[dll_id].GetGOScriptID(page_name, isdoor);
        if (gos_id != -1) {
          if (!obj->osiris_script) {
            // we need to allocate memory for a script
            obj->osiris_script = (tOSIRISScript *)mem_malloc(sizeof(tOSIRISScript));
            if (!obj->osiris_script) {
              // out of memory
              mprintf(0, "OSIRIS: Out of memory trying to bind script\n");
              return false;
            }

            obj->osiris_script->default_script.script_instance = NULL;
            obj->osiris_script->custom_script.script_instance = NULL;
            obj->osiris_script->mission_script.script_instance = NULL;
            obj->osiris_script->level_script.script_instance = NULL;
          }
          os = obj->osiris_script;

          // ok, the mission dll has a script for us
          gos_instance = OSIRIS_loaded_modules[dll_id].CreateInstance(gos_id);
          if (!gos_instance) {
            // we had an error obtaining the instance of the GOS...ick
            mprintf(0, "OSIRIS: Unable to create GOS instance from mission dll for (%s)\n", page_name);
            Int3();
          } else {
            // ok, we got a valid instance
            os->mission_script.DLLID = dll_id;
            os->mission_script.script_id = gos_id;
            os->mission_script.script_instance = gos_instance;

#ifdef OSIRISDEBUG
            tRefObj *node;
            if (OSIRIS_loaded_modules[dll_id].RefRoot == NULL) {
              node = OSIRIS_loaded_modules[dll_id].RefRoot = (tRefObj *)mem_malloc(sizeof(tRefObj));
            } else {
              node = OSIRIS_loaded_modules[dll_id].RefRoot;
              while (node->next)
                node = node->next;
              node->next = (tRefObj *)mem_malloc(sizeof(tRefObj));
              node = node->next;
            }
            node->objnum = OBJNUM(obj);
            node->id = obj->id;
            node->dummy = (obj->type == OBJ_DUMMY) ? true : false;
            node->type = (node->dummy == false) ? obj->type : obj->dummy_type;
            node->next = NULL;
#endif
          }
        }
      }
    }
  } // end if(!iscustomonly)

  return true;
}

//	Osiris_DetachScriptsFromObject
//	Purpose:
//		Call this function when an object is about to be destroyed.  This will unbind and remove
//	all scripts associated with that object.  This function does not call any events.
void Osiris_DetachScriptsFromObject(object *obj) {
  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return;
  }

  // make sure the object is valid
  if (!CANHAVEANYSCRIPT(obj)) {
    // invalid object
    return;
  }

  if (!obj->osiris_script) {
    return;
  }

  // free the memory for the allocated script
  tOSIRISSCRIPTID osid;
  osid.objhandle = obj->handle;
  osid.type = OBJECT_SCRIPT;
  Osiris_FreeMemoryForScript(&osid);

  int dll_id;
  tOSIRISScript *os;

  os = obj->osiris_script;

  // free up the scripts for the object, starting with it's default script
  if (os->default_script.script_instance) {
    // first we need to free the instance
    dll_id = os->default_script.DLLID;

#ifdef OSIRISDEBUG
    tRefObj *prev = NULL, *node = OSIRIS_loaded_modules[dll_id].RefRoot;
    while (node) {
      if (node->objnum == OBJNUM(obj)) {
        // free this node
        if (prev)
          prev->next = node->next;
        else {
          ASSERT(node == OSIRIS_loaded_modules[dll_id].RefRoot);
          OSIRIS_loaded_modules[dll_id].RefRoot = node->next;
        }

        mem_free(node);
        break;
      }
      prev = node;
      node = node->next;
    }
    ASSERT(node); // make sure we found the node
#endif

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      OSIRIS_loaded_modules[dll_id].DestroyInstance(os->default_script.script_id, os->default_script.script_instance);

      // now decrement the dll's count
      Osiris_UnloadModule(dll_id);
    }

    os->default_script.DLLID = 0;
    os->default_script.script_id = 0;
    os->default_script.script_instance = NULL;
  }

  // now check for the level script
  if (os->level_script.script_instance) {
    // free the instance
    dll_id = os->level_script.DLLID;

#ifdef OSIRISDEBUG
    tRefObj *prev = NULL, *node = OSIRIS_loaded_modules[dll_id].RefRoot;
    while (node) {
      if (node->objnum == OBJNUM(obj)) {
        // free this node
        if (prev)
          prev->next = node->next;
        else {
          ASSERT(node == OSIRIS_loaded_modules[dll_id].RefRoot);
          OSIRIS_loaded_modules[dll_id].RefRoot = node->next;
        }

        mem_free(node);
        break;
      }
      prev = node;
      node = node->next;
    }
    ASSERT(node); // make sure we found the node
#endif

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      OSIRIS_loaded_modules[dll_id].DestroyInstance(os->level_script.script_id, os->level_script.script_instance);
    }

    os->level_script.DLLID = 0;
    os->level_script.script_id = 0;
    os->level_script.script_instance = NULL;
  }

  // check for an attached custom script
  if (os->custom_script.script_instance) {
    // free the instance
    dll_id = os->custom_script.DLLID;

#ifdef OSIRISDEBUG
    tRefObj *prev = NULL, *node = OSIRIS_loaded_modules[dll_id].RefRoot;
    while (node) {
      if (node->objnum == OBJNUM(obj)) {
        // free this node
        if (prev)
          prev->next = node->next;
        else {
          ASSERT(node == OSIRIS_loaded_modules[dll_id].RefRoot);
          OSIRIS_loaded_modules[dll_id].RefRoot = node->next;
        }

        mem_free(node);
        break;
      }
      prev = node;
      node = node->next;
    }
    ASSERT(node); // make sure we found the node
#endif

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      OSIRIS_loaded_modules[dll_id].DestroyInstance(os->custom_script.script_id, os->custom_script.script_instance);
    }

    os->custom_script.DLLID = 0;
    os->custom_script.script_id = 0;
    os->custom_script.script_instance = NULL;
  }

  // check for a mission dll script
  if (os->mission_script.script_instance) {
    // free the instance
    dll_id = os->mission_script.DLLID;

#ifdef OSIRISDEBUG
    tRefObj *prev = NULL, *node = OSIRIS_loaded_modules[dll_id].RefRoot;
    while (node) {
      if (node->objnum == OBJNUM(obj)) {
        // free this node
        if (prev)
          prev->next = node->next;
        else {
          ASSERT(node == OSIRIS_loaded_modules[dll_id].RefRoot);
          OSIRIS_loaded_modules[dll_id].RefRoot = node->next;
        }

        mem_free(node);
        break;
      }
      prev = node;
      node = node->next;
    }
    ASSERT(node); // make sure we found the node
#endif

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      OSIRIS_loaded_modules[dll_id].DestroyInstance(os->mission_script.script_id, os->mission_script.script_instance);
    }

    os->mission_script.DLLID = 0;
    os->mission_script.script_id = 0;
    os->mission_script.script_instance = NULL;
  }

  // finally free up the memory allocated for the script struct
  mem_free(obj->osiris_script);
  obj->osiris_script = NULL;
}

//	Osiris_CallLevelEvent
//	Purpose:
//		Triggers an event for a level script.  Returns true if the default action should continue
//	to process.
bool Osiris_CallLevelEvent(int event, tOSIRISEventInfo *data) {
  if (!Osiris_level_script_loaded)
    return true;

  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return true;
  }

  if (!(Osiris_event_mask & OEM_LEVELS))
    return true; // level events are disabled

  if (!Osiris_IsEventEnabled(event))
    return true;

  int aux_event = -1;
  if (event == EVT_AI_NOTIFY) {
    switch (data->evt_ai_notify.notify_type) {
    case AIN_GOAL_COMPLETE:
      aux_event = EVT_AIN_GOALCOMPLETE;
      break;
    case AIN_GOAL_INVALID:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_GOAL_FAIL:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_GOAL_ERROR:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    }
  }

  if (tOSIRISCurrentLevel.level_loaded) {
    // there is a loaded level, get it's dll id and call it's event
    int dll_id = tOSIRISCurrentLevel.dll_id;
    void *instance = tOSIRISCurrentLevel.instance;

    if (instance) {
      data->me_handle = OBJECT_HANDLE_NONE; // its a level script!...no me
      int16_t ret;

      ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(0, instance, event, data);
      if (aux_event != -1) {
        // call child event
        ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(0, instance, aux_event, data);
      }

      return (bool)((ret & CONTINUE_DEFAULT) != 0);
    }
  }

  return true;
}

//	Osiris_CallTriggerEvent
//	Purpose:
//		Triggers an event for a trigger script.  Returns true if the default action should continue
//	to process.
bool Osiris_CallTriggerEvent(int trignum, int event, tOSIRISEventInfo *ei) {
  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return true;
  }

  if (!(Osiris_event_mask & OEM_TRIGGERS))
    return true; // trigger events are disabled

  if (!Osiris_IsEventEnabled(event))
    return true;

  if (trignum < 0 || trignum >= Num_triggers)
    return true;

  if (!tOSIRISCurrentLevel.level_loaded)
    return true;

  int dll_id, script_id;
  int aux_event = -1;
  void *instance;

  if (event == EVT_AI_NOTIFY) {
    switch (ei->evt_ai_notify.notify_type) {
    case AIN_GOAL_COMPLETE:
      aux_event = EVT_AIN_GOALCOMPLETE;
      break;
    case AIN_GOAL_INVALID:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_GOAL_FAIL:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_GOAL_ERROR:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    }
  }

  dll_id = tOSIRISCurrentLevel.dll_id;
  script_id = Triggers[trignum].osiris_script.script_id;
  instance = Triggers[trignum].osiris_script.script_instance;

  if (instance) {
    int16_t ret;
    ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(script_id, instance, event, ei);

    if (aux_event != -1) {
      // call child event
      ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(script_id, instance, aux_event, ei);
    }

    return (bool)((ret & CONTINUE_DEFAULT) != 0);
  }

  return true;
}

//	Osiris_EnableEvents
//	Purpose:
//		Enables the passed in mask of event types to be called
void Osiris_EnableEvents(uint8_t mask) { Osiris_event_mask |= mask; }

//	Osiris_DisableEvents
//	Purpose:
//		Disables the passed in mask of event types
void Osiris_DisableEvents(uint8_t mask) { Osiris_event_mask &= ~mask; }

//	Osiris_DisableCreateEvents
//	Purpose:
//		Disables any events involved when an object is created.  This is to be used for
//	Loading games/viewing demos, as so not to re-initialize good data.
void Osiris_DisableCreateEvents(void) { Osiris_create_events_disabled = true; }

//	Osiris_EnablesCreateEvents
//	Purpose:
//		Enables any events involved when an object is created.  This is to be used for
//	Loading games/viewing demos, as so not to re-initialize good data. (call when done with
// Osiris_DisableCreateEvents())
void Osiris_EnableCreateEvents(void) { Osiris_create_events_disabled = false; }

//	Osiris_IsEventEnabled
//	Purpose:
//		Returns true if the event is allowed to be called
bool Osiris_IsEventEnabled(int event) {
  switch (event) {
  case EVT_CREATED:
  case EVT_AI_INIT:
    return !Osiris_create_events_disabled;
    break;
  default:
    return true;
    break;
  }
  return true;
}

//	Osiris_CallEvent
//	Purpose:
//		Triggers an event for an object.  Pass in the event number and the associated
//	structure of data.  All events will be chained through the associated scripts of the
//	object (as long as they are available) in the order: custom script, level script,
//	mission script, and finally it's default script.  The chain breaks if one of the scripts
//	returns false on the call to their CallInstanceEvent().
bool Osiris_CallEvent(object *obj, int event, tOSIRISEventInfo *data) {
  if ((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)) {
    // no scripts for a client!
    return true;
  }

  if (!(Osiris_event_mask & OEM_OBJECTS))
    return true; // object events are disabled

  if (!Osiris_IsEventEnabled(event))
    return true;

  // make sure the object is valid
  if (!CANHAVEANYSCRIPT(obj)) {
    // invalid object
    return true;
  }

  if (!obj->osiris_script) {
    // mprintf(0,"OSIRIS: Unhandled event (%d) for object id=%d\n",event,obj->id);
    return true; // no script for this object...hmm
  }

  int dll_id;
  int aux_event = -1; // event value
  tOSIRISScript *os;
  int16_t ret = CONTINUE_CHAIN | CONTINUE_DEFAULT;

  if (event == EVT_AI_NOTIFY) {
    switch (data->evt_ai_notify.notify_type) {
    case AIN_OBJ_KILLED:
      aux_event = EVT_AIN_OBJKILLED;
      break;
    case AIN_SEE_TARGET:
      aux_event = EVT_AIN_SEEPLAYER;
      break;
    case AIN_WHIT_OBJECT:
      aux_event = EVT_AIN_WHITOBJECT;
      break;
    case AIN_GOAL_COMPLETE:
      aux_event = EVT_AIN_GOALCOMPLETE;
      break;
    case AIN_GOAL_INVALID:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_GOAL_FAIL:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_GOAL_ERROR:
      aux_event = EVT_AIN_GOALFAIL;
      break;
    case AIN_MELEE_HIT:
      aux_event = EVT_AIN_MELEE_HIT;
      break;
    case AIN_MELEE_ATTACK_FRAME:
      aux_event = EVT_AIN_MELEE_ATTACK_FRAME;
      break;
    case AIN_MOVIE_START:
      aux_event = EVT_AIN_MOVIE_START;
      break;
    case AIN_MOVIE_END:
      aux_event = EVT_AIN_MOVIE_END;
      break;
    }
  }

  os = obj->osiris_script;
  data->me_handle = obj->handle;

  if (os->custom_script.script_instance) {
    dll_id = os->custom_script.DLLID;

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (aux_event != -1) {
      // call the child event
      OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->custom_script.script_id, os->custom_script.script_instance,
                                                      aux_event, data);
    }

    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      // call the event
      ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->custom_script.script_id,
                                                            os->custom_script.script_instance, event, data);
    }
  }

  if ((ret & CONTINUE_CHAIN) && os->level_script.script_instance) {
    dll_id = os->level_script.DLLID;

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      if (aux_event != -1) {
        // call the child event
        OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->level_script.script_id, os->level_script.script_instance,
                                                        aux_event, data);
      }

      // call the event
      ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->level_script.script_id,
                                                            os->level_script.script_instance, event, data);
    }
  }

  if ((ret & CONTINUE_CHAIN) && os->mission_script.script_instance) {
    dll_id = os->mission_script.DLLID;

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {
      if (aux_event != -1) {
        // call the child event
        OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->mission_script.script_id,
                                                        os->mission_script.script_instance, aux_event, data);
      }

      // call the event
      ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->mission_script.script_id,
                                                            os->mission_script.script_instance, event, data);
    }
  }

  if ((ret & CONTINUE_CHAIN) && os->default_script.script_instance) {
    dll_id = os->default_script.DLLID;

    ASSERT(OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE);
    if (OSIRIS_loaded_modules[dll_id].flags & OSIMF_INUSE) {

      if (aux_event != -1) {
        // call the child event
        OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->default_script.script_id,
                                                        os->default_script.script_instance, aux_event, data);
      }

      // call the event
      ret = OSIRIS_loaded_modules[dll_id].CallInstanceEvent(os->default_script.script_id,
                                                            os->default_script.script_instance, event, data);
    }
  }

  return (bool)((ret & CONTINUE_DEFAULT) != 0);
}

#define MAX_OSIRIS_TIMERS 64
#define OITF_USED 0x0001
#define OITF_REPEATCALL 0x0002
#define OITF_TRIGGERTIMER 0x0004
#define OITF_LEVELTIMER 0x0008
#define OITF_CANCELONDEAD 0x0010
struct tOSIRISINTERNALTIMER {
  uint16_t flags;
  union {
    int objhandle;
    int trignum;
  };
  int id;
  int repeat_count;
  int objhandle_detonator;
  int handle;
  float timer_interval;
  float timer_next_signal;
  float timer_end;
};
tOSIRISINTERNALTIMER OsirisTimers[MAX_OSIRIS_TIMERS];

static inline int FORM_HANDLE(int counter, int slot) { return (((counter & 0xFFFFFF) << 8) | (slot & 0xFF)); }

static inline int GET_SLOT(int handle) { return (handle & 0xFF); }

int Osiris_timer_counter = 0;

//	Osiris_ProcessTimers
//	Purpose:
//		This function checks all timers currently running, if any need to be signaled it signals them.
void Osiris_ProcessTimers(void) {
  object *obj;
  bool signal, kill;
  tOSIRISEventInfo ei;

  for (int i = 0; i < MAX_OSIRIS_TIMERS; i++) {
    signal = false;
    kill = false;

    if (OsirisTimers[i].flags & OITF_USED) {

      if (OsirisTimers[i].flags & OITF_CANCELONDEAD) {
        obj = ObjGet(OsirisTimers[i].objhandle_detonator);
        if (!obj || (obj->type == OBJ_GHOST) ||
            (obj->type == OBJ_PLAYER && Players[obj->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
          // the detontator died...cancel the timer!
          OsirisTimers[i].flags &= ~OITF_USED;
          OsirisTimers[i].repeat_count = 0;

          tOSIRISEventInfo ei;
          ei.evt_timercancel.detonated = 1;
          ei.evt_timercancel.handle = OsirisTimers[i].handle;

          if (OsirisTimers[i].flags & OITF_TRIGGERTIMER) {
            Osiris_CallTriggerEvent(OsirisTimers[i].trignum, EVT_TIMERCANCEL, &ei);
          } else if (OsirisTimers[i].flags & OITF_LEVELTIMER) {
            Osiris_CallLevelEvent(EVT_TIMERCANCEL, &ei);
          } else {
            object *obj = ObjGet(OsirisTimers[i].objhandle);
            if (obj)
              Osiris_CallEvent(obj, EVT_TIMERCANCEL, &ei);
          }

          mprintf(0, "OSIRIS TIMER: Cancelling Timer (%d/%d)\n", OsirisTimers[i].handle, i);
          continue;
        }
      }

      if (OsirisTimers[i].timer_next_signal <= Gametime) {
        // this timer needs to be signaled
        signal = true;

        if (OsirisTimers[i].flags & OITF_REPEATCALL) {
          // this is a repeater
          if (OsirisTimers[i].repeat_count != -1) {
            // it has a finite repeat
            OsirisTimers[i].repeat_count--;
            if (OsirisTimers[i].repeat_count <= 0) {
              // remove the timer
              kill = true;
              OsirisTimers[i].repeat_count = 0;
            } else {
              // adjust for next signal
              OsirisTimers[i].timer_next_signal += OsirisTimers[i].timer_interval;
            }
          } else {
            // infinite repeat
            OsirisTimers[i].timer_next_signal += OsirisTimers[i].timer_interval;
          }
        }
      }

      if ((!((OsirisTimers[i].flags & OITF_REPEATCALL) && (OsirisTimers[i].repeat_count == -1))) &&
          OsirisTimers[i].timer_end <= Gametime) {

        // this timer has expired, remove it
        kill = true;
        // signal timer
        signal = true;
      }

      if (signal) {
        ei.evt_timer.game_time = Gametime;
        ei.evt_timer.id = OsirisTimers[i].id;
      }

      // this timer is currently in use, see what kind of trigger it is
      if (OsirisTimers[i].flags & OITF_TRIGGERTIMER) {
        // trigger timer
        if (signal) {
          Osiris_CallTriggerEvent(OsirisTimers[i].trignum, EVT_TIMER, &ei);
        }
      } else if (OsirisTimers[i].flags & OITF_LEVELTIMER) {
        // level timer
        if (signal) {
          Osiris_CallLevelEvent(EVT_TIMER, &ei);
        }
      } else {
        // object timer
        obj = ObjGet(OsirisTimers[i].objhandle);
        if (obj) {
          // process this object timer
          if (signal) {
            Osiris_CallEvent(obj, EVT_TIMER, &ei);
          }
        } else {
          // this object no longer exists, remove the timer
          kill = true;
        }
      }

      if (kill)
        OsirisTimers[i].flags &= ~OITF_USED;
    }
  }
}

//	Osiris_ResetAllTimers
//	Purpose:
//		Flushes all the timers
void Osiris_ResetAllTimers(void) {
  for (int i = 0; i < MAX_OSIRIS_TIMERS; i++) {
    OsirisTimers[i].flags = 0;
  }
}

//	Osiris_CreateTimer
//	Pupose:
//		Adds a timer to the list to be processed.  You'll receive a EVT_TIMER when the timer is signaled.
//	Returns an id to the timer, which can be used to cancel a timer. -1 on error.
int Osiris_CreateTimer(tOSIRISTIMER *ot) {
  // find an empty timer
  int i;
  for (i = 0; i < MAX_OSIRIS_TIMERS; i++) {
    if (!(OsirisTimers[i].flags & OITF_USED)) {
      break;
    }
  }

  if (i >= MAX_OSIRIS_TIMERS)
    return -1; // no more slots available

  // clear out the slots
  OsirisTimers[i].flags = 0;
  OsirisTimers[i].id = 0;
  OsirisTimers[i].objhandle = 0;
  OsirisTimers[i].repeat_count = 0;
  OsirisTimers[i].timer_end = 0;
  OsirisTimers[i].timer_interval = 0;
  OsirisTimers[i].timer_next_signal = 0;
  OsirisTimers[i].handle = 0;
  OsirisTimers[i].objhandle_detonator = OBJECT_HANDLE_NONE;

  // fill in the data
  OsirisTimers[i].flags |= OITF_USED;
  OsirisTimers[i].id = ot->id;
  OsirisTimers[i].timer_end = ot->timer_interval + Gametime;
  OsirisTimers[i].timer_interval = ot->timer_interval;
  OsirisTimers[i].timer_next_signal = ot->timer_interval + Gametime;

  if (ot->flags & OTF_TRIGGER) {
    OsirisTimers[i].trignum = ot->trigger_number;
    OsirisTimers[i].flags |= OITF_TRIGGERTIMER;
  } else if (ot->flags & OTF_LEVEL) {
    OsirisTimers[i].flags |= OITF_LEVELTIMER;
  } else {
    OsirisTimers[i].objhandle = ot->object_handle;
  }

  if (ot->flags & OTF_REPEATER) {
    // this is a repeater timer
    OsirisTimers[i].flags |= OITF_REPEATCALL;
    OsirisTimers[i].repeat_count = ot->repeat_count;
    if (ot->repeat_count != -1) {
      OsirisTimers[i].timer_end = (ot->timer_interval * ot->repeat_count) + Gametime;
    }
  }

  if (ot->flags & OTF_CANCELONDEAD) {
    // there is a detonator
    OsirisTimers[i].flags |= OITF_CANCELONDEAD;
    OsirisTimers[i].objhandle_detonator = ot->object_handle_detonator;
  }

  // create a handle
  Osiris_timer_counter++;
  int handle = FORM_HANDLE(Osiris_timer_counter, i);

  OsirisTimers[i].handle = handle;

  return handle;
}

//	Osiris_CancelTimer
//	Purpose:
//		Cancels a timer that's in use, given its handle
void Osiris_CancelTimer(int handle) {
  int slot;

  slot = GET_SLOT(handle);

  if (slot < 0 || slot >= MAX_OSIRIS_TIMERS)
    return;

  if (OsirisTimers[slot].handle != handle) // not the same timer
    return;

  OsirisTimers[slot].flags &= ~OITF_USED;

  tOSIRISEventInfo ei;
  ei.evt_timercancel.detonated = 0;
  ei.evt_timercancel.handle = handle;

  if (OsirisTimers[slot].flags & OITF_TRIGGERTIMER) {
    Osiris_CallTriggerEvent(OsirisTimers[slot].trignum, EVT_TIMERCANCEL, &ei);
  } else if (OsirisTimers[slot].flags & OITF_LEVELTIMER) {
    Osiris_CallLevelEvent(EVT_TIMERCANCEL, &ei);
  } else {
    object *obj = ObjGet(OsirisTimers[slot].objhandle);
    if (obj)
      Osiris_CallEvent(obj, EVT_TIMERCANCEL, &ei);
  }
}

//	Osiris_GetTimerHandle
//	Purpose:
//		Gets the handle for the timer with the specified id
int Osiris_GetTimerHandle(int id) {
  // Look for timer with this ID
  for (int i = 0; i < MAX_OSIRIS_TIMERS; i++)
    if ((OsirisTimers[i].flags & OITF_USED) && (OsirisTimers[i].id == id)) {
      return OsirisTimers[i].handle;
    }

  return 0;
}

//	Osiris_CancelTimer
//	Purpose:
//		Cancels a timer given its ID
void Osiris_CancelTimerID(int id) {
  // Look for timer with this ID
  for (int i = 0; i < MAX_OSIRIS_TIMERS; i++)
    if ((OsirisTimers[i].flags & OITF_USED) && (OsirisTimers[i].id == id)) {
      Osiris_CancelTimer(OsirisTimers[i].handle);
      return;
    }
}

//	Osiris_TimerExists
//	Purpose:
//		Returns true if the timer is valid
uint8_t Osiris_TimerExists(int handle) {
  int id = GET_SLOT(handle);

  if (id < 0 || id >= MAX_OSIRIS_TIMERS)
    return false;

  if (!(OsirisTimers[id].flags & OITF_USED))
    return false;

  if (OsirisTimers[id].handle != handle) // not the same timer
    return false;

  return true;
}

//	Osiris_TimerTimeRemaining
//	Purpose:
//		Returns the amount of time remaining on the specified timer
float Osiris_TimerTimeRemaining(int handle) {
  int id = GET_SLOT(handle);

  if (id < 0 || id >= MAX_OSIRIS_TIMERS)
    return -1.0;

  if (!(OsirisTimers[id].flags & OITF_USED))
    return -1.0;

  if (OsirisTimers[id].handle != handle) // not the same timer
    return -1.0;

  return (OsirisTimers[id].timer_end - Gametime);
}

#define OSIRIS_SYSTEM_FILEVERSION 0x01
//	Osiris_SaveSystemState
//	Purpose:
//		Saves the current state of the system (not the scripts!) to file
void Osiris_SaveSystemState(CFILE *file) {
  int i;
  int save_start = cftell(file);
  int checksum_pos;

  cf_WriteString(file, "OSIRIS");

  cf_WriteByte(file, OSIRIS_SYSTEM_FILEVERSION);

  checksum_pos = cftell(file);
  cf_WriteInt(file, 0); // this will be # of bytes writtens

  cf_WriteInt(file, Osiris_timer_counter);

  // save out the timer state
  for (i = 0; i < MAX_OSIRIS_TIMERS; i++) {
    if (OsirisTimers[i].flags & OITF_USED) {
      // write out information about this timer
      cf_WriteByte(file, 1); // timer exists
      cf_WriteShort(file, OsirisTimers[i].flags);
      cf_WriteInt(file, OsirisTimers[i].id);
      cf_WriteInt(file, OsirisTimers[i].repeat_count);
      cf_WriteFloat(file, OsirisTimers[i].timer_interval);
      cf_WriteFloat(file, OsirisTimers[i].timer_next_signal);
      cf_WriteFloat(file, OsirisTimers[i].timer_end);
      cf_WriteInt(file, OsirisTimers[i].objhandle);
      cf_WriteInt(file, OsirisTimers[i].objhandle_detonator);
      cf_WriteInt(file, OsirisTimers[i].handle);
    } else {
      cf_WriteByte(file, 0);
    }
  }

  // auto-save script mallocs
  Osiris_SaveMemoryChunks(file);

  // go through all loaded DLLs and save states
  // this is touchy, we need to make sure all DLL modules that are currently
  // loaded, be loaded when we restore states.  As a safety precaution, the Global
  // state will be saved as the following (an array of the following):
  // byte offset	size		description
  //	0			1			Number of loaded DLLs
  //		...
  //	+1			1			String length of module name
  //	+2			x			Name of the module
  //	+2+x		4			Size of global data stored
  //	+6+x		y			global data
  //		...

  // first count up the number of loaded modules
  int loaded_module_count = 0;
  for (i = 0; i < MAX_LOADED_MODULES; i++) {
    if (OSIRIS_loaded_modules[i].flags & OSIMF_INUSE) {
      // this is a loaded module
      loaded_module_count++;
    }
  }

  cf_WriteByte(file, loaded_module_count);

  for (i = 0; i < MAX_LOADED_MODULES; i++) {
    if (OSIRIS_loaded_modules[i].flags & OSIMF_INUSE) {
      // get the length of the module name
      int module_name_length = strlen(OSIRIS_loaded_modules[i].module_name) + 1;
      cf_WriteByte(file, module_name_length);
      cf_WriteBytes((uint8_t *)OSIRIS_loaded_modules[i].module_name, module_name_length, file);

      // now here is the tricky part, save the current fileposition, write a dummy 0 int
      int saved_file_pos = cftell(file);
      cf_WriteInt(file, 0);

      int global_size = OSIRIS_loaded_modules[i].SaveRestoreState(file, 1);
      int restore_file_pos = cftell(file);

      // now jump back and fill in the correct global data size, than jump back
      cfseek(file, saved_file_pos, SEEK_SET);
      cf_WriteInt(file, global_size);
      cfseek(file, restore_file_pos, SEEK_SET);
    }
  }

  // Go through all the objects and call their EVT_SAVESTATE (if they have a script)
  Osiris_SaveOMMS(file);

  tOSIRISEventInfo ei;
  ei.evt_savestate.fileptr = (void *)file;

  Osiris_CallLevelEvent(EVT_SAVESTATE, &ei);

  for (i = 0; i <= Num_triggers; i++) {
    Osiris_CallTriggerEvent(i, EVT_SAVESTATE, &ei);
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (Objects[i].type != OBJ_NONE && Objects[i].osiris_script) {
      Osiris_CallEvent(&Objects[i], EVT_SAVESTATE, &ei);
    }
  }

  int save_end = cftell(file);

  mprintf(0, "Osiris: Save state, %d bytes written\n", save_end - save_start);

  cfseek(file, checksum_pos, SEEK_SET);
  cf_WriteInt(file, save_end - save_start); // write out 'checksum'
  cfseek(file, save_end, SEEK_SET);
}

//	Osiris_RestoreSystemState
//	Purpose:
//		Restore the state of the system from file (does not restore scripts!)
bool Osiris_RestoreSystemState(CFILE *file) {
  int i;
  int restore_start = cftell(file);
  int num_bytes_to_be_restored;

  char tag[256];
  cf_ReadString(tag, 256, file);
  if (strcmp(tag, "OSIRIS")) {
    // Things aren't right...our tag is not here
    mprintf(0, "Missing OSIRIS tag\n");
    Int3();
    return false;
  }

  uint8_t version = (uint8_t)cf_ReadByte(file);

  num_bytes_to_be_restored = cf_ReadInt(file);

  Osiris_timer_counter = cf_ReadInt(file);

  // restore timer state
  for (i = 0; i < MAX_OSIRIS_TIMERS; i++) {
    if (cf_ReadByte(file)) {
      // timer is used
      OsirisTimers[i].flags = cf_ReadShort(file);
      OsirisTimers[i].id = cf_ReadInt(file);
      OsirisTimers[i].repeat_count = cf_ReadInt(file);
      OsirisTimers[i].timer_interval = cf_ReadFloat(file);
      OsirisTimers[i].timer_next_signal = cf_ReadFloat(file);
      OsirisTimers[i].timer_end = cf_ReadFloat(file);
      OsirisTimers[i].objhandle = cf_ReadInt(file);
      OsirisTimers[i].objhandle_detonator = cf_ReadInt(file);
      OsirisTimers[i].handle = cf_ReadInt(file);

    } else {
      OsirisTimers[i].flags = 0;
    }
  }

  // restore auto-saved memory chunks
  Osiris_RestoreMemoryChunks(file);

  // now we need to restore the global state of the DLLs
  // byte offset	size		description
  //	0			1			Number of loaded DLLs
  //		...
  //	+1			1			String length of module name
  //	+2			x			Name of the module
  //	+2+x		4			Size of global data stored
  //	+6+x		y			global data
  //		...
  int loaded_module_count = 0;
  for (i = 0; i < MAX_LOADED_MODULES; i++) {
    if (OSIRIS_loaded_modules[i].flags & OSIMF_INUSE) {
      // this is a loaded module
      loaded_module_count++;
    }
  }

  int read_module_count = cf_ReadByte(file);
  if (read_module_count != loaded_module_count) {
    // the current number of loaded module does not equal the number of modules that were loaded
    // when the state was saved.  This means that things are not going to be restored exactly for
    // sure.  We'll skip over those that are not loaded.  We're int3 here because I want to know
    // when this happens.
    mprintf(0,
             "OSIRIS: Restoring global state, the number of loaded modules is not the same as the restored count (%d "
             "vs. %d)\n",
             loaded_module_count, read_module_count);
    if (Demo_flags != DF_PLAYBACK) {
      Int3();
    }
  }

  // now go through all the read module count DLLs and see if that DLL is currently loaded
  for (i = 0; i < read_module_count; i++) {
    char read_module_name[_MAX_PATH];
    int read_module_namelen;
    int read_module_globalsize;
    int next_file_pos;
    int module_handle;

    read_module_namelen = cf_ReadByte(file);
    cf_ReadBytes((uint8_t *)read_module_name, read_module_namelen, file);
    read_module_name[read_module_namelen] = '\0';

    read_module_globalsize = cf_ReadInt(file);
    next_file_pos = cftell(file) + read_module_globalsize;

    module_handle = Osiris_FindLoadedModule(read_module_name);
    if (module_handle == -1) {
      mprintf(0, "OSIRIS: The module (%s) was not found while trying to restore the state\n", read_module_name);
      if (Demo_flags != DF_PLAYBACK) {
        Int3();
      }
    } else {
      OSIRIS_loaded_modules[module_handle].SaveRestoreState(file, 0);
    }

    cfseek(file, next_file_pos, SEEK_SET); // this ensures that we keep track in the file, even if the
                                           // DLL reads too much/little
  }

  Osiris_RestoreOMMS(file);

  // Go through all the objects and call their EVT_RESTORESTATE (if they have a script)
  tOSIRISEventInfo ei;

  ei.evt_restorestate.fileptr = (void *)file;

  Osiris_CallLevelEvent(EVT_RESTORESTATE, &ei);

  for (i = 0; i <= Num_triggers; i++) {
    Osiris_CallTriggerEvent(i, EVT_RESTORESTATE, &ei);
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (Objects[i].type != OBJ_NONE && Objects[i].osiris_script) {
      Osiris_CallEvent(&Objects[i], EVT_RESTORESTATE, &ei);
    }
  }

  int restore_end = cftell(file);

  mprintf(0, "Osiris: Restore state, %d bytes read\n", restore_end - restore_start);

  ASSERT(num_bytes_to_be_restored == (restore_end - restore_start));
  if (num_bytes_to_be_restored == (restore_end - restore_start))
    return true;
  else {
    if (Demo_flags == DF_PLAYBACK) {
      cfseek(file, restore_start + num_bytes_to_be_restored, SEEK_SET);
      return true;
    }
  }

  return false;
}

struct tOSIRISMEMNODE {
  tOSIRISMEMCHUNK chunk_id;
  void *memory;
  tOSIRISMEMNODE *next;
};

tOSIRISMEMNODE *Osiris_mem_root;

//	Osiris_InitMemoryManager
//	Purpose:
//		Initializes the memory manager for the scripts, for buffers that the scripts want
//	automatically restored/save.
void Osiris_InitMemoryManager(void) {
  Osiris_mem_root = NULL;
  atexit(Osiris_CloseMemoryManager);
}

//	Osiris_CloseMemoryManager
//	Purpose:
//		Shuts down the Osiris memory manager, freeing any unfreed memory
void Osiris_CloseMemoryManager(void) {
  tOSIRISMEMNODE *curr, *next;
  curr = Osiris_mem_root;
  while (curr) {
    next = curr->next;
    if (curr->memory)
      mem_free(curr->memory);
    mem_free(curr);
    curr = next;
  }
  Osiris_mem_root = NULL;
}

//	Osiris_AllocateMemory
//	Purpose:
//		Allocates a chunk of memory to be associated with a script.  It will automatically
//	save this memory to disk on game save, and will pass the pointer to this memory on EVT_RESTORE
void *Osiris_AllocateMemory(tOSIRISMEMCHUNK *mc) {
  // find the end of the list
  tOSIRISMEMNODE *curr, **error_node;

  if (!Osiris_mem_root) {
    // it'll be the first node
    Osiris_mem_root = (tOSIRISMEMNODE *)mem_malloc(sizeof(tOSIRISMEMNODE));
    if (!Osiris_mem_root)
      return NULL;

    curr = Osiris_mem_root;
    error_node = &Osiris_mem_root;
  } else {
    // traverse to the tail
    curr = Osiris_mem_root;
    while (curr->next) {
      curr = curr->next;
    }

    curr->next = (tOSIRISMEMNODE *)mem_malloc(sizeof(tOSIRISMEMNODE));
    if (!curr->next)
      return NULL;
    error_node = &curr->next;
    curr = curr->next;
  }

  // setup the data
  curr->next = NULL;
  curr->memory = mem_malloc(mc->size);
  if (!curr->memory) {
    // ack...out of memory
    *error_node = NULL; // make sure we cut off the list
    mem_free(curr);
    return NULL;
  }
  memcpy(&curr->chunk_id, mc, sizeof(tOSIRISMEMCHUNK));

  return curr->memory;
}

//	Osiris_FreeMemory
//	Purpose:
//		Frees a chunk of memory that was allocated by Osiris_AllocateMemory().
void Osiris_FreeMemory(void *mem_ptr) {
  tOSIRISMEMNODE *tofree;

  if (!Osiris_mem_root)
    return;

  if (Osiris_mem_root->memory == mem_ptr) {
    // free the base pointer
    tofree = Osiris_mem_root;
    Osiris_mem_root = Osiris_mem_root->next;
  } else {
    // traverse until we find the node
    tOSIRISMEMNODE *curr;
    curr = Osiris_mem_root;
    bool done = false;
    tofree = NULL;
    while (!done) {
      if (!curr->next) {
        done = true; // we didn't find it
      } else if (curr->next->memory == mem_ptr) {
        // this is the guy to free
        tofree = curr->next;
        done = true;
      } else
        curr = curr->next;
    }

    if (tofree) {
      // ok there is a value to free, pull the list back one from curr on
      curr->next = tofree->next;
    } else {
      // nothing to do
      return;
    }
  }

  // free the memory associated with tofree
  if (tofree->memory)
    mem_free(tofree->memory);
  mem_free(tofree);
}

bool compareid(tOSIRISSCRIPTID *sid, tOSIRISSCRIPTID *oid) {
  if (sid->type == oid->type) {
    if (sid->type == LEVEL_SCRIPT)
      return true;
    if (sid->type == TRIGGER_SCRIPT && sid->triggernum == oid->triggernum)
      return true;
    if (sid->type == OBJECT_SCRIPT && sid->objhandle == oid->objhandle)
      return true;
  }
  return false;
}

//	Osiris_FreeMemoryForScript
//	Purpose:
//		Frees all memory allocated for a given script
void Osiris_FreeMemoryForScript(tOSIRISSCRIPTID *sid) {
  if (!Osiris_mem_root)
    return;
  bool done = false;
  tOSIRISMEMNODE *curr, *next, *prev;
  curr = Osiris_mem_root;
  prev = NULL;

  while (!done) {
    if (!curr) {
      done = true;
    } else {
      next = curr->next;

      if (compareid(sid, &curr->chunk_id.my_id)) {
        // this has to go
        if (curr == Osiris_mem_root) {
          // removing root
          Osiris_mem_root = curr->next;

          if (curr->memory)
            mem_free(curr->memory);
          mem_free(curr);
        } else {
          // remove from list and pull back
          prev->next = curr->next;

          if (curr->memory)
            mem_free(curr->memory);
          mem_free(curr);
        }
      } else {
        prev = curr;
      }

      curr = next;
    }
  }
}

//	Osiris_SaveMemoryChunks
//	Purpose:
//		Saves out the 'auto manage' script memory to file
void Osiris_SaveMemoryChunks(CFILE *file) {
  tOSIRISMEMNODE *curr;
  curr = Osiris_mem_root;

  while (curr) {
    cf_WriteInt(file, curr->chunk_id.size);
    cf_WriteByte(file, curr->chunk_id.my_id.type);
    switch (curr->chunk_id.my_id.type) {
    case OBJECT_SCRIPT:
      cf_WriteInt(file, curr->chunk_id.my_id.objhandle);
      break;
    case TRIGGER_SCRIPT:
      cf_WriteInt(file, curr->chunk_id.my_id.triggernum);
      break;
    case LEVEL_SCRIPT:
      break;
    }
    cf_WriteInt(file, curr->chunk_id.id);
    cf_WriteBytes((uint8_t *)curr->memory, curr->chunk_id.size, file);
    curr = curr->next;
  }

  cf_WriteInt(file, 0);
}

//	Osiris_RestoreMemoryChunks
//	Purpose:
//		Restores the 'auto manage' from file, calls the EVT_MEMRESTORE
void Osiris_RestoreMemoryChunks(CFILE *file) {
  tOSIRISMEMNODE *curr;
  tOSIRISMEMNODE *memchunk;

  // Osiris_CloseMemoryManager(); We might not want to close this down...due to some objects don't get destroyed
  // Osiris_mem_root = NULL;
  curr = Osiris_mem_root;
  if (curr) {
    while (curr->next) {
      curr = curr->next;
    }
  }

  bool done = false;
  while (!done) {
    int size = cf_ReadInt(file);
    if (size == 0) {
      // we're done
      done = true;
    } else {
      // handle this node
      memchunk = (tOSIRISMEMNODE *)mem_malloc(sizeof(tOSIRISMEMNODE));
      if (!memchunk) {
        Error("Out of memory");
      }

      memchunk->chunk_id.size = size;
      memchunk->chunk_id.my_id.type = (script_type)cf_ReadByte(file);
      switch (memchunk->chunk_id.my_id.type) {
      case OBJECT_SCRIPT:
        memchunk->chunk_id.my_id.objhandle = cf_ReadInt(file);
        break;
      case TRIGGER_SCRIPT:
        memchunk->chunk_id.my_id.triggernum = cf_ReadInt(file);
        break;
      case LEVEL_SCRIPT:
        break;
      }
      memchunk->chunk_id.id = cf_ReadInt(file);
      memchunk->memory = mem_malloc(memchunk->chunk_id.size);
      if (!memchunk->memory) {
        Error("Out of memory");
      }
      cf_ReadBytes((uint8_t *)memchunk->memory, memchunk->chunk_id.size, file);
      memchunk->next = NULL;

      // ok, the node is setup, add it to the linked list
      if (!Osiris_mem_root) {
        Osiris_mem_root = curr = memchunk;
      } else {
        curr->next = memchunk;
        curr = curr->next;
      }

      tOSIRISEventInfo ei;
      ei.evt_memrestore.id = memchunk->chunk_id.id;
      ei.evt_memrestore.memory_ptr = memchunk->memory;

      // send an event to the object
      switch (memchunk->chunk_id.my_id.type) {
      case OBJECT_SCRIPT: {
        object *obj = ObjGet(memchunk->chunk_id.my_id.objhandle);
        if (obj) {
          Osiris_CallEvent(obj, EVT_MEMRESTORE, &ei);
        }
      } break;
      case TRIGGER_SCRIPT:
        Osiris_CallTriggerEvent(memchunk->chunk_id.my_id.triggernum, EVT_MEMRESTORE, &ei);
        break;
      case LEVEL_SCRIPT:
        Osiris_CallLevelEvent(EVT_MEMRESTORE, &ei);
        break;
      };
    }
  }
}

void _extractscript(char *script, char *tempfilename) { cf_CopyFile(tempfilename, script); }

int _getfreeextractslot(void) {
  // find a free slot
  for (int q = 0; q < MAX_LOADED_MODULES; q++) {
    if (!(OSIRIS_Extracted_scripts[q].flags & OESF_USED)) {
      return q;
    }
  }
  return -1;
}

void _clearextractedall(void) { Osiris_ClearExtractedScripts(false); }

int Osiris_ExtractScriptsFromHog(int library_handle, bool is_mission_hog) {
  if (library_handle == 0)
    return 0;

  mprintf(0, "OSIRIS: Extracting Scripts From Hog\n");

  char filename[_MAX_PATH], temp_filename[_MAX_PATH];
  char tempdir[_MAX_PATH], temp_file[_MAX_PATH], temp_fileext[_MAX_EXT];
  char temp_realname[_MAX_PATH];

  if (!OSIRIS_Extracted_script_dir) {
    strcpy(tempdir, Descent3_temp_directory);
    // ddio_MakePath(tempdir,LocalD3Dir,"custom","cache",NULL);	//TODO: make real path here
    OSIRIS_Extracted_script_dir = mem_strdup(tempdir);
    if (!OSIRIS_Extracted_script_dir)
      Error("Out of memory");
  } else {
    strcpy(tempdir, OSIRIS_Extracted_script_dir);
  }

  int count = 0;

  const char *script_extension;
#if defined(__LINUX__) || defined(ANDROID)
#if defined(MACOSX)
  script_extension = "*.dylib";
#else
  script_extension = "*.so";
#endif
#else
  script_extension = "*.dll";
#endif

  int index;
  index = _getfreeextractslot();
  if (index == -1) {
    mprintf(0, "OSIRIS: Out of slots extracting scripts!!!!!!!!\n");
    Int3();
    goto ex_error;
  }

  mprintf(0, "Search started\n");
  if (cf_LibraryFindFirst(library_handle, script_extension, filename)) {

    mprintf(0, "	Found: %s...", filename);
    if (!ddio_GetTempFileName(tempdir, "d3s", temp_filename))
      Int3();
    else {
      ddio_SplitPath(temp_filename, NULL, temp_file, temp_fileext);
      strcat(temp_file, temp_fileext);

      OSIRIS_Extracted_scripts[index].flags = OESF_USED;
      OSIRIS_Extracted_scripts[index].temp_filename = mem_strdup(temp_file);

      ddio_SplitPath(filename, NULL, temp_realname, NULL);
      OSIRIS_Extracted_scripts[index].real_filename = mem_strdup(temp_realname);

      if (is_mission_hog) {
        OSIRIS_Extracted_scripts[index].flags |= OESF_MISSION;
      }

      // extract it out
      mprintf(0, "Extracting...");
      _extractscript(filename, temp_filename);
      mprintf(0, "Done\n");

      count++;

      while (cf_LibraryFindNext(filename)) {
        mprintf(0, "	Found: %s...", filename);

        index = _getfreeextractslot();
        if (index == -1) {
          mprintf(0, "OSIRIS: Out of slots extracting scripts!!!!!!!!\n");
          Int3();
          goto ex_error;
        }

        // generate temp filename
        if (!ddio_GetTempFileName(tempdir, "d3s", temp_filename))
          Int3();
        else {
          ddio_SplitPath(temp_filename, NULL, temp_file, temp_fileext);
          strcat(temp_file, temp_fileext);

          OSIRIS_Extracted_scripts[index].flags = OESF_USED;
          OSIRIS_Extracted_scripts[index].temp_filename = mem_strdup(temp_file);

          ddio_SplitPath(filename, NULL, temp_realname, NULL);
          OSIRIS_Extracted_scripts[index].real_filename = mem_strdup(temp_realname);

          if (is_mission_hog) {
            OSIRIS_Extracted_scripts[index].flags |= OESF_MISSION;
          }

          // extract it out
          mprintf(0, "Extracting...");
          _extractscript(filename, temp_filename);
          mprintf(0, "Done\n");

          count++;
        }
      }
    }
  }

  mprintf(0, "Done Extracting\n");

ex_error:
  cf_LibraryFindClose();

  static bool atex = false;

  if (!atex) {
    atexit(_clearextractedall);
    atex = true;
  }

  return count;
}

void Osiris_ClearExtractedScripts(bool mission_only) {
  mprintf(0, "OSIRIS: Removing Extracted DLLs\n");

  char fullpath[_MAX_PATH];
  if (!OSIRIS_Extracted_script_dir) {
    return;
  }

  for (int i = 0; i < MAX_LOADED_MODULES; i++) {
    if (OSIRIS_Extracted_scripts[i].flags & OESF_USED) {
      if (mission_only && (!(OSIRIS_Extracted_scripts[i].flags & OESF_MISSION)))
        continue;

      ASSERT(OSIRIS_Extracted_scripts[i].temp_filename);
      ASSERT(OSIRIS_Extracted_scripts[i].real_filename);
      if (!(OSIRIS_Extracted_scripts[i].temp_filename && OSIRIS_Extracted_scripts[i].real_filename))
        continue;

      ddio_MakePath(fullpath, OSIRIS_Extracted_script_dir, OSIRIS_Extracted_scripts[i].temp_filename, NULL);
      ddio_DeleteFile(fullpath);

      mem_free(OSIRIS_Extracted_scripts[i].temp_filename);
      mem_free(OSIRIS_Extracted_scripts[i].real_filename);
      OSIRIS_Extracted_scripts[i].temp_filename = NULL;
      OSIRIS_Extracted_scripts[i].real_filename = NULL;
      OSIRIS_Extracted_scripts[i].flags &= ~OESF_USED;
    }
  }

  if (!mission_only) {
    mem_free(OSIRIS_Extracted_script_dir);
    OSIRIS_Extracted_script_dir = NULL;
  }
}

/*
******************************************************************************
Osiris Mission Memory System:
----------------------------
        OMMS is a way to allocate memory that can be shared between scripts and/or modules.  This
memory can also last through level changes.  The basic process of using this system is someone
calls the OMMS_Malloc() to allocate a chunk of memory that is to be shared/global.  This returns
a handle which is to be used by OMMS_Attach(), to get the pointer to the memory, and OMMS_Detach(),
which informs Osiris that you're no longer using the pointer OMMS_Attach() returned. OMMS_Detach()
will NOT free the memory, only OMMS_Free() does that, and it only does that when the reference
count for the memory is at 0 (OMMS_Attach() increments the reference count, OMMS_Detach() decrements
the reference count).  Basically, just surround the code that uses the global memory with a call
to OMMS_Attach() and OMMS_Detach().  ALWAYS make sure that you detach before you leave the event.

// Allocates a block of global memory for this module, of size amount_of_memory.
// unique_identfier is the script provided unique ID which is used throughout.
// script_identifier is the pointer of data provided to the script in it's InitializeDLL function (really the name of
the script)
// Returns -1 if there isn't enough available memory
// Returns -2 if the unique identifier passed in is already used, but the requested amount_of_memory is different
// If the memory has already been allocated, it will return the handle.
OMMSHANDLE OMMS_Malloc(size_t amount_of_memory,uint32_t unique_identifier,char *script_identifier);

//	Attaches to a block of global OMMS memory.  As long as at least one module (or script) is
//	attached to a module, the memory will not be deleted. (Increments the reference count)
//	Returns NULL if the memory couldn't be attached (it has been either free'd or never malloced)
void *OMMS_Attach(OMMSHANDLE handle);

//	Detaches a block of global OMMS memory. (Reduces the reference count).
void OMMS_Detach(OMMSHANDLE handle);

//	Frees a block of global memory
//	Only has affect if you are attached to the memory.  Memory will _ONLY_ be deleted when the
//	following conditions are meant for the shared memory block:
//	1) The reference count for the global memory is at 0 (OMMS_Attach() adds to reference count, OMMS_Detach()
subtracts).
//	2) OMMS_Free() has been called for the block of global memory.
//	The conditions can happen in any order, but as soon as both are satisfied, the memory
//	becomes deleted and any pointer returned by OMMS_Attach() becomes invalid.
//
//	handle : the value returned by OMMS_Malloc()
 void OMMS_Free(OMMSHANDLE handle);

//	Returns an OMMSHANDLE to a block of global memory allocated by a module/script.  Pass
//	in the unique_identifier and the script_identifier that was passed in the OMMS_Malloc().
//	Note: script_identifier is really the filename of the module that called the OMMS_Malloc().
//	Returns -1 if the module was never OMMS_Malloc()'d.
OMMSHANDLE OMMS_Find(uint32_t unique_identifier,char *script_identifier);

//	Returns information about the OMMS memory given it's handle returned from the OMMS_Find() or
//	OMMS_Malloc(). Returns 0 if the handle was invalid, 1 if the information has been filled in;
//	Pass NULL in for those parameters you don't need information about.
char OMMS_GetInfo(OMMSHANDLE handle,uint32_t *mem_size,uint32_t *uid,uint16_t *reference_count,uint8_t *has_free_been_called);


******************************************************************************
*/

struct tOMMSNode {
  uint16_t id;
  uint32_t size_of_memory;
  uint32_t unique_id;
  uint16_t reference_count;
  uint8_t free_called;
  void *memory_ptr;
  tOMMSNode *next;
};

struct tOMMSHashNode {
  char *script_name;
  uint16_t base_id;
  tOMMSNode *root;
  tOMMSHashNode *next;
};

tOMMSHashNode *OMMS_Hash_node_root = NULL;
uint16_t OMMS_Current_base_id = 0;
uint16_t OMMS_Current_id = 0;

//	Searches through the hash nodes and looks for the one associated with
//	the script name, if one doesn't exist it will create one (if autocreate is true).
tOMMSHashNode *Osiris_OMMS_FindHashNode(char *script_name, bool autocreate);
//	frees all memory associated with the OMMSHashNode given (includes all script
//	memory...returns the next node in the list, NULL if none
tOMMSHashNode *Osiris_OMMS_DeleteHashNode(tOMMSHashNode *node);
//	finds an OMMS node, given the hash node to start at.  If it isn't
//	found than one is created. NULL if out of memory.
tOMMSNode *Osiris_OMMS_FindNode(tOMMSHashNode *root, uint32_t uid, bool autocreate);
//	Removes the OMMS node for the given HashNode (completly remove)
void Osiris_OMMS_RemoveNode(tOMMSHashNode *root, uint32_t uid);
//	Reduces the reference count for an OMMSNode by 1
void Osiris_OMMS_ReduceRefCount(tOMMSHashNode *root, tOMMSNode *node);
//	Calls free on a node
void Osiris_OMMS_CallFreeForNode(tOMMSHashNode *root, tOMMSNode *node);
//	Searches for the given OMMSHANDLE, returns NULL if not found.  if hash is
//	given it will return the hash root that the node was found in.
tOMMSNode *Osiris_OMMS_FindHandle(OMMSHANDLE handle, tOMMSHashNode **hash = NULL);

// Allocates a block of global memory for this module, of size amount_of_memory.
// unique_identfier is the script provided unique ID which is used throughout.
// script_identifier is the pointer of data provided to the script in it's InitializeDLL function (really the name of
// the script) Returns -1 if there isn't enough available memory Returns -2 if the unique identifier passed in is
// already used, but the requested amount_of_memory is different Returns -3 if the unique identifier passed in is
// already used, same size requested
static OMMSHANDLE Osiris_OMMS_Malloc(size_t amount_of_memory, uint32_t unique_identifier, char *script_identifier);

//	Attaches to a block of global OMMS memory.  As long as at least one module (or script) is
//	attached to a module, the memory will not be deleted. (Increments the reference count)
//	Returns NULL if the memory couldn't be attached (it has been either free'd or never malloced)
static void *Osiris_OMMS_Attach(OMMSHANDLE handle);

//	Detaches a block of global OMMS memory. (Reduces the reference count).
static void Osiris_OMMS_Detach(OMMSHANDLE handle);

//	Frees a block of global memory
//	Only has affect if you are attached to the memory.  Memory will _ONLY_ be deleted when the
//	following conditions are meant for the shared memory block:
//	1) The reference count for the global memory is at 0 (OMMS_Attach() adds to reference count, OMMS_Detach()
// subtracts). 	2) OMMS_Free() has been called for the block of global memory. 	The conditions can happen in any order,
// but
// as soon as both are satisfied, the memory 	becomes deleted and any pointer returned by OMMS_Attach() becomes
// invalid.
//
//	handle : the value returned by OMMS_Malloc()
static void Osiris_OMMS_Free(OMMSHANDLE handle);

//	Returns an OMMSHANDLE to a block of global memory allocated by a module/script.  Pass
//	in the unique_identifier and the script_identifier that was passed in the OMMS_Malloc().
//	Note: script_identifier is really the filename of the module that called the OMMS_Malloc().
//	Returns -1 if the module was never OMMS_Malloc()'d.
static OMMSHANDLE Osiris_OMMS_Find(uint32_t unique_identifier, char *script_identifier);

//	Returns information about the OMMS memory given it's handle returned from the OMMS_Find() or
//	OMMS_Malloc(). Returns 0 if the handle was invalid, 1 if the information has been filled in;
//	Pass NULL in for those parameters you don't need information about.
static char Osiris_OMMS_GetInfo(OMMSHANDLE handle, uint32_t *mem_size, uint32_t *uid, uint16_t *reference_count,
                                uint8_t *has_free_been_called);

void Osiris_InitOMMS(void) {
  OMMS_Current_base_id = 0;
  OMMS_Current_id = 0;
  OMMS_Hash_node_root = NULL;
  atexit(Osiris_CloseOMMS);
}

void Osiris_CloseOMMS(void) {
  mprintf(0, "OSIRIS: Reseting OMMS memory\n");

  tOMMSHashNode *curr = OMMS_Hash_node_root;

  while (curr) {
    curr = Osiris_OMMS_DeleteHashNode(curr);
  }

  OMMS_Hash_node_root = NULL;
}

void Osiris_SaveOMMS(CFILE *file) {
  // save out our current OMMS handle position
  cf_WriteShort(file, OMMS_Current_base_id);
  cf_WriteShort(file, OMMS_Current_id);

  // go through all the hash nodes write their information out
  tOMMSHashNode *currhash = OMMS_Hash_node_root;
  while (currhash) {
    // write out a 1, saying that we have a hash node here
    cf_WriteByte(file, 1);

    cf_WriteShort(file, currhash->base_id);

    // write out the info about this hash node
    int length;
    length = (currhash->script_name) ? strlen(currhash->script_name) : 0;
    cf_WriteByte(file, length);
    if (length)
      cf_WriteBytes((uint8_t *)currhash->script_name, length, file);

    // now go through all the nodes and write their data
    tOMMSNode *node;
    node = currhash->root;
    while (node) {
      // write out 1, for valid hash
      cf_WriteByte(file, 1);
      cf_WriteShort(file, node->id);

      // write out all the node data
      cf_WriteByte(file, node->free_called);
      cf_WriteShort(file, node->reference_count);
      cf_WriteInt(file, node->unique_id);
      cf_WriteInt(file, node->size_of_memory);
      if (node->size_of_memory)
        cf_WriteBytes((uint8_t *)node->memory_ptr, node->size_of_memory, file);

      node = node->next;
    }
    // write out terminating 0
    cf_WriteByte(file, 0);

    // go to the next hash node
    currhash = currhash->next;
  }

  // write out terminating 0
  cf_WriteByte(file, 0);
}

void Osiris_RestoreOMMS(CFILE *file) {
  ASSERT(OMMS_Hash_node_root == NULL);

  OMMS_Current_base_id = (uint16_t)cf_ReadShort(file);
  OMMS_Current_id = (uint16_t)cf_ReadShort(file);

  tOMMSHashNode *currhash;
  tOMMSNode *node;

  currhash = NULL;

  // we have to rebuild the nodes
  while (cf_ReadByte(file)) {
    if (!currhash) {
      currhash = OMMS_Hash_node_root = (tOMMSHashNode *)mem_malloc(sizeof(tOMMSHashNode));
    } else {
      currhash->next = (tOMMSHashNode *)mem_malloc(sizeof(tOMMSHashNode));
      currhash = currhash->next;
    }

    if (!currhash)
      Error("Out of memory");

    currhash->next = NULL;
    currhash->root = NULL;
    currhash->script_name = NULL;

    currhash->base_id = (uint16_t)cf_ReadShort(file);

    // read length of string
    int length = cf_ReadByte(file);
    if (length) {
      currhash->script_name = (char *)mem_malloc(length + 1);
      if (!currhash->script_name)
        Error("Out of Memory");
      else
        cf_ReadBytes((uint8_t *)currhash->script_name, length, file);
    }

    node = NULL;

    // now go through all the nodes and right their data
    while (cf_ReadByte(file)) {
      if (!node) {
        node = currhash->root = (tOMMSNode *)mem_malloc(sizeof(tOMMSNode));
      } else {
        node->next = (tOMMSNode *)mem_malloc(sizeof(tOMMSNode));
        node = node->next;
      }

      if (!node)
        Error("Out of memory");

      node->memory_ptr = NULL;
      node->next = NULL;

      node->id = (uint16_t)cf_ReadShort(file);

      node->free_called = (cf_ReadByte(file)) ? true : false;
      node->reference_count = (uint16_t)cf_ReadShort(file);
      node->unique_id = cf_ReadInt(file);
      node->size_of_memory = cf_ReadInt(file);
      if (node->size_of_memory) {
        node->memory_ptr = mem_malloc(node->size_of_memory);
        if (!node->memory_ptr)
          Error("Out of memory");

        cf_ReadBytes((uint8_t *)node->memory_ptr, node->size_of_memory, file);
      }
    } // end reading nodes
  }   // end reading hash nodes
}

//	Searches through the hash nodes and looks for the one associated with
//	the script name, if one doesn't exist it will create one (if autocreate is true).
tOMMSHashNode *Osiris_OMMS_FindHashNode(char *script_name, bool autocreate) {
  tOMMSHashNode *curr = OMMS_Hash_node_root;

  if (!OMMS_Hash_node_root) {
    // allocate the root node
    if (!autocreate)
      return NULL;

    curr = OMMS_Hash_node_root = (tOMMSHashNode *)mem_malloc(sizeof(tOMMSHashNode));
  } else {
    if (curr->script_name && !stricmp(curr->script_name, script_name)) {
      // the root node matches
      return curr;
    }

    // search through to see if we can find the node
    while (curr->next) {
      if (curr->next->script_name && !stricmp(curr->next->script_name, script_name)) {
        // curr->next is a matching node
        return curr->next;
      }

      curr = curr->next;
    }

    // allocate a node and tack it on the end
    if (!autocreate)
      return NULL;

    curr->next = (tOMMSHashNode *)mem_malloc(sizeof(tOMMSHashNode));
    curr = curr->next;
  }

  // if we get here then curr is a freshly allocated node
  curr->next = NULL;
  curr->root = NULL;
  curr->script_name = mem_strdup(script_name);
  curr->base_id = ++OMMS_Current_base_id;

  return curr;
}

//	frees all memory associated with the OMMSHashNode given (includes all script
//	memory...returns the next node in the list, NULL if none
tOMMSHashNode *Osiris_OMMS_DeleteHashNode(tOMMSHashNode *node) {
  if (!node)
    return NULL;
  tOMMSHashNode *ret = node->next;

  if (node->script_name)
    mem_free(node->script_name);

  tOMMSNode *curr, *next;
  curr = next = node->root;

  while (curr) {
    next = curr->next;
    mem_free(curr->memory_ptr);
    mem_free(curr);
    curr = next;
  }

  mem_free(node);

  return ret;
}

//	finds an OMMS node, given the hash node to start at.  If it isn't
//	found than one is created. NULL if out of memory.
tOMMSNode *Osiris_OMMS_FindNode(tOMMSHashNode *root, uint32_t uid, bool autocreate) {
  tOMMSNode *curr = root->root;

  if (!root->root) {
    // allocate the root node
    if (!autocreate)
      return NULL;

    curr = root->root = (tOMMSNode *)mem_malloc(sizeof(tOMMSNode));
  } else {
    if (curr->unique_id == uid) {
      // the root node matches
      return curr;
    }

    // search through to see if we can find the node
    while (curr->next) {
      if (curr->next->unique_id == uid) {
        // curr->next is a matching node
        return curr->next;
      }

      curr = curr->next;
    }

    // allocate a node and tack it on the end
    if (!autocreate)
      return NULL;

    curr->next = (tOMMSNode *)mem_malloc(sizeof(tOMMSNode));
    curr = curr->next;
  }

  // if we get here then curr is a freshly allocated node
  curr->free_called = 0;
  curr->memory_ptr = NULL;
  curr->next = NULL;
  curr->reference_count = 0;
  curr->size_of_memory = 0;
  curr->unique_id = uid;
  curr->id = ++OMMS_Current_id;

  return curr;
}

//	Removes the OMMS node for the given HashNode (completly remove)
void Osiris_OMMS_RemoveNode(tOMMSHashNode *root, uint32_t uid) {
  tOMMSNode *curr = root->root;
  tOMMSNode *node_to_free = NULL;

  if (!root->root)
    return;

  if (root->root->unique_id == uid) {
    // the root node matches
    node_to_free = root->root;
    root->root = NULL;
    goto free_mem;
  }

  // search through to see if we can find the node
  while (curr->next) {
    if (curr->next->unique_id == uid) {
      // curr->next is a matching node
      node_to_free = curr->next;
      curr->next = curr->next->next;
      goto free_mem;
    }
    curr = curr->next;
  }

free_mem:
  if (!node_to_free)
    return;

  mprintf(0, "OMMS: deleting uid 0x%x\n", node_to_free->unique_id);
  if (node_to_free->memory_ptr)
    mem_free(node_to_free->memory_ptr);
  mem_free(node_to_free);
}

//	Reduces the reference count for an OMMSNode by 1
void Osiris_OMMS_ReduceRefCount(tOMMSHashNode *root, tOMMSNode *node) {
  if (!node)
    return;

  node->reference_count--;

  if (node->reference_count <= 0 && node->free_called) {
    // free the node
    Osiris_OMMS_RemoveNode(root, node->unique_id);
  }
}

//	Calls free on a node
void Osiris_OMMS_CallFreeForNode(tOMMSHashNode *root, tOMMSNode *node) {
  if (!node)
    return;

  node->free_called = 1;

  if (node->reference_count <= 0 && node->free_called) {
    // free the node
    Osiris_OMMS_RemoveNode(root, node->unique_id);
  }
}

//	Searches for the given OMMSHANDLE, returns NULL if not found.  if hash is
//	given it will return the hash root that the node was found in.
tOMMSNode *Osiris_OMMS_FindHandle(OMMSHANDLE handle, tOMMSHashNode **hash) {
  tOMMSHashNode *hashcurr = OMMS_Hash_node_root;
  tOMMSNode *nodecurr;
  uint16_t base_id;
  uint16_t id;
  base_id = ((handle & 0xFFFF0000) >> 16);
  id = (handle & 0x0000FFFF);

  while (hashcurr) {
    if (hashcurr->base_id == base_id) {

      nodecurr = hashcurr->root;
      while (nodecurr) {
        if (nodecurr->id == id) {
          if (hash)
            *hash = hashcurr;
          return nodecurr;
        }

        nodecurr = nodecurr->next;
      }
    }

    hashcurr = hashcurr->next;
  }

  return NULL;
}

// Allocates a block of global memory for this module, of size amount_of_memory.
// unique_identfier is the script provided unique ID which is used throughout.
// script_identifier is the pointer of data provided to the script in it's InitializeDLL function (really the name of
// the script) Returns -1 if there isn't enough available memory Returns -2 if the unique identifier passed in is
// already used, but the requested amount_of_memory is different If the memory has already been allocated, it will
// return the handle.
OMMSHANDLE Osiris_OMMS_Malloc(size_t amount_of_memory, uint32_t unique_identifier, char *script_identifier) {
  ASSERT(amount_of_memory > 0);
  if (amount_of_memory <= 0)
    return -1;

  // find the correct hash node
  tOMMSHashNode *hash = Osiris_OMMS_FindHashNode(script_identifier, true);
  if (!hash)
    return -1;

  tOMMSNode *node = Osiris_OMMS_FindNode(hash, unique_identifier, true);
  if (!node)
    return -1;

  if (node->memory_ptr) {
    // the memory already has been allocated
    if (node->size_of_memory == amount_of_memory)
      return ((hash->base_id << 16) | (node->id));

    // the size's requested don't match
    return -2;
  }

  // we need to allocate the memory
  node->memory_ptr = mem_malloc(amount_of_memory);
  if (!node->memory_ptr)
    return -1; // out of memory

  node->size_of_memory = amount_of_memory;
  node->unique_id = unique_identifier;

  mprintf(0, "OMMS: malloc handle (0x%x%x) size = %d\n", hash->base_id, node->id, node->size_of_memory);
  return ((hash->base_id << 16) | (node->id));
}

//	Attaches to a block of global OMMS memory.  As long as at least one module (or script) is
//	attached to a module, the memory will not be deleted. (Increments the reference count)
//	Returns NULL if the memory couldn't be attached (it has been either free'd or never malloced)
void *Osiris_OMMS_Attach(OMMSHANDLE handle) {
  tOMMSNode *node = Osiris_OMMS_FindHandle(handle);
  if (!node)
    return NULL;

  if (node->memory_ptr) {
    node->reference_count++;
  }
  return node->memory_ptr;
}

//	Detaches a block of global OMMS memory. (Reduces the reference count).
void Osiris_OMMS_Detach(OMMSHANDLE handle) {
  tOMMSHashNode *hash;
  tOMMSNode *node = Osiris_OMMS_FindHandle(handle, &hash);
  if (!node)
    return;

  Osiris_OMMS_ReduceRefCount(hash, node);
}

//	Frees a block of global memory
//	Only has affect if you are attached to the memory.  Memory will _ONLY_ be deleted when the
//	following conditions are meant for the shared memory block:
//	1) The reference count for the global memory is at 0 (OMMS_Attach() adds to reference count, OMMS_Detach()
// subtracts). 	2) OMMS_Free() has been called for the block of global memory. 	The conditions can happen in any order,
// but
// as soon as both are satisfied, the memory 	becomes deleted and any pointer returned by OMMS_Attach() becomes
// invalid.
//
//	handle : the value returned by OMMS_Malloc()
void Osiris_OMMS_Free(OMMSHANDLE handle) {
  tOMMSHashNode *hash;
  tOMMSNode *node = Osiris_OMMS_FindHandle(handle, &hash);
  if (!node)
    return;

  Osiris_OMMS_CallFreeForNode(hash, node);
}

//	Returns an OMMSHANDLE to a block of global memory allocated by a module/script.  Pass
//	in the unique_identifier and the script_identifier that was passed in the OMMS_Malloc().
//	Note: script_identifier is really the filename of the module that called the OMMS_Malloc().
//	Returns -1 if the module was never OMMS_Malloc()'d.
OMMSHANDLE Osiris_OMMS_Find(uint32_t unique_identifier, char *script_identifier) {
  tOMMSHashNode *hash = Osiris_OMMS_FindHashNode(script_identifier, false);
  if (!hash)
    return -1;

  tOMMSNode *node = Osiris_OMMS_FindNode(hash, unique_identifier, false);
  if (!node)
    return -1;
  if (!node->memory_ptr)
    return -1;

  return ((hash->base_id << 16) | (node->id));
}

//	Returns information about the OMMS memory given it's handle returned from the OMMS_Find() or
//	OMMS_Malloc(). Returns 0 if the handle was invalid, 1 if the information has been filled in;
//	Pass NULL in for those parameters you don't need information about.
char Osiris_OMMS_GetInfo(OMMSHANDLE handle, uint32_t *mem_size, uint32_t *uid, uint16_t *reference_count,
                         uint8_t *has_free_been_called) {
  if (mem_size)
    *mem_size = 0;
  if (uid)
    *uid = 0;
  if (reference_count)
    *reference_count = 0;
  if (has_free_been_called)
    *has_free_been_called = 0;

  tOMMSHashNode *hash;
  tOMMSNode *node = Osiris_OMMS_FindHandle(handle, &hash);
  if (!node)
    return 0;

  if (mem_size)
    *mem_size = node->size_of_memory;
  if (uid)
    *uid = node->unique_id;
  if (reference_count)
    *reference_count = node->reference_count;
  if (has_free_been_called)
    *has_free_been_called = node->free_called;

  return 1;
}

//*****************************************************************************
//	Osiris_CreateModuleInitStruct
//	Purpose:
//		This function initializes a Module Init Struct with all the needed data to get sent
//	to the module during initialization.
void Osiris_CreateModuleInitStruct(tOSIRISModuleInit *mi) {
  int i = 0;

  // fill in function pointers here
  mi->fp[i++] = (int *)MonoPrintf;
  mi->fp[i++] = (int *)msafe_CallFunction;
  mi->fp[i++] = (int *)msafe_GetValue;
  mi->fp[i++] = (int *)osipf_CallObjectEvent;
  mi->fp[i++] = (int *)osipf_CallTriggerEvent;
  mi->fp[i++] = (int *)osipf_SoundTouch;
  mi->fp[i++] = (int *)osipf_ObjectFindID;
  mi->fp[i++] = (int *)osipf_WeaponFindID;
  mi->fp[i++] = (int *)osipf_ObjectGetTimeLived;
  mi->fp[i++] = (int *)osipf_GetGunPos;
  mi->fp[i++] = (int *)osipf_RoomValue;
  mi->fp[i++] = (int *)osipf_IsRoomValid;
  mi->fp[i++] = (int *)osipf_GetAttachParent;
  mi->fp[i++] = (int *)osipf_GetNumAttachSlots;
  mi->fp[i++] = (int *)osipf_GetAttachChildHandle;
  mi->fp[i++] = (int *)osipf_AttachObjectAP;
  mi->fp[i++] = (int *)osipf_AttachObjectRad;
  mi->fp[i++] = (int *)osipf_UnattachFromParent;
  mi->fp[i++] = (int *)osipf_UnattachChild;
  mi->fp[i++] = (int *)osipf_UnattachChildren;
  mi->fp[i++] = (int *)osipf_RayCast;
  mi->fp[i++] = (int *)osipf_AIGetPathID;
  mi->fp[i++] = (int *)osipf_AIGoalFollowPathSimple;
  mi->fp[i++] = (int *)osipf_AIPowerSwitch;
  mi->fp[i++] = (int *)osipf_AITurnTowardsVectors;
  mi->fp[i++] = (int *)osipf_AISetType;
  mi->fp[i++] = (int *)osipf_AIFindHidePos;
  mi->fp[i++] = (int *)osipf_AIGoalAddEnabler;
  mi->fp[i++] = (int *)osipf_AIGoalAdd;
  mi->fp[i++] = (int *)osipf_AIGoalClear;
  mi->fp[i++] = (int *)osipf_AIValue;
  mi->fp[i++] = (int *)osipf_AIFindObjOfType;
  mi->fp[i++] = (int *)osipf_AIGetRoomPathPoint;
  mi->fp[i++] = (int *)osipf_AIFindEnergyCenter;
  mi->fp[i++] = (int *)osipf_AIGetDistToObj;
  mi->fp[i++] = (int *)osipf_AISetGoalFlags;
  mi->fp[i++] = (int *)osipf_AISetGoalCircleDist;
  mi->fp[i++] = (int *)osipf_CFReadBytes;
  mi->fp[i++] = (int *)osipf_CFReadInt;
  mi->fp[i++] = (int *)osipf_CFReadShort;
  mi->fp[i++] = (int *)osipf_CFReadByte;
  mi->fp[i++] = (int *)osipf_CFReadFloat;
  mi->fp[i++] = (int *)osipf_CFReadDouble;
  mi->fp[i++] = (int *)osipf_CFReadString;
  mi->fp[i++] = (int *)osipf_CFWriteBytes;
  mi->fp[i++] = (int *)osipf_CFWriteString;
  mi->fp[i++] = (int *)osipf_CFWriteInt;
  mi->fp[i++] = (int *)osipf_CFWriteShort;
  mi->fp[i++] = (int *)osipf_CFWriteByte;
  mi->fp[i++] = (int *)osipf_CFWriteFloat;
  mi->fp[i++] = (int *)osipf_CFWriteDouble;
  mi->fp[i++] = (int *)Osiris_AllocateMemory;
  mi->fp[i++] = (int *)Osiris_FreeMemory;
  mi->fp[i++] = (int *)Osiris_CancelTimer;
  mi->fp[i++] = (int *)Osiris_CreateTimer;
  mi->fp[i++] = (int *)msafe_DoPowerup;
  mi->fp[i++] = (int *)osipf_ObjCreate;
  mi->fp[i++] = (int *)osipf_GameTime;
  mi->fp[i++] = (int *)osipf_FrameTime;
  mi->fp[i++] = (int *)osipf_ObjWBValue;
  mi->fp[i++] = (int *)Osiris_TimerExists;
  mi->fp[i++] = (int *)osipf_ObjectValue;
  mi->fp[i++] = (int *)osipf_MatcenValue;
  mi->fp[i++] = (int *)osipf_MatcenReset;
  mi->fp[i++] = (int *)osipf_MatcenCopy;
  mi->fp[i++] = (int *)osipf_MatcenCreate;
  mi->fp[i++] = (int *)osipf_MatcenFindId;
  mi->fp[i++] = (int *)osipf_MissionFlagSet;
  mi->fp[i++] = (int *)osipf_MissionFlagGet;
  mi->fp[i++] = (int *)osipf_PlayerValue;
  mi->fp[i++] = (int *)osipf_ObjectCustomAnim;
  mi->fp[i++] = (int *)osipf_PlayerAddHudMessage;
  mi->fp[i++] = (int *)osipf_ObjGhost;
  mi->fp[i++] = (int *)osipf_ObjBurning;
  mi->fp[i++] = (int *)osipf_ObjIsEffect;
  mi->fp[i++] = (int *)osipf_CFopen;
  mi->fp[i++] = (int *)osipf_CFclose;
  mi->fp[i++] = (int *)osipf_CFtell;
  mi->fp[i++] = (int *)osipf_CFeof;
  mi->fp[i++] = (int *)osipf_SoundStop;
  mi->fp[i++] = (int *)osipf_SoundPlay2d;
  mi->fp[i++] = (int *)osipf_SoundPlay3d;
  mi->fp[i++] = (int *)osipf_SoundFindId;
  mi->fp[i++] = (int *)osipf_AIIsObjFriend;
  mi->fp[i++] = (int *)osipf_AIIsObjEnemy;
  mi->fp[i++] = (int *)osipf_AIGoalValue;
  mi->fp[i++] = (int *)osipf_AIGetNearbyObjs;
  mi->fp[i++] = (int *)osipf_AIGetCurGoalIndex;
  mi->fp[i++] = (int *)Osiris_OMMS_Malloc;
  mi->fp[i++] = (int *)Osiris_OMMS_Attach;
  mi->fp[i++] = (int *)Osiris_OMMS_Detach;
  mi->fp[i++] = (int *)Osiris_OMMS_Free;
  mi->fp[i++] = (int *)Osiris_OMMS_Find;
  mi->fp[i++] = (int *)Osiris_OMMS_GetInfo;
  mi->fp[i++] = (int *)Cinematic_Start;
  mi->fp[i++] = (int *)Cinematic_Stop;
  mi->fp[i++] = (int *)osipf_FindSoundName;
  mi->fp[i++] = (int *)osipf_FindRoomName;
  mi->fp[i++] = (int *)osipf_FindTriggerName;
  mi->fp[i++] = (int *)osipf_FindObjectName;
  mi->fp[i++] = (int *)osipf_GetTriggerRoom;
  mi->fp[i++] = (int *)osipf_GetTriggerFace;
  mi->fp[i++] = (int *)osipf_FindDoorName;
  mi->fp[i++] = (int *)osipf_FindTextureName;
  mi->fp[i++] = (int *)osipf_CreateRandomSparks;
  mi->fp[i++] = (int *)Osiris_CancelTimerID;
  mi->fp[i++] = (int *)osipf_GetGroundPos;
  mi->fp[i++] = (int *)osipf_EnableShip;
  mi->fp[i++] = (int *)osipf_IsShipEnabled;
  mi->fp[i++] = (int *)osipf_PathGetInformation;
  mi->fp[i++] = (int *)Cinematic_StartCannedScript;
  mi->fp[i++] = (int *)osipf_FindMatcenName;
  mi->fp[i++] = (int *)osipf_FindPathName;
  mi->fp[i++] = (int *)osipf_FindLevelGoalName;
  mi->fp[i++] = (int *)osipf_ObjectFindType;
  mi->fp[i++] = (int *)osipf_LGoalValue;
  mi->fp[i++] = (int *)osipf_ObjMakeListOfType;
  mi->fp[i++] = (int *)osipf_ObjKill;
  //	mi->fp[i++] = (int *)osipf_AIAreRoomsReachable;
  mi->fp[i++] = (int *)osipf_AIIsDestReachable;
  mi->fp[i++] = (int *)osipf_AIIsObjReachable;
  mi->fp[i++] = (int *)osipf_GameGetDiffLevel;
  mi->fp[i++] = (int *)osipf_GetLanguageSetting;
  mi->fp[i++] = (int *)osipf_PathValue;

  // fill in the remaining with NULL
  for (; i < MAX_MODULEFUNCS; i++) {
    mi->fp[i] = NULL;
  }
}
