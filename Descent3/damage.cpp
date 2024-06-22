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

 * $Logfile: /DescentIII/main/damage.cpp $
 * $Revision: 164 $
 * $Date: 3/22/00 12:13p $
 * $Author: Matt $
 *
 *	Applies and handles damage to game entities.
 *
 * $Log: /DescentIII/main/damage.cpp $
 *
 * 164   3/22/00 12:13p Matt
 * Added some if statements to not damage & kill objects when playing back
 * a demo.
 *
 * 163   1/26/00 9:19p Jeff
 * added support for IntelliVIBE DLL
 *
 * 162   10/21/99 2:44p Matt
 * Mac merge
 *
 * 161   10/08/99 4:54p Nate
 * Fixed bug that prevented custom damage modification from working
 *
 * 160   10/08/99 4:28p Chris
 * Added the forcefield and glass breaking override options
 *
 * 159   9/22/99 11:58a Jeff
 * always call the multiplayer event when player shields change and then
 * check to see if the player should be killed
 *
 * 158   7/26/99 11:07a Jason
 * fixed broke glass bug
 *
 * 157   5/22/99 10:27p Jason
 * changes for multiplayer and buildings, ai
 *
 * 156   5/21/99 4:30a Matt
 * Added commented-out code to play sound for sparking death, in case we
 * ever get  a  sound we like.
 *
 * 155   5/17/99 9:23p Matt
 * When applying damage to player, only play invulnerability sound if
 * would otherwise be playing a sound.
 *
 * 154   5/09/99 10:50p Jason
 * made napalm rocket burn people longer
 *
 * 153   5/04/99 6:53p Jeff
 * added event for when a player dies
 *
 * 152   4/30/99 2:32p Matt
 * Doubled the velocity of straight-up flying deaths to make Josh's pop
 * machines cooler.
 *
 * 151   4/30/99 3:28a Chris
 * Flares disappear when they hit bad surfaces (volatile and lava)
 *
 * 150   4/29/99 6:48p Matt
 * Made volatile surfaces apply damage and lava surfaces catch the player
 * on fire.  Both now generate the steam puff effect.
 *
 * 149   4/28/99 4:48a Chris
 * Added the no-scale damage by diff checkbox
 *
 * 148   4/27/99 12:12a Matt
 * Added option to make object not tumble in flying death
 *
 * 147   4/26/99 7:07p Jason
 * fixed multiplayer bug with destroy object
 *
 * 146   4/26/99 6:23p Jeff
 * don't apply damage to OBJ_DUMMYs! (It cause problems in multiplayer
 * with the guidebot)
 *
 * 145   4/25/99 10:38p Matt
 * Made the Osiris kill object function work on players.
 *
 * 144   4/25/99 10:19p Matt
 * Fixed multiplayer and demo problems will killing an object from script,
 * and cleaned up the death code a bit in the process.
 *
 * 143   4/24/99 11:38p Matt
 * Set the death delay for electrical deaths on default-death objects.
 * This has apparently been broken since I rewrote the death system ages
 * ago, but no one reported it.
 *
 * 142   4/24/99 4:32p Jason
 * made fusion damage sound not be irritating
 *
 * 141   4/23/99 12:32a Matt
 * Added a death info option to play the explosion sound at the start of
 * the delay, instead of at the end when the object actually dies.
 *
 * 140   4/22/99 4:15p Matt
 * Don't bash the delay time when setting the flying physics for dying
 * objects.  For default deaths, this was already set to the same values
 * when setting up the death, and for explicit deaths, use the value from
 * the page.
 *
 * 139   4/21/99 3:01p Matt
 * Added a new type for dying objects that have AI, instead of keeping a
 * flag in the dying info.
 *
 * 138   4/21/99 12:40p Jason
 * made explosion system framerate independant
 *
 * 137   4/21/99 12:22p Matt
 * Added extra time to delay-from-anim time to allow object to finish its
 * current anim before starting the death anim.
 *
 * 136   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 135   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 134   4/12/99 6:15p Samir
 * Sound priorities pass 1
 *
 * 133   4/10/99 6:32p Matt
 * Don't allow glass to be broken twice.
 *
 * 132   4/06/99 6:24p Jason
 * various fixes for multiplayer
 *
 * 131   4/06/99 6:02p Matt
 * Added score system
 *
 * 130   4/02/99 11:23a Matt
 * Made KillObject not take a death_info struct, but rather the death info
 * as individual parameters.  Moved death_info into objinfo.h, since it's
 * only used for generic objects.  Took out fade-away death hack, now that
 * fade-away deaths can be explicitely set.
 *
 * 129   4/01/99 4:28p Matt
 * Cleaned up handling of dying flag to prevent infinite recursion.  Jeff
 * will test.
 *
 * 128   3/29/99 11:20a Matt
 * Added more flexibility to death delays, and added fade away deaths.
 *
 * 127   3/22/99 1:47p Matt
 * Moved breaking glass code from collide.cpp to damage.cpp
 *
 * 126   3/08/99 5:10p Chris
 * Make upsidedown robots fall faster (use the loss anti-grav flag)
 *
 * 125   3/05/99 6:41p Matt
 * In default death, instead of adding 3 second to delay time, calculate
 * the time remaining the robot's current animation and add that.
 *
 * 124   3/05/99 3:32p Matt
 * Added hack for making nomads fade out
 *
 * 123   3/05/99 11:30a Kevin
 * Fixed really stupid bug
 *
 * 122   3/03/99 5:41p Matt
 * Don't scale applied damage if damage type is GD_SCRIPTED
 *
 * 121   2/28/99 6:20p Matt
 * Added the ability to set death types for generic objects.
 *
 * 120   2/26/99 2:03p Matt
 * Got blastable doors working, and cleaned up concussive force code.
 *
 * 119   2/25/99 10:58a Matt
 * Added new explosion system.
 *
 * 118   2/22/99 2:03p Jason
 * added different damages for players and generics
 *
 * 117   2/13/99 6:16p Jeff
 * fixed ApplyDamageTo functions so they only damage what objects they are
 * supposed to
 *
 * 116   2/13/99 12:29a Jeff
 * don't apply damage to OBJ_DUMMYs
 *
 * 115   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 114   2/08/99 5:17p Jason
 * took out EMD effect and added more weapon options
 *
 * 113   2/07/99 1:19a Jeff
 * added new multiplayer game events EVT_GAMEOBJKILLED and
 * EVT_GAMEOBJDESTROYED
 *
 * 112   2/04/99 2:05p Matt
 * Added blastable doors
 *
 * 111   2/04/99 11:36a Jason
 * fixed some multi bugs
 *
 * 110   2/03/99 12:15p Jason
 * added multiplayer vis optimizations
 *
 * 109   2/02/99 8:43a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 108   2/01/99 4:25p Jeff
 * fixed player invulnerabilty after cinematic sequence and death bug
 *
 * 107   2/01/99 12:55p Jeff
 * don't damage player if OF_DESTROYABLE is not set
 *
 * 106   1/28/99 12:09p Jeff
 * added force feedback to player shake...fixed spelling error in define
 * for forcefeedback
 *
 * 105   1/20/99 12:31p Chris
 * Include the weapon_handle in evt_damage
 *
 * 104   1/20/99 2:13a Chris
 * It is now possible for robots to have special immunities, resistances,
 * and vunerabilities
 *
 * 103   1/18/99 2:46p Matt
 * Combined flags & flags2 fields in object struct
 *
 * 102   1/17/99 7:20p Jeff
 * doh! put back in call to multiplayer event on object damage
 *
 * 101   1/15/99 3:49a Jeff
 * removed calls to multiplayer dll events (EVT_DAMAGED)
 *
 * 100   1/13/99 2:42p Jason
 * added damage event
 *
 * 99    1/13/99 2:28a Chris
 * Massive AI, OSIRIS update
 *
 * 98    1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 97    1/06/99 3:07p Jason
 * toned down redness
 *
 * 96    12/13/98 7:47p Chris
 * Make walkers die slowly more often
 *
 * 95    12/07/98 2:26p Jason
 * fixed a bug with peer to peer damage on the client end
 *
 * 94    12/04/98 3:03p Jason
 *
 * 93    12/04/98 1:41p Jason
 * made napalm do even less damage
 *
 * 92    12/03/98 3:39p Jason
 * added peer 2 peer style damage
 *
 * 91    12/02/98 10:30a Jason
 * added additional damage types for client-side multiplayer
 *
 * 90    12/01/98 10:57a Jason
 * fixed compiler warning
 *
 * 89    11/19/98 5:40p Kevin
 * Demo system
 *
 * 88    11/19/98 12:22p Jason
 * optimizations
 *
 * 87    11/13/98 2:25p Samir
 * modify game music info when damaged or killed robot
 *
 * 86    11/13/98 12:29p Jason
 * changes for weapons
 *
 * 85    11/11/98 2:46p Kevin
 * Demo recording system work
 *
 * 84    11/11/98 11:41a Jason
 * added sunlight damage
 *
 * 83    11/10/98 3:12p Chris
 * Got rid of a const double to float warning
 *
 * 82    10/30/98 4:24p Jason
 * changes for multiplayer
 *
 * 81    10/22/98 2:58p Chris
 * Difficulty levels are in beta
 *
 * 80    10/22/98 10:50a Samir
 * only register kill for robots so accuracy rating can be closer.
 *
 * 79    10/19/98 7:17p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 78    10/14/98 1:02p Jason
 * fixed FindSoundName issues
 *
 * 77    10/06/98 11:27a Jason
 * added new death type for robots
 *
 * 76    9/30/98 5:35p Jason
 * added multiplayer menu bailing for samir
 *
 * 75    9/25/98 5:02p Jason
 * fixed parenting problems
 *
 * 74    9/17/98 6:08p Jason
 * more tweaks for effects
 *
 * 73    9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 72    9/14/98 4:17p Jason
 * added friendly fire damage
 *
 * 71    8/14/98 6:26p Kevin
 * for chris: dealt with killer==NULL in ExplodeObject
 *
 * 70    8/14/98 4:58p Jeff
 * only if damage>0 does it play sound
 *
 * 69    8/14/98 12:49p Chris
 * Working on attach system
 *
 * 68    8/12/98 12:04p Chris
 * Attach system version .5 (still needs more work to be multiplayer
 * friendly)
 *
 * 67    8/10/98 5:24p Jason
 * made robots have a little variation when dying
 *
 * 66    8/03/98 5:56p Jason
 * got fusion cannon working correctly
 *
 * 65    7/31/98 5:23p Jason
 * added ship armor scalars
 *
 * 64    7/30/98 11:09a Jason
 * added weapons that freeze and deform terrain
 *
 * 63    7/21/98 12:13p Jason
 * Told DLL about which weapon was used to kill a player
 *
 * 62    7/15/98 2:33p Jason
 * added scalar variables for various player skills
 *
 * 61    7/15/98 12:48p Jeff
 * put in calls to handle new multiplayer event...when an object's shields
 * change
 *
 * 60    6/30/98 11:39a Jason
 * added AdditionalDamage packet type for multiplayer
 *
 * 59    6/29/98 12:12p Kevin
 * Added robot damage and death packets
 *
 * 58    6/26/98 7:26p Jason
 * checked in so kevin can work on coop
 *
 * 57    6/26/98 2:14p Jason
 * fixed InitiatePlayerDeath bug with dead robots
 *
 * 56    6/02/98 6:04p Jason
 * undid pre-e3 invul change
 *
 * 55    5/25/98 6:38p Matt
 * Added needed include.
 *
 * 54    5/25/98 4:16p Jason
 * made invulnerability different for E3 demo
 *
 * 53    5/22/98 6:22p Chris
 * Improved Dynamic path allocation
 *
 * 52    5/19/98 2:41a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 51    5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 50    5/04/98 12:55p Jason
 * fixed NULL pointer bug
 *
 * 49    5/01/98 6:50p Samir
 * call initiate player death with melee if killed by robot.
 *
 * 48    5/01/98 3:41p Chris
 *
 * 47    5/31/98 3:07p Chris
 * Robots die slowly more often.  Made robots die slowly when the killer
 * object is a
 * player or robot.  (Melee attacks and bumping damage deaths)
 *
 * 46    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 45    4/17/98 3:57p Jason
 * added microwave effect
 *
 * 44    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 43    4/10/98 3:28p Jason
 * Turn off guided missile when you get hit
 *
 * 42    4/09/98 5:17p Jason
 * got guided working in multiplayer
 *
 * 41    4/06/98 4:05p Jason
 * made suicides work correctly
 *
 * 40    4/06/98 2:54p Jason
 * yet more multiplayer changes
 *
 * 39    4/06/98 12:14p Jason
 * changes to multiplayer
 *
 * 38    3/31/98 12:16p Jason
 * some small changes for explosions
 *
 * 37    3/30/98 5:11p Jason
 * more changes for game/dll integration
 *
 * 36    3/23/98 4:51p Jason
 * incremental checkin for multiplay
 *
 * 35    3/23/98 4:36p Jason
 * make powerups non-destroyable in multiplay
 *
 * 34    3/12/98 7:30p Chris
 * Added ObjSetOrient
 *
 * 33    2/25/98 4:31p Jason
 * changes for explosions
 *
 * 32    2/18/98 4:12a Jason
 * took out ridiculous explosions
 *
 * 31    2/16/98 11:19p Chris
 * Added support for melee robots
 *
 * 30    2/16/98 4:55p Chris
 * Added default sounds for explosions
 *
 * 29    2/10/98 11:32a Samir
 * Added D3X support when a player gets killed to the gamemode script.
 *
 * 28    2/09/98 5:38p Jeff
 * changed EVT_PLAYERKILLED to EVT_GAMEPLAYERKILLED for osiris
 *
 * 27    2/05/98 2:54p Jason
 * changes for explosions
 *
 * 26    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 25    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 24    2/03/98 4:04p Jeff
 * added OSIRIS events for player killed and exploded
 *
 * 23    1/28/98 1:11p Jason
 * took shields field out of Player struct
 *
 * 22    1/28/98 12:00p Jason
 * more changes for multiplayer
 *
 * 21    1/21/98 6:09p Jason
 * Got player deaths working in multiplayer
 *
 * 20    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 19    1/20/98 6:01p Jason
 * first pass at getting multiplayer deaths working
 *
 * 18    1/19/98 6:23p Chris
 * Fixed a crash when the killer is no longer alive.
 *
 * 17    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 16    1/15/98 6:49p Jason
 * incremental checkin for multiplayer
 *
 * 15    1/05/98 3:54p Chris
 * Added ambient and explosion sounds
 *
 * 14    1/05/98 11:02a Jason
 * made shake magnitude proportional to the distance from the explosion
 *
 *
 * 13    12/12/97 6:13p Jason
 * added sparks
 *
 * 12    12/08/97 5:21p Jason
 * added code for destroyable buildings that leave their base object
 * around
 *
 * 11    12/08/97 3:28p Jason
 * tweaked explosions
 *
 * 10    12/03/97 5:53p Jason
 * worked on cooler explosion effects
 *
 * 9     12/01/97 11:02a Jason
 * made camera shake from explosions
 *
 * 8     12/01/97 9:50a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 7     11/18/97 4:37p Jason
 * added visible damage system
 *
 * 6     11/04/97 5:50p Jason
 * made #define for strange number (.6)
 *
 * 5     10/24/97 2:47p Jason
 * added blast rings to robots
 *
 * 4     10/20/97 4:46p Jason
 * changes for explosions
 *
 * 3     10/08/97 6:35p Samir
 * Dying player ships get marked as destroyed.  When death sequence is
 * over, they are marked as dead.   This is needed to better control
 * movement of the dying ship.
 *
 * 2     10/03/97 11:58a Samir
 * Added mission name
 *
 * 1     10/01/97 4:50p Samir
 * Damage for players and robots.
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <memory.h>
#include "damage.h"
#include "object.h"
#include "objinfo.h"
#include "player.h"
#include "fireball.h"
#include "gameevent.h"
#include "hlsoundlib.h"
#include "multi.h"
#include "game.h"
#include "sounds.h"
#include "soundload.h"
#include "game2dll.h"
#include "weapon.h"
#include "ship.h"
#include "attach.h"
#include "difficulty.h"
#include "demofile.h"
#include "musicapi.h"
#include "osiris_dll.h"
#include "D3ForceFeedback.h"
#include "multi_server.h"
#include "doorway.h"
#include "DeathInfo.h"
#include "AIGoal.h"
#include "viseffect.h"
#include "psrand.h"
#include "vibeinterface.h"

#include <algorithm>

static void SetDeformDamageEffect(object *obj);
static void ApplyFreezeDamageEffect(object *obj);
static void DecreasePlayerShields(int slot, float damage);
static void DoEDrainEffect(int eventnum, void *data);
static void PlayPlayerDamageSound(object *playerobj, int damage_type);
static void GenerateDefaultDeath(object *obj, int *death_flags, float *delay_time);
static void PlayPlayerInvulnerabilitySound(object *playerobj);
static void SetFlyingPhysics(object *objp, bool tumbles);
static float GetDeathAnimTime(object *objp);
static void SetFallingPhysics(object *objp);

// Shake variables
static matrix Old_player_orient;
float Shake_magnitude = 0.0;

// Causes an object to deform
void SetDeformDamageEffect(object *obj) {
  if (obj->effect_info) {
    obj->effect_info->type_flags |= EF_DEFORM;
    obj->effect_info->deform_time = 1.0;
    obj->effect_info->deform_range = .3f;
  }
}

#define MAX_NAPALM_DAMAGE_TIME 10.0f
// Causes an object to have napalm attached to it
void SetNapalmDamageEffect(object *obj, object *killer, int weapon_id) {
  if (obj->effect_info) {
    obj->effect_info->type_flags |= EF_NAPALMED;

    if (Weapons[weapon_id].flags & WF_INVISIBLE)
      obj->effect_info->damage_time += (MAX_NAPALM_DAMAGE_TIME / 5.0f);
    else
      obj->effect_info->damage_time += (MAX_NAPALM_DAMAGE_TIME / 1.5f);

    obj->effect_info->damage_time = std::min(MAX_NAPALM_DAMAGE_TIME, obj->effect_info->damage_time);

    if (obj->type == OBJ_PLAYER)
      obj->effect_info->damage_per_second = Weapons[weapon_id].player_damage;
    else
      obj->effect_info->damage_per_second = Weapons[weapon_id].generic_damage;

    if (Gametime - obj->effect_info->last_damage_time > 1.0f)
      obj->effect_info->last_damage_time = 0;

    if (killer != NULL)
      obj->effect_info->damage_handle = killer->handle;
    else
      obj->effect_info->damage_handle = OBJECT_HANDLE_NONE;

    if (obj->effect_info->sound_handle == SOUND_NONE_INDEX)
      obj->effect_info->sound_handle = Sound_system.Play3dSound(SOUND_PLAYER_BURNING, SND_PRIORITY_HIGHEST, obj);
  }
}

// Causes an object to have napalm attached to it
void ApplyFreezeDamageEffect(object *obj) {
  if (obj->effect_info) {
    if (!(obj->effect_info->type_flags & EF_FREEZE))
      obj->effect_info->freeze_scalar = 1.0;

    obj->effect_info->type_flags |= EF_FREEZE;
    obj->effect_info->freeze_scalar -= .2f;

    if (obj->effect_info->freeze_scalar < .3)
      obj->effect_info->freeze_scalar = .3f;
  }
}

// Event to handle damage effect
void DoDamageEffect(int eventnum, void *data) {
  float damage_norm = Players[Player_num].damage_magnitude / MAX_DAMAGE_MAG;

  if (damage_norm > 1.0)
    damage_norm = 1.0;

  DrawAlphaBlendedScreen(1.0, 0, 0, .4 * damage_norm);

  // If we're all done, just stop.  Else, make another event!
  if (Players[Player_num].damage_magnitude < .0001f)
    Players[Player_num].damage_magnitude = 0.0;
  else
    CreateNewEvent(RENDER_EVENT, DAMAGE_EFFECT, 0, NULL, 0, DoDamageEffect);
}

// Decreases a players shields
void DecreasePlayerShields(int slot, float damage) {
  object *playerobj = &Objects[Players[slot].objnum];
  playerobj->shields -= damage;
  Players[slot].damage_magnitude += damage;

  if (slot == Player_num) {
    if ((FindEventID(DAMAGE_EFFECT)) == -1)
      CreateNewEvent(RENDER_EVENT, DAMAGE_EFFECT, 0, NULL, 0, DoDamageEffect);

    if (Game_mode & GM_MULTI)
      Multi_bail_ui_menu = true;

    Game_music_info.player_damaged = true;

    // update IntelliVIBE
    if (damage > 0) {
      VIBE_DoPlayerDamage(damage);
    }
  }
}

// Event to handle damage effect
void DoEDrainEffect(int eventnum, void *data) {
  float edrain_norm = Players[Player_num].edrain_magnitude / MAX_EDRAIN_MAG;

  if (edrain_norm > 1.0)
    edrain_norm = 1.0;

  DrawAlphaBlendedScreen(0, 0, 1.0, .6 * edrain_norm);

  // If we're all done, just stop.  Else, make another event!
  if (Players[Player_num].edrain_magnitude < .0001f)
    Players[Player_num].edrain_magnitude = 0.0;
  else
    CreateNewEvent(RENDER_EVENT, EDRAIN_EFFECT, 0, NULL, 0, DoEDrainEffect);
}

// Decreases a players shields
void DecreasePlayerEnergy(int slot, float energy) {
  Players[slot].energy -= energy;
  Players[slot].edrain_magnitude += energy;

  if (slot == Player_num) {
    if ((FindEventID(EDRAIN_EFFECT)) == -1)
      CreateNewEvent(RENDER_EVENT, EDRAIN_EFFECT, 0, NULL, 0, DoEDrainEffect);
  }
}

// Plays the sound for a player being damaged
void PlayPlayerDamageSound(object *playerobj, int damage_type) {
  int sound_handle;

  switch (damage_type) {
  case PD_ENERGY_WEAPON:
    sound_handle = SOUND_HIT_BY_ENERGY_WEAPON;
    break;
  case PD_MATTER_WEAPON:
    sound_handle = SOUND_HIT_BY_MATTER_WEAPON;
    break;
  case PD_CONCUSSIVE_FORCE:
    sound_handle = SOUND_HIT_BY_CONCUSSIVE_FORCE;
    break;
  case PD_WALL_HIT:
    sound_handle = SOUND_PLAYER_HIT_WALL;
    break;
  case PD_VOLATILE_HISS:
    sound_handle = SOUND_VOLATILE_HISS;
    break;

  default:
    Int3();
  case PD_MELEE_ATTACK: // melee sounds handled in aimain.cpp for now
  case PD_NONE:
    return;
  }

  Sound_system.Play3dSound(sound_handle, SND_PRIORITY_HIGHEST, playerobj);
}

// Plays the sound for a player being damaged
void PlayPlayerInvulnerabilitySound(object *playerobj) {
  Sound_system.Play3dSound(SOUND_METALLIC_DOOR_HIT, SND_PRIORITY_HIGHEST, playerobj);
}

// Kills the player
// weapon_id can be -1 for no weapon
void KillPlayer(object *playerobj, object *killer, float damage_amount, int weapon_id) {
  // tell IntelliVIBE that the player is dying
  if (playerobj->id == Player_num) {
    VIBE_PlayerDeath();
  }

  // Save the killer
  Players[playerobj->id].killer_objnum = killer ? OBJNUM(killer) : 0;

  // Set some stuff
  Players[playerobj->id].damage_magnitude = 0;
  Players[playerobj->id].edrain_magnitude = 0;

  tOSIRISEventInfo ei;
  ei.evt_player_dies.it_handle = playerobj->handle;
  Osiris_CallLevelEvent(EVT_PLAYER_DIES, &ei);

  // If single-player, record & initiate death
  if (!(Game_mode & GM_MULTI)) {

    if (Demo_flags == DF_RECORDING)
      DemoWritePlayerDeath(playerobj, (killer && IS_ROBOT(killer)));

    if (Demo_flags != DF_PLAYBACK)
      InitiatePlayerDeath(playerobj, (killer && IS_ROBOT(killer)));
  } else if (Netgame.local_role == LR_SERVER) { // Multiplayer & server

    // Call DLL stuff
    DLLInfo.me_handle = playerobj->handle;

    if (killer != NULL)
      DLLInfo.it_handle = killer->handle;
    else
      DLLInfo.it_handle = OBJECT_HANDLE_NONE;

    DLLInfo.iParam = weapon_id;

    CallGameDLL(EVT_GAMEPLAYERKILLED, &DLLInfo);

    // pick a fate for this guy
    int fate = PlayerChooseDeathFate(playerobj->id, damage_amount, false);

    // Send it to everyone
    MultiSendPlayerDead(playerobj->id, fate);

    // Figure out new rankings
    GetNewRankings(playerobj, killer);
  }
}

//	Applies damage to a player object, returns false if damage wasn't applied due to things like
//	invunerability
bool ApplyDamageToPlayer(object *playerobj, object *killer, int damage_type, float damage_amount, int server_says,
                         int weapon_id, bool playsound) {
  if (!playerobj || playerobj->type != OBJ_PLAYER) {
    // bail it's not a player (no damage should be applied to ghosts or observer's either
    return false;
  }

  //	apply damage to the current player!
  object *weapon_obj = NULL;

  if (killer != NULL && killer->type == OBJ_WEAPON) {
    weapon_obj = killer;
    killer = ObjGetUltimateParent(killer);

    if (!(Game_mode & GM_MULTI) || ((Game_mode & GM_MULTI) && Netgame.local_role == LR_SERVER))
      weapon_id = weapon_obj->id;
    if ((Game_mode & GM_MULTI) && Netgame.local_role == LR_CLIENT && !server_says && (Netgame.flags & NF_PEER_PEER))
      weapon_id = weapon_obj->id;
  }

  if ((Players[playerobj->id].flags & PLAYER_FLAGS_DYING) || (Players[playerobj->id].flags & PLAYER_FLAGS_DEAD)) {
    PlayPlayerDamageSound(playerobj, damage_type);
    return false;
  }

  if ((Players[playerobj->id].flags & PLAYER_FLAGS_INVULNERABLE) || ((Player_object->flags & OF_DESTROYABLE) == 0)) {
    if (damage_type != PD_NONE)
      PlayPlayerInvulnerabilitySound(playerobj);

    if (weapon_obj != NULL) {
      Players[playerobj->id].invul_magnitude = 1;
      Players[playerobj->id].invul_vector = weapon_obj->pos - playerobj->pos;
      vm_NormalizeVectorFast(&Players[playerobj->id].invul_vector);
    }
    return false;
  } else {
    if (!(Game_mode & GM_MULTI)) {
      damage_amount *= Players[playerobj->id].armor_scalar;
      damage_amount *= Ships[Players[playerobj->id].ship_index].armor_scalar;

      DecreasePlayerShields(playerobj->id, damage_amount);

      if (damage_amount > 0 && playsound)
        PlayPlayerDamageSound(playerobj, damage_type);

      if (Players[playerobj->id].guided_obj != NULL)
        ReleaseGuidedMissile(playerobj->id);

      if (Players[playerobj->id].user_timeout_obj != NULL)
        ReleaseUserTimeoutMissile(playerobj->id);

      if (weapon_id != 255) {
        if (Weapons[weapon_id].flags & WF_MICROWAVE)
          SetDeformDamageEffect(playerobj);
        if (Weapons[weapon_id].flags & WF_FREEZE)
          ApplyFreezeDamageEffect(playerobj);
        if (Weapons[weapon_id].flags & WF_NAPALM)
          SetNapalmDamageEffect(playerobj, killer, weapon_id);
      }

      if (playerobj->shields < 0) {
        KillPlayer(playerobj, killer, damage_amount, weapon_id);
      }
    } else {
      // If this is a peer to peer game, and its me taking damage, then ask the server to damage me!
      if (Netgame.local_role == LR_CLIENT && (Netgame.flags & NF_PEER_PEER) && !server_says) {
        if (playerobj->id == Player_num) {
          MultiSendRequestPeerDamage(killer, weapon_id, damage_type, damage_amount);
          return true;
        }
      }

      if ((Netgame.flags & NF_PEER_PEER) && Netgame.local_role == LR_SERVER && !server_says) {
        if (playerobj->id != Player_num)
          return true;
      }

      if (Netgame.local_role == LR_SERVER || server_says) {
        if (Netgame.local_role == LR_SERVER) {
          // Check to see if we're on the same team
          if (killer != NULL && killer->type == OBJ_PLAYER) {
            if (killer->id != playerobj->id) {
              if (Players[killer->id].team == Players[playerobj->id].team && !(Netgame.flags & NF_DAMAGE_FRIENDLY))
                return false; // don't hurt players on your own team
            }

            damage_amount *= Players[killer->id].damage_scalar;
          }

          damage_amount *= Players[playerobj->id].armor_scalar;
          damage_amount *= Ships[Players[playerobj->id].ship_index].armor_scalar;
        }

        DecreasePlayerShields(playerobj->id, damage_amount);
        if (damage_amount > 0 && playsound)
          PlayPlayerDamageSound(playerobj, damage_type);
        if (playerobj->id == Player_num && Players[playerobj->id].guided_obj != NULL)
          ReleaseGuidedMissile(playerobj->id);

        if (playerobj->id == Player_num && Players[playerobj->id].user_timeout_obj != NULL)
          ReleaseUserTimeoutMissile(playerobj->id);

        if (weapon_id != 255) {
          if (Weapons[weapon_id].flags & WF_MICROWAVE)
            SetDeformDamageEffect(playerobj);
          if (Weapons[weapon_id].flags & WF_NAPALM)
            SetNapalmDamageEffect(playerobj, killer, weapon_id);
          if (Weapons[weapon_id].flags & WF_FREEZE)
            ApplyFreezeDamageEffect(playerobj);
        }

        // Tell others about this tragic event
        if (Netgame.local_role == LR_SERVER) {
          if (weapon_id != 255) {
            // If this is an electrical weapon then we should special case the damage
            if (Weapons[weapon_id].flags & WF_ELECTRICAL) {
              Multi_additional_damage[playerobj->id] += damage_amount;
              Multi_additional_damage_type[playerobj->id] = PD_ENERGY_WEAPON;
            } else
              MultiSendDamagePlayer(playerobj->id, weapon_id, damage_type, damage_amount);
          } else {
            if (weapon_obj != NULL)
              MultiSendDamagePlayer(playerobj->id, 255, damage_type, damage_amount);
            else {
              Multi_additional_damage[playerobj->id] += damage_amount;
              Multi_additional_damage_type[playerobj->id] = damage_type;
            }
          }
        }
      }

      if (Netgame.local_role == LR_SERVER) {
        // Call DLL stuff
        DLLInfo.me_handle = playerobj->handle;
        if (killer != NULL)
          DLLInfo.it_handle = killer->handle;
        else
          DLLInfo.it_handle = OBJECT_HANDLE_NONE;
        DLLInfo.fParam = damage_amount;
        CallGameDLL(EVT_GAMEOBJECTSHIELDSCHANGED, &DLLInfo);

        if (playerobj->shields < 0) {
          KillPlayer(playerobj, killer, damage_amount, weapon_id);
        }
      }
    }
  }

  return true;
}

// Fills in death info to roughly appoximate the deaths from the old explosion system
void GenerateDefaultDeath(object *obj, int *death_flags, float *delay_time) {
  // Set some defaults
  *death_flags = 0;
  *delay_time = 0.0;

  if ((obj->type != OBJ_ROBOT && !(obj->type == OBJ_BUILDING && obj->ai_info)) ||
      (obj->movement_type != MT_WALKING && ((ps_rand() % 3) != 0)) ||
      (obj->movement_type == MT_WALKING && ((ps_rand() % 10) > 5))) {

    // Quick death
    *death_flags = 0;
    *delay_time = 0.0;

    // Maybe set blast ring
    if ((ps_rand() % 3) == 0)
      *death_flags |= DF_BLAST_RING;
  } else { // slow death

    int alternate_death = 0;
    bool f_upsidedown_walker = (obj->movement_type == MT_WALKING) && (obj->orient.uvec.y < 0.0f);

    if (!f_upsidedown_walker && (ps_rand() % 2) == 1) {
      *death_flags = DF_DELAY_SPARKS;
      alternate_death = 1;
    }

    if (obj->type == OBJ_ROBOT || (obj->type == OBJ_BUILDING && obj->ai_info)) {
      if (alternate_death || (obj->movement_type != MT_PHYSICS && obj->movement_type != MT_WALKING) ||
          (obj->movement_type == MT_WALKING && !f_upsidedown_walker)) {
        *death_flags = DF_DELAY_SPARKS;
        *delay_time = 3.0f;
        alternate_death = 1;
      } else {
        if (obj->movement_type != MT_WALKING)
          *death_flags = 0;
        else
          *death_flags = DF_DELAY_LOSES_ANTIGRAV;
      }

      // Alternate death must last 3 seconds to correspond with sound effect
      // If you change this assumption, tell Jerry
      if (!alternate_death && Object_info[obj->id].anim) {
        if (obj->control_type == CT_AI &&
            Object_info[obj->id].anim[obj->ai_info->movement_type].elem[AS_DEATH].to != 0.0f) {
          // compute time remaining in current animation
          float extra_time = obj->rtype.pobj_info.anim_time *
                             (obj->rtype.pobj_info.anim_end_frame - obj->rtype.pobj_info.anim_frame) /
                             (obj->rtype.pobj_info.anim_end_frame - obj->rtype.pobj_info.anim_start_frame);
          extra_time = std::min<float>(extra_time, 3.0); // limit extra time to 3 seconds
          *delay_time = Object_info[obj->id].anim[obj->ai_info->movement_type].elem[AS_DEATH].spc + 0.25 + extra_time;
          // Walkers last a little longer
          if (obj->movement_type == MT_WALKING)
            *delay_time += 2.0f;
        } else
          *delay_time = 2.0f;
      }
    } else { // If building, make it shoot up
      *death_flags |= DF_DELAY_FLYING;
      if (obj->orient.uvec.y == 1.0f)
        *delay_time = 2.0f;
      else
        *delay_time = 0.7f;
    }

    // Some deaths get blast ring
    if ((ps_rand() % 8) == 0)
      *death_flags |= DF_BLAST_RING;
  }

  // Set flags for all deaths
  *death_flags |= DF_FIREBALL + DF_BREAKS_APART + DF_CONTACT_FIREBALL + DF_CONTACT_BREAKS_APART + DF_DEBRIS_SMOKES +
                  DF_DEBRIS_FIREBALL;
}

// Applies a default death to an object
// Parameters:	objp - the object to destroy
//					killer - the object who is killing it, or NULL
//					damage - how much damage was applied in the death blow?
void KillObject(object *objp, object *killer, float damage) {
  int death_flags = -1;
  float delay_time;

  // Make sure a valid type
  ASSERT(IS_GENERIC(objp->type) || (objp->type == OBJ_DOOR));

  // Bail if already dying or exploding
  if ((objp->flags & OF_DYING) || (objp->flags & OF_DEAD))
    return;

  // Get death info from the object page
  if (IS_GENERIC(objp->type)) {

    // Get random probability
    int r = (ps_rand() * 100 / (D3_RAND_MAX + 1)) + 1; // in range 1 to 100

    // Loop through death types looking for chosen one
    for (int i = 0; i < MAX_DEATH_TYPES; i++) {
      int p = Object_info[objp->id].death_probabilities[i];
      if (r <= p) {
        float delay_min, delay_max;

        death_flags = Object_info[objp->id].death_types[i].flags;

        delay_min = Object_info[objp->id].death_types[i].delay_min;
        delay_max = Object_info[objp->id].death_types[i].delay_max;

        delay_time = delay_min + (delay_max - delay_min) * ps_rand() / D3_RAND_MAX;

        mprintf(0, "Using %d\n", i);
        break;
      }
      r -= p;
    }
  }

  // If no death from page, generate default
  if (death_flags == -1)
    GenerateDefaultDeath(objp, &death_flags, &delay_time);

  // Now kill the object
  KillObject(objp, killer, damage, death_flags, delay_time);
}

// Sets the physics parameters for a falling object
void SetFallingPhysics(object *objp) {
  // Set gravity & other parms
  objp->mtype.phys_info.flags = PF_GRAVITY | PF_BOUNCE;
  objp->mtype.phys_info.num_bounces = 0;
  objp->mtype.phys_info.coeff_restitution = .03f;
  if (objp->mtype.phys_info.mass < 20.0)
    objp->mtype.phys_info.mass = 20.0f;
  objp->mtype.phys_info.drag = .00001f;
  objp->mtype.phys_info.rotdrag = .00001f;

  // Special stuff for walkers
  if (objp->movement_type == MT_WALKING) {
    objp->mtype.phys_info.rotvel = Zero_vector;
    objp->mtype.phys_info.flags |= PF_POINT_COLLIDE_WALLS;
    float proj = objp->mtype.phys_info.velocity * objp->orient.uvec;
    if (proj < 0.0f)
      objp->mtype.phys_info.velocity -= proj * objp->orient.uvec;

    objp->mtype.phys_info.velocity += objp->orient.uvec * (3.0f + ((float)ps_rand() / D3_RAND_MAX) * 5.0);
    objp->movement_type = MT_PHYSICS;
  } else { // not a walker

    // If not spinning much, give the object a good spin
    if (vm_GetMagnitude(&objp->mtype.phys_info.rotvel) < 4000.0f) {
      objp->mtype.phys_info.rotvel.x = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
      objp->mtype.phys_info.rotvel.y = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
      objp->mtype.phys_info.rotvel.z = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
    }
  }
}

// Sets the physics parameters for an object the flies in the air when dies
void SetFlyingPhysics(object *objp, bool tumbles) {
  // Set gravity & other parms
  objp->mtype.phys_info.flags = PF_GRAVITY | PF_NO_COLLIDE;
  objp->mtype.phys_info.coeff_restitution = .03f;
  objp->mtype.phys_info.mass = 50000.0f;
  objp->mtype.phys_info.drag = .01f;
  objp->mtype.phys_info.rotdrag = .01f;

  objp->movement_type = MT_PHYSICS;

  if (tumbles) {
    // Make y spin a little bit more that x or z
    objp->mtype.phys_info.rotvel.x = (float)((40000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
    objp->mtype.phys_info.rotvel.y = (float)((60000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
    objp->mtype.phys_info.rotvel.z = (float)((40000.0f * (float)(D3_RAND_MAX / 2 - ps_rand())) / (float)(D3_RAND_MAX / 2));
  }

  if (objp->orient.uvec.y == 1.0f) {
    objp->mtype.phys_info.velocity.y = (float)(3 * (ps_rand() % 15)) + 20.0;
    objp->mtype.phys_info.velocity.x = 0;
    objp->mtype.phys_info.velocity.z = 0;

    // Doubled the velocity on 4/30/99 to make Josh's pop machines cooler. -MT
    objp->mtype.phys_info.velocity.y *= 2.0;
  } else {
    objp->mtype.phys_info.velocity = objp->orient.uvec * ((float)(2.0f * (ps_rand() % 15)) + 7.0f);
  }
}

// Figure out how long it will take the dying anim to play
float GetDeathAnimTime(object *objp) {
  float death_time = 0.0;

  if (objp->control_type == CT_AI) {

    ASSERT(IS_GENERIC(objp->type));

    if (Object_info[objp->id].anim[objp->ai_info->movement_type].elem[AS_DEATH].to != 0) {

      // calculate how long for the object to finish its current animation before starting death anim
      float extra_time = objp->rtype.pobj_info.anim_time *
                         (objp->rtype.pobj_info.anim_end_frame - objp->rtype.pobj_info.anim_frame) /
                         (objp->rtype.pobj_info.anim_end_frame - objp->rtype.pobj_info.anim_start_frame);
      extra_time = std::min<float>(extra_time, 3.0); // limit extra time to 3 seconds
      mprintf(0, "extra_time = %2f\n", extra_time);

      death_time = Object_info[objp->id].anim[objp->ai_info->movement_type].elem[AS_DEATH].spc + 0.25 + extra_time;
    }
  }

  return death_time;
}

// Kill an object
// The caller can specify death information; if none is specified, a default death will be used.
// Parameters:	objp - the object to destroy
//					killer - the object who is killing it, or NULL
//					damage - how much damage was applied in the death blow
//					death_flags - how the object dies
//					delay_time - how long to delay, if from anim flag not set
void KillObject(object *objp, object *killer, float damage, int death_flags, float delay_time) {
  // Make sure a valid type
  ASSERT(IS_GENERIC(objp->type) || (objp->type == OBJ_DOOR));

  // Bail if already dying or exploding
  if ((objp->flags & OF_DYING) || (objp->flags & OF_DEAD))
    return;

  // Send out multiplayer info
  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
    int seed = ps_rand();
    MultiSendKillObject(objp, killer, damage, death_flags, delay_time, seed);
    ps_srand(seed);
  }

  // Record demo
  if (Demo_flags == DF_RECORDING) {
    int seed = ps_rand();
    DemoWriteKillObject(objp, killer, damage, death_flags, delay_time, seed);
    ps_srand(seed);
  }

  // Say this this object is dying
  objp->flags |= OF_DYING;

  // If object is a door, let the doorway system know
  if (objp->type == OBJ_DOOR)
    DoorwayDestroy(objp);

  // Set the delay if from anim
  if (death_flags & DF_DELAY_FROM_ANIM)
    delay_time = GetDeathAnimTime(objp);

  // Check for delay
  if (delay_time == 0.0) { // No delay. Dies now

    // If blast rings set, create 0-2 delayed blast rings
    if (death_flags & DF_BLAST_RING) {
      float ring_size = OBJECT_OUTSIDE(objp) ? (objp->size * 3) : objp->size;
      int extras = ps_rand() % 3;
      for (int i = 0; i < extras; i++)
        CreateNewEvent(0, 0, (i * .1) + .1, objp, sizeof(*objp), DoBlastRingEvent);
    }

    // Register a kill if the killer is a player
    if (killer && (killer->type == OBJ_PLAYER) && IS_GENERIC(objp->type))
      PlayerScoreAdd(killer->id, Object_info[objp->id].score);

    // Destroy the object now
    DestroyObject(objp, damage * 3.0, death_flags);
  } else { // Some sort of delayed death

    // For upside-down walkers, force simple delay
    bool f_upsidedown_walker = (objp->movement_type == MT_WALKING) && (objp->orient.uvec.y < 0.0f);
    if (f_upsidedown_walker)
      death_flags |= DF_DELAY_LOSES_ANTIGRAV;

    // Set dying control
    int old_control_type = objp->control_type;
    SetObjectControlType(objp, CT_DYING);

    // Set dying flags
    objp->ctype.dying_info.death_flags = death_flags;
    objp->ctype.dying_info.last_smoke_time = -1;
    objp->ctype.dying_info.last_spark_time = -1;
    objp->ctype.dying_info.last_fireball_time = -1;

    // If the killer is a player, save so can add score when the object dies
    if (killer && (killer->type == OBJ_PLAYER) && IS_GENERIC(objp->type))
      objp->ctype.dying_info.killer_playernum = killer->id;
    else
      objp->ctype.dying_info.killer_playernum = -1;

    // Set the timer
    objp->ctype.dying_info.delay_time = delay_time;

    // If loses anti-grav, set physics so object falls
    if (death_flags & DF_DELAY_LOSES_ANTIGRAV)
      SetFallingPhysics(objp);

    // Deal with some goal stuff.  Ask Chris about this
    if ((objp->type == OBJ_ROBOT) || ((objp->type == OBJ_BUILDING) && objp->ai_info)) {
      if ((old_control_type == CT_AI) &&
          (Object_info[objp->id].anim[objp->ai_info->movement_type].elem[AS_DEATH].to != 0.0f)) {
        SetObjectControlType(objp, CT_DYING_AND_AI);
        int next_anim = AS_DEATH;
        GoalAddGoal(objp, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
        mprintf(0, "Start dying anim ");
      }
    }

    // Deal with objects that fly
    if (death_flags & DF_DELAY_FLYING) {
      SetFlyingPhysics(objp, !(death_flags & DF_DELAY_NO_TUMBLE_FLY));

      // Create a fireball
      if (death_flags & DF_FIREBALL)
        CreateObjectFireball(objp);
    }

    // Deal with objects that fade out
    if (death_flags & DF_DELAY_FADE_AWAY) {
      ASSERT(objp->effect_info != NULL);
      objp->effect_info->type_flags |= EF_FADING_OUT;
      objp->effect_info->fade_time = objp->effect_info->fade_max_time = objp->ctype.dying_info.delay_time;
    }

    // Play the sound now if flagged to do so
    if (death_flags & DF_DELAY_SOUND)
      PlayObjectExplosionSound(objp);
    // else if (death_flags & DF_DELAY_SPARKS)	//If no special sound & doing sparks, play sparks sound
    //	Sound_system.Play3dSound(SOUND_ELECTRICAL_DEATH, SND_PRIORITY_NORMAL, objp);
  }
}

//	Applies damage to robot objects.  Handled differently than damage to players for obvious reasons.
bool ApplyDamageToGeneric(object *hit_obj, object *killer, int damage_type, float damage, int server_says,
                          int weapon_id) {
  ASSERT(hit_obj != NULL);

  if (hit_obj->type == OBJ_DUMMY) {
    // as per ChrisP, dummies should be ignored here
    return false;
  }

  if (hit_obj->flags & OF_AI_DEATH) {
    return false;
  }

  // I don't think there's any problem with calling this function on an object that's not a generic
  // or a door, but I don't see why you would.
  ASSERT(IS_GENERIC(hit_obj->type) || (hit_obj->type == OBJ_DOOR));

  object *weapon_obj = killer;

  if (damage_type != GD_SCRIPTED &&
      !(IS_GENERIC(hit_obj->type) && (Object_info[hit_obj->id].flags & OIF_NO_DIFF_SCALE_DAMAGE)))
    damage *= Diff_robot_damage[DIFF_LEVEL];

  if (killer != NULL && killer->type == OBJ_WEAPON) {
    killer = ObjGetUltimateParent(killer);

    if (!(Game_mode & GM_MULTI) || (Game_mode & GM_MULTI && Netgame.local_role == LR_SERVER))
      weapon_id = weapon_obj->id;
  }

  if (hit_obj->flags & OF_DESTROYABLE && (!(hit_obj->flags & OF_USE_DESTROYED_POLYMODEL))) {
    if ((Game_mode & GM_MULTI) && (hit_obj->flags & OF_DESTROYED)) {
      return false; // This object has already been sent to the server to be blown up!
    }

    if (hit_obj->type == OBJ_POWERUP && (Game_mode & GM_MULTI))
      return false;

    if ((!(Game_mode & GM_MULTI)) || server_says || ((Netgame.local_role == LR_SERVER) && (Game_mode & GM_MULTI))) {
      tOSIRISEventInfo ei;
      if (killer != NULL)
        ei.evt_damaged.it_handle = killer->handle;
      else
        ei.evt_damaged.it_handle = OBJECT_HANDLE_NONE;

      if (weapon_obj)
        ei.evt_damaged.weapon_handle = weapon_obj->handle;
      else
        ei.evt_damaged.weapon_handle = OBJECT_HANDLE_NONE;

      ei.evt_damaged.damage_type = damage_type;
      ei.evt_damaged.damage = damage;
      Osiris_CallEvent(hit_obj, EVT_DAMAGED, &ei);

      // This statement allows a robot to have special resistances or vulerabilites to damage types
      damage = ei.evt_damaged.damage;
      if (damage == 0.0f) {
        return false;
      }

      hit_obj->shields -= damage;

      if (Game_mode & GM_MULTI) { // only the server will be calling this
        if (killer != NULL)
          DLLInfo.it_handle = killer->handle;
        else
          DLLInfo.it_handle = OBJECT_HANDLE_NONE;

        DLLInfo.me_handle = hit_obj->handle;
        DLLInfo.fParam = damage;
        CallGameDLL(EVT_GAMEOBJECTSHIELDSCHANGED, &DLLInfo);
      }
    }
    if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
      // Let everyone know about the damage
      MultiSendDamageObject(hit_obj, killer, damage, weapon_id);
    }

    if ((hit_obj->shields < 0) && (hit_obj->flags & OF_AI_DO_DEATH)) {
      hit_obj->shields = 0;
      hit_obj->flags |= OF_AI_DEATH;
    }

    if ((hit_obj->shields < 0) && !(hit_obj->flags & OF_DYING)) {
      // CURRRENTLY - atttached objects remain attached when dying (it looks better) -- chrishack
      //			if (!((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT)))
      //			{
      //				// Attached objects have a 50% chance of falling off their parent when they die
      //				if(ps_rand() >= (D3_RAND_MAX >> 1))
      //				{
      //					UnattachFromParent(hit_obj);
      //				}
      //			}

      if (Game_mode & GM_MULTI) {

        DLLInfo.me_handle = hit_obj->handle;
        DLLInfo.it_handle = (killer) ? killer->handle : OBJECT_HANDLE_NONE;
        CallGameDLL(EVT_GAMEOBJKILLED, &DLLInfo);

        if (Netgame.local_role == LR_SERVER)
          KillObject(hit_obj, killer, damage);
      } else {
        // music hook
        if (killer && killer->type == OBJ_PLAYER && hit_obj->ai_info) {
          if (hit_obj->ai_info->awareness > AWARE_BARELY && hit_obj->ai_info->target_handle == killer->handle)
            Game_music_info.n_hostiles_player_killed++;
        }

        if (Demo_flags != DF_PLAYBACK)
          KillObject(hit_obj, killer, damage);
      }
    }

    if ((!(Game_mode & GM_MULTI)) || server_says || ((Netgame.local_role == LR_SERVER) && (Game_mode & GM_MULTI))) {
      if (weapon_id != 255) {
        if (Weapons[weapon_id].flags & WF_MICROWAVE)
          SetDeformDamageEffect(hit_obj);
        if (Weapons[weapon_id].flags & WF_NAPALM)
          SetNapalmDamageEffect(hit_obj, killer, weapon_id);
        if (Weapons[weapon_id].flags & WF_FREEZE)
          ApplyFreezeDamageEffect(hit_obj);
      }
      return true;
    }
    return false;
  } else
    return false;
}

// Adds a bit of shake to the camera
void AddToShakeMagnitude(float delta) {

  ASSERT(delta >= 0.0);
  Shake_magnitude += delta;
}

// Sets a definite shake to the camera
void SetShakeMagnitude(float delta) {

  ASSERT(delta >= 0.0);
  Shake_magnitude = delta;
}

#define MAX_SHAKE_MAGNITUDE 120

// Shakes player by some random amount
void ShakePlayer() {
  if (Shake_magnitude > MAX_SHAKE_MAGNITUDE)
    Shake_magnitude = MAX_SHAKE_MAGNITUDE;

  float mag = Shake_magnitude;

  uint16_t pitch_adjust = ((ps_rand() % 5) - 2) * mag;
  uint16_t bank_adjust = ((ps_rand() % 5) - 2) * mag;
  uint16_t heading_adjust = ((ps_rand() % 5) - 2) * mag;
  matrix m, tempm;

  Old_player_orient = Player_object->orient;

  if (Shake_magnitude < .00001)
    return;

  vm_AnglesToMatrix(&m, pitch_adjust, heading_adjust, bank_adjust);

  DoForceForShake(Shake_magnitude);
  Shake_magnitude -= (Frametime * (MAX_SHAKE_MAGNITUDE / 3));

  if (Shake_magnitude < 0)
    Shake_magnitude = 0.0;

  tempm = m * Player_object->orient;

  ObjSetOrient(Player_object, &tempm);
}

// Restores the player orientation matrix after shaking
void UnshakePlayer() { ObjSetOrient(Player_object, &Old_player_orient); }

#include "terrain.h"
#include "collide.h"

#define SHARD_MAX_EDGE_LEN 3.0f

// Break the specified (glass) face into shards
// Parameters:	rp, facenum - the face to break.  The face must be a portal face.
//					hitpnt - the point on the face where the face shatters.  If NULL, uses center
// point of
// face 					hitvec - the direction in which the thing that's breaking the glass is
// moving.  If NULL, 						uses the negative of the surface normal
void BreakGlassFace(room *rp, int facenum, vector *hitpnt, vector *hitvec) {
  int roomnum;
  vector t_hitpnt, t_hitvec;
  face *fp = &rp->faces[facenum];

  ASSERT(fp->portal_num != -1);
  portal *pp0 = &rp->portals[fp->portal_num];
  portal *pp1 = &Rooms[pp0->croom].portals[pp0->cportal];

  // If face already broken, bail
  if (!(pp0->flags & PF_RENDER_FACES))
    return;

  // Set hitpnt if not specified
  if (hitpnt == NULL) {
    ComputeCenterPointOnFace(&t_hitpnt, rp, facenum);
    hitpnt = &t_hitpnt;
  }

  // Set hitvec if not specified
  if (hitvec == NULL) {
    t_hitvec = -fp->normal;
    hitvec = &t_hitvec;
  }

  // Get roomnum
  if (rp->flags & RF_EXTERNAL)
    roomnum = MAKE_ROOMNUM(GetTerrainCellFromPos(hitpnt));
  else
    roomnum = ROOMNUM(rp);

  // Play sound
  pos_state pos;
  pos.position = hitpnt;
  pos.orient = (matrix *)&Identity_matrix;
  pos.roomnum = roomnum;

  if (sound_override_glass_breaking == -1)
    Sound_system.Play3dSound(SOUND_BREAKING_GLASS, SND_PRIORITY_HIGH, &pos);
  else
    Sound_system.Play3dSound(sound_override_glass_breaking, SND_PRIORITY_HIGH, &pos);

  // Clear render flags
  pp0->flags &= ~PF_RENDER_FACES;
  pp1->flags &= ~PF_RENDER_FACES;

  // Get the UV for the hit point
  float hitpnt_u, hitpnt_v;
  FindHitpointUV(&hitpnt_u, &hitpnt_v, hitpnt, rp, facenum);

  // Calculate shard movement vector
  vector shardvec = *hitvec;
  vm_NormalizeVectorFast(&shardvec);

  // Create shards
  vector prevpoint = rp->verts[fp->face_verts[fp->num_verts - 1]];
  float prev_u = fp->face_uvls[fp->num_verts - 1].u, prev_v = fp->face_uvls[fp->num_verts - 1].v;
  for (int vertnum = 0; vertnum < fp->num_verts;) {
    int objnum;
    vector curpoint = rp->verts[fp->face_verts[vertnum]], center;
    float cur_u = fp->face_uvls[vertnum].u, cur_v = fp->face_uvls[vertnum].v;

    // Check if should split edge
    if (vm_VectorDistanceQuick(&prevpoint, &curpoint) > SHARD_MAX_EDGE_LEN) {
      curpoint = (curpoint + prevpoint) / 2;
      cur_u = (cur_u + prev_u) / 2;
      cur_v = (cur_v + prev_v) / 2;
    } else // no split
      vertnum++;

    // Calculate the center point
    center = (curpoint + prevpoint + *hitpnt) / 3.0;

    // Create the object
    objnum = ObjCreate(OBJ_SHARD, 0, roomnum, &center, NULL);

    // Setup shard info
    if (objnum != -1) {
      object *objp = &Objects[objnum];
      shard_info_s *si = &objp->rtype.shard_info;

      si->points[0] = prevpoint - objp->pos;
      si->points[1] = curpoint - objp->pos;
      si->points[2] = *hitpnt - objp->pos;

      si->u[0] = prev_u;
      si->v[0] = prev_v;
      si->u[1] = cur_u;
      si->v[1] = cur_v;
      si->u[2] = hitpnt_u;
      si->v[2] = hitpnt_v;

      si->normal = fp->normal;
      si->tmap = fp->tmap;

      // Set velocity
      objp->mtype.phys_info.velocity = shardvec * (50.0 + 100.0 * (objnum % 3));

      // Set rotational velocity
      objp->mtype.phys_info.rotvel.x = 25000.0 * (objnum % 5);
      objp->mtype.phys_info.rotvel.y = 25000.0 * (objnum % 2);
      objp->mtype.phys_info.rotvel.z = 25000.0 * (objnum % 3);

      prevpoint = curpoint;
      prev_u = cur_u;
      prev_v = cur_v;
    }
  }

  // Do multiplayer stuff
  if ((Game_mode & GM_MULTI) && Netgame.local_role == LR_SERVER) {
    MultiSendBreakGlass(rp, facenum);

    if (Num_broke_glass != MAX_BROKE_GLASS) {
      Broke_glass_rooms[Num_broke_glass] = rp - Rooms;
      Broke_glass_faces[Num_broke_glass] = facenum;
      Num_broke_glass++;
    }
  }
}
