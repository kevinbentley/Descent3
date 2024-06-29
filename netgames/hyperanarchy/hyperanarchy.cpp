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

 * $Logfile: /DescentIII/Main/hyperanarchy/hyperanarchy.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:57:56 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: hyperanarchy.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:57:56  kevinb
 * initial 1.5 import
 *
 *
 * 68    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 67    7/12/99 1:22p Jeff
 * updated for new netflags
 *
 * 66    7/11/99 6:45p Jeff
 * cleaner plr if the list is too long
 *
 * 65    5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 64    5/20/99 5:03p Jeff
 * fixed HUD display bugs
 *
 * 63    5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 62    5/12/99 11:28a Jeff
 * added sourcesafe comment block
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <string.h>
#include "gamedll_header.h"
#include "idmfc.h"
#include "HyperAnarchy.h"
#include "hyperstr.h"
IDMFC *DMFCBase = NULL;
static IDmfcStats *dstat = NULL;
static object *dObjects;
static player *dPlayers;

#define SPID_HYPERINFO 0
#define SPID_HYPERPOS 1
#define HCM_PLAYERCOLOR 0
#define HCM_NORMAL 1

struct tPlayerStat {
  int Score[2];
};

static int pack_pstat(tPlayerStat *user_info, uint8_t *data);
static int unpack_pstat(tPlayerStat *user_info, uint8_t *data);

int pack_pstat(tPlayerStat *user_info, uint8_t *data) {
  int count = 0;
  MultiAddInt(user_info->Score[0], data, &count);
  MultiAddInt(user_info->Score[1], data, &count);
  return count;
}

int unpack_pstat(tPlayerStat *user_info, uint8_t *data) {
  int count = 0;
  user_info->Score[0] = MultiGetInt(data, &count);
  user_info->Score[1] = MultiGetInt(data, &count);
  return count;
}

static int SortedPlayers[MAX_PLAYER_RECORDS];
static bool DisplayScoreScreen;
static int HyperOrbID = -1;
static int WhoHasOrb = -1;
static int KillCount = 0;
static int HyperOrbIcon = -1;
static bool DisplayFlagBlink = true;
static int WhoJustScoredTimer = -1;
static int HyperMoveTimer = -1;
static uint8_t HUD_color_model = HCM_PLAYERCOLOR;
static int Highlight_bmp = -1;
static bool display_my_welcome = false;

static void OnClientPlayerEntersGame(int player_num);

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

static void SwitchHUDColor(int i);
// handles a Hyper Anarchy Game State packet
static void ReceiveHyperGameState(uint8_t *data);
// sends a Hyper Anarchy Game State packet
static void SendHyperGameState(int playernum);
// Displays HUD scores
static void DisplayHUDScores(struct tHUDItem *hitem);
// Displays the Stats screen
static void DisplayScores(void);
// Sorts based on score
static void SortPlayerScores(int *sortedindex, int size);
// Updates the effect on all the players
static void UpdateEffect(void);
// Displays the Welcome Screen
static void DisplayWelcomeScreen(int pnum);
// Handler for menu item for turning on/off blinking hud
static void SwitchBlinkingHud(int i);
// Generates a valid random room
static int GetRandomValidRoom(void);
// Moves the HyperOrb to the center of a random room
// if objnum is -1, than the HyperOrb is created and moved
static void MoveHyperOrbToRoom(int objnum);
// Given a room the HyperOrb is created and placed in the center of it
static void CreateHyperOrbInRoom(int room);
// Given the objnum and room it will move the HyperOrb to the center of that room. Objnum better be valid.
static void MoveHyperOrbToRoomCenter(int objnum, int room);
// handles a Hyper Anarchy Object Placement packet
static void ReceiveHyperPos(uint8_t *data);
// Searches through all the objects and looks for the HyperOrb, returns it's objnum. -1 if it doesn't exist
static int FindHyperObjectNum(void);
// Searches through all the player's inventory, returns the pnum of the player who has the HyperOrb, -1
// if no one does.
static int FindHyperOrbInInventory(void);
static void ResetTimer(void);
static void SaveStatsToFile(char *filename);

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }

  tPlayerStat *stat = (tPlayerStat *)pr->user_info;

  snprintf(buffer, buffer_size, "%d[%d]", stat->Score[DSTAT_LEVEL], stat->Score[DSTAT_OVERALL]);
}

void ShowStatBitmap(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);

  if (pr && pr->state == STATE_INGAME) {
    if (WhoHasOrb == pr->pnum) {
      // draw hyper orb icon
      DLLRenderHUDQuad(x + 3, y, 10, 10, 0, 0, 1, 1, HyperOrbIcon, alpha_to_use, 0);
    }
  }
}

// Timer handlers
void OnTimer(void);
void OnTimerKill(void);
void OnTimerFlagReturn(void);
void OnTimerFlagReturnKill(void);

// This function gets called by the game when it wants to learn some info about the game
void DLLFUNCCALL DLLGetGameInfo(tDLLOptions *options) {
  options->flags = DOF_MAXTEAMS;
  options->max_teams = 1;
  strcpy(options->game_name, TXT_GAMENAME);
  strcpy(options->requirements, "");
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

  DMFCBase->Set_OnInterval(OnInterval);
  DMFCBase->Set_OnHUDInterval(OnHUDInterval);
  DMFCBase->Set_OnKeypress(OnKeypress);
  DMFCBase->Set_OnServerGameCreated(OnServerGameCreated);
  DMFCBase->Set_OnServerLevelStart(OnServerLevelStart);
  DMFCBase->Set_OnClientLevelStart(OnClientLevelStart);
  DMFCBase->Set_OnClientLevelEnd(OnClientLevelEnd);
  DMFCBase->Set_OnGameStateRequest(OnGameStateRequest);
  DMFCBase->Set_OnPlayerConnect(OnPlayerConnect);
  DMFCBase->Set_OnServerCollide(OnServerCollide);
  DMFCBase->Set_OnClientCollide(OnClientCollide);
  DMFCBase->Set_OnClientPlayerKilled(OnClientPlayerKilled);
  DMFCBase->Set_OnPLRInterval(OnPLRInterval);
  DMFCBase->Set_OnPLRInit(OnPLRInit);
  DMFCBase->Set_OnServerPlayerDisconnect(OnServerPlayerDisconnect);
  DMFCBase->Set_OnClientPlayerDisconnect(OnClientPlayerDisconnect);
  DMFCBase->Set_OnSaveStatsToFile(OnSaveStatsToFile);
  DMFCBase->Set_OnLevelEndSaveStatsToFile(OnLevelEndSaveStatsToFile);
  DMFCBase->Set_OnDisconnectSaveStatsToFile(OnDisconnectSaveStatsToFile);
  DMFCBase->Set_OnPrintScores(OnPrintScores);
  DMFCBase->Set_OnPlayerEntersObserver(OnPlayerEntersObserver);
  DMFCBase->Set_OnClientPlayerEntersGame(OnClientPlayerEntersGame);

  DLLCreateStringTable("hyper.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    *all_ok = 0;
    return;
  }

  // add the anarchy menu/submenus
  IMenuItem *lev1, *lev2, *MainMenu;
  lev1 = CreateMenuItemWArgs(TXT_GAMENAME, MIT_NORMAL, 0, NULL);

  lev2 = CreateMenuItemWArgs(TXT_HUDSCORECOLORS, MIT_STATE, 0, SwitchHUDColor);
  lev2->SetStateItemList(2, TXT_PLAYERCOLORS, TXT_NORMAL);
  lev2->SetState(HUD_color_model);
  lev1->AddSubMenu(lev2);

  MainMenu = DMFCBase->GetOnScreenMenu();
  MainMenu->AddSubMenu(lev1);

  dObjects = DMFCBase->GetObjects();
  dPlayers = DMFCBase->GetPlayers();

  DMFCBase->GameInit(1);

  // add the death and suicide messages
  DMFCBase->AddDeathMessage(TXT_DEATH1, true);
  DMFCBase->AddSuicideMessage(TXT_SUICIDE1);

  HyperOrbID = DLLFindObjectIDName("Hyperorb");
  if (HyperOrbID == -1) {
    DLLmprintf(0, "Hyper Anarchy: BIG WARNING, COULDN'T FIND HyperOrb ID...YOUR GAME IS IN JEOPARDY!\n");
    *all_ok = 0;
    return;
  }

  // setup the Playerstats struct so DMFC can handle it automatically when a new player enters the game
  DMFCBase->SetupPlayerRecord(sizeof(tPlayerStat), (int (*)(void *, uint8_t *))pack_pstat,
                              (int (*)(void *, uint8_t *))unpack_pstat);

  DMFCBase->RegisterPacketReceiver(SPID_HYPERINFO, ReceiveHyperGameState);
  DMFCBase->RegisterPacketReceiver(SPID_HYPERPOS, ReceiveHyperPos);

  DMFCBase->SetNumberOfTeams(1);
  (DMFCBase->GetNetgameInfo())->flags |= (NF_DAMAGE_FRIENDLY | NF_TRACK_RANK);

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  DisplayScoreScreen = false;
  WhoHasOrb = -1;
  KillCount = 0;
  HyperMoveTimer = -1;
  HyperOrbIcon = DLLbm_AllocLoadFileBitmap("HyperOrbICON.ogf", 0, BITMAP_FORMAT_1555);
  if (HyperOrbIcon == -1) {
    *all_ok = 0;
    return;
  }

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
  tDmfcStatsColumnInfo pl_col[7];
  char gname[20];
  strcpy(gname, TXT_STATSGAMENAME);

  tsi.flags = DSIF_SHOW_PIC | DSIF_SHOW_OBSERVERICON;
  tsi.cColumnCountDetailed = 0;
  tsi.cColumnCountPlayerList = 7;
  tsi.clbDetailedColumn = NULL;
  tsi.clbDetailedColumnBMP = NULL;
  tsi.clbPlayerColumn = DetermineScore;
  tsi.clbPlayerColumnBMP = ShowStatBitmap;
  tsi.DetailedColumns = NULL;
  tsi.GameName = gname;
  tsi.MaxNumberDisplayed = NULL;
  tsi.PlayerListColumns = pl_col;
  tsi.SortedPlayerRecords = SortedPlayers;

  pl_col[0].color_type = DSCOLOR_TEAM;
  pl_col[0].title[0] = '\0';
  pl_col[0].type = DSCOL_BMP;
  pl_col[0].width = 15;

  pl_col[1].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[1].title, TXT_PILOT);
  pl_col[1].type = DSCOL_PILOT_NAME;
  pl_col[1].width = 120;

  pl_col[2].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[2].title, TXT_SCORE);
  pl_col[2].type = DSCOL_CUSTOM;
  pl_col[2].width = 60;

  pl_col[3].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[3].title, TXT_KILLS_SHORT);
  pl_col[3].type = DSCOL_KILLS_LEVEL;
  pl_col[3].width = 57;

  pl_col[4].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[4].title, TXT_DEATHS_SHORT);
  pl_col[4].type = DSCOL_DEATHS_LEVEL;
  pl_col[4].width = 57;

  pl_col[5].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[5].title, TXT_SUICIDES_SHORT);
  pl_col[5].type = DSCOL_SUICIDES_LEVEL;
  pl_col[5].width = 57;

  pl_col[6].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[6].title, TXT_PING);
  pl_col[6].type = DSCOL_PING;
  pl_col[6].width = 40;

  dstat->Initialize(&tsi);
}

// Called when the DLL is shutdown
void DLLFUNCCALL DLLGameClose() {
  if (Highlight_bmp > BAD_BITMAP_HANDLE)
    DLLbm_FreeBitmap(Highlight_bmp);

  DLLDestroyStringTable(StringTable, StringTableSize);
  if (HyperOrbIcon > 0)
    DLLbm_FreeBitmap(HyperOrbIcon);

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

//////////////////////////////////////////////////////////////
/////// Overrides ///////////////////////////////////////////

void OnHUDInterval(void) {
  dstat->DoFrame();
  DMFCBase->DisplayOutrageLogo();

  DMFCBase->OnHUDInterval();
}

void OnInterval(void) {
  // Set a Timer to display
  if ((HyperMoveTimer == -1) && (WhoHasOrb == -1))
    HyperMoveTimer = DMFCBase->SetTimerInterval(OnTimerFlagReturn, 30.0f, 30.0f);

  SortPlayerScores(SortedPlayers, MAX_PLAYER_RECORDS);
  DMFCBase->OnInterval();
}

void OnPlayerEntersObserver(int pnum, object *piggy) {
  if (WhoHasOrb == pnum) {
    WhoHasOrb = -1;
    KillCount = 0;
    HyperMoveTimer = -1;
    DLLAddHUDMessage(TXT_LOSTORB, dPlayers[pnum].callsign);

    UpdateEffect();
  }

  DMFCBase->OnPlayerEntersObserver(pnum, piggy);
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
  player_record *pr;
  tPlayerStat *stat;
  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    pr = DMFCBase->GetPlayerRecord(i);
    if (pr)
      stat = (tPlayerStat *)pr->user_info;
    else
      stat = NULL;
    if (stat) {
      stat->Score[DSTAT_LEVEL] = 0;
      stat->Score[DSTAT_OVERALL] = 0;
    }
  }
}

void OnServerLevelStart(void) {
  // Now create a hyper orb in a random room -eek
  if (HyperOrbID != -1) {
    DLLmprintf(0, "Attempting to create HyperOrb in a random room\n");
    int room = GetRandomValidRoom();
    DLLmprintf(0, "Room %d selected\n", room);
    // We got a good room
    // Safe to create the flag
    CreateHyperOrbInRoom(room);
  }

  KillCount = 0;
  WhoHasOrb = -1;
  HyperMoveTimer = -1;
  UpdateEffect();

  DMFCBase->OnServerLevelStart();
}

void OnClientLevelEnd(void) { DMFCBase->OnClientLevelEnd(); }

// The server has started a new level, so clear out level scores
void OnClientLevelStart(void) {
  DMFCBase->OnClientLevelStart();

  player_record *pr;
  tPlayerStat *stat;
  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    pr = DMFCBase->GetPlayerRecord(i);
    if (pr)
      stat = (tPlayerStat *)pr->user_info;
    else
      stat = NULL;
    if (stat) {
      stat->Score[DSTAT_LEVEL] = 0;
    }
  }

  DMFCBase->RequestGameState();
  UpdateEffect();
}

// We need to send all the inventory info out to the new player
void OnGameStateRequest(int player_num) {
  SendHyperGameState(player_num);
  DMFCBase->OnGameStateRequest(player_num);
}

// A new player has entered the game, zero there stats out
void OnPlayerConnect(int player_num) {
  tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(player_num);
  if (stat) {
    stat->Score[DSTAT_LEVEL] = 0;
    stat->Score[DSTAT_OVERALL] = 0;
  }

  DMFCBase->OnPlayerConnect(player_num);
}

// A new player has entered the game, zero there stats out
void OnClientPlayerEntersGame(int player_num) {
  DMFCBase->OnClientPlayerEntersGame(player_num);
  if (player_num != DMFCBase->GetPlayerNum())
    DisplayWelcomeScreen(player_num);
  else
    display_my_welcome = true;
}

void OnPrintScores(int level) {
  char buffer[256];
  char name[50];
  memset(buffer, ' ', 256);

  size_t t;
  size_t pos[6];
  size_t len[6];
  pos[0] = 0;
  t = len[0] = 20; // give ample room for pilot name
  pos[1] = pos[0] + t + 1;
  t = len[1] = strlen(TXT_SCORE);
  pos[2] = pos[1] + t + 1;
  t = len[2] = strlen(TXT_KILLS);
  pos[3] = pos[2] + t + 1;
  t = len[3] = strlen(TXT_DEATHS);
  pos[4] = pos[3] + t + 1;
  t = len[4] = strlen(TXT_SUICIDES);
  pos[5] = pos[4] + t + 1;
  t = len[5] = strlen(TXT_PING);

  memcpy(&buffer[pos[0]], TXT_PILOT, strlen(TXT_PILOT));
  memcpy(&buffer[pos[1]], TXT_SCORE, len[1]);
  memcpy(&buffer[pos[2]], TXT_KILLS, len[2]);
  memcpy(&buffer[pos[3]], TXT_DEATHS, len[3]);
  memcpy(&buffer[pos[4]], TXT_SUICIDES, len[4]);
  memcpy(&buffer[pos[5]], TXT_PING, len[5]);
  buffer[pos[5] + len[5] + 1] = '\n';
  buffer[pos[5] + len[5] + 2] = '\0';
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
    if ((pr) && (pr->state != STATE_EMPTY)) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      snprintf(name, sizeof(name), "%s%s:", (pr->state == STATE_DISCONNECTED) ? "*" : "", pr->callsign);
      name[19] = '\0';

      tPlayerStat *stat = (tPlayerStat *)pr->user_info;

      memset(buffer, ' ', 256);
      t = strlen(name);
      memcpy(&buffer[pos[0]], name, (t < len[0]) ? t : len[0]);
      snprintf(name, sizeof(name), "%d[%d]", (stat) ? stat->Score[DSTAT_LEVEL] : 0,
               (stat) ? stat->Score[DSTAT_OVERALL] : 0);
      t = strlen(name);
      memcpy(&buffer[pos[1]], name, (t < len[1]) ? t : len[1]);
      snprintf(name, sizeof(name), "%d[%d]", pr->dstats.kills[DSTAT_LEVEL], pr->dstats.kills[DSTAT_OVERALL]);
      t = strlen(name);
      memcpy(&buffer[pos[2]], name, (t < len[2]) ? t : len[2]);
      snprintf(name, sizeof(name), "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL], pr->dstats.deaths[DSTAT_OVERALL]);
      t = strlen(name);
      memcpy(&buffer[pos[3]], name, (t < len[3]) ? t : len[3]);
      snprintf(name, sizeof(name), "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL], pr->dstats.suicides[DSTAT_OVERALL]);
      t = strlen(name);
      memcpy(&buffer[pos[4]], name, (t < len[4]) ? t : len[4]);

      if (pr->state == STATE_INGAME)
        snprintf(name, sizeof(name), "%.0f", (DMFCBase->GetNetPlayers())[pr->pnum].ping_time * 1000.0f);
      else
        strcpy(name, "---");
      t = strlen(name);
      memcpy(&buffer[pos[5]], name, (t < len[5]) ? t : len[5]);
      buffer[pos[5] + len[5] + 1] = '\n';
      buffer[pos[5] + len[5] + 2] = '\0';
      DPrintf(buffer);
    }
  }
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

void OnPLRInit(void) {
  int i, t, j;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    SortedPlayers[i] = i;
  }

  for (i = 1; i <= MAX_PLAYER_RECORDS - 1; i++) {
    t = SortedPlayers[i];
    // Shift elements down until
    // insertion point found.
    for (j = i - 1; j >= 0 && compare_slots(SortedPlayers[j], t); j--) {
      SortedPlayers[j + 1] = SortedPlayers[j];
    }
    // insert
    SortedPlayers[j + 1] = t;
  }

  DMFCBase->OnPLRInit();
}

void OnPLRInterval(void) {
#define PLAYERS_COL 110
#define SCORE_COL 240
#define KILLS_COL 300
#define DEATHS_COL 360
#define SUICIDES_COL 420

  DMFCBase->OnPLRInterval();

  int y = 40;
  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;

  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(PLAYERS_COL, y, TXT_PILOT);
  DLLgrtext_Printf(SCORE_COL, y, TXT_SCORE);
  DLLgrtext_Printf(KILLS_COL, y, TXT_KILLS);
  DLLgrtext_Printf(DEATHS_COL, y, TXT_DEATHS);
  DLLgrtext_Printf(SUICIDES_COL, y, TXT_SUICIDES);
  y += height;

  // print out player stats
  int rank = 1;
  int slot;
  tPlayerStat *stat;
  player_record *pr;

  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    slot = SortedPlayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      stat = (tPlayerStat *)pr->user_info;

      int pnum = DMFCBase->WasPlayerInGameAtLevelEnd(slot);
      if (pnum != -1) {
        DLLgrtext_SetColor((DMFCBase->GetPlayerColors())[pnum]);
      } else {
        DLLgrtext_SetColor(GR_RGB(128, 128, 128));
      }

      DLLgrtext_Printf(PLAYERS_COL, y, "%d)%s", rank, pr->callsign);
      DLLgrtext_Printf(SCORE_COL, y, "%d[%d]", (stat) ? stat->Score[DSTAT_LEVEL] : 0,
                       (stat) ? stat->Score[DSTAT_OVERALL] : 0);
      DLLgrtext_Printf(KILLS_COL, y, "%d[%d]", pr->dstats.kills[DSTAT_LEVEL], pr->dstats.kills[DSTAT_OVERALL]);
      DLLgrtext_Printf(DEATHS_COL, y, "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL], pr->dstats.deaths[DSTAT_OVERALL]);
      DLLgrtext_Printf(SUICIDES_COL, y, "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL], pr->dstats.suicides[DSTAT_OVERALL]);
      y += height;
      rank++;
      if (y >= 440)
        goto quick_exit;
    }
  }

quick_exit:;
}

void OnServerCollide(object *me_obj, object *it_obj) {
  if (!me_obj || !it_obj)
    return;

  if (it_obj->type != OBJ_PLAYER) {
    DMFCBase->OnServerCollide(me_obj, it_obj);
    return;
  }

  if ((me_obj->type == OBJ_PLAYER) && (DLLInvCheckItem(it_obj->id, OBJ_POWERUP, HyperOrbID))) {
    /*
    //Two Players collided...one had orb
    DLLmprintf(0,"Player2Player\n");
    DMFCBase->CallClientEvent(EVT_CLIENT_GAMECOLLIDE,DMFCBase->GetMeObjNum(),DMFCBase->GetItObjNum(),-1);
    DMFCBase->CallOnClientCollide(me_obj,it_obj);
    */
  } else if (me_obj->type == OBJ_POWERUP && me_obj->id == HyperOrbID) {
    // A Player collided with the HyperOrb
    // Sent this information to the clients to process
    DMFCBase->CallClientEvent(EVT_CLIENT_GAMECOLLIDE, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
    DMFCBase->CallOnClientCollide(me_obj, it_obj);
  }

  DMFCBase->OnServerCollide(me_obj, it_obj);
}

void OnClientCollide(object *me_objp, object *it_objp) {
  if (me_objp->type == OBJ_PLAYER) {
    // spew this puppy
    DLLPlayerSpewInventory(it_objp, false, false);
    DLLAddHUDMessage(TXT_LOSTORB, dPlayers[it_objp->id].callsign);
    WhoHasOrb = -1;
    KillCount = 0;
    HyperMoveTimer = -1;
    UpdateEffect();
  } else {
    // We'll only get here if me_objp is HyperOrb and it_objp is the collider
    WhoHasOrb = it_objp->id;
    KillCount = 0; // reset this variable, since they just picked up the HyperOrb

    // add the hyper orb to the players inventory
    DLLInvAddTypeID(it_objp->id, me_objp->type, me_objp->id, -1, -1, 0, NULL);
    // if we are the server, remove the orb from the world and tell the clients to do the same
    if (DMFCBase->GetLocalRole() == LR_SERVER) {
      DLLSetObjectDeadFlag(me_objp, true, 0);
    }

    DLLAddHUDMessage(TXT_GOTORB, dPlayers[it_objp->id].callsign);

    // Play a sound
    int id = DLLFindSoundName("PwrHyperOrb");
    if (id != -1)
      DLLPlay3dSound(id, &dObjects[dPlayers[DMFCBase->GetPlayerNum()].objnum], 1, 0);
    UpdateEffect();

    // Set a Timer to display
    if (WhoJustScoredTimer != -1)
      DMFCBase->KillTimer(WhoJustScoredTimer);
    WhoJustScoredTimer = DMFCBase->SetTimerInterval(OnTimer, 0.5f, 5.0f, OnTimerKill);
  }
  DMFCBase->OnClientCollide(me_objp, it_objp);
}

void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
  int score = 0;
  int kpnum;

  if (killer_obj) {
    if ((killer_obj->type == OBJ_PLAYER) || (killer_obj->type == OBJ_GHOST))
      kpnum = killer_obj->id;
    else if (killer_obj->type == OBJ_ROBOT || (killer_obj->type == OBJ_BUILDING && killer_obj->ai_info)) {
      // countermeasure kill
      kpnum = DMFCBase->GetCounterMeasureOwner(killer_obj);
    } else {
      kpnum = -1;
    }
  } else
    kpnum = -1;

  bool suicide = (bool)(kpnum == victim_pnum);

  if (victim_pnum == WhoHasOrb) {
    // The guy with the score orb lost it!
    KillCount++;
    if (!suicide) {
      score = KillCount + 1;
      if (score > 5)
        score = 5;
    } else {
      score = -(KillCount + 1);
      if (score < -5)
        score = -5;
    }

    WhoHasOrb = -1;
    KillCount = 0;
    HyperMoveTimer = -1;
    DLLAddHUDMessage(TXT_LOSTORB, dPlayers[victim_pnum].callsign);

    UpdateEffect();
  } else {

    if (kpnum != -1) {
      // Was the killer the guy with the HyperOrb?
      if (kpnum == WhoHasOrb) {
        // Yup!
        KillCount++;
        score = KillCount + 1;
        if (score > 5)
          score = 5;
        if (!suicide)
          DLLAddHUDMessage(TXT_SCOREPOINTS, dPlayers[kpnum].callsign, score);
      } else {
        // Nope!
        if (!suicide)
          score = 1;
        else
          score = -1;
      }
    }
  }

  tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(kpnum);

  if (kpnum != -1 && stat) {
    stat->Score[DSTAT_LEVEL] += score;
    stat->Score[DSTAT_OVERALL] += score;
  }

  if ((DMFCBase->GetLocalRole() == LR_SERVER) && (kpnum != -1) && (stat)) {
    // check the score to see if we hit the limit
    if ((DMFCBase->GetScoreLimit(&score))) {
      if (score <= stat->Score[DSTAT_LEVEL]) {
        DLLmprintf(0, "Score limit reached\n");
        DMFCBase->EndLevel();
      }
    }
  }

  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
}

void OnServerPlayerDisconnect(int player_num) {
  DMFCBase->OnServerPlayerDisconnect(player_num);
  if (player_num == WhoHasOrb) {
    // send this event to the clients so they can handle it
    DMFCBase->CallClientEvent(EVT_CLIENT_GAMEPLAYERDISCONNECT, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
    DMFCBase->CallOnClientPlayerDisconnect(player_num);
  }
}

void OnClientPlayerDisconnect(int player_num) {
  if (player_num == WhoHasOrb) {
    WhoHasOrb = -1;
    KillCount = 0;
    HyperMoveTimer = -1;
    ResetTimer();
  }
  DMFCBase->OnClientPlayerDisconnect(player_num);
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
  tPlayerStat *ps;
  int count, p;

  // sort the stats
  SortPlayerScores(sortedslots, MAX_PLAYER_RECORDS);
  count = 1;

  snprintf(buffer, sizeof(buffer), TXT_SAVESTATSA, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSB);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSC);
  DLLcf_WriteString(file, buffer);
  strcpy(buffer, "----------------------------------------------------------------------------------------------");
  DLLcf_WriteString(file, buffer);

  for (p = 0; p < MAX_PLAYER_RECORDS; p++) {
    pr = DMFCBase->GetPlayerRecord(sortedslots[p]);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      memset(buffer, ' ', BUFSIZE);

      ps = (tPlayerStat *)pr->user_info;

      snprintf(tempbuffer, sizeof(tempbuffer), "%d)", count);
      memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s%s", (pr->state == STATE_INGAME) ? "" : "*", pr->callsign);
      memcpy(&buffer[7], tempbuffer, strlen(tempbuffer));

      if (ps) {
        snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", ps->Score[DSTAT_LEVEL], ps->Score[DSTAT_OVERALL]);
        memcpy(&buffer[35], tempbuffer, strlen(tempbuffer));
      }

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.kills[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL]);
      memcpy(&buffer[47], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL],
               pr->dstats.deaths[DSTAT_OVERALL]);
      memcpy(&buffer[59], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[70], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s", DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(sortedslots[p])));
      memcpy(&buffer[81], tempbuffer, strlen(tempbuffer));

      size_t pos = 81 + strlen(tempbuffer) + 1;

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
      snprintf(buffer, sizeof(buffer), "%d) %s%s", count, (pr->state == STATE_INGAME) ? "" : "*", pr->callsign);
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
            snprintf(tempbuffer, sizeof(tempbuffer), "%s", dpr->callsign);
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

        while (DMFCBase->FindPInfoStatNext(&stat)) {
          if (stat.slot != p) {
            memset(buffer, ' ', BUFSIZE);
            dpr = DMFCBase->GetPlayerRecord(stat.slot);

            if (dpr) {
              strncpy(tempbuffer, dpr->callsign, sizeof(tempbuffer));
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
  DLLAddHUDMessage(TXT_STATSAVED);
}

#define ROOTFILENAME "Hyper"
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

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

// handles a Hyper Anarchy Game State packet
void ReceiveHyperGameState(uint8_t *data) {
  // remove all the HyperOrbs from everyone's inventory
  for (int i = 0; i < DLLMAX_PLAYERS; i++)
    DLLInvRemove(i, OBJ_POWERUP, HyperOrbID);

  int count = 0;
  WhoHasOrb = MultiGetInt(data, &count);
  KillCount = MultiGetInt(data, &count);

  if (WhoHasOrb != -1) {
    DLLmprintf(0, "%s has the score orb!\n", dPlayers[WhoHasOrb].callsign);
    DLLInvAddTypeID(WhoHasOrb, OBJ_POWERUP, HyperOrbID, -1, -1, 0, NULL);
  }
  UpdateEffect();
}

// sends a Hyper Anarchy Game State packet
void SendHyperGameState(int playernum) {
  bool updateall = false;
  int count = 0;
  uint8_t data[MAX_GAME_DATA_SIZE];
  DMFCBase->StartPacket(data, SPID_HYPERINFO, &count);

  if ((WhoHasOrb != -1) && (!DMFCBase->CheckPlayerNum(WhoHasOrb))) {
    WhoHasOrb = -1;
    KillCount = 0;
    HyperMoveTimer = -1;
    updateall = true;
  }

  MultiAddInt(WhoHasOrb, data, &count);
  MultiAddInt(KillCount, data, &count);

  DMFCBase->SendPacket(data, count, (updateall) ? SP_ALL : playernum);

  if (updateall) {
    // remove all the HyperOrbs from everyone's inventory
    for (int i = 0; i < DLLMAX_PLAYERS; i++)
      DLLInvRemove(i, OBJ_POWERUP, HyperOrbID);
    UpdateEffect();
  }
}

// Displays HUD scores
void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    DisplayWelcomeScreen(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (DisplayScoreScreen)
    return;

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX]) + 3;
  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)((DisplayScoreScreen) ? 128 : 255));
  int y = (DMFCBase->GetGameWindowH() / 2) - ((height * 5) / 2);
  int x = 510;
  int rank = 1;
  ddgr_color color = 0;
  bool hasorb;
  char temp[50];
  bool hdisp = false;

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 85.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;
  int icon_size = height - 3;
  int icon_x = name_x - 5 - icon_size;
  bool player_shown;

#define NUM_PLAYERS_TO_SHOW_PLUS_ONE 6

  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    int slot = SortedPlayers[i];
    player_record *pr = DMFCBase->GetPlayerRecord(slot);
    player_shown = false;

    if (pr && pr->state != STATE_EMPTY) {
      hasorb = false;

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      if ((pr->state == STATE_DISCONNECTED) || (pr->state == STATE_INGAME && !DMFCBase->IsPlayerObserver(pr->pnum))) {
        tPlayerStat *stat = (tPlayerStat *)pr->user_info;

        if ((rank < NUM_PLAYERS_TO_SHOW_PLUS_ONE) ||
            (pr->state == STATE_INGAME && pr->pnum == DMFCBase->GetPlayerNum()))
          player_shown = true;

        if (pr->state == STATE_INGAME && WhoHasOrb == pr->pnum) {
          hasorb = true;
          if (player_shown)
            hdisp = true;
        }

        if (((pr->state == STATE_INGAME) && (WhoHasOrb != pr->pnum)) || (DisplayFlagBlink) ||
            pr->state == STATE_DISCONNECTED) {
          strcpy(temp, pr->callsign);
          DMFCBase->ClipString(name_width, temp, true);

          if (pr->state == STATE_INGAME && pr->pnum == DMFCBase->GetPlayerNum()) {

            switch (HUD_color_model) {
            case HCM_PLAYERCOLOR:
              color = (DMFCBase->GetPlayerColors())[pr->pnum];
              break;
            case HCM_NORMAL:
              color = GR_RGB(40, 255, 40);
              break;
            };

            if (Highlight_bmp > BAD_BITMAP_HANDLE) {
              // draw the highlight bar in the background
              DLLrend_SetAlphaValue(alpha * 0.50f);
              DLLrend_SetZBufferState(0);
              DLLrend_SetTextureType(TT_LINEAR);
              DLLrend_SetLighting(LS_NONE);
              DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);

              DLLrend_DrawScaledBitmap(icon_x - 2, y - 2, score_x + score_width + 2, y + height - 1, Highlight_bmp, 0,
                                       0, 1, 1, 1.0f, -1, NULL);
              DLLrend_SetZBufferState(1);
            }

            DLLgrtext_SetAlpha(alpha);
            DLLgrtext_SetColor(color);
            DLLgrtext_Printf(name_x, y, temp);
            DLLgrtext_Printf(score_x, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);

          } else if (rank < NUM_PLAYERS_TO_SHOW_PLUS_ONE) {
            if (pr->state == STATE_DISCONNECTED) {
              color = GR_GREY;
            } else {
              switch (HUD_color_model) {
              case HCM_PLAYERCOLOR:
                color = (DMFCBase->GetPlayerColors())[pr->pnum];
                break;
              case HCM_NORMAL:
                color = GR_RGB(40, 255, 40);
                break;
              };
            }

            DLLgrtext_SetAlpha(alpha);
            DLLgrtext_SetColor(color);
            DLLgrtext_Printf(name_x, y, temp);
            DLLgrtext_Printf(score_x, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
          }
        }

        if (hasorb && DisplayFlagBlink) {
          DLLrend_SetZBufferState(0);
          DLLrend_SetTextureType(TT_LINEAR);
          DLLrend_SetAlphaValue(alpha);
          DLLrend_SetLighting(LS_NONE);
          DLLrend_SetWrapType(WT_CLAMP);
          DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);
          DLLrend_DrawScaledBitmap(icon_x, y, icon_x + icon_size, y + icon_size, HyperOrbIcon, 0, 0, 1, 1, 1.0f, -1,
                                   NULL);
          DLLrend_SetZBufferState(1);
        }

        if (player_shown)
          y += height;
        rank++;
      }
    }
  }

  if (WhoHasOrb != -1 && DisplayFlagBlink && !hdisp) {
    player_record *pr = DMFCBase->GetPlayerRecordByPnum(WhoHasOrb);
    if (pr && pr->state == STATE_INGAME) {
      // the player with the orb needs to be shown
      strcpy(temp, dPlayers[WhoHasOrb].callsign);
      DMFCBase->ClipString(name_width, temp, true);

      DLLgrtext_SetAlpha(alpha);
      DLLgrtext_SetColor(GR_RGB(40, 255, 40));
      DLLgrtext_Printf(name_x, y, temp);

      tPlayerStat *stat = (tPlayerStat *)pr->user_info;
      DLLgrtext_Printf(score_x, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);

      DLLrend_SetZBufferState(0);
      DLLrend_SetTextureType(TT_LINEAR);
      DLLrend_SetAlphaValue(alpha);
      DLLrend_SetLighting(LS_NONE);
      DLLrend_SetWrapType(WT_CLAMP);
      DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);
      DLLrend_DrawScaledBitmap(icon_x, y, icon_x + icon_size, y + icon_size, HyperOrbIcon, 0, 0, 1, 1, 1.0f, -1, NULL);
      DLLrend_SetZBufferState(1);
    }
  }

  // Display the HyperOrb in the corner if we have it
  if (DMFCBase->GetPlayerNum() == WhoHasOrb) {
    DLLrend_SetZBufferState(0);
    DLLrend_SetTextureType(TT_LINEAR);
    DLLrend_SetAlphaValue(alpha);
    DLLrend_SetLighting(LS_NONE);
    DLLrend_SetWrapType(WT_CLAMP);
    DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);
    int x1, x2, y1, y2;
    x1 = DMFCBase->GetGameWindowW() - 5 - DLLbm_w(HyperOrbIcon, 0);
    y1 = 25;
    x2 = x1 + DLLbm_w(HyperOrbIcon, 0);
    y2 = y1 + DLLbm_h(HyperOrbIcon, 0);
    DLLrend_DrawScaledBitmap(x1, y1, x2, y2, HyperOrbIcon, 0, 0, 1, 1, 1.0f, -1, NULL);
    DLLrend_SetZBufferState(1);
  }
}

// Update Effect on the guy who has the Orb
void UpdateEffect(void) {
  float redb[4];
  float greenb[4];
  float blueb[4];
  int i;

  for (i = 0; i < 4; i++) {
    redb[i] = 0.83f;
    greenb[i] = 0.17f;
    blueb[i] = 0;
  }

  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    if (DMFCBase->CheckPlayerNum(i)) {
      // Player valid
      if (i == WhoHasOrb) {
        // Do the effect on this guy
        DLLPlayerSetRotatingBall(i, 3, 4, redb, greenb, blueb);
      } else {
        // Reset effect on this guy
        DLLPlayerSetRotatingBall(i, 0, 4, NULL, NULL, NULL);
      }
    }
  }
}

// Displays the Welcome Screen
void DisplayWelcomeScreen(int player_num) {
  char name_buffer[64];
  strcpy(name_buffer, (DMFCBase->GetPlayers())[player_num].callsign);

  if (player_num == DMFCBase->GetPlayerNum()) {
    DLLAddHUDMessage(TXT_WELCOME, name_buffer);
  } else {
    DLLAddHUDMessage(TXT_JOINED, name_buffer);
  }
}

void SortPlayerScores(int *sortedindex, int size) {
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
  memcpy(sortedindex, tempsort, ((size > MAX_PLAYER_RECORDS) ? MAX_PLAYER_RECORDS : size) * sizeof(int));
}

// Generates a valid random room
int GetRandomValidRoom(void) {
  while (1) {
    int room;
    room = rand() % (DMFCBase->GetHighestRoomIndex() + 1);
    if ((!ROOMNUM_OUTSIDE(room)) && ((DMFCBase->GetRooms())[room].used)) {
      if (!((DMFCBase->GetRooms())[room].flags & RF_EXTERNAL)) {
        DLLmprintf(0, "Room %d selected\n", room);
        return room;
      }
    }
  }
}

// Moves the HyperOrb to the center of a random room
// if objnum is -1, than the HyperOrb is created and moved
void MoveHyperOrbToRoom(int objnum) {
  if ((objnum < 0) || (objnum >= MAX_OBJECTS))
    objnum = -1;
  else if (dObjects[objnum].type != OBJ_POWERUP)
    objnum = -1;

  if (objnum == -1) {
    // we need to create it and place it somewhere in the level
    CreateHyperOrbInRoom(GetRandomValidRoom());
  } else {
    // we need to just move it
    MoveHyperOrbToRoomCenter(objnum, GetRandomValidRoom());
  }
}

// Given a room the HyperOrb is created and placed in the center of it
void CreateHyperOrbInRoom(int room) {
  if (DMFCBase->GetLocalRole() != LR_SERVER)
    return;
  vector vpos;
  int objnum;
  DLLComputeRoomCenter(&vpos, &((DMFCBase->GetRooms())[room]));
  objnum = DLLObjCreate(OBJ_POWERUP, HyperOrbID, room, &vpos, NULL, OBJECT_HANDLE_NONE);
  DLLMultiSendObject(&dObjects[objnum], 0, true);
}

// Given the objnum and room it will move the HyperOrb to the center of that room. Objnum better be valid.
void MoveHyperOrbToRoomCenter(int objnum, int room) {
  vector home_pos;
  DLLComputeRoomCenter(&home_pos, &((DMFCBase->GetRooms())[room]));
  DLLObjSetPos(&dObjects[objnum], &home_pos, room, NULL, false);
  if (DMFCBase->GetLocalRole() == LR_SERVER) { // tell the clients to move
    uint8_t data[MAX_GAME_DATA_SIZE];
    int count = 0;

    DMFCBase->StartPacket(data, SPID_HYPERPOS, &count);
    MultiAddInt(room, data, &count);
    DMFCBase->SendPacket(data, count, SP_ALL);
  }
}

// handles a Hyper Anarchy Object Placement packet
void ReceiveHyperPos(uint8_t *data) {
  int count = 0;
  int room = MultiGetInt(data, &count);

  // first find the Orb's number
  int objnum = FindHyperObjectNum();
  if (objnum == -1) {
    // THIS BETTER NOT HAPPEN!!!!!!!
    Int3();
  }
  MoveHyperOrbToRoomCenter(objnum, room);
}

// Searches through all the objects and looks for the HyperOrb, returns it's objnum. -1 if it doesn't exist
int FindHyperObjectNum(void) {
  // go through all the objects until we find it
  for (int i = 0; i < MAX_OBJECTS; i++) {
    if ((dObjects[i].type == OBJ_POWERUP) && (dObjects[i].id == HyperOrbID)) {
      // we found it
      return i;
    }
  }
  return -1;
}

// Searches through all the player's inventory, returns the pnum of the player who has the HyperOrb, -1
// if no one does.
int FindHyperOrbInInventory(void) {
  // go through everyone's inventory looking for HyperOrb
  for (int pnum = 0; pnum < DLLMAX_PLAYERS; pnum++) {
    if (DMFCBase->CheckPlayerNum(pnum)) {
      if (DLLInvCheckItem(pnum, OBJ_POWERUP, HyperOrbID))
        return pnum;
    }
  }
  return -1;
}

void ResetTimer(void) {
  if (HyperMoveTimer != -1)
    DMFCBase->KillTimer(HyperMoveTimer);
  HyperMoveTimer = -1;
}

/////////////////////////////////
// Timer event handlers
void OnTimer(void) { DisplayFlagBlink = !DisplayFlagBlink; }
void OnTimerKill(void) { DisplayFlagBlink = true; }

void OnTimerFlagReturn(void) {
  if (DMFCBase->GetLocalRole() != LR_SERVER)
    return;
  if (WhoHasOrb == -1) {
    // time to return move the hyperorb home
    int objnum = FindHyperObjectNum();
    if (objnum != -1) {
      // ok, so it's in some place, lets move it home
      MoveHyperOrbToRoom(objnum);
    } else {
      // did it disappear?, check all the players inventories
      WhoHasOrb = FindHyperOrbInInventory();
      if (WhoHasOrb == -1) { // no one has it, it's missing!, create it and place it in a room
        MoveHyperOrbToRoom(-1);
      }
    }
  }
  HyperMoveTimer = -1;
}

void OnTimerFlagReturnKill(void) { HyperMoveTimer = -1; }

void SwitchHUDColor(int i) { HUD_color_model = i; }
