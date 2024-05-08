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

#define AUDIO

#include <cstring>
#ifdef _WIN32
#include <windows.h>
#else
#include <ctime>
#include <sys/time.h>
#endif // _WIN32

#if defined(AUDIO)
#include <SDL.h>
#endif

#include "byteswap.h"
#include "decoders.h"
#include "mvelib.h"
#include "mve_audio.h"
#include "SystemInterfaces.h"

#define MVE_OPCODE_ENDOFSTREAM 0x00
#define MVE_OPCODE_ENDOFCHUNK 0x01
#define MVE_OPCODE_CREATETIMER 0x02
#define MVE_OPCODE_INITAUDIOBUFFERS 0x03
#define MVE_OPCODE_STARTSTOPAUDIO 0x04
#define MVE_OPCODE_INITVIDEOBUFFERS 0x05

#define MVE_OPCODE_DISPLAYVIDEO 0x07
#define MVE_OPCODE_AUDIOFRAMEDATA 0x08
#define MVE_OPCODE_AUDIOFRAMESILENCE 0x09
#define MVE_OPCODE_INITVIDEOMODE 0x0A

#define MVE_OPCODE_SETPALETTE 0x0C
#define MVE_OPCODE_SETPALETTECOMPRESSED 0x0D

#define MVE_OPCODE_SETDECODINGMAP 0x0F

#define MVE_OPCODE_VIDEODATA 0x11

#define MVE_AUDIO_FLAGS_STEREO 1
#define MVE_AUDIO_FLAGS_16BIT 2
#define MVE_AUDIO_FLAGS_COMPRESSED 4

int g_spdFactorNum = 0;
static int g_spdFactorDenom = 10;
static int g_frameUpdated = 0;

static ISoundDevice *snd_ds = nullptr;

static SDL_AudioDeviceID device = 0;

static short get_short(const unsigned char *data) {
  return D3::convert_le<int16_t>(data[0] | (data[1] << 8));
}

static unsigned short get_ushort(const unsigned char *data) {
  return D3::convert_le<uint16_t>(data[0] | (data[1] << 8));
}

static int get_int(const unsigned char *data) {
  return D3::convert_le<int32_t>(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
}

static unsigned int unhandled_chunks[32 * 256];

static int default_seg_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
  unhandled_chunks[major << 8 | minor]++;
  // fprintf(stderr, "unknown chunk type %02x/%02x\n", major, minor);
  return 1;
}

/*************************
 * general handlers
 *************************/
static int end_movie_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
  return 0;
}

/*************************
 * timer handlers
 *************************/

/*
 * timer variables
 */
static int timer_created = 0;
static int micro_frame_delay = 0;
static int timer_started = 0;
static unsigned long int timer_expire = 0;

#if defined(_WIN32) || defined(macintosh)

unsigned long int timer_getmicroseconds() {
  static int counter = 0;
#ifdef _WIN32
  DWORD now = GetTickCount();
#else
  long now = TickCount();
#endif
  counter++;

  return now * 1000 + counter;
}

#else

unsigned long int timer_getmicroseconds() {
  struct timeval tv;
  static time_t starttime = 0;

  gettimeofday(&tv, nullptr);

  if (!starttime)
    starttime = tv.tv_sec;

  return (tv.tv_sec - starttime) * 1000000 + tv.tv_usec;
}

#endif

void timer_sleepmicroseconds(unsigned long int usec) {
#ifdef _WIN32
  Sleep(usec / 1000);
#elif defined(macintosh)
  Delay(usec / 1000);
#else
  struct timespec ts;
  ts.tv_sec = usec / 1000000;
  ts.tv_nsec = usec % 1000000 * 1000;
  nanosleep(&ts, nullptr);
#endif
}

static int create_timer_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {

#if !defined(_WIN32) && !defined(macintosh) // FIXME
  __extension__ long long temp;
#else
  long temp;
#endif

  if (timer_created)
    return 1;
  else
    timer_created = 1;

  micro_frame_delay = get_int(data) * (int)get_short(data + 4);
  if (g_spdFactorNum != 0) {
    temp = micro_frame_delay;
    temp *= g_spdFactorNum;
    temp /= g_spdFactorDenom;
    micro_frame_delay = (int)temp;
  }

  return 1;
}

static void timer_stop() {
  timer_expire = 0;
  timer_started = 0;
}

static void timer_start() {
  timer_expire = timer_getmicroseconds();
  timer_expire += micro_frame_delay;
  timer_started = 1;
}

static void do_timer_wait() {
  unsigned long int ts;
  unsigned long int tv;

  if (!timer_started)
    return;

  tv = timer_getmicroseconds();
  if (tv > timer_expire)
    goto end;

  ts = timer_expire - tv;

  timer_sleepmicroseconds(ts);

end:
  timer_expire += micro_frame_delay;
}

/*************************
 * audio handlers
 *************************/

#ifdef AUDIO
#define TOTAL_AUDIO_BUFFERS 64

static int audiobuf_created = 0;
static short *mve_audio_buffers[TOTAL_AUDIO_BUFFERS];
static int mve_audio_buflens[TOTAL_AUDIO_BUFFERS];
static int mve_audio_curbuf_curpos = 0;
static int mve_audio_bufhead = 0;
static int mve_audio_buftail = 0;
static int mve_audio_playing = 0;
static int mve_audio_canplay = 0;
static int mve_audio_compressed = 0;
static int mve_audio_enabled = 1;

static void mve_audio_callback(void *userdata, unsigned char *stream, int len) {
  int total = 0;
  int length;
  if (mve_audio_bufhead == mve_audio_buftail)
    return /* 0 */;

  // fprintf(stderr, "+ <%d (%d), %d, %d>\n", mve_audio_bufhead, mve_audio_curbuf_curpos, mve_audio_buftail, len);

  while (mve_audio_bufhead != mve_audio_buftail                                     /* while we have more buffers  */
         && len > (mve_audio_buflens[mve_audio_bufhead] - mve_audio_curbuf_curpos)) /* and while we need more data */
  {
    length = mve_audio_buflens[mve_audio_bufhead] - mve_audio_curbuf_curpos;
    memcpy(stream,                                                                            /* cur output position */
           ((unsigned char *)mve_audio_buffers[mve_audio_bufhead]) + mve_audio_curbuf_curpos, /* cur input position  */
           length);                                                                           /* cur input length    */

    total += length;
    stream += length;                               /* advance output */
    len -= length;                                  /* decrement avail ospace */
    mve_free(mve_audio_buffers[mve_audio_bufhead]); /* free the buffer */
    mve_audio_buffers[mve_audio_bufhead] = NULL;    /* free the buffer */
    mve_audio_buflens[mve_audio_bufhead] = 0;       /* free the buffer */

    if (++mve_audio_bufhead == TOTAL_AUDIO_BUFFERS) /* next buffer */
      mve_audio_bufhead = 0;
    mve_audio_curbuf_curpos = 0;
  }

  // fprintf(stderr, "= <%d (%d), %d, %d>: %d\n", mve_audio_bufhead, mve_audio_curbuf_curpos, mve_audio_buftail, len,
  // total);
  /*    return total; */

  if (len != 0                                   /* ospace remaining  */
      && mve_audio_bufhead != mve_audio_buftail) /* buffers remaining */
  {
    memcpy(stream,                                                                            /* dest */
           ((unsigned char *)mve_audio_buffers[mve_audio_bufhead]) + mve_audio_curbuf_curpos, /* src */
           len);                                                                              /* length */

    mve_audio_curbuf_curpos += len; /* advance input */
    stream += len;                  /* advance output (unnecessary) */
    len -= len;                     /* advance output (unnecessary) */

    if (mve_audio_curbuf_curpos >= mve_audio_buflens[mve_audio_bufhead]) /* if this ends the current chunk */
    {
      mve_free(mve_audio_buffers[mve_audio_bufhead]); /* free buffer */
      mve_audio_buffers[mve_audio_bufhead] = NULL;
      mve_audio_buflens[mve_audio_bufhead] = 0;

      if (++mve_audio_bufhead == TOTAL_AUDIO_BUFFERS) /* next buffer */
        mve_audio_bufhead = 0;
      mve_audio_curbuf_curpos = 0;
    }
  }

  // fprintf(stderr, "- <%d (%d), %d, %d>\n", mve_audio_bufhead, mve_audio_curbuf_curpos, mve_audio_buftail, len);
}
#endif

static int create_audiobuf_handler(unsigned char major, unsigned char minor, unsigned char *data, int len,
                                   void *context) {
#ifdef AUDIO
  int flags;
  int sample_rate;
  int desired_buffer;

  int stereo;
  int bitsize;

  int format;

  if (!mve_audio_enabled)
    return 1;

  if (audiobuf_created)
    return 1;
  else
    audiobuf_created = 1;

  flags = get_ushort(data + 2);
  sample_rate = get_ushort(data + 4);
  desired_buffer = get_int(data + 6);

  stereo = (flags & MVE_AUDIO_FLAGS_STEREO) ? 1 : 0;
  bitsize = (flags & MVE_AUDIO_FLAGS_16BIT) ? 1 : 0;

  mve_audio_compressed = 0;
  if (minor > 0 && (flags & MVE_AUDIO_FLAGS_COMPRESSED)) {
    mve_audio_compressed = 1;
  }

  if (bitsize == 1) {
#ifdef OUTRAGE_BIG_ENDIAN
    format = AUDIO_S16MSB;
#else
    format = AUDIO_S16LSB;
#endif
  } else {
    format = AUDIO_U8;
  }

  fprintf(stderr, "creating audio buffers:\n");
  fprintf(stderr, "sample rate = %d, stereo = %d, bitsize = %d, compressed = %d\n", sample_rate, stereo,
          bitsize ? 16 : 8, mve_audio_compressed);

  SDL_AudioSpec spec {
      .freq = sample_rate,
      .format = (unsigned short)format,
      .channels = (unsigned char)(stereo ? 2 : 1),
      .size = 4096,
      .callback = mve_audio_callback,
  };
  device = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
  if (device != 0) {
    fprintf(stderr, "   success\n");
    mve_audio_canplay = 1;
  } else {
    fprintf(stderr, "   failure : %s\n", SDL_GetError());
    mve_audio_canplay = 0;
  }

  mve_audio_canplay = 1;

  memset(mve_audio_buffers, 0, sizeof(mve_audio_buffers));
  memset(mve_audio_buflens, 0, sizeof(mve_audio_buflens));
#endif

  return 1;
}

static int play_audio_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
#ifdef AUDIO
  if (mve_audio_canplay && !mve_audio_playing && mve_audio_bufhead != mve_audio_buftail) {
    SDL_PauseAudioDevice(device, 0);
    mve_audio_playing = 1;
  }
#endif
  return 1;
}

static int audio_data_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
#ifdef AUDIO
  static const int selected_chan = 1;
  int chan;
  int nsamp;
  if (mve_audio_canplay) {
    chan = get_ushort(data + 2);
    nsamp = get_ushort(data + 4);
    if (chan & selected_chan) {
      /* HACK: +4 mveaudio_uncompress adds 4 more bytes */
      if (major == MVE_OPCODE_AUDIOFRAMEDATA) {
        if (mve_audio_compressed) {
          nsamp += 4;

          mve_audio_buflens[mve_audio_buftail] = nsamp;
          mve_audio_buffers[mve_audio_buftail] = (short *)mve_alloc(nsamp);
          mveaudio_uncompress(mve_audio_buffers[mve_audio_buftail], data, -1); /* XXX */
        } else {
          nsamp -= 8;
          data += 8;

          mve_audio_buflens[mve_audio_buftail] = nsamp;
          mve_audio_buffers[mve_audio_buftail] = (short *)mve_alloc(nsamp);
          memcpy(mve_audio_buffers[mve_audio_buftail], data, nsamp);
        }
      } else {
        mve_audio_buflens[mve_audio_buftail] = nsamp;
        mve_audio_buffers[mve_audio_buftail] = (short *)mve_alloc(nsamp);

        memset(mve_audio_buffers[mve_audio_buftail], 0, nsamp); /* XXX */
      }

      if (++mve_audio_buftail == TOTAL_AUDIO_BUFFERS)
        mve_audio_buftail = 0;

      if (mve_audio_buftail == mve_audio_bufhead)
        fprintf(stderr, "d'oh!  buffer ring overrun (%d)\n", mve_audio_bufhead);
    }
  }
#endif

  return 1;
}

/*************************
 * video handlers
 *************************/

static int videobuf_created = 0;
static int video_initialized = 0;
int g_width, g_height;
void *g_vBuffers = NULL, *g_vBackBuf1, *g_vBackBuf2;

static int g_destX, g_destY;
static int g_screenWidth, g_screenHeight;
static unsigned char *g_pCurMap = NULL;
static int g_nMapLength = 0;
static int g_truecolor;

static int create_videobuf_handler(unsigned char major, unsigned char minor, unsigned char *data, int len,
                                   void *context) {
  short w, h;
  short count, truecolor;

  if (videobuf_created)
    return 1;
  else
    videobuf_created = 1;

  w = get_short(data);
  h = get_short(data + 2);

  if (minor > 0) {
    count = get_short(data + 4);
  } else {
    count = 1;
  }

  if (minor > 1) {
    truecolor = get_short(data + 6);
  } else {
    truecolor = 0;
  }

  g_width = w << 3;
  g_height = h << 3;

  /* TODO: * 4 causes crashes on some files */
  /* only malloc once */
  if (g_vBuffers == NULL)
    g_vBackBuf1 = g_vBuffers = mve_alloc(g_width * g_height * 8);
  if (truecolor) {
    g_vBackBuf2 = (unsigned short *)g_vBackBuf1 + (g_width * g_height);
  } else {
    g_vBackBuf2 = (unsigned char *)g_vBackBuf1 + (g_width * g_height);
  }

  memset(g_vBackBuf1, 0, g_width * g_height * 4);

#ifdef DEBUG
  fprintf(stderr, "DEBUG: w,h=%d,%d count=%d, tc=%d\n", w, h, count, truecolor);
#endif

  g_truecolor = truecolor;

  return 1;
}

static int display_video_handler(unsigned char major, unsigned char minor, unsigned char *data, int len,
                                 void *context) {
  if (g_destX == -1) // center it
    g_destX = (g_screenWidth - g_width) >> 1;
  if (g_destY == -1) // center it
    g_destY = (g_screenHeight - g_height) >> 1;

  mve_showframe((unsigned char *)g_vBackBuf1, g_width, g_height, 0, 0, g_width, g_height, g_destX, g_destY,
                g_truecolor);

  g_frameUpdated = 1;

  return 1;
}

static int init_video_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
  short width, height;

  if (video_initialized)
    return 1; /* maybe we actually need to change width/height here? */
  else
    video_initialized = 1;

  width = get_short(data);
  height = get_short(data + 2);
  g_screenWidth = width;
  g_screenHeight = height;

  return 1;
}

static int video_palette_handler(unsigned char major, unsigned char minor, unsigned char *data, int len,
                                 void *context) {
  short start, count;
  unsigned char *p;

  start = get_short(data);
  count = get_short(data + 2);

  p = data + 4;

  mve_setpalette(p - 3 * start, start, count);

  return 1;
}

static int video_codemap_handler(unsigned char major, unsigned char minor, unsigned char *data, int len,
                                 void *context) {
  g_pCurMap = data;
  g_nMapLength = len;
  return 1;
}

static int video_data_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
  short nFrameHot, nFrameCold;
  short nXoffset, nYoffset;
  short nXsize, nYsize;
  unsigned short nFlags;
  unsigned char *temp;

  nFrameHot = get_short(data);
  nFrameCold = get_short(data + 2);
  nXoffset = get_short(data + 4);
  nYoffset = get_short(data + 6);
  nXsize = get_short(data + 8);
  nYsize = get_short(data + 10);
  nFlags = get_ushort(data + 12);

  if (nFlags & 1) {
    temp = (unsigned char *)g_vBackBuf1;
    g_vBackBuf1 = g_vBackBuf2;
    g_vBackBuf2 = temp;
  }

  /* convert the frame */
  if (g_truecolor) {
    decodeFrame16((unsigned char *)g_vBackBuf1, g_pCurMap, g_nMapLength, data + 14, len - 14);
  } else {
    decodeFrame8((unsigned char *)g_vBackBuf1, g_pCurMap, g_nMapLength, data + 14, len - 14);
  }

  return 1;
}

static int end_chunk_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
  g_pCurMap = NULL;
  return 1;
}

void MVE_ioCallbacks(mve_cb_Read io_read) { mve_read = io_read; }

void MVE_memCallbacks(mve_cb_Alloc mem_alloc, mve_cb_Free mem_free) {
  mve_alloc = mem_alloc;
  mve_free = mem_free;
}

void MVE_sfCallbacks(mve_cb_ShowFrame showframe) { mve_showframe = showframe; }

void MVE_palCallbacks(mve_cb_SetPalette setpalette) { mve_setpalette = setpalette; }

MVESTREAM* MVE_rmPrepMovie(void *src, int x, int y, int track) {
  MVESTREAM *mve;
  mve = mve_open(src);

  if (!mve)
    return nullptr;

  g_destX = x;
  g_destY = y;

  for (int i = 0; i < 32; i++)
    mve_set_handler(mve, i, default_seg_handler);

  mve_set_handler(mve, MVE_OPCODE_ENDOFSTREAM, end_movie_handler);
  mve_set_handler(mve, MVE_OPCODE_ENDOFCHUNK, end_chunk_handler);
  mve_set_handler(mve, MVE_OPCODE_CREATETIMER, create_timer_handler);
  mve_set_handler(mve, MVE_OPCODE_INITAUDIOBUFFERS, create_audiobuf_handler);
  mve_set_handler(mve, MVE_OPCODE_STARTSTOPAUDIO, play_audio_handler);
  mve_set_handler(mve, MVE_OPCODE_INITVIDEOBUFFERS, create_videobuf_handler);

  mve_set_handler(mve, MVE_OPCODE_DISPLAYVIDEO, display_video_handler);
  mve_set_handler(mve, MVE_OPCODE_AUDIOFRAMEDATA, audio_data_handler);
  mve_set_handler(mve, MVE_OPCODE_AUDIOFRAMESILENCE, audio_data_handler);
  mve_set_handler(mve, MVE_OPCODE_INITVIDEOMODE, init_video_handler);

  mve_set_handler(mve, MVE_OPCODE_SETPALETTE, video_palette_handler);
  mve_set_handler(mve, MVE_OPCODE_SETPALETTECOMPRESSED, default_seg_handler);

  mve_set_handler(mve, MVE_OPCODE_SETDECODINGMAP, video_codemap_handler);

  mve_set_handler(mve, MVE_OPCODE_VIDEODATA, video_data_handler);

  mve_play_next_chunk(mve); /* video initialization chunk */
  if (mve_audio_enabled)
    mve_play_next_chunk(mve); /* audio initialization chunk */

  return mve;
}

void MVE_getVideoSpec(MVE_videoSpec *vSpec) {
  vSpec->screenWidth = g_screenWidth;
  vSpec->screenHeight = g_screenHeight;
  vSpec->width = g_width;
  vSpec->height = g_height;
  vSpec->truecolor = g_truecolor;
}

int MVE_rmStepMovie(MVESTREAM *mve) {
  static int init_timer = 0;
  int cont = 1;

  if (!timer_started)
    timer_start();

  while (cont && !g_frameUpdated) // make a "step" be a frame, not a chunk...
    cont = mve_play_next_chunk(mve);
  g_frameUpdated = 0;

  if (!cont)
    return MVE_ERR_EOF;

  if (micro_frame_delay && !init_timer) {
    timer_start();
    init_timer = 1;
  }

  do_timer_wait();

  return 0;
}

void MVE_rmEndMovie(MVESTREAM *mve) {
  timer_stop();
  timer_created = 0;

#ifdef AUDIO
  if (mve_audio_canplay) {
    // only close audio if we opened it
    SDL_CloseAudioDevice(device);
    mve_audio_canplay = 0;
  }
  for (int i = 0; i < TOTAL_AUDIO_BUFFERS; i++)
    if (mve_audio_buffers[i] != NULL)
      mve_free(mve_audio_buffers[i]);
  memset(mve_audio_buffers, 0, sizeof(mve_audio_buffers));
  memset(mve_audio_buflens, 0, sizeof(mve_audio_buflens));
  mve_audio_curbuf_curpos = 0;
  mve_audio_bufhead = 0;
  mve_audio_buftail = 0;
  mve_audio_playing = 0;
  mve_audio_canplay = 0;
  mve_audio_compressed = 0;
  audiobuf_created = 0;
#endif

  mve_free(g_vBuffers);
  g_vBuffers = nullptr;
  g_pCurMap = nullptr;
  g_nMapLength = 0;
  videobuf_created = 0;
  video_initialized = 0;

  mve_close(mve);
  mve = nullptr;
}

void MVE_rmHoldMovie() { timer_started = 0; }

void MVE_sndInit(ISoundDevice *lpDS) {
#ifdef AUDIO
  snd_ds = lpDS;
#endif
}

void MVE_sndInit(int x) {
#ifdef AUDIO
  if (x == -1)
    mve_audio_enabled = 0;
  else
    mve_audio_enabled = 1;
#endif
}
