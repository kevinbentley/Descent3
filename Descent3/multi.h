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

 * $Logfile: /DescentIII/Main/multi.h $
 * $Revision: 172 $
 * $Date: 7/09/01 2:06p $
 * $Author: Matt $
 *
 * Header for multiplayer
 *
 * $Log: /DescentIII/Main/multi.h $
 *
 * 172   7/09/01 2:06p Matt
 * Channged multiplayer version to 10
 *
 * 171   5/09/00 5:11p Jeff
 * fixed struct packing bug
 *
 * 170   4/19/00 5:35p Matt
 * Changed multiplayer version to 9
 *
 * 169   10/25/99 5:22p Jeff
 * upped multiplayer version for merc/1.3
 *
 * 168   10/16/99 8:45p Jeff
 * created multi functions to strip a player of his weapons and energy
 *
 * 167   10/01/99 1:39p Kevin
 * new MULTI_VERSION for demo (macintosh)
 *
 * 166   9/09/99 12:24p Kevin
 * Fixed a bug that was causing problems in the Mac version
 * (Game_is_master_tracker_game was defined as a uint8_t in the game, but an
 * int in the dll)
 *
 * 165   9/02/99 3:34p Jason
 * send secondary fire reliable in a C/S game
 *
 * 164   9/01/99 6:56p Jason
 * fixed guided missiles and timeout missiles so they work in multiplayer
 *
 * 163   9/01/99 4:12p Kevin
 * Byte ordering fixes for the macintosh
 *
 * 162   7/26/99 2:11p Kevin
 * 1.1 patch multiplayer version change
 *
 * 161   6/03/99 8:48a Kevin
 * fixes for new OEM version....
 *
 * 160   5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 159   5/20/99 4:54p Jason
 * added heartbeats to server
 *
 * 158   5/20/99 4:10p Jason
 * added heartbeat to multiplayer so clients wouldn't time out, also
 * various multiplayer fixes
 *
 * 157   5/19/99 5:39p Jason
 * made level failing work in coop
 *
 * 156   5/11/99 10:59a Kevin
 * Ship allow/dissalow works now!
 *
 * 155   5/03/99 2:36p Jason
 * change for multiplayer games
 *
 * 154   5/02/99 5:01p Kevin
 * changed MAX_RESPAWNS per Jason
 *
 * 153   4/29/99 11:46p Jason
 * added ability to set the next level in a multiplayer game
 *
 * 152   4/29/99 11:02p Jeff
 * added the ability for the server to set audio taunt delay time via
 * command line option and/or dedicated server console
 *
 * 151   4/28/99 2:28a Jeff
 * finished (hopefully) making guidebot multiplayer friendly
 *
 * 150   4/25/99 10:19p Matt
 * Fixed multiplayer and demo problems will killing an object from script,
 * and cleaned up the death code a bit in the process.
 *
 * 149   4/24/99 11:58p Kevin
 * Game info list (hit I in the pxo game list)
 *
 * 148   4/24/99 6:44p Jeff
 * added functions for theif so he can steal things other than weapons
 *
 * 147   4/17/99 4:24p Kevin
 * Changed multiplayer version number for Demo & regular
 *
 * 146   4/16/99 12:03a Jeff
 * removed #pragma's for Linux
 *
 * 145   4/06/99 6:24p Jason
 * various fixes for multiplayer
 *
 * 144   4/03/99 2:06p Kevin
 * Changed last file to audio taunt #4.
 *
 * 143   4/02/99 6:31p Jason
 * fixed multiplayer powerup/player start bugs
 *
 * 142   4/01/99 5:48p Kevin
 * Put in code to make it easy to add the guidebot to multiplayer (coop)
 * games
 *
 * 141   3/17/99 4:08p Kevin
 * Changed the way games appear and timeout in the game list.
 *
 * 140   3/11/99 6:30p Jeff
 * numerous fixes to demo system in multiplayer games (when
 * recording/playback a demo in a multiplayer game)
 *
 * 139   3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 138   2/25/99 11:01a Matt
 * Added new explosion system.
 *
 * 137   2/25/99 10:30a Jason
 * added nonvis generic/robot system
 *
 * 136   2/13/99 12:35a Jeff
 * fixed up packets to handle new inventory system (removed some compiler
 * warnings)
 *
 * 135   2/12/99 3:38p Jason
 * added client-side interpolation...its not fully debugged though.
 *
 * 134   2/09/99 6:52p Jeff
 * implemented 'typing inidcator' in multiplayer...players that are typing
 * messages have an icon on them
 *
 * 133   2/04/99 12:26p Jason
 * added spew that was better for multiplayer
 *
 * 132   2/03/99 12:15p Jason
 * added multiplayer vis optimizations
 *
 * 131   1/28/99 6:17p Jason
 * added markers
 *
 * 130   1/27/99 5:47p Jeff
 * audio taunts implemented!
 *
 * 129   1/22/99 4:06p Jeff
 * added hud messages that can be sent to just teammates or individual
 * people
 *
 * 128   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 127   1/13/99 2:53p Jason
 * added CONNECT_BAIL packet type
 *
 * 126   1/13/99 6:38a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 125   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 124   1/05/99 5:09p Jason
 * added permissable server networking (ala Quake/Unreal) to Descent3
 *
 * 123   1/05/99 11:52a Jason
 * added more msafe functionality
 *
 * 122   1/04/99 8:11p Jason
 * fixed packet loss tracking problem
 *
 * 121   12/31/98 7:36p Jeff
 * correctly hash type/ids for multisafe.  Added some new inline functions
 * to add/get type/id to a packet
 *
 * 120   12/28/98 2:22p Kevin
 * Initial mission downloading system
 *
 * 119   12/21/98 4:04p Jason
 * first pass at multisafe powerups
 *
 * 118   12/16/98 5:37p Jason
 * added new multisafe architecture
 *
 * 117   12/15/98 4:20p Jason
 * added triggers and door funtions to multisafe list
 *
 * 116   12/14/98 5:32p Jason
 * added multisafe functions
 *
 * 115   12/14/98 10:53a Jason
 * added bright player ships option
 *
 * 114   12/10/98 10:51a Jason
 * added autolag
 *
 * 113   12/07/98 3:02p Jason
 * added multi_logo_state
 *
 * 112   12/03/98 3:39p Jason
 * added peer 2 peer style damage
 *
 * 111   12/02/98 10:30a Jason
 * added additional damage types for client-side multiplayer
 *
 * 110   12/01/98 5:48p Jeff
 * added pilot picture id to netplayer struct
 *
 * 109   12/01/98 12:47p Jason
 * got rid of NF_DROPMISORDERED and added NF_USE_SMOOTHING
 *
 * 108   11/19/98 11:27a Jason
 * added Multi_accept_state for Jeff
 *
 * 107   11/16/98 4:47p Jason
 * changes for multiplayer (weapons load sent and deleting destroyed
 * lightmapped objects)
 *
 * 106   11/13/98 4:25p Jason
 * changes for better weapon effects
 *
 * 105   11/11/98 12:11p Chris
 * The attach system and weapon firing (continous and spray) are now
 * network friendly
 *
 * 104   11/10/98 4:29p Kevin
 * Added attach code for chris
 *
 * 103   11/10/98 11:16a Jason
 * fixed some multiplayer bugs with powerups disappearing
 *
 *
 * 102   11/06/98 5:43p Jason
 * made pings sent not reliably
 *
 * 101   11/03/98 6:14p Chris
 * Starting to make on/off and spray weapons accessable to robots
 *
 * 100   10/28/98 11:51a Jason
 * fixed some multiplayer problems, plus redid coop a bit to make it
 * cleaner
 *
 * 99    10/27/98 10:19a Jason
 * changes for new architecture
 *
 * 98    10/23/98 1:08p Kevin
 * changed multi version
 *
 * 97    10/19/98 7:19p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 96    10/19/98 2:48p Kevin
 * Added accurate weapon thingy for Chris
 *
 * 95    10/08/98 3:38p Jeff
 * removed time_left from Netgame
 *
 * 94    10/07/98 1:07p Jason
 * added more safety precautions
 *
 * 93    10/05/98 7:23p Jason
 * added protective layer onto multiplayer
 *
 * 92    10/01/98 12:17p Kevin
 * Fixed Ping for Peer-Peer games
 *
 * 91    10/01/98 11:29a Jason
 * changes for world states in multiplayer games
 *
 * 90    9/30/98 5:35p Jason
 * added multiplayer menu bailing for samir
 *
 * 89    9/15/98 12:42p Jason
 * got dedicated server actually working
 *
 * 88    9/14/98 4:17p Jason
 * added friendly fire damage
 *
 * 87    9/11/98 12:26p Jason
 * got energy to shield and fusion damage working in multiplayer
 *
 * 86    9/04/98 3:45p Kevin
 * Added ping_time to Netplayers struct. It's updated in peer-peer and
 * client server
 *
 * 85    8/13/98 6:32p Kevin
 * Initial implementation of directplay API
 *
 * 84    8/12/98 6:36p Jeff
 * converted the send link/unlink functions to handle ghosted objects.
 * Updated MultiSendObject to handle dummy objects
 *
 * 83    8/12/98 1:17p Jeff
 * added link/unlink object packets
 *
 * 82    8/07/98 12:27p Kevin
 * Added network stuff for energy/shield conversion
 *
 * 81    8/04/98 6:13p Kevin
 * fixes for sound & bmp exchange
 *
 * 80    8/04/98 3:07p Kevin
 * sound & bmp exchange fixes for > 2 players
 *
 * 79    8/04/98 10:26a Kevin
 * Custom sound and bmp exchange system
 *
 * 78    8/03/98 5:56p Jason
 * got fusion cannon working correctly
 *
 * 77    7/29/98 5:39p Kevin
 * sound/bitmap exchange
 *
 * 76    7/29/98 12:40p Jason
 * more multiplayer testing for occlusion and packet sequencing
 *
 * 75    7/27/98 5:31p Kevin
 * Sound/Bitmap exchange system
 *
 * 74    7/24/98 9:37a Kevin
 * Added some new MP_ types
 *
 * 73    7/23/98 12:38p Jason
 * more tweaks for multiplayer vis stuff
 *
 * 72    7/22/98 3:16p Jason
 * added observer mode
 *
 * 71    7/20/98 6:20p Kevin
 * peer-peer stuff
 *
 * 70    7/17/98 1:22p Kevin
 * Dynamic retransmission of reliable packets and stuff
 *
 * 69    7/16/98 12:51p Jason
 * added a way for DLLs to bail out if something is wrong
 *
 * 68    7/14/98 5:52p Kevin
 * Packet loss measurements and auto pps adjusting
 *
 * 67    7/13/98 11:52a Kevin
 * Added Callscriptwithparms
 *
 * 66    7/08/98 6:01p Jeff
 * added packet to remove an item from inventory
 *
 * 65    7/08/98 12:01p Kevin
 * weapon battery info
 *
 * 64    7/07/98 7:33p Jeff
 * changes made for inventory use
 *
 * 63    7/07/98 3:16p Kevin
 * Added inventory parms
 *
 * 62    7/07/98 11:19a Kevin
 * Added inventory use message
 *
 * 61    7/07/98 10:10a Kevin
 * Added basic turret support for coop
 *
 * 60    7/06/98 6:46p Kevin
 * vector parameter passing in scripts
 *
 * 59    7/06/98 5:36p Kevin
 * Variable parameter passing
 *
 * 58    7/06/98 11:51a Jason
 * added accessor function for countermeasures
 *
 * 57    7/02/98 12:57p Jason
 * various changes for multiplayer positional sequencing
 *
 * 56    7/02/98 10:39a Kevin
 * More coop stuff
 *
 * 55    7/01/98 6:30p Kevin
 * More coop
 *
 * 54    7/01/98 12:55p Jason
 * more changes for countermeasures
 *
 * 53    7/01/98 12:11p Jason
 * added countermeasures
 *
 * 52    6/30/98 7:17p Kevin
 * more animation stuff
 *
 * 51    6/30/98 5:08p Kevin
 * Animation frame stuff
 *
 * 50    6/30/98 3:58p Chris
 *
 * 49    6/30/98 11:39a Jason
 * added AdditionalDamage packet type for multiplayer
 *
 * 48    6/29/98 3:08p Jason
 * added on/off weapons
 *
 * 47    6/29/98 12:49p Jason
 * temp checkin for on/off weapons
 *
 * 46    6/29/98 12:12p Kevin
 * Added robot damage and death packets
 *
 * 45    6/26/98 6:53p Kevin
 * Coop mode
 *
 * 44    6/26/98 6:20p Jason
 * changes for coop
 *
 * 43    6/25/98 5:22p Kevin
 * Req/Send gametime to clients
 *
 * 42    6/25/98 12:32p Jason
 * added new multiplayer functionality
 *
 * 41    6/24/98 3:24p Kevin
 * Updated PXO screens with chat, etc.
 *
 * 40    6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 39    5/19/98 6:27p Jason
 * put in urgent packets
 *
 * 38    5/14/98 11:07a Kevin
 * Made gameover packet to the tracker reliable
 *
 * 37    5/12/98 5:12p Jason
 * added dll callable level ending
 *
 * 36    5/12/98 4:18p Jason
 * added better level sequencing for multiplayer
 *
 * 35    5/12/98 12:33p Jason
 * got level sequencing working in multiplayer
 *
 * 34    5/04/98 10:55a Kevin
 * Mastertracker fixes/enhancements
 *
 * 33    4/30/98 3:50p Kevin
 * Mastertracker pilot stats
 *
 * 32    4/28/98 2:58p Kevin
 * Added mastertracker flags
 *
 * 31    4/24/98 3:50p Kevin
 * Added mastertracker game tracking support
 *
 * 30    4/20/98 12:46p Jason
 * added level checksumming for multiplayer games
 *
 * 29    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 28    4/14/98 7:56p Matt
 * Moved MSN_NAMELEN from mission.h to descent,h, so multi.h didn't need
 * to include mission.h.
 *
 */

#ifndef MULTI_H
#define MULTI_H

#include <array>

#include "pstypes.h"
#include "vecmat_external.h"
#include "object_external_struct.h"
#include "object_external.h"
#include "player_external.h"
#include "spew.h"

#if defined(__LINUX__)
#include "linux_fix.h"
#endif

#include "multi_external.h" //defines and structs are in here

extern bool Multi_bail_ui_menu;
#if defined(DEMO)
#define MULTI_VERSION 7
#elif defined(OEM)
#define MULTI_VERSION 5
#else
// #define MULTI_VERSION	4
//  Patch 1.1!
// #define MULTI_VERSION	6
//  Patch 1.3
#define MULTI_VERSION 10
#endif

#define MULTI_PING_INTERVAL 3

// Multiplayer packets
#define MP_CONNECTION_ACCEPTED 1  // Server says we can join
#define MP_OBJECT 2               // Object packet from the server
#define MP_PLAYER 3               // Name packet from the server
#define MP_ALL_SET 4              // Client is ready to play!
#define MP_PLAYER_POS 5           // Player position packet
#define MP_REQUEST_PLAYERS 6      // Clients wants to know about players
#define MP_MY_INFO 7              // Stats for local client
#define MP_DONE_PLAYERS 8         // Done requesting players
#define MP_ENTERING_GAME 9        // I'm entering the game
#define MP_DISCONNECT 10          // A player has disconnected
#define MP_PLAYER_FIRE 11         // A player is firing
#define MP_ASK_TO_JOIN 12         // Asking if its ok to join
#define MP_JOIN_RESPONSE 13       // Answering MP_ASK_TO_JOIN
#define MP_SERVER_QUIT 14         // Server is quitting
#define MP_LEAVE_GAME 15          // A client is leaving the game
#define MP_BLOWUP_BUILDING 16     // A building is blowing up
#define MP_DONE_BUILDINGS 17      // Server is done sending buildings
#define MP_REQUEST_BUILDINGS 18   // Requesting buildings
#define MP_BUILDING 19            // Server is telling us about buildings
#define MP_DONE_OBJECTS 20        // Server is done sending buildings
#define MP_REQUEST_OBJECTS 21     // Requesting buildings
#define MP_JOIN_OBJECTS 22        // Server is telling us about buildings
#define MP_PLAYER_DEAD 23         // Server says someone is dead!
#define MP_PLAYER_RENEW 24        // A player is coming back from the dead!
#define MP_PLAYER_ENTERED_GAME 25 // A player is entering the game
#define MP_DAMAGE_PLAYER 26       // A player should take damage
#define MP_MESSAGE_FROM_SERVER 27 // A text message from the server
#define MP_END_PLAYER_DEATH 28    // A player is done dying
#define MP_RENEW_PLAYER 29        // Renew a player (a new ship!)
#define MP_GET_GAME_INFO 30       // Someone is asking about our game
#define MP_GAME_INFO 31           // Server is telling us about its game
//@@#define MP_EXECUTE_SCRIPT						32	// Server says to execute a script
#define MP_MESSAGE_TO_SERVER 33      // A message from the client to the server
#define MP_SPECIAL_PACKET 34         // a special data packet for scripts
#define MP_EXECUTE_DLL 35            // Server says to execute a dll
#define MP_REMOVE_OBJECT 36          // Server says to remove an object
#define MP_GUIDED_INFO 37            // Guided missile info from a player
#define MP_LEVEL_ENDED 38            // Server says the level has ended
#define MP_READY_FOR_LEVEL 39        // Client wants info about the level
#define MP_LEVEL_INFO 40             // Server is telling client about the level
#define MP_GET_PXO_GAME_INFO 41      // Same as MP_GET_GAME_INFO but for PXO games only
#define MP_POWERUP_REPOSITION 42     // The server is telling the client to move a powerup
#define MP_GET_GAMETIME 43           // Client equesting the server's gametime
#define MP_HERE_IS_GAMETIME 44       // Server's gametime response
#define MP_ROBOT_POS 45              // Robot position and orientation
#define MP_ROBOT_FIRE 46             // A robot is firing
#define MP_ROBOT_DAMAGE 47           // Apply damage to robot
#define MP_ROBOT_EXPLODE 48          // Blow up robot
#define MP_ON_OFF 49                 // a player is starting or stopping an on/off weapon
#define MP_ADDITIONAL_DAMAGE 50      // Server is telling us to add or subtract shields
#define MP_ANIM_UPDATE 51            // Server is sending an animation update packet
#define MP_REQUEST_COUNTERMEASURE 52 // Client is asking the server to create a countermeasure
#define MP_CREATE_COUNTERMEASURE 53  // Server is telling us to create a countermeasure
#define MP_PLAY_3D_SOUND_FROM_OBJ 54 // Server sending a 3d sound based on an obj position
#define MP_PLAY_3D_SOUND_FROM_POS 55 // Server sending a 3d sound based on an arbitrary position
#define MP_ROBOT_FIRE_SOUND 56       // The packet type which makes the firing sound from the robot
//@@#define MP_EXECUTE_SCRIPT_WITH_PARMS		57 // Execute Script with parameters
#define MP_TURRET_UPDATE 58 // Update on turret info from the server
#define MP_CLIENT_USE_INVENTORY_ITEM                                                                                   \
  59                                //	Client is telling the server that he want's to use an item from his inventory
#define MP_REMOVE_INVENTORY_ITEM 60 // Server is telling the clients to remove an item from a player's inventory
#define MP_SERVER_SENT_COUNT 61     //	The server is telling the client how much data he has sent
#define MP_CLIENT_SET_PPS 62        //	The client is telling the server what pps to use
#define MP_GREETINGS_FROM_CLIENT 63 //	The client is identifying himself so the server knows his ip
#define MP_REQUEST_TO_OBSERVE 64    // A player is requesting to enter observe mode
#define MP_OBSERVER_CHANGE 65       // The server is telling us about an observer change
#define MP_VISIBLE_PLAYERS 66       // Server is telling us what players are visible
#define MP_FILE_REQ 67              // Request a sound or bmp for a particular player slot
#define MP_FILE_DENIED 68           // The server isn't going to send you a file you asked for (no soup for you)
#define MP_FILE_DATA 69             // Data chunk, which is part of a file xfer
#define MP_FILE_ACK 70 // When you receive a chunk of data, reply with this ACK and the sender will send the next chunk
#define MP_SERVER_ECHO_REQ                                                                                             \
  71 // Special packet the server sends to an echo server (on the mastertracker) which responds with his IP address and
     // port. It makes sure servers behind firewalls/NAT/proxy work
#define MP_SERVER_ECHO_RSP 72           // Response from Echo server with our real IP and port
#define MP_FILE_CANCEL 73               // Cancel an existing file transfer (client or server/Sender or receiver)
#define MP_INVISIBLE_PLAYER 74          // Just a packeting test
#define MP_PLAYER_CUSTOM_DATA 75        //	This player has custom data. Here are the file names
#define MP_ABORT_JOIN_SERVER 76         // Stop trying to join a server because the level is ending or server quiting
#define MP_ENERGY_SHIELD_CONV_ON_OFF 77 // Client wants to do an energy to shield conversion
#define MP_GHOST_OBJECT 78              // Tells clients to ghost or unghost an object
#define MP_PLAYER_PING 79               // Ask for a ping
#define MP_PLAYER_PONG 80               // Response to a ping.
#define MP_PLAYER_LAG_INFO 81           // Tell clients in a client/server game what the ping of another player is.
#define MP_REQUEST_DAMAGE 82            // We're asking the server to damage us
#define MP_REQUEST_SHIELDS 83           // We're asking the server to give us shields
#define MP_REQUEST_WORLD_STATES 84      // Clients wants to know about the world state
#define MP_DONE_WORLD_STATES 85         // Server says we're done with world states
#define MP_WORLD_STATES 86              // Information about the world
#define MP_ATTACH_OBJ 87                // Attach an object with the attach system
#define MP_UNATTACH_OBJ 88              // UnAttach an object with the attach system
#define MP_AIWEAP_FLAGS 89              // Allows robots to have continous and spray weapons
#define MP_ATTACH_RAD_OBJ 90            // Attach by rad
#define MP_TIMEOUT_WEAPON 91            // Timeout weapon
#define MP_WEAPONS_LOAD 92              // Client is telling server about weapons load
#define MP_REQUEST_PEER_DAMAGE 93       // Client is asking another player to damage him
#define MP_MSAFE_FUNCTION 94            // Msafe function
#define MP_MSAFE_POWERUP 95             // Multisafe powerup
#define MP_ASK_FOR_URL 96               // Ask for a url list from the server
#define MP_CUR_MSN_URLS 97              // Response from the server listing the URLs for the current mission
#define MP_REQUEST_TO_FIRE 98           // Client is requesting to fire
#define MP_PERMISSION_TO_FIRE 99        // Permissable firing packet
#define MP_CONNECT_BAIL 100             // Server says to bail on connecting
#define MP_CLIENT_PLAY_TAUNT 101        // Client is requesting to play audio taunt
#define MP_SERVER_PLAY_TAUNT 102        // Server is telling clients to play a player's audio taunt
#define MP_REQUEST_MARKER 103           // Client is asking for a marker to be dropped
#define MP_REQUEST_TYPE_ICON 104        // Client is telling server that he is typing a message
#define MP_SEND_TYPE_ICON 105  // Server is telling clients that a player is typing a message (to display icon on hud)
#define MP_REQUEST_TO_MOVE 106 // Client is requesting to move
#define MP_ADJUST_POSITION 107 // Server is telling me my new position
#define MP_GENERIC_NONVIS 108  // Server says I can't see this generic object
#define MP_SEND_DEMO_OBJECT_FLAGS 109 // Server is sending what join objects have the OF_CLIENTDEMOOBJECT set
#define MP_GUIDEBOTMENU_REQUEST 110   // Client is requesting either the guidebot menu, or one of the items on the menu
#define MP_GUIDEBOTMENU_DATA 111      // Server is sending the guidebot text to display in the menu
#define MP_BREAK_GLASS 112            // Server is telling us to break some glass
#define MP_THIEF_STEAL 113            // Server is telling a client that the thief stole an item from him
#define MP_REQUEST_PLAYERLIST 114     // Client is requesting a list of players for this game
#define MP_PLAYERLIST_DATA 115        // Server is sending a list of players in this game
#define MP_SERVER_AUDIOTAUNT_TIME 116
#define MP_CHANGE_RANK 117       // Server says a player has changed rank
#define MP_BASHPLAYER_SHIP 118   // Server says we need to use a different ship
#define MP_HEARTBEAT 119         // A blank packet that says we're still alive (for loading levels)
#define MP_INITIAL_RANK 120      // Server is telling me about rank
#define MP_MISSILE_RELEASE 121   // Informing about a guided missile being released from guided mode
#define MP_STRIP_PLAYER 122      // Strips player of all weapons (but laser) and reduces energy to 0
#define MP_REJECTED_CHECKSUM 123 // The server rejected the client checksum. This lets the client know.

// Shield request defines
#define MAX_SHIELD_REQUEST_TYPES 1
#define SHIELD_REQUEST_ENERGY_TO_SHIELD 0

#define SERVER_PLAYER 128

#define MASTER_TRACKER_SIG 0xf429b142

// values for fired_on_this_frame
#define PFP_NO_FIRED 0       // the player didn't fire at all this frame
#define PFP_FIRED 1          // the player fired this frame and the info should be packed in a player pos flag
#define PFP_FIRED_RELIABLE 2 // used for secondaries of a non-peer to peer game
struct player_fire_packet {
  uint8_t fired_on_this_frame;
  uint8_t wb_index;
  uint8_t fire_mask;
  uint8_t damage_scalar;
  uint8_t reliable;
  int dest_roomnum;
};

extern netgame_info Netgame;

extern std::array<uint16_t, MAX_OBJECTS> Local_object_list;
extern std::array<uint16_t, MAX_OBJECTS> Server_object_list;
extern std::array<uint16_t, MAX_SPEW_EFFECTS> Server_spew_list;

#define MAX_RECEIVE_SIZE 4096
#define MAX_NETWORK_GAMES 100

// The size of the packet_number and guaranteed fields of game_packet_data:
#define HEADER_INFO_SIZE 5

#define NETFILE_NONE 0      // No file transfer in progress
#define NETFILE_SENDING 1   // Sending a file to someone
#define NETFILE_RECEIVING 2 // Receiving a file from someone
#define NETFILE_ASKING 3    // Waiting for a response as to if we can get a file

#define NETFILE_ID_NOFILE 0       // No file at all (for sequencing)
#define NETFILE_ID_SHIP_TEX 1     // Custom ship texture
#define NETFILE_ID_VOICE_TAUNT1 2 // Voice taunt #1
#define NETFILE_ID_VOICE_TAUNT2 3 // Voice taunt #2
#define NETFILE_ID_VOICE_TAUNT3 4 // Voice taunt #3
#define NETFILE_ID_VOICE_TAUNT4 5 // Voice taunt #4
#define NETFILE_ID_DONE 99        // Done transferring files

// This sets the last file we look for in the sequence above
#define NETFILE_ID_LAST_FILE NETFILE_ID_VOICE_TAUNT4

// A semi-compressed orientation matrix for multiplayer games
struct multi_orientation {
  int16_t multi_matrix[9];
};

static inline void MultiMatrixMakeEndianFriendly(multi_orientation *mmat) {
  for (int i = 0; i < 9; i++) {
    mmat->multi_matrix[i] = INTEL_SHORT(mmat->multi_matrix[i]);
  }
}

// For firing players
extern std::array<player_fire_packet, MAX_NET_PLAYERS> Player_fire_packet;

// For powerup respawning
#define MAX_RESPAWNS 300
#define RESPAWN_TIME 60 // seconds until a powerup respawns

#define MULTI_SEND_MESSAGE_ALL -1
#define MULTI_SEND_MESSAGE_RED_TEAM -2
#define MULTI_SEND_MESSAGE_BLUE_TEAM -3
#define MULTI_SEND_MESSAGE_GREEN_TEAM -4
#define MULTI_SEND_MESSAGE_YELLOW_TEAM -5

struct powerup_respawn {
  vector pos;
  int objnum;
  int roomnum;
  uint8_t used;
  int16_t original_id;
};

struct powerup_timer {
  int id;
  float respawn_time;
};

extern std::array<powerup_timer, MAX_RESPAWNS> Powerup_timer;
extern std::array<powerup_respawn, MAX_RESPAWNS> Powerup_respawn;
extern std::array<network_game, MAX_NETWORK_GAMES> Network_games;
extern std::array<netplayer, MAX_NET_PLAYERS> NetPlayers;
extern std::array<uint8_t, MAX_RECEIVE_SIZE> Multi_receive_buffer;
extern int Ok_to_join;
extern int Num_powerup_respawn;
extern int Num_powerup_timer;
extern int Multi_next_level;

// Heartbeat flag
extern bool Got_heartbeat;

// This is for breakable glass
#define MAX_BROKE_GLASS 100
extern std::array<uint16_t, MAX_BROKE_GLASS> Broke_glass_rooms, Broke_glass_faces;
extern int Num_broke_glass;

// For keeping track of damage and shields
extern std::array<float, MAX_NET_PLAYERS> Multi_additional_damage;
extern int Multi_requested_damage_type;
extern float Multi_requested_damage_amount;
extern std::array<float, MAX_SHIELD_REQUEST_TYPES> Multi_additional_shields;

extern std::array<std::array<uint8_t, MAX_GAME_DATA_SIZE>, MAX_NET_PLAYERS> Multi_send_buffer;
extern std::array<int, MAX_NET_PLAYERS> Multi_send_size;
extern std::array<std::array<float, MAX_NET_PLAYERS>, MAX_NET_PLAYERS> Multi_last_sent_time;
extern std::array<int, MAX_NET_PLAYERS> Multi_additional_damage_type;

extern std::array<uint8_t, MAX_NET_PLAYERS> Multi_reliable_urgent;
extern std::array<std::array<uint8_t, MAX_GAME_DATA_SIZE>, MAX_NET_PLAYERS> Multi_reliable_send_buffer;
extern std::array<int, MAX_NET_PLAYERS> Multi_reliable_send_size;
extern std::array<float, MAX_NET_PLAYERS> Multi_reliable_last_send_time;
extern std::array<uint8_t, MAX_NET_PLAYERS> Multi_reliable_sent_position;
extern uint32_t Multi_visible_players[];

extern int Got_level_info;
extern int Got_new_game_time;
// For keeping track of buildings that have changed
extern std::array<uint8_t, MAX_OBJECTS> Multi_building_states;
extern uint16_t Multi_num_buildings_changed;

extern bool Multi_logo_state;

// For searching out netgames
extern int Num_network_games_known;

// Is this a master tracker game?
extern int Game_is_master_tracker_game;

#define TRACKER_ID_LEN 10 // Don't change this!
extern std::array<char, TRACKER_ID_LEN> Tracker_id;

#define LOGIN_LEN 33
#define REAL_NAME_LEN 66
#define PASSWORD_LEN 17
#define EMAIL_LEN 100
#define TRACKER_ID_LEN 10
#define PILOT_NAME_LEN 20

#if defined(WIN32)
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
  uint32_t checksum;   // This value needs to be equal to whatever the checksum is once the packet is decoded
  uint32_t pad; // just to provide room for out 4 byte encryption boundry only needed on the client side for now
};
#define DESCENT3_BLOCK_SIZE (sizeof(vmt_descent3_struct) - 4)
#if defined(WIN32)
#pragma pack(pop, pxo)
#else
#pragma pack()
#endif

extern std::array<vmt_descent3_struct, MAX_NET_PLAYERS> MTPilotinfo;

// Display a menu based on what the server just told us about
void MultiDoGuidebotMenuData(uint8_t *data);

// The user either wants a menu to display or they took an action off of the menu
void MultiDoGuidebotMenuRequest(uint8_t *data, int slot);

void MultiProcessBigData(uint8_t *buf, int len, network_address *from_addr);

// Points the server_address variable at a new location
void MultiSetServerAddress(network_address *addr);

// Does multiplayer stuff for one frame
void MultiDoFrame();

// Returns 1 on success, 0 on fail
int TryToJoinServer(network_address *addr);

// The server says we can join!
void MultiDoConnectionAccepted(uint8_t *data);

// Polls for a connection message so we can finally join this game
void MultiPollForConnectionAccepted();

// Gets a new connection set up
void MultiSendConnectionAccepted(int slotnum, SOCKET sock, network_address *addr);

// Starts a new multiplayer game
void StartNewMultiplayerGame();

// Clears all connections
// Server and Client
void MultiCloseGame();

// The server sends to everyone that the player is dead
void MultiSendPlayerDead(int slot, uint8_t fate);

// Called when you want to leave a netgame
void MultiLeaveGame();

// MultiProcessIncoming reads incoming data off the unreliable and reliable ports and sends
// the data to process_big_data
void MultiProcessIncoming();

// Starts a packet of data
int START_DATA(int type, uint8_t *data, int *count, uint8_t reliable = 0);

// End a pakcet of data
void END_DATA(int count, uint8_t *data, int offset);

// Skip the header stuff
void SKIP_HEADER(uint8_t *data, int *count);

// Starts a level for multiplayer
bool MultiStartNewLevel(int level);

// Returns the number of players in a game
int MultiCountPlayers();

// Puts player "slot" position info into the passed in buffer
// Returns the number of bytes used
int MultiStuffPosition(int slot, uint8_t *data);

// Sends a full packet out the the server
// Resets the send_size variable
// If slot = -1, sends out to the server
void MultiSendFullPacket(int slot, int flags);

void MultiSendFullReliablePacket(int slot, int flags);

// Makes the passed in player a ghost
void MultiMakePlayerGhost(int slot);

// Makes the passed in player real (non-ghost)
void MultiMakePlayerReal(int slot);

// Sends a fire packet from a player
void MultiSendFirePlayerWB(int playernum, uint8_t wb_index, uint8_t fire_mask, uint8_t reliable = 0, float scalar = 1.0);

void MultiMakeMatrix(multi_orientation *dest, matrix *src);

// Extracts a matrix from an abbreviated matrix
void MultiExtractMatrix(matrix *dest, multi_orientation *src);

void MultiSendBlowupBuilding(int, int, float);

// Return index of powerup that has matching table entry
int MultiMatchPowerup(int unique_id);

// Return index of robot that has matching table entry
int MultiMatchRobot(int unique_id);

// Builds the tables for uniquely identifying powerups and robots
void MultiBuildMatchTables();

// Return index of generic that has matching table entry
int MultiMatchWeapon(uint32_t unique_id);

// Tell my clients about damage done to a player
void MultiSendDamagePlayer(int, int, int type, float amount);

// Send a message!
void MultiSendMessageFromServer(int, char *, int to = MULTI_SEND_MESSAGE_ALL);

// Tells the server that I'm done dying
void MultiSendEndPlayerDeath();

// Returns the unique id of a given object type/id
uint32_t MultiGetMatchChecksum(int type, int id);

// Return index of generic that has matching table entry
int MultiMatchGeneric(uint32_t unique_id);

// Sends a message from client to server
void MultiSendMessageToServer(int, char *, int to = MULTI_SEND_MESSAGE_ALL);

// Sends an object from the server to the client
void MultiSendObject(object *obj, uint8_t announce, uint8_t demo_record = false);

// Paints all the goal rooms in a level with their colors
void MultiPaintGoalRooms(int *texcolors = NULL);

// Sends a special script packet to a player
void MultiSendSpecialPacket(int slot, uint8_t *outdata, int size);

// Flushes all receive sockets so that there is no data coming from them
void MultiFlushAllIncomingBuffers();

// Tells all clients to remove a specified object
void MultiSendRemoveObject(object *obj, uint8_t playsound);

// Sends the special script packet to the server
void MultiClientSendSpecialPacket(uint8_t *outdata, int size);

// Sends info out on my guided missile into a slot
// returns number of bytes in packet
int MultiStuffGuidedInfo(uint8_t, uint8_t *);

// Polls for a connection message so we can finally join this game
// Client only
int MultiPollForLevelInfo();

// Server is telling us about the level
void MultiDoLevelInfo(uint8_t *data);

// Server is telling the client about the level currently playing
// Server only
void MultiSendLevelInfo(int slot);

// Clients says he's ready for level info
// so send it to him
void MultiDoReadyForLevel(uint8_t *data);

// Client is telling the server that he is ready for a level
// Client only
void MultiSendReadyForLevel();

// Tells all the clients to end the level
void MultiSendLevelEnded(int success, int next_level);

// Some DLL is telling us to end the level!
void MultiEndLevel();

// Request the server's gametime
void GetServerGameTime();

// Send robot info
int MultiStuffRobotPosition(uint16_t objectnum, uint8_t *data);

// Handle robot position
void MultiDoRobotPos(uint8_t *data);

// Handle robot (or any AI created) weapon fire
int MultiSendRobotFireWeapon(uint16_t objectnum, vector *pos, vector *dir, uint16_t weaponnum);

// Send robot damage
void MultiSendKillObject(object *hit_obj, object *killer, float damage, int death_flags, float delay, int16_t seed);

// handle robot damage
void MultiDoRobotExplode(uint8_t *data);

// Peer to peer request for damage
void MultiSendRequestPeerDamage(object *, int, int, float);

// Tell all the clients about this players rank
void MultiSendInitialRank(int pnum);

// Tells the other players that a slot is starting/stopping its on/off weapon
void MultiSendOnOff(object *obj, uint8_t on, uint8_t wb_index, uint8_t fire_mask);

// Tells all the clients to apply damage to a player
void MultiSendAdditionalDamage(int slot, int type, float amount);

// We're asking the server to create a countermeasure for us
void MultiSendRequestCountermeasure(int16_t objnum, int weapon_index);

// Tell the client that an object took damage
void MultiSendDamageObject(object *hit_obj, object *killer, float damage, int weaponid);

// Handle message from server that robot/object took damage
void MultiDoRobotDamage(uint8_t *data);

// Add an object to the list of objects that need an animation update next player packet interval
void MultiAddObjAnimUpdate(int objnum);

// Stuff an animation update into a packet
int MultiStuffObjAnimUpdate(uint16_t objnum, uint8_t *data);

// Handle an animation update
void MultiDoObjAnimUpdate(uint8_t *data);

// Play a 3d sound that the server told us about
void MultiDoPlay3dSound(uint8_t *data);

// Tell the clients to play a 3d sound
void MultiPlay3dSound(int16_t soundidx, uint16_t objnum, int priority);

// Tell the client to play a sound because a robot fired
void MultiSendRobotFireSound(int16_t soundidx, uint16_t objnum);

// Play the robot sound that the server told us about
void MultiDoRobotFireSound(uint8_t *data);

// Add a turret to the list of stuff to be updated
void MultiAddObjTurretUpdate(int objnum);

// Stuff turret data into a packet
int MultiStuffTurretUpdate(uint16_t objnum, uint8_t *data);

// Handle a turret update from the server
void MultiDoTurretUpdate(uint8_t *data);

// Handle a client use inventory item packet
void MultiDoClientInventoryUseItem(int slot, uint8_t *data);

// Send a request to use an inventory item to the server
void MultiSendClientInventoryUseItem(int type, int id);

// Handle a remove item from inventory
void MultiDoClientInventoryRemoveItem(int slot, uint8_t *data);

// Tell the clients to remove an item from a player's inventory
void MultiSendInventoryRemoveItem(int slot, int type, int id);

void MultiAddObjWBAnimUpdate(int objnum);

int MultiStuffObjWBAnimUpdate(uint16_t objnum, uint8_t *data);

void MultiDoObjWBAnimUpdate(uint8_t *data);

void MultiDoBytesSent(uint8_t *data);

void MultiSendBytesSent(int slot);

void MultiSendPPSSet(int pps);

void MultiDoPPSSet(uint8_t *data, int slot);

void MultiSendGreetings(uint32_t id);

void MultiDoGreetings(uint8_t *data, network_address *addr);

// We're asking to enter observer mode
void MultiSendRequestToObserve(int mode, int on, int objnum);

// Server is telling us about players that we can see
void MultiDoVisiblePlayers(uint8_t *data);

// Sends all the visible players to another player
void MultiSendVisiblePlayers(int to_slot);

void MultiDoFileReq(uint8_t *data);

void MultiDoFileDenied(uint8_t *data);

void MultiDoFileData(uint8_t *data);

void MultiDoFileAck(uint8_t *data);

//	Tells clients that a particular player's custom data is here and ready for downloading
void MultiSendClientCustomData(int slot, int whoto = -1);

void MultiCancelFile(int playernum, int filenum, int file_who);

void MultiAskForFile(uint16_t file_id, uint16_t file_who, uint16_t who);

void DoNextPlayerFile(int playernum);

// We're asking the server to damage us
void MultiSendRequestDamage(int type, float amount);

// Asks the server for shields based on frametime "amount" x the type of shields requested
void MultiSendRequestShields(int type, float amount);

// Tells the clients to ghost or unghost an object
void MultiSendGhostObject(object *obj, bool ghost);
void MultiDoGhostObject(uint8_t *data);

// Sends this nonreliable packet to everyone except the server and the named slot
void MultiSendToAllExcept(int except, uint8_t *data, int size, int seq_threshold);

// Tells the server about the weapons we're carrying
void MultiSendWeaponsLoad();

// Tell clients to break some glass
void MultiSendBreakGlass(room *rp, int facenum);

// Sends a heartbeat to the server
void MultiSendHeartbeat();

// Ping functions to find the players latency
void MultiDoPong(uint8_t *data);
void MultiDoPing(uint8_t *data, network_address *addr);
void MultiSendPing(int slot);
void MultiDoLagInfo(uint8_t *data);

// Stuffs a players firing information into a packet
int MultiStuffPlayerFire(int slot, uint8_t *data);

// Stuffs request to move into a packet
int MultiStuffRequestToMove(uint8_t *data);

// Stuff info for a guided missile
int MultiStuffGuidedInfo(int slot, uint8_t *data);

// Tell everyone I'm timingout my timeout weapon
void MultiSendReleaseTimeoutMissile();

// We're asking the server for permission to fire!
void MultiSendRequestToFire(int, int, float scalar = 1.0);

// Client is asking the server to play an audio taunt
void MultiSendRequestPlayTaunt(int index);

// Client is asking for a marker
void MultiSendRequestForMarker(char *message);

// Client is telling the server that he is [not] typing a hud message
void MultiSendRequestTypeIcon(bool typing_message);

// Sets whether or not the server answsers to a connection request
extern bool Multi_accept_state;
void MultiSetAcceptState(bool state);

void MultiSendAiWeaponFlags(object *obj, int flags, int wb_index);
void MultiDoAiWeaponFlags(uint8_t *data);
void MultiSendAttach(object *parent, char parent_ap, object *child, char child_ap, bool f_aligned);
void MultiDoAttach(uint8_t *data);
void MultiSendAttachRad(object *parent, char parent_ap, object *child, float rad);
void MultiDoAttachRad(uint8_t *data);
void MultiSendUnattach(object *child);
void MultiDoUnattach(uint8_t *data);

void MultiDoJoinDemoObjects(uint8_t *data);

// Rank stuff
void MultiDoChangeRank(uint8_t *data);

// Sets whether or not we want the logos to be displayed on ships
void MultiSetLogoState(bool state);

void MultiSendThiefSteal(int player, int item);
void MultiDoThiefSteal(uint8_t *data);

void MultiSetAudioTauntTime(float time, int to_who = -1);
void MultiDoAudioTauntTime(uint8_t *data);

// Server only function to clear a Guidebot for a disconnected player
void MultiClearGuidebot(int slot);

// Guided missile release
void MultiDoMissileRelease(int from_slot, uint8_t *data);
void MultiSendMissileRelease(int slot, bool is_guided);

// Server telling a client what ship to switch to
void MultiBashPlayerShip(int slot, char *ship);

// Strips a player bare of weapons
void MultiSendStripPlayer(int slot);

inline void MultiGetTypeID(uint8_t *data, int *count, int *type, int *id) {
  *id = -1;
  *type = MultiGetByte(data, count);

  uint32_t hash_value = MultiGetUint(data, count);

  if ((*type) == OBJ_WEAPON)
    *id = MultiMatchWeapon(hash_value);
  else
    *id = MultiMatchGeneric(hash_value);
}

inline void MultiAddTypeID(int type, int id, uint8_t *data, int *count) {
  uint32_t hash_value;
  hash_value = MultiGetMatchChecksum(type, id);

  MultiAddByte(type, data, count);
  MultiAddUint(hash_value, data, count);
}

int MultiGetShipChecksum(int ship_index);

#endif
