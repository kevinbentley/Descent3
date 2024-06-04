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

* $Logfile: /DescentIII/Main/mtclient/mt_net.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:58:40 $
* $Author: kevinb $
*
* Mastertracker network code
*
* $Log: not supported by cvs2svn $
 *
 * 13    10/03/01 12:44a Kevin
 * Smaller version of pxo packets
 *
 * 12    9/02/99 3:16p Kevin
 * Macintosh byte ordering fixes
 *
 * 11    8/24/99 5:47p Kevin
 * Macintosh crap
 *
 * 10    4/19/99 8:36p Jeff
 * Compile under Linux
 *
 * 9     4/19/99 7:56p Kevin
 * ifdef'd out some win32 specific stuff
 *
 * 8     3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 7     12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 6     10/01/98 11:37a Kevin
 * UI fixes and stuff
 *
 * 5     9/16/98 8:06p Jason
 * got mastertracker working with the dedicated server
 *
 * 4     9/04/98 1:51p Kevin
 * implemented asyncronous gethostbyname
 *
 * 3     8/25/98 6:33p Kevin
 * PXO screens
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/21/98 11:21a Kevin
*
* $NoKeywords: $
*/

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#include <wsipx.h>
#endif

#include <memory.h>
#include "pstypes.h"
#include "networking.h"
#include "mtgametrack.h"
#include "mt_net.h"
#include "byteswap.h"

#define LOGIN_LEN 33
#define REAL_NAME_LEN 66
#define PASSWORD_LEN 17
#define EMAIL_LEN 100
#define TRACKER_ID_LEN 10
#define PILOT_NAME_LEN 20

#ifdef WIN32
#pragma pack(push, pxo)
#endif
#pragma pack(1) // Single byte alignment!
struct vmt_descent3_struct {
  char tracker_id[TRACKER_ID_LEN];
  char pilot_name[PILOT_NAME_LEN];
  int rank;

  int kills;
  int deaths;
  int suicides;
  int online_time;
  int games_played;
  uint32_t security;
  uint8_t virgin_pilot; // This pilot was just created if TRUE
  uint32_t lateral_thrust;
  uint32_t rotational_thrust;
  uint32_t sliding_pct; // Percentage of the time you were sliding
  uint32_t checksum;    // This value needs to be equal to whatever the checksum is once the packet is decoded
  uint32_t pad;         // just to provide room for out 4 byte encryption boundry only needed on the client side for now
};
#define DESCENT3_BLOCK_SIZE (sizeof(vmt_descent3_struct) - 4)
#ifdef WIN32
#pragma pack(pop, pxo)
#else
#pragma pack()
#endif

#include "mtpilottrack.h"

extern int MT_Initialized;
// Mastertracker sockets
static SOCKET TCP_game_tracker_socket;
static SOCKET TCP_pilot_tracker_socket;
static SOCKET TCP_chat_server_socket;

// Mastertracker addresses (we resolve them on init, and don't want to have to do it again)
static SOCKADDR_IN gtrackaddr;
static SOCKADDR_IN ptrackaddr;
static SOCKADDR_IN ctrackaddr;
static SOCKADDR_IN sockaddr;

#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)

#define NW_AGHBN_CANCEL 1
#define NW_AGHBN_LOOKUP 2
#define NW_AGHBN_READ 3

// extern void DLLDebug_ConsolePrintf  (int n, const char *format, ... );
typedef void (*Debug_ConsolePrintf_fp)(int n, const char *format, ...);

extern Debug_ConsolePrintf_fp DLLDebug_ConsolePrintf;

typedef int (*nw_Asyncgethostbyname_fp)(uint32_t *ip, int command, const char *hostname);
extern nw_Asyncgethostbyname_fp DLLnw_Asyncgethostbyname;

typedef int (*nw_SendWithID_fp)(uint8_t id, uint8_t *data, int len, network_address *who_to);
extern nw_SendWithID_fp DLLnw_SendWithID;
typedef int (*PollUI_fp)();
extern PollUI_fp DLLPollUI;
extern bool *DLLDedicated_server;

int SendGameTrackerPacker(void *packet) {
  game_packet_header *g_pack = (game_packet_header *)packet;

  network_address send_address;
  memset(&send_address, 0, sizeof(network_address));
  SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&gtrackaddr;
  memcpy(send_address.address, &inaddr->sin_addr, 4);
  send_address.port = htons(inaddr->sin_port);
  send_address.connection_type = NP_TCP;

  return DLLnw_SendWithID(PXO_NETID_GAME_TRACKER, (uint8_t *)g_pack, INTEL_INT(g_pack->len), &send_address);
}

void InitMTSockets() {
#ifdef WIN32
  WSADATA ws_data;
  WORD ver = MAKEWORD(1, 1);
#endif
  int rcode;
  uint32_t ip;
#ifdef WIN32
  int error = WSAStartup(ver, &ws_data);
  if (error != 0) {
    DLLmprintf(0, "There was an error initializing networking! Error=%d\n", error);
    return;
  } else
#endif
  {
    DLLmprintf(0, "Network initted successfully!\n");
  }

  {
    static HOSTENT lhe;
    memset(&sockaddr, 0, sizeof(SOCKADDR_IN));
    gtrackaddr.sin_family = AF_INET;
    gtrackaddr.sin_addr.s_addr = INADDR_ANY;
    gtrackaddr.sin_port = 0;

    gtrackaddr.sin_family = AF_INET;
    // This would be a good place to resolve the IP based on a domain name
    DLLmprintf(0, "Looking up hostname: %s.\n", GAMETRACKERNAME);

    DLLnw_Asyncgethostbyname(&ip, NW_AGHBN_LOOKUP, GAMETRACKERNAME);

    do {
      rcode = DLLnw_Asyncgethostbyname(&ip, NW_AGHBN_READ, GAMETRACKERNAME);

      if (!*DLLDedicated_server) {
        if (99 == DLLPollUI()) {
          return;
        }
      }
    } while (rcode == 0);

    if (rcode != 1) {
      DLLmprintf(0, "Unable to gethostbyname(\"%s\").\n", GAMETRACKERNAME);
      DLLmprintf(0, "WSAGetLastError() returned %d.\n", WSAGetLastError());
      DLLnw_Asyncgethostbyname(nullptr, NW_AGHBN_CANCEL, nullptr);
      return;
    }

    memcpy(&gtrackaddr.sin_addr.s_addr, &ip, 4); //&iaddr, 4);
    gtrackaddr.sin_port = htons(GAMEPORT);
    InitGameTrackerClient(GT_D3TNG);
  }
  {

    memset(&sockaddr, 0, sizeof(SOCKADDR_IN));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = 0; // htons(REGPORT);
    DLLmprintf(0, "Looking up hostname: %s.\n", PILOTTRACKERNAME);
    DLLnw_Asyncgethostbyname(&ip, NW_AGHBN_LOOKUP, PILOTTRACKERNAME);
    do {
      rcode = DLLnw_Asyncgethostbyname(&ip, NW_AGHBN_READ, PILOTTRACKERNAME);
      if (!*DLLDedicated_server) {
        if (99 == DLLPollUI()) {
          return;
        }
      }
    } while (rcode == 0);

    if (rcode != 1) {
      DLLmprintf(0, "Unable to gethostbyname(\"%s\").\n", PILOTTRACKERNAME);
      DLLmprintf(0, "WSAGetLastError() returned %d.\n", WSAGetLastError());
      DLLnw_Asyncgethostbyname(nullptr, NW_AGHBN_CANCEL, nullptr);
      return;
    }
    ptrackaddr.sin_family = AF_INET;
    memcpy(&ptrackaddr.sin_addr.s_addr, &ip, 4);
    ptrackaddr.sin_port = htons(REGPORT);
    InitPilotTrackerClient();
  }
  MT_Initialized = 1;
}

void CloseMTSockets() {
#ifdef WIN32
  if (WSACleanup()) {
    DLLmprintf(0, "Error closing wsock!\n");
  }
#endif
}

int SendPilotTrackerPacket(void *packet) {
  udp_packet_header *p_pack = (udp_packet_header *)packet;

  network_address send_address;
  memset(&send_address, 0, sizeof(network_address));
  SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&ptrackaddr;
  memcpy(send_address.address, &inaddr->sin_addr, 4);
  send_address.port = htons(inaddr->sin_port);
  send_address.connection_type = NP_TCP;
  return DLLnw_SendWithID(PXO_NETID_USER_TRACKER, (uint8_t *)p_pack, INTEL_SHORT(p_pack->len), &send_address);
}
