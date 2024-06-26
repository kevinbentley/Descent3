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


/*
 * $Logfile: /DescentIII/Main/lib/con_dll.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:58:12 $
 * $Author: kevinb $
 *
 * Common header for connection DLLs.
 *
 * $Log: con_dll.h,v $
 * Revision 1.1.1.1  2003/08/26 03:58:12  kevinb
 * initial 1.5 import
 *
 *
 * 78    5/09/00 5:11p Jeff
 * fixed struct packing bug
 *
 * 77    3/26/00 10:30p Kevin
 * MOD Downloader for 1.4 patch.
 *
 * 75    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 74    8/02/99 11:47a Kevin
 * don't display the d3 single mission twice!
 *
 * 73    7/12/99 4:15p Kevin
 * Changed the way we determine if we should report stats or not in PXO
 *
 * 72    7/06/99 5:52p Kevin
 * PXO & multiplayer fixes for the patch
 *
 * 71    6/23/99 3:35p Samir
 * added pstypes.h
 *
 * 70    6/03/99 8:48a Kevin
 * fixes for new OEM version....
 *
 * 69    5/24/99 4:21p Jason
 * fixed difficultly level problem
 *
 * 68    4/28/99 6:39p Kevin
 * Build 182 fixes
 *
 * 67    4/26/99 2:54p Kevin
 * fixed team count & keyword system to work with dedicated server
 *
 * 66    4/25/99 5:02p Kevin
 * Bunches of multiplayer UI improvements
 *
 * 65    4/25/99 12:11a Kevin
 * game info dialog stuff
 *
 * 64    4/23/99 5:32p Kevin
 * Fixed a few mission bugs.
 *
 * 63    4/23/99 3:33p Kevin
 * mission file/multiplayer mod keyword system
 *
 * 62    4/19/99 7:56p Kevin
 * ifdef'd out some win32 specific stuff
 *
 * 61    4/19/99 6:10p Kevin
 * Demo now only has one multiplayer level
 *
 * 60    4/18/99 3:12p Jeff
 * got working with linux
 *
 * 59    4/16/99 3:17p Kevin
 * More mouselook support
 *
 * 58    4/14/99 3:06p Kevin
 * Force main mission to list even on small installations
 *
 * 57    4/08/99 4:54p Kevin
 * Display level warp dialog for multiplayer
 *
 * 56    4/08/99 3:42p Kevin
 * Added some stuff for the scoring API. Not functional yet.
 *
 * 55    4/03/99 9:26p Jeff
 * changed dialogs that weren't using UID_OK and UID_CANCEL to use and
 * handle them properly
 *
 * 54    3/25/99 3:29p Jason
 * added option to randomize powerup respawn points
 *
 * 53    3/25/99 3:26p Kevin
 * Made PXO games be based on your chat channel
 *
 * 52    3/24/99 1:41p Jeff
 * some dedicated server fixups...ability to set number of teams
 *
 * 51    3/17/99 4:08p Kevin
 * Changed the way games appear and timeout in the game list.
 *
 * 50    3/04/99 6:11p Kevin
 * Fixed mission name for OEM
 *
 * 49    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 48    3/02/99 1:18a Kevin
 *
 * 47    3/02/99 1:11a Kevin
 *
 * 46    3/01/99 9:37p Jeff
 * fixed missing semicolon
 *
 * 45    3/01/99 9:03p Kevin
 * OEM Beta 4
 *
 * 44    2/28/99 11:04p Jeff
 * handle Capture The Flag->CTF in Demo/OEM
 *
 * 43    2/19/99 5:21p Kevin
 * Fixed some connection DLLs and a Direct Sound bug with threads.
 *
 * 42    2/15/99 7:47p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 41    2/04/99 11:40a Kevin
 * Made listboxes sort
 *
 * 40    2/03/99 6:14p Kevin
 * OEM changes
 *
 * 39    2/03/99 4:20p Kevin
 * Got multiplayer working with .mn3 files, and setup autodownloading
 *
 * 38    1/11/99 12:29p Jeff
 * changes made not to call the module library directly
 *
 * 37    1/07/99 11:51a Kevin
 * Added support for joining servers on alternate ports and hosting behind
 * a proxy/firewall
 *
 * 36    12/30/98 3:49p Kevin
 * Moved multiplayer options out of DLL and into main app
 *
 * 35    12/30/98 12:16p Kevin
 * Auto Mission Download system
 *
 * 34    12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 33    12/18/98 11:00a Jason
 *
 * 32    12/15/98 10:53a Jason
 * yet more changes for 1.1
 *
 * 31    12/14/98 10:53a Jason
 * added bright player ships option
 *
 * 30    12/01/98 12:47p Jason
 * got rid of NF_DROPMISORDERED and added NF_USE_SMOOTHING
 *
 * 29    11/18/98 3:26p Kevin
 * Put multiplayer options into con_dll.h
 *
 * 28    10/19/98 11:07p Kevin
 * fixed bug
 *
 * 27    10/19/98 7:51p Kevin
 * performance testing
 *
 * 26    10/19/98 1:08p Kevin
 * Removed single player level from demo build
 *
 * 25    10/15/98 1:36p Jeff
 * updated dllinfo struct
 *
 * 24    10/13/98 12:03p Kevin
 * Changed use of preprocessors for debug, etc.
 *
 * 23    10/12/98 8:39p Kevin
 * removed mprintf's and fixed some smallish bugs
 *
 * 22    10/08/98 12:05p Kevin
 * Moved some start menu stuff around for Luke
 *
 * 21    10/07/98 11:45a Kevin
 * changed demo mission name
 *
 * 20    10/06/98 11:00a Kevin
 * Updated mission names for demo
 *
 * 19    10/01/98 11:37a Kevin
 * UI fixes and stuff
 *
 * 18    9/29/98 2:23p Kevin
 * More UI tweaks
 *
 * 17    9/28/98 9:53a Kevin
 * Fixing misc UI problems, and fixed some bugs that VC 6 found
 *
 * 16    9/24/98 12:50p Kevin
 * Added UI for rotational velocity and drop out of order packets in net
 * games
 *
 * 15    9/23/98 6:33p Kevin
 * Fixed load settings
 *
 * 14    9/23/98 2:55p Kevin
 * Saved multi config and changed UI to conform
 *
 * 13    9/22/98 3:55p Kevin
 * Removed obsolete function
 *
 * 12    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 11    9/21/98 11:19a Kevin
 * check protocol before entering multiplayer screens
 *
 * 10    9/16/98 8:06p Jason
 * got mastertracker working with the dedicated server
 *
 * 9     9/04/98 1:51p Kevin
 * implemented asyncronous gethostbyname
 *
 * 8     9/02/98 6:54p Kevin
 * Fixed general directplay support up, and got modem-modem working
 *
 * 7     8/31/98 10:14a Kevin
 * Misc. multi-UI fixes
 *
 * 6     8/27/98 5:03p Kevin
 * Prettied up multiplayer screens and fixed some bugs.
 *
 * 5     8/25/98 6:33p Kevin
 * pxo
 *
 * 4     8/24/98 5:04p Kevin
 * Made msn files have the option to not be playable in multiplayer
 *
 * 3     8/24/98 10:42a Kevin
 * Updated DLL for directplay and PXO background
 *
 * 2     8/19/98 11:50a Kevin
 * Got DirectPlay IPX working, and localized connection DLLs
 *
 * $NoKeywords: $
 */
///////////////////////////////////////////////

#include "ship.h"
#include "pstypes.h"

#if defined(__LINUX__) || defined(ANDROID)
#include <string.h>
#include "linux_fix.h"
#endif

// Uncomment out this line of code to build the demo version of the multiplayer connection dlls
// #define DEMO	1

// localization info
char **StringTable;
int StringTableSize = 0;
const char *_ErrorString = "Missing String";
const char *GetString(int d) {
  if ((d < 0) || (d >= StringTableSize))
    return _ErrorString;
  else
    return StringTable[d];
}
#define TXT(d) GetString(d)
///////////////////////////////////////////////
#define CHAR_LEFT_ARROW 24
#define CHAR_UP_ARROW 25
#define CHAR_RIGHT_ARROW 26
#define CHAR_DOWN_ARROW 27
#define CHAR_CHECKBOX_OFF 28
#define CHAR_CHECKBOX_ON 29
#define CHAR_RADIO_OFF 30
#define CHAR_RADIO_ON 31

#define DLL_UI_CANCEL 99

#define DLL_BRIEFING_FONT 1
#define DLL_BIG_BRIEFING_FONT 2

struct dllinfo {
  int me_handle;
  int it_handle;
  uint8_t *special_data;
  char *input_string;
  int input_key;
  union {
    int iRet;
    float fRet;
  };
  float fParam;
  ptrdiff_t iParam;
};

struct multi_api {
  int *objs;
  int *rooms;
  int *terrain;
  int *players;
  int *netgame;
  int *netplayers;
  int *ships;
  int *fp[200]; // function pointers
  int *vp[200]; // variable pointers
};

typedef void (*GetMultiAPI_fp)(multi_api *api);
GetMultiAPI_fp DLLGetMultiAPI;

typedef void (*SetUITextItemText_fp)(void *uit, char *newtext, uint32_t color);
SetUITextItemText_fp DLLSetUITextItemText;

typedef void *(*NewUIWindowCreate_fp)(int x, int y, int w, int h, int flags);
NewUIWindowCreate_fp DLLNewUIWindowCreate;

typedef void (*NewUIWindowDestroy_fp)(void *deswin);
NewUIWindowDestroy_fp DLLNewUIWindowDestroy;

typedef void (*NewUIWindowOpen_fp)(void *deswin);
NewUIWindowOpen_fp DLLNewUIWindowOpen;

typedef void (*NewUIWindowClose_fp)(void *deswin);
NewUIWindowClose_fp DLLNewUIWindowClose;

typedef void *(*TextCreate_fp)(void *parentwin, void *textitem, int x, int y, int flags);
TextCreate_fp DLLTextCreate;

typedef void *(*EditCreate_fp)(void *parentwin, int id, int x, int y, int w, int h, int flags);
EditCreate_fp DLLEditCreate;

typedef void *(*ButtonCreate_fp)(void *parentwin, int id, void *titleitem, int x, int y, int w, int h, int flags);
ButtonCreate_fp DLLButtonCreate;

typedef void *(*ListCreate_fp)(void *parentwin, int id, int x, int y, int w, int h, int flags);
ListCreate_fp DLLListCreate;

typedef void (*ListRemoveAll_fp)(void *item);
ListRemoveAll_fp DLLListRemoveAll;

typedef void (*ListAddItem_fp)(void *item, void *uitext);
ListAddItem_fp DLLListAddItem;

typedef void (*ListRemoveItem_fp)(void *item, void *txtitem);
ListRemoveItem_fp DLLListRemoveItem;

typedef void (*ListSelectItem_fp)(void *item, void *txtitem);
ListSelectItem_fp DLLListSelectItem;

typedef char *(*ListGetItem_fp)(void *item, int index);
ListGetItem_fp DLLListGetItem;

typedef int (*ListGetSelectedIndex_fp)(void *item);
ListGetSelectedIndex_fp DLLListGetSelectedIndex;

typedef void (*EditSetText_fp)(void *item, const char *buff);
EditSetText_fp DLLEditSetText;

typedef void (*EditGetText_fp)(void *item, char *buff, int len);
EditGetText_fp DLLEditGetText;

typedef void (*DatabaseWrite_fp)(const char *label, const char *entry, int entrylen);
DatabaseWrite_fp DLLDatabaseWrite;

typedef void (*DatabaseRead_fp)(const char *label, char *entry, int *entrylen);
DatabaseRead_fp DLLDatabaseRead;

typedef void (*DescentDefer_fp)(void);
DescentDefer_fp DLLDescentDefer;

typedef void (*DoMessageBox_fp)(const char *title, const char *msg, int type, ddgr_color title_color,
                                ddgr_color text_color);
DoMessageBox_fp DLLDoMessageBoxFP;
static inline void DLLDoMessageBox(const char *title, const char *msg, int type, ddgr_color title_color = GR_WHITE,
                            ddgr_color text_color = GR_WHITE) {
  DLLDoMessageBoxFP(title, msg, type, title_color, text_color);
}

typedef int (*DoUI_fp)(void);
DoUI_fp DLLDoUI;

typedef void (*Debug_ConsolePrintf_fp)(int n, const char *format, ...);
Debug_ConsolePrintf_fp DLLDebug_ConsolePrintf;

typedef void (*DedicatedServerPrintf_fp)(const char *format, ...);
DedicatedServerPrintf_fp DLLPrintDedicatedMessage;
/*
typedef int( *ValidateUser_fp) (validate_id_request *valid_id, char *trackerid);
ValidateUser_fp DLLValidateUser;

typedef void( *PollPTrackNet_fp) ();
PollPTrackNet_fp DLLPollPTrackNet;
*/
typedef void *(*NewUIGameWindowCreate_fp)(int x, int y, int w, int h, int flags);
NewUIGameWindowCreate_fp DLLNewUIGameWindowCreate;

typedef void (*NewUIGameWindowDestroy_fp)(void *item);
NewUIGameWindowDestroy_fp DLLNewUIGameWindowDestroy;

typedef void (*NewUIGameWindowOpen_fp)(void *item);
NewUIGameWindowOpen_fp DLLNewUIGameWindowOpen;

typedef void (*NewUIGameWindowClose_fp)(void *item);
NewUIGameWindowClose_fp DLLNewUIGameWindowClose;

typedef void (*SetScreenMode_fp)(int);
SetScreenMode_fp DLLSetScreenMode;

typedef float (*timer_GetTime_fp)(void);
timer_GetTime_fp DLLtimer_GetTime;

typedef int (*TryToJoinServer_fp)(network_address *addr);
TryToJoinServer_fp DLLTryToJoinServer;

typedef void (*MultiStartClient_fp)(char *scriptname);
MultiStartClient_fp DLLMultiStartClient;

typedef void (*rend_GetRenderState_fp)(rendering_state *rstate);
rend_GetRenderState_fp DLLrend_GetRenderState;

typedef bool (*LoadMission_fp)(char *msn);
LoadMission_fp DLLLoadMission;

typedef void (*ddio_MakePath_fp)(char *newPath, const char *absolutePathHeader, const char *subDir, ...);
ddio_MakePath_fp DLLddio_MakePath;

typedef bool (*ddio_FindFileStart_fp)(const char *wildcard, char *namebuf);
ddio_FindFileStart_fp DLLddio_FindFileStart;

typedef void (*ddio_FindFileClose_fp)();
ddio_FindFileClose_fp DLLddio_FindFileClose;

typedef bool (*ddio_FindNextFile_fp)(char *namebuf);
ddio_FindNextFile_fp DLLddio_FindNextFile;

// typedef void( *MultiStartServer_fp) (int playing,char *scriptname,int dedicated_num_teams=-1);
typedef void (*MultiStartServer_fp)(int playing, char *scriptname, int dedicated_num_teams);
MultiStartServer_fp DLLMultiStartServerFP;
static inline void DLLMultiStartServer(int playing, char *scriptname, int dedicated_num_teams = -1) {
  DLLMultiStartServerFP(playing, scriptname, dedicated_num_teams);
}

typedef void (*ShowProgressScreen_fp)(const char *, const char *);
ShowProgressScreen_fp DLLShowProgressScreen;

typedef int (*SearchForLocalGamesTCP_fp)(uint32_t, uint16_t);
SearchForLocalGamesTCP_fp DLLSearchForLocalGamesTCP;

typedef int (*nw_GetHostAddressFromNumbers_fp)(char *str);
nw_GetHostAddressFromNumbers_fp DLLnw_GetHostAddressFromNumbers;

typedef int (*nw_GetProtocolType_fp)(void);
nw_GetProtocolType_fp DLLnw_GetProtocolType;

typedef void *(*HotSpotCreate_fp)(void *parentwin, int id, int key, void *txtitemoff, void *txtitemon, int x, int y,
                                  int w, int h, int flags);
HotSpotCreate_fp DLLHotSpotCreate;

typedef int (*PollUI_fp)(void);
PollUI_fp DLLPollUI;

typedef const char *(*GetMissionName_fp)(const char *mission);
GetMissionName_fp DLLGetMissionName;

typedef void (*RemoveUITextItem_fp)(void *item);
RemoveUITextItem_fp DLLRemoveUITextItem;

typedef void *(*CreateNewUITextItem_fp)(const char *newtext, uint32_t color, int font);
CreateNewUITextItem_fp DLLCreateNewUITextItemFP;
static inline void *DLLCreateNewUITextItem(const char *newtext, uint32_t color, int font = -1) {
  return DLLCreateNewUITextItemFP(newtext, color, font);
}

typedef void *(*mem_malloc_fp)(int size);
mem_malloc_fp DLLmem_malloc;

typedef void (*mem_free_fp)(void *memblock);
mem_free_fp DLLmem_free;

typedef void (*CreateSplashScreen_fp)(const char *msg, int usecancel);
CreateSplashScreen_fp DLLCreateSplashScreen;

typedef void (*CloseSplashScreen_fp)(void);
CloseSplashScreen_fp DLLCloseSplashScreen;

typedef void *(*UIConsoleGadgetCreate_fp)(void *parentid, int id, int x, int y, int font, int cols, int rows,
                                          int flags);
UIConsoleGadgetCreate_fp DLLUIConsoleGadgetCreate;

typedef void (*UIConsoleGadgetputs_fp)(void *item, const char *str);
UIConsoleGadgetputs_fp DLLUIConsoleGadgetputs;

typedef void (*NewUIWindowSetFocusOnEditGadget_fp)(void *item, void *parent);
NewUIWindowSetFocusOnEditGadget_fp DLLNewUIWindowSetFocusOnEditGadget;

typedef void *(*OldEditCreate_fp)(void *parentitem, int id, int x, int y, int w, int h, int flags);
OldEditCreate_fp DLLOldEditCreate;

typedef void *(*OldListCreate_fp)(void *parentitem, int id, int x, int y, int w, int h, int flags);
OldListCreate_fp DLLOldListCreate;

typedef void (*OldListRemoveAll_fp)(void *item);
OldListRemoveAll_fp DLLOldListRemoveAll;

typedef void (*OldListAddItem_fp)(void *item, void *uitext);
OldListAddItem_fp DLLOldListAddItem;

typedef void (*OldListRemoveItem_fp)(void *item, void *txtitem);
OldListRemoveItem_fp DLLOldListRemoveItem;

typedef void (*OldListSelectItem_fp)(void *item, void *txtitem);
OldListSelectItem_fp DLLOldListSelectItem;

typedef char *(*OldListGetItem_fp)(void *item, int index);
OldListGetItem_fp DLLOldListGetItem;

typedef int (*OldListGetSelectedIndex_fp)(void *item);
OldListGetSelectedIndex_fp DLLOldListGetSelectedIndex;

typedef void (*OldEditSetText_fp)(void *item, const char *newtext);
OldEditSetText_fp DLLOldEditSetText;

typedef void (*OldEditGetText_fp)(void *item, char *buff, int len);
OldEditGetText_fp DLLOldEditGetText;

typedef void (*ToggleUICallback_fp)(int state);
ToggleUICallback_fp DLLToggleUICallback;

typedef int (*SearchForGamesPXO_fp)(uint32_t ask, uint16_t port);
SearchForGamesPXO_fp DLLSearchForGamesPXO;

typedef void (*SetOldEditBufferLen_fp)(void *item, int len);
SetOldEditBufferLen_fp DLLSetOldEditBufferLen;

typedef void (*NewUIWindowLoadBackgroundImage_fp)(void *item, const char *image_name);
NewUIWindowLoadBackgroundImage_fp DLLNewUIWindowLoadBackgroundImage;

typedef void (*DeleteUIItem_fp)(void *delitem);
DeleteUIItem_fp DLLDeleteUIItem;

typedef int (*SearchForLocalGamesIPX_fp)(network_address *check_addr);
SearchForLocalGamesIPX_fp DLLSearchForLocalGamesIPX;

typedef void (*HotSpotSetStates_fp)(void *hotspot, void *texton, void *textoff);
HotSpotSetStates_fp DLLHotSpotSetStates;

typedef bool (*PlayerSetShipPermission_fp)(int pnum, char *ship_name, bool allowed);
PlayerSetShipPermission_fp DLLPlayerSetShipPermission;

typedef bool (*PlayerIsShipAllowed_fp)(int pnum, int ship_index);
PlayerIsShipAllowed_fp DLLPlayerIsShipAllowed;

#ifdef WIN32
typedef int (*dp_ListDirectPlayGames_fp)();
dp_ListDirectPlayGames_fp DLLdp_ListDirectPlayGames;

typedef int (*dp_InitDirectPlay_fp)(char *conn_name, void *parms, int num_elements);
dp_InitDirectPlay_fp DLLdp_InitDirectPlay;

typedef int (*dp_GetModemChoices_fp)(char *buffer, uint32_t *size);
dp_GetModemChoices_fp DLLdp_GetModemChoices;
#endif

// Given a filename, pointer to a char * array and a pointer to an int,
// it will load the string table and fill in the information
// returns true on success
typedef bool (*CreateStringTable_fp)(const char *filename, char ***table, int *size);
CreateStringTable_fp DLLCreateStringTable;

// Given a string table and it's count of strings, it will free up it's memory
typedef void (*DestroyStringTable_fp)(char **table, int size);
DestroyStringTable_fp DLLDestroyStringTable;

typedef void (*DatabaseReadInt_fp)(const char *label, int *val);
DatabaseReadInt_fp DLLDatabaseReadInt;

typedef void (*DatabaseWriteInt_fp)(const char *label, int val);
DatabaseWriteInt_fp DLLDatabaseWriteInt;

typedef void (*DoScreenshot_fp)();
DoScreenshot_fp DLLDoScreenshot;

typedef bool (*IsMissionMultiPlayable_fp)(char *mission);
IsMissionMultiPlayable_fp DLLIsMissionMultiPlayable;

//	returns width of text in current font.
typedef int (*grtext_GetTextLineWidth_fp)(const char *str);
grtext_GetTextLineWidth_fp DLLgrtext_GetTextLineWidth;

typedef void (*GadgetDestroy_fp)(void *item);
GadgetDestroy_fp DLLGadgetDestroy;

#ifdef WIN32
typedef int (*dp_StartGame_fp)(char *gamename);
dp_StartGame_fp DLLdp_StartGame;

typedef void (*dp_EndGame_fp)();
dp_EndGame_fp DLLdp_EndGame;
#endif

typedef int (*nw_Asyncgethostbyname_fp)(uint32_t *ip, int command, const char *hostname);
nw_Asyncgethostbyname_fp DLLnw_Asyncgethostbyname;

typedef int (*nw_ReccomendPPS_fp)();
nw_ReccomendPPS_fp DLLnw_ReccomendPPS;

typedef void (*DoMultiAllowed_fp)(void);
DoMultiAllowed_fp DLLDoMultiAllowed;

typedef void (*MultiDoConfigSave_fp)(void);
MultiDoConfigSave_fp DLLMultiDoConfigSave;

typedef void (*MultiDoConfigLoad_fp)(void);
MultiDoConfigLoad_fp DLLMultiDoConfigLoad;

typedef int (*MultiLoadSettings_fp)(const char *filename);
MultiLoadSettings_fp DLLMultiLoadSettings;

typedef void *(*NetworkReceiveCallback)(uint8_t *data, int len, network_address *from);

typedef void (*HandleGamePacket_fp)(uint8_t *data, int len, network_address *from);

typedef int (*nw_RegisterCallback_fp)(HandleGamePacket_fp, uint8_t id);
nw_RegisterCallback_fp DLLnw_RegisterCallback;

typedef NetworkReceiveCallback (*nw_UnRegisterCallback_fp)(uint8_t id);
nw_UnRegisterCallback_fp DLLnw_UnRegisterCallback;

typedef int (*nw_SendWithID_fp)(uint8_t id, uint8_t *data, int len, network_address *who_to);
nw_SendWithID_fp DLLnw_SendWithID;

typedef int (*nw_DoReceiveCallbacks_fp)(void);
nw_DoReceiveCallbacks_fp DLLnw_DoReceiveCallbacks;

typedef int (*msn_CheckGetMission_fp)(network_address *net_addr, char *filename);
msn_CheckGetMission_fp DLLmsn_CheckGetMission;

typedef void (*MultiGameOptionsMenu_fp)(int alloptions);
MultiGameOptionsMenu_fp DLLMultiGameOptionsMenu;

// Loads a dynamic module into memory for use.
// Returns true on success, false otherwise
// typedef bool (*mod_LoadModule_fp)(module *handle,const char *modfilename,int flags=MODF_NOW);
typedef bool (*mod_LoadModule_fp)(module *handle, const char *modfilename, int flags);
mod_LoadModule_fp DLLmod_LoadModule;

// Frees a previously loaded module from memory, it can no longer be used
// Returns true on success, false otherwise
typedef bool (*mod_FreeModule_fp)(module *handle);
mod_FreeModule_fp DLLmod_FreeModule;

// Returns a pointer to a function within a loaded module.  If it returns NULL there was an error.  Check
// mod_GetLastError to see if there was an error symstr is the name of the function you want to get the symbol for (Do
// NOT give any pre/suffix to this name) parmbytes is the size (in bytes) of the parameter list the function should have
typedef MODPROCADDRESS (*mod_GetSymbol_fp)(module *handle, const char *symstr, uint8_t parmbytes);
mod_GetSymbol_fp DLLmod_GetSymbol;

// Returns an error code to what the last error was.  When this function is called the last error is cleared, so by
// calling this function it not only returns the last error, but it removes it, so if you were to call this function
// again, it would return no error
typedef int (*mod_GetLastError_fp)(void);
mod_GetLastError_fp DLLmod_GetLastError;

// "Current Pilot" name access function
typedef void (*CurrentPilotName_fp)(char *buffer);
CurrentPilotName_fp CurrentPilotName;

typedef void (*UpdateAndPackGameList_fp)(void);
UpdateAndPackGameList_fp DLLUpdateAndPackGameList;

typedef int (*MultiLevelSelection_fp)(void);
MultiLevelSelection_fp DLLMultiLevelSelection;

typedef bool (*DoPlayerMouselookCheck_fp)(uint32_t flags);
DoPlayerMouselookCheck_fp DLLDoPlayerMouselookCheck;

typedef int (*CheckMissionForScript_fp)(char *mission, char *script, int dedicated_server_num_teams);
CheckMissionForScript_fp DLLCheckMissionForScript;

typedef void (*ShowNetgameInfo_fp)(network_game *game);
ShowNetgameInfo_fp DLLShowNetgameInfo;

typedef int (*CheckGetD3M_fp)(char *d3m);
CheckGetD3M_fp DLLCheckGetD3M;

int DLLUIClass_CurrID = 0xD0;

#define MAX_NET_GAMES 100
#define JEFF_RED GR_RGB(255, 40, 40)
#define JEFF_BLUE GR_RGB(40, 40, 255)
#define JEFF_GREEN GR_RGB(40, 255, 40)
#define NETPOLLINTERVAL 10.0

extern int MTAVersionCheck(uint32_t oldver, char *URL);

#define LOGIN_LEN 33
#define REAL_NAME_LEN 66
#define PASSWORD_LEN 17
#define EMAIL_LEN 100
#define TRACKER_ID_LEN 10
#define PILOT_NAME_LEN 20

#ifdef WIN32
#pragma pack(push, pxo)
#endif
#pragma pack(1)
struct vmt_descent3_struct {
  char tracker_id[TRACKER_ID_LEN];
  char pilot_name[PILOT_NAME_LEN];
  int rank;

  int kills;
  int deaths;
  int suicides;
  int online_time;
  int games_played;
  uint32_t security;
  uint8_t virgin_pilot; // This pilot was just created if TRUE
  uint32_t lateral_thrust;
  uint32_t rotational_thrust;
  uint32_t sliding_pct; // Percentage of the time you were sliding
  uint32_t checksum;   // This value needs to be equal to whatever the checksum is once the packet is decoded
  uint32_t pad; // just to provide room for out 4 byte encryption boundry only needed on the client side for now
};
#define DESCENT3_BLOCK_SIZE (sizeof(vmt_descent3_struct) - 4)
#ifdef WIN32
#pragma pack(pop, pxo)
#else
#pragma pack()
#endif

/////////////////////////////
// Defines
#ifndef RELEASE
#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)
#else
#define DLLmprintf(...)
#endif

uint32_t MTClientVer = 100;

char MTUpdateURL[300] = "";

multi_api API;

player *DLLMPlayers;
ship *DLLShips;
vmt_descent3_struct *DLLMTPilotinfo;
int DLLPlayer_num;
int *DLLGame_is_master_tracker_game;
int DLLGame_mode;
char *DLLTracker_id;
int *DLLNum_directplay_games;
netgame_info *DLLNetgame;
char *DLLLocalD3Dir;
int *DLLMultiGameStarting;
netplayer *DLLMNetPlayers;
int MTWritingPilot, MTReadingPilot;
int UnvalidatedDLL = 0;
int *DLLNum_network_games_known;
bool *DLLDedicated_server;
network_game *DLLNetwork_games;
int MT_Initialized = 0;
uint8_t *DLLNewUIWindow_alpha;
float LastTrackerDataUpdate;
void *pconsole = NULL;
bool *DLLDP_active;
bool *DLLUse_DirectPlay;
bool *DLLMulti_Gamelist_changed;
bool *DLLSupports_score_api;
// bool * DLLMulti_no_stats_saved;
uint16_t DLLnw_ListenPort;

char szloginid[LOGIN_LEN] = "";
char sztrackerid[TRACKER_ID_LEN] = "";
char szpassword[PASSWORD_LEN] = "";

char *DLLHelpText1;
char *DLLHelpText2;
char *DLLHelpText3;
char *DLLHelpText4;

char *DLLPXO_hosted_lobby_name = NULL;

#define DLLMAX_SHIPS 30

#define PARENT0 0
#define PARENT1 1
#define PARENT2 2
#define PARENT3 3
#define PARENT4 4

char *DLLAuto_login_name;
char *DLLAuto_login_pass;
char *DLLAuto_login_addr;
char *DLLAuto_login_port;

bool Use_netgame_flags;

module MTAVDLLHandle = {NULL};

#if defined(WIN32)
typedef void(DLLFUNCCALL DLLAVInit_fp)(int *ptr);
typedef void(DLLFUNCCALL DLLAVCall_fp)(int eventnum);
typedef void(DLLFUNCCALL DLLAVClose_fp)();
typedef void(DLLFUNCCALL DLLAVGetVersion_fp)(int *version);
typedef void(DLLFUNCCALL DLLRunCheck_fp)(char *d3_path);
#elif defined(__LINUX__) || defined(ANDROID)
typedef void DLLFUNCCALL(DLLAVInit_fp)(int *ptr);
typedef void DLLFUNCCALL(DLLAVCall_fp)(int eventnum);
typedef void DLLFUNCCALL(DLLAVClose_fp)();
typedef void DLLFUNCCALL(DLLAVGetVersion_fp)(int *version);
typedef void DLLFUNCCALL(DLLRunCheck_fp)(char *d3_path);
#endif

DLLAVInit_fp *DLLAVInit = NULL;
DLLAVCall_fp *DLLAVCall = NULL;
DLLAVClose_fp *DLLAVClose = NULL;
DLLAVGetVersion_fp *DLLAVGetVersion = NULL;
DLLRunCheck_fp *DLLRunCheck = NULL;

struct msn_list {
  char msn_name[_MAX_PATH];
  char msn_file[_MAX_PATH];
  void *ti;
  struct msn_list *next;
};

msn_list *FirstMsn, *CurrMsn, *TmpMsn;

#ifdef WIN32
#include "directplay.h"

modem_list *DLLModems_found;
int *DLLNum_modems_found;

LPDPSESSIONDESC2 DLLDirectplay_sessions;
#endif

BOOL DLLTCP_active;
BOOL DLLIPX_active;

void AddMsnItem(msn_list *new_msn) {
  CurrMsn = FirstMsn;
  if (CurrMsn) {
    while (CurrMsn->next) {
      CurrMsn = CurrMsn->next;
    }
    CurrMsn->next = new_msn;
    CurrMsn = CurrMsn->next;
  } else {
    FirstMsn = new_msn;
    CurrMsn = FirstMsn;
  }
  CurrMsn->next = NULL;
}
void RemoveAllMsnItems(void) {
  CurrMsn = FirstMsn;
  if (CurrMsn) {
    while (CurrMsn->next) {
      TmpMsn = CurrMsn;
      DLLRemoveUITextItem(CurrMsn->ti);
      CurrMsn = CurrMsn->next;
      DLLmem_free(TmpMsn);
    }
    DLLRemoveUITextItem(CurrMsn->ti);
    DLLmem_free(CurrMsn);
  }
  FirstMsn = NULL;
}

msn_list *FindMsnItem(const char *name) {
  CurrMsn = FirstMsn;
  if (CurrMsn) {
    while (CurrMsn->next) {
      if (strcmp(CurrMsn->msn_name, name) == 0)
        return CurrMsn;
      CurrMsn = CurrMsn->next;
    }
    if (strcmp(CurrMsn->msn_name, name) == 0)
      return CurrMsn;
  }
  return NULL;
}

void MultiplayerOptionsMenu();

// Draws a menu that inputs multiplayer game options
// Returns true if we are starting a game
#define MAX_DLLS 40
char dll_text[MAX_DLLS][_MAX_PATH];

int StartMultiplayerGameMenu() {
  void *game_name_text = DLLCreateNewUITextItem(TXT(10), UICOL_TEXT_NORMAL, -1);    // TXT_LC_GAMENAME
  void *mission_name_text = DLLCreateNewUITextItem(TXT(11), UICOL_TEXT_NORMAL, -1); // TXT_LC_MSNNAME
  void *script_name_text = DLLCreateNewUITextItem(TXT(12), UICOL_TEXT_NORMAL, -1);  // TXT_LC_SCRIPTNAME

  void *start_game_on_text = DLLCreateNewUITextItem(TXT(13), UICOL_HOTSPOT_HI, -1);       // TXT_LC_STARTGAME
  void *multiplayer_opts_on_text = DLLCreateNewUITextItem(TXT(14), UICOL_HOTSPOT_HI, -1); // TXT_LC_MPLYROPTIONS
  void *exit_on_text = DLLCreateNewUITextItem(TXT(5), UICOL_HOTSPOT_HI, -1);              // TXT_LC_PREVMENU

  void *start_game_off_text = DLLCreateNewUITextItem(TXT(13), UICOL_HOTSPOT_LO, -1);       // TXT_LC_STARTGAME
  void *multiplayer_opts_off_text = DLLCreateNewUITextItem(TXT(14), UICOL_HOTSPOT_LO, -1); // TXT_LC_MPLYROPTIONS
  void *exit_off_text = DLLCreateNewUITextItem(TXT(5), UICOL_HOTSPOT_LO, -1);              // TXT_LC_PREVMENU

  void *save_settings_txt_on = DLLCreateNewUITextItem(TXT_DLL_SAVESETTINGS, UICOL_HOTSPOT_HI, -1);
  void *save_settings_txt_off = DLLCreateNewUITextItem(TXT_DLL_SAVESETTINGS, UICOL_HOTSPOT_LO, -1);

  void *load_settings_txt_on = DLLCreateNewUITextItem(TXT_DLL_LOADSETTINGS, UICOL_HOTSPOT_HI, -1);
  void *load_settings_txt_off = DLLCreateNewUITextItem(TXT_DLL_LOADSETTINGS, UICOL_HOTSPOT_LO, -1);

  void *start_text = DLLCreateNewUITextItem(TXT(13), UICOL_WINDOW_TITLE, DLL_BIG_BRIEFING_FONT);

  void *blank_text = DLLCreateNewUITextItem("", GR_BLACK, -1);
  void *dll_txt_items[MAX_DLLS];
  int a;
  for (a = 0; a < MAX_DLLS; a++)
    dll_txt_items[a] = NULL;
  char str[100];
  int exit_menu = 0;
  int cury = 40;
  int ret = 0;
  int dllcount = 0;
  int id = 100;

  rendering_state rs;
  DLLrend_GetRenderState(&rs);

  void *main_wnd = DLLNewUIWindowCreate(0, 0, rs.screen_width, rs.screen_height, UIF_PROCESS_ALL);

  void *start_title = DLLTextCreate(main_wnd, start_text, 0, cury, UIF_CENTER);
  cury += 35;

  // Mission name
  void *mission_text = DLLTextCreate(main_wnd, game_name_text, 0, cury, UIF_CENTER);
  cury += 15;
  void *mission_name_edit = DLLEditCreate(main_wnd, id++, 10, cury, 300, 15, UIF_CENTER);
  cury += 18;
  cury += 30;

  // mission name
  void *game_name = DLLTextCreate(main_wnd, mission_name_text, 45, cury, 0);
  cury += 15;

  void *list_1 = DLLListCreate(main_wnd, id++, 40, cury, 200, 100, 0);

  // Back up the the same line!
  cury -= 15;

  // Script box
  void *script_name = DLLTextCreate(main_wnd, script_name_text, 370, cury, 0);
  cury += 18;
  void *script_list = DLLListCreate(main_wnd, id++, 360, cury, 200, 100, 0);
  cury += 118;
  cury += 40;

  // Start button
  int start_button = UID_OK;
  void *start_hs = DLLHotSpotCreate(main_wnd, UID_OK, KEY_ENTER, start_game_off_text, start_game_on_text, 10, cury, 180,
                                    30, UIF_FIT | UIF_CENTER);
  cury += 18;

  // Option button
  int option_button = id;
  void *option_hs = DLLHotSpotCreate(main_wnd, id++, KEY_O, multiplayer_opts_off_text, multiplayer_opts_on_text, 10,
                                     cury, 180, 30, UIF_FIT | UIF_CENTER);
  cury += 18;

  // cancel button

  int save_button = id;
  void *save_hs = DLLHotSpotCreate(main_wnd, id++, 0, save_settings_txt_off, save_settings_txt_on, 10, cury, 180, 30,
                                   UIF_FIT | UIF_CENTER);
  cury += 18;
  int load_button = id;
  void *load_hs = DLLHotSpotCreate(main_wnd, id++, 0, load_settings_txt_off, load_settings_txt_on, 10, cury, 180, 30,
                                   UIF_FIT | UIF_CENTER);
  cury += 18;

  int cancel_button = UID_CANCEL;
  void *cancel_hs = DLLHotSpotCreate(main_wnd, UID_CANCEL, KEY_ESC, exit_off_text, exit_on_text, 10, cury, 180, 30,
                                     UIF_FIT | UIF_CENTER);
  // put the multiplayer dll's into the listbox
  dllcount = 1;
  char buffer[_MAX_PATH];

#if (!(defined(OEM) || defined(DEMO)))
  char search[256];
  DLLddio_MakePath(search, DLLLocalD3Dir, "netgames", "*.d3m", NULL);
  if (DLLddio_FindFileStart(search, buffer)) {
    dllcount = 1;
    buffer[strlen(buffer) - 4] = '\0'; // Strip out the extention
    strcpy(dll_text[dllcount - 1], buffer);
    while ((DLLddio_FindNextFile(buffer)) && (dllcount < MAX_DLLS)) {
      buffer[strlen(buffer) - 4] = '\0'; // Strip out the extention
      strcpy(dll_text[dllcount], buffer);
      dllcount++;
    }
  } else {
    dllcount = 0;
  }
  DLLddio_FindFileClose();
#else
  strcpy(dll_text[0], "Anarchy");
  strcpy(dll_text[1], "Capture The Flag");
  dllcount = 2;
#endif
  DLLListRemoveAll(script_list);

  int index;

  for (index = 0; index < dllcount; index++) {
    dll_txt_items[index] = DLLCreateNewUITextItem(dll_text[index], UICOL_LISTBOX_LO, -1);
    DLLListAddItem(script_list, dll_txt_items[index]);
  }
#if (!(defined(OEM) || defined(DEMO)))
  msn_list *mi;

  DLLddio_MakePath(search, DLLLocalD3Dir, "data", "levels", "*.msn", NULL);
  // DLLmprintf((0,search));
  if (DLLddio_FindFileStart(search, buffer)) {
    if (DLLIsMissionMultiPlayable(buffer)) {
      DLLmprintf(0, "Found a mission: %s\n", buffer);
      mi = (msn_list *)DLLmem_malloc(sizeof(msn_list));
      strcpy(mi->msn_name, DLLGetMissionName(buffer));
      strcpy(mi->msn_file, buffer);
      mi->ti = DLLCreateNewUITextItem(mi->msn_name, UICOL_LISTBOX_LO, -1);
      AddMsnItem(mi);
      DLLListAddItem(list_1, mi->ti);
    }
    while (DLLddio_FindNextFile(buffer)) {
      if (DLLIsMissionMultiPlayable(buffer)) {
        DLLmprintf(0, "Found a mission: %s\n", buffer);
        mi = (msn_list *)DLLmem_malloc(sizeof(msn_list));
        strcpy(mi->msn_name, DLLGetMissionName(buffer));
        strcpy(mi->msn_file, buffer);
        mi->ti = DLLCreateNewUITextItem(mi->msn_name, UICOL_LISTBOX_LO, -1);
        AddMsnItem(mi);
        DLLListAddItem(list_1, mi->ti);
      }
    }
  }
  DLLddio_FindFileClose();

  // char mn3_path[_MAX_PATH*2];
  DLLddio_MakePath(search, DLLLocalD3Dir, "missions", "*.mn3", NULL);
  // DLLmprintf(0,search);
  if (DLLddio_FindFileStart(search, buffer)) {
    // DLLddio_MakePath(mn3_path,DLLLocalD3Dir,"missions",buffer,NULL);

    if (DLLIsMissionMultiPlayable(buffer) && (stricmp("d3_2.mn3", buffer) != 0)) {
      DLLmprintf(0, "Found a mission: %s\n", buffer);
      mi = (msn_list *)DLLmem_malloc(sizeof(msn_list));
      strcpy(mi->msn_name, DLLGetMissionName(buffer));
      strcpy(mi->msn_file, buffer);
      mi->ti = DLLCreateNewUITextItem(mi->msn_name, UICOL_LISTBOX_LO, -1);
      AddMsnItem(mi);
      DLLListAddItem(list_1, mi->ti);
    }
    while (DLLddio_FindNextFile(buffer)) {
      if (stricmp("d3_2.mn3", buffer) == 0)
        continue;
      // DLLddio_MakePath(mn3_path,DLLLocalD3Dir,"missions",buffer,NULL);
      if (DLLIsMissionMultiPlayable(buffer)) {
        DLLmprintf(0, "Found a mission: %s\n", buffer);
        mi = (msn_list *)DLLmem_malloc(sizeof(msn_list));
        strcpy(mi->msn_name, DLLGetMissionName(buffer));
        strcpy(mi->msn_file, buffer);
        mi->ti = DLLCreateNewUITextItem(mi->msn_name, UICOL_LISTBOX_LO, -1);
        AddMsnItem(mi);
        DLLListAddItem(list_1, mi->ti);
      }
    }
  }
  DLLddio_FindFileClose();
#ifdef RELEASE
  // TODO: Make sure the main mission is always listed -- even on a minimal install
  if (!FindMsnItem("Descent 3: Retribution")) {
    mi = (msn_list *)DLLmem_malloc(sizeof(msn_list));

    strcpy(mi->msn_name, "Descent 3: Retribution");
    strcpy(mi->msn_file, "d3.mn3");
    AddMsnItem(mi);
    mi->ti = DLLCreateNewUITextItem(mi->msn_name, UICOL_LISTBOX_LO);
    DLLListAddItem(list_1, mi->ti);
  }
#endif
  const char *p;
#else
  void *msn_single_ti = DLLCreateNewUITextItem("Polaris", UICOL_LISTBOX_LO);
  void *msn_multi_ti = DLLCreateNewUITextItem("The Core", UICOL_LISTBOX_LO);
  void *msn_multi_2 = DLLCreateNewUITextItem("Taurus", UICOL_LISTBOX_LO);
  DLLListAddItem(list_1, msn_single_ti);
  DLLListAddItem(list_1, msn_multi_ti);
  DLLListAddItem(list_1, msn_multi_2);
#endif
  // Bash some values to default
  char pilot_name[PILOT_STRING_SIZE];
  CurrentPilotName(pilot_name);

  strcpy(DLLMPlayers[DLLPlayer_num].callsign, pilot_name);
  snprintf(str, sizeof(str), "%s's Game", DLLMPlayers[DLLPlayer_num].callsign);
  DLLEditSetText(mission_name_edit, str);

  DLLNetgame->max_players = 8;
  DLLNetgame->packets_per_second = DLLnw_ReccomendPPS();
  DLLNetgame->respawn_time = 60;
  DLLNetgame->difficulty = 2;
  DLLNetgame->flags = NF_RANDOMIZE_RESPAWN;
  DLLNewUIWindowLoadBackgroundImage(main_wnd, "multimain.ogf");
  DLLNewUIWindowOpen(main_wnd);
  char dftset[_MAX_PATH * 2];
  DLLddio_MakePath(dftset, DLLLocalD3Dir, "custom", "settings", "default.mps", NULL);
  if (DLLMultiLoadSettings(dftset)) {
    DLLEditSetText(mission_name_edit, DLLNetgame->name);
#if (!(defined(OEM) || defined(DEMO)))
    p = DLLGetMissionName(DLLNetgame->mission);
    mi = FindMsnItem(p);

    if (mi)
      DLLListSelectItem(list_1, mi->ti);
#endif
    for (index = 0; index < dllcount; index++) {
      if (stricmp(dll_text[index], DLLNetgame->scriptname) == 0) {
        DLLListSelectItem(script_list, dll_txt_items[index]);
        break;
      }
    }
  }
  while (!exit_menu) {
    int res;

    res = DLLDoUI();

    // handle all UI results.

    if (res == option_button) {
      DLLNewUIWindowClose(main_wnd);
      MultiplayerOptionsMenu();
      DLLNewUIWindowOpen(main_wnd);
    } else if (res == start_button) {
      // Get Game name
      DLLEditGetText(mission_name_edit, DLLNetgame->name, NETGAME_NAME_LEN);
      // Get mission name
#if (!(defined(OEM) || defined(DEMO)))
      mi = FindMsnItem(DLLListGetItem(list_1, DLLListGetSelectedIndex(list_1)));
      if (!mi)
        break;
      strncpy(DLLNetgame->mission, mi->msn_file, MSN_NAMELEN);
      DLLNetgame->mission[MSN_NAMELEN - 1] = '\0';
      strncpy(DLLNetgame->mission_name, mi->msn_name, MISSION_NAME_LEN);
      DLLNetgame->mission_name[MISSION_NAME_LEN - 1] = '\0';
#else
      // strcpy(DLLNetgame->mission,DLLListGetSelectedIndex(list_1)?"thecore.d3l":"polaris.d3l");

      switch (DLLListGetSelectedIndex(list_1)) {
      case 0:
        strcpy(DLLNetgame->mission, "polaris.d3l");
        strncpy(DLLNetgame->mission_name, "Polaris", MISSION_NAME_LEN);
        break;
      case 1:
        strcpy(DLLNetgame->mission, "thecore.d3l");
        strncpy(DLLNetgame->mission_name, "The Core", MISSION_NAME_LEN);
        break;
      case 2:

        strcpy(DLLNetgame->mission, "taurus.d3l");
        strncpy(DLLNetgame->mission_name, "Taurus", MISSION_NAME_LEN);

        break;
      default:;
      }

      // strcpy(DLLNetgame->name,DLLListGetSelectedIndex(list_1)?"The Core":"Polaris");
#endif
      // Get script
      strcpy(buffer, DLLListGetItem(script_list, DLLListGetSelectedIndex(script_list)));
      if (strcmp(buffer, "None")) {
        // remove file extension
        for (int d = strlen(buffer) - 1; d >= 0; d--) {
          if (buffer[d] == '.') {
            buffer[d] = '\0';
            break;
          }
        }

#if (defined(OEM) || defined(DEMO))
        if (!stricmp(buffer, "Capture The Flag"))
          strcpy(buffer, "CTF");
#endif

        strcpy(DLLNetgame->scriptname, buffer);
      }

      // Actually start the game
      // DAJ commen out next line if problems
      int teams = DLLCheckMissionForScript(DLLNetgame->mission, DLLNetgame->scriptname, 0);
      //			int teams = 1;
      if (teams >= 0)
#if (!(defined(OEM) || defined(DEMO)))
      {
        if (DLLLoadMission(DLLNetgame->mission))
#else
      {
        if (DLLLoadMission(DLLNetgame->mission))
#endif
        {
          // Do warp dialog here if needed
          if (-1 != DLLMultiLevelSelection()) {
            DLLmprintf(0, "Mission loaded successfully!\n");
            DLLMultiStartServer(1, DLLNetgame->scriptname, teams);
            exit_menu = 1;
            ret = 1;
          }
        }
      }
    } else if (res == cancel_button) {
      exit_menu = 1;
    } else if (res == save_button) {
      // Get Game name
      DLLEditGetText(mission_name_edit, DLLNetgame->name, NETGAME_NAME_LEN);
#if (!(defined(OEM) || defined(DEMO)))
      // Get mission name
      mi = FindMsnItem(DLLListGetItem(list_1, DLLListGetSelectedIndex(list_1)));
      if (!mi)
        break;
      strcpy(DLLNetgame->mission, mi->msn_file);
#endif
      // Get script
      strcpy(buffer, DLLListGetItem(script_list, DLLListGetSelectedIndex(script_list)));
      if (strcmp(buffer, "None")) {
        // remove file extension
        for (int d = strlen(buffer) - 1; d >= 0; d--) {
          if (buffer[d] == '.') {
            buffer[d] = '\0';
            break;
          }
        }

        strcpy(DLLNetgame->scriptname, buffer);
      }
      DLLMultiDoConfigSave();
    } else if (res == load_button) {
      // Get Game name
      DLLEditGetText(mission_name_edit, DLLNetgame->name, NETGAME_NAME_LEN);
#if (!(defined(OEM) || defined(DEMO)))
      // Get mission name
      mi = FindMsnItem(DLLListGetItem(list_1, DLLListGetSelectedIndex(list_1)));
      if (!mi)
        break;
      strcpy(DLLNetgame->mission, mi->msn_file);
#endif
      // Get script
      strcpy(buffer, DLLListGetItem(script_list, DLLListGetSelectedIndex(script_list)));
      if (strcmp(buffer, "None")) {
        // remove file extension
        for (int d = strlen(buffer) - 1; d >= 0; d--) {
          if (buffer[d] == '.') {
            buffer[d] = '\0';
            break;
          }
        }

        strcpy(DLLNetgame->scriptname, buffer);
      }
      DLLMultiDoConfigLoad();
      if (!Use_netgame_flags) {
        DLLNetgame->flags = 0;
      }
      DLLEditSetText(mission_name_edit, DLLNetgame->name);
#if (!(defined(OEM) || defined(DEMO)))
      p = DLLGetMissionName(DLLNetgame->mission);
      mi = FindMsnItem(p);

      if (mi)
        DLLListSelectItem(list_1, mi->ti);
#endif
      for (index = 0; index < dllcount; index++) {
        if (stricmp(dll_text[index], DLLNetgame->scriptname) == 0) {
          DLLListSelectItem(script_list, dll_txt_items[index]);
          break;
        }
      }
    }
  }

  DLLNewUIWindowClose(main_wnd);
  DLLNewUIWindowDestroy(main_wnd);
  for (a = 0; a < MAX_DLLS; a++)
    if (dll_txt_items[a])
      DLLRemoveUITextItem(dll_txt_items[a]);
  RemoveAllMsnItems();
  // cleanup
#ifdef DEMO
  DLLRemoveUITextItem(msn_multi_ti);
  DLLRemoveUITextItem(msn_single_ti);
  DLLRemoveUITextItem(msn_multi_2);
#endif
  DLLRemoveUITextItem(game_name_text);
  DLLRemoveUITextItem(mission_name_text);
  DLLRemoveUITextItem(script_name_text);
  DLLRemoveUITextItem(start_game_on_text);
  DLLRemoveUITextItem(multiplayer_opts_on_text);
  DLLRemoveUITextItem(exit_on_text);
  DLLRemoveUITextItem(start_game_off_text);
  DLLRemoveUITextItem(multiplayer_opts_off_text);
  DLLRemoveUITextItem(exit_off_text);
  DLLRemoveUITextItem(blank_text);
  DLLRemoveUITextItem(save_settings_txt_on);
  DLLRemoveUITextItem(save_settings_txt_off);
  DLLRemoveUITextItem(load_settings_txt_on);
  DLLRemoveUITextItem(load_settings_txt_off);

  DLLRemoveUITextItem(start_text);

  DLLDeleteUIItem(start_title);
  DLLDeleteUIItem(save_hs);
  DLLDeleteUIItem(load_hs);
  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(game_name);
  DLLDeleteUIItem(list_1);
  DLLDeleteUIItem(mission_text);
  DLLDeleteUIItem(mission_name_edit);
  DLLDeleteUIItem(script_name);
  DLLDeleteUIItem(script_list);
  DLLDeleteUIItem(option_hs);
  DLLDeleteUIItem(start_hs);
  DLLDeleteUIItem(cancel_hs);

  return ret;
}

void MultiplayerOptionsMenu() {
#ifndef MULTI_USE_ALL_OPTIONS
  DLLMultiGameOptionsMenu(0);
#else
  DLLMultiGameOptionsMenu(1);
#endif
}
