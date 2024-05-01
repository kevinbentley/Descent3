/*
 * Copyright (C) 2002-2024 D2X Project
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

#ifndef _LIBMVE_H
#define _LIBMVE_H

#define MVE_ERR_EOF 1

typedef struct {
  int screenWidth;
  int screenHeight;
  int width;
  int height;
  int truecolor;
} MVE_videoSpec;

int MVE_rmPrepMovie(void *stream, int x, int y, int track);
int MVE_rmStepMovie(void);
void MVE_rmHoldMovie(void);
void MVE_rmEndMovie(void);

void MVE_getVideoSpec(MVE_videoSpec *vSpec);

void MVE_sndInit(int x);

typedef unsigned int (*mve_cb_Read)(void *stream, void *buffer, unsigned int count);

typedef void *(*mve_cb_Alloc)(unsigned int size);
typedef void (*mve_cb_Free)(void *ptr);

typedef void (*mve_cb_ShowFrame)(unsigned char *buffer, unsigned int bufw, unsigned int bufh, unsigned int sx,
                                 unsigned int sy, unsigned int w, unsigned int h, unsigned int dstx, unsigned int dsty);

typedef void (*mve_cb_SetPalette)(unsigned char *p, unsigned int start, unsigned int count);

void MVE_ioCallbacks(mve_cb_Read io_read);
void MVE_memCallbacks(mve_cb_Alloc mem_alloc, mve_cb_Free mem_free);
void MVE_sfCallbacks(mve_cb_ShowFrame showframe);
void MVE_palCallbacks(mve_cb_SetPalette setpalette);

#endif /* _LIBMVE_H */
