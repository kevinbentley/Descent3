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

 * $Logfile: /DescentIII/Data/scripts/DallasFuncs.cpp $
 * $Revision: 1.1 $
 * $Date: 2000-04-18 01:45:34 $
 * $Author: icculus $
 *
 * Definitions for the D3 actions & queries for Dallas
 *
 * $Log: not supported by cvs2svn $
 *
 * 214   10/27/99 4:19p Josh
 * upped timer handle count once again to 50
 *
 * 213   10/23/99 2:56p Chris
 * Fixed the place object on object goal
 *
 * 212   10/23/99 2:42a Chris
 * Added the PutObjectOnObject AI Goal
 *
 * 211   10/17/99 9:04p Samir
 * added a complex cinematic function for moving camera to position from
 * position on the clipboard.
 *
 * 210   10/16/99 9:56p Jeff
 * added a way to strip all players of all weapons and energy
 *
 * 209   10/16/99 8:44p Jeff
 * created an action to remove all powerups from a room.  Created an
 * action to strip a player of all weapons
 *
 * 208   10/15/99 6:05p Samir
 * added a query for max speed of an object.
 *
 * 207   10/12/99 12:43p Jeff
 * added actions and queries for virus infection and negative light
 *
 * 206   10/08/99 4:15p Samir
 * added frametime query
 *
 * 205   5/20/99 4:11p Jeff
 * null terminate string for message when adding to inventory correctly
 * (\0 not 0)
 *
 * 204   5/20/99 3:12p Chris
 * Fixed bug in blockage code
 *
 * 203   5/19/99 4:57p Matt
 * Added an action & a query.
 *
 * 202   5/19/99 2:55p Chris
 * Fixed bug with aAISetTarget
 *
 * 201   5/19/99 12:25p Chris
 * Added new functions
 *
 * 200   5/19/99 11:25a Matt
 * Added multisafe functions & Dallas actions for showing a timer on the
 * screen and adding custom HUD messages.
 *
 * 199   5/11/99 5:17p Jeff
 * added query to get difficulty level
 *
 * 198   5/11/99 11:49a Matt
 * Added the ability to specify a name when adding an item to the
 * inventory.
 *
 * 197   5/08/99 10:10p Nate
 * Fixed Level Goal Item index problem
 *
 * 196   5/08/99 2:39p Chris
 * Added a new function for dallas
 *
 * 195   5/07/99 11:56p Matt
 * Added an action to give a player an "invisible" key -- one that doesn't
 * get added to the inventory or shown on the HUD.
 *
 * 194   5/07/99 8:22p 3dsmax
 * Fixed goal query bugs
 *
 * 193   5/07/99 7:22p Chris
 * Added some level goal querys
 *
 * 192   5/07/99 2:58p Matt
 * Increased the maximum number of timer handles from 20 to 40.
 *
 * 191   5/06/99 4:11a Jeff
 * created multisafe function to destroy robots in the level (helps boss
 * fights)
 *
 * 190   5/04/99 6:52p Jeff
 * added new canned cinematic to fade screen to white and endlevel.  Fixed
 * crash bug with invalid player path for canned cine with player paths
 *
 * 189   5/04/99 12:13p Matt
 * Renamed fire-flare symbol to fire-weapon.
 *
 * 188   5/04/99 1:05a Matt
 * Added new fire weapon function, and added a #define to make the old
 * fire flare function use it.
 *
 * 187   5/02/99 1:36a Jason
 * added moving object lighting viseffects
 *
 * 186   4/30/99 6:52p Matt
 * Changed comment
 *
 * 185   4/30/99 6:51p Matt
 * Added a query to check if an object is on the terrain.
 *
 * 184   4/30/99 4:32p Matt
 * Added a Dallas action to fire a flare from an object.
 *
 * 183   4/29/99 4:50p Jeff
 * fixed evil evil merge problems
 *
 * 182   4/29/99 12:30p Chris
 * Dumb bug (Follow path simple now takes and USES the priority field)
 *
 * 181   4/29/99 1:59a Chris
 * Added the portal blockage support
 *
 * 179   4/28/99 7:34p Matt
 * Increased the number of spew handles from 20 to 50.
 *
 * 178   4/28/99 5:15p Jeff
 * fixed bug with adding items to inventory...should not timeout on spew
 * for spewable
 *
 * 177   4/27/99 5:37p Matt
 * Added action to set/clear physics flags for an object.
 *
 * 176   4/26/99 10:35p Chris
 *
 * 175   4/26/99 1:43p Chris
 *
 * 174   4/26/99 1:40p Nate
 * Fixed bug with undeclared 'ctype' identifier
 *
 * 173   4/26/99 11:11a Chris
 * Added a new function
 *
 * 172   4/25/99 10:37p Matt
 * Changes in death flags
 *
 * 171   4/25/99 3:06p Matt
 * Increased the max number of spew handles from 10 to 20.
 *
 * 170   4/24/99 2:18a Chris
 * Added some new functions.
 *
 * 169   4/19/99 6:14p Chris
 * Added two new AI Queries for Nate
 *
 * 168   4/07/99 11:25a Matt
 * Added fail level action
 *
 * 167   4/07/99 3:05a Chris
 * Improved the team stuff and fixed a compile bug in
 * LightningCreateGunpoints
 *
 * 166   4/06/99 11:44p Matt
 * Added action to create a lighting bolt between two gunpoints on the
 * same object, and queries to return an object's original shields and to
 * multiply a percent times a float.
 *
 * 165   4/06/99 8:44p Matt
 * Added a couple actions for Mark's energy/shield collector
 *
 * 164   4/06/99 11:00a Jeff
 *
 * 163   4/05/99 5:44p Chris
 * Added a drop all objects functions
 *
 * 162   4/05/99 1:07p Chris
 * Added a goal failed state
 *
 * 161   4/04/99 6:20p Matt
 * Added distance-based shake Dallas action.
 *
 * 160   4/03/99 3:51p Chris
 *
 * 159   4/03/99 3:16p Chris
 *
 * 158   4/03/99 2:49p Chris
 * Fixed a bug with the ScriptedDeath DALLAS func.
 *
 * 157   4/03/99 1:12a Jeff
 * added multisafe/dallas actions to set an object on fire
 *
 * 156   4/02/99 6:41p Matt
 * Added query to find the closest player to an object.
 *
 * 155   4/02/99 1:20p Nate
 * Fixed dallas syntax bug with qGetAttachedChild
 *
 * 154   4/02/99 12:57p Chris
 * Added 2 new DALLAS actions for Nate
 *
 * 153   4/02/99 11:27a Nate
 * Upped the SavedObjectHandle limit to 20
 *
 * 152   4/02/99 11:24a Matt
 * Added kill object action that allows the caller to specify the death.
 *
 * 151   3/31/99 11:40a Jason
 * added support for attached thick lightning
 *
 * 150   3/30/99 7:40p Chris
 *
 * 149   3/30/99 7:39p Chris
 *
 * 148   3/30/99 7:25p Chris
 * Make the weath_lightning stuff more flexable
 *
 * 147   3/29/99 8:41p Nate
 * Jason fix
 *
 * 146   3/29/99 8:02p Nate
 * Added qObjCanSeePlayerAdvancedWithStore
 *
 * 145   3/29/99 7:30p Jason
 * added cool new energy effect
 *
 * 144   3/29/99 6:04p Nate
 * Changed aLightningCreate header for new abilities.
 *
 * 143   3/29/99 5:26p Chris
 * Added the unattach form object and the set max speed functions to
 * DALLAS
 *
 * 142   3/29/99 11:11a Jeff
 * fixed fvi calls for view cone functions (hit_none is a valid hit)
 *
 * 141   3/28/99 6:47p Matt
 * Added default value for spark rate
 *
 * 140   3/28/99 5:56p Matt
 * Added Dallas action to turn on object sparking
 *
 * 139   3/28/99 3:29p Sean
 * Jeff: Fixed misnamed dallas func
 *
 * 138   3/27/99 9:14p Jeff
 * added advanced object view cones dallas funcs
 *
 * 137   3/27/99 7:22p Jeff
 * fixed cinematics when going from one cut to another immediatly.  Added
 * start transition
 *
 * 136   3/26/99 12:38p Jeff
 * added cloak predefs
 *
 * 135   3/25/99 9:09p Nate
 * Fixed Land On Object action
 *
 * 134   3/25/99 4:56p Chris
 * Added code for the land on object DALLAS goal
 *
 * 133   3/24/99 10:02a Matt
 * Added Dallas action to set music region for all players
 *
 * 132   3/23/99 6:42p Chris
 * Added the Get to Object Goal for DALLAS
 *
 * 131   3/23/99 4:30p Chris
 * Fixed a bug in the AIGoalGoToRoom()  (parameters where out of order)
 *
 * 130   3/22/99 6:35p Matt
 * Added Dallas action to create a lightning bolt between two objects.
 * Jason will implement this.
 *
 * 129   3/22/99 1:59p Matt
 * Added break glass Dallas action
 *
 * 128   3/04/99 6:13p Matt
 * Pass second game message string in message2.  Also changed color of the
 * HUD message.
 *
 * 127   3/03/99 3:02p Matt
 * Added Game Message action in Dallas
 *
 * 126   3/02/99 11:19a Jeff
 * added comment
 *
 * 125   2/28/99 11:24p Matt
 * Changed a literal to a symbolic constant
 *
 * 124   2/28/99 8:31p Jeff
 * added fade and move player dallas action.  Fixed the end-level sequence
 * changing view back to player for split second.
 *
 * 123   2/27/99 1:41p Matt
 * Added saved object handles to savegame read/write functions.
 *
 * 122   2/26/99 1:57a Jeff
 * added text to end level sequence
 *
 * 121   2/25/99 8:53p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 120   2/23/99 7:34p Jeff
 * save out position clipboard, fixed up add inventory item
 *
 * 119   2/23/99 7:23p Matt
 * Fixed function parms for new types.
 *
 * 118   2/23/99 11:09a Matt
 * Fixed level goal actions/queries
 *
 * 117   2/22/99 10:21p Matt
 * Added (but did not test) several actions and queries for level goals.
 *
 * 116   2/22/99 10:53a Matt
 * Added a version of the streaming audio action that takes a text string,
 * for sounds that aren't in the table file.
 *
 * 115   2/22/99 10:40a Luke
 * fixed aAIGoalFollowPath with new data types
 *
 * 114   2/22/99 1:19a Jeff
 * added support for inventory (simple) in dallas.  Moved end-level
 * sequence to use IGC.  Add position clipboard stuff for dallas.  Fixed
 * some inventory bug with storing object handles
 *
 * 113   2/21/99 8:35p Jeff
 * misc changes to handle new matcen and path types of dallas
 *
 * 112   2/21/99 6:35p Matt
 * Finished action for setting object movement type, and fixed the attach
 * new object action.
 *
 * 111   2/21/99 6:05p Matt
 * Use new types for matcens, paths, & streaming audio.
 *
 * 110   2/21/99 5:49p Matt
 * Added Dallas action to set an object's volume
 *
 * 109   2/21/99 4:55p Matt
 * Added actions to set an object's movement type and to enable/disable
 * gravity for a object.
 *
 * 108   2/19/99 6:44p Chris
 *
 * 107   2/16/99 9:36p Jeff
 * added low text layout for cinematics
 *
 * 106   2/16/99 12:37a Matt
 * Added set object velocity action
 *
 * 105   2/15/99 9:57p Matt
 * Several small changes
 *
 * 104   2/15/99 3:30p Dan
 * Fixed typo
 *
 * 103   2/15/99 3:19p Dan
 * Added integer add & subtract queries (MattT on Dan's machine)
 *
 * 102   2/15/99 11:09a Matt
 * Added function to count the number of a certain type of object in the
 * level. (Also added HUD actions to print an int and float.)
 *
 * 101   2/14/99 4:27a Jeff
 * forgot to unset a flag when ending a custom cinematic. and set a flag
 * when starting a custom cinematic.
 *
 * 100   2/13/99 8:44p Jeff
 * made intro cinematic into a 'canned' cinematic.  Added ability to
 * create custom in-game cinematics (SUPER powerful)
 *
 * 99    2/13/99 5:33p Matt
 * Changed pathname in endlevel sequence from string to specific string
 *
 * 98    2/12/99 6:14p Matt
 * Added object is type query
 *
 * 97    2/12/99 4:17p Matt
 * Added key name & HUD message to give key action
 *
 * 96    2/12/99 12:07p Matt
 * Make region action use enumerated type
 *
 * 95    2/11/99 1:07p Matt
 * Added action to enable/disable triggers
 *
 * 94    2/11/99 2:53a Jeff
 * improvements to introcam
 *
 * 93    2/10/99 4:06p Matt
 * Changed the object type name parameter to the attach action to a
 * specific string.
 *
 * 92    2/10/99 2:56p Matt
 * Fixed typo
 *
 * 91    2/10/99 2:31p Matt
 * Added Enable/Disable Matcen action.
 *
 * 90    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 89    2/10/99 1:21p Matt
 * Added UserFlags and a query to return a user var as an integer.
 *
 * 88    2/09/99 1:29p Matt
 * Added Matcen IDs, object handle saves, random value query, player in
 * room query.
 *
 * 87    2/08/99 5:08p Matt
 * Added MatcenID user type, and added No Reorientation flag to flag masks
 * for all the AI actions.
 *
 * 86    2/08/99 3:10a Jeff
 * added a multisafe type for player control type setting.  Improved intro
 * cinematic action function, player now follows path.
 *
 * 85    2/06/99 10:03p Matt
 * Added keys system
 *
 * 84    2/06/99 1:52a Matt
 * Added a bunch of Dallas funcs, mostly for Sean
 *
 * 83    2/05/99 5:51p Chris
 * Added rereorienation to ai goal flags
 *
 * 82    2/05/99 1:29p Matt
 * Changed wind to use direction vector & speed instead of velocity
 * vector, and added some defaults to some actions.
 *
 * 81    2/04/99 3:24p Matt
 * Increased the number of user vars to 25, and added save/load code for
 * user vars and sound & spew handles.
 *
 * 80    2/03/99 5:48p Matt
 * Added room damage system
 *
 * 79    2/03/99 2:56a Jeff
 * ship permission actions and queries
 *
 * 78    2/03/99 12:24a Matt
 * Got HUD message, 2D sound, streaming sound, and player-is-visible all
 * working correctly in multiplayer.
 *
 * 77    2/02/99 3:58p Jeff
 * started to implement level intro cinematic (need ai functions first).
 * No longer need camera object to do cinematic (auto-created)...path
 * cameras use speed based on distance needed to travel.
 *
 * 76    2/02/99 3:38p Luke
 * Changed Matcen names to take direct string input instead of using
 * messages
 *
 * 75    2/02/99 12:35p Jeff
 * changed cinematic path parameter to use a instead of s
 *
 * 74    2/01/99 2:08p Kevin
 * Fixed parameter order for qObjCanSeeObj
 *
 * 73    2/01/99 1:11p Matt
 * Changed a bunch of stuff to work with object handles instead of player
 * numbers.  Also fixed the view cone action, which ignored distance.
 *
 * 72    2/01/99 12:41p Kevin
 * Moved some functions into the training system script
 *
 * 71    1/31/99 11:06p Matt
 * Changed timers from handles to IDs, and implemented music region set.
 *
 * 70    1/31/99 9:00p Jeff
 * added new in game cinematics system
 *
 * 69    1/31/99 8:11p Matt
 * Added player visible query, and made zoom work with popup cameras.
 *
 * 68    1/31/99 7:15p Matt
 * Added physics flags for spew
 *
 * 67    1/30/99 7:54p Chris
 *
 * 66    1/30/99 3:46p Luke
 * Changed two boolean parameters to be FALSE by default (0 didn't work)
 *
 * 65    1/30/99 3:19p Matt
 * Made Dallas spews work from object centers in addition to gunpoints
 *
 * 64    1/29/99 3:14p Matt
 * Deleted some obsolete Dallas actions, and made the player controls
 * actions take player numbers instead of the player object.
 *
 * 63    1/29/99 2:50p Luke
 * Added a bunch of default values to help designers and fixed a few
 * parameter listings, but modified no actual code
 *
 * 62    1/29/99 12:57p Kevin
 * Added cone to ObjCanSeeObj
 *
 * 61    1/29/99 12:49p Matt
 * Added door actions & queries, chagned the working of the math queries,
 * adding math queries for percentages, and reworded a few other queries.
 *
 * 60    1/26/99 6:39p Kevin
 * Added energy get/set
 *
 * 59    1/26/99 5:17p Matt
 * Added user types and stop object sound action.
 *
 * 58    1/26/99 12:53p Kevin
 * Added SetTeam function
 *
 * 57    1/26/99 10:51a Matt
 * Fixed stupid oversight.
 *
 * 56    1/25/99 6:32p Matt
 * A bunch of stuff: sounds, goal flag masks, pick up with radius.
 *
 * 55    1/25/99 12:19p Matt
 * Fixed stupid bugs
 *
 * 54    1/25/99 11:13a Matt
 * Changed a bunch of actions to use enums for On/Off, Enable/Disable,
 * etc. instead of bools.  Also changed the Player controls action to use
 * flags.
 *
 * 53    1/25/99 10:15a Matt
 * AI Goal stuff
 *
 * 52    1/25/99 7:23a Chris
 * Added the GUID (Goal Unique Id) and added the ability for weapon
 * batteries to always fire exactly forward.
 *
 * 51    1/24/99 6:28p Matt
 * Added path follow action
 *
 * 50    1/23/99 5:37p Matt
 * Deleted AI goal flags that the user won't be using
 *
 * 49    1/23/99 5:19p Matt
 * Added AI goal flags
 *
 * 48    1/23/99 4:48p Matt
 * Added some default parameter values
 *
 * 47    1/23/99 2:56a Jeff
 * added target field to boss intro struct
 *
 * 46    1/22/99 7:50p Kevin
 * Training mission additions..
 *
 * 45    1/22/99 5:42p Matt
 * Added a couple AI actions, though I haven't tested them fully yet.
 *
 * 44    1/22/99 3:09p Matt
 * Added forcefield state query
 *
 * 43    1/21/99 7:03p Matt
 * Added action to set/clear secret flag
 *
 * 42    1/20/99 9:30p Matt
 * Got AISetMode action working
 *
 * 41    1/20/99 6:26p Matt
 * Added several actions
 *
 * 40    1/20/99 3:49p Kevin
 * Added some glue functions
 *
 * 39    1/20/99 3:44a Jeff
 * created functions and struct for boss introduction cinematic sequence
 *
 * 38    1/19/99 6:54p Matt
 * Added queries to add & subtract floats
 *
 * 37    1/19/99 6:13p Matt
 * Added an action & query for lighting distance
 *
 * 36    1/19/99 3:43p Kevin
 * Added msafe functionality to set an object to render type RT_NONE
 *
 * 35    1/19/99 12:16p Matt
 * Added start endlevel sequence action
 *
 * 34    1/19/99 10:33a Kevin
 *
 * 33    1/19/99 10:02a Matt
 * Added unfinished sound action
 *
 * 32    1/18/99 7:31p Matt
 * Added a bunch of Dallas actions
 *
 * 31    1/18/99 6:18p Kevin
 * Added controller masking to DALLAS
 *
 * 30    1/18/99 3:30p Matt
 * Added some default values and ranges
 *
 * 29    1/15/99 5:02p Matt
 * Got activate/deactive matcen actions working
 *
 * 28    1/15/99 11:04a Matt
 * Added actions for matcens (not working) and fog (working)
 *
 * 27    1/13/99 5:48p Nate
 * Fixed "Sheild" in function prototypes
 *
 * 26    1/13/99 12:42p Matt
 * Added an action to close a popup view
 *
 * 25    1/11/99 8:43p Nate
 * Added custom DALLAS queries
 *
 * 24    1/11/99 6:23p Nate
 * Fixed two broken queries, some spelling errors, and made "Obj type"
 * return an ObjectType (specific enumerated type)
 *
 * 23    1/11/99 4:53p Matt
 * Change spew action to use enum, and added real values for SpewType
 *
 * 22    1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 21    1/11/99 10:43a Matt
 * Made forcefield on/off/toggle optionally do both sides of a portal
 *
 * 20    1/11/99 10:25a Matt
 * Added spew handles and got spew off working.  Also added functions to
 * init, load, & save variables.
 *
 * 19    1/08/99 6:07p Matt
 * Added some comments
 *
 * 18    1/08/99 4:33p Matt
 * Got popup views working in Dallas
 *
 * 17    1/08/99 3:00p Luke
 * (Jeff) fixed ObjPlayAnim bug (never filled in objhandle)
 *
 * 16    1/06/99 12:02p Matt
 * Fixed some function name mismatches
 *
 * 15    1/05/99 6:53p Jeff
 * fixed hud message color
 *
 * 14    1/05/99 6:38p Jeff
 * fixed spew errors, added some defines
 *
 * 13    1/05/99 4:31p Matt
 * Added a bunch more actions
 *
 * 12    1/05/99 3:41p Jeff
 * added spew create and stop functions
 *
 * 11    1/04/99 11:03p Matt
 * Added a bunch of actions & queries, and renamed a bunch of others
 *
 * 10    1/02/99 3:50p Matt
 * Added ENUM defines to comment block, and made aShowHUDMessage() take
 * var args.
 *
 * 9     1/01/99 3:25p Matt
 * Fixed lightning actions
 *
 * 8     12/30/98 6:56p Matt
 * Added a bunch more actions and queries
 *
 * 7     12/23/98 6:43p Nate
 * Fixed the category for the qIsPlayerWeapon Query
 *
 * 6     12/23/98 6:10p Matt
 * Added toggle forcefield action
 *
 * 5     12/23/98 4:29p Matt
 * Un-did hack from previous version.  Now works w/ scripts.
 *
 * 4     12/23/98 3:02p Luke
 * Nate: temp fix so that editor will compile
 *
 * 3     12/23/98 1:46p Matt
 * Renamed the portal render/forcefield actions
 *
 * 2     12/23/98 1:39p Matt
 * Added DallasFuncs.cpp to project
 *
 * 1     12/23/98 1:36p Matt
 *
 */

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cfloat>

#include "osiris_vector.h"

// These should really be included, I think, but there's a problem with osiris_import.h being included twice
// #include "osiris_import.h"
// #include "osiris_common.h"

/*

Dallas types:

  ID	Name			How passed
   o	object		object handle
   d	door			handle of door object
   r	room			integer room number
   t	trigger		integer trigger number
   i	int			integer
   b	bool			usigned byte
   f	float			single-precision float (4 bytes)
   p	percentage	single-precision float in range 0.0 - 1.0
   v	vector		pointer to triplet of floats
   s	string		pointer to null-terminated string
        e	enum			integer
        a	name			a specific (non-localizable) name, as of a matcen.  Does not appear in the
message file. n	sound			sound name h	path			integer path number m	matcen
integer matcen numer l	level goal	integer level goal number z	streaming audio	pointer to null-terminated name
of audio file



Dallas Action Categories.  Used by Dallas to build the action list.

$$CATEGORIES
Objects
Players
Doors
Rooms
Triggers
Spew
Weather
AI
Sound && Music
Timer
Level Goals
Mission
Math
User Vars
Misc
Scripts
Cinematics
Custom
$$END


Enumerated types:

$$ENUM Axis
0:X
1:Y
2:Z
$$END

$$ENUM SpewType
0:Explosion0
1:Explosion1
2:Explosion2
3:Explosion3
4:Explosion4
5:Explosion5
6:Explosion6
7:Grey Smoke
8:Black Smoke
15:Red Spark
16:Blue Spark
23:Napalm
28:Raindrop
35:Corona0
36:Corona1
37:Corona2
38:Corona3
39:Snowflake
41:Blue Fire
$$END

//I've just defined the flags that spew needs, but feel free to define others if you need them
$$FLAG PhysicsFlags
128:Gravity
2048:Fixed Velocity
32768:Reverse Gravity
65536:No Collide
2097152:Ignore Concussive Force
8388608:Lock X
16777216:Lock Y
33554432:Lock Z
$$END

$$FLAG FVIHitFlags
1:Check against objects
2:Hit backfaces of poly objects
4:Go through transparent walls if hit
8:Ignore powerups
16:Check for collisions with backfaces (default ignored)
32:Solid Portals
256:Ignore Moving Objects
512:Ignore Non-Lightmap Objects
1024:Ignore all objects besides players
2048:Ignore all walls
4096:Check terrain ceiling
8192:Ignore all objects but doors
524288:Ignore external rooms
1048576:Ignore weapons
2097152:Ignore terrain
4194304:Treat players as spheres
8388608:Treat Robots as spheres
$$END
Total: 16269119

$$ENUM ObjectType
2:Robot
4:Player
5:Weapon
6:Viewer
7:Powerup
8:Debris
10:Shockwave
11:Clutter
16:Building
17:Door
$$END

$$FLAG PlayerControl
1:Forward Thrust
2:Reverse Thrust
4:Slide Left
8:Slide Right
16:Slide Up
32:Slide Down
64:Pitch Up
128:Pitch Down
256:Heading Left
512:Heading Right
1024:Roll Left
2048:Roll Right
4096:Primary
8192:Secondary
16384:Afterburner
$$END

$$ENUM Enabled/Disabled
0:DISABLED
1:ENABLED
$$END

$$ENUM Enable/Disable
0:DISABLE
1:ENABLE
$$END

$$ENUM Completed
0:NOT COMPLETED
1:COMPLETED
$$END

$$ENUM Failed
0:NOT FAILED
1:FAILED
$$END

$$ENUM Can/Cannot
0:CANNOT
1:CAN
$$END

$$ENUM On/Off
0:OFF
1:ON
$$END

$$ENUM Yes/No
0:NO
1:YES
$$END

$$ENUM Activate/Deactivate
0:DEACTIVATE
1:ACTIVATE
$$END

$$ENUM Teams
0:PTMC
65536:Rebel
131072:Hostile
196608:Neutral
$$END

*/

//
//  Variables
//

#define MAX_USER_VARS 25 // make sure this value matches the USERTYPE definition
float User_vars[MAX_USER_VARS];

#define MAX_SPEW_HANDLES 50 // make sure this value matches the USERTYPE definition
int Spew_handles[MAX_SPEW_HANDLES];

#define MAX_SOUND_HANDLES 10 // make sure this value matches the USERTYPE definition
int Sound_handles[MAX_SOUND_HANDLES];

#define MAX_SAVED_OBJECT_HANDLES 20 // make sure this value matches the USERTYPE definition
int Saved_object_handles[MAX_SAVED_OBJECT_HANDLES];

int User_flags;

class cPositionClipboard {
public:
  cPositionClipboard() { has_pos = false; }
  bool has_pos;
  int room;
  vector pos;
  matrix orient;
};
cPositionClipboard PositionClipboard;

#define SOUND_INVALID_HANDLE -1
#define SPEW_INVALID_HANDLE -1

/*
Tell Dallas about our handles

$$USERTYPE UserVar:24
$$USERTYPE UserFlag:31
$$USERTYPE SpewHandle:49
$$USERTYPE TimerID:49
$$USERTYPE SavedObjectSlot:19
*/

// TEMP!!!
#ifndef OBJECT_HANDLE_NONE
#define OBJECT_HANDLE_NONE -1
#endif

//
//  System functions
//

// Initialize vars
void dfInit() {
  int i;

  for (i = 0; i < MAX_SPEW_HANDLES; i++)
    Spew_handles[i] = SPEW_INVALID_HANDLE;

  for (i = 0; i < MAX_SOUND_HANDLES; i++)
    Sound_handles[i] = SOUND_INVALID_HANDLE;

  for (i = 0; i < MAX_USER_VARS; i++)
    User_vars[i] = 0.0;

  for (i = 0; i < MAX_SAVED_OBJECT_HANDLES; i++)
    Saved_object_handles[i] = OBJECT_HANDLE_NONE;

  User_flags = 0;
}

// Save vars
void dfSave(void *fileptr) {
  int i;

  for (i = 0; i < MAX_SPEW_HANDLES; i++)
    File_WriteInt(Spew_handles[i], fileptr);

  for (i = 0; i < MAX_SOUND_HANDLES; i++)
    File_WriteInt(Sound_handles[i], fileptr);

  for (i = 0; i < MAX_USER_VARS; i++)
    File_WriteFloat(User_vars[i], fileptr);

  for (i = 0; i < MAX_SAVED_OBJECT_HANDLES; i++)
    File_WriteInt(Saved_object_handles[i], fileptr);

  File_WriteInt(User_flags, fileptr);

  File_WriteByte(PositionClipboard.has_pos, fileptr);
  File_WriteInt(PositionClipboard.room, fileptr);
  File_WriteFloat(PositionClipboard.pos.x, fileptr);
  File_WriteFloat(PositionClipboard.pos.y, fileptr);
  File_WriteFloat(PositionClipboard.pos.z, fileptr);
  File_WriteFloat(PositionClipboard.orient.fvec.x, fileptr);
  File_WriteFloat(PositionClipboard.orient.fvec.y, fileptr);
  File_WriteFloat(PositionClipboard.orient.fvec.z, fileptr);
  File_WriteFloat(PositionClipboard.orient.uvec.x, fileptr);
  File_WriteFloat(PositionClipboard.orient.uvec.y, fileptr);
  File_WriteFloat(PositionClipboard.orient.uvec.z, fileptr);
  File_WriteFloat(PositionClipboard.orient.rvec.x, fileptr);
  File_WriteFloat(PositionClipboard.orient.rvec.y, fileptr);
  File_WriteFloat(PositionClipboard.orient.rvec.z, fileptr);
}

// Restore vars
void dfRestore(void *fileptr) {
  int i;

  for (i = 0; i < MAX_SPEW_HANDLES; i++)
    Spew_handles[i] = File_ReadInt(fileptr);

  for (i = 0; i < MAX_SOUND_HANDLES; i++)
    Sound_handles[i] = File_ReadInt(fileptr);

  for (i = 0; i < MAX_USER_VARS; i++)
    User_vars[i] = File_ReadFloat(fileptr);

  for (i = 0; i < MAX_SAVED_OBJECT_HANDLES; i++)
    Saved_object_handles[i] = File_ReadInt(fileptr);

  User_flags = File_ReadInt(fileptr);

  PositionClipboard.has_pos = (File_ReadByte(fileptr)) ? true : false;
  PositionClipboard.room = File_ReadInt(fileptr);
  PositionClipboard.pos.x = File_ReadFloat(fileptr);
  PositionClipboard.pos.y = File_ReadFloat(fileptr);
  PositionClipboard.pos.z = File_ReadFloat(fileptr);
  PositionClipboard.orient.fvec.x = File_ReadFloat(fileptr);
  PositionClipboard.orient.fvec.y = File_ReadFloat(fileptr);
  PositionClipboard.orient.fvec.z = File_ReadFloat(fileptr);
  PositionClipboard.orient.uvec.x = File_ReadFloat(fileptr);
  PositionClipboard.orient.uvec.y = File_ReadFloat(fileptr);
  PositionClipboard.orient.uvec.z = File_ReadFloat(fileptr);
  PositionClipboard.orient.rvec.x = File_ReadFloat(fileptr);
  PositionClipboard.orient.rvec.y = File_ReadFloat(fileptr);
  PositionClipboard.orient.rvec.z = File_ReadFloat(fileptr);
}

int dfGetPlayer(int objhandle) {
  msafe_struct mstruct;
  mstruct.objhandle = objhandle;
  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  if (mstruct.type == OBJ_WEAPON) {
    MSafe_GetValue(MSAFE_OBJECT_PARENT, &mstruct);
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

    if (mstruct.type == OBJ_PLAYER || mstruct.type == OBJ_OBSERVER || mstruct.type == OBJ_GHOST) {
      return mstruct.objhandle;
    } else {
      mprintf(0, "---------------------NOT A PLAYER OR PLAYER WEAPON!!!!!!!!!-------------\n");
      return objhandle;
    }

  } else if (mstruct.type == OBJ_PLAYER || mstruct.type == OBJ_OBSERVER || mstruct.type == OBJ_GHOST) {
    return objhandle;
  } else {
    mprintf(0, "---------------------NOT A PLAYER OR PLAYER WEAPON!!!!!!!!!-------------\n");
  }

  return objhandle;
}

//
//  D3 actions
//

/*
$$ACTION
Rooms
[e:Enable/Disable] forcefield at portal [i:PortalNum] in room [r:Room]; Double-sided = [b:DoublesidedFlag=1]
aPortalRenderSet
Enable/Disable forcefield
  Turns on or off the specified forcefield

Parameters:
  Room:  The room the forcefield is in
  PortalNum:  The portal number of the forcefield
$$END
*/
void aPortalRenderSet(int state, int portalnum, int roomnum, bool doublesided) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.portalnum = portalnum;
  mstruct.flags = doublesided ? 1 : 0;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_ROOM_PORTAL_RENDER, &mstruct);
}

/*
$$ACTION
Rooms
[e:Enable/Disable] Blockage at portal [i:PortalNum] in room [r:Room]
aPortalBlockageSet
Enable/Disable Blockage
  Turns on or off the blockage at a specified portal

Parameters:
  Room:  The room the blockage is in
  PortalNum:  The portal number of the blockage
$$END
*/
void aPortalBlockageSet(int state, int portalnum, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.portalnum = portalnum;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_ROOM_PORTAL_BLOCK, &mstruct);
}

/*
$$ACTION
Rooms
Toggle forcefield at portal [i:PortalNum] in room [r:Room]; Double-sided = [b:DoublesidedFlag=1]
aPortalRenderToggle
Toggle forcefield
  Turns off the specified forcefield if it's on, and on if it's off

Parameters:
  Room:  The room the forcefield is in
  PortalNum:  The portal number of the forcefield
$$END
*/
void aPortalRenderToggle(int portalnum, int roomnum, bool doublesided) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.portalnum = portalnum;

  MSafe_GetValue(MSAFE_ROOM_PORTAL_RENDER, &mstruct);

  mstruct.flags = doublesided ? 1 : 0;
  mstruct.state = !mstruct.state;
  MSafe_CallFunction(MSAFE_ROOM_PORTAL_RENDER, &mstruct);
}

/*
$$ACTION
Rooms
Break glass at portal [i:PortalNum] in room [r:Room]
aPortalBreakGlass
Break glass
  Breaks the glass in the specified portal

Parameters:
  PortalNum:  The portal number of the forcefield
  Room:  The room the forcefield is in
$$END
*/
void aPortalBreakGlass(int portalnum, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.portalnum = portalnum;

  MSafe_CallFunction(MSAFE_ROOM_BREAK_GLASS, &mstruct);
}

/*
Damage sound types
$$ENUM DamageSoundType
0:None
1:Energy Weapon
2:Matter Weapon
3:Melee Attach
4:Concussive Force
5:Wall Hit
$$END
*/

/*
$$ACTION
Rooms
Set room [r:Room] damage to [f:Damage] with sound type [e:DamageSoundType]
aRoomSetDamage
Set room damage
  Sets the sepecifed room to damage the player

Parameters:
  Room:  The room that will cause the damage
  Damage: the damage rate, in shield units per second
$$END
*/
void aRoomSetDamage(int roomnum, float damage, int soundtype) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.amount = damage;
  mstruct.index = soundtype;

  MSafe_CallFunction(MSAFE_ROOM_DAMAGE, &mstruct);
}

/*
$$ACTION
Misc
Show HUD message [s:Message]
aShowHUDMessage
Show HUD message
  Shows a HUD message for all players

Parameters:
  Message:  The message to show
$$END
*/
void aShowHUDMessage(const char *format, ...) {
  msafe_struct mstruct;
  va_list args;

  va_start(args, format);
  std::vsnprintf(mstruct.message, sizeof(mstruct.message) - 1, format, args);
  va_end(args);
  mstruct.message[sizeof(mstruct.message) - 1] = 0; // if message too long, vsnprintf() won't terminate

  mstruct.state = 0; // means all players
  mstruct.color = GR_RGB(0, 255, 0);

  MSafe_CallFunction(MSAFE_MISC_HUD_MESSAGE, &mstruct);
}

/*
$$ACTION
Misc
Show HUD message [s:Message] for player [o:PlayerObject=IT]
aShowHUDMessageObj
Show HUD message
  Shows a HUD message for a specific player

Parameters:
  Message:  The message to show
  PlayerObject: The player who sees the object
$$END
*/
void aShowHUDMessageObj(const char *format, int objhandle, ...) {
  msafe_struct mstruct;
  va_list args;

  va_start(args, objhandle);
  std::vsnprintf(mstruct.message, sizeof(mstruct.message) - 1, format, args);
  va_end(args);
  mstruct.message[sizeof(mstruct.message) - 1] = 0; // if message too long, vsnprintf() won't terminate

  mstruct.state = 1; // means specific player
  mstruct.objhandle = dfGetPlayer(objhandle);
  mstruct.color = GR_RGB(0, 255, 0);

  MSafe_CallFunction(MSAFE_MISC_HUD_MESSAGE, &mstruct);
}

/*
$$ACTION
Misc
Show Colored HUD message of color [i:Red] [i:Green] [i:Blue] saying [s:Message]
aShowColoredHUDMessage
Show Colored HUD message
  Shows a colored HUD message for all players

Parameters:
  Red: Red component of color (0-255)
  Green: Green component of color (0-255)
  Blue: Blue component of color (0-255)
  Message:  The message to show
$$END
*/
void aShowColoredHUDMessage(int red, int green, int blue, const char *format, ...) {
  msafe_struct mstruct;
  va_list args;

  va_start(args, format);
  std::vsnprintf(mstruct.message, sizeof(mstruct.message) - 1, format, args);
  va_end(args);
  mstruct.message[sizeof(mstruct.message) - 1] = 0; // if message too long, vsnprintf() won't terminate

  mstruct.state = 0; // means all players
  mstruct.color = GR_RGB((uint8_t)red, (uint8_t)green, (uint8_t)blue);

  MSafe_CallFunction(MSAFE_MISC_HUD_MESSAGE, &mstruct);
}

/*
$$ACTION
Misc
Show Colored HUD message of color [i:Red] [i:Green] [i:Blue] saying [s:Message] for player [o:PlayerObject=IT]
aShowColoredHUDMessageObj
Show Colored HUD message
  Shows a colored HUD message for a specific player

Parameters:
  Red: Red component of color (0-255)
  Green: Green component of color (0-255)
  Blue: Blue component of color (0-255)
  Message:  The message to show
  PlayerObject: The player who sees the object
$$END
*/
void aShowColoredHUDMessageObj(int red, int green, int blue, const char *format, int objhandle, ...) {
  msafe_struct mstruct;
  va_list args;

  va_start(args, objhandle);
  std::vsnprintf(mstruct.message, sizeof(mstruct.message) - 1, format, args);
  va_end(args);
  mstruct.message[sizeof(mstruct.message) - 1] = 0; // if message too long, vsnprintf() won't terminate

  mstruct.state = 1;
  mstruct.objhandle = dfGetPlayer(objhandle);
  mstruct.color = GR_RGB((uint8_t)red, (uint8_t)green, (uint8_t)blue);

  MSafe_CallFunction(MSAFE_MISC_HUD_MESSAGE, &mstruct);
}

/*
$$ACTION
Misc
Add Game Message [s:GameMessage] with HUD mesage [s:HUDMessage]
aAddGameMessage
Add Game Message
  Adds a message to the game message log, and shows another message on the HUD

Parameters:
  GameMessage: The message that's added to the game message log
  HUDMessage: The message that's displayed on the HUD
$$END
*/
void aAddGameMessage(const char *game_message, const char *hud_message) {
  msafe_struct mstruct;

  strncpy(mstruct.message, game_message, sizeof(mstruct.message));
  mstruct.message[sizeof(mstruct.message) - 1] = 0;

  strncpy(mstruct.message2, hud_message, sizeof(mstruct.message2));
  mstruct.message[sizeof(mstruct.message) - 1] = 0;

  mstruct.color = GR_RGB(0, 242, 148);
  mstruct.state = 0; // means all players

  MSafe_CallFunction(MSAFE_MISC_GAME_MESSAGE, &mstruct);
}

/*
$$ACTION
Weather
Turn rain ON with density = [p:Density=0.5:0.0|1.0]
aRainTurnOn
Turn rain ON
  Turns on the rain

Parameters:
  ??
$$END
*/
void aRainTurnOn(float density) {
  msafe_struct mstruct;

  mstruct.scalar = density;
  mstruct.state = true;

  MSafe_CallFunction(MSAFE_WEATHER_RAIN, &mstruct);
}

/*
$$ACTION
Weather
Turn rain OFF
aRainTurnOff
Turn rain OFF
  Turns off the rain

Parameters:
  None.
$$END
*/
void aRainTurnOff() {
  msafe_struct mstruct;

  mstruct.state = false;

  MSafe_CallFunction(MSAFE_WEATHER_RAIN, &mstruct);
}

/*
$$ACTION
Weather
Turn snow ON with density = [p:Density=0.5:0.0|1.0]
aSnowTurnOn
Turn snow ON
  Turns on the snow

Parameters:
  ??
$$END
*/
void aSnowTurnOn(float density) {
  msafe_struct mstruct;

  mstruct.scalar = density;
  mstruct.state = true;

  MSafe_CallFunction(MSAFE_WEATHER_SNOW, &mstruct);
}

/*
$$ACTION
Weather
Turn snow OFF
aSnowTurnOff
Turn snow OFF
  Turns off the snow

Parameters:
  None
$$END
*/
void aSnowTurnOff() {
  msafe_struct mstruct;

  mstruct.state = false;

  MSafe_CallFunction(MSAFE_WEATHER_SNOW, &mstruct);
}

/*
$$ACTION
Weather
Turn lightning ON with frequency of [f:Seconds=5.0] and probability of [p:Probability=0.5]
aLightningTurnOn
Turn lightning ON
  Turns on the lightning

Parameters:
  Seconds:  How often to check to create lightning
  Probability:  The chance of creating lightning at each check
$$END
*/
void aLightningTurnOn(float check_delay, float prob) {
  msafe_struct mstruct;

  mstruct.state = true;
  mstruct.scalar = check_delay;
  mstruct.randval = static_cast<int>(prob * static_cast<float>(RAND_MAX));

  MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING, &mstruct);
}

/*
$$ACTION
Weather
Turn lightning OFF
aLightningTurnOff
Turn lightning OFF
  Turns off the lightning

Parameters:
  None
$$END
*/
void aLightningTurnOff() {
  msafe_struct mstruct;

  mstruct.state = false;

  MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING, &mstruct);
}

/*
$$ACTION
Weather
Create lighting between [o:Object1] and [o:Object2]; with [f:Lifetime=1.0], [f:Thickness=1.0], [i:NumTiles=1],
[u:Texture], [f:SlideTime=0], [i:TimesDrawn=1], and color=[i:Red=255],[i:Green=255],[i:Blue=255],
AutoTile=[b:AutoTile=false] aLightningCreate Create lighting between two objects Creates a lighting effect between two
specified obejcts

Parameters:
  Object1, Object2:  Where the lighting is created
  Lifetime: How long the lighting lasts
  Thickness: How thick the lightning is
  NumTiles: How many times to tile the texture within the bolt
  Texture: The texture to be used for the lighting
  SlideTime: The time it will take to slide the entire bolt once
  TimesDrawn: The number of times to draw the bolt (saturation)
  Red, Green, Blue: The color of the lighting (0-255)
  AutoTile - For automatic UV tiling based on the length of the bolt
$$END
*/
void aLightningCreate(int objhandle1, int objhandle2, float lifetime, float thickness, int numtiles, int texture_id,
                      float slidetime, int timesdrawn, int red, int green, int blue, bool autotile) {
  msafe_struct mstruct;
  int type;

  Obj_Value(objhandle1, VF_GET, OBJV_I_TYPE, &type);
  if (type == OBJ_NONE)
    return;

  Obj_Value(objhandle2, VF_GET, OBJV_I_TYPE, &type);
  if (type == OBJ_NONE)
    return;

  Obj_Value(objhandle1, VF_GET, OBJV_I_ROOMNUM, &mstruct.roomnum);
  Obj_Value(objhandle1, VF_GET, OBJV_V_POS, &mstruct.pos);
  Obj_Value(objhandle2, VF_GET, OBJV_V_POS, &mstruct.pos2);

  mstruct.objhandle = objhandle1;
  mstruct.ithandle = objhandle2;
  mstruct.lifetime = lifetime;
  mstruct.size = thickness;

  mstruct.interval = slidetime;
  mstruct.count = timesdrawn;
  mstruct.index = numtiles;
  mstruct.texnum = texture_id;
  mstruct.color = ((red >> 3) << 10) | ((green >> 3) << 5) | (blue >> 3);

  if (autotile)
    mstruct.state = 1;
  else
    mstruct.state = 0;

  mstruct.flags = 0;

  MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING_BOLT, &mstruct);
}

/*
$$ACTION
Weather
Create lighting between gunpoints [i:Gunpoint1=0] & [i:Gunpoint2=1] of [o:Object=OWNER]; with [f:Lifetime=1.0],
[f:Thickness=1.0], [i:NumTiles=1], [u:Texture], [f:SlideTime=0], [i:TimesDrawn=1], and
color=[i:Red=255],[i:Green=255],[i:Blue=255], AutoTile=[b:AutoTile=false] aLightningCreateGunpoints Create lighting
between gunpoints Creates a lighting effect between two specified gunpoints on an object

Parameters:
  Object:  Where the lighting is created
  Gunpoint1,Gunpoint2: The points between which the lightning is created
  Lifetime: How long the lighting lasts
  Thickness: How thick the lightning is
  NumTiles: How many times to tile the texture within the bolt
  Texture: The texture to be used for the lighting
  SlideTime: The time it will take to slide the entire bolt once
  TimesDrawn: The number of times to draw the bolt (saturation)
  Red, Green, Blue: The color of the lighting (0-255)
  AutoTile - For automatic UV tiling based on the length of the bolt
$$END
*/
void aLightningCreateGunpoints(int gunpoint1, int gunpoint2, int objhandle, float lifetime, float thickness,
                               int numtiles, int texture_id, float slidetime, int timesdrawn, int red, int green,
                               int blue, bool autotile) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);
  if (mstruct.roomnum == -1)
    return;

  mstruct.g1 = gunpoint1;
  mstruct.g2 = gunpoint2;

  mstruct.lifetime = lifetime;
  mstruct.size = thickness;
  mstruct.interval = slidetime;
  mstruct.count = timesdrawn;
  mstruct.index = numtiles;
  mstruct.texnum = texture_id;
  mstruct.color = ((red >> 3) << 10) | ((green >> 3) << 5) | (blue >> 3);

  if (autotile)
    mstruct.state = 1;
  else
    mstruct.state = 0;

  mstruct.flags = 1;

  MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING_BOLT, &mstruct);
}

/*
$$ACTION
User Vars
Set user flag [e:UserFlag] to [b:True/False]
aUserFlagSet
Set user flag
  Set a flag to true or flase

Parameters:
  UserFlag: The variable to set
  True/False: What to set the flag to
$$END
*/
void aUserFlagSet(int flagnum, bool state) {
  if ((flagnum >= 0) && (flagnum < 32)) {
    int bit = 1 << flagnum;
    if (state)
      User_flags |= bit;
    else
      User_flags &= ~bit;
  }
}

/*
$$ACTION
User Vars
Set user var [e:UserVar] to [f:value]
aUserVarSet
Set user var
  Set a user variable to specific value

Parameters:
  UserVar: The variable to set
  Value: The value assigned to the variable
$$END
*/
void aUserVarSet(int varnum, float value) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    User_vars[varnum] = value;
}

/*
$$ACTION
User Vars
Increment user var [e:UserVar]
aUserVarInc
Increment user var
  Adds one to a user variable

Parameters:
  UserVar: The variable to increment
$$END
*/
void aUserVarInc(int varnum) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    User_vars[varnum]++;
}

/*
$$ACTION
User Vars
Decrement user var [e:UserVar]
aUserVarDec
Decrement user var
  Subtracts one to a user variable

Parameters:
  UserVar: The variable to decrement
$$END
*/
void aUserVarDec(int varnum) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    User_vars[varnum]--;
}

/*
$$ACTION
User Vars
Add [f:value] to user var [e:UserVar]
aUserVarAdd
Add to user var
  Adds to a user variable

Parameters:
  Value: The amount to add to the user variable
  UserVar: The variable to be modified
$$END
*/
void aUserVarAdd(float value, int varnum) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    User_vars[varnum] += value;
}

/*
$$ACTION
User Vars
Subtract [f:value] from user var [e:UserVar]
aUserVarSub
Subtract from user var
  Subtracts from a user variable

Parameters:
  Value: The amount to subtract from the user variable
  UserVar: The variable to be modified
$$END
*/
void aUserVarSub(float value, int varnum) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    User_vars[varnum] -= value;
}

/*
$$ENUM Lock/Unlock
0:UNLOCK
1:LOCK
$$END
*/

/*
$$ACTION
Doors
[e:Lock/Unlock] door [d:DoorName]
aDoorLockUnlock
Lock/Unlock door
  Locks or unlocks the specified door

Parameters:
  DoorName: the object name of the door to be locked or unlocked
$$END
*/
void aDoorLockUnlock(int state, int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_DOOR_LOCK_STATE, &mstruct);
}

/*
$$ACTION
Doors
Activate door [d:Door]
aDoorActivate
Activate door
  Activates (i.e. opens and possibly closes) the specified door

Parameters:
  Door: the object of the door to be activated
$$END
*/
void aDoorActivate(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_CallFunction(MSAFE_DOOR_ACTIVATE, &mstruct);
}

/*
$$ACTION
Doors
Set door [d:Door] position to [p:Position]
aDoorSetPos
Set door position
  Moves the door to the specified position

Parameters:
  Door: the object of the door to be set
  Position: the position of the door, with 0% being fully closed and 100% fully open
$$END
*/
void aDoorSetPos(int objhandle, float pos) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.scalar = pos;

  MSafe_CallFunction(MSAFE_DOOR_POSITION, &mstruct);
}

/*
$$ACTION
Doors
Stop door [d:Door]
aDoorStop
Stop door
  Stops the specified door if it's animating

Parameters:
  Door: the object of the door to stop
$$END
*/
void aDoorStop(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_CallFunction(MSAFE_DOOR_STOP, &mstruct);
}

/*
$$ACTION
Misc
Create Popup View at gunpoint [i:GunPoint] of [o:Object] for [f:Time=10.0] seconds with zoom [f:Zoom=1.0]
aCreatePopupView
  Creates a temorary view window

Parameters:
  GunPoint: the gun number where the viewer should be placed
  Object: the object that is the viewer
  Time: how long the view lasts.  If time set to 0, popup stays up until explicitly closed.
  Zoom: the relative zoom of the viewer camera. 1.0 is the normal zoom.
$$END
*/
void aCreatePopupView(int gunpoint, int objref, float time, float zoom) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.interval = time;
  mstruct.gunpoint = gunpoint;
  mstruct.scalar = zoom;

  MSafe_CallFunction(MSAFE_MISC_POPUP_CAMERA, &mstruct);
}

/*
$$ACTION
Misc
Close the popup view
aClosePopupView
  Closes the popup view, if it's up

Parameters:
  None.
$$END
*/
void aClosePopupView() { MSafe_CallFunction(MSAFE_MISC_CLOSE_POPUP, NULL); }

/*
$$ACTION
Objects
Set object [o:Object] shields to [f:Shields]
aObjSetShields
Set object shields
  Sets an object's shields to a specific value

Parameters:
  Object: the object whose shields are being set
  Shields: the value to assign to the object's shields
$$END
*/
void aObjSetShields(int objref, float shields) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.shields = shields;

  MSafe_CallFunction(MSAFE_OBJECT_SHIELDS, &mstruct);
}

/*
$$ACTION
Objects
Set object [o:Object] energy to [f:Energy]
aObjSetEnergy
Set object energy
  Sets an object's energy to a specific value

Parameters:
  Object: the object whose energy are being set
  Energy: the value to assign to the object's energy
$$END
*/
void aObjSetEnergy(int objref, float energy) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.energy = energy;

  MSafe_CallFunction(MSAFE_OBJECT_ENERGY, &mstruct);
}

/*
$$ACTION
Objects
Play object [o:Object] animation from frame [i:StartFrame] to [i:EndFrame=1], cycle time = [f:CycleTime=1.0], looping =
[b:Looping=FALSE] aObjPlayAnim Play object animation Plays an animation for an object

Parameters:
  Object: the object to animate
  StartFrame: the frame number of the start of the animation
  EndFrame: the frame number of the end of the animation
  CycleTime: how long the entire animation takes
  Looping: if true, animation repeats.  If false, animation plays once
$$END
*/
void aObjPlayAnim(int objref, int startframe, int endframe, float cycletime, bool looping) {
  int flags = 0;

  if (looping)
    flags |= AIAF_LOOPING;

  Obj_SetCustomAnim(objref, (float)startframe, (float)endframe, cycletime, flags, -1, -1);
}

/*
$$ACTION
Objects
Damage object [o:Object] by [f:DamageAmount]
aObjApplyDamage
Damage object
  Applies damage to an object

Parameters:
  Object: the object to damage
  DamageAmount:  how much damage to apply to the object (scaled by difficulty level)
$$END
*/
void aObjApplyDamage(int objref, float damage) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.killer_handle = objref;
  mstruct.damage_type = 0;
  mstruct.amount = damage;

  MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
}

/*
Death info

$$ENUM DeathDelayType
0:No Delay
1:Delay Min/Max
2:Delay from Anim
$$END

$$ENUM DeathExplosionSize
0:Small
1:Medium
2:Large
$$END

$$FLAG DeathFlags
4:During Delay: Sparks
8:During Delay: Loses anti-grav
16:During Delay: Smokes
1048576:During Delay: Flies in air
2097152:During Delay: Fireballs
4194304:During Delay: Fades away
32:On Death: Fireballs
64:On Death: Breaks apart
128:On Death: Blast ring
256:On Death: Remains
512:On Death: Loses anti-grav
8388608:On Death: Fades away
4096:On Contact: Fireball
8192:On Contact: Breaks apart
16384:On Contact: Blask ring
32768:On Contact: Remains
65536:Debris: Smokes
131072:Debris Death: Fireball
262144:Debris Death: Blast ring
524288:Debris Death: Remains
$$END

$$ACTION
Objects
Kill object [o:Object]; delay type = [e:DeathDelayType], explosion size = [e:DeathExplosionSize], death flags =
[g:DeathFlags], Min/Max delay = [f:MinDelay] / [f:MaxDelay] aObjKill Kill Object Kills the specified object using the
specified death info

Parameters:
  Object: the object to kill
$$END
*/
void aObjKill(int objhandle, int delay_type, int expl_size, int death_flags, float min_delay, float max_delay) {
  death_flags |= (expl_size << DF_EXPL_SIZE_SHIFT);

  if (delay_type == 2)
    death_flags |= DF_DELAY_FROM_ANIM;

  if (delay_type == 0)
    min_delay = max_delay = 0;

  Obj_Kill(objhandle, OBJECT_HANDLE_NONE, 1000.0f, death_flags, min_delay, max_delay);
}

/*
$$ACTION
Objects
Kill object [o:Object] with its default death
aObjDestroy
Kill Object with default death
  Kills the specified object using the object's default death

Parameters:
  Object: the object to kill
$$END
*/
void aObjDestroy(int objhandle) { Obj_Kill(objhandle, OBJECT_HANDLE_NONE, 1000.0f, -1, 0.0, 0.0); }

/*
$$ACTION
Objects
Delete object [o:Object]
aObjDelete
Delete Object
  Delete the specified object.  The object disappears with no death.

Parameters:
  Object: the object to delete
$$END
*/
void aObjDelete(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.playsound = 0;

  MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mstruct);
}

/*
$$ACTION
Objects
Set object [o:Object] lighting distance to [f:Distance]
aObjSetLightingDist
Set object lighting distance
  Sets the lighting distance for an object

Parameters:
  Object: the object to set
  Distance: how far the light from the object will cast
$$END
*/
void aObjSetLightingDist(int objhandle, float dist) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.light_distance = dist;

  MSafe_CallFunction(MSAFE_OBJECT_LIGHT_DIST, &mstruct);
}

/*
$$ACTION
Objects
Set object [o:Object] lighting color = [f:Red=0.5],[f:Green=0.5],[f:Blue=0.5]
aObjSetLightingColor
Set object lighting color
  Sets the lighting color for an object

Parameters:
  Object: the object to set
  R,G,B: the fog color (0.0 to 1.0 for each of R,G, & B)
$$END
*/
void aObjSetLightingColor(int objhandle, float r, float g, float b) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.r1 = r;
  mstruct.g1 = g;
  mstruct.b1 = b;

  MSafe_CallFunction(MSAFE_OBJECT_LIGHT_COLOR, &mstruct);
}

/*
$$ACTION
Objects
[e:Enable/Disable] gravity for object [o:Object]
aObjGravityEnable
Enable/Disable object gravity
  Enable or Disable gravity for the specified object

Parameters:
  Enable/Disable: whether gravity should be on or off
  Object: the object to set
$$END
*/
void aObjGravityEnable(int enable, int objhandle) {
  int flags = PF_GRAVITY;

  Obj_Value(objhandle, enable ? VF_SET_FLAGS : VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
}

/*
Object movement types
$$ENUM MovementType
0:None
1:Physics
2:Walking
$$END
*/

/*
$$ACTION
Objects
Set movement type for [o:Object] to [e:MovementType]
aObjSetMovementType
Set movement type for object
  Sets the movement type for an object

Parameters:
  Object: the object to set
  MovementType: how this object moves
$$END
*/
void aObjSetMovementType(int objhandle, int mtype) { Obj_Value(objhandle, VF_SET, OBJV_C_MOVEMENT_TYPE, &mtype); }

/*
$$ACTION
Objects
Set object [o:Object] movement direction = <[f:X],[f:Y],[f:Z]>, speed = [f:Speed=1.0]
aObjSetVelocity
Set object movement direction and speed
  Sets the movement direction and speed for an object

Parameters:
  Object: the object to set
  X,Y,Z: the direction vector for the wind
  Speed: the speed of the wind (10.0 is faster than the player ship)
$$END
*/
void aObjSetVelocity(int objhandle, float x, float y, float z, float speed) {
  vector velocity;

  velocity.x = x * speed;
  velocity.y = y * speed;
  velocity.z = z * speed;

  Obj_Value(objhandle, VF_SET, OBJV_V_VELOCITY, &velocity);
}

/*
$$ACTION
Rooms
Turn [e:On/Off] Strobe in room [r:Room]
aRoomSetLightingStrobe
Turn On/Off strobe in room
  Turns on or off the light stobe in a room

Parameters:
  On/Off: whether the stobe should be on or off
  Room: the room to set
$$END
*/
void aRoomSetLightingStrobe(int state, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_ROOM_LIGHT_STROBE, &mstruct);
}

/*
$$ACTION
Rooms
Turn [e:On/Off] Flicker in room [r:Room]
aRoomSetLightingFlicker
Turn On/Off flicker in room
  Turns on or off the light flicker in a room

Parameters:
  On/Off: whether the flicker should be on or off
  Room: the room to set
$$END
*/
void aRoomSetLightingFlicker(int state, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_ROOM_LIGHT_FLICKER, &mstruct);
}

/*
$$ACTION
Rooms
Turn [e:On/Off] fuelcen in room [r:Room]
aRoomSetFuelcen
Turn On/Off fuelcen in room
  Turns on or off the fuelcen in a room

Parameters:
  On/Off: whether the fuelcen should be on or off
  Room: the room to set
$$END
*/
void aRoomSetFuelcen(int state, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_ROOM_REFUEL, &mstruct);
}

/*
$$ACTION
Rooms
Set room [r:Room] lighting pulse time = [f:PulseTime] offset = [f:PulseOffset]
aRoomSetLightingPulse
Set room lighting pulse values
  Sets the lighting pulse values for a room

Parameters:
  Room: the room to set
  PulseTime: how long a pulse cycle takes, or 0 to turn off pulse
  PulseOffset: the time offset for this pulse
$$END
*/
void aRoomSetLightingPulse(int roomnum, float time, float offset) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.pulse_time = (uint8_t)(time * 100);
  mstruct.pulse_offset = (uint8_t)(offset * 100);

  MSafe_CallFunction(MSAFE_ROOM_LIGHT_PULSE, &mstruct);
}

/*
$$ACTION
Misc
Set waypoint [i:Number]
aSetWaypoint
Set waypoint
  Sets the specified waypoint as active

Parameters:
  Number: which waypoint to set
$$END
*/
void aSetWaypoint(int number) {
  msafe_struct mstruct;

  mstruct.index = number;

  MSafe_CallFunction(MSAFE_MISC_WAYPOINT, &mstruct);
}

/*
$$ACTION
Spew
Turn ON spew from [o:Object] at gunpoint
[i:GunNum];[e:SpewType=7],[f:Mass=0.0],[f:Drag=0.0],[g:PhysicsFlags=65536:100480],[b:IsRealObject=FALSE],[f:BlobLifetime=1.5],[f:BlobInterval=0.15],[f:SpewLife=30.0],[f:BlobSize=4.0],[f:BlobSpeed=20.0],[b:Randomize].
Handle = [e:SpewHandle] aTurnOnSpew Turn on spew Turns on spew and sets the spew type and other variables

Parameters:
  Object:  the object to spew from
  GunNum: the gunpoint on the object to spew from, or -1 to spew from center of object
  SpewType: The type of effect the blobs of spew should be
  Mass: the mass of each blob of spew
  Drag: the drag of the blob as it moves through the atmosphere
  PhysicsFlags: how the slews blobs are treated by the physics
  IsRealObject: if set than the spew blobs are real objects, else it's just a viseffect (leave it as is unless you know
what you are doing) BlobLifetime: the lifetime of each blob of spew BlobInterval: how often a new blob of spew should be
created SpewLife: the lifetime of the spewer (-1 for infinite) BlobSize: the size of each blob of spew BlobSpeed: the
speed of each blob spew Randomize: if set than BlobSize, BlobSpeed and BlobLifetime are randomized a little (+/- some)
for each blob SpewHandle: Where to store the handle for this spewer
$$END
*/
void aTurnOnSpew(int objref, int gunpoint, int effect_type, float mass, float drag, int gravity_type, uint8_t isreal,
                 float lifetime, float interval, float longevity, float size, float speed, uint8_t random,
                 int handle_slot) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.gunpoint = gunpoint;
  mstruct.effect_type = effect_type;
  mstruct.mass = mass;
  mstruct.drag = drag;
  mstruct.phys_info = gravity_type;
  mstruct.is_real = isreal;
  mstruct.lifetime = lifetime;
  mstruct.interval = interval;
  mstruct.longevity = longevity;
  mstruct.size = size;
  mstruct.speed = speed;
  mstruct.random = (random) ? SPEW_RAND_SIZE | SPEW_RAND_LIFETIME | SPEW_RAND_SPEED : 0;

  MSafe_CallFunction(MSAFE_OBJECT_START_SPEW, &mstruct);

  if ((handle_slot >= 0) && (handle_slot < MAX_SPEW_HANDLES))
    Spew_handles[handle_slot] = mstruct.id;
}

/*
$$ACTION
Spew
Turn OFF spew from [e:SpewHandle]
aTurnOffSpew
Turn off spew
  Turns off spew that was created with Turn On Spew. Pass in the handle given by Turn On Spew.

Parameters:
  SpewHandle: the handle of the spewer to stop
$$END
*/
void aTurnOffSpew(int handle_slot) {
  msafe_struct mstruct;

  if ((handle_slot >= 0) && (handle_slot < MAX_SPEW_HANDLES)) {

    mstruct.id = Spew_handles[handle_slot];

    if (mstruct.id != SPEW_INVALID_HANDLE) {
      MSafe_CallFunction(MSAFE_OBJECT_STOP_SPEW, &mstruct);
      Spew_handles[handle_slot] = SPEW_INVALID_HANDLE;
    }
  }
}

/*
$$ACTION
Objects
Attach new object of type [a:ChildTypeName] attachpoint [i:ChildPoint] to object [o:Parent] at attachpoint
[i:ParentPoint] aAttachObject Attach new object Creates a new object attached to another object

Parameters:
$$END
*/
void aAttachObject(const char *objtypename, int childpoint, int objref, int parentpoint) {
  int child_handle;
  int child_type = Obj_FindType(objtypename);
  int child_id = Obj_FindID(objtypename);

  if (child_id >= 0) {

    msafe_struct mstruct;
    mstruct.objhandle = objref;
    MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
    MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);

    child_handle = Obj_Create(child_type, child_id, mstruct.roomnum, &mstruct.pos);

    if (child_handle != OBJECT_HANDLE_NONE) {
      if (!Obj_AttachObjectAP(objref, parentpoint, child_handle, childpoint, 1)) {

        //!!Error attaching, so delete new object
      }
    }
  }
}

/*
$$ACTION
Objects
UnAttach [o:AttachedObject] from an object
aUnAttachObject
UnAttach an object from another one
  Unattaches an object

Parameters:
$$END
*/
void aUnAttachObject(int objref) { Obj_UnattachFromParent(objref); }

/*
$$ACTION
Objects
Object [o:ParentObject] drop all attached objects
aDropObjects
Drop attached objects
  Makes an object drop objects attached to it

Parameters:
$$END
*/
void aDropObjects(int objref) { Obj_UnattachChildren(objref); }

/*
$$ACTION
Objects
Attach existing object [o:Child] attachpoint [i:ChildPoint] to object [o:Parent] at attachpoint [i:ParentPoint]
aAttachExistingObject
Attach existing object to another object
  Attaches an existing object to another object

Parameters:
$$END
*/
void aAttachExistingObject(int child_ref, int childpoint, int objref, int parentpoint) {
  if (!Obj_AttachObjectAP(objref, parentpoint, child_ref, childpoint, 1)) {

    //!!Error attaching, so delete new object
  }
}

/*
$$ACTION
Sound && Music
Set music region to [e:Region] for player [o:PlayerObject=IT]
aMusicSetRegion
Set music region
  Sets the specified region as the active region for the music system

Parameters:
  Region: which region is now active
  PlayerObject: which player gets the music change
$$END
*/
void aMusicSetRegion(int region_num, int objhandle) {
  msafe_struct mstruct;

  mstruct.state = 0; // specific player
  mstruct.index = region_num;
  mstruct.objhandle = objhandle;

  MSafe_CallFunction(MSAFE_MUSIC_REGION, &mstruct);
}

/*
$$ACTION
Sound && Music
Set music region to [e:Region] for all players
aMusicSetRegionAll
Set music region for all players
  Sets the specified region as the active region for the music system for all players

Parameters:
  Region: which region is now active
$$END
*/
void aMusicSetRegionAll(int region_num) {
  msafe_struct mstruct;

  mstruct.state = 0; // all players
  mstruct.index = region_num;

  MSafe_CallFunction(MSAFE_MUSIC_REGION, &mstruct);
}

/*
$$ACTION
Timer
Generate object [o:Object] timer event in [f:Time] seconds with ID [e:TimerID]
aSetObjectTimer
Generate object timer event
  Sets an object timer to go off in the specified amount of time

Parameters:
  Object: the object to receive the timer notification
  Time: how long in seconds until notification
  TimerID: the ID for this timer
$$END
*/
void aSetObjectTimer(int objref, float time, int id) {
  tOSIRISTIMER timer_info;

  timer_info.flags = 0;
  timer_info.repeat_count = 0;
  timer_info.object_handle = objref;
  timer_info.object_handle_detonator = OBJECT_HANDLE_NONE;
  timer_info.timer_interval = time;
  timer_info.id = id;

  Scrpt_CreateTimer(&timer_info);
}

/*
$$ACTION
Timer
Generate level timer event in [f:Time] seconds using with ID [e:TimerID]
aSetLevelTimer
Generate level timer event
  Sets a level timer to go off in the specified amount of time

Parameters:
  Time: how long in seconds until notification
  TimerID: the ID for this timer
$$END
*/
void aSetLevelTimer(float time, int id) {
  tOSIRISTIMER timer_info;

  timer_info.flags = OTF_LEVEL;
  timer_info.repeat_count = OTF_LEVEL;
  timer_info.object_handle_detonator = OBJECT_HANDLE_NONE;
  timer_info.timer_interval = time;
  timer_info.id = id;

  Scrpt_CreateTimer(&timer_info);
}

/*
$$ACTION
Timer
Cancel Timer [e:TimerID]
aCancelTimer
Cancels a timer event
  Cancels a timer

Parameters:
  TimerID: the ID for this timer
$$END
*/
void aCancelTimer(int id) { Scrpt_CancelTimerID(id); }

/*
$$ACTION
Timer
Show Timer [e:TimerID] on HUD
aTimerShow
Show Timer on HUD
  Shows the specified timer on the HUD

Parameters:
  TimerID: the ID for this timer
$$END
*/
void aTimerShow(int id) {
  msafe_struct mstruct;

  mstruct.index = id;
  mstruct.color = GR_RGB(0, 255, 0);
  MSafe_CallFunction(MSAFE_MISC_START_TIMER, &mstruct);
}

/*
$$ACTION
Mission
End level
aEndLevel
End level
  Terminates the level

Parameters:
  None.
$$END
*/
void aEndLevel() {
  msafe_struct mstruct;

  mstruct.state = 1; // success
  MSafe_CallFunction(MSAFE_MISC_END_LEVEL, &mstruct);
}

/*
$$ACTION
Mission
Fail Level
aFailLevel
Fail Level
  Terminates the level in failure.  Level will restart.

Parameters:
  None.
$$END
*/
void aFailLevel() {
  msafe_struct mstruct;

  mstruct.state = 0; // failure
  MSafe_CallFunction(MSAFE_MISC_END_LEVEL, &mstruct);
}

/*
$$ACTION
Cinematics
Start endlevel sequence; camera = [o:Camera], path = [h:PlayerPath], time = [f:Time=10.0], text = [s:Text]
aStartEndlevelSequence
Start endlevel sequence
  Start the endlevel camera sequence

Parameters:
  Camera: the viewer object for the sequence
  PlayerPath: the path the player ship follows
  Time: how long before the level ends
  Text: Any text (if any) you want to display (pass empty message if you want none)
$$END
*/
void aStartEndlevelSequence(int objhandle, int pathid, float time, const char *text) {
  tCannedCinematicInfo info;

  info.object_to_use_for_point = objhandle;
  info.target_pathid = pathid;
  info.text_to_display = text;
  info.time = time;
  info.type = CANNED_LEVEL_END_POINT;

  Cine_StartCanned(&info);
}

/*
$$ACTION
Cinematics
Start endlevel sequence with camera on path; camera path = [h:CameraPath], player path = [h:PlayerPath], time =
[f:Time=10.0], text = [s:Text] aStartEndlevelSequencePath Start endlevel sequence on Path Start the endlevel camera
sequence, with the camera on a path

Parameters:
  CameraPath: the path the camera should follow for the sequence
  PlayerPath: the path the player ship follows
  Time: how long before the level ends
  Text: Any text (if any) you want to display (pass empty message if you want none)
$$END
*/
void aStartEndlevelSequencePath(int camerapath, int pathid, float time, const char *text) {
  tCannedCinematicInfo info;

  info.camera_pathid = camerapath;
  info.target_pathid = pathid;
  info.text_to_display = text;
  info.time = time;
  info.type = CANNED_LEVEL_END_PATH;

  Cine_StartCanned(&info);
}

/*
$$ACTION
Cinematics
Fade Screen to white, and end level time = [f:Time=10.0], text = [s:Text]
aFadeWhiteAndEndlevel
Fades the screen to white and ends the level

Parameters:
  Time: how long before the level ends (the screen fades to white across this time)
  Text: Any text (if any) you want to display (pass empty message if you want none)
$$END
*/
void aFadeWhiteAndEndlevel(float time, const char *text) {
  tCannedCinematicInfo info;

  info.text_to_display = text;
  info.time = time;
  info.type = CANNED_LEVEL_END_FADE_WHITE;

  Cine_StartCanned(&info);
}

/*
$$ACTION
Players
Fade Screen out and move [o:Player] to Position Clipboard
aFadeAndMovePlayer
Fades the screen out and 'warps' the player to the position in the
position clipboard.

Parameters:
        Player: the player to move
$$END
*/
void aFadeAndMovePlayer(int Player) {
  if (PositionClipboard.has_pos) {
    tCannedCinematicInfo info;

    info.room = PositionClipboard.room;
    info.pos = PositionClipboard.pos;
    info.orient = PositionClipboard.orient;
    info.target_objhandle = Player;
    info.type = CANNED_MOVE_PLAYER_FADE;

    Cine_StartCanned(&info);
  } else {
    mprintf(0, "No ClipBoard Data Filled In\n");
  }
}

/*
$$ACTION
Mission
Set mission flag [i:FlagNum] to [b:State]
aMissionSetFlag
Set mission flag
  Sets the specified mission flag

Parameters:
  FlagNum: the flag to set
  State: the value to set the flag to
$$END
*/
void aMissionSetFlag(int flagnum, bool state) { Msn_FlagSet(flagnum, state); }

/*
$$ACTION
Mission
Set secret level flag to [b:State]
aMissionSetSecretFlag
Set secret level flags
  Sets/Clears the secret level flag, so the next secret level will be enabled/disabled

Parameters:
  State: whether to set or clear the flag
$$END
*/
void aMissionSetSecretFlag(bool state) { Msn_FlagSet(32, state); }

/*
$$ACTION
Mission
Set level objective flag [i:FlagNum] to [b:State=1]
aMissionSetLevelFlag
Set level objective flag
  Sets the specified level objective flag

Parameters:
  FlagNum: the flag to set
  State: the value to set the flag to
$$END
*/
void aMissionSetLevelFlag(int flagnum, bool state) {
  //!!Add code here
}

/*
$$ACTION
Sound && Music
Play 2D Sound [n:Sound] for player [o:PlayerObject=IT], volume = [p:Volume=1.0:0.0|1.0]
aSoundPlay2DObj
Play 2D Sound
  Plays a sound in 2D

Parameters:
  Sound: the sound to play
  PlayerObject: the player who hears the sound
  Volume: how loud to play the sound
$$END
*/
void aSoundPlay2DObj(int soundnum, int objhandle, float volume) {
  msafe_struct mstruct;

  mstruct.state = 1; // specific player
  mstruct.index = soundnum;
  mstruct.objhandle = dfGetPlayer(objhandle);
  mstruct.volume = volume;

  MSafe_CallFunction(MSAFE_SOUND_2D, &mstruct);
}

/*
$$ACTION
Sound && Music
Play 2D Sound [n:Sound] for all players, volume = [p:Volume=1.0:0.0|1.0]
aSoundPlay2D
Play 2D Sound
  Plays a sound in 2D

Parameters:
  Sound: the sound to play
  Volume: how loud to play the sound
$$END
*/
void aSoundPlay2D(int soundnum, float volume) {
  msafe_struct mstruct;

  mstruct.state = 0; // all players
  mstruct.index = soundnum;
  mstruct.volume = volume;

  MSafe_CallFunction(MSAFE_SOUND_2D, &mstruct);
}

/*
$$ACTION
Sound && Music
Play Sound [n:Sound] from object [o:Object], volume = [p:Volume=1.0:0.0|1.0]
aSoundPlayObject
Play Object Sound
  Plays a sound from an object

Parameters:
  Sound: the sound to play
  Object: the object to attach the sound to
  Volume: how loud to play the sound
$$END
*/
void aSoundPlayObject(int soundnum, int objref, float volume) {
  msafe_struct mstruct;

  mstruct.index = soundnum;
  mstruct.volume = volume;
  mstruct.objhandle = objref;

  MSafe_CallFunction(MSAFE_SOUND_OBJECT, &mstruct);
}

/*
$$ACTION
Sound && Music
Play streaming sound [z:Sound] for all players, volume = [p:Volume=1.0:0.0|1.0]
aSoundPlaySteaming
Play Steaming Sound
  Plays a streaming sound sample

Parameters:
  Sound: the sound to play
  Volume: how loud to play the sound
$$END
*/
void aSoundPlaySteaming(const char *soundname, float volume) {
  msafe_struct mstruct;

  mstruct.state = 0; // all players

  strncpy(mstruct.name, soundname, sizeof(mstruct.name) - 1);
  mstruct.name[sizeof(mstruct.name) - 1] = 0;
  mstruct.volume = volume;

  MSafe_CallFunction(MSAFE_SOUND_STREAMING, &mstruct);
}

/*
$$ACTION
Sound && Music
Play streaming sound [a:SoundName] for all players, volume = [p:Volume=1.0:0.0|1.0]  (TEXT NAME VERSION)
aSoundPlaySteamingText
Play Steaming Sound
  Plays a streaming sound sample

Parameters:
  SoundName: the sound to play
  Volume: how loud to play the sound
$$END
*/
#define aSoundPlaySteamingText aSoundPlaySteaming

/*
$$ACTION
Sound && Music
Play streaming sound [z:Sound] for player [o:PlayerObject=IT], volume = [p:Volume=1.0:0.0|1.0]
aSoundPlaySteamingObj
Play Steaming Sound
  Plays a streaming sound sample

Parameters:
  Sound: the sound to play
  Volume: how loud to play the sound
$$END
*/
void aSoundPlaySteamingObj(const char *soundname, int objhandle, float volume) {
  msafe_struct mstruct;

  mstruct.state = 1; // specific player
  mstruct.objhandle = objhandle;

  strncpy(mstruct.name, soundname, sizeof(mstruct.name) - 1);
  mstruct.name[sizeof(mstruct.name) - 1] = 0;
  mstruct.volume = volume;

  MSafe_CallFunction(MSAFE_SOUND_STREAMING, &mstruct);
}

/*
$$ACTION
Sound && Music
Set volume for object [o:Object] to [p:Volume=1.0:0.0|1.0]
aSoundVolumeObj
Set volume for object sound
  Sets the volume for all sounds attached to an object

Parameters:
  Object - the object whose sound to stop
  Volume - the volume to set
$$END
*/
void aSoundVolumeObj(int objhandle, float volume) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.volume = volume;

  MSafe_CallFunction(MSAFE_SOUND_VOLUME_OBJ, &mstruct);
}

/*
$$ACTION
Sound && Music
Stop sound for object [o:Object]
aSoundStopObj
Stop sound for object
  Stops all sounds attached to an object

Parameters:
  Object - the object whose sound to stop
$$END
*/
void aSoundStopObj(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_CallFunction(MSAFE_SOUND_STOP_OBJ, &mstruct);
}

/*
$$ENUM Ghost/Unghost
0:UNGHOST
1:GHOST
$$END
*/

/*
$$ACTION
Objects
[e:Ghost/Unghost] object [o:Object]
aObjGhostSet
Ghost/Unghost an object
  Ghosts or Unghosts an object

Parameters:
  Ghost/Unghost: whether to ghost or unghost the object
  Object: the object to ghost or unghost
$$END
*/
void aObjGhostSet(int state, int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_CallFunction(state ? MSAFE_OBJECT_GHOST : MSAFE_OBJECT_UNGHOST, &mstruct);
}

/*
$$ACTION
Objects
Hide object [o:Object]
aObjHide
Hide an object
  Makes an object not render. It will still be there but be invisible.

Parameters:
  Object: the object to hide
$$END
*/
void aObjHide(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_CallFunction(MSAFE_OBJECT_NO_RENDER, &mstruct);
}

/*
$$ACTION
Objects
Make object [o:Object] invulnerable for [i:Time=20.0]
aObjMakeInvuln
Makes object invulnerable
  Makes object invulnerable

Parameters:
  Object: the object to make invulnerable
  Time: how long the object stays invulnerable
$$END
*/
void aObjMakeInvuln(int objref, int time) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.state = 1;
  mstruct.lifetime = time;

  MSafe_CallFunction(MSAFE_OBJECT_INVULNERABLE, &mstruct);
}

/*
$$ACTION
Objects
Make object [o:Object] vulnerable
aObjMakeVulnerable
Makes object invulnerable
  Makes object invulnerable

Parameters:
  Object: the object to make vulnerable again

$$END
*/
void aObjMakeVulnerable(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  mstruct.state = 0;
  MSafe_CallFunction(MSAFE_OBJECT_INVULNERABLE, &mstruct);
}

/*
$$ACTION
Objects
Deform object [o:Object] by [f:Amount=.1:0|1.0] for [f:Time] seconds
aObjDeform
Deform object
  Deforms an object (applies the microwave cannon effect)

Parameters:
  Object: the object to deform
  Amount: how much to deform the object. 0.1 is a "normal" amount; 0.4 is a big amount.
  Time: how long to deform the object
$$END
*/
void aObjDeform(int objhandle, float amount, float time) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.amount = amount;
  mstruct.lifetime = time;

  MSafe_CallFunction(MSAFE_OBJECT_DEFORM, &mstruct);
}

/*
$$ACTION
Objects
Make object [o:Object] spark at a rate of [f:SparkRate=50] for [f:Time] seconds
aObjSpark
Make object spark
  Makes an object have sparks for the given amount of time

Parameters:
  Object: the object to apply sparks to
  SparkRate: how many sparks per second the object will have
  Time: how long the sparking will last
$$END
*/
void aObjSpark(int objhandle, float rate, float time) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.amount = rate;
  mstruct.lifetime = time;

  MSafe_CallFunction(MSAFE_OBJECT_SPARKS, &mstruct);
}

/*
$$ACTION
Misc
Shake viewer by [f:Amount=40.0:0|100.0]
aMiscViewerShake
Shake view
  Shakes the viewer

Parameters:
  Amount: how much to shake the viewer (0-100)
$$END
*/
void aMiscViewerShake(float amount) {
  msafe_struct mstruct;

  mstruct.amount = amount;

  MSafe_CallFunction(MSAFE_OBJECT_VIEWER_SHAKE, &mstruct);
}

/*
$$ACTION
Misc
Shake area around object [o:Object] by [f:Amount=40.0:0|100.0] over a distance of [f:Dist=100]
aMiscShakeArea
Shake the area around an object
  Shakes the viewer proportional to the distance to an object

Parameters:
  Object: the epicenter of the shake
  Amount: how much to shake the viewer (0-100)
  Dist: how far away the shake can be felt.
$$END
*/
void aMiscShakeArea(int objhandle, float amount, float dist) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.amount = amount;
  mstruct.scalar = dist;

  MSafe_CallFunction(MSAFE_OBJECT_SHAKE_AREA, &mstruct);
}

/*
$$ACTION
Rooms
Set texture on room [r:Room] face [i:FaceNum] to [u:Texture]
aRoomSetFaceTexture
Change face texture
  Sets the texture for a room face

Parameters:
  Room: the room the face is in
  FaceNum: the face whose texture is changed
  TextureName: the texture to assign to the specified face
$$END
*/
void aRoomSetFaceTexture(int roomnum, int facenum, int texturenum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.facenum = facenum;
  mstruct.index = texturenum;

  MSafe_CallFunction(MSAFE_ROOM_TEXTURE, &mstruct);
}

/*
$$ACTION
Misc
[e:Activate/Deactivate] matcen [m:Matcen]
aMatcenSetState
Activate/Deactivate matcen
Activates or Deactivates a matcen, so it starts or stops producing

Parameters:
  Activate/Deactivate: whether to start or stop the matcen
  Matcen: the matcen to activate
$$END
*/
void aMatcenSetState(int state, int matcen_id) {
  int flags = MSTAT_ACTIVE;

  if (matcen_id >= 0)
    Matcen_Value(matcen_id, state ? VF_SET_FLAGS : VF_CLEAR_FLAGS, MTNV_I_STATUS, &flags);
}

/*
$$ACTION
Misc
[e:Enable/Disable] matcen [m:Matcen]
aMatcenSetEnableState
Enable/disable matcen
Enable or disable a matcen, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
  Matcen: the matcen to enable or disable
$$END
*/
void aMatcenSetEnableState(int state, int matcen_id) {
  int flags = MSTAT_DISABLED;

  if (matcen_id >= 0)
    Matcen_Value(matcen_id, state ? VF_CLEAR_FLAGS : VF_SET_FLAGS, MTNV_I_STATUS, &flags);
}

/*
$$ACTION
Misc
Set matcen [m:Matcen] max produced = [i:MaxProduced=-1], production rate multiplier = [f:Multiplier=1.0], max alive
children = [i:MaxAlive=-1:1|32] aMatcenSetValues Set matcen values Set matcen values for max produced, production rate
multiplier, and max alive children

Parameters:
  Matcen: the matcen to set
  MaxProduced: the total number this matcen will produce in its lifetime, or -1 for no limit
  Multiplier: controls the speed of the matcen. 1.0 is the normal speed
  MaxAlive: the maximum number of created object that will be alive at one time, or -1 for no limit
$$END
*/
void aMatcenSetValues(int matcen_id, int max_produced, float multiplier, int max_alive) {
  if (matcen_id >= 0) {
    Matcen_Value(matcen_id, VF_SET, MTNV_I_MAX_PROD, &max_produced, 0);
    Matcen_Value(matcen_id, VF_SET, MTNV_F_PROD_MULTIPLIER, &multiplier, 0);
    Matcen_Value(matcen_id, VF_SET, MTNV_I_MAX_ALIVE_CHILDREN, &max_alive, 0);
  }
}

/*
$$ACTION
Rooms
Set fog in room [r:Room] to color = [f:Red=0.5],[f:Green=0.5],[f:Blue=0.5], depth = [f:Depth=300.0]
aRoomSetFog
Set room fog
  Sets the fog color and depth for a room

Parameters:
  Room: the room to set
  R,G,B: the fog color (0-1)
  Depth:  how deep the fog should be
$$END
*/
void aRoomSetFog(int roomnum, float r, float g, float b, float depth) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.fog_depth = depth;
  mstruct.fog_r = r;
  mstruct.fog_g = g;
  mstruct.fog_b = b;

  MSafe_CallFunction(MSAFE_ROOM_FOG, &mstruct);
}

/*
$$ACTION
Rooms
Change fog in room [r:Room] to color = [f:Red=0.5],[f:Green=0.5],[f:Blue=0.5], delpth = [f:Depth=200.0] over
[f:Time=20.0] seconds aRoomChangeFog Change room fog Changes the fog in a room over time

Parameters:
  Room: the room to set
  R,G,B: the new fog color (0-1)
  Depth:  how deep the fog should be after the change (starts from the current fog depth)
  Time: how long in seconds the change takes
$$END
*/
void aRoomChangeFog(int roomnum, float r, float g, float b, float depth, float time) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.fog_depth = depth;
  mstruct.fog_r = r;
  mstruct.fog_g = g;
  mstruct.fog_b = b;
  mstruct.interval = time;

  MSafe_CallFunction(MSAFE_ROOM_CHANGING_FOG, &mstruct);
}

/*
$$ACTION
Rooms
Turn fog [e:On/Off] in room [r:Room]
aRoomFogSetState
Turn fog On/Off
  Turns On or Off the fog in a room

Parameters:
  On/Off: whether to turn the fog on or off
  Room: the room in which to turn on or off the fog
$$END
*/
void aRoomFogSetState(int state, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.state = state;

  MSafe_CallFunction(MSAFE_ROOM_FOG_STATE, &mstruct);
}

/*
$$ACTION
Rooms
Toggle fog in room [r:Room]
aRoomToggleFog
Toggle room fog
  Toggles the fog state in a room

Parameters:
  Room: the room in which to turn off the fog
$$END
*/
void aRoomToggleFog(int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;

  MSafe_GetValue(MSAFE_ROOM_FOG_STATE, &mstruct);

  mstruct.state = !mstruct.state;

  MSafe_CallFunction(MSAFE_ROOM_FOG_STATE, &mstruct);
}

/*
$$ACTION
Rooms
Set wind in room [r:Room], direction = <[f:X],[f:Y],[f:Z]>, speed = [f:Speed=1.0]
aRoomSetWind
Set wind in room
  Sets the wind in a room

Parameters:
  Room: the room in which to set the wind
  X,Y,Z: the direction vector for the wind
  Speed: the speed of the wind (10.0 is faster than the player ship)
$$END
*/
void aRoomSetWind(int roomnum, float x, float y, float z, float speed) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  //!!mstruct.wind = *v;
  mstruct.wind.x = x * speed;
  mstruct.wind.y = y * speed;
  mstruct.wind.z = z * speed;

  MSafe_CallFunction(MSAFE_ROOM_WIND, &mstruct);
}

/*
$$ACTION
Rooms
Change wind in room [r:Room] to direction = <[f:X],[f:Y],[f:Z]>, speed = [f:Speed=1.0] over [f:Time=10.0] seconds
aRoomChangeWind
Change wind in room
  Changes the wind in a room over time

Parameters:
  Room: the room in which to set the wind
  X,Y,Z: the direction vector for the wind
  Speed: the speed of the wind (10.0 is faster than the player ship)
  Time: how long the change takes
$$END
*/
void aRoomChangeWind(int roomnum, float x, float y, float z, float speed, float time) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  //!!mstruct.wind = *v;
  mstruct.wind.x = x * speed;
  mstruct.wind.y = y * speed;
  mstruct.wind.z = z * speed;
  mstruct.interval = time;

  MSafe_CallFunction(MSAFE_ROOM_CHANGING_WIND, &mstruct);
}

/*
$$ACTION
AI
Object For [o:Object] turn the AI scripted death flag [e:On/Off]
aSetScriptedDeath
Turn On/Off the AI scripted death flag
  Turns on/off the scripted death flag for the specified object

Parameters:
  Object - the object in question
  On/Off - whether to turn on/off the AI Scripted Death Flag
$$END
*/
void aSetScriptedDeath(int objhandle, int state) {
  int flags = OF_AI_DEATH;

  Obj_Value(objhandle, state ? VF_SET_FLAGS : VF_CLEAR_FLAGS, OBJV_I_FLAGS, &flags);
}

/*
$$ACTION
AI
Turn [e:On/Off] the AI for object [o:Object]
aAISetState
Turn On/Off the AI for object
  Turns on or off the AI for the specified object

Parameters:
  On/Off - whether to turn the AI on or off
  Object - the object whose AI is turned on or off
$$END
*/
void aAISetState(int state, int objhandle) { AI_PowerSwitch(objhandle, state != 0); }

/*
$$ACTION
AI
Set the FOV of [o:Object] to [f:FOV] degrees
aAISetFOV
Sets the FOV for an AI object (0 - 360)
  Sets the FOV for an AI object (0 - 360)

Parameters:
  Object - the object whose AI is turned on or off
  FOV - the number of angles of the FOV
$$END
*/
void aAISetFOV(int objhandle, float fov) {
  fov = cos(fov * PI / (360.0));
  AI_Value(objhandle, VF_SET, AIV_F_FOV, &fov);
}

/*
$$ACTION
AI
Set the Target of [o:Object] to [o:Target]
aAISetTarget
Sets the target for an AI object
  Sets the target for an AI object

Parameters:
  Object - the object whose AI target is being set
  Target - the object to be targetted for attack
$$END
*/
void aAISetTarget(int objhandle, int targethandle) { AI_Value(objhandle, VF_SET, AIV_I_TARGET_HANDLE, &targethandle); }

/*
$$ACTION
AI
Set Team to [e:Teams] for the AI for object [o:Object]
aAISetTeam
Sets the team for a specific object
  Sets the team for a specific object

Parameters:
  Team: Which team you want the object to belong to
  Object - the object whose team you want to change
$$END
*/
void aAISetTeam(int team, int objhandle) {
  int flags = AIF_TEAM_MASK;
  AI_Value(objhandle, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
  flags = team; // AIF_TEAM_REBEL;
  AI_Value(objhandle, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

  int target_handle = OBJECT_HANDLE_NONE;
  AI_Value(objhandle, VF_SET, AIV_I_TARGET_HANDLE, &target_handle);
}

/*
$$ACTION
AI
Clear the [e:GoalPriority=3] prioriity goal for object [o:Object]
aAIClearGoal
Clears a goal for a specific object
        Clears a goal for a specific object

Parameters:
        GoalPriority: The priority of the goal you can to clear
        Object: the object whose goal you want to clear
$$END
*/

void aAIClearGoal(int slot, int handle) { AI_ClearGoal(handle, slot); }

/*
$$ENUM AIModeType
1:Stalker
2:Standard Attack
3:Guardian
4:Stationary Turret
6:Melee
7:Bird Flock
9:Herd
$$END

Luke would additionally like these types:
Wander
Berzerker
Pursue
Sniper
Survival
Sneak Attack
Supervisor

*/

/*
$$ACTION
AI
Set AI mode for object [o:Object] to [e:AIModeType]
aAISetMode
Set AI mode
  Sets the AI mode for an objectTurn ON AI for object

Parameters:
  Object - the object whose AI mode is set
  AIModeType - which mode to set for the object
$$END
*/
void aAISetMode(int objhandle, int modetype) { AI_SetType(objhandle, modetype); }

/*
$$ACTION
AI
Set [o:Object] to have a max speed of [f:MaxSpeed]
aAISetMaxSpeed
Set the max speed of an object
  Set the max speed of an object

Parameters:
  Object - the object whose AI mode is set
  MaxSpeed - Maximum speed
$$END
*/
void aAISetMaxSpeed(int objhandle, float max_speed) { AI_Value(objhandle, VF_SET, AIV_F_MAX_SPEED, &max_speed); }

// Used for all AI Goal calls
#define DEFAULT_INFLUENCE 1.0

/*
Flags for AI Goals

$$FLAG AIGoalFlags
1:Permanent
4:Keep at Completion
16:Object is Target
128:Go Directly to Goal if Visible
256:Force Awareness
512:Objects are Friends
1024:Objects are Species
2048:Objects are Enemies
4096:Orient Velocity
65536:Orient Target
131072:No Reorientation
262144:Orient Goal Object
1048576:Orient Path Node
2097152:Follow Path Exactly
4194304:Reverse at End of Path
8388608:Circle at End of Path
16777216:Follow Path in Reverse Direction
$$END

Flags for AI

$$FLAG AIFlags
1:Weapon Attack 1
2:Weapon Attack 2
4:Melee Attack 1
8:Melee Attack 2
32: Act as team neutral until shot
64:Persistant (always using CPU cycles)
128:Dodging
256:Firing Ranged Weapons
512:Flinching
1024:Determining Targets
2048:Aiming
8192:Auto-avoid walls
16384:Disabled
32768:Team PTMC (WARNING - NEVER SET TWO TEAMS)
65536:Team Rebel (WARNING - NEVER SET TWO TEAMS)
131072:Team Hostile to everyone (WARNING - NEVER SET TWO TEAMS)
196608:Team Neutral to everyone (WARNING - NEVER SET TWO TEAMS)
524288:Orientate to velocity
4194304:Target by distance
8388608:Disable ranged weapon firing (even in script)
16777216:Disable melee attacks (even in script)
33554432:Auto-avoid friends
268435456:Biased Flight Height
536870912:Force awareness (always using CPU cycles)
$$END

User type for Goal IDs

$$USERTYPE GoalID:99

AI Goal slot values

$$ENUM GoalPriority
3:High
0:Low
$$END

$$ENUM Set/Clear
0:Clear
1:Set
$$END

*/

/*
$$ACTION
AI
[e:Set/Clear=1] AI Flags [g:AIFlags=0] for Object [o:Object]
aAIFlags
Sets and clears AI flags
        Sets and clears AI flags

Parameters:
        Set/Clear - Set or Clear the specified flags
        AIFlags - the flags to either set or clear (other flags are not effected)
        Object - The object of which you want to alter the AI flags
$$END
*/
void aAIFlags(int set, int flags, int handle) {
  bool f_team = false;

  // Because its a bitfield, I had to hack a team value...  Team PTMC was 0; so, it was
  // impossible to set...  32768 wasn't used, so I hacked it here.  O' The shame...  :(

  if (!set)
    flags &= ~(AIF_TEAM_MASK);
  else
    f_team = (flags & (AIF_TEAM_MASK | 32768)) != 0;

  // hacked PTMC team value
  flags &= ~(32768);

  // Since it is a bit field... clear out the old value
  if (f_team) {
    int team_mask = AIF_TEAM_MASK;
    AI_Value(handle, VF_CLEAR_FLAGS, AIV_I_FLAGS, &team_mask);
  }

  AI_Value(handle, (set) ? VF_SET_FLAGS : VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
}

/*
$$ACTION
AI
Set AI object [o:Object] goal Priority = [e:GoalPriority=3] circle distance to [f:distance]
aAIGoalSetCircleDistance
Sets the circle distance for a goal
  Sets the circle distance for a goal

Parameters:
  Object - the object who is send to the room
  Priority - priority of the goal in question
$$END
*/
void aAIGoalSetCircleDistance(int objhandle, int slot, float distance) {
  AI_GoalValue(objhandle, slot, VF_SET, AIGV_F_CIRCLE_DIST, &distance);
}

/*
$$ACTION
AI
Send AI object [o:Object] to room [r:Room]; Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags=4352:201109], GoalID =
[e:GoalID=-1] aAIGoalGotoRoom Send AI object to room Instructs an AI object to go to a specific room

Parameters:
  Object - the object who is send to the room
  Room - the room to go do
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalGotoRoom(int objhandle, int roomnum, int slot, int flags, int goalid) {
  vector pos;

  Room_Value(roomnum, VF_GET, RMSV_V_PATH_PNT, &pos, 0);

  AI_AddGoal(objhandle, AIG_GET_TO_POS, slot, DEFAULT_INFLUENCE, goalid, flags, &pos, roomnum);
}

/*
$$ACTION
AI
Send AI object [o:Object] to object [o:Target]; Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags=4352:201109],
GoalID = [e:GoalID=-1] aAIGoalGotoObject Send AI object to a specified object Instructs an AI object to go to a specific
object

Parameters:
  Object - the object who is send to the room
  Target - the object to get to
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalGotoObject(int objhandle, int target, int slot, int flags, int goalid) {
  AI_AddGoal(objhandle, AIG_GET_TO_OBJ, slot, DEFAULT_INFLUENCE, goalid, flags, target);
}

/*
$$ACTION
AI
Send AI object [o:Object] on path [h:Path]; Flags = [g:AIGoalFlags=4352:32706959], GoalID = [e:GoalID=-1], Priority =
[e:GoalPriority=3] aAIGoalFollowPathSimple Send AI object on path Instructs an AI object to follow a path

Parameters:
  Object - the object who is send to the room
  Path - the path to follow
  Flags - the flags for this goal
  GoalID - an ID for this goal
  Priority - The priority of the goal
$$END
*/
void aAIGoalFollowPathSimple(int objhandle, int pathid, int flags, int goalid, int priority = 0) {
  //!!GoalID not used yet

  if (pathid != -1)
    AI_GoalFollowPathSimple(objhandle, pathid, goalid, flags, priority);
}

/*
$$ACTION
AI
Send AI object [o:Object] on path [h:Path] between nodes [i:FirstNode] and [i:LastNode], starting at [i:StartNode];
Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags=4352:32706959], GoalID = [e:GoalID=-1] aAIGoalFollowPath Send AI
object on path Instructs an AI object to follow a path

Parameters:
  Object - the object who is send to the room
  Path - the path to follow
  FirstNode, LastNode - the endpoints of the part of the path to follow
  StartNode - where to start following the path
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalFollowPath(int objhandle, int pathid, int firstnode, int lastnode, int startnode, int slot, int flags,
                       int goalid) {
  if (pathid != -1)
    AI_AddGoal(objhandle, AIG_FOLLOW_PATH, slot, DEFAULT_INFLUENCE, goalid, flags, pathid, firstnode, lastnode,
               startnode);
}

/*
$$ACTION
AI
Make object [o:Picker] (attachpoint [i:PickerPoint]) pick up object [o:Pickee] (attachpoint = [i:PickeePoint]); Aligned
= [b:Aligned]; Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags:463253], GoalID = [e:GoalID=-1] aAIGoalPickUpObject
Make object pick up object
  Make one object pick up another

Parameters:
  Picker - the object doing the picking up
  PickerPoint - the attach point on the picker
  Pickee - the object being picked up
  PickeePoint - the attach point on the pickee
  Aligned - if true, aligns the two object
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalPickUpObject(int pickerhandle, int pickerpoint, int pickeehandle, int pickeepoint, bool aligned, int slot,
                         int flags, int goalid) {
  AI_AddGoal(pickerhandle, AIG_ATTACH_TO_OBJ, slot, DEFAULT_INFLUENCE, goalid, flags, pickeehandle, pickerpoint,
             pickeepoint, 0.0, aligned, 0);
}

/*
$$ACTION
AI
Make object [o:Picker] (attachpoint [i:CarriedObjectPoint]) be set down onto object [o:LandOnObject] (attachpoint =
[i:LandOnPoint]); Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags:463253], GoalID = [e:GoalID=-1]
aAIGoalSetObjectOnObject
Make object pick up object
  Make one object pick up another

Parameters:
  Picker - the object doing the picking up
  CarriedObjectPoint - the attach point on the picker
  LandOnObject - the object being picked up
  LandOnPoint - the attach point on the pickee
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalSetObjectOnObject(int pickerhandle, int pickerpoint, int pickeehandle, int pickeepoint, int slot, int flags,
                              int goalid) {
  AI_AddGoal(pickerhandle, AIG_PLACE_OBJ_ON_OBJ, slot, DEFAULT_INFLUENCE, goalid, flags, pickeehandle, pickerpoint,
             pickeepoint, 0.0, true, 0);
}

/*
$$ACTION
AI
Make object [o:LandingObject] (attachpoint [i:LanderAttachPoint]) land on object [o:ObjectToLandOn] (attachpoint =
[i:LandOnObjectAttachPoint]); Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags:463253], GoalID = [e:GoalID=-1]
aAIGoalLandOnObject
Make an object land on another object
  Make one object and on another object

Parameters:
  LandingObject - the object that is going to land
  LanderAttachPoint - the attach point that the landing object uses
  ObjectToLandOn - the object being landed on
  LandOnObjectAttachPoint - the attach point of the object being landed on
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalLandOnObject(int pickerhandle, int pickerpoint, int pickeehandle, int pickeepoint, int slot, int flags,
                         int goalid) {
  AI_AddGoal(pickerhandle, AIG_ATTACH_TO_OBJ, slot, DEFAULT_INFLUENCE, goalid, flags | GF_IS_ATTACH_CHILD, pickeehandle,
             pickerpoint, pickeepoint, 0.0, true, 0);
}

/*
$$ACTION
AI
Make object [o:Picker] (attachpoint [i:PickerPoint]) pick up object [o:Pickee] with radius = [p:RadiusRatio=1.0];
Priority = [e:GoalPriority=3], Flags = [g:AIGoalFlags:463253], GoalID = [e:GoalID=-1] aAIGoalPickUpObjectRad Make object
pick up object Make one object pick up another

Parameters:
  Picker - the object doing the picking up
  PickerPoint - the attach point on the picker
  Pickee - the object being picked up
  RadiusRatio - how close to hold the object relative to the object's size
  Priority - if High, overrides the default goals; if Low, does only when the object has no other enabled goals
  Flags - the flags for this goal
  GoalID - an ID for this goal
$$END
*/
void aAIGoalPickUpObjectRad(int pickerhandle, int pickerpoint, int pickeehandle, float radius, int slot, int flags,
                            int goalid) {
  AI_AddGoal(pickerhandle, AIG_ATTACH_TO_OBJ, slot, DEFAULT_INFLUENCE, goalid, flags, pickeehandle, pickerpoint, -1,
             radius, 0, 1);
}

/*
$$ACTION
Objects
[e:Set/Clear=1] Physics Flags [g:PhysicsFlags=0] for Object [o:Object]
aPhysFlags
Set/Clear Physics flags
        Sets or and clears physics flags

Parameters:
        Set/Clear - Set or Clear the specified flags
        PhysicsFlags - the flags to either set or clear (other flags are not effected)
        Object - The object of which you want to alter the physics flags
$$END
*/
void aPhysFlags(int set, int flags, int handle) {
  Obj_Value(handle, (set) ? VF_SET_FLAGS : VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
}

/*
$$ACTION
Cinematics
Simple letterbox format cinematic, using path [h:CameraPath], with text [s:Text] targeting [o:Target] for
[f:Seconds=10.0f] has fade in [b:FadeIn] aCinematicSimple CinematicSimple This creates a simple cinematic, in Letterbox
mode.  The camera will follow the given path. And the given text will be shown at the bottom of the screen.  There is no
'quick exit' by keypress.  To do more than one line of text, seperate each line of text using a pipe ('|').

Parameters:
        CameraPath: The path the camera should follow
        Text: The text to be displayed on the screen
        Target: Object to target during the cinematic
        Seconds: how long the cinematic should last
        FadeIn: If TRUE then the cinematic will fade in

$$END
*/
void aCinematicSimple(int pathid, const char *Text, int Target, float Seconds, bool FadeIn = false) {
  tGameCinematic info;

  info.flags = 0;
  info.flags = (GCF_LETTERBOX | GCF_USEPATH | GCF_TEXT_WIPEIN | GCF_LAYOUT_BOTTOM);
  info.target_objhandle = Target;
  info.max_time_play = Seconds;
  info.callback = NULL;
  info.text_display.min = 0.40f;
  info.text_display.max = 1.0f;
  info.track_target.min = 0.0f;
  info.track_target.max = 1.0f;
  info.player_disabled.min = 0.0f;
  info.player_disabled.max = 1.0f;
  info.in_camera_view.min = 0.0f;
  info.in_camera_view.max = 1.0f;
  info.quick_exit.min = 1.0f;
  info.quick_exit.max = 1.0f;
  info.end_transition = GCTT_FADEINOUT;
  info.start_transition = (FadeIn) ? GCTT_FADE : GCTT_NONE;
  info.pathid = pathid;

  Cine_Start(&info, Text);
}

/*
$$ACTION
Cinematics
Introduction fly-in using path [h:CameraPath], with text [s:Text] following player position [o:TotallyNotUsedTarget] on
[h:PlayerPath] for [f:Seconds=10.0f]. aCinematicIntro CinematicIntro THE TARGET IS NOT USED, IT'S HERE FOR BACKWARD
COMPATIBILITY This starts a level introduction cinematic. The camera will follow the given path. And the given text will
be shown at the bottom of the screen.  There is a 'quick exit' by keypress, after the first quarter of the cinematic is
done.  To do more than one line of text, seperate each line of text using a pipe ('|').

Parameters:
ONCE AGAIN, THE TARGET IS NOT USED, IT'S HERE FOR BACKWARD COMPATIBILITY
ONCE AGAIN, THE TARGET IS NOT USED, IT'S HERE FOR BACKWARD COMPATIBILITY
        CameraPath: The path the camera should follow
        Text: The text to be displayed on the screen
        Target: NO LONGER USED (it's the player object)
        PlayerPath: The path the target object should follow
        Seconds: how long the cinematic should last
ONCE AGAIN, THE TARGET IS NOT USED, IT'S HERE FOR BACKWARD COMPATIBILITY
ONCE AGAIN, THE TARGET IS NOT USED, IT'S HERE FOR BACKWARD COMPATIBILITY
$$END
*/
void aCinematicIntro(int camera_path, const char *Text, int NoLongerUserTarget, int PlayerPath, float Seconds) {
  tCannedCinematicInfo info;

  info.type = CANNED_LEVEL_INTRO;
  info.camera_pathid = camera_path;
  info.target_pathid = PlayerPath;
  info.text_to_display = Text;
  info.time = Seconds;

  Cine_StartCanned(&info);
}

/*
$$ACTION
Cinematics
Stops the currently playing in-game cinematic
aCinematicStop
CinematicStop
        Stops a currently playing in-game cinematic, restoring everything
$$END
*/
void aCinematicStop(void) { Cine_Stop(); }

class complex_cinematic {
public:
  complex_cinematic() {
    being_made = false;
    memset(&info, 0, sizeof(tGameCinematic));
  }

  tGameCinematic info;
  bool being_made;
};
complex_cinematic ccinematic;

/*
$$ACTION
Cinematics
Complex Cinematic: Start
aComplexCinematicStart
ComplexCinematicStart
        Starts the creation process of a 'complex' in-game cinematic.
$$END
*/
void aComplexCinematicStart(void) {
  ccinematic.being_made = true;
  memset(&ccinematic.info, 0, sizeof(tGameCinematic));

  ccinematic.info.flags = (GCF_LETTERBOX | GCF_USEPATH | GCF_TEXT_WIPEIN | GCF_LAYOUT_BOTTOM | GCF_STOPIFTAGETDEAD);
  ccinematic.info.target_objhandle = OBJECT_HANDLE_NONE;
  ccinematic.info.max_time_play = 10.0f;
  ccinematic.info.callback = NULL;
  ccinematic.info.text_display.min = 0.40f;
  ccinematic.info.text_display.max = 1.0f;
  ccinematic.info.track_target.min = 0.0f;
  ccinematic.info.track_target.max = 1.0f;
  ccinematic.info.player_disabled.min = 0.0f;
  ccinematic.info.player_disabled.max = 1.0f;
  ccinematic.info.in_camera_view.min = 0.0f;
  ccinematic.info.in_camera_view.max = 1.0f;
  ccinematic.info.quick_exit.min = 1.0f;
  ccinematic.info.quick_exit.max = 1.0f;
  ccinematic.info.end_transition = GCTT_FADEINOUT;
  ccinematic.info.start_transition = GCTT_NONE;

  ccinematic.info.pathid = -1;
}

/*
$$ACTION
Cinematics
Complex Cinematic: End, cinematic text: [s:Text] play time: [f:Seconds=10.0]
aComplexCinematicEnd
ComplexCinematicEnd
        Ends the creation process of a 'complex' in-game cinematic and starts it running.
Params:
        Text: The text you want displayed during the cinematic
        Seconds: How long cinematic should play
$$END
*/
void aComplexCinematicEnd(const char *Text, float Seconds) {
  if (!ccinematic.being_made)
    return;

  ccinematic.info.max_time_play = Seconds;

  Cine_Start(&ccinematic.info, Text);
  ccinematic.being_made = false;
}

/*
$$ACTION
Cinematics
Complex Cinematic: Text Display Start [p:Start=0.4] until End [p:End=0.8]
aComplexCinematicText
ComplexCinematicText
        Determines the range (based on a percentage into the cinematic) that the text should display
Params:
        Start: At what percentage of time into the cinematic should text start displaying
        End: At what percentage of time into the cinematic should text stop displaying
$$END
*/
void aComplexCinematicText(float Start, float End) {
  ccinematic.info.text_display.min = Start;
  ccinematic.info.text_display.max = End;
}

/*
$$ACTION
Cinematics
Complex Cinematic: Track Target [o:Target] Start [p:Start=0.0] until End [p:End=1.0]
aComplexCinematicTrack
ComplexCinematicTrack
        Determines the range (based on a percentage into the cinematic) that the target should be tracked
        (NOTE: it should be the entire time...0->100% but you may feel different)
Params:
        Target: Object to target
        Start: At what percentage of time into the cinematic should target be tracked
        End: At what percentage of time into the cinematic should target stop being tracked
$$END
*/
void aComplexCinematicTrack(int Target, float Start, float End) {
  ccinematic.info.target_objhandle = Target;
  ccinematic.info.track_target.min = Start;
  ccinematic.info.track_target.max = End;
}

/*
$$ACTION
Cinematics
Complex Cinematic: Player Disabled Start [p:Start=0.0] until End [p:End=1.0]
aComplexCinematicPlayerDisabled
ComplexCinematicPlayerDisabled
        Determines the range (based on a percentage into the cinematic) that the player's
        controls are disabled.
Params:
        Start: At what percentage of time into the cinematic should controls disable
        End: At what percentage of time into the cinematic should controls be renabled
$$END
*/
void aComplexCinematicPlayerDisabled(float Start, float End) {
  ccinematic.info.player_disabled.min = Start;
  ccinematic.info.player_disabled.max = End;
}

/*
$$ACTION
Cinematics
Complex Cinematic: View From Camera Start [p:Start=0.0] until End [p:End=1.0]
aComplexCinematicCameraView
ComplexCinematicCameraView
        Determines the range (based on a percentage into the cinematic) that the view is from
        the camera
Params:
        Start: At what percentage of time into the cinematic should the view be in the camera
        End: At what percentage of time into the cinematic should the view be back to the player
$$END
*/
void aComplexCinematicCameraView(float Start, float End) {
  ccinematic.info.in_camera_view.min = Start;
  ccinematic.info.in_camera_view.max = End;
}

/*
$$ACTION
Cinematics
Complex Cinematic: Quick Exit Start [p:Start=1.0] until End [p:End=1.0]
aComplexCinematicQuickExit
ComplexCinematicQuickExit
        Determines the range (based on a percentage into the cinematic) that the player can quick
        exit from the cinematic by pressing a key (usually 0%-100% or 100%-100%)
Params:
        Start: At what percentage of time into the cinematic can the player quick exit
        End: At what percentage of time into the cinematic can't the player quick exit
$$END
*/
void aComplexCinematicQuickExit(float Start, float End) {
  ccinematic.info.quick_exit.min = Start;
  ccinematic.info.quick_exit.max = End;
}

/*
$$ENUM CineEndTransition
0:None
1:Wacky
2:Fade In
3:Fade Out/In
$$END
*/

/*
$$ACTION
Cinematics
Complex Cinematic: Set End Transition to [e:CineEndTransition=3]
aComplexCinematicEndTrans
ComplexCinematicEndTrans
        Sets the end transition setting.
$$END
*/
void aComplexCinematicEndTrans(int End) { ccinematic.info.end_transition = End; }

/*
$$ACTION
Cinematics
Complex Cinematic: Set Start Fade in to [b:Enable]
aComplexCinematicStartTrans
ComplexCinematicStartTrans
        Sets whether the cinematic should fade in to start
$$END
*/
void aComplexCinematicStartTrans(bool Enable) { ccinematic.info.start_transition = (Enable) ? GCTT_FADE : GCTT_NONE; }

/*
$$ACTION
Cinematics
Complex Cinematic: Put Camera On Path [h:Path]
aComplexCinematicCameraOnPath
ComplexCinematicCameraOnPath
        Tells the cinematic that the camera should be on the given path
$$END
*/
void aComplexCinematicCameraOnPath(int Path) {
  ccinematic.info.flags |= GCF_USEPATH;
  ccinematic.info.flags &= ~GCF_USEPOINT;
  ccinematic.info.pathid = Path;
}

/*
$$ACTION
Cinematics
Complex Cinematic: Put Camera At Position [v:Position] in room [r:Room]
aComplexCinematicCameraAtPoint
ComplexCinematicCameraAtPoint
        Tells the cinematic that the camera should be on a point
Params:
        Position: The position of the camera in the world
        Room: The room that that position is in
$$END
*/
void aComplexCinematicCameraAtPoint(vector *Position, int Room) {
  ccinematic.info.flags &= ~GCF_USEPATH;
  ccinematic.info.flags |= GCF_USEPOINT;

  ccinematic.info.position = *Position;
  ccinematic.info.room = Room;
}

/*
$$ACTION
Cinematics
Complex Cinematic: Put Camera At Position in clipboard in room [r:Room]
aComplexCinematicCameraAtStoredPt
ComplexCinematicCameraAtStored Point
        Tells the cinematic that the camera should be on a point stored in clipboard
Params:
        Room: The room that that position is in
$$END
*/
void aComplexCinematicCameraAtStoredPt(int Room) {
  if (!PositionClipboard.has_pos)
    return;

  ccinematic.info.flags &= ~GCF_USEPATH;
  ccinematic.info.flags |= GCF_USEPOINT;

  ccinematic.info.position = PositionClipboard.pos;
  ccinematic.info.room = Room;
}

/*
$$ENUM CineScreenMode
0:LetterBox
1:FullScreen
$$END
*/

/*
$$ACTION
Cinematics
Complex Cinematic: Set Screen Mode to [e:CineScreenMode=0]
aComplexCinematicScreenMode
ComplexCinematicScreenMode
        Sets what type of screen mode the cinematic should be in
$$END
*/
void aComplexCinematicScreenMode(int Mode) {
  ccinematic.info.flags &= ~GCF_SCREENFORMAT;
  ccinematic.info.flags |= Mode;
}

/*
$$ENUM CineTextMode
0:None
4:WipeIn
8:FadeInOut
$$END
*/

/*
$$ACTION
Cinematics
Complex Cinematic: Set Text Display Mode to [e:CineTextMode=8]
aComplexCinematicTextMode
ComplexCinematicTextMode
        Sets what type of text effect the cinematic should use
$$END
*/
void aComplexCinematicTextMode(int Mode) {
  ccinematic.info.flags &= ~GCF_TEXT_MASK;
  ccinematic.info.flags |= Mode;
}

/*
$$ENUM CineTextLayoutMode
0:Bottom
16:Top
32:Middle
64:Low
$$END
*/

/*
$$ACTION
Cinematics
Complex Cinematic: Set Text Screen Layout to [e:CineTextLayoutMode=0]
aComplexCinematicTextLayoutMode
ComplexCinematicTextLayoutMode
        Sets what type of text layout the cinematic should use
$$END
*/
void aComplexCinematicTextLayoutMode(int Mode) {
  ccinematic.info.flags &= ~GCF_LAYOUT_MASK;
  ccinematic.info.flags |= Mode;
}

/*
$$FLAG CinematicFlags
256:Stop If Target Is Dead
512:Force Target To End of Path on Quick Exit
$$END
*/

/*
$$ACTION
Cinematics
Complex Cinematic: Flags: [g:CinematicFlags=256:768]
aComplexCinematicFlags
ComplexCinematicFlags
        Sets special flags for the cinematic
$$END
*/
void aComplexCinematicFlags(int flags) {
  ccinematic.info.flags &= ~(GCF_STOPIFTAGETDEAD | GCF_FORCETARGETTOEND);
  ccinematic.info.flags |= flags;
}

/*
$$ACTION
Mission
Enable the given ship [a:Ship], so it can be chosen in single player
aEnableShip
EnableShip
        Enables a ship (given it's name) so it can be chosen in
single player ship selection dialog.

Parameters:
        Ship:	The name of the ship you want to enable
$$END
*/
void aEnableShip(const char *Ship) {
  // this doesn't have to be multiplayer friendly, since it's a single
  // player only thing
  Game_EnableShip(Ship, true);
}

/*
$$ACTION
Mission
Disable the given ship [a:Ship], so it can't be chosen in single player
aDisableShip
DisableShip
        Disables a ship (given it's name) so it can't be chosen in
single player ship selection dialog.

Parameters:
        Ship:	The name of the ship you want to disable

$$END
*/
void aDisableShip(const char *Ship) {
  // this doesn't have to be multiplayer friendly, since it's a single
  // player only thing
  Game_EnableShip(Ship, false);
}

/*
$$ACTION
Triggers
[e:Enable/Disable] trigger [t:Trigger]
aTriggerSetState
Enable/Disable a trigger
  Enables or disables the specified trigger

Parameters:
  Enable/Disable: whether to enable or disable the trigger
  Trigger: which trigger to set
$$END
*/
void aTriggerSetState(int state, int trigger_num) {
  msafe_struct mstruct;

  mstruct.trigger_num = trigger_num;
  mstruct.state = state;
  MSafe_CallFunction(MSAFE_TRIGGER_SET, &mstruct);
}

/*
$$ACTION
Players
Add [o:Object] to [o:PlayerObject]'s inventory, Spewable when player dies [b:Spewable=FALSE]
aAddObjectToInventory
Adds a specific object to a player's inventory

Parameters:
  Object: Object to add
  PlayerObject: Player to get object
  Spewable: Whether the object should be spewed from the inventory when the player dies
$$END
*/
void aAddObjectToInventory(int Object, int PlayerObject, bool Spewable) {
  msafe_struct mstruct;

  mstruct.objhandle = PlayerObject;
  mstruct.ithandle = Object;
  mstruct.message[0] = '\0'; // no name

  if (Spewable)
    mstruct.flags = 0;
  else
    mstruct.flags = INVAF_NOTSPEWABLE;

  MSafe_CallFunction(MSAFE_INVEN_ADD_OBJECT, &mstruct);
}

/*
$$ACTION
Players
Add [o:Object] to [o:PlayerObject]'s inventory with name [s:ItemName], Spewable when player dies [b:Spewable=FALSE]
aAddObjectToInventoryNamed
Adds a specific object to a player's inventory with a custom name

Parameters:
  Object: Object to add
  PlayerObject: Player to get object
  ItemName: The name for this object
  Spewable: Whether the object should be spewed from the inventory when the player dies
$$END
*/
void aAddObjectToInventoryNamed(int Object, int PlayerObject, const char *name, bool Spewable) {
  msafe_struct mstruct;

  mstruct.objhandle = PlayerObject;
  mstruct.ithandle = Object;

  strncpy(mstruct.message, name, sizeof(mstruct.message) - 1);
  mstruct.message[sizeof(mstruct.message) - 1] = '\0';

  if (Spewable)
    mstruct.flags = 0;
  else
    mstruct.flags = INVAF_NOTSPEWABLE;

  MSafe_CallFunction(MSAFE_INVEN_ADD_OBJECT, &mstruct);
}

/*
$$ACTION
Players
Remove [o:Object] from [o:PlayerObject]'s inventory
aRemoveObjectFromInventory
Removes a specific object from a player's inventory

Parameters:
  Object: Object to remove
  PlayerObject: Which Player
$$END
*/
void aRemoveObjectFromInventory(int Object, int PlayerObject) {
  msafe_struct mstruct;

  mstruct.objhandle = PlayerObject;
  mstruct.ithandle = Object;
  MSafe_CallFunction(MSAFE_INVEN_REMOVE_OBJECT, &mstruct);
}

/*
$$ACTION
Objects
Store [o:Object] position in position clipboard
aStoreObjectInPositionClipboard
Stores the position of an object in the internal 'clipboard'

Parameters:
        Object: object whose position you want to store
$$END
*/
void aStoreObjectInPositionClipboard(int Object) {
  msafe_struct mstruct;
  mstruct.objhandle = Object;
  MSafe_GetValue(MSAFE_OBJECT_WORLD_POSITION, &mstruct);

  PositionClipboard.pos = mstruct.pos;
  PositionClipboard.orient = mstruct.orient;
  PositionClipboard.room = mstruct.roomnum;
  PositionClipboard.has_pos = true;
}

/*
$$ACTION
Objects
Move [o:Object] to position in position clipboard
aMoveObjectToPositionClipboard
Moves an object to the position stored in the internal 'clipboard'

Parameters:
        Object: object whose position you want to change
$$END
*/
void aMoveObjectToPositionClipboard(int Object) {
  if (!PositionClipboard.has_pos)
    return;

  msafe_struct mstruct;
  mstruct.objhandle = Object;
  mstruct.pos = PositionClipboard.pos;
  mstruct.orient = PositionClipboard.orient;
  mstruct.roomnum = PositionClipboard.room;

  MSafe_CallFunction(MSAFE_OBJECT_WORLD_POSITION, &mstruct);
}

/*
$$ACTION
Objects
Cloak [o:Object] for [f:Seconds] seconds
aCloakObject
Cloaks an object for the time specified.

Parameters:
        Object: object to cloak
        Seconds: how long should it be cloaked
$$END
*/
void aCloakObject(int Object, float Seconds) {
  msafe_struct mstruct;
  mstruct.objhandle = Object;
  mstruct.state = 1;
  mstruct.lifetime = Seconds;
  MSafe_CallFunction(MSAFE_OBJECT_CLOAK, &mstruct);
}

/*
$$ACTION
Objects
UnCloak [o:Object]
aUnCloakObject
UnCloaks an object

Parameters:
        Object: object to uncloak
$$END
*/
void aUnCloakObject(int Object) {
  msafe_struct mstruct;
  mstruct.objhandle = Object;
  mstruct.state = 0;
  MSafe_CallFunction(MSAFE_OBJECT_CLOAK, &mstruct);
}

/*
$$ACTION
Players
Cloak all players for [f:Seconds] seconds
aCloakAllPlayers
Cloaks all the Players in the game

Parameters:
        Seconds: how long should the players be cloaked
$$END
*/
void aCloakAllPlayers(float Seconds) {
  msafe_struct mstruct;
  mstruct.state = 1;
  mstruct.lifetime = Seconds;
  MSafe_CallFunction(MSAFE_OBJECT_CLOAKALLPLAYERS, &mstruct);
}

/*
$$ACTION
Players
UnCloak all players
aUnCloakAllPlayers
UnCloaks all the Players in the game

$$END
*/
void aUnCloakAllPlayers(void) {
  msafe_struct mstruct;
  mstruct.state = 0;
  MSafe_CallFunction(MSAFE_OBJECT_CLOAKALLPLAYERS, &mstruct);
}

/*
$$ACTION
Objects
Set [o:Object] on Fire for [f:Seconds] doing [f:Damage] damage per second
aSetObjectOnFire
Sets an object on fire

Parameters:
        Object = object to be set on fire
        Seconds = how long it should be on fire
        Damage = how much damage per second the fire should do
$$END
*/
void aSetObjectOnFire(int obj, float seconds, float dps) {
  msafe_struct mstruct;
  mstruct.objhandle = obj;
  mstruct.longevity = seconds;
  mstruct.interval = dps;
  mstruct.ithandle = OBJECT_HANDLE_NONE;
  MSafe_CallFunction(MSAFE_OBJECT_SETONFIRE, &mstruct);
}

/*
$$ACTION
Objects
Fire weapon [a:WeaponName] from gun number [i:GunNum] of object [o:Object]
aObjFireWeapon
Fire weapon
  Fires the specified weapon from the given gun number of an object

Parameters:
  WeaponName - the weapon to fire
  GunNum - the gun number to fire from, or -1 to fire from the object's center
  Object - the object to fire the flare
$$END
*/
void aObjFireWeapon(const char *weapon_name, int gun_num, int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.index = Wpn_FindID(weapon_name);
  if (mstruct.index == -1)
    return;
  mstruct.gunpoint = gun_num;

  MSafe_CallFunction(MSAFE_OBJECT_FIRE_WEAPON, &mstruct);
}

/*
$$ACTION
Objects
Fire flare from gun number [i:GunNum] of object [o:Object]
aObjFireFlare
Fire flare
  Fires a flare from the given gun number of an object

Parameters:
  GunNum - the gun number to fire from, or -1 to fire from the object's center
  Object - the object to fire the flare
$$END
*/
#define aObjFireFlare(gun_num, objhandle) aObjFireWeapon("Yellow flare", gun_num, objhandle)

////////////////////////////////////////////////////////////////////////////////////////////
// The following code is to handle a 'kill all object except these' Dallas command sequence.
// these are beneficial for areas like Boss rooms with no escape or something, were it is
// just nice to kill all objects in the level, except what is needed, for framerate
// It will only kill robots in the level, except those designated to spare.

struct tKillRobotListNode {
  tKillObjectItem item;
  tKillRobotListNode *next;
};

class CKillRobotList {
public:
  CKillRobotList() { list = NULL; };
  ~CKillRobotList() { clear(); }

  void clear(void);
  void add(tKillObjectItem *data);

  tKillRobotListNode *list;
};
CKillRobotList KillRobotList;

void CKillRobotList::clear(void) {
  tKillRobotListNode *next, *curr = list;

  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  list = NULL;
}

void CKillRobotList::add(tKillObjectItem *data) {
  tKillRobotListNode *curr = list;

  if (!curr) {
    list = curr = (tKillRobotListNode *)malloc(sizeof(tKillRobotListNode));
  } else {
    while (curr->next) {
      curr = curr->next;
    }

    curr->next = (tKillRobotListNode *)malloc(sizeof(tKillRobotListNode));
    curr = curr->next;
  }

  if (!curr)
    return;

  curr->next = NULL;
  memcpy(&curr->item, data, sizeof(tKillObjectItem));
}

/*
$$ACTION
Objects
Destroy All Robots: Start
aDestroyAllRobotsInit
Initializes the "Destroy All Robots" DALLAS command sequence.  Call this BEFORE doing
        any other of the "Destroy All Robots" commands.

NOTE: It is VERY important that the entire command sequence happens all in the same
        action, and in proper order.
$$END
*/
void aDestroyAllRobotsInit(void) { KillRobotList.clear(); }

/*
$$ACTION
Objects
Destroy All Robots: Spare robots of this type [a:RobotID]
aDestroyAllRobotsSpareType
Spares any robot that has if of the species given (i.e. Tubbs)

Parameters:
  RobotID - the name of the group of robots to Spare
$$END
*/
void aDestroyAllRobotsSpareType(const char *name) {
  int id = Obj_FindID(name);

  if (id != -1) {
    tKillObjectItem item;
    item.info_type = KOI_ID;
    item.id = id;

    KillRobotList.add(&item);
  }
}

/*
$$ACTION
Objects
Destroy All Robots: Spare robot ([o:RobotHandle])
aDestroyAllRobotsSpareHandle
Spares the robot with the given handle

Parameters:
  RobotHandle - the handle of the robot to Spare
$$END
*/
void aDestroyAllRobotsSpareHandle(int handle) {
  if (handle != OBJECT_HANDLE_NONE) {
    tKillObjectItem item;
    item.info_type = KOI_HANDLE;
    item.objhandle = handle;

    KillRobotList.add(&item);
  }
}

/*
$$ACTION
Objects
Destroy All Robots: End
aDestroyAllRobotsEnd
Destroys the robots (except those spared) in the level

$$END
*/
void aDestroyAllRobotsEnd(void) {
  tKillRobotListNode *curr = KillRobotList.list;
  int count = 0;

  if (!curr)
    return;

  while (curr) {
    count++;
    curr = curr->next;
  }

  curr = KillRobotList.list;
  tKillObjectItem *kolist = NULL;

  kolist = (tKillObjectItem *)malloc(sizeof(tKillObjectItem) * count);
  if (!kolist)
    return;

  count = 0;
  while (curr) {
    memcpy(&kolist[count], &curr->item, sizeof(tKillObjectItem));
    count++;
    curr = curr->next;
  }

  msafe_struct ms;
  ms.count = count;
  ms.list = kolist;
  MSafe_CallFunction(MSAFE_OBJECT_DESTROY_ROBOTS_EXCEPT, &ms);

  free(kolist);

  KillRobotList.clear();
}

/*
$$ACTION
Objects
[e:Enable/Disable] virus infections signs for [o:Object]
aEnableVirusInfection
Enables or disables the graphical effects related to an object being infected
with a virus

$$END
*/
void aEnableVirusInfection(int enable, int handle) {
  char cenable;
  cenable = (enable) ? 1 : 0;

  Obj_Value(handle, VF_SET, OBJV_C_VIRUS_INFECTED, &cenable);
}

/*
$$ACTION
Objects
[e:Enable/Disable] negative lighting for [o:Object]
aEnableNegativeLighting
Enables or disables negative dynamic lighting (ala black hole) for the object

$$END
*/
void aEnableNegativeLighting(int enable, int handle) {
  char cenable;
  cenable = (enable) ? 1 : 0;

  Obj_Value(handle, VF_SET, OBJV_C_NEGATIVE_LIGHT, &cenable);
}

/*
$$ACTION
Players
Strip all weapons and energy from player [o:Object]
aStripWeaponsEnergy
Removes all weapons (but lasers) and ammo, and reduces energy to 0.

$$END
*/
void aStripWeaponsEnergy(int Object) {
  int val = 0;
  Player_Value(Object, VF_SET, PLYV_I_STRIP_WEAPONS, &val);
}

/*
$$ACTION
Players
Strip all weapons and energy from all players
aStripWeaponsEnergyFromAll
Removes all weapons (but lasers) and ammo, and reduces energy to 0.

$$END
*/
void aStripWeaponsEnergyFromAll(void) {
  int val = -1;
  Player_Value(OBJECT_HANDLE_NONE, VF_SET, PLYV_I_STRIP_WEAPONS, &val);
}

/*
$$ACTION
Rooms
Remove all powerups from room [r:Room]
aRemovePowerupsInRoom
Removes all the powerups in the room given

$$END
*/
void aRemovePowerupsInRoom(int Room) {
  msafe_struct mstruct;
  mstruct.roomnum = Room;
  MSafe_CallFunction(MSAFE_ROOM_REMOVE_ALL_POWERUPS, &mstruct);
}

/*
$$QUERY
Objects
b:Is [o:Object] virus infected
qVirusInfected
Returns true if the object is showing signs of being infected by a virus

$$END
*/
bool qVirusInfected(int handle) {
  char cenable;
  Obj_Value(handle, VF_GET, OBJV_C_VIRUS_INFECTED, &cenable);

  return (cenable) ? true : false;
}

/*
$$QUERY
Objects
b:Is [o:Object] giving off negative dynamic light (ala black hole)
qNegativeLight
Returns true if the object is giving off negative light, like a black hole (it is
removing light from the world)

$$END
*/
bool qNegativeLight(int handle) {
  char cenable;
  Obj_Value(handle, VF_GET, OBJV_C_NEGATIVE_LIGHT, &cenable);

  return (cenable) ? true : false;
}

/*
$$QUERY
Mission
i:Get difficulty level
qGetDifficulty
Returns the difficulty level (0 = trainee,4 = insane)

$$END
*/
int qGetDifficulty(void) { return Game_GetDiffLevel(); }

/*
Requested by Luke 1/15/99

PickupPowerup [OBJECT]
 -deletes powerup and plays powerup sound
AddToInventory [OBJECT]
 -add powerup to the player's inventory
Turn Fog in Room [ROOM] to [TRUE/FALSE]
 -turns on/off the fog flag
Fade Fog in Room [ROOM] to Distance [DIST] and Color [RGB] over Time
[TIME]
 -needs new code, but should be easy (like SetRoomFog over time)
 -ask Jason for new code if need be
Fade Wind in Room [ROOM] to Direction [XYZ] over Time [TIME]
 -another new code one, but also easy (like SetRoomWind over time)
 -Jason also can help on this one
AI: Fire when close [ROBOT], Distance [DIST]
 -Robot fires constantly when a player is within DIST meters

*/

/*

MatcenSetStatus
ChangeFaceTexture

PlaySoundLoc3d
TouchSound

*/

/*
$$QUERY
Objects
f:[o:Object] cloak time left
qObjectCloakTime

Parameters:
        Object: object to get cloak time left (0 if it's not cloaked)
$$END
*/
float qObjectCloakTime(int Object) {
  msafe_struct mstruct;
  mstruct.objhandle = Object;
  mstruct.state = 0;
  mstruct.lifetime = 0;
  MSafe_GetValue(MSAFE_OBJECT_CLOAK, &mstruct);

  return (mstruct.state) ? mstruct.lifetime : 0;
}

/*
$$QUERY
Objects
f:Get [o:Object] position on [e:Axis=0] axis
qObjectPosition

Parameters:
        Object: object to get cloak time left (0 if it's not cloaked)
$$END
*/
float qObjectPosition(int handle, int axis) {
  float value = 0.0f;
  int type;

  Obj_Value(handle, VF_GET, OBJV_I_TYPE, &type);
  if (type != OBJ_NONE) {
    vector pos;
    Obj_Value(handle, VF_GET, OBJV_V_POS, &pos);

    switch (axis) {
    case 0:
      value = pos.x;
      break;
    case 1:
      value = pos.y;
      break;
    case 2:
      value = pos.z;
      break;
    }
  }

  return value;
}

/*
$$QUERY
AI
b:[o:Object] close to target
qAICloseToTarget

Parameters:
        Object: Is this object near its target
$$END
*/
bool qAICloseToTarget(int me) {
  int target = OBJECT_HANDLE_NONE;
  bool f_close = false;
  char ctype;
  int status;
  float awareness;

  Obj_Value(me, VF_GET, OBJV_C_CONTROL_TYPE, &ctype);
  if (ctype == CT_AI) {
    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target);
    if (target != OBJECT_HANDLE_NONE) {
      AI_Value(me, VF_GET, AIV_F_AWARENESS, &awareness);

      if (awareness >= AWARE_BARELY) {
        AI_Value(me, VF_GET, AIV_I_STATUS_REG, &status);
        f_close = ((status & AISR_CIRCLE_DIST) != 0);
      }
    }
  }

  return f_close;
}

/*
$$QUERY
AI
b:Is [o:Object] aware
qAIIsObjectAware

Parameters:
        Object: Is this object near its target
$$END
*/
bool qAIIsObjectAware(int me) {
  bool f_aware = false;
  char ctype;

  Obj_Value(me, VF_GET, OBJV_C_CONTROL_TYPE, &ctype);
  if (ctype == CT_AI) {
    float awareness;
    AI_Value(me, VF_GET, AIV_F_AWARENESS, &awareness);

    if (awareness >= AWARE_BARELY) {
      f_aware = true;
    }
  }

  return f_aware;
}

/*
$$QUERY
AI
o:[o:Object] get target
qAIGetTarget

Parameters:
        Object: object we want the the target of
$$END
*/
int qAIGetTarget(int me) {
  int target = OBJECT_HANDLE_NONE;
  char ctype;

  Obj_Value(me, VF_GET, OBJV_C_CONTROL_TYPE, &ctype);
  if (ctype == CT_AI) {
    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target);
  }

  return target;
}

/*
$$QUERY
Players
b:[o:Player] has [o:Object] in their inventory
qHasObjectInInventory

Parameters:
        Player: Player to check
        Object: Which object to check for
$$END
*/
bool qHasObjectInInventory(int PlayerObject, int Object) {
  msafe_struct mstruct;

  mstruct.objhandle = PlayerObject;
  mstruct.ithandle = Object;
  MSafe_GetValue(MSAFE_INVEN_CHECK_OBJECT, &mstruct);

  return mstruct.state;
}

/*
$$ACTION
Objects
Save object handle for [o:Object] in slot [e:SavedObjectSlot]
aObjSaveHandle
Save object handle
  Saves an object handle for later user

Parameters:
  o:Object: the object whose handle is saved
  SavedObjectSlot: the slot in which to save the handle
$$END
*/
void aObjSaveHandle(int objhandle, int slot) {
  if ((slot >= 0) && (slot < MAX_SAVED_OBJECT_HANDLES))
    Saved_object_handles[slot] = objhandle;
}

/*
$$ACTION
Level Goals
Set goal [l:LevelGoal] as [e:Completed]
aGoalCompleted
Set goal completion state
  Tells the goal system that the specified goal has been completed or not

Parameters:
  LevelGoal: the goal to set
  Completed: whether or not the goal has been completed
$$END
*/
void aGoalCompleted(int goal_index, int completed) {
  int flags = LGF_COMPLETED;

  LGoal_Value(completed ? VF_SET_FLAGS : VF_CLEAR_FLAGS, LGSV_I_STATUS, &flags, goal_index);
}

/*
$$ACTION
Level Goals
Set goal [l:LevelGoal] item number [i:ItemIndex] as [e:Completed]
aGoalItemCompleted
Set goal item completion state
  Tells the goal system that the specified goal item has been completed or not

Parameters:
  LevelGoal: the goal
  ItemIndex: the index of the item in question
  Completed: whether or not the goal item has been completed
$$END
*/
void aGoalItemCompleted(int goal_index, int item_index, int completed) {
  bool f_set = (completed != 0);
  LGoal_Value(VF_SET, LGSSV_B_ITEM_DONE, &f_set, goal_index, item_index - 1);
}

/*
$$ACTION
Level Goals
Set goal [l:LevelGoal] as [e:Failed]
aGoalFailed
Set goal fail state
  Tells the goal system that the specified goal has been failed or not

Parameters:
  LevelGoal: the goal to set
  Failed: whether or not the goal has been failed
$$END
*/
void aGoalFailed(int goal_index, int failed) {
  int flags = LGF_FAILED;

  LGoal_Value(failed ? VF_SET_FLAGS : VF_CLEAR_FLAGS, LGSV_I_STATUS, &flags, goal_index);
}

/*
$$ACTION
Level Goals
[e:Enable/Disable] goal [l:LevelGoal]
aGoalEnableDisable
Enable/disable goal
  Enable or disable the specified goal

Parameters:
  Enable/Disable: whether the goal should be enabled or disabled
  LevelGoal: the goal to set
$$END
*/
void aGoalEnableDisable(int enabled, int goal_index) {
  int flags = LGF_ENABLED;

  LGoal_Value(enabled ? VF_SET_FLAGS : VF_CLEAR_FLAGS, LGSV_I_STATUS, &flags, goal_index);
}

/*
$$ACTION
Level Goals
Set goal [l:LevelGoal] priority = [i:Priority]
aGoalSetPriority
Set goal priority
  Sets the priority of the specified goal

Parameters:
  LevelGoal: the goal to set
  Priority: the priority to set
$$END
*/
void aGoalSetPriority(int goal_index, int priority) { LGoal_Value(VF_SET, LGSV_I_PRIORITY, &priority, goal_index); }

/*
$$ACTION
Level Goals
Set goal [l:LevelGoal] completion message = [s:Message]
aGoalSetCompletionMessage
Set goal completion message
  Sets the completion message for the specified goal

Parameters:
  LevelGoal: the goal to set
  Message: the message for the goal
$$END
*/
void aGoalSetCompletionMessage(int goal_index, const char *message) {
  LGoal_Value(VF_SET, LGSV_PC_COMPLETION_MESSAGE, (void *) message, goal_index);
}

/*
$$ACTION
Level Goals
GuideBot [e:Can/Cannot] lead the player to goal [l:LevelGoal]
aGoalSetGBKnowledge
GuideBot can/cannot lead the player to goal
  Tells the goal system whether the GuideBot is allowed to lead the player to the specified goal

Parameters:
  Can/Cannot: whether or not the GuideBot can lead the player to the goal
  LevelGoal: the goal to set
$$END
*/
void aGoalSetGBKnowledge(int enabled, int goal_index) {
  int flags = LGF_GB_DOESNT_KNOW_LOC;

  LGoal_Value(enabled ? VF_CLEAR_FLAGS : VF_SET_FLAGS, LGSV_I_STATUS, &flags, goal_index);
}

//
//  D3 queries
//

/* NOTE: The following query is handled internally by DALLAS
$$QUERY
Scripts
b:Script [x:ScriptID] has executed
qScriptExecuted_DALLAS
Has this script been executed?
  Determines if the specified script has executed at least once

Parameters:
  ScriptID: The script to check
$$END
*/

/* NOTE: The following query is handled internally by DALLAS
$$QUERY
Scripts
i:Times Script [x:ScriptID] has been executed
qTimesScriptExecuted_DALLAS
How many times has this script been executed?
  Returns the number of times the specified script has executed

Parameters:
  ScriptID: The script to check
$$END
*/

/*
$$QUERY
Objects
b:[o:Object] exists
qObjExists
Does this object exist?
  Determines if the specified object exists in the world

Parameters:
  Object: The object to check
$$END
*/
bool qObjExists(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  return (mstruct.type != -1);
}

/*
$$QUERY
Objects
b:[o:Object=IT] is a player
qObjIsPlayer
Is this object a player?
  Determines if the specified object is a player

Parameters:
  Object: The object to check
$$END
*/
bool qObjIsPlayer(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  return (mstruct.type == OBJ_PLAYER);
}

/*
$$QUERY
Objects
b:[o:Object=IT] is a player weapon
qObjIsPlayerWeapon
Is this object a player weapon?
  Determines if the specified object is a player weapon

Parameters:
  Object: The object to check
$$END
*/
bool qObjIsPlayerWeapon(int handle) {
  msafe_struct mstruct;

  mstruct.objhandle = handle;

  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  if (mstruct.type == OBJ_WEAPON) {
    MSafe_GetValue(MSAFE_OBJECT_PARENT, &mstruct);
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

    if (mstruct.type == OBJ_PLAYER)
      return 1;
  }

  return 0;
}

/*
$$QUERY
Objects
b:[o:Object=IT] is a player or player weapon
qObjIsPlayerOrPlayerWeapon
Is this object either a player or a player weapon?
  Determines if the specified object is either a player or a player weapon

Parameters:
  Object: The object to check
$$END
*/
bool qObjIsPlayerOrPlayerWeapon(int handle) {
  msafe_struct mstruct;

  mstruct.objhandle = handle;

  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  if (mstruct.type == OBJ_PLAYER)
    return 1;

  if (mstruct.type == OBJ_WEAPON) {
    MSafe_GetValue(MSAFE_OBJECT_PARENT, &mstruct);
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

    if (mstruct.type == OBJ_PLAYER)
      return 1;
  }

  return 0;
}

/*
$$QUERY
Objects
b:[o:Object=IT] is an energy weapon
qObjIsEnergyWeapon
Is this object an energy weapon?
  Determines if the specified object is an energy weapon

Parameters:
  Object: The object to check
$$END
*/
bool qObjIsEnergyWeapon(int handle) {
  msafe_struct mstruct;

  mstruct.objhandle = handle;
  MSafe_GetValue(MSAFE_OBJECT_ENERGY_WEAPON, &mstruct);

  return mstruct.state;
}

/*
$$QUERY
Objects
b:[o:Object=IT] is a [e:ObjectType]
qObjIsType
Is this object the specified type?
  Determines if the specified object is the specified type

Parameters:
  Object: The object to check
  ObjectType: The type to check
$$END
*/
bool qObjIsType(int objhandle, int type) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  return (mstruct.type == type);
}

/*
$$QUERY
Objects
b:[o:TargetObject] is within the [i:Cone=90] degree view cone of [o:Object]
qObjCanSeeObj
Can object see the target object
  Determines if the specified object can see the other object

Parameters:
  Object: The object doing the looking
  TargetObject: The target object
  Cone: Angle between 0-360 which makes the viewcone that determines if the object can see the other object
$$END
*/
bool qObjCanSeeObj(int handletarget, int cone, int handlesrc) {
  vector vsource, vtarget;

  msafe_struct mstruct;

  // Get half of the angle that the user specified because they specified a cone, and we want an angle
  double cangle = (double)((double)cone / (double)2);

  double testangle = cos(cangle * PI / 180);

  mstruct.objhandle = handletarget;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  vtarget = mstruct.pos;

  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  vsource = mstruct.pos;

  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_ORIENT, &mstruct);

  vector subvec = vtarget - vsource;
  vm_VectorNormalizeFast(&subvec);
  float dotp = vm_DotProduct(&subvec, &mstruct.orient.fvec);

  if (dotp > testangle) {
    return true;
  }
  return false;
}

/*
$$QUERY
Objects
b:[o:TargetObject] is within the [i:Cone=90] degree view cone of [o:Object] using flags [g:FVIHitFlags=1048585:16269119]
qObjCanSeeObjAdvanced
Can object see the target object
  Determines if the specified object can see the other object using the given flags

Parameters:
  Object: The object doing the looking
  TargetObject: The target object
  Cone: Angle between 0-360 which makes the viewcone that determines if the object can see the other object
  FVIHitFlags: Flags used to determine visibility
$$END
*/
bool qObjCanSeeObjAdvanced(int handletarget, int cone, int handlesrc, int fvi_flags) {
  vector vsource, vtarget;
  int sourceroom;

  msafe_struct mstruct;

  // Get half of the angle that the user specified because they specified a cone, and we want an angle
  double cangle = (double)((double)cone / (double)2);

  double testangle = cos(cangle * PI / 180);

  mstruct.objhandle = handletarget;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  vtarget = mstruct.pos;

  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  vsource = mstruct.pos;

  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);
  sourceroom = mstruct.roomnum;

  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_ORIENT, &mstruct);

  vector subvec = vtarget - vsource;
  vm_VectorNormalizeFast(&subvec);
  float dotp = vm_DotProduct(&subvec, &mstruct.orient.fvec);

  if (dotp > testangle) {
    // see if we can cast a ray to the object
    ray_info ray;
    fvi_flags |= FQ_CHECK_OBJS;
    int fate = FVI_RayCast(handlesrc, &vsource, &vtarget, sourceroom, 0.0f, fvi_flags, &ray);
    if (fate == HIT_NONE)
      return true;

    if (fate == HIT_OBJECT) {
      if (ray.hit_object == handletarget) {
        return true;
      }
    }
  }
  return false;
}

/*
$$QUERY
Objects
o:[o:Object=IT] parent
qObjParent
Object parent
  Gets the parent of the specified object

Parameters:
  Object: The object whose parent is returned
$$END
*/
int qObjParent(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_GetValue(MSAFE_OBJECT_PARENT, &mstruct);

  return mstruct.objhandle;
}

/*
$$QUERY
Objects
o:Get attached child of [o:Object] at attach point [i:AttachPoint]
qGetAtachedChild
Attached child
  Gets the attached child of the specified object

Parameters:
  Object: The object who we want to determine its attached child
  AttachPoint: The attach point the child is attached to
$$END
*/
int qGetAtachedChild(int objhandle, int attachpoint) { return Obj_GetAttachChildHandle(objhandle, attachpoint); }

/*
$$QUERY
Objects
r:[o:Object=IT] room
qObjRoom
Object Room
  Returns the room the specified object is in

Parameters:
  Object: The object whose room you want to know
$$END
*/
int qObjRoom(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);

  return mstruct.roomnum;
}

// These should be in object_external.h
#define ROOMNUM_CELLNUM_FLAG 0x80000000
#define ROOMNUM_OUTSIDE(roomnum) (((roomnum) & ROOMNUM_CELLNUM_FLAG) != 0)

/*
$$QUERY
Objects
b:[o:Object=IT] is on the terrain
qObjOnTerrain
Object on terrain?
  Determines if the specified object is on the terrain

Parameters:
  Object: The object to check
$$END
*/
bool qObjOnTerrain(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);

  return ROOMNUM_OUTSIDE(mstruct.roomnum);
}

/*
$$QUERY
Objects
e(ObjectType):[o:Object=IT] type
qObjType
Object type
  Returns the specified object's type

Parameters:
  Object: The object whose type you want to know
$$END
*/
int qObjType(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);

  return mstruct.type;
}

/*
$$QUERY
User Vars
f:User Variable [e:UserVar]
qUserVarValue
User Variable
  Returns the value of the specified user variable

Parameters:
  UserVar: The variable whose value to return
$$END
*/
float qUserVarValue(int varnum) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    return User_vars[varnum];
  else
    return 0.0;
}

/*
$$QUERY
User Vars
i:User Variable [e:UserVar] (Integer)
qUserVarValueInt
User Variable (Integer)
  Returns the value of the specified user variable rounded to the nearest integer

Parameters:
  UserVar: The variable whose value to return
$$END
*/
int qUserVarValueInt(int varnum) {
  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    return (User_vars[varnum] + 0.5);
  else
    return 0.0;
}

/*
$$QUERY
User Vars
b:User Flag [e:UserFlag]
qUserFlag
User flag
  Returns the state of the specified user flag

Parameters:
  UserFlag: The flag whose state to return
$$END
*/
bool qUserFlag(int flagnum) {
  if ((flagnum >= 0) && (flagnum < 32))
    return ((User_flags & (1 << flagnum)) != 0);
  else
    return 0;
}

/*
$$QUERY
Objects
f:Object [o:Object] shields
qObjShields
Get an object's shields
  Gets an object's shields

Parameters:
  Object: the object whose shields are being queried
$$END
*/
float qObjShields(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &mstruct);

  return mstruct.shields;
}

/*
$$QUERY
Objects
f:Object [o:Object] energy
qObjEnergy
Get an object's energy
  Gets an object's energy

Parameters:
  Object: the object whose energy are being queried
$$END
*/
float qObjEnergy(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_ENERGY, &mstruct);

  return mstruct.energy;
}

/*
$$QUERY
Objects
f:Object [o:Object] original shields
qObjShieldsOriginal
Object's original shields
  Gets an object's original (full-strength) shields

Parameters:
  Object: the object whose shields are being queried
$$END
*/
float qObjShieldsOriginal(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;

  MSafe_GetValue(MSAFE_OBJECT_SHIELDS_ORIGINAL, &mstruct);

  return mstruct.shields;
}

/*
$$QUERY
Doors
b:Door [d:Door] is locked
qDoorLocked
Door locked
Determines if a door is locked

Parameters:
  Door: the door to check
$$END
*/
bool qDoorLocked(int objref) {
  msafe_struct mstruct;

  mstruct.objhandle = objref;
  MSafe_GetValue(MSAFE_DOOR_LOCK_STATE, &mstruct);

  return mstruct.state;
}

/*
$$QUERY
Doors
b:Door [d:Door] is openable by [o:Object=IT]
qDoorOpenable
Door openable
Determines if a door is openable by the specified object

Parameters:
  Door: the door to check
  Object: the object to check
$$END
*/
bool qDoorOpenable(int door_handle, int opener_handle) {
  msafe_struct mstruct;

  mstruct.objhandle = door_handle;
  mstruct.ithandle = opener_handle;
  MSafe_GetValue(MSAFE_DOOR_OPENABLE, &mstruct);

  return mstruct.state;
}

/*
$$QUERY
Doors
p:Door [d:Door] position
qDoorGetPos
Get door position
  Gets the position of the specified door

Parameters:
  Door: the object of the door
$$END
*/
float qDoorGetPos(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_GetValue(MSAFE_DOOR_POSITION, &mstruct);

  return mstruct.scalar;
}

/*
$$QUERY
Mission
b:Mission flag [i:FlagNum] is set
aMissionGetFlag
Get a mission flag
  Gets the specified mission flag

Parameters:
  FlagNum: the flag to get
$$END
*/
bool aMissionGetFlag(int flagnum) { return Msn_FlagGet(flagnum); }

/*
$$QUERY
Mission
b:Level objective flag [i:FlagNum] is set
aMissionGetLevelFlag
Get a level objective flag
  Gets the specified level objective flag

Parameters:
  FlagNum: the flag to get
$$END
*/
bool aMissionGetLevelFlag(int flagnum) {
  //!!Add code here

  return 0;
}

/*
$$QUERY
Objects
f:Object [o:Object] animation frame
qObjAnimFrame
Object animation frame
  Get an object's animation frame

Parameters:
  Object: the object whose animation frame is being queried
$$END
*/
float qObjAnimFrame(int objref) {
  float anim_frame;

  Obj_Value(objref, VF_GET, OBJV_F_ANIM_FRAME, &anim_frame);

  return anim_frame;
}

/*
$$QUERY
Rooms
b:Room [r:Room] fog is on
qRoomFogOn
Room fog is on
  Checks if the fog is on in a room

Parameters:
  Room: the room to check
$$END
*/
bool qRoomFogOn(int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;

  MSafe_GetValue(MSAFE_ROOM_FOG_STATE, &mstruct);

  return mstruct.state;
}

/*
$$ACTION
Players
[e:Enable/Disable] player controls [g:PlayerControl] for [o:PlayerObject]
aTogglePlayerObjControl
TogglePlayerControl
  Sets a players control either disabled or enabled

Parameters:
  Object: The player object
  PlayerObject: The player this affects
  Enable/Disable: Whether to Enable or Disable the specified controls
$$END
*/
void aTogglePlayerObjControl(int enable, int controlmask, int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;
  mstruct.control_mask = controlmask;
  mstruct.control_val = enable;

  MSafe_CallFunction(MSAFE_OBJECT_PLAYER_CMASK, &mstruct);
}

/*
$$ACTION
Players
[e:Enable/Disable] all player control for [o:PlayerObject]
aTogglePlayerObjAllControls
ToggleAllPlayerControls
  Sets a players control either disabled or enabled

Parameters:
  Enable/Disable: Enable/Disable the specified control
  PlayerObject: The player this affects
$$END
*/
void aTogglePlayerObjAllControls(int enable, int objhandle) {
  msafe_struct mstruct;
  int controlbit = 0xffffffff;
  mstruct.objhandle = objhandle;
  mstruct.control_mask = controlbit;
  mstruct.control_val = enable ? 1 : 0;

  MSafe_CallFunction(MSAFE_OBJECT_PLAYER_CMASK, &mstruct);
}

/*
$$ACTION
Players
Give player [o:PlayerObject] key [o:KeyObject], key number [i:KeyNum=1:1|8], name = [s:KeyName], show HUD message =
[e:Yes/No] aObjectPlayerGiveKey Give player key Gives a player the specified key, and deletes the key object if not
multiplayer

Parameters:
  PlayerObject: The player who gets the key
  KeyObject: the object that is the key
  KeyNum: which key this is (1-8)
  KeyName: the name of this key (shown in inventory & on HUD)
  Yes/No: should the name of the key be shown on the HUD?
$$END
*/
void aObjectPlayerGiveKey(int player_handle, int key_handle, int key_num, const char *key_name, int show_on_hud) {
  msafe_struct mstruct;

  mstruct.objhandle = key_handle;
  mstruct.ithandle = player_handle;
  mstruct.index = key_num;

  strncpy(mstruct.message, key_name, sizeof(mstruct.message) - 1);
  mstruct.message[sizeof(mstruct.message) - 1] = 0;

  MSafe_CallFunction(MSAFE_OBJECT_PLAYER_KEY, &mstruct);

  if (show_on_hud)
    aShowHUDMessage(key_name);
}

/*
$$ACTION
Players
Give player [o:PlayerObject] invisible key number [i:KeyNum=1:1|8]
aObjectPlayerGiveInvisibleKey
Give player key
  Gives a player the specified key, which doesn't show up on the HUD or in the inventory

Parameters:
  PlayerObject: The player who gets the key
  KeyNum: which key this is (1-8)
$$END
*/
void aObjectPlayerGiveInvisibleKey(int player_handle, int key_num) {
  msafe_struct mstruct;

  mstruct.objhandle = OBJECT_HANDLE_NONE;
  mstruct.ithandle = player_handle;
  mstruct.index = key_num;
  mstruct.message[0] = 0; // don't think this is used, but just in case

  MSafe_CallFunction(MSAFE_OBJECT_PLAYER_KEY, &mstruct);
}

/*
$$QUERY
Objects
f:Object [o:Object] lighting distance
qObjGetLightingDist
Get object lighting distance
  Gets the lighting distance for an object

Parameters:
  Object: the object to get
$$END
*/
float qObjGetLightingDist(int objhandle) {
  msafe_struct mstruct;

  mstruct.objhandle = objhandle;

  MSafe_GetValue(MSAFE_OBJECT_LIGHT_DIST, &mstruct);

  return mstruct.light_distance;
}

/*
$$QUERY
Math
f:[f:Float1] plus [f:Float2]
qMathAddFloat
Add floats
  Adds two floating-point numbers and returns the result

Parameters:
  Float1, Float2: the numbers to add
$$END
*/
float qMathAddFloat(float f0, float f1) { return f0 + f1; }

/*
$$QUERY
Math
f:[f:Float1] minus [f:Float2]
qMathSubFloat
Subtract floats
  Subtracts one floating-point number from another

Parameters:
  Float1, Float2: subtracts Float2 from Float1
$$END
*/
float qMathSubFloat(float f0, float f1) { return f0 - f1; }

/*
$$QUERY
Math
f:[f:Float1] times [f:Float2]
qMathMulFloat
Multiply floats
  Multiplies two floating-point numbers and returns the result

Parameters:
  Float1, Float2: the numbers to multiply
$$END
*/
float qMathMulFloat(float f0, float f1) { return f0 * f1; }

/*
$$QUERY
Math
f:Convert int [i:Int] to float
qMathIntToFloat
Convert Int to Float
  Converts an integer value to a floating-point value

Parameters:
  Int: the interger that's converted to a float
$$END
*/
float qMathIntToFloat(int i) { return (float)i; }

/*
$$QUERY
Math
p:[p:Percent1] plus [p:Percent2]
qMathAddPercent
Add percentages
  Adds two percentages and returns the result, without going above 100%

Parameters:
  Percent1, Percent2: the percentages to add
$$END
*/
float qMathAddPercent(float f0, float f1) {
  float r = f0 + f1;

  return (r > 1.0) ? 1.0 : r;
}

/*
$$QUERY
Math
p:[p:Percent1] minus [p:Percent2]
qMathSubPercent
Subtract percentages
  Subtracts one percentage number from another, withing going below 0%

Parameters:
  Percent1, Percent2: subtracts Percent2 from Percent1
$$END
*/
float qMathSubPercent(float f0, float f1) {
  float r = f0 - f1;

  return (r < 0.0) ? 0.0 : r;
}

/*
$$QUERY
Math
i:[i:Integer1] plus [i:Integer2]
qMathAddInt
Add integers
  Adds two integer numbers and returns the result

Parameters:
  Integer1, Integer2: the numbers to add
$$END
*/
int qMathAddInt(int f0, int f1) { return f0 + f1; }

/*
$$QUERY
Math
i:[i:Integer1] minus [i:Integer2]
qMathSubInt
Subtract integers
  Subtracts one integer number from another

Parameters:
  Integer1, Integer2: subtracts Integer2 from Integer1
$$END
*/
int qMathSubInt(int f0, int f1) { return f0 - f1; }

/*
$$QUERY
Math
f:[p:Percent] of [f:Float]
qMathPercentage
Percentage of a number
  Multiplies a number by a percentage

Parameters:
  Percent: how much to scale the number by
  Float: the number that's scaled
$$END
*/
float qMathPercentage(float f0, float f1) { return f0 * f1; }

#include <math.h>

/*
$$QUERY
Objects
f:Distance between [o:Object1] and [o:Object2]
qObjGetDistance
Distance between two objects
  Gets the distance between two objects

Parameters:
  Object1, Object2: the two objects
$$END
*/
float qObjGetDistance(int objhandle0, int objhandle1) {
  msafe_struct mstruct;
  vector p0;

  mstruct.objhandle = objhandle0;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  p0 = mstruct.pos;

  mstruct.objhandle = objhandle1;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);

  return vm_VectorDistance(&p0, &mstruct.pos);
}

/*
$$QUERY
Rooms
b:Forcefield at portal [i:PortalNum] in room [r:Room] is on
qPortalIsOn
Forcefield is on
  Checks whether a forcefield is on

Parameters:
  Room:  The room the forcefield is in
  PortalNum:  The portal number of the forcefield
$$END
*/
bool qPortalIsOn(int portalnum, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.portalnum = portalnum;

  MSafe_GetValue(MSAFE_ROOM_PORTAL_RENDER, &mstruct);

  return mstruct.state;
}

/*
$$QUERY
Misc
b:Random chance of [p:Probability]
qRandomChance
Random Chance
  Determines whether a random event should happen.  Returns true the portion of the time specified.

Parameters:
  Probablilty:  how likely this query is to return true.
$$END
*/
bool qRandomChance(float prob) {
  if (prob == 0.0)
    return false;

  return ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) <= prob);
}

/*
$$QUERY
Math
f:Random value between [f:LowerLimit] and [f:UpperLimit]
qRandomValue
Random Value
  Returns a random value between the two specified values

Parameters:
  LowerLimit: the returned value will be higher than or equal to this value
  UpperLimit: the returned value will be lower than or equal to this value
$$END
*/
float qRandomValue(float low, float high) { return low + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (high - low); }

/*
$$QUERY
Objects
b:Player is within the [i:Cone=90] degree view cone of [o:Object] at a max distance of [f:Distance]
qObjCanSeePlayer
Can object see a player
  Determines if the specified object can see a player

Parameters:
  Object: The object doing the looking
  Cone: Angle between 0-360 which makes the viewcone that determines if the object can see the other object
  Distance: The player must be within this distance for this query to return true
$$END
*/
bool qObjCanSeePlayer(int cone, int handlesrc, float max_distance) {
  vector vsource, vtarget, viewvec;
  msafe_struct mstruct;

  // Get half of the angle that the user specified because they specified a cone, and we want an angle
  double cangle = (double)((double)cone / (double)2);
  double t = cangle * PI / 180;
  double testangle = cos(t);

  // Loop though all possible players
  for (int p = 0; p < MAX_PLAYERS; p++) {

    // Get player position
    mstruct.slot = p;
    MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);

    // See if this player active
    if (mstruct.objhandle == OBJECT_HANDLE_NONE)
      continue;

    // Get the target position
    MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
    vtarget = mstruct.pos;

    // Get the viewer position
    mstruct.objhandle = handlesrc;
    MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
    vsource = mstruct.pos;

    // Get the viewer orientation
    mstruct.objhandle = handlesrc;
    MSafe_GetValue(MSAFE_OBJECT_ORIENT, &mstruct);

    // Get the normalized vector from the source to the target
    float dist = vm_GetNormalizedDirFast(&viewvec, &vtarget, &vsource);

    // Get the angle between the objects
    float dot = vm_DotProduct(&viewvec, &mstruct.orient.fvec);

    // Check angle and distance
    if ((dot > testangle) && (dist < max_distance))
      return 1;
  }

  // Didn't find any in the view cone
  return 0;
}

/*
$$QUERY
Objects
b:Player is within the [i:Cone=90] degree view cone of [o:Object] at a max distance of [f:Distance] using flags
[g:FVIHitFlags=1048585:16269119] qObjCanSeePlayerAdvanced Can object see a player Determines if the specified object can
see a player (but allowing some customizability as to what the object can see through)

Parameters:
  Object: The object doing the looking
  Cone: Angle between 0-360 which makes the viewcone that determines if the object can see the other object
  Distance: The player must be within this distance for this query to return true
  FVIHitFlags: Flags used to determine visibility
$$END
*/
bool qObjCanSeePlayerAdvanced(int cone, int handlesrc, float max_distance, int fvi_flags) {
  vector vsource, vtarget, viewvec;
  msafe_struct mstruct;
  matrix orient;
  int sourceroom;

  // Get half of the angle that the user specified because they specified a cone, and we want an angle
  double cangle = (double)((double)cone / (double)2);
  double t = cangle * PI / 180;
  double testangle = cos(t);

  // Get the viewer position
  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  vsource = mstruct.pos;

  // Get the viewer orientation
  MSafe_GetValue(MSAFE_OBJECT_ORIENT, &mstruct);
  orient = mstruct.orient;

  // Get the viewer room
  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);
  sourceroom = mstruct.roomnum;

  // Loop though all possible players
  for (int p = 0; p < MAX_PLAYERS; p++) {

    // Get player position
    mstruct.slot = p;
    MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);

    // See if this player active
    if (mstruct.objhandle == OBJECT_HANDLE_NONE)
      continue;

    // Get the target position
    MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
    vtarget = mstruct.pos;

    // Get the normalized vector from the source to the target
    float dist = vm_GetNormalizedDirFast(&viewvec, &vtarget, &vsource);

    // Get the angle between the objects
    float dot = vm_DotProduct(&viewvec, &orient.fvec);

    // Check angle and distance
    if ((dot > testangle) && (dist < max_distance)) {
      // see if we can cast a ray to the player
      ray_info ray;
      fvi_flags |= (FQ_CHECK_OBJS | FQ_ONLY_PLAYER_OBJ);
      int fate = FVI_RayCast(handlesrc, &vsource, &vtarget, sourceroom, 0.0f, fvi_flags, &ray);

      if (fate == HIT_NONE)
        return true;

      if (fate == HIT_OBJECT) {
        mstruct.objhandle = ray.hit_object;
        MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);
        if (mstruct.type == OBJ_PLAYER) {
          return 1;
        }

        return 1;
      }
    }
  }

  // Didn't find any in the view cone
  return 0;
}

/*
$$QUERY
Objects
b:Player (store in [e:SavedObjectSlot]) is within the [i:Cone=90] degree view cone of [o:Object] at a max distance of
[f:Distance] using flags [g:FVIHitFlags=1048585:16269119] qObjCanSeePlayerAdvancedWithStore Can object see a player
  Determines if the specified object can see a player (but allowing some customizability as to what the object can see
through), and if the player can be seen, stores the object in the given object slot.

Parameters:
  SavedObjectSlot: the slot to save the seen player object in
  Object: The object doing the looking
  Cone: Angle between 0-360 which makes the viewcone that determines if the object can see the other object
  Distance: The player must be within this distance for this query to return true
  FVIHitFlags: Flags used to determine visibility
$$END
*/
bool qObjCanSeePlayerAdvancedWithStore(int slot, int cone, int handlesrc, float max_distance, int fvi_flags) {
  vector vsource, vtarget, viewvec;
  msafe_struct mstruct;
  matrix orient;
  int sourceroom;

  // Get half of the angle that the user specified because they specified a cone, and we want an angle
  double cangle = (double)((double)cone / (double)2);
  double t = cangle * PI / 180;
  double testangle = cos(t);

  // Get the viewer position
  mstruct.objhandle = handlesrc;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  vsource = mstruct.pos;

  // Get the viewer orientation
  MSafe_GetValue(MSAFE_OBJECT_ORIENT, &mstruct);
  orient = mstruct.orient;

  // Get the viewer room
  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &mstruct);
  sourceroom = mstruct.roomnum;

  // Loop though all possible players
  for (int p = 0; p < MAX_PLAYERS; p++) {

    // Get player position
    mstruct.slot = p;
    MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);

    // See if this player active
    if (mstruct.objhandle == OBJECT_HANDLE_NONE)
      continue;

    // Get the target position
    MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
    vtarget = mstruct.pos;

    // Get the normalized vector from the source to the target
    float dist = vm_GetNormalizedDirFast(&viewvec, &vtarget, &vsource);

    // Get the angle between the objects
    float dot = vm_DotProduct(&viewvec, &orient.fvec);

    // Check angle and distance
    if ((dot > testangle) && (dist < max_distance)) {
      // see if we can cast a ray to the player
      ray_info ray;
      fvi_flags |= (FQ_CHECK_OBJS | FQ_ONLY_PLAYER_OBJ);
      int fate = FVI_RayCast(handlesrc, &vsource, &vtarget, sourceroom, 0.0f, fvi_flags, &ray);

      if (fate == HIT_NONE) {
        if ((slot >= 0) && (slot < MAX_SAVED_OBJECT_HANDLES))
          Saved_object_handles[slot] = mstruct.objhandle;
        return true;
      }

      if (fate == HIT_OBJECT) {
        mstruct.objhandle = ray.hit_object;
        MSafe_GetValue(MSAFE_OBJECT_TYPE, &mstruct);
        if (mstruct.type == OBJ_PLAYER) {
          if ((slot >= 0) && (slot < MAX_SAVED_OBJECT_HANDLES))
            Saved_object_handles[slot] = mstruct.objhandle;
          return 1;
        }

        if ((slot >= 0) && (slot < MAX_SAVED_OBJECT_HANDLES))
          Saved_object_handles[slot] = mstruct.objhandle;

        return 1;
      }
    }
  }

  // Didn't find any in the view cone
  if ((slot >= 0) && (slot < MAX_SAVED_OBJECT_HANDLES))
    Saved_object_handles[slot] = OBJECT_HANDLE_NONE;

  return 0;
}

/*
$$QUERY
Rooms
b:A player is in room [r:Room]
qRoomHasPlayer
A player is in the room
  Determines if a player is in the specified room

Parameters:
  Room: the room to check
$$END
*/
bool qRoomHasPlayer(int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  MSafe_GetValue(MSAFE_ROOM_HAS_PLAYER, &mstruct);

  return mstruct.state;
}

/*
$$QUERY
Mission
b:Is the ship [a:Ship] enabled?
qIsShipEnabled
        Given the name of a ship, it will return true
if the ship is allowed to be chosen in the single player
ship selection.

Parameters:
  Ship: The name of the ship you want to query
$$END
*/
bool qIsShipEnabled(const char *Ship) { return Game_IsShipEnabled(Ship); }

/*
$$QUERY
Rooms
f:Room [r:Room] damage
qRoomGetDamage
Get room damage
  Returns the current damage setting for the specified room

Parameters:
  Room:  The room for which the damage is returned
$$END
*/
float qRoomGetDamage(int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;

  MSafe_GetValue(MSAFE_ROOM_DAMAGE, &mstruct);

  return mstruct.amount;
}

/*
$$QUERY
Objects
o:Saved object handle [e:SavedObjectSlot]
qObjSavedHandle
Saved object handle
  Returns the object handle saved in the specified slot

Parameters:
  HandleSlot: the slot for which the object handle is returned
$$END
*/
int qObjSavedHandle(int slot) {
  if ((slot >= 0) && (slot < MAX_SAVED_OBJECT_HANDLES))
    return Saved_object_handles[slot];
  else
    return OBJECT_HANDLE_NONE;
}

/*
$$QUERY
Triggers
Trigger [t:Trigger] state
qTriggerGetState
Get the enabled/disabled state of a trigger
  Determines if a trigger is enabled or disabled

Parameters:
  Trigger: which trigger to check
$$END
*/
bool qTriggerGetState(int trigger_num) {
  msafe_struct mstruct;

  mstruct.trigger_num = trigger_num;
  MSafe_GetValue(MSAFE_TRIGGER_SET, &mstruct);

  return mstruct.state;
}

/*
$$QUERY
Objects
i:Number of [e:ObjectType] objects of ID = [a:ObjectIDName] in mine
qObjCountTypeID
Get number of objects of a certain type
  Counts the number of objects of the specified type

Parameters:
  ObjectType: the type of the objects to count
  ObjectIDName: the name of the object ID to count
$$END
*/
int qObjCountTypeID(int type, const char *idname) {
  int id = Obj_FindID(idname);

  if (id != -1) {
    msafe_struct mstruct;

    mstruct.type = type;
    mstruct.id = id;

    MSafe_GetValue(MSAFE_OBJECT_COUNT_TYPE, &mstruct);

    return mstruct.count;
  } else
    return 0;
}

/*
$$ACTION
Misc
Show HUD message [s:Message] [f:Float]
aShowHUDMessageF
Show HUD message
  Shows a HUD message for all players with a float parameter

Parameters:
  Message:  The message to show, with %f marking where the number should go
$$END
*/
#define aShowHUDMessageF aShowHUDMessage

/*
$$ACTION
Misc
Show HUD message [s:Message] for player [o:PlayerObject=IT] with parm [f:Float]
aShowHUDMessageObjF
Show HUD message to one player
  Shows a HUD message for one players with a float parameter

Parameters:
  Message:  The message to show, with %f marking where the number should go
  PlayerObject: the player who sees the message
  Float: the number to show
$$END
*/
#define aShowHUDMessageObjF aShowHUDMessageObj

/*
$$ACTION
Misc
Show HUD message [s:Message] [i:Integer]
aShowHUDMessageI
Show HUD message
  Shows a HUD message for all players with an integer parameter

Parameters:
  Message:  The message to show, with %d marking where the number should go
$$END
*/
#define aShowHUDMessageI aShowHUDMessage

/*
$$QUERY
Level Goals
b:All Primary Objectives Complete
qGoalPrimariesComplete
All Primary Objective Complete
  Determines if all primary objectives are complete

Parameters:
  None.
$$END
*/
bool qGoalPrimariesComplete() {
  int flags = LF_ALL_PRIMARIES_DONE;

  LGoal_Value(VF_GET, LGV_I_STATUS, &flags);

  return (flags != 0);
}

/*
$$QUERY
Level Goals
b:Goal [l:LevelGoal] is enabled
qGoalEnabled
Goal is enabled
  Determines if the specified goal is enabled

Parameters:
  LevelGoal: the goal to check
$$END
*/
bool qGoalEnabled(int goal_index) {
  int flags;

  LGoal_Value(VF_GET, LGSV_I_STATUS, &flags, goal_index);

  return ((flags & LGF_ENABLED) != 0);
}

/*
$$QUERY
Level Goals
b:Goal [l:LevelGoal] is complete
qGoalCompleted
Goal is enabled
  Determines if the specified goal is complete

Parameters:
  LevelGoal: the goal to check
$$END
*/
bool qGoalCompleted(int goal_index) {
  int flags;

  LGoal_Value(VF_GET, LGSV_I_STATUS, &flags, goal_index);

  return ((flags & LGF_COMPLETED) != 0);
}

/*
$$QUERY
Level Goals
b:Goal [l:LevelGoal] is failed
qGoalFailed
Goal is failed
  Determines if the specified goal is failed

Parameters:
  LevelGoal: the goal to check
$$END
*/
bool qGoalFailed(int goal_index) {
  int flags;

  LGoal_Value(VF_GET, LGSV_I_STATUS, &flags, goal_index);

  return ((flags & LGF_FAILED) != 0);
}

/*
$$QUERY
Players
o:Closest player to [o:Object].  Store dist in user var [e:UserVar].
qPlayerClosest
Closest player
  Find the closest player to the specified object

Parameters:
  Object: the object to check players against
$$END
*/
int qPlayerClosest(int objhandle, int varnum) {
  vector objpos;
  float closest_dist = FLT_MAX;
  int closest_player = OBJECT_HANDLE_NONE;
  msafe_struct mstruct;

  // Get the object position
  mstruct.objhandle = objhandle;
  MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);
  objpos = mstruct.pos;

  // Loop though all possible players and compute distance
  for (int p = 0; p < MAX_PLAYERS; p++) {

    // Get player position
    mstruct.slot = p;
    MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);

    // See if this player active
    if (mstruct.objhandle == OBJECT_HANDLE_NONE)
      continue;

    // Get the target position
    MSafe_GetValue(MSAFE_OBJECT_POS, &mstruct);

    // Get the normalized vector from the source to the target
    float dist = vm_VectorDistanceQuick(&objpos, &mstruct.pos);

    if (dist < closest_dist) {
      closest_dist = dist;
      closest_player = mstruct.objhandle;
    }
  }

  if ((varnum >= 0) && (varnum < MAX_USER_VARS))
    User_vars[varnum] = closest_dist;

  return closest_player;
}

/*
$$QUERY
Objects
f:[o:WeaponObject=IT] damage
qObjDamage
Object damage
  Returns the amount of damage the given weapon object does

Parameters:
  WeaponObject: The weapon object whose damage it returned
$$END
*/
float qObjDamage(int handle) {
  msafe_struct mstruct;

  mstruct.objhandle = handle;
  MSafe_GetValue(MSAFE_OBJECT_DAMAGE_AMOUNT, &mstruct);

  return mstruct.amount;
}

/*
$$QUERY
Misc
f:Frametime
qFrametime
Game Frametime
  Returns the frametime

Parameters:
  None
$$END
*/
float qFrametime() { return Game_GetFrameTime(); }

/*
$$QUERY
AI
f:[o:Object] max speed
qAIQueryMaxSpeed

Parameters:
        Object: Get object's max speed.
$$END
*/
float qAIQueryMaxSpeed(int objhandle) {
  float max_speed = 0.0f;
  AI_Value(objhandle, VF_GET, AIV_F_MAX_SPEED, &max_speed);
  return max_speed;
}
