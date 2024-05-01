#ifdef HAVE_CONFIG_H
#include "conf.h"
#endif

#include <string.h> // for mem* functions
#if !defined(_WIN32) && !defined(macintosh)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#include "mvelib.h"

static const char  MVE_HEADER[]  = "Interplay MVE File\x1A";
static const short MVE_HDRCONST1 = 0x001A;
static const short MVE_HDRCONST2 = 0x0100;
static const short MVE_HDRCONST3 = 0x1133;

mve_cb_Read mve_read;
mve_cb_Alloc mve_alloc;
mve_cb_Free mve_free;
mve_cb_ShowFrame mve_showframe;
mve_cb_SetPalette mve_setpalette;

/*
 * private utility functions
 */
static short _mve_get_short(unsigned char *data);
static unsigned short _mve_get_ushort(unsigned char *data);

/*
 * private functions for mvefile
 */
static MVEFILE *_mvefile_alloc(void);
static void _mvefile_free(MVEFILE *movie);
static int _mvefile_open(MVEFILE *movie, void *stream);
static void _mvefile_reset(MVEFILE *movie);
static int  _mvefile_read_header(MVEFILE *movie);
static void _mvefile_set_buffer_size(MVEFILE *movie, int buf_size);
static int _mvefile_fetch_next_chunk(MVEFILE *movie);

/*
 * private functions for mvestream
 */
static MVESTREAM *_mvestream_alloc(void);
static void _mvestream_free(MVESTREAM *movie);
static int _mvestream_open(MVESTREAM *movie, void *stream);
static void _mvestream_reset(MVESTREAM *movie);

/************************************************************
 * public MVEFILE functions
 ************************************************************/

/*
 * open an MVE file
 */
MVEFILE *mvefile_open(void *stream)
{
    MVEFILE *file;

    /* create the file */
    file = _mvefile_alloc();
    if (! _mvefile_open(file, stream))
    {
        _mvefile_free(file);
        return NULL;
    }

    /* initialize the file */
    _mvefile_set_buffer_size(file, 1024);

    /* verify the file's header */
    if (! _mvefile_read_header(file))
    {
        _mvefile_free(file);
        return NULL;
    }

    /* now, prefetch the next chunk */
    _mvefile_fetch_next_chunk(file);

    return file;
}

/*
 * close a MVE file
 */
void mvefile_close(MVEFILE *movie)
{
    _mvefile_free(movie);
}

/*
 * reset a MVE file
 */
void mvefile_reset(MVEFILE *file)
{
	_mvefile_reset(file);

    /* initialize the file */
    _mvefile_set_buffer_size(file, 1024);

    /* verify the file's header */
    if (! _mvefile_read_header(file))
    {
        _mvefile_free(file);
		//return NULL;
    }

    /* now, prefetch the next chunk */
    _mvefile_fetch_next_chunk(file);
}

/*
 * get the size of the next segment
 */
int mvefile_get_next_segment_size(MVEFILE *movie)
{
    /* if nothing is cached, fail */
    if (movie->cur_chunk == NULL  ||  movie->next_segment >= movie->cur_fill)
        return -1;

    /* if we don't have enough data to get a segment, fail */
    if (movie->cur_fill - movie->next_segment < 4)
        return -1;

    /* otherwise, get the data length */
    return _mve_get_short(movie->cur_chunk + movie->next_segment);
}

/*
 * get type of next segment in chunk (0xff if no more segments in chunk)
 */
unsigned char mvefile_get_next_segment_major(MVEFILE *movie)
{
    /* if nothing is cached, fail */
    if (movie->cur_chunk == NULL  ||  movie->next_segment >= movie->cur_fill)
        return 0xff;

    /* if we don't have enough data to get a segment, fail */
    if (movie->cur_fill - movie->next_segment < 4)
        return 0xff;

    /* otherwise, get the data length */
    return movie->cur_chunk[movie->next_segment + 2];
}

/*
 * get subtype (version) of next segment in chunk (0xff if no more segments in
 * chunk)
 */
unsigned char mvefile_get_next_segment_minor(MVEFILE *movie)
{
    /* if nothing is cached, fail */
    if (movie->cur_chunk == NULL  ||  movie->next_segment >= movie->cur_fill)
        return 0xff;

    /* if we don't have enough data to get a segment, fail */
    if (movie->cur_fill - movie->next_segment < 4)
        return 0xff;

    /* otherwise, get the data length */
    return movie->cur_chunk[movie->next_segment + 3];
}

/*
 * see next segment (return NULL if no next segment)
 */
unsigned char *mvefile_get_next_segment(MVEFILE *movie)
{
    /* if nothing is cached, fail */
    if (movie->cur_chunk == NULL  ||  movie->next_segment >= movie->cur_fill)
        return NULL;

    /* if we don't have enough data to get a segment, fail */
    if (movie->cur_fill - movie->next_segment < 4)
        return NULL;

    /* otherwise, get the data length */
    return movie->cur_chunk + movie->next_segment + 4;
}

/*
 * advance to next segment
 */
void mvefile_advance_segment(MVEFILE *movie)
{
    /* if nothing is cached, fail */
    if (movie->cur_chunk == NULL  ||  movie->next_segment >= movie->cur_fill)
        return;

    /* if we don't have enough data to get a segment, fail */
    if (movie->cur_fill - movie->next_segment < 4)
        return;

    /* else, advance to next segment */
    movie->next_segment +=
        (4 + _mve_get_ushort(movie->cur_chunk + movie->next_segment));
}

/*
 * fetch the next chunk (return 0 if at end of stream)
 */
int mvefile_fetch_next_chunk(MVEFILE *movie)
{
    return _mvefile_fetch_next_chunk(movie);
}

/************************************************************
 * public MVESTREAM functions
 ************************************************************/

/*
 * open an MVE stream
 */
MVESTREAM *mve_open(void *stream)
{
    MVESTREAM *movie;

    /* allocate */
    movie = _mvestream_alloc();

    /* open */
    if (! _mvestream_open(movie, stream))
    {
        _mvestream_free(movie);
        return NULL;
    }

    return movie;
}

/*
 * close an MVE stream
 */
void mve_close(MVESTREAM *movie)
{
    _mvestream_free(movie);
}

/*
 * reset an MVE stream
 */
void mve_reset(MVESTREAM *movie)
{
	_mvestream_reset(movie);
}

/*
 * set segment type handler
 */
void mve_set_handler(MVESTREAM *movie, unsigned char major, MVESEGMENTHANDLER handler)
{
    if (major < 32)
        movie->handlers[major] = handler;
}

/*
 * set segment handler context
 */
void mve_set_handler_context(MVESTREAM *movie, void *context)
{
    movie->context = context;
}

/*
 * play next chunk
 */
int mve_play_next_chunk(MVESTREAM *movie)
{
    unsigned char major, minor;
    unsigned char *data;
    int len;

    /* loop over segments */
    major = mvefile_get_next_segment_major(movie->movie);
    while (major != 0xff)
    {
        /* check whether to handle the segment */
        if (major < 32  &&  movie->handlers[major] != NULL)
        {
            minor = mvefile_get_next_segment_minor(movie->movie);
            len = mvefile_get_next_segment_size(movie->movie);
            data = mvefile_get_next_segment(movie->movie);

            if (! movie->handlers[major](major, minor, data, len, movie->context))
                return 0;
        }

        /* advance to next segment */
        mvefile_advance_segment(movie->movie);
        major = mvefile_get_next_segment_major(movie->movie);
    }

    if (! mvefile_fetch_next_chunk(movie->movie))
        return 0;

    /* return status */
    return 1;
}

/************************************************************
 * private functions
 ************************************************************/

/*
 * allocate an MVEFILE
 */
static MVEFILE *_mvefile_alloc(void)
{
    MVEFILE *file = (MVEFILE *)mve_alloc(sizeof(MVEFILE));
    file->stream = NULL;
    file->cur_chunk = NULL;
    file->buf_size = 0;
    file->cur_fill = 0;
    file->next_segment = 0;

    return file;
}

/*
 * free an MVE file
 */
static void _mvefile_free(MVEFILE *movie)
{
    /* free the stream */
	movie->stream = NULL;

    /* free the buffer */
    if (movie->cur_chunk)
        mve_free(movie->cur_chunk);
    movie->cur_chunk = NULL;

    /* not strictly necessary */
    movie->buf_size = 0;
    movie->cur_fill = 0;
    movie->next_segment = 0;

    /* free the struct */
    mve_free(movie);
}

/*
 * open the file stream in thie object
 */
static int _mvefile_open(MVEFILE *file, void *stream)
{
    file->stream = stream;
    if (! file->stream)
        return 0;

    return 1;
}

/*
 * allocate an MVEFILE
 */
static void _mvefile_reset(MVEFILE *file)
{
#if 0
    file->cur_chunk = NULL;
    file->buf_size = 0;
    file->cur_fill = 0;
    file->next_segment = 0;
#endif
}

/*
 * read and verify the header of the recently opened file
 */
static int _mvefile_read_header(MVEFILE *movie)
{
    unsigned char buffer[26];

    /* check the file is open */
    if (! movie->stream)
        return 0;

    /* check the file is long enough */
    if (! mve_read(movie->stream, buffer, 26))
        return 0;

    /* check the signature */
    if (memcmp(buffer, MVE_HEADER, 20))
        return 0;

    /* check the hard-coded constants */
    if (_mve_get_short(buffer+20) != MVE_HDRCONST1)
        return 0;
    if (_mve_get_short(buffer+22) != MVE_HDRCONST2)
        return 0;
    if (_mve_get_short(buffer+24) != MVE_HDRCONST3)
        return 0;

    return 1;
}

static void _mvefile_set_buffer_size(MVEFILE *movie, int buf_size)
{
    unsigned char *new_buffer;
    int new_len;

    /* check if this would be a redundant operation */
    if (buf_size  <=  movie->buf_size)
        return;

    /* allocate new buffer */
    new_len = 100 + buf_size;
    new_buffer = (unsigned char *)mve_alloc(new_len);

    /* copy old data */
    if (movie->cur_chunk  &&  movie->cur_fill)
        memcpy(new_buffer, movie->cur_chunk, movie->cur_fill);

    /* free old buffer */
    if (movie->cur_chunk)
    {
        mve_free(movie->cur_chunk);
        movie->cur_chunk = 0;
    }

    /* install new buffer */
    movie->cur_chunk = new_buffer;
    movie->buf_size = new_len;
}

static int _mvefile_fetch_next_chunk(MVEFILE *movie)
{
    unsigned char buffer[4];
    unsigned short length;

    /* fail if not open */
    if (! movie->stream)
        return 0;

    /* fail if we can't read the next segment descriptor */
    if (! mve_read(movie->stream, buffer, 4))
        return 0;

    /* pull out the next length */
    length = _mve_get_short(buffer);

    /* make sure we've got sufficient space */
    _mvefile_set_buffer_size(movie, length);

    /* read the chunk */
    if (! mve_read(movie->stream, movie->cur_chunk, length))
        return 0;
    movie->cur_fill = length;
    movie->next_segment = 0;

    return 1;
}

static short _mve_get_short(unsigned char *data)
{
    short value;
    value = data[0] | (data[1] << 8);
    return value;
}

static unsigned short _mve_get_ushort(unsigned char *data)
{
    unsigned short value;
    value = data[0] | (data[1] << 8);
    return value;
}

/*
 * allocate an MVESTREAM
 */
static MVESTREAM *_mvestream_alloc(void)
{
    MVESTREAM *movie;

    /* allocate and zero-initialize everything */
    movie = (MVESTREAM *)mve_alloc(sizeof(MVESTREAM));
    movie->movie = NULL;
    movie->context = 0;
    memset(movie->handlers, 0, sizeof(movie->handlers));

    return movie;
}

/*
 * free an MVESTREAM
 */
static void _mvestream_free(MVESTREAM *movie)
{
    /* close MVEFILE */
    if (movie->movie)
        mvefile_close(movie->movie);
    movie->movie = NULL;

    /* clear context and handlers */
    movie->context = NULL;
    memset(movie->handlers, 0, sizeof(movie->handlers));

	/* free the struct */
	mve_free(movie);
}

/*
 * open an MVESTREAM object
 */
static int _mvestream_open(MVESTREAM *movie, void *stream)
{
    movie->movie = mvefile_open(stream);

    return (movie->movie == NULL) ? 0 : 1;
}

/*
 * reset an MVESTREAM
 */
static void _mvestream_reset(MVESTREAM *movie)
{
	mvefile_reset(movie->movie);
}
