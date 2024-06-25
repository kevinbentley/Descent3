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

* $Logfile: /DescentIII/Main/mtclient/mtgametrack.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:58:40 $
* $Author: kevinb $
*
* Game Tracker client code
*
* $Log: not supported by cvs2svn $
 *
 * 17    10/03/01 12:44a Kevin
 * Smaller version of pxo packets
 *
 * 16    9/02/99 3:16p Kevin
 * Macintosh byte ordering fixes
 *
 * 15    8/25/99 2:38p Samir
 * added byteswap.h for INTEL_INT.
 *
 * 14    8/24/99 5:47p Kevin
 * Macintosh crap
 *
 * 13    7/06/99 5:52p Kevin
 * PXO & multiplayer fixes for the patch
 *
 * 12    5/05/99 5:23p Kevin
 * fixed some bugs on the gamelist
 *
 * 11    5/04/99 7:29p Kevin
 * Fixed bug that caused the server to send his game info twice whenever
 * the level starts.
 *
 * 10    5/04/99 5:39p Kevin
 * connection dll & pxo game tracking improvements (added server type to
 * list)
 *
 * 9     4/19/99 8:35p Jeff
 * Compile under Linux
 *
 * 8     3/25/99 3:26p Kevin
 * Made PXO games be based on your chat channel
 *
 * 7     1/07/99 11:51a Kevin
 * Added support for joining servers on alternate ports and hosting behind
 * a proxy/firewall
 *
 * 6     12/30/98 12:16p Kevin
 * Auto Mission Download system
 *
 * 5     12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 4     10/19/98 9:50a Kevin
 * Added nettest application
 *
 * 3     7/27/98 5:31p Kevin
 * Sound/Bitmap exchange system
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/21/98 11:08a Kevin
 *
 * 6     5/14/98 11:07a Kevin
 * Made gameover packet to the tracker reliable
 *
 * 5     5/04/98 12:53p Kevin
 * Fixed mastertracker resend stuff
 *
 * 4     4/30/98 3:49p Kevin
 * Mastertracker pilot stats
 *
 * 3     4/24/98 3:50p Kevin
 * Added mastertracker game tracking support
 *
 * 2     4/23/98 4:49p Kevin
 * Added Master tracker Game tracker support
 *
 * 1     4/23/98 3:26p Kevin
 * Initial version
*
* $NoKeywords: $
*/

/*
  InitGameTracker(int game_type); //D3 or Freespace
  //Call periodically so we can send our update, and make sure it is received
  IdleGameTracker();
  StartTrackerGame(void *buffer)  //Call with a freespace_net_game_data or d3_net_game_data structure
  //Call with a freespace_net_game_data or d3_net_game_data structure
  //Updates our memory so when it is time, we send the latest game data
  UpdateGameData(gamedata);
  //Call to signify end of game
  RequestGameList();//Sends a GNT_GAMELIST_REQ packet to the server.
  game_list * GetGameList();//returns a pointer to a game_list struct

*/
#ifdef WIN32
#include <windows.h>
#endif

#include <cstring>
#include <ctime>

#include "pstypes.h"
#include "networking.h"
#include "mtgametrack.h"
#include "byteswap.h"
#include "mt_net.h"

// extern float DLLtimer_GetTime(void);
typedef float (*timer_GetTime_fp)();
extern timer_GetTime_fp DLLtimer_GetTime;

typedef void (*HandleGamePacket_fp)(uint8_t *data, int len, network_address *from);

typedef int (*nw_RegisterCallback_fp)(HandleGamePacket_fp, uint8_t id);
extern nw_RegisterCallback_fp DLLnw_RegisterCallback;

typedef int (*nw_DoReceiveCallbacks_fp)();
extern nw_DoReceiveCallbacks_fp DLLnw_DoReceiveCallbacks;

#if (defined(LOGGER) && (!defined(RELEASE)))
#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)
#else
#define DLLmprintf(...)
#endif

typedef void (*Debug_ConsolePrintf_fp)(int n, const char *format, ...);
extern Debug_ConsolePrintf_fp DLLDebug_ConsolePrintf;

// Variables

static game_list GameBuffer[MAX_GAME_BUFFERS];
static int GameType; // d3 or fs

static float LastTrackerUpdate;
static float LastSentToTracker;

static float LastGameOverPacket;
static float FirstGameOverPacket;

static int SendingGameOver;

static uint32_t TrackerAckdUs;
static uint32_t TrackerGameIsRunning;

static game_packet_header TrackerGameData;
static game_packet_header GameListReq;
static game_packet_header TrackAckPacket;
static game_packet_header GameOverPacket;

static game_packet_header inpacket;

static d3_net_game_data_tiny *D3TrackerGameData;

extern int DLLnw_ListenPort;
extern uint16_t DLLPXOPort;
extern char *DLLPXO_hosted_lobby_name;

int InitGameTrackerClient(int gametype) {
  GameType = gametype;
  LastTrackerUpdate = 0;
  switch (gametype) {
  case GT_FREESPACE:
    //	TrackerGameData.len = GAME_HEADER_ONLY_SIZE+sizeof(freespace_net_game_data);
    break;
  case GT_DESCENT3:
    TrackerGameData.len = INTEL_INT(GAME_HEADER_ONLY_SIZE + sizeof(d3_net_game_data_short));
    break;
  case GT_D3TNG:
    TrackerGameData.len = INTEL_INT(GAME_HEADER_ONLY_SIZE + sizeof(d3_net_game_data_tiny));
    break;
  }
  TrackerGameData.game_type = gametype;                  // 1==freespace (GT_FREESPACE), 2==D3, 3==tuberacer, etc.
  TrackerGameData.type = INTEL_INT(GNT_GAMEUPDATE_TINY); // Used to specify what to do ie. Add a new net game
                                                         // (GNT_GAMESTARTED), remove a net game (game over), etc.

  D3TrackerGameData = (d3_net_game_data_tiny *)&TrackerGameData.data;
  if (DLLPXOPort) {
    D3TrackerGameData->options = 1;
    D3TrackerGameData->arg1 = DLLPXOPort;
  }
  GameListReq.game_type = gametype;
  GameListReq.type = INTEL_INT(GNT_GAMELIST_LITE_FILTER_REQ);
  GameListReq.len = INTEL_INT(GAME_HEADER_ONLY_SIZE);

  TrackAckPacket.game_type = gametype;
  TrackAckPacket.len = INTEL_INT(GAME_HEADER_ONLY_SIZE);
  TrackAckPacket.type = INTEL_INT(GNT_CLIENT_ACK);

  GameOverPacket.game_type = gametype;
  GameOverPacket.len = INTEL_INT(GAME_HEADER_ONLY_SIZE);
  GameOverPacket.type = INTEL_INT(GNT_GAMEOVER);

  SendingGameOver = 0;

  DLLnw_RegisterCallback(HandleGamePacket, PXO_NETID_GAME_TRACKER);
  return 1;
}

void IdleGameTracker() {
  DLLnw_DoReceiveCallbacks();
  // uint32_t bytesin;
  // mprintf(0,"IdleGameTracker() entered.\n");
  if ((TrackerGameIsRunning) && ((DLLtimer_GetTime() - LastTrackerUpdate) > TRACKER_UPDATE_INTERVAL)) {

    struct tm *newtime;
    time_t aclock;
    time(&aclock); /* Get time in seconds */
    newtime = localtime(&aclock);
    // Time to update the tracker again
    DLLmprintf(0, "[%.24s] Updating the PXO game tracker!\n", asctime(newtime));
    SendGameTrackerPacker(&TrackerGameData);
    //		sendto(gamesock,(const char *)&TrackerGameData,TrackerGameData.len,0,(SOCKADDR
    //*)&gtrackaddr,sizeof(SOCKADDR_IN));
    TrackerAckdUs = 0;
    LastTrackerUpdate = DLLtimer_GetTime();
    LastSentToTracker = DLLtimer_GetTime();
  } else if ((TrackerGameIsRunning) && (!TrackerAckdUs) &&
             ((DLLtimer_GetTime() - LastSentToTracker) > TRACKER_RESEND_TIME)) {
    // We still haven't been acked by the last packet and it's time to resend.

    struct tm *newtime;
    time_t aclock;
    time(&aclock); /* Get time in seconds */
    newtime = localtime(&aclock);
    // Time to update the tracker again
    DLLmprintf(0, "[%.24s] (Resending) Updating the PXO game tracker!\n", asctime(newtime));

    SendGameTrackerPacker(&TrackerGameData);
    TrackerAckdUs = 0;
    LastTrackerUpdate = DLLtimer_GetTime();
    LastSentToTracker = DLLtimer_GetTime();
  }

  if (SendingGameOver) {
    if ((DLLtimer_GetTime() - LastGameOverPacket) > TRACKER_RESEND_TIME) {
      // resend
      LastGameOverPacket = DLLtimer_GetTime();
      SendGameTrackerPacker(&GameOverPacket);
    } else if ((DLLtimer_GetTime() - FirstGameOverPacket) > TRACKER_TIMEOUT) {
      // Giving up, it timed out.
      SendingGameOver = 3;
    }
  }
}

void HandleGamePacket(uint8_t *data, int len, network_address *from) {

  memcpy(&inpacket, data, sizeof(inpacket));

  // Check to make sure the packets ok
  if (len) {
    switch (INTEL_INT(inpacket.type)) {
    case GNT_SERVER_ACK:
      // The server got our packet so we can stop sending now
      TrackerAckdUs = 1;
      if (SendingGameOver) {
        SendingGameOver = 2;
      }
      break;
    case GNT_GAMELIST_LITE_DATA:
      if (len < (GAME_HEADER_ONLY_SIZE + sizeof(game_list))) {
        DLLmprintf(0, "(%d) packet is too small!\n", len);
      }
      // Woohoo! Game data! put it in the buffer (if one's free)
      // DLLmprintf(0,"GNT_GAMELIST_LITE_DATA received.\n");
      for (int i = 0; i < MAX_GAME_BUFFERS; i++) {
        if (GameBuffer[i].game_type == GT_UNUSED) {
          memset(&GameBuffer[i], 0, sizeof(game_list));
          memcpy(&GameBuffer[i], inpacket.data, len - GAME_HEADER_ONLY_SIZE);
          i = MAX_GAME_BUFFERS + 1;
        }
      }
      break;
    }
    // mprintf(0,"Sending ACK.\n");
    AckPacket(inpacket.sig);
  }
}

void UpdateGameData(void *buffer) {
  if (GameType == GT_FREESPACE) {
    //		memcpy(FreeSpaceTrackerGameData,buffer,sizeof(freespace_net_game_data));
  } else if (GameType == GT_DESCENT3) {
    memcpy(D3TrackerGameData, buffer, sizeof(d3_net_game_data_short));
  } else if (GameType == GT_D3TNG) {
    memcpy(D3TrackerGameData, buffer, sizeof(d3_net_game_data_tiny));
  }
}

game_list gl;

game_list *GetGameList() {
  memset(&gl, 0, sizeof(gl));
  for (auto & i : GameBuffer) {
    if (i.game_type != GT_UNUSED) {
      memcpy(&gl, &i, sizeof(gl));
      i.game_type = GT_UNUSED;
      return &gl;
    }
  }
  return nullptr;
}

void RequestGameList() {
  // Zero out all games
  for (auto & i : GameBuffer) {
    memset(&i, 0, sizeof(game_list));
  }

  int len = strlen(DLLPXO_hosted_lobby_name) + 1;
  memcpy(GameListReq.data, DLLPXO_hosted_lobby_name, len);
  GameListReq.len = D3::convert_le<uint32_t>(GAME_HEADER_ONLY_SIZE + len);
  SendGameTrackerPacker(&GameListReq);
}

int SendGameOver() {
  IdleGameTracker();

  if (SendingGameOver == 3) {
    // Request timed out.
    return 2;
  }
  if (SendingGameOver == 2) {
    SendingGameOver = 0;
    return 1;
  }
  if (SendingGameOver == 1) {
    // Wait until it's sent.
    return 0;
  }
  if (SendingGameOver == 0) {
    LastGameOverPacket = DLLtimer_GetTime();
    FirstGameOverPacket = DLLtimer_GetTime();
    SendingGameOver = 1;
    TrackerGameIsRunning = 0;
    SendGameTrackerPacker(&GameOverPacket);
    return 0;
  }
  return 0;
}

void AckPacket(int sig) {
  TrackAckPacket.sig = sig;
  SendGameTrackerPacker(&TrackAckPacket);
}

void StartTrackerGame(void *buffer) {

  struct tm *newtime;
  time_t aclock;
  time(&aclock); /* Get time in seconds */
  newtime = localtime(&aclock);
  // Time to update the tracker again
  DLLmprintf(0, "[%.24s] Updating the PXO game tracker with a new game!\n", asctime(newtime));

  if (GameType == GT_FREESPACE) {
    //		memcpy(FreeSpaceTrackerGameData,buffer,sizeof(freespace_net_game_data));
  } else if (GameType == GT_DESCENT3) {
    memcpy(D3TrackerGameData, buffer, sizeof(d3_net_game_data_short));
    SendGameTrackerPacker(&TrackerGameData);
    TrackerAckdUs = 0;
    LastTrackerUpdate = DLLtimer_GetTime();
    LastSentToTracker = DLLtimer_GetTime();

  } else if (GameType == GT_D3TNG) {
    memcpy(D3TrackerGameData, buffer, sizeof(d3_net_game_data_tiny));
    SendGameTrackerPacker(&TrackerGameData);
    TrackerAckdUs = 0;
    LastTrackerUpdate = DLLtimer_GetTime();
    LastSentToTracker = DLLtimer_GetTime();
  }
  TrackerGameIsRunning = 1;
  // LastTrackerUpdate = 0;
}
