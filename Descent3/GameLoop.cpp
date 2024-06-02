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

 * $Logfile: /DescentIII/main/GameLoop.cpp $
 * $Revision: 400 $
 * $Date: 4/19/00 5:10p $
 * $Author: Matt $
 *
 * Main loop for Descent 3
 *
 * $Log: /DescentIII/main/GameLoop.cpp $
 *
 * 400   4/19/00 5:10p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 * Mac key code change (KEY_PAGEDOWN)
 *
 * 399   4/06/00 9:25a Matt
 * Fixed a screen clear problem on at ATI Rage Fury Maxx in dual-chip mode
 * by forcing the screen to clear four times (instead of three).
 *
 * 398   3/30/00 11:48a Jeff
 * an ivibe call was nestled in a DEBUG block
 *
 * 397   3/29/00 2:24p Jeff
 * moved call to vibe_quarterframe before rendering
 *
 * 396   3/20/00 12:08p Matt
 * Merge of Duane's post-1.3 changes.
 * Made PageDown key pause on Mac (Mac only)
 *
 * 395   1/27/00 12:04p Jeff
 * updated IntelliVIBE to match new specs
 *
 * 394   1/26/00 9:20p Jeff
 * added support for IntelliVIBE DLL
 *
 * 393   10/24/99 9:34a Chris
 *
 * 392   10/22/99 6:04p Jeff
 * fixed bugs and compiler errors resulting from mac code merge
 *
 * 391   10/22/99 1:26p Matt
 * Mac merge
 *
 * 390   10/15/99 5:56p 3dsmax
 * In terrain sound system, treat heights above 255 as 255.
 *
 * 389   9/20/99 5:30p Jeff
 * added pretty powerup particles for Katmai systems
 *
 * 388   8/31/99 5:30p Jason
 * network statistics code
 *
 * 387   7/26/99 1:17p Jeff
 * need to call startframe/endframe for renderstats
 *
 * 386   7/22/99 8:59p Jeff
 * added texture upload for render stats
 *
 * 385   7/20/99 1:18p Samir
 * save state of rearviews between game through the pilot file.
 *
 * 384   7/15/99 6:39p Jeff
 * added outlinemode cheat code and rendering stats cheat
 *
 * 383   7/13/99 10:02a Jeff
 * call mulitplayer event to translate text taunts
 *
 * 382   5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 381   5/23/99 12:35a Chris
 * FVI check now ignores rendered portals
 *
 * 380   5/21/99 5:08a Chris
 * Corrected the Region Vis mprintf
 *
 * 379   5/20/99 10:10p Samir
 * don't allow certain keys for death (like savegame, guidebot, markers).
 *
 * 378   5/17/99 6:06p Chris
 * Adding robot debug code
 *
 * 377   5/12/99 1:18p Samir
 * play music during game too when in menus.
 *
 * 376   5/11/99 10:58a Kevin
 * Added del-PAD_7 to kill off all robots of a certain type (the first
 * type found)
 *
 * 375   5/10/99 10:22p Ardussi
 * changes to compile on Mac
 *
 * 374   5/10/99 5:40p Jeff
 * no saving during a cinematic
 *
 * 373   5/09/99 10:07p Jeff
 * added guidebot shortcuts
 *
 * 372   5/09/99 3:07p Jason
 * added a way to track FVI rays
 *
 * 371   5/07/99 6:21p Jeff
 * hooked up fvi to debug graph
 *
 * 370   5/05/99 5:45p Samir
 * fixed DEL-F10 player ship change.
 *
 * 369   5/04/99 9:26p Jeff
 * debug key to turn off spewers
 *
 * 368   5/01/99 4:59p Jason
 * made rearview work correctly
 *
 * 367   4/30/99 12:02p Matt
 * Keep the rear view up between levels, but close the other camera views.
 *
 * 366   4/25/99 6:14p Kevin
 * added "-timetest file.dem" to behave like gamegauge does
 *
 * 365   4/24/99 8:43p Samir
 * when shrinking screen hud messages get rendered in black region.
 *
 * 364   4/24/99 7:22p Jason
 * fixed respawn problem
 *
 * 363   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 362   4/20/99 11:45a Samir
 * added autosave
 *
 * 361   4/16/99 6:02p Jason
 * fixed crash bugs with dev release
 *
 * 360   4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 359   4/16/99 12:04p Jason
 * fixed players respawning too fast
 *
 * 358   4/15/99 11:58p Jeff
 * include soar.h to make Linux happy
 *
 * 357   4/15/99 1:39a Jeff
 * changes for linux compile
 *
 * 356   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 355   4/12/99 7:14p Samir
 * added multiple pages per mono window.
 *
 * 354   4/12/99 1:13a Matt
 * Added guidebot view to small windows (& simplified code to set marker
 * views).
 *
 * 353   4/10/99 5:56p Matt
 * Cleaned up object initialization code, including create object & load
 * object.
 *
 * 352   4/07/99 12:30p Matt
 * Added code for failed missions.
 *
 * 351   4/04/99 8:15p Jeff
 * added debug graph stuff
 *
 * 350   4/02/99 11:33p Jeff
 * able to turn off IGC in debug mode.  Better handling of cinematics
 * quick exit if playing via alt-p
 *
 * 349   3/27/99 4:45p Samir
 * reinstate pause music when pausing game.
 *
 * 348   3/23/99 9:07p Samir
 * turn on and off music when pausing and resuming game, if appropriate.
 *
 * 347   3/23/99 2:50p Samir
 * made HUD_disabled available to all builds.
 *
 * 346   3/22/99 4:26p Samir
 * added toggles for guided missile view and reticle.
 *
 * 345   3/08/99 9:07p Samir
 * dont flush controller if object doesn't exist.
 *
 * 344   3/08/99 5:13p Jason
 * added delay to player respawn after death
 *
 * 343   3/05/99 5:23p Jason
 * fixed text taunts to actually work
 *
 * 342   3/05/99 1:34p Jeff
 * don't allow saving/loading of games during cinematics
 *
 * 341   3/04/99 4:56p Jason
 * moved function call to correct spot
 *
 * 340   3/04/99 4:53p Jason
 * added LOD manipulation function calls
 *
 * 339   3/02/99 9:37p Matt
 * In all-weapons cheat, give the player the max ammo for each weapon,
 * instead of 5000.  This means that non-ammo weapons won't get ammo.
 *
 * 338   3/02/99 6:39p Jeff
 * level goals working in save/load game
 *
 * 337   3/02/99 2:50p Samir
 * hud observer mode works with rest of hud.
 *
 * 336   3/01/99 4:17p Jeff
 * added net flag whether buddy bot allowed
 *
 * 335   3/01/99 12:23a Samir
 * reset return value for DLL upon going into CallGameDLL with key event
 * (at the request of Jeff).
 *
 * 334   2/24/99 12:25p Jeff
 * fixed guided missile/mass driver reticle/view problems when going into
 * a cinematic
 *
 * 333   2/21/99 12:28p Matt
 * Added terrain sound system
 *
 * 332   2/18/99 10:29a Jason
 * fixed zbuffer problem
 *
 * 331   2/17/99 12:38p Kevin
 * Added -framecap <fps> to limit frame and fixed timer bug and old
 * framerate limiter code.
 *
 * 330   2/16/99 5:24p Kevin
 * Converted timer to use 64bit int.
 *
 * 329   2/15/99 7:49p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 328   2/13/99 12:31a Jeff
 * debug key fixups (now in alphabetical order)
 *
 * 327   2/12/99 6:47p Jeff
 * removed tilde as telcom key
 *
 * 326   2/12/99 3:54a Jeff
 * added function to restart a level, and a cheat key to do so (del-alt-e)
 *
 * 325   2/10/99 6:55p Jeff
 * added proxmines to the game
 *
 * 324   2/10/99 2:41p Chris
 * Added debug info
 *
 * 323   2/09/99 12:09p Jason
 * rewriting indoor engine...
 *
 * 322   2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 321   2/09/99 1:29a Jeff
 * added code to let D3 process multiplayer games in the background if
 * game is not in focus.
 *
 * 320   2/08/99 6:39p Jason
 * first pass at new indoor engine
 *
 * 319   2/05/99 7:23p Kevin
 * OEM Changes
 *
 * 318   1/31/99 8:48p Jeff
 * new in game cinematics system finished
 *
 * 317   1/31/99 7:25p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 316   1/31/99 3:44p Matt
 * Streamlined game sequencing
 *
 * 315   1/30/99 4:42p Jeff
 * changed keys for telcom
 *
 * 314   1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 313   1/29/99 6:29p Samir
 * implemented hud scrollback for hud messages.
 *
 * 312   1/28/99 6:17p Jason
 * added markers
 *
 * 311   1/28/99 2:22p Samir
 * simplified music system for D3.
 *
 * 310   1/28/99 11:32a Jason
 * added marker cameras
 *
 * 309   1/27/99 6:54p Keneta
 * fixed merge problwm
 *
 * 308   1/27/99 6:08p Jason
 * first pass at markers
 *
 * 307   1/27/99 6:05p Samir
 * added scrollback for game messages on HUD.
 *
 * 306   1/27/99 6:02p Jeff
 * test keys for audio taunts
 *
 * 305   1/22/99 5:15p Jeff
 * added a key to toggle osiris debug messages
 *
 * 304   1/22/99 4:06p Jeff
 * added hud messages that can be sent to just teammates or individual
 * people
 *
 * 303   1/21/99 7:02p Jason
 * took out liquid effect from key c
 *
 * 302   1/21/99 3:34p Jason
 * added liquid code
 *
 * 301   1/20/99 3:45a Jeff
 * added call to update any in-game cinematics (boss introduction
 * cinematics)
 *
 * 300   1/19/99 11:25a Jason
 * added room (fog and wind) changing functions
 *
 * 299   1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 298   1/15/99 7:16p Kevin
 * Added GameGauge Configuration & code
 *
 * 297   1/13/99 12:43p Jason
 * fixed flickering exit menu screen
 *
 * 296   1/11/99 4:08p Jason
 * added multiplayer taunt macros
 *
 * 295   1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 294   1/04/99 12:48p Jason
 * fixed clear screen problems with triple buffer
 *
 * 293   12/21/98 9:44a Chris
 * Ambient life stuff is all tied in to game sequencing
 *
 * 292   12/18/98 10:42a Jeff
 * call to process osiris's timers added in GameFrame
 *
 * 291   12/17/98 12:08p Jeff
 * first checkin of new implementation of OSIRIS (old OSIRIS no longer
 * works)
 *
 * 290   12/16/98 12:04p Kevin
 * GameSpy!
 *
 * 289   12/15/98 6:41p Jason
 * took out mprintf
 *
 * 288   12/07/98 11:30a Kevin
 * Added some features from the 1.1 demo patch
 *
 * 287   12/07/98 10:35a Jason
 * added adjustable FOV
 *
 * 286   12/01/98 3:34p Matt
 * Got rear view working.
 *
 * 285   11/24/98 3:57p Kevin
 * Demo system immprovements
 *
 * 284   11/24/98 10:41a Kevin
 * Demo system
 *
 * 283   11/23/98 4:52p Kevin
 * Demo system enhancments
 *
 * 282   11/19/98 5:40p Kevin
 * Demo system
 *
 * 281   11/19/98 12:43p Samir
 * added functions to start ui menu immediately without using
 * Game_interface_mode
 *
 * 280   11/18/98 2:54p Jason
 * added snow effect
 *
 * 279   11/16/98 4:15p Samir
 * added death.
 *
 * 278   11/13/98 2:28p Samir
 * new music system.
 *
 * 276   11/10/98 5:18p Jeff
 * removed force feedback test keys
 *
 * 275   11/09/98 3:08p Kevin
 * Added demo code
 *
 * 274   11/06/98 7:00p Jeff
 * first round of new force feedback installed
 *
 * 273   11/05/98 7:35p Samir
 * StartTime function altered to return if timer paused == 0;.
 *
 * 272   11/05/98 5:54p Kevin
 * Demo system work
 *
 * 271   11/03/98 6:43p Jeff
 * new low-level & high level Force Feedback system implemented, handles
 * window losing focus, etc.
 *
 * 270   10/29/98 11:08a Samir
 * don't allow sizing of letterbox screens.
 *
 * 269   10/24/98 2:16p Samir
 * processbuttons doesn't call lowlevel input code anymore.
 *
 * 268   10/21/98 11:14a Samir
 * added generic code to skip rendering while in game controller config or
 * telcom.
 *
 * 267   10/20/98 12:42p Matt
 * Made the small views work on the cockpit.
 *
 * 266   10/19/98 7:51p Kevin
 * performance testing
 *
 * 265   10/19/98 7:18p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 264   10/19/98 2:48p Jeff
 * changed define for rtp performance...just define USE_RTP in
 * rtperformance.h in order to enable it
 *
 * 263   10/19/98 1:10p Kevin
 * Took demo recording out of demo build
 *
 * 262   10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 261   10/18/98 7:26p Samir
 * added ability to poll mouse and joystick for input in death screen.
 * clear screen when toggling console screen.
 *
 * 260   10/17/98 5:50p Jeff
 * hooked in rtperformance (run time performance) library
 *
 * 259   10/17/98 12:46p Kevin
 * Beta 4 fixes
 *
 * 258   10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 257   10/16/98 2:44p Kevin
 * working on getting demo compiling
 *
 * 256   10/16/98 2:24p Jason
 * changes for the demo
 *
 * 255   10/16/98 12:44a Jeff
 * created frametime info log stuff
 *
 * 254   10/15/98 8:19p Samir
 * damn stupid bug when growing window.
 *
 * 253   10/14/98 6:41p Samir
 * if in UI system, clear screen every frame to prevent hall of mirrors.
 *
 * 252   10/14/98 4:27p Samir
 * must press spacebar to quit death.
 *
 * 251   10/12/98 10:16a Matt
 * Took out D3XDebugIO() call. which didn't really do anything, so I could
 * use the backquote key elsewhere.
 *
 * 250   10/11/98 3:00a Jeff
 * TelCom now calls GameFrame() if it's being run in multiplayer, so calls
 * were put into GameFrame to handle certain cases when it's in TelCom
 *
 * 249   10/09/98 12:22p Jeff
 * DemoCheats()
 *
 * 248   10/08/98 3:38p Jeff
 * DEL-E doesn't work in multiplayer games
 *
 * 247   10/08/98 3:12p Matt
 * Fixed toggle outline key, and added key to turn on all outline options.
 *
 * 246   10/06/98 5:45p Kevin
 * Added new configuration for demo
 *
 * 245   10/06/98 3:07p Jeff
 * fixed del-x cheat code so it adds counter measures right
 *
 * 244   10/06/98 2:59p Jason
 * added timedemo function
 *
 * 243   10/05/98 7:23p Jason
 * implemented destroyable lights (first draft)
 *
 * 242   10/05/98 12:09p Kevin
 * Converted projects to VC6 and demo file stuff added
 *
 * 241   10/05/98 11:08a Jason
 * implemented player message log
 *
 * 238   9/29/98 10:44a Jeff
 * renamed gunbouy to gunboy
 *
 * 237   9/25/98 4:50p Jeff
 *
 * 236   9/24/98 12:57p Jason
 * more state limited optimizations
 *
 * 235   9/22/98 12:40p Matt
 * Cleaned up the object per-frame processing code.
 *
 * 234   9/21/98 11:10a Jeff
 * Calls to init/close forcefeedback
 *
 * 233   9/18/98 7:38p Jeff
 *
 * 232   9/18/98 1:27p Jason
 * cleaned up renderer initting
 *
 * 231   9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 229   9/16/98 5:38p Jason
 * made dedicated server bail on key events
 *
 * 228   9/16/98 5:10p Jason
 * added first pass at thrid-person camera system
 *
 * 227   9/14/98 6:28p Jason
 * first pass at getting dedicated server working
 *
 * 226   9/10/98 12:01p Chris
 * Made matcen:DoRenderFrame() functional
 *
 * 225   9/08/98 4:56p Chris
 * Matcens rev.5 almost functional
 *
 * 224   9/03/98 12:11p Chris
 * Adding matcen support
 *
 * 223   9/01/98 4:11p Samir
 * moved screenshot code from gameloop to game.cpp
 *
 * 222   8/31/98 6:50p Jeff
 * made inventory and countermeasure keys customizable
 *
 * 221   8/31/98 5:44p Matt
 * Added a key (Del-N) to restart a level
 *
 * 220   8/26/98 4:30p Jason
 * added directional lights (headlight for player)
 *
 * 219   8/25/98 11:27p Matt
 * Added key to toggle fog.
 *
 * 218   8/25/98 3:08p Samir
 * Del-F10 does ship (and cockpit) transitions.
 *
 * 217   8/25/98 1:40p Jason
 * fixed message bug
 *
 * 216   8/25/98 12:36p Jason
 * added specular debug key
 *
 * 215   8/24/98 6:07p Samir
 * change cockpits with ships.
 *
 * 214   8/24/98 10:40a Jason
 * fixed some rendering problems
 *
 * 213   8/18/98 5:54p Jeff
 * added countermeasures and afterburner when you DEL-X
 *
 * 212   8/18/98 3:02p Samir
 * added game saving and loading.
 *
 * 211   8/17/98 6:40p Matt
 * Added ambient sound system
 *
 * 210   8/16/98 12:20a Jeff
 * moved out actual energy->shields to player function...keypress still
 * handled here though
 *
 * 209   8/15/98 11:23p Matt
 * Re-added keyboard flush when the game dll is swallowing keys.
 *
 * 208   8/15/98 10:53p Matt
 * Rewrote key handling routines to deal with keys pressed while dead, and
 * to generally clean things up a bit.
 *
 * 207   8/15/98 5:16p Matt
 * Added new Base_directory variable.  Got rid of D3_LOCAL check and
 * 'local directory' registry variable.
 *
 * 206   8/14/98 5:28p Jeff
 * test key added
 *
 * 205   8/14/98 4:57p Jeff
 *
 * 204   8/13/98 7:23p Jeff
 * moved in UI system
 *
 * 203   8/13/98 3:10p Jeff
 * keyflush if multiplayer dll requests so
 *
 * 202   8/12/98 2:54p Matt
 * Renamed the slash and backslash key constants.
 *
 * 201   8/10/98 5:51p Samir
 * new keys for music system.
 *
 * 200   8/10/98 12:16p Chris
 * Added AI_NumHostileAlert
 *
 * 199   8/07/98 7:12p Samir
 * changed d3xexecscript.
 *
 * 198   8/04/98 10:26a Kevin
 * Custom sound and bmp exchange system
 *
 * 197   7/28/98 5:40p Samir
 * added call to music system per frame.
 *
 * 196   7/27/98 5:59p Jason
 * added piggyback mode plus multiplayer colors
 *
 * 195   7/24/98 5:30p Samir
 * took out extranneous stream cheats.
 *
 * 194   7/24/98 4:45p Jason
 * added notification if any subsystem takes more than .2 seconds to
 * execute
 *
 * 193   7/23/98 11:43a Jeff
 * fixed observer mode bug
 *
 * 192   7/22/98 3:16p Jason
 * added observer mode
 *
 * 191   7/21/98 10:25a Kevin
 * commented out heapcheck
 *
 * 190   7/20/98 7:00p Sean
 * SOMEONE:  Added a heapcheck call
 *
 * 189   7/09/98 8:33p Samir
 * changes for new streaming interface.
 *
 * 188   7/08/98 6:00p Jeff
 * handles inventory use in a multiplayer game
 *
 * 187   7/06/98 7:17p Jeff
 * added keys for countermeasures (temporary...probably want these
 * configurable)
 *
 * 186   6/30/98 6:36p Chris
 * Added rev .1 of multiplayer animations - BTW  It is totally not done.
 *
 * 185   6/30/98 6:14p Samir
 * Call DoUIFrameWithoutInput instead of DoUIFrame.
 *
 * 184   6/25/98 5:22p Kevin
 * Req/Send gametime to clients
 *
 * 183   6/25/98 12:42p Jeff
 * Added exit game confirmation
 *
 * 182   6/24/98 5:59p Chris
 *
 * 181   6/24/98 5:55p Chris
 * Added simple support for on the fly mixer/quality switching - Kills all
 * sounds (which is incorrect).
 *
 * 180   6/24/98 5:20p Matt
 * Added key for pause;  Cleaned up key handling; ripped out some E3 demo
 * code.
 *
 * 179   6/24/98 4:39p Chris
 * Improved the multiple mixer support
 *
 * 178   6/24/98 12:09p Chris
 * Update
 *
 * 177   6/24/98 11:12a Jeff
 * fixed accidental checkin
 *
 * 176   6/24/98 11:14a Chris
 * Added more support and bug fixes
 *
 * 175   6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 174   6/19/98 6:42p Jason
 * made specular mapping a config detail item
 *
 * 173   6/19/98 6:21p Chris
 * Moved Del+F5 to DEL+F6 and F6 to Del+F11
 *
 * 172   6/19/98 6:05p Jeff
 * call to update voices to handle the voice queue
 *
 * 171   6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 170   6/18/98 5:21p Jeff
 * put in call to update streaming audio buffers in the game loop
 *
 * 169   6/18/98 1:09p Chris
 *
 * 168   6/16/98 5:27p Chris
 * Revision version 1.0 (should all be functional for 16 bit mono samples)
 *
 * 167   6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 166   6/16/98 10:38a Jeff
 * localization, strings pulled out to stringtable.h and d3.str
 *
 * 165   6/04/98 4:52p Jeff
 * Added a suspend/resume controls call on return from EVT_CLIENT_KEYPRESS
 * if the DLL requests it
 *
 * 164   6/02/98 11:01a Jason
 * Post E3 Checkin
 *
 * 163   6/01/98 11:00a Jeff
 * Moved the call to the multiplayer EVT_CLIENT_KEYPRESS up in the
 * function
 *
 * 162   5/27/98 12:35a Samir
 * level restart for E3 by default on, this time.
 *
 * 161   5/26/98 10:51p Samir
 * ability to activate/deactivate restart level sequence timer.
 *
 *
 * 159   5/26/98 5:03p Samir
 * Set E3 time limit for level to 15 minutes.
 *
 * 158   5/26/98 1:20p Samir
 * added special weapons key for E3!
 *
 * 157   5/26/98 11:36a Matt
 * Changed small view system to allow the popup window in any of the three
 * positions, to allow any window to be the "bigger" size, and to restore
 * the old view when a popup view goes away.
 *
 * 156   5/25/98 8:29p Samir
 * Added E3_DEMO define for E3 stuff like game time limits and special
 * keys.
 *
 * 155   5/25/98 3:46p Jason
 * added better light glows
 *
 * 154   5/22/98 8:36p Samir
 * added E3 keyboard lock to hide the not so cool looking stuff in D3
 *
 * 153   5/22/98 3:27p Jason
 * added specular lighting
 *
 * 152   5/19/98 10:44a Jeff
 * changed D3_QUICK to D3_FAST
 *
 * 151   5/18/98 4:36p Jeff
 * TelCom uses Game_interface_mode variable now
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gameloop.h"
#include "game.h"
#include "render.h"
#include "descent.h"
#include "slew.h"
#include "mono.h"
#include "doorway.h"
#include "weapon.h"
#include "hlsoundlib.h"
#include "multi.h"
#include "player.h"
#include "damage.h"
#include "ship.h"
#include "objinit.h"
#include "gameevent.h"
#include "gametexture.h"
#include "AIMain.h"
#include "ddvid.h"
#include "ddio.h"
#include "hud.h"
#include "terrain.h"
#include "BOA.h"
#include "lighting.h"
#include "findintersection.h"
#include "soar.h"
#include "multi.h"
#include "hud.h"
#include "bsp.h"
#include "gauges.h"
#include "SmallViews.h"
#include "newui.h"
#include "Inventory.h"
#include "physics.h"
#include "controller.h"
#include "controls.h"
#include "gamesequence.h"
#include "cockpit.h"
#include "help.h"
#include "game.h"
#include "aipath.h"
#include "game2dll.h"
#include "Mission.h"
#include "object_lighting.h"
#include "fireball.h"
#include "weather.h"
#include "stringtable.h"
#include "streamaudio.h"
#include "voice.h"
#include "soundload.h"
#include "sounds.h"
#include "ambient.h"
#include "ship.h"
#include "config.h"
#include "matcen.h"
#include "dedicated_server.h"
#include "D3ForceFeedback.h"
#include "levelgoal.h"
#include "demofile.h"
#include "pilot.h"
#include "rtperformance.h"
#include "demofile.h"
#include "musicapi.h"
// #include "gamespy.h"
#include "osiris_dll.h"
#include "aiambient.h"
#include "marker.h"
#include "gamecinematics.h"
#include "postrender.h"
#include "debuggraph.h"
#include "gamesave.h"
#include "psrand.h"
#include "spew.h"
#include "grtext.h"
#include "gamefont.h"
#include "renderobject.h"
#include "vibeinterface.h"
#include "buddymenu.h"

#ifdef EDITOR
#include "editor\d3edit.h"
#endif

extern bool Display_renderer_stats;

// Current zoom factor (this is the tan of 29.25, which is half our FOV of 58.5)
float Render_FOV = D3_DEFAULT_FOV;
float Render_zoom = D3_DEFAULT_ZOOM;

// How long (in seconds) the last frame took
float Frametime = .1f;

// How long (in seconds) since the game started
float Gametime;

int Timedemo_frame = -1;

// How many frames have been renered.
// NOTE: this is a count of 3d frames, not game frames
int FrameCount = 0;

bool HUD_disabled = 0;
#ifdef _DEBUG
int DoAI = 1;
bool System_locked = false;
int Stream_type = 0;
#else
int Stream_type = 0;
#define DoAI 1
#endif

bool Tracking_FVI = false;

// Set this to force window clear
int Clear_screen = 0;

//	determines if game is paused.
bool Game_paused = false;

// Used for limiting the framerate
int Min_allowed_frametime = 0;

// determines if we're rendering the main view
bool Rendering_main_view = false;
bool Skip_render_game_frame = false;
bool Menu_interface_mode = false;

int frames_one_second = 0;
int min_one_second = 0x7fffffff;
int max_one_second = 0;

int64_t last_timer = 0;

// contains information for the music system.
tMusicSeqInfo Game_music_info;

// Defines for changing the window size
#define WINDOW_W_DELTA ((Max_window_w / 16) & ~1)
#define WINDOW_H_DELTA ((Max_window_h / 16) & ~1)

#define WINDOW_MIN_W ((Max_window_w * 10) / 22)
#define WINDOW_MIN_H ((Max_window_h * 10) / 22)

//	Functions
void ApplyShadowsToRooms();
void StartGameMenu();
void EndGameMenu();
void ProcessGuidebotKeys(int key);

// Make the 3D window larger
void GrowWindow() {
  if (GetHUDMode() == HUD_LETTERBOX)
    return;

  Game_window_w += WINDOW_W_DELTA;
  Game_window_h += WINDOW_H_DELTA;

  if (Game_window_h > Max_window_h)
    Game_window_h = Max_window_h;

  if (Game_window_w > Max_window_w)
    Game_window_w = Max_window_w;

  Game_window_x = (Max_window_w - Game_window_w) / 2;
  Game_window_y = (Max_window_h - Game_window_h) / 2;

  Current_pilot.set_hud_data(NULL, NULL, NULL, &Game_window_w, &Game_window_h);

  Clear_screen = 4;

  ResizeCockpit();
}

// Make the 3D window smaller
void ShrinkWindow() {
  if (GetHUDMode() == HUD_LETTERBOX)
    return;

  if (Game_window_w > WINDOW_MIN_W) {

    Game_window_w -= WINDOW_W_DELTA;
    Game_window_h -= WINDOW_H_DELTA;

    if (Game_window_w < WINDOW_MIN_W)
      Game_window_w = WINDOW_MIN_W;

    if (Game_window_h < WINDOW_MIN_H)
      Game_window_h = WINDOW_MIN_H;

    Game_window_x = (Max_window_w - Game_window_w) / 2;
    Game_window_y = (Max_window_h - Game_window_h) / 2;

    Clear_screen = 4;

    ResizeCockpit();

    Current_pilot.set_hud_data(NULL, NULL, NULL, &Game_window_w, &Game_window_h);
  }
}

// Data and code for camera views

#define CV_NONE 0      // View not active
#define CV_REARVIEW 1  // Rear view
#define CV_MARKER1 2   // Marker view
#define CV_MARKER2 3   // Marker view
#define CV_MARKER3 4   // Marker view
#define CV_MARKER4 5   // Marker view
#define CV_MARKER5 6   // Marker view
#define CV_MARKER6 7   // Marker view
#define CV_MARKER7 8   // Last marker view
#define CV_MARKER8 9   // Last marker view
#define CV_GUIDEBOT 10 // Guide-Bot
// #define CV_COOP		3		//View from a coop player

#define NUM_CAMERA_VIEWS 3

int Camera_view_mode[NUM_CAMERA_VIEWS];

// Selects the next mode for this view
void SelectNextCameraView(int window) {
  int current = Camera_view_mode[window];

  // If the window has gone away because there's no object, then the current state is none
  if (GetSmallViewer(window) == OBJECT_HANDLE_NONE)
    current = CV_NONE;

  switch (current) {
  case CV_NONE:
    Camera_view_mode[window] = CV_REARVIEW;
    CreateSmallView(window, Player_object->handle, SVF_REARVIEW, 0.0, D3_DEFAULT_ZOOM, -1, TXT_VIEW_REAR);
    if (window == 0)
      Current_pilot.lrearview_enabled = true; // set to true.
    else if (window == 2)
      Current_pilot.rrearview_enabled = true;
    break;

  case CV_REARVIEW: {
    object *objp = ObjGet(Buddy_handle[Player_num]);
    if (window == 0)
      Current_pilot.lrearview_enabled = false; // leaving rearview
    else if (window == 2)
      Current_pilot.rrearview_enabled = false;

    if (objp && objp->type == OBJ_ROBOT) { // Not hidden
      Camera_view_mode[window] = CV_GUIDEBOT;
      CreateSmallView(window, objp->handle, 0, 0.0, D3_DEFAULT_ZOOM, -1, TXT_VIEW_GUIDEBOT);
      break;
    }
    // If no GB, then fall into next case
  }
  case CV_GUIDEBOT:
  case CV_MARKER1:
  case CV_MARKER2:
  case CV_MARKER3:
  case CV_MARKER4:
  case CV_MARKER5:
  case CV_MARKER6:
  case CV_MARKER7:
  case CV_MARKER8: {
    if (window == 0)
      Current_pilot.lrearview_enabled = false; // leaving rearview
    else if (window == 2)
      Current_pilot.rrearview_enabled = false;

    if (Players[Player_num].num_markers > 0) {
      int num = (current == CV_GUIDEBOT) ? 0 : (current - CV_MARKER1) + 1;
      int max = (Game_mode & GM_MULTI) ? 2 : 8; // Why no symbolic constants?  Ask Jason.
      int id = Player_num * 2 + num;

      if (num < max) {
        int i;

        // Search for the marker
        for (i = 0; i <= Highest_object_index; i++) {
          if ((Objects[i].type == OBJ_MARKER) && (Objects[i].id == id))
            break;
        }

        if (i <= Highest_object_index) {
          char buf[25];
          snprintf(buf, sizeof(buf), TXT_VIEW_MARKER, num + 1);

          CreateSmallView(window, Objects[i].handle, 0, 0.0, D3_DEFAULT_ZOOM, -1, buf);
          Camera_view_mode[window] = CV_MARKER1 + num;

          break;
        }
      }
    }
    // If couldn't find marker or have cycled though all, close window
    Camera_view_mode[window] = CV_NONE;
    CloseSmallView(window);
    break;
  }
  default:
    Int3(); // all cases should be handled
  }
}

// Turn off all camera views
// If total reset is true, set all views to none, otherwise kill object view but keep rear views.
void InitCameraViews(bool total_reset) {
  for (int i = 0; i < NUM_CAMERA_VIEWS; i++) {
    if (total_reset || (Camera_view_mode[i] != CV_REARVIEW)) {
      Camera_view_mode[i] = CV_NONE;
    } else { // is rear view, so keep it
      Camera_view_mode[i] = CV_REARVIEW;
      CreateSmallView(i, Player_object->handle, SVF_REARVIEW, 0.0, D3_DEFAULT_ZOOM, -1, TXT_VIEW_REAR);
    }
  }
}

void RestoreCameraRearviews() {
  if (Camera_view_mode[0] != CV_REARVIEW) {
    if (Current_pilot.lrearview_enabled) {
      Camera_view_mode[0] = CV_REARVIEW;
      CreateSmallView(0, Player_object->handle, SVF_REARVIEW, 0.0, D3_DEFAULT_ZOOM, -1, TXT_VIEW_REAR);
    }
  }
  if (Camera_view_mode[2] != CV_REARVIEW) {
    if (Current_pilot.rrearview_enabled) {
      Camera_view_mode[2] = CV_REARVIEW;
      CreateSmallView(2, Player_object->handle, SVF_REARVIEW, 0.0, D3_DEFAULT_ZOOM, -1, TXT_VIEW_REAR);
    }
  }
}

void ProcessButtons() {
  // If dead, any key not handled above will eand the death sequence
  // this shouldn't be called in ReadPlayerControls since the player is DEAD!
  if (Players[Player_num].flags & PLAYER_FLAGS_DEAD) {
    int x, y;
    PollControls();
    if (Controller->get_joy_raw_values(&x, &y) || Controller->get_mouse_raw_values(&x, &y)) {
      // death.
      mprintf(0, "here?");

      if (Total_time_dead < DEATH_RESPAWN_TIME)
        return;

      mprintf(0, "Respawning joystick death.  Death time=%f\n", Total_time_dead);

      if (Game_mode & GM_MULTI)
        MultiSendEndPlayerDeath(); // couldn't this be called from withing EndPlayerDeath()?
      else
        EndPlayerDeath(Player_num);
      // Clear keyboard
      ResetPersistentHUDMessage();
      ddio_KeyFlush();
      if (Controller) {
        Controller->flush();
      }
    }
    return;
  }
}

#define GBC_FIND_ACTIVE_GOAL_0 3  // Find next primary
#define GBC_FIND_SPEW 19          // Find Spew
#define GBC_FIND_POWERUP 20       // Find Powerup
#define GBC_FIND_ENERGY_CENTER 21 // Find energy
#define GBC_ESCORT_SHIP 35        // Escort Ship
#define GBC_EXTINGUISH 36         // Use Extinguisher
#define GBC_GO_WINGNUT 37         // Use Wingnut Powerup
#define GBC_RTYPE 39              // Use Gaurdian Powerup
#define GBC_ANTI_VIRUS 40         // Use Anti-virus Powerup
#define GBC_RETURN_TO_SHIP 43     // Return to ship
// Handles guidebot shortcut keys
void ProcessGuidebotKeys(int key) {
  if (!(key & KEY_SHIFTED))
    return;
  key &= ~KEY_SHIFTED;

  // check to make sure our Guidebot is out of the ship
  object *buddy = ObjGet(Buddy_handle[Player_num]);
  if (!buddy || buddy->type != OBJ_ROBOT) {
    // not out of the ship
    mprintf(0, "Guidebot: mrmph mmrump..mrmph...LET ME OUT OF YOUR SHIP!\n");
    return;
  }
  int command_id = -1;

  switch (key) {
  case KEY_1:
    command_id = GBC_FIND_ACTIVE_GOAL_0;
    break;
  case KEY_2:
    command_id = GBC_FIND_SPEW;
    break;
  case KEY_3:
    command_id = GBC_FIND_POWERUP;
    break;
  case KEY_4:
    command_id = GBC_FIND_ENERGY_CENTER;
    break;
  case KEY_5:
    command_id = GBC_ESCORT_SHIP;
    break;
  case KEY_6:
    command_id = GBC_EXTINGUISH;
    break;
  case KEY_7:
    command_id = GBC_GO_WINGNUT;
    break;
  case KEY_8:
    command_id = GBC_RTYPE;
    break;
  case KEY_9:
    command_id = GBC_ANTI_VIRUS;
    break;
  case KEY_0:
    command_id = GBC_RETURN_TO_SHIP;
    break;
  default:
    // nope
    return;
    break;
  }

  // Process the command
  gb_com command;
  command.action = COM_DO_ACTION;
  command.index = command_id;
  command.ptr = NULL;

  if ((!(Game_mode & GM_MULTI)) || (Netgame.local_role != LR_CLIENT)) {
    AINotify(buddy, AIN_USER_DEFINED, (void *)&command);
  } else {
    MultiSendGuidebotMenuSelection(&command);
  }
}

// Deals with a normal (non-debug) key.  Once the key is handled, this function returns

void ProcessNormalKey(int key) {
  // First do keys that work normally even when dead
  switch (key) {

    // ingnore the modifier keys
  case KEY_LALT:
  case KEY_RALT:
  case KEY_LSHIFT:
  case KEY_RSHIFT:
  case KEY_LCTRL:
  case KEY_RCTRL:
    return;

  case KEY_ESC:
    Game_interface_mode = GAME_EXIT_CONFIRM;
    return;

  case KEY_PAUSE:
    Game_interface_mode = GAME_PAUSE_INTERFACE;
    return;

  case KEY_F1:
    Game_interface_mode = GAME_HELP_INTERFACE;
    return;

  case KEY_F2:
    Game_interface_mode = GAME_OPTIONS_INTERFACE;
    return;

  case KEY_F8:
    if (Game_mode & GM_MULTI) {
      StartHUDInputMessage();
      return;
    }
    break;

  case KEY_SHIFTED + KEY_F8:
    ToggleGameMessageConsole();
    Clear_screen = 4;
    break;

  case KEY_SHIFTED + KEY_F9:
    ToggleHUDMessageConsole();
    Clear_screen = 4; // clears screen.
    break;

    // #ifndef DEMO
  case KEY_F5:
    Game_interface_mode = GAME_TOGGLE_DEMO;
    return;
  case KEY_ALTED + KEY_F5:
    DemoAbort(true);
    return;
    // #endif
    //  case KEY_SHIFTED+KEY_LAPOSTRO:	Game_interface_mode = GAME_TELCOM_CARGO;return;
    //  case KEY_ALTED+KEY_LAPOSTRO: Game_interface_mode = GAME_TELCOM_BRIEFINGS; return;
  case KEY_SHIFTED + KEY_TAB:
    Game_interface_mode = GAME_TELCOM_BRIEFINGS;
    return;
  case KEY_ALTED + KEY_F3:
    if (!Cinematic_inuse) {
      Game_interface_mode = GAME_LOAD_INTERFACE;
      return;
    }
    break;

  case KEY_CTRLED + KEY_F8:
    if (Game_mode & GM_MULTI) {
      StartTeamHUDInputMessage();
      return;
    }
    break;
  case KEY_CTRLED + KEY_1:
  case KEY_CTRLED + KEY_2:
  case KEY_CTRLED + KEY_3:
  case KEY_CTRLED + KEY_4:
  case KEY_CTRLED + KEY_5:
  case KEY_CTRLED + KEY_6:
  case KEY_CTRLED + KEY_7:
  case KEY_CTRLED + KEY_8: {
    int index = key & ~KEY_CTRLED;
    index = index - KEY_1;

    if (Game_mode & GM_MULTI) {
      char str[80];

      mprintf(0, "Printing message %d!\n", index);

      int save_do = Doing_input_message;
      int save_len = HudInputMessageLen;
      strcpy(str, HudInputMessage);

      // strcpy (HudInputMessage,Current_pilot.taunts[index]);
      // decode the text macro by sending it off to the DLL
      // for processesing
      DLLInfo.input_string = Current_pilot.taunts[index];
      DLLInfo.special_data = (uint8_t *)HudInputMessage;
      DLLInfo.iParam = MAX_HUD_INPUT_LEN;
      CallGameDLL(EVT_CLIENT_DECODETEXTMACRO, &DLLInfo);

      Doing_input_message = 1;
      SendOffHUDInputMessage();
      strcpy(HudInputMessage, str);
      HudInputMessageLen = save_len;
      Doing_input_message = save_do;
    }

    break;
  }

  case KEY_PRINT_SCREEN:
  case KEY_SHIFTED + KEY_PRINT_SCREEN:
    mprintf(0, "Doing screenshot!\n");
    DoScreenshot();
    return;

  case KEY_SHIFTED + KEY_MINUS:
  case KEY_MINUS:
    ShrinkWindow();
    return;

  case KEY_SHIFTED + KEY_EQUAL:
  case KEY_EQUAL:
    GrowWindow();
    return;
  case KEY_SPACEBAR:
    if (Players[Player_num].flags & PLAYER_FLAGS_DEAD) {

      if (Total_time_dead < DEATH_RESPAWN_TIME)
        return;

      if (Game_mode & GM_MULTI)
        MultiSendEndPlayerDeath(); // couldn't this be called from withing EndPlayerDeath()?
      else
        EndPlayerDeath(Player_num);

      // Clear keyboard
      ResetPersistentHUDMessage();
      ddio_KeyFlush();
      if (Controller) {
        Controller->flush();
      }

      return;
    }
  }
  if (Demo_flags == DF_PLAYBACK) {
    switch (key) {
    case KEY_C: {
      // goto next player
      int viewer_objnum = Viewer_object - Objects;
      int found = 0;

      for (int i = viewer_objnum + 1; i <= Highest_object_index && !found; i++, i %= (Highest_object_index + 1)) {
        if (Objects[i].type == OBJ_CAMERA) {
          found = 1;
          Viewer_object = &Objects[i];
        }
      }
    } break;
    case KEY_P: {
      // goto next player
      int viewer_objnum = Viewer_object - Objects;
      int found = 0;

      for (int i = viewer_objnum + 1; i <= Highest_object_index && !found; i++, i %= (Highest_object_index + 1)) {
        if (Objects[i].type == OBJ_PLAYER) {
          found = 1;
          Viewer_object = &Objects[i];
        }
      }
    } break;
    case KEY_R: {
      // goto next robot
      int viewer_objnum = Viewer_object - Objects;
      int found = 0;

      for (int i = viewer_objnum + 1; i <= Highest_object_index && !found; i++, i %= (Highest_object_index + 1)) {
        if (Objects[i].type == OBJ_ROBOT) {
          found = 1;
          Viewer_object = &Objects[i];
        }
      }
    } break;
    case KEY_SPACEBAR:
      // Reset view
      Viewer_object = Player_object;
      break;
    case KEY_DOWN:
      Game_paused = true;
      Demo_paused = true;
      break;
    case KEY_RIGHT:
      Demo_do_one_frame = true;
      break;
    case KEY_CTRLED + KEY_LEFT: {
      char sztmp[_MAX_PATH * 2];
      strcpy(sztmp, Demo_fname);
      DemoAbort();
      Game_interface_mode = GAME_DEMO_LOOP;
      Demo_restart = true;
      strcpy(Demo_fname, sztmp);
    } break;
    case KEY_UP:
      Game_paused = false;
      Demo_paused = false;
      break;
    default:
      break;
    }
  }

  // If dead, any key not handled above will eand the death sequence
  if (Players[Player_num].flags & PLAYER_FLAGS_DEAD) {
    return;
  }

  // If dying, only the keys handled above do anything, so bail
  if (Players[Player_num].flags & PLAYER_FLAGS_DYING)
    return;

  // These keys only work when not dying or dead
  ProcessGuidebotKeys(key);

  switch (key) {
  case KEY_SHIFTED + KEY_F1:
    SelectNextCameraView(0);
    return;
  case KEY_SHIFTED + KEY_F2:
    SelectNextCameraView(2);
    return;
    // case KEY_SHIFTED+KEY_F3:		SelectNextCameraView(2);		return;

  case KEY_1:
    SelectWeapon(0);
    return;
  case KEY_2:
    SelectWeapon(1);
    return;
  case KEY_3:
    SelectWeapon(2);
    return;
  case KEY_4:
    SelectWeapon(3);
    return;
  case KEY_5:
    SelectWeapon(4);
    return;
  case KEY_6:
    SelectWeapon(5);
    return;
  case KEY_7:
    SelectWeapon(6);
    return;
  case KEY_8:
    SelectWeapon(7);
    return;
  case KEY_9:
    SelectWeapon(8);
    return;
  case KEY_0:
    SelectWeapon(9);
    return;

  case KEY_F3:
    if (GetHUDMode() != HUD_OBSERVER)
      ToggleHUDMode();
    return;
  case KEY_F12:
    Marker_message = 1;
    StartHUDInputMessage();
    break;
  case KEY_F4: {
    if ((!(Game_mode & GM_MULTI)) || (Netgame.flags & NF_ALLOWGUIDEBOT)) {
      Game_interface_mode = GAME_BUDDY_INTERFACE;
    }
    return;
  } break;
  case KEY_F9:
    //	quick save key!
    if (!Cinematic_inuse) {
      StartGameMenu();
      QuickSaveGame();
      EndGameMenu();
    }
    break;
  case KEY_ALTED + KEY_F2:
    if (!Cinematic_inuse) {
      Game_interface_mode = GAME_SAVE_INTERFACE;
      return;
    }
    break;
  }
}
bool Force_one_texture = false;

#ifdef _DEBUG
static int test_kill_objs = 0;

void InitTestSystems() { test_kill_objs = 0; }

// Tells others that we are cheating
void SendCheaterText() {
  // Notify other players that you're using debug/test keys.  We may want to change this to
  // only send the message for some keys.
  if (Game_mode & GM_MULTI) {
    char str[255];
    snprintf(str, sizeof(str), TXT_CHEATER, Players[Player_num].callsign);

    if (Netgame.local_role == LR_SERVER)
      MultiSendMessageFromServer(GR_RGB(255, 0, 0), str);
    else
      MultiSendMessageToServer(0, str);
  }
}

#include "osiris_dll.h"
#include "audiotaunts.h"

void InitObjectScripts(object *obj, bool call_evt_created = true);

#ifdef _DEBUG
extern bool Cinematics_enabled;
#endif

// Deal with keys that only work for testing & debugging (eg., slew)
void ProcessTestKeys(int key) {
  static int ffret = -1;
  int i;

  // Debug break
  if (key == KEY_SHIFTED + KEY_BACKSP)
    Int3();

  // Handle slew keys
  if (Player_object->control_type == CT_SLEW) {
    switch (key) // Special for slew keys.  Add all new debugging keys to the second switch statement.
    {
    case KEY_PAD5:
      SlewStop(Player_object);
      break;
    case KEY_PAD0:
      SlewResetOrient(Player_object);
      break;
    }
  }

  if (key == (KEY_SHIFTED + KEY_LBRACKET)) {
    MultiSendRequestPlayTaunt(0);
  }

  if (key == (KEY_SHIFTED + KEY_RBRACKET)) {
    MultiSendRequestPlayTaunt(1);
  }

  // All other debug/test keys require the DEBUGGED modifier, so bail if it's not set
  if (!(key & KEY_DEBUGGED))
    return;

  switch (key & ~KEY_DEBUGGED) // for simplicity, do swich on keycode without the flag
  {

  /*
  **************************************************
                            Keys A-Z
  **************************************************
  */
  case KEY_A:

    DoAI = !DoAI;
    AddHUDMessage("AI turned %s.", DoAI ? "on" : "off");
    break;

  case KEY_B:
    Game_show_sphere = (Game_show_sphere + 1) % 4;

    if (Game_show_sphere == 0)
      AddHUDMessage("No visible spheres.");
    else if (Game_show_sphere == 1)
      AddHUDMessage("Wall collision spheres(only encompass first anim frame).");
    else if (Game_show_sphere == 2)
      AddHUDMessage("Spheres for FVI(encompass all anims).");
    else if (Game_show_sphere == 3)
      AddHUDMessage("Object size spheres.");

    break;

  case KEY_C:
    SendCheaterText();
    if (Player_object->effect_info->type_flags & EF_CLOAKED) {
      MakeObjectVisible(Player_object);
      AddHUDMessage("You escape the darkness!");
    } else {
      MakeObjectInvisible(Player_object, 10000);
      AddHUDMessage("You enter the darkness!");
    }
    break;

  case (KEY_C + KEY_SHIFTED): {
    Cinematics_enabled = !Cinematics_enabled;

    AddHUDMessage("Game Cinematics: %s", Cinematics_enabled ? "enabled" : "disabled");
  } break;

  case KEY_D: {

    int GetRankIndex(int pnum, char *rankbuf);
    void ChangeRankIndex(int old_index, int pnum);

    int oldrank = GetRankIndex(1, NULL);
    Players[1].rank += 100;
    ChangeRankIndex(oldrank, 1);

    break;
  }

  case KEY_SHIFTED + KEY_D: {
    int done = 0;
    for (i = 0; i <= Highest_room_index && !done; i++) {
      for (int t = 0; t < Rooms[i].num_faces && !done; t++) {
        if (GameTextures[Rooms[i].faces[t].tmap].flags & TF_LIGHT) {
          DestroyLight(i, t);
          done = 1;
        }
      }
    }
    break;
  }

  case KEY_E:
    // ends level prematurely
    // this is only for single player
    if (Game_mode & GM_MULTI) {
      AddHUDMessage("Press F6 to end a multiplayer level");
    } else {
      SetGameState(GAMESTATE_LVLEND);
    }
    break;

  case KEY_E + KEY_ALTED:
    // restart level
    if ((!(Game_mode & GM_MULTI)) || Netgame.local_role == LR_SERVER) {
      SetGameState(GAMESTATE_LVLFAILED);
    }
    break;

  case KEY_F:
    Hud_stat_mask ^= STAT_FPS;
    break;

    /*case KEY_G:
            {
                    char dmb_msg[100];
                    mprintf(0,"Current Gametime is %f\n",Gametime);
                    snprintf(dmb_msg,sizeof(dmb_msg),"Current Gametime is %f\n",Gametime);
                    AddHUDMessage(dmb_msg);
            }
            break;*/

  case KEY_G: {
    if (Player_object->type == OBJ_OBSERVER) {
      if (Game_mode & GM_MULTI)
        MultiSendRequestToObserve(OBSERVER_MODE_ROAM, 0, 0);
      else
        PlayerStopObserving(Player_num);

    } else {
      if (Game_mode & GM_MULTI)
        MultiSendRequestToObserve(OBSERVER_MODE_ROAM, 1, 0);
      else
        PlayerSwitchToObserver(Player_num, OBSERVER_MODE_ROAM);
    }
  } break;

  case KEY_H:
    HUD_disabled = !HUD_disabled;
    if (!HUD_disabled)
      AddHUDMessage(TXT_HUDENABLED);
    break;

  case KEY_I:

    SendCheaterText();
    if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE) {
      MakePlayerVulnerable(Player_num);
      AddHUDMessage("Your mother wont protect you now!");
    } else {
      MakePlayerInvulnerable(Player_num, 10000);
      AddHUDMessage("You're a wimp!");
    }
    break;

  case KEY_J: {
    object *obj = &Objects[Player_num];
    for (i = 0; i < 21; i++) {
      if (obj->dynamic_wb[i].flags & DWBF_QUAD) {
        obj->dynamic_wb[i].flags &= ~DWBF_QUAD;
        AddHUDMessage("Quad Flag Turned Off");
      } else {
        obj->dynamic_wb[i].flags |= DWBF_QUAD;
        AddHUDMessage("Quad Flag Turned On");
      }
    }

  } break;

  case KEY_K: {
    if (Game_mode & GM_MULTI)
      break;

    for (i = 0; i < MAX_OBJECTS; i++) {
      if (test_kill_objs == 0 && Objects[i].type == OBJ_ROBOT) {
        DoAI = 0;
        ObjDelete(i);
        AddHUDMessage("All robots dead!");
      } else if (test_kill_objs == 1 && Objects[i].type == OBJ_CLUTTER) {
        ObjDelete(i);
        AddHUDMessage("All clutter gone!");
      } else if (test_kill_objs == 2 && Objects[i].type == OBJ_POWERUP) {
        ObjDelete(i);
        AddHUDMessage("All powerups gone!");
      }
    }
    test_kill_objs++;

    test_kill_objs = test_kill_objs % 3;

    break;
  }

  case KEY_L:
    Terrain_LOD_engine_off = !Terrain_LOD_engine_off;
    AddHUDMessage("Terrain LOD engine turned %s", Terrain_LOD_engine_off ? "OFF" : "ON");
    break;

  case KEY_M:
    Render_portals = 1 - Render_portals;
    break;

  case KEY_N:
    if (Current_level && Current_level->filename) {
      vector player_pos = Player_object->pos;
      matrix player_orient = Player_object->orient;
      int player_roomnum = Player_object->roomnum;

      // Load the level
      LoadAndStartCurrentLevel();

      // Restore player position
      ObjSetPos(Player_object, &player_pos, player_roomnum, &player_orient, true);
    }
    break;

  case KEY_O:
    Outline_mode ^= OM_ON;
    AddHUDMessage("Outline mode turned %s", OUTLINE_ON(0) ? "ON" : "OFF");
    break;

  case KEY_O + KEY_SHIFTED:
    Outline_mode = OM_ON + OM_ALL;
    AddHUDMessage("All outline options turned on.");
    break;

  case KEY_P:
    MakeTestPath(&Player_object->roomnum, &Player_object->pos);
    break;

  case KEY_Q:
    if (StateLimited) {
      StateLimited = 0;
      AddHUDMessage("State limited turned off.");
    } else {
      StateLimited = 1;
      AddHUDMessage("State limited turned on.");
    }
    break;

  case KEY_R:
    if (Weather.flags & WEATHER_FLAGS_SNOW) {
      Weather.flags &= ~WEATHER_FLAGS_SNOW;
      AddHUDMessage("Snow turned off.");
    } else {
      Weather.flags |= WEATHER_FLAGS_SNOW;
      AddHUDMessage("Snow turned on.");
    }
    break;

  case KEY_S:
    if (Sound_system.IsActive()) {
      AddHUDMessage("Sound system off.");
      Sound_system.KillSoundLib(false);
    } else {
      AddHUDMessage("Sound system on.");
      Sound_system.InitSoundLib(Descent, Sound_mixer, Sound_quality, false);
    }
    break;

  case KEY_S + KEY_SHIFTED: {
    // extern spewinfo SpewEffects[MAX_SPEW_EFFECTS];
    int count;

    AddHUDMessage("Spewers Killed");

    for (count = 0; count < MAX_SPEW_EFFECTS; count++) {
      SpewEffects[count].inuse = 0;
    }

  } break;

  case KEY_T:
    if (Timedemo_frame == -1)
      Timedemo_frame = 0;
    break;

  case KEY_U:
    AIPath_test_end_room = Player_object->roomnum;
    AIPath_test_end_pos = Player_object->pos;
    break;

  case KEY_V:
    // TODO: should this actually be a fallthrough?

  case KEY_W:
    if (Weather.flags & WEATHER_FLAGS_LIGHTNING) {
      Weather.flags &= ~WEATHER_FLAGS_LIGHTNING;
      AddHUDMessage("Lighting turned off.");

    } else {
      Weather.flags |= WEATHER_FLAGS_LIGHTNING;
      Weather.lightning_sequence = 0;
      Weather.lightning_rand_value = 70;
      Weather.lightning_interval_time = .01f;
      AddHUDMessage("Lighting turned on.");
    }
    break;

  case KEY_X: {
    SendCheaterText();
    Players[Player_num].energy = 200.0f;
    Players[Player_num].weapon_flags = 0xFFFFFFFF;
    int i;

    for (i = 0; i < MAX_PLAYER_WEAPONS; i++)
      Players[Player_num].weapon_ammo[i] = Ships[Players[Player_num].ship_index].max_ammo[i];

    Players[Player_num].afterburn_time_left = AFTERBURN_TIME;

    AddHUDMessage("All weapons!");

    // add all the countermeasures
    if (Game_mode & GM_MULTI)
      break;
    int c_id, b_id, s_id, g_id, p_id;
    c_id = FindWeaponName("Chaff");
    b_id = FindWeaponName("Betty");
    s_id = FindWeaponName("SeekerMine");
    g_id = FindWeaponName("Gunboy");
    p_id = FindWeaponName("ProxMine");

    int c_pid, b_pid, s_pid, g_pid, p_pid;
    c_pid = FindObjectIDName("chaff");
    b_pid = FindObjectIDName("Betty4pack");
    s_pid = FindObjectIDName("Seeker3pack");
    g_pid = FindObjectIDName("gunboypowerup");
    p_pid = FindObjectIDName("ProxMinepowerup");

    if (c_pid == -1)
      c_pid = FindObjectIDName("Shield");
    if (b_pid == -1)
      b_pid = FindObjectIDName("Energy");
    if (s_pid == -1)
      s_pid = FindObjectIDName("Shield");
    if (g_pid == -1)
      g_pid = FindObjectIDName("Energy");
    if (p_pid == -1)
      p_pid = FindObjectIDName("Shield");

    object *objp = &Objects[Players[Player_num].objnum];
    for (i = 0; i < 30; i++) {
      if (c_id != -1)
        Players[Player_num].counter_measures.Add(OBJ_WEAPON, c_id, objp, OBJ_POWERUP, c_pid);
      if (b_id != -1)
        Players[Player_num].counter_measures.Add(OBJ_WEAPON, b_id, objp, OBJ_POWERUP, b_pid);
      if (s_id != -1)
        Players[Player_num].counter_measures.Add(OBJ_WEAPON, s_id, objp, OBJ_POWERUP, s_pid);
      if (g_id != -1)
        Players[Player_num].counter_measures.Add(OBJ_WEAPON, g_id, objp, OBJ_POWERUP, g_pid);
      if (p_id != -1)
        Players[Player_num].counter_measures.Add(OBJ_WEAPON, p_id, objp, OBJ_POWERUP, p_pid);
    }

    break;
  }

  case KEY_Y:
    Physics_player_verbose = 1 - Physics_player_verbose;
    if (Physics_player_verbose)
      AddHUDMessage("Verbose player physics info\n");
    else
      AddHUDMessage("Player physics info off\n");
    break;

  case KEY_Z: {
    // Inventory test
    int id, objnum;

    id = FindObjectIDName("Betty4Pack");
    objnum = ObjCreate(OBJ_POWERUP, id, Player_object->roomnum, &Player_object->pos, &Player_object->orient);

    if (objnum != -1) {
      if (Game_mode & GM_MULTI)
        MultiSendObject(&Objects[objnum], false);

      InitObjectScripts(&Objects[objnum], true);
      Players[Player_num].inventory.AddObject(Objects[objnum].handle, true);
    }
  } break;

  case KEY_Z + KEY_ALTED: {
    // look for a betty4pack and remove the sucker
    int id;
    id = FindObjectIDName("Betty4Pack");
    for (i = 0; i < MAX_OBJECTS; i++) {
      if (Objects[i].type == OBJ_DUMMY && Objects[i].dummy_type == OBJ_POWERUP && Objects[i].id == id) {
        // here's a betty
        mprintf(0, "Killing a betty\n");
        SetObjectDeadFlag(&Objects[i], true);
      }
    }

  } break;
    /*
    **************************************************
                              Keypad Keys
    **************************************************
    */

  case KEY_PAD0: {
    Game_update_attach = 1 - Game_update_attach;

    if (Game_update_attach) {
      mprintf(0, "Update attach on\n");
    } else {
      mprintf(0, "Update attach off\n");
    }
  } break;

  case KEY_PAD1: {
    Game_do_flying_sim = 1 - Game_do_flying_sim;
    if (Game_do_flying_sim) {
      mprintf(0, "Game_do_flying_sim on\n");
    } else {
      mprintf(0, "Game_do_flying_sim off\n");
    }
  } break;

  case KEY_PAD2: {
    Game_do_walking_sim = 1 - Game_do_walking_sim;
    if (Game_do_walking_sim) {
      mprintf(0, "Game_do_walking_sim on\n");
    } else {
      mprintf(0, "Game_do_walking_sim off\n");
    }
  } break;

  case KEY_PAD3: {
    Game_do_vis_sim = 1 - Game_do_vis_sim;
    if (Game_do_vis_sim) {
      mprintf(0, "Game_do_vis_sim on\n");
    } else {
      mprintf(0, "Game_do_vis_sim off\n");
    }
  } break;

  case KEY_PAD4: {
    Game_do_ai_movement = 1 - Game_do_ai_movement;
    if (Game_do_ai_movement) {
      mprintf(0, "Game_do_ai_movement on\n");
    } else {
      mprintf(0, "Game_do_ai_movement off\n");
    }
  } break;

  case KEY_PAD5: {
    Game_do_ai_vis = 1 - Game_do_ai_vis;
    if (Game_do_ai_vis) {
      mprintf(0, "Game_do_ai_vis on\n");
    } else {
      mprintf(0, "Game_do_ai_vis off\n");
    }
  } break;

  case KEY_PAD6: {
    if (AI_debug_robot_do) {
      AI_debug_robot_do = false;
      mprintf(0, "AI Debug Info Off\n");
    } else {
      AI_debug_robot_do = true;
      mprintf(0, "AI Debug Info On\n");
    }
  } break;

  case KEY_PAD7: {
    bool killed_something = false;
    int killed_count = 0;
    int i, a;
    for (i = 0; i < MAX_OBJECTS; i++) {
      if (Objects[i].type == OBJ_ROBOT || (Objects[i].type == OBJ_BUILDING && Objects[i].ai_info)) {
        // Now, kill all robots of this type!
        AddHUDMessage("Killing all %s robots!", Object_info[Objects[i].id].name);
        for (a = 0; a < MAX_OBJECTS; a++) {
          if (Objects[a].id == Objects[i].id) {
            SetObjectDeadFlag(&Objects[a]);
            killed_something = true;
            killed_count++;
          }
        }
        /*
        SetObjectDeadFlag(&Objects[i]);
        AddHUDMessage("Killed object %d!",i);

        if(killed_count>4)
                break;
        */
      }
      if (killed_something)
        break;
    }
    if (!killed_something)
      AddHUDMessage("Nothing to kill!");
    else
      mprintf(0, "Killed %d objects of type %s!\n", killed_count, Object_info[Objects[i].id].name);
  } break;
    /*
    **************************************************
                              Number Keys
    **************************************************
    */

  case KEY_1: {
    // goto prev viewer
    int viewer_objnum = Viewer_object - Objects;
    int found = 0;

    for (i = viewer_objnum - 1; i >= 0 && !found; i--, i < 0 ? i = Highest_object_index : i = i) {
      if (Objects[i].type == OBJ_POWERUP || Objects[i].type == OBJ_PLAYER || Objects[i].type == OBJ_ROBOT ||
          Objects[i].type == OBJ_CLUTTER || Objects[i].type == OBJ_BUILDING || Objects[i].type == OBJ_MARKER) {
        found = 1;
        Viewer_object = &Objects[i];
      }
    }

    AddHUDMessage("Viewer set to previous object.");

  } break;

  case KEY_2: {
    // reset viewer
    AddHUDMessage("Viewer set to player object.");
    Viewer_object = Player_object;
  } break;

  case KEY_3: {
    // goto next viewer
    int viewer_objnum = Viewer_object - Objects;
    int found = 0;

    for (i = viewer_objnum + 1; i <= Highest_object_index && !found; i++, i %= (Highest_object_index + 1)) {
      if (Objects[i].type == OBJ_POWERUP || Objects[i].type == OBJ_PLAYER || Objects[i].type == OBJ_ROBOT ||
          Objects[i].type == OBJ_CLUTTER || Objects[i].type == OBJ_BUILDING || Objects[i].type == OBJ_MARKER) {
        found = 1;
        Viewer_object = &Objects[i];
      }
    }

    AddHUDMessage("Viewer set to next object.");
  } break;

  case KEY_4:
    if (Tracking_FVI)
      Tracking_FVI = false;
    else
      Tracking_FVI = true;

    AddHUDMessage("Tracking FVI now set to %s.", Tracking_FVI ? "on" : "off");

    break;

  case KEY_6:
    Render_FOV -= 1;
    AddHUDMessage("FOV is now %f", Render_FOV);
    break;

  case KEY_7:
    Render_FOV += 1;
    AddHUDMessage("FOV is now %f", Render_FOV);
    break;

  case KEY_8:
    Render_FOV = D3_DEFAULT_FOV;
    AddHUDMessage("FOV has been reset to %f", Render_FOV);
    break;

  case KEY_9:
    Force_one_texture = !Force_one_texture;
    break;

    /*
    **************************************************
                              Function Keys
    **************************************************
    */

  case KEY_F5:
    D3MusicToggle();
    break;

  case KEY_F6: {
    vector test_pos;
    fvi_info hit_info;
    fvi_query fq;
    int fate;
    int this_key = key & ~KEY_DEBUGGED;

    test_pos = Player_object->pos + Player_object->orient.fvec * 1000000.0f;

    fq.p0 = &Player_object->pos;
    fq.startroom = Player_object->roomnum;
    fq.p1 = &test_pos;
    fq.rad = 0.0;
    fq.thisobjnum = OBJNUM(Player_object);
    fq.ignore_obj_list = NULL;
    if (this_key == KEY_F6)
      fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_RENDER_THROUGH_PORTALS;
    else
      fq.flags = 0;

    fate = fvi_FindIntersection(&fq, &hit_info);

    switch (fate) {
    case HIT_NONE:
      mprintf(0, "Hit nothing\n");
      break;
    case HIT_WALL:
      mprintf(0, "Hit wall\n");
      break;
    case HIT_OBJECT:
      mprintf(0, "Hit Object %d\n", hit_info.hit_object);
      break;
    case HIT_TERRAIN:
      mprintf(0, "Hit Terrain %d\n", CELLNUM(hit_info.hit_room));
      break;
    case HIT_OUT_OF_TERRAIN_BOUNDS:
      mprintf(0, "Hit nothing: Leaving Terrain\n");
      break;
    case HIT_SPHERE_2_POLY_OBJECT:
      mprintf(0, "Hit Poly_object\n");
      break;
    default:
      mprintf(0, "Hit %d not printed, add to list\n", fate);
      break;
    }

    if (fate) {
      int objnum;

      objnum = ObjCreate(OBJ_DEBUG_LINE, 1, Player_object->roomnum, &Player_object->pos, NULL);
      if (objnum >= 0) { // DAJ -1FIX
        Objects[objnum].rtype.line_info.end_pos = hit_info.hit_pnt;
        Objects[objnum].size = vm_VectorDistance(&Player_object->pos, &hit_info.hit_pnt);
        ObjSetAABB(&Objects[objnum]);
      }
    }

    Sound_system.CheckAndForceSoundDataAlloc(SOUND_REFUELING);
    Sound_system.PlayStream(0, SoundFiles[Sounds[SOUND_REFUELING].sample_index].sample_8bit,
                            SoundFiles[Sounds[SOUND_REFUELING].sample_index].sample_length, SIF_STREAMING_8_M, 1.0,
                            NULL);
  } break;

  case KEY_F7:
    // Toggle Music Debug Info!!
    Music_debug_verbose = !Music_debug_verbose;
    break;

  case KEY_F8:
    D3MusicSetRegion((D3MusicGetRegion() > 0) ? 0 : 1);
    break;

  case KEY_F9: {
    vector vec = Player_object->pos + (Player_object->orient.fvec * 20);
    if (BSPRayOccluded(&Player_object->pos, &vec, MineBSP.root))
      mprintf(0, "Occluded!\n");
    else
      mprintf(0, "NOT occluded!\n");
  } break;

  case KEY_F10:
    int ObjInitTypeSpecific(object * objp, bool reinitializing);
    FreeCockpit();
    CloseShipHUD();
    Players[0].ship_index = GetNextShip(Players[0].ship_index);
    AddHUDMessage("Player ship set to %s\n", Ships[Players[0].ship_index].name);
    ObjInitTypeSpecific(Player_object, 0); // reset physics, model, etc.
    InitShipHUD(Players[0].ship_index);
    InitCockpit(Players[0].ship_index);
    if (GetHUDMode() == HUD_COCKPIT)
      SetHUDMode(HUD_COCKPIT);
    else if (GetHUDMode() == HUD_FULLSCREEN)
      SetHUDMode(HUD_FULLSCREEN);
    break;

  case KEY_F11:
    /*
                    if(Player_object->control_type != CT_SOAR)
                    {
                            AddHUDMessage("SOAR ON.  Auto-pilot engaged.");

                            SetObjectControlType(Player_object, CT_SOAR);
                            SoarCreateAgent(OBJNUM(Player_object), 0);
                    }
                    else
                    {
                            AddHUDMessage("SOAR OFF.  Manual control returned.");

                            SoarDestroyAgent(OBJNUM(Player_object), 0);
                            SetObjectControlType(Player_object, CT_FLYING);
                    }
                    break;

            case KEY_F12:
            */
    {
      char test[MAX_MATCEN_NAME_LEN];
      bool f_name_changed;

      strcpy(test, "test");

      int m_id = CreateMatcen(test, &f_name_changed);

      if (m_id >= 0) {
        int id = FindObjectIDName("Tubbs");
        int p = 100;
        float t = 5.0f;
        int m = 5;

        mprintf(0, "Matcen alive!\n");

        vector centerPt = Player_object->pos + (Player_object->orient.fvec * 2.0f);
        Matcen[m_id]->SetAttachType(MT_ROOM);
        Matcen[m_id]->SetAttach(Player_object->roomnum);
        Matcen[m_id]->SetCreateRoom(Player_object->roomnum);
        Matcen[m_id]->SetCreatePnt(&centerPt);
        Matcen[m_id]->SetControlType(MPC_WHILE_PLAYER_NEAR);

        Matcen[m_id]->SetMaxProd(12);
        Matcen[m_id]->SetNumProdTypes(3);
        Matcen[m_id]->SetMaxAliveChildren(1);
        Matcen[m_id]->SetProdInfo(0, &id, &p, &t, &m);
        id = FindObjectIDName("Sixgun");
        Matcen[m_id]->SetProdInfo(1, &id, &p, &t, &m);
        id = FindObjectIDName("bladescaled");
        Matcen[m_id]->SetProdInfo(2, &id, &p, &t, &m);

        Matcen[m_id]->SetStatus(MSTAT_ACTIVE | MSTAT_RANDOM_PROD_ORDER, true);
      } else {
        mprintf(0, "Nope!\n");
      }
    }
    break;

  /*
  **************************************************
                            Other Keys
  **************************************************
  */
  case KEY_TAB:
    Game_interface_mode = GAME_DEBUGGRAPH_INTERFACE;
    break;

  case KEY_COMMA:
    rtp_StartLog();
    break;

  case KEY_PERIOD:
    rtp_StopLog();
    break;

  case KEY_LAPOSTRO:
    Show_osiris_debug = !Show_osiris_debug;
    AddHUDMessage("%s osiris debug messages", (Show_osiris_debug) ? "Enabling" : "Disabling");
    break;

  case KEY_BACKSLASH:
    // attempt to restore video
    if (DebugBreak_callback_stop)
      (*DebugBreak_callback_stop)();
    if (DebugBreak_callback_resume)
      (*DebugBreak_callback_resume)();
    break;

  case KEY_SPACEBAR:
    if (Player_object->control_type == CT_FLYING) {
      SetObjectControlType(Player_object, CT_SLEW);
      Player_object->movement_type = MT_NONE;
      SlewStop(Player_object);
      AddHUDMessage("Slew on");
    } else {
      SlewStop(Player_object);
      SetObjectControlType(Player_object, CT_FLYING);
      Player_object->movement_type = MT_PHYSICS;
      AddHUDMessage("Physics on");
    }
    break;

  case KEY_BACKSP: {
    if (!ROOMNUM_OUTSIDE(Player_object->roomnum)) {
      int i;

      Game_show_portal_vis_pnts = 1 - Game_show_portal_vis_pnts;

      mprintf(0, "Vis info for room %d\n", Player_object->roomnum);

      for (i = 0; i <= Highest_room_index; i++) {
        if (BOA_IsVisible(i, Player_object->roomnum)) {
          mprintf(0, "%d can see you in %d\n", i, Player_object->roomnum);
        }
      }

      for (i = Highest_room_index + 1; i <= Highest_room_index + 8; i++) {
        if (BOA_IsVisible(i, Player_object->roomnum)) {
          mprintf(0, "Terrain %d can see you in %d\n", i - Highest_room_index - 1, Player_object->roomnum);
        }
      }
    }
  } break;
  }
}
#endif

// Sends this key to the multiplayer game DLL
// Return:	true means to handle the key normally
//				false means to do no further processing on this key
bool SendKeyToGameDLL(int key) {
  DLLInfo.input_key = key;

  DLLInfo.iRet = 0;
  CallGameDLL(EVT_CLIENT_KEYPRESS, &DLLInfo);

  if (DLLInfo.iRet != 0) {

    ddio_KeyFlush(); // keep the controls stuff from getting any keys
    return 0;        // Don't process this key
  }

  // Handle key normally
  return 1;
}

void DemoCheats(int key);
// Get and handle all pending keys
void ProcessKeys() {
  int key;

  if (Dedicated_server)
    return; // No key processing for dedicated server!

  //	if we are in some menu then don't process game keys!
  if (Game_interface_mode != GAME_INTERFACE || Menu_interface_mode)
    return;

  // Process all pending keys
  while ((key = ddio_KeyInKey()) != 0) {

    // Where does this belong?
    //	do d3x debugging console
    // D3XDebugIO(key);

    // If inputting a multiplayer message, send keys there
    if (Doing_input_message) {
      DoHUDInputMessageKey(key);
      continue;
    }

    // If multiplayer, send the key to the game DLL
    if (Game_mode & GM_MULTI) {
      if (!SendKeyToGameDLL(key)) // returns true if should keep processing this key
        continue;                 // the DLL says not process this key
    }

    // Handle normal key
    ProcessNormalKey(key);

// Handle debugging & test keys
#ifdef _DEBUG
    ProcessTestKeys(key);
#endif

    // #ifdef DEMO
    DemoCheats(key);
    // #endif
  }
}

// Render the world into a game window
// Parameters:	viewer - if not null, this object disabled from rendering.  Not used otherwise.
//					viewer_eye - where we're rendering from
//					viewer_roomnum - the roomnum viewer_eye is in
//					viewer_orient - the oriention for this view
//					zoom - the zoom for this view
//					rear_view - if true, we're looking out the rear of this object

#ifdef _DEBUG
extern void DrawRoomVisPnts(object *obj);
#endif

void GameRenderWorld(object *viewer, vector *viewer_eye, int viewer_roomnum, matrix *viewer_orient, float zoom,
                     bool rear_view) {
  matrix temp_orient, save_orient;

  // Get the viewer orientation
  if (rear_view) {
    temp_orient.fvec = -viewer_orient->fvec;
    temp_orient.rvec = -viewer_orient->rvec;
    temp_orient.uvec = viewer_orient->uvec;
    viewer_orient = &temp_orient;
    save_orient = viewer->orient;
    viewer->orient = temp_orient;
  }

  // Start the 3D
  g3_StartFrame(viewer_eye, viewer_orient, zoom);

  // Reset fog,zbuffer
  Num_fogged_rooms_this_frame = 0;
  rend_SetZBufferState(1);
  rend_SetZBufferWriteMask(1);

  // Reset our postrenderings
  ResetPostrenderList();

  // Render!
  if (ROOMNUM_OUTSIDE(viewer_roomnum))
    RenderTerrain(0);
  else {
    bool flag_automap = (viewer != NULL) ? (viewer->type != OBJ_ROBOT) : 0;
    RenderMine(viewer_roomnum, flag_automap, 0);

#ifdef _DEBUG
    if (Game_show_portal_vis_pnts) {
      DrawRoomVisPnts(Player_object);
    }
#endif
  }

  // Done with 3D
  PostRender(viewer_roomnum);
  g3_EndFrame();

  // Restore viewer orientation
  if (rear_view)
    viewer->orient = save_orient;
}

// Render into the big window
void GameDrawMainView() {
  extern bool Guided_missile_smallview; // smallviews.cpp

  bool rear_view = 0;
  object *save_view;

  DebugBlockPrint("SR");

  // Start rendering
  StartFrame(false);

  // Set guided view
  if (!Cinematic_inuse && Players[Player_num].guided_obj != NULL && !Guided_missile_smallview) {
    save_view = Viewer_object;
    Viewer_object = Players[Player_num].guided_obj;

  } else if ((Viewer_object == Player_object) && (Players[Player_num].flags & PLAYER_FLAGS_REARVIEW))
    rear_view = 1;

  // Draw the world
  Rendering_main_view = true;
  GameRenderWorld(Viewer_object, &Viewer_object->pos, Viewer_object->roomnum, &Viewer_object->orient, Render_zoom,
                  rear_view);
  Rendering_main_view = false;

  // Restore viewer object if guided
  if (!Cinematic_inuse && Players[Player_num].guided_obj != NULL && !Guided_missile_smallview)
    Viewer_object = save_view;

  // Room changes
  DoRoomChangeFrame();

  // Draw Matcen Effects
  DoMatcensRenderFrame();

  // Draw any render events
  ProcessRenderEvents();

  // We're done with this window
  EndFrame();

  DebugBlockPrint("DR");
}

// Added by Samir
#define HUD_RENDER_ZOOM 0.56f

// Do Cockpit/Hud
void GameDrawHud() {
  //	Start frame and 3d frame
  StartFrame(false);
  g3_StartFrame(&Viewer_object->pos, &Viewer_object->orient, HUD_RENDER_ZOOM);

  //	render HUD
  RenderHUDFrame();

  //	End frame
  g3_EndFrame();
  EndFrame();

  //	render auxillary consoles
  StartFrame(0, 0, Max_window_w, Max_window_h, false);
  g3_StartFrame(&Viewer_object->pos, &Viewer_object->orient, HUD_RENDER_ZOOM);

  RenderAuxHUDFrame();

  //	End frame
  g3_EndFrame();
  EndFrame();
}

// Draw a frame of the game
void GameRenderFrame(void) {
  bool no_render = false;
  AI_NumRendered = 0;
  AI_NumHostileAlert = 0;

  if (Dedicated_server)
    return;

#ifndef RELEASE
  Mine_depth = 0;
#endif

  // increase our timing for the powerup sparkles, used globally by all
  Last_powerup_sparkle_time += Frametime;

  PreUpdateAllLightGlows();

  // Don't render if receiving data
  if ((Game_mode & GM_MULTI) && NetPlayers[Player_num].sequence != NETSEQ_PLAYING) {
    no_render = true;
    ShowProgressScreen(TXT_RECEIVINGDATA, NULL, 0);
  }

  // Generate "shaken" view for player
  if (!Game_paused)
    ShakePlayer();

  rend_SetZBufferState(1);
  rend_SetZBufferWriteMask(1);

  // clear screen if needed
  if (Clear_screen) {
    StartFrame(0, 0, Max_window_w, Max_window_h, false);
    rend_ClearScreen(GR_BLACK);
    EndFrame();
    Clear_screen--;
  }

  // Render the mine
  if (!no_render) {
    // render preliminary hud view (for dirty rectangles)
    if (Small_hud_flag) { // small hud flag is set in RenderHUDFrame in GameDrawHud.
      StartFrame(0, 0, Max_window_w, Max_window_h, false);
      RenderPreHUDFrame();
      EndFrame();
    }

    // Draw the big 3d view
    GameDrawMainView();

    // Do the small views.  These should be before GameDrawHUD() for the small windows
    DrawSmallViews();

    // Do Cockpit/Hud
    if (!HUD_disabled)
      GameDrawHud();

    // Render Ingame Cinematics
    Cinematic_RenderFrame();

    // Process the debug visual graph
    DebugGraph_Render();

    if (Display_renderer_stats) {
      // display some rendering stats
      tRendererStats stats;
      rend_GetStatistics(&stats);
      grtext_SetFont(HUD_FONT);

      char buffer[128];
      int x, y, height;

      x = 15;
      y = 240;
      StartFrame(0, 0, Game_window_w, Game_window_h);
      rend_StartFrame(0, 0, Game_window_w, Game_window_h, 0);
      height = grfont_GetHeight(HUD_FONT) + 1;
      snprintf(buffer, sizeof(buffer), "Polys=%d", stats.poly_count);
      RenderHUDText(GR_RGB(255, 40, 40), 255, 1, x, y, buffer);
      y += height;
      snprintf(buffer, sizeof(buffer), "Verts=%d", stats.vert_count);
      RenderHUDText(GR_RGB(255, 40, 40), 255, 1, x, y, buffer);
      y += height;
      snprintf(buffer, sizeof(buffer), "Uploads=%d", stats.texture_uploads);
      RenderHUDText(GR_RGB(255, 40, 40), 255, 1, x, y, buffer);
      y += height;
      grtext_Flush();
      EndFrame();
    }
  }

  // Do UI Frame
  if (Game_interface_mode == GAME_INTERFACE && !Menu_interface_mode) {
    DoUIFrameWithoutInput();
    rend_Flip();
  }

  // Restore normal view
  if (!Game_paused)
    UnshakePlayer();

  // Done with the dynamic lights
  ClearDynamicLightmaps();

  // Increment frame count
  FrameCount++;
  frames_one_second++;

  //  Update our glows
  PostUpdateAllLightGlows();

  // Reset our powerup sparkle time if it has overflowed
  while (Last_powerup_sparkle_time >= POWERUP_SPARKLE_INTERVAL) {
    Last_powerup_sparkle_time -= POWERUP_SPARKLE_INTERVAL;
  }
}

void GameProcessMusic() {
  // the last game state in the sequencer.
  extern tGameState Last_game_state;

  if (Last_game_state == GAMESTATE_LVLSTART) {
    Game_music_info.started_level = true;
  } else {
    Game_music_info.started_level = false;
  }

  // player_damaged set in damage.cpp DecreasePlayerShields.

  if ((Players[Player_num].flags & PLAYER_FLAGS_DYING) || (Players[Player_num].flags & PLAYER_FLAGS_DEAD)) {
    Game_music_info.player_dead = true;
  } else {
    Game_music_info.player_dead = false;
  }

  Game_music_info.n_hostiles = AI_NumHostileAlert;
  Game_music_info.frametime = Frametime;

  D3MusicDoFrame(&Game_music_info);
}

// variables for Frametime system

// timer_GetMSTime()
// float last_timer=0.0;
int timer_paused = 0;

// Stop the Frametime clock
void StopTime() {
  if (!timer_paused) {
    last_timer = timer_GetMSTime() - last_timer;
    if (last_timer < 0) {
      // Int3();
      last_timer = 0;
    }
  }

  timer_paused++;
}

// Restart the Frametime clock
void StartTime() {
  if (timer_paused == 0)
    return;

  timer_paused--;

  ASSERT(timer_paused >= 0);

  if (!timer_paused)
    last_timer = timer_GetMSTime() - last_timer;
}

float Min_frametime = 500;
float Max_frametime = 0;
float Avg_frametime = 0;
uint32_t Frames_counted = 0;

// Compute how long last frame took
void CalcFrameTime(void) {
  int64_t current_timer;

  if (timer_paused)
    return;

  current_timer = timer_GetMSTime();
  if (current_timer >= last_timer) {
    Frametime = static_cast<float>(current_timer - last_timer) / 1000.0f;
  } else {
    Frametime = 0.0f;
  }

  last_timer = current_timer;

  if (Min_frametime > Frametime) {
    mprintf(0, "This was the fastest frame yet!\n");
    Min_frametime = Frametime - Demo_frame_ofs;
  } else if (Max_frametime < Frametime) {
    mprintf(0, "This was the slowest frame yet!\n");
    Max_frametime = Frametime - Demo_frame_ofs;
  }
  Frames_counted++;
  Avg_frametime += (Frametime - Demo_frame_ofs);
}

//	called before first call to StopTime, StartTime or CalcFrameTime
void InitFrameTime(void) {

  if (timer_paused) {
    mprintf(1, "Timer paused in InitFrameTime()\n");
  }
  last_timer = timer_GetMSTime();
  timer_paused = 0;
}

// Pauses game
void PauseGame() {
  mprintf(0, "Game paused.\n");
  Game_paused = true;

  D3MusicPause();
  Sound_system.PauseSounds();
  StopTime();
}

//	resumes game operation.
void ResumeGame() {
  StartTime();
  Game_paused = false;
  Sound_system.ResumeSounds();
  D3MusicResume();
  mprintf(0, "Game resumed.\n");
}

// Data for terrain sound
terrain_sound_band Terrain_sound_bands[NUM_TERRAIN_SOUND_BANDS];
int Terrain_sound_handles[NUM_TERRAIN_SOUND_BANDS];
float Terrain_sound_fade; // used for transitions between inside & outside

#define FADE_TIME 1.0

// Update the sound on the terrain
void UpdateTerrainSound() {
  // Update fade in/out (for inside/outside transitions)
  if (OBJECT_OUTSIDE(Player_object)) {
    if (Terrain_sound_fade < 1.0) { // fading in
      Terrain_sound_fade += Frametime / FADE_TIME;
      if (Terrain_sound_fade > 1.0)
        Terrain_sound_fade = 1.0;
    }
  } else {
    if (Terrain_sound_fade > 0.0) { // fading out
      Terrain_sound_fade -= Frametime / FADE_TIME;
      if (Terrain_sound_fade < 0.0)
        Terrain_sound_fade = 0.0;
    } else
      return; // already faded out
  }

  // Get player altitude
  int alt = Player_object->pos.y / TERRAIN_HEIGHT_INCREMENT;
  if (alt > 255) {
    alt = 255;
  }

  // Update each sound
  for (int b = 0; b < NUM_TERRAIN_SOUND_BANDS; b++) {
    terrain_sound_band *tb = &Terrain_sound_bands[b];
    if (tb->sound_index != -1) {
      float volume;

      if ((alt < tb->low_alt) || (alt > tb->high_alt))
        volume = 0.0;
      else
        volume =
            tb->low_volume + ((tb->high_volume - tb->low_volume) * (alt - tb->low_alt) / (tb->high_alt - tb->low_alt));

      Sound_system.Update2dSound(Terrain_sound_handles[b], volume * Terrain_sound_fade, 0.0);
    }
  }
}

// Clear out all the terrain sound bands
void ClearTerrainSound() {
  for (int b = 0; b < NUM_TERRAIN_SOUND_BANDS; b++) {
    Terrain_sound_bands[b].sound_index = -1;
    Terrain_sound_bands[b].low_alt = 0;
    Terrain_sound_bands[b].high_alt = 0;
    Terrain_sound_bands[b].low_volume = 0.0;
    Terrain_sound_bands[b].high_volume = 0.0;
  }
}

// Starts the sound on the terrain
void StartTerrainSound() {
  // Set to be full on or full off
  if (OBJECT_OUTSIDE(Player_object))
    Terrain_sound_fade = 1.0;
  else
    Terrain_sound_fade = Frametime / FADE_TIME; // will fade to zero first time

  // Start the sounds
  for (int b = 0; b < NUM_TERRAIN_SOUND_BANDS; b++) {
    terrain_sound_band *tb = &Terrain_sound_bands[b];
    if (tb->sound_index != -1) {
      Terrain_sound_handles[b] = Sound_system.Play2dSound(tb->sound_index);
    }
  }

  // Set the volumes
  UpdateTerrainSound();
}

// The main loop for D3.  It renders, gets input, etc. for one frame
extern bool Skip_render_game_frame;
void GameFrame(void) {
#ifdef USE_RTP
  INT64 curr_time;
#endif

  bool is_game_idle = !Descent->active();

  if (Tracking_FVI) {
    mprintf(0, "Beginning frame!\n");
  }

  // Begin Gameloop stuff
  Physics_normal_counter = 0;
  Physics_normal_looping_counter = 0;
  Physics_walking_counter = 0;
  Physics_walking_looping_counter = 0;
  Physics_vis_counter = 0;

  FVI_counter = 0;
  FVI_room_counter = 0;

#ifdef _DEBUG
  // Dump networking stats to virtual window
  tNetworkStatus netstat;
  static tNetworkStatus old_netstat;
  static bool netstat_init = false;
  static float netstat_time = 0;

  nw_GetNetworkStats(&netstat);
  mprintf_at(5, 0, 0, "TCP/IP Network Stats:");
  mprintf_at(5, 1, 0, "TCP: tx: %d/%d rtx: %d/%d rx: %d/%d", netstat.tcp_total_packets_sent,
             netstat.tcp_total_bytes_sent, netstat.tcp_total_packets_resent, netstat.tcp_total_bytes_resent,
             netstat.tcp_total_packets_rec, netstat.tcp_total_bytes_rec);
  mprintf_at(5, 2, 0, "UDP: tx: %d/%d rx: %d/%d", netstat.udp_total_packets_sent, netstat.udp_total_bytes_sent,
              netstat.udp_total_packets_rec, netstat.udp_total_bytes_rec);

  if (!netstat_init) {
    netstat_time = timer_GetTime();

    old_netstat = netstat;
    netstat_init = true;
  } else {
    float newt = timer_GetTime();
    if (netstat_time + 0.5f <= newt) {
      // time to update
      float tcp_rx, tcp_rtx, tcp_tx;
      float udp_rx, udp_tx;
      float time_diff = newt - netstat_time;

      tcp_rx = ((float)(netstat.tcp_total_bytes_rec - old_netstat.tcp_total_bytes_rec)) / time_diff;
      tcp_tx = ((float)(netstat.tcp_total_bytes_sent - old_netstat.tcp_total_bytes_sent)) / time_diff;
      tcp_rtx = ((float)(netstat.tcp_total_bytes_resent - old_netstat.tcp_total_bytes_resent)) / time_diff;

      udp_rx = ((float)(netstat.udp_total_bytes_rec - old_netstat.udp_total_bytes_rec)) / time_diff;
      udp_tx = ((float)(netstat.udp_total_bytes_sent - old_netstat.udp_total_bytes_sent)) / time_diff;

      mprintf_at(5, 3, 0, "TCP/s: TX: % 5.1f RTX: % 5.1f RX: % 5.1f", tcp_tx, tcp_rtx, tcp_rx);
      mprintf_at(5, 4, 0, "UDP/s: TX: % 5.1f RX: % 5.1f", udp_tx, udp_rx);

      old_netstat = netstat;
      netstat_time = newt;
    }
  }

#endif
  // Do our first quaterframe of IntelliVIBE
  VIBE_DoQuaterFrame(true);

  // clear out music struct
  memset(&Game_music_info, 0, sizeof(Game_music_info));

  // if in user interface, clear screen every frame for small game windows.
  if (Game_interface_mode != GAME_INTERFACE || Menu_interface_mode)
    Clear_screen = 4;

  // Setup sound for new frame
  Sound_system.BeginSoundFrame();
  UpdateVoices();

#ifdef USE_RTP
  RTP_GETCLOCK(curr_time);
#endif

  if ((!Game_paused) || (Demo_do_one_frame)) {
    // if we are recording a demo, all moved objects will be written
    if (!Skip_render_game_frame) {
      DemoWriteChangedObjects();
    }
    // Demo Frame (do this first so all subsequent demo items are marked for this frame)
    if (!Skip_render_game_frame) {
      DemoStartNewFrame();
    }
    if (Demo_flags == DF_PLAYBACK) {
      DemoFrame();
    }

    if (!is_game_idle) {
      // Get and process keys
      RTP_tSTARTTIME(processkeys_time, curr_time);
      ProcessKeys();
      ProcessButtons();
      RTP_tENDTIME(processkeys_time, curr_time);
    }

    // Global AI Frame Stuff  -- must be before ObjMoveAll
    RTP_tSTARTTIME(aiframeall_time, curr_time);
    if (DoAI) {
      AIFrameAll();
    }
    a_life.DoFrame();
    RTP_tENDTIME(aiframeall_time, curr_time);

    // ApplyShadowsToRooms ();

    // Move objects for this frame
    RTP_tSTARTTIME(objframe_time, curr_time);
    ObjDoFrameAll();
    RTP_tENDTIME(objframe_time, curr_time);

    RTP_tSTARTTIME(matcenframe_time, curr_time);
    DoMatcensFrame();
    RTP_tENDTIME(matcenframe_time, curr_time);

    // Checks for goal completion
    RTP_tSTARTTIME(levelgoal_time, curr_time);
    Level_goals.DoFrame();
    RTP_tENDTIME(levelgoal_time, curr_time);

    // Do doorways
    RTP_tSTARTTIME(doorframe_time, curr_time);
    DoorwayDoFrame();
    RTP_tENDTIME(doorframe_time, curr_time);

    //	Do player frame
    RTP_tSTARTTIME(playerframe_time, curr_time);
    DoPlayerFrame();
    RTP_tENDTIME(playerframe_time, curr_time);

    // Do our second quaterframe of IntelliVIBE
    VIBE_DoQuaterFrame(false);

    // Weather frame
    RTP_tSTARTTIME(weatherframe_time, curr_time);
    DoWeatherForFrame();
    RTP_tENDTIME(weatherframe_time, curr_time);

    // Ambient sounds
    RTP_tSTARTTIME(ambsound_frame_time, curr_time);
    DoAmbientSounds();
    RTP_tENDTIME(ambsound_frame_time, curr_time);

    // Terrain sound
    UpdateTerrainSound();

    // Call the interval script for the level script
    //@$-D3XExecScript(Current_level->d3xthread, Current_mission.cur_level, REF_LEVELTYPE, EVT_INTERVAL, 0, 0);
    tOSIRISEventInfo ei;
    ei.evt_interval.frame_time = Frametime;
    ei.evt_interval.game_time = Gametime;
    Osiris_CallLevelEvent(EVT_INTERVAL, &ei);
    Osiris_ProcessTimers();

    // Process any in-game cinematics
    Cinematic_Frame();

    // Do our third quaterframe of IntelliVIBE
    VIBE_DoQuaterFrame(false);

  } else {
    // Do our second quaterframe of IntelliVIBE
    VIBE_DoQuaterFrame(false);
    Sleep(3);
    // Do our third quaterframe of IntelliVIBE
    VIBE_DoQuaterFrame(false);
  }

  // do music always.
  RTP_tSTARTTIME(musicframe_time, curr_time);
  GameProcessMusic();
  RTP_tENDTIME(musicframe_time, curr_time);

  if ((Demo_paused) && (Demo_flags == DF_PLAYBACK) && !is_game_idle) {
    Demo_do_one_frame = false;
    ProcessKeys();
  }

  // Always do multiplayer frames before render frame
  //
  // Do multiplayer stuff
  RTP_tSTARTTIME(multiframe_time, curr_time);
  MultiDoFrame();
  RTP_tENDTIME(multiframe_time, curr_time);

  // Do Gamespy stuff
  //	gspy_DoFrame();

  // Do our fourth quaterframe of IntelliVIBE
  VIBE_DoQuaterFrame(false);

#ifdef USE_RTP
  RTP_GETCLOCK(curr_time); // update the current time, since something has happened since ENDFTIME
#endif

  if (!is_game_idle) {
    RTP_tSTARTTIME(renderframe_time, curr_time);
    if (!Skip_render_game_frame) {
      // Render the frame
      GameRenderFrame();
    }
    RTP_tENDTIME(renderframe_time, curr_time);
  }

  if (!Game_paused) {
    // Do pending events
    RTP_tSTARTTIME(normalevent_time, curr_time);
    ProcessNormalEvents();
    RTP_tENDTIME(normalevent_time, curr_time);

    // float start_delay = timer_GetTime();
    // Slow down the game if the user asked us to

    int64_t current_timer;
    uint32_t sleeptime;
    current_timer = timer_GetMSTime();
    if ((current_timer - last_timer) < Min_allowed_frametime) {
      sleeptime = (uint32_t)Min_allowed_frametime - (current_timer - last_timer);
      // mprintf(0,"Sleeping for %d ms\n",sleeptime);
      Sleep(sleeptime);
    }

    static int graph_id = -2;
    if (graph_id == -2) {
      graph_id = DebugGraph_Add((float)0.0f, (float)260.0f, "Framerate");
    }
    if (graph_id >= 0) {
      float fps;

      if (Frametime > 0) {
        fps = 1.0 / Frametime;
        DebugGraph_Update(graph_id, fps);
      }
    }

    // Compute how long frame took
    CalcFrameTime();

    // Update Gametime
    Gametime += Frametime;
  }

  // End Gameloop Loop stuff
  Sound_system.EndSoundFrame();
  DoDestroyedLightsForFrame();

  // Clear lod stuff
  ClearLODOffs();

  static int fvi_graph_id = -2;
  if (fvi_graph_id == -2) {
    fvi_graph_id = DebugGraph_Add(0, 1000, "FVI Calls");
  }
  if (fvi_graph_id >= 0) {
    DebugGraph_Update(fvi_graph_id, FVI_counter);
  }

#ifdef USE_RTP
  RTP_RECORDVALUE(frame_time, Frametime);
  rtp_RecordFrame();

  /*
          if (frame_info.ai_time>.1)
                  mprintf(0,"NOTE: AI frame took longer than .1 seconds! %f\n",frame_info.ai_time);
          if (frame_info.render_time>.1)
                  mprintf(0,"NOTE: Render frame took longer than .1 seconds! %f\n",frame_info.render_time);
          if (frame_info.multi_time>.1)
                  mprintf(0,"NOTE: Multi frame took longer than .1 seconds! %f\n",frame_info.multi_time);
          if (frame_info.obj_time>.1)
                  mprintf(0,"NOTE: Object frame took longer than .1 seconds! %f\n",frame_info.obj_time);
  */
#endif

  mprintf_at(1, 0, 39, "Pn %05d, L %05d", Physics_normal_counter, Physics_normal_looping_counter);
  mprintf_at(1, 1, 39, "Pw %05d, L %05d", Physics_walking_counter, Physics_walking_looping_counter);
  mprintf_at(1, 2, 39, "Pv %05d", Physics_vis_counter);
  mprintf_at(1, 3, 39, "Fc %05d, R %05d", FVI_counter, FVI_room_counter);

#ifdef D3_FAST
  if (FrameCount > 20)
    SetFunctionMode(MENU_MODE);
  else {
    int key;
    int rand_num = ps_rand() % 4;

    if (rand_num == 0)
      key = KEY_LCTRL;
    else if (rand_num == 1)
      key = KEY_SPACEBAR;
    else if (rand_num == 2)
      key = KEY_A;
    else
      key = KEY_Z;

    ddio_UpdateKeyState(key, timer_GetTime(), 1);
    ddio_UpdateKeyState(key, timer_GetTime() + .5f, 0);
  }
#endif

  if (Tracking_FVI) {
    mprintf(0, "Ending frame!\n");
  }

  if (!is_game_idle) {
    Descent->defer();
  }
}

// game menu functions
void StartGameMenu() {
  SetUICallback(GameFrame);
  SuspendControls();
  Menu_interface_mode = true;

  // reset bail flag.
  Multi_bail_ui_menu = false;

  if (!(Game_mode & GM_MULTI)) {
    PauseGame();
  }

  ui_ShowCursor();
}

void EndGameMenu() {
  ui_HideCursor();

  if (!(Game_mode & GM_MULTI)) {
    ResumeGame();
  }

  Menu_interface_mode = false;

  ResumeControls();
  SetUICallback(NULL);
  Clear_screen = 4;
}
