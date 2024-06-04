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
 * $Logfile: /DescentIII/Main/mtclient/mtpilottrack.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:58:40 $
 * $Author: kevinb $
 *
 * Pilot tracker client header
 *
 * $Log: not supported by cvs2svn $
 *
 * 13    4/20/99 8:57p Jeff
 * compile for Linux
 *
 * 12    4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 11    4/07/99 9:15a Kevin
 * Changed PXO server addresses for release builds
 *
 * 10    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 9     2/16/99 12:36a Kevin
 * Fixes for release builds of OEM V3 and KAtmai
 *
 * 8     2/03/99 6:14p Kevin
 * OEM changes
 *
 * 7     12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 6     10/30/98 11:25a Kevin
 * Message of the day for PXO
 *
 * 5     10/09/98 2:56p Kevin
 * Changed IP addresses for PXO demo
 *
 * 4     10/01/98 11:37a Kevin
 * UI fixes and stuff
 *
 * 3     9/03/98 11:12a Kevin
 * Fixed bug in #define
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/25/98 4:12p Kevin
 *
 * 11    5/14/98 6:08p Kevin
 * fixed encryption bug
 *
 * 10    5/14/98 5:19p Kevin
 * Encrypted pilot data
 *
 * 9     5/13/98 4:06p Kevin
 * Added more mastertracker info
 *
 * 8     5/12/98 5:12p Kevin
 * added virgin_pilot field
 *
 * 7     5/12/98 5:10p Kevin
 * added lateral and rotational thrust
 *
 * 6     5/07/98 9:47a Kevin
 * Made pilot reading more robust
 *
 * 5     5/04/98 12:53p Kevin
 * Fixed mastertracker resend stuff
 *
 * 4     5/04/98 10:56a Kevin
 * Mastertracker fixes/enhancements
 *
 * 3     4/30/98 3:50p Kevin
 * Mastertracker pilot stats
 *
 * 2     4/27/98 7:12p Kevin
 * Mastertracker pilot tracker
 *
 * 1     4/27/98 5:27p Kevin
 * Initial version
 *
 * $NoKeywords: $
 */

#ifndef _PILOT_TRACKER_HEADER
#define _PILOT_TRACKER_HEADER
// Pilot tracker client header

#ifdef WIN32
#pragma pack(push, r_udp)
#endif
#pragma pack(1)

// Definitions
#define STATE_IDLE 0
#define STATE_SENDING_PILOT 1
#define STATE_READING_PILOT 2
#define STATE_RECEIVED_PILOT 3
#define STATE_WROTE_PILOT 4
#define STATE_TIMED_OUT 5
#define STATE_PILOT_NOT_FOUND 6
#define STATE_WRITE_PILOT_FAILED 7

#define REGPORT 2092                // The UDP port
#define PILOTTRACKERNAME "tracker.pxo.nottheeye.com"

#define PILOT_REQ_TIMEOUT 30.000
#define PILOT_REQ_RESEND_TIME 2.0

#define MAX_NET_RETRIES 30
#define NET_ACK_TIMEOUT 1.5

// This is for type
#define UNT_CONTROL 0
#define UNT_NEW_ID_REQUEST 1
#define UNT_VALIDAT_ID_REQUEST 2
#define UNT_LOOKUP_ID_REQUEST 3
#define UNT_UPDATE_ID_REQUEST 4
#define UNT_MOTD_REQUEST 5
#define UNT_MOTD_RESPONSE 6
#define UNT_PILOT_DATA_READ 7      // Request from the game for pilot info
#define UNT_PILOT_DATA_RESPONSE 8  // Mastertracker's response to a read request (has pilot data in this packet)
#define UNT_PILOT_DATA_WRITE 9     // Request from the server to write a user record
#define UNT_PILOT_WRITE_FAILED 10  // Server didn't update the pilots record for some reason
#define UNT_PILOT_WRITE_SUCCESS 11 // Server updated the pilots record
#define UNT_PILOT_READ_FAILED 12   // Couldn't find the record
#define UNT_LOGIN_AUTH_REQUEST 13  // Request login authentication by login/password only (returns tracker id)
#define UNT_LOGIN_NO_AUTH 14       // Couldn't login this user (code has reason)
#define UNT_LOGIN_AUTHENTICATED 15 // User was authenticated (data has sz string with tracker id)
#define UNT_TRACKER_VERSION_REQ 16 // Request the latest MT version (xcode has game type) code has present version
#define UNT_TRACKER_VERSION_RSP                                                                                        \
  17 // Response for the latest MT version (xcode has game type) code has version data has null term string with url for
     // dll to download

// This is for code
#define CMD_NEW_USER_ACK 1
#define CMD_NEW_USER_NAK 2
#define CMD_VALIDATED_USER_ACK 3
#define CMD_UPDATED_USER_ACK 4
#define CMD_CLIENT_RECEIVED 5
#define CMD_FIND_USER_NAK 6
#define CMD_FIND_USER_ACK 7
#define CMD_UPDATED_USER_NAK 8
#define CMD_VALIDATED_USER_NAK 9
// Game designators for UNT_PILOT_DATA_REQUEST and UNT_PILOT_DATA_RESPONSE
#define CMD_GAME_FREESPACE 10
#define CMD_GAME_DESCENT3 11

// This is for xcode
#define REG_NAK_EMAIL 0      // failed to register the guy because of an invalid email address
#define REG_NAK_LOGIN 1      // failed to register the guy because an existing login exists
#define REG_NAK_ERROR 2      // failed to register because of an error on the tracker
#define REG_NAK_STRINGS 3    // failed to validate because of invalid password/login match
#define REG_NAK_UNKNOWN 4    // failed to validate because the player is unknown
#define REG_NAK_UPDATE_PL 5  // update info failed because login/passwd were not correct
#define REG_NAK_UPDATE_GEN 6 // update info failed in general (tracker problem)
#define REG_NAK_UPDATE_LOG 7 // update failed because login not found
#define REG_ACK_NEW_ID 8     // New id created, just used for return code, not net packets.

#define MAX_UDP_DATA_LENGH 500
#define PACKED_HEADER_ONLY_SIZE (sizeof(udp_packet_header) - MAX_UDP_DATA_LENGH)
// sizeof(update_id_request)	//The largest packet

// data could be one of the following:

// type == UNT_NEW_ID_REQUEST
// Respond with ACK
struct new_id_request {
  char first_name[REAL_NAME_LEN]; // Real Name
  char last_name[REAL_NAME_LEN];  // Real Name
  char login[LOGIN_LEN];          // Login id
  char password[PASSWORD_LEN];    // password
  char email[EMAIL_LEN];          // Email Address
  uint8_t showemail;              // 0==don't show 1 == show
  uint8_t showname;               // 0==don't show 1 == show
};

// type == UNT_VALIDAT_ID_REQUEST or UNT_LOOKUP_ID_REQUEST
struct validate_id_request {
  char login[LOGIN_LEN];           // Login id
  char password[PASSWORD_LEN];     // password
  char tracker_id[TRACKER_ID_LEN]; // Tracker ID
};

// type == UNT_UPDATE_ID_REQUEST
struct update_id_request {
  char old_login[LOGIN_LEN];       // Login before it's changed.
  char old_password[PASSWORD_LEN]; // Password before it's changed
  char tracker_id[TRACKER_ID_LEN]; // Tracker ID (not sure if we need it for updating, but maybe)
  char first_name[REAL_NAME_LEN];  // Real Name
  char last_name[REAL_NAME_LEN];   // Real Name
  char login[LOGIN_LEN];           // Login id (new)
  char password[PASSWORD_LEN];     // password (new)
  char email[EMAIL_LEN];           // Email Address (new)
  uint8_t showemail;               // 0==don't show 1 == show
  uint8_t showname;                // 0==don't show 1 == show
};

struct pilot_request {
  char pilot_name[PILOT_NAME_LEN]; // Login id
  char tracker_id[TRACKER_ID_LEN]; // Tracker ID
};

struct udp_packet_header {
  uint8_t type;      // Type of request
  uint16_t len;      // Length of total packet, including this header
  uint32_t code;     // For control messages
  uint16_t xcode;    // For control/NAK messages and for sigs.
  uint32_t sig;      // To identify unique return ACKs
  uint32_t security; // Just a random value, we store the last value used in the user record
                     // So we don't process the same request twice.
  uint8_t data[MAX_UDP_DATA_LENGH];
};

#ifdef WIN32
// Queue -- We need a queue to put responses in, so after a certain amount of time
// If we don't get an ACK back from the client, we resend the packet, until eventually
// We give up.

struct net_reg_queue {
  char login[LOGIN_LEN];      // Login id
  uint32_t time_last_sent;    // Time in milliseconds since we last sent this packet
  int retries;                // Number of times this has been sent
  udp_packet_header packet;   // Packet containing the actual data to resend, etc.
  struct net_reg_queue *next; // Pointer to next item in the list
  SOCKADDR netaddr;
  uint32_t sig; // Signature to be used by the client to ACK our response.
};
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME SPECIFIC structures

/*
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
        uint8_t virgin_pilot;	//This pilot was just created if TRUE
        uint32_t lateral_thrust;
        uint32_t rotational_thrust;
        uint32_t sliding_pct;	//Percentage of the time you were sliding
        uint32_t checksum;			//This value needs to be equal to whatever the checksum is once the
packet is decoded uint32_t pad;			//just to provide room for out 4 byte encryption boundry only needed on
the client side for now
};
*/

//
// -------------------------------------------------------------------------------------------------------------

extern int Motd_version;

/**
 * Get MOTD from remote. Call with NULL to poll. Call with valid pointer and maxlen to get the message of the day.
 * @param szmotd
 * @param maxlen
 * @return
 * -3 - Error, called with NULL, but no request is waiting;
 * -2 - Error, already waiting on message of the day (hasn't timed out yet);
 * -1 - Timeout waiting for message of the day;
 * 0 - Waiting for data;
 * 1 - Data received.
 */
int GetD3MOTD(char *szmotd, int maxlen);

/**
 * Cancel previous MOTD request
 * @return
 * -3 Error, called with NULL, but no request is waiting
 * 2 Request successfully cancelled
 */
int GetD3MOTDCancel();

// Function prototypes
int InitPilotTrackerClient();

int SendD3PilotData(vmt_descent3_struct *d3_pilot);
int GetD3PilotData(vmt_descent3_struct *d3_pilot, char *pilot_name, char *tracker_id);

/**
 * Cancel previous GetD3PilotData() wait
 * @return
 * -3: Error - Called GetD3PilotData with NULL, but no request is waiting;
 * 2: Request successfully canceled;
 */
int GetD3PilotDataCancel();
void PollPTrackNet();
// int ValidateUser(validate_id_request *valid_id);
int ValidateUser(validate_id_request *valid_id, char *trackerid);
extern int MTAVersionCheck(uint32_t oldver, char *URL);

#ifdef WIN32
#pragma pack(pop, r_udp)
#else
#pragma pack()
#endif
#endif
