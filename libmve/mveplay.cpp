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

#include <chrono>
#include <cstring>
#include <deque>
#include <memory>
#include <thread>

#include "byteswap.h"
#include "chrono_timer.h"
#include "decoders.h"
#include "mvelib.h"
#include "mve_audio.h"

#ifdef AUDIO
#ifdef _WIN32
#include "win_sound.h"
#else
#include "lnx_sound.h"
#endif
#endif

#define MVE_OPCODE_ENDOFSTREAM 0x00           // mcmd_end
#define MVE_OPCODE_ENDOFCHUNK 0x01            // mcmd_next
#define MVE_OPCODE_CREATETIMER 0x02           // mcmd_syncInit
#define MVE_OPCODE_INITAUDIOBUFFERS 0x03      // mcmd_sndConfigure
#define MVE_OPCODE_STARTSTOPAUDIO 0x04        // mcmd_sndSync
#define MVE_OPCODE_INITVIDEOBUFFERS 0x05      // mcmd_nfConfig
#define MVE_OPCODE_UNKNOWN_06 0x06            // mcmd_nfDecomp
#define MVE_OPCODE_DISPLAYVIDEO 0x07          // mcmd_sfShowFrame
#define MVE_OPCODE_AUDIOFRAMEDATA 0x08        // mcmd_sndAdd
#define MVE_OPCODE_AUDIOFRAMESILENCE 0x09     // mcmd_sndSilence
#define MVE_OPCODE_INITVIDEOMODE 0x0A         // mcmd_gfxMode
#define MVE_OPCODE_UNKNOWN_0B 0x0B            // mcmd_palMakeSynthPalette
#define MVE_OPCODE_SETPALETTE 0x0C            // mcmd_palLoadPalette
#define MVE_OPCODE_SETPALETTECOMPRESSED 0x0D  // mcmd_palLoadCompPalette
#define MVE_OPCODE_UNKNOWN_0E 0x0E            // mcmd_nfChanges
#define MVE_OPCODE_SETDECODINGMAP 0x0F        // mcmd_nfParms
#define MVE_OPCODE_UNKNOWN_10 0x10            // mcmd_nfDecompChg
#define MVE_OPCODE_VIDEODATA 0x11             // mcmd_nfPkDecomp

#define MVE_AUDIO_FLAGS_STEREO 1
#define MVE_AUDIO_FLAGS_16BIT 2
#define MVE_AUDIO_FLAGS_COMPRESSED 4

int g_spdFactorNum = 0;
static int g_spdFactorDenom = 10;
static int g_frameUpdated = 0;

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

unsigned long int timer_getmicroseconds() {
  return D3::ChronoTimer::GetTimeUS();
}

void timer_sleepmicroseconds(unsigned long int usec) {
  std::this_thread::sleep_for(std::chrono::microseconds(usec));
}

static int create_timer_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
  long temp;

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
  uint64_t ts;
  uint64_t tv;

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
static std::unique_ptr<D3::MovieSoundDevice> snd_ds;
static int mve_audio_enabled = 1;
#else
static int mve_audio_enabled = 0;
#endif

static int create_audiobuf_handler(unsigned char major, unsigned char minor, unsigned char *data, int len,
                                   void *context) {
#ifdef AUDIO
  if (!mve_audio_enabled)
    return 1;

  int flags = get_ushort(data + 2);
  int sample_rate = get_ushort(data + 4);
  int desired_buffer = get_int(data + 6);

  int channels = (flags & MVE_AUDIO_FLAGS_STEREO) ? 2 : 1;
  int sample_size = (flags & MVE_AUDIO_FLAGS_16BIT) ? 2 : 1;

  bool is_compressed = false;
  if (minor > 0 && (flags & MVE_AUDIO_FLAGS_COMPRESSED)) {
    is_compressed = true;
  }

  snd_ds = std::make_unique<D3::MovieSoundDevice>(sample_rate, sample_size, channels, desired_buffer, is_compressed);
#endif

  return 1;
}

static int play_audio_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
#ifdef AUDIO
  if (snd_ds && snd_ds->IsInitialized()) {
    snd_ds->Play();
  }
#endif
  return 1;
}

static int audio_data_handler(unsigned char major, unsigned char minor, unsigned char *data, int len, void *context) {
#ifdef AUDIO
  static const int selected_chan = 1;
  if (snd_ds->IsInitialized()) {
    int chan = get_ushort(data + 2);
    if (chan & selected_chan) {
      if (major == MVE_OPCODE_AUDIOFRAMEDATA) {
        snd_ds->Lock();
        mveaudio_process(snd_ds->GetBuffer(), data, snd_ds->IsCompressed());
        snd_ds->Unlock();
      } else {
        // SILENCE, MORTALS!
        int nsamp = get_ushort(data + 4);
        snd_ds->Lock();
        snd_ds->GetBuffer()->insert(snd_ds->GetBuffer()->end(), nsamp, 0);
        snd_ds->Unlock();
      }
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
void *g_vBuffers = nullptr, *g_vBackBuf1, *g_vBackBuf2;

static int g_destX, g_destY;
static int g_screenWidth, g_screenHeight;
static unsigned char *g_pCurMap = nullptr;
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
  if (g_vBuffers == nullptr)
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
  unsigned char *temp;

  short nFrameHot = get_short(data);
  short nFrameCold = get_short(data + 2);
  short nXoffset = get_short(data + 4);
  short nYoffset = get_short(data + 6);
  short nXsize = get_short(data + 8);
  short nYsize = get_short(data + 10);
  unsigned short nFlags = get_ushort(data + 12);

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
  g_pCurMap = nullptr;
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
  snd_ds.reset();
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
  // snd_ds = lpDS;
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
