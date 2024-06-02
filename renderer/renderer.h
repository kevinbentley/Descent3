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

 * $Logfile: /DescentIII/Main/lib/renderer.h $
 * $Revision: 80 $
 * $Date: 4/19/00 5:22p $
 * $Author: Matt $
 *
 * Header for renderer library
 *
 * $Log: /DescentIII/Main/lib/renderer.h $
 *
 * 80    4/19/00 5:22p Matt
 * From Duane for 1.4
 * Added extern
 *
 * 79    10/21/99 1:43p Kevin
 * Mac Merge
 *
 * 78    9/18/99 9:22p Jeff
 * Get/Set Alpha factor functions
 *
 * 77    8/10/99 10:51p Duane
 * Added UseMipmap global
 *
 * 76    7/22/99 8:37p Jeff
 * added texture upload to renderstats
 *
 * 75    7/15/99 6:38p Jeff
 * created function to get rendering stats
 *
 * 74    4/01/99 10:56a Jason
 * added better support for movie rendering
 *
 * 73    3/31/99 3:48p Jason
 * changes for cinematics
 *
 * 72    3/29/99 7:29p Jason
 * made renderer handle default resolution more gracefully
 *
 * 71    3/24/99 11:55a Jason
 * added S3 texture compression
 *
 * 70    3/22/99 5:51p Jason
 * enhancements to mirrors
 *
 * 69    1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 68    1/22/99 1:09a Jason
 * added vid mem checking
 *
 * 67    1/18/99 10:45a Samir
 * added function to get DirectDraw object from Win32 apps.
 *
 * 66    12/23/98 5:35p Jason
 * added saturated lightmap blending
 *
 * 65    12/18/98 5:25p Jason
 * added specularity to mine walls
 *
 * 64    12/09/98 5:28p Jason
 * added more options
 *
 * 63    12/08/98 2:29p Jason
 * fog rendering changes for patch
 *
 * 62    10/21/98 9:28p Jason
 * Made no lightmaps work globally
 *
 * 61    10/21/98 12:05p Jason
 * changes for data paging
 *
 * 60    10/17/98 3:10p Jason
 * added Set/Get error message stuff
 *
 * 59    10/08/98 3:36p Jason
 * fixes for the demo
 *
 * 58    9/25/98 1:17a Jason
 * added rend_SetCoplanarPolygonOffset functions
 *
 * 57    9/18/98 1:28p Jason
 * cleaned up renderer initting
 *
 * 56    9/11/98 4:03p Jason
 * added better multitexture support
 *
 * 55    6/11/98 3:38p Jason
 * added a general StateLimit render boolean for APIs that are state
 * limited (like OpenGL or D3D)
 *
 * 54    6/09/98 4:47p Jason
 * added windowed openGL mode
 *
 * 53    5/26/98 3:59p Jason
 * added LIGHTMAP_BLEND_CONSTANT alpha type
 *
 * 52    5/20/98 5:44p Jason
 * incremental checkin for bumpmapping
 *
 * 51    5/19/98 12:27p Jason
 * cleaned up some 3d stuff
 *
 * 50    5/06/98 1:39p Jason
 * added rend_SetResolution
 *
 * 49    5/06/98 10:51a Jeff
 * put rend_DrawScaledChunkBitmap back in the header
 *
 * 48    5/05/98 3:02p Jason
 * attempting to add different screen resolutions
 *
 * 46    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 45    4/17/98 4:27p Jason
 * added alpha per vertex stuff to drawscaledbitmap
 *
 * 44    4/08/98 12:27p Jason
 * added rend_drawsimplebitmap
 *
 * 43    4/01/98 12:02p Jason
 * incremental checkin for rendering changes
 *
 * 42    3/13/98 1:22p Jason
 * Moved UseHardware flag to the renderer lib where it belongs
 *
 * 41    3/03/98 6:50p Jason
 * added gamma stuff in preferred state
 *
 * 40    3/02/98 5:53p Jason
 * added gamma functionality
 *
 * 39    2/14/98 10:48p Jason
 * got preferred rendering working
 *
 * 38    2/12/98 1:32p Jason
 * got mipmapping working
 *
 * 37    2/05/98 6:53p Jason
 * added new weapon slot
 *
 * 36    2/03/98 3:16p Jason
 * added the ability to specify saturation textures for models
 *
 * 35    1/28/98 5:37p Jason
 * added streamer weapons
 *
 * 34    1/19/98 2:32p Jason
 * added the ability to set clear flags on rend_StartFrame
 *
 * 33    1/16/98 11:54a Samir
 * Added support for rendering chunked bitmaps.
 *
 * 32    1/15/98 6:32p Jason
 * added v wrapping for sky textures
 *
 * 31    12/22/97 7:23p Samir
 * took out transparent colors again.
 *
 * 30    12/22/97 7:15p Samir
 * removed references of ddgr and gr.h.  replace with grdefs.h
 *
 * 29    12/19/97 5:22p Samir
 * Added more drawing primatives for software.
 *
 * 28    12/19/97 2:18p Jason
 * fixed some more 2d/3d integration
 *
 * 27    12/19/97 12:20p Jason
 * changes for better 2d/3d system integration
 *
 * 26    11/25/97 12:33p Jason
 * added antialiasing mode
 *
 * 25    11/19/97 5:25p Jason
 * added new alpha mode - AT_FLAT_BLEND
 *
 * 24    11/13/97 4:06p Jason
 * added rend_DrawLFBBitmap
 *
 * 23    11/13/97 3:52p Jason
 * added lfb stuff for renderer
 *
 * 22    10/29/97 12:36p Jason
 * remove byte/bool conflicts in the renderer lib
 *
 * 21    10/24/97 4:39p Jason
 * added support to not write into the zbuffer
 *
 * 20    10/24/97 2:29p Jason
 * added alpha saturation type
 *
 * 19    10/22/97 4:19p Jason
 * added smoke trail effects
 *
 * 18    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 17    10/13/97 3:56p Jason
 * made a better 3d bitmap system
 *
 * 16    9/16/97 4:09p Jason
 * implemented software zbuffer
 *
 * 15    9/09/97 12:09p Jason
 * took transparency out of texture_types
 *
 * 14    9/09/97 11:44a Jason
 * changed the way alpha works with the renderer
 *
 * 13    9/04/97 5:52p Matt
 * Took out include of 3d.h
 *
 * 12    8/29/97 11:59a Jason
 * implemented screenshot functions
 *
 * 11    8/24/97 2:45p Jason
 * implemented texture wrapping
 *
 * 10    8/07/97 11:46a Jason
 * implemented tmap overlay system
 *
 * 9     8/06/97 11:43a Jason
 * made lightmaps work correctly in the terrain
 *
 * 8     8/04/97 6:46p Jason
 * added code for a lightmap system
 *
 * 7     8/04/97 3:28p Jason
 * added alpha blending per texture
 *
 * 6     7/20/97 7:36p Jason
 * added support for colored fog
 *
 * 2     6/24/97 7:45p Matt
 * Removed include of manage.h
 *
 * 1     6/23/97 9:25p Samir
 * added because source safe sucks
 *
 * 11    6/16/97 5:02p Jason
 * added flip function
 *
 * 10    6/16/97 3:44p Jason
 * added line drawing
 *
 * 9     6/16/97 2:54p Jason
 * added rend_DrawFontCharacter function for drawing fonts
 *
 * 8     6/16/97 2:34p Jason
 * added 3dfx support
 *
 * 7     6/06/97 11:35a Jason
 * added missing functions for pixel primitives
 *
 * 6     6/03/97 12:19p Jason
 * more functions added for opengl
 *
 * 5     5/27/97 4:39p Jason
 * changes to support OpenGL
 *
 * 4     5/22/97 11:59a Jason
 * add a ScaleBitmap function to the abstracted render library
 *
 * 3     5/21/97 12:30p Jason
 * calls rend_start and rend_end when frames begin/end
 *
 * 2     5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 1     5/19/97 3:23p Jason
 *
 * $NoKeywords: $
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include "pstypes.h"
#include "grdefs.h"

// Declare this here so we don't need to include 3d.h
typedef struct g3Point g3Point;
typedef struct chunked_bitmap chunked_bitmap;

//	for rend_Init prototype
class oeApplication;

#define TEXTURE_WIDTH 128
#define TEXTURE_HEIGHT 128
#define TEXTURE_BPP 2

#define FLAT_SHADE_COLOR 0x7C01
// If an incoming texture has the above color in it, change that color to this color
#define REPLACEMENT_COLOR 0x07C0

extern int Triangles_drawn;

// Is this hardware or software rendered?
enum renderer_type {
  RENDERER_OPENGL = 2,
  RENDERER_DIRECT3D = 3,
  RENDERER_GLIDE = 4,
  RENDERER_NONE = 5,
};

extern renderer_type Renderer_type;

// renderer clear flags
#define RF_CLEAR_ZBUFFER 1
#define RF_CLEAR_COLOR 2

// Overlay texture settings
#define OT_NONE 0           // No overlay
#define OT_BLEND 1          // Draw a lightmap texture afterwards
#define OT_REPLACE 2        // Draw a tmap2 style texture afterwards
#define OT_FLAT_BLEND 3     // Draw a gouraud shaded polygon afterwards
#define OT_BLEND_VERTEX 4   // Like OT_BLEND, but take constant alpha into account
#define OT_BUMPMAP 5        // Draw a saturated bumpmap afterwards
#define OT_BLEND_SATURATE 6 // Add a lightmap in

extern uint8_t Overlay_type;
extern int Overlay_map;
extern int Bumpmap_ready, Bump_map;
extern float Z_bias;
extern bool UseHardware;
extern bool StateLimited;
extern bool NoLightmaps;
extern bool UseMultitexture;
extern bool UseWBuffer;
extern bool UseMipmap;  // DAJ
extern bool ATIRagePro; // DAJ
extern bool Formac;     // DAJ

class NewBitmap;

// various state setting functions
//------------------------------------

// Sets our renderer
void rend_SetRendererType(renderer_type state);

#define MAP_TYPE_BITMAP 0
#define MAP_TYPE_LIGHTMAP 1
#define MAP_TYPE_BUMPMAP 2
#define MAP_TYPE_UNKNOWN 3

// lighting state
enum light_state {
  LS_NONE,        // no lighting, fully lit rendering
  LS_GOURAUD,     // Gouraud shading
  LS_PHONG,       // Phong shading
  LS_FLAT_GOURAUD // Take color from flat color
};

void rend_SetLighting(light_state);

enum color_model {
  CM_MONO, // monochromatic (intensity) model - default
  CM_RGB,  // RGB model
};

// color model
void rend_SetColorModel(color_model);

enum texture_type {
  TT_FLAT,                // solid color
  TT_LINEAR,              // textured linearly
  TT_PERSPECTIVE,         // texture perspectively
  TT_LINEAR_SPECIAL,      // A textured polygon drawn as a flat color
  TT_PERSPECTIVE_SPECIAL, // A textured polygon drawn as a flat color
};

// Alpha type flags - used to decide what type of alpha blending to use
#define ATF_CONSTANT 1 // Take constant alpha into account
#define ATF_TEXTURE 2  // Take texture alpha into account
#define ATF_VERTEX 4   // Take vertex alpha into account

// Alpha types
#define AT_ALWAYS 0                    // Alpha is always 255 (1.0)
#define AT_CONSTANT 1                  // constant alpha across the whole image
#define AT_TEXTURE 2                   // Only uses texture alpha
#define AT_CONSTANT_TEXTURE 3          // Use texture * constant alpha
#define AT_VERTEX 4                    // Use vertex alpha only
#define AT_CONSTANT_VERTEX 5           // Use vertex * constant alpha
#define AT_TEXTURE_VERTEX 6            // Use texture * vertex alpha
#define AT_CONSTANT_TEXTURE_VERTEX 7   // Use all three (texture constant vertex)
#define AT_LIGHTMAP_BLEND 8            // dest*src colors
#define AT_SATURATE_TEXTURE 9          // Saturate up to white when blending
#define AT_FLAT_BLEND 10               // Like lightmap blend, but uses gouraud shaded flat polygon
#define AT_ANTIALIAS 11                // Draws an antialiased polygon
#define AT_SATURATE_VERTEX 12          // Saturation with vertices
#define AT_SATURATE_CONSTANT_VERTEX 13 // Constant*vertex saturation
#define AT_SATURATE_TEXTURE_VERTEX 14  // Texture * vertex saturation
#define AT_LIGHTMAP_BLEND_VERTEX 15    //	Like AT_LIGHTMAP_BLEND, but take vertex alpha into account
#define AT_LIGHTMAP_BLEND_CONSTANT 16  // Like AT_LIGHTMAP_BLEND, but take constant alpha into account
#define AT_SPECULAR 32
#define AT_LIGHTMAP_BLEND_SATURATE 33 // Light lightmap blend, but add instead of multiply

#define LFB_LOCK_READ 0
#define LFB_LOCK_WRITE 1

enum wrap_type {
  WT_WRAP,  // Texture repeats
  WT_CLAMP, // Texture clamps
  WT_WRAP_V // Texture wraps in v
};

struct rendering_state {
  int8_t initted;

  int8_t cur_bilinear_state;
  int8_t cur_zbuffer_state;
  int8_t cur_fog_state;
  int8_t cur_mip_state;

  texture_type cur_texture_type;
  color_model cur_color_model;
  light_state cur_light_state;
  int8_t cur_alpha_type;

  wrap_type cur_wrap_type;

  float cur_fog_start, cur_fog_end;
  float cur_near_z, cur_far_z;
  float gamma_value;

  int cur_alpha;
  ddgr_color cur_color;
  ddgr_color cur_fog_color;

  int8_t cur_texture_quality; // 0-none, 1-linear, 2-perspective

  int clip_x1, clip_x2, clip_y1, clip_y2;
  int screen_width, screen_height;

};

struct renderer_preferred_state {
  uint8_t mipping;
  uint8_t filtering;
  float gamma;
  uint8_t bit_depth;
  int width, height;
  uint8_t vsync_on;
};

struct renderer_lfb {
  int type;
  uint16_t *data;
  int bytes_per_row;
};

struct tRendererStats {
  int poly_count;
  int vert_count;
  int texture_uploads;
};

// returns rendering statistics for the frame
void rend_GetStatistics(tRendererStats *stats);

void rend_SetTextureType(texture_type);

// Given a handle to a bitmap and nv point vertices, draws a 3D polygon
void rend_DrawPolygon3D(int handle, g3Point **p, int nv, int map_type = MAP_TYPE_BITMAP);

// Given a handle to a bitmap and nv point vertices, draws a 2D polygon
void rend_DrawPolygon2D(int handle, g3Point **p, int nv);

// Tells the software renderer whether or not to use mipping
void rend_SetMipState(int8_t);

// Sets the fog state to TRUE or FALSE
void rend_SetFogState(int8_t on);

// Sets the near and far plane of fog
void rend_SetFogBorders(float fog_near, float fog_far);

// Sets the color for fill based primitives;
void rend_SetFlatColor(ddgr_color color);

// Tells the renderer we're starting a frame.  Clear flags tells the renderer
// what buffer (if any) to clear
void rend_StartFrame(int x1, int y1, int x2, int y2, int clear_flags = RF_CLEAR_ZBUFFER);

// Tells the renderer the frame is over
void rend_EndFrame();

// Init our renderer, pass the application object also.
int rend_Init(renderer_type state, oeApplication *app, renderer_preferred_state *pref_state);

// de-init the renderer
void rend_Close();

// Draws a scaled 2d bitmap to our buffer
// NOTE: scripts are expecting the old prototype that has a zvalue (which is ignored) before color
void rend_DrawScaledBitmap(int x1, int y1, int x2, int y2, int bm, float u0, float v0, float u1, float v1,
                           int color = -1, float *alphas = NULL);

// Sets the state of bilinear filtering for our textures
void rend_SetFiltering(int8_t state);

// Sets the state of zbuffering to on or off
void rend_SetZBufferState(int8_t state);

// Sets the near and far planes for z buffer
void rend_SetZValues(float nearz, float farz);

// Sets a bitmap as an overlay to rendered on top of the next texture map
void rend_SetOverlayMap(int handle);

// Sets the type of overlay operation
void rend_SetOverlayType(uint8_t type);

// Clears the display to a specified color
void rend_ClearScreen(ddgr_color color);

// Fills a rectangle on the display
void rend_FillRect(ddgr_color color, int x1, int y1, int x2, int y2);

// Sets a pixel on the display
void rend_SetPixel(ddgr_color color, int x, int y);

// Sets a pixel on the display
ddgr_color rend_GetPixel(int x, int y);

// Sets up a font character to draw.  We draw our fonts as pieces of textures
void rend_DrawFontCharacter(int bm_handle, int x1, int y1, int x2, int y2, float u, float v, float w, float h);

// Draws a line
void rend_DrawLine(int x1, int y1, int x2, int y2);

//	Draws spheres
void rend_FillCircle(ddgr_color col, int x, int y, int rad);

//	draws circles
void rend_DrawCircle(int x, int y, int rad);

// Flips the surface
void rend_Flip();

// Sets the argb characteristics of the font characters.  color1 is the upper left and proceeds clockwise
void rend_SetCharacterParameters(ddgr_color color1, ddgr_color color2, ddgr_color color3, ddgr_color color4);

// Sets the color of fog
void rend_SetFogColor(ddgr_color fogcolor);

// sets the alpha type
void rend_SetAlphaType(int8_t);

// Sets the constant alpha value
void rend_SetAlphaValue(uint8_t val);

// Sets the overall alpha scale factor (all alpha values are scaled by this value)
// usefull for motion blur effect
void rend_SetAlphaFactor(float val);

// Returns the current Alpha factor
float rend_GetAlphaFactor(void);

// Sets the wrap parameter
void rend_SetWrapType(wrap_type val);

/// Takes a screenshot of the current frame and returns a NewBitmap
std::unique_ptr<NewBitmap> rend_Screenshot();

// Takes a screenshot of the current frame and puts it into the handle passed
void rend_Screenshot(int bm_handle);

// Adds a bias to each coordinates z value.  This is useful for making 2d bitmaps
// get drawn without being clipped by the zbuffer
void rend_SetZBias(float z_bias);

// Enables/disables writes the depth buffer
void rend_SetZBufferWriteMask(int state);

// Sets where the software renderer should write to
void rend_SetSoftwareParameters(float aspect, int width, int height, int pitch, uint8_t *framebuffer);

// Fills in some variables so the 3d math routines know how to project
void rend_GetProjectionParameters(int *width, int *height);
void rend_GetProjectionScreenParameters(int &screenLX, int &screenTY, int &screenW, int &screenH);

// Returns the aspect ratio of the physical screen
float rend_GetAspectRatio();

// Gets a pointer to a linear frame buffer
void rend_GetLFBLock(renderer_lfb *lfb);

// Releases an lfb lock
void rend_ReleaseLFBLock(renderer_lfb *lfb);

// Given a source x,y and width,height, draws any sized bitmap into the renderer lfb
void rend_DrawLFBBitmap(int sx, int sy, int w, int h, int dx, int dy, uint16_t *data, int rowsize);

//	given a chunked bitmap, renders it.
void rend_DrawChunkedBitmap(chunked_bitmap *chunk, int x, int y, uint8_t alpha);

//	given a chunked bitmap, renders it.scaled
void rend_DrawScaledChunkedBitmap(chunked_bitmap *chunk, int x, int y, int neww, int newh, uint8_t alpha);

// Draws a line using the states of the renderer
void rend_DrawSpecialLine(g3Point *p0, g3Point *p1);

// Sets some global preferences for the renderer
// Returns -1 if it had to use the default resolution/bitdepth
int rend_SetPreferredState(renderer_preferred_state *pref_state);

// Sets the gamma value
void rend_SetGammaValue(float val);

// Fills in the passed in pointer with the current rendering state
void rend_GetRenderState(rendering_state *rstate);

// Draws a simple bitmap at the specified x,y location
void rend_DrawSimpleBitmap(int bm_handle, int x, int y);

// Gets OpenGL ready to work in a window
int rend_InitOpenGLWindow(oeApplication *app, renderer_preferred_state *pref_state);

// Shuts down OpenGL in a window
void rend_CloseOpenGLWindow();

// Sets the state of the OpenGLWindow to on or off
void rend_SetOpenGLWindowState(int state, oeApplication *app, renderer_preferred_state *pref_state);

// Sets the hardware bias level for coplanar polygons
// This helps reduce z buffer artifaces
void rend_SetCoplanarPolygonOffset(float factor);

// Gets the error message string
const char *rend_GetErrorMessage();

// Sets the error message string
void rend_SetErrorMessage(const char *str);

// Preuploads a bitmap to the card
void rend_PreUploadTextureToCard(int, int);
void rend_FreePreUploadedTexture(int, int);

// Returns 1 if there is mid video memory, 2 if there is low vid memory, or 0 if there is large vid memory
int rend_LowVidMem();

// Returns 1 if the renderer supports bumpmapping
int rend_SupportsBumpmapping();

// Gets a bumpmap ready for drawing, or turns off bumpmapping
void rend_SetBumpmapReadyState(int state, int map);

// Clears the zbuffer
void rend_ClearZBuffer();

// Clears the texture cache
void rend_ResetCache();

// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y.
void rend_CopyBitmapToFramebuffer(int bm_handle, int x, int y);

// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void rend_SetFrameBufferCopyState(bool state);

#if defined(WIN32)
// returns the direct draw object
void *rend_RetrieveDirectDrawObj(void **frontsurf, void **backsurf);
#endif

#endif
