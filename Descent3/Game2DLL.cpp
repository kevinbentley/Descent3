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

#include "pstypes.h"
#include "pserror.h"
#include "game.h"
#include "game2dll.h"
#include "room.h"
#include "object.h"
#include "terrain.h"
#include "player.h"
#include "mono.h"
#include "hud.h"
#include "Inventory.h"
#include "multi_server.h"
#include "ship.h"
#include "DllWrappers.h"
#include "soundload.h"
#include "spew.h"
#include "objinfo.h"
#include "module.h"
#include "localization.h"
#include "weapon.h"
#include "voice.h"
#include "gametexture.h"
#include "Mission.h"
#include "damage.h"
#include "ui.h"
#include "newui.h"
#include "multi_dll_mgr.h"
#include "controls.h"
#include "gameloop.h"
#include "gamesequence.h"
#include "dedicated_server.h"
#include "attach.h"
#include "PilotPicsAPI.h"
#include "vclip.h"
#include "osiris_dll.h"
#include "manage.h"
#include "PHYSICS.H"
#include "collide.h"
#include "render.h"
#include "audiotaunts.h"
#include "polymodel.h"
#include "osiris_share.h"
#include "viseffect.h"
#include "ObjScript.h"
#include "args.h"

#include <algorithm>

void SelectNextCameraView(int window);
#define NUM_CAMERA_VIEWS 3
extern std::array<int, NUM_CAMERA_VIEWS> Camera_view_mode;

//	Osiris_CreateModuleInitStruct
//	Purpose:
//		This function initializes a Module Init Struct with all the needed data to get sent
//	to the module during initialization.
extern void Osiris_CreateModuleInitStruct(tOSIRISModuleInit *mi);
module GameDLLHandle = {NULL};
extern std::array<ddgr_color, 32> Player_colors;
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
// The exported DLL function call prototypes
#if defined(__LINUX__)
typedef void DLLFUNCCALL (*DLLGameCall_fp)(int eventnum, dllinfo *data);
typedef void DLLFUNCCALL (*DLLGameInit_fp)(int *api_func, uint8_t *all_ok, int num_teams_to_use);
typedef void DLLFUNCCALL (*DLLGameClose_fp)();
typedef void DLLFUNCCALL (*DLLGameGetName_fp)(char *buffer, int maxsize);
typedef void DLLFUNCCALL (*DLLGameGetDesc_fp)(char **buffer, int maxsize, int lines);
typedef void DLLFUNCCALL (*DLLGetGameInfo_fp)(tDLLOptions *options);
#else
typedef void(DLLFUNCCALL *DLLGameCall_fp)(int eventnum, dllinfo *data);
typedef void(DLLFUNCCALL *DLLGameInit_fp)(int *api_func, uint8_t *all_ok, int num_teams_to_use);
typedef void(DLLFUNCCALL *DLLGameClose_fp)();
typedef void(DLLFUNCCALL *DLLGameGetName_fp)(char *buffer, int maxsize);
typedef void(DLLFUNCCALL *DLLGameGetDesc_fp)(char **buffer, int maxsize, int lines);
typedef void(DLLFUNCCALL *DLLGetGameInfo_fp)(tDLLOptions *options);
#endif
DLLGameCall_fp DLLGameCall = NULL;
DLLGameInit_fp DLLGameInit = NULL;
DLLGameClose_fp DLLGameClose = NULL;
DLLGetGameInfo_fp DLLGetGameInfo = NULL;
dllinfo DLLInfo;
tOSIRISModuleInit Multi_d3m_osiris_funcs;
char Multi_game_dll_name[_MAX_PATH * 2];
#define GAMEDLL_FUNCPOINTERS 400
#ifdef _DEBUG
#define NEXTFP                                                                                                         \
  do {                                                                                                                 \
    i++;                                                                                                               \
    if (i >= GAMEDLL_FUNCPOINTERS)                                                                                     \
      Int3();                                                                                                          \
  } while (0);                                                                                                         \
  api->fp[i]
#else
#define NEXTFP                                                                                                         \
  i++;                                                                                                                 \
  api->fp[i]
#endif

static void DUMMYrend_DrawScaledBitmap(int x1, int y1, int x2, int y2, int bm, float u0, float v0, float u1, float v1,
                                       float zval, int color, float *alphas) {
  ASSERT(zval >= 0.0f && zval <= 1.0f);
  rend_DrawScaledBitmap(x1, y1, x2, y2, bm, u0, v0, u1, v1, color, alphas);
}

void GetGameAPI(game_api *api) {
  api->objs = (int *)std::data(Objects);
  api->rooms = (int *)std::data(Rooms);
  api->terrain = (int *)Terrain_seg;
  api->players = (int *)std::data(Players);
  api->netgame = (int *)&Netgame;
  api->netplayers = (int *)&NetPlayers;
  api->ships = (int *)&Ships;
  api->weapons = (int *)&Weapons;
  api->Current_mission = (int *)&Current_mission;
  api->GameTextures = (int *)std::data(GameTextures);
  api->GameVClips = (int *)GameVClips;
  // Fill in function pointers here.  The order here must match the order on the
  // DLL side
  int i = -1; // start at -1 because it increments right away

  NEXTFP = (int *)AddHUDMessage;
  NEXTFP = (int *)MultiSendClientExecuteDLL;
  NEXTFP = (int *)FindObjectIDName;
  NEXTFP = (int *)GetGoalRoomForTeam;
  NEXTFP = (int *)SetMaxTeams;
  NEXTFP = (int *)ComputeRoomCenter;
  NEXTFP = (int *)ObjCreate;
  NEXTFP = (int *)MultiSendObject;
  NEXTFP = (int *)MultiPaintGoalRooms;
  NEXTFP = (int *)MultiSendSpecialPacket;
  NEXTFP = (int *)IncTeamScore;
  NEXTFP = (int *)MonoPrintf;
  NEXTFP = (int *)ObjSetPos;
  NEXTFP = (int *)InvCheckItem;
  NEXTFP = (int *)InvAddTypeID;
  NEXTFP = (int *)InvRemove;
  NEXTFP = (int *)PlayerSetLighting;
  NEXTFP = (int *)FindShipName;
  NEXTFP = (int *)PlayerSetRotatingBall;
  NEXTFP = (int *)ChangePlayerShipIndex;
  NEXTFP = (int *)InvGetTypeIDCount;
  NEXTFP = (int *)D3W_Play3dSound;
  NEXTFP = (int *)FindSoundName;
  NEXTFP = (int *)SpewCreate;
  NEXTFP = (int *)SpewClearEvent;
  NEXTFP = (int *)bm_AllocLoadFileBitmap;
  NEXTFP = (int *)bm_FreeBitmap;
  NEXTFP = (int *)DUMMYrend_DrawScaledBitmap;
  NEXTFP = (int *)grtext_Printf;
  NEXTFP = (int *)grtext_Flush;
  NEXTFP = (int *)grtext_SetColor;
  NEXTFP = (int *)grtext_SetFancyColor;
  NEXTFP = (int *)grtext_SetAlpha;
  NEXTFP = (int *)grtext_GetAlpha;
  NEXTFP = (int *)grtext_SetFont;
  NEXTFP = (int *)grtext_GetFont;
  NEXTFP = (int *)grtext_GetTextLineWidth;
  NEXTFP = (int *)grfont_GetHeight;
  NEXTFP = (int *)grtext_CenteredPrintf;
  NEXTFP = (int *)AddColoredHUDMessage;
  NEXTFP = (int *)bm_w;
  NEXTFP = (int *)bm_h;
  NEXTFP = (int *)rend_DrawSimpleBitmap;
  NEXTFP = (int *)MultiClientSendSpecialPacket;
  NEXTFP = (int *)AddBlinkingHUDMessage;
  NEXTFP = (int *)InvReset;
  NEXTFP = (int *)AddHUDItem;
  NEXTFP = (int *)RenderHUDQuad;
  NEXTFP = (int *)RenderHUDText;
  NEXTFP = (int *)MultiEndLevel;
  NEXTFP = (int *)bm_data;
  NEXTFP = (int *)bm_AllocBitmap;
  NEXTFP = (int *)rend_FillRect;
  NEXTFP = (int *)bm_CreateChunkedBitmap;
  NEXTFP = (int *)bm_DestroyChunkedBitmap;
  NEXTFP = (int *)rend_DrawChunkedBitmap;
  NEXTFP = (int *)rend_DrawScaledChunkedBitmap;
  NEXTFP = (int *)OpenCFILE;
  NEXTFP = (int *)cfclose;
  NEXTFP = (int *)cfeof;
  NEXTFP = (int *)cfexist;
  NEXTFP = (int *)cf_ReadBytes;
  NEXTFP = (int *)cf_ReadInt;
  NEXTFP = (int *)cf_ReadShort;
  NEXTFP = (int *)cf_ReadByte;
  NEXTFP = (int *)cf_ReadFloat;
  NEXTFP = (int *)cf_ReadDouble;
  NEXTFP = (int *)cf_ReadString;
  NEXTFP = (int *)cf_WriteBytes;
  NEXTFP = (int *)cf_WriteString;
  NEXTFP = (int *)cf_WriteInt;
  NEXTFP = (int *)cf_WriteShort;
  NEXTFP = (int *)cf_WriteByte;
  NEXTFP = (int *)cf_WriteFloat;
  NEXTFP = (int *)cf_WriteDouble;
  NEXTFP = (int *)cf_CopyFile;
  NEXTFP = (int *)cf_Diff;
  NEXTFP = (int *)MultiDisconnectPlayer;
  NEXTFP = (int *)nw_GetNumbersFromHostAddress;
  NEXTFP = (int *)nw_GetThisIP;
  NEXTFP = (int *)CreateStringTable;
  NEXTFP = (int *)DestroyStringTable;
  NEXTFP = (int *)RenderHUDTextFlags;
  NEXTFP = (int *)PlayerSpewInventory;
  NEXTFP = (int *)PlayerSetHUDNameFOV;
  NEXTFP = (int *)GetUltimateParentForObject;
  NEXTFP = (int *)SetObjectDeadFlagDLL;
  NEXTFP = (int *)DLLFatalError;
  NEXTFP = (int *)assertdll;
  NEXTFP = (int *)MultiMatchWeapon;
  NEXTFP = (int *)MultiGetMatchChecksum;
  NEXTFP = (int *)FindWeaponName;
  NEXTFP = (int *)cf_OpenLibrary;
  NEXTFP = (int *)cf_CloseLibrary;
  NEXTFP = (int *)MultiSendRequestToObserve;
  NEXTFP = (int *)FindTextureName;
  NEXTFP = (int *)ApplyDamageToPlayer;
  NEXTFP = (int *)MultiMatchGeneric;
  NEXTFP = (int *)SetUITextItemText;
  NEXTFP = (int *)NewUIWindowCreate;
  NEXTFP = (int *)NewUIWindowDestroy;
  NEXTFP = (int *)NewUIWindowOpen;
  NEXTFP = (int *)NewUIWindowClose;
  NEXTFP = (int *)TextCreate;
  NEXTFP = (int *)EditCreate;
  NEXTFP = (int *)ButtonCreate;
  NEXTFP = (int *)ListCreate;
  NEXTFP = (int *)ListRemoveAll;
  NEXTFP = (int *)ListAddItem;
  NEXTFP = (int *)ListRemoveItem;
  NEXTFP = (int *)ListSelectItem;
  NEXTFP = (int *)ListGetItem;
  NEXTFP = (int *)ListGetSelectedIndex;
  NEXTFP = (int *)EditSetText;
  NEXTFP = (int *)EditGetText;
  NEXTFP = (int *)DoUI;
  NEXTFP = (int *)DoMessageBox;
  NEXTFP = (int *)DescentDefer;
  NEXTFP = (int *)NewUIGameWindowCreate;
  NEXTFP = (int *)NewUIGameWindowDestroy;
  NEXTFP = (int *)NewUIGameWindowOpen;
  NEXTFP = (int *)NewUIGameWindowClose;
  NEXTFP = (int *)HotSpotCreate;
  NEXTFP = (int *)PollUI;
  NEXTFP = (int *)RemoveUITextItem;
  NEXTFP = (int *)CreateNewUITextItem;
  NEXTFP = (int *)UIConsoleGadgetCreate;
  NEXTFP = (int *)UIConsoleGadgetputs;
  NEXTFP = (int *)NewUIWindowSetFocusOnEditGadget;
  NEXTFP = (int *)OldEditCreate;
  NEXTFP = (int *)OldListCreate;
  NEXTFP = (int *)OldListRemoveAll;
  NEXTFP = (int *)OldListAddItem;
  NEXTFP = (int *)OldListRemoveItem;
  NEXTFP = (int *)OldListSelectItem;
  NEXTFP = (int *)OldListGetItem;
  NEXTFP = (int *)OldListGetSelectedIndex;
  NEXTFP = (int *)OldEditSetText;
  NEXTFP = (int *)OldEditGetText;
  NEXTFP = (int *)ToggleUICallback;
  NEXTFP = (int *)SetOldEditBufferLen;
  NEXTFP = (int *)NewUIWindowLoadBackgroundImage;
  NEXTFP = (int *)DeleteUIItem;
  NEXTFP = (int *)HotSpotSetStates;
  NEXTFP = (int *)SetUICallback;
  NEXTFP = (int *)RetrieveUICallback;
  NEXTFP = (int *)SuspendControls;
  NEXTFP = (int *)ResumeControls;
  NEXTFP = (int *)ui_ShowCursor;
  NEXTFP = (int *)ui_HideCursor;
  NEXTFP = (int *)GameFrame;
  NEXTFP = (int *)PrintDedicatedMessage;
  NEXTFP = (int *)ddio_MakePath;
  NEXTFP = (int *)ddio_SplitPath;
  NEXTFP = (int *)D3W_Play2dSound;
  NEXTFP = (int *)D3W_TouchSound;
  NEXTFP = (int *)dDatabaseRead1;
  NEXTFP = (int *)dDatabaseRead2;
  NEXTFP = (int *)dDatabaseRead3;
  NEXTFP = (int *)dDatabaseWrite1;
  NEXTFP = (int *)dDatabaseWrite2;
  NEXTFP = (int *)dAttachObject;
  NEXTFP = (int *)dObjGet;
  NEXTFP = (int *)ListSetSelectedIndex;
  NEXTFP = (int *)RemoveUIBmpItem;
  NEXTFP = (int *)CreateNewUIBmpItem;
  NEXTFP = (int *)GetUIItemWidth;
  NEXTFP = (int *)GetUIItemHeight;
  NEXTFP = (int *)SliderCreate;
  NEXTFP = (int *)SliderSetRange;
  NEXTFP = (int *)SliderGetRange;
  NEXTFP = (int *)SliderSetPos;
  NEXTFP = (int *)SliderGetPos;
  NEXTFP = (int *)SliderSetSelectChangeCallback;
  NEXTFP = (int *)SliderSetSelectChangeCallbackWData;
  NEXTFP = (int *)TextSetTitle;
  NEXTFP = (int *)PPic_GetPilot;
  NEXTFP = (int *)PPic_GetBitmapHandle;
  NEXTFP = (int *)rend_DrawLine;
  NEXTFP = (int *)rend_SetFlatColor;
  NEXTFP = (int *)MultiSetLogoState;
  NEXTFP = (int *)PlayerGetRandomStartPosition;
  NEXTFP = (int *)InitPlayerNewShip;
  NEXTFP = (int *)CheckBoxCreate;
  NEXTFP = (int *)CheckBoxSetCheck;
  NEXTFP = (int *)CheckBoxIsChecked;
  NEXTFP = (int *)nw_GetHostAddressFromNumbers;
  NEXTFP = (int *)mng_ClearAddonTables;
  NEXTFP = (int *)mng_SetAddonTable;
  NEXTFP = (int *)DebugBreak_callback_stop;
  NEXTFP = (int *)DebugBreak_callback_resume;
  NEXTFP = (int *)Int3MessageBox;
  NEXTFP = (int *)GetUIItemPosition;
  NEXTFP = (int *)dAttachObjectRadius;
  NEXTFP = (int *)dUnattachChildren;
  NEXTFP = (int *)dUnattachChild;
  NEXTFP = (int *)dUnattachFromParent;
  NEXTFP = (int *)vm_GetMagnitude;
  NEXTFP = (int *)vm_MatrixMulVector;
  NEXTFP = (int *)phys_apply_force;
  NEXTFP = (int *)phys_apply_rot;
  NEXTFP = (int *)vm_TransposeMatrix;
  NEXTFP = (int *)vm_CrossProduct;
  NEXTFP = (int *)vm_NormalizeVector;
  NEXTFP = (int *)ConvertEulerToAxisAmount;
  NEXTFP = (int *)ConvertAxisAmountToEuler;
  NEXTFP = (int *)vm_GetMagnitudeFast;
  NEXTFP = (int *)vm_MakeIdentity;
  NEXTFP = (int *)dvm_MakeZeroVector;
  NEXTFP = (int *)dvm_MakeZeroAngle;
  NEXTFP = (int *)vm_VectorMulTMatrix;
  NEXTFP = (int *)vm_MatrixMul;
  NEXTFP = (int *)vm_MatrixMulTMatrix;
  NEXTFP = (int *)vm_DotProduct;
  NEXTFP = (int *)vm_SubVectors;
  NEXTFP = (int *)vm_AddVectors;
  NEXTFP = (int *)vm_AverageVector;
  NEXTFP = (int *)vm_ScaleVector;
  NEXTFP = (int *)vm_ScaleAddVector;
  NEXTFP = (int *)vm_DivVector;
  NEXTFP = (int *)vm_NormalizeVectorFast;
  NEXTFP = (int *)vm_ClearMatrix;
  NEXTFP = (int *)vm_AnglesToMatrix;
  NEXTFP = (int *)vm_Orthogonalize;
  NEXTFP = (int *)vm_VectorToMatrix;
  NEXTFP = (int *)vm_VectorAngleToMatrix;
  NEXTFP = (int *)vm_SinCos;
  NEXTFP = (int *)vm_GetSlope;
  NEXTFP = (int *)vm_GetPerp;
  NEXTFP = (int *)vm_GetNormal;
  NEXTFP = (int *)vm_VectorDistance;
  NEXTFP = (int *)vm_VectorDistanceQuick;
  NEXTFP = (int *)vm_GetNormalizedDir;
  NEXTFP = (int *)vm_GetNormalizedDirFast;
  NEXTFP = (int *)vm_ExtractAnglesFromMatrix;
  NEXTFP = (int *)vm_DeltaAngVec;
  NEXTFP = (int *)vm_DeltaAngVecNorm;
  NEXTFP = (int *)vm_DistToPlane;
  NEXTFP = (int *)calc_det_value;
  NEXTFP = (int *)vm_MakeInverseMatrix;
  NEXTFP = (int *)vm_SinCosToMatrix;
  NEXTFP = (int *)vm_GetCentroid;
  NEXTFP = (int *)vm_MakeRandomVector;
  NEXTFP = (int *)vm_ComputeBoundingSphere;
  NEXTFP = (int *)vm_GetCentroidFast;
  NEXTFP = (int *)RenderHUDGetTextLineWidth;
  NEXTFP = (int *)RenderHUDGetTextHeight;
  NEXTFP = (int *)dStartFrame;
  NEXTFP = (int *)EndFrame;
  NEXTFP = (int *)ResetFacings;
  NEXTFP = (int *)GameRenderWorld;
  NEXTFP = (int *)GetFrameParameters;
  NEXTFP = (int *)rend_SetZBufferState;
  NEXTFP = (int *)rend_SetLighting;
  NEXTFP = (int *)rend_SetColorModel;
  NEXTFP = (int *)rend_SetTextureType;
  NEXTFP = (int *)rend_DrawPolygon3D;
  NEXTFP = (int *)rend_SetMipState;
  NEXTFP = (int *)rend_SetFogState;
  NEXTFP = (int *)rend_SetFiltering;
  NEXTFP = (int *)rend_SetOverlayMap;
  NEXTFP = (int *)rend_SetOverlayType;
  NEXTFP = (int *)rend_ClearScreen;
  NEXTFP = (int *)rend_SetPixel;
  NEXTFP = (int *)rend_GetPixel;
  NEXTFP = (int *)rend_FillCircle;
  NEXTFP = (int *)rend_DrawCircle;
  NEXTFP = (int *)rend_SetAlphaType;
  NEXTFP = (int *)rend_SetAlphaValue;
  NEXTFP = (int *)rend_SetWrapType;
  NEXTFP = (int *)rend_SetZBias;
  NEXTFP = (int *)rend_SetZBufferWriteMask;
  NEXTFP = (int *)rend_GetLFBLock;
  NEXTFP = (int *)rend_ReleaseLFBLock;
  NEXTFP = (int *)rend_DrawLFBBitmap;
  NEXTFP = (int *)rend_DrawSpecialLine;
  NEXTFP = (int *)fvi_FindIntersection;
  NEXTFP = (int *)fvi_QuickDistFaceList;
  NEXTFP = (int *)fvi_QuickDistCellList;
  NEXTFP = (int *)fvi_QuickDistObjectList;
  NEXTFP = (int *)fvi_QuickRoomCheck;
  NEXTFP = (int *)ObjSetPosAndMarkMoved;
  NEXTFP = (int *)dSetObjectDeadFlagWDemo;
  NEXTFP = (int *)taunt_AreEnabled;
  NEXTFP = (int *)dSetAudioTaunts;
  NEXTFP = (int *)GetRankIndex;
  NEXTFP = (int *)VisEffectAllocate;
  NEXTFP = (int *)VisEffectFree;
  NEXTFP = (int *)VisEffectInitType;
  NEXTFP = (int *)VisEffectCreate;
  NEXTFP = (int *)VisEffectLink;
  NEXTFP = (int *)VisEffectUnlink;
  NEXTFP = (int *)VisEffectRelink;
  NEXTFP = (int *)VisEffectDelete;
  NEXTFP = (int *)CreateRandomSparks;
  NEXTFP = (int *)CreateRandomLineSparks;
  NEXTFP = (int *)VisEffectCreateControlled;
  NEXTFP = (int *)CreateRandomParticles;
  NEXTFP = (int *)AttachRandomNapalmEffectsToObject;
  NEXTFP = (int *)InitObjectScripts;
  NEXTFP = (int *)g3_StartFrame;
  NEXTFP = (int *)g3_EndFrame;
  NEXTFP = (int *)g3_GetViewPosition;
  NEXTFP = (int *)g3_GetViewMatrix;
  NEXTFP = (int *)g3_GetUnscaledMatrix;
  NEXTFP = (int *)g3_StartInstanceMatrix;
  NEXTFP = (int *)g3_StartInstanceAngles;
  NEXTFP = (int *)g3_DoneInstance;
  NEXTFP = (int *)g3_CheckNormalFacing;
  NEXTFP = (int *)g3_RotatePoint;
  NEXTFP = (int *)g3_ProjectPoint;
  NEXTFP = (int *)g3_CalcPointDepth;
  NEXTFP = (int *)g3_Point2Vec;
  NEXTFP = (int *)g3_CodePoint;
  NEXTFP = (int *)g3_RotateDeltaX;
  NEXTFP = (int *)g3_RotateDeltaY;
  NEXTFP = (int *)g3_RotateDeltaZ;
  NEXTFP = (int *)g3_RotateDeltaVec;
  NEXTFP = (int *)g3_AddDeltaVec;
  NEXTFP = (int *)g3_DrawPoly;
  NEXTFP = (int *)g3_DrawSphere;
  NEXTFP = (int *)g3_CheckAndDrawPoly;
  NEXTFP = (int *)g3_DrawLine;
  NEXTFP = (int *)g3_DrawBitmap;
  NEXTFP = (int *)g3_DrawRotatedBitmap;
  NEXTFP = (int *)g3_DrawBox;
  NEXTFP = (int *)g3_SetCustomClipPlane;
  NEXTFP = (int *)g3_SetFarClipZ;
  NEXTFP = (int *)g3_ClipPolygon;
  NEXTFP = (int *)g3_FreeTempPoints;
  NEXTFP = (int *)g3_GetMatrixScale;
  NEXTFP = (int *)g3_SetTriangulationTest;
  NEXTFP = (int *)g3_DrawSpecialLine;
  NEXTFP = (int *)g3_DrawPlanarRotatedBitmap;
  NEXTFP = (int *)PlayerStopSounds;
  NEXTFP = (int *)FindArg;
  NEXTFP = (int *)FireWeaponFromObject;
  NEXTFP = (int *)CreateAndFireWeapon;
  NEXTFP = (int *)SelectNextCameraView;
  NEXTFP = (int *)dInven_Add;
  NEXTFP = (int *)dInven_AddObject;
  NEXTFP = (int *)dInven_AddCounterMeasure;
  NEXTFP = (int *)dInven_Remove;
  NEXTFP = (int *)dInven_Use;
  NEXTFP = (int *)dInven_UseObjHandle;
  NEXTFP = (int *)dInven_Size;
  NEXTFP = (int *)dInven_CheckItem;
  NEXTFP = (int *)dInven_Reset;
  NEXTFP = (int *)dInven_ResetPos;
  NEXTFP = (int *)dInven_NextPos;
  NEXTFP = (int *)dInven_PrevPos;
  NEXTFP = (int *)dInven_GetPosTypeID;
  NEXTFP = (int *)dInven_GetAuxPosTypeID;
  NEXTFP = (int *)dInven_GetPosDescription;
  NEXTFP = (int *)dInven_GetPosIconName;
  NEXTFP = (int *)dInven_GetPosName;
  NEXTFP = (int *)dInven_GetPosInfo;
  NEXTFP = (int *)dInven_GetPosCount;
  NEXTFP = (int *)dInven_AtBeginning;
  NEXTFP = (int *)dInven_AtEnd;
  NEXTFP = (int *)dInven_GotoPos;
  NEXTFP = (int *)dInven_GotoPosTypeID;
  NEXTFP = (int *)dInven_UsePos;
  NEXTFP = (int *)dInven_GetPos;
  NEXTFP = (int *)dInven_ValidatePos;
  NEXTFP = (int *)dInven_IsSelectable;
  NEXTFP = (int *)dInven_IsUsable;
  NEXTFP = (int *)dInven_GetTypeIDCount;
  NEXTFP = (int *)dInven_FindPos;
  NEXTFP = (int *)dInven_GetInventoryItemList;

  // Variable pointers
  api->vp[0] = (int *)&Player_num;
  api->vp[1] = (int *)&Highest_room_index;
  api->vp[2] = (int *)&Game_window_w;
  api->vp[3] = (int *)&Game_window_h;
  api->vp[4] = (int *)&Game_fonts;
  api->vp[5] = (int *)&Frametime;
  api->vp[6] = (int *)&Gametime;
  api->vp[7] = (int *)&Multi_additional_damage;
  api->vp[8] = (int *)&Game_interface_mode;
  api->vp[9] = (int *)LocalD3Dir;
  api->vp[10] = (int *)&Game_is_master_tracker_game;
  api->vp[11] = (int *)std::data(Local_object_list);
  api->vp[12] = (int *)std::data(Server_object_list);
  api->vp[13] = (int *)&Dedicated_server;
  api->vp[14] = (int *)std::data(Player_colors);
  api->vp[15] = (int *)&Hud_aspect_x;
  api->vp[16] = (int *)&Hud_aspect_y;
  api->vp[17] = (int *)&Viewer_object;
  api->vp[18] = (int *)&Render_zoom;
  api->vp[19] = (int *)&Game_window_x;
  api->vp[20] = (int *)&Game_window_y;
  api->vp[21] = (int *)&Poly_models;
  api->vp[22] = (int *)VisEffects;
  api->vp[23] = (int *)&Highest_vis_effect_index;
  api->vp[24] = (int *)&Multi_next_level;
  api->vp[25] = (int *)&Level_info;
  api->vp[26] = (int *)GameArgs;
  api->vp[27] = (int *)std::data(Camera_view_mode);
  api->vp[28] = (int *)std::data(Object_info);

  api->osiris_functions = &Multi_d3m_osiris_funcs;
  Osiris_CreateModuleInitStruct(&Multi_d3m_osiris_funcs);
  Multi_d3m_osiris_funcs.string_table = NULL;
  Multi_d3m_osiris_funcs.string_count = 0;
  Multi_d3m_osiris_funcs.module_identifier = 0xEDF7;
  Multi_d3m_osiris_funcs.module_is_static = false;
  Multi_d3m_osiris_funcs.game_checksum = Osiris_game_checksum;
  Multi_d3m_osiris_funcs.script_identifier = Netgame.scriptname;
}
// Closes and deletes any tempfiles for the game module
void CloseGameModule(module *mod) {
  // Clear out error queue
  mod_GetLastError();
  mod_FreeModule(mod);
  if (Multi_game_dll_name[0] != '\0') {
    // Try deleting the file now!
    if (!ddio_DeleteFile(Multi_game_dll_name)) {
      mprintf(0, "Couldn't delete the tmp dll");
    }
  }
  mod->handle = NULL;
}
// this function will load up the DLL, but not get any symbols
bool InitGameModule(const char *name, module *mod) {
  char lib_name[_MAX_PATH * 2];
  char dll_name[_MAX_PATH * 2];
  char tmp_dll_name[_MAX_PATH * 2];
  // Make the hog filename
  ddio_MakePath(lib_name, Base_directory, "netgames", name, NULL);
  strcat(lib_name, ".d3m");
// Make the dll filename
#if defined(WIN32)
  snprintf(dll_name, sizeof(dll_name), "%s.dll", name);
#else
  snprintf(dll_name, sizeof(dll_name), "%s.so", name);
#endif

  // Open the hog file
  if (!cf_OpenLibrary(lib_name)) {
    ddio_MakePath(tmp_dll_name, Base_directory, "netgames", name, NULL);
    strcat(tmp_dll_name, ".d3m");
    Multi_game_dll_name[0] = '\0';
    goto loaddll;
  }
  // get a temp file name
  if (!ddio_GetTempFileName(Descent3_temp_directory, "d3m", tmp_dll_name)) {
    return false;
  }
  // Copy the DLL
  if (!cf_CopyFile(tmp_dll_name, dll_name)) {
    mprintf(0, "DLL copy failed!\n");
    return false;
  }
  strcpy(Multi_game_dll_name, tmp_dll_name);
loaddll:
  // Clear out error queue
  mod_GetLastError();
  if (!mod_LoadModule(mod, tmp_dll_name)) {
    int err = mod_GetLastError();
    mprintf(0, "You are missing the DLL %s!\n", name);
    return false;
  }
  return true;
}
// Frees the dll if its in memory
void FreeGameDLL() {
  if (!GameDLLHandle.handle)
    return;
  if (DLLGameClose)
    DLLGameClose();
  Osiris_UnloadMissionModule();
  CloseGameModule(&GameDLLHandle);
  DLLGameCall = NULL;
  DLLGameInit = NULL;
  DLLGameClose = NULL;
  DLLGetGameInfo = NULL;
}
// Loads the game dll.  Returns 1 on success, else 0 on failure
int LoadGameDLL(const char *name, int num_teams_to_use) {
  static int first = 1;
  // char lib_name[_MAX_PATH*2];
  // char dll_name[_MAX_PATH*2];
  // char tmp_dll_name[_MAX_PATH*2];
  // char dll_path_name[_MAX_PATH*2];
  // char fulldll[_MAX_PATH*2];
  // ddio_MakePath(fulldll,Base_directory,"netgames",name,NULL);
  if (GameDLLHandle.handle)
    FreeGameDLL();
  if (num_teams_to_use == -1) {
    int mint, maxt;
    if (GetDLLNumTeamInfo(name, &mint, &maxt)) {
      // multi team game
      num_teams_to_use = mint;
    } else {
      // non-team game
      num_teams_to_use = 1;
    }
  }
  mprintf(0, "Loading '%s', setting up for %d teams\n", name, num_teams_to_use);
  if (!InitGameModule(name, &GameDLLHandle))
    return 0;

  // Clear out error queue
  mod_GetLastError();
  DLLGameInit = (DLLGameInit_fp)mod_GetSymbol(&GameDLLHandle, "DLLGameInit", 12);
  if (!DLLGameInit) {
    int err = mod_GetLastError();
    mprintf(0, "Couldn't get a handle to the dll function DLLGameInit!\n");
    Int3();
    FreeGameDLL();
    return 0;
  }
  // Clear out error queue
  mod_GetLastError();
  DLLGameCall = (DLLGameCall_fp)mod_GetSymbol(&GameDLLHandle, "DLLGameCall", 8);
  if (!DLLGameCall) {
    int err = mod_GetLastError();
    mprintf(0, "Couldn't get a handle to the dll function DLLGameCall!\n");
    Int3();
    FreeGameDLL();
    return 0;
  }
  // Clear out error queue
  mod_GetLastError();
  DLLGameClose = (DLLGameClose_fp)mod_GetSymbol(&GameDLLHandle, "DLLGameClose", 0);
  if (!DLLGameClose) {
    int err = mod_GetLastError();
    mprintf(0, "Couldn't get a handle to the dll function DLLGameClose!\n");
    Int3();
    FreeGameDLL();
    return 0;
  }
  // Clear out error queue
  mod_GetLastError();
  DLLGetGameInfo = (DLLGetGameInfo_fp)mod_GetSymbol(&GameDLLHandle, "DLLGetGameInfo", 4);
  if (!DLLGetGameInfo) {
    int err = mod_GetLastError();
    mprintf(0, "Couldn't get a handle to the dll function DLLGetGameInfo!\n");
    Int3();
    FreeGameDLL();
    return 0;
  }
  if (first) {
    // Jeff: Linux for some reason dies if you try to
    // free a DLL/so on atexit, they should be freed
    // anyway during game sequencing
    // atexit (FreeGameDLL);
    first = 0;
  }
  void *api_fp;
  uint8_t ok = 1;
  api_fp = (void *)GetGameAPI;

  DLLGameInit((int *)api_fp, &ok, num_teams_to_use);
  if (!ok) {
    // The DLL said no to the load
    mprintf(0, "DLLGameInit returned false, couldn't init DLL\n");
    Int3();
    FreeGameDLL();
    return 0;
  }
  Osiris_LoadMissionModule(&GameDLLHandle, name);

  return 1;
}
// If this function is called than the DLL is to be closed, because there was an error running it
// if reason is not NULL than that is the reason why
void DLLFatalError(const char *reason) {
  mprintf(0, "============================\n");
  mprintf(0, "= DLL Fatal Error          =\n");
  mprintf(0, "============================\n");
  mprintf(0, "%s\n", (reason) ? reason : "<No Reason Given>");
  Netgame.flags |= NF_EXIT_NOW;
  Int3();
}
// The chokepoint function to call the dll function
void CallGameDLL(int eventnum, dllinfo *data) {
  if (GameDLLHandle.handle && DLLGameCall) {
    data->iRet = 0;
    DLLGameCall(eventnum, data);
  }
}
// Call this function right after a player connects to the game to see if a player is banned
bool GameDLLIsAddressBanned(network_address *addr, const char *tracker_id) {
  ASSERT(addr);
  DLLInfo.special_data = (uint8_t *)addr;
  // This used to be tracker_id, but storing a pointer as an int is a problem in 64 bit
  // and no code ever was populating the tracker id that I know of. -Kevin
  DLLInfo.iParam = 0;
  DLLInfo.iRet = 0;
  CallGameDLL(EVT_GAMECHECKBAN, &DLLInfo);
  if (DLLInfo.iRet)
    return true;
  else
    return false;
}
// Call this function to get the team that a connecting player should be placed on
//	Callsign and network address of the player MUST be filled in at this point
//	PXO id must also be set if mastertracker game
//
//	Return values:
//		-2:	GameDLL can't determine a team (user specified that they want to handle), so pick a random team
//		-1:	Dedicated Server
//		 0-4: Team
int GameDLLGetConnectingPlayersTeam(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  DLLInfo.iParam = slot;
  DLLInfo.iRet = 0;
  CallGameDLL(EVT_GAME_GET_PLAYER_TEAM, &DLLInfo);
  return DLLInfo.iRet;
}
// Call this function to get information/options from a unloaded mod
bool GetDLLGameInfo(const char *name, tDLLOptions *options) {
  module mod = {NULL};
  memset(options, 0, sizeof(tDLLOptions));
  DLLGetGameInfo_fp modGetGameInfo;
  if (!InitGameModule(name, &mod))
    return false;
  // Clear out error queue
  mod_GetLastError();
  modGetGameInfo = (DLLGetGameInfo_fp)mod_GetSymbol(&mod, "DLLGetGameInfo", 4);
  if (!modGetGameInfo) {
    int err = mod_GetLastError();
    mprintf(0, "Couldn't get a handle to the dll function DLLGetGameInfo!\n");
    Int3();
    CloseGameModule(&mod);
    return false;
  }
  modGetGameInfo(options);
  CloseGameModule(&mod);
  return true;
}
// Call this function to get the list of requirements that the given module needs in order
// to be playable.  Returns the number of requirements it needs...-1 on error.
int GetDLLRequirements(const char *name, char *requirements, int buflen) {
  ASSERT(buflen >= 0);
  ASSERT(requirements);
  tDLLOptions opt;
  if (!GetDLLGameInfo(name, &opt)) {
    mprintf(0, "Unable to get %s's requirements\n", name);
    return -1;
  }
  strncpy(requirements, opt.requirements, buflen - 1);
  requirements[buflen - 1] = '\0';
  uint32_t opt_req_len = strlen(opt.requirements);
  if (opt_req_len > strlen(requirements)) {
    // too small of a buffer!
    mprintf(0, "Too small of a buffer to fill in all requirements!...need %d\n", opt_req_len + 1);
    Int3();
    // cut off last requirement (which is shortened)
    char *p = strrchr(requirements, ',');
    if (p) {
      *p = '\0';
    } else {
      *requirements = '\0';
    }
  }
  // go through requirements and count em
  char *p = requirements;
  int count = 0;
  while (*p) {
    if (*p == ',')
      count++;
    p++;
  }
  count++;
  return count;
}
// Call this function to get information about the number of teams for the game
// Returns true if it's a team game...false if it's a non-team game.
// If it returns true, then min is filled in with the minumum number of teams needed for the game
// and max is filled in with the maximum number of teams for the game...if they are the same
// value, then it is the only number of teams supported.
bool GetDLLNumTeamInfo(const char *name, int *mint, int *maxt) {
  tDLLOptions dllo;
  if (!GetDLLGameInfo(name, &dllo)) {
    *mint = 1;
    *maxt = 1;
    return false;
  }
  if (!(dllo.flags & DOF_MAXTEAMS)) {
    *mint = 1;
    *maxt = 1;
    return false;
  }
  *maxt = (dllo.max_teams == 0 || dllo.max_teams == 1 || dllo.max_teams < 0) ? 1 : std::min(dllo.max_teams, 4);
  if ((*maxt) == 1) {
    *mint = 1;
  } else {
    *mint = 2;
  }
  if (dllo.flags & DOF_MINTEAMS && dllo.min_teams >= 0) {
    *mint = (dllo.min_teams == 0 || dllo.min_teams == 1) ? 1 : std::min(*maxt, dllo.min_teams);
  }
  return ((*maxt) == 1) ? false : true;
}
