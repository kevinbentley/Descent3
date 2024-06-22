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

 * $Logfile: /DescentIII/main/screens.cpp $
 * $Revision: 52 $
 * $Date: 10/21/99 9:29p $
 * $Author: Jeff $
 *
 *
 *
 * $Log: /DescentIII/main/screens.cpp $
 *
 * 52    10/21/99 9:29p Jeff
 * B.A. Macintosh code merge
 *
 * 51    5/24/99 4:16a Jeff
 * fixed screenshot bug for multiplayer
 *
 * 50    5/23/99 7:22p Samir
 * flush keyboard and mouse when entering screen!
 *
 * 49    5/23/99 3:53a Samir
 * fixed printscreen.
 *
 * 47    5/20/99 6:14p Kevin
 * fixed mouse button to close PLR
 *
 * 46    5/11/99 6:33p Kevin
 * fixed problem with sound being played as 3d and view position not being
 * equal to the player position! Doh
 *
 * 45    5/07/99 5:38p Jeff
 * use new multiplayer plr screen
 *
 * 44    5/07/99 2:51p Jason
 * fixed a bunch of endlevel multiplayer issues
 *
 * 43    5/05/99 7:46p Kevin
 * Fixed some post level results things
 *
 * 42    5/02/99 5:30p Kevin
 * fixed shield and energy ratings.
 *
 * 41    4/30/99 3:03p Kevin
 * improved times restored count
 *
 * 40    4/26/99 11:34a Samir
 * wrap startframe and endframe around plrresults UI callback.
 *
 * 39    4/23/99 1:56a Matt
 * Added system for counting kills of friendly objects
 *
 * 38    4/21/99 4:49p Kevin
 *
 * 37    4/20/99 8:58p Jeff
 * included joystick.h so it compiles in Linux
 *
 * 36    4/20/99 2:34p Kevin
 * multiplayer post level results will automatically go to the next level
 * after 30 seconds so the client doesn't timeout in the reliable code.
 * This number should never be higher than the timeout for the reliable
 * networking code in networking.cpp (currently 2 minutes)
 *
 * 35    4/20/99 2:00p Kevin
 * Improved post level results screens
 *
 * 34    4/20/99 12:45a Matt
 * Use briefing font instead of HUD font for post-level results screen.
 *
 * 33    4/18/99 2:48p Kevin
 * lock PLR at 30 fps
 *
 * 32    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 31    4/07/99 12:41p Kevin
 * New strings
 *
 * 30    4/07/99 12:31p Matt
 * Added code for failed missions.
 *
 * 29    4/07/99 11:31a Kevin
 * Added success/failure to Post level results
 *
 * 28    4/06/99 6:02p Matt
 * Added score system
 *
 * 27    3/28/99 4:11p Kevin
 * Fixed compiler warning
 *
 * 26    3/23/99 5:04p Kevin
 * Post level results stuff.
 *
 * 25    3/23/99 12:33p Kevin
 * More post level results improvements
 *
 * 24    3/22/99 7:02p Kevin
 * New post level results screens.... not done.
 *
 * 23    3/09/99 6:36p Samir
 * space bar to quit
 *
 * 22    2/15/99 9:17p Jeff
 * table parse for plr screens
 *
 * 21    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 20    10/22/98 10:50a Samir
 * only register kill for robots so accuracy rating can be closer.
 *
 * 19    10/18/98 12:15p Jeff
 * set multi_bail_ui_menu to false when starting PLR screen, else it bails
 * immediatly
 *
 * 18    10/17/98 7:26p Samir
 * destroy window after closing.
 *
 * 17    10/14/98 1:02p Jason
 * fixed FindSoundName issues
 *
 * 16    10/07/98 12:08p Samir
 * took out buttons.
 *
 * 15    10/02/98 5:46p Samir
 * took out mission file objective text and replaced with level goals.
 *
 * 14    9/15/98 5:44p Jason
 * more work on dedicated server
 *
 * 13    9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 12    6/17/98 3:27p Jeff
 * Changes made for localization
 *
 * 11    6/16/98 10:54a Jeff
 *
 * 10    6/11/98 1:56p Jeff
 * use d3m files instead of dll
 *
 * 9     6/10/98 2:08p Samir
 * multiplayer screens loaded.
 *
 * 8     5/25/98 8:19p Samir
 * Added E3 speed demo to pass through screens.
 *
 * 7     5/15/98 2:22p Jeff
 * Sets default colors for Post level results screen
 *
 * 6     5/14/98 5:27p Jason
 * fixed some more sequencing bugs
 *
 * 5     5/14/98 3:18p Jason
 * finished multiplayer sequencing issues
 *
 * 4     5/11/98 7:45p Samir
 * hopefully fixed some flash in bugs.
 *
 * 3     4/18/98 7:18a Samir
 * added level objectives text to result screen.
 *
 * 2     4/18/98 2:08a Samir
 * update.
 *
 * 1     4/14/98 8:18p Samir
 * initial revision.
 *
 * $NoKeywords: $
 */

#include "screens.h"
#include "newui.h"
#include "game.h"
#include "ddio.h"
#include "descent.h"
#include "application.h"
#include "gamefont.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "player.h"
#include "Mission.h"
#include "game2dll.h"
#include "stringtable.h"
#include "dedicated_server.h"
#include "levelgoal.h"
#include "sounds.h"
#include "pilot.h"
#include "joystick.h"

#define LVLRES_FADEIN_TIME 0.50f
#define TEXT_REDRAW_COUNT 6.0f
#define LVLRES_STATS 7

/*
$$TABLE_GAMEFILE "mplvlr1.ogf"
$$TABLE_GAMEFILE "lvlres0.ogf"
$$TABLE_GAMEFILE "mplvlr2.ogf"
$$TABLE_GAMEFILE "lvlres1.ogf"
$$TABLE_GAMEFILE "mplvlr3.ogf"
$$TABLE_GAMEFILE "lvlres2.ogf"
*/
#define BACKGROUND_VIS 0
#define OVERLAY_VIS 1

static int Stat_ratings[] = {TXI_SCRNNONE, TXI_SCRNFEEBLE,    TXI_SCRNPOOR,   TXI_SCRNAVG,
                             TXI_SCRNGOOD, TXI_SCRNEXCELLENT, TXI_SCRNSUPREME};

static struct {
  int state;
  float state_time, this_frame_time, last_frame_time;

  tLargeBitmap first_back;
  tLargeBitmap glow_back;
  tLargeBitmap shade_back;

  struct {
    tLargeBitmap *bmp;
  } vis_list[2];

  int16_t time_min, time_sec;
  float shield_rating, energy_rating;
  float accuracy_rating;
} PLR;

void PLResultsFrame();
void PLResultsText(float draw_mag);
void PLResultsVisFrame();
const char *GetNormalizedRating(float mag);
void PaintPLRSinglePlayerText();
void SinglePlayerPostLevelResults();

static tLargeBitmap level_bmp;
bool background_loaded = false;
bool PLR_success = true;

void PLResultsFrame() {
  StartFrame(0, 0, Max_window_w, Max_window_h);
  Sound_system.BeginSoundFrame(false);
  // Right now we don't want you to do anything
  if (background_loaded)
    DrawLargeBitmap(&level_bmp, 0, 0, 1.0f);
  // Call the DLL so it can do it's thing
  if (Game_mode & GM_MULTI) {
    CallGameDLL(EVT_CLIENT_GAMEPOSTLEVELRESULTS, &DLLInfo);
  } else {
    // Draw the text here
    PaintPLRSinglePlayerText();
  }
  grtext_Flush();
  Sound_system.EndSoundFrame();
  EndFrame();
}

float paint_start = 0.0f;
#define MAX_PLR_LINES 20
bool val_printed[MAX_PLR_LINES];

int paint_in_sound_id = -1;
int paint_in_sound_handle = -1;
int chunk_sound_id = -1;

#define MAX_PLR_FPS_TIME .033
extern void DoScreenshot();
bool PostLevelResults(bool success) {
  PLR_success = success;

  if (Dedicated_server)
    return true;

  paint_in_sound_id = FindSoundName("PPR paint in");
  chunk_sound_id = FindSoundName("PPR chunk");

  float timelast = timer_GetTime();

  int old_mode = GetScreenMode();
  SetScreenMode(SM_MENU);
  SetUICallback(PLResultsFrame);
  ui_HideCursor();
  ddio_KeyFlush();
  ddio_MouseQueueFlush();

  // Do the multiplayer stuff
  if (Game_mode & GM_MULTI) {
    // Draw the background
    if (!LoadLargeBitmap("mplvlr.ogf", &level_bmp))
      Error("Unable to load %s.", "mplvlr.ogf");
    else
      background_loaded = true;

    // Play a sound
    Sound_system.Play2dSound(SOUND_LIGHTNING);

    float start_time = timer_GetTime();
    float time_to_wait;

    if (Netgame.local_role == LR_SERVER)
      time_to_wait = 10;
    else
      time_to_wait = 15;

    while ((timer_GetTime() - start_time) < time_to_wait) {
      Multi_bail_ui_menu = 0;
      App()->defer();
      DoUIFrame();
      rend_Flip();
      GetUIFrameResult();
    }

    int keypressed = ddio_KeyInKey();
    if (keypressed == KEY_PRINT_SCREEN) {
      DoScreenshot();
    }
    ddio_KeyFlush();
  } else {
    // Do the single player stuff
    if (!background_loaded) {
      if (LoadLargeBitmap("multimain.ogf", &level_bmp)) {
        background_loaded = true;
      }
      SinglePlayerPostLevelResults();
      float start_time = timer_GetTime();
      float time_to_wait = 2;

      while ((timer_GetTime() - start_time) < time_to_wait) {
        while ((timer_GetTime() - timelast) < MAX_PLR_FPS_TIME) {
          App()->delay(0);
        }
        timelast = timer_GetTime();

        App()->defer();
        DoUIFrame();
        rend_Flip();
        GetUIFrameResult();
      }
    }
  }

  bool rval = true;
  float max_wait_time = 10;
  float start_time = timer_GetTime();
  // Wait for input and move on
  while (Netgame.local_role != LR_SERVER) {
    if (Game_mode & GM_MULTI) {
      if ((timer_GetTime() - start_time) > max_wait_time) {
        break;
      }
    }
    while ((timer_GetTime() - timelast) < MAX_PLR_FPS_TIME) {
      App()->delay(0);
    }
    timelast = timer_GetTime();

    Multi_bail_ui_menu = 0;
    App()->defer();
    int x, y, dx, dy;
    if (ddio_MouseGetState(&x, &y, &dx, &dy)) {
      rval = true;
      break;
    }

    DoUIFrame();
    rend_Flip();
    GetUIFrameResult();

    int key = ddio_KeyInKey();

    tJoyPos jp;
    joy_GetPos((tJoystick)JOYSTICK_1, &jp);
    if (jp.buttons) {
      rval = true;
      break;
    }

    if ((key == KEY_ENTER) || (key == KEY_SPACEBAR)) {
      rval = true;
      break;
    } else if (key == KEY_ESC) {
      rval = false;
      break;
    } else if (key == KEY_PRINT_SCREEN) {
      DoScreenshot();
    }
#ifndef RELEASE
    else if (key == KEY_R) {
      paint_start = timer_GetTime();
      for (int a = 0; a < MAX_PLR_LINES; a++) {
        val_printed[a] = false;
      }
      if (paint_in_sound_handle != -1) {
        Sound_system.StopSoundImmediate(paint_in_sound_handle);
        paint_in_sound_handle = -1;
      }
      if (paint_in_sound_id != -1) {
        paint_in_sound_handle = Sound_system.Play3dSound(paint_in_sound_id, &Objects[Players[Player_num].objnum]);
      }
    }
#endif
  }

  if (background_loaded)
    FreeLargeBitmap(&level_bmp);

  ui_ShowCursor();
  background_loaded = false;
  SetScreenMode(old_mode);
  SetUICallback(NULL);
  return rval;
}

#define PLR_COLS 100

char PLRHeader[PLR_COLS];
char PLRLevel[PLR_COLS];

char PLRText[MAX_PLR_LINES][PLR_COLS];
char PLRVal[MAX_PLR_LINES][PLR_COLS];

extern int Times_game_restored;

void SinglePlayerPostLevelResults() {
  const char *difficulty_levels[] = {TXT_TRAINEE, TXT_ROOKIE, TXT_HOTSHOT, TXT_ACE, TXT_INSANE};

  // Setup all the text to display
  // Initialize all the characters

  if (paint_in_sound_id != -1) {
    paint_in_sound_handle = Sound_system.Play2dSound(paint_in_sound_id, (float)1.0);
  }

  memset(PLRText, 0, sizeof(PLRText));
  memset(PLRVal, 0, sizeof(PLRVal));
  for (int a = 0; a < MAX_PLR_LINES; a++) {
    val_printed[a] = false;
  }
  paint_start = timer_GetTime();

  int curline = 0;
  int j;
  PLR.time_min = (int16_t)Players[Player_num].time_level / 60.0f;
  PLR.time_sec = (int16_t)(Players[Player_num].time_level - ((float)PLR.time_min * 60.0f));
  PLR.shield_rating = Objects[Players[Player_num].objnum].shields;
  PLR.energy_rating = Players[Player_num].energy;
  if (Players[Player_num].num_discharges_level > 0)
    PLR.accuracy_rating = (float)Players[Player_num].num_hits_level / (float)Players[Player_num].num_discharges_level;
  else
    PLR.accuracy_rating = 0.5f;

  // strcpy(PLRHeader,PLR_success?"Mission Successfull":"Mission Failed");
  strcpy(PLRHeader, PLR_success ? TXT_PLR_MSN_SUCCESS : TXT_PLR_MSN_FAILED);

  snprintf(PLRLevel, sizeof(PLRLevel), "%s", Level_info.name);
  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLTDIFFICULT);
  uint8_t dif;
  Current_pilot.get_difficulty(&dif);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%s", difficulty_levels[dif]);
  curline++;
  curline++;

  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_SCORE);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%d", Players[Player_num].score);
  curline++;
  curline++;

  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLRTIME);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%d:%.2d", PLR.time_min, PLR.time_sec);
  curline++;
  curline++;

  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLRENEMIESKILL);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%d", Players[Player_num].num_kills_level);
  curline++;
  curline++;

  if (Players[Player_num].friendly_kills_level) {
    snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLRFRIENDSKILL);
    snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%d", Players[Player_num].friendly_kills_level);
    curline++;
    curline++;
  }

  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLRSHIELD);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%.0f", PLR.shield_rating);
  curline++;
  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLRENERGY);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%.0f", PLR.energy_rating);
  curline++;
  curline++;

  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_NUMDEATHS);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%d", Players[Player_num].num_deaths_level);
  curline++;
  snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_PLRSAVERESRAT);
  snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%d", Times_game_restored);
  curline++;
  curline++;

  bool has_objectives = false;
  for (j = 0; (j < Level_goals.GetNumGoals()) && (curline < MAX_PLR_LINES); j++) {
    int goal_status;

    if (Level_goals.GoalStatus(j, LO_GET_SPECIFIED, &goal_status)) {
      if ((goal_status & LGF_ENABLED) && (goal_status & LGF_TELCOM_LISTS)) {
        has_objectives = true;
        break;
      }
    }
  }

  if (has_objectives) {
    snprintf(PLRText[curline], sizeof(PLRText[curline]), "%s", TXT_OBJECTIVES1);
    curline++;
    curline++;
  }

  for (j = 0; (j < Level_goals.GetNumGoals()) && (curline < MAX_PLR_LINES); j++) {
    int goal_status;

    if (Level_goals.GoalStatus(j, LO_GET_SPECIFIED, &goal_status)) {
      if ((goal_status & LGF_ENABLED) && (goal_status & LGF_TELCOM_LISTS))
      // if(goal_status & LGF_ENABLED)
      {
        char txt[64];
        Level_goals.GoalGetName(j, txt, sizeof(txt));
        if (goal_status & LGF_COMPLETED) {
          snprintf(PLRText[curline], sizeof(PLRText[curline]), "   %s:", txt);
          snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%s", TXT_COMPLETED);
        } else {
          snprintf(PLRText[curline], sizeof(PLRText[curline]), "   %s:", txt);
          snprintf(PLRVal[curline], sizeof(PLRVal[curline]), "%s", TXT_NOTCOMPLETEDYET);
        }
        curline++;
      }
    }
  }
}

#define PLR_PAINT_TIME .8 // Seconds it takes to paint the text across the screen
#define PLR_START_VAL_TIME 2.0
#define PLR_VAL_INTERVAL .20

int paint_progress = 0;

#define PLR_VALUE_TOP 125

int line_progress[MAX_PLR_LINES]; // This is where we currently are
char line_replace[MAX_PLR_LINES]; // The character we replaced with a NULL. Draw this bright

void PaintPLRSinglePlayerText() {

  const int TEXT_HEIGHT = 14;
  const int LEFT_COL = 50;
  const int RIGHT_COL = 450;
  char hi[3] = "\0\0";

#define PLR_TXT_HEADER TXT_PLRTITLE
  int i;

  // Put everything back where it was...
  for (i = 0; i < MAX_PLR_LINES; i++) {
    if (line_replace[i]) {
      PLRText[i][line_progress[i]] = line_replace[i];
    }
    line_progress[i] = 0;
    line_replace[i] = 0;
  }

  paint_progress = 25 * ((timer_GetTime() - paint_start) / PLR_PAINT_TIME);

  bool all_done_painting = true;

  for (i = 0; i < MAX_PLR_LINES; i++) {
    int curpos = paint_progress + (-2 * i);
    if (curpos < 0)
      curpos = 0;
    int tlen = strlen(PLRText[i]);
    if (tlen > curpos) {
      line_progress[i] = curpos;
      line_replace[i] = PLRText[i][curpos];
      PLRText[i][curpos] = '\0';
      all_done_painting = false;
    }
  }

  if (all_done_painting) {
    if (paint_in_sound_handle != -1) {
      mprintf(0, "Stopping paint in sound\n");
      Sound_system.StopSoundImmediate(paint_in_sound_handle);
      paint_in_sound_handle = -1;
    }
  }

  grtext_SetAlpha(255);

  grtext_SetFlags(GRTEXTFLAG_SHADOW);

  grtext_SetColor(UICOL_TEXT_NORMAL);
  grtext_SetFont(BIG_BRIEFING_FONT);
  int centerx = (Max_window_w / 2) - (grtext_GetTextLineWidth(PLR_TXT_HEADER) / 2);
  if (centerx < 0)
    centerx = 0;
  grtext_Printf(centerx, 30, PLR_TXT_HEADER);

  grtext_SetColor(UICOL_WINDOW_TITLE);
  centerx = (Max_window_w / 2) - (grtext_GetTextLineWidth(PLRLevel) / 2);
  if (centerx < 0)
    centerx = 0;
  grtext_Printf(centerx, 55, PLRLevel);

  centerx = (Max_window_w / 2) - (grtext_GetTextLineWidth(PLRHeader) / 2);
  if (centerx < 0)
    centerx = 0;
  grtext_Printf(centerx, 80, PLRHeader);

  grtext_SetFont(BRIEFING_FONT);
  int adjusted_line_no = 0;
  // depending on where we are paint part or all of the text.
  for (i = 0; i < MAX_PLR_LINES; i++) {
    // This way we paint the values at better interval
    if (*PLRVal[i])
      adjusted_line_no++;

    grtext_SetAlpha(255);
    grtext_SetColor(UICOL_TEXT_NORMAL);
    grtext_Printf(LEFT_COL, (TEXT_HEIGHT * i) + PLR_VALUE_TOP, PLRText[i]);
    if (line_replace[i] && (line_progress[i] > 0)) {
      grtext_SetAlpha(64);
      hi[0] = line_replace[i];
      grtext_Printf(LEFT_COL + grtext_GetTextLineWidth(PLRText[i]), (TEXT_HEIGHT * i) + PLR_VALUE_TOP, hi);
    }
    grtext_SetAlpha(255);
    float now = timer_GetTime();
    if ((now - paint_start) > (PLR_START_VAL_TIME + (adjusted_line_no * PLR_VAL_INTERVAL))) {
      if (!val_printed[i]) {
        if ((chunk_sound_id != -1) && (*PLRVal[i]))
          Sound_system.Play2dSound(chunk_sound_id, (float)1.0);
      }
      val_printed[i] = true;
      grtext_SetColor(UICOL_WINDOW_TITLE);
      grtext_Printf(RIGHT_COL, (TEXT_HEIGHT * i) + PLR_VALUE_TOP, PLRVal[i]);
    }
  }

  grtext_SetAlpha(255);
  grtext_SetColor(UICOL_WINDOW_TITLE);
  centerx = (Max_window_w / 2) - (grtext_GetTextLineWidth(TXT_HITAKEYORBUTTON) / 2);
  if (centerx < 0)
    centerx = 0;
  grtext_Printf(centerx, Max_window_h - (TEXT_HEIGHT * 1.2), TXT_HITAKEYORBUTTON);
}

/*

const char *GetNormalizedRating(float mag)
{
        int rating;

//	determine rating.
        rating = (int)(mag*5.0f);

        if (rating < 0)
                rating = 0;
        else if (rating >= LVLRES_STATS)
                rating = LVLRES_STATS-1;

        return TXT(Stat_ratings[rating]);
}

*/
