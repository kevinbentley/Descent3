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

 * $Logfile: /DescentIII/Main/monsterball/monsterball.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:58:29 $
 * $Author: kevinb $
 *
 * Monmsterball Multiplayer game
 *
 * $Log: monsterball.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:58:29  kevinb
 * initial 1.5 import
 *
 *
 * 43    9/24/01 3:17p Matt
 * Only show results for two teams, since there are always only two teams.
 *
 * 42    9/24/01 2:28p Matt
 * Allowed room for longer team name on results screen.
 *
 * 41    9/13/01 5:30p Matt
 * Added a team member list to the stats display.
 *
 * 40    10/21/99 2:46p Kevin
 * Macintosh merge!
 *
 * 39    8/17/99 5:53p Jeff
 * track ranks on PXO
 *
 * 38    7/15/99 1:18a Jeff
 * fixed up $scores
 *
 * 37    7/12/99 2:27p Jeff
 * fixed PLR to only display the team label for the disconnected list if
 * there are people in the list
 *
 * 36    7/11/99 6:55p Jeff
 * fixed PLR so it doesn't go off the screen on long lists and active
 * players in the game are shown first
 *
 * 35    5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 34    5/13/99 5:08p Ardussi
 * changes for compiling on the Mac
 *
 * 33    5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 32    5/12/99 11:29a Jeff
 * changed for loop variable for sanity...
 *
 * 31    5/09/99 6:20a Jeff
 * improved Entropy (added sounds, max virii per room).  Fixed rendering
 * bugs for other multiplayer dlls.
 *
 * 30    5/08/99 3:54p Jeff
 * fixed Post level results screen.  Fixed welcome messages. Fixed save
 * stats to file generation
 *
 * 29    5/08/99 5:07a Jeff
 * a little touch ups on PLR (needs work)
 *
 * 28    5/07/99 1:45p Jeff
 * don't count dedicated server in team size count
 *
 * 27    4/30/99 7:37p Jeff
 * cool effects when you score
 *
 * 26    4/28/99 4:24a Jeff
 * added safety checks to prevent crashes
 *
 * 25    4/27/99 3:44p Jeff
 * fixed requirement keywords
 *
 * 24    4/23/99 6:15p Jeff
 * fixed double calls to GameClose
 *
 * 23    4/23/99 12:43p Jeff
 * forgot to call CloseGame
 *
 * 22    4/22/99 7:15p Jeff
 * changed requirement strings
 *
 * 21    4/21/99 5:34p Jeff
 * added requirements
 *
 * 20    4/19/99 6:23p Jeff
 * Linux compile
 *
 * 19    3/31/99 5:49p Jeff
 * fixed bug of displaying icon accidently
 *
 * 18    3/27/99 4:53p Jeff
 * player rankings in multiplayer games implemented.  Fixed join message
 * so it doesn't get cut off
 *
 * 17    3/19/99 5:42p Jeff
 * high res font fixups
 *
 * 16    3/19/99 12:54p Jeff
 * base support for requesting the number of teams for a multiplayer game
 *
 * 15    3/17/99 12:23p Jeff
 * converted DMFC to be COM interface
 *
 * 14    2/11/99 6:09p Jeff
 * localized
 *
 * 13    2/11/99 12:49a Jeff
 * changed names of exported variables
 *
 * 12    2/10/99 1:48p Matt
 * Changed object handle symbolic constants
 *
 * 11    2/09/99 3:32p Jeff
 * table file parser takes quotes strings for force keywords
 *
 * 10    2/05/99 7:03p Jeff
 * table file parsing macros put in
 *
 * 9     1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 8     1/24/99 8:32p Jeff
 * a bunch of updates to get 100% up to date, added individual scoring.
 *
 * 7     1/21/99 11:16p Jeff
 * exported vecmat functions
 *
 * 6     1/20/99 8:05p Jeff
 * fixed some bugs
 *
 * 5     1/20/99 2:28p Jeff
 *
 * 4     1/19/99 9:54p Jeff
 * improvements added...very complete
 *
 * 3     1/19/99 5:34p Jeff
 * updated monsterball
 *
 * 2     1/18/99 12:06a Jeff
 * updated to get 90% of base functionality in
 *
 * $NoKeywords: $
 */

#include <cmath>

#include "gamedll_header.h"
#include "idmfc.h"
#include "monsterball.h"
#include <string.h>
#include "monsterstr.h"

#include <algorithm>

IDMFC *DMFCBase = NULL;
static IDmfcStats *dstat = NULL;
static room *dRooms;
static object *dObjects;
static player *dPlayers;
static vis_effect *dVisEffects;
//////////////////////////////////
// defines
#define SPID_NEWPLAYER 0
#define SPID_HITINFO 1

#define MONSTERBALL_ID_NAME "Monsterball"
#define MONSTERBALL_SND_SCORE "Extra life"
#define MONSTERBALL_SND_PICKUP "IGotIt"
#define MONSTERBALL_SND_HIT "Monsterball Hit"
#define MONSTERBALL_LOSE "Drop unknown "
/*
$$TABLE_SOUND "Extra life"
$$TABLE_GENERIC "Monsterball"
$$TABLE_SOUND "IGotIt"
$$TABLE_SOUND "Monsterball Hit"
$$TABLE_SOUND "Drop unknown "
*/

#define SCORE_DRAGIN 3
#define SCORE_HITIN 1

#define MAX_MONSTERBALL_VEL 120.0f

//////////////////////////////////
// Structs

struct tPlayerStat {
  int Score[2];
  int BadScore[2];
};

static int pack_pstat(tPlayerStat *user_info, uint8_t *data);
static int unpack_pstat(tPlayerStat *user_info, uint8_t *data);

int pack_pstat(tPlayerStat *user_info, uint8_t *data) {
  int count = 0;
  MultiAddInt(user_info->Score[0], data, &count);
  MultiAddInt(user_info->Score[1], data, &count);
  MultiAddInt(user_info->BadScore[0], data, &count);
  MultiAddInt(user_info->BadScore[1], data, &count);
  return count;
}

int unpack_pstat(tPlayerStat *user_info, uint8_t *data) {
  int count = 0;
  user_info->Score[0] = MultiGetInt(data, &count);
  user_info->Score[1] = MultiGetInt(data, &count);
  user_info->BadScore[0] = MultiGetInt(data, &count);
  user_info->BadScore[1] = MultiGetInt(data, &count);
  return count;
}

struct weapon_collide_info {
  vector rotvel;
  vector velocity;
  vector pos;
  matrix orient;
  float mass;
  float size;
};

struct {
  int id, room;
  int objhandle;
  int owner_handle;
  int icon;
  vector pos;
} Monsterball_info;

//////////////////////////////////
// Globals

static int SortedPLRPlayers[DLLMAX_TEAMS][MAX_PLAYER_RECORDS];
static int TeamScores[DLLMAX_TEAMS];
static int SortedTeams[DLLMAX_TEAMS];
static int SortedPlayers[MAX_PLAYER_RECORDS];

static int NumOfTeams = 2;
static int WhoJustScored = -1, WhoJustScoredTimer = -1;
static int GoalRooms[DLLMAX_TEAMS];
static int Highlight_bmp;
static int LastHitPnum = -1;

static bool players_sorted = false; // the Sorted*[] have been sorted
static bool DisplayPowerBBlink = true;
static bool DisplayScoreBlink = true;
static bool DisplayScoreScreen = false;
static bool display_my_welcome = false;
static bool monsterball_info_set = false;

///////////////////////////////////////////////
// localization info
static char **StringTable;
static int StringTableSize = 0;
static const char *_ErrorString = "Missing String";
const char *GetStringFromTable(int d) {
  if ((d < 0) || (d >= StringTableSize))
    return _ErrorString;
  else
    return StringTable[d];
}
///////////////////////////////////////////////

//////////////////////////////////
// Prototypes
static void DisplayHUDScores(struct tHUDItem *hitem);
static void DisplayStats(void);
static void GetGameStartPacket(uint8_t *data);
static void SendGameStartPacket(int pnum);
static bool GetMonsterballInfo(int id);
static void SortTeams(void);
static void DisplayWelcomeMessage(int player_num);
static void OnTimerScore(void);
static void OnTimer(void);
static void OnTimerScoreKill(void);
static void OnTimerKill(void);
static void OnTimerRegen(void);
static void OnTimerRegenKill(void);
static void SaveStatsToFile(char *filename);
static void SortPlayerSlots(int *sorted_list, int count);
static void SendLastHitInfo(void);
static void GetLastHitInfo(uint8_t *data);

static void HandlePickupPowerball(object *owner);
static void HandleLosePowerball(bool play_sound);
static void HandleMonsterballCollideWithObject(object *ball, object *player, vector *point, vector *normal);
static void HandleMonsterballCollideWithWeapon(object *ball, weapon_collide_info *winfo, vector *point, vector *normal);
static void bump_object(object *object0, vector *rotvel, vector *velocity, vector *pos, matrix *orient, float mass,
                        float size, vector *collision_point, vector *collision_normal, float rot_scale,
                        float vel_scale);
static void DoMonsterballScoreEffect(void);
static void OnClientPlayerEntersGame(int player_num);

static bool ValidateOwner(int *pnum, object **obj);

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }

  tPlayerStat *stat = (tPlayerStat *)pr->user_info;

  if (column_num == 2) {
    snprintf(buffer, buffer_size, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
  } else {
    snprintf(buffer, buffer_size, "%d", (stat) ? stat->BadScore[DSTAT_LEVEL] : 0);
  }
}

void TeamScoreCallback(int team, char *buffer, int buffer_size) {
  ASSERT(team >= 0 && team < DLLMAX_TEAMS);

  snprintf(buffer, buffer_size, " %d", TeamScores[team]);
}

void ShowStatBitmap(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);

  if (!pr || pr->state != STATE_INGAME)
    return;

  int pnum;
  object *owner;

  if (!ValidateOwner(&pnum, &owner))
    return;

  // the owner is still valid
  if (pnum == pr->pnum) {
    DLLRenderHUDQuad(x + 2, y, 10, 10, 0, 0, 1, 1, Monsterball_info.icon, alpha_to_use, 0);
  }
}

#define NUM_TEAMS 2

// This function gets called by the game when it wants to learn some info about the game
void DLLFUNCCALL DLLGetGameInfo(tDLLOptions *options) {
  options->flags = DOF_MAXTEAMS | DOF_MINTEAMS;
  options->max_teams = NUM_TEAMS;
  options->min_teams = NUM_TEAMS;
  strcpy(options->game_name, TXT_GAMENAME);
  strcpy(options->requirements, "MINGOALS2,GOALPERTEAM,SPEC1");
}

// Initializes the game function pointers
void DLLFUNCCALL DLLGameInit(int *api_func, uint8_t *all_ok, int num_teams_to_use) {
  *all_ok = 1;
  DMFCBase = CreateDMFC();
  if (!DMFCBase) {
    *all_ok = 0;
    return;
  }

  dstat = CreateDmfcStats();
  if (!dstat) {
    *all_ok = 0;
    return;
  }

  DMFCBase->LoadFunctions(api_func);

  // Setup event handlers
  DMFCBase->Set_OnCanChangeTeam(OnCanChangeTeam);
  DMFCBase->Set_OnClientPlayerDisconnect(OnClientPlayerDisconnect);
  DMFCBase->Set_OnPlayerEntersObserver(OnPlayerEntersObserver);
  DMFCBase->Set_OnClientPlayerKilled(OnClientPlayerKilled);
  DMFCBase->Set_OnServerObjectShieldsChanged(OnServerObjectShieldsChanged);
  DMFCBase->Set_OnGameStateRequest(OnGameStateRequest);
  DMFCBase->Set_OnServerGameCreated(OnServerGameCreated);
  DMFCBase->Set_OnClientLevelStart(OnClientLevelStart);
  DMFCBase->Set_OnPlayerConnect(OnPlayerConnect);
  DMFCBase->Set_OnInterval(OnInterval);
  DMFCBase->Set_OnHUDInterval(OnHUDInterval);
  DMFCBase->Set_OnKeypress(OnKeypress);
  DMFCBase->Set_OnServerCollide(OnServerCollide);
  DMFCBase->Set_OnClientCollide(OnClientCollide);
  DMFCBase->Set_OnServerPlayerChangeSegment(OnServerPlayerChangeSegment);
  DMFCBase->Set_OnClientPlayerChangeSegment(OnClientPlayerChangeSegment);
  DMFCBase->Set_OnServerObjectChangeSegment(OnServerObjectChangeSegment);
  DMFCBase->Set_OnClientObjectChangeSegment(OnClientObjectChangeSegment);
  DMFCBase->Set_OnSaveStatsToFile(OnSaveStatsToFile);
  DMFCBase->Set_OnLevelEndSaveStatsToFile(OnLevelEndSaveStatsToFile);
  DMFCBase->Set_OnDisconnectSaveStatsToFile(OnDisconnectSaveStatsToFile);
  DMFCBase->Set_OnPLRInterval(OnPLRInterval);
  DMFCBase->Set_OnPLRInit(OnPLRInit);
  DMFCBase->Set_OnPrintScores(OnPrintScores);
  DMFCBase->Set_OnClientPlayerEntersGame(OnClientPlayerEntersGame);

  // setup arrays
  dRooms = DMFCBase->GetRooms();
  dObjects = DMFCBase->GetObjects();
  dPlayers = DMFCBase->GetPlayers();
  dVisEffects = DMFCBase->GetVisEffectArray();

  netgame_info *Netgame = DMFCBase->GetNetgameInfo();
  Netgame->flags |= (NF_TRACK_RANK);

  DMFCBase->GameInit(NumOfTeams);
  DLLCreateStringTable("monster.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);

  // add the death and suicide messages
  DMFCBase->AddDeathMessage(TXT_KILLEDA, true);
  DMFCBase->AddSuicideMessage(TXT_SUICIDEA);

  // setup the Playerstats struct so DMFC can handle it automatically when a new player enters the game
  DMFCBase->SetupPlayerRecord(sizeof(tPlayerStat), (int (*)(void *, uint8_t *))pack_pstat,
                              (int (*)(void *, uint8_t *))unpack_pstat);

  // register special packet receivers
  DMFCBase->RegisterPacketReceiver(SPID_NEWPLAYER, GetGameStartPacket);
  DMFCBase->RegisterPacketReceiver(SPID_HITINFO, GetLastHitInfo);

  DMFCBase->SetNumberOfTeams(NumOfTeams);

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  Monsterball_info.icon = DLLbm_AllocLoadFileBitmap("PowerballIcon.ogf", 0, BITMAP_FORMAT_1555);
  if (Monsterball_info.icon == -1)
    Monsterball_info.icon = BAD_BITMAP_HANDLE;

  DisplayScoreScreen = false;

  // TableFileAdd("Monsterball.Gam");

  Highlight_bmp = DLLbm_AllocBitmap(32, 32, 0);
  if (Highlight_bmp > BAD_BITMAP_HANDLE) {
    uint16_t *data = DLLbm_data(Highlight_bmp, 0);
    if (!data) {
      // bail on out of here
      *all_ok = 0;
      return;
    }
    for (int x = 0; x < 32 * 32; x++) {
      data[x] = GR_RGB16(50, 50, 50) | OPAQUE_FLAG;
    }
  }

  // Initialize the Stats Manager
  // ----------------------------
  tDmfcStatsInit tsi;
  tDmfcStatsColumnInfo pl_col[8];
  char gname[20];
  strcpy(gname, TXT_STATGAMENAME);

  tsi.flags = DSIF_SHOW_PIC | DSIF_SHOW_OBSERVERICON | DSIF_SEPERATE_BY_TEAM;
  tsi.cColumnCountDetailed = 0;
  tsi.cColumnCountPlayerList = 8;
  tsi.clbDetailedColumnBMP = NULL;
  tsi.clbDetailedColumn = NULL;
  tsi.clbPlayerColumn = DetermineScore;
  tsi.clbPlayerColumnBMP = ShowStatBitmap;
  tsi.DetailedColumns = NULL;
  tsi.GameName = gname;
  tsi.MaxNumberDisplayed = NULL;
  tsi.PlayerListColumns = pl_col;
  tsi.SortedPlayerRecords = SortedPlayers;
  tsi.clTeamLine = TeamScoreCallback;

  pl_col[0].color_type = DSCOLOR_TEAM;
  pl_col[0].title[0] = '\0';
  pl_col[0].type = DSCOL_BMP;
  pl_col[0].width = 15;

  pl_col[1].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[1].title, TXT_PILOT);
  pl_col[1].type = DSCOL_PILOT_NAME;
  pl_col[1].width = 110;

  pl_col[2].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[2].title, TXT_POINTS);
  pl_col[2].type = DSCOL_CUSTOM;
  pl_col[2].width = 51;

  pl_col[3].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[3].title, TXT_BLUNDERS);
  pl_col[3].type = DSCOL_CUSTOM;
  pl_col[3].width = 64;

  pl_col[4].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[4].title, TXT_KILLSSHORT);
  pl_col[4].type = DSCOL_KILLS_LEVEL;
  pl_col[4].width = 41;

  pl_col[5].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[5].title, TXT_DEATHSSHORT);
  pl_col[5].type = DSCOL_DEATHS_LEVEL;
  pl_col[5].width = 41;

  pl_col[6].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[6].title, TXT_SUICIDESSHORT);
  pl_col[6].type = DSCOL_SUICIDES_LEVEL;
  pl_col[6].width = 41;

  pl_col[7].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[7].title, TXT_PING);
  pl_col[7].type = DSCOL_PING;
  pl_col[7].width = 40;

  dstat->Initialize(&tsi);
}

// Called when the DLL is shutdown
void DLLFUNCCALL DLLGameClose() {
  if (Monsterball_info.icon > BAD_BITMAP_HANDLE)
    DLLbm_FreeBitmap(Monsterball_info.icon);

  DLLDestroyStringTable(StringTable, StringTableSize);

  if (dstat) {
    dstat->DestroyPointer();
    dstat = NULL;
  }

  if (DMFCBase) {
    DMFCBase->GameClose();
    DMFCBase->DestroyPointer();
    DMFCBase = NULL;
  }
}

bool OnCanChangeTeam(int pnum, int newteam) {
  if (!DMFCBase->OnCanChangeTeam(pnum, newteam))
    return false;

  int p;
  if (!ValidateOwner(&p, NULL))
    return true;

  if (p == pnum)
    return false;

  return true;
}

void OnHUDInterval(void) {
  dstat->DoFrame();
  DMFCBase->DisplayOutrageLogo();

  DMFCBase->OnHUDInterval();
}

void OnInterval(void) {
  SortPlayerSlots(SortedPlayers, MAX_PLAYER_RECORDS);
  players_sorted = true;
  SortTeams();

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    // make sure velocity of the ball isn't more than MAX_MONSTERBALL_VEL
    object *ball;
    if (!DLLObjGet(Monsterball_info.objhandle, &ball)) {
      // blah!
      FatalError("MONSTERBALL IS MISSING\n");
    }

    float mag = DLLvm_GetMagnitudeFast(&ball->mtype.phys_info.velocity);
    if (mag > MAX_MONSTERBALL_VEL) {
      ball->mtype.phys_info.velocity /= mag;
      ball->mtype.phys_info.velocity *= MAX_MONSTERBALL_VEL;
    }
  }

  DMFCBase->OnInterval();
}

void OnKeypress(int key) {
  dllinfo *Data = DMFCBase->GetDLLInfoCallData();
  switch (key) {
  case K_F7:
    DisplayScoreScreen = !DisplayScoreScreen;
    DMFCBase->EnableOnScreenMenu(false);
    dstat->Enable(DisplayScoreScreen);
    break;
  case K_PAGEDOWN:
    if (DisplayScoreScreen) {
      dstat->ScrollDown();
      Data->iRet = 1;
    }
    break;
  case K_PAGEUP:
    if (DisplayScoreScreen) {
      dstat->ScrollUp();
      Data->iRet = 1;
    }
    break;
  case K_F6:
    DisplayScoreScreen = false;
    dstat->Enable(false);
    break;
  case K_ESC:
    if (DisplayScoreScreen) {
      dstat->Enable(false);
      DisplayScoreScreen = false;
      Data->iRet = 1;
    }
    break;
  }

  DMFCBase->OnKeypress(key);
}

// The server has just started, so clear out all the stats and game info
void OnServerGameCreated(void) {
  DMFCBase->OnServerGameCreated();
  tPlayerStat *stat;
  player_record *pr;
  int i;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    pr = DMFCBase->GetPlayerRecord(i);
    if (!pr)
      continue;

    stat = (tPlayerStat *)pr->user_info;
    if (stat) {
      stat->Score[DSTAT_LEVEL] = stat->Score[DSTAT_OVERALL] = 0;
      stat->BadScore[DSTAT_LEVEL] = stat->BadScore[DSTAT_OVERALL] = 0;
    }
  }

  for (i = 0; i < NumOfTeams; i++) {
    TeamScores[i] = 0;
  }
}

void OnServerCollide(object *me_obj, object *it_obj, vector *point, vector *normal) {
  if (!me_obj || !it_obj) {
    DMFCBase->OnServerCollide(me_obj, it_obj, point, normal);
    return;
  }

  // check to see if the collision was with the Monsterball
  if (me_obj->handle == Monsterball_info.objhandle) {

    LastHitPnum = -1;

    switch (it_obj->type) {
    case OBJ_PLAYER: {
      if (DMFCBase->IsPlayerAlive(it_obj->id)) {
        LastHitPnum = it_obj->id;

        // call the event on the client so they can do any physics sim
        DMFCBase->CallClientEvent(EVT_CLIENT_GAMECOLLIDE, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1, true);
        DMFCBase->CallOnClientCollide(me_obj, it_obj, point, normal);
      }
    } break;
    case OBJ_WEAPON: {
      object *parent;
      DLLGetUltimateParentForObject(&parent, it_obj);
      if (parent->type == OBJ_PLAYER) {
        LastHitPnum = parent->id;
      }

      weapon_collide_info winfo;
      winfo.rotvel.x = it_obj->mtype.phys_info.rotvel.x;
      winfo.rotvel.y = it_obj->mtype.phys_info.rotvel.y;
      winfo.rotvel.z = it_obj->mtype.phys_info.rotvel.z;
      winfo.velocity.x = it_obj->mtype.phys_info.velocity.x;
      winfo.velocity.y = it_obj->mtype.phys_info.velocity.y;
      winfo.velocity.z = it_obj->mtype.phys_info.velocity.z;
      winfo.pos.x = it_obj->pos.x;
      winfo.pos.y = it_obj->pos.y;
      winfo.pos.z = it_obj->pos.z;
      winfo.orient.fvec.x = it_obj->orient.fvec.x;
      winfo.orient.fvec.y = it_obj->orient.fvec.y;
      winfo.orient.fvec.z = it_obj->orient.fvec.z;
      winfo.orient.uvec.x = it_obj->orient.uvec.x;
      winfo.orient.uvec.y = it_obj->orient.uvec.y;
      winfo.orient.uvec.z = it_obj->orient.uvec.z;
      winfo.orient.rvec.x = it_obj->orient.rvec.x;
      winfo.orient.rvec.y = it_obj->orient.rvec.y;
      winfo.orient.rvec.z = it_obj->orient.rvec.z;
      winfo.mass = it_obj->mtype.phys_info.mass;
      winfo.size = it_obj->size;
      HandleMonsterballCollideWithWeapon(me_obj, &winfo, point, normal);
    } break;
    }
  }

  // check to see if the collision was between a player and another player, who has the powerball
  if (me_obj->type == OBJ_PLAYER && (it_obj->type == OBJ_PLAYER || it_obj->type == OBJ_WEAPON)) {
    if (it_obj->type == OBJ_PLAYER && !DMFCBase->IsPlayerAlive(it_obj->id)) {
      // the collided player isn't alive
    } else {
      int p;
      if (ValidateOwner(&p, NULL)) {
        if (p == me_obj->id) {
          // the player has the powerball
          DMFCBase->CallClientEvent(EVT_CLIENT_GAMECOLLIDE, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1, true);
          DMFCBase->CallOnClientCollide(me_obj, it_obj, point, normal);
        }
      }
    }
  }

  DMFCBase->OnServerCollide(me_obj, it_obj, point, normal);
}

void OnClientPlayerDisconnect(int player_num) {
  int p;
  if (ValidateOwner(&p, NULL)) {
    if (p == player_num) {
      HandleLosePowerball(true);
    }
  }
  DMFCBase->OnClientPlayerDisconnect(player_num);
}

void OnPlayerEntersObserver(int pnum, object *piggy) {
  int p;
  if (ValidateOwner(&p, NULL)) {
    if (p == pnum) {
      HandleLosePowerball(true);
    }
  }

  DMFCBase->OnPlayerEntersObserver(pnum, piggy);
}

void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
  int p;
  if (ValidateOwner(&p, NULL)) {
    if (p == victim_pnum) {
      HandleLosePowerball(true);
    }
  }

  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
}

void HandleLosePowerball(bool play_sound) {
  static int sound = -1;

  object *owner;
  if (!ValidateOwner(NULL, &owner))
    return;

  object *ball;
  if (!DLLObjGet(Monsterball_info.objhandle, &ball)) {
    // blah!
    FatalError("MONSTERBALL IS MISSING\n");
  }

  if (play_sound) {
    if (sound == -1)
      sound = DLLFindSoundName(IGNORE_TABLE(MONSTERBALL_LOSE));
    if (sound != -1)
      DLLPlay2dSound(sound, 1);
  }

  if (DMFCBase->GetLocalRole() == LR_SERVER)
    DLLUnattachFromParent(ball);

  Monsterball_info.owner_handle = OBJECT_HANDLE_NONE;
}

void HandlePickupPowerball(object *owner) {
  static int sound = -1;

  if (sound == -1)
    sound = DLLFindSoundName(IGNORE_TABLE(MONSTERBALL_SND_PICKUP));
  if (sound != -1)
    DLLPlay2dSound(sound, MAX_GAME_VOLUME / 2);

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    // if it was a player, attach the ball to the player
    object *bobj;
    if (!DLLObjGet(Monsterball_info.objhandle, &bobj)) {
      FatalError("Monster Ball not found\n");
    }

    bool ret = DLLAttachObject(owner, 0, bobj, 0, true);
    if (!ret) {
      // blah!
      mprintf(0, "COULDN'T ATTACH MONSTERBALL TO PLAYER!!!!!!\n");
    }
  }

  Monsterball_info.owner_handle = owner->handle;
}

void OnClientCollide(object *me_obj, object *it_obj, vector *point, vector *normal) {
  // three things can happen in here
  // 1) The collision is between the ball (with no owner) and a player
  // 2) The collision is between the owner and another player or weapon
  // 3) The collision is between the ball and a robot

  if (me_obj && me_obj->type == OBJ_PLAYER) {
    // case 2: me_obj = owner
    // Result: The owner is to lose the monsterball
    HandleLosePowerball(true);
    DMFCBase->OnClientCollide(me_obj, it_obj, point, normal);
    return;
  }

  if (me_obj && me_obj->type == OBJ_ROBOT) {

    if (it_obj->type == OBJ_ROBOT) {
      // case 3: me_obj = monsterball it_obj = robot
      if (DMFCBase->GetLocalRole() == LR_SERVER) {
        // do the physics on the Monsterball
        HandleMonsterballCollideWithObject(me_obj, it_obj, point, normal);
      }
    }

    if (it_obj->type == OBJ_PLAYER) {
      // case 1: me_obj = monsterball it_obj = player
      // Result: The player is to pickup the monsterball (as long as it has no owner)
      int p = 0;
      if (!ValidateOwner(&p, NULL) && p != it_obj->id) {
        ASSERT(it_obj->type == OBJ_PLAYER);
        // HandlePickupPowerball(it_obj);
        HandleMonsterballCollideWithObject(me_obj, it_obj, point, normal);
      }
    }

    DMFCBase->OnClientCollide(me_obj, it_obj, point, normal);
    return;
  }

  DMFCBase->OnClientCollide(me_obj, it_obj, point, normal);
}

void OnServerObjectShieldsChanged(object *obj, float amount) {
  if (!obj)
    return;
  if (obj->handle == Monsterball_info.objhandle) {
    obj->shields += amount;
  }
}

void OnServerObjectChangeSegment(object *obj, int newseg, int oldseg) {
  if (!obj) {
    DMFCBase->OnServerObjectChangeSegment(obj, newseg, oldseg);
    return;
  }

  if (obj->type == OBJ_ROBOT && obj->handle == Monsterball_info.objhandle) {
    // this is the monster ball, see if it's going into a goal room
    bool is_goal = false;
    for (int i = 0; i < NumOfTeams; i++) {
      if (newseg == GoalRooms[i]) {
        is_goal = true;
        break;
      }
    }

    if (is_goal && !ValidateOwner(NULL, NULL)) {
      // it's a team goal
      SendLastHitInfo();
      DMFCBase->CallClientEvent(EVT_CLIENT_GAMEOBJCHANGESEG, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1,
                                true);
      DMFCBase->CallOnClientObjectChangeSegment(obj, newseg, oldseg);
    }
  }

  DMFCBase->OnServerObjectChangeSegment(obj, newseg, oldseg);
}

void OnClientObjectChangeSegment(object *obj, int newseg, int oldseg) {
  static int sound = -1;

  if (!obj) {
    DMFCBase->OnClientObjectChangeSegment(obj, newseg, oldseg);
    FatalError("INVALID OBJECT PASSED INTO OnClientObjectChangeSegment()");
    return;
  }
  int team = -1;

  for (int i = 0; i < NumOfTeams; i++) {
    if (newseg == GoalRooms[i]) {
      team = i;
      break;
    }
  }

  if (team < 0 || team >= NumOfTeams) {
    FatalError("NOT A GOAL ROOM\n");
    return;
  }

  if (sound == -1)
    sound = DLLFindSoundName(IGNORE_TABLE(MONSTERBALL_SND_SCORE));
  if (sound != -1)
    DLLPlay2dSound(sound, MAX_GAME_VOLUME * 0.66f);

  DoMonsterballScoreEffect();

  DLLvm_MakeVectorZero(&obj->mtype.phys_info.velocity);
  DLLvm_MakeIdentity(&obj->orient);
  DLLObjSetPos(obj, &Monsterball_info.pos, Monsterball_info.room, NULL, false);

  if (!DMFCBase->CheckPlayerNum(LastHitPnum)) {
    if (SCORE_HITIN == 1) {
      DLLAddHUDMessage(TXT_SCOREONE, DMFCBase->GetTeamString(team));
    } else {
      DLLAddHUDMessage(TXT_SCOREMULTI, DMFCBase->GetTeamString(team), SCORE_HITIN);
    }
  } else {
    int last_hit_team = dPlayers[LastHitPnum].team;
    char *callsign = dPlayers[LastHitPnum].callsign;
    tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(LastHitPnum);

    if (last_hit_team != team) {
      // he scored for the other team!!!

      if (SCORE_HITIN == 1) {
        DLLAddHUDMessage(TXT_BLUNDERSCORE, callsign, DMFCBase->GetTeamString(team));
      } else {
        DLLAddHUDMessage(TXT_BLUNDERMULTISCORE, callsign, SCORE_HITIN, DMFCBase->GetTeamString(team));
      }

      if (stat) {
        stat->BadScore[DSTAT_LEVEL]++;
        stat->BadScore[DSTAT_OVERALL]++;
      }
    } else {
      // good score!
      if (SCORE_HITIN == 1) {
        DLLAddHUDMessage(TXT_PLAYERSCORE, callsign, DMFCBase->GetTeamString(team));
      } else {
        DLLAddHUDMessage(TXT_PLAYERMULTISCORE, callsign, DMFCBase->GetTeamString(team), SCORE_HITIN);
      }

      if (stat) {
        stat->Score[DSTAT_LEVEL]++;
        stat->Score[DSTAT_OVERALL]++;
      }
    }
  }

  TeamScores[team] += SCORE_HITIN;

  // do killgoal check
  int goal;
  if ((DMFCBase->GetScoreLimit(&goal)) && (DMFCBase->GetLocalRole() == LR_SERVER)) {
    if (TeamScores[team] >= goal)
      DMFCBase->EndLevel();
  }

  // Set a Timer to display
  if (WhoJustScoredTimer != -1)
    DMFCBase->KillTimer(WhoJustScoredTimer);
  WhoJustScoredTimer = DMFCBase->SetTimerInterval(OnTimerScore, 0.5f, 5.0f, OnTimerScoreKill);
  WhoJustScored = team;

  DMFCBase->OnClientObjectChangeSegment(obj, newseg, oldseg);
}

void OnServerPlayerChangeSegment(int player_num, int newseg, int oldseg) {
  if (player_num == -1)
    return;
  if (newseg == GoalRooms[DMFCBase->GetPlayerTeam(player_num)]) {
    // check to see if a player dragged the ball into the goal
    int p;
    if (ValidateOwner(&p, NULL)) {
      // a player currently has the monsterball
      if (p == player_num) {
        // it's this player
        DMFCBase->CallClientEvent(EVT_CLIENT_GAMEPLAYERCHANGESEG, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
        DMFCBase->CallOnClientPlayerChangeSegment(player_num, newseg, oldseg);
      }
    }
  }
  DMFCBase->OnServerPlayerChangeSegment(player_num, newseg, oldseg);
}

void OnClientPlayerChangeSegment(int player_num, int newseg, int oldseg) {
  // If we get here, than a player dragged the powerball into their goal
  static int sound = -1;
  object *bobj;
  int p;

  // if we got here than the player with the Monsterball has entered his team's goal!

  if (DMFCBase->IsPlayerDedicatedServer(player_num))
    return; // dedicated server

  if (!ValidateOwner(&p, NULL)) {
    return;
  }
  if (p != player_num)
    return;

  HandleLosePowerball(false);

  if (!DLLObjGet(Monsterball_info.objhandle, &bobj)) {
    FatalError("MonsterBall Is Missing!\n");
  }

  DLLObjSetPos(bobj, &Monsterball_info.pos, Monsterball_info.room, NULL, false);

  if (SCORE_DRAGIN == 1)
    DLLAddHUDMessage(TXT_SCOREONE, DMFCBase->GetTeamString(dPlayers[player_num].team));
  else
    DLLAddHUDMessage(TXT_SCOREMULTI, DMFCBase->GetTeamString(dPlayers[player_num].team), SCORE_DRAGIN);

  TeamScores[dPlayers[player_num].team] += SCORE_DRAGIN;

  if (sound == -1)
    sound = DLLFindSoundName(IGNORE_TABLE(MONSTERBALL_SND_SCORE));
  if (sound != -1)
    DLLPlay2dSound(sound, MAX_GAME_VOLUME / 2);

  // do killgoal check
  int goal;
  if ((DMFCBase->GetScoreLimit(&goal)) && (DMFCBase->GetLocalRole() == LR_SERVER)) {
    if (TeamScores[dPlayers[player_num].team] >= goal)
      DMFCBase->EndLevel();
  }

  // Set a Timer to display
  if (WhoJustScoredTimer != -1)
    DMFCBase->KillTimer(WhoJustScoredTimer);
  WhoJustScoredTimer = DMFCBase->SetTimerInterval(OnTimerScore, 0.5f, 5.0f, OnTimerScoreKill);
  WhoJustScored = dPlayers[player_num].team;
}

// The server has started a new level, so clear out any scores needed to be reset
void OnClientLevelStart(void) {
  DMFCBase->OnClientLevelStart();

  tPlayerStat *stat;
  int i;
  player_record *pr;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    pr = DMFCBase->GetPlayerRecord(i);
    if (pr)
      stat = (tPlayerStat *)pr->user_info;
    else
      stat = NULL;
    if (stat) {
      stat->Score[DSTAT_LEVEL] = 0;
      stat->BadScore[DSTAT_LEVEL] = 0;
    }
  }

  for (i = 0; i < NumOfTeams; i++) {
    TeamScores[i] = 0;
    GoalRooms[i] = DLLGetGoalRoomForTeam(i);
  }
  LastHitPnum = -1;

  DLLMultiPaintGoalRooms(NULL);

  DLLmprintf(0, "Getting Monsterball info\n");
  if (!GetMonsterballInfo(DLLFindObjectIDName(IGNORE_TABLE(MONSTERBALL_ID_NAME)))) {
    FatalError("Error finding Monsterball room\n");
  }

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    int objnum = DLLObjCreate(OBJ_ROBOT, Monsterball_info.id, Monsterball_info.room, &Monsterball_info.pos, NULL,
                              OBJECT_HANDLE_NONE);
    if (objnum == -1)
      FatalError("Unable to create Monsterball");

    dObjects[objnum].mtype.phys_info.rotdrag = 5.0f;

    DLLMultiSendObject(&dObjects[objnum], 1, true);
    Monsterball_info.objhandle = dObjects[objnum].handle;
    Monsterball_info.owner_handle = OBJECT_HANDLE_NONE;
    monsterball_info_set = true;
  } else {
    DMFCBase->RequestGameState();
  }
  players_sorted = false;
}

// A New Player has entered the game, so we want to send him a game status packet that
// has information about the game
void OnGameStateRequest(int player_num) {
  SendGameStartPacket(player_num);
  DMFCBase->OnGameStateRequest(player_num);
}

// A new player has entered the game, zero their stats out
void OnPlayerConnect(int player_num) {
  tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(player_num);
  if (stat) {
    stat->Score[DSTAT_LEVEL] = 0;
    stat->Score[DSTAT_OVERALL] = 0;
    stat->BadScore[DSTAT_LEVEL] = 0;
    stat->BadScore[DSTAT_OVERALL] = 0;
  }

  DMFCBase->OnPlayerConnect(player_num);
}

// A new player has entered the game, zero there stats out
void OnClientPlayerEntersGame(int player_num) {
  DMFCBase->OnClientPlayerEntersGame(player_num);
  if (player_num != DMFCBase->GetPlayerNum())
    DisplayWelcomeMessage(player_num);
  else
    display_my_welcome = true;
}

bool compare_slots(int a, int b) {
  int ascore, bscore;
  player_record *apr, *bpr;
  tPlayerStat *astat, *bstat;

  apr = DMFCBase->GetPlayerRecord(a);
  bpr = DMFCBase->GetPlayerRecord(b);
  if (!apr)
    return true;
  if (!bpr)
    return false;
  if (apr->state == STATE_EMPTY)
    return true;
  if (bpr->state == STATE_EMPTY)
    return false;
  astat = (tPlayerStat *)apr->user_info;
  bstat = (tPlayerStat *)bpr->user_info;

  if ((apr->state == STATE_INGAME) && (bpr->state == STATE_INGAME)) {
    // both players were in the game
    ascore = (astat) ? astat->Score[DSTAT_LEVEL] : 0;
    bscore = (bstat) ? bstat->Score[DSTAT_LEVEL] : 0;
    return (ascore < bscore);
  }
  if ((apr->state == STATE_INGAME) && (bpr->state == STATE_DISCONNECTED)) {
    // apr gets priority since he was in the game on exit
    return false;
  }
  if ((apr->state == STATE_DISCONNECTED) && (bpr->state == STATE_INGAME)) {
    // bpr gets priority since he was in the game on exit
    return true;
  }
  // if we got here then both players were disconnected
  ascore = (astat) ? astat->Score[DSTAT_LEVEL] : 0;
  bscore = (bstat) ? bstat->Score[DSTAT_LEVEL] : 0;
  return (ascore < bscore);
}

void SortPlayerSlots(int *sorted_list, int count) {
  int tempsort[MAX_PLAYER_RECORDS];
  int i, t, j;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    tempsort[i] = i;
  }

  for (i = 1; i <= MAX_PLAYER_RECORDS - 1; i++) {
    t = tempsort[i];
    // Shift elements down until
    // insertion point found.
    for (j = i - 1; j >= 0 && compare_slots(tempsort[j], t); j--) {
      tempsort[j + 1] = tempsort[j];
    }
    // insert
    tempsort[j + 1] = t;
  }

  // copy the array over
  memcpy(sorted_list, tempsort, count * sizeof(int));
}

void OnPLRInit(void) {
  monsterball_info_set = false; // for the next level

  SortPlayerSlots(SortedPlayers, MAX_PLAYER_RECORDS);

  // Now fill in the final structure of sorted names
  int TeamCount[DLLMAX_TEAMS];
  player_record *pr;
  int team, i;

  for (i = 0; i < DLLMAX_TEAMS; i++)
    TeamCount[i] = 0;
  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    int slot = SortedPlayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    if (pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      team = (pr->state == STATE_INGAME) ? dPlayers[pr->pnum].team : pr->team;

      if (team >= NumOfTeams)
        team = 0;
      SortedPLRPlayers[team][TeamCount[team]] = slot;
      TeamCount[team]++;
    }
  }
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    if (TeamCount[i] < MAX_PLAYER_RECORDS)
      SortedPLRPlayers[i][TeamCount[i]] = -1;
  }

  DMFCBase->OnPLRInit();
}

void OnPLRInterval(void) {
  DMFCBase->OnPLRInterval();

  int TeamCol = 35;
  int NameCol = 190;
  int PointCol = 280;
  int BlunderCol = 340;
  int KillsCol = 410;
  int DeathsCol = 450;
  int SuicidesCol = 490;
  int y = 40;
  int slot;
  player_record *pr;
  tPlayerStat *stat;

  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);
  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(NameCol, y, TXT_PILOT);
  DLLgrtext_Printf(PointCol, y, TXT_POINTS);
  DLLgrtext_Printf(BlunderCol, y, TXT_BLUNDERS);
  DLLgrtext_Printf(KillsCol, y, TXT_KILLSSHORT);
  DLLgrtext_Printf(DeathsCol, y, TXT_DEATHSSHORT);
  DLLgrtext_Printf(SuicidesCol, y, TXT_SUICIDESSHORT);
  y += height;
  bool has_members;
  bool doing_connected = true;
do_disconnected_folk:

  for (int team = 0; team < NUM_TEAMS; team++) {
    // process this team
    bool show_team_label;
    show_team_label = false;

    if (!doing_connected) {
      int temp_idx;
      temp_idx = 0;

      while (SortedPLRPlayers[team][temp_idx] != -1) {
        int pnum = DMFCBase->WasPlayerInGameAtLevelEnd(SortedPLRPlayers[team][temp_idx]);
        if (pnum == -1) {
          show_team_label = true;
          break;
        }
        temp_idx++;
      }
    } else {
      show_team_label = true;
    }

    if (show_team_label) {
      // is there anyone on this team?
      DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));
      DLLgrtext_Printf(TeamCol, y, TXT_HUDDISPLAY, DMFCBase->GetTeamString(team), TeamScores[team]);
    }
    has_members = false;

    for (int index = 0; index < MAX_PLAYER_RECORDS; index++) {
      // get the player num
      slot = SortedPLRPlayers[team][index];
      if (slot == -1) // we are done with this team
        break;

      pr = DMFCBase->GetPlayerRecord(slot);
      if (pr && pr->state != STATE_EMPTY) {

        if (DMFCBase->IsPlayerDedicatedServer(pr))
          continue; // skip dedicated server

        int pnum = DMFCBase->WasPlayerInGameAtLevelEnd(slot);

        if ((doing_connected && pnum == -1) || (!doing_connected && pnum != -1))
          continue; // we're not handling them right now

        if (pnum != -1) {
          DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));
        } else {
          DLLgrtext_SetColor(GR_RGB(128, 128, 128));
        }

        char tempbuffer[40];
        strcpy(tempbuffer, pr->callsign);
        DMFCBase->ClipString(PointCol - NameCol - 10, tempbuffer, true);

        // valid player
        stat = (tPlayerStat *)pr->user_info;
        DLLgrtext_Printf(NameCol, y, "%s", tempbuffer);
        DLLgrtext_Printf(PointCol, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
        DLLgrtext_Printf(BlunderCol, y, "%d", (stat) ? stat->BadScore[DSTAT_LEVEL] : 0);
        DLLgrtext_Printf(KillsCol, y, "%d", pr->dstats.kills[DSTAT_LEVEL]);
        DLLgrtext_Printf(DeathsCol, y, "%d", pr->dstats.deaths[DSTAT_LEVEL]);
        DLLgrtext_Printf(SuicidesCol, y, "%d", pr->dstats.suicides[DSTAT_LEVEL]);
        y += height;
        has_members = true;

        if (y >= 440)
          goto quick_exit;
      }
    } // end for
    // on to the next team

    if (!has_members)
      y += height; // on to the next line

    if (y >= 440)
      goto quick_exit;
  } // end for

  if (doing_connected) {
    doing_connected = false;
    goto do_disconnected_folk;
  }

quick_exit:;
}

void OnPrintScores(int level) {
  char buffer[256];
  char name[50];
  size_t t;
  size_t pos[7];
  size_t len[7];

  for (int i = 0; i < NumOfTeams; i++) {
    snprintf(buffer, sizeof(buffer), "%s:%d\n", DMFCBase->GetTeamString(i), TeamScores[i]);
    DPrintf(buffer);
  }

  memset(buffer, ' ', 256);
  pos[0] = 0;
  t = len[0] = 20; // give ample room for pilot name
  pos[1] = pos[0] + t + 1;
  t = len[1] = strlen(TXT_POINTS);
  pos[2] = pos[1] + t + 1;
  t = len[2] = strlen(TXT_BLUNDERS);
  pos[3] = pos[1] + t + 1;
  t = len[3] = strlen(TXT_KILLS);
  pos[4] = pos[2] + t + 1;
  t = len[4] = strlen(TXT_DEATHS);
  pos[5] = pos[3] + t + 1;
  t = len[5] = strlen(TXT_SUICIDES);
  pos[6] = pos[4] + t + 1;
  t = len[6] = strlen(TXT_PING);

  memcpy(&buffer[pos[0]], TXT_PILOT, strlen(TXT_PILOT));
  memcpy(&buffer[pos[1]], TXT_POINTS, len[1]);
  memcpy(&buffer[pos[2]], TXT_BLUNDERS, len[2]);
  memcpy(&buffer[pos[3]], TXT_KILLS, len[3]);
  memcpy(&buffer[pos[4]], TXT_DEATHS, len[4]);
  memcpy(&buffer[pos[5]], TXT_SUICIDES, len[5]);
  memcpy(&buffer[pos[6]], TXT_PING, len[6]);
  buffer[pos[6] + len[6] + 1] = '\n';
  buffer[pos[6] + len[6] + 2] = '\0';
  DPrintf(buffer);

  int slot;
  player_record *pr;
  int pcount;

  if (level < 0 || level >= MAX_PLAYER_RECORDS)
    pcount = MAX_PLAYER_RECORDS;
  else
    pcount = level;

  int sortedplayers[MAX_PLAYER_RECORDS];
  DMFCBase->GetSortedPlayerSlots(sortedplayers, MAX_PLAYER_RECORDS);

  for (int i = 0; i < pcount; i++) {
    slot = sortedplayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    tPlayerStat *stat;
    if ((pr) && (pr->state != STATE_EMPTY)) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      snprintf(name, sizeof(name), "%s%s:", (pr->state == STATE_DISCONNECTED) ? "*" : "", pr->callsign);
      name[19] = '\0';

      stat = (tPlayerStat *)pr->user_info;

      memset(buffer, ' ', 256);
      t = strlen(name);
      memcpy(&buffer[pos[0]], name, (t < len[0]) ? t : len[0]);
      snprintf(name, sizeof(name), "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
      t = strlen(name);
      memcpy(&buffer[pos[1]], name, (t < len[1]) ? t : len[1]);
      snprintf(name, sizeof(name), "%d", (stat) ? stat->BadScore[DSTAT_LEVEL] : 0);
      t = strlen(name);
      memcpy(&buffer[pos[2]], name, (t < len[2]) ? t : len[2]);
      snprintf(name, sizeof(name), "%d", pr->dstats.kills[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[3]], name, (t < len[2]) ? t : len[3]);
      snprintf(name, sizeof(name), "%d", pr->dstats.deaths[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[4]], name, (t < len[3]) ? t : len[4]);
      snprintf(name, sizeof(name), "%d", pr->dstats.suicides[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[5]], name, (t < len[4]) ? t : len[5]);

      if (pr->state == STATE_INGAME)
        snprintf(name, sizeof(name), "%.0f", (DMFCBase->GetNetPlayers())[pr->pnum].ping_time * 1000.0f);
      else
        strcpy(name, "---");
      t = strlen(name);
      memcpy(&buffer[pos[6]], name, (t < len[6]) ? t : len[6]);
      buffer[pos[6] + len[6] + 1] = '\n';
      buffer[pos[6] + len[6] + 2] = '\0';
      DPrintf(buffer);
    }
  }
}

void SaveStatsToFile(char *filename) {
  CFILE *file;
  DLLOpenCFILE(&file, filename, "wt");
  if (!file) {
    DLLmprintf(0, "Unable to open output file\n");
    return;
  }

// write out game stats
#define BUFSIZE 150
  char buffer[BUFSIZE];
  char tempbuffer[25];
  int sortedslots[MAX_PLAYER_RECORDS];
  player_record *pr, *dpr;
  tPInfoStat stat;
  int count, p;
  tPlayerStat *st;

  // sort the stats
  DMFCBase->GetSortedPlayerSlots(sortedslots, MAX_PLAYER_RECORDS);
  SortTeams();
  count = 1;

  snprintf(buffer, sizeof(buffer), TXT_SAVESTATSA, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  for (p = 0; p < NumOfTeams; p++) {
    int team_i = SortedTeams[p];
    memset(buffer, ' ', BUFSIZE);
    snprintf(tempbuffer, sizeof(tempbuffer), TXT_SAVESTATSTEAM, DMFCBase->GetTeamString(team_i));
    memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));
    snprintf(tempbuffer, sizeof(tempbuffer), "[%d]", TeamScores[team_i]);
    memcpy(&buffer[20], tempbuffer, strlen(tempbuffer));
    buffer[20 + strlen(tempbuffer)] = '\0';
    DLLcf_WriteString(file, buffer);
  }

  // Write team members
  DLLcf_WriteString(file, ""); // blank line
  for (int t = 0; t < NumOfTeams; t++) {
    int team_i = SortedTeams[t];

    snprintf(buffer, sizeof(buffer), TXT_SAVESTATSTEAM, DMFCBase->GetTeamString(team_i));
    strncat(buffer, ":", sizeof(buffer) - strlen(buffer) - 1);
    DLLcf_WriteString(file, buffer);

    for (p = 0; p < MAX_PLAYER_RECORDS; p++) {
      pr = DMFCBase->GetPlayerRecord(sortedslots[p]);
      if (pr && pr->state != STATE_EMPTY) {

        if (DMFCBase->IsPlayerDedicatedServer(pr))
          continue; // skip dedicated server

        if (pr->team == team_i) { // Check if current team
          snprintf(buffer, sizeof(buffer), "  %s", pr->callsign);
          DLLcf_WriteString(file, buffer);
        }
      }
    }
  }
  DLLcf_WriteString(file, ""); // blank line

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSB);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSC);
  DLLcf_WriteString(file, buffer);
  strcpy(buffer, "--------------------------------------------------------------------------------------");
  DLLcf_WriteString(file, buffer);

  for (p = 0; p < MAX_PLAYER_RECORDS; p++) {
    pr = DMFCBase->GetPlayerRecord(sortedslots[p]);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      st = (tPlayerStat *)pr->user_info;
      memset(buffer, ' ', BUFSIZE);

      snprintf(tempbuffer, sizeof(tempbuffer), "%d)", count);
      memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s%s", (pr->state == STATE_INGAME) ? "" : "*", pr->callsign);
      memcpy(&buffer[5], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", (st) ? st->Score[DSTAT_LEVEL] : 0,
               (st) ? st->Score[DSTAT_OVERALL] : 0);
      memcpy(&buffer[34], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", (st) ? st->BadScore[DSTAT_LEVEL] : 0,
               (st) ? st->BadScore[DSTAT_OVERALL] : 0);
      memcpy(&buffer[42], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.kills[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL]);
      memcpy(&buffer[55], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL],
               pr->dstats.deaths[DSTAT_OVERALL]);
      memcpy(&buffer[67], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[78], tempbuffer, strlen(tempbuffer));

      size_t pos = 78 + strlen(tempbuffer) + 1;
      if (pos < BUFSIZE)
        buffer[pos] = '\0';

      buffer[BUFSIZE - 1] = '\0';
      DLLcf_WriteString(file, buffer);
      count++;
    }
  }

  DLLcf_WriteString(file, TXT_SAVESTATSD);

  count = 1;
  for (p = 0; p < MAX_PLAYER_RECORDS; p++) {
    pr = DMFCBase->GetPlayerRecord(p);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      // Write out header
      snprintf(buffer, sizeof(buffer), "%d) %s%s (%s)", count, (pr->state == STATE_INGAME) ? "" : "*", pr->callsign,
               DMFCBase->GetTeamString(pr->team));
      DLLcf_WriteString(file, buffer);
      size_t length = strlen(buffer);
      memset(buffer, '=', length);
      buffer[length] = '\0';
      DLLcf_WriteString(file, buffer);

      // time in game
      snprintf(buffer, sizeof(buffer), TXT_TIMEINGAME, DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(p)));
      DLLcf_WriteString(file, buffer);

      if (DMFCBase->FindPInfoStatFirst(p, &stat)) {
        snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSE);
        DLLcf_WriteString(file, buffer);

        if (stat.slot != p) {
          memset(buffer, ' ', BUFSIZE);
          dpr = DMFCBase->GetPlayerRecord(stat.slot);

          if (dpr) {
            strncpy(tempbuffer, DMFCBase->GetTeamString(dpr->team), sizeof(tempbuffer));
            memcpy(buffer, tempbuffer, strlen(tempbuffer));

            strcpy(tempbuffer, dpr->callsign);
            memcpy(&buffer[6], tempbuffer, strlen(tempbuffer));

            snprintf(tempbuffer, sizeof(tempbuffer), "%d", stat.kills);
            memcpy(&buffer[36], tempbuffer, strlen(tempbuffer));

            snprintf(tempbuffer, sizeof(tempbuffer), "%d", stat.deaths);
            memcpy(&buffer[46], tempbuffer, strlen(tempbuffer));

            size_t pos = 46 + strlen(tempbuffer) + 1;
            if (pos < BUFSIZE)
              buffer[pos] = '\0';

            buffer[BUFSIZE - 1] = '\0';
            DLLcf_WriteString(file, buffer);
          }
        }

        while (DMFCBase->FindPInfoStatNext(&stat)) {
          if (stat.slot != p) {
            memset(buffer, ' ', BUFSIZE);
            dpr = DMFCBase->GetPlayerRecord(stat.slot);
            if (dpr) {
              strcpy(tempbuffer, dpr->callsign);
              memcpy(buffer, tempbuffer, strlen(tempbuffer));

              snprintf(tempbuffer, sizeof(tempbuffer), "%d", stat.kills);
              memcpy(&buffer[30], tempbuffer, strlen(tempbuffer));

              snprintf(tempbuffer, sizeof(tempbuffer), "%d", stat.deaths);
              memcpy(&buffer[40], tempbuffer, strlen(tempbuffer));

              size_t pos = 40 + strlen(tempbuffer) + 1;
              if (pos < BUFSIZE)
                buffer[pos] = '\0';

              buffer[BUFSIZE - 1] = '\0';
              DLLcf_WriteString(file, buffer);
            }
          }
        }
      }
      DMFCBase->FindPInfoStatClose();
      DLLcf_WriteString(file, ""); // skip a line
      count++;
    }
  }

  // done writing stats
  DLLcfclose(file);
  DLLAddHUDMessage(TXT_STATSSAVED);
}

#define ROOTFILENAME "MonsterBall"
void OnSaveStatsToFile(void) {
  char filename[256];
  DMFCBase->GenerateStatFilename(filename, ROOTFILENAME, false);
  SaveStatsToFile(filename);
}

void OnLevelEndSaveStatsToFile(void) {
  char filename[256];
  DMFCBase->GenerateStatFilename(filename, ROOTFILENAME, true);
  SaveStatsToFile(filename);
}

void OnDisconnectSaveStatsToFile(void) {
  char filename[256];
  DMFCBase->GenerateStatFilename(filename, ROOTFILENAME, false);
  SaveStatsToFile(filename);
}

//////////////////////////////////////////////
// NON-DMFC Functions
//////////////////////////////////////////////
void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    DisplayWelcomeMessage(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (!monsterball_info_set || !players_sorted ||
      DisplayScoreScreen) // interval hasn't been called yet or we are display the stats
    return;

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX]) + 3;
  int y, x, team, p;

  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)255);

  if (!ValidateOwner(&p, NULL)) {
    p = -1;
  }

  y = (DMFCBase->GetGameWindowH() / 2) - ((height * 2) / 2);
  x = 510;

  team = DMFCBase->GetMyTeam();
  DLLRenderHUDText(DMFCBase->GetTeamColor(team), 255, 0, x, 0, TXT_SAVESTATSTEAM, DMFCBase->GetTeamString(team));

  int powerteam = -1;
  if (p != -1)
    powerteam = DMFCBase->GetPlayerTeam(p);

  int myteam = DMFCBase->GetMyTeam();
  int team_count;

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 100.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;
  int icon_size = height - 3;
  int icon_x = name_x - icon_size - 3;
  DLLgrtext_SetAlpha(alpha);
  char name[256];

  for (int i = 0; i < NumOfTeams; i++) {
    team = SortedTeams[i];

    if ((WhoJustScored != team) || (DisplayScoreBlink)) {
      if (team == myteam && Highlight_bmp > BAD_BITMAP_HANDLE) {
        // draw the highlite bar in the background
        DLLrend_SetAlphaValue(alpha * 0.50f);
        DLLrend_SetZBufferState(0);
        DLLrend_SetTextureType(TT_LINEAR);
        DLLrend_SetLighting(LS_NONE);
        DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);
        DLLrend_DrawScaledBitmap(name_x - 2, y - 2, score_x + score_width + 2, y + height - 1, Highlight_bmp, 0, 0, 1,
                                 1, 1.0, -1, NULL);
        DLLrend_SetZBufferState(1);
      }

      team_count = 0;
      for (int q = 0; q < DLLMAX_PLAYERS; q++) {
        if (DMFCBase->CheckPlayerNum(q) && dPlayers[q].team == team && !DMFCBase->IsPlayerDedicatedServer(q))
          team_count++;
      }

      DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));

      snprintf(name, sizeof(name), TXT_HUDSCORE, team_count, DMFCBase->GetTeamString(team));
      DMFCBase->ClipString(name_width, name, true);

      DLLgrtext_Printf(name_x, y, name);
      DLLgrtext_Printf(score_x, y, "[%d]", TeamScores[team]);
    }
    y += height;
  }
}

void GetLastHitInfo(uint8_t *data) {
  int size = 0;

  LastHitPnum = (int8_t)MultiGetByte(data, &size);
}
void SendLastHitInfo(void) {
  int size = 0;
  uint8_t data[MAX_GAME_DATA_SIZE];

  DMFCBase->StartPacket(data, SPID_HITINFO, &size);

  MultiAddByte(LastHitPnum, data, &size);

  DMFCBase->SendPacket(data, size, SP_ALL);
}

void GetGameStartPacket(uint8_t *data) {
  int i, count = 0;

  // team scores
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    TeamScores[i] = MultiGetInt(data, &count);
  }

  // who has the Monsterball
  int8_t temp;
  temp = (int8_t)MultiGetByte(data, &count);
  if (temp == -1) {
    Monsterball_info.owner_handle = OBJECT_HANDLE_NONE;
  } else {
    if (DMFCBase->CheckPlayerNum(temp))
      Monsterball_info.owner_handle = dObjects[dPlayers[temp].objnum].handle;
    else
      Monsterball_info.owner_handle = OBJECT_HANDLE_NONE;
  }

  monsterball_info_set = true;

  temp = (int8_t)MultiGetByte(data, &count);
  NumOfTeams = temp;

  // we need to find the objnum of the Monsterball...its there somewhere
  DLLmprintf(0, "Looking for Monsterball in level\n");
  int objnum = -1;

  for (i = 0; i < MAX_OBJECTS; i++) {
    if ((dObjects[i].type == OBJ_ROBOT) && (dObjects[i].id == Monsterball_info.id)) {
      // here it is
      objnum = i;
      break;
    }
  }
  DLLmprintf(0, "Monsterball %s\n", (objnum == -1) ? "Not Found" : "Found");
  if (objnum == -1) {
    FatalError("Couldn't Find Monsterball when it should be there");
  }

  Monsterball_info.objhandle = dObjects[objnum].handle;
}

void SendGameStartPacket(int pnum) {
  int i, count = 0;
  uint8_t data[MAX_GAME_DATA_SIZE];

  DMFCBase->StartPacket(data, SPID_NEWPLAYER, &count);

  // add the team scores
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    MultiAddInt(TeamScores[i], data, &count);
  }

  int8_t temp;
  int p;

  // who has the Monsterball if anyone
  if (ValidateOwner(&p, NULL)) {
    temp = p;
  } else {
    temp = -1;
  }
  MultiAddByte(temp, data, &count);

  // number of teams
  temp = NumOfTeams;
  MultiAddByte(temp, data, &count);

  // we're done
  DLLmprintf(0, "Sending Game State to %s\n", dPlayers[pnum].callsign);
  DMFCBase->SendPacket(data, count, pnum);
}

bool GetMonsterballInfo(int id) {
  if (id == -1)
    return false;

  Monsterball_info.id = id;

  // find the room with the RF_SPECIAL1
  for (int i = 0; i <= DMFCBase->GetHighestRoomIndex(); i++) {
    if (dRooms[i].flags & RF_SPECIAL1) {
      // here's the Monsterball!
      Monsterball_info.room = i;
      DLLComputeRoomCenter(&Monsterball_info.pos, &dRooms[i]);
      return true;
    }
  }
  return false;
}

#define compGT(a, b) (a < b)
// insert sort
void SortTeams(void) {
  int t;
  int i, j;

  // copy scores into scoreinfo array
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    SortedTeams[i] = i;
  }

  for (i = 1; i <= DLLMAX_TEAMS - 1; i++) {
    t = SortedTeams[i];

    // Shift elements down until
    // insertion point found.
    for (j = i - 1; j >= 0 && compGT(TeamScores[SortedTeams[j]], TeamScores[t]); j--) {
      SortedTeams[j + 1] = SortedTeams[j];
    }

    // insert
    SortedTeams[j + 1] = t;
  }
}

void DisplayWelcomeMessage(int player_num) {
  char name_buffer[64];
  strcpy(name_buffer, (DMFCBase->GetPlayers())[player_num].callsign);

  if (player_num == DMFCBase->GetPlayerNum()) {
    int team = DMFCBase->GetMyTeam();
    if (team == -1)
      return;

    DLLAddHUDMessage(TXT_WELCOME, name_buffer);
    DLLAddColoredHUDMessage(DMFCBase->GetTeamColor(team), TXT_ONTEAM, DMFCBase->GetTeamString(team));
  } else {
    int team = dPlayers[player_num].team;
    if (team == -1)
      return;

    DLLAddColoredHUDMessage(DMFCBase->GetTeamColor(team), TXT_JOINED, name_buffer, DMFCBase->GetTeamString(team));
  }
}

void OnTimerScore(void) { DisplayScoreBlink = !DisplayScoreBlink; }
void OnTimerScoreKill(void) {
  DisplayScoreBlink = true;
  WhoJustScored = WhoJustScoredTimer = -1;
}

// -------------------------------------------------------------------------

void HandleMonsterballCollideWithObject(object *ball, object *player, vector *point, vector *normal) {
  static int sound = -1;
  if (sound == -1)
    sound = DLLFindSoundName(IGNORE_TABLE(MONSTERBALL_SND_HIT));
  if (sound != -1)
    DLLPlay3dSound(sound, ball, MAX_GAME_VOLUME / 3, 0);

  // bump_object(ball,&player->mtype.phys_info.rotvel,&player->mtype.phys_info.velocity,
  //	&player->pos, &player->orient, player->mtype.phys_info.mass, player->size,point,normal,1.0f,1.0f);
}

void HandleMonsterballCollideWithWeapon(object *ball, weapon_collide_info *winfo, vector *point, vector *normal) {
  static int sound = -1;
  if (sound == -1)
    sound = DLLFindSoundName(IGNORE_TABLE(MONSTERBALL_SND_HIT));
  if (sound != -1)
    DLLPlay3dSound(sound, ball, 0, 0); // FIXME: volume was set to 0 here, is that right?

  bump_object(ball, &winfo->rotvel, &winfo->velocity, &winfo->pos, &winfo->orient, winfo->mass, winfo->size, point,
              normal, -0.3f, 5.0f);
}

void bump_object(object *object0, vector *rotvel, vector *velocity, vector *pos, matrix *orient, float mass, float size,
                 vector *collision_point, vector *collision_normal, float rot_scalar, float vel_scalar) {
  object *t = NULL;
  object *other = NULL;

  ASSERT(std::isfinite(rotvel->x));
  ASSERT(std::isfinite(rotvel->y));
  ASSERT(std::isfinite(rotvel->z));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(velocity->x));
  ASSERT(std::isfinite(velocity->y));
  ASSERT(std::isfinite(velocity->z));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.z));

  vector r1 = *collision_point - object0->pos;
  vector r2 = *collision_point - (*pos);
  vector w1;
  vector w2;
  vector n1;
  vector n2;
  float temp1;
  float temp2;

  float j;

  matrix o_t1 = object0->orient;
  matrix o_t2 = *orient;

  DLLvm_TransposeMatrix(&o_t1);
  DLLvm_TransposeMatrix(&o_t2);

  vector cmp1 = object0->mtype.phys_info.rotvel * o_t1;
  vector cmp2 = (*rotvel) * o_t2;

  DLLConvertEulerToAxisAmount(&cmp1, &n1, &temp1);
  DLLConvertEulerToAxisAmount(&cmp2, &n2, &temp2);

  n1 *= temp1;
  n2 *= temp2;

  if (temp1 != 0.0f) {
    DLLvm_CrossProduct(&w1, &n1, &r1);
  } else {
    w1.x = 0;
    w1.y = 0;
    w1.z = 0;
  }

  if (temp2 != 0.0f) {
    DLLvm_CrossProduct(&w2, &n2, &r2);
  } else {
    w2.x = 0;
    w2.y = 0;
    w2.z = 0;
  }

  vector p1 = object0->mtype.phys_info.velocity + w1;
  vector p2 = (*velocity) + w2;
  float v_rel;

  float m1 = object0->mtype.phys_info.mass;
  float m2 = mass;

  ASSERT(m1 != 0.0f && m2 != 0.0f);

  v_rel = *collision_normal * (p1 - p2);

  float e;
  e = vel_scalar;

  vector c1;
  vector c2;
  vector cc1;
  vector cc2;
  float cv1;
  float cv2;

  float i1 = (2.0f / 5.0f) * m1 * object0->size * object0->size;
  float i2 = (2.0f / 5.0f) * m2 * size;

  if (i1 < .0000001)
    i1 = .0000001f;
  if (i2 < .0000001)
    i2 = .0000001f;

  DLLvm_CrossProduct(&c1, &r1, collision_normal);
  DLLvm_CrossProduct(&c2, &r2, collision_normal);

  c1 = c1 / i1;
  c2 = c2 / i2;

  DLLvm_CrossProduct(&cc1, &c1, &r1);
  DLLvm_CrossProduct(&cc2, &c2, &r2);

  cv1 = (*collision_normal) * c1;
  cv2 = (*collision_normal) * c2;

  j = (-(1.0f + e)) * v_rel;
  j /= (1 / m1 + 1 / m2 + cv1 + cv2);

  // apply the force to the player
  vector new_vel;
  new_vel = ((j * (*collision_normal)) / m1);

  // make sure the velocity falls within a valid range
  float mag = DLLvm_GetMagnitudeFast(&new_vel);

  new_vel /= mag;

  mag = std::clamp(mag, 10.0f, 20.0f);

  new_vel *= mag;

  object0->mtype.phys_info.velocity += new_vel;

  vector jcn = j * (*collision_normal);

  DLLvm_CrossProduct(&c1, &r1, &jcn);

  n1 = (c1) / i1;

  temp1 = DLLvm_NormalizeVector(&n1);

  vector txx1;
  DLLConvertAxisAmountToEuler(&n1, &temp1, &txx1);

  float rotscale1;
  rotscale1 = rot_scalar;

  // change the player's rotational velocity
  object0->mtype.phys_info.rotvel += (txx1 * object0->orient) * rotscale1;

  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.z));
}

bool ValidateOwner(int *pnum, object **obj) {
  if (Monsterball_info.owner_handle == OBJECT_HANDLE_NONE)
    return false;

  object *owner;
  if (!DLLObjGet(Monsterball_info.owner_handle, &owner)) {
    // the object no longer exists
    Monsterball_info.owner_handle = OBJECT_HANDLE_NONE;
    return false;
  }

  if (owner->type != OBJ_PLAYER || (dPlayers[owner->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
    // the owner isn't a player playing
    Monsterball_info.owner_handle = OBJECT_HANDLE_NONE;
    return false;
  }

  if (pnum)
    *pnum = owner->id;
  if (obj)
    *obj = owner;
  return true;
}

void DoMonsterballScoreEffect(void) {
  object *Monsterball;
  if (!DLLObjGet(Monsterball_info.objhandle, &Monsterball))
    return;

  vector start_pos, end_pos;
  int start_room, end_room;
  bool doing_start = false;

  vector m_pos, i_pos;
  int m_room, i_room;

  m_pos = Monsterball->pos;
  m_room = Monsterball->roomnum;
  i_pos = Monsterball_info.pos;
  i_room = Monsterball_info.room;

  //////////////////////////////////////
  float lifetime = 4.0f;
  float thickness = 17.5f;
  float slidetime = 0.3f;
  uint16_t color = GR_RGB16(30, 255, 30);
  int numtiles = 1;
  bool autotile = true;
  int sat_count = 2;
  int texture_id = DLLFindTextureName("ThickLineLightning");
  //////////////////////////////////////

  for (int q = 0; q < 2; q++) {
    ////////////////////////////////
    vector check_pos;
    fvi_query fq;
    fvi_info hit_data;
    int hit_type;

    fq.p0 = (doing_start) ? &m_pos : &i_pos;
    fq.p1 = &check_pos;
    fq.startroom = (doing_start) ? m_room : i_room;
    fq.rad = 3.0f;
    fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
    fq.thisobjnum = Monsterball - dObjects;
    fq.ignore_obj_list = NULL;

    // find top of room
    check_pos = (doing_start) ? m_pos : i_pos;
    check_pos.y *= 50000;
    hit_type = DLLfvi_FindIntersection(&fq, &hit_data, false);

    if (hit_type == HIT_NONE)
      return;

    start_room = hit_data.hit_room;
    start_pos = hit_data.hit_pnt;

    check_pos = (doing_start) ? m_pos : i_pos;
    check_pos.y *= -50000;
    hit_type = DLLfvi_FindIntersection(&fq, &hit_data, false);

    if (hit_type == HIT_NONE)
      return;

    end_room = hit_data.hit_room;
    end_pos = hit_data.hit_pnt;

    int visnum = DLLVisEffectCreate(VIS_FIREBALL, THICK_LIGHTNING_INDEX, start_room, &start_pos);
    if (visnum >= 0) {
      vis_effect *vis = &dVisEffects[visnum];
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;
      vis->end_pos = end_pos;

      vis->custom_handle = texture_id;

      vis->lighting_color = color;
      vis->billboard_info.width = thickness;
      vis->billboard_info.texture = autotile;
      vis->velocity.x = sat_count;
      vis->velocity.y = slidetime;
      vis->velocity.z = numtiles;

      vis->flags = VF_USES_LIFELEFT | VF_WINDSHIELD_EFFECT | VF_LINK_TO_VIEWER | VF_EXPAND;
      vis->size = DLLvm_VectorDistanceQuick(&vis->pos, &vis->end_pos);
    }

    color = GR_RGB16(100, 255, 150);
    visnum = DLLVisEffectCreate(VIS_FIREBALL, SUN_CORONA_INDEX, start_room, &start_pos);
    if (visnum >= 0) {
      vis_effect *vis = &dVisEffects[visnum];
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;

      vis->lighting_color = color;

      vis->flags = VF_USES_LIFELEFT | VF_WINDSHIELD_EFFECT | VF_LINK_TO_VIEWER;
      vis->size = 4;
    }
    visnum = DLLVisEffectCreate(VIS_FIREBALL, SUN_CORONA_INDEX, end_room, &end_pos);
    if (visnum >= 0) {
      vis_effect *vis = &dVisEffects[visnum];
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;

      vis->lighting_color = color;

      vis->flags = VF_USES_LIFELEFT | VF_WINDSHIELD_EFFECT | VF_LINK_TO_VIEWER;
      vis->size = 4;
    }

    DLLCreateRandomSparks(rand() % 200 + 50, (doing_start) ? &m_pos : &i_pos, (doing_start) ? m_room : i_room,
                          HOT_SPARK_INDEX, (rand() % 3) + 2);

    doing_start = !doing_start;
  }

  if (Monsterball->effect_info) {
    Monsterball->effect_info->type_flags &= ~EF_CLOAKED;
    Monsterball->effect_info->type_flags |= EF_FADING_IN;
    Monsterball->effect_info->fade_time = 4.0f;
    Monsterball->effect_info->cloak_time = 0;
    Monsterball->effect_info->fade_max_time = 4.0f;
  }
}
