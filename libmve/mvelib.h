#ifndef INCLUDED_MVELIB_H
#define INCLUDED_MVELIB_H

#include <stdio.h>
#include <stdlib.h>

#include "libmve.h"

extern mve_cb_Read mve_read;
extern mve_cb_Alloc mve_alloc;
extern mve_cb_Free mve_free;
extern mve_cb_ShowFrame mve_showframe;
extern mve_cb_SetPalette mve_setpalette;

/*
 * structure for maintaining info on a MVEFILE stream
 */
typedef struct MVEFILE
{
    void           *stream;
    unsigned char  *cur_chunk;
    int             buf_size;
    int             cur_fill;
    int             next_segment;
} MVEFILE;

/*
 * open a .MVE file
 */
MVEFILE *mvefile_open(void *stream);

/*
 * close a .MVE file
 */
void mvefile_close(MVEFILE *movie);

/*
 * get size of next segment in chunk (-1 if no more segments in chunk)
 */
int mvefile_get_next_segment_size(MVEFILE *movie);

/*
 * get type of next segment in chunk (0xff if no more segments in chunk)
 */
unsigned char mvefile_get_next_segment_major(MVEFILE *movie);

/*
 * get subtype (version) of next segment in chunk (0xff if no more segments in
 * chunk)
 */
unsigned char mvefile_get_next_segment_minor(MVEFILE *movie);

/*
 * see next segment (return NULL if no next segment)
 */
unsigned char *mvefile_get_next_segment(MVEFILE *movie);

/*
 * advance to next segment
 */
void mvefile_advance_segment(MVEFILE *movie);

/*
 * fetch the next chunk (return 0 if at end of stream)
 */
int mvefile_fetch_next_chunk(MVEFILE *movie);

/*
 * callback for segment type
 */
typedef int (*MVESEGMENTHANDLER)(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context);

/*
 * structure for maintaining an MVE stream
 */
typedef struct MVESTREAM
{
    MVEFILE                    *movie;
    void                       *context;
    MVESEGMENTHANDLER           handlers[32];
} MVESTREAM;

/*
 * open an MVE stream
 */
MVESTREAM *mve_open(void *stream);

/*
 * close an MVE stream
 */
void mve_close(MVESTREAM *movie);

/*
 * reset an MVE stream
 */
void mve_reset(MVESTREAM *movie);

/*
 * set segment type handler
 */
void mve_set_handler(MVESTREAM *movie, unsigned char major, MVESEGMENTHANDLER handler);

/*
 * set segment handler context
 */
void mve_set_handler_context(MVESTREAM *movie, void *context);

/*
 * play next chunk
 */
int mve_play_next_chunk(MVESTREAM *movie);

#endif /* INCLUDED_MVELIB_H */
