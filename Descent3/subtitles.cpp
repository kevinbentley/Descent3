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

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/main/subtitles.cpp $
 * $Revision: 7 $
 * $Date: 5/06/99 1:20a $
 * $Author: Samir $
 *
 * Subtitle system for cinematics
 *
 * $Log: /DescentIII/main/subtitles.cpp $
 *
 * 7     5/06/99 1:20a Samir
 * use mve_ calls for subtitles.
 *
 * 6     4/20/99 12:48a Matt
 * Made subtitles use briefing font instead of HUD font, even though I
 * know the subtitles don't actually work.
 *
 * 5     4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 4     10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 3     8/29/98 6:53p Jeff
 * only do subtitles if -subtitles is given on command line
 *
 * 2     8/28/98 4:20p Jeff
 * got subtitles completly working
 *
 * $NoKeywords: $
 */

#include "subtitles.h"
// #include "gamefont.h"
// #include "grtext.h"
// #include "renderer.h"
#include "pserror.h"
#include "ddio.h"
// #include "ddvid.h"
#include "manage.h"
#include "application.h"
#include "mem.h"
#include "movie.h"
#include "args.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Subtitle data
struct subtitle {
  int first_frame, last_frame;
  char *msg;
};

#define MAX_SUBTITLES 500
#define MOVIE_SUBTITLE_EXTENSION ".msb"
#define MESSAGE_LENGTH 300

static subtitle Subtitles[MAX_SUBTITLES];
int Num_subtitles;
int Movie_subtitle_init;

// Prints out a subtitle on the screen, centered, at y pos y, with color color.
void PrintSubTitle(int y, ddgr_color color, char *msg);
// Parses a subtitle file
void SubtParseSubtitles(CFILE *file);
// clears the area where subtitle text is display (call once a frame)
void ClearSubTitleArea(void);
// Resets the subtitle information
void SubtResetSubTitles(void);

void readline(CFILE *file, char *buf, int maxsize) {
  ASSERT(file);
  ASSERT(buf);
  buf[0] = '\0';
  bool done = false;
  while (!done) {
    if (cfeof(file)) {
      done = true;
      buf[0] = '\0';
    }
    if (cf_ReadString(buf, maxsize, file))
      done = true;
  }
}

char *parse_whitespace(char *p) {
  ASSERT(p);
  while (isspace(*p))
    p++;
  return p;
}

char *parse_int(char *buf, int *d) {
  ASSERT(buf);
  ASSERT(d);
  char *t;
  bool got_digit = 0;
  t = buf = parse_whitespace(buf);

  // Check for negative sign
  if (*t == '-')
    t++;

  // Check for valid characters in number
  while (isdigit(*t)) {
    t++;
    got_digit = 1;
  }

  // Make sure at least one digit
  if (!got_digit) {
    *d = 0;
    return NULL;
  }

  // Check for valid seperator, and convert
  if ((*t == 0) || isspace(*t) || (*t == ',')) { // valid number
    *d = atoi(buf);
    return t;
  } else {
    return NULL;
  }
}

char *parse_token(char *p, const char *token) {
  ASSERT(p);
  ASSERT(token);

  int len = strlen(token);
  if (!strnicmp(p, token, len)) {
    return p + len;
  }

  return NULL;
}

#define PARSE_NEXT_LINE()                                                                                              \
  do {                                                                                                                 \
    readline(file, buf, MESSAGE_LENGTH);                                                                               \
    p = buf;                                                                                                           \
  } while (0)

// Parses a subtitle file
void SubtParseSubtitles(CFILE *file) {
  SubtResetSubTitles();

  int first_frame, last_frame;
  char buf[MESSAGE_LENGTH];
  char *p = buf;

  PARSE_NEXT_LINE();

  while (!parse_token(buf, "#End")) {
    ASSERT(Num_subtitles < MAX_SUBTITLES);

    // starting frame number
    p = parse_int(p, &first_frame);
    if (!p) {
      mprintf(0, "Couldn't parse first_frame\n");
      goto subt_parse_error;
    }

    p = parse_int(p, &last_frame);
    if (!p) {
      mprintf(0, "Couldn't parse last_frame\n");
      goto subt_parse_error;
    }

    p = parse_whitespace(p);

    Subtitles[Num_subtitles].first_frame = first_frame;
    Subtitles[Num_subtitles].last_frame = last_frame;
    Subtitles[Num_subtitles].msg = (char *)mem_malloc(strlen(p) + 1);
    if (!Subtitles[Num_subtitles].msg)
      goto subt_parse_error;
    strcpy(Subtitles[Num_subtitles].msg, p); // be sure to free this later

    Num_subtitles++;

    PARSE_NEXT_LINE();
  }
  return;
subt_parse_error:
  mprintf(0, "Error Parsing SubTitle File!\n");
  SubtResetSubTitles();
}

// Resets the subtitle information
void SubtResetSubTitles(void) {
  for (int i = 0; i < Num_subtitles; i++) {
    if (Subtitles[i].msg)
      mem_free(Subtitles[i].msg);
    Subtitles[i].msg = NULL;
  }
  Num_subtitles = 0;
  Movie_subtitle_init = 1;
}

// Initializes the subtitles for a given movie file
void SubtInitSubtitles(const std::filesystem::path &filename) {
  // Load the subtitles
  Num_subtitles = 0;
  Movie_subtitle_init = 0;

  // need a quick out here if no subtitles.
  if (!FindArg("-subtitles"))
    return;

  std::filesystem::path subtitle_path = std::filesystem::path(LocalArtDir) / "movies" / filename;
  subtitle_path.replace_extension(MOVIE_SUBTITLE_EXTENSION);

  mprintf(0, "Looking for the subtitle file %s\n", subtitle_path.u8string().c_str());

  CFILE *ifile = cfopen(subtitle_path, "rt");
  if (!ifile) {
    mprintf(0, "Movie: Couldn't find subtitle file %s\n", subtitle_path.u8string().c_str());
    return;
  }

  SubtResetSubTitles();
  SubtParseSubtitles(ifile);
  cfclose(ifile);
}

// Shutsdown the subtitle system
void SubtCloseSubtitles() { SubtResetSubTitles(); }

#define MAX_ACTIVE_SUBTITLES 3

// draw the subtitles for this frame
void SubtDrawSubtitles(int frame_num) {
  static int active_subtitles[MAX_ACTIVE_SUBTITLES];
  static int num_active_subtitles, next_subtitle, line_spacing;
  int t, y, fh;
  int must_erase = 0;

  if (Movie_subtitle_init) {
    num_active_subtitles = 0;
    next_subtitle = 0;
    fh = 12;
    line_spacing = fh + (fh >> 2);
    Movie_subtitle_init = 0;
  }

  // get rid of any subtitles that have expired
  for (t = 0; t < num_active_subtitles;) {
    if (frame_num > Subtitles[active_subtitles[t]].last_frame) {
      int t2;
      for (t2 = t; t2 < num_active_subtitles - 1; t2++)
        active_subtitles[t2] = active_subtitles[t2 + 1];
      num_active_subtitles--;
      must_erase = 1;
    } else
      t++;
  }

  // get any subtitles new for this frame
  while ((next_subtitle < Num_subtitles) && (frame_num >= Subtitles[next_subtitle].first_frame)) {
    if (num_active_subtitles >= MAX_ACTIVE_SUBTITLES)
      Error("Too many active subtitles!");
    active_subtitles[num_active_subtitles++] = next_subtitle;
    next_subtitle++;
  }

  ClearSubTitleArea();

  // find y coordinate for first line of subtitles
  y = 480 - ((line_spacing + 1) * MAX_ACTIVE_SUBTITLES + 2);
  int first, last;

  for (t = 0; t < num_active_subtitles; t++) {
    if (active_subtitles[t] != -1) {
      first = Subtitles[active_subtitles[t]].first_frame;
      last = Subtitles[active_subtitles[t]].last_frame;
      PrintSubTitle(y, ((first <= frame_num) && (last >= frame_num)) ? GR_RGB(255, 255, 255) : GR_RGB(128, 128, 128),
                    Subtitles[active_subtitles[t]].msg);
      y += line_spacing + 1;
    }
  }
}

// Prints out a subtitle on the screen, centered, at y pos y, with color color.
void PrintSubTitle(int y, ddgr_color color, char *msg) { mve_Puts(-1, y, color, msg); }

// clears the area where subtitle text is display (call once a frame)
void ClearSubTitleArea(void) {
  int fh = 12;
  int line_spacing = fh + (fh >> 2);
  int y = 475 - ((line_spacing + 1) * MAX_ACTIVE_SUBTITLES + 2);

  mve_ClearRect(0, y, 639, 479);
}
