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

 * $Logfile: /DescentIII/main/credits.cpp $
 * $Revision: 17 $
 * $Date: 10/05/99 3:00p $
 * $Author: Kevin $
 *
 * Credits system
 *
 * $Log: /DescentIII/main/credits.cpp $
 *
 * 17    10/05/99 3:00p Kevin
 * No longer display static credits for demo
 *
 * 16    5/13/99 6:41p Samir
 * don't reset mouse when ending credits.  causes problems.
 *
 * 15    5/08/99 1:43p Jason
 * made credits scroll a little faster
 *
 * 14    5/05/99 7:38p Jason
 * added scrolling credits system
 *
 * 13    5/02/99 12:08a Jason
 * changes to credits
 *
 * 12    4/30/99 5:42p Jason
 * more updates to credits system
 *
 * 11    4/29/99 11:57a Samir
 * added music.
 *
 * 10    4/19/99 12:46p Jason
 * fixed credits
 *
 * 9     4/17/99 3:29p Jason
 * first pass at credit system
 *
 * 8     4/15/99 2:32p Kevin
 * Added some code for the Demo
 *
 * 7     4/14/99 4:19a Jeff
 * more case mismatch fixes in #includes
 *
 * 6     4/13/99 12:24p Jason
 * made credits warp faster
 *
 * 5     4/02/99 5:47p Jeff
 * text effect in
 *
 * 4     4/02/99 6:03a Jeff
 * testing a new text effect...not done yet
 *
 * 3     3/31/99 3:04p Jeff
 * added _real_ temporary credits system...
 *
 * 2     3/31/99 12:11p Jeff
 * added empty credits file
 *
 * $NoKeywords: $
 */

#include "mono.h"
#include "pstypes.h"
#include "ddio.h"
#include "grtext.h"
#include "renderer.h"
#include "gamefont.h"
#include "game.h"
#include "bitmap.h"
#include "descent.h"
#include "mem.h"
#include "3d.h"
#include "musicapi.h"
#include "hlsoundlib.h"
#include <string.h>
#include <math.h>
#include "psrand.h"

#if defined(__LINUX__)
#include "linux_fix.h"
#endif

/*
$$TABLE_GAMEFILE "GameCredits.txt"
$$TABLE_GAMEFILE "credits.omf"
*/

// music regions for credits
#define CREDITS1_MUSIC_REGION 0

// other stuff
#define CLTYPE_HEADING 0
#define CLTYPE_TEXT 1
#define CLTYPE_END 2
#define CLTYPE_BLANK 3

struct creditline {
  ddgr_color color;
  uint8_t type;
  char *text;
  creditline *next;
  uint16_t startx, starty, endx, endy;
  float displaytime;
};

static void Credits_Render(creditline *, float);
static creditline Creditlines;

static ddgr_color CreditTextColor, CreditHeadingColor;
static int CreditStartX, CreditStartY, CreditEndX, CreditEndY;
static float CreditDisplayTime;
static chunked_bitmap Credits_bm;

#define MAX_CREDIT_LEN 200

static bool Credits_IsKeyPressed(void) {
  if (ddio_KeyInKey())
    return true;

  return false;
}

// Parses a credit line
// Returns 1 if new text was read, else 0
static int Credits_ParseLine(char *line, creditline *credit) {
  int line_len = strlen(line);
  int new_text = 0;

  if (line_len < 1) {
    ASSERT(credit->next == NULL);
    ASSERT(credit->text == NULL);

    credit->text = NULL;

    credit->type = CLTYPE_BLANK;
    new_text = 1;

  } else if (line[0] == ';') // Comment
    return 0;
  else if (line[0] == '*') // Movement data
  {
    int x1, x2, y1, y2;
    float timedelay;

    int num_found = sscanf(line, "*%d %d %d %d %f", &x1, &y1, &x2, &y2, &timedelay);
    if (num_found != 5) {
      mprintf(0, "Bad movement data in credit text (%s)\n", line);
      return 0;
    } else {
      CreditStartX = x1;
      CreditStartY = y1;
      CreditEndX = x2;
      CreditEndY = y2;
      CreditDisplayTime = timedelay;
    }

  } else if (line[0] == '!') // Heading
  {
    ASSERT(credit->next == NULL);
    ASSERT(credit->text == NULL);

    credit->text = (char *)mem_malloc(line_len + 1);
    ASSERT(credit->text);

    strcpy(credit->text, &line[1]);
    credit->startx = CreditStartX;
    credit->starty = CreditStartY;
    credit->endx = CreditEndX;
    credit->endy = CreditEndY;
    credit->displaytime = CreditDisplayTime;
    mprintf(0, "Read header %s\n", line);

    credit->color = CreditHeadingColor;
    credit->type = CLTYPE_HEADING;
    new_text = 1;

  } else if (line[0] == '$') // text color
  {
    int r, g, b;
    int num_found = sscanf(line, "$%d %d %d", &r, &g, &b);
    if (num_found != 3) {
      mprintf(0, "Bad color in credit text (%s)\n", line);
      return 0;
    } else {
      CreditTextColor = GR_RGB(r, g, b);
    }

  } else if (line[0] == '^') // heading color
  {
    int r, g, b;
    int num_found = sscanf(line, "^%d %d %d", &r, &g, &b);
    if (num_found != 3) {
      mprintf(0, "Bad color in credit text (%s)\n", line);
      return 0;
    } else {
      CreditHeadingColor = GR_RGB(r, g, b);
    }

  } else {
    ASSERT(credit->next == NULL);
    ASSERT(credit->text == NULL);

    if (!strnicmp("Jason Leighton", line, 14) && (ps_rand() % 100) == 0) {
      strcat(line, " (Hi mom!)");
      line_len += 10;
    }

    credit->text = (char *)mem_malloc(line_len + 1);
    ASSERT(credit->text);

    strcpy(credit->text, line);
    credit->color = CreditTextColor;
    credit->type = CLTYPE_TEXT;
    // mprintf(0,"Read textline %s\n",line);
    new_text = 1;
  }

  return new_text;
}

// Given a filename, attempts to load that filename as credit text
static bool Credits_LoadCredits(const char *filename) {
  CFILE *infile;
  char curline[MAX_CREDIT_LEN];

  // Reset our data
  CreditTextColor = GR_RGB(0, 128, 255);
  CreditHeadingColor = GR_RGB(255, 255, 255);
  CreditStartX = CreditEndX = 320;
  CreditStartY = CreditEndY = 50;
  CreditDisplayTime = 10;

  creditline *cur_credit = &Creditlines;
  Creditlines.next = NULL;
  Creditlines.text = NULL;

  // Open the file, bail on failure
  infile = cfopen(filename, "rt");

  if (!infile) {
    mprintf(0, "Couldn't open credit file to read credits!\n");
    return false;
  }

  for (int i = 0; i < 27; i++) {
    // Generate blank lines for the start
    cur_credit->text = NULL;
    cur_credit->type = CLTYPE_BLANK;
    cur_credit->next = (creditline *)mem_malloc(sizeof(creditline));
    ASSERT(cur_credit->next);
    cur_credit = cur_credit->next;
    cur_credit->next = NULL;
    cur_credit->text = NULL;
  }

  // Read in each line of the credit file, allocing memory and putting it into a correct category
  int done = 0;
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }

    // Read a line and parse it
    cf_ReadString(curline, MAX_CREDIT_LEN, infile);
    // mprintf(0,"Read string %s\n",curline);

    if (!strnicmp("END", curline, 3)) {
      done = 1;
      continue;
    }

    if (Credits_ParseLine(curline, cur_credit)) {
      // Make a new line
      cur_credit->next = (creditline *)mem_malloc(sizeof(creditline));
      ASSERT(cur_credit->next);
      cur_credit = cur_credit->next;
      cur_credit->next = NULL;
      cur_credit->text = NULL;
    }
  }

  cur_credit->type = CLTYPE_END;

  cfclose(infile);
  return true;
}

extern void ShowStaticScreen(char *bitmap_filename, bool timed = false, float delay_time = 0.0f);

#define CREDIT_PIXELS_PER_SECOND 22

void Credits_Display(void) {
#ifdef DEMO
  // ShowStaticScreen("democredits1.ogf");
  // ShowStaticScreen("democredits2.ogf");
  // return;
#else
  // Load background image
  int bm_handle = bm_AllocLoadFileBitmap("CreditsBackground.tga", 0);

  if (bm_handle < 0) {
    mprintf(0, "Failed to load background credit screen!\n");
    return;
  }

  if (!bm_CreateChunkedBitmap(bm_handle, &Credits_bm)) {
    Error("Failed to slice up credits screen!");
  }

  bm_FreeBitmap(bm_handle);

  // start up the music
  D3MusicStart("credits.omf");
  D3MusicSetRegion(CREDITS1_MUSIC_REGION);

  mprintf(0, "Chillin in credits\n");

  // Load our credits
  if (!Credits_LoadCredits("GameCredits.txt")) {
    mprintf(0, "There was an error loading game credits!\n");
  } else {
    // First count how many headers there are so we know how many to allocate
    int count = 0;
    int done = 0;
    creditline *credit = &Creditlines;

    while (!done) {
      if (credit->type != CLTYPE_END)
        count++;
      credit = credit->next;
      if (!credit || credit->type == CLTYPE_END)
        done = 1;
    }

    int font_height = grfont_GetHeight(BIG_BRIEFING_FONT);
    int total_pixel_height = font_height * count;

    int cur_line = 0;
    float total_pixel_count = 0;
    float cur_pixel_count = 0;
    float last_time = timer_GetTime();

    // Now show these guys
    done = 0;
    credit = &Creditlines;
    while (cur_line < count) {
      StartFrame(0, 0, Game_window_w, Game_window_h);
      rend_DrawChunkedBitmap(&Credits_bm, 0, 0, 255);
      Credits_Render(credit, cur_pixel_count);
      EndFrame();
      rend_Flip();

      float frametime = timer_GetTime() - last_time;
      last_time = timer_GetTime();

      cur_pixel_count += frametime * CREDIT_PIXELS_PER_SECOND;

      while (cur_pixel_count >= font_height) {
        credit = credit->next;
        cur_line++;
        if (credit == NULL || credit->type == CLTYPE_END) {
          cur_pixel_count = -1;
          cur_line = count;
        } else {
          cur_pixel_count -= font_height;
        }
      }

      // Player music for this frame
      tMusicSeqInfo music_info;
      Sound_system.BeginSoundFrame(false);
      music_info.frametime = frametime;
      music_info.player_dead = false;
      music_info.started_level = false;
      D3MusicDoFrame(&music_info);
      Sound_system.EndSoundFrame();

      // Check for keys
      App()->defer();
      if (Credits_IsKeyPressed()) {
        cur_line = count;
      }
    }
  }

  // Free credit text memory
  creditline *cur_credit = &Creditlines;
  while (cur_credit) {
    if (cur_credit->text)
      mem_free(cur_credit->text);

    creditline *next_credit = cur_credit->next;

    if (cur_credit != &Creditlines) {
      mem_free(cur_credit);
    }

    cur_credit = next_credit;
  }

  // Free bitmaps
  bm_DestroyChunkedBitmap(&Credits_bm);

  // end the music.
  D3MusicStop();
  ddio_KeyFlush();
//	ddio_MouseReset();				// -mouse shouldn't be reset.   ui system gets hosed
// unfortunately under NT.
#endif
}

void Credits_Render(creditline *header, float pixels_in) {
  bool done = false;
  creditline *credit = header;

  grtext_Reset();
  grtext_SetFont(BIG_BRIEFING_FONT);
  grtext_SetFontScale(1.0);
  int text_height = grfont_GetHeight(BIG_BRIEFING_FONT);

  float pixels_this_frame = 0;
  int cur_pixel = -pixels_in;
  int cur_line = 0;
  while ((pixels_this_frame < 480 + text_height) && !done) {
    if (credit->type == CLTYPE_BLANK) {
      credit = credit->next;
      cur_line++;

      pixels_this_frame += text_height;
      cur_pixel += text_height;

      if (credit == NULL)
        done = 1;
      else if (credit->type == CLTYPE_END)
        done = 1;

      continue;
    }
    grtext_SetColor(credit->color);

    // Figure out alpha
    if (cur_pixel < 0) {
      float norm = 1.0 - ((-cur_pixel) / (float)text_height);
      grtext_SetAlpha(norm * 255);
    } else if ((cur_pixel + text_height) > 480) {
      float norm = 1.0 - (((cur_pixel + text_height) - 480) / (float)text_height);
      grtext_SetAlpha(norm * 255);
    } else
      grtext_SetAlpha(255);

    // Figure out text placement
    int texty = cur_pixel;

    grtext_CenteredPrintf(0, texty, "%s", credit->text);

    credit = credit->next;

    if (credit == NULL)
      done = 1;
    else if (credit->type == CLTYPE_END)
      done = 1;

    cur_line++;
    pixels_this_frame += text_height;
    cur_pixel += text_height;
  }

  grtext_Flush();
}
