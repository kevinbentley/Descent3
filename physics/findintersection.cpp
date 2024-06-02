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

 * $Logfile: /DescentIII/Main/physics/FindIntersection.cpp $
 * $Revision: 231 $
 * $Date: 10/25/99 1:17a $
 * $Author: Chris $
 *
 * Find intersection code
 *
 * $Log: /DescentIII/Main/physics/FindIntersection.cpp $
 *
 * 231   10/25/99 1:17a Chris
 *
 * 230   10/21/99 3:12p Kevin
 * Mac merge & memory savings
 *
 * 229   6/10/99 6:31p Chris
 * Added support for the new editor
 *
 * 228   5/23/99 2:53a Chris
 * Removed annoying asserts
 *
 * 227   5/23/99 12:32a Chris
 * Fixed problems with ignoring render though portals
 *
 * 226   5/20/99 1:16a Chris
 * Fixed the last wall stuck cases
 *
 * 225   5/18/99 11:10a Matt
 * Added variable ceiling height.
 *
 * 224   5/17/99 6:05p Chris
 * Added support for hit faces on a submodel
 *
 * 223   5/17/99 5:01p Matt
 * Changed the code to check for objects in visited rooms whether the
 * vector started on the terrain or inside.  This fixes the problem where
 * the mass driver, when fired from outside, could not hit objects inside.
 *
 * 222   5/12/99 6:16a Chris
 * fvi_QuickDistObjectList if stop at closed doors, it also stops at
 * blocked/forcefielded portals
 *
 * 221   5/09/99 3:07p Jason
 * added a way to track FVI rays
 *
 * 220   5/07/99 6:21p Jeff
 * hooked up fvi to rtperformance
 *
 * 219   5/03/99 3:14p Matt
 * Fixed bug in Chris's hack.
 *
 * 218   5/03/99 1:52p Chris
 * Hacked FVI to make relinking consistant even with level cracks
 *
 * 217   4/20/99 8:14p Chris
 * Added support for object's that hit the ceiling and for making the
 * level always check for the ceiling (inside and outside the mine)
 *
 * 216   4/18/99 5:42a Chris
 * Added the FQ_IGNORE_RENDER_THROUGH_PORTALS flag
 *
 * 215   4/14/99 1:42a Jeff
 * fixed case mismatched #includes
 *
 * 214   4/12/99 10:21a Chris
 * Added another divide by zero assert
 *
 * 213   4/12/99 10:20a Chris
 * Added an assert to catch bad hit obj sizes
 *
 * 212   4/08/99 4:53p Chris
 *
 * 211   4/05/99 3:56p Chris
 * We should be able to pickup clutter now
 *
 * 210   4/02/99 10:18a Chris
 * SPHERE-SPHERE for player rock collisions
 *
 * 209   3/31/99 5:16p Matt
 * Don't look at non-shell faces when determining what room a point is in
 *
 * 208   3/09/99 10:52a Chris
 * Fix a bug introduced when trying to to fix the trigger problems
 *
 * 207   3/05/99 1:02p Jason
 * sped up raycasting for light coronas
 *
 * 206   3/04/99 8:15p Matt
 * Hack that might help the exit level trigger problem on OEM level 0.
 *
 * 205   3/04/99 5:54p Chris
 * Patched the occassional not found portal trigger
 *
 * 204   2/25/99 1:54p Chris
 * Ignoring weapons now ignores shockwaves, shards, and fireballs
 *
 * 203   2/16/99 3:09p Chris
 *
 * 202   2/16/99 1:51p Chris
 * FIxed multiple trigger bugs
 *
 * 201   2/15/99 4:38p Chris
 * Damn...  Lava was hitting triggers!!!!!!
 *
 * 200   2/15/99 11:47a Chris
 *
 * 199   2/11/99 6:25p Chris
 * Added PF_NO_COLLIDE_DOORS
 *
 * 198   2/02/99 8:44a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 197   1/29/99 5:09p Chris
 * Made changes for ROCKS
 *
 * 196   1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 195   1/18/99 8:07p Chris
 * Added the no-collide same flag (for flocks and nests)
 *
 * 194   1/18/99 2:46p Matt
 * Combined flags & flags2 fields in object struct
 *
 * 193   1/15/99 5:59p Chris
 *
 * 192   1/13/99 6:54a Jeff
 * fixed #includes for linux
 *
 * 191   1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 190   1/01/99 4:53p Chris
 * Fixed a problem with long-rays causing unneccessary asserts
 *
 * 189   1/01/99 4:10p Chris
 * Added some const parameters, improved ray cast object collide/rejection
 * code
 *
 * 188   11/23/98 11:06a Chris
 * Added support for finding just AIs and Players with
 * fvi_QuickDistObjectList
 *
 * 187   11/02/98 6:15p Chris
 * Room AABBs get saved with the level and the sort_face and dec_sort_face
 * list s have been removed
 *
 * 186   10/29/98 5:20p Chris
 * Player ships collide smaller now
 *
 * 185   10/22/98 10:25p Kevin
 * took out volatile
 *
 * 184   10/22/98 10:25p Chris
 * Fixed a major bug with fvi_QuickXList()  -- preincrement f@cked me.
 *
 * 183   10/22/98 9:46p Chris
 *
 * 182   10/22/98 9:45p Chris
 * Added some asserts
 *
 * 181   10/21/98 9:41p Chris
 * Improved walking code!
 *
 * 180   10/21/98 7:44a Chris
 * Tweaked player wall collisions
 *
 * 179   10/20/98 8:05p Sean
 * Fixes callers with a start room of -1
 *
 * 178   10/20/98 6:58p Chris
 * My god - improved the cylinder code.  :)
 *
 * 177   10/18/98 5:36p Chris
 *
 * 176   10/17/98 12:25p Chris
 * Fixed attached flares
 *
 * 175   10/16/98 8:33p Chris
 * Fixed attached flare problem
 *
 * 174   10/16/98 6:19p Chris
 * More linked object fixes
 *
 * 173   10/16/98 12:27a Chris
 * Improved collision code.  Finish it tomarrow.
 *
 * 172   10/15/98 12:22a Matt
 * Fixed compile warnings
 *
 * 171   9/22/98 6:42p Dan
 * Temp fix
 *
 * 170   9/22/98 12:02p Matt
 * Fixed compile warnings
 *
 * 169   9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 168   8/28/98 4:33p Chris
 *
 * 167   8/17/98 3:14p Chris
 * Fixed a bug with the FQ_IGNORE_WALLS flag that caused precomputed
 * weapons not to relink into the mine from the terrain.
 *
 * 166   8/03/98 3:59p Chris
 * Added support for FQ_IGNORE_WEAPONS, added .000001 attach code, fix a
 * bug in polymodel collision detection
 *
 * 165   7/31/98 11:52a Chris
 * Weapons can be persistent.  Added ability for objects to be manually
 * set for no object collisions.
 *
 * 164   7/23/98 4:08p Chris
 *
 * 163   7/23/98 12:46p Chris
 * Added a flag to ignore external rooms
 *
 * 162   7/23/98 12:31p Chris
 *
 * 161   7/22/98 6:48p Chris
 *
 * 160   7/22/98 6:42p Chris
 * A relink fix for points on a wall
 *
 * 159   7/22/98 2:31p Chris
 * Fixed an odd bug with objects moving farther than a long ray externally
 * (never happened until I did the weapon pre-compute stuff)
 *
 * 158   7/21/98 2:14p Chris
 * Some FVI speedups - not done
 *
 * 157   7/17/98 9:56a Chris
 * Intermediate checkin
 *
 * 156   7/16/98 8:29p Chris
 * Partial implementation of the new collide code
 *
 * 155   7/02/98 2:51p Chris
 * Added a fast line to bbox function
 *
 * 154   6/15/98 6:08p Chris
 * Hit_type to hit_type[0]
 *
 * 153   6/15/98 6:58a Chris
 * Comment'ed out most bbox related additions
 *
 * 152   6/03/98 6:50p Chris
 * Fixed some infinity bugs
 *
 * 151   6/03/98 6:42p Chris
 * Added multipoint collision detection an Assert on invalid (infinite
 * endpoint).
 *
 * 150   6/03/98 12:34p Chris
 * Fixed a potential bug in subdivided rays
 *
 * 149   6/01/98 9:23p Chris
 * Removed a mprintf
 *
 * 148   6/01/98 9:23p Chris
 * Fixed a bunch of collision problems
 *
 * 147   6/01/98 11:38a Chris
 * Made FQ_SOLID_PORTALS more effective
 *
 * 146   5/26/98 10:45a Keneta
 * Shockwaves should not collide with anything
 *
 * 145   5/22/98 2:42p Sean
 * FROM JASON:Upped max next portals to 50
 *
 * 144   5/20/98 1:46p Chris
 * Fixed a bug in QuickDistFaceList
 *
 * 143   5/18/98 11:59a Chris
 *
 * 142   5/05/98 5:23p Chris
 * Faster external room collisions with FQ_EXTERNAL_ROOMS_AS_SPHERE
 *
 * 141   5/04/98 10:17a Chris
 * Improved checking
 *
 * 140   5/04/98 9:40a Chris
 * Improved Physics_player_verbose stuff
 *
 * 139   5/04/98 12:16a Chris
 * More debugging
 *
 * 138   5/03/98 10:59p Chris
 * Fixed problems with external rooms
 *
 * 137   5/03/98 8:36p Chris
 * Additional debug info
 *
 * 136   4/23/98 5:58p Chris
 * OOps.
 *
 * 135   4/23/98 5:44p Chris
 * Working on Door collisions
 *
 * 134   4/20/98 6:56p Chris
 * Removed sphere check for poly2sphere (just AABB)
 *
 * 133   4/20/98 5:48p Chris
 * Patching a collision bug
 *
 * 132   4/13/98 5:34p Chris
 * Sped up fvi.  check_hit_objs is not called at all for fvi calls with
 * FQ_CHECK_OBJS set
 *
 * 131   4/13/98 4:41p Chris
 *
 * 130   4/13/98 3:51p Chris
 * Added sphere bubbles to weapons (when wanted)  and fixed a small FVI
 * bug
 *
 * 129   4/13/98 2:21p Chris
 * Fixed some collision problems dealing with AABBs and Polymodel paging
 * in.
 *
 * 128   4/09/98 12:05p Chris
 * Added parenting for all object types.  :)
 *
 * 127   4/08/98 7:38p Chris
 *
 * 126   4/08/98 2:38p Chris
 * Fixed powerup pickup bug
 *
 * 125   4/07/98 8:14p Chris
 * Made powerups easier to hit
 *
 * 124   4/06/98 4:09p Chris
 * Made f_correcting a bool -- NOTE: chrishack -- physics need to handle
 * powerups in a good manner (flying through them).
 *
 * 123   4/06/98 2:54p Chris
 * TEMPORARY FIX -- Object collisions are of less priority than wall
 * collisions -- keep this until we have multipoint collision detection --
 * chrishack
 *
 * 122   4/03/98 3:35p Chris
 * Fixed problems with FQ_LIGHTMAP_ONLY (has to include external rooms)
 *
 * 121   4/03/98 11:27a Chris
 * Doubled the size of powerups
 *
 * 120   4/01/98 3:51p Chris
 *
 * 119   4/01/98 3:46p Chris
 * Added hack for powerups and players
 *
 * 118   3/25/98 1:17p Chris
 * Removed a bug.
 *
 * 117   3/24/98 2:57p Chris
 * Fixed a bug in the QuickDistObjectList function
 *
 * 116   3/23/98 11:37a Chris
 * Added the f_lightmap_only parameter to fvi_QuickDistObjectList
 *
 * 115   3/23/98 11:18a Chris
 * Added int fvi_QuickDistObjectList(vector *pos, int init_room_index,
 * float rad, int16_t *object_index_list, int max_elements)
 *
 *
 * 114   3/18/98 10:12p Chris
 * Added some more bug checking.  If 2 objects radii add up to zero, then
 * let me know.  :)
 *
 * 113   3/18/98 5:01p Chris
 * Fixed a bug with the zero rad wall collision code
 *
 * 112   3/18/98 4:50p Chris
 * Added a speed opt. for zero radius wall collision objects
 *
 * 111   3/18/98 4:31p Chris
 * Speed up fvi and fixed some bugs
 *
 * 110   3/17/98 3:36p Chris
 * Fixed bugs in the relink code and the QuickDistFaceList code.  (They
 * where using fvi_max_xyz and fvi_min_xyz)
 *
 * 109   3/17/98 11:33a Chris
 * Improved performance (AABB updates on poly-sphere collide)
 *
 * 108   3/16/98 9:55p Chris
 * Working on optimizing fvi
 *
 * 107   3/16/98 8:25p Chris
 * Fixed bugs with the new fvi code
 *
 * 106   3/16/98 6:55p Chris
 * Temporary fix.  There is a problem somewhere in the new optimazations.
 *
 * 105   3/16/98 5:50p Chris
 * Added sorted face lists for fvi
 *
 * 104   3/16/98 2:52p Chris
 * Moved some asserts for FQ_NO_RELINK
 *
 * 103   3/16/98 1:13p Chris
 * Speed up
 *
 * 102   3/16/98 12:50p Chris
 * Speed up?
 *
 * 101   3/16/98 9:46a Chris
 * Improved the speed
 *
 * 100   3/16/98 9:43a Chris
 * Added FQ_NO_RELINK
 *
 * 99    3/16/98 9:25a Chris
 * Sped up fvi
 *
 * 98    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 97    2/23/98 6:50p Jason
 * changes to help facilitate fast lighting with shadow volumes
 *
 *
 * 96    2/20/98 1:45p Chris
 * Milestone fixes
 *
 * 95    2/19/98 6:17p Chris
 * Added some debug info
 *
 * 94    2/15/98 2:08p Chris
 *
 * 93    2/12/98 2:07p Chris
 * Fixed the trigger face list
 *
 * 92    2/11/98 10:04p Chris
 * Added FQ_ONLY_DOOR_OBJ and fixed a bug with FQ_ONLY_PLAYER_OBJ
 *
 * 91    2/10/98 2:45p Chris
 * Made objects not get checked if FQ_CHECK_OBJECTS is not set.
 * (OBJ_ROOMS are still checked)
 *
 * 90    2/10/98 2:41p Chris
 * Fixed a problem with large objects beening hit when they shouldn't
 *
 * 89    2/06/98 3:47p Brent
 * CHRIS -- I made the MAX_CELLS_VISITED equal to the number of cells on
 * the terrain.  This is insane, but it allows for the placement of HUGE
 * objects.  :)  -- Thanx Brent.
 *
 * 88    2/06/98 2:57a Chris
 * Added point_collide_with_walls and ignore_robot_collisions
 *
 * 87    2/05/98 1:58p Chris
 * Made the cellnum be a roomnum for hitting terrain
 *
 * 86    2/04/98 6:23p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 85    2/02/98 8:19p Chris
 * Fixed the hung on wall problem and the powerup problem.
 *
 * 84    1/29/98 5:50p Matt
 * Changed old camera object type to be viewer object (for editor), and
 * now camera objects will just be for game cameras.
 *
 * 83    1/20/98 12:25p Luke
 * CHRIS-- Added a check to make sure that the startseg is not an external
 * room
 *
 * 82    1/20/98 12:22p Chris
 * Removed the attempting to patch mprintf
 *
 * 81    1/19/98 5:05p Chris
 * Added ceiling collisions for players and powerups
 *
 * 80    1/14/98 7:56p Jason
 * don't do obj relink if you're in the same room
 *
 * 79    1/07/98 4:11p Jason
 * CHRIS -- Fixed stupid mistake with edge fix -- .y values where getting
 * misassigned.
 *
 * 78    1/06/98 7:14p Chris
 * Made edge of world less dangerous
 *
 * 77    12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 76    12/18/97 12:25p Chris
 * Sub-divide long rays and use a better flat-line algorithm for the
 * terrain fvi.
 *
 * 75    12/16/97 6:11p Chris
 * Attempt to improve FVI for outside
 *
 * 74    12/03/97 2:36p Sean
 * Added another code fix for external room problems
 *
 * 73    11/24/97 11:41a Chris
 * Fixed a small glitch in the fvi_check_node stuff
 *
 * 72    11/24/97 11:01a Chris
 * Removed a debugging assert
 *
 * 71    11/24/97 10:15a Chris
 * Improved fvi
 *
 * 70    11/21/97 5:26p Jason
 * checked in so chris can find a bug
 *
 * 68    11/20/97 6:02p Chris
 * Fixed the quick cell list code
 *
 * 67    11/17/97 5:46p Chris
 * Fixed a problem in line_to_sphere1 it -- see history for diff.
 *
 * 66    11/11/97 8:39p Chris
 * Passed the wrong object to PolyCollide when doing the relative motion
 * mapping of polygon moving and hitting a sphere.
 *
 * 65    11/11/97 11:26a Sean
 * CHRIS -- increased MAX_NEXT_PORTALS.  It seems that radiosity rays can
 * cross a lot of portals in a single room (in this case it was over 5)...
 * Beefed it up to 20.  It that causes a problem, it can be beefed up more
 * without any disadvantage.
 *
 * 64    11/03/97 5:10p Jason
 * Fixed by Chris, forgot to assume fvi_terrain_obj_visit_list to the max
 * cells visited limit.
 *
 * 63    10/29/97 3:39p Matt
 * Got rid of compiler warning
 *
 * 62    10/28/97 5:46p Chris
 * Added a quick cell list function
 *
 * 61    10/28/97 12:20p Chris
 * Added support to ignore wall collisions
 *
 * 60    10/22/97 4:33p Chris
 * Improved default hit_obj_type collision types (i.e. when the ray is
 * cast with a -1 as its index)
 *
 * 59    10/22/97 4:30p Chris
 * We can now slew between the mine and the terrain
 *
 * 58    10/22/97 12:42p Chris
 * Incremental BBOX stuff and added support for subobject hit returned
 * from fvi
 *
 * 57    10/21/97 4:14p Chris
 * Incremental improvements to the fvi/physics/collide integration
 *
 * 56    10/20/97 3:51p Chris
 * Fixed a problem with the POLY_BBOX collide code
 *
 * 55    10/20/97 3:43p Chris
 * Added more collide code
 *
 * 54    10/20/97 11:55a Chris
 * Added some support for the new collide system.
 *
 * 53    10/15/97 5:08p Chris
 * Fixed the collision_side_pnt and added a relative position/velocity
 * check
 *
 * 52    10/14/97 6:56p Chris
 * In middle of some incremental improvements
 *
 * 51    10/07/97 3:51p Chris
 * Added support for object backface checking -- external rooms are
 * classified as objects
 *
 * 50    10/06/97 2:36p Chris
 * Improved and fixed fvi.
 *
 * 49    10/06/97 12:36p Chris
 * Intermediate fix for terrain rendering problems
 *
 * 48    10/06/97 10:52a Jason
 * added "FQ_IGNORE_NON_LIGHTMAP_OBJECTS" flag
 *
 * 47    10/05/97 6:14a Chris
 * Added terrain speedup.  Allowed poly-collision for weapons.
 *
 * 46    10/03/97 6:24p Chris
 * Corrected a mistype to disallow all camera collisions
 *
 * 45    10/03/97 3:34p Chris
 * No camera collisions
 *
 * 44    10/02/97 7:02p Chris
 * Removed LOD optimazation
 *
 * 43    10/02/97 6:44p Chris
 * Added support for quick fvi_checks
 *
 * 42    10/02/97 5:38p Chris
 * Added support for invisible terrain tiles
 *
 * 41    10/02/97 11:34a Chris
 * Added support for external room collisions
 *
 * 40    9/19/97 6:58p Chris
 * Fixed some bugs with the big object system and removed some annoying
 * mprintf's
 *
 * 39    9/19/97 4:56p Jason
 * FROM CHRIS: Took out clutter assert in check_hit_obj
 *
 * 38    9/19/97 1:01p Chris
 * Added better large object support
 *
 * 37    9/17/97 3:24p Chris
 *
 * 36    9/17/97 11:01a Chris
 * Working on poly collision code (not done) and removed dependance on
 * segment.h
 *
 * 35    9/15/97 6:24p Chris
 * Added a second chance check if no rooms are initialy found
 *
 * 34    9/15/97 4:43p Craig
 *
 * 33    9/15/97 5:20a Chris
 * Added sphere2poly support.  Rearranged object collisions.
 *
 * 32    9/12/97 6:36p Chris
 * Added collision terrain segment support
 * Added some LARGE OBJECT collision support
 *
 * 31    9/12/97 10:37a Chris
 * Added a zero radius speed up for fvi terrain.
 *
 * 30    9/11/97 7:08p Matt
 * Fixed minor bug
 *
 * 29    9/11/97 3:10p Chris
 *
 * 28    9/11/97 3:08p Chris
 * Added support for weapons flying through holes in transparent textures.
 *
 * 27    9/11/97 1:58p Chris
 * Added ability to ignore moving objects
 *
 * 26    9/11/97 12:43p Chris
 * Added new support for face_physics_info from room.h.  Also, changed how
 * we detect portals.  Also added recorded faces.
 *
 * 25    9/10/97 11:58a Matt
 * Ripped out some unused commented-out code
 *
 * 24    9/02/97 6:32p Jason
 * Fixed fvi_rooms_visited array in the quick face list code.
 *
 * 23    9/02/97 4:16p Chris
 * Fixed the 'clockwise' vertices problem with backface checking.  I.e.
 * vertices should be oppositely ordered when negating the face normal.
 *
 * 22    9/02/97 3:06p Chris
 * Fixed stupid bug
 *
 * 21    9/02/97 3:04p Chris
 * Fixed quick face list bug
 *
 * 20    9/02/97 11:57a Chris
 * Fix a bug in the quick_dist stuff
 *
 * 19    9/02/97 11:41a Chris
 * Added support the the quick face/room from distance function
 *
 * 18    8/26/97 1:44p Chris
 * Fixed a bug in the clipping of a vector to the terrain boundaries.
 *
 * 17    8/25/97 6:21p Chris
 * Portals only crossed at centerpoint
 *
 * 16    8/20/97 3:16p Chris
 * Working on the edge of terrain problems
 *
 * 15    8/18/97 1:48a Chris
 * Added AABB speedups.  Added a new way to do inter-room and mine-terrain
 * movements.  Added a fvi_relink that correctly uses the hit_seg
 * FVIF_OUTSIDE flag
 *
 * 14    8/12/97 3:47p Chris
 * Updated the AABB stuff.
 *
 * 13    8/12/97 1:13p Chris
 * Added AABBs.
 *
 * 12    8/11/97 5:49p Chris
 * Allow for some terrain to mine flights
 *
 * 11    8/05/97 4:43p Chris
 * Added support for fly by textures.  Added support (fly by) support for
 * fly thru textures.
 *
 * 10    8/04/97 5:35p Chris
 * Added support for back face collisions and new fvi code
 *
 * 9     8/04/97 12:37p Chris
 * We now support fvi in Rooms  :)
 *
 * 8     7/31/97 3:12p Chris
 * Fixed a problem with the new iterator based radius checker
 *
 * 7     7/28/97 1:16p Chris
 * Allow for player and robots to be hit by weapons and correct parenting
 * of weapons.
 *
 * 6     7/23/97 6:27p Jason
 * added code to support terrain simplification
 *
 * 5     7/23/97 5:14p Chris
 * Used a faster iterator for visiting terrain segments
 *
 * 4     7/15/97 7:29p Chris
 * Added a sound for helicopter blades.
 *
 * 3     7/15/97 5:35p Chris
 * New AI code
 *
 * 39    6/24/97 4:01p Chris
 * Fixed another problem with the .y dependancy.
 *
 * 38    6/24/97 3:53p Chris
 * Fixed a bug with the new .y dependancy
 *
 * 37    6/24/97 3:29p Chris
 * Removed the .pos dependancy for terrain and am using the .y instead
 *
 * 36    6/18/97 3:52p Chris
 *
 * 35    6/12/97 2:40p Chris
 *
 * 34    6/10/97 6:23p Chris
 *
 * 33    6/10/97 5:32p Chris
 *
 * 32    6/10/97 5:32p Chris
 *
 * 31    6/05/97 7:22p Matt
 * When get list of faces for mesh side, return the normals for each face.
 * Also, added a function to return the four floating verts in a side.
 *
 * 30    5/27/97 5:36p Chris
 *
 * 29    5/27/97 5:36p Chris
 * Incremental.
 *
 * 28    5/27/97 5:05p Chris
 * Added physics for floating segments.  We need more
 * code if all mesh faces get their own normals or if mesh sides are used
 * for non-floating other sides.
 *
 * 27    5/13/97 5:52p Chris
 * Added ability to exit and enter mine.  Also did some
 * incremental improvements.
 *
 * 26    5/06/97 11:18a Chris
 *
 * 25    5/05/97 5:41a Chris
 * Added some better polygon collision code.  It is still rough though.
 *
 * 24    4/17/97 3:10p Chris
 * Added edge of world object delete.  Also did some incremental
 * improvements.
 *
 * 23    4/16/97 3:25p Chris
 * Commented the code
 *
 * 22    4/16/97 1:39p Chris
 *
 * 21    4/15/97 6:31p Chris
 * Added support for self-correcting and non-correcting
 * sphere collisions.  This allows objects to ignore sphere
 * collisions that happen at initial positions, but allows the walls to
 * self-correct edges.
 *
 * 20    4/15/97 4:13p Chris
 *
 * 19    4/11/97 3:05a Chris
 * Added some terrain collision code.  Need ground.
 *
 * 18    3/24/97 6:29p Chris
 *
 * 17    3/24/97 3:50p Chris
 * Removed some annoying, but informative physics info.
 *
 * 16    3/24/97 3:27p Chris
 * Fixed some corner problems
 *
 * 15    3/24/97 11:43a Chris
 *
 * 14    3/21/97 7:08p Chris
 * Working on rewritting FVI and Physics
 *
 * 13    3/20/97 6:26p Chris
 *
 * 12    3/20/97 6:18p Chris
 *
 * 11    3/20/97 6:13p Chris
 *
 * 10    3/20/97 6:06p Chris
 *
 * 9     3/17/97 7:36p Chris
 * Made it easier to hit objects...  :)
 *
 * 8     3/17/97 11:55a Chris
 * Added more debug info.
 *
 * 7     3/14/97 12:18p Chris
 * Tweak physics and remove braking for now.
 *
 * 6     3/13/97 1:17p Chris
 * Incremental improvements...
 *
 * 5     3/12/97 6:31p Chris
 * Alpha 1.0 of player "flying" in the mine
 *
 * 4     3/07/97 7:01p Chris
 * Segments now have perfect edges and corners  :)
 *
 * 3     3/03/97 1:03p Chris
 *
 * 2     3/03/97 5:52a Chris
 * Pre-alpha .01
 *
 * 1     3/03/97 3:25a Chris
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mono.h"
#include "findintersection.h"
#include "pserror.h"
#include "collide.h"
#include "terrain.h"
// #include "bspfi.h"
#include "3d.h"
#include "room.h"
#include "descent.h"
#include "weapon.h"

#ifndef NED_PHYSICS
#include "gametexture.h"
#else
#include "..\neweditor\ned_GameTexture.h"
#endif

#include "BOA.h"
#include "polymodel.h"
#include "physics.h"
#include "player.h"
#include "doorway.h"
#include "renderer.h"

// Debug performance includes (do nothing in final release)
#ifndef NED_PHYSICS
#include "rtperformance.h"
#endif

int FVI_counter;
int FVI_room_counter;

//------------------------------------------------------------------------------------------
// Defines and globals for fvi_FindIntersection
//------------------------------------------------------------------------------------------

#define MAX_CELLS_VISITED (TERRAIN_DEPTH * TERRAIN_WIDTH) // Maximum terrain cells visited in one fvi call

bool FVI_always_check_ceiling = false;

// This doesn't really belong here, but I don't know where else to put it.
float Ceiling_height = MAX_TERRAIN_HEIGHT;

// Bit fields for quick 'already-checked' checking
static uint8_t
    fvi_visit_list[MAX_ROOMS / 8 + 1]; // This bit-field provides a fast check if a mine segment has been visited
static uint8_t
    fvi_terrain_visit_list[(TERRAIN_DEPTH * TERRAIN_WIDTH) / 8 +
                           1]; // This bit-field provides a fast check if a terrain segment has been visited
static uint8_t
    fvi_terrain_obj_visit_list[(TERRAIN_DEPTH * TERRAIN_WIDTH) / 8 +
                               1]; // This bit-field provides a fast check if a terrain segment has been visited

// The number rooms and terrain cells that this fvi call visited.
static int fvi_num_rooms_visited;
static int fvi_num_cells_visited;
static int fvi_num_cells_obj_visited;

// Should we do a terrain check.  This flag exists because if we do a terrain check, it always does a full check. So,
// we only have to do it once.
static bool f_check_terrain;
static bool fvi_zero_rad;

// Unordered list of rooms and terrain cells that this fvi call visited.
// DAJ changed to ushorts to save memory
static uint16_t fvi_rooms_visited[MAX_ROOMS];         // This should be a small number (100 to 1000)
static uint16_t fvi_cells_visited[MAX_CELLS_VISITED]; // Use this so that we do not have to use 256x256 elements
static uint16_t fvi_cells_obj_visited[MAX_CELLS_VISITED];

// Fvi wall collision stuff
static float fvi_wall_sphere_rad;
static vector fvi_wall_sphere_offset;
static vector fvi_wall_sphere_p0;
static vector fvi_wall_sphere_p1;

static float fvi_anim_sphere_rad;
static vector fvi_anim_sphere_offset;
static vector fvi_anim_sphere_p0;
static vector fvi_anim_sphere_p1;

// Fvi information pointers.
fvi_info *fvi_hit_data_ptr;
fvi_query *fvi_query_ptr;

// Best collision's distance
float fvi_collision_dist;

// AABB for the movement
static vector fvi_max_xyz;
static vector fvi_min_xyz;
static vector fvi_movement_delta;

// AABB for the movement
static vector fvi_wall_max_xyz;
static vector fvi_wall_min_xyz;

// CHRISHACK -- Do we still need this????
int fvi_curobj;
int fvi_moveobj;

// Recorded faces
fvi_face_room_list Fvi_recorded_faces[MAX_RECORDED_FACES];
int Fvi_num_recorded_faces = 0;

//------------------------------------------------------------------------------------------
// Some function def's
//------------------------------------------------------------------------------------------

static int do_fvi_terrain();
static int fvi_room(int room_index, int from_portal, int room_obj = -1);
static void do_fvi_rooms(int initial_room_index);
/// Find the point on the specified plane where the line intersects.
/// - returns: true if point found, false if line parallel to plane.
/// - parameter new_pnt: is the found point on the plane.
/// - parameter plane_pnt: describe the plane.
/// - parameter plane_norm: describe the plane.
/// - parameter p0: are the ends of the line.
/// - parameter p1: are the ends of the line.
///
/// Assumes that the initial point is not intersecting the plane.
static inline int find_plane_line_intersection(vector *intp, vector *colp, vector *plane_pnt, const vector *plane_norm,
                                               const vector *p0, const vector *p1, float rad);
static bool IsPointInCylinder(vector *normal, vector *cylinder_pnt, vector *edir, float elen, const float rad,
                              const vector *pnt, vector *mdir, bool *f_collide);

//! check if a sphere intersects a face -- this can be optimized (only need 2d stuff after rotation)
static int check_vector_to_cylinder(vector *colp, vector *intp, float *col_dist, vector *wall_norm, const vector *p0,
                                    const vector *p1, float rad, vector *ep0, vector *ep1);

//! check if a sphere intersects a face.
static int check_sphere_to_face(vector *colp, vector *intp, float *col_dist, vector *wall_norm, const vector *p0,
                                const vector *p1, vector *face_normal, int nv, float rad, vector **vertex_ptr_list);
static void fvi_rooms_objs(void);
static int obj_in_list(int objnum, int *obj_list);
static void make_trigger_face_list(int last_sim_faces);
static bool PhysPastPortal(const room *rp, portal *pp);

//------------------------------------------------------------------------------------------
// FVI FUNCTIONS
//------------------------------------------------------------------------------------------

void InitFVI(void) {
  memset(fvi_terrain_visit_list, 0, (TERRAIN_DEPTH * TERRAIN_WIDTH) / 8 + 1);
  memset(fvi_terrain_obj_visit_list, 0, (TERRAIN_DEPTH * TERRAIN_WIDTH) / 8 + 1);
  memset(fvi_visit_list, 0, MAX_ROOMS / 8 + 1);
}

// find the point on the specified plane where the line intersects
// returns true if point found, false if line parallel to plane
// new_pnt is the found point on the plane
// plane_pnt & plane_norm describe the plane
// p0 & p1 are the ends of the line
// Assumes that the initial point is not intersecting the plane
inline int find_plane_line_intersection(vector *intp, vector *colp, vector *plane_pnt, const vector *plane_norm,
                                        const vector *p0, const vector *p1, float rad) {
  vector line_vec;             // Vector from p0 to p1
  vector point_plane_vec;      // Vector from p0 to a point on the plane
  float proj_dist_line;        // Distance projection of line onto the plane normal
  float proj_dist_point_plane; // Distance of the object from the plane

  ASSERT(intp != NULL && plane_pnt != NULL && colp != NULL && plane_norm != NULL && p0 != NULL && p1 != NULL &&
         rad >= 0.0);

  // Line direction
  line_vec = *p1 - *p0;

  // Compute the distance to the plane and the distance the line travels in the direction of the normal
  // Negative because if the object is moving toward the plane, it is moving in the opposite direction of the normal
  proj_dist_line = (*plane_norm * line_vec);
  if (proj_dist_line >= 0.0f)
    return 0;

  //  Vector from p0 to a point on the plane
  point_plane_vec = *plane_pnt - *p0;
  proj_dist_point_plane = (*plane_norm * point_plane_vec);

  // Throw out any sphere who's centerpoint is initially behind the face
  if (proj_dist_point_plane > 0.0)
    return 0;

  // Use the distance from the edge of the sphere to the plane.  If the new proj_dist_point_plane is
  // negative, then the sphere pokes thru the edge at the initial position
  proj_dist_point_plane += rad;

  if (proj_dist_point_plane > 0.0 && proj_dist_line < 0.0) {
    *intp = *p0;
    *colp = *intp + *plane_norm * (-rad + proj_dist_point_plane);

    return 1;
  }

  // cannot intersect wall if we are more than a rad away (closest point check)
  if (proj_dist_point_plane <= proj_dist_line) {
    return 0;
  }

  // If we are moving almost parallal to the plane, then make sure we are a rad away form it
  // I picked .00000001 from my head.  It would be pretty parallel of a pretty short movement and
  // the linear combination below might not product a nice answer
  if (fabs(proj_dist_line) <= 0.00000000001) {
    float plane_dist;

    plane_dist = (*p1 - *plane_pnt) * *plane_norm;
    if (plane_dist >= rad)
      return 0;

    *intp = *p1 + (rad - plane_dist) * (*plane_norm);

    // Make sure the computed new position is not behind the wall.
    ASSERT((*intp - *plane_pnt) * *plane_norm >= -0.01);

  } else {
    // The intersection of the line and the plane is a simple linear combination
    *intp = *p0 + (proj_dist_point_plane / proj_dist_line) * line_vec;
  }

  // Make sure the computed new position is not colliding with the wall.
  //	ASSERT((*intp - *plane_pnt) * *plane_norm >= rad);

  // Collision point is a rad. closer in the direction of the normal
  *colp = *intp + *plane_norm * -rad;

  return 1;
}

struct vec2d {
  float i, j;
};

// given largest componant of normal, return i & j
// if largest componant is negative, swap i & j
static const int ij_table[3][2] = {
    {2, 1}, // pos x biggest
    {0, 2}, // pos y biggest
    {1, 0}, // pos z biggest
};

// intersection types
#define IT_NONE 0  // doesn't touch face at all
#define IT_FACE 1  // touches face
#define IT_EDGE 2  // touches edge of face
#define IT_POINT 3 // touches vertex

// see if a point in inside a face by projecting into 2d
uint32_t check_point_to_face(vector *colp, vector *face_normal, int nv, vector **vertex_ptr_list) {
  vector_array *colp_array; // Axis-independant version of the collision point
  vector_array *norm;       // Axis-independant version of the plane's normal
  vector t;                 // Temporary vector that holds the magnatude of the normal's x,y,z components (ABS)
  int biggest;              // Index of the largest of the three components (0-x, 1-y, 2-z)  Axis to ignore :)
  int i, j, edge;           // Index for i-axis, Index for j-axis, and the current edge
  uint32_t edgemask;            // Bit-field for which side we are outside of
  float check_i, check_j;   // (i,j) checkpoint for 2d in/out test
  vector_array *v0, *v1;    // Vertices of the current line segment in the 2d in/out check loop

  // Lets look at these vectors as arrays :)
  norm = (vector_array *)face_normal;
  colp_array = (vector_array *)colp;

  // now do 2d check to see if point is in side

  // Get x,y,z components of the normal and put them in array form (so we can pick any two for i,j)
  t.x = fabs(norm->xyz[0]);
  t.y = fabs(norm->xyz[1]);
  t.z = fabs(norm->xyz[2]);

  // Determine which axis will be normal to the plane the points are projected onto
  if (t.x > t.y)
    if (t.x > t.z)
      biggest = 0;
    else
      biggest = 2;
  else if (t.y > t.z)
    biggest = 1;
  else
    biggest = 2;

  // For a plane with a normal that is in the opposite direction of the axis,
  // we should circle the other direction -- i.e. always circle in clockwise direction with normal (left-handed)
  if (norm->xyz[biggest] > 0) {
    i = ij_table[biggest][0];
    j = ij_table[biggest][1];
  } else {
    i = ij_table[biggest][1];
    j = ij_table[biggest][0];
  }

  // now do the 2d problem in the i,j plane

  // Get the i,j check point
  check_i = colp_array->xyz[i];
  check_j = colp_array->xyz[j];

  // Do a simple 2d cross-product between each line segment and the start point to the check point
  // Go in a clockwise direction, if determinant is negative then point is outside of this multi-
  // side polygon.  :)  Only works for concave polygons.
  for (edge = edgemask = 0; edge < nv; edge++) {
    vec2d edgevec, checkvec;
    float d;

    // v0 = (vector_array *)&Vertices[vertex_list[facenum*3+edge]];
    // v1 = (vector_array *)&Vertices[vertex_list[facenum*3+((edge+1)%nv)]];
    v0 = (vector_array *)vertex_ptr_list[edge];
    v1 = (vector_array *)vertex_ptr_list[(edge + 1) % nv];

    edgevec.i = v1->xyz[i] - v0->xyz[i];
    edgevec.j = v1->xyz[j] - v0->xyz[j];

    checkvec.i = check_i - v0->xyz[i];
    checkvec.j = check_j - v0->xyz[j];

    d = checkvec.i * edgevec.j - checkvec.j * edgevec.i;

    if (d < 0) // we are outside of triangle
      edgemask |= (1 << edge);
  }

  return edgemask;
}

// decide it it's close enough to hit
// determine if and where a vector intersects with a sphere
// vector defined by p0,p1
// if there is an intersection this function returns 1, fills in intp, and col_dist else it returns 0
// NOTE:  Caller should account for the radius of the vector (i.e. no rad. for the vector is passed
//        to this function -- the 2 radii are additive to it is trial and it saves 1 parameter
int check_vector_to_sphere_1(vector *intp, float *col_dist, const vector *p0, const vector *p1, vector *sphere_pos,
                             float sphere_rad, bool f_correcting, bool f_init_collisions) {
  vector line_vec;            // Vector direction of line from p0 to p1
  vector normalized_line_vec; // Normalized line vector
  float mag_line;             // Length of the line

  vector point_to_center_vec;  // Vector from p0 to the center of the sphere
  vector closest_point;        // Location the sphere's centerpoint parallel projected onto the line
  float closest_point_dist;    // Distance from p0 to the closest_point
  float closest_mag_to_center; // Distance from the clostest_point to the center of the sphere

  float shorten; // How much to subtract from the closest_point_dist to get the actual intersection
                 // point

  ASSERT(sphere_rad > 0.0);

  // Get the vectors as usual
  line_vec = *p1 - *p0;
  point_to_center_vec = *sphere_pos - *p0;

  if (line_vec * point_to_center_vec <= 0.0f)
    return 0;

  // Get the magnitude and direction of the line vector
  normalized_line_vec = line_vec;
  mag_line = vm_NormalizeVector(&normalized_line_vec);

  // Compute the location of the point on the line that is perpendicular to the center of the sphere
  closest_point_dist = normalized_line_vec * point_to_center_vec;

  // We check for an initial hit, so if closest_point is negative distance, it was a miss (think about it)
  // Otherwise, make sure it is not any farther than would for a collision to happen
  if (closest_point_dist < 0.0 || closest_point_dist >= mag_line + sphere_rad)
    return 0;

  // Is the initial p0 position an intersection?  If so, warn us and collide immediately.
  if (point_to_center_vec * point_to_center_vec < sphere_rad * sphere_rad) {
    if (f_correcting) {
/*
      // chrishack
      mprintf(0, "FVI WARNING: Start point is inside of a checked sphere %f %f\n",
              point_to_center_vec * point_to_center_vec,
              sphere_rad * sphere_rad);
*/
      // chrishack this movement intersection fix is a hack...  How do we do correct cylinder/vector interestion?
      vector n_ptc = point_to_center_vec;
      vm_NormalizeVector(&n_ptc);

      *intp =
          *p0 - n_ptc * (sphere_rad - (float)sqrt(sphere_rad * sphere_rad - point_to_center_vec * point_to_center_vec));

      *col_dist = 0.0;
      return 1;
    } else if (f_init_collisions) {
      *intp = *p0;
      *col_dist = 0.0;

      return 1;
    } else {
      // If not correcting, ignore initial point collisions, as they make no sense.
      return 0;
    }
  }

  closest_point = *p0 + closest_point_dist * normalized_line_vec;
  closest_mag_to_center = vm_VectorDistance(&closest_point, sphere_pos);

  // We are not moving close enough to collide with the circle
  if (closest_mag_to_center >= sphere_rad)
    return 0;

  // Pathagorithm Theorom -- the radius is the hypothenus, the other two sides are the distance
  // from the point to the line, and the amount we should subtract from the line to account
  // for the sphere overlapping the line at the closest approach point
  shorten = sqrt(sphere_rad * sphere_rad - closest_mag_to_center * closest_mag_to_center);
  *col_dist = closest_point_dist - shorten;
  if (*col_dist > mag_line)
    return 0;

  // Actual collision distance
  *intp = *p0 + *col_dist * normalized_line_vec;

  // Actual collision point
  return 1;
}

bool IsPointInCylinder(vector *normal, vector *cylinder_pnt, vector *edir, float elen, const float rad,
                       const vector *pnt, vector *mdir, bool *f_collide) {
  float plen = (*pnt - *cylinder_pnt) * *edir;

  if (plen < 0.0f || plen > elen) {
    return false;
  }

  vector newp = *cylinder_pnt + *edir * plen;
  *normal = *pnt - newp;

  if (vm_NormalizeVector(normal) >= rad) {
    return false;
  }

  if (*normal * *mdir >= 0.0f)
    *f_collide = false;
  else
    *f_collide = true;

  return true;
}

// check if a sphere intersects a face -- this can be optimized (only need 2d stuff after rotation)
int check_vector_to_cylinder(vector *colp, vector *intp, float *col_dist, vector *wall_norm, const vector *p0,
                             const vector *p1, float rad, vector *ep0, vector *ep1) {
  matrix edge_orient;
  vector po0, po1;
  vector edgevec = *ep1 - *ep0;
  vector mvec;
  vector closest_pnt;

  float edge_len;
  float dist;
  float vector_len;
  float dist_from_origin;
  float dist_to_intersection;
  int i;
  int valid_hit = 0;

  vector mvec3d;
  float vector_len3d;

  float t[4];
  vector ivertex[4];

  int valid_t[4];
  float cole_dist[4];
  vector inte[4];

  mvec3d = *p1 - *p0;
  vector_len3d = vm_NormalizeVector(&mvec3d);

  edge_len = vm_NormalizeVector(&edgevec);

  vector init_normal;
  bool f_init_collide;

  if (!IsPointInCylinder(&init_normal, ep0, &edgevec, edge_len, rad, p0, &mvec3d, &f_init_collide)) {
    vm_VectorToMatrix(&edge_orient, &edgevec, NULL, NULL);

    po0 = (*p0 - *ep0) * edge_orient;
    po1 = (*p1 - *ep0) * edge_orient;

    po0.z = po1.z = 0.0;
    mvec = po1 - po0;
    vector_len = vm_NormalizeVector(&mvec);

    dist = -(mvec * po0);

    closest_pnt = po0 + dist * mvec;
    //	ASSERT(!(closest_pnt.x == 0.0 && closest_pnt.y == 0.0 && closest_pnt.z == 0)); -- why does this matter?

    dist_from_origin = vm_GetMagnitude(&closest_pnt);
    if (dist_from_origin >= rad)
      return 0;

    dist_to_intersection = sqrt(rad * rad - dist_from_origin * dist_from_origin);

    t[0] = (dist + dist_to_intersection) / vector_len; // (0.0 to 1.0) is on line
    if (t[0] >= 0.0 && t[0] <= 1.0) {
      valid_t[0] = 1;
    } else {
      valid_t[0] = 0;
    }

    t[1] = (dist - dist_to_intersection) / vector_len; // (0.0 to 1.0) is on line
    if (t[1] >= 0.0 && t[1] <= 1.0) {
      valid_t[1] = 1;
    } else {
      valid_t[1] = 0;
    }

    for (i = 0; i < 2; i++) {
      float t_edge;

      if (valid_t[i]) {
        ivertex[i] = *p0 + mvec3d * (vector_len3d * t[i]);

        t_edge = ((ivertex[i] - *ep0) * edgevec) / edge_len;
        if (t_edge >= 0.0 && t_edge <= 1.0) {
          cole_dist[i] = vector_len3d * t[i];
          inte[i] = *ep0 + ((ivertex[i] - *ep0) * edgevec) * edgevec;
          valid_hit = 1;
          /// mprintf(0, "%f,%f,%f to %f,%f, %f\n", XYZ(p0), XYZ(p1));
        } else {
          valid_t[i] = 0;
        }
      }
    }

    vector d_vec;
    // check end spheres
    if (check_vector_to_sphere_1(&ivertex[2], &cole_dist[2], p0, p1, ep0, rad, false, true)) {
      t[2] = cole_dist[2] / vector_len3d;
      valid_t[2] = 1;
      valid_hit = 1;
      // mprintf(0, "Sphere %f,%f,%f to %f,%f, %f\n", XYZ(p0), XYZ(p1));
      d_vec = *ep1 - ivertex[2];
      vm_NormalizeVector(&d_vec);
      inte[2] = ivertex[2] + rad * (d_vec);
    } else {
      valid_t[2] = 0;
    }
    if (check_vector_to_sphere_1(&ivertex[3], &cole_dist[3], p0, p1, ep1, rad, false, true)) {
      t[3] = cole_dist[3] / vector_len3d;
      valid_t[3] = 1;
      valid_hit = 1;
      d_vec = *ep1 - ivertex[3];
      vm_NormalizeVector(&d_vec);
      inte[3] = ivertex[3] + rad * (d_vec);
    } else {
      valid_t[3] = 0;
    }

    if (valid_hit == 0)
      return 0;

    int best_hit_index = -1;
    for (i = 0; i < 4; i++) {
      if (valid_t[i]) {
        if (best_hit_index == -1 || cole_dist[i] < cole_dist[best_hit_index]) {
          best_hit_index = i;
        }
      }
    }

    //	if(best_hit_index < 2)

    *colp = inte[best_hit_index];
    *intp = ivertex[best_hit_index];
    *col_dist = cole_dist[best_hit_index];

    *wall_norm = *intp - *colp;
    vm_NormalizeVector(wall_norm);

    // mprintf(0, "We hit at %f,%f,%f \nwith %f,%f,%f on face\n", XYZ(intp), XYZ(colp));

    return 1;
  } else {
    if (f_init_collide) {
      *col_dist = 0.0f;
      *wall_norm = init_normal;
      *colp = *p0 - init_normal * rad;
      *intp = *p0;

      return 1;
    } else {
      return 0;
    }
  }
}

/*
int check_vector_to_cylinder(vector *colp, vector *intp, float *col_dist, vector *wall_norm, vector *p0, vector *p1,
float rad, vector *ep0, vector *ep1)
{
        int i;
        float s;
        float t;
        float pmag;
        vector init_normal;
        bool f_hit = false;
        vector mdir = *p1 - *p0;
        float mlen = vm_NormalizeVector(&mdir);
        vector edir = *ep1 - *ep0;
        float elen = vm_NormalizeVector(&edir);
        bool f_init_collide;

        float cdist; // Closest dist

        vector perp = (mdir ^ edir);        // Determines the normalized perp to both lines
        if(perp == Zero_vector)
                goto check_ends;  // We are moving parallal to the cylinder (only end collisions are possible)
        pmag = vm_NormalizeVector(&perp);

        ASSERT(pmag != 0.0);

        vector brbc = *p0 - *ep0;
        cdist = fabs((brbc) * perp);  // Closest distance

        if(cdist >= rad)  // If the closest point is a more than a rad away, no hit
                return 0;

        // Check for an initial collision
        if(!IsPointInCylinder(&init_normal, ep0, &edir, elen, rad, p0, &mdir, &f_init_collide))
        {
                t = (((brbc) ^ edir) * perp)/pmag;

                vector o = perp ^ edir;
                vm_NormalizeVector(&o);

                s = fabs(sqrt(rad * rad - pmag * pmag)/(mdir * o));

                vector cyl_pnt[2];
                vector cyl_norm[2];

                // Determine the 2 potential hitpoint
                cyl_pnt[0] = *p0 + (t - s) * mdir;
                cyl_pnt[1] = *p0 + (t + s) * mdir;

                // Determine the 2 potential hit normals
                for(i = 0; i < 2; i++)
                {
                        vector hb = cyl_pnt[i] - *ep0;
                        cyl_norm[i] = (hb - (hb * edir) * edir)/rad;
                        vm_NormalizeVector(&cyl_norm[i]); // Accounts for fp round off. - probably not necessary
                }

                bool f_valid[2];
                f_valid[0] = f_valid[1] = true;

                // Determine if points are on the valid
                for(i = 0; i < 2; i++)
                {
                        if(f_valid[i])
                        {
                                if(cyl_norm[i] * mdir >= 0.0f) // Is it opposite the direction of motion
                                {
                                        f_valid[i] = false;
                                }
                        }

                        if(f_valid[i])  // Is it on the cylinder
                        {
                                float proj = (cyl_pnt[i] - *ep0) * edir;
                                if(proj < 0.0 || proj > elen)
                                {
                                        f_valid[i] = false;
                                }
                        }

                        if(f_valid[i]) // Is it on the movement path
                        {
                                float proj = (cyl_pnt[i] - *p0) * mdir;
                                if(proj < 0.0 || proj > mlen)
                                {
                                        f_valid[i] = false;
                                }
                        }

                        // A real collision :)  Update all the collision properties
                        if(f_valid[i])
                        {
                                // Determine the collision distance
                                float new_dist = vm_VectorDistance(p0, &cyl_pnt[i]);

                                *col_dist = new_dist;
                                *wall_norm = cyl_norm[i];
                                *intp = cyl_pnt[i];
                                *colp = cyl_pnt[i] - cyl_norm[i] * rad;

                                f_hit = 1;
                        }
                }

                check_ends:

                vector end_pnt;

                if(f_hit)
                {
                        end_pnt = *intp;
                }
                else
                {
                        end_pnt = *p1;
                }

        // decide it it's close enough to hit
        // determine if and where a vector intersects with a sphere
        // vector defined by p0,p1
        // if there is an intersection this function returns 1, fills in intp, and col_dist else it returns 0
        // NOTE:  Caller should account for the radius of the vector (i.e. no rad. for the vector is passed
        //        to this function -- the 2 radii are additive to it is trial and it saves 1 parameter
                if(check_vector_to_sphere_1(intp, col_dist, p0, &end_pnt, ep0, rad, false, true))
                {
                        f_hit = 1;
                }

                if(f_hit)
                {
                        end_pnt = *intp;
                }
                else
                {
                        end_pnt = *p1;
                }

                if(check_vector_to_sphere_1(intp, col_dist, p0, &end_pnt, ep0, rad, false, true))
                {
                        f_hit = 1;
                }

                return f_hit;
        }
        else
        {
                if(f_init_collide)
                {
                        *col_dist = 0.0f;
                        *wall_norm = init_normal;
                        *colp = *p0 - init_normal * rad;
                        *intp = *p0;

                        return 1;
                }
                else
                {
                        return 0;
                }
        }
}
*/

// check if a sphere intersects a face
int check_sphere_to_face(vector *colp, vector *intp, float *col_dist, vector *wall_norm, const vector *p0,
                         const vector *p1, vector *face_normal, int nv, float rad, vector **vertex_ptr_list) {
  uint32_t edgemask;

  ASSERT(nv > 0 && nv <= 32); // otherwise, we overflow the edgemask -- if we hit this we need to make edgemask a long
                              // long and adjust the other functions accordingly

  // now do 2d check to see if point is inside the face (if so, we are done)
  edgemask = check_point_to_face(colp, face_normal, nv, vertex_ptr_list);

  // If we are inside edgemask is 0, we hit the face.
  if (edgemask == 0) {
    //		mprintf(0, "CSTF Hit Face\n");
    *col_dist = vm_VectorDistance(p0, intp);
    *wall_norm = *face_normal;
    return IT_FACE;
  } else {
    // Although the plane collision point is not in the face, we might hit an edge.
    // If the checkpoint collides with the edge of a face, it could
    // go a little farther before hitting anything

    vector *v0, *v1;
    int edgenum;

    // If we have no radius we could only hit the face and not an edge or point
    if (rad == 0.0)
      return IT_NONE;

    int f_hit = 0;
    vector c_end = *p1;

    // get verts for edge we're behind
    for (edgenum = 0; edgenum < nv; edgenum++) {
      if (edgemask & 1) {
        v0 = vertex_ptr_list[edgenum];
        v1 = vertex_ptr_list[(edgenum + 1) % nv];

        if (check_vector_to_cylinder(colp, intp, col_dist, wall_norm, p0, &c_end, rad, v0, v1)) {
          c_end = *intp;
          f_hit = 1;
        }
      }

      edgemask = edgemask >> 1;
    }

    return f_hit;
  } /*	checkvec = *p0 - *v0;
           edgevec = *v1 - *v0;
           edgelen = vm_NormalizeVector(&edgevec);

           cur_dist = edgevec * checkvec;

           closest_point = *v0 + cur_dist * edgevec;

           // See if the sphere intersects the edge of the face
           if(!check_vector_to_sphere_1(intp, col_dist, p0, p1, &closest_point, rad, 1)) return IT_NONE;
           checkvec = *intp - *v0;
           cur_dist = edgevec * checkvec;
           if(cur_dist >= 0 && cur_dist <= edgelen) {

//			mprintf(0, "Hit edge\n");

                   *wall_norm = *intp - closest_point;
                   vm_NormalizeVector(wall_norm);
                   *colp = *intp + (-rad) * *wall_norm;

                   return IT_EDGE;
           }

           // Look to see if there is a point collision
           else if(cur_dist < 0) closest_point = *v0;
           else closest_point = *v1;
           if(!check_vector_to_sphere_1(intp, col_dist, p0, p1, &closest_point, rad, 1)) return IT_NONE;

//		mprintf(0, "Hit point\n");

           *wall_norm = *intp - closest_point;
           vm_NormalizeVector(wall_norm);
           *colp = *intp + (-rad) * *wall_norm;

           return IT_POINT;
   }*/
}

// returns true if line intersects with face. fills in newp with intersection
// point on plane, whether or not line intersects side
// facenum determines which of four possible faces we have
// note: the seg parm is temporary, until the face itself has a point field
int check_line_to_face(vector *newp, vector *colp, float *col_dist, vector *wall_norm, const vector *p0,
                       const vector *p1, vector *face_normal, vector **vertex_ptr_list, const int nv, const float rad) {
  int f_pli; // Flag for if a plane that defines the face intersects with the line
  int vertnum = 0;
  vector *test = vertex_ptr_list[0];
  int i;

  ASSERT(newp != NULL && p0 != 0 && p1 != NULL && rad >= 0.0);

  // This is so we always use the same vertex
  for (i = 1; i < nv; i++) {
    if (test > vertex_ptr_list[i]) {
      test = vertex_ptr_list[i];
      vertnum = i;
    }
  }

  // Determine the intersection point between the plane(of the face) and the line
  // This point is the center of the circle (not the edge)
  f_pli = find_plane_line_intersection(newp, colp, vertex_ptr_list[vertnum], face_normal, p0, p1, rad);

  if (!f_pli)
    return IT_NONE;

  // This is the edge point where the actual intersection with the plane is occuring
  //	*colp = *newp;
  //	if (rad != 0.0)
  //		*colp += *face_normal*(-rad);

  //	mprintf(0, "Check line to face: segment %d, side %d\n", seg - Segments, side);

  // We know that we hit the plane, but did we hit the face (in bounds)
  return check_sphere_to_face(colp, newp, col_dist, wall_norm, p0, p1, face_normal, nv, rad, vertex_ptr_list);
}

// chrishack -- check this later
// computes the parameters of closest approach of two lines
// fill in two parameters, t0 & t1.  returns 0 if lines are parallel, else 1
bool check_line_to_line(float *t1, float *t2, vector *p1, vector *v1, vector *p2, vector *v2) {
  matrix det;
  float d, cross_mag2; // mag squared cross product

  det.rvec = *p2 - *p1;
  det.fvec = *v1 ^ *v2; // (crossproduct)
  cross_mag2 = det.fvec * det.fvec;

  if (cross_mag2 == 0.0)
    return false; // lines are parallel

  det.uvec = *v2;
  d = calc_det_value(&det);
  *t1 = d / cross_mag2;

  det.uvec = *v1;
  d = calc_det_value(&det);
  *t2 = d / cross_mag2;

  return true; // found point
}

// determine if a vector intersects with an object
// if no intersects, returns 0, else fills in intp and returns dist
int check_vector_to_object(vector *intp, float *col_dist, vector *p0, vector *p1, float rad, object *still_obj,
                           object *fvi_obj) {
  float still_size;
  vector still_pos = still_obj->pos;
  float total_size;

  int fvi_objnum = fvi_query_ptr->thisobjnum;

  if ((still_obj->flags & OF_POLYGON_OBJECT) && still_obj->type != OBJ_POWERUP && still_obj->type != OBJ_WEAPON &&
      still_obj->type != OBJ_DEBRIS && still_obj->type != OBJ_ROOM && still_obj->type != OBJ_PLAYER) {
    still_size = Poly_models[still_obj->rtype.pobj_info.model_num].anim_size;
    still_pos += still_obj->anim_sphere_offset;
  } else {
    still_size = still_obj->size;
  }

  // chrishack -- why?
  //	if (obj->type == OBJ_ROBOT && Robot_info[obj->id].attack_type)
  //		size = (size*3)/4;
  // if obj is player, and bumping into other player or a weapon of another coop player, reduce radius
  //	if (obj->type == OBJ_PLAYER &&
  //		 	((otherobj->type == OBJ_PLAYER) ||
  //	 		((Game_mode&GM_MULTI_COOP) && otherobj->type == OBJ_WEAPON &&
  // otherobj->ctype.laser_info.parent_type
  //== OBJ_PLAYER))) 		size = size/2;

  // This accounts for relative position vs. relative velocity
  if (fvi_objnum != -1 && still_obj->movement_type == MT_PHYSICS && Objects[fvi_objnum].movement_type == MT_PHYSICS) {
    if (still_obj->type != OBJ_POWERUP && Objects[fvi_objnum].type != OBJ_POWERUP) {
      if ((still_pos - Objects[fvi_objnum].pos) *
              (still_obj->mtype.phys_info.velocity - Objects[fvi_objnum].mtype.phys_info.velocity) >=
          0) {
#ifndef NED_PHYSICS
#ifdef _DEBUG
        if (Physics_player_verbose) {
          if (Player_object == &Objects[fvi_objnum]) {
            mprintf(0, "FVI: Earily exit on %d\n", OBJNUM(still_obj));
          }
        }
#endif
#endif

        return 0;
      }
    }
  }

  total_size = still_size + rad;

  if (total_size <= 0.0f) {
#ifdef _DEBUG
    if (fvi_objnum >= 0)
      mprintf(0, "Get Chris: type %d and type %d are zero radius\n", still_obj->type, Objects[fvi_objnum].type);
    else
      mprintf(0, "Get Chris: A non-object tried to hit a zero radii object of type %d\n", still_obj->type);
#endif
    return 0;
  }

  // Account for the radius of the vector.
  return check_vector_to_sphere_1(intp, col_dist, p0, p1, &still_pos, total_size, false, true);
}

inline void compute_movement_AABB(void) {
  const vector delta_movement = fvi_hit_data_ptr->hit_pnt - *fvi_query_ptr->p0;

  fvi_min_xyz = fvi_max_xyz = *fvi_query_ptr->p0;

  if (delta_movement.x > 0.0f)
    fvi_max_xyz.x += delta_movement.x;
  else
    fvi_min_xyz.x += delta_movement.x;

  if (delta_movement.y > 0.0f)
    fvi_max_xyz.y += delta_movement.y;
  else
    fvi_min_xyz.y += delta_movement.y;

  if (delta_movement.z > 0.0f)
    fvi_max_xyz.z += delta_movement.z;
  else
    fvi_min_xyz.z += delta_movement.z;

  fvi_wall_min_xyz = fvi_min_xyz;
  fvi_wall_max_xyz = fvi_max_xyz;

  if (!fvi_zero_rad) {
    if (fvi_query_ptr->thisobjnum < 0) {
      vector offset_vec;

      offset_vec.x = fvi_query_ptr->rad;
      offset_vec.y = fvi_query_ptr->rad;
      offset_vec.z = fvi_query_ptr->rad;

      fvi_min_xyz -= offset_vec;
      fvi_max_xyz += offset_vec;

      fvi_wall_min_xyz = fvi_min_xyz;
      fvi_wall_max_xyz = fvi_max_xyz;
    } else {
      vector max_offset = Objects[fvi_query_ptr->thisobjnum].max_xyz - Objects[fvi_query_ptr->thisobjnum].pos;
      vector min_offset = Objects[fvi_query_ptr->thisobjnum].min_xyz - Objects[fvi_query_ptr->thisobjnum].pos;

      fvi_max_xyz += max_offset;
      fvi_min_xyz += min_offset;

      //			if(!(Objects[fvi_query_ptr->thisobjnum].mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))
      {
        fvi_wall_min_xyz = fvi_min_xyz;
        fvi_wall_max_xyz = fvi_max_xyz;
      }
    }
  }
}

inline bool object_object_AABB(object *obj1, object *obj2) {
  bool overlap = true;

  if (obj1->max_xyz.x < obj2->min_xyz.x || obj2->max_xyz.x < obj1->min_xyz.x || obj1->max_xyz.z < obj2->min_xyz.z ||
      obj2->max_xyz.z < obj1->min_xyz.z || obj1->max_xyz.y < obj2->min_xyz.y || obj2->max_xyz.y < obj1->min_xyz.y)
    overlap = false;

  return overlap;
}

inline bool object_movement_AABB(object *obj) {
  bool overlap = true;

  if (obj->max_xyz.x < fvi_min_xyz.x || fvi_max_xyz.x < obj->min_xyz.x || obj->max_xyz.z < fvi_min_xyz.z ||
      fvi_max_xyz.z < obj->min_xyz.z || obj->max_xyz.y < fvi_min_xyz.y || fvi_max_xyz.y < obj->min_xyz.y)
    overlap = false;

  return overlap;
}

inline bool object_room_AABB(object *obj, face *room_face) {
  bool overlap = true;

  if (obj->max_xyz.y < room_face->min_xyz.y || room_face->max_xyz.y < obj->min_xyz.y ||
      obj->max_xyz.x < room_face->min_xyz.x || room_face->max_xyz.x < obj->min_xyz.x ||
      obj->max_xyz.z < room_face->min_xyz.z || room_face->max_xyz.z < obj->min_xyz.z)
    overlap = false;

  return overlap;
}

inline bool room_movement_AABB(face *room_face) {
  bool overlap = true;

  if (fvi_wall_max_xyz.y < room_face->min_xyz.y || room_face->max_xyz.y < fvi_wall_min_xyz.y ||
      fvi_wall_max_xyz.x < room_face->min_xyz.x || room_face->max_xyz.x < fvi_wall_min_xyz.x ||
      fvi_wall_max_xyz.z < room_face->min_xyz.z || room_face->max_xyz.z < fvi_wall_min_xyz.z)
    overlap = false;

  return overlap;
}

inline bool room_manual_AABB(const face *room_face, const vector *min_xyz, const vector *max_xyz) {
  bool overlap = true;

  if (max_xyz->y < room_face->min_xyz.y || room_face->max_xyz.y < min_xyz->y || max_xyz->x < room_face->min_xyz.x ||
      room_face->max_xyz.x < min_xyz->x || max_xyz->z < room_face->min_xyz.z || room_face->max_xyz.z < min_xyz->z)
    overlap = false;

  return overlap;
}

#define MAX_QUICK_ROOMS 20

// Returns the number of faces that are approximately within the specified radius
int fvi_QuickDistFaceList(int init_room_index, vector *pos, float rad, fvi_face_room_list *quick_fr_list,
                          int max_elements) {
  int num_faces = 0;
  room *cur_room;
  vector min_xyz, max_xyz;
  int next_rooms[MAX_QUICK_ROOMS];
  int highest_next_room_index;
  int cur_next_room_index;
  int i;

  // ASSERT(quick_fr_list != NULL);
  ASSERT(pos != NULL);
  ASSERT(init_room_index >= 0 && init_room_index <= Highest_room_index && Rooms[init_room_index].used != 0);
  ASSERT(rad >= 0.0f);

  // Quick volume
  min_xyz = max_xyz = *pos;

  min_xyz.x -= rad;
  min_xyz.y -= rad;
  min_xyz.z -= rad;
  max_xyz.x += rad;
  max_xyz.y += rad;
  max_xyz.z += rad;

  // Initially this is the only room in the list
  next_rooms[0] = init_room_index;
  highest_next_room_index = 0;
  cur_next_room_index = 0;

  // Use standard fvi list_array / bool list
  fvi_visit_list[init_room_index >> 3] |= 0x01 << (init_room_index % 8);
  fvi_rooms_visited[0] = init_room_index;
  fvi_num_rooms_visited = 1;

  while (num_faces < max_elements && cur_next_room_index <= highest_next_room_index) {
    cur_room = &Rooms[next_rooms[cur_next_room_index]];

    // sort shit
    uint8_t msector = 0;

    if (min_xyz.x <= cur_room->bbf_min_xyz.x) {
      msector |= 0x01;
    }
    if (min_xyz.y <= cur_room->bbf_min_xyz.y) {
      msector |= 0x02;
    }
    if (min_xyz.z <= cur_room->bbf_min_xyz.z) {
      msector |= 0x04;
    }
    if (max_xyz.x >= cur_room->bbf_max_xyz.x) {
      msector |= 0x08;
    }
    if (max_xyz.y >= cur_room->bbf_max_xyz.y) {
      msector |= 0x10;
    }
    if (max_xyz.z >= cur_room->bbf_max_xyz.z) {
      msector |= 0x20;
    }

    const int16_t num_bbf_regions = cur_room->num_bbf_regions;
    int16_t *num_faces_ptr = cur_room->num_bbf;
    uint8_t *bbf_val = cur_room->bbf_list_sector;
    vector *region_min = cur_room->bbf_list_min_xyz;
    vector *region_max = cur_room->bbf_list_max_xyz;
    int16_t **bbf_list_ptr = cur_room->bbf_list;

    // Do the actual wall collsion stuff here!
    for (int test1 = 0; test1 < num_bbf_regions; test1++) {
      if (((*bbf_val) & msector) == (*bbf_val)) {
        if (region_min->x > max_xyz.x || region_min->y > max_xyz.y || region_min->z > max_xyz.z ||
            region_max->x < min_xyz.x || region_max->y < min_xyz.y || region_max->z < min_xyz.z)
          goto skip_region;

        int16_t *cur_face_index_ptr = *bbf_list_ptr;

        for (int sort_list_cur = 0; sort_list_cur < (*num_faces_ptr); sort_list_cur++) {
          i = *cur_face_index_ptr;
          cur_face_index_ptr++;

          int portal_num;
          int connect_room;

          if (!room_manual_AABB(&cur_room->faces[i], &min_xyz, &max_xyz))
            continue;

          if (quick_fr_list != NULL) {
            if (num_faces < max_elements) {
              quick_fr_list[num_faces].face_index = i;
              quick_fr_list[num_faces].room_index = ROOMNUM(cur_room);
              num_faces++;
            } else
              break;
          } else
            num_faces++;

          cur_room->faces[i].flags |= FF_TOUCHED;

          portal_num = cur_room->faces[i].portal_num;
          if (portal_num >= 0) {
            connect_room = cur_room->portals[portal_num].croom;

            // If the conect_room is not a terrain cell and we still have a slot in the next room list...
            if (connect_room >= 0 && highest_next_room_index + 1 < MAX_QUICK_ROOMS) {
              ASSERT(Rooms[connect_room].used);

              if ((fvi_visit_list[connect_room >> 3] & (0x01 << ((connect_room) % 8))) == 0) {
                fvi_visit_list[connect_room >> 3] |= 0x01 << (connect_room % 8);
                fvi_rooms_visited[fvi_num_rooms_visited++] = connect_room;

                next_rooms[++highest_next_room_index] = connect_room;
              }
            }
          }
        }
      }
    skip_region:;
      num_faces_ptr++;
      bbf_val++;
      region_max++;
      region_min++;
      bbf_list_ptr++;
    }

    cur_next_room_index++;
  }

  // Cleans up the boolean room visit list
  for (i = 0; i < fvi_num_rooms_visited; i++) {
    fvi_visit_list[fvi_rooms_visited[i] >> 3] = 0;
  }

  return num_faces;
}

// Returns the number of faces that are approximately within the specified radius
int fvi_QuickDistCellList(int init_cell_index, vector *pos, float rad, int *quick_cell_list, int max_elements) {
  int num_cells = 0;
  int next_y_delta;
  int xstart, xend, ystart, yend;
  int check_x, check_y;
  int xcounter, ycounter;
  int cur_node;

  ASSERT(quick_cell_list != NULL);
  ASSERT(pos != NULL);
  ASSERT(init_cell_index >= 0 && init_cell_index < TERRAIN_WIDTH * TERRAIN_DEPTH);
  ASSERT(rad >= 0.0f);

  cur_node = init_cell_index;

  // Check worst-case collisions.  This includes all nodes within a radius edge of the current node
  check_x = rad / TERRAIN_SIZE + 1;
  check_y = rad / TERRAIN_SIZE + 1;

  xstart = cur_node % TERRAIN_WIDTH - check_x;
  xend = cur_node % TERRAIN_WIDTH + check_x;
  ystart = cur_node / TERRAIN_WIDTH - check_y;
  yend = cur_node / TERRAIN_WIDTH + check_y;

  if (xstart < 0)
    xstart = 0;
  if (xend >= TERRAIN_WIDTH)
    xend = TERRAIN_WIDTH - 1;
  if (ystart < 0)
    ystart = 0;
  if (yend >= TERRAIN_DEPTH)
    yend = TERRAIN_DEPTH - 1;

  // This should be a faster interative why to do a square with center at original position
  cur_node = TERRAIN_WIDTH * ystart + xstart;
  next_y_delta = TERRAIN_WIDTH - (xend - xstart) - 1;

  for (ycounter = ystart; ycounter <= yend; ycounter++) {
    for (xcounter = xstart; xcounter <= xend; xcounter++) {
      if ((Terrain_seg[cur_node].y >= pos->y - rad) || (Terrain_seg[cur_node + TERRAIN_WIDTH + 1].y >= pos->y - rad) ||
          (Terrain_seg[cur_node + 1].y >= pos->y - rad) || (Terrain_seg[cur_node + TERRAIN_WIDTH].y >= pos->y - rad)) {
        quick_cell_list[num_cells++] = cur_node;
        if (num_cells >= max_elements)
          break;
      }
      cur_node += 1;
    }
    if (num_cells >= max_elements)
      break;
    cur_node += next_y_delta;
  }

  return num_cells;
}

int fvi_QuickDistObjectList(vector *pos, int init_room_index, float rad, int16_t *object_index_list, int max_elements,
                            bool f_lightmap_only, bool f_only_players_and_ais, bool f_include_non_collide_objects,
                            bool f_stop_at_closed_doors) {
  int num_objects = 0;
  int x; //, y;
  vector delta;

  // Quick volume
  delta.x = delta.y = delta.z = rad;
  fvi_min_xyz = fvi_max_xyz = *pos;

  fvi_min_xyz -= delta;
  fvi_max_xyz += delta;

  fvi_wall_min_xyz = fvi_min_xyz;
  fvi_wall_max_xyz = fvi_max_xyz;

  if (ROOMNUM_OUTSIDE(init_room_index)) {
    int num_cells = 0;
    int next_y_delta;
    int xstart, xend, ystart, yend;
    int check_x, check_y;
    int xcounter, ycounter;
    int cur_node;

    cur_node = CELLNUM(init_room_index);

    // Check worst-case collisions.  This includes all nodes within a radius edge of the current node
    check_x = rad / TERRAIN_SIZE + 1;
    check_y = rad / TERRAIN_SIZE + 1;

    xstart = cur_node % TERRAIN_WIDTH - check_x;
    xend = cur_node % TERRAIN_WIDTH + check_x;
    ystart = cur_node / TERRAIN_WIDTH - check_y;
    yend = cur_node / TERRAIN_WIDTH + check_y;

    if (xstart < 0)
      xstart = 0;
    if (xend >= TERRAIN_WIDTH)
      xend = TERRAIN_WIDTH - 1;
    if (ystart < 0)
      ystart = 0;
    if (yend >= TERRAIN_DEPTH)
      yend = TERRAIN_DEPTH - 1;

    // This should be a faster interative why to do a square with center at original position
    cur_node = TERRAIN_WIDTH * ystart + xstart;
    next_y_delta = TERRAIN_WIDTH - (xend - xstart) - 1;

    for (ycounter = ystart; ycounter <= yend; ycounter++) {
      for (xcounter = xstart; xcounter <= xend; xcounter++) {
        // Do object stuff
        int cur_obj_index = Terrain_seg[cur_node].objects;

        while (cur_obj_index > -1) {
          if (num_objects >= max_elements)
            break;

          if ((f_include_non_collide_objects) || CollisionRayResult[Objects[cur_obj_index].type] != RESULT_NOTHING) {
            if (!f_only_players_and_ais || Objects[cur_obj_index].type == OBJ_PLAYER ||
                Objects[cur_obj_index].ai_info) {
              if (!(f_lightmap_only && (Objects[cur_obj_index].lighting_render_type != LRT_LIGHTMAPS) &&
                    Objects[cur_obj_index].type != OBJ_ROOM)) {
                if (object_movement_AABB(&Objects[cur_obj_index]) && !(Objects[cur_obj_index].flags & OF_BIG_OBJECT)) {
                  object_index_list[num_objects++] = cur_obj_index;
                  ASSERT(num_objects < 0 || num_objects <= max_elements);
                }
              }
            }
          }

          cur_obj_index = Objects[cur_obj_index].next;
        }

        if (num_objects >= max_elements)
          break;
        cur_node += 1;
      }
      if (num_objects >= max_elements)
        break;
      cur_node += next_y_delta;
    }

    // Do big object stuff
    for (x = 0; x < Num_big_objects; x++) {
      if (num_objects >= max_elements)
        break;

      if ((f_include_non_collide_objects) || CollisionRayResult[Objects[x].type] != RESULT_NOTHING) {
        if (!f_only_players_and_ais || Objects[x].type == OBJ_PLAYER || Objects[x].ai_info) {
          if (!(f_lightmap_only && (Objects[BigObjectList[x]].lighting_render_type != LRT_LIGHTMAPS) &&
                Objects[BigObjectList[x]].type != OBJ_ROOM)) {
            if (object_movement_AABB(&Objects[BigObjectList[x]])) {
              object_index_list[num_objects++] = BigObjectList[x];
              ASSERT(num_objects < 0 || num_objects <= max_elements);
            }
          }
        }
      }
    }
  } else {
    room *cur_room;
    int next_rooms[MAX_QUICK_ROOMS];
    int highest_next_room_index;
    int cur_next_room_index;
    int i;

    ASSERT(pos != NULL);
    ASSERT(init_room_index >= 0 && init_room_index <= Highest_room_index && Rooms[init_room_index].used != 0);
    ASSERT(rad >= 0.0f);

    // Initially this is the only room in the list
    next_rooms[0] = init_room_index;
    highest_next_room_index = 0;
    cur_next_room_index = 0;

    // Use standard fvi list_array / bool list
    fvi_visit_list[init_room_index >> 3] |= 0x01 << (init_room_index % 8);
    fvi_rooms_visited[0] = init_room_index;
    fvi_num_rooms_visited = 1;

    while (num_objects <= max_elements && cur_next_room_index <= highest_next_room_index) {
      cur_room = &Rooms[next_rooms[cur_next_room_index]];

      // Do object stuff
      int cur_obj_index = cur_room->objects;

      while (cur_obj_index > -1) {
        if (num_objects >= max_elements)
          break;
        if ((f_include_non_collide_objects) || CollisionRayResult[Objects[cur_obj_index].type] != RESULT_NOTHING) {
          if (!f_only_players_and_ais || Objects[cur_obj_index].type == OBJ_PLAYER || Objects[cur_obj_index].ai_info) {
            if (!(f_lightmap_only && (Objects[cur_obj_index].lighting_render_type != LRT_LIGHTMAPS))) {
              if (object_movement_AABB(&Objects[cur_obj_index])) {
                object_index_list[num_objects++] = cur_obj_index;
                ASSERT(num_objects < 0 || num_objects <= max_elements);
              }
            }
          }
        }

        cur_obj_index = Objects[cur_obj_index].next;
      }

      if (num_objects >= max_elements)
        break;

      if (f_stop_at_closed_doors && cur_room->flags & RF_DOOR) {
        // Closed doors antenuate a lot
        if (DoorwayGetPosition(cur_room) == 0.0)
          goto skip_room_prop;
      }

      for (x = 0; x < cur_room->num_portals; x++) {
        int portal_num;
        int connect_room;

        if (f_stop_at_closed_doors) {
          if ((cur_room->portals[x].flags & PF_RENDER_FACES) &&
                  !(cur_room->portals[x].flags & PF_RENDERED_FLYTHROUGH) ||
              (cur_room->portals[x].flags & PF_BLOCK)) {
            continue;
          }
        }

        i = cur_room->portals[x].portal_face;

        if (!room_movement_AABB(&cur_room->faces[i]))
          continue;

        portal_num = cur_room->faces[i].portal_num;
        connect_room = cur_room->portals[portal_num].croom;

        // If the conect_room is not a terrain cell and we still have a slot in the next room list...
        if (connect_room >= 0 && highest_next_room_index + 1 < MAX_QUICK_ROOMS) {
          ASSERT(Rooms[connect_room].used);

          if ((fvi_visit_list[connect_room >> 3] & (0x01 << ((connect_room) % 8))) == 0) {
            fvi_visit_list[connect_room >> 3] |= 0x01 << (connect_room % 8);
            fvi_rooms_visited[fvi_num_rooms_visited++] = connect_room;

            ASSERT(highest_next_room_index + 1 >= 0 && highest_next_room_index + 1 < MAX_QUICK_ROOMS);
            next_rooms[++highest_next_room_index] = connect_room;
          }
        }
      }

    skip_room_prop:

      cur_next_room_index++;
    }

    // Cleans up the boolean room visit list
    for (i = 0; i < fvi_num_rooms_visited; i++) {
      fvi_visit_list[fvi_rooms_visited[i] >> 3] = 0;
    }
  }

  return num_objects;
}

bool fvi_QuickRoomCheck(vector *pos, room *cur_room, bool try_again) {
  vector hit_point; // where we hit
  vector colp;
  float cur_dist; // distance to hit point
  int i;
  bool f_in_room = true;

internal_try_again:

  int closest_hit_type = 0;
  float closest_hit_distance = 10000000.0f;

  vector min_xyz;
  vector max_xyz;
  vector new_pos;

  if (!(cur_room->used) || (cur_room->flags & RF_EXTERNAL))
    return false;

  new_pos = min_xyz = max_xyz = *pos;

  if (!try_again) {
    new_pos.x += 10000000.0f;
    max_xyz.x += 10000000.0f;
  } else {
    new_pos.z -= 10000000.0f;
    min_xyz.z -= 10000000.0f;
    new_pos.y -= 10000000.0f;
    min_xyz.y -= 10000000.0f;
    new_pos.x -= 10000000.0f;
    min_xyz.x -= 10000000.0f;
  }
  //	mprintf(0, "Checking room %d ", ROOMNUM(cur_room));

  // sort shit
  uint8_t msector = 0;

  if (min_xyz.x <= cur_room->bbf_min_xyz.x) {
    msector |= 0x01;
  }
  if (min_xyz.y <= cur_room->bbf_min_xyz.y) {
    msector |= 0x02;
  }
  if (min_xyz.z <= cur_room->bbf_min_xyz.z) {
    msector |= 0x04;
  }
  if (max_xyz.x >= cur_room->bbf_max_xyz.x) {
    msector |= 0x08;
  }
  if (max_xyz.y >= cur_room->bbf_max_xyz.y) {
    msector |= 0x10;
  }
  if (max_xyz.z >= cur_room->bbf_max_xyz.z) {
    msector |= 0x20;
  }

  const int16_t num_bbf_regions = cur_room->num_bbf_regions;
  int16_t *num_faces_ptr = cur_room->num_bbf;
  uint8_t *bbf_val = cur_room->bbf_list_sector;
  vector *region_min = cur_room->bbf_list_min_xyz;
  vector *region_max = cur_room->bbf_list_max_xyz;
  int16_t **bbf_list_ptr = cur_room->bbf_list;

  // Do the actual wall collsion stuff here!
  for (int test1 = 0; test1 < num_bbf_regions; test1++) {
    if (((*bbf_val) & msector) == (*bbf_val)) {
      if (region_min->x > max_xyz.x || region_min->y > max_xyz.y || region_min->z > max_xyz.z ||
          region_max->x < min_xyz.x || region_max->y < min_xyz.y || region_max->z < min_xyz.z)
        goto skip_region;

      int16_t *cur_face_index_ptr = *bbf_list_ptr;

      for (int sort_list_cur = 0; sort_list_cur < (*num_faces_ptr); sort_list_cur++) {
        i = *cur_face_index_ptr;
        cur_face_index_ptr++;

        vector face_normal;
        vector *vertex_ptr_list[MAX_VERTS_PER_FACE];
        int face_hit_type;
        vector wall_norm;
        int16_t count;
        bool f_backface;

        if (cur_room->faces[i].flags & FF_NOT_SHELL)
          continue;

        if (!room_manual_AABB(&cur_room->faces[i], &min_xyz, &max_xyz))
          continue;

        f_backface = false;

        for (count = 0; count < cur_room->faces[i].num_verts; count++)
          vertex_ptr_list[count] = &cur_room->verts[cur_room->faces[i].face_verts[count]];

        face_normal = cur_room->faces[i].normal;

        face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, pos, &new_pos, &face_normal,
                                           vertex_ptr_list, cur_room->faces[i].num_verts, 0.0);
        if (!face_hit_type) {
          face_normal *= -1.0f;
          for (count = 0; count < cur_room->faces[i].num_verts; count++)
            vertex_ptr_list[cur_room->faces[i].num_verts - count - 1] =
                &cur_room->verts[cur_room->faces[i].face_verts[count]];

          face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, pos, &new_pos, &face_normal,
                                             vertex_ptr_list, cur_room->faces[i].num_verts, 0.0);
          f_backface = true;
        }

        // If we hit the face...
        if (face_hit_type) {
          if ((cur_dist <= closest_hit_distance && !f_backface) || (cur_dist < closest_hit_distance && f_backface)) {
            closest_hit_distance = cur_dist;

            if (f_backface)
              closest_hit_type = HIT_BACKFACE;
            else
              closest_hit_type = HIT_WALL;
          }
        }
      }
    }
  skip_region:;
    num_faces_ptr++;
    bbf_val++;
    region_max++;
    region_min++;
    bbf_list_ptr++;
  }

  if (closest_hit_type != HIT_WALL) {
    f_in_room = false;
    //		mprintf(0, " in room bool = %d, hit_type = %d\n", (int) f_in_room, closest_hit_type);
  }

  if (!f_in_room && !try_again) {
    try_again = true;
    f_in_room = true;
    goto internal_try_again;
  }

  return f_in_room;
}

// Long rays are 10 segments or longer in length
#define MIN_LONG_RAY (TERRAIN_SIZE * 20.0)

inline bool is_long_xz_ray(fvi_query *fq) {
  if ((fabs(fq->p0->x - fq->p1->x) > MIN_LONG_RAY) || (fabs(fq->p0->z - fq->p1->z) > MIN_LONG_RAY)) {
    return true;
  } else {
    return false;
  }
}

void check_ceiling() {
  vector hit_point;
  float cur_dist;

  vector face_normal = {0.0, -1.0, 0.0};
  vector *vertex_ptr_list[4];
  vector vlist[4];
  int face_hit_type;
  vector wall_norm;
  vector colp;

  // Bail early if hitpnt is not high enough
  if (fvi_query_ptr->rad + fvi_hit_data_ptr->hit_pnt.y < CEILING_HEIGHT)
    return;

  vlist[0].x = 0.0;
  vlist[0].y = CEILING_HEIGHT;
  vlist[0].z = 0.0;
  vlist[1].x = TERRAIN_WIDTH * TERRAIN_SIZE;
  vlist[1].y = CEILING_HEIGHT;
  vlist[1].z = 0.0;
  vlist[2].x = TERRAIN_WIDTH * TERRAIN_SIZE;
  vlist[2].y = CEILING_HEIGHT;
  vlist[2].z = TERRAIN_DEPTH * TERRAIN_SIZE;
  vlist[3].x = 0.0;
  vlist[3].y = CEILING_HEIGHT;
  vlist[3].z = TERRAIN_DEPTH * TERRAIN_SIZE;

  vertex_ptr_list[0] = &vlist[0];
  vertex_ptr_list[1] = &vlist[1];
  vertex_ptr_list[2] = &vlist[2];
  vertex_ptr_list[3] = &vlist[3];

  // Did we hit this face?
  face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0,
                                     &fvi_hit_data_ptr->hit_pnt, &face_normal, vertex_ptr_list, 4, fvi_query_ptr->rad);

  if (face_hit_type) {
    if (cur_dist <= fvi_collision_dist) {
      if ((cur_dist < fvi_collision_dist) || !(fvi_query_ptr->flags & FQ_MULTI_POINT)) {
        fvi_hit_data_ptr->num_hits = 0;

        fvi_hit_data_ptr->hit_pnt = hit_point;
        fvi_collision_dist = cur_dist;
        compute_movement_AABB();
      } else if (fvi_hit_data_ptr->num_hits == MAX_HITS) {
        goto ignore_hit;
      }

      fvi_hit_data_ptr->hit_type[fvi_hit_data_ptr->num_hits] = HIT_CEILING;
      fvi_hit_data_ptr->hit_wallnorm[fvi_hit_data_ptr->num_hits] = wall_norm;
      // fvi_hit_data_ptr->hit_seg = -1; -- set in the fvi_FindIntersection function
      fvi_hit_data_ptr->hit_object[fvi_hit_data_ptr->num_hits] = -1;
      fvi_hit_data_ptr->hit_face[fvi_hit_data_ptr->num_hits] = 0;
      fvi_hit_data_ptr->hit_face_room[fvi_hit_data_ptr->num_hits] = 0;
      fvi_hit_data_ptr->hit_face_pnt[fvi_hit_data_ptr->num_hits] = colp;

      fvi_hit_data_ptr->num_hits++;
    }
  }
ignore_hit:;
}

void make_trigger_face_list(int last_sim_faces) {
  int num_real_collisions;
  int x;

  num_real_collisions = last_sim_faces;

  ASSERT(Fvi_num_recorded_faces <= MAX_RECORDED_FACES);

  for (x = last_sim_faces; x < Fvi_num_recorded_faces; x++) {
    vector face_normal;
    vector *vertex_ptr_list[MAX_VERTS_PER_FACE];
    int face_hit_type;
    vector wall_norm;
    vector colp;
    vector hit_point;
    int16_t count;
    room *cur_room = &Rooms[Fvi_recorded_faces[x].room_index];
    int i = Fvi_recorded_faces[x].face_index;
    float cur_dist;

    for (count = 0; count < cur_room->faces[i].num_verts; count++)
      vertex_ptr_list[count] = &cur_room->verts[cur_room->faces[i].face_verts[count]];
/*
    mprintf(0, "FVI:In trigger %f to %f crossed %f\n",
            fvi_query_ptr->p0->z,
            fvi_hit_data_ptr->hit_pnt.z,
            vertex_ptr_list[0]->z);
*/

    face_normal = cur_room->faces[i].normal;

    face_hit_type =
        check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0, &fvi_hit_data_ptr->hit_pnt,
                           &face_normal, vertex_ptr_list, cur_room->faces[i].num_verts, 0.0f);

    if (face_hit_type) {
      //			mprintf(0, "FVI:hit trigger\n");
      Fvi_recorded_faces[num_real_collisions].face_index = i;
      Fvi_recorded_faces[num_real_collisions++].room_index = Fvi_recorded_faces[x].room_index;
    }
  }

  if (!ROOMNUM_OUTSIDE(fvi_query_ptr->startroom) && !ROOMNUM_OUTSIDE(fvi_hit_data_ptr->hit_room)) {
    int i;

    for (i = 0; i < Rooms[fvi_query_ptr->startroom].num_portals; i++) {
      if (Rooms[fvi_query_ptr->startroom].portals[i].croom == fvi_hit_data_ptr->hit_room) {
        int j;
        bool f_found = false;

        for (j = 0; j < num_real_collisions; j++) {
          if (Fvi_recorded_faces[j].face_index == Rooms[fvi_query_ptr->startroom].portals[i].portal_face &&
              Fvi_recorded_faces[j].room_index == fvi_query_ptr->startroom) {
            f_found = true;
            break;
          }
        }

        if (!f_found) {
          Fvi_recorded_faces[num_real_collisions].face_index = Rooms[fvi_query_ptr->startroom].portals[i].portal_face;
          Fvi_recorded_faces[num_real_collisions++].room_index = fvi_query_ptr->startroom;
        }
      }
    }
  }

  Fvi_num_recorded_faces = num_real_collisions;
}

// Find out if a vector intersects with anything.
// Fills in hit_data, an fvi_info structure (see header file).
// Parms:
//  p0 & startseg 	describe the start of the vector
//  p1 					the end of the vector
//  rad 					the radius of the cylinder
//  thisobjnum 		used to prevent an object with colliding with itself
//  ingore_obj			ignore collisions with this object
//  check_obj_flag	determines whether collisions with objects are checked
// Returns the hit_data->hit_type
#ifndef NED_PHYSICS
extern bool Tracking_FVI;
#endif

int fvi_FindIntersection(fvi_query *fq, fvi_info *hit_data, bool no_subdivision) {
  int i;
  object *this_obj;
  int last_sim_trigger_faces;

  if (fq->startroom == -1) {
    return HIT_NONE;
  }

#ifndef NED_PHYSICS
  if (Tracking_FVI) {
    mprintf(0, "Track FVI - Ray %d, thisobjnum=%d, startroom=%d, rad=%f\n",
            FVI_counter,
            fq->thisobjnum,
            fq->startroom,
            fq->rad);
  }
#endif

  /////////////////////////////////////////
  // Debug Code
#ifdef USE_RTP
  INT64 curr_time;
  RTP_GETCLOCK(curr_time);

  RTP_tSTARTTIME(fvi_time, curr_time);
  RTP_INCRVALUE(fvi_calls, 1);
#endif

  FVI_counter++;
  /////////////////////////////////////////

  // Setup our globals
  fvi_hit_data_ptr = hit_data;
  fvi_query_ptr = fq;

  if (fq->thisobjnum >= 0)
    this_obj = &Objects[fq->thisobjnum];
  else
    this_obj = NULL;

  if (fq->rad == 0.0f)
    fvi_zero_rad = true;
  else
    fvi_zero_rad = false;

  ASSERT(fq != NULL && hit_data != NULL);

  ASSERT(_finite(fq->p1->x) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(fq->p1->y) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(fq->p1->z) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.

  fvi_movement_delta = *fq->p1 - *fq->p0;

  // mprintf(0, "FVI:----New search----\n");
  // mprintf(0, "FVI: P0 is %f, %f, %f\n", XYZ(fq->p0));
  if (fq->flags & FQ_NEW_RECORD_LIST) {
    Fvi_num_recorded_faces = 0;
  }
  last_sim_trigger_faces = Fvi_num_recorded_faces;

  if ((this_obj) && (this_obj->flags & OF_POLYGON_OBJECT) && this_obj->type != OBJ_WEAPON &&
      this_obj->type != OBJ_POWERUP && this_obj->type != OBJ_DEBRIS && this_obj->type != OBJ_ROOM &&
      this_obj->type != OBJ_PLAYER && fq->rad == this_obj->size) {
    if (this_obj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS) {
      fvi_wall_sphere_rad = 0.0f;
      fvi_wall_sphere_offset = Zero_vector;
      fvi_wall_sphere_p0 = *fq->p0;
      fvi_wall_sphere_p1 = *fq->p1;
    } else {
      fvi_wall_sphere_rad = Poly_models[this_obj->rtype.pobj_info.model_num].wall_size;
      fvi_wall_sphere_offset = this_obj->wall_sphere_offset;
      fvi_wall_sphere_p0 = *fq->p0 + fvi_wall_sphere_offset;
      fvi_wall_sphere_p1 = *fq->p1 + fvi_wall_sphere_offset;
    }

    fvi_anim_sphere_rad = Poly_models[this_obj->rtype.pobj_info.model_num].anim_size;
    fvi_anim_sphere_offset = this_obj->anim_sphere_offset;
    fvi_anim_sphere_p0 = *fq->p0 + fvi_anim_sphere_offset;
    fvi_anim_sphere_p1 = *fq->p1 + fvi_anim_sphere_offset;
  } else {
    if ((this_obj) && this_obj->type == OBJ_PLAYER && fq->rad == this_obj->size) {
      fvi_wall_sphere_rad = fq->rad * PLAYER_SIZE_SCALAR;
      if (Players[this_obj->id].flags & (PLAYER_FLAGS_DEAD | PLAYER_FLAGS_DYING))
        fvi_wall_sphere_rad *= 0.5f;
      fvi_wall_sphere_offset = Zero_vector;
      fvi_wall_sphere_p0 = *fq->p0;
      fvi_wall_sphere_p1 = *fq->p1;
    } else if ((this_obj) && this_obj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS) {
      fvi_wall_sphere_rad = 0.0f;
      fvi_wall_sphere_offset = Zero_vector;
      fvi_wall_sphere_p0 = *fq->p0;
      fvi_wall_sphere_p1 = *fq->p1;
    } else {
      fvi_wall_sphere_rad = fq->rad;
      fvi_wall_sphere_offset = Zero_vector;
      fvi_wall_sphere_p0 = *fq->p0;
      fvi_wall_sphere_p1 = *fq->p1;
    }

    fvi_anim_sphere_rad = fq->rad;
    fvi_anim_sphere_offset = Zero_vector;
    fvi_anim_sphere_p0 = *fq->p0;
    fvi_anim_sphere_p1 = *fq->p1;
  }

  fvi_num_rooms_visited = 0;
  fvi_num_cells_visited = 0;
  fvi_num_cells_obj_visited = 0;
  f_check_terrain = true;

  // Initially assume we will hit the endpoint -- Do not compute the end segment unless we actually have no collisions
  hit_data->hit_pnt = *fq->p1;
  hit_data->hit_room = -1;

  hit_data->num_hits = 0;
  hit_data->hit_type[0] = HIT_NONE;
  hit_data->hit_face_room[0] = -1;
  hit_data->hit_object[0] = -1;

  hit_data->n_rooms = 0;
  fvi_collision_dist = vm_VectorDistance(fq->p0, fq->p1) + 0.0000001f;

  // Computes a axis-aligned bounding-box that encompasses the area
  compute_movement_AABB();

  if (ROOMNUM_OUTSIDE(fq->startroom)) {
    // Subdivides long rays
    if ((!no_subdivision) && is_long_xz_ray(fq)) {

      // Save old pointers
      fvi_info *save_fvi_hit_data_ptr = hit_data;
      fvi_query *save_fvi_query_ptr = fq;

      // Copy old data to new data
      fvi_info fvi_new_hit_data = *hit_data;
      fvi_query fvi_new_query = *fq;

      // These are the new "moving" line points
      vector new_p0;
      vector new_p1;

      // Number of whole subdivisions
      int num_subdivisions = vm_VectorDistance(fq->p0, fq->p1) / MIN_LONG_RAY;
      vector sub_dir;     // Direction and magnitude of each subdivision
      int s_hit_type = 0; // Sub-divided hit type

      sub_dir = *fq->p1 - *fq->p0;  // Direction of movement
      vm_NormalizeVector(&sub_dir); // Normalize it
      sub_dir *= MIN_LONG_RAY;      // Scale it to the length of a sub-division

      // Determine the first sub-division
      new_p0 = *fq->p0;
      new_p1 = new_p0 + sub_dir;

      fvi_new_query.p0 = &new_p0;
      fvi_new_query.p1 = &new_p1;

      for (i = 0; i < num_subdivisions; i++) {
        fvi_new_query.startroom = GetTerrainRoomFromPos(&new_p0);

        //				mprintf(0, "S %d F %f,%f,%f to %f,%f,%f\n", i, XYZ(&new_p0), XYZ(&new_p1));
        s_hit_type = fvi_FindIntersection(&fvi_new_query, &fvi_new_hit_data, true);

        fvi_new_query.flags &= (~FQ_NEW_RECORD_LIST);

        if (s_hit_type != HIT_NONE) {
          //mprintf(0, "Hit %d at %f, %f, %f\n", s_hit_type, XYZ(&fvi_new_hit_data.hit_pnt));
          break;
        }

        if (!ROOMNUM_OUTSIDE(fvi_new_hit_data.hit_room))
          break;

        new_p0 = new_p1;
        new_p1 += sub_dir;
      }

      // Check up to the real stopping point
      if (s_hit_type == HIT_NONE) {
        new_p1 = *save_fvi_query_ptr->p1;
        s_hit_type = fvi_FindIntersection(&fvi_new_query, &fvi_new_hit_data, true);
      }

      hit_data = save_fvi_hit_data_ptr;
      fq = save_fvi_query_ptr;

      *hit_data = fvi_new_hit_data;
#ifdef USE_RTP
      RTP_tENDTIME(fvi_time, curr_time);
#endif
      return hit_data->hit_type[0];
    } else
      do_fvi_terrain();
  } else {
    ASSERT(!(Rooms[fq->startroom].flags & RF_EXTERNAL)); // If we hit this, it is not FVI's fault
                                                         // The caller to fvi has a bug
    FVI_room_counter++;
    // do_fvi_rooms(fq->startroom);
    fvi_room(fq->startroom, -1);

    ASSERT(fvi_num_rooms_visited >= 1);
  }

  // Check objects in rooms we visited
  fvi_rooms_objs();

  if (FVI_always_check_ceiling && (fq->flags & FQ_CHECK_CEILING)) {
    check_ceiling();
  }

  // Determine hit seg.

  // Only do this if not running radiosity
  if (!(fq->flags & FQ_NO_RELINK)) {
    if (fvi_num_rooms_visited == 1 && fvi_num_cells_visited == 0) {
      hit_data->hit_room = fvi_rooms_visited[0];
    } else if ((hit_data->hit_type[0] == HIT_WALL || hit_data->hit_type[0] == HIT_TERRAIN) &&
               (fvi_zero_rad ||
                (fvi_query_ptr->thisobjnum >= 0 &&
                 (Objects[fvi_query_ptr->thisobjnum].mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))) &&
               (ROOMNUM_OUTSIDE(hit_data->hit_face_room[0]) ||
                !(Rooms[hit_data->hit_face_room[0]].flags & RF_EXTERNAL))) {
      hit_data->hit_room = hit_data->hit_face_room[0];
    } else {
      bool f_found_room = false;

      for (i = 0; i < fvi_num_rooms_visited && !f_found_room; i++) {
        if (!(Rooms[fvi_rooms_visited[i]].flags & RF_EXTERNAL))
          if (fvi_QuickRoomCheck(&hit_data->hit_pnt, &Rooms[fvi_rooms_visited[i]])) {
            f_found_room = true;
            hit_data->hit_room = fvi_rooms_visited[i];
          }
      }

      if (!f_found_room && fvi_num_cells_visited >= 1) {
        // We must be outside

        // Check the ceiling too
        if (!FVI_always_check_ceiling && (fq->flags & FQ_CHECK_CEILING)) {
          check_ceiling();
        }

        // Determine if we are within the valid terrain bounds
        hit_data->hit_room = GetTerrainRoomFromPos(&hit_data->hit_pnt);
        if (hit_data->hit_room == -1) {
          hit_data->hit_type[0] = HIT_OUT_OF_TERRAIN_BOUNDS;
        }
      } else if (!f_found_room) {
        //				mprintf(0, "Attempting to patch\n");
        for (i = 0; i < fvi_num_rooms_visited && !f_found_room; i++) {
          if (!(Rooms[fvi_rooms_visited[i]].flags & RF_EXTERNAL))
            if (fvi_QuickRoomCheck(&hit_data->hit_pnt, &Rooms[fvi_rooms_visited[i]]), true) {
              f_found_room = true;
              hit_data->hit_room = fvi_rooms_visited[i];
              ASSERT(!(Rooms[hit_data->hit_room].flags & RF_EXTERNAL));
              //				break;
            }
        }

        ASSERT(no_subdivision || f_found_room);
      }
    }

    // Do the ASSERTS for FVI.
    ASSERT(!(hit_data->hit_room == -1 && hit_data->hit_type[0] != HIT_OUT_OF_TERRAIN_BOUNDS));
    ASSERT(!(hit_data->hit_type[0] == HIT_OBJECT && hit_data->hit_object[0] == -1));
  }

  // Clean up the visit list bits
  for (i = 0; i < fvi_num_cells_visited; i++) {
    fvi_terrain_visit_list[fvi_cells_visited[i] >> 3] = 0;
  }

  for (i = 0; i < fvi_num_cells_obj_visited; i++) {
    fvi_terrain_obj_visit_list[fvi_cells_obj_visited[i] >> 3] = 0;
  }

  for (i = 0; i < fvi_num_rooms_visited; i++) {
    fvi_visit_list[fvi_rooms_visited[i] >> 3] = 0;
  }

  if (fvi_query_ptr->flags & FQ_RECORD) {
    make_trigger_face_list(last_sim_trigger_faces);
  }

  hit_data->hit_dist = fvi_collision_dist;

  // Return the hit type
#ifdef USE_RTP
  RTP_tENDTIME(fvi_time, curr_time);
#endif
  return hit_data->hit_type[0];
}

int obj_in_list(int objnum, int *obj_list) {
  int t;

  while ((t = *obj_list) != -1 && t != objnum)
    obj_list++;

  return (t == objnum);
}

// new function for Mike
// note: n_segs_visited must be set to zero before this is called
int sphere_intersects_wall(vector *pnt, int segnum, float rad) {
  /*
          int facemask;
          segment *seg;

          segs_visited[n_segs_visited++] = segnum;

          facemask = GetSegMasks(pnt,segnum,rad).facemask;

          seg = &Segments[segnum];

          if (facemask != 0) {				//on the back of at least one face

                  int side,bit,face;

                  //for each face we are on the back of, check if intersected

                  for (side=0,bit=1;side<6 && facemask>=bit;side++) {

                          for (face=0;face<2;face++,bit<<=1) {

                                  if (facemask & bit) {            //on the back of this face
                                          int face_hit_type;      //in what way did we hit the face?
                                          int num_faces,vertex_list[6];

                                          //did we go through this wall/door?

                                          if ((seg-Segments)==-1)
                                                  Error("segnum == -1 in sphere_intersects_wall()");

                                          create_abs_vertex_lists(&num_faces,vertex_list,seg-Segments,side);

                                          face_hit_type = check_sphere_to_face( pnt,&seg->sides[side],
                                                                                  face,((num_faces==1)?4:3),rad,vertex_list);

                                          if (face_hit_type) {            //through this wall/door
                                                  int child,i;

                                                  //if what we have hit is a door, check the adjoining seg

                                                  child = seg->children[side];

                                                  for (i=0;i<n_segs_visited && child!=segs_visited[i];i++);

                                                  if (i==n_segs_visited) {                //haven't visited here yet

                                                          if (!IS_CHILD(child))
                                                                  return 1;
                                                          else {

                                                                  if (sphere_intersects_wall(pnt,child,rad))
                                                                          return 1;
                                                          }
                                                  }
                                          }
                                  }
                          }
                  }
          }
  */
  return 0;
}

static const int bbox_edges[12][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {3, 4}, {2, 5},
                                      {5, 4}, {4, 7}, {5, 6}, {7, 6}, {7, 0}, {6, 1}};

static const int bbox_faces[6][4] = {{4, 5, 2, 3}, {7, 6, 5, 4}, {0, 1, 6, 7},
                                     {0, 3, 2, 1}, {7, 4, 3, 0}, {1, 2, 5, 3}};
/*
bool BBoxPlaneIntersection(bool fast_exit, vector *collision_point, vector *collision_normal, object *obj, vector
*new_pos, int nv, vector **vertex_ptr_list, vector *face_normal)
{
        vector plane_pnt;
        vector verts[12];
        vector norms[6];
        poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
        int i, j, k;
        vector rel[32];
        float dot[32];
        vector *bbox_vertex_ptr_list[4];

        int num_int_box = 0;
        int num_int_poly = 0;
        vector int_points_box[12];
        vector int_points_poly[32];
        int16_t int_faces = 0;
        bool f_int_box = false;
        bool f_int_poly = false;


        verts[0] = (obj->orient.rvec * pm->mins.x) +
                                  (obj->orient.uvec * pm->maxs.y) +
                                  (obj->orient.fvec * pm->mins.z);

        verts[1] = (obj->orient.rvec * pm->mins.x) +
                                  (obj->orient.uvec * pm->mins.y) +
                                  (obj->orient.fvec * pm->mins.z);

        verts[2] = (obj->orient.rvec * pm->maxs.x) +
                                  (obj->orient.uvec * pm->mins.y) +
                                  (obj->orient.fvec * pm->mins.z);

        verts[3] = (obj->orient.rvec * pm->maxs.x) +
                                  (obj->orient.uvec * pm->maxs.y) +
                                  (obj->orient.fvec * pm->mins.z);

        verts[4] = (obj->orient.rvec * pm->maxs.x) +
                                  (obj->orient.uvec * pm->maxs.y) +
                                  (obj->orient.fvec * pm->maxs.z);

        verts[5] = (obj->orient.rvec * pm->maxs.x) +
                                  (obj->orient.uvec * pm->mins.y) +
                                  (obj->orient.fvec * pm->maxs.z);

        verts[6] = (obj->orient.rvec * pm->mins.x) +
                                  (obj->orient.uvec * pm->mins.y) +
                                  (obj->orient.fvec * pm->maxs.z);

        verts[7] = (obj->orient.rvec * pm->mins.x) +
                                  (obj->orient.uvec * pm->maxs.y) +
                                  (obj->orient.fvec * pm->maxs.z);


//	mprintf(0, "START\n");
        for(i = 0; i < 8; i++)
        {
                verts[i] += *new_pos;
//		mprintf(0, "%f %f %f\n", XYZ(&verts[i]));
        }
//	mprintf(0, "END\n");

        norms[0] = obj->orient.rvec;
        norms[1] = obj->orient.fvec;
        norms[2] = -obj->orient.rvec;
        norms[3] = -obj->orient.fvec;
        norms[4] = obj->orient.uvec;
        norms[5] = -obj->orient.uvec;

        for(i = 0; i < 8; i++)
        {
                rel[i] = verts[i] - *vertex_ptr_list[0];
                dot[i] = rel[i] * (*face_normal);
        }

        // Get Plane intersection point
        for(i = 0; i < 12; i++)
        {
                vector movement;
                bool found;
                float nmovement;

                found = false;

                if(dot[bbox_edges[i][0]] > 0.0f && dot[bbox_edges[i][1]] < 0.0f)
                {
                        movement = verts[bbox_edges[i][1]] - verts[bbox_edges[i][0]];

                        nmovement = -(movement * *face_normal);

                        plane_pnt = verts[bbox_edges[i][0]];
                        plane_pnt += movement * (dot[bbox_edges[i][0]]/nmovement);

                        f_int_poly = true;
                        found = true;
                }
                else if(dot[bbox_edges[i][0]] < 0.0f && dot[bbox_edges[i][1]] > 0.0f)
                {
                        movement = verts[bbox_edges[i][0]] - verts[bbox_edges[i][1]];

                        nmovement = -(movement * *face_normal);

                        plane_pnt = verts[bbox_edges[i][1]];
                        plane_pnt += movement * (dot[bbox_edges[i][1]]/nmovement);

                        f_int_poly = true;
                        found = true;
                }

                if((found) && (!check_point_to_face(&plane_pnt, face_normal, nv, vertex_ptr_list)))
                {
                        // we hit it
//			mprintf(0, "BBOX Collided with a plane\n");
                        if(fast_exit)
                                return true;

                        int_points_poly[num_int_poly++] = plane_pnt;
                }
        }

        for(j = 0; j < 6; j++)
        {
                // Now the other way
                // Get Plane intersection point
                for(i = 0; i < nv; i++)
                {
                        rel[i] = *vertex_ptr_list[i] - verts[bbox_faces[j][0]];
                        dot[i] = rel[i] * (norms[j]);
                }

                for(i = 0; i < nv; i++)
                {
                        vector movement;
                        bool found;
                        float nmovement;

                        found = false;

                        if(dot[i] > 0.0f && dot[(i+1)%nv] < 0.0f)
                        {
                                movement = *vertex_ptr_list[(i+1)%nv] - *vertex_ptr_list[i];

                                nmovement = -(movement * norms[j]);

                                plane_pnt = *vertex_ptr_list[i];
                                plane_pnt += movement * (dot[i]/nmovement);

                                f_int_box = true;
                                found = true;
                        }
                        else if(dot[i] < 0.0f && dot[(i+1)%nv] > 0.0f)
                        {
                                movement = *vertex_ptr_list[i] - *vertex_ptr_list[(i+1)%nv];

                                nmovement = -(movement * norms[j]);

                                plane_pnt = *vertex_ptr_list[(i+1)%nv];
                                plane_pnt += movement * (dot[(i+1)%nv]/nmovement);

                                f_int_box = true;
                                found = true;
                        }

                        if(found)
                        {

                                for(k = 0; k < 4; k++)
                                {
                                        bbox_vertex_ptr_list[k] = &verts[bbox_faces[j][k]];
                                }

                                if (!check_point_to_face(&plane_pnt, &norms[j], 4, bbox_vertex_ptr_list))
                                {
                                        // we hit it
        //				mprintf(0, "BBOX Collided with a plane\n");
                                        if(fast_exit)
                                                return true;
                                        int_faces |= (0x01 << j);
                                        int_points_box[num_int_box++] = plane_pnt;
                                }
                        }
                }
        }

        if(num_int_poly || num_int_box)
        {
                vm_MakeZero(collision_point);

                for(i = 0; i < num_int_poly; i++)
                {
                        *collision_point += int_points_poly[i];
                }

                for(i = 0; i < num_int_box; i++)
                {
                        *collision_point += int_points_box[i];
                }

                *collision_point /= (float)(num_int_poly + num_int_box);
                *collision_normal = *face_normal;

                return true;
        }

        return false;
}
*/

vector PointSpeed(object *obj, vector *pos, matrix *orient, vector *rotvel, vector *velocity) {
  vector r1 = *pos - obj->pos;
  vector w1;
  vector n1;
  float temp1;

  matrix o_t1 = *orient;

  vm_TransposeMatrix(&o_t1);
  vector cmp1 = *rotvel * o_t1;
  ConvertEulerToAxisAmount(&cmp1, &n1, &temp1);

  n1 *= temp1;

  if (temp1 != 0.0f) {
    vm_CrossProduct(&w1, &n1, &r1);
  } else {
    w1 = Zero_vector;
  }

  return *velocity + w1;
}

// MTS: only used in this file.
// Hacked for some initial testing
bool BBoxPlaneIntersection(bool fast_exit, vector *collision_point, vector *collision_normal, object *obj,
                           vector *new_pos, int nv, vector **vertex_ptr_list, vector *face_normal, matrix *orient,
                           vector *rotvel, vector *velocity) {
  vector plane_pnt;
  vector verts[12];
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  int i;
  vector rel[32];
  float dot[32];
  bool collidable[32];

  int num_int_box = 0;
  vector int_points_box[12];

  verts[0] = (orient->rvec * pm->mins.x) + (orient->uvec * pm->maxs.y) + (orient->fvec * pm->mins.z);

  verts[1] = (orient->rvec * pm->mins.x) + (orient->uvec * pm->mins.y) + (orient->fvec * pm->mins.z);

  verts[2] = (orient->rvec * pm->maxs.x) + (orient->uvec * pm->mins.y) + (orient->fvec * pm->mins.z);

  verts[3] = (orient->rvec * pm->maxs.x) + (orient->uvec * pm->maxs.y) + (orient->fvec * pm->mins.z);

  verts[4] = (orient->rvec * pm->maxs.x) + (orient->uvec * pm->maxs.y) + (orient->fvec * pm->maxs.z);

  verts[5] = (orient->rvec * pm->maxs.x) + (orient->uvec * pm->mins.y) + (orient->fvec * pm->maxs.z);

  verts[6] = (orient->rvec * pm->mins.x) + (orient->uvec * pm->mins.y) + (orient->fvec * pm->maxs.z);

  verts[7] = (orient->rvec * pm->mins.x) + (orient->uvec * pm->maxs.y) + (orient->fvec * pm->maxs.z);

  for (i = 0; i < 8; i++) {
    verts[i] += *new_pos;
  }

  vector xxx_normal = Zero_vector;
  xxx_normal.y = 1.0f;

  for (i = 0; i < 8; i++) {
    rel[i] = verts[i];
    dot[i] = rel[i] * (xxx_normal);
  }

  for (i = 0; i < 8; i++) {
    collidable[i] =
        true; //(PointSpeed(&Objects[fvi_query_ptr->thisobjnum], &verts[i], orient, rotvel, velocity).y < 0.0);
  }

  // Get Ground intersection points
  for (i = 0; i < 12; i++) {
    vector movement;
    bool found;
    float nmovement;

    found = false;

    if (dot[bbox_edges[i][0]] > 0.0f && dot[bbox_edges[i][1]] < 0.0f && collidable[bbox_edges[i][1]]) {
      movement = verts[bbox_edges[i][1]] - verts[bbox_edges[i][0]];

      nmovement = -(movement * *face_normal);

      plane_pnt = verts[bbox_edges[i][0]];
      plane_pnt += movement * (dot[bbox_edges[i][0]] / nmovement);

      found = true;
    } else if (dot[bbox_edges[i][0]] < 0.0f && dot[bbox_edges[i][1]] > 0.0f && collidable[bbox_edges[i][0]]) {
      movement = verts[bbox_edges[i][0]] - verts[bbox_edges[i][1]];

      nmovement = -(movement * *face_normal);

      plane_pnt = verts[bbox_edges[i][1]];
      plane_pnt += movement * (dot[bbox_edges[i][1]] / nmovement);

      found = true;
    }

    if (found) {
      if (fast_exit)
        return true;

      int_points_box[num_int_box++] = plane_pnt;
    }
  }

  if (num_int_box) {
    vm_MakeZero(collision_point);

    for (i = 0; i < num_int_box; i++) {
      *collision_point += int_points_box[i];
    }

    *collision_point /= (float)(num_int_box);
    *collision_normal = xxx_normal;

    //		mprintf(0, "BBox %d hits\n", num_int_box);

    return true;
  }

  return false;
}

// Returns true if the object is through any walls
int object_intersects_wall(object *objp) {
  //	n_segs_visited = 0;
  //
  //	return sphere_intersects_wall(&objp->pos,objp->segnum,objp->size);
  ASSERT(0);
  return 0;
}

void check_hit_obj(int objnum) {
  vector hit_point;
  float cur_dist;
  const object *obj = &Objects[objnum];
  bool f_x = false;
  int collision_type;
  int m_obj_index = fvi_query_ptr->thisobjnum;
  object *m_obj = &Objects[m_obj_index];

  if (!(fvi_query_ptr->flags & FQ_CHECK_OBJS) && (obj->type != OBJ_ROOM))
    return;
  if ((fvi_query_ptr->flags & (FQ_IGNORE_EXTERNAL_ROOMS)) && (obj->type == OBJ_ROOM))
    return;

  if (obj->flags & OF_NO_OBJECT_COLLISIONS)
    return;

  if (!(obj->flags & OF_DEAD)) {
    if (!(m_obj_index == objnum)) {
      if (!((m_obj_index > -1) && ((collision_type = CollisionResult[m_obj->type][obj->type]) == RESULT_NOTHING) &&
            (CollisionResult[obj->type][m_obj->type] == RESULT_NOTHING))) {
        // Account for ray casting
        if (!(m_obj_index > -1) && (CollisionRayResult[obj->type] == RESULT_NOTHING))
          return;

        if (object_movement_AABB(&Objects[objnum])) {
#ifndef NED_PHYSICS
#ifdef _DEBUG
          if (Physics_player_verbose) {
            if (OBJNUM(Player_object) == objnum && m_obj_index != -1) {
              mprintf(0, "FVI: %d AABB with player\n", m_obj_index);
            } else if (Player_object == m_obj) {
              mprintf(0, "FVI: Player AABB with %d\n", objnum);
            }
          }
#endif
#endif

          if (fvi_query_ptr->ignore_obj_list == NULL || !obj_in_list(objnum, fvi_query_ptr->ignore_obj_list)) {
            if (!ObjectsAreRelated(objnum, m_obj_index)) {

              if (m_obj_index < 0) {
                switch (obj->type) {
                case OBJ_ROOM:
                  if (fvi_query_ptr->flags & FQ_EXTERNAL_ROOMS_AS_SPHERE)
                    collision_type = RESULT_CHECK_SPHERE_SPHERE;
                  else
                    collision_type = RESULT_CHECK_SPHERE_ROOM;
                  break;
                case OBJ_PLAYER:
                  if (fvi_query_ptr->flags & FQ_PLAYERS_AS_SPHERE)
                    collision_type = RESULT_CHECK_SPHERE_SPHERE;
                  else
                    collision_type = RESULT_CHECK_SPHERE_POLY;
                  break;
                case OBJ_ROBOT:
                  if (fvi_query_ptr->flags & FQ_ROBOTS_AS_SPHERE)
                    collision_type = RESULT_CHECK_SPHERE_SPHERE;
                  else
                    collision_type = RESULT_CHECK_SPHERE_POLY;
                  break;

                default:
                  collision_type = RESULT_CHECK_SPHERE_POLY;
                  break;
                }
              } else {
                if (((m_obj->type == OBJ_CLUTTER) && (m_obj->mtype.phys_info.flags & PF_GRAVITY) &&
                     (m_obj->movement_type == MT_PHYSICS) && (obj->type == OBJ_PLAYER)) ||
                    ((obj->type == OBJ_CLUTTER) && (obj->mtype.phys_info.flags & PF_GRAVITY) &&
                     (obj->movement_type == MT_PHYSICS) && (m_obj->type == OBJ_PLAYER))) {
                  collision_type = RESULT_CHECK_SPHERE_SPHERE;
                }

                // Ignore robot collisions if it is specified
                if ((m_obj->mtype.phys_info.flags & PF_NO_SAME_COLLISIONS) && (obj->type == m_obj->type) &&
                    (obj->id == m_obj->id))
                  return;

                // Ignore robot collisions if it is specified
                if ((m_obj->mtype.phys_info.flags & PF_NO_ROBOT_COLLISIONS) &&
                    (obj->type == OBJ_CLUTTER || obj->type == OBJ_ROBOT || (obj->type == OBJ_BUILDING && obj->ai_info)))
                  return;

                if ((obj->mtype.phys_info.flags & PF_NO_ROBOT_COLLISIONS) &&
                    (obj->type == OBJ_CLUTTER || m_obj->type == OBJ_ROBOT ||
                     (m_obj->type == OBJ_BUILDING && m_obj->ai_info)))
                  return;

                if ((m_obj->mtype.phys_info.flags & PF_NO_DOOR_COLLISIONS)) {
                  if (obj->movement_type != MT_PHYSICS && obj->movement_type != MT_WALKING) {
                    return;
                  }
                }
              }

              if (fvi_query_ptr->flags & FQ_IGNORE_NON_LIGHTMAP_OBJECTS)
                if (obj->lighting_render_type != LRT_LIGHTMAPS && obj->type != OBJ_ROOM)
                  return;

              if (fvi_query_ptr->flags & FQ_IGNORE_POWERUPS)
                if (obj->type == OBJ_POWERUP)
                  return;

              if (fvi_query_ptr->flags & FQ_IGNORE_WEAPONS)
                if (obj->type == OBJ_WEAPON || obj->type == OBJ_FIREBALL || obj->type == OBJ_SHARD ||
                    obj->type == OBJ_SHOCKWAVE)
                  return;

              if (fvi_query_ptr->flags & FQ_IGNORE_MOVING_OBJECTS)
                if (obj->movement_type == MT_PHYSICS || obj->movement_type == MT_WALKING)
                  return;

              if (obj->type != OBJ_ROOM) {
                if (fvi_query_ptr->flags & FQ_ONLY_PLAYER_OBJ)
                  if (obj->type != OBJ_PLAYER)
                    return;

                if (fvi_query_ptr->flags & FQ_ONLY_DOOR_OBJ)
                  if (obj->type != OBJ_DOOR)
                    return;
              }

              if (obj->type == OBJ_PLAYER && (fvi_query_ptr->flags & FQ_PLAYERS_AS_SPHERE))
                collision_type = RESULT_CHECK_SPHERE_SPHERE;
              if (obj->type == OBJ_ROBOT && (fvi_query_ptr->flags & FQ_ROBOTS_AS_SPHERE))
                collision_type = RESULT_CHECK_SPHERE_SPHERE;

              switch (collision_type) {
              case RESULT_CHECK_BBOX_ROOM:
              case RESULT_CHECK_SPHERE_ROOM: {
                ASSERT(obj->type == OBJ_ROOM);

                fvi_room(obj->id, -1, objnum);
              } break;

              case RESULT_CHECK_SPHERE_POLY:
              case RESULT_CHECK_BBOX_POLY: {
                //									float dist;
                //									vector pos;
                //									float size;

                if (!(obj->flags & OF_POLYGON_OBJECT))
                  goto sphere_sphere;

                //									pos = obj->pos +
                // obj->anim_sphere_offset; 									dist =
                // vm_VectorDistance(&pos, &fvi_anim_sphere_p0);
                // size = Poly_models[obj->rtype.pobj_info.model_num].anim_size;

                //									if((dist <= size +
                // fvi_anim_sphere_rad)
                //										||
                // check_vector_to_object(&hit_point, &cur_dist, &fvi_anim_sphere_p0,&fvi_anim_sphere_p1,
                // fvi_anim_sphere_rad, &Objects[objnum], &Objects[fvi_query_ptr->thisobjnum])
                //									{
                fvi_curobj = objnum;
                fvi_moveobj = m_obj_index;
                if (PolyCollideObject(&Objects[objnum])) {
                  compute_movement_AABB();
                }
                //									}
              } break;

              case RESULT_CHECK_POLY_SPHERE:
              case RESULT_CHECK_POLY_BBOX: {
                if (!(m_obj->flags & OF_POLYGON_OBJECT))
                  goto sphere_sphere;

                // Save the Fvi information pointers.
                fvi_info *temp_fvi_hit_data_ptr = fvi_hit_data_ptr;
                fvi_query *temp_fvi_query_ptr = fvi_query_ptr;
                fvi_info hit_info;
                fvi_query fq;
                float saved_dist = fvi_collision_dist;

                vector relative_pos = obj->pos + (*fvi_query_ptr->p0 - *fvi_query_ptr->p1);

                fvi_hit_data_ptr = &hit_info;
                fvi_query_ptr = &fq;

                fq.p0 = &Objects[objnum].pos;
                fq.p1 = &relative_pos;
                fq.rad = obj->size;
                fq.thisobjnum = objnum;
                fq.flags = 0;

                hit_info.num_hits = 0;
                hit_info.hit_type[0] = HIT_NONE;

                fvi_curobj = m_obj_index;
                fvi_moveobj = objnum;
                PolyCollideObject(&Objects[temp_fvi_query_ptr->thisobjnum]);

                fvi_hit_data_ptr = temp_fvi_hit_data_ptr;
                fvi_query_ptr = temp_fvi_query_ptr;

                if (hit_info.hit_type[0] != HIT_NONE) {
                  int counter;

                  if (saved_dist != fvi_collision_dist) {
                    fvi_hit_data_ptr->hit_pnt = m_obj->pos + (obj->pos - hit_info.hit_pnt);
                    compute_movement_AABB();
                  }

                  fvi_hit_data_ptr->num_hits = 0;

                  for (counter = 0; counter < hit_info.num_hits; counter++) {
                    fvi_hit_data_ptr->hit_type[fvi_hit_data_ptr->num_hits] = HIT_OBJECT;
                    fvi_hit_data_ptr->hit_object[fvi_hit_data_ptr->num_hits] = objnum;
                    fvi_hit_data_ptr->hit_face_pnt[fvi_hit_data_ptr->num_hits] =
                        fvi_hit_data_ptr->hit_pnt + (hit_info.hit_face_pnt[counter] - m_obj->pos);
                    fvi_hit_data_ptr->hit_wallnorm[fvi_hit_data_ptr->num_hits] = -hit_info.hit_wallnorm[counter];
                    fvi_hit_data_ptr->hit_subobject[0] = hit_info.hit_subobject[0];
                    fvi_hit_data_ptr->hit_face[0] = hit_info.hit_face[0];
                    fvi_hit_data_ptr->hit_subobj_fvec = hit_info.hit_subobj_fvec;
                    fvi_hit_data_ptr->hit_subobj_uvec = hit_info.hit_subobj_uvec;
                    fvi_hit_data_ptr->hit_subobj_pos = hit_info.hit_subobj_pos;

                    fvi_hit_data_ptr->num_hits++;
                  }

                  ASSERT(!(fvi_hit_data_ptr->num_hits > 1 && !(fvi_query_ptr->flags & FQ_MULTI_POINT)));
                }
              } break;

              case RESULT_CHECK_SPHERE_SPHERE:
              case RESULT_CHECK_BBOX_BBOX:
              case RESULT_CHECK_SPHERE_BBOX:
              case RESULT_CHECK_BBOX_SPHERE: {
              sphere_sphere:
                if (check_vector_to_object(&hit_point, &cur_dist, &fvi_anim_sphere_p0, &fvi_anim_sphere_p1,
                                           fvi_anim_sphere_rad, &Objects[objnum], &Objects[m_obj_index])) {
                  //	hit_point

                  if (cur_dist < fvi_collision_dist) {

                    vector pos_hit;
                    float hit_obj_size;
                    vector hit_obj_pos;

                    hit_obj_pos = obj->pos + obj->anim_sphere_offset;
                    pos_hit = hit_point - hit_obj_pos;

                    if ((obj->flags & OF_POLYGON_OBJECT) && obj->type != OBJ_ROOM && obj->type != OBJ_WEAPON &&
                        obj->type != OBJ_POWERUP && obj->type != OBJ_DEBRIS && obj->type != OBJ_PLAYER) {
                      hit_obj_size = Poly_models[obj->rtype.pobj_info.model_num].anim_size;
                    } else {
                      hit_obj_size = obj->size;
                    }

                    pos_hit = hit_obj_pos + pos_hit * (hit_obj_size / (hit_obj_size + fvi_anim_sphere_rad));
                    ASSERT(hit_obj_size + fvi_anim_sphere_rad > 0.0f);

                    fvi_collision_dist = cur_dist;
                    fvi_hit_data_ptr->hit_pnt = hit_point - fvi_anim_sphere_offset;
                    compute_movement_AABB();
                    fvi_hit_data_ptr->num_hits = 1;

                    fvi_hit_data_ptr->hit_object[0] = objnum;
                    fvi_hit_data_ptr->hit_type[0] = HIT_OBJECT;
                    fvi_hit_data_ptr->hit_face_pnt[0] = pos_hit;
                    fvi_hit_data_ptr->hit_wallnorm[0] = (pos_hit - hit_obj_pos) / hit_obj_size;
                    ASSERT(hit_obj_size > 0.0f);

                    ASSERT(objnum != -1);
                  }
                }
              } break;

              default: {
                mprintf(0, "Collision of type %d is not programmed yet", collision_type);
              } break;
              }
            } else {
#ifndef NED_PHYSICS
#ifdef _DEBUG
              if (Physics_player_verbose) {
                if (OBJNUM(Player_object) == objnum || Player_object == m_obj) {
                  mprintf(0, "Related\n");
                }
              }
#endif
#endif
            }
          } else {
#ifndef NED_PHYSICS
#ifdef _DEBUG
            if (Physics_player_verbose) {
              if (OBJNUM(Player_object) == objnum || Player_object == m_obj) {
                mprintf(0, "Ignore list\n");
              }
            }
#endif
#endif
          }
        }
      }
    } else {
#ifndef NED_PHYSICS
#ifdef _DEBUG
      if (Physics_player_verbose) {
        if (objnum != m_obj_index) {
          if (OBJNUM(Player_object) == objnum || Player_object == m_obj) {
            mprintf(0, "Result nothing %d %d\n", objnum, m_obj_index);
          }
        }
      }
#endif
#endif
    }
  } else {
#ifndef NED_PHYSICS
#ifdef _DEBUG
    if (Physics_player_verbose) {
      if (OBJNUM(Player_object) == objnum || Player_object == m_obj) {
        mprintf(0, "Dead %d %d\n", objnum, m_obj_index);
      }
    }
#endif
#endif
  }

  ASSERT(!(fvi_hit_data_ptr->num_hits > 1 && !(fvi_query_ptr->flags & FQ_MULTI_POINT)));
}

/*	// Check each terrain cell
        for(i = 0; i < fvi_num_cells_visited; i++)
        {
                int j_start;
                int j_end;

                start_node = GetColTerrainSegFromTerrainSeg(fvi_cells_visited[i]);
                ASSERT(start_node != -1);

                if(start_node%COL_TERRAIN_WIDTH) j_start = -1;
                else j_start = 0;

                if(start_node%COL_TERRAIN_WIDTH < (COL_TERRAIN_WIDTH - 1)) j_end = 1;
                else j_end = 0;

                for(j = j_start; j <= j_end; j++)
                {
                        int k_start;
                        int k_end;

                        if(start_node/COL_TERRAIN_WIDTH) k_start = -1;
                        else k_start = 0;

                        if(start_node/COL_TERRAIN_WIDTH < (COL_TERRAIN_DEPTH - 1)) k_end = 1;
                        else k_end = 0;

                        for(k = k_start; k <= k_end; k++)
                        {
                                int cur_col_node = start_node + j + (k * COL_TERRAIN_WIDTH);

                                // Only check each col cell once.
                                if((fvi_col_terrain_visit_list[cur_col_node >> 3] & (0x01 << (cur_col_node % 8))) == 0)
                                {
                                        ASSERT(fvi_num_col_cells_visited <= MAX_CELLS_VISITED);

                                        fvi_col_terrain_visit_list[cur_col_node >> 3] |= 0x01 << (cur_col_node % 8);
                                        fvi_col_cells_visited[fvi_num_col_cells_visited] = cur_col_node;
                                        fvi_num_col_cells_visited++;

                                        for (objnum = Col_terrain_seg[cur_col_node].objects; objnum != -1; objnum =
   Objects[objnum].next)
                                        {
                                                if(!(Objects[objnum].flags & OF_BIG_OBJECT))
                                                        check_hit_obj(objnum);
                                        }
                                }
                        }
                }
        }
*/

#define MAX_BBOX_GROUND_TOLERANCE 0.0001

/*
void DoLinearApprox(vector *collision_point, vector *collision_normal, float *hit_dist, float *hit_interval, vector
*movement_dir, vector *p0, object *obj, int nv, vector **vertex_ptr_list, vector *face_normal)
{
        vector end_pos;
        bool hit;

        *hit_interval /= 2.0f;
        end_pos = *p0 + ((*hit_interval + *hit_dist)* *movement_dir);

        float frametime = fvi_query_ptr->frametime * ((*hit_interval + *hit_dist)/vm_VectorDistance(fvi_query_ptr->p0,
fvi_query_ptr->p1)); matrix orient = *fvi_query_ptr->o_orient; vector rotvel = *fvi_query_ptr->o_rotvel; vector rotforce
= *fvi_query_ptr->o_rotthrust; angle turnroll = *fvi_query_ptr->o_turnroll;
        //vector thrust = *fvi_query_ptr->o_thrust;
        vector velocity = *fvi_query_ptr->o_velocity;
        //vector movement_pos;
        //vector movement_vec;
        //vector test;

        float sim_time_remaining = frametime;
        float old_sim_time_remaining = frametime;

        PhysicsDoSimRot(&Objects[fvi_query_ptr->thisobjnum], frametime, &orient, &rotforce, &rotvel, &turnroll);
//	PhysicsDoSimLinear(&Objects[fvi_query_ptr->thisobjnum], &Objects[fvi_query_ptr->thisobjnum].pos, &thrust,
&velocity, &movement_vec, &movement_pos, frametime);


        vector moved_vec_n;
        float attempted_dist,actual_dist;

        // Save results of this simulation
        old_sim_time_remaining = sim_time_remaining;
        moved_vec_n = end_pos - *p0;
        if(moved_vec_n != Zero_vector)
        {
                actual_dist = vm_NormalizeVector(&moved_vec_n);
        }
        else
        {
                actual_dist = 0.0f;
        }

        // Compute more results of this simulation
        attempted_dist = vm_VectorDistance(fvi_query_ptr->p0, fvi_query_ptr->p1);
        sim_time_remaining = sim_time_remaining * ((attempted_dist - actual_dist) / attempted_dist);
        float moved_time = old_sim_time_remaining - sim_time_remaining;

        if (sim_time_remaining < 0.0)
        {
                sim_time_remaining = 0.0;
                moved_time = old_sim_time_remaining;
        }

        if (sim_time_remaining > old_sim_time_remaining)
        {
                sim_time_remaining = old_sim_time_remaining;
                moved_time = 0.0;
        }

        if(old_sim_time_remaining > 0.0)
        {
                velocity = fvi_hit_data_ptr->hit_velocity * (moved_time / old_sim_time_remaining) + velocity *
(sim_time_remaining / old_sim_time_remaining);
        }
        else
        {
                velocity = fvi_hit_data_ptr->hit_velocity;
        }

        hit = BBoxPlaneIntersection(false, collision_point, collision_normal, obj, &end_pos, nv, vertex_ptr_list,
face_normal, &orient, &rotvel, &velocity);

        if(!hit)
        {
                *hit_dist += *hit_interval;
        }
        else
        {
                fvi_hit_data_ptr->hit_pnt = end_pos;
                fvi_hit_data_ptr->hit_turnroll = turnroll;
                fvi_hit_data_ptr->hit_orient = orient;
                fvi_hit_data_ptr->hit_rotvel = rotvel;
        }

        if(*hit_interval > MAX_BBOX_GROUND_TOLERANCE)
                DoLinearApprox(collision_point, collision_normal, hit_dist, hit_interval, movement_dir, p0, obj, nv,
vertex_ptr_list, face_normal);

        return;
}
*/
// checks for collisions within a given terrain node (fvi_sub minus the recursiveness).
// If f_check_local_nodes is set, it will look in surrounding nodes.
inline void check_terrain_node(int cur_node, bool f_check_local_nodes, bool f_check_ground) {
  vector hit_point;
  float cur_dist;
  int check_x, check_y;
  int tercheck_x, tercheck_y;
  int new_node;
  int xcounter, ycounter;
  int xstart, xend;
  int ystart, yend;
  int terxstart, terxend;
  int terystart, teryend;
  int i;
  int objnum;
  bool f_check_next_ground;
  object *this_obj;

  if (fvi_query_ptr->thisobjnum >= 0)
    this_obj = &Objects[fvi_query_ptr->thisobjnum];
  else
    this_obj = NULL;

  // Object checks
  if ((fvi_terrain_obj_visit_list[cur_node >> 3] & (0x01 << (cur_node % 8))) == 0) {
    ASSERT(cur_node >= 0 && cur_node < TERRAIN_WIDTH * TERRAIN_DEPTH);
    ASSERT(fvi_num_cells_obj_visited < MAX_CELLS_VISITED);
    fvi_terrain_obj_visit_list[cur_node >> 3] |= 0x01 << (cur_node % 8);
    fvi_cells_obj_visited[fvi_num_cells_obj_visited] = cur_node;
    fvi_num_cells_obj_visited++;

    if (fvi_query_ptr->flags & FQ_CHECK_OBJS) {
      for (objnum = Terrain_seg[cur_node].objects; objnum != -1; objnum = Objects[objnum].next) {
        ASSERT(objnum != -1);
        if (!(Objects[objnum].flags & OF_BIG_OBJECT))
          check_hit_obj(objnum);
      }
    } else {

      if (!(fvi_query_ptr->flags & FQ_IGNORE_EXTERNAL_ROOMS))
        for (objnum = Terrain_seg[cur_node].objects; objnum != -1; objnum = Objects[objnum].next) {
          ASSERT(objnum != -1);
          if ((Objects[objnum].type == OBJ_ROOM) && !(Objects[objnum].flags & OF_BIG_OBJECT))
            check_hit_obj(objnum);
        }
    }
  }

  // Terrain node checks
  if (f_check_ground) {
    int lod_x = (cur_node % TERRAIN_WIDTH) >> 2;
    int lod_z = (cur_node / TERRAIN_WIDTH) >> 2;

    ASSERT(cur_node >= 0 && cur_node < TERRAIN_WIDTH * TERRAIN_DEPTH);
    ASSERT((fvi_terrain_visit_list[cur_node >> 3] & (0x01 << (cur_node % 8))) == 0);
    ASSERT(fvi_num_cells_visited < MAX_CELLS_VISITED);

    // Mark the current node as visited
    fvi_terrain_visit_list[cur_node >> 3] |= 0x01 << (cur_node % 8);
    fvi_cells_visited[fvi_num_cells_visited] = cur_node;
    fvi_num_cells_visited++;

    if (((float)Terrain_max_height_int[6][lod_z * (TERRAIN_WIDTH >> 2) + lod_x] * TERRAIN_HEIGHT_INCREMENT +
                 fvi_query_ptr->rad >=
             fvi_query_ptr->p0->y ||
         (float)Terrain_max_height_int[6][lod_z * (TERRAIN_WIDTH >> 2) + lod_x] * TERRAIN_HEIGHT_INCREMENT +
                 fvi_query_ptr->rad >=
             fvi_query_ptr->p1->y) &&
        !(Terrain_seg[cur_node].flags & TF_INVISIBLE) &&
        !(fvi_query_ptr->flags & (FQ_IGNORE_WALLS | FQ_IGNORE_TERRAIN))) {

      // check this node for ground collision
      for (i = 0; i < 2; i++) {
        vector face_normal;
        vector *vertex_ptr_list[4];
        vector vlist[3];
        int face_hit_type;
        vector wall_norm;
        vector colp;

        // There are two triangles per node.  Check each of them for collision.
        if (i == 0) {
          int cellnum_upper_right = cur_node + TERRAIN_WIDTH + 1;
          int cellnum_right = cur_node + 1;

          vlist[0].x = (cur_node % TERRAIN_WIDTH) * TERRAIN_SIZE;
          vlist[0].y = Terrain_seg[cur_node].y;
          vlist[0].z = (cur_node / TERRAIN_WIDTH) * TERRAIN_SIZE;

          vlist[1].x = (cellnum_upper_right % TERRAIN_WIDTH) * TERRAIN_SIZE;
          if (cellnum_upper_right < TERRAIN_WIDTH * TERRAIN_DEPTH)
            vlist[1].y = Terrain_seg[cellnum_upper_right].y;
          else
            vlist[1].y = 0.0;
          vlist[1].z = (cellnum_upper_right / TERRAIN_WIDTH) * TERRAIN_SIZE;

          vlist[2].x = (cellnum_right % TERRAIN_WIDTH) * TERRAIN_SIZE;
          if (cellnum_right < TERRAIN_WIDTH * TERRAIN_DEPTH)
            vlist[2].y = Terrain_seg[cellnum_right].y;
          else
            vlist[2].y = 0.0;
          vlist[2].z = (cellnum_right / TERRAIN_WIDTH) * TERRAIN_SIZE;

          vertex_ptr_list[0] = &vlist[0];
          vertex_ptr_list[1] = &vlist[1];
          vertex_ptr_list[2] = &vlist[2];

          face_normal = TerrainNormals[MAX_TERRAIN_LOD - 1][cur_node].normal2;

        } else {
          int cellnum_upper = cur_node + TERRAIN_WIDTH;
          int cellnum_upper_right = cur_node + TERRAIN_WIDTH + 1;

          vlist[0].x = (cur_node % TERRAIN_WIDTH) * TERRAIN_SIZE;
          vlist[0].y = Terrain_seg[cur_node].y;
          vlist[0].z = (cur_node / TERRAIN_WIDTH) * TERRAIN_SIZE;

          vlist[1].x = (cellnum_upper % TERRAIN_WIDTH) * TERRAIN_SIZE;
          if (cellnum_upper < TERRAIN_WIDTH * TERRAIN_DEPTH)
            vlist[1].y = Terrain_seg[cellnum_upper].y;
          else
            vlist[1].y = 0.0;
          vlist[1].z = (cellnum_upper / TERRAIN_WIDTH) * TERRAIN_SIZE;

          vlist[2].x = (cellnum_upper_right % TERRAIN_WIDTH) * TERRAIN_SIZE;
          if (cellnum_upper_right < TERRAIN_WIDTH * TERRAIN_DEPTH)
            vlist[2].y = Terrain_seg[cellnum_upper_right].y;
          else
            vlist[2].y = 0.0;
          vlist[2].z = (cellnum_upper_right / TERRAIN_WIDTH) * TERRAIN_SIZE;

          vertex_ptr_list[0] = &vlist[0];
          vertex_ptr_list[1] = &vlist[1];
          vertex_ptr_list[2] = &vlist[2];

          face_normal = TerrainNormals[MAX_TERRAIN_LOD - 1][cur_node].normal1;
        }

        // Did we hit this face?
        if ((fvi_query_ptr->thisobjnum >= 0) &&
            (Objects[fvi_query_ptr->thisobjnum].mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS)) {
          face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0,
                                             &fvi_hit_data_ptr->hit_pnt, &face_normal, vertex_ptr_list, 3, 0.0f);
        } else if ((this_obj) && (this_obj->flags & OF_POLYGON_OBJECT)) {
          face_hit_type =
              check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, &fvi_wall_sphere_p0, &fvi_wall_sphere_p1,
                                 &face_normal, vertex_ptr_list, 3, fvi_wall_sphere_rad);
          hit_point -= fvi_wall_sphere_offset;
        } else {
          face_hit_type =
              check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0,
                                 &fvi_hit_data_ptr->hit_pnt, &face_normal, vertex_ptr_list, 3, fvi_query_ptr->rad);
        }
/*
        if(Objects[fvi_query_ptr->thisobjnum].type == OBJ_CLUTTER) {
          mprintf(0, "Y = %f\n", Objects[fvi_query_ptr->thisobjnum].pos.y);
        }
*/


        // chrisnote - closest hit should be tracked...  So, we can call BBPI once with
        // false and all other times with true for fast exit.
#if 0
        if (this_obj && this_obj->type == OBJ_CLUTTER) {
          if (!BBoxPlaneIntersection(true, &fvi_hit_data_ptr->hit_face_pnt[0], &fvi_hit_data_ptr->hit_wallnorm[0],
                                     &Objects[fvi_query_ptr->thisobjnum], fvi_query_ptr->p0, 3, vertex_ptr_list,
                                     &face_normal, fvi_query_ptr->o_orient, fvi_query_ptr->o_rotvel,
                                     fvi_query_ptr->o_velocity))
            ASSERT(1);

          if (fvi_hit_data_ptr->hit_type[0] == HIT_NONE &&
              BBoxPlaneIntersection(false, &fvi_hit_data_ptr->hit_face_pnt[0], &fvi_hit_data_ptr->hit_wallnorm[0],
                                    &Objects[fvi_query_ptr->thisobjnum], &fvi_hit_data_ptr->hit_pnt, 3, vertex_ptr_list,
                                    &face_normal, &fvi_hit_data_ptr->hit_orient, &fvi_hit_data_ptr->hit_rotvel,
                                    &fvi_hit_data_ptr->hit_velocity)) {
            float hit_dist = 0.0;
            float hit_interval;
            vector movement_dir;

            if (!BBoxPlaneIntersection(false, &fvi_hit_data_ptr->hit_face_pnt[0], &fvi_hit_data_ptr->hit_wallnorm[0],
                                       &Objects[fvi_query_ptr->thisobjnum], fvi_query_ptr->p0, 3, vertex_ptr_list,
                                       &face_normal, fvi_query_ptr->o_orient, fvi_query_ptr->o_rotvel,
                                       fvi_query_ptr->o_velocity)) {
              movement_dir = fvi_hit_data_ptr->hit_pnt - *fvi_query_ptr->p0;
              hit_interval = vm_NormalizeVector(&movement_dir);

              DoLinearApprox(&fvi_hit_data_ptr->hit_face_pnt[0], &fvi_hit_data_ptr->hit_wallnorm[0], &hit_dist,
                             &hit_interval, &movement_dir, fvi_query_ptr->p0, &Objects[fvi_query_ptr->thisobjnum], 3,
                             vertex_ptr_list, &face_normal);

              fvi_collision_dist = hit_dist;
            } else {
              fvi_hit_data_ptr->hit_orient = *fvi_query_ptr->o_orient;
              fvi_hit_data_ptr->hit_rotvel = *fvi_query_ptr->o_rotvel;
              fvi_hit_data_ptr->hit_turnroll = *fvi_query_ptr->o_turnroll;
              fvi_hit_data_ptr->hit_pnt = *fvi_query_ptr->p0;

              fvi_collision_dist = 0.0;
              movement_dir = Zero_vector;
              hit_dist = 0.0f;
            }

            fvi_hit_data_ptr->hit_type[0] = HIT_TERRAIN;
            fvi_hit_data_ptr->hit_wallnorm[0].x = 0.0;
            fvi_hit_data_ptr->hit_wallnorm[0].y = 1.0;
            fvi_hit_data_ptr->hit_wallnorm[0].z = 0.0;
            // fvi_hit_data_ptr->hit_seg = -1; -- set in the fvi_FindIntersection function
            // fvi_hit_data_ptr->hit_pnt = *fvi_query_ptr->p0 + hit_dist *movement_dir;
            fvi_hit_data_ptr->hit_face[0] = i;
            fvi_hit_data_ptr->hit_face_room[0] = cur_node;
            // fvi_hit_data_ptr->hit_side_pnt = fvi_hit_data_ptr->hit_pnt;
            // fvi_hit_data_ptr->hit_side_pnt.y = fvi_query_ptr->p0->y - Objects[fvi_query_ptr->thisobjnum].size;
/*
            if(!BBoxPlaneIntersection(true,
              &fvi_hit_data_ptr->hit_face_pnt[0], &fvi_hit_data_ptr->hit_wallnorm[0], &Objects[fvi_query_ptr->thisobjnum],
              &fvi_hit_data_ptr->hit_pnt, 3, vertex_ptr_list, &face_normal, &fvi_hit_data_ptr->hit_orient,
              &fvi_hit_data_ptr->hit_rotvel, &fvi_hit_data_ptr->hit_rotvel))
              ASSERT(1);
*/
            goto ignore_hit;
          }
        }
#endif
        // If we hit the face...
        if (face_hit_type) {
          if (cur_dist <= fvi_collision_dist) {
            if ((cur_dist < fvi_collision_dist) || !(fvi_query_ptr->flags & FQ_MULTI_POINT)) {
              fvi_hit_data_ptr->num_hits = 0;

              fvi_collision_dist = cur_dist;
              fvi_hit_data_ptr->hit_pnt = hit_point;
              compute_movement_AABB();
            } else if (fvi_hit_data_ptr->num_hits == MAX_HITS) {
              goto ignore_hit;
            }

            fvi_hit_data_ptr->hit_object[fvi_hit_data_ptr->num_hits] = -1;
            fvi_hit_data_ptr->hit_type[fvi_hit_data_ptr->num_hits] = HIT_TERRAIN;
            fvi_hit_data_ptr->hit_wallnorm[fvi_hit_data_ptr->num_hits] = wall_norm;
            // fvi_hit_data_ptr->hit_seg = -1; -- set in the fvi_FindIntersection function
            fvi_hit_data_ptr->hit_face[fvi_hit_data_ptr->num_hits] = i;
            fvi_hit_data_ptr->hit_face_room[fvi_hit_data_ptr->num_hits] = (MAKE_ROOMNUM(cur_node));
            fvi_hit_data_ptr->hit_face_pnt[fvi_hit_data_ptr->num_hits] = colp;

            fvi_hit_data_ptr->num_hits++;
          }
        }
      ignore_hit:;
      }
    }
  }

  // check local nodes for any collision type, but no recursion for them :)
  if (f_check_local_nodes) {
    int next_y_delta;

    // Check worst-case collisions.  This includes all nodes within a radius edge of the current node
    tercheck_x = check_x = fvi_query_ptr->rad / TERRAIN_SIZE + 1;
    tercheck_y = check_y = fvi_query_ptr->rad / TERRAIN_SIZE + 1;

    if (fvi_query_ptr->flags & FQ_CHECK_OBJS) {
      check_x += CELLS_PER_COL_CELL;
      check_y += CELLS_PER_COL_CELL;
    }

    xstart = cur_node % TERRAIN_WIDTH - check_x;
    xend = cur_node % TERRAIN_WIDTH + check_x;
    ystart = cur_node / TERRAIN_WIDTH - check_y;
    yend = cur_node / TERRAIN_WIDTH + check_y;

    terxstart = cur_node % TERRAIN_WIDTH - tercheck_x;
    terxend = cur_node % TERRAIN_WIDTH + tercheck_x;
    terystart = cur_node / TERRAIN_WIDTH - tercheck_y;
    teryend = cur_node / TERRAIN_WIDTH + tercheck_y;

    if (xstart < 0)
      xstart = 0;
    if (xend >= TERRAIN_WIDTH)
      xend = TERRAIN_WIDTH - 1;
    if (ystart < 0)
      ystart = 0;
    if (yend >= TERRAIN_DEPTH)
      yend = TERRAIN_DEPTH - 1;

    // This should be a faster interative why to do a square with center at original position
    new_node = TERRAIN_WIDTH * ystart + xstart;
    next_y_delta = TERRAIN_WIDTH - (xend - xstart) - 1;

    for (ycounter = ystart; ycounter <= yend; ycounter++) {
      for (xcounter = xstart; xcounter <= xend; xcounter++) {

        if ((fvi_terrain_visit_list[new_node >> 3] & (0x01 << (new_node % 8))) == 0) {

          f_check_next_ground = false;

          if (ycounter >= terystart && ycounter <= teryend) {
            if ((!f_check_next_ground) && xcounter >= terxstart && xcounter <= terxend) {
              f_check_next_ground = true;
            }
          }

          check_terrain_node(new_node, false, f_check_next_ground);
        }

        new_node += 1;
      }

      new_node += next_y_delta;
    }
  }

  return;
}

/*
inline void check_square_node(int x, int y, int width)
{
        // check local nodes for any collision type, but no recursion for them :)
        int next_y_delta;

        // Check worst-case collisions.  This includes all nodes within a radius edge of the current node
        tercheck_x = check_x = fvi_query_ptr->rad/TERRAIN_SIZE + 1;
        tercheck_y = check_y = fvi_query_ptr->rad/TERRAIN_SIZE + 1;

                if(fvi_query_ptr->flags & FQ_CHECK_OBJS)
                {
                        check_x += CELLS_PER_COL_CELL;
                        check_y += CELLS_PER_COL_CELL;
                }

                xstart = cur_node%TERRAIN_WIDTH - check_x;
                xend = cur_node%TERRAIN_WIDTH + check_x;
                ystart = cur_node/TERRAIN_WIDTH - check_y;
                yend = cur_node/TERRAIN_WIDTH + check_y;

                terxstart = cur_node%TERRAIN_WIDTH - tercheck_x;
                terxend = cur_node%TERRAIN_WIDTH + tercheck_x;
                terystart = cur_node/TERRAIN_WIDTH - tercheck_y;
                teryend = cur_node/TERRAIN_WIDTH + tercheck_y;

                if(xstart < 0) xstart = 0;
                if(xend >= TERRAIN_WIDTH) xend = TERRAIN_WIDTH - 1;
                if(ystart < 0) ystart = 0;
                if(yend >= TERRAIN_DEPTH) yend = TERRAIN_DEPTH - 1;

                // This should be a faster interative why to do a square with center at original position
                new_node = TERRAIN_WIDTH * ystart + xstart;
                next_y_delta = TERRAIN_WIDTH - (xend - xstart) - 1;

                for(ycounter = ystart; ycounter <= yend; ycounter++)
                {
                        for(xcounter = xstart; xcounter <= xend; xcounter++)
                        {

                                if((fvi_terrain_visit_list[new_node >> 3] & (0x01 << (new_node % 8))) == 0)
                                {

                                        f_check_next_ground = false;

                                        if(ycounter >= terystart && ycounter <= teryend)
                                        {
                                                if((!f_check_next_ground) && xcounter >= terxstart && xcounter <=
terxend)
                                                {
                                                        f_check_next_ground = true;
                                                }
                                        }

//					if(!((fvi_terrain_obj_visit_list[new_node >> 3] & (0x01 << (new_node % 8))) !=
0)) if(!((fvi_terrain_visit_list[new_node >> 3] & (0x01 << (new_node % 8))) != 0)) check_terrain_node(new_node, false,
f_check_next_ground);
                                }

                                new_node += 1;
                        }

                        new_node += next_y_delta;
                }
        }
}
*/

int do_fvi_terrain() {
  int x1, x2, y1, y2, x, y, delta_y, delta_x, change_x, change_y, length, cur_node, error_term, i;

  int new_x, new_y;
  int counter;
  int delta_ter_check = fvi_query_ptr->rad / TERRAIN_SIZE + 1;
  int delta_check = fvi_query_ptr->rad / TERRAIN_SIZE + CELLS_PER_COL_CELL + 1;

  // This is the only time we will check the terrain
  f_check_terrain = false;

  // We need to know the endpoint
  fvi_hit_data_ptr->hit_room = GetTerrainRoomFromPos(&fvi_hit_data_ptr->hit_pnt);

  // End point is out of bounds, so clip it.
  if (fvi_hit_data_ptr->hit_room == -1) {
    float delta = 1.0;
    vector movement = fvi_hit_data_ptr->hit_pnt - *fvi_query_ptr->p0;

    if (fvi_hit_data_ptr->hit_pnt.x < (fvi_query_ptr->rad + 0.000001)) {
      delta = (fvi_query_ptr->p0->x - (fvi_query_ptr->rad + 0.000001)) / (-movement.x);
    } else if (fvi_hit_data_ptr->hit_pnt.x >
               (float)((TERRAIN_WIDTH - 1) * TERRAIN_SIZE) - (fvi_query_ptr->rad + 0.000001)) {
      delta = ((float)((TERRAIN_WIDTH - 1) * TERRAIN_SIZE) - (fvi_query_ptr->rad + 0.000001) - fvi_query_ptr->p0->x) /
              (movement.x);
    }

    if (fvi_hit_data_ptr->hit_pnt.z < (fvi_query_ptr->rad + 0.000001)) {
      if ((fvi_query_ptr->p0->z - (fvi_query_ptr->rad + 0.000001)) / (-movement.z) < delta)
        delta = (fvi_query_ptr->p0->z - (fvi_query_ptr->rad + 0.000001)) / (-movement.z);
    } else if (fvi_hit_data_ptr->hit_pnt.z >
               (float)((TERRAIN_DEPTH - 1) * TERRAIN_SIZE) - (fvi_query_ptr->rad + 0.000001)) {
      if (((float)((TERRAIN_DEPTH - 1) * TERRAIN_SIZE) - (fvi_query_ptr->rad + 0.000001) - fvi_query_ptr->p0->z) /
              (movement.z) <
          delta)
        delta = ((float)((TERRAIN_DEPTH - 1) * TERRAIN_SIZE) - (fvi_query_ptr->rad + 0.000001) - fvi_query_ptr->p0->z) /
                (movement.z);
    }

    fvi_hit_data_ptr->hit_pnt = *fvi_query_ptr->p0 + delta * movement;
    fvi_collision_dist = vm_VectorDistance(&fvi_hit_data_ptr->hit_pnt, fvi_query_ptr->p0);

    fvi_hit_data_ptr->hit_room = GetTerrainRoomFromPos(&fvi_hit_data_ptr->hit_pnt);

    fvi_hit_data_ptr->hit_type[0] = HIT_OUT_OF_TERRAIN_BOUNDS;

    compute_movement_AABB();

    if (fvi_hit_data_ptr->hit_room == -1)
      return fvi_hit_data_ptr->hit_type[0];
  }

  // Determine the start end end nodes
  x1 = CELLNUM(fvi_query_ptr->startroom) % TERRAIN_WIDTH;
  y1 = CELLNUM(fvi_query_ptr->startroom) / TERRAIN_WIDTH;

  x2 = CELLNUM(fvi_hit_data_ptr->hit_room) % TERRAIN_WIDTH;
  y2 = CELLNUM(fvi_hit_data_ptr->hit_room) / TERRAIN_WIDTH;

  x = x1;
  y = y1;

  // How many nodes did I move?
  delta_x = x2 - x1;
  delta_y = y2 - y1;

  // check the current node for collsions (if we are done, return)
  check_terrain_node(CELLNUM(fvi_query_ptr->startroom), true, true);
  if (delta_x == 0 && delta_y == 0)
    goto check_big_objs;

  // check the end node
  cur_node = y1 * TERRAIN_DEPTH + x2;
  check_terrain_node(cur_node, true, (fvi_terrain_visit_list[cur_node >> 3] & (0x01 << (cur_node % 8))) == 0);

  // Do a Breshenham line algorithm
  if (delta_x < 0) {
    change_x = -1;
    delta_x = -delta_x;

  } else {
    change_x = 1;
  }

  if (delta_y < 0) {
    change_y = -1;
    delta_y = -delta_y;

  } else {
    change_y = 1;
  }

  error_term = 0;
  i = 1;

  if (delta_x < delta_y) {
    length = delta_y + 1;

    while (i < length) {
      y += change_y;
      error_term += delta_x;

      if (error_term >= delta_y) {
        x += change_x;
        error_term -= delta_y;
      }

      if (y >= TERRAIN_DEPTH || y < 0 || x < 0 || x >= TERRAIN_WIDTH) {
        fvi_hit_data_ptr->hit_type[0] = HIT_OUT_OF_TERRAIN_BOUNDS;
        goto check_big_objs;
      }

      for (counter = -delta_check; counter <= delta_check; counter++) {
        new_x = x + counter;

        if (new_x < 0) {
          counter = -x;
          new_x = 0;
        }

        if (new_x >= TERRAIN_WIDTH)
          break;

        // Check the current node for collisions -- chrishack -- This can be made iterative
        cur_node = y * TERRAIN_DEPTH + new_x;

        if ((fvi_terrain_visit_list[cur_node >> 3] & (0x01 << (cur_node % 8))) == 0) {
          if (counter < -delta_ter_check || counter > delta_ter_check) {
            check_terrain_node(cur_node, false, false);
          } else {
            check_terrain_node(cur_node, false, true);
          }
        }
      }

      i++;
    }

  } else {
    length = delta_x + 1;

    while (i < length) {
      x += change_x;
      error_term += delta_y;

      if (error_term >= delta_x) {
        y += change_y;
        error_term -= delta_x;
      }

      if (y >= TERRAIN_DEPTH || y < 0 || x < 0 || x >= TERRAIN_WIDTH) {
        fvi_hit_data_ptr->hit_type[0] = HIT_OUT_OF_TERRAIN_BOUNDS;
        goto check_big_objs;
      }

      for (counter = -delta_check; counter <= delta_check; counter++) {
        new_y = y + counter;

        if (new_y < 0) {
          counter = -y;
          new_y = 0;
        }
        if (new_y >= TERRAIN_DEPTH)
          break;

        // Check the current node for collisions -- chrishack -- This can be made iterative
        cur_node = new_y * TERRAIN_DEPTH + x;

        if ((fvi_terrain_visit_list[cur_node >> 3] & (0x01 << (cur_node % 8))) == 0) {
          if (counter < -delta_ter_check || counter > delta_ter_check) {
            check_terrain_node(cur_node, false, false);
          } else {
            check_terrain_node(cur_node, false, true);
          }
        }
      }

      i++;
    }
  }

  ASSERT(x == x2 && y == y2);

check_big_objs: // Check Big objects
  if (fvi_query_ptr->flags & FQ_CHECK_OBJS) {
    for (i = 0; i < Num_big_objects; i++) {
      ASSERT(BigObjectList[i] >= 0);
      check_hit_obj(BigObjectList[i]);
      //		mprintf(0, "CHecking BIG %d\n", i);
    }
  } else {
    if (!(fvi_query_ptr->flags & FQ_IGNORE_EXTERNAL_ROOMS))
      for (i = 0; i < Num_big_objects; i++) {
        if (Objects[BigObjectList[i]].type == OBJ_ROOM)
          check_hit_obj(BigObjectList[i]);
        //		mprintf(0, "CHecking BIG %d\n", i);
      }
  }

  return fvi_hit_data_ptr->hit_type[0];
}

// NOTE: CHRIS increased MAX_NEXT_PORTALS because radiosity rays tend to hit more portals
// than in game stuff.  It has no performance effect; so, I should be fine.
#define MAX_NEXT_PORTALS 50

void fvi_rooms_objs(void) {
  int objnum;
  int i;
  room *cur_room;

  // first, see if vector hit any objects in this segment
  if (!(fvi_query_ptr->flags & FQ_CHECK_OBJS))
    return;

  for (i = 0; i < fvi_num_rooms_visited; i++) {
    cur_room = &Rooms[fvi_rooms_visited[i]];
    ASSERT((fvi_visit_list[ROOMNUM(cur_room) >> 3] & (0x01 << (ROOMNUM(cur_room) % 8))) != 0);
    ASSERT(ROOMNUM(cur_room) >= 0 && ROOMNUM(cur_room) <= Highest_room_index && cur_room->used);

    for (objnum = cur_room->objects; objnum != -1; objnum = Objects[objnum].next) {
      ASSERT(objnum != -1);
      check_hit_obj(objnum);
    }
  }
}

// Flags for GetFaceAlpha()
#define FA_CONSTANT 1    // face has a constant alpha for the whole face
#define FA_VERTEX 2      // face has different alpha per vertex
#define FA_TRANSPARENT 4 // face has transparency (i.e. per pixel 1-bit alpha)

// Determines if a face draws with alpha blending
// Parameters:	fp - pointer to the face in question
//					bm_handle - the handle for the bitmap for this frame, or -1 if don't care about
// transparence Returns:		bitmask describing the alpha blending for the face
// the return bits are the ATF_ flags in renderer.h
inline int GetFaceAlpha(face *fp, int bm_handle) {
  int ret = AT_ALWAYS;
  if (GameTextures[fp->tmap].flags & TF_SATURATE) {
    if (fp->flags & FF_VERTEX_ALPHA)
      ret = AT_SATURATE_TEXTURE_VERTEX;
    else
      ret = AT_SATURATE_TEXTURE;
  } else {
    // Check the face's texture for an alpha value
    if (GameTextures[fp->tmap].alpha < 1.0)
      ret |= ATF_CONSTANT;

    // Someday we'll probably check the bitmap's alpha, too
    // Check for vertex alpha flag
    if (fp->flags & FF_VERTEX_ALPHA)
      ret |= ATF_VERTEX;

    // Check for transparency
    if (GameBitmaps[bm_handle].format != BITMAP_FORMAT_4444 && GameTextures[fp->tmap].flags & TF_TMAP2)
      ret |= ATF_TEXTURE;
  }

  return ret;
}

bool PhysPastPortal(const room *rp, portal *pp) {
  // If we don't render the portal's faces, then we see through it
  if (!(pp->flags & PF_RENDER_FACES))
    return 1;

  // Check if the face's texture has transparency
  face *fp = &rp->faces[pp->portal_face];
  int bm_handle = GetTextureBitmap(fp->tmap, 0);

  if (GetFaceAlpha(fp, bm_handle))
    return 1; // Face has alpha or transparency, so we can see through it
  else
    return 0; // Not transparent, so no render past
}

int fvi_room(int room_index, int from_portal, int room_obj) {
  vector hit_point; // where we hit
  float cur_dist;   // distance to hit point
  const room *cur_room = &Rooms[room_index];
  int16_t i;
  int next_portals[MAX_NEXT_PORTALS];
  int num_next_portals = 0;
  int next_portal_index;
  int portal_num;
  //	vector col_point[32];
  //	vector col_normal[32];
  int num_cols = 0;
  object *this_obj;
  uint8_t msector = 0;

  if (fvi_min_xyz.x <= cur_room->bbf_min_xyz.x) {
    msector |= 0x01;
  }
  if (fvi_min_xyz.y <= cur_room->bbf_min_xyz.y) {
    msector |= 0x02;
  }
  if (fvi_min_xyz.z <= cur_room->bbf_min_xyz.z) {
    msector |= 0x04;
  }
  if (fvi_max_xyz.x >= cur_room->bbf_max_xyz.x) {
    msector |= 0x08;
  }
  if (fvi_max_xyz.y >= cur_room->bbf_max_xyz.y) {
    msector |= 0x10;
  }
  if (fvi_max_xyz.z >= cur_room->bbf_max_xyz.z) {
    msector |= 0x20;
  }

  if (fvi_query_ptr->thisobjnum >= 0)
    this_obj = &Objects[fvi_query_ptr->thisobjnum];
  else
    this_obj = NULL;

  ASSERT(room_index >= 0 && room_index <= Highest_room_index);
  ASSERT(Rooms[room_index].used);
  ASSERT((fvi_visit_list[room_index >> 3] & (0x01 << (room_index % 8))) == 0);

  if (!(cur_room->flags & RF_EXTERNAL)) {
    fvi_visit_list[room_index >> 3] |= 0x01 << (room_index % 8);
    fvi_rooms_visited[fvi_num_rooms_visited] = room_index;
    fvi_num_rooms_visited++;

    ASSERT(fvi_num_rooms_visited <= MAX_ROOMS);
  }

  if (fvi_query_ptr->flags & FQ_IGNORE_WALLS) {
    vector face_normal;
    vector *vertex_ptr_list[MAX_VERTS_PER_FACE];
    int16_t count;
    bool f_backface;
    int face_info;
    int j; //, k;

    for (j = 0; j < cur_room->num_portals; j++) {
      i = cur_room->portals[j].portal_face;

      portal_num = cur_room->faces[i].portal_num;

      //			if ((msector & cur_room->faces[i].sector) != cur_room->faces[i].sector) continue;
      if (!room_movement_AABB(&cur_room->faces[i]))
        continue;

      face_info = GetFacePhysicsFlags(cur_room, &cur_room->faces[i]);
      if (face_info == FPT_IGNORE)
        continue;

      if (portal_num >= 0 && portal_num == from_portal)
        continue;

      f_backface = false;

      for (count = 0; count < cur_room->faces[i].num_verts; count++)
        vertex_ptr_list[count] = &cur_room->verts[cur_room->faces[i].face_verts[count]];

      face_normal = cur_room->faces[i].normal;

      // Add the portal if we are within a AABB of it.
      if ((face_info & FPF_PORTAL)) {
        // If we can cross a portal, add it to the next portal list if it is not already there
        if (!(face_info & FPF_SOLID) && !(fvi_query_ptr->flags & FQ_SOLID_PORTALS)) {
          bool f_add_next_portal;

          f_add_next_portal = true;

          for (next_portal_index = 0; next_portal_index < num_next_portals; next_portal_index++) {
            if (next_portals[next_portal_index] == portal_num)
              f_add_next_portal = false;
          }

          if (f_add_next_portal) {
            ASSERT(num_next_portals < MAX_NEXT_PORTALS);
            next_portals[num_next_portals++] = portal_num;

            if ((fvi_query_ptr->flags & FQ_RECORD) && (face_info & FPF_RECORD)) {
              ASSERT(Fvi_num_recorded_faces < MAX_RECORDED_FACES);
              if (Fvi_num_recorded_faces < MAX_RECORDED_FACES) {
                Fvi_recorded_faces[Fvi_num_recorded_faces].face_index = i;
                Fvi_recorded_faces[Fvi_num_recorded_faces++].room_index = room_index;
              }
            }
          }
        }
      }
    }
  } else {
    const int16_t num_bbf_regions = cur_room->num_bbf_regions;
    int16_t *num_faces_ptr = cur_room->num_bbf;
    uint8_t *bbf_val = cur_room->bbf_list_sector;
    vector *region_min = cur_room->bbf_list_min_xyz;
    vector *region_max = cur_room->bbf_list_max_xyz;
    int16_t **bbf_list_ptr = cur_room->bbf_list;

    // Do the actual wall collsion stuff here!
    for (int test1 = 0; test1 < num_bbf_regions; test1++) {
      if (((*bbf_val) & msector) == (*bbf_val)) {
        if (region_min->x > fvi_wall_max_xyz.x || region_min->y > fvi_wall_max_xyz.y ||
            region_min->z > fvi_wall_max_xyz.z || region_max->x < fvi_wall_min_xyz.x ||
            region_max->y < fvi_wall_min_xyz.y || region_max->z < fvi_wall_min_xyz.z)
          goto skip_region;

        if (fvi_zero_rad && FastVectorBBox((float *)region_min, (float *)region_max, (float *)fvi_query_ptr->p0,
                                           (float *)&fvi_movement_delta) == false)
          goto skip_region;

        int16_t *cur_face_index_ptr = *bbf_list_ptr;

        for (int sort_list_cur = 0; sort_list_cur < (*num_faces_ptr); sort_list_cur++) {
          vector face_normal;
          vector *vertex_ptr_list[MAX_VERTS_PER_FACE];
          int face_hit_type;
          vector wall_norm;
          vector colp;
          int16_t count;
          bool f_backface;
          int face_info;
          face *cur_face;

          i = *cur_face_index_ptr;
          cur_face = &cur_room->faces[*cur_face_index_ptr];
          cur_face_index_ptr++;

          const vector *cf_max = &cur_face->max_xyz;
          const vector *cf_min = &cur_face->min_xyz;

          if (cf_min->x > fvi_wall_max_xyz.x || cf_min->y > fvi_wall_max_xyz.y || cf_min->z > fvi_wall_max_xyz.z ||
              cf_max->x < fvi_wall_min_xyz.x || cf_max->y < fvi_wall_min_xyz.y || cf_max->z < fvi_wall_min_xyz.z)
            continue;

          if (fvi_zero_rad && FastVectorBBox((float *)cf_min, (float *)cf_max, (float *)fvi_query_ptr->p0,
                                             (float *)&fvi_movement_delta) == false)
            continue;

          portal_num = cur_face->portal_num;
          if (portal_num >= 0 && portal_num == from_portal)
            continue;

          face_info = GetFacePhysicsFlags(cur_room, cur_face);
          if (face_info == FPT_IGNORE)
            continue;

          f_backface = false;

          for (count = 0; count < cur_face->num_verts; count++)
            vertex_ptr_list[count] = &cur_room->verts[cur_face->face_verts[count]];

          face_normal = cur_face->normal;

          // Add the portal if we are within a AABB of it.
          if ((face_info & FPF_PORTAL)) {
            if ((fvi_query_ptr->flags & FQ_RECORD) && (face_info & FPF_RECORD)) {
              ASSERT(Fvi_num_recorded_faces < MAX_RECORDED_FACES);
              if (Fvi_num_recorded_faces < MAX_RECORDED_FACES) {
                Fvi_recorded_faces[Fvi_num_recorded_faces].face_index = i;
                Fvi_recorded_faces[Fvi_num_recorded_faces++].room_index = room_index;
              }
            }

            // If we can cross a portal, add it to the next portal list if it is not already there
            if (!(face_info & FPF_SOLID) && !(fvi_query_ptr->flags & FQ_SOLID_PORTALS)) {
              bool f_add_next_portal = true;

              for (next_portal_index = 0; next_portal_index < num_next_portals; next_portal_index++) {
                if (next_portals[next_portal_index] == portal_num) {
                  f_add_next_portal = false;
                  break;
                }
              }

              if (f_add_next_portal) {
                ASSERT(num_next_portals < MAX_NEXT_PORTALS);
                next_portals[num_next_portals++] = portal_num;
              }
            }

            if ((fvi_query_ptr->flags & FQ_IGNORE_RENDER_THROUGH_PORTALS) &&
                (PhysPastPortal(cur_room, &cur_room->portals[portal_num]))) {
              bool f_add_next_portal = true;

              for (next_portal_index = 0; next_portal_index < num_next_portals; next_portal_index++) {
                if (next_portals[next_portal_index] == portal_num) {
                  f_add_next_portal = false;
                  break;
                }
              }

              if (f_add_next_portal) {
                ASSERT(num_next_portals < MAX_NEXT_PORTALS);
                next_portals[num_next_portals++] = portal_num;
              }

              continue;
            }
          }

          // Did we hit this face?
          if ((this_obj) && (this_obj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS)) {
            face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0,
                                               &fvi_hit_data_ptr->hit_pnt, &face_normal, vertex_ptr_list,
                                               cur_face->num_verts, 0.0f);
          } else if ((this_obj) && (this_obj->flags & OF_POLYGON_OBJECT)) {
            face_hit_type =
                check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, &fvi_wall_sphere_p0, &fvi_wall_sphere_p1,
                                   &face_normal, vertex_ptr_list, cur_face->num_verts, fvi_wall_sphere_rad);
            hit_point -= fvi_wall_sphere_offset;
          } else {
            face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0,
                                               &fvi_hit_data_ptr->hit_pnt, &face_normal, vertex_ptr_list,
                                               cur_face->num_verts, fvi_query_ptr->rad);
          }

          if ((((fvi_query_ptr->flags & FQ_OBJ_BACKFACE) && (cur_room->flags & RF_EXTERNAL)) ||
               ((fvi_query_ptr->flags & FQ_BACKFACE) && !(cur_room->flags & RF_EXTERNAL))) &&
              (!face_hit_type)) {
            face_normal *= -1.0f;
            for (count = 0; count < cur_face->num_verts; count++)
              vertex_ptr_list[cur_face->num_verts - count - 1] = &cur_room->verts[cur_face->face_verts[count]];

            face_hit_type = check_line_to_face(&hit_point, &colp, &cur_dist, &wall_norm, fvi_query_ptr->p0,
                                               &fvi_hit_data_ptr->hit_pnt, &face_normal, vertex_ptr_list,
                                               cur_face->num_verts, fvi_query_ptr->rad);
            f_backface = true;
          }

          if (face_hit_type && (face_info & FPF_TRANSPARENT) && (fvi_query_ptr->flags & FQ_TRANSPOINT) &&
              CheckTransparentPoint(&colp, cur_room, i)) {
            // Go through the hole
            face_hit_type = HIT_NONE;
          }

          // If we hit the face...
          if (face_hit_type) {
            if ((fvi_query_ptr->flags & FQ_RECORD) && (face_info & FPF_RECORD) &&
                !(Fvi_recorded_faces[Fvi_num_recorded_faces - 1].face_index == i &&
                  Fvi_recorded_faces[Fvi_num_recorded_faces - 1].room_index == room_index)) {
              ASSERT(Fvi_num_recorded_faces < MAX_RECORDED_FACES);
              if (Fvi_num_recorded_faces < MAX_RECORDED_FACES) {
                Fvi_recorded_faces[Fvi_num_recorded_faces].face_index = i;
                Fvi_recorded_faces[Fvi_num_recorded_faces++].room_index = room_index;
              }
            }

            if (cur_dist <= fvi_collision_dist && (face_info & (FPF_SOLID | FPF_TRANSPARENT))) {

              if ((cur_dist < fvi_collision_dist) || !(fvi_query_ptr->flags & FQ_MULTI_POINT)) {
                fvi_hit_data_ptr->num_hits = 0;

                fvi_collision_dist = cur_dist;
                fvi_hit_data_ptr->hit_pnt = hit_point;
                compute_movement_AABB();
              } else if (fvi_hit_data_ptr->num_hits == MAX_HITS) {
                goto ignore_hit;
              }

              if (f_backface)
                fvi_hit_data_ptr->hit_type[fvi_hit_data_ptr->num_hits] = HIT_BACKFACE;
              else
                fvi_hit_data_ptr->hit_type[fvi_hit_data_ptr->num_hits] = HIT_WALL;

              fvi_hit_data_ptr->hit_wallnorm[fvi_hit_data_ptr->num_hits] = wall_norm;
              // fvi_hit_data_ptr->hit_seg = -1; -- set in the fvi_FindIntersection function
              fvi_hit_data_ptr->hit_object[fvi_hit_data_ptr->num_hits] = room_obj;
              fvi_hit_data_ptr->hit_face[fvi_hit_data_ptr->num_hits] = i;
              fvi_hit_data_ptr->hit_face_room[fvi_hit_data_ptr->num_hits] = room_index; // Segment of the best hit
              fvi_hit_data_ptr->hit_face_pnt[fvi_hit_data_ptr->num_hits] = colp;

              fvi_hit_data_ptr->num_hits++;
            }
          }
        }
      }
    skip_region:;
    ignore_hit:;
      num_faces_ptr++;
      bbf_val++;
      region_max++;
      region_min++;
      bbf_list_ptr++;
    }
  }
  // repeated: ;

  /*	if(num_cols > 1)
          {
                  int i;
                  vector new_normal;
                  float len;

                  for(i = 0; i < num_cols; i++)
                  {
                          new_normal += col_normal[i];
                  }

                  len = vm_NormalizeVector(&new_normal);

                  if(len == 0.0f)
                  {
                          mprintf(0, "PHYSICS WARNING: Normals cancal out\n");
                          new_normal = col_normal[0];
                  }

                  fvi_hit_data_ptr->hit_pnt = fvi_hit_data_ptr->hit_pnt - (fvi_query_ptr->rad * (new_normal));
          }
  */

  if (!(fvi_query_ptr->flags & FQ_SOLID_PORTALS)) {
    // Accounts for doors that leave a
    for (i = 0; i < cur_room->num_portals; i++) {
      int c_room = cur_room->portals[i].croom;

      if ((c_room > 0) && (Rooms[c_room].flags & RF_DOOR)) {
        bool f_add_next_portal = true;
        int next_portal_index;

        for (next_portal_index = 0; next_portal_index < num_next_portals; next_portal_index++) {
          if (next_portals[next_portal_index] == i) {
            f_add_next_portal = false;
            break;
          }
        }

        if (f_add_next_portal) {
          ASSERT(num_next_portals < MAX_NEXT_PORTALS);
          next_portals[num_next_portals++] = i;
        }
      }
    }

    // Check all potentially crossed portals
    for (next_portal_index = 0; next_portal_index < num_next_portals; next_portal_index++) {
      int connect_room;

      portal_num = next_portals[next_portal_index];
      connect_room = cur_room->portals[portal_num].croom;

      if (!(Rooms[connect_room].flags & RF_EXTERNAL)) {
        if ((fvi_visit_list[connect_room >> 3] & (0x01 << ((connect_room) % 8))) == 0) {
          /*
          mprintf(0, "A portal %d to room %d,from room %d,with %d cportal\n",
                  portal_num,
                  cur_room->portals[portal_num].croom,
                  room_index,
                  cur_room->portals[portal_num].cportal);
          */
          fvi_room(connect_room, cur_room->portals[portal_num].cportal);
        }
      } else if (f_check_terrain) {
        fvi_info hit_data_terrain = *fvi_hit_data_ptr;
        fvi_query query_terrain = *fvi_query_ptr;
        fvi_info *temp_hit_data = fvi_hit_data_ptr;
        fvi_query *temp_query = fvi_query_ptr;

        fvi_hit_data_ptr = &hit_data_terrain;
        fvi_query_ptr = &query_terrain;

        query_terrain.startroom = GetTerrainRoomFromPos(query_terrain.p0);

        //			mprintf(0, "We might go outside\n");

        // This is quick, so do it here.
        hit_data_terrain.hit_room = GetTerrainRoomFromPos(&hit_data_terrain.hit_pnt);

        if (hit_data_terrain.hit_room == -1)
          hit_data_terrain.hit_type[0] = HIT_OUT_OF_TERRAIN_BOUNDS;

        // Find the hit data!!!
        do_fvi_terrain();

        // This is quick, so do it here.
        hit_data_terrain.hit_room = GetTerrainRoomFromPos(&hit_data_terrain.hit_pnt);
        if (hit_data_terrain.hit_room == -1)
          hit_data_terrain.hit_type[0] = HIT_OUT_OF_TERRAIN_BOUNDS;

        // Reset the fvi global pointers to handle in mine stuff.
        fvi_hit_data_ptr = temp_hit_data;
        fvi_query_ptr = temp_query;

        // Make sure we register the hit
        if (hit_data_terrain.hit_type[0] != HIT_NONE)
          *fvi_hit_data_ptr = hit_data_terrain;
      }
    }
  }

  // quit_looking:

  ASSERT(!(fvi_hit_data_ptr->hit_type[0] == HIT_OBJECT && fvi_hit_data_ptr->hit_object[0] == -1));

  return fvi_hit_data_ptr->hit_type[0];
}
