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

 * $Logfile: /DescentIII/Main/gametexture.h $
 * $Revision: 47 $
 * $Date: 9/13/01 2:30p $
 * $Author: Matt $
 *
 * Header for gametexture.cpp
 *
 * $Log: /DescentIII/Main/gametexture.h $
 *
 * 47    9/13/01 2:30p Matt
 * Increased MAX_TEXTURES from 2800 to 3100.
 *
 * 46    3/21/00 1:17p Matt
 * Increased MAX_TEXTURES to 2800 for PC and Mac, so add-on developers
 * could add more of their own textures.
 *
 * 45    3/20/00 12:09p Matt
 * Merge of Duane's post-1.3 changes.
 * Lower MAX_TEXTURES for Mac (Mac only)
 *
 * 44    10/17/99 6:06p Chris
 * We ran out of texture handles...
 *
 * 43    5/05/99 5:03a Gwar
 * renamed ned_GameTextures array to GameTextures in new editor to make
 * game code happy; 3D texture view still does not display textures
 *
 * 42    4/30/99 12:56p Kevin
 * Lowered values for MAX_SOUNDS, MAX_ROOMS, MAX_TEXTURES and MAX_OBJIDS.
 * Talk to me before changing any of these again.
 *
 * 41    4/20/99 9:26p Matt
 * Added breakable flag for glass
 *
 * 40    4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 39    3/30/99 6:06p Jason
 * added new procedural effect
 *
 * 38    3/10/99 7:12p Jason
 * added smooth specular shading for curved surfaces
 *
 * 37    2/20/99 2:17p Matt
 * Added texture sounds
 *
 * 36    1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 35    1/26/99 4:04p Jason
 * added some more texture flags
 *
 * 34    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 33    12/23/98 4:59p Jason
 * some new texture features added
 *
 * 32    11/30/98 5:50p Jason
 * added 4444 bitmap support
 *
 * 31    10/07/98 5:03p Jason
 * more options for textures
 *
 * 30    10/01/98 2:47p Jason
 * added timed procedurals
 *
 * 29    8/31/98 1:35p Keneta
 * Made some use count unsigned shorts
 *
 * 28    8/13/98 11:57a Jason
 * added water procedurals
 *
 * 27    7/14/98 6:50p Jason
 * made procedurals save out to the table file
 *
 * 26    7/09/98 7:30p Jason
 * more procedural stuff
 *
 * 25    7/07/98 4:12p Jason
 * checkin for procedurals
 *
 * 24    7/06/98 12:55p Jason
 * added first pass at procedurals
 *
 * 23    6/10/98 12:21p Matt
 * Revamped system that controls what textures are displayed on the
 * texture tab.  Should work correctly now, and will now save the settings
 * to the registry.  Also, textures now default to no type set, not all
 * types set.
 *
 * 22    6/02/98 6:03p Jason
 * added specular lightmaps
 *
 * 21    5/20/98 5:44p Jason
 * incremental checkin for bumpmapping
 *
 * 20    5/20/98 1:08p Jason
 * more stuff for adding bumpmaps
 *
 * 19    5/19/98 3:19p Jason
 * cleaned up some texture flags
 *
 * 18    5/03/98 10:24p Matt
 * Renamed some unused constants
 *
 * 17    4/15/98 12:22p Jason
 * lots of miscellaneous stuff pertaining to lighting and vis effects
 *
 * 16    4/06/98 4:41p Jason
 * added texture alpha change
 *
 * 15    3/17/98 4:33p Jason
 * Added size changing to bitmaps/textures
 *
 * 14    2/13/98 12:40p Jason
 * added functions to touch all data in a level when the level is loaded
 *
 * 13    2/10/98 11:38a Matt
 * Ripped out the obsolete merge stuff
 *
 * 12    2/03/98 3:15p Jason
 * added the ability to specify saturation textures for models
 *
 * 11    1/13/98 3:09p Jason
 * added glow effect for engines
 *
 * 10    1/06/98 2:58p Mark
 * upped texture limit to 3000.
 *
 * 9     12/19/97 2:46p Jason
 * implemented bitmap paging routines
 *
 * 8     11/21/97 2:02p Jason
 * made light textures on model render that model face fully bright
 *
 * 7     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 6     8/19/97 1:57a Jason
 * made rgb lighting take floats
 *
 * 5     8/12/97 1:10a Jason
 * added code to support radiosity lighting
 *
 * 4     8/08/97 12:59p Jason
 * got texture sliding and pingponging working
 *
 * 3     8/05/97 4:27p Chris
 * Added two flags for fly thru and fly by
 *
 * 2     8/04/97 3:28p Jason
 * added alpha blending per texture
 *
 * 11    6/24/97 12:45p Jason
 * checked in for safety
 *
 * 9     6/06/97 3:57p Jason
 * implemented changes for small textures and automatic tmap2 recognition
 *
 * 8     5/30/97 5:46p Jason
 * added colored light functionality on a vertex level
 *
 * 7     5/23/97 7:07p Matt
 * Added code, data, & dialogs to keep track of what a texture is used for
 * (mine, terrain, object) so we can display in the texture dialog only
 * the ones we're interested in.
 *
 * $NoKeywords: $
 */

#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H
#include <array>

#ifdef NEWEDITOR /* only include tablefile header (manage stuff for NEWEDITOR) */
#include "..\neweditor\ned_TableFile.h"
#include "..\neweditor\ned_GameTexture.h"
#else

#include "manage.h"

#define TF_VOLATILE 1
#define TF_WATER (1 << 1)
#define TF_METAL (1 << 2)   // Shines like metal
#define TF_MARBLE (1 << 3)  // Shines like marble
#define TF_PLASTIC (1 << 4) // Shines like plastic
#define TF_FORCEFIELD (1 << 5)
#define TF_ANIMATED (1 << 6)
#define TF_DESTROYABLE (1 << 7)
#define TF_EFFECT (1 << 8)
#define TF_HUD_COCKPIT (1 << 9)
#define TF_MINE (1 << 10)
#define TF_TERRAIN (1 << 11)
#define TF_OBJECT (1 << 12)
#define TF_TEXTURE_64 (1 << 13)
#define TF_TMAP2 (1 << 14)
#define TF_TEXTURE_32 (1 << 15)
#define TF_FLY_THRU (1 << 16)
#define TF_PASS_THRU (1 << 17)
#define TF_PING_PONG (1 << 18)
#define TF_LIGHT (1 << 19)
#define TF_BREAKABLE (1 << 20) // Breakable (as in glass)
#define TF_SATURATE (1 << 21)
#define TF_ALPHA (1 << 22)
#define TF_DONTUSE (1 << 23)
#define TF_PROCEDURAL (1 << 24)
#define TF_WATER_PROCEDURAL (1 << 25)
#define TF_FORCE_LIGHTMAP (1 << 26)
#define TF_SATURATE_LIGHTMAP (1 << 27)
#define TF_TEXTURE_256 (1 << 28)
#define TF_LAVA (1 << 29)
#define TF_RUBBLE (1 << 30)
#define TF_SMOOTH_SPECULAR (1 << 31)

#define TF_TEXTURE_TYPES (TF_MINE + TF_TERRAIN + TF_OBJECT + TF_EFFECT + TF_HUD_COCKPIT + TF_LIGHT)

#define TF_SPECULAR (TF_METAL + TF_MARBLE | TF_PLASTIC)

#define NOT_TEXTURE 0
#define NORMAL_TEXTURE 1 // a normal size texture
#define SMALL_TEXTURE 2  // 1/4 of a normal texture
#define TINY_TEXTURE 3   // 1/8 of a normal texture
#define HUGE_TEXTURE 4   // Double the size of a normal texture

#define MAX_TEXTURES 3100

#define PROC_MEMORY_TYPE_NONE 0
#define PROC_MEMORY_TYPE_FIRE 1
#define PROC_MEMORY_TYPE_WATER 2

struct static_proc_element {
  uint8_t type;

  uint8_t frequency;
  uint8_t speed;
  uint8_t color;
  uint8_t size;

  uint8_t x1, y1, x2, y2;

};

struct proc_struct {
  int16_t dynamic_proc_elements; // list of dynamic procedural texture elements
  void *proc1;                 // pointer for procedural page
  void *proc2;                 // back page of procedural
  int16_t procedural_bitmap;     // handle to the bitmap holding the finished procedural

  uint16_t *palette;
  static_proc_element *static_proc_elements;
  uint16_t num_static_elements;

  uint8_t memory_type;

  uint8_t heat;
  uint8_t thickness;
  uint8_t light;

  float last_evaluation_time;
  float evaluation_time;
  float osc_time;
  uint8_t osc_value;

  int last_procedural_frame; // last frame a procedural was calculated for this texture
};

struct texture {
  char name[PAGENAME_LEN]; // this textures name
  int flags;               // values defined above
  int bm_handle;           // handle which shows what this texture looks like
  int destroy_handle;      // handle which denotes the destroyed image

  int damage;
  float reflectivity;
  float r, g, b; // colored lighting	 (0 to 100%)

  float slide_u, slide_v; // How many times this texture slides during a second
  float alpha;            // alpha value (from 0 to 1)
  float speed;            // how fast this texture animates

  proc_struct *procedural;

  int sound;          // The sound this texture makes
  float sound_volume; // The volume for this texture's sound

  int16_t bumpmap;     // The bumpmap for this texture, or -1 if there is none
  uint8_t corona_type; // what type of corona this thing uses
  uint8_t used;        // is this texture free to be allocated?

};

extern std::array<texture, MAX_TEXTURES> GameTextures;
extern int Num_textures;

// Inits the texture system, returning 1 if successful
int InitTextures();
void ShutdownTextures();

// Set aside a texture for use
int AllocTexture(void);

// Frees a texture for future use
void FreeTexture(int);

// Given current index, gets index of next texture in use
int GetNextTexture(int n);

// Given current index, gets index of prev texture in use
int GetPreviousTexture(int n);

// Searches thru all textures for a specific name, returns -1 if not found
// or index of texture with name
int FindTextureName(const char *name);

// Searches thru all textures for a bitmap of a specific name, returns -1 if not found
// or index of texture with name
int FindTextureBitmapName(const char *name);

// Given a texture handle, returns that textures bitmap
// If the texture is animated, returns framenum mod num_of_frames in the animation
int GetTextureBitmap(int handle, int framenum, bool force = false);

// Given a filename, loads either the bitmap or vclip found in that file.  If type
// is not NULL, sets it to 1 if file is animation, otherwise sets it to zero
int LoadTextureImage(const char *filename, int *type, int texture_size, int mipped, int pageable = 0, int format = 0);

// Goes through and marks a texture as a tmap2 if its bitmap(s) have transparency
bool CheckIfTextureIsTmap2(int texnum);

// Touches a texture, makes sure its in memory
void TouchTexture(int n);

// Builds the bumpmaps for the texture
void BuildTextureBumpmaps(int texhandle);

// Allocates the memory needed for static elements for a procedural texture
void AllocateStaticProceduralsForTexture(int handle, int num_elements);

// Frees the memory used by static procedural elements
void FreeStaticProceduralsForTexture(int handle);

// Frees all the procedural memory for a texture
void FreeProceduralForTexture(int n);

// Allocates memory for a procedural that is attached to a texture
int AllocateProceduralForTexture(int handle);

#endif

#endif
