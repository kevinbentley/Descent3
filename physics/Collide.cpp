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

 * $Logfile: /DescentIII/Main/physics/Collide.cpp $
 * $Revision: 239 $
 * $Date: 9/20/01 5:33p $
 * $Author: Matt $
 *
 * Descent III collision code
 *
 * $Log: /DescentIII/Main/physics/Collide.cpp $
 *
 * 239   9/20/01 5:33p Matt
 * Fixed weird omega cannon bugs (I hope) by only letting the omega
 * particles collide from inside AquireElectricalTarget().
 *
 * 238   11/04/99 5:35p Chris
 * Levels with forcefields with a custom bouce sound don't cause damage
 *
 * 237   10/20/99 5:40p Chris
 * Added the Red Guidebot
 *
 * 236   10/08/99 4:29p Chris
 * Added the forcefield and glass breaking override options
 *
 * 235   5/24/99 1:26a Matt
 * Correctly deal with hit_info == NULL being passed to collision
 * routines.
 *
 * 234   5/21/99 2:55a Matt
 * When an object is bounced-out and needs to be killed, call
 * DestroyObject() if it's already dying.  Before the code just set the
 * dead flag, which caused robots to disappear if they bumped into
 * something while dying.
 *
 * 233   5/20/99 9:03p Matt
 * Changed trigger system so that collisions with rendered portals don't
 * set off triggers on the portals.
 *
 * 232   5/19/99 1:23p Matt
 * Fixed (hopefully) yet more collision problems introduced by my recent
 * changes.
 *
 * 231   5/18/99 10:15p Matt
 * Fixed bug with weapon spawning that I introduced last night.
 *
 * 230   5/18/99 10:57a Chris
 * Various bug fixes
 *
 * 229   5/17/99 9:09p Matt
 * Made objects with lava behave like walls with lava; flares don't stick,
 * player catches on fire.
 *
 * 228   5/17/99 6:07p Chris
 * GB doesn't damage players - PF_LOCK_MASK objects always do...
 *
 * 227   5/11/99 5:50p Chris
 * Buildings don't collide with each other
 *
 * 226   5/08/99 4:27p Chris
 * Hearing code
 *
 * 225   5/08/99 3:31p Matt
 * Deal with weapons hitting water.
 *
 * 224   5/07/99 10:56p Chris
 * GB avoids forcefields, lava, and volatile surfaces...  If he accidently
 * hits one of these, he ignores the collision (i.e. no effects).  It make
 * him look smarter.
 *
 * 223   4/30/99 3:28p Matt
 * Weapons now make a special sound when colliding with lava & volatile
 * surfaces, instead of the standard hit-wall sound.
 *
 * 222   4/29/99 6:48p Matt
 * Made volatile surfaces apply damage and lava surfaces catch the player
 * on fire.  Both now generate the steam puff effect.
 *
 * 221   4/29/99 2:17a Samir
 * adjusted some sound priority stuff
 *
 * 220   4/23/99 6:44p Matt
 * Changed weapons to keep going after breaking glass.
 *
 * 219   4/21/99 4:27p Chris
 *
 * 218   4/21/99 3:45p Chris
 *
 * 217   4/21/99 3:43p Chris
 *
 * 216   4/21/99 2:56p Chris
 * Made player-player collisions almost complete in-elastic
 *
 * 215   4/21/99 1:30p Matt
 * Make breakable glass use the new breakable flag, instead of
 * piggybacking on the destroyable flag.
 *
 * 214   4/21/99 11:06a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 213   4/21/99 10:12a Chris
 * Tweaked robot/player damage
 *
 * 212   4/21/99 3:33a Chris
 * Collisions between robots and players cause damage to both robots and
 * players (robots get more damage)
 *
 * 211   4/19/99 12:03p Jason
 * added checking for fireball collisions
 *
 * 210   4/19/99 4:02a Jeff
 * fixed min/max for Linux
 *
 * 209   4/18/99 10:55p Chris
 * Added ignore own concussive blasts
 *
 * 208   4/16/99 8:18p Jason
 * make impact spawning weapons work with doors
 *
 * 207   4/14/99 1:42a Jeff
 * fixed case mismatched #includes
 *
 * 206   4/12/99 6:15p Samir
 * Sound priorities pass 1
 *
 * 205   4/06/99 6:24p Jason
 * various fixes for multiplayer
 *
 * 204   3/23/99 4:10p Jason
 * more tweaks for line sparks
 *
 * 203   3/23/99 12:50p Jason
 * added line sparks
 *
 * 202   3/22/99 6:41p Jason
 * fixed client side weapons not reacting correctly to bouncing code
 *
 * 201   3/22/99 1:47p Matt
 * Moved breaking glass code from collide.cpp to damage.cpp
 *
 * 200   3/16/99 4:16p Matt
 * Made mass driver spin the victim more. (Jason had reduced it from 0.25
 * to 0.05; I've moved it back up to 0.12 at Andy's request.)
 *
 * 199   3/12/99 7:46p Jeff
 * record wall hit collisions to demo file
 *
 * 198   3/11/99 5:55p Jason
 * fixed player spin with mass driver
 *
 * 197   3/05/99 2:12p Matt
 * Fixed bug (in a slightly hacky way) where energy weapons would cause
 * glass to switch to the damaged texture.  For a real fix, we need a
 * separate breakable glass flag for textures.
 *
 * 196   3/03/99 10:52a Chris
 * Energy weapons push again
 *
 * 195   3/03/99 5:44a Chris
 * Max secondary burn time of 10 seconds
 *
 * 194   3/01/99 3:18p Jason
 * made powerups work correctly in multiplayer
 *
 * 193   2/28/99 11:29p Chris
 * Improved robot-wall reactions
 *
 * 192   2/22/99 2:03p Jason
 * added different damages for players and generics
 *
 * 191   2/21/99 4:35p Chris
 * Improving the level goal system...  Not done.
 *
 * 190   2/20/99 10:31a Kevin
 * OEM Beta 1 fixs
 *
 * 189   2/19/99 12:35p Chris
 * Player can fly through markers
 *
 * 188   2/17/99 4:50p Jason
 * fixed destroyable face/breakable glass bug
 *
 * 187   2/17/99 1:26p Matt
 * Fixed the die angle system for weapons (changing it around a little in
 * the process: now all non-weapons (which don't use the system) should
 * have dot == -1, weapons that die at any angle have dot == 0, and
 * setting dot == 1 means it never dies).
 *
 * 186   2/16/99 8:16a Chris
 * Fixed a bug - THANKS!
 *
 * 185   2/10/99 1:48p Matt
 * Changed object handle symbolic constants
 *
 * 184   2/09/99 2:38p Jason
 * added destroyable faces
 *
 * 183   2/02/99 8:44a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 182   1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 181   1/29/99 5:09p Chris
 * Made changes for ROCKS
 *
 * 180   1/28/99 6:17p Jason
 * added markers
 *
 * 179   1/26/99 6:39p Jason
 * added wall effects code
 *
 * 178   1/25/99 5:59p Matt
 * Patched the masses of objects
 *
 * 177   1/24/99 8:18p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 176   1/23/99 5:16p Chris
 * Bounds fixed acos and asin stuff (-1.0000000000001 could cause really
 * bad things to happen with rot. vels)
 *
 * 175   1/20/99 10:50a Jason
 * added new terrain
 *
 * 174   1/20/99 2:13a Chris
 * It is now possible for robots to have special immunities, resistances,
 * and vunerabilities
 *
 * 173   1/18/99 12:12a Jeff
 * removed weapon collide event, combined it in general collide event.
 * general collide event handles more collides.  Added a room collide
 * event
 *
 * 172   1/15/99 3:59a Jeff
 * added two new multiplayer DLL events for weapon collisions.  Added two
 * new fields to DLLInfo data, point and normal, which are filled out for
 * collision events.
 *
 * 170   1/10/99 7:35p Matt
 * Added missing break to DO_COLLISION macor
 *
 * 169   1/10/99 6:49a Jeff
 * Some initial work to get linux version to compile
 *
 * 168   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 167   1/01/99 4:10p Chris
 * Added some const parameters, improved ray cast object collide/rejection
 * code
 *
 * 166   12/21/98 10:50a Chris
 * You can now push walking objects
 *
 * 165   12/17/98 12:08p Jeff
 * first checkin of new implementation of OSIRIS (old OSIRIS no longer
 * works)
 *
 * 164   11/19/98 3:54p Chris
 *
 * 163   11/19/98 3:51p Chris
 * Shooting dying robots makes them blow up faster (but now not as
 * quickly)
 *
 * 162   11/13/98 4:25p Jason
 * changes for better weapon effects
 *
 * 161   11/13/98 1:00p Chris
 * Fixed a math problem with the new collision response code.  Zero rad
 * particles where causing i1 or i2 to be zero.  c1 = c1/i1 -> it was
 * going to infinity.  So, I made a floor threshold for i1 and i2
 *
 * 160   11/11/98 2:46p Kevin
 * Demo recording system work
 *
 * 159   11/10/98 5:17p Jeff
 * peppered in some more forcefeedback effects
 *
 * 158   10/30/98 5:17p Chris
 * Players only get 1/4 the rotational velocity of an impulse
 *
 * 157   10/29/98 1:45p Chris
 * Checked in the better collision response code
 *
 * 156   10/22/98 12:57p Chris
 * Added sounds to player/player and player/robot collisions
 *
 * 155   10/20/98 1:26p Jason
 * took out spawning on direct hits
 *
 * 154   10/20/98 12:10p Chris
 *
 * 153   10/19/98 8:38p Matt
 * Don't make a sound when colliding with lava, since the lava will start
 * you on fire, which will make sound.
 *
 * 152   10/19/98 7:19p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 151   10/18/98 2:09p Matt
 * Made the backquote/flare thing go away in release versions, and made it
 * work for terrain cells.
 *
 * 150   10/17/98 12:25p Chris
 * Fixed attached flares
 *
 * 149   10/16/98 5:25p Chris
 * Fixed sticky code
 *
 * 148   10/16/98 4:33p Chris
 *
 * 147   10/16/98 4:18p Chris
 * Fixed the 'flare thing'
 *
 * 146   10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 145   10/15/98 4:51p Chris
 * Speed up dying for player too
 *
 * 144   10/15/98 4:49p Chris
 * Speed up dying if the robot is getting hit
 *
 * 143   10/12/98 2:27p Matt
 * Fixed code to print room:face when backquote/tilde held down and flare
 * hits the wall.
 *
 * 142   10/12/98 10:04a Chris
 * Wall hits cannot kill the player
 *
 * 141   10/09/98 7:57p Chris
 * Added the flare room/wall cheat
 *
 * 140   10/09/98 7:47p Chris
 * Added ObjSetDeadFlag
 *
 * 139   10/08/98 12:00p Kevin
 * Demo system work
 *
 * 138   10/05/98 7:23p Jason
 * implemented destroyable lights (first draft)
 *
 * 137   10/01/98 6:56p Jason
 * turned off energy weapon hit effects if the object getting hit is the
 * viewer - this helps cut down on the general clutter in heavy combat
 *
 * 136   9/29/98 4:48p Chris
 * Working on multiplayer collisions
 *
 * 135   9/23/98 5:04p Chris
 * Raised the collide wall damage threshold
 *
 * 134   9/23/98 3:47p Chris
 * Increased the speed to cause damage from wall hits
 *
 * 133   9/22/98 12:23p Chris
 * Further improvements to wall hitting
 *
 * 132   9/21/98 8:32p Chris
 * Another improvement to the forcefield stuff
 *
 * 131   9/21/98 8:19p Chris
 * Improved volatile and forcefield hits
 *
 * 130   9/21/98 1:08p Chris
 * Improved lava handling
 *
 * 129   9/21/98 1:04p Chris
 *
 * 128   9/21/98 1:03p Chris
 *
 * 127   9/21/98 1:01p Chris
 * Fixed more volatile problems
 *
 * 126   9/21/98 11:44a Chris
 * Fixed the volatile terrain crash bug
 *
 * 125   9/18/98 7:45p Chris
 * Lava works - needs tweaking.
 *
 * 124   8/25/98 7:27p Chris
 * Improved the scorch code
 *
 * 123   8/25/98 7:23p Chris
 * Made weapons explode even if they break glass
 *
 * 122   8/25/98 12:35p Chris
 * Fixed a small reversed normal bug
 *
 * 121   8/19/98 2:48p Jason
 * fixed some weapon firing and weapon exploding bugs
 *
 * 120   8/18/98 7:12p Chris
 * Improved FUSION behavior.
 *
 * 119   8/12/98 12:26p Chris
 *
 * 118   8/05/98 11:16a Matt
 * Added trigger checks when weapons and the player collide with walls.
 *
 * 117   8/03/98 5:56p Jason
 * got fusion cannon working correctly
 *
 * 116   7/31/98 11:52a Chris
 * Weapons can be persistent.  Added ability for objects to be manually
 * set for no object collisions.
 *
 * 115   7/30/98 11:09a Jason
 * added weapons that freeze and deform terrain
 *
 * 114   7/22/98 4:36p Jason
 * took out bugs from observer mode
 *
 * 113   7/17/98 10:12a Chris
 *
 * 112   7/01/98 12:56p Jason
 * more changes for countermeasures
 *
 * 111   7/01/98 12:12p Jason
 * added countermeasures
 *
 * 110   6/24/98 3:56p Jason
 * added code for new omega cannon
 *
 * 109   6/15/98 3:23p Chris
 * Single point walker update
 *
 * 108   6/15/98 7:53a Chris
 * Fixed a comment'ed out variable
 *
 * 107   6/15/98 7:52a Chris
 * Removed the new "cool" physics
 *
 * 106   6/11/98 12:48p Jason
 * added better spewing weapons
 *
 * 105   6/04/98 12:00p Matt
 * Took out Napalm Rocket hack that I added for the E3 demo.
 *
 * 104   6/02/98 10:43p Chris
 * Multipoint collision detection enabled
 *
 * 103   6/01/98 9:23p Chris
 * Fixed a bunch of collision problems
 *
 * 102   5/27/98 6:18p Matt
 * Super hack to reduce impact damage of napalm rocket (for E3 only)
 *
 * 101   5/27/98 6:08p Chris
 * Added weapon to generic sound
 *
 * 100   5/26/98 4:17p Jason
 * made scripts/dlls not collide every single frame
 *
 * 99    5/26/98 3:58p Matt
 * Only matter weapons now break glass.
 *
 * 98    5/25/98 8:36p Matt
 * Added code to set different sizes for different weapon scorch marks.
 * Also, don't leave scorch marks on lights.
 *
 * 97    5/22/98 12:34p Matt
 * Added scorch mark/bullet hole system.
 *
 * 96    5/22/98 11:59a Chris
 * Fixed improper uses of FindSoundName and made the proper static sounds
 *
 * 95    5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 94    5/07/98 2:52p Chris
 * Removed a bounce mprintf
 *
 * 93    5/07/98 2:40p Chris
 * Added death_dot and bounce sound for weapons
 *
 * 92    5/07/98 2:22p Chris
 * Hit die dot
 *
 * 91    5/06/98 7:07p Samir
 * when player is completely dead, don't call script too.
 *
 * 90    5/05/98 3:42p Chris
 * Code cleanup and fixed the collide_XXX_with_wall code.  The wall_normal
 * was know by fvi; so, it is passed to the function (instead of
 * generating it again)
 *
 * 89    5/04/98 3:51p Matt
 * Finished (for now) with breaking glass.
 *
 * 88    5/04/98 1:00p Jason
 * changed the way weapon explosions work
 *
 * 87    5/04/98 12:47p Matt
 * Improvements to the breaking glass system, though I don't consider it
 * anywhere near done yet.
 *
 * 86    5/03/98 10:24p Matt
 * Partially completed breaking glass code, checked in so Chris can fix a
 * bug
 *
 * 85    4/23/98 7:14p Chris
 * Changed non-moving objects to player collisions
 *
 * 84    4/22/98 9:43p Chris
 * More AI improvements
 *
 * 83    4/22/98 3:25p Jason
 * changes for multiplayer debugging
 *
 * 82    4/20/98 4:47p Chris
 * Made collision stuff more accurate
 *
 * 81    4/17/98 2:00p Jason
 * added cool object effects
 *
 * 80    4/15/98 12:56p Chris
 * Reformatted some code
 *
 * 79    4/09/98 5:18p Jason
 * got guided working in multiplayer
 *
 * 78    4/09/98 12:05p Chris
 * Added parenting for all object types.  :)
 *
 * 77    4/08/98 11:16a Chris
 * Fixed powerup pickup bug
 *
 * 76    4/07/98 4:25p Chris
 * Added support for buddy bot
 *
 * 75    4/06/98 11:59a Chris
 * Fixed powerup/powerup hack
 *
 * 74    3/31/98 5:56p Jason
 * changes for multiplay
 *
 * 73    3/30/98 5:12p Jason
 * more changes for game/dll integration
 *
 * 72    3/20/98 9:34p Jason
 * added SetObjectDeadFlag inlined function
 *
 * 71    3/20/98 6:39p Jason
 * 100.0 to 1.0 for volume
 *
 * 70    3/20/98 3:54p Chris
 * Working on adding sounds to the game.  :)
 *
 * 69    3/20/98 3:21p Chris
 * Added player hit by weapon sound.
 *
 * 68    3/20/98 2:59p Chris
 * Added a wall hit sound for the player and added support for a base
 * volume for 3d sounds
 *
 * 67    3/19/98 7:15p Jason
 * more changes for multiplayer
 *
 * 66    3/19/98 3:44p Chris
 * Multiplayer enchancement for collisions
 *
 * 65    3/19/98 3:27p Chris
 * Did some collision code for multiplayer.
 *
 * 64    3/18/98 5:45p Jason
 * more multiplayer script integration
 *
 * 63    3/17/98 6:17p Jason
 * added gamemode collide stuff
 *
 * 62    3/17/98 11:27a Chris
 * Added object bump notifies for AI
 *
 * 61    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 60    2/23/98 5:46p Chris
 * Removed some old code.
 *
 * 59    2/18/98 11:48a Craig
 *
 * 58    2/11/98 4:10p Jason
 * got spawning impact weapons working
 *
 * 57    2/05/98 2:54p Jason
 * changes for explosions
 *
 * 56    2/05/98 2:02p Chris
 * Fixed the hitseg and hitwall in collide_object_with_wall and
 * scrape_object_with_wall
 *
 * 55    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 54    1/30/98 2:54p Matt
 * Took script calls out of bump_two_objects, since they alread existed in
 * collide_two_objects
 *
 * 53    1/29/98 5:48p Matt
 * Got rid of marker objects
 *
 * 52    1/29/98 4:16p Matt
 * Fixed some problems from my last changes
 *
 * 51    1/29/98 3:11p Matt
 * Clean up a bit: deleted commented-out code, removed leftover D1/D2
 * stuff, removed references to hostage objects
 *
 * 50    1/28/98 12:00p Jason
 * more changes for multiplayer
 *
 * 49    1/26/98 11:01a Jason
 * incremental checkin for multiplayer
 *
 * 48    1/23/98 11:21a Jason
 * incremental multiplayer checkin
 *
 * 47    1/21/98 6:09p Jason
 * Got player deaths working in multiplayer
 *
 * 46    1/21/98 3:05p Samir
 * Changed a function call to StartPlayerExplosion
 *
 * 45    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 44    1/20/98 12:10p Jason
 * implemented vis effect system
 *
 * 43    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 42    1/14/98 7:57p Chris
 * Improving the awareness system
 *
 * 41    1/14/98 1:23p Jason
 * made ApplyDamageToGeneric send the weapons parent as the killer
 *
 * 40    1/09/98 4:13p Chris
 * Reformatted some code
 *
 * 39    1/09/98 4:11p Chris
 * Removed a mprintf
 *
 * 38    12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 37    12/15/97 11:03a Jason
 * make sparks only when successfully hit
 *
 * 36    12/12/97 6:13p Jason
 * added sparks
 *
 * 35    12/10/97 2:36p Jason
 * added random small explosions
 *
 * 34    12/04/97 12:15p Jason
 * gave designers the ability to set their own weapon-to-wall hit vclips
 *
 * 33    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 32    11/20/97 1:38p Chris
 * No rotation is applied to player objects
 *
 * 31    11/13/97 5:06p Chris
 * Added support for clutter to weapon collisions
 *
 * 30    11/05/97 6:42p Jason
 * took out stupid blast ring
 *
 * 29    10/29/97 1:29p Chris
 * Added PF_STICK for weapons
 *
 * 28    10/24/97 2:30p Jason
 * more changes for explosions
 *
 * 27    10/23/97 11:14a Jason
 * changed some fireball DEFINEs
 *
 * 26    10/22/97 7:26p Samir
 * Player death mostly working.   Damn hangup still occurs.  Freaky.
 *
 * 25    10/22/97 4:30p Chris
 * We can now slew between the mine and the terrain
 *
 * 24    10/22/97 11:44a Jason
 * changes for explosion system
 *
 * 23    10/21/97 4:15p Chris
 * Incremental integration of the fvi/physics/collide code
 *
 * 22    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 21    10/20/97 11:55a Chris
 * Added some support for the new collide system.
 *
 * 20    10/16/97 3:46p Chris
 * Incremental improvements
 *
 * 19    10/03/97 3:47p Chris
 * Moved script calls to bump two objects (so building can have scripts)
 *
 * 18    10/03/97 3:45p Chris
 * Added some bumping force by weapons
 *
 * 17    10/03/97 3:18p Samir
 * Added script hook to bump_this_object
 *
 * 16    10/02/97 11:34a Chris
 * Added support for external room collisions
 *
 * 15    10/01/97 4:51p Samir
 * Include damage.h
 *
 * 14    9/19/97 9:37p Chris
 * Attempted to fix door collisions -- almost there, but not quite
 *
 * 13    9/15/97 5:17a Chris
 * Removed the Explosion Vclips since they do not play correctly in
 * Hardware
 * Added support for building collisons.
 * working on SPhere to non-moving sphere collisions
 *
 * 12    9/12/97 6:36p Chris
 * Added building collisions
 *
 * 11    9/05/97 12:27p Samir
 * Player takes damage and set death if needed.
 *
 * 10    9/04/97 12:03p Matt
 * Got rid of warnings
 *
 * 9     9/03/97 2:13p Chris
 * Working on improving the debris system and partical explosions
 *
 * 8     8/21/97 7:53p Chris
 *
 * 7     8/21/97 7:52p Chris
 *
 * 6     8/18/97 1:46a Chris
 * Allowed for robot damage and destoyable objects.
 * Also, allowed weapons to bounce
 *
 * 5     8/14/97 11:44a Samir
 * Don't kill powerups.  Let script do it.
 *
 * 4     8/12/97 3:32p Samir
 * collisions call script code now too.
 *
 * 3     8/11/97 1:54p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 2     7/28/97 1:16p Chris
 * Allow for player and robots to be hit by weapons and correct parenting
 * of weapons.
 *
 * 16    5/19/97 5:39 PM Jeremy
 * removed "we hit a robot" mprintf
 *
 * 15    5/15/97 6:09p Chris
 *
 * 14    5/13/97 5:52p Chris
 * Added ability to exit and enter mine.  Also did some
 * incremental improvements.
 *
 * 13    5/05/97 5:41a Chris
 * Added some better polygon collision code.  It is still rough though.
 *
 * 12    4/29/97 8:03a Chris
 * Improved the sound code.  High-level sound now
 * fully uses the flags in the sound page and it
 * resulted in a simpilier coding interface  :)
 *
 * 11    4/24/97 5:42p Jason
 * got fireball vclips working
 *
 * 10    4/24/97 12:28p Jason
 * added sound when weapon hits a wall
 *
 * 9     4/24/97 3:25a Chris
 * // Added some more support for 3d sounds
 *
 * 8     4/23/97 6:34p Chris
 * // Incremental collision stuff.
 *
 * 7     4/23/97 6:06p Jason
 * made player ship and weapons work correctly together (first pass)
 *
 * 6     4/17/97 3:10p Chris
 * Added edge of world object delete.  Also did some incremental
 * improvements.
 *
 * 5     4/11/97 3:05a Chris
 * Allowed robot sphere collision
 *
 * 4     3/15/97 1:29p Chris
 *
 * $NoKeywords: $
 */

#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "collide.h"
#include "PHYSICS.H"
#include "pserror.h"
#include "mono.h"
#include "object.h"
#include "player.h"
#include "hlsoundlib.h"
#include "weapon.h"
#include "damage.h"
#include "fireball.h"
#include "sounds.h"
#include "AIMain.h"
#include "multi.h"
#include "game.h"
#include "soundload.h"
#include "game2dll.h"
#include "scorch.h"
#include "ddio.h"
#include "vecmat.h"
#include "trigger.h"
#include "lighting.h"
#include "hud.h"
#include "D3ForceFeedback.h"
#include "demofile.h"
#include "osiris_dll.h"
#include "marker.h"
#include "hud.h"
#include "levelgoal.h"
#include "psrand.h"

#include <algorithm>

#define PLAYER_ROTATION_BY_FORCE_SCALAR 0.12f
#define NONPLAYER_ROTATION_BY_FORCE_SCALAR 1.0f

uint8_t CollisionResult[MAX_OBJECT_TYPES][MAX_OBJECT_TYPES];
uint8_t CollisionRayResult[MAX_OBJECT_TYPES];

static bool IsOKToApplyForce(object *objp);
static void bump_this_object(object *objp, object *other_objp, vector *force, vector *collision_pnt, int damage_flag);
//! Creates some effects where a weapon has collided with a wall.
static void DoWallEffects(object *weapon, int surface_tmap);
//! Check for lava, volatile, or water surface.  If contact, make special sound & kill the weapon.
static void check_for_special_surface(object *weapon, int surface_tmap, vector *surface_normal, float hit_dot);
/// Process a collision between a weapon and a wall.
/// - Returns: true if the weapon hits the wall, and false if should keep going though the wall (for breakable glass).
static bool collide_weapon_and_wall(object *weapon, fix hitspeed, int hitseg, int hitwall, vector *hitpnt,
                                    vector *wall_normal, float hit_dot);
/// Prints out a marker hud message if needed.
static void collide_player_and_marker(object *playerobj, object *marker_obj, vector *collision_point,
                                      vector *collision_normal, bool f_reverse_normal, fvi_info *hit_info);
static void collide_player_and_wall(object *playerobj, float hitspeed, int hitseg, int hitwall, vector *hitpt,
                                    vector *wall_normal, float hit_dot);
static void collide_generic_and_wall(object *genericobj, float hitspeed, int hitseg, int hitwall, vector *hitpt,
                                     vector *wall_normal, float hit_dot);
static void CollideAnglesToMatrix(matrix *m, float p, float h, float b);
static vector *CollideExtractAnglesFromMatrix(vector *a, matrix *m);
static void bump_two_objects(object *object0, object *object1, vector *collision_point, vector *collision_normal,
                             int damage_flag);
static void collide_player_and_player(object *p1, object *p2, vector *collision_point, vector *collision_normal,
                                      bool f_reverse_normal, fvi_info *hit_info);
static void collide_generic_and_player(object *robotobj, object *playerobj, vector *collision_point,
                                       vector *collision_normal, bool f_reverse_normal, fvi_info *hit_info);
static void MakeWeaponStick(object *weapon, object *parent, fvi_info *hit_info);
static void check_lg_inform(object *A, object *B);

bool IsOKToApplyForce(object *objp) {
  if (Game_mode & GM_MULTI) {
    if (objp->type == OBJ_PLAYER) {
      if (objp != Player_object)
        return false;
    } else {
      if (objp->type != OBJ_WEAPON && objp->type != OBJ_POWERUP && Netgame.local_role != LR_SERVER)
        return false;
    }
  }

  if (objp->mtype.phys_info.mass == 0.0)
    return false;

  if (objp->movement_type != MT_PHYSICS && objp->movement_type != MT_WALKING)
    return false;

  if (objp->mtype.phys_info.flags & PF_PERSISTENT)
    return false;

  if (objp->mtype.phys_info.flags & PF_LOCK_MASK) // Not done!
    return false;

  return true;
}

//	-----------------------------------------------------------------------------
void bump_this_object(object *objp, object *other_objp, vector *force, vector *collision_pnt, int damage_flag) {
  //	float force_mag;

  if (objp->type == OBJ_PLAYER) {
    if ((Game_mode & GM_MULTI) && (objp != Player_object))
      return;

    phys_apply_force(objp, force);
  } else {
    if ((Game_mode & GM_MULTI) && (objp->type != OBJ_PLAYER && objp->type != OBJ_POWERUP) &&
        (Netgame.local_role != LR_SERVER))
      return;

    phys_apply_force(objp, force);
    phys_apply_rot(objp, force);
  }

  //	if (! (objp->mtype.phys_info.flags & PF_PERSISTENT))
  //		if (objp->type == OBJ_PLAYER) {
  //			vector force2;
  //			force2 = forcex/4;

  //			phys_apply_force(objp,&force2);

  //			if (damage_flag && ((other_objp->type != OBJ_ROBOT) || !Robot_info[other_objp->id].companion)) {
  //				force_mag = vm_vec_mag_quick(&force2);
  //				apply_force_damage(objp, force_mag, other_objp);
  //			}
  //		} else if ((objp->type == OBJ_ROBOT) || (objp->type == OBJ_CLUTTER) || (objp->type == OBJ_CNTRLCEN)) {
  //			if (!Robot_info[objp->id].boss_flag) {
  //				vector force2;
  //				force2.x = force->x/(4 + Difficulty_level);
  //				force2.y = force->y/(4 + Difficulty_level);
  //				force2.z = force->z/(4 + Difficulty_level);

  //				phys_apply_force(objp, force);
  //				phys_apply_rot(objp, &force2);
  //				if (damage_flag) {
  //					force_mag = vm_vec_mag_quick(force);
  //					apply_force_damage(objp, force_mag, other_objp);
  //				}
  //			}
  //		}
}

/*

         void bump_one_object(object *obj0, vector *hit_dir, float damage)
{
        vector	hit_vec;

        hit_vec = *hit_dir;
        vm_vec_scale(&hit_vec, damage);

        phys_apply_force(obj0,&hit_vec);

}
*/

// #define DAMAGE_SCALE 		128	//	Was 32 before 8:55 am on Thursday, September 15, changed by MK,
// walls
//  were hurting me more than robots! #define DAMAGE_THRESHOLD 	(F1_0/3) #define WALL_LOUDNESS_SCALE (20)

// float force_force = 50.0;

struct vec2d {
  float i, j;
};

#define cross(v0, v1) (((v0)->i * (v1)->j) - ((v0)->j * (v1)->i))

// finds the uv coords of the given point on the given seg & side
// fills in u & v. if l is non-NULL fills it in also
void FindHitpointUV(float *u, float *v, vector *point, room *rp, int facenum) {
  face *fp = &rp->faces[facenum];
  int ii, jj;
  vec2d pnt[3], checkp, vec0, vec1;
  float *t;
  float k0, k1;
  int i;

  // 1. find what plane to project this wall onto to make it a 2d case

  GetIJ(&fp->normal, &ii, &jj);

  // 2. compute u,v of intersection point

  // Copy face points into 2d verts array
  for (i = 0; i < 3; i++) {
    t = &rp->verts[fp->face_verts[i]].x;
    pnt[i].i = t[ii];
    pnt[i].j = t[jj];
  }
  t = &point->x;
  checkp.i = t[ii];
  checkp.j = t[jj];

  // vec from 1 -> 0
  vec0.i = pnt[0].i - pnt[1].i;
  vec0.j = pnt[0].j - pnt[1].j;

  // vec from 1 -> 2
  vec1.i = pnt[2].i - pnt[1].i;
  vec1.j = pnt[2].j - pnt[1].j;

  k1 = -((cross(&checkp, &vec0) + cross(&vec0, &pnt[1])) / cross(&vec0, &vec1));
  if (fabsf(vec0.i) > fabsf(vec0.j))
    k0 = ((-k1 * vec1.i) + checkp.i - pnt[1].i) / vec0.i;
  else
    k0 = ((-k1 * vec1.j) + checkp.j - pnt[1].j) / vec0.j;

  // mprintf(0," k0,k1  = %x,%x\n",k0,k1);

  *u = fp->face_uvls[1].u + (k0 * (fp->face_uvls[0].u - fp->face_uvls[1].u)) +
       (k1 * (fp->face_uvls[2].u - fp->face_uvls[1].u));
  *v = fp->face_uvls[1].v + (k0 * (fp->face_uvls[0].v - fp->face_uvls[1].v)) +
       (k1 * (fp->face_uvls[2].v - fp->face_uvls[1].v));

  // mprintf(0," u,v    = %x,%x\n",*u,*v);
}

// Creates some effects where a weapon has collided with a wall
void DoWallEffects(object *weapon, int surface_tmap) {
  texture *texp = &GameTextures[surface_tmap];

  if (texp->flags & (TF_VOLATILE + TF_LAVA + TF_WATER)) {
    // Create some lava steam
    if ((texp->flags & TF_WATER) || ((ps_rand() % 4) == 0)) {
      int visnum = VisEffectCreate(VIS_FIREBALL, MED_SMOKE_INDEX, weapon->roomnum, &weapon->pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];

        vis->lifetime = .9f;
        vis->lifeleft = .9f;

        vis->movement_type = MT_PHYSICS;
        vis->size = 3.0;
        vm_MakeZero(&vis->velocity);
        vis->velocity.y = 10;
      }
    }
  } else if (texp->flags & TF_RUBBLE) {
    if ((ps_rand() % 4) == 0) {
      int num_rubble = (ps_rand() % 3) + 1;
      int bm_handle = GetTextureBitmap(texp - std::data(GameTextures), 0);
      uint16_t *data = bm_data(bm_handle, 0);

      uint16_t color = data[(bm_w(bm_handle, 0) * (bm_h(bm_handle, 0) / 2)) + (bm_w(bm_handle, 0) / 2)];

      for (int i = 0; i < num_rubble; i++) {
        int visnum;

        visnum = VisEffectCreate(VIS_FIREBALL, RUBBLE1_INDEX + (ps_rand() % 2), weapon->roomnum, &weapon->pos);

        if (visnum >= 0) {
          vis_effect *vis = &VisEffects[visnum];

          vis->movement_type = MT_PHYSICS;
          vis->mass = 100;
          vis->drag = .1f;

          vis->phys_flags |= PF_GRAVITY | PF_NO_COLLIDE;

          if ((ps_rand() % 3) == 0) {
            vis->velocity.x = (ps_rand() % 100) - 50;
            vis->velocity.y = -((ps_rand() % 200) - 30);
            vis->velocity.z = (ps_rand() % 100) - 50;
          } else {
            vis->velocity.x = (ps_rand() % 300) - 50;
            vis->velocity.y = -((ps_rand() % 200) - 30);
            vis->velocity.z = (ps_rand() % 300) - 50;
          }

          vm_NormalizeVectorFast(&vis->velocity);
          vis->velocity *= 4 + (ps_rand() % 20);
          vis->size = .5 + (((ps_rand() % 11) - 5) * .05);
          vis->flags |= VF_USES_LIFELEFT;
          float lifetime = 1.0 + (((ps_rand() % 11) - 5) * .1);
          vis->lifeleft = lifetime;
          vis->lifetime = lifetime;
          vis->lighting_color = color;
        }
      }
    }
  }
}

#define FORCEFIELD_DAMAGE 5.0f

extern void DeformTerrain(vector *pos, int depth, float size);

// Check for lava, volatile, or water surface.  If contact, make special sound & kill the weapon
void check_for_special_surface(object *weapon, int surface_tmap, vector *surface_normal, float hit_dot) {
  bool f_forcefield, f_volatile, f_lava, f_water;

  f_forcefield = (GameTextures[surface_tmap].flags & TF_FORCEFIELD) != 0;
  f_volatile = (GameTextures[surface_tmap].flags & TF_VOLATILE) != 0;
  f_lava = (GameTextures[surface_tmap].flags & TF_LAVA) != 0;
  f_water = (GameTextures[surface_tmap].flags & TF_WATER) != 0;

  // Kill the weapon if the surface is volatile, lava, or water
  if (f_volatile || f_lava || f_water) {
    int snd;
    ain_hear hear;
    hear.f_directly_player = false;

    if (f_water) {
      snd = SOUND_WEAPON_HIT_WATER;
      hear.hostile_level = 0.2f;
      hear.curiosity_level = 0.3f;
    } else if (f_volatile || f_lava) {
      snd = SOUND_WEAPON_HIT_LAVA;
      hear.hostile_level = 0.1f;
      hear.curiosity_level = 0.5f;
    } else
      Int3();

    hear.max_dist = Sounds[snd].max_distance;
    Sound_system.Play3dSound(snd, SND_PRIORITY_NORMAL, weapon);
    AINotify(weapon, AIN_HEAR_NOISE, (void *)&hear);

    if (!f_water)
      DoWeaponExploded(weapon, surface_normal);

    SetObjectDeadFlag(weapon);
  }
}

// Process a collision between a weapon and a wall
// Returns true if the weapon hits the wall, and false if should keep going though the wall (for breakable glass)
bool collide_weapon_and_wall(object *weapon, fix hitspeed, int hitseg, int hitwall, vector *hitpnt, vector *wall_normal,
                             float hit_dot) {
  bool f_forcefield;
  bool f_volatile, f_lava, f_water;
  // mprintf(0, "Weapon hit wall, how nice.\n");

  // #ifndef RELEASE
  if ((stricmp(Weapons[weapon->id].name, "Yellow flare") == 0) && (weapon->parent_handle == Player_object->handle) &&
      (KEY_STATE(KEY_LAPOSTRO))) {
    if (ROOMNUM_OUTSIDE(hitseg)) {
      AddHUDMessage("Terrain cell %d", CELLNUM(hitseg));
    } else {
      AddHUDMessage("Room %d face %d", hitseg, hitwall);
    }
  }
  // #endif

  // Check if forcefield
  int tmap;
  if (!ROOMNUM_OUTSIDE(hitseg)) // Make sure we've hit a wall, and not terrain
  {
    tmap = Rooms[hitseg].faces[hitwall].tmap;
  } else {
    tmap = Terrain_tex_seg[Terrain_seg[CELLNUM(hitseg)].texseg_index].tex_index;
  }
  f_forcefield = (GameTextures[tmap].flags & TF_FORCEFIELD) != 0;
  f_volatile = (GameTextures[tmap].flags & TF_VOLATILE) != 0;
  f_lava = (GameTextures[tmap].flags & TF_LAVA) != 0;
  f_water = (GameTextures[tmap].flags & TF_WATER) != 0;

  if (f_forcefield && !(Weapons[weapon->id].flags & WF_MATTER_WEAPON)) {
    ain_hear hear;
    hear.f_directly_player = false;
    hear.hostile_level = 0.9f;
    hear.curiosity_level = 0.1f;

    if (sound_override_force_field == -1)
      hear.max_dist = Sounds[SOUND_FORCEFIELD_BOUNCE].max_distance;
    else
      hear.max_dist = Sounds[sound_override_force_field].max_distance;

    AINotify(weapon, AIN_HEAR_NOISE, (void *)&hear);

    if (sound_override_force_field == -1)
      Sound_system.Play3dSound(SOUND_FORCEFIELD_BOUNCE, SND_PRIORITY_HIGH, weapon);
    else
      Sound_system.Play3dSound(sound_override_force_field, SND_PRIORITY_HIGH, weapon);

    return true;
  }

  // Check for destroyable or breakable face
  if (!ROOMNUM_OUTSIDE(hitseg)) // First, make sure we've hit a wall, and not terrain
  {
    room *rp = &Rooms[hitseg];
    face *fp = &rp->faces[hitwall];

    // Check for a trigger on this wall
    CheckTrigger(hitseg, hitwall, weapon, TT_COLLIDE);

    // Check for a destroyable face
    if ((GameTextures[fp->tmap].flags & TF_DESTROYABLE) && !(fp->flags & FF_DESTROYED)) {
      int visnum = CreateFireball(hitpnt, SHATTER_INDEX + (ps_rand() % 2), hitseg, VISUAL_FIREBALL);

      if (visnum >= 0) {
        // Alter the size of this explosion based on the face size
        vector verts[MAX_VERTS_PER_FACE];
        vector center;
        for (int t = 0; t < fp->num_verts; t++)
          verts[t] = rp->verts[fp->face_verts[t]];

        float size = sqrt(vm_GetCentroid(&center, verts, fp->num_verts));
        VisEffects[visnum].size = (size / 2);
      }

      CreateRandomSparks(20, hitpnt, hitseg);

      if (sound_override_glass_breaking == -1)
        Sound_system.Play3dSound(SOUND_BREAKING_GLASS, SND_PRIORITY_HIGH, weapon);
      else
        Sound_system.Play3dSound(sound_override_glass_breaking, SND_PRIORITY_HIGH, weapon);

      fp->flags |= FF_DESTROYED;
    }

    // Check for a breakable face: If the texture is breakable and it's on a portal
    // and hit with a matter weapon, break it
    if ((fp->portal_num != -1) && (GameTextures[fp->tmap].flags & TF_BREAKABLE) &&
        (Weapons[weapon->id].flags & WF_MATTER_WEAPON)) {

      // Do the breaking glass stuff
      if (!((Game_mode & GM_MULTI) && Netgame.local_role == LR_CLIENT))
        BreakGlassFace(rp, hitwall, hitpnt, &weapon->mtype.phys_info.velocity);

      ain_hear hear;
      hear.f_directly_player = false;
      hear.hostile_level = 0.9f;
      hear.curiosity_level = 1.0f;
      if (sound_override_glass_breaking == -1)
        hear.max_dist = Sounds[SOUND_BREAKING_GLASS].max_distance;
      else
        hear.max_dist = Sounds[sound_override_glass_breaking].max_distance;
      AINotify(weapon, AIN_HEAR_NOISE, (void *)&hear);

      return false;
    }
  }

  // Add a scorch
  if ((Weapons[weapon->id].scorch_handle != -1) && !f_water && !f_volatile && !f_lava)
    AddScorch(hitseg, hitwall, hitpnt, Weapons[weapon->id].scorch_handle, Weapons[weapon->id].scorch_size);

  if (ROOMNUM_OUTSIDE(hitseg)) {
    if (Weapons[weapon->id].terrain_damage_size > 0 && Weapons[weapon->id].terrain_damage_depth > 0) {
      DeformTerrain(&weapon->pos, Weapons[weapon->id].terrain_damage_depth, Weapons[weapon->id].terrain_damage_size);
    }
  }

  // Do special smoke, etc.
  DoWallEffects(weapon, tmap);

  // look for lava, volatile, water
  check_for_special_surface(weapon, tmap, wall_normal, hit_dot);

  // If dead, we're done
  if (weapon->flags & OF_DEAD)
    return true;

  // If done bouncing, kill the weapon
  if ((weapon->mtype.phys_info.num_bounces <= 0) && !(weapon->mtype.phys_info.flags & PF_STICK) &&
      (hit_dot > weapon->mtype.phys_info.hit_die_dot)) {
    int snd;
    ain_hear hear;
    hear.f_directly_player = false;

    snd = Weapons[weapon->id].sounds[WSI_IMPACT_WALL];
    hear.hostile_level = 0.9f;
    hear.curiosity_level = 0.1f;

    if (snd != SOUND_NONE_INDEX) {
      hear.max_dist = Sounds[snd].max_distance;
      Sound_system.Play3dSound(snd, SND_PRIORITY_NORMAL, weapon);
      AINotify(weapon, AIN_HEAR_NOISE, (void *)&hear);
    }

    // Check to see if we should spawn
    if ((Weapons[weapon->id].flags & WF_SPAWNS_IMPACT) && Weapons[weapon->id].spawn_count > 0 &&
        Weapons[weapon->id].spawn_handle >= 0)
      CreateImpactSpawnFromWeapon(weapon, wall_normal);

    if ((Weapons[weapon->id].flags & WF_SPAWNS_ROBOT) && (Weapons[weapon->id].flags & WF_COUNTERMEASURE) &&
        Weapons[weapon->id].robot_spawn_handle >= 0)
      CreateRobotSpawnFromWeapon(weapon);

    DoWeaponExploded(weapon, wall_normal);

    SetObjectDeadFlag(weapon);
  } else { // weapon is bouncing

    if (Weapons[weapon->id].sounds[WSI_BOUNCE] != SOUND_NONE_INDEX) {
      Sound_system.Play3dSound(Weapons[weapon->id].sounds[WSI_BOUNCE], SND_PRIORITY_HIGH, weapon);

      if (Weapons[weapon->id].sounds[WSI_BOUNCE] > -1) {
        ain_hear hear;
        hear.f_directly_player = false;
        hear.hostile_level = 0.20f;
        hear.curiosity_level = 0.6f;
        hear.max_dist = Sounds[Weapons[weapon->id].sounds[WSI_BOUNCE]].max_distance;
        AINotify(weapon, AIN_HEAR_NOISE, (void *)&hear);
      }
    }
  }

  return true;
}

// Prints out a marker hud message if needed
void collide_player_and_marker(object *playerobj, object *marker_obj, vector *collision_point, vector *collision_normal,
                               bool f_reverse_normal, fvi_info *hit_info) {
  if (playerobj->id == Player_num) {
    char str[100];
    snprintf(str, sizeof(str), "Marker: %s", MarkerMessages[marker_obj->id]);
    AddHUDMessage(str);
  }
}

#define MIN_WALL_HIT_SOUND_VEL 40.0f
#define MAX_WALL_HIT_SOUND_VEL 120.0f
#define MIN_PLAYER_WALL_SOUND_TIME .1f
#define WALL_DAMAGE 0.5f
#define MIN_WALL_HIT_DAMAGE_SHIELDS 5
#define MIN_WALL_DAMAGE_SPEED 65.0

#define VOLATILE_DAMAGE 7.0f // damage per hit

void collide_player_and_wall(object *playerobj, float hitspeed, int hitseg, int hitwall, vector *hitpt,
                             vector *wall_normal, float hit_dot) {
  float volume = MAX_GAME_VOLUME;
  bool f_volatile, f_lava;
  bool f_forcefield;
  int tmap;

  if (playerobj->flags & OF_DYING)
    playerobj->ctype.dying_info.delay_time *= 0.9f;

  // Check for a trigger on this wall
  if (!ROOMNUM_OUTSIDE(hitseg)) // Make sure we've hit a wall, and not terrain
  {
    CheckTrigger(hitseg, hitwall, playerobj, TT_COLLIDE);
    tmap = Rooms[hitseg].faces[hitwall].tmap;
  } else {
    tmap = Terrain_tex_seg[Terrain_seg[CELLNUM(hitseg)].texseg_index].tex_index;
  }
  f_lava = (GameTextures[tmap].flags & TF_LAVA) != 0;
  f_volatile = (GameTextures[tmap].flags & TF_VOLATILE) != 0;
  f_forcefield = (GameTextures[tmap].flags & TF_FORCEFIELD) != 0;

  if (f_lava) {
    if (!((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
      int id = FindWeaponName("NapalmBlob");
      if (id >= 0)
        SetNapalmDamageEffect(playerobj, NULL, id);
      else
        Int3();
    }
  }

  // If volatile, make the sound & apply damage
  if (f_volatile) {
    if (playerobj == Player_object) {
      if ((!(Game_mode & GM_MULTI)) || Netgame.local_role == LR_SERVER)
        ApplyDamageToPlayer(playerobj, playerobj, PD_VOLATILE_HISS, VOLATILE_DAMAGE);
      else {
        Multi_requested_damage_type = PD_VOLATILE_HISS;
        Multi_requested_damage_amount += (VOLATILE_DAMAGE);
      }
    }
  }

  if (f_forcefield) {
    if (playerobj == Player_object && sound_override_force_field == -1) {
      if ((!(Game_mode & GM_MULTI)) || Netgame.local_role == LR_SERVER)
        ApplyDamageToPlayer(playerobj, playerobj, PD_ENERGY_WEAPON, FORCEFIELD_DAMAGE);
      else {
        Multi_requested_damage_type = PD_ENERGY_WEAPON;
        Multi_requested_damage_amount += (FORCEFIELD_DAMAGE);
      }
    }

    if (sound_override_force_field == -1)
      Sound_system.Play3dSound(SOUND_FORCEFIELD_BOUNCE, SND_PRIORITY_HIGH, playerobj, MAX_GAME_VOLUME);
    else
      Sound_system.Play3dSound(sound_override_force_field, SND_PRIORITY_HIGH, playerobj, MAX_GAME_VOLUME);
  }

  if (f_forcefield || f_lava || f_volatile) {
    ain_hear hear;
    hear.f_directly_player = true;
    hear.hostile_level = 0.90f;
    hear.curiosity_level = 0.6f;
    if (sound_override_force_field == -1)
      hear.max_dist = Sounds[SOUND_FORCEFIELD_BOUNCE].max_distance;
    else
      hear.max_dist = Sounds[sound_override_force_field].max_distance;
    AINotify(playerobj, AIN_HEAR_NOISE, (void *)&hear);
  }

  // Do sound stuff when a player hits a wall
  if (!f_forcefield && !f_volatile && !f_lava && hitspeed > MIN_WALL_HIT_SOUND_VEL &&
      Players[playerobj->id].last_hit_wall_sound_time + MIN_PLAYER_WALL_SOUND_TIME < Gametime) {
    if (hitspeed < MAX_WALL_HIT_SOUND_VEL) {
      volume =
          MAX_GAME_VOLUME * (hitspeed - MIN_WALL_HIT_SOUND_VEL) / (MAX_WALL_HIT_SOUND_VEL - MIN_WALL_HIT_SOUND_VEL);
    }

    if (hitspeed > MIN_WALL_DAMAGE_SPEED) {
      if (playerobj == Player_object && playerobj->shields >= MIN_WALL_HIT_DAMAGE_SHIELDS) {
        if ((!(Game_mode & GM_MULTI)) || Netgame.local_role == LR_SERVER)
          ApplyDamageToPlayer(playerobj, playerobj, PD_WALL_HIT, WALL_DAMAGE);
        else {
          Multi_requested_damage_type = PD_WALL_HIT;
          Multi_requested_damage_amount += (WALL_DAMAGE);
        }
      }
    }

    Sound_system.Play3dSound(SOUND_PLAYER_HIT_WALL, SND_PRIORITY_NORMAL, playerobj, volume);
    if (Demo_flags == DF_RECORDING)
      DemoWrite3DSound(SOUND_PLAYER_HIT_WALL, OBJNUM(playerobj), 1, volume);

    ain_hear hear;
    hear.f_directly_player = true;
    hear.hostile_level = 0.10f;
    hear.curiosity_level = 0.5f;
    hear.max_dist = Sounds[SOUND_PLAYER_HIT_WALL].max_distance * volume;
    AINotify(playerobj, AIN_HEAR_NOISE, (void *)&hear);

    Players[playerobj->id].last_hit_wall_sound_time = Gametime;
  }

  if (Players[playerobj->id].flags & PLAYER_FLAGS_DYING)
    StartPlayerExplosion(playerobj->id);

  // Do ForceFeedback
  //----------------
  if (playerobj->id == Player_num && ForceIsEnabled()) {
    DoForceForWall(playerobj, hitspeed, hitseg, hitwall, wall_normal);
  }

  return;
}

void collide_generic_and_wall(object *genericobj, float hitspeed, int hitseg, int hitwall, vector *hitpt,
                              vector *wall_normal, float hit_dot) {
  bool f_volatile, f_lava;
  bool f_forcefield;
  float volume = MAX_GAME_VOLUME;

  // Check for a trigger on this wall
  int tmap;
  if (!ROOMNUM_OUTSIDE(hitseg)) // Make sure we've hit a wall, and not terrain
  {
    CheckTrigger(hitseg, hitwall, genericobj, TT_COLLIDE);
    tmap = Rooms[hitseg].faces[hitwall].tmap;
  } else {
    tmap = Terrain_tex_seg[Terrain_seg[CELLNUM(hitseg)].texseg_index].tex_index;
  }
  f_forcefield = (GameTextures[tmap].flags & TF_FORCEFIELD) != 0;
  f_volatile = (GameTextures[tmap].flags & TF_VOLATILE) != 0;
  f_lava = (GameTextures[tmap].flags & TF_LAVA) != 0;

  if (IS_GUIDEBOT(genericobj)) {
    f_forcefield = false;
    f_volatile = false;
    f_lava = false;
  }

  if (f_lava) {
    if (!((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
      int id = FindWeaponName("NapalmBlob");
      if (id >= 0)
        SetNapalmDamageEffect(genericobj, NULL, id);
      else
        Int3();
    }
  }

  // If volatile, make the sound & apply damage
  if (f_volatile && !((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
    ApplyDamageToGeneric(genericobj, genericobj, GD_VOLATILE_HISS, VOLATILE_DAMAGE);
    Sound_system.Play3dSound(SOUND_VOLATILE_HISS, SND_PRIORITY_HIGHEST, genericobj, MAX_GAME_VOLUME);
  }

  if (f_forcefield && !((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
    if (sound_override_force_field == -1) {
      Sound_system.Play3dSound(SOUND_FORCEFIELD_BOUNCE, SND_PRIORITY_LOW, genericobj, MAX_GAME_VOLUME);
      ApplyDamageToGeneric(genericobj, genericobj, GD_ENERGY, FORCEFIELD_DAMAGE);
    } else {
      Sound_system.Play3dSound(sound_override_force_field, SND_PRIORITY_LOW, genericobj, MAX_GAME_VOLUME);
    }
  }

  if (genericobj->control_type != CT_AI) {
    if (!f_forcefield && !f_volatile && !f_lava && hitspeed > MIN_WALL_HIT_SOUND_VEL) {
      if (hitspeed < MAX_WALL_HIT_SOUND_VEL) {
        volume =
            MAX_GAME_VOLUME * (hitspeed - MIN_WALL_HIT_SOUND_VEL) / (MAX_WALL_HIT_SOUND_VEL - MIN_WALL_HIT_SOUND_VEL);
      }

      if (hitspeed > MIN_WALL_DAMAGE_SPEED) {
        if ((!(Game_mode & GM_MULTI)) || Netgame.local_role == LR_SERVER) {
          ApplyDamageToGeneric(genericobj, genericobj, GD_PHYSICS, WALL_DAMAGE);
        }
      }

      Sound_system.Play3dSound(SOUND_PLAYER_HIT_WALL, SND_PRIORITY_LOW, genericobj, volume);
      if (Demo_flags == DF_RECORDING)
        DemoWrite3DSound(SOUND_PLAYER_HIT_WALL, OBJNUM(genericobj), 1, volume);
    }
  }

  return;
}

static float Last_volatile_scrape_sound_time = 0;

// this gets called when an object is scraping along the wall
void scrape_object_on_wall(object *obj, int hitseg, int hitwall, vector *hitpt, vector *wall_normal) {
  /*	switch (obj->type) {

                  case OBJ_PLAYER:

                          if (obj->id==Player_num) {
                                  int type;

                                  //mprintf(0, "Scraped segment #%3i, side #%i\n", hitseg, hitside);

                                  if ((type=check_volatile_wall(obj,hitseg,hitside,hitpt))!=0) {
                                          vector	hit_dir, rand_vec;

                                          if ((GameTime > Last_volatile_scrape_sound_time + F1_0/4) || (GameTime <
     Last_volatile_scrape_sound_time)) { int sound = (type==1)?SOUND_VOLATILE_WALL_HISS:SOUND_SHIP_IN_WATER;

                                                  Last_volatile_scrape_sound_time = GameTime;

                                                  digi_link_sound_to_pos( sound, hitseg, 0, hitpt, 0, F1_0 );
                                                  if (Game_mode & GM_MULTI)
                                                          multi_send_play_sound(sound, F1_0);
                                          }

                                          #ifdef COMPACT_SEGS
                                                  get_side_normal(&Segments[hitseg], higside, 0, &hit_dir );
                                          #else
                                                  hit_dir = Segments[hitseg].sides[hitside].normals[0];
                                          #endif

                                          make_random_vector(&rand_vec);
                                          vm_vec_scale_add2(&hit_dir, &rand_vec, F1_0/8);
                                          vm_vec_normalize_quick(&hit_dir);
                                          bump_one_object(obj, &hit_dir, F1_0*8);
                                  }

                                  //@@} else {
                                  //@@	//what scrape sound
                                  //@@	//PLAY_SOUND( SOUND_PLAYER_SCRAPE_WALL );
                                  //@@}

                          }

                          break;

                  //these two kinds of objects below shouldn't really slide, so
                  //if this scrape routine gets called (which it might if the
                  //object (such as a fusion blob) was created already poking
                  //through the wall) call the collide routine.

                  case OBJ_WEAPON:
                          collide_weapon_and_wall(obj,0,hitseg,hitside,hitpt);
                          break;

                  case OBJ_DEBRIS:
                          collide_debris_and_wall(obj,0,hitseg,hitside,hitpt);
                          break;
          }
  */
}
/*
void apply_damage_to_player(object *playerobj, object *killer, float damage)
{
        if (Player_is_dead)
                return;

        if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE)
                return;

        if (Endlevel_sequence)
                return;

        //for the player, the 'real' shields are maintained in the Players[]
        //array.  The shields value in the player's object are, I think, not
        //used anywhere.  This routine, however, sets the objects shields to
        //be a mirror of the value in the Player structure.

        if (playerobj->id == Player_num) {		//is this the local player?

                //	MK: 08/14/95: This code can never be reached.  See the return about 12 lines up.
// -- 		if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE) {
// --
// -- 			//invincible, so just do blue flash
// --
// -- 			PALETTE_FLASH_ADD(0,0,f2i(damage)*4);	//flash blue
// --
// -- 		}
// -- 		else {		//take damage, do red flash

                        Players[Player_num].shields -= damage;

                        PALETTE_FLASH_ADD(f2i(damage)*4,-f2i(damage/2),-f2i(damage/2));	//flash red

// -- 		}

                if (Players[Player_num].shields < 0)	{

                        Players[Player_num].killer_objnum = killer-Objects;

//			if ( killer && (killer->type == OBJ_PLAYER))
//				Players[Player_num].killer_objnum = killer-Objects;

                        playerobj->flags |= OF_DEAD;

                        if (Buddy_objnum != -1)
                                if ((killer->type == OBJ_ROBOT) && (Robot_info[killer->id].companion))
                                        Buddy_sorry_time = GameTime;
                }
// -- removed, 09/06/95, MK --  else if (Players[Player_num].shields < LOSE_WEAPON_THRESHOLD) {
// -- removed, 09/06/95, MK -- 			int	randnum = ps_rand();
// -- removed, 09/06/95, MK --
// -- removed, 09/06/95, MK -- 			if (floatmul(Players[Player_num].shields, randnum) < damage/4) {
// -- removed, 09/06/95, MK -- 				if (ps_rand() > 20000) {
// -- removed, 09/06/95, MK -- 					destroy_secondary_weapon(Secondary_weapon);
// -- removed, 09/06/95, MK -- 				} else if (Primary_weapon == 0) {
// -- removed, 09/06/95, MK -- 					if (Players[Player_num].flags &
PLAYER_FLAGS_QUAD_LASERS)
// -- removed, 09/06/95, MK --
destroy_primary_weapon(MAX_PRIMARY_WEAPONS);	//	This means to destroy quad laser.
// -- removed, 09/06/95, MK -- 					else if (Players[Player_num].laser_level > 0)
// -- removed, 09/06/95, MK -- 						destroy_primary_weapon(Primary_weapon);
// -- removed, 09/06/95, MK -- 				} else
// -- removed, 09/06/95, MK -- 					destroy_primary_weapon(Primary_weapon);
// -- removed, 09/06/95, MK -- 			} else
// -- removed, 09/06/95, MK -- 				; // mprintf(0, "%8x > %8x, so don't lose weapon.\n",
floatmul(Players[Player_num].shields, randnum), damage/4);
// -- removed, 09/06/95, MK -- 		}

                playerobj->shields = Players[Player_num].shields;		//mirror

        }
}
*/

void CollideAnglesToMatrix(matrix *m, float p, float h, float b) {
  float sinp, cosp, sinb, cosb, sinh, cosh;

  sinp = sin(p);
  cosp = cos(p);
  sinb = sin(b);
  cosb = cos(b);
  sinh = sin(h);
  cosh = cos(h);

  m->rvec.x = cosb * cosh;
  m->rvec.y = cosb * sinp * sinh - cosp * sinb;
  m->rvec.z = cosb * cosp * sinh + sinb * sinp;

  m->uvec.x = cosh * sinb;
  m->uvec.y = sinb * sinp * sinh + cosp * cosb;
  m->uvec.z = sinb * cosp * sinh - cosb * sinp;

  m->fvec.x = -sinh;
  m->fvec.y = sinp * cosh;
  m->fvec.z = cosp * cosh;
}

vector *CollideExtractAnglesFromMatrix(vector *a, matrix *m) {
  float sinh, cosh, sinp, sinb;

  sinh = -m->fvec.x;
  if (sinh < -1.0f)
    sinh = -1.0f;
  else if (sinh > 1.0f)
    sinh = 1.0f;
  a->y = asin(sinh);

  cosh = cos(a->y);
  ASSERT(cosh != 0.0);

  sinp = m->fvec.y / cosh;
  if (sinp < -1.0f)
    sinp = -1.0f;
  else if (sinp > 1.0f)
    sinp = 1.0f;

  sinb = m->uvec.x / cosh;
  if (sinb < -1.0f)
    sinb = -1.0f;
  else if (sinb > 1.0f)
    sinb = 1.0f;

  a->x = asin(sinp);
  a->z = asin(sinb);

  return a;
}

void ConvertEulerToAxisAmount(vector *e, vector *n, float *w) {
  float rotspeed = vm_GetMagnitude(e);
  matrix rotmat;
  vector e_n;
  float scale = rotspeed / .0001f;

  // If there isn't a rotation, return something valid
  if (rotspeed == 0.0f || scale == 0.0f) {
    *n = Zero_vector;
    n->y = 1.0f;
    *w = 0.0f;

    return;
  }

  e_n = *e / scale;

  //	vector f;
  CollideAnglesToMatrix(&rotmat, e_n.x, e_n.y, e_n.z);

  //	mprintf(0, "F %f, %f, %f\n", XYZ(&rotmat.fvec));
  //	mprintf(0, "R %f, %f, %f\n", XYZ(&rotmat.rvec));
  //	mprintf(0, "U %f, %f, %f\n", XYZ(&rotmat.uvec));

  //	CollideExtractAnglesFromMatrix(&f, &rotmat);

  //	mprintf(0, "Before %f, %f, %f\n", XYZ(&e_n));
  //	mprintf(0, "After  %f, %f, %f\n", XYZ(&f));

  // This is from Graphics Gems 1 p.467  I am converting from a angle vector
  // to the normal of that rotation (you can also get the angle about that normal, but
  // we don't need it)
  n->x = rotmat.uvec.z - rotmat.fvec.y;
  n->y = rotmat.fvec.x - rotmat.rvec.z;
  n->z = rotmat.rvec.y - rotmat.uvec.x;

  if (*n != Zero_vector) {
    vm_NormalizeVector(n);

    float ct = (rotmat.rvec.x + rotmat.uvec.y + rotmat.fvec.z - 1.0f) / 2.0f;
    if (ct < -1.0f)
      ct = -1.0f;
    else if (ct > 1.0f)
      ct = 1.0f;

    float v = acos(ct);
    float z = sin(v);

    //		if(v < 0.0)
    //			*w = -rotspeed;
    //		else
    *w = rotspeed * ((2.0f * PI) / (65535.0f));

    if (z >= 0.0f)
      *n *= -1.0f;
  } else {
    *w = 0.0f;
  }
}

void ConvertAxisAmountToEuler(vector *n, float *w, vector *e) {
  float s;
  float c;
  float t;

  float scale = *w / .0001f;
  float w_n = .0001f;
  vector s_result;

  if (*w == 0.0f) {
    *e = Zero_vector;
    return;
  }

  s = sin(.0001);
  c = cos(.0001);
  t = 1.0f - c;

  matrix rotmat;
  const float sx = s * n->x;
  const float sy = s * n->y;
  const float sz = s * n->z;
  const float txy = t * n->x * n->y;
  const float txz = t * n->x * n->z;
  const float tyz = t * n->y * n->z;
  const float txx = t * n->x * n->x;
  const float tyy = t * n->y * n->y;
  const float tzz = t * n->z * n->z;

  rotmat.rvec.x = txx + c;
  rotmat.rvec.y = txy - sz;
  rotmat.rvec.z = txz + sy;
  rotmat.uvec.x = txy + sz;
  rotmat.uvec.y = tyy + c;
  rotmat.uvec.z = tyz - sx;
  rotmat.fvec.x = txz - sy;
  rotmat.fvec.y = tyz + sx;
  rotmat.fvec.z = tzz + c;

  CollideExtractAnglesFromMatrix(&s_result, &rotmat);

  e->x = (s_result.x) * scale * (65535.0f / (2.0 * PI));
  e->y = (s_result.y) * scale * (65535.0f / (2.0 * PI));
  e->z = (s_result.z) * scale * (65535.0f / (2.0 * PI));
}

void bump_obj_against_fixed(object *obj, vector *collision_point, vector *collision_normal) {
  ASSERT(std::isfinite(obj->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(obj->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(obj->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(obj->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(obj->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(obj->mtype.phys_info.velocity.z));

  if (!IsOKToApplyForce(obj))
    return;

  vector r1 = *collision_point - obj->pos;
  vector w1;
  vector n1;
  float temp1;

  float j;

  matrix o_t1 = obj->orient;
  vm_TransposeMatrix(&o_t1);

  vector cmp1 = obj->mtype.phys_info.rotvel * o_t1;

  ConvertEulerToAxisAmount(&cmp1, &n1, &temp1);

  n1 *= temp1;

  if (temp1 != 0.0f) {
    vm_CrossProduct(&w1, &n1, &r1);
  } else {
    w1 = Zero_vector;
  }

  vector p1 = obj->mtype.phys_info.velocity + w1;
  float v_rel;

  float m1 = obj->mtype.phys_info.mass;

  ASSERT(m1 != 0.0f);
  if (m1 <= 0.0f)
    m1 = 0.00000001f;

  v_rel = *collision_normal * (p1);

  float e = obj->mtype.phys_info.coeff_restitution;

  vector c1;
  vector cc1;
  float cv1;

  //	matrix i1;
  //	matrix i2;
  float i1 = (2.0f / 5.0f) * m1 * obj->size * obj->size;

  if (i1 < .0000001)
    i1 = .0000001f;

  vm_CrossProduct(&c1, &r1, collision_normal);

  c1 = c1 / i1;

  vm_CrossProduct(&cc1, &c1, &r1);

  cv1 = (*collision_normal) * c1;

  j = (-(1.0f + e)) * v_rel;
  j /= (1 / m1 + cv1);

  obj->mtype.phys_info.velocity += ((j * (*collision_normal)) / m1);

  vector jcn = j * (*collision_normal);

  vm_CrossProduct(&c1, &r1, &jcn);

  n1 = (c1) / i1;

  temp1 = vm_NormalizeVector(&n1);

  vector txx1;

  ConvertAxisAmountToEuler(&n1, &temp1, &txx1);

  obj->mtype.phys_info.rotvel += (txx1 * obj->orient);

  ASSERT(std::isfinite(obj->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(obj->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(obj->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(obj->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(obj->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(obj->mtype.phys_info.velocity.z));

  // hack rotvel
  /*	vector v = obj->mtype.phys_info.velocity;
          vector c = *collision_normal;

          if(v != Zero_vector)
          {
                  vm_NormalizeVector(&v);

                  if(v != c)
                  {
                          float rad = vm_VectorDistance(&obj->pos, collision_point);
                          float rotvel = vm_GetMagnitude(&obj->mtype.phys_info.velocity)*((2*PI*rad));
                          vector r;
                          vector e;

                          vm_CrossProduct(&r, &v, &c);
                          vm_NormalizeVector(&r);

                          ConvertAxisAmountToEuler(&r, &rotvel, &e);

                          matrix rrr = obj->orient;
  //			vm_TransposeMatrix(&rrr);
                          obj->mtype.phys_info.rotvel = rrr * r;
                  }
                  else
                  {
                          obj->mtype.phys_info.rotvel = Zero_vector;
                  }
          }
          else
          {
                  obj->mtype.phys_info.rotvel = Zero_vector;
          }*/
}

void bump_two_objects(object *object0, object *object1, vector *collision_point, vector *collision_normal,
                      int damage_flag) {
  //	vector force;	//dv,
  object *t = NULL;
  object *other = NULL;

  // Determine if a moving object hits a non-moving object
  if ((object0->movement_type != MT_PHYSICS && object0->movement_type != MT_WALKING) ||
      (object0->movement_type == MT_PHYSICS && object0->mtype.phys_info.velocity == Zero_vector &&
       (object0->mtype.phys_info.flags & PF_LOCK_MASK) && (object0->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))) {
    t = object1;
    other = object0;
    *collision_normal *= -1.0f;
  }
  if ((object1->movement_type != MT_PHYSICS && object1->movement_type != MT_WALKING) ||
      (object1->movement_type == MT_PHYSICS && object1->mtype.phys_info.velocity == Zero_vector &&
       (object1->mtype.phys_info.flags & PF_LOCK_MASK) && (object1->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))) {
    t = object0;
    other = object1;
  }

  // If we hit a non-moving object...
  if (t) {
    // chrishack -- walker hack
    if (t->movement_type != MT_PHYSICS && t->movement_type != MT_WALKING) {
      t->mtype.phys_info.velocity = Zero_vector;
      return;
    }

    if (t->mtype.phys_info.flags & PF_PERSISTENT)
      return;

    vector moved_v;
    float wall_part;

    float luke_test;

    if (t->type == OBJ_PLAYER) {
      luke_test = vm_GetMagnitude(&t->mtype.phys_info.velocity);
    }

    if (!(t->flags & OF_DEAD)) {
      //			bump_obj_against_fixed(t, collision_point, collision_normal);
      //		}
      ///*
      // Find hit speed
      moved_v = t->pos - t->last_pos;
      wall_part = *collision_normal * t->mtype.phys_info.velocity;

      if (t->mtype.phys_info.flags & PF_BOUNCE) {
        wall_part *= 2.0; // Subtract out wall part twice to achieve bounce

        // New bounceness code
        if ((t->mtype.phys_info.flags & PF_BOUNCE) && (t->mtype.phys_info.num_bounces != PHYSICS_UNLIMITED_BOUNCE)) {
          if (t->mtype.phys_info.num_bounces == 0) {
            ASSERT(t->type != OBJ_PLAYER);
            if (t->flags & OF_DYING) {
              ASSERT((t->control_type == CT_DYING) || (t->control_type == CT_DYING_AND_AI));
              DestroyObject(t, 50.0, t->ctype.dying_info.death_flags);
            } else
              SetObjectDeadFlag(t);
          }
        }
        t->mtype.phys_info.num_bounces--;

        t->mtype.phys_info.velocity += *collision_normal * (wall_part * -1.0f);

        if (t->mtype.phys_info.coeff_restitution != 1.0f)
          t->mtype.phys_info.velocity -= (t->mtype.phys_info.velocity * (1.0f - t->mtype.phys_info.coeff_restitution));
      } else {
        float wall_force;

        wall_force = t->mtype.phys_info.thrust * *collision_normal;
        t->mtype.phys_info.thrust +=
            *collision_normal * (wall_force * -1.001); // 1.001 so that we are not quite tangential

        // Update velocity from wall hit.
        t->mtype.phys_info.velocity +=
            *collision_normal * (wall_part * -1.001); // 1.001 so that we are not quite tangential
        if (t->type == OBJ_PLAYER) {
          float real_vel;

          real_vel = vm_NormalizeVector(&t->mtype.phys_info.velocity);
          t->mtype.phys_info.velocity *= ((real_vel + luke_test) / 2.0f);
          // obj->mtype.phys_info.velocity *= (luke_test);
        }
      }

      // Weapons should face their new heading.  This is so missiles are pointing in the correct direct.
      if (t->type == OBJ_WEAPON && (t->mtype.phys_info.flags & (PF_BOUNCE | PF_GRAVITY | PF_WIND)))
        vm_VectorToMatrix(&t->orient, &t->mtype.phys_info.velocity, &t->orient.uvec, NULL);
    }

    // Return it to the original direction
    if (object0->movement_type != MT_PHYSICS && object0->movement_type != MT_WALKING) {
      *collision_normal *= -1.0f;
    }

    // Do ForceFeedback stuff for non-moving objects
    //-----------------------------------------
    if (ForceIsEnabled()) {

      if (object0->type == OBJ_PLAYER && object0->id == Player_num) {
      }
    }
    //*/
    return;
  }

  //	force = object0->mtype.phys_info.velocity - object1->mtype.phys_info.velocity;
  //	force *= 2*(object0->mtype.phys_info.mass * object1->mtype.phys_info.mass)/(object0->mtype.phys_info.mass +
  // object1->mtype.phys_info.mass);

  //	if(!(object1->mtype.phys_info.flags & PF_PERSISTENT))
  //		bump_this_object(object1, object0, &force, collision_point, damage_flag);
  //
  //	force = -force;
  //
  //	if(!(object0->mtype.phys_info.flags & PF_PERSISTENT))
  //		bump_this_object(object0, object1, &force, collision_point, damage_flag);

  //	vector r_vel = object0->mtype.phys_info.velocity - object1->mtype.phys_info.velocity;
  // Add this back

  ASSERT(std::isfinite(object1->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(object1->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(object1->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(object1->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(object1->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(object1->mtype.phys_info.velocity.z));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.z));

  vector r1 = *collision_point - object0->pos;
  vector r2 = *collision_point - object1->pos;
  vector w1;
  vector w2;
  vector n1;
  vector n2;
  float temp1;
  float temp2;

  float j;

  matrix o_t1 = object0->orient;
  matrix o_t2 = object1->orient;

  vm_TransposeMatrix(&o_t1);
  vm_TransposeMatrix(&o_t2);

  vector cmp1 = object0->mtype.phys_info.rotvel * o_t1;
  vector cmp2 = object1->mtype.phys_info.rotvel * o_t2;

  ConvertEulerToAxisAmount(&cmp1, &n1, &temp1);
  ConvertEulerToAxisAmount(&cmp2, &n2, &temp2);

  n1 *= temp1;
  n2 *= temp2;

  if (temp1 != 0.0f) {
    vm_CrossProduct(&w1, &n1, &r1);
  } else {
    w1 = Zero_vector;
  }

  if (temp2 != 0.0f) {
    vm_CrossProduct(&w2, &n2, &r2);
  } else {
    w2 = Zero_vector;
  }

  vector p1 = object0->mtype.phys_info.velocity + w1;
  vector p2 = object1->mtype.phys_info.velocity + w2;
  float v_rel;

  float m1 = object0->mtype.phys_info.mass;
  float m2 = object1->mtype.phys_info.mass;

  bool f_force_1 = IsOKToApplyForce(object0);
  bool f_force_2 = IsOKToApplyForce(object1);

  ASSERT(m1 != 0.0f && m2 != 0.0f);
  if (m1 <= 0.0f)
    m1 = 0.00000001f;
  if (m2 <= 0.0f)
    m2 = 0.00000001f;

  v_rel = *collision_normal * (p1 - p2);

  float e;

  if (object0->type == OBJ_PLAYER && object1->type == OBJ_PLAYER)
    e = 0.015f;
  else if ((object0->type == OBJ_WEAPON || object1->type == OBJ_WEAPON) &&
           (object0->type != OBJ_PLAYER && object1->type != OBJ_PLAYER))
    e = 1.0f;
  else if ((object0->type == OBJ_CLUTTER && object1->type == OBJ_PLAYER) ||
           (object0->type == OBJ_PLAYER && object1->type == OBJ_CLUTTER))
    e = 0.5f;
  else
    e = 0.1f;

  vector c1;
  vector c2;
  vector cc1;
  vector cc2;
  float cv1;
  float cv2;

  //	matrix i1;
  //	matrix i2;
  float i1 = (2.0f / 5.0f) * m1 * object0->size * object0->size;
  float i2 = (2.0f / 5.0f) * m2 * object1->size * object1->size;

  if (i1 < .0000001)
    i1 = .0000001f;
  if (i2 < .0000001)
    i2 = .0000001f;

  vm_CrossProduct(&c1, &r1, collision_normal);
  vm_CrossProduct(&c2, &r2, collision_normal);

  c1 = c1 / i1;
  c2 = c2 / i2;

  vm_CrossProduct(&cc1, &c1, &r1);
  vm_CrossProduct(&cc2, &c2, &r2);

  cv1 = (*collision_normal) * c1;
  cv2 = (*collision_normal) * c2;

  j = (-(1.0f + e)) * v_rel;
  j /= (1 / m1 + 1 / m2 + cv1 + cv2);

  if (f_force_1)
    object0->mtype.phys_info.velocity += ((j * (*collision_normal)) / m1);

  if (f_force_2)
    object1->mtype.phys_info.velocity -= ((j * (*collision_normal)) / m2);

  vector jcn = j * (*collision_normal);

  vm_CrossProduct(&c1, &r1, &jcn);
  vm_CrossProduct(&c2, &r2, &jcn);

  n1 = (c1) / i1;
  n2 = (c2) / i2;

  temp1 = vm_NormalizeVector(&n1);
  temp2 = vm_NormalizeVector(&n2);

  vector txx1;
  vector txx2;

  ConvertAxisAmountToEuler(&n1, &temp1, &txx1);
  ConvertAxisAmountToEuler(&n2, &temp2, &txx2);

  float rotscale1, rotscale2;

  if (object0->type == OBJ_PLAYER)
    rotscale1 = PLAYER_ROTATION_BY_FORCE_SCALAR;
  else
    rotscale1 = NONPLAYER_ROTATION_BY_FORCE_SCALAR;

  if (object1->type == OBJ_PLAYER)
    rotscale2 = PLAYER_ROTATION_BY_FORCE_SCALAR;
  else
    rotscale2 = NONPLAYER_ROTATION_BY_FORCE_SCALAR;

  if (f_force_1)
    object0->mtype.phys_info.rotvel += (txx1 * object0->orient) * rotscale1;

  if (f_force_2)
    object1->mtype.phys_info.rotvel += (txx2 * object1->orient) * rotscale2;

  ASSERT(std::isfinite(object1->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(object1->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(object1->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.rotvel.z));
  ASSERT(std::isfinite(object1->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(object1->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(object1->mtype.phys_info.velocity.z));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.x));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.y));
  ASSERT(std::isfinite(object0->mtype.phys_info.velocity.z));

  // Do ForceFeedback stuff for moving objects
  //-----------------------------------------
  if (ForceIsEnabled()) {

    if (object0->type == OBJ_PLAYER && object0->id == Player_num) {
      // v is the force vector
      vector v;
      v = -1.0 * v_rel * (*collision_normal);

      // Was it weapon->player collide
      switch (object1->type) {
      case OBJ_WEAPON:
        // Do force effect for player/weapon collision
        DoForceForWeapon(object0, object1, &v);
        break;
      default:
        break;
      }
    }
  }

  // Catch things on fire if possible
  if (object0->effect_info && object1->effect_info) {
    // One of these objects must be burning
    if ((object0->effect_info->type_flags & EF_NAPALMED) || (object1->effect_info->type_flags & EF_NAPALMED)) {
      // Both cannot be burning
      if (!(object0->effect_info->type_flags & EF_NAPALMED) || !(object1->effect_info->type_flags & EF_NAPALMED)) {
        object *src_obj, *dest_obj;
        if (object0->effect_info->type_flags & EF_NAPALMED) {
          src_obj = object0;
          dest_obj = object1;
        } else {
          src_obj = object1;
          dest_obj = object0;
        }

        dest_obj->effect_info->type_flags |= EF_NAPALMED;

        dest_obj->effect_info->damage_time = std::max(1.0, src_obj->effect_info->damage_time / 3.0);
        dest_obj->effect_info->damage_per_second = src_obj->effect_info->damage_per_second;

        // We need this cap (as the gb burns forever
        if (dest_obj->effect_info->damage_time > 10.0f) {
          dest_obj->effect_info->damage_time = 10.0f;
        }

        dest_obj->effect_info->last_damage_time = 0;

        dest_obj->effect_info->damage_handle = src_obj->handle;

        if (dest_obj->effect_info->sound_handle == SOUND_NONE_INDEX)
          dest_obj->effect_info->sound_handle =
              Sound_system.Play3dSound(SOUND_PLAYER_BURNING, SND_PRIORITY_HIGHEST, dest_obj);
      }
    }
  }
}

void collide_player_and_player(object *p1, object *p2, vector *collision_point, vector *collision_normal,
                               bool f_reverse_normal, fvi_info *hit_info) {
  if (f_reverse_normal)
    *collision_normal *= -1.0f;

  vector rvel = p1->mtype.phys_info.velocity - p2->mtype.phys_info.velocity;
  float speed = vm_NormalizeVector(&rvel);
  float scalar;

  if (speed <= MIN_WALL_HIT_SOUND_VEL) {
    scalar = 0.0f;
  } else if (speed >= MAX_WALL_HIT_SOUND_VEL) {
    scalar = 1.0f;
  } else {
    scalar = (speed - MIN_WALL_HIT_SOUND_VEL) / (MAX_WALL_HIT_SOUND_VEL - MIN_WALL_HIT_SOUND_VEL);
  }

  if (scalar > .01) {
    pos_state cur_pos;
    cur_pos.position = collision_point;
    cur_pos.orient = &p1->orient;
    cur_pos.roomnum = p1->roomnum;

    Sound_system.Play3dSound(SOUND_PLAYER_HIT_WALL, SND_PRIORITY_HIGHEST, &cur_pos, MAX_GAME_VOLUME * scalar);
  }

  bump_two_objects(p1, p2, collision_point, collision_normal, 1);
}

#include "polymodel.h"

void collide_generic_and_player(object *robotobj, object *playerobj, vector *collision_point, vector *collision_normal,
                                bool f_reverse_normal, fvi_info *hit_info) {
  if (f_reverse_normal)
    *collision_normal *= -1.0f;

  vector rvel;
  if (robotobj->movement_type == MT_PHYSICS || robotobj->movement_type == MT_WALKING) {
    rvel = robotobj->mtype.phys_info.velocity;
  } else {
    rvel = Zero_vector;
  }
  rvel -= playerobj->mtype.phys_info.velocity;
  float speed = vm_NormalizeVector(&rvel);
  float scalar;

  if (speed <= MIN_WALL_HIT_SOUND_VEL) {
    scalar = 0.0f;
  } else if (speed >= MAX_WALL_HIT_SOUND_VEL) {
    scalar = 1.0f;
  } else {
    scalar = (speed - MIN_WALL_HIT_SOUND_VEL) / (MAX_WALL_HIT_SOUND_VEL - MIN_WALL_HIT_SOUND_VEL);
  }

  // Check for lava surface on an object
  if ((robotobj->type == OBJ_BUILDING) && hit_info) {
    poly_model *pm = GetPolymodelPointer(robotobj->rtype.pobj_info.model_num);
    int tmap = pm->textures[pm->submodel[hit_info->hit_subobject[0]].faces[hit_info->hit_face[0]].texnum];

    if (GameTextures[tmap].flags & TF_LAVA) {
      if (!((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
        int id = FindWeaponName("NapalmBlob");
        if (id >= 0)
          SetNapalmDamageEffect(playerobj, NULL, id);
        else
          Int3();
      }
      scalar = 0; // don't make collide sound
    }
  }

  if (scalar > .01 || (robotobj->mtype.phys_info.flags & PF_LOCK_MASK)) {
    pos_state cur_pos;
    cur_pos.position = collision_point;
    cur_pos.orient = &playerobj->orient;
    cur_pos.roomnum = playerobj->roomnum;

    Sound_system.Play3dSound(SOUND_PLAYER_HIT_WALL, SND_PRIORITY_HIGHEST, &cur_pos, MAX_GAME_VOLUME * scalar);

    ain_hear hear;
    hear.f_directly_player = true;
    hear.hostile_level = 0.10f;
    hear.curiosity_level = 0.5f;
    hear.max_dist = Sounds[SOUND_PLAYER_HIT_WALL].max_distance * scalar;
    AINotify(playerobj, AIN_HEAR_NOISE, (void *)&hear);

    if ((scalar > .25f && (robotobj->movement_type == MT_WALKING || robotobj->movement_type == MT_PHYSICS)) ||
        ((robotobj->mtype.phys_info.flags & PF_LOCK_MASK) &&
         (robotobj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))) {
      if (!(IS_GUIDEBOT(robotobj))) {
        if (robotobj->shields <= 1.0f) {
          ApplyDamageToGeneric(robotobj, playerobj, GD_PHYSICS, 2.0f);
        } else {
          ApplyDamageToGeneric(robotobj, playerobj, GD_PHYSICS, 5.0f * Frametime * scalar);
        }
        if (scalar < 1.0f && (robotobj->mtype.phys_info.flags & PF_LOCK_MASK) &&
            (robotobj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))
          scalar = 1.0f;

        ApplyDamageToPlayer(playerobj, playerobj, PD_WALL_HIT, 2.0f * Frametime * scalar);
      }
    }
  }

  // mprintf(0, "We hit a robot\n");
  if (robotobj->control_type == CT_AI) {
    AINotify(robotobj, AIN_BUMPED_OBJ, (void *)playerobj);
  }

  /*	if((GameTextures[Rooms[hitseg].faces[hitwall].tmap].flags & TF_VOLATILE) && !((Game_mode & GM_MULTI) &&
     (Netgame.local_role==LR_CLIENT)))
          {
                  int id = FindWeaponName("NapalmBlob");
                  if(id >= 0)
                  {
                          int objnum = ObjCreate(OBJ_WEAPON, id, playerobj->roomnum, &playerobj->pos, NULL,
     playerobj->handle);

                          if(objnum >= 0)
                          {
                                  object *weapon = &Objects[objnum];
                                  float damage_to_apply = Weapons[weapon->id].damage;

                                  // Factor in multiplier
                                  damage_to_apply *= weapon->ctype.laser_info.multiplier;

                                  ApplyDamageToPlayer(playerobj, weapon, 0);

                                  SetObjectDeadFlag(objnum);
                          }
                  }
          }
  */
  bump_two_objects(robotobj, playerobj, collision_point, collision_normal, 1);
}

void MakeWeaponStick(object *weapon, object *parent, fvi_info *hit_info) {
  weapon->mtype.obj_link_info.parent_handle = parent->handle;
  weapon->mtype.obj_link_info.fvec = hit_info->hit_subobj_fvec;
  weapon->mtype.obj_link_info.uvec = hit_info->hit_subobj_uvec;
  weapon->mtype.obj_link_info.pos = hit_info->hit_subobj_pos;
  weapon->mtype.obj_link_info.sobj_index = hit_info->hit_subobject[0];
  weapon->movement_type = MT_OBJ_LINKED;
}

void collide_generic_and_weapon(object *robotobj, object *weapon, vector *collision_point, vector *collision_normal,
                                bool f_reverse_normal, fvi_info *hit_info) {
  object *parent_obj;
  float damage_to_apply;
  uint8_t electrical = (Weapons[weapon->id].flags & WF_ELECTRICAL) ? 1 : 0;
  bool f_stick = ((weapon->mtype.phys_info.flags & PF_STICK) != 0);
  bool f_energy = ((Weapons[weapon->id].flags & WF_MATTER_WEAPON) == 0);
  int damage_type;

  // Check for lava & volatile surfaces on an object
  if ((robotobj->type == OBJ_BUILDING) && hit_info) {
    poly_model *pm = GetPolymodelPointer(robotobj->rtype.pobj_info.model_num);
    int tmap = pm->textures[pm->submodel[hit_info->hit_subobject[0]].faces[hit_info->hit_face[0]].texnum];
    vector *normal = &hit_info->hit_wallnorm[0];

    DoWallEffects(weapon, tmap);

    check_for_special_surface(weapon, tmap, normal, 1.0);

    // If object died, stop processing
    if (weapon->flags & OF_DEAD)
      return;
  }

  if (Weapons[weapon->id].flags & WF_NAPALM)
    damage_type = GD_FIRE;
  else if (Weapons[weapon->id].flags & WF_MATTER_WEAPON)
    damage_type = GD_MATTER;
  else if (Weapons[weapon->id].flags & WF_ELECTRICAL)
    damage_type = GD_ELECTRIC;
  else
    damage_type = GD_ENERGY;

  if (f_reverse_normal)
    *collision_normal *= -1.0f;

  if (robotobj->flags & OF_DYING)
    robotobj->ctype.dying_info.delay_time *= 0.975f;

  if (Weapons[weapon->id].sounds[WSI_IMPACT_WALL] != SOUND_NONE_INDEX) {
    Sound_system.Play3dSound(Weapons[weapon->id].sounds[WSI_IMPACT_WALL], SND_PRIORITY_HIGH, weapon);

    ain_hear hear;
    hear.f_directly_player = false;
    if (robotobj->control_type == CT_AI) {
      hear.hostile_level = 1.0f;
      hear.curiosity_level = 0.1f;
    } else if (robotobj->type == OBJ_DOOR) {
      hear.hostile_level = 0.5f;
      hear.curiosity_level = 1.0f;
    } else {
      hear.hostile_level = .9f;
      hear.curiosity_level = 0.5f;
    }

    hear.max_dist = Sounds[Weapons[weapon->id].sounds[WSI_IMPACT_WALL]].max_distance;
    AINotify(weapon, AIN_HEAR_NOISE, (void *)&hear);
  }

  // Do weapon explosion stuff
  DoWeaponExploded(weapon, collision_normal, collision_point);

  // Check to see if we should spawn
  if (robotobj->type == OBJ_DOOR && !(Game_mode & GM_MULTI)) {
    if ((Weapons[weapon->id].flags & WF_SPAWNS_IMPACT) && Weapons[weapon->id].spawn_count > 0 &&
        Weapons[weapon->id].spawn_handle >= 0)
      CreateImpactSpawnFromWeapon(weapon, collision_normal);
  }

  if ((Weapons[weapon->id].flags & WF_SPAWNS_ROBOT) && (Weapons[weapon->id].flags & WF_COUNTERMEASURE) &&
      Weapons[weapon->id].robot_spawn_handle >= 0)
    CreateRobotSpawnFromWeapon(weapon);

  parent_obj = ObjGet(weapon->parent_handle);

  if ((parent_obj) && (parent_obj->control_type == CT_AI)) {
    AINotify(parent_obj, AIN_WHIT_OBJECT, (void *)robotobj);
  }

  if (robotobj->control_type == CT_AI) {
    AINotify(robotobj, AIN_HIT_BY_WEAPON, (void *)weapon);
  }

  if (electrical) {
    damage_to_apply = Weapons[weapon->id].generic_damage * Frametime;
  } else
    damage_to_apply = Weapons[weapon->id].generic_damage;

  // Factor in multiplier
  damage_to_apply *= weapon->ctype.laser_info.multiplier;

  if (ApplyDamageToGeneric(robotobj, weapon, damage_type, damage_to_apply)) {
    if (Weapons[weapon->id].sounds[WSI_IMPACT_ROBOT] != SOUND_NONE_INDEX) {
      Sound_system.Play3dSound(Weapons[weapon->id].sounds[WSI_IMPACT_ROBOT], SND_PRIORITY_HIGHEST, weapon);
    }
    if (!electrical) {
      light_info *li = &Weapons[weapon->id].lighting_info;
      uint16_t color = GR_RGB16(li->red_light2 * 255, li->green_light2 * 255, li->blue_light2 * 255);
      CreateRandomLineSparks(3 + ps_rand() % 6, &weapon->pos, weapon->roomnum, color);
    }
  }
#if 0	
	if(Demo_flags == DF_RECORDING)
	{
		DemoWriteCollideGenericWeapon( robotobj, weapon, collision_point, collision_normal, f_reverse_normal, hit_info );	
	}
	else if(Demo_flags == DF_PLAYBACK)
	{
		//During playback we don't need the code below (actually it won't work)
		return;
	}
#endif

  if (!electrical) {

    bump_two_objects(robotobj, weapon, collision_point, collision_normal, 0);

    if (!f_stick || (hit_info == NULL)) {
      if ((robotobj->lighting_render_type == LRT_LIGHTMAPS) || !(weapon->mtype.phys_info.flags & PF_PERSISTENT))
        SetObjectDeadFlag(weapon);
    } else {
      MakeWeaponStick(weapon, robotobj, hit_info);
    }
  }
}

void collide_player_and_weapon(object *playerobj, object *weapon, vector *collision_point, vector *collision_normal,
                               bool f_reverse_normal, fvi_info *hit_info) {
  object *parent_obj;
  float damage_to_apply;
  uint8_t electrical = Weapons[weapon->id].flags & WF_ELECTRICAL ? 1 : 0;
  bool f_stick = ((weapon->mtype.phys_info.flags & PF_STICK) != 0);

  if (f_reverse_normal)
    *collision_normal *= -1.0f;

  parent_obj = ObjGet(weapon->parent_handle);

  if ((parent_obj) && (parent_obj->control_type == CT_AI)) {
    AINotify(parent_obj, AIN_WHIT_OBJECT, (void *)playerobj);
  }

  // Do weapon explosion stuff
  DoWeaponExploded(weapon, collision_normal, collision_point, playerobj);

  // Check to see if we should spawn
  /*if ((Weapons[weapon->id].flags & WF_SPAWNS_IMPACT) && Weapons[weapon->id].spawn_count>0 &&
     Weapons[weapon->id].spawn_handle>=0) CreateImpactSpawnFromWeapon (weapon,collision_normal);*/

  if ((Weapons[weapon->id].flags & WF_SPAWNS_ROBOT) && (Weapons[weapon->id].flags & WF_COUNTERMEASURE) &&
      Weapons[weapon->id].robot_spawn_handle >= 0)
    CreateRobotSpawnFromWeapon(weapon);

  if (electrical)
    damage_to_apply = Weapons[weapon->id].player_damage * Frametime;
  else
    damage_to_apply = Weapons[weapon->id].player_damage;

  // Factor in multiplier
  damage_to_apply *= weapon->ctype.laser_info.multiplier;

  int damage_type = electrical ? PD_ENERGY_WEAPON : PD_MATTER_WEAPON;

  if (ApplyDamageToPlayer(playerobj, weapon, damage_type, damage_to_apply)) {
    // we were damaged!
    if (Weapons[weapon->id].sounds[WSI_IMPACT_ROBOT] != SOUND_NONE_INDEX)
      Sound_system.Play3dSound(Weapons[weapon->id].sounds[WSI_IMPACT_ROBOT], SND_PRIORITY_NORMAL, weapon);
  }
#if 0		
	if(Demo_flags == DF_RECORDING)
	{
		DemoWriteCollidePlayerWeapon( playerobj, weapon, collision_point, collision_normal, f_reverse_normal, hit_info );	
	}
	else if(Demo_flags == DF_PLAYBACK)
	{
		//During playback we don't need the code below (actually it won't work)
		return;
	}
#endif

  if (!electrical) {
    bump_two_objects(playerobj, weapon, collision_point, collision_normal, 0);

    if (!f_stick || (hit_info == NULL)) {
      if (!(weapon->mtype.phys_info.flags & PF_PERSISTENT))
        SetObjectDeadFlag(weapon);
    } else {
      MakeWeaponStick(weapon, playerobj, hit_info);
    }
  }
}

#define COLLISION_OF(a, b) (((a) << 8) + (b))

#define DO_COLLISION(type1, type2, collision_function)                                                                 \
  case COLLISION_OF((type1), (type2)):                                                                                 \
    (collision_function)((A), (B), collision_point, collision_normal, false, hit_info);                                \
    break;                                                                                                             \
  case COLLISION_OF((type2), (type1)):                                                                                 \
    (collision_function)((B), (A), collision_point, collision_normal, true, hit_info);                                 \
    break;

#define DO_SAME_COLLISION(type1, type2, collision_function)                                                            \
  case COLLISION_OF((type1), (type1)):                                                                                 \
    (collision_function)((A), (B), collision_point, collision_normal, false, hit_info);                                \
    break;

#define NO_COLLISION(type1, type2)                                                                                     \
  case COLLISION_OF((type1), (type2)):                                                                                 \
  case COLLISION_OF((type2), (type1)):                                                                                 \
    break;

void check_lg_inform(object *A, object *B) {
  if (A->flags & (OF_INFORM_PLAYER_COLLIDE_TO_LG | OF_INFORM_PLAYER_WEAPON_COLLIDE_TO_LG)) {
    if (B->type == OBJ_PLAYER) {
      bool f_pwc = (A->flags & OF_INFORM_PLAYER_WEAPON_COLLIDE_TO_LG) != 0;
      int type;

      if (f_pwc) {
        type = OF_INFORM_PLAYER_WEAPON_COLLIDE_TO_LG;
      } else {
        type = OF_INFORM_PLAYER_COLLIDE_TO_LG;
      }

      Level_goals.Inform(LIT_OBJECT, type, A->handle);
    }
  }

  if (A->flags & OF_INFORM_PLAYER_WEAPON_COLLIDE_TO_LG) {
    if (B->type == OBJ_WEAPON) {
      object *parent = ObjGetUltimateParent(B);

      if (parent && parent->type == OBJ_PLAYER) {
        Level_goals.Inform(LIT_OBJECT, OF_INFORM_PLAYER_WEAPON_COLLIDE_TO_LG, A->handle);
      }
    }
  }
}

void collide_two_objects(object *A, object *B, vector *collision_point, vector *collision_normal, fvi_info *hit_info) {
  int collision_type;
  int a_num = OBJNUM(A);
  int b_num = OBJNUM(B);
  uint8_t a_good = 0, b_good = 0;
  uint8_t a_hittime_good = 1, b_hittime_good = 1;

  // Only do omega particle collisions if specifically allowed
  extern bool Enable_omega_collions;
  if (((A->type == OBJ_WEAPON) && (A->id == OMEGA_INDEX)) || ((B->type == OBJ_WEAPON) && (B->id == OMEGA_INDEX)))
    if (!Enable_omega_collions)
      return;

  ASSERT(CollisionResult[A->type][B->type] != RESULT_NOTHING);

  collision_type = COLLISION_OF(A->type, B->type);

  check_lg_inform(A, B);
  check_lg_inform(B, A);

  // mprintf( (0, "Object %d of type %d collided with object %d of type %d\n", A-Objects,A->type, B-Objects, B->type ));

  //	COLLISION SCRIPT HOOK
  if (Game_mode & GM_MULTI) {
    ASSERT(!(A->flags & OF_DEAD));
    ASSERT(!(B->flags & OF_DEAD));

    // Make sure we have good scripts to call
    if (A->type == OBJ_PLAYER || A->type == OBJ_ROBOT || A->type == OBJ_POWERUP || A->type == OBJ_WEAPON ||
        A->type == OBJ_BUILDING || A->type == OBJ_DOOR || A->type == OBJ_CLUTTER)
      a_good = 1;
    if (B->type == OBJ_PLAYER || B->type == OBJ_ROBOT || B->type == OBJ_POWERUP || B->type == OBJ_WEAPON ||
        B->type == OBJ_BUILDING || B->type == OBJ_DOOR || B->type == OBJ_CLUTTER)
      b_good = 1;

    if (A->type == OBJ_PLAYER && (Players[A->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD)))
      a_good = 0;
    if (B->type == OBJ_PLAYER && (Players[B->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD)))
      b_good = 0;

    if (A->type == OBJ_POWERUP && A->effect_info->last_object_hit == b_num &&
        (Gametime - A->effect_info->last_object_hit_time) < 1) {
      a_good = 0;
      a_hittime_good = 0;
    }

    if (B->type == OBJ_POWERUP && B->effect_info->last_object_hit == a_num &&
        (Gametime - B->effect_info->last_object_hit_time) < 1) {
      b_good = 0;
      b_hittime_good = 0;
    }

    if (a_good && b_good) {
      DLLInfo.me_handle = A->handle;
      DLLInfo.it_handle = B->handle;
      DLLInfo.collide_info.point.x = collision_point->x;
      DLLInfo.collide_info.point.y = collision_point->y;
      DLLInfo.collide_info.point.z = collision_point->z;
      DLLInfo.collide_info.normal.x = collision_normal->x;
      DLLInfo.collide_info.normal.y = collision_normal->y;
      DLLInfo.collide_info.normal.z = collision_normal->z;
      CallGameDLL(EVT_GAMECOLLIDE, &DLLInfo);

      DLLInfo.me_handle = B->handle;
      DLLInfo.it_handle = A->handle;
      CallGameDLL(EVT_GAMECOLLIDE, &DLLInfo);

      // Update static variables
      if (A->type == OBJ_POWERUP) {
        A->effect_info->last_object_hit = b_num;
        A->effect_info->last_object_hit_time = Gametime;
      }
      if (B->type == OBJ_POWERUP) {
        B->effect_info->last_object_hit = a_num;
        B->effect_info->last_object_hit_time = Gametime;
      }
    }
  }

  // Call script only if its ok to
  int ok_to_call_script = 1;
  if (A->type == OBJ_PLAYER && (Players[A->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD)))
    ok_to_call_script = 0;
  if (B->type == OBJ_PLAYER && (Players[B->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD)))
    ok_to_call_script = 0;

  // Check to see if we should call the script
  if ((Game_mode & GM_MULTI)) {
    if ((A->type == OBJ_POWERUP || B->type == OBJ_POWERUP) && (a_hittime_good == 0 || b_hittime_good == 0))
      ok_to_call_script = 0;
  }

  if (ok_to_call_script) {

    if (!(Game_mode & GM_MULTI)) {
      ASSERT(!(A->flags & OF_DEAD));
      ASSERT(!(B->flags & OF_DEAD));
    }
    tOSIRISEventInfo ei;
    ei.evt_collide.it_handle = B->handle;
    Osiris_CallEvent(A, EVT_COLLIDE, &ei);

    ei.evt_collide.it_handle = A->handle;
    Osiris_CallEvent(B, EVT_COLLIDE, &ei);
  }

  switch (collision_type) {
    DO_COLLISION(OBJ_PLAYER, OBJ_WEAPON, collide_player_and_weapon)
    DO_COLLISION(OBJ_PLAYER, OBJ_MARKER, collide_player_and_marker)

    DO_COLLISION(OBJ_ROBOT, OBJ_PLAYER, collide_generic_and_player)
    DO_COLLISION(OBJ_BUILDING, OBJ_PLAYER, collide_generic_and_player)
    DO_COLLISION(OBJ_DOOR, OBJ_PLAYER, collide_generic_and_player)
    DO_COLLISION(OBJ_ROOM, OBJ_VIEWER, collide_generic_and_player)
    DO_COLLISION(OBJ_ROOM, OBJ_PLAYER, collide_generic_and_player)
    DO_COLLISION(OBJ_CLUTTER, OBJ_PLAYER, collide_generic_and_player)

    DO_COLLISION(OBJ_ROBOT, OBJ_WEAPON, collide_generic_and_weapon)
    DO_COLLISION(OBJ_CLUTTER, OBJ_WEAPON, collide_generic_and_weapon)
    DO_COLLISION(OBJ_BUILDING, OBJ_WEAPON, collide_generic_and_weapon)
    DO_COLLISION(OBJ_ROOM, OBJ_WEAPON, collide_generic_and_weapon)
    DO_COLLISION(OBJ_DOOR, OBJ_WEAPON, collide_generic_and_weapon)

    DO_SAME_COLLISION(OBJ_PLAYER, OBJ_PLAYER, collide_player_and_player)

    // Handled by the script, so no code
    NO_COLLISION(OBJ_PLAYER, OBJ_POWERUP)
    NO_COLLISION(OBJ_POWERUP, OBJ_WEAPON)

  default:
    bump_two_objects(A, B, collision_point, collision_normal, 1);
  }

  if ((A->type == OBJ_PLAYER && B->type == OBJ_POWERUP && (B->flags & OF_DEAD)) ||
      (B->type == OBJ_PLAYER && A->type == OBJ_POWERUP && (A->flags & OF_DEAD))) {
    ain_hear hear;
    hear.f_directly_player = true;
    hear.hostile_level = 0.05f;
    hear.curiosity_level = 1.0f;

    hear.max_dist = Sounds[SOUND_POWERUP_PICKUP].max_distance;
    if (A->type == OBJ_PLAYER)
      AINotify(A, AIN_HEAR_NOISE, (void *)&hear);
    else
      AINotify(B, AIN_HEAR_NOISE, (void *)&hear);
  }
}

#define ENABLE_COLLISION_SPHERE_SPHERE(type1, type2)                                                                   \
  CollisionResult[type1][type2] = RESULT_CHECK_SPHERE_SPHERE;                                                          \
  CollisionResult[type2][type1] = RESULT_CHECK_SPHERE_SPHERE;

#define ENABLE_COLLISION_SPHERE_POLY(type1, type2)                                                                     \
  CollisionResult[type1][type2] = RESULT_CHECK_SPHERE_POLY;                                                            \
  CollisionResult[type2][type1] = RESULT_CHECK_POLY_SPHERE;

#define ENABLE_COLLISION_POLY_SPHERE(type1, type2)                                                                     \
  CollisionResult[type1][type2] = RESULT_CHECK_POLY_SPHERE;                                                            \
  CollisionResult[type2][type1] = RESULT_CHECK_SPHERE_POLY;

#define ENABLE_COLLISION_BBOX_POLY(type1, type2)                                                                       \
  CollisionResult[type1][type2] = RESULT_CHECK_BBOX_POLY;                                                              \
  CollisionResult[type2][type1] = RESULT_CHECK_POLY_BBOX;

#define ENABLE_COLLISION_POLY_BBOX(type1, type2)                                                                       \
  CollisionResult[type1][type2] = RESULT_CHECK_POLY_BBOX;                                                              \
  CollisionResult[type2][type1] = RESULT_CHECK_BBOX_POLY;

#define ENABLE_COLLISION_BBOX_BBOX(type1, type2)                                                                       \
  CollisionResult[type1][type2] = RESULT_CHECK_BBOX_BBOX;                                                              \
  CollisionResult[type2][type1] = RESULT_CHECK_BBOX_BBOX;

#define ENABLE_COLLISION_BBOX_SPHERE(type1, type2)                                                                     \
  CollisionResult[type1][type2] = RESULT_CHECK_BBOX_SPHERE;                                                            \
  CollisionResult[type2][type1] = RESULT_CHECK_SPHERE_BBOX;

#define ENABLE_COLLISION_SPHERE_BBOX(type1, type2)                                                                     \
  CollisionResult[type1][type2] = RESULT_CHECK_SPHERE_BBOX;                                                            \
  CollisionResult[type2][type1] = RESULT_CHECK_BBOX_SPHERE;

#define ENABLE_COLLISION_SPHERE_ROOM(type1, type2)                                                                     \
  CollisionResult[type1][type2] = RESULT_CHECK_SPHERE_ROOM;                                                            \
  CollisionResult[type2][type1] = RESULT_CHECK_SPHERE_ROOM;

#define ENABLE_COLLISION_BBOX_ROOM(type1, type2)                                                                       \
  CollisionResult[type1][type2] = RESULT_CHECK_BBOX_ROOM;                                                              \
  CollisionResult[type2][type1] = RESULT_CHECK_BBOX_ROOM;

#define DISABLE_COLLISION(type1, type2)                                                                                \
  CollisionResult[type1][type2] = RESULT_NOTHING;                                                                      \
  CollisionResult[type2][type1] = RESULT_NOTHING;

void CollideInit() {
  int i, j;

  for (i = 0; i < MAX_OBJECT_TYPES; i++)
    for (j = 0; j < MAX_OBJECT_TYPES; j++) {
      CollisionResult[i][j] = RESULT_NOTHING;
    }

  for (i = 0; i < MAX_OBJECT_TYPES; i++) {
    CollisionRayResult[i] = RESULT_NOTHING;
  }
  CollisionRayResult[OBJ_ROBOT] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_PLAYER] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_WEAPON] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_POWERUP] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_CLUTTER] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_BUILDING] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_DOOR] = RESULT_CHECK_SPHERE_POLY;
  CollisionRayResult[OBJ_ROOM] = RESULT_CHECK_SPHERE_POLY;

  for (i = 0; i < MAX_OBJECT_TYPES; i++) {
    ENABLE_COLLISION_SPHERE_ROOM(i, OBJ_ROOM)
  }

  ENABLE_COLLISION_POLY_SPHERE(OBJ_WALL, OBJ_ROBOT)
  ENABLE_COLLISION_POLY_SPHERE(OBJ_WALL, OBJ_WEAPON)
  ENABLE_COLLISION_POLY_SPHERE(OBJ_WALL, OBJ_PLAYER)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_ROBOT, OBJ_ROBOT)
  //	ENABLE_COLLISION_SPHERE_SPHERE( OBJ_BUILDING, OBJ_BUILDING )
  ENABLE_COLLISION_POLY_SPHERE(OBJ_PLAYER, OBJ_FIREBALL)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_PLAYER, OBJ_PLAYER)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_PLAYER, OBJ_MARKER)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_MARKER, OBJ_PLAYER)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_WEAPON, OBJ_WEAPON)
  ENABLE_COLLISION_POLY_SPHERE(OBJ_ROBOT, OBJ_PLAYER)
  //	ENABLE_COLLISION_SPHERE_SPHERE( OBJ_ROBOT, OBJ_PLAYER )
  ENABLE_COLLISION_POLY_SPHERE(OBJ_ROBOT, OBJ_WEAPON)

  ENABLE_COLLISION_POLY_SPHERE(OBJ_PLAYER, OBJ_WEAPON)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_PLAYER, OBJ_POWERUP)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_POWERUP, OBJ_WALL)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_WEAPON, OBJ_CLUTTER)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_PLAYER, OBJ_CLUTTER)
  ENABLE_COLLISION_SPHERE_SPHERE(OBJ_CLUTTER, OBJ_CLUTTER)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_ROBOT, OBJ_CLUTTER)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_PLAYER, OBJ_BUILDING)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_ROBOT, OBJ_BUILDING)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_WEAPON, OBJ_BUILDING)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_CLUTTER, OBJ_BUILDING)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_CLUTTER, OBJ_DOOR)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_BUILDING, OBJ_DOOR)

  ENABLE_COLLISION_SPHERE_ROOM(OBJ_PLAYER, OBJ_ROOM)
  ENABLE_COLLISION_SPHERE_ROOM(OBJ_ROBOT, OBJ_ROOM)
  ENABLE_COLLISION_SPHERE_ROOM(OBJ_WEAPON, OBJ_ROOM)
  ENABLE_COLLISION_SPHERE_ROOM(OBJ_VIEWER, OBJ_ROOM)

  ENABLE_COLLISION_SPHERE_POLY(OBJ_PLAYER, OBJ_DOOR)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_ROBOT, OBJ_DOOR)
  ENABLE_COLLISION_SPHERE_POLY(OBJ_WEAPON, OBJ_DOOR)
  DISABLE_COLLISION(OBJ_POWERUP, OBJ_POWERUP)
}

// Process a collision between an object and a wall
// Returns true if the object hits the wall, and false if should keep going though the wall (for breakable glass)
bool collide_object_with_wall(object *A, float hitspeed, int hitseg, int hitwall, vector *hitpt, vector *wall_normal,
                              float hit_dot) {
  uint8_t do_event = 0;
  bool ret = true;

  switch (A->type) {
  case OBJ_NONE:
    Error("A object of type NONE hit a wall!\n");
    break;
  case OBJ_PLAYER:
    collide_player_and_wall(A, hitspeed, hitseg, hitwall, hitpt, wall_normal, hit_dot);
    do_event = 1;
    break;
  case OBJ_WEAPON:
    ret = collide_weapon_and_wall(A, hitspeed, hitseg, hitwall, hitpt, wall_normal, hit_dot);
    do_event = 1;
    break;
  case OBJ_DEBRIS:
    break; // chrishack -- collide_debris_and_wall(A,hitspeed,hitseg,hitwall,hitpt); break;
  case OBJ_FIREBALL:
    break; // collide_fireball_and_wall(A,hitspeed,hitseg,hitwall,hitpt);
  case OBJ_CLUTTER:
  case OBJ_BUILDING:
  case OBJ_ROBOT:
    collide_generic_and_wall(A, hitspeed, hitseg, hitwall, hitpt, wall_normal, hit_dot);
    do_event = 1;
    break;
  case OBJ_VIEWER:
    break; // collide_camera_and_wall(A,hitspeed,hitseg,hitwall,hitpt);
  case OBJ_POWERUP:
    break; // collide_powerup_and_wall(A,hitspeed,hitseg,hitwall,hitpt);
  case OBJ_GHOST:
    break; // do nothing
  case OBJ_OBSERVER:
    break; // do nothing
  case OBJ_SPLINTER:
    break;
  case OBJ_MARKER:
    break;
  case OBJ_SHARD:
    if (sound_override_glass_breaking == -1)
      Sound_system.Play3dSound(SOUND_BREAKING_GLASS, SND_PRIORITY_NORMAL, A, MAX_GAME_VOLUME / 10);
    else
      Sound_system.Play3dSound(sound_override_glass_breaking, SND_PRIORITY_NORMAL, A, MAX_GAME_VOLUME / 10);
    break;

  default:
    mprintf(0, "Unhandled collision of object type %d and wall\n", A->type);
    //		Error( "Unhandled object type hit wall in collide.c\n" );
  }

  if (do_event && (Game_mode & GM_MULTI)) {
    // call multiplayer event
    DLLInfo.me_handle = A->handle;
    DLLInfo.it_handle = OBJECT_HANDLE_NONE;
    DLLInfo.collide_info.point.x = hitpt->x;
    DLLInfo.collide_info.point.y = hitpt->y;
    DLLInfo.collide_info.point.z = hitpt->z;
    DLLInfo.collide_info.normal.x = wall_normal->x;
    DLLInfo.collide_info.normal.y = wall_normal->y;
    DLLInfo.collide_info.normal.z = wall_normal->z;
    DLLInfo.collide_info.hitspeed = hitspeed;
    DLLInfo.collide_info.hit_dot = hit_dot;
    DLLInfo.collide_info.hitseg = hitseg;
    DLLInfo.collide_info.hitwall = hitwall;
    CallGameDLL(EVT_GAMEWALLCOLLIDE, &DLLInfo);
  }

  return ret;
}
