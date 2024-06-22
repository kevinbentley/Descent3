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

 * $Logfile: /DescentIII/Main/init.cpp $
 * $Revision: 323 $
 * $Date: 10/22/01 12:42p $
 * $Author: Matt $
 *
 * Initialization of D3 systems
 *
 * $Log: /DescentIII/Main/init.cpp $
 *
 * 323   10/22/01 12:42p Matt
 * Added MercInstalled() function.
 *
 * 322   10/03/01 12:45a Kevin
 * Smaller version of pxo packets
 *
 * 321   9/15/01 1:46p Kevin
 * Added -nocrashbox to suppress crash dialog box
 *
 * 320   9/14/01 4:47p Matt
 * Cleaned up problems when screen bit depth set to 32.
 *
 * 319   9/14/01 12:50p Matt
 * Took out code that bashed the missile view ot left if it was set to
 * center.  It's now not possible to set the view to center in the config
 * menu.
 *
 * 318   4/19/00 5:36p Matt
 * Added command-line option to adjust mouse sensitivity
 *
 * 317   3/20/00 12:11p Matt
 * Merge of Duane's post-1.3 changes.
 * Misc Mac stuff: movie, int'l keyboards, loading screens (Mac only)
 *
 * 316   1/26/00 9:20p Jeff
 * added support for IntelliVIBE DLL
 *
 * 315   12/01/99 3:58p Jeff
 * one last time...linux pregamecdcheck bug fix
 *
 * 314   12/01/99 3:30p Jeff
 * set CD_inserted to 1 for Linux
 *
 * 313   11/30/99 5:07p Jeff
 * no pregame cd check for Linux (for now)
 *
 * 312   10/26/99 3:30p Jeff
 * handle extra.gam addon tablefile
 *
 * 311   10/25/99 3:09p Kevin
 * added -mlooksens
 *
 * 310   10/25/99 9:48a Matt
 * Mac code that should enable the dynamic allocation of lightmap_info
 * structures.  This should be disabled for editor builds.
 *
 * 309   10/25/99 12:47a Chris
 * Fixed a long overdue bug with zero rad wall collison objects and
 * colliding
 *
 * 308   10/22/99 10:52p Matt
 * Mac merge
 *
 * 307   10/22/99 10:43p Jeff
 * put in a variable to detect whether we are running the editor (needed
 * in manage system, which can't use EDITOR define)
 *
 * 306   10/19/99 4:55p Jeff
 * removed compiler warning
 *
 * 305   10/19/99 12:44p Chris
 * Fixed a small bug with the registery check
 *
 * 304   10/18/99 1:59p Chris
 * Added the ability to load the merc. hog
 *
 * 303   10/17/99 3:55p Jeff
 * Linux movie stuff
 *
 * 302   10/12/99 11:03a Jeff
 * if there is a -mission command line option, open that mn3 right after
 * d3.hog for any overridables
 *
 * 301   10/06/99 2:04p Kevin
 * copy protection fix to match the 1.2 full cd
 *
 * 300   10/05/99 10:11a Kevin
 * Don't show tantrum logo on macintosh demo (per GraphSim's Request)
 *
 * 299   10/05/99 9:46a Kevin
 * copy protection can now handle US/AUS & ROW no LL versions in one exe
 *
 * 298   9/29/99 8:05a Kevin
 * Changes to copy protection to allow for us and ROW-NONLL versions to
 * use the same exe
 *
 * 297   9/24/99 12:01p Samir
 * use directinput when -alternatejoy is selected (like 1.0)
 *
 * 296   9/23/99 2:59p Kevin
 * mac dll hog file
 *
 * 295   9/20/99 5:35p Jeff
 * added -nosparkles command line option to turn off powerup sparkles
 *
 * 294   9/18/99 9:21p Jeff
 * Init motion blur if we are a Katmai
 *
 * 293   8/20/99 9:45a Kevin
 * Rankings changes!
 *
 * 292   7/30/99 5:24p Samir
 * use no joystick emulation by default.
 *
 * 291   7/29/99 12:27p Chris
 * FIxed a mismatched paren
 *
 * 290   7/28/99 5:11p Kevin
 * Mac merges
 *
 * 289   7/26/99 5:19p Kevin
 * fixed copy protection for DVD drives
 *
 * 288   7/12/99 6:44p Jeff
 * create a lock file in the temp directory, if one already exists (for a
 * program in use), then don't allow the use of the temp directory
 *
 * 287   7/08/99 5:44p Jason
 * added default framecap of 60 to deal with stuttering issues
 *
 * 286   7/06/99 5:54p Kevin
 * more foriegn versions....
 *
 * 285   6/24/99 8:10p Jeff
 * added support for OpenGL renderer
 *
 * 284   6/24/99 3:15p Jeff
 * don't check renderer in Linux if dedicated
 *
 * 283   6/22/99 7:03p Jeff
 * added command line arguments to set renderer for Linux (Glide only
 * right now)
 *
 * 282   6/21/99 2:12p Kevin
 * South american version changes
 *
 * 281   6/17/99 11:34a Kevin
 *
 * 280   6/16/99 12:04p Kevin
 * Warning!!! This is a laserlocked version!
 *
 * 279   6/11/99 1:15a Samir
 * localization issues.
 *
 * 278   6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 277   6/03/99 8:48a Kevin
 * fixes for new OEM version....
 *
 * 276   5/24/99 6:20a Kevin
 * fixed dedicated server & copy protection
 *
 * 275   5/24/99 2:13a Matt
 * Fixed -superlowmem switch.
 *
 * 274   5/23/99 3:03p Kevin
 * real dist. checksums
 *
 * 273   5/23/99 2:38a Kevin
 * Lame ass(tm) copy protection
 *
 * 272   5/21/99 10:05a Kevin
 * Added stuff for a future DVD version
 *
 * 271   5/19/99 11:47a Kevin
 * made the parent window of the message box actually be Descent 3.
 *
 * 270   5/18/99 10:31a Kevin
 * made the us version only work with US english and US canadian languages
 *
 * 269   5/12/99 2:24p Jeff
 * Descent3 now has a setable temp directory for all temp files
 *
 * 268   5/12/99 1:18p Samir
 * play music during game too when in menus.
 *
 * 267   5/11/99 1:19a Samir
 * upped music volume, set default to 0.5
 *
 * 266   5/10/99 9:25p Jeff
 * first phase of Rock 'n' Ride support added
 *
 * 265   5/10/99 8:49p Jason
 * added vsync command line switch
 *
 * 264   5/10/99 5:35p Kevin
 * New command line options for heat and scoring API enhancements
 *
 * 263   5/07/99 6:54p Jason
 * fixed some gamegauge issues
 *
 * 262   5/07/99 12:04p Samir
 * added support for foreign keyboards and error text.
 *
 * 261   5/06/99 6:11p Kevin
 * fixes for save/load game syste. Also require CD again and added some
 * heat.net stuff
 *
 * 260   5/05/99 11:16p Kevin
 * heat.net stuff among other things
 *
 * 259   5/05/99 5:46p Samir
 * took out call to ResumeSounds when restoring from an Alt-tab.
 *
 * 258   5/02/99 9:13a Jeff
 * added system specific hog files (d3-linux.hog for Linux)
 *
 * 257   5/01/99 4:24p Jeff
 * fixed some windows specific code for Linux (*grrrr*)
 *
 * 256   4/30/99 10:53p Samir
 * store pilot settings in a temporary buffer when multitasking.
 *
 * 255   4/30/99 5:06p Kevin
 * misc dedicated server, networking and low memory enhancements
 *
 * 254   4/29/99 10:01p Samir
 * use emulation mode of joystick first.
 *
 * 253   4/29/99 5:53p Kevin
 * Made it so Japanese people can't play D3... well that is only if their
 * computers have the Japanese language installed. I'm not prejudice or
 * anything....It's just that Interplay doesn't want the english version
 * selling in Japan or something like that. :)
 *
 * 252   4/29/99 2:28p Kevin
 * Laserlock implementation
 *
 * 251   4/27/99 9:59p Kevin
 * CD not requred for dedicated server. Also improved demo playback
 *
 * 250   4/27/99 2:10p Samir
 * added code to set the desired sound card given the descriptive name of
 * a sound card.
 *
 * 249   4/26/99 9:11p Matt
 * Use small font instead of old UI font.
 *
 * 248   4/26/99 11:34a Samir
 * don't resume sounds if game was paused when alt-tabbing back
 * (ResumeGame will do the trick.)
 *
 * 247   4/25/99 6:14p Kevin
 * added "-timetest file.dem" to behave like gamegauge does
 *
 * 246   4/25/99 4:15p Matt
 * Added code to manually allow the user to specifiy the screen aspect
 * ratio, to make the game work with wide-screen TVs.
 *
 * 245   4/25/99 1:27p Matt
 * Fixed small bug
 *
 * 244   4/22/99 9:53a Kevin
 * Fixed some dedicated server crashes
 *
 * 243   4/20/99 11:44a Jeff
 * get the language type from the registry
 *
 * 242   4/17/99 7:42p Samir
 * Don't save out renderer and sound mixer in release version since the
 * launcher should only do this.
 *
 * 241   4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 240   4/16/99 12:03a Jeff
 * removed cd check for Linux
 *
 * 239   4/15/99 3:48p Samir
 * set mouse mode when ddio is initialized.
 *
 * 238   4/15/99 2:32p Kevin
 * Added some code for the Demo
 *
 * 237   4/15/99 10:57a Kevin
 * cd check only in release builds
 *
 * 236   4/15/99 9:25a Kevin
 * CD check fixes and updates
 *
 * 235   4/14/99 3:07p Kevin
 * Fixed some multiple CD bugs
 *
 * 234   4/14/99 12:35p Samir
 * localization issues.
 *
 * 233   4/14/99 11:48a Matt
 * Don't set messagebox title for release builds
 *
 * 232   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 231   4/12/99 7:15p Samir
 * added ability to configure number of sounds played at one time.
 *
 * 230   4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 229   4/06/99 4:15p Nate
 * Fixed UpdateInitMessage in editor (samir)
 *
 * 228   4/06/99 1:53p Samir
 * added improved progress bar.
 *
 * 227   4/05/99 9:53a Kevin
 * Took out the splash screens Craig made me add while he was smoking
 * crack.
 *
 * 226   4/04/99 8:15p Jeff
 * added debug graph stuff
 *
 * 225   4/03/99 1:24p Jason
 * changed some wording for loading screen
 *
 * 224   4/02/99 7:04p Kevin
 * Added splash screens do release builds
 *
 * 223   4/02/99 5:08p Matt
 * Added intro movie.
 *
 * 222   4/02/99 3:49p Kevin
 * Added profanity filter code
 *
 * 221   4/02/99 1:26p Matt
 * Changes I made for the OEM version but forgot to check in.  Oops.
 *
 * 220   3/19/99 4:08p Kevin
 * Multiple CD installation support
 *
 * 219   3/09/99 12:34p Jeff
 * extract scripts to custom\cache
 *
 * 218   3/08/99 3:29p Samir
 * RestartD3 ddio_Init key emulation = true.
 *
 * 217   3/05/99 5:23p Jeff
 * extract scripts from extra.hog before d3.hog
 *
 * 216   3/04/99 1:15p Jeff
 * erase temporary files that may have been left over from last run
 *
 * 215   3/02/99 5:21p Jason
 * fixed some flip bugs
 *
 * 214   3/02/99 2:21p Samir
 * windows 95 and NT both use same keyboard handler due to flaky
 * directinput.
 *
 * 213   3/02/99 1:49a Mark
 * put ifdefs around showstaticscreen
 *
 * 212   3/02/99 12:16a Jeff
 *
 * 211   3/02/99 12:06a Kevin
 *
 * 210   3/01/99 11:48p Jeff
 * fixed prototype placement
 *
 * 209   3/01/99 11:47p Kevin
 *
 * 208   3/01/99 11:38p Kevin
 *
 * 207   3/01/99 9:03p Kevin
 * OEM Beta 4
 *
 * 206   2/19/99 10:31p Samir
 * added music volume.
 *
 * 205   2/17/99 12:38p Kevin
 * Added -framecap <fps> to limit frame and fixed timer bug and old
 * framerate limiter code.
 *
 * 204   2/16/99 12:00p Samir
 * added new video resolution swtich test.
 *
 * 203   2/16/99 12:36a Kevin
 * Fixes for release builds of OEM V3 and KAtmai
 *
 * 202   2/15/99 3:24p Kevin
 *
 * 201   2/15/99 3:23p Kevin
 * Disabled procedurals for gamegauge
 *
 * 200   2/15/99 3:20p Kevin
 * Fixed bug with dlls in a hog
 *
 * 199   2/15/99 1:22p Kevin
 * Changes for GameGauge
 *
 * 198   2/11/99 10:35p Jeff
 * added support for multiple languages in string table files
 *
 * 197   2/10/99 3:29p Jeff
 * extracted dll manager knows difference between game hogs and miission
 * hogs
 *
 * 196   2/09/99 1:29a Jeff
 * added code to let D3 process multiplayer games in the background if
 * game is not in focus.
 *
 * 195   2/08/99 2:24p Kevin
 * Display bundler.mve and bundler.tga if they are included in the OEM
 * package.
 *
 * 194   2/05/99 7:23p Kevin
 * OEM Changes
 *
 * 193   2/04/99 9:46a Kevin
 * OEM version changes
 *
 * 192   1/31/99 8:51p Jeff
 * new in game cinematics system finished
 *
 * 191   1/29/99 5:22p Jeff
 * localization
 *
 * 190   1/27/99 6:08p Jason
 * first pass at markers
 *
 * 189   1/27/99 2:58p Jason
 * fixed center small view
 *
 * 188   1/25/99 6:47p Samir
 * allow slow keyboard
 *
 * 187   1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 186   1/25/99 12:33a Jeff
 * save out scorch marks and weapon corona detail settings
 *
 * 185   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 184   1/17/99 10:41p Kevin
 * Added command line options for setting the renderer in GAMEGAUGE mode.
 *
 * 183   1/13/99 3:25p Jason
 * fixed vsync problem
 *
 * 182   1/08/99 2:58p Kevin
 * Added TCP mprintf support so you can log to a remote machine.
 *
 * 181   1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 180   1/07/99 12:28p Samir
 * Call to InitD3Music added parameter.
 *
 * 179   1/05/99 3:59p Kevin
 *
 * 178   1/05/99 3:55p Kevin
 * Added structured exception handling
 *
 * 177   1/04/99 5:43p Kevin
 * new command line args
 *
 * 176   12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 175   12/16/98 12:04p Kevin
 * GameSpy!
 *
 * 174   12/14/98 4:48p Jeff
 * call to intialize Osiris module manager
 *
 * 173   12/10/98 3:41p Jeff
 * implemented settings for 16 or 32 bit depth (in config)
 *
 * 172   12/07/98 11:30a Kevin
 * Added some features from the 1.1 demo patch
 *
 * 171   12/02/98 1:07p Jason
 * made vsync work correctly, finally
 *
 * 170   11/24/98 5:17p Jeff
 * initialize Pilot Pics
 *
 * 169   11/23/98 12:31p Jeff
 * save out force feedback stuff (bad merge, we lost it earlier)
 *
 * 168   11/13/98 2:29p Samir
 * new music code.
 *
 * 166   11/09/98 2:59p Kevin
 * Added command line option for disabling multiplayer bitmap exchange
 *
 * 165   11/03/98 6:43p Jeff
 * new low-level & high level Force Feedback system implemented, handles
 * window losing focus, etc.
 *
 * 164   10/24/98 2:18p Samir
 * don't do mouse stuff for dedicated server.
 *
 * 163   10/22/98 2:42p Samir
 * fixed ALT-TAB pause issue.
 *
 * 162   10/22/98 1:58p Kevin
 * Fixed the working directory (-setdir) command
 *
 * 161   10/22/98 1:39p Jeff
 * autolevel is default full
 *
 * 160   10/20/98 6:24p Jason
 * added super low memory mode
 *
 * 159   10/20/98 10:56a Sean
 * fixed #ifdef editor thingy
 *
 * 158   10/20/98 12:58a Jeff
 * added a way to force a lo-resolution timer
 *
 * 157   10/20/98 12:10a Samir
 * this should fix the problem of the mouse not working properly in game.
 *
 * 156   10/19/98 6:30p Jeff
 * changes made for detail variables.  Put in preset values.  Preset
 * options.  Removed terrain_cast from detail.  Put new callbacks in
 * UIListBox and UISlider
 *
 * 153   10/18/98 9:12p Matt
 * Use new symbolic constant for the program name.
 *
 * 152   10/18/98 8:51p Matt
 * Revamped debug/error system.
 *
 * 151   10/18/98 3:36p Jeff
 * if _DEBUG isn't defined than the rtp_enable/disableflags call gets
 * compiled out
 *
 * 150   10/18/98 2:50p Kevin
 * Use low memory mode in dedicated server mode.
 *
 * 149   10/17/98 5:50p Jeff
 * hooked in rtperformance (run time performance) library
 *
 * 148   10/17/98 12:46p Kevin
 * Beta 4 fixes
 *
 * 147   10/16/98 2:44p Kevin
 * working on getting demo compiling
 *
 * 146   10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 145   10/15/98 1:33p Jeff
 * removed amount of debris detail level.  Added powerup halo detail
 * level.  Added predef detail level settings
 *
 * 144   10/15/98 11:58a Kevin
 * checked for low mem
 *
 * 143   10/14/98 4:37p Matt
 * Made InitD3System() exit with error if there's a problem instead of
 * returning a status value.  Also moved some editor-specific code from
 * init.cpp to mainfrm.cpp, and cleaned up some other initialization and
 * error-handling code.
 *
 * 142   10/13/98 3:47p Samir
 * added function to check if a cursor is visible
 *
 * 141   10/13/98 3:41p Kevin
 * bug fixes
 *
 * 140   10/13/98 2:49p Matt
 * Open "extra.hog" (if it exists" at startup so we can put any extra data
 * in there.
 *
 * 139   10/12/98 3:01p Jeff
 * added vsync and more detail level settings
 *
 * 138   10/12/98 2:51p Samir
 * use main menu background for loading data screen.
 *
 * 137   10/09/98 8:47p Samir
 * don't kill sound library when shutting down game.
 *
 * 136   10/08/98 7:27p Samir
 * don't change defer handlers when shuting down or restarting.
 *
 * 135   10/08/98 5:55p Matt
 * Set main hogfile.
 *
 * 134   10/08/98 3:36p Jason
 * fixes for the demo
 *
 * 133   10/08/98 1:23p Samir
 * shutdown and reinit now do so with ddio systems.
 *
 * 132   10/07/98 2:54p Jeff
 * General UI fixes and additions
 *
 * 131   10/07/98 12:55p Jason
 * fixed some defaults
 *
 * 130   10/03/98 11:21p Matt
 * Added system to seperately control outline mode for mine, terrain, sky,
 * & objects
 *
 * 129   10/01/98 11:57a Matt
 * Added some mprintf()s
 *
 * 128   9/30/98 10:36a Kevin
 * Added command line launching of URLs and command line directory
 * specification
 *
 * 127   9/25/98 2:53p Jason
 * added progress bar
 *
 * 126   9/25/98 12:31p Samir
 * in main game, hide cursor when starting.
 *
 * 125   9/23/98 3:08p Jeff
 *
 * 124   9/22/98 6:58p Samir
 * Render_floating_triggers is _DEBUG code, so make it so.
 *
 * 123   9/22/98 3:55p Samir
 * ifdef out stuff for non-debug version.
 *
 * 122   9/22/98 10:32a Jason
 * made preferred renderer default to OpenGL
 *
 * 121   9/21/98 11:10a Jeff
 * Calls to init/close forcefeedback
 *
 * 120   9/18/98 7:38p Jeff
 * creation of low-level forcefeedback and beginning of high-level
 * forcefeedback
 *
 * 119   9/18/98 1:27p Jason
 * cleaned up renderer initting
 *
 * 118   9/16/98 6:07p Jason
 * made dedicated server use standard mouse mode
 *
 * 117   9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 116   9/14/98 6:28p Jason
 * first pass at getting dedicated server working
 *
 * 115   9/03/98 12:11p Chris
 * Adding matcen support
 *
 * 114   8/31/98 12:39p Samir
 * added code to resume controllers when restoring game mode.
 *
 * 113   8/27/98 6:23p Jeff
 * changed autoleveling in config so it is a slider...had to convert
 * global from bool->uint8_t.  Added fast headlight and mirrored surfaces to
 * config menu
 *
 * 112   8/19/98 2:19p Jeff
 * moved detail globals to a struct
 *
 * 111   8/17/98 6:40p Matt
 * Added ambient sound system
 *
 * 110   8/15/98 5:16p Matt
 * Added new Base_directory variable.  Got rid of D3_LOCAL check and
 * 'local directory' registry variable.
 *
 * 109   8/10/98 5:52p Samir
 * took out briefings search path.
 *
 * 108   7/31/98 11:51a Jason
 * added player ship choosing to multiplayer games
 *
 * 107   7/24/98 5:32p Samir
 * added initializer for D3 Music.
 *
 * 106   7/13/98 12:42p Samir
 * don't do initmessage if graphics system not initialized.
 *
 * 105   7/08/98 6:27p Samir
 * stream library integrated with highlevel sound system.
 *
 * 104   7/01/98 4:56p Samir
 * redid init code.
 *
 * 103   6/24/98 11:14a Chris
 * Added more support and bug fixes
 *
 * 102   6/23/98 6:00p Chris
 * DirectSound 16 mixer is active with 8 bit samples
 *
 * 101   6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 100   6/19/98 6:42p Jason
 * made specular mapping a config detail item
 *
 * 99    6/19/98 6:04p Jeff
 * variables to turn on/off voices
 *
 * 98    6/18/98 5:22p Jeff
 * initialize streaming audio system
 *
 * 97    6/17/98 3:58p Jeff
 * put in PilotInit().  String table loaded near begining for Main exe,
 * after tables are loaded for editor
 *
 * 96    6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 95    6/16/98 11:49a Jeff
 * string table loaded after manage system
 *
 * 94    6/16/98 10:54a Jeff
 *
 * 93    6/12/98 5:56p Jeff
 * Load string tables during init
 *
 * 92    6/08/98 3:56p Jeff
 * added initializing functions for compressed audio and voice systems
 *
 * 91    6/02/98 6:03p Jason
 * added specular lightmaps
 *
 * 90    6/02/98 4:37p Samir
 * multiple joysticks supported.
 *
 * 89    6/01/98 11:37a Chris
 *
 * 88    5/19/98 3:43p Samir
 * must move mem_Init after error_Init.
 *
 * 87    5/19/98 3:37p Samir
 * added mem_Init
 *
 * 86    5/14/98 11:49a Chris
 * Bettered the sound paging system
 *
 * 85    5/12/98 2:05p Craig
 * errror
 *
 * 84    5/12/98 11:45a Samir
 * added logfile init.
 *
 * 83    5/06/98 6:34p Jeff
 * Added Terrain casting to config
 *
 * 82    5/06/98 4:32p Samir
 * moved ui init back to it's proper place.
 *
 * 81    5/06/98 12:44p Jeff
 * added saving/restoring video resolution
 *
 * 80    5/05/98 5:16p Samir
 * took out calls to init UI system (that's done now in SetScreenMode)
 *
 * 79    5/05/98 3:02p Jason
 * attempting to add different screen resolutions
 *
 * 78    5/04/98 3:42p Matt
 * Page in all sounds at init time, so you don't have to wait when you're
 * starting a game
 *
 * 77    5/01/98 4:48p Jeff
 * Added autoleveling into the configuration
 *
 * 76    4/28/98 6:42p Matt
 * If registry says renderer is software, force it to be glide.
 *
 * 75    4/28/98 11:56a Jeff
 * moved things from config (d3.cfg) into the registry
 *
 * 74    4/24/98 1:53a Samir
 * added trigger init and free.
 *
 * 73    4/16/98 6:53a Samir
 * added default script warning system.
 *
 * 72    4/16/98 12:23a Samir
 * fixed bug when checking if script compiled in editor.
 *
 * 71    4/14/98 7:31p Matt
 * Changed code to use ddio_MakePath() instead of sprintf() to create file
 * spec
 *
 * 70    4/10/98 7:48p Samir
 * make sure to set default values for outlining, etc.
 *
 * 69    4/09/98 5:30p Samir
 * new main  menu art.
 *
 * 68    4/08/98 7:19p Samir
 * Added runtime debugging option.
 *
 * 67    4/07/98 9:20p Samir
 * Changes to debug stuff.
 *
 * 66    4/06/98 5:13p Chris
 * Sounds page in at the beginning of a level
 *
 * 65    4/02/98 7:58p Samir
 * make sure to pause game and close/init control system when application
 * looses focus.
 *
 * 64    3/27/98 5:18p Samir
 * initialize debug break handlers differently for editor.
 *
 * 63    3/27/98 3:29p Brent
 * if joy init fails, don't try initializing joystick. (samir)
 *
 * 62    3/27/98 2:44p Samir
 * Restore joystick initialization.
 *
 * 61    3/23/98 8:03p Samir
 * A bunch of changes to allow for ALT-TAB to work.
 *
 * 60    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 59    3/20/98 1:19p Jeff
 * Changes made to use Default_pilot string for pilot filename to use.
 *
 * 58    3/19/98 11:27a Samir
 * Better error checking.
 *
 * 57    3/13/98 1:22p Jason
 * Moved UseHardware flag to the renderer lib where it belongs
 *
 * 56    3/10/98 5:16p Samir
 * Got debug callbacks working when you hit an Int3.
 *
 * 55    3/05/98 6:39p Samir
 * Initialize ui system with UI_FONT
 *
 * 54    3/04/98 12:00p Jason
 * added default gamma settings
 *
 * 53    2/27/98 5:35p Jeff
 * Added in loading and saving of a game configuration file
 *
 * 52    2/18/98 1:33a Jason
 * don't do mip mapping by default
 *
 * 51    2/18/98 1:11a Samir
 * Some game window mess.
 *
 * 50    2/17/98 2:21p Samir
 * Added d3xdebug.h
 *
 * 49    2/14/98 10:48p Jason
 * got preferred rendering working
 *
 * 46    2/11/98 5:55p Samir
 * Now InitD3XDebug and CloseD3XDebug are called when you enter and leave
 * the game.  This as well as ui_Init and ui_Close
 *
 * 45    2/02/98 7:34p Samir
 * Moved D3X Initialization to PlayGame.
 *
 * 44    1/29/98 12:24p Samir
 * Added logfile support.
 *
 * 43    1/27/98 1:20p Samir
 * Fixed initialization for main game.
 *
 * 42    1/13/98 12:31p Samir
 * only register small font for editor.
 *
 * 41    1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 40    12/31/97 1:01a Chris
 * Removed old dead code
 *
 *
 *
 * $NoKeywords: $
 */

// Initialization routines for Descent3/Editor

#include <cstring>
#include <ctime>
#include <filesystem>

#include "mono.h"
#include "gametexture.h"
#include "object.h"
#include "vecmat.h"
#include "init.h"
#include "config.h"
#include "3d.h"
#include "hlsoundlib.h"
#include "manage.h"
#include "bitmap.h"
#include "ddio.h"
#include "render.h"
#include "descent.h"
#include "renderer.h"
#include "vclip.h"
#include "grdefs.h"
#include "pserror.h"
#include "lighting.h"
#include "polymodel.h"
#include "door.h"
#include "terrain.h"
#include "soundload.h"
#include "ship.h"
#include "controls.h"
#include "Mission.h"
#include "findintersection.h"
#include "appdatabase.h"
#include "room.h"
#include "game.h"
#include "gamefile.h"
#include "TelCom.h"
#include "objinfo.h"
#include "cinematics.h"
#include "lightmap_info.h"
#include "fireball.h"
#include "networking.h"
#include "args.h"
#include "pilot.h"
#include "gameloop.h"
#include "trigger.h"
#include "physics.h"
#include "special_face.h"
#include "voice.h"
#include "localization.h"
#include "stringtable.h"
#include "player.h"
#include "psrand.h"
#include "ambient.h"
#include "matcen.h"
#include "dedicated_server.h"
#include "D3ForceFeedback.h"
#include "newui.h"
#include "SmallViews.h"
#include "uisys.h"
#include "rtperformance.h"
#include "musicapi.h"
#include "PilotPicsAPI.h"
#include "osiris_dll.h"
#include "mem.h"
#include "multi.h"
#include "marker.h"
#include "gamecinematics.h"
#include "debuggraph.h"
#include "vibeinterface.h"

// Uncomment this to allow all languages
#define ALLOW_ALL_LANG 1

#ifdef EDITOR
#include "editor\HFile.h"
#include "editor\d3edit.h"
#include "slew.h"
#include "gr.h"
#define INIT_MESSAGE(c) SplashMessage c
#else
void IntroScreen();
#define INIT_MESSAGE(c) InitMessage(c)
#endif

#if defined(EDITOR) || defined(NEWEDITOR)
bool Running_editor = true; // didn't we have a variable like this somewhere
#else
bool Running_editor = false; // didn't we have a variable like this somewhere
#endif

static bool Init_in_editor = false;

// used to update load bar.
static void SetInitMessageLength(const char *c, float amount); // portion of total bar to fill (0 to 1)
extern void UpdateInitMessage(float amount);                   // amount is 0 to 1
static void SetupTempDirectory(void);
static void DeleteTempFiles(void);
static void PreGameCdCheck();
static void InitIOSystems(bool editor);
static void InitStringTable();
static void InitGraphics(bool editor);
static void InitGameSystems(bool editor);
static void InitDedicatedServer();

#define TEMPBUFFERSIZE 256

// If there's a joystick, this is the stick number.  Else, this is -1
char App_ddvid_subsystem[8];

//	other info.
static chunked_bitmap Title_bitmap;
static bool Init_systems_init = false;
static bool Graphics_init = false;
static bool Title_bitmap_init = false;
uint8_t Use_motion_blur = 0;

// The "root" directory of the D3 file tree
char Base_directory[_MAX_PATH];

extern int Min_allowed_frametime;

extern bool Render_powerup_sparkles;
extern int Use_file_xfer;

static const float kDefaultMouselookSensitivity = 9.102f;
static const float kAnglesPerDegree = 65536.0f / 360.0f;
float Mouselook_sensitivity = kAnglesPerDegree * kDefaultMouselookSensitivity;
float Mouse_sensitivity = 1.0f;

int merc_hid = -1;

/*
        Initializes all the subsystems that need to be initialized BEFORE application creation.
        Returns 1 if all is good, 0 if something is wrong
*/
void PreInitD3Systems() {
  // initialize error system
  bool debugging = false;

#ifndef RELEASE

  debugging = (FindArg("-debug") != 0);

  if (FindArg("-logfile"))
    Debug_Logfile("d3.log");

#endif

#ifdef DAJ_DEBUG
  debugging = true;
#endif

  error_Init(debugging, false, PRODUCT_NAME);

  if (FindArg("-lowmem"))
    Mem_low_memory_mode = true;
  if (FindArg("-superlowmem"))
    Mem_low_memory_mode = Mem_superlow_memory_mode = true;
  if (FindArg("-dedicated"))
    Mem_low_memory_mode = true;
  mem_Init();
  if (FindArg("-himem")) {
    Mem_low_memory_mode = false;
    Mem_superlow_memory_mode = false;
  }
  // For the client and the server, this turns off the bitmap exchange system.
  if (FindArg("-nomultibmp"))
    Use_file_xfer = 0;

  int iframelmtarg = FindArg("-limitframe");
  if (iframelmtarg) {
    Min_allowed_frametime = atoi(GameArgs[iframelmtarg + 1]);
    mprintf(0, "Using %d as a minimum frametime\n", Min_allowed_frametime);
  } else {
    if (FindArg("-dedicated"))
      Min_allowed_frametime = 30;
    else
      Min_allowed_frametime = 0;
  }
  iframelmtarg = FindArg("-framecap");
  if (iframelmtarg) {
    Min_allowed_frametime = ((float)1.0 / (float)atoi(GameArgs[iframelmtarg + 1])) * 1000;
    mprintf(0, "Using %d as a minimum frametime\n", Min_allowed_frametime);
  } else {
    // Default to a framecap of 60
    Min_allowed_frametime = (1.0 / 60.0) * 1000;
    mprintf(0, "Using default framecap of 60\n");
  }

  // Mouselook sensitivity!
  int msensearg = FindArg("-mlooksens");
  if (msensearg) {
    Mouselook_sensitivity = kAnglesPerDegree * atof(GameArgs[msensearg + 1]);
    mprintf(0, "Using mouselook sensitivity of %f\n", Mouselook_sensitivity);
  }

  // Mouse sensitivity (non-mouselook)
  msensearg = FindArg("-mousesens");
  if (msensearg) {
    Mouse_sensitivity = atof(GameArgs[msensearg + 1]);
    mprintf(0, "Using mouse sensitivity of %f\n", Mouse_sensitivity);
  }

  grtext_Init();

#ifndef RELEASE
  SetMessageBoxTitle(PRODUCT_NAME " Message");
#endif
}

/*
        Save game variables to the registry
*/
void SaveGameSettings() {
  char tempbuffer[TEMPBUFFERSIZE];
  int tempint;

  snprintf(tempbuffer, sizeof(tempbuffer), "%f", Render_preferred_state.gamma);
  Database()->write("RS_gamma", tempbuffer, strlen(tempbuffer) + 1);

  snprintf(tempbuffer, sizeof(tempbuffer), "%f", Sound_system.GetMasterVolume());
  Database()->write("SND_mastervol", tempbuffer, strlen(tempbuffer) + 1);

  snprintf(tempbuffer, sizeof(tempbuffer), "%f", D3MusicGetVolume());
  Database()->write("MUS_mastervol", tempbuffer, strlen(tempbuffer) + 1);

  snprintf(tempbuffer, sizeof(tempbuffer), "%f", Detail_settings.Pixel_error);
  Database()->write("RS_pixelerror", tempbuffer, strlen(tempbuffer) + 1);

  snprintf(tempbuffer, sizeof(tempbuffer), "%f", Detail_settings.Terrain_render_distance / ((float)TERRAIN_SIZE));
  Database()->write("RS_terraindist", tempbuffer, strlen(tempbuffer) + 1);

  Database()->write("Dynamic_Lighting", Detail_settings.Dynamic_lighting);

#ifdef _DEBUG
  Database()->write("Outline_mode", Outline_mode);
  Database()->write("Lighting_on", Lighting_on);
  Database()->write("Render_floating_triggers", Render_floating_triggers);
#endif

  Database()->write("TerrLeveling", Default_player_terrain_leveling);
  Database()->write("RoomLeveling", Default_player_room_leveling);
  // Database()->write("Terrain_casting",Detail_settings.Terrain_casting);
  Database()->write("Specmapping", Detail_settings.Specular_lighting);
  Database()->write("FastHeadlight", Detail_settings.Fast_headlight_on);
  Database()->write("MirrorSurfaces", Detail_settings.Mirrored_surfaces);
  Database()->write("MissileView", Missile_camera_window);
  Database()->write("RS_vsync", Render_preferred_state.vsync_on);
  Database()->write("DetailScorchMarks", Detail_settings.Scorches_enabled);
  Database()->write("DetailWeaponCoronas", Detail_settings.Weapon_coronas_enabled);
  Database()->write("DetailFog", Detail_settings.Fog_enabled);
  Database()->write("DetailCoronas", Detail_settings.Coronas_enabled);
  Database()->write("DetailProcedurals", Detail_settings.Procedurals_enabled);
  Database()->write("DetailObjectComp", Detail_settings.Object_complexity);
  Database()->write("DetailPowerupHalos", Detail_settings.Powerup_halos);

  Database()->write("RS_resolution", Game_video_resolution);

  Database()->write("RS_bitdepth", Render_preferred_bitdepth);
  Database()->write("RS_bilear", Render_preferred_state.filtering);
  Database()->write("RS_mipping", Render_preferred_state.mipping);
  Database()->write("RS_color_model", Render_state.cur_color_model);
  Database()->write("RS_light", Render_state.cur_light_state);
  Database()->write("RS_texture_quality", Render_state.cur_texture_quality);

  Database()->write("VoicePowerup", PlayPowerupVoice);
  Database()->write("VoiceAll", PlayVoices);

  // Write out force feedback
  Database()->write("EnableJoystickFF", D3Use_force_feedback);
  Database()->write("ForceFeedbackAutoCenter", D3Force_auto_center);
  uint8_t force_gain;
  if (D3Force_gain < 0.0f)
    D3Force_gain = 0.0f;
  if (D3Force_gain > 1.0f)
    D3Force_gain = 1.0f;
  force_gain = (uint8_t)((100.0f * D3Force_gain) + 0.5f);
  Database()->write("ForceFeedbackGain", force_gain);

#ifndef RELEASE // never save this value out in release.
  Database()->write("SoundMixer", Sound_mixer);
  Database()->write("PreferredRenderer", PreferredRenderer);
#endif

  tempint = Sound_quality;
  Database()->write("SoundQuality", tempint);

  Database()->write("SoundQuantity", Sound_system.GetLLSoundQuantity());

  if (Default_pilot[0] != '\0')
    Database()->write("Default_pilot", Default_pilot, strlen(Default_pilot) + 1);
  else
    Database()->write("Default_pilot", " ", 2);
}

/*
        Read game variables from the registry
*/
void LoadGameSettings() {
  char tempbuffer[TEMPBUFFERSIZE], *stoptemp;
  int templen = TEMPBUFFERSIZE;
  int tempint;

  // set defaults
#ifdef _DEBUG
  Outline_mode = OM_ALL;
  Lighting_on = true;
#endif

  Detail_settings.Specular_lighting = false;
  Detail_settings.Dynamic_lighting = true;
  Detail_settings.Fast_headlight_on = true;
  Detail_settings.Mirrored_surfaces = true;
  Detail_settings.Scorches_enabled = true;
  Detail_settings.Weapon_coronas_enabled = true;
  Render_preferred_state.mipping = true;
  Render_preferred_state.filtering = true;
  Render_preferred_state.bit_depth = 16;
  Render_preferred_bitdepth = 16;
  Default_player_terrain_leveling = 2;
  Default_player_room_leveling = 2;
  Render_preferred_state.gamma = 1.5;
  PreferredRenderer = RENDERER_OPENGL;

  Sound_system.SetLLSoundQuantity(MIN_SOUNDS_MIXED + (MAX_SOUNDS_MIXED - MIN_SOUNDS_MIXED) / 2);
  D3MusicSetVolume(0.5f);
  Detail_settings.Pixel_error = 8.0;
  Sound_system.SetMasterVolume(1.0);
  Detail_settings.Terrain_render_distance = 70.0 * TERRAIN_SIZE;
  D3Use_force_feedback = true;
  D3Force_gain = 1.0f;
  D3Force_auto_center = true;
  Game_video_resolution = RES_640X480;
  PlayPowerupVoice = true;
  PlayVoices = true;
  Sound_mixer = SOUND_MIXER_SOFTWARE_16;
  Sound_quality = SQT_NORMAL;
  Missile_camera_window = SVW_LEFT;
  Render_preferred_state.vsync_on = true;
  Detail_settings.Fog_enabled = true;
  Detail_settings.Coronas_enabled = true;
  Detail_settings.Procedurals_enabled = true;
  Detail_settings.Object_complexity = 1;
  Detail_settings.Powerup_halos = true;

  ddio_SetKeyboardLanguage(KBLANG_AMERICAN);

  if (Database()->read("KeyboardType", tempbuffer, &templen)) {
    if (stricmp(tempbuffer, "French") == 0) {
      ddio_SetKeyboardLanguage(KBLANG_FRENCH);
    } else if (stricmp(tempbuffer, "German") == 0) {
      ddio_SetKeyboardLanguage(KBLANG_GERMAN);
    }
  }

  templen = TEMPBUFFERSIZE;
  if (Database()->read("RS_gamma", tempbuffer, &templen)) {
    Render_preferred_state.gamma = strtod(tempbuffer, &stoptemp);
  }
  templen = TEMPBUFFERSIZE;
  if (Database()->read("SND_mastervol", tempbuffer, &templen)) {
    Sound_system.SetMasterVolume(strtod(tempbuffer, &stoptemp));
  }
  templen = TEMPBUFFERSIZE;
  if (Database()->read("MUS_mastervol", tempbuffer, &templen)) {
    D3MusicSetVolume(strtod(tempbuffer, &stoptemp));
  }
  templen = TEMPBUFFERSIZE;
  if (Database()->read("RS_pixelerror", tempbuffer, &templen)) {
    Detail_settings.Pixel_error = strtod(tempbuffer, &stoptemp);
  }
  templen = TEMPBUFFERSIZE;
  if (Database()->read("RS_terraindist", tempbuffer, &templen)) {
    Detail_settings.Terrain_render_distance = strtod(tempbuffer, &stoptemp) * TERRAIN_SIZE;
  }
  templen = TEMPBUFFERSIZE;
  Database()->read_int("Dynamic_Lighting", &Detail_settings.Dynamic_lighting);

#ifdef _DEBUG
  Database()->read_int("Outline_mode", &Outline_mode);
  Database()->read("Lighting_on", &Lighting_on);
  Database()->read("Render_floating_triggers", &Render_floating_triggers);
#endif

  Database()->read_int("TerrLeveling", &Default_player_terrain_leveling);
  Database()->read_int("RoomLeveling", &Default_player_room_leveling);
  Database()->read("Specmapping", &Detail_settings.Specular_lighting);
  Database()->read("RS_bitdepth", &Render_preferred_bitdepth, sizeof(Render_preferred_bitdepth));
  Database()->read_int("RS_resolution", &Game_video_resolution);
  Database()->read_int("RS_bilear", &Render_preferred_state.filtering);
  Database()->read_int("RS_mipping", &Render_preferred_state.mipping);
  Database()->read_int("RS_color_model", &Render_state.cur_color_model);
  Database()->read_int("RS_light", &Render_state.cur_light_state);
  Database()->read_int("RS_texture_quality", &Render_state.cur_texture_quality);
  // force feedback stuff
  Database()->read("EnableJoystickFF", &D3Use_force_feedback);
  Database()->read("ForceFeedbackAutoCenter", &D3Force_auto_center);
  uint8_t force_gain;
  Database()->read("ForceFeedbackGain", &force_gain, sizeof(force_gain));
  if (force_gain > 100)
    force_gain = 100;
  D3Force_gain = ((float)force_gain) / 100.0f;
  Database()->read_int("PreferredRenderer", &PreferredRenderer);
  Database()->read_int("MissileView", &Missile_camera_window);
  Database()->read("FastHeadlight", &Detail_settings.Fast_headlight_on);
  Database()->read("MirrorSurfaces", &Detail_settings.Mirrored_surfaces);
  Database()->read_int("RS_vsync", &Render_preferred_state.vsync_on);

  if (FindArg("-vsync"))
    Render_preferred_state.vsync_on = true;

  //@@	// Base missile camera if in wrong window
  //@@	if (Missile_camera_window==SVW_CENTER)
  //@@		Missile_camera_window=SVW_LEFT;

  Database()->read("VoicePowerup", &PlayPowerupVoice);
  Database()->read("VoiceAll", &PlayVoices);

  Database()->read("DetailScorchMarks", &Detail_settings.Scorches_enabled);
  Database()->read("DetailWeaponCoronas", &Detail_settings.Weapon_coronas_enabled);
  Database()->read("DetailFog", &Detail_settings.Fog_enabled);
  Database()->read("DetailCoronas", &Detail_settings.Coronas_enabled);
  Database()->read("DetailProcedurals", &Detail_settings.Procedurals_enabled);
  Database()->read_int("DetailObjectComp", &tempint);
  Detail_settings.Object_complexity = tempint;
  if (Detail_settings.Object_complexity < 0 || Detail_settings.Object_complexity > 2)
    Detail_settings.Object_complexity = 1;

  Database()->read("DetailPowerupHalos", &Detail_settings.Powerup_halos);

  if (Database()->read_int("SoundMixer", &tempint))
    Sound_mixer = tempint;

  if (Database()->read_int("SoundQuality", &tempint))
    Sound_quality = tempint;

  if (Database()->read_int("SoundQuantity", &tempint)) {
    Sound_system.SetLLSoundQuantity(tempint);
  }

  Sound_card_name[0] = 0;
  templen = TEMPBUFFERSIZE;
  if (Database()->read("SoundcardName", tempbuffer, &templen)) {
    strcpy(Sound_card_name, tempbuffer);
  }

  int len = _MAX_PATH;
  Database()->read("Default_pilot", Default_pilot, &len);

  // Now that we have read in all the data, set the detail level if it is a predef setting (custom is ignored in
  // function)

  int level;
  level = DETAIL_LEVEL_MED;

  Database()->read_int("PredefDetailSetting", &level);
  ConfigSetDetailLevel(level);
  int widtharg = FindArg("-Width");
  int heightarg = FindArg("-Height");
  if (widtharg) {
    Video_res_list[N_SUPPORTED_VIDRES - 1].width = atoi(GameArgs[widtharg + 1]);
    Game_video_resolution = N_SUPPORTED_VIDRES - 1;
  }
  if (heightarg) {
    Video_res_list[N_SUPPORTED_VIDRES - 1].height = atoi(GameArgs[heightarg + 1]);
    Game_video_resolution = N_SUPPORTED_VIDRES - 1;
  }

  // Motion blur
  Use_motion_blur = 0;
  if (Katmai || FindArg("-motionblur")) {
    if (!FindArg("-nomotionblur")) {
      Use_motion_blur = 1;
    }
  }

  Render_powerup_sparkles = false;
  if (Katmai && !FindArg("-nosparkles")) {
    Render_powerup_sparkles = true;
  }

}

struct tTempFileInfo {
  const char *wildcard;
};
static const tTempFileInfo temp_file_wildcards[] = {{"d3s*.tmp"}, {"d3m*.tmp"}, {"d3o*.tmp"},
                                                    {"d3c*.tmp"}, {"d3t*.tmp"}, {"d3i*.tmp"}};
static const int num_temp_file_wildcards = sizeof(temp_file_wildcards) / sizeof(tTempFileInfo);

/*
        I/O systems initialization
*/
void InitIOSystems(bool editor) {
  ddio_init_info io_info;

  // Set the base directory
  int dirarg = FindArg("-setdir");
  int exedirarg = FindArg("-useexedir");
  if (dirarg) {
    strncpy(Base_directory, GameArgs[dirarg + 1], sizeof(Base_directory) - 1);
    Base_directory[sizeof(Base_directory) - 1] = '\0';
  } else if (exedirarg) {
    char exec_path[_MAX_PATH];
    memset(exec_path, 0, sizeof(exec_path));
    // Populate exec_path with the executable path
    if (!ddio_GetBinaryPath(exec_path, sizeof(exec_path))) {
    Error("Failed to get executable path\n");
    } else {
       std::filesystem::path executablePath(exec_path);
       std::string baseDirectoryString = executablePath.parent_path().string();
       strncpy(Base_directory, baseDirectoryString.c_str(), sizeof(Base_directory) - 1);
       Base_directory[sizeof(Base_directory) - 1] = '\0';
       mprintf(0, "Using working directory of %s\n", Base_directory);
      }
    } else {
       ddio_GetWorkingDir(Base_directory, sizeof(Base_directory));
      }

  ddio_SetWorkingDir(Base_directory);

  App()->set_defer_handler(D3DeferHandler);

#ifndef RELEASE
  if (!editor && !FindArg("-windowed")) {
    if (Dedicated_server) {
      ddio_MouseMode(MOUSE_STANDARD_MODE);
    } else {
      ddio_MouseMode(MOUSE_EXCLUSIVE_MODE);
    }
  }
#else
  ddio_MouseMode(MOUSE_EXCLUSIVE_MODE);
#endif

  //	do io init stuff
  //io_info.obj = App();
  io_info.joy_emulation = (bool)((FindArg("-alternatejoy") == 0) && (FindArg("-directinput") == 0));
  io_info.key_emulation = true; //(bool)(FindArg("-slowkey")!=0); WIN95: DirectInput is flaky for some keys.
  INIT_MESSAGE(("Initializing DDIO systems."));
  if (!ddio_Init(&io_info)) {
    Error("I/O initialization failed.");
  }

  rtp_Init();
  RTP_ENABLEFLAGS(RTI_FRAMETIME | RTI_RENDERFRAMETIME | RTI_MULTIFRAMETIME | RTI_MUSICFRAMETIME |
                  RTI_AMBSOUNDFRAMETIME);
  RTP_ENABLEFLAGS(RTI_WEATHERFRAMETIME | RTI_PLAYERFRAMETIME | RTI_DOORFRAMETIME | RTI_LEVELGOALTIME |
                  RTI_MATCENFRAMETIME);
  RTP_ENABLEFLAGS(RTI_OBJFRAMETIME | RTI_AIFRAMETIME | RTI_PROCESSKEYTIME);

  //	Read in stuff from the registry
  INIT_MESSAGE(("Reading settings."));
  LoadGameSettings();

  // Setup temp directory
  INIT_MESSAGE(("Setting up temp directory."));
  SetupTempDirectory();
  mprintf(0, "Removing any temp files left over from last execution\n");
  DeleteTempFiles();

  //	create directory system.
  if (!mng_InitTableFiles()) {
#ifdef EDITOR
    Error("Couldn't successfully initialize the table files.  I'm shutting down!");
#else
    Error(TXT_INITTABLEERR);
#endif
  }

  // Init hogfiles
  INIT_MESSAGE(("Checking for HOG files."));
  int d3_hid = -1, extra_hid = -1, sys_hid = -1, extra13_hid = -1;
  char fullname[_MAX_PATH];

#ifdef DEMO
  // DAJ	d3_hid = cf_OpenLibrary("d3demo.hog");
  ddio_MakePath(fullname, LocalD3Dir, "d3demo.hog", NULL);
#else
  ddio_MakePath(fullname, LocalD3Dir, "d3.hog", NULL);
#endif
  d3_hid = cf_OpenLibrary(fullname);

  // JC: Steam release uses extra1.hog instead of extra.hog, so try loading it first
  // Open this file if it's present for stuff we might add later
  ddio_MakePath(fullname, LocalD3Dir, "extra1.hog", NULL);
  extra_hid = cf_OpenLibrary(fullname);
  if (extra_hid == 0) {
    ddio_MakePath(fullname, LocalD3Dir, "extra.hog", NULL);
    extra_hid = cf_OpenLibrary(fullname);
  }

  // JC: Steam release uses extra.hog instead of merc.hog, so try loading it last (so we don't conflict with the above)
  // Open mercenary hog if it exists
  ddio_MakePath(fullname, LocalD3Dir, "merc.hog", NULL);
  merc_hid = cf_OpenLibrary(fullname);
  if (merc_hid == 0) {
    ddio_MakePath(fullname, LocalD3Dir, "extra.hog", NULL);
    merc_hid = cf_OpenLibrary(fullname);
  }

  // Open this for extra 1.3 code (Black Pyro, etc)
  ddio_MakePath(fullname, LocalD3Dir, "extra13.hog", NULL);
  extra13_hid = cf_OpenLibrary(fullname);

  // last library opened is the first to be searched for dynamic libs, so put
  // this one at the end to find our newly build script libraries first
  ddio_MakePath(fullname, LocalD3Dir, PRIMARY_HOG, NULL);
  sys_hid = cf_OpenLibrary(fullname);

  // Check to see if there is a -mission command line option
  // if there is, attempt to open that hog/mn3 so it can override such
  // things as the mainmenu movie, or loading screen
  int mission_arg = FindArg("-mission");
  if (mission_arg > 0) {
    char path_to_mission[_MAX_PATH];
    char filename[256];

    // get the true filename
    ddio_SplitPath(GameArgs[mission_arg + 1], NULL, filename, NULL);
    strcat(filename, ".mn3");

    // make the full path (it is forced to be on the harddrive since it contains
    // textures and stuff).
    ddio_MakePath(path_to_mission, LocalD3Dir, "missions", filename, NULL);
    if (cfexist(path_to_mission)) {
      cf_OpenLibrary(path_to_mission);
    } else {
      Int3(); // mission not found
    }
  }

  // Initialize debug graph early incase any system uses it in it's init
  INIT_MESSAGE(("Initializing debug graph."));
  DebugGraph_Initialize();

  //	initialize all the OSIRIS systems
  //	extract from extra.hog first, so it's dll files are listed ahead of d3.hog's
  INIT_MESSAGE(("Initializing OSIRIS."));
  Osiris_InitModuleLoader();
  if (extra13_hid != -1)
    Osiris_ExtractScriptsFromHog(extra13_hid, false);
  if (extra_hid != -1)
    Osiris_ExtractScriptsFromHog(extra_hid, false);
  if (merc_hid != -1)
    Osiris_ExtractScriptsFromHog(merc_hid, false);
  if (sys_hid != -1)
    Osiris_ExtractScriptsFromHog(sys_hid, false);
  Osiris_ExtractScriptsFromHog(d3_hid, false);
}

// Returns true if Mercenary is installed (inits the Black Pyro and Red GB)
bool MercInstalled() { return merc_hid > 0; }

extern int Num_languages;
void InitStringTable() {

  int language = LANGUAGE_ENGLISH;
  Database()->read("LanguageType", &language, sizeof(language));

  if (language < 0 || language >= Num_languages) {
    Int3();
    language = LANGUAGE_ENGLISH;
  }
  Localization_SetLanguage(language);

  int string_count = LoadStringTables();

  if (string_count == 0)
    Error("Couldn't find the string table.");
  else
    mprintf(0, "%d strings loaded from the string tables\n", string_count);
}

void InitGraphics(bool editor) {
  // Init our bitmaps, must be called before InitTextures
  bm_InitBitmaps();

  // Init our textures
  if (!InitTextures())
    Error("Failed to initialize texture system.");

#ifdef EDITOR
  char *driver = "GDIX";

  if (!ddgr_Init(Descent, driver, editor ? false : true))
    Error("DDGR graphic system init failed.");

  // Init our renderer
  grSurface::init_system();
  rend_Init(RENDERER_OPENGL, Descent, NULL);
  Desktop_surf = new grSurface(0, 0, 0, SURFTYPE_VIDEOSCREEN, 0);
#else
  strcpy(App_ddvid_subsystem, "GDIX");

  if (!Dedicated_server) {
    if (!ddvid_Init(App_ddvid_subsystem))
      Error("Graphics initialization failed.\n");
  }

  INIT_MESSAGE("Loading fonts.");
  LoadAllFonts();
#endif
  Graphics_init = true;
}

void InitGameSystems(bool editor) {
  //	initialize possible remote controller.
  int adr = FindArg("-rjoy");
  if (adr)
    Controller_ip = &GameArgs[adr + 1][1];

  //	do other joint editor/game initialization.
  SetInitMessageLength(TXT_INITCOLLATING, 0.4f);
  TelComInit();
  InitFrameTime();

  // Check for aspect ratio override
  int t = FindArg("-aspect");
  if (t) {
    extern void g3_SetAspectRatio(float);
    float aspect = atof(GameArgs[t + 1]);
    if (aspect > 0.0)
      g3_SetAspectRatio(aspect);
  }

  // Initialize force feedback effects (if we can)
  ForceInit();

  if (!editor) {
    tUIInitInfo uiinit;
    uiinit.window_font = SMALL_FONT;
    uiinit.w = 640;
    uiinit.h = 480;
    ui_Init(&uiinit);
    ui_UseCursor("StdCursor.ogf");

    NewUIInit();
    InitControls();

    atexit(CloseControls);
    atexit(ui_Close);
  }
}

//////////////////////////////////////////////////////////////////////////////
static float Init_messagebar_portion = 0.0f, Init_messagebar_offset = 0.0f;
static const char *Init_messagebar_text = NULL;

// portion of total bar to fill (0 to 1)
void SetInitMessageLength(const char *c, float amount) {
  Init_messagebar_text = c;
  Init_messagebar_offset += Init_messagebar_portion;
  Init_messagebar_portion = amount;
}

// amount is 0 to 1
void UpdateInitMessage(float amount) {
  if (Init_in_editor)
    return;
  InitMessage(Init_messagebar_text, (amount * Init_messagebar_portion) + Init_messagebar_offset);
/*
  mprintf(0, "amt=%.2f, portion=%.2f offs=%.2f, prog=%.2f\n",
          amount,
          Init_messagebar_portion,
          Init_messagebar_offset,
          (amount*Init_messagebar_portion)+Init_messagebar_offset);
*/
}

void InitMessage(const char *c, float progress) {
  int x = Game_window_w / 2 - Title_bitmap.pw / 2;
  int y = Game_window_h / 2 - Title_bitmap.ph / 2;
  int i, rx, ry, rw, rh;

  if (Dedicated_server) {
    PrintDedicatedMessage("%s\n", c);
    return;
  }

  if (!Graphics_init)
    return;

  StartFrame();

  if (Title_bitmap_init) {
    rend_ClearScreen(GR_BLACK);
    rend_DrawChunkedBitmap(&Title_bitmap, x, y, 255);
  }

  if (c) {
    g3Point *pntlist[4], points[4];
    // Set our four corners to cover the screen
    grtext_SetFont(MONITOR9_NEWUI_FONT);
    rw = Game_window_w;
    rh = grfont_GetHeight(MONITOR9_NEWUI_FONT) + 8;
    rx = 0;
    ry = Game_window_h - rh;
    points[0].p3_sx = rx;
    points[0].p3_sy = ry;
    points[1].p3_sx = rx + rw;
    points[1].p3_sy = ry;
    points[2].p3_sx = rx + rw;
    points[2].p3_sy = ry + rh;
    points[3].p3_sx = rx;
    points[3].p3_sy = ry + rh;

    for (i = 0; i < 4; i++) {
      points[i].p3_z = 0;
      points[i].p3_flags = PF_PROJECTED;
      pntlist[i] = &points[i];
    }

    rend_SetZBufferState(0);
    rend_SetTextureType(TT_FLAT);
    rend_SetAlphaType(AT_CONSTANT);
    rend_SetLighting(LS_NONE);
    rend_SetFlatColor(GR_BLACK);
    rend_SetAlphaValue(230);
    rend_DrawPolygon2D(0, pntlist, 4);

    if (progress >= 0) {
      points[0].p3_sx = rx;
      points[0].p3_sy = ry + rh - (rh / 2) + 2;
      points[1].p3_sx = rx + ((float)rw * progress);
      points[1].p3_sy = ry + rh - (rh / 2) + 2;
      points[2].p3_sx = rx + ((float)rw * progress);
      points[2].p3_sy = ry + rh;
      points[3].p3_sx = rx;
      points[3].p3_sy = ry + rh;

      rend_SetFlatColor(GR_RGB(255, 0, 0));
      rend_SetAlphaValue(230);
      rend_DrawPolygon2D(0, pntlist, 4);
    }

    grtext_SetAlpha(255);
    grtext_SetColor(NEWUI_MONITORFONT_COLOR);
    //		grtext_CenteredPrintf(0, ry, c);
    grtext_Puts(0, ry, c);
    grtext_Flush();
  }

  EndFrame();
  rend_Flip();
}

//////////////////////////////////////////////////////////////////////////////
#if (defined(OEM) || defined(DEMO) || defined(RELEASE))
void ShowStaticScreen(char *bitmap_filename, bool timed = false, float delay_time = 0.0f);
#endif

void IntroScreen() {
// #if (defined(OEM) || defined(DEMO) )
#ifdef DEMO
  ShowStaticScreen("tantrum.ogf", true, 3.0);
  ShowStaticScreen("outrage.ogf", true, 3.0);
#else
#endif

#ifdef DEMO
  int bm_handle = bm_AllocLoadFileBitmap("demomenu.ogf", 0);
#else
  int bm_handle = bm_AllocLoadFileBitmap("oemmenu.ogf", 0);
#endif
  mprintf(0, "Intro screen!.\n");

  if (bm_handle > -1) {
    if (!bm_CreateChunkedBitmap(bm_handle, &Title_bitmap))
      Error("Failed to slice up d3.ogf!");

    bm_FreeBitmap(bm_handle);

    Title_bitmap_init = true;
    InitMessage(NULL);
  } else {
    mprintf(1, "Unable to find d3.tga.\n");
  }
}

void InitDedicatedServer() {
  Game_mode |= GM_MULTI;
  Netgame.local_role = LR_SERVER;

  int ok = LoadServerConfigFile();

  if (!ok) {
    PrintDedicatedMessage(TXT_SHUTTINGDOWN);
    Error("Cannot load Dedicated Server config file.");
    exit(0);
  }
}

/*
        The D3 Initialization Mess

        This initialization sequence will occur after the application and debug systems
        are set up.

        From here, we initialize all systems.

        Initializes all the subsystems that D3/Editor needs to run.
        Returns 1 if all is good, 0 if something is wrong
*/
int ServerTimeout = 0;
float LastPacketReceived;

uint16_t Gameport = D3_DEFAULT_PORT;
uint16_t PXOPort = 0;
// Initialiaze everything before data load
void InitD3Systems1(bool editor) {
#if defined(RELEASE)
  SetDebugBreakHandlers(NULL, NULL);
#else
  SetDebugBreakHandlers(D3DebugStopHandler, D3DebugResumeHandler);
#endif

  Init_in_editor = editor;

  // Gamespy command to specify the port to listen on
  int gameportarg = FindArg("+host");
  if (!gameportarg) {
    gameportarg = FindArg("-useport");
  }
  if (gameportarg) {
    Gameport = atoi(GameArgs[gameportarg + 1]);
  }

  int pxoportarg = FindArg("-pxoport");
  if (pxoportarg)
    PXOPort = atoi(GameArgs[pxoportarg + 1]);

  // perform user i/o system initialization
  INIT_MESSAGE(("Initializing I/O system."));
  InitIOSystems(editor);

  //	load the string table
  InitStringTable();

  INIT_MESSAGE(("Initializing GFX"));
  InitGraphics(editor);

  //	initialize data structures
  InitObjectInfo();
  InitVClips();
  InitRooms();

  //	initialize lighting systems
  InitLightmapInfo();
  InitSpecialFaces();
  InitDynamicLighting();

  // Initialize missions
  InitMission();

  // Initializes the ship structure
  InitShips();

  // Initializes the fvi structures for quicker operation
  InitFVI();

  // Initializes the matcens
  InitMatcens();

  // This function needs be called before ANY 3d stuff can get done. I mean it.
  InitMathTables();

  // Initialize a random seed.
  ps_srand(time(nullptr));

  // This function has to be done before any sound stuff is called
  InitSounds();

  // Allocate memory and stuff for our terrain engine, objects, etc.
  InitTerrain();
  InitModels();
  InitDoors();
  InitGamefiles();

  //	network initialization
  if (!FindArg("-nonetwork")) {
    nw_InitNetworking();
    nw_InitSockets(Gameport);
  }

  int timeoutarg = FindArg("-timeout");
  if (timeoutarg) {
    ServerTimeout = atoi(GameArgs[timeoutarg + 1]);
    LastPacketReceived = timer_GetTime();
  }

  // Sound initialization
  int soundres = Sound_system.InitSoundLib(Sound_mixer, Sound_quality, false);

  //	Initialize Cinematics system
  InitCinematics();

  // Initialize IntelliVIBE (if available)
  VIBE_Init();
}

// Initialize rest of stuff
void InitD3Systems2(bool editor) {
  // Initialize In-Game Cinematics system
  Cinematic_Init();

//	initialize slewing
#ifdef EDITOR
  SlewControlInit();
#endif

  int tables_loaded = 0;

  //	load in all data headers.
  INIT_MESSAGE((TXT_INITDATA));
  tables_loaded = mng_LoadTableFiles(!editor);

  if (!tables_loaded)
    Error("Cannot load table file.");

  INIT_MESSAGE((TXT_INITCOLLATING));

  // Initialize the pilot system
  PilotInit();

  // Setup our object system.  By object I mean stuff in our world, not those silly C++ things.
  // This call must come after InitTableFiles(), so we have a player ship for the user
  InitObjects();

  // Fireball initting must come after LoadTableFiles
  SetInitMessageLength(TXT_INITCOLLATING, 0.1f);
  InitFireballs();
  UpdateInitMessage(1.0f);

  // initializes triggers
  InitTriggers();

  // the remaining sound system
  InitVoices();
  InitD3Music(FindArg("-nomusic") ? false : true);
  InitAmbientSoundSystem();

  InitGameSystems(editor);

  InitPlayers();

  SetInitMessageLength(TXT_INITCOLLATING, 0.5f);
  InitMarkers();
  UpdateInitMessage(1.0f);

  PPic_InitDatabase();

  //	Set next logical function for game.
  if (editor)
    SetFunctionMode(EDITOR_MODE);
  else
    SetFunctionMode(MENU_MODE);

  if (Dedicated_server)
    InitDedicatedServer();

  Init_systems_init = true;

  // free title screen bitmap.
  if (Title_bitmap_init) {
    bm_DestroyChunkedBitmap(&Title_bitmap);
    Title_bitmap_init = false;
  }

  // initialize localized text for controller system.
  extern void Localize_ctl_bindings();
  Localize_ctl_bindings();
}

void SetupTempDirectory(void) {
  // NOTE: No string tables are available at this point
  //--------------------------------------------------

  mprintf(0, "Setting up temp directory\n");

  int t_arg = FindArg("-tempdir");
  if (t_arg) {
    strcpy(Descent3_temp_directory, GameArgs[t_arg + 1]);
  } else {
    // initialize it to custom/cache
    ddio_MakePath(Descent3_temp_directory, Base_directory, "custom", "cache", NULL);
  }

  // verify that temp directory exists
  if (!ddio_SetWorkingDir(Descent3_temp_directory)) {
    Error("Unable to set temporary directory to: \"%s\"", Descent3_temp_directory);
    exit(1);
  }

  char tempfilename[_MAX_PATH];

  // verify that we can write to the temp directory
  if (!ddio_GetTempFileName(Descent3_temp_directory, "d3t", tempfilename)) {
    mprintf(0, "Unable to get temp file name\n");
    Error("Unable to set temporary directory to: \"%s\"", Descent3_temp_directory);
    exit(1);
  }

  // try to create a file in temp directory
  CFILE *file = cfopen(tempfilename, "wb");
  if (!file) {
    // unable to open file for writing
    mprintf(0, "Unable to open temp file name for writing\n");
    Error("Unable to set temporary directory to: \"%s\"", Descent3_temp_directory);
    exit(1);
  }

  cf_WriteInt(file, 0x56);
  cfclose(file);

  // now open up the file and make sure it is correct
  file = cfopen(tempfilename, "rb");
  if (!file) {
    // unable to open file for reading
    mprintf(0, "Unable to open temp file name for reading\n");
    ddio_DeleteFile(tempfilename);
    Error("Unable to set temporary directory to: \"%s\"", Descent3_temp_directory);
    exit(1);
  }

  if (cf_ReadInt(file) != 0x56) {
    // verify failed
    mprintf(0, "Temp file verify failed\n");
    cfclose(file);
    ddio_DeleteFile(tempfilename);
    Error("Unable to set temporary directory to: \"%s\"", Descent3_temp_directory);
    exit(1);
  }

  cfclose(file);

  // temp directory is valid!
  ddio_DeleteFile(tempfilename);

  mprintf(0, "Temp Directory Set To: \"%s\"\n", Descent3_temp_directory);

  // Lock the directory
  if (!ddio_CreateLockFile(std::filesystem::path(Descent3_temp_directory))) {
    mprintf(0, "Lock file NOT created in temp dir %s!\n", Descent3_temp_directory);
    Error("Unable to set temporary directory to: \"%s\"\nUnable to create lock file", Descent3_temp_directory);
    exit(1);
  }
  // restore working dir
  ddio_SetWorkingDir(Base_directory);
}

void DeleteTempFiles(void) {
  char filename[_MAX_PATH];

  // delete the d3 temp files in the temp directory
  if (ddio_SetWorkingDir(Descent3_temp_directory)) {
    int i;
    for (i = 0; i < num_temp_file_wildcards; i++) {
      if (ddio_FindFileStart(temp_file_wildcards[i].wildcard, filename)) {
        do {
          ddio_DeleteFile(filename);
        } while (ddio_FindNextFile(filename));
      }
      ddio_FindFileClose();
    }
  }

  // restore directory
  ddio_SetWorkingDir(Base_directory);
}

/*
 *
 *	These functions handle shutting down and restarting all systems in D3
 *
 */

static int Init_old_screen_mode;
static void (*Init_old_ui_callback)() = NULL;
static bool Init_old_control_mode;
static bool Init_ui_cursor_visible;
static bool Init_was_game_paused = false;
static pilot Init_old_pilot;

// TODO: MTS: Unused in project
void ShutdownD3() {
  if (!Init_systems_init)
    return;

  mprintf(0, "Shutting down D3...\n");

  // Close forcefeedback effects
  ForceShutdown();

  //	shutdown game systems
  Init_old_control_mode = Control_poll_flag;

  // JEFF: only pause game if not in multi, so we can background process
  if (GetFunctionMode() == GAME_MODE) {
    if (!(Game_mode & GM_MULTI)) {
      Init_was_game_paused = Game_paused;
      if (!Init_was_game_paused) {
        PauseGame();
      } else {
        D3MusicPause();
      }
    }
  } else {
    D3MusicPause();
    Sound_system.PauseSounds();
  }

  SaveControlConfig(&Init_old_pilot);
  CloseControls();

  //	shutdown cinematics.

  //	shutdown screen.
  Init_ui_cursor_visible = ui_IsCursorVisible();
  Init_old_screen_mode = GetScreenMode();
  Init_old_ui_callback = GetUICallback();
  SetScreenMode(SM_NULL);
  ddvid_Close();

  // shutdown IO
  ddio_Close();
}

// TODO: MTS: unused in project
//	This function restarts all game systems
void RestartD3() {
  ddio_init_info io_info;

  if (!Init_systems_init)
    return;

  mprintf(0, "Restarting D3...\n");

  if (!FindArg("-windowed")) {
    if (Dedicated_server) {
      ddio_MouseMode(MOUSE_STANDARD_MODE);
    } else {
      ddio_MouseMode(MOUSE_EXCLUSIVE_MODE);
    }
  }

  // startup io
  io_info.key_emulation = true; //(bool)(FindArg("-slowkey")!=0);
  io_info.joy_emulation = (bool)((FindArg("-alternatejoy") == 0) && (FindArg("-directinput") == 0));
  if (!ddio_Init(&io_info)) {
    Error("I/O initialization failed.");
  }

  //	startup screen.
  ddvid_Init(App_ddvid_subsystem);
  ddio_KeyFlush();
  SetScreenMode(Init_old_screen_mode);
  SetUICallback(Init_old_ui_callback);
  if (Init_ui_cursor_visible)
    ui_ShowCursor();

  //	startup game systems
  InitControls();
  LoadControlConfig(&Init_old_pilot);

  // resume game sounds and time as needed
  if (GetFunctionMode() == GAME_MODE) {
    if (!(Game_mode & GM_MULTI)) {
      if (!Init_was_game_paused) {
        ResumeGame();
      } else {
        D3MusicResume();
      }
    }
  } else {
    Sound_system.ResumeSounds();
    D3MusicResume();
  }

  // resume controller if it was active before alt-tabbing out.
  if (Init_old_control_mode) {
    ResumeControls();
  }

  // Restart Force Feedback
  ForceRestart();

  //	startup cinematics.

  //	startup sound.
  //	Sound_system.ResumeSounds();
  //	Sound_system.InitSoundLib(Descent, Sound_mixer, Sound_quality, false);
}
