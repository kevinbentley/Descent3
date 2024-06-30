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

 * $Logfile: /DescentIII/main/fireball.h $
 * $Revision: 69 $
 * $Date: 10/12/99 11:01a $
 * $Author: Jeff $
 *
 * Header for fireball.cpp
 *
 * $Log: /DescentIII/main/fireball.h $
 *
 * 69    10/12/99 11:01a Jeff
 * added grey lightning
 *
 * 68    9/21/99 2:54p Jeff
 * added grey spark fireball (for multicolored sparks)
 *
 * 67    5/10/99 1:53a Jason
 * add blackshark explosion
 *
 * 66    4/23/99 12:29a Matt
 * Moved the code that plays an object's explosion sound into a function.
 *
 * 65    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 64    4/06/99 1:50p Jason
 * added new mass driver effect
 *
 * 63    4/05/99 4:39p Jason
 * added groovy new smoke trails
 *
 * 62    3/28/99 5:55p Matt
 * Added prototype
 *
 * 61    2/25/99 10:58a Matt
 * Added new explosion system.
 *
 * 60    2/09/99 2:39p Jason
 * added destroyable faces
 *
 * 59    1/26/99 6:39p Jason
 * added wall effects code
 *
 * 58    1/24/99 8:17p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 57    12/11/98 5:08p Jason
 * changed mass driver effect
 *
 * 56    11/19/98 6:37p Jason
 * made a better black shark effect
 *
 * 55    11/18/98 2:53p Jason
 * added snow effect
 *
 * 54    10/29/98 6:01p Jason
 * added multiple coronas
 *
 * 53    9/29/98 7:15p Jason
 * added axis billboards
 *
 * 52    9/29/98 12:49p Jason
 * worked on matcen effects and lightning
 *
 * 51    9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 50    9/09/98 4:28p Jason
 * added better weapon effects
 *
 * 49    8/17/98 10:48a Jason
 * added more lightning code
 *
 * 48    7/24/98 4:45p Jason
 * added DrawSphere
 *
 * 47    6/25/98 12:19p Jason
 * made gravity effect do different damage in single vs multiplayer
 *
 * 46    6/23/98 3:34p Jason
 * added cool lighting effect to gravity field
 *
 * 45    6/22/98 6:26p Jason
 * added gravity field effect for weapons
 *
 * 44    5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 43    4/30/98 6:45p Jason
 * more changes for weather
 *
 * 42    4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 41    4/29/98 11:38a Jason
 * added some weather effects (first pass)
 *
 * 40    4/17/98 12:45p Jason
 * various changes for multiplayer
 *
 * 39    4/15/98 3:28p Jason
 * changed glow stuff to work with new system
 *
 * 38    4/10/98 2:17p Jason
 * added afterburner fireball
 *
 * 37    4/07/98 3:31p Jason
 * got particle effects working with weapons
 *
 * 36    4/02/98 6:42p Jason
 * added blue blast ring effect
 *
 * 35    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 34    3/09/98 5:58p Jason
 * draw powerups with saturated alpha rings
 *
 * 33    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 32    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 */

#ifndef FIREBALL_H

#define FIREBALL_H

#include "fireball_external.h"
#include "object.h"
#include "vecmat.h"
#include "manage.h"
#include "grdefs.h"
#include "DeathInfo.h"

#define PARTICLE_LIFE .5
#define DEBRIS_LIFE 2.0

#define FF_MOVES 1

#define VISUAL_FIREBALL 0 // This fireball is for looks only
#define REAL_FIREBALL 1   // This fireball can actually burn things

// The alpha for a fireball
#define FIREBALL_ALPHA .9f
// Smoke alpha
#define SMOKE_ALPHA .3f

#define MAX_FIREBALL_SIZE 80.0

// The lifetime of the blast ring
#define DAMAGE_RING_TIME 1.5f

#define NUM_FIREBALLS 52

struct fireball {
  char name[PAGENAME_LEN]; // The filename of this animation

  uint8_t type;       // type of fireball, see above
  uint8_t tex_size;   // What size texture to use for this animation
  float total_life; // How long this animation should last (in seconds)
  float size;       // How big this explosion is
  int16_t bm_handle;  // The handle to the vlip
};

extern std::array<fireball, NUM_FIREBALLS> Fireballs;

// Initalizes the explosion system
void InitFireballs();

// Given an object, renders the representation of this fireball
void DrawFireballObject(object *obj);

// Creates a fireball
// Returns object number on success, else -1 on error
// If vis_effect is non-zero, then this is a visual effect only
int CreateFireball(vector *pos, int fireball_num, int roomnum, int realtype = VISUAL_FIREBALL);

// Creates a fireball vis effect for the specified object
// The explosion size is twice the object size times size_scale
// The fireball type will be randomly selected based on the object size times size_scale
// Returns the visnum of the fireball
int CreateObjectFireball(object *objp, float size_scale = 1.0);

// Control code for debris
void DoDebrisFrame(object *obj);

// Process a dying object for one frame
void DoDyingFrame(object *objp);

// A quick way to see where a weapon hits.  Weapons make debris.
void CreateWeaponDebris(object *obj);

// Creates a concussive blast (physics based -- no visuals)
void MakeShockwave(object *explode_obj_ptr, int parent_handle);

void DoConcussiveForce(object *explode_obj_ptr, int parent_handle, float player_scalar = 1);

// Creates a gravity field that sucks objects into it
extern int CreateGravityField(vector *pos, int roomnum, float size, float time, int parent_handle);

// Control code for explosions
void DoExplosionFrame(object *obj);

// Destroy an object immediately
void DestroyObject(object *objp, float explosion_mag, int death_flags);

// Creates a debris piece that goes off in a given direction, with a given magnitude
object *CreateSubobjectDebrisDirected(object *parent, int subobj_num, vector *dir, float explosion_mag,
                                      int death_flags = DF_DEBRIS_SMOKES);

//	Creates nifty splinters that shoot out from the body, I figure.
void CreateSplintersFromBody(object *obj, float explosion_mag, float lifetime);

// Creates a blast ring to be drawn
int CreateBlastRing(vector *pos, int index, float lifetime, float max_size, int roomnum, int force_blue = 0);

// Creates a standard blast ring for an object
int CreateObjectBlastRing(object *objp);

// Creates a smolding smoke to be drawn
int CreateSmolderingObject(vector *pos, int index, float lifetime, float max_size, int roomnum);

// Draws a blast ring
void DrawBlastRingObject(object *obj);

// Draws a colored alpha disk...useful for cool lighting effects
void DrawColoredDisk(vector *pos, float r, float g, float b, float inner_alpha, float outer_alpha, float size,
                     uint8_t saturate = 0, uint8_t lod = 1);

// Draws a colored alpha ring...useful for cool lighting effects
void DrawColoredRing(vector *pos, float r, float g, float b, float inner_alpha, float outer_alpha, float size,
                     float inner_ring_ratio, uint8_t saturate = 0, uint8_t lod = 1);

// Creates a blast ring from an event
void DoBlastRingEvent(int eventnum, void *data);

// Makes a fireball have a custom vclip
int CreateCustomFireballObject(vector *pos, int fireball_num, int tex_handle, int roomnum);

// Creates an explosion
void DoExplosionEvent(int eventnum, void *data);

// An event handler that simply draws an alpha blended poly on top of the screen
// Takes a 4 element array of floats int r,g,b,a format
void DrawAlphaEvent(int eventnum, void *data);

// Returns a random medium sized explosion
int GetRandomMediumExplosion();

// Returns a random small explosion
int GetRandomSmallExplosion();

// Returns a random small explosion
int GetRandomBillowingExplosion();

// Draws a sphere with the appropriate texture.  If texture=-1, then uses rgb as colors
void DrawSphere(vector *pos, float r, float g, float b, float alpha, float size, int texture, uint8_t saturate = 1);

// Creates end points that simulate lightning
void CreateLightningRodPositions(vector *src, vector *dest, vector *world_vecs, int num_segments, float rand_mag,
                                 bool do_flat);

// Draws a glowing cone of light using a bitmap
void DrawColoredGlow(vector *pos, float r, float g, float b, float size);

void CreateElectricalBolts(object *objp, int num_bolts);

// Play the explosion sound for this object
void PlayObjectExplosionSound(object *objp);

#endif
