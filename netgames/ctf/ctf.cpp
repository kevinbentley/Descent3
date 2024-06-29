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

 * $Logfile: /DescentIII/Main/ctf/ctf.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:56:47 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: ctf.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:56:47  kevinb
 * initial 1.5 import
 *
 *
 * 140   10/03/01 1:05p Matt
 * Made team_name buffer large enough to hold the team number *plus* the
 * number of players on the team.
 *
 * 139   9/24/01 2:28p Matt
 * Allowed room for longer team name on results screen.
 *
 * 138   9/20/01 12:58p Matt
 * Added a team member list to the stats file.
 *
 * 137   10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 136   9/03/99 5:30p Jeff
 * use the flag's roomnumber instead of the player's roomnum when checking
 * for a score (in case of a really thin room that the flag is in)
 *
 * 135   8/17/99 5:53p Jeff
 * track ranks on PXO
 *
 * 134   7/15/99 1:17a Jeff
 * fixed up $scores
 *
 * 133   7/13/99 12:10p Jeff
 * added some specific text taunt token decoding
 *
 * 132   7/12/99 2:27p Jeff
 * fixed PLR to only display the team label for the disconnected list if
 * there are people in the list
 *
 * 131   7/11/99 6:54p Jeff
 * fixed PLR so it doesn't go off the screen on long lists and active
 * players in the game are shown first
 *
 * 130   6/10/99 5:21p Jeff
 * fixed crash in french version, due to local array being to small
 *
 * 129   5/26/99 4:38a Jeff
 * fixed ctf bad scoring bugs
 *
 * 128   5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 127   5/20/99 7:54p 3dsmax
 * changed number of attach points
 *
 * 126   5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 125   5/12/99 11:28a Jeff
 * added sourcesafe comment block
 *
 * $NoKeywords: $
 */

#include "gamedll_header.h"
#include <string.h>

#include "idmfc.h"
#include "ctf.h"
#include "CTFstr.h"

IDMFC *DMFCBase;
static IDmfcStats *dstat;

static object *dObjects;
static player *dPlayers;
static room *dRooms;
static netplayer *dNetPlayers;

#define SPID_GAMESTATE 0x01
#define SPID_ADDDELFLAG 0x02
#define SPID_COLLIDE 0x03

// Inventory flags
#define FLAGMASK_REDTEAM 0x01
#define FLAGMASK_BLUETEAM 0x02
#define FLAGMASK_GREENTEAM 0x04
#define FLAGMASK_YELLOWTEAM 0x08

// athome masks
#define REDAH 0x001
#define BLUEAH 0x002
#define GREENAH 0x004
#define YELLOWAH 0x008

#define FLAG_TIMEOUT_VALUE 120
// Sound name defines
#define SOUND_PICKUPFLAG_OWNTEAM "CTFPickupFlag1"
#define SOUND_PICKUPFLAG_OTHERTEAM "CTFPickupFlag1"
#define SOUND_SCORE_OWNTEAM "CTFScore1"
#define SOUND_SCORE_OTHERTEAM "CTFScore1"
#define SOUND_LOSEFLAG_OWNTEAM "CTFLostFlag1"
#define SOUND_LOSEFLAG_OTHERTEAM "CTFLostFlag1"
#define SOUND_FLAGRETURNED_OWNTEAM "CTFReturnedFlag1"
#define SOUND_FLAGRETURNED_OTHERTEAM "CTFReturnedFlag1"
#define SOUND_HATTRICK_FIRST "CTFHatTrick"
#define SOUND_HATTRICK_REGULAR "CTFHatTrick"
/*
$$TABLE_SOUND "CTFPickupFlag1"
$$TABLE_SOUND "CTFPickupFlag1"
$$TABLE_SOUND "CTFScore1"
$$TABLE_SOUND "CTFScore1"
$$TABLE_SOUND "CTFLostFlag1"
$$TABLE_SOUND "CTFLostFlag1"
$$TABLE_SOUND "CTFReturnedFlag1"
$$TABLE_SOUND "CTFReturnedFlag1"
$$TABLE_SOUND "CTFHatTrick"
$$TABLE_SOUND "CTFHatTrick"
*/
static int snd_return_ownteam = -1;
static int snd_return_otherteam = -1;
static int snd_pickedup_otherteam = -1;
static int snd_pickedup_ownteam = -1;
static int snd_score_ownteam = -1;
static int snd_score_otherteam = -1;
static int snd_lose_ownteam = -1;
static int snd_lose_otherteam = -1;
static int snd_hattrick_first = -1;
static int snd_hattrick_reg = -1;

struct tPlayerStat { // Overall scores (throughout the game)
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

static int SortedPlayers[MAX_PLAYER_RECORDS]; // sorted player nums
static int SortedPLRPlayers[DLLMAX_TEAMS][MAX_PLAYER_RECORDS];

static int TeamScores[DLLMAX_TEAMS];        // teams scores
static int OverallTeamScores[DLLMAX_TEAMS]; // overall scores per team
static int SortedTeams[DLLMAX_TEAMS];       // sorted team scores
static int Highlight_bmp = -1;
static bool DisplayScoreScreen;
static bool Someone_has_hattrick = false; // this is false if no one has had a hattrick this level
static bool First_game_frame = false;

static int FlagIDs[DLLMAX_TEAMS];      // Flag Object ID's
static int AFlagIDs[DLLMAX_TEAMS];     // Attached Flag Object ID's
static int GoalRooms[DLLMAX_TEAMS];    // Goal Rooms for Teams
static int FlagBmp[DLLMAX_TEAMS];      // Flag Bitmap handles
static int FlagAHBmp[DLLMAX_TEAMS];    // Flag At Home Bitmap handles
static int DimFlagAHBmp[DLLMAX_TEAMS]; // Dimmed versions of the Flag At Home Bitmaps
static bool FlagAtHome[DLLMAX_TEAMS];  // Flag At Home bools
static int HasFlag[DLLMAX_TEAMS];      // List of Playernums of who has what flag, -1 if no one does
static bool DisplayFlagBlink = true, DisplayScoreBlink = true;
static int WhoJustFlagged = -1, WhoJustFlaggedTimer = -1;
static int WhoJustScored = -1, WhoJustScoredTimer = -1;
static int CTFNumOfTeams = 2;
static int ChildFlags[DLLMAX_TEAMS]; // Object handles of attached flags as a player has em

static float Flag_timeout_timers[DLLMAX_TEAMS];
static bool display_my_welcome = false;

static void OnTimerScoreKill(void);                        // timer callback: when a score flash timer ends
static void OnTimerScore(void);                            // timer callback: on a score flash interval
static void OnTimer(void);                                 // timer callback: when a flag taken flash timer ends
static void OnTimerKill(void);                             // timer callback: on a flag taken flash interval
static void DisplayWelcomeMessage(int player_num);         // displays a welcome message to the player when he joins
static void SortTeamScores(int *sortedindex, int *scores); // sorts an array of team scores, filling in the sorted index
                                                           // numbers
static void DisplayHUDScores(struct tHUDItem *hitem);      // callback when the HUD info is to be drawn
static void ReceiveGameState(uint8_t *data); // callback when a gamestate packet is received from the server
static void SendGameState(int playernum);  // called when the server is to send gamestate packet to a client
static void SetColoredBalls(
    int playernum,
    bool reset = false); // sets the colored balls around a player (determined by what is in their inventory)
static void ChangeNumberOfTeams(int newsize); // called when the number of teams in the game is changed or to be changed
static void DoFlagReturnedHome(int team);     // called to handle any events when a flag is returned home for a team
static void DoLoseFlag(int team);             // called to handle any events when a team loses their flag
static void TellClientsToAddorDelFlag(int pnum, int team, int objnum, bool add);
static void ServerIsTellingMeToAddorDelAFlag(uint8_t *data);
static void OnGetTokenString(char *src, char *dest, int dest_size);
// returns the number of flags a player has, 0 if none, or an invalid pnum
static int GetFlagCountForPlayer(int pnum);
// returns the mask of which flags this player currently has
static uint8_t GetFlagMaskForPlayer(int pnum);
//	adds a flag to a player, as a precaution, it will go through all the players and makes sure that no one
//	has the flag that is being added.  If they are adding the flag, than remove that flag from whoever we thought
// had it 	it will return false if it had to remove a flag from a player
static bool GivePlayerFlag(int pnum, uint8_t team);
// this function takes a flag away from the player, useful for when he scores, spews, disconnects, or observer modes
static void LoseFlagForPlayer(int pnum, uint8_t team, bool remove_from_inven = true);

///////////////////////////////////////////////
// localization info/functions
static char **StringTable;
static int StringTableSize = 0;
static const char *_ErrorString = "Missing String";
const char *GetString(int d) {
  if ((d < 0) || (d >= StringTableSize))
    return _ErrorString;
  else
    return StringTable[d];
}
static void SaveStatsToFile(char *filename);
static void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size);
static void ShowStatBitmap(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use);

// This function gets called by the game when it wants to learn some info about the game
void DLLFUNCCALL DLLGetGameInfo(tDLLOptions *options) {
  options->flags = DOF_MAXTEAMS | DOF_MINTEAMS;
  options->max_teams = 4;
  options->min_teams = 2;
  strcpy(options->game_name, TXT_CTF);
  strcpy(options->requirements, "MINGOALS2,GOALPERTEAM");
}

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }

  tPlayerStat *stat = (tPlayerStat *)pr->user_info;
  snprintf(buffer, buffer_size, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
}

void TeamScoreCallback(int team, char *buffer, int buffer_size) {
  ASSERT(team >= 0 && team < DLLMAX_TEAMS);

  snprintf(buffer, buffer_size, " %d", TeamScores[team]);
}

void ShowStatBitmap(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  int flagcount, flagmask;

  if (pr && pr->state == STATE_INGAME) {

    flagcount = GetFlagCountForPlayer(pr->pnum);

    if (!flagcount)
      return;

    flagmask = GetFlagMaskForPlayer(pr->pnum);

    // Display the flags that this player has
    x = x + w - (11 * flagcount);
    for (int q = 0; q < CTFNumOfTeams; q++) {
      // draw all the flags the player has in his inventory
      if (flagmask & 0x01) {
        // player has this flag
        DLLRenderHUDQuad(x, y, 10, 10, 0, 0, 1, 1, FlagBmp[q], alpha_to_use, 0);
        x += 11;
      }

      // rotate 1 bit for next flag
      flagmask = flagmask >> 1;
    }
  }
}

///////////////////////////////////////////////
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
  DMFCBase->Set_OnClientPlayerKilled(OnClientPlayerKilled);
  DMFCBase->Set_OnServerCollide(OnServerCollide);
  // DMFCBase->Set_OnClientCollide(OnClientCollide);
  DMFCBase->Set_OnPLRInterval(OnPLRInterval);
  DMFCBase->Set_OnPLRInit(OnPLRInit);
  DMFCBase->Set_OnCanChangeTeam(OnCanChangeTeam);
  DMFCBase->Set_OnSaveStatsToFile(OnSaveStatsToFile);
  DMFCBase->Set_OnLevelEndSaveStatsToFile(OnLevelEndSaveStatsToFile);
  DMFCBase->Set_OnDisconnectSaveStatsToFile(OnDisconnectSaveStatsToFile);
  DMFCBase->Set_OnPrintScores(OnPrintScores);
  DMFCBase->Set_OnPlayerEntersObserver(OnPlayerEntersObserver);
  DMFCBase->Set_OnClientPlayerDisconnect(OnClientPlayerDisconnect);
  DMFCBase->Set_OnPlayerChangeTeam(OnPlayerChangeTeam);
  DMFCBase->Set_OnGetTokenString(OnGetTokenString);

  // Setup arrays for easier to read code
  dObjects = DMFCBase->GetObjects();
  dPlayers = DMFCBase->GetPlayers();
  dRooms = DMFCBase->GetRooms();
  dNetPlayers = DMFCBase->GetNetPlayers();

  netgame_info *Netgame = DMFCBase->GetNetgameInfo();
  Netgame->flags |= (NF_TRACK_RANK);

  CTFNumOfTeams = num_teams_to_use;

  DMFCBase->GameInit(CTFNumOfTeams);
  DLLCreateStringTable("CTF.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    *all_ok = 0;
    return;
  }

  ChangeNumberOfTeams(CTFNumOfTeams);

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

  // setup the Playerstats struct so DMFC can handle it automatically when a new player enters the game
  DMFCBase->SetupPlayerRecord(sizeof(tPlayerStat), (int (*)(void *, uint8_t *))pack_pstat,
                              (int (*)(void *, uint8_t *))unpack_pstat);

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  DMFCBase->RegisterPacketReceiver(SPID_GAMESTATE, ReceiveGameState);
  DMFCBase->RegisterPacketReceiver(SPID_ADDDELFLAG, ServerIsTellingMeToAddorDelAFlag);
  DMFCBase->RegisterPacketReceiver(SPID_COLLIDE, OnClientCollide);

  // Load all the bitmaps
  FlagBmp[RED_TEAM] = DLLbm_AllocLoadFileBitmap("RedFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  FlagBmp[BLUE_TEAM] = DLLbm_AllocLoadFileBitmap("BlueFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  FlagBmp[GREEN_TEAM] = DLLbm_AllocLoadFileBitmap("GreenFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  FlagBmp[YELLOW_TEAM] = DLLbm_AllocLoadFileBitmap("YellowFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  // athome bitmaps
  FlagAHBmp[RED_TEAM] = DLLbm_AllocLoadFileBitmap("RedFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  FlagAHBmp[BLUE_TEAM] = DLLbm_AllocLoadFileBitmap("BlueFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  FlagAHBmp[GREEN_TEAM] = DLLbm_AllocLoadFileBitmap("GreenFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  FlagAHBmp[YELLOW_TEAM] = DLLbm_AllocLoadFileBitmap("YellowFlagIcon.ogf", 0, BITMAP_FORMAT_1555);
  DimFlagAHBmp[RED_TEAM] = DLLbm_AllocLoadFileBitmap("RedFlagIconDim.ogf", 0, BITMAP_FORMAT_1555);
  DimFlagAHBmp[BLUE_TEAM] = DLLbm_AllocLoadFileBitmap("BlueFlagIconDim.ogf", 0, BITMAP_FORMAT_1555);
  DimFlagAHBmp[GREEN_TEAM] = DLLbm_AllocLoadFileBitmap("GreenFlagIconDim.ogf", 0, BITMAP_FORMAT_1555);
  DimFlagAHBmp[YELLOW_TEAM] = DLLbm_AllocLoadFileBitmap("YellowFlagIconDim.ogf", 0, BITMAP_FORMAT_1555);
  // fill in the IDs

  FlagIDs[RED_TEAM] = DLLFindObjectIDName("FlagRed");
  FlagIDs[BLUE_TEAM] = DLLFindObjectIDName("Flagblue");
  FlagIDs[GREEN_TEAM] = DLLFindObjectIDName("FlagGreen");
  FlagIDs[YELLOW_TEAM] = DLLFindObjectIDName("FlagYellow");
  AFlagIDs[RED_TEAM] = DLLFindObjectIDName("ShipRedFlag");
  AFlagIDs[BLUE_TEAM] = DLLFindObjectIDName("ShipBlueFlag");
  AFlagIDs[GREEN_TEAM] = DLLFindObjectIDName("ShipGreenFlag");
  AFlagIDs[YELLOW_TEAM] = DLLFindObjectIDName("ShipYellowFlag");

  // give initial values for the at home so they're set
  FlagAtHome[RED_TEAM] = FlagAtHome[BLUE_TEAM] = FlagAtHome[GREEN_TEAM] = FlagAtHome[YELLOW_TEAM] = false;

  // make sure all was init ok
  for (int i = 0; i < DLLMAX_TEAMS; i++) {
    if ((FlagBmp[i] <= BAD_BITMAP_HANDLE) || (FlagAHBmp[i] <= BAD_BITMAP_HANDLE) ||
        (DimFlagAHBmp[i] <= BAD_BITMAP_HANDLE) || (FlagIDs[i] < 0) || (AFlagIDs[i] < 0)) {
      *all_ok = 0;
      return;
    }
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

  // Load in and touch all the sounds so they're ready to rock
  snd_score_ownteam = DLLFindSoundName(IGNORE_TABLE(SOUND_SCORE_OWNTEAM));
  if (snd_score_ownteam != -1)
    DLLTouchSound(snd_score_ownteam);
  snd_score_otherteam = DLLFindSoundName(IGNORE_TABLE(SOUND_SCORE_OTHERTEAM));
  if (snd_score_otherteam != -1)
    DLLTouchSound(snd_score_otherteam);
  snd_pickedup_otherteam = DLLFindSoundName(IGNORE_TABLE(SOUND_PICKUPFLAG_OWNTEAM));
  if (snd_pickedup_otherteam != -1)
    DLLTouchSound(snd_pickedup_otherteam);
  snd_pickedup_ownteam = DLLFindSoundName(IGNORE_TABLE(SOUND_PICKUPFLAG_OTHERTEAM));
  if (snd_pickedup_ownteam != -1)
    DLLTouchSound(snd_pickedup_ownteam);
  snd_return_ownteam = DLLFindSoundName(IGNORE_TABLE(SOUND_FLAGRETURNED_OWNTEAM));
  if (snd_return_ownteam != -1)
    DLLTouchSound(snd_return_ownteam);
  snd_return_otherteam = DLLFindSoundName(IGNORE_TABLE(SOUND_FLAGRETURNED_OTHERTEAM));
  if (snd_return_otherteam != -1)
    DLLTouchSound(snd_return_otherteam);
  snd_lose_ownteam = DLLFindSoundName(IGNORE_TABLE(SOUND_LOSEFLAG_OWNTEAM));
  if (snd_lose_ownteam != -1)
    DLLTouchSound(snd_lose_ownteam);
  snd_lose_otherteam = DLLFindSoundName(IGNORE_TABLE(SOUND_LOSEFLAG_OTHERTEAM));
  if (snd_lose_otherteam != -1)
    DLLTouchSound(snd_lose_otherteam);
  snd_hattrick_first = DLLFindSoundName(IGNORE_TABLE(SOUND_HATTRICK_FIRST));
  if (snd_hattrick_first != -1)
    DLLTouchSound(snd_hattrick_first);
  snd_hattrick_reg = DLLFindSoundName(IGNORE_TABLE(SOUND_HATTRICK_REGULAR));
  if (snd_hattrick_reg != -1)
    DLLTouchSound(snd_hattrick_reg);

  DisplayScoreScreen = false;

  // Initialize the Stats Manager
  // ----------------------------

  tDmfcStatsInit tsi;
  tDmfcStatsColumnInfo pl_col[7];
  char gname[32];
  strcpy(gname, TXT_CTF);

  tsi.flags = DSIF_SHOW_PIC | DSIF_SHOW_OBSERVERICON | DSIF_SEPERATE_BY_TEAM;
  tsi.cColumnCountDetailed = 0;
  tsi.cColumnCountPlayerList = 7;
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
  pl_col[0].width = 33;

  pl_col[1].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[1].title, TXT_PILOT);
  pl_col[1].type = DSCOL_PILOT_NAME;
  pl_col[1].width = 120;

  pl_col[2].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[2].title, TXT_POINTS);
  pl_col[2].type = DSCOL_CUSTOM;
  pl_col[2].width = 52;

  pl_col[3].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[3].title, TXT_KILLS_SHORT);
  pl_col[3].type = DSCOL_KILLS_LEVEL;
  pl_col[3].width = 47;

  pl_col[4].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[4].title, TXT_DEATHS_SHORT);
  pl_col[4].type = DSCOL_DEATHS_LEVEL;
  pl_col[4].width = 47;

  pl_col[5].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[5].title, TXT_SUICIDES_SHORT);
  pl_col[5].type = DSCOL_SUICIDES_LEVEL;
  pl_col[5].width = 47;

  pl_col[6].color_type = DSCOLOR_TEAM;
  strcpy(pl_col[6].title, TXT_PING);
  pl_col[6].type = DSCOL_PING;
  pl_col[6].width = 40;

  dstat->Initialize(&tsi);
}
// Called when the DLL is shutdown
void DLLFUNCCALL DLLGameClose() {
  //@@SaveConfig();
  //@@DMFCBase->CFGClose();

  // Free all the bitmaps
  DLLbm_FreeBitmap(FlagBmp[RED_TEAM]);
  DLLbm_FreeBitmap(FlagBmp[BLUE_TEAM]);
  DLLbm_FreeBitmap(FlagBmp[GREEN_TEAM]);
  DLLbm_FreeBitmap(FlagBmp[YELLOW_TEAM]);
  DLLbm_FreeBitmap(DimFlagAHBmp[RED_TEAM]);
  DLLbm_FreeBitmap(DimFlagAHBmp[BLUE_TEAM]);
  DLLbm_FreeBitmap(DimFlagAHBmp[GREEN_TEAM]);
  DLLbm_FreeBitmap(DimFlagAHBmp[YELLOW_TEAM]);
  DLLbm_FreeBitmap(FlagAHBmp[RED_TEAM]);
  DLLbm_FreeBitmap(FlagAHBmp[BLUE_TEAM]);
  DLLbm_FreeBitmap(FlagAHBmp[GREEN_TEAM]);
  DLLbm_FreeBitmap(FlagAHBmp[YELLOW_TEAM]);

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

/////////////////////////////////////////////////////////////
// DMFC Overrides

// OnHUDInterval
void OnHUDInterval(void) {
  dstat->DoFrame();

  DMFCBase->DisplayOutrageLogo();

  DMFCBase->OnHUDInterval();
}

// OnInterval
void OnInterval(void) {
  DMFCBase->GetSortedPlayerSlots(SortedPlayers, MAX_PLAYER_RECORDS);

  SortTeamScores(SortedTeams, TeamScores);

  // Determine if a flag has timed out yet
  for (int i = 0; i < CTFNumOfTeams; i++) {
    if ((HasFlag[i] == -1) && (!FlagAtHome[i])) {
      // check the time out values
      if (DMFCBase->GetGametime() >= Flag_timeout_timers[i]) {
        // the timeout has expired, move home!
        vector home_pos;
        int home, objnum;

        Flag_timeout_timers[i] = 0;
        FlagAtHome[i] = true;
        HasFlag[i] = -1;
        home = GoalRooms[i];
        objnum = -1;

        // find the flag objnum
        for (int o = 0; o < MAX_OBJECTS; o++) {
          if (dObjects[o].type == OBJ_POWERUP && dObjects[o].id == FlagIDs[i]) {
            // found it
            objnum = o;
            break;
          }
        }

        if (objnum == -1) {
          // hmm couldn't find the flag
          // this is messed up...will create the flag on the server and all will be happy
          if (DMFCBase->GetLocalRole() == LR_SERVER) {
            int flagid = FlagIDs[i];
            if ((flagid != -1) && (home >= 0) && (home <= DMFCBase->GetHighestRoomIndex()) &&
                (!ROOMNUM_OUTSIDE(home)) && (dRooms[home].used)) {
              // Safe to create the flag
              DLLComputeRoomCenter(&home_pos, &dRooms[home]);
              objnum = DLLObjCreate(OBJ_POWERUP, flagid, home, &home_pos, NULL, OBJECT_HANDLE_NONE);
              DLLMultiSendObject(&dObjects[objnum], 0, true);
            }
          }
        } else {
          if ((home >= 0) && (home <= DMFCBase->GetHighestRoomIndex()) && (!ROOMNUM_OUTSIDE(home)) &&
              (dRooms[home].used)) {
            DLLComputeRoomCenter(&home_pos, &dRooms[home]);
            DLLObjSetPos(&dObjects[objnum], &home_pos, home, NULL, false);
          }
        }
      }
    }
  }

  DMFCBase->OnInterval();

  First_game_frame = true;
}

// OnKeypress
// What it needs to do:
//   1) Test for F7 keypress
void OnKeypress(int key) {
  dllinfo *Data;
  Data = DMFCBase->GetDLLInfoCallData();

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

// OnServerGameCreated
// What it needs to do:
//   1) Zero out all the stats for every player
//   2) Zero out team scores
//   3) Display welcome message to server
void OnServerGameCreated(void) {
  DMFCBase->OnServerGameCreated();
  tPlayerStat *stat;
  player_record *pr;
  int i;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    pr = DMFCBase->GetPlayerRecord(i);
    if (pr) {
      stat = (tPlayerStat *)pr->user_info;
      if (stat) {
        stat->Score[DSTAT_LEVEL] = 0;
        stat->Score[DSTAT_OVERALL] = 0;
      }
    }
  }
  for (i = 0; i < CTFNumOfTeams; i++) {
    TeamScores[i] = 0;
    OverallTeamScores[i] = 0;
  }
}

// OnClientLevelStart
// What it needs to do:
//    1) Zero out level scores for everyone
//    2) Reset colored balls
//    3) Zero out team scores
//    4) Set number of teams
//    5) If we are the server, create the flags and send them to the clients
void OnClientLevelStart(void) {
  int i;

  DMFCBase->OnClientLevelStart();

  First_game_frame = false;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    SortedPlayers[i] = -1;
  }
  for (i = 0; i < DLLMAX_TEAMS; i++) {

    SortedTeams[i] = -1;
    Flag_timeout_timers[i] = 0;
    ChildFlags[i] = OBJECT_HANDLE_NONE;
  }

  Someone_has_hattrick = false;

  tPlayerStat *stat;
  player_record *pr;
  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    pr = DMFCBase->GetPlayerRecord(i);
    if (pr) {
      stat = (tPlayerStat *)pr->user_info;
      if (stat) {
        stat->Score[DSTAT_LEVEL] = 0;
      }
    }
  }
  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    SetColoredBalls(i, true);
  }

  // fill in the goal room #'s
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    GoalRooms[i] = DLLGetGoalRoomForTeam(i);
    FlagAtHome[i] = true;
    HasFlag[i] = -1;
    TeamScores[i] = 0;
  }

  DMFCBase->SetNumberOfTeams(CTFNumOfTeams);
  DLLMultiPaintGoalRooms(NULL);

  // Bash the inventory since it doesn't get reset for the server
  DLLInvReset(DMFCBase->GetPlayerNum(), true);

  // Display our welcome message
  display_my_welcome = true;

  // If we are the server create the flags
  if (DMFCBase->GetLocalRole() != LR_SERVER) {
    // Get the game state
    DMFCBase->RequestGameState();
    return;
  }

  vector vpos;
  int objnum;
  int flagid, goalroom;

  for (i = 0; i < CTFNumOfTeams; i++) {
    flagid = FlagIDs[i];
    goalroom = GoalRooms[i];
    if ((flagid != -1) && (goalroom >= 0) && (goalroom <= DMFCBase->GetHighestRoomIndex()) &&
        (!ROOMNUM_OUTSIDE(goalroom)) && (dRooms[goalroom].used)) {
      // Safe to create the flag
      DLLmprintf(0, "Creating %s Flag\n", DMFCBase->GetTeamString(i));
      DLLComputeRoomCenter(&vpos, &dRooms[goalroom]);
      objnum = DLLObjCreate(OBJ_POWERUP, flagid, goalroom, &vpos, NULL, OBJECT_HANDLE_NONE);
      DLLMultiSendObject(&dObjects[objnum], 0, true);
    }
  }
}

// OnServerCollide
// What it needs to do:
//   1) See if the player has collided with a flag, if so pass to clients
void OnServerCollide(object *me_obj, object *it_obj) {
  // see if we need to send this event to the clients
  // only if me==player it==flag powerup
  if (!me_obj || !it_obj)
    return;
  if ((me_obj->type == OBJ_PLAYER || me_obj->type == OBJ_GHOST) && (it_obj->type == OBJ_POWERUP))
    if ((it_obj->id == FlagIDs[RED_TEAM]) || (it_obj->id == FlagIDs[BLUE_TEAM]) ||
        (it_obj->id == FlagIDs[GREEN_TEAM]) || (it_obj->id == FlagIDs[YELLOW_TEAM])) {

      // Start a packet for the collide
      uint8_t data[MAX_GAME_DATA_SIZE];
      int count = 0;
      DMFCBase->StartPacket(data, SPID_COLLIDE, &count);
      int start = count;

      // we need me, it and me roomnum
      MultiAddUshort((me_obj - dObjects), data, &count);
      MultiAddUshort((it_obj - dObjects), data, &count);
      MultiAddInt(it_obj->roomnum, data, &count);

      DMFCBase->SendPacket(data, count, SP_ALL);
      OnClientCollide(&data[start]);
    }
}

// OnClientCollide
//  What it needs to do:
//    1) See if Player collided with own flag
//       1.1) Check to see if in home goal
//         1.1.1) Reset colored balls
//         1.1.2) Remove all the flags from the inventory, send them back to their home goal
//         1.1.3) Add scores
//         1.1.4) Print out score
//         1.1.5) Do Kill Goal check
//       1,2) Move home flag to center of base
//    2) else collide with another team's flag
//       2.1) Add flag to inventory
//       2.2) Set rotating balls
//       2.3) Print out message
void OnClientCollide(uint8_t *data) {
  object *me_obj, *it_obj;
  int me_roomnum;
  int count = 0;
  int me_serv_objnum, it_serv_objnum, me_client_objnum, it_client_objnum;

  me_serv_objnum = MultiGetUshort(data, &count);
  it_serv_objnum = MultiGetUshort(data, &count);
  me_roomnum = MultiGetInt(data, &count);

  me_client_objnum = DMFCBase->ConvertServerToLocalObjnum(me_serv_objnum);
  it_client_objnum = DMFCBase->ConvertServerToLocalObjnum(it_serv_objnum);

  if (me_client_objnum == -1 || it_client_objnum == -1) {
    Int3();
    return;
  }

  me_obj = &dObjects[me_client_objnum];
  it_obj = &dObjects[it_client_objnum];

  // now process the collide

  int fteam = -1;                            // flags team
  int pnum = me_obj->id;                     // player number
  int pteam = DMFCBase->GetPlayerTeam(pnum); // player's team
  int i;
  bool play_return_home_msg = false;

  for (i = 0; i < CTFNumOfTeams; i++) {
    if (it_obj->id == FlagIDs[i])
      fteam = i;
  }

  if (fteam == -1) {
    return; // something wrong, as none of the IDs are one of the flag's IDs
  }

  // Reset the timer for this flag since it's guaranteed someone owns it now
  // or it has been sent home.
  Flag_timeout_timers[fteam] = 0;

  // Did player collide with his own team's flag?
  if (fteam == pteam) {
    int16_t flag_count = 0;
    vector fpos;
    int groom;
    int flagcount;
    int flagmask;

    bool captured_flags[DLLMAX_TEAMS];
    for (i = 0; i < DLLMAX_TEAMS; i++) {
      captured_flags[i] = false;
    }

    // Check what room the player is in, if they're not in home base, then it's no score
    if (GoalRooms[fteam] == me_roomnum) {
      // ok so he is in his home base, now find out how many flags he has, score for each and return them home
      flagcount = GetFlagCountForPlayer(pnum);
      flagmask = GetFlagMaskForPlayer(pnum);

      // now loop through the flags, check to see if we have them and handle it
      for (i = 0; i < CTFNumOfTeams; i++) {
        if (flagmask & 0x01) {
          // we have the flag we're currently working on
          captured_flags[i] = true;
          groom = GoalRooms[i];
          if ((groom >= 0) && (groom <= DMFCBase->GetHighestRoomIndex()) && (!ROOMNUM_OUTSIDE(groom)) &&
              (dRooms[groom].used)) {
            // the room is valid, so move it back to home

            LoseFlagForPlayer(pnum, i);

            if (DMFCBase->GetLocalRole() == LR_SERVER) {
              // if we are the server create the object and send it on it's way to the player's
              DLLComputeRoomCenter(&fpos, &dRooms[groom]);
              int objnum = DLLObjCreate(OBJ_POWERUP, FlagIDs[i], groom, &fpos, NULL, OBJECT_HANDLE_NONE);
              DLLMultiSendObject(&dObjects[objnum], 1, true);
            } // end server create
          }   // end room ok

          // set it's at home flag
          FlagAtHome[i] = true;
        } // end flag check
        // rotate the flagmask over one to check for the next flag
        flagmask = flagmask >> 1;
      } // end for loop

      // remove any rotating balls
      SetColoredBalls(pnum, true);

      // Now handle any scoring
      int score = 0;
      switch (flagcount) {
      case 0:
        break;
      case 1:
        score = 1;
        break;
      case 2:
        score = 3;
        break;
      case 3:
        score = 9;
        break;
      }

      // print out the message and add to the scores

      if (score) {
        tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(pnum);
        if (stat) {
          stat->Score[DSTAT_LEVEL] += score;
          stat->Score[DSTAT_OVERALL] += score;

          if (stat->Score[DSTAT_LEVEL] == 3) {
            if (Someone_has_hattrick) {
              DLLAddHUDMessage(TXT_HATTRICK, dPlayers[pnum].callsign);
              if (snd_hattrick_reg != -1)
                DLLPlay2dSound(snd_hattrick_reg, MAX_GAME_VOLUME / 2);
            } else {
              DLLAddHUDMessage(TXT_HATTRICKFIRST, dPlayers[pnum].callsign);
              if (snd_hattrick_first != -1)
                DLLPlay2dSound(snd_hattrick_first, MAX_GAME_VOLUME / 2);
              Someone_has_hattrick = true;
            }
          }
        }

        TeamScores[pteam] += score;
        OverallTeamScores[pteam] += score;
        int newscore = TeamScores[pteam];

        switch (flagcount) {
        case 1: {
          char t[20];
          t[0] = '\0';
          for (int c = 0; c < DLLMAX_TEAMS; c++) {
            if (captured_flags[c]) {
              strcpy(t, DMFCBase->GetTeamString(c));
              break;
            }
          }
          DLLAddHUDMessage(TXT_CAPTURE, dPlayers[pnum].callsign, DMFCBase->GetTeamString(pteam), t);
        } break;
        case 2: {
          char t[2][20];
          t[0][0] = '\0';
          t[1][0] = '\0';
          int index = 0;
          for (int c = 0; c < DLLMAX_TEAMS; c++) {
            if (captured_flags[c]) {
              strcpy(t[index], DMFCBase->GetTeamString(c));
              index++;
              if (index == 2)
                break;
            }
          }
          DLLAddHUDMessage(TXT_CAPTURETWO, dPlayers[pnum].callsign, DMFCBase->GetTeamString(pteam), t[0], t[1]);
        } break;
        case 3: {
          char t[3][20];
          t[0][0] = '\0';
          t[1][0] = '\0';
          t[2][0] = '\0';

          int index = 0;
          for (int c = 0; c < DLLMAX_TEAMS; c++) {
            if (captured_flags[c]) {
              strcpy(t[index], DMFCBase->GetTeamString(c));
              index++;
              if (index == 3)
                break;
            }
          }
          DLLAddHUDMessage(TXT_CAPTURETHREE, dPlayers[pnum].callsign, DMFCBase->GetTeamString(pteam), t[0], t[1], t[2]);
        }
        }

        if (dPlayers[DMFCBase->GetPlayerNum()].team == pteam) {
          if (snd_score_ownteam != -1)
            DLLPlay2dSound(snd_score_ownteam, MAX_GAME_VOLUME / 2);
        } else {
          if (snd_score_otherteam != -1)
            DLLPlay2dSound(snd_score_otherteam, MAX_GAME_VOLUME / 2);
        }

        // Set a Timer to display
        if (WhoJustScoredTimer != -1)
          DMFCBase->KillTimer(WhoJustScoredTimer);
        WhoJustScoredTimer = DMFCBase->SetTimerInterval(OnTimerScore, 0.5f, 5.0f, OnTimerScoreKill);
        WhoJustScored = pteam;
      }
      // do the killgoal check
      int killgoal;
      if (DMFCBase->GetScoreLimit(&killgoal)) {
        if (TeamScores[pteam] >= killgoal) {
          // That's all she wrote for this level
          DLLmprintf(0, "OnClientCollide:Kill Goal Reached!\n");
          DMFCBase->EndLevel();
        }
      }
    } else {
      DoFlagReturnedHome(pteam);
      if (DMFCBase->CheckPlayerNum(pnum)) {
        char parm1[20], parm2[20];
        strcpy(parm1, DMFCBase->GetTeamString(pteam));
        strcpy(parm2, DMFCBase->GetTeamString(fteam));
        DLLAddHUDMessage(TXT_RETURN, dPlayers[pnum].callsign, parm1, parm2);
      }
    }

    // since the player collided with his own team's flag we need to move the flag back home
    FlagAtHome[pteam] = true;
    HasFlag[pteam] = -1;
    vector home_pos;
    int home = GoalRooms[pteam];

    if ((home >= 0) && (home <= DMFCBase->GetHighestRoomIndex()) && (!ROOMNUM_OUTSIDE(home)) && (dRooms[home].used)) {
      DLLComputeRoomCenter(&home_pos, &dRooms[home]);
      DLLObjSetPos(it_obj, &home_pos, home, NULL, false);
    }

  } // end Player Collides with own team's flag
  else {
    // The Player collide with another team's flag
    FlagAtHome[fteam] = false;

    // add the flag to the player
    GivePlayerFlag(pnum, fteam);

    if (dPlayers[DMFCBase->GetPlayerNum()].team == dPlayers[pnum].team) {
      if (snd_pickedup_ownteam != -1)
        DLLPlay2dSound(snd_pickedup_ownteam, MAX_GAME_VOLUME / 2);
    } else {
      if (snd_pickedup_otherteam != -1)
        DLLPlay2dSound(snd_pickedup_otherteam, MAX_GAME_VOLUME / 2);
    }

    // Set a Timer to display
    if (WhoJustFlaggedTimer != -1)
      DMFCBase->KillTimer(WhoJustFlaggedTimer);
    WhoJustFlaggedTimer = DMFCBase->SetTimerInterval(OnTimer, 0.5f, 5.0f, OnTimerKill);
    WhoJustFlagged = fteam;

    char parm1[20], parm2[20];
    strcpy(parm1, DMFCBase->GetTeamString(pteam));
    strcpy(parm2, DMFCBase->GetTeamString(fteam));
    if (dObjects[dPlayers[pnum].objnum].roomnum == GoalRooms[fteam]) {
      DLLAddHUDMessage(TXT_PICKUPFLAG, dPlayers[pnum].callsign, parm1, parm2);
    } else {
      DLLAddHUDMessage(TXT_PICKUPFLAGSPEW, dPlayers[pnum].callsign, parm1, parm2);
    }

    // remove the flag from the world
    if (DMFCBase->GetLocalRole() == LR_SERVER) {
      // tell the clients to remove this flag
      DLLSetObjectDeadFlag(it_obj, true, false);
    }
  }
}

// OnGameStateRequest
//   1) Send game state to new player
void OnGameStateRequest(int player_num) {
  SendGameState(player_num);
  DMFCBase->OnGameStateRequest(player_num);
}

void OnPlayerConnect(int player_num) {
  DMFCBase->OnPlayerConnect(player_num);

  tPlayerStat *stat;
  stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(player_num);
  if (stat) {
    stat->Score[DSTAT_LEVEL] = 0;
    stat->Score[DSTAT_OVERALL] = 0;
  }

  if (player_num != DMFCBase->GetPlayerNum()) {
    // announce the arrival of the player
    DisplayWelcomeMessage(player_num);
  }
}

void OnClientLevelEnd(void) { DMFCBase->OnClientLevelEnd(); }

void OnPlayerChangeTeam(int player_num, int newteam, bool announce, bool spew_onrespawn) {
  DMFCBase->OnPlayerChangeTeam(player_num, newteam, announce, spew_onrespawn);
  player_record *pr = DMFCBase->GetPlayerRecordByPnum(player_num);
}

// OnClientPlayerKilled
//		1) If suicide add to suicides
//    2) Else add to killer's kill, add to victim's deaths
//    3) Reset colored balls
//    4) If killed in a flag's home goal than put it in the center of the room
void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
  int kpnum = -1;

  if (killer_obj) {
    if ((killer_obj->type == OBJ_PLAYER) || (killer_obj->type == OBJ_GHOST) || (killer_obj->type == OBJ_OBSERVER))
      kpnum = killer_obj->id;
    else if (killer_obj->type == OBJ_ROBOT || killer_obj->type == OBJ_BUILDING) {
      // countermeasure kill
      kpnum = DMFCBase->GetCounterMeasureOwner(killer_obj);
    } else {
      kpnum = -1;
    }
  }

  HandlePlayerSpew(victim_pnum);
  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
}

void OnClientPlayerDisconnect(int player_num) {
  HandlePlayerSpew(player_num);
  DMFCBase->OnClientPlayerDisconnect(player_num);
}

void OnPlayerEntersObserver(int pnum, object *piggy) {
  HandlePlayerSpew(pnum);
  DMFCBase->OnPlayerEntersObserver(pnum, piggy);
}

bool OnCanChangeTeam(int pnum, int newteam) {
  if (!DMFCBase->OnCanChangeTeam(pnum, newteam))
    return false;

  if (GetFlagCountForPlayer(pnum)) {
    DMFCBase->AnnounceTeamChangeDeny(pnum);
    return false;
  }

  return true;
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
  memcpy(SortedPlayers, tempsort, MAX_PLAYER_RECORDS * sizeof(int));

  // Now fill in the final structure of sorted names
  int TeamCount[DLLMAX_TEAMS];
  int team;
  for (i = 0; i < DLLMAX_TEAMS; i++)
    TeamCount[i] = 0;
  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    int slot = SortedPlayers[i];
    player_record *pr = DMFCBase->GetPlayerRecord(slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      team = (pr->state == STATE_INGAME) ? dPlayers[pr->pnum].team : pr->team;

      if (team >= CTFNumOfTeams)
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
  int NameCol = 180;
  int PointsCol = 320;
  int KillsCol = 370;
  int DeathsCol = 410;
  int SuicidesCol = 450;
  int y = 40;
  int slot;
  bool had_members;
  player_record *pr;
  tPlayerStat *stat;

  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(PointsCol, y, TXT_POINTS);
  DLLgrtext_Printf(NameCol, y, TXT_PILOT);
  DLLgrtext_Printf(KillsCol, y, TXT_KILLS_SHORT);
  DLLgrtext_Printf(DeathsCol, y, TXT_DEATHS_SHORT);
  DLLgrtext_Printf(SuicidesCol, y, TXT_SUICIDES_SHORT);
  y += height;

  bool doing_connected = true;

do_disconnected_folk:

  for (int team = 0; team < CTFNumOfTeams; team++) {
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
      DLLgrtext_Printf(TeamCol, y, TXT_TEAMSCOREFORM, DMFCBase->GetTeamString(team), TeamScores[team],
                       OverallTeamScores[team]);
    }
    had_members = false;

    for (int index = 0; index < MAX_PLAYER_RECORDS; index++) {
      // get the player num
      slot = SortedPLRPlayers[team][index];
      if (slot == -1) // we are done with this team
        break;

      pr = DMFCBase->GetPlayerRecord(slot);
      if (!pr || pr->state == STATE_EMPTY)
        continue;

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue;

      if ((doing_connected && DMFCBase->WasPlayerInGameAtLevelEnd(slot) == -1) ||
          (!doing_connected && DMFCBase->WasPlayerInGameAtLevelEnd(slot) != -1))
        continue; // we're not handling them right now

      stat = (tPlayerStat *)pr->user_info;

      int pnum = DMFCBase->WasPlayerInGameAtLevelEnd(slot);
      if (pnum != -1) {
        DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));
      } else {
        DLLgrtext_SetColor(GR_RGB(128, 128, 128));
      }

      // valid player
      char temp[120];
      snprintf(temp, sizeof(temp), "%s", pr->callsign);
      DMFCBase->ClipString(PointsCol - NameCol - 10, temp, true);

      DLLgrtext_Printf(NameCol, y, "%s", temp);
      DLLgrtext_Printf(PointsCol, y, "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
      DLLgrtext_Printf(KillsCol, y, "%d", pr->dstats.kills[DSTAT_LEVEL]);
      DLLgrtext_Printf(DeathsCol, y, "%d", pr->dstats.deaths[DSTAT_LEVEL]);
      DLLgrtext_Printf(SuicidesCol, y, "%d", pr->dstats.suicides[DSTAT_LEVEL]);
      y += height;

      if (y >= 440)
        goto quick_exit;

      had_members = true;

    } // end for

    if (!had_members) {
      // skip a line
      y += height;

      if (y >= 440)
        goto quick_exit;
    }
    // on to the next team
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
  tPlayerStat *ps;
  int count, p;
  int team;

  // sort the stats
  DMFCBase->GetSortedPlayerSlots(sortedslots, MAX_PLAYER_RECORDS);

  int i, t, j;

  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    sortedslots[i] = i;
  }

  for (i = 1; i <= MAX_PLAYER_RECORDS - 1; i++) {
    t = sortedslots[i];
    // Shift elements down until
    // insertion point found.
    for (j = i - 1; j >= 0 && compare_slots(sortedslots[j], t); j--) {
      sortedslots[j + 1] = sortedslots[j];
    }
    // insert
    sortedslots[j + 1] = t;
  }

  count = 1;

  snprintf(buffer, sizeof(buffer), TXT_STAT_HEADING, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  for (i = 0; i < DMFCBase->GetNumTeams(); i++) {
    int team = SortedTeams[i];

    snprintf(buffer, sizeof(buffer), "%s: %d[%d]", DMFCBase->GetTeamString(team), TeamScores[team],
             OverallTeamScores[team]);
    DLLcf_WriteString(file, buffer);
  }
  strcpy(buffer, "\r\n");
  DLLcf_WriteString(file, buffer);

  // Write team members
  DLLcf_WriteString(file, ""); // blank line
  for (t = 0; t < DMFCBase->GetNumTeams(); t++) {
    int team_i = SortedTeams[t];

    snprintf(buffer, sizeof(buffer), "%s:", DMFCBase->GetTeamString(team_i));
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

  snprintf(buffer, sizeof(buffer), "%s", TXT_STAT_HEADINGA);
  DLLcf_WriteString(file, buffer);
  strcpy(buffer, "--------------------------------------------------------------------------------------------------");
  DLLcf_WriteString(file, buffer);

  for (int pslot = 0; pslot < MAX_PLAYER_RECORDS; pslot++) {
    int real_slot = sortedslots[pslot];
    pr = DMFCBase->GetPlayerRecord(real_slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      // we have a valid play
      ps = (tPlayerStat *)pr->user_info;
      memset(buffer, ' ', BUFSIZE);

      team = pr->team;

      snprintf(tempbuffer, sizeof(tempbuffer), "%d)", count);
      memcpy(&buffer[0], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%.6s", DMFCBase->GetTeamString(team));
      memcpy(&buffer[5], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s%s", (pr->state == STATE_INGAME) ? "" : "*", pr->callsign);
      memcpy(&buffer[12], tempbuffer, strlen(tempbuffer));

      if (ps) {
        snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", ps->Score[DSTAT_LEVEL], ps->Score[DSTAT_OVERALL]);
        memcpy(&buffer[41], tempbuffer, strlen(tempbuffer));
      }

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.kills[DSTAT_LEVEL],
               pr->dstats.kills[DSTAT_OVERALL]);
      memcpy(&buffer[53], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.deaths[DSTAT_LEVEL],
               pr->dstats.deaths[DSTAT_OVERALL]);
      memcpy(&buffer[65], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%d[%d]", pr->dstats.suicides[DSTAT_LEVEL],
               pr->dstats.suicides[DSTAT_OVERALL]);
      memcpy(&buffer[76], tempbuffer, strlen(tempbuffer));

      snprintf(tempbuffer, sizeof(tempbuffer), "%s", DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(real_slot)));
      memcpy(&buffer[86], tempbuffer, strlen(tempbuffer));

      size_t pos = 86 + strlen(tempbuffer) + 1;
      if (pos < BUFSIZE)
        buffer[pos] = '\0';

      buffer[BUFSIZE - 1] = '\0';
      DLLcf_WriteString(file, buffer);

      count++;
    }
  } // end for

  DLLcf_WriteString(file, TXT_STAT_HEADINGB);

  count = 1;
  for (int s = 0; s < MAX_PLAYER_RECORDS; s++) {
    p = sortedslots[s];
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
      snprintf(buffer, sizeof(buffer), TXT_STAT_TIG, DMFCBase->GetTimeString(DMFCBase->GetTimeInGame(p)));
      DLLcf_WriteString(file, buffer);

      if (DMFCBase->FindPInfoStatFirst(p, &stat)) {
        snprintf(buffer, sizeof(buffer), "%s", TXT_STAT_HEADINGC);
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
  DLLAddHUDMessage(TXT_STAT_SAVED);
}

#define ROOTFILENAME "CTF"
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
  char name[70];
  size_t t;
  size_t pos[6];
  size_t len[6];

  for (int i = 0; i < CTFNumOfTeams; i++) {
    snprintf(buffer, sizeof(buffer), "%s:%d\n", DMFCBase->GetTeamString(i), TeamScores[i]);
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

      tPlayerStat *stat;
      stat = (tPlayerStat *)pr->user_info;

      memset(buffer, ' ', 256);
      t = strlen(name);
      memcpy(&buffer[pos[0]], name, (t < len[0]) ? t : len[0]);
      snprintf(name, sizeof(name), "%d", (stat) ? stat->Score[DSTAT_LEVEL] : 0);
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

//	DMFCApp::HandlePlayerSpew
//
//	If a player dies, becomes an observer or disconnects, it's possible that they
//	have a flag or more.  This function will handle setting certain variables, timer
//	and other various settings related to a flag spew
void HandlePlayerSpew(int pnum) {
  // Handle dropping the flag if the player had one
  uint8_t flaginfo = GetFlagCountForPlayer(pnum);
  uint8_t flagmask = GetFlagMaskForPlayer(pnum);

  if (flaginfo == 0) {
    return;
  }

  // Ok the player has flags, lets make sure everything that needs to happen, happens
  // 1) We need to clear flags and colored ball indicator
  // 2) If they are dying in a homebase of one of the flags they have, than set the
  //	  flag home.
  // 3) Start a timer if the flag spews outside of a base

  // If we got here than the player has a flag
  vector fpos; // used to hold the center pos of the room

  bool play_lose = false; // set true if the player lost a flag (ummm, this is guaranteed)

  // loop through all the possible flags and check to see what they had
  for (int color = 0; color < DLLMAX_TEAMS; color++) {
    // check if the ID exists, and if this player had that color flag
    if ((FlagIDs[color] != -1) && (flagmask & 0x01)) {

      play_lose = true;

      // now check to see if they are in the flag's home goal
      if (GoalRooms[color] == dObjects[pnum].roomnum) {
        // we are!
        // so remove the flag from the inventory (so it don't get spewed)
        DLLInvRemove(pnum, OBJ_POWERUP, FlagIDs[color]);
        DoFlagReturnedHome(color);

        // set the at home flag
        FlagAtHome[color] = true;
        if (DMFCBase->GetLocalRole() == LR_SERVER) {
          // if we are the server put the flag back in the center of the goal and tell all the players to do the same
          DLLComputeRoomCenter(&fpos, &dRooms[GoalRooms[color]]);
          int objnum = DLLObjCreate(OBJ_POWERUP, FlagIDs[color], GoalRooms[color], &fpos, NULL, OBJECT_HANDLE_NONE);
          DLLMultiSendObject(&dObjects[objnum], 1, true);
        }
      } else {
        // ok the flag is spewing out into the great beyond
        // Start the timer!
        Flag_timeout_timers[color] = DMFCBase->GetGametime() + FLAG_TIMEOUT_VALUE;
      }

      // player has the flag
      LoseFlagForPlayer(pnum, color, false);
    }
    // rotate flagmask so it is pointing at the next bit
    flagmask = (flagmask >> 1);
  }

  // Reset colored balls
  SetColoredBalls(pnum, true);

  if (play_lose)
    DoLoseFlag(DMFCBase->GetPlayerTeam(pnum));
}

/////////////////////////////////////////////////////////////
// CTF Functions
void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    // announce our arrival to ourselves (as server)
    DisplayWelcomeMessage(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (!First_game_frame || DisplayScoreScreen) // interval hasn't been called yet or we are display the stats
    return;

  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)((DisplayScoreScreen) ? 128 : 255));

  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX]) + 3;

  int y = 170;
  int x = 540;
  int team = DMFCBase->GetPlayerTeam(DMFCBase->GetPlayerNum());
  int myteam = team;
  int i;

  // Flag bitmaps
  // if (HasFlag[team]!=-1) then draw a dimmed flag with the team flag of who has it on top
  // if (HasFlag[team]==-1) && (FlagAtHome[team]==true) then draw normal flag
  // if (HasFlag[team]==-1) && (FlagAtHome[team]==false) then draw dimmed flag
  int cx, cy;
  for (i = 0; i < CTFNumOfTeams; i++) {
    // first determine the x and y
    switch (i) {
    case RED_TEAM:
      cx = x;
      cy = height + 5;
      break;
    case BLUE_TEAM:
      cx = x + 33;
      cy = height + 5;
      break;
    case GREEN_TEAM:
      cx = x;
      cy = 2 * height + 41;
      break;
    case YELLOW_TEAM:
      cx = x + 33;
      cy = 2 * height + 41;
      break;
    }

    if ((WhoJustFlagged != i) || (DisplayFlagBlink)) {
      if (HasFlag[i] != -1) {
        // draw dimmed flag with corner as the team who has the flag
        DLLRenderHUDQuad(cx, cy, DLLbm_w(DimFlagAHBmp[i], 0), DLLbm_h(DimFlagAHBmp[i], 0), 0, 0, 1, 1, DimFlagAHBmp[i],
                         alpha, 0);
        DLLRenderHUDQuad(cx + 16, cy, 16, 16, 0, 0, 1, 1, FlagBmp[DMFCBase->GetPlayerTeam(HasFlag[i])], alpha, 0);
      } else {
        if (FlagAtHome[i]) {
          // draw normal flag
          DLLRenderHUDQuad(cx, cy, DLLbm_w(FlagAHBmp[i], 0), DLLbm_h(FlagAHBmp[i], 0), 0, 0, 1, 1, FlagAHBmp[i], alpha,
                           0);
        } else {
          // draw dimmed flag
          int f_height = DLLbm_h(DimFlagAHBmp[i], 0);
          DLLRenderHUDQuad(cx, cy, DLLbm_w(DimFlagAHBmp[i], 0), f_height, 0, 0, 1, 1, DimFlagAHBmp[i], alpha, 0);

          // Draw timeout time
          int time_left;
          time_left = (int)(Flag_timeout_timers[i] - DMFCBase->GetGametime());
          if (time_left > 0 && Flag_timeout_timers[i] != 0) {
            int minutes;
            minutes = time_left / 60;
            time_left = time_left % 60;
            DLLRenderHUDText(GR_GREEN, alpha, 0, cx, cy + 2 + f_height, "%01d:%02d", minutes, time_left);
          }
        }
      }
    }
  }

  x = 520;

  if (Highlight_bmp <= BAD_BITMAP_HANDLE) {
    // write the name of your team at the top of the screen since for some reason we don't a highlight bmp
    DLLRenderHUDText(DMFCBase->GetTeamColor(team), alpha, 0, x, y, TXT_TEAMFORM, DMFCBase->GetTeamString(team));
    y += height;
  }

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 85.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;
  y = (DMFCBase->GetGameWindowH() / 2) - ((height * DMFCBase->GetNumTeams()) / 2);

  // draw the team scores
  for (team = 0; team < DLLMAX_TEAMS; team++) {
    i = SortedTeams[team];

    if (i >= CTFNumOfTeams)
      continue;

    if ((WhoJustScored != i) || (DisplayScoreBlink)) {

      // determine the number of players on the team
      int num_players;
      num_players = 0;
      for (int w = 0; w < DLLMAX_PLAYERS; w++) {
        if (DMFCBase->CheckPlayerNum(w) && dPlayers[w].team == i && !DMFCBase->IsPlayerDedicatedServer(w))
          num_players++;
      }

      if (i == myteam && Highlight_bmp > BAD_BITMAP_HANDLE) {
        // draw the highlite bar in the background
        DLLrend_SetAlphaValue(alpha * 0.50f);
        DLLrend_SetZBufferState(0);
        DLLrend_SetTextureType(TT_LINEAR);
        DLLrend_SetLighting(LS_NONE);
        DLLrend_SetAlphaType(AT_CONSTANT_TEXTURE);

        DLLrend_DrawScaledBitmap(name_x - 2, y - 2, score_x + score_width + 2, y + height - 1, Highlight_bmp, 0, 0, 1,
                                 1, 1.0, BITMAP_FORMAT_1555, NULL);
        DLLrend_SetZBufferState(1);
      }

      char team_name[MAX_TEAMNAME_LEN + 5];
      snprintf(team_name, sizeof(team_name), "[%d]%s", num_players, DMFCBase->GetTeamString(i));
      // DMFCBase->ClipString(615 - x - 10,team_name,true);
      // DLLRenderHUDText(DMFCBase->GetTeamColor(i),alpha,0,x,y,team_name);
      // DLLRenderHUDText(DMFCBase->GetTeamColor(i),alpha,0,615,y,"%d",TeamScores[i]);
      DMFCBase->ClipString(name_width, team_name, true);

      DLLgrtext_SetAlpha(alpha);
      DLLgrtext_SetColor(DMFCBase->GetTeamColor(i));
      DLLgrtext_Printf(name_x, y, team_name);
      DLLgrtext_Printf(score_x, y, "%d", TeamScores[i]);
    }
    y += height;
  }

  // draw the bitmap for any flags you have currently
  int flagcount;
  int flagmask;

  flagcount = GetFlagCountForPlayer(DMFCBase->GetPlayerNum());
  flagmask = GetFlagMaskForPlayer(DMFCBase->GetPlayerNum());

  if (flagcount == 0)
    return;

  y += 5;

  for (i = 0; i < CTFNumOfTeams; i++) {
    if (flagmask & 0x01) {
      // we have the flag
      DLLRenderHUDQuad(x, y, DLLbm_w(FlagBmp[i], 0) / 2, DLLbm_h(FlagBmp[i], 0) / 2, 0, 0, 1, 1, FlagBmp[i], alpha, 0);
      x += DLLbm_w(FlagBmp[i], 0) + 3;
    }
    // adjust the flagmask for the next flag
    flagmask = flagmask >> 1;
  }
}

#define compGT(a, b) (a < b)
void SortTeamScores(int *sortedindex, int *scores) {
  int t;
  int i, j;

  // copy scores into scoreinfo array
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    sortedindex[i] = i;
  }

  for (i = 1; i <= DLLMAX_TEAMS - 1; i++) {
    t = sortedindex[i];

    // Shift elements down until
    // insertion point found.
    for (j = i - 1; j >= 0 && compGT(scores[sortedindex[j]], scores[t]); j--) {
      sortedindex[j + 1] = sortedindex[j];
    }
    // insert
    sortedindex[j + 1] = t;
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

// adds a colored ball to a player (without removing what he has already)
void SetColoredBalls(int playernum, bool reset) {
  float redb[4];
  float greenb[4];
  float blueb[4];

  if (reset) {
    DLLPlayerSetRotatingBall(playernum, 0, 0, NULL, NULL, NULL);
    return;
  }

  int flagcount;
  int flagmask;

  bool red, blue, green, yellow;
  red = blue = green = yellow = false;

  flagcount = GetFlagCountForPlayer(playernum);
  flagmask = GetFlagMaskForPlayer(playernum);

  if (flagcount == 0) {
    DLLPlayerSetRotatingBall(playernum, 0, 0, NULL, NULL, NULL);
    return;
  }

  if (flagmask & FLAGMASK_REDTEAM)
    red = true;
  if (flagmask & FLAGMASK_BLUETEAM)
    blue = true;
  if (flagmask & FLAGMASK_GREENTEAM)
    green = true;
  if (flagmask & FLAGMASK_YELLOWTEAM)
    yellow = true;

  for (int i = 0; i < flagcount; i++) {
    if (red) {
      red = false;
      redb[i] = 1;
      greenb[i] = 0;
      blueb[i] = 0;
    } else if (blue) {
      blue = false;
      redb[i] = 0;
      greenb[i] = 0;
      blueb[i] = 1;
    } else if (green) {
      green = false;
      redb[i] = 0;
      greenb[i] = 1;
      blueb[i] = 0;
    } else if (yellow) {
      yellow = false;
      redb[i] = 1;
      greenb[i] = 1;
      blueb[i] = 0;
    }
  }

  DLLPlayerSetRotatingBall(playernum, flagcount, 0, redb, greenb, blueb);
}

// Allows for dynamic changing of the number of teams in the game
void ChangeNumberOfTeams(int newsize) {
  CTFNumOfTeams = newsize;
  DMFCBase->SetNumberOfTeams(CTFNumOfTeams);
}

void DoFlagReturnedHome(int team) {
  if (DMFCBase->GetPlayerTeam(DMFCBase->GetPlayerNum()) == team) {
    if (snd_return_ownteam != -1)
      DLLPlay2dSound(snd_return_ownteam, MAX_GAME_VOLUME / 2);
  } else {
    if (snd_return_otherteam != -1)
      DLLPlay2dSound(snd_return_otherteam, MAX_GAME_VOLUME / 2);
  }
}

void DoLoseFlag(int team) {
  if (DMFCBase->GetPlayerTeam(DMFCBase->GetPlayerNum()) == team) {
    if (snd_lose_ownteam != -1)
      DLLPlay2dSound(snd_lose_ownteam, MAX_GAME_VOLUME / 2);
  } else {
    if (snd_lose_otherteam != -1)
      DLLPlay2dSound(snd_lose_otherteam, MAX_GAME_VOLUME / 2);
  }
}

//	VerifyFlagPosition
//	Call this at certain intervals to verify a flags position.  It will look at the
//	flags room and makes sure that if it's in it's home room, the correct values
//	are set, and vice versa.
void VerifyFlagPosition(void) {}

//	AddFlagToPlayer
//	gives a player a flag
bool AddFlagToPlayer(int pnum, int team, int flagobjnum) {
  object *pobj = &dObjects[dPlayers[pnum].objnum];
  bool ret = true;

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    // We're the server, so we need to create the flag and tell the clients, and then attach it
    flagobjnum = DLLObjCreate(OBJ_POWERUP, AFlagIDs[team], pobj->roomnum, &pobj->pos, NULL, OBJECT_HANDLE_NONE);

    if (flagobjnum != -1) {
      // tell the clients that the flag has been created and they should attach it
      TellClientsToAddorDelFlag(pnum, team, flagobjnum, true);
    }

    // Attach the flag

    //	1st figure out how many flags the guy already has
    //	-------------------------------------------------
    int max_num_attach = 3; // based off chrishack for multiplayer
    int num_attached = 0;

    if (!pobj->attach_children)
      ret = false;
    else {
      for (int ap = 0; ap < max_num_attach; ap++) {
        if (pobj->attach_children[ap] != OBJECT_HANDLE_NONE) {
          // attempt to make sure it's a valid object
          object *tobj;
          if (DLLObjGet(pobj->attach_children[ap], &tobj)) {
            num_attached++;
          }
        }
      }

      //	2nd num_attached is the current number of flags this object has
      //	---------------------------------------------------------------
      switch (num_attached) {
      case 0: {
        // the easy case, nothing is attached, so just attach it to ap0
        ret = DLLAttachObject(pobj, 0, &dObjects[flagobjnum], 0, true);
      } break;

      case 1: {
        bool retval;
        object *tobj;

        // we should have a flag at ap0, move it to ap1
        ASSERT(pobj->attach_children[0] != OBJECT_HANDLE_NONE);
        int saved_ap0 = pobj->attach_children[0];
        retval = DLLUnattachChild(pobj, 0);
        ASSERT(retval);

        retval = DLLObjGet(saved_ap0, &tobj);
        ASSERT(retval);

        // attach to ap1
        retval = DLLAttachObject(pobj, 1, tobj, 0, true);
        ASSERT(retval);

        // attach new flag to ap2
        retval = DLLAttachObject(pobj, 2, &dObjects[flagobjnum], 0, true);
        ASSERT(retval);

        ret = retval;

      } break;

      case 2: {
        // we should have a flag at ap1 and ap2
        // so just add this to ap3

        // attach new flag to ap3
        ret = DLLAttachObject(pobj, 0, &dObjects[flagobjnum], 0, true);

      } break;

      case 3:
      default: {
        Int3(); // Get Jeff
        ret = false;
      } break;
      }
    }

    if (!ret) {
      // couldn't attach the flag
      mprintf(0, "CTF: COULDN'T ATTACH FLAG TO PLAYER, DELETING\n");
      // tell the clients to remove this flag
      DLLSetObjectDeadFlag(&dObjects[flagobjnum], true, false);
    }
  }

  if (flagobjnum == -1) {
    // there was an error creating the flag...not good
    mprintf(0, "CTF: Couldn't create/unhash flag for attachment\n");
    DMFCBase->DisconnectMe();
    return false;
  }

  ChildFlags[team] = dObjects[flagobjnum].handle;

  return ret;
}

//	RemoveFlagFromPlayer
//	removes a flag from a player
bool RemoveFlagFromPlayer(int pnum, int team) {
  int flagobjnum = -1;

  if (DMFCBase->GetLocalRole() == LR_SERVER) {

    if (ChildFlags[team] == OBJECT_HANDLE_NONE)
      return false;

    object *fptr;
    if (!DLLObjGet(ChildFlags[team], &fptr)) {
      // the flag is already dead?!?
      return false;
    }

    DLLSetObjectDeadFlag(fptr, true, false);

    // tell the clients to remove the flag
    TellClientsToAddorDelFlag(pnum, team, -1, false);
  }

  ChildFlags[team] = OBJECT_HANDLE_NONE;

  return true;
}

void TellClientsToAddorDelFlag(int pnum, int team, int objnum, bool add) {
  if (add) {
    // if we are adding a flag, than we need to send the object to them to make sure that
    // they have it for when we go to process it
    DLLMultiSendObject(&dObjects[objnum], false, true);
  }

  uint8_t data[MAX_GAME_DATA_SIZE];
  int size = 0;
  DMFCBase->StartPacket(data, SPID_ADDDELFLAG, &size);

  MultiAddByte(pnum, data, &size);
  MultiAddByte(team, data, &size);
  MultiAddByte(add, data, &size);

  if (add) {
    // add the objnum of the flag and pack it into the packet
    MultiAddInt(objnum, data, &size);
  }

  DMFCBase->SendPacket(data, size, SP_ALL);
}

void ServerIsTellingMeToAddorDelAFlag(uint8_t *data) {
  int size = 0;
  int pnum, team;
  bool add;

  pnum = MultiGetByte(data, &size);
  team = MultiGetByte(data, &size);
  add = (MultiGetByte(data, &size)) ? true : false;

  // determine if we should add or delete a flag
  if (add) {
    int objnum;
    objnum = MultiGetInt(data, &size);
    objnum = DMFCBase->ConvertServerToLocalObjnum(objnum);
    if (objnum == -1) {
      // uh oh...corruption???
      FatalError("CTF: Server->Local Object Corruption\n");
      return;
    }
    AddFlagToPlayer(pnum, team, objnum);
  } else {
    RemoveFlagFromPlayer(pnum, team);
  }
}

/////////////////////////////////
// Timer event handlers
void OnTimer(void) { DisplayFlagBlink = !DisplayFlagBlink; }
void OnTimerKill(void) {
  DisplayFlagBlink = true;
  WhoJustFlagged = WhoJustFlaggedTimer = -1;
}

void OnTimerScore(void) { DisplayScoreBlink = !DisplayScoreBlink; }
void OnTimerScoreKill(void) {
  DisplayScoreBlink = true;
  WhoJustScored = WhoJustScoredTimer = -1;
}

///////////////////////////////////////////////////////////////////////////////////
int PackByte(uint8_t byte, uint8_t *buffer, int pos) {
  buffer[pos] = byte;
  pos++;
  return pos;
}

int UnPackByte(uint8_t *byte, uint8_t *buffer, int pos) {
  *byte = buffer[pos];
  pos++;
  return pos;
}

int PackBytes(uint8_t *bytes, int count, uint8_t *buffer, int pos) {
  memcpy(&buffer[pos], bytes, count);
  pos += count;
  return pos;
}

int UnPackBytes(uint8_t *bytes, int count, uint8_t *buffer, int pos) {
  memcpy(bytes, &buffer[pos], count);
  pos += count;
  return pos;
}

int PackWord(uint16_t word, uint8_t *buffer, int pos) { return PackBytes((uint8_t *)&word, sizeof(uint16_t), buffer, pos); }

int UnPackWord(uint16_t *word, uint8_t *buffer, int pos) { return UnPackBytes((uint8_t *)word, sizeof(uint16_t), buffer, pos); }

int PackInt(int data, uint8_t *buffer, int pos) { return PackBytes((uint8_t *)&data, sizeof(int), buffer, pos); }

int UnPackInt(int *data, uint8_t *buffer, int pos) { return UnPackBytes((uint8_t *)data, sizeof(int), buffer, pos); }

int PackArray(uint8_t *data, int size, int count, uint8_t *buffer, int pos) {
  return PackBytes(data, size * count, buffer, pos);
}

int UnPackArray(uint8_t *data, int size, int count, uint8_t *buffer, int pos) {
  return UnPackBytes(data, size * count, buffer, pos);
}

void SendGameState(int pnum) {
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;
  int i;

  DMFCBase->StartPacket(data, SPID_GAMESTATE, &count);

  // pack number of teams in this game
  MultiAddInt(CTFNumOfTeams, data, &count);

  // pack flag whether someone has scored a hattrick
  MultiAddByte(Someone_has_hattrick, data, &count);

  for (i = 0; i < DLLMAX_TEAMS; i++) {
    // Pack FlagAtHome
    MultiAddByte(FlagAtHome[i], data, &count);

    // pack flag timeout timers
    MultiAddFloat(Flag_timeout_timers[i], data, &count);

    // pack team scores
    MultiAddInt(TeamScores[i], data, &count);

    // pack overall team scores
    MultiAddInt(OverallTeamScores[i], data, &count);

    // pack who has flag data
    MultiAddInt(HasFlag[i], data, &count);
  }

  uint16_t server_objnums[DLLMAX_TEAMS];
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    if (ChildFlags[i] == OBJECT_HANDLE_NONE) {
      // slot not in use
      server_objnums[i] = 65535;
    } else {
      // should be a valid slot
      object *obj;

      if (!DLLObjGet(ChildFlags[i], &obj)) {
        // ok it's not a valid slot...hrm
        ChildFlags[i] = OBJECT_HANDLE_NONE;
        server_objnums[i] = 65535;
      } else {
        // it's valid
        int objnum = (obj - dObjects);
        server_objnums[i] = objnum;
      }
    }
  }

  // pack attached flag handles
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    MultiAddUshort(server_objnums[i], data, &count);
  }

  DMFCBase->SendPacket(data, count, pnum);
}

void ReceiveGameState(uint8_t *data) {
  int count = 0;
  int num_teams;
  int i;

  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    // reset everything
    SetColoredBalls(i, true);
    for (int t = 0; t < DLLMAX_TEAMS; t++) {
      while (DLLInvCheckItem(i, OBJ_POWERUP, FlagIDs[t])) {
        DLLInvRemove(i, OBJ_POWERUP, FlagIDs[t]);
      }
    }
  }

  // Read num teams
  num_teams = MultiGetInt(data, &count);
  ChangeNumberOfTeams(num_teams);

  // see if someone has had a hattrick yet
  Someone_has_hattrick = (MultiGetByte(data, &count)) ? true : false;

  for (i = 0; i < DLLMAX_TEAMS; i++) {
    // UnPack FlagAtHome
    FlagAtHome[i] = (MultiGetByte(data, &count)) ? true : false;

    // unpack flag timeout timers
    Flag_timeout_timers[i] = MultiGetFloat(data, &count);

    // unpack team scores
    TeamScores[i] = MultiGetInt(data, &count);

    // unpack overall team scores
    OverallTeamScores[i] = MultiGetInt(data, &count);

    // unpack who has flag data
    HasFlag[i] = MultiGetInt(data, &count);
  }

  // go through the HasFlag array and put items in the inventory, and add colored balls
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    if (HasFlag[i] != -1) {
      DLLInvAddTypeID(HasFlag[i], OBJ_POWERUP, FlagIDs[i], -1, -1, 0, NULL);

      // put some balls on the guy
      SetColoredBalls(HasFlag[i]);
    }
  }

  uint16_t server_objnums[DLLMAX_TEAMS];
  // unpack attached flag handles
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    server_objnums[i] = MultiGetUshort(data, &count);
  }

  // the final step, match the server_objnums->ChildFlags and Attach the flags
  for (i = 0; i < DLLMAX_TEAMS; i++) {
    if (server_objnums[i] != 65535) {
      // we should have a real object here
      uint16_t our_objnum = DMFCBase->ConvertServerToLocalObjnum(server_objnums[i]);

      if (our_objnum == -1) {
        // fatal error
        mprintf(0, "CTF: Local Objnums don't match server objnums\n");
        ChildFlags[i] = OBJECT_HANDLE_NONE;
        DMFCBase->DisconnectMe();
      } else {
        // yeah! a valid objnum, attach it!!!
        if (HasFlag[i] != -1)
          AddFlagToPlayer(HasFlag[i], i, our_objnum);
        else {
          // hmm, HasFlag doesn't match ChildFlags
          mprintf(0, "CTF: HasFlag doesn't match ChildFlags!!!!\n");
          ChildFlags[i] = OBJECT_HANDLE_NONE;
        }
      }
    } else {
      // ok invalid...
      ChildFlags[i] = OBJECT_HANDLE_NONE;
    }
  }
}

/*
********************************************************************************************
*/

//	returns the number of flags a player has, 0 if none, or an invalid pnum
int GetFlagCountForPlayer(int pnum) {
  // 1st check the pnum, make sure it is OK, is it isn't, return 0
  if (pnum < 0 || pnum >= DLLMAX_PLAYERS) {
    // invalid player number, return 0 flags
    mprintf(0, "CTF: Invalid PNUM passed to GetFlagCountForPlayer()\n");
    return 0;
  }

  int flag_count = 0;
  // 2nd, go through all the team flags, and check the player's inventory, see if they have the ID,
  // if so, add it to their count
  for (int i = 0; i < DLLMAX_TEAMS; i++) {
    if (DLLInvCheckItem(pnum, OBJ_POWERUP, FlagIDs[i])) {
      // they have this flag
      flag_count++;
    }
  }

  return flag_count;
}

//	returns the mask of which flags this player currently has
uint8_t GetFlagMaskForPlayer(int pnum) {
  // 1st check the pnum, make sure it is OK, if it isn't, return 0, meaning no flags
  if (pnum < 0 || pnum >= DLLMAX_PLAYERS) {
    // invalid player number, return 0 flags
    mprintf(0, "CTF: Invalid PNUM passed to GetFlagMaskForPlayer()\n");
    return 0;
  }

  int flag_mask = 0;
  uint8_t mask = 0x01;

  // 2nd go through all the teams flags, and check the player's inventory, see if they have the ID,
  // if so, OR the current mask to the running flag_mask
  for (int i = 0; i < DLLMAX_TEAMS; i++) {
    if (DLLInvCheckItem(pnum, OBJ_POWERUP, FlagIDs[i])) {
      // the have this flag
      flag_mask |= mask;
    }
    // adjust the mask because we are moving to the next flag
    mask = mask << 1;
  }

  return flag_mask;
}

//	adds a flag to a player, as a precaution, it will go through all the players and makes sure that no one
//	has the flag that is being added.  If they are adding the flag, than remove that flag from whoever we thought
// had it 	it will return false if it had to remove a flag from a player
bool GivePlayerFlag(int pnum, uint8_t team) {
  // 1st check the player num, make sure it is valid
  if (!DMFCBase->CheckPlayerNum(pnum)) {
    // not a valid player
    mprintf(0, "CTF: Invalid pnum passed to GivePlayerFlag()\n");
    return false;
  }

  // 2nd check to make sure the team given is valid, and not our own team
  if (team >= CTFNumOfTeams) {
    // not a valid team
    mprintf(0, "CTF: Invalid team passed to GivePlayerFlag() (team>=CTFNumOfTeams)\n");
    return false;
  }
  if (team == DMFCBase->GetPlayerTeam(pnum)) {
    // we can't add a flag of the same team to a player
    mprintf(0, "CTF: In GivePlayerFlag(), trying to add a player's home team flag\n");
    return false;
  }

  // 3rd, make sure no one else currently has this flag
  // we'll check our HasFlags[] first
  if (HasFlag[team] != -1) {
    // hmm, we have someone listed as already having this flag...odd
    mprintf(0, "CTF: In GivePlayerFlag(), trying to add a flag, but we see someone else should already have it\n");
    int player = HasFlag[team];
    if (DMFCBase->CheckPlayerNum(player)) {
      // this player is in the game...
      // make sure this player doesn't have the flag in his inventory
      while (DLLInvCheckItem(player, OBJ_POWERUP, FlagIDs[team])) {
        // we have it listed that he does
        mprintf(0, "CTF: In GivePlayerFlag(), we detected the flag in someone elses inventory\n");
        // remove all the flags that this player has of this team...very weird
        DLLInvRemove(player, OBJ_POWERUP, FlagIDs[team]);
        SetColoredBalls(player, false);
        // check to see if the player had a flag attached to him
        if (ChildFlags[team] != OBJECT_HANDLE_NONE && DMFCBase->GetLocalRole() == LR_SERVER) {
          // he does have a flag attached to him...kill it
          RemoveFlagFromPlayer(player, team);
        }
      }
    }
    // reset this value of the array
    HasFlag[team] = -1;
    if (DMFCBase->GetLocalRole() != LR_SERVER) {
      mprintf(0, "CTF: Game must be out of sync, requesting game state\n");
      DMFCBase->RequestGameState();
    }
  }

  // loop through all the players and make sure they don't have this flag
  for (int player = 0; player < DLLMAX_PLAYERS; player++) {
    // check to see if it's an active player
    if (!DMFCBase->CheckPlayerNum(player))
      continue;

    // remove all the flags the player has
    while (DLLInvCheckItem(player, OBJ_POWERUP, FlagIDs[team])) {
      mprintf(0, "CTF: In GivePlayerFlag(), detected a flag in a stranger's inventory\n");
      DLLInvRemove(player, OBJ_POWERUP, FlagIDs[team]);
      SetColoredBalls(player, false);
      // check to see if the player had a flag attached to him
      if (ChildFlags[team] != OBJECT_HANDLE_NONE && DMFCBase->GetLocalRole() == LR_SERVER) {
        // he does have a flag attached to him...kill it
        RemoveFlagFromPlayer(player, team);
      }
    }
  }

  // ok, when we get here everything should be ducky, just add the flag and do the necessary things
  DLLInvAddTypeID(pnum, OBJ_POWERUP, FlagIDs[team], -1, -1, 0, NULL);
  HasFlag[team] = pnum;
  SetColoredBalls(pnum);

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    // so we got here and added a flag to the player, now we need to attach the flag to the player
    if (!AddFlagToPlayer(pnum, team)) {
      // there was an error adding the flag,,,,ack!
      mprintf(0, "CTF: In GivePlayerFlag(), couldn't attach the flag to the player\n");
    }
  }

  return true;
}

// this function takes a flag away from the player, useful for when he scores, spews, disconnects, or observer modes
void LoseFlagForPlayer(int pnum, uint8_t team, bool remove_from_inven) {
  // 1st check the player number
  if (pnum < 0 || pnum >= DLLMAX_PLAYERS) {
    mprintf(0, "CTF:Invalid pnum passed to LoseFlagForPlayer()\n");
    return;
  }

  // 2nd check the team number
  if (team >= CTFNumOfTeams) {
    mprintf(0, "CTF:Invalid team passed to LoseFlagForPlayer()\n");
    return;
  }

  if (team == DMFCBase->GetPlayerTeam(pnum)) {
    mprintf(0, "CTF:Invalid team passed to LoseFlagForPlayer()...same team as player\n");
    return;
  }

  // ok, we have it registered that the flag belongs to us
  while (remove_from_inven && DLLInvCheckItem(pnum, OBJ_POWERUP, FlagIDs[team])) {
    DLLInvRemove(pnum, OBJ_POWERUP, FlagIDs[team]);
  }

  SetColoredBalls(pnum);
  HasFlag[team] = -1;

  // check to see if the player had a flag attached to him
  if (ChildFlags[team] != OBJECT_HANDLE_NONE) {
    // he does have a flag attached to him...kill it
    if (DMFCBase->GetLocalRole() == LR_SERVER) {
      // remove this flag and tell the clients to do so, cause we're the server
      RemoveFlagFromPlayer(pnum, team);
    }
  }
}

void OnGetTokenString(char *src, char *dest, int dest_size) {
  if (!stricmp(src, "flag")) {
    int mypnum = DMFCBase->GetPlayerNum();
    int flagcount = GetFlagCountForPlayer(mypnum);
    int flagmask = GetFlagMaskForPlayer(mypnum);
    int team;
    bool hasflag[DLLMAX_TEAMS];

    for (team = 0; team < CTFNumOfTeams; team++) {
      // draw all the flags the player has in his inventory
      if (flagmask & 0x01) {
        // player has this flag
        hasflag[team] = true;
      } else {
        hasflag[team] = false;
      }

      // rotate 1 bit for next flag
      flagmask = flagmask >> 1;
    }
    for (; team < DLLMAX_TEAMS; team++) {
      hasflag[team] = false;
    }

    switch (flagcount) {
    case 1: {
      char t[64];
      for (team = 0; team < CTFNumOfTeams; team++) {
        if (hasflag[team]) {
          strcpy(t, DMFCBase->GetTeamString(team));
          break;
        }
      }

      strncpy(dest, t, dest_size - 1);
      dest[dest_size - 1] = '\0';
      return;
    } break;
    case 2: {
      char t[2][64];
      int found = 0;
      for (team = 0; team < CTFNumOfTeams; team++) {
        if (hasflag[team]) {
          strcpy(t[found], DMFCBase->GetTeamString(team));
          found++;
          if (found == flagcount)
            break;
        }
      }

      char buffer[256];
      snprintf(buffer, sizeof(buffer), "%s and %s", t[0], t[1]);
      strncpy(dest, buffer, dest_size - 1);
      dest[dest_size - 1] = '\0';
      return;
    } break;
    case 3: {
      char t[3][64];
      int found = 0;
      for (team = 0; team < CTFNumOfTeams; team++) {
        if (hasflag[team]) {
          strcpy(t[found], DMFCBase->GetTeamString(team));
          found++;
          if (found == flagcount)
            break;
        }
      }

      char buffer[256];
      snprintf(buffer, sizeof(buffer), "%s, %s and %s", t[0], t[1], t[2]);
      strncpy(dest, buffer, dest_size - 1);
      dest[dest_size - 1] = '\0';
      return;

    } break;
    default:
      strncpy(dest, "No", dest_size - 1);
      dest[dest_size - 1] = '\0';
      return;
      break;
    }
  }

  DMFCBase->OnGetTokenString(src, dest, dest_size);
}
