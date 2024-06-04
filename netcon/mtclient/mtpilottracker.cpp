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
 */

/*
 * $Logfile: /DescentIII/Main/mtclient/mtpilottracker.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:58:40 $
 * $Author: kevinb $
 *
 * Pilot tracker client code
 *
 * $Log: not supported by cvs2svn $
 *
 * 15    10/28/99 3:13p Kevin
 * fixed major badness with byte ordering 'fix'
 *
 * 14    9/02/99 3:16p Kevin
 * Macintosh byte ordering fixes
 *
 * 13    9/01/99 5:24p Kevin
 * Macintosh byte ordering problems
 *
 * 12    7/21/99 9:11a Kevin
 * bandwidth reduction act #1
 *
 * 11    4/21/99 11:15a Kevin
 * sectret code to tell the differences between oem, demo and retail
 * builds on the tracker
 *
 * 10    4/19/99 8:36p Jeff
 * Compile under Linux
 *
 * 9     3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 8     1/11/99 6:02p Kevin
 * Fixed warning
 *
 * 7     12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 6     11/03/98 9:27a Kevin
 * Added PXO message of the day
 *
 * 5     10/30/98 11:25a Kevin
 * Message of the day for PXO
 *
 * 4     8/31/98 10:14a Kevin
 * Misc. multi-UI fixes
 *
 * 3     8/25/98 6:33p Kevin
 * PXO screens
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/25/98 4:12p Kevin
 *
 * 10    5/14/98 6:08p Kevin
 * fixed encryption bug
 *
 * 9     5/14/98 5:19p Kevin
 * Encrypted pilot data
 *
 * 8     5/07/98 9:47a Kevin
 * Made pilot reading more robust
 *
 * 7     5/04/98 1:22p Kevin
 * Mastertracker
 *
 * 6     5/04/98 12:53p Kevin
 * Fixed mastertracker resend stuff
 *
 * 5     5/01/98 12:28p Kevin
 * Added new user registration button for MT
 *
 * 4     4/30/98 3:50p Kevin
 * Mastertracker pilot stats
 *
 * 3     4/28/98 12:51p Kevin
 * Master tracker login
 *
 * 2     4/27/98 7:12p Kevin
 * Mastertracker pilot tracker
 *
 * 1     4/27/98 5:29p Kevin
 * Initial Version
 *
 * $NoKeywords: $
 */

#ifdef WIN32
#include <windows.h>
#endif

#include <cstdlib>
#include <cstring>

#include "pstypes.h"
#include "networking.h"
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
#pragma pack(1)
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

#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)

typedef void (*Debug_ConsolePrintf_fp)(int n, const char *format, ...);
extern Debug_ConsolePrintf_fp DLLDebug_ConsolePrintf;

typedef float (*timer_GetTime_fp)();
extern timer_GetTime_fp DLLtimer_GetTime;

typedef void (*HandlePilotData_fp)(uint8_t *data, int len, network_address *from);

typedef int (*nw_RegisterCallback_fp)(HandlePilotData_fp, uint8_t id);
extern nw_RegisterCallback_fp DLLnw_RegisterCallback;

typedef int (*nw_DoReceiveCallbacks_fp)();
extern nw_DoReceiveCallbacks_fp DLLnw_DoReceiveCallbacks;

#define VALID_STATE_IDLE 1
#define VALID_STATE_WAITING 2
#define VALID_STATE_VALID 3
#define VALID_STATE_INVALID 4
#define VALID_STATE_TIMEOUT 5

#define VERSION_STATE_IDLE 1
#define VERSION_STATE_WAITING 2
#define VERSION_STATE_RECEIVED 3
#define VERSION_STATE_TIMEOUT 5

#define STATE_WAITING_MOTD 8
#define STATE_HAVE_MOTD 9

#define MAX_MOTDLEN 1000
// Variables

static int D3WriteState;
static int D3ReadState;
static float D3LastSent;
static float D3FirstSent;

static float D3LastSentWrite;
static float D3FirstSentWrite;

static udp_packet_header d3_pilot_req, d3_pilot_write, motd_req;
static pilot_request *d3_pr;
static vmt_descent3_struct *ReadD3Pilot;
static vmt_descent3_struct WriteD3Pilot;

static udp_packet_header PacketHeader, VersionPacketHeader;
static validate_id_request *ValidIDReq;

static int MOTDState;

static float MOTDFirstSent;
static float MOTDLastSent;

static char *Motdptr;
static uint32_t Motd_maxlen;

static int ValidState;

static float ValidFirstSent;
static float ValidLastSent;

static int VersionState;

static float VersionFirstSent;
static float VersionLastSent;
static char *VersionURL;

static uint32_t ValidSecurity;

static char *Psztracker_id;

static char ProccesingPilot[PILOT_NAME_LEN];

static void AckServer(uint32_t sig);
static void IdlePTrack();
static void HandlePilotData(uint8_t *data, int len, network_address *from);
static void xorcode(void *data, uint32_t len, uint32_t hash);
static void ValidIdle();
static void VersionIdle();

typedef int (*PollUI_fp)();
extern PollUI_fp DLLPollUI;

int InitPilotTrackerClient() {

  D3WriteState = STATE_IDLE;
  D3ReadState = STATE_IDLE;

  ReadD3Pilot = nullptr;
  ValidState = VALID_STATE_IDLE;

  VersionState = VERSION_STATE_IDLE;

  srand(DLLtimer_GetTime());
  ValidSecurity = (uint32_t)rand();
  // Build the request packet
  PacketHeader.type = UNT_LOGIN_AUTH_REQUEST; // UNT_VALIDAT_ID_REQUEST;
  PacketHeader.len = INTEL_SHORT(PACKED_HEADER_ONLY_SIZE + sizeof(validate_id_request));
  ValidIDReq = (validate_id_request *)&PacketHeader.data;

  d3_pr = (pilot_request *)&d3_pilot_req.data;

  DLLnw_RegisterCallback(HandlePilotData, PXO_NETID_USER_TRACKER);
  return 1;
}

// Returns:
//-3	Error -- Called with NULL, but no request is waiting
//-2	Error -- Already sending data (hasn't timed out yet)
//-1	Timeout trying to send pilot data
//  0	Sending
//  1	Data successfully sent

// Call with NULL to poll
// Call with valid pointer to a vmt_descent3_struct to initiate send
int SendD3PilotData(vmt_descent3_struct *d3_pilot) {
  // First check the network
  PollPTrackNet();

  if (d3_pilot == nullptr) {
    if (D3WriteState == STATE_IDLE) {
      return -3;
    }
    if (D3WriteState == STATE_SENDING_PILOT) {
      return 0;
    }
    if (D3WriteState == STATE_WROTE_PILOT) {
      // We wrote this pilot, and now we are about to inform the app, so back to idle
      D3WriteState = STATE_IDLE;
      return 1;
    }
    if (D3WriteState == STATE_TIMED_OUT) {
      // We gave up on sending this pilot, and now we are about to inform the app, so back to idle
      D3WriteState = STATE_IDLE;

      return -1;
    }
    if (D3WriteState == STATE_WRITE_PILOT_FAILED) {
      // The tracker said this dude couldn't be written
      D3WriteState = STATE_IDLE;

      return 3;
    }
  } else if (D3WriteState == STATE_IDLE) {
    // New request, send out the req, and go for it.

    D3WriteState = STATE_SENDING_PILOT;

    D3LastSentWrite = DLLtimer_GetTime();
    D3FirstSentWrite = DLLtimer_GetTime();

    d3_pilot_write.len = INTEL_SHORT(PACKED_HEADER_ONLY_SIZE + DESCENT3_BLOCK_SIZE);
    d3_pilot_write.type = UNT_PILOT_DATA_WRITE;
    d3_pilot_write.code = INTEL_INT(CMD_GAME_DESCENT3);
    d3_pilot_write.security = d3_pilot->security;

    d3_pilot->deaths = INTEL_INT(d3_pilot->deaths);
    d3_pilot->kills = INTEL_INT(d3_pilot->kills);
    d3_pilot->online_time = INTEL_INT(d3_pilot->online_time);
    d3_pilot->games_played = INTEL_INT(d3_pilot->games_played);
    d3_pilot->lateral_thrust = INTEL_INT(d3_pilot->lateral_thrust);
    d3_pilot->rank = INTEL_INT(d3_pilot->rank);
    d3_pilot->rotational_thrust = INTEL_INT(d3_pilot->rotational_thrust);
    d3_pilot->sliding_pct = INTEL_INT(d3_pilot->sliding_pct);
    d3_pilot->suicides = INTEL_INT(d3_pilot->suicides);

#if (!(defined(OEM) || defined(DEMO)))
    // This is the secret number we will use to determine if it's
    // a game where we want to update the player's rank or not.
    d3_pilot->lateral_thrust = INTEL_INT(0x142);
#endif
    memcpy(&d3_pilot_write.data, d3_pilot, DESCENT3_BLOCK_SIZE);

    return 0;
  }
  return -2;
}

// Returns:
//-3	Error -- Called with NULL, but no request is waiting
//-2	Error -- Already waiting on data (hasn't timed out yet)
//-1	Timeout waiting for pilot data
//  0	Waiting for data
//  1	Data received
//  2	Get Cancelled

// Call with NULL to poll
// Call with -1 to cancel wait
// Call with valid pointer to a vmt_descent3_struct to get a response
int GetD3PilotData(vmt_descent3_struct *d3_pilot, char *pilot_name, char *tracker_id) {
  // First check the network
  PollPTrackNet();

  if (d3_pilot == nullptr) {
    if (D3ReadState == STATE_IDLE) {
      return -3;
    }
    if (D3ReadState == STATE_READING_PILOT) {
      return 0;
    }
    if (D3ReadState == STATE_RECEIVED_PILOT) {
      // We got this pilot, and now we are about to inform the app, so back to idle
      D3ReadState = STATE_IDLE;
      ReadD3Pilot = nullptr;

      return 1;
    }
    if (D3ReadState == STATE_TIMED_OUT) {
      // We gave up on this pilot, and now we are about to inform the app, so back to idle
      D3ReadState = STATE_IDLE;
      ReadD3Pilot = nullptr;
      return -1;
    }
    if (D3ReadState == STATE_PILOT_NOT_FOUND) {
      // The tracker said this dude is not found.
      D3ReadState = STATE_IDLE;
      ReadD3Pilot = nullptr;
      return 3;
    }

  } else if (D3ReadState == STATE_IDLE) {
    // New request, send out the req, and go for it.

    D3ReadState = STATE_READING_PILOT;
    ReadD3Pilot = d3_pilot;
    D3LastSent = DLLtimer_GetTime();
    D3FirstSent = DLLtimer_GetTime(); // DLLtimer_GetTime();

    d3_pilot_req.len = INTEL_SHORT(PACKED_HEADER_ONLY_SIZE + sizeof(pilot_request));
    d3_pilot_req.type = UNT_PILOT_DATA_READ;
    d3_pilot_req.code = INTEL_INT(CMD_GAME_DESCENT3);
    strcpy(d3_pr->pilot_name, pilot_name);
    strcpy(d3_pr->tracker_id, tracker_id);
    strcpy(ProccesingPilot, pilot_name);
    return 0;
  }
  return -2;
}

int GetD3PilotDataCancel() {
  // First check the network
  PollPTrackNet();

  if (D3ReadState == STATE_IDLE) {
    return -3;
  } else {
    // Cancel this baby
    D3ReadState = STATE_IDLE;
    ReadD3Pilot = nullptr;
    return 2;
  }
}

// Send an ACK to the server
void AckServer(uint32_t sig) {
  udp_packet_header ack_pack;

  ack_pack.type = UNT_CONTROL;
  ack_pack.sig = sig;
  ack_pack.code = INTEL_INT(CMD_CLIENT_RECEIVED);
  ack_pack.len = INTEL_SHORT(PACKED_HEADER_ONLY_SIZE);

  SendPilotTrackerPacket(&ack_pack);
  // sendto(pilotsock,(char *)&ack_pack,PACKED_HEADER_ONLY_SIZE,0,(SOCKADDR *)&ptrackaddr,sizeof(SOCKADDR_IN));
}

void IdlePTrack() {
  // socket
  if (D3ReadState == STATE_READING_PILOT) {
    if ((DLLtimer_GetTime() - D3FirstSent) >= PILOT_REQ_TIMEOUT) {
      D3ReadState = STATE_TIMED_OUT;

    } else if ((DLLtimer_GetTime() - D3LastSent) >= PILOT_REQ_RESEND_TIME) {
      // Send 'da packet
      // sendto(pilotsock,(char *)&d3_pilot_req,d3_pilot_req.len,0,(SOCKADDR *)&ptrackaddr,sizeof(SOCKADDR_IN));
      SendPilotTrackerPacket(&d3_pilot_req);
      D3LastSent = DLLtimer_GetTime();
    }
  }

  if (D3WriteState == STATE_SENDING_PILOT) {
    if ((DLLtimer_GetTime() - D3FirstSentWrite) >= PILOT_REQ_TIMEOUT) {
      D3WriteState = STATE_TIMED_OUT;

    } else if ((DLLtimer_GetTime() - D3LastSentWrite) >= PILOT_REQ_RESEND_TIME) {
      // Send 'da packet
      SendPilotTrackerPacket(&d3_pilot_write);
      // sendto(pilotsock,(char *)&d3_pilot_write,d3_pilot_write.len,0,(SOCKADDR *)&ptrackaddr,sizeof(SOCKADDR_IN));
      D3LastSentWrite = DLLtimer_GetTime();
    }
  }
  if (MOTDState == STATE_WAITING_MOTD) {
    if ((DLLtimer_GetTime() - MOTDFirstSent) >= PILOT_REQ_TIMEOUT) {
      MOTDState = STATE_TIMED_OUT;

    } else if ((DLLtimer_GetTime() - MOTDLastSent) >= PILOT_REQ_RESEND_TIME) {
      // Send 'da packet
      SendPilotTrackerPacket(&motd_req);
      MOTDLastSent = DLLtimer_GetTime();
    }
  }
}

void PollPTrackNet() {
  IdlePTrack();
  DLLnw_DoReceiveCallbacks();
}

int Motd_version = 0;

void HandlePilotData(uint8_t *data, int len, network_address *from) {
  udp_packet_header inpacket;
  vmt_descent3_struct *d3_pilot;
  memcpy(&inpacket, data, sizeof(inpacket));
  inpacket.len = INTEL_SHORT(inpacket.len) - 1;
  if (len) {
    switch (inpacket.type) {
    case UNT_MOTD_RESPONSE:
      if (MOTDState == STATE_WAITING_MOTD) {
        if (Motdptr) {
          if ((inpacket.len - PACKED_HEADER_ONLY_SIZE) > Motd_maxlen)
            inpacket.len = PACKED_HEADER_ONLY_SIZE + Motd_maxlen - 1;
          strncpy(Motdptr, (char *)inpacket.data, inpacket.len - PACKED_HEADER_ONLY_SIZE);
          Motdptr[inpacket.len - PACKED_HEADER_ONLY_SIZE] = '\0';
        }
        MOTDState = STATE_HAVE_MOTD;
      }
      break;
    case UNT_PILOT_DATA_RESPONSE:
      if (inpacket.code == CMD_GAME_DESCENT3) {
        if (D3ReadState == STATE_READING_PILOT) {
          d3_pilot = (vmt_descent3_struct *)&inpacket.data;
          xorcode(d3_pilot, DESCENT3_BLOCK_SIZE, inpacket.security);
          if (stricmp(ProccesingPilot, d3_pilot->pilot_name) == 0) {
            // Copy the data
            memcpy(ReadD3Pilot, &inpacket.data, DESCENT3_BLOCK_SIZE);
            // Set the state
            D3ReadState = STATE_RECEIVED_PILOT;
          }
        }
      }
      break;
    case UNT_PILOT_READ_FAILED:
      if (inpacket.code == CMD_GAME_DESCENT3) {
        if (D3ReadState == STATE_READING_PILOT) {
          D3ReadState = STATE_PILOT_NOT_FOUND;
        }
      }
      break;
    case UNT_PILOT_WRITE_SUCCESS:
      if (inpacket.code == CMD_GAME_DESCENT3) {
        if (D3WriteState == STATE_SENDING_PILOT) {
          D3WriteState = STATE_WROTE_PILOT;
        }
      }
      break;
    case UNT_PILOT_WRITE_FAILED:
      if (inpacket.code == CMD_GAME_DESCENT3) {
        if (D3WriteState == STATE_SENDING_PILOT) {
          D3WriteState = STATE_WRITE_PILOT_FAILED;
        }
      }
      break;
    case UNT_CONTROL:
      switch (INTEL_INT(inpacket.code)) {
      case CMD_VALIDATED_USER_ACK:
        if (ValidState == VALID_STATE_WAITING) {
          ValidState = VALID_STATE_VALID;
        }
        break;
      case CMD_VALIDATED_USER_NAK:
        if (ValidState == VALID_STATE_WAITING) {
          ValidState = VALID_STATE_INVALID;
        }
        break;
      }
    case UNT_LOGIN_NO_AUTH:
      if (ValidState == VALID_STATE_WAITING) {
        ValidState = VALID_STATE_INVALID;
      }
      break;
    case UNT_LOGIN_AUTHENTICATED:
      if (ValidState == VALID_STATE_WAITING) {
        ValidState = VALID_STATE_VALID;
        strcpy(Psztracker_id, (const char *)&inpacket.data);
        // memcpy(&Motd_version,inpacket.data[strlen(Psztracker_id)+1],sizeof(int));
        Motd_version = inpacket.xcode;
      }
      break;
    case UNT_TRACKER_VERSION_RSP:
      if (VersionState == VERSION_STATE_WAITING) {
        // This is a version response possibly with the URL to download a file at the end.
        strcpy(VersionURL, (const char *)&inpacket.data);
        VersionState = VERSION_STATE_RECEIVED;
      }
      break;
    default:
      break;
    }
  }
  AckServer(inpacket.sig);
}

// Call with a valid struct to validate a user
// Call with NULL to poll

// Return codes:
//  -3	Still waiting (returned if we were waiting for a tracker response and ValidateUser was called with a non-NULL
//  value -2 Timeout waiting for tracker to respond -1	User invalid
//   0	Still waiting for response from tracker/Idle
//   1	User valid
int ValidateUser(validate_id_request *valid_id, char *trackerid) {
  ValidIdle();
  if (valid_id == NULL) {
    switch (ValidState) {
    case VALID_STATE_IDLE:
      return 0;
      break;
    case VALID_STATE_WAITING:
      return 0;
      break;
    case VALID_STATE_VALID:
      ValidState = VALID_STATE_IDLE;
      return 1;
      break;
    case VALID_STATE_INVALID:
      ValidState = VALID_STATE_IDLE;
      return -1;
    case VALID_STATE_TIMEOUT:
      ValidState = VALID_STATE_IDLE;
      return -2;
    }
    return 0;
  } else {
    // if(ValidState==VALID_STATE_IDLE)
    {
      /*
      //First, flush the input buffer for the socket
      uint32_t bytesin;
      udp_packet_header inpacket;
      do
      {
              bytesin = ReceivePilotTracker(&inpacket);
      }while(bytesin && (bytesin!=-1));
      */
      Psztracker_id = trackerid;
      ValidSecurity = (uint32_t)rand();
      PacketHeader.security = ValidSecurity;
      // strcpy(ValidIDReq->tracker_id,valid_id->tracker_id);
      strcpy(ValidIDReq->login, valid_id->login);
      strcpy(ValidIDReq->password, valid_id->password);
      SendPilotTrackerPacket(&PacketHeader);
      ValidState = VALID_STATE_WAITING;
      ValidFirstSent = DLLtimer_GetTime();
      ValidLastSent = DLLtimer_GetTime();
      return 0;
    }
    //	else
    //	{
    //		return -3;
    //	}
  }
}

void ValidIdle() {
  PollPTrackNet();
  if (ValidState == VALID_STATE_WAITING) {
    if ((DLLtimer_GetTime() - ValidFirstSent) >= PILOT_REQ_TIMEOUT) {
      ValidState = VALID_STATE_TIMEOUT;

    } else if ((DLLtimer_GetTime() - ValidLastSent) >= PILOT_REQ_RESEND_TIME) {
      // Send 'da packet
      SendPilotTrackerPacket(&PacketHeader);
      ValidLastSent = DLLtimer_GetTime();
    }
  }
}
// This code will modify 4 bytes at a time, so make sure to pad it!!!
void xorcode(void *data, uint32_t len, uint32_t hash) {
  return;
  uint32_t i = 0;
  uint32_t *src = (uint32_t *)&data;

  while (i < len) {
    *src = *src ^ hash;
    src++;
    i += sizeof(uint32_t);
  }
}

void VersionIdle() {
  PollPTrackNet();
  if (VersionState == VERSION_STATE_WAITING) {
    if ((DLLtimer_GetTime() - VersionFirstSent) >= PILOT_REQ_TIMEOUT) {
      VersionState = VERSION_STATE_TIMEOUT;

    } else if ((DLLtimer_GetTime() - VersionLastSent) >= PILOT_REQ_RESEND_TIME) {
      // Send 'da packet
      SendPilotTrackerPacket(&VersionPacketHeader);
      VersionLastSent = DLLtimer_GetTime();
    }
  }
}

// Return codes:
//  -3	Still waiting (returned if we were waiting for a tracker response and VersionCheck was called with a non-NULL
//  value -2 Timeout waiting for tracker to respond
//   0	Still waiting for response from tracker/Idle
//   1	Version received (URL[0] will not be NULL if we have the URL which means we need a newer version)
// Call once with the real version, then poll with the version set to 0 URL is a pointer to a char buff(max size == 200)
// that will be filled if/when we get a URL response
int MTAVersionCheck(uint32_t oldver, char *URL) {

  int res = DLLPollUI();
  if (res == 99) {
    VersionState = VERSION_STATE_TIMEOUT;
  }
  VersionIdle();
  if (oldver == 0) {
    switch (VersionState) {
    case VERSION_STATE_IDLE:
      return 0;
      break;
    case VERSION_STATE_WAITING:
      return 0;
      break;
    case VERSION_STATE_RECEIVED:
      VersionState = VERSION_STATE_IDLE;
      return 1;
    case VERSION_STATE_TIMEOUT:
      VersionState = VERSION_STATE_IDLE;
      return -2;
    }
    return 0;
  } else {
    if (VersionState == VERSION_STATE_IDLE) {
      /*
      //First, flush the input buffer for the socket
      uint32_t bytesin;
      udp_packet_header inpacket;
      do
      {
              bytesin = ReceivePilotTracker(&inpacket);
      }while(bytesin && (bytesin!=-1));
      */
      VersionURL = URL;
      VersionPacketHeader.len = INTEL_SHORT(PACKED_HEADER_ONLY_SIZE);
      VersionPacketHeader.type = UNT_TRACKER_VERSION_REQ;
      VersionPacketHeader.xcode = INTEL_SHORT(CMD_GAME_DESCENT3);
      VersionPacketHeader.code = INTEL_INT(oldver);

      SendPilotTrackerPacket(&VersionPacketHeader);
      VersionState = VERSION_STATE_WAITING;
      VersionFirstSent = DLLtimer_GetTime();
      VersionLastSent = DLLtimer_GetTime();
      return 0;
    } else {
      return -3;
    }
  }
}

int GetD3MOTD(char *szmotd, int maxlen) {
  // First check the network
  PollPTrackNet();

  if (szmotd == nullptr) {
    if (MOTDState == STATE_WAITING_MOTD) {
      return 0;
    }
    if (MOTDState == STATE_TIMED_OUT) {
      MOTDState = STATE_IDLE;
      return -1;
    }
    if (MOTDState == STATE_HAVE_MOTD) {
      MOTDState = STATE_IDLE;
      return 1;
    }
    return -3;
  } else if (MOTDState == STATE_IDLE) {
    // New request, send out the req, and go for it.

    MOTDState = STATE_WAITING_MOTD;
    Motdptr = szmotd;
    Motd_maxlen = maxlen;
    MOTDFirstSent = DLLtimer_GetTime();
    MOTDLastSent = DLLtimer_GetTime();

    motd_req.len = INTEL_SHORT(PACKED_HEADER_ONLY_SIZE);
    motd_req.type = UNT_MOTD_REQUEST;
    motd_req.code = INTEL_INT(CMD_GAME_DESCENT3);
    return 0;
  }
  return -2;
}

int GetD3MOTDCancel() {
  // First check the network
  PollPTrackNet();

  if (MOTDState == STATE_IDLE) {
    return -3;
  } else {
    // Cancel this baby
    MOTDState = STATE_IDLE;
    Motdptr = nullptr;
    ReadD3Pilot = nullptr;
    return 2;
  }
}
