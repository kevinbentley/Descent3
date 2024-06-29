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

 * $Logfile: /DescentIII/Main/entropy/EntropyBase.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:57:41 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: EntropyBase.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:57:41  kevinb
 * initial 1.5 import
 *
 *
 * 59    9/24/01 2:28p Matt
 * Allowed room for longer team name on results screen.
 *
 * 58    9/13/01 5:31p Matt
 * Added a team member list to the stats display.
 * Fixed a non-terminated string bug.
 *
 * 57    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 56    9/03/99 5:27p Jeff
 * fixed energy bug (going into an energy center with >100 energy)
 *
 * 55    8/17/99 5:53p Jeff
 * track ranks on PXO
 *
 * 54    7/23/99 2:31p Jeff
 * fixed bug where if the killer is not known, a player would still be
 * able to carry virus after dying.
 *
 * 53    7/15/99 1:18a Jeff
 * fixed up $scores
 *
 * 52    7/15/99 1:01a Jeff
 * added $scores support
 *
 * 51    7/13/99 12:11p Jeff
 * added some specific text taunt token decoding
 *
 * 50    7/12/99 2:27p Jeff
 * fixed PLR to only display the team label for the disconnected list if
 * there are people in the list.  Play fanfare and print out a message is
 * someone takes over the last base
 *
 * 49    7/11/99 6:54p Jeff
 * fixed PLR so it doesn't go off the screen on long lists and active
 * players in the game are shown first
 *
 * 48    6/08/99 7:08p Jeff
 * begining to comment for SDK release
 *
 * 47    5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 46    5/23/99 2:22a Jeff
 * added countdown.  fixed takeover time...off by .5 seconds
 *
 * 45    5/22/99 1:12a Jeff
 * play a sound on the server when picking up a virus
 *
 * 44    5/21/99 10:30p Jason
 * made some rule changes to make more fun
 *
 * 43    5/21/99 10:03a Jeff
 * hopefully filled in any remaining gaps related to have more than you
 * can carry virus loads
 *
 * 42    5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 41    5/12/99 11:28a Jeff
 * when a player scores, dont remove all virii, just what they used
 *
 * $NoKeywords: $
 */

#include "gamedll_header.h" //included by all mods, it includes all needed headers, etc.
#include <string.h>
#include "idmfc.h" //dmfc! (required)
#include "Entropy.h"
#include "Entropystr.h" //our string table for Entropy
#include "EntropyAux.h"

// the DMFC object, used throughout, and required by all mods
IDMFC *DMFCBase = NULL;
// our DmfcStats object, used for the F7 screen
static IDmfcStats *dstat = NULL;
// these are some helper pointers, so we don't have to constantly query
// DMFC for these arrays, we can query once and just save it for just future use.
object *dObjects;
static player *dPlayers;
room *dRooms;

////////////////////////////////////////////////////
// Customization flags
// These are 'the rules' to Entropy basically

// scoring
#define SCORE_PLYR_TAKEOVER_ROOM 5 // num points for a player when he/she takes over a room
#define SCORE_TEAM_WINSGAME 10     // num points for a team when they win a round
#define SCORE_TEAM_TAKEOVER_ROOM 3 // num points for a team when a teammate of their's takes over a room

// rates
#define REPAIR_RATE 5.0f    // units/sec of the repair room
#define ENERGY_RATE 5.0f    // units/sec of the energy room
#define DAMAGE_RATE 5.0f    // units/sec of damage when in an enemy room
#define ENERGY_CAP 100.0f   // max energy given to a player via an Energy room
#define SHIELD_CAP 100.0f   // max shields given to a player via a Repair room
#define VIRUS_SPEW 20.0f    // How long it takes for a lab to spew a virus
#define VIRUS_PER_KILL 2.0f // How many virii a player can carry per kill-in-a-row.

#define MINIMUM_VIRUS_COUNT 5 // Minimum number of virii needed to take over a room
#define TAKEOVER_TIME 3.0f    // How long a player must stand still to take over a room

////////////////////////////////////////////////////
struct tPlayerPos {
  float total_time;
  vector last_pos;
};

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

int TeamOwnedRooms[NUM_TEAMS];
static int TeamVirii[NUM_TEAMS][MAX_VIRII];
int NumberOfKillsSinceLastDeath[DLLMAX_PLAYERS];
static int SortedPLRPlayers[NUM_TEAMS][MAX_PLAYER_RECORDS];
int TeamScore[NUM_TEAMS];
static int SortedTeams[NUM_TEAMS];
static int SortedPlayers[MAX_PLAYER_RECORDS];
int EnergyText[NUM_TEAMS];
int RepairText[NUM_TEAMS];
int LabText[NUM_TEAMS];
static tPlayerPos TimeInRoom[DLLMAX_PLAYERS];
static bool DisplayScoreScreen;
int virus_id = -1;
int *RoomList = NULL;
int RoomCount;
static int Highlight_bmp = -1;
static bool display_my_welcome = false;
static float Server_last_play_damage_sound = 0;
static int Player_who_took_over_last_base = -1;

static int snd_repair_center = -1;
static int snd_energy_center = -1;
static int snd_score = -1;
static int snd_virus_destroy = -1;
static int snd_damage = -1;
static int snd_virus_pickup = -1;

// void DisplayScores(void);
static void DisplayHUDScores(struct tHUDItem *hitem);
static void DisplayWelcomeMessage(int player_num);
static void SortTeamScores(int *sortedindex, int *scores);
static void SaveStatsToFile(char *filename);
static void OnLabSpewTimer(void);
void RemoveVirusFromPlayer(int player_num, bool remove_all);
static bool ScanForLaboratory(int team, int *newlab);
static bool CompareDistanceTravel(vector *curr_pos, vector *last_pos);
static void OnDisconnectSaveStatsToFile(void);
static void OnLevelEndSaveStatsToFile(void);
static void OnGetTokenString(char *src, char *dest, int dest_size);
// Player in special room functions
static void DoIntervalPlayerFrame(void);
static void DoPlayerInLab(int pnum, float time);
static void DoPlayerInEnergy(int pnum, float time);
static void DoPlayerInRepair(int pnum, float time);
static void DoPlayerInEnemy(int pnum, float time);

extern void DoServerConfigureDialog(void);
static void OnPrintScores(int level);

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
  options->flags = DOF_MAXTEAMS | DOF_MINTEAMS;
  options->max_teams = NUM_TEAMS;
  options->min_teams = NUM_TEAMS;
  strcpy(options->game_name, TXT_GAMENAME);
  strcpy(options->requirements, "ENTROPY");
}

void DetermineScore(int precord_num, int column_num, char *buffer, int buffer_size) {
  player_record *pr = DMFCBase->GetPlayerRecord(precord_num);
  if (!pr || pr->state == STATE_EMPTY) {
    buffer[0] = '\0';
    return;
  }

  tPlayerStat *stat = (tPlayerStat *)pr->user_info;
  snprintf(buffer, buffer_size, "%d[%d]", (stat) ? stat->Score[DSTAT_LEVEL] : 0,
           (stat) ? stat->Score[DSTAT_OVERALL] : 0);
}

void TeamScoreCallback(int team, char *buffer, int buffer_size) {
  ASSERT(team >= 0 && team < NUM_TEAMS);

  snprintf(buffer, buffer_size, " %d", TeamScore[team]);
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
  DMFCBase->Set_OnClientPlayerDisconnect(OnClientPlayerDisconnect);
  DMFCBase->Set_OnServerPlayerChangeSegment(OnServerPlayerChangeSegment);
  DMFCBase->Set_OnClientPlayerChangeSegment(OnClientPlayerChangeSegment);
  DMFCBase->Set_OnServerCollide(OnServerCollide);
  DMFCBase->Set_OnControlMessage(OnControlMessage);
  DMFCBase->Set_OnClientShowUI(OnClientShowUI);
  DMFCBase->Set_OnGetTokenString(OnGetTokenString);
  DMFCBase->Set_OnPrintScores(OnPrintScores);

  // Setup arrays for easier to read code
  dObjects = DMFCBase->GetObjects();
  dPlayers = DMFCBase->GetPlayers();
  dRooms = DMFCBase->GetRooms();

  netgame_info *Netgame = DMFCBase->GetNetgameInfo();
  Netgame->flags |= (NF_TRACK_RANK);

  DMFCBase->GameInit(NUM_TEAMS);
  DLLCreateStringTable("entropy.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    *all_ok = 0;
    return;
  }

  // add the death and suicide messages
  DMFCBase->AddDeathMessage(TXT_KILLA, true);

  DMFCBase->AddSuicideMessage(TXT_SUICIDEA);

  // register special packet receivers
  DMFCBase->RegisterPacketReceiver(SPID_NEWPLAYER, GetGameStartPacket);
  DMFCBase->RegisterPacketReceiver(SPID_TAKEOVER, ReceiveTakeOverPacket);
  DMFCBase->RegisterPacketReceiver(SPID_ROOMINFO, ReceiveRoomInfo);
  DMFCBase->RegisterPacketReceiver(SPID_PICKUPVIRUS, ReceivePickupVirus);
  DMFCBase->RegisterPacketReceiver(SPID_VIRUSCREATE, DoVirusCreate);

  DMFCBase->SetNumberOfTeams(NUM_TEAMS);

  DMFCBase->AddHUDItemCallback(HI_TEXT, DisplayHUDScores);

  EnergyText[RED_TEAM] = DLLFindTextureName("RedEnergy");
  EnergyText[BLUE_TEAM] = DLLFindTextureName("BlueEnergy");
  RepairText[RED_TEAM] = DLLFindTextureName("RedRepair");
  RepairText[BLUE_TEAM] = DLLFindTextureName("BlueRepair");
  LabText[RED_TEAM] = DLLFindTextureName("RedLab");
  LabText[BLUE_TEAM] = DLLFindTextureName("BlueLab");

  snd_repair_center = DLLFindSoundName("EntropyRepair");
  snd_energy_center = DLLFindSoundName("EntropyEnergy");
  snd_score = DLLFindSoundName("EntropyScore");
  snd_virus_destroy = DLLFindSoundName("EntropyDestroy");
  snd_damage = DLLFindSoundName("HitEnergy");
  snd_virus_pickup = DLLFindSoundName("Powerup pickup");

  DMFCBase->SetupPlayerRecord(sizeof(tPlayerStat), (int (*)(void *, uint8_t *))pack_pstat,
                              (int (*)(void *, uint8_t *))unpack_pstat);

  virus_id = DLLFindObjectIDName("EntropyVirus");

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
  pl_col[4].width = 62;

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

  if (RoomList) {
    free(RoomList);
    RoomList = NULL;
  }

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
  for (i = 0; i < NUM_TEAMS; i++) {
    TeamScore[i] = 0;
  }
}

// The server has started a new level, so clear out level scores
void OnClientLevelStart(void) {
  DMFCBase->OnClientLevelStart();
  int i;

  for (i = 0; i < NUM_TEAMS; i++) {
    TeamOwnedRooms[i] = 0;
    for (int v = 0; v < MAX_VIRII; v++)
      TeamVirii[i][v] = -1;
  }

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

  // reset damage timer
  Server_last_play_damage_sound = 0;

  // reset the id to -1, so we are ready for the new level
  Player_who_took_over_last_base = -1;

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    DMFCBase->SetTimerInterval(OnLabSpewTimer, VIRUS_SPEW, -1.0f);
  }

  if (RoomList) {
    free(RoomList);
    RoomList = NULL;
  }
  RoomCount = 0;
  int r;
  for (r = 0; r <= DMFCBase->GetHighestRoomIndex(); r++) {
    if (dRooms[r].used) {
      int flags = dRooms[r].flags;
      if (flags & RF_SPECIAL1 || flags & RF_SPECIAL2 || flags & RF_SPECIAL3 || flags & RF_SPECIAL4 ||
          flags & RF_SPECIAL5 || flags & RF_SPECIAL6) {
        RoomCount++;
      }
    }
  }

  if (RoomCount == 0) {
    FatalError("No Special Rooms Defined");
    return;
  }

  RoomList = (int *)malloc(sizeof(int) * RoomCount);
  if (!RoomList) {
    FatalError("Out of memory");
    return;
  }

  bool room_used_already;
  int special_room_index = 0;

  for (r = 0; r <= DMFCBase->GetHighestRoomIndex(); r++) {
    if (dRooms[r].used) {
      if (dRooms[r].flags & RF_FUELCEN) {
        dRooms[r].flags &= ~RF_FUELCEN;
        dRooms[r].room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      }

      room_used_already = false;
      if (dRooms[r].flags & RF_SPECIAL1) { // Red Team Laboratory
        TeamOwnedRooms[RED_TEAM]++;
        room_used_already = true;
        PaintRoomWithTexture(LabText[RED_TEAM], r);
        RoomList[special_room_index] = r;
        special_room_index++;
      }
      if (dRooms[r].flags & RF_SPECIAL4) { // Blue Team Laboratory
        if (room_used_already) {
          dRooms[r].flags &= ~RF_SPECIAL4;
          dRooms[r].room_change_flags |= RCF_GOALSPECIAL_FLAGS;
        } else {
          TeamOwnedRooms[BLUE_TEAM]++;
          room_used_already = true;
          PaintRoomWithTexture(LabText[BLUE_TEAM], r);
          RoomList[special_room_index] = r;
          special_room_index++;
        }
      }
      if (dRooms[r].flags & RF_SPECIAL2) { // Red Team Energy Room
        if (room_used_already) {
          dRooms[r].flags &= ~RF_SPECIAL2;
          dRooms[r].room_change_flags |= RCF_GOALSPECIAL_FLAGS;
        } else {
          TeamOwnedRooms[RED_TEAM]++;
          room_used_already = true;
          PaintRoomWithTexture(EnergyText[RED_TEAM], r);
          RoomList[special_room_index] = r;
          special_room_index++;
        }
      }
      if (dRooms[r].flags & RF_SPECIAL5) { // Blue Team Energy Room
        if (room_used_already) {
          dRooms[r].flags &= ~RF_SPECIAL5;
          dRooms[r].room_change_flags |= RCF_GOALSPECIAL_FLAGS;
        } else {
          TeamOwnedRooms[BLUE_TEAM]++;
          room_used_already = true;
          PaintRoomWithTexture(EnergyText[BLUE_TEAM], r);
          RoomList[special_room_index] = r;
          special_room_index++;
        }
      }
      if (dRooms[r].flags & RF_SPECIAL3) { // Red Team Repair Room
        if (room_used_already) {
          dRooms[r].flags &= ~RF_SPECIAL3;
          dRooms[r].room_change_flags |= RCF_GOALSPECIAL_FLAGS;
        } else {
          TeamOwnedRooms[RED_TEAM]++;
          room_used_already = true;
          PaintRoomWithTexture(RepairText[RED_TEAM], r);
          RoomList[special_room_index] = r;
          special_room_index++;
        }
      }
      if (dRooms[r].flags & RF_SPECIAL6) { // Blue Team Repair Room
        if (room_used_already) {
          dRooms[r].flags &= ~RF_SPECIAL6;
          dRooms[r].room_change_flags |= RCF_GOALSPECIAL_FLAGS;
        } else {
          TeamOwnedRooms[BLUE_TEAM]++;
          room_used_already = true;
          PaintRoomWithTexture(RepairText[BLUE_TEAM], r);
          RoomList[special_room_index] = r;
          special_room_index++;
        }
      }
    }
  }

  // zero out other arrays
  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    NumberOfKillsSinceLastDeath[i] = 0;
    TimeInRoom[i].total_time = 0;
    RemoveVirusFromPlayer(i, true);
  }

  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    // spew 3 virii in each lab
    for (i = 0; i < 3; i++)
      OnLabSpewTimer();
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

  if (player_num != -1) {
    NumberOfKillsSinceLastDeath[player_num] = 0;
  }
  TimeInRoom[player_num].total_time = 0;
  RemoveVirusFromPlayer(player_num, true);
}

void OnServerPlayerChangeSegment(int player_num, int newseg, int oldseg) {
  if (player_num == -1) {
    DMFCBase->OnServerPlayerChangeSegment(player_num, newseg, oldseg);
    return;
  }

  // check to make sure it is an 'indoor' room and not terrain
  if (!ROOMNUM_OUTSIDE(newseg)) {
    // Check the room flags, see if we entered a special room
    room *rp = &dRooms[newseg];
    if (rp->flags & RF_EXTERNAL) {
      DMFCBase->OnServerPlayerChangeSegment(player_num, newseg, oldseg);
      return;
    }

    if ((rp->flags & RF_SPECIAL1) || (rp->flags & RF_SPECIAL2) || (rp->flags & RF_SPECIAL3) ||
        (rp->flags & RF_SPECIAL4) || (rp->flags & RF_SPECIAL5) || (rp->flags & RF_SPECIAL6)) {
      DMFCBase->CallClientEvent(EVT_CLIENT_GAMEPLAYERCHANGESEG, DMFCBase->GetMeObjNum(), DMFCBase->GetItObjNum(), -1);
      DMFCBase->CallOnClientPlayerChangeSegment(player_num, newseg, oldseg);
    }
  }

  DMFCBase->OnServerPlayerChangeSegment(player_num, newseg, oldseg);
}

void OnClientPlayerChangeSegment(int player_num, int newseg, int oldseg) {
  // someone has entered a special room
  TimeInRoom[player_num].total_time = 0;

  DMFCBase->OnClientPlayerChangeSegment(player_num, newseg, oldseg);
}

// We need to adjust the scores
void OnClientPlayerKilled(object *killer_obj, int victim_pnum) {
  int kpnum;

  if (victim_pnum != -1)
    RemoveVirusFromPlayer(victim_pnum, true);

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

  if (kpnum != -1) {
    if (kpnum == victim_pnum) {
      NumberOfKillsSinceLastDeath[kpnum] = 0;
    } else {
      NumberOfKillsSinceLastDeath[kpnum]++;

      if (victim_pnum != -1)
        NumberOfKillsSinceLastDeath[victim_pnum] = 0;
    }
  } else {
    // this would be the case if the room killed a player
    if (victim_pnum != -1)
      NumberOfKillsSinceLastDeath[victim_pnum] = 0;
  }

  // TODO: Handle a kill if killed by a room
  DMFCBase->OnClientPlayerKilled(killer_obj, victim_pnum);
}

void OnHUDInterval(void) {
  dstat->DoFrame();
  DMFCBase->DisplayOutrageLogo();

  DMFCBase->OnHUDInterval();
}

void OnInterval(void) {
  SortTeamScores(SortedTeams, TeamScore);
  // TODO: Correct Sorting based on score
  DMFCBase->GetSortedPlayerSlots(SortedPlayers, MAX_PLAYER_RECORDS);
  DoIntervalPlayerFrame();
  DMFCBase->OnInterval();
}

void OnClientPlayerDisconnect(int pnum) {
  if (pnum != -1) {
    NumberOfKillsSinceLastDeath[pnum] = 0;
  }
  DMFCBase->OnClientPlayerDisconnect(pnum);
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

  // if(key==K_E && DMFCBase->GetLocalRole()==LR_SERVER){
  //	DMFCBase->StartUIWindow(1);
  //}

  DMFCBase->OnKeypress(key);
}

void OnClientShowUI(int id, void *user_data) {
  if (id == 1)
    DoServerConfigureDialog();
  DMFCBase->OnClientShowUI(id, user_data);
}

void OnServerCollide(object *me_obj, object *it_obj) {
  if (!me_obj || !it_obj)
    return;

  if (virus_id == -1) {
    FatalError("Unable to find Virus Object");
    return;
  }

  if ((me_obj->type == OBJ_PLAYER) && (it_obj->type == OBJ_POWERUP) && (it_obj->id == virus_id)) {
    // determine what to do with this collision
    int virus_objnum = it_obj - dObjects;
    int virus_team = -1;
    int virus_index = -1;
    int player_num = me_obj->id;

    // find which team the virus belongs to
    for (int v = 0; v < MAX_VIRII; v++) {
      if (virus_objnum == TeamVirii[RED_TEAM][v]) {
        virus_team = RED_TEAM;
        virus_index = v;
        break;
      }
      if (virus_objnum == TeamVirii[BLUE_TEAM][v]) {
        virus_team = BLUE_TEAM;
        virus_index = v;
        break;
      }
    }
    if (virus_team == -1) {
      // hey! we hit a virus that doesn't belong to any team!!
      DLLmprintf(0, "Virus (%d) doesn't belong to any team, removing...\n", virus_objnum);
      DMFCBase->OnServerCollide(me_obj, it_obj);
      DLLSetObjectDeadFlag(it_obj, true, false);
      return;
    }

    int curr_count = DLLInvGetTypeIDCount(player_num, OBJ_POWERUP, it_obj->id);
    if (dPlayers[player_num].team == virus_team) {
      // a player has collided with a virus from his team
      // see if the player has enough kills to pick up this virus
      int max_carry = NumberOfKillsSinceLastDeath[player_num] * VIRUS_PER_KILL;
      if (curr_count + 1 > max_carry) {
        // the player can't carry another virii yet
        if (player_num == DMFCBase->GetPlayerNum()) {
          DLLAddHUDMessage(TXT_CANTCARRY);
        } else {
          DMFCBase->SendControlMessageToPlayer(player_num, VIRUS_NOTENOUGHKILLS);
        }
      } else {
        // pick this guy up
        TeamVirii[virus_team][virus_index] = -1;
        SendClientPickupVirus(player_num);
        DLLSetObjectDeadFlag(it_obj, true, true);
        if (snd_virus_pickup != -1) {
          DLLPlay2dSound(snd_virus_pickup, MAX_GAME_VOLUME);
        }
      }
    } else {
      // a player has collided with a virus from another team
      // kill this object
      TeamVirii[virus_team][virus_index] = -1;
      DLLSetObjectDeadFlag(it_obj, true, false);
      if (player_num == DMFCBase->GetPlayerNum()) {
        DLLAddHUDMessage(TXT_VIRUSDESTROYED);
        if (snd_virus_destroy != -1) {
          DLLPlay2dSound(snd_virus_destroy, MAX_GAME_VOLUME);
        }
      } else {
        DMFCBase->SendControlMessageToPlayer(player_num, VIRUS_DESTROYED);
      }
    }
  }

  DMFCBase->OnServerCollide(me_obj, it_obj);
}

void TakeOverRoom(int newteam, int oldteam, int roomnum, int victor) {
  if (ROOMNUM_OUTSIDE(roomnum)) {
    Int3();
    return;
  }

  bool server = false;
  bool success = false;
  if (DMFCBase->GetLocalRole() == LR_SERVER)
    server = true;

  TeamOwnedRooms[newteam]++;
  TeamOwnedRooms[oldteam]--;

  tPlayerStat *stat = (tPlayerStat *)DMFCBase->GetPlayerRecordData(victor);
  if (stat) {
    stat->Score[DSTAT_LEVEL] += SCORE_PLYR_TAKEOVER_ROOM;
    stat->Score[DSTAT_OVERALL] += SCORE_PLYR_TAKEOVER_ROOM;
    TeamScore[DMFCBase->GetPlayerTeam(victor)] += SCORE_TEAM_TAKEOVER_ROOM;

    if (snd_score != -1) {
      DLLPlay2dSound(snd_score, MAX_GAME_VOLUME);
    }
  }

  char room_buf[40];

  room *rp = &dRooms[roomnum];

  if (oldteam == RED_TEAM) {
    if (rp->flags & RF_SPECIAL1) {
      rp->flags &= ~RF_SPECIAL1;
      rp->flags |= RF_SPECIAL4;
      rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      PaintRoomWithTexture(LabText[BLUE_TEAM], roomnum);
      if (server)
        SendTakeOverPacket(newteam, oldteam, roomnum, victor);
      strcpy(room_buf, "Laboratory");
      success = true;
    }
    if (rp->flags & RF_SPECIAL2) {
      rp->flags &= ~RF_SPECIAL2;
      rp->flags |= RF_SPECIAL5;
      rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      PaintRoomWithTexture(EnergyText[BLUE_TEAM], roomnum);
      if (server)
        SendTakeOverPacket(newteam, oldteam, roomnum, victor);
      strcpy(room_buf, "Energy");
      success = true;
    }
    if (rp->flags & RF_SPECIAL3) {
      rp->flags &= ~RF_SPECIAL3;
      rp->flags |= RF_SPECIAL6;
      rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      PaintRoomWithTexture(RepairText[BLUE_TEAM], roomnum);
      if (server)
        SendTakeOverPacket(newteam, oldteam, roomnum, victor);
      strcpy(room_buf, "Repair");
      success = true;
    }
  } else {
    if (rp->flags & RF_SPECIAL4) {
      rp->flags &= ~RF_SPECIAL4;
      rp->flags |= RF_SPECIAL1;
      rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      PaintRoomWithTexture(LabText[RED_TEAM], roomnum);
      if (server)
        SendTakeOverPacket(newteam, oldteam, roomnum, victor);
      strcpy(room_buf, "Laboratory");
      success = true;
    }
    if (rp->flags & RF_SPECIAL5) {
      rp->flags &= ~RF_SPECIAL5;
      rp->flags |= RF_SPECIAL2;
      rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      PaintRoomWithTexture(EnergyText[RED_TEAM], roomnum);
      if (server)
        SendTakeOverPacket(newteam, oldteam, roomnum, victor);
      strcpy(room_buf, "Energy");
      success = true;
    }
    if (rp->flags & RF_SPECIAL6) {
      rp->flags &= ~RF_SPECIAL6;
      rp->flags |= RF_SPECIAL3;
      rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
      PaintRoomWithTexture(RepairText[RED_TEAM], roomnum);
      if (server)
        SendTakeOverPacket(newteam, oldteam, roomnum, victor);
      strcpy(room_buf, "Repair");
      success = true;
    }
  }

  if (!success) {
    DLLmprintf(0, "Invalid Takeover!!!!!!!\n");
    return;
  }

  // print out hud message (and sound?)
  char buffer[256];
  DLLmprintf(0, "old=%d new=%d\n", oldteam, newteam);
  snprintf(buffer, sizeof(buffer), TXT_TAKEOVER, (victor != -1) ? dPlayers[victor].callsign : TXT_NONAME,
           DMFCBase->GetTeamString(oldteam), room_buf);
  DLLAddHUDMessage(buffer);
  if (victor != -1)
    RemoveVirusFromPlayer(victor, false);

  if (TeamOwnedRooms[oldteam] <= 0) {
    TeamScore[newteam] += SCORE_TEAM_WINSGAME;
    Player_who_took_over_last_base = victor;
    if (server) {
      DMFCBase->EndLevel();
    }
  }

  int newlab;
  if (!ScanForLaboratory(oldteam, &newlab)) {
    // we need to turn newlab into a new laboratory
    int flag = 0;
    room *rp = &dRooms[newlab];
    if (oldteam == RED_TEAM) {
      rp->flags &= ~RF_SPECIAL2;
      rp->flags &= ~RF_SPECIAL3;
      flag = RF_SPECIAL1;
    } else {
      rp->flags &= ~RF_SPECIAL5;
      rp->flags &= ~RF_SPECIAL6;
      flag = RF_SPECIAL4;
    }
    rp->flags |= flag;
    rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
    PaintRoomWithTexture(LabText[oldteam], newlab);
  }
}

void DoPlayerInLab(int pnum, float time) {
  // nothing to do in here
}

void DoPlayerInEnergy(int pnum, float time) {
  // restore player's energy
  float amount = REPAIR_RATE * time;

  if (dPlayers[pnum].energy >= ENERGY_CAP)
    return;

  if (dPlayers[pnum].energy + amount > ENERGY_CAP)
    dPlayers[pnum].energy = ENERGY_CAP;
  else
    dPlayers[pnum].energy += amount;

  if (dPlayers[pnum].energy < ENERGY_CAP && pnum == DMFCBase->GetPlayerNum() && snd_energy_center >= 0) {
    DLLPlay2dSound(snd_energy_center, 1);
  }
}

void DoPlayerInRepair(int pnum, float time) {
  // restore player's shields, give at a rate of 3 per second
  float amount = REPAIR_RATE * time;
  float curr_shields = dObjects[dPlayers[pnum].objnum].shields;
  float max_amount = SHIELD_CAP - curr_shields;
  if (amount > max_amount)
    amount = max_amount;
  if (curr_shields >= SHIELD_CAP)
    return;

  DMFCBase->DoDamageToPlayer(pnum, PD_ENERGY_WEAPON, -amount);

  if (amount > 0 && pnum == DMFCBase->GetPlayerNum() && snd_repair_center >= 0) {
    DLLPlay2dSound(snd_repair_center, MAX_GAME_VOLUME * 0.75f);
  }
}

void DoPlayerInEnemy(int pnum, float time) {
  float damage_amount = DAMAGE_RATE * time;

  if (dPlayers[pnum].flags & PLAYER_FLAGS_DYING || dPlayers[pnum].flags & PLAYER_FLAGS_DEAD)
    return;

  // only play sound if player is a client, else do our own sound
  // so it isn't framerate dependant
  if (DMFCBase->GetLocalRole() == LR_SERVER) {
    if (pnum != DMFCBase->GetPlayerNum()) {
      DMFCBase->DoDamageToPlayer(pnum, PD_ENERGY_WEAPON, damage_amount, true);
    } else {
      DMFCBase->DoDamageToPlayer(pnum, PD_ENERGY_WEAPON, damage_amount, false);
      // time to play sound?
      float gt = DMFCBase->GetGametime();
      if (gt - Server_last_play_damage_sound > (1.0f / 5.0f)) // fake 5pps
      {
        // time to play sound
        Server_last_play_damage_sound = gt;
        if (snd_damage != -1) {
          DLLPlay2dSound(snd_damage, 1);
        }
      }
    }
  }

  // check to see if the player has 5 virii in his inventory, if he does, he's
  // trying to take over this room
  if (DLLInvGetTypeIDCount(pnum, OBJ_POWERUP, virus_id) < MINIMUM_VIRUS_COUNT)
    return;

  if (TimeInRoom[pnum].total_time == 0) {
    // update player position
    memcpy(&TimeInRoom[pnum].last_pos, &dObjects[dPlayers[pnum].objnum].pos, sizeof(vector));
  }

  vector curr_pos;
  memcpy(&curr_pos, &dObjects[dPlayers[pnum].objnum].pos, sizeof(vector));

  if (!CompareDistanceTravel(&curr_pos, &TimeInRoom[pnum].last_pos)) {
    // the player has moved!!!
    TimeInRoom[pnum].total_time = 0;
  } else {
    // still standing still
    TimeInRoom[pnum].total_time += time;
  }

  float time_remaining = (TAKEOVER_TIME - TimeInRoom[pnum].total_time);

  if (time_remaining <= 0) {
    // Take over the room!!!!
    if (DMFCBase->GetLocalRole() == LR_SERVER) {
      int newteam = DMFCBase->GetPlayerTeam(pnum);
      int oldteam = (newteam == RED_TEAM) ? BLUE_TEAM : RED_TEAM;
      int room = dObjects[dPlayers[pnum].objnum].roomnum;
      TakeOverRoom(newteam, oldteam, room, pnum);
    }
  }
}

void DoIntervalPlayerFrame(void) {
  static float last_frametime = 0;
  static bool update_this_frame = false;
  float frametime = 0;

  if (update_this_frame) {
    frametime = last_frametime + DMFCBase->GetFrametime();
    last_frametime = 0;
    update_this_frame = false;
  } else {
    last_frametime = DMFCBase->GetFrametime();
    update_this_frame = true;
    return;
  }

  for (int i = 0; i < DLLMAX_PLAYERS; i++) {
    if (DMFCBase->CheckPlayerNum(i)) {
      if (i == DMFCBase->GetPlayerNum() || DMFCBase->GetLocalRole() == LR_SERVER) {

        if (dObjects[dPlayers[i].objnum].type != OBJ_PLAYER)
          continue; // only work with OBJ_PLAYERS...this automatically handles observers,dedicated server

        // only need to be here if we are the player that has to do with this
        // or we are the server

        // first check to see if this player is in a special room
        if (ROOMNUM_OUTSIDE(dObjects[dPlayers[i].objnum].roomnum))
          continue;

        int team = DMFCBase->GetPlayerTeam(i);
        room *rp = &dRooms[dObjects[dPlayers[i].objnum].roomnum];
        if (rp->flags & RF_SPECIAL1) {
          if (team == RED_TEAM)
            DoPlayerInLab(i, frametime);
          else
            DoPlayerInEnemy(i, frametime);
        }
        if (rp->flags & RF_SPECIAL2) {
          if (team == RED_TEAM)
            DoPlayerInEnergy(i, frametime);
          else
            DoPlayerInEnemy(i, frametime);
        }
        if (rp->flags & RF_SPECIAL3) {
          if (team == RED_TEAM)
            DoPlayerInRepair(i, frametime);
          else
            DoPlayerInEnemy(i, frametime);
        }
        if (rp->flags & RF_SPECIAL4) {
          if (team == BLUE_TEAM)
            DoPlayerInLab(i, frametime);
          else
            DoPlayerInEnemy(i, frametime);
        }
        if (rp->flags & RF_SPECIAL5) {
          if (team == BLUE_TEAM)
            DoPlayerInEnergy(i, frametime);
          else
            DoPlayerInEnemy(i, frametime);
        }
        if (rp->flags & RF_SPECIAL6) {
          if (team == BLUE_TEAM)
            DoPlayerInRepair(i, frametime);
          else
            DoPlayerInEnemy(i, frametime);
        }
      }
    }
  }
}

bool compare_slots(int a, int b) {
  int ascore, bscore;
  player_record *apr, *bpr;
  tPlayerStat *as, *bs;

  apr = DMFCBase->GetPlayerRecord(a);
  bpr = DMFCBase->GetPlayerRecord(b);
  if (!apr)
    return true;
  if (!bpr)
    return false;
  as = (tPlayerStat *)apr->user_info;
  bs = (tPlayerStat *)bpr->user_info;
  if (!as)
    return true;
  if (!bs)
    return false;

  if (apr->state == STATE_EMPTY)
    return true;
  if (bpr->state == STATE_EMPTY)
    return false;
  if ((apr->state == STATE_INGAME) && (bpr->state == STATE_INGAME)) {
    // both players were in the game
    ascore = as->Score[DSTAT_LEVEL];
    bscore = bs->Score[DSTAT_LEVEL];
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
  ascore = as->Score[DSTAT_LEVEL];
  bscore = bs->Score[DSTAT_LEVEL];
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
  int TeamCount[NUM_TEAMS];
  int team;
  for (i = 0; i < NUM_TEAMS; i++)
    TeamCount[i] = 0;
  for (i = 0; i < MAX_PLAYER_RECORDS; i++) {
    int slot = SortedPlayers[i];
    player_record *pr = DMFCBase->GetPlayerRecord(slot);
    if (pr && pr->state != STATE_EMPTY) {

      if (DMFCBase->IsPlayerDedicatedServer(pr))
        continue; // skip dedicated server

      team = (pr->state == STATE_INGAME) ? dPlayers[pr->pnum].team : pr->team;
      SortedPLRPlayers[team][TeamCount[team]] = slot;
      TeamCount[team]++;
    }
  }
  for (i = 0; i < NUM_TEAMS; i++) {
    if (TeamCount[i] < MAX_PLAYER_RECORDS)
      SortedPLRPlayers[i][TeamCount[i]] = -1;
  }

  if (Player_who_took_over_last_base != -1) {
    // play a fanfare!
    if (snd_score != -1) {
      DLLPlay2dSound(snd_score, MAX_GAME_VOLUME);
    }
  }

  DMFCBase->OnPLRInit();
}

void OnPLRInterval(void) {
  DMFCBase->OnPLRInterval();

  int TeamCol = 35;
  int NameCol = 165;
  int KillsCol = 335;
  int DeathsCol = 375;
  int SuicidesCol = 425;
  int y = 40;
  int slot;
  player_record *pr;

  DLLgrtext_SetFont((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]);
  int height = DLLgrfont_GetHeight((DMFCBase->GetGameFontTranslateArray())[SMALL_UI_FONT_INDEX]) + 1;

  if (Player_who_took_over_last_base != -1) {
    // print out at the top who took over the last room
    int team = (DMFCBase->GetPlayerTeam(Player_who_took_over_last_base) == RED_TEAM) ? BLUE_TEAM : RED_TEAM;
    DLLgrtext_SetColor(GR_RGB(40, 255, 40));
    char message[384];
    snprintf(message, sizeof(message), "%s successfully took over %s team's last base!",
             dPlayers[Player_who_took_over_last_base].callsign, DMFCBase->GetTeamString(team));
    DLLgrtext_CenteredPrintf(0, y, message);
    y += height;
  }

  // print out header
  DLLgrtext_SetColor(GR_RGB(255, 255, 150));
  DLLgrtext_Printf(NameCol, y, TXT_PILOT);
  DLLgrtext_Printf(KillsCol, y, TXT_KILLS);
  DLLgrtext_Printf(DeathsCol, y, TXT_DEATHS);
  DLLgrtext_Printf(SuicidesCol, y, TXT_SUICIDES);
  y += height;

  tPlayerStat *stat;
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
      DLLgrtext_Printf(TeamCol, y, TXT_HUDDISPLAY, DMFCBase->GetTeamString(team), TeamScore[team]);
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

        stat = (tPlayerStat *)pr->user_info;
        // valid player
        DLLgrtext_Printf(NameCol, y, "%s %d[%d]", pr->callsign, (stat) ? stat->Score[DSTAT_LEVEL] : 0,
                         (stat) ? stat->Score[DSTAT_OVERALL] : 0);
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

void OnControlMessage(uint8_t msg, int from_pnum) {
  switch (msg) {
  case VIRUS_NOTENOUGHKILLS:
    DLLAddHUDMessage(TXT_CANTCARRY);
    break;
  case VIRUS_CANTKILL:
    DLLAddHUDMessage(TXT_CANTKILLVIRUS);
    break;
  case VIRUS_DESTROYED:
    DLLAddHUDMessage(TXT_VIRUSDESTROYED);
    if (snd_virus_destroy != -1) {
      DLLPlay2dSound(snd_virus_destroy, MAX_GAME_VOLUME);
    }
    break;
  default:
    DMFCBase->OnControlMessage(msg, from_pnum);
    break;
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
  tPlayerStat *st;
  int count, p;

  // sort the stats
  DMFCBase->GetSortedPlayerSlots(sortedslots, MAX_PLAYER_RECORDS);
  SortTeamScores(SortedTeams, TeamScore);
  count = 1;

  snprintf(buffer, sizeof(buffer), TXT_SAVESTATSA, (DMFCBase->GetNetgameInfo())->name,
           (DMFCBase->GetCurrentMission())->cur_level);
  DLLcf_WriteString(file, buffer);

  for (p = 0; p < NUM_TEAMS; p++) {
    int team_i = SortedTeams[p];
    memset(buffer, ' ', BUFSIZE);
    snprintf(tempbuffer, sizeof(tempbuffer), TXT_TEAMINFO, DMFCBase->GetTeamString(team_i));
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

    snprintf(buffer, sizeof(buffer), TXT_TEAMINFO, DMFCBase->GetTeamString(team_i));
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

  snprintf(buffer, sizeof(buffer), "%s", TXT_CURRRANKINGS);
  DLLcf_WriteString(file, buffer);

  snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSB);
  DLLcf_WriteString(file, buffer);
  strcpy(buffer, "-----------------------------------------------------------------------------");
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

  DLLcf_WriteString(file, TXT_SAVESTATSC);

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
        snprintf(buffer, sizeof(buffer), "%s", TXT_SAVESTATSD);
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
  DLLAddHUDMessage(TXT_SAVED);
}

#define ROOTFILENAME "Entropy"
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

void DisplayHUDScores(struct tHUDItem *hitem) {
  if (display_my_welcome) {
    DisplayWelcomeMessage(DMFCBase->GetPlayerNum());
    display_my_welcome = false;
  }

  if (DisplayScoreScreen)
    return;

  // Display the countdown if there should be one
  if (IsPlayerInEnemy(DMFCBase->GetPlayerNum()) &&
      DLLInvGetTypeIDCount(DMFCBase->GetPlayerNum(), OBJ_POWERUP, virus_id) >= MINIMUM_VIRUS_COUNT) {
    float time_remaining = (TAKEOVER_TIME - TimeInRoom[DMFCBase->GetPlayerNum()].total_time);

    int font = (DMFCBase->GetGameFontTranslateArray())[BIG_FONT_INDEX];
    DLLgrtext_SetFont(font);
    int fontheight = DLLgrfont_GetHeight(font);

    char buffer[255];
    int max_w = DMFCBase->GetGameWindowW();
    snprintf(buffer, sizeof(buffer), "T - %.1f", (time_remaining >= 0) ? time_remaining : 0);
    int lwidth = DLLgrtext_GetTextLineWidth(buffer);
    DLLgrtext_SetColor(GR_RGB(40, 255, 40));
    DLLgrtext_SetAlpha(255);
    DLLgrtext_Printf((max_w / 2) - (lwidth / 2), fontheight * 5, buffer);
  }

  int font = (DMFCBase->GetGameFontTranslateArray())[HUD_FONT_INDEX];
  int height = DLLgrfont_GetHeight(font) + 3;
  DLLgrtext_SetFont(font);

  int y = (DMFCBase->GetGameWindowH() / 2) - ((height * 3) / 2);
  int x = 520;
  int team;
  uint8_t alpha = DMFCBase->ConvertHUDAlpha((uint8_t)((DisplayScoreScreen) ? 128 : 255));

  team = DMFCBase->GetMyTeam();
  DLLRenderHUDText(DMFCBase->GetTeamColor(team), alpha, 0, x, 0, TXT_TEAMINFO, DMFCBase->GetTeamString(team));

  // determine coordinates to use here
  // we'll use a virtual width of 85 pixels on a 640x480 screen
  // so first determine the new width
  int name_width = 100.0f * DMFCBase->GetHudAspectX();
  int score_width = DLLgrtext_GetTextLineWidth("888");
  int name_x = DMFCBase->GetGameWindowW() - name_width - score_width - 10;
  int score_x = DMFCBase->GetGameWindowW() - score_width - 5;
  char buffer[256];

  for (int i = 0; i < NUM_TEAMS; i++) {
    team = SortedTeams[i];

    if (team == DMFCBase->GetMyTeam()) {
      if (Highlight_bmp > BAD_BITMAP_HANDLE) {
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
    }

    snprintf(buffer, sizeof(buffer), TXT_HUDSCORE, DMFCBase->GetTeamString(team), TeamOwnedRooms[team]);
    DMFCBase->ClipString(name_width, buffer, true);

    DLLgrtext_SetAlpha(alpha);
    DLLgrtext_SetColor(DMFCBase->GetTeamColor(team));
    DLLgrtext_Printf(name_x, y, buffer);
    DLLgrtext_Printf(score_x, y, "[%d]", TeamScore[team]);

    y += height;
  }
  DLLgrtext_SetColor(GR_WHITE);
  DLLgrtext_Printf(name_x, y, TXT_VIRUSLOAD, DLLInvGetTypeIDCount(DMFCBase->GetPlayerNum(), OBJ_POWERUP, virus_id),
                   (int)(NumberOfKillsSinceLastDeath[DMFCBase->GetPlayerNum()] * VIRUS_PER_KILL));
  y += height;
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
    DLLAddColoredHUDMessage(DMFCBase->GetTeamColor(team), TXT_TEAMJOIN, DMFCBase->GetTeamString(team));
  } else {
    int team = dPlayers[player_num].team;
    if (team == -1)
      return;

    DLLAddColoredHUDMessage(DMFCBase->GetTeamColor(team), TXT_JOIN, name_buffer, DMFCBase->GetTeamString(team));
  }
}

void OnLabSpewTimer(void) {
  int max_rooms = DMFCBase->GetHighestRoomIndex() + 1;
  int objnum;
  int index;
  int virus_count;

  for (int r = 0; r < RoomCount; r++) {
    if (dRooms[RoomList[r]].flags & RF_SPECIAL1) {
      index = -1;
      virus_count = 0;
      for (int v = 0; v < MAX_VIRII; v++) {
        if (TeamVirii[RED_TEAM][v] == -1) {
          // insert here
          index = v;
        } else {
          if (dObjects[TeamVirii[RED_TEAM][v]].roomnum == RoomList[r])
            virus_count++;
        }
      }

      // only create virus if we found a slot and there are less than MAX_VIRII_PER_ROOM
      // in the room
      if (virus_count < MAX_VIRII_PER_ROOM && index != -1) {
        objnum = SpewObjectInRoom(OBJ_POWERUP, virus_id, RoomList[r]);
        TeamVirii[RED_TEAM][index] = objnum;
      }
    }
    if (dRooms[RoomList[r]].flags & RF_SPECIAL4) {
      index = -1;
      virus_count = 0;
      for (int v = 0; v < MAX_VIRII; v++) {
        if (TeamVirii[BLUE_TEAM][v] == -1) {
          // insert here
          index = v;
        } else {
          if (dObjects[TeamVirii[BLUE_TEAM][v]].roomnum == RoomList[r])
            virus_count++;
        }
      }
      // only create virus if we found a slot and there are less than MAX_VIRII_PER_ROOM
      // in the room
      if (virus_count < MAX_VIRII_PER_ROOM && index != -1) {
        objnum = SpewObjectInRoom(OBJ_POWERUP, virus_id, RoomList[r]);
        TeamVirii[BLUE_TEAM][index] = objnum;
      }
    }
  }
}

void RemoveVirusFromPlayer(int player_num, bool remove_all) {
  int inv_count = DLLInvGetTypeIDCount(player_num, OBJ_POWERUP, virus_id);

  if (!remove_all) {
    ASSERT(inv_count >= MINIMUM_VIRUS_COUNT);
    inv_count = MINIMUM_VIRUS_COUNT;
  }

  for (int i = 0; i < inv_count; i++) {
    DLLInvRemove(player_num, OBJ_POWERUP, virus_id);
  }
}

// returns true if there is at least 1 lab, else returns the room which sould be a lab in newlab
bool ScanForLaboratory(int team, int *newlab) {
  *newlab = 0;
  int flag;
  int ef, rf;
  bool found = false;

  flag = (team == RED_TEAM) ? RF_SPECIAL1 : RF_SPECIAL4;
  ef = (team == RED_TEAM) ? RF_SPECIAL2 : RF_SPECIAL5;
  rf = (team == RED_TEAM) ? RF_SPECIAL3 : RF_SPECIAL6;

  for (int r = 0; r < RoomCount; r++) {
    room *rp = &dRooms[RoomList[r]];
    if (rp->flags & flag) {
      // we found a lab
      return true;
    }
    if ((rp->flags & ef) && (!found)) {
      found = true;
      *newlab = RoomList[r];
    }
    if ((rp->flags & rf) && (!found)) {
      found = true;
      *newlab = RoomList[r];
    }
  }
  return false;
}

bool CompareDistanceTravel(vector *curr_pos, vector *last_pos) {
  vector result;
  float a, b, c, bc, dist;

  result.x = curr_pos->x - last_pos->x;
  result.y = curr_pos->y - last_pos->y;
  result.z = curr_pos->z - last_pos->z;

  a = fabs(result.x);
  b = fabs(result.y);
  c = fabs(result.z);

  if (a < b) {
    float t = a;
    a = b;
    b = t;
  }

  if (b < c) {
    float t = b;
    b = c;
    c = t;

    if (a < b) {
      float t = a;
      a = b;
      b = t;
    }
  }

  bc = (b / 4) + (c / 8);

  dist = a + bc + (bc / 2);

  if (dist > 5) {
    memcpy(last_pos, curr_pos, sizeof(vector));
    return false;
  } else {
    return true;
  }
}

bool IsPlayerInEnemy(int pnum) {
  if (!DMFCBase->CheckPlayerNum(pnum))
    return false;

  if (dObjects[dPlayers[pnum].objnum].type != OBJ_PLAYER)
    return false; // only work with OBJ_PLAYERS...this automatically handles observers,dedicated server

  // first check to see if this player is in a special room
  if (ROOMNUM_OUTSIDE(dObjects[dPlayers[pnum].objnum].roomnum))
    return false;

  int team = DMFCBase->GetPlayerTeam(pnum);
  room *rp = &dRooms[dObjects[dPlayers[pnum].objnum].roomnum];

  if (team != RED_TEAM) {
    if ((rp->flags & RF_SPECIAL1) || (rp->flags & RF_SPECIAL2) || (rp->flags & RF_SPECIAL3)) {
      return true;
    }
  }

  if (team != BLUE_TEAM) {
    if ((rp->flags & RF_SPECIAL4) || (rp->flags & RF_SPECIAL5) || (rp->flags & RF_SPECIAL6)) {
      return true;
    }
  }

  return false;
}

void OnGetTokenString(char *src, char *dest, int dest_size) {
  if (!stricmp(src, "virus")) {
    int count = DLLInvGetTypeIDCount(DMFCBase->GetPlayerNum(), OBJ_POWERUP, virus_id);
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%d", count);
    strncpy(dest, buffer, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return;
  }

  DMFCBase->OnGetTokenString(src, dest, dest_size);
}

void OnPrintScores(int level) {
  char buffer[256];
  char name[70];
  size_t t;
  size_t pos[6];
  size_t len[6];

  netplayer *dNetPlayers = DMFCBase->GetNetPlayers();

  for (int i = 0; i < NUM_TEAMS; i++) {
    snprintf(buffer, sizeof(buffer), "%s:%d\n", DMFCBase->GetTeamString(i), TeamScore[i]);
    DPrintf(buffer);
  }

  memset(buffer, ' ', 256);

  pos[0] = 0;
  t = len[0] = 30; // give ample room for pilot name
  pos[1] = pos[0] + t + 1;
  t = len[1] = strlen(TXT_SCORE);
  pos[2] = pos[1] + t + 1;
  t = len[2] = strlen(TXT_KILLS_SHORT);
  pos[3] = pos[2] + t + 1;
  t = len[3] = strlen(TXT_DEATHS_SHORT);
  pos[4] = pos[3] + t + 1;
  t = len[4] = strlen(TXT_SUICIDES_SHORT);
  pos[5] = pos[4] + t + 1;
  t = len[5] = strlen(TXT_PING);

  memcpy(&buffer[pos[0]], TXT_PILOT, strlen(TXT_PILOT));
  memcpy(&buffer[pos[1]], TXT_SCORE, len[1]);
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
