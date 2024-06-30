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

 * $Logfile: /DescentIII/main/fireball.cpp $
 * $Revision: 241 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * Fireball code
 *
 * $Log: /DescentIII/main/fireball.cpp $
 *
 * 241   4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 240   3/22/00 12:13p Matt
 * Added some if statements to not damage & kill objects when playing back
 * a demo.
 *
 * 239   3/20/00 12:07p Matt
 * Merge of Duane's post-1.3 changes.
 * Check for no available vis effects.
 *
 * 238   10/24/99 1:30a 3dsmax
 * if submodel face has 0 vertices, bail out nicely when creating visfx
 * electric bolts.
 *
 * 237   10/12/99 11:01a Jeff
 * added grey lightning
 *
 * 236   9/21/99 2:54p Jeff
 * added grey spark fireball (for multicolored sparks)
 *
 * 235   7/28/99 4:15p Kevin
 * Macintosh
 *
 * 234   5/22/99 10:27p Jason
 * changes for multiplayer and buildings, ai
 *
 * 233   5/22/99 12:40a Matt
 * Don't create spliters for non-renderable submodels.  (This fixed the
 * error texture that was sometimes visible when a blastable grate door
 * blew up.)
 *
 * 232   5/21/99 7:53p Jason
 * fixed bug where powerups in multiplayer would get out of sync due to
 * blackshark
 *
 * 231   5/10/99 10:22p Ardussi
 * changes to compile on Mac
 *
 * 230   5/10/99 8:28p Jason
 * made blackshark more interesting indoors
 *
 * 229   5/10/99 1:53a Jason
 * add blackshark explosion
 *
 * 228   5/07/99 7:30p Chris
 * Check for backfaces with concussive forces
 *
 * 227   5/06/99 7:18p Matt
 * Fixed turret object names.
 *
 * 226   5/06/99 5:44p Matt
 * Added three more dead turrets
 *
 * 225   5/06/99 3:16a Matt
 * Added semi-hacked dead model for the Swatter turret.
 *
 * 224   5/05/99 2:33p Jason
 * fixed some multiplayer issues with client objects
 *
 * 223   5/02/99 7:42p Jason
 * added fireball error checking
 *
 * 222   5/01/99 4:59p Jason
 * change blue blast ring
 *
 * 221   4/30/99 5:42p Jason
 * changes for blast rings
 *
 * 220   4/29/99 2:16a Samir
 * adjusted some sound priority stuff
 *
 * 219   4/23/99 12:32a Matt
 * Deleted cut-and-paste-error comments.
 *
 * 218   4/23/99 12:27a Matt
 * Moved the code that plays an object's explosion sound into a function.
 *
 * 217   4/22/99 8:29p Kevin
 * made psrand.h come after stdlib.h
 *
 * 216   4/21/99 5:31p Jason
 * changed smoke chances
 *
 * 215   4/21/99 3:01p Matt
 * Added a new type for dying objects that have AI, instead of keeping a
 * flag in the dying info.
 *
 * 214   4/21/99 12:41p Jason
 * make explosion system framerate independant
 *
 * 213   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 212   4/19/99 3:45a Jeff
 * fixed min/max problem
 *
 * 211   4/18/99 10:55p Chris
 * Added ignore own concussive blasts
 *
 * 210   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 209   4/10/99 5:09p Samir
 * prioritize sounds, pass 1
 *
 * 208   4/06/99 6:53p Jason
 * fixed source safe bug
 *
 * 207   4/06/99 6:02p Matt
 * Added score system
 *
 * 205   4/05/99 4:39p Jason
 * added groovy new smoke trails
 *
 * 204   4/02/99 3:57p Jason
 * sped up vis effect stuff
 *
 * 203   4/01/99 10:10p Matt
 * Re-added my death system changes from version 197 that Jason so kindly
 * blew away with version 198.
 *
 * 202   4/01/99 5:39p Matt
 * Fixed (hopefully) bug introduced in last version.
 *
 * 201   4/01/99 4:28p Matt
 * Cleaned up handling of dying flag to prevent infinite recursion.  Jeff
 * will test.
 *
 * 200   4/01/99 1:10p Jason
 * made vis effects better for the lighting system
 *
 * 199   3/31/99 11:40a Jason
 * added support for attached thick lightning
 *
 * 198   3/29/99 7:30p Jason
 * added cool new energy effect
 *
 * 196   3/27/99 2:15p Jason
 * added better thick lightining
 *
 * 195   3/25/99 3:29p Jason
 * added option to randomize powerup respawn points
 *
 * 194   3/24/99 5:54p Jason
 * fixed size for thick lightning
 *
 * 193   3/24/99 12:34p Jason
 * fixed concussive damage bailing out too early
 *
 * 192   3/09/99 1:35p Jason
 * made blackshark not suck in energy weapons
 *
 * 191   3/05/99 6:42p Matt
 * On death, only do shockwave and shake if an object breaks apart or has
 * fireballs.  Also, check for no sound before calling play sound.
 *
 * 190   3/05/99 3:32p Matt
 * Made 'remains' work for object deaths.
 *
 * 189   3/02/99 4:18p Jason
 * fixed black smoke bug
 *
 * 188   3/01/99 11:28a Matt
 * Made debris radius half the size of the polymodel, so it sits closer to
 * the floor when it stops bouncing.
 *
 * 187   2/28/99 5:31p Matt
 * Removed mprintf()
 *
 * 186   2/26/99 3:52p Jason
 * fixed mprintf
 *
 * 185   2/26/99 2:03p Matt
 * Got blastable doors working, and cleaned up concussive force code.
 *
 * 184   2/25/99 10:58a Matt
 * Added new explosion system.
 *
 * 183   2/23/99 10:50a Matt
 * Check for spew type of -1 is DoDeathSpew()
 *
 * 182   2/22/99 2:03p Jason
 * added different damages for players and generics
 *
 * 181   2/13/99 12:30a Jeff
 * an OBJ_DUMMY shouldn't be blown up...Int3 put in to catch this
 *
 * 180   2/10/99 3:38p Jason
 * table file filter fixups
 *
 * 179   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 178   2/09/99 2:38p Jason
 * added destroyable faces
 *
 * 177   2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 176   2/06/99 10:30p Jason
 * fixed some blackshark stuff
 *
 * 175   2/05/99 1:38p Jason
 * dropped splinter count
 *
 * 174   2/02/99 8:43a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 173   2/01/99 10:16a Chris
 * Fixed mass prop. bug and accounted for the fact that we hack in a new
 * mass for debris
 *
 * 172   1/29/99 5:09p Chris
 * Made changes for ROCKS
 *
 * 171   1/26/99 6:39p Jason
 * added wall effects code
 *
 * 170   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 169   1/20/99 2:13a Chris
 * It is now possible for robots to have special immunities, resistances,
 * and vunerabilities
 *
 * 168   1/18/99 2:46p Matt
 * Combined flags & flags2 fields in object struct
 *
 * 167   12/13/98 9:18p Chris
 * Improved influence values for in-code goals (10000 to 1.0).  Added
 * GF_ORIENT stuff.  :)
 *
 * 166   12/13/98 7:17p Chris
 * Improved walker death code
 *
 * 165   12/11/98 5:08p Jason
 * changed mass driver effect
 *
 * 164   11/30/98 6:02p Jay
 * Fixed a bug with concussive forces being applied to room objects
 *
 * 163   11/19/98 6:37p Jason
 * made a better black shark effect
 *
 * 162   11/19/98 4:35p Chris
 * tweaked it
 *
 * 161   11/19/98 4:21p Chris
 * Got rid of some wierd rotation cases with slow deaths from being killed
 * with the mass driver
 *
 * 160   11/19/98 12:22p Jason
 * optimizations
 *
 * 159   11/18/98 2:53p Jason
 * added snow effect
 *
 * 158   11/16/98 6:03p Jason
 * took out some comments
 *
 * 157   11/11/98 2:46p Kevin
 * Demo recording system work
 *
 * 156   10/29/98 6:01p Jason
 * added multiple coronas
 *
 * 155   10/28/98 11:51a Jason
 * fixed some multiplayer problems, plus redid coop a bit to make it
 * cleaner
 *
 * 154   10/22/98 5:40p Matt
 * If no viewer object, bail from several fireball funtions that use that
 * variable.
 *
 * 153   10/19/98 7:18p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 152   10/17/98 3:14p Jason
 * made electrical death less deforming
 *
 * 150   10/16/98 1:41p Jason
 * changes for the demo
 *
 * 149   10/15/98 11:09a Chris
 * Added visibility checks for concussive blasts
 *
 * 148   10/12/98 9:28a Jason
 * fixed some rendering bugs
 *
 * 147   10/07/98 6:55p Jason
 * added better lightning death
 *
 * 146   10/07/98 5:17p Jason
 * added new invul hit effect
 *
 * 145   10/06/98 11:41a Jason
 * tweaked electrical death
 *
 * 144   10/06/98 11:27a Jason
 * added new death type for robots
 *
 * 143   9/29/98 7:15p Jason
 * added axis billboards
 *
 * 142   9/29/98 12:49p Jason
 * worked on matcen effects and lightning
 *
 * 141   9/18/98 8:23p Jason
 * fixed insidious vis effect errors
 *
 * 140   9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 139   9/11/98 6:40p Jason
 * added smoke puffs
 *
 * 138   9/09/98 4:49p Jason
 * tweaked black shark lightning effect
 *
 * 137   9/09/98 4:28p Jason
 * added better weapon effects
 *
 * 136   8/31/98 5:29p Jason
 * made explosions better with addition of sound effects
 *
 * 135   8/21/98 12:29p Jason
 * made smoke puffs draw more inside the mine
 *
 * 134   8/20/98 4:59p Nate
 * Limitted the velocity of created debris to +-100000.0f
 *
 * 133   8/19/98 2:49p Jason
 * Fixed black smoked to be more noticable
 *
 * 132   8/17/98 10:48a Jason
 * added more lightning code
 *
 * 131   8/17/98 1:32a Chris
 * Fixed a type cast bug the resulted in rand_vec.y  always equaling .4
 * and then zero after normalization (as the others ranged from D3_RAND_MAX/2
 * to -D3_RAND_MAX/2)
 *
 * 130   8/17/98 1:15a Chris
 * By default, obj_debris don't make a sound when they die
 *
 * 129   8/16/98 6:17p Chris
 * Added generic object spewing code
 *
 * 128   8/10/98 5:24p Jason
 * don't do blast flash if you can't see the blast
 *
 * 127   8/03/98 11:12a Jason
 * fixed some zero foward vector errors
 *
 * 126   7/24/98 6:08p Jason
 * added some more procedurals
 *
 * 125   7/24/98 4:45p Jason
 * added DrawSphere
 *
 * 124   6/29/98 5:06p Jason
 * made a somewhat better gravity explosion
 *
 *
 * 123   6/25/98 5:17p Jason
 * checked in for mark to check out warp effect
 *
 * 122   6/25/98 12:19p Jason
 * made gravity effect do different damage in single vs multiplayer
 *
 * 121   6/23/98 3:34p Jason
 * added cool lighting effect to gravity field
 *
 * 120   6/22/98 6:52p Jason
 * changed gravity field effect somewhat
 *
 * 119   6/22/98 6:26p Jason
 * added gravity field effect for weapons
 *
 * 118   6/15/98 7:45a Chris
 * FIxed a bug with making shockwaves
 *
 * 117   5/27/98 5:53p Chris
 * No more flying turrets
 *
 * 116   5/26/98 6:54p Jason
 * viseffect optimizations
 *
 * 115   5/26/98 3:36p Chris
 * Tweaked explosions
 *
 * 114   5/26/98 3:24p Chris
 * Oops.  I was corrupting the orientation
 *
 * 113   5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 112   5/15/98 4:21p Chris
 * Oops
 *
 * 111   5/15/98 3:53p Keneta
 * Make objects on ceiling not fly upward
 *
 * 110   5/14/98 7:40p Samir
 * shaking cockpit.
 *
 * 109   5/14/98 2:17p Jason
 * more changes to be memory friendly
 *
 * 108   5/11/98 4:40p Chris
 * AI info is now a malloc'ed pointer
 *
 * 107   5/01/98 6:23p Jason
 * made better puddle rain
 *
 * 106   5/01/98 3:41p Chris
 *
 * 105   5/31/98 3:12p Chris
 * Made objects die with death anims.
 *
 * 104   5/31/98 11:01a Chris
 * Made debris less heavy
 *
 * 103   4/30/98 6:45p Jason
 * more changes for weather
 *
 * 102   4/30/98 3:39p Jason
 * don't make non-billowingfireballs rotate
 *
 * 101   4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 100   4/29/98 11:38a Jason
 * added some weather effects (first pass)
 *
 * 99    4/22/98 3:24p Jason
 * fixed colored disk problem
 *
 * 98    4/17/98 12:45p Jason
 * various changes for multiplayer
 *
 * 97    4/15/98 3:28p Jason
 * changed glow stuff to work with new system
 *
 * 96    4/15/98 2:33p Jason
 * changed some smoke trail stuff
 *
 * 95    4/13/98 4:19p Chris
 * Added PF_IGNORE_CONCUSSIVE_FORCES
 *
 * 94    4/10/98 2:17p Jason
 * added afterburner fireball
 *
 * 93    4/09/98 5:17p Jason
 * got guided working in multiplayer
 *
 * 92    4/07/98 3:31p Jason
 * got particle effects working with weapons
 *
 * 91    4/06/98 1:35p Chris
 * Fixed a multiplayer bug
 *
 * 90    4/02/98 6:42p Jason
 * added blue blast ring effect
 *
 * 89    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 88    3/31/98 12:16p Jason
 * some small changes for explosions
 *
 * 87    3/27/98 4:46p Jason
 * changes for voodoo2
 *
 * 86    3/23/98 4:54p Chris
 * Fixed problem with powerups getting concussive force
 *
 * 85    3/20/98 9:35p Jason
 * fixed stupid error with last rev
 *
 * 83    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 82    3/19/98 3:44p Chris
 *
 * 81    3/19/98 3:44p Chris
 * Multiplayer enchancement for collisions
 *
 * 80    3/19/98 1:25p Chris
 * Improved size stuff used for concussive effects
 *
 * 79    3/19/98 1:17p Chris
 * Concussive blasts effect weapons and not powerups
 *
 * 78    3/13/98 4:17p Jason
 * took out mprintf
 *
 * 77    3/12/98 7:30p Chris
 * Added ObjSetOrient
 *
 * 76    3/12/98 7:14p Jason
 * fixed FOV bug
 *
 * 75    3/09/98 5:58p Jason
 * draw powerups with saturated alpha rings
 *
 * 74    3/06/98 4:09p Jason
 * don't do glows if not in hardware
 *
 * 73    2/27/98 11:56a Chris
 * Improved the distance formula for concussive blasts
 *
 * 72    2/25/98 4:59p Jason
 * got dynamic explosion lighting working with vis-effects
 *
 * 71    2/25/98 4:31p Jason
 * changes for explosions
 *
 * 70    2/19/98 6:20p Chris
 * FindPointRoom() call is not for in-game.
 *
 * 69    2/19/98 1:10p Jason
 * toned down building explosions a bit
 *
 * 68    2/16/98 2:24p Jason
 * fixed bad indexing into subobjects problem
 *
 * 67    2/10/98 6:03p Jason
 * took out ugly blast sphere graphic
 *
 * 66    2/05/98 2:54p Jason
 * changes for explosions
 *
 * 65    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 64    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 */
#include <memory.h>
#include "pstypes.h"
#include "pserror.h"
#include "fireball.h"
#include "vclip.h"
#include "object.h"
#include "cockpit.h"
#include "game.h"
#include "3d.h"
#include "mono.h"
#include "room.h"
#include "polymodel.h"
#include "objinfo.h"
#include "gametexture.h"
#include "splinter.h"
#include "PHYSICS.H"
#include "damage.h"
#include "gameevent.h"
#include "weapon.h"
#include "viseffect.h"
#include "spew.h"
#include "hlsoundlib.h"
#include "sounds.h"
#include "gameloop.h"
#include "multi.h"
#include "AIGoal.h"
#include "AIMain.h"
#include "ship.h"
#include "BOA.h"
#include "demofile.h"
#include "ObjScript.h"
#include <stdlib.h>
#include <string.h>
#include "psrand.h"

#include <algorithm>

static object *CreateSubobjectDebris(object *parent, int subobj_num, float explosion_mag, int death_flags);
static void DrawSmolderingObject(object *obj);
static int GetRandomExplosion(float size);
static void CreateBlueBlastRing(vector *pos, int index, float lifetime, float max_size, int roomnum, int objnum,
                                int force_up);

// If an objects size is bigger than this, we create size/threshold extra explosions
#define EXTRA_EXPLOSION_THRESHOLD 15
std::array<fireball, NUM_FIREBALLS> Fireballs = {
    fireball
    {"ExplosionAA.oaf", FT_EXPLOSION, SMALL_TEXTURE, .9f, 3.0},        //	MED_EXPLOSION2
    {"ExplosionBB.oaf", FT_EXPLOSION, SMALL_TEXTURE, .9f, 2.0},        //	SMALL_EXPLOSION2
    {"explosionCC.oaf", FT_EXPLOSION, SMALL_TEXTURE, .9f, 3.0f},       // MED_EXPLOSION
    {"explosionDD.oaf", FT_EXPLOSION, SMALL_TEXTURE, .9f, 3.0f},       // MED_EXPLOSION3
    {"ExplosionE.oaf", FT_EXPLOSION, SMALL_TEXTURE, .9f, 3.0},         // BIG_EXPLOSION
    {"ExplosionFF.oaf", FT_EXPLOSION, SMALL_TEXTURE, 1.0f, 1.0f},      // BILLOWING
    {"explosionG.oaf", FT_EXPLOSION, SMALL_TEXTURE, 1.0f, 2.0f},       // SMALL_EXPLOSION_INDEX
    {"smokepuff.oaf", FT_SMOKE, SMALL_TEXTURE, .7f, .7f},              // MED_SMOKE_INDEX
    {"black_smoke.oaf", FT_SMOKE, SMALL_TEXTURE, .7f, 1.0f},           // BLACK_SMOKE
    {"BlastRingOrange.ogf", FT_EFFECT, SMALL_TEXTURE, 1.0, 1.0},       // RED_BLAST_RING
    {"smokepuff.oaf", FT_SMOKE, SMALL_TEXTURE, .4f, .7f},              // SMOKE_TRAIL
    {"smokepuff.oaf", FT_EXPLOSION, SMALL_TEXTURE, .7f, 3.0},          // CUSTOM_EXPLOSION
    {"explosionblast2.ogf", FT_EXPLOSION, NORMAL_TEXTURE, .7f, .7f},   // SHRINKING_BLAST
    {"black_smoke.oaf", FT_SMOKE, SMALL_TEXTURE, .7f, 1.0f},           // SMOLDERING
    {"warp.oaf", FT_EFFECT, NORMAL_TEXTURE, 1.0, 1.0},                 // SHRINKING_BLAST2
    {"Hotspark.ogf", FT_SPARK, SMALL_TEXTURE, 1.0, 1.0},               // HOT_SPARK
    {"Coolspark.ogf", FT_SPARK, SMALL_TEXTURE, 1.0, 1.0},              // COOL_SPARK
    {"thrustball.ogf", FT_EFFECT, SMALL_TEXTURE, 1.0, 1.0},            // GRADIENT_BALL
    {"NOIMAGE", FT_EFFECT, SMALL_TEXTURE, .7f, 3.0},                   // SPRAY
    {"NOIMAGE", FT_EFFECT, SMALL_TEXTURE, .7f, 3.0},                   // FADING_LINE
    {"muzzleflash.ogf", FT_EFFECT, SMALL_TEXTURE, .7f, 3.0},           // MUZZLE_FLASH
    {"shiphit.ogf", FT_EFFECT, NORMAL_TEXTURE, .7f, 3.0},              // SHIP HIT EFFECT
    {"BlastRingBlue.ogf", FT_EFFECT, SMALL_TEXTURE, .7f, 3.0},         // BLUE SHIELD RING
    {"NOIMAGE", FT_EFFECT, SMALL_TEXTURE, .7f, 3.0},                   // PARTICLE
    {"explosion.oaf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},            // AFTERBURNER
    {"NOIMAGE", FT_EXPLOSION, SMALL_TEXTURE, 1.0f, 2.0f},              // NAPALM BALL
    {"LightningOriginA.ogf", FT_EXPLOSION, SMALL_TEXTURE, 1.0f, 2.0f}, // LIGHTNING ORIGINA
    {"LightningOriginB.ogf", FT_EXPLOSION, SMALL_TEXTURE, 1.0f, 2.0f}, // LIGHTNING ORIGINB
    {"Raindrop.ogf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},             // Windshield drop
    {"Puddle.ogf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},               //	Puddle drop
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // Gravity effect
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // LIGHTNING_BOLT_INDEX
    {"InvulnerabilityHit.ogf", FT_EFFECT, NORMAL_TEXTURE, 1.0f, 2.0f}, // Invul shield hit effect
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // SINE_WAVE_INDEX
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // AXIS_BILLBOARD_INDEX
    {"StarFlare6.ogf", FT_EFFECT, NORMAL_TEXTURE, 1.0f, 2.0f},         // DEFAULT_CORONA
    {"HeadlightFlare.ogf", FT_EFFECT, NORMAL_TEXTURE, 1.0f, 2.0f},     // HEADLIGHT_CORONA
    {"StarFlare.ogf", FT_EFFECT, NORMAL_TEXTURE, 1.0f, 2.0f},          // STAR_CORONA
    {"SunFlare.ogf", FT_EFFECT, NORMAL_TEXTURE, 1.0f, 2.0f},           // SUN_CORONA
    {"Whiteball.ogf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},            // SNOWFLAKE_INDEX
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // THICK_LIGHTNING_INDEX
    {"NapalmFire.oaf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},           // BLUE_FIRE_INDEX
    {"Rocklette1.ogf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},           // RUBBLE1_INDEX
    {"Rocklette2.ogf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},           // RUBBLE2_INDEX
    {"Whiteball.ogf", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},            // WATER_SPLASH_INDEX
    {"lg.oaf", FT_EFFECT, SMALL_TEXTURE, 1.0f, 2.0f},                  // SHATTER_INDEX
    {"lg.oaf", FT_EFFECT, SMALL_TEXTURE, 1.0f, 2.0f},                  // SHATTER_INDEX2
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // BILLBOARD_SMOKETRAIL_INDEX
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f},                  // MASSDRIVER_EFFECT_INDEX
    {"ExplosionBlkShrk.oaf", FT_EXPLOSION, SMALL_TEXTURE, .9f, 3.0},   // BLUE_EXPLOSION_INDEX
    {"Coolspark.ogf", FT_SPARK, SMALL_TEXTURE, 1.0, 1.0},              // GRAY_SPARK_INDEX
    {"NOIMAGE", FT_EFFECT, TINY_TEXTURE, 1.0f, 2.0f}};                 // GRAY_LIGHTNING_BOLT_INDEX

// Initializes the explosion system, loading needed bitmaps, etc
void InitFireballs() {
  int i, num_fireballs = NUM_FIREBALLS;
  for (i = 0; i < num_fireballs; i++) {
    if (!(stricmp(Fireballs[i].name, "NOIMAGE")))
      continue;
    int bm_handle = LoadTextureImage(IGNORE_TABLE(Fireballs[i].name), NULL, Fireballs[i].tex_size, 0);
    if (bm_handle < 0) {
      Error("Couldn't load fireball %s in InitFireballs.", Fireballs[i].name);
      return;
    }
    ASSERT(bm_handle >= 0);
    Fireballs[i].bm_handle = bm_handle;
  }

  // convert the grey spark into grayscale
  uint16_t *data;
  int size;
  float recip32 = 1.0f / 32.0f;
  data = bm_data(Fireballs[GRAY_SPARK_INDEX].bm_handle, 0);
  size = bm_w(Fireballs[GRAY_SPARK_INDEX].bm_handle, 0) * bm_h(Fireballs[GRAY_SPARK_INDEX].bm_handle, 0);
  for (i = 0; i < size; i++) {
    uint16_t col565 = data[i];
    if (col565 == 0x07e0) {
      data[i] = NEW_TRANSPARENT_COLOR;
    } else {
      uint8_t r = (uint8_t)((col565 & 0xf800) >> 11);
      uint8_t g = (uint8_t)((col565 & 0x07c0) >> 6);
      uint8_t b = (uint8_t)(col565 & 0x001f);
      float brightness = ((r * 0.30f) + (g * 0.59f) + (b * 0.11f)) * recip32;
      uint8_t elem = (uint8_t)(255.0f * brightness);
      if (brightness > 1.0f)
        elem = 255;
      data[i] = GR_RGB16(elem, elem, elem) | OPAQUE_FLAG;
    }
  }
  GameBitmaps[Fireballs[GRAY_SPARK_INDEX].bm_handle].flags |= BF_CHANGED;
}

// Given an object, renders the representation of this fireball
void DrawFireballObject(object *obj) {
  ASSERT(obj->type == OBJ_FIREBALL);

  // First check to see if these are special types
  if (obj->id == BLAST_RING_INDEX) {
    DrawBlastRingObject(obj);
    return;
  }
  if (obj->id == GRAVITY_FIELD_INDEX) {
    // Draw two blast rings
    matrix tempm;
    vm_MakeIdentity(&tempm);
    ObjSetOrient(obj, &tempm);
    DrawBlastRingObject(obj);
    return;
  }
  if (obj->id == SMOLDERING_INDEX) {
    DrawSmolderingObject(obj);
    return;
  }
  float norm_time;
  float time_live = Gametime - obj->creation_time;
  float size = obj->size;

  int objnum = OBJNUM(obj);
  int rot_angle;
  int bm_handle;
  if (Fireballs[obj->id].type == FT_BILLOW)
    rot_angle = ((objnum * 5000) + (FrameCount * 160)) % 65536;
  else
    rot_angle = ((objnum * 5000) + (FrameCount * 30)) % 65536;

  norm_time = time_live / obj->lifetime;
  if (norm_time >= 1)
    norm_time = .99999f;            // don't go over!
  if (obj->id == SMOKE_TRAIL_INDEX) // If its a smoke trail, get image from texture
  {
    int texnum = obj->ctype.blast_info.bm_handle;
    if (GameTextures[texnum].flags & TF_ANIMATED) {
      PageInVClip(GameTextures[texnum].bm_handle);
      vclip *vc = &GameVClips[GameTextures[texnum].bm_handle];
      int int_frame = vc->num_frames * norm_time;
      bm_handle = vc->frames[int_frame];
    } else
      bm_handle = GameTextures[texnum].bm_handle;
  } else if (obj->id == CUSTOM_EXPLOSION_INDEX) // Do custom
  {
    bm_handle = GetTextureBitmap(obj->ctype.blast_info.bm_handle, 0);
    if (!(GameTextures[obj->ctype.blast_info.bm_handle].flags & TF_ANIMATED)) {
      // If this is just a single bitmap, scale it based on time
      if (norm_time < .5) // Ramp up quickly
      {
        float temp_norm = norm_time / .2;
        temp_norm = std::min(1.0f, temp_norm);
        size *= temp_norm;
      } else // ramp down slowly
      {
        float temp_norm = ((norm_time - .5) / .5);
        size *= (1.0 - temp_norm);
      }
    }
  } else if (Fireballs[obj->id].type == FT_SPARK) // Do spark
  {
    bm_handle = Fireballs[obj->id].bm_handle;
    size *= (1.0 - norm_time);

  } else {
    vclip *vc = &GameVClips[Fireballs[obj->id].bm_handle];
    int int_frame = vc->num_frames * norm_time;
    bm_handle = vc->frames[int_frame];
  }
  if (Fireballs[obj->id].type == FT_SMOKE) {
    if (norm_time > .3) {
      float temp_time = (norm_time - .3);
      temp_time /= .7f;
      size *= (1 + (temp_time * 2.3));
    }
  }
  // Set some alpha
  if (Fireballs[obj->id].type == FT_SMOKE || obj->id == CUSTOM_EXPLOSION_INDEX)
    rend_SetAlphaType(AT_CONSTANT + AT_TEXTURE);
  else
    rend_SetAlphaType(AT_SATURATE_TEXTURE);
  float val;
  if (norm_time > .5)
    val = 1.0 - ((norm_time - .5) / .5);
  else
    val = 1.0;
  if (Fireballs[obj->id].type == FT_SMOKE)
    rend_SetAlphaValue(val * SMOKE_ALPHA * 255);
  else
    rend_SetAlphaValue(val * FIREBALL_ALPHA * 255);
  rend_SetOverlayType(OT_NONE);

  rend_SetZBias(-2.0f);
  rend_SetZBufferWriteMask(0);
  rend_SetWrapType(WT_CLAMP);
  rend_SetLighting(LS_NONE);
  // Cap size
  if (size > MAX_FIREBALL_SIZE)
    size = MAX_FIREBALL_SIZE;

  // Draw!!
  g3_DrawRotatedBitmap(&obj->pos, rot_angle, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
  rend_SetZBias(0);
  rend_SetZBufferWriteMask(1);
}
// Creates a gravity field that sucks objects into it
int CreateGravityField(vector *pos, int roomnum, float size, float time, int parent_handle) {
  int index = CreateFireball(pos, GRAVITY_FIELD_INDEX, roomnum, REAL_FIREBALL);
  if (index < 0)
    return -1;
  object *obj = &Objects[index];

  obj->lifetime = time;
  obj->lifeleft = time;
  obj->size = 1;
  obj->ctype.blast_info.max_size = size;
  obj->ctype.blast_info.bm_handle = Fireballs[BLUE_BLAST_RING_INDEX].bm_handle;
  obj->parent_handle = parent_handle;
  return index;
}
// Creates a fireball and then sets its size
int CreateFireball(vector *pos, int fireball_num, int roomnum, int realtype) {
  int objnum;

  ASSERT(roomnum != -1);
  if (realtype == VISUAL_FIREBALL) // If this is a visual effect then create it instead!
    return (VisEffectCreate(VIS_FIREBALL, fireball_num, roomnum, pos));
  else {
    objnum = ObjCreate(OBJ_FIREBALL, fireball_num, roomnum, pos, NULL);
    if (objnum < 0) {
      mprintf(0, "Couldn't create fireball object!\n");
      return -1;
    }
    Objects[objnum].size = Fireballs[fireball_num].size;
    Objects[objnum].flags |= OF_USES_LIFELEFT;

    Objects[objnum].lifeleft = Fireballs[fireball_num].total_life;
    Objects[objnum].lifetime = Objects[objnum].lifeleft;
  }

  return objnum;
}
// TODO: MTS: used only in this file.
// Creates a fireball object with a custom texture/vclip
int CreateCustomFireballObject(vector *pos, int fireball_num, int tex_handle, int roomnum) {
  int objnum;
  ASSERT(GameTextures[tex_handle].used >= 1);

  if (roomnum == -1)
    return -1;
  objnum = ObjCreate(OBJ_FIREBALL, fireball_num, roomnum, pos, NULL);
  if (objnum < 0) {
    mprintf(0, "Couldn't create fireball object!\n");
    return -1;
  }
  Objects[objnum].size = Fireballs[fireball_num].size;
  Objects[objnum].flags |= OF_USES_LIFELEFT;
  float lifetime;
  // If this is an animated texture then use the life of the vclip
  if (GameTextures[tex_handle].flags & TF_ANIMATED) {
    PageInVClip(GameTextures[tex_handle].bm_handle);
    vclip *vc = &GameVClips[GameTextures[tex_handle].bm_handle];
    lifetime = vc->frame_time * vc->num_frames;
  } else // Just set it to half a second
    lifetime = .5;
  Objects[objnum].lifeleft = lifetime;
  Objects[objnum].lifetime = lifetime;
  Objects[objnum].ctype.blast_info.bm_handle = tex_handle;

  return objnum;
}
//----------------------------------
// Putting in some explosion stuff
//----------------------------------
// Creates a debris piece that goes off in a given direction, with a given magnitude
object *CreateSubobjectDebrisDirected(object *parent, int subobj_num, vector *dir, float explosion_mag,
                                      int death_flags) {
  int objnum;
  object *obj;
  ASSERT(parent->flags & OF_POLYGON_OBJECT);
  objnum = ObjCreate(OBJ_DEBRIS, 0, parent->roomnum, &parent->pos, &parent->orient);

  if (objnum < 0 || objnum > Highest_object_index) {
    mprintf(0, "WARNING: Debris not created!\n");
    return NULL;
  }
  obj = &Objects[objnum];

  ASSERT(subobj_num < MAX_SUBOBJECTS);
  int model_num = parent->rtype.pobj_info.model_num;

  // Set polygon-object-specific data
  obj->rtype.pobj_info.model_num = model_num;
  obj->rtype.pobj_info.subobj_flags = 0x00000001 << subobj_num;
  obj->rtype.pobj_info.tmap_override = parent->rtype.pobj_info.tmap_override;
  // Set physics data for this object
  ASSERT(obj->movement_type == MT_PHYSICS);
  obj->mtype.phys_info.velocity = *dir;
  obj->mtype.phys_info.velocity *= explosion_mag;
  // obj->mtype.phys_info.velocity += parent->mtype.phys_info.velocity;
  if (obj->mtype.phys_info.velocity.x > 100000.0f)
    obj->mtype.phys_info.velocity.x = 100000.0f;
  if (obj->mtype.phys_info.velocity.y > 100000.0f)
    obj->mtype.phys_info.velocity.y = 100000.0f;
  if (obj->mtype.phys_info.velocity.z > 100000.0f)
    obj->mtype.phys_info.velocity.z = 100000.0f;
  if (obj->mtype.phys_info.velocity.x < -100000.0f)
    obj->mtype.phys_info.velocity.x = -100000.0f;
  if (obj->mtype.phys_info.velocity.y < -100000.0f)
    obj->mtype.phys_info.velocity.y = -100000.0f;
  if (obj->mtype.phys_info.velocity.z < -100000.0f)
    obj->mtype.phys_info.velocity.z = -100000.0f;
  obj->mtype.phys_info.rotvel = parent->mtype.phys_info.rotvel;
  vm_MakeZero(&obj->mtype.phys_info.rotthrust);
  obj->size = Poly_models[obj->rtype.pobj_info.model_num].submodel[subobj_num].rad * 0.5;
  obj->mtype.phys_info.mass = 40.0;
  obj->mtype.phys_info.drag = .001f;

  obj->mtype.phys_info.flags = (PF_GRAVITY | PF_BOUNCE | PF_FIXED_ROT_VELOCITY);
  obj->mtype.phys_info.coeff_restitution = .2f;
  obj->mtype.phys_info.rotvel.x = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
  obj->mtype.phys_info.rotvel.y = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
  obj->mtype.phys_info.rotvel.z = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
  if (death_flags & DF_DEBRIS_REMAINS) {
    obj->mtype.phys_info.num_bounces = 8;
    obj->mtype.phys_info.flags |= PF_STICK;
    obj->flags &= ~OF_USES_LIFELEFT;
    // ChrisP needs to add some code here to make the debris behave resonably
  } else {
    obj->mtype.phys_info.num_bounces = 2;
    obj->lifeleft = 2.0 + ((ps_rand() % 50) * .05);
    obj->flags |= OF_USES_LIFELEFT;
  }
  ASSERT(obj->control_type == CT_DEBRIS);
  // Copy death flags debris
  obj->ctype.debris_info.death_flags = death_flags;
  obj->ctype.debris_info.last_smoke_time = -1;
  // Done!
  return obj;
}
// Creates a subobject debris piece that goes off in a random direction
object *CreateSubobjectDebris(object *parent, int subobj_num, float explosion_mag, int death_flags) {
  vector rand_vec;
  // Set physics data for this object
  rand_vec.x = (float)(D3_RAND_MAX / 2 - ps_rand());
  rand_vec.y = (float)(D3_RAND_MAX / 2 - ps_rand()) + .2f * D3_RAND_MAX; // a habit of moving upwards
  rand_vec.z = (float)(D3_RAND_MAX / 2 - ps_rand());

  vm_NormalizeVectorFast(&rand_vec);
  explosion_mag *= 1.0f + ((float)(D3_RAND_MAX / 2 - ps_rand()) / (float)(D3_RAND_MAX / 2) * 0.05); // +5/-5 percent
  return CreateSubobjectDebrisDirected(parent, subobj_num, &rand_vec, explosion_mag, death_flags);
}
// Create extra fireballs for an exploding object
void CreateExtraFireballs(object *obj, float size_scale) {
  // Create some extra explosions to start later
  float expl_size = obj->size * size_scale;
  int size_add = expl_size / EXTRA_EXPLOSION_THRESHOLD;
  int extras = size_add + (ps_rand() % 4);
  int i;
  if (obj->type == OBJ_BUILDING && OBJECT_OUTSIDE(obj))
    extras += 4;
  // Cap at 12
  extras = std::min(12, extras);
  // mprintf(0,"Creating %d extra explosions\n",extras);
  CreateRandomSparks(extras, &obj->pos, obj->roomnum);
  for (i = 0; i < extras; i++) {
    vector pos = obj->pos;
    float vals[10], add_time;
    float upwards;
    // Make this a billowing explosion
    if (obj->type == OBJ_BUILDING && OBJECT_OUTSIDE(obj)) {
      float increment = (obj->size * 1.5) / extras;
      pos.y += (increment * i);
      add_time = (1.0 / extras) * i;
      upwards = 60;
    } else {
      pos.x += (((ps_rand() % 100) / 50.0) - 1.0) * (obj->size / 2);
      pos.y += (((ps_rand() % 100) / 50.0) - 1.0) * (obj->size / 2);
      pos.z += (((ps_rand() % 100) / 50.0) - 1.0) * (obj->size / 2);
      add_time = .3 + ((ps_rand() % 100) / 200.0);
      upwards = 0;
    }

    vals[0] = pos.x;
    vals[1] = pos.y;
    vals[2] = pos.z;
    if (size_add > 0) {
      if (ps_rand() % 2)
        vals[3] = BIG_EXPLOSION_INDEX;
      else
        vals[3] = GetRandomMediumExplosion();
    } else
      vals[3] = GetRandomMediumExplosion();
    vals[4] = obj->roomnum;
    vals[5] = expl_size;
    vals[6] = upwards;
    // Bash some values for billowing explosions
    if ((obj->type == OBJ_BUILDING) && (OBJECT_OUTSIDE(obj))) {
      float norm = ((float)(i + 1)) / extras;
      // norm=1.0-norm;
      vals[3] = GetRandomBillowingExplosion();
      vals[5] *= (.5 + (.5 * norm));
    }

    CreateNewEvent(0, 0, add_time, vals, sizeof(float) * 7, DoExplosionEvent);
  }
}
// Break apart a polygon model into pieces of debris
void BreakApartModel(object *obj, float explosion_mag, int death_flags) {
  poly_model *pm = GetPolymodelPointer(obj->rtype.pobj_info.model_num);
  if (pm->n_models > 1) {
    int i;

    // Create debris pieces from subobjects
    for (i = 1; i < pm->n_models; i++)
      CreateSubobjectDebris(obj, i, explosion_mag, death_flags);
    // Change size for collision purposes
    obj->size = Poly_models[obj->rtype.pobj_info.model_num].submodel[0].rad;
  }
}
// Splinter stuff
#define MAX_SPLINTERS_PER_OBJECT 10
// Creates individual face particles from the main body of an object
void CreateSplintersFromBody(object *obj, float explosion_mag, float lifetime) {
  ASSERT(obj->flags & OF_POLYGON_OBJECT);
  int facenums[MAX_SPLINTERS_PER_OBJECT];
  vector rot_vecs[MAX_SUBOBJECTS];
  int num_splinters = 0;
  int i, t;
  int parent_objnum = OBJNUM(obj);
  matrix m;
  m = obj->orient;
  vm_TransposeMatrix(&m);
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  // If submodel 0 not renderable, bail
  if (IsNonRenderableSubmodel(pm, 0))
    return;
  bsp_info *sm = &pm->submodel[0];
  if (sm->num_faces < MAX_SPLINTERS_PER_OBJECT) {
    for (i = 0; i < sm->num_faces; i++) {
      facenums[i] = i;
      num_splinters++;
    }
  } else {
    int limit = std::min(sm->num_faces, MAX_SPLINTERS_PER_OBJECT);
    for (i = 0; i < limit; i++) {
      facenums[i] = ps_rand() % sm->num_faces;
      num_splinters++;
    }
  }
  // Now, create those splinters!
  for (i = 0; i < num_splinters; i++) {
    int facenum = facenums[i];
    vector dest, center;
    int num_verts = std::min<float>(sm->faces[facenum].nverts, MAX_VERTS_PER_SPLINTER);

    vm_MakeZero(&dest);
    vm_MakeZero(&center);
    // First get the center of this particular face
    for (t = 0; t < num_verts; t++) {
      vector pnt = sm->verts[sm->faces[facenum].vertnums[t]];
      vector temp_vec;

      temp_vec = pnt * m;
      rot_vecs[t] = temp_vec;
      center += temp_vec;
    }

    center /= num_verts;
    dest = center + obj->pos;

    // Now create splinter with that faces center position
    int s_objnum = ObjCreate(OBJ_SPLINTER, pm - std::data(Poly_models), obj->roomnum, &dest, NULL);
    if (s_objnum < 0) {
      mprintf(0, "Couldn't create splinter object!\n");
      return;
    } else {
      // Fill in relevant info

      object *splinter_obj = &Objects[s_objnum];
      splinter_obj->ctype.splinter_info.subobj_num = 0;
      splinter_obj->ctype.splinter_info.facenum = facenum;
      for (t = 0; t < num_verts; t++)
        splinter_obj->ctype.splinter_info.verts[t] = (rot_vecs[t]) - center;
      splinter_obj->ctype.splinter_info.center = center;
      vector subvec = dest - obj->pos;
      vm_NormalizeVector(&subvec);
      ObjSetOrient(splinter_obj, &Identity_matrix);
      splinter_obj->mtype.phys_info.velocity =
          (obj->mtype.phys_info.velocity) + (((subvec * obj->size) / lifetime) * 4);
      splinter_obj->mtype.phys_info.flags |= PF_FIXED_ROT_VELOCITY;
      splinter_obj->mtype.phys_info.rotvel = splinter_obj->mtype.phys_info.velocity * 400;
      // Randomize by 20 percent plus or minus
      splinter_obj->mtype.phys_info.velocity *= 1.0 + ((((ps_rand() % 100) - 50) / 50.0) * .2);
      splinter_obj->mtype.phys_info.rotvel *= 1.0 + ((((ps_rand() % 100) - 50) / 50.0) * .2);

      vm_MakeZero(&splinter_obj->mtype.phys_info.rotthrust);
      splinter_obj->size = .5f;
      splinter_obj->mtype.phys_info.mass = 2500.0f;
      splinter_obj->mtype.phys_info.drag = .01f;

      splinter_obj->mtype.phys_info.flags |= (PF_GRAVITY) | (PF_BOUNCE);

      splinter_obj->mtype.phys_info.num_bounces = 0;
      splinter_obj->movement_type = MT_PHYSICS;
      SetObjectControlType(splinter_obj, CT_SPLINTER);
      splinter_obj->render_type = RT_SPLINTER;
      // Randomize the lifetime a little
      float mod_lifetime = lifetime;
      mod_lifetime += (((ps_rand() % 9) - 4) * .1);
      if ((OBJNUM(splinter_obj) % 14) == 0)
        mod_lifetime += ((ps_rand() % 3) * .5);
      splinter_obj->lifeleft = mod_lifetime;
      splinter_obj->lifetime = mod_lifetime;
      splinter_obj->flags |= OF_USES_LIFELEFT;
    }
  }
}
void DoDeathSpew(object *parent) {
  ASSERT(IS_GENERIC(parent->type));
  int i, j;
  int num_last_type = 0;
  uint8_t f_dspew = Object_info[parent->id].f_dspew;

  if (!parent)
    return;
  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    int type;
    int id;
    id = Object_info[parent->id].dspew[i];
    if (id == -1)
      continue; // spew type set to none
    type = Object_info[id].type;
    int max_spewed = Object_info[parent->id].dspew_number[i];
    int rand_val = (int)((float)D3_RAND_MAX * Object_info[parent->id].dspew_percent[i]);
    // Skip it if the player has that weapon battery enabled
    // If multiplayer, it will spew type 2 if no type 1 is spewed
    if (i == 0 && (f_dspew & DSF_ONLY_IF_PLAYER_HAS_OBJ_1)) {
      bool f_skip = false;

      if (Game_mode & GM_MULTI) {
        f_dspew &= ~DSF_ONLY_IF_PLAYER_HAS_OBJ_1;
        f_dspew |= DSF_ONLY_IF_NO_1;
      } else if (type == OBJ_POWERUP) {
        player *playp = &Players[0];
        for (j = 0; j < MAX_PLAYER_WEAPONS; j++) {
          if (playp->weapon_flags & HAS_FLAG(j)) {
            int p_id = Ships[playp->ship_index].spew_powerup[j];
            if (p_id == id) {
              f_skip = true;
              break;
            }
          }
        }
        if (f_skip)
          continue;
      }
    }

    if (i == 1 && (f_dspew & DSF_ONLY_IF_NO_1) && num_last_type != 0)
      continue;
    num_last_type = 0;
    for (j = 0; j < max_spewed; j++) {
      if (ps_rand() <= rand_val) {
        int objnum = ObjCreate(type, id, parent->roomnum, &parent->pos, NULL);
        num_last_type++;
        if (objnum < 0) {
          mprintf(0, "Couldn't spew object!\n");
          return;
        }
        object *obj = &Objects[objnum];

        // Set random velocity for powerups
        obj->mtype.phys_info.velocity.x = ((ps_rand() / (float)D3_RAND_MAX) - .5f) * 35.0;
        obj->mtype.phys_info.velocity.z = ((ps_rand() / (float)D3_RAND_MAX) - .5f) * 35.0;
        obj->mtype.phys_info.velocity.y = ((ps_rand() / (float)D3_RAND_MAX) - .5f) * 35.0;
        InitObjectScripts(obj);
        // Send object to other players
        if (Game_mode & GM_MULTI) {
          if (Netgame.local_role == LR_SERVER) {
            MultiSendObject(obj, 0);
          }
        }
      }
    }
  }
}

// Creates a fireball vis effect for the specified object
// The explosion size is based on the object size times the size_scale
// The fireball type will be randomly selected based on the explosion size
// Returns the visnum of the fireball
int CreateObjectFireball(object *objp, float size_scale) {
  int expl_type = GetRandomExplosion(objp->size * size_scale);
  float expl_size = objp->size * size_scale * 2.0;
  int fireball_visnum = CreateFireball(&objp->pos, expl_type, objp->roomnum, VISUAL_FIREBALL);
  if (fireball_visnum >= 0)
    VisEffects[fireball_visnum].size = expl_size;
  return fireball_visnum;
}
//	-------------------------------------------------------------------------------------------------------
// do whatever needs to be done for this piece of debris for this frame
void DoDebrisFrame(object *obj) {
  ASSERT(obj->control_type == CT_DEBRIS);
  // Get death flags
  int death_flags = obj->ctype.debris_info.death_flags;
  // See if we're dead
  if ((obj->lifeleft <= 0.0) || (obj->mtype.phys_info.num_bounces < 1)) {
    // If explodes, create fireball & sound
    if (death_flags & DF_DEBRIS_FIREBALL) {
      Sound_system.Play3dSound(SOUND_DEBRIS_EXPLODE, SND_PRIORITY_NORMAL, obj);
      CreateObjectFireball(obj);
    }
    // If debris has a blast ring, create it
    if (death_flags & DF_DEBRIS_BLAST_RING)
      CreateObjectBlastRing(obj);
    // Make debris go away, or make it inactive
    if (!(death_flags & DF_DEBRIS_REMAINS))
      SetObjectDeadFlag(obj);
    else
      SetObjectControlType(obj, CT_NONE);
    // Done with this debris
    return;
  }
  // Create smoke, if this debris smokes
  if (death_flags & DF_DEBRIS_SMOKES) {
    if (Gametime - obj->ctype.debris_info.last_smoke_time > .015 && (rand() % 2)) {
      // Create a small flame puff every now and then
      int visnum = CreateFireball(&obj->pos, BLACK_SMOKE_INDEX, obj->roomnum, VISUAL_FIREBALL);

      if (visnum >= 0)
        VisEffects[visnum].size = obj->size / 2; // Make small!
      obj->ctype.debris_info.last_smoke_time = Gametime;
    }
  }
}
// Create electrical bolts on an object
void CreateElectricalBolts(object *objp, int num_bolts) {
  for (int i = 0; i < num_bolts; i++) {
    poly_model *pm = &Poly_models[objp->rtype.pobj_info.model_num];
    int subnum = ps_rand() % pm->n_models;
    bsp_info *sm = &pm->submodel[subnum];
    if (sm->nverts > 0) {
      int visnum = VisEffectCreate(VIS_FIREBALL, LIGHTNING_BOLT_INDEX, objp->roomnum, &objp->pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];
        vis->lifeleft = 1.0;
        vis->lifetime = 1.0;
        vis->end_pos = objp->pos;
        vis->velocity.x = .15f;
        vis->velocity.y = 3;
        vis->attach_info.obj_handle = objp->handle;
        vis->attach_info.subnum = subnum;
        vis->attach_info.vertnum = ps_rand() % sm->nverts;
        vis->attach_info.end_vertnum = ps_rand() % sm->nverts;
        vis->attach_info.modelnum = objp->rtype.pobj_info.model_num;
        vis->flags = VF_USES_LIFELEFT | VF_EXPAND | VF_ATTACHED;
      }
    } else {
      mprintf(0, "VIS: Submodel %s has 0 vertices!!!\n", sm->name);
    }
  }
}
// Create a smoke spewer for the specified object
void CreateObjectSmokeSpewer(object *objp) {
  spewinfo myspew;
  myspew.random = 0;
  myspew.use_gunpoint = false;
  myspew.real_obj = false;
  myspew.pt.origin = objp->pos;
  myspew.pt.normal.x = 0;
  myspew.pt.normal.y = 1.0;
  myspew.pt.normal.z = 0;
  myspew.pt.room_num = objp->roomnum;
  myspew.effect_type = BLACK_SMOKE_INDEX;
  myspew.drag = .01f;
  myspew.mass = 10;
  myspew.time_int = .25;
  myspew.longevity = 30;
  myspew.lifetime = 2.0;
  myspew.size = 10.0;
  myspew.speed = 50;
  SpewCreate(&myspew);
}
// Play the explosion sound for this object
void PlayObjectExplosionSound(object *objp) {
  int sound;
  if (objp->type == OBJ_DOOR) {
    sound = SOUND_ROBOT_EXPLODE_1;
  } else {
    ASSERT(IS_GENERIC(objp->type));
    sound = Object_info[objp->id].sounds[GSI_EXPLODE];
    if (sound == SOUND_NONE_INDEX) { // check for default
      if (objp->type == OBJ_BUILDING)
        sound = SOUND_BUILDING_EXPLODE;
      else
        sound = (ps_rand() > D3_RAND_MAX / 2) ? SOUND_ROBOT_EXPLODE_1 : SOUND_ROBOT_EXPLODE_2;
    }
  }
  if (sound != -1)
    Sound_system.Play3dSound(sound, SND_PRIORITY_HIGH, objp);
}
const char *dead_object_types[] = {
    "swatter", "swatter(deadmodel)", "Hangturret",  "Securityturret(DEAD)",
    "Lance",   "Lance(DEAD)",        "L10 swatter", "swatter(deadmodel)",
};
#define N_DEAD_OBJECT_TYPES (sizeof(dead_object_types) / sizeof(*dead_object_types) / 2)
#include "osiris_predefs.h"
// Creates a dead version of the given object
void CreateDeadObject(object *objp) {
  if (objp->type == OBJ_ROBOT) {
    for (int i = 0; i < N_DEAD_OBJECT_TYPES; i++) {
      if (stricmp(Object_info[objp->id].name, dead_object_types[i * 2]) == 0) {
        int id = FindObjectIDName(dead_object_types[i * 2 + 1]);
        if (id != -1) {
          vector old_point, pos;
          PhysCalcGround(&old_point, NULL, objp, 0); // Old ground point
          poly_model *pm = GetPolymodelPointer(Object_info[id].render_handle);
          pos = old_point - pm->ground_slots[0].pnt * ~objp->orient;
          osipf_ObjCreate(Object_info[id].type, id, objp->roomnum, &pos, &objp->orient);
        }
        return; // done
      }
    }
  }
}
#define FADE_TIME 2.0
// Destroy an object immediately
void DestroyObject(object *objp, float explosion_mag, int death_flags) {
  ASSERT(IS_GENERIC(objp->type) || (objp->type == OBJ_DOOR));
  // Say this this object is dying (if not already set)
  objp->flags |= OF_DYING;
  // Create blast ring if enabled for this object
  if (death_flags & DF_BLAST_RING)
    CreateObjectBlastRing(objp);
  // Do a shake & shockwave only if the object either breaks apart or has fireballs
  if ((death_flags & DF_FIREBALL) || (death_flags & DF_BREAKS_APART)) {
    // Shake the player.  The odd magnitude is from Jason's old code.
    // maybe it would make more sense to base the shake on the explosion size
    float dist = vm_VectorDistanceQuick(&Player_object->pos, &objp->pos);
    if (dist / objp->size < 30.0)
      AddToShakeMagnitude(objp->size * 5.0 - dist / 6.0);
    // Do a shockwave
    MakeShockwave(objp, objp->handle);
  }
  // Play sound if not flagged to play at start of delay
  if (!(death_flags & DF_DELAY_SOUND))
    PlayObjectExplosionSound(objp);
  // Do death spew if generic object
  if (IS_GENERIC(objp->type)) {
    if (!((Game_mode & GM_MULTI) && (Netgame.local_role != LR_SERVER)))
      if (Demo_flags != DF_PLAYBACK)
        DoDeathSpew(objp);
  }
  ASSERT(objp->flags & OF_POLYGON_OBJECT);
  ASSERT(objp->rtype.pobj_info.subobj_flags == 0xFFFFFFFF);
  // Create fireballs
  int fireball_visnum = -1;
  if (death_flags & DF_FIREBALL) {
    // Determine size of explosion
    float size_scale;
    switch (DEATH_EXPL_SIZE(death_flags)) {
    case DF_EXPL_SMALL:
      size_scale = 0.5f;
      break;
    case DF_EXPL_MEDIUM:
      size_scale = 1.0f;
      break;
    case DF_EXPL_LARGE:
      size_scale = 1.6f;
      break;
    default:
      Int3();
    }
    // Create big fireball
    fireball_visnum = CreateObjectFireball(objp, size_scale);
    // Create extra fireballs
    CreateExtraFireballs(objp, size_scale);
  }
  // Switch to dying model
  if (objp->rtype.pobj_info.dying_model_num != -1)
    objp->rtype.pobj_info.model_num = objp->rtype.pobj_info.dying_model_num;
  // Create debris pieces
  if (death_flags & DF_BREAKS_APART)
    BreakApartModel(objp, explosion_mag, death_flags);
  // Create splinters.  Base life of the life of the fireball created earlier
  if (death_flags & DF_FIREBALL) {
    float fireball_lifeleft = (fireball_visnum != -1) ? VisEffects[fireball_visnum].lifeleft : 2.0;
    CreateSplintersFromBody(objp, explosion_mag, OBJECT_OUTSIDE(objp) ? fireball_lifeleft : (fireball_lifeleft / 2.0));
  }
  // Make sure its ok to delete if this is a netplayer game
  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT) && (objp->flags & OF_SERVER_OBJECT))
    ASSERT(objp->flags & OF_SERVER_SAYS_DELETE);
  // Make object go away or become inert
  if (death_flags & DF_REMAINS) { // Make object do nothing
    SetObjectControlType(objp, CT_NONE);
    objp->type = OBJ_DEBRIS; // do it won't do idle animation
    objp->movement_type = MT_NONE;
  } else if (death_flags & DF_FADE_AWAY) {
    ASSERT(objp->effect_info != NULL);
    objp->effect_info->type_flags |= EF_FADING_OUT;
    objp->effect_info->fade_time = objp->effect_info->fade_max_time = FADE_TIME;
    objp->lifeleft = FADE_TIME;
    objp->flags |= OF_USES_LIFELEFT;
    objp->control_type = CT_NONE;
  } else { // Mark the object to die
    CreateDeadObject(objp);
    SetObjectDeadFlag(objp);
  }
}
#define ELECTRICAL_DEATH_TIME 3.0
// Process a dying object for one frame
void DoDyingFrame(object *objp) {
  // Make sure types & flags are right
  ASSERT(objp->flags & OF_DYING);
  ASSERT((objp->control_type == CT_DYING) || (objp->control_type == CT_DYING_AND_AI));
  // Get death flags
  int death_flags = objp->ctype.dying_info.death_flags;
  // Update delay time
  objp->ctype.dying_info.delay_time -= Frametime;
  // Done dying?
  if (objp->ctype.dying_info.delay_time < 0) {
    // Kill the object for real
    DestroyObject(objp, 30, death_flags);
    // Add to score
    if ((objp->ctype.dying_info.killer_playernum != -1) && IS_GENERIC(objp->type))
      PlayerScoreAdd(objp->ctype.dying_info.killer_playernum, Object_info[objp->id].score);
    // We're done
    return;
  }
  // If sparking death, do sparks
  if (death_flags & DF_DELAY_SPARKS) {
    float dying_norm = objp->ctype.dying_info.delay_time / ELECTRICAL_DEATH_TIME;
    dying_norm = std::min<float>(dying_norm, 1.0);
    // Do deform stuff
    objp->effect_info->type_flags |= EF_DEFORM;
    objp->effect_info->deform_time = 1.0;
    objp->effect_info->deform_range = (1.0 - dying_norm) * .2f;
    int dying_chance = (dying_norm * 10) + 1;
    // Create random electrical effect
    if (Gametime - objp->ctype.dying_info.last_spark_time > .01) {
      if ((ps_rand() % dying_chance) == 0) {
        int num_bolts = ((1.0 - dying_norm) * 5.0) + 3;
        CreateElectricalBolts(objp, num_bolts);
      }
      objp->ctype.dying_info.last_spark_time = Gametime;
    }
  }
  // If fireball death, do fireballs
  if (death_flags & DF_DELAY_FIREBALL) {
    vector velocity_norm = objp->mtype.phys_info.velocity;
    vm_NormalizeVector(&velocity_norm);
    vector pos = objp->pos - (velocity_norm * (objp->size / 2));
    if (OBJECT_OUTSIDE(objp))
      CreateFireball(&pos, BLACK_SMOKE_INDEX, objp->roomnum, VISUAL_FIREBALL);
    // Create an explosion that follows every now and then
    if ((Gametime - objp->ctype.dying_info.last_fireball_time > .01) && (ps_rand() % 3) == 0) {
      if (!(objp->flags & OF_POLYGON_OBJECT))
        return;
      objp->ctype.dying_info.last_fireball_time = Gametime;
      vector dest;
      poly_model *pm = &Poly_models[objp->rtype.pobj_info.model_num];
      bsp_info *sm = &pm->submodel[0];
      int vertnum = ps_rand() % sm->nverts;
      GetPolyModelPointInWorld(&dest, &Poly_models[objp->rtype.pobj_info.model_num], &objp->pos, &objp->orient, 0,
                               &sm->verts[vertnum]);
      int visnum = CreateFireball(&dest, GetRandomSmallExplosion(), objp->roomnum, VISUAL_FIREBALL);
      if (visnum >= 0) // DAJ this pervents a -1 array index
      {
        VisEffects[visnum].size += ((ps_rand() % 20) / 20.0) * 3.0;
        if ((ps_rand() % 2)) {
          VisEffects[visnum].movement_type = MT_PHYSICS;
          VisEffects[visnum].velocity = objp->mtype.phys_info.velocity;
          VisEffects[visnum].mass = objp->mtype.phys_info.mass;
          VisEffects[visnum].drag = objp->mtype.phys_info.drag;
        }
      }
    }
  }
  // If smoke death, do smoke
  if (death_flags & DF_DELAY_SMOKES) {
    // see if we should draw some smoke
    if ((Gametime - objp->ctype.dying_info.last_smoke_time > .01) &&
        (ps_rand() % 3) == 0) { // don't draw most of the time
      objp->ctype.dying_info.last_smoke_time = Gametime;

      // Make even less likely inside
      if (OBJECT_OUTSIDE(objp) || ((ps_rand() % 2) == 0))
        CreateFireball(&objp->pos, BLACK_SMOKE_INDEX, objp->roomnum, VISUAL_FIREBALL);
    }
  }
}
// Pulls every object near the gravity field into its center
void DoGravityFieldEffect(object *obj) {
  float max_size = obj->ctype.blast_info.max_size;
  float lifenorm = (obj->lifetime - obj->lifeleft) / obj->lifetime;
  float dist, force;
  vector vforce;
  int i;
  object *hit_obj_ptr;
  float time_norm = 1.0 - (obj->lifeleft / obj->lifetime);
  obj->size = max_size;
  float sphere_norm = 1.0 - ((lifenorm - .1) * 1.5);
  if (sphere_norm < 0)
    sphere_norm = 0;
  SetShakeMagnitude(25);
  float vdist = vm_VectorDistanceQuick(&Viewer_object->pos, &obj->pos);
  CreateRandomSparks(3, &obj->pos, obj->roomnum, -1, 2);

  if (!(obj->flags & OF_SERVER_SAYS_DELETE)) {
    obj->flags |= OF_SERVER_SAYS_DELETE;
    int visnum = VisEffectCreate(VIS_FIREBALL, SUN_CORONA_INDEX, obj->roomnum, &obj->pos);
    if (visnum >= 0) {
      vis_effect *vis = &VisEffects[visnum];
      vis->size = max_size / 4;
      vis->lifeleft = obj->lifetime;
      vis->lifetime = obj->lifetime;
      vis->flags = VF_USES_LIFELEFT | VF_WINDSHIELD_EFFECT;
    }
    // Create lightning from the heavens
    if (OBJECT_OUTSIDE(obj) && vdist > 5) {
      int visnum = VisEffectCreate(VIS_FIREBALL, THICK_LIGHTNING_INDEX, obj->roomnum, &obj->pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];
        vis->lifeleft = obj->lifetime;
        vis->lifetime = obj->lifetime;
        vis->end_pos = obj->pos;

        vis->end_pos.y = obj->pos.y + (MAX_TERRAIN_HEIGHT * 2);
        vis->velocity.x = 2;
        vis->velocity.y = 1;
        vis->velocity.z = 3;
        vis->custom_handle = FindTextureName("ThickLineLightning");
        vis->billboard_info.width = 70;
        vis->billboard_info.texture = 0;

        vis->lighting_color = OPAQUE_FLAG | GR_RGB16(100, 150, 255);
        vis->flags = VF_USES_LIFELEFT | VF_WINDSHIELD_EFFECT;
        vis->size = 50;
      }
    }
    // Create lightning from the heavens
    if (!OBJECT_OUTSIDE(obj)) {
      ps_srand(Gametime * 100);
      int count = 0;
      // Cast 3 rays out from the center
      for (i = 0; i < 3; i++) {
      again:
        vector rand_vector, test_vector;
        rand_vector.x = ((ps_rand() % 100 - 50) / 50.0) + .1; // So we don't get a zero vector
        rand_vector.y = ((ps_rand() % 100) - 50) / 50.0;
        rand_vector.z = ((ps_rand() % 100) - 50) / 50.0;
        vm_NormalizeVector(&rand_vector);
        test_vector = obj->pos + (rand_vector * 1000);
        vector dest_pos;
        int dest_room;
        fvi_query fq;
        fvi_info hit_info;
        int fate;
        fq.p0 = &obj->pos;
        fq.p1 = &test_vector;
        fq.startroom = obj->roomnum;

        fq.rad = 0.0f;
        fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
        fq.thisobjnum = OBJNUM(obj);
        fq.ignore_obj_list = NULL;
        fate = fvi_FindIntersection(&fq, &hit_info);
        dest_pos = hit_info.hit_pnt;
        dest_room = hit_info.hit_room;
        if (count < 5) {
          if (vm_VectorDistance(&obj->pos, &dest_pos) < 2) {
            count++;
            goto again;
          } else
            count = 0;
        }
        int visnum = VisEffectCreate(VIS_FIREBALL, THICK_LIGHTNING_INDEX, obj->roomnum, &obj->pos);
        if (visnum >= 0) {
          vis_effect *vis = &VisEffects[visnum];
          vis->lifeleft = obj->lifetime;
          vis->lifetime = obj->lifetime;

          vis->end_pos = dest_pos;

          vis->custom_handle = FindTextureName("ThickLineLightning");
          vis->billboard_info.width = 25;
          vis->billboard_info.texture = 1;
          vis->velocity.x = 2;
          vis->velocity.y = 1;
          vis->velocity.z = .5;

          vis->lighting_color = GR_RGB16(100, 150, 255);
          vis->flags = VF_USES_LIFELEFT | VF_WINDSHIELD_EFFECT | VF_LINK_TO_VIEWER;
          vis->size = 50;
        }
      }
    }
  }
  // Create random strands of lightning
  for (i = 0; i < 3 && vdist > 5; i++) {
    int visnum = VisEffectCreate(VIS_FIREBALL, LIGHTNING_BOLT_INDEX, obj->roomnum, &obj->pos);
    if (visnum >= 0) {
      vis_effect *vis = &VisEffects[visnum];
      vis->lifeleft = Frametime;
      vis->lifetime = Frametime;
      vis->end_pos = obj->pos;
      vis->end_pos.x += (((float)(ps_rand() % 100) - 50) / 50.0) * sphere_norm * max_size;
      vis->end_pos.y += (((float)(ps_rand() % 100) - 50) / 50.0) * sphere_norm * max_size;
      vis->end_pos.z += (((float)(ps_rand() % 100) - 50) / 50.0) * sphere_norm * max_size;
      vis->custom_handle = visnum;
      vis->velocity.x = 2;
      vis->velocity.y = .25;
      vis->flags = VF_USES_LIFELEFT;
      vis->size = 100;
    }
  }

  for (i = 0; i <= Highest_object_index; i++) {
    hit_obj_ptr = &Objects[i];
    if (!(hit_obj_ptr->type == OBJ_PLAYER || hit_obj_ptr->type == OBJ_ROBOT || hit_obj_ptr->type == OBJ_WEAPON ||
          hit_obj_ptr->type == OBJ_POWERUP || hit_obj_ptr->type == OBJ_CLUTTER ||
          (hit_obj_ptr->type == OBJ_BUILDING && hit_obj_ptr->ai_info)))
      continue;
    if (hit_obj_ptr->type == OBJ_WEAPON && !(Weapons[hit_obj_ptr->id].flags & WF_MATTER_WEAPON))
      continue;
    if (obj == hit_obj_ptr)
      continue;
    if (hit_obj_ptr->flags & OF_DEAD)
      continue;
    if (hit_obj_ptr->movement_type != MT_PHYSICS)
      continue;
    // The distance is actually the objects' centers minus some of the hit object's radius (I set it to 80%)
    if ((hit_obj_ptr->flags & OF_POLYGON_OBJECT) && hit_obj_ptr->type != OBJ_WEAPON &&
        hit_obj_ptr->type != OBJ_POWERUP && hit_obj_ptr->type != OBJ_DEBRIS) {
      vector pos;
      pos = hit_obj_ptr->pos + hit_obj_ptr->wall_sphere_offset;
      dist = vm_VectorDistanceQuick(&pos, &obj->pos) - Poly_models[hit_obj_ptr->rtype.pobj_info.model_num].wall_size;
    } else {
      dist = vm_VectorDistanceQuick(&hit_obj_ptr->pos, &obj->pos) - hit_obj_ptr->size;
    }

    if (dist < 0.0f)
      dist = 0.0f;
    if (dist <= (obj->ctype.blast_info.max_size * 2)) {

      float dist_norm = 1.0 - (dist / (obj->ctype.blast_info.max_size * 2));
      force = dist_norm * time_norm * 30;
      // Cap it
      if (force > 500)
        force = 500;

      // Find the force vector on the object
      vm_GetNormalizedDirFast(&vforce, &hit_obj_ptr->pos, &obj->pos);
      vforce *= (-force); // Sucking vector
      if (hit_obj_ptr->mtype.phys_info.mass > 1)
        vforce *= (hit_obj_ptr->mtype.phys_info.mass * 5);
      // Don't affect powerups in a multiplayer game
      if (!((Game_mode & GM_MULTI) && hit_obj_ptr->type == OBJ_POWERUP))
        phys_apply_force(hit_obj_ptr, &vforce);
      if (hit_obj_ptr != Viewer_object) {
        // Create strands of lightning
        int visnum = VisEffectCreate(VIS_FIREBALL, LIGHTNING_BOLT_INDEX, obj->roomnum, &obj->pos);
        if (visnum >= 0) {
          vis_effect *vis = &VisEffects[visnum];
          vis->lifeleft = Frametime;
          vis->lifetime = Frametime;
          vis->end_pos = hit_obj_ptr->pos;
          vis->custom_handle = OBJNUM(hit_obj_ptr);
          vis->flags = VF_USES_LIFELEFT | VF_NO_Z_ADJUST;
          vis->size = dist;
          vis->velocity.x = 1;
          vis->velocity.y = .25;
        }
        if ((ps_rand() % 8) == 0)
          CreateRandomSparks(ps_rand() % 3, &hit_obj_ptr->pos, hit_obj_ptr->roomnum, -1, (ps_rand() % 2) + 2);
      }

      // Peg the object to the gravity field center if it is close
      hit_obj_ptr->mtype.phys_info.flags |= PF_DESTINATION_POS;
      hit_obj_ptr->mtype.phys_info.dest_pos = obj->pos;
    }
  }
}
// do whatever needs to be done for this explosion for this frame
void DoExplosionFrame(object *obj) {
  ASSERT(obj->control_type == CT_EXPLOSION);
  ASSERT(obj->type != OBJ_PLAYER);
  if (obj->id == GRAVITY_FIELD_INDEX) {
    DoGravityFieldEffect(obj);
  }

  // See if we should die of old age
  if (obj->lifeleft <= 0.0) {
    if (obj->id == GRAVITY_FIELD_INDEX) {
      // Create a big ass explosion
      if (OBJECT_OUTSIDE(obj))
        CreateBlastRing(&obj->pos, BLAST_RING_INDEX, DAMAGE_RING_TIME, obj->ctype.blast_info.max_size * 3, obj->roomnum,
                        1);
      else
        CreateBlastRing(&obj->pos, BLAST_RING_INDEX, DAMAGE_RING_TIME, obj->ctype.blast_info.max_size, obj->roomnum, 1);

      //	Blow the damn thing up and register a kill.

      float mag = vm_VectorDistanceQuick(&obj->pos, &Player_object->pos);
      if (mag > obj->ctype.blast_info.max_size)
        mag = 0;
      else
        mag = 1.0 - (mag / obj->ctype.blast_info.max_size);

      if (OBJECT_OUTSIDE(Viewer_object))
        AddToShakeMagnitude(mag * obj->ctype.blast_info.max_size * 5);
      else
        AddToShakeMagnitude(mag * obj->ctype.blast_info.max_size * 2);
      obj->impact_time = 0;
      obj->impact_size = obj->ctype.blast_info.max_size;
      obj->impact_force = obj->impact_size * 2;
      obj->impact_player_damage = obj->impact_size * 3;
      obj->impact_generic_damage = obj->impact_size * 3;

      if (Game_mode & GM_MULTI) // Do different damage to players if in multiplayer
        DoConcussiveForce(obj, obj->parent_handle, 1.0f / 5.0f);
      else
        DoConcussiveForce(obj, obj->parent_handle, 1.0);
      CreateRandomSparks(200, &obj->pos, obj->roomnum, -1, (ps_rand() % 2) + 2);

      int explode_visnum = CreateFireball(&obj->pos, BLUE_EXPLOSION_INDEX, obj->roomnum, VISUAL_FIREBALL);
      if (explode_visnum >= 0)
        VisEffects[explode_visnum].size = obj->ctype.blast_info.max_size;
    }

    // We died of old age
    SetObjectDeadFlag(obj);
    obj->lifeleft = 0.0;
  }
}
void MakeShockwave(object *explode_obj_ptr, int parent_handle) {
  if (explode_obj_ptr->impact_time > 0.0) {
    object *p = ObjGet(parent_handle);
    object *top_parent = p;
    int handle;
    ASSERT(explode_obj_ptr);
    while (p) {
      p = ObjGet(p->parent_handle);
      if (p) {
        top_parent = p;
      }
    }
    if (top_parent) {
      handle = top_parent->handle;
    } else {
      handle = OBJECT_HANDLE_NONE;
    }
    int objnum = ObjCreate(OBJ_SHOCKWAVE, 0, explode_obj_ptr->roomnum, &explode_obj_ptr->pos, NULL, handle);
    if (objnum >= 0) {
      Objects[objnum].control_type = CT_NONE;
      Objects[objnum].movement_type = MT_SHOCKWAVE;
      Objects[objnum].render_type = RT_NONE;
      Objects[objnum].lifeleft = explode_obj_ptr->impact_time;
      Objects[objnum].impact_size = explode_obj_ptr->impact_size;
      Objects[objnum].impact_force = explode_obj_ptr->impact_force;
      Objects[objnum].impact_player_damage = explode_obj_ptr->impact_player_damage;
      Objects[objnum].impact_generic_damage = explode_obj_ptr->impact_generic_damage;
      Objects[objnum].impact_time = explode_obj_ptr->impact_time;
      Objects[objnum].flags |= OF_USES_LIFELEFT;
    }
  } else {
    DoConcussiveForce(explode_obj_ptr, parent_handle);
  }
}
// object *object_create_explosion_sub(object *explode_obj_ptr, int16_t segnum, vms_vector * position, fix size, int
// vclip_type, fix maxdamage, fix maxdistance, fix maxforce, int parent )
void DoConcussiveForce(object *explode_obj_ptr, int parent_handle, float player_scalar) {
  int objnum;
  float max_player_damage = explode_obj_ptr->impact_player_damage;
  float max_generic_damage = explode_obj_ptr->impact_generic_damage;
  float maxforce = explode_obj_ptr->impact_force;
  float maxdistance = explode_obj_ptr->impact_size;
  float effect_distance;
  int16_t parent;
  object *parent_obj;
  if (explode_obj_ptr->type == OBJ_SHOCKWAVE) {
    effect_distance =
        explode_obj_ptr->impact_size * ((Gametime - explode_obj_ptr->creation_time) / explode_obj_ptr->impact_time);
    if (effect_distance > explode_obj_ptr->impact_size)
      effect_distance = explode_obj_ptr->impact_size;
  } else {
    effect_distance = explode_obj_ptr->impact_size;
  }
  parent_obj = ObjGet(parent_handle);
  if (parent_obj != NULL)
    parent = OBJNUM(parent_obj);
  objnum = OBJNUM(explode_obj_ptr);
  if (explode_obj_ptr->impact_size <= 0.0)
    return;
  {
    float dist, force;
    vector vforce;
    float damage;
    int i;
    object *hit_obj_ptr;

    for (i = 0; i <= Highest_object_index; i++) {
      //	Weapons used to be affected by badass explosions, but this introduces serious problems.
      //	When a smart bomb blows up, if one of its children goes right towards a nearby wall, it will
      //	blow up, blowing up all the children.  So I remove it.  MK, 09/11/94
      //			if ( (hit_obj_ptr!=explode_obj_ptr) && !(hit_obj_ptr->flags&OF_DEAD) &&
      //((hit_obj_ptr->type==OBJ_WEAPON /*&& (hit_obj_ptr->id==PROXIMITY_ID || hit_obj_ptr->id==SUPERPROX_ID ||
      // hit_obj_ptr->id==PMINE_ID)*/) || (hit_obj_ptr->type == OBJ_CNTRLCEN) || (hit_obj_ptr->type==OBJ_PLAYER) ||
      //((hit_obj_ptr->type==OBJ_ROBOT) && ((Objects[parent].type != OBJ_ROBOT) || (Objects[parent].id !=
      // hit_obj_ptr->id))))) {
      hit_obj_ptr = &Objects[i];
      // Check for types that get concussive force
      if (!((hit_obj_ptr->type == OBJ_WEAPON) || (hit_obj_ptr->type == OBJ_ROBOT) ||
            (hit_obj_ptr->type == OBJ_BUILDING) || (hit_obj_ptr->type == OBJ_PLAYER) ||
            (hit_obj_ptr->type == OBJ_DOOR) || (hit_obj_ptr->type == OBJ_CLUTTER)))
        continue;
      if ((hit_obj_ptr != explode_obj_ptr) && !(hit_obj_ptr->flags & OF_DEAD)) {
        if (hit_obj_ptr->movement_type == MT_PHYSICS || hit_obj_ptr->movement_type == MT_WALKING) {
          if (hit_obj_ptr->mtype.phys_info.flags & PF_IGNORE_CONCUSSIVE_FORCES)
            continue;
        }
        if (hit_obj_ptr->movement_type == MT_PHYSICS || hit_obj_ptr->movement_type == MT_WALKING) {
          if ((hit_obj_ptr->mtype.phys_info.flags & PF_IGNORE_OWN_CONC_FORCES) &&
              ObjGetUltimateParent(hit_obj_ptr) == ObjGetUltimateParent(explode_obj_ptr))
            continue;
        }
        // The distance is actually the objects' centers minus some of the hit object's radius (I set it to 80%)
        if ((hit_obj_ptr->flags & OF_POLYGON_OBJECT) && hit_obj_ptr->type != OBJ_WEAPON &&
            hit_obj_ptr->type != OBJ_POWERUP && hit_obj_ptr->type != OBJ_DEBRIS) {
          vector pos;
          pos = hit_obj_ptr->pos + hit_obj_ptr->wall_sphere_offset;
          dist = vm_VectorDistanceQuick(&pos, &explode_obj_ptr->pos) -
                 Poly_models[hit_obj_ptr->rtype.pobj_info.model_num].wall_size;
        } else {
          dist = vm_VectorDistanceQuick(&hit_obj_ptr->pos, &explode_obj_ptr->pos) - hit_obj_ptr->size;
        }

        if (dist < 0.0f)
          dist = 0.0f;
        // Make damage be from 'maxdamage' to 0.0, where 0.0 is 'maxdistance' away;
        if (dist <= effect_distance) {
          // mprintf(0, "Distance = %f\n", dist);
          if (1 /*object_to_object_visibility(obj, hit_obj_ptr, FQ_TRANSWALL)*/) {
            fvi_query fq;
            fvi_info hit_info;
            int fate;
            if (explode_obj_ptr->type == OBJ_SHOCKWAVE) {
              int index = i >> 5;
              int bit = i % 32;
              if (explode_obj_ptr->mtype.shock_info.damaged_list[index] & (0x00000001 << bit)) {
                continue;
              } else {
                explode_obj_ptr->mtype.shock_info.damaged_list[index] |= (0x00000001 << bit);
              }
            }
            // This section excludes objects that are not visible at shockwave passby time
            {
              if (!BOA_IsVisible(hit_obj_ptr->roomnum, explode_obj_ptr->roomnum)) {
                continue;
              }
              vector subvec = hit_obj_ptr->pos - explode_obj_ptr->pos;
              vm_NormalizeVectorFast(&subvec);
              vector hitvec = (explode_obj_ptr->pos + (subvec * .05f));
              fq.p0 = &hitvec;
              fq.p1 = &hit_obj_ptr->pos;
              fq.startroom = explode_obj_ptr->roomnum;

              fq.rad = 0.0f;
              fq.flags = FQ_CHECK_OBJS | FQ_ONLY_DOOR_OBJ | FQ_BACKFACE | FQ_NO_RELINK;
              fq.thisobjnum = OBJNUM(explode_obj_ptr);
              fq.ignore_obj_list = NULL;
              fate = fvi_FindIntersection(&fq, &hit_info);
              if (fate != HIT_NONE) {
                continue;
              }
            }
            if (hit_obj_ptr->type == OBJ_PLAYER)
              damage = max_player_damage - (dist / maxdistance) * max_player_damage;
            else
              damage = max_generic_damage - (dist / maxdistance) * max_generic_damage;

            force = maxforce - (dist / maxdistance) * maxforce;
            // mprintf(0, "f %f d %f\n", force, damage);
            // Find the force vector on the object
            vm_GetNormalizedDirFast(&vforce, &hit_obj_ptr->pos, &explode_obj_ptr->pos);
            vforce *= force;

            if (hit_obj_ptr->type == OBJ_CLUTTER) // Reduces the ping pong effect
              vforce *= .5f;
            if (hit_obj_ptr->movement_type == MT_PHYSICS)
              phys_apply_force(hit_obj_ptr, &vforce);
            // Apply damage to players, generics, and doors
            if (damage) {

              if (hit_obj_ptr->type == OBJ_PLAYER) {
                if (Demo_flags != DF_PLAYBACK) {
                  ApplyDamageToPlayer(hit_obj_ptr, parent_obj, PD_CONCUSSIVE_FORCE, damage * player_scalar);
                  mprintf(0, "Applying %f damage to player from force.\n", damage);
                }

                //	 shake player cockpit if damage is pretty bad.
                if (hit_obj_ptr->id == Player_num) {
                  float mag = damage / 200.0f;
                  vector vec = vforce;
                  vm_NormalizeVector(&vec);
                  // mprintf(0, "force: %.1f,%.1f,%.1f mag=%.2f\n", vec.x,vec.y,vec.z,mag);
                  StartCockpitShake(mag, &vec);
                }
              } else if (IS_GENERIC(hit_obj_ptr->type) || (hit_obj_ptr->type == OBJ_DOOR)) {
                if (Demo_flags != DF_PLAYBACK)
                  ApplyDamageToGeneric(hit_obj_ptr, parent_obj, GD_CONCUSSIVE, damage);
              }
            }
          } else {
            // mprintf(0, "No badass: robot=%2i, dist=%7.3f, maxdistance=%7.3f .\n", i, f2fl(dist), f2fl(maxdistance));
          }   // end if (object_to_object_visibility...
        }     // end if (dist < maxdistance)
      }       // end for
    }
  } // end if (maxdamage...
  //	return obj;
}
void CreateBlueBlastRing(vector *pos, int index, float lifetime, float max_size, int roomnum, int objnum,
                         int force_up) {
  if (!Viewer_object)
    return;
  if (objnum == -1) // Create a new object
  {
    objnum = ObjCreate(OBJ_FIREBALL, index, roomnum, pos, NULL);
    if (objnum < 0) // DAJ -1FIX
    {
      mprintf(0, "Couldn't create blast object!\n");
      return;
    }
    Objects[objnum].size = 1.0;
    Objects[objnum].flags |= OF_USES_LIFELEFT;
    Objects[objnum].ctype.blast_info.max_size = max_size;
  }
  matrix tempm;
  // Point straight up

  if (ps_rand() % 2 || force_up) {
    memset(&tempm, 0, sizeof(matrix));
    tempm.rvec.x = 1.0;
    tempm.uvec.z = -1.0;
    tempm.fvec.y = 1.0;
  } else {
    // Face the viewer
    vector fvec = Viewer_object->pos - *pos;
    vm_NormalizeVectorFast(&fvec);
    if (vm_GetMagnitudeFast(&fvec) < .5)
      return;
    vm_VectorToMatrix(&tempm, &fvec, NULL, NULL);
  }
  ObjSetOrient(&Objects[objnum], &tempm);
  Objects[objnum].lifeleft = lifetime / 2;
  Objects[objnum].lifetime = lifetime / 2;
  Objects[objnum].ctype.blast_info.bm_handle = Fireballs[BLUE_BLAST_RING_INDEX].bm_handle;
}
// Creates a blast ring to be drawn
int CreateBlastRing(vector *pos, int index, float lifetime, float max_size, int roomnum, int force_blue) {
  int objnum;
  float vals[4];
  fvi_info hit_info;
  fvi_query fq;
  if (!Viewer_object)
    return -1;
  // First create a flash if the viewer can see it
  fq.p0 = &Viewer_object->pos;
  fq.p1 = pos;
  fq.startroom = Viewer_object->roomnum;

  fq.rad = 0.01f;
  fq.flags = FQ_NO_RELINK;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;
  int fate = fvi_FindIntersection(&fq, &hit_info);
  if (fate == HIT_NONE) {
    vals[0] = 1.0;
    vals[1] = 1.0;
    vals[2] = 1.0;
    vals[3] = .8f;
    CreateNewEvent(RENDER_EVENT, 0, 0, &vals, sizeof(float) * 4, DrawAlphaEvent);
  }

  objnum = ObjCreate(OBJ_FIREBALL, index, roomnum, pos, NULL);
  if (objnum < 0) {
    mprintf(0, "Couldn't create blast object!\n");
    return -1;
  }
  Objects[objnum].size = max_size;
  Objects[objnum].flags |= OF_USES_LIFELEFT;
  Objects[objnum].lifeleft = lifetime;
  Objects[objnum].lifetime = lifetime;
  Objects[objnum].ctype.blast_info.max_size = max_size;
  Objects[objnum].ctype.blast_info.bm_handle = Fireballs[index].bm_handle;
  if ((ps_rand() % 2)) {
    ObjSetOrient(&Objects[objnum], &Identity_matrix);
    if ((ps_rand() % 3) == 0 || force_blue)
      CreateBlueBlastRing(pos, index, lifetime, max_size, roomnum, -1, force_blue);
  } else
    CreateBlueBlastRing(pos, index, lifetime, max_size, roomnum, objnum, force_blue);

  return objnum;
}
// TODO: MTS: only used in this file.
// Creates a standard blast ring for an object
int CreateObjectBlastRing(object *objp) {
  float ring_size = OBJECT_OUTSIDE(objp) ? (objp->size * 3) : objp->size;
  return CreateBlastRing(&objp->pos, BLAST_RING_INDEX, DAMAGE_RING_TIME, ring_size, objp->roomnum);
}
// TODO: MTS: Not used?
// Creates a smolding smoke to be drawn
int CreateSmolderingObject(vector *pos, int index, float lifetime, float max_size, int roomnum) {
  int objnum;
  vector new_pos = *pos;
  new_pos.y = GetTerrainGroundPoint(&new_pos);

  objnum = ObjCreate(OBJ_FIREBALL, index, roomnum, &new_pos, NULL);
  if (objnum < 0) {
    mprintf(0, "Couldn't create blast object!\n");
    return -1;
  }
  Objects[objnum].size = 1.0;
  Objects[objnum].flags |= OF_USES_LIFELEFT;
  Objects[objnum].lifeleft = lifetime;
  Objects[objnum].lifetime = lifetime;
  Objects[objnum].ctype.blast_info.max_size = max_size;
  return objnum;
}
// Draws a colored alpha disk...useful for cool lighting effects
void DrawColoredDisk(vector *pos, float r, float g, float b, float inner_alpha, float outer_alpha, float size,
                     uint8_t saturate, uint8_t lod) {
  rend_SetZBufferWriteMask(0);
  DrawColoredRing(pos, r, g, b, inner_alpha, outer_alpha, size, 0, saturate, lod);
  rend_SetZBufferWriteMask(1);
}
// TODO: MTS: Not used?
// Draws a glowing cone of light using a bitmap
void DrawColoredGlow(vector *pos, float r, float g, float b, float size) {
  rend_SetTextureType(TT_LINEAR);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);
  ddgr_color color = GR_RGB(r * 255, g * 255, b * 255);
  int bm_handle = Fireballs[GRADIENT_BALL_INDEX].bm_handle;
  g3_DrawBitmap(pos, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle, color);
}

// Draws a colored alpha ring...useful for cool lighting effects
void DrawColoredRing(vector *pos, float r, float g, float b, float inner_alpha, float outer_alpha, float size,
                     float inner_ring_ratio, uint8_t saturate, uint8_t lod) {
  static vector circleVecs[3][32];
  static int lodSegments[3] = {32, 16, 8};
  static bool firstCall = true;

  if (firstCall) {
    // initialize the circleVecs
    firstCall = false;
    int lodi;
    for (lodi = 0; lodi < 3; ++lodi) {
      int numSegments = lodSegments[lodi];
      int ringIncrement = 65536 / numSegments;
      int ringAngle = 0;
      int i;
      for (i = 0; i < numSegments; ++i, ringAngle += ringIncrement) {
        float ringSin = FixSin(ringAngle);
        float ringCos = FixCos(ringAngle);
        circleVecs[lodi][i].x = ringCos;
        circleVecs[lodi][i].y = ringSin;
        circleVecs[lodi][i].z = 0.0f;
      }
    }
  }

  // setup renderer
  rend_SetLighting(LS_GOURAUD);
  rend_SetTextureType(TT_FLAT);
  rend_SetOverlayType(OT_NONE);
  rend_SetColorModel(CM_RGB);
  rend_SetFlatColor(GR_RGB(r * 255, g * 255, b * 255));
  rend_SetAlphaType((saturate) ? AT_SATURATE_VERTEX : AT_VERTEX);

  // check LOD level
  ASSERT(lod >= 0 && lod <= 2);
  int i, numSegments = lodSegments[lod];

  // get the view matrix
  matrix viewOrient;
  g3_GetUnscaledMatrix(&viewOrient);
  viewOrient = ~viewOrient;

  // setup the points
  g3Point innerPoints[32], outerPoints[32];
  float innerRingSize = size * inner_ring_ratio;
  float outerRingSize = size;
  for (i = 0; i < numSegments; ++i) {
    vector worldSpaceCircleVec = circleVecs[lod][i] * viewOrient;
    vector innerPos = (*pos) + (worldSpaceCircleVec * innerRingSize);
    vector outerPos = (*pos) + (worldSpaceCircleVec * outerRingSize);

    g3_RotatePoint(&innerPoints[i], &innerPos);
    innerPoints[i].p3_flags |= PF_RGBA;
    innerPoints[i].p3_a = inner_alpha;
    innerPoints[i].p3_r = r;
    innerPoints[i].p3_g = g;
    innerPoints[i].p3_b = b;

    g3_RotatePoint(&outerPoints[i], &outerPos);
    outerPoints[i].p3_flags |= PF_RGBA;
    outerPoints[i].p3_a = outer_alpha;
    outerPoints[i].p3_r = r;
    outerPoints[i].p3_g = g;
    outerPoints[i].p3_b = b;
  }

  // and draw...
  g3Point *pntList[4];
  for (i = 0; i < numSegments; ++i) {
    int next = (i + 1) % numSegments;
    pntList[0] = &outerPoints[i];
    pntList[1] = &outerPoints[next];
    pntList[2] = &innerPoints[next];
    pntList[3] = &innerPoints[i];
    g3_DrawPoly(4, pntList, 0);
  }
}

// TODO: MTS: not used?
// Draws a sphere with the appropriate texture.  If texture=-1, then uses rgb as colors
void DrawSphere(vector *pos, float r, float g, float b, float alpha, float size, int texture, uint8_t saturate) {
  static vector sphere_vecs[16][16];
  static int first = 1;
  g3Point sphere_points[16][16], *pntlist[4], draw_points[4];
  int bm_handle = -1;
  ddgr_color color = GR_RGB(r * 255, g * 255, b * 255);

  int i, t;

  if (size < 0)
    return;
  if (first) {
    first = 0;
    // Create a unit sphere
    int increment = 65536 / 16;
    for (i = 0; i < 16; i++) {
      for (t = 0; t < 16; t++) {
        matrix tempm;
        angle pitch, heading;
        pitch = i * increment;
        heading = t * increment;

        vm_AnglesToMatrix(&tempm, pitch, heading, 0);
        sphere_vecs[i][t] = tempm.fvec;
      }
    }
  }
  rend_SetZBufferWriteMask(0);
  draw_points[0].p3_u = 0;
  draw_points[0].p3_v = 0;
  draw_points[1].p3_u = 1.0 + ((ps_rand() % 100) / 500.0);
  draw_points[1].p3_v = 0;
  draw_points[2].p3_u = 1.0 + ((ps_rand() % 100) / 500.0);
  draw_points[2].p3_v = 1.0 + ((ps_rand() % 100) / 500.0);
  draw_points[3].p3_u = 0;
  draw_points[3].p3_v = 1.0 + ((ps_rand() % 100) / 500.0);

  if (texture == -1) {
    rend_SetTextureType(TT_FLAT);
    rend_SetOverlayType(OT_NONE);
    rend_SetColorModel(CM_RGB);
    rend_SetLighting(LS_NONE);
    rend_SetFlatColor(color);
    rend_SetAlphaType(AT_CONSTANT);
    rend_SetAlphaValue(alpha * 255.0);
  } else {
    rend_SetTextureType(TT_LINEAR);
    rend_SetOverlayType(OT_NONE);
    rend_SetColorModel(CM_MONO);
    rend_SetLighting(LS_NONE);
    rend_SetAlphaType(AT_SATURATE_TEXTURE);
    rend_SetAlphaValue(alpha * 255.0);
    bm_handle = GetTextureBitmap(texture, 0);
  }

  for (i = 0; i < 16; i++) {
    for (t = 0; t < 16; t++) {
      vector temp_vec = *pos + (sphere_vecs[i][t] * size);
      g3_RotatePoint(&sphere_points[i][t], &temp_vec);
    }
  }
  for (i = 0; i < 16; i++) {
    int next_i = (i + 1) % 16;
    for (t = 0; t < 16; t++) {
      int next_t = (t + 1) % 16;
      draw_points[0] = sphere_points[i][t];
      draw_points[1] = sphere_points[i][next_t];
      draw_points[2] = sphere_points[next_i][next_t];
      draw_points[3] = sphere_points[next_i][t];

      for (int k = 0; k < 4; k++) {
        draw_points[k].p3_flags |= PF_UV | PF_RGBA;
        g3_CodePoint(&draw_points[k]);
        pntlist[k] = &draw_points[k];
      }
      g3_CheckAndDrawPoly(4, pntlist, bm_handle, NULL, &sphere_vecs[0][0]);
    }
  }
  rend_SetZBufferWriteMask(1);
}
#define BLAST_RING_ALPHA 1.0f
// TODO: MTS: only used in this file.
//  Draws a blast ring
void DrawBlastRingObject(object *obj) {
  vector inner_vecs[30], outer_vecs[30];
  g3Point inner_points[30], outer_points[30];
  float lifenorm = (obj->lifetime - obj->lifeleft) / obj->lifetime;
  float cur_size = lifenorm * obj->ctype.blast_info.max_size;
  int i;
  g3Point *pntlist[4];
  static int grav_first = 1;
  static int grav_texture;

  if (obj->id == GRAVITY_FIELD_INDEX)
    cur_size = (1 - lifenorm) * obj->ctype.blast_info.max_size;

  int bm_handle = obj->ctype.blast_info.bm_handle;
  int num_segments = 20;
  int ring_increment = 65536 / num_segments;
  int ring_angle = 0;

  if (lifenorm > 1.0)
    lifenorm = 1.0;
  // First draw a blast sphere
  float sphere_norm;
  int rot_angle;
  // Scale lifetime to make it look like a lensflare
  if (lifenorm < .1) {
    sphere_norm = lifenorm * 10;
    rot_angle = (FrameCount * 20) % 65536;
  } else {
    sphere_norm = 1.0 - ((lifenorm - .1) * 1.5);
    rot_angle = (FrameCount * 550) % 65536;
    if (sphere_norm < 0)
      sphere_norm = 0;
  }
  float sphere_alpha = sphere_norm;
  int disk_handle;
  float disk_size = sphere_norm * obj->ctype.blast_info.max_size;
  if (obj->id == GRAVITY_FIELD_INDEX) {
    rend_SetZBias(-(cur_size / 2));
    DrawColoredDisk(&obj->pos, .3f, .5f, 1, .9f, 0, disk_size, 1, 0);
    // Set states for the ring
    rend_SetOverlayType(OT_NONE);
    rend_SetLighting(LS_NONE);
    rend_SetTextureType(TT_LINEAR);
    rend_SetAlphaType(AT_SATURATE_TEXTURE);
    rend_SetAlphaValue(sphere_alpha * 255.0);
    rend_SetZBufferWriteMask(0);

  } else {
    disk_handle = Fireballs[SHRINKING_BLAST_INDEX].bm_handle;

    rend_SetOverlayType(OT_NONE);
    rend_SetLighting(LS_NONE);
    rend_SetTextureType(TT_LINEAR);
    rend_SetAlphaType(AT_SATURATE_TEXTURE);
    rend_SetAlphaValue(sphere_alpha * 255.0);
    rend_SetZBufferWriteMask(0);
    rend_SetZBias(-(cur_size / 2));
    if (sphere_norm >= 0.0)
      g3_DrawRotatedBitmap(&obj->pos, rot_angle, disk_size, (disk_size * bm_h(disk_handle, 0)) / bm_w(disk_handle, 0),
                           disk_handle);
  }
  // Now draw a blast ring
  if (lifenorm < .2) {
    lifenorm = lifenorm * 3;
  } else
    lifenorm = .6 + (((lifenorm - .2) / .8) * .4);
  if (lifenorm > 1)
    lifenorm = 1;

  rend_SetAlphaType(AT_SATURATE_TEXTURE_VERTEX);
  rend_SetAlphaValue(255);
  ring_angle = 0;
  cur_size *= 2;
  float alpha = 1.0;
  if (lifenorm > .5)
    alpha = 1.0 - ((lifenorm - .5) / .5);
  for (i = 0; i < num_segments; i++, ring_angle += ring_increment) {
    float ring_sin = FixSin(((int)(ring_angle + (lifenorm * 65536)) % 65536));
    float ring_cos = FixCos(((int)(ring_angle + (lifenorm * 65536)) % 65536));

    inner_vecs[i] = obj->orient.rvec * (ring_cos * cur_size * .50);
    inner_vecs[i] += obj->orient.fvec * (ring_sin * cur_size * .50);
    inner_vecs[i] += obj->pos;
    outer_vecs[i] = obj->orient.rvec * (ring_cos * cur_size);
    outer_vecs[i] += obj->orient.fvec * (ring_sin * cur_size);
    outer_vecs[i] += obj->pos;

    g3_RotatePoint(&inner_points[i], &inner_vecs[i]);
    g3_RotatePoint(&outer_points[i], &outer_vecs[i]);
    outer_points[i].p3_flags |= PF_UV | PF_RGBA;
    inner_points[i].p3_flags |= PF_UV | PF_RGBA;
    outer_points[i].p3_a = 1.0 - lifenorm;
    inner_points[i].p3_a = 0;
  }
  for (i = 0; i < num_segments; i++) {
    int next = (i + 1) % num_segments;
    outer_points[i].p3_u = 0;
    outer_points[next].p3_u = 1.0;
    outer_points[i].p3_v = 0;
    outer_points[next].p3_v = 0;
    inner_points[i].p3_u = 0;
    inner_points[next].p3_u = 1.0;
    inner_points[i].p3_v = 1;
    inner_points[next].p3_v = 1;
    pntlist[0] = &outer_points[i];
    pntlist[1] = &outer_points[next];
    pntlist[2] = &inner_points[next];
    pntlist[3] = &inner_points[i];
    g3_DrawPoly(4, pntlist, bm_handle);
  }
  rend_SetZBias(0);
  rend_SetZBufferWriteMask(1);
}

// Creates a blast ring
void DoBlastRingEvent(int eventnum, void *data) {
  object *obj = (object *)data;
  CreateObjectBlastRing(obj);
}
// TODO: MTS: only used in this file.
//  Creates an explosion
void DoExplosionEvent(int eventnum, void *data) {
  float *vals = (float *)data;
  vector pos;
  int fireball_num, roomnum;
  float size;
  float upwards_velocity;
  pos_state sound_pos;
  pos.x = vals[0];
  pos.y = vals[1];
  pos.z = vals[2];
  fireball_num = (int)vals[3];
  roomnum = (int)vals[4];
  size = vals[5];
  upwards_velocity = vals[6];
  int visnum = CreateFireball(&pos, fireball_num, roomnum, VISUAL_FIREBALL);
  if (visnum >= 0) {
    vector zero_vec = {0, 0, 0};
    matrix id_mat = Identity_matrix;

    sound_pos.position = &pos;
    sound_pos.roomnum = roomnum;
    sound_pos.orient = &id_mat;
    sound_pos.velocity = &zero_vec;

    if (ps_rand() > D3_RAND_MAX / 2)
      Sound_system.Play3dSound(SOUND_ROBOT_EXPLODE_1, SND_PRIORITY_HIGH, &sound_pos);
    else
      Sound_system.Play3dSound(SOUND_ROBOT_EXPLODE_2, SND_PRIORITY_HIGH, &sound_pos);
    VisEffects[visnum].size = size;
    if (upwards_velocity > .001) {
      VisEffects[visnum].movement_type = MT_PHYSICS;
      VisEffects[visnum].phys_flags = PF_FIXED_VELOCITY;
      VisEffects[visnum].velocity.x = 0;
      VisEffects[visnum].velocity.z = 0;
      VisEffects[visnum].velocity.y = upwards_velocity;
    }
  }
}
// An event handler that simply draws an alpha blended poly on top of the screen
// Takes a 4 element array of floats int r,g,b,a format
void DrawAlphaEvent(int eventnum, void *data) {
  float *vals = (float *)data;

  DrawAlphaBlendedScreen(vals[0], vals[1], vals[2], vals[3]);
}
// Returns a random explosion based on the explosion size
int GetRandomExplosion(float size) {
  if (size > EXTRA_EXPLOSION_THRESHOLD)
    return BIG_EXPLOSION_INDEX;
  else
    return GetRandomMediumExplosion();
}
// TODO: MTS: only found in this file.
// Returns a random medium sized explosion
int GetRandomMediumExplosion() {
  int choices[] = {MED_EXPLOSION_INDEX, MED_EXPLOSION_INDEX2, MED_EXPLOSION_INDEX3};
  int pick = ps_rand() % 3;
  return (choices[pick]);
}
int GetRandomSmallExplosion() {
  int choices[] = {SMALL_EXPLOSION_INDEX, SMALL_EXPLOSION_INDEX2};
  int pick = ps_rand() % 2;
  return (choices[pick]);
}
// TODO: MTS: only found in this file.
int GetRandomBillowingExplosion() {
  int choices[] = {BILLOWING_INDEX, MED_EXPLOSION_INDEX2};
  int pick = ps_rand() % 2;
  return (choices[pick]);
}
void DrawSmolderingObject(object *obj) {
  vector veca;
  angvec angs;
  vector world_verts[4];
  g3Point pnts[4], *pntlist[4];
  if (!Viewer_object)
    return;
  vm_ExtractAnglesFromMatrix(&angs, &Viewer_object->orient);
  veca.x = FixCos(angs.h);
  veca.z = FixSin(angs.h);
  veca.y = 0;
  world_verts[0] = obj->pos - (veca * 10);
  world_verts[1] = obj->pos + (veca * 10);
  world_verts[2] = obj->pos + (veca * 10);
  world_verts[3] = obj->pos - (veca * 10);
  world_verts[0].y += obj->ctype.blast_info.max_size;
  world_verts[1].y += obj->ctype.blast_info.max_size;
  for (int i = 0; i < 4; i++) {
    g3_RotatePoint(&pnts[i], &world_verts[i]);
    pnts[i].p3_flags |= PF_UV;
    pntlist[i] = &pnts[i];
  }
  pnts[0].p3_u = 0;
  pnts[0].p3_v = 0;
  pnts[1].p3_u = 1;
  pnts[1].p3_v = 0;
  pnts[2].p3_u = 1;
  pnts[2].p3_v = 1;
  pnts[3].p3_u = 0;
  pnts[3].p3_v = 1;
  rend_SetTextureType(TT_LINEAR);
  rend_SetLighting(LS_NONE);
  rend_SetOverlayType(OT_NONE);
  rend_SetAlphaType(AT_CONSTANT + AT_TEXTURE);
  rend_SetAlphaValue(.4 * 255);

  vclip *vc = &GameVClips[Fireballs[obj->id].bm_handle];
  int bm_handle = vc->frames[3];
  g3_DrawPoly(4, pntlist, bm_handle);
}
// Creates end points that simulate lightning
void CreateLightningRodPositions(vector *src, vector *dest, vector *world_vecs, int num_segments, float rand_mag,
                                 bool do_flat) {
  vector delta_vec = *dest - *src;
  matrix mat;

  // Setup some interpolants
  float mag = vm_GetMagnitudeFast(&delta_vec);
  float delta_dist = mag / num_segments;
  delta_vec /= mag;
  // Create matrix for randomization
  vm_VectorToMatrix(&mat, &delta_vec, NULL, NULL);

  vector cur_pos = *src;

  vector from = cur_pos;
  world_vecs[0] = from;
  world_vecs[num_segments - 1] = *dest;
  // Create the points
  for (int i = 1; i < num_segments - 1; i++, cur_pos += (delta_vec * delta_dist)) {
    vector to = cur_pos + (delta_vec * delta_dist);
    // vector to=world_vecs[i-1]+(delta_vec*delta_dist);
    to += mat.rvec * ((((ps_rand() % 200) - 100) / 100.0) * rand_mag);
    if (!do_flat)
      to += mat.uvec * ((((ps_rand() % 200) - 100) / 100.0) * rand_mag);
    ASSERT(i < 50);

    world_vecs[i] = to;
  }
}
