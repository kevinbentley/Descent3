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

 * $Logfile: /DescentIII/Main/hoard/hoard.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:57:53 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: hoard.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:57:53  kevinb
 * initial 1.5 import
 *
 *
 * 91    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 90    8/11/99 6:37p Jeff
 * added input command for min count to score
 *
 * 89    7/12/99 1:22p Jeff
 * updated for new netflags
 *
 * 88    7/12/99 1:16p Jeff
 * fixed bug when a player dies they sometimes pickup their orb
 *
 * 87    7/11/99 6:44p Jeff
 * cleaner plr if the list is too long
 *
 * 86    5/23/99 3:08a Jeff
 * fixed stats display
 *
 * 85    5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 84    5/20/99 9:40p Jeff
 * fixed hardlock for a client just joining the game if someone has a
 * hoard orb
 *
 * 83    5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 82    5/12/99 11:28a Jeff
 * added sourcesafe comment block
 *
 * $NoKeywords: $
 */

#include "gamedll_header.h"
#include <string.h>
#include "idmfc.h"
#include "Hoard.h"
#include "hoardstr.h"
#include "hoardaux.h"

#include <algorithm>

IDMFC *DMFCBase = NULL;
static IDmfcStats *dstat = NULL;
static IMenuItem *OSMenuSave = NULL;
static object *dObjects = NULL;
static player *dPlayers = NULL;

#define SPID_INVINFO 1 // packet for hoard inventory info
#define SPID_GAMECONFIG 2

#define HOARD_CONFIG_DLG 1234
#define HCM_PLAYERCOLOR 0
#define HCM_NORMAL 1

struct tPlayerStat {
  int Score[2];
  int HighestScore[2];
};
static int pack_pstat(tPlayerStat *user_info, uint8_t *data);
static int unpack_pstat(tPlayerStat *user_info, uint8_t *data);
int pack_pstat(tPlayerStat *user_info, uint8_t *data) {
  int count = 0;
  MultiAddInt(user_info->Score[0], data, &count);
  MultiAddInt(user_info->Score[1], data, &count);
  MultiAddInt(user_info->HighestScore[0], data, &count);
  MultiAddInt(user_info->HighestScore[1], data, &count);
  return count;
}

int unpack_pstat(tPlayerStat *user_info, uint8_t *data) {
  int count = 0;
  user_info->Score[0] = MultiGetInt(data, &count);
  user_info->Score[1] = MultiGetInt(data, &count);
  user_info->HighestScore[0] = MultiGetInt(data, &count);
  user_info->HighestScore[1] = MultiGetInt(data, &count);
  return count;
}

static tGameConfig config;

static int SortedPlayers[MAX_PLAYER_RECORDS]; // sorted player nums
static bool DisplayScoreScreen;
static int HoardID = 0;
static int HoardOrbIcon = BAD_BITMAP_HANDLE;
static bool DisplayBlink = true;
static int WhoJustScored = -1;
static int WhoJustScoredTimer = -1;
static uint8_t HUD_color_model = HCM_PLAYERCOLOR;
static int Highlight_bmp = -1;
static bool display_my_welcome = false;

static void OnTimer(void);
static void OnTimerKill(void);
static void DisplayWelcomeMessage(int player_num);
static void DisplayHUDScores(struct tHUDItem *hitem);
static void SortPlayerScores(int *sortedindex, int size);
static void DisplayWelcomeMessage(int player_num);
static void DoBallsEffect(int i, int count);
static void ReceiveHoardInv(uint8_t *data);
static void SendHoardInv(int playernum);
static void SaveStatsToFile(char *filename);
static void ReceiveGameConfig(uint8_t *data);
static void OnClientPlayerEntersGame(int player_num);

static bool Config_displayed = false;

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

// This function gets called by the game when it wants to learn some info about the game
void DLLFUNCCALL DLLGetGameInfo(tDLLOptions *options) {
  options->flags = DOF_MAXTEAMS;
  options->max_teams = 1;
  strcpy(options->game_name, TXT_GAMENAME);
  strcpy(options->requirements, "MINGOALS1");
}

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }
  tPlayerStat *stat = (tPlayerStat *)pr->user_info;

  if (column_num == 2) {
    // Score
    snprintf(buffer, buffer_size, "%d[%d]", stat->Score[DSTAT_LEVEL], stat->Score[DSTAT_OVERALL]);
  } else {
    // Highest Score
    snprintf(buffer, buffer_size, "%d[%d]", stat->HighestScore[DSTAT_LEVEL], stat->HighestScore[DSTAT_OVERALL]);
  }
}

void ShowStatBitmap(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  float ratio = DEFAULT_HUD_WIDTH / ((float)DMFCBase->GetGameWindowW());

  if (pr && pr->state == STATE_INGAME) {
    DLLRenderHUDText(GR_GREY, alpha_to_use, 0, x, y, "%d", DLLInvGetTypeIDCount(pr->pnum, OBJ_POWERUP, HoardID));
    x += (ratio * ((float)DLLgrtext_GetTextLineWidth("12"))) + 1;
    DLLRenderHUDQuad(x, y, 10, 10, 0, 0, 1, 1, HoardOrbIcon, alpha_to_use, 0);
  }
}

// We import these from DMFC
bool StringParseNumber(const char *string, int *number, const char **newpos);
bool StringParseWord(const char *string, char *word, int size, const char **newpos);
/*
bool StringParseWord(const char *string,char *word,int size,const char **newpos)
{
        *newpos = string;
        word[0] = '\0';

        //get through all the whitespace
        while( *string && *string==' ') string++;
        if(!(*string)){
                //nothing is left in the string
                *newpos = string;
                return false;
        }

        //we're at the beginning of a word
        while( *string && *string!=' '){
                if(size>1){
                        *word = *string;
                        size--;
                }

                word++;
                string++;
        }

        //tack on an ending \0
        *word = '\0';

        *newpos = string;
        return true;
}

bool StringParseNumber(const char *string,int *number,const char **newpos)
{
        char temp[10];
        bool ret = StringParseWord(string,temp,10,newpos);
        if(!ret){
                *number = 0;
                return false;
        }

        *number = atoi(temp);
        return true;
}
*/
void DMFCInputCommand_MinCount(const char *input_string) {
  if (DMFCBase->GetLocalRole() != LR_SERVER)
    return;
  if (!DMFCBase->IAmDedicatedServer())
    return;

  char s[20];

  // parse "$mincount"
  if (!StringParseWord(input_string, s, 20, &input_string)) {
    DMFCBase->DisplayInputCommandHelp("mincount");
    return;
  }

  // parse count
  int count;
  if (!StringParseNumber(input_string, &count, &input_string)) {
    DMFCBase->DisplayInputCommandHelp("mincount");
    return;
  }

  if (count < 1)
    count = 1;
  if (count > 12)
    count = 12;

  config.min_hoard = count;
  DLLAddHUDMessage("Hoard Orb Score Minimum Count Set To %d", count);
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
  DMFCBase->Set_OnInterval(OnInterval);
  DMFCBase->Set_OnHUDInterval(OnHUDInterval);
  DMFCBase->Set_OnKeypress(OnKeypress);
  DMFCBase->Set_OnServerGameCreated(OnServerGameCreated);
  DMFCBase->Set_OnClientLevelStart(OnClientLevelStart);
  DMFCBase->Set_OnClientLevelEnd(OnClientLevelEnd);
  DMFCBase->Set_OnGameStateRequest(OnGameStateRequest);
  DMFCBase->Set_OnPlayerConnect(OnPlayerConnect);
  DMFCBase->Set_OnServerPlayerChangeSegment(OnServerPlayerChangeSegment);
  DMFCBase->Set_OnClientPlayerChangeSegment(OnClientPlayerChangeSegment);
  DMFCBase->Set_OnServerCollide(OnServerCollide);
  DMFCBase->Set_OnClientCollide(OnClientCollide);
  DMFCBase->Set_OnClientPlayerKilled(OnClientPlayerKilled);
  DMFCBase->Set_OnPLRInterval(OnPLRInterval);
  DMFCBase->Set_OnPrintScores(OnPrintScores);
  DMFCBase->Set_OnPLRInit(OnPLRInit);
  DMFCBase->Set_OnSaveStatsToFile(OnSaveStatsToFile);
  DMFCBase->Set_OnClientShowUI(OnClientShowUI);
  DMFCBase->Set_OnDisconnectSaveStatsToFile(OnDisconnectSaveStatsToFile);
  DMFCBase->Set_OnLevelEndSaveStatsToFile(OnLevelEndSaveStatsToFile);
  DMFCBase->Set_OnClientPlayerEntersGame(OnClientPlayerEntersGame);

  // Setup arrays for easier to read code
  dObjects = DMFCBase->GetObjects();
  dPlayers = DMFCBase->GetPlayers();

  DLLCreateStringTable("Hoard.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    *all_ok = 0;
    return;
  }

  // setup default config
  config.min_hoard = 1;

  if (DMFCBase->AddInputCommand("mincount",
                                "[Dedicated Server Only]\nSets the minimum number of hoard orbs needed to score.\n",
                                DMFCInputCommand_MinCount, true) < 1)
    mprintf(0, "Hoard Warning: Error Adding Input Command\n");

  HoardGameInit(1);

  // add the death and suicide messages
  DMFCBase->AddDeathMessage(TXT_DEATH1, true);
  DMFCBase->AddDeathMessage(TXT_DEATH2, true);
  DMFCBase->AddDeathMessage(TXT_DEATH3, false);
  DMFCBase->AddDeathMessage(TXT_DEATH4, false);
  DMFCBase->AddDeathMessage(TXT_DEATH5, true);
  DMFCBase->AddDeathMessage(TXT_DEATH6, true);
  DMFCBase->AddDeathMessage(TXT_DEATH7, false);
  DMFCBase->AddDeathMessage(TXT_DEATH8, true);
  DMFCBase->AddDeathMessage(TXT_DEATH9, true);
  DMFCBase->AddDeathMessage(TXT_DEATH10, true);

  DMFCBase->AddSuicideMessage(TXT_SUICIDE1);
  DMFCBase->AddSuicideMessage(TXT_SUICIDE2);
  DMFCBase->AddSuicideMessage(TXT_SUICIDE3);
  DMFCBase->AddSuicideMessage(TXT_SUICIDE4);
  DMFCBase->AddSuicideMessage(TXT_SUICIDE5);
  DMFCBase->AddSuicideMessage(TXT_SUICIDE6);

  HoardID = DLLFindObjectIDName("Hoardorb");
  if (HoardID == -1) {
    DLLmprintf(0, "HOARD: BIG WARNING, COULDN'T FIND HOARD ORB ID...YOUR GAME IS IN JEOPARDY!\n");
    *all_ok = 0;
    return;
  }

  DMFCBase->SetupPlayerRecord(sizeof(tPlayerStat), (int (*)(void *, uint8_t *))pack_pstat,
                              (int (*)(void *, uint8_t *))unpack_pstat);

  DMFCBase->RegisterPacketReceiver(SPID_INVINFO, ReceiveHoardInv);
  DMFCBase->RegisterPacketReceiver(SPID_GAMECONFIG, ReceiveGameConfig);

  DMFCBase->SetNumberOfTeams(1);
  (DMFCBase->GetNetgameInfo())->flags |= (NF_DAMAGE_FRIENDLY | NF_TRACK_RANK);

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  DisplayScoreScreen = false;

  HoardOrbIcon = DLLbm_AllocLoadFileBitmap("HoardICON.ogf", 0, BITMAP_FORMAT_1555);
  if (HoardOrbIcon == -1) {
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
  tDmfcStatsColumnInfo pl_col[8];
  char gname[20];
  strcpy(gname, TXT_STATGAMENAME);

  tsi.flags = DSIF_SHOW_PIC | DSIF_SHOW_OBSERVERICON;
  tsi.cColumnCountDetailed = 0;
  tsi.cColumnCountPlayerList = 8;
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
  pl_col[0].width = 27;

  pl_col[1].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[1].title, TXT_PILOT);
  pl_col[1].type = DSCOL_PILOT_NAME;
  pl_col[1].width = 84;

  pl_col[2].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[2].title, TXT_SCORE);
  pl_col[2].type = DSCOL_CUSTOM;
  pl_col[2].width = 49;

  pl_col[3].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[3].title, TXT_HIGHEST);
  pl_col[3].type = DSCOL_CUSTOM;
  pl_col[3].width = 65;

  pl_col[4].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[4].title, TXT_KILLS_SHORT);
  pl_col[4].type = DSCOL_KILLS_LEVEL;
  pl_col[4].width = 40;

  pl_col[5].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[5].title, TXT_DEATHS_SHORT);
  pl_col[5].type = DSCOL_DEATHS_LEVEL;
  pl_col[5].width = 40;

  pl_col[6].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[6].title, TXT_SUICIDES_SHORT);
  pl_col[6].type = DSCOL_SUICIDES_LEVEL;
  pl_col[6].width = 40;

  pl_col[7].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[7].title, TXT_PING);
  pl_col[7].type = DSCOL_PING;
  pl_col[7].width = 40;

  dstat->Initialize(&tsi);
}

// Called when the DLL is shutdown
void DLLFUNCCALL DLLGameClose() {
  if (Highlight_bmp > BAD_BITMAP_HANDLE)
    DLLbm_FreeBitmap(Highlight_bmp);

  DLLDestroyStringTable(StringTable, StringTableSize);
  if (HoardOrbIcon > BAD_BITMAP_HANDLE)
    DLLbm_FreeBitmap(HoardOrbIcon);

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

// DMFCApp::GameInit
//
//   Sets up all the DLL functions and pointers and preps the class for use.  This ABSOLUTLY must be
//   called, so if you override DMFCApp::GameInit, make sure that you put a call to this somewhere in
//   the override.
void ShowGameConfigDialog(int i);
void SwitchHUDColor(int i);
void HoardGameInit(int teams) {
  IMenuItem *lev1, *lev2;
  lev1 = CreateMenuItemWArgs(TXT_GAMENAME, MIT_NORMAL, 0, NULL);

  lev2 = CreateMenuItemWArgs(TXT_HUDSCORECOLORS, MIT_STATE, 0, SwitchHUDColor);
  lev2->SetStateItemList(2, TXT_PLAYERCOLORS, TXT_NORMAL);
  lev2->SetState(HUD_color_model);
  lev1->AddSubMenu(lev2);

  // lev2 = CreateMenuItemWArgs(TXT_GAMECONFIG,MIT_NORMAL,0,ShowGameConfigDialog);
  // lev1->AddSubMenu(lev2);

  IMenuItem *MainMenu = DMFCBase->GetOnScreenMenu();
  MainMenu->AddSubMenu(lev1);

  DMFCBase->GameInit(teams);
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
  t = len[1] = strlen(TXT_POINTS);
  pos[2] = pos[1] + t + 1;
  t = len[2] = strlen(TXT_KILLS);
  pos[3] = pos[2] + t + 1;
  t = len[3] = strlen(TXT_DEATHS);
  pos[4] = pos[3] + t + 1;
  t = len[4] = strlen(TXT_SUICIDES);
  pos[5] = pos[4] + t + 1;
  t = len[5] = strlen(TXT_PING);

  memcpy(&buffer[pos[0]], TXT_PILOT, strlen(TXT_PILOT));
  memcpy(&buffer[pos[1]], TXT_POINTS, len[1]);
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

void OnHUDInterval(void) {
  dstat->DoFrame();
  DMFCBase->DisplayOutrageLogo();

  DMFCBase->OnHUDInterval();
}

void OnInterval(void) {
  SortPlayerScores(SortedPlayers, MAX_PLAYER_RECORDS);
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
      stat->HighestScore[DSTAT_LEVEL] = 0;
      stat->HighestScore[DSTAT_OVERALL] = 0;
    }
  }
}

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
      stat->HighestScore[DSTAT_LEVEL] = 0;
    }
  }
  DMFCBase->RequestGameState();
  int grooms[4];
  grooms[0] = grooms[1] = grooms[2] = grooms[3] = DLLFindTextureName("GreenBase");
  DLLMultiPaintGoalRooms(grooms);

  // display the config dialog
  if (!Config_displayed && DMFCBase->GetLocalRole() == LR_SERVER) {
    DMFCBase->StartUIWindow(HOARD_CONFIG_DLG, &config);
    Config_displayed = true;
  }
}

void OnClientShowUI(int id, void *user_data) {
  if (id == HOARD_CONFIG_DLG)
    DisplayHoardConfigDialog((tGameConfig *)user_data);

  if (id == 0xEEE1) {
    // block off wait for players dialog
    DisplayHoardConfigDialog(&config);
    return;
  }

  DMFCBase->OnClientShowUI(id, user_data);
}

void OnClientLevelEnd(void) { DMFCBase->OnClientLevelEnd(); }

// We need to send all the inventory info out to the new player
void OnGameStateRequest(int player_num) {
  SendHoardInv(player_num);
  DMFCBase->OnGameStateRequest(player_num);
}

// A new player has entered the game, zero there stats out
void OnPlayerConnect(int player_num) {
  DMFCBase->OnPlayerConnect(player_num);

  tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(player_num);
  if (stat) {
    stat->Score[DSTAT_LEVEL] = 0;
    stat->Score[DSTAT_OVERALL] = 0;
    stat->HighestScore[DSTAT_LEVEL] = 0;
    stat->HighestScore[DSTAT_OVERALL] = 0;
  }
}

void OnServerPlayerChangeSegment(int player_num, int newseg, int oldseg) {
  int g1, g2, g3, g4;
  g1 = DLLGetGoalRoomForTeam(0);
  g2 = DLLGetGoalRoomForTeam(1);
  g3 = DLLGetGoalRoomForTeam(2);
  g4 = DLLGetGoalRoomForTeam(3);

  int count = DLLInvCheckItem(player_num, OBJ_POWERUP, HoardID);

  if ((count) && ((newseg == g1) || (newseg == g2) || (newseg == g3) || (newseg == g4))) {

    DMFCBase->CallClientEvent(EVT_CLIENT_GAMEPLAYERCHANGESEG, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
    DMFCBase->CallOnClientPlayerChangeSegment(player_num, newseg, oldseg);
  }
  DMFCBase->OnServerPlayerChangeSegment(player_num, newseg, oldseg);
}

void OnClientPlayerChangeSegment(int player_num, int newseg, int oldseg) {
  int score, count, i;

  count = DLLInvGetTypeIDCount(player_num, OBJ_POWERUP, HoardID);
  score = count;

  if (count < config.min_hoard) {
    if (player_num == DMFCBase->GetPlayerNum())
      DLLAddHUDMessage(TXT_NEEDMOREOBS, config.min_hoard);
    return;
  }

  for (i = 0; i < count; i++) {
    score += i;
    DLLInvRemove(player_num, OBJ_POWERUP, HoardID);
  }

  if (score == 0)
    return;

  tPlayerStat *stat;
  stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(player_num);

  if (stat) {
    // increment scores
    stat->Score[DSTAT_LEVEL] += score;
    stat->Score[DSTAT_OVERALL] += score;
    if (stat->HighestScore[DSTAT_LEVEL] < score)
      stat->HighestScore[DSTAT_LEVEL] = score;
    if (stat->HighestScore[DSTAT_OVERALL] < score)
      stat->HighestScore[DSTAT_OVERALL] = score;
  }

  char buffer[100];
  if (score == 1)
    snprintf(buffer, sizeof(buffer), TXT_SCOREONE, dPlayers[player_num].callsign,
             (stat) ? stat->Score[DSTAT_LEVEL] : 0);
  else
    snprintf(buffer, sizeof(buffer), TXT_SCOREMULTI, dPlayers[player_num].callsign, score,
             (stat) ? stat->Score[DSTAT_LEVEL] : 0);
  int sound = DLLFindSoundName("PwrHoardScore");
  if (sound != -1)
    DLLPlay3dSound(sound, &dObjects[dPlayers[DMFCBase->GetPlayerNum()].objnum], 1, 0);

  // Set a Timer to display
  if (WhoJustScoredTimer != -1)
    DMFCBase->KillTimer(WhoJustScoredTimer);
  WhoJustScoredTimer = DMFCBase->SetTimerInterval(OnTimer, 0.5f, 5.0f, OnTimerKill);
  WhoJustScored = player_num;

  // remove the balls
  DLLPlayerSetRotatingBall(player_num, 0, 0, NULL, NULL, NULL);

  DLLAddHUDMessage(buffer);

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    // check the score to see if we hit the limit
    if (DMFCBase->GetScoreLimit(&score)) {
      if (score <= ((stat) ? stat->Score[DSTAT_LEVEL] : 0)) {
        DLLmprintf(0, "Score limit reached\n");
        DMFCBase->EndLevel();
      }
    }
  }
  DMFCBase->OnClientPlayerChangeSegment(player_num, newseg, oldseg);
}

// A new player has entered the game, zero there stats out
void OnClientPlayerEntersGame(int player_num) {
  DMFCBase->OnClientPlayerEntersGame(player_num);
  if (player_num != DMFCBase->GetPlayerNum())
    DisplayWelcomeMessage(player_num);
  else
    display_my_welcome = true;
}

void OnServerCollide(object *me_obj, object *it_obj) {
  // see if we need to send this event to the clients
  // only if me==player it==hoard powerup

  if (!me_obj || !it_obj) {
    DMFCBase->OnServerCollide(me_obj, it_obj);
    return;
  }

  if ((me_obj->type == OBJ_PLAYER) && (it_obj->type == OBJ_POWERUP) && (it_obj->id == HoardID)) {
    // check to make sure the player isn't dying or dead
    player *plyr_ptr = &dPlayers[me_obj->id];
    if ((plyr_ptr->flags & PLAYER_FLAGS_DYING) || (plyr_ptr->flags & PLAYER_FLAGS_DEAD)) {
      // this player is dying or dead...ignore it
      DMFCBase->OnServerCollide(me_obj, it_obj);
      return;
    }

    DMFCBase->CallClientEvent(EVT_CLIENT_GAMECOLLIDE, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
    DMFCBase->CallOnClientCollide(me_obj, it_obj);

    // test to see if they are in a goal room, if so score
    int current_room = me_obj->roomnum;
    int g1, g2, g3, g4;
    g1 = DLLGetGoalRoomForTeam(0);
    g2 = DLLGetGoalRoomForTeam(1);
    g3 = DLLGetGoalRoomForTeam(2);
    g4 = DLLGetGoalRoomForTeam(3);

    if ((current_room == g1) || (current_room == g2) || (current_room == g3) || (current_room == g4)) {
      DMFCBase->CallClientEvent(EVT_CLIENT_GAMEPLAYERCHANGESEG, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
      DMFCBase->CallOnClientPlayerChangeSegment(me_obj->id, current_room, current_room);
    }
  }
  DMFCBase->OnServerCollide(me_obj, it_obj);
}

void OnClientCollide(object *me_obj, object *it_obj) {
  int playernum = me_obj->id;
  int count = DLLInvGetTypeIDCount(playernum, OBJ_POWERUP, HoardID);

  if (count < 12) {
    if (DMFCBase->GetPlayerNum() == playernum) {
      DLLAddHUDMessage(TXT_GOTHOARD);
    }
    int sound = DLLFindSoundName("PwrHoardPickup");
    if (sound != -1)
      DLLPlay3dSound(sound, me_obj, 1, 0);
    if (it_obj->type == OBJ_POWERUP) {
      DLLInvAddTypeID(playernum, it_obj->type, it_obj->id, -1, -1, 0, NULL);
      if (DMFCBase->GetLocalRole() == LR_SERVER) {
        DLLSetObjectDeadFlag(it_obj, true, false);
      }
    } else
      DLLmprintf(0, "HOARD BIG WARNING: TRYING TO ADD NONPOWERUP TO INVENTORY! (%d)\n", it_obj->type);

    // add rotating balls if necessary
    DoBallsEffect(playernum, count + 1);
  } else {
    // they have max orbs
    if (DMFCBase->GetPlayerNum() == playernum) {
      DLLAddHUDMessage(TXT_MAXHOARDS);
    }
  }
  DMFCBase->OnClientCollide(me_obj, it_obj);
}

// used for the clients when a player dies, to print out a message and other stuff
void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
  int kpnum = -1;

  if (killer_obj) {
    if ((killer_obj->type == OBJ_PLAYER) || (killer_obj->type == OBJ_GHOST))
      kpnum = killer_obj->id;
    else if (killer_obj->type == OBJ_ROBOT) {
      // countermeasure kill
      kpnum = DMFCBase->GetCounterMeasureOwner(killer_obj);
    } else {
      kpnum = -1;
    }
  } else
    kpnum = -1;

  // add an extra hoard to the inventory if they didn't kill themselves
  if (kpnum != victim_pnum) {
    DLLInvAddTypeID(victim_pnum, OBJ_POWERUP, HoardID, -1, -1, 0, NULL);
  }

  // remove the balls
  DLLPlayerSetRotatingBall(victim_pnum, 0, 0, NULL, NULL, NULL);

  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
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
#define PLAYERS_COL 100
#define SCORE_COL 200
#define HIGH_COL 260
#define KILLS_COL 320
#define DEATHS_COL 380
#define SUICIDES_COL 440

  DMFCBase->OnPLRInterval();

  int y = 40;
  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;

  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(PLAYERS_COL, y, TXT_PILOT);
  DLLgrtext_Printf(SCORE_COL, y, TXT_LEVEL);
  DLLgrtext_Printf(SCORE_COL, y + height, TXT_POINTS);
  DLLgrtext_Printf(HIGH_COL, y, TXT_HIGH);
  DLLgrtext_Printf(HIGH_COL, y + height, TXT_GOAL);
  DLLgrtext_Printf(KILLS_COL, y, TXT_KILLS);
  DLLgrtext_Printf(DEATHS_COL, y, TXT_DEATHS);
  DLLgrtext_Printf(SUICIDES_COL, y, TXT_SUICIDES);
  y += (2 * height);

  // print out player stats
  int rank = 1;
  int slot;
  player_record *pr;
  tPlayerStat *stat;

  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    slot = SortedPlayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      int pnum = DMFCBase->WasPlayerInGameAtLevelEnd(slot);
      if (pnum != -1) {
        DLLgrtext_SetColor((DMFCBase->GetPlayerColors())[pnum]);
      } else {
        DLLgrtext_SetColor(GR_RGB(128, 128, 128));
      }

      stat = (tPlayerStat *)pr->user_info;

      DLLgrtext_Printf(PLAYERS_COL, y, "%d)%s", rank, pr->callsign);
      DLLgrtext_Printf(SCORE_COL, y, "%d[%d]", (stat) ? stat->Score[DSTAT_LEVEL] : 0,
                       (stat) ? stat->Score[DSTAT_OVERALL] : 0);
      DLLgrtext_Printf(HIGH_COL, y, "%d[%d]", (stat) ? stat->HighestScore[DSTAT_LEVEL] : 0,
                       (stat) ? stat->HighestScore[DSTAT_OVERALL] : 0);
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

  snprintf(buffer, sizeof(buffer), TXT_STATSSAVEA, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSB);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSC);
  DLLcf_WriteString(file, buffer);
  strcpy(
      buffer,
      "-------------------------------------------------------------------------------------------------------------");
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

      if (ps) {
        snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", ps->HighestScore[DSTAT_LEVEL],
                 ps->HighestScore[DSTAT_OVERALL]);
        memcpy(&buffer[81], tempbuffer, strlen(tempbuffer));
      }

      snprintf(tempbuffer, sizeof(tempbuffer), "%s", DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(sortedslots[p])));
      memcpy(&buffer[96], tempbuffer, strlen(tempbuffer));

      size_t pos = 96 + strlen(tempbuffer) + 1;

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

#define ROOTFILENAME "Hoard"
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

// handles a hoard inventory packet
void ReceiveHoardInv(uint8_t *data) {
  int x, i, count = 0;
  int size;

  for (x = 0; x < DLLMAX_PLAYERS; x++) {
    // see if we have a valid player
    size = MultiGetByte(data, &count);

    if (DMFCBase->CheckPlayerNum(x)) {
      // we have a valid player, add orbs
      ASSERT(size >= 0);
      DoBallsEffect(x, size);
      for (i = 0; i < size; i++) {
        DLLInvAddTypeID(x, OBJ_POWERUP, HoardID, -1, -1, 0, NULL);
      } // end for
    }   // end if
  }     // end for
}

// sends a hoard inventory packet to a player
void SendHoardInv(int playernum) {
  uint8_t data[MAX_GAME_DATA_SIZE];
  int i;
  int count = 0;

  DMFCBase->StartPacket(data, SPID_INVINFO, &count);

  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    if (DMFCBase->CheckPlayerNum(i)) {
      MultiAddByte(DLLInvGetTypeIDCount(i, OBJ_POWERUP, HoardID), data, &count);
    } else {
      MultiAddByte(0, data, &count);
    }
  }

  DMFCBase->SendPacket(data, count, playernum);

  SendGameConfig(playernum);
}

void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    DisplayWelcomeMessage(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (DisplayScoreScreen)
    return;

  int x = 520;
  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX]) + 3;
  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)((DisplayScoreScreen) ? 128 : 255));
  int y = (DMFCBase->GetGameWindowH() / 2) - ((height * 5) / 2);
  int rank = 1;
  ddgr_color color;

  char name[50];
  player_record *pr;
  tPlayerStat *stat;

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 85.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;
  DLLgrtext_SetAlpha(alpha);

  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    int slot = SortedPlayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      if ((pr->state == STATE_DISCONNECTED) || (pr->state == STATE_INGAME && !DMFCBase->IsPlayerObserver(pr->pnum))) {

        stat = (tPlayerStat *)pr->user_info;
        strcpy(name, pr->callsign);
        DMFCBase->ClipString(name_width, name, true);

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

            DLLrend_DrawScaledBitmap(name_x - 2, y - 2, score_x + score_width + 2, y + height - 1, Highlight_bmp, 0, 0,
                                     1, 1, 1.0f, -1, NULL);
            DLLrend_SetZBufferState(1);
          }

          if ((WhoJustScored != pr->pnum) || (DisplayBlink)) {
            DLLgrtext_SetColor(color);
            DLLgrtext_Printf(name_x, y, name);
            DLLgrtext_Printf(score_x, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
          }
          y += height;
        } else if (rank < 6) {
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

          if ((pr->state == STATE_DISCONNECTED) || (WhoJustScored != pr->pnum) || (DisplayBlink)) {
            DLLgrtext_SetColor(color);
            DLLgrtext_Printf(name_x, y, name);
            DLLgrtext_Printf(score_x, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
          }
          y += height;
        }
        rank++;
      }
    }
  }

  // draw the hoard orb count
  int w = DLLbm_w(HoardOrbIcon, 0);
  char buffer[4];
  snprintf(buffer, sizeof(buffer), "%d", DLLInvGetTypeIDCount(DMFCBase->GetPlayerNum(), OBJ_POWERUP, HoardID));
  int x1, x2, y1, y2;
  x1 = DMFCBase->GetGameWindowW() - 5 - DLLbm_w(HoardOrbIcon, 0);
  y1 = 25;
  x2 = x1 + DLLbm_w(HoardOrbIcon, 0);
  y2 = y1 + DLLbm_h(HoardOrbIcon, 0);

  DLLrend_SetAlphaValue(alpha);
  DLLrend_SetZBufferState(0);
  DLLrend_SetTextureType(TT_LINEAR);
  DLLrend_SetLighting(LS_NONE);
  DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);
  DLLrend_DrawScaledBitmap(x1, y1, x2, y2, HoardOrbIcon, 0, 0, 1, 1, 1.0f, -1, NULL);
  DLLrend_SetZBufferState(1);

  x1 += w / 2;
  y1 += DLLbm_h(HoardOrbIcon, 0) / 2;
  x1 -= ((float)DLLgrtext_GetTextLineWidth(buffer)) / 2.0f;
  y1 -= ((height - 3) / 2.0);

  DLLgrtext_SetColor(GR_RGB(128, 128, 128));
  DLLgrtext_SetAlpha(std::min(alpha + 30, 255));
  DLLgrtext_Printf(x1, y1, buffer);
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

void DisplayWelcomeMessage(int player_num) {
  char name_buffer[64];
  strcpy(name_buffer, (DMFCBase->GetPlayers())[player_num].callsign);

  if (player_num == DMFCBase->GetPlayerNum()) {
    DLLAddHUDMessage(TXT_WELCOME, name_buffer);
  } else {
    DLLAddHUDMessage(TXT_JOINED, name_buffer);
  }
}

void DoBallsEffect(int i, int count) {
  float redb[4];
  float greenb[4];
  float blueb[4];

  for (int x = 0; x < 4; x++) {
    redb[x] = blueb[x] = 0;
    greenb[x] = 1;
  }

  switch (count) {
  case 0:
    DLLPlayerSetRotatingBall(i, 0, 0, redb, greenb, blueb);
    break;
  case 1:
    DLLPlayerSetRotatingBall(i, 1, 4, redb, greenb, blueb);
    break;
  case 2:
    DLLPlayerSetRotatingBall(i, 1, 3, redb, greenb, blueb);
    break;
  case 3:
    DLLPlayerSetRotatingBall(i, 1, 2, redb, greenb, blueb);
    break;
  case 4:
    DLLPlayerSetRotatingBall(i, 1, 1, redb, greenb, blueb);
    break;
  case 5:
    DLLPlayerSetRotatingBall(i, 2, 4, redb, greenb, blueb);
    break;
  case 6:
    DLLPlayerSetRotatingBall(i, 2, 3, redb, greenb, blueb);
    break;
  case 7:
    DLLPlayerSetRotatingBall(i, 2, 2, redb, greenb, blueb);
    break;
  case 8:
    DLLPlayerSetRotatingBall(i, 2, 1, redb, greenb, blueb);
    break;
  case 9:
    DLLPlayerSetRotatingBall(i, 3, 4, redb, greenb, blueb);
    break;
  case 10:
    DLLPlayerSetRotatingBall(i, 3, 3, redb, greenb, blueb);
    break;
  case 11:
    DLLPlayerSetRotatingBall(i, 3, 2, redb, greenb, blueb);
    break;
  case 12:
    DLLPlayerSetRotatingBall(i, 3, 1, redb, greenb, blueb);
    break;
  }
}

/////////////////////////////////
// Timer event handlers
void OnTimer(void) { DisplayBlink = !DisplayBlink; }
void OnTimerKill(void) {
  DisplayBlink = true;
  WhoJustScored = WhoJustScoredTimer = -1;
}

// game config send/receive
void SendGameConfig(int towho) {
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;

  DMFCBase->StartPacket(data, SPID_GAMECONFIG, &count);

  MultiAddByte(config.min_hoard, data, &count);

  DMFCBase->SendPacket(data, count, towho);
}

void ReceiveGameConfig(uint8_t *data) {
  int count = 0;
  config.min_hoard = MultiGetByte(data, &count);
}

void ShowGameConfigDialog(int i) {
  DMFCBase->EnableOnScreenMenu(false);
  DMFCBase->StartUIWindow(HOARD_CONFIG_DLG, &config);
}

void SwitchHUDColor(int i) { HUD_color_model = i; }
