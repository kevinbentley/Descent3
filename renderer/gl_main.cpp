/*
* Descent 3: Piccu Engine
* Copyright (C) 2024 Parallax Software
* Copyright (C) 2024 SaladBadger
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
#include "gl_local.h"
#include "rtperformance.h"
#include "gl_shader.h"

#include <NewBitmap.h>

oeApplication* ParentApplication = nullptr;

bool Renderer_initted;
bool Renderer_close_flag;
bool UseHardware = true;
bool StateLimited;
bool NoLightmaps;
bool UseMultitexture;
renderer_type Renderer_type = RENDERER_OPENGL;

bool OpenGL_multitexture_state;
bool OpenGL_packed_pixels;
bool Fast_test_render = false;
module *OpenGLDLLHandle = nullptr;

constexpr int NUM_FBOS = 2;
Framebuffer framebuffers[NUM_FBOS];
int framebuffer_current_draw;

unsigned int framebuffer_blit_x, framebuffer_blit_y, framebuffer_blit_w, framebuffer_blit_h;

ShaderProgram blitshader;
//Temp shader to test the shader systems. 
ShaderProgram testshader;
GLint blitshader_gamma = -1;

static float mat4_identity[16] =
{ 1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };


// Init our renderer
int rend_Init(renderer_type state, oeApplication* app, renderer_preferred_state* pref_state)
{
#ifndef DEDICATED_ONLY
	int retval = 0;
	rend_SetRendererType(state);
	if (!Renderer_initted)
	{
		if (!Renderer_close_flag)
		{
			atexit(rend_Close);
			Renderer_close_flag = 1;
		}

		Renderer_initted = 1;
	}
	else
	{
		return 1; //[ISB] don't double dip on renderer initialization. This happens after an int3
	}

	mprintf((0, "Renderer init is set to %d\n", Renderer_initted));

	retval = opengl_Init(app, pref_state);

	extern const char* blitVertexSrc;
	extern const char* blitFragmentSrc;
	blitshader.AttachSource(blitVertexSrc, blitFragmentSrc);
	blitshader_gamma = blitshader.FindUniform("gamma");
	if (blitshader_gamma == -1)
		Error("rend_Init: Failed to find gamma uniform!");

	//Simple shader for testing, before everything is made to use shaders. 
	extern const char* testVertexSrc;
	extern const char* testFragmentSrc;
	testshader.AttachSource(testVertexSrc, testFragmentSrc);

	//[ISB] moved here.. stupid. 
	opengl_SetGammaValue(OpenGL_preferred_state.gamma);

	return retval;
#else
	return 0;
#endif
}

void rend_Close(void)
{
	mprintf((0, "CLOSE:Renderer init is set to %d\n", Renderer_initted));
	if (!Renderer_initted)
		return;

	blitshader.Destroy();
	opengl_Close();

	Renderer_initted = false;
}

void GL_Ortho(float* mat, float left, float right, float bottom, float top, float znear, float zfar)
{
	memset(mat, 0, sizeof(float[16]));
	mat[0] = 2 / (right - left);
	mat[5] = 2 / (top - bottom);
	mat[10] = -2 / (zfar - znear);
	mat[12] = -((right + left) / (right - left));
	mat[13] = -((top + bottom) / (top - bottom));
	mat[14] = -((zfar + znear) / (zfar - znear));
	mat[15] = 1;
	/*		2 / (right - left), 0, 0, 0,
		0, 2 / (top - bottom), 0, 0,
		0, 0, -2 / (zfar - znear), 0,
		-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((zfar + znear) / (zfar - znear)), 1*/
}

void opengl_UpdateWindow()
{
	int width, height;
	if (!OpenGL_preferred_state.fullscreen)
	{
		SDL_SetWindowPosition(SDL_GL_GetCurrentWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		int x, y;
		SDL_GetWindowPosition(SDL_GL_GetCurrentWindow(), &x, &y);
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, &height);
		ParentApplication->set_sizepos(x, y, width, height);
		ParentApplication->set_flags(OEAPP_WINDOWED);
	}
	else
	{
		ParentApplication->set_flags(OEAPP_FULLSCREEN);

		SDL_DisplayMode dm{};
		SDL_GetCurrentDisplayMode(0, &dm);

		OpenGL_state.view_width = dm.w;
		OpenGL_state.view_height = dm.h;

		width = OpenGL_preferred_state.width;
		height = OpenGL_preferred_state.height;
	}

	float baseAspect = width / (float)height;
	float trueAspect = OpenGL_state.view_width / (float)OpenGL_state.view_height;

	if (baseAspect < trueAspect) //base screen is less wide, so pillarbox it
	{
		framebuffer_blit_h = OpenGL_state.view_height; framebuffer_blit_y = 0;
		framebuffer_blit_w = OpenGL_state.view_height * baseAspect; framebuffer_blit_x = (OpenGL_state.view_width - framebuffer_blit_w) / 2;
	}
	else //base screen is more wide, so letterbox it
	{
		framebuffer_blit_w = OpenGL_state.view_width; framebuffer_blit_x = 0;
		framebuffer_blit_h = OpenGL_state.view_width / baseAspect; framebuffer_blit_y = (OpenGL_state.view_height - framebuffer_blit_h) / 2;
	}

	OpenGL_state.screen_width = width;
	OpenGL_state.screen_height = height;
}

void opengl_SetViewport()
{
	//[ISB] the hardware t&l code is AWFUL and the software t&l code won't compile. 
	// Reverting it back to only ever using passthrough. 
	// Projection
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho((GLfloat)0.0f, (GLfloat)(OpenGL_preferred_state.width), (GLfloat)(OpenGL_preferred_state.height), (GLfloat)0.0f, 0.0f, 1.0f);

	float left = 0;
	float right = OpenGL_preferred_state.width;
	float bottom = OpenGL_preferred_state.height;
	float top = 0;
	float znear = 0;
	float zfar = 1;

	float projection[16];
	GL_Ortho(projection, left, right, bottom, top, znear, zfar);

	GL_UpdateLegacyBlock(projection, mat4_identity);
	// Viewport
	glViewport(0, 0, OpenGL_preferred_state.width, OpenGL_preferred_state.height);

	// ModelView
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

// Sets some global preferences for the renderer
int rend_SetPreferredState(renderer_preferred_state* pref_state)
{
	int retval = 1;
	renderer_preferred_state old_state = OpenGL_preferred_state;

	OpenGL_preferred_state = *pref_state;
	if (OpenGL_state.initted)
	{
		int reinit = 0;
		mprintf((0, "Inside pref state!\n"));

		// Change gamma if needed
		/*if( pref_state->width!=OpenGL_state.screen_width || pref_state->height!=OpenGL_state.screen_height || old_state.bit_depth!=pref_state->bit_depth)
		{
			reinit=1;
		}

		if( reinit )
		{
			opengl_Close();
			retval = opengl_Init( NULL, &OpenGL_preferred_state );
		}
		else
		{*/

		if (pref_state->width != OpenGL_state.screen_width || pref_state->height != OpenGL_state.screen_height
			|| pref_state->window_width != OpenGL_state.view_width || pref_state->window_height != OpenGL_state.view_height
			|| pref_state->fullscreen != old_state.fullscreen || pref_state->antialised != old_state.antialised)
		{
			opengl_UpdateWindow();
			opengl_SetViewport();
			opengl_UpdateFramebuffer();
		}

		if (old_state.gamma != pref_state->gamma)
		{
			opengl_SetGammaValue(pref_state->gamma);
		}

#ifdef WIN32
		if (dwglSwapIntervalEXT)
		{
			if (pref_state->vsync_on)
				dwglSwapIntervalEXT(1);
			else
				dwglSwapIntervalEXT(0);
		}
#endif
		//}
	}
	else
	{
		OpenGL_preferred_state = *pref_state;
	}

	return retval;
}

void rend_StartFrame(int x1, int y1, int x2, int y2, int clear_flags)
{
	if (clear_flags & RF_CLEAR_ZBUFFER)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	OpenGL_state.clip_x1 = x1;
	OpenGL_state.clip_y1 = y1;
	OpenGL_state.clip_x2 = x2;
	OpenGL_state.clip_y2 = y2;

	//[ISB] Use the viewport to constrain the clipping window so that the new hardware code 
	//can work with the legacy code.
	float projection[16];
	GL_Ortho(projection, 0, x2 - x1, y2 - y1, 0, 0, 1);

	GL_UpdateLegacyBlock(projection, mat4_identity);

	glViewport(x1, OpenGL_state.screen_height - y2, x2 - x1, y2 - y1);
}

static int OpenGL_last_frame_polys_drawn = 0;
static int OpenGL_last_frame_verts_processed = 0;
static int OpenGL_last_uploaded = 0;

// Flips the screen
void rend_Flip(void)
{
#ifndef NDEBUG
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		mprintf((0, "Error entering flip: %d\n", err));
	}
#endif
#ifndef RELEASE
	int i;

	RTP_INCRVALUE(texture_uploads, OpenGL_uploads);
	RTP_INCRVALUE(polys_drawn, OpenGL_polys_drawn);

	mprintf_at((1, 1, 0, "Uploads=%d    Polys=%d   Verts=%d   ", OpenGL_uploads, OpenGL_polys_drawn, OpenGL_verts_processed));
	mprintf_at((1, 2, 0, "Sets= 0:%d   1:%d   2:%d   3:%d   ", OpenGL_sets_this_frame[0], OpenGL_sets_this_frame[1], OpenGL_sets_this_frame[2], OpenGL_sets_this_frame[3]));
	mprintf_at((1, 3, 0, "Sets= 4:%d   5:%d  ", OpenGL_sets_this_frame[4], OpenGL_sets_this_frame[5]));
	for (i = 0; i < 10; i++)
	{
		OpenGL_sets_this_frame[i] = 0;
	}
#endif

	OpenGL_last_frame_polys_drawn = OpenGL_polys_drawn;
	OpenGL_last_frame_verts_processed = OpenGL_verts_processed;
	OpenGL_last_uploaded = OpenGL_uploads;

	OpenGL_uploads = 0;
	OpenGL_polys_drawn = 0;
	OpenGL_verts_processed = 0;

	if (OpenGL_preferred_state.gamma == 1.0)
		framebuffers[framebuffer_current_draw].BlitToRaw(0, framebuffer_blit_x, framebuffer_blit_y, framebuffer_blit_w, framebuffer_blit_h);
	else
	{
		blitshader.Use();
		framebuffers[framebuffer_current_draw].BlitTo(0, framebuffer_blit_x, framebuffer_blit_y, framebuffer_blit_w, framebuffer_blit_h);
		glUseProgram(0);
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

#ifndef NDEBUG
	err = glGetError();
	if (err != GL_NO_ERROR)
	{
		mprintf((0, "Error blitting to real framebuffer: %d\n", err));
	}
#endif

#if defined(WIN32)	
	SwapBuffers((HDC)hOpenGLDC);
#elif defined(__LINUX__)
	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
#endif

	framebuffer_current_draw = (framebuffer_current_draw + 1) % NUM_FBOS;
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffers[framebuffer_current_draw].Handle());

#ifndef NDEBUG
	err = glGetError();
	if (err != GL_NO_ERROR)
	{
		mprintf((0, "Error setting framebuffer back: %d\n", err));
	}
#endif

#ifdef __PERMIT_GL_LOGGING
	if (__glLog == true)
	{
		DGL_LogNewFrame();
	}
#endif
}

void rend_EndFrame(void)
{
}


// returns true if the passed in extension name is supported
bool opengl_CheckExtension(char* extName)
{
	GLint extcount;
	glGetIntegerv(GL_NUM_EXTENSIONS, &extcount);
	for (int i = 0; i < extcount; i++)
	{
		const GLubyte* extname = glGetStringi(GL_EXTENSIONS, i);
		if (!stricmp((const char*)extname, extName))
			return true;
	}

	return false;
}

void opengl_SetGammaValue(float val)
{
	blitshader.Use();

	glUniform1f(blitshader_gamma, 1.f / val);

	glUseProgram(0);
}

void rend_SetFlatColor(ddgr_color color)
{
	OpenGL_state.cur_color = color;
}

// Sets the fog state to TRUE or FALSE
void rend_SetFogState(int8_t state)
{
	if (state == OpenGL_state.cur_fog_state)
		return;

	OpenGL_state.cur_fog_state = state;
	if (state == 1)
	{
		//TODO
		//glEnable(GL_FOG);
	}
	else
	{
		//glDisable(GL_FOG);
	}
}

// Sets the near and far plane of fog
void rend_SetFogBorders(float nearz, float farz)
{
	// Sets the near and far plane of fog
	float fogStart = nearz;
	float fogEnd = farz;

	OpenGL_state.cur_fog_start = fogStart;
	OpenGL_state.cur_fog_end = fogEnd;

	//glFogi(GL_FOG_MODE, GL_LINEAR);
	//glFogf(GL_FOG_START, fogStart);
	//glFogf(GL_FOG_END, fogEnd);
}

void rend_SetLighting(light_state state)
{
	if (state == OpenGL_state.cur_light_state)
		return;	// No redundant state setting
	if (UseMultitexture && Last_texel_unit_set != 0)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		Last_texel_unit_set = 0;
	}

	OpenGL_sets_this_frame[4]++;

	switch (state)
	{
	case LS_NONE:
		//glShadeModel(GL_SMOOTH);
		OpenGL_state.cur_light_state = LS_NONE;
		break;
	case LS_FLAT_GOURAUD:
		//glShadeModel(GL_SMOOTH);
		OpenGL_state.cur_light_state = LS_FLAT_GOURAUD;
		break;
	case LS_GOURAUD:
	case LS_PHONG:
		//glShadeModel(GL_SMOOTH);
		OpenGL_state.cur_light_state = LS_GOURAUD;
		break;
	default:
		Int3();
		break;
	}

	CHECK_ERROR(13)
}

void rend_SetRendererType(renderer_type state)
{
	Renderer_type = state;
	mprintf((0, "RendererType is set to %d.\n", state));
}

void rend_SetColorModel(color_model state)
{
	switch (state)
	{
	case CM_MONO:
		OpenGL_state.cur_color_model = CM_MONO;
		break;
	case CM_RGB:
		OpenGL_state.cur_color_model = CM_RGB;
		break;
	default:
		Int3();
		break;
	}
}

void rend_SetTextureType(texture_type state)
{
	if (state == OpenGL_state.cur_texture_type)
		return;	// No redundant state setting
	if (UseMultitexture && Last_texel_unit_set != 0)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		Last_texel_unit_set = 0;
	}
	OpenGL_sets_this_frame[3]++;

	switch (state)
	{
	case TT_FLAT:
		OpenGL_state.cur_texture_quality = 0;
		break;
	case TT_LINEAR:
	case TT_LINEAR_SPECIAL:
	case TT_PERSPECTIVE:
	case TT_PERSPECTIVE_SPECIAL:
		OpenGL_state.cur_texture_quality = 2;
		break;
	default:
		Int3();	// huh? Get Jason
		break;
	}

	CHECK_ERROR(12)
		OpenGL_state.cur_texture_type = state;
}

// Sets where the software renderer should write to
void rend_SetSoftwareParameters(float aspect, int width, int height, int pitch, uint8_t* framebuffer)
{
}

// Sets the state of bilinear filtering for our textures
void rend_SetFiltering(int8_t state)
{
	OpenGL_state.cur_bilinear_state = state;
}

// Sets the state of z-buffering to on or off
void rend_SetZBufferState(int8_t state)
{
	if (state == OpenGL_state.cur_zbuffer_state)
		return;	// No redundant state setting

	OpenGL_sets_this_frame[5]++;
	OpenGL_state.cur_zbuffer_state = state;

	//	mprintf ((0,"OPENGL: Setting zbuffer state to %d.\n",state)); 

	if (state)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	CHECK_ERROR(14)
}

// Sets the near and far planes for z buffer
void rend_SetZValues(float nearz, float farz)
{
	OpenGL_state.cur_near_z = nearz;
	OpenGL_state.cur_far_z = farz;
	//	mprintf ((0,"OPENGL:Setting depth range to %f - %f\n",nearz,farz));
}

// Sets a bitmap as a overlay map to rendered on top of the next texture map
// a -1 value indicates no overlay map
void rend_SetOverlayMap(int handle)
{
	Overlay_map = handle;
}

void rend_SetOverlayType(uint8_t type)
{
	Overlay_type = type;
}

// Clears the display to a specified color
void rend_ClearScreen(ddgr_color color)
{
	int r = (color >> 16 & 0xFF);
	int g = (color >> 8 & 0xFF);
	int b = (color & 0xFF);

	glClearColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Clears the zbuffer for the screen
void rend_ClearZBuffer(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

// Clears the zbuffer for the screen
void rend_ResetCache(void)
{
	mprintf((0, "Resetting texture cache!\n"));
	opengl_ResetCache();
}

// Sets the color of fog
void rend_SetFogColor(ddgr_color color)
{
	if (color == OpenGL_state.cur_fog_color)
		return;

	float fc[4];
	fc[0] = GR_COLOR_RED(color);
	fc[1] = GR_COLOR_GREEN(color);
	fc[2] = GR_COLOR_BLUE(color);
	fc[3] = 1;

	fc[0] /= 255.0f;
	fc[1] /= 255.0f;
	fc[2] /= 255.0f;

	//TODO:
	//glFogfv(GL_FOG_COLOR, fc);
}

// Sets the lighting state of opengl
void rend_SetLightingState(light_state state)
{
	if (state == OpenGL_state.cur_light_state)
		return;	// No redundant state setting

	if (UseMultitexture && Last_texel_unit_set != 0)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		Last_texel_unit_set = 0;
	}

	OpenGL_sets_this_frame[4]++;

	switch (state)
	{
	case LS_NONE:
		//glShadeModel(GL_SMOOTH);
		OpenGL_state.cur_light_state = LS_NONE;
		break;
	case LS_FLAT_GOURAUD:
		//glShadeModel(GL_SMOOTH);
		OpenGL_state.cur_light_state = LS_FLAT_GOURAUD;
		break;
	case LS_GOURAUD:
	case LS_PHONG:
		//glShadeModel(GL_SMOOTH);
		OpenGL_state.cur_light_state = LS_GOURAUD;
		break;
	default:
		Int3();
		break;
	}

	CHECK_ERROR(13)
}
// returns the alpha that we should use
float opengl_GetAlphaMultiplier(void)
{
	switch (OpenGL_state.cur_alpha_type)
	{
	case AT_ALWAYS:
		return 1.0;
	case AT_CONSTANT:
		return OpenGL_state.cur_alpha / 255.0;
	case AT_TEXTURE:
		return 1.0;
	case AT_CONSTANT_TEXTURE:
		return OpenGL_state.cur_alpha / 255.0;
	case AT_VERTEX:
		return 1.0;
	case AT_CONSTANT_TEXTURE_VERTEX:
	case AT_CONSTANT_VERTEX:
		return OpenGL_state.cur_alpha / 255.0;
	case AT_TEXTURE_VERTEX:
		return 1.0;
	case AT_LIGHTMAP_BLEND:
	case AT_LIGHTMAP_BLEND_SATURATE:
		return OpenGL_state.cur_alpha / 255.0;
	case AT_SATURATE_TEXTURE:
		return OpenGL_state.cur_alpha / 255.0;
	case AT_SATURATE_VERTEX:
		return 1.0;
	case AT_SATURATE_CONSTANT_VERTEX:
		return OpenGL_state.cur_alpha / 255.0;
	case AT_SATURATE_TEXTURE_VERTEX:
		return 1.0;
	case AT_SPECULAR:
		return 1.0;
	default:
		//Int3();		// no type defined,get jason
		return 0;
	}
}


void opengl_SetAlwaysAlpha(bool state)
{
	if (state && OpenGL_blending_on)
	{
		glDisable(GL_BLEND);
		//glDisable(GL_ALPHA_TEST);
		OpenGL_blending_on = false;
	}
	else if (!state)
	{
		glEnable(GL_BLEND);
		//glEnable(GL_ALPHA_TEST);
		OpenGL_blending_on = true;
	}
}

void rend_SetAlphaType(int8_t atype)
{
	if (atype == OpenGL_state.cur_alpha_type)
		return;		// don't set it redundantly
	if (UseMultitexture && Last_texel_unit_set != 0)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		Last_texel_unit_set = 0;

	}
	OpenGL_sets_this_frame[6]++;

	switch (atype)
	{
	case AT_ALWAYS:
		rend_SetAlphaValue(255);
		opengl_SetAlwaysAlpha(true);
		glBlendFunc(GL_ONE, GL_ZERO);
		break;
	case AT_CONSTANT:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case AT_TEXTURE:
		rend_SetAlphaValue(255);
		opengl_SetAlwaysAlpha(true);
		glBlendFunc(GL_ONE, GL_ZERO);
		break;
	case AT_CONSTANT_TEXTURE:
	case AT_CONSTANT_TEXTURE_VERTEX:
	case AT_TEXTURE_VERTEX:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case AT_CONSTANT_VERTEX:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case AT_VERTEX:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case AT_LIGHTMAP_BLEND:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		break;
	case AT_SATURATE_TEXTURE:
	case AT_LIGHTMAP_BLEND_SATURATE:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case AT_SATURATE_VERTEX:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case AT_SATURATE_CONSTANT_VERTEX:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case AT_SATURATE_TEXTURE_VERTEX:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case AT_SPECULAR:
		opengl_SetAlwaysAlpha(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		//hack
		OpenGL_state.cur_texture_quality = 2;
		OpenGL_state.cur_texture_type = TT_PERSPECTIVE;

		break;
	default:
		Int3();		// no type defined,get jason
		break;
	}
	OpenGL_state.cur_alpha_type = atype;
	Alpha_multiplier = opengl_GetAlphaMultiplier();
	CHECK_ERROR(15)
}

// Sets the alpha value for constant alpha
void rend_SetAlphaValue(uint8_t val)
{
	OpenGL_state.cur_alpha = val;
	Alpha_multiplier = opengl_GetAlphaMultiplier();
}

// Sets the overall alpha scale factor (all alpha values are scaled by this value)
// usefull for motion blur effect
void rend_SetAlphaFactor(float val)
{
	if (val < 0.0f) val = 0.0f;
	if (val > 1.0f) val = 1.0f;
	OpenGL_Alpha_factor = val;
}

// Returns the current Alpha factor
float rend_GetAlphaFactor(void)
{
	return OpenGL_Alpha_factor;
}

// Sets the texture wrapping type
void rend_SetWrapType(wrap_type val)
{
	OpenGL_state.cur_wrap_type = val;
}

void rend_SetZBias(float z_bias)
{
	if (Z_bias != z_bias)
	{
		Z_bias = z_bias;
	}
}

// Enables/disables writes the depth buffer
void rend_SetZBufferWriteMask(int state)
{
	OpenGL_sets_this_frame[5]++;
	if (state)
	{
		glDepthMask(GL_TRUE);
	}
	else
	{
		glDepthMask(GL_FALSE);
	}
}

// Returns the aspect ratio of the physical screen
void rend_GetProjectionParameters(int* width, int* height)
{
	*width = OpenGL_state.clip_x2 - OpenGL_state.clip_x1;
	*height = OpenGL_state.clip_y2 - OpenGL_state.clip_y1;
}

void rend_GetProjectionScreenParameters(int& screenLX, int& screenTY, int& screenW, int& screenH)
{
	screenLX = OpenGL_state.clip_x1;
	screenTY = OpenGL_state.clip_y1;
	screenW = OpenGL_state.clip_x2 - OpenGL_state.clip_x1 + 1;
	screenH = OpenGL_state.clip_y2 - OpenGL_state.clip_y1 + 1;
}

// Returns the aspect ratio of the physical screen
float rend_GetAspectRatio(void)
{
	float aspect_ratio = (float)((3.0f * OpenGL_state.screen_width) / (4.0f * OpenGL_state.screen_height));
	return aspect_ratio;
}

// Sets the hardware bias level for coplanar polygons
// This helps reduce z buffer artifacts
void rend_SetCoplanarPolygonOffset(float factor)
{
	if (factor == 0.0f)
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(-1.0f, -1.0f);
	}
}

// Preuploads a texture to the video card
void rend_PreUploadTextureToCard(int handle, int map_type)
{
}

// Frees an uploaded texture from the video card
void rend_FreePreUploadedTexture(int handle, int map_type)
{
}

char Renderer_error_message[256];
// Retrieves an error message
const char* rend_GetErrorMessage()
{
	return Renderer_error_message;
}

// Sets an error message
void rend_SetErrorMessage(const char* str)
{
	ASSERT(strlen(str) < 256);
	strcpy(Renderer_error_message, str);
}

// Returns 1 if there is mid video memory, 2 if there is low vid memory, or 0 if there is large vid memory
int rend_LowVidMem(void)
{
	return 0;
}

// Returns 1 if the renderer supports bumpmapping
int rend_SupportsBumpmapping(void)
{
	return 0;
}

// Sets a bumpmap to be rendered, or turns off bumpmapping altogether
void rend_SetBumpmapReadyState(int state, int map)
{
}

// returns the direct draw object 
void* rend_RetrieveDirectDrawObj(void** frontsurf, void** backsurf)
{
	*frontsurf = NULL;
	*backsurf = NULL;
	return NULL;
}

// returns rendering statistics for the frame
void rend_GetStatistics(tRendererStats* stats)
{
	if (Renderer_initted)
	{
		stats->poly_count = OpenGL_last_frame_polys_drawn;
		stats->vert_count = OpenGL_last_frame_verts_processed;
		stats->texture_uploads = OpenGL_last_uploaded;
	}
	else
	{
		memset(stats, 0, sizeof(tRendererStats));
	}
}

// Tells the software renderer whether or not to use mipping
void rend_SetMipState(int8_t mipstate)
{
	OpenGL_state.cur_mip_state = mipstate;
}

void rend_TransformSetToPassthru(void)
{
}

void rend_TransformSetViewport(int lx, int ty, int width, int height)
{
}

void rend_TransformSetProjection(float trans[4][4])
{
}

void rend_TransformSetModelView(float trans[4][4])
{
}

// Fills in the passed in pointer with the current rendering state
void rend_GetRenderState(rendering_state* rstate)
{
	memcpy(rstate, &OpenGL_state, sizeof(rendering_state));
}

void rend_DLLGetRenderState(DLLrendering_state* rstate)
{
#define COPY_ELEMENT(element) rstate->element = OpenGL_state.element;
	COPY_ELEMENT(initted);
	COPY_ELEMENT(cur_bilinear_state);
	COPY_ELEMENT(cur_zbuffer_state);
	COPY_ELEMENT(cur_fog_state);
	COPY_ELEMENT(cur_mip_state);
	COPY_ELEMENT(cur_texture_type);
	COPY_ELEMENT(cur_color_model);
	COPY_ELEMENT(cur_light_state);
	COPY_ELEMENT(cur_alpha_type);
	COPY_ELEMENT(cur_wrap_type);
	COPY_ELEMENT(cur_fog_start);
	COPY_ELEMENT(cur_fog_end);
	COPY_ELEMENT(cur_near_z);
	COPY_ELEMENT(cur_far_z);
	COPY_ELEMENT(gamma_value);
	COPY_ELEMENT(cur_alpha);
	COPY_ELEMENT(cur_color);
	COPY_ELEMENT(cur_fog_color);
	COPY_ELEMENT(cur_texture_quality);
	COPY_ELEMENT(clip_x1);
	COPY_ELEMENT(clip_x2);
	COPY_ELEMENT(clip_y1);
	COPY_ELEMENT(clip_y2);
	COPY_ELEMENT(screen_width);
	COPY_ELEMENT(screen_height);
#undef COPY_ELEMENT
}

// Takes a screenshot of the current frame and puts it into the handle passed
std::unique_ptr<NewBitmap> rend_Screenshot() {
  uint16_t *dest_data;
  uint32_t *temp_data;

  int total = OpenGL_state.screen_width * OpenGL_state.screen_height;
  auto result = std::make_unique<NewBitmap>(OpenGL_state.screen_width, OpenGL_state.screen_height, PixelDataFormat::RGBA32, true);

  if (!result || result->getData() == nullptr) {
    return nullptr;
  }

  glad_glReadPixels(0, 0, OpenGL_state.screen_width, OpenGL_state.screen_height, GL_RGBA, GL_UNSIGNED_BYTE,
                (GLvoid *)result->getData());

  return result;
}

// Takes a screenshot of the current frame and puts it into the handle passed
void rend_Screenshot(int bm_handle) {
  auto screenshot = rend_Screenshot();
  auto *temp_data = reinterpret_cast<uint32_t*>(screenshot->getData());

  uint32_t w, h;
  screenshot->getSize(w, h);

  ASSERT((bm_w(bm_handle, 0)) == OpenGL_state.screen_width);
  ASSERT((bm_h(bm_handle, 0)) == OpenGL_state.screen_height);

  uint16_t* dest_data = bm_data(bm_handle, 0);

  for (int i = 0; i < h; i++) {
    for (int t = 0; t < w; t++) {
      uint32_t spix = temp_data[i * w + t];

      int r = spix & 0xff;
      int g = (spix >> 8) & 0xff;
      int b = (spix >> 16) & 0xff;

      dest_data[(((h - 1) - i) * w) + t] = GR_RGB16(r, g, b);
    }
  }
}

void opengl_UpdateFramebuffer(void)
{
	for (int i = 0; i < NUM_FBOS; i++)
	{
		framebuffers[i].Update(OpenGL_state.screen_width, OpenGL_state.screen_height, OpenGL_preferred_state.antialised);
	}

	framebuffer_current_draw = 0;
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffers[0].Handle());
	//Unbind the read framebuffer so that OBS can capture the window properly
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	GL_InitFramebufferVAO();
}

void opengl_CloseFramebuffer(void)
{
	for (int i = 0; i < NUM_FBOS; i++)
	{
		framebuffers[i].Destroy();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GL_DestroyFramebufferVAO();
}

//shader test
void rend_UseShaderTest(void)
{
	testshader.Use();
}

void rend_EndShaderTest(void)
{
	glUseProgram(0);
}
