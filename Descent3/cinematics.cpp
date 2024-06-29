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

#include "cinematics.h"
#include "movie.h"
#include "game.h"
#include "ddio.h"
#include "descent.h"
#include "gamefont.h"
#include "hlsoundlib.h"
#include "subtitles.h"
#include "dedicated_server.h"
#include "appdatabase.h"
#include "bitmap.h"

#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
static struct {
  float last_frame_time;
  float frame_interval_time;
  float fps;
} MovieCallbackData;
#endif

static bool Cinematic_lib_init = false;
static int Cinematic_x = 0, Cinematic_y = 0, Cinematic_w = 0, Cinematic_h = 0;

static void CinematicCallback(int mve_x, int mve_y, int frame_num);

///////////////////////////////////////////////////////////////////////////////
//	functions

bool InitCinematics() {
  if (Dedicated_server) {
    Cinematic_lib_init = false;
    return true;
  }

  char path[_MAX_PATH];
  ddio_MakePath(path, Base_directory, "movies", NULL);

  if (mve_Init(path, Sound_card_name) != MVELIB_NOERROR)
    return false;

  mve_SetCallback(CinematicCallback);

  Cinematic_lib_init = true;

  return true;
}

void SetMovieProperties(int x, int y, int w, int h, renderer_type type) {
  const bool kHiColorEnabled = true;
  Cinematic_x = x;
  Cinematic_y = y;
  Cinematic_w = w;
  Cinematic_h = h;
  mve_SetRenderProperties(x, y, w, h, type, kHiColorEnabled);
}

bool PlayMovie(const std::filesystem::path &moviename) {
  if (!Cinematic_lib_init)
    return false;

  // get in the right directory
  std::filesystem::path filename = moviename;
  // check extension
  std::filesystem::path extension = moviename.extension();
  if (stricmp(extension.u8string().c_str(), ".mve") != 0 && stricmp(extension.u8string().c_str(), ".mv8") != 0) {
    // we need an extension
    filename.replace_extension(extension.u8string() + ".mve");
  }

  // shutdown sound.
  bool sound_sys_active = Sound_system.IsActive();
  if (sound_sys_active) {
    Sound_system.KillSoundLib(false);
  }

  //	start movie.
#ifdef DEBUG
  MovieCallbackData.last_frame_time = timer_GetTime();
  MovieCallbackData.frame_interval_time = 1.0f;
  MovieCallbackData.fps = 0.0f;
#endif

  // Initializes the subtitles for a given movie file
  SubtInitSubtitles(moviename);

  SetMovieProperties(0, 0, Max_window_w, Max_window_h, Renderer_type);

  int mveerr = mve_PlayMovie(filename.u8string().c_str(), Descent);

  // Shutdown the subtitle system
  SubtCloseSubtitles();

  bool retval = true;
  if (mveerr != MVELIB_NOERROR) {
    mprintf(1, "Movie error %d.\n", mveerr);
    retval = false;
  }

  //	startup D3 sound.
  if (sound_sys_active) {
    Sound_system.InitSoundLib(Descent, Sound_mixer, Sound_quality, false);
  }

  return retval;
}

tCinematic *StartMovie(const char *moviename, bool looping) {
  if (!Cinematic_lib_init)
    return NULL;

  // get in the right directory
  char filename[_MAX_PATH];
  strncpy(filename, moviename, sizeof(filename) - 1);
  filename[sizeof(filename) - 1] = 0;

  // check extension
  const char *extension = strrchr(filename, '.');
  if (extension == NULL || (stricmp(extension, ".mve") != 0 && stricmp(extension, ".mv8") != 0)) {
    // we need an extension
    strncat(filename, ".mve", sizeof(filename) - strlen(filename) - 1);
    filename[sizeof(filename) - 1] = 0;
  }

  SetMovieProperties(0, 0, Max_window_w, Max_window_h, Renderer_type);

  int filehandle;
  intptr_t hMovie = mve_SequenceStart(filename, &filehandle, Descent, looping);
  if (hMovie == 0)
    return NULL;

  tCinematic *mve = new tCinematic;
  mve->mvehandle = hMovie;
  mve->filehandle = filehandle;
  mve->frame_chunk.bm_array = NULL;
  return mve;
}

bool FrameMovie(tCinematic *mve, int x, int y, bool sequence) {
  if (!Cinematic_lib_init || mve == NULL)
    return false;

  int bm_handle;
  intptr_t hNewMovie = mve_SequenceFrame(mve->mvehandle, mve->filehandle, sequence, &bm_handle);
  if (hNewMovie != -1) {
    // we must have looped, we have a new handle
    mve->mvehandle = hNewMovie;
  }

  //	do chunk conversion and blt if absolutely necessary.
  if (bm_handle > -1) {
    if (x == -1) {
      x = (Cinematic_w - bm_w(bm_handle, 0)) / 2;
    }

    if (y == -1) {
      y = (Cinematic_h - bm_h(bm_handle, 0)) / 2;
    }

    rend_SetAlphaType(AT_ALWAYS);
    rend_CopyBitmapToFramebuffer(bm_handle, x, y);
  }

  return (hNewMovie != -1);
}

void EndMovie(tCinematic *mve) {
  if (mve == NULL || !Cinematic_lib_init)
    return;

  mve_SequenceClose(mve->mvehandle, mve->filehandle);

  if (mve->frame_chunk.bm_array) {
    bm_DestroyChunkedBitmap(&mve->frame_chunk);
  }

  delete mve;
}

void CinematicCallback(int mveX, int mveY, int frameNum) { SubtDrawSubtitles(frameNum); }
