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

 * $Logfile: /DescentIII/Main/multi_client.cpp $
 * $Revision: 57 $
 * $Date: 9/20/01 1:10p $
 * $Author: Matt $
 *
 * Multiplayer client code
 *
 * $Log: /DescentIII/Main/multi_client.cpp $
 *
 * 57    9/20/01 1:10p Matt
 * Fix for client not taking fusion overchage damage in a peer-to-peer
 * game.
 *
 * 56    9/02/99 3:34p Jason
 * send secondary fire reliable in a C/S game
 *
 * 55    5/20/99 4:10p Jason
 * added heartbeat to multiplayer so clients wouldn't time out, also
 * various multiplayer fixes
 *
 * 54    5/17/99 6:26p Jason
 * added message for when the reliable buffer overruns
 *
 * 53    5/13/99 6:20p Kevin
 * fixed bug with client who's reliable connection was broken to the
 * server not disconnecting
 *
 * 52    5/10/99 10:22p Ardussi
 * changes to compile on Mac
 *
 * 51    5/05/99 5:41p Jason
 * fixed various multiplayer issues, including sequencing bugs and cheat
 * prevention
 *
 * 50    4/30/99 5:06p Kevin
 * misc dedicated server, networking and low memory enhancements
 *
 * 49    4/27/99 4:42a Jeff
 * pass guidebot name on MyInfo
 *
 * 48    4/14/99 2:51a Jeff
 * fixed some case mismatched #includes
 *
 * 47    2/16/99 3:47p Jason
 * added marker updates to multiplayer server stream
 *
 * 46    2/15/99 7:49p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 45    2/15/99 12:24p Jason
 * set default pps setting if permissable netgame
 *
 * 44    2/15/99 11:21a Jason
 * took out client side interpolation
 *
 * 43    2/12/99 5:58p Jason
 * more permissable server stuff
 *
 * 42    2/12/99 3:38p Jason
 * added client side interpolation
 *
 * 41    2/04/99 11:01a Jason
 * added anti cheating to multiplayer
 *
 * 40    12/21/98 10:22a Jason
 * added auto pps
 *
 * 39    12/08/98 4:52p Jeff
 * changed the pilot pics packing to use Ushort instead of int16_t just for
 * my conscience...removed some annoying mprintf's too
 *
 * 38    12/01/98 5:48p Jeff
 * added pilot picture id to netplayer struct
 *
 * 37    11/18/98 10:50a Jason
 * fixed peer to peer with new architecture
 *
 * 36    11/16/98 4:47p Jason
 * changes for multiplayer (weapons load sent and deleting destroyed
 * lightmapped objects)
 *
 * 35    10/28/98 11:51a Jason
 * fixed some multiplayer problems, plus redid coop a bit to make it
 * cleaner
 *
 * 34    10/27/98 10:19a Jason
 * changes for new arch
 *
 * 33    10/22/98 12:28p Kevin
 * Fixed pings in peer-peer
 *
 * 32    10/19/98 7:18p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 31    10/01/98 4:03p Jason
 * took out sequencing bug
 *
 * 30    10/01/98 11:36a Kevin
 * UI fixes and stuff
 *
 * 29    10/01/98 11:29a Jason
 * changes for world states in multiplayer games
 *
 * 28    9/11/98 12:26p Jason
 * got energy to shield and fusion damage working in multiplayer
 *
 * 27    9/04/98 3:45p Kevin
 * Added ping_time to Netplayers struct. It's updated in peer-peer and
 * client server
 *
 * 26    8/05/98 10:46a Kevin
 * sound & bmp exchange fixes
 *
 */

#include "multi.h"
#include "multi_client.h"
#include "game.h"
#include "player.h"
#include "ddio.h"
#include "pilot.h"
#include "Mission.h"
#include "stringtable.h"
#include "d3serial.h"
#include "ship.h"

#define WEAPONS_LOAD_UPDATE_INTERVAL 2.0

float Last_weapons_load_update_time = 0;

// Setup saved moves
saved_move SavedMoves[MAX_SAVED_MOVES];
int Current_saved_move = 0;

extern int Use_file_xfer;

// Tell the server about my info, such as name, ship type, etc
void MultiSendMyInfo() {
  int size;
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;

  mprintf(0, "Sending my info\n");
  char pshipmodel[PAGENAME_LEN];
  Current_pilot.get_ship(pshipmodel);

  int ship_index = FindShipName(pshipmodel);
  if (ship_index < 0)
    ship_index = 0;

  size = START_DATA(MP_MY_INFO, data, &count);

  // Do callsign name
  MultiAddByte(Player_num, data, &count);
  int len = strlen(Players[Player_num].callsign) + 1;
  MultiAddByte(len, data, &count);
  memcpy(&data[count], Players[Player_num].callsign, len);
  count += len;

  // Do ship name
  len = strlen(Ships[ship_index].name) + 1;
  MultiAddByte(len, data, &count);
  memcpy(&data[count], Ships[ship_index].name, len);
  count += len;

  if (Game_is_master_tracker_game) {
    MultiAddUint(MASTER_TRACKER_SIG, data, &count);
    strcpy(Players[Player_num].tracker_id, std::data(Tracker_id));
    len = strlen(Players[Player_num].tracker_id) + 1;
    MultiAddByte(len, data, &count);
    memcpy(&data[count], Players[Player_num].tracker_id, len);
    count += len;
  }
  int ser = 0;
  GetInternalSerializationNumber(&ser);
  MultiAddInt(ser, data, &count);

  // Send packets per second
  int pps = nw_ReccomendPPS();
  if ((Netgame.flags & NF_PERMISSABLE) && pps < 8)
    pps = 8; // If permissable game, can't be lower than 8

  MultiAddByte(pps, data, &count);

  // pilot picture id
  uint16_t ppic_id;
  Current_pilot.get_multiplayer_data(NULL, NULL, NULL, &ppic_id);
  MultiAddUshort(ppic_id, data, &count);

  // Copy the guidebot name out
  char guidebot_name[32];
  Current_pilot.get_guidebot_name(guidebot_name);
  len = strlen(guidebot_name) + 1;
  MultiAddByte(len, data, &count);
  memcpy(&data[count], guidebot_name, len);
  count += len;

  END_DATA(count, data, size);

  nw_SendReliable(NetPlayers[Player_num].reliable_socket, data, count);
}

// Ask the server to tell me about the players
void MultiSendRequestForPlayers() {
  int size;
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;

  mprintf(0, "Sending request for players\n");

  size = START_DATA(MP_REQUEST_PLAYERS, data, &count);
  MultiAddByte(Player_num, data, &count);
  END_DATA(count, data, size);

  nw_SendReliable(NetPlayers[Player_num].reliable_socket, data, count);
}

// Ask the server to tell me about the buildings
void MultiSendRequestForBuildings() {
  int size;
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;

  mprintf(0, "Sending request for buildings\n");

  size = START_DATA(MP_REQUEST_BUILDINGS, data, &count);
  MultiAddByte(Player_num, data, &count);
  END_DATA(count, data, size);

  nw_SendReliable(NetPlayers[Player_num].reliable_socket, data, count);
}

// Ask the server to tell me about the world
void MultiSendRequestForWorldStates() {
  int size;
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;

  mprintf(0, "Sending request for world states\n");

  size = START_DATA(MP_REQUEST_WORLD_STATES, data, &count);
  MultiAddByte(Player_num, data, &count);
  // Send the digest (checksum) for this level + our salt + the ships
  // Do level checksum
  for (int i = 0; i < 16; i++) {
    MultiAddByte(NetPlayers[Player_num].digest[i], data, &count);
  }

  END_DATA(count, data, size);

  nw_SendReliable(NetPlayers[Player_num].reliable_socket, data, count);
}

// Ask the server to tell me about the objects
void MultiSendRequestForObjects() {
  int size;
  uint8_t data[MAX_GAME_DATA_SIZE];
  int count = 0;

  mprintf(0, "Sending request for objects\n");

  size = START_DATA(MP_REQUEST_OBJECTS, data, &count);
  MultiAddByte(Player_num, data, &count);
  END_DATA(count, data, size);

  nw_SendReliable(NetPlayers[Player_num].reliable_socket, data, count);
}

#define SERVER_DISCONNECT_TIME 8.0

// Returns 1 if the server is gone!
int ServerTimedOut() {
  // Don't check for a non-connected player
  if (!(NetPlayers[Player_num].flags & NPF_CONNECTED))
    return 0;

  if (!nw_CheckReliableSocket(NetPlayers[Player_num].reliable_socket)) {
    mprintf(0, "Reliable connection to the server was broken. Disconnecting.\n");
    ShowProgressScreen(TXT_RELIABLE_OVERRUN);
    Sleep(1000);
    return 1;
  }
  if ((timer_GetTime() - Netgame.last_server_time) > SERVER_DISCONNECT_TIME)
    return 1;

  return 0;
}
#define NET_CLIENT_GAMETIME_REQ_TIMEOUT 10
#define NET_CLIENT_GAMETIME_REQ_RETRY 1
float First_gametime_req = 0;
float Last_gametime_req = 0;

// Do client stuff for this frame
void MultiDoClientFrame() {
  int i;
  Multi_last_sent_time[Player_num][0] += Frametime;

  // Get data from the server
  MultiProcessIncoming();

  if (Netgame.flags & NF_EXIT_NOW) {
    // DLL says we should bail!
    Netgame.flags &= ~NF_EXIT_NOW;
    MultiLeaveGame();
    SetFunctionMode(MENU_MODE);
    return;
  }

  if (NetPlayers[Player_num].sequence == NETSEQ_LEVEL_START) {
    MultiSendMyInfo();
    NetPlayers[Player_num].sequence = NETSEQ_NEED_GAMETIME;
    First_gametime_req = timer_GetTime();
  } else if (NetPlayers[Player_num].sequence == NETSEQ_NEED_GAMETIME) {
    // Ask for gametime
    GetServerGameTime();
    Last_gametime_req = timer_GetTime();
    NetPlayers[Player_num].sequence = NETSEQ_WAIT_GAMETIME;
  } else if (NetPlayers[Player_num].sequence == NETSEQ_WAIT_GAMETIME) {
    if (Got_new_game_time) {
      NetPlayers[Player_num].sequence = NETSEQ_REQUEST_PLAYERS;
    } else {
      // Wait for server response
      if ((timer_GetTime() - First_gametime_req) > NET_CLIENT_GAMETIME_REQ_TIMEOUT) {
        // Giving up, we waited too long.
        mprintf(0, "Server disconnected while waiting for gametime!\n");
        MultiLeaveGame();
        ShowProgressScreen(TXT_MLTDISCFRMSERV);
        Sleep(2000);
      } else if ((timer_GetTime() - Last_gametime_req) > NET_CLIENT_GAMETIME_REQ_RETRY) {
        NetPlayers[Player_num].sequence = NETSEQ_NEED_GAMETIME;
      }
    }

  } else if (NetPlayers[Player_num].sequence == NETSEQ_REQUEST_PLAYERS) {
    MultiSendRequestForPlayers();
    NetPlayers[Player_num].sequence = NETSEQ_PLAYERS;
  } else if (NetPlayers[Player_num].sequence == NETSEQ_REQUEST_BUILDINGS) {
    MultiSendRequestForBuildings();
    NetPlayers[Player_num].sequence = NETSEQ_BUILDINGS;
  } else if (NetPlayers[Player_num].sequence == NETSEQ_REQUEST_OBJECTS) {
    MultiSendRequestForObjects();
    NetPlayers[Player_num].sequence = NETSEQ_OBJECTS;
  } else if (NetPlayers[Player_num].sequence == NETSEQ_REQUEST_WORLD) {
    MultiSendRequestForWorldStates();
    NetPlayers[Player_num].sequence = NETSEQ_WORLD;
    NetPlayers[Player_num].custom_file_seq = 0;
  } else if (NetPlayers[Player_num].sequence == NETSEQ_PLAYING) {
    if (NetPlayers[Player_num].custom_file_seq == 0) {
      // Tell the server about our custom data (once only)
      if (NetPlayers[Player_num].ship_logo[0])
        PlayerSetCustomTexture(Player_num, NetPlayers[Player_num].ship_logo);
      NetPlayers[Player_num].custom_file_seq = 0xff;

      // Make sure we as the client actually want to send our custom data
      if (Use_file_xfer)
        MultiSendClientCustomData(Player_num);
    }

    bool client_file_xfering = false;
    for (i = 0; i < MAX_NET_PLAYERS; i++) {
      if (NetPlayers[i].file_xfer_flags != NETFILE_NONE)
        client_file_xfering = true;
    }
    // See if we have room for a transfer
    if (!client_file_xfering) {
      // Check to see if we need to request any files from this bozo
      for (i = 0; i < MAX_NET_PLAYERS; i++) {
        if (i == Player_num)
          continue;
        if ((NetPlayers[i].custom_file_seq != NETFILE_ID_NOFILE) &&
            (NetPlayers[i].custom_file_seq != NETFILE_ID_DONE)) {
          // See if we are already sending or receiving a file from this player
          if (NetPlayers[i].file_xfer_flags == NETFILE_NONE) {
            // Check to see if we have this file in our cache
            // Time to ask for the file specified in the sequence
            MultiAskForFile(NetPlayers[i].custom_file_seq, i, 0);
            break;
          }
        }
      }
    }

    Last_weapons_load_update_time += Frametime;
    if (Last_weapons_load_update_time > WEAPONS_LOAD_UPDATE_INTERVAL) {
      Last_weapons_load_update_time = 0;
      MultiSendWeaponsLoad();
    }

    // Figure out if we need to send our movement
    bool send_it = false;

    if (Player_fire_packet[Player_num].fired_on_this_frame != PFP_NO_FIRED)
      send_it = true;

    if (Multi_last_sent_time[Player_num][0] > (1.0 / (float)NetPlayers[Player_num].pps))
      send_it = true;

    if (send_it) {
      // Request damage if need be
      if (Multi_requested_damage_amount != 0) {
        if ((Netgame.local_role == LR_CLIENT) && (Netgame.flags & NF_PEER_PEER)) {
          MultiSendRequestPeerDamage(&Objects[Players[Player_num].objnum], -1, Multi_requested_damage_type,
                                     Multi_requested_damage_amount);
        } else {
          MultiSendRequestDamage(Multi_requested_damage_type, Multi_requested_damage_amount);
        }
        Multi_requested_damage_amount = 0;
      }

      // Request shields if need be
      for (i = 0; i < MAX_SHIELD_REQUEST_TYPES; i++) {
        if (Multi_additional_shields[i] != 0) {
          MultiSendRequestShields(i, Multi_additional_shields[i]);
          Multi_additional_shields[i] = 0;
        }
      }

      uint8_t data[MAX_GAME_DATA_SIZE], count = 0, add_count = 0;

      count = MultiStuffPosition(Player_num, data);

      // Send firing if needed
      if (Player_fire_packet[Player_num].fired_on_this_frame == PFP_FIRED)
        add_count = MultiStuffPlayerFire(Player_num, &data[count]);

      count += add_count;

      // Add in guided stuff
      if (Players[Player_num].guided_obj != NULL) {
        add_count = MultiStuffGuidedInfo(Player_num, &data[count]);
        count += add_count;
      }

      ASSERT(count < MAX_GAME_DATA_SIZE);

      if (Netgame.flags & NF_PEER_PEER) {
        for (i = 0; i < MAX_NET_PLAYERS; i++) {
          if (!(NetPlayers[i].flags & NPF_CONNECTED))
            continue;
          if (i == Player_num)
            continue;

          // Now get the ping time if needed
          if ((timer_GetTime() - NetPlayers[i].last_ping_time) > MULTI_PING_INTERVAL)
            MultiSendPing(i);

          nw_Send(&NetPlayers[i].addr, data, count, 0);
        }
      } else
        nw_Send(&Netgame.server_address, data, count, 0);

      // TODO: SEND RELIABLE WEAPON FIRE
      if (Player_fire_packet[Player_num].fired_on_this_frame == PFP_FIRED_RELIABLE) {
        // mprintf(0,"I NEED TO SEND RELIABLE FIRE\n");
        count = MultiStuffPlayerFire(Player_num, data);
        nw_SendReliable(NetPlayers[Player_num].reliable_socket, data, count, true);
      }

      // Clear our data
      Player_fire_packet[Player_num].fired_on_this_frame = PFP_NO_FIRED;
      Multi_last_sent_time[Player_num][0] = 0;
      Players[Player_num].flags &= ~PLAYER_FLAGS_SEND_MOVEMENT;
    }

    if (ServerTimedOut()) {
      mprintf(0, "Server disconnected!\n");
      MultiLeaveGame();
      ShowProgressScreen(TXT_MLTDISCFRMSERV);
      Sleep(2000);
    }
  }
}

// Initializes some fields for a network client to play
// Client only
void MultiStartClient(char *scriptname) {
  int i;

  for (i = 0; i < MAX_NET_PLAYERS; i++) {
    memset(&NetPlayers[i], 0, sizeof(netplayer));
  }

  for (i = 0; i < MAX_SAVED_MOVES; i++)
    SavedMoves[i].timestamp = 0;

  Current_saved_move = 0;

  // Temporary name fix
  Current_pilot.get_name(Players[Player_num].callsign);

  Multi_send_size[Player_num] = 0;
  Multi_last_sent_time[Player_num][0] = 0;
  Last_weapons_load_update_time = 0;

  Netgame.local_role = LR_CLIENT;
  Game_mode = GM_NETWORK;
  SetGamemodeScript(scriptname);
}
