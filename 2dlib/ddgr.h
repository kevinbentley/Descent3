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

 * $Logfile: /DescentIII/Main/lib/Ddgr.h $
 * $Revision: 6 $
 * $Date: 12/23/97 6:16p $
 * $Author: Samir $
 *
 * DDGR library interface header
 *
 * $Log: /DescentIII/Main/lib/Ddgr.h $
 *
 * 6     12/23/97 6:16p Samir
 * Moved ddgr_Close to header.
 *
 * 5     12/22/97 7:24p Samir
 * took out transparent color defs.
 *
 * 4     12/22/97 7:13p Samir
 * Moved constants to grdefs.h
 *
 * 3     9/12/97 4:13p Samir
 * Added some private data access functions.
 *
 * 1     6/23/97 9:25p Samir
 * added because source safe sucks
 *
 * 26    6/12/97 6:30p Samir
 * DDGR v2.0 Changes in 2d system implemented.
 *
 * 25    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 24    5/22/97 4:03p Samir
 * Hacked OpenGL stuff.  WILL CHANGE
 *
 * 23    5/15/97 2:08p Samir
 * Added 8-bit support and driver info structure.
 *
 * 22    3/28/97 3:07p Samir
 * Clear function now takes a color
 *
 * 21    3/27/97 11:11a Samir
 * Revised headers to reflect movement of functions from ddgr to 2dlib
 *
 * 20    3/26/97 7:44p Samir
 * Took out prototypes to unimplemented functions.
 *
 * 19    2/27/97 6:16p Samir
 * moved high level functions to 2dlib internal library
 *
 * 18    2/03/97 6:00p Jason
 * added 2d bitmap scaling functions
 *
 * 17    1/30/97 6:01p Samir
 * The partition of memory and os surfaces as well as the change in
 * ddgr_surface structure and all related changes.
 *
 * $NoKeywords: $
 */

#ifndef _DDGR_H
#define _DDGR_H

#include "grdefs.h"

//	----------------------------------------------------------------------------
//	DDGR
//		version 1.0						// DirectDraw, GDI support
//		version 2.x						// fullscreen-windowed remanagement.
//	----------------------------------------------------------------------------

//	----------------------------------------------------------------------------
//	Data structures
//	----------------------------------------------------------------------------

/*	Type definitions */

class oeApplication;

/*
        Diagnostic DDGR system types and functions
*/

struct ddgr_init_info {
  oeApplication *obj;  // the app object created by app calling
  char *subsystem;     // subsystem name (i.e. 'DirectDraw', 'GDI')
  uint16_t windowed : 1; // are we running in a fullscreen or windowed mode
  uint16_t debug : 1;    // are we running in debug mode?
};

/*	app = application object.
        subsystem = subsystem name ('DirectDraw', 'GDI')
        fullscreen = whether it's full screen or windowed
*/
bool ddgr_Init(oeApplication *app, char *subsystem, bool fullscreen);
void ddgr_Close();
void ddgr_GetSubsystem(char *name, bool *fullscreen);

//	returns aspect ratio of current display.
float ddgr_GetAspectRatio();

/*	Surface bit depths
                The bitdepth of the surface determines the color format of the surface.  Renderers
                should use this value to plot
*/

//	Green with all 6 bits set to 1 is our transparent color
//	default transparent color to 16bit, but all code should use the first 2 defines.

/*	Surface types
                Surfaces symbolize a flat 2d surface where pixels are lit.  Essentially, a surface could
                be a bitmap, but if it's the display, it's a bitmap managed by the video card.
                The goal of this library is to provide a clean, device-independent method to accessing
                surfaces.

        SURFTYPE_VIDEOSCREEN:
                The video screen is a physical or virtual display.
                When you create a videoscreen, you may specify either it is monopage or dualpage (backbuffer)
                When dualpage, the program can RENDER to the 1st page.  To update the video display, you
                must perform a surface flip.

        SURFTYPE_GENERIC:
                This is a generic bitmap managed by the operating system.  RENDERING is allowed.
 */
const int SURFTYPE_VIDEOSCREEN = 1, // This is equivical to the display.
    SURFTYPE_GENERIC = 2;           //	This is an offscreen bitmap.

/*	Surface flags
                Flags modify a surfaces behavior.  A surface may have a backbuffer, which is only really
                useful for videoscreens.

        SURFFLAG_BACKBUFFER:
                This surface has a backbuffer.
                        v2.0  Supported in only videoscreen surfaces.

        SURFFLAG_COLORKEY:
                This surface was created with colorkeying in mind.
                Renderers should keep this in mind, and check this flag.
 */
const int SURFFLAG_BACKBUFFER = 1, SURFFLAG_COLORKEY = 2;

/*	Surface structures
                The surface
*/
const int SURF_NAMELEN = 16;

struct ddgr_surface {
  void *obj;               // internal structure info to library
  char name[SURF_NAMELEN]; // name
  int w, h, bpp;           // width, height and bit depth
  uint16_t type;             // how driver handles this surface
  uint16_t flags;            // colorkeying, etc.
  int locks;               // lock count.
};

#if defined(WIN32)
/*
        ddraw_surf = true	if this is a true DirectDraw surface, false if a GDI surface
        object_ptr = DirectDraw object if ddraw_surf = true, a HDC if a GDI surface.
*/
void ddgr_surf_GetPrivateData(ddgr_surface *sf, bool *ddraw_surf, uint32_t *object_ptr);

//	you must typecase this return value to LPDIRECTDRAW
unsigned ddgr_GetDDrawObject();
#endif // WIN32

/*	Surface Functions
 */

/*	input:
                sf->name is optional.
                sf->w, sf->h, sf->bpp are mandatory
                sf->type and sf->flags are mandatory.
        output:
                sf->obj = surface object.
                sf->locks = 0
*/
bool ddgr_surf_Create(ddgr_surface *sf);
void ddgr_surf_Destroy(ddgr_surface *sf);

/*	retrieves a pointer to surface memory.  allowed to lock one surface multiple times.
                ptr is the returned pointer to surface memory.  used to unlock surface also
                rowsize is the size in bytes of one row of memory.
*/
bool ddgr_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize);
bool ddgr_surf_Unlock(ddgr_surface *sf, void *ptr);

//	attaches an OS handle to a surface
void ddgr_surf_AttachHandle(ddgr_surface *sf, unsigned handle);

/*	initializes a video screen from the given input surface which specifies the dimensions
        of the screen.
                sf->name is optional
                sf->w, sf->h are mandatory
                sf->bpp is recommended.  if set to BPP_DEFAULT, it uses the current display bit depth
                sf->type = SURFTYPE_VIDEOSCREEN
                sf->flags = 0 or SURFFLAG_BACKBUFFER.  surfaces with backbuffers allow rendering to
                                                them and display via flip.  monopage surfaces don't have this luxury.
*/
bool ddgr_surf_InitVideo(ddgr_surface *sf);

/*	close video reverses the operation of init video for that surface.  the display should stay
        the same, but no more operations may occur to that surface through this library.
*/
void ddgr_surf_CloseVideo(ddgr_surface *sf);

/*	flips the buffers in a surface.  really only useful for video screens
 */
bool ddgr_surf_FlipVideo(ddgr_surface *sf);

/*	graphic primatives
 */
void ddgr_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h);
bool ddgr_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);

/*
        8-bit palette surface structures
*/
struct ddgr_rgb {
  uint8_t r, g, b; // RGB triplet
  uint8_t x;       // reserved...
};

struct ddgr_palette {
  void *obj;         // internal object
  ddgr_rgb rgb[256]; // rgb values for palette.
};

//	attaches a palette to an 8-bit surface only.
bool ddgr_surf_AttachPalette(ddgr_surface *surf, ddgr_palette *pal);

//	grabs a palette.
bool ddgr_surf_GetPalette(ddgr_surface *surf, ddgr_palette *pal);

//	creates and destroys palette objects.
bool ddgr_8bit_CreatePalette(ddgr_palette *pal);
bool ddgr_8bit_DestroyPalette(ddgr_palette *pal);

//	loads a palette with specified entriyes
bool ddgr_8bit_LoadPalette(ddgr_palette *pal, int start, int count);

//	returns an index into the palette
int ddgr_8bit_FindClosestColor(ddgr_palette *pal, ddgr_color col);

#endif
