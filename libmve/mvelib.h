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

#ifndef INCLUDED_MVELIB_H
#define INCLUDED_MVELIB_H

#include <cstdio>
#include <cstdlib>

#include "SystemInterfaces.h"

/* callback for reading stream */
typedef unsigned int (*mve_cb_Read)(void *stream, void *buffer, unsigned int count);
/* callback for memore allocating */
typedef void *(*mve_cb_Alloc)(unsigned int size);
/* callback for memory freeing */
typedef void (*mve_cb_Free)(void *ptr);
/* callback for showing frame */
typedef void (*mve_cb_ShowFrame)(unsigned char *buffer, unsigned int bufw, unsigned int bufh, unsigned int sx,
                                 unsigned int sy, unsigned int w, unsigned int h, unsigned int dstx, unsigned int dsty,
                                 unsigned int hicolor);
/* callback for setting palette */
typedef void (*mve_cb_SetPalette)(unsigned char *p, unsigned int start, unsigned int count);
/* callback for segment type */
typedef int (*MVESEGMENTHANDLER)(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context);

extern mve_cb_Read mve_read;
extern mve_cb_Alloc mve_alloc;
extern mve_cb_Free mve_free;
extern mve_cb_ShowFrame mve_showframe;
extern mve_cb_SetPalette mve_setpalette;

#define MVE_ERR_EOF 1

typedef struct {
  int screenWidth;
  int screenHeight;
  int width;
  int height;
  int truecolor;
} MVE_videoSpec;

/* structure for maintaining info on a MVEFILE stream */
typedef struct MVEFILE {
  void *stream;
  unsigned char *cur_chunk;
  int buf_size;
  int cur_fill;
  int next_segment;
} MVEFILE;

/* structure for maintaining an MVE stream */
typedef struct MVESTREAM {
  MVEFILE *movie;
  void *context;
  MVESEGMENTHANDLER handlers[32];
} MVESTREAM;

MVESTREAM* MVE_rmPrepMovie(void *stream, int x, int y, int track);
int MVE_rmStepMovie(MVESTREAM *mve);
void MVE_rmHoldMovie();
void MVE_rmEndMovie(MVESTREAM *mve);

void MVE_getVideoSpec(MVE_videoSpec *vSpec);

void MVE_sndInit(ISoundDevice *lpDS);

void MVE_sndInit(int x);

void MVE_ioCallbacks(mve_cb_Read io_read);
void MVE_memCallbacks(mve_cb_Alloc mem_alloc, mve_cb_Free mem_free);
void MVE_sfCallbacks(mve_cb_ShowFrame showframe);
void MVE_palCallbacks(mve_cb_SetPalette setpalette);

// Low-level functions

/* open an MVE file */
MVEFILE *mvefile_open(void *stream);

/* close an MVE file */
void mvefile_close(MVEFILE *movie);

/* get size of next segment in chunk (-1 if no more segments in chunk) */
int mvefile_get_next_segment_size(MVEFILE *movie);

/* get type of next segment in chunk (0xff if no more segments in chunk) */
unsigned char mvefile_get_next_segment_major(MVEFILE *movie);

/* get subtype (version) of next segment in chunk (0xff if no more segments in chunk) */
unsigned char mvefile_get_next_segment_minor(MVEFILE *movie);

/* see next segment (return NULL if no next segment) */
unsigned char *mvefile_get_next_segment(MVEFILE *movie);

/* advance to next segment */
void mvefile_advance_segment(MVEFILE *movie);

/* fetch the next chunk (return 0 if at end of stream) */
int mvefile_fetch_next_chunk(MVEFILE *movie);

/* open an MVE stream */
MVESTREAM *mve_open(void *stream);

/* close an MVE stream */
void mve_close(MVESTREAM *movie);

/* reset an MVE stream */
void mve_reset(MVESTREAM *movie);

/* set segment type handler */
void mve_set_handler(MVESTREAM *movie, unsigned char major, MVESEGMENTHANDLER handler);

/* set segment handler context */
void mve_set_handler_context(MVESTREAM *movie, void *context);

/* play next chunk */
int mve_play_next_chunk(MVESTREAM *movie);

#endif /* INCLUDED_MVELIB_H */
