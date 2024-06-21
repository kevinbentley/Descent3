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

 * $Logfile: /DescentIII/Main/renderer/renderer.cpp $
 * $Revision: 125 $
 * $Date: 4/19/00 5:24p $
 * $Author: Matt $
 *
 * Renderer abstraction layer
 *
 * $Log: /DescentIII/Main/renderer/renderer.cpp $
 *
 * 125   4/19/00 5:24p Matt
 * From Duane for 1.4
 * Removed ATI flag
 *
 * 124   3/20/00 12:31p Matt
 * Merge of Duane's post-1.3 changes.
 * Removed defines for Mac.
 *
 * 123   10/21/99 3:18p Kevin
 * Mac Merge
 *
 * 122   9/18/99 9:26p Jeff
 * added alpha factor (for overriding all alpha on polygons drawn)
 *
 * 121   7/29/99 2:01p Kevin
 *
 * 120   7/29/99 12:31p Kevin
 * Mac merge fixes
 *
 * 119   7/28/99 2:06p Kevin
 * Macintosh Changes
 *
 * 118   7/15/99 6:38p Jeff
 * created function to get rendering stats
 *
 * 117   6/24/99 8:13p Jeff
 * OpenGL added for Linux
 *
 * 116   6/22/99 7:04p Jeff
 * added Glide support for Linux
 *
 * 115   5/13/99 3:47p Ardussi
 * changes for compiling on the Mac
 *
 * 114   5/04/99 4:34p Jason
 * changes for bumpmapping
 *
 * 113   5/01/99 9:26p Kevin
 * ifdef should have been ifndef
 *
 * 112   5/01/99 4:56p Kevin
 * made critical renderer code do nothing in DEDICATED_ONLY builds
 *
 * 111   4/16/99 6:45p Kevin
 * removed ifdef demo
 *
 * 110   4/16/99 3:22a Jeff
 * added ifdefs to specify what renderers to compile in (initially for
 * linux use)
 *
 * 109   4/14/99 1:44a Jeff
 * fixed case mismatched #includes
 *
 * 108   4/13/99 4:59p Jason
 * changes for font renderings
 *
 * 107   4/02/99 3:02p Samir
 * rend_RetrieveDDrawProps modified so renderer none works.
 *
 * 106   4/01/99 10:56a Jason
 * added better support for movie rendering
 *
 * 105   3/31/99 3:48p Jason
 * changes for cinematics
 *
 * 104   3/30/99 3:39p Jason
 * fixed some fog issues
 *
 * 103   3/29/99 7:29p Jason
 * made renderer handle default resolution more gracefully
 *
 * 102   3/24/99 11:55a Jason
 * added S3 texture compression
 *
 * 101   3/22/99 5:51p Jason
 * enhancements to mirrors
 *
 * 100   3/02/99 6:03p Jason
 * fixed opengl problem
 *
 * 99    2/26/99 3:32p Jason
 * made OpenGL/D3D not work with Voodoo3 OEM
 *
 * 98    2/17/99 1:05p Jason
 * revamped object/face/terrain selection code
 *
 * 97    2/16/99 11:36a Jason
 * fixed up some FindArg stuff
 *
 * 96    2/15/99 3:47p Jason
 * added screenshots to opengl
 *
 * 95    2/06/99 10:34p Jason
 * added renderer error message if no renderer is set
 *
 * 94    1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 93    1/22/99 1:08a Jason
 * added vid mem checking
 *
 * 92    1/18/99 10:45a Samir
 * added function to get DirectDraw object from Win32 apps.
 *
 * 91    12/08/98 2:30p Jason
 * fog rendering changes for patch
 *
 * 90    12/03/98 5:02p Jason
 * made glide work good with 128x128 lightmaps
 *
 * 89    11/30/98 2:27p Jason
 * more opengl fixes
 *
 * 88    11/30/98 12:03p Jason
 * fixed some opengl issues
 *
 * 87    11/30/98 11:15a Jason
 * fixed some renderer issues for the demo patch
 *
 * 86    11/19/98 6:55p Jason
 * hurray! Fixed TNT problems with Direct3d
 *
 * 85    11/11/98 2:07p Jason
 * added direct3d screenshots
 *
 * 84    10/22/98 10:31a Sean
 * fixed lighting in a window with opengl
 *
 * 83    10/22/98 12:27a Sean
 * put breaks in switch statements
 *
 * 82    10/21/98 9:28p Jason
 * Made no lightmaps work globally
 *
 * 81    10/21/98 12:06p Jason
 * changes for data paging
 *
 * 80    10/17/98 2:46p Jason
 * better error string reports
 *
 * 79    10/14/98 6:28p Jason
 * added Coplanar polygon stuff
 *
 * 78    10/12/98 7:20p Jason
 * fixed gamma for direct3d
 *
 * 77    10/08/98 3:36p Jason
 * fixes for the demo
 *
 * 76    9/25/98 9:25p Jason
 * did some graphics optimizations
 *
 * 75    9/25/98 1:17a Jason
 * added rend_SetCoplanarPolygonOffset functions
 *
 * 74    9/24/98 12:57p Jason
 * more state limited optimizations
 *
 * 73    9/18/98 1:28p Jason
 * cleaned up renderer initting
 *
 * 72    9/15/98 12:11p Jason
 * made special lines work in opengl
 *
 * 71    9/11/98 4:03p Jason
 * added better multitexture support
 *
 * 70    9/08/98 5:20p Jason
 * more state changing optimizations
 *
 * 69    9/02/98 5:41p Jason
 * adding lightmaps back to opengl
 *
 * 68    9/02/98 2:26p Jason
 * changes for state limiting
 *
 * 67    8/31/98 5:30p Jason
 * first pass at textures with Direct3d
 *
 * 66    7/16/98 2:30p Jason
 * added first pass at Direct3D support
 *
 * 65    6/11/98 3:38p Jason
 * added a general StateLimit render boolean for APIs that are state
 * limited (like OpenGL or D3D)
 *
 * 64    6/10/98 1:08p Jason
 * Fixed yet more OpenGL bugs
 *
 * 63    6/10/98 12:23p Jason
 * fixed some more bugs with windowed opengl
 *
 * 62    6/09/98 7:32p Jason
 * fixed windowed OpenGl bug
 *
 * 61    6/09/98 6:16p Jason
 * added some features for windowed opengl
 *
 * 60    6/09/98 4:47p Jason
 * added windowed openGL mode
 *
 * 59    5/20/98 5:44p Jason
 * incremental checkin for bumpmapping
 *
 * 58    5/19/98 2:23p Jeff
 * put in the rend_SetZBufferState(0) into DrawChunkedBitmap
 *
 * 57    5/18/98 7:07p Jeff
 * rend_DrawChunkBitmap now calls rend_DrawSimpleBitmap instead of
 * rend_DrawScaledBitmap
 *
 * 56    5/11/98 6:14p Jason
 * some minor fixes for opengl
 *
 * 55    5/06/98 1:39p Jason
 * added rend_SetResolution
 *
 * 54    5/05/98 3:02p Jason
 * attempting to add different screen resolutions
 *
 * 53    5/05/98 1:01p Jeff
 * Added a rend_DrawScaledChunkBitmap
 *
 * 52    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 51    4/17/98 4:27p Jason
 * added alpha per vertex stuff to drawscaledbitmap
 *
 * 50    4/18/98 3:25a Samir
 * changed some flag in rend_DrawChunkedBitmap
 *
 * 49    4/08/98 3:07p Jeff
 * changed the zvalue parameter within DrawSimpleBitmap
 *
 * 48    4/08/98 12:27p Jason
 * added rend_drawsimplebitmap
 *
 * 47    4/01/98 12:02p Jason
 * incremental checkin for rendering changes
 *
 * 46    3/13/98 1:22p Jason
 * Moved UseHardware flag to the renderer lib where it belongs
 *
 * 45    3/02/98 5:53p Jason
 * added gamma functionality
 *
 * 44    2/27/98 4:46p Jason
 * added more opengl support
 *
 * 43    2/26/98 11:00a Jason
 * incremental opengl functionality
 *
 * 42    2/17/98 2:02p Jason
 * fixed clamping bug for chunked bitmaps
 *
 * 41    2/16/98 11:43a Jason
 * more opengl stuff
 *
 * 40    2/14/98 10:48p Jason
 * got preferred rendering working
 *
 * 39    2/13/98 3:56p Jason
 * added much better opengl support
 *
 * 38    2/12/98 1:32p Jason
 * got mipmapping working
 *
 * 37    1/28/98 5:37p Jason
 * added streamer weapons
 *
 * 36    1/28/98 12:54p Jason
 * made renderer auto shutdown on program close
 *
 *
 * 35    1/19/98 2:32p Jason
 * added the ability to set clear flags on rend_StartFrame
 *
 * 34    1/16/98 11:54a Samir
 * Added support for rendering chunked bitmaps.
 *
 * 33    1/14/98 5:49p Jeff
 * tex_LFBLock stuff added (samir.)
 *
 * 32    12/29/97 5:51p Samir
 * rend_Flip should call ddvid_Flip for software flip.
 *
 * 31    12/22/97 7:34p Samir
 * Removed instances of gr.h include.  Replaced with grdefs.h
 *
 * 30    12/19/97 5:22p Samir
 * Added more drawing primatives for software.
 *
 * 29    12/19/97 2:36p Jason
 * more fixes for 2d/3d integration
 *
 * 28    12/19/97 12:20p Jason
 * changes for better 2d/3d system integration
 *
 * 27    11/14/97 3:44p Jason
 * added transparency to blitting function
 *
 * 26    11/13/97 4:06p Jason
 * added rend_DrawLFBBitmap
 *
 * 25    11/13/97 3:52p Jason
 * added lfb stuff for renderer
 *
 * 24    10/29/97 12:36p Jason
 * remove byte/bool conflicts in the renderer lib
 *
 * 23    10/24/97 4:39p Jason
 * added support to not write into the zbuffer
 *
 * 22    10/22/97 5:01p Jason
 * added rend_SetZBias
 *
 * 21    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 20    10/13/97 3:56p Jason
 * made a better 3d bitmap system
 *
 * 19    9/16/97 6:23p Jason
 * took out software z buffer from rend_SetZBuffer
 *
 * 18    9/16/97 4:09p Jason
 * implemented software zbuffer
 *
 * 17    9/09/97 12:34p Jason
 * made software transparency work correctly with new alpha type
 *
 * 16    9/09/97 11:45a Jason
 * changed the way alpha works with the renderer
 *
 * 15    8/29/97 5:42p Jason
 * fixed hud rendering problems
 *
 * 14    8/29/97 11:59a Jason
 * implemented screenshot functions
 *
 * 13    8/24/97 2:45p Jason
 * implemented texture wrapping
 *
 * 12    8/07/97 11:46a Jason
 * implemented tmap overlay system
 *
 * 11    8/04/97 6:46p Jason
 * added code for a lightmap system
 *
 * 10    8/04/97 3:28p Jason
 * added alpha blending per texture
 *
 * 9     7/20/97 7:36p Jason
 * added support for colored fog
 *
 * 8     7/18/97 12:57p Jason
 * added line drawing for glide
 *
 * 13    6/16/97 5:02p Jason
 * added flip function
 *
 * 12    6/16/97 3:44p Jason
 * added line drawing
 *
 * 11    6/16/97 2:54p Jason
 * added rend_DrawFontCharacter function for drawing fonts
 *
 * 10    6/16/97 2:34p Jason
 * added 3dfx support
 *
 * 9     6/06/97 11:35a Jason
 * added missing functions for pixel primitives
 *
 * 8     6/03/97 12:19p Jason
 * more functions added for opengl
 *
 * 7     5/29/97 6:26p Jason
 * incremental changes for opengl/lighting support
 *
 * 6     5/27/97 4:39p Jason
 * changes to support OpenGL
 *
 * 5     5/22/97 11:59a Jason
 * add a ScaleBitmap function to the abstracted render library
 *
 * 4     5/21/97 7:35p Matt
 * Move Current_surface & viewport locking from 3D to renderer library
 *
 * $NoKeywords: $
 */
#include "renderer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ddvid.h"
#include "pstypes.h"
#include "mono.h"
#include "pserror.h"
#include "ddio.h"
#include "bitmap.h"
#include "application.h"
#include "3d.h"

// Renderers for Windows version.  Mac gets these through a global include file.
#if defined(WIN32)
#define USE_OPENGL
// #define USE_GLIDE
#define USE_D3D
// #define USE_SOFTWARE
#endif

// Renderers for Linux version
#if defined(__LINUX__) || defined(ANDROID)
#define USE_OPENGL
#define USE_GLIDE
// #define USE_D3D
// #define USE_SOFTWARE
#endif

#ifdef USE_SOFTWARE
#include "texture.h"
#endif
#ifdef USE_OPENGL
#include "rend_opengl.h"
#endif
#ifdef USE_GLIDE
#include "rend_glide.h"
#endif
#ifdef USE_D3D
#include "rend_d3d.h"
#endif
extern int FindArg(const char *);
#ifdef USE_OPENGL
int OpenGL_window_initted = 0;
#endif

// The font characteristics
static float rend_FontRed[4], rend_FontBlue[4], rend_FontGreen[4], rend_FontAlpha[4];
char Renderer_error_message[256] = "Generic renderer error";
int Triangles_drawn = 0;
bool UseHardware = 0;
bool NoLightmaps = 0;
bool StateLimited = 0;
bool UseMultitexture = 0;
bool UseWBuffer = 0;
int Overlay_map = -1;
int Bump_map = 0, Bumpmap_ready = 0;
uint8_t Overlay_type = OT_NONE;
float Z_bias = 0.0;
uint8_t Renderer_close_flag = 0, Renderer_initted = 0;
// Is this hardware or software rendered?
renderer_type Renderer_type = RENDERER_SOFTWARE_16BIT;
// Tells the software renderer whether or not to use mipping
void rend_SetMipState(int8_t mipstate) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetMipState(mipstate);
#endif
    break;
  case RENDERER_OPENGL:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetMipState(mipstate);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetMipState(mipstate);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_SetInitOptions() {
  switch (Renderer_type) {
  case RENDERER_DIRECT3D:
    /*
    //#ifdef DEMO
            if (UseMultitexture)
            {
                    if (!FindArg("-forcelightmaps"))
                            UseMultitexture=0;
            }
            NoLightmaps=true;
    //#endif
    */
    break;
  default:
    break;
  }
  if (FindArg("-forcelightmaps"))
    NoLightmaps = false;
  if (FindArg("-nolightmaps")) {
    NoLightmaps = true;
    UseMultitexture = false;
  }
  if (FindArg("-NoMultitexture"))
    UseMultitexture = false;
}
// Init our renderer
int rend_Init(renderer_type state, oeApplication *app, renderer_preferred_state *pref_state) {
#ifndef DEDICATED_ONLY
  int retval = 0;
  rend_SetRendererType(state);
  if (!Renderer_initted) {
    if (!Renderer_close_flag) {
      atexit(rend_Close);
      Renderer_close_flag = 1;
    }
    Renderer_initted = 1;
  }
#ifdef USE_OPENGL
  if (OpenGL_window_initted) {
    rend_CloseOpenGLWindow();
    OpenGL_window_initted = 0;
  }
#endif
  mprintf(0, "Renderer init is set to %d\n", Renderer_initted);
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    NoLightmaps = false;
    UseHardware = 0;
    StateLimited = 0;
    UseMultitexture = 0;
    UseWBuffer = 0;
#ifdef USE_SOFTWARE
    retval = tex_Init();
#endif
    break;
  case RENDERER_OPENGL: {
    NoLightmaps = false;
    UseHardware = 1;
    StateLimited = 1;
    UseMultitexture = 0;
    UseWBuffer = 0;

#ifndef OEM_V3
    int flags = app->flags();
    if (flags & OEAPP_WINDOWED) {
      // initialize for windowed
      retval = rend_InitOpenGLWindow(app, pref_state);
    } else {
      // initialize for full screen
      retval = opengl_Init(app, pref_state);
    }
#endif
  } break;

  case RENDERER_GLIDE:
    NoLightmaps = false;
    UseHardware = 1;
    StateLimited = 0;
    UseMultitexture = 0;
    UseWBuffer = 1;
#ifdef USE_GLIDE
    retval = glide_Init(app, pref_state);
#endif
    break;
  case RENDERER_DIRECT3D:
    NoLightmaps = false;
    UseHardware = 1;
    StateLimited = 1;
    UseMultitexture = 0;
    UseWBuffer = 0;
#ifdef USE_D3D
#ifndef OEM_V3
    retval = d3d_Init(app, pref_state);
#endif
#endif
    break;
  default:
    rend_SetErrorMessage("No renderer set.  Make sure you have run the game from the launcher.");
    retval = 0;
    break;
  }
  if (retval != 0)
    rend_SetInitOptions();
  return retval;
#else
  return 0;
#endif // #ifdef DEDICATED_ONLY
}
void rend_Close() {
  mprintf(0, "CLOSE:Renderer init is set to %d\n", Renderer_initted);
  if (!Renderer_initted)
    return;
#ifdef USE_OPENGL
  if (OpenGL_window_initted) {
    if (Renderer_type != RENDERER_OPENGL)
      rend_CloseOpenGLWindow();
    OpenGL_window_initted = 0;
  }
#endif
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_Close();
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_Close();
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_Close();
#endif
    break;
  default:
    Int3();
    break;
  }
  Renderer_initted = 0;
}

// Given nv points, draws that polygon according to the various state variables
// Handle is a bitmap handle
void rend_DrawPolygon(int handle, g3Point **p, int nv, int map_type) {
#ifndef DEDICATED_ONLY
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_DrawPointList(handle, p, nv);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_DrawPolygon(handle, p, nv, map_type);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_DrawPolygon(handle, p, nv, map_type);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_DrawPolygon(handle, p, nv, map_type);
#endif
    break;
  default:
    Int3();
    break;
  }
#endif // #ifdef DEDICATED_ONLY
}
void rend_SetFlatColor(ddgr_color color) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetFlatColor(color);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetFlatColor(color);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetFlatColor(color);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetFlatColor(color);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets the fog state to TRUE or FALSE
void rend_SetFogState(int8_t on) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetFogState(on);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetFogState(on);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetFogState(on);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetFogState(on);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets the near and far plane of fog
void rend_SetFogBorders(float fog_near, float fog_far) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetFogBorders(fog_near, fog_far);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetFogBorders(fog_near, fog_far);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetFogBorders(fog_near, fog_far);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetFogBorders(fog_near, fog_far);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_SetRendererType(renderer_type state) {
  Renderer_type = state;
  mprintf(0, "RendererType is set to %d.\n", state);
}
void rend_SetLighting(light_state state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetLighting(state);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetLightingState(state);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetLightingState(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetLightingState(state);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_SetColorModel(color_model state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetColorModel(state);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetColorModel(state);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetColorModel(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetColorModel(state);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_SetTextureType(texture_type state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetTextureType(state);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetTextureType(state);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetTextureType(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetTextureType(state);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_StartFrame(int x1, int y1, int x2, int y2, int clear_flags) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_StartFrame(x1, y1, x2, y2);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_BeginFrame(x1, y1, x2, y2, clear_flags);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_BeginFrame(x1, y1, x2, y2, clear_flags);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_BeginFrame(x1, y1, x2, y2, clear_flags);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Flips the screen
void rend_Flip() {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    ddvid_VideoFlip();
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_Flip();
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_Flip();
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_Flip();
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_EndFrame() {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_EndFrame();
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_EndFrame();
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_EndFrame();
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_EndFrame();
#endif
    break;
  default:
    Int3();
    break;
  }
}
// draws a scaled 2d bitmap to our buffer
void rend_DrawScaledBitmap(int x1, int y1, int x2, int y2, int bm, float u0, float v0, float u1, float v1, int color,
                           float *alphas) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
  case RENDERER_OPENGL:
  case RENDERER_GLIDE:
  case RENDERER_DIRECT3D: {
    g3Point *ptr_pnts[4];
    g3Point pnts[4];
    float r, g, b;
    if (color != -1) {
      r = GR_COLOR_RED(color) / 255.0;
      g = GR_COLOR_GREEN(color) / 255.0;
      b = GR_COLOR_BLUE(color) / 255.0;
    }
    for (int i = 0; i < 4; i++) {
      if (color == -1)
        pnts[i].p3_l = 1.0;
      else {
        pnts[i].p3_r = r;
        pnts[i].p3_g = g;
        pnts[i].p3_b = b;
      }
      if (alphas) {
        pnts[i].p3_a = alphas[i];
      }

      pnts[i].p3_z = 1.0f;
      pnts[i].p3_flags = PF_PROJECTED;
    }

    pnts[0].p3_sx = x1;
    pnts[0].p3_sy = y1;
    pnts[0].p3_u = u0;
    pnts[0].p3_v = v0;
    pnts[1].p3_sx = x2;
    pnts[1].p3_sy = y1;
    pnts[1].p3_u = u1;
    pnts[1].p3_v = v0;
    pnts[2].p3_sx = x2;
    pnts[2].p3_sy = y2;
    pnts[2].p3_u = u1;
    pnts[2].p3_v = v1;
    pnts[3].p3_sx = x1;
    pnts[3].p3_sy = y2;
    pnts[3].p3_u = u0;
    pnts[3].p3_v = v1;
    ptr_pnts[0] = &pnts[0];
    ptr_pnts[1] = &pnts[1];
    ptr_pnts[2] = &pnts[2];
    ptr_pnts[3] = &pnts[3];
    rend_SetTextureType(TT_LINEAR);
    rend_DrawPolygon(bm, ptr_pnts, 4);
    break;
  }
  default:
    Int3();
    break;
  }
}
// Sets where the software renderer should write to
void rend_SetSoftwareParameters(float aspect, int width, int height, int pitch, uint8_t *framebuffer) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetSoftwareParameters(aspect, width, height, pitch, framebuffer);
#endif
    break;
  case RENDERER_OPENGL:
  case RENDERER_GLIDE:
  case RENDERER_DIRECT3D:
  default:
    // Int3();	// This function shouldn't have been called!
    break;
  }
}
// Sets the state of bilinear filtering for our textures
void rend_SetFiltering(int8_t state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetFiltering(state);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetFiltering(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetFiltering(state);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets the state of zbuffering to on or off
void rend_SetZBufferState(int8_t state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetZBufferState(state);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetZBufferState(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetZBufferState(state);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets the near and far planes for z buffer
void rend_SetZValues(float nearz, float farz) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetZValues(nearz, farz);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetZValues(nearz, farz);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetZValues(nearz, farz);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets a bitmap as a overlay map to rendered on top of the next texture map
// a -1 value indicates no overlay map
void rend_SetOverlayMap(int handle) { Overlay_map = handle; }
void rend_SetOverlayType(uint8_t type) { Overlay_type = type; }
// Clears the display to a specified color
void rend_ClearScreen(ddgr_color color) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_ClearScreen(color);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_ClearScreen(color);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_ClearScreen(color);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Clears the zbuffer for the screen
void rend_ClearZBuffer() {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_ClearZBuffer();
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_ClearZBuffer();
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_ClearZBuffer();
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Clears the zbuffer for the screen
void rend_ResetCache() {
  mprintf(0, "Resetting texture cache!\n");
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_ResetCache();
#endif
    break;
  case RENDERER_GLIDE:
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_ResetCache();
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Fills a rectangle on the display
void rend_FillRect(ddgr_color color, int x1, int y1, int x2, int y2) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_FillRect(color, x1, y1, x2, y2);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_FillRect(color, x1, y1, x2, y2);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_FillRect(color, x1, y1, x2, y2);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_FillRect(color, x1, y1, x2, y2);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets a pixel on the display
void rend_SetPixel(ddgr_color color, int x, int y) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetPixel(color, x, y);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetPixel(color, x, y);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetPixel(color, x, y);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetPixel(color, x, y);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets a pixel on the display
ddgr_color rend_GetPixel(int x, int y) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    return tex_GetPixel(x, y);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    return opengl_GetPixel(x, y);
#endif
    break;
  case RENDERER_GLIDE:
  case RENDERER_DIRECT3D:
  default:
    // Int3();
    break;
  }
  return GR_BLACK;
}
//	Draws spheres
void rend_FillCircle(ddgr_color col, int x, int y, int rad) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_FillCircle(col, x, y, rad);
#endif
    break;
  case RENDERER_OPENGL:
  case RENDERER_GLIDE:
  case RENDERER_DIRECT3D:
  default:
    // Int3();
    break;
  }
}
//	draws circles
void rend_DrawCircle(int x, int y, int rad) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_DrawCircle(x, y, rad);
#endif
    break;
  case RENDERER_OPENGL:
  case RENDERER_GLIDE:
  case RENDERER_DIRECT3D:
  default:
    // Int3();
    break;
  }
}
// Sets up a font character to draw.  We draw our fonts as pieces of textures
void rend_DrawFontCharacter(int bm_handle, int x1, int y1, int x2, int y2, float u, float v, float w, float h) {
  g3Point *ptr_pnts[4];
  g3Point pnts[4];
  for (int i = 0; i < 4; i++) {
    pnts[i].p3_z = 1; // Make REALLY close!
    pnts[i].p3_flags = PF_PROJECTED;
    ptr_pnts[i] = &pnts[i];
  }
  pnts[0].p3_sx = x1;
  pnts[0].p3_sy = y1;
  pnts[0].p3_u = u;
  pnts[0].p3_v = v;
  pnts[1].p3_sx = x2;
  pnts[1].p3_sy = y1;
  pnts[1].p3_u = u + w;
  pnts[1].p3_v = v;
  pnts[2].p3_sx = x2;
  pnts[2].p3_sy = y2;
  pnts[2].p3_u = u + w;
  pnts[2].p3_v = v + h;
  pnts[3].p3_sx = x1;
  pnts[3].p3_sy = y2;
  pnts[3].p3_u = u;
  pnts[3].p3_v = v + h;
  rend_DrawPolygon(bm_handle, ptr_pnts, 4);
}
// Draws a line
void rend_DrawLine(int x1, int y1, int x2, int y2) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_DrawLine(x1, y1, x2, y2);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_DrawLine(x1, y1, x2, y2);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_DrawLine(x1, y1, x2, y2);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_DrawLine(x1, y1, x2, y2);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets the argb characteristics of the font characters.  color1 is the upper left and proceeds clockwise
void rend_SetCharacterParameters(ddgr_color color1, ddgr_color color2, ddgr_color color3, ddgr_color color4) {
  rend_FontRed[0] = (float)(GR_COLOR_RED(color1) / 255.0);
  rend_FontRed[1] = (float)(GR_COLOR_RED(color2) / 255.0);
  rend_FontRed[2] = (float)(GR_COLOR_RED(color3) / 255.0);
  rend_FontRed[3] = (float)(GR_COLOR_RED(color4) / 255.0);
  rend_FontGreen[0] = (float)(GR_COLOR_GREEN(color1) / 255.0);
  rend_FontGreen[1] = (float)(GR_COLOR_GREEN(color2) / 255.0);
  rend_FontGreen[2] = (float)(GR_COLOR_GREEN(color3) / 255.0);
  rend_FontGreen[3] = (float)(GR_COLOR_GREEN(color4) / 255.0);
  rend_FontBlue[0] = (float)(GR_COLOR_BLUE(color1) / 255.0);
  rend_FontBlue[1] = (float)(GR_COLOR_BLUE(color2) / 255.0);
  rend_FontBlue[2] = (float)(GR_COLOR_BLUE(color3) / 255.0);
  rend_FontBlue[3] = (float)(GR_COLOR_BLUE(color4) / 255.0);
  rend_FontAlpha[0] = (color1 >> 24) / 255.0;
  rend_FontAlpha[1] = (color2 >> 24) / 255.0;
  rend_FontAlpha[2] = (color3 >> 24) / 255.0;
  rend_FontAlpha[3] = (color4 >> 24) / 255.0;
}
// Sets the color of fog
void rend_SetFogColor(ddgr_color fogcolor) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetFogColor(fogcolor);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetFogColor(fogcolor);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetFogColor(fogcolor);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_SetAlphaType(int8_t atype) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_SetAlphaType(atype);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetAlphaType(atype);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetAlphaType(atype);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetAlphaType(atype);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Sets the alpha value for constant alpha
void rend_SetAlphaValue(uint8_t val) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetAlphaValue(val);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetAlphaValue(val);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetAlphaValue(val);
#endif
    break;
  default:
    Int3();
    break;
  }
}

// Sets the overall alpha scale factor (all alpha values are scaled by this value)
// usefull for motion blur effect
void rend_SetAlphaFactor(float val) {
  if (val < 0.0f)
    val = 0.0f;
  if (val > 1.0f)
    val = 1.0f;

  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetAlphaFactor(val);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetAlphaFactor(val);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetAlphaFactor(val);
#endif
    break;
  default:
    Int3();
    break;
  }
}

// Returns the current Alpha factor
float rend_GetAlphaFactor(void) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    return opengl_GetAlphaFactor();
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    return glide_GetAlphaFactor();
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    return d3d_GetAlphaFactor();
#endif
    break;
  default:
    Int3();
    break;
  }
  return 1.0f;
}

// Sets the texture wrapping type
void rend_SetWrapType(wrap_type val) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetWrapType(val);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetWrapType(val);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetWrapType(val);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Draws a line using the states of the renderer
void rend_DrawSpecialLine(g3Point *p0, g3Point *p1) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_DrawSpecialLine(p0, p1);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_DrawSpecialLine(p0, p1);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_DrawSpecialLine(p0, p1);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Takes a screenshot of the current frame and puts it into the handle passed
void rend_Screenshot(int bm_handle) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_Screenshot(bm_handle);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_Screenshot(bm_handle);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_Screenshot(bm_handle);
#endif
    break;
  default:
    Int3();
    break;
  }
}
void rend_SetZBias(float z_bias) { Z_bias = z_bias; }
// Enables/disables writes the depth buffer
void rend_SetZBufferWriteMask(int state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetZBufferWriteMask(state);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetZBufferWriteMask(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetZBufferWriteMask(state);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Gets a pointer to a linear frame buffer
void rend_GetLFBLock(renderer_lfb *lfb) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_GetLFBLock(lfb);
#endif
    break;
  case RENDERER_OPENGL:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_GetLFBLock(lfb);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_GetLFBLock(lfb);
#endif
    break;
  default:
    Int3();
    break;
  }
}
// Releases an lfb lock
void rend_ReleaseLFBLock(renderer_lfb *lfb) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_ReleaseLFBLock(lfb);
#endif
    break;
  case RENDERER_OPENGL:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_ReleaseLFBLock(lfb);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_ReleaseLFBLock(lfb);
#endif
    break;
  default:
    Int3();
    break;
  }
}

// Returns the aspect ratio of the physical screen
void rend_GetProjectionParameters(int *width, int *height) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_GetProjectionParameters(width, height);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_GetProjectionParameters(width, height);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_GetProjectionParameters(width, height);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_GetProjectionParameters(width, height);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for this lib!\n");
    Int3();
    break;
  }
}

void rend_GetProjectionScreenParameters(int &screenLX, int &screenTY, int &screenW, int &screenH) {
  switch (Renderer_type) {
  case RENDERER_OPENGL: {
#ifdef USE_OPENGL
    opengl_GetProjectionScreenParameters(screenLX, screenTY, screenW, screenH);
#endif
  } break;

  default:
    mprintf(0, "Function not implemented for this lib!\n");
    Int3();
    break;
  }
}

// Returns the aspect ratio of the physical screen
float rend_GetAspectRatio() {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    return tex_GetAspectRatio();
    break;
#else
    return -1.0f;
    break;
#endif
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    return glide_GetAspectRatio();
    break;
#else
    return -1.0f;
    break;
#endif
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    return opengl_GetAspectRatio();
    break;
#else
    return -1.0f;
    break;
#endif
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    return d3d_GetAspectRatio();
    break;
#else
    return -1.0f;
    break;
#endif
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    return -1;
    Int3();
    break;
  }
}
// Given a source x,y and width,height, draws any sized bitmap into the renderer lfb
void rend_DrawLFBBitmap(int sx, int sy, int w, int h, int dx, int dy, uint16_t *data, int rowsize) {
  renderer_lfb lfb;
  int i, t;
  lfb.type = LFB_LOCK_WRITE;
  rend_GetLFBLock(&lfb);
  if (lfb.data == NULL) {
    mprintf(0, "Couldn't get lock in rend_DrawLFBBitmap!\n");
    return;
  }
  for (i = 0; i < h; i++) {
    for (t = 0; t < w; t++) {
      uint16_t pix = data[((sy + i) * (rowsize / 2)) + sx + t];
      if (pix & OPAQUE_FLAG)
        lfb.data[((dy + i) * (lfb.bytes_per_row / 2)) + dx + t] = pix;
    }
  }
  rend_ReleaseLFBLock(&lfb);
}
//	given a chunked bitmap, renders it.
void rend_DrawChunkedBitmap(chunked_bitmap *chunk, int x, int y, uint8_t alpha) {
  int *bm_array = chunk->bm_array;
  int w = chunk->w;
  int h = chunk->h;
  int piece_w = bm_w(bm_array[0], 0);
  int piece_h = bm_h(bm_array[0], 0);
  int screen_w, screen_h;
  int i, t;
  rend_SetZBufferState(0);
  rend_GetProjectionParameters(&screen_w, &screen_h);
  for (i = 0; i < h; i++) {
    for (t = 0; t < w; t++) {
      int dx = x + (piece_w * t);
      int dy = y + (piece_h * i);
      int dw, dh;
      if ((dx + piece_w) > screen_w)
        dw = piece_w - ((dx + piece_w) - screen_w);
      else
        dw = piece_w;
      if ((dy + piece_h) > screen_h)
        dh = piece_h - ((dy + piece_h) - screen_h);
      else
        dh = piece_h;

      float u2 = (float)dw / (float)piece_w;
      float v2 = (float)dh / (float)piece_h;
      rend_DrawSimpleBitmap(bm_array[i * w + t], dx, dy);
    }
  }
  rend_SetZBufferState(1);
}
//	given a chunked bitmap, renders it.scaled
void rend_DrawScaledChunkedBitmap(chunked_bitmap *chunk, int x, int y, int neww, int newh, uint8_t alpha) {
  int *bm_array = chunk->bm_array;
  int w = chunk->w;
  int h = chunk->h;
  int piece_w;
  int piece_h;
  int screen_w, screen_h;
  int i, t;

  float scalew, scaleh;

  scalew = ((float)neww) / ((float)chunk->pw);
  scaleh = ((float)newh) / ((float)chunk->ph);
  piece_w = scalew * ((float)bm_w(bm_array[0], 0));
  piece_h = scaleh * ((float)bm_h(bm_array[0], 0));
  rend_GetProjectionParameters(&screen_w, &screen_h);
  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetZBufferState(0);
  rend_SetAlphaType(AT_CONSTANT_TEXTURE);
  rend_SetAlphaValue(alpha);
  rend_SetWrapType(WT_WRAP);
  for (i = 0; i < h; i++) {
    for (t = 0; t < w; t++) {
      int dx = x + (piece_w * t);
      int dy = y + (piece_h * i);
      int dw, dh;
      if ((dx + piece_w) > screen_w)
        dw = piece_w - ((dx + piece_w) - screen_w);
      else
        dw = piece_w;
      if ((dy + piece_h) > screen_h)
        dh = piece_h - ((dy + piece_h) - screen_h);
      else
        dh = piece_h;

      float u2 = (float)dw / (float)piece_w;
      float v2 = (float)dh / (float)piece_h;
      rend_DrawScaledBitmap(dx, dy, dx + dw, dy + dh, bm_array[i * w + t], 0, 0, u2, v2);
    }
  }
  rend_SetZBufferState(1);
}
// Sets some global preferences for the renderer
int rend_SetPreferredState(renderer_preferred_state *pref_state) {
  int retval = 1;
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    retval = glide_SetPreferredState(pref_state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    retval = d3d_SetPreferredState(pref_state);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    retval = opengl_SetPreferredState(pref_state);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
  rend_SetInitOptions();
  return retval;
}
// Sets the gamma for this display
void rend_SetGammaValue(float val) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetGammaValue(val);
#endif
    break;
  case RENDERER_OPENGL:
  case RENDERER_DIRECT3D:
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Draws a simple bitmap at the specified x,y location
void rend_DrawSimpleBitmap(int bm_handle, int x, int y) {
  rend_SetAlphaType(AT_CONSTANT_TEXTURE);
  rend_SetAlphaValue(255);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetFiltering(0);
  rend_DrawScaledBitmap(x, y, x + bm_w(bm_handle, 0), y + bm_h(bm_handle, 0), bm_handle, 0, 0, 1, 1);
  rend_SetFiltering(1);
}
// Fills in the passed in pointer with the current rendering state
void rend_GetRenderState(rendering_state *rstate) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
#ifdef USE_SOFTWARE
    tex_GetRenderState(rstate);
#endif
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_GetRenderState(rstate);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_GetRenderState(rstate);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_GetRenderState(rstate);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y
void rend_CopyBitmapToFramebuffer(int bm_handle, int x, int y) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    // tex_GetRenderState (rstate);
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_CopyBitmapToFramebuffer(bm_handle, x, y);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_CopyBitmapToFramebuffer(bm_handle, x, y);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_CopyBitmapToFramebuffer(bm_handle, x, y);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void rend_SetFrameBufferCopyState(bool state) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    // tex_GetRenderState (rstate);
    break;
  case RENDERER_GLIDE:
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetFrameBufferCopyState(state);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetFrameBufferCopyState(state);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Changes the resolution of the renderer
void rend_SetResolution(int width, int height) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetResolution(width, height);
#endif
    break;
  case RENDERER_OPENGL:
  case RENDERER_DIRECT3D:
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
#ifdef USE_OPENGL
int WindowGL = 0;
#endif
// Gets OpenGL ready to work in a window
int rend_InitOpenGLWindow(oeApplication *app, renderer_preferred_state *pref_state) {
#ifdef USE_OPENGL
  WindowGL = 1;
  return opengl_Init(app, pref_state);
#else
  return 0;
#endif
}
// Shuts down OpenGL in a window
void rend_CloseOpenGLWindow() {
#ifdef USE_OPENGL
  opengl_Close();
  WindowGL = 0;
  OpenGL_window_initted = 0;
  mprintf(1, "SHUTTING DOWN WINDOWED OPENGL!");
#endif
}
// Sets the state of the OpenGLWindow to on or off
static renderer_type Save_rend;
static bool Save_state_limit;
void rend_SetOpenGLWindowState(int state, oeApplication *app, renderer_preferred_state *pref_state) {
#ifdef USE_OPENGL
  if (state) {
    if (!OpenGL_window_initted) {
      if (rend_InitOpenGLWindow(app, pref_state))
        OpenGL_window_initted = 1;
      else
        return;
    }
    UseHardware = 1;
    Save_rend = Renderer_type;
    Save_state_limit = StateLimited;
    Renderer_type = RENDERER_OPENGL;
    StateLimited = 1;
    NoLightmaps = false;
  } else {
    if (OpenGL_window_initted) {
      UseHardware = 0;
      Renderer_type = RENDERER_SOFTWARE_16BIT;
      StateLimited = Save_state_limit;
    }
  }
#endif
}
// Sets the hardware bias level for coplanar polygons
// This helps reduce z buffer artifaces
void rend_SetCoplanarPolygonOffset(float factor) {
  ASSERT(factor >= 0 && factor <= 1.0);
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    glide_SetCoplanarPolygonOffset(factor);
#endif
    break;
  case RENDERER_OPENGL:
#ifdef USE_OPENGL
    opengl_SetCoplanarPolygonOffset(factor);
#endif
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_SetCoplanarPolygonOffset(factor);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Preuploads a texture to the video card
void rend_PreUploadTextureToCard(int handle, int map_type) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
    break;
  case RENDERER_OPENGL:
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_PreUploadTextureToCard(handle, map_type);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Frees an uploaded texture from the video card
void rend_FreePreUploadedTexture(int handle, int map_type) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
    break;
  case RENDERER_OPENGL:
    break;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    d3d_FreePreUploadedTexture(handle, map_type);
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// Retrieves an error message
const char *rend_GetErrorMessage() { return Renderer_error_message; }
// Sets an error message
void rend_SetErrorMessage(const char *str) {
  ASSERT(strlen(str) < 256);
  strcpy(Renderer_error_message, str);
}
// Returns 1 if there is mid video memory, 2 if there is low vid memory, or 0 if there is large vid memory
int rend_LowVidMem() {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
    break;
  case RENDERER_GLIDE:
#ifdef USE_GLIDE
    return glide_LowVidMem();
#endif
    break;
  case RENDERER_OPENGL:
  case RENDERER_DIRECT3D:
    return 0;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
  return 0;
}
// Returns 1 if the renderer supports bumpmapping
int rend_SupportsBumpmapping() {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
  case RENDERER_GLIDE:
  case RENDERER_OPENGL:
    return 0;
  case RENDERER_DIRECT3D:
#ifdef USE_D3D
    return d3d_SupportsBumpmapping();
#endif
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
  return 0;
}
// Sets a bumpmap to be rendered, or turns off bumpmapping altogether
void rend_SetBumpmapReadyState(int state, int map) {
  switch (Renderer_type) {
  case RENDERER_SOFTWARE_16BIT:
  case RENDERER_SOFTWARE_8BIT:
  case RENDERER_GLIDE:
  case RENDERER_OPENGL:
    break;
  case RENDERER_DIRECT3D:
    Bumpmap_ready = state;
    Bump_map = map;
    break;
  default:
    mprintf(0, "Function not implemented for the lib!\n");
    Int3();
    break;
  }
}
// returns the direct draw object
void *rend_RetrieveDirectDrawObj(void **frontsurf, void **backsurf) {
  if (Renderer_initted) {
    switch (Renderer_type) {
    case RENDERER_SOFTWARE_16BIT:
    case RENDERER_SOFTWARE_8BIT:
      break;
    case RENDERER_GLIDE:
      break;
    case RENDERER_OPENGL:
      break;
    case RENDERER_DIRECT3D:
#ifdef USE_D3D
      return d3d_DirectDrawObj(frontsurf, backsurf);
#endif
      break;
    default:
      mprintf(0, "Function not implemented for the lib!\n");
      Int3();
      break;
    }
  }
  *frontsurf = NULL;
  *backsurf = NULL;
  return NULL;
}
// returns rendering statistics for the frame
void rend_GetStatistics(tRendererStats *stats) {
  if (Renderer_initted) {
    switch (Renderer_type) {
    case RENDERER_SOFTWARE_16BIT:
    case RENDERER_SOFTWARE_8BIT:
      memset(stats, 0, sizeof(tRendererStats));
      break;
    case RENDERER_GLIDE:
#ifdef USE_GLIDE
      glide_GetStatistics(stats);
#endif
      break;
    case RENDERER_OPENGL:
#ifdef USE_OPENGL
      opengl_GetStatistics(stats);
#endif
      break;
    case RENDERER_DIRECT3D:
#ifdef USE_D3D
      d3d_GetStatistics(stats);
#endif
      break;
    default:
      mprintf(0, "Function not implemented for the lib!\n");
      Int3();
      break;
    }
  } else {
    memset(stats, 0, sizeof(tRendererStats));
  }
}
