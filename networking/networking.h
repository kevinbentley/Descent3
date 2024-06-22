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

 * $Logfile: /DescentIII/Main/lib/networking.h $
 * $Revision: 1.9 $
 * $Date: 2004/12/05 04:00:20 $
 * $Author: ryan $
 *
 *
 *
 * $Log: networking.h,v $
 * Revision 1.10  2004/12/05 04:38:23  ryan
 * Disable IPX support.
 *
 * Revision 1.9  2004/12/05 04:00:20  ryan
 * MacOS X patches.
 *
 * Revision 1.8  2004/03/21 17:11:39  kevinb
 * Fixes so linux will compile again. Tested with gcc-2.96
 *
 * Revision 1.7  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.6  2004/02/09 04:14:51  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.5  2001/01/13 21:48:46  icculus
 * patched to (re)compile on win32.
 *
 * Revision 1.4  2000/09/22 19:05:40  icculus
 * updated
 *
 * Revision 1.3  2000/06/24 01:15:15  icculus
 * patched to compile.
 *
 * Revision 1.2  2000/06/03 14:33:51  icculus
 * Merge with Outrage 1.4 tree...
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 49    8/31/99 5:30p Jason
 * network statistics code
 *
 * 48    8/21/99 3:14a Jeff
 * real async lookup in linux
 *
 * 47    7/29/99 10:33a Kevin
 * Macintosh Updates
 *
 * 45		7/28/99 ????? Kevin
 *	Mac Stuff
 *
 *	44    5/22/99 1:57a Kevin
 * increased timeout in reliable code
 *
 * 43    5/19/99 5:21p Kevin
 * changed return value of nw_GetHostAddressFromNumbers()
 *
 * 42    5/10/99 10:53p Ardussi
 * changes to compile on Mac
 *
 * 41    4/30/99 5:06p Kevin
 * misc dedicated server, networking and low memory enhancements
 *
 * 40    4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 39    4/17/99 6:14a Jeff
 * fixed errors compiling due to typos
 *
 * 38    4/17/99 5:50a Jeff
 * added defines and macros for Linux port
 *
 * 37    4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 36    4/15/99 2:57a Jeff
 * added some defines and includes needed for linux ipx
 *
 * 35    4/12/99 3:16p Kevin
 * Added a bunch of stuff for the linux version
 *
 * 34    2/24/99 12:48p Kevin
 * Added urgent flag to nw_SendReliable. It causes the packet to go out
 * that frame.
 *
 * 33    2/05/99 7:24p Kevin
 * Added NAGLE type packet buffering to reliable networking code
 *
 * 32    1/26/99 9:44p Jeff
 * moved tcplog functions to mono library
 *
 * 31    1/13/99 6:48a Jeff
 * made linux friendly with some #ifdef's
 *
 * 29    1/08/99 2:58p Kevin
 * Added TCP mprintf support so you can log to a remote machine.
 *
 * 28    12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 27    12/03/98 9:29a Kevin
 * Added better ip selection code
 *
 * 26    11/02/98 6:41p Jason
 * changed demo port number
 *
 * 25    10/12/98 8:39p Kevin
 * removed mprintf's and fixed some smallish bugs
 *
 * 24    10/01/98 11:37a Kevin
 * UI fixes and stuff
 *
 * 23    9/28/98 11:02a Kevin
 * added Networking defer, and fixed some UI issues
 *
 * 22    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 21    9/21/98 11:19a Kevin
 * check protocol before entering multiplayer screens
 *
 * 20    9/04/98 1:51p Kevin
 * implemented asyncronous gethostbyname
 *
 * 19    8/14/98 4:54p Kevin
 * More directplay stuff
 *
 * 18    8/13/98 6:32p Kevin
 * Initial implementation of directplay API
 *
 */
#ifndef NETWORKING_H
#define NETWORKING_H

#include "pstypes.h"
#include <cstdint>

#if defined(WIN32)
// Windows includes
#include <winsock.h>

// helper macros for working with SOCKADDR_IN to make it look nicer between windows and Linux
static inline void INADDR_SET_SUN_SADDR(struct in_addr *st, uint32_t value) { st->S_un.S_addr = value; }
static inline void INADDR_GET_SUN_SADDR(struct in_addr *st, uint32_t *value) { *value = st->S_un.S_addr; }
static inline void INADDR_SET_SUN_SUNW(struct in_addr *st, uint16_t s_w1, uint16_t s_w2) {
  st->S_un.S_un_w.s_w1 = s_w1;
  st->S_un.S_un_w.s_w2 = s_w2;
}
static inline void INADDR_GET_SUN_SUNW(struct in_addr *st, uint16_t *s_w1, uint16_t *s_w2) {
  *s_w1 = st->S_un.S_un_w.s_w1;
  *s_w2 = st->S_un.S_un_w.s_w2;
}
static inline void INADDR_SET_SUN_SUNB(struct in_addr *st, uint8_t s_b1, uint8_t s_b2, uint8_t s_b3,
                                uint8_t s_b4) {
  st->S_un.S_un_b.s_b1 = s_b1;
  st->S_un.S_un_b.s_b2 = s_b2;
  st->S_un.S_un_b.s_b3 = s_b3;
  st->S_un.S_un_b.s_b4 = s_b4;
}
static inline void INADDR_GET_SUN_SUNB(struct in_addr *st, uint8_t *s_b1, uint8_t *s_b2, uint8_t *s_b3,
                                uint8_t *s_b4) {
  *s_b1 = st->S_un.S_un_b.s_b1;
  *s_b2 = st->S_un.S_un_b.s_b2;
  *s_b3 = st->S_un.S_un_b.s_b3;
  *s_b4 = st->S_un.S_un_b.s_b4;
}

#elif defined(__LINUX__)
// Linux includes/defines

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>

// rcg06212000 my SDL adds.
#include "SDL.h"
#include "SDL_thread.h"

#include "linux_fix.h"

#define SOCKET int
#define BOOL bool
#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr
#define INVALID_SOCKET -1

#ifdef TRUE
#undef TRUE
#endif
#define TRUE true

#ifdef FALSE
#undef FALSE
#endif
#define FALSE false
#define HOSTENT struct hostent
#define SOCKET_ERROR -1

// Winsock = sockets error translation
#define WSAEWOULDBLOCK EWOULDBLOCK
#define WSAEINVAL EINVAL
#define WSAENOPROTOOPT ENOPROTOOPT

#ifndef WSAGetLastError
#define WSAGetLastError() errno
#endif

extern bool Use_DirectPlay;

// helper macros for working with SOCKADDR_IN to make it look nicer between windows and Linux
static inline void INADDR_SET_SUN_SADDR(struct in_addr *st, uint32_t value) { st->s_addr = value; }
static inline void INADDR_GET_SUN_SADDR(struct in_addr *st, uint32_t *value) { *value = st->s_addr; }
static inline void INADDR_SET_SUN_SUNW(struct in_addr *st, uint16_t s_w1, uint16_t s_w2) {
  union {
    struct {
      uint8_t s_b1, s_b2, s_b3, s_b4;
    } S_un_b;
    struct {
      uint16_t s_w1, s_w2;
    } S_un_w;
    uint32_t S_addr;
  } S_un;

  S_un.S_un_w.s_w1 = s_w1;
  S_un.S_un_w.s_w2 = s_w2;
  st->s_addr = S_un.S_addr;
}
static inline void INADDR_GET_SUN_SUNW(struct in_addr *st, uint16_t *s_w1, uint16_t *s_w2) {
  union {
    struct {
      uint8_t s_b1, s_b2, s_b3, s_b4;
    } S_un_b;
    struct {
      uint16_t s_w1, s_w2;
    } S_un_w;
    uint32_t S_addr;
  } S_un;

  S_un.S_addr = st->s_addr;
  *s_w1 = S_un.S_un_w.s_w1;
  *s_w2 = S_un.S_un_w.s_w2;
}
static inline void INADDR_SET_SUN_SUNB(struct in_addr *st, uint8_t s_b1, uint8_t s_b2, uint8_t s_b3,
                                uint8_t s_b4) {
  union {
    struct {
      uint8_t s_b1, s_b2, s_b3, s_b4;
    } S_un_b;
    struct {
      uint16_t s_w1, s_w2;
    } S_un_w;
    uint32_t S_addr;
  } S_un;

  S_un.S_un_b.s_b1 = s_b1;
  S_un.S_un_b.s_b2 = s_b2;
  S_un.S_un_b.s_b3 = s_b3;
  S_un.S_un_b.s_b4 = s_b4;
  st->s_addr = S_un.S_addr;
}
static inline void INADDR_GET_SUN_SUNB(struct in_addr *st, uint8_t *s_b1, uint8_t *s_b2, uint8_t *s_b3,
                                uint8_t *s_b4) {
  union {
    struct {
      uint8_t s_b1, s_b2, s_b3, s_b4;
    } S_un_b;
    struct {
      uint16_t s_w1, s_w2;
    } S_un_w;
    uint32_t S_addr;
  } S_un;

  S_un.S_addr = st->s_addr;
  *s_b1 = S_un.S_un_b.s_b1;
  *s_b2 = S_un.S_un_b.s_b2;
  *s_b3 = S_un.S_un_b.s_b3;
  *s_b4 = S_un.S_un_b.s_b4;
}
#endif // OS

#define NWT_UNRELIABLE 1
#define NWT_RELIABLE 2

// This is the max size of a packet - DO NOT INCREASE THIS NUMBER ABOVE 512!
#define MAX_PACKET_SIZE 512
#if 1 // ndef DEMO
#define DEFAULT_GAME_PORT D3_DEFAULT_PORT
#else
#define DEFAULT_GAME_PORT 6250
#endif
// Network flags
#define NF_CHECKSUM 1
#define NF_NOSEQINC 2

enum network_protocol : uint32_t
{
  NP_NONE,
  NP_TCP,
  NP_IPX,
  NP_DIRECTPLAY
};

struct network_address {
  uint8_t address[6];
  uint16_t port;
  uint8_t net_id[4];
  network_protocol connection_type; // IPX, IP, modem, etc.
};

extern BOOL DP_active;
extern BOOL TCP_active;
extern BOOL IPX_active;

// create a new non-blocking socket
int make_nonblocking(SOCKET sock);

// Get the info from RAS
uint32_t psnet_ras_status();

// function to shutdown and close the given socket.  It takes a couple of things into consideration
// when closing, such as possibly reiniting reliable sockets if they are closed here.
void nw_CloseSocket(SOCKET *sockp);

// Inits the sockets layer to activity
void nw_InitNetworking(int iReadBufSizeOverride = -1);

// called by psnet_init to initialize the listen socket used by a host/server
int nw_InitReliableSocket();

// function which checks the Listen_socket for possibly incoming requests to be connected.
// returns 0 on error or nothing waiting.  1 if we should try to accept
int nw_CheckListenSocket(network_address *from_addr);

// Inits the sockets that the application will be using
void nw_InitSockets(uint16_t port);

// Connects a client to a server
void nw_ConnectToServer(SOCKET *socket, network_address *server_addr);

// Returns internet address format from string address format...ie "204.243.217.14"
// turns into 1414829242
uint32_t nw_GetHostAddressFromNumbers(char *str);

// Fills in the string with the string address from the internet address
void nw_GetNumbersFromHostAddress(network_address *address, char *str);

// returns the ip address of this computer
uint32_t nw_GetThisIP();

// function which checks the Listen_socket for possibly incoming requests to be connected.
// returns 0 on error or nothing waiting.  1 if we should try to accept
int nw_CheckListenSocket(network_address *from_addr);

// Calculates a unique uint16_t checksum for a stream of data
uint16_t nw_CalculateChecksum(void *vptr, int len);

// Sends data on an unreliable socket
int nw_Send(network_address *who_to, void *data, int len, int flags);

// nw_ReceiveFromSocket will get data out of the socket and stuff it into the packet_buffers
// nw_Receive now calls this function, then determines which of the packet buffers
// to package up and use
void nw_ReceiveFromSocket();

// routine to "free" a packet buffer
void nw_FreePacket(int id);

// nw_Recieve will call the above function to read data out of the socket.  It will then determine
// which of the buffers we should use and pass to the routine which called us
int nw_Receive(void *data, network_address *from_addr);

// nw_SendReliable sends the given data through the given reliable socket.
int nw_SendReliable(uint32_t socketid, uint8_t *data, int length, bool urgent = false);

// function which reads data off of a reliable socket.  recv() should read the totaly amount of data
// available I believe.  (i.e. we shouldn't read only part of a message with one call....I may be wrong
// and this may be a source of bugs).
int nw_ReceiveReliable(SOCKET socket, uint8_t *buffer, int max_len);

// Returns the current protocol in use
int nw_GetProtocolType();

// Copies my address into the passed argument
void nw_GetMyAddress(network_address *addr);

// Sends a packet to the game tracker
int nw_SendGameTrackerPacker(void *packet);

// Checks for an incoming game tracker packet.
int nw_ReceiveGameTracker(void *packet);

// Send a packet to the pilot tracker
int nw_SendPilotTrackerPacket(void *packet);

// Checks for an incoming pilot tracker packet.
int nw_ReceivePilotTracker(void *packet);

int nw_PingCompare(const void *arg1, const void *arg2);

// initialize the buffering system
void nw_psnet_buffer_init();

// buffer a packet (maintain order!)
void nw_psnet_buffer_packet(uint8_t *data, int length, network_address *from);

// get the index of the next packet in order!
int nw_psnet_buffer_get_next(uint8_t *data, int *length, network_address *from);

// get the index of the next packet in order!
int nw_psnet_buffer_get_next_by_packet_id(uint8_t *data, int *length, uint32_t packet_id);

// This is all the reliable UDP stuff...
#define MAXNETBUFFERS                                                                                                  \
  150                    // Maximum network buffers (For between network and upper level functions, which is
                         // required in case of out of order packets
#define NETRETRYTIME .75 // Time after sending before we resend
#define MIN_NET_RETRYTIME .2
#define NETTIMEOUT 300        // Time after receiving the last packet before we drop that user
#define NETHEARTBEATTIME 10   // How often to send a heartbeat
#define MAXRELIABLESOCKETS 40 // Max reliable sockets to open at once...
#define NETBUFFERSIZE 600     // Max size of a network packet

// Network Types
#define RNT_ACK 1        // ACK Packet
#define RNT_DATA 2       // Data Packet
#define RNT_DATA_COMP 3  // Compressed Data Packet
#define RNT_REQ_CONN 4   // Requesting a connection
#define RNT_DISCONNECT 5 // Disconnecting a connection
#define RNT_HEARTBEAT 6  // Heartbeat -- send every NETHEARTBEATTIME
#define RNT_I_AM_HERE 7

// Reliable socket states
#define RNF_UNUSED 0       // Completely clean socket..
#define RNF_CONNECTED 1    // Connected and running fine
#define RNF_BROKEN 2       // Broken - disconnected abnormally
#define RNF_DISCONNECTED 3 // Disconnected cleanly
#define RNF_CONNECTING 4   // We received the connecting message, but haven't told the game yet.
#define RNF_LIMBO 5        // between connecting and connected

void nw_SendReliableAck(SOCKADDR *raddr, uint32_t sig, network_protocol link_type, float time_sent);
void nw_WorkReliable(uint8_t *data, int len, network_address *naddr);
int nw_Compress(void *srcdata, void *destdata, int count);
int nw_Uncompress(void *compdata, void *uncompdata, int count);

#define NW_AGHBN_CANCEL 1
#define NW_AGHBN_LOOKUP 2
#define NW_AGHBN_READ 3

struct async_dns_lookup {
  uint32_t ip; // resolved host. Write only to worker thread.
  char *host;      // host name to resolve. read only to worker thread
  bool done;       // write only to the worker thread. Signals that the operation is complete
  bool error;      // write only to worker thread. Thread sets this if the name doesn't resolve
  bool abort;      // read only to worker thread. If this is set, don't fill in the struct.

  // rcg06212000 added to let us join the thread at completion...
#ifdef __LINUX__
  SDL_Thread *threadId;
#endif
};

#ifdef WIN32
#define CDECLCALL __cdecl
#else
#define CDECLCALL
#endif
#ifdef __LINUX__
// rcg06192000 used to return void *.
int CDECLCALL gethostbynameworker(void *parm);
#else
void CDECLCALL gethostbynameworker(void *parm);
#endif

int nw_Asyncgethostbyname(uint32_t *ip, int command, char *hostname);
int nw_ReccomendPPS();
void nw_DoNetworkIdle(void);

typedef void *(*NetworkReceiveCallback)(uint8_t *data, int len, network_address *from);
int nw_RegisterCallback(NetworkReceiveCallback nfp, uint8_t id);
NetworkReceiveCallback nw_UnRegisterCallback(uint8_t id);
int nw_SendWithID(uint8_t id, uint8_t *data, int len, network_address *who_to);
int nw_DoReceiveCallbacks(void);
void nw_HandleConnectResponse(uint8_t *data, int len, network_address *server_addr);
int nw_RegisterCallback(NetworkReceiveCallback nfp, uint8_t id);
void nw_HandleUnreliableData(uint8_t *data, int len, network_address *from_addr);
void nw_ReliableResend(void);
int nw_CheckReliableSocket(int socknum);

struct tNetworkStatus {
  // TCP/IP Status lines
  int udp_total_packets_sent; // total number of packets sent out on the network (unreliable)
  int udp_total_packets_rec;  // total number of packets recieved on the network (unrealiable)
  int udp_total_bytes_sent;   // total number of bytes sent (unreliable)
  int udp_total_bytes_rec;    // total number of bytes recieved (unreliable)

  int tcp_total_packets_sent;   // total number of packets sent out on the network (reliable)
  int tcp_total_packets_rec;    // total number of packets recieved on the network (reliable)
  int tcp_total_bytes_sent;     // total number of bytes sent (reliable)
  int tcp_total_bytes_rec;      // total number of bytes recieved (reliable)
  int tcp_total_packets_resent; // total number of packets resent (reliable)
  int tcp_total_bytes_resent;   // total number of bytes resent (reliable)

  // IPX Status lines
  int ipx_total_packets_sent; // total number of packets sent out on the network (unreliable)
  int ipx_total_packets_rec;  // total number of packets recieved on the network (unrealiable)
  int ipx_total_bytes_sent;   // total number of bytes sent (unreliable)
  int ipx_total_bytes_rec;    // total number of bytes recieved (unreliable)

  int spx_total_packets_sent;   // total number of packets sent out on the network (reliable)
  int spx_total_packets_rec;    // total number of packets recieved on the network (reliable)
  int spx_total_bytes_sent;     // total number of bytes sent (reliable)
  int spx_total_bytes_rec;      // total number of bytes recieved (reliable)
  int spx_total_packets_resent; // total number of packets resent (reliable)
  int spx_total_bytes_resent;   // total number of bytes resent (reliable)
};               // network status information

// fills in the buffer with network stats
// pass NULL to reset the stats
void nw_GetNetworkStats(tNetworkStatus *stats);

#endif
