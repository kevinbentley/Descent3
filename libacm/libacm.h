/*
 * libacm - Interplay ACM audio decoder.
 *
 * Copyright (c) 2004-2010, Marko Kreen
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __LIBACM_H
#define __LIBACM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIBACM_VERSION "1.3"

#define ACM_ID		0x032897
#define ACM_WORD	2

#define ACM_OK			 0
#define ACM_ERR_OTHER		-1
#define ACM_ERR_OPEN		-2
#define ACM_ERR_NOT_ACM		-3
#define ACM_ERR_READ_ERR	-4
#define ACM_ERR_BADFMT		-5
#define ACM_ERR_CORRUPT		-6
#define ACM_ERR_UNEXPECTED_EOF	-7
#define ACM_ERR_NOT_SEEKABLE	-8

struct ACMInfo {
	unsigned channels;		/* number of sound channels (1: mono, 2: stereo */
	unsigned rate;			/* samplerate */
	unsigned acm_id;
	unsigned acm_version;
	unsigned acm_channels;		/* channels from header (often wrong) */
	unsigned acm_level;
	unsigned acm_cols;		/* 1 << acm_level */
	unsigned acm_rows;
};

struct acm_io_callbacks {
	/*
	 * Read up to "n" items with "size" bytes each into the buf at "ptr",
	 * kinda like fread().
	 * "datasrc" is the "io_arg" that was passed to acm_open_decoder()
	 *
	 * return the number of items read (not numbytes, but numbytes/size)
	 *   or 0 on EOF (end of file)
	 *   or a negative value on error
	 */
	int (*read_func)(void *ptr, int size, int n, void *datasrc);
	/* optional, must support seeking into start*/
	int (*seek_func)(void *datasrc, int offset, int whence);
	/* optional, called on acm_close */
	int (*close_func)(void *datasrc);
	/* returns size in bytes*/
	int (*get_length_func)(void *datasrc);
};

struct ACMStream {
        struct ACMInfo info;
	unsigned total_values;		/* number of sound samples in the ACM file */

	/* acm data stream */
	void *io_arg;
        struct acm_io_callbacks io;
	unsigned data_len;

	/* acm stream buffer */
	uint8_t *buf;
	unsigned buf_max, buf_size, buf_pos, bit_avail;
	unsigned bit_data;
	unsigned buf_start_ofs;

	/* block lengths (in samples) */
	unsigned block_len;
	unsigned wrapbuf_len;
	/* buffers */
	int *block;
	int *wrapbuf;
	int *ampbuf;
	int *midbuf;			/* pointer into ampbuf */
	/* result */
	unsigned block_ready:1;
	unsigned file_eof:1;
	unsigned wavc_file:1;
	unsigned stream_pos;			/* in words. absolute */
	unsigned block_pos;			/* in words, relative */
};
typedef struct ACMStream ACMStream;

/* decode.c */

/*
 * Open ACMStream from acm_io_callbacks.
 * - res: if opening the decoder succeeds, the new ACMStream will be assigned to *res
 * - io_arg: will be passed to the acm_io_callbacks as "datasrc" argument
 * - io: your custom callbacks to read the data
 * - force_chans >= 1: force the file to be decoded and played with that
 *   many channels, regardless of number of channels in the file header
 * - force_chans == 0: assume the ACM file's header contains the
 *   correct amount of channels (this is not always the case, stereo
 *   files tagged as mono exist in some games!)
 * - force_chans == -1: quirk mode: for plain ACM files stereo
 *   is assumed, for WAVC files the header's value is used
 *
 * returns ACM_OK if opening was successful, otherwise an ACM_ERR_* code
 */
int acm_open_decoder(ACMStream **res, void *io_arg, struct acm_io_callbacks io, int force_chans);

/*
 * Read up to "nbytes" bytes of audio samples from ACMStream "acm" into buffer "buf".
 * "bigendianp", "wordlen" and "sgned" specify the format you want the returned samples
 * to have, for example 0, 2, 1 for "little endian, 16bit (2byte), signed" (s16le).
 * - bigendianp: 0 for samples in little endian byteorder, 1 for big endian
 * - wordlen: only 2 for 16bit (2byte) samples is currently supported
 * - sgned: 1 for signed samples, 0 for unsigned samples
 *
 * returns the amount of bytes have been successfully read into buf
 *   or 0 on EOF (nothing left to read in file)
 *   or a value < 0 (ACM_ERR_*) on error
 */
int acm_read(ACMStream *acm, void *buf, unsigned nbytes,
		int bigendianp, int wordlen, int sgned);
void acm_close(ACMStream *acm);

/* util.c */

/*
 * Open ACMStream from file.
 * - acm: if opening the decoder succeeds, the new ACMStream will be assigned to *acm
 * - filename: filename (incl. path) to the ACM file to be opened
 * - force_chans >= 1: force the file to be decoded and played with that
 *   many channels, regardless of number of channels in the file header
 * - force_chans == 0: assume the ACM file's header contains the
 *   correct amount of channels (this is not always the case, stereo
 *   files tagged as mono exist in some games!)
 * - force_chans == -1: quirk mode: for plain ACM files stereo
 *   is assumed, for WAVC files the header's value is used
 *
 * returns ACM_OK if opening was successful, otherwise an ACM_ERR_* code
 */
int acm_open_file(ACMStream **acm, const char *filename, int force_chans);
const struct ACMInfo *acm_info(ACMStream *acm);
int acm_seekable(ACMStream *acm);
unsigned acm_bitrate(ACMStream *acm);
unsigned acm_rate(ACMStream *acm);
unsigned acm_channels(ACMStream *acm);
unsigned acm_raw_total(ACMStream *acm);
unsigned acm_raw_tell(ACMStream *acm);
unsigned acm_pcm_total(ACMStream *acm);
unsigned acm_pcm_tell(ACMStream *acm);
unsigned acm_time_total(ACMStream *acm);
unsigned acm_time_tell(ACMStream *acm);
int acm_read_loop(ACMStream *acm, void *dst, unsigned len,
		int bigendianp, int wordlen, int sgned);
int acm_seek_pcm(ACMStream *acm, unsigned pcm_pos);
int acm_seek_time(ACMStream *acm, unsigned pos_ms);
const char *acm_strerror(int err);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

