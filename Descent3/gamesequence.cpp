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

 * $Logfile: /DescentIII/main/gamesequence.cpp $
 * $Revision: 313 $
 * $Date: 8/30/01 12:20p $
 * $Author: Matt $
 *
 * Game Sequencer
 *
 * $Log: /DescentIII/main/gamesequence.cpp $
 *
 * 313   8/30/01 12:20p Matt
 * Removed Int3
 *
 * 312   7/09/01 4:22p Matt
 * Fixed code that was supposed to find an allowed ship in a netgame but
 * did so using the AllowedShips[] array instead of the Ships[] array, so
 * it would never find the add-on ships.
 *
 * 311   4/20/00 12:29p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 * Free the BSP tree when freeing a level
 * On Mac, free all sounds when flushing the data cache
 * Mac-only controller changes
 *
 * 310   4/06/00 9:25a Matt
 * Fixed a screen clear problem on at ATI Rage Fury Maxx in dual-chip mode
 * by forcing the screen to clear four times (instead of three).
 *
 * 309   3/20/00 12:09p Matt
 * Merge of Duane's post-1.3 changes.
 * Mac controller stuff
 * Fixed mem leaks with game paths
 * Message for PageDown pause
 * Removed dynamic lightmap info system
 *
 * 308   1/26/00 9:20p Jeff
 * added support for IntelliVIBE DLL
 *
 * 307   10/29/99 5:01p Jeff
 * fixed bug where ending a cinematic on FreeThisLevel() hosed
 * resume/suspend controls
 *
 * 306   10/22/99 10:51p Matt
 * Mac merge
 *
 * 305   10/22/99 3:40p Kevin
 * Mac merge fixes
 *
 * 304   7/20/99 1:18p Samir
 * save state of rearviews between game through the pilot file.
 *
 * 303   6/14/99 4:04p Matt
 * Fixed problem where goal couldn't be found by the Dallas init function
 * because it was  searching for the English name and the goals had been
 * translated.  Now we load the English text, init the scripts, and then
 * load the correct language.
 *
 * A simpler way of doing this would have been to *not* load the localized
 * version when the level is loaded, and just loaded it after the script
 * had been initialized.
 *
 * 302   6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 301   5/21/99 7:07p Jason
 * fixed some weird multiplayer rejoin anomalies
 *
 * 300   5/20/99 3:40p Jason
 * made mission looping work correctly in multiplayer
 *
 * 299   5/20/99 12:17a Jason
 * automatically delete all ambient objects if in multiplayer
 *
 * 298   5/19/99 5:39p Jason
 * made level failing work in coop
 *
 * 297   5/19/99 11:46a Kevin
 * fixed problem with level not being loaded and client not able to join
 * further games.
 *
 * 296   5/18/99 7:02p Jeff
 * created new callback for UI so that game states get set properly (only
 * really affects music, but fixes a problem for multiplayer games with
 * music.)
 *
 * 295   5/17/99 10:15p Matt
 * Added system for having ambient objects that get deleted at low detail
 * levels.
 *
 * 294   5/17/99 2:39p Kevin
 * fixed bug with current_mission.filename and not using strdup to
 * allocate enough room for the mn3
 *
 * 293   5/12/99 1:57p Jason
 * fixed yet more buggy/ugly code
 *
 * 292   5/12/99 1:18p Samir
 * play music during game too when in menus.
 *
 * 291   5/11/99 10:59a Kevin
 * ship allow/disallow in multi works now
 *
 * 290   5/10/99 9:25p Jeff
 * first phase of Rock 'n' Ride support added
 *
 * 289   5/10/99 10:29a Samir
 * moved StopAllSounds in EndLevel so that both single and multiplayer
 * stop sounds at the end of a level. (interplay bug).
 *
 * 288   5/10/99 3:37a Matt
 * When starting a level, delete all the viewer objects in the level.
 *
 * 287   5/09/99 2:34p Jason
 * fixed hanging of clients when dedicated server quits
 *
 * 286   5/08/99 4:30a Jeff
 * fixed sequencing bug where clients never got a level end event for the
 * multiplayer games
 *
 * 285   5/07/99 5:39p Samir
 * better error checking for CheckAndForceDataAlloc for PageInSound.
 *
 * 284   5/07/99 5:06p Jason
 * some dedicated server memory optimizations
 *
 * 283   5/07/99 2:50p Jason
 * fixed a bunch of endlevel multiplayer issues
 *
 * 282   5/06/99 4:12p Jason
 * fixed automap getting cleared after loading a savegame
 *
 * 281   5/05/99 6:48p Samir
 * made pause key take down the pause window as well.
 *
 * 280   5/05/99 12:23p Jason
 * fixed some problems with ending levels
 *
 * 279   5/05/99 12:02p Kevin
 * fixed bug with branching missions and scripts
 *
 * 278   5/05/99 1:32a Jeff
 * save/restore player energy also
 *
 * 277   5/05/99 1:28a Jeff
 * save/restore player's shields in single player game if they are over
 * 100
 *
 * 276   5/04/99 10:47p Samir
 * added secret level screen.
 *
 * 275   5/04/99 4:34p Jason
 * changes for bumpmapping
 *
 * 274   5/03/99 3:35p Kevin
 * bug fixes
 *
 * 273   5/01/99 5:52p Samir
 * removed RenderHudMessages, and redid RenderHUDMessages so it did what
 * RenderHudMessages did, resets on screen hud messages.  The HUD message
 * console is resetted in ResetGameMessages.
 *
 * 272   4/30/99 12:02p Matt
 * Keep the rear view up between levels, but close the other camera views.
 *
 * 271   4/29/99 11:46p Jason
 * added ability to set the next level in a multiplayer game
 *
 * 270   4/29/99 4:59p Jason
 * fixed some preuploaded texture problems
 *
 * 269   4/28/99 3:33a Jeff
 * reset IGC system on level load, just for sanity
 *
 * 268   4/27/99 6:09p Samir
 * SetCurrentLevel called for secret levels too.
 *
 * 267   4/25/99 6:14p Kevin
 * added "-timetest file.dem" to behave like gamegauge does
 *
 * 266   4/25/99 3:35a Jeff
 * added a please wait popup dialog when entering telcom
 *
 * 265   4/23/99 10:34p Kevin
 * fixed bad things with multiple CD code
 *
 * 264   4/23/99 8:26p Samir
 * fixed stupid clearscreen bug in endlevel
 *
 * 263   4/22/99 9:53a Kevin
 * Fixed some dedicated server crashes
 *
 * 262   4/20/99 6:55p Matt
 * Added code to keep a bitmask of all keys held by all players, and to
 * allow a robot to open a door if any player has the key(s) for that
 * door.
 *
 * 261   4/20/99 3:32p Kevin
 * new prepare for descent behaivor
 *
 * 260   4/20/99 2:59p Jeff
 * fixed SimpleStartLevel
 *
 * 259   4/20/99 11:45a Samir
 * added autosave
 *
 * 258   4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 257   4/16/99 4:30p Kevin
 * New Training mission exit code
 *
 * 256   4/16/99 12:33a Matt
 * Disable Soar on non-Windows systems.
 *
 * 255   4/15/99 3:26p Samir
 * stop all sounds when quitting game, so that resume game doesn't
 * playback any sounds.
 *
 * 254   4/15/99 2:47p Kevin
 * doh! I forgot args.h
 *
 * 253   4/15/99 2:43p Kevin
 * Added some things that I put into the demo for HEAT.NET
 *
 * 252   4/15/99 2:37p Kevin
 * Fixed multi-cd problem going from cd 2 - 1
 *
 * 251   4/15/99 1:39a Jeff
 * changes for linux compile
 *
 * 250   4/14/99 6:55p Matt
 * Fixed secret level sequencing bug
 *
 * 249   4/14/99 3:07p Kevin
 * Fixed some multiple CD bugs
 *
 * 248   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 247   4/12/99 7:15p Samir
 * prioritization pass 1
 *
 * 246   4/12/99 5:57p Kevin
 * Fixed a sequencing bug with branching levels
 *
 * 245   4/08/99 4:21p Samir
 * clear screen before ending level.
 *
 * 244   4/08/99 3:12p Matt
 * Finished cleaning up level sequencing code.  Got rid of all the "level
 * minus one" stuff.
 *
 * 243   4/07/99 3:40p Kevin
 * Fixes for Beta 1
 *
 * 242   4/07/99 12:30p Matt
 * Added code for failed missions.
 *
 * 241   4/06/99 10:44p Samir
 * Always stop music system when loading new level.
 *
 * 240   4/05/99 10:54a Matt
 * Added auto-waypoint system
 *
 * 239   4/04/99 8:15p Jeff
 * added debug graph stuff
 *
 * 238   4/03/99 5:05p Samir
 * added ENDMISSION keyword to end a mission after a certain level.
 *
 * 237   3/25/99 4:57p Jason
 * fixed resetplayerobject bug
 *
 * 236   3/25/99 11:57a Jason
 * changed some sequencing bugs
 *
 * 235   3/24/99 11:55a Jason
 * added S3 texture compression
 *
 * 234   3/24/99 10:54a Kevin
 * Fixed some problems related to splitting up the main d3.mn3 file across
 * 2 CDs
 *
 * 233   3/23/99 11:52a Jason
 * added preliminary S3 texture compression support
 *
 * 232   3/19/99 4:08p Kevin
 * Multiple CD installation support
 *
 * 231   3/11/99 12:06p Jason
 * fixed triple buffering problem
 *
 * 230   3/10/99 7:12p Jason
 * added smooth specular shading for curved surfaces
 *
 * 229   3/08/99 4:31p Kevin
 * Fixed interlevel sequencing problem with branching multiplayer
 * missions.
 *
 * 228   3/08/99 3:24p Jeff
 * fixed end level sequencing where if the level ended while the player
 * was dead.
 *
 * 227   3/05/99 7:42p Kevin
 * Doh! we weren't resetting timers!!
 *
 * 226   3/03/99 2:35a Jeff
 * clear hud messages at the end of level
 *
 * 225   3/03/99 12:56a Kevin
 * removed assert that was causing problems
 *
 * 224   2/28/99 3:24a Samir
 * call OptionsMenu.
 *
 * 223   2/25/99 8:54p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 222   2/24/99 3:15p Kevin
 * OEM menu changes, and bug fixes for the save/load system
 *
 * 221   2/24/99 9:57a Kevin
 * Added error messages if you try to save a game while in multi
 *
 * 220   2/21/99 12:18p Chris
 * Improving the level goal system...  Not done.
 *
 * 219   2/21/99 4:20p Matt
 * Added SoundSource objects (and reformatted parts of the object header
 * files).
 *
 * 218   2/21/99 12:28p Matt
 * Added terrain sound system
 *
 * 217   2/20/99 9:22p Jeff
 * finished telcom level goals screen.  Made it so if you go into the
 * telcom from the game it goes to main menu instead of briefings.
 *
 * 216   2/20/99 4:11p Jeff
 * fixed cockpit selection bug again (which cockpit to use depending on
 * multi or single)
 *
 * 215   2/20/99 2:31p Kevin
 * Made multiplayer DLLs return to the game list after a game.
 *
 * 214   2/20/99 2:17p Matt
 * Added texture sounds
 *
 * 213   2/19/99 12:01p Jason
 * took out sky band
 *
 * 211   2/16/99 12:38p Kevin
 * Improved paging data progress indicator
 *
 * 210   2/16/99 11:13a Jason
 * fixed bug in cockpit initialization code
 *
 * 209   2/15/99 7:49p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 208   2/14/99 8:06p Jeff
 * start of new pilot read/write...not working yet, still needs work
 *
 * 207   2/12/99 3:54a Jeff
 * added function to restart a level, and a cheat key to do so (del-alt-e)
 *
 * 205   2/10/99 4:56p Kevin
 * Better progress indicator & prepare for Descent message
 *
 * 204   2/10/99 3:47p Jason
 * table filter changes
 *
 * 203   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 202   2/10/99 10:58a Kevin
 * doh!
 *
 * 201   2/10/99 10:56a Kevin
 * Took out loadlevelcb calls for now
 *
 * 200   2/09/99 7:01p Kevin
 * First work for new and improved progress screen while loading a level.
 * Note that this is a hack at this point, while I get the details worked
 * out, then I'll make it cleaner.
 *
 * 199   2/05/99 7:23p Kevin
 * OEM Changes
 *
 * 198   2/04/99 12:35p Jeff
 * free in-game cinematics when level ends
 *
 * 197   2/01/99 6:14p Kevin
 * Moved InitLevelScripts to later in the sequence
 *
 * 196   2/01/99 3:57p Samir
 * fixed bug in secret levels.
 *
 * 195   2/01/99 12:44p Jason
 * added another bumpmapping pass
 *
 * 194   2/01/99 10:35a Matt
 * Fixed the initial player position in the game when playing from the
 * editor.
 *
 * 193   1/31/99 7:25p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 192   1/31/99 3:44p Matt
 * Streamlined game sequencing
 *
 * 191   1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 190   1/29/99 2:08p Jeff
 * localization
 *
 * 189   1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 188   1/28/99 11:32a Jason
 * added marker cameras
 *
 * 187   1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 186   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 185   1/20/99 4:20p Samir
 * finished secret level implementation.
 *
 * 184   1/20/99 10:50a Jason
 * added new terrain
 *
 * 183   1/19/99 11:25a Jason
 * added room (fog and wind) changing functions
 *
 * 182   1/15/99 7:16p Kevin
 * Added GameGauge Configuration & code
 *
 * 181   1/14/99 3:08p Jason
 * more cache changes
 *
 * 180   1/14/99 3:05p Jason
 * fixed stupid texture data bug
 *
 * 179   1/14/99 2:26p Jason
 * made data tracking more reliable
 *
 * 178   1/13/99 2:28a Chris
 * Massive AI, OSIRIS update
 *
 * 177   1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 176   1/04/99 6:45p Jason
 * took out paging return
 *
 * 175   12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 174   12/28/98 5:56p Jason
 * don't page in data if editor
 *
 * 173   12/23/98 1:25p Chris
 * Got the FIRST AI working!!!!!!!!  I need to rearrange the sequencing so
 * that the AIInitAll wouldn't reset objects AFTER there EVT_AI_INIT was
 * called.
 *
 * 172   12/21/98 3:33p Samir
 * level warp fully implemented.
 *
 * 171   12/21/98 9:44a Chris
 * Ambient life stuff is all tied in to game sequencing
 *
 * 170   12/18/98 5:40p Chris
 * Ambient life is now all sequenced up
 *
 * 169   12/15/98 4:28p Jeff
 * added mission data information to the pilot files to save what the
 * highest level they achieved on a mission is.  Added level select dialog
 * (not hooked up) and level warp cheat.
 *
 * 168   12/14/98 11:57a Jason
 * changes for visibile automap
 *
 * 167   12/03/98 12:50p Samir
 * music file loaded at beginning of level.
 *
 * 166   11/19/98 5:40p Kevin
 * Demo system
 *
 * 165   11/16/98 12:19p Samir
 * pause and resume sounds until first frame of level.
 *
 * 164   11/13/98 2:28p Samir
 * new music system.
 *
 * 163   11/09/98 3:08p Kevin
 * Added demo code
 *
 * 162   11/05/98 7:36p Samir
 * rearranged some sequencing so that common editor/game code gets called,
 * and moved redundant game screen init code to StartNewLevel.
 *
 * 161   11/05/98 5:54p Kevin
 * Demo system work
 *
 * 160   10/30/98 3:44p Samir
 * reset multi_ui_bail.
 *
 * 159   10/23/98 12:51p Samir
 * added call to SetHudMode so that level sequencing maintains the hud.
 *
 * 158   10/22/98 8:31p Chris
 * Sounds use GlobalAlloc and GlobalFree
 *
 * 157   10/22/98 5:46p Jason
 * took care of remaining page-in issues
 *
 * 156   10/22/98 4:11p Samir
 * took out ifdef DEMO for inventory.
 *
 * 155   10/22/98 3:30p Samir
 * fixed for editor the hud.
 *
 * 154   10/22/98 2:40p Samir
 * redid HUD sequencing so multiplayer hud stuff works.
 *
 * 153   10/22/98 1:30a Jeff
 * (Samir) ifdefed out guidebot interface for demo
 *
 * 152   10/21/98 9:28p Jason
 * Made no lightmaps work globally
 *
 * 151   10/21/98 7:04p Samir
 * moved init hud and cockpit to init level
 *
 * 150   10/21/98 6:53p Jason
 * changes for shitty direct3d cards
 *
 * 149   10/21/98 4:52p Jeff
 * disallow Automap for Demo
 *
 * 148   10/21/98 1:37p Jason
 * fixed naming bug
 *
 * 147   10/21/98 12:05p Jason
 * changes for data paging
 *
 * 146   10/21/98 10:35a Samir
 * cleaned up GameInterface code.
 *
 * 145   10/20/98 8:48p Sean
 * Don't call ResetPlayerObject() when playing from the editor, since that
 * caused the player to move to the start position. (MattT on Sean's
 * machine.)
 *
 * 144   10/20/98 6:50p Matt
 * Fixed small bug paging in object animation sounds.
 *
 * 143   10/20/98 2:53a Kevin
 * gunboy crap
 *
 * 142   10/20/98 12:11a Chris
 *
 * 141   10/19/98 11:22p Samir
 * clear screen after UI.
 *
 * 140   10/19/98 11:06p Kevin
 *
 * 139   10/19/98 8:51p Matt
 * Added missing period in pause message.
 *
 * 138   10/19/98 7:45p Matt
 *
 * 137   10/19/98 5:40p Samir
 * added loading level callback.
 *
 * 136   10/19/98 12:12p Samir
 * call ResetPlayerObject from StartNewLevel.
 *
 * 135   10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 134   10/18/98 11:11p Matt
 * Added call to ClearTransientObjects() and cleaned up some sequencing
 * stuff.
 *
 * 133   10/18/98 7:27p Samir
 * flush controller at start of every level.
 *
 * 132   10/16/98 4:03p Matt
 * Fixed run-on in pause message.
 *
 * 131   10/15/98 8:32p Matt
 * Fixed bug with starting abient sounds that caused rooms & other
 * non-generic objects to have ambient sounds.
 *
 * 130   10/14/98 6:40p Samir
 * write pilot files out at quitting game.
 *
 * 129   10/12/98 3:02p Jeff
 * moved DEFAULT_SHIP #define into ship.h
 *
 * 128   10/12/98 11:15a Samir
 * changed some sequencing stuff in GAMESTATE_LVLSTART.
 *
 * 127   10/09/98 4:13p Matt
 * Use different default ship for the demo
 *
 * 126   10/08/98 8:01p Nate
 * got rid of warning.
 *
 * 125   10/08/98 7:29p Samir
 * revamped sequencing.
 *
 * 124   10/08/98 2:33p Kevin
 *
 * 123   10/08/98 2:29p Kevin
 * fixed bad if statement
 *
 * 122   10/08/98 12:00p Kevin
 * Demo system work
 *
 * 121   10/07/98 12:22p Jason
 *
 * 120   10/06/98 5:45p Kevin
 * Added new configuration for demo
 *
 * 119   10/06/98 2:38p Jeff
 * fixed paused message
 *
 * 118   10/05/98 12:09p Kevin
 * Converted projects to VC6 and demo file stuff added
 *
 * 117   10/02/98 3:40p Chris
 * Improved the level goal code
 *
 * 116   9/28/98 2:15p Kevin
 * Changed calls to network idle function
 *
 * 115   9/28/98 11:02a Kevin
 * added Networking defer, and fixed some UI issues
 *
 * 114   9/28/98 10:55a Jason
 * fixed some bugs that VC6 caught
 *
 * 113   9/25/98 4:55p Jason
 * flush all multiplayer buffers at the start of a new level
 *
 * 112   9/17/98 3:31p Samir
 * if level is ending, freethislevel gets called twice (at EndLevel, and
 * QuitToMenu), so make sure we don't freelevel in latter case.
 *
 * 111   9/16/98 5:10p Jason
 * added first pass at thrid-person camera system
 *
 * 110   9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 109   9/10/98 3:07p Chris
 * Improved matcen sequencing code and test effect1
 *
 * 108   9/10/98 12:55p Chris
 * Added pre-level initialization for matcens  :)
 *
 * 107   9/09/98 1:08p Jeff
 * commented out call to FlushDataCache in FreeThisLevel
 *
 * 106   9/08/98 3:25p Matt
 * Fixed, hopefully, problems with getting the the player position &
 * orientation back to the editor when playing from the editor.
 *
 * 105   9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 104   9/08/98 10:28a Samir
 * added function to deinitialize a level.
 *
 * 103   9/03/98 12:11p Chris
 * Adding matcen support
 *
 * 102   8/29/98 6:53p Jeff
 * added single-player ship selection
 *
 * 101   8/28/98 1:34p Matt
 * Added code to reset the waypoint when starting a new level, and while I
 * was at it cleaned up the new level start sequencing.
 *
 * 100   8/27/98 2:51p Jeff
 * made it so SHIFT-ESC exits the TelCom back to Main Menu
 *
 * 99    8/26/98 1:48a Chris
 * Fixed odd non-stopping sounds when ESC out of the game - etc.
 *
 * 98    8/24/98 2:45p Jason
 * tweaks to the data cache stuff
 *
 * 97    8/24/98 10:42a Jason
 * more memory paging issues dealt with
 *
 * 96    8/21/98 8:28p Samir
 * made FlushDataCache bail if in the editor
 *
 * 95    8/21/98 5:14p Jason
 * made better memory use of primitives
 *
 * 94    8/21/98 3:02p Jason
 * better paging in of weapons stuff
 *
 * 93    8/20/98 10:52a Samir
 * added load game(restore game) functionality from main menu.
 *
 * 92    8/19/98 6:39p Samir
 * took out null of Current_level.
 *
 * 91    8/19/98 5:36p Samir
 * pause game when in load game state.
 *
 * 90    8/18/98 3:02p Samir
 * new sequencing for LoadGameState and PLEASE define Current_level some
 * other way (or at least keep the definition in StartNewLebvel)
 *
 * 89    8/18/98 1:50p Matt
 * Added missing ambient sound init
 *
 * 88    8/18/98 1:05a Samir
 *
 * 87    8/17/98 6:40p Matt
 * Added ambient sound system
 *
 * 86    8/16/98 5:56p Jeff
 * added game interface for multiplayer dll ui stuff
 *
 * 85    8/10/98 6:19p Jason
 * Reset all doorways at the beginning of a level
 *
 * 84    8/10/98 2:21p Jeff
 * changes made due to adding flag for inventory reset
 *
 * 83    8/04/98 2:32p Chris
 * Improved attach code added more fixes to the AABB partial computation
 * patch
 *
 * 82    7/31/98 5:19p Samir
 * mission filenames are dynamically allocated now to allow for pathnames
 * (since we'd have too many 256 char arrays per level.
 *
 * 81    7/28/98 5:41p Samir
 * music system hooks.
 *
 * 80    7/20/98 12:04p Jason
 * added per level satellite lighting
 *
 * 79    6/29/98 6:42p Samir
 * Properly handle controller pausing and resumption.
 *
 * 78    6/25/98 5:22p Kevin
 * Req/Send gametime to clients
 *
 * 77    6/25/98 12:43p Jeff
 * Added exit game confirmation
 *
 * 76    6/24/98 5:18p Matt
 * Added code for user pausing
 *
 * 75    6/23/98 11:10p Matt
 * Simplified some code
 *
 * 74    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 73    6/16/98 10:38a Jeff
 * localization, strings pulled out to stringtable.h and d3.str
 *
 * 72    6/15/98 10:54a Chris
 * All sounds stop at the end of a level
 *
 * 71    5/27/98 12:36a Samir
 * print out message saying demo will restart in x minutes for E3.
 *
 * 70    5/26/98 11:03p Chris
 *
 * 69    5/26/98 10:54p Chris
 * Ooops again
 *
 * 68    5/26/98 10:49p Samir
 * reset level timer limit for E3.
 *
 * 67    5/26/98 10:42p Chris
 * Fixed door sound paging
 *
 * 66    5/26/98 10:21p Chris
 * Added door sound paging
 *
 * 65    5/26/98 10:16p Jason
 * Precache terrain lod bitmaps
 *
 * 64    5/26/98 5:04p Samir
 * took out calls to SetHudMode (called in SetScreenMode)
 *
 * 63    5/26/98 2:49p Jason
 * fixed FOV bug
 *
 * 62    5/25/98 8:29p Samir
 * moved call to postlevel results to EndLevel function.
 *
 * 61    5/25/98 3:46p Jason
 * added better light glows
 *
 * 60    5/24/98 2:55a Jeff
 * added paramter to MenuOptions()
 *
 * 59    5/22/98 12:34p Matt
 * Added scorch mark/bullet hole system.
 *
 * 58    5/21/98 2:32p Samir
 * added full support for intra-mission level branching.
 *
 * 57    5/18/98 4:36p Jeff
 * TelCom uses Game_interface_mode variable now
 *
 * 56    5/17/98 4:08p Chris
 * Fixed bugs with initial sound loading.  :)
 *
 * 55    5/15/98 5:18p Chris
 * Working on sound paging
 *
 * 54    5/15/98 5:07p Chris
 * Fixed some bugs in sound paging
 *
 * 53    5/14/98 3:18p Jason
 * finished multiplayer sequencing issues
 *
 * 52    5/14/98 11:49a Chris
 * Bettered the sound paging system
 *
 * 51    5/12/98 4:18p Jason
 * added better level sequencing for multiplayer
 *
 * 50    5/12/98 12:33p Jason
 * got level sequencing working in multiplayer
 *
 * 49    5/11/98 6:19p Samir
 * hide cursor when entering game.
 *
 * 48    5/11/98 4:14p Samir
 * set ui callback to NULL when just entering game....
 *
 * 47    5/11/98 11:31a Jason
 * added some events for level sequencing
 *
 * 46    5/05/98 5:16p Samir
 * moved loading level message to this file.
 *
 * 45    5/01/98 4:24p Samir
 * open cockpit fully if current hud mode is cockpit at start of level.
 *
 * 44    4/24/98 5:31p Samir
 * reset reticle at game start
 *
 * 43    4/24/98 1:53a Samir
 * took care of a lot of scripting memory leaks.
 *
 * 42    4/21/98 4:16a Samir
 * clear out obj_text array in level node for simple start level.
 *
 * 41    4/20/98 10:02a Chris
 * Working on fixing AI/OSIRIS integration bugs
 *
 * 40    4/16/98 2:56p Chris
 * Updated buddy support and intergrated scripting and AI
 *
 * 39    4/16/98 6:52a Samir
 * took out cockpit init.free code
 *
 * 38    4/14/98 9:18p Samir
 * redid post level results.
 *
 * 37    4/10/98 2:58p Chris
 * Redid where the buddy gets allocated, not all the way done yet.
 *
 * 36    4/09/98 7:02p Chris
 *
 * 35    4/09/98 6:57p Craig
 * FIxed a sequencing bug
 *
 * 34    4/07/98 4:25p Chris
 * Added support for buddy bot
 *
 * 33    4/06/98 5:13p Chris
 * Sounds page in at the beginning of a level
 *
 * 32    4/06/98 12:14p Jason
 * changes to multiplayer
 *
 * 31    4/03/98 3:36p Chris
 * Added the start of the buddy menu
 *
 * 30    4/02/98 11:11a Samir
 * Error checking for level load/misison init fail.
 *
 * 29    3/31/98 3:49p Jason
 * added memory lib
 *
 * 28    3/27/98 5:06p Samir
 * took out unnecessary mprintfs.
 *
 * 27    3/23/98 7:06p Chris
 *
 * 26    3/23/98 6:16p Chris
 * added some soar_helpers and some debug mprintf's
 *
 * 25    3/17/98 2:40p Samir
 * reorg of hud/gauge system.
 *
 * 24    3/13/98 12:37p Jeff
 * start level at 0 for simplestartlevel.
 *
 * 23    3/13/98 12:08p Samir
 * Added SimpleStartLevel.
 *
 * 22    3/05/98 2:51p Jeff
 * Added Help interface
 *
 * 21    3/05/98 2:50p Chris
 * A bunch of SOAR updates
 *
 * 20    3/03/98 12:10p Samir
 * Added simple pausing.
 *
 * 19    3/02/98 5:52p Samir
 * Added game interface system.
 *
 * 18    2/23/98 1:59p Jason
 * touch terrain textures when initting a level
 *
 * 17    2/18/98 3:25p Samir
 * Added test systems code.
 *
 * 16    2/18/98 1:19a Samir
 * DoLevelIntro now bails at the right place if we're in multiplayer mode.
 *
 * 15    2/17/98 8:26p Chris
 *
 * 14    2/17/98 7:48p Chris
 *
 * 13    2/17/98 7:47p Chris
 *
 * 12    2/17/98 4:42p Samir
 * Current_level is now defined after calling DoLevelIntro.
 *
 * 11    2/17/98 2:22p Jason
 * fixed multiplayer sequencing with briefings
 *
 * 10    2/17/98 12:20p Chris
 * Made sounds not get paged out at end/beginning of level
 *
 * 9     2/13/98 6:43p Samir
 * ifdef out editor code iin GameSequencer.
 *
 * 8     2/13/98 12:40p Jason
 * added functions to touch all data in a level when the level is loaded
 *
 * 7     2/13/98 10:57a Samir
 * Changed some gamescript initialization.
 *
 * 6     2/12/98 6:51p Matt
 * Renamed GameLoop() to be GameFrame(), cleaned up the StartTime/StopTime
 * system, and moved the interval script call to GameFrame().
 *
 * 5     2/12/98 5:08p Matt
 * Reset cockpit mode when starting a level.  Unfortunately, this involved
 * some semi-major mucking with game sequencing.
 *
 * 4     2/11/98 4:36p Samir
 * Call SetGameMode to modify game mode.
 *
 * 3     2/09/98 3:58p Matt
 * Initialize small views and camera views at level start
 *
 * 2     2/08/98 5:01p Samir
 * New game sequencing changes.
 *
 * 1     2/08/98 3:54p Samir
 * Initial revision.
 *
 * $NoKeywords: $
 */
#ifdef USE_PROFILER
#include <profiler.h>
#endif

#include "gamesequence.h"

#include "game.h"
#include "gameloop.h"
#include "descent.h"
#include "player.h"
#include "Mission.h"
#include "BOA.h"
#include "gameevent.h"
#include "AIMain.h"

#include "soar_helpers.h"

#include "terrain.h"
#include "hlsoundlib.h"
#include "SmallViews.h"
#include "polymodel.h"
#include "gametexture.h"
#include "hud.h"
#include "findintersection.h"
#include "menu.h"
#include "newui.h"
#include "cockpit.h"
#include "help.h"
#include "buddymenu.h"
#include "mem.h"
#include "soundload.h"
#include "robot.h"
#include "screens.h"
#include "game2dll.h"
#include "ship.h"
#include "TelCom.h"
#include "scorch.h"
#include "render.h"
#include "stringtable.h"
#include "ddio_common.h"
#include "gamesave.h"
#include "sounds.h"
#include "ambient.h"
#include "vclip.h"
#include "pilot.h"
#include "doorway.h"
#include "matcen.h"
#include "dedicated_server.h"
#include "networking.h"
#include "levelgoal.h"
#include "demofile.h"
#include "lightmap_info.h"
#include "lightmap.h"
#include "fireball.h"
#include "d3music.h"
#include "TelComAutoMap.h"
#include "aiambient.h"
#include "ObjScript.h"
#include "marker.h"
#include "gamecinematics.h"
#include "osiris_dll.h"
#include "debuggraph.h"
#include "multi_dll_mgr.h"
#include "multi_ui.h"
#include "gamepath.h"
#include "vclip.h"
#include "bsp.h"

#include "args.h"
void ResetHudMessages(void);

//	Variables
tGameState Game_state = GAMESTATE_IDLE;      // current game state.
tGameState Last_game_state = GAMESTATE_IDLE; // previous frame game state.
int Game_interface_mode = GAME_INTERFACE;    // game interface mode (options menu?)

extern bool FirstGame;

static bool Level_started = false;
static int Level_warp_next = 0;

#ifdef E3_DEMO
extern float E3_TIME_LIMIT;
extern bool E3_enforce_level_restart;
#endif

extern float Multi_Game_time_start;

extern bool Demo_looping;
extern bool IsRestoredGame;

//	internal functions
bool StartNewGame();        //	We start a game by using the current mission in memory.
bool DoLevelIntro();        // shows movie and briefing
void StartGameFromEditor(); // set up new game/new level stuff when playing from editor
void EndLevel(int state);   //	ends the current level.
void RestartLevel();        // restarts the current level.
void RunGameMenu();         // executes a game menu.
void FreeThisLevel();       // frees any data/esc that was created for that level.
void FlushDataCache();      // Clears out all the level specific stuff from memory
void SetNextLevel();        // advances to the next level
void CheckHogfile();        // make sure we have the right hogfile

// Data paging functions
void PageInAllData();
void PageInLevelTexture(int);
bool PageInSound(int);
void PageInDoor(int);
void PageInWeapon(int);
void PageInGeneric(int);
void PageInShip(int);

// Data allocation arrays, for keeping track of what textures/sounds are level specific
uint8_t Models_to_free[MAX_POLY_MODELS];
uint8_t Textures_to_free[MAX_TEXTURES];
uint8_t Sounds_to_free[MAX_TEXTURES];

#ifdef EDITOR
extern vector editor_player_pos;
extern matrix editor_player_orient;
extern int editor_player_roomnum;
#endif

extern bool mn3_Open(const char *mn3file);
extern void mn3_Close();

extern bool Game_gauge_do_time_test;
extern char Game_gauge_usefile[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
//	Sequences game events
///////////////////////////////////////////////////////////////////////////////
bool GameSequencer() {
  bool in_editor = (GetFunctionMode() == EDITOR_GAME_MODE);
  tGameState old_game_state;

  // interpret current function mode.
  switch (GetFunctionMode()) {
  case INIT_MODE:
  case GAME_MODE:
  case EDITOR_MODE:
  case EDITOR_GAME_MODE:
  case MENU_MODE:
  case QUIT_MODE:
  case CREDITS_MODE:
  case GAMEGAUGE_MODE:
    break;
  case RESTORE_GAME_MODE:
  case LOADDEMO_MODE:
    SetFunctionMode(GAME_MODE); // need to do so sequencer thiks we're in game.
    break;
  }

  //	The main game sequencer
  while ((GetFunctionMode() == GAME_MODE) || (GetFunctionMode() == EDITOR_GAME_MODE)) {
    old_game_state = Game_state;

    switch (Game_state) {
    case GAMESTATE_IDLE:
      break;
    case GAMESTATE_NEW:
      StartNewGame();
      SetGameState(GAMESTATE_LVLSTART);
      break;

    case GAMESTATE_LVLSTART:
      CheckHogfile(); // make sure we have the right hogfile

      if (in_editor) { // start in editor
#ifdef EDITOR
        StartGameFromEditor();
#endif
      } else { // start in game
        if (!DoLevelIntro() || !LoadAndStartCurrentLevel()) {
          if (Game_mode & GM_MULTI)
            MultiLeaveGame();
          MultiDLLGameStarting = 0;
          Multi_bail_ui_menu = false;
          SetFunctionMode(MENU_MODE); //	return to main menu
          break;
        }
      }

      SetGameState(GAMESTATE_LVLPLAYING);
      break;

    case GAMESTATE_LVLPLAYING:
      //	must do to display main menu interfaces
      if (Last_game_state == GAMESTATE_LVLSTART) {
        // 1st frame resume sounds.
        Sound_system.ResumeSounds();
      }

      if (Game_interface_mode != GAME_INTERFACE) {
        RunGameMenu();
      } else {
        Descent->defer();
        GameFrame();
      }
      break;

    case GAMESTATE_LOADDEMO:
      if (DemoPlaybackFile(Demo_fname)) {
        SetGameState(GAMESTATE_LVLPLAYING);
      } else {
        SetFunctionMode(MENU_MODE);
      }
      break;
    case GAMESTATE_LOADGAME:
      if (Game_mode & GM_MULTI) {
        DoMessageBox(TXT_ERROR, TXT_CANT_LOAD_MULTI, MSGBOX_OK);
        break;
      }
      D3MusicStop(); // make sure all music streams are stopped before restoring game.
      PauseGame();
      if (!LoadCurrentSaveGame()) {
        SetFunctionMode(MENU_MODE);
      } else {
        SetGameState(GAMESTATE_LVLPLAYING);
        SetScreenMode(SM_GAME);
        SetHUDMode(GetHUDMode());
      }
      ResumeGame();
      break;

    case GAMESTATE_LVLEND:
      SuspendControls();
      EndLevel(1);
      SetGameState(GAMESTATE_LVLNEXT);

      // This is for HEAT.NET and their tournement mode stuff
      // if(FindArg("-doonelevel"))
      //	SetGameState(GAMESTATE_LVLSTART);
      if (FindArg("-doonelevel")) {
        SetFunctionMode(QUIT_MODE);
      }

      break;

    case GAMESTATE_LVLNEXT:
      SetNextLevel();
      SetGameState(GAMESTATE_LVLSTART);
      break;

    case GAMESTATE_LVLWARP:
      SuspendControls();
      EndLevel(-1);
      SetCurrentLevel(Level_warp_next);
      SetGameState(GAMESTATE_LVLSTART);
      break;

    case GAMESTATE_LVLFAILED:
      SuspendControls();
      EndLevel(0);
      SetGameState(GAMESTATE_LVLSTART); // restart same level
      break;
    }
    Last_game_state = old_game_state;
  }

#ifdef EDITOR // Ugly hack to get play position back to the editor
  if (Player_object && (Player_object->type == OBJ_PLAYER)) {
    editor_player_pos = Player_object->pos;
    editor_player_orient = Player_object->orient;
    editor_player_roomnum = Player_object->roomnum;
  } else
    editor_player_roomnum = -1;
#endif

  //	free up scripts.
  PltWriteFile(&Current_pilot);
  FreeThisLevel();

  SetGameMode(GM_NONE);

  return true;
}

// Make sure we have the correct hogfile
void CheckHogfile() {
  char hogpath[_MAX_PATH * 2];
  mprintf(0, "Checking to see if we need to open another hog off of disk or CDROM\n");

  if (Current_mission.filename && (stricmp(Current_mission.filename, "d3.mn3") == 0) &&
      (Current_mission.cur_level > 4)) {
    // close the mission hog file and open d3_2.mn3
    mn3_Close();
    ddio_MakePath(hogpath, D3MissionsDir, "d3_2.mn3", nullptr);
    if (cfexist(hogpath)) {
      mn3_Open(hogpath);
      mem_free(Current_mission.filename);
      Current_mission.filename = mem_strdup("d3_2.mn3");
    } else {
      SetFunctionMode(MENU_MODE);
    }
  } else if (Current_mission.filename && (stricmp(Current_mission.filename, "d3_2.mn3") == 0) &&
             (Current_mission.cur_level <= 4)) {
    // Part 2 of the mission is d3_2.mn3
    // close the mission hog file and open d3.mn3
    mn3_Close();
    ddio_MakePath(hogpath, D3MissionsDir, "d3.mn3", nullptr);
    if (cfexist(hogpath)) {
      mn3_Open(hogpath);
      mem_free(Current_mission.filename);
      Current_mission.filename = mem_strdup("d3.mn3");
    } else {
      SetFunctionMode(MENU_MODE);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//	quickly sets up a mission of 1 level, and doesn't do any
//	fancy intro stuff
bool SimpleStartLevel(char *level_name) {
  //	this initializes a mini one level mission with no frills.

  Current_mission.cur_level = 1;
  Current_mission.num_levels = 1;
  Current_mission.levels = (tLevelNode *)mem_malloc(sizeof(tLevelNode));
  memset(Current_mission.levels, 0, sizeof(tLevelNode));

  Current_level = NULL;
  Current_mission.levels[0].filename = mem_strdup(level_name);
  InitMissionScript();

  return true;
}

///////////////////////////////////////////////////////////////////////////////
//	We start a game by using the current mission in memory.
//	First we display the mission briefing (the intro movie for Descent 3, if not an add on)
//	Then we start level
///////////////////////////////////////////////////////////////////////////////

bool StartNewGame() {
  SetCurrentLevel(Current_mission.cur_level);

  ResetGamemode();

  if (!(Game_mode & GM_MULTI)) {
    Player_num = 0; // Reset player num
    Players[Player_num].ship_index = FindShipName(DEFAULT_SHIP);
    ASSERT(Players[Player_num].ship_index != -1);
  }

  if (Game_mode & GM_MULTI)
    CallGameDLL(EVT_GAMECREATED, &DLLInfo);

  // Load any addon data
  mng_LoadAddonPages();

  InitPlayerNewShip(Player_num, INVRESET_ALL);
  InitPlayerNewGame(Player_num);

  InitCameraViews(1); // Turn off all camera views, including rear views

  Quicksave_game_slot = -1; // reset so that quicksave key will always go to savegame menu first

  return true;
}

// Shows the intro movie and briefing for a level
bool DoLevelIntro() {
  tLevelNode *lvl = Current_level;

  mprintf(0, "In DoLevelIntro()\n");

  // multiplayer stuff (we skip the movie and briefings)
  if (Game_mode & GM_MULTI) {
    if (Netgame.local_role == LR_CLIENT) {
      // Clear out residual junk
      MultiFlushAllIncomingBuffers();

      if (!MultiPollForLevelInfo()) {
        return false;
      }
    }
    return true;
  }

#ifdef STEALTH // DAJ just get started
  return true;
#endif
  //	if this level has a movie:
  if (lvl->flags & LVLFLAG_STARTMOVIE) {
    DoMissionMovie(Current_mission.levels[Current_mission.cur_level - 1].moviename);
  }

  //	if this level has a briefing:
  if (lvl->flags & LVLFLAG_BRIEFING) {
    if (!DoMissionBriefing(Current_mission.cur_level - 1)) {
      // quit exit to main menu
      return false;
    }
  }
  return true;
}

// Sets the current level for subsequent level loads, movies, or briefings
void SetCurrentLevel(int level) {
  ASSERT(level > 0 && level <= Current_mission.num_levels);

  // Set this level as the mission's current level
  Current_mission.cur_level = level;

  // Set pointer to this level
  Current_level = &Current_mission.levels[level - 1];
}

void StartLevelSounds();

// Get rid of any viewer objects in the level
void ClearViewerObjects() {
  int i;
  object *objp;

  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++)
    if (objp->type == OBJ_VIEWER) {
      mprintf(0, "Deleting viewer object %d\n", i);
      ObjDelete(i);
    }
}

// If low or medium detail, delete all or some ambient objects
void DeleteAmbientObjects() {
  int i, count;
  object *objp;

  if (!(Game_mode & GM_MULTI) && Detail_settings.Object_complexity == 2) // high
    return;

  for (i = 0, objp = Objects, count = 0; i <= Highest_object_index; i++, objp++) {
    if (IS_GENERIC(objp->type) && (Object_info[objp->id].flags & OIF_AMBIENT_OBJECT)) {
      if ((Detail_settings.Object_complexity == 0) || (count & 1) || (Game_mode & GM_MULTI))
        ObjDelete(i);
      count++;
    }
  }
}

void Localization_SetLanguage(int type);
int Localization_GetLanguage(void);
void LoadLevelText(const char *level_filename);

// Starts the level, which has already been loaded
void StartLevel() {
  extern void RestoreCameraRearviews(); // gameloop.cpp

  // Init time
  Gametime = 0.0f;

  // Make sure all sounds have stopped
  Sound_system.StopAllSounds();

  // Get the data for this level
  PageInAllData();

  // TEMP HACK
  if (rend_SupportsBumpmapping())
    Detail_settings.Bumpmapping_enabled = 1;
  else
    Detail_settings.Bumpmapping_enabled = 0;

  // Initialize a bunch of stuff for this level
  MakeBOA();
  ComputeAABB(true);

  // Clear/reset objects & events
  ClearAllEvents();
  ClearRoomChanges();
  ResetMarkers();
  ResetScorches();
  ResetWaypoint();
  ResetLightGlows();
  DoorwayDeactivateAll();
  ClearViewerObjects();
  DeleteAmbientObjects();

  // AI, scripting, & Soar
  AIInitAll();

  // Set up the player object
  ResetPlayerObject(Player_num);

  DSSoarInit();

  InitMatcensForLevel();

  // What is this?
  a_life.InitForLevel();

  // Start sound & music
  StartLevelSounds();
  Sound_system.PauseSounds(); // HACK!! pause sounds started up to now.
  D3MusicStart(Current_level->score);

  // Get the list of waypoints from the waypoint objects
  MakeAtuoWaypointList();

// Test stuff
#ifdef _DEBUG
  InitTestSystems();
#endif

  // Set screen mode
  SetScreenMode(SM_GAME);

  // Init HUD and cockpit
  int ship_index;

  if (Game_mode & GM_MULTI) {
    char ship_model[PAGENAME_LEN];
    Current_pilot.get_ship(ship_model);
    ship_index = FindShipName(ship_model);
    ASSERT(ship_index != -1); // DAJ -1FIX
    if (Netgame.local_role == LR_SERVER) {
      if (PlayerIsShipAllowed(Player_num, ship_model)) {
        Players[Player_num].ship_index = FindShipName(ship_model);
        ASSERT(Players[Player_num].ship_index != -1); // DAJ -1FIX
      } else {
        mprintf(0, "Player %d wanted to use a ship (%s) which wasn't allowed.\n", Player_num, ship_model);
        int i;
        bool found_one = false;

        // Loop through ships, looking for one that's allowed
        for (i = 0; i < MAX_SHIPS && !found_one; i++) {
          if (Ships[i].used && PlayerIsShipAllowed(Player_num, i)) {
            Players[Player_num].ship_index = i;
            found_one = true;
          }
        }

        // We should have found one
        ASSERT(found_one == true);
      }
      ship_index = Players[Player_num].ship_index;
      PlayerChangeShip(Player_num, ship_index);
    }
  } else {
    ship_index = Players[Player_num].ship_index;
  }

  if (ship_index < 0)
    ship_index = 0;
  InitShipHUD(ship_index);
  InitCockpit(ship_index);
  if (GetHUDMode() == HUD_COCKPIT) // make sure cockpit is open, if hud mode is cockpit
    QuickOpenCockpit();
  ResetHUDMessages();
  ResetGameMessages();
  ResetReticle();
  ResetSmallViews();  // ResetSmallViews() must come before InitCameraViews()
  InitCameraViews(0); // ResetSmallViews() must come before InitCameraViews()
  RestoreCameraRearviews();
  SetHUDMode(GetHUDMode()); // what does this do?

  // Init zoom
  Render_zoom = D3_DEFAULT_ZOOM;

  // flush controller system.
  ResumeControls();
  Controller->flush();

  Level_goals.InitLevel();

  // Do multiplayer & player stuff
  if (Game_mode & GM_MULTI) {
    MultiStartNewLevel(Current_mission.cur_level);
  } else { // Init player for single-player
    DeleteMultiplayerObjects();
    InitPlayerNewLevel(Player_num);
  }

  // Set flags
  Level_started = true;
  Multi_bail_ui_menu = false;

  // Clear robot keys
  Global_keys = 0;

  // Clear OSIRIS stuff
  Osiris_ResetAllTimers();

  // Initialize IGC
  Cinematic_LevelInit();

  // Bash the language to english
  int save_lang = Localization_GetLanguage();
  Localization_SetLanguage(LANGUAGE_ENGLISH);

  // Load the English text so the goal stuff will initialize correctly
  LoadLevelText(Current_mission.levels[Current_mission.cur_level - 1].filename);

  // Restore the correct language
  Localization_SetLanguage(save_lang);

  // Init the level scripts
  InitLevelScript();

  // Load the localized text
  LoadLevelText(Current_mission.levels[Current_mission.cur_level - 1].filename);

  Gametime = 0.0f;
  // Start the clock
  InitFrameTime();

  LoadLevelProgress(LOAD_PROGRESS_DONE, 0);

}

// Loads a level and starts everything up
bool LoadAndStartCurrentLevel() {
  char hogpath[_MAX_PATH * 2];
  // This is a bit redundant because we just did it in most cases, but we need to be sure that it always happens,
  // and this code is here for weird systems, like save/load and demo, etc.
  if (Current_mission.filename && (stricmp(Current_mission.filename, "d3.mn3") == 0) &&
      (Current_mission.cur_level > 4)) {
    // close the mission hog file and open d3_2.mn3
    mn3_Close();
    ddio_MakePath(hogpath, D3MissionsDir, "d3_2.mn3", nullptr);
    if (cfexist(hogpath)) {
      mn3_Open(hogpath);
      mem_free(Current_mission.filename);
      Current_mission.filename = mem_strdup("d3_2.mn3");
    } else {
      SetFunctionMode(MENU_MODE);
    }
  } else if (Current_mission.filename && (stricmp(Current_mission.filename, "d3_2.mn3") == 0) &&
             (Current_mission.cur_level <= 4)) {
    // Part 2 of the mission is d3_2.mn3
    // close the mission hog file and open d3.mn3
    mn3_Close();
    ddio_MakePath(hogpath, D3MissionsDir, "d3.mn3", nullptr);
    if (cfexist(hogpath)) {
      mn3_Open(hogpath);
      mem_free(Current_mission.filename);
      Current_mission.filename = mem_strdup("d3.mn3");
    } else {
      SetFunctionMode(MENU_MODE);
    }
  }

  //	load the level. if fails, then bail out
  // ShowProgressScreen (TXT_LOADINGLEVEL);
  if (!LoadMissionLevel(Current_mission.cur_level))
    return false;

  AutomapClearVisMap();

  // Now start the level
  StartLevel();

  // Done!
  return true;
}

#ifdef EDITOR
// Called to do game initialization stuff when playing from the editor
// Mostly, this will be the same stuff as StartNewLevel()
void StartGameFromEditor() {
  // Set up the player ship
  InitPlayerNewShip(Player_num, INVRESET_ALL);

  // Start the level
  StartLevel();

  // Move the player to the editor viewer position
  ObjSetPos(Player_object, &editor_player_pos, editor_player_roomnum, &editor_player_orient, false);
}
#endif

void ComputeCenterPointOnFace(vector *vp, room *rp, int facenum);

// Start object ambient sounds
void StartObjectSounds() {
  for (int i = 0; i < MAX_OBJECTS; i++) {
    object *objp = &Objects[i];

    // If generic object, check for ambient sound
    switch (objp->type) {

    case OBJ_CLUTTER:
    case OBJ_BUILDING:
    case OBJ_ROBOT:
    case OBJ_POWERUP: {
      int ambient_sound = Object_info[objp->id].sounds[GSI_AMBIENT];
      if (ambient_sound != SOUND_NONE_INDEX)
        Sound_system.Play3dSound(ambient_sound, SND_PRIORITY_LOWEST, objp);
      break;
    }

    case OBJ_SOUNDSOURCE:
      ASSERT(objp->control_type == CT_SOUNDSOURCE);
      if (objp->name) // if has name, attach sound to object
        Sound_system.Play3dSound(objp->ctype.soundsource_info.sound_index, SND_PRIORITY_NORMAL, objp,
                                 objp->ctype.soundsource_info.volume);
      else { // no name, so attach to 3D position & delete object
        pos_state ps;
        ps.position = &objp->pos;
        ps.roomnum = objp->roomnum;
        ps.orient = (matrix *)&Identity_matrix;
        Sound_system.Play3dSound(objp->ctype.soundsource_info.sound_index, SND_PRIORITY_NORMAL, &ps,
                                 objp->ctype.soundsource_info.volume);
        ObjDelete(i);
      }
      break;
    }
  }
}

// Go through the level and start and sounds associated with textures
void StartTextureSounds() {
  int r, f;
  room *rp;
  face *fp;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
        int sound = GameTextures[fp->tmap].sound;
        if ((sound != -1) && (sound != SOUND_NONE_INDEX)) {
          vector pos;
          pos_state ps;
          ComputeCenterPointOnFace(&pos, rp, f);
          ps.position = &pos;
          ps.roomnum = r;
          ps.orient = (matrix *)&Identity_matrix;
          Sound_system.Play3dSound(sound, SND_PRIORITY_LOWEST, &ps);
        }
      }
    }
  }
}

// Starts all the sounds on this level
void StartLevelSounds() {
  StartObjectSounds();
  StartTextureSounds();
  StartTerrainSound();
  InitAmbientSounds();
}

// frees any data/esc that was created for that level
void FreeThisLevel() {
  if (!Level_started)
    return;

  bool original_controls = Control_poll_flag;

  Cinematic_Stop();

  // make sure our controls are correct (this is needed for failed missions)
  if (Control_poll_flag != original_controls) {
    if (Control_poll_flag)
      SuspendControls();
    else
      ResumeControls();
  }

  Multi_bail_ui_menu = false;

  DemoAbort();

  // closes hud.
  FreeCockpit();
  CloseShipHUD();

  //	end music sequencer's run.
  D3MusicStop();

  FreeScriptsForLevel();
  ClearAllEvents();

  // Resets the ambient life controller
  a_life.ALReset();

  DestroyAllMatcens();
  Level_goals.CleanupAfterLevel();

  Sound_system.StopAllSounds();

  // Clear out all memory that was used for this past level
  FlushDataCache();

  InitGamePaths(); // DAJ LEAKFIX

  DSSoarEnd();

  // Reset the camera if need be
  if (Player_camera_objnum != -1) {
    SetObjectDeadFlag(&Objects[Player_camera_objnum]);
    Player_camera_objnum = -1;
    Viewer_object = &Objects[Players[Player_num].objnum];
  }

  ResetHUDMessages();

  DestroyDefaultBSPTree();

  Level_started = false;
  IsRestoredGame = false;
}

extern void FreeTextureBumpmaps(int);
// Clears out all the level specific stuff from memory
void FlushDataCache() {
  int i;

  // This must be done before we free polymodels
  FreeAllObjects();

#ifdef EDITOR
  if (Network_up)
    return;
#endif

  int texfreed = 0;
  int modelsfreed = 0;
  int soundsfreed = 0;

  for (i = 0; i < MAX_TEXTURES; i++) {
    if (Textures_to_free[i] != 0) {
      if (!(GameTextures[i].flags & TF_ANIMATED)) {
        if (GameTextures[i].bumpmap != -1)
          FreeTextureBumpmaps(i);

        bm_FreeBitmapData(GameTextures[i].bm_handle);
      }

      texfreed++;
    }
  }
  for (i = 0; i < MAX_POLY_MODELS; i++) {
    if (Models_to_free[i] != 0) {
      FreePolymodelData(i);
      modelsfreed++;
    }
  }

  for (i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds_to_free[i] != 0)
    {
      soundsfreed++;
      int index = Sounds[i].sample_index;
      if (SoundFiles[index].sample_16bit) {
        mem_free(SoundFiles[index].sample_16bit);
        SoundFiles[index].sample_16bit = NULL;
      }
      if (SoundFiles[index].sample_8bit) {
        mem_free(SoundFiles[index].sample_8bit);
        SoundFiles[index].sample_8bit = NULL;
      }
    }
  }

  mprintf(0, "Freed %d textures, %d models, and %d sounds.\n", texfreed, modelsfreed, soundsfreed);
  // the renderer is never initialized in dedicated server mode, so don't try to reset things either
  if (!Dedicated_server) {
    rend_ResetCache();
  }
}

///////////////////////////////////////////////////////////////////////////////
//	Runs any possible end movie and stats screen, as well as loads in the next level
///////////////////////////////////////////////////////////////////////////////

// Parameter:	state -  1 = success, 0 = failure, -1 = abort
void EndLevel(int state) {
  tLevelNode *lvl = &Current_mission.levels[Current_mission.cur_level - 1];

  // Tells all the clients to end the level
  if ((Game_mode & GM_MULTI) && Netgame.local_role == LR_SERVER) {
    MultiSendLevelEnded(state, Multi_next_level);
    CallGameDLL(EVT_CLIENT_GAMELEVELEND, &DLLInfo);
    CallMultiDLL(MT_EVT_GAME_OVER);
  }

  if (!(Game_mode & GM_MULTI)) {

    // report the information to the pilot's mission data
    CurrentPilotUpdateMissionStatus();
    //		Sound_system.StopAllSounds();		-- moved to below because bug was reported that sounds were
    // playing in performance screen

    // save our shields (in case this call is due to starting a new level
    // in InitPlayerNewLevel, we'll determine if we should restore them
    // this function ALWAYS gets called right before InitPlayerNewLevel from StartLevel
    Player_shields_saved_from_last_level = Objects[Players[Player_num].objnum].shields;
    Player_energy_saved_from_last_level = Players[Player_num].energy;
  } else {
    // Stop all player sounds
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if (NetPlayers[i].flags & NPF_CONNECTED) {
        PlayerStopSounds(i);
        Players[i].flags &= ~(PLAYER_FLAGS_THRUSTED | PLAYER_FLAGS_AFTERBURN_ON);
      }
    }
  }

  // clear screen now.
  if (!Dedicated_server) {
    StartFrame();
    rend_ClearScreen(GR_BLACK);
    EndFrame();
    rend_Flip();
    Sound_system.StopAllSounds();
  }

  //	Sequencing here.
  // if this level has an endmovie
  if ((state == 1) && (lvl->flags & LVLFLAG_ENDMOVIE) && !(Game_mode & GM_MULTI)) {
    DoMissionMovie(lvl->endmovie);
  }

  //	display postlevel results.
  if ((state != -1) && (GetFunctionMode() != EDITOR_GAME_MODE))
    PostLevelResults(state == 1);

  // check for dead players
  if (Game_mode & GM_MULTI) {
    // in multiplayer check all players
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if ((NetPlayers[i].flags & NPF_CONNECTED) && (NetPlayers[i].sequence >= NETSEQ_PLAYING)) {
        // check to see if player is dying
        if ((Players[i].flags & PLAYER_FLAGS_DYING) || (Players[i].flags & PLAYER_FLAGS_DEAD)) {
          mprintf(0, "Prematurely ending death for player %d\n", i);
          EndPlayerDeath(i);
        }
      }
    }

  } else {
    // in single player, check Player_num
    if ((Players[Player_num].flags & PLAYER_FLAGS_DYING) || (Players[Player_num].flags & PLAYER_FLAGS_DEAD)) {
      mprintf(0, "Prematurely ending death for player\n");
      EndPlayerDeath(Player_num);
    }
  }

  //	Free any game objects/etc that needs to be done when ending a level here.
  FreeThisLevel();

  // This option is used for HEAT.NET. They have their dedicated server shut down after the
  // kill goal or time limit is reached.
  if (Dedicated_server) {
    if (FindArg("-quitongoal")) {
      SetFunctionMode(QUIT_MODE);
    }
  }
}

// Advances to the next level.  If we were on the last level, end the game
void SetNextLevel() {
  ASSERT(Current_mission.cur_level > 0);

  tLevelNode *lvl = &Current_mission.levels[Current_mission.cur_level - 1];

  if (Game_mode & GM_MULTI && Multi_next_level != -1) {
    SetCurrentLevel(Multi_next_level);
    Multi_next_level = -1;
  } else if (lvl->flags & LVLFLAG_BRANCH) {
    //	jump to brached level
    mprintf(0, "Branching...\n");
    Current_mission.cur_level = lvl->lvlbranch0;
    SetCurrentLevel(Current_mission.cur_level);
  } else if ((Current_mission.cur_level == Current_mission.num_levels) || (lvl->flags & LVLFLAG_FINAL)) {
    //	in this case we are done with the mission!
    DoEndMission();

    if (!(Game_mode & GM_MULTI)) // Multiplayer loops its levels and never ends
    {
      SetFunctionMode(MENU_MODE);
    }
  } else if (Current_mission.game_state_flags & MSN_STATE_SECRET_LEVEL) {
    if (lvl->flags & LVLFLAG_SPAWNSECRET) {
      // display secret level screen?
      ShowProgressScreen(TXT_ENTERSECRETLVL, NULL, true);
      Descent->delay(1.0f);
      Current_mission.game_state_flags &= (~MSN_STATE_SECRET_LEVEL);
      SetCurrentLevel(lvl->secretlvl);
    } else {
      Int3(); // Game says go to secret level, but there's none to go to.
      SetCurrentLevel(Current_mission.cur_level + 1);
    }
  } else {
    // nothing special
    SetCurrentLevel(Current_mission.cur_level + 1);
  }
}

void GameFrameUI() {
  GameFrame();
  Last_game_state = Game_state;
}

void RunGameMenu() {
  bool pause_game = false;

  if (Game_interface_mode != GAME_INTERFACE) {
    NewUIWindow_alpha = 226;
    SetUICallback(GameFrameUI);
    SuspendControls();

    // reset bail flag.
    Multi_bail_ui_menu = false;

    if (!(Game_mode & GM_MULTI)) {
      pause_game = true;
      PauseGame();
      D3MusicResume();
    }

    switch (Game_interface_mode) {
    case GAME_OPTIONS_INTERFACE: {
      extern void OptionsMenu();
      ui_ShowCursor();
      OptionsMenu();
      ui_HideCursor();
    } break;
    case GAME_HELP_INTERFACE: {
      ui_ShowCursor();
      HelpDisplay();
      ui_HideCursor();
    } break;
    case GAME_TOGGLE_DEMO: {
      ui_ShowCursor();
      DemoToggleRecording();
      ui_HideCursor();
    } break;
    case GAME_BUDDY_INTERFACE: {
      //			#ifdef DEMO
      //				DoMessageBox(TXT_ERROR, TXT_WRONGVERSION, MSGBOX_OK);
      //			#else
      ui_ShowCursor();
      BuddyDisplay();
      ui_HideCursor();
      //			#endif
    } break;
    case GAME_TELCOM_CARGO: {
      // #ifndef DEMO
      DoWaitPopup(true, TXT_TELCOMLOAD);
      ui_ShowCursor();
      TelComShow(TS_CARGO);
      ui_HideCursor();
      DoWaitPopup(false);
      // #else
      //	DoMessageBox(TXT_ERROR, TXT_WRONGVERSION, MSGBOX_OK);
      // #endif
    } break;
    case GAME_TELCOM_BRIEFINGS: {
      DoWaitPopup(true, TXT_TELCOMLOAD);
      ui_ShowCursor();
      TelComShow(TS_MAINMENU);
      ui_HideCursor();
      DoWaitPopup(false);
    } break;
    case GAME_TELCOM_AUTOMAP: {
      // #ifndef DEMO
      DoWaitPopup(true, TXT_TELCOMLOAD);
      ui_ShowCursor();
      TelComShow(TS_MAP);
      ui_HideCursor();
      DoWaitPopup(false);
      // #else
      //	DoMessageBox(TXT_ERROR, TXT_WRONGVERSION, MSGBOX_OK);
      // #endif
    } break;
    case GAME_PAUSE_INTERFACE:
      if (Game_mode & GM_MULTI)
        AddHUDMessage(TXT_NOPAUSEINMULTI);
      else {
        DoMessageBoxAdvanced(TXT(TXI_HLPPAUSE), TXT_PRESSOKTOCONT, TXT_OK, KEY_PAUSE, NULL);
        // DoMessageBox(TXT(TXI_HLPPAUSE),TXT_PRESSOKTOCONT, MSGBOX_OK);
      }
      break;
    case GAME_LEVEL_WARP:
      Level_warp_next = DisplayLevelWarpDlg(-1);
      if (Level_warp_next != -1)
        SetGameState(GAMESTATE_LVLWARP);
      break;
    case GAME_EXIT_CONFIRM: {
      int ret = 0;
      ui_ShowCursor();
      // Weird code for the training mission and the first time you play...
      if (Current_mission.filename && (stricmp(Current_mission.filename, "training.mn3") == 0) && (FirstGame)) {
        ret = DoMessageBoxAdvanced(TXT_TRAININGABORTTITLE, TXT_TRAININGABORTTEXT, TXT_SKIP, KEY_S, TXT_ABORT, KEY_A,
                                   TXT_CANCEL, KEY_ESC, NULL);
        if (ret == 2) {
          // Cancel
          ret = 0;
        } else if (ret == 1) {
          // Abort -- back to the main menu
          FirstGame = false;
        } else if (ret == 0) {
          // Skip
          ret = 1;
        }

      } else {
        ret = DoMessageBox(TXT_CONFIRM, TXT_CONFIRMEXIT, MSGBOX_YESNO);
      }
      if (ret) {
        Demo_looping = false;
        if ((Players[Player_num].flags & PLAYER_FLAGS_DYING) || (Players[Player_num].flags & PLAYER_FLAGS_DEAD)) {
          EndPlayerDeath(Player_num);
          if (Game_mode & GM_MULTI) {
            MultiSendEndPlayerDeath();
            MultiLeaveGame();
          }
          SetFunctionMode(MENU_MODE);
        } else {
          if (Game_mode & GM_MULTI)
            MultiLeaveGame();
          SetFunctionMode(MENU_MODE);
        }
        Sound_system.StopAllSounds();
      }
    } break;
    case GAME_DLL_INTERFACE: {
      DLLInfo.me_handle = DLLInfo.it_handle = OBJECT_HANDLE_NONE;
      ui_ShowCursor();
      CallGameDLL(EVT_CLIENT_SHOWUI, &DLLInfo);
      ui_HideCursor();
    } break;

    case GAME_DEBUGGRAPH_INTERFACE: {
      DebugGraph_DisplayOptions();
    } break;

    case GAME_SAVE_INTERFACE:
      ui_ShowCursor();
#ifdef EDITOR
      if (GetFunctionMode() == EDITOR_GAME_MODE)
        DoMessageBox("Silly", "You can't save while playing from the editor!", MSGBOX_OK);
      else
#endif
        SaveGameDialog(); // link to above endif!
      ui_HideCursor();
      break;

    case GAME_LOAD_INTERFACE:
      ui_ShowCursor();
#ifdef EDITOR
      if (GetFunctionMode() == EDITOR_GAME_MODE)
        DoMessageBox("Silly", "You can't load while playing from the editor!", MSGBOX_OK);
      else
#endif
        LoadGameDialog();
      ui_HideCursor();
      break;

    case GAME_POST_DEMO:
      DemoPostPlaybackMenu();
      SetFunctionMode(MENU_MODE);
      break;
    case GAME_DEMO_LOOP:
      SetFunctionMode(MENU_MODE);
      break;
    default:
      Int3(); // unhandled game interface mode
    }

    if (pause_game) {
      ResumeGame();
      pause_game = false;
    }

    ResumeControls();
    SetUICallback(NULL);
    Game_interface_mode = GAME_INTERFACE;
    NewUIWindow_alpha = 192;
    Clear_screen = 4;
  }
}

void PageInLevelTexture(int id) {
  if (id == -1 || id == 0)
    return;

  if (Dedicated_server)
    return;

  TouchTexture(id);

  // Upload all these textures to the card
  if (GameTextures[id].flags & TF_ANIMATED) {
    vclip *vc = &GameVClips[GameTextures[id].bm_handle];
    for (int i = 0; i < vc->num_frames; i++) {
      if (!(GameTextures[id].flags & TF_PROCEDURAL) && !(GameTextures[id].flags & TF_SPECULAR))
        GameBitmaps[vc->frames[i]].flags |= BF_COMPRESSABLE;
      else
        GameBitmaps[vc->frames[i]].flags &= ~BF_COMPRESSABLE;

      if (!Dedicated_server && GameBitmaps[vc->frames[i]].cache_slot == -1)
        rend_PreUploadTextureToCard(vc->frames[i], MAP_TYPE_BITMAP);
    }
  } else {
    if (!(GameTextures[id].flags & TF_PROCEDURAL) && !(GameTextures[id].flags & TF_SPECULAR))
      GameBitmaps[GameTextures[id].bm_handle].flags |= BF_COMPRESSABLE;
    else
      GameBitmaps[GameTextures[id].bm_handle].flags &= ~BF_COMPRESSABLE;

    if (!Dedicated_server && GameBitmaps[GameTextures[id].bm_handle].cache_slot == -1)
      rend_PreUploadTextureToCard(GameTextures[id].bm_handle, MAP_TYPE_BITMAP);
  }

  if (GameTextures[id].flags & TF_DESTROYABLE && GameTextures[id].destroy_handle != -1)
    PageInLevelTexture(GameTextures[id].destroy_handle);

  Textures_to_free[id] = 1;
}

bool PageInSound(int id) {
  if (id == -1)
    return false;

  if (Dedicated_server)
    return false;

  // sometimes, id passed was 0xffff which seems like a int16_t -1.  The if statement
  // ensures that the array Sounds_to_free is dealt with properly.
  if (Sound_system.CheckAndForceSoundDataAlloc(id)) {
    Sounds_to_free[id] = 1;
    return true;
  }

  return false;
}

void PageInDoor(int id) {
  // Set sounds
  door *doorpointer = &Doors[id];

  PageInPolymodel(doorpointer->model_handle);
  Models_to_free[doorpointer->model_handle] = 1;

  poly_model *pm = &Poly_models[doorpointer->model_handle];
  for (int t = 0; t < pm->n_textures; t++)
    PageInLevelTexture(pm->textures[t]);

  if (doorpointer->open_sound != -1 && doorpointer->open_sound != SOUND_NONE_INDEX)
    PageInSound(doorpointer->open_sound);
  if (doorpointer->close_sound != -1 && doorpointer->close_sound != SOUND_NONE_INDEX)
    PageInSound(doorpointer->close_sound);
}

void PageInWeapon(int id) {
  weapon *weaponpointer = &Weapons[id];

  if (id == -1)
    return;

  int i;

  if (!(weaponpointer->flags & (WF_IMAGE_BITMAP | WF_IMAGE_VCLIP))) {
    PageInPolymodel(weaponpointer->fire_image_handle);
    Models_to_free[weaponpointer->fire_image_handle] = 1;

    poly_model *pm = &Poly_models[weaponpointer->fire_image_handle];
    for (int t = 0; t < pm->n_textures; t++)
      PageInLevelTexture(pm->textures[t]);
  }

  // Load the various textures associated with this weapon
  if (weaponpointer->explode_image_handle != -1) {
    PageInLevelTexture(weaponpointer->explode_image_handle);
  }

  if (weaponpointer->particle_handle != -1) {
    PageInLevelTexture(weaponpointer->particle_handle);
  }

  if (weaponpointer->smoke_handle != -1) {
    PageInLevelTexture(weaponpointer->smoke_handle);
  }

  if (weaponpointer->scorch_handle != -1) {
    PageInLevelTexture(weaponpointer->scorch_handle);
  }

  if (weaponpointer->icon_handle != -1) {
    PageInLevelTexture(weaponpointer->icon_handle);
  }

  // Try to load spawn weapons
  if (weaponpointer->spawn_handle != -1 && weaponpointer->spawn_count > 0 && weaponpointer->spawn_handle != id) {
    PageInWeapon(weaponpointer->spawn_handle);
  }

  if (weaponpointer->alternate_spawn_handle != -1 && weaponpointer->spawn_count > 0 &&
      weaponpointer->alternate_spawn_handle != id) {
    PageInWeapon(weaponpointer->alternate_spawn_handle);
  }

  if (weaponpointer->robot_spawn_handle != -1) {
    PageInGeneric(weaponpointer->robot_spawn_handle);
  }

  // Try and load the various sounds
  for (i = 0; i < MAX_WEAPON_SOUNDS; i++) {
    if (weaponpointer->sounds[i] != SOUND_NONE_INDEX) {
      PageInSound(weaponpointer->sounds[i]);
    }
  }
}
int paged_in_count = 0;
extern int need_to_page_in;
extern int need_to_page_num;
int paged_in_num = 0;

// #define PAGED_IN_CALC paged_in_count ? (float)paged_in_count/(float)need_to_page_in : 0.0f
#define PAGED_IN_CALC paged_in_num ? (float)paged_in_num / (float)need_to_page_num : 0.0f
void PageInShip(int id) {
  int i, t;

  ship *shippointer = &Ships[id];

  // Page in all textures for this object

  PageInPolymodel(shippointer->model_handle);
  Models_to_free[shippointer->model_handle] = 1;

  poly_model *pm = &Poly_models[shippointer->model_handle];

  for (t = 0; t < pm->n_textures; t++) {
    PageInLevelTexture(pm->textures[t]);
    // Create bumps if neccessary
    if (rend_SupportsBumpmapping()) {
      if (GameTextures[pm->textures[t]].bumpmap == -1) {
        mprintf(0, "Trying to make bumpmap!\n");
        BuildTextureBumpmaps(pm->textures[t]);
      }
    }
  }

  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  if (shippointer->med_render_handle != -1) {
    PageInPolymodel(shippointer->med_render_handle);
    Models_to_free[shippointer->med_render_handle] = 1;

    pm = &Poly_models[shippointer->med_render_handle];
    for (t = 0; t < pm->n_textures; t++)
      PageInLevelTexture(pm->textures[t]);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  if (shippointer->lo_render_handle != -1) {
    PageInPolymodel(shippointer->lo_render_handle);
    Models_to_free[shippointer->lo_render_handle] = 1;

    pm = &Poly_models[shippointer->lo_render_handle];
    for (t = 0; t < pm->n_textures; t++)
      PageInLevelTexture(pm->textures[t]);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  if (shippointer->dying_model_handle != -1) {
    PageInPolymodel(shippointer->dying_model_handle);
    Models_to_free[shippointer->dying_model_handle] = 1;

    pm = &Poly_models[shippointer->dying_model_handle];
    for (t = 0; t < pm->n_textures; t++)
      PageInLevelTexture(pm->textures[t]);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  // Try and load the various weapons
  int j;
  if (shippointer->static_wb) {
    for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
      for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
        if (shippointer->static_wb[i].gp_weapon_index[j] != LASER_INDEX) {
          PageInWeapon(shippointer->static_wb[i].gp_weapon_index[j]);
          LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
        }
      }
    }
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  // Try and load the various weapons
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      if ((j % 5) == 0)
        LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
      if (shippointer->static_wb[i].fm_fire_sound_index[j] != SOUND_NONE_INDEX)
        PageInSound(shippointer->static_wb[i].fm_fire_sound_index[j]);
    }
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    if ((i % 5) == 0)
      LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
    if (shippointer->firing_sound[i] != -1)
      PageInSound(shippointer->firing_sound[i]);

    if (shippointer->firing_release_sound[i] != -1)
      PageInSound(shippointer->firing_release_sound[i]);

    if (shippointer->spew_powerup[i] != -1)
      PageInGeneric(shippointer->spew_powerup[i]);
  }
}

void PageInGeneric(int id) {
  int i, t;

  if (id == -1)
    return;

  object_info *objinfopointer = &Object_info[id];

  // Page in all textures for this object

  PageInPolymodel(objinfopointer->render_handle);
  Models_to_free[objinfopointer->render_handle] = 1;

  poly_model *pm = &Poly_models[objinfopointer->render_handle];

  for (t = 0; t < pm->n_textures; t++) {
    PageInLevelTexture(pm->textures[t]);

    // Create bumps if neccessary
    if (objinfopointer->type == OBJ_ROBOT && rend_SupportsBumpmapping()) {
      if (GameTextures[pm->textures[t]].bumpmap == -1)
        BuildTextureBumpmaps(pm->textures[t]);
    }
  }

  if (objinfopointer->med_render_handle != -1) {
    PageInPolymodel(objinfopointer->med_render_handle);
    Models_to_free[objinfopointer->med_render_handle] = 1;

    pm = &Poly_models[objinfopointer->med_render_handle];
    for (t = 0; t < pm->n_textures; t++)
      PageInLevelTexture(pm->textures[t]);
  }

  if (objinfopointer->lo_render_handle != -1) {
    PageInPolymodel(objinfopointer->lo_render_handle);
    Models_to_free[objinfopointer->lo_render_handle] = 1;

    pm = &Poly_models[objinfopointer->lo_render_handle];
    for (t = 0; t < pm->n_textures; t++)
      PageInLevelTexture(pm->textures[t]);
  }

  // Process all sounds for this object
  for (i = 0; i < MAX_OBJ_SOUNDS; i++) {
    if (objinfopointer->sounds[i] != SOUND_NONE_INDEX) {
      PageInSound(objinfopointer->sounds[i]);
    }
  }

  if (objinfopointer->ai_info) {
    for (i = 0; i < MAX_AI_SOUNDS; i++) {
      if (objinfopointer->ai_info->sound[i] != SOUND_NONE_INDEX) {
        PageInSound(objinfopointer->ai_info->sound[i]);
      }
    }
  }
  // Try and load the various wb sounds
  int j;
  if (objinfopointer->static_wb) {
    for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
      for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
        if (objinfopointer->static_wb[i].fm_fire_sound_index[j] != SOUND_NONE_INDEX) {
          PageInSound(objinfopointer->static_wb[i].fm_fire_sound_index[j]);
        }
      }
    }
  }
  // Try and load the various wb sounds
  if (objinfopointer->anim) {
    for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
      for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
        if (objinfopointer->anim[i].elem[j].anim_sound_index != SOUND_NONE_INDEX) {
          PageInSound(objinfopointer->anim[i].elem[j].anim_sound_index);
        }
      }
    }
  }

  // Load the spew types
  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    if (objinfopointer->dspew_number[i] > 0 && objinfopointer->dspew[i] != 0 && objinfopointer->dspew[i] != id) {
      PageInGeneric(objinfopointer->dspew[i]);
    }
  }

  // Try and load the various weapons

  // Automatically include laser
  PageInWeapon(LASER_INDEX);

  if (objinfopointer->static_wb) {
    for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
      for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
        if (objinfopointer->static_wb[i].gp_weapon_index[j] != LASER_INDEX) {
          PageInWeapon(objinfopointer->static_wb[i].gp_weapon_index[j]);
        }
      }
    }
  }
}

extern const char *Static_sound_names[];

void PageInAllData() {
  int i;
  paged_in_count = 0;
  paged_in_num = 0;
  memset(Textures_to_free, 0, MAX_TEXTURES);
  memset(Sounds_to_free, 0, MAX_SOUNDS);
  memset(Models_to_free, 0, MAX_POLY_MODELS);

  PageInShip(Players[Player_num].ship_index);
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  /*
  $$TABLE_TEXTURE "LightFlareStare"
  $$TABLE_TEXTURE "LightFlare"
  */
  PageInLevelTexture(FindTextureName(IGNORE_TABLE("LightFlareStar")));
  PageInLevelTexture(FindTextureName(IGNORE_TABLE("LightFlare")));

  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);

  if (PreferredRenderer == RENDERER_DIRECT3D) {
    if (LightmapInfo && !Dedicated_server) {
      if (!NoLightmaps) {
        for (i = 0; i < MAX_LIGHTMAP_INFOS; i++) {
          if (LightmapInfo[i].used && LightmapInfo[i].type != LMI_DYNAMIC) {
            if (!Dedicated_server && GameLightmaps[LightmapInfo[i].lm_handle].cache_slot == -1) {
              rend_PreUploadTextureToCard(LightmapInfo[i].lm_handle, MAP_TYPE_LIGHTMAP);
            }
          }
        }
      }
    }
  }

  // Get static fireballs
  for (i = 0; i < NUM_FIREBALLS; i++) {
    char name[PAGENAME_LEN];
    strcpy(name, Fireballs[i].name);

    name[strlen(name) - 4] = 0;
    int id = FindTextureName(name);
    if (id != -1)
      PageInLevelTexture(id);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  // Get static sounds
  for (i = 0; i < NUM_STATIC_SOUNDS; i++) {
    int sid = FindSoundName(Static_sound_names[i]);

    if (sid != -1)
      PageInSound(sid);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);

  // First get textures
  for (i = 0; i <= Highest_room_index; i++) {
    if ((i % 15) == 0)
      LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);

    if (!Rooms[i].used)
      continue;

    room *rp = &Rooms[i];
    for (int t = 0; t < rp->num_faces; t++) {
      PageInLevelTexture(rp->faces[t].tmap);
    }
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);

  // Touch all terrain textures
  for (i = 0; i < TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH; i++) {
    PageInLevelTexture(Terrain_tex_seg[i].tex_index);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  if (Terrain_sky.textured) {
    PageInLevelTexture(Terrain_sky.dome_texture);
  }
  LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
  for (i = 0; i < Terrain_sky.num_satellites; i++)
    PageInLevelTexture(Terrain_sky.satellite_texture[i]);

  // Touch all objects
  for (i = 0; i <= Highest_object_index; i++) {
    if ((i % 20) == 0)
      LoadLevelProgress(LOAD_PROGRESS_PAGING_DATA, PAGED_IN_CALC);
    object *obj = &Objects[i];
    if (obj->type == OBJ_POWERUP || obj->type == OBJ_ROBOT || obj->type == OBJ_CLUTTER || obj->type == OBJ_BUILDING) {
      PageInGeneric(obj->id);
      continue;
    }

    if (obj->type == OBJ_DOOR) {
      PageInDoor(obj->id);
      continue;
    }
  }
  LoadLevelProgress(LOAD_PROGRESS_PREPARE, 0);
}
