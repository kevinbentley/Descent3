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
#pragma once

#ifdef WIN32
#define NOMINMAX
#include <Windows.h>
#include "wglext.h"
#endif
#include <algorithm>
#include <glad/gl.h>
#define DD_ACCESS_RING //need direct access to some stuff
#include "application.h"
#include "3d.h"
#include "renderer.h"
#include "vecmat.h"
#include "bitmap.h"
#include "lightmap.h"
#include "mem.h"
#include "mono.h"
#include "pserror.h"
#include "gl_shader.h"
#include "module.h"

#define CHECK_ERROR(n) //need to decide what it does. 

#define GL_DEBUG

#ifdef WIN32
//typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int interval);
extern PFNWGLSWAPINTERVALEXTPROC dwglSwapIntervalEXT;

extern HWND hOpenGLWnd;
extern HDC hOpenGLDC;
#endif

//gl_init.cpp
extern bool OpenGL_packed_pixels;
extern bool OpenGL_debugging_enabled;
int opengl_Init(oeApplication* app, renderer_preferred_state* pref_state);
void opengl_Close();

//gl_main.cpp
extern oeApplication* ParentApplication;
extern renderer_preferred_state OpenGL_preferred_state;
extern rendering_state OpenGL_state;
extern bool Fast_test_render;

bool opengl_CheckExtension(char* extName);
void opengl_SetGammaValue(float val);
void opengl_UpdateFramebuffer(void);
void opengl_CloseFramebuffer(void);
void opengl_SetViewport();
void opengl_UpdateWindow();


//gl_image.cpp
extern int OpenGL_last_bound[2];
extern int OpenGL_sets_this_frame[10];
extern int OpenGL_uploads;
extern int Last_texel_unit_set;

#define GET_WRAP_STATE(x)	((x>>2) & 0x03)
#define GET_MIP_STATE(x)	((x>>1) & 0x01);
#define GET_FILTER_STATE(x)	(x & 0x01)

#define SET_WRAP_STATE(x,s) {x&=0xF3; x|=(s<<2);}
#define SET_MIP_STATE(x,s) {x&=0xFD; x|=(s<<1);}
#define SET_FILTER_STATE(x,s) {x&=0xFE; x|=(s);}

void opengl_InitImages(void);
void opengl_FreeImages(void);
int opengl_MakeTextureObject(int tn);
int opengl_MakeBitmapCurrent(int handle, int map_type, int tn);
void opengl_TranslateBitmapToOpenGL(int texnum, int bm_handle, int map_type, int replace, int tn);
void opengl_MakeWrapTypeCurrent(int handle, int map_type, int tn);
void opengl_MakeFilterTypeCurrent(int handle, int map_type, int tn);
int opengl_InitCache(void);
void opengl_ResetCache(void);
void opengl_FreeCache(void);
void opengl_SetUploadBufferSize(int width, int height);
void opengl_FreeUploadBuffers(void);

//gl_draw.cpp
extern float OpenGL_Alpha_factor;
extern float Alpha_multiplier;
extern bool OpenGL_blending_on;
extern bool OpenGL_multitexture_state;
extern int OpenGL_polys_drawn;
extern int OpenGL_verts_processed;
extern module *OpenGLDLLHandle;

void opengl_SetDrawDefaults(void);
void rend_SetLightingState(light_state state);
void rend_SetMipState(int8_t mipstate);
void opengl_DrawMultitexturePolygon3D(int handle, g3Point** p, int nv, int map_type);
void opengl_SetMultitextureBlendMode(bool state);
void opengl_DrawFlatPolygon3D(g3Point** p, int nv);
//Call to ensure that the draw VAO is always ready to go when changing VAOs.
void GL_UseDrawVAO(void);

//gl_framebuffer.cpp
class Framebuffer
{
	GLuint		m_name, m_subname;
	GLuint		m_colorname, m_subcolorname, m_depthname;
	uint32_t	m_width, m_height;
	bool		m_msaa;

	//Used when multisampling is enabled. Blits the multisample framebuffer to the non-multisample sub framebuffer
	//Leaves the sub framebuffer bound for reading to finish the blit. 
	void SubColorBlit();
public:
	Framebuffer();
	void Update(int width, int height, bool msaa);
	void Destroy();
	//Blits to the target framebuffer using glBlitFramebuffer.
	//Will set current read framebuffer to m_name.
	void BlitToRaw(GLuint target, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	//Blits to the target framebuffer using a draw. Bind desired shader before calling. 
	//Will set current read framebuffer to m_name. Will not trash viewport. 
	void BlitTo(GLuint target, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

	GLuint Handle() const
	{
		return m_name;
	}
};

//temporary
void GL_InitFramebufferVAO(void);
void GL_DestroyFramebufferVAO(void);

void GL_UpdateLegacyBlock(float* projection, float* modelview);
