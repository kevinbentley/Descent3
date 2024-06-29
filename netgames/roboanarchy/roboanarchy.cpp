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

 * $Logfile: /DescentIII/Main/roboanarchy/roboanarchy.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:59:03 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: roboanarchy.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:59:03  kevinb
 * initial 1.5 import
 *
 *
 * 43    10/21/99 3:20p Kevin
 * Macintosh merge
 *
 * 42    7/12/99 1:22p Jeff
 * updated for new netflags
 *
 * 41    7/11/99 6:45p Jeff
 * cleaner plr if the list is too long
 *
 * 40    5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 39    5/12/99 11:28a Jeff
 * added sourcesafe comment block
 *
 * $NoKeywords: $
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "idmfc.h"
#include "roboAnarchy.h"
#include "roboanarchystr.h"

#include <algorithm>

IDMFC *DMFCBase = NULL;
static IDmfcStats *dstat = NULL;

static int SortedPlayers[MAX_PLAYER_RECORDS]; // sorted player nums
static bool DisplayScoreScreen;
static int Highlight_bmp = -1;

#define AHD_NONE 0
#define AHD_SCORE 1
#define AHD_EFFICIENCY 2
#define ACM_PLAYERCOLOR 0
#define ACM_NORMAL 1
static uint8_t Anarchy_hud_display = AHD_SCORE;
static uint8_t HUD_color_model = ACM_PLAYERCOLOR;
static bool display_my_welcome = false;

static void DisplayHUDScores(struct tHUDItem *hitem);
static void DisplayScores(void);
static void DisplayWelcomeMessage(int player_num);
static void SaveStatsToFile(char *filename);
static void SwitchHUDColor(int i);
static void SwitchAnarchyScores(int i);

///////////////////////////////////////////////
// localization info
static char **StringTable;
static int StringTableSize = 0;
static const char *_ErrorString = "Missing String";
const char *GetString(int d) {
  if ((d < 0) || (d >= StringTableSize))
    return _ErrorString;
  else
    return StringTable[d];
}
///////////////////////////////////////////////

void SwitchAnarchyScores(int i) {
  if (i < 0)
    i = 0;
  if (i > 2)
    i = 2;

  Anarchy_hud_display = i;

  switch (i) {
  case AHD_NONE:
    DLLAddHUDMessage(TXT_HUDD_NONE);
    break;
  case AHD_SCORE:
    DLLAddHUDMessage(TXT_HUDD_SCORES);
    break;
  case AHD_EFFICIENCY:
    DLLAddHUDMessage(TXT_HUDD_EFFIC);
    break;
  };
}

// This function gets called by the game when it wants to learn some info about the game
void DLLFUNCCALL DLLGetGameInfo(tDLLOptions *options) {
  options->flags = DOF_MAXTEAMS;
  options->max_teams = 1;
  strcpy(options->game_name, "Anarchy");
  strcpy(options->requirements, "COOP");
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

  // Setup the event handlers that we handle
  DMFCBase->Set_OnKeypress(OnKeypress);
  DMFCBase->Set_OnHUDInterval(OnHUDInterval);
  DMFCBase->Set_OnInterval(OnInterval);
  DMFCBase->Set_OnClientPlayerKilled(OnClientPlayerKilled);
  DMFCBase->Set_OnClientPlayerEntersGame(OnClientPlayerEntersGame);
  DMFCBase->Set_OnClientLevelStart(OnClientLevelStart);
  DMFCBase->Set_OnClientLevelEnd(OnClientLevelEnd);
  DMFCBase->Set_OnServerGameCreated(OnServerGameCreated);
  DMFCBase->Set_OnPLRInterval(OnPLRInterval);
  DMFCBase->Set_OnPLRInit(OnPLRInit);
  DMFCBase->Set_OnSaveStatsToFile(OnSaveStatsToFile);
  DMFCBase->Set_OnLevelEndSaveStatsToFile(OnLevelEndSaveStatsToFile);
  DMFCBase->Set_OnDisconnectSaveStatsToFile(OnDisconnectSaveStatsToFile);
  DMFCBase->Set_OnPrintScores(OnPrintScores);

  DLLCreateStringTable("Anarchy.str", &StringTable, &StringTableSize);
  mprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    *all_ok = 0;
    return;
  }

  AnarchyGameInit(1);

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

  DMFCBase->SetNumberOfTeams(1);

  netgame_info *Netgame = DMFCBase->GetNetgameInfo();
  Netgame->flags |= (NF_DAMAGE_FRIENDLY | NF_USE_ROBOTS | NF_TRACK_RANK);

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

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  DisplayScoreScreen = false;
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
    AnarchyGameClose();
    DMFCBase->GameClose();
    DMFCBase->DestroyPointer();
    DMFCBase = NULL;
  }
}

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }

  snprintf(buffer, buffer_size, "%d", pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL]);
}

void AnarchyGameClose(void) {}

// DMFCApp::GameInit
//
//   Sets up all the DLL functions and pointers and preps the class for use.  This ABSOLUTLY must be
//   called, so if you override DMFCApp::GameInit, make sure that you put a call to this somewhere in
//   the override.
void AnarchyGameInit(int teams) {
  // add the anarchy menu/submenus
  IMenuItem *lev1, *lev2;

  lev1 = CreateMenuItemWArgs("Anarchy", MIT_NORMAL, 0, NULL);

  lev2 = CreateMenuItemWArgs(TXT_MNU_HUDSTYLE, MIT_STATE, 0, SwitchAnarchyScores);
  lev2->SetStateItemList(3, TXT_NONE, TXT_SCOREHD, TXT_EFFICIENCY);
  lev2->SetState(1);
  lev1->AddSubMenu(lev2);

  lev2 = CreateMenuItemWArgs(TXT_MNU_HUDCOLOR, MIT_STATE, 0, SwitchHUDColor);
  lev2->SetStateItemList(2, TXT_PLAYERCOLORS, TXT_NORMAL);
  lev2->SetState(HUD_color_model);
  lev1->AddSubMenu(lev2);

  lev2 = DMFCBase->GetOnScreenMenu();
  lev2->AddSubMenu(lev1);

  DMFCBase->GameInit(teams);

  // Initialize the Stats Manager
  // ----------------------------

  tDmfcStatsInit tsi;
  tDmfcStatsColumnInfo pl_col[6];
  char gname[20];
  strcpy(gname, "Anarchy");

  tsi.flags = DSIF_SHOW_PIC | DSIF_SHOW_OBSERVERICON;
  tsi.cColumnCountDetailed = 0;
  tsi.cColumnCountPlayerList = 6;
  tsi.clbDetailedColumn = NULL;
  tsi.clbDetailedColumnBMP = NULL;
  tsi.clbPlayerColumn = DetermineScore;
  tsi.clbPlayerColumnBMP = NULL;
  tsi.DetailedColumns = NULL;
  tsi.GameName = gname;
  tsi.MaxNumberDisplayed = NULL;
  tsi.PlayerListColumns = pl_col;
  tsi.SortedPlayerRecords = SortedPlayers;

  pl_col[0].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[0].title, TXT_PILOT);
  pl_col[0].type = DSCOL_PILOT_NAME;
  pl_col[0].width = 120;

  pl_col[1].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[1].title, TXT_SCORE);
  pl_col[1].type = DSCOL_CUSTOM;
  pl_col[1].width = 50;

  pl_col[2].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[2].title, TXT_KILLS_SHORT);
  pl_col[2].type = DSCOL_KILLS_LEVEL;
  pl_col[2].width = 50;

  pl_col[3].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[3].title, TXT_DEATHS_SHORT);
  pl_col[3].type = DSCOL_DEATHS_LEVEL;
  pl_col[3].width = 60;

  pl_col[4].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[4].title, TXT_SUICIDES_SHORT);
  pl_col[4].type = DSCOL_SUICIDES_LEVEL;
  pl_col[4].width = 65;

  pl_col[5].color_type = DSCOLOR_SHIPCOLOR;
  strcpy(pl_col[5].title, TXT_PING);
  pl_col[5].type = DSCOL_PING;
  pl_col[5].width = 40;

  dstat->Initialize(&tsi);
}

void OnHUDInterval(void) {
  dstat->DoFrame();
  DMFCBase->DisplayOutrageLogo();
  DMFCBase->OnHUDInterval();
}

void OnInterval(void) {
  DMFCBase->GetSortedPlayerSlots(SortedPlayers, MAX_PLAYER_RECORDS);
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
void OnServerGameCreated(void) { DMFCBase->OnServerGameCreated(); }

// The server has started a new level, so clear out any scores needed to be reset
void OnClientLevelStart(void) {
  for (int i = 0; i < MAX_PLAYER_RECORDS; i++) {
    SortedPlayers[i] = -1;
  }

  DMFCBase->OnClientLevelStart();
}

void OnClientLevelEnd(void) { DMFCBase->OnClientLevelEnd(); }

// A new player has entered the game, zero their stats out
void OnClientPlayerEntersGame(int player_num) {
  DMFCBase->OnClientPlayerEntersGame(player_num);

  if (player_num != DMFCBase->GetPlayerNum())
    DisplayWelcomeMessage(player_num);
  else
    display_my_welcome = true;
}

// We need to adjust the scores
void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
  player_record *kpr;

  int kpnum;

  if (killer_obj) {
    if ((killer_obj->type == OBJ_PLAYER) || (killer_obj->type == OBJ_GHOST))
      kpnum = killer_obj->id;
    else if (killer_obj->type == OBJ_ROBOT || killer_obj->type == OBJ_BUILDING) {
      // countermeasure kill
      kpnum = DMFCBase->GetCounterMeasureOwner(killer_obj);
    } else {
      kpnum = -1;
    }
  } else {
    kpnum = -1;
  }

  kpr = DMFCBase->GetPlayerRecordByPnum(kpnum);
  if (kpr) {
    int goal;
    if (DMFCBase->GetScoreLimit(&goal)) {
      int score = kpr->dstats.kills[DSTAT_LEVEL] - kpr->dstats.suicides[DSTAT_LEVEL];
      if (score >= goal) {
        DMFCBase->EndLevel();
      }
    }
  }
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
  memcpy(SortedPlayers, tempsort, DLLMAX_PLAYERS * sizeof(int));

  DMFCBase->OnPLRInit();
}

void OnPLRInterval(void) {
#define PLAYERS_COL 130
#define SCORE_COL 280
#define DEATHS_COL 330
#define SUICIDES_COL 390
#define TOTAL_COL 460

  DMFCBase->OnPLRInterval();

  int y = 40;

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;
  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(PLAYERS_COL, y, TXT_PILOT);
  DLLgrtext_Printf(SCORE_COL, y, TXT_KILLS_SHORT);
  DLLgrtext_Printf(DEATHS_COL, y, TXT_DEATHS_SHORT);
  DLLgrtext_Printf(SUICIDES_COL, y, TXT_SUICIDES_SHORT);
  DLLgrtext_Printf(TOTAL_COL, y, TXT_SCORE);
  y += height;

  // print out player stats
  int rank = 1;
  int slot, pnum;
  player_record *pr;

  for (int i = 0; i < DLLMAX_PLAYERS; i++) {
    slot = SortedPlayers[i];
    pr = DMFCBase->GetPlayerRecord(slot);
    if ((pr) && (pr->state != STATE_EMPTY)) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip a dedicated server

      pnum = DMFCBase->WasPlayerInGameAtLevelEnd(slot);
      if (pnum != -1) {
        DLLgrtext_SetColor((DMFCBase->GetPlayerColors())[pnum]);
      } else {
        DLLgrtext_SetColor(GR_RGB(128, 128, 128));
      }

      char temp[100];
      snprintf(temp, sizeof(temp), "%d)%s", rank, pr->callsign);
      DMFCBase->ClipString(SCORE_COL - PLAYERS_COL - 10, temp, true);
      DLLgrtext_Printf(PLAYERS_COL, y, "%s", temp);

      DLLgrtext_Printf(SCORE_COL, y, "%d", pr->dstats.kills[DSTAT_LEVEL]);
      DLLgrtext_Printf(DEATHS_COL, y, "%d", pr->dstats.deaths[DSTAT_LEVEL]);
      DLLgrtext_Printf(SUICIDES_COL, y, "%d", pr->dstats.suicides[DSTAT_LEVEL]);
      DLLgrtext_Printf(TOTAL_COL, y, "%d", pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL]);
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
    mprintf(0, "Unable to open output file\n");
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

  snprintf(buffer, sizeof(buffer), TXT_SAVE_HEADER, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVE_HEADERB);
  DLLcf_WriteString(file, buffer);
  strcpy(buffer, "-----------------------------------------------------------------------------------------------");
  DLLcf_WriteString(file, buffer);

  for (int s = 0; s < MAX_PLAYER_RECORDS; s++) {
    p = sortedslots[s];
    pr = DMFCBase->GetPlayerRecord(p);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      memset(buffer, ' ', BUFSIZE);

      snprintf(tempbuffer, sizeof(tempbuffer), "%d)", count);
      memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s%s", (pr->state == STATE_INGAME) ? "" : "*", pr->callsign);
      memcpy(&buffer[7], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]",
               pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL] - pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[36], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.kills[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL]);
      memcpy(&buffer[48], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL],
               pr->dstats.deaths[DSTAT_OVERALL]);
      memcpy(&buffer[60], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[71], tempbuffer, strlen(tempbuffer));

      strcpy(tempbuffer, DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(p)));
      memcpy(&buffer[82], tempbuffer, strlen(tempbuffer));

      size_t pos = 82 + strlen(tempbuffer) + 1;
      if (pos < BUFSIZE)
        buffer[pos] = '\0';

      buffer[BUFSIZE - 1] = '\0';
      DLLcf_WriteString(file, buffer);
      count++;
    }
  }

  DLLcf_WriteString(file, TXT_SAVE_HEADERC);

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
      snprintf(buffer, sizeof(buffer), TXT_SAVE_TIMEINGAME, DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(p)));
      DLLcf_WriteString(file, buffer);

      if (DMFCBase->FindPInfoStatFirst(p, &stat)) {
        snprintf(buffer, sizeof(buffer), "%s", TXT_SAVE_KILLERLIST);
        DLLcf_WriteString(file, buffer);

        if (stat.slot != p) {
          memset(buffer, ' ', BUFSIZE);
          dpr = DMFCBase->GetPlayerRecord(stat.slot);

          ASSERT(dpr != NULL);
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
  DLLAddHUDMessage(TXT_MSG_SAVESTATS);
}

#define ROOTFILENAME "Anarchy"
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

void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    DisplayWelcomeMessage(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (DisplayScoreScreen)
    return;

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX]) + 3;
  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)((DisplayScoreScreen) ? 128 : 255));
  int y = (DMFCBase->GetGameWindowH() / 2) - ((height * 5) / 2);
  int x = 520;
  ddgr_color color;

  int rank = 1;
  player_record *pr;

  // Display your Kills & Deaths on the top corners of the screen
  pr = DMFCBase->GetPlayerRecordByPnum(DMFCBase->GetPlayerNum());
  if (pr) {
    int y = 25, x;
    int lwidth;
    char buffer[20];

    int w_kill, w_death, max_w;
    w_kill = DLLgrtext_GetTextLineWidth(TXT_KILLS);
    w_death = DLLgrtext_GetTextLineWidth(TXT_DEATHS);
    max_w = std::max(w_kill, w_death);

    x = DMFCBase->GetGameWindowW() - DMFCBase->GetGameWindowW() * 0.0078125f;
    DLLgrtext_SetColor(GR_GREEN);
    DLLgrtext_SetAlpha(alpha);
    DLLgrtext_Printf(x - (max_w / 2) - (w_kill / 2), y, TXT_KILLS);
    y += height;

    snprintf(buffer, sizeof(buffer), "%d", pr->dstats.kills[DSTAT_LEVEL]);
    lwidth = DLLgrtext_GetTextLineWidth(buffer);
    DLLgrtext_SetColor(GR_GREEN);
    DLLgrtext_SetAlpha(alpha);
    DLLgrtext_Printf(x - (max_w / 2) - (lwidth / 2), y, buffer);
    y += height + 3;

    DLLgrtext_SetColor(GR_GREEN);
    DLLgrtext_SetAlpha(alpha);
    DLLgrtext_Printf(x - (max_w / 2) - (w_death / 2), y, TXT_DEATHS);
    y += height;

    snprintf(buffer, sizeof(buffer), "%d", pr->dstats.deaths[DSTAT_LEVEL]);
    lwidth = DLLgrtext_GetTextLineWidth(buffer);
    DLLgrtext_SetColor(GR_GREEN);
    DLLgrtext_SetAlpha(alpha);
    DLLgrtext_Printf(x - (max_w / 2) - (lwidth / 2), y, buffer);
  }

  int ESortedPlayers[DLLMAX_PLAYERS] = {};

  switch (Anarchy_hud_display) {
  case AHD_NONE:
    return;
    break;
  case AHD_EFFICIENCY:
    DMFCBase->GetSortedPlayerSlots(ESortedPlayers, DLLMAX_PLAYERS);
    break;
  }

  char name[30];

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 85.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;

  for (int i = 0; i < DLLMAX_PLAYERS; i++) {
    int slot;

    if (Anarchy_hud_display == AHD_EFFICIENCY)
      slot = ESortedPlayers[i];
    else
      slot = SortedPlayers[i];

    pr = DMFCBase->GetPlayerRecord(slot);

    if ((pr) && (pr->state != STATE_EMPTY)) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      if ((pr->state == STATE_DISCONNECTED) || (pr->state == STATE_INGAME && !DMFCBase->IsPlayerObserver(pr->pnum))) {

        if (pr->pnum == DMFCBase->GetPlayerNum()) {

          switch (HUD_color_model) {
          case ACM_PLAYERCOLOR:
            color = (DMFCBase->GetPlayerColors())[pr->pnum];
            break;
          case ACM_NORMAL:
            color = GR_RGB(40, 255, 40);
            break;
          };

          if (Highlight_bmp > BAD_BITMAP_HANDLE) {
            // draw the highlite bar in the background
            DLLrend_SetAlphaValue(alpha * 0.50f);
            DLLrend_SetZBufferState(0);
            DLLrend_SetTextureType(TT_LINEAR);
            DLLrend_SetLighting(LS_NONE);
            DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);
            DLLrend_DrawScaledBitmap(name_x - 2, y - 2, score_x + score_width + 2, y + height - 1, Highlight_bmp, 0, 0,
                                     1, 1, 1.0, -1, NULL);
            DLLrend_SetZBufferState(1);
          }

          strcpy(name, pr->callsign);
          DMFCBase->ClipString(name_width, name, true);

          DLLgrtext_SetAlpha(alpha);
          DLLgrtext_SetColor(color);
          DLLgrtext_Printf(name_x, y, "%s", name);

          if (Anarchy_hud_display == AHD_EFFICIENCY) {
            float t = pr->dstats.kills[DSTAT_LEVEL] + pr->dstats.suicides[DSTAT_LEVEL] + pr->dstats.deaths[DSTAT_LEVEL];
            float value = (float)(pr->dstats.kills[DSTAT_LEVEL]) / ((t) ? t : 0.0000001f);
            DLLgrtext_Printf(score_x, y, "%.1f", value);
          } else {
            DLLgrtext_Printf(score_x, y, "%d", pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL]);
          }

          y += height;
        } else if (rank < 6) {

          if (pr->state == STATE_DISCONNECTED) {
            color = GR_GREY;
          } else {
            switch (HUD_color_model) {
            case ACM_PLAYERCOLOR:
              color = (DMFCBase->GetPlayerColors())[pr->pnum];
              break;
            case ACM_NORMAL:
              color = GR_RGB(40, 255, 40);
              break;
            };
          }
          strcpy(name, pr->callsign);
          DMFCBase->ClipString(name_width, name, true);

          DLLgrtext_SetAlpha(alpha);
          DLLgrtext_SetColor(color);
          DLLgrtext_Printf(name_x, y, "%s", name);

          if (Anarchy_hud_display == AHD_EFFICIENCY) {
            float t = pr->dstats.kills[DSTAT_LEVEL] + pr->dstats.suicides[DSTAT_LEVEL] + pr->dstats.deaths[DSTAT_LEVEL];
            float value = (float)(pr->dstats.kills[DSTAT_LEVEL]) / ((t) ? t : 0.0000001f);
            DLLgrtext_Printf(score_x, y, "%.1f", value);
          } else {
            DLLgrtext_Printf(score_x, y, "%d", pr->dstats.kills[DSTAT_LEVEL] - pr->dstats.suicides[DSTAT_LEVEL]);
          }

          y += height;
        }
        rank++;
      }
    }
  }
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

void SwitchHUDColor(int i) {
  if (i < 0 || i > 1)
    return;
  HUD_color_model = i;

  switch (HUD_color_model) {
  case ACM_PLAYERCOLOR:
    DLLAddHUDMessage(TXT_MSG_COLORPLR);
    break;
  case ACM_NORMAL:
    DLLAddHUDMessage(TXT_MSG_COLORNORM);
    break;
  };
}
