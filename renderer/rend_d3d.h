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
*/

#ifndef REND_D3D_H
#define REND_D3D_H

#include "renderer.h"
#include "3d.h"

class oeApplication;

// Starts up glide
int d3d_Init(oeApplication *app, renderer_preferred_state *pref_state);

// Closes down glide
void d3d_Close();

// The main drawing function...draws a flat/textured/gouraud polygon
void d3d_DrawPolygon(int, g3Point **, int, int);

void d3d_SetFlatColor(ddgr_color color);

// Ends a frame
void d3d_EndFrame();

// Flips the screen
void d3d_Flip();

// Does setup for a new frame
void d3d_BeginFrame(int, int, int, int, int);

// Tells glide what kind of texturing (linear/perspective) we want
void d3d_SetTextureType(texture_type);

// Sets the lighting state of glide
void d3d_SetLightingState(light_state state);

// Sets the glide color model (either rgb or mono)
void d3d_SetColorModel(color_model state);

// Sets the state of bilinear filtering for our textures
void d3d_SetFiltering(int8_t state);

// Sets the state of zbuffering to on or off
void d3d_SetZBufferState(int8_t state);

// Sets the near/far z values for zbuffering
void d3d_SetZValues(float nearz, float farz);

// Sets a bitmap as a lightmap to rendered on top of the next texture map
// a -1 value indicates no lighting map
void d3d_SetLightingMap(int handle);

// Clears the display to a specified color
void d3d_ClearScreen(ddgr_color color);

// Fills a rectangle on the display
void d3d_FillRect(ddgr_color color, int x1, int y1, int x2, int y2);

// Sets a pixel on the display
void d3d_SetPixel(ddgr_color color, int x, int y);

// Sets the near and far plane of fog
void d3d_SetFogBorders(float nearz, float farz);

// Sets the fog state to on or off
void d3d_SetFogState(int8_t state);

// Draws a 2d line
void d3d_DrawLine(int x1, int y1, int x2, int y2);

// sets fog color
void d3d_SetFogColor(ddgr_color fogcolor);

// sets the alpha type
void d3d_SetAlphaType(int8_t);

// Sets the constant alpha value
void d3d_SetAlphaValue(uint8_t val);

// Sets the overall alpha scale factor (all alpha values are scaled by this value)
// usefull for motion blur effect
void d3d_SetAlphaFactor(float val);

// Returns the current Alpha factor
float d3d_GetAlphaFactor(void);

// Sets the glide wrapping type
void d3d_SetWrapType(wrap_type val);

// Takes a screenshot of the frontbuffer and puts it into the passed bitmap handle
void d3d_Screenshot(int bm_handle);

// Sets write mask for depth buffer
void d3d_SetZBufferWriteMask(int state);

// Locks the linear frame buffer for application access
void d3d_GetLFBLock(renderer_lfb *lfb);

// Releases the previous LFB lock
void d3d_ReleaseLFBLock(renderer_lfb *lfb);

void d3d_GetProjectionParameters(int *width, int *height);
float d3d_GetAspectRatio();

// Draws a line using the states set by the renderer lib
void d3d_DrawSpecialLine(g3Point *p0, g3Point *p1);

void d3d_SetMipState(int8_t);

// Sets up a some global preferences for glide
int d3d_SetPreferredState(renderer_preferred_state *pref_state);

// Sets the gamma correction value
void d3d_SetGammaValue(float val);

// Gets the current state of the renderer
void d3d_GetRenderState(rendering_state *rstate);

// Sets the resolution that glide uses
void d3d_SetResolution(int width, int height);

// Sets the coplanar z bias for rendered polygons
void d3d_SetCoplanarPolygonOffset(float factor);

// Creates a on the video card if needed
void d3d_PreUploadTextureToCard(int handle, int map_type);

// Evicts local texture memory
void d3d_FreePreUploadedTexture(int handle, int map_type);

// Returns a string describing the passed in error
const char *d3d_ErrorString(int error);

// Takes a screenshot of the frontbuffer and puts it into the passed bitmap handle
void d3d_Screenshot(int bm_handle);

// Returns 1 if the renderer supports bumpmapping
int d3d_SupportsBumpmapping();

// Clears the zbuffer
void d3d_ClearZBuffer();

// Clears the texture cache
void d3d_ResetCache();

// Creates or destroys a linear framebuffer lock
void d3d_GetLFBLock(renderer_lfb *lfb);
void d3d_ReleaseLFBLock(renderer_lfb *lfb);

// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y
void d3d_CopyBitmapToFramebuffer(int bm_handle, int x, int y);

// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void d3d_SetFrameBufferCopyState(bool state);

#if defined(WIN32)
// returns directdraw object
void *d3d_DirectDrawObj(void **frontsurf, void **backsurf);
#endif

// returns rendering statistics for the frame
void d3d_GetStatistics(tRendererStats *stats);

#endif
