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

 * $Logfile: /DescentIII/Main/Dmfc/dmfcfunctions.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:57:20 $
 * $Author: kevinb $
 *
 * Function pointers
 *
 * $Log: dmfcfunctions.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:57:20  kevinb
 * initial 1.5 import
 *
 *
 * 26    8/16/99 5:38p Jeff
 * final updates for patch
 *
 * 25    8/15/99 4:36p Jeff
 * finished exporting all inventory class functions.  export object_info
 * array. added check for -nooutragelogo to display Outrage logo display.
 *
 * 24    8/11/99 5:31p Jeff
 * addon tablefile function returns a bool now
 *
 * 23    8/11/99 1:22p Jeff
 * exported needed functions for camera windows
 *
 * 22    7/20/99 11:27a Jeff
 * created functions to fire weapons
 *
 * 21    7/11/99 3:31p Jeff
 * exported game arguments, made command line option to specify
 * autoexec.dmfc
 *
 * 20    7/07/99 12:16p Jeff
 * all mangles symbol names fixed.  Finished making interface functions.
 *
 * 19    5/20/99 5:31p Jeff
 * exported PlayerStopSounds
 *
 * 18    5/19/99 11:49p Jeff
 * final preparations for dmfc version 1.0
 *
 * 17    5/19/99 5:27p Jeff
 * fixed some function prototypes
 *
 * 16    5/19/99 2:44a Jeff
 * CreateTextItem has a third parameter
 *
 * 15    5/03/99 8:39a Jeff
 * tons of Entropy fixes
 *
 * 14    4/30/99 7:36p Jeff
 * exported vis_effects to dmfc
 *
 * 13    3/27/99 4:53p Jeff
 * player rankings in multiplayer games implemented.  Fixed join message
 * so it doesn't get cut off
 *
 * 12    3/22/99 6:20p Jeff
 * added 2 more audio taunts.  a mulitplayer event when someone plays an
 * audio taunt.  option to disable audio taunts.
 *
 * 11    3/17/99 12:23p Jeff
 * converted DMFC to be COM interface
 *
 * 10    3/12/99 7:40p Jeff
 * removed enhanced objcreate, added enhanced objsetpos
 *
 * 9     3/11/99 6:30p Jeff
 * numerous fixes to demo system in multiplayer games (when
 * recording/playback a demo in a multiplayer game)
 *
 * 8     3/05/99 1:29p Jeff
 *
 * 7     2/25/99 8:54p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 6     2/10/99 11:36p Jeff
 * exported renderer and fvi functions
 *
 * 5     2/08/99 5:22p Jeff
 * exported rend_SetZBuffer...fixed up small view of stats
 *
 * 4     2/08/99 12:06a Jeff
 * exported some new functions and variables
 *
 * 3     2/06/99 6:59p Jeff
 * created RenderHUDGetTextLineWidth and RenderHUDGetTextHeight
 *
 * 2     2/03/99 4:09p Jeff
 * moved function pointers to seperate file. created autoexec.dmfc
 *
 * $NoKeywords: $
 */

#include "DMFC.h"
#include "dmfcinternal.h"
#include "dmfcinputcommands.h"
#include "gamedll_header.h"

void (*DLLGetGameAPI)(game_api *);
bool (*DLLAddHUDMessage)(const char *format, ...);
void (*DLLDebug_ConsolePrintf)(int n, const char *format, ...);
void (*DLLMultiSendClientExecuteDLL)(int eventnum, int me_objnum, int it_objnum, int to, dllinfo *info);
void (*DLLMultiSendObject)(object *obj, uint8_t announce, uint8_t demo_record);
void (*DLLMultiPaintGoalRooms)(int *texcolors);
void (*DLLMultiSendSpecialPacket)(int slot, uint8_t *outdata, int size);
void (*DLLComputeRoomCenter)(vector *vp, room *rp);
int (*DLLGetGoalRoomForTeam)(int teamnum);
int (*DLLObjCreate)(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient,
                                 int parent_handle);
int (*DLLFindObjectIDName)(const char *name);
void (*DLLObjSetPosNoMark)(object *objp, vector *newpos, int roomnum, matrix *orient,
                                        bool f_update_attached_children);
void (*DLLObjSetPos)(object *objp, vector *newpos, int roomnum, matrix *orient,
                                  bool f_update_attached_children);
void (*DLLSetMaxTeams)(int num);
int (*DLLIncTeamScore)(int team, int amount);
bool (*DLLInvCheckItem)(int pnum, int type, int id);
bool (*DLLInvAddTypeID)(int pnum, int type, int id, int aux_type, int aux_id, int flags, const char *description);
bool (*DLLInvRemove)(int pnum, int type, int id);
void (*DLLPlayerSetLighting)(int slot, float dist, float r, float g, float b);
int (*DLLFindShipName)(const char *name);
void (*DLLPlayerSetRotatingBall)(int slot, int num, float speed, float *r, float *g, float *b);
void (*DLLPlayerChangeShip)(int slot, int ship_index);
int (*DLLInvGetTypeIDCount)(int playernum, int type, int id);
int (*DLLPlay3dSound)(int sound_index, object *cur_obj, float volume, int flags);
int (*DLLFindSoundName)(const char *str);
int (*DLLSpewCreate)(spewinfo *spew);
void (*DLLSpewClearEvent)(int handle, bool force);
int (*DLLbm_AllocLoadFileBitmap)(const char *filename, int mipped, int format);
void (*DLLbm_FreeBitmap)(int handle);
void (*DLLrend_DrawScaledBitmap)(int x1, int y1, int x2, int y2, int bm, float u0, float v0, float u1,
                                              float v1, float zval, int color, float *alphas);
void (*DLLgrtext_Printf)(int x, int y, const char *fmt, ...);
void (*DLLgrtext_Flush)(void);
void (*DLLgrtext_SetColor)(ddgr_color col);
void (*DLLgrtext_SetFancyColor)(ddgr_color col1, ddgr_color col2, ddgr_color col3, ddgr_color col4);
void (*DLLgrtext_SetAlpha)(uint8_t alpha);
uint8_t (*DLLgrtext_GetAlpha)(void);
void (*DLLgrtext_SetFont)(int font_handle);
int (*DLLgrtext_GetFont)(void);
int (*DLLgrtext_GetTextLineWidth)(const char *str);
int (*DLLgrfont_GetHeight)(int font);
void (*DLLgrtext_CenteredPrintf)(int xoff, int y, const char *fmt, ...);
bool (*DLLAddColoredHUDMessage)(ddgr_color color, const char *format, ...);
int (*DLLbm_h)(int handle, int miplevel);
int (*DLLbm_w)(int handle, int miplevel);
void (*DLLrend_DrawSimpleBitmap)(int bm_handle, int x, int y);
void (*DLLMultiClientSendSpecialPacket)(uint8_t *outdate, int size);
bool (*DLLAddBlinkingHUDMessage)(char *format, ...);
void (*DLLInvReset)(int playernum, bool reset_all);
void (*DLLAddHUDItem)(tHUDItem *item);
void (*DLLRenderHUDQuad)(int x, int y, int w, int h, float u0, float v0, float u1, float v1, int bm,
                                      uint8_t alpha, int sat_count);
void (*DLLRenderHUDText)(ddgr_color col, uint8_t alpha, int sat_count, int x, int y, const char *fmt, ...);
void (*DLLMultiEndLevel)(void);
uint16_t *(*DLLbm_data)(int handle, int miplevel);
int (*DLLbm_AllocBitmap)(int w, int h, int add_mem);
void (*DLLrend_FillRect)(ddgr_color color, int x1, int y1, int x2, int y2);
bool (*DLLbm_CreateChunkedBitmap)(int bm_handle, chunked_bitmap *chunk);
void (*DLLbm_DestroyChunkedBitmap)(chunked_bitmap *chunk);
void (*DLLrend_DrawChunkedBitmap)(chunked_bitmap *chunk, int x, int y, uint8_t alpha);
void (*DLLrend_DrawScaledChunkedBitmap)(chunked_bitmap *chunk, int x, int y, int neww, int newh,
                                                     uint8_t alpha);
void (*DLLOpenCFILE)(CFILE **handle, const char *filename, const char *mode);
void (*DLLcfclose)(CFILE *cfp);
int (*DLLcfeof)(CFILE *cfp);
int (*DLLcfexist)(const char *filename);
int (*DLLcf_ReadBytes)(uint8_t *buf, int count, CFILE *cfp);
int (*DLLcf_ReadInt)(CFILE *cfp);
int16_t (*DLLcf_ReadShort)(CFILE *cfp);
int8_t (*DLLcf_ReadByte)(CFILE *cfp);
float (*DLLcf_ReadFloat)(CFILE *cfp);
double (*DLLcf_ReadDouble)(CFILE *cfp);
int (*DLLcf_ReadString)(char *buf, size_t n, CFILE *cfp);
int (*DLLcf_WriteBytes)(const uint8_t *buf, int count, CFILE *cfp);
int (*DLLcf_WriteString)(CFILE *cfp, const char *buf);
void (*DLLcf_WriteInt)(CFILE *cfp, int i);
void (*DLLcf_WriteShort)(CFILE *cfp, int16_t s);
void (*DLLcf_WriteByte)(CFILE *cfp, int8_t b);
void (*DLLcf_WriteFloat)(CFILE *cfp, float f);
void (*DLLcf_WriteDouble)(CFILE *cfp, double d);
bool (*DLLcf_CopyFile)(char *dest, const char *src);
bool (*DLLcf_Diff)(const char *a, const char *b);
void (*DLLMultiDisconnectPlayer)(int slot);
void (*DLLnw_GetNumbersFromHostAddress)(network_address *address, char *str);
int (*DLLnw_GetThisIP)(void);
bool (*DLLCreateStringTable)(const char *filename, char ***table, int *size);
void (*DLLDestroyStringTable)(char **table, int size);
void (*DLLRenderHUDTextFlags)(int flags, ddgr_color col, uint8_t alpha, int sat_count, int x, int y, const char *fmt, ...);
void (*DLLPlayerSetHUDNameFOV)(int fov);
void (*DLLGetUltimateParentForObject)(object **parent, object *child);
void (*DLLSetObjectDeadFlagRaw)(object *obj, bool tell_clients_to_remove, bool tell_clients_to_play_sound);
void (*DLLSetObjectDeadFlag)(object *obj, bool tell_clients_to_remove, bool tell_clients_to_play_sound);
void (*FatalError)(const char *reason);
int (*DLLMultiMatchWeapon)(uint32_t unique_id);
uint32_t (*DLLMultiGetMatchChecksum)(int type, int id);
int (*DLLFindWeaponName)(const char *name);
int (*DLLcf_OpenLibrary)(const char *libname);
void (*DLLcf_CloseLibrary)(int handle);
void (*DLLMultiSendRequestToObserve)(int mode, int on, int objnum);
int (*DLLFindTextureName)(const char *name);
bool (*DLLApplyDamageToPlayer)(object *playerobj, object *killer, int damage_type, float damage_amount,
                                            int server_says, int weapon_id, bool playsound);
int (*DLLMultiMatchGeneric)(uint32_t unique_id);
void (*DLLSetUITextItemText)(void *uit, char *newtext, uint32_t color);
void *(*DLLNewUIWindowCreate)(int x, int y, int w, int h, int flags);
void (*DLLNewUIWindowDestroy)(void *deswin);
void (*DLLNewUIWindowOpen)(void *deswin);
void (*DLLNewUIWindowClose)(void *deswin);
void *(*DLLTextCreate)(void *parentwin, void *textitem, int x, int y, int flags);
void *(*DLLEditCreate)(void *parentwin, int id, int x, int y, int w, int h, int flags);
void *(*DLLButtonCreate)(void *parentwin, int id, void *titleitem, int x, int y, int w, int h, int flags);
void *(*DLLListCreate)(void *parentwin, int id, int x, int y, int w, int h, int flags);
void (*DLLListRemoveAll)(void *item);
void (*DLLListAddItem)(void *item, void *uitext);
void (*DLLListRemoveItem)(void *item, void *txtitem);
void (*DLLListSelectItem)(void *item, void *txtitem);
char *(*DLLListGetItem)(void *item, int index);
int (*DLLListGetSelectedIndex)(void *item);
void (*DLLListSetSelectedIndex)(void *item, int index);
void (*DLLEditSetText)(void *item, const char *buff);
void (*DLLEditGetText)(void *item, char *buff, int len);
int (*DLLDoUI)(void);
int (*DLLDoMessageBox)(const char *title, const char *msg, int type, ddgr_color title_color,
                                    ddgr_color text_color);
void (*DLLDescentDefer)(void);
void *(*DLLNewUIGameWindowCreate)(int x, int y, int w, int h, int flags);
void (*DLLNewUIGameWindowDestroy)(void *item);
void (*DLLNewUIGameWindowOpen)(void *item);
void (*DLLNewUIGameWindowClose)(void *item);
void *(*DLLHotSpotCreate)(void *parentwin, int id, int key, void *txtitemoff, void *txtitemon, int x,
                                       int y, int w, int h, int flags);
int (*DLLPollUI)(void);
void (*DLLRemoveUITextItem)(void *item);
void *(*DLLCreateNewUITextItem)(const char *newtext, uint32_t color, int font);
void (*DLLRemoveUIBmpItem)(void *item);
void *(*DLLCreateNewUIBmpItem)(int handle, uint8_t alpha);
void *(*DLLUIConsoleGadgetCreate)(void *parentid, int id, int x, int y, int font, int cols, int rows,
                                               int flags);
void (*DLLUIConsoleGadgetputs)(void *item, const char *str);
void (*DLLNewUIWindowSetFocusOnEditGadget)(void *item, void *parent);
void *(*DLLOldListCreate)(void *parentitem, int id, int x, int y, int w, int h, int flags);
void (*DLLOldListRemoveAll)(void *item);
void (*DLLOldListAddItem)(void *item, void *uitext);
void (*DLLOldListRemoveItem)(void *item, void *txtitem);
void (*DLLOldListSelectItem)(void *item, void *txtitem);
void *(*DLLOldEditCreate)(void *parentitem, int id, int x, int y, int w, int h, int flags);
void (*DLLOldEditGetText)(void *item, char *buff, int len);
void (*DLLOldEditSetText)(void *item, const char *newtext);
char *(*DLLOldListGetItem)(void *item, int index);
int (*DLLOldListGetSelectedIndex)(void *item);
void (*DLLToggleUICallback)(int state);
void (*DLLSetOldEditBufferLen)(void *item, int len);
void (*DLLNewUIWindowLoadBackgroundImage)(void *item, const char *image_name);
void (*DLLDeleteUIItem)(void *delitem);
void (*DLLHotSpotSetStates)(void *hs, void *texton, void *textoff);
void (*DLLSetUICallback)(void (*fn)());
void (*DLLGetUICallback)(void **fn);
void (*DLLSuspendControls)(void);
void (*DLLResumeControls)(void);
void (*DLLShowCursor)(void);
void (*DLLHideCursor)(void);
void (*DLLGameFrame)(void);
void (*DPrintf)(const char *format, ...);
void (*DLLassert)(int, const char *, const char *, int);
void (*DLLddio_SplitPath)(const char *srcPath, char *path, char *filename, char *ext);
void (*DLLddio_MakePath)(char *newPath, const char *absolutePathHeader, const char *subDir, ...);
int (*DLLPlay2dSound)(int sound_index, float volume);
void (*DLLTouchSound)(int sound_index);
bool (*DatabaseRead1)(const char *label, char *entry, int *entrylen);
bool (*DatabaseRead2)(const char *label, void *entry, int wordsize);
bool (*DatabaseRead3)(const char *label, bool *entry);
bool (*DatabaseWrite1)(const char *label, const char *entry, int entrylen);
bool (*DatabaseWrite2)(const char *label, int entry);
bool (*DLLAttachObject)(object *parent, char parent_ap, object *child, char child_ap, bool f_use_aligned);
bool (*DLLObjGet)(int handle, object **obj);
int (*DLLGetUIItemWidth)(void *item);
int (*DLLGetUIItemHeight)(void *item);
void *(*DLLSliderCreate)(void *parent, int id, int x, int y, int flags);
void (*DLLSliderSetRange)(void *slider, int range);
int (*DLLSliderGetRange)(void *slider);
void (*DLLSliderSetPos)(void *slider, int pos);
int (*DLLSliderGetPos)(void *slider);
void (*DLLSliderSetSelectChangeCallback)(void *slider, void (*fn)(int));
void (*DLLSliderSetSelectChangeCallbackWData)(void *slider, void (*fn)(int, void *), void *ptr);
void (*DLLTextSetTitle)(void *text, void *textitem);
bool (*DLLPPic_GetPilot)(uint16_t pilot_id, char *pilot_name, int buffersize);
int (*DLLPPic_GetBitmapHandle)(uint16_t pilot_id);
void (*DLLrend_DrawLine)(int x1, int y1, int x2, int y2);
void (*DLLrend_SetFlatColor)(ddgr_color color);
void (*DLLMultiSetLogoState)(bool state);
void (*DLLPlayerSpewInventory)(object *obj, bool spew_energy_and_shield, bool spew_nonspewable);
int (*DLLPlayerGetRandomStartPosition)(int slot);
void (*DLLInitPlayerNewShip)(int slot, int inven_reset);
void *(*DLLCheckBoxCreate)(void *parent, int id, void *title, int x, int y, int w, int h, int flags);
void (*DLLCheckBoxSetCheck)(void *cb, bool state);
bool (*DLLCheckBoxIsChecked)(void *cb);
uint32_t (*DLLnw_GetHostAddressFromNumbers)(char *str);
void (*TableFilesClear)(void);
bool (*TableFileAdd)(char *filename);
void (*DLLDebugBreak_callback_stop)(void);
void (*DLLDebugBreak_callback_resume)(void);
void (*DLLInt3MessageBox)(const char *file, const char *line);
void (*DLLGetUIItemPosition)(void *item, int *x, int *y, int *w, int *h);
bool (*DLLAttachObjectRadius)(object *parent, char parent_ap, object *child, float percent_rad);
bool (*DLLUnattachChildren)(object *parent);
bool (*DLLUnattachChild)(object *parent, char parent_ap);
bool (*DLLUnattachFromParent)(object *child);
float (*DLLvm_GetMagnitude)(vector *);
void (*DLLvm_MatrixMulVector)(vector *, vector *, matrix *);
void (*DLLphys_apply_force)(object *obj, vector *force_vec, int16_t weapon_index);
void (*DLLphys_apply_rot)(object *obj, vector *force_vec);
void (*DLLvm_TransposeMatrix)(matrix *);
void (*DLLvm_CrossProduct)(vector *, vector *, vector *);
float (*DLLvm_NormalizeVector)(vector *);
void (*DLLConvertEulerToAxisAmount)(vector *e, vector *n, float *w);
void (*DLLConvertAxisAmountToEuler)(vector *n, float *w, vector *e);
float (*DLLvm_GetMagnitudeFast)(vector *);
void (*DLLvm_MakeIdentity)(matrix *);
void (*DLLvm_MakeVectorZero)(vector *v);
void (*DLLvm_MakeAngleZero)(angvec *a);
void (*DLLvm_VectorMulTMatrix)(vector *result, vector *v, matrix *m);
void (*DLLvm_MatrixMul)(matrix *, matrix *, matrix *);
void (*DLLvm_MatrixMulTMatrix)(matrix *dest, matrix *src0, matrix *src1);
float (*DLLvm_DotProduct)(vector *, vector *);
void (*DLLvm_SubVectors)(vector *, const vector *, const vector *);
void (*DLLvm_AddVectors)(vector *, vector *, vector *);
void (*DLLvm_AverageVector)(vector *, int);
void (*DLLvm_ScaleVector)(vector *, vector *, float);
void (*DLLvm_ScaleAddVector)(vector *d, vector *p, vector *v, float s);
void (*DLLvm_DivVector)(vector *, vector *, float);
float (*DLLvm_NormalizeVectorFast)(vector *);
void (*DLLvm_ClearMatrix)(matrix *);
void (*DLLvm_AnglesToMatrix)(matrix *, angle p, angle h, angle b);
void (*DLLvm_Orthogonalize)(matrix *m);
void (*DLLvm_VectorToMatrix)(matrix *m, vector *fvec, vector *uvec, vector *rvec);
void (*DLLvm_VectorAngleToMatrix)(matrix *m, vector *v, angle a);
void (*DLLvm_SinCos)(angle, float *, float *);
float (*DLLvm_GetSlope)(float, float, float, float);
void (*DLLvm_GetPerp)(vector *n, vector *a, vector *b, vector *c);
float (*DLLvm_GetNormal)(vector *n, vector *v0, vector *v1, vector *v2);
float (*DLLvm_VectorDistance)(const vector *a, const vector *b);
float (*DLLvm_VectorDistanceQuick)(vector *a, vector *b);
float (*DLLvm_GetNormalizedDir)(vector *dest, vector *end, vector *start);
float (*DLLvm_GetNormalizedDirFast)(vector *dest, vector *end, vector *start);
angvec *(*DLLvm_ExtractAnglesFromMatrix)(angvec *a, matrix *m);
angle (*DLLvm_DeltaAngVec)(vector *v0, vector *v1, vector *fvec);
angle (*DLLvm_DeltaAngVecNorm)(vector *v0, vector *v1, vector *fvec);
float (*DLLvm_DistToPlane)(vector *checkp, vector *norm, vector *planep);
float (*DLLvm_CalcDetValue)(matrix *det);
void (*DLLvm_MakeInverseMatrix)(matrix *dest);
void (*DLLvm_SinCosToMatrix)(matrix *m, float sinp, float cosp, float sinb, float cosb, float sinh,
                                          float cosh);
float (*DLLvm_GetCentroid)(vector *centroid, vector *src, int nv);
void (*DLLvm_MakeRandomVector)(vector *vec);
float (*DLLvm_ComputeBoundingSphere)(vector *center, vector *vecs, int num_verts);
float (*DLLvm_GetCentroidFast)(vector *centroid, vector *src, int nv);
int (*DLLRenderHUDGetTextLineWidth)(const char *string);
int (*DLLRenderHUDGetTextHeight)(const char *string);
void (*DLLStartFrame)(int x, int y, int x2, int y2, bool clear);
void (*DLLEndFrame)(void);
void (*DLLResetFacings)(void);
void (*DLLGameRenderWorld)(object *viewer, vector *viewer_eye, int viewer_roomnum, matrix *viewer_orient,
                                        float zoom, bool rear_view);
bool (*DLLGetFrameParameters)(int *x1, int *y1, int *x2, int *y2);
void (*DLLrend_SetZBufferState)(int8_t state);
void (*DLLrend_SetLighting)(light_state);
void (*DLLrend_SetColorModel)(color_model);
void (*DLLrend_SetTextureType)(texture_type);
void (*DLLrend_DrawPolygon)(int handle, g3Point **p, int nv, int map_type);
void (*DLLrend_SetMipState)(int8_t);
void (*DLLrend_SetFogState)(int8_t on);
void (*DLLrend_SetFiltering)(int8_t state);
void (*DLLrend_SetOverlayMap)(int handle);
void (*DLLrend_SetOverlayType)(uint8_t type);
void (*DLLrend_ClearScreen)(ddgr_color color);
void (*DLLrend_SetPixel)(ddgr_color color, int x, int y);
ddgr_color (*DLLrend_GetPixel)(int x, int y);
void (*DLLrend_FillCircle)(ddgr_color col, int x, int y, int rad);
void (*DLLrend_DrawCircle)(int x, int y, int rad);
void (*DLLrend_SetAlphaType)(int8_t);
void (*DLLrend_SetAlphaValue)(uint8_t val);
void (*DLLrend_SetWrapType)(wrap_type val);
void (*DLLrend_SetZBias)(float z_bias);
void (*DLLrend_SetZBufferWriteMask)(int state);
void (*DLLrend_GetLFBLock)(renderer_lfb *lfb);
void (*DLLrend_ReleaseLFBLock)(renderer_lfb *lfb);
void (*DLLrend_DrawLFBBitmap)(int sx, int sy, int w, int h, int dx, int dy, uint16_t *data, int rowsize);
void (*DLLrend_DrawSpecialLine)(g3Point *p0, g3Point *p1);
int (*DLLfvi_FindIntersection)(fvi_query *fq, fvi_info *hit_data, bool no_subdivision);
int (*DLLfvi_QuickDistFaceList)(int init_room_index, vector *pos, float rad,
                                             fvi_face_room_list *quick_fr_list, int max_elements);
int (*DLLfvi_QuickDistCellList)(int init_cell_index, vector *pos, float rad, int *quick_cell_list,
                                             int max_elements);
int (*DLLfvi_QuickDistObjectList)(vector *pos, int init_roomnum, float rad, int16_t *object_index_list,
                                               int max_elements, bool f_lightmap_only, bool f_only_players_and_ais,
                                               bool f_include_non_collide_objects, bool f_stop_at_closed_doors);
bool (*DLLfvi_QuickRoomCheck)(vector *pos, room *cur_room, bool try_again);
bool (*DLLtaunt_AreEnabled)(void);
void (*DLLtaunt_Enable)(bool enable);
int (*GetPlayerRankIndex)(int pnum, char *rankbuf);
int (*DLLVisEffectAllocate)(void);
int (*DLLVisEffectFree)(int visnum);
int (*DLLVisEffectInitType)(vis_effect *vis);
int (*DLLVisEffectCreate)(uint8_t type, uint8_t id, int roomnum, vector *pos);
void (*DLLVisEffectLink)(int visnum, int roomnum);
void (*DLLVisEffectUnlink)(int visnum);
void (*DLLVisEffectRelink)(int visnum, int newroomnum);
void (*DLLVisEffectDelete)(int visnum);
void (*DLLCreateRandomSparks)(int num_sparks, vector *pos, int roomnum, int which_index,
                                           float force_scalar);
void (*DLLCreateRandomLineSparks)(int num_sparks, vector *pos, int roomnum, uint16_t color,
                                               float force_scalar);
int (*DLLVisEffectCreateControlled)(uint8_t type, object *parent, uint8_t id, int roomnum, vector *pos,
                                                 float lifetime, vector *velocity, int phys_flags, float size,
                                                 float mass, float drag, bool isreal);
void (*DLLCreateRandomParticles)(int num_sparks, vector *pos, int roomnum, int bm_handle, float size,
                                              float life);
void (*DLLAttachRandomNapalmEffectsToObject)(object *obj);
void (*DLLInitObjectScripts)(object *objp, bool do_evt_created);
void (*DLLg3_StartFrame)(vector *view_pos, matrix *view_matrix, float zoom);
void (*DLLg3_EndFrame)(void);
void (*DLLg3_GetViewPosition)(vector *vp);
void (*DLLg3_GetViewMatrix)(matrix *mat);
void (*DLLg3_GetUnscaledMatrix)(matrix *mat);
void (*DLLg3_StartInstanceMatrix)(vector *pos, matrix *orient);
void (*DLLg3_StartInstanceAngles)(vector *pos, angvec *angles);
void (*DLLg3_DoneInstance)();
bool (*DLLg3_CheckNormalFacing)(vector *v, vector *norm);
uint8_t (*DLLg3_RotatePoint)(g3Point *dest, vector *src);
void (*DLLg3_ProjectPoint)(g3Point *point);
float (*DLLg3_CalcPointDepth)(vector *pnt);
void (*DLLg3_Point2Vec)(vector *v, int16_t sx, int16_t sy);
uint8_t (*DLLg3_CodePoint)(g3Point *point);
vector *(*DLLg3_RotateDeltaX)(vector *dest, float dx);
vector *(*DLLg3_RotateDeltaY)(vector *dest, float dy);
vector *(*DLLg3_RotateDeltaZ)(vector *dest, float dz);
vector *(*DLLg3_RotateDeltaVec)(vector *dest, vector *src);
uint8_t (*DLLg3_AddDeltaVec)(g3Point *dest, g3Point *src, vector *deltav);
int (*DLLg3_DrawPoly)(int nv, g3Point **pointlist, int bm, int map_type, g3Codes *clip_codes);
void (*DLLg3_DrawSphere)(ddgr_color color, g3Point *pnt, float rad);
void (*DLLg3_CheckAndDrawPoly)(int nv, g3Point **pointlist, int bm, vector *norm, vector *pnt);
void (*DLLg3_DrawLine)(ddgr_color color, g3Point *p0, g3Point *p1);
void (*DLLg3_DrawBitmap)(vector *pos, float width, float height, int bm, int color);
void (*DLLg3_DrawRotatedBitmap)(vector *pos, angle rot_angle, float width, float height, int bm,
                                             int color);
void (*DLLg3_DrawBox)(ddgr_color color, g3Point *pnt, float rad);
void (*DLLg3_SetCustomClipPlane)(uint8_t state, vector *pnt, vector *normal);
void (*DLLg3_SetFarClipZ)(float z);
g3Point **(*DLLg3_ClipPolygon)(g3Point **pointlist, int *nv, g3Codes *cc);
void (*DLLg3_FreeTempPoints)(g3Point **pointlist, int nv);
void (*DLLg3_GetMatrixScale)(vector *matrix_scale);
void (*DLLg3_SetTriangulationTest)(int state);
void (*DLLg3_DrawSpecialLine)(g3Point *p0, g3Point *p1);
void (*DLLg3_DrawPlanarRotatedBitmap)(vector *pos, vector *norm, angle rot_angle, float width,
                                                   float height, int bm);
void (*DLLPlayerStopSounds)(int slot);
int (*DLLFindArg)(const char *which);
int (*DLLFireWeaponFromObject)(object *obj, int weapon_num, int gun_num, bool f_force_forward,
                                            bool f_force_target);
int (*DLLCreateAndFireWeapon)(vector *pos, vector *dir, object *parent, int weapon_num);
void (*DLLSelectNextCameraView)(int window);
bool (*Inven_Add)(Inventory *inven, int type, int id, object *parent, int aux_type, int aux_id, int flags,
                               char *description);
bool (*Inven_AddObject)(Inventory *inven, int object_handle, int flags, char *description);
bool (*Inven_AddCounterMeasure)(Inventory *inven, int id, int aux_type, int aux_id, int flags,
                                             char *description);
bool (*Inven_Remove)(Inventory *inven, int type, int id);
bool (*Inven_Use)(Inventory *inven, int type, int id, object *parent);
bool (*Inven_UseObjHandle)(Inventory *inven, int objhandle, object *parent);
int (*Inven_Size)(Inventory *inven);
bool (*Inven_CheckItem)(Inventory *inven, int type, int id);
void (*Inven_Reset)(Inventory *inven, bool in_game, int reset_stage);
void (*Inven_ResetPos)(Inventory *inven);
void (*Inven_NextPos)(Inventory *inven, bool skip);
void (*Inven_PrevPos)(Inventory *inven, bool skip);
bool (*Inven_GetPosTypeID)(Inventory *inven, int &type, int &id);
bool (*Inven_GetAuxPosTypeID)(Inventory *inven, int &type, int &id);
char *(*Inven_GetPosDescription)(Inventory *inven);
char *(*Inven_GetPosIconName)(Inventory *inven);
char *(*Inven_GetPosName)(Inventory *inven);
bool (*Inven_GetPosInfo)(Inventory *inven, uint16_t &iflags, int &flags);
int (*Inven_GetPosCount)(Inventory *inven);
bool (*Inven_AtBeginning)(Inventory *inven);
bool (*Inven_AtEnd)(Inventory *inven);
void (*Inven_GotoPos)(Inventory *inven, int newpos);
void (*Inven_GotoPosTypeID)(Inventory *inven, int type, int id);
bool (*Inven_UsePos)(Inventory *inven, object *parent);
int (*Inven_GetPos)(Inventory *inven);
void (*Inven_ValidatePos)(Inventory *inven, bool forward);
bool (*Inven_IsSelectable)(Inventory *inven);
bool (*Inven_IsUsable)(Inventory *inven);
int (*Inven_GetTypeIDCount)(Inventory *inven, int type, int id);
bool (*Inven_FindPos)(Inventory *inven, int type, int id);
int (*Inven_GetInventoryItemList)(Inventory *inven, tInvenList *list, int max_amount, int *cur_sel);
