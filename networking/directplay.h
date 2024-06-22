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

 * $Logfile: /DescentIII/Main/lib/directplay.h $
 * $Revision: 5 $
 * $Date: 9/02/98 6:54p $
 * $Author: Kevin $
 *
 *	Directplay API header
 *
 * $Log: /DescentIII/Main/lib/directplay.h $
 *
 * 5     9/02/98 6:54p Kevin
 * Fixed general directplay support up, and got modem-modem working
 *
 * 4     8/24/98 10:55a Kevin
 * new directplay stuff
 *
 * 3     8/14/98 4:54p Kevin
 * More directplay stuff
 *
 * 2     8/13/98 6:32p Kevin
 * Initial implementation of directplay API
 *
 * 1     8/13/98 6:25p Kevin
 *
 */
#ifndef _OUTRAGE_DIRECTPLAY_HEADER
#define _OUTRAGE_DIRECTPLAY_HEADER

#include "dplay.h"
#include "dplobby.h"

struct modem_list {
  char name[200];
};

#define MAX_MODEMS 15
#define MAX_DP_GAMES 32
#define MAX_DIRECTPLAY_CONNECTIONS 10
#define MAX_PENDING_NEW_CONNECTIONS 10

extern bool Use_DirectPlay;
extern bool Directplay_lobby_launched_game;

extern DPSESSIONDESC2 Directplay_sessions[MAX_DP_GAMES];
extern int Num_directplay_games;

extern uint32_t Pending_dp_conn[MAX_PENDING_NEW_CONNECTIONS];

// This is called when a game is started, so Directplay will be happy
int dp_StartGame(char *gamename);

// This is called when the game ends, to tell directplay the game is over
void dp_EndGame();

// This is called to request a list of ongoig direct play games
int dp_ListDirectPlayGames();

//	Send a packet to a direct play user
int dp_DirectPlaySend(network_address *who_to, uint8_t *data, int len, bool reliable);

// This function will look for incoming messages, and dispatch them accordingly
void dp_DirectPlayDispatch();

// Initialize stuff
int dp_InitDirectPlay(char *conn_name, void *parms = NULL, int num_elements = 0);

// Shutdown things
void dp_ShutdownDirectPlay();

// Destroy a player object
void dp_DirectPlayDestroyPlayer(DPID who);

// Join a network game
int dp_DirectPlayJoinGame(LPDPSESSIONDESC2 session);

// Call this function with size set to 0, and it will fill in size with
// the amount of buffer space you need
// Otherwise, it will fill in the buffer with a bunch of null delimited
// strings, with a double null at the end.
int dp_GetModemChoices(char *buffer, LPDWORD size);

// Register a DirectPlay lobby aware application
// Use this so a directplay lobby provider such as zone.com can launch the game
//
// Parameters:
// appname		The non-localized name of the application (ie. "Descent 3") DON'T LOCALIZE THIS! IT IS AN ID
//	exefile		Executable file name (without path)
//	exepath		Path to executable file
//	arguments	Any command line arguments the app needs
//	workingdir	The Working directory for the application
//	description	Localized description of the application
void dp_RegisterLobbyApplication(char *appname, char *exefile, char *exepath, char *arguments, char *workingdir,
                                 char *description);

// Returns TRUE if the game was launched from a lobby
bool dp_DidLobbyLaunchGame();

// Autoconnects to a game or starts one, based on the directplay lobby stuff
bool dp_AutoConnect();

#endif
