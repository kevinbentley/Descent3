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

 * $Source: $
 * $Revision: 27 $
 * $Author: Matt $
 * $Date: 12/06/01 9:26a $
 *
 * main menu interface
 *
 * $Log: /DescentIII/Main/mmItem.cpp $
 *
 * 27    12/06/01 9:26a Matt
 * Added code to override main menu bitmap.
 *
 * 26    3/20/00 12:17p Matt
 * Merge of Duane's post-1.3 changes.
 * Don't show build number in release versions (Mac only)
 *
 * 25    8/02/99 9:01a Duane
 * turned off menusound for mac
 *
 * 24    4/29/99 3:21a Samir
 * reorganized main menu music to work in config, multiplayer, whereever.
 *
 * 23    4/21/99 4:10p Samir
 * changed sound names for table file.
 *
 * 22    4/20/99 1:58a Matt
 * Changed version number text from old UI font to briefing font.
 *
 * 21    4/18/99 8:35p Samir
 * replaced placeholder sounds with newer placeholder sounds.
 *
 * 20    4/15/99 2:32p Kevin
 * Added some code for the Demo
 *
 * 19    4/14/99 11:48a Matt
 * Moved the main menu movie to the movies directory
 *
 * 18    4/02/99 3:03p Samir
 * opengl doesn't use main menu movie.
 *
 * 17    3/31/99 11:53a Samir
 * slow opengl code for movies.
 *
 * 16    3/23/99 9:06p Samir
 * properly sync wait dialog and sound system calls.
 *
 * 15    3/22/99 10:14a Kevin
 * Added a build number to the release builds of main. Also put in code to
 * increment the build number each time a release build is done.
 *
 * 14    3/18/99 10:13a Samir
 * new main menu interface.
 *
 * 13    3/02/99 11:52a Kevin
 * Fixes for OEM Beta 4.1
 *
 * 12    2/26/99 5:34p Samir
 * oem screen.
 *
 * 11    2/20/99 12:33p Kevin
 * Added some OEM stuff
 *
 * 10    10/23/98 7:05p Samir
 * fixed keyboard select prob.
 *
 * 9     10/22/98 5:23p Matt
 * Moved the version number and made it not print the build number if the
 * build number was zero.
 *
 * 8     10/20/98 3:52p Samir
 * tweaked main menu look.
 *
 * 7     10/13/98 6:06p Samir
 * fixed booboo.
 *
 * 6     10/13/98 5:51p Samir
 * moved version number
 *
 * 5     10/13/98 3:16p Samir
 * enhanced gadgets some more with new effects (added Credits option).
 *
 * 4     10/13/98 12:03p Kevin
 * Changed use of preprocessors for debug, etc.
 *
 * 3     10/12/98 4:40p Samir
 * fancy effect for hotspots in main menu.
 *
 * 2     10/12/98 1:46p Samir
 * initial new main menu
 *
 */

#include "mmItem.h"
#include "game.h"
#include "program.h"
#include "descent.h"
#include "cinematics.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "musicapi.h"

#include "ddio.h"
// #include <malloc.h>
#include "mem.h"

#include <string.h>

// externed from newui.cpp
extern int UI_frame_result;

static mmInterface *MM_object = NULL;
// attached window.
mmInterface *mmItem::m_window = NULL;

const char *MMSoundFiles[N_MM_SOUNDS] = {"MenuBeepEnter", "MenuBeepSelect"};
void PlayMenuSound(int sound_index, bool wait_till_done = false);

/*
$$TABLE_SOUND "MenuBeepEnter"
$$TABLE_SOUND "MenuBeepSelect"
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

mmItem::mmItem() { m_text = NULL; }

mmItem::~mmItem() {
  if (m_text)
    mem_free(m_text);
}

//	attaches a window to all mmitems.
void mmItem::AttachInterface(mmInterface *wnd) { mmItem::m_window = wnd; }

void mmItem::Create(int id, int key, int x, int y, const char *text, int flags, tmmItemFX init_fx) {
  m_alpha = 0;
  m_satcount = 0;
  m_fxqueue.flush();

  m_text = text ? mem_strdup(text) : NULL;
  m_fxqueue.send(init_fx);
  m_curfx = mmItemFXNull;
  m_process_speed = 0.0f;

  //	set colors
  m_colors[0] = MMITEM_COLOR;
  m_last_frametime = UI_TIME();

  UIGadget::Create(m_window, id, x, y, 0, 0, UIF_FIT | flags);
  UIGadget::SetHotkey(key);
}

void mmItem::AddEffect(tmmItemFX fx) { m_fxqueue.send(fx); }

void mmItem::ClearEffects() { m_fxqueue.flush(); }

// override: called when resized or before drawing.
void mmItem::OnFormat() {
  if (m_Flags & UIF_FIT) {
    ui_DrawSetFont(MMITEM_FONT);

    m_W = (m_text ? ui_GetTextWidth(m_text) : 0);
    m_H = (m_text ? ui_GetTextHeight(m_text) : 0);
  }

  UIGadget::OnFormat();
}

// override: behavior when gadget is destroyed.
void mmItem::OnDestroy() {
  if (m_text) {
    mem_free(m_text);
    m_text = NULL;
  }
}

void mmItem::OnSelect() {
  PlayMenuSound(m_window->SoundHandles[MM_SELECT_SOUND], true);
  UIGadget::OnSelect();
}

// override: behavior when mouse button is pressed.
void mmItem::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN) {
    LOCK_FOCUS(this);
  }
}

// override: behavior when mouse button is released.
void mmItem::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    if (HasFocus()) {
      if (PT_IN_GADGET(UIGadget::m_Wnd, this, UI_input.mx, UI_input.my)) {
        OnSelect();
      }
    }
    UNLOCK_FOCUS(this);
  }
}

// override: behavior when gadget loses input focus.
void mmItem::OnLostFocus() { AddEffect(mmItemFXFadeOutToNormal); }

// override: behavior when gadget gains input focus.
void mmItem::OnGainFocus() {
  AddEffect(mmItemFXFadeInToBright);
  PlayMenuSound(m_window->SoundHandles[MM_FOCUS_SOUND]);
}

// override: behavior when gadget is processed
void mmItem::OnUserProcess() {
  //	if (HasFocus() && !PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my)) {
  //		LostFocus();
  //	}
}

// override: behavior when gadget is being drawn.
void mmItem::OnDraw() {
  //	if not disabled, do fancy effects.
  if (m_text) {
    int i;

    ui_DrawSetFont(MMITEM_FONT);
    ui_DrawSetTextType(0);
    ui_SetCharAlpha(255);
    ui_DrawString(m_colors[0], 0, 0, m_text);
    ui_DrawSetTextType(UI_TEXTTYPE_SATURATE);
    ui_SetCharAlpha((uint8_t)m_alpha);
    for (i = 0; i < m_satcount; i++)
      ui_DrawString(m_colors[0], 0, 0, m_text);
  }

  if ((UI_TIME() - m_last_frametime) >= m_process_speed) {
    // process special fx.
    switch (m_curfx) {
    case mmItemFXNull:
      break;
    case mmItemFXNormal:
      m_alpha = MMITEM_ALPHA;
      m_satcount = MMITEM_SAT;
      m_process_speed = 0.0f;
      m_curfx = mmItemFXNull;
      break;

    case mmItemFXFadeOutToNormal:
      m_process_speed = 0.075f;
      m_satcount = (m_satcount < MMITEM_SAT) ? MMITEM_SAT : (m_satcount - 1);
      if (m_satcount == MMITEM_SAT) {
        m_curfx = mmItemFXNull;
      }
      break;

    case mmItemFXFadeInToBright:
      m_process_speed = 0.075f;
      m_satcount = (m_satcount > 2) ? 2 : (m_satcount + 1);
      if (m_satcount == 2) {
        m_curfx = mmItemFXNull;
      }
      break;
    }

    // grab new fx.
    if (m_curfx == mmItemFXNull) {
      tmmItemFX newfx;
      if (m_fxqueue.recv(&newfx)) {
        m_process_speed = 0.0f;
        m_curfx = newfx;
      }
    }

    m_last_frametime = UI_TIME();
  }
}

//////////////////////////////////////////////////////////////////////////////
//	MAIN MENU INTERFACE CODE

#include "stdlib.h" //need this to get _MAX_PATH, which really ought to be in ddio.h

bool static_menu_background = false;

void mmInterface::Create() {
  int i;

  MM_object = this;

  UIWindow::Create(0, 0, Max_window_w, Max_window_h);
  mmItem::AttachInterface(this);

#ifndef MOVIE_MENU
#if defined(OEM)
  if (!LoadLargeBitmap("oemmenu.ogf", &m_art)) {
    Error("Unable to load main menu art oemmenu.ogf.");
  }
#elif defined(DEMO)
  if (!LoadLargeBitmap("demomenu.ogf", &m_art)) {
    Error("Unable to load main menu art demomenu.ogf.");
  }
#else
  if (!LoadLargeBitmap("mainmenu.ogf", &m_art)) {
    Error("Unable to load main menu art mainmenu.ogf.");
  }
#endif
#else
  if (cfexist("mainmenuoverride.ogf")) {
    if (!LoadLargeBitmap("mainmenuoverride.ogf", &m_art)) {
      Error("Unable to load main menu art mainmenuoverride.ogf.");
    }
    m_movie = NULL;
    static_menu_background = true;
  } else {
    char filename[_MAX_PATH];
    ddio_MakePath(filename, Base_directory, "movies", "mainmenu", NULL);
    m_movie = StartMovie(filename, true);

    if (!m_movie) //[ISB] Didn't find the menu movie?
    {
      if (!LoadLargeBitmap("mainmenu.ogf", &m_art)) {
        Error("Unable to load main menu art mainmenu.ogf.");
      } else {
        static_menu_background = true;
      }
    }
  }
#endif

  // load sounds and music
  for (i = 0; i < N_MM_SOUNDS; i++) {
    SoundHandles[i] = FindSoundName(IGNORE_TABLE(MMSoundFiles[i]));
  }

  D3MusicStart("mainmenu.omf");
  SetMusicRegion(MM_MUSIC_REGION);

  SetUICallback(MenuScene);
  m_nmenu_items = 0;
}

//	does user interface.
int mmInterface::DoUI() {
  UI_frame_result = -1;
  ui_ShowCursor();

  SetUICallback(MenuScene);

  while (UI_frame_result == -1) {
    App()->defer();
    DoUIFrame();
    rend_Flip();
  }

  ui_HideCursor();
  ui_Flush();

  return UI_frame_result;
}

//	add item.
bool mmInterface::AddItem(int id, int key, const char *text, int type) {
  if (m_nmenu_items == N_MMENU_ITEMS) {
    Int3(); // N_MMENU_ITEMS needs to be upped! (Samir)
    return false;
  }

  m_menuitems[m_nmenu_items].Create(id, key, MMITEM_X, MMITEM_Y + (m_nmenu_items * 20), text,
                                    (type == 1)   ? UIF_GROUP_START
                                    : (type == 2) ? UIF_GROUP_END
                                    : (type == 3) ? (UIF_GROUP_START + UIF_GROUP_END)
                                                  : 0);
  m_nmenu_items++;

  return true;
}

// When interface is being nuked.
void mmInterface::OnDestroy() {
  UIWindow::OnDestroy();

  D3MusicStop();
  Sound_system.StopAllSounds();

  if (static_menu_background) {
    FreeLargeBitmap(&m_art);
  } else {
#ifdef MOVIE_MENU
    if (m_movie) {
      EndMovie(m_movie);
      m_movie = NULL;
    }
#else
    FreeLargeBitmap(&m_art);
#endif
  }

  SetUICallback(DEFAULT_UICALLBACK);
  MM_object = NULL;
}

// displays the copyright text
void mmInterface::CopyrightText() {
  int i;
  char type[16];
  type[0] = 0;
#ifdef DEMO
  strcpy(type, "Demo ");
#endif

  if (PROGRAM(beta))
    strcpy(type, "Beta ");

#ifdef OEM
  strcat(type, "OEM ");
#endif

  if (Program_version.version_type == DEVELOPMENT_VERSION) {
    strcat(type, "Dev");
  } else if (Program_version.version_type == RELEASE_VERSION) {
    strcat(type, "Ver");
  }

  int x = Max_window_w - 164, y = Max_window_h - 29; // was -128 and -16

  // attempt to print text nicely.
  grtext_SetFont(BRIEFING_FONT);
  grtext_SetAlpha(192);
  grtext_SetColor(GR_RGB(255, 32, 32));

  grtext_Printf(x, y, "%s %d.%d.%d %s", type, Program_version.major,
                Program_version.minor, Program_version.build, D3_GIT_HASH);
  grtext_SetFlags(GRTEXTFLAG_SHADOW);
  grtext_Printf(x, y, "%s %d.%d.%d %s", type, Program_version.major,
                Program_version.minor, Program_version.build, D3_GIT_HASH);

  grtext_Flush();
}

void mmInterface::SetMusicRegion(int region) {
  if (region == -1) {
    D3MusicStop();
    D3MusicStart("mainmenu.omf");
    SetMusicRegion(MM_MUSIC_REGION);
  } else {
    D3MusicSetRegion(region, true);
  }
}

// display menu scene
void MenuScene() {
  extern bool NewUI_wait_dialog; // is wait dialog up?

  if (MM_object) {
    StartFrame();

    if (static_menu_background) {
      DrawLargeBitmap(&MM_object->m_art, 0, 0, 1.0f);
    } else {
#ifdef MOVIE_MENU
      FrameMovie(MM_object->m_movie, -1, -1, true);
#else
      DrawLargeBitmap(&MM_object->m_art, 0, 0, 1.0f);
#endif
    }

    MM_object->CopyrightText();

    EndFrame();
  }
}

#define N_MENU_SOUND_SLOTS 4

void PlayMenuSound(int sound_index, bool wait_till_done) {
  int sound_uid;

  Sound_system.BeginSoundFrame(false);
  sound_uid = Sound_system.Play2dSound(sound_index, 1.0f);
  Sound_system.EndSoundFrame();

  if (wait_till_done) {
    float timer = timer_GetTime();
    while (Sound_system.IsSoundPlaying(sound_uid) && ((timer + 5.0f) > timer_GetTime())) {
      Sound_system.BeginSoundFrame(false);
      App()->defer();
      Sound_system.EndSoundFrame();
    }
  }
}
