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
#include <string.h>
#include "gl_local.h"

#ifndef GL_UNSIGNED_SHORT_5_5_5_1
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#endif

#ifndef GL_UNSIGNED_SHORT_4_4_4_4
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#endif

uint16_t* OpenGL_bitmap_remap = NULL;
uint16_t* OpenGL_lightmap_remap = NULL;
uint8_t* OpenGL_bitmap_states = NULL;
uint8_t* OpenGL_lightmap_states = NULL;

unsigned int opengl_last_upload_res = 0;
uint* opengl_Upload_data = NULL;
uint* opengl_Translate_table = NULL;
uint* opengl_4444_translate_table = NULL;

uint16_t* opengl_packed_Upload_data = NULL;
uint16_t* opengl_packed_Translate_table = NULL;
uint16_t* opengl_packed_4444_translate_table = NULL;

//Texture list
GLuint texture_name_list[10000];
int Cur_texture_object_num = 1;
int Last_texel_unit_set = -1;

int OpenGL_last_bound[2];
int OpenGL_sets_this_frame[10];
int OpenGL_uploads;

bool OpenGL_cache_initted;

void opengl_InitImages(void)
{
	memset(texture_name_list, 0, sizeof(texture_name_list));
	Cur_texture_object_num = 1;
	Last_texel_unit_set = -1;
}

void opengl_FreeImages(void)
{
	uint* delete_list = (uint*)mem_malloc(Cur_texture_object_num * sizeof(int));
	ASSERT(delete_list);
	for (int i = 1; i < Cur_texture_object_num; i++)
		delete_list[i] = i;

	if (Cur_texture_object_num > 1)
		glDeleteTextures(Cur_texture_object_num, (const uint*)delete_list);

	mem_free(delete_list);
}

int opengl_MakeTextureObject(int tn)
{
	int num = Cur_texture_object_num;

	Cur_texture_object_num++;

	if (texture_name_list[num] == 0)
		glGenTextures(1, &texture_name_list[num]);

	if (UseMultitexture && Last_texel_unit_set != tn)
	{
		glActiveTexture(GL_TEXTURE0 + tn);
		Last_texel_unit_set = tn;
	}

	num = texture_name_list[num];

	glBindTexture(GL_TEXTURE_2D, num);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, NUM_MIP_LEVELS - 1);

	//glTexEnvf (GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	CHECK_ERROR(2)

	return num;
}

extern bool Force_one_texture;

// Utilizes a LRU cacheing scheme to select/upload textures the opengl driver
int opengl_MakeBitmapCurrent(int handle, int map_type, int tn)
{
	int w, h;
	int texnum;

	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		w = GameLightmaps[handle].square_res;
		h = GameLightmaps[handle].square_res;
	}
	else
	{
		if (Force_one_texture)
		{
			handle = 0;
		}

		w = bm_w(handle, 0);
		h = bm_h(handle, 0);
	}

	// See if the bitmaps is already in the cache
	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		if (OpenGL_lightmap_remap[handle] == 65535)
		{
			texnum = opengl_MakeTextureObject(tn);
			SET_WRAP_STATE(OpenGL_lightmap_states[handle], WT_WRAP);
			SET_FILTER_STATE(OpenGL_lightmap_states[handle], 0);
			OpenGL_lightmap_remap[handle] = texnum;
			opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 0, tn);
		}
		else
		{
			texnum = OpenGL_lightmap_remap[handle];
			if (GameLightmaps[handle].flags & LF_CHANGED)
				opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 1, tn);
		}
	}
	else
	{
		if (OpenGL_bitmap_remap[handle] == 65535)
		{
			texnum = opengl_MakeTextureObject(tn);
			SET_WRAP_STATE(OpenGL_bitmap_states[handle], WT_WRAP);
			SET_FILTER_STATE(OpenGL_bitmap_states[handle], 0);
			OpenGL_bitmap_remap[handle] = texnum;
			opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 0, tn);
		}
		else
		{
			texnum = OpenGL_bitmap_remap[handle];
			if (GameBitmaps[handle].flags & BF_CHANGED)
			{
				opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 1, tn);
			}
		}
	}

	if (OpenGL_last_bound[tn] != texnum)
	{
		if (UseMultitexture && Last_texel_unit_set != tn)
		{
			glActiveTexture(GL_TEXTURE0 + tn);
			Last_texel_unit_set = tn;
		}

		glBindTexture(GL_TEXTURE_2D, texnum);
		OpenGL_last_bound[tn] = texnum;
		OpenGL_sets_this_frame[0]++;
	}

	CHECK_ERROR(7)
		return 1;
}

// Sets up an appropriate wrap type for the current bound texture
void opengl_MakeWrapTypeCurrent(int handle, int map_type, int tn)
{
	int uwrap;
	wrap_type dest_wrap;

	if (tn == 1)
		dest_wrap = WT_CLAMP;
	else
		dest_wrap = OpenGL_state.cur_wrap_type;

	if (map_type == MAP_TYPE_LIGHTMAP)
		uwrap = GET_WRAP_STATE(OpenGL_lightmap_states[handle]);
	else
		uwrap = GET_WRAP_STATE(OpenGL_bitmap_states[handle]);

	if (uwrap == dest_wrap)
		return;
	
	if (UseMultitexture && Last_texel_unit_set != tn)
	{
		glActiveTexture(GL_TEXTURE0 + tn);
		Last_texel_unit_set = tn;
	}

	OpenGL_sets_this_frame[1]++;

	if (dest_wrap == WT_CLAMP)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}
	else if (dest_wrap == WT_WRAP_V)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		SET_WRAP_STATE(OpenGL_lightmap_states[handle], dest_wrap);
	}
	else
	{
		SET_WRAP_STATE(OpenGL_bitmap_states[handle], dest_wrap);
	}

	CHECK_ERROR(8)
}

// Chooses the correct filter type for the currently bound texture
void opengl_MakeFilterTypeCurrent(int handle, int map_type, int tn)
{
	int magf, mmip;
	int8_t dest_filter, dest_mip;

	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		magf = GET_FILTER_STATE(OpenGL_lightmap_states[handle]);
		mmip = GET_MIP_STATE(OpenGL_lightmap_states[handle]);
		dest_filter = 1;
		dest_mip = 0;
	}
	else
	{
		magf = GET_FILTER_STATE(OpenGL_bitmap_states[handle]);
		mmip = GET_MIP_STATE(OpenGL_bitmap_states[handle]);
		dest_filter = OpenGL_preferred_state.filtering;
		if (!OpenGL_state.cur_bilinear_state)
			dest_filter = 0;
		dest_mip = OpenGL_preferred_state.mipping;
		if (!OpenGL_state.cur_mip_state || !bm_mipped(handle))
			dest_mip = 0;
	}

	if (magf == dest_filter && mmip == dest_mip)
		return;
	if (UseMultitexture && Last_texel_unit_set != tn)
	{
		glActiveTexture(GL_TEXTURE0 + tn);
		Last_texel_unit_set = tn;
	}

	GLenum mag_filter = dest_filter ? GL_LINEAR : GL_NEAREST;
	GLenum min_filter;
	if (dest_mip)
	{
		min_filter = dest_filter ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
		//This is a bit hacky, this should be set once at texture creation.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, NUM_MIP_LEVELS - 1);
	}
	else
	{
		min_filter = dest_filter ? GL_LINEAR : GL_NEAREST;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

	OpenGL_sets_this_frame[2]++;

	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		SET_FILTER_STATE(OpenGL_lightmap_states[handle], dest_filter);
		SET_MIP_STATE(OpenGL_lightmap_states[handle], dest_mip);
	}
	else
	{
		SET_FILTER_STATE(OpenGL_bitmap_states[handle], dest_filter);
		SET_MIP_STATE(OpenGL_bitmap_states[handle], dest_mip);
	}

	CHECK_ERROR(9)
}

int opengl_InitCache(void)
{
	OpenGL_bitmap_remap = (uint16_t*)mem_malloc(MAX_BITMAPS * 2);
	ASSERT(OpenGL_bitmap_remap);
	OpenGL_lightmap_remap = (uint16_t*)mem_malloc(MAX_LIGHTMAPS * 2);
	ASSERT(OpenGL_lightmap_remap);

	OpenGL_bitmap_states = (uint8_t*)mem_malloc(MAX_BITMAPS);
	ASSERT(OpenGL_bitmap_states);
	OpenGL_lightmap_states = (uint8_t*)mem_malloc(MAX_LIGHTMAPS);
	ASSERT(OpenGL_lightmap_states);

	Cur_texture_object_num = 1;

	// Setup textures and cacheing
	int i;
	for (i = 0; i < MAX_BITMAPS; i++)
	{
		OpenGL_bitmap_remap[i] = 65535;
		OpenGL_bitmap_states[i] = 255;
		GameBitmaps[i].flags |= BF_CHANGED | BF_BRAND_NEW;
	}

	for (i = 0; i < MAX_LIGHTMAPS; i++)
	{
		OpenGL_lightmap_remap[i] = 65535;
		OpenGL_lightmap_states[i] = 255;
		GameLightmaps[i].flags |= LF_CHANGED | LF_BRAND_NEW;
	}

	/*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if (UseMultitexture)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glActiveTexture(GL_TEXTURE0 + 0);
	}*/

	CHECK_ERROR(3);

	OpenGL_cache_initted = true;
	return 1;
}

void opengl_FreeCache(void)
{
	if (OpenGL_cache_initted)
	{
		mem_free(OpenGL_lightmap_remap);
		mem_free(OpenGL_bitmap_remap);
		mem_free(OpenGL_lightmap_states);
		mem_free(OpenGL_bitmap_states);
		OpenGL_cache_initted = false;
	}
}

// Resets the texture cache
void opengl_ResetCache(void)
{
	if (OpenGL_cache_initted)
	{
		mem_free(OpenGL_lightmap_remap);
		mem_free(OpenGL_bitmap_remap);
		mem_free(OpenGL_lightmap_states);
		mem_free(OpenGL_bitmap_states);
		OpenGL_cache_initted = false;
	}

	opengl_InitCache();
}

void opengl_FreeUploadBuffers(void)
{
	if (OpenGL_packed_pixels)
	{
		if (opengl_packed_Upload_data)
		{
			mem_free(opengl_packed_Upload_data);
		}
		if (opengl_packed_Translate_table)
		{
			mem_free(opengl_packed_Translate_table);
		}
		if (opengl_packed_4444_translate_table)
		{
			mem_free(opengl_packed_4444_translate_table);
		}
		opengl_packed_Upload_data = NULL;
		opengl_packed_Translate_table = NULL;
		opengl_packed_4444_translate_table = NULL;
	}
	else
	{
		if (opengl_Upload_data)
			mem_free(opengl_Upload_data);
		if (opengl_Translate_table)
			mem_free(opengl_Translate_table);
		if (opengl_4444_translate_table)
			mem_free(opengl_4444_translate_table);
		opengl_Upload_data = NULL;
		opengl_Translate_table = NULL;
		opengl_4444_translate_table = NULL;
	}
	opengl_last_upload_res = 0;
}

void opengl_SetUploadBufferSize(int width, int height)
{
	if ((width * height) <= opengl_last_upload_res)
		return;

	opengl_FreeUploadBuffers();

	if (OpenGL_packed_pixels)
	{
		opengl_packed_Upload_data = (uint16_t*)mem_malloc(width * height * 2);
		opengl_packed_Translate_table = (uint16_t*)mem_malloc(65536 * 2);
		opengl_packed_4444_translate_table = (uint16_t*)mem_malloc(65536 * 2);

		ASSERT(opengl_packed_Upload_data);
		ASSERT(opengl_packed_Translate_table);
		ASSERT(opengl_packed_4444_translate_table);

		mprintf((0, "Building packed OpenGL translate table...\n"));

		for (int i = 0; i < 65536; i++)
		{
			int r = (i >> 10) & 0x1f;
			int g = (i >> 5) & 0x1f;
			int b = i & 0x1f;

#ifdef BRIGHTNESS_HACK
			r *= BRIGHTNESS_HACK;
			g *= BRIGHTNESS_HACK;
			b *= BRIGHTNESS_HACK;
			if (r > 0x1F) r = 0x1F;
			if (g > 0x1F) g = 0x1F;
			if (b > 0x1F) b = 0x1F;
#endif

			uint16_t pix;

			if (!(i & OPAQUE_FLAG))
			{
				pix = 0;
			}
			else
			{
				pix = (r << 11) | (g << 6) | (b << 1) | 1;
			}

			opengl_packed_Translate_table[i] = pix;

			// 4444 table
			int a = (i >> 12) & 0xf;
			r = (i >> 8) & 0xf;
			g = (i >> 4) & 0xf;
			b = i & 0xf;

			pix = (r << 12) | (g << 8) | (b << 4) | a;
			opengl_packed_4444_translate_table[i] = pix;
		}
	}
	else
	{
		opengl_Upload_data = (uint*)mem_malloc(width * height * 4);
		opengl_Translate_table = (uint*)mem_malloc(65536 * 4);
		opengl_4444_translate_table = (uint*)mem_malloc(65536 * 4);

		ASSERT(opengl_Upload_data);
		ASSERT(opengl_Translate_table);
		ASSERT(opengl_4444_translate_table);

		mprintf((0, "Building OpenGL translate table...\n"));

		for (int i = 0; i < 65536; i++)
		{
			uint pix;
			int r = (i >> 10) & 0x1f;
			int g = (i >> 5) & 0x1f;
			int b = i & 0x1f;

#ifdef BRIGHTNESS_HACK
			r *= BRIGHTNESS_HACK;
			g *= BRIGHTNESS_HACK;
			b *= BRIGHTNESS_HACK;
			if (r > 0x1F) r = 0x1F;
			if (g > 0x1F) g = 0x1F;
			if (b > 0x1F) b = 0x1F;
#endif

			float fr = (float)r / 31.0f;
			float fg = (float)g / 31.0f;
			float fb = (float)b / 31.0f;

			r = 255 * fr;
			g = 255 * fg;
			b = 255 * fb;

			if (!(i & OPAQUE_FLAG))
			{
				pix = 0;
			}
			else
			{
				pix = (255 << 24) | (b << 16) | (g << 8) | (r);
			}

			opengl_Translate_table[i] = pix;

			// Do 4444
			int a = (i >> 12) & 0xf;
			r = (i >> 8) & 0xf;
			g = (i >> 4) & 0xf;
			b = i & 0xf;

			float fa = (float)a / 15.0f;
			fr = (float)r / 15.0f;
			fg = (float)g / 15.0f;
			fb = (float)b / 15.0f;

			a = 255 * fa;
			r = 255 * fr;
			g = 255 * fg;
			b = 255 * fb;

			pix = (a << 24) | (b << 16) | (g << 8) | (r);

			opengl_4444_translate_table[i] = pix;
		}
	}

	opengl_last_upload_res = width * height;
}

// Takes our 16bit format and converts it into the memory scheme that OpenGL wants
void opengl_TranslateBitmapToOpenGL(int texnum, int bm_handle, int map_type, int replace, int tn)
{
	uint16_t* bm_ptr;

	int w, h;
	int size;

	if (UseMultitexture && Last_texel_unit_set != tn)
	{
		glActiveTexture(GL_TEXTURE0 + tn);
		Last_texel_unit_set = tn;
	}

	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		if (GameLightmaps[bm_handle].flags & LF_BRAND_NEW)
			replace = 0;

		bm_ptr = lm_data(bm_handle);
		GameLightmaps[bm_handle].flags &= ~(LF_CHANGED | LF_BRAND_NEW);

		w = lm_w(bm_handle);
		h = lm_h(bm_handle);
		size = GameLightmaps[bm_handle].square_res;
	}
	else
	{
		if (GameBitmaps[bm_handle].flags & BF_BRAND_NEW)
			replace = 0;

		bm_ptr = bm_data(bm_handle, 0);
		GameBitmaps[bm_handle].flags &= ~(BF_CHANGED | BF_BRAND_NEW);
		w = bm_w(bm_handle, 0);
		h = bm_h(bm_handle, 0);
		size = w;
	}

	if (OpenGL_last_bound[tn] != texnum)
	{
		glBindTexture(GL_TEXTURE_2D, texnum);
		OpenGL_sets_this_frame[0]++;
		OpenGL_last_bound[tn] = texnum;
	}

	opengl_SetUploadBufferSize(w, h);

	int i;

	if (OpenGL_packed_pixels)
	{
		if (map_type == MAP_TYPE_LIGHTMAP)
		{
			uint16_t* left_data = (uint16_t*)opengl_packed_Upload_data;
			int bm_left = 0;

			for (int i = 0; i < h; i++, left_data += size, bm_left += w)
			{
				uint16_t* dest_data = left_data;
				for (int t = 0; t < w; t++)
				{
					*dest_data++ = opengl_packed_Translate_table[bm_ptr[bm_left + t]];
				}
			}

			if (replace)
			{
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, size, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, opengl_packed_Upload_data);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5_A1, size, size, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, opengl_packed_Upload_data);
			}
		}
		else
		{
			int limit = 0;

			if (bm_mipped(bm_handle))
			{
				limit = NUM_MIP_LEVELS;
			}
			else
			{
				limit = 1;
			}

			for (int m = 0; m < limit; m++)
			{
				if (m < NUM_MIP_LEVELS)
				{
					bm_ptr = bm_data(bm_handle, m);
					w = bm_w(bm_handle, m);
					h = bm_h(bm_handle, m);
				}
				else
				{
					bm_ptr = bm_data(bm_handle, NUM_MIP_LEVELS - 1);
					w = bm_w(bm_handle, NUM_MIP_LEVELS - 1);
					h = bm_h(bm_handle, NUM_MIP_LEVELS - 1);

					w >>= m - (NUM_MIP_LEVELS - 1);
					h >>= m - (NUM_MIP_LEVELS - 1);

					if ((w < 1) || (h < 1))
						continue;

				}

				if (bm_format(bm_handle) == BITMAP_FORMAT_4444)
				{
					// Do 4444
					for (i = 0; i < w * h; i++)
						opengl_packed_Upload_data[i] = opengl_packed_4444_translate_table[bm_ptr[i]];

					if (replace)
					{
						glTexSubImage2D(GL_TEXTURE_2D, m, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, opengl_packed_Upload_data);
					}
					else
					{
						glTexImage2D(GL_TEXTURE_2D, m, GL_RGBA4, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, opengl_packed_Upload_data);
					}
				}
				else
				{
					// Do 1555
					for (i = 0; i < w * h; i++)
					{
						opengl_packed_Upload_data[i] = opengl_packed_Translate_table[bm_ptr[i]];
					}

					if (replace)
					{
						glTexSubImage2D(GL_TEXTURE_2D, m, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, opengl_packed_Upload_data);
					}
					else
					{
						glTexImage2D(GL_TEXTURE_2D, m, GL_RGB5_A1, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, opengl_packed_Upload_data);
					}
				}
			}
		}
	}
	else
	{
		if (map_type == MAP_TYPE_LIGHTMAP)
		{
			uint* left_data = (uint*)opengl_Upload_data;
			int bm_left = 0;

			for (int i = 0; i < h; i++, left_data += size, bm_left += w)
			{
				uint* dest_data = left_data;
				for (int t = 0; t < w; t++)
				{
					*dest_data++ = opengl_Translate_table[bm_ptr[bm_left + t]];
				}
			}
			if (size > 0)
			{
				if (replace)
				{
					glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, size, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
				}
			}
		}
		else
		{
			int limit = 0;

			if (bm_mipped(bm_handle))
			{
				limit = NUM_MIP_LEVELS;
			}
			else
			{
				limit = 1;
			}

			for (int m = 0; m < limit; m++)
			{
				bm_ptr = bm_data(bm_handle, m);
				w = bm_w(bm_handle, m);
				h = bm_h(bm_handle, m);

				if (bm_format(bm_handle) == BITMAP_FORMAT_4444)
				{
					// Do 4444
					for (i = 0; i < w * h; i++)
						opengl_Upload_data[i] = opengl_4444_translate_table[bm_ptr[i]];
				}
				else
				{
					// Do 1555

					for (i = 0; i < w * h; i++)
						opengl_Upload_data[i] = opengl_Translate_table[bm_ptr[i]];
				}

				//rcg06262000 my if wrapper.
				if ((w > 0) && (h > 0))
				{
					if (replace)
					{
						glTexSubImage2D(GL_TEXTURE_2D, m, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
					}
					else
					{
						glTexImage2D(GL_TEXTURE_2D, m, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
					}
				}
			}
		}
	}

	//mprintf ((1,"Doing slow upload to opengl!\n"));

	if (map_type == MAP_TYPE_LIGHTMAP)
	{
		GameLightmaps[bm_handle].flags &= ~LF_LIMITS;
	}

	CHECK_ERROR(6)
		OpenGL_uploads++;
}

uint8_t opengl_Framebuffer_ready = 0;
chunked_bitmap opengl_Chunked_bitmap;

void opengl_ChangeChunkedBitmap(int bm_handle, chunked_bitmap* chunk)
{
	int bw = bm_w(bm_handle, 0);
	int bh = bm_h(bm_handle, 0);

	//determine optimal size of the square bitmaps
	float fopt = 128.0f;
	int iopt;

	//find the smallest dimension and base off that
	int smallest = std::min(bw, bh);

	if (smallest <= 32)
		fopt = 32;
	else
		if (smallest <= 64)
			fopt = 64;
		else
			fopt = 128;

	iopt = (int)fopt;

	// Get how many pieces we need across and down
	float temp = bw / fopt;
	int how_many_across = temp;
	if ((temp - how_many_across) > 0)
		how_many_across++;

	temp = bh / fopt;
	int how_many_down = temp;
	if ((temp - how_many_down) > 0)
		how_many_down++;

	ASSERT(how_many_across > 0);
	ASSERT(how_many_down > 0);

	// Now go through our big bitmap and partition it into pieces
	uint16_t* src_data = bm_data(bm_handle, 0);
	uint16_t* sdata;
	uint16_t* ddata;

	int shift;
	switch (iopt)
	{
	case 32:
		shift = 5;
		break;
	case 64:
		shift = 6;
		break;
	case 128:
		shift = 7;
		break;
	default:
		Int3(); //Get Jeff
		break;
	}
	int maxx, maxy;
	int windex, hindex;
	int s_y, s_x, d_y, d_x;

	for (hindex = 0; hindex < how_many_down; hindex++) 
	{
		for (windex = 0; windex < how_many_across; windex++) 
		{
			//loop through the chunks
			//find end x and y
			if (windex < how_many_across - 1)
				maxx = iopt;
			else
				maxx = bw - (windex << shift);
			if (hindex < how_many_down - 1)
				maxy = iopt;
			else
				maxy = bh - (hindex << shift);

			//find the starting source x and y
			s_x = (windex << shift);
			s_y = (hindex << shift);

			//get the pointers pointing to the right spot
			ddata = bm_data(chunk->bm_array[hindex * how_many_across + windex], 0);
			GameBitmaps[chunk->bm_array[hindex * how_many_across + windex]].flags |= BF_CHANGED;
			sdata = &src_data[s_y * bw + s_x];

			//copy the data
			for (d_y = 0; d_y < maxy; d_y++) 
			{
				for (d_x = 0; d_x < maxx; d_x++) 
				{
					ddata[d_x] = sdata[d_x];
				}//end for d_x
				sdata += bw;
				ddata += iopt;
			}//end for d_y

		}//end for windex
	}//end for hindex
}

// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y
void rend_CopyBitmapToFramebuffer(int bm_handle, int x, int y)
{
	ASSERT(opengl_Framebuffer_ready);

	if (opengl_Framebuffer_ready == 1)
	{
		bm_CreateChunkedBitmap(bm_handle, &opengl_Chunked_bitmap);
		opengl_Framebuffer_ready = 2;
	}
	else
	{
		opengl_ChangeChunkedBitmap(bm_handle, &opengl_Chunked_bitmap);
	}

	rend_DrawChunkedBitmap(&opengl_Chunked_bitmap, 0, 0, 255);
}

// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void rend_SetFrameBufferCopyState(bool state)
{
	if (state)
	{
		ASSERT(opengl_Framebuffer_ready == 0);
		opengl_Framebuffer_ready = 1;
	}
	else
	{
		ASSERT(opengl_Framebuffer_ready != 0);
		opengl_Framebuffer_ready = 0;

		if (opengl_Framebuffer_ready == 2)
		{
			bm_DestroyChunkedBitmap(&opengl_Chunked_bitmap);
			opengl_ResetCache();
		}
	}
}
