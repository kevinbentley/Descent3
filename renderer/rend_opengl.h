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

#ifndef REND_OPENGL_H
#define REND_OPENGL_H

#include "renderer.h"
#include "3d.h"

class oeApplication;

// Starts up opengl
int opengl_Init(oeApplication *app, renderer_preferred_state *pref_state);

// Closes down opengl
void opengl_Close();
void opengl_Shutdown();

// The main drawing function...draws a flat/textured/gouraud polygon
void opengl_DrawPolygon(int, g3Point **, int, int);

void opengl_SetFlatColor(ddgr_color color);

// Ends a frame
void opengl_EndFrame();

// Flips the screen
void opengl_Flip();

// Does setup for a new frame
void opengl_BeginFrame(int, int, int, int, int);

// Tells opengl what kind of texturing (linear/perspective) we want
void opengl_SetTextureType(texture_type);

// Sets the lighting state of opengl
void opengl_SetLightingState(light_state state);

// Sets the opengl color model (either rgb or mono)
void opengl_SetColorModel(color_model state);

// Sets the state of bilinear filtering for our textures
void opengl_SetFiltering(int8_t state);

// Sets the state of zbuffering to on or off
void opengl_SetZBufferState(int8_t state);

// Sets the near/far z values for zbuffering
void opengl_SetZValues(float nearz, float farz);

// Sets a bitmap as a lightmap to rendered on top of the next texture map
// a -1 value indicates no lighting map
void opengl_SetLightingMap(int handle);

// Clears the display to a specified color
void opengl_ClearScreen(ddgr_color color);

// Fills a rectangle on the display
void opengl_FillRect(ddgr_color color, int x1, int y1, int x2, int y2);

// Sets a pixel on the display
void opengl_SetPixel(ddgr_color color, int x, int y);

// Sets the near and far plane of fog
void opengl_SetFogBorders(float nearz, float farz);

// Sets the fog state to on or off
void opengl_SetFogState(int8_t state);

// Fills in projection variables
void opengl_GetProjectionParameters(int *width, int *height);
void opengl_GetProjectionScreenParameters(int &screenLX, int &screenTY, int &screenW, int &screenH);

// Returns the aspect ratio of the physical screen
float opengl_GetAspectRatio();

// Sets texture wrapping type
void opengl_SetWrapType(wrap_type val);

// Sets the constant alpha value
void opengl_SetAlphaValue(uint8_t val);

// Sets the overall alpha scale factor (all alpha values are scaled by this value)
// usefull for motion blur effect
void opengl_SetAlphaFactor(float val);

// Returns the current Alpha factor
float opengl_GetAlphaFactor(void);

// Sets the type of alpha blending you want
void opengl_SetAlphaType(int8_t atype);

// Sets whether or not to write into the zbuffer
void opengl_SetZBufferWriteMask(int state);

// Gets the current state of the renderer
void opengl_GetRenderState(rendering_state *rstate);

// draws a line
void opengl_DrawLine(int x1, int y1, int x2, int y2);

// draws a line
void opengl_DrawSpecialLine(g3Point *p0, g3Point *p1);

// Sets the color that opengl uses for fog
void opengl_SetFogColor(ddgr_color color);

// Sets the coplanar z bias for rendered polygons
void opengl_SetCoplanarPolygonOffset(float factor);

// Sets up a some global preferences for openGL
int opengl_SetPreferredState(renderer_preferred_state *pref_state);

// Sets the gamma correction value
void opengl_SetGammaValue(float val);

// Takes a screenshot of the frontbuffer and puts it into the passed bitmap handle
void opengl_Screenshot(int bm_handle);

// Returns the pixel color at x,y
ddgr_color opengl_GetPixel(int, int);

// Clears the zbuffer
void opengl_ClearZBuffer();

// Clears the texture cache
void opengl_ResetCache();

// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y
void opengl_CopyBitmapToFramebuffer(int bm_handle, int x, int y);

// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void opengl_SetFrameBufferCopyState(bool state);

#if defined(WIN32)
// returns directdraw object
void *opengl_DirectDrawObj();
#endif

// returns rendering statistics for the frame
void opengl_GetStatistics(tRendererStats *stats);


#endif
