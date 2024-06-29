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

//The number of vertex attributes the legacy code used. 
constexpr int NUM_LEGACY_VERTEX_ATTRIBS = 4;
//The count of vertices that each buffer will store
constexpr int NUM_VERTS_PER_BUFFER = 32000;

struct color_array
{
	float r, g, b, a;
};

struct tex_array
{
	float s, t, r, w;
};

struct gl_vertex
{
	vector vert;
	color_array color;
	tex_array tex_coord;
	tex_array tex_coord2;
};

gl_vertex GL_vertices[100];

float OpenGL_Alpha_factor = 1.0f;
float Alpha_multiplier = 1.0f;

int OpenGL_polys_drawn;
int OpenGL_verts_processed;

int Overlay_map = -1;
int Bump_map = 0;
int Bumpmap_ready = 0;
uint8_t Overlay_type = OT_NONE;
float Z_bias = 0.0f;

bool OpenGL_blending_on = true;

static GLuint drawbuffer;
//The next committed vertex is where to start writing vertex data to the buffer
static GLuint nextcommittedvertex; 
static ShaderProgram drawshaders[4];
static int lastdrawshader = -1;

static GLuint drawvao;

void GL_UseDrawVAO(void)
{
	glBindVertexArray(drawvao);
}

int GL_CopyVertices(int numvertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, drawbuffer);
	if (nextcommittedvertex + numvertices > NUM_VERTS_PER_BUFFER)
		nextcommittedvertex = 0;

	int startoffset = nextcommittedvertex;

	glBufferSubData(GL_ARRAY_BUFFER, startoffset * sizeof(gl_vertex), numvertices * sizeof(gl_vertex), GL_vertices);

	nextcommittedvertex += numvertices;

	return startoffset;
}

void opengl_SetDrawDefaults(void)
{
	//Init shaders
	extern const char* genericVertexBody;
	extern const char* genericFragBody;
	//No texturing
	drawshaders[0].AttachSourcePreprocess(genericVertexBody, genericFragBody, false, false, false);
	//Textured
	drawshaders[1].AttachSourcePreprocess(genericVertexBody, genericFragBody, true, false, false);
	//Textured and lightmapped
	drawshaders[2].AttachSourcePreprocess(genericVertexBody, genericFragBody, true, true, false);
	//Specular. 
	drawshaders[3].AttachSourcePreprocess(genericVertexBody, genericFragBody, true, false, true);

	lastdrawshader = -1;

	//Init draw buffers
	glGenBuffers(1, &drawbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawbuffer);
	size_t buffersize = NUM_VERTS_PER_BUFFER * sizeof(gl_vertex);
	glBufferData(GL_ARRAY_BUFFER, buffersize, nullptr, GL_DYNAMIC_DRAW);

	//Init VAO and vertex state
	glGenVertexArrays(1, &drawvao);
	glBindVertexArray(drawvao);

	size_t offset = 0;

	//attrib 0: position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), 0);

	//attrib 1: color
	//glBufferData(GL_ARRAY_BUFFER, NUM_VERTS_PER_BUFFER * sizeof(color_array), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), (const void*)offsetof(gl_vertex, color));

	//attrib 2: uv
	//glBufferData(GL_ARRAY_BUFFER, NUM_VERTS_PER_BUFFER * sizeof(tex_array), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), (const void*)offsetof(gl_vertex, tex_coord));
	offset += sizeof(tex_array) * NUM_VERTS_PER_BUFFER;

	//attrib 3: uv 2
	//glBufferData(GL_ARRAY_BUFFER, NUM_VERTS_PER_BUFFER * sizeof(tex_array), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), (const void*)offsetof(gl_vertex, tex_coord2));
	offset += sizeof(tex_array) * NUM_VERTS_PER_BUFFER;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_SelectDrawShader()
{
	//TODO: This will bind excessively because I don't know if the previous shader was overridden by something.
	//This should probably be cleaned up
	if (OpenGL_state.cur_alpha_type == AT_SPECULAR)
		drawshaders[3].Use();
	else if (OpenGL_state.cur_texture_quality == 0)
		drawshaders[0].Use();
	else if (OpenGL_state.cur_texture_quality != 0)
	{
		if (Overlay_type != OT_NONE)
			drawshaders[2].Use();
		else
			drawshaders[1].Use();
	}
}

// Takes nv vertices and draws the 3D polygon defined by those vertices.
// Uses bitmap "handle" as a texture
void rend_DrawPolygon3D(int handle, g3Point** p, int nv, int map_type)
{
	g3Point* pnt;
	int i;
	float fr, fg, fb;

	ASSERT(nv < 100);

	/*if (OpenGL_state.cur_texture_quality == 0)
	{
		opengl_DrawFlatPolygon3D(p, nv);
		return;
	}

	if (Overlay_type != OT_NONE && UseMultitexture)
	{
		opengl_DrawMultitexturePolygon3D(handle, p, nv, map_type);
		return;
	}*/

	float one_over_square_res = 1;
	float xscalar = 1;
	float yscalar = 1;

	GL_SelectDrawShader();

	if (OpenGL_state.cur_light_state == LS_FLAT_GOURAUD || OpenGL_state.cur_texture_type == 0)
	{
		fr = GR_COLOR_RED(OpenGL_state.cur_color) / 255.0;
		fg = GR_COLOR_GREEN(OpenGL_state.cur_color) / 255.0;
		fb = GR_COLOR_BLUE(OpenGL_state.cur_color) / 255.0;
	}

	if (UseMultitexture)
	{
		opengl_SetMultitextureBlendMode(false);
	}

	if (OpenGL_state.cur_texture_quality != 0)
	{
		// make sure our bitmap is ready to be drawn
		opengl_MakeBitmapCurrent(handle, map_type, 0);
		opengl_MakeWrapTypeCurrent(handle, map_type, 0);
		opengl_MakeFilterTypeCurrent(handle, map_type, 0);

		if (Overlay_type != OT_NONE)
		{
			one_over_square_res = 1.0 / GameLightmaps[Overlay_map].square_res;
			xscalar = (float)GameLightmaps[Overlay_map].width * one_over_square_res;
			yscalar = (float)GameLightmaps[Overlay_map].height * one_over_square_res;
			// make sure our bitmap is ready to be drawn
			opengl_MakeBitmapCurrent(Overlay_map, MAP_TYPE_LIGHTMAP, 1);
			opengl_MakeWrapTypeCurrent(Overlay_map, MAP_TYPE_LIGHTMAP, 1);
			opengl_MakeFilterTypeCurrent(Overlay_map, MAP_TYPE_LIGHTMAP, 1);
		}
	}

	float alpha = Alpha_multiplier * OpenGL_Alpha_factor;

	gl_vertex* vertp = GL_vertices;

	// Specify our coordinates
	for (i = 0; i < nv; i++, vertp++)
	{
		pnt = p[i];

		if (OpenGL_state.cur_alpha_type & ATF_VERTEX)
		{
			alpha = pnt->p3_a * Alpha_multiplier * OpenGL_Alpha_factor;
		}

		// If we have a lighting model, apply the correct lighting!
		if (OpenGL_state.cur_light_state != LS_NONE)
		{
			if (OpenGL_state.cur_light_state == LS_FLAT_GOURAUD)
			{
				vertp->color.r = fr;
				vertp->color.g = fg;
				vertp->color.b = fb;
				vertp->color.a = alpha;
			}
			else
			{
				// Do lighting based on intesity (MONO) or colored (RGB)
				if (OpenGL_state.cur_color_model == CM_MONO)
				{
					vertp->color.r = pnt->p3_l;
					vertp->color.g = pnt->p3_l;
					vertp->color.b = pnt->p3_l;
					vertp->color.a = alpha;
				}
				else
				{
					vertp->color.r = pnt->p3_r;
					vertp->color.g = pnt->p3_g;
					vertp->color.b = pnt->p3_b;
					vertp->color.a = alpha;
				}
			}
		}
		else
		{
			if (OpenGL_state.cur_texture_type != 0)
			{
				vertp->color.r = 1;
				vertp->color.g = 1;
				vertp->color.b = 1;
				vertp->color.a = alpha;
			}
			else
			{
				vertp->color.r = fr;
				vertp->color.g = fg;
				vertp->color.b = fb;
				vertp->color.a = alpha;
			}
		}

		if (OpenGL_state.cur_texture_type != 0)
		{
			// Texture this polygon!
			float texw = 1.0 / (pnt->p3_z + Z_bias);
			vertp->tex_coord.s = pnt->p3_u * texw;
			vertp->tex_coord.t = pnt->p3_v * texw;
			vertp->tex_coord.r = 0;
			vertp->tex_coord.w = texw;

			if (Overlay_type != OT_NONE)
			{
				vertp->tex_coord2.s = pnt->p3_u2 * xscalar * texw;
				vertp->tex_coord2.t = pnt->p3_v2 * yscalar * texw;
				vertp->tex_coord2.r = 0;
				vertp->tex_coord2.w = texw;
			}
		}

		// Finally, specify a vertex
		vertp->vert.x = pnt->p3_sx;
		vertp->vert.y = pnt->p3_sy;

		float z = std::max(0.f, std::min(1.0f, 1.0f - (1.0f / (pnt->p3_z + Z_bias))));
		vertp->vert.z = -z;
	}

	// And draw!
	int offset = GL_CopyVertices(nv);
	glDrawArrays(GL_TRIANGLE_FAN, offset, nv);
	OpenGL_polys_drawn++;
	OpenGL_verts_processed += nv;

	CHECK_ERROR(10)
}

// Takes nv vertices and draws the 2D polygon defined by those vertices.
// Uses bitmap "handle" as a texture
void rend_DrawPolygon2D(int handle, g3Point** p, int nv)
{
	ASSERT(nv < 100);
	ASSERT(Overlay_type == OT_NONE);

	rend_DrawPolygon3D(handle, p, nv, MAP_TYPE_BITMAP);
}

// draws a scaled 2d bitmap to our buffer
void rend_DrawScaledBitmap(int x1, int y1, int x2, int y2,
	int bm, float u0, float v0, float u1, float v1, int color, float* alphas)
{
	g3Point* ptr_pnts[4];
	g3Point pnts[4];
	float r, g, b;
	if (color != -1)
	{
		r = GR_COLOR_RED(color) / 255.0;
		g = GR_COLOR_GREEN(color) / 255.0;
		b = GR_COLOR_BLUE(color) / 255.0;
	}
	for (int i = 0; i < 4; i++)
	{
		if (color == -1)
			pnts[i].p3_l = 1.0;
		else
		{
			pnts[i].p3_r = r;
			pnts[i].p3_g = g;
			pnts[i].p3_b = b;
		}
		if (alphas)
		{
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
	rend_DrawPolygon2D(bm, ptr_pnts, 4);
}

void rend_DrawScaledBitmapWithZ(int x1, int y1, int x2, int y2,
	int bm, float u0, float v0, float u1, float v1, float zval, int color, float* alphas)
{
	g3Point* ptr_pnts[4];
	g3Point pnts[4];
	float r, g, b;

	if (color != -1)
	{
		r = GR_COLOR_RED(color) / 255.0;
		g = GR_COLOR_GREEN(color) / 255.0;
		b = GR_COLOR_BLUE(color) / 255.0;
	}

	for (int i = 0; i < 4; i++)
	{
		if (color == -1)
			pnts[i].p3_l = 1.0;
		else
		{
			pnts[i].p3_r = r;
			pnts[i].p3_g = g;
			pnts[i].p3_b = b;
		}

		if (alphas)
		{
			pnts[i].p3_a = alphas[i];
		}

		pnts[i].p3_z = zval;
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
	rend_DrawPolygon3D(bm, ptr_pnts, 4);
}

// Fills a rectangle on the display
void rend_FillRect(ddgr_color color, int x1, int y1, int x2, int y2)
{
	int r = GR_COLOR_RED(color);
	int g = GR_COLOR_GREEN(color);
	int b = GR_COLOR_BLUE(color);

	int width = x2 - x1;
	int height = y2 - y1;

	x1 += OpenGL_state.clip_x1;
	y1 += OpenGL_state.clip_y1;

	glEnable(GL_SCISSOR_TEST);
	glScissor(x1, OpenGL_state.screen_height - (height + y1), width, height);
	glClearColor((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	width = OpenGL_state.clip_x2 - OpenGL_state.clip_x1;
	height = OpenGL_state.clip_y2 - OpenGL_state.clip_y1;

	glScissor(OpenGL_state.clip_x1, OpenGL_state.screen_height - (OpenGL_state.clip_y1 + height), width, height);
	glDisable(GL_SCISSOR_TEST);
}

// Sets a pixel on the display
void rend_SetPixel(ddgr_color color, int x, int y)
{
	float r = (color >> 16 & 0xFF) / 255.f;
	float g = (color >> 8 & 0xFF) / 255.f;
	float b = (color & 0xFF) / 255.f;

	GL_SelectDrawShader();

	GL_vertices[0].color.r = r;
	GL_vertices[0].color.g = g;
	GL_vertices[0].color.b = b;
	GL_vertices[0].color.a = 1.0f;

	GL_vertices[0].vert.x = x;
	GL_vertices[0].vert.y = y;
	GL_vertices[0].vert.z = 0;

	//please do not call this function if you can avoid it.
	int offset = GL_CopyVertices(1);
	glDrawArrays(GL_POINTS, offset, 1);

	/*glColor3ub(r, g, b);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();*/
}

// Sets a pixel on the display
ddgr_color rend_GetPixel(int x, int y)
{
	ddgr_color color[4];
	glReadPixels(x, (OpenGL_state.screen_height - 1) - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)color);
	return color[0];
}

void rend_FillCircle(ddgr_color col, int x, int y, int rad)
{
}

void rend_DrawCircle(int x, int y, int rad)
{
}

// Sets up a font character to draw.  We draw our fonts as pieces of textures
void rend_DrawFontCharacter(int bm_handle, int x1, int y1, int x2, int y2, float u, float v, float w, float h)
{
	g3Point* ptr_pnts[4];
	g3Point pnts[4];
	for (int i = 0; i < 4; i++)
	{
		pnts[i].p3_z = 1;	// Make REALLY close!
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
	rend_DrawPolygon2D(bm_handle, ptr_pnts, 4);
}

// Draws a line
void rend_DrawLine(int x1, int y1, int x2, int y2)
{
	int8_t atype;
	light_state ltype;
	texture_type ttype;
	int color = OpenGL_state.cur_color;

	float r = GR_COLOR_RED(color) / 255.f;
	float g = GR_COLOR_GREEN(color) / 255.f;
	float b = GR_COLOR_BLUE(color) / 255.f;

	atype = OpenGL_state.cur_alpha_type;
	ltype = OpenGL_state.cur_light_state;
	ttype = OpenGL_state.cur_texture_type;

	rend_SetAlphaType(AT_ALWAYS);
	rend_SetLighting(LS_NONE);
	rend_SetTextureType(TT_FLAT);

	GL_SelectDrawShader();

	GL_vertices[0].color.r = r;
	GL_vertices[0].color.g = g;
	GL_vertices[0].color.b = b;
	GL_vertices[0].color.a = 1.0f;
	GL_vertices[1].color = GL_vertices[0].color;

	//hack to avoid line clipping but this isn't working correctly yet, causes one corner to vanish. 
	GL_vertices[0].vert.x = x1 + 1.f;
	GL_vertices[0].vert.y = y1 + 1.f;
	GL_vertices[0].vert.z = 0;
	GL_vertices[1].vert.x = x2 + 1.f;
	GL_vertices[1].vert.y = y2 + 1.f;
	GL_vertices[1].vert.z = 0;

	int offset = GL_CopyVertices(2);
	glDrawArrays(GL_LINES, offset, 2);

	rend_SetAlphaType(atype);
	rend_SetLighting(ltype);
	rend_SetTextureType(ttype);
}

// The font characteristics
static float rend_FontRed[4], rend_FontBlue[4], rend_FontGreen[4], rend_FontAlpha[4];

// Sets the argb characteristics of the font characters.  color1 is the upper left and proceeds clockwise
void rend_SetCharacterParameters(ddgr_color color1, ddgr_color color2, ddgr_color color3, ddgr_color color4)
{
	rend_FontRed[0] = (float)(GR_COLOR_RED(color1) / 255.0f);
	rend_FontRed[1] = (float)(GR_COLOR_RED(color2) / 255.0f);
	rend_FontRed[2] = (float)(GR_COLOR_RED(color3) / 255.0f);
	rend_FontRed[3] = (float)(GR_COLOR_RED(color4) / 255.0f);
	rend_FontGreen[0] = (float)(GR_COLOR_GREEN(color1) / 255.0f);
	rend_FontGreen[1] = (float)(GR_COLOR_GREEN(color2) / 255.0f);
	rend_FontGreen[2] = (float)(GR_COLOR_GREEN(color3) / 255.0f);
	rend_FontGreen[3] = (float)(GR_COLOR_GREEN(color4) / 255.0f);
	rend_FontBlue[0] = (float)(GR_COLOR_BLUE(color1) / 255.0f);
	rend_FontBlue[1] = (float)(GR_COLOR_BLUE(color2) / 255.0f);
	rend_FontBlue[2] = (float)(GR_COLOR_BLUE(color3) / 255.0f);
	rend_FontBlue[3] = (float)(GR_COLOR_BLUE(color4) / 255.0f);
	rend_FontAlpha[0] = (color1 >> 24) / 255.0f;
	rend_FontAlpha[1] = (color2 >> 24) / 255.0f;
	rend_FontAlpha[2] = (color3 >> 24) / 255.0f;
	rend_FontAlpha[3] = (color4 >> 24) / 255.0f;
}

// Turns on/off multitexture blending
void opengl_SetMultitextureBlendMode(bool state)
{
	if (OpenGL_multitexture_state == state)
		return;
	OpenGL_multitexture_state = state;
	if (state)
	{
		Last_texel_unit_set = 0;
	}
	else
	{
		Last_texel_unit_set = 0;
	}
}

// Takes nv vertices and draws the polygon defined by those vertices.  Uses bitmap "handle"
// as a texture
void opengl_DrawMultitexturePolygon3D(int handle, g3Point** p, int nv, int map_type)
{
	Int3();
}

void opengl_DrawFlatPolygon3D(g3Point** p, int nv)
{
	Int3();
}

// Draws a line using the states of the renderer
void rend_DrawSpecialLine(g3Point* p0, g3Point* p1)
{
	float fr, fg, fb, alpha;
	int i;

	fr = GR_COLOR_RED(OpenGL_state.cur_color);
	fg = GR_COLOR_GREEN(OpenGL_state.cur_color);
	fb = GR_COLOR_BLUE(OpenGL_state.cur_color);

	fr /= 255.0f;
	fg /= 255.0f;
	fb /= 255.0f;

	alpha = Alpha_multiplier * OpenGL_Alpha_factor;

	gl_vertex* vertp = GL_vertices;

	// And draw!
	for (i = 0; i < 2; i++, vertp++)
	{
		color_array* colorp = &vertp->color;

		g3Point* pnt = p0;

		if (i == 1)
			pnt = p1;

		if (OpenGL_state.cur_alpha_type & ATF_VERTEX)
			alpha = pnt->p3_a * Alpha_multiplier * OpenGL_Alpha_factor;

		// If we have a lighting model, apply the correct lighting!
		if (OpenGL_state.cur_light_state != LS_NONE)
		{
			if (OpenGL_state.cur_light_state == LS_FLAT_GOURAUD)
			{
				colorp->r = fr; colorp->g = fg, colorp->b = fb; colorp->a = alpha;
			}
			else
			{
				// Do lighting based on intesity (MONO) or colored (RGB)
				if (OpenGL_state.cur_color_model == CM_MONO)
				{
					colorp->r = pnt->p3_uvl.l; colorp->g = pnt->p3_uvl.l; colorp->b = pnt->p3_uvl.l; colorp->a = alpha;
				}
				else
				{
					colorp->r = pnt->p3_uvl.r; colorp->g = pnt->p3_uvl.g; colorp->b = pnt->p3_uvl.r; colorp->a = alpha;
				}
			}
		}
		else
		{
			colorp->r = fr; colorp->g = fg, colorp->b = fb; colorp->a = alpha;
		}

		// Finally, specify a vertex
		float z = std::max(0., std::min(1.0, 1.0 - (1.0 / (pnt->p3_z + Z_bias))));

		vertp->vert.x = pnt->p3_sx; vertp->vert.y = pnt->p3_sy; vertp->vert.z = -z;
		//glVertex3f(pnt->p3_sx + x_add, pnt->p3_sy + y_add, -z);
	}

	GL_SelectDrawShader();
	int offset = GL_CopyVertices(2);
	glDrawArrays(GL_LINES, offset, 2);
}

// Gets a pointer to a linear frame buffer
void rend_GetLFBLock(renderer_lfb* lfb)
{
}

// Releases an lfb lock
void rend_ReleaseLFBLock(renderer_lfb* lfb)
{
}

// Given a source x,y and width,height, draws any sized bitmap into the renderer lfb
void rend_DrawLFBBitmap(int sx, int sy, int w, int h, int dx, int dy, uint16_t* data, int rowsize)
{
}

//	given a chunked bitmap, renders it.
void rend_DrawChunkedBitmap(chunked_bitmap* chunk, int x, int y, uint8_t alpha)
{
	int* bm_array = chunk->bm_array;
	int w = chunk->w;
	int h = chunk->h;
	int piece_w = bm_w(bm_array[0], 0);
	int piece_h = bm_h(bm_array[0], 0);
	int screen_w, screen_h;
	int i, t;
	rend_SetZBufferState(0);
	rend_GetProjectionParameters(&screen_w, &screen_h);
	for (i = 0; i < h; i++)
	{
		for (t = 0; t < w; t++)
		{
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
void rend_DrawScaledChunkedBitmap(chunked_bitmap* chunk, int x, int y, int neww, int newh, uint8_t alpha)
{
	int* bm_array = chunk->bm_array;
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
	for (i = 0; i < h; i++)
	{
		for (t = 0; t < w; t++)
		{
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

// Draws a simple bitmap at the specified x,y location
void rend_DrawSimpleBitmap(int bm_handle, int x, int y)
{
	rend_SetAlphaType(AT_CONSTANT_TEXTURE);
	rend_SetAlphaValue(255);
	rend_SetLighting(LS_NONE);
	rend_SetColorModel(CM_MONO);
	rend_SetOverlayType(OT_NONE);
	rend_SetFiltering(0);
	rend_DrawScaledBitmap(x, y, x + bm_w(bm_handle, 0), y + bm_h(bm_handle, 0), bm_handle, 0, 0, 1, 1);
	rend_SetFiltering(1);
}
