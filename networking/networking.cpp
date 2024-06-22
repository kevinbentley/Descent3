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

 * $Logfile: /DescentIII/Main/networking/networking.cpp $
 * $Revision: 1.7 $
 * $Date: 2004/12/05 04:38:23 $
 * $Author: ryan $
 *
 *
 *
 * $Log: networking.cpp,v $
 * Revision 1.7  2004/12/05 04:38:23  ryan
 * Disable IPX support.
 *
 * Revision 1.6  2004/12/05 04:00:20  ryan
 * MacOS X patches.
 *
 * Revision 1.5  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.4  2001/01/13 21:48:46  icculus
 * patched to (re)compile on win32.
 *
 * Revision 1.3  2000/06/29 06:41:24  icculus
 * mad commits.
 *
 * Revision 1.2  2000/06/24 01:15:15  icculus
 * patched to compile.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:41  icculus
 * initial checkin
 *
 *
 * 116   1/30/00 3:33p Jason
 * Expanded network receive buffer
 *
 * 115   10/21/99 3:01p Kevin
 * Macintosh willdial fixes
 *
 * 113   9/17/99 2:44p Kevin
 * preferred net buffer size == 16k
 *
 * 112   8/31/99 5:30p Jason
 * network statistics code
 *
 * 111   8/24/99 2:10p Kevin
 * Some debugging & Macintosh fixes
 *
 * 110   8/23/99 5:15p Kevin
 * Macintosh Byte ordering fixes
 *
 * 109   8/21/99 3:14a Jeff
 * real async lookup in Linux
 *
 * 108   8/10/99 11:00a Kevin
 * decreased receive buffer size
 *
 * 107   8/02/99 10:24p Kevin
 * fixed some mac stuff
 *
 * 106   7/29/99 10:33a Kevin
 * More Mac
 *
 * 105   7/26/99 12:05p Kevin
 * Macintosh stuff
 *
 * 104   5/23/99 5:55p Jeff
 * mprintf for easy debugging
 *
 * 103   5/19/99 5:21p Kevin
 * changed return value of nw_GetHostAddressFromNumbers()
 *
 * 102   5/19/99 1:12p Kevin
 * fixed an mprintf and added a saftey check
 *
 * 101   5/06/99 3:27a Kevin
 * directplay fixes
 *
 * 100   4/30/99 5:07p Kevin
 * misc dedicated server, networking and low memory enhancements
 *
 * 99    4/25/99 3:19p Kevin
 * removed really bad call to Error() when the reliable buffer overflows.
 * It is possible for this to happen when one client disconnects and
 * shouldn't cause the server to shutdown.
 *
 * 98    4/22/99 6:32p Kevin
 * Hopefully fixed linux gehostbyname problem
 *
 * 97    4/19/99 7:57p Jeff
 * pack structures for Linux version
 *
 * 96    4/19/99 4:02a Jeff
 * fixed select calls for Linux
 *
 * 95    4/17/99 5:56a Jeff
 * ported to Linux
 *
 * 94    4/15/99 2:58a Jeff
 * added some defines and includes needed for linux ipx
 *
 * 93    4/14/99 1:38a Jeff
 * fixed case mismatched #includes
 *
 * 92    4/12/99 3:16p Kevin
 * Added a bunch of stuff for the linux version
 *
 * 91    3/08/99 3:59p Kevin
 * Idle processing of network packets fixed
 *
 * 90    2/24/99 12:48p Kevin
 * Added urgent flag to nw_SendReliable. It causes the packet to go out
 * that frame.
 *
 * 89    2/23/99 3:09p Jason
 * changed queue time to tenth of a second, as a test.  4 tenths of a
 * second might be too long, especially on a LAN.
 *
 * 88    2/08/99 11:12p Kevin
 * Fixed ip selection & RAS code
 *
 * 87    2/08/99 4:08p Kevin
 * Fixed a stupid bug I introduced last week
 *
 * 86    2/05/99 7:24p Kevin
 * Added NAGLE type packet buffering to reliable networking code
 *
 * 85    1/26/99 9:45p Jeff
 * moved tcplog from networking to mono lib
 *
 * 84    1/08/99 4:51p Jeff
 * don't put the null char at the end of the buffer when sending the
 * TCPPrintf
 *
 * 83    1/08/99 2:58p Kevin
 * Added TCP mprintf support so you can log to a remote machine.
 *
 * 82    1/07/99 11:51a Kevin
 * Added support for joining servers on alternate ports and hosting behind
 * a proxy/firewall
 *
 * 81    1/06/99 3:08p Jason
 * changed recommended pps
 *
 * 80    1/04/99 12:22p Jeff
 * commented out assert no longer needed (nw_GetHostAddressFromNumbers)
 *
 * 79    12/28/98 10:02a Kevin
 * removed mprintfs
 *
 * 78    12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 77    12/14/98 3:07p Kevin
 * Added +ip to specify IP to bind to (gamespy command line arg)
 *
 * 76    12/03/98 9:29a Kevin
 * Added better ip selection code
 *
 * 75    11/06/98 4:46p Jason
 * added runtime error for being unable to send reliable packet
 *
 * 74    10/29/98 5:08p Jason
 * added an Int3 for when the unthinkable actually happens
 *
 * 73    10/19/98 7:51p Kevin
 * performance testing
 *
 * 72    10/16/98 11:55a Kevin
 * Made dlls loadable in a hog
 *
 * 71    10/14/98 7:20p Kevin
 * More dsp changes...
 *
 * 70    10/12/98 8:39p Kevin
 * removed mprintf's and fixed some smallish bugs
 *
 * 69    10/12/98 4:10p Kevin
 * Made sockets reuasable so if the game locks you don't have to reboot
 *
 * 68    10/08/98 12:30p Nate
 * For Kevin. Fixed stupidity bug I just introduced
 *
 * 67    10/08/98 9:59a Kevin
 * made change to async gethostbyname
 *
 * 66    10/06/98 6:07p Jason
 * added protective layer for reliable packets
 *
 * 65    9/30/98 10:36a Kevin
 * Added command line launching of URLs and command line directory
 * specification
 *
 * 64    9/28/98 4:22p Kevin
 * Redesigned game list menus
 *
 * 63    9/28/98 11:02a Kevin
 * added Networking defer, and fixed some UI issues
 *
 * 62    9/28/98 9:53a Kevin
 * Fixing misc UI problems, and fixed some bugs that VC 6 found
 *
 * 61    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 60    9/04/98 1:51p Kevin
 * implemented asyncronous gethostbyname
 *
 * 59    9/03/98 11:12a Kevin
 * fixed bug related to the size of reliable packet header...
 *
 * 58    8/31/98 10:15a Kevin
 * Misc. multi-UI fixes
 *
 * 57    8/24/98 5:04p Kevin
 * Made msn files have the option to not be playable in multiplayer
 *
 * 56    8/24/98 10:55a Kevin
 * new directplay stuff
 *
 * 55    8/19/98 11:50a Kevin
 * Got DirectPlay IPX working, and localized connection DLLs
 *
 * 54    8/17/98 11:00a Kevin
 * Moved DLLs into subdirectories
 *
 * 53    8/14/98 4:54p Kevin
 * More directplay stuff
 *
 * 52    8/13/98 6:32p Kevin
 * Initial implementation of directplay API
 *
 * 51    8/11/98 11:18a Kevin
 * Cleaned up unused code and unused function
 *
 * 50    8/11/98 10:46a Kevin
 * removed TCPIP only code from reliable code
 *
 * 49    8/11/98 10:28a Kevin
 * Added a bunch of return code checking to help throttle bandwidth
 *
 * 48    8/10/98 4:32p Kevin
 * added RAS code to correctly Identify IP address
 *
 * 47    8/10/98 12:56p Kevin
 * Removed blocking writes
 *
 * 46    8/07/98 7:02p Kevin
 *
 * 45    8/07/98 7:02p Kevin
 * dumb bug fix for below
 *
 * 44    8/07/98 6:44p Kevin
 * made unreliable sockets non blocking
 *
 * 43    8/05/98 2:25p Kevin
 * improved network address reporting
 *
 * 42    8/05/98 12:07p Kevin
 * minor fixes to reliable
 *
 * 41    7/29/98 6:11p Kevin
 * took out sequence hack
 *
 * 40    7/29/98 5:31p Kevin
 * added rcs header
 *
 */

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#include <process.h>
#include <wsipx.h>
#include <ras.h>
typedef int socklen_t;
#endif
#include <stdlib.h>
#include <string.h>
#ifdef __LINUX__
#if !MACOSX
#include <netinet/in.h>
#endif
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE true
#define FALSE false
#define LPSTR char *
#endif

#ifdef WIN32
#include "dplay.h"
#include "dplobby.h"
#endif

#include "descent.h"
// #include "../manage/shippage.h"
#include "appdatabase.h"

#include "pstypes.h"
#include "pserror.h"
#include "mono.h"
#include "networking.h"
#include "ddio.h"
#include "mem.h"
#include "game.h"
#include "args.h"
#include "byteswap.h"

#ifdef WIN32
#include "directplay.h"
#endif

#include "pstring.h"

#ifndef WIN32
bool Use_DirectPlay = false;
#endif

#include "module.h" //for some nice defines to use below

#define MAX_CONNECT_TRIES 50
#define MAX_RECEIVE_BUFSIZE 32768
//(1<<16)			// 16 K, eh?

int iMaxReceiveBufsize = MAX_RECEIVE_BUFSIZE;

#ifdef WIN32
DWORD(DLLFUNCCALL *pRasEnumConnections)(LPRASCONN lprasconn, LPDWORD lpcb, LPDWORD lpcConnections) = NULL;
DWORD(DLLFUNCCALL *pRasGetConnectStatus)(HRASCONN hrasconn, LPRASCONNSTATUS lprasconnstatus) = NULL;
DWORD(DLLFUNCCALL *pRasGetProjectionInfo)
(HRASCONN hrasconn, RASPROJECTION rasprojection, LPVOID lpprojection, LPDWORD lpcb) = NULL;
#endif

int Dialup_connection = 0;

int nw_ServerSocket = -1;
int nw_ClientSocket = -1;

network_protocol NetworkProtocol = NP_NONE;

int Sockets_initted = 0;
int Network_initted = 0;

uint32_t Net_fixed_ip = INADDR_NONE;
// sockets for IPX and TCP

SOCKET TCP_socket;
SOCKET TCP_reliable_socket;
SOCKET TCP_listen_socket;

// the sockets that the game will use when selecting network type
static SOCKET *Unreliable_socket;
static SOCKET *Reliable_socket;
static SOCKET *Listen_socket;

// our current running statistics
static tNetworkStatus NetStatistics;

BOOL TCP_active = FALSE;
BOOL IPX_active = FALSE;
BOOL DP_active = FALSE; // Direct Play active
// BOOL TCP_MT_active = FALSE;

// This structure contains the local computer info
network_address My_addr;

struct network_checksum_packet {
  int sequence_number;
  uint16_t flags;
  uint16_t checksum;
  uint8_t data[MAX_PACKET_SIZE];
};

// definition for a non-checksum packet
struct network_naked_packet {
  int sequence_number;
  uint16_t flags;
  uint8_t data[MAX_PACKET_SIZE];
};

// structure definition for our packet buffers
struct network_packet_buffer {
  int sequence_number;
  int len;
  network_address from_addr;
  uint8_t data[MAX_PACKET_SIZE];
};

#define MAX_PACKET_BUFFERS 96

static network_packet_buffer Packet_buffers[MAX_PACKET_BUFFERS]; // buffer to hold packets sent to us
static int16_t Packet_free_list[MAX_PACKET_BUFFERS];               // contains id's of free packet buffers
static int Num_packet_buffers;
static int Largest_packet_index = 0;

static int Uncompressed_outgoing_data_len = 0;
static int Compressed_outgoing_data_len = 0;

int Next_packet_id;
int Last_packet_id;

static CFILE *NetDebugFile = NULL;

// An array of callbacks
static NetworkReceiveCallback Netcallbacks[16];

#define R_NET_SEQUENCE_NONE 0
#define R_NET_SEQUENCE_CONNECTING 1
#define R_NET_SEQUENCE_CONNECTED 2
#define R_NET_SEQUENCE_FAILED 3

#define R_NET_PACKET_QUEUE_TIME .1f

static int Net_connect_socket_id = INVALID_SOCKET;
static int Net_connect_sequence = R_NET_SEQUENCE_NONE;

// ------------------------------------------------------------------------------------------------------
// PACKET BUFFERING FUNCTIONS
//

// a sequence number of -1 will indicate that this packet is not valid
static network_packet_buffer Psnet_buffers[MAX_PACKET_BUFFERS];
static int Psnet_seq_number = 0;
static int Psnet_lowest_id = 0;
static int Psnet_highest_id = 0;

// Reliable UDP stuff
//*******************************
#ifdef WIN32
#pragma pack(push, r_udp)
#endif
#pragma pack(1)
struct reliable_header {
  uint8_t type;                // packet type
  uint8_t compressed;          //
  uint16_t seq;                // sequence packet 0-65535 used for ACKing also
  uint16_t data_len;           // length of data
  float send_time;           // Time the packet was sent, if an ACK the time the packet being ACK'd was sent.
  uint8_t data[NETBUFFERSIZE]; // Packet data
};

#define RELIABLE_PACKET_HEADER_ONLY_SIZE (sizeof(reliable_header) - NETBUFFERSIZE)
#define MAX_PING_HISTORY 10

struct reliable_net_sendbuffer {
  uint8_t buffer[NETBUFFERSIZE];

};

struct reliable_net_rcvbuffer {
  uint8_t buffer[NETBUFFERSIZE];
};

static SOCKET Reliable_UDP_socket = INVALID_SOCKET;

static float first_sent_iamhere = 0;
static float last_sent_iamhere = 0;

static uint32_t serverconn = 0xFFFFFFFF;

#ifdef WIN32
#pragma pack(pop, r_udp)
#else
#pragma pack()
#endif

struct reliable_socket {

  float timesent[MAXNETBUFFERS];
  int16_t send_len[MAXNETBUFFERS];
  int16_t recv_len[MAXNETBUFFERS];
  float last_packet_received; // For a given connection, this is the last packet we received
  float last_packet_sent;
  float pings[MAX_PING_HISTORY];
  uint32_t num_ping_samples;
  float mean_ping;
  float last_sent;           // The last time we sent a packet (used for NAGLE emulation)
  int waiting_packet_number; // Which packet has data in it that is waiting for the interval to send

  uint16_t status;                           // Status of this connection
  uint16_t oursequence;              // This is the next sequence number the application is expecting
  uint16_t theirsequence;            // This is the next sequence number the peer is expecting
  uint16_t rsequence[MAXNETBUFFERS]; // This is the sequence number of the given packet

  uint8_t ping_pos;

  network_address net_addr;         // A D3 network address structure
  network_protocol connection_type; // IPX, IP, modem, etc.
  reliable_net_rcvbuffer *rbuffers[MAXNETBUFFERS];
  SOCKADDR addr;                                    // SOCKADDR of our peer
  reliable_net_sendbuffer *sbuffers[MAXNETBUFFERS]; // This is an array of pointers for quick sorting
  uint16_t ssequence[MAXNETBUFFERS];          // This is the sequence number of the given packet
  uint8_t send_urgent;
};

static reliable_socket reliable_sockets[MAXRELIABLESOCKETS];
//*******************************
#ifdef __LINUX__
#include <fcntl.h>
#endif

int make_nonblocking(SOCKET sock)
{
#ifdef WIN32
  unsigned long arg = 1;
  return ioctlsocket(sock, FIONBIO, &arg);
#else // WIN32
  return fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);
#endif
}

void CloseNetworking() {
  if (Sockets_initted != 1)
    return;

  if (NetDebugFile) {
    cfprintf(NetDebugFile, "NetDebug.log closed at %f seconds.\n", timer_GetTime());
    cfclose(NetDebugFile);
    NetDebugFile = NULL;
  }

  mprintf(0, "Shutting down networking...\n");
#ifdef WIN32
  WSACancelBlockingCall();

  dp_ShutdownDirectPlay();
#endif

  if (TCP_socket != INVALID_SOCKET) {
    shutdown(TCP_socket, 1);
#ifdef WIN32
    closesocket(TCP_socket);
#else
    close(TCP_socket);
#endif
  }
#ifdef WIN32
  if (WSACleanup()) {
    mprintf(0, "Error closing wsock!\n");
  }
#endif

  Network_initted = 0;
  Sockets_initted = 0;

  NetworkProtocol = NP_NONE;
}

// Inits the sockets layer to activity
void nw_InitNetworking(int iReadBufSizeOverride) {
  if (iReadBufSizeOverride == -1) {
    iMaxReceiveBufsize = MAX_RECEIVE_BUFSIZE;
  } else {
    iMaxReceiveBufsize = iReadBufSizeOverride;
  }

  // reset our stats so we are ready to use them
  nw_GetNetworkStats(NULL);

#ifdef WIN32
  WSADATA ws_data;
  WORD ver = MAKEWORD(1, 1);
#endif

  static char exewithpath[_MAX_PATH * 2];
  static char exefile[_MAX_PATH * 2];
  static char ourargs[_MAX_PATH * 2];
  static char exedir[_MAX_PATH * 2];
  static char exeext[_MAX_PATH];
  static char *fixdir;
  static char szconntype[100];
  int parmlen;
  int len = 99;
  Database()->read("NetworkConnection", szconntype, &len);
  if (stricmp(szconntype, "DIALUP") == 0) {
    Dialup_connection = 1;
  } else {
    Dialup_connection = 0;
  }
  int iparg;

  if (FindArg("-netdebug")) {
    NetDebugFile = (CFILE *)cfopen("netdebug.log", "wa");
    ASSERT(NetDebugFile);
    cfprintf(NetDebugFile, "NetDebug.log opened at %f seconds\n", timer_GetTime());
  }

  iparg = FindArg("-useip");
  if (!iparg) {
    iparg = FindArg("+ip");
  }
  if (iparg) {
    Net_fixed_ip = inet_addr(GameArgs[iparg + 1]);
    if (Net_fixed_ip == INADDR_NONE) {
      Net_fixed_ip = INADDR_NONE;
    }
  }
#ifdef WIN32
  if (!dp_DidLobbyLaunchGame()) {
    // Tell direct play about this game
    char *p = GetCommandLine();
    mprintf(0, "Command line: %s\n", p);
    parmlen = strlen(p);

    int a;
    for (a = 0; a < parmlen; ++a) {
      if (p[a] == ' ') {
        break;
      }
    }
    if (a < parmlen) {
      strcpy(ourargs, p + a + 1);
    } else {
      strcpy(ourargs, "");
    }
    strncpy(exewithpath, p, a);
    exewithpath[a] = NULL;
    ddio_SplitPath(exewithpath, exedir, exefile, exeext);
    if (exedir[0] == '\"') {
      fixdir = exedir + 1;
    } else {
      fixdir = exedir;
    }
    if (exeext[strlen(exeext) - 1] == '\"') {
      exeext[strlen(exeext) - 1] = NULL;
    }
    strcat(exefile, exeext);
    // dp_RegisterLobbyApplication("Descent 3",exefile,fixdir,ourargs,Base_directory,"Descent 3");
  }
#endif

#ifdef WIN32
  int error = WSAStartup(ver, &ws_data);
#else
  int error = 0;
#endif
  if (error != 0) {
    mprintf(0, "There was an error initializing networking! Error=%d\n", error);
    return;
  } else {
    mprintf(0, "Network initted successfully!\n");
    Network_initted = 1;
    atexit(CloseNetworking);
  }
}

// Sets the size of buffers
void nw_SetSocketOptions(SOCKET sock) {
  int broadcast;
  int ret, cursize, bufsize, trysize;
  socklen_t cursizesize;

  // Set the mode of the socket to allow broadcasting.  We need to be able to broadcast
  // when a game is searched for in IPX mode.
  broadcast = 1;
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (LPSTR)&broadcast, sizeof(broadcast));
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&broadcast, sizeof(broadcast));

  int error = make_nonblocking(sock);
  if (error == SOCKET_ERROR) {
    mprintf(0, "Unable to make socket non-blocking -- %d", WSAGetLastError());
  }

  // try and increase the size of my receive buffer
  bufsize = iMaxReceiveBufsize;

  // set the current size of the receive buffer
  cursizesize = sizeof(int);
  getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (LPSTR)&cursize, &cursizesize);
  for (trysize = bufsize; trysize >= cursize; trysize >>= 1) {
    ret = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (LPSTR)&trysize, sizeof(trysize));
    if (ret == SOCKET_ERROR) {
      int wserr;

      wserr = WSAGetLastError();
      if ((wserr == WSAENOPROTOOPT) || (wserr == WSAEINVAL))
        break;

    } else
      break;
  }
  getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (LPSTR)&cursize, &cursizesize);
  mprintf(0, "Receive buffer set to %d\n", cursize);
  /*
  // set the current size of the send buffer
  bufsize = MAX_RECEIVE_BUFSIZE/4;
  cursizesize = sizeof(int);
  getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (LPSTR)&cursize, &cursizesize);
  for ( trysize = bufsize; trysize >= cursize; trysize >>= 1 )
  {
          ret = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (LPSTR)&trysize, sizeof(trysize));
          if ( ret == SOCKET_ERROR )
          {
                  int wserr;

                  wserr = WSAGetLastError();
                  if ( (wserr == WSAENOPROTOOPT) || (wserr == WSAEINVAL) )
                          break;
          }
          else
                  break;
  }
  getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (LPSTR)&cursize, &cursizesize);
  mprintf(0, "Send buffer set to %d\n", cursize);
  */
}

uint16_t nw_ListenPort = 0;

// Inits the sockets that the application will be using
void nw_InitSockets(uint16_t port) {

  nw_ListenPort = port;
  // UDP/TCP socket structure
  SOCKADDR_IN sock_addr;

  // Now do tcp!
  TCP_active = 0;
  TCP_socket = INVALID_SOCKET;
  // TCP_reliable_socket = INVALID_SOCKET;
  TCP_listen_socket = INVALID_SOCKET;

  // Initialize the UDP socket
  TCP_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // Initialize all reliable sockets, IPX and TCP
  nw_InitReliableSocket();

  if (TCP_socket != INVALID_SOCKET) {
    // bind the socket
    memset(&sock_addr, 0, sizeof(SOCKADDR_IN));
    sock_addr.sin_family = AF_INET;

    uint32_t my_ip;

    my_ip = nw_GetThisIP();

    memcpy(&sock_addr.sin_addr.s_addr, &my_ip, sizeof(uint32_t));

    sock_addr.sin_port = htons(port);
    if (bind(TCP_socket, (SOCKADDR *)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR) {
      mprintf(0, "Couldn't bind TCP socket (%d)! Invalidating TCP\n", WSAGetLastError());
      goto tcp_done;
    }

    nw_SetSocketOptions(TCP_socket);
    TCP_active = 1;
  } else {
    mprintf(0, "Cannot create TCP socket (%d)!\n", WSAGetLastError());
  }

tcp_done:
  int ret;
  uint32_t isocktrue = 1;

  setsockopt(TCP_socket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&isocktrue, sizeof(isocktrue));
  ret = setsockopt(TCP_socket, SOL_SOCKET, SO_BROADCAST, (LPSTR)&isocktrue, sizeof(uint32_t));
  if (ret == SOCKET_ERROR) {
    int wserr;
    wserr = WSAGetLastError();
    if ((wserr == WSAENOPROTOOPT) || (wserr == WSAEINVAL)) {
      mprintf(0, "Unable to make socket broadcastable!");

      Int3(); // Get Kevin
    }
  }

  Sockets_initted = 1;

  if (TCP_active)
    mprintf(0, "TCP Initialized\n");

  nw_psnet_buffer_init();
  nw_RegisterCallback((NetworkReceiveCallback)nw_HandleUnreliableData, NWT_UNRELIABLE);
}

// Copies my address into the passed argument
void nw_GetMyAddress(network_address *addr) {
  socklen_t len;
  SOCKADDR_IN in_addr;

  memset(&My_addr, 0, sizeof(network_address));
  if (TCP_active) {
    // assign the TCP_* sockets to the socket values used elsewhere
    Unreliable_socket = &TCP_socket;
    Reliable_socket = &TCP_reliable_socket;
    Listen_socket = &TCP_listen_socket;

    // get the socket name for the TCP_socket, and put it into My_addr
    len = sizeof(SOCKADDR_IN);
    if (getsockname(*Unreliable_socket, (SOCKADDR *)&in_addr, &len) == SOCKET_ERROR) {
      mprintf(0, "Unable to get sock name for TCP unreliable socket (%s)\n", WSAGetLastError());
      return;
    }

    memcpy(My_addr.address, &in_addr.sin_addr, 4);

    // My_addr.port = in_addr.sin_port;
    My_addr.port = ntohs(in_addr.sin_port);
  }

  *addr = My_addr;
}

// Returns internet address format from string address format...ie "204.243.217.14"
// turns into 1414829242
uint32_t nw_GetHostAddressFromNumbers(char *str) {
  // ASSERT (NetworkProtocol==NP_TCP);

  return inet_addr(str);
}

// Fills in the string with the string address from the internet address
void nw_GetNumbersFromHostAddress(network_address *address, char *str) {
  // ASSERT(NetworkProtocol==NP_TCP);
  ASSERT(str);
  struct in_addr addr;

  if (address->connection_type == NP_TCP) {
    memcpy(&addr, address->address, sizeof(struct in_addr));
    sprintf(str, "IP: %s:%d", inet_ntoa(addr), address->port);
  }

#ifdef WIN32
  else if (Use_DirectPlay && (address->connection_type == NP_DIRECTPLAY)) {
    DPID id;
    memcpy(&id, address->address, sizeof(DPID));
    sprintf(str, "DirectPlay: 0x%x", id);
  }
#endif
}

#define CLOSE_TIMEOUT_TIME 3 // 3 seconds

// returns the ip address of this computer
uint32_t nw_GetThisIP() {
  SOCKADDR_IN local_address;
  int address_size = sizeof(SOCKADDR);

  if (Net_fixed_ip != INADDR_NONE) {
    return Net_fixed_ip;
  }
  // Init local address to zero
  local_address.sin_addr.s_addr = INADDR_ANY;
  if (Dialup_connection) {
#ifdef WIN32
    local_address.sin_addr.s_addr = psnet_ras_status();
#else
    local_address.sin_addr.s_addr = INADDR_ANY;
#endif
  }
  if ((!Dialup_connection) || (!local_address.sin_addr.s_addr)) {
    // Removed the fancy way, it worked worse than the easy way (some adsl/cable people had problems.
    /*
    // Get the local host name
    ret = gethostname(local, 255 );
    if (ret != SOCKET_ERROR )
    {
            // Resolve host name for local address
            hostent = gethostbyname((LPSTR)local);
            if ( hostent )
                    local_address.sin_addr.s_addr = *((u_long FAR *)(hostent->h_addr));
    }
    */
    local_address.sin_addr.s_addr = INADDR_ANY;
  }
  return local_address.sin_addr.s_addr;
}

// Calculates a unique uint16_t checksum for a stream of data
uint16_t nw_CalculateChecksum(void *vptr, int len) {
  uint8_t *ptr = (uint8_t *)vptr;
  uint32_t sum1, sum2;

  sum1 = sum2 = 0;

  while (len--) {
    sum1 += *ptr++;
    if (sum1 >= 255)
      sum1 -= 255;
    sum2 += sum1;
  }
  sum2 %= 255;

  return (uint16_t)((sum1 << 8) + sum2);
}

// Sends data on an unreliable socket
int nw_Send(network_address *who_to, void *data, int len, int flags) {
  if (len == 0) {
    mprintf(0, "Attempting to send 0 byte network packet in nw_Send()\n");
    Int3();
  }
  if (NetDebugFile) {
    uint8_t *ptr = (uint8_t *)data;
    cfprintf(NetDebugFile, "nw_Send packet of type %d at %f seconds.\n", ptr[0], timer_GetTime());
  }
  return nw_SendWithID(NWT_UNRELIABLE, (uint8_t *)data, len, who_to);
}

// MTS: only used in this file?
void nw_HandleUnreliableData(uint8_t *data, int len, network_address *from_addr) {
  nw_psnet_buffer_packet((uint8_t *)data, len, from_addr);
}

// MTS: unused?
// routine to "free" a packet buffer
void nw_FreePacket(int id) {
  Packet_buffers[id].sequence_number = -1;
  Packet_free_list[--Num_packet_buffers] = (int16_t)id;
  if (Largest_packet_index == id)
    while ((--Largest_packet_index > 0) && (Packet_buffers[Largest_packet_index].sequence_number == -1))
      ;
}

// nw_Recieve will call the above function to read data out of the socket.  It will then determine
// which of the buffers we should use and pass to the routine which called us
int nw_Receive(void *data, network_address *from_addr) {
  // call the routine to read data out of the socket (which stuffs it into the packet buffers)

  if (Use_DirectPlay) {
#ifdef WIN32
    dp_DirectPlayDispatch();
#endif
  } else {
    //	nw_ReceiveFromSocket();
    nw_DoReceiveCallbacks();
  }

  int buffer_size;

  // try and get a free buffer and return its size
  if (nw_psnet_buffer_get_next((uint8_t *)data, &buffer_size, from_addr)) {
    return buffer_size;
  }
  return 0;
}

int ExtraBufferTempHack = 0;
// Temp hack to figure out this buffer overflow thing

// Return codes:
//-1 socket not connected
// 0 No packet ready to receive
// >0 Buffer filled with the number of bytes recieved

int nw_ReceiveReliable(SOCKET socketid, uint8_t *buffer, int max_len) {

  int i;
  if (Use_DirectPlay) {
#ifdef WIN32
    dp_DirectPlayDispatch();

    // try and get a free buffer and return its size
    if (nw_psnet_buffer_get_next_by_packet_id((uint8_t *)buffer, &max_len, socketid)) {
      return max_len;
    }
    return 0;
#endif
  }
  reliable_socket *rsocket = NULL;
  // nw_WorkReliable();
  nw_DoReceiveCallbacks();
  if (socketid >= MAXRELIABLESOCKETS) {
    mprintf(0, "Invalid socket id passed to nw_NewReceiveReliable() -- %d\n", socketid);
    return -1;
  }
  rsocket = &reliable_sockets[socketid];
  if ((RNF_CONNECTED != rsocket->status) && (RNF_LIMBO != rsocket->status)) {
    mprintf(0, "Can't receive packet because it isn't connected in nw_ReceiveReliable(). socket = %d\n", socketid);
    return 0;
  }
  // If the buffer position is the position we are waiting for, fill in
  // the buffer we received in the call to this function and return true

  for (i = 0; i < MAXNETBUFFERS; i++) {
    if ((rsocket->rsequence[i] == rsocket->oursequence) && (rsocket->rbuffers[i])) {
      memcpy(buffer, rsocket->rbuffers[i]->buffer, rsocket->recv_len[i]);
      mem_free(rsocket->rbuffers[i]);
      rsocket->rbuffers[i] = NULL;
      rsocket->rsequence[i] = 0;
/*
      mprintf(0,"Found packet for upper layer in nw_ReceiveReliable() %d bytes. seq:%d.\n",
               rsocket->recv_len[i],
               rsocket->oursequence);
*/
      rsocket->oursequence++;
      return rsocket->recv_len[i];
    }
  }

  return 0;
}

// This function will look for a control packet, indicating a
// desire to establish a reliable link.
// When is makes a link, it will return a SOCKET, and fill in from_addr.
// if there is no waiting line, it returns -1
int nw_CheckListenSocket(network_address *from_addr) {
  SOCKADDR_IN *ip_addr; // UDP/TCP socket structure

#ifdef WIN32
  DPID id;
#endif

  if (Use_DirectPlay) {
#ifdef WIN32
    // look for a pending connection
    for (int i = 0; i < MAX_PENDING_NEW_CONNECTIONS; i++) {
      if (Pending_dp_conn[i] != DPID_UNKNOWN) {
        memset(from_addr, 0, sizeof(network_address));
        memcpy(from_addr->address, &Pending_dp_conn[i], sizeof(DPID));
        from_addr->connection_type = NP_DIRECTPLAY;
        id = Pending_dp_conn[i];
        Pending_dp_conn[i] = DPID_UNKNOWN;
        mprintf(0, "New DirectPlay connection in nw_CheckListenSocket().\n");
        return id;
      }
    }
    return -1;
#endif
  }

  // nw_WorkReliable();
  nw_DoReceiveCallbacks();
  int i;
  for (i = 1; i < MAXRELIABLESOCKETS; i++) {
    if (reliable_sockets[i].status == RNF_CONNECTING) {
      reliable_sockets[i].status = RNF_CONNECTED;
      // memcpy(from_addr,&reliable_sockets[i].addr,sizeof(SOCKADDR));
      mprintf(0, "New reliable connection in nw_CheckListenSocket().\n");

      switch (reliable_sockets[i].connection_type) {
      case NP_TCP:
        ip_addr = (SOCKADDR_IN *)&reliable_sockets[i].addr;
        memset(from_addr, 0x00, sizeof(network_address));
        from_addr->port = ntohs(ip_addr->sin_port);
        from_addr->connection_type = NP_TCP;
#ifdef WIN32
        memcpy(from_addr->address, &ip_addr->sin_addr.S_un.S_addr, 4);
#else
        memcpy(from_addr->address, &ip_addr->sin_addr.s_addr, 4);
#endif
        break;

      default:
        Int3();
        break;
      }
      char dbg_output[50];
      nw_GetNumbersFromHostAddress(from_addr, dbg_output);
      mprintf(0, "Got address from: %s\n", dbg_output);
      return i;
    }
  }
  return INVALID_SOCKET;
}

int nw_SendReliable(uint32_t socketid, uint8_t *data, int length, bool urgent) {
  int i;
  int bytesout;
  int use_buffer = -1;
  reliable_socket *rsocket;
  reliable_header send_header;
  int send_this_packet = 1;

  if (length == 0) {
    mprintf(0, "Attempting to send 0 byte network packet in nw_SendReliable()\n");
    Int3();
  }
  // mprintf(0,"Socket id passed to nw_NewSendReliable() -- %d\n",socketid);

  if (NetDebugFile) {
    cfprintf(NetDebugFile, "nw_SendReliable packet of type %d at %f seconds.\n", data[0], timer_GetTime());
  }

  if (Use_DirectPlay) {
#ifdef WIN32
    network_address who_to;
    who_to.connection_type = NP_DIRECTPLAY;
    memcpy(&who_to.address, &socketid, sizeof(DPID));
    return dp_DirectPlaySend(&who_to, data, length, true);
#endif
  }

  ASSERT(length < sizeof(reliable_header));
  // nw_WorkReliable();
  nw_DoReceiveCallbacks();

  if (socketid >= MAXRELIABLESOCKETS) {
    mprintf(0, "Invalid socket id passed to nw_NewSendReliable() -- %d\n", socketid);
    return -1;
  }

  rsocket = &reliable_sockets[socketid];
  if (rsocket->status != RNF_CONNECTED) {
    // We can't send because this isn't a connected reliable socket.
    mprintf(0, "Can't send packet because of status %d in nw_SendReliable(). socket = %d\n", rsocket->status, socketid);
    return -1;
  }
  if (urgent)
    rsocket->send_urgent = 1;
  // See if there is a packet waiting to be sent
  if (-1 != rsocket->waiting_packet_number) {
    int pnum = rsocket->waiting_packet_number;
    ASSERT(rsocket->sbuffers[pnum]);
    // See if there's room for this data
    if (sizeof(reliable_net_sendbuffer) < (rsocket->send_len[pnum] + length)) {
      // Send the previous packet, then use the normal code to generate a new packet
      mprintf(0, "Pending reliable packet buffer full, sending packet now.\n");
      rsocket->waiting_packet_number = -1;

      use_buffer = pnum;
      network_address send_address;
      memset(&send_address, 0, sizeof(network_address));

      memcpy(send_header.data, rsocket->sbuffers[pnum], rsocket->send_len[pnum]);
      send_header.data_len = INTEL_SHORT(rsocket->send_len[pnum]);
      send_header.type = RNT_DATA;
      send_header.send_time = INTEL_FLOAT(timer_GetTime());

      send_address.connection_type = rsocket->connection_type;

      if (NP_TCP == rsocket->connection_type) {
        SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&rsocket->addr;
        memcpy(send_address.address, &inaddr->sin_addr, 4);
        send_address.port = htons(inaddr->sin_port);
        send_address.connection_type = NP_TCP;
      }

      // mprintf(0,"Sending reliable packet! Sequence %d\n",send_header.seq);
      bytesout = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&send_header,
                               RELIABLE_PACKET_HEADER_ONLY_SIZE + rsocket->send_len[use_buffer], &send_address);

      if ((bytesout == SOCKET_ERROR) && (WSAEWOULDBLOCK == WSAGetLastError())) {
        // This will cause it to try to send again next frame. (or sooner)
        rsocket->timesent[use_buffer] = timer_GetTime() - (NETRETRYTIME * 4);
      } else {
        rsocket->timesent[use_buffer] = timer_GetTime();
      }
    } else {
      // tack this data on the end of the previous packet
      // mprintf(0,"Appending to delayed packet...\n");
      ASSERT(rsocket->sbuffers[pnum]);
      memcpy(rsocket->sbuffers[pnum]->buffer + rsocket->send_len[pnum], data, length);
      // int msize = mem_size(rsocket->sbuffers[pnum]);
      rsocket->send_len[pnum] += length;
      return length;
    }
  }

  // Add the new packet to the sending list and send it.
  for (i = 0; i < MAXNETBUFFERS; i++) {
    use_buffer = -1;
    if (NULL == rsocket->sbuffers[i]) {
      // mprintf(0,"Sending in nw_SendReliable() %d bytes seq=%d.\n",length,rsocket->theirsequence);

      rsocket->send_len[i] = length;
      rsocket->sbuffers[i] = (reliable_net_sendbuffer *)mem_malloc(sizeof(reliable_net_sendbuffer));

      memcpy(rsocket->sbuffers[i]->buffer, data, length);

      send_header.seq = INTEL_SHORT(rsocket->theirsequence);
      rsocket->ssequence[i] = rsocket->theirsequence;

      use_buffer = i;
      rsocket->waiting_packet_number = i;

      rsocket->theirsequence++;
      return length;
    }
  }
  mprintf(0, "Can't send packet because a buffer overflow nw_SendReliable(). socket = %d\n", socketid);
  rsocket->status = RNF_BROKEN;

  for (i = 0; i < MAXNETBUFFERS; i++) {
    if (rsocket->sbuffers[i]) {
      mprintf(0, "Buffer %d: %d,%d,%d,%d,%d,%d\n",
              i,
              rsocket->sbuffers[i]->buffer[0],
              rsocket->sbuffers[i]->buffer[1],
              rsocket->sbuffers[i]->buffer[2],
              rsocket->sbuffers[i]->buffer[3],
              rsocket->sbuffers[i]->buffer[4],
              rsocket->sbuffers[i]->buffer[5]);
    }
  }

  // Error ("Couldn't send packet because of buffer overflow!");

  // Int3();
  return 0;
}

// MTS: only used in this file
int nw_InitReliableSocket() {
  nw_RegisterCallback((NetworkReceiveCallback)nw_WorkReliable, NWT_RELIABLE);
  return 1;
}
// MTS: only used in this file
void nw_SendReliableAck(SOCKADDR *raddr, uint32_t sig, network_protocol link_type, float time_sent) {
  int ret;
  reliable_header ack_header;
  ack_header.type = RNT_ACK;
  // mprintf(0,"Sending ACK for sig %d.\n",sig);
  ack_header.data_len = INTEL_SHORT((int16_t)sizeof(uint32_t));
  ack_header.send_time = INTEL_FLOAT(time_sent);
  sig = INTEL_INT(sig);
  memcpy(&ack_header.data, &sig, sizeof(uint32_t));

  network_address send_address;
  memset(&send_address, 0, sizeof(network_address));

  send_address.connection_type = link_type;

  if (NP_TCP == link_type) {
    SOCKADDR_IN *inaddr = (SOCKADDR_IN *)raddr;
    memcpy(send_address.address, &inaddr->sin_addr, 4);
    send_address.port = htons(inaddr->sin_port);
    send_address.connection_type = NP_TCP;
  }

  ret = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&ack_header, RELIABLE_PACKET_HEADER_ONLY_SIZE + sizeof(uint32_t),
                      &send_address);
}

void nw_DoNetworkIdle(void) {
  if (!Use_DirectPlay) {
    nw_DoReceiveCallbacks();
    nw_ReliableResend();
  }
}

#define CONNECTSEQ 0x142 // Magic number for starting a connection, just so it isn't 0

void nw_WorkReliable(uint8_t *data, int len, network_address *naddr) {
  int i;
  int rcode = -1;
  int16_t max_len = NETBUFFERSIZE;
  static reliable_header rcv_buff;
  static SOCKADDR rcv_addr;
  int bytesin = 0;
  int addrlen = sizeof(SOCKADDR);
  uint32_t rcvid; // The id of who we actually received a packet from, as opposed to socketid parm

  if (NP_TCP == naddr->connection_type) {
    SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&rcv_addr;
    memcpy(&inaddr->sin_addr, &naddr->address, 4);
    inaddr->sin_port = htons(naddr->port);
  }

  if (Net_connect_sequence == R_NET_SEQUENCE_CONNECTING) {
    nw_HandleConnectResponse(data, len, naddr);
    return;
  }
  // Check for incoming data

  reliable_socket *rsocket = NULL;
  // Check to see if we need to send a packet out.
  if ((serverconn != -1) && (reliable_sockets[serverconn].status == RNF_LIMBO) &&
      ((timer_GetTime() - last_sent_iamhere) > NETRETRYTIME)) {
    reliable_header conn_header;
    // Now send I_AM_HERE packet
    conn_header.type = RNT_I_AM_HERE;
    conn_header.seq = INTEL_SHORT((int16_t)(~CONNECTSEQ));
    conn_header.data_len = INTEL_SHORT((int16_t)0);
    last_sent_iamhere = timer_GetTime();
    network_address send_address;
    memset(&send_address, 0, sizeof(network_address));

    send_address.connection_type = reliable_sockets[serverconn].connection_type;
    if (NP_TCP == send_address.connection_type) {
      SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&reliable_sockets[serverconn].addr;
      memcpy(send_address.address, &inaddr->sin_addr, 4);
      send_address.port = htons(inaddr->sin_port);
      send_address.connection_type = NP_TCP;
    }

    int ret = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&conn_header, RELIABLE_PACKET_HEADER_ONLY_SIZE, &send_address);

    if ((ret == SOCKET_ERROR) && (WSAEWOULDBLOCK == WSAGetLastError())) {
      reliable_sockets[serverconn].last_packet_sent = timer_GetTime() - NETRETRYTIME;
    } else {
      reliable_sockets[serverconn].last_packet_sent = timer_GetTime();
    }
  }
  network_protocol link_type = naddr->connection_type;
  network_address d3_rcv_addr;
  memcpy(&d3_rcv_addr, naddr, sizeof(network_address));
  memcpy((uint8_t *)&rcv_buff, data, len);
  SOCKADDR_IN *rcvaddr, *rsockaddr;

  do {

    rsocket = NULL;
    if (len) {
      // Someone wants to connect, so find a slot
      if (rcv_buff.type == RNT_REQ_CONN) {
        for (i = 1; i < MAXRELIABLESOCKETS; i++) {
          if ((reliable_sockets[i].status == RNF_CONNECTED) || (reliable_sockets[i].status == RNF_LIMBO))
            // if(memcmp(&rcv_addr,&reliable_sockets[i].addr,sizeof(SOCKADDR))==0)
            if (memcmp(&d3_rcv_addr, &reliable_sockets[i].net_addr, sizeof(network_address)) == 0)
            // d3_rcv_addr
            {
              // We already have a reliable link to this user, so we will ignore it...
              mprintf(0, "Received duplicate connection request. %d\n", i);
              // reliable_sockets[i].last_packet_received = timer_GetTime();
              nw_SendReliableAck(&reliable_sockets[i].addr, INTEL_SHORT(rcv_buff.seq), link_type,
                                 INTEL_FLOAT(rcv_buff.send_time));
              // We will change this as a hack to prevent later code from hooking us up
              rcv_buff.type = 0xff;
              continue;
            }
        }
        for (i = 1; i < MAXRELIABLESOCKETS; i++) {
          if (reliable_sockets[i].status == RNF_UNUSED) {
            // Add the new connection here.
            reliable_sockets[i].connection_type = link_type;
            memcpy(&reliable_sockets[i].net_addr, naddr, sizeof(network_address));
            memcpy(&reliable_sockets[i].addr, &rcv_addr, sizeof(SOCKADDR));
            reliable_sockets[i].ping_pos = 0;
            reliable_sockets[i].num_ping_samples = 0;
            reliable_sockets[i].status = RNF_LIMBO;
            reliable_sockets[i].last_packet_received = timer_GetTime();
            reliable_sockets[i].last_sent = timer_GetTime();
            reliable_sockets[i].waiting_packet_number = -1;
            reliable_sockets[i].send_urgent = 0;

            rsocket = &reliable_sockets[i];
            rcvaddr = (SOCKADDR_IN *)&rcv_addr;
            // Int3();
            mprintf(0, "Connect from %s:%d\n", inet_ntoa(rcvaddr->sin_addr), htons(rcvaddr->sin_port));
            break;
          }
        }
        if (i == MAXRELIABLESOCKETS) {
          // No more connections!
          mprintf(0, "Out of incoming reliable connection sockets\n");
          // Int3();//See Kevin
          continue;
        }
        nw_SendReliableAck(&rsocket->addr, INTEL_SHORT(rcv_buff.seq), link_type, INTEL_FLOAT(rcv_buff.send_time));
      }

      // Find out if this is a packet from someone we were expecting a packet.
      rcvaddr = (SOCKADDR_IN *)&rcv_addr;
      for (i = 1; i < MAXRELIABLESOCKETS; i++) {

        rsockaddr = (SOCKADDR_IN *)&reliable_sockets[i].addr;
        if (memcmp(&d3_rcv_addr, &reliable_sockets[i].net_addr, sizeof(network_address)) == 0) {
          rsocket = &reliable_sockets[i];
          rcvid = i;
          break;
        }
      }
      if (NULL == rsocket) {
        mprintf(0, "Received reliable data from unconnected client.\n");
        char addrstr[200];
        nw_GetNumbersFromHostAddress(&d3_rcv_addr, addrstr);
        mprintf(0, "Received from %s\n", addrstr);
        continue;
      }
      rsocket->last_packet_received = timer_GetTime();

      if (rsocket->status != RNF_CONNECTED) {
        // Get out of limbo
        if (rsocket->status == RNF_LIMBO) {
          // this is our connection to the server
          if ((serverconn != -1)) {
            if (rcv_buff.type == RNT_ACK) {
              int *acknum = (int *)&rcv_buff.data;
              *acknum = INTEL_INT(*acknum);
              if (*acknum == (~CONNECTSEQ & 0xffff)) {
                rsocket->status = RNF_CONNECTED;
                mprintf(0, "Got ACK for IAMHERE!\n");
              }
              continue;
            }
          } else if (rcv_buff.type == RNT_I_AM_HERE) {
            rsocket->status = RNF_CONNECTING;
            nw_SendReliableAck(&rsocket->addr, INTEL_SHORT(rcv_buff.seq), link_type, INTEL_FLOAT(rcv_buff.send_time));
            mprintf(0, "Got IAMHERE!\n");
            continue;
          }
        }
        if ((rcv_buff.type == RNT_DATA) && (serverconn != -1)) {
          rsocket->status = RNF_CONNECTED;
        } else {
          // mprintf(0,"Packet from nonconnected socket -- seq: %d status: %d\n",rcv_buff.seq,rsocket->status);
          rsocket->last_packet_received = timer_GetTime();
          continue;
        }
      }
      // Update the last recv variable so we don't need a heartbeat
      rsocket->last_packet_received = timer_GetTime();

      if (rcv_buff.type == RNT_HEARTBEAT) {
        continue;
      }
      if (rcv_buff.type == RNT_ACK) {
        // Update ping time
        rsocket->num_ping_samples++;

        rsocket->pings[rsocket->ping_pos] = rsocket->last_packet_received - INTEL_FLOAT(rcv_buff.send_time);
        // mprintf(0,"ping time: %f\n",rsocket->pings[rsocket->ping_pos]);
        if (rsocket->num_ping_samples >= MAX_PING_HISTORY) {
          float sort_ping[MAX_PING_HISTORY];
          for (int a = 0; a < MAX_PING_HISTORY; a++)
            sort_ping[a] = rsocket->pings[a];

          qsort(sort_ping, MAX_PING_HISTORY, sizeof(float), nw_PingCompare);
          rsocket->mean_ping = ((sort_ping[MAX_PING_HISTORY / 2] + sort_ping[(MAX_PING_HISTORY / 2) + 1])) / 2;
          // mprintf_at(2,i+1,0,"Ping: %f  ",rsocket->mean_ping);
        }
        rsocket->ping_pos++;
        if (rsocket->ping_pos >= MAX_PING_HISTORY) {
          rsocket->ping_pos = 0;
        }
        for (i = 0; i < MAXNETBUFFERS; i++) {
          uint32_t *acksig = (uint32_t *)&rcv_buff.data;
          *acksig = INTEL_INT(*acksig);
          if (rsocket)
            if (rsocket->sbuffers[i])
              if (rsocket->ssequence[i] == *acksig) {
                // mprintf(0,"Received ACK %d\n",*acksig);
                mem_free(rsocket->sbuffers[i]);
                rsocket->sbuffers[i] = NULL;
                rsocket->ssequence[i] = 0;
              }
        }
        // remove that packet from the send buffer
        rsocket->last_packet_received = timer_GetTime();
        continue;
      }

      if (rcv_buff.type == RNT_DATA_COMP) {
        // More2Come
        // Decompress it. Put it back in the buffer. Process it as RNT_DATA
        rcv_buff.type = RNT_DATA;
      }
      if (rcv_buff.type == RNT_DATA) {

        // If the data is out of order by >= MAXNETBUFFERS-1 ignore that packet for now
        int seqdelta;
        seqdelta = INTEL_SHORT(rcv_buff.seq) - rsocket->oursequence;
        if (seqdelta < 0)
          seqdelta = seqdelta * -1;
        if (seqdelta >= MAXNETBUFFERS - 1) {
          mprintf(0, "Received reliable packet out of order!\n");
          // It's out of order, so we won't ack it, which will mean we will get it again soon.
          continue;
        }
        // else move data into the proper buffer position
        int savepacket = 1;

        if (rsocket->oursequence < (0xffff - (MAXNETBUFFERS - 1))) {
          if (rsocket->oursequence > INTEL_SHORT(rcv_buff.seq)) {
            mprintf(0, "Received old packet with seq of %d\n", INTEL_SHORT(rcv_buff.seq));
            savepacket = 0;
          }

        } else {
          // Sequence is high, so prepare for wrap around
          if (((uint16_t)(INTEL_SHORT(rcv_buff.seq) + rsocket->oursequence)) > (MAXNETBUFFERS - 1)) {
            mprintf(0, "Received old packet with seq of %d\n", INTEL_SHORT(rcv_buff.seq));
            savepacket = 0;
          }
        }

        for (i = 0; i < MAXNETBUFFERS; i++) {
          if ((NULL != rsocket->rbuffers[i]) && (rsocket->rsequence[i] == INTEL_SHORT(rcv_buff.seq))) {
            // Received duplicate packet!
            mprintf(0, "Received duplicate packet!\n");
            savepacket = 0;
          }
        }
        if (savepacket) {
          for (i = 0; i < MAXNETBUFFERS; i++) {
            if (NULL == rsocket->rbuffers[i]) {
              // mprintf(0,"Got good data seq: %d\n",rcv_buff.seq);
              if (INTEL_SHORT(rcv_buff.data_len) > max_len)
                rsocket->recv_len[i] = max_len; // INTEL_SHORT(rcv_buff.data_len);
              else
                rsocket->recv_len[i] = INTEL_SHORT(rcv_buff.data_len);
              rsocket->rbuffers[i] = (reliable_net_rcvbuffer *)mem_malloc(sizeof(reliable_net_rcvbuffer));
              memcpy(rsocket->rbuffers[i]->buffer, rcv_buff.data, rsocket->recv_len[i]);
              rsocket->rsequence[i] = INTEL_SHORT(rcv_buff.seq);
              // mprintf(0,"Adding packet to receive buffer in nw_ReceiveReliable().\n");
              break;
            }
          }
        }
        nw_SendReliableAck(&rsocket->addr, INTEL_SHORT(rcv_buff.seq), link_type, INTEL_FLOAT(rcv_buff.send_time));
      }
    }
  } while (0); // while((IPX_has_data>0) || (UDP_has_data>0));
}

// MTS: only used in this file
void nw_HandleConnectResponse(uint8_t *data, int len, network_address *server_addr) {

  int i;
  static reliable_header ack_header;
  static reliable_header conn_header;
  SOCKADDR rcv_addr;

  memcpy(&ack_header, data, len);

  if (NP_TCP == server_addr->connection_type) {
    SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&rcv_addr;
    memcpy(&inaddr->sin_addr, &server_addr->address, 4);
    inaddr->sin_port = htons(server_addr->port);
  }

  mprintf(0, "Got a connect response!\n");
  if (ack_header.type == RNT_ACK) {
    int *acknum = (int *)&ack_header.data;
    if (INTEL_INT(*acknum) == CONNECTSEQ) {
      // if(memcmp(&rcv_addr,&sockaddr,sizeof(SOCKADDR))==0)
      {
        for (i = 1; i < MAXRELIABLESOCKETS; i++) {
          if (reliable_sockets[i].status == RNF_UNUSED) {
            // Add the new connection here.
            memset(&reliable_sockets[i], 0, sizeof(reliable_socket));
            reliable_sockets[i].connection_type = server_addr->connection_type;
            memcpy(&reliable_sockets[i].net_addr, server_addr, sizeof(network_address));
            reliable_sockets[i].last_packet_received = timer_GetTime();
            memcpy(&reliable_sockets[i].addr, &rcv_addr, sizeof(SOCKADDR));
            reliable_sockets[i].status = RNF_LIMBO;
            Net_connect_socket_id = i;
            reliable_sockets[i].last_sent = timer_GetTime();
            reliable_sockets[i].waiting_packet_number = -1;
            mprintf(0, "Succesfully connected to server in nw_ConnectToServer().\n");
            // Now send I_AM_HERE packet
            conn_header.type = RNT_I_AM_HERE;
            conn_header.seq = INTEL_SHORT((int16_t)(~CONNECTSEQ));
            conn_header.data_len = INTEL_SHORT((int16_t)0);
            serverconn = i;
            first_sent_iamhere = timer_GetTime();
            last_sent_iamhere = timer_GetTime();

            int rcode =
                nw_SendWithID(NWT_RELIABLE, (uint8_t *)&conn_header, RELIABLE_PACKET_HEADER_ONLY_SIZE, server_addr);
            // int rcode = sendto(typeless_sock,(char
            // *)&conn_header,RELIABLE_PACKET_HEADER_ONLY_SIZE,0,addr,sizeof(SOCKADDR));
            if (rcode == SOCKET_ERROR) {
              Net_connect_socket_id = INVALID_SOCKET;
              reliable_sockets[i].status = RNF_UNUSED;
              memset(&reliable_sockets[i], 0, sizeof(reliable_socket));
              mprintf(0, "Unable to send packet in nw_ConnectToServer()\n");

              Net_connect_sequence = R_NET_SEQUENCE_FAILED;
              return;
            }
            reliable_sockets[i].last_packet_sent = timer_GetTime();
            /*
            float f;
            f = timer_GetTime();
            while(((timer_GetTime() - f)<2) && (reliable_sockets[i].status!=RNF_CONNECTING))
            {
                    //nw_WorkReliable();
                    nw_DoReceiveCallbacks();
            }
            */
            Net_connect_sequence = R_NET_SEQUENCE_CONNECTED;
            return;
          }
        }
        mprintf(0, "Out of reliable socket space in nw_ConnectToServer().\n");
        Net_connect_sequence = R_NET_SEQUENCE_FAILED;
        return;
      }
      // else
      //{
      //	mprintf(0,"Received a reliable packet from a server other than the current server\n");
      //}
    } else {
      mprintf(0, "Received out of sequence ACK in nw_ConnectToServer().\n");
    }
  } else {
    mprintf(0, "Received something that isn't an ACK in nw_ConnectToServer().\n");
  }
}

void nw_ConnectToServer(SOCKET *socket, network_address *server_addr) {

  // Send out a RNT_REQ_CONN packet, and wait for it to be acked.

  float time_sent_req = 0;
  float first_sent_req = 0;
  static reliable_header conn_header;
  static reliable_header ack_header;
  int bytesin;
  struct timeval timeout;
  *socket = INVALID_SOCKET;

  if (Use_DirectPlay) {
    // We need a session description to do this, so we don't use this function
    return;
  }

  conn_header.type = RNT_REQ_CONN;
  conn_header.seq = INTEL_SHORT((int16_t)CONNECTSEQ);
  conn_header.data_len = 0;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  if ((server_addr->connection_type == NP_TCP) && (!TCP_active)) {
    return;
  }

  Net_connect_sequence = R_NET_SEQUENCE_CONNECTING;

  memset(&ack_header, 0, sizeof(reliable_header));
  bytesin = 0;

  network_address d3_rcv_addr;
  memset(&d3_rcv_addr, 0, sizeof(network_address));

  int ret = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&conn_header, RELIABLE_PACKET_HEADER_ONLY_SIZE, server_addr);
  if (SOCKET_ERROR == ret) {
    mprintf(0, "Unable to send packet in nw_ConnectToServer()! -- %d\n", WSAGetLastError());
    return;
  }

  first_sent_req = timer_GetTime();
  time_sent_req = timer_GetTime();

  // Wait until we get a response from the server or we timeout

  do {
    nw_DoReceiveCallbacks();
    // Now we wait for the connection to be made....
    if (Net_connect_sequence == R_NET_SEQUENCE_CONNECTED) {
      *socket = Net_connect_socket_id;
      return;
    }
    if ((timer_GetTime() - time_sent_req) > 2) {
      mprintf(0, "Resending connect request.\n");
      int ret = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&conn_header, RELIABLE_PACKET_HEADER_ONLY_SIZE, server_addr);
      if (ret != SOCKET_ERROR) {
        time_sent_req = timer_GetTime();
      } else {
        mprintf(0, "Error sending connection request! -- %d\n", WSAGetLastError());
      }
    }

  } while ((timer_GetTime() - first_sent_req) < NETTIMEOUT);
  return;
}

void nw_CloseSocket(SOCKET *sockp) {
  reliable_header diss_conn_header;
#ifdef WIN32
  if (DP_active) {
    dp_DirectPlayDestroyPlayer(*sockp);
    return;
  }
#endif

  if (*sockp >= MAXRELIABLESOCKETS) {
    mprintf(0, "Invalid socket id passed to nw_NewCloseSocket() -- %d\n", *sockp);
    return;
  }

  if (reliable_sockets[*sockp].status == RNF_UNUSED) {
    mprintf(0, "Trying to close an unused socket (%d) -- ignoring request.\n", *sockp);
  }
  mprintf(0, "Closing socket %d\n", *sockp);
  // Go through every buffer and "free it up(tm)"
  int i;
  for (i = 0; i < MAXNETBUFFERS; i++) {
    if (reliable_sockets[*sockp].rbuffers[i]) {
      mem_free(reliable_sockets[*sockp].rbuffers[i]);
      reliable_sockets[*sockp].rbuffers[i] = NULL;
      reliable_sockets[*sockp].rsequence[i] = 0;
    }
    if (reliable_sockets[*sockp].sbuffers[i]) {
      mem_free(reliable_sockets[*sockp].sbuffers[i]);
      reliable_sockets[*sockp].sbuffers[i] = NULL;
      reliable_sockets[*sockp].rsequence[i] = 0;
    }
  }
  diss_conn_header.type = RNT_DISCONNECT;
  diss_conn_header.seq = INTEL_SHORT((int16_t)(CONNECTSEQ));
  diss_conn_header.data_len = 0;
  if (*sockp == serverconn)
    serverconn = -1;

  network_address send_address;
  memset(&send_address, 0, sizeof(network_address));

  send_address.connection_type = reliable_sockets[*sockp].connection_type;
  if (NP_TCP == reliable_sockets[*sockp].connection_type) {
    SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&reliable_sockets[*sockp].addr;
    memcpy(send_address.address, &inaddr->sin_addr, 4);
    send_address.port = htons(inaddr->sin_port);
    send_address.connection_type = NP_TCP;
  }

  nw_SendWithID(NWT_RELIABLE, (uint8_t *)&diss_conn_header, RELIABLE_PACKET_HEADER_ONLY_SIZE, &send_address);

  memset(&reliable_sockets[*sockp], 0, sizeof(reliable_socket));
  reliable_sockets[*sockp].status = RNF_UNUSED;
}

int nw_CheckReliableSocket(int socknum) {
  // Checks to see if a socket is connected or not.
  if (Use_DirectPlay) {
    return true;
  }
  if (socknum >= MAXRELIABLESOCKETS) {
    mprintf(0, "Invalid socket id passed to nw_CheckReliableSocket() -- %d\n", socknum);
    return 0;
  }
  switch (reliable_sockets[socknum].status) {
  case RNF_UNUSED:
  case RNF_BROKEN:
  case RNF_DISCONNECTED:
    return 0;
  default:
    return 1;
  }
}

// MTS: only used in this file.
int nw_PingCompare(const void *arg1, const void *arg2) {
  float *ping1 = (float *)arg1;
  float *ping2 = (float *)arg2;

  if (*ping1 == *ping2)
    return 0;
  else if (*ping1 > *ping2)
    return 1;
  else if (*ping1 < *ping2)
    return -1;

  return 0;
}

// MTS: only used in this file
// Warning, experimental compression below, if you want to use it, talk to Kevin. Doesn't do much currently, only
// reduces 0's
#define COMPRESS_KEY 0xfd
int nw_Compress(void *srcdata, void *destdata, int count) {
  int i;
  uint8_t *curr_src = (uint8_t *)srcdata;
  uint8_t *currp = (uint8_t *)destdata;
  for (i = 0; i < count; i++) {
    // Woops, we have a char that matches our compress key, so add it as it's own type
    if (curr_src[i] == COMPRESS_KEY) {
      *currp = COMPRESS_KEY;
      currp++;
      //*currp = 1;
      // currp++;
      *currp = COMPRESS_KEY;
      currp++;
    }
    // Look for 3 in a row
    else if ((curr_src[i] == 0) && (curr_src[i + 1] == 0) && (curr_src[i + 2] == 0) && (i + 3 < count)) {
      int repeat_count = 3;
      *currp = COMPRESS_KEY;
      currp++;
      while ((curr_src[i] == curr_src[i + repeat_count]) && (repeat_count < 250) && (i + repeat_count < count)) {
        repeat_count++;
      }
      *currp = repeat_count;
      currp++;
      //*currp = curr_src[i];
      // currp++;
      i += (repeat_count - 1);
    } else {
      *currp = curr_src[i];
      currp++;
    }
  }
  return currp - (uint8_t *)destdata;
}

// MTS: only used in this file
int nw_Uncompress(void *compdata, void *uncompdata, int count) {
  int i;
  int destlen = 0;
  uint8_t *comp_src = (uint8_t *)compdata;
  uint8_t *currp = (uint8_t *)uncompdata;
  for (i = 0; i < count; i++) {
    if (*comp_src == COMPRESS_KEY) {
      comp_src++;
      if (*comp_src == COMPRESS_KEY) {
        currp[destlen] = COMPRESS_KEY;
        destlen++;
      } else {
        for (int a = 0; a < (*comp_src); a++) {
          currp[destlen] = 0; //*(comp_src+1);
          destlen++;
        }
      }
      i++;
      // comp_src++;
      comp_src++;
    } else {
      currp[destlen] = *comp_src;
      destlen++;
      comp_src++;
    }
  }
  return destlen;
}

// MTS: only used in this file
// initialize the buffering system
void nw_psnet_buffer_init() {
  int idx;

  // blast the buffer clean
  memset(Psnet_buffers, 0, sizeof(network_packet_buffer) * MAX_PACKET_BUFFERS);

  // set all buffer sequence #'s to -1
  for (idx = 0; idx < MAX_PACKET_BUFFERS; idx++) {
    Psnet_buffers[idx].sequence_number = -1;
  }

  // initialize the sequence #
  Psnet_seq_number = 0;
  Psnet_lowest_id = -1;
  Psnet_highest_id = -1;
}

// MTS: only used in this file
// buffer a packet (maintain order!)
void nw_psnet_buffer_packet(uint8_t *data, int length, network_address *from) {
  int idx;
  int found_buf = 0;

  // find the first empty packet
  for (idx = 0; idx < MAX_PACKET_BUFFERS; idx++) {
    if (Psnet_buffers[idx].sequence_number == -1) {
      found_buf = 1;
      break;
    }
  }

  // if we didn't find the buffer, report an overrun
  if (!found_buf) {
    mprintf(0, "WARNING - Buffer overrun in psnet\n");
  } else {
    // copy in the data
    memcpy(Psnet_buffers[idx].data, data, length);
    Psnet_buffers[idx].len = length;
    memcpy(&Psnet_buffers[idx].from_addr, from, sizeof(network_address));
    Psnet_buffers[idx].sequence_number = Psnet_seq_number;

    // keep track of the highest id#
    Psnet_highest_id = Psnet_seq_number++;

    // set the lowest id# for the first time
    if (Psnet_lowest_id == -1) {
      Psnet_lowest_id = Psnet_highest_id;
    }
  }
}

// MTS: only used in this file
// get the index of the next packet in order!
int nw_psnet_buffer_get_next_by_packet_id(uint8_t *data, int *length, uint32_t packet_id) {
  int idx;
  int found_buf = 0;

  // if there are no buffers, do nothing
  if ((Psnet_lowest_id == -1) || (Psnet_lowest_id > Psnet_highest_id)) {
    return 0;
  }

  // search until we find the lowest packet index id#
  for (idx = 0; idx < MAX_PACKET_BUFFERS; idx++) {
    uint32_t *thisid;
    thisid = (uint32_t *)&Psnet_buffers[idx].from_addr.address;
    // if we found the buffer
    if ((Psnet_buffers[idx].sequence_number == Psnet_lowest_id) && (packet_id == *thisid)) {
      found_buf = 1;
      break;
    }
  }

  if (!found_buf)
    return 0;

  // copy out the buffer data
  memcpy(data, Psnet_buffers[idx].data, Psnet_buffers[idx].len);
  *length = Psnet_buffers[idx].len;

  // now we need to cleanup the packet list

  // mark the buffer as free
  Psnet_buffers[idx].sequence_number = -1;
  Psnet_lowest_id++;

  return 1;
}

// MTS: only used in this file
// get the index of the next packet in order!
int nw_psnet_buffer_get_next(uint8_t *data, int *length, network_address *from) {
  int idx;
  int found_buf = 0;

  // if there are no buffers, do nothing
  if ((Psnet_lowest_id == -1) || (Psnet_lowest_id > Psnet_highest_id)) {
    return 0;
  }

  // search until we find the lowest packet index id#
  for (idx = 0; idx < MAX_PACKET_BUFFERS; idx++) {
    // if we found the buffer
    if (Psnet_buffers[idx].sequence_number == Psnet_lowest_id) {
      found_buf = 1;
      break;
    }
  }

  // at this point, we should _always_ have found the buffer
  ASSERT(found_buf);

  // copy out the buffer data
  memcpy(data, Psnet_buffers[idx].data, Psnet_buffers[idx].len);
  *length = Psnet_buffers[idx].len;
  memcpy(from, &Psnet_buffers[idx].from_addr, sizeof(network_address));

  // now we need to cleanup the packet list

  // mark the buffer as free
  Psnet_buffers[idx].sequence_number = -1;
  Psnet_lowest_id++;

  return 1;
}

#ifdef WIN32
// MTS: only used in this file
// functions to get the status of a RAS connection
uint32_t psnet_ras_status() {
  int rval;
  DWORD size, num_connections, i;
  RASCONN rasbuffer[25];
  HINSTANCE ras_handle;
  uint32_t rasip = 0;
  RASPPPIP projection;
  int Ras_connected;

  Ras_connected = 0;

  // first, call a LoadLibrary to load the RAS api
  ras_handle = LoadLibrary("rasapi32.dll");
  if (ras_handle == NULL) {
    return INADDR_ANY;
  }

  pRasEnumConnections =
      (DWORD(__stdcall *)(LPRASCONN, LPDWORD, LPDWORD))GetProcAddress(ras_handle, "RasEnumConnectionsA");
  if (!pRasEnumConnections) {
    FreeLibrary(ras_handle);
    return INADDR_ANY;
  }
  pRasGetConnectStatus =
      (DWORD(__stdcall *)(HRASCONN, LPRASCONNSTATUS))GetProcAddress(ras_handle, "RasGetConnectStatusA");
  if (!pRasGetConnectStatus) {
    FreeLibrary(ras_handle);
    return INADDR_ANY;
  }
  pRasGetProjectionInfo =
      (DWORD(__stdcall *)(HRASCONN, RASPROJECTION, LPVOID, LPDWORD))GetProcAddress(ras_handle, "RasGetProjectionInfoA");
  if (!pRasGetProjectionInfo) {
    FreeLibrary(ras_handle);
    return INADDR_ANY;
  }

  size = sizeof(rasbuffer);
  rasbuffer[0].dwSize = sizeof(RASCONN);

  rval = pRasEnumConnections(rasbuffer, &size, &num_connections);
  if (rval) {
    FreeLibrary(ras_handle);
    return INADDR_ANY;
  }

  // JAS: My computer gets to this point, but I have no RAS connections,
  // so just exit
  if (num_connections < 1) {
    mprintf(0, "Found no RAS connections\n");
    FreeLibrary(ras_handle);
    return INADDR_ANY;
  }

  mprintf(0, "Found %d connections\n", num_connections);

  for (i = 0; i < num_connections; i++) {
    RASCONNSTATUS status;
    DWORD size;

    mprintf(0, "Connection %d:\n", i);
    mprintf(0, "Entry Name: %s\n", rasbuffer[i].szEntryName);
    mprintf(0, "Device Type: %s\n", rasbuffer[i].szDeviceType);
    mprintf(0, "Device Name: %s\n", rasbuffer[i].szDeviceName);

    // get the connection status
    status.dwSize = sizeof(RASCONNSTATUS);
    rval = pRasGetConnectStatus(rasbuffer[i].hrasconn, &status);
    if (rval != 0) {
      FreeLibrary(ras_handle);
      return INADDR_ANY;
    }

    mprintf(0, "\tStatus: %s\n", (status.rasconnstate == RASCS_Connected) ? "Connected" : "Not Connected");

    // get the projection informatiom
    size = sizeof(projection);
    projection.dwSize = size;
    rval = pRasGetProjectionInfo(rasbuffer[i].hrasconn, RASP_PppIp, &projection, &size);
    if (rval != 0) {
      FreeLibrary(ras_handle);
      return INADDR_ANY;
    }

    mprintf(0, "\tIP Address: %s\n", projection.szIpAddress);
  }

  Ras_connected = 1;

  FreeLibrary(ras_handle);
  rasip = inet_addr(projection.szIpAddress);
  if (rasip == INADDR_NONE)
    return INADDR_ANY;
  // The ip of the RAS connection
  return rasip;
}
#endif

static async_dns_lookup aslu;
static async_dns_lookup *lastaslu = NULL;

#ifdef WIN32
#define CDECLCALL __cdecl
#else
#define CDECLCALL
#endif

#ifdef __LINUX__
int CDECLCALL gethostbynameworker(void *parm);
#include "SDL.h"
#include "SDL_thread.h"

// rcg06192000 use SDL threads.
// #include <pthread.h>
// #include <dlfcn.h>
// typedef int (*pthread_create_fp)(pthread_t *__thread,__const pthread_attr_t *__attr,void *(*__start_routine) (void
// *),void *__arg); typedef int (*pthread_detach_fp)(pthread_t __th); typedef pthread_t (*pthread_self_fp)(void); static
// pthread_create_fp dpthread_create = NULL; static pthread_detach_fp dpthread_detach = NULL; static pthread_self_fp
// dpthread_self = NULL;

void nw_LoadThreadLibrary(void) {
  // rcg06192000 use SDL threads.
  /*
          if(dpthread_create)
                  return;

          void *lib;

          lib = dlopen("libpthread.so",RTLD_GLOBAL|RTLD_NOW);
          if(!lib)
          {
                  Int3();
                  return;
          }

          dpthread_create = (pthread_create_fp)dlsym(lib,"pthread_create");
          dpthread_detach = (pthread_detach_fp)dlsym(lib,"pthread_detach");
          dpthread_self = (pthread_self_fp)dlsym(lib,"pthread_self");

          if(!dpthread_create || !dpthread_detach || !dpthread_self)
          {
                  dpthread_create = NULL;	//this variable I use to see if the library is loaded
                  Int3();
                  return;
          }

          // don't close the library...we need it open for future use
          // and we can't close it on atexit() because linux will segfault for some stupid reason
  */
}
#else
void CDECLCALL gethostbynameworker(void *parm);
#endif

int nw_Asyncgethostbyname(uint32_t *ip, int command, char *hostname) {

  if (command == NW_AGHBN_LOOKUP) {
    if (lastaslu) {
      lastaslu->abort = true;

      // rcg06212000 join the thread.
#ifdef __LINUX__
      SDL_WaitThread(lastaslu->threadId, NULL);
      free(lastaslu);
#endif
    } // if

    // rcg06262000 don't need all the rigamarole since we join the thread.

#if (!defined(__LINUX__))
    async_dns_lookup *newaslu;
    newaslu = (async_dns_lookup *)mem_malloc(sizeof(async_dns_lookup));
    memset(&newaslu->ip, 0, sizeof(uint32_t));
    newaslu->host = hostname;
    newaslu->done = false;
    newaslu->error = false;
    newaslu->abort = false;
    lastaslu = newaslu;
    aslu.done = false;
#else
    memset(&aslu.ip, 0, sizeof(uint32_t));
    aslu.host = hostname;
    aslu.done = false;
    aslu.error = false;
    aslu.abort = false;
    lastaslu = &aslu;
    aslu.done = false;
#endif

#ifdef WIN32
    _beginthread(gethostbynameworker, 0, newaslu);
#elif defined(__LINUX__)
    // rcg06192000 use SDL threads.
    /*
            nw_LoadThreadLibrary();
            if(!dpthread_create)
            {

                    HOSTENT *he = gethostbyname(lastaslu->host);
                    if(he==NULL)
                    {
                            lastaslu->error = true;
                    }
                    else
                    {
                            memcpy(&lastaslu->ip,he->h_addr_list[0],sizeof(uint32_t));
                            lastaslu->done = true;
                            memcpy(&aslu,lastaslu,sizeof(async_dns_lookup));
                    }
            }else
    */

    {
      // rcg06192000 SDLified.
      // pthread_t thread;
      // dpthread_create(&thread, NULL, gethostbynameworker,newaslu);
      aslu.threadId = SDL_CreateThread(gethostbynameworker, "dnsworker", &aslu);
    }
#else
    HOSTENT *he = gethostbyname(lastaslu->host);
    if (he == NULL) {
      lastaslu->error = true;
    } else {
      memcpy(&lastaslu->ip, he->h_addr_list[0], sizeof(uint32_t));
      lastaslu->done = true;
      memcpy(&aslu, lastaslu, sizeof(async_dns_lookup));
    }
#endif
    return 1;
  } else if (command == NW_AGHBN_CANCEL) {
    if (lastaslu) {
      lastaslu->abort = true;

      // rcg06212000 join the thread.
#ifdef __LINUX__
      SDL_WaitThread(lastaslu->threadId, NULL);
#endif
    } // if
    lastaslu = NULL;
  } else if (command == NW_AGHBN_READ) {
    if (!lastaslu)
      return -1;
    if (aslu.done) {
      // rcg06212000 join the thread.
#ifdef __LINUX__
      SDL_WaitThread(aslu.threadId, NULL);
#endif

      lastaslu = NULL;
      memcpy(ip, &aslu.ip, sizeof(uint32_t));
      return 1;
    } else if (aslu.error) {
      // rcg06212000 join the thread.
#ifdef __LINUX__
      SDL_WaitThread(aslu.threadId, NULL);
#else
      mem_free(lastaslu);
#endif

      lastaslu = NULL;
      return -1;
    } else
      return 0;
  }
  return -2;
}

// This is the worker thread which does the lookup.
#ifdef __LINUX__
int CDECLCALL gethostbynameworker(void *parm)
#else
void CDECLCALL gethostbynameworker(void *parm)
#endif
{
  // rcg06192000 nope.
  //	#ifdef __LINUX__
  //	dpthread_detach(dpthread_self());
  //	#endif

  async_dns_lookup *lookup = (async_dns_lookup *)parm;

  mprintf(0, "IPLOOKUP: Starting threaded lookup ...");
  HOSTENT *he = gethostbyname(lookup->host);
  mprintf(0, "IPLOOKUP: Threaded lookup complete.");

  if (he == NULL) {
    lookup->error = true;
#ifdef __LINUX__
    return 0;
#else
    return;
#endif
  } else if (!lookup->abort) {
    memcpy(&lookup->ip, he->h_addr_list[0], sizeof(uint32_t));
    mprintf(0, "IPLOOKUP: [%s] is %d.%d.%d.%d ...",
            lookup->host,
            (lookup->ip & 0x000000FF),
            (lookup->ip & 0x0000FF00) >> 8,
            (lookup->ip & 0x00FF0000) >> 16,
            (lookup->ip & 0xFF000000) >> 24);
    // memcpy(&aslu,lookup,sizeof(async_dns_lookup));
    lookup->done = true;
  }

// rcg06252000 don't free this, 'cause we need the threadId.
#ifndef __LINUX__
  mem_free(lookup);
#endif

#ifdef __LINUX__
  return 0;
#endif
}

int nw_ReccomendPPS() {
  static char szconnspeed[100];
  int len = 99;
  strcpy(szconnspeed, "");
  Database()->read("ConnectionSpeed", szconnspeed, &len);
  if (stricmp(szconnspeed, "28K") == 0)
    return 5;
  else if (stricmp(szconnspeed, "33K") == 0)
    return 6;
  else if (stricmp(szconnspeed, "56K") == 0)
    return 7;
  else if (stricmp(szconnspeed, "ISDN") == 0)
    return 8;
  else if (stricmp(szconnspeed, "Cable") == 0)
    return 9;
  else if (stricmp(szconnspeed, "Fast") == 0)
    return 12;
  else
    return 7;
}

// Register the networking library to call your function back
// When data containing your ID is found
// Returns non-zero if succesfull, Zero if this ID is already registered
int nw_RegisterCallback(NetworkReceiveCallback nfp, uint8_t id) {
  ASSERT(id < 16);

  // rcg06212000 this happens all the time; let it slide.
  // if(Netcallbacks[id])
  //{
  //	mprintf(0,"Trying to reregister a callback!\n");
  //	Int3(); // Get Kevin!
  //}

  Netcallbacks[id] = nfp;
  return 0;
}

NetworkReceiveCallback nw_UnRegisterCallback(uint8_t id) {
  NetworkReceiveCallback nfp;
  ASSERT(id < 16);
  nfp = Netcallbacks[id];
  Netcallbacks[id] = NULL;
  return nfp;
}

int nw_SendWithID(uint8_t id, uint8_t *data, int len, network_address *who_to) {
  uint8_t packet_data[1500];
  int send_this_packet = 1;
  SOCKET send_sock;
  SOCKADDR_IN sock_addr; // UDP/TCP socket structure

  int ret, send_len;
  uint8_t iaddr[6], *send_data;
  int16_t port;
  fd_set wfds;

  ASSERT(data);
  ASSERT(len);
  ASSERT(who_to);

  timeval timeout = {0, 0};

  packet_data[0] = id;
  memcpy(packet_data + 1, data, len);
  len++; // Account for the added byte

  //	if (NetDebugFile)
  //		cfprintf (NetDebugFile,"nw_SendWithID packet of id=%d type %d at %f
  // seconds.\n",id,data[0],timer_GetTime());

// mprintf(0,"Sending packet for id %d.\n",id);
#ifdef WIN32
  if (Use_DirectPlay)
    return dp_DirectPlaySend(who_to, (uint8_t *)data, len, false);
#endif

  // mprintf(1, "network: type %d\n", who_to->connection_type);
  // send_sock = *Unreliable_socket;
  switch (who_to->connection_type) {
  case NP_TCP:
    if (id == NWT_RELIABLE) {
      NetStatistics.tcp_total_packets_sent++;
      NetStatistics.tcp_total_bytes_sent += len;
    } else if (id == NWT_UNRELIABLE) {
      NetStatistics.udp_total_packets_sent++;
      NetStatistics.udp_total_bytes_sent += len;
    }

    send_sock = TCP_socket;
    if (!TCP_active)
      return 0;
    break;
  default:
    mprintf(2, "Unknown protocol type in nw_Send()\n");
    Int3();
    return 0;
  }

  /*
  uint8_t compdata[MAX_PACKET_SIZE*3];
  uint8_t testdata[MAX_PACKET_SIZE*3];
  int uncompsize;

  ////Int3();
  Uncompressed_outgoing_data_len += len;
  int compsize = nw_Compress(data,compdata,len);
  Compressed_outgoing_data_len += compsize;
  uncompsize = nw_Uncompress(compdata,testdata,compsize);

  ASSERT(uncompsize==len);
  ASSERT(memcmp(data,testdata,uncompsize)==0);

  int my_comp_ratio = (float) ((float)Uncompressed_outgoing_data_len/(float)Compressed_outgoing_data_len);

  mprintf_at(2,1,0,"Compression: %d%%  ",my_comp_ratio);
  */
  if (!Sockets_initted) {
    mprintf(0, "Network ==> Socket not inited in nw_Send\n");
    return 0;
  }

  memset(iaddr, 0x00, 6);
  memcpy(iaddr, who_to->address, 6);

  port = who_to->port;

  if (port == 0) {
    mprintf(0, "Network ==> destination port %d invalid in psnet_send\n", port);
    Int3();
    return 0;
  }

  send_len = len;
  send_data = (uint8_t *)packet_data;

  FD_ZERO(&wfds);
  FD_SET(send_sock, &wfds);

  int sock_writable = select(send_sock + 1, NULL, &wfds, NULL, &timeout);
  if (sock_writable == SOCKET_ERROR) {
    mprintf(0, "Error on blocking select for write %d\n", WSAGetLastError());
    return 0;
  }

  if (!sock_writable) {
    // This packet gets dropped.
    return 0;
  }

  if (send_this_packet) {
    switch (who_to->connection_type) {
    case NP_TCP:
      sock_addr.sin_family = AF_INET;
      memcpy(&sock_addr.sin_addr.s_addr, iaddr, 4);
      sock_addr.sin_port = htons(port);

      ret = sendto(TCP_socket, (char *)send_data, send_len, 0, (SOCKADDR *)&sock_addr, sizeof(sock_addr));
      break;

    default:
      Int3(); // Unknown protocol
      break;

    } // end switch
  }
  int lasterr;
  if (ret != SOCKET_ERROR) {
    return 1;
  }
  lasterr = WSAGetLastError();
  if (lasterr == WSAEWOULDBLOCK) {
    return 0;
  }

  mprintf(0, "Couldn't send data (%d)!\n", lasterr);
  return 0;
}

int nw_DoReceiveCallbacks(void) {
  SOCKADDR_IN ip_addr; // UDP/TCP socket structure
  socklen_t read_len, from_len;
  network_address from_addr;

  uint8_t packet_data[1500];

  nw_ReliableResend();

  while (TCP_active) {
    // check if there is any data on the socket to be read.  The amount of data that can be
    // atomically read is stored in len.

#if 0
		fd_set	rfds;
		FD_ZERO(&rfds);
		FD_SET( TCP_socket, &rfds );
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;

		timeval	timeout;
		if ( select( TCP_socket+1, &rfds, NULL, NULL, &timeout) == SOCKET_ERROR)
		{
			mprintf(0, "Error %d doing a socket select on IP read\n", WSAGetLastError());
			break;
		}

		// if the read file descriptor is not set, then bail!
		if ( !FD_ISSET(TCP_socket, &rfds ) )
			break;
#endif
    // get data off the socket and process
    from_len = sizeof(SOCKADDR_IN);
    read_len = recvfrom(TCP_socket, (char *)packet_data, 1500, 0, (SOCKADDR *)&ip_addr, &from_len);

    if (read_len == SOCKET_ERROR) {
      int x = WSAGetLastError();
      if (x != WSAEWOULDBLOCK) {
        mprintf(0, "Read error on IP socket.  Winsock error %d \n", x);
      }
      break;
    }
    memset(&from_addr, 0x00, sizeof(network_address));
    from_addr.connection_type = NP_TCP;
    from_addr.port = ntohs(ip_addr.sin_port);

#ifdef WIN32
    memcpy(from_addr.address, &ip_addr.sin_addr.S_un.S_addr, 4);
#else
    memcpy(from_addr.address, &ip_addr.sin_addr.s_addr, 4);
#endif
    uint8_t packet_id = (packet_data[0] & 0x0f);
    if (Netcallbacks[packet_id]) {
      // mprintf(0,"Calling network callback for id %d.\n",packet_id);
      int rlen = read_len - 1;
      if (packet_id == NWT_UNRELIABLE) {
        NetStatistics.udp_total_packets_rec++;
        NetStatistics.udp_total_bytes_rec += rlen;
      } else if (packet_id == NWT_RELIABLE) {
        NetStatistics.tcp_total_packets_rec++;
        NetStatistics.tcp_total_bytes_rec += rlen;
      }

      Netcallbacks[packet_id](packet_data + 1, rlen, &from_addr);
    }
  }

  return 0;
}

// MTS: only used in this file?
// Resend any unack'd packets and send any buffered packets, heartbeats, etc.
void nw_ReliableResend(void) {
  int i, j;
  int rcode = -1;
  int16_t max_len = NETBUFFERSIZE;
  static reliable_header rcv_buff;
  static SOCKADDR rcv_addr;
  int bytesin = 0;
  int addrlen = sizeof(SOCKADDR);
  reliable_socket *rsocket = NULL;
  // Go through each reliable socket that is connected and do any needed work.
  for (j = 0; j < MAXRELIABLESOCKETS; j++) {
    rsocket = &reliable_sockets[j];

    if (serverconn == -1) {
      if (rsocket->status == RNF_LIMBO)
        if ((timer_GetTime() - rsocket->last_packet_received) > NETTIMEOUT) {
          mprintf(0, "Reliable (but in limbo) socket (%d) timed out in nw_WorkReliable().\n", j);
          memset(rsocket, 0, sizeof(reliable_socket));
          rsocket->status = RNF_UNUSED; // Won't work if this is an outgoing connection.
        }
    } else {
      if ((rsocket->status == RNF_LIMBO) && ((timer_GetTime() - first_sent_iamhere) > NETTIMEOUT)) {
        rsocket->status = RNF_BROKEN;
        mprintf(0, "Reliable socket (%d) timed out in nw_WorkReliable().\n", j);
      }
    }

    if (rsocket->status == RNF_CONNECTED) {
      float retry_packet_time;
      if ((rsocket->mean_ping == 0) || (rsocket->mean_ping > (NETRETRYTIME * 4))) {
        retry_packet_time = NETRETRYTIME;
      } else {
        if (rsocket->mean_ping < MIN_NET_RETRYTIME) {
          retry_packet_time = (float)MIN_NET_RETRYTIME;
          // mprintf(0,"Using retransmission time of %f\n",retry_packet_time);
        } else {
          retry_packet_time = ((float)(float)rsocket->mean_ping * (float)1.25);
          // mprintf(0,"Using retransmission time of %f\n",retry_packet_time);
        }
      }
      // Iterate through send buffers.
      for (i = 0; i < MAXNETBUFFERS; i++) {
        if (((i == rsocket->waiting_packet_number) &&
             ((((timer_GetTime() - rsocket->last_sent) > R_NET_PACKET_QUEUE_TIME)) ||
              ((rsocket->mean_ping > 0) && (rsocket->mean_ping < R_NET_PACKET_QUEUE_TIME)) || rsocket->send_urgent)) ||
            ((rsocket->sbuffers[i]) && ((timer_GetTime() - rsocket->timesent[i]) >= retry_packet_time))) // Send again
        {

          if (i == rsocket->waiting_packet_number) {
            rsocket->waiting_packet_number = -1;
            rsocket->last_sent = timer_GetTime();
            // mprintf(0,"Sending delayed packet...\n");
          }
          reliable_header send_header;
          // mprintf(0,"Resending reliable packet in nw_WorkReliable().\n");
          send_header.send_time = INTEL_FLOAT(timer_GetTime());
          send_header.seq = INTEL_SHORT(rsocket->ssequence[i]);
          memcpy(send_header.data, rsocket->sbuffers[i]->buffer, rsocket->send_len[i]);
          send_header.data_len = INTEL_SHORT(rsocket->send_len[i]);
          send_header.type = RNT_DATA;

          network_address send_address;
          memset(&send_address, 0, sizeof(network_address));

          send_address.connection_type = rsocket->connection_type;

          if (NP_TCP == send_address.connection_type) {
            SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&rsocket->addr;
            memcpy(send_address.address, &inaddr->sin_addr, 4);
            send_address.port = htons(inaddr->sin_port);
            send_address.connection_type = NP_TCP;

            int len = RELIABLE_PACKET_HEADER_ONLY_SIZE + rsocket->send_len[i];
            NetStatistics.tcp_total_packets_sent--;    // decrement because we are going to inc
                                                       // in nw_SendWithID
            NetStatistics.tcp_total_bytes_sent -= len; // see above
            NetStatistics.tcp_total_packets_resent++;
            NetStatistics.tcp_total_bytes_resent += len;
          }

          // mprintf(0,"Resending reliable packet! Sequence %d\n",send_header.seq);
          rcode = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&send_header,
                                RELIABLE_PACKET_HEADER_ONLY_SIZE + rsocket->send_len[i], &send_address);

          if ((rcode == SOCKET_ERROR) && (WSAEWOULDBLOCK == WSAGetLastError())) {
            // The packet didn't get sent, flag it to try again next frame
            rsocket->timesent[i] = timer_GetTime() - (NETRETRYTIME * 4);
          } else {
            rsocket->last_packet_sent = timer_GetTime();
            rsocket->timesent[i] = timer_GetTime();
          }
        }
      }
      // We've sent all the packets, now we go out of urgent mode.
      rsocket->send_urgent = 0;
      if ((rsocket->status == RNF_CONNECTED) && ((timer_GetTime() - rsocket->last_packet_sent) > NETHEARTBEATTIME)) {
        reliable_header send_header;
        // mprintf(0,"Resending reliable packet in nw_WorkReliable().\n");
        send_header.send_time = INTEL_FLOAT(timer_GetTime());
        send_header.seq = INTEL_SHORT((int16_t)0);
        send_header.data_len = INTEL_SHORT((int16_t)0);
        send_header.type = RNT_HEARTBEAT;

        rcode = -1;
        network_address send_address;
        memset(&send_address, 0, sizeof(network_address));

        send_address.connection_type = rsocket->connection_type;

        if (NP_TCP == send_address.connection_type) {
          SOCKADDR_IN *inaddr = (SOCKADDR_IN *)&rsocket->addr;
          memcpy(send_address.address, &inaddr->sin_addr, 4);
          send_address.port = htons(inaddr->sin_port);
          send_address.connection_type = NP_TCP;

          int len = RELIABLE_PACKET_HEADER_ONLY_SIZE + rsocket->send_len[i];
          NetStatistics.tcp_total_packets_sent--;    // decrement because we are going to inc
                                                     // in nw_SendWithID
          NetStatistics.tcp_total_bytes_sent -= len; // see above
          NetStatistics.tcp_total_packets_resent++;
          NetStatistics.tcp_total_bytes_resent += len;
        }

        rcode = nw_SendWithID(NWT_RELIABLE, (uint8_t *)&send_header, RELIABLE_PACKET_HEADER_ONLY_SIZE, &send_address);

        if ((rcode != SOCKET_ERROR) && (WSAEWOULDBLOCK != WSAGetLastError())) {
          // It must have been sent
          rsocket->last_packet_sent = timer_GetTime();
        }
      }

      if ((rsocket->status == RNF_CONNECTED) && ((timer_GetTime() - rsocket->last_packet_received) > NETTIMEOUT)) {
        // This socket is hosed.....inform someone?
        mprintf(0, "Reliable Socket (%d) timed out in nw_WorkReliable().\n", j);
        rsocket->status = RNF_BROKEN;
      }
    }
  }
}

// fills in the buffer with network stats
// pass NULL to reset the stats
void nw_GetNetworkStats(tNetworkStatus *stats) {
  if (!stats) {
    // reset the stats
    memset(&NetStatistics, 0, sizeof(NetStatistics));
    return;
  }

  memcpy(stats, &NetStatistics, sizeof(NetStatistics));
}
