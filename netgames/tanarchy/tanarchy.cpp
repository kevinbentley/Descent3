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

 * $Logfile: /DescentIII/Main/tanarchy/tanarchy.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:59:14 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: tanarchy.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:59:14  kevinb
 * initial 1.5 import
 *
 *
 * 74    10/03/01 1:05p Matt
 * Made team_name buffer large enough to hold the team number *plus* the
 * number of players on the team.
 *
 * 73    9/24/01 2:28p Matt
 * Allowed room for longer team name on results screen.
 *
 * 72    9/18/01 6:54p Matt
 * Show results for NUM_TEAMS, not MAX_TEAMS.
 * Removed some unused code.
 *
 * 71    9/13/01 5:31p Matt
 * Added a team member list to the stats display.
 * Fixed a non-terminated string bug.
 *
 * 70    10/21/99 3:28p Kevin
 * Mac merge!
 *
 * 69    7/15/99 1:18a Jeff
 * added $scores
 *
 * 68    7/12/99 2:27p Jeff
 * fixed PLR to only display the team label for the disconnected list if
 * there are people in the list
 *
 * 67    7/12/99 1:22p Jeff
 * updated for new netflags
 *
 * 66    7/11/99 6:55p Jeff
 * fixed PLR so it doesn't go off the screen on long lists and active
 * players in the game are shown first
 *
 * 65    5/23/99 5:54p Jeff
 * fixed HUD display
 *
 * 64    5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 63    5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 62    5/12/99 11:28a Jeff
 * added sourcesafe comment block
 *
 * $NoKeywords: $
 */

#include "gamedll_header.h"
#include <string.h>
#include "idmfc.h"
#include "tanDMFC.h"
#include "tanarchystr.h"
IDMFC *DMFCBase = NULL;
static IDmfcStats *dstat = NULL;
static player *dPlayers;

#define SPID_NEWPLAYER 0
#define NUM_TEAMS 2

static int SortedPLRPlayers[MAX_TEAMS][MAX_PLAYER_RECORDS];
static int TeamScore[NUM_TEAMS];
static int SortedTeams[NUM_TEAMS];
static int SortedPlayers[MAX_PLAYER_RECORDS];
static bool DisplayScoreScreen;
static bool display_my_welcome = false;

static void GetGameStartPacket(uint8_t *data);
static void SendGameStartPacket(int pnum);
static void DisplayScores(void);
static void DisplayHUDScores(struct tHUDItem *hitem);
static void DisplayWelcomeMessage(int player_num);
static void SortTeamScores(int *sortedindex, int *scores);
void OnSaveStatsToFile(void);
static void OnLevelEndSaveStatsToFile(void);
static void OnDisconnectSaveStatsToFile(void);
static void OnPrintScores(int level);
static void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size);
static void TeamScoreCallback(int team, char *buffer, int buffer_size);
static bool compare_slots(int a, int b);

static int Highlight_bmp = -1;

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

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }

  snprintf(buffer, buffer_size, "%d[%d]", pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL],
           pr->dstats.kills[DSTAT_OVERALL] - pr->dstats.suicides[DSTAT_OVERALL]);
}

void TeamScoreCallback(int team, char *buffer, int buffer_size) {
  ASSERT(team >= 0 && team < DLLMAX_TEAMS);

  snprintf(buffer, buffer_size, " %d", TeamScore[team]);
}

// This function gets called by the game when it wants to learn some info about the game
void DLLFUNCCALL DLLGetGameInfo(tDLLOptions *options) {
  options->flags = DOF_MAXTEAMS | DOF_MINTEAMS;
  options->max_teams = 2;
  options->min_teams = 2;
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
  DMFCBase->Set_OnGameStateRequest(OnGameStateRequest);
  DMFCBase->Set_OnClientPlayerKilled(OnClientPlayerKilled);
  DMFCBase->Set_OnServerGameCreated(OnServerGameCreated);
  DMFCBase->Set_OnClientLevelStart(OnClientLevelStart);
  DMFCBase->Set_OnClientLevelEnd(OnClientLevelEnd);
  DMFCBase->Set_OnClientPlayerEntersGame(OnClientPlayerEntersGame);
  DMFCBase->Set_OnInterval(OnInterval);
  DMFCBase->Set_OnHUDInterval(OnHUDInterval);
  DMFCBase->Set_OnKeypress(OnKeypress);
  DMFCBase->Set_OnPLRInterval(OnPLRInterval);
  DMFCBase->Set_OnPLRInit(OnPLRInit);
  DMFCBase->Set_OnSaveStatsToFile(OnSaveStatsToFile);
  DMFCBase->Set_OnLevelEndSaveStatsToFile(OnLevelEndSaveStatsToFile);
  DMFCBase->Set_OnDisconnectSaveStatsToFile(OnDisconnectSaveStatsToFile);
  DMFCBase->Set_OnPrintScores(OnPrintScores);

  dPlayers = DMFCBase->GetPlayers();

  DMFCBase->GameInit(NUM_TEAMS);
  DLLCreateStringTable("tanarchy.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    *all_ok = 0;
    return;
  }

  netgame_info *Netgame = DMFCBase->GetNetgameInfo();
  Netgame->flags |= (NF_TRACK_RANK);

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

  // register special packet receivers
  DMFCBase->RegisterPacketReceiver(SPID_NEWPLAYER, GetGameStartPacket);

  DMFCBase->SetNumberOfTeams(NUM_TEAMS);

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  DisplayScoreScreen = false;

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
  tDmfcStatsColumnInfo pl_col[6];
  char gname[20];
  strcpy(gname, TXT_STATSGAMENAME);

  tsi.flags = DSIF_SHOW_PIC | DSIF_SHOW_OBSERVERICON | DSIF_SEPERATE_BY_TEAM;
  tsi.cColumnCountDetailed = 0;
  tsi.cColumnCountPlayerList = 6;
  tsi.clbDetailedColumnBMP = NULL;
  tsi.clbDetailedColumn = NULL;
  tsi.clbPlayerColumn = DetermineScore;
  tsi.clbPlayerColumnBMP = NULL;
  tsi.DetailedColumns = NULL;
  tsi.GameName = gname;
  tsi.MaxNumberDisplayed = NULL;
  tsi.PlayerListColumns = pl_col;
  tsi.SortedPlayerRecords = SortedPlayers;
  tsi.clTeamLine = TeamScoreCallback;

  pl_col[0].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[0].title, TXT_PILOT);
  pl_col[0].type = DSCOL_PILOT_NAME;
  pl_col[0].width = 120;

  pl_col[1].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[1].title, TXT_SCORE);
  pl_col[1].type = DSCOL_CUSTOM;
  pl_col[1].width = 47;

  pl_col[2].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[2].title, TXT_KILLS);
  pl_col[2].type = DSCOL_KILLS_LEVEL;
  pl_col[2].width = 47;

  pl_col[3].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[3].title, TXT_DEATHS);
  pl_col[3].type = DSCOL_DEATHS_LEVEL;
  pl_col[3].width = 57;

  pl_col[4].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[4].title, TXT_SUICIDES);
  pl_col[4].type = DSCOL_SUICIDES_LEVEL;
  pl_col[4].width = 67;

  pl_col[5].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[5].title, TXT_PING);
  pl_col[5].type = DSCOL_PING;
  pl_col[5].width = 40;

  dstat->Initialize(&tsi);
}
// Called when the DLL is shutdown
void DLLFUNCCALL DLLGameClose() {
  if (Highlight_bmp > BAD_BITMAP_HANDLE)
    DLLbm_FreeBitmap(Highlight_bmp);

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

// The server has just started, so clear out all the stats and game info
void OnServerGameCreated(void) {
  DMFCBase->OnServerGameCreated();

  for (int i = 0; i < NUM_TEAMS; i++) {
    TeamScore[i] = 0;
  }
}

// The server has started a new level, so clear out level scores
void OnClientLevelStart(void) {
  DMFCBase->OnClientLevelStart();
  for (int i = 0; i < NUM_TEAMS; i++) {
    TeamScore[i] = 0;
  }
  DMFCBase->RequestGameState();
}

void OnClientLevelEnd(void) { DMFCBase->OnClientLevelEnd(); }

// A New Player has entered the game, so we want to send him a game status packet that
// has information about the game
void OnGameStateRequest(int player_num) {
  SendGameStartPacket(player_num);
  DMFCBase->OnGameStateRequest(player_num);
}

// A new player has entered the game, zero there stats out
void OnClientPlayerEntersGame(int player_num) {
  DMFCBase->OnClientPlayerEntersGame(player_num);

  if (player_num != DMFCBase->GetPlayerNum())
    DisplayWelcomeMessage(player_num);
  else
    display_my_welcome = true;
}

// We need to adjust the scores
void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
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

  if (DMFCBase->IsPlayerDedicatedServer(victim_pnum))
    return; // dedicated server

  if (kpnum == victim_pnum && victim_pnum != -1)
    // subtract from the team score
    TeamScore[dPlayers[victim_pnum].team]--;
  else if ((kpnum != -1) && (dPlayers[kpnum].team != -1))
    TeamScore[dPlayers[kpnum].team]++;

  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
}

void OnHUDInterval(void) {
  dstat->DoFrame();

  DMFCBase->DisplayOutrageLogo();

  DMFCBase->OnHUDInterval();
}

void OnInterval(void) {
  SortTeamScores(SortedTeams, TeamScore);
  DMFCBase->GetSortedPlayerSlots(SortedPlayers, MAX_PLAYER_RECORDS);

  // do killgoal check
  int goal;
  if (DMFCBase->GetScoreLimit(&goal)) {
    for (int i = 0; i < NUM_TEAMS; i++) {
      if (TeamScore[i] >= goal)
        DMFCBase->EndLevel();
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

bool compare_slots(int a, int b) {
  int ascore, bscore;
  player_record *apr, *bpr;
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
  if ((apr->state == STATE_INGAME) && (bpr->state == STATE_INGAME)) {
    // both players were in the game
    ascore = apr->dstats.kills[DSTAT_LEVEL] - apr->dstats.suicides[DSTAT_LEVEL];
    bscore = bpr->dstats.kills[DSTAT_LEVEL] - bpr->dstats.suicides[DSTAT_LEVEL];
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
  ascore = apr->dstats.kills[DSTAT_LEVEL] - apr->dstats.suicides[DSTAT_LEVEL];
  bscore = bpr->dstats.kills[DSTAT_LEVEL] - bpr->dstats.suicides[DSTAT_LEVEL];
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

  // Now fill in the final structure of sorted names
  int TeamCount[MAX_TEAMS];
  int team;
  for (i = 0; i < MAX_TEAMS; i++)
    TeamCount[i] = 0;
  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    int slot = SortedPlayers[i];
    player_record *pr = DMFCBase->GetPlayerRecord(slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // dedicated server

      team = (pr->state == STATE_INGAME) ? dPlayers[pr->pnum].team : pr->team;
      SortedPLRPlayers[team][TeamCount[team]] = slot;
      TeamCount[team]++;
    }
  }
  for (i = 0; i < MAX_TEAMS; i++) {
    if (TeamCount[i] < MAX_PLAYER_RECORDS)
      SortedPLRPlayers[i][TeamCount[i]] = -1;
  }

  DMFCBase->OnPLRInit();
}

void OnPLRInterval(void) {
  DMFCBase->OnPLRInterval();

  int TeamCol = 35;
  int NameCol = 190;
  int KillsCol = 330;
  int DeathsCol = 380;
  int SuicidesCol = 430;
  int y = 40;
  int slot;
  player_record *pr;

  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);
  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(NameCol, y, TXT_PILOT);
  DLLgrtext_Printf(KillsCol, y, TXT_KILLS);
  DLLgrtext_Printf(DeathsCol, y, TXT_DEATHS);
  DLLgrtext_Printf(SuicidesCol, y, TXT_SUICIDES);
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
      DLLgrtext_Printf(TeamCol, y, TXT_TEAMSCORE, DMFCBase->GetTeamString(team), TeamScore[team]);
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
          continue; // dedicated server

        int pnum = DMFCBase->WasPlayerInGameAtLevelEnd(slot);

        if ((doing_connected && pnum == -1) || (!doing_connected && pnum != -1))
          continue; // we're not handling them right now

        if (pnum != -1) {
          DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));
        } else {
          DLLgrtext_SetColor(GR_RGB(128, 128, 128));
        }

        // valid player
        DLLgrtext_Printf(NameCol, y, "%s %d[%d]", pr->callsign,
                         pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL],
                         pr->dstats.kills[DSTAT_OVERALL] - pr->dstats.suicides[DSTAT_OVERALL]);
        DLLgrtext_Printf(KillsCol, y, "%d[%d]", pr->dstats.kills[DSTAT_LEVEL], pr->dstats.kills[DSTAT_OVERALL]);
        DLLgrtext_Printf(DeathsCol, y, "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL], pr->dstats.deaths[DSTAT_OVERALL]);
        DLLgrtext_Printf(SuicidesCol, y, "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL],
                         pr->dstats.suicides[DSTAT_OVERALL]);
        y += height;
        has_members = true;

        if (y >= 440)
          goto quick_exit;
      }
    } // end for
    // on to the next team
    if (!has_members)
      y += height;

    if (y >= 440)
      goto quick_exit;

  } // end for

  if (doing_connected) {
    doing_connected = false;
    goto do_disconnected_folk;
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
  int count, p;

  // sort the stats
  DMFCBase->GetSortedPlayerSlots(sortedslots, MAX_PLAYER_RECORDS);
  count = 1;

  snprintf(buffer, sizeof(buffer), TXT_SAVESTATSA, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  for (p = 0; p < NUM_TEAMS; p++) {
    int team_i = SortedTeams[p];
    memset(buffer, ' ', BUFSIZE);
    snprintf(tempbuffer, sizeof(tempbuffer), TXT_TEAM, DMFCBase->GetTeamString(team_i));
    memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));
    snprintf(tempbuffer, sizeof(tempbuffer), "[%d]", TeamScore[team_i]);
    memcpy(&buffer[20], tempbuffer, strlen(tempbuffer));
    buffer[20 + strlen(tempbuffer)] = '\0';
    DLLcf_WriteString(file, buffer);
  }

  // Write team members
  DLLcf_WriteString(file, ""); // blank line
  for (int t = 0; t < NUM_TEAMS; t++) {
    int team_i = SortedTeams[t];

    snprintf(buffer, sizeof(buffer), TXT_TEAM, DMFCBase->GetTeamString(team_i));
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
  strcpy(buffer, "-----------------------------------------------------------------------------");
  DLLcf_WriteString(file, buffer);

  for (p = 0; p < MAX_PLAYER_RECORDS; p++) {
    pr = DMFCBase->GetPlayerRecord(sortedslots[p]);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      memset(buffer, ' ', BUFSIZE);

      snprintf(tempbuffer, sizeof(tempbuffer), "%d)", count);
      memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s%s", (pr->state == STATE_INGAME) ? "" : "*", pr->callsign);
      memcpy(&buffer[5], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]",
               pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL] - pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[34], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.kills[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL]);
      memcpy(&buffer[46], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL],
               pr->dstats.deaths[DSTAT_OVERALL]);
      memcpy(&buffer[58], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[69], tempbuffer, strlen(tempbuffer));

      size_t pos = 69 + strlen(tempbuffer) + 1;
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

#define ROOTFILENAME "Team Anarchy"
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

// Handles when we get a new player packet
void GetGameStartPacket(uint8_t *data) {
  // get the team scores
  DLLmprintf(0, "Receiving Team Scores from server\n");
  int count = 0, i;
  for (i = 0; i < NUM_TEAMS; i++) {
    TeamScore[i] = MultiGetInt(data, &count);
  }
}

// Handles sending a new player packet
void SendGameStartPacket(int pnum) {
  int count = 0;
  uint8_t data[MAX_GAME_DATA_SIZE];

  DMFCBase->StartPacket(data, SPID_NEWPLAYER, &count);

  // add the team scores
  int i;
  for (i = 0; i < NUM_TEAMS; i++) {
    MultiAddInt(TeamScore[i], data, &count);
  }

  // we're done
  DLLmprintf(0, "Sending Team Scores to %s\n", dPlayers[pnum].callsign);
  DMFCBase->SendPacket(data, count, pnum);
}

void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    DisplayWelcomeMessage(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (DisplayScoreScreen)
    return;

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX]) + 3;
  int y = (DMFCBase->GetGameWindowH() / 2) - ((height * NUM_TEAMS) / 2);
  int x = 520;
  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)((DisplayScoreScreen) ? 128 : 255));
  int team;

  //	char name[30];

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 100.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;

  team = DMFCBase->GetMyTeam();
  DLLRenderHUDText(DMFCBase->GetTeamColor(team), 255, 0, x, 0, TXT_TEAM, DMFCBase->GetTeamString(team));
  int num_players = 0;

  for (int i = 0; i < NUM_TEAMS; i++) {
    team = SortedTeams[i];
    num_players = 0;

    for (int q = 0; q < DLLMAX_PLAYERS; q++) {
      if (DMFCBase->CheckPlayerNum(q) && dPlayers[q].team == team && !DMFCBase->IsPlayerDedicatedServer(q))
        num_players++;
    }

    if (team == DMFCBase->GetMyTeam()) {
      if (Highlight_bmp > BAD_BITMAP_HANDLE) {
        // draw the highlite bar in the background
        DLLrend_SetAlphaValue(alpha * 0.50f);
        DLLrend_SetAlphaValue(alpha);
        DLLrend_SetZBufferState(0);
        DLLrend_SetTextureType(TT_LINEAR);
        DLLrend_SetLighting(LS_NONE);
        DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);

        DLLrend_DrawScaledBitmap(name_x - 2, y - 2, score_x + score_width + 2, y + height - 1, Highlight_bmp, 0, 0, 1,
                                 1, 1.0, -1, NULL);
        DLLrend_SetZBufferState(1);
      }
    }

    char team_name[MAX_TEAMNAME_LEN + 5];
    snprintf(team_name, sizeof(team_name), "[%d]%s", num_players, DMFCBase->GetTeamString(team));
    DMFCBase->ClipString(name_width, team_name, true);

    DLLgrtext_SetAlpha(alpha);
    DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));
    DLLgrtext_Printf(name_x, y, team_name);
    DLLgrtext_Printf(score_x, y, "%d", TeamScore[team]);

    //		sprintf(name,TXT_TEAMSCORE,DMFCBase->GetTeamString(team));
    //		DMFCBase->ClipString(name_width,name,true);

    y += height;
  }
}

// insert sort
#define compGT(a, b) (a < b)
void SortTeamScores(int *sortedindex, int *scores) {
  int t;
  int i, j;

  // copy scores into scoreinfo array
  for (i = 0; i < NUM_TEAMS; i++) {
    sortedindex[i] = i;
  }

  for (i = 1; i <= NUM_TEAMS - 1; i++) {
    t = sortedindex[i];

    /* Shift elements down until */
    /* insertion point found.    */
    for (j = i - 1; j >= 0 && compGT(scores[sortedindex[j]], scores[t]); j--) {
      sortedindex[j + 1] = sortedindex[j];
    }

    /* insert */
    sortedindex[j + 1] = t;
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
    DLLAddColoredHUDMessage(DMFCBase->GetTeamColor(team), TXT_TEAMJOINMSG, DMFCBase->GetTeamString(team));
  } else {
    int team = dPlayers[player_num].team;
    if (team == -1)
      return;

    DLLAddColoredHUDMessage(DMFCBase->GetTeamColor(team), TXT_JOINED, name_buffer, DMFCBase->GetTeamString(team));
  }
}

void OnPrintScores(int level) {
  char buffer[256];
  char name[70];
  size_t t;
  size_t pos[6];
  size_t len[6];

  for (int i = 0; i < NUM_TEAMS; i++) {
    snprintf(buffer, sizeof(buffer), "%s:%d\n", DMFCBase->GetTeamString(i), TeamScore[i]);
    DPrintf(buffer);
  }

  memset(buffer, ' ', 256);
  pos[0] = 0;
  t = len[0] = 30; // give ample room for pilot name
  pos[1] = pos[0] + t + 1;
  t = len[1] = strlen(TXT_POINTS);
  pos[2] = pos[1] + t + 1;
  t = len[2] = strlen(TXT_KILLS_SHORT);
  pos[3] = pos[2] + t + 1;
  t = len[3] = strlen(TXT_DEATHS_SHORT);
  pos[4] = pos[3] + t + 1;
  t = len[4] = strlen(TXT_SUICIDES_SHORT);
  pos[5] = pos[4] + t + 1;
  t = len[5] = strlen(TXT_PING);

  memcpy(&buffer[pos[0]], TXT_PILOT, strlen(TXT_PILOT));
  memcpy(&buffer[pos[1]], TXT_POINTS, len[1]);
  memcpy(&buffer[pos[2]], TXT_KILLS_SHORT, len[2]);
  memcpy(&buffer[pos[3]], TXT_DEATHS_SHORT, len[3]);
  memcpy(&buffer[pos[4]], TXT_SUICIDES_SHORT, len[4]);
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

  netplayer *dNetPlayers = DMFCBase->GetNetPlayers();

  int sortedplayers[MAX_PLAYER_RECORDS];
  DMFCBase->GetSortedPlayerSlots(sortedplayers, MAX_PLAYER_RECORDS);

  for (int i = 0; i < pcount; i++) {
    slot = sortedplayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    if ((pr) && (pr->state != STATE_EMPTY)) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      snprintf(name, sizeof(name), "%s%s: %.8s", (pr->state == STATE_DISCONNECTED) ? "*" : "", pr->callsign,
               DMFCBase->GetTeamString(pr->team));
      name[29] = '\0';

      memset(buffer, ' ', 256);
      t = strlen(name);
      memcpy(&buffer[pos[0]], name, (t < len[0]) ? t : len[0]);
      snprintf(name, sizeof(name), "%d", pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[1]], name, (t < len[1]) ? t : len[1]);
      snprintf(name, sizeof(name), "%d", pr->dstats.kills[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[2]], name, (t < len[2]) ? t : len[2]);
      snprintf(name, sizeof(name), "%d", pr->dstats.deaths[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[3]], name, (t < len[3]) ? t : len[3]);
      snprintf(name, sizeof(name), "%d", pr->dstats.suicides[DSTAT_LEVEL]);
      t = strlen(name);
      memcpy(&buffer[pos[4]], name, (t < len[4]) ? t : len[4]);

      if (pr->state == STATE_INGAME)
        snprintf(name, sizeof(name), "%.0f", dNetPlayers[pr->pnum].ping_time * 1000.0f);
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
