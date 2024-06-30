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

 * $Logfile: /DescentIII/Main/player.h $
 * $Revision: 101 $
 * $Date: 9/29/01 5:34p $
 * $Author: Kevin $
 *
 * Header for player.cpp
 *
 * $Log: /DescentIII/Main/player.h $
 *
 * 101   9/29/01 5:34p Kevin
 * hack to prevent the observermode powerup stealing cheat/bug
 *
 * 100   5/20/99 2:48a Matt
 * Auto-waypoints now stored & used per player.  Manual waypoints will all
 * players, once Jason makes it work.
 *
 * 99    4/24/99 6:45p Jeff
 * added functions for theif so he can steal things other than weapons
 *
 * 98    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 97    4/06/99 6:02p Matt
 * Added score system
 *
 * 96    4/05/99 3:34p Matt
 * Cleaned up player start flags
 *
 * 95    4/05/99 10:54a Matt
 * Added auto-waypoint system
 *
 * 94    3/08/99 5:14p Jason
 * added delay to player respawn after death
 *
 * 93    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 92    2/25/99 8:55p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 91    2/11/99 1:22a Jeff
 * made function to switch a player into AI mode, converted code that did
 * this to call this function.
 *
 * 90    2/09/99 6:53p Jeff
 * implemented 'typing inidcator' in multiplayer...players that are typing
 * messages have an icon on them
 *
 * 89    2/08/99 3:06a Jeff
 * added a function to reset a player's control type
 *
 * 88    1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 87    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 86    1/19/99 9:20a Kevin
 * Added afterburner masking
 *
 * 85    1/18/99 6:18p Kevin
 * Added controller masking to DALLAS
 *
 * 84    1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 83    12/01/98 3:35p Matt
 * Got rear view working.
 *
 * 82    11/23/98 1:50p Jason
 * added thruster sounds
 *
 * 81    11/13/98 4:25p Jason
 * changes for better weapon effects
 *
 * 80    11/13/98 12:30p Jason
 * changes for weapons
 *
 * 79    11/11/98 7:18p Jeff
 * changes made so that a dedicated server's team is always -1 (team game
 * or not)
 *
 * 78    11/03/98 6:16p Chris
 * Starting to make on/off and spray weapons accessable to robots
 *
 * 77    9/23/98 2:55p Chris
 * Improved auto-leveling and added newbie leveling
 *
 * 76    9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 75    9/16/98 5:10p Jason
 * added first pass at thrid-person camera system
 *
 * 74    9/11/98 12:26p Jason
 * got energy to shield and fusion damage working in multiplayer
 *
 * 73    9/10/98 12:18p Jason
 * more changes to afterburner/thrust effect
 *
 * 72    8/28/98 1:34p Matt
 * Added code to reset the waypoint when starting a new level, and while I
 * was at it cleaned up the new level start sequencing.
 *
 * 71    8/24/98 2:45p Jason
 * added team start position stuff
 *
 * 70    8/24/98 12:24p Jason
 * added waypoints and player start position flags
 *
 * 69    8/19/98 6:27p Chris
 * Added a last_fired_time for the player (used for AI and cloaking)
 *
 * 68    8/16/98 12:19a Jeff
 * added energy->shields function
 *
 * 67    8/10/98 2:21p Jeff
 * changes made due to adding flag for inventory reset
 *
 * 66    8/06/98 2:44p Jeff
 * added ship permissions functions (first round)
 *
 * 65    8/03/98 5:56p Jason
 * got fusion cannon working correctly
 *
 * 64    7/31/98 1:55p Jason
 * added a function for custom textures
 *
 * 63    7/31/98 11:51a Jason
 * added player ship choosing to multiplayer games
 *
 * 62    7/22/98 3:16p Jason
 * added observer mode
 *
 * 61    7/20/98 6:39p Jason
 * first attempt at getting player visibilty stuff working in multiplayer
 *
 * 60    7/20/98 10:42a Jason
 * added more player scalars, plus afterburner changes
 *
 * 59    7/15/98 2:33p Jason
 * added scalar variables for various player skills
 *
 * 58    7/03/98 3:09p Jeff
 * added  counter measures inventory
 *
 * 57    7/02/98 6:30p Jason
 * added some multiplayer stuff for Jeff
 *
 * 56    6/29/98 3:08p Jason
 * added on/off weapons
 *
 * 55    6/25/98 5:17p Jason
 * added multiple colored balls for players
 *
 * 54    6/25/98 12:45p Jeff
 * fixed callsign length, it was too int16_t
 *
 * 53    5/26/98 7:49p Samir
 * E3 version has a long afterburner.
 *
 * 52    5/25/98 8:17p Matt
 * Moved MAX_PLAYER_WEAPONS fromw weapon.h to player.h, so that the latter
 * doesn't need to include the former, drastically speeding build times
 * when weapon.h is changed.
 *
 * 51    5/12/98 5:09p Kevin
 * Added fields to player to keep more mastertracker stats
 *
 * 50    5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 49    5/01/98 6:50p Samir
 * changed death sequence to fall on melee kill (single player) and death
 * camera improvements.
 *
 * 48    4/30/98 2:53p Kevin
 * added suicide to players
 *
 * 47    4/30/98 1:15p Kevin
 * Added lifetime deaths and kills for MT
 *
 * 46    4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 45    4/29/98 12:51p Kevin
 * Added mastertracker values
 *
 * 44    4/27/98 1:14p Jason
 * cleaned up afterburner stuff
 *
 * 43    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 42    4/13/98 12:42p Jason
 * changed afterburner effect
 *
 * 41    4/09/98 5:18p Jason
 * got guided working in multiplayer
 *
 * 40    4/09/98 2:23p Jason
 * added guided/afterburner stuff
 *
 * 39    4/06/98 12:14p Jason
 * changes to multiplayer
 *
 * 38    4/03/98 12:28p Jason
 * fixed confusion with clients changing rooms in multiplayer
 *
 * 37    4/01/98 2:13p Jason
 * added PlayerChangeShip
 *
 * 36    4/01/98 12:02p Jason
 * incremental checkin for rendering changes
 *
 * 35    3/31/98 11:15a Jason
 * added the ability for player objects to cast light
 *
 * 34    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 33    3/20/98 3:54p Chris
 * Working on adding sounds to the game.  :)
 *
 * 32    3/20/98 2:59p Chris
 * Added a wall hit sound for the player and added support for a base
 * volume for 3d sounds
 *
 * 31    3/18/98 5:45p Jason
 * more multiplayer script integration
 *
 * 30    3/17/98 3:25p Jason
 * added number of team functions
 *
 * 29    3/17/98 11:22a Jason
 * added GetGoalRoom functions
 *
 * 28    3/16/98 3:53p Jason
 * added team field to player struct
 *
 * 27    2/17/98 3:41p Matt
 * Revamped weapon system and got sounds for spray and fusion weapons
 * working.  Still need to implements getting continuous & cutoff sounds
 * from player ship.
 *
 * 26    2/11/98 4:54p Jeff
 * Moved the inventory into the Player struct
 *
 * 25    2/06/98 6:07p Jason
 * made multiplayer objects get deleted in single-player mode
 *
 * 24    2/05/98 3:03p Matt
 * Changed comment
 *
 * 23    1/28/98 1:12p Jason
 * took shields field out of Player struct
 *
 * 22    1/28/98 12:00p Jason
 * more changes for multiplayer
 *
 * 21    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 20    1/23/98 11:21a Jason
 * incremental multiplayer checkin
 *
 * 19    1/21/98 6:09p Jason
 * Got player deaths working in multiplayer
 *
 * 18    1/21/98 3:08p Samir
 * Added slot to StartPlayerExplosion.
 *
 * 17    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 16    1/20/98 6:35p Samir
 * Death sequence more multiplayer friendly?
 *
 * 15    1/20/98 6:01p Jason
 * first pass at getting multiplayer deaths working
 *
 * 14    1/07/98 6:39p Jason
 * Fixed player object number stuff
 *
 * 13    12/18/97 3:49p Jason
 * a new first pass at networking!
 *
 * 12    11/14/97 2:59p Mark
 * FROM JASON:changed the way paging weapons and player weapons work
 *
 * 11    11/04/97 6:18p Chris
 * Added support so that the player ship uses the robot's firing dialog.
 *
 * 10    10/22/97 7:26p Samir
 * Player death mostly working.   Damn hangup still occurs.  Freaky.
 *
 * 9     10/21/97 3:16p Samir
 * Death with explosions (not customized yet.)
 *
 * 8     10/08/97 6:36p Samir
 * Except for player explosions, player death cycle implemented.  May
 * change due to asthetics.
 *
 * 7     10/03/97 11:59a Samir
 * Take care of setting player weapon usage stats.
 *
 * 6     10/01/97 4:51p Samir
 * Moved ApplyDamagePlayer to damage.cpp
 *
 * 5     9/17/97 11:35a Samir
 * BIG SEGMENT RIPOUT
 *
 * 4     9/12/97 4:16p Samir
 * Added cloaking and invulnerability.
 *
 * 3     9/05/97 2:34p Samir
 * Simple player death should work.
 *
 * 2     9/05/97 12:26p Samir
 * Player takes damage, and dies.
 *
 * 7     5/06/97 12:53p Matt
 * Save over terrain flag with start position in player struct
 *
 * 6     4/23/97 6:06p Jason
 * made player ship and weapons work correctly together (first pass)
 *
 * 5     4/17/97 2:55p Jason
 * added many D2 like fields to the player structure
 *
 * 4     4/02/97 4:00p Jason
 * added ship_index field to player struct
 *
 * 3     4/01/97 10:49p Matt
 * Deleted obsolete player_ship stuff, and added player stuff
 *
 * $NoKeywords: $
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "pstypes.h"
#include "Inventory.h"

#include "robotfirestruct.h"
#include "object_external_struct.h"
#include "player_external_struct.h"
#include "player_external.h"

#define MAX_WAYPOINTS 25

#define INITIAL_LIVES 3 // start off with 3 lives

// For energy to shields conversion
#define CONVERTER_RATE 20.0f       // 10 units per second xfer rate
#define CONVERTER_SCALE 2.0f       // 2 units energy -> 1 unit shields
#define CONVERTER_SOUND_DELAY 0.5f // play every half second

// How long afterburner lasts before it has to be recharged
#ifdef E3_DEMO
#define AFTERBURN_TIME 5000.0
#else
#define AFTERBURN_TIME 5.0
#endif

// Player start position flags
#define PSPF_RED 1
#define PSPF_BLUE 2
#define PSPF_GREEN 4
#define PSPF_YELLOW 8

struct player_pos_suppress {
  int room;
  float expire_time;
  int ignored_pos;
  bool active;
};

#define PLAYER_POS_HACK_TIME 10

extern std::array<player_pos_suppress, MAX_PLAYERS> Player_pos_fix;

struct team {
  char name[CALLSIGN_LEN + 1];
  int score;
};

extern int Player_num;
extern int Default_ship_permission;

// the object which is the person playing the game
extern object *Player_object;

extern int Num_teams, Team_game;
extern std::array<player, MAX_PLAYERS> Players;
extern std::array<team, MAX_TEAMS> Teams;
extern float HudNameTan;
extern int Current_waypoint;

extern bool Player_has_camera;
extern int Player_camera_objnum;
extern uint32_t Players_typing; // information about which players are typing messages (to display an icon)

extern float Player_shields_saved_from_last_level;
extern float Player_energy_saved_from_last_level;

// How long a player must be dead before he can respawn
#define DEATH_RESPAWN_TIME 3.0f
extern float Total_time_dead;

// Stuff for the new score info on the HUD
extern int Score_added;         // the recently-added amount
extern float Score_added_timer; // how long the added value will be displayed
#define SCORE_ADDED_TIME 2.0    // how long new score info stays on the screen

// Sets up players array
void InitPlayers();

// Look for player objects & set player starts
extern void FindPlayerStarts();

// Resets all the properties a player ship to the default values
// Pass in what kind of reset the inventory should do INVRESET_
void InitPlayerNewShip(int slot, int inven_reset);

//	makes the player invulnerable
void MakePlayerInvulnerable(int slot, float time, bool play_sound_and_message = false);

//	makes the player invulnerable
void MakePlayerVulnerable(int slot);

//	Performs the player death sequence.
void InitiatePlayerDeath(object *playerobj, bool melee = false, int fate = -1);

//	Forces end to player death
void EndPlayerDeath(int slot);

//	Detaches a subobject from the player ship
void DeadPlayerShipHit(object *obj, vector *hitpt, float magnitude);

//	Do actions for the player each frame
void DoPlayerFrame();

//	Force player to explode (this should be called to intercept the death sequencer's control of explosions
void StartPlayerExplosion(int slot);

// Resets the player object in a mine to stop moving
void ResetPlayerObject(int slot, bool f_reset_pos = true);

// Makes the player into an AI controlled physics object
void PlayerSetControlToAI(int slot, float velocity = 75.0f);

// Resets a player's control type back to it's default setting
void ResetPlayerControlType(int slot);

void InitPlayerNewGame(int slot);

// Called from a single player game to get rid of all multiplayer ships
void DeleteMultiplayerObjects();

// Sets the maximum number of teams in a game
void SetMaxTeams(int num);

// Returns the goal room of the passed in team
int GetGoalRoomForTeam(int teamnum);

// Returns the goal room of the passed in player
int GetGoalRoomForPlayer(int slot);

// Moves a player to a specified start position
void PlayerMoveToStartPos(int slot, int start_slot);

// Returns a random player starting position
int PlayerGetRandomStartPosition(int slot);

// Increases the team score by an amount, returning the new total
int IncTeamScore(int, int);

// Resets the scores for all the teams
void ResetTeamScores();

// Sets the lighting that a player will cast
void PlayerSetLighting(int slot, float dist, float r, float g, float b);

// Sets a wacky rotating ball around the player ship
void PlayerSetRotatingBall(int slot, int num, float speed, float *r, float *g, float *b);

// Gets the position of a given ball in world coords
void PlayerGetBallPosition(vector *dest, int slot, int num);

// Spews the inventory of the passed in player object
void PlayerSpewInventory(object *obj, bool spew_energy_and_shield = true, bool spew_nonspewable = false);

// Changes the ship a particular player is flying
void PlayerChangeShip(int slot, int ship_index);

// Called when a player is entering a new level
void InitPlayerNewLevel(int slot);

// Sets the FOV range at which the hud names will come on
void PlayerSetHUDNameFOV(int fov);

// Switches a player object to observer mode
void PlayerSwitchToObserver(int slot, int observer_mode, int piggy_objnum = 0);

// Stops a player from observing
void PlayerStopObserving(int slot);

// Sets the players custom texture.  If filename=NULL then sets to no texture
// Returns 1 if filename was successfully loaded, else 0
int PlayerSetCustomTexture(int slot, char *filename);

// Chooses the style of death a player is going to use
int PlayerChooseDeathFate(int slot, float damage, bool melee);

//	Sets/Clears a permission for a ship on a given player
//	if pnum is -1 then all players will be set, else player is the player number
//	returns true on success
bool PlayerSetShipPermission(int pnum, char *ship_name, bool allowed);

//	Resets the ship permissions for a given player
//	pass false for set_default if you don't want the default ship allowed
bool PlayerResetShipPermissions(int pnum, bool set_default);

//	Returns true if the given ship is allowed to be chosen for a pnum
bool PlayerIsShipAllowed(int pnum, char *ship_name);
bool PlayerIsShipAllowed(int pnum, int ship_index);

// Performs the energy->shields tranfer (for the powerup) given the playernum, call this while player
// is holding down the e->s key.
void DoEnergyToShields(int pnum);

// Stop sounds for this player
void PlayerStopSounds(int slot);

// Sets the start position that the player will respawn at
void PlayerAddWaypoint(int index);

// Resets the waypoints (for new level)
void ResetWaypoint();

// Find all the waypoint objects and add them to the list of waypoints
void MakeAtuoWaypointList();

// Sets the auto-waypoint in the object's room to be current
void SetAutoWaypoint(object *objp);

// Returns the team (0 to 3) of the given player
static inline int PlayerGetTeam(int pnum) {
  if (Players[pnum].team == -1) {
    // special "no-team" for Dedicated server
    return 0; // fake a red team
  }

  return Players[pnum].team;
}

// Add the player's score
void PlayerScoreAdd(int playernum, int points);

// steals an item from the given player
void ThiefStealItem(int player_object_handle, int item);
// returns a stolen item to a player
void ThiefReturnItem(int player_object_handle, int item);
// returns true if a player has the specified item to be stolen
bool ThiefPlayerHasItem(int player_object_handle, int item);
#endif
