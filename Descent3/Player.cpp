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

 * $Logfile: /DescentIII/Main/Player.cpp $
 * $Revision: 331 $
 * $Date: 10/22/01 12:43p $
 * $Author: Matt $
 *
 * Code for dealing with players
 *
 * $Log: /DescentIII/Main/Player.cpp $
 *
 * 331   10/22/01 12:43p Matt
 * On player death/exit, don't try to spew a red guidebot if Mercenary is
 * not installed.
 *
 * 330   3/20/00 12:19p Matt
 * Merge of Duane's post-1.3 changes.
 * Change for no avilable vis effects.
 *
 * 329   1/26/00 9:20p Jeff
 * added support for IntelliVIBE DLL
 *
 * 328   11/02/99 1:56p Chris
 * Fixed bug with black pyro spewing a blue gb on death
 *
 * 327   10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 326   10/20/99 5:40p Chris
 * Added the Red Guidebot
 *
 * 325   7/28/99 3:47p Kevin
 * Mac!
 *
 * 324   7/26/99 4:56p Kevin
 * more demo bug fixes
 *
 * 323   7/26/99 12:40p Kevin
 * Fixed some multiplayer client recorded demo bugs
 *
 * 322   7/08/99 5:45p Jason
 * Bug fixes for the patch
 *
 * 321   5/23/99 3:06a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 320   5/21/99 7:09p Jason
 * fixed some weird multiplayer rejoin anomalies
 *
 * 319   5/20/99 7:54p 3dsmax
 * added better memory support changing ships
 *
 * 318   5/20/99 2:53p Jason
 * made autowaypoints work in coop
 *
 * 317   5/20/99 2:48a Matt
 * Auto-waypoints now stored & used per player.  Manual waypoints will all
 * players, once Jason makes it work.
 *
 * 316   5/19/99 3:25p Jason
 * fixed wrong ordering of InitObjectScripts and MultiSendObject
 *
 * 315   5/17/99 11:03a Matt
 * When initializing the player ship for a new level, limit the ammo to
 * the max the ship can carry.
 *
 * 314   5/13/99 3:41p Ardussi
 * changes for compiling on the Mac
 *
 * 313   5/12/99 3:26p Jason
 * made terrain damage effect multiplayer friendly
 *
 * 312   5/10/99 10:23p Ardussi
 * changes to compile on Mac
 *
 * 311   5/10/99 9:25p Jeff
 * first phase of Rock 'n' Ride support added
 *
 * 310   5/10/99 2:01a Jason
 * make player invulnerable for 2 seconds during respawn in a single
 * player game
 *
 * 309   5/08/99 4:12p Chris
 * Added AI hearing noises... version 1
 *
 * 308   5/07/99 1:44p Chris
 * Made in-game cinematics use the ORIENT_PATH_NODE for player ships
 *
 * 307   5/05/99 2:33p Jason
 * Room 18 face 116: No connection for edge 3
 * Room 18 face 116: No connection for edge 4
 * Room 18 face 116: No connection for edge 5
 * Room 18 face 140: No connection for edge 0
 * Fixed some multiplayer issues
 *
 * 306   5/05/99 1:32a Jeff
 * save/restore player energy also
 *
 * 305   5/05/99 1:28a Jeff
 * save/restore player's shields in single player game if they are over
 * 100
 *
 * 304   5/04/99 9:27p Jeff
 * cheaters don't win! (no score for cheaters)
 *
 * 303   5/04/99 7:09p Jason
 * changed sun damage effect just a little
 *
 * 302   4/29/99 3:03p Jason
 * fixed player popping in and out in a multiplayer game
 *
 * 301   4/28/99 5:55p Matt
 * Don't spew powerup for secondaries if have none.  This fixes spewing
 * multipacks with count == 0.
 *
 * 300   4/28/99 5:10p Jeff
 * fixed inventory spew in multiplayer (with non-spewable items)
 *
 * 299   4/28/99 2:25a Jeff
 * added call to add guidebot in selected multiplayer games to the clients
 *
 * 298   4/27/99 10:33p Matt
 * Added code to spew multi-pack powerups upon death if available for a
 * weapon.  Now you're not limited to spewing three homing missiles, for
 * example -- you can spew a multi-pack with 8 missiles in it.
 *
 * 297   4/27/99 4:27p Jeff
 * added player respawn osiris event
 *
 * 296   4/27/99 4:44a Jeff
 * only add guidebots to inventory in a single player game...must figure
 * out a way to handle initial join of multiplayer
 *
 * 295   4/27/99 1:38a Jason
 * fixed sparse array bug with players
 *
 * 294   4/26/99 7:53p Jason
 * temp fix for multiplayer waypoints
 *
 * 293   4/24/99 10:39p Samir
 * turn off any current ship engine sounds if ship noises are turned off
 *
 * 292   4/24/99 8:40p Samir
 * ship toggle sounds implemented.
 *
 * 291   4/24/99 7:22p Jason
 * fixed another respawn problem
 *
 * 290   4/24/99 6:45p Jeff
 * added functions for theif so he can steal things other than weapons
 *
 * 289   4/24/99 2:20a Chris
 * Added the Neutral_till_hit flag
 *
 * 288   4/23/99 1:56a Matt
 * Added system for counting kills of friendly objects
 *
 * 287   4/22/99 4:31p Jason
 * fixed team spawning problems
 *
 * 286   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 285   4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 284   4/10/99 5:56p Matt
 * Cleaned up object initialization code, including create object & load
 * object.
 *
 * 283   4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 282   4/06/99 6:25p Jason
 * various fixes for multiplayer
 *
 * 281   4/06/99 6:02p Matt
 * Added score system
 *
 * 280   4/06/99 2:08p Jason
 * fixed crashes with dying models not being set
 *
 * 279   4/05/99 3:34p Matt
 * Cleaned up player start flags
 *
 * 278   4/05/99 10:54a Matt
 * Added auto-waypoint system
 *
 * 277   4/03/99 2:20p Jason
 * added better heat damage effect
 *
 * 276   4/02/99 6:31p Jason
 * Fixed multiplayer powerup/player start bugs
 *
 * 275   4/02/99 3:55p Chris
 * Fixed or at least commented about guidebot bugs
 *
 * 274   3/31/99 10:27a Samir
 * code to reset auto select states when ship is initializiaed and code to
 * save and load these states from disk.
 *
 * 273   3/23/99 12:33p Kevin
 * More post level results improvements
 *
 * 272   3/16/99 6:43p Kevin
 * OEM Split fixes
 *
 * 271   3/12/99 7:45p Jeff
 * handle demo items (lifeleft, player change type, etc).  Reset quad fire
 * masks on inventory spew.
 *
 * 270   3/11/99 6:31p Jeff
 * numerous fixes to demo system in multiplayer games (when
 * recording/playback a demo in a multiplayer game)
 *
 * 269   3/10/99 2:25p Kevin
 * Save/Load and Demo file fixes
 *
 * 268   3/09/99 6:34p Kevin
 * Made the training mission not be branching, and fixed the crash with
 * people dying in the demo playback
 *
 * 267   3/09/99 6:17p Jason
 * fixed observer mode changing
 *
 * 266   3/09/99 3:19p Jason
 * fixed persistent player death message in multiplayer game
 *
 * 265   3/08/99 5:14p Jason
 * added delay to player respawn after death
 *
 * 264   3/05/99 11:57a Jason
 * fixes for OEM
 *
 * 263   3/04/99 7:39p Matt
 * Added sound effects to FreeSpace-style persistent HUD messages.
 *
 * 262   3/03/99 5:35p Matt
 * Added fade-out for goal complete messages
 *
 * 261   3/03/99 3:38a Samir
 * reset reticle when you die.
 *
 * 260   3/02/99 2:50p Samir
 * hud observer mode works with rest of hud.
 *
 * 259   3/02/99 1:17p Jason
 * made player textures play at a fixed rate
 *
 * 258   3/02/99 12:22p Matt
 * Revisions to weapon & ammo powerups.  Not fully tested.
 *
 * 257   3/01/99 7:20p Chris
 * Fixed dist problems with finding nearby objects
 *
 * 256   3/01/99 4:17p Jeff
 *
 * 255   2/25/99 8:55p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 254   2/25/99 10:28a Jason
 * made player able to fire flares in netgames
 *
 * 253   2/24/99 11:25a Matt
 * Small improvement
 *
 * 251   2/23/99 7:35p Jeff
 * handle not spewing of inventory items marked as such
 *
 * 250   2/22/99 2:04p Jason
 * added different damages for players and generics
 *
 * 249   2/18/99 5:27p Matt
 * Added color parm to AddPersistentHUDMessage() and fixed the timeout.
 *
 * 248   2/17/99 2:08p Jason
 * fixed observermode bug
 *
 * 247   2/17/99 2:04p Jason
 * changed spew timeouts just a little
 *
 * 246   2/16/99 3:47p Jason
 * added marker updates to multiplayer server stream
 *
 * 245   2/15/99 7:50p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 244   2/15/99 11:22a Jason
 * took out client-side prediciton
 *
 * 243   2/13/99 12:32a Jeff
 * updated inventory spew to handle 'new' inventory system.  Inventory
 * reset takes a different parameter too now.
 *
 * 242   2/12/99 3:38p Jason
 * added client side interpolation
 *
 * 241   2/11/99 1:22a Jeff
 * made function to switch a player into AI mode, converted code that did
 * this to call this function.
 *
 * 240   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 239   2/09/99 6:53p Jeff
 * implemented 'typing inidcator' in multiplayer...players that are typing
 * messages have an icon on them
 *
 * 238   2/08/99 5:26p Jeff
 * removed all calls to MultiSendRemoveObject, incorportated into
 * SetObjectDeadFlag.  Fixes sequencing issues in multiplayer
 *
 * 237   2/08/99 3:06a Jeff
 * added a function to reset a player's control type
 *
 * 236   2/06/99 10:03p Matt
 * Added keys system
 *
 * 235   2/04/99 11:20a Jason
 * added waypoint message
 *
 * 234   2/04/99 11:01a Jason
 * added anti cheating to multiplayer
 *
 * 233   2/03/99 4:26p Jason
 * made multiplayer coop actually work!
 *
 * 232   2/03/99 1:50a Jeff
 * fixed bug on checking if a player ship is available (if -1 is passed
 * in)
 *
 * 231   2/01/99 4:25p Jeff
 * fixed player invulnerabilty after cinematic sequence and death bug
 *
 * 230   2/01/99 12:56p Jeff
 * correctly restore hud if in cinematics
 *
 * 229   1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 228   1/29/99 7:13p Jeff
 * localization
 *
 * 227   1/28/99 6:17p Jason
 * added markers
 *
 * 226   1/27/99 6:37p Jason
 * fixed player spawning over terrain
 *
 * 225   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 224   1/20/99 4:23p Jason
 * made player flags work again
 *
 * 223   1/18/99 6:18p Kevin
 * Added controller masking to DALLAS
 *
 * 222   1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 221   1/14/99 4:24p Jason
 * made damage effect go away much faster
 *
 * 220   1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 219   1/12/99 7:11p Jeff
 * init scripts on player spew
 *
 * 218   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 217   1/06/99 12:34p Jason
 * misc changes for multiplayer
 *
 * 216   12/01/98 3:35p Matt
 * Got rear view working.
 *
 * 215   11/23/98 1:50p Jason
 * added thruster sounds
 *
 * 214   11/13/98 12:30p Jason
 * changes for weapons
 *
 * 213   11/11/98 7:18p Jeff
 * changes made so that a dedicated server's team is always -1 (team game
 * or not)
 *
 * 212   11/11/98 11:41a Jason
 * added sunlight damage
 *
 * 211   11/06/98 11:39a Chris
 * Robots with flamethrowers and Omega cannons work in single player
 *
 * 210   11/03/98 6:16p Chris
 * Starting to make on/off and spray weapons accessable to robots
 *
 * 209   10/29/98 4:54p Jason
 * made ClearTransientObjects not work in multiplayer
 *
 * 208   10/28/98 5:25p Jason
 * fixed player death problems in multiplayer
 *
 * 207   10/22/98 10:45p Samir
 * try more death options.
 *
 * 206   10/22/98 2:58p Chris
 * Difficulty levels are in beta
 *
 * 205   10/19/98 9:22p Matt
 * Stop effects sound when resetting player object.
 *
 * 204   10/19/98 11:35a Chris
 * Made a change in when the player gets GB
 *
 * 203   10/18/98 11:11p Matt
 * Added call to ClearTransientObjects() and cleaned up some sequencing
 * stuff.
 *
 * 202   10/18/98 7:27p Samir
 * spin on y axis for d2 death.
 *
 * 201   10/17/98 3:07p Jason
 * respawn players not near each other
 *
 * 200   10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 199   10/14/98 4:27p Samir
 * use new persistent hud message system for death message.
 *
 * 198   10/14/98 1:02p Jason
 * fixed FindSoundName issues
 *
 * 197   10/13/98 4:12p Jason
 * toned down speed of observer mode
 *
 * 196   10/13/98 3:41p Kevin
 * bug fixes
 *
 * 195   10/13/98 2:31p Jason
 * automatically create new player starts
 *
 * 194   10/13/98 1:53p Jason
 * added some asserts to track down explosion bug
 *
 * 193   10/08/98 5:49p Sean
 * (Jeff) fixed reset of Quad fire flag when resetting a player ship
 *
 * 192   10/08/98 3:36p Jason
 * fixes for the demo
 *
 * 191   10/07/98 9:29p Jeff
 * reset quad firing masks on init new ship
 *
 * 190   10/07/98 12:35p Jason
 * fixed player cameras going from level to level
 *
 * 189   10/05/98 6:48p Jason
 * took out annoying mprintf
 *
 * 188   10/03/98 8:05p Matt
 * Added asserts
 *
 * 187   10/02/98 8:54p Jason
 * fixed bad parentin on badass damage
 *
 * 186   10/02/98 12:31p Samir
 * restored player breakup with fixed code (from renderobject.cpp too).
 *
 * 185   10/01/98 11:30a Jeff
 * made the observer mode events into just a client event
 *
 * 184   9/30/98 4:05p Jason
 * more parenting fun
 *
 * 183   9/30/98 3:49p Jeff
 * added events for when a player enters/exits observer mode
 *
 * 182   9/30/98 3:17p Jason
 * fixed countermeasure spewing problem
 *
 * 181   9/29/98 1:59p Jason
 * don't do breakup death
 *
 * 180   9/28/98 8:39p Jason
 * give spewed objects parents
 *
 * 179   9/28/98 10:59a Samir
 * clarified passing of pointer to CreateFireball in
 * PlayerShipSpewPartSub.   Adding two vectors should return a vector
 * reference, and that should be valid, but I guess not.
 *
 * 178   9/23/98 6:07p Samir
 * player death cam should fit nicely on walls.
 *
 * 177   9/23/98 2:55p Chris
 * Improved auto-leveling and added newbie leveling
 *
 * 176   9/22/98 6:48p Jason
 * fixed dedicated server problems
 *
 * 175   9/22/98 5:20p Jason
 * fixed some player bugs
 *
 * 174   9/22/98 11:15a Jeff
 * took out bad ASSERT
 *
 * 173   9/21/98 12:56p Jason
 * made camera even smoother
 *
 * 172   9/21/98 12:11p Jason
 * fixed camera problems
 *
 * 171   9/18/98 6:09p Jason
 * added smoother camera
 *
 * 170   9/18/98 4:52p Jason
 * Incremental checkin for camera
 *
 * 169   9/18/98 1:27p Matt
 * Added afterburner release sound
 *
 * 168   9/18/98 11:18a Jason
 * fixed miscellaneous bugs with camera system
 *
 * 167   9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 166   9/16/98 5:10p Jason
 * added first pass at thrid-person camera system
 *
 * 165   9/11/98 12:26p Jason
 * got energy to shield and fusion damage working in multiplayer
 *
 * 164   9/10/98 12:18p Jason
 * more changes to afterburner/thrust effect
 *
 * 163   9/09/98 7:09p Jason
 * changed afterburner effect for ships
 *
 * 162   8/28/98 1:34p Matt
 * Added code to reset the waypoint when starting a new level, and while I
 * was at it cleaned up the new level start sequencing.
 *
 * 161   8/24/98 2:45p Jason
 * added team start position stuff
 *
 * 160   8/24/98 12:24p Jason
 * added waypoints and player start position flags
 *
 * 159   8/20/98 7:01p Jeff
 * changed sound on energy->shields converter
 *
 * 158   8/19/98 12:38p Jason
 * made countermeasure spewing work correctly
 *
 * 157   8/17/98 10:48a Jason
 * added more sparks when players explode
 *
 * 156   8/16/98 6:18p Chris
 * Fixed player spewing
 *
 * 155   8/16/98 2:34a Jeff
 * fixed a hud message
 *
 * 154   8/16/98 12:19a Jeff
 * added energy->shields function
 *
 * 153   8/10/98 2:21p Jeff
 * changes made due to adding flag for inventory reset
 *
 * 152   8/07/98 2:44p Jeff
 * some changes to ship permissions (reset can take a -1 for pnum in order
 * to reset everyone)
 *
 * 151   8/07/98 10:51a Jason
 * made custom textures 64x64
 *
 * 150   8/06/98 2:44p Jeff
 * added ship permissions functions (first round)
 *
 * 149   8/03/98 5:56p Jason
 * got fusion cannon working correctly
 *
 * 148   8/03/98 4:29p Jason
 * fixed afterburner bug
 *
 * 147   7/31/98 3:24p Samir
 * allow breakup death outside only.
 *
 * 146   7/31/98 1:55p Jason
 * added a function for custom textures
 *
 * 145   7/31/98 11:51a Jason
 * added player ship choosing to multiplayer games
 *
 * 144   7/29/98 12:47p Jason
 * multiplayer changes
 *
 * 143   7/28/98 5:39p Samir
 * tweaked death sequence.
 *
 * 142   7/28/98 12:29p Jason
 * added rotational velocity to multiplayer position packets
 *
 * 141   7/27/98 5:59p Jason
 * added piggyback mode plus multiplayer colors
 *
 * 140   7/22/98 4:36p Jason
 * took out bugs from observer mode
 *
 * 139   7/22/98 3:16p Jason
 * added observer mode
 *
 * 138   7/20/98 10:42a Jason
 * added more player scalars, plus afterburner changes
 *
 * 137   7/19/98 6:48p Jeff
 * got rid of annoying mprintf on death
 *
 * 136   7/17/98 5:57p Jason
 * misc multiplayer changes
 *
 * 135   7/15/98 2:33p Jason
 * added scalar variables for various player skills
 *
 * 134   7/03/98 3:09p Jeff
 * added  counter measures inventory
 *
 * 133   7/02/98 6:37p Jason
 * fixed bug with last rev
 *
 * 132   7/02/98 6:30p Jason
 * added some multiplayer stuff for Jeff
 *
 * 131   7/02/98 12:57p Jason
 * various changes for multiplayer positional sequencing
 *
 * 130   6/29/98 3:08p Jason
 * added on/off weapons
 *
 * 129   6/25/98 5:17p Jason
 * added multiple colored balls for players
 *
 * 128   6/22/98 6:02p Samir
 * don't show cockpit when dying.
 *
 * 127   6/17/98 6:31p Samir
 * Added anti-grav warning when dying.
 *
 * 126   6/16/98 10:54a Jeff
 *
 * 125   6/15/98 6:08p Chris
 * Hit_type to hit_type[0]
 *
 * 124   6/11/98 12:48p Jason
 * added better spewing weapons
 *
 * 123   6/05/98 4:54p Samir
 * fixed bugs in MoveDeathCam.
 *
 * 122   6/03/98 6:42p Chris
 * Added multipoint collision detection an Assert on invalid (infinite
 * endpoint).
 *
 * 121   6/02/98 5:49p Jeff
 * changed assert in PlayerSpewObject so it handles a ghost along with
 * player type
 *
 * 120   6/01/98 10:37a Matt
 * Added system to spew powerups when the player dies.  Still needs Jason
 * to deal with  mng_FindSpecificGenericPage().
 *
 * 119   5/27/98 12:36a Samir
 * invulnerablize player at start of E3 demo level, and use default
 * weapons.
 *
 * 118   5/26/98 10:48p Samir
 * for E3, new level = special weapons.
 *
 * 117   5/25/98 6:50p Matt
 * Added needed include.
 *
 * 116   5/22/98 6:27p Samir
 * reimplemented spinning D2 death, a bit modified.
 *
 * 115   5/22/98 11:59a Chris
 * Fixed improper uses of FindSoundName and made the proper static sounds
 *
 * 114   5/15/98 5:41p Jason
 * implemented volume lighting system
 *
 * 113   5/12/98 3:45p Chris
 * Added a "dead" buddy when the player dies with the buddy in his
 * inventory
 *
 * 112   5/11/98 4:40p Chris
 * AI info is now a malloc'ed pointer
 *
 * 111   5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 110   5/04/98 12:22p Chris
 * Improved Guidebot spewing
 *
 * 109   5/04/98 10:56a Kevin
 * Mastertracker fixes/enhancements
 *
 * 108   5/01/98 6:50p Samir
 * changed death sequence to fall on melee kill (single player) and death
 * camera improvements.
 *
 * 107   5/01/98 4:32p Jason
 * take care afterburner sound when a player dies
 *
 * 106   4/30/98 2:48p Kevin
 * mastertracker
 *
 * 105   4/30/98 2:34p Kevin
 * Movet mastertracker stuff to playerinit
 *
 * 104   4/30/98 1:15p Kevin
 * Added lifetime deaths and kills for MT
 *
 * 103   4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 102   4/29/98 12:51p Kevin
 * Added mastertracker values
 *
 * 101   4/27/98 1:14p Jason
 * cleaned up afterburner stuff
 *
 * 100   4/22/98 4:20p Jason
 * reset player effects when dead
 *
 * 99    4/22/98 3:25p Jason
 * changes for multiplayer debugging
 *
 * 98    4/20/98 3:03p Craig
 * FROM JASON: Fixed effect resetting bug
 *
 * 97    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 96    4/18/98 7:17a Samir
 * Update level time each player frame.
 *
 * 95    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 94    4/15/98 2:33p Jason
 * changed some smoke trail stuff
 *
 * 93    4/13/98 12:42p Jason
 * changed afterburner effect
 *
 * 92    4/10/98 8:59p Jason
 * toned down red damage effect
 *
 * 91    4/10/98 3:28p Jason
 * fixed afterburner bug
 *
 * 90    4/10/98 2:42p Jason
 * fixed afterburner blobs to be a stream
 *
 * 89    4/09/98 7:15p Craig
 * Remove inventory add
 *
 * 88    4/09/98 5:18p Jason
 * got guided working in multiplayer
 *
 * 87    4/09/98 2:23p Jason
 * added guided/afterburner stuff
 *
 * 86    4/07/98 7:17p Chris
 * Removed guidebots from multiplayer
 *
 * 85    4/07/98 4:50p Jason
 * made red damage glow fade much quicker
 *
 * 84    4/07/98 4:25p Chris
 * Added support for buddy bot
 *
 * 83    4/06/98 2:54p Jason
 * yet more multiplayer changes
 *
 * 82    4/06/98 12:14p Jason
 * changes to multiplayer
 *
 * 81    4/03/98 12:28p Jason
 * fixed confusion with clients changing rooms in multiplayer
 *
 * 80    4/03/98 11:55a Jason
 * fixed polymodel paging problem
 *
 * 79    4/02/98 6:32p Jason
 * get multiple items in inventory spewing
 *
 * 78    4/01/98 6:23p Jason
 * added a slew of stuff for multiplayer
 *
 * 77    4/01/98 2:13p Jason
 * added PlayerChangeShip
 *
 * 76    4/01/98 12:02p Jason
 * incremental checkin for rendering changes
 *
 * 75    3/31/98 11:15a Jason
 * added the ability for player objects to cast light
 *
 * 74    3/30/98 5:11p Jason
 * more changes for game/dll integration
 *
 * 73    3/27/98 6:53p Samir
 * lessen death glitter.
 *
 * 72    3/23/98 7:37p Jason
 * fixed multiplayer shield problem
 *
 * 71    3/20/98 6:05p Chris
 * Fixed a bug with player sounds
 *
 * 70    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 69    3/20/98 2:18p Jason
 * changes for multiplayer
 *
 * 68    3/19/98 7:15p Jason
 * more changes for multiplayer
 *
 * 67    3/18/98 5:45p Jason
 * more multiplayer script integration
 *
 * 66    3/18/98 12:11p Jason
 * fixed non-existant killer problems
 *
 * 65    3/18/98 11:08a Jason
 * more changes for script and multiplayer
 *
 * 64    3/17/98 3:25p Jason
 * added number of team functions
 *
 * 63    3/17/98 2:40p Samir
 * reorg of hud/gauge system.
 *
 * 62    3/17/98 11:34a Jason
 * added GetGoalRoom stuff
 *
 * 61    3/13/98 12:09p Samir
 * made changes to reflect new cockpit.cpp and cockpit.h
 *
 * 60    3/12/98 7:30p Chris
 * Added ObjSetOrient
 *
 * 59    2/25/98 2:05p Jason
 * did FOV and object visibility changes
 *
 * 58    2/25/98 1:01p Jason
 * fixed FOV effect showing up for everyone in a multiplayer game
 *
 * 57    2/24/98 2:31p Jason
 * added FOV warp effect for when coming back to life
 *
 * 56    2/23/98 4:52p Chris
 * Removed size hack
 *
 * 55    2/19/98 6:38p Chris
 * Added the ship size hack back in.
 *
 * 54    2/19/98 6:31p Jason
 * fixed bug where a player killer object wasn't valid
 *
 * 53    2/18/98 11:03p Chris
 * Removed the false ship size of 4.0 that we used for the milestone
 *
 * 52    2/18/98 2:13a Chris
 * hacked size to 4
 *
 * 51    2/17/98 11:33p Matt
 * Stop player weapon firing activity when player dies
 *
 * 50    2/17/98 3:46p Matt
 * Revamped weapon system and got sounds for spray and fusion weapons
 * working.  Still need to implements getting continuous & cutoff sounds
 * from player ship.
 *
 * 49    2/15/98 4:50p Jeff
 * added a call to reset the player's inventory
 *
 * 48    2/09/98 5:38p Jeff
 * changed EVT_PLAYEREXPLODED to EVT_GAMEPLAYEREXPLODED
 *
 * 47    2/06/98 6:07p Jason
 * made multiplayer objects get deleted in single-player mode
 *
 * 46    2/05/98 2:57p Matt
 * Changed code to use ObjSetPos()
 *
 * 45    2/05/98 10:44a Jason
 * changed Red_blast_ring_index define
 *
 * 44    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 43    2/03/98 4:04p Jeff
 * added OSIRIS events for player killed and exploded
 *
 * 42    1/28/98 1:12p Jason
 * took shields field out of Player struct
 *
 * 41    1/28/98 12:00p Jason
 * more changes for multiplayer
 *
 * 40    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 39    1/23/98 11:21a Jason
 * incremental multiplayer checkin
 *
 * 38    1/21/98 6:09p Jason
 * Got player deaths working in multiplayer
 *
 * 37    1/21/98 1:31p Samir
 * No use thrust because of multiplayer.
 *
 * 36    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 35    1/20/98 6:35p Samir
 * Death sequence more multiplayer friendly?
 *
 * 34    1/20/98 6:01p Jason
 * first pass at getting multiplayer deaths working
 *
 * 33    1/20/98 12:10p Jason
 * implemented vis effect system
 *
 * 32    1/19/98 5:49p Samir
 * Some more death stuff.
 *
 * 31    1/08/98 12:31p Samir
 * Called InitPlayerNewShip when died.
 *
 * 30    1/07/98 6:39p Jason
 * Fixed player object number stuff
 *
 * 29    12/17/97 4:02p Samir
 * Fixed bug.
 *
 * 28    12/16/97 4:44p Samir
 * Some newer player death stuff.
 *
 * 27    12/10/97 3:28p Samir
 * Some randomness.
 *
 * 26    12/01/97 2:45p Samir
 * Press space bar to quit death sequence.
 *
 * 25    11/17/97 4:58p Samir
 * Fixed player death cam problems.
 *
 * 24    11/14/97 2:59p Mark
 * FROM JASON:changed the way paging weapons and player weapons work
 *
 * 23    11/11/97 12:31p Samir
 * Hopefully fixed bug when death cam is moving from terrain to mine and
 * vice-versa.
 *
 * 22    10/28/97 6:38p Samir
 * Took out include to gauges.h
 *
 * 21    10/27/97 4:31p Samir
 * Commented out annoying mprintfs.
 *
 * 20    10/27/97 10:57a Samir
 * A little better close corner death scenes.
 *
 * 19    10/23/97 6:46p Samir
 * Mostly functional player explosions with special FX like fireballs and
 * splinters, breakups, etc.
 *
 * 18    10/22/97 7:26p Samir
 * Player death mostly working.   Damn hangup still occurs.  Freaky.
 *
 * 17    10/21/97 3:16p Samir
 * Death with explosions (not customized yet.)
 *
 * 16    10/20/97 3:00p Samir
 * Tweaked some random behavior in death and 'fixed' the camera on room
 * side problem.
 *
 * 15    10/16/97 4:10p Chris
 * Added some bounciness to the player object
 *
 * 14    10/15/97 3:05p Samir
 * Death cam 99% working.
 *
 * 13    10/10/97 3:57p Samir
 * Death sequence mostly perfect.  Needs explosions still.
 *
 * 12    10/08/97 6:36p Samir
 * Except for player explosions, player death cycle implemented.  May
 * change due to asthetics.
 *
 * 11    10/03/97 11:59a Samir
 * Take care of setting player weapon usage stats.
 *
 * 10    10/01/97 4:51p Samir
 * Moved ApplyDamagePlayer to damage.cpp
 *
 * 9     9/30/97 5:34p Samir
 * Moved level script code out of this file.
 *
 * 8     9/17/97 5:40p Samir
 * Fixed some vulnerability problems.
 *
 * 7     9/17/97 11:35a Samir
 * BIG SEGMENT RIPOUT
 *
 * 6     9/12/97 4:16p Samir
 * Added cloaking and invulnerability.
 *
 * 5     9/05/97 4:37p Samir
 * Some nonsense.
 *
 * 4     9/05/97 3:53p Samir
 * Fixed some more initial player stats.
 *
 * 3     9/05/97 2:33p Samir
 * Simple player death should work.
 *
 * 2     9/05/97 12:26p Samir
 * Player takes damage, and dies.
 *
 * 5     5/06/97 3:45p Matt
 * Save all player flags in player struct, not just over_terrain
 *
 * 4     5/06/97 12:53p Matt
 * Save over terrain flag with start position in player struct
 *
 * 3     4/23/97 6:06p Jason
 * made player ship and weapons work correctly together (first pass)
 *
 * 2     4/01/97 10:49p Matt
 * Added code
 *
 * 1     4/01/97 10:27p Matt
 *
 * $NoKeywords: $
 */

#include <cmath>

#include "pserror.h"
#include "player.h"
#include "game.h"
#include "hud.h"
#include "gauges.h"
#include "Mission.h"
#include "vecmat.h"
#include "fireball.h"
#include "polymodel.h"
#include "findintersection.h"
#include "hud.h"
#include "splinter.h"
#include "PHYSICS.H"
#include "viseffect.h"
#include "damage.h"
#include "multi.h"
#include "ship.h"
#include "gameevent.h"
#include "gameloop.h"
#include "descent.h"
#include "cockpit.h"
#include "game2dll.h"
#include "robotfire.h"
#include "robot.h"
#include "AIMain.h"
#include "aipath.h"
#include "AIGoal.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "sounds.h"
#include "weapon.h"
#include "stringtable.h"
#include "pilot.h"
#include "vclip.h"
#include <stdlib.h>
#include "objinit.h"
#include "difficulty.h"
#include "ddio.h"
#include "ObjScript.h"
#include "gamecinematics.h"
#include "demofile.h"
#include "psrand.h"
#include "osiris_share.h"
#include "config.h"
#include "osiris_dll.h"
#include "gamesequence.h"

#include <algorithm>

player Players[MAX_PLAYERS];
int Player_num;

int Num_teams = 0;
int Team_game = 0;
int Default_ship_permission = 0x01;
float HudNameTan = -1;

team Teams[MAX_TEAMS];

static int Highest_player_start = 0;

// Only one of these waypoint variable can be active at one time; the other will be -1
int Current_waypoint = 0; // the most recent manually-set waypoint, or -1

// Stuff for the new score info on the HUD
int Score_added = 0;           // the recently-added amount
float Score_added_timer = 0.0; // how long the added value will be displayed

// Camera stuff
#define MAX_CAMERA_SAMPLES 100
#define MAX_CAMERA_SUB_SAMPLES 50
#define CAMERA_LAG_TIME .10f // How far behind the camera is in time
#define CAMERA_SAMPLE_INCREMENT (CAMERA_LAG_TIME / (float)MAX_CAMERA_SUB_SAMPLES)
bool Player_has_camera = false;
int Player_camera_objnum = -1;
float Player_shields_saved_from_last_level = -1.0f;
float Player_energy_saved_from_last_level = -1.0f;

uint32_t Players_typing; // information about which players are typing messages (to display an icon)

static float Player_camera_last_sample_time = 0;
static float Player_camera_last_follow_time = 0;

static int Camera_sample_index = 0;
static int Camera_follow_index = 0;
static vector Camera_sample_vectors[MAX_CAMERA_SAMPLES];
static matrix Camera_sample_matrix[MAX_CAMERA_SAMPLES];
static int Camera_sample_rooms[MAX_CAMERA_SAMPLES];

float Total_time_dead = 0;

static void StartPlayerDeath(int slot, float damage, bool melee, int fate);

// Sets up the players array
void InitPlayers() {
  int i;

  // find the ships that are allowed by default
  Default_ship_permission = 0;
  for (i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used & Ships[i].flags & SF_DEFAULT_ALLOW) {
      int flag = 0x01;
      flag = flag << i;
      Default_ship_permission |= flag;
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    Players[i].startpos_flags = 0;

    int index = AllocTexture();

    ASSERT(index >= 0);
    GameTextures[index].bm_handle = 0;
    snprintf(GameTextures[index].name, sizeof(GameTextures[index].name), "Player %d texture", i);
    Players[i].custom_texture_handle = index;
  }
  PlayerResetShipPermissions(-1, true);
  Players_typing = 0;
}

// Look for player objects & set player starts
void FindPlayerStarts() {
  int i;
  int unique = 0;

  // Flag all players as unused
  for (i = 0; i < MAX_PLAYERS; i++)
    Players[i].start_roomnum = -1;

  Highest_player_start = 0;

  if (Game_mode & GM_MULTI) {
    ps_srand(400);
  }

  // Now look for player objects
  for (i = 0; i <= Highest_object_index; i++)
    if (Objects[i].type == OBJ_PLAYER) {
      ASSERT(Players[Objects[i].id].start_roomnum == -1); // make sure not used twice
      Players[Objects[i].id].start_pos = Objects[i].pos;
      Players[Objects[i].id].start_roomnum = Objects[i].roomnum;
      Players[Objects[i].id].start_orient = Objects[i].orient;
      Players[Objects[i].id].objnum = i;

      if (Objects[i].id > Highest_player_start)
        Highest_player_start = Objects[i].id;

      unique++;
    }

  mprintf(0, "There are %d unique start positions in this level\n", unique);

  // Now create the extra players
  if (Game_mode & GM_MULTI) {
    // Build a list so we can fill in the rest
    int choose_list[MAX_PLAYERS];
    int num_choose = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
      if (Players[i].start_roomnum != -1) {
        choose_list[num_choose++] = i;
      }
    }
    for (i = Highest_player_start + 1; i < MAX_PLAYERS; i++) {
      int oldplaynum = ps_rand() % num_choose;
      oldplaynum = choose_list[oldplaynum];

      int objnum = ObjCreate(OBJ_PLAYER, i, Players[oldplaynum].start_roomnum, &Players[oldplaynum].start_pos,
                             &Players[oldplaynum].start_orient);
      ASSERT(objnum >= 0);
      Players[Objects[objnum].id].start_pos = Players[oldplaynum].start_pos;
      Players[Objects[objnum].id].start_roomnum = Players[oldplaynum].start_roomnum;
      Players[Objects[objnum].id].start_orient = Players[oldplaynum].start_orient;
      Players[Objects[objnum].id].startpos_flags = Players[oldplaynum].startpos_flags;
      Players[Objects[objnum].id].objnum = objnum;
      if (Objects[objnum].id > Highest_player_start)
        Highest_player_start = Objects[objnum].id;
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
      // Make all extra slots use slot 0
      if (Players[i].start_roomnum == -1) {
        int oldplaynum = ps_rand() % num_choose;
        oldplaynum = choose_list[oldplaynum];

        int objnum = ObjCreate(OBJ_PLAYER, i, Players[oldplaynum].start_roomnum, &Players[oldplaynum].start_pos,
                               &Players[oldplaynum].start_orient);
        ASSERT(objnum >= 0);
        Players[Objects[objnum].id].start_pos = Players[oldplaynum].start_pos;
        Players[Objects[objnum].id].start_roomnum = Players[oldplaynum].start_roomnum;
        Players[Objects[objnum].id].start_orient = Players[oldplaynum].start_orient;
        Players[Objects[objnum].id].startpos_flags = Players[oldplaynum].startpos_flags;
        Players[Objects[objnum].id].objnum = objnum;
        if (Objects[objnum].id > Highest_player_start)
          Highest_player_start = Objects[objnum].id;
      }
    }
  }
}

// Returns a random player starting position
int PlayerGetRandomStartPosition(int slot) {
  if (Netgame.flags & NF_RESPAWN_WAYPOINT) {
    // Grab an autowaypoint
    if (Players[slot].current_auto_waypoint_room != -1) {
      int waypointnum = -(Players[slot].current_auto_waypoint_room - 1);
      return waypointnum;
    } else {
      if (Current_waypoint < 0)
        return 0;
      else
        return Current_waypoint;
    }
  }

  ps_srand((timer_GetTime() * 1000));
  // If this is a team game then pick a spot on that team
  if (Team_game) {

    int team = PlayerGetTeam(slot);
    mprintf(0, "Picking team start position, team=%d.\n", team);
    int num_avail = 0;
    int avail_array[MAX_PLAYERS];

    for (int i = 0; i <= Highest_player_start; i++) {
      if ((Players[i].startpos_flags & (1 << team)) && Players[i].start_roomnum != -1) {
        avail_array[num_avail] = i;
        num_avail++;
      }
    }
    if (num_avail > 0) {
      int num;
      int done = 0;
      while (!done) {
        num = avail_array[ps_rand() % (num_avail)];
        if (Players[num].start_roomnum != -1)
          done = 1;
      }
      return num;
    }
  }

  // Default to non-team mode
  int num;
  int done = 0;
  int badcount = 0;
  mprintf(0, "Picking non-team start position.\n");
  while (!done) {
    num = ps_rand() % (Highest_player_start + 1);
    if (Players[num].start_roomnum != -1) {
      // Check to see if there are any other players in this room
      int objnum = -1;
      if (Players[num].start_roomnum >= 0) {
        room *rp = &Rooms[Players[num].start_roomnum];
        objnum = rp->objects;
      } else {
        objnum = Terrain_seg[Players[num].start_roomnum].objects;
      }
      int bad = 0;
      for (; objnum != -1 && !bad; objnum = Objects[objnum].next) {
        if (Objects[objnum].type == OBJ_PLAYER)
          bad = 1;
      }

      if (bad) {
        badcount++;
        if (badcount >= 15) // give up after fifteen tries
        {
          mprintf(0, "Stopping cuz I couldn't find a valid player position!\n");
          done = 1;
        }
      } else
        done = 1;
    }
  }

  mprintf(0, "Picked index for start position %d\n", num);

  return num;
}

// Called from a single player game to get rid of all multiplayer ships
void DeleteMultiplayerObjects() {
  for (int i = 0; i <= Highest_object_index; i++) {
    if (Objects[i].type == OBJ_PLAYER && Objects[i].id != Player_num)
      ObjDelete(i);
  }
}

// Stops all sounds for a player
void PlayerStopSounds(int slot) {
  if (Players[slot].afterburner_sound_handle != -1) {
    Sound_system.StopSoundImmediate(Players[slot].afterburner_sound_handle);
    Players[slot].afterburner_sound_handle = -1;
  }

  if (Players[slot].thruster_sound_handle != -1) {
    Sound_system.StopSoundImmediate(Players[slot].thruster_sound_handle);
    Players[slot].thruster_sound_handle = -1;
  }
}

// Called when a player is entering the game for the first time
void InitPlayerNewGame(int slot) {
  Players[slot].num_kills_total = 0;
  Players[slot].num_deaths_total = 0;
  Players[slot].score = 0;

  uint32_t bit = (0x01 << slot);
  Players_typing &= ~bit;
}

// Called when a player is entering a new level
void InitPlayerNewLevel(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);

  if (Player_num == slot && (!(Game_mode & GM_MULTI))) {
    // see if we should restore our shields (which were saved in the last call
    // to ResetPlayerObject.  Only restore if shields are >INITIAL_SHIELDS
    if (Player_shields_saved_from_last_level > INITIAL_SHIELDS)
      Objects[Players[slot].objnum].shields = Player_shields_saved_from_last_level;
    if (Player_energy_saved_from_last_level > INITIAL_ENERGY)
      Players[slot].energy = Player_energy_saved_from_last_level;

    // set this to -1 to prevent any unneeded madness
    Player_shields_saved_from_last_level = -1.0f;
    Player_energy_saved_from_last_level = -1.0f;
  }

  Players[slot].num_kills_level = 0;
  Players[slot].friendly_kills_level = 0;
  Players[slot].num_hits_level = 0;
  Players[slot].num_discharges_level = 0;
  Players[slot].num_markers = 0;
  Players[slot].inventory.Reset(true, (Game_mode & GM_MULTI) ? INVRESET_ALL : INVRESET_LEVELCHANGE);
  Players[slot].counter_measures.Reset(true, (Game_mode & GM_MULTI) ? INVRESET_ALL : INVRESET_LEVELCHANGE);
  Players[slot].keys = 0;
  Players[slot].num_deaths_level = 0;

  if (Game_mode & GM_MULTI)
    NetPlayers[slot].packet_time = 0;

  if (slot == Player_num)
    Player_camera_objnum = -1;

  // Turn off rear view
  Players[slot].flags &= ~PLAYER_FLAGS_REARVIEW;

  // Kill autowaypoint
  Players[slot].current_auto_waypoint_room = -1;

  // Restore Quad Lasers if they are still in inventory
  static int quad_laser_id = -2;
  if (quad_laser_id == -2)
    quad_laser_id = FindObjectIDName("QuadLaser");
  if (quad_laser_id != -1) {
    if (Players[slot].inventory.CheckItem(OBJ_POWERUP, quad_laser_id)) {
      object *pobj = &Objects[Players[slot].objnum];
      pobj->dynamic_wb[LASER_INDEX].flags |= DWBF_QUAD;
      pobj->dynamic_wb[SUPER_LASER_INDEX].flags |= DWBF_QUAD;
    }
  }

  uint32_t bit = (0x01 << slot);
  Players_typing &= ~bit;

  // Give the player a GuideBot if he doesn't have one and if the GB isn't out there
  if ((!(Game_mode & GM_MULTI)) && (Demo_flags != DF_PLAYBACK)) {
    if ((!Players[slot].inventory.CheckItem(OBJ_ROBOT, ROBOT_GUIDEBOT)) &&
        (ObjGet(Buddy_handle[slot])->type != OBJ_ROBOT))
      Players[slot].inventory.Add(OBJ_ROBOT, ROBOT_GUIDEBOT);
  }

  // Limit the player's ammo to what the current ship can hold
  player *player = &Players[slot];
  ship *ship = &Ships[player->ship_index];
  for (int i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    if ((i >= SECONDARY_INDEX) || ship->static_wb[i].ammo_usage)
      player->weapon_ammo[i] = std::min<float>(ship->max_ammo[i], player->weapon_ammo[i]);
  }

#ifdef E3_DEMO
  extern float E3_TIME_LIMIT;

  MakePlayerInvulnerable(slot, E3_TIME_LIMIT * 2);
  //@@	Players[slot].energy=200.0f;
  //@@	Players[slot].weapon_flags=HAS_FLAG(LASER_INDEX)+HAS_FLAG(PLASMA_INDEX)+HAS_FLAG(VAUSS_INDEX)
  //@@ +HAS_FLAG(MICROWAVE_INDEX);
  //@@	Players[slot].weapon_flags+= HAS_FLAG(GUIDED_INDEX)+HAS_FLAG(NAPALMROCKET_INDEX)+HAS_FLAG(CYCLONE_INDEX);
  //@@
  //@@	for (int i=0;i<MAX_PLAYER_WEAPONS;i++)
  //@@		Players[slot].weapon_ammo[i] = 1000;

#endif
}

// Resets all the properties a player ship to the default values
// Pass into inven_reset what you want passed to Inventory.Reset()
void InitPlayerNewShip(int slot, int inven_reset) {
  int i;

  ASSERT(slot >= 0 && slot < MAX_PLAYERS);

  Players[slot].energy = INITIAL_ENERGY;
  Players[slot].num_balls = 0;
  Players[slot].laser_level = 0;
  Players[slot].killer_objnum = -1;
  Players[slot].light_dist = 0;
  Players[slot].oldroom = -1;
  Players[slot].guided_obj = NULL;
  Players[slot].user_timeout_obj = NULL;
  Players[slot].afterburn_time_left = AFTERBURN_TIME;
  Players[slot].last_thrust_time = 0;
  Players[slot].last_afterburner_time = 0;

  //	start out with basic weapons
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++)
    Players[slot].weapon_ammo[i] = 0;

  Players[slot].weapon_flags = HAS_FLAG(LASER_INDEX);
  Players[slot].weapon_flags += HAS_FLAG(CONCUSSION_INDEX);
  Players[slot].weapon_flags += HAS_FLAG(FLARE_INDEX);
  Players[slot].weapon_ammo[CONCUSSION_INDEX] = 2 + MAX_DIFFICULTY_LEVELS - Difficulty_level;

  Players[slot].weapon[PW_PRIMARY].index = LASER_INDEX;
  Players[slot].weapon[PW_PRIMARY].firing_time = 0;
  Players[slot].weapon[PW_PRIMARY].sound_handle = -1;

  Players[slot].weapon[PW_SECONDARY].index = CONCUSSION_INDEX;
  Players[slot].weapon[PW_SECONDARY].firing_time = 0;
  Players[slot].weapon[PW_SECONDARY].sound_handle = -1;

  Players[slot].small_left_obj = -1;
  Players[slot].small_right_obj = -1;
  Players[slot].small_dll_obj = -1;

  //	some other stuff
  Players[slot].flags = 0;

  Players[slot].invulnerable_time = 0;

  Players[slot].damage_magnitude = 0;
  Players[slot].edrain_magnitude = 0;

  if (Players[slot].objnum >= 0 && Players[slot].objnum <= Highest_object_index &&
      Objects[Players[slot].objnum].type != OBJ_NONE)
    Objects[Players[slot].objnum].weapon_fire_flags = 0;

  // reset the inventory
  Players[slot].inventory.Reset(true, inven_reset);
  Players[slot].counter_measures.Reset(true, inven_reset);

  Players[slot].last_homing_warning_sound_time = 0.0f;
  Players[slot].last_hit_wall_sound_time = 0.0f;
  Players[slot].multiplayer_flags = 0;
  Players[slot].last_multiplayer_flags = 0;
  Players[slot].afterburner_mag = 0;
  Players[slot].thrust_mag = 0;
  Players[slot].last_guided_time = 0;
  Players[slot].afterburner_sound_handle = -1;

  Players[slot].thruster_sound_state = 0;
  Players[slot].thruster_sound_handle = -1;

  Players[slot].movement_scalar = 1;
  Players[slot].armor_scalar = 1;
  Players[slot].damage_scalar = 1;
  Players[slot].turn_scalar = 1;
  Players[slot].weapon_recharge_scalar = 1;
  Players[slot].weapon_speed_scalar = 1;
  // Enable all controller input
  Players[slot].controller_bitflags = 0xffffffff;

  ResetWeaponSelectStates(); // reset storage of current weapon class selected per slot.
  ResetReticle();

  // add his guidebot (if it is a guidebot game)
  // this is here in case DMFC calls this function (which would remove the guidebot)
  if (GetGameState() == GAMESTATE_LVLPLAYING && Game_mode & GM_MULTI && Netgame.local_role == LR_SERVER &&
      Netgame.flags & NF_ALLOWGUIDEBOT) {
    if ((!Players[slot].inventory.CheckItem(OBJ_ROBOT, ROBOT_GUIDEBOT)) &&
        (ObjGet(Buddy_handle[slot])->type != OBJ_ROBOT))
      Players[slot].inventory.Add(OBJ_ROBOT, ROBOT_GUIDEBOT);
  }
}

// Gives the named player an afterburner
void PlayerGiveAfterburner(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  Players[slot].flags |= PLAYER_FLAGS_AFTERBURNER;
}

//	makes the player invulnerable
void MakePlayerInvulnerable(int slot, float time, bool play_sound_and_message) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  Players[slot].flags |= PLAYER_FLAGS_INVULNERABLE;
  Players[slot].invulnerable_time = time;

  if (play_sound_and_message) {
    Players[slot].flags |= PLAYER_FLAGS_PLAYSOUNDMSGFORINVULN;
    static int inv_sound_on_id = -2;
    if (inv_sound_on_id == -2)
      inv_sound_on_id = FindSoundName("Invulnerability on");

    if (inv_sound_on_id != -1)
      Sound_system.Play3dSound(inv_sound_on_id, &Objects[Players[slot].objnum], MAX_GAME_VOLUME / 2);

    if (slot == Player_num) {
      AddHUDMessage(TXT_INVULNON);
    }
  }
}

//	makes the player invulnerable
void MakePlayerVulnerable(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  //	Play sound maybe.
  Players[slot].flags &= ~PLAYER_FLAGS_INVULNERABLE;
  Players[slot].invulnerable_time = 0.0f;

  if (Players[slot].flags & PLAYER_FLAGS_PLAYSOUNDMSGFORINVULN) {
    static int inv_sound_off_id = -1;
    if (inv_sound_off_id == -1)
      inv_sound_off_id = FindSoundName("Invulnerability off");

    if (inv_sound_off_id != -1)
      Sound_system.Play3dSound(inv_sound_off_id, &Objects[Players[slot].objnum], MAX_GAME_VOLUME / 2);

    if (slot == Player_num) {
      AddHUDMessage(TXT_INVULNOFF);
    }
  }
}

//	Performs the player death sequence.

//	Here list prototypes of all player automatic functions
void DoNewPlayerDeathFrame(int slot);

// Does sampling of player position plus sets the camera positon

void UpdatePlayerCameraPosition() {
  object *playerobj = &Objects[Players[Player_num].objnum];
  vector dest_pos;
  matrix dest_mat;
  int dest_room;
  int total_increments = 0;

  // Increment our timers
  Player_camera_last_sample_time += Frametime;
  Player_camera_last_follow_time += Frametime;

  ASSERT(Player_camera_last_sample_time >= 0);
  ASSERT(Player_camera_last_follow_time >= 0);

  while (Player_camera_last_sample_time >= CAMERA_SAMPLE_INCREMENT) {
    Player_camera_last_sample_time -= CAMERA_SAMPLE_INCREMENT;
    total_increments++;
  }

  if (total_increments > 0) {
    vector delta_vec = playerobj->pos - Camera_sample_vectors[Camera_sample_index];

    vector delta_r = playerobj->orient.rvec - Camera_sample_matrix[Camera_sample_index].rvec;
    vector delta_u = playerobj->orient.uvec - Camera_sample_matrix[Camera_sample_index].uvec;
    vector delta_f = playerobj->orient.fvec - Camera_sample_matrix[Camera_sample_index].fvec;

    delta_vec /= total_increments;
    delta_r /= total_increments;
    delta_u /= total_increments;
    delta_f /= total_increments;

    vector current_pos = Camera_sample_vectors[Camera_sample_index];
    vector current_r = Camera_sample_matrix[Camera_sample_index].rvec;
    vector current_u = Camera_sample_matrix[Camera_sample_index].uvec;
    vector current_f = Camera_sample_matrix[Camera_sample_index].fvec;

    int current_room = Camera_sample_rooms[Camera_sample_index];

    for (int i = 0; i < total_increments; i++) {
      Camera_sample_vectors[Camera_sample_index] = current_pos;

      if (i < (total_increments / 2))
        Camera_sample_rooms[Camera_sample_index] = current_room;
      else
        Camera_sample_rooms[Camera_sample_index] = playerobj->roomnum;

      Camera_sample_matrix[Camera_sample_index].rvec = current_r;
      Camera_sample_matrix[Camera_sample_index].uvec = current_u;
      Camera_sample_matrix[Camera_sample_index].fvec = current_f;

      Camera_sample_index++;

      if (Camera_sample_index == MAX_CAMERA_SAMPLES)
        Camera_sample_index = 0;

      current_pos += delta_vec;
      current_r += delta_r;
      current_u += delta_u;
      current_f += delta_f;
    }

    Camera_sample_vectors[Camera_sample_index] = current_pos;
    Camera_sample_rooms[Camera_sample_index] = playerobj->roomnum;
    Camera_sample_matrix[Camera_sample_index] = playerobj->orient;
  }

  while (Player_camera_last_follow_time >= CAMERA_SAMPLE_INCREMENT) {
    Camera_follow_index++;

    if (Camera_follow_index == MAX_CAMERA_SAMPLES)
      Camera_follow_index = 0;

    Player_camera_last_follow_time -= CAMERA_SAMPLE_INCREMENT;
  }

  // Get normalize position of the following camera
  int follow_start = Camera_follow_index;
  int follow_end = (Camera_follow_index + 1) % MAX_CAMERA_SAMPLES;

  float follow_norm = Player_camera_last_follow_time / CAMERA_SAMPLE_INCREMENT;

  ASSERT(follow_norm >= 0 && follow_norm <= 1);

  // Set position
  dest_pos =
      ((1.0 - follow_norm) * Camera_sample_vectors[follow_start]) + (follow_norm * Camera_sample_vectors[follow_end]);

  // Set room
  if (follow_norm > .5)
    dest_room = Camera_sample_rooms[follow_start];
  else
    dest_room = Camera_sample_rooms[follow_end];

  // Set orientation matrix
  dest_mat.rvec = ((1.0 - follow_norm) * Camera_sample_matrix[follow_start].rvec) +
                  ((follow_norm)*Camera_sample_matrix[follow_end].rvec);
  dest_mat.uvec = ((1.0 - follow_norm) * Camera_sample_matrix[follow_start].uvec) +
                  ((follow_norm)*Camera_sample_matrix[follow_end].uvec);
  dest_mat.fvec = ((1.0 - follow_norm) * Camera_sample_matrix[follow_start].fvec) +
                  ((follow_norm)*Camera_sample_matrix[follow_end].fvec);

  // Set camera position
  fvi_info hit_data;
  fvi_query fq;
  vector new_pos = dest_pos;
  new_pos -= dest_mat.fvec * (playerobj->size * 3);
  new_pos += dest_mat.uvec * (playerobj->size / 2);

  fq.p1 = &new_pos;
  fq.p0 = &dest_pos;
  fq.startroom = dest_room;
  fq.rad = .5;
  fq.thisobjnum = OBJNUM(playerobj);
  fq.ignore_obj_list = NULL;
  fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
  fvi_FindIntersection(&fq, &hit_data);

  ObjSetPos(&Objects[Player_camera_objnum], &hit_data.hit_pnt, hit_data.hit_room, &dest_mat, false);
}

// Creates or destroys a player camera depending on what the situation calls for
void SetupPlayerCamera() {
  object *playerobj = &Objects[Players[Player_num].objnum];

  if (Player_has_camera) {
    if (Player_camera_objnum == -1) {
      // We have to create a new camera
      int objnum = ObjCreate(OBJ_CAMERA, 0, playerobj->roomnum, &playerobj->pos, &playerobj->orient);
      if (objnum < 0) {
        // Couldn't create a camera for some reason
        Player_has_camera = false;
        Player_camera_objnum = 0;
        return;
      } else {
        Player_camera_objnum = objnum;
        Camera_sample_index = MAX_CAMERA_SUB_SAMPLES;
        Player_camera_last_sample_time = 0;
        Player_camera_last_follow_time = 0;
        Camera_follow_index = 0;

        for (int i = 0; i < MAX_CAMERA_SAMPLES; i++) {
          Camera_sample_matrix[i] = playerobj->orient;
          Camera_sample_vectors[i] = playerobj->pos;
          Camera_sample_rooms[i] = playerobj->roomnum;
        }
      }
    }

    if (Viewer_object == playerobj) {
      // Set viewer to be camera
      Viewer_object = &Objects[Player_camera_objnum];
    }

    UpdatePlayerCameraPosition();
  } else {
    if (Player_camera_objnum != -1) {
      SetObjectDeadFlag(&Objects[Player_camera_objnum]);
      Player_camera_objnum = -1;
    }
  }
}

// Does actions for the given player slot
void DoPlayerFrameForOne(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  object *obj = &Objects[Players[slot].objnum];
  static int napalm_id = -1;

  Players[slot].time_level = Gametime;

  if (napalm_id == -1) {
    napalm_id = FindWeaponName("Napalm");
  }

  // If piggy backing observer, then set position relative to observed object
  if (obj->type == OBJ_OBSERVER && Players[slot].piggy_objnum != -1) {
    object *observed = &Objects[Players[slot].piggy_objnum];
    ObjSetPos(obj, &observed->pos, observed->roomnum, &observed->orient, false);

    obj->mtype.phys_info = observed->mtype.phys_info;
  }

  if (obj->type == OBJ_PLAYER || obj->type == OBJ_OBSERVER && obj->id == Player_num) {
    // Do camera stuff if needed
    SetupPlayerCamera();
  }

  if (Demo_flags != DF_PLAYBACK) {
    if ((Players[slot].flags & PLAYER_FLAGS_DYING) || (Players[slot].flags & PLAYER_FLAGS_DEAD))
      DoNewPlayerDeathFrame(slot);
  }

  //	do invulnerable stuff
  if (Players[slot].flags & PLAYER_FLAGS_INVULNERABLE) {
    Players[slot].invulnerable_time -= Frametime;
    if (Players[slot].invulnerable_time <= 0.0f) {
      //	deinvulnerablize the player!!
      MakePlayerVulnerable(slot);
    }
  }

  // Do terrain damage stuff
  if (Terrain_sky.damage_per_second > 0 && !(Players[slot].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
    if (OBJECT_OUTSIDE(obj)) {
      float scalar = GetTerrainDynamicScalar(&obj->pos, CELLNUM(obj->roomnum));

      // White out the screen
      if (scalar > 0 && slot == Player_num) {
        float vals[4];

        vals[0] = 1.0;
        vals[1] = 1.0;
        vals[2] = .8f;
        vals[3] = scalar / 4;

        CreateNewEvent(RENDER_EVENT, 0, 0, &vals, sizeof(float) * 4, DrawAlphaEvent);
      }

      if (scalar > .7) {
        SetNapalmDamageEffect(obj, NULL, napalm_id);
        obj->effect_info->damage_time = 1;
        obj->effect_info->damage_per_second = 2;
      }
    }
  }

  Players[slot].invul_magnitude -= (Frametime * 2);

  // Drop the red effect of the console player faster than other players
  float alpha_blend_scalar_time = 1.0;
  if (slot == Player_num)
    alpha_blend_scalar_time = 2.0;

  Players[slot].damage_magnitude -= (Frametime * (MAX_DAMAGE_MAG)*alpha_blend_scalar_time);
  Players[slot].edrain_magnitude -= (Frametime * (MAX_EDRAIN_MAG)*alpha_blend_scalar_time);

  if (Players[slot].invul_magnitude < 0)
    Players[slot].invul_magnitude = 0;

  if (Players[slot].damage_magnitude < 0)
    Players[slot].damage_magnitude = 0;
  if (Players[slot].edrain_magnitude < 0)
    Players[slot].edrain_magnitude = 0;

  if ((obj->weapon_fire_flags & WFF_SPRAY) && !(Players[slot].flags & PLAYER_FLAGS_DEAD)) {
    int ship_index = Players[slot].ship_index;
    int wb_index = Players[slot].weapon[PW_PRIMARY].index;
    DoSprayEffect(&Objects[Players[slot].objnum], &Ships[ship_index].static_wb[wb_index], wb_index);
  }

  // Do On/Off weapons for multiplayer
  if (slot != Player_num && (obj->weapon_fire_flags & WFF_ON_OFF) && !(Players[slot].flags & PLAYER_FLAGS_DEAD)) {
    FireOnOffWeapon(&Objects[Players[slot].objnum]);
  }

  // Do thrust stuff here
  if (Player_num == slot && Game_toggles.ship_noises == false) {
    if (Players[slot].thruster_sound_handle > -1) {
      Sound_system.StopSoundImmediate(Players[slot].thruster_sound_handle);
      Players[slot].thruster_sound_handle = -1;
    }
  }

  if (Players[slot].flags & PLAYER_FLAGS_THRUSTED) {
    Players[slot].thrust_mag += (Frametime * 2);
    if (Players[slot].thrust_mag > 1)
      Players[slot].thrust_mag = 1;

    // Play thrust sound
    if (slot == Player_num) {
      if (Players[slot].thruster_sound_state == 0) {
        if (Players[slot].thruster_sound_handle != -1) {
          Sound_system.StopSoundImmediate(Players[slot].thruster_sound_handle);
          Players[slot].thruster_sound_handle = -1;
        }
        if (Players[slot].thruster_sound_handle == -1) {
          if (Game_toggles.ship_noises) {
            Players[slot].thruster_sound_handle = Sound_system.Play3dSound(SOUND_SHIP_FORWARD_THRUST, obj);
          }
        }

        Players[slot].thruster_sound_state = 1;
      }
    }
  } else {
    // Cool down thrust
    Players[slot].thrust_mag -= (Frametime * 2);
    if (Players[slot].thrust_mag < 0)
      Players[slot].thrust_mag = 0;

    // Stop thrust sound
    if (slot == Player_num) {
      if (Players[slot].thruster_sound_state == 1) {
        if (Players[slot].thruster_sound_handle != -1) {
          Sound_system.StopSoundImmediate(Players[slot].thruster_sound_handle);
        }

        Players[slot].thruster_sound_handle = -1;

        if (Game_toggles.ship_noises) {
          Sound_system.Play3dSound(SOUND_SHIP_FORWARD_RELEASE, obj);
        }
      }

      if (Players[slot].thruster_sound_handle == -1) {
        if (Game_toggles.ship_noises) {
          Players[slot].thruster_sound_handle = Sound_system.Play3dSound(SOUND_SHIP_IDLE, obj);
        }
      }
      Players[slot].thruster_sound_state = 0;
    }
  }

  // Do afterburner stuff
  if ((Players[slot].flags & PLAYER_FLAGS_AFTERBURN_ON) &&
      !(Players[slot].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
    if (Players[slot].afterburner_sound_handle == -1) {
      // turn on the afterburner!
      Players[slot].afterburner_sound_handle = Sound_system.Play3dSound(SOUND_AFTERBURNER, obj);
    }

    Players[slot].afterburner_mag += (Frametime * 2);
    if (Players[slot].afterburner_mag > 1)
      Players[slot].afterburner_mag = 1;
  } else {
    // Cool down afterburner
    Players[slot].afterburner_mag -= (Frametime * 2);
    if (Players[slot].afterburner_mag < 0)
      Players[slot].afterburner_mag = 0;

    if (Players[slot].afterburner_sound_handle != -1) {
      Sound_system.StopSoundImmediate(Players[slot].afterburner_sound_handle);
      Players[slot].afterburner_sound_handle = -1;
      Sound_system.Play3dSound(SOUND_AFTERBURNER_TAIL, obj);
    }
  }
}

//	Do player automatic frame (all player automatic actions)
// Does all player, single or multiplayer games
void DoPlayerFrame() {
  if (Demo_flags == DF_PLAYBACK) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if (Objects[Players[i].objnum].id != i)
        continue;
      if (Objects[Players[i].objnum].type == OBJ_GHOST)
        continue;

      DoPlayerFrameForOne(i);
    }

  } else if (Game_mode & GM_MULTI) {
    for (int i = 0; i < MAX_NET_PLAYERS; i++) {
      if (!(NetPlayers[i].flags & NPF_CONNECTED))
        continue;

      DoPlayerFrameForOne(i);
    }

  } else {
    DoPlayerFrameForOne(Player_num);
  }
}

//	This function performs the death roll for a player.
#define MIN_DEATHCAM_DIST 40.0f
#define MEDIAN_DEATHCAM_DIST 80.0f
#define MAX_DEATHCAM_DIST 150.0f

#define DEATH_PHYS_INTERVAL 0.10f
#define DEATH_FATE_INTERVAL 0.50f

#define MAX_EXPLOSION_MAG 40.0f
#define MAX_ROLL_TIME 2.5
#define DEATH_COCKPIT_TIME 0.0f

#define DEATH_INSTANT 0
#define DEATH_FALL 1
#define DEATH_BREAKUP 2
#define DEATH_D2STYLE 3

#define DEATH_EXPLODE_THRESHOLD 100.0f
#define DEATH_BREAKUP_THRESHOLD 40.0f

struct tDeathSeq {
  object *camera;
  object *oldviewer;

  poly_model *dying_model;

  int16_t fate;
  int16_t breakup_count;
  float initial_death_time;
  float time_dying;
  float max_time_dying;
  float physics_frametime;
  float fate_frametime;

  float damage;
  float accel_mod;
  vector force_dir;

  uint8_t saved_ctrl_type;
  uint32_t saved_phys_flags;
  float saved_drag;
  vector saved_rotthrust;

  tHUDMode saved_cockpit;
  int saved_player_modelnum;
  bool in_cockpit;

  tDeathSeq() { camera = NULL; };

};

static tDeathSeq Death[MAX_NET_PLAYERS];

void debug_deathtype(int slot, int damage) {
  if (Death[slot].fate == DEATH_INSTANT)
    mprintf(0, "INSTANT DEATH ");
  else if (Death[slot].fate == DEATH_FALL)
    mprintf(0, "FALLING DEATH ");
  else if (Death[slot].fate == DEATH_BREAKUP)
    mprintf(0, "BREAKUP DEATH ");
  else
    mprintf(0, "UNKNOWN DEATH ");
}

float MoveDeathCam(int slot, vector *vec, float distance);
void PlayerShipExplode(object *obj, float magnitude);
void PlayerShipBreakup(object *obj, float magnitude);
void PlayerShipSpewPart(object *obj, int subobjnum, float magnitude);

void InitiatePlayerDeath(object *playerobj, bool melee, int fate) {
  if (!(Players[playerobj->id].flags & (PLAYER_FLAGS_DEAD + PLAYER_FLAGS_DYING))) {
    //	player is dying.  We don't want to make player dead yet.
    Players[playerobj->id].flags |= PLAYER_FLAGS_DYING;

    // Take care of stuff that should happen when you die
    ClearPlayerFiring(playerobj, PW_PRIMARY);
    ClearPlayerFiring(playerobj, PW_SECONDARY);

    // Start the death sequence
    StartPlayerDeath(playerobj->id, -playerobj->shields, melee, fate);
  }
}

// Chooses the style of death a player is going to use
int PlayerChooseDeathFate(int slot, float damage, bool melee) {
  int fate;
  bool is_moving;
  object *playerobj = &Objects[Players[slot].objnum];

  ASSERT(slot >= 0 && slot < MAX_PLAYERS);

  if (vm_GetMagnitude(&playerobj->mtype.phys_info.velocity))
    is_moving = true;
  else
    is_moving = false;

  fate = (damage <= DEATH_BREAKUP_THRESHOLD && is_moving && !melee && OBJECT_OUTSIDE(playerobj)) ? DEATH_BREAKUP
         : (damage <= DEATH_EXPLODE_THRESHOLD || melee)                                          ? DEATH_FALL
                                                                                                 : DEATH_INSTANT;

  if (fate == DEATH_BREAKUP) {
    if ((ps_rand() % 4) < 2)
      fate = DEATH_D2STYLE;
  } else if (fate == DEATH_FALL) {
    if ((ps_rand() % 4) != 3)
      fate = DEATH_D2STYLE;
  }

  //	split ship into subobjects.   they should still be one object but now with several parts.
  if (playerobj->rtype.pobj_info.dying_model_num == -1) {
    if (fate == DEATH_BREAKUP) {
      fate = DEATH_FALL;
    }
  }

  return fate;
}

///////////////////////////////////////////////////////////////////////////////
//	Starts player death sequence.

void StartPlayerDeath(int slot, float damage, bool melee, int fate) {
  int objnum;
  object *playerobj = &Objects[Players[slot].objnum];
  int killer_num = Players[playerobj->id].killer_objnum;
  object *killer;

  ASSERT(slot >= 0 && slot < MAX_PLAYERS);

  Players[playerobj->id].num_deaths_level++;
  Players[playerobj->id].num_deaths_total++;
  // Do killer object stuff
  if (killer_num < 0 || killer_num > MAX_OBJECTS)
    killer = NULL;
  else {
    killer = &Objects[killer_num];
    if (killer->type == OBJ_NONE)
      killer = NULL;
  }

  //	determine current state of player object.
  //	create death camera if it doesn't exit
  if (slot == Player_num) {
    objnum = ObjCreate(OBJ_CAMERA, 0, playerobj->roomnum, &playerobj->pos, &playerobj->orient);
    if (objnum == -1) {
      mprintf(0, "Failed to create death cam.\n");
      Int3();
    } else {
      Death[slot].camera = &Objects[objnum];
      if (Objects[objnum].type == OBJ_NONE)
        Int3(); // Samir- This really shouldn't happen.  will cause assertion
    }

    Death[slot].oldviewer = Viewer_object;

    //	set screen mode
    if (Cinematic_inuse) {
      Death[slot].saved_cockpit = Cinematic_GetOldHudMode();
    } else {
      Death[slot].saved_cockpit = GetHUDMode();
    }

    Death[slot].in_cockpit = true;
  }

  //	save player ship information that will be changed here.
  Death[slot].saved_ctrl_type = playerobj->control_type;
  Death[slot].saved_phys_flags = playerobj->mtype.phys_info.flags;
  Death[slot].saved_drag = playerobj->mtype.phys_info.drag;
  Death[slot].saved_player_modelnum = playerobj->rtype.pobj_info.model_num;
  Death[slot].saved_rotthrust = playerobj->mtype.phys_info.rotthrust;
  Death[slot].breakup_count = 0;

  if (killer == NULL) // If the killer isn't valid, just use the reverse forward direction
    Death[slot].force_dir = -playerobj->orient.fvec;
  else
    Death[slot].force_dir = playerobj->pos - killer->pos;

  vm_NormalizeVector(&Death[slot].force_dir);
  Death[slot].force_dir = Death[slot].force_dir * playerobj->orient;

  //	determine fate of player ship
  if (fate == -1)
    Death[slot].fate = PlayerChooseDeathFate(slot, damage, melee);
  else
    Death[slot].fate = fate;

  //	split ship into subobjects.   they should still be one object but now with several parts.
  if (playerobj->rtype.pobj_info.dying_model_num != -1) {
    playerobj->rtype.pobj_info.model_num = playerobj->rtype.pobj_info.dying_model_num;
    Death[slot].dying_model = GetPolymodelPointer(playerobj->rtype.pobj_info.model_num);
    playerobj->rtype.pobj_info.subobj_flags = 0xffffffff;
    //		playerobj->rtype.pobj_info.subobj_flags = ~(0xffffffff << (Death[slot].dying_model->n_models));
    //		mprintf(0, "initflags=%08x\n", playerobj->rtype.pobj_info.subobj_flags);
  } else {
    // This ship has no dying model so dont break up
    if (Death[slot].fate == DEATH_BREAKUP)
      Int3(); // Get Jason - a death was chosen that this ship doesn't support

    Death[slot].dying_model = GetPolymodelPointer(playerobj->rtype.pobj_info.model_num);
    playerobj->rtype.pobj_info.subobj_flags = 0xffffffff;
  }

  //	determine physics properties of death
  SetObjectControlType(playerobj, CT_NONE);
  float rotate_adj = 0.0f;

  if (Death[slot].fate == DEATH_BREAKUP) {
    //	a breakup typically means the ship starts to fall apart.
    Death[slot].accel_mod = 1.0f;
    playerobj->mtype.phys_info.flags = (PF_FIXED_ROT_VELOCITY);
    playerobj->mtype.phys_info.drag = .005f;
    playerobj->mtype.phys_info.mass = 3000.0f;
    playerobj->mtype.phys_info.coeff_restitution = 0.3f;
    rotate_adj = 32768.0f;
  } else if (Death[slot].fate == DEATH_D2STYLE) {
    Death[slot].accel_mod = 0.960f;
    playerobj->mtype.phys_info.drag = 50.0;
    playerobj->mtype.phys_info.mass = 3000.0f;
    playerobj->mtype.phys_info.flags = PF_FIXED_ROT_VELOCITY;
    playerobj->mtype.phys_info.coeff_restitution = 0.3f;
    rotate_adj = 32768.0f;
  } else {
    //	if we're falling or dying immediately, let gravity take control of the ship while it
    //	deaccelerates.
    Death[slot].accel_mod = 0.960f;
    playerobj->mtype.phys_info.flags = PF_GRAVITY | PF_FIXED_ROT_VELOCITY;
    playerobj->mtype.phys_info.num_bounces = 0;
    playerobj->mtype.phys_info.coeff_restitution = .03f;
    playerobj->mtype.phys_info.mass = 2500.0f;
    playerobj->mtype.phys_info.drag = 50.0f;
    rotate_adj = 32768.0f;
  }

  playerobj->mtype.phys_info.rotvel.x = (float)((rotate_adj));
  playerobj->mtype.phys_info.rotvel.y = (float)((rotate_adj));
  playerobj->mtype.phys_info.rotvel.z = (float)((rotate_adj));

  //	set times and other stuff for dying.
  if (Death[slot].fate == DEATH_FALL)
    Death[slot].max_time_dying = 3.0f;
  else if (Death[slot].fate == DEATH_INSTANT)
    Death[slot].max_time_dying = 2.5f;
  else if (Death[slot].fate == DEATH_BREAKUP)
    Death[slot].max_time_dying = 4.0f;
  else if (Death[slot].fate == DEATH_D2STYLE)
    Death[slot].max_time_dying = 2.0f;

  Total_time_dead = 0;

  Death[slot].initial_death_time = Gametime;
  Death[slot].physics_frametime = Gametime;
  Death[slot].fate_frametime = Gametime;

#ifndef RELEASE
//	debug_deathtype(slot, damage);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//	The Death sequencer.

void DoNewPlayerDeathFrame(int slot) {
  object *playerobj;

  ASSERT(slot >= 0 && slot < MAX_PLAYERS);

  // Kevin added this in case the player dies and while dying stops recording a demo.
  // It's the cleanest solution I could find.
  if ((Player_num == slot) && (!Death[slot].camera))
    return;

  // if (Player_num==slot)
  //	ASSERT(Death[slot].camera);

  playerobj = &Objects[Players[slot].objnum];

  //	determine current state of player object.
  Death[slot].time_dying = Gametime - Death[slot].initial_death_time;

  // Increase death time
  if (slot == Player_num && (Players[slot].flags & PLAYER_FLAGS_DEAD)) {
    //	Total_time_dead+=Frametime;
    Total_time_dead = Death[slot].time_dying;
    if (Total_time_dead > DEATH_RESPAWN_TIME) {
      AddPersistentHUDMessage(GR_RGB(0, 255, 0), HUD_MSG_PERSISTENT_CENTER, Game_window_y + Game_window_h - 20,
                              HUD_MSG_PERSISTENT_INFINITE, 0, SOUND_NONE_INDEX, TXT_SPACETOCONT);
    }
  }

  //	depending on state of player ship, perform some operation
  if (Players[playerobj->id].flags & PLAYER_FLAGS_DYING) {
    //	modify player ship physics as needed.
    //	player ship will fall to the ground and deaccelerate
    //	modify physics properties every INTERVAL
    if ((Death[slot].physics_frametime + DEATH_PHYS_INTERVAL) > Gametime) {
      if (Death[slot].fate == DEATH_FALL) {
        playerobj->mtype.phys_info.rotvel.x /= 1.15f;
        playerobj->mtype.phys_info.rotvel.y /= 1.1f;
        playerobj->mtype.phys_info.rotvel.z /= 1.0f;
      } else if (Death[slot].fate == DEATH_D2STYLE) {
        playerobj->mtype.phys_info.rotvel.x /= 1.15f;
        playerobj->mtype.phys_info.rotvel.y /= 1.0f;
        playerobj->mtype.phys_info.rotvel.z /= 1.05f;
      } else {
        playerobj->mtype.phys_info.rotvel.x /= 1.10f;
        playerobj->mtype.phys_info.rotvel.y /= 1.05f;
        playerobj->mtype.phys_info.rotvel.z /= 1.0f;
      }

      playerobj->mtype.phys_info.velocity *= Death[slot].accel_mod;
      Death[slot].physics_frametime = Gametime;
    }

    //	move death camera if distance between death camera and player is less than a certain amount.
    if (slot == Player_num && Death[slot].in_cockpit) {
      if (Death[slot].time_dying > DEATH_COCKPIT_TIME) {
        Death[slot].in_cockpit = false;
        SetHUDMode(HUD_LETTERBOX);
        Viewer_object = Death[slot].camera; // set the current viewer to be this new camera.
      }
    } else if (slot == Player_num) {
      vector directional;
      float death_cam_dist = vm_VectorDistanceQuick(&Death[slot].camera->pos, &playerobj->pos);

      if (death_cam_dist < MIN_DEATHCAM_DIST) {
        vm_MakeRandomVector(&directional);
        MoveDeathCam(slot, &directional, MEDIAN_DEATHCAM_DIST);
      } else if (death_cam_dist > MAX_DEATHCAM_DIST) {
        vm_MakeRandomVector(&directional);
        MoveDeathCam(slot, &directional, MEDIAN_DEATHCAM_DIST);
      }

      //	check to see if the vector from death cam to player is obstructed by something.
      fvi_info hit_data;
      fvi_query fq;

      hit_data.hit_type[0] = (OBJECT_OUTSIDE(playerobj) ? HIT_TERRAIN : HIT_WALL);
      fq.p1 = &playerobj->pos;
      fq.p0 = &Death[slot].camera->pos;
      fq.startroom = Death[slot].camera->roomnum;
      fq.rad = .5;
      fq.thisobjnum = OBJNUM(Death[slot].camera);
      fq.ignore_obj_list = NULL;
      fq.flags = 0;
      fvi_FindIntersection(&fq, &hit_data);

      if (hit_data.hit_type[0] == HIT_WALL) {
        //	death camera's view is obstructed, move the death cam
        //	mprintf(0, "Death cam view obstructed, changing view...\n");
        vm_MakeRandomVector(&directional);
        MoveDeathCam(slot, &directional, MEDIAN_DEATHCAM_DIST);
      }

      //	orient death camera towards player ship
      directional = playerobj->pos - Death[slot].camera->pos;
      if (vm_GetMagnitudeFast(&directional) == 0.0f)
        directional.x += 1.0f;
      vm_VectorToMatrix(&Death[slot].camera->orient, &directional, NULL, NULL);
    }

    //	perform fate specific actions here
    if (Death[slot].time_dying >= Death[slot].max_time_dying) {
      PlayerShipExplode(playerobj, 40.0f);
      Players[playerobj->id].flags |= PLAYER_FLAGS_DEAD;
      Players[playerobj->id].flags &= ~PLAYER_FLAGS_DYING;
    }
    //	fate action occurs every fate interval.
    else if ((Death[slot].fate_frametime + DEATH_FATE_INTERVAL) > Gametime) {
      if (Death[slot].fate == DEATH_BREAKUP) {
        if (ps_rand() % 8) {
          //	break up a piece of the ship
          if (Death[slot].breakup_count == 2) {
            Death[slot].time_dying = Death[slot].max_time_dying;
          } else {
            PlayerShipBreakup(playerobj, 20.0f + (ps_rand() % 10));
            Death[slot].breakup_count++;
            //	mprintf(0, "Breakup!\n");
          }
        }
      }
      Death[slot].fate_frametime = Gametime;
    }

    //	do smoke trails and special visual effects.
    if ((ps_rand() % 6) == 0) {
      //	smoke
      int visnum;
      vector smoke_pt;
      smoke_pt = (-playerobj->orient.fvec) * (playerobj->size * 0.5f);
      smoke_pt = playerobj->pos + smoke_pt;
      visnum = CreateFireball(&smoke_pt, BLACK_SMOKE_INDEX, playerobj->roomnum, VISUAL_FIREBALL);
      if (visnum >= 0)
        VisEffects[visnum].size = 1.0 + ((ps_rand() % 3) / 3.0); // Make small!
    }

    // Create an explosion that follows every now and then
    if ((ps_rand() % 5) == 0) {

      vector dest;
      poly_model *pm = Death[slot].dying_model;
      bsp_info *sm = &pm->submodel[0];
      int vertnum = ps_rand() % sm->nverts;

      GetPolyModelPointInWorld(&dest, pm, &playerobj->pos, &playerobj->orient, 0, &sm->verts[vertnum]);
      int visnum = CreateFireball(&dest, GetRandomSmallExplosion(), playerobj->roomnum, VISUAL_FIREBALL);

      if (visnum >= 0) { // DAJ added to pervent -1 array index
        VisEffects[visnum].size += ((ps_rand() % 20) / 20.0) * 3.0;

        if ((ps_rand() % 2)) {
          VisEffects[visnum].movement_type = MT_PHYSICS;
          VisEffects[visnum].velocity = playerobj->mtype.phys_info.velocity;
          VisEffects[visnum].mass = playerobj->mtype.phys_info.mass;
          VisEffects[visnum].drag = playerobj->mtype.phys_info.drag;
        }
      }
    }
  }

  // mprintf(0,"Playerobj size=%f\n",playerobj->size);
}

#define TARGET_DEGREE (170 / 2)
#define FOV_CHANGE_TIME .7f

// Alters the field of view over a period of time
void DoFOVEvent(int eventnum, void *data) {
  float *val = (float *)data;
  float new_time = *val;
  float norm = new_time / FOV_CHANGE_TIME;

  new_time -= Frametime;

  if (new_time < 0) {
    Render_zoom = D3_DEFAULT_ZOOM;
  } else {

    float num = (Render_FOV / 2) + (norm * (TARGET_DEGREE - (Render_FOV / 2)));
    num = (3.14 * (float)num / 180.0);
    Render_zoom = tan(num);
    CreateNewEvent(OBJECT_EVENT, FOV_CHANGE_EVENT, 0, &new_time, sizeof(float), DoFOVEvent);
  }
}

//	forces an end to the player death sequence
void EndPlayerDeath(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  object *playerobj = &Objects[Players[slot].objnum];

  if (slot == Player_num) {
    if (Death[slot].camera) {
      ObjDelete(OBJNUM(Death[slot].camera));
      Death[slot].camera = NULL;
      Viewer_object = Death[slot].oldviewer;
    }
    SetHUDMode(Death[slot].saved_cockpit);
    ResetPersistentHUDMessage();
  }

  if (!(Players[playerobj->id].flags & PLAYER_FLAGS_DEAD))
    PlayerShipExplode(playerobj, 50.0f);

  // Stop sounds for this player
  PlayerStopSounds(slot);

  // Get rid of explosions, weapons etc. that are still alive
  if (!(Game_mode & GM_MULTI))
    ClearTransientObjects(0);

  // Reset the player object
  InitPlayerNewShip(slot, INVRESET_DEATHSPEW);
  ResetPlayerObject(slot);

  // Do the zoom-in effect and set him for invulernable in single player
  if (slot == Player_num) {
    float val = FOV_CHANGE_TIME;
    float *valp = &val;
    DoFOVEvent(-1, (void *)valp);

    if (!(Game_mode & GM_MULTI)) {
      MakePlayerInvulnerable(slot, 2.0);
    }
  }

  // call osiris level event
  tOSIRISEventInfo evt;
  evt.evt_player_respawn.it_handle = Objects[Players[slot].objnum].handle;
  Osiris_CallLevelEvent(EVT_PLAYER_RESPAWN, &evt);
}

void MovePlayerToWaypoint(object *objp);

void ResetPlayerObject(int slot, bool f_reset_pos) {
  //	Init physics
  object *playobj = &Objects[Players[slot].objnum];
  ship *ship = &Ships[Players[slot].ship_index];

  playobj->shields = INITIAL_SHIELDS;
  Players[slot].energy = INITIAL_ENERGY;
  playobj->mtype.phys_info = Ships[Players[slot].ship_index].phys_info;
  Objects[Players[slot].objnum].effect_info->type_flags = EF_VOLUME_LIT;

  if (playobj->effect_info->sound_handle != SOUND_NONE_INDEX) {
    Sound_system.StopSoundLooping(playobj->effect_info->sound_handle);
    playobj->effect_info->sound_handle = SOUND_NONE_INDEX;
  }

  if (f_reset_pos) {
    if ((Game_mode & GM_MULTI) && !(Netgame.flags & NF_RESPAWN_WAYPOINT)) {
      ObjSetPos(playobj, &Players[slot].start_pos, Players[slot].start_roomnum, &Players[slot].start_orient, false);
    } else {
      MovePlayerToWaypoint(playobj);
    }
  }

  playobj->render_type = RT_POLYOBJ;
  playobj->rtype.pobj_info.model_num = ship->model_handle;
  playobj->rtype.pobj_info.dying_model_num = ship->dying_model_handle;
  playobj->rtype.pobj_info.tmap_override = -1;
  playobj->rtype.pobj_info.subobj_flags = 0xFFFFFFFF;
  playobj->lighting_render_type = LRT_GOURAUD;
  playobj->lm_object.used = 0;
  playobj->flags = (OF_POLYGON_OBJECT | OF_DESTROYABLE);

  if (Demo_flags == DF_PLAYBACK) {
    playobj->flags |= OF_SERVER_OBJECT;
  }

  if (Game_mode & GM_MULTI) {
    if (Netgame.local_role == LR_CLIENT) {
      playobj->flags |= OF_SERVER_OBJECT;
    } else
      playobj->flags |= OF_CLIENT_KNOWS;
  }

  playobj->size = Poly_models[playobj->rtype.pobj_info.model_num].rad;

  vm_MakeZero(&playobj->mtype.phys_info.velocity);
  vm_MakeZero(&playobj->mtype.phys_info.thrust);
  vm_MakeZero(&playobj->mtype.phys_info.rotvel);
  vm_MakeZero(&playobj->mtype.phys_info.rotthrust);

  playobj->mtype.phys_info.turnroll = 0;

  if (slot == Player_num) {
    SetObjectControlType(playobj, CT_FLYING);
    playobj->movement_type = MT_PHYSICS;
  } else {
    SetObjectControlType(playobj, CT_NONE);
    playobj->movement_type = MT_PHYSICS;
    playobj->mtype.phys_info.flags = PF_FIXED_VELOCITY;
  }

  if (Game_mode & GM_MULTI) {
    MultiMakePlayerReal(slot);
    if (Netgame.flags & NF_PERMISSABLE)
      playobj->mtype.phys_info.flags &= ~PF_WIGGLE;
  }

  if (slot == Player_num) {
    Viewer_object = Player_object = playobj;
  }

  // Reset quad firing mask
  object *objp = &Objects[Players[slot].objnum];
  for (int weapon_battery = 0; weapon_battery < MAX_WBS_PER_OBJ; weapon_battery++) {
    objp->dynamic_wb[weapon_battery].flags &= ~DWBF_QUAD;
  }

  // Give the player a GuideBot if he doesn't have one and if the GB isn't out there
  if ((!(Game_mode & GM_MULTI)) && (Demo_flags != DF_PLAYBACK)) {
    // The first if is to prevent a tough demo playback bug where
    // the game would crash *after* the demo is done playing back.
    if (ObjGet(Buddy_handle[slot]))
      if ((!Players[slot].inventory.CheckItem(OBJ_ROBOT, ROBOT_GUIDEBOT)) &&
          (ObjGet(Buddy_handle[slot])->type != OBJ_ROBOT))
        Players[slot].inventory.Add(OBJ_ROBOT, ROBOT_GUIDEBOT);
  }

  // reinit the reticle
  ResetReticle();
}

// Resets a player's control type back to it's default setting
void ResetPlayerControlType(int slot) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);

  //	Init physics
  object *playobj = &Objects[Players[slot].objnum];
  ship *ship = &Ships[Players[slot].ship_index];

  playobj->mtype.phys_info = Ships[Players[slot].ship_index].phys_info;

  vm_MakeZero(&playobj->mtype.phys_info.velocity);
  vm_MakeZero(&playobj->mtype.phys_info.thrust);
  vm_MakeZero(&playobj->mtype.phys_info.rotvel);
  vm_MakeZero(&playobj->mtype.phys_info.rotthrust);

  playobj->mtype.phys_info.turnroll = 0;

  if (slot == Player_num) {
    SetObjectControlType(playobj, CT_FLYING);
    playobj->movement_type = MT_PHYSICS;
  } else {
    SetObjectControlType(playobj, CT_NONE);
    playobj->movement_type = MT_PHYSICS;
    playobj->mtype.phys_info.flags = PF_FIXED_VELOCITY;
  }
}

// Makes the player into an AI controlled physics object
void PlayerSetControlToAI(int slot, float velocity) {
  ASSERT(slot >= 0 && slot < MAX_PLAYERS);
  if (slot < 0 || slot >= MAX_PLAYERS)
    return;

  object *pobj = &Objects[Players[slot].objnum];

  // Turn off some player physics stuff
  pobj->mtype.phys_info.flags &= ~PF_USES_THRUST;
  pobj->mtype.phys_info.drag = .1f;
  pobj->mtype.phys_info.flags &= ~PF_LEVELING;

  // pobj->flags &= ~OF_DESTROYABLE;
  vm_MakeZero(&pobj->mtype.phys_info.thrust);
  vm_MakeZero(&pobj->mtype.phys_info.rotthrust);
  vm_MakeZero(&pobj->mtype.phys_info.rotvel);
  vm_MakeZero(&pobj->mtype.phys_info.velocity);

  // Put the player in AI mode
  SetObjectControlType(pobj, CT_AI);

  memset(pobj->ai_info, 0, sizeof(ai_frame));

  pobj->ai_info->ai_class = AIC_STATIC;
  pobj->ai_info->ai_type = AIT_AIS;

  GoalInitTypeGoals(pobj, AIT_AIS);

  pobj->ai_info->flags = AIF_PERSISTANT | AIF_DISABLE_FIRING | AIF_DISABLE_MELEE | AIF_ORIENT_TO_VEL;
  pobj->ai_info->max_velocity = velocity;
  pobj->ai_info->max_delta_velocity = 40.0f;
  pobj->ai_info->max_turn_rate = 14000;
  pobj->ai_info->awareness = AWARE_MOSTLY;
  pobj->ai_info->movement_type = MC_FLYING;
  pobj->ai_info->next_movement = AI_INVALID_INDEX;
  pobj->ai_info->anim_sound_handle = 0;
  pobj->ai_info->status_reg = 0;
  pobj->ai_info->last_played_sound_index = -1;
  pobj->ai_info->weapon_speed = 0.0f;
  pobj->ai_info->animation_type = AS_ALERT;
  pobj->ai_info->next_melee_time = Gametime;
  pobj->ai_info->next_flinch_time = Gametime;
  pobj->ai_info->target_handle = OBJECT_HANDLE_NONE;
  pobj->ai_info->next_check_see_target_time = Gametime;
  pobj->ai_info->last_see_target_time = Gametime;
  pobj->ai_info->last_render_time = -1.0f;
  pobj->ai_info->next_target_update_time = Gametime;
  pobj->ai_info->notify_flags |= AI_NOTIFIES_ALWAYS_ON;
  pobj->ai_info->last_see_target_pos = Zero_vector;
  pobj->ai_info->dodge_vel_percent = 1.0f;
  pobj->ai_info->attack_vel_percent = 1.0f;
  pobj->ai_info->fight_same = 0.0f;
  pobj->ai_info->agression = 0.0f;
  pobj->ai_info->avoid_friends_distance = 0.0f;
  pobj->ai_info->biased_flight_importance = 0.0f;
  pobj->ai_info->circle_distance = 10.0f;
  pobj->ai_info->dodge_percent = 0.0f;
  pobj->ai_info->fight_team = 0.0f;

  AIPathInitPath(&pobj->ai_info->path);
}

// Moves a player to a specified start position
void PlayerMoveToStartPos(int player_slot, int start_slot) {
  object *playobj = &Objects[Players[player_slot].objnum];

  if (start_slot >= 0) // Non autowaypoint
  {
    Players[player_slot].current_auto_waypoint_room = -1;
    ObjSetPos(playobj, &Players[start_slot].start_pos, Players[start_slot].start_roomnum,
              &Players[start_slot].start_orient, true);
  } else {
    // Do autowaypoint stuff
    int waypointnum = (-start_slot) + 1;
    Players[player_slot].current_auto_waypoint_room = waypointnum;
    MovePlayerToWaypoint(playobj);
  }
}

//	Force player to explode (this should be called to intercept the death sequencer's control of explosions
void StartPlayerExplosion(int slot) {
  Death[slot].max_time_dying = 0.0f;

  if (Death[slot].in_cockpit) {
    Death[slot].in_cockpit = false;
    SetHUDMode(HUD_LETTERBOX);
    Viewer_object = Death[slot].camera; // set the current viewer to be this new camera.
  }
}

//	Detaches a subobject from the player ship
void DeadPlayerShipHit(object *obj, int hit_room, vector *hitpt, float magnitude) {
  fvi_info hit_data;
  fvi_query fq;
  vector hitvec, hitpt2;
  int subobjnum = -1;

  //	vector from hitpoint to object center position
  hitvec = obj->pos - (*hitpt);
  hitpt2 = *hitpt;

  //	get first subobject to be hit when looking for a hit subobject.
  hit_data.hit_type[0] = HIT_SPHERE_2_POLY_OBJECT;

  while (hit_data.hit_type[0] != HIT_NONE) {
    fq.p0 = &hitpt2;
    fq.p1 = &obj->pos;
    fq.startroom = hit_room;
    fq.rad = obj->size;
    fq.thisobjnum = obj - Objects;
    fq.ignore_obj_list = NULL;
    fq.flags = FQ_CHECK_OBJS | FQ_OBJ_BACKFACE | FQ_ONLY_PLAYER_OBJ;

    fvi_FindIntersection(&fq, &hit_data);

    if (hit_data.hit_type[0] == HIT_SPHERE_2_POLY_OBJECT) {
      // we probably hit a subobject of the player object.
      //	NOTE: we should check if the hit object is still the player object!
      subobjnum = hit_data.hit_subobject[0];
    } else if (hit_data.hit_type[0] != HIT_NONE) {
      hitpt2 = hit_data.hit_pnt;
      hit_data.hit_type[0] = HIT_NONE;
    }
  }

  if (subobjnum > -1) {
    //	we hit a subobject.  new debris object, and delete this subobject from the player model.  note that
    //	we should must the suobject handle to the polymodel when we're done.
    PlayerShipSpewPart(obj, subobjnum, magnitude);
  }
}

// Spews a guidebot
void PlayerSpewGuidebot(object *parent, int type, int id) {
  int objnum;
  object *obj;
  int model_num = Object_info[ROBOT_GUIDEBOT].render_handle;
  float size;

  if (stricmp(Ships[Players[parent->id].ship_index].name, "Black Pyro") == 0) {
    // Only spew red GB if merc is installed
    extern bool MercInstalled();
    if (MercInstalled())
      model_num = Object_info[ROBOT_GUIDEBOTRED].render_handle;
  }

  PageInPolymodel(model_num, OBJ_ROBOT, &size);

  objnum = ObjCreate(OBJ_DEBRIS, 0, parent->roomnum, &parent->pos, &parent->orient);

  if (objnum < 0 || objnum > Highest_object_index) {
    mprintf(0, "WARNING: No object slots.  Dead GB not created!\n");
    return;
  }

  obj = &Objects[objnum];

  // Set polygon-object-specific data
  obj->rtype.pobj_info.model_num = model_num;
  obj->rtype.pobj_info.subobj_flags = 0xFFFFFFFF;

  // Set physics data for this object

  obj->mtype.phys_info.velocity = parent->mtype.phys_info.velocity + parent->orient.fvec * 30.0;

  vm_MakeZero(&obj->mtype.phys_info.rotthrust);

  obj->size = Object_info[ROBOT_GUIDEBOT].size;
  obj->mtype.phys_info.mass = 40.0;
  obj->mtype.phys_info.drag = .001f;

  obj->mtype.phys_info.flags = (PF_GRAVITY | PF_BOUNCE | PF_FIXED_ROT_VELOCITY);
  obj->mtype.phys_info.coeff_restitution = .25f;

  obj->mtype.phys_info.rotvel.x = (float)((120000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
  obj->mtype.phys_info.rotvel.y = (float)((120000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
  obj->mtype.phys_info.rotvel.z = (float)((120000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));

  obj->mtype.phys_info.num_bounces = 5;

  obj->movement_type = MT_PHYSICS;

  ASSERT(obj != Player_object);
  obj->type = OBJ_DEBRIS;
  SetObjectControlType(obj, CT_DEBRIS); // become debris while exploding
  obj->lifeleft = 5.0 + ((ps_rand() % 50) * .05);
  obj->flags |= OF_USES_LIFELEFT;
  DemoWriteObjLifeLeft(obj);
}

// Spews an object in a random direction
void PlayerSpewObject(object *objp, int timed, int room, vector *pos, matrix *orient) {
  ASSERT((!(Game_mode & GM_MULTI)) || (Netgame.local_role == LR_SERVER));

  ObjSetPos(objp, pos, room, orient, true);

  // Set random velocity for powerups
  objp->mtype.phys_info.velocity.x = ((ps_rand() / (float)D3_RAND_MAX) - .5f) * 40.0; // +20 to -20
  objp->mtype.phys_info.velocity.z = ((ps_rand() / (float)D3_RAND_MAX) - .5f) * 40.0; // +20 to -20
  objp->mtype.phys_info.velocity.y = ((ps_rand() / (float)D3_RAND_MAX) - .5f) * 40.0; // +20 to -20

  // Send object to other players
  if (Game_mode & GM_MULTI) {
    if (Netgame.flags & NF_COOP)
      timed = 0;

    if (Netgame.local_role == LR_SERVER) {
      if (timed == 2) {
        objp->flags |= OF_USES_LIFELEFT;
        objp->lifeleft = 20.0;
      } else if (timed == 1) {
        objp->flags |= OF_USES_LIFELEFT;
        objp->lifeleft = 180.0;
      }
      DemoWriteObjLifeLeft(objp);
    }
  }
}

// Spews an object in a random direction
// Returns the new object
int PlayerSpewObject(object *parent, int type, int id, int timed, void *sinfo) {
  if (id < 0) // Don't spew non-existant stuff
    return -1;

  ASSERT((parent->type == OBJ_PLAYER) || (parent->type == OBJ_GHOST));

  if (type == OBJ_POWERUP) {
    if (Game_mode & GM_MULTI) {
      if (Object_info[id].multi_allowed == 0)
        return -1;
    }
  }
  // A dead GB is spew'ed on player death (if he had one)
  if (type == OBJ_ROBOT && id == ROBOT_GUIDEBOT) {
    PlayerSpewGuidebot(parent, type, id);
    return -1;
  }

  int objnum = ObjCreate(type, id, parent->roomnum, &parent->pos, NULL, parent->handle);

  if (objnum < 0) {
    mprintf(0, "Couldn't spew object!\n");
    return -1;
  }

  object *obj = &Objects[objnum];

  PlayerSpewObject(obj, timed, parent->roomnum, &parent->pos, NULL);

  // Send object to other players
  if (Game_mode & GM_MULTI) {
    if (Netgame.local_role == LR_SERVER) {
      MultiSendObject(obj, 0);
    }
  }

  // Setup the script used for this object
  InitObjectScripts(obj);

  return objnum;
}

// TEMP: this should be in a header file
#define FIRST_SECONDARY_WEAPON MAX_PRIMARY_WEAPONS

// How many at most to spew of each secondary weapon
#define MAX_SECONDARY_SPEW 3

// This is a terrible hack -- it maps powerup to multi-pack versions
// This mapping should really be on the powerup page
const char *powerup_multipacks[] = {"Concussion", "4packConc",   "Frag",   "4packFrag",
                              "Guided",     "4packGuided", "Homing", "4packHoming"};
#define N_POWERUP_MULTIPACKS (sizeof(powerup_multipacks) / sizeof(*powerup_multipacks) / 2)

// Returns the index of the multipack version of the specified powerup, or -1 if none
int FindMultipackPowerup(int single_index) {
  for (int i = 0; i < N_POWERUP_MULTIPACKS; i++) {
    if (stricmp(Object_info[single_index].name, powerup_multipacks[i * 2]) == 0)
      return FindObjectIDName(powerup_multipacks[i * 2 + 1]);
  }

  return -1;
}

// Spews the inventory of the passed in player object
void PlayerSpewInventory(object *obj, bool spew_energy_and_shield, bool spew_nonspewable) {
  ASSERT(obj->type == OBJ_PLAYER || obj->type == OBJ_GHOST || obj->type == OBJ_OBSERVER);
  int slot = obj->id;
  int id, type;
  player *playp = &Players[slot];

  if (slot == Player_num || (Game_mode & GM_MULTI && Netgame.local_role == LR_SERVER)) {
    // turn off quad firing flag (becuase they will be spewing quad fire here
    for (int weapon_battery = 0; weapon_battery < MAX_WBS_PER_OBJ; weapon_battery++) {
      obj->dynamic_wb[weapon_battery].flags &= ~DWBF_QUAD;
    }
  }

  if (obj->type == OBJ_OBSERVER)
    return; // don't do anything if observer

  if (Game_mode & GM_MULTI) {
    if (Netgame.local_role != LR_SERVER) {
      playp->inventory.Reset(true, (spew_nonspewable) ? INVRESET_ALL : INVRESET_DEATHSPEW);
      playp->counter_measures.Reset(true, (spew_nonspewable) ? INVRESET_ALL : INVRESET_DEATHSPEW);
      return;
    }
  }

  // spew a shield and energy
  if (spew_energy_and_shield) {
    id = FindObjectIDName("Shield");
    if (id >= 0)
      PlayerSpewObject(obj, OBJ_POWERUP, id, 1, NULL);

    id = FindObjectIDName("Energy");
    if (id >= 0)
      PlayerSpewObject(obj, OBJ_POWERUP, id, 1, NULL);
  }

  // Spew the primary weapon powerups
  if (Game_mode & GM_MULTI) {
    if (playp->weapon[PW_PRIMARY].index > 0) {
      id = Ships[playp->ship_index].spew_powerup[playp->weapon[PW_PRIMARY].index];
      if (id != -1) {
        ASSERT(Object_info[id].type == OBJ_POWERUP);
        PlayerSpewObject(obj, OBJ_POWERUP, id, 2, NULL);
      }
    }

    // Spew the secondary weapon powerups
    id = Ships[playp->ship_index].spew_powerup[playp->weapon[PW_SECONDARY].index];
    if (id != -1) {
      ASSERT(Object_info[id].type == OBJ_POWERUP);
      int count = std::min<int>(playp->weapon_ammo[playp->weapon[PW_SECONDARY].index], MAX_SECONDARY_SPEW);
      for (int t = 0; t < count; t++)
        PlayerSpewObject(obj, OBJ_POWERUP, id, 2, NULL);
    }
  } else // Single player
  {
    int w;

    // Spew the primary weapon powerups
    for (w = 1; w < MAX_PRIMARY_WEAPONS; w++) {
      if (playp->weapon_flags & HAS_FLAG(w)) {
        id = Ships[playp->ship_index].spew_powerup[w];
        if (id != -1) {
          ASSERT(Object_info[id].type == OBJ_POWERUP);
          int objnum = PlayerSpewObject(obj, OBJ_POWERUP, id, 0, NULL);

          // Set ammo
          if (objnum != -1) {
            object *objp = &Objects[objnum];
            ASSERT(objp->control_type == CT_POWERUP);
            if (Game_mode & GM_MULTI)
              objp->ctype.powerup_info.count = std::max<int>(objp->ctype.powerup_info.count / 4, playp->weapon_ammo[w]);
            else
              objp->ctype.powerup_info.count = playp->weapon_ammo[w];
          }
        }
      }
    }

    // Spew the secondary weapon powerups
    for (w = FIRST_SECONDARY_WEAPON; w < FIRST_SECONDARY_WEAPON + MAX_SECONDARY_WEAPONS; w++) {
      if ((playp->weapon_flags & HAS_FLAG(w)) && playp->weapon_ammo[w]) {
        id = Ships[playp->ship_index].spew_powerup[w];
        if (id != -1) {
          ASSERT(Object_info[id].type == OBJ_POWERUP);

          // Check for multipack version
          int multi_id = FindMultipackPowerup(id);
          if (multi_id != -1) {
            int objnum;
            ASSERT(Object_info[multi_id].type == OBJ_POWERUP);
            objnum = PlayerSpewObject(obj, OBJ_POWERUP, multi_id, 0, NULL);
            if (objnum != -1)
              Objects[objnum].ctype.powerup_info.count = playp->weapon_ammo[w];
          } else {
            int count = std::min<int>(playp->weapon_ammo[w], MAX_SECONDARY_SPEW);
            for (int t = 0; t < count; t++)
              PlayerSpewObject(obj, OBJ_POWERUP, id, 0, NULL);
          }
        }
      }
    }
  }

  // Spew out the inventory items
  object *temp_obj;
  uint16_t inven_flags;
  int object_flags;
  bool spew_it;

  playp->inventory.ResetPos();
  int count = playp->inventory.Size();
  int i;
  for (i = 0; i < count; i++) {
    int limit = playp->inventory.GetPosCount();
    for (int t = 0; t < limit; t++) {
      playp->inventory.GetPosTypeID(type, id);
      playp->inventory.GetPosInfo(inven_flags, object_flags);

      if (spew_nonspewable)
        spew_it = true;
      else {
        if (!(inven_flags & INVF_NOTSPEWABLE)) {
          spew_it = true;
        } else {
          spew_it = false;
        }
      }

      if (spew_it) {
        if (id == -1) {
          // this is an already exisiting object, no creating
          playp->inventory.Remove(type, id);

          // type is really the object handle
          temp_obj = ObjGet(type);
          ASSERT(temp_obj);
          if (temp_obj) {
            ObjUnGhostObject(OBJNUM(temp_obj));
            if (Game_mode & GM_MULTI) {
              // tell the clients to unghost
              MultiSendGhostObject(temp_obj, false);
            }

            if (Game_mode & GM_MULTI)
              PlayerSpewObject(temp_obj, (inven_flags & INVF_TIMEOUTONSPEW) ? 2 : 0, obj->roomnum, &obj->pos, NULL);
            else
              PlayerSpewObject(temp_obj, 0, obj->roomnum, &obj->pos, NULL);
          }

        } else {
          ASSERT(type != OBJ_NONE);
          if (Game_mode & GM_MULTI)
            PlayerSpewObject(obj, type, id, (inven_flags & INVF_TIMEOUTONSPEW) ? 2 : 0, NULL);
          else
            PlayerSpewObject(obj, type, id, 0, NULL);
          playp->inventory.Remove(type, id);
        }
      }
    }
    playp->inventory.NextPos(true);
  }

  // Spew out the countermeasure items
  playp->counter_measures.ResetPos();
  count = playp->counter_measures.Size();
  int done = 0;
  int total_spewed = 0;

  for (i = 0; i < count && !done; i++) {
    if (count < 2 || (ps_rand() % 2)) {
      int limit = playp->counter_measures.GetPosCount();
      limit = std::min(2, limit);
      for (int t = 0; t < limit; t++) {
        playp->counter_measures.GetAuxPosTypeID(type, id);
        playp->counter_measures.GetPosInfo(inven_flags, object_flags);
        ASSERT(id != -1);
        ASSERT(type != OBJ_NONE);

        if (Game_mode & GM_MULTI)
          PlayerSpewObject(obj, type, id, (inven_flags & INVF_TIMEOUTONSPEW) ? 2 : 0, NULL);
        else
          PlayerSpewObject(obj, type, id, 0, NULL);

        playp->counter_measures.GetPosTypeID(type, id);
        playp->counter_measures.Remove(type, id);
      }

      total_spewed++;
      if (total_spewed >= 3)
        done = 1;
    }
    playp->counter_measures.NextPos(true);
  }
}

///////////////////////////////////////////////////////////////////////////////

//	Blow up the entire ship (all remaining subobjects.
void PlayerShipExplode(object *obj, float magnitude) {
  int visnum;

  ASSERT(obj != NULL);

  DLLInfo.me_handle = obj->handle;
  DLLInfo.it_handle = obj->handle;
  CallGameDLL(EVT_GAMEPLAYEREXPLODED, &DLLInfo);

  if (Death[obj->id].dying_model && (Death[obj->id].dying_model->n_models > 1)) {
    int i;

    // Create debris pieces from subobjects
    for (i = 1; i < Death[obj->id].dying_model->n_models; i++) {
      if (obj->rtype.pobj_info.subobj_flags & (1 << i)) {
        PlayerShipSpewPart(obj, i, magnitude * 0.85f);
      }
    }
  }

  CreateBlastRing(&obj->pos, BLAST_RING_INDEX, DAMAGE_RING_TIME, obj->size * 3, obj->roomnum);

  obj->rtype.pobj_info.subobj_flags = 0;

  // Player explosion sound
  Sound_system.Play3dSound(SOUND_BUILDING_EXPLODE, obj);

  CreateRandomSparks(80, &obj->pos, obj->roomnum, HOT_SPARK_INDEX, (ps_rand() % 3) + 2);
  visnum = CreateFireball(&obj->pos, BIG_EXPLOSION_INDEX, obj->roomnum, VISUAL_FIREBALL);
  if (visnum >= 0)
    VisEffects[visnum].size *= (3.0f * (magnitude / MAX_EXPLOSION_MAG));

  // Do badass damage
  obj->impact_time = 0;
  obj->impact_size = obj->size * 3;
  obj->impact_force = obj->impact_size * 2;
  obj->impact_generic_damage = obj->impact_size * 3;
  obj->impact_player_damage = obj->impact_size * 3;
  DoConcussiveForce(obj, obj->handle, 1.0);

  // Spew out any weapons, powerups, inventory
  PlayerSpewInventory(obj);

  if (Game_mode & GM_MULTI)
    MultiMakePlayerGhost(obj->id);

  obj->effect_info->type_flags = 0;

  // Stop sounds for this player
  PlayerStopSounds(obj->id);

  // Clear keyboard buffer
  if (obj->id == Player_num) {
    ddio_KeyFlush();
    Controller->flush();
  }
}

//	breaks off a random piece.
void PlayerShipBreakup(object *obj, float magnitude) {
  int subobjnum, i, j, idx;
  unsigned test_flag;
  int n_models = Death[obj->id].dying_model ? Death[obj->id].dying_model->n_models : 0;
  int n_remaining_models;

  //	don't break off object 0.
  if (n_models == 1)
    return;

  //	count number of valid subobjects skip 1st subobject
  n_remaining_models = 0;
  test_flag = obj->rtype.pobj_info.subobj_flags;
  for (i = 1; i < n_models; i++) {
    if (test_flag & (1 << i))
      n_remaining_models++;
  }

  // this is an INDEX into the VALID subobjects in the polymodel. (skip 1st subobj)
  idx = (ps_rand() * n_remaining_models / D3_RAND_MAX) + 1;

  subobjnum = -1;
  for (i = 1, j = 1; i < n_models; i++) {
    if (test_flag & (1 << i)) { // valid subobject?
      if (idx == j) {           // correct subobject index?
        test_flag &= ~(1 << i);
        subobjnum = i;
        break;
      }
      j++;
    }
  }

  //	okay, if no suboject found, blowup.
  if (subobjnum == -1) {
    StartPlayerExplosion(obj->id);
  } else {
    PlayerShipSpewPart(obj, subobjnum, magnitude);
  }
}

//	spews a part of the player ship and all its child subobjects
void PlayerShipSpewPartSub(object *obj, bsp_info *submodel, float magnitude);

void PlayerShipSpewPart(object *obj, int subobjnum, float magnitude) {
  PlayerShipSpewPartSub(obj, &Poly_models[obj->rtype.pobj_info.model_num].submodel[subobjnum], magnitude);
}

void PlayerShipSpewPartSub(object *obj, bsp_info *submodel, float magnitude) {
  vector rand_vec;
  int subobjnum = submodel - Poly_models[obj->rtype.pobj_info.model_num].submodel;
  int i;
  int visnum;

  ASSERT(subobjnum > -1 && subobjnum < Poly_models[obj->rtype.pobj_info.model_num].n_models);

  //	first go through all children.
  //	find child index, and use that index into the submodel array of the polymodel to pass a new submodel down
  //	the chain.
  i = 0;
  while (i < submodel->num_children) {
    PlayerShipSpewPartSub(obj, &Poly_models[obj->rtype.pobj_info.model_num].submodel[submodel->children[i]], magnitude);
    i++;
  }

  rand_vec.x = (float)(D3_RAND_MAX / 2 - ps_rand());
  if (obj->movement_type != MT_PHYSICS)
    rand_vec.y = (float)((float)ps_rand() / 2.0); // A habit of moving upward
  else
    rand_vec.y = (float)((float)D3_RAND_MAX / 1.5f - (float)ps_rand()); // A habit of moving upward
  rand_vec.z = (float)(D3_RAND_MAX / 2 - ps_rand());
  vm_NormalizeVectorFast(&rand_vec);

  object *subobj = CreateSubobjectDebrisDirected(obj, subobjnum, &rand_vec, magnitude);
  if (subobj) {
    //	create mini-explosion at start of debris fall.
    vector newpos = subobj->pos + submodel->offset;
    visnum = CreateFireball(&newpos, MED_EXPLOSION_INDEX, subobj->roomnum, VISUAL_FIREBALL);
    if (visnum >= 0) {
      VisEffects[visnum].size *= (2.5f * (magnitude / MAX_EXPLOSION_MAG));
      VisEffects[visnum].lifeleft *= 2.0f;
      rand_vec = (-rand_vec) * (magnitude * 25.0f);
      phys_apply_force(obj, &rand_vec);
      // mprintf(0, "Breakoff fireball size: %f, lifeleft: %f\n", Objects[objnum].size, Objects[objnum].lifeleft);
    }
  }

  //	mark subobject dead
  obj->rtype.pobj_info.subobj_flags &= (~(1 << subobjnum));
  // mprintf(0, "%d:sobj=%08x\n", subobjnum, obj->rtype.pobj_info.subobj_flags);
}

//	Moves death camera a certain distance based off of direction from vec from
//	the player. returns new dist
//
static vector Death_cam_vectors[] = {{0, 1, 0},  {0, 1, -1}, {0, 0, -1}, {0, -1, -1}, {0, -1, 0},  {0, -1, 1},
                                     {0, 0, 1},  {0, 1, 1},  {1, 0, 0},  {1, 0, -1},  {-1, 0, -1}, {-1, 0, 0},
                                     {-1, 0, 1}, {1, 0, 1},  {1, 1, 0},  {1, -1, 0},  {-1, -1, 0}, {-1, 1, 0}};

#define NUM_DEATH_VECS (sizeof(Death_cam_vectors) / sizeof(vector))

float MoveDeathCam(int slot, vector *vec, float distance) {
  fvi_info hit_data;
  fvi_query fq;
  vector best_vec, next_vec, cam_vec;
  float far_scale;
  int cur_vec_index, init_vec_index, loop_count;
  object *playobj = &Objects[Players[slot].objnum];

  //	once we've reached our distance goal, then we stop, otherwise keep moving.
  //	actually move the camera.  make sure we don't leave the mine though.
  hit_data.hit_type[0] = (OBJECT_OUTSIDE(playobj) ? HIT_TERRAIN : HIT_WALL);
  far_scale = 1.0f;

  init_vec_index = ps_rand() % NUM_DEATH_VECS;
  cur_vec_index = init_vec_index;
  loop_count = 0;

  do {
    //	randomize cam_vec just a little bit if possible.
    cam_vec = Death_cam_vectors[cur_vec_index++];
    cam_vec.x += ((ps_rand() % 5) - 2) * 0.1f;
    cam_vec.y += ((ps_rand() % 5) - 2) * 0.1f;
    vm_NormalizeVector(&cam_vec);

    cam_vec = cam_vec * distance;
    best_vec = playobj->pos + cam_vec;
    cam_vec = cam_vec * far_scale;
    next_vec = playobj->pos + cam_vec;

    if (cur_vec_index == init_vec_index) {
      distance = distance / 1.25f;
      far_scale = far_scale * 1.05f;
      loop_count++;
    }

    fq.p0 = &playobj->pos;
    fq.p1 = &next_vec;
    fq.startroom = playobj->roomnum;
    fq.rad = .5;
    fq.thisobjnum = OBJNUM(playobj);
    fq.ignore_obj_list = NULL;
    fq.flags = 0;

    ASSERT(std::isfinite(next_vec.x));
    ASSERT(std::isfinite(next_vec.y));
    ASSERT(std::isfinite(next_vec.z));

    fvi_FindIntersection(&fq, &hit_data);

    if (hit_data.hit_type[0] == HIT_NONE || loop_count == 32) {
      //	okay, we need to find the room that best_vec is in.
      fq.p0 = &playobj->pos;
      fq.p1 = &best_vec;
      fq.startroom = playobj->roomnum;
      fq.rad = 0.75f;
      fq.thisobjnum = OBJNUM(playobj);
      fq.ignore_obj_list = NULL;
      fq.flags = 0;
      fvi_FindIntersection(&fq, &hit_data);

      if (hit_data.hit_type[0] != HIT_NONE)
        ObjSetPos(Death[slot].camera, &hit_data.hit_pnt, hit_data.hit_room, NULL, false);
      else
        ObjSetPos(Death[slot].camera, &best_vec, hit_data.hit_room, NULL, false);
    } else {
      float ray_dist = vm_VectorDistanceQuick(&hit_data.hit_pnt, &playobj->pos);
      if (ray_dist < distance) {
        hit_data.hit_type[0] = HIT_NONE;
      }
    }

    // go back to start of list if at end.
    if (cur_vec_index == NUM_DEATH_VECS)
      cur_vec_index = 0;
  } while (hit_data.hit_type[0] != HIT_NONE && loop_count < 32);

  *vec = cam_vec;

  return distance;
}

// Returns the goal room of the passed in team
int GetGoalRoomForTeam(int teamnum) {
  ASSERT(teamnum >= 0 && teamnum <= 3);
  int flags[] = {RF_GOAL1, RF_GOAL2, RF_GOAL3, RF_GOAL4};

  for (int i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && (Rooms[i].flags & flags[teamnum])) {
      return i;
    }
  }

  return -1; // No goal for this team!
}

// Returns the goal room of the passed in player
int GetGoalRoomForPlayer(int slot) {
  ASSERT(slot >= 0 && slot <= MAX_PLAYERS);
  int team = PlayerGetTeam(slot);

  if (team == -1)
    return -1;

  return (GetGoalRoomForTeam(team));
}

// Sets the maximum number of teams in a game
void SetMaxTeams(int num) {
  if (num > MAX_TEAMS)
    num = MAX_TEAMS;

  if (num < 2)
    num = 1;

  if (num >= 2)
    Team_game = 1;
  else
    Team_game = 0;

  Num_teams = num;
}

int IncTeamScore(int teamnum, int add) {
  ASSERT(teamnum >= 0 && teamnum < Num_teams);
  Teams[teamnum].score += add;
  return Teams[teamnum].score;
}

// Resets the teams scores to zero
void ResetTeamScores() {
  int i;
  for (i = 0; i < MAX_TEAMS; i++)
    Teams[i].score = 0;
}

// Sets the lighting that a player will cast
void PlayerSetLighting(int slot, float dist, float r, float g, float b) {
  Players[slot].light_dist = dist;
  Players[slot].r = r;
  Players[slot].g = g;
  Players[slot].b = b;
}

// Gets the position of a given ball in world coords
void PlayerGetBallPosition(vector *dest, int slot, int num) {
  matrix rotmat, tempm;
  object *obj = &Objects[Players[slot].objnum];

  // Get position in circle
  float ballspeed = Players[slot].ballspeed * 65536;
  float rot_temp = ballspeed / 65536.0;
  int int_game = Gametime / rot_temp;
  float diff = Gametime - (int_game * rot_temp);
  int rot_angle = (diff * 65536);
  rot_angle = (rot_angle + (num * 5000)) % 65536;

  // Get matrix to multiply with
  if (num == 0)
    vm_AnglesToMatrix(&rotmat, 0, 0, rot_angle);
  else if (num == 1)
    vm_AnglesToMatrix(&rotmat, 0, rot_angle, 0);
  else
    vm_AnglesToMatrix(&rotmat, rot_angle, 0, 0);

  tempm = obj->orient * rotmat;

  // Get world position
  if (num == 1)
    *dest = obj->pos + (tempm.fvec * (obj->size + 1));
  else
    *dest = obj->pos + (tempm.uvec * (obj->size + 1));
}

// Sets a wacky rotating ball around the player ship
void PlayerSetRotatingBall(int slot, int num, float speed, float *r, float *g, float *b) {
  ASSERT(num >= 0 && num <= 3);

  Players[slot].ballspeed = speed;
  Players[slot].num_balls = num;

  for (int i = 0; i < num; i++) {
    Players[slot].ball_r[i] = r[i];
    Players[slot].ball_g[i] = g[i];
    Players[slot].ball_b[i] = b[i];
  }

  if (Demo_flags == DF_RECORDING) {
    DemoWritePlayerBalls(slot);
  }
}

void ObjSetRenderPolyobj(object *objp, int model_num, int dying_model_num = -1);

// Changes the ship a particular player is flying
void PlayerChangeShip(int slot, int ship_index) {
  ship *ship;

  if (Players[slot].start_roomnum == -1)
    return; // this player doesn't exist

  object *objp = &Objects[Players[slot].objnum];

  ship = &Ships[ship_index];

  if (!ship->used) { // this ship doesn't exist
    Int3();
    ship_index = GetNextShip(0);
    ASSERT(ship_index != -1);
    ship = &Ships[ship_index];
  }

  // Set size & shields
  objp->size = ship->size;
  objp->mtype.phys_info = ship->phys_info;

  // Set up render info, but save render type first
  int save_rt = objp->render_type;
  ObjSetRenderPolyobj(objp, ship->model_handle, ship->dying_model_handle);
  objp->render_type = save_rt;

  objp->rtype.pobj_info.model_num = ship->model_handle;
  objp->rtype.pobj_info.dying_model_num = ship->dying_model_handle;
  PageInPolymodel(ship->model_handle);
  if (ship->dying_model_handle != -1)
    PageInPolymodel(ship->dying_model_handle);

  if (ship->lo_render_handle >= 0)
    PageInPolymodel(ship->lo_render_handle);
  if (ship->med_render_handle >= 0)
    PageInPolymodel(ship->med_render_handle);

  ComputeDefaultSize(OBJ_PLAYER, objp->rtype.pobj_info.model_num, &objp->size);

  WBClearInfo(objp);

  Players[slot].ship_index = ship_index;
}

// Sets the FOV range at which the hud names will come on
void PlayerSetHUDNameFOV(int fov) {
  if (fov < 0) {
    HudNameTan = -1;
    return;
  }

  float rad = (float)(3.14 * (float)(fov / 2) / 180.0);
  HudNameTan = tan(rad);
}

// Switches a player object to observer mode
void PlayerSwitchToObserver(int slot, int observer_mode, int piggy_objnum) {
  object *obj = &Objects[Players[slot].objnum];

  // call the event to the multiplayer DLL's so they can do what they need
  if (Game_mode & GM_MULTI) {
    DLLInfo.me_handle = obj->handle;

    if (observer_mode == OBSERVER_MODE_PIGGYBACK) {
      DLLInfo.it_handle = Objects[piggy_objnum].handle;
    } else {
      DLLInfo.it_handle = OBJECT_HANDLE_NONE;
    }

    CallGameDLL(EVT_CLIENT_GAMEPLAYERENTERSOBSERVER, &DLLInfo);
  }

  // Stop sounds for this player
  PlayerStopSounds(slot);

  if (slot == Player_num) {
    AddHUDMessage(TXT_ENTEROBS);
    SetHUDMode(HUD_OBSERVER);
    Players[slot].movement_scalar = 2.0;
  } else
    AddHUDMessage(TXT_PLYRENTEROBS, Players[slot].callsign);

  CreateRandomSparks(30, &obj->pos, obj->roomnum, HOT_SPARK_INDEX, (ps_rand() % 3) + 2);

  if (Demo_flags != DF_PLAYBACK) {
    PlayerSpewInventory(obj, false);
  }

  obj->type = OBJ_OBSERVER;
  obj->render_type = RT_NONE;

  if (Demo_flags == DF_RECORDING) {
    DemoWritePlayerTypeChange(slot, false, observer_mode, piggy_objnum);
  }

  if (observer_mode == OBSERVER_MODE_ROAM) {
    SetObjectControlType(obj, CT_FLYING);
    Players[slot].piggy_objnum = -1;
    obj->movement_type = MT_PHYSICS;
  } else if (observer_mode == OBSERVER_MODE_PIGGYBACK) {
    SetObjectControlType(obj, CT_NONE);
    Players[slot].piggy_objnum = piggy_objnum;
    Players[slot].piggy_sig = Objects[piggy_objnum].handle & HANDLE_COUNT_MASK;
    mprintf(0, "Object %d is observing object %d!\n", obj - Objects, piggy_objnum);
  }
}

// Stops a player from observing
void PlayerStopObserving(int slot) {
  // call the event to the multiplayer DLL's so they can do what they need
  if (Game_mode & GM_MULTI) {
    DLLInfo.me_handle = Objects[Players[slot].objnum].handle;
    DLLInfo.it_handle = OBJECT_HANDLE_NONE;
    CallGameDLL(EVT_CLIENT_GAMEPLAYEREXITSOBSERVER, &DLLInfo);
  }

  if (slot == Player_num) {
    uint8_t hud_mode;
    Current_pilot.get_hud_data(&hud_mode);
    AddHUDMessage(TXT_LEAVEOBS);
    SetHUDMode((tHUDMode)hud_mode);
  } else
    AddHUDMessage(TXT_PLYRLEAVEOBS, Players[slot].callsign);

  // Stop sounds for this player
  PlayerStopSounds(slot);

  object *obj = &Objects[Players[slot].objnum];

  obj->type = OBJ_PLAYER;
  Players[slot].piggy_objnum = -1;

  InitPlayerNewShip(slot, INVRESET_ALL);
  ResetPlayerObject(slot);

  if (Demo_flags == DF_RECORDING) {
    DemoWritePlayerTypeChange(slot, true);
  }
}

#define PLAYER_TEXTURE_FPS 8.0f
// Sets the players custom texture.  If filename=NULL then sets to no texture
// Returns 1 if filename was successfully loaded, else 0
int PlayerSetCustomTexture(int slot, char *filename) {
  // Free up previous vclip/bitmap if there is one
  texture *texp = &GameTextures[Players[slot].custom_texture_handle];
  int bm_handle = texp->bm_handle;

  if (bm_handle != 0) {
    if (texp->flags & TF_ANIMATED)
      FreeVClip(bm_handle);
    else
      bm_FreeBitmap(bm_handle);

    texp->bm_handle = 0;
  }

  // Now load the new one
  texp->bm_handle = 0;
  if (filename == NULL)
    return 1;

  int anim;
  int new_handle = LoadTextureImage(filename, &anim, SMALL_TEXTURE, 1, 0);

  if (new_handle < 0)
    return 0;

  texp->bm_handle = new_handle;
  if (anim)
    texp->flags |= TF_ANIMATED;
  else
    texp->flags &= ~TF_ANIMATED;

  texp->flags |= TF_TEXTURE_64;

  // Set texture speed
  if (texp->flags & TF_ANIMATED) {
    vclip *vc = &GameVClips[texp->bm_handle];
    texp->speed = vc->num_frames * (1.0 / PLAYER_TEXTURE_FPS);
  }

  return 1;
}

//	Sets/Clears a permission for a ship on a given player
//	if pnum is -1 then all players will be set, else player is the player number
//	returns true on success
bool PlayerSetShipPermission(int pnum, char *ship_name, bool allowed) {
  ASSERT(ship_name);

  if (pnum < -1 || pnum >= MAX_PLAYERS) // illegal value
    return false;

  int ship_index = FindShipName(ship_name);
  if (ship_index == -1) {
    ASSERT(ship_index != -1);
    return false;
  }
  int bit = 0x01;
  bit = bit << ship_index;

  if (pnum == -1) {
    // go through everyone
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if (allowed)
        Players[i].ship_permissions |= bit;
      else
        Players[i].ship_permissions &= ~bit;
    }
  } else {
    if (allowed)
      Players[pnum].ship_permissions |= bit;
    else
      Players[pnum].ship_permissions &= ~bit;
  }
  return true;
}

//	Resets the ship permissions for a given player
//	pass false for set_default if you don't want the default ship allowed
bool PlayerResetShipPermissions(int pnum, bool set_default) {
  if (pnum < -1 || pnum >= MAX_PLAYERS)
    return false;

  int perm;

  mprintf(0, "Reseting ship permissions\n");

  if (set_default)
    perm = Default_ship_permission;
  else
    perm = 0;

  if (pnum == -1) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
      Players[i].ship_permissions = perm;
    }
  } else {
    Players[pnum].ship_permissions = perm;
  }

  return true;
}

//	Returns true if the given ship is allowed to be chosen for a pnum
bool PlayerIsShipAllowed(int pnum, char *ship_name) {
  ASSERT(ship_name);

  if (pnum < -1 || pnum >= MAX_PLAYERS) // illegal value
    return false;

  int ship_index = FindShipName(ship_name);
  if (ship_index == -1) {
    ASSERT(ship_index != -1);
    return false;
  }
  int bit = 0x01;
  bit = bit << ship_index;
  return ((Players[(pnum != -1) ? pnum : Player_num].ship_permissions & bit) != 0);
}
bool PlayerIsShipAllowed(int pnum, int ship_index) {
  if (pnum < -1 || pnum >= MAX_PLAYERS) // illegal value
    return false;

  ASSERT(ship_index >= 0 && ship_index < MAX_SHIPS);

  int bit = 0x01;
  bit = bit << ship_index;
  return ((Players[pnum].ship_permissions & bit) != 0);
}

void DoEnergyToShields(int pnum) {
  float amount; // how much energy gets transfered
  static float last_play_time = 0;

  if (Players[pnum].energy - INITIAL_ENERGY <= 0) {
    if (pnum == Player_num)
      AddHUDMessage(TXT_NEEDMOREENERGY, INITIAL_ENERGY);
    return;
  }
  if (Objects[Players[pnum].objnum].shields >= MAX_SHIELDS) {
    if (pnum == Player_num)
      AddHUDMessage(TXT_SHIELDSATMAX);
    return;
  }

  amount = std::min({Frametime * CONVERTER_RATE, Players[pnum].energy - INITIAL_ENERGY, (MAX_SHIELDS - Objects[Players[pnum].objnum].shields) * CONVERTER_SCALE});

  Players[pnum].energy -= amount;

  if ((!(Game_mode & GM_MULTI)) || Netgame.local_role == LR_SERVER)
    Objects[Players[pnum].objnum].shields += amount / CONVERTER_SCALE;
  else
    Multi_additional_shields[SHIELD_REQUEST_ENERGY_TO_SHIELD] += Frametime;

  if (pnum == Player_num) {
    if (last_play_time > Gametime)
      last_play_time = 0;

    if (Gametime > last_play_time + CONVERTER_SOUND_DELAY) {
      Sound_system.Play3dSound(SOUND_ENERGY_CONVERTER, &Objects[Players[pnum].objnum], MAX_GAME_VOLUME / 2);

      ain_hear hear;
      hear.f_directly_player = true;
      hear.hostile_level = 0.3f;
      hear.curiosity_level = 1.0f;
      hear.max_dist = Sounds[SOUND_ENERGY_CONVERTER].max_distance * 0.5f;
      AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);

      last_play_time = Gametime;
    }
  }
}

// Sets the start position that the player will respawn at
void PlayerAddWaypoint(int index) {
  ASSERT(Players[index].start_roomnum != -1); // Invalid start position specified
  mprintf(0, "Current waypoint is now %d\n", index);
  Current_waypoint = index;

  // A manual waypoint blows away all auto-waypoints
  for (int i = 0; i < MAX_PLAYERS; i++)
    Players[i].current_auto_waypoint_room = -1;
}

// Resets the waypoints (for new level)
void ResetWaypoint() {
  // Set global waypoint to first start position
  Current_waypoint = 0;

  // Clear out all auto-waypoints
  for (int i = 0; i < MAX_PLAYERS; i++)
    Players[i].current_auto_waypoint_room = -1;
}

struct waypoint {
  vector pos;
  int roomnum;
  matrix orient;
};

waypoint Waypoints[MAX_WAYPOINTS];
int Num_waypoints;

// Find all the waypoint objects and add them to the list of waypoints
void MakeAtuoWaypointList() {
  int i;
  object *objp;
  room *rp;

  Num_waypoints = 0;

  // Clear room waypoint flags
  for (i = 0, rp = Rooms; i <= Highest_room_index; i++, rp++)
    rp->flags &= ~RF_WAYPOINT;

  // Look through objects for waypoints
  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++) {
    if (objp->type == OBJ_WAYPOINT) {
      if (Num_waypoints < MAX_WAYPOINTS) {
        Waypoints[Num_waypoints].pos = objp->pos;
        Waypoints[Num_waypoints].roomnum = objp->roomnum;
        Waypoints[Num_waypoints].orient = objp->orient;
        Num_waypoints++;

        if (OBJECT_OUTSIDE(objp))
          ; // Terrain_seg[CELLNUM(objp->roomnum)].flags |= TF_WAYPOINT;
        else
          Rooms[objp->roomnum].flags |= RF_WAYPOINT;
      }

      ObjDelete(i);
    }
  }
}

// Sets the player's waypoint to the one in the specified room
void SetAutoWaypoint(object *objp) {
  ASSERT(objp->type == OBJ_PLAYER);

  // Get the player we're setting
  player *pp = &Players[objp->id];

  if (!OBJECT_OUTSIDE(objp)) {
    // delete the next two lines
    if (pp->current_auto_waypoint_room != objp->roomnum) {
      mprintf(0, "Setting auto-waypoint in room %d\n", objp->roomnum);
    }
    pp->current_auto_waypoint_room = objp->roomnum;
  }
}

// Moves the player to his last waypoint
void MovePlayerToWaypoint(object *objp) {
  ASSERT(objp->type == OBJ_PLAYER || objp->type == OBJ_GHOST);

  player *pp = &Players[objp->id];

  // If this player has an auto-waypoint, use it.  Else use global waypoint.
  if (pp->current_auto_waypoint_room != -1) {
    waypoint *wp;
    int i;

    // Find the waypoint
    for (i = 0, wp = Waypoints; i < Num_waypoints; i++, wp++)
      if (wp->roomnum == pp->current_auto_waypoint_room)
        break;
    ASSERT(i < Num_waypoints);

    ObjSetPos(objp, &wp->pos, wp->roomnum, &wp->orient, false);
  } else {
    ASSERT(Current_waypoint != -1);

    mprintf(0, "Resetting player ship to waypoint %d\n", Current_waypoint);
    ObjSetPos(objp, &Players[Current_waypoint].start_pos, Players[Current_waypoint].start_roomnum,
              &Players[Current_waypoint].start_orient, false);
  }
}

// Adds to the player's score & kill total
void PlayerScoreAdd(int playernum, int points) {
  // Add score
  if (points) {

    if (points > 0)
      Players[playernum].num_kills_level++;
    else
      Players[playernum].friendly_kills_level++;

    if (!(playernum != Player_num || IsCheater)) {
      Players[playernum].score += points;

      Score_added = points;
      Score_added_timer = SCORE_ADDED_TIME;
    }
  }
}

////////////////////////////////////////////////////
// Thief interface functions
////////////////////////////////////////////////////
extern uint8_t AutomapVisMap[MAX_ROOMS];
void MakeObjectVisible(object *obj);

// steals an item from the given player
void ThiefStealItem(int player_object_handle, int item) {
  object *pobj = ObjGet(player_object_handle);
  ASSERT(pobj);
  ASSERT(pobj->type == OBJ_PLAYER);

  int playernum = pobj->id;

  static int conv_id = -2;
  static int quad_id = -2;

  bool is_multi = false;
  if (Game_mode & GM_MULTI)
    is_multi = true;

  if (is_multi) {
    ASSERT(item != THIEFITEM_AUTOMAP);
  }

  if (is_multi && Netgame.local_role == LR_SERVER) {
    // send it off
    MultiSendThiefSteal(playernum, item);
  }

  switch (item) {
  case THIEFITEM_AUTOMAP:
    if (playernum == Player_num) {
      for (int i = 0; i < MAX_ROOMS; i++) {
        if (AutomapVisMap[i] == 1)
          AutomapVisMap[i] = 2;
      }
    }
    break;

  case THIEFITEM_HEADLIGHT:
    Players[playernum].flags &= ~PLAYER_FLAGS_HEADLIGHT;
    Players[playernum].flags |= PLAYER_FLAGS_HEADLIGHT_STOLEN;
    break;

  case THIEFITEM_ETOSCONV: {
    if (conv_id == -2)
      conv_id = FindObjectIDName("Converter");

    if (conv_id != -1) {
      Players[playernum].inventory.Remove(OBJ_POWERUP, conv_id);
    }
  } break;

  case THIEFITEM_CLOAK: {
    if ((pobj->effect_info) && (pobj->effect_info->type_flags & EF_FADING_OUT) ||
        (pobj->effect_info->type_flags & EF_CLOAKED)) {
      MakeObjectVisible(pobj);
    }
  } break;

  case THIEFITEM_INVULN: {
    if (Players[playernum].flags & PLAYER_FLAGS_INVULNERABLE) {
      MakePlayerVulnerable(playernum);
    }
  } break;

  case THIEFITEM_QUADFIRE: {
    pobj->dynamic_wb[LASER_INDEX].flags &= ~DWBF_QUAD;
    pobj->dynamic_wb[SUPER_LASER_INDEX].flags &= ~DWBF_QUAD;

    // remove from inventory
    if (quad_id == -2)
      quad_id = FindObjectIDName("QuadLaser");

    if (quad_id > -1) {
      Players[playernum].inventory.Remove(OBJ_POWERUP, quad_id);
    }

  } break;

  case THIEFITEM_RAPIDFIRE: {
    if (Players[playernum].weapon_recharge_scalar < 1.0f) {
      Players[playernum].weapon_recharge_scalar = 1.0f;
    }
  } break;
  }
}

// returns a stolen item to a player
void ThiefReturnItem(int player_object_handle, int item) {
  object *pobj = ObjGet(player_object_handle);
  ASSERT(pobj);
  ASSERT(pobj->type == OBJ_PLAYER);

  int playernum = pobj->id;

  switch (item) {
  case THIEFITEM_AUTOMAP:
    if (playernum == Player_num) {
      for (int i = 0; i < MAX_ROOMS; i++) {
        if (AutomapVisMap[i] == 2)
          AutomapVisMap[i] = 1;
      }
    }
    break;
  case THIEFITEM_HEADLIGHT:
    Players[playernum].flags &= ~PLAYER_FLAGS_HEADLIGHT_STOLEN;
    break;
    // all others should be handled by their powerup
  }
}

// returns true if a player has the specified item to be stolen
bool ThiefPlayerHasItem(int player_object_handle, int item) {
  object *pobj = ObjGet(player_object_handle);
  ASSERT(pobj);
  ASSERT(pobj->type == OBJ_PLAYER);

  int playernum = pobj->id;

  static int conv_id = -2;

  bool is_multi = false;
  if (Game_mode & GM_MULTI)
    is_multi = true;

  if ((playernum < 0 || playernum >= MAX_PLAYERS))
    return false;
  if (is_multi && !(NetPlayers[playernum].flags & NPF_CONNECTED))
    return false;

  switch (item) {
  case THIEFITEM_AUTOMAP:
    return !is_multi;
    break;
  case THIEFITEM_HEADLIGHT:
    if (Players[playernum].flags & PLAYER_FLAGS_HEADLIGHT_STOLEN)
      return false;
    return true;
    break;
  case THIEFITEM_ETOSCONV: {
    if (conv_id == -2)
      conv_id = FindObjectIDName("Converter");

    if (conv_id != -1) {
      int inv_count = Players[playernum].inventory.GetTypeIDCount(OBJ_POWERUP, conv_id);
      if (inv_count > 0)
        return true;
    }
    return false;
  } break;
  case THIEFITEM_CLOAK: {
    if (pobj->effect_info) {
      if (!((pobj->effect_info->type_flags & EF_FADING_OUT) || (pobj->effect_info->type_flags & EF_CLOAKED))) {
        return false;
      } else {
        return true;
      }
    }
    return false;
  } break;
  case THIEFITEM_INVULN: {
    if (Players[playernum].flags & PLAYER_FLAGS_INVULNERABLE) {
      return true;
    }
    return false;
  } break;
  case THIEFITEM_QUADFIRE: {
    if (pobj->dynamic_wb[LASER_INDEX].flags & DWBF_QUAD)
      return true;
    else
      return false;
  } break;
  case THIEFITEM_RAPIDFIRE: {
    if (Players[playernum].weapon_recharge_scalar < 1.0f) {
      return true;
    }
    return false;
  } break;
  }

  return false;
}
