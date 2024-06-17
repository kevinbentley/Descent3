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

#ifndef GAMEDLL_HEADER_H
#define GAMEDLL_HEADER_H

#include "spew.h"
#include "gamefont.h"
#include "hud.h"
#include "module.h" //for DMFCDLLOUT, etc.
#include "renderer.h"
#include "findintersection.h"

//////////////////////////////////////////
#include "pstypes.h"
#include "vecmat_external.h"
#include "object_external_struct.h"
#include "object_external.h"
#include "player_external.h"
#include "room_external.h"
#include "multi_external.h"
#include "multi_world_state.h"
#include "viseffect_external.h"
#include "osiris_share.h"
#include "3d.h"
#include "terrain.h"
#include "gametexture.h"
#include "args.h"
#include "bitmap.h"
#include "Inventory.h"

#ifdef __cplusplus
#define CEXTERN(a)                                                                                                     \
  extern "C" {                                                                                                         \
  a                                                                                                                    \
  }
#else
#define CEXTERN(a) extern a
#endif

// From ssl_lib.h
#define MAX_GAME_VOLUME 1.0f

#define DMFCDLLOUT(x) extern "C" x

#define UIF_CENTER 0x01
#define UIF_FIT 0x02
#define UILB_NOSCROLL 0x04   // turns off automatic scroll buttons on UIListBox
#define UILB_AUTOSELECT 0x08 // turns on automatic change of SelectedIndex if scrolled out of view
#define UIRB_NOBUTTON 0x10   // disables the drawing of the button on the left of the text of a radio button
#define UIF_BORDER 0x100     // for certain gadgets specifies that the border be drawn.
#define UIED_PASSWORD 0x200  // special password masking for edit box text (*)
#define UIF_PROCESS_LEFTKEY (1 << 8)
#define UIF_PROCESS_RIGHTKEY (1 << 9)
#define UIF_PROCESS_UPKEY (1 << 10)
#define UIF_PROCESS_DOWNKEY (1 << 11)
#define UIF_PROCESS_ALL (0xff00)

struct tPreJoinData {
  bool is_banned;
  int team;
};

struct game_collide_info {
  vector point, normal;
  float hitspeed, hit_dot;
  int hitseg, hitwall;
};

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
  game_collide_info collide_info;
  int newseg, oldseg;
};

#define MAX_GAMENAME_LEN 32
#define MAX_REQUIREMENT_LEN 384
#define DOF_MAXTEAMS 0x0001 // max_teams member is valid
#define DOF_MINTEAMS 0x0002
// this struct is used to return game specific information to Descent 3
struct tDLLOptions {
  // general flags, also specifies what members of the structure are valid
  int flags;

  // 0 or 1 for non-team games...maximum value is 4.  If not specified, than it is assumed 0
  int max_teams;
  // must be less then or equal to max_teams.  If not specified, then it is assumed 0 for
  // non-team games, 2 for team games. (max_teams will always tell you if it's a team game)
  int min_teams;

  // gives the full name of the game (must be set)
  char game_name[MAX_GAMENAME_LEN];

  // this is an array of semicolor seperated 'string identifiers' that serve as requirements
  // the mission needs to support in order for it to be playable with the game.
  // this parameter must be set (even it is just a '\0' for the first character..aka no requirements)
  char requirements[MAX_REQUIREMENT_LEN];

};

struct game_api {
  int *objs;
  int *rooms;
  int *terrain;
  int *players;
  int *netgame;
  int *netplayers;
  int *ships;
  int *weapons;
  int *Current_mission;
  int *GameTextures;
  int *GameVClips;
  int *fp[450]; // function pointers
  int *vp[50];  // variable pointers
  tOSIRISModuleInit *osiris_functions;
};

// Descent3 function prototypes.  NOTE: These must match the real D3 prototypes.

typedef void (*GetGameAPI_fp)(game_api *);
DMFCDLLOUT(GetGameAPI_fp DLLGetGameAPI;)

typedef bool (*AddHUDMessage_fp)(const char *format, ...);
DMFCDLLOUT(AddHUDMessage_fp DLLAddHUDMessage;)

typedef void (*Debug_ConsolePrintf_fp)(int n, const char *format, ...);
DMFCDLLOUT(Debug_ConsolePrintf_fp DLLDebug_ConsolePrintf;)

// typedef void( *MultiSendClientExecuteDLL_fp ) (int eventnum,int me_objnum,int it_objnum,int to,dllinfo *info=NULL);
typedef void (*MultiSendClientExecuteDLL_fp)(int eventnum, int me_objnum, int it_objnum, int to, dllinfo *info);
DMFCDLLOUT(MultiSendClientExecuteDLL_fp DLLMultiSendClientExecuteDLL;)

// typedef void( *MultiSendObject_fp ) (object *obj,uint8_t announce,uint8_t demo_record=true);
typedef void (*MultiSendObject_fp)(object *obj, uint8_t announce, uint8_t demo_record);
DMFCDLLOUT(MultiSendObject_fp DLLMultiSendObject;)

// typedef void( *MultiPaintGoalRooms_fp ) (int *texcolors=NULL);
typedef void (*MultiPaintGoalRooms_fp)(int *texcolors);
DMFCDLLOUT(MultiPaintGoalRooms_fp DLLMultiPaintGoalRooms;)

typedef void (*MultiSendSpecialPacket_fp)(int slot, uint8_t *outdata, int size);
DMFCDLLOUT(MultiSendSpecialPacket_fp DLLMultiSendSpecialPacket;)

typedef void (*ComputeRoomCenter_fp)(vector *vp, room *rp);
DMFCDLLOUT(ComputeRoomCenter_fp DLLComputeRoomCenter;)

typedef int (*GetGoalRoomForTeam_fp)(int teamnum);
DMFCDLLOUT(GetGoalRoomForTeam_fp DLLGetGoalRoomForTeam;)

// ObjCreate without writing data to demo
// typedef int( *ObjCreate_fp ) (uint8_t type,uint16_t id,int roomnum,vector *pos,const matrix *orient,int parent_handle =
// OBJECT_HANDLE_NONE);
typedef int (*ObjCreate_fp)(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient, int parent_handle);
DMFCDLLOUT(ObjCreate_fp DLLObjCreate;)

typedef int (*FindObjectIDName_fp)(const char *name);
DMFCDLLOUT(FindObjectIDName_fp DLLFindObjectIDName;)

typedef void (*ObjSetPosNoMark_fp)(object *objp, vector *newpos, int roomnum, matrix *orient,
                                   bool f_update_attached_children);
DMFCDLLOUT(ObjSetPosNoMark_fp DLLObjSetPosNoMark;)

// ObjSetPos, that automatically sets the OF_MOVED_THIS_FRAME
typedef void (*ObjSetPos_fp)(object *obj, vector *pos, int roomnum, matrix *orient, bool f_update_attached_children);
DMFCDLLOUT(ObjSetPos_fp DLLObjSetPos;)

typedef void (*SetMaxTeams_fp)(int num);
DMFCDLLOUT(SetMaxTeams_fp DLLSetMaxTeams;)

typedef int (*IncTeamScore_fp)(int team, int amount);
DMFCDLLOUT(IncTeamScore_fp DLLIncTeamScore;)

typedef bool (*InvCheckItem_fp)(int pnum, int type, int id);
DMFCDLLOUT(InvCheckItem_fp DLLInvCheckItem;)

// typedef bool( *InvAddTypeID_fp ) (int pnum, int type,int id,int aux_type=-1,int aux_id=-1,int flags=0,const char *description=NULL);
typedef bool (*InvAddTypeID_fp)(int pnum, int type, int id, int aux_type, int aux_id, int flags, const char *description);
DMFCDLLOUT(InvAddTypeID_fp DLLInvAddTypeID;)

typedef bool (*InvRemove_fp)(int pnum, int type, int id);
DMFCDLLOUT(InvRemove_fp DLLInvRemove;)

typedef void (*PlayerSetLighting_fp)(int slot, float dist, float r, float g, float b);
DMFCDLLOUT(PlayerSetLighting_fp DLLPlayerSetLighting;)

typedef int (*FindShipName_fp)(const char *name);
DMFCDLLOUT(FindShipName_fp DLLFindShipName;)

// Sets a wacky rotating ball around the player ship
typedef void (*PlayerSetRotatingBall_fp)(int slot, int num, float speed, float *r, float *g, float *b);
DMFCDLLOUT(PlayerSetRotatingBall_fp DLLPlayerSetRotatingBall;)

// Changes the ship a particular player is flying
typedef void (*PlayerChangeShip_fp)(int slot, int ship_index);
DMFCDLLOUT(PlayerChangeShip_fp DLLPlayerChangeShip;)

typedef int (*InvGetTypeIDCount_fp)(int playernum, int type, int id);
DMFCDLLOUT(InvGetTypeIDCount_fp DLLInvGetTypeIDCount;)

// typedef int (*D3W_Play3dSound_fp ) (int sound_index, object *cur_obj, float volume = MAX_GAME_VOLUME, int flags = 0);
typedef int (*D3W_Play3dSound_fp)(int sound_index, object *cur_obj, float volume, int flags);
DMFCDLLOUT(D3W_Play3dSound_fp DLLPlay3dSound;)

typedef int (*FindSoundName_fp)(const char *str);
DMFCDLLOUT(FindSoundName_fp DLLFindSoundName;)

typedef int (*SpewCreate_fp)(spewinfo *spew);
DMFCDLLOUT(SpewCreate_fp DLLSpewCreate;)

// typedef void (*SpewClearEvent_fp) (int handle,bool force=false);
typedef void (*SpewClearEvent_fp)(int handle, bool force);
DMFCDLLOUT(SpewClearEvent_fp DLLSpewClearEvent;)

// Allocs and loads a bitmap
// Returns the handle of the loaded bitmap
// Returns -1 if something is wrong
// If mipped is non-zero, allocs extra space for mips and computes them
// typedef int (*bm_AllocLoadFileBitmap_fp) (const char *filename,int mipped,int format=BITMAP_FORMAT_1555);
typedef int (*bm_AllocLoadFileBitmap_fp)(const char *filename, int mipped, int format);
DMFCDLLOUT(bm_AllocLoadFileBitmap_fp DLLbm_AllocLoadFileBitmap;)

// Given a handle, frees the bitmap memory and flags this bitmap as unused
typedef void (*bm_FreeBitmap_fp)(int handle);
DMFCDLLOUT(bm_FreeBitmap_fp DLLbm_FreeBitmap;)

// Draws a scaled 2d bitmap to our buffer
// typedef void (*rend_DrawScaledBitmap_fp) (int x1,int y1,int x2,int y2,int bm,float u0,float v0,float u1,float
// v1,float zval,int color=-1,float *alphas=NULL);
typedef void (*rend_DrawScaledBitmap_fp)(int x1, int y1, int x2, int y2, int bm, float u0, float v0, float u1, float v1,
                                         float zval, int color, float *alphas);
DMFCDLLOUT(rend_DrawScaledBitmap_fp DLLrend_DrawScaledBitmap;)

//	puts a formatted string in the text buffer
typedef void (*grtext_Printf_fp)(int x, int y, const char *fmt, ...);
DMFCDLLOUT(grtext_Printf_fp DLLgrtext_Printf;)

//	renders all text in buffer and clears buffer.  USUALLY CALL THIS TO RENDER TEXT
typedef void (*grtext_Flush_fp)(void);
DMFCDLLOUT(grtext_Flush_fp DLLgrtext_Flush;)

// sets the color for text
typedef void (*grtext_SetColor_fp)(ddgr_color col);
DMFCDLLOUT(grtext_SetColor_fp DLLgrtext_SetColor;)

//	sets fancy color for text
typedef void (*grtext_SetFancyColor_fp)(ddgr_color col1, ddgr_color col2, ddgr_color col3, ddgr_color col4);
DMFCDLLOUT(grtext_SetFancyColor_fp DLLgrtext_SetFancyColor;)

//	sets the alpha value for text
typedef void (*grtext_SetAlpha_fp)(uint8_t alpha);
DMFCDLLOUT(grtext_SetAlpha_fp DLLgrtext_SetAlpha;)

//	gets font alpha
typedef uint8_t (*grtext_GetAlpha_fp)(void);
DMFCDLLOUT(grtext_GetAlpha_fp DLLgrtext_GetAlpha;)

// sets the font for text
typedef void (*grtext_SetFont_fp)(int font_handle);
DMFCDLLOUT(grtext_SetFont_fp DLLgrtext_SetFont;)

// gets the current font
typedef int (*grtext_GetFont_fp)(void);
DMFCDLLOUT(grtext_GetFont_fp DLLgrtext_GetFont;)

//	returns width of text in current font.
typedef int (*grtext_GetTextLineWidth_fp)(const char *str);
DMFCDLLOUT(grtext_GetTextLineWidth_fp DLLgrtext_GetTextLineWidth;)

//	returns a font's height
typedef int (*grfont_GetHeight_fp)(int font);
DMFCDLLOUT(grfont_GetHeight_fp DLLgrfont_GetHeight;)

//	puts a centered string in the text buffer.
typedef void (*grtext_CenteredPrintf_fp)(int xoff, int y, const char *fmt, ...);
DMFCDLLOUT(grtext_CenteredPrintf_fp DLLgrtext_CenteredPrintf;)

// Adds a colored message to the hud
typedef bool (*AddColoredHUDMessage_fp)(ddgr_color color, const char *format, ...);
DMFCDLLOUT(AddColoredHUDMessage_fp DLLAddColoredHUDMessage;)

// returns the height of a bitmap
typedef int (*bm_h_fp)(int handle, int miplevel);
DMFCDLLOUT(bm_h_fp DLLbm_h;)

// returns the width of a bitmap
typedef int (*bm_w_fp)(int handle, int miplevel);
DMFCDLLOUT(bm_w_fp DLLbm_w;)

// Draws a simple bitmap at the specified x,y location
typedef void (*rend_DrawSimpleBitmap_fp)(int bm_handle, int x, int y);
DMFCDLLOUT(rend_DrawSimpleBitmap_fp DLLrend_DrawSimpleBitmap;)

// sends a special packet to the server
typedef void (*MultiClientSendSpecialPacket_fp)(uint8_t *outdate, int size);
DMFCDLLOUT(MultiClientSendSpecialPacket_fp DLLMultiClientSendSpecialPacket;)

// adds a blinking hud message
typedef bool (*AddBlinkingHUDMessage_fp)(char *format, ...);
DMFCDLLOUT(AddBlinkingHUDMessage_fp DLLAddBlinkingHUDMessage;)

// resets a player's inventory
// typedef void (*InvReset_fp)(int playernum,bool reset_all=true);
typedef void (*InvReset_fp)(int playernum, bool reset_all);
DMFCDLLOUT(InvReset_fp DLLInvReset;)

//	places an item on the hud
typedef void (*AddHUDItem_fp)(tHUDItem *item);
DMFCDLLOUT(AddHUDItem_fp DLLAddHUDItem;)

//	renders a bitmap onto the hud
// typedef void (*RenderHUDQuad_fp) (int x, int y, int w, int h, float u0, float v0, float u1, float v1, int bm, uint8_t
// alpha, int sat_count=0);
typedef void (*RenderHUDQuad_fp)(int x, int y, int w, int h, float u0, float v0, float u1, float v1, int bm,
                                 uint8_t alpha, int sat_count);
DMFCDLLOUT(RenderHUDQuad_fp DLLRenderHUDQuad;)

//	renders text, scaled, alphaed, saturated,
typedef void (*RenderHUDText_fp)(ddgr_color col, uint8_t alpha, int sat_count, int x, int y, const char *fmt, ...);
DMFCDLLOUT(RenderHUDText_fp DLLRenderHUDText;)

// Ends a multiplayer level and goes on to the next, Server only
typedef void (*MultiEndLevel_fp)(void);
DMFCDLLOUT(MultiEndLevel_fp DLLMultiEndLevel;)

// returns a pointer to the data in a bitmap
typedef uint16_t *(*bm_data_fp)(int handle, int miplevel);
DMFCDLLOUT(bm_data_fp DLLbm_data;)

// Allocs a bitmap of w x h size
// If add_mem is nonzero, adds that to the amount alloced
// (added due to the way the tmapper works)
// Returns bitmap handle if successful, -1 if otherwise
typedef int (*bm_AllocBitmap_fp)(int w, int h, int add_mem);
DMFCDLLOUT(bm_AllocBitmap_fp DLLbm_AllocBitmap;)

// Fills a rectangle on the display
typedef void (*rend_FillRect_fp)(ddgr_color color, int x1, int y1, int x2, int y2);
DMFCDLLOUT(rend_FillRect_fp DLLrend_FillRect;)

//	takes a large static bitmap and breaks it into smaller managable bitmaps
typedef bool (*bm_CreateChunkedBitmap_fp)(int bm_handle, chunked_bitmap *chunk);
DMFCDLLOUT(bm_CreateChunkedBitmap_fp DLLbm_CreateChunkedBitmap;)

//	destroys a chunked bitmap.
typedef void (*bm_DestroyChunkedBitmap_fp)(chunked_bitmap *chunk);
DMFCDLLOUT(bm_DestroyChunkedBitmap_fp DLLbm_DestroyChunkedBitmap;)

//	given a chunked bitmap, renders it.
typedef void (*rend_DrawChunkedBitmap_fp)(chunked_bitmap *chunk, int x, int y, uint8_t alpha);
DMFCDLLOUT(rend_DrawChunkedBitmap_fp DLLrend_DrawChunkedBitmap;)

//	given a chunked bitmap, renders it.scaled
typedef void (*rend_DrawScaledChunkedBitmap_fp)(chunked_bitmap *chunk, int x, int y, int neww, int newh, uint8_t alpha);
DMFCDLLOUT(rend_DrawScaledChunkedBitmap_fp DLLrend_DrawScaledChunkedBitmap;)

// Opens a file for reading or writing
// If a path is specified, will try to open the file only in that path.
// If no path is specified, will look through search directories and library files.
// Parameters:	filename - the name if the file, with or without a path
//					mode - the standard C mode string
// Returns:		the CFile handle, or NULL if file not opened
typedef void (*OpenCFILE_fp)(CFILE **handle, const char *filename, const char *mode);
DMFCDLLOUT(OpenCFILE_fp DLLOpenCFILE;)

// Closes an open CFILE.
// Parameters:  cfile - the file pointer returned by cfopen()
typedef void (*cfclose_fp)(CFILE *cfp);
DMFCDLLOUT(cfclose_fp DLLcfclose;)

// Returns true if at EOF
typedef int (*cfeof_fp)(CFILE *cfp);
DMFCDLLOUT(cfeof_fp DLLcfeof;)

// Tells if the file exists
// Returns non-zero if file exists.  Also tells if the file is on disk
//	or in a hog -  See return values in cfile.h
typedef int (*cfexist_fp)(const char *filename);
DMFCDLLOUT(cfexist_fp DLLcfexist;)

// Reads the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO READ STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes read.
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int (*cf_ReadBytes_fp)(uint8_t *buf, int count, CFILE *cfp);
DMFCDLLOUT(cf_ReadBytes_fp DLLcf_ReadBytes;)

// The following functions read numeric vales from a CFILE.  All values are
// stored in the file in Intel (little-endian) format.  These functions
// will convert to big-endian if required.
// These funtions will throw an exception of if the value cannot be read,
// so do not call these if you don't require the data to be present.

// Read and return an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int (*cf_ReadInt_fp)(CFILE *cfp);
DMFCDLLOUT(cf_ReadInt_fp DLLcf_ReadInt;)

// Read and return a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int16_t (*cf_ReadShort_fp)(CFILE *cfp);
DMFCDLLOUT(cf_ReadShort_fp DLLcf_ReadShort;)

// Read and return a byte (8 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int8_t (*cf_ReadByte_fp)(CFILE *cfp);
DMFCDLLOUT(cf_ReadByte_fp DLLcf_ReadByte;)

// Read and return a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef float (*cf_ReadFloat_fp)(CFILE *cfp);
DMFCDLLOUT(cf_ReadFloat_fp DLLcf_ReadFloat;)

// Read and return a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef double (*cf_ReadDouble_fp)(CFILE *cfp);
DMFCDLLOUT(cf_ReadDouble_fp DLLcf_ReadDouble;)

// Reads a string from a CFILE.  If the file is type binary, this
// function reads until a NULL or EOF is found.  If the file is text,
// the function reads until a newline or EOF is found.  The string is always
// written to the destination buffer null-terminated, without the newline.
// Parameters:  buf - where the string is written
//					n - the maximum string length, including the terminating 0
//					cfp - the CFILE pointer
// Returns the number of bytes in the string, before the terminator
// Does not generate an exception on EOF
typedef int (*cf_ReadString_fp)(char *buf, size_t n, CFILE *cfp);
DMFCDLLOUT(cf_ReadString_fp DLLcf_ReadString;)

// Writes the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO WRITE STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes written.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef int (*cf_WriteBytes_fp)(const uint8_t *buf, int count, CFILE *cfp);
DMFCDLLOUT(cf_WriteBytes_fp DLLcf_WriteBytes;)

// Writes a null-terminated string to a file.  If the file is type binary,
// the string is terminated in the file with a null.  If the file is type
// text, the string is terminated with a newline.
// Parameters:	buf - pointer to the string
//					cfp = the CFILE pointer
// Returns the number of bytes written
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef int (*cf_WriteString_fp)(CFILE *cfp, const char *buf);
DMFCDLLOUT(cf_WriteString_fp DLLcf_WriteString;)

// Write an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*cf_WriteInt_fp)(CFILE *cfp, int i);
DMFCDLLOUT(cf_WriteInt_fp DLLcf_WriteInt;)

// Write a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*cf_WriteShort_fp)(CFILE *cfp, int16_t s);
DMFCDLLOUT(cf_WriteShort_fp DLLcf_WriteShort;)

// Write a byte (8 bits).  If the byte is a newline & the file is a text file, writes a CR/LF pair.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*cf_WriteByte_fp)(CFILE *cfp, int8_t b);
DMFCDLLOUT(cf_WriteByte_fp DLLcf_WriteByte;)

// Write a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*cf_WriteFloat_fp)(CFILE *cfp, float f);
DMFCDLLOUT(cf_WriteFloat_fp DLLcf_WriteFloat;)

// Write a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*cf_WriteDouble_fp)(CFILE *cfp, double d);
DMFCDLLOUT(cf_WriteDouble_fp DLLcf_WriteDouble;)

// Copies a file.  Returns TRUE if copied ok.  Returns FALSE if error opening either file.
// Throws an exception of type (cfile_error *) if the OS returns an error on read or write
typedef bool (*cf_CopyFile_fp)(char *dest, const char *src);
DMFCDLLOUT(cf_CopyFile_fp DLLcf_CopyFile;)

// Checks to see if two files are different.
// Returns TRUE if the files are different, or FALSE if they are the same.
typedef bool (*cf_Diff_fp)(const char *a, const char *b);
DMFCDLLOUT(cf_Diff_fp DLLcf_Diff;)

// Disconnects a player
typedef void (*MultiDisconnectPlayer_fp)(int slot);
DMFCDLLOUT(MultiDisconnectPlayer_fp DLLMultiDisconnectPlayer;)

// Fills in the string with the string address from the internet address
typedef void (*nw_GetNumbersFromHostAddress_fp)(network_address *address, char *str);
DMFCDLLOUT(nw_GetNumbersFromHostAddress_fp DLLnw_GetNumbersFromHostAddress;)

// Returns the address of this machine
typedef int (*nw_GetThisIP_fp)(void);
DMFCDLLOUT(nw_GetThisIP_fp DLLnw_GetThisIP;)

// Given a filename, pointer to a char * array and a pointer to an int,
// it will load the string table and fill in the information
// returns true on success
typedef bool (*CreateStringTable_fp)(const char *filename, char ***table, int *size);
DMFCDLLOUT(CreateStringTable_fp DLLCreateStringTable;)

// Given a string table and it's count of strings, it will free up it's memory
typedef void (*DestroyStringTable_fp)(char **table, int size);
DMFCDLLOUT(DestroyStringTable_fp DLLDestroyStringTable;)

//	renders text, scaled, alphaed, saturated,
typedef void (*RenderHUDTextFlags_fp)(int flags, ddgr_color col, uint8_t alpha, int sat_count, int x, int y, const char *fmt, ...);
DMFCDLLOUT(RenderHUDTextFlags_fp DLLRenderHUDTextFlags;)

// Sets the FOV range at which the hud names will come on
typedef void (*PlayerSetHUDNameFOV_fp)(int fov);
DMFCDLLOUT(PlayerSetHUDNameFOV_fp DLLPlayerSetHUDNameFOV;)

// Fills in the original parent of the object, it will be the object passed in if it doesn't have a parent
typedef void (*GetUltimateParentForObject_fp)(object **parent, object *child);
DMFCDLLOUT(GetUltimateParentForObject_fp DLLGetUltimateParentForObject;)

// Sets an object flag dead (does not write demo data)
// typedef void (*SetObjectDeadFlagRaw_fp)(object *obj,bool tell_clients_to_remove=false,bool
// tell_clients_to_play_sound=false);
typedef void (*SetObjectDeadFlagRaw_fp)(object *obj, bool tell_clients_to_remove, bool tell_clients_to_play_sound);
DMFCDLLOUT(SetObjectDeadFlagRaw_fp DLLSetObjectDeadFlagRaw;)

// Sets an object flag dead (automatically writes demo data when needed)
// typedef void (*SetObjectDeadFlag_fp)(object *obj,bool tell_clients_to_remove=false,bool
// tell_clients_to_play_sound=false);
typedef void (*SetObjectDeadFlag_fp)(object *obj, bool tell_clients_to_remove, bool tell_clients_to_play_sound);
DMFCDLLOUT(SetObjectDeadFlag_fp DLLSetObjectDeadFlag;)

// Call this function if there was an error while running the Multiplayer DLL, it will bail out
// typedef void (*DLLFatalError_fp)(const char *reason=NULL);
typedef void (*DLLFatalError_fp)(const char *reason);
DMFCDLLOUT(DLLFatalError_fp FatalError;)

// Assert for the DLLs
typedef void (*assertdll_fp)(int x, const char *expression, const char *file, int line);
DMFCDLLOUT(assertdll_fp DLLassert;)

// Return index of generic that has matching table entry
typedef int (*MultiMatchWeapon_fp)(uint32_t unique_id);
DMFCDLLOUT(MultiMatchWeapon_fp DLLMultiMatchWeapon;)

// Returns the unique id of a given object type/id
typedef uint32_t (*MultiGetMatchChecksum_fp)(int type, int id);
DMFCDLLOUT(MultiGetMatchChecksum_fp DLLMultiGetMatchChecksum;)

// Searches thru all weapons for a specific name, returns -1 if not found
// or index of weapon with name
typedef int (*FindWeaponName_fp)(const char *name);
DMFCDLLOUT(FindWeaponName_fp DLLFindWeaponName;)

// Opens a HOG file.  Future calls to cfopen(), etc. will look in this HOG.
// Parameters:  libname - the path & filename of the HOG file
// Returns: 0 if error, else library handle that can be used to close the library
typedef int (*cf_OpenLibrary_fp)(const char *libname);
DMFCDLLOUT(cf_OpenLibrary_fp DLLcf_OpenLibrary;)

// Closes a library file.
// Parameters:  handle: the handle returned by cf_OpenLibrary()
typedef void (*cf_CloseLibrary_fp)(int handle);
DMFCDLLOUT(cf_CloseLibrary_fp DLLcf_CloseLibrary;)

// We're asking to enter observer mode
typedef void (*MultiSendRequestToObserve_fp)(int mode, int on, int objnum);
DMFCDLLOUT(MultiSendRequestToObserve_fp DLLMultiSendRequestToObserve;)

// Searches thru all textures for a specific name, returns -1 if not found
// or index of texture with name
typedef int (*FindTextureName_fp)(const char *name);
DMFCDLLOUT(FindTextureName_fp DLLFindTextureName;)

//	Applies damage to a player object, returns false if damage wasn't applied due to things like
//	invunerability
// typedef bool (*ApplyDamageToPlayer_fp)(object *playerobj, object *killer, int damage_type, float damage_amount,int
// server_says=0,int weapon_id=255,bool playsound=true);
typedef bool (*ApplyDamageToPlayer_fp)(object *playerobj, object *killer, int damage_type, float damage_amount,
                                       int server_says, int weapon_id, bool playsound);
DMFCDLLOUT(ApplyDamageToPlayer_fp DLLApplyDamageToPlayer;)

// Return index of generic that has matching table entry
typedef int (*MultiMatchGeneric_fp)(uint32_t unique_id);
DMFCDLLOUT(MultiMatchGeneric_fp DLLMultiMatchGeneric;)

typedef void (*SetUITextItemText_fp)(void *uit, char *newtext, uint32_t color);
DMFCDLLOUT(SetUITextItemText_fp DLLSetUITextItemText;)

typedef void *(*NewUIWindowCreate_fp)(int x, int y, int w, int h, int flags);
DMFCDLLOUT(NewUIWindowCreate_fp DLLNewUIWindowCreate;)

typedef void (*NewUIWindowDestroy_fp)(void *deswin);
DMFCDLLOUT(NewUIWindowDestroy_fp DLLNewUIWindowDestroy;)

typedef void (*NewUIWindowOpen_fp)(void *deswin);
DMFCDLLOUT(NewUIWindowOpen_fp DLLNewUIWindowOpen;)

typedef void (*NewUIWindowClose_fp)(void *deswin);
DMFCDLLOUT(NewUIWindowClose_fp DLLNewUIWindowClose;)

typedef void *(*TextCreate_fp)(void *parentwin, void *textitem, int x, int y, int flags);
DMFCDLLOUT(TextCreate_fp DLLTextCreate;)

typedef void (*TextSetTitle_fp)(void *text, void *textitem);
DMFCDLLOUT(TextSetTitle_fp DLLTextSetTitle;)

typedef void *(*EditCreate_fp)(void *parentwin, int id, int x, int y, int w, int h, int flags);
DMFCDLLOUT(EditCreate_fp DLLEditCreate;)

typedef void *(*ButtonCreate_fp)(void *parentwin, int id, void *titleitem, int x, int y, int w, int h, int flags);
DMFCDLLOUT(ButtonCreate_fp DLLButtonCreate;)

typedef void *(*ListCreate_fp)(void *parentwin, int id, int x, int y, int w, int h, int flags);
DMFCDLLOUT(ListCreate_fp DLLListCreate;)

typedef void (*ListRemoveAll_fp)(void *item);
DMFCDLLOUT(ListRemoveAll_fp DLLListRemoveAll;)

typedef void (*ListAddItem_fp)(void *item, void *uitext);
DMFCDLLOUT(ListAddItem_fp DLLListAddItem;)

typedef void (*ListRemoveItem_fp)(void *item, void *txtitem);
DMFCDLLOUT(ListRemoveItem_fp DLLListRemoveItem;)

typedef void (*ListSelectItem_fp)(void *item, void *txtitem);
DMFCDLLOUT(ListSelectItem_fp DLLListSelectItem;)

typedef char *(*ListGetItem_fp)(void *item, int index);
DMFCDLLOUT(ListGetItem_fp DLLListGetItem;)

typedef int (*ListGetSelectedIndex_fp)(void *item);
DMFCDLLOUT(ListGetSelectedIndex_fp DLLListGetSelectedIndex;)

typedef void (*ListSetSelectedIndex_fp)(void *item, int index);
DMFCDLLOUT(ListSetSelectedIndex_fp DLLListSetSelectedIndex;)

typedef void (*EditSetText_fp)(void *item, const char *buff);
DMFCDLLOUT(EditSetText_fp DLLEditSetText;)

typedef void (*EditGetText_fp)(void *item, char *buff, int len);
DMFCDLLOUT(EditGetText_fp DLLEditGetText;)

typedef int (*GetUIItemWidth_fp)(void *item);
DMFCDLLOUT(GetUIItemWidth_fp DLLGetUIItemWidth;)

typedef int (*GetUIItemHeight_fp)(void *item);
DMFCDLLOUT(GetUIItemHeight_fp DLLGetUIItemHeight;)

// UI CheckBox functions
typedef void *(*CheckBoxCreate_fp)(void *parent, int id, void *title, int x, int y, int w, int h, int flags);
DMFCDLLOUT(CheckBoxCreate_fp DLLCheckBoxCreate;)

typedef void (*CheckBoxSetCheck_fp)(void *cb, bool state);
DMFCDLLOUT(CheckBoxSetCheck_fp DLLCheckBoxSetCheck;)

typedef bool (*CheckBoxIsChecked_fp)(void *cb);
DMFCDLLOUT(CheckBoxIsChecked_fp DLLCheckBoxIsChecked;)

//	does a UI loop:  returns a result value for the current window in focus.
typedef int (*DoUI_fp)(void);
DMFCDLLOUT(DoUI_fp DLLDoUI;)

//	puts up a message box with a title and message.
// typedef int (*DoMessageBox_fp)(const char *title, const char *msg, int type, ddgr_color title_color = GR_WHITE,
// ddgr_color text_color = GR_WHITE);
typedef int (*DoMessageBox_fp)(const char *title, const char *msg, int type, ddgr_color title_color,
                               ddgr_color text_color);
DMFCDLLOUT(DoMessageBox_fp DLLDoMessageBox;)

typedef void (*DescentDefer_fp)(void);
DMFCDLLOUT(DescentDefer_fp DLLDescentDefer;)

// typedef void *(*NewUIGameWindowCreate_fp)(int x, int y, int w, int h, int flags=UIF_PROCESS_ALL);
typedef void *(*NewUIGameWindowCreate_fp)(int x, int y, int w, int h, int flags);
DMFCDLLOUT(NewUIGameWindowCreate_fp DLLNewUIGameWindowCreate;)

typedef void (*NewUIGameWindowDestroy_fp)(void *item);
DMFCDLLOUT(NewUIGameWindowDestroy_fp DLLNewUIGameWindowDestroy;)

typedef void (*NewUIGameWindowOpen_fp)(void *item);
DMFCDLLOUT(NewUIGameWindowOpen_fp DLLNewUIGameWindowOpen;)

typedef void (*NewUIGameWindowClose_fp)(void *item);
DMFCDLLOUT(NewUIGameWindowClose_fp DLLNewUIGameWindowClose;)

typedef void *(*HotSpotCreate_fp)(void *parentwin, int id, int key, void *txtitemoff, void *txtitemon, int x, int y,
                                  int w, int h, int flags);
DMFCDLLOUT(HotSpotCreate_fp DLLHotSpotCreate;)

typedef int (*PollUI_fp)(void);
DMFCDLLOUT(PollUI_fp DLLPollUI;)

typedef void (*RemoveUITextItem_fp)(void *item);
DMFCDLLOUT(RemoveUITextItem_fp DLLRemoveUITextItem;)

// typedef void *(*CreateNewUITextItem_fp)(const char *newtext,uint32_t color,int font=-1);
typedef void *(*CreateNewUITextItem_fp)(const char *newtext, uint32_t color, int font);
DMFCDLLOUT(CreateNewUITextItem_fp DLLCreateNewUITextItem;)

typedef void (*RemoveUIBmpItem_fp)(void *item);
DMFCDLLOUT(RemoveUIBmpItem_fp DLLRemoveUIBmpItem;)

typedef void *(*CreateNewUIBmpItem_fp)(int handle, uint8_t alpha);
DMFCDLLOUT(CreateNewUIBmpItem_fp DLLCreateNewUIBmpItem;)

typedef void *(*UIConsoleGadgetCreate_fp)(void *parentid, int id, int x, int y, int font, int cols, int rows,
                                          int flags);
DMFCDLLOUT(UIConsoleGadgetCreate_fp DLLUIConsoleGadgetCreate;)

typedef void (*UIConsoleGadgetputs_fp)(void *item, const char *str);
DMFCDLLOUT(UIConsoleGadgetputs_fp DLLUIConsoleGadgetputs;)

typedef void (*NewUIWindowSetFocusOnEditGadget_fp)(void *item, void *parent);
DMFCDLLOUT(NewUIWindowSetFocusOnEditGadget_fp DLLNewUIWindowSetFocusOnEditGadget;)

typedef void *(*OldListCreate_fp)(void *parentitem, int id, int x, int y, int w, int h, int flags);
DMFCDLLOUT(OldListCreate_fp DLLOldListCreate;)

typedef void (*OldListRemoveAll_fp)(void *item);
DMFCDLLOUT(OldListRemoveAll_fp DLLOldListRemoveAll;)

typedef void (*OldListAddItem_fp)(void *item, void *uitext);
DMFCDLLOUT(OldListAddItem_fp DLLOldListAddItem;)

typedef void (*OldListRemoveItem_fp)(void *item, void *txtitem);
DMFCDLLOUT(OldListRemoveItem_fp DLLOldListRemoveItem;)

typedef void (*OldListSelectItem_fp)(void *item, void *txtitem);
DMFCDLLOUT(OldListSelectItem_fp DLLOldListSelectItem;)

typedef void *(*OldEditCreate_fp)(void *parentitem, int id, int x, int y, int w, int h, int flags);
DMFCDLLOUT(OldEditCreate_fp DLLOldEditCreate;)

typedef void (*OldEditGetText_fp)(void *item, char *buff, int len);
DMFCDLLOUT(OldEditGetText_fp DLLOldEditGetText;)

typedef void (*OldEditSetText_fp)(void *item, const char *newtext);
DMFCDLLOUT(OldEditSetText_fp DLLOldEditSetText;)

typedef char *(*OldListGetItem_fp)(void *item, int index);
DMFCDLLOUT(OldListGetItem_fp DLLOldListGetItem;)

typedef int (*OldListGetSelectedIndex_fp)(void *item);
DMFCDLLOUT(OldListGetSelectedIndex_fp DLLOldListGetSelectedIndex;)

typedef void (*ToggleUICallback_fp)(int state);
DMFCDLLOUT(ToggleUICallback_fp DLLToggleUICallback;)

typedef void (*SetOldEditBufferLen_fp)(void *item, int len);
DMFCDLLOUT(SetOldEditBufferLen_fp DLLSetOldEditBufferLen;)

typedef void (*NewUIWindowLoadBackgroundImage_fp)(void *item, const char *image_name);
DMFCDLLOUT(NewUIWindowLoadBackgroundImage_fp DLLNewUIWindowLoadBackgroundImage;)

typedef void (*DeleteUIItem_fp)(void *delitem);
DMFCDLLOUT(DeleteUIItem_fp DLLDeleteUIItem;)

typedef void (*HotSpotSetStates_fp)(void *hs, void *texton, void *textoff);
DMFCDLLOUT(HotSpotSetStates_fp DLLHotSpotSetStates;)

//	sets the callback for background rendering of desktop for UI
typedef void (*SetUICallback_fp)(void (*fn)());
DMFCDLLOUT(SetUICallback_fp DLLSetUICallback;)

typedef void (*RetrieveUICallback_fp)(void **fn);
DMFCDLLOUT(RetrieveUICallback_fp DLLGetUICallback;)

typedef void (*SuspendControls_fp)(void);
DMFCDLLOUT(SuspendControls_fp DLLSuspendControls;)

typedef void (*ResumeControls_fp)(void);
DMFCDLLOUT(ResumeControls_fp DLLResumeControls;)

typedef void (*ui_ShowCursor_fp)(void);
DMFCDLLOUT(ui_ShowCursor_fp DLLShowCursor;)

typedef void (*ui_HideCursor_fp)(void);
DMFCDLLOUT(ui_HideCursor_fp DLLHideCursor;)

typedef void (*GameFrame_fp)(void);
DMFCDLLOUT(GameFrame_fp DLLGameFrame;)

// typedef void *(*SliderCreate_fp)(void *parent, int id, int x, int y, int flags=0);
typedef void *(*SliderCreate_fp)(void *parent, int id, int x, int y, int flags);
DMFCDLLOUT(SliderCreate_fp DLLSliderCreate;)

typedef void (*SliderSetRange_fp)(void *slider, int range);
DMFCDLLOUT(SliderSetRange_fp DLLSliderSetRange;)

typedef int (*SliderGetRange_fp)(void *slider);
DMFCDLLOUT(SliderGetRange_fp DLLSliderGetRange;)

typedef void (*SliderSetPos_fp)(void *slider, int pos);
DMFCDLLOUT(SliderSetPos_fp DLLSliderSetPos;)

typedef int (*SliderGetPos_fp)(void *slider);
DMFCDLLOUT(SliderGetPos_fp DLLSliderGetPos;)

typedef void (*SliderSetSelectChangeCallback_fp)(void *slider, void (*fn)(int));
DMFCDLLOUT(SliderSetSelectChangeCallback_fp DLLSliderSetSelectChangeCallback;)

typedef void (*SliderSetSelectChangeCallbackWData_fp)(void *slider, void (*fn)(int, void *), void *ptr);
DMFCDLLOUT(SliderSetSelectChangeCallbackWData_fp DLLSliderSetSelectChangeCallbackWData;)

// Prints a message to the console if the dedicated server is active
typedef void (*DPrintf_fp)(const char *fmt, ...);
DMFCDLLOUT(DPrintf_fp DPrintf;)

// Split a pathname into its component parts
//	The path in splitpath is in the *LOCAL* file system's syntax
typedef void (*ddio_SplitPath_fp)(const char *srcPath, char *path, char *filename, char *ext);
DMFCDLLOUT(ddio_SplitPath_fp DLLddio_SplitPath;)

// Constructs a path in the local file system's syntax
// 	builtPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//	subdir:	the first subdirectory
//  takes a variable number of additional subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
typedef void (*ddio_MakePath_fp)(char *newPath, const char *absolutePathHeader, const char *subDir, ...);
DMFCDLLOUT(ddio_MakePath_fp DLLddio_MakePath;)

//	Plays a 2d sound
// typedef int (*Play2dSound_fp)(int sound_index, float volume =MAX_GAME_VOLUME/2);
typedef int (*Play2dSound_fp)(int sound_index, float volume);
DMFCDLLOUT(Play2dSound_fp DLLPlay2dSound;)

typedef void (*TouchSound_fp)(int sound_index);
DMFCDLLOUT(TouchSound_fp DLLTouchSound;)

// Database functions to read/write
typedef bool (*dDatabaseRead_fp1)(const char *label, char *entry, int *entrylen);
DMFCDLLOUT(dDatabaseRead_fp1 DatabaseRead1;)

typedef bool (*dDatabaseRead_fp2)(const char *label, void *entry, int wordsize);
DMFCDLLOUT(dDatabaseRead_fp2 DatabaseRead2;)

typedef bool (*dDatabaseRead_fp3)(const char *label, bool *entry);
DMFCDLLOUT(dDatabaseRead_fp3 DatabaseRead3;)

typedef bool (*dDatabaseWrite_fp1)(const char *label, const char *entry, int entrylen);
DMFCDLLOUT(dDatabaseWrite_fp1 DatabaseWrite1;)

typedef bool (*dDatabaseWrite_fp2)(const char *label, int entry);
DMFCDLLOUT(dDatabaseWrite_fp2 DatabaseWrite2;)

// Attaches 2 objects via attach points on each.  The f_used_aligned allows for an aligned connection.
// NOTE: The child always moves to the parent
// typedef bool (*AttachObject_fp)(object *parent, char parent_ap, object *child, char child_ap, bool f_use_aligned =
// false);
typedef bool (*AttachObject_fp)(object *parent, char parent_ap, object *child, char child_ap, bool f_use_aligned);
DMFCDLLOUT(AttachObject_fp DLLAttachObject;)

// Retruns a pointer to an object given its handle.  Returns NULL if object no longer exists.
typedef bool (*ObjGet_fp)(int handle, object **obj);
DMFCDLLOUT(ObjGet_fp DLLObjGet;)

//		Given a pilot id, it will return the pilot name of
//	the pilot name.  Returns false if it's an invalid pilot id.
typedef bool (*PPic_GetPilot_fp)(uint16_t pilot_id, char *pilot_name, int buffersize);
DMFCDLLOUT(PPic_GetPilot_fp DLLPPic_GetPilot;)

//		Given a pilot id, it will return a handle to the bitmap for the pilot.
//  MAKE SURE YOU FREE THE BITMAP WITH DLLbm_FreeBitmap().  Returns -1 if it was an illegal pilot id.
//	Returns BAD_BITMAP_HANDLE if it couldn't open the bitmap.
typedef int (*PPic_GetBitmapHandle_fp)(uint16_t pilot_id);
DMFCDLLOUT(PPic_GetBitmapHandle_fp DLLPPic_GetBitmapHandle;)

// Draws a line
typedef void (*rend_DrawLine_fp)(int x1, int y1, int x2, int y2);
DMFCDLLOUT(rend_DrawLine_fp DLLrend_DrawLine;)

// Sets the color for fill based primitives;
typedef void (*rend_SetFlatColor_fp)(ddgr_color color);
DMFCDLLOUT(rend_SetFlatColor_fp DLLrend_SetFlatColor;)

// Sets whether or not we want the logos to be displayed on ships
typedef void (*MultiSetLogoState_fp)(bool state);
DMFCDLLOUT(MultiSetLogoState_fp DLLMultiSetLogoState;)

// Spews the inventory of the passed in player object
// typedef void (*PlayerSpewInventory_fp)(object *obj,bool spew_energy_and_shield=true,bool spew_nonspewables=false);
typedef void (*PlayerSpewInventory_fp)(object *obj, bool spew_energy_and_shield, bool spew_nonspewables);
DMFCDLLOUT(PlayerSpewInventory_fp DLLPlayerSpewInventory;)

// Returns a random player starting position
typedef int (*PlayerGetRandomStartPosition_fp)(int slot);
DMFCDLLOUT(PlayerGetRandomStartPosition_fp DLLPlayerGetRandomStartPosition;)

// Resets all the properties a player ship to the default values
// Pass in what kind of reset the inventory should do INVRESET_
typedef void (*InitPlayerNewShip_fp)(int slot, int inven_reset);
DMFCDLLOUT(InitPlayerNewShip_fp DLLInitPlayerNewShip;)

// Returns internet address format from string address format...ie "204.243.217.14"
// turns into 1414829242
typedef uint32_t (*nw_GetHostAddressFromNumbers_fp)(char *str);
DMFCDLLOUT(nw_GetHostAddressFromNumbers_fp DLLnw_GetHostAddressFromNumbers;)

//	Removes all addon table files from D3 (really shouldn't be called, automatically done)
typedef void (*TableFilesClear_fp)(void);
DMFCDLLOUT(TableFilesClear_fp TableFilesClear;)

//	Adds a table file into the manage system for add-on data
typedef bool (*TableFileAdd_fp)(char *filename);
DMFCDLLOUT(TableFileAdd_fp TableFileAdd;)

// Debugger interaction
typedef void (*DebugBreak_callback_stop_fp)(void);
DMFCDLLOUT(DebugBreak_callback_stop_fp DLLDebugBreak_callback_stop;)
typedef void (*DebugBreak_callback_resume_fp)(void);
DMFCDLLOUT(DebugBreak_callback_resume_fp DLLDebugBreak_callback_resume;)
typedef void (*Int3MessageBox_fp)(const char *file, const char *line);
DMFCDLLOUT(Int3MessageBox_fp DLLInt3MessageBox;)

//	Fills in the non-NULL parameters with the position and size information about
//	a UI Item
typedef void (*GetUIItemPosition_fp)(void *item, int *x, int *y, int *w, int *h);
DMFCDLLOUT(GetUIItemPosition_fp DLLGetUIItemPosition;)

// Attaches a child object to a parent object by a percent of the radius of the child.
// NOTE: The child always moves to the parent and not the reverse
typedef bool (*AttachObjectRadius_fp)(object *parent, char parent_ap, object *child, float percent_rad);
DMFCDLLOUT(AttachObjectRadius_fp DLLAttachObjectRadius;)

// Unattaches all children from a parent object
typedef bool (*UnattachChildren_fp)(object *parent);
DMFCDLLOUT(UnattachChildren_fp DLLUnattachChildren;)

// Unattaches a child from an attach point
typedef bool (*UnattachChild_fp)(object *parent, char parent_ap);
DMFCDLLOUT(UnattachChild_fp DLLUnattachChild;)

// Unattaches an object from its parent
typedef bool (*UnattachFromParent_fp)(object *child);
DMFCDLLOUT(UnattachFromParent_fp DLLUnattachFromParent;)

typedef float (*vm_GetMagnitude_fp)(vector *vec);
DMFCDLLOUT(vm_GetMagnitude_fp DLLvm_GetMagnitude;)

// Rotates a vector thru a matrix
typedef void (*vm_MatrixMulVector_fp)(vector *, vector *, matrix *);
DMFCDLLOUT(vm_MatrixMulVector_fp DLLvm_MatrixMulVector;)

// Applies an instantaneous force on an object, resulting in an instantaneous
// change in velocity.
// typedef void (*phys_apply_force_fp)(object *obj,vector *force_vec,int16_t weapon_index=-1);
typedef void (*phys_apply_force_fp)(object *obj, vector *force_vec, int16_t weapon_index);
DMFCDLLOUT(phys_apply_force_fp DLLphys_apply_force;)

typedef void (*phys_apply_rot_fp)(object *obj, vector *force_vec);
DMFCDLLOUT(phys_apply_rot_fp DLLphys_apply_rot;)

// Transposes a matrix in place
typedef void (*vm_TransposeMatrix_fp)(matrix *);
DMFCDLLOUT(vm_TransposeMatrix_fp DLLvm_TransposeMatrix;)

// Returns a perpendicular vector to the two given vectors
typedef void (*vm_CrossProduct_fp)(vector *, vector *, vector *);
DMFCDLLOUT(vm_CrossProduct_fp DLLvm_CrossProduct;)

// Normalizes a vector
// Returns the magnitude before normalization
typedef float (*vm_NormalizeVector_fp)(vector *);
DMFCDLLOUT(vm_NormalizeVector_fp DLLvm_NormalizeVector;)

typedef void (*ConvertEulerToAxisAmount_fp)(vector *e, vector *n, float *w);
DMFCDLLOUT(ConvertEulerToAxisAmount_fp DLLConvertEulerToAxisAmount;)

typedef void (*ConvertAxisAmountToEuler_fp)(vector *n, float *w, vector *e);
DMFCDLLOUT(ConvertAxisAmountToEuler_fp DLLConvertAxisAmountToEuler;)

// Given a vector, returns an approximation of the magnitude
typedef float (*vm_GetMagnitudeFast_fp)(vector *);
DMFCDLLOUT(vm_GetMagnitudeFast_fp DLLvm_GetMagnitudeFast;)

// Given a matrix, makes it an identity matrix
typedef void (*vm_MakeIdentity_fp)(matrix *);
DMFCDLLOUT(vm_MakeIdentity_fp DLLvm_MakeIdentity;)

// Set a vector to {0,0,0}
typedef void (*vm_MakeVectorZero_fp)(vector *v);
DMFCDLLOUT(vm_MakeVectorZero_fp DLLvm_MakeVectorZero;)

// Set an angvec to {0,0,0}
typedef void (*vm_MakeAngleZero_fp)(angvec *a);
DMFCDLLOUT(vm_MakeAngleZero_fp DLLvm_MakeAngleZero;)

// Multiply a vector times the transpose of a matrix
typedef void (*vm_VectorMulTMatrix_fp)(vector *result, vector *v, matrix *m);
DMFCDLLOUT(vm_VectorMulTMatrix_fp DLLvm_VectorMulTMatrix;)

// Multiplies 2 3x3 matrixes, returning the result in first argument
typedef void (*vm_MatrixMul_fp)(matrix *, matrix *, matrix *);
DMFCDLLOUT(vm_MatrixMul_fp DLLvm_MatrixMul;)

// Multiply a matrix times the transpose of a matrix
typedef void (*vm_MatrixMulTMatrix_fp)(matrix *dest, matrix *src0, matrix *src1);
DMFCDLLOUT(vm_MatrixMulTMatrix_fp DLLvm_MatrixMulTMatrix;)

// Returns the dot product of the two given vectors
typedef float (*vm_DotProduct_fp)(vector *, vector *);
DMFCDLLOUT(vm_DotProduct_fp DLLvm_DotProduct;)

// Returns the difference between two vectors
typedef void (*vm_SubVectors_fp)(vector *, const vector *, const vector *);
DMFCDLLOUT(vm_SubVectors_fp DLLvm_SubVectors;)

// Returns adds two vectors, returns result in first arg
typedef void (*vm_AddVectors_fp)(vector *, vector *, vector *);
DMFCDLLOUT(vm_AddVectors_fp DLLvm_AddVectors;)

// Given a vector, divides second arg by vector components
typedef void (*vm_AverageVector_fp)(vector *, int);
DMFCDLLOUT(vm_AverageVector_fp DLLvm_AverageVector;)

// Scales second arg vector by 3rd arg, placing result in first arg
typedef void (*vm_ScaleVector_fp)(vector *, vector *, float);
DMFCDLLOUT(vm_ScaleVector_fp DLLvm_ScaleVector;)

// Scales all components of vector v by value s adds the result to p and stores result in vector d
typedef void (*vm_ScaleAddVector_fp)(vector *d, vector *p, vector *v, float s);
DMFCDLLOUT(vm_ScaleAddVector_fp DLLvm_ScaleAddVector;)

// Divides second vector components by 3rd arg, placing result in first arg.  Useful for parametric lines
typedef void (*vm_DivVector_fp)(vector *, vector *, float);
DMFCDLLOUT(vm_DivVector_fp DLLvm_DivVector;)

// Same as NormalizeVector, but uses approximation
typedef float (*vm_NormalizeVectorFast_fp)(vector *);
DMFCDLLOUT(vm_NormalizeVectorFast_fp DLLvm_NormalizeVectorFast;)

// Clears a matrix to zero
typedef void (*vm_ClearMatrix_fp)(matrix *);
DMFCDLLOUT(vm_ClearMatrix_fp DLLvm_ClearMatrix;)

// Given 3 angles (p,h,b), makes a rotation matrix out of them
typedef void (*vm_AnglesToMatrix_fp)(matrix *, angle p, angle h, angle b);
DMFCDLLOUT(vm_AnglesToMatrix_fp DLLvm_AnglesToMatrix;)

// Ensure that a matrix is orthogonal
typedef void (*vm_Orthogonalize_fp)(matrix *m);
DMFCDLLOUT(vm_Orthogonalize_fp DLLvm_Orthogonalize;)

// Compute a matrix from one or two vectors.  At least one and at most two vectors must/can be specified.
// Parameters:	m - filled in with the orienation matrix
//					fvec,uvec,rvec - pointers to vectors that determine the matrix.
//						One or two of these must be specified, with the other(s) set to NULL.
typedef void (*vm_VectorToMatrix_fp)(matrix *m, vector *fvec, vector *uvec, vector *rvec);
DMFCDLLOUT(vm_VectorToMatrix_fp DLLvm_VectorToMatrix;)

// Computes a matrix from a vector and and angle of rotation around that vector
// Parameters:	m - filled in with the computed matrix
//					v - the forward vector of the new matrix
//					a - the angle of rotation around the forward vector
typedef void (*vm_VectorAngleToMatrix_fp)(matrix *m, vector *v, angle a);
DMFCDLLOUT(vm_VectorAngleToMatrix_fp DLLvm_VectorAngleToMatrix;)

// Given an angle, places sin in 2nd arg, cos in 3rd.  Either can be null
typedef void (*vm_SinCos_fp)(angle, float *, float *);
DMFCDLLOUT(vm_SinCos_fp DLLvm_SinCos;)

// Given x1,y1,x2,y2, returns the slope
typedef float (*vm_GetSlope_fp)(float, float, float, float);
DMFCDLLOUT(vm_GetSlope_fp DLLvm_GetSlope;)

// Calculates the perpendicular vector given three points
// Parms:	n - the computed perp vector (filled in)
//			v0,v1,v2 - three clockwise vertices
typedef void (*vm_GetPerp_fp)(vector *n, vector *a, vector *b, vector *c);
DMFCDLLOUT(vm_GetPerp_fp DLLvm_GetPerp;)

// Calculates the (normalized) surface normal give three points
// Parms:	n - the computed surface normal (filled in)
//			v0,v1,v2 - three clockwise vertices
// Returns the magnitude of the normal before it was normalized.
// The bigger this value, the better the normal.
typedef float (*vm_GetNormal_fp)(vector *n, vector *v0, vector *v1, vector *v2);
DMFCDLLOUT(vm_GetNormal_fp DLLvm_GetNormal;)

// Gets the distances (magnitude) between two vectors. Slow.
typedef float (*vm_VectorDistance_fp)(const vector *a, const vector *b);
DMFCDLLOUT(vm_VectorDistance_fp DLLvm_VectorDistance;)

// Gets the approx distances (magnitude) between two vectors. Faster.
typedef float (*vm_VectorDistanceQuick_fp)(vector *a, vector *b);
DMFCDLLOUT(vm_VectorDistanceQuick_fp DLLvm_VectorDistanceQuick;)

// Computes a normalized direction vector between two points
// Parameters:	dest - filled in with the normalized direction vector
//					start,end - the start and end points used to calculate the vector
// Returns:		the distance between the two input points
typedef float (*vm_GetNormalizedDir_fp)(vector *dest, vector *end, vector *start);
DMFCDLLOUT(vm_GetNormalizedDir_fp DLLvm_GetNormalizedDir;)

// Returns a normalized direction vector between two points
// Uses sloppier magnitude, less precise
typedef float (*vm_GetNormalizedDirFast_fp)(vector *dest, vector *end, vector *start);
DMFCDLLOUT(vm_GetNormalizedDirFast_fp DLLvm_GetNormalizedDirFast;)

// extract angles from a matrix
typedef angvec *(*vm_ExtractAnglesFromMatrix_fp)(angvec *a, matrix *m);
DMFCDLLOUT(vm_ExtractAnglesFromMatrix_fp DLLvm_ExtractAnglesFromMatrix;)

//	returns the angle between two vectors and a forward vector
typedef angle (*vm_DeltaAngVec_fp)(vector *v0, vector *v1, vector *fvec);
DMFCDLLOUT(vm_DeltaAngVec_fp DLLvm_DeltaAngVec;)

//	returns the angle between two normalized vectors and a forward vector
typedef angle (*vm_DeltaAngVecNorm_fp)(vector *v0, vector *v1, vector *fvec);
DMFCDLLOUT(vm_DeltaAngVecNorm_fp DLLvm_DeltaAngVecNorm;)

// Computes the distance from a point to a plane.
// Parms:	checkp - the point to check
// Parms:	norm - the (normalized) surface normal of the plane
//				planep - a point on the plane
// Returns:	The signed distance from the plane; negative dist is on the back of the plane
typedef float (*vm_DistToPlane_fp)(vector *checkp, vector *norm, vector *planep);
DMFCDLLOUT(vm_DistToPlane_fp DLLvm_DistToPlane;)

// returns the value of a determinant
typedef float (*vm_CalcDetValue_fp)(matrix *det);
DMFCDLLOUT(vm_CalcDetValue_fp DLLvm_CalcDetValue;)

typedef void (*vm_MakeInverseMatrix_fp)(matrix *dest);
DMFCDLLOUT(vm_MakeInverseMatrix_fp DLLvm_MakeInverseMatrix;)

typedef void (*vm_SinCosToMatrix_fp)(matrix *m, float sinp, float cosp, float sinb, float cosb, float sinh, float cosh);
DMFCDLLOUT(vm_SinCosToMatrix_fp DLLvm_SinCosToMatrix;)

// Gets the real center of a polygon
typedef float (*vm_GetCentroid_fp)(vector *centroid, vector *src, int nv);
DMFCDLLOUT(vm_GetCentroid_fp DLLvm_GetCentroid;)

//	retrieves a random vector in values -RAND_MAX/2 to RAND_MAX/2
typedef void (*vm_MakeRandomVector_fp)(vector *vec);
DMFCDLLOUT(vm_MakeRandomVector_fp DLLvm_MakeRandomVector;)

// Given a set of points, computes the minimum bounding sphere of those points
typedef float (*vm_ComputeBoundingSphere_fp)(vector *center, vector *vecs, int num_verts);
DMFCDLLOUT(vm_ComputeBoundingSphere_fp DLLvm_ComputeBoundingSphere;)

// Gets the real center of a polygon, but uses fast magnitude calculation
// Returns the size of the passed in stuff
typedef float (*vm_GetCentroidFast_fp)(vector *centroid, vector *src, int nv);
DMFCDLLOUT(vm_GetCentroidFast_fp DLLvm_GetCentroidFast;)

// returns scaled line width
typedef int (*RenderHUDGetTextLineWidth_fp)(const char *string);
DMFCDLLOUT(RenderHUDGetTextLineWidth_fp DLLRenderHUDGetTextLineWidth;)

// returns scaled text height
typedef int (*RenderHUDGetTextHeight_fp)(const char *string);
DMFCDLLOUT(RenderHUDGetTextHeight_fp DLLRenderHUDGetTextHeight;)

// typedef void (*StartFrame_fp)(int x, int y, int x2, int y2, bool clear=true);
typedef void (*StartFrame_fp)(int x, int y, int x2, int y2, bool clear);
DMFCDLLOUT(StartFrame_fp DLLStartFrame;)

typedef void (*EndFrame_fp)(void);
DMFCDLLOUT(EndFrame_fp DLLEndFrame;)

typedef void (*ResetFacings_fp)(void);
DMFCDLLOUT(ResetFacings_fp DLLResetFacings;)

// Render the world into a game window
// Parameters:	viewer - if not null, this object disabled from rendering.  Not used otherwise.
//					viewer_eye - where we're rendering from
//					viewer_roomnum - the roomnum viewer_eye is in
//					viewer_orient - the oriention for this view
//					zoom - the zoom for this view
//					rear_view - if true, we're looking out the rear of this object
typedef void (*GameRenderWorld_fp)(object *viewer, vector *viewer_eye, int viewer_roomnum, matrix *viewer_orient,
                                   float zoom, bool rear_view);
DMFCDLLOUT(GameRenderWorld_fp DLLGameRenderWorld;)

// retrives the settings of the last call to StartFrame
// returns false if it's not currently in between a StartFrame/EndFrame block
typedef bool (*GetFrameParameters_fp)(int *x1, int *y1, int *x2, int *y2);
DMFCDLLOUT(GetFrameParameters_fp DLLGetFrameParameters;)

// Sets the state of zbuffering to on or off
typedef void (*rend_SetZBufferState_fp)(int8_t state);
DMFCDLLOUT(rend_SetZBufferState_fp DLLrend_SetZBufferState;)

typedef void (*rend_SetLighting_fp)(light_state);
DMFCDLLOUT(rend_SetLighting_fp DLLrend_SetLighting;)

typedef void (*rend_SetColorModel_fp)(color_model);
DMFCDLLOUT(rend_SetColorModel_fp DLLrend_SetColorModel;)

typedef void (*rend_SetTextureType_fp)(texture_type);
DMFCDLLOUT(rend_SetTextureType_fp DLLrend_SetTextureType;)

// Given a handle to a bitmap and nv point vertices, draws a polygon
// typedef void (*rend_DrawPolygon_fp)(int handle,g3Point **p,int nv,int map_type=MAP_TYPE_BITMAP);
typedef void (*rend_DrawPolygon_fp)(int handle, g3Point **p, int nv, int map_type);
DMFCDLLOUT(rend_DrawPolygon_fp DLLrend_DrawPolygon;)

// Tells the software renderer whether or not to use mipping
typedef void (*rend_SetMipState_fp)(int8_t);
DMFCDLLOUT(rend_SetMipState_fp DLLrend_SetMipState;)

// Sets the fog state to TRUE or FALSE
typedef void (*rend_SetFogState_fp)(int8_t on);
DMFCDLLOUT(rend_SetFogState_fp DLLrend_SetFogState;)

// Sets the state of bilinear filtering for our textures
typedef void (*rend_SetFiltering_fp)(int8_t state);
DMFCDLLOUT(rend_SetFiltering_fp DLLrend_SetFiltering;)

// Sets a bitmap as an overlay to rendered on top of the next texture map
typedef void (*rend_SetOverlayMap_fp)(int handle);
DMFCDLLOUT(rend_SetOverlayMap_fp DLLrend_SetOverlayMap;)

// Sets the type of overlay operation
typedef void (*rend_SetOverlayType_fp)(uint8_t type);
DMFCDLLOUT(rend_SetOverlayType_fp DLLrend_SetOverlayType;)

// Clears the display to a specified color
typedef void (*rend_ClearScreen_fp)(ddgr_color color);
DMFCDLLOUT(rend_ClearScreen_fp DLLrend_ClearScreen;)

// Sets a pixel on the display
typedef void (*rend_SetPixel_fp)(ddgr_color color, int x, int y);
DMFCDLLOUT(rend_SetPixel_fp DLLrend_SetPixel;)

// Gets a pixel on the display
typedef ddgr_color (*rend_GetPixel_fp)(int x, int y);
DMFCDLLOUT(rend_GetPixel_fp DLLrend_GetPixel;)

//	Draws spheres
typedef void (*rend_FillCircle_fp)(ddgr_color col, int x, int y, int rad);
DMFCDLLOUT(rend_FillCircle_fp DLLrend_FillCircle;)

//	draws circles
typedef void (*rend_DrawCircle_fp)(int x, int y, int rad);
DMFCDLLOUT(rend_DrawCircle_fp DLLrend_DrawCircle;)

// sets the alpha type
typedef void (*rend_SetAlphaType_fp)(int8_t);
DMFCDLLOUT(rend_SetAlphaType_fp DLLrend_SetAlphaType;)

// Sets the constant alpha value
typedef void (*rend_SetAlphaValue_fp)(uint8_t val);
DMFCDLLOUT(rend_SetAlphaValue_fp DLLrend_SetAlphaValue;)

// Sets the wrap parameter
typedef void (*rend_SetWrapType_fp)(wrap_type val);
DMFCDLLOUT(rend_SetWrapType_fp DLLrend_SetWrapType;)

// Adds a bias to each coordinates z value.  This is useful for making 2d bitmaps
// get drawn without being clipped by the zbuffer
typedef void (*rend_SetZBias_fp)(float z_bias);
DMFCDLLOUT(rend_SetZBias_fp DLLrend_SetZBias;)

// Enables/disables writes the depth buffer
typedef void (*rend_SetZBufferWriteMask_fp)(int state);
DMFCDLLOUT(rend_SetZBufferWriteMask_fp DLLrend_SetZBufferWriteMask;)

// Gets a pointer to a linear frame buffer
typedef void (*rend_GetLFBLock_fp)(renderer_lfb *lfb);
DMFCDLLOUT(rend_GetLFBLock_fp DLLrend_GetLFBLock;)

// Releases an lfb lock
typedef void (*rend_ReleaseLFBLock_fp)(renderer_lfb *lfb);
DMFCDLLOUT(rend_ReleaseLFBLock_fp DLLrend_ReleaseLFBLock;)

// Given a source x,y and width,height, draws any sized bitmap into the renderer lfb
typedef void (*rend_DrawLFBBitmap_fp)(int sx, int sy, int w, int h, int dx, int dy, uint16_t *data, int rowsize);
DMFCDLLOUT(rend_DrawLFBBitmap_fp DLLrend_DrawLFBBitmap;)

// Draws a line using the states of the renderer
typedef void (*rend_DrawSpecialLine_fp)(g3Point *p0, g3Point *p1);
DMFCDLLOUT(rend_DrawSpecialLine_fp DLLrend_DrawSpecialLine;)

// Find out if a vector intersects with anything.
// Fills in hit_data, an fvi_info structure
// Parms:
//  p0 & startseg 	describe the start of the vector
//  p1 					the end of the vector
//  rad 					the radius of the cylinder
//  thisobjnum 		used to prevent an object with colliding with itself
//  ingore_obj_list	NULL, or ptr to a list of objnums to ignore, terminated with -1
//  check_obj_flag	determines whether collisions with objects are checked
// Returns the hit_data->hit_type
// typedef int (*fvi_FindIntersection_fp)(fvi_query *fq,fvi_info *hit_data,  bool no_subdivision = false);
typedef int (*fvi_FindIntersection_fp)(fvi_query *fq, fvi_info *hit_data, bool no_subdivision);
DMFCDLLOUT(fvi_FindIntersection_fp DLLfvi_FindIntersection;)

// Generates a list of faces(with corresponding room numbers) within a given distance to a position.
// Return value is the number of faces in the list
typedef int (*fvi_QuickDistFaceList_fp)(int init_room_index, vector *pos, float rad, fvi_face_room_list *quick_fr_list,
                                        int max_elements);
DMFCDLLOUT(fvi_QuickDistFaceList_fp DLLfvi_QuickDistFaceList;)

// Returns the number of cells that are approximately within the specified radius
typedef int (*fvi_QuickDistCellList_fp)(int init_cell_index, vector *pos, float rad, int *quick_cell_list,
                                        int max_elements);
DMFCDLLOUT(fvi_QuickDistCellList_fp DLLfvi_QuickDistCellList;)

// Returns the number of objects that are approximately within the specified radius
// typedef int (*fvi_QuickDistObjectList_fp)(vector *pos, int init_roomnum, float rad, int16_t *object_index_list, int
// max_elements, bool f_lightmap_only, bool f_only_players_and_ais = false, bool f_include_non_collide_objects = false,
// bool f_stop_at_closed_doors = false);
typedef int (*fvi_QuickDistObjectList_fp)(vector *pos, int init_roomnum, float rad, int16_t *object_index_list,
                                          int max_elements, bool f_lightmap_only, bool f_only_players_and_ais,
                                          bool f_include_non_collide_objects, bool f_stop_at_closed_doors);
DMFCDLLOUT(fvi_QuickDistObjectList_fp DLLfvi_QuickDistObjectList;)

// returns true if the given point is in the given room
// typedef bool (*fvi_QuickRoomCheck_fp)(vector *pos, room *cur_room, bool try_again = false);
typedef bool (*fvi_QuickRoomCheck_fp)(vector *pos, room *cur_room, bool try_again);
DMFCDLLOUT(fvi_QuickRoomCheck_fp DLLfvi_QuickRoomCheck;)

// returns true if audio taunts are enabled
typedef bool (*taunt_AreEnabled_fp)(void);
DMFCDLLOUT(taunt_AreEnabled_fp DLLtaunt_AreEnabled;)

//	Enables/Disables audio_taunts for the player
typedef void (*taunt_Enable_fp)(bool enable);
DMFCDLLOUT(taunt_Enable_fp DLLtaunt_Enable;)

// Returns a ranking index based on the player rating
// If rankbuf is non-null, fills in the string corresponding to that rank
// Returns -1 if not a pxo game (ie no rankings in this game)
// typedef int (*GetPlayerRankIndex_fp) (int pnum,char *rankbuf=NULL);
typedef int (*GetPlayerRankIndex_fp)(int pnum, char *rankbuf);
DMFCDLLOUT(GetPlayerRankIndex_fp GetPlayerRankIndex;)

// Returns the next free viseffect
typedef int (*VisEffectAllocate_fp)(void);
DMFCDLLOUT(VisEffectAllocate_fp DLLVisEffectAllocate;)

// Frees up a viseffect for use
typedef int (*VisEffectFree_fp)(int visnum);
DMFCDLLOUT(VisEffectFree_fp DLLVisEffectFree;)

typedef int (*VisEffectInitType_fp)(vis_effect *vis);
DMFCDLLOUT(VisEffectInitType_fp DLLVisEffectInitType;)

// initialize a new viseffect.  adds to the list for the given room
// returns the object number
typedef int (*VisEffectCreate_fp)(uint8_t type, uint8_t id, int roomnum, vector *pos);
DMFCDLLOUT(VisEffectCreate_fp DLLVisEffectCreate;)

// link the viseffect  into the list for its room
// Does nothing for effects over terrain
typedef void (*VisEffectLink_fp)(int visnum, int roomnum);
DMFCDLLOUT(VisEffectLink_fp DLLVisEffectLink;)

// Unlinks a viseffect from a room
// Does nothing for terrain
typedef void (*VisEffectUnlink_fp)(int visnum);
DMFCDLLOUT(VisEffectUnlink_fp DLLVisEffectUnlink;)

// when an effect has moved into a new room, this function unlinks it
// from its old room and links it into the new room
typedef void (*VisEffectRelink_fp)(int visnum, int newroomnum);
DMFCDLLOUT(VisEffectRelink_fp DLLVisEffectRelink;)

// remove viseffect from the world
typedef void (*VisEffectDelete_fp)(int visnum);
DMFCDLLOUT(VisEffectDelete_fp DLLVisEffectDelete;)

// Creates a some sparks that go in random directions
// typedef void (*CreateRandomSparks_fp) (int num_sparks,vector *pos,int roomnum,int which_index=-1,float
// force_scalar=1);
typedef void (*CreateRandomSparks_fp)(int num_sparks, vector *pos, int roomnum, int which_index, float force_scalar);
DMFCDLLOUT(CreateRandomSparks_fp DLLCreateRandomSparks;)

// Creates a some line sparks that go in random directions
// typedef void (*CreateRandomLineSparks_fp) (int num_sparks,vector *pos,int roomnum,uint16_t color=0,float
// force_scalar=1);
typedef void (*CreateRandomLineSparks_fp)(int num_sparks, vector *pos, int roomnum, uint16_t color, float force_scalar);
DMFCDLLOUT(CreateRandomLineSparks_fp DLLCreateRandomLineSparks;)

// Creates vis effects but has the caller set their parameters
// initialize a new viseffect.  adds to the list for the given room
// returns the vis number
// typedef int (*VisEffectCreateControlled_fp)(uint8_t type,object *parent,uint8_t id,int roomnum,vector *pos,float
// lifetime,vector *velocity,int phys_flags=0,float size=0,float mass=0.0f,float drag=0.0f,bool isreal=0);
typedef int (*VisEffectCreateControlled_fp)(uint8_t type, object *parent, uint8_t id, int roomnum, vector *pos,
                                            float lifetime, vector *velocity, int phys_flags, float size, float mass,
                                            float drag, bool isreal);
DMFCDLLOUT(VisEffectCreateControlled_fp DLLVisEffectCreateControlled;)

// Creates a some particles that go in random directions
typedef void (*CreateRandomParticles_fp)(int num_sparks, vector *pos, int roomnum, int bm_handle, float size,
                                         float life);
DMFCDLLOUT(CreateRandomParticles_fp DLLCreateRandomParticles;)

// Attaches viseffects that move with an object
typedef void (*AttachRandomNapalmEffectsToObject_fp)(object *obj);
DMFCDLLOUT(AttachRandomNapalmEffectsToObject_fp DLLAttachRandomNapalmEffectsToObject;)

// allocates and initializes the scripts for an object.
//	robots, powerups, doors, etc.
typedef void (*InitObjectScripts_fp)(object *objp, bool do_evt_created);
DMFCDLLOUT(InitObjectScripts_fp DLLInitObjectScripts;)

// Frame setup functions:

// start the frame, specifying view position, matrix, & zoom
typedef void (*g3_StartFrame_fp)(vector *view_pos, matrix *view_matrix, float zoom);
DMFCDLLOUT(g3_StartFrame_fp DLLg3_StartFrame;)

// end the frame
typedef void (*g3_EndFrame_fp)(void);
DMFCDLLOUT(g3_EndFrame_fp DLLg3_EndFrame;)

// get the current view position
typedef void (*g3_GetViewPosition_fp)(vector *vp);
DMFCDLLOUT(g3_GetViewPosition_fp DLLg3_GetViewPosition;)

//	returns the current view matrix
typedef void (*g3_GetViewMatrix_fp)(matrix *mat);
DMFCDLLOUT(g3_GetViewMatrix_fp DLLg3_GetViewMatrix;)

//	returns the current unscaled view matrix
typedef void (*g3_GetUnscaledMatrix_fp)(matrix *mat);
DMFCDLLOUT(g3_GetUnscaledMatrix_fp DLLg3_GetUnscaledMatrix;)

// Instancing

// instance at specified point with specified orientation
typedef void (*g3_StartInstanceMatrix_fp)(vector *pos, matrix *orient);
DMFCDLLOUT(g3_StartInstanceMatrix_fp DLLg3_StartInstanceMatrix;)

// instance at specified point with specified orientation
typedef void (*g3_StartInstanceAngles_fp)(vector *pos, angvec *angles);
DMFCDLLOUT(g3_StartInstanceAngles_fp DLLg3_StartInstanceAngles;)

// pops the old context
typedef void (*g3_DoneInstance_fp)();
DMFCDLLOUT(g3_DoneInstance_fp DLLg3_DoneInstance;)

// Misc utility functions:

// returns true if a plane is facing the viewer. takes the unrotated surface
// normal of the plane, and a point on it.  The normal need not be normalized
typedef bool (*g3_CheckNormalFacing_fp)(vector *v, vector *norm);
DMFCDLLOUT(g3_CheckNormalFacing_fp DLLg3_CheckNormalFacing;)

// Point definition and rotation functions:

// rotates a point. returns codes.  does not check if already rotated
typedef uint8_t (*g3_RotatePoint_fp)(g3Point *dest, vector *src);
DMFCDLLOUT(g3_RotatePoint_fp DLLg3_RotatePoint;)

// projects a point
typedef void (*g3_ProjectPoint_fp)(g3Point *point);
DMFCDLLOUT(g3_ProjectPoint_fp DLLg3_ProjectPoint;)

// calculate the depth of a point - returns the z coord of the rotated point
typedef float (*g3_CalcPointDepth_fp)(vector *pnt);
DMFCDLLOUT(g3_CalcPointDepth_fp DLLg3_CalcPointDepth;)

// from a 2d point, compute the vector through that point
typedef void (*g3_Point2Vec_fp)(vector *v, int16_t sx, int16_t sy);
DMFCDLLOUT(g3_Point2Vec_fp DLLg3_Point2Vec;)

// code a point.  fills in the p3_codes field of the point, and returns the codes
typedef uint8_t (*g3_CodePoint_fp)(g3Point *point);
DMFCDLLOUT(g3_CodePoint_fp DLLg3_CodePoint;)

// delta rotation functions
typedef vector *(*g3_RotateDeltaX_fp)(vector *dest, float dx);
DMFCDLLOUT(g3_RotateDeltaX_fp DLLg3_RotateDeltaX;)
typedef vector *(*g3_RotateDeltaY_fp)(vector *dest, float dy);
DMFCDLLOUT(g3_RotateDeltaY_fp DLLg3_RotateDeltaY;)
typedef vector *(*g3_RotateDeltaZ_fp)(vector *dest, float dz);
DMFCDLLOUT(g3_RotateDeltaZ_fp DLLg3_RotateDeltaZ;)
typedef vector *(*g3_RotateDeltaVec_fp)(vector *dest, vector *src);
DMFCDLLOUT(g3_RotateDeltaVec_fp DLLg3_RotateDeltaVec;)
typedef uint8_t (*g3_AddDeltaVec_fp)(g3Point *dest, g3Point *src, vector *deltav);
DMFCDLLOUT(g3_AddDeltaVec_fp DLLg3_AddDeltaVec;)

// Drawing functions:
// draw a polygon
// Parameters:	nv - the number of verts in the poly
//					pointlist - a pointer to a list of pointers to points
//					bm - the bitmap handle if texturing.  ignored if flat shading
// typedef int (*g3_DrawPoly_fp)(int nv,g3Point **pointlist,int bm,int map_type=0,g3Codes *clip_codes=NULL);
typedef int (*g3_DrawPoly_fp)(int nv, g3Point **pointlist, int bm, int map_type, g3Codes *clip_codes);
DMFCDLLOUT(g3_DrawPoly_fp DLLg3_DrawPoly;)

// draw a sortof sphere - i.e., the 2d radius is proportional to the 3d
// radius, but not to the distance from the eye
typedef void (*g3_DrawSphere_fp)(ddgr_color color, g3Point *pnt, float rad);
DMFCDLLOUT(g3_DrawSphere_fp DLLg3_DrawSphere;)

// like g3_DrawPoly(), but checks to see if facing.  If surface normal is
// NULL, this routine must compute it, which will be slow.  It is better to
// pre-compute the normal, and pass it to this function.  When the normal
// is passed, this function works like g3_CheckNormalFacing() plus
// g3_DrawPoly().
typedef void (*g3_CheckAndDrawPoly_fp)(int nv, g3Point **pointlist, int bm, vector *norm, vector *pnt);
DMFCDLLOUT(g3_CheckAndDrawPoly_fp DLLg3_CheckAndDrawPoly;)

// draws a line. takes two points.
typedef void (*g3_DrawLine_fp)(ddgr_color color, g3Point *p0, g3Point *p1);
DMFCDLLOUT(g3_DrawLine_fp DLLg3_DrawLine;)

// draws a bitmap with the specified 3d width & height
// returns 1 if off screen, 0 if drew
// typedef void (*g3_DrawBitmap_fp)(vector *pos,float width,float height,int bm,int color=-1);
typedef void (*g3_DrawBitmap_fp)(vector *pos, float width, float height, int bm, int color);
DMFCDLLOUT(g3_DrawBitmap_fp DLLg3_DrawBitmap;)

// Draws a bitmap that has been rotated about its center.  Angle of rotation is passed as 'rot_angle'
// typedef void (*g3_DrawRotatedBitmap_fp)(vector *pos,angle rot_angle,float width,float height,int bm,int color=-1);
typedef void (*g3_DrawRotatedBitmap_fp)(vector *pos, angle rot_angle, float width, float height, int bm, int color);
DMFCDLLOUT(g3_DrawRotatedBitmap_fp DLLg3_DrawRotatedBitmap;)

// Draw a wireframe box aligned with the screen.  Used for the editor.
// Parameters:	color - the color to draw the lines
//					pnt - the center point
//					rad - specifies the width/2 & height/2 of the box
typedef void (*g3_DrawBox_fp)(ddgr_color color, g3Point *pnt, float rad);
DMFCDLLOUT(g3_DrawBox_fp DLLg3_DrawBox;)

// Sets up a custom clipping plane - g3_StartFrame must be called before this is called
typedef void (*g3_SetCustomClipPlane_fp)(uint8_t state, vector *pnt, vector *normal);
DMFCDLLOUT(g3_SetCustomClipPlane_fp DLLg3_SetCustomClipPlane;)

// sets the z distance of the far clipping plane
typedef void (*g3_SetFarClipZ_fp)(float z);
DMFCDLLOUT(g3_SetFarClipZ_fp DLLg3_SetFarClipZ;)

// Clips a polygon
// Parameters:	pointlist - pointer to a list of pointers to points
//					nv - the number of points in the polygon
//					cc - the clip codes for this polygon
// Returns:	a pointer to a list of pointer of points in the clipped polygon
// NOTE: You MUST call g3_FreeTempPoints() when you're done with the clipped polygon
typedef g3Point **(*g3_ClipPolygon_fp)(g3Point **pointlist, int *nv, g3Codes *cc);
DMFCDLLOUT(g3_ClipPolygon_fp DLLg3_ClipPolygon;)

// Free up any temp points (created by the clipper) in the given pointlist
// Parameters:	pointlist - pointer to list of pointers to points, returned by g3_ClipPolygon()
//					nv - the number of points in pointlist
typedef void (*g3_FreeTempPoints_fp)(g3Point **pointlist, int nv);
DMFCDLLOUT(g3_FreeTempPoints_fp DLLg3_FreeTempPoints;)

// Gets the matrix scale vector
typedef void (*g3_GetMatrixScale_fp)(vector *matrix_scale);
DMFCDLLOUT(g3_GetMatrixScale_fp DLLg3_GetMatrixScale;)

// Sets the triangulation test to on or off
typedef void (*g3_SetTriangulationTest_fp)(int state);
DMFCDLLOUT(g3_SetTriangulationTest_fp DLLg3_SetTriangulationTest;)

// draws a line based on the current setting of render states. takes two points.  returns true if drew
typedef void (*g3_DrawSpecialLine_fp)(g3Point *p0, g3Point *p1);
DMFCDLLOUT(g3_DrawSpecialLine_fp DLLg3_DrawSpecialLine;)

// Draws a bitmap on a specific plane.  Also does rotation.  Angle of rotation is passed as 'rot_angle'
typedef void (*g3_DrawPlanarRotatedBitmap_fp)(vector *pos, vector *norm, angle rot_angle, float width, float height,
                                              int bm);
DMFCDLLOUT(g3_DrawPlanarRotatedBitmap_fp DLLg3_DrawPlanarRotatedBitmap;)

// Stops all sounds for a player
typedef void (*PlayerStopSounds_fp)(int slot);
DMFCDLLOUT(PlayerStopSounds_fp DLLPlayerStopSounds;)

// Returns index of argument sought, or 0 if not found
typedef int (*FindArg_fp)(const char *which);
DMFCDLLOUT(FindArg_fp DLLFindArg;)

// Given an object and a weapon, fires a shot from that object
typedef int (*FireWeaponFromObject_fp)(object *obj, int weapon_num, int gun_num, bool f_force_forward,
                                       bool f_force_target);
DMFCDLLOUT(FireWeaponFromObject_fp DLLFireWeaponFromObject;)

// Creates an weapon and sends it speeding on its way
typedef int (*CreateAndFireWeapon_fp)(vector *pos, vector *dir, object *parent, int weapon_num);
DMFCDLLOUT(CreateAndFireWeapon_fp DLLCreateAndFireWeapon;)

// Selects the next camera view in the small windows
typedef void (*SelectNextCameraView_fp)(int window);
DMFCDLLOUT(SelectNextCameraView_fp DLLSelectNextCameraView;)

// adds a type/id item to the inventory (returns true on success)
// typedef bool (*dInven_Add_fp)(Inventory *inven,int type,int id,object *parent=NULL,int aux_type=-1,int aux_id=-1,int
// flags=0,char *description=NULL);
typedef bool (*dInven_Add_fp)(Inventory *inven, int type, int id, object *parent, int aux_type, int aux_id, int flags,
                              char *description);
DMFCDLLOUT(dInven_Add_fp Inven_Add;)

// adds an object to the inventory (marked by it's objhandle)
// typedef bool (*dInven_AddObject_fp)(Inventory *inven,int object_handle,int flags=0,char *description=NULL);
typedef bool (*dInven_AddObject_fp)(Inventory *inven, int object_handle, int flags, char *description);
DMFCDLLOUT(dInven_AddObject_fp Inven_AddObject;)

// adds a special cased CounterMeasure into the inventory
// typedef bool (*dInven_AddCounterMeasure_fp)(Inventory *inven,int id,int aux_type=-1,int aux_id=-1,int flags=0,char
// *description=NULL);
typedef bool (*dInven_AddCounterMeasure_fp)(Inventory *inven, int id, int aux_type, int aux_id, int flags,
                                            char *description);
DMFCDLLOUT(dInven_AddCounterMeasure_fp Inven_AddCounterMeasure;)

//	removes an item from the inventory (reduces it's count by one...if there is no more, then it goes bye-bye)
//	to remove an object that was added via objhandle, then pass the objhandle
//	in the 'type' parameter, and don't pass in an id.
// typedef bool (*dInven_Remove_fp)(Inventory *inven,int type,int id=-1);
typedef bool (*dInven_Remove_fp)(Inventory *inven, int type, int id);
DMFCDLLOUT(dInven_Remove_fp Inven_Remove;)

// uses an item in the inventory (also reduces its count by one...if there is no more, then it goes bye-bye)
// typedef bool (*dInven_Use_fp)(Inventory *inven,int type,int id,object *parent=NULL);
typedef bool (*dInven_Use_fp)(Inventory *inven, int type, int id, object *parent);
DMFCDLLOUT(dInven_Use_fp Inven_Use;)

// uses an item in the inventory (given it's objhandle).
// typedef bool (*dInven_UseObjHandle_fp)(Inventory *inven,int objhandle,object *parent=NULL);
typedef bool (*dInven_UseObjHandle_fp)(Inventory *inven, int objhandle, object *parent);
DMFCDLLOUT(dInven_UseObjHandle_fp Inven_UseObjHandle;)

// returns how many unique type/ids are in the inventory
typedef int (*dInven_Size_fp)(Inventory *inven);
DMFCDLLOUT(dInven_Size_fp Inven_Size;)

// returns true if there is an item in the inventory with the given type/id (or objhandle if id is -1, pass the object
// handle as the type parameter) typedef bool (*dInven_CheckItem_fp)(Inventory *inven,int type,int id=-1);
typedef bool (*dInven_CheckItem_fp)(Inventory *inven, int type, int id);
DMFCDLLOUT(dInven_CheckItem_fp Inven_CheckItem;)

// Resets the inventory, cleaning it out
// in_game: set to true if this is being called from during gameplay
// reset_stage:
//		INVRESET_ALL:			Reset _EVERYTHING_
//		INVRESET_LEVELCHANGE:	Remove everything except those that last across levels
//		INVRESET_DEATHSPEW:		Remove everything except those that do not spew (Default)
// typedef void (*dInven_Reset_fp)(Inventory *inven,bool in_game,int reset_stage=INVRESET_DEATHSPEW);
typedef void (*dInven_Reset_fp)(Inventory *inven, bool in_game, int reset_stage);
DMFCDLLOUT(dInven_Reset_fp Inven_Reset;)

// resets the position pointer in the list to the beginning
typedef void (*dInven_ResetPos_fp)(Inventory *inven);
DMFCDLLOUT(dInven_ResetPos_fp Inven_ResetPos;)

// moves the position pointer to the next inventory item
// skip : if true then skip over non-selectable items
// typedef void (*dInven_NextPos_fp)(Inventory *inven,bool skip=false);
typedef void (*dInven_NextPos_fp)(Inventory *inven, bool skip);
DMFCDLLOUT(dInven_NextPos_fp Inven_NextPos;)

// moves the position pointer to the previous inventory item
// skip : if true then skip over non-selectable items
// typedef void (*dInven_PrevPos_fp)(Inventory *inven,bool skip=false);
typedef void (*dInven_PrevPos_fp)(Inventory *inven, bool skip);
DMFCDLLOUT(dInven_PrevPos_fp Inven_PrevPos;)

// returns the type/id of the item at the current position
// return true if it is a real object (meaning it was placed in the inventory
// via an object handle...so id will be -1)
typedef bool (*dInven_GetPosTypeID_fp)(Inventory *inven, int &type, int &id);
DMFCDLLOUT(dInven_GetPosTypeID_fp Inven_GetPosTypeID;)

// returns the aux type/id of the item
// return true if it is a real object (meaning it was placed in the inventory
// via an object handle...so id will be -1)
typedef bool (*dInven_GetAuxPosTypeID_fp)(Inventory *inven, int &type, int &id);
DMFCDLLOUT(dInven_GetAuxPosTypeID_fp Inven_GetAuxPosTypeID;)

// returns the description of the item at the current position
typedef char *(*dInven_GetPosDescription_fp)(Inventory *inven);
DMFCDLLOUT(dInven_GetPosDescription_fp Inven_GetPosDescription;)

// returns the icon name of the item at the current position
typedef char *(*dInven_GetPosIconName_fp)(Inventory *inven);
DMFCDLLOUT(dInven_GetPosIconName_fp Inven_GetPosIconName;)

// returns the name of the item at the current position
typedef char *(*dInven_GetPosName_fp)(Inventory *inven);
DMFCDLLOUT(dInven_GetPosName_fp Inven_GetPosName;)

// return information about the current position item
// return true if it is a real object
typedef bool (*dInven_GetPosInfo_fp)(Inventory *inven, uint16_t &iflags, int &flags);
DMFCDLLOUT(dInven_GetPosInfo_fp Inven_GetPosInfo;)

// returns the count of the item at the current position
typedef int (*dInven_GetPosCount_fp)(Inventory *inven);
DMFCDLLOUT(dInven_GetPosCount_fp Inven_GetPosCount;)

// returns true if the position pointer is at the begining of the inventory list
typedef bool (*dInven_AtBeginning_fp)(Inventory *inven);
DMFCDLLOUT(dInven_AtBeginning_fp Inven_AtBeginning;)

// returns false if the position pointer is at the end of the inventory list
typedef bool (*dInven_AtEnd_fp)(Inventory *inven);
DMFCDLLOUT(dInven_AtEnd_fp Inven_AtEnd;)

// jump right to an item in the inventory
typedef void (*dInven_GotoPos_fp)(Inventory *inven, int newpos);
DMFCDLLOUT(dInven_GotoPos_fp Inven_GotoPos;)

// jump right to an item in the inventory give it's type and id
// to jump to an item that was added via object handle, pass the object
// handle in as the type, and make id -1.
typedef void (*dInven_GotoPosTypeID_fp)(Inventory *inven, int type, int id);
DMFCDLLOUT(dInven_GotoPosTypeID_fp Inven_GotoPosTypeID;)

// uses the currently selected item
// typedef bool (*dInven_UsePos_fp)(Inventory *inven,object *parent=NULL);
typedef bool (*dInven_UsePos_fp)(Inventory *inven, object *parent);
DMFCDLLOUT(dInven_UsePos_fp Inven_UsePos;)

// returns the 'index' position of the current position
typedef int (*dInven_GetPos_fp)(Inventory *inven);
DMFCDLLOUT(dInven_GetPos_fp Inven_GetPos;)

// checks the pos, if its on a nonselectable item it will move to the next selectable (NULL if none)
// typedef void (*dInven_ValidatePos_fp)(Inventory *inven,bool forward=true);
typedef void (*dInven_ValidatePos_fp)(Inventory *inven, bool forward);
DMFCDLLOUT(dInven_ValidatePos_fp Inven_ValidatePos;)

// returns whether an item is selectable
typedef bool (*dInven_IsSelectable_fp)(Inventory *inven);
DMFCDLLOUT(dInven_IsSelectable_fp Inven_IsSelectable;)

typedef bool (*dInven_IsUsable_fp)(Inventory *inven);
DMFCDLLOUT(dInven_IsUsable_fp Inven_IsUsable;)

// returns how many of an type/id is in the inventory
// for object handle items, pass the object handle in as the type and leave
// id as -1
typedef int (*dInven_GetTypeIDCount_fp)(Inventory *inven, int type, int id);
DMFCDLLOUT(dInven_GetTypeIDCount_fp Inven_GetTypeIDCount;)

// searches the inventory for the specified type/id, sets the pos to it
// for object handle items, pass the object handle in as the type and leave
// id as -1
// typedef bool (*dInven_FindPos_fp)(Inventory *inven,int type,int id=-1);
typedef bool (*dInven_FindPos_fp)(Inventory *inven, int type, int id);
DMFCDLLOUT(dInven_FindPos_fp Inven_FindPos;)

// gets a detailed list of information about what is in the inventory
// returns the number of items filled in.
typedef int (*dInven_GetInventoryItemList_fp)(Inventory *inven, tInvenList *list, int max_amount, int *cur_sel);
DMFCDLLOUT(dInven_GetInventoryItemList_fp Inven_GetInventoryItemList;)

#endif
