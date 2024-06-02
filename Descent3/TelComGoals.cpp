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

 * $Logfile: /DescentIII/main/TelComGoals.cpp $
 * $Revision: 17 $
 * $Date: 4/20/99 1:45a $
 * $Author: Matt $
 *
 * TelCom Goal Status screen
 *
 * $Log: /DescentIII/main/TelComGoals.cpp $
 *
 * 17    4/20/99 1:45a Matt
 * Fixed a dereferencing bug that was causing this screen to use totally
 * different fonts than the code intended.  It now uses the two briefing
 * fonts.
 *
 * 16    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 15    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 14    4/05/99 3:28p Jeff
 * failed mission added to telcom goal screen
 *
 * 13    4/02/99 9:24p Jeff
 * fixed tooltip detection
 *
 * 12    3/31/99 5:34p Jeff
 * fixed 0 byte malloc
 *
 * 11    3/27/99 2:59p Jeff
 * handle multiple line goals...tooltips don't go off screen now
 *
 * 10    3/24/99 3:01p Jeff
 * fixed 0 byte malloc
 *
 * 9     2/27/99 2:48p Jeff
 * adjust to bottom right corner of mouse pointer (tool tips)
 *
 * 7     2/26/99 5:01p Jeff
 * added background screen and some new artwork
 *
 * 6     2/26/99 12:07a Jeff
 * fixed up tooltip stuff
 *
 * 5     2/24/99 9:39p Jeff
 * updated
 *
 * 4     2/21/99 9:06p Jeff
 * fixed bug where nothing would display on the screen if there were
 * goals, but none are enabled or viewable by telcom
 *
 * 3     2/20/99 9:22p Jeff
 * finished telcom level goals screen.  Made it so if you go into the
 * telcom from the game it goes to main menu instead of briefings.
 *
 * 2     2/20/99 4:37p Jeff
 * added telcomgoals
 *
 * 1     2/20/99 4:31p Jeff
 *
 * $NoKeywords: $
 */

#include "TelComGoals.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cfile.h"
#include "pserror.h"
#include "ddio.h"
#include "bitmap.h"

#include "TelCom.h"
#include "renderer.h"
#include "game.h"
#include "mem.h"
#include "stringtable.h"
#include "textaux.h"
#include "TelComEfxStructs.h"
#include "TelComEffects.h"
#include "levelgoal.h"
#include "textaux.h"
#include "Mission.h"
#include "hlsoundlib.h"

#include <algorithm>

#define TITLE_X 30 + TGminx
#define VALUE_X 400 + TGminx
int TGminx, TGmaxx, TGminy, TGmaxy;
#define SM_FONT BRIEFING_FONT
#define BG_FONT BIG_BRIEFING_FONT

#define UI_RIGHT_ARROW_CHAR 26

struct tGoalLineInfo {
  bool primary;
  bool is_objective;
  bool is_active;
  int goal_index;
  int lx, rx, ty, by; // bounding box
};

static tGoalLineInfo *TG_Lines;
static int TG_NumLines;
static int *TG_SortedList;
static int TG_CurrObjectiveArrow;

struct tToolTipData {
  int w, h;
};

static tToolTipData TG_TT_dest;
static tToolTipData TG_TT_curr;
static chunked_bitmap TG_Tooltipbitmap;
static int TG_MouseOffset_x = -1, TG_MouseOffset_y = -1;
// returns true if left < right
bool TG_compare_slots(int left, int right) {
  int left_index, right_index;
  int left_priority, right_priority;
  char left_list, right_list;

  left_index = TG_Lines[left].goal_index;
  right_index = TG_Lines[right].goal_index;

  // Primaries have precedence over secondaries
  if (TG_Lines[left].primary && !TG_Lines[right].primary)
    return false; // right is a secondary, left is a primary
  if (!TG_Lines[left].primary && TG_Lines[right].primary)
    return true; // right is a primary, left is secondary

  Level_goals.GoalPriority(left_index, LO_GET_SPECIFIED, &left_priority);
  Level_goals.GoalPriority(right_index, LO_GET_SPECIFIED, &right_priority);
  Level_goals.GoalGoalList(left_index, LO_GET_SPECIFIED, &left_list);
  Level_goals.GoalGoalList(right_index, LO_GET_SPECIFIED, &right_list);

  // check goal list...the lower has priority
  if (left_list < right_list)
    return false;
  if (right_list < left_list)
    return true;

  // the have same goal list, if it's an object, then that has priority, else sort by
  // goal priority
  if (TG_Lines[left].is_objective)
    return false;
  if (TG_Lines[right].is_objective)
    return true;

  // they are both goals, and not objectives, check based on priority
  return (left_priority > right_priority);
}

void TCGoalsBuildLineData(void) {
  int number_of_goals = Level_goals.GetNumGoals();
  int index, goal_status, count = 0, i;

  // see how many of these are something we want
  for (index = 0; index < number_of_goals; index++) {
    Level_goals.GoalStatus(index, LO_GET_SPECIFIED, &goal_status);

    if (goal_status & LGF_ENABLED)
      count++;
  }

  //'count' goals are what we have to display
  // allocate memory needed and start filling in
  if (count) {
    TG_Lines = (tGoalLineInfo *)mem_malloc(sizeof(tGoalLineInfo) * count);
    TG_NumLines = count;
    TG_SortedList = (int *)mem_malloc(sizeof(int) * count);
    if (!TG_SortedList || !TG_Lines) {
      // out of memory
      Telcom_system.current_status = TS_OFF;
      return;
    }

    // fill in data
    i = 0;
    for (index = 0; index < number_of_goals; index++) {
      Level_goals.GoalStatus(index, LO_GET_SPECIFIED, &goal_status);

      if (goal_status & LGF_ENABLED) {
        TG_Lines[i].goal_index = index;
        TG_Lines[i].is_active = false;

        // Is this a primary or secondary goal?
        if (goal_status & LGF_SECONDARY_GOAL) {
          TG_Lines[i].primary = false;
        } else {
          TG_Lines[i].primary = true;
        }

        if (goal_status & LGF_TELCOM_LISTS) {
          TG_Lines[i].is_objective = true;
        } else {
          TG_Lines[i].is_objective = false;
        }

        // initialize x/y values to -1, that way they will be filled in when drawn first
        // frame.
        TG_Lines[i].lx = TG_Lines[i].rx = TG_Lines[i].ty = TG_Lines[i].by = -1;

        i++;
      }
    }

    // Determine which goals are active
    int num_active, act_g_index;
    num_active = Level_goals.GetNumActivePrimaryGoals();
    for (i = 0; i < num_active; i++) {
      act_g_index = Level_goals.GetActivePrimaryGoal(i);

      // search for that index
      for (index = 0; index < TG_NumLines; index++) {
        if (act_g_index == TG_Lines[index].goal_index) {
          TG_Lines[index].is_active = true;
          break;
        }
      }
    }
    num_active = Level_goals.GetNumActiveSecondaryGoals();
    for (i = 0; i < num_active; i++) {
      act_g_index = Level_goals.GetActiveSecondaryGoal(i);

      // search for that index
      for (index = 0; index < TG_NumLines; index++) {
        if (act_g_index == TG_Lines[index].goal_index) {
          TG_Lines[index].is_active = true;
          break;
        }
      }
    }

    // All data has been filled in, now sort it all
    int t, j;
    for (i = 0; i < TG_NumLines; i++) {
      TG_SortedList[i] = i;
    }

    for (i = 1; i <= TG_NumLines - 1; i++) {
      t = TG_SortedList[i];

      // Shift elements down until
      // insertion point found.
      for (j = i - 1; j >= 0 && TG_compare_slots(TG_SortedList[j], t); j--) {
        TG_SortedList[j + 1] = TG_SortedList[j];
      }
      // insert
      TG_SortedList[j + 1] = t;
    }
  } else {
    TG_Lines = NULL;
    TG_NumLines = 0;
    TG_SortedList = NULL;
  }
}

int FindHighlightedItem(int x, int y) {
  for (int i = 0; i < TG_NumLines; i++) {
    if (x >= TG_Lines[i].lx && x <= TG_Lines[i].rx && y >= TG_Lines[i].ty && y <= TG_Lines[i].by) {
      return TG_Lines[i].goal_index;
    }
  }
  return -1;
}

#define ACTIVE_ALPHA_PER_SEC 255.0f
#define ACTIVE_ALPHA_MIN 100.0f
#define ACTIVE_ALPHA_MAX 255.0f

#define COLOR_OBJECTIVE_HEADING GR_WHITE
#define COLOR_OBJECTIVE_NAME GR_RGB(255, 255, 40)
#define COLOR_GOAL_NAME GR_WHITE
#define COLOR_COMPLETED GR_RGB(40, 255, 40)
#define COLOR_INCOMPLETE GR_RGB(255, 40, 40)
#define COLOR_FAILED GR_RGB(255, 255, 40)

void TCGoalsRenderCallback(void) {
  static bool active_alpha_in = false;
  static float active_alpha = ACTIVE_ALPHA_MAX;

  // recalculate alpha
  float alpha_change = last_frametime * ACTIVE_ALPHA_PER_SEC;
  float alpha_amount;
  while (alpha_change > 0) {
    if (active_alpha_in) {
      alpha_amount = std::min(ACTIVE_ALPHA_MAX - active_alpha, alpha_change);
      active_alpha += alpha_amount;

      if (active_alpha > (ACTIVE_ALPHA_MAX - 1.0f))
        active_alpha_in = false;
    } else {
      alpha_amount = std::min(alpha_change, active_alpha - ACTIVE_ALPHA_MIN);
      active_alpha -= alpha_amount;

      if (active_alpha < (ACTIVE_ALPHA_MIN + 1.0f))
        active_alpha_in = true;
    }
    alpha_change -= alpha_amount;
  }

  int old_font = grtext_GetFont();

  grtext_SetAlpha(255);
  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetZBufferState(0);
  rend_SetAlphaType(AT_CONSTANT + AT_TEXTURE);
  rend_SetAlphaValue(255);
  rend_SetZBufferState(0);

  int y = TGminy;

  int obj_x, obj_max_width, goal_x, goal_max_width, status_x, status_max_width;
  obj_x = TGminx + 25;
  obj_max_width = 315;
  status_x = obj_x + obj_max_width;
  status_max_width = TGmaxx - status_x;
  goal_x = obj_x + 20;
  goal_max_width = status_x - goal_x;
  /*
  int goal_name_x,goal_status_x,goal_name_max_width,goal_status_max_width;
  goal_name_x = TGminx + 20;
  goal_name_max_width = 320;
  goal_status_x = goal_name_x + goal_name_max_width;
  goal_status_max_width = TGmaxx-goal_status_x;
  */

  int period_length;
  period_length = grfont_GetCharWidth(SM_FONT, '.') + Grtext_spacing;

  //@@@ASSERT(goal_status_max_width>0);
  ASSERT(status_max_width > 0);

  int big_height = grfont_GetHeight(BG_FONT);
  int small_height = grfont_GetHeight(SM_FONT);

  grtext_SetAlpha(255);
  grtext_SetColor(GR_WHITE);

  // render here
  // grtext_SetFont(BRIEFING_FONT);
  //@@@int number_of_goals = Level_goals.GetNumGoals();
  int goal_index;
  int goal_status, i, width, x;
  bool first_primary, first_secondary;
  first_primary = first_secondary = true;

#define GOAL_NAME_BUFFER_SIZE 256
#define BUFFER_SIZE GOAL_NAME_BUFFER_SIZE * 4
  char buffer[BUFFER_SIZE];

  // Print out Heading
  char level_string[32];
  snprintf(level_string, sizeof(level_string), TXT_LEVELSTRING, Current_mission.cur_level);
  grtext_SetFont(BG_FONT);
  grtext_SetColor(GR_RGB(255, 255, 255));
  int level_name_x = TGmaxx - grtext_GetTextLineWidth(level_string) - 15;
  grtext_Printf(level_name_x, y, level_string);
  if (!Level_info.name[0]) {
    grtext_Printf(TGminx + 15, y, TXT_UNNAMED);
  } else {
    grtext_Printf(TGminx + 15, y, Level_info.name);
  }
  y += (big_height + 15);

  for (i = 0; i < TG_NumLines; i++) {
    goal_index = TG_SortedList[i];
    grtext_SetAlpha(255);

    // Print out heading
    if (TG_Lines[goal_index].primary) {
      if (first_primary) {
        // this is the first primary goal, print out heading
        grtext_SetFont(BG_FONT);
        grtext_SetColor(COLOR_OBJECTIVE_HEADING);
        grtext_Printf(TGminx + 15, y, TXT_PRIMGOALS);
        y += (big_height + 1);
        first_primary = false;
      }
    } else {
      if (first_secondary) {
        if (!first_primary)
          y += 10;

        // this is the first secondary goal, print out heading
        grtext_SetFont(BG_FONT);
        grtext_SetColor(COLOR_OBJECTIVE_HEADING);
        grtext_Printf(TGminx + 15, y, TXT_SECONDARYGOALS);
        y += (big_height + 1);
        first_secondary = false;
      }
    }

    grtext_SetFont(SM_FONT);

    // determine x position
    if (TG_Lines[goal_index].is_objective) {
      x = obj_x;
      width = obj_max_width;
    } else {
      x = goal_x;
      width = goal_max_width;
    }

    // get the name of our goal
    Level_goals.GoalGetName(TG_Lines[goal_index].goal_index, buffer, GOAL_NAME_BUFFER_SIZE);

    // clip goal_name to our max width
    //@@textaux_ClipString(width,buffer,1.0,UI_RIGHT_ARROW_CHAR);
    if (TG_Lines[goal_index].is_objective) {
      grtext_SetColor(COLOR_OBJECTIVE_NAME);
    } else {
      grtext_SetColor(COLOR_GOAL_NAME);
    }
    //@@grtext_Printf(x,y,buffer);
    char wrap_buffer[BUFFER_SIZE];
    textaux_WordWrap(buffer, wrap_buffer, width, SM_FONT);
    const char *nextline;
    char linebuffer[256];
    int wrap_y = y;

    nextline = textaux_CopyTextLine(wrap_buffer, linebuffer);
    while ((nextline) && ((y + small_height + 2) < TGmaxy)) {
      grtext_Printf(x, y, linebuffer);
      y += (small_height + 2);
      nextline = textaux_CopyTextLine(nextline, linebuffer);
    }
    grtext_Printf(x, y, linebuffer);

    // see if we need to fill in x/y coords
    if (TG_Lines[goal_index].lx == -1) {
      TG_Lines[goal_index].lx = x;
      TG_Lines[goal_index].rx = status_x + status_max_width;
      TG_Lines[goal_index].ty = wrap_y;
      TG_Lines[goal_index].by = y + small_height;
    }

    // fill with '.' until the start of the next column
    int end_x = x + grtext_GetTextLineWidth(linebuffer) + Grtext_spacing;
    // move end_x to mod period_length
    while ((end_x % period_length) != 0) {
      end_x++;
    }

    int length_to_fill = ((status_x - (end_x + 10)) / period_length) * period_length;
    int index = 0;
    while (length_to_fill > period_length && index < (BUFFER_SIZE - 1)) {
      buffer[index] = '.';
      index++;
      length_to_fill -= period_length;
    }
    buffer[index] = '\0';
    grtext_SetColor(GR_WHITE);
    grtext_Printf(end_x, y, buffer);

    if (TG_Lines[goal_index].is_active) {

      if (TG_CurrObjectiveArrow > BAD_BITMAP_HANDLE) {
        rend_SetAlphaType(AT_CONSTANT_TEXTURE);
        rend_SetAlphaValue(active_alpha);
        rend_SetLighting(LS_NONE);
        rend_SetColorModel(CM_MONO);
        rend_SetOverlayType(OT_NONE);
        rend_SetWrapType(WT_CLAMP);
        rend_SetFiltering(0);

        rend_DrawScaledBitmap(x - small_height - 2, wrap_y, x - 2, wrap_y + small_height, TG_CurrObjectiveArrow, 0, 0,
                              1, 1);

        rend_SetAlphaValue(255.0);
        rend_SetFiltering(1);
      } else {
        uint8_t alpha_to_use;
        alpha_to_use = (uint8_t)active_alpha;
        grtext_SetAlpha(alpha_to_use);
      }
    }

    // get the status of the goal
    Level_goals.GoalStatus(TG_Lines[goal_index].goal_index, LO_GET_SPECIFIED, &goal_status);
    if (goal_status & LGF_COMPLETED) {
      // completed goal
      grtext_SetColor(COLOR_COMPLETED);
      grtext_Printf(status_x, y, TXT_COMPLETED);
    } else if (goal_status & LGF_FAILED) {
      // failed goal
      grtext_SetColor(COLOR_FAILED);
      grtext_Printf(status_x, y, TXT_FAILED);
    } else {
      // not completed
      grtext_SetColor(COLOR_INCOMPLETE);
      grtext_Printf(status_x, y, TXT_NOTCOMPLETEDYET);
    }

    y += (small_height + 2);
  }

  if ((TG_NumLines <= 0) || (first_primary && first_secondary)) {
    // no goals for this level
    grtext_SetFont(BG_FONT);

    y = TGminy + ((TGmaxy - TGminy) / 2) - (grfont_GetHeight(BG_FONT) / 2);
    grtext_CenteredPrintf(0, y, TXT_NOGOALSAVAIL);
  }

  grtext_Flush();

  // Display tooltip box
  int mouse_x, mouse_y;
  ddio_MouseGetState(&mouse_x, &mouse_y, NULL, NULL);
  int index = FindHighlightedItem(mouse_x, mouse_y);
  char desc_buffer[1024], s_desc_buffer[1024], *ptr;
  ptr = desc_buffer;
  *ptr = '\0';

  if (index != -1) {
#define MIN_TOOLTIP_WIDTH 100
#define MAX_TOOLTIP_WIDTH 300
#define MIN_TOOLTIP_HEIGHT 40
    // we're over an item

    Level_goals.GoalGetDesc(index, desc_buffer, 1024);
    while (*ptr && (*ptr == ' ' || *ptr == '\t'))
      ptr++;
    if (strlen(ptr) > 0) {
      int width = grtext_GetTextLineWidth(ptr);

      if (width > MAX_TOOLTIP_WIDTH)
        width = MAX_TOOLTIP_WIDTH;
      textaux_WordWrap(ptr, s_desc_buffer, width - 45, SM_FONT);

      int num_lines = 0;
      char *dptr = s_desc_buffer;
      while (*dptr) {
        if (*dptr == '\n')
          num_lines++;
        dptr++;
      }
      num_lines++;
      ptr = s_desc_buffer;

      // figure out true width
      const char *next_line = textaux_CopyTextLine(ptr, desc_buffer);
      width = grtext_GetTextLineWidth(desc_buffer);
      int t;
      while (next_line) {
        next_line = textaux_CopyTextLine(next_line, desc_buffer);
        t = grtext_GetTextLineWidth(desc_buffer);
        if (t > width)
          width = t;
      }

      TG_TT_dest.w = width + 20;
      TG_TT_dest.h = 10 + (num_lines * small_height);
    } else {
      memset(&TG_TT_dest, 0, sizeof(tToolTipData)); // start shrinking
    }
  } else {
    memset(&TG_TT_dest, 0, sizeof(tToolTipData)); // start shrinking
  }

#define TOOLTIP_SPEED 400.0f

  // adjust box
  if (TG_TT_curr.w > TG_TT_dest.w) {
    // shrinking
    TG_TT_curr.w -= std::min(TG_TT_curr.w - TG_TT_dest.w, (int)(TOOLTIP_SPEED * last_frametime));
  } else {
    // enlarging
    TG_TT_curr.w += std::min(TG_TT_dest.w - TG_TT_curr.w, (int)(TOOLTIP_SPEED * last_frametime));
  }

  if (TG_TT_curr.h > TG_TT_dest.h) {
    // shrinking
    TG_TT_curr.h -= std::min(TG_TT_curr.h - TG_TT_dest.h, (int)(TOOLTIP_SPEED * last_frametime));
  } else {
    // enlarging
    TG_TT_curr.h += std::min(TG_TT_dest.h - TG_TT_curr.h, (int)(TOOLTIP_SPEED * last_frametime));
  }

  // rend_SetAlphaType (AT_CONSTANT_TEXTURE);
  // rend_SetAlphaValue (200.0);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetWrapType(WT_CLAMP);
  rend_SetFiltering(0);

  if (TG_MouseOffset_x == -1) {
    // determine bottom-right x/y of mouse cursor
    uint16_t *data = bm_data(TC_cursor, 0);
    int width = bm_w(TC_cursor, 0);
    int index = width * bm_h(TC_cursor, 0) - 1;
    while (index > 0 && (!(data[index] & OPAQUE_FLAG)))
      index--;

    TG_MouseOffset_x = index % width;
    TG_MouseOffset_y = index / width;
  }

  // Adjust X box if it is to far to the right
  if (mouse_x + TG_TT_curr.w > Telcom_system.Monitor_coords[MONITOR_MAIN].right ||
      mouse_x + TG_TT_dest.w > Telcom_system.Monitor_coords[MONITOR_MAIN].right) {
    // we must adjust
    mouse_x -= TG_TT_curr.w;
  }

  rend_DrawScaledChunkedBitmap(&TG_Tooltipbitmap, mouse_x + TG_MouseOffset_x, mouse_y + TG_MouseOffset_y, TG_TT_curr.w,
                               TG_TT_curr.h, 255);
  rend_SetFiltering(1);

  if (TG_TT_curr.w != 0 && TG_TT_curr.h != 0) {
    // See if we need to draw any text
    // only when curr==dest
    if (TG_TT_curr.w == TG_TT_dest.w && TG_TT_curr.h == TG_TT_dest.h) {
      // write text description
      grtext_SetAlpha(255);
      grtext_SetColor(GR_WHITE);
      grtext_SetFont(SM_FONT);

      const char *next_line;
      int c_x, c_y;
      c_x = mouse_x + TG_MouseOffset_x + 10;
      c_y = mouse_y + TG_MouseOffset_y + 5;

      next_line = textaux_CopyTextLine(ptr, desc_buffer);
      while (next_line) {
        grtext_Printf(c_x, c_y, desc_buffer);
        next_line = textaux_CopyTextLine(next_line, desc_buffer);
        c_y += small_height;
      }
      grtext_Printf(c_x, c_y, desc_buffer);
      grtext_Flush();
    }
  }

  grtext_SetFont(old_font);
  rend_SetZBufferState(1);
}

// This is the function called by TelCom
//  return true if TelCom should exit to TelCom Main Menu
//  return false if you should exit out of TelCom completly
bool TelComGoalStatus(tTelComInfo *tcs) {
  bool done = false;

  TelcomStartScreen(0);

  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;
  CreateBackgroundEffect(&backg, MONITOR_MAIN, 0);
  CreateBackgroundEffect(&backg, MONITOR_TOP, 0);

  TCBMPDESC bmpdesc;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  bmpdesc.caps = TCBD_XY;
  bmpdesc.x = 0;
  bmpdesc.y = 0;
  strcpy(bmpdesc.filename, "TelcomGoalBkg.ogf");
  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, 0);
  /*
  $$TABLE_GAMEFILE "TelcomGoalBkg.ogf"
  */

  TGminx = tcs->Monitor_coords[MONITOR_MAIN].left + 10;
  TGminy = tcs->Monitor_coords[MONITOR_MAIN].top + 10;
  TGmaxy = tcs->Monitor_coords[MONITOR_MAIN].bottom - 10;
  TGmaxx = tcs->Monitor_coords[MONITOR_MAIN].right - 10;
  TG_Lines = NULL;
  TG_SortedList = NULL;
  TG_NumLines = 0;
  memset(&TG_TT_dest, 0, sizeof(tToolTipData));
  memset(&TG_TT_curr, 0, sizeof(tToolTipData));

  int bm_handle = bm_AllocLoadFileBitmap("TelcomToolTip.ogf", 0);
  if (bm_handle <= BAD_BITMAP_HANDLE) {
    bm_handle = bm_AllocBitmap(32, 32, 0);
    if (bm_handle > BAD_BITMAP_HANDLE) {
      uint16_t *data = bm_data(bm_handle, 0);
      for (int i = 0; i < 1024; i++) {
        data[i] = GR_RGB16(0, 0, 0) | OPAQUE_FLAG;
      }
    }
  }

  bm_CreateChunkedBitmap(bm_handle, &TG_Tooltipbitmap);

  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_STATIC;
  textdesc.font = BG_FONT;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_FONT;
  textdesc.textbox.left = 0;
  textdesc.textbox.right = 380;
  textdesc.textbox.top = 4;
  textdesc.textbox.bottom = 50;
  textdesc.color = GR_RGB(255, 255, 255);

  CreateTextEffect(&textdesc, TXT_GOALSTATUSHEADING, MONITOR_TOP, 0);
  TelcomEndScreen();
  TelcomRenderSetScreen(0);

  TelcomRenderSetCallback(TCGoalsRenderCallback);

  TCGoalsBuildLineData();

  TG_CurrObjectiveArrow = bm_AllocLoadFileBitmap("CurrObjectiveArrow.ogf", 0);

  while (!done) {
    Sound_system.BeginSoundFrame(Telcom_called_from_game);

    if (tcs->state != TCS_POWERON || tcs->current_status != TS_GOALS) {
      // we're done with the loop
      done = true;
    }

    // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
    TelComHandleAllEvents(&Telcom_system);

    TelcomRenderScreen();
    Descent->defer();
    if (KEY_STATE(KEY_ESC))
      Telcom_system.state = TCS_POWEROFF;

    Sound_system.EndSoundFrame();
  }

  DestroyAllScreens();
  TelcomRenderSetScreen(DUMMY_SCREEN);
  TelcomRenderSetCallback(NULL);

  if (TG_Lines) {
    mem_free(TG_Lines);
    TG_Lines = NULL;
  }
  if (TG_SortedList) {
    mem_free(TG_SortedList);
    TG_SortedList = NULL;
  }
  TG_NumLines = 0;

  if (TG_CurrObjectiveArrow > BAD_BITMAP_HANDLE)
    bm_FreeBitmap(TG_CurrObjectiveArrow);

  bm_DestroyChunkedBitmap(&TG_Tooltipbitmap);

  return true;
}
