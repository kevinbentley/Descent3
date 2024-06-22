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

 * $Logfile: /DescentIII/Main/dedicated_server.cpp $
 * $Revision: 1.5 $
 * $Date: 2004/03/11 03:46:52 $
 * $Author: kevinb $
 *
 * Dedicated server code
 *
 * $Log: dedicated_server.cpp,v $
 * Revision 1.5  2004/03/11 03:46:52  kevinb
 * Merge of 1.5 code from windows. Hopefully I didn't break anything!
 *
 * Revision 1.4  2001/01/13 21:48:45  icculus
 * patched to (re)compile on win32.
 *
 * Revision 1.3  2000/06/03 14:33:49  icculus
 * Merge with Outrage 1.4 tree...
 *
 *
 * 67    10/17/01 4:52p Matt
 * Use safe printf() to fix buffer overflow.
 *
 * 66    7/09/01 5:45p Matt
 * Added buffer overflow checking to dedicated server read.
 *
 * 65    4/20/00 4:46p Matt
 * Dedicated server messages now support sending to one player (or team)
 *
 * 64    4/20/00 2:23p Matt
 * Bail from parse routine if null command; used to have an Int3().  Fixed
 * the crash when ":" was typed in the dedicated server console.
 *
 * 63    3/23/00 2:34p Matt
 * Fixed table error (max string len) that caused crashes when parsing
 * MultiSettingsFile keywords.
 *
 * 62    10/21/99 5:39p Matt
 * Mac merge
 *
 * 61    8/23/99 5:12p Kevin
 * Fixed double frame interval calling for DMFC
 *
 * 60    7/20/99 12:57p Jason
 * added dedicated server message_of_the_day
 *
 * 59    7/15/99 12:47p Jeff
 * fixed dedicated server quiting when a player logs out from telnet.
 * Adding logout command
 *
 * 58    7/14/99 8:57p Jeff
 * don't parse out semi-colons
 *
 * 57    7/09/99 3:49p Jason
 * fixed bugs/issues for patch
 *
 * 56    7/06/99 5:52p Kevin
 * PXO & multiplayer fixes for the patch
 *
 * 55    6/10/99 4:12p Kevin
 * Fixed SetLevel in dedicated server for HEAT.NET, and added
 * level_names.str for level name localization.
 *
 * 54    5/24/99 9:55p Jason
 * fixed stupid dedicated server ship allow thing.  I swear I'm going to
 * start killing people who keep adding things to multiplayer when they
 * really don't know what they are doing.  STOP!
 *
 * 53    5/12/99 1:57p Jason
 * fixed yet more buggy/ugly code
 *
 * 52    5/10/99 5:35p Kevin
 * New command line options for heat and scoring API enhancements
 *
 * 51    5/09/99 1:34p Kevin
 * Added diffuculty level system to multiplayer
 *
 * 50    5/07/99 5:00p Jeff
 * handle errors better with a dedicated server if it couldn't load the
 * multiplayer dll
 *
 * 49    5/02/99 2:32p Kevin
 * fixed various dedicated server problems.
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstdio>

#include <string.h>
#include <stdlib.h>

#ifndef __LINUX__
typedef int socklen_t;
#endif

#include "pstypes.h"
#include "pserror.h"
#include "pstring.h"
#include "cfile.h"
#include "inffile.h"
#include "dedicated_server.h"
#include "multi.h"
#include "args.h"
#include "appconsole.h"
#include "ddio.h"
#include "newui.h"
#include "ui.h"
#include "multi_dll_mgr.h"
#include "multi_ui.h"
#include "Mission.h"
#include "multi_server.h"
#include "Macros.h"
#include "game.h"
#include "mem.h"
#include "stringtable.h"
#include "multi_save_settings.h"
#include "objinfo.h"
#include "rtperformance.h"
#include "player.h"
#include "stringtable.h"
#include "init.h"
#include "ship.h"
#include "hud.h"
#include "networking.h"


bool Dedicated_server = false;

static int Dedicated_start_level = 1;
static int Dummy_dedicated_var;
static char Dummy_dedicated_string[_MAX_PATH];

// If true, allow remote connections
static int Dedicated_allow_remote = 0;
static uint16_t Dedicated_listen_port = 2092;
static char dedicated_telnet_password[65];
static int Dedicated_num_teams = 1;

static int RunServerConfigs();
static int DedicatedServerLex(const char *command);
static void SetCVarNone(int index);

extern int CheckMissionForScript(char *mission, char *script, int dedicated_server_num_teams);

extern char Multi_message_of_the_day[];
extern char PXO_hosted_lobby_name[];
// These define the types of variables that can be set in the code through
// the dedicated server

static cvar_entry CVars[] = {
    {"PPS", CVAR_TYPE_INT, &Netgame.packets_per_second, 2, 20, CVAR_GAMEINIT}, // 0
    {"TimeLimit", CVAR_TYPE_INT, &Netgame.timelimit, 0, 10000, CVAR_GAMEINIT},
    {"KillGoal", CVAR_TYPE_INT, &Netgame.killgoal, 0, 10000, CVAR_GAMEINIT},
    {"RespawnTime", CVAR_TYPE_INT, &Netgame.respawn_time, 0, 10000, CVAR_GAMEINIT},
    {"GameName", CVAR_TYPE_STRING, &Netgame.name, -1, NETGAME_NAME_LEN, CVAR_GAMEINIT}, // 4
    {"MissionName", CVAR_TYPE_STRING, &Netgame.mission, -1, MSN_NAMELEN, CVAR_GAMEINIT},
    {"Scriptname", CVAR_TYPE_STRING, &Netgame.scriptname, -1, NETGAME_SCRIPT_LEN, CVAR_GAMEINIT},
    {"ConnectionName", CVAR_TYPE_STRING, &Netgame.connection_name, -1, PAGENAME_LEN, CVAR_GAMEINIT},
    {"Quit", CVAR_TYPE_NONE, NULL, -1, -1, CVAR_GAMEPLAY}, // 8
    {"EndLevel", CVAR_TYPE_NONE, NULL, -1, -1, CVAR_GAMEPLAY},
#if 0 // def DEMO
{"MaxPlayers",CVAR_TYPE_INT,&Netgame.max_players,2,16,CVAR_GAMEINIT},	//10
#else
    {"MaxPlayers", CVAR_TYPE_INT, &Netgame.max_players, 2, MAX_PLAYERS, CVAR_GAMEINIT}, // 10
#endif
    {"Say", CVAR_TYPE_STRING, NULL, -1, 200, CVAR_GAMEPLAY},                                                  // 11
    {"UseSmoothing", CVAR_TYPE_INT, &Dummy_dedicated_var, 0, 1, CVAR_GAMEINIT},                               // 12
    {"SendRotVel", CVAR_TYPE_INT, &Dummy_dedicated_var, 0, 1, CVAR_GAMEINIT},                                 // 13
    {"MultiSettingsFile", CVAR_TYPE_STRING, &Dummy_dedicated_string, -1, 40, CVAR_GAMEINIT},                  // 14
    {"DisallowPowerup", CVAR_TYPE_STRING, &Dummy_dedicated_string, -1, 40, CVAR_GAMEINIT | CVAR_GAMEPLAY},    // 15
    {"AllowPowerup", CVAR_TYPE_STRING, &Dummy_dedicated_string, -1, 40, CVAR_GAMEINIT | CVAR_GAMEPLAY},       // 16
    {"StartRtLog", CVAR_TYPE_NONE, NULL, -1, -1, CVAR_GAMEPLAY},                                              // 17
    {"StopRtLog", CVAR_TYPE_NONE, NULL, -1, -1, CVAR_GAMEPLAY},                                               // 18
    {"PXOUsername", CVAR_TYPE_STRING, &Auto_login_name, -1, 50, CVAR_GAMEINIT},                               // 19
    {"PXOPassword", CVAR_TYPE_STRING, &Auto_login_pass, -1, 50, CVAR_GAMEINIT},                               // 20
    {"BrightPlayers", CVAR_TYPE_INT, &Dummy_dedicated_var, -1, -1, CVAR_GAMEINIT},                            // 21
    {"Peer2Peer", CVAR_TYPE_INT, &Dummy_dedicated_var, -1, -1, CVAR_GAMEINIT},                                // 22
    {"AccurateCollisions", CVAR_TYPE_INT, &Dummy_dedicated_var, -1, -1, CVAR_GAMEINIT},                       // 23
    {"ConsolePassword", CVAR_TYPE_STRING, &dedicated_telnet_password, -1, 65, CVAR_GAMEINIT | CVAR_GAMEPLAY}, // 24
    {"AllowRemoteConsole", CVAR_TYPE_INT, &Dedicated_allow_remote, 0, 1, CVAR_GAMEINIT},                      // 25
    {"RemoteConsolePort", CVAR_TYPE_INT, &Dedicated_listen_port, 1, 65535, CVAR_GAMEINIT},                    // 26
    {"Permissable", CVAR_TYPE_INT, &Dummy_dedicated_var, -1, -1, CVAR_GAMEINIT},                              // 27
    {"NumTeams", CVAR_TYPE_INT, &Dedicated_num_teams, 2, 4, CVAR_GAMEINIT},                                   // 28
    {"PXOHostingLobby", CVAR_TYPE_STRING, &PXO_hosted_lobby_name, -1, 100, CVAR_GAMEINIT | CVAR_GAMEPLAY},    // 29
    {"RandomizeRespawn", CVAR_TYPE_INT, &Dummy_dedicated_var, -1, -1, CVAR_GAMEINIT},                         // 30
    {"AllowMouselook", CVAR_TYPE_INT, &Dummy_dedicated_var, -1, -1, CVAR_GAMEINIT},                           // 31
    {"AudioTauntDelay", CVAR_TYPE_FLOAT, NULL, -1, -1, CVAR_GAMEINIT},                                        // 32
    {"SetLevel", CVAR_TYPE_INT, NULL, -1, -1, CVAR_GAMEINIT | CVAR_GAMEPLAY},                                 // 33
    {"SetDifficulty", CVAR_TYPE_INT, NULL, 0, 4, CVAR_GAMEINIT},                                              // 34
    {"MOTD", CVAR_TYPE_STRING, &Multi_message_of_the_day, -1, HUD_MESSAGE_LENGTH * 2, CVAR_GAMEINIT},         // 35
};

#define CVAR_TIMELIMIT 1
#define CVAR_KILLGOAL 2
#define CVAR_QUIT 8
#define CVAR_ENDLEVEL 9
#define CVAR_MAXPLAYERS 10
#define CVAR_MESSAGE 11
#define CVAR_USESMOOTHING 12
#define CVAR_SENDROTVEL 13
#define CVAR_SETTINGS 14
#define CVAR_DISALLOW 15
#define CVAR_ALLOW 16
#define CVAR_STARTLOG 17
#define CVAR_STOPLOG 18
#define CVAR_BRIGHTPLAYERS 21
#define CVAR_PEER2PEER 22
#define CVAR_ACCURATE_COLL 23
#define CVAR_PERMISSABLE 27
#define CVAR_RANDOMIZERESPAWN 30
#define CVAR_ALLOWMOUSELOOKERS 31
#define CVAR_AUDIOTAUNTDELAY 32
#define CVAR_SETLEVEL 33
#define CVAR_SETDIFF 34
#define CVAR_MOTD 35

#define MAX_CVARS (sizeof(CVars) / sizeof(cvar_entry))

// Takes the data that the config file has an runs a server based on that data
// Returns true if ok, false if something is wrong
int RunServerConfigs() {
  // Load the connection DLL
  if (LoadMultiDLL(Netgame.connection_name)) {
    CallMultiDLL(MT_AUTO_START);
    if (!MultiDLLGameStarting) {
      PrintDedicatedMessage(TXT_DS_COULDNTINIT, Netgame.connection_name);
      PrintDedicatedMessage("\n");
      return 0;
    } else {
      PrintDedicatedMessage(TXT_DS_DLLINIT);
      PrintDedicatedMessage("\n");
    }
  } else {
    PrintDedicatedMessage(TXT_DS_CONNECTLOADERR, Netgame.connection_name);
    PrintDedicatedMessage("\n");
    return 0;
  }

  // Put in the correct mission names for the oem builds
#if (defined(OEM) || defined(DEMO))
  if (stricmp("polaris.d3l", Netgame.mission) == 0) {
    strcpy(Netgame.mission_name, "Polaris");
  } else if (stricmp("taurus.d3l", Netgame.mission) == 0) {
    strcpy(Netgame.mission_name, "Taurus");
  } else if (stricmp("thecore.d3l", Netgame.mission) == 0) {
    strcpy(Netgame.mission_name, "The Core");
  }
#else
  const char *p = GetMissionName(Netgame.mission);
  strcpy(Netgame.mission_name, p);
#endif

  // Load the mission
  if (!LoadMission(Netgame.mission)) {
    PrintDedicatedMessage(TXT_DS_LOADMISSIONERR, Netgame.mission);
    PrintDedicatedMessage("\n");
    return 0;
  } else {
    PrintDedicatedMessage(TXT_DS_MISSIONLOADED, Netgame.mission);
    PrintDedicatedMessage("\n");
  }

  if (Current_mission.num_levels >= Dedicated_start_level) {
    Current_mission.cur_level = Dedicated_start_level;
  } else {
    Current_mission.cur_level = 1;
  }
  // Start the actual server

  int teams = CheckMissionForScript(Netgame.mission, Netgame.scriptname, Dedicated_num_teams);

  if (teams == -1) {
    PrintDedicatedMessage(TXT_MSNNOTCOMPATIBLE);
    PrintDedicatedMessage("\n");
    return 0;
  } else {
    MultiStartServer(0, Netgame.scriptname, teams);
    strcpy(Players[0].callsign, TXT_DS_SERVERNAME);
  }

  InitDedicatedSocket(Dedicated_listen_port);

  return 1;
}

int DedicatedServerLex(const char *command) {
  for (int i = 0; i < MAX_CVARS; i++)
    if (stricmp(CVars[i].varname, command) == 0)
      return i;

  return INFFILE_ERROR;
}

// Reads in the server config file for a dedicated server
// Returns true if everything is ok
int LoadServerConfigFile() {
  InfFile inf;
  char operand[INFFILE_LINELEN]; // operand
  int t = FindArgChar("-dedicated", 'd');

  //	int t=FindArg ("-dedicated");
  if (!t) {
    PrintDedicatedMessage(TXT_DS_BADCOMMANDLINE);
    PrintDedicatedMessage("\n");
    return 0;
  }

  // Set our defaults
  MultiResetSettings();

  // Make all ships available
  for (int i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used)
      PlayerSetShipPermission(-1, Ships[i].name, true);
  }

  if (GameArgs[t + 1][0]) {
    strcpy(Netgame.server_config_name, GameArgs[t + 1]);
  } else {
    PrintDedicatedMessage(TXT_DS_MISSINGCONFIG);
    PrintDedicatedMessage("\n");
    return 0;
  }

  //	open file
  if (!inf.Open(Netgame.server_config_name, "[server config file]", DedicatedServerLex)) {
    PrintDedicatedMessage(TXT_DS_BADCONFIG, Netgame.server_config_name);
    PrintDedicatedMessage("\n");
    return 0;
  }

  //	check if valid dedicated server file
  while (inf.ReadLine()) {
    int cmd;

    while ((cmd = inf.ParseLine(operand, INFFILE_LINELEN)) > INFFILE_ERROR) {
      SetCVar(CVars[cmd].varname, operand, true);
    }
  }

  inf.Close();

  if (!RunServerConfigs())
    return 0;

  return 1;
}

// Starts a dedicated server and loads the server config file
void StartDedicatedServer() {
  int t = FindArgChar("-dedicated", 'd');
  // int t=FindArg ("-dedicated");
  if (!t)
    return;

  Dedicated_server = true;
}

// Sets the value for a cvar NONE type
void SetCVarNone(int index) {
  if (CVars[index].type != CVAR_TYPE_NONE)
    return; // Only handles ints

  // Do command specific stuff here
  if (index == CVAR_QUIT) {
    if (NetPlayers[Player_num].sequence == NETSEQ_PLAYING) {
      MultiLeaveGame();
      SetFunctionMode(QUIT_MODE);
    }
  }

  if (index == CVAR_ENDLEVEL) {
    if (NetPlayers[Player_num].sequence == NETSEQ_PLAYING) {
      MultiEndLevel();
    }
  }

  if (index == CVAR_STARTLOG)
    rtp_StartLog();

  if (index == CVAR_STOPLOG)
    rtp_StopLog();
}

// Sets the value for a cvar INT type
void SetCVarInt(int index, int val) {
  void *dest_variable;

  if (CVars[index].type != CVAR_TYPE_INT)
    return; // Only handles ints

  dest_variable = CVars[index].dest_variable;

  if (!(CVars[index].var_min == -1 && CVars[index].var_max == -1)) {
    if (val < CVars[index].var_min)
      val = (int)CVars[index].var_min;

    if (val > CVars[index].var_max)
      val = (int)CVars[index].var_max;
  }

  // Do command specific stuff here
  switch (index) {
  case CVAR_TIMELIMIT: {
    if (val > 0)
      Netgame.flags |= NF_TIMER;
    else
      Netgame.flags &= ~NF_TIMER;
  } break;

  case CVAR_KILLGOAL: {
    if (val > 0)
      Netgame.flags |= NF_KILLGOAL;
    else
      Netgame.flags &= ~NF_KILLGOAL;
  } break;

  case CVAR_MAXPLAYERS: {
    if (val > MAX_PLAYERS)
      val = MAX_PLAYERS;
    else if (val < 2)
      val = 2;

  } break;

  case CVAR_BRIGHTPLAYERS: {
    if (val)
      Netgame.flags |= NF_BRIGHT_PLAYERS;
    else
      Netgame.flags &= ~NF_BRIGHT_PLAYERS;
  } break;

  case CVAR_USESMOOTHING: {
    if (val)
      Netgame.flags |= NF_USE_SMOOTHING;
    else
      Netgame.flags &= ~NF_USE_SMOOTHING;
  } break;

  case CVAR_PEER2PEER: {
    if (val) {
      Netgame.flags |= NF_PEER_PEER;
      Netgame.flags &= ~NF_PERMISSABLE;
    } else
      Netgame.flags &= ~NF_PEER_PEER;
  } break;

  case CVAR_PERMISSABLE: {
    if (val) {
      Netgame.flags |= NF_PERMISSABLE;
      Netgame.flags &= ~NF_PEER_PEER;
    } else
      Netgame.flags &= ~NF_PERMISSABLE;
  } break;

  case CVAR_RANDOMIZERESPAWN: {
    if (val) {
      Netgame.flags |= NF_RANDOMIZE_RESPAWN;
    } else
      Netgame.flags &= ~NF_RANDOMIZE_RESPAWN;
  } break;

  case CVAR_ACCURATE_COLL: {
    if (val)
      Netgame.flags |= NF_USE_ACC_WEAP;
    else
      Netgame.flags &= ~NF_USE_ACC_WEAP;
  } break;

  case CVAR_SENDROTVEL: {
    if (val)
      Netgame.flags |= NF_SENDROTVEL;
    else
      Netgame.flags &= ~NF_SENDROTVEL;
  } break;
  case CVAR_SETLEVEL: {
    if (NetPlayers[Player_num].sequence == NETSEQ_PLAYING) {
      if (val >= 1 && val <= Current_mission.num_levels) {
        Multi_next_level = val;
        MultiEndLevel();
      }
    } else {
      if (val >= 1) {
        Dedicated_start_level = val;
      }
    }
  } break;
  case CVAR_ALLOWMOUSELOOKERS: {
    if (val)
      Netgame.flags |= NF_ALLOW_MLOOK;
    else
      Netgame.flags &= ~NF_ALLOW_MLOOK;
  } break;
  case CVAR_SETDIFF: {
    Netgame.difficulty = val;
  } break;
  }

  if (dest_variable)
    *((int *)dest_variable) = val;
}

// Sets the value for a cvar FLOAT type
void SetCVarFloat(int index, float val) {
  void *dest_variable;

  if (CVars[index].type != CVAR_TYPE_FLOAT)
    return; // Only handles ints

  dest_variable = CVars[index].dest_variable;

  if (!(CVars[index].var_min == -1 && CVars[index].var_max == -1)) {
    if (val < CVars[index].var_min)
      val = (float)CVars[index].var_min;

    if (val > CVars[index].var_max)
      val = (float)CVars[index].var_max;
  }

  if (dest_variable)
    *((float *)dest_variable) = val;

  // Do command specific stuff here
  switch (index) {
  case CVAR_AUDIOTAUNTDELAY:
    MultiSetAudioTauntTime(val);
    break;
  }
}
// Sets the value for a cvar string type
void SetCVarString(int index, const char *val) {
  void *dest_variable;

  if (CVars[index].type != CVAR_TYPE_STRING)
    return; // Only handles ints

  if (index == CVAR_MESSAGE) {
    // say the message to everyone
    char str[255];

    int to_whom;
    const char *msg = GetMessageDestination(val, &to_whom);

    if (to_whom != MULTI_SEND_MESSAGE_ALL)
      val = msg;

    std::snprintf(str, sizeof(str), TXT_HUDSAY, Players[Player_num].callsign, val);

    MultiSendMessageFromServer(GR_RGB(0, 128, 255), str, to_whom);

    return;
  }

  if (index == CVAR_SETTINGS) {
    if (MultiLoadSettings(val)) {
      PrintDedicatedMessage(TXT_DS_SETTINGSLOADED);
      PrintDedicatedMessage("\n");
    } else {
      PrintDedicatedMessage(TXT_DS_SETTINGSERR);
      PrintDedicatedMessage("\n");
    }
  }

  if (index == CVAR_DISALLOW) {
    int objid = FindObjectIDName(IGNORE_TABLE(val));
    if (objid != -1) {
      PrintDedicatedMessage(TXT_DS_DISALLOWOBJECT, Object_info[objid].name);
      PrintDedicatedMessage("\n");
      Object_info[objid].multi_allowed = 0;
    }
  }

  if (index == CVAR_ALLOW) {
    int objid = FindObjectIDName(IGNORE_TABLE(val));
    if (objid != -1) {
      PrintDedicatedMessage(TXT_DS_ALLOWOBJECTS, Object_info[objid].name);
      PrintDedicatedMessage("\n");
      Object_info[objid].multi_allowed = 1;
    }
  }

  dest_variable = CVars[index].dest_variable;

  if (dest_variable) {
    strncpy((char *)dest_variable, val, CVars[index].var_max);
  }
}

// The accessor function that sets the value of a cvar
void SetCVar(const char *cvar_string, const char *cvar_argument, bool game_init) {
  int i;
  int done = 0;

  for (i = 0; i < MAX_CVARS && !done; i++) {
    if (!(stricmp(cvar_string, CVars[i].varname))) {
      done = 1;

      if (game_init) {
        if (!(CVars[i].permissions & CVAR_GAMEINIT)) {
          PrintDedicatedMessage(TXT_DS_CANTUSEINIT);
          PrintDedicatedMessage("\n");
          continue;
        }

      } else {
        if (!(CVars[i].permissions & CVAR_GAMEPLAY)) {
          PrintDedicatedMessage(TXT_DS_CANTUSEPLAY);
          PrintDedicatedMessage("\n");
          continue;
        }
      }

      if (CVars[i].type != CVAR_TYPE_NONE && i != CVAR_MESSAGE) {
        PrintDedicatedMessage(TXT_DS_VARSET, cvar_string, cvar_argument);
        PrintDedicatedMessage("\n");
      }

      switch (CVars[i].type) {
      case CVAR_TYPE_INT: {
        int val = atoi(cvar_argument);
        SetCVarInt(i, val);
      } break;
      case CVAR_TYPE_NONE: {
        SetCVarNone(i);
      } break;
      case CVAR_TYPE_FLOAT: {
        float val = (float)atof(cvar_argument);
        SetCVarFloat(i, val);
      } break;
      case CVAR_TYPE_STRING: {
        SetCVarString(i, cvar_argument);
      } break;
      default:
        Int3(); // Get Jason, no cvar argument defined
        break;
      }
    }
  }
}

// The accessor function that sets the value of a cvar...INT only
void SetCVar(const char *cvar_string, int cvar_argument) {
  int i;
  int done = 0;

  for (i = 0; i < MAX_CVARS && !done; i++) {
    if (!(stricmp(cvar_string, CVars[i].varname))) {
      done = 1;
      switch (CVars[i].type) {
      case CVAR_TYPE_INT: {
        SetCVarInt(i, cvar_argument);
      } break;

      default:
        Int3(); // You are using the wrong accessor function...this is for INTS only!
        break;
      }
    }
  }
}

// The accessor function that sets the value of a cvar...FLOAT only
void SetCVar(const char *cvar_string, float cvar_argument) {
  int i;
  int done = 0;

  for (i = 0; i < MAX_CVARS && !done; i++) {
    if (!(stricmp(cvar_string, CVars[i].varname))) {
      done = 1;
      switch (CVars[i].type) {
      case CVAR_TYPE_FLOAT: {
        SetCVarFloat(i, cvar_argument);
      } break;

      default:
        Int3(); // You are using the wrong accessor function...this is for INTS only!
        break;
      }
    }
  }
}

void ParseLine(char *srcline, char *command, char *operand, int cmdlen, int oprlen) {
  //	tokenize line.
  char *opr, *cmd;

  if (strlen(srcline) == 0)
    return;

  //	parse out command and operand (command=str)
  //	m_lineptr = command, opr = operand, nextcmd = next lineptr.
  cmd = strtok(srcline, " \t=:");
  if (cmd)
    opr = strtok(NULL, "");
  else
    return; // null command, so bail

  //	clean out trailing and preceeding trash (tabs, spaces, etc)
  CleanupStr(command, cmd, cmdlen);
  if (opr)
    CleanupStr(operand, opr, oprlen);
  else
    operand[0] = 0;
}

// Called once per frame for the dedicated server
void DoDedicatedServerFrame() {
  char str[255];
  char command[255] = {}; // operand
  char operand[255];      // operand

  ListenDedicatedSocket();
  DedicatedReadTelnet();

  // CallGameDLL (EVT_GAME_INTERVAL,&DLLInfo);

  if (ServerTimeout) {
    float now = timer_GetTime();
    int sincelastpacket = ((float)(now - LastPacketReceived)) / 60;
    // See if it's time to shutdown...
    if (sincelastpacket > ServerTimeout) {
      int quitno = DedicatedServerLex("Quit");
      if (quitno >= 0)
        SetCVar(CVars[quitno].varname, "", false);
    }
  }

  bool new_command = con_Input(str, 255);

  if (!new_command)
    return;

  if (str[0] == '$') {
    DLLInfo.input_string = str;
    CallGameDLL(EVT_CLIENT_INPUT_STRING, &DLLInfo);
    return;
  }

  ParseLine(str, command, operand, 255, 255);

  if (!command[0])
    return;

  int index = DedicatedServerLex(command);

  if (index < 0) {
    PrintDedicatedMessage(TXT_DS_BADCOMMAND);
    PrintDedicatedMessage("\n");
    return;
  }

  // Everything ok, set command
  SetCVar(CVars[index].varname, operand, false);
}

// Prints a message to the console if the dedicated server is active
void PrintDedicatedMessage(const char *fmt, ...) {
  if (!Dedicated_server)
    return;

  char buf[CON_MAX_STRINGLEN];
  std::va_list args;

  va_start(args, fmt);
  std::vsnprintf(buf, CON_MAX_STRINGLEN, fmt, args);
  va_end(args);

  con_Printf(buf);
  DedicatedSocketputs(buf);
}

#ifdef __LINUX__
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "linux_fix.h"
#include "errno.h"
#define BOOL bool
#ifndef SOCKET
#define SOCKET int
#endif
#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr
#define INVALID_SOCKET -1

// Winsock = sockets error translation

#define WSAEWOULDBLOCK EWOULDBLOCK
#define WSAEINVAL EINVAL
#define WSAENOPROTOOPT ENOPROTOOPT

#ifndef WSAGetLastError
#define WSAGetLastError() errno
#endif

#define SOCKET_ERROR -1

#endif

struct dedicated_socket {
  SOCKET sock;
  SOCKADDR_IN addr;
  char input[255];
  bool validated;
  dedicated_socket *prev;
  dedicated_socket *next;
};

dedicated_socket *Head_sock = NULL;

SOCKET dedicated_listen_socket = INVALID_SOCKET;

#define DEDICATED_LOGIN_PROMPT TXT_DS_ENTERPASS

void InitDedicatedSocket(uint16_t port) {
  SOCKADDR_IN sock_addr;

  memset(&sock_addr, 0, sizeof(SOCKADDR_IN));
  sock_addr.sin_family = AF_INET;
  uint32_t my_ip;
  my_ip = nw_GetThisIP();
  memcpy(&sock_addr.sin_addr.s_addr, &my_ip, sizeof(uint32_t));
  sock_addr.sin_port = htons(port);

  dedicated_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (INVALID_SOCKET == dedicated_listen_socket) {
    mprintf(0, "Unable to create listen socket for dedicated server!\n");
    return;
  }
  if (SOCKET_ERROR == bind(dedicated_listen_socket, (SOCKADDR *)&sock_addr, sizeof(sock_addr))) {
    mprintf(0, "Unable to bind listen socket for dedicated server!\n");
    return;
  }
  if (listen(dedicated_listen_socket, 1)) {
    mprintf(0, "Unable to listen on dedicated server socket!\n");
    return;
  }
  make_nonblocking(dedicated_listen_socket);
}

void ListenDedicatedSocket(void) {
  SOCKET incoming_socket;
  SOCKADDR_IN conn_addr;
  //	int addrlen = sizeof(conn_addr);
  socklen_t addrlen = sizeof(conn_addr);
  incoming_socket = accept(dedicated_listen_socket, (SOCKADDR *)&conn_addr, &addrlen);
  if (INVALID_SOCKET != incoming_socket) {
    // Make the socket non-blocking

    make_nonblocking(incoming_socket);

    if (!Dedicated_allow_remote) {
      // Check to see if this came in from the local address
      uint32_t localhost = inet_addr("127.0.0.1");
      if (memcmp(&localhost, &conn_addr.sin_addr, sizeof(localhost)) != 0) {
        mprintf(0, "Rejecting connection from remote host!\n");
        PrintDedicatedMessage(TXT_DS_REJECTREMOTE, inet_ntoa(conn_addr.sin_addr));
        PrintDedicatedMessage("\n");
        shutdown(incoming_socket, 2);
#if defined(WIN32)
        closesocket(incoming_socket);
#else
        close(incoming_socket);
#endif
        return;
      }
    }
    // At this point it's considered a valid connection
    PrintDedicatedMessage(TXT_DS_NEWCONNECT, inet_ntoa(conn_addr.sin_addr));
    PrintDedicatedMessage("\n");
    dedicated_socket *new_socket;
    new_socket = (dedicated_socket *)mem_malloc(sizeof(dedicated_socket));
    if (Head_sock)
      Head_sock->prev = new_socket;
    new_socket->next = Head_sock;
    new_socket->prev = NULL;
    Head_sock = new_socket;
    memcpy(&new_socket->addr, &conn_addr, sizeof(new_socket->addr));
    new_socket->input[0] = '\0';
    new_socket->sock = incoming_socket;
    new_socket->validated = false;
    // Give the new connection the login prompt
    send(new_socket->sock, DEDICATED_LOGIN_PROMPT, strlen(DEDICATED_LOGIN_PROMPT) + 1, 0);
  }
}

void DedicatedSocketputs(char *str) {
  char newstr[300];
  char buf[2];

  memset(newstr, 0, 300);
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '\n') {
      strcat(newstr, "\r\n");
    } else {
      buf[0] = str[i];
      buf[1] = '\0';
      strcat(newstr, buf);
    }
  }

  dedicated_socket *conn;
  conn = Head_sock;
  while (conn) {
    if (conn->validated) {
      send(conn->sock, newstr, strlen(newstr) + 1, 0);
    }
    conn = conn->next;
  }
}

dedicated_socket *DedicatedLogoutTelnet(dedicated_socket *conn) {
  // user is no longer valid (so we don't attempt to send them a message
  conn->validated = false;

  PrintDedicatedMessage(TXT_DS_REMOTECLOSE, inet_ntoa(conn->addr.sin_addr));
  PrintDedicatedMessage("\n");

  shutdown(conn->sock, 2);
#if defined(WIN32)
  closesocket(conn->sock);
#else
  close(conn->sock);
#endif

  dedicated_socket *prev;
  prev = conn->prev;
  if (prev) {
    prev->next = conn->next;
  } else {
    Head_sock = conn->next;
    if (Head_sock)
      Head_sock->prev = NULL;
  }

  mem_free(conn);
  return prev;
}

void DedicatedReadTelnet(void) {
  dedicated_socket *conn;
  char buf[5];
  conn = Head_sock;

  while (conn) {
    int bytesread = 1;
    while (bytesread >= 0 && conn) {
      // Read one byte at a time, looking for a CR
      bytesread = recv(conn->sock, buf, 1, 0);
      if (bytesread == 0) {
        // Connection closed. Remove it from the list, and inform the other(?) users.
        conn = DedicatedLogoutTelnet(conn);
        break;
      } else if (bytesread > 0) {
        buf[1] = '\0';
        // When we see a CR, process the line
        if ((buf[0] == 0x0a) || (buf[0] == 0x0d)) {
          if (conn->input[0] == 0) {
            continue;
          }
          send(conn->sock, "\r\n", strlen("\r\n"), 0);
          if (conn->validated) {
            char command[255] = {}; // operand
            char operand[255];      // operand

            if (!stricmp(conn->input, "logout")) {
              // log the connection out
              conn = DedicatedLogoutTelnet(conn);
            } else {
              // Process the string
              PrintDedicatedMessage("[%s] %s\n", inet_ntoa(conn->addr.sin_addr), conn->input);
              if (conn->input[0] == '$') {
                DLLInfo.input_string = conn->input;
                CallGameDLL(EVT_CLIENT_INPUT_STRING, &DLLInfo);
                conn->input[0] = '\0';
                return;
              }

              ParseLine(conn->input, command, operand, 255, 255);
              conn->input[0] = '\0';
              if (!command[0])
                return;

              int index = DedicatedServerLex(command);

              if (index < 0) {
                PrintDedicatedMessage(TXT_DS_BADCOMMAND);
                PrintDedicatedMessage("\n");
                return;
              }

              // Everything ok, set command
              SetCVar(CVars[index].varname, operand, false);
            }
          } else {
            // All we want to see from them is the correct password
            if (strcmp(conn->input, dedicated_telnet_password) == 0) {
              // They logged in ok!
              conn->validated = true;
              send(conn->sock, "\r\n", strlen("\r\n") + 1, 0);
              PrintDedicatedMessage(TXT_DS_REMOTELOGGEDIN, inet_ntoa(conn->addr.sin_addr));
              PrintDedicatedMessage("\n");
              conn->input[0] = '\0';
            } else {
              PrintDedicatedMessage(TXT_DS_BADPASS, inet_ntoa(conn->addr.sin_addr));
              PrintDedicatedMessage("\n");
              shutdown(conn->sock, 2);
#if defined(WIN32)
              closesocket(conn->sock);
#else
              close(conn->sock);
#endif
            }
          }
        } else {
          if (buf[0] == 8) {
            // handle backspace
            char delstr[5];
            delstr[0] = 8;
            delstr[1] = ' ';
            delstr[2] = 8;
            delstr[3] = '\0';
            conn->input[strlen(conn->input) - 1] = '\0';
            buf[1] = '\0';
            send(conn->sock, delstr, strlen(delstr), 0);
          } else {
            if (strlen(conn->input) + bytesread >= sizeof(conn->input)) {
              conn->input[0] = 0;
              const char *s = "\n\rCommand line too long\n\r";
              send(conn->sock, s, strlen(s), 0);
            } else {
              strcat(conn->input, buf);
              send(conn->sock, buf, 1, 0);
            }
          }
        }
      }
    }
    if (conn)
      conn = conn->next;
  }
}
