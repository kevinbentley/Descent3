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

 * $Logfile: /DescentIII/main/viseffect.cpp $
 * $Revision: 145 $
 * $Date: 4/19/00 5:26p $
 * $Author: Matt $
 *
 * System for creating small visual effects visects
 *
 * $Log: /DescentIII/main/viseffect.cpp $
 *
 * 145   4/19/00 5:26p Matt
 * From Duane for 1.4
 * Changes to InitVisEffects()
 *
 * 144   3/21/00 9:58a Matt
 * Changed to Mac-only the code that sets a variable number of vis effects
 * based on texture quality.
 *
 * 143   3/20/00 2:33p Matt
 * Merge of Duane's post-1.3 changes.
 * Small change in freeing viseffect memory.
 * Fixed botched change with sine wave code.
 *
 * 141   11/05/99 3:17p Jeff
 * fixed visalloc bug for pc
 *
 * 140   10/22/99 2:38p Jay
 * Update for the FinalBoss Laser Effect
 *
 * 139   10/21/99 9:29p Jeff
 * B.A. Macintosh code merge
 *
 * 138   10/12/99 11:08a Jeff
 * grey lightning effect
 *
 * 137   9/21/99 2:54p Jeff
 * grey spark's want lighting
 *
 * 136   7/20/99 1:00p Jason
 * added auto katmai support
 *
 * 135   5/17/99 6:11p Jason
 * moved center of lightning effect
 *
 * 134   5/14/99 12:15p Jason
 * fixed vis effect problem for luke
 *
 * 133   5/13/99 3:42p Ardussi
 * changes for compiling on the Mac
 *
 * 132   5/10/99 8:20a Chris
 * Fixed bug with weather lightning effects and Non-render objects
 *
 * 131   5/10/99 1:53a Jason
 * add blackshark explosion
 *
 * 130   5/05/99 6:30p Jason
 * toned down mass driver effect
 *
 * 129   5/04/99 7:30p Jason
 * fixed viseffect linking problem
 *
 * 128   5/02/99 4:14p Jason
 * fixed bug with attached viseffects
 *
 * 127   5/02/99 1:36a Jason
 * added moving object lighting viseffects
 *
 * 126   5/02/99 12:21a Jason
 * fixed crash bug with napalm vis effects
 *
 * 125   5/01/99 4:58p Jason
 * made real viseffects not get created if not seen
 *
 * 124   4/30/99 7:51p Jason
 * fixed lighting coming from controlled viseffects
 *
 * 123   4/30/99 6:21p Jeff
 * fixed autotile (Jason)
 *
 * 122   4/30/99 5:42p Jason
 * changes for blast rings
 *
 * 121   4/28/99 11:28a Jason
 * made real viseffects not cast light
 *
 * 120   4/26/99 7:42p Jason
 * fixed spew effect
 *
 * 119   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 118   4/19/99 3:18p Jason
 * made real vis effects work
 *
 * 117   4/19/99 3:47a Jeff
 * fixed min/max for Linux
 *
 * 116   4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 115   4/13/99 12:16p Jason
 * more tweaks for the mass driver
 *
 * 114   4/09/99 7:49p Jason
 * yet more mass driver fixes
 *
 * 113   4/09/99 7:26p Jason
 * added better mass driver effect
 *
 * 112   4/07/99 3:53p Jason
 * fixed lightning autotile problem
 *
 * 111   4/06/99 6:25p Jason
 * more mass driver tweaks
 *
 * 110   4/06/99 4:14p Jason
 * made mass driver a little cooler
 *
 * 109   4/06/99 1:51p Jason
 * added new mass driver effect
 *
 * 108   4/05/99 4:39p Jason
 * added groovy new smoke trails
 *
 * 107   4/03/99 4:25p Jason
 * sped up attached vis effects by a large amount
 *
 * 106   4/02/99 3:58p Jason
 * sped up vis effect stuff
 *
 * 105   4/01/99 1:10p Jason
 * made vis effects better for the lighting system
 *
 * 104   3/31/99 1:20p Kevin
 * Fix for Demos and Gamegauge -- to deal with situations where time goes
 * backwards
 *
 * 103   3/31/99 11:42a Jason
 * added support for attached thick lightning
 *
 * 102   3/30/99 7:18p Jason
 * made blast rings more noticeable
 *
 * 101   3/30/99 6:01p Jason
 * added new procedural effect
 *
 * 100   3/30/99 5:19p Jason
 * fixed saturation of thicklighting
 *
 * 99    3/29/99 7:30p Jason
 * added cool new energy effect
 *
 * 98    3/27/99 2:15p Jason
 * added better thick lightining
 *
 * 97    3/25/99 3:30p Jason
 *
 * 96    3/24/99 6:28p Jason
 * fixed size with thick lightning
 *
 * 95    3/23/99 4:10p Jason
 * more tweaks for line sparks
 *
 * 94    3/23/99 3:52p Jason
 * fixed sine wave bug
 *
 * 93    3/23/99 12:50p Jason
 * added line sparks
 *
 * 92    3/22/99 11:17a Jason
 * Katmai enhancements
 *
 * 91    2/25/99 11:01a Matt
 * Added new explosion system.
 *
 * 90    2/15/99 4:10p Jason
 * made non-vis objects kill all their attach sounds/objects
 *
 * 89    2/09/99 2:39p Jason
 * added destroyable faces
 *
 * 88    1/26/99 6:39p Jason
 * added wall effects code
 *
 * 87    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 86    12/11/98 5:08p Jason
 * changed mass driver effect
 *
 * 85    11/19/98 6:38p Jason
 * made a better black shark effect
 *
 * 84    11/18/98 2:54p Jason
 * added snow effect
 *
 * 83    11/10/98 3:28p Jason
 * made dynamic lighting work more sensibly
 *
 * 82    10/21/98 12:47p Jason
 * fixed stupid bug with my last rev
 *
 * 81    10/20/98 9:52p Jason
 * took out assert
 *
 * 80    10/05/98 11:35p Matt
 * Added assert
 *
 * 79    10/05/98 7:29p Jason
 * added cool black smoke
 *
 * 78    9/30/98 2:26p Jason
 * fixed billboard bug
 *
 * 77    9/30/98 12:59p Jason
 * added some cool matcen effects
 *
 * 76    9/29/98 7:15p Jason
 * added axis billboards
 *
 * 75    9/29/98 12:49p Jason
 * worked on matcen effects and lightning
 *
 * 74    9/28/98 4:41p Jason
 * made explosions give dynamic light
 *
 * 73    9/24/98 12:57p Jason
 * more state limited optimizations
 *
 * 72    9/21/98 7:01p Jason
 * miscellaneous visual tweaks
 *
 * 71    9/21/98 6:53p Sean
 * took out stupid debug assert
 *
 * 70    9/18/98 8:23p Jason
 * fixed insidious vis effect errors
 *
 * 69    9/18/98 11:18a Jason
 * fixed miscellaneous bugs with camera system
 *
 * 68    9/17/98 6:08p Jason
 * more tweaks for effects
 *
 * 67    9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 66    9/15/98 6:39p Jason
 * made medium smoke saturate
 *
 * 65    9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 64    9/09/98 4:49p Jason
 * tweaked black shark lightning effect
 *
 * 63    9/09/98 4:30p Jason
 * fixed a remaining (and insidious) bug with gunpoint instancing
 *
 * 62    9/09/98 4:28p Jason
 * added better weapon effects
 *
 * 61    8/17/98 12:10p Chris
 * Fixed MAJOR bug in getting gunpoint positions
 *
 * 60    8/03/98 11:12a Jason
 * fixed some zero foward vector errors
 *
 * 59    6/24/98 3:56p Jason
 * added code for new omega cannon
 *
 * 58    6/23/98 3:34p Jason
 * added cool lighting effect to gravity field
 *
 * 57    6/22/98 6:52p Jason
 * changed gravity field effect somewhat
 *
 * 56    6/22/98 6:26p Jason
 * added gravity field effect for weapons
 *
 * 55    6/12/98 5:14p Jason
 * made viseffects deal with zbuffer better
 *
 * 54    6/10/98 4:47p Jason
 * smoke trail test
 *
 * 53    6/02/98 11:02a Jason
 * Post E3 Checkin
 *
 * 52    5/27/98 5:17p Jason
 * fixed some bugs for the E3 Demo
 *
 * 51    5/26/98 6:54p Jason
 * viseffect optimizations
 *
 * 50    5/26/98 6:36p Jason
 * made particle viseffects not relink
 *
 * 49    5/15/98 11:22a Jason
 * make smoke trail saturation settable by designers
 *
 * 48    5/13/98 12:05p Jason
 * made napalm explosions bigger for bigger objects
 *
 * 47    5/06/98 1:25p Jason
 * more viseffect tweaks
 *
 * 46    5/06/98 12:55p Jason
 * did some vis effect optimizations
 *
 * 45    5/01/98 6:23p Jason
 * made better puddle rain
 *
 * 44    4/30/98 6:45p Jason
 * more changes for weather
 *
 * 43    4/30/98 3:39p Jason
 * don't make non-billowingfireballs rotate
 *
 * 42    4/30/98 11:55a Jason
 * weather tweaks
 *
 * 41    4/29/98 3:27p Jason
 * added weather engine
 *
 * 40    4/29/98 12:50p Jason
 * more rain changes
 *
 * 39    4/29/98 11:38a Jason
 * added some weather effects (first pass)
 *
 * 38    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 37    4/20/98 3:58p Jason
 * made viseffects attach to subobjects other than zero
 *
 * 36    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 35    4/17/98 12:45p Jason
 * various changes for multiplayer
 *
 * 34    4/15/98 2:33p Jason
 * changed some smoke trail stuff
 *
 * 33    4/15/98 12:22p Jason
 * lots of miscellaneous stuff pertaining to lighting and vis effects
 *
 * 32    4/10/98 12:39p Jason
 * added expanding explosion bitmaps
 *
 * 31    4/09/98 4:53p Jason
 * fixed particle bug
 *
 * 30    4/07/98 3:31p Jason
 * got particle effects working with weapons
 *
 * 29    4/07/98 12:54p Jason
 * changes for viseffects and multiplayer dll
 *
 * 28    4/02/98 12:24p Jason
 * trimmed some fat from our structures
 *
 * 27    3/31/98 2:22p Jason
 * bug fix for dead vis effects
 *
 * 26    3/30/98 12:46a Jason
 * sped up deletion of vis effects
 *
 * 25    3/09/98 1:00p Jason
 * toned down explosion lighting
 *
 * 24    3/05/98 6:56p Jason
 * temp fix for out of bound errors on viseffects
 *
 * 23    2/26/98 3:20p Jason
 * changes for faster lighting
 *
 * 22    2/25/98 4:59p Jason
 * got dynamic explosion lighting working with vis-effects
 *
 * 21    2/25/98 4:31p Jason
 * changes for explosions
 *
 * 20    2/17/98 1:50p Jason
 * fixed viseffect zbias problem
 *
 * 19    2/17/98 1:00p Jason
 * fixed viseffect clipping
 *
 * 18    2/16/98 2:37p Jason
 * added real viseffects
 *
 * 17    2/06/98 1:00p Jason
 * did some state setting for blast rings
 *
 * 16    2/05/98 6:53p Jason
 * added new weapon slot
 *
 * 15    2/05/98 2:54p Jason
 * changes for explosions
 *
 * 14    2/05/98 12:37p Jason
 * added more weapon effects
 *
 * 13    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 12    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 */

#include "viseffect.h"
#include "fireball.h"
#include "terrain.h"
#include "game.h"
#include "room.h"
#include "vclip.h"
#include "gametexture.h"
#include "object.h"
#include <memory.h>
#include <stdlib.h>
#include "physics.h"
#include "weapon.h"
#include "lighting.h"
#include "dedicated_server.h"
#include "player.h"
#include "config.h"
#include "weather.h"
#include "polymodel.h"
#include "psrand.h"
#include "mem.h"

#include <algorithm>

// DAJ vis_effect VisEffects[max_vis_effects];
// DAJ uint16_t VisDeadList[max_vis_effects];
// DAJ static int16_t Vis_free_list[max_vis_effects];

vis_effect *VisEffects = NULL;

static int16_t *Vis_free_list = NULL;
uint16_t *VisDeadList = NULL;

uint16_t max_vis_effects = 0;

int NumVisDead = 0;
int Highest_vis_effect_index = 0;
int Num_vis_effects = 0;

void ShutdownVisEffects() {
  if (VisEffects)
    mem_free(VisEffects);
  if (VisDeadList)
    mem_free(VisDeadList);
  if (Vis_free_list)
    mem_free(Vis_free_list);
}

// Goes through our array and clears the slots out
void InitVisEffects() {
  static uint16_t old_max_vis = 0;
  max_vis_effects = MAX_VIS_EFFECTS; // always peg to max on PC

  if (old_max_vis == max_vis_effects)
    return;

  if (VisEffects != NULL) {
    VisEffects = (vis_effect *)mem_realloc(VisEffects, sizeof(vis_effect) * max_vis_effects);
    VisDeadList = (uint16_t *)mem_realloc(VisDeadList, sizeof(uint16_t) * max_vis_effects);
    Vis_free_list = (int16_t *)mem_realloc(Vis_free_list, sizeof(int16_t) * max_vis_effects);
  } else if (VisEffects == NULL) {
    VisEffects = (vis_effect *)mem_malloc(sizeof(vis_effect) * max_vis_effects);
    VisDeadList = (uint16_t *)mem_malloc(sizeof(uint16_t) * max_vis_effects);
    Vis_free_list = (int16_t *)mem_malloc(sizeof(int16_t) * max_vis_effects);
  }
  for (int i = 0; i < max_vis_effects; i++) {
    VisEffects[i].type = VIS_NONE;
    VisEffects[i].roomnum = -1;
    VisEffects[i].prev = -1;
    VisEffects[i].next = -1;
    Vis_free_list[i] = i;
  }
  old_max_vis = max_vis_effects;
  Num_vis_effects = 0;
  Highest_vis_effect_index = 0;

  atexit(ShutdownVisEffects);
}

// Returns the next free viseffect
int VisEffectAllocate() {
  if (Num_vis_effects == max_vis_effects) {
    mprintf(0, "Couldn't allocate vis effect!\n");
    return -1;
  }

  int n = Vis_free_list[Num_vis_effects++];
  ASSERT(VisEffects[n].type == VIS_NONE); // Get Jason

  if (n > Highest_vis_effect_index) {
    Highest_vis_effect_index = n;
  }

  return n;
}

// Frees up a viseffect for use
int VisEffectFree(int visnum) {
  ASSERT(visnum >= 0 && visnum <= max_vis_effects);

  Vis_free_list[--Num_vis_effects] = visnum;
  VisEffects[visnum].type = VIS_NONE;

  if (visnum == Highest_vis_effect_index) {
    while (VisEffects[Highest_vis_effect_index].type != VIS_NONE && Highest_vis_effect_index > 0)
      Highest_vis_effect_index--;
  }

  return 1;
}

int VisEffectInitType(vis_effect *vis) {
  int ret = 1;

  vis->size = Fireballs[vis->id].size;
  vis->flags |= VF_USES_LIFELEFT;
  vis->lifeleft = Fireballs[vis->id].total_life;
  vis->lifetime = vis->lifeleft;

  if (Fireballs[vis->id].type == FT_EXPLOSION && vis->id != CUSTOM_EXPLOSION_INDEX && vis->id != NAPALM_BALL_INDEX)
    vis->lighting_color = OPAQUE_FLAG | GR_RGB16(255, 180, 20);

  return ret;
}

// initialize a new viseffect.  adds to the list for the given room
// returns the vis number
int VisEffectCreate(uint8_t type, uint8_t id, int roomnum, vector *pos) {
  int visnum;
  vis_effect *vis;

  if ((Game_mode & GM_MULTI) && Dedicated_server)
    return -1; // Dedicated servers don't need to create vis effects

  if (ROOMNUM_OUTSIDE(roomnum)) {
    if (CELLNUM(roomnum) > TERRAIN_WIDTH * TERRAIN_DEPTH)
      return -1;
    if (CELLNUM(roomnum) < 0)
      return -1;

    if (Gametime - Last_terrain_render_time > 5.0)
      return -1;
  } else {
    ASSERT(roomnum >= 0 && roomnum <= Highest_room_index && Rooms[roomnum].used);

    // Don't create viseffects in rooms we haven't seen in a while
    if (Gametime - Rooms[roomnum].last_render_time > 5.0)
      return -1;
  }

  // Find next free object
  visnum = VisEffectAllocate();

  if (visnum == -1) // no free objects
    return -1;

  ASSERT(VisEffects[visnum].type == VIS_NONE); // make sure unused

  vis = &VisEffects[visnum];

  ASSERT(vis->roomnum == -1);

  memset(vis, 0, sizeof(vis_effect));

  // Fill in fields
  vis->type = VIS_FIREBALL;
  vis->id = id;
  vis->pos = *pos;
  vis->flags = 0;
  vis->phys_flags = 0;
  vis->roomnum = roomnum;
  vis->movement_type = MT_NONE;
  vis->attach_info.end_vertnum = -1;
  vis->next = -1;
  vis->prev = -1;
  vis->lighting_color = 0;

  ASSERT(roomnum != -1);

  vis->creation_time = Gametime;

  // Initialize all the type-specific info
  VisEffectInitType(vis);

  VisEffectLink(visnum, roomnum);

  return visnum;
}

// Creates vis effects but has the caller set their parameters
// initialize a new viseffect.  adds to the list for the given room
// returns the vis number
int VisEffectCreateControlled(uint8_t type, object *parent, uint8_t id, int roomnum, vector *pos, float lifetime,
                              vector *velocity, int phys_flags, float size, float drag, float mass, bool isreal) {
  int visnum;
  vis_effect *vis;
  static int napalm_id = -1;

  if (napalm_id == -1)
    napalm_id = FindWeaponName("Napalm");

  if (isreal) {
    ASSERT(parent != NULL); // You have a spew that has no parent object?

    if (ROOMNUM_OUTSIDE(roomnum)) {
      if (CELLNUM(roomnum) > TERRAIN_WIDTH * TERRAIN_DEPTH)
        return -1;
      if (CELLNUM(roomnum) < 0)
        return -1;

      if (Gametime - Last_terrain_render_time > 5.0)
        return -1;
    } else {
      ASSERT(roomnum >= 0 && roomnum <= Highest_room_index && Rooms[roomnum].used);

      // Don't create real objects in rooms we haven't seen in a while
      if (Gametime - Rooms[roomnum].last_render_time > 5.0)
        return -1;
    }

    int objnum = CreateAndFireWeapon(pos, velocity, parent, napalm_id);
    if (objnum >= 0) {
      object *obj = &Objects[objnum];

      obj->lifeleft = lifetime;
      obj->lifetime = lifetime;
      obj->movement_type = MT_PHYSICS;

      if (mass > 0 && drag > 0) {
        obj->mtype.phys_info.mass = mass;
        obj->mtype.phys_info.drag = drag;
      }

      if (size > 0)
        obj->size = size;

      obj->mtype.phys_info.velocity = *velocity;

      if (phys_flags)
        obj->mtype.phys_info.flags = phys_flags;

      obj->ctype.laser_info.casts_light = false;
    }

    return objnum;
  }

  visnum = VisEffectCreate(type, id, roomnum, pos);

  if (visnum < 0)
    return -1; // No vis effects free

  vis = &VisEffects[visnum];

  vis->lifeleft = lifetime;
  vis->lifetime = lifetime;
  vis->movement_type = MT_PHYSICS;
  vis->mass = mass;
  vis->drag = drag;

  if (size > 0)
    vis->size = size;

  vis->velocity = *velocity;

  // float mag=vm_GetMagnitudeFast (&vis->velocity);
  // mprintf(0,"CREATION:Velocity mag is %f\n",mag);

  if (phys_flags)
    vis->phys_flags = phys_flags;

  if (ROOMNUM_OUTSIDE(roomnum))
    vis->phys_flags |= PF_NO_COLLIDE;

  vis->flags |= VF_NO_Z_ADJUST;
  vis->lighting_color &= ~(0x8000);

  return visnum;
}

// link the viseffect  into the list for its room
// Does nothing for effects over terrain
void VisEffectLink(int visnum, int roomnum) {
  vis_effect *vis = &VisEffects[visnum];

  ASSERT(visnum != -1);

  if (!ROOMNUM_OUTSIDE(vis->roomnum))
    ASSERT(roomnum >= 0 && roomnum <= Highest_room_index);

  vis->roomnum = roomnum;

  if (ROOMNUM_OUTSIDE(vis->roomnum))
    return;

  vis->next = Rooms[roomnum].vis_effects;
  Rooms[roomnum].vis_effects = visnum;
  ASSERT(vis->next != visnum);

  vis->prev = -1;

  if (vis->next != -1)
    VisEffects[vis->next].prev = visnum;
}

// Unlinks a viseffect from a room
// Does nothing for terrain
void VisEffectUnlink(int visnum) {
  vis_effect *vis = &VisEffects[visnum];

  ASSERT(visnum != -1);

  if (ROOMNUM_OUTSIDE(vis->roomnum))
    return;
  else {

    room *rp = &Rooms[vis->roomnum];

    if (vis->prev == -1)
      rp->vis_effects = vis->next;
    else
      VisEffects[vis->prev].next = vis->next;

    if (vis->next != -1)
      VisEffects[vis->next].prev = vis->prev;

    vis->roomnum = -1;
  }
}

// when an effect has moved into a new room, this function unlinks it
// from its old room and links it into the new room
void VisEffectRelink(int visnum, int newroomnum) {
  ASSERT(visnum >= 0 && visnum < max_vis_effects);

  VisEffectUnlink(visnum);
  VisEffectLink(visnum, newroomnum);
}

// Kills all the effects that are dead
void VisEffectDeleteDead() {
  int i;
  for (i = 0; i < NumVisDead; i++) {
    VisEffectDelete(VisDeadList[i]);
  }

  NumVisDead = 0;
}

// remove viseffect from the world
void VisEffectDelete(int visnum) {
  vis_effect *vis = &VisEffects[visnum];

  ASSERT(visnum != -1);
  ASSERT(vis->type != VIS_NONE);

  VisEffectUnlink(visnum);

  vis->type = VIS_NONE; // unused!
  vis->roomnum = -1;    // zero it!

  VisEffectFree(visnum);
}

// Frees all the objects that are currently in use
void FreeAllVisEffects() {

  for (int i = 0; i < max_vis_effects; i++)
    if (VisEffects[i].type != VIS_NONE)
      VisEffectDelete(i);
}

// Creates a some sparks that go in random directions
void CreateRandomLineSparks(int num_sparks, vector *pos, int roomnum, uint16_t color, float force_scalar) {
  // Make more sparks if Katmai
  if (Katmai)
    num_sparks *= 2;

  // Create some sparks
  for (int i = 0; i < num_sparks; i++) {
    int visnum = VisEffectCreate(VIS_FIREBALL, FADING_LINE_INDEX, roomnum, pos);
    if (visnum >= 0) {
      vis_effect *vis = &VisEffects[visnum];

      vis->movement_type = MT_PHYSICS;
      vis->mass = 500;
      vis->drag = .001f;
      vis->phys_flags |= PF_GRAVITY | PF_NO_COLLIDE;

      vis->velocity.x = (ps_rand() % 100) - 50;
      vis->velocity.y = (ps_rand() % 100);
      vis->velocity.z = (ps_rand() % 100) - 50;

      vm_NormalizeVectorFast(&vis->velocity);

      vis->velocity *= 20 + (ps_rand() % 10);
      vis->velocity *= force_scalar;
      vis->size = .7 + ((ps_rand() % 10) * .04);
      vis->flags |= VF_USES_LIFELEFT;
      float lifetime = 1 + ((ps_rand() % 10) * .15);
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;

      if (color == 0)
        vis->lighting_color = GR_RGB16(200 + (ps_rand() % 50), 150 + (ps_rand() % 50), ps_rand() % 50);
      else
        vis->lighting_color = color;
    }
  }
}

// Creates a some sparks that go in random directions
void CreateRandomSparks(int num_sparks, vector *pos, int roomnum, int which_index, float force_scalar) {
  // Make more sparks if Katmai
  if (Katmai)
    num_sparks *= 2;

  // Create some sparks
  for (int i = 0; i < num_sparks; i++) {
    int sparknum;
    int index;

    if (ps_rand() % 2)
      index = HOT_SPARK_INDEX;
    else
      index = COOL_SPARK_INDEX;

    if (which_index != -1)
      index = which_index;

    sparknum = VisEffectCreate(VIS_FIREBALL, index, roomnum, pos);

    if (sparknum >= 0) {
      vis_effect *vis = &VisEffects[sparknum];

      vis->movement_type = MT_PHYSICS;
      vis->mass = 100;
      vis->drag = .1f;

      vis->phys_flags |= PF_GRAVITY | PF_NO_COLLIDE;

      vis->velocity.x = (ps_rand() % 100) - 50;
      vis->velocity.y = (ps_rand() % 100);
      vis->velocity.z = (ps_rand() % 100) - 50;

      vm_NormalizeVectorFast(&vis->velocity);
      vis->velocity *= 10 + (ps_rand() % 10);
      vis->velocity *= force_scalar;
      vis->size = .2 + ((ps_rand() % 10) * .01);
      vis->flags |= VF_USES_LIFELEFT;
      float lifetime = 1 + ((ps_rand() % 10) * .15);
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;
    }
  }
}

// Creates a some particles that go in random directions
void CreateRandomParticles(int num_sparks, vector *pos, int roomnum, int bm_handle, float size, float life) {
  // Create some sparks
  float tenth_life = life / 10.0;
  float tenth_size = size / 10.0;

  for (int i = 0; i < num_sparks; i++) {
    int sparknum;

    sparknum = VisEffectCreate(VIS_FIREBALL, PARTICLE_INDEX, roomnum, pos);

    if (sparknum >= 0) {
      vis_effect *vis = &VisEffects[sparknum];

      vis->movement_type = MT_PHYSICS;
      vis->mass = 100;
      vis->drag = .1f;

      vis->phys_flags |= PF_GRAVITY | PF_NO_COLLIDE;

      vis->velocity.x = (ps_rand() % 100) - 50;
      vis->velocity.y = (ps_rand() % 100);
      vis->velocity.z = (ps_rand() % 100) - 50;

      vm_NormalizeVectorFast(&vis->velocity);
      vis->velocity *= 10 + (ps_rand() % 10);
      vis->size = size + (((ps_rand() % 11) - 5) * tenth_size);
      vis->flags |= VF_USES_LIFELEFT;
      float lifetime = life + (((ps_rand() % 11) - 5) * tenth_life);
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;
      vis->custom_handle = bm_handle;
    }
  }
}

// Draws a weapons fading line
void DrawVisFadingLine(vis_effect *vis) {
  float norm_time;
  float time_live = Gametime - vis->creation_time;
  float size = vis->size;

  int visnum = vis - VisEffects;
  norm_time = time_live / vis->lifetime;

  if (norm_time >= 1)
    norm_time = .99999f; // don't go over!

  rend_SetAlphaType(AT_SATURATE_VERTEX);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);
  rend_SetOverlayType(OT_NONE);

  vector vecs[2];
  g3Point pnts[2];
  int i;

  vecs[0] = vis->pos;
  vecs[1] = vis->end_pos;

  if (!(vis->flags & VF_WINDSHIELD_EFFECT)) // bash end position
  {
    vector vel = -vis->velocity;
    vm_NormalizeVectorFast(&vel);
    vecs[1] = vis->pos + (vel * vis->size);
  }

  ddgr_color color = GR_16_TO_COLOR(vis->lighting_color);
  int r = GR_COLOR_RED(color);
  int g = GR_COLOR_GREEN(color);
  int b = GR_COLOR_BLUE(color);

  for (i = 0; i < 2; i++) {
    g3_RotatePoint(&pnts[i], &vecs[i]);
    pnts[i].p3_flags |= PF_RGBA;
    pnts[i].p3_r = (r / 255.0);
    pnts[i].p3_g = (g / 255.0);
    ;
    pnts[i].p3_b = (b / 255.0);
    ;
  }

  if (vis->flags & VF_WINDSHIELD_EFFECT)
    pnts[0].p3_a = .3f;
  else
    pnts[0].p3_a = 1.0 - norm_time;

  pnts[1].p3_a = 0.0;

  g3_DrawSpecialLine(&pnts[0], &pnts[1]);
}

// Draws a blast ring vis effect
void DrawVisBlastRing(vis_effect *vis) {
  vector inner_vecs[30], outer_vecs[30];
  g3Point inner_points[30], outer_points[30];
  float lifenorm = (vis->lifetime - vis->lifeleft) / vis->lifetime;
  float cur_size = lifenorm * vis->size;
  int i;
  g3Point *pntlist[4];
  matrix orient;
  vector fvec;

  if (vis->flags & VF_REVERSE) {
    lifenorm = 1 - lifenorm;
    cur_size = lifenorm * vis->size;
  }

  if (vis->flags & VF_PLANAR)
    fvec = vis->end_pos;
  else {
    fvec = Viewer_object->pos - vis->pos;
    vm_NormalizeVectorFast(&fvec);
  }

  if (vm_GetMagnitudeFast(&fvec) < .5)
    return;
  vm_VectorToMatrix(&orient, &fvec, NULL, NULL);

  int num_segments = 20;

  int ring_increment = 65536 / num_segments;
  int ring_angle = 0;

  if (lifenorm > 1.0)
    lifenorm = 1.0;

  rend_SetAlphaType(AT_SATURATE_TEXTURE_VERTEX);
  rend_SetOverlayType(OT_NONE);
  rend_SetTextureType(TT_LINEAR);
  rend_SetLighting(LS_NONE);
  rend_SetZBias(-1.0);
  rend_SetZBufferWriteMask(0);

  ring_angle = 0;

  for (i = 0; i < num_segments; i++, ring_angle += ring_increment) {
    float ring_sin = FixSin(ring_angle);
    float ring_cos = FixCos(ring_angle);

    inner_vecs[i] = orient.rvec * (ring_cos * (cur_size / 2));
    inner_vecs[i] += orient.uvec * (ring_sin * (cur_size / 2));
    inner_vecs[i] += vis->pos;

    outer_vecs[i] = orient.rvec * (ring_cos * cur_size);
    outer_vecs[i] += orient.uvec * (ring_sin * cur_size);
    outer_vecs[i] += vis->pos;

    g3_RotatePoint(&inner_points[i], &inner_vecs[i]);
    g3_RotatePoint(&outer_points[i], &outer_vecs[i]);
    outer_points[i].p3_flags |= PF_UV | PF_RGBA;
    inner_points[i].p3_flags |= PF_UV | PF_RGBA;

    outer_points[i].p3_a = (1.0 - lifenorm);
    inner_points[i].p3_a = 0;
    inner_points[i].p3_l = 1;
    inner_points[i].p3_l = 1;
  }

  for (i = 0; i < num_segments; i++) {
    int next = (i + 1) % num_segments;

    outer_points[i].p3_u = 0 + lifenorm;
    outer_points[next].p3_u = 1.0 + lifenorm;
    outer_points[i].p3_v = 0;
    outer_points[next].p3_v = 0;

    inner_points[i].p3_u = 0 + lifenorm;
    inner_points[next].p3_u = 1.0 + lifenorm;
    inner_points[i].p3_v = 1;
    inner_points[next].p3_v = 1;

    pntlist[0] = &outer_points[i];
    pntlist[1] = &outer_points[next];
    pntlist[2] = &inner_points[next];
    pntlist[3] = &inner_points[i];

    g3_DrawPoly(4, pntlist, vis->custom_handle);
  }

  rend_SetZBufferWriteMask(1);
  rend_SetZBias(0);
}

// Draws a raindrop on the players windshield
void DrawVisRainDrop(vis_effect *vis) {
  float norm_time;
  float time_live = Gametime - vis->creation_time;
  float size = vis->size;

  int visnum = vis - VisEffects;
  int bm_handle;
  fireball *fb = &Fireballs[vis->id];

  norm_time = time_live / vis->lifetime;

  if (norm_time >= 1)
    norm_time = .99999f; // don't go over!

  size *= (1 - (norm_time / 2));

  bm_handle = fb->bm_handle;

  float val;
  if (norm_time > .5)
    val = 1.0 - ((norm_time - .5) / .5);
  else if (norm_time < .1)
    val = norm_time / .1;
  else
    val = 1.0;

  rend_SetAlphaValue(val * .4 * 255);
  rend_SetOverlayType(OT_NONE);
  rend_SetWrapType(WT_CLAMP);
  rend_SetLighting(LS_NONE);

  // Set position
  vector pos;

  if (vis->id == RAINDROP_INDEX) {
    rend_SetZBufferState(0);
    rend_SetAlphaType(AT_SATURATE_TEXTURE);
    rend_SetAlphaValue(val * .4 * 255);

    pos = Viewer_object->pos;
    pos += Viewer_object->orient.rvec * vis->pos.x;
    pos += Viewer_object->orient.uvec * vis->pos.y;
    pos += Viewer_object->orient.fvec * vis->pos.z;
    g3_DrawRotatedBitmap(&pos, 0, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
    rend_SetZBufferState(1);
  } else {
    rend_SetAlphaType(AT_SATURATE_TEXTURE);
    rend_SetAlphaValue(val * .2 * 255);
    rend_SetZBufferWriteMask(0);
    pos = vis->pos;
    ASSERT(!((vis->end_pos.x == 0.0) && (vis->end_pos.y == 0.0) && (vis->end_pos.z == 0.0)));
    g3_DrawPlanarRotatedBitmap(&pos, &vis->end_pos, 0, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0),
                               bm_handle);
    rend_SetZBufferWriteMask(1);
  }

  rend_SetWrapType(WT_WRAP);
}

// Draws a snowflake
void DrawVisSnowflake(vis_effect *vis) {
  float norm_time;
  float time_live = Gametime - vis->creation_time;
  float size = vis->size;

  int visnum = vis - VisEffects;
  int bm_handle;
  fireball *fb = &Fireballs[vis->id];

  norm_time = time_live / vis->lifetime;

  if (norm_time >= 1)
    norm_time = .99999f; // don't go over!

  // size*=(1-(norm_time/2));

  bm_handle = fb->bm_handle;

  float val;

  val = 1.0 - (norm_time);

  rend_SetAlphaValue(val * .6 * 255);
  rend_SetOverlayType(OT_NONE);
  // rend_SetWrapType (WT_CLAMP);
  rend_SetLighting(LS_NONE);
  // rend_SetZBufferState (0);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);

  ddgr_color color = GR_16_TO_COLOR(vis->lighting_color);
  g3_DrawBitmap(&vis->pos, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle, color);

  // rend_SetZBufferState (1);
  // rend_SetWrapType (WT_WRAP);
}

// Draws a lighting bolt from one area to another
// Velocity.x is how much randomness goes into drawing
// Velocity.y is the scalar that effects how many segments to draw
void DrawVisLightningBolt(vis_effect *vis) {
  vector line_norm;
  float line_mag;
  int num_segs;
  float lightning_mag;

  g3Point pnt1, pnt2;

  line_norm = vis->pos - vis->end_pos;
  line_mag = vm_GetMagnitudeFast(&line_norm);

  line_norm /= line_mag;

  if (line_mag < 1)
    return;

  float alpha_norm;

  if (vis->flags & VF_EXPAND) {
    num_segs = line_mag * vis->velocity.y;
    lightning_mag = vis->velocity.x;

    alpha_norm = vis->lifeleft / vis->lifetime;
  } else {
    num_segs = line_mag * vis->velocity.y;
    lightning_mag = vis->velocity.x;

    alpha_norm = .7f;

    // Make it powerup up based on distance
    if (line_mag > 30 && (vis->flags & VF_NO_Z_ADJUST)) {
      float scalar = 1.0 - ((line_mag - 30) / 150.0);
      if (scalar < 0)
        return;

      alpha_norm *= scalar;
    }
  }

  if (num_segs < 2)
    return;

  // Set some states

  rend_SetTextureType(TT_FLAT);
  rend_SetAlphaType(AT_SATURATE_VERTEX);
  rend_SetLighting(LS_NONE);
  rend_SetZBufferWriteMask(0);

  if (vis->id == GRAY_LIGHTNING_BOLT_INDEX) {
    // get the color from the struct
    rend_SetFlatColor(GR_16_TO_COLOR(vis->lighting_color));
  } else {
    rend_SetFlatColor(GR_RGB(10, 60, 200));
  }

  pnt1.p3_a = alpha_norm;
  pnt2.p3_a = alpha_norm;

  vector vecs[50];

  num_segs = std::min(num_segs, 50);

  CreateLightningRodPositions(&vis->pos, &vis->end_pos, vecs, num_segs, lightning_mag, false);

  for (int i = 0; i < num_segs - 1; i++) {
    g3_RotatePoint(&pnt1, &vecs[i]);
    g3_RotatePoint(&pnt2, &vecs[i + 1]);

    pnt1.p3_flags |= PF_RGBA;
    pnt2.p3_flags |= PF_RGBA;

    g3_DrawSpecialLine(&pnt1, &pnt2);
  }

  rend_SetZBufferWriteMask(1);
}

// Draws a lighting bolt sine wave from one area to another
// Velocity.x represents how many increments to take (a scalar)
// Velocity.y represents how "wide" the arcs are from the center of the line
void DrawVisSineWave(vis_effect *vis) {
  vector line_norm;
  float line_mag;
  matrix mat;
  int num_segs;

  vector from, to, base_from, rvec, uvec;
  g3Point pnt1, pnt2;

  line_norm = vis->pos - vis->end_pos;
  line_mag = vm_GetMagnitudeFast(&line_norm);
  if (line_mag < .1)
    return;

  line_norm /= line_mag;

  float alpha_norm;

  if (vis->flags & VF_EXPAND)
    alpha_norm = vis->lifeleft / vis->lifetime;

  num_segs = vis->velocity.x * line_mag; // /2
  line_norm /= vis->velocity.x;          // *2

  alpha_norm = vis->lifeleft / vis->lifetime;

  vm_VectorToMatrix(&mat, &line_norm, &vis->velocity, NULL);
  rvec = mat.rvec * vis->velocity.y; // /4
  uvec = mat.uvec * vis->velocity.y; // /4

  // Set some states

  rend_SetTextureType(TT_FLAT);
  rend_SetAlphaType(AT_SATURATE_VERTEX);
  rend_SetLighting(LS_NONE);
  rend_SetZBufferWriteMask(0);
  rend_SetFlatColor(GR_RGB(10, 60, 200));
  int cur_sin = (vis - VisEffects) * 5000;

  cur_sin += (FrameCount * 2000);

  base_from = vis->end_pos;
  from = base_from;

  pnt1.p3_a = alpha_norm;
  pnt2.p3_a = alpha_norm;

  for (int i = 0; i < num_segs; i++, base_from += line_norm) {
    to = base_from + line_norm + (FixSin((cur_sin) % 65536) * uvec);
    to += (FixCos((cur_sin) % 65536) * rvec);

    g3_RotatePoint(&pnt1, &from);
    g3_RotatePoint(&pnt2, &to);

    pnt1.p3_flags |= PF_RGBA;
    pnt2.p3_flags |= PF_RGBA;

    g3_DrawSpecialLine(&pnt1, &pnt2);

    from = to;

    cur_sin += 4000;
  }

  rend_SetZBufferWriteMask(1);
}

// Calculates the corners for a billboard
// Returns 0 if off screen, or 1 if we should draw
int GetBillboardCorners(g3Point *pnts, g3Point *top_point, g3Point *bot_point, float width) {
  // get the camera's world position
  vector viewerPos;
  g3_GetViewPosition(&viewerPos);

  // calculate the vector from the top point to the bottom point
  ASSERT(bot_point->p3_flags & PF_ORIGPOINT);
  ASSERT(top_point->p3_flags & PF_ORIGPOINT);
  vector deltaVec = bot_point->p3_vecPreRot - top_point->p3_vecPreRot;
  vm_NormalizeVector(&deltaVec);

  // get the vector from the camera to the top point
  vector top = top_point->p3_vecPreRot - viewerPos;
  vm_NormalizeVector(&top);

  // calculate the vector out from the 'rod' that is facing the camera
  vector rodNorm;
  vm_CrossProduct(&rodNorm, &deltaVec, &top);
  vm_NormalizeVector(&rodNorm);

  // get the offset vector
  vector tempv = rodNorm * width;

  // setup the points
  int i, codesAND = 0xFF;
  for (i = 0; i < 4; ++i) {
    float scale = (i == 0 || i == 3) ? -1.0f : 1.0f;
    vector bbPt = ((i < 2) ? top_point->p3_vecPreRot : bot_point->p3_vecPreRot) + (tempv * scale);

    // initialize the point
    codesAND &= g3_RotatePoint(&pnts[i], &bbPt);
  }

  if (codesAND)
    return 0;

  return 1;
}

// Draws a thick lighting bolt from one area to another
// Velocity.x is how many times to saturate
// Velocity.y is how fast the lightning moves across the v component
// Velocity.z is how many times the effect is tiled across the v component
// If Billboard_info.texture is not zero, it does autotiling
void DrawVisThickLightning(vis_effect *vis) {
  // compute the corners of a rod.  fills in vertbuf.
  g3Point top_point, bot_point;
  g3Point pnts[4], *pntlist[4];

  g3_RotatePoint(&top_point, &vis->pos);
  g3_RotatePoint(&bot_point, &vis->end_pos);

  if (!GetBillboardCorners(pnts, &top_point, &bot_point, vis->billboard_info.width))
    return;

  vector line_norm = vis->end_pos - vis->pos;
  float line_mag = vm_GetMagnitudeFast(&line_norm);

  line_norm /= line_mag;

  if (line_mag < 1)
    return;

  int texnum = vis->custom_handle;
  int bm_handle = GetTextureBitmap(texnum, 0, true);
  float tile_factor = vis->velocity.z;
  float alpha_norm;
  int i, codes_and;

  if (vis->flags & VF_EXPAND)
    alpha_norm = vis->lifeleft / vis->lifetime;
  else
    alpha_norm = .7f;

  rend_SetOverlayType(OT_NONE);
  rend_SetTextureType(TT_LINEAR);
  rend_SetLighting(LS_FLAT_GOURAUD);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetWrapType(WT_WRAP);
  rend_SetFlatColor(GR_16_TO_COLOR(vis->lighting_color));
  rend_SetAlphaValue(255 * alpha_norm);
  rend_SetZBufferWriteMask(0);

  for (i = 0, codes_and = 0xff; i < 4; i++) {
    pntlist[i] = &pnts[i];
  }

  if (vis->billboard_info.texture) // do autotiling
  {
    float ratio = line_mag / (float)vis->billboard_info.width;
    tile_factor *= ratio;
  }

  pnts[0].p3_u = 0;
  pnts[0].p3_v = 0;

  pnts[1].p3_u = 1;
  pnts[1].p3_v = 0;

  pnts[2].p3_u = 1;
  pnts[2].p3_v = tile_factor;

  pnts[3].p3_u = 0;
  pnts[3].p3_v = tile_factor;

  float vchange = 0;

  if (vis->velocity.y != 0) {
    int int_time = Gametime / vis->velocity.y;
    float norm_time = Gametime - (int_time * vis->velocity.y);
    norm_time /= vis->velocity.y;

    vchange = norm_time;
  }

  for (i = 0; i < 4; i++) {
    pnts[i].p3_v += vchange;
    pnts[i].p3_flags |= PF_UV;
  }

  // Now draw this thing!
  for (i = 0; i < vis->velocity.x; i++) {
    g3_DrawPoly(4, pntlist, bm_handle);
  }

  rend_SetZBufferWriteMask(1);
}

// Draws a bitmap that can orient around an axis
void DrawVisAxisBillboard(vis_effect *vis) {
  float norm_time, alpha_norm = 1;
  float uchange = 0, vchange = 0;
  float time_live = Gametime - vis->creation_time;
  float size = vis->size;

  int visnum = vis - VisEffects;
  int bm_handle;
  int i;

  // Get corners of this billboard
  g3Point top_point, bot_point;
  g3Point pnts[4], *pntlist[4];

  g3_RotatePoint(&top_point, &vis->pos);
  g3_RotatePoint(&bot_point, &vis->end_pos);

  if (!GetBillboardCorners(pnts, &top_point, &bot_point, vis->billboard_info.width))
    return;

  for (i = 0; i < 4; i++) {
    pnts[i].p3_flags |= PF_UV;
    pntlist[i] = &pnts[i];
  }

  fireball *fb = &Fireballs[vis->id];

  norm_time = time_live / vis->lifetime;

  if (vis->flags & VF_EXPAND)
    alpha_norm = vis->lifeleft / vis->lifetime;

  if (norm_time >= 1)
    norm_time = 0.99999f; // don't go over!

  if (vis->billboard_info.texture) // If its a texture, get image from texture
  {
    int texnum = vis->custom_handle;
    if (GameTextures[texnum].flags & TF_ANIMATED) {
      vclip *vc = &GameVClips[GameTextures[texnum].bm_handle];
      int int_frame = vc->num_frames * norm_time;
      bm_handle = vc->frames[int_frame];
    } else
      bm_handle = GetTextureBitmap(texnum, 0);

    if (GameTextures[texnum].flags & TF_SATURATE)
      rend_SetAlphaType(AT_SATURATE_TEXTURE);
    else
      rend_SetAlphaType(ATF_CONSTANT + ATF_TEXTURE);

    rend_SetAlphaValue(alpha_norm * GameTextures[texnum].alpha * 255);

    if (GameTextures[texnum].slide_u != 0) {
      int int_time = Gametime / GameTextures[texnum].slide_u;
      float norm_time = Gametime - (int_time * GameTextures[texnum].slide_u);
      norm_time /= GameTextures[texnum].slide_u;

      uchange = norm_time;
    }

    if (GameTextures[texnum].slide_v != 0) {
      int int_time = Gametime / GameTextures[texnum].slide_v;
      float norm_time = Gametime - (int_time * GameTextures[texnum].slide_v);
      norm_time /= GameTextures[texnum].slide_v;
      vchange = norm_time;
    }
  } else {
    bm_handle = vis->custom_handle;
    rend_SetAlphaType(ATF_CONSTANT + ATF_TEXTURE);
    rend_SetAlphaValue(alpha_norm * 255);
  }

  rend_SetOverlayType(OT_NONE);

  rend_SetZBufferWriteMask(0);

  if (uchange == 0 && vchange == 0)
    rend_SetWrapType(WT_CLAMP);
  else
    rend_SetWrapType(WT_WRAP);

  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetTextureType(TT_LINEAR);

  pnts[0].p3_u = 0;
  pnts[0].p3_v = 0;

  pnts[1].p3_u = 1;
  pnts[1].p3_v = 0;

  pnts[2].p3_u = 1;
  pnts[2].p3_v = 1;

  pnts[3].p3_u = 0;
  pnts[3].p3_v = 1;

  for (i = 0; i < 4; i++) {
    pnts[i].p3_u += uchange;
    pnts[i].p3_v += vchange;
  }

  g3_DrawPoly(4, pntlist, bm_handle);

  rend_SetZBufferWriteMask(1);

  rend_SetWrapType(WT_WRAP);
}

// Draws a bitmap that can orient around an axis
void DrawVisBillboardSmoketrail(vis_effect *vis) {
  float norm_time, alpha_norm = 1;
  float uchange = 0, vchange = 0;
  float time_live = Gametime - vis->creation_time;
  float size = vis->size;

  int visnum = vis - VisEffects;
  int bm_handle;

  // Get corners of this billboard
  g3Point top_point, bot_point;
  g3Point pnts[4], *pntlist[4];

  g3_RotatePoint(&top_point, &vis->pos);
  g3_RotatePoint(&bot_point, &vis->end_pos);

  norm_time = time_live / vis->lifetime;
  alpha_norm = vis->lifeleft / vis->lifetime;
  float width = vis->billboard_info.width * alpha_norm;

  if (alpha_norm > 0.8f) {
    // Make this smoke puff a bit smaller at the beginning of its life
    float newnorm = 1.0f - ((alpha_norm - 0.8f) / 0.2f);
    width *= newnorm;
  }

  alpha_norm *= 0.7f;

  if (!GetBillboardCorners(pnts, &top_point, &bot_point, width))
    return;

  fireball *fb = &Fireballs[vis->id];

  for (int i = 0; i < 4; i++) {
    pnts[i].p3_flags |= PF_UV | PF_RGBA;
    pntlist[i] = &pnts[i];
    pnts[i].p3_a = alpha_norm;
  }

  if (norm_time >= 1)
    norm_time = 0.99999f; // don't go over!

  int texnum = vis->custom_handle;
  if (GameTextures[texnum].flags & TF_ANIMATED) {
    vclip *vc = &GameVClips[GameTextures[texnum].bm_handle];
    int int_frame = vc->num_frames * norm_time;
    bm_handle = vc->frames[int_frame];
  } else
    bm_handle = GetTextureBitmap(texnum, 0);

  if (GameTextures[texnum].flags & TF_SATURATE)
    rend_SetAlphaType(AT_SATURATE_TEXTURE_VERTEX);
  else
    rend_SetAlphaType(AT_TEXTURE_VERTEX);

  rend_SetOverlayType(OT_NONE);

  rend_SetZBufferWriteMask(0);

  rend_SetFlatColor(GR_16_TO_COLOR(vis->lighting_color));
  rend_SetColorModel(CM_MONO);
  rend_SetTextureType(TT_LINEAR);
  rend_SetLighting(LS_FLAT_GOURAUD);

  pnts[0].p3_u = 0;
  pnts[0].p3_v = 0;

  pnts[1].p3_u = 1;
  pnts[1].p3_v = 0;

  pnts[2].p3_u = 1;
  pnts[2].p3_v = 1;

  pnts[3].p3_u = 0;
  pnts[3].p3_v = 1;

  g3_DrawPoly(4, pntlist, bm_handle);

  rend_SetZBufferWriteMask(1);
}

// Draws a long "stick" to represent the mass driver trail
void DrawVisMassDriverEffect(vis_effect *vis, bool f_boss) {
  int i, t, k;
  static int masstrail = -1;

  if (masstrail == -1)
    masstrail = FindTextureName("MassTrail");
  ASSERT(masstrail != -1); // DAJ -1FIX

  vector center_vecs[2];
  g3Point arc_points[32], *pntlist[32];

  center_vecs[0] = vis->pos;
  center_vecs[1] = vis->end_pos;

  vector normvec = center_vecs[1] - center_vecs[0];
  matrix orient;

  vm_NormalizeVector(&normvec);
  vm_VectorToMatrix(&orient, &normvec, NULL, NULL);

  float size = ((float)vis->billboard_info.width) * .25;
  int circle_pieces = 16;

  if (f_boss) {
    size *= 3.0f;
  }

  float mag = vm_VectorDistanceQuick(&vis->pos, &vis->end_pos);
  vector dir_norm = (vis->end_pos - vis->pos) / mag;
  float alpha_norm = (vis->lifeleft / vis->lifetime) * .5;
  int bm_handle = GetTextureBitmap(vis->custom_handle, 0);

  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetOverlayType(OT_NONE);
  rend_SetTextureType(TT_LINEAR);
  rend_SetLighting(LS_FLAT_GOURAUD);
  rend_SetZBufferWriteMask(0);
  if (f_boss)
    rend_SetFlatColor(GR_RGB(255, 170, 170));
  else
    rend_SetFlatColor(GR_RGB(200, 200, 255));

  rend_SetAlphaValue(255 * alpha_norm);

  for (i = 0; i < 2; i++) {
    for (t = 0; t < circle_pieces; t++) {
      float norm = (float)t / (float)circle_pieces;
      vector arc_vec = center_vecs[i];

      arc_vec += (orient.uvec * (size / 4) * FixSin(norm * 65536));
      arc_vec -= (orient.rvec * (size / 4) * FixCos(norm * 65536));

      g3_RotatePoint(&arc_points[i * circle_pieces + t], &arc_vec);
      arc_points[i * circle_pieces + t].p3_flags |= PF_UV | PF_RGBA;
    }
  }

  for (k = 0; k < circle_pieces; k++) {
    int next = (k + 1) % circle_pieces;
    arc_points[k].p3_u = 0;
    arc_points[k].p3_v = mag / 2;

    arc_points[k + circle_pieces].p3_u = 0;
    arc_points[k + circle_pieces].p3_v = 0;

    arc_points[next + circle_pieces].p3_u = 1;
    arc_points[next + circle_pieces].p3_v = 0;

    arc_points[next].p3_u = 1;
    arc_points[next].p3_v = mag / 2;

    pntlist[0] = &arc_points[t + k];
    pntlist[1] = &arc_points[t + k - circle_pieces];
    pntlist[2] = &arc_points[t + next - circle_pieces];
    pntlist[3] = &arc_points[t + next];

    g3_DrawPoly(4, pntlist, bm_handle);
  }

  for (i = 0; i < 2; i++) {
    for (t = 0; t < circle_pieces; t++) {
      float norm = (float)t / (float)circle_pieces;
      vector arc_vec = center_vecs[i];

      arc_vec += (orient.uvec * (size)*FixSin(norm * 65536));
      arc_vec -= (orient.rvec * (size)*FixCos(norm * 65536));

      g3_RotatePoint(&arc_points[i * circle_pieces + t], &arc_vec);
      arc_points[i * circle_pieces + t].p3_flags |= PF_UV;
    }
  }

  rend_SetFlatColor(GR_16_TO_COLOR(vis->lighting_color));
  rend_SetAlphaValue(255 * alpha_norm);

  for (k = 0; k < circle_pieces; k++) {
    int next = (k + 1) % circle_pieces;
    arc_points[k].p3_u = 0;
    arc_points[k].p3_v = mag / 2;

    arc_points[k + circle_pieces].p3_u = 0;
    arc_points[k + circle_pieces].p3_v = 0;

    arc_points[next + circle_pieces].p3_u = 1;
    arc_points[next + circle_pieces].p3_v = 0;

    arc_points[next].p3_u = 1;
    arc_points[next].p3_v = mag / 2;

    pntlist[0] = &arc_points[t + k];
    pntlist[1] = &arc_points[t + k - circle_pieces];
    pntlist[2] = &arc_points[t + next - circle_pieces];
    pntlist[3] = &arc_points[t + next];

    if (!g3_DrawPoly(4, pntlist, bm_handle))
      return;
  }

  // Now draw some rings
  int rings = mag / 3;
  float fsize = 3;

  if (rings > 400) {
    rings = 400;
    fsize = mag / 400.0;
  }

  rend_SetLighting(LS_NONE);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetAlphaValue(255 * alpha_norm);

  bm_handle = GetTextureBitmap(masstrail, 0);

  int int_gametime = Gametime;
  int frameroll = (Gametime - int_gametime) * -(65536 * 4);

  if (!f_boss) {
    for (i = 1; i < rings; i++) {
      int rot_angle = (i * 2000) % 65536;
      vector pos = vis->pos + (dir_norm * (i * fsize));
      float new_size = 1.0;
      new_size += FixSin((i * 9000) + frameroll) * .3;

      g3_DrawPlanarRotatedBitmap(&pos, &dir_norm, rot_angle, new_size,
                                 (new_size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
    }
  }
  rend_SetZBufferWriteMask(1);
}

// Renders a vis effect
void DrawVisEffect(vis_effect *vis) {
  ASSERT(vis->type != VIS_NONE);

  // First check to see if these are special types

  if (vis->id == LIGHTNING_BOLT_INDEX || vis->id == GRAY_LIGHTNING_BOLT_INDEX) {
    DrawVisLightningBolt(vis);
    return;
  } else if (vis->id == MASSDRIVER_EFFECT_INDEX) {
    DrawVisMassDriverEffect(vis, false);
    return;
  } else if (vis->id == MERCBOSS_MASSDRIVER_EFFECT_INDEX) {
    DrawVisMassDriverEffect(vis, true);
    return;
  } else if (vis->id == BILLBOARD_SMOKETRAIL_INDEX) {
    DrawVisBillboardSmoketrail(vis);
    return;
  } else if (vis->id == THICK_LIGHTNING_INDEX) {
    DrawVisThickLightning(vis);
    return;
  } else if (vis->id == SINE_WAVE_INDEX) {
    DrawVisSineWave(vis);
    return;
  } else if (vis->id == BLAST_RING_INDEX) {
    DrawVisBlastRing(vis);
    return;
  } else if (vis->id == FADING_LINE_INDEX) {
    DrawVisFadingLine(vis);
    return;
  } else if (vis->id == SNOWFLAKE_INDEX) {
    DrawVisSnowflake(vis);
    return;
  } else if (vis->id == RAINDROP_INDEX || vis->id == PUDDLEDROP_INDEX) {
    DrawVisRainDrop(vis);
    return;
  } else if (vis->id == AXIS_BILLBOARD_INDEX) {
    DrawVisAxisBillboard(vis);
    return;
  }

  float norm_time;
  float time_live = Gametime - vis->creation_time;

  // This hack is needed for the demo system and Gamegauge, since it adjusts gametime during
  // the game there are times when this could be a negative number (which would be bad)
  if (time_live < 0)
    time_live = 0;

  float size = vis->size;

  // Bigger explosions for Katmai
  if (Katmai) {
    if (vis->id == BIG_EXPLOSION_INDEX || vis->id == MED_EXPLOSION_INDEX || vis->id == MED_EXPLOSION_INDEX2 ||
        vis->id == MED_EXPLOSION_INDEX3)
      size *= 1.8f;
  }

  int visnum = vis - VisEffects;
  int rot_angle;
  int bm_handle;

  fireball *fb = &Fireballs[vis->id];

  if (fb->type == FT_BILLOW)
    rot_angle = ((visnum * 5000) + (FrameCount * 160)) % 65536;
  else if (vis->flags & VF_ATTACHED)
    rot_angle = 0;
  else if (vis->id == RUBBLE1_INDEX || vis->id == RUBBLE2_INDEX)
    rot_angle = ((visnum * 5000) + (FrameCount * 860)) % 65536;
  else if (vis->id == SUN_CORONA_INDEX) {
    rot_angle = ((visnum * 5000) + (FrameCount * 500)) % 65536;
    size *= 1.0 + ((rand() % 10) / 100);
  } else
    rot_angle = (visnum * 5000) % 65536;

  norm_time = time_live / vis->lifetime;

  // TEMP!!
  if (vis->flags & VF_ATTACHED) {
    int int_time_live = time_live;
    norm_time = time_live - int_time_live;
  }

  if (norm_time >= 1)
    norm_time = .99999f; // don't go over!

  if (vis->flags & VF_EXPAND) {
    size = (vis->size / 2) + ((vis->size * norm_time) / 2);
  }

  if (vis->id == SMOKE_TRAIL_INDEX) // If its a smoke trail, get image from texture
  {
    int texnum = vis->custom_handle;
    if (GameTextures[texnum].flags & TF_ANIMATED) {
      vclip *vc = &GameVClips[GameTextures[texnum].bm_handle];
      int int_frame = vc->num_frames * norm_time;
      bm_handle = vc->frames[int_frame];
    } else
      bm_handle = GameTextures[texnum].bm_handle;
  } else if (vis->id == SPRAY_INDEX) {
    int vnum = vis->custom_handle;
    vclip *vc = &GameVClips[vnum];
    int int_frame = vc->num_frames * norm_time;
    bm_handle = vc->frames[int_frame];

    //	if (norm_time<.5)
    // size=1+((vis->size-1)*(norm_time));
  } else if (vis->id == CUSTOM_EXPLOSION_INDEX || vis->id == PARTICLE_INDEX) // Do custom
  {
    if ((GameTextures[vis->custom_handle].flags & TF_ANIMATED)) {
      int vnum = GameTextures[vis->custom_handle].bm_handle;
      vclip *vc = &GameVClips[vnum];
      int int_frame = vc->num_frames * norm_time;
      bm_handle = vc->frames[int_frame];
    } else
      bm_handle = GetTextureBitmap(vis->custom_handle, 0);
  } else if (fb->type == FT_SPARK) // Do spark
  {
    bm_handle = fb->bm_handle;
    size *= (1.0 - norm_time);

  } else if (vis->id == SUN_CORONA_INDEX || vis->id == MUZZLE_FLASH_INDEX || vis->id == RUBBLE1_INDEX ||
             vis->id == RUBBLE2_INDEX) {
    bm_handle = fb->bm_handle;
  } else {
    vclip *vc = &GameVClips[fb->bm_handle];
    int int_frame = vc->num_frames * norm_time;
    bm_handle = vc->frames[int_frame];
  }

  if (fb->type == FT_SMOKE) {
    if (norm_time > .3) {
      float temp_time = (norm_time - .3);
      temp_time /= .7f;

      if (vis->flags & VF_REVERSE)
        size /= (1 + (temp_time * 2.3));
      else
        size *= (1 + (temp_time * 2.3));
    }
  }

  // Set some alpha
  if (vis->id == SMOKE_TRAIL_INDEX || vis->id == CUSTOM_EXPLOSION_INDEX || vis->id == PARTICLE_INDEX) {
    if (GameTextures[vis->custom_handle].flags & TF_SATURATE)
      rend_SetAlphaType(AT_SATURATE_TEXTURE);
    else
      rend_SetAlphaType(ATF_CONSTANT + ATF_TEXTURE);
  } else if (vis->id == BLACK_SMOKE_INDEX) {
    rend_SetAlphaType(AT_LIGHTMAP_BLEND);
  } else if ((fb->type == FT_SMOKE && vis->id != MED_SMOKE_INDEX) || vis->id == RUBBLE1_INDEX ||
             vis->id == RUBBLE2_INDEX) {
    rend_SetAlphaType(ATF_CONSTANT + ATF_TEXTURE);
  } else
    rend_SetAlphaType(AT_SATURATE_TEXTURE);

  float val;
  if (norm_time > .5)
    val = 1.0 - ((norm_time - .5) / .5);
  else
    val = 1.0;

  // Cap size
  if (size > MAX_FIREBALL_SIZE)
    size = MAX_FIREBALL_SIZE;
  if ((vis->id != BIG_EXPLOSION_INDEX && vis->id != BLUE_EXPLOSION_INDEX) && size > (MAX_FIREBALL_SIZE / 2))
    size = MAX_FIREBALL_SIZE / 2;

  if (vis->id == SMOKE_TRAIL_INDEX || vis->id == CUSTOM_EXPLOSION_INDEX || vis->id == PARTICLE_INDEX)
    rend_SetAlphaValue(val * GameTextures[vis->custom_handle].alpha * 255);
  else if (fb->type == FT_SMOKE)
    rend_SetAlphaValue(val * SMOKE_ALPHA * 255);
  else if (vis->id == RUBBLE1_INDEX || vis->id == RUBBLE2_INDEX)
    rend_SetAlphaValue(255);
  else if (vis->id == MUZZLE_FLASH_INDEX)
    rend_SetAlphaValue(128);
  else if (vis->flags & VF_ATTACHED)
    rend_SetAlphaValue(FIREBALL_ALPHA * 255);
  else
    rend_SetAlphaValue(val * FIREBALL_ALPHA * 255);

  rend_SetOverlayType(OT_NONE);

  if (!(vis->flags & VF_NO_Z_ADJUST))
    rend_SetZBias(-size);

  rend_SetZBufferWriteMask(0);
  rend_SetWrapType(WT_CLAMP);
  rend_SetLighting(LS_NONE);

  // Draw!!
  if (vis->id == RUBBLE1_INDEX || vis->id == RUBBLE2_INDEX || vis->id == GRAY_SPARK_INDEX) {
    int color = GR_16_TO_COLOR(vis->lighting_color);
    g3_DrawRotatedBitmap(&vis->pos, rot_angle, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle,
                         color);
  } else {
    if (vis->flags & VF_PLANAR)
      g3_DrawPlanarRotatedBitmap(&vis->pos, &vis->end_pos, rot_angle, size,
                                 (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
    else
      g3_DrawRotatedBitmap(&vis->pos, rot_angle, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
  }

  rend_SetZBias(0.0f);
  rend_SetZBufferWriteMask(1);

  rend_SetWrapType(WT_WRAP);
}

void VisEffectSetDeadFlag(vis_effect *vis) {
  if (vis->flags & VF_DEAD)
    return;
  if (vis->type == VIS_NONE)
    return;

  vis->flags |= VF_DEAD;

  VisDeadList[NumVisDead++] = vis - VisEffects;
}

// Moves
void VisEffectMoveOne(vis_effect *vis) {
  if (vis->flags & VF_USES_LIFELEFT)
    vis->lifeleft -= Frametime; //...inevitable countdown towards death

  // Chris, do your stuff here
  if (vis->movement_type == MT_PHYSICS)
    do_vis_physics_sim(vis);

  if (vis->flags & VF_USES_LIFELEFT) {
    if (vis->lifeleft < 0)
      VisEffectSetDeadFlag(vis);
  }

  if (vis->id == SNOWFLAKE_INDEX) {
    Weather.snowflakes_to_create++;

    vis->pos += vis->velocity * Frametime;

    if (vis->pos.y < 1)
      VisEffectSetDeadFlag(vis);
  }

  // Do attached viseffect stuff here
  if (vis->flags & VF_ATTACHED) {
    int objnum = vis->attach_info.obj_handle & HANDLE_OBJNUM_MASK;
    uint32_t sig = vis->attach_info.obj_handle & HANDLE_COUNT_MASK;
    object *obj = &Objects[objnum];

    if ((obj->flags & OF_DEAD) || (obj->handle & HANDLE_COUNT_MASK) != sig) {
      // The object we're attached to doesn't exist anymore
      VisEffectSetDeadFlag(vis);

    } else if (obj->type == OBJ_PLAYER && (Players[obj->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
      // The object we're attached to doesn't exist anymore
      VisEffectSetDeadFlag(vis);
    } else {
      if (vis->id == THICK_LIGHTNING_INDEX) {
        if (vis->flags & VF_PLANAR) {
          // Do object to object attachment
          int dest_objnum = vis->attach_info.dest_objhandle & HANDLE_OBJNUM_MASK;
          uint32_t dest_sig = vis->attach_info.dest_objhandle & HANDLE_COUNT_MASK;
          object *dest_obj = &Objects[dest_objnum];

          if ((dest_obj->flags & OF_DEAD) || (dest_obj->handle & HANDLE_COUNT_MASK) != dest_sig) {
            // The object we're attached to doesn't exist anymore
            VisEffectSetDeadFlag(vis);
            return;
          }

          if (dest_obj->type == OBJ_PLAYER &&
              (Players[dest_obj->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
            VisEffectSetDeadFlag(vis);
            return;
          }

          vis->pos = obj->pos;
          vis->end_pos = dest_obj->pos;

          // If were are shooting to the exact center of the viewer object then move
          // the positions a little bit or it will look wrong:
          if (obj == Viewer_object) {
            vis->pos -= (obj->orient.uvec * .1f);
          }

          if (dest_obj == Viewer_object) {
            vis->end_pos -= (dest_obj->orient.uvec * .1f);
          }

        } else {
          if (obj->rtype.pobj_info.model_num != vis->attach_info.modelnum) {
            VisEffectSetDeadFlag(vis);
          } else {
            WeaponCalcGun(&vis->pos, NULL, obj, vis->attach_info.vertnum);
            WeaponCalcGun(&vis->end_pos, NULL, obj, vis->attach_info.end_vertnum);
          }
        }
      } else {
        float normalized_time[MAX_SUBOBJECTS];

        if (obj->lowest_attached_vis == -1) {
          obj->lowest_attached_vis = vis - VisEffects;
          poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];

          int i;

          SetNormalizedTimeObj(obj, normalized_time);
          SetModelAngles(pm, normalized_time);
          SetModelInterpPos(pm, normalized_time);

          for (i = vis - VisEffects; i <= Highest_vis_effect_index; i++) {
            vis_effect *this_vis = &VisEffects[i];
            if (this_vis->type != VIS_NONE && (this_vis->flags & VF_ATTACHED) &&
                ((this_vis->attach_info.obj_handle & HANDLE_OBJNUM_MASK) == objnum) &&
                this_vis->id != THICK_LIGHTNING_INDEX) {
              bsp_info *sm = &pm->submodel[this_vis->attach_info.subnum];
              GetPolyModelPointInWorld(&this_vis->pos, pm, &obj->pos, &obj->orient, this_vis->attach_info.subnum,
                                       normalized_time, &sm->verts[this_vis->attach_info.vertnum], NULL);

              if (this_vis->attach_info.end_vertnum != -1)
                GetPolyModelPointInWorld(&this_vis->end_pos, pm, &obj->pos, &obj->orient, this_vis->attach_info.subnum,
                                         normalized_time, &sm->verts[this_vis->attach_info.end_vertnum], NULL);
            }
          }
        }
      }

      // Relink if need be
      if (obj->roomnum != vis->roomnum)
        VisEffectRelink(vis - VisEffects, obj->roomnum);
    }
  }

  // Do vis effect explosion lighting
  if (Detail_settings.Dynamic_lighting && vis->lighting_color != 0 && (vis->lighting_color & OPAQUE_FLAG) &&
      (vis->flags & VF_USES_LIFELEFT) && !(vis->flags & VF_DEAD)) {
    float scalar;

    scalar = (vis->lifetime - vis->lifeleft) / vis->lifetime;

    if (scalar > .5) {
      scalar -= .5;

      scalar = 1.0 - (scalar / .5);
    } else {
      scalar *= 2;
    }

    if (scalar > .05) {
      int color = GR_16_TO_COLOR(vis->lighting_color);
      float r = (GR_COLOR_RED(color)) / 255.0;
      float g = (GR_COLOR_GREEN(color)) / 255.0;
      float b = (GR_COLOR_BLUE(color)) / 255.0;

      if (ROOMNUM_OUTSIDE(vis->roomnum)) {
        int cellnum = CELLNUM(vis->roomnum);

        if (cellnum >= 0 && cellnum < TERRAIN_WIDTH * TERRAIN_DEPTH)
          ApplyLightingToTerrain(&vis->pos, cellnum, vis->size * scalar * 3, r, g, b);
        else
          mprintf(0, "Vis effect not in world!\n");
      } else {
        if (vis->roomnum >= 0 && vis->roomnum <= Highest_room_index && Rooms[vis->roomnum].used)
          ApplyLightingToRooms(&vis->pos, vis->roomnum, vis->size * scalar * 3, r, g, b);
      }
    }
  }

  // Link this effect to the viewer if needed
  if (vis->flags & VF_LINK_TO_VIEWER) {
    if (vis->roomnum != Viewer_object->roomnum) {
      VisEffectRelink(vis - VisEffects, Viewer_object->roomnum);
    }
  }
}

// Moves our visuals
void VisEffectMoveAll() {
  int i;

  for (i = 0; i <= Highest_vis_effect_index; i++) {
    if (VisEffects[i].type != VIS_NONE)
      VisEffectMoveOne(&VisEffects[i]);
  }
}

/*
// Attaches viseffects that move with an object
void AttachRandomVisEffectsToObject (int num,int handle,object *obj)
{
        int i;
        vector zero_pos={0,0,0};
        poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];



        for (i=0;i<num;i++)
        {

                int visnum=VisEffectCreate(VIS_FIREBALL,NAPALM_BALL_INDEX,obj->roomnum,&zero_pos);
                if (visnum>=0)
                {
                        vis_effect *vis=&VisEffects[visnum];
                        vis->size=1.0;
                        vis->lifetime=15.0;
                        vis->lifeleft=15.0;
                        vis->flags |=VF_ATTACHED;
                        vis->attach_info.obj_handle=obj->handle;

                        int subnum=ps_rand()%pm->n_models;
                        bsp_info *sm=&pm->submodel[subnum];

                        vis->attach_info.subnum=subnum;
                        vis->attach_info.vertnum=ps_rand()%sm->nverts;

                }
        }
}*/

// Attaches viseffects that move with an object
void AttachRandomNapalmEffectsToObject(object *obj) {
  if (obj->flags & OF_DEAD)
    return;

  vector velocity_norm = obj->mtype.phys_info.velocity;
  vm_NormalizeVector(&velocity_norm);
  vector pos = obj->pos - (velocity_norm * (obj->size / 2));

  if (obj->movement_type == MT_PHYSICS && (OBJECT_OUTSIDE(obj) && (ps_rand() % 3) == 0) || (ps_rand() % 3) == 0)
    CreateFireball(&pos, BLACK_SMOKE_INDEX, obj->roomnum, VISUAL_FIREBALL);

  float size_scalar = obj->size / 7.0;

  size_scalar = std::clamp(size_scalar, 1.0f, 4.0f);

  // Create an explosion that follows every now and then
  if ((ps_rand() % 3) == 0) {
    if (!(obj->flags & OF_POLYGON_OBJECT))
      return;

    int num = 1;

    num += (obj->size / 15);

    for (int i = 0; i < num; i++) {
      vector dest;
      poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];

      if (pm->n_models == 0)
        return;

      int subnum = ps_rand() % pm->n_models;

      if (IsNonRenderableSubmodel(pm, subnum))
        continue;

      bsp_info *sm = &pm->submodel[subnum];

      if (sm->nverts == 0)
        return;

      int vertnum = ps_rand() % sm->nverts;

      GetPolyModelPointInWorld(&dest, &Poly_models[obj->rtype.pobj_info.model_num], &obj->pos, &obj->orient, subnum,
                               &sm->verts[vertnum]);
      int visnum = VisEffectCreate(VIS_FIREBALL, GetRandomSmallExplosion(), obj->roomnum, &dest);
      if (visnum == -1)
        return;

      VisEffects[visnum].size += ((ps_rand() % 20) / 20.0) * 1.0;

      VisEffects[visnum].size *= size_scalar;

      if ((ps_rand() % 2)) {
        if (obj->movement_type == MT_PHYSICS) {
          VisEffects[visnum].movement_type = MT_PHYSICS;
          VisEffects[visnum].velocity = obj->mtype.phys_info.velocity;
          VisEffects[visnum].mass = obj->mtype.phys_info.mass;
          VisEffects[visnum].drag = obj->mtype.phys_info.drag;
        }
      }
    }
  }
}
