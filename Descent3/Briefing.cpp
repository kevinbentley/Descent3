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

 * $Logfile: /DescentIII/main/Briefing.cpp $
 * $Revision: 57 $
 * $Date: 4/14/99 2:50a $
 * $Author: Jeff $
 *
 * Briefing system
 *
 * $Log: /DescentIII/main/Briefing.cpp $
 *
 * 57    4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 56    2/25/99 11:56a Jeff
 * added embedded hottag support
 *
 * 55    1/04/99 6:12p Jeff
 * put in handling of mission state flags
 *
 * 54    1/04/99 12:32p Jeff
 * added support for mission flag parsing
 *
 * 53    12/15/98 4:28p Jeff
 * don't die if the briefing file doesn't exist
 *
 * 52    10/12/98 8:32p Jeff
 * changed the way focus is handled
 *
 * 51    9/11/98 10:34a Jeff
 * Briefing Editor completed
 *
 * 50    9/09/98 7:02p Jeff
 *
 * 49    8/28/98 12:57p Jeff
 * added sounds and some key functionality
 *
 * 48    8/27/98 2:51p Jeff
 * New TelCom finally checked in
 *
 * 47    8/19/98 1:38p Jeff
 * removed update2dsound
 *
 * 46    8/18/98 11:57a Jeff
 * fixed sound problem
 *
 * 45    7/11/98 9:16p Jeff
 * moved automatically drawing monitor overlay graphics from update() to a
 * function of it's own, that way the TelCom API can be avoided if needed
 *
 * 44    7/09/98 8:33p Samir
 * changes for new streaming interface.
 *
 * 43    6/26/98 2:49p Jeff
 * fixed the bug where is you aborted parsing in the middle of a screen
 * you'd crash
 *
 * 42    6/25/98 12:44p Jeff
 * Added ESC to escape out of TelCom while it's initializing.  Added
 * DestroyScratch to Monitor
 *
 * 41    6/19/98 6:05p Jeff
 * changes made due to voice system
 *
 * 40    6/18/98 5:18p Jeff
 * use new streamaudio system
 *
 * 39    6/17/98 8:08p Jeff
 * removed call to DoVoiceFrame
 *
 * 38    6/08/98 3:56p Jeff
 * added voice support
 *
 * 37    5/19/98 3:40p Jeff
 * poly models functional
 *
 * 36    5/18/98 4:20p Jeff
 * setup TelCom so D3_FAST zips it through
 *
 * 35    5/18/98 3:37p Jeff
 * added glow parameter to $button
 *
 * 34    5/15/98 5:16p Jeff
 * various changes
 *
 * 33    5/11/98 6:20p Jeff
 * added glitch and static keywords
 *
 * 32    5/08/98 12:39p Jeff
 * various cleanups
 *
 * 31    5/06/98 6:34p Jeff
 * capped framerate for mouse
 *
 * 30    5/04/98 5:29p Jeff
 * Added sound frames and mouse cursor drawing
 *
 * 29    5/04/98 1:35p Jeff
 * Changes made for mouse handling
 *
 * 28    5/04/98 11:01a Jeff
 * added scroll param to text
 *
 * 27    5/03/98 7:59p Jeff
 * little changes
 *
 * 26    5/01/98 2:16p Jeff
 * added $title and $sound
 *
 * 25    4/30/98 7:16p Jeff
 * added $font, exiting to mainmenu
 *
 * 24    4/29/98 4:36p Jeff
 * increased text buffer size
 *
 * 23    4/28/98 6:58p Jeff
 * Added new poly model effect driver
 *
 * 22    4/26/98 7:22p Jeff
 * fixed fade ping pong bug, implemented new invert and stretch bitmaps
 *
 * 21    4/26/98 2:53a Jeff
 * Made changes needed for new Effect driver system
 *
 * 20    4/24/98 6:35p Jeff
 * Added space bar page forward
 *
 * 19    4/24/98 3:29p Jeff
 * fixed powerup effect
 *
 * 18    4/23/98 7:09p Jeff
 * added power up/down support
 *
 * 17    4/22/98 7:44p Jeff
 * added flashing buttons
 *
 * 16    4/21/98 4:22p Jeff
 * Call a general purpose function to draw entire telcom screen
 *
 * 15    4/20/98 6:45p Jeff
 * added multiple screen handling and on screen buttons
 *
 * 14    4/17/98 6:55p Jeff
 * Added button support
 *
 * 13    4/15/98 6:28p Jeff
 * Got parsing working for most of the keywords
 *
 * 12    3/23/98 9:55a Jeff
 * Made changes to remove old telcom
 *
 * 11    3/12/98 3:32p Jeff
 * Initial changes started for New TelCom
 *
 * 10    2/03/98 12:21p Jeff
 * changed default font to briefing font
 *
 * 9     1/26/98 4:19p Jeff
 * Added "blur in" bitmap effect
 *
 * 8     1/20/98 9:16p Jeff
 * Added back in fading bitmaps
 *
 * 7     1/20/98 6:04p Jeff
 * Added support for fading fonts
 *
 * 6     1/20/98 10:43a Jeff
 *
 * 5     1/19/98 5:37p Jeff
 * Got briefing up to par, and even better than before, added timer so
 * scroll and type fonts are time based.
 *
 * 4     1/16/98 2:40p Jeff
 * Adjusted so everything is displayed in correct spots, took out
 * DefaultControl timer, added support for non fading bitmaps
 *
 * 3     1/15/98 11:14a Jeff
 * Changed some code in TelComCallMission() to get Telcom working again
 *
 * 2     11/17/97 3:56p Matt
 * Added the briefing system code
 *
 * 1     11/12/97 10:44a Matt
 *
 * $NoKeywords: $
 */

#include "Briefing.h"
#include "BriefingParse.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "game.h"
#include "mem.h"
#include "hlsoundlib.h"
#include "voice.h"
#include "streamaudio.h"
#include "pserror.h"
#include "ddio.h"
#include "descent.h"
#include "TelCom.h"
#include "TelComEffects.h"
#include "Mission.h"

struct tBriefingTag {
  const char *name;
  int id;
  int length;
};

#define TAG_LEVELNUM 0
#define TAG_PLEVELNUM 1
#define TAG_NLEVELNUM 2

static tBriefingTag HotTags[] = {
    {"#LEVELNUM#", TAG_LEVELNUM, -1},
    {"#PLEVELNUM#", TAG_PLEVELNUM, -1},
    {"#NLEVELNUM#", TAG_NLEVELNUM, -1},
};
static constexpr int NumHotTags = sizeof(HotTags) / sizeof(tBriefingTag);

static int osb_xoff = 0, osb_yoff = 0;
static int current_screen = -1;
static tTelComInfo *pb_tcs = NULL;
static bool gottitle = false;
static bool pbfirst_call;
static char pbtitle[100];
static bool ok_to_parse_screen = false;
static int skipped_screens;

static bool IsMissionMaskOK(uint32_t set, uint32_t unset);
static void ReplaceHotTag(char *string, int tag);
static bool ParseForHotTags(const char *src, char **dest);
static bool PlayBriefing(tTelComInfo *tcs);
static void PBAddTextEffect(TCTEXTDESC* desc, char *text, char *description, int id);
static void PBAddBmpEffect(TCBMPDESC* desc, char *description);
static void PBAddMovieEffect(TCMOVIEDESC* desc, char *description);
static void PBAddBkgEffect(TCBKGDESC* desc, char *description);
static void PBAddPolyEffect(TCPOLYDESC* desc, char *description);
static void PBAddButtonEffect(TCBUTTONDESC* desc, char *description, int id);
static void PBStartScreen(int screen_num, char *description, char *layout, uint32_t mask_set, uint32_t mask_unset);
static void PBEndScreen();
static bool PBLoopCallback();
static void PBSetTitle(char *title);
static void PBSetStatic(float amount);
static void PBSetGlitch(float amount);
static void PBAddVoice(char *filename, int flags, char *description);

bool IsMissionMaskOK(uint32_t set, uint32_t unset) {
  uint32_t Gamemissionmask = Current_mission.game_state_flags;

  uint32_t fGamemissionmask;
  fGamemissionmask = Gamemissionmask ^ 0xFFFFFFFF;

  if (!(((set & Gamemissionmask) == set) && ((unset & fGamemissionmask) == unset))) {
    return false;
  }

  return true;
}

void ReplaceHotTag(char *string, int tag) {
  if (tag < 0 || tag >= NumHotTags) {
    *string = '\0';
    return;
  }

  switch (tag) {
  case TAG_LEVELNUM:
    sprintf(string, "%d", Current_mission.cur_level);
    break;
  case TAG_PLEVELNUM:
    sprintf(string, "%d", Current_mission.cur_level - 1);
    break;
  case TAG_NLEVELNUM:
    sprintf(string, "%d", Current_mission.cur_level + 1);
    break;
  }
}

// returns true if there were hot tags and it had to allocate memory for dest (so it needs to be freed)
#define MEMORY_BLOCK 50
bool ParseForHotTags(const char *src, char **dest) {
  bool ret = false;
  const char *curr_ptr = src;
  char *dest_ptr;
  *dest = NULL;

  bool done = false;
  int length = strlen(src) + 1;
  int curr_size = length;
  int curr_index = 0;

  dest_ptr = *dest = (char *)mem_malloc(length);
  if (!dest_ptr)
    return false;
  char replacement[256];

  while (!done) {
    if (*curr_ptr != '#') {
      if (*curr_ptr == '\0') {
        done = true;
      } else {
        *dest_ptr = *curr_ptr;
        dest_ptr++;
        curr_ptr++;
        curr_index++;
        length--;

        if (length < 1) {
          // we need to allocate some more memory
          char *new_mem = (char *)mem_malloc(curr_size + MEMORY_BLOCK);
          if (!new_mem) {
            // out of memory
            mem_free((*dest));
            *dest = NULL;
            return false;
          }

          memcpy(new_mem, (*dest), curr_index);
          mem_free(*dest);
          *dest = new_mem;
          dest_ptr = &new_mem[curr_index];
          curr_size += MEMORY_BLOCK;
          length += MEMORY_BLOCK;
        }
      }
    } else {
      int is_hot_tag = -1;

      // see if it's a hot tag
      for (int i = 0; i < NumHotTags; i++) {
        if (HotTags[i].length == -1)
          HotTags[i].length = strlen(HotTags[i].name);

        if (!strnicmp(curr_ptr, HotTags[i].name, HotTags[i].length)) {
          // this is a hot tag!!!!!
          mprintf(0, "Found Embedded HotTag: %s\n", HotTags[i].name);
          is_hot_tag = i;
          ret = true;
          break;
        }
      }

      if (is_hot_tag == -1) {
        // it wasn't a hot tag continue on
        *dest_ptr = *curr_ptr;
        dest_ptr++;
        curr_ptr++;
        curr_index++;
        length--;

        if (length < 1) {
          // we need to allocate some more memory
          char *new_mem = (char *)mem_malloc(curr_size + MEMORY_BLOCK);
          if (!new_mem) {
            // out of memory
            mem_free((*dest));
            *dest = NULL;
            return false;
          }

          memcpy(new_mem, (*dest), curr_index);
          mem_free(*dest);
          *dest = new_mem;
          dest_ptr = &new_mem[curr_index];
          curr_size += MEMORY_BLOCK;
          length += MEMORY_BLOCK;
        }
      } else {
        // we need to replace the hot tag
        ReplaceHotTag(replacement, is_hot_tag);
        curr_ptr += HotTags[is_hot_tag].length; // skip past hot tag

        int dest_left = strlen(replacement);
        char *r_ptr = replacement;

        while (dest_left > 0) {
          *dest_ptr = *r_ptr;
          dest_ptr++;
          curr_index++;
          length--;

          if (length < 1) {
            // we need to allocate some more memory
            char *new_mem = (char *)mem_malloc(curr_size + MEMORY_BLOCK);
            if (!new_mem) {
              // out of memory
              mem_free((*dest));
              *dest = NULL;
              return false;
            }

            memcpy(new_mem, (*dest), curr_index);
            mem_free(*dest);
            *dest = new_mem;
            dest_ptr = &new_mem[curr_index];
            curr_size += MEMORY_BLOCK;
            length += MEMORY_BLOCK;
          }

          dest_left--;
          r_ptr++;
        }
      }
    }
  }
  *dest_ptr = '\0';

  if (!ret) {
    mem_free((*dest));
    *dest = NULL;
  }

  return ret;
}

bool PlayBriefing(tTelComInfo *tcs) {
  TelcomRenderSetScreen(0);
  bool done = false;

  while (!done) {
    Sound_system.BeginSoundFrame(Telcom_called_from_game);

    if (tcs->state == TCS_POWEROFF || tcs->current_status != TS_MISSION) {
      // we're done with the loop
      done = true;
    }
    // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
    TelComHandleAllEvents(tcs);

    TelcomRenderScreen();
    Descent->defer();
    if (KEY_STATE(KEY_ESC))
      tcs->state = TCS_POWEROFF;

    Sound_system.EndSoundFrame();
  }
  return true;
}

void PBAddTextEffect(TCTEXTDESC* desc, char *text, char *description, int id) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen) {
    char *new_text = NULL;
    const bool new_stuff = ParseForHotTags(text, &new_text);

    CreateTextEffect(desc, new_stuff ? new_text : text, MONITOR_MAIN, current_screen, id);

    if (new_text) {
      mem_free(new_text);
    }
  }
}

void PBAddBmpEffect(TCBMPDESC* desc, char *description) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen)
    CreateBitmapEffect(desc, MONITOR_MAIN, current_screen);
}

void PBAddMovieEffect(TCMOVIEDESC* desc, char *description) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen)
    CreateMovieEffect(desc, MONITOR_MAIN, current_screen);
}

void PBAddBkgEffect(TCBKGDESC* desc, char *description) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen) {
    mprintf(0, "PB: Add Bkg\n");
  }
}

void PBAddPolyEffect(TCPOLYDESC* desc, char *description) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen)
    CreatePolyModelEffect(desc, MONITOR_MAIN, current_screen);
}

void PBAddSoundEffect(TCSNDDESC* desc, char *description) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen)
    CreateSoundEffect(desc, MONITOR_MAIN, current_screen);
}

void PBAddButtonEffect(TCBUTTONDESC* desc, char *description, int id) {
  if (IsMissionMaskOK(desc->mission_mask_set, desc->mission_mask_unset) && ok_to_parse_screen) {
    desc->x += osb_xoff;
    desc->y += osb_yoff;
    desc->tab_stop = false; // no briefing buttons can have focus
    CreateButtonEffect(desc, MONITOR_MAIN, current_screen, id);
  }
}

void PBStartScreen(int screen_num, char *description, char *layout, uint32_t mask_set, uint32_t mask_unset) {
  if (!IsMissionMaskOK(mask_set, mask_unset)) {
    ok_to_parse_screen = false;
    skipped_screens++;
    return;
  }
  int real_screen_num = screen_num - skipped_screens;
  ok_to_parse_screen = true;

  TelcomStartScreen(real_screen_num);
  current_screen = real_screen_num;

  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;
  CreateBackgroundEffect(&backg, MONITOR_TOP, current_screen);
  if (gottitle) {
    TCTEXTDESC textd;
    textd.color = GR_RGB(200, 200, 200);
    textd.type = TC_TEXT_STATIC;
    textd.font = BBRIEF_FONT_INDEX;
    textd.textbox.left = 4;
    textd.textbox.right = 300;
    textd.textbox.top = 2;
    textd.textbox.bottom = 80;
    textd.caps = TCTD_COLOR | TCTD_FONT | TCTD_TEXTBOX;
    CreateTextEffect(&textd, pbtitle, MONITOR_TOP, current_screen);
  }

  if (layout) {
    TCBMPDESC bmpd;
    bmpd.caps = TCBD_XY;
    bmpd.type = TC_BMP_STATIC;
    bmpd.flags = 0;
    bmpd.x = bmpd.y = 0;
    strcpy(bmpd.filename, layout);
    CreateBitmapEffect(&bmpd, MONITOR_MAIN, current_screen);
  }
}

void PBEndScreen() {
  if (ok_to_parse_screen) {
    TelcomEndScreen();
    current_screen = -1;
  }
}

bool PBLoopCallback() {
  if (!pbfirst_call) {
    Sound_system.EndSoundFrame();
  } else
    pbfirst_call = false;

  bool ret = false;
  Sound_system.BeginSoundFrame(Telcom_called_from_game);

  if (pb_tcs->state == TCS_POWEROFF || pb_tcs->current_status != TS_MISSION) {
    // we're done with the loop
    ret = true;
  }

  // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
  TelComHandleAllEvents(pb_tcs);
  TelcomRenderScreen();

  Descent->defer();
  if (KEY_STATE(KEY_ESC)) {
    pb_tcs->state = TCS_POWEROFF;
    ret = true;
  }

  return ret;
}

void PBSetTitle(char *title) {
  gottitle = true;
  strcpy(pbtitle, title);
}

void PBSetStatic(float amount) {
  if (amount > 0)
    TelcomEnableStatic(amount);
}

void PBSetGlitch(float amount) {
  if (amount > 0)
    TelcomEnableGlitch(amount);
}

void PBAddVoice(char *filename, int flags,char *description) {}

bool ParseBriefing(const char *filename, tTelComInfo *tcs) {
  if (!cfexist(filename)) {
    tcs->state = TCS_POWEROFF;
    return false;
  }

  osb_xoff = tcs->Monitor_coords[MONITOR_MAIN].left;
  osb_yoff = tcs->Monitor_coords[MONITOR_MAIN].top;
  current_screen = -1;
  pb_tcs = tcs;
  gottitle = false;
  pbtitle[0] = '\0';
  pbfirst_call = true;

  CBriefParse engine;
  tBriefParseCallbacks pb_callbacks;

  pb_callbacks.AddTextEffect = PBAddTextEffect;
  pb_callbacks.AddBmpEffect = PBAddBmpEffect;
  pb_callbacks.AddMovieEffect = PBAddMovieEffect;
  pb_callbacks.AddBkgEffect = PBAddBkgEffect;
  pb_callbacks.AddPolyEffect = PBAddPolyEffect;
  pb_callbacks.AddSoundEffect = PBAddSoundEffect;
  pb_callbacks.AddButtonEffect = PBAddButtonEffect;
  pb_callbacks.StartScreen = PBStartScreen;
  pb_callbacks.EndScreen = PBEndScreen;
  pb_callbacks.LoopCallback = PBLoopCallback;
  pb_callbacks.SetTitle = PBSetTitle;
  pb_callbacks.SetStatic = PBSetStatic;
  pb_callbacks.SetGlitch = PBSetGlitch;
  pb_callbacks.AddVoice = PBAddVoice;

  engine.SetCallbacks(&pb_callbacks);

  DestroyAllScreens();
  TelcomRenderSetScreen(DUMMY_SCREEN);

  skipped_screens = 0;
  int ret = engine.ParseBriefing(filename);
  Sound_system.EndSoundFrame();

  if (ret == PBERR_NOERR) {
    PlayBriefing(tcs);
  }

  DestroyAllScreens(true);
  TelcomCreateDummyScreen();
  TelcomRenderSetScreen(DUMMY_SCREEN);

  TelcomDisableStatic();
  TelcomDisableGlitch();

  return false;
}
