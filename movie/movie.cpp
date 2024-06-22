/*
* Descent 3
* Copyright (C) 2024 Parallax Software
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

#include <stdlib.h>

#ifdef __LINUX__
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

#define O_BINARY 0
#endif


#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#include <io.h>
#include "dsound.h"
#endif

#include <fcntl.h>
#include <string.h>

#include "movie.h"
#include "mvelibw.h"
#include "pserror.h"
#include "renderer.h"
#include "ddio.h"
#include "ddvid.h"
#include "grtext.h"
#include "mem.h"
#include "bitmap.h"
#include "gamefont.h"
#include "game.h"

#ifdef WIN32
#include "winapp.h"
#elif defined(__LINUX__)
#include "lnxapp.h"
#endif

namespace {
MovieFrameCallback_fp Movie_callback = NULL;
char MovieDir[512];
char SoundCardName[512];
uint16_t CurrentPalette[256];
int Movie_bm_handle = -1;
uint32_t Movie_current_framenum = 0;
bool Movie_looping = false;

#ifndef NO_MOVIES

#ifdef WIN32
class MovieSoundBuffer : public ISysSoundBuffer {
private:
  LPDIRECTSOUNDBUFFER m_pBuffer;

public:
  MovieSoundBuffer(LPDIRECTSOUNDBUFFER buffer) : m_pBuffer(buffer) {}

  ////////////////////////////
  // Release
  ////////////////////////////
  // Releases the memory associated with a sound buffer.  This pointer is
  // no longer valid after return.
  //
  // Returns:
  //       -1 : Invalid Parameter
  //        0 : Ok!
  int Release() {
    m_pBuffer->Release();
    delete this;
    return 0;
  }

  //////////////////////////////
  // SetVolume
  //////////////////////////////
  // Sets the volume of a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : Cannot set volume
  //       -2 : Invalid parameters
  int SetVolume(int32_t vol) { return m_pBuffer->SetVolume(vol); }

  ///////////////////////////
  // SetPan
  ///////////////////////////
  // Sets the pan of a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : Cannot set pan
  //       -2 : Invalid parameters
  int SetPan(int32_t pan) { return m_pBuffer->SetPan(pan); }

  /////////////////////////
  // Stop
  /////////////////////////
  // Stops a buffer from playing
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Stop() { return m_pBuffer->Stop(); }

  /////////////////////////
  // Play
  /////////////////////////
  // Starts a buffer playing (or changes the flags for a buffer currently
  // playing).
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Play(uint32_t flags) {
    DWORD dsFlags = (flags & LNXSND_LOOPING) ? DSBPLAY_LOOPING : 0;
    return m_pBuffer->Play(0, 0, dsFlags);
  }

  ////////////////////////////
  // GetCaps
  ////////////////////////////
  // Get the capabilities of a sound buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int GetCaps(SysSoundCaps *caps) {
    DSBCAPS dsCaps;
    dsCaps.dwSize = sizeof(dsCaps);
    int res = m_pBuffer->GetCaps(&dsCaps);
    if (res != 0)
      return res;

    caps->dwBufferBytes = dsCaps.dwBufferBytes;
    caps->dwFlags = dsCaps.dwFlags;
    return 0;
  }

  //////////////////////////////
  // GetStatus
  //////////////////////////////
  // Returns the status of a buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int GetStatus(uint32_t *status) { return m_pBuffer->GetStatus(reinterpret_cast<LPDWORD>(status)); }

  ///////////////////////////////////////
  // GetCurrentPosition
  ///////////////////////////////////////
  // Returns the current play and write positions of the buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int GetCurrentPosition(uint32_t *ppos, uint32_t *wpos) {
    return m_pBuffer->GetCurrentPosition(reinterpret_cast<LPDWORD>(ppos), reinterpret_cast<LPDWORD>(wpos));
  }

  ///////////////////////////////////////
  // SetCurrentPosition
  ///////////////////////////////////////
  // Sets the current play position of the buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int SetCurrentPosition(uint32_t pos) { return m_pBuffer->SetCurrentPosition(pos); }

  /////////////////////////
  // Lock
  /////////////////////////
  // Locks the given buffer, returning pointer(s) to the buffer(s) along with
  // available the size of the buffer(s) for writing.
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Lock(uint32_t pos, uint32_t numbytes, void **ptr1, uint32_t *numbytes1, void **ptr2,
           uint32_t *numbytes2, uint32_t flags) {
    return m_pBuffer->Lock(pos, numbytes, ptr1, reinterpret_cast<LPDWORD>(numbytes1), ptr2,
                           reinterpret_cast<LPDWORD>(numbytes2), flags);
  }

  ///////////////////////////
  // Unlock
  ///////////////////////////
  // Unlocks a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Unlock(void *ptr1, uint32_t num1, void *ptr2, uint32_t num2) {
    return m_pBuffer->Unlock(ptr1, num1, ptr2, num2);
  }
};

class MovieSoundDevice : public ISoundDevice {
private:
  LPDIRECTSOUND m_ds;

public:
  MovieSoundDevice() : m_ds(NULL) {}

  void SetDirectSound(LPDIRECTSOUND ds) { m_ds = ds; }

  LPDIRECTSOUND GetDirectSound() { return m_ds; }

  ///////////////////////////////
  // CreateSoundBuffer
  ///////////////////////////////
  // Creates a sound buffer to be used with mixing and output.
  //
  // Returns:
  //       -1 : Invalid Parameter
  //       -2 : Out of memory
  //        0 : Ok!
  int CreateSoundBuffer(SysSoundBufferDesc *lbdesc, ISysSoundBuffer **lsndb) {
    if (m_ds == NULL)
      return -1;

    DSBUFFERDESC dsBufferDesc;
    dsBufferDesc.dwSize = sizeof(dsBufferDesc);
    dsBufferDesc.dwFlags = lbdesc->dwFlags;
    dsBufferDesc.dwBufferBytes = lbdesc->dwBufferBytes;
    dsBufferDesc.dwReserved = 0;
    dsBufferDesc.lpwfxFormat = reinterpret_cast<LPWAVEFORMATEX>(lbdesc->lpwfxFormat);

    LPDIRECTSOUNDBUFFER dsSndBuffer = NULL;
    int res = m_ds->CreateSoundBuffer(&dsBufferDesc, &dsSndBuffer, NULL);
    if (res != DS_OK) {
      *lsndb = NULL;
      return res;
    }

    *lsndb = new MovieSoundBuffer(dsSndBuffer);
    return res;
  }
};

#else

class MovieSoundBuffer : public ISysSoundBuffer {
private:
  LnxSoundBuffer *m_pBuffer;

public:
  LnxSoundBuffer *GetLnxBuffer() { return m_pBuffer; }
  MovieSoundBuffer(LnxSoundBuffer *buffer) : m_pBuffer(buffer) {}

  ////////////////////////////
  // Release
  ////////////////////////////
  // Releases the memory associated with a sound buffer.  This pointer is
  // no longer valid after return.
  //
  // Returns:
  //       -1 : Invalid Parameter
  //        0 : Ok!
  int Release() {
    return LnxSoundBuffer_Release(m_pBuffer);
    // m_pBuffer->Release();
    delete this;
    return 0;
  }

  //////////////////////////////
  // SetVolume
  //////////////////////////////
  // Sets the volume of a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : Cannot set volume
  //       -2 : Invalid parameters
  int SetVolume(int32_t vol) { return LnxSoundBuffer_SetVolume(m_pBuffer, vol); }

  ///////////////////////////
  // SetPan
  ///////////////////////////
  // Sets the pan of a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : Cannot set pan
  //       -2 : Invalid parameters
  int SetPan(int32_t pan) { return LnxSoundBuffer_SetPan(m_pBuffer, pan); }

  /////////////////////////
  // Stop
  /////////////////////////
  // Stops a buffer from playing
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Stop() { return LnxSoundBuffer_Stop(m_pBuffer); }

  /////////////////////////
  // Play
  /////////////////////////
  // Starts a buffer playing (or changes the flags for a buffer currently
  // playing).
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Play(uint32_t flags) {
    uint32_t dsFlags = (flags & LNXSND_LOOPING) ? LNXSND_LOOPING : 0;
    return LnxSoundBuffer_Play(m_pBuffer, dsFlags);
  }

  ////////////////////////////
  // GetCaps
  ////////////////////////////
  // Get the capabilities of a sound buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int GetCaps(SysSoundCaps *caps) { return LnxSoundBuffer_GetCaps(m_pBuffer, (LinuxSoundCaps *)caps); }

  //////////////////////////////
  // GetStatus
  //////////////////////////////
  // Returns the status of a buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int GetStatus(uint32_t *status) { return LnxSoundBuffer_GetStatus(m_pBuffer, status); }

  ///////////////////////////////////////
  // GetCurrentPosition
  ///////////////////////////////////////
  // Returns the current play and write positions of the buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int GetCurrentPosition(uint32_t *ppos, uint32_t *wpos) {

    return LnxSoundBuffer_GetCurrentPosition(m_pBuffer, ppos, wpos);
  }

  ///////////////////////////////////////
  // SetCurrentPosition
  ///////////////////////////////////////
  // Sets the current play position of the buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int SetCurrentPosition(uint32_t pos) { return LnxSoundBuffer_SetCurrentPosition(m_pBuffer, pos); }

  /////////////////////////
  // Lock
  /////////////////////////
  // Locks the given buffer, returning pointer(s) to the buffer(s) along with
  // available the size of the buffer(s) for writing.
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Lock(uint32_t pos, uint32_t numbytes, void **ptr1, uint32_t *numbytes1, void **ptr2,
           uint32_t *numbytes2, uint32_t flags) {
    return LnxSoundBuffer_Lock(m_pBuffer, pos, numbytes, ptr1, numbytes1, ptr2, numbytes2, flags);
  }

  ///////////////////////////
  // Unlock
  ///////////////////////////
  // Unlocks a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  int Unlock(void *ptr1, uint32_t num1, void *ptr2, uint32_t num2) {
    return LnxSoundBuffer_Unlock(m_pBuffer, ptr1, num1, ptr2, num2);
  }
};
class MovieSoundDevice : public ISoundDevice {
private:
  LnxSoundDevice m_ds;

public:
  MovieSoundDevice() {}

  void SetDirectSound(LnxSoundDevice ds) { m_ds = ds; }

  LnxSoundDevice GetDirectSound() { return m_ds; }

  ///////////////////////////////
  // CreateSoundBuffer
  ///////////////////////////////
  // Creates a sound buffer to be used with mixing and output.
  //
  // Returns:
  //       -1 : Invalid Parameter
  //       -2 : Out of memory
  //        0 : Ok!
  int CreateSoundBuffer(SysSoundBufferDesc *lbdesc, ISysSoundBuffer **lsndb) {
    LnxSoundBuffer *sb = NULL;
    int ret = LnxSound_CreateSoundBuffer(&m_ds, (LnxBufferDesc *)lbdesc, (LnxSoundBuffer **)&sb);
    if (ret == 0) {
      ISysSoundBuffer *p = (ISysSoundBuffer *)new MovieSoundBuffer(sb);
      *lsndb = p;
    } else {
      lsndb = NULL;
    }
    return ret;
  }
};

#endif

#endif
} // namespace

static void *CallbackAlloc(uint32_t size);
static void CallbackFree(void *p);
static uint32_t CallbackFileRead(int hFile, void *pBuffer, uint32_t bufferCount);
static void InitializePalette();
static void CallbackSetPalette(uint8_t *pBuffer, uint32_t start, uint32_t count);
static void CallbackShowFrame(uint8_t *buf, uint32_t bufw, uint32_t bufh, uint32_t sx,
                              uint32_t sy, uint32_t w, uint32_t h, uint32_t dstx, uint32_t dsty,
                              uint32_t hicolor);

#ifndef NO_MOVIES
static bool mve_InitSound(MovieSoundDevice &device);
static void mve_CloseSound(MovieSoundDevice &device);
#endif

// sets the directory where movies are stored
int mve_Init(const char *dir, const char *sndcard) {
#ifndef NO_MOVIES
  strcpy(MovieDir, dir);
  strcpy(SoundCardName, sndcard);
  return MVELIB_NOERROR;
#else
  return MVELIB_INIT_ERROR;
#endif
}

// callback called per frame of playback of movies.
void mve_SetCallback(MovieFrameCallback_fp callBack) {
#ifndef NO_MOVIES
  Movie_callback = callBack;
#endif
}

// used to tell movie library how to render movies.
void mve_SetRenderProperties(int16_t x, int16_t y, int16_t w, int16_t h, renderer_type type, bool hicolor) {}

#ifdef __LINUX__
// locates the case-sensitive movie file name
bool mve_FindMovieFileRealName(const char *movie, char *real_name) {
  // split into directory and file...
  char t_dir[_MAX_PATH];
  char t_file[_MAX_PATH];
  char t_ext[256];
  char t_out[_MAX_PATH];
  ddio_SplitPath(movie, t_dir, t_file, t_ext);
  // pop the extension back on..
  strcat(t_file, t_ext);
  // found a directory?
  if (strlen(t_dir) > 0) {
    // map the bits (or fail)
    if (!cf_FindRealFileNameCaseInsenstive(t_dir, t_file, t_out))
      return false;
    // re-assemble
    ddio_MakePath(real_name, t_dir, t_out, NULL);
  } else {
    // just a file, map that
    if (!cf_FindRealFileNameCaseInsenstive(NULL, t_file, t_out))
      return false;
    // re-assemble
    strcpy(real_name, t_out);
  }
  return true;
}
#endif

// plays a movie using the current screen.
int mve_PlayMovie(const char *pMovieName) {
#ifndef NO_MOVIES
  // first, find that movie..
  char real_name[_MAX_PATH];
#ifdef __LINUX__
  if (!mve_FindMovieFileRealName(pMovieName, real_name)) {
    mprintf(0, "MOVIE: No such file %s\n", pMovieName);
    return MVELIB_FILE_ERROR;
  }
#else
  strcpy(real_name, pMovieName);
#endif
  // open movie file.
  int hFile = open(real_name, O_RDONLY | O_BINARY);
  if (hFile == -1) {
    mprintf(0, "MOVIE: Unable to open %s\n", real_name);
    return MVELIB_FILE_ERROR;
  }

  // determine the movie type
  const char *pExtension = strrchr(pMovieName, '.');
  bool highColor = (pExtension != NULL && stricmp(pExtension, ".mv8") != 0);

  // setup
  MVE_rmFastMode(MVE_RM_NORMAL);
  MVE_sfCallbacks(CallbackShowFrame);
  MVE_memCallbacks(CallbackAlloc, CallbackFree);
  MVE_ioCallbacks(CallbackFileRead);
  MVE_sfSVGA(640, 480, 480, 0, NULL, 0, 0, NULL, highColor ? 1 : 0);
  MVE_palCallbacks(CallbackSetPalette);
  InitializePalette();
  Movie_bm_handle = -1;

  MovieSoundDevice soundDevice;
  if (!mve_InitSound(soundDevice)) {
    mprintf(0, "Failed to initialize sound\n");
    close(hFile);
    return MVELIB_INIT_ERROR;
  }

  int result = MVE_rmPrepMovie(hFile, -1, -1, 0);
  if (result != 0) {
    mprintf(0, "PrepMovie result = %d\n", result);
    close(hFile);
    mve_CloseSound(soundDevice);
    return MVELIB_INIT_ERROR;
  }

  bool aborted = false;
  Movie_current_framenum = 0;
  while ((result = MVE_rmStepMovie()) == 0) {
    // let the OS do its thing
    App()->defer();

    // check for bail
    int key = ddio_KeyInKey();
    if (key == KEY_ESC) {
      aborted = true;
      break;
    }
  }

  // free our bitmap
  if (Movie_bm_handle != -1) {
    bm_FreeBitmap(Movie_bm_handle);
    Movie_bm_handle = -1;
  }

  // close our file handle
  close(hFile);

  // determine the return code
  int err = MVELIB_NOERROR;
  if (aborted) {
    err = MVELIB_PLAYBACK_ABORTED;
  } else if (result != MVE_ERR_EOF) {
    err = MVELIB_PLAYBACK_ERROR;
  }

  // cleanup and shutdown
  MVE_rmEndMovie();
  MVE_ReleaseMem();

  // reset sound
  mve_CloseSound(soundDevice);

  // return out
  return err;
#else
  return MVELIB_INIT_ERROR;
#endif
}

void *CallbackAlloc(uint32_t size) { return mem_malloc(size); }

void CallbackFree(void *p) { mem_free(p); }

uint32_t CallbackFileRead(int hFile, void *pBuffer, uint32_t bufferCount) {
  uint32_t numRead = read(hFile, pBuffer, bufferCount);
  return (numRead == bufferCount) ? 1 : 0;
}

void InitializePalette() {
  for (int i = 0; i < 256; ++i) {
    CurrentPalette[i] = OPAQUE_FLAG | GR_RGB16(0, 0, 0);
  }
}

void CallbackSetPalette(uint8_t *pBuffer, uint32_t start, uint32_t count) {
#ifndef NO_MOVIES
  pBuffer += start * 3;

  for (uint32_t i = 0; i < count; ++i) {
    uint32_t r = pBuffer[0] << 2;
    uint32_t g = pBuffer[1] << 2;
    uint32_t b = pBuffer[2] << 2;
    pBuffer += 3;

    CurrentPalette[start + i] = OPAQUE_FLAG | GR_RGB16(r, g, b);
  }
#endif
}

int NextPow2(int n) {
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;
  return n;
}

#ifndef NO_MOVIES
void BlitToMovieBitmap(uint8_t *buf, uint32_t bufw, uint32_t bufh, uint32_t hicolor,
                       bool usePow2Texture, int &texW, int &texH) {
  // get some sizes
  int drawWidth = hicolor ? (bufw >> 1) : bufw;
  int drawHeight = bufh;

  if (usePow2Texture) {
    int wPow2 = NextPow2(drawWidth);
    int hPow2 = NextPow2(drawHeight);
    int texSize = (wPow2 > hPow2) ? wPow2 : hPow2;
    texW = texSize;
    texH = texSize;
  } else {
    texW = drawWidth;
    texH = drawHeight;
  }

  if (Movie_bm_handle == -1) {
    // Allocate our bitmap
    Movie_bm_handle = bm_AllocBitmap(texW, texH, 0);
  }

  uint16_t *pPixelData = (uint16_t *)bm_data(Movie_bm_handle, 0);
  GameBitmaps[Movie_bm_handle].flags |= BF_CHANGED;
  if (hicolor) {
    uint16_t *wBuf = (uint16_t *)buf;
    for (int y = 0; y < drawHeight; ++y) {
      for (int x = 0; x < drawWidth; ++x) {
        uint16_t col16 = *wBuf++;
        uint32_t b = ((col16 >> 11) & 0x1F) << 3;
        uint32_t g = ((col16 >> 5) & 0x3F) << 2;
        uint32_t r = ((col16 >> 0) & 0x1F) << 3;
        pPixelData[x] = OPAQUE_FLAG | GR_RGB16(r, g, b);
      }

      pPixelData += texW;
    }
  } else {
    for (int y = 0; y < drawHeight; ++y) {
      for (int x = 0; x < drawWidth; ++x) {
        uint8_t palIndex = *buf++;
        pPixelData[x] = CurrentPalette[palIndex];
      }

      pPixelData += texW;
    }
  }
}

void CallbackShowFrame(uint8_t *buf, uint32_t bufw, uint32_t bufh, uint32_t sx, uint32_t sy,
                       uint32_t w, uint32_t h, uint32_t dstx, uint32_t dsty, uint32_t hicolor) {
  // prepare our bitmap
  int texW, texH;
  BlitToMovieBitmap(buf, bufw, bufh, hicolor, true, texW, texH);

  // calculate UVs from texture
  int drawWidth = hicolor ? (bufw >> 1) : bufw;
  int drawHeight = bufh;
  float u = float(drawWidth - 1) / float(texW - 1);
  float v = float(drawHeight - 1) / float(texH - 1);

  StartFrame(0, 0, 640, 480, false);

  rend_ClearScreen(GR_BLACK);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetAlphaValue(255);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetWrapType(WT_CLAMP);
  rend_SetFiltering(0);
  rend_SetZBufferState(0);
  rend_DrawScaledBitmap(dstx, dsty, dstx + drawWidth, dsty + drawHeight, Movie_bm_handle, 0.0f, 0.0f, u, v);
  rend_SetFiltering(1);
  rend_SetZBufferState(1);

  // call our callback
  if (Movie_callback != NULL) {
    Movie_callback(dstx, dsty, Movie_current_framenum);
  }
  ++Movie_current_framenum;

  EndFrame();

  rend_Flip();
}
#endif

intptr_t mve_SequenceStart(const char *mvename, int *fhandle, bool looping) {
#ifndef NO_MOVIES

  // first, find that movie..
  char real_name[_MAX_PATH];
#ifdef __LINUX__
  if (!mve_FindMovieFileRealName(mvename, real_name)) {
    mprintf(0, "MOVIE: No such file %s\n", mvename);
    *fhandle = -1;
    return 0;
  }
#else
  strcpy(real_name, mvename);
#endif
  int hfile = open(real_name, O_RDONLY | O_BINARY);

  if (hfile == -1) {
    mprintf(1, "MOVIE: Unable to open %s\n", real_name);
    *fhandle = -1;
    return 0;
  }

  // setup
  MVE_rmFastMode(MVE_RM_NORMAL);
  MVE_memCallbacks(CallbackAlloc, CallbackFree);
  MVE_ioCallbacks(CallbackFileRead);
  InitializePalette();
  Movie_bm_handle = -1;
  Movie_looping = looping;

  // let the render know we will be copying bitmaps to framebuffer (or something)
  rend_SetFrameBufferCopyState(true);

  *fhandle = hfile;
  return (intptr_t)MVE_frOpen(CallbackFileRead, hfile, NULL);
#else
  return 0;
#endif
}

intptr_t mve_SequenceFrame(intptr_t handle, int fhandle, bool sequence, int *bm_handle) {
#ifndef NO_MOVIES
  if (bm_handle) {
    *bm_handle = -1;
  }

  if (handle == -1) {
    return -1;
  }

  static unsigned sw = 0, sh = 0, hicolor = 0;
  int err = 0;

reread_frame:

  // get the next frame of data
  uint8_t *pBuffer = NULL;
  err = MVE_frGet((MVE_frStream)handle, &pBuffer, &sw, &sh, &hicolor);

  // refresh our palette
  {
    uint32_t palstart = 0;
    uint32_t palcount = 0;
    uint8_t *pal = NULL;
    MVE_frPal((MVE_frStream)handle, &pal, &palstart, &palcount);
    CallbackSetPalette(pal, palstart, palcount);
  }

  if (err == 0) {
    // blit to bitmap
    int texW, texH;
    BlitToMovieBitmap(pBuffer, sw, sh, hicolor, false, texW, texH);

    if (bm_handle) {
      *bm_handle = Movie_bm_handle;
    }

    return handle;
  }

  if (Movie_looping && err == MVE_ERR_EOF) {
    MVE_frClose((MVE_frStream)handle);
#ifdef WIN32
    _lseek(fhandle, 0, SEEK_SET);
#else
    lseek(fhandle, 0, SEEK_SET);
#endif
    handle = (intptr_t)MVE_frOpen(CallbackFileRead, fhandle, NULL);
    sequence = true;
    goto reread_frame;
  }

  return -1;
#else
  return -1;
#endif
}

bool mve_SequenceClose(intptr_t hMovie, int hFile) {
#ifndef NO_MOVIES
  if (hMovie == -1)
    return false;

  MVE_frClose((MVE_frStream)hMovie);
  MVE_ReleaseMem();
  close(hFile);

  // free our bitmap
  if (Movie_bm_handle != -1) {
    bm_FreeBitmap(Movie_bm_handle);
    Movie_bm_handle = -1;
  }

  // We're no longer needing this
  rend_SetFrameBufferCopyState(false);

  return true;
#else
  return false;
#endif
}

void mve_Puts(int16_t x, int16_t y, ddgr_color col, const char *txt) {
  grtext_SetFont(BRIEFING_FONT);
  grtext_SetColor(col);
  grtext_SetAlpha(255);
  grtext_SetFlags(GRTEXTFLAG_SHADOW);
  grtext_CenteredPrintf(0, y, txt);
  grtext_Flush();
}

void mve_ClearRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  // Note: I can not figure out how to clear, and then write over it with text. It always covers my text!
  // rend_FillRect( GR_BLACK, x1, y1, x2, y2 );
}

#ifndef NO_MOVIES
#ifdef WIN32
// Internal function to enumerate sound devices
BOOL CALLBACK DSEnumCallback(LPGUID lp_guid, LPCSTR lpstr_description, LPCSTR lpstr_module, LPVOID lp_Context) {
  GUID FAR *lp_ret_guid = (GUID FAR *)lp_Context;

  if (SoundCardName[0]) {
    if (strcmp(lpstr_description, SoundCardName) == 0) {
      if (lp_guid) {
        memmove(lp_ret_guid, lp_guid, sizeof(GUID));
      }

      return FALSE;
    }
  }

  return TRUE;
}

bool mve_InitSound(MovieSoundDevice &device) {
  //	Perform Direct Sound Initialization
  device.SetDirectSound(NULL);

  GUID *pguid = NULL;
  GUID card_guid, zero_card_guid;
  ZeroMemory(&card_guid, sizeof(GUID));
  ZeroMemory(&zero_card_guid, sizeof(GUID));
  HRESULT hr = DirectSoundEnumerate(DSEnumCallback, &card_guid);
  if (hr == DS_OK) {
    if (memcmp(&card_guid, &zero_card_guid, sizeof(GUID)) != 0) {
      pguid = &card_guid;
    }
  }

  LPDIRECTSOUND lpDS;
  if (DirectSoundCreate(pguid, &lpDS, NULL) != DS_OK) {
    return false;
  }

  HWND hWnd = Win32App()->windowHandle();;
  hr = lpDS->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
  if (hr != DS_OK) {
    lpDS->Release();
    return false;
  }

  bool use_22k_sound = false;

  //	Start Mixer
  LPDIRECTSOUNDBUFFER lpPrimaryBuffer;
  DSBUFFERDESC dsbd;
  memset(&dsbd, 0, sizeof(DSBUFFERDESC));
  dsbd.dwSize = sizeof(DSBUFFERDESC);
  dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
  hr = lpDS->CreateSoundBuffer(&dsbd, &lpPrimaryBuffer, NULL);
  if (hr == DS_OK) {
    // set format to 44khz if requested.
    WAVEFORMATEX fmt;
    fmt.cbSize = sizeof(fmt);
    fmt.wFormatTag = WAVE_FORMAT_PCM;
    fmt.nChannels = 2;
    fmt.wBitsPerSample = 16;
    fmt.nSamplesPerSec = use_22k_sound ? 22050 : 44100;
    fmt.nBlockAlign = fmt.nChannels * (fmt.wBitsPerSample / 8);
    fmt.nAvgBytesPerSec = ((DWORD)fmt.nSamplesPerSec) * ((DWORD)fmt.nBlockAlign);
    hr = lpPrimaryBuffer->SetFormat(&fmt);
    if (hr != DS_OK) {
      lpPrimaryBuffer->Release();
      lpDS->Release();
      lpDS = NULL;
      return false;
    }

    hr = lpPrimaryBuffer->Play(0, 0, DSBPLAY_LOOPING);
    if (hr != DS_OK) {
      lpPrimaryBuffer->Release();
      lpDS->Release();
      return false;
    }

    lpPrimaryBuffer->Release();
  } else {
    lpDS->Release();
    return false;
  }

  device.SetDirectSound(lpDS);
  MVE_sndInit(&device);

  return true;
}

void mve_CloseSound(MovieSoundDevice &device) {
  LPDIRECTSOUND ds = device.GetDirectSound();
  if (ds) {
    ds->Release();
    device.SetDirectSound(NULL);
  }
}
#else
bool mve_InitSound(MovieSoundDevice &device) {

  LnxSoundDevice snddev;
  bool use_22k_sound = false;
  snddev.freq = use_22k_sound ? 22050 : 44100;
  snddev.bit_depth = 16;
  snddev.channels = 2;
  snddev.bps = snddev.freq * snddev.channels * snddev.bit_depth / 8;

  device.SetDirectSound(snddev);

  MVE_sndInit(&device);

  return true;
}

void mve_CloseSound(MovieSoundDevice &device) {
  // TODO: close the driver out
}
#endif

#endif
