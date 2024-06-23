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

 * $Logfile: /DescentIII/Main/editor/MainFrm.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * The editor main frame window
 *
 * $Log: not supported by cvs2svn $
 *
 * 164   10/29/99 4:34p Matt
 * Added code (not being called) to count the number of specular faces in
 * a level.
 *
 * 163   10/27/99 10:37a Matt
 * Added some code (not being called in this version) to list all the
 * objects in a level that use lightmaps.
 *
 * 162   10/25/99 12:54p Jeff
 * test1 _really_ destroys all lightmaps
 *
 * 161   10/13/99 10:41a Chris
 * Added 'special forcefields' that have custom bounce factors
 *
 * 160   9/15/99 1:56p Matt
 * Added the option to allow rooms or groups placed on the terrain to
 * either align with the terrain or with gravity.
 *
 * 159   8/18/99 11:29a Matt
 * Added shortcuts for next vertex and add vert to face.
 *
 * 158   8/17/99 4:09p Matt
 * Added some accelerator keys, and a function to copy face light
 * multiples.
 *
 * 157   8/12/99 9:36a Matt
 * Changed MoveEntireMine() code to move in both X and Y.
 *
 * 156   7/28/99 5:48p Matt
 * Added test code to scale an entire mine.
 *
 * 155   5/22/99 4:40a Matt
 * Fixed yet another small bug in the show-all-locked-pages code.
 *
 * 154   5/21/99 1:29p Matt
 * Fixed tiny bug.
 *
 * 153   5/21/99 12:36p Matt
 * Added test code to check for destroyable textures without a destroyed
 * bitmap.
 *
 * 152   5/10/99 12:04a Matt
 * Added function for Luke to shift the entire mine.
 *
 * 151   5/08/99 1:01p Matt
 * Added a function for Luke to scale all the room light multipliers in a
 * level.
 *
 * 150   5/08/99 1:39a Matt
 * Added a function to delete all objects of a certain type, and support
 * for placing and attaching groups to the terrain.
 *
 * 149   5/05/99 2:02a Matt
 * Added a function to check for precision-error FVI cracks in the level.
 *
 * 148   5/03/99 2:56a Matt
 * Added a function for Luke to delete all the faces in a room that have
 * texture 1 on them.
 *
 * 147   5/02/99 9:23p Matt
 * Notify the level keypad when the level has changed, and then re-init
 * the combo boxes.
 *
 * 146   5/02/99 6:41a Jeff
 * created 'test/temp' function to force unload all osiris modules
 *
 * 145   5/02/99 2:01a Jeff
 * fixed crash in getchangemask
 *
 * 144   5/01/99 9:43p Matt
 * Apparently, there's no longer a page called "DUMMY PAGE" in the list of
 * locked pages, so remove the assert that checked for it.
 *
 * 143   4/29/99 11:51p Matt
 * Improved viewer move functions.
 *
 * 142   4/29/99 3:19p Jeff
 * test function 3 to grab non-physics set objects
 *
 * 141   4/23/99 4:55p Matt
 * Fixed bug in previous version.
 *
 * 140   4/23/99 2:51p Matt
 * Added function to relink objects from the terrain to the mine to fix
 * one of Dan's levels.
 *
 * 139   4/21/99 10:36p Matt
 * Fixed typo
 *
 * 138   4/21/99 10:20p Matt
 * Fixed cut room message
 *
 * 137   4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 136   4/16/99 3:54p Nate
 * Added Viewer Properties Dialog
 *
 * 135   4/12/99 12:50p Matt
 * Added function to dump goal text to a file.
 *
 * 134   4/05/99 11:17a Matt
 * Added code to list all the objects in the levels.
 *
 * 133   4/05/99 10:54a Matt
 * Added auto-waypoint system
 *
 * 131   4/03/99 7:54p Matt
 * Finished implementing spiffy keypad update system.
 *
 * 130   4/02/99 5:08p Matt
 * Added intro movie.
 *
 * 129   3/30/99 6:24p Matt
 * Added new error system, where instead of putting up an error message, a
 * function returns a failure code & returns an error message that the
 * caller can display if it wants.
 *
 * 128   3/30/99 4:09p Matt
 * Fixed very small bug
 *
 * 127   3/30/99 11:25a Matt
 * Re-enabled object reset code
 *
 * 126   3/25/99 4:11p Samir
 * added aureal test code.
 *
 * 125   3/18/99 8:41p Jeff
 * created orphan hunter dialog
 *
 * 124   3/15/99 4:04p Matt
 * Added code to show a list of named rooms.
 *
 * 123   3/10/99 7:17p Samir
 * added function that updates keypads.
 *
 * 122   3/01/99 6:26p Matt
 * Added function to fix bad objects in Dan's level
 *
 * 121   2/23/99 11:51p Jeff
 * new script dll sync dialog
 *
 * 120   2/22/99 11:39p Matt
 * Deleted debris editor menu item, since it' no longer needed.
 *
 * 119   2/21/99 4:20p Matt
 * Added SoundSource objects (and reformatted parts of the object header
 * files).
 *
 * 118   2/05/99 1:29p Matt
 * Added a function to show the viewer's forward vector.  (Also checked
 * select-object-by-number to use common code to print out the selected
 * object info.)
 *
 * 117   2/03/99 1:10p Matt
 * Changed the paletted room current faces to be stored in a seperate
 * array, instead of in the room structure.
 *
 * 116   2/03/99 1:20a Matt
 * Added a system to show all pages locked.
 *
 * 115   2/01/99 11:36p Matt
 * Added menu functions to select an object by number and move the viewer
 * to the current object.
 *
 * 114   1/24/99 6:35p Matt
 * Made view set functions behave differently in Room View
 *
 * 113   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 112   1/19/99 6:53p Matt
 * Fixed a problem when the viewer was instantaneously moved from inside
 * to ourside or vise-versa.
 *
 * 111   1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 110   1/12/99 12:35p Nate
 * Clicking on the DALLAS menu item now restores it if it was minimized
 *
 * 109   1/11/99 3:34p Jeff
 * added checks for when going editor->game to see if scripts are out of
 * date, if so give the option of breaking out.  Add some options to mass
 * script compiler, along with a toolbar shortcut.
 *
 * 108   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 107   12/23/98 4:01p Nate
 * Added code create Dallas as a modeless dialog
 *
 * 106   12/11/98 6:48p Nate
 * Added support for starting D.A.L.L.A.S. from the main menu
 *
 * 105   12/11/98 5:50p Jeff
 * implemented and added changes regarding Level&Scripting manage system
 * and compiler interface
 *
 * 104   12/01/98 11:17p Matt
 * Added menu option to disable drawing objects in the wireframe view
 *
 * 103   11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 102   10/21/98 12:50p Sean
 * Allow for cameras to be placed on external rooms
 *
 * 101   10/14/98 4:37p Matt
 * Made InitD3System() exit with error if there's a problem instead of
 * returning a status value.  Also moved some editor-specific code from
 * init.cpp to mainfrm.cpp, and cleaned up some other initialization and
 * error-handling code.
 *
 * 100   10/12/98 1:46p Samir
 * new Program_version parameters.
 *
 * 99    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 98    10/06/98 12:38p Nate
 *
 * 97    10/04/98 1:25p Matt
 *
 * 96    10/02/98 1:43p Samir
 * took out FULL_DEVELOPMENT
 *
 * 95    9/09/98 12:48p Samir
 * added script localizer.
 *
 * 94    9/03/98 5:29p Matt
 * Added code to fix cracks in levels.
 *
 * 93    9/03/98 2:20p Jeff
 * flush keyboard after briefeditor exits
 *
 * 92    9/02/98 2:55p Jeff
 * initial creation of briefing editor
 *
 * 91    8/31/98 4:37p Matt
 * Added improved room & mine error checking.
 *
 * 90    8/27/98 6:42p Chris
 * Added the goal keypad and the start of the matcen keypad
 *
 * 89    8/20/98 12:35p Matt
 * Added nice editing for ambient sound patterns
 *
 * 88    8/13/98 1:06p Nate
 * Disabled pausing of Editor when running TableTextEditor
 *
 * 87    8/10/98 12:14p Nate
 * Added Table File Edit dialog.
 *
 * 86    7/08/98 6:26p Samir
 * took out obsolete code.
 *
 * 85    7/01/98 4:58p Samir
 * changed InitD3Systems.
 *
 * 84    6/29/98 6:45p Samir
 * call WM_ACTIVATEAPP Descent Handler from mainframe.
 *
 * 83    6/25/98 7:16p Matt
 * Added code to check for errors in portal linkage
 *
 * 82    5/01/98 3:57p Matt
 * Added function to place a camera in the center of the current face.
 *
 * 81    4/21/98 2:40p Matt
 * Added option to show level stats
 *
 * 80    4/16/98 6:39p Kevin
 * made CKeypadDialog::Activate static.
 *
 * 79    4/14/98 7:50p Matt
 * Added system to keep info for each level
 *
 * 78    3/27/98 6:05p Samir
 * Added key handler for main frame.
 *
 * 77    3/23/98 8:03p Samir
 * A bunch of changes to allow for ALT-TAB to work.
 *
 * 76    3/23/98 2:17p Jeff
 * Included telcom.h
 *
 * 75    3/06/98 5:36p Matt
 * Took out cfile try/catch for editor, since it's probably better to get
 * the error in the cfile code when debugging, so you can look at the
 * stack & parms and stuff.  I've left try/catch in for the game, but
 * ideally we'd take that out too when running under the debugger, if we
 * could figure out how to do that.
 *
 * 74    2/17/98 6:13p Jeff
 * Changed it so TelCom is forced to go into Briefings when called
 *
 * 73    2/15/98 7:44p Matt
 * Added groovy try/catch/throw error checking for cfile functions
 *
 * 72    2/09/98 10:54a Matt
 * Don't allow user to switch to mine view if there are no internal rooms
 *
 * 71    2/05/98 3:11p Matt
 * Don't move the viewer to an external room.
 *
 * 70    2/05/98 2:57p Matt
 * Changed code to use ObjSetPos()
 *
 * 69    2/04/98 6:23p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 68    1/30/98 6:07p Matt
 * Added code and menu items to deal with camera objects
 *
 * 67    1/29/98 2:15p Samir
 * Implemented ObjectListModeless and Toolbar button.
 *
 * 66    1/21/98 1:08p Matt
 * Made SetViewMode() not take new_viewer parm, since it's not needed
 * after my revamp of the editor view system.
 *
 * 65    1/21/98 12:33p Matt
 * Revamped viewer system
 *
 * 64    12/02/97 4:43p Samir
 * Repaired MainFrm.cpp
 *
 * 63    12/01/97 6:06p Samir
 * Implemented new FileDialog tracker system.
 *
 * 62    11/17/97 3:53p Matt
 * When deleting objects, set the pointers to them to NULL.
 * Added test function to play the briefing.
 *
 * 61    10/22/97 4:30p Chris
 * We can now slew between the mine and the terrain
 *
 * 60    10/16/97 7:35p Samir
 * For fullscreen game from editor, hide all user interface elements of
 * the editor window and use the client area for our display. It's REALLY
 * hacked, but seems to be the cleanest method of playing the game in
 * fullscreen.  Old method of blanking window doesn't work.
 *
 * 59    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 58    10/03/97 3:39p Matt
 * Added seperate sets of wireframe view variables for mine & room views
 *
 * 57    9/23/97 10:38a Jason
 * Took out OnTerrain
 *
 * 56    9/23/97 10:27a Jason
 * took premature return from OnFileImportRoom
 *
 * 55    9/22/97 5:59p Samir
 * Changed ObjCScript system, so everything is broken, but it shouldn't
 * crash the game.
 *
 * 53    9/17/97 12:58p Samir
 * Got rid of Curve Keypad.
 *
 * 52    9/17/97 12:48p Samir
 * Got rid of more obscure segment references.
 *
 * 51    9/17/97 11:30a Jason
 * ripped out segment engine
 *
 * 50    9/16/97 4:27p Matt
 * Got rid of static_light & changed fields in the room struct
 *
 * 49    9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 48    9/09/97 12:23p Samir
 * Added a menu item to go to level properties dialog.
 *
 * 47    9/02/97 6:41p Matt
 * Added code for group paste
 *
 * 46    8/29/97 5:45p Matt
 * Made selection & cut/copy/past funcs work with rooms
 *
 * 45    8/29/97 2:49p Samir
 * Nuked SegmentKeypad.
 *
 * 44    8/27/97 10:55a Samir
 * Fixed bug when keypad is initally closed, and you toggle it, and the
 * control bar looked fine, just no tab control.
 *
 * 43    8/21/97 7:48p Matt
 * Added code to move player object (like old move player to curseg)
 *
 * 42    8/20/97 5:28p Samir
 * Took out Desktop_surf init and put it into init.cpp
 *
 * 41    8/15/97 6:32p Samir
 * Added ScriptWizard!
 *
 * 40    8/13/97 5:39p Samir
 * Use CompileScript to compile a script now, and we compile default
 * script at startup of editor.
 *
 * 39    8/12/97 5:47p Matt
 * Added menu items to edit debris, clutter, & buildings
 * Increased number of items in objpage dropdown box
 *
 * 38    8/12/97 3:22p Samir
 * osi_Compile and D3XReallocProgram added parameters.
 *
 * 37    8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 36    8/08/97 3:30p Matt
 * Fixed stupid bug
 *
 * 35    8/08/97 3:22p Jeff
 * Added automatic OGF conversion when extracting HSM
 *
 * 34    8/08/97 3:09p Matt
 * Added testing calls to new generic page dialog
 *
 * 33    8/08/97 2:51p Jeff
 * added code to check if default script is locked
 *
 * 32    8/06/97 10:36a Samir
 * Fixed osi_Compile calls.
 *
 * 31    8/04/97 4:12p Samir
 * Call to osi_Compile uses new prototype.
 *
 * 30    8/04/97 12:42p Matt
 * Made move viewer function work with room engine
 *
 * 29    8/01/97 2:36p Jeff
 *
 * 28    7/29/97 3:48p Jeff
 *
 * 27    7/29/97 2:19p Jason
 * added filepage editor to mainframe
 *
 * 26    7/29/97 2:11p Jeff
 * Added compile on exit for Osiris
 *
 * 25    7/29/97 12:17p Matt
 * Made room:face display on status bar show different info for room,
 * mine, and terrain views.
 *
 * 24    7/28/97 5:33p Matt
 * Added function to change the view mode
 *
 * 23    7/28/97 10:51a Jeff
 * Changed cha *DefaultExternalEditor to what it should be called, char
 * Default_external_editor[256]
 *
 * 22    7/26/97 8:48p Jeff
 * fixed up calls to script editor.  Added DefaultExternalEditor global
 * variable
 *
 * 21    7/25/97 6:16p Samir
 * Fixed the tile-cascade switching/default madness.
 *
 * 20    7/24/97 3:00p Matt
 * Save/load game & editor settings from/to the registry, and added code
 * to display current keypad.
 *
 * 19    7/22/97 7:08p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 18    7/21/97 5:55p Jeff
 *
 * 17    7/21/97 4:05p Jeff
 * fixed default path for external editor
 *
 * 16    7/21/97 3:21p Jeff
 *
 * 15    7/19/97 8:09p Jeff
 *
 * 14    7/18/97 5:36p Jason
 * save changed paletted rooms on exit
 *
 * 13    7/18/97 5:17p Jeff
 *
 * 93    6/30/97 1:30p Jason
 * added netherspace stuff
 *
 * 92    6/27/97 7:21p Matt
 * Added function to move player 0 to current segment
 *
 * 91    6/27/97 3:10p Jason
 *
 * 90    6/27/97 12:19p Samir
 * Added room keypad dialog
 *
 * 89    6/25/97 5:29p Jason
 * added/modified code to display a room
 *
 * 88    6/18/97 11:56a Jason
 * added some more terrain functions for Mark
 *
 *
 * 87    6/13/97 2:18p Matt
 * Added functions to change wireframe view target
 *
 * 86    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 85    6/10/97 5:08p Jason
 * added reorderpages menu item
 *
 * 84    6/06/97 4:33p Jason
 * added cool stuff for megacells
 *
 * 83    6/05/97 3:37p Samir
 * Added megacell keypad.
 *
 * 82    6/05/97 2:52p Jason
 * added megacell functions
 *
 * 81    6/03/97 4:55p Mark
 *
 * 81	6/03/97	4:39p	Jeff
 *	Added code for Context sensitive help
 *
 * 80    6/02/97 2:31p Samir
 * Music test code!
 *
 * 79    5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 78    5/13/97 7:27p Matt
 * Added code to set & clear fuelcen flag in segments
 *
 * 77    5/13/97 12:04p Matt
 * Added code to add a floating segment
 *
 * 76    5/05/97 3:37p Matt
 *
 * 75    4/30/97 5:52p Jason
 * added ability to switch between 8bit/16bit modes
 *
 * 74    4/17/97 4:03p Samir
 * Apply Tmap 1 and Tmap2 implemented, but no Tmap2 rendering is occurring
 * yet.
 *
 * 73    4/17/97 11:08a Samir
 * BuildBridge Implemented
 *
 * 72    4/16/97 6:11p Matt
 * Added code to divide a segment into two
 *
 * 71    4/15/97 11:29a Samir
 * Iimplemented menu item object placement and deletion.
 *
 * 70    4/11/97 4:59p Samir
 * Grab texture menu item works.
 *
 * 69    4/08/97 10:42a Jason
 * implemented path following interface
 *
 * 68    4/04/97 3:15p Samir
 * Added paths keypad, removed player keypad since it's joined with object
 * keypad.
 *
 * 67    4/03/97 1:20p Jason
 * changes to get the sound page system playing
 *
 * 66    4/02/97 10:56a Matt
 * Changed "Other" menu to "Object", and removed obsolete set-player-start
 * option
 *
 * 65    4/01/97 11:00p Matt
 * Changed editor to keep a viewer object (type camera) seperate from the
 * player object.  This camera, and not the player, is now moved by
 * slewing, the C key, etc.  When going into the game, the viewer position
 * & orientation are copied to the player.  When going back to the editor,
 * the player position is copied to the viewer, and the player object is
 * reset to its start location.
 *
 * 64    3/31/97 5:58p Matt
 * Revamped mine update flags
 *
 * 63    3/28/97 12:20p Jason
 * added terrain dialog stuff, plus bitmap memory indicator
 *
 * 62    3/26/97 6:46p Samir
 * Fixed order of tabs in dialog box.
 *
 * 61    3/26/97 5:48p Samir
 * Keep splash screen up a bit longer.
 *
 * 60    3/26/97 4:37p Samir
 * Splash screen up and running.
 *
 * 59    3/24/97 6:48p Samir
 * Allow clean delete of door segments.  AddDefaultSegment
 *
 * 58    3/21/97 12:30p Samir
 * Added more keypad functionality and NET pane.
 *
 * 57    3/20/97 5:01p Matt
 * Removed obsolete select-from-box code
 *
 * 56    3/20/97 11:55a Jason
 * changes for terrain editing/drawing
 *
 * 55    3/17/97 2:26p Matt
 * Added function to set player view from curseg/curside
 *
 * 54    3/17/97 1:32p Matt
 * Took out redundant and unneeded handlers for View menu items.
 *
 * 53    3/17/97 12:25a Matt
 * Added call to FormJoint(), and changed a bunch of code to use the
 * SEGNUM() macro.
 *
 * 52    3/14/97 6:53p Samir
 * Took out unused functions and added delete segment function.
 *
 * 51    3/14/97 12:50p Samir
 * Added marked segment pane
 *
 * 50    3/13/97 7:02p Samir
 * Added current segment:side pane.
 *
 * 49    3/13/97 12:09p Matt
 * Switch to data\levels directory, so the Open file dialog will default
 * to that directory.
 *
 * 48    3/12/97 3:25p Matt
 * Added funcs for cut, copy, paste, & delete, and to save and load
 * groups.
 *
 * 47    3/10/97 11:13a Samir
 * Changes made to reflect deletion of OSDebug class from system
 *
 * 46    3/05/97 7:21p Samir
 * Added special initialization code for editor and use osD3Winxxxx
 * classes for os objects.
 *
 * 45    3/05/97 11:49a Samir
 * Added doorway and terrain keypad tabs.
 *
 * 44    3/04/97 11:37a Samir
 * Fixed goofup in tab ordering for trigger keypad.
 *
 * 43    3/03/97 5:23p Samir
 * Create osDatabase and osDebug obejcts.
 *
 * 42    3/02/97 4:21p Matt
 * Added code to select connected segments
 *
 * 41    2/28/97 6:40p Matt
 * Call code to call box selection code
 *
 * 40    2/28/97 4:00p Matt
 * Added code to handle the list of selected segments
 *
 * 39    2/28/97 2:37p Mark
 *
 * 38    2/28/97 11:09a Samir
 * Fixed Play in 640x480 menu item.
 *
 * 37    2/28/97 11:03a Samir
 * Changes to reflect newer gameos interface.
 *
 * 36    2/27/97 5:29p Mark
 *
 * 35    2/26/97 3:35p Mark
 *
 * 34    2/20/97 6:05p Samir
 * Allow for clean activation and deactivation of surfaces in editor when
 * going into fullscreen mode.
 *
 * 33    2/20/97 5:10p Samir
 * Added Tmap1 and Tmap2 apply accels.  Tmap1 works by doing a CTRL-1.
 *
 * 32    2/20/97 9:57a Matt
 * Added Add Segment
 *
 * 31    2/19/97 5:39p Matt
 * Made EditorStatus() take printf-type args, as the D1/D2 function did.
 *
 * 30    2/19/97 2:15p Samir
 * Added keypad info.
 *
 * 29    2/18/97 7:04p Samir
 * Added print status bar message functions
 *
 * 28    2/12/97 4:07p Samir
 * Prompts for hogfile name when staring hog editor.
 *
 * 27    2/12/97 2:33p Samir
 * Added hog dialog.
 *
 * 26    2/10/97 1:59p Jason
 * Better import anim/bitmap functionality
 *
 * 25    2/06/97 2:46p Jason
 * added import bitmap function
 *
 * 24    2/05/97 12:16p Samir
 * Added menu item for preferences.
 *
 * 23    2/04/97 5:27p Samir
 * Instead of GAME_MODE go to EDITOR_GAME_MODE when playing the level.
 *
 * 22    2/04/97 5:18p Samir
 * Added Leaving editor... option in File Menu
 *
 * 21    1/30/97 6:43p Samir
 * stupid forgetting an argument
 *
 * 20    1/30/97 6:24p Samir
 * Reflect changes in ddgr system and game->editor->game stuff
 *
 * 19    1/23/97 4:35p Samir
 * Added floating keypad toggle and support
 *
 * 18    1/21/97 12:45p Samir
 * Toggle to get rid of keypad
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstdio>

#include "stdafx.h"
#include "editor.h"

//	USER INTERFACE HEADERS
#include "MainFrm.h"
#include "editorDoc.h"
#include "editorView.h"
#include "TextureDialog.h"
#include "ObjectDialog.h"
#include "LightingDialog.h"
#include "MegacellKeypad.h"
#include "TriggerDialog.h"
#include "DoorwayDialog.h"
#include "TerrainDialog.h"
#include "WorldTexturesDialog.h"
#include "WorldWeaponsDialog.h"
#include "WorldObjectsDoorDialog.h"
#include "WorldObjectsLightDialog.h"
#include "WorldObjectsPlayerDialog.h"
#include "RoomKeypadDialog.h"
#include "MegacellDialog.h"
#include "WorldSoundsDialog.h"
#include "PathPadDialog.h"
#include "GrFontDialog.h"
#include "FloatingKeypadDialog.h"
#include "PreferencesDialog.h"
#include "HogDialog.h"
#include "D3Splash.h"
#include "filepagedialog.h"
#include "LevelDialog.h"
#include "ObjectListDialog.h"
#include "TelCom.h"
#include "Slew.h"
#include "AmbientSoundPattern.h"
#include "levelkeypad.h"
#include "matcenkeypad.h"
#include "scriptlevelinterface.h"
#include "ScriptMassCompile.h"
#include "EditLineDialog.h"

// D3 EDITOR HEADERS
#include "pserror.h"
#include "Application.h"
#include "AppDatabase.h"
#include "program.h"
#include "gr.h"
#include "init.h"
#include "mono.h"
#include "ds3dlib.h"
#include "ddio.h"
#include "descent.h"
#include "bitmap.h"
#include "gametexture.h"
#include "manage.h"
#include "vclip.h"
#include "erooms.h"
#include "HTexture.h"
#include "HView.h"
#include "selectedroom.h"
#include "drawworld.h"
#include "Group.h"
#include "moveworld.h"
#include "worldobjectsgenericdialog.h"
#include "objinfo.h"
#include "HFile.h"
#include "hroom.h"
#include "texture.h"
#include "read3ds.h"
#include "terrain.h"
#include "HObject.h"
#include "hotspotmap.h"
#include "TableFileEdit.h"
#include "BriefEdit.h"
#include "TableFileFilter.h"
#include "DallasMainDlg.h"
#include "ViewerPropDlg.h"
#include "mem.h"
#include "findintersection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_COMMAND(ID_TOOLS_WORLD_TEXTURES, OnToolsWorldTextures)
ON_WM_SIZE()
ON_COMMAND(ID_TOOLS_WORLD_WEAPONS, OnToolsWorldWeapons)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_DOOR, OnToolsWorldObjectsDoor)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_LIGHTS, OnToolsWorldObjectsLights)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_PLAYER, OnToolsWorldObjectsPlayer)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_POWERUPS, OnToolsWorldObjectsPowerups)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_ROBOTS, OnToolsWorldObjectsRobots)
ON_COMMAND(ID_SUBEDITORS_FONT, OnSubeditorsFont)

ON_COMMAND(ID_FILE_PLAY640X480, OnFilePlayin640x480)
ON_UPDATE_COMMAND_UI(ID_VIEW_KEYPAD_TOGGLE, OnUpdateViewKeypadToggle)
ON_COMMAND(ID_VIEW_KEYPAD_TOGGLE, OnViewKeypadToggle)
ON_COMMAND(ID_FILE_LEAVE_EDITOR, OnFileLeaveEditor)
ON_COMMAND(ID_FILE_PREFERENCES, OnFilePreferences)
ON_COMMAND(IDM_IMPORT_BITMAP, OnImportBitmap)
ON_COMMAND(ID_SUBEDITORS_HOGMAKER, OnSubeditorsHogmaker)
ON_COMMAND(ID_NUMPAD0, OnNumpad0)
ON_COMMAND(ID_NUMPAD1, OnNumpad1)
ON_COMMAND(ID_NUMPAD2, OnNumpad2)
ON_COMMAND(ID_NUMPAD3, OnNumpad3)
ON_COMMAND(ID_NUMPAD4, OnNumpad4)
ON_COMMAND(ID_NUMPAD5, OnNumpad5)
ON_COMMAND(ID_NUMPAD6, OnNumpad6)
ON_COMMAND(ID_NUMPAD7, OnNumpad7)
ON_COMMAND(ID_NUMPAD8, OnNumpad8)
ON_COMMAND(ID_NUMPAD9, OnNumpad9)
ON_COMMAND(ID_NUMPADDEL, OnNumpaddel)
ON_COMMAND(ID_NUMPADMINUS, OnNumpadminus)
ON_COMMAND(ID_NUMPADADD, OnNumpadadd)
ON_COMMAND(ID_VIEW_CENTERONMINE, OnViewCenterOnMine)
ON_COMMAND(ID_VIEW_MOVECAMERATOSELECTEDROOM, OnViewMoveCameraToSelectedRoom)
ON_COMMAND(ID_VIEW_CENTERONCUBE, OnViewCenterOnCube)
ON_COMMAND(ID_VIEW_CENTERONOBJECT, OnViewCenterOnObject)
ON_COMMAND(ID_GROUP_CREATEGROUP, OnGroupCreateGroup)
ON_COMMAND(ID_GROUP_LOADGROUP, OnGroupLoadGroup)
ON_COMMAND(ID_GROUP_MIRRORGROUP, OnGroupMirrorGroup)
ON_COMMAND(ID_GROUP_SAVEGROUP, OnGroupSaveGroup)
ON_COMMAND(ID_EDIT_ADDSELECT, OnEditAddSelect)
ON_COMMAND(ID_EDIT_CLEARSELECTED, OnEditClearSelected)
ON_COMMAND(ID_EDIT_REMOVESELECT, OnEditRemoveSelect)
ON_COMMAND(ID_EDIT_SELECTATTACHED, OnEditSelectAttached)
ON_COMMAND(ID_EDIT_SAVESCRAP, OnEditSaveScrap)
ON_COMMAND(ID_EDIT_LOADSCRAP, OnEditLoadScrap)
ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
ON_COMMAND(ID_EDIT_CUT, OnEditCut)
ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_CURSEG, OnSegSidePane)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_NET, OnNetPane)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_BMMEM, OnBMMemPane)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_ENGINE, OnEnginePane)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_VIEWER, OnViewerPane)
ON_COMMAND(ID_NUMPADDIV, OnNumpadDiv)
ON_COMMAND(ID_NUMPADENTER, OnNumpadEnter)
ON_COMMAND(ID_NUMPADLOCK, OnNumpadLock)
ON_COMMAND(ID_NUMPADMUL, OnNumpadMul)
ON_COMMAND(ID_OBJECT_DELETEOBJECT, OnObjectDeleteObject)
ON_COMMAND(ID_OBJECT_PLACEOBJECT, OnObjectPlaceObject)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_SOUND, OnToolsWorldObjectsSound)
ON_COMMAND(ID_TEST_TEST1, OnTestTest1)
ON_COMMAND(ID_TEST_TEST2, OnTestTest2)
ON_COMMAND(ID_TEST_TEST3, OnTestTest3)
ON_WM_HELPINFO()
ON_COMMAND(ID_EDITORS_MEGACELLS, OnEditorsMegacells)
ON_COMMAND(IDD_REORDER_PAGES, OnReorderPages)
ON_COMMAND(ID_FILE_IMPORT_ROOM, OnFileImportRoom)
ON_COMMAND(ID_OBJECT_MOVEPLAYER, OnObjectMovePlayer)
ON_COMMAND(ID_ROOM_VIEW, OnRoomView)
ON_COMMAND(ID_TERRAIN_VIEW, OnTerrainView)
ON_COMMAND(ID_MINE_VIEW, OnMineView)
ON_UPDATE_COMMAND_UI(ID_MINE_VIEW, OnUpdateMineView)
ON_UPDATE_COMMAND_UI(ID_ROOM_VIEW, OnUpdateRoomView)
ON_UPDATE_COMMAND_UI(ID_TERRAIN_VIEW, OnUpdateTerrainView)
ON_COMMAND(ID_VIEW_NEWVIEWER, OnViewNewviewer)
ON_COMMAND(ID_VIEWER_NEXT, OnViewNextviewer)
ON_COMMAND(ID_VIEW_DELETEVIEWER, OnViewDeleteviewer)
ON_COMMAND(ID_D3HELP, OnD3help)
ON_COMMAND(ID_HOTSPOT_TGA, OnHotspotTga)
ON_COMMAND(ID_EDITORS_FILES, OnEditorsFiles)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_CLUTTER, OnToolsWorldObjectsClutter)
ON_COMMAND(ID_TOOLS_WORLD_OBJECTS_BUILDINGS, OnToolsWorldObjectsBuildings)
ON_COMMAND(ID_EDIT_PLACE, OnEditPlace)
ON_COMMAND(ID_EDIT_ATTACH, OnEditAttach)
ON_UPDATE_COMMAND_UI(ID_EDIT_ATTACH, OnUpdateEditAttach)
ON_UPDATE_COMMAND_UI(ID_EDIT_SAVESCRAP, OnUpdateEditSaveScrap)
ON_COMMAND(ID_FILE_LEVELPROPS, OnFileLevelProps)
ON_COMMAND(ID_OBJBUTTON, OnObjbutton)
ON_UPDATE_COMMAND_UI(ID_OBJBUTTON, OnUpdateObjbutton)
ON_WM_NCDESTROY()
ON_COMMAND(ID_OBJECT_SETCAMERAFROMVIEWER, OnObjectSetCameraFromViewer)
ON_COMMAND(ID_OBJECT_PLACECAMERAATVIEWER, OnObjectPlaceCameraAtViewer)
ON_COMMAND(ID_OBJECT_SETVIEWERFROMCAMERA, OnObjectSetViewerFromCamera)
ON_WM_KEYDOWN()
ON_COMMAND(ID_FILE_LEVEL_INFO, OnFileLevelInfo)
ON_COMMAND(ID_FILE_STATS, OnFileStats)
ON_COMMAND(ID_FILE_VERIFY_LEVEL, OnFileVerifyLevel)
ON_COMMAND(ID_OBJECT_PLACECAMERAATCURRENTFACE, OnObjectPlaceCameraAtCurrentFace)
ON_COMMAND(ID_SUBEDITORS_TABLEFILEEDIT, OnSubEditorsTableFileEdit)
ON_COMMAND(ID_EDITORS_AMBIENTSOUNDS, OnEditorsAmbientSounds)
ON_COMMAND(ID_BRIEFING_EDITOR, OnBriefingEditor)
ON_COMMAND(ID_SCRIPT_LEVEL_INTERFACE, OnScriptLevelInterface)
ON_COMMAND(ID_FILE_FIXCRACKS, OnFileFixCracks)
ON_COMMAND(ID_VIEW_RESETVIEWRADIUS, OnViewResetViewRadius)
ON_COMMAND(ID_SUBEDITORS_TABLEFILEFILTER, OnSubeditorsTablefilefilter)
ON_COMMAND(ID_VIEW_SHOWOBJECTSINWIREFRAMEVIEW, OnViewShowObjectsInWireframeView)
ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWOBJECTSINWIREFRAMEVIEW, OnUpdateViewShowObjectsInWireframeView)
ON_COMMAND(ID_EDITORS_DALLAS, OnEditorsDallas)
ON_UPDATE_COMMAND_UI(ID_OSIRISCOMPILE, OnUpdateOsiriscompile)
ON_COMMAND(ID_OSIRISCOMPILE, OnOsiriscompile)
ON_COMMAND(ID_VIEW_MOVECAMERATOCURRENTOBJECT, OnViewMoveCameraToCurrentObject)
ON_COMMAND(ID_OBJECT_SELECTBYNUMBER, OnObjectSelectByNumber)
ON_COMMAND(IDD_SHOW_ALL_CHECKED_OUT, OnShowAllCheckedOut)
ON_COMMAND(ID_VIEW_SHOWVIEWERFORWARDVECTOR, OnViewShowViewerForwardVector)
ON_COMMAND(ID_OBJECT_PLACESOUNDSOURCEATVIEWER, OnObjectPlaceSoundSourceAtViewer)
ON_COMMAND(IDD_ORPHANHUNTER, OnOrphanhunter)
ON_COMMAND(ID_OBJECT_PLACEWAYPOINTATVIEWER, OnObjectPlaceWaypointAtViewer)
ON_COMMAND(ID_FILE_SAVEGOALTEXT, OnFileSaveGoalText)
ON_COMMAND(ID_VIEW_VIEWPROP, OnViewViewprop)
ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWPROP, OnUpdateViewViewprop)
ON_COMMAND(ID_VIEW_MOVECAMERATOSELECTEDFACE, OnViewMoveCameraToSelectedFace)
ON_COMMAND(ID_EDIT_PLACE_TERRAIN, OnEditPlaceTerrain)
ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
ON_COMMAND(ID_VIEW_NEXTVIEWER, OnViewNextviewer)
ON_COMMAND(ID_ACCEL_COPY_LIGHT_MULTIPLE, OnAccelCopyLightMultiple)
ON_COMMAND(ID_ACCEL_SLIDEDOWN, OnAccelSlidedown)
ON_COMMAND(ID_ACCEL_SLIDELEFT, OnAccelSlideleft)
ON_COMMAND(ID_ACCEL_SLIDERIGHT, OnAccelSlideright)
ON_COMMAND(ID_ACCEL_SLIDEUP, OnAccelSlideup)
ON_COMMAND(ID_ACCEL_NEXTVERTEX, OnAccelNextVertex)
//}}AFX_MSG_MAP
ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR,         // status line indicator
    ID_INDICATOR_BMMEM,   // How much memory our bitmaps used
    ID_INDICATOR_NET,     // network indicator
    ID_INDICATOR_CURSEG,  // our current seg.side indicator
    ID_INDICATOR_MARKSEG, // our marked seg.side indicator
    ID_INDICATOR_NUM,
    ID_INDICATOR_ENGINE, // which engine is running (mine or room)
    ID_INDICATOR_VIEWER  // which viewer is current
};

static CMainFrame *MFC_Main_frame = NULL;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() {
  // TODO: add member initialization code here
  m_KeypadTabDialog = NULL;

  m_LightingDialog = NULL;
  m_TextureDialog = NULL;
  m_ObjectDialog = NULL;
  m_TriggerDialog = NULL;
  m_DoorwayDialog = NULL;
  m_PathPadDialog = NULL;
  m_TerrainDialog = NULL;
  m_MegacellKeypad = NULL;
  m_LevelDialog = NULL;
  m_MatcenDialog = NULL;

  m_ObjModeless = NULL;
  m_KeypadTabCtrl = NULL;
  m_RoomDialog = NULL;
  m_FloatingKeypadDialog = NULL;
  m_D3Splash = NULL;
}

CMainFrame::~CMainFrame() {}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  //	Initializes the ddgr system and prepares for gr.
  if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
    TRACE0("Failed to create toolbar\n");
    return -1; // fail to create
  }

  if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
    TRACE0("Failed to create status bar\n");
    return -1; // fail to create
  }

  //	Add keypad dialog bar to the right side of the app.
  if (!m_wndKeypadBar.Create(this, IDD_KEYPAD_DLGBAR, CBRS_RIGHT, IDC_DLGBAR_KEYPAD)) {
    TRACE0("Failed to create status bar\n");
    return -1; // fail to create
  }

  // TODO: Remove this if you don't want tool tips or a resizeable toolbar
  m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

  // TODO: Delete these three lines if you don't want the toolbar to
  //  be dockable

  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_RIGHT);

  InitKeypadDialog();
  DockKeypad(TRUE); // dock if tiled

  theApp.main_frame = MFC_Main_frame = this;

  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT &cs) {
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const { CFrameWnd::AssertValid(); }

void CMainFrame::Dump(CDumpContext &dc) const { CFrameWnd::Dump(dc); }

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame private supporting functions

void CMainFrame::InitGraphicsSystem() {
  //	HERE: We create the DDGR Object for general GR use in the editor
  //	HERE: We end the DDGR creating module
}

//	Display current tab dialog
void CMainFrame::ShowCurrentKeypad() {
  switch (D3EditState.keypad_current) {
  case TAB_TEXTURE_KEYPAD:
    m_KeypadTabDialog = m_TextureDialog;
    break;
  case TAB_OBJECTS_KEYPAD:
    m_KeypadTabDialog = m_ObjectDialog;
    break;
  case TAB_LIGHTING_KEYPAD:
    m_KeypadTabDialog = m_LightingDialog;
    break;
  case TAB_ROOM_KEYPAD:
    m_KeypadTabDialog = m_RoomDialog;
    break;
  case TAB_PATHS_KEYPAD:
    m_KeypadTabDialog = m_PathPadDialog;
    break;
  case TAB_TRIGGER_KEYPAD:
    m_KeypadTabDialog = m_TriggerDialog;
    break;
  case TAB_DOORWAY_KEYPAD:
    m_KeypadTabDialog = m_DoorwayDialog;
    break;
  case TAB_TERRAIN_KEYPAD:
    m_KeypadTabDialog = m_TerrainDialog;
    break;
  case TAB_MEGACELL_KEYPAD:
    m_KeypadTabDialog = m_MegacellKeypad;
    break;
  case TAB_LEVEL_KEYPAD:
    m_KeypadTabDialog = m_LevelDialog;
    break;
  case TAB_MATCEN_KEYPAD:
    m_KeypadTabDialog = m_MatcenDialog;
    break;
  default:
    Int3();
  }

  if (m_KeypadTabDialog) {
    CTabCtrl *tab_ctrl = (CTabCtrl *)m_wndKeypadBar.GetDlgItem(IDC_KEYPADS);

    m_KeypadTabDialog->ShowWindow(SW_SHOW);
    tab_ctrl->SetCurSel(D3EditState.keypad_current);
  }
}

void CMainFrame::InitKeypadDialog() {
  CTabCtrl *tab_ctrl;
  TC_ITEM tc_item;

  m_KeypadTabCtrl = tab_ctrl = (CTabCtrl *)m_wndKeypadBar.GetDlgItem(IDC_KEYPADS);

  //	Add tabs to tabcontrol in the keypad dialog bar.
  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Texture";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_TEXTURE_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Megacell";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_MEGACELL_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Terrain";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_TERRAIN_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Object";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_OBJECTS_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Room";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_ROOM_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Doorway";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_DOORWAY_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Trigger";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_TRIGGER_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Lighting";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_LIGHTING_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Paths";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_PATHS_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Level";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_LEVEL_KEYPAD, &tc_item);

  tc_item.mask = TCIF_TEXT;
  tc_item.pszText = "Matcen";
  tc_item.cchTextMax = lstrlen(tc_item.pszText) + 1;
  tab_ctrl->InsertItem(TAB_MATCEN_KEYPAD, &tc_item);

  //	Get coordinates of dialog bar tab and
  RECT tab_rect, tab_winrect;
  int tx, ty, tw, th;

  tab_ctrl->GetWindowRect(&tab_winrect);
  ::CopyRect(&tab_rect, &tab_winrect);
  tab_ctrl->AdjustRect(FALSE, &tab_rect);
  tx = tab_rect.left - tab_winrect.left;
  ty = tab_rect.top - tab_winrect.top;
  tw = tab_rect.right - tab_rect.left;
  th = tab_rect.bottom - tab_rect.top;

  //	Create tab dialogs
  //	resize them to fit the tab control
  //	set scroll bars accordingly
  m_TextureDialog = new CTextureDialog(tab_ctrl);
  m_TextureDialog->Create();
  m_TextureDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_MegacellKeypad = new CMegacellKeypad(tab_ctrl);
  m_MegacellKeypad->Create();
  m_MegacellKeypad->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_ObjectDialog = new CObjectDialog(tab_ctrl);
  m_ObjectDialog->Create();
  m_ObjectDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_LightingDialog = new CLightingDialog(tab_ctrl);
  m_LightingDialog->Create();
  m_LightingDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_RoomDialog = new CRoomKeypadDialog(tab_ctrl);
  m_RoomDialog->Create();
  m_RoomDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_TriggerDialog = new CTriggerDialog(tab_ctrl);
  m_TriggerDialog->Create();
  m_TriggerDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_DoorwayDialog = new CDoorwayDialog(tab_ctrl);
  m_DoorwayDialog->Create();
  m_DoorwayDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_TerrainDialog = new CTerrainDialog(tab_ctrl);
  m_TerrainDialog->Create();
  m_TerrainDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_PathPadDialog = new CPathPadDialog(tab_ctrl);
  m_PathPadDialog->Create();
  m_PathPadDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_LevelDialog = new levelkeypad(tab_ctrl);
  m_LevelDialog->Create();
  m_LevelDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);

  m_MatcenDialog = new matcenkeypad(tab_ctrl);
  m_MatcenDialog->Create();
  m_MatcenDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
}

void CMainFrame::DisplaySplashScreen() {
  m_D3Splash = new CD3Splash(this);
  m_D3Splash->Create();
  m_D3Splash->ShowWindow(SW_SHOW);
  m_D3Splash->UpdateWindow();
}

void CMainFrame::RemoveSplashScreen() {
  if (!m_D3Splash)
    return;
  m_D3Splash->ShowWindow(SW_HIDE);
  m_D3Splash->DestroyWindow();
  m_D3Splash = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::ActivateFrame(int nCmdShow) {
  // TODO: Add your specialized code here and/or call the base class
  nCmdShow = SW_MAXIMIZE; // Force initial maximization

  RemoveSplashScreen(); // shown when CreateClient

  DockKeypad(D3EditState.tile_views);

  //	display object modeless if need be.
  if (D3EditState.objmodeless_on && !m_ObjModeless) {
    m_ObjModeless = new CObjectListModeless(this);
    m_ObjModeless->Create();
    m_ObjModeless->SetWindowPos(this, D3EditState.objmodeless_x, D3EditState.objmodeless_y, -1, -1, SWP_NOSIZE);
    m_ObjModeless->ShowWindow(SW_SHOW);
  }

  CFrameWnd::ActivateFrame(nCmdShow);
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) { return CFrameWnd::OnCommand(wParam, lParam); }

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if (nChar == VK_NUMPAD5) {
    SlewStop(Viewer_object);
  }

  CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult) {
  //	Perform notification requests on the keypad tab dialog bar and other
  //	custom control bars.
  NMHDR *nmhdr;

  assert(lParam != 0);

  nmhdr = (NMHDR *)lParam;

  switch (wParam) {
  case IDC_KEYPADS:
    DoKeypadTabNotify(nmhdr);
    break;
  }

  return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CMainFrame::DoKeypadTabNotify(NMHDR *nmhdr) {
  CTabCtrl *tab_ctrl;

  tab_ctrl = (CTabCtrl *)m_wndKeypadBar.GetDlgItem(IDC_KEYPADS);

  switch (nmhdr->code) {
  case TCN_SELCHANGE:
    // Tab control changed. So update the controls currently displayed.
    D3EditState.keypad_current = (int)tab_ctrl->GetCurSel();
    assert(D3EditState.keypad_current > -1);

    switch (D3EditState.keypad_current) {
    case TAB_TEXTURE_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_TextureDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_OBJECTS_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_ObjectDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_LIGHTING_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_LightingDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_ROOM_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_RoomDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_PATHS_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_PathPadDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_LEVEL_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_LevelDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_MATCEN_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_MatcenDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_TRIGGER_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_TriggerDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_DOORWAY_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_DoorwayDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_TERRAIN_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_TerrainDialog;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;

    case TAB_MEGACELL_KEYPAD:
      if (m_KeypadTabDialog)
        m_KeypadTabDialog->ShowWindow(SW_HIDE);
      m_KeypadTabDialog = m_MegacellKeypad;
      m_KeypadTabDialog->ShowWindow(SW_SHOW);
      break;
    }
    break;
  }
}

//	Put all non client window destruction here!
void CMainFrame::OnNcDestroy() { CFrameWnd::OnNcDestroy(); }

void CMainFrame::OnDestroy() {
  CFrameWnd::OnDestroy();

  // Save game & editor variables to the registry
  SaveGameSettings();
  SaveEditorSettings();

  //	kill game and editor objects outside MFC.
  if (Desktop_surf) {
    delete Desktop_surf;
    Desktop_surf = NULL;
  }
  if (Database) {
    delete Database;
    Database = NULL;
  }
  if (Descent) {
    delete Descent;
    Descent = NULL;
  }
}

void InitCScripts() {
  char path[_MAX_PATH];
  int dirlen = _MAX_PATH;

  // Create a default segment.  This should probably be in the editor initialization code
  // This call must come after InitObjects()
  CreateNewMine();

  //	Setup include directories for OSIRIS
  ddio_MakePath(path, Base_directory, "data", "levels", NULL);
}

//	Initializes OS components for Descent3.  MUST BE DONE BEFORE ANYTHING ELSE!

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext) {
  // TODO: Add your specialized code here and/or call the base class
  PreInitD3Systems();
  WinMainInitEditor((unsigned)CWnd::m_hWnd, (unsigned)AfxGetInstanceHandle());
  ProgramVersion(DEVELOPMENT_VERSION, 0, 0, 0);

  DisplaySplashScreen();

  // Initialize a ton of stuff.
  InitD3Systems1(true);
  InitD3Systems2(true);

  // Initialize scripts
  InitCScripts();

  // Load variables from registry
  LoadEditorSettings();

  // Change to the levels directory, since the most likely thing to open is a level
  ddio_SetWorkingDir("data\\levels");

  return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::ResizeKeypad() {
  if (::IsWindow(m_wndKeypadBar.m_hWnd)) {
    CTabCtrl *tab_ctrl;
    RECT tab_rect, tab_winrect, dbar_rect;
    int tx, ty, tw, th;

    tab_ctrl = (CTabCtrl *)m_wndKeypadBar.GetDlgItem(IDC_KEYPADS);

    m_wndKeypadBar.GetClientRect(&dbar_rect);
    dbar_rect.left += 2;
    dbar_rect.right -= 2;
    dbar_rect.top += 2;
    dbar_rect.bottom -= 2;
    tab_ctrl->MoveWindow(&dbar_rect);

    tab_ctrl->GetWindowRect(&tab_winrect);
    ::CopyRect(&tab_rect, &tab_winrect);
    tab_ctrl->AdjustRect(FALSE, &tab_rect);
    tx = tab_rect.left - tab_winrect.left;
    ty = tab_rect.top - tab_winrect.top;
    tw = tab_rect.right - tab_rect.left;
    th = tab_rect.bottom - tab_rect.top;

    if (m_TextureDialog)
      m_TextureDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_ObjectDialog)
      m_ObjectDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_LightingDialog)
      m_LightingDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_RoomDialog)
      m_RoomDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_PathPadDialog)
      m_PathPadDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_TriggerDialog)
      m_TriggerDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_DoorwayDialog)
      m_DoorwayDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_TerrainDialog)
      m_TerrainDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_MegacellKeypad)
      m_MegacellKeypad->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_LevelDialog)
      m_LevelDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
    if (m_MatcenDialog)
      m_MatcenDialog->SetWindowPos(tab_ctrl, tx, ty, tw, th, SWP_NOZORDER);
  }
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) {
  CFrameWnd::OnSize(nType, cx, cy);

  // TODO: Add your message handler code here
  ResizeKeypad();
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) {
#if 0
	CFrameWnd::OnActivateApp(bActive, hTask);
	
	if (bActive) {
		theApp.resume();
		mprintf_at(2,0,0, "App Active  ");
	}
	else {
		theApp.pause();
		mprintf_at(2,0,0, "App Inactive");
	}

  ((oeLnxApplication *)Descent)->run_handler(this->m_hWnd, WM_ACTIVATEAPP, (unsigned)bActive, 0);
#endif
}

//	---------------------------------------------------------------------------
//	These functions handle the status bar and displaying stuff in the status bar.
//	---------------------------------------------------------------------------

void CMainFrame::SetStatusMessage(char *str) { m_wndStatusBar.SetPaneText(0, str); }

void EditorStatus(const char *format, ...) {
  if (MFC_Main_frame) {
    char status_line[256];
    std::va_list ap;

    va_start(ap, format);
    std::vsnprintf(status_line, 256, format, ap);
    va_end(ap);

    MFC_Main_frame->SetStatusMessage(status_line);
  }
}

void SplashMessage(const char *format, ...) {
  if (D3_splash_screen) {
    char status_line[256];
    std::va_list ap;

    va_start(ap, format);
    std::vsnprintf(status_line, 256, format, ap);
    va_end(ap);

    D3_splash_screen->PutText(status_line);
  }
}

char Editor_error_message[1000] = "";

// Set the editor error message.  A function that's going to return a failure
// code should call this with the error message.
void SetErrorMessage(const char *fmt, ...) {
  std::va_list arglist;

  va_start(arglist, fmt);
  std::vsnprintf(Editor_error_message, sizeof(Editor_error_message), fmt, arglist);
  va_end(arglist);

  mprintf(0, "Editor error: %s\n", Editor_error_message);
}

// Get the error message from the last function that returned failure
const char *GetErrorMessage() { return Editor_error_message; }

void CMainFrame::OnSegSidePane(CCmdUI *pCmdUI) {
  CString strSegSide;

  pCmdUI->Enable();
  if (Editor_view_mode == VM_TERRAIN) {
    // We could put something here, but I don't know what.  Jason?
  } else if (Editor_view_mode == VM_MINE) {
    if (Curroomp)
      strSegSide.Format("Cur %d:%d", ROOMNUM(Curroomp), Curface);
    else
      strSegSide.Format("No curroom");
  } else if (Editor_view_mode == VM_ROOM) {
    if (Current_faces[D3EditState.current_room - FIRST_PALETTE_ROOM] != -1)
      strSegSide.Format("Face %d", Current_faces[D3EditState.current_room - FIRST_PALETTE_ROOM]);
    else
      strSegSide.Format("No face");
  } else
    Int3();

  pCmdUI->SetText(strSegSide);
}

void CMainFrame::OnBMMemPane(CCmdUI *pCmdUI) {
  CString strSegSide;

  pCmdUI->Enable();

  strSegSide.Format("Bitmap memory: %d K", Bitmap_memory_used / 1000);

  pCmdUI->SetText(strSegSide);
}

void CMainFrame::OnEnginePane(CCmdUI *pCmdUI) {
  CString strEngineType;

  pCmdUI->Enable();

  switch (Editor_view_mode) {
  case VM_MINE:
    strEngineType.Format("Mine View");
    break;
  case VM_TERRAIN:
    strEngineType.Format("Terrain View");
    break;
  case VM_ROOM:
    strEngineType.Format("Room View");
    break;
  }
  pCmdUI->SetText(strEngineType);
}

void CMainFrame::OnViewerPane(CCmdUI *pCmdUI) {
  CString strViewerNum;

  pCmdUI->Enable();

  if (Editor_view_mode == VM_ROOM)
    strViewerNum.Format(""); // Don't show viewer number in room view
  else
    strViewerNum.Format("Viewer %d", GetViewerNum());

  pCmdUI->SetText(strViewerNum);
}

void CMainFrame::OnNetPane(CCmdUI *pCmdUI) {
  CString strSegSide;

  pCmdUI->Enable();
  if (Network_up)
    strSegSide.Format("NET");
  else
    strSegSide.Format("NoNet");

  pCmdUI->SetText(strSegSide);
}

//	---------------------------------------------------------------------------
//	Menu items
//	---------------------------------------------------------------------------

void CMainFrame::OnToolsWorldTextures() {
  CWorldTexturesDialog wtexdlg;

  theApp.pause();
  wtexdlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnToolsWorldWeapons() {
  CWorldWeaponsDialog wweapdlg;

  theApp.pause();
  wweapdlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnToolsWorldObjectsDoor() {
  CWorldObjectsDoorDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnToolsWorldObjectsLights() {
  CWorldObjectsLightDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnToolsWorldObjectsPlayer() {
  CWorldObjectsPlayerDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnToolsWorldObjectsPowerups() {
  CWorldObjectsGenericDialog dlg;

  dlg.m_type = OBJ_POWERUP;
  dlg.m_current = D3EditState.current_powerup;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();

  if (dlg.m_current != -1)
    D3EditState.current_powerup = dlg.m_current;
}

void CMainFrame::OnToolsWorldObjectsRobots() {
  CWorldObjectsGenericDialog dlg;

  dlg.m_type = OBJ_ROBOT;
  dlg.m_current = D3EditState.current_robot;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();

  if (dlg.m_current != -1)
    D3EditState.current_robot = dlg.m_current;
}

void CMainFrame::OnToolsWorldObjectsClutter() {
  CWorldObjectsGenericDialog dlg;

  dlg.m_type = OBJ_CLUTTER;
  dlg.m_current = D3EditState.current_clutter;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();

  if (dlg.m_current != -1)
    D3EditState.current_clutter = dlg.m_current;
}

void CMainFrame::OnToolsWorldObjectsBuildings() {
  CWorldObjectsGenericDialog dlg;

  dlg.m_type = OBJ_BUILDING;
  dlg.m_current = D3EditState.current_building;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();

  if (dlg.m_current != -1)
    D3EditState.current_building = dlg.m_current;
}

void CMainFrame::OnSubeditorsFont() {
  CGrFontDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnUpdateViewKeypadToggle(CCmdUI *pCmdUI) { pCmdUI->SetCheck((BOOL)D3EditState.keypad_visible); }

void CMainFrame::OnViewKeypadToggle() {
  D3EditState.keypad_visible = !D3EditState.keypad_visible;

  if (D3EditState.tile_views) {
    ShowControlBar(&m_wndKeypadBar, (BOOL)D3EditState.keypad_visible, FALSE);
    ResizeKeypad();
    ShowCurrentKeypad();
  } else if (!D3EditState.keypad_visible && m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->ShowWindow(SW_HIDE);
  else if (D3EditState.keypad_visible && m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->ShowWindow(SW_SHOW);
}

void CMainFrame::DockKeypad(BOOL dock) {
  if (D3EditState.keypad_visible) {
    if (dock) {
      //	Resize the keypad to the size of the window.
      if (m_FloatingKeypadDialog) {
        m_FloatingKeypadDialog->DestroyWindow();
        m_FloatingKeypadDialog = NULL;
      }
      ShowControlBar(&m_wndKeypadBar, TRUE, FALSE);
      ResizeKeypad();
      ShowCurrentKeypad();
    } else {
      ShowControlBar(&m_wndKeypadBar, FALSE, FALSE);
      if (!m_FloatingKeypadDialog) {
        if (!D3EditState.float_keypad_moved) {
          RECT rect;
          m_wndKeypadBar.GetWindowRect(&rect);
          GetActiveFrame()->ScreenToClient(&rect);
          D3EditState.float_keypad_x = rect.left;
          D3EditState.float_keypad_y = rect.top;
        }

        CWnd *wnd = GetActiveView();

        m_FloatingKeypadDialog = new CFloatingKeypadDialog(wnd);
        m_FloatingKeypadDialog->Create();

        if (!D3EditState.float_keypad_moved) {
          RECT rect;
          m_FloatingKeypadDialog->GetWindowRect(&rect);
          D3EditState.float_keypad_w = rect.right - rect.left;
          D3EditState.float_keypad_h = rect.bottom - rect.top;
        }
      }

      // place keypad at right, top of desktop if not already placed
      m_FloatingKeypadDialog->SetWindowPos(NULL, D3EditState.float_keypad_x, D3EditState.float_keypad_y,
                                           D3EditState.float_keypad_w, D3EditState.float_keypad_h, SWP_NOZORDER);
      m_FloatingKeypadDialog->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
      m_FloatingKeypadDialog->ShowWindow(SW_SHOW);
      D3EditState.float_keypad_moved = 1;
    }
  } else {
    //	 keypad is NOT visi  .
    ShowControlBar(&m_wndKeypadBar, FALSE, FALSE);
  }
}

//	Invoke Descent 3 from D3Edit

extern void RunGameFromEditor();

void CMainFrame::OnFilePlayin640x480() {
  // Returns true if there are out of data files
  int count = AreScriptsOutofDate();
  if (count > 0) {
    if (OutrageMessageBox(MBOX_YESNO, "There were %d scripts that couldn't be compiled, continue?", count) != IDYES)
      return;
  }

  renderer_type sr_save;
  bool keypad_was_visible = D3EditState.keypad_visible;
  DWORD cbar_was_visible = (m_wndToolBar.GetStyle() & WS_VISIBLE);
  DWORD status_was_visible = (m_wndStatusBar.GetStyle() & WS_VISIBLE);

  //	Shutdown view system
  m_ViewActivated = FALSE;
  ((CEditorView *)GetActiveView())->DeactivateView();
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->Deactivate();
  CKeypadDialog::Deactivate();
  delete Desktop_surf;

  //	hide keypad if it's visible
  if (keypad_was_visible)
    OnViewKeypadToggle();
  if (cbar_was_visible)
    ShowControlBar(&m_wndToolBar, FALSE, FALSE);
  if (status_was_visible)
    ShowControlBar(&m_wndStatusBar, FALSE, FALSE);

  SetFunctionMode(EDITOR_GAME_MODE);

  sr_save = Renderer_type;

  //	if we have selected the windowed toggle, assert this.
  if (D3EditState.game_render_mode == GM_WINDOWED)
    PROGRAM(windowed) = 1;
  else
    PROGRAM(windowed) = 0;

  RunGameFromEditor();
  PROGRAM(windowed) = 1;

  Renderer_type = sr_save;

  //	hide keypad if it's visible
  if (status_was_visible)
    ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
  if (cbar_was_visible)
    ShowControlBar(&m_wndToolBar, TRUE, FALSE);
  if (keypad_was_visible)
    OnViewKeypadToggle();

  //	Restore view system
  Desktop_surf = new grSurface(0, 0, 0, SURFTYPE_VIDEOSCREEN, 0);
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->Activate();
  CKeypadDialog::Activate();
  ((CEditorView *)GetActiveView())->ActivateView();
  m_ViewActivated = TRUE;
}

void CMainFrame::OnFileLeaveEditor() {
  // Returns true if there are out of data files
  int count = AreScriptsOutofDate();
  if (count > 0) {
    if (OutrageMessageBox(MBOX_YESNO, "There were %d scripts that couldn't be compiled, continue?", count) != IDYES)
      return;
  }

  bool keypad_was_visible = D3EditState.keypad_visible;
  DWORD cbar_was_visible = (m_wndToolBar.GetStyle() & WS_VISIBLE);
  DWORD status_was_visible = (m_wndStatusBar.GetStyle() & WS_VISIBLE);

  //	Shutdown view system
  m_ViewActivated = FALSE;
  ((CEditorView *)GetActiveView())->DeactivateView();
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->Deactivate();
  CKeypadDialog::Deactivate();
  delete Desktop_surf;

  //	hide keypad if it's visible
  if (keypad_was_visible)
    OnViewKeypadToggle();
  if (cbar_was_visible)
    ShowControlBar(&m_wndToolBar, FALSE, FALSE);
  if (status_was_visible)
    ShowControlBar(&m_wndStatusBar, FALSE, FALSE);

  SetFunctionMode(MENU_MODE);

  //	if we have selected the windowed toggle, assert this.
  if (D3EditState.game_render_mode == GM_WINDOWED)
    PROGRAM(windowed) = 1;
  else
    PROGRAM(windowed) = 0;

  RunGameFromEditor();
  PROGRAM(windowed) = 1;

  //	hide keypad if it's visible
  if (status_was_visible)
    ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
  if (cbar_was_visible)
    ShowControlBar(&m_wndToolBar, TRUE, FALSE);
  if (keypad_was_visible)
    OnViewKeypadToggle();

  //	Restore view system
  Desktop_surf = new grSurface(0, 0, 0, SURFTYPE_VIDEOSCREEN, 0);
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->Activate();
  CKeypadDialog::Activate();
  ((CEditorView *)GetActiveView())->ActivateView();
  m_ViewActivated = TRUE;
}

void CMainFrame::OnFilePreferences() {
  CPreferencesDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnImportBitmap() {
  char filename[200];
  int bm_handle, anim = 0;

  CString filter =
      "Descent III files (*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  bm_handle = LoadTextureImage(filename, &anim, NOT_TEXTURE, 0);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir, GameBitmaps[bm_handle].name);
    bm_SaveFileBitmap(filename, bm_handle);
    bm_FreeBitmap(bm_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir, GameVClips[bm_handle].name);
    SaveVClip(filename, bm_handle);
    FreeVClip(bm_handle);
  }

  OutrageMessageBox("Image(s) imported!");
}

void CMainFrame::OnSubeditorsHogmaker() {
  //	Open common file open dialog box.
  CString filter = "Descent III hogfiles (*.hog)|*.hog||";
  CFileDialog dlg_open(TRUE, 0, 0, OFN_FILEMUSTEXIST, (LPCTSTR)filter, this);
  char filename[_MAX_PATH];

  if (dlg_open.DoModal() == IDCANCEL) {
    return;
  }

  lstrcpy(filename, dlg_open.GetPathName());

  //	Open the HOG Dialog
  CHogDialog dlg(this, filename);

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

//	---------------------------------------------------------------------------
//	Number PAD functions
//	---------------------------------------------------------------------------

void CMainFrame::OnNumpad0() {
  mprintf(0, "NUMPAD0\n");
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD0);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD0);
}

void CMainFrame::OnNumpad1() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD1);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD1);
}

void CMainFrame::OnNumpad2() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD2);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD2);
}

void CMainFrame::OnNumpad3() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD3);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD3);
}

void CMainFrame::OnNumpad4() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD4);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD4);
}

void CMainFrame::OnNumpad5() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD5);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD5);
}

void CMainFrame::OnNumpad6() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD6);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD6);
}

void CMainFrame::OnNumpad7() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD7);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD7);
}

void CMainFrame::OnNumpad8() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD8);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD8);
}

void CMainFrame::OnNumpad9() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMPAD9);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMPAD9);
}

void CMainFrame::OnNumpaddel() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_DELETE);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_DELETE);
}

void CMainFrame::OnNumpadminus() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_SUBTRACT);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_SUBTRACT);
}

void CMainFrame::OnNumpadadd() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_ADD);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_ADD);
}

void CMainFrame::OnNumpadDiv() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_DIVIDE);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_DIVIDE);
}

void CMainFrame::OnNumpadEnter() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_RETURN);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_RETURN);
}

void CMainFrame::OnNumpadLock() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_NUMLOCK);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_NUMLOCK);
}

void CMainFrame::OnNumpadMul() {
  if (!D3EditState.keypad_visible)
    return;
  if (m_FloatingKeypadDialog)
    m_FloatingKeypadDialog->RunKeypadFunction(VK_MULTIPLY);
  else if (m_KeypadTabDialog)
    m_KeypadTabDialog->RunKeypadFunction(VK_MULTIPLY);
}

//	---------------------------------------------------------------------------
//	Yet more editor functions
//	---------------------------------------------------------------------------

void CMainFrame::OnViewCenterOnMine() { ResetWireframeView(); }

void CMainFrame::OnViewMoveCameraToSelectedRoom() { SetViewerFromRoomFace(Curroomp, Curface, 1); }

void CMainFrame::OnViewCenterOnCube() {
  vector pos;

  if (Editor_view_mode == VM_ROOM)
    ComputeRoomCenter(&pos, &Rooms[D3EditState.current_room]);
  else
    ComputeRoomCenter(&pos, Curroomp);

  SetWireframeView(&pos);
}

void CMainFrame::OnViewCenterOnObject() { SetWireframeView(&Objects[Cur_object_index].pos); }

void CMainFrame::OnGroupCreateGroup() {
  // TODO: Add your command handler code here
}

void CMainFrame::OnGroupLoadGroup() {
  // TODO: Add your command handler code here
}

void CMainFrame::OnGroupMirrorGroup() {
  // TODO: Add your command handler code here
}

void CMainFrame::OnGroupSaveGroup() {
  // TODO: Add your command handler code here
}

void CMainFrame::OnEditAddSelect() { AddRoomToSelectedList(ROOMNUM(Curroomp)); }

void CMainFrame::OnEditClearSelected() { ClearRoomSelectedList(); }

void CMainFrame::OnEditRemoveSelect() { RemoveRoomFromSelectedList(ROOMNUM(Curroomp)); }

void CMainFrame::OnEditSelectAttached() {
  int count;

  count = SelectConnectedRooms(ROOMNUM(Curroomp));

  EditorStatus("%d rooms selected", count);
}

void CMainFrame::OnEditSaveScrap() {
  if (Scrap == NULL) {
    OutrageMessageBox("The scrap buffer is empty.");
    return;
  }

  CString filter = "D3 Group Files (*.grp)|*.grp||";
  char filename[255];

  if (!SaveFileDialog(this, (LPCSTR)filter, filename, Current_scrap_dir, sizeof(Current_scrap_dir)))
    return;

  if (!strchr(filename, '.'))
    strcat(filename, ".grp");

  SaveGroup(filename, Scrap);

  EditorStatus("Group saved to %s", filename);
}

void CMainFrame::OnEditLoadScrap() {
  CString filter = "D3 Group Files (*.grp)|*.grp||";
  char filename[255];
  group *newscrap;

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_scrap_dir, sizeof(Current_scrap_dir)))
    return;

  if (!strchr(filename, '.'))
    strcat(filename, ".grp");

  newscrap = LoadGroup(filename);

  if (newscrap) {
    if (Scrap)
      FreeGroup(Scrap);
    Scrap = newscrap;
    EditorStatus("Group loaded from %s", filename);
  }
}

// Copies the selected rooms to the scrap buffer.
// Returns:	true if copied ok, 0 if some error
int CopySelectedRooms() {
  if (N_selected_rooms == 0) {
    OutrageMessageBox("You must have rooms selected for this operation.");
    return 0;
  }

  if (!Markedroomp) {
    OutrageMessageBox("You must have a marked room for this operation.");
    return 0;
  }

  if (!IsRoomSelected(ROOMNUM(Markedroomp))) {
    OutrageMessageBox("The Marked room must be selected for this operation.");
    return 0;
  }

  if (!((Markedroomp->faces[Markedface].portal_num == -1) ||
        (Markedroomp->portals[Markedroomp->faces[Markedface].portal_num].croom == -1) ||
        !IsRoomSelected(Markedroomp->portals[Markedroomp->faces[Markedface].portal_num].croom))) {
    OutrageMessageBox("The Marked room/face must be unattached for this operation.");
    return 0;
  }

  // Get rid of old contents of scrap buffer
  if (Scrap)
    FreeGroup(Scrap);

  Scrap = CopyGroup(N_selected_rooms, Selected_rooms, ROOMNUM(Markedroomp), Markedface);

  return 1;
}

void CMainFrame::OnEditCopy() {
  if (CopySelectedRooms())
    EditorStatus("%d rooms copied to Scrap", N_selected_rooms);
}

void CMainFrame::OnEditPlace() {
  if (!Scrap) {
    OutrageMessageBox("There is nothing in the scrap buffer.");
    return;
  }

  if (Curroomp->faces[Curface].portal_num != -1) {
    OutrageMessageBox("The selected Room/Face must be free for this operation.");
    return;
  }

  PlaceGroup(Curroomp, Curface, Scrap);
}

void CMainFrame::OnEditPlaceTerrain() {
  if (!Scrap) {
    OutrageMessageBox("There is nothing in the scrap buffer.");
    return;
  }

  int cellnum;

  if (Num_terrain_selected != 1) {
    OutrageMessageBox("You must have one and only one cell selected this operation");
    return;
  } else {
    for (cellnum = 0; cellnum < TERRAIN_WIDTH * TERRAIN_DEPTH; cellnum++)
      if (TerrainSelected[cellnum])
        break;

    ASSERT(cellnum != TERRAIN_WIDTH * TERRAIN_DEPTH);
  }

  int result = OutrageMessageBox(MBOX_YESNOCANCEL, "Do you want to align to the terrain? NO will align with gravity.");

  if (result == IDCANCEL)
    return;

  PlaceGroupTerrain(cellnum, Scrap, (result == IDYES));
}

void CMainFrame::OnEditAttach() {
  ASSERT(Placed_group != NULL);

  AttachGroup();
}

void CMainFrame::OnEditCut() {
  if (CopySelectedRooms()) {
    int n = N_selected_rooms;
    DeleteGroup(N_selected_rooms, Selected_rooms);
    EditorStatus("%d rooms cut to Scrap", n);
    ClearRoomSelectedList();
  }
}

void CMainFrame::OnEditDelete() {
  if (N_selected_rooms == 0) {
    OutrageMessageBox("You must have rooms selected for this operation.");
    return;
  }

  DeleteGroup(N_selected_rooms, Selected_rooms);
  EditorStatus("%d rooms deleted", N_selected_rooms);
  ClearRoomSelectedList();
}

void CMainFrame::OnObjectDeleteObject() {
  // TODO: Add your command handler code here
  if (m_ObjectDialog)
    m_ObjectDialog->DeleteObject();
}

void CMainFrame::OnObjectPlaceObject() {
  // TODO: Add your command handler code here
  if (m_ObjectDialog)
    m_ObjectDialog->PlaceObject();
}

void CMainFrame::OnToolsWorldObjectsSound() {
  CWorldSoundsDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

// Keep this around
void ResetObjectOntoTerrain() {
  if (Cur_object_index != -1) {

    object *objp = &Objects[Cur_object_index];

    if (!OBJECT_OUTSIDE(objp)) {
      int roomnum = GetTerrainRoomFromPos(&objp->pos);
      ObjSetPos(objp, &objp->pos, roomnum, NULL, true);

      EditorStatus("Object %d (\"%s\") moved to cell %d", OBJNUM(objp), objp->name ? objp->name : "<no name>",
                   CELLNUM(roomnum));

      World_changed = 1;
    } else
      EditorStatus("Object %d (\"%s\") already outside (on cell %d)", OBJNUM(objp),
                   objp->name ? objp->name : "<no name>", CELLNUM(objp->roomnum));
  }
}

// Keep this around
void ResetObjectsIntoMine() {
  int i, objnum, count = 0;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      for (objnum = Terrain_seg[i].objects; objnum != -1;) {
        object *objp = &Objects[objnum];
        int next = objp->next;
        if ((objp->type != OBJ_VIEWER) && (objp->type != OBJ_ROOM)) {
          int roomnum = FindPointRoom(&objp->pos);
          if (roomnum == -1)
            OutrageMessageBox("Can't find room for object %d (type = %s)", objnum, Object_type_names[objp->type]);
          else {
            mprintf(0, "Moving object %d to room %d\n", objnum, roomnum);
            ObjSetPos(&Objects[objnum], &objp->pos, roomnum, NULL, true);
            count++;
          }
        }
        objnum = next;
      }
    }
  }

  OutrageMessageBox("%d objects were moved from the terrain to the mine.", count);

  World_changed = 1;
}

void DeleteAllFacesWithTexture1(room *rp) {
  int count = 0;

  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete all faces in room %d that have texture 1?",
                        ROOMNUM(rp)) != IDYES)
    return;

  for (int i = 0; i < rp->num_faces; i++) {
    if ((rp->faces[i].tmap == 1) && (rp->faces[i].portal_num == -1)) {
      DeleteRoomFace(rp, i);
      i--;
      count++;
    }
  }

  OutrageMessageBox("%d faces deleted from room %d.", count, ROOMNUM(rp));

  Curface = Curedge = Curvert = 0;

  World_changed = 1;
}

// Put test code here.  Feel free to delete any old code.

extern float Room_multiplier[];

#include "lightmap_info.h"
#include "lightmap.h"
#include "polymodel.h"

int IsNonRenderableSubmodel(poly_model *pm, int submodelnum);

extern uint16_t *Free_lmi_list;

void CMainFrame::OnTestTest1() {
  if (MessageBox("Do you really really want to murder the lightmaps?", "Confirm", MB_YESNO) != IDYES)
    return;

  // severly bash lightmaps
  int r, f;
  room *rp;
  face *fp;

  for (r = 0; r <= Highest_room_index; r++) {
    if (!Rooms[r].used)
      continue;
    rp = &Rooms[r];
    for (f = 0; f < rp->num_faces; f++) {
      fp = &rp->faces[f];
      fp->flags &= ~FF_LIGHTMAP;
      fp->lmi_handle = BAD_LMI_INDEX;
    }
  }

  // now free lightmap infos
  void CloseLightmapInfos();
  CloseLightmapInfos();
  InitLightmapInfo(0);
  Num_of_lightmap_info = 0;
  Num_lightmap_infos_read = 0;

  int i, m, t;
  for (i = 0; i < MAX_OBJECTS; i++) {
    if (!Objects[i].lm_object.used)
      continue;

    poly_model *pm = &Poly_models[Objects[i].rtype.pobj_info.model_num];
    for (m = 0; m < pm->n_models; m++) {
      if (IsNonRenderableSubmodel(pm, m))
        continue;

      for (t = 0; t < Objects[i].lm_object.num_faces[m]; t++) {
        lightmap_object_face *fp = &Objects[i].lm_object.lightmap_faces[m][t];
        fp->lmi_handle = BAD_LMI_INDEX;
        mem_free(fp->u2);
        mem_free(fp->v2);
      }
      mem_free(Objects[i].lm_object.lightmap_faces[m]);
    }

    Objects[i].lm_object.used = 0;
  }
}

extern void dump_text_to_clipboard(char *text);

// Make a list of all the rooms with names
void ShowRooms() {
  char text_buf[10000], *t;
  int i, n;

  t = text_buf;
  sprintf(t, "");
  for (i = n = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && Rooms[i].name) {
      sprintf(t, "Room %d is named \"%s\"\n", i, Rooms[i].name);
      n++;
      t += strlen(t);
      if ((t - text_buf) > (sizeof(text_buf) - 200)) {
        sprintf(t, "Out of buffer space\n");
        break;
      }
    }
  }

  dump_text_to_clipboard(text_buf);

  OutrageMessageBox("There are %d named rooms.\n\nThe list has been written to the clipboard.", n);
}

void ListAllObjects() {
  void ListObjectsInAllLevels();
  extern bool Stay_paused;

  if (OutrageMessageBox(MBOX_YESNO, "This will take a long time.\n\nAre you sure you want to continue?") != IDYES)
    return;

  theApp.pause();
  Stay_paused = 1;
  SetFunctionMode(EDITOR_GAME_MODE); // keep LoadLevel() from bringing up messages
  ListObjectsInAllLevels();
  SetFunctionMode(EDITOR_MODE);
  Stay_paused = 0;
  theApp.resume();

  OutrageMessageBox("Object infomation written to clipboard.");
}

void FindBadDestroyedTextures() {
  int count = 0;

  for (int i = 0; i < MAX_TEXTURES; i++) {
    if ((GameTextures[i].flags & TF_DESTROYABLE) && (GameTextures[i].destroy_handle == 0)) {
      mprintf(0, "Texture %d, \"%s\" has a bad destroyed bitmap\n", i, GameTextures[i].name);
      count++;
    }
  }

  OutrageMessageBox("Found %d bad destroyed textures.", count);
}

// Make a list of all the objects with lightmaps
void ListLightmapObjects() {
  int count = 0, lm_count = 0;

  for (int i = 0; i <= Highest_object_index; i++) {
    if (Objects[i].type != OBJ_NONE) {
      count++;
      if (IS_GENERIC(Objects[i].type) &&
          (Object_info[Objects[i].id].lighting_info.lighting_render_type == LRT_LIGHTMAPS)) {
        lm_count++;
        mprintf(0, "%d: %s  %s", i, Object_type_names[Objects[i].type], Object_info[Objects[i].id].name);
        if (Objects[i].name)
          mprintf(0, "  name=\"%s\"\n", Objects[i].name);
        else
          mprintf(0, "\n");
      } else
        ; // mprintf(0,"%d ",i);
    }
  }
  mprintf(0, "Num object = %d.  Num with lightmaps = %d\n", count, lm_count);
}

// Put test code here.  Feel free to delete any old code.
void CMainFrame::OnTestTest2() { FindBadDestroyedTextures(); }

extern char error_buf[];
extern int error_buf_offset;
void CheckError(const char *str, ...);
uint32_t check_point_to_face(vector *colp, vector *face_normal, int nv, vector **vertex_ptr_list);

void LookForFVICracks() {
  int r, f, v, edgemask, count = 0;
  room *rp;
  face *fp;

  error_buf_offset = 0;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
        vector *vertex_ptr_list[MAX_VERTS_PER_FACE];
        for (v = 0; v < fp->num_verts; v++)
          vertex_ptr_list[v] = &rp->verts[fp->face_verts[v]];
        for (v = 0; v < fp->num_verts; v++) {
          edgemask = check_point_to_face(vertex_ptr_list[v], &fp->normal, fp->num_verts, vertex_ptr_list);
          if (edgemask) {
            CheckError("Vert %d is outside of %d:%d\n", v, r, f);
            count++;
          }
        }
      }
    }
  }

  DumpTextToClipboard(error_buf);

  OutrageMessageBox("Found %d FVI face cracks.", count);
}

void MoveEntireMine() {
  char buf[10] = "";

  strcpy(buf, "0");
  if (!InputString(buf, sizeof(buf), "Move Amount", "Enter an amount to move in X"))
    return;
  float delta_x = atof(buf);

  strcpy(buf, "0");
  if (!InputString(buf, sizeof(buf), "Move Amount", "Enter an amount to move in Z"))
    return;
  float delta_z = atof(buf);

  int r;
  room *rp;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (int v = 0; v < rp->num_verts; v++) {
        rp->verts[v].x += delta_x;
        rp->verts[v].z += delta_z;
      }

      for (int objnum = rp->objects; objnum != -1; objnum = Objects[objnum].next) {
        Objects[objnum].pos.x += delta_x;
        Objects[objnum].pos.z += delta_z;
      }
    }
  }

  World_changed = 1;
}

void ScaleEntireMine() {
  char buf[10] = "";

  if (!InputString(buf, sizeof(buf), "Scale Amount", "Enter an amount by which to scale the mine"))
    return;

  float scale = atof(buf);

  int r;
  room *rp;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (int v = 0; v < rp->num_verts; v++)
        rp->verts[v] *= scale;

      for (int objnum = rp->objects; objnum != -1; objnum = Objects[objnum].next)
        Objects[objnum].pos *= scale;
    }
  }

  World_changed = 1;
}

int CountSpecularFaces() {
  int i, t;
  int count = 0;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      room *rp = &Rooms[i];

      for (t = 0; t < rp->num_faces; t++) {
        face *fp = &rp->faces[t];
        if (GameTextures[fp->tmap].flags & TF_SPECULAR) {
          count++;
        }
      }
    }
  }

  return count;
}

// Put test code here.  Feel free to delete any old code.
void CMainFrame::OnTestTest3() {
  MoveEntireMine();
  return;

  // ResetObjectsIntoMine();

  // Check all powerups and make sure they all have physics on them (for spewing)
  CFILE *file = cfopen("C:\\physics.txt", "wt");
  if (!file)
    return;

  char buffer[384];

  for (int i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type == OBJ_NONE)
      continue;

    switch (Object_info[i].type) {
    case OBJ_POWERUP: {
      if (!(Object_info[i].flags & OIF_USES_PHYSICS)) {
        sprintf(buffer, "Powerup: %s", Object_info[i].name);
        cf_WriteString(file, buffer);
      }
    } break;
    case OBJ_CLUTTER: {
      if (!(Object_info[i].flags & OIF_USES_PHYSICS)) {
        sprintf(buffer, "Clutter: %s", Object_info[i].name);
        cf_WriteString(file, buffer);
      }
    } break;
    case OBJ_BUILDING: {
      if (!(Object_info[i].flags & OIF_USES_PHYSICS)) {
        sprintf(buffer, "Building: %s", Object_info[i].name);
        cf_WriteString(file, buffer);
      }
    } break;
    case OBJ_ROBOT: {
      if (!(Object_info[i].flags & OIF_USES_PHYSICS)) {
        sprintf(buffer, "Robot: %s", Object_info[i].name);
        cf_WriteString(file, buffer);
      }
    } break;
    }
  }

  cfclose(file);
}

int GetChangeMask() {
  static room *last_curroomp = NULL;
  static int last_curface = -1, last_curportal = -1, last_curobj = -1;
  static char last_name[OBJ_NAME_LEN + 1] = "";

  int mask = 0;

  if (Cur_object_index != last_curobj)
    mask |= KUF_CUROBJ_CHANGED;
  last_curobj = Cur_object_index;

  if (Curroomp != last_curroomp)
    mask |= KUF_CURROOM_CHANGED;
  last_curroomp = Curroomp;

  if (Curface != last_curface)
    mask |= KUF_CURFACE_CHANGED;
  last_curface = Curface;

  if (Curportal != last_curportal)
    mask |= KUF_CURPORTAL_CHANGED;
  last_curportal = Curportal;

  if (Cur_object_index != -1) {
    char *name = Objects[Cur_object_index].name ? Objects[Cur_object_index].name : "<no name>";
    if (strcmp(last_name, name))
      mask |= KUF_CUROBJ_NAME_CHANGED;
    strcpy(last_name, name);
  }

  if (New_mine)
    mask |= KUF_LEVEL_LOADED;

  return mask;
}

// Called from the main idle function
void CMainFrame::OnIdle() {
  // update keypads.
  int mask = GetChangeMask();

  if (m_TextureDialog) {
    m_TextureDialog->UpdateKeypad(mask);
  }
  if (m_ObjectDialog) {
    m_ObjectDialog->UpdateKeypad(mask);
  }
  if (m_LightingDialog) {
    m_LightingDialog->UpdateKeypad(mask);
  }
  if (m_RoomDialog) {
    m_RoomDialog->UpdateKeypad(mask);
  }
  if (m_PathPadDialog) {
    m_PathPadDialog->UpdateKeypad(mask);
  }
  if (m_TriggerDialog) {
    m_TriggerDialog->UpdateKeypad(mask);
  }
  if (m_DoorwayDialog) {
    m_DoorwayDialog->UpdateKeypad(mask);
  }
  if (m_TerrainDialog) {
    m_TerrainDialog->UpdateKeypad(mask);
  }
  if (m_MegacellKeypad) {
    m_MegacellKeypad->UpdateKeypad(mask);
  }
  if (m_LevelDialog) {
    m_LevelDialog->UpdateKeypad(mask);
  }
  if (m_MatcenDialog) {
    m_MatcenDialog->UpdateKeypad(mask);
  }
}

BOOL CMainFrame::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  return CFrameWnd::OnHelpInfo(pHelpInfo);
}

void CMainFrame::OnEditorsMegacells() {
  CMegacellDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void ReorderPages(int);
void CMainFrame::OnReorderPages() {
  if (Network_up == 0) {
    OutrageMessageBox("The network is not up, so this function is unavailable.");
    return;
  }

  int answer = MessageBox("Are you absolutely positively sure you want to do this?  I mean, if you have no idea what "
                          "you are doing (ie, a level designer) then please - don't execute this function.",
                          "EXTREME DANGER - YOU MIGHT DIE", MB_YESNO);

  if (answer == IDNO) {
    OutrageMessageBox("Damn that was close.");
    return;
  }
  ReorderPages(0);

  OutrageMessageBox("Done reordering pages!");
}

void CMainFrame::OnFileImportRoom() {
  // Filter out the curious
  char filename[200];

  CString filter = "Outrage 3dsmax files (*.p3d)|*.p3d||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_room_dir, sizeof(Current_room_dir)))
    return;

  int n = Read3DSMaxFile(filename);

  if (n >= 0) {
    D3EditState.current_room = n;
    State_changed = 1;

    OutrageMessageBox("Room imported and saved locally.\n\nPress OK to check room validity.");
    VerifyRoom(&Rooms[n]);
  }

  theApp.resume();
}

void CMainFrame::OnObjectMovePlayer() { HObjectMoveToViewer(Player_object); }

// Set the editor view mode
void SetViewMode(int view_mode) {
  // Set new view mode
  Editor_view_mode = view_mode;

  // Get the correct viewer (terrain or mine or room)
  SetEditorViewer();

  // Set the correct wireframe view
  if (view_mode == VM_ROOM)
    Wireframe_view = &Wireframe_view_room;
  else if (view_mode == VM_MINE)
    Wireframe_view = &Wireframe_view_mine;

  // Force the windows to update
  AfxGetMainWnd()->Invalidate(TRUE);
  AfxGetMainWnd()->UpdateWindow();
}

void CMainFrame::OnRoomView() { SetViewMode(VM_ROOM); }

void CMainFrame::OnTerrainView() { SetViewMode(VM_TERRAIN); }

void CMainFrame::OnMineView() {
  // Make sure there's a room to switch to
  for (int roomnum = 0; roomnum <= Highest_room_index; roomnum++)
    if (Rooms[roomnum].used && !(Rooms[roomnum].flags & RF_EXTERNAL))
      break;

  if (roomnum > Highest_room_index) {
    OutrageMessageBox("Cannot switch to Mine View: there are no internal rooms.");
    return;
  }

  SetViewMode(VM_MINE);
}

void CMainFrame::OnUpdateMineView(CCmdUI *pCmdUI) {
  // TODO: Add your command update UI handler code here
  pCmdUI->SetRadio(Editor_view_mode == VM_MINE);
}

void CMainFrame::OnUpdateRoomView(CCmdUI *pCmdUI) {
  // TODO: Add your command update UI handler code here
  int start, end, roomnum;
  bool room_loaded = false;

  start = FIRST_PALETTE_ROOM;
  end = start + MAX_PALETTE_ROOMS;

  for (roomnum = start; roomnum < end; roomnum++)
    if (Rooms[roomnum].used) {
      room_loaded = true;
      break;
    }

  if (!room_loaded)
    pCmdUI->Enable(false);
  else {
    pCmdUI->Enable(true);
    pCmdUI->SetRadio(Editor_view_mode == VM_ROOM);
  }
}

void CMainFrame::OnUpdateTerrainView(CCmdUI *pCmdUI) {
  // TODO: Add your command update UI handler code here
  pCmdUI->SetRadio(Editor_view_mode == VM_TERRAIN);
}

void CMainFrame::OnViewNewviewer() { CreateNewViewer(); }

void CMainFrame::OnViewNextviewer() { SelectNextViewer(); }

void CMainFrame::OnViewDeleteviewer() { DeleteViewer(); }

void CMainFrame::OnD3help() {
  // TODO: Add your command handler code here
  WinHelp(HID_GENERAL, HELP_CONTEXT);
}

// void InitScriptEditor(bool level_script=true);

/*
void InitScriptEditor(bool level_script)
{
        int size;
        bool locked=true;
        CScriptEditorDlg editor;

   ASSERT(Current_level_script);

        // Check to see if we even have default script locked
        if ((!level_script) && ((mng_FindTrackLock ("Default.scr",PAGETYPE_GAMEFILE))==-1))
        {
                OutrageMessageBox ("Warning: You are trying to edit the Default script,but it's not locked.  If you want
to save your work, lock first."); locked=false;
        }


        if(strlen(Default_external_editor)==0)
        {
                char buffer[256];
                CString default_path;
                size=GetWindowsDirectory(buffer,256);
                ASSERT(size<256);
                buffer[size]='\\';
                buffer[size+1]='\0';

                default_path=buffer;
                default_path+="Notepad.exe";
                editor.SetExternalEditor(default_path.GetBuffer(1));
        }
        else
        {
                editor.SetExternalEditor(Default_external_editor);
        }

        if(level_script)
        {
                editor.SetScript(Current_level_script, Level_script_prog);
        }
        else
        {
                if(!LoadDefaultScript()) return;
                ASSERT(Default_script);
                editor.SetScript(Default_script, Default_script_prog);
        }


        if(editor.DoModal()==IDOK)
        {
                if(level_script)
                {
                        if(Current_level_script) mem_free(Current_level_script);
                        Current_level_script = (char *) mem_malloc(lstrlen(editor.GetScript())+1);
                        if(Current_level_script)
                                strcpy(Current_level_script,editor.GetScript());
                        else
                                OutrageMessageBox("Couldn't allocate memory to save script!");
                }
                else
                {
                        if(!locked)
                        {
                                OutrageMessageBox("Default script wasn't locked...not saving\n");
                        }
                        else
                        {
                                if(Default_script) mem_free(Default_script);
                                Default_script = (char *) mem_malloc(editor.GetScriptLength());
                                if(Default_script)
                                        strcpy(Default_script,editor.GetScript());
                                else
                                        OutrageMessageBox("Couldn't allocate memory to save script!");
                                OutrageMessageBox("Don't forget to check back in the default script\n");
                        }
                }

                //Try and compile now
                bool exit_ok=false;

                if (!CompileScript(editor.GetScript(), editor.m_Program))
                {
                        OutrageMessageBox("WARNING!!!: Your script did not compile correctly, please fix!");
                        if(editor.DoModal()==IDOK) exit_ok=true;
                }

                //Save the script if the selected Save and Exit
                if(exit_ok)
                {
                        //one last try to compile
                        if (!CompileScript(editor.GetScript(), editor.m_Program))
                        {
                                OutrageMessageBox("WARNING!!!: Your script still did not compile correctly!");
                        }

                        if(level_script)
                        {
                                if(Current_level_script) mem_free(Current_level_script);
                                Current_level_script = (char *) mem_malloc(lstrlen(editor.GetScript())+1);
                                if(Current_level_script)
                                        strcpy(Current_level_script,editor.GetScript());
                                else
                                        OutrageMessageBox("Couldn't allocate memory to save script!");
                        }
                        else
                        {
                                if(!locked)
                                {
                                        OutrageMessageBox("Default script wasn't locked...not saving\n");
                                }
                                else
                                {
                                        if(Default_script) free(Default_script);
                                        Default_script = (char *) mem_malloc(editor.GetScriptLength());
                                        if(Default_script)
                                                strcpy(Default_script,editor.GetScript());
                                        else
                                                OutrageMessageBox("Couldn't allocate memory to save script!");
                                        OutrageMessageBox("Don't forget to check back in the default script\n");
                                }
                        }
                }
        }

        if(strcmp(editor.m_ExternalEditor,Default_external_editor))
        {
                strcpy(Default_external_editor,editor.m_ExternalEditor.GetBuffer(1));
        }

        if(!level_script) SaveDefaultScript(true);

}
*/

// Takes a TGA and extracts the hotspot map and ogf from it
void CMainFrame::OnHotspotTga() {
  // TODO: Add your command handler code here
  CString tga_filter = "TGA (*.tga)|*.tga|All Files (*.*)|*.*||";
  CString tga_path;
  char *buffer;
  int anim = 0, bm_handle;
  char filename[200];

  CFileDialog dlg(true, 0, 0, OFN_FILEMUSTEXIST, (LPCTSTR)tga_filter, this);

  if (dlg.DoModal() == IDOK) {
    tga_path = dlg.GetPathName();
  } else {
    return;
  }

  buffer = (char *)mem_malloc(strlen(tga_path.GetBuffer(1)) + 1);
  if (!buffer) {
    Int3(); // find Jeff
    return;
  }
  strcpy(buffer, tga_path.GetBuffer(1));
  if (menutga_ConvertTGAtoHSM(buffer))
    OutrageMessageBox("HotSpot Map Extracted");

  bm_handle = LoadTextureImage(buffer, &anim, NOT_TEXTURE, 0);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir, GameBitmaps[bm_handle].name);
    bm_SaveFileBitmap(filename, bm_handle);
    bm_FreeBitmap(bm_handle);
  }

  if (buffer)
    mem_free(buffer);
}

void CMainFrame::OnEditorsFiles() {
  CFilePageDialog dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnUpdateEditAttach(CCmdUI *pCmdUI) { pCmdUI->Enable(Placed_group != NULL); }

void CMainFrame::OnUpdateEditSaveScrap(CCmdUI *pCmdUI) { pCmdUI->Enable(Scrap != NULL); }

void CMainFrame::OnFileLevelProps() {
  CLevelDialog dlg(this);

  dlg.DoModal();
}

void CMainFrame::OnObjbutton() {
  if (m_ObjModeless) {
    RECT rect;
    m_ObjModeless->GetWindowRect(&rect);
    GetActiveFrame()->ScreenToClient(&rect);
    D3EditState.objmodeless_x = rect.left;
    D3EditState.objmodeless_y = rect.top;
    D3EditState.objmodeless_on = false;
    m_ObjModeless->DestroyWindow();
    m_ObjModeless = NULL;
  } else {
    m_ObjModeless = new CObjectListModeless(this);
    m_ObjModeless->Create();
    m_ObjModeless->SetWindowPos(this, D3EditState.objmodeless_x, D3EditState.objmodeless_y, -1, -1, SWP_NOSIZE);
    m_ObjModeless->ShowWindow(SW_SHOW);
    D3EditState.objmodeless_on = true;
  }
}

void CMainFrame::OnUpdateObjbutton(CCmdUI *pCmdUI) {
  if (m_ObjModeless && !D3EditState.objmodeless_on) {
    m_ObjModeless = NULL;
  }

  pCmdUI->SetCheck(D3EditState.objmodeless_on);
}

void CMainFrame::OnObjectSetCameraFromViewer() {
  object *objp = &Objects[Cur_object_index];

  if (objp->type != OBJ_CAMERA) {
    OutrageMessageBox("The current object must be a camera for this operation.");
    return;
  }

  ObjSetPos(objp, &Viewer_object->pos, Viewer_object->roomnum, &Viewer_object->orient, false);

  EditorStatus("Camera object %d moved to viewer", Cur_object_index);

  World_changed = 1;
}

void CMainFrame::OnObjectPlaceCameraAtViewer() {
  int objnum;

  objnum = ObjCreate(OBJ_CAMERA, 0, Viewer_object->roomnum, &Viewer_object->pos, &Viewer_object->orient);

  if (objnum == -1) {
    Int3();
    return;
  }

  EditorStatus("Camera created as object %d\n", objnum);

  World_changed = 1;
}

void CMainFrame::OnObjectPlaceCameraAtCurrentFace() {
  vector pos;
  matrix orient;
  int objnum;
  int roomnum;

  ComputeCenterPointOnFace(&pos, Curroomp, Curface);
  vm_VectorAngleToMatrix(&orient, &Curroomp->faces[Curface].normal, 0);

  if (Curroomp->flags & RF_EXTERNAL) {
    roomnum = GetTerrainRoomFromPos(&pos);
  } else {
    roomnum = ROOMNUM(Curroomp);
  }

  objnum = ObjCreate(OBJ_CAMERA, 0, roomnum, &pos, &orient);

  if (objnum == -1) {
    Int3();
    return;
  }

  EditorStatus("Camera created as object %d\n", objnum);

  World_changed = 1;
}

void CMainFrame::OnObjectSetViewerFromCamera() {
  object *objp = &Objects[Cur_object_index];

  if (objp->type != OBJ_CAMERA) {
    OutrageMessageBox("The current object must be a camera for this operation.");
    return;
  }

  MoveViewer(&objp->pos, objp->roomnum, &objp->orient);

  EditorStatus("Viewer moved to object %d", Cur_object_index);

  World_changed = 1;
}

#include "LevelInfoDialog.h"

void CMainFrame::OnFileLevelInfo() {
  CLevelInfoDialog dlg(&Level_info);

  dlg.DoModal();
}

void CMainFrame::OnFileStats() { ShowLevelStats(); }

void CMainFrame::OnFileVerifyLevel() { VerifyMine(); }

void CMainFrame::OnSubEditorsTableFileEdit() {
  // TODO: Add your command handler code here
  CTableFileEdit dlg;

  // theApp.pause();
  dlg.DoModal();
  // theApp.resume();
}

void CMainFrame::OnEditorsAmbientSounds() {
  CAmbientSoundPattern dlg;

  theApp.pause();
  dlg.DoModal();
  theApp.resume();
}

void CMainFrame::OnBriefingEditor() {
  CBriefEdit dlg;
  dlg.DoModal();
  ddio_KeyFlush();
}

void CMainFrame::OnScriptLevelInterface() {
  CScriptLevelInterface dlg;
  dlg.DoModal();
  ddio_KeyFlush();
}

void CMainFrame::OnFileFixCracks() { FixCracks(); }

void CMainFrame::OnViewResetViewRadius() { ResetWireframeViewRad(); }

void CMainFrame::OnSubeditorsTablefilefilter() {
  // TODO: Add your command handler code here
  TableFileFilter dlg;

  dlg.DoModal();
}

void CMainFrame::OnViewShowObjectsInWireframeView() {
  D3EditState.objects_in_wireframe = !D3EditState.objects_in_wireframe;

  State_changed = 1;
}

void CMainFrame::OnUpdateViewShowObjectsInWireframeView(CCmdUI *pCmdUI) {
  pCmdUI->SetCheck((BOOL)D3EditState.objects_in_wireframe);
}

void CMainFrame::OnEditorsDallas() {
  if (theApp.m_DallasModelessDlgPtr == NULL) {
    theApp.m_DallasModelessDlgPtr = new CDallasMainDlg;
    theApp.m_DallasModelessDlgPtr->Create(IDD_DALLAS_MAIN_DIALOG, this);
    theApp.m_DallasModelessDlgPtr->ShowWindow(SW_SHOW);
  } else
    theApp.m_DallasModelessDlgPtr->ShowWindow(SW_RESTORE);
}

void CMainFrame::OnUpdateOsiriscompile(CCmdUI *pCmdUI) {
  // TODO: Add your command update UI handler code here
}

void CMainFrame::OnOsiriscompile() {
  CScriptMassCompile dlg;
  dlg.DoModal();
}

// Copied here from HObject.cpp
#define OBJECT_PLACE_DIST 10.0
bool MoveObject(object *obj, vector *newpos);

void CMainFrame::OnViewMoveCameraToCurrentObject() {
  object *objp = &Objects[Cur_object_index];
  vector pos;
  matrix orient;
  fvi_query fq;
  fvi_info hit_info;

  // Turn the viewer around so facing the object
  orient.fvec = -objp->orient.fvec;
  orient.rvec = -objp->orient.rvec;
  orient.uvec = objp->orient.uvec;

  // Move the viewer to the object
  MoveViewer(&objp->pos, objp->roomnum, &orient);

  // Calculate a position a little in front of the object
  pos = Viewer_object->pos - (Viewer_object->orient.fvec * OBJECT_PLACE_DIST);

  // Follow vector from start position to desired end position, & move as far as we can
  fq.p0 = &Viewer_object->pos;
  fq.startroom = Viewer_object->roomnum;
  fq.p1 = &pos;
  fq.thisobjnum = OBJNUM(Viewer_object);
  fq.ignore_obj_list = NULL;
  fq.flags = 0;
  fq.rad = 0.0;

  fvi_FindIntersection(&fq, &hit_info);

  // Move the viewer to the new position
  MoveViewer(&hit_info.hit_pnt, hit_info.hit_room, NULL);
}

void SelectObject(int objnum);

void CMainFrame::OnObjectSelectByNumber() {
  int n;

  if (InputNumber(&n, "Select Object", "Enter object number to select", this)) {

    if ((n > Highest_object_index) || (Objects[n].type == OBJ_NONE)) {
      OutrageMessageBox("Invalid object number.");
      return;
    }

    SelectObject(n);
  }
}

#include "manage.h"
#define MAX_LOCKLIST_ELEMENTS 1000
extern const char *PageNames[];
extern void dump_text_to_clipboard(char *text);

void CMainFrame::OnShowAllCheckedOut() {
  char text_buf[10000], *t;

  // Get all locked pages
  mngs_Pagelock *LockList = (mngs_Pagelock *)mem_malloc(MAX_LOCKLIST_ELEMENTS * sizeof(mngs_Pagelock));
  int n = mng_GetListOfLocks(LockList, MAX_LOCKLIST_ELEMENTS, NULL);

  // ASSERT(n >= 1);		//always dummy page?
  // ASSERT(!strcmp(LockList[0].name,"DUMMY PAGE"));

  sprintf(text_buf, "Locked pages:\n");
  t = text_buf + strlen(text_buf);
  for (int i = 0; i < n; i++) {
    sprintf(t, "  Type %s, Page = <%s>, Locker = <%s>\n", PageNames[LockList[i].pagetype], LockList[i].name,
            LockList[i].holder);
    t += strlen(t);
    if ((t - text_buf) > (sizeof(text_buf) - 200)) {
      sprintf(t, "Out of buffer space\n");
      break;
    }
  }

  mem_free(LockList);

  dump_text_to_clipboard(text_buf);

  OutrageMessageBox("%d pages are checked out.\n\nThe list has been written to the clipboard.", n);
}

void CMainFrame::OnViewShowViewerForwardVector() {
  EditorStatus("Viewer forward vector: %.3f, %.3f, %.3f", Viewer_object->orient.fvec.x + 0.0005,
               Viewer_object->orient.fvec.y + 0.0005, Viewer_object->orient.fvec.z + 0.0005);
}

void CMainFrame::OnObjectPlaceSoundSourceAtViewer() {
  int objnum;

  objnum = ObjCreate(OBJ_SOUNDSOURCE, 0, Viewer_object->roomnum, &Viewer_object->pos, &Viewer_object->orient);

  if (objnum == -1) {
    Int3();
    return;
  }

  object *objp = &Objects[objnum];
  objp->ctype.soundsource_info.sound_index = -1;
  objp->ctype.soundsource_info.volume = 1.0;

  EditorStatus("SoundSource created as object %d\n", objnum);

  World_changed = 1;
}

#include "OrphanRemoveDlg.h"
void CMainFrame::OnOrphanhunter() {
  COrphanRemoveDlg dlg;
  dlg.DoModal();
}

#include "player.h"

void CMainFrame::OnObjectPlaceWaypointAtViewer() {
  int objnum;
  int count = 0;

  // Count the number of waypoints
  for (int i = 0; i <= Highest_object_index; i++)
    if (Objects[i].type == OBJ_WAYPOINT)
      count++;

  if (count >= MAX_WAYPOINTS) {
    EditorMessageBox("Cannot add waypoint: Already at maximum number of waypoints.");
    return;
  }

  // Check for waypoint already in this room
  if (OBJECT_OUTSIDE(Viewer_object))
    objnum = Terrain_seg[CELLNUM(Viewer_object->roomnum)].objects;
  else
    objnum = Rooms[Viewer_object->roomnum].objects;

  for (objnum = Rooms[Viewer_object->roomnum].objects; objnum != -1; objnum = Objects[objnum].next) {
    if (Objects[objnum].type == OBJ_WAYPOINT) {
      EditorMessageBox("Cannot add waypoint: There's alerady a waypoint in this room (object %d)", objnum);
      return;
    }
  }

  objnum = ObjCreate(OBJ_WAYPOINT, 0, Viewer_object->roomnum, &Viewer_object->pos, &Viewer_object->orient);

  if (objnum == -1) {
    Int3();
    return;
  }

  EditorStatus("Waypoint created as object %d\n", objnum);

  World_changed = 1;
}

#include "levelgoal.h"

// Writes the level goal text to a file for localization
void DumpLevelGoals(char *outname, char *levelname) {
  int n_goals = Level_goals.GetNumGoals();
  char buf[1000];
  CFILE *ofile;

  ofile = cfopen(outname, "wt");

  if (!ofile)
    return;

  cfprintf(ofile, "!/!Level strings for %s\n\n", levelname);

  cfprintf(ofile, "!/!Notes on Localizing This File\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!Line Tokens:\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!  Each non-blank line begins with one of the following tokens that\n");
  cfprintf(ofile, "!/!  identifies it as either a comment or a string in a particular\n");
  cfprintf(ofile, "!/!  language:\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!    !/!  = comment (optional)\n");
  cfprintf(ofile, "!/!    !=!  = English version of string\n");
  cfprintf(ofile, "!/!    !G!  = German version of string\n");
  cfprintf(ofile, "!/!    !S!  = Spanish version of string\n");
  cfprintf(ofile, "!/!    !I!  = Italian version of string\n");
  cfprintf(ofile, "!/!    !F!  = French version of string\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!Rules:\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!  1. There must be an English version of each string.\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!  2. All text when translated should stay very near the\n");
  cfprintf(ofile, "!/!     length of the English version, unless otherwise noted.\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!  3. The maximum length of any line is 1024 characters.\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!  4. All %%s,%%d,%%f and similar tokens MUST stay in the string.\n");
  cfprintf(ofile, "!/!     In the game, these tokens will be replaced by:\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!        %%s  = another string\n");
  cfprintf(ofile, "!/!        %%d  = an integer number\n");
  cfprintf(ofile, "!/!        %%f  = a floating point number (a number with a decimal point)\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!     These tokens MUST stay in the same relative order (i.e. in the\n");
  cfprintf(ofile, "!/!     string \"%%s got %%d points\" the %%s must always come before the %%d).\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!Special Characters:\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!  Special characters can be inserted in strings with the following tokens:\n");
  cfprintf(ofile, "!/!\n");
  cfprintf(ofile, "!/!    \\t  = tab\n");
  cfprintf(ofile, "!/!    \\n  = newline\n");
  cfprintf(ofile, "!/!    \\0 - \\255  = specific ASCII character\n");
  cfprintf(ofile, "\n\n");

  for (int i = 0; i < n_goals; i++) {

    Level_goals.GoalGetName(i, buf, sizeof(buf));
    ASSERT(strlen(buf) < 1024); // localization code can only handle 1024 chars in a string
    cfprintf(ofile, "!/!Goal %d Name\n", i);
    cfprintf(ofile, "!=!%s\n\n", buf);

    Level_goals.GoalGetItemName(i, buf, sizeof(buf));
    ASSERT(strlen(buf) < 1024); // localization code can only handle 1024 chars in a string
    cfprintf(ofile, "!/!Goal %d Item Name\n", i);
    cfprintf(ofile, "!=!%s\n\n", buf);

    Level_goals.GoalGetDesc(i, buf, sizeof(buf));
    ASSERT(strlen(buf) < 1024); // localization code can only handle 1024 chars in a string
    cfprintf(ofile, "!/!Goal %d Description\n", i);
    cfprintf(ofile, "!=!%s\n\n", buf);

    // Level_goals.GoalGetCompletionMessage(i,buf,sizeof(buf));
    // cfprintf(ofile,"!/!Goal %d Completion Message\n",i);
    // cfprintf(ofile,"!=!%s\n\n",buf);
  }

  cfclose(ofile);
}

void CMainFrame::OnFileSaveGoalText() {
  CString path = theApp.main_doc->GetPathName();

  char pathname[_MAX_FNAME], filename[_MAX_FNAME], ext[_MAX_FNAME];
  ddio_SplitPath(path.GetBuffer(0), pathname, filename, ext);
  strcat(pathname, filename);
  strcat(pathname, ".str");
  strcat(filename, ext);

  CFileDialog dlg_open(FALSE, (LPCTSTR) ".str", pathname, 0, NULL, this);
  if (dlg_open.DoModal() == IDCANCEL)
    return;

  DumpLevelGoals(dlg_open.GetPathName().GetBuffer(0), filename);
}

void CMainFrame::OnViewViewprop() {
  if (theApp.m_ViewerPropDlgPtr == NULL) {
    theApp.m_ViewerPropDlgPtr = new CViewerPropDlg;
    theApp.m_ViewerPropDlgPtr->Create(IDD_VIEWER_DIALOG, this);
    theApp.m_ViewerPropDlgPtr->ShowWindow(SW_SHOW);
  } else {
    theApp.m_ViewerPropDlgPtr->DestroyWindow();
  }
}

void CMainFrame::OnUpdateViewViewprop(CCmdUI *pCmdUI) {
  if (theApp.m_ViewerPropDlgPtr == NULL) {
    pCmdUI->SetCheck(0);
  } else {
    pCmdUI->SetCheck(1);
  }
}

void CMainFrame::OnViewMoveCameraToSelectedFace() { SetViewerFromRoomFace(Curroomp, Curface, 0); }

void CMainFrame::OnAccelCopyLightMultiple() {
  extern void CopyFaceLightMultiple(room * rp, int facenum);

  CopyFaceLightMultiple(Curroomp, Curface);
}

void CMainFrame::OnAccelSlidedown() { HTextureSlide(Curroomp, Curface, 0.0f, (float)-1.0 * D3EditState.texscale); }

void CMainFrame::OnAccelSlideleft() { HTextureSlide(Curroomp, Curface, (float)-1.0 * D3EditState.texscale, 0.0f); }

void CMainFrame::OnAccelSlideright() { HTextureSlide(Curroomp, Curface, (float)1.0 * D3EditState.texscale, 0.0f); }

void CMainFrame::OnAccelSlideup() { HTextureSlide(Curroomp, Curface, 0.0f, (float)1.0 * D3EditState.texscale); }

void CMainFrame::OnAccelNextVertex() {
  if (++Curvert >= Curroomp->faces[Curface].num_verts)
    Curvert = 0;

  EditorStatus("Vertex %d (%d) selected.", Curvert, Curroomp->faces[Curface].face_verts[Curvert]);

  State_changed = 1;
}
