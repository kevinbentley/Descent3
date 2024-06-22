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

 * $Logfile: /DescentIII/Main/newui_core.cpp $
 * $Revision: 64 $
 * $Date: 10/21/99 5:05p $
 * $Author: Matt $
 *
 * <insert description of file here>
 *
 * $Log: /DescentIII/Main/newui_core.cpp $
 *
 * 64    10/21/99 5:05p Matt
 * Mac merge
 *
 * 63    5/20/99 11:08p Samir
 * better error checking when freeing resources, may do nothing, may fix a
 * bug.
 *
 * 62    5/10/99 12:31a Samir
 * listboxes don't quit when double clicked outside selected item.
 *
 * 61    5/08/99 11:20p Samir
 * hotspots have different highlight effect.
 *
 * 60    5/08/99 1:06a Samir
 * scrunch messagebox buttons closer together
 *
 * 59    5/06/99 1:24a Samir
 * upped editbox maxlength to 512
 *
 * 58    5/05/99 10:53a Samir
 * allow loading of 'error texture' bitmaps to determine missing data (and
 * not to error out.)
 *
 * 57    5/02/99 7:28p Samir
 * fixed a bunch of option button bugs and allow music in
 * UIFrameWithoutInput for the menu mode.
 *
 * 56    5/02/99 2:14a Samir
 * fixed a few issues with option buttons.
 *
 * 55    5/01/99 7:46p Samir
 * oops.   really bad if statement fixed, could fix crash bug.
 *
 * 54    5/01/99 1:14a Samir
 * fixed mouse sequencing probs with selections being canceled out by
 * UISystem.
 *
 * 53    4/30/99 10:53p Samir
 * only accept double clicks inside of listbox
 *
 * 52    4/29/99 10:02p Samir
 * fixed percent display for slider.
 *
 * 51    4/29/99 3:21a Samir
 * reorganized main menu music to work in config, multiplayer, whereever.
 *
 * 50    4/29/99 2:18a Samir
 * updated art for options style menu.
 *
 * 49    4/28/99 1:54a Samir
 * visual tweaks to text
 *
 * 48    4/27/99 9:24a Matt
 * Added system for drawing title bars on dialogs.
 *
 * 47    4/26/99 7:46p Samir
 * newuiTiledWindow flags passed to create is an int now.
 *
 * 46    4/21/99 2:15p Samir
 * table file filter fixes.
 *
 * 45    4/21/99 12:42p Samir
 * change some communication betwen UIEdit and child classes.
 *
 * 44    4/21/99 10:58a Samir
 * added changable text.
 *
 * 43    4/20/99 11:46a Samir
 * numerous ui 'feel' fixes.
 *
 * 42    4/18/99 7:55p Samir
 * fixed listbox double click and added functions to load and release
 * pertinent newui graphic data.
 *
 * 41    4/15/99 5:28p Samir
 * added advanced messagebox
 *
 * 40    4/05/99 5:40p Samir
 * double clicking on an empty listbox wont return anything.
 *
 * 39    4/05/99 5:13p Samir
 * fixed combo box asthetics.
 *
 * 38    4/05/99 10:40a Samir
 * upped count of gadgets in titled window.
 *
 * 37    3/23/99 9:05p Samir
 * took out redundant ddio_KeyFlush
 *
 * 36    3/22/99 1:55p Jeff
 * fixed more crashes
 *
 * 35    3/22/99 12:47p Jeff
 * oops...fixed some listbox crashes
 *
 * 34    3/19/99 9:21p Jeff
 * fixed some listbox sorting issues
 *
 * 33    3/19/99 9:15p Jeff
 * fixed some combo box things (Samir).   Fixed sorting issues with
 * listboxes/comboboxes if an item is added/removed before the selected
 * index (Jeff)
 *
 * 32    3/17/99 11:46a Jeff
 * added callback to set focus when a sheet is realized (Samir)
 *
 * 31    3/10/99 3:49p Samir
 * indent hotspots after newline.
 *
 * 30    3/09/99 11:58a Samir
 * converted buddy menu to new ui.
 *
 * 29    3/03/99 4:16a Samir
 * added fix for DoEditDialog, setting focus on edit gadget by default for
 * all sheets with editboxes (1st one.)
 *
 * 28    3/03/99 3:38a Samir
 * made listbox highlight a little more tolerable.
 *
 * 27    3/01/99 8:51p Samir
 * upped count of ui bitmaps.
 *
 * 26    3/01/99 7:29p Samir
 * fixed an issue with slaves getting freed after their master was
 * destroyed for sliders.
 *
 * 25    3/01/99 6:55p Samir
 * fixed saturation problems with old ui text.
 *
 * 24    3/01/99 5:52p Samir
 * fixed slider bars and added render distance.
 *
 * 23    3/01/99 4:39p Samir
 * added mono_state and dual_state menu option buttons.
 *
 * 22    3/01/99 4:59a Samir
 * added hotspots, combo boxes.
 *
 * 21    2/28/99 3:26a Samir
 * editbox enhancements.
 *
 * 20    2/28/99 2:23a Jeff
 * fixed sorting problem when calling GetCurrentItem
 *
 * 19    2/28/99 1:21a Jeff
 * fixed cut & paste bug using slider-> instead of edit->
 *
 * 18    2/26/99 2:10a Samir
 * fixed newuiTiledWindow so it realizes gadgets only when first started.
 *
 * 17    2/24/99 9:39p Jeff
 * fixed listbox sorting
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstdio>

#include "newui_core.h"
#include "bitmap.h"
#include "mem.h"
#include "pserror.h"
#include "game.h"
#include "ddio.h"
#include "renderer.h"
#include "descent.h"
#include "application.h"
#include "stringtable.h"
#include "gamefont.h"
#include "textaux.h"
#include "musicapi.h"
#include "hlsoundlib.h"

#include <string.h>

extern void ui_DoCursor();

// filenames of ui bitmaps
/*
        $$TABLE_GAMEFILE "LRGButton.ogf"
        $$TABLE_GAMEFILE "LRGButtonLit.ogf"
        $$TABLE_GAMEFILE "LongButton.ogf"
        $$TABLE_GAMEFILE "LongButtonLit.ogf"
        $$TABLE_GAMEFILE "SmallButton.ogf"
        $$TABLE_GAMEFILE "SmallButtonLit.ogf"
        $$TABLE_GAMEFILE "SmallButtonFramed.ogf"
        $$TABLE_GAMEFILE "SmallButtonFramedLit.ogf"
        $$TABLE_GAMEFILE "LongButtonRed.ogf"
        $$TABLE_GAMEFILE "LongButtonLitRed.ogf"
        $$TABLE_GAMEFILE "SmallButton.ogf"
        $$TABLE_GAMEFILE "SmallButtonLitRed.ogf"
        $$TABLE_GAMEFILE "Bar.ogf"
        $$TABLE_GAMEFILE "MinusButton.ogf"
        $$TABLE_GAMEFILE "MinusButtonLit.ogf"
        $$TABLE_GAMEFILE "PluseButton.ogf"
        $$TABLE_GAMEFILE "PluseButtonLit.ogf"
        $$TABLE_GAMEFILE "UpArrow.ogf"
        $$TABLE_GAMEFILE "UpArrowLit.ogf"
        $$TABLE_GAMEFILE "DownArrow.ogf"
        $$TABLE_GAMEFILE "DownArrowLit.ogf"
        $$TABLE_GAMEFILE "TinyButton.ogf"
        $$TABLE_GAMEFILE "TinyButtonLit.ogf"
        $$TABLE_GAMEFILE "SmallScreen.ogf"
        $$TABLE_GAMEFILE "MediumScreen.ogf"
        $$TABLE_GAMEFILE "FullScreen.ogf"
        $$TABLE_GAMEFILE "lbTop32.ogf"
        $$TABLE_GAMEFILE "lbTopRight32.ogf"
        $$TABLE_GAMEFILE "lbRight32.ogf"
        $$TABLE_GAMEFILE "lbBottomRight32.ogf"
        $$TABLE_GAMEFILE "lbBottom32.ogf"
        $$TABLE_GAMEFILE "lbBottomLeft32.ogf"
        $$TABLE_GAMEFILE "lbLeft32.ogf"
        $$TABLE_GAMEFILE "lbTopLeft32.ogf"
        $$TABLE_GAMEFILE "winTop32.ogf"
        $$TABLE_GAMEFILE "winTopRight64.ogf"
        $$TABLE_GAMEFILE "winRight32.ogf"
        $$TABLE_GAMEFILE "winBottomRight64.ogf"
        $$TABLE_GAMEFILE "winBottom32.ogf"
        $$TABLE_GAMEFILE "winBottomLeft64.ogf"
        $$TABLE_GAMEFILE "winLeft32.ogf"
        $$TABLE_GAMEFILE "winTopLeft64.ogf"
        $$TABLE_GAMEFILE "winCenter32.ogf"
        $$TABLE_GAMEFILE "winTitleLeft32.ogf"
        $$TABLE_GAMEFILE "winTitleCenter32.ogf"
        $$TABLE_GAMEFILE "winTitleRight32.ogf"
        $$TABLE_GAMEFILE "ComboBox.ogf"
        $$TABLE_GAMEFILE "AltArrowUp.ogf"
        $$TABLE_GAMEFILE "AltArrowUpLit.ogf"
        $$TABLE_GAMEFILE "AltArrowDown.ogf"
        $$TABLE_GAMEFILE "AltArrowDownLit.ogf"
*/

#define N_NEWUI_BMPS_TOTAL 64

#define NEWUI_LRGBTN_FILE "LRGButton.ogf"
#define NEWUI_LRGBTNLIT_FILE "LRGButtonLit.ogf"
#define NEWUI_LBTN_FILE "LongButton.ogf"
#define NEWUI_LBTNLIT_FILE "LongButtonLit.ogf"
#define NEWUI_BTN_FILE "SmallButton.ogf"
#define NEWUI_BTNLIT_FILE "SmallButtonLit.ogf"
#define NEWUI_LBTNFRAMED_FILE "LongButton.ogf"
#define NEWUI_LBTNLITFRAMED_FILE "LongButtonLit.ogf"
#define NEWUI_BTNFRAMED_FILE "SmallButtonFramed.ogf"
#define NEWUI_BTNLITFRAMED_FILE "SmallButtonFramedLit.ogf"
#define NEWUI_LCHKBTN_FILE "LongButtonRed.ogf"
#define NEWUI_LCHKBTNLIT_FILE "LongButtonLitRed.ogf"
#define NEWUI_CHKBTN_FILE "SmallButton.ogf"
#define NEWUI_CHKBTNLIT_FILE "SmallButtonLitRed.ogf"
#define NEWUI_SLIDER_FILE "Bar.ogf"
#define NEWUI_LARR_FILE "MinusButton.ogf"
#define NEWUI_LARRLIT_FILE "MinusButtonLit.ogf"
#define NEWUI_RARR_FILE "PluseButton.ogf"
#define NEWUI_RARRLIT_FILE "PluseButtonLit.ogf"
#define NEWUI_UARR_FILE "UPArrow.ogf"
#define NEWUI_UARRLIT_FILE "UPArrowLit.ogf"
#define NEWUI_DARR_FILE "DownArrow.ogf"
#define NEWUI_DARRLIT_FILE "DownArrowLit.ogf"
#define NEWUI_UARRCB_FILE "AltArrowUp.ogf"
#define NEWUI_UARRLITCB_FILE "AltArrowUpLit.ogf"
#define NEWUI_DARRCB_FILE "AltArrowDown.ogf"
#define NEWUI_DARRLITCB_FILE "AltArrowDownLit.ogf"
#define NEWUI_TINYBTN_FILE "TinyButton.ogf"
#define NEWUI_TINYBTNLIT_FILE "TinyButtonLit.ogf"

#define NEWUI_MSGBOX_FILE "SmallScreen.ogf"
#define NEWUI_MEDWIN_FILE "MediumScreen.ogf"
#define NEWUI_LRGWIN_FILE "FullScreen.ogf"

#define NEWUI_LB_N_FILE "lbTop32.ogf"
#define NEWUI_LB_NE_FILE "lbTopRight32.ogf"
#define NEWUI_LB_E_FILE "lbRight32.ogf"
#define NEWUI_LB_SE_FILE "lbBottomRight32.ogf"
#define NEWUI_LB_S_FILE "lbBottom32.ogf"
#define NEWUI_LB_SW_FILE "lbBottomLeft32.ogf"
#define NEWUI_LB_W_FILE "lbLeft32.ogf"
#define NEWUI_LB_NW_FILE "lbTopLeft32.ogf"

#define NEWUI_CB_FILE "ComboBox.ogf"

#define NEWUI_WIN_N_FILE "winTop32.ogf"
#define NEWUI_WIN_NE_FILE "winTopRight64.ogf"
#define NEWUI_WIN_E_FILE "winRight32.ogf"
#define NEWUI_WIN_SE_FILE "winBottomRight64.ogf"
#define NEWUI_WIN_S_FILE "winBottom32.ogf"
#define NEWUI_WIN_SW_FILE "winBottomLeft64.ogf"
#define NEWUI_WIN_W_FILE "winLeft32.ogf"
#define NEWUI_WIN_NW_FILE "winTopLeft64.ogf"
#define NEWUI_WIN_C_FILE "winCenter32.ogf"

#define NEWUI_WIN_TITLE_L_FILE "winTitleLeft32.ogf"
#define NEWUI_WIN_TITLE_C_FILE "winTitleCenter32.ogf"
#define NEWUI_WIN_TITLE_R_FILE "winTitleRight32.ogf"

// used to position gadgets in a small screen
#define NEWUI_MSGBOX_BUTTONS_X 242
#define NEWUI_MSGBOX_BUTTONS_Y 24
#define NEWUI_MSGBOX_BUTTONS_H 22
#define NEWUI_MSGBOX_BUTTONS_Y2 16
#define NEWUI_MSGBOX_BUTTONS_H2 20
#define NEWUI_MSGBOX_SHEET_X 22
#define NEWUI_MSGBOX_SHEET_Y 30

//	used to position gadgets in a medium screen
#define NEWUI_MEDWIN_OPTIONS_X 314
#define NEWUI_MEDWIN_OPTIONS_Y 60
#define NEWUI_MEDWIN_OPTIONS_W 140
#define NEWUI_MEDWIN_OPTIONS_H 27
#define NEWUI_MEDWIN_SHEET_X 28
#define NEWUI_MEDWIN_SHEET_Y 40
#define NEWUI_MEDWIN_TITLE_X 90
#define NEWUI_MEDWIN_TITLE_Y 13
#define NEWUI_MEDWIN_TITLE_W 125

//	used to position gadgets in a large screen
#define NEWUI_LRGWIN_OPTIONS_X 35
#define NEWUI_LRGWIN_OPTIONS_Y 415
#define NEWUI_LRGWIN_OPTIONS_W 132
#define NEWUI_LRGWIN_OPTIONS_H 27
#define NEWUI_LRGWIN_SHEET_X 40
#define NEWUI_LRGWIN_SHEET_Y 50
#define NEWUI_LRGWIN_TITLE_X 40
#define NEWUI_LRGWIN_TITLE_Y 30

// used to define tiled window dims
#define NEWUI_TILED_SHEET_X 40
#define NEWUI_TILED_SHEET_Y 50
#define NEWUI_TILED_TITLE_X 40
#define NEWUI_TILED_TITLE_Y 30

// newuiListbox constants.
#define LB_PIECE_WIDTH 32
#define LB_PIECE_HEIGHT 32

// newuiTiledWindow constants.
#define TW_PIECE_WIDTH 32
#define TW_PIECE_HEIGHT 32
#define TW_CORNER_WIDTH 64
#define TW_CORNER_HEIGHT 64

// newuiEdit constants
#define EDIT_GADGET_WIDTH 192
#define EDIT_GADGET_HEIGHT 12
#define EDIT_BUFLEN_MAX 1025 // DAJ utb 512

// CLASS newui resource manager

class newuiResources {
  struct t_bmp_list {
    union {
      int bm_handle;
      chunked_bitmap chunk;
    };
    int16_t chunked; // is it a bitmap handle or chunk
    int16_t n_count;
    char *filename;             // filename of bitmap.
  } m_list[N_NEWUI_BMPS_TOTAL]; // list of bitmaps.

public:
  newuiResources();

  bool Init();     // initializes list
  void Shutdown(); // frees memory

  // loads bitmap and returns the object
  UIBitmapItem *Load(const char *filename);

  // frees memory for bitmap object.
  void Free(UIBitmapItem *bmitem);
};

//	CLASS creates an arrow button that is sensitive to touch (when down, always select)

//	CLASS a new check box: note that newuiButton and UICheckBox will share the same UIButton base
//	since bott newuiButton and UICheckBox inherit UIButton virtually.

class newuiCheckBox : public newuiButton, public UICheckBox {
public:
  newuiCheckBox();

  void Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y, bool is_long = false);

protected:
  virtual void OnDraw(); // this will use the newuiButton drawing scheme
  virtual void OnDestroy() { newuiButton::OnDestroy(); };
  virtual void OnFormat() { newuiButton::OnFormat(); };
  virtual void OnKeyDown(int key) { UICheckBox::OnKeyDown(key); };
  virtual void OnKeyUp(int key) { UICheckBox::OnKeyUp(key); };
  virtual void OnMouseBtnDown(int btn) { UICheckBox::OnMouseBtnDown(btn); };
  virtual void OnMouseBtnUp(int btn) { UICheckBox::OnMouseBtnUp(btn); };
  virtual void OnLostFocus() { newuiButton::OnLostFocus(); };
  virtual void OnGainFocus() { newuiButton::OnGainFocus(); };
};

class newuiRadioButton : public newuiButton, public UIRadioButton {
public:
  newuiRadioButton();

  void Create(UIWindow *wnd, UIRadioButton *prev_rb, int16_t id, const char *name, int16_t x, int16_t y,
              bool is_long = false);

protected:
  virtual void OnDraw(); // this will use the newuiButton drawing scheme
  virtual void OnDestroy() { newuiButton::OnDestroy(); };
  virtual void OnFormat() { newuiButton::OnFormat(); };
  virtual void OnKeyDown(int key) { UIRadioButton::OnKeyDown(key); };
  virtual void OnKeyUp(int key) { UIRadioButton::OnKeyUp(key); };
  virtual void OnMouseBtnDown(int btn) { UIRadioButton::OnMouseBtnDown(btn); };
  virtual void OnMouseBtnUp(int btn) { UIRadioButton::OnMouseBtnUp(btn); };
  virtual void OnLostFocus() { newuiButton::OnLostFocus(); };
  virtual void OnGainFocus() { newuiButton::OnGainFocus(); };
};

//	CLASS a new slider.

#define SUBGADGET_LEFT 0x1
#define SUBGADGET_RIGHT 0x2

class newuiSlider : public UIGadget {
  int16_t m_pos;
  int16_t m_unitrange;
  UIBitmapItem *m_bar_bmp;
  UISnazzyTextItem *m_title;
  newuiArrowButton m_minus_btn;
  newuiArrowButton m_plus_btn;
  tSliderSettings m_unit_settings;

public:
  newuiSlider();

  void Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y, int16_t range);
  void Offset(int16_t offs);
  void SetPos(int16_t pos);
  void SetRange(int16_t range);
  int16_t GetPos() const { return m_pos; };
  int16_t GetRange() const { return m_unitrange; };
  void SetUnits(tSliderSettings *settings);

protected:
  virtual void OnFormat();                  // override: called when resized or before drawing.
  virtual void OnLostFocus();               // override: behavior when gadget loses input focus.
  virtual void OnGainFocus();               // override: behavior when gadget gains input focus.
  virtual void OnDraw();                    // behavior when gadget is being drawn.
  virtual void OnDestroy();                 // behavior when gadget is being destroyed.
  virtual void OnNotifySelect(UIGadget *g); // this function will handle when an arrow button was pressed
  virtual void OnKeyDown(int btn);          // override: behavior when key pressed.
  virtual void OnKeyUp(int btn);            // override: behavior when key released.
  virtual void OnAttachToWindow();          // when gadget is added to a window (AddGadget is called)
  virtual void OnDetachFromWindow();        // when gadget is detached from window
};

//	CLASS newuiEditBox

class newuiEditBox : public UIEdit {
public:
  newuiEditBox();

  void Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y, int16_t w, int16_t flags);
  void EnableOnQuickEscapeBehavior(bool do_it);

protected:
  virtual void OnDraw();
  virtual void OnDestroy();
  virtual void OnKeyDown(int key);

private:
  UISnazzyTextItem *m_title;
  bool m_quick_escape_enable;
};

static inline UISnazzyTextItem *MonitorSmallText(const char *text) {
  return new UISnazzyTextItem(0, MONITOR9_NEWUI_FONT, text, NEWUI_MONITORFONT_COLOR);
}

static inline UISnazzyTextItem *MonitorLargeText(const char *text) {
  return new UISnazzyTextItem(0, MONITOR15_NEWUI_FONT, text, NEWUI_MONITORFONT_COLOR);
}

static inline UISnazzyTextItem *GadgetSmallText(const char *text) {
  return new UISnazzyTextItem(0, GADGET9_NEWUI_FONT, text, NEWUI_GADGETFONT_COLOR);
}

static inline UISnazzyTextItem *GadgetLargeText(const char *text) {
  return new UISnazzyTextItem(0, GADGET15_NEWUI_FONT, text, NEWUI_GADGETFONT_COLOR);
}

//////////////////////////////////////////////////////////////////////////////
//	DATA
static const char *Preloaded_bitmap_list[] = {
    NEWUI_LRGBTN_FILE, // common buttons
    NEWUI_LRGBTNLIT_FILE,   NEWUI_LBTN_FILE,        NEWUI_LBTNLIT_FILE,     NEWUI_BTN_FILE,
    NEWUI_BTNLIT_FILE,      NEWUI_LCHKBTN_FILE,     NEWUI_LCHKBTNLIT_FILE,  NEWUI_CHKBTN_FILE,
    NEWUI_CHKBTNLIT_FILE,   NEWUI_TINYBTN_FILE,     NEWUI_TINYBTNLIT_FILE,
    NEWUI_MSGBOX_FILE, // window frames
    NEWUI_MEDWIN_FILE,      NEWUI_LRGWIN_FILE,
    NEWUI_LB_N_FILE, // listbox frame
    NEWUI_LB_NE_FILE,       NEWUI_LB_E_FILE,        NEWUI_LB_SE_FILE,       NEWUI_LB_S_FILE,
    NEWUI_LB_SW_FILE,       NEWUI_LB_W_FILE,        NEWUI_LB_NW_FILE,
    NEWUI_WIN_N_FILE, // tiled window frames
    NEWUI_WIN_NE_FILE,      NEWUI_WIN_E_FILE,       NEWUI_WIN_SE_FILE,      NEWUI_WIN_S_FILE,
    NEWUI_WIN_SW_FILE,      NEWUI_WIN_W_FILE,       NEWUI_WIN_NW_FILE,      NEWUI_WIN_C_FILE,
    NEWUI_WIN_TITLE_L_FILE, NEWUI_WIN_TITLE_C_FILE, NEWUI_WIN_TITLE_R_FILE,
};

#define N_UI_PRELOADED_BITMAPS (sizeof(Preloaded_bitmap_list) / sizeof(const char *))

int UI_frame_result = -1;
static newuiResources Newui_resources;
static void (*UI_callback)() = NULL;
static UIBitmapItem *Preloaded_bitmaps[N_UI_PRELOADED_BITMAPS] = {
    NULL,
};

#ifndef MULTI_H
extern bool Multi_bail_ui_menu;
#endif

void SimpleUICallback();

//////////////////////////////////////////////////////////////////////////////
// initializes the core system for the newui

void newuiCore_Init() { Newui_resources.Init(); }

// initializes the core system for the newui
void newuiCore_Close() { Newui_resources.Shutdown(); }

//	 C interface to load and free bitmap resources
UIBitmapItem *newui_LoadBitmap(const char *filename) { return Newui_resources.Load(filename); }

//	 C interface to load and free bitmap resources
void newui_FreeBitmap(UIBitmapItem *bmitem) { Newui_resources.Free(bmitem); }

// touches all newui bitmaps, do before any newui menus open
void newuiCore_PageInBitmaps() {
  int i;

  if (Preloaded_bitmaps[0]) {
    Int3(); // we've already paged in stuff!
    return;
  }

  for (i = 0; i < N_UI_PRELOADED_BITMAPS; i++) {
    Preloaded_bitmaps[i] = newui_LoadBitmap(Preloaded_bitmap_list[i]);
  }
}

// call when NO newui menus open
void newuiCore_ReleaseBitmaps() {
  int i;

  if (!Preloaded_bitmaps[0]) {
    Int3(); // we've already freed paged in stuff!
    return;
  }

  for (i = 0; i < N_UI_PRELOADED_BITMAPS; i++) {
    newui_FreeBitmap(Preloaded_bitmaps[i]);
    Preloaded_bitmaps[i] = NULL;
  }
}

//	does a UI loop
//

int DoUI() {
  //	this should poll UI_frame_result.
  UI_frame_result = -1;
  ui_ShowCursor();
  ui_Flush();

  while (UI_frame_result == -1) {
    App()->defer();
    DoUIFrame();
    rend_Flip();
  }

  ui_HideCursor();
  ui_Flush();

  return UI_frame_result;
}

//	does one frame of ui.
void DoUIFrame() {
  if (Multi_bail_ui_menu) {
    UI_frame_result = NEWUIRES_FORCEQUIT;
  } else {
    if (UI_callback)
      (*UI_callback)();

    if (GetFunctionMode() == MENU_MODE) {
      tMusicSeqInfo music_info;

      Sound_system.BeginSoundFrame(false);

      music_info.frametime = UIFrameTime;
      music_info.player_dead = false;
      music_info.started_level = false;
      D3MusicDoFrame(&music_info);

      Sound_system.EndSoundFrame();
    }

    UI_frame_result = ui_DoFrame();
  }

  if (UI_input.printscreen) {
    UI_input.printscreen = false;
    DoScreenshot();
  }
}

//	does one frame of ui.
void DoUIFrameWithoutInput() {
  if (Multi_bail_ui_menu) {
    UI_frame_result = NEWUIRES_FORCEQUIT;
  } else {
    if (UI_callback)
      (*UI_callback)();

    if (GetFunctionMode() == MENU_MODE) {
      tMusicSeqInfo music_info;

      Sound_system.BeginSoundFrame(false);

      music_info.frametime = UIFrameTime;
      music_info.player_dead = false;
      music_info.started_level = false;
      D3MusicDoFrame(&music_info);

      Sound_system.EndSoundFrame();
    }

    UI_frame_result = ui_DoFrame(false);
  }
}

int GetUIFrameResult() { return UI_frame_result; }

//	sets the callback for background rendering of desktop for UI
void SetUICallback(void (*fn)()) {
  if (fn == DEFAULT_UICALLBACK)
    fn = SimpleUICallback;
  UI_callback = fn;
}

void (*GetUICallback())() { return UI_callback; }

void SimpleUICallback() {
  StartFrame(0, 0, Max_window_w, Max_window_h);
  rend_ClearScreen(GR_BLACK);
  EndFrame();
}

//////////////////////////////////////////////////////////////////////////////
// CLASS newui resource manager

newuiResources::newuiResources() {}

bool newuiResources::Init() {
  int i;
  for (i = 0; i < N_NEWUI_BMPS_TOTAL; i++) {
    m_list[i].n_count = 0;
  }

  return true;
}

void newuiResources::Shutdown() {
  int i;

  for (i = 0; i < N_NEWUI_BMPS_TOTAL; i++) {
    if (m_list[i].n_count > 0) {
      if (m_list[i].chunked) {
        bm_DestroyChunkedBitmap(&m_list[i].chunk);
      } else {
        bm_FreeBitmap(m_list[i].bm_handle);
      }
    }
    m_list[i].n_count = 0;
  }
}

// loads bitmap and returns the object
UIBitmapItem *newuiResources::Load(const char *filename) {
  UIBitmapItem *bmitem;
  int i, free_slot = -1;

  // do search for bitmap.
  for (i = 0; i < N_NEWUI_BMPS_TOTAL; i++) {
    if (m_list[i].n_count == 0) {
      if (free_slot == -1) {
        free_slot = i;
      }
    } else {
      if (stricmp(filename, m_list[i].filename) == 0) {
        break;
      }
    }
  }
  if (i == N_NEWUI_BMPS_TOTAL) {
    // perform load.
    int bm, chw, chh;

    if (free_slot == -1) {
      // reached limit.
      Int3();
      return NULL;
    }
    i = free_slot;

    bm = bm_AllocLoadFileBitmap(IGNORE_TABLE(filename), 0);
    if (bm < 0) {
      Error("NewUI: Failed to load bitmap %s", filename);
    }

    chw = bm_w(bm, 0);
    chh = bm_h(bm, 0);

    if ((chw == 32 && chh == 32) || (chw == 64 && chh == 64) || (chw == 128 && chh == 128)) {
      m_list[i].bm_handle = bm;
      m_list[i].chunked = 0;
    } else {
      // chunk it.
      bm_CreateChunkedBitmap(bm, &m_list[i].chunk);
      bm_FreeBitmap(bm);
      m_list[i].chunked = 1;
    }

    m_list[i].n_count = 0;
    m_list[i].filename = mem_strdup(filename);
  }

  m_list[i].n_count++;

  if (m_list[i].chunked) {
    bmitem = new UIBitmapItem(&m_list[i].chunk);
  } else {
    bmitem = new UIBitmapItem(m_list[i].bm_handle);
  }

  return bmitem;
}

// frees memory for bitmap object.
void newuiResources::Free(UIBitmapItem *bmitem) {
  int i;

  if (!bmitem) {
    Int3(); // Get samir.
    return;
  }

  for (i = 0; i < N_NEWUI_BMPS_TOTAL; i++) {
    if (m_list[i].n_count > 0) {
      if (m_list[i].chunked && bmitem->is_chunked()) {
        if (bmitem->get_chunked_bitmap()->bm_array == m_list[i].chunk.bm_array) {
          break;
        }
      } else if (!m_list[i].chunked && !bmitem->is_chunked()) {
        if (bmitem->get_bitmap() == m_list[i].bm_handle) {
          break;
        }
      }
    }
  }

  if (i >= N_NEWUI_BMPS_TOTAL) {
    Int3(); // maybe we should free this, well this really should never happen but if it does
    return; // I can't be completely sure this is a valid pointer, so rather than risking a crash I'll have a leak.
  }

  //	ASSERT(i < N_NEWUI_BMPS_TOTAL);

  // decrement and free.
  delete bmitem;

  m_list[i].n_count--;
  if (m_list[i].n_count == 0) {
    if (m_list[i].chunked) {
      bm_DestroyChunkedBitmap(&m_list[i].chunk);
    } else {
      bm_FreeBitmap(m_list[i].bm_handle);
    }
    mem_free(m_list[i].filename);
  }
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS a menu with options and sheets

newuiMenu::newuiMenu() {
  m_nsheets = 0;
  m_bkg = 0;
  m_cursheet = NULL;
  m_newoptionid = -1;
  m_align = NEWUI_ALIGN_VERT;
}

//	creates a menu
void newuiMenu::Create() {
  m_nsheets = 0;

  if (!m_bkg) {
    m_bkg = Newui_resources.Load(NEWUI_MEDWIN_FILE);
  }

  m_sheetx = NEWUI_MEDWIN_SHEET_X;
  m_sheety = NEWUI_MEDWIN_SHEET_Y;
  m_optionsx = NEWUI_MEDWIN_OPTIONS_X;
  m_optionsy = NEWUI_MEDWIN_OPTIONS_Y;
  m_optionsw = NEWUI_MEDWIN_OPTIONS_W;
  m_optionsh = NEWUI_MEDWIN_OPTIONS_H;
  m_titlex = NEWUI_MEDWIN_TITLE_X;
  m_titley = NEWUI_MEDWIN_TITLE_Y;
  m_align = NEWUI_ALIGN_VERT;

  m_uiframe_cb = GetUICallback();
  m_activate_sheet_cb = NULL;
  m_option_focus_cb = NULL;

  UIWindow::Create((Max_window_w - m_bkg->width()) / 2, (Max_window_h - m_bkg->height()) / 2, m_bkg->width(),
                   m_bkg->height());
  m_newoptionid = -1;
  m_cursheetidx = -1;
}

//	sets current option to display.
void newuiMenu::SetCurrentOption(int16_t id) { m_newoptionid = id; }

// returns current option
int16_t newuiMenu::GetCurrentOption() const {
  if (m_cursheetidx != -1) {
    return m_sheetbtn[m_cursheetidx].GetID();
  }

  return -1;
}

newuiSheet *newuiMenu::GetCurrentSheet() const { return m_cursheet; }

// when a new option is ready.   at this point the system sets the focus on this option
void newuiMenu::SetOnOptionFocusCB(void (*fn)(newuiMenu *, int16_t, void *), void *data) {
  m_option_focus_cb = fn;
  m_option_focus_cb_data = data;
}

// processes a menu
int newuiMenu::DoUI() {
  int res, i;

  if (m_newoptionid != -1) {
    m_cursheetidx = -1;
    for (i = 0; i < m_nsheets; i++) {
      if (m_sheetbtn[i].GetID() == (int)m_newoptionid) {
        if (m_cursheet) {
          m_cursheet->Unrealize();
          m_cursheet = NULL;
        }

        if (m_hassheet[i]) {
          if (m_activate_sheet_cb) {
            (*m_activate_sheet_cb)(this, m_sheetbtn[i].GetID(), m_newoptionid, m_activate_sheet_cb_data);
          }

          m_cursheet = &m_sheets[i];
          m_cursheet->Realize();
        }

        m_cursheetidx = i;

        SetFocusOnGadget(&m_sheetbtn[i]);

        if (m_option_focus_cb) {
          (*m_option_focus_cb)(this, m_sheetbtn[i].GetID(), m_option_focus_cb_data);
        }

        break;
      }
    }
    if (i == m_nsheets) { // error!
      Int3();
      if (m_cursheet) {
        m_cursheet->Unrealize();
        m_cursheet = NULL;
      }
    }
    m_newoptionid = -1;
  }

  // refreshes gadgets on current sheet.
  if (m_cursheet) {
    m_cursheet->UpdateChanges();
  }

  // do ui and check if a new option was selected
  res = ::DoUI();

  for (i = 0; i < m_nsheets; i++) {
    if (i != m_cursheetidx) {
      if (res == m_sheetbtn[i].GetID() && m_hassheet[i]) {
        m_newoptionid = (int16_t)res;
        break;
      }
    }
  }

  // updates return values
  if (m_cursheet) {
    m_cursheet->UpdateReturnValues();
  }

  return res;
}

// when a new sheet is realized, this function will be called.
// passed in: the menu object, the old option and the new option respectively
void newuiMenu::SetOnOptionSwitchCB(void (*fn)(newuiMenu *, int16_t, int16_t, void *), void *data) {
  m_activate_sheet_cb = fn;
  m_activate_sheet_cb_data = data;
}

// equivalent of SetUICallback, called before gadgets are drawn
void newuiMenu::SetOnUIFrameCB(void (*fn)()) {
  //	m_uiframe_cb = GetUICallback();
  //	SetUICallback(fn);
}

//	adds an option to a menu, returns a newuiSheet object to add user interface to.
void newuiMenu::AddSimpleOption(int16_t id, const char *title, int yoff) {
  newuiMenu::AddOption(id, title, 0, false, yoff);
}

newuiSheet *newuiMenu::AddOption(int16_t id, const char *title, int size, bool has_sheet, int yoff) {
  newuiMenuOptionButton *last_btn = NULL;

  if (m_nsheets == N_NEWUI_SHEETS) {
    Int3();
    return NULL;
  }

  if (has_sheet) {
    m_sheets[m_nsheets].Create(this, title, size, m_sheetx, m_sheety);
  }

  if (m_nsheets > 0) {
    last_btn = &m_sheetbtn[m_nsheets - 1];
  }

  switch (m_align) {
  case NEWUI_ALIGN_VERT:
    m_sheetbtn[m_nsheets].Create(this, last_btn, id, title, m_optionsx, m_optionsy + m_nsheets * m_optionsh + yoff,
                                 has_sheet);
    break;
  case NEWUI_ALIGN_HORIZ:
    m_sheetbtn[m_nsheets].Create(this, last_btn, id, title, m_optionsx + m_nsheets * m_optionsw + yoff, m_optionsy,
                                 has_sheet);
    break;
  default:
    Int3();
  }

  m_hassheet[m_nsheets] = has_sheet;
  m_newoptionid = id;
  m_nsheets++;

  if (!has_sheet) {
    return NULL;
  }

  return &m_sheets[m_nsheets - 1];
}

// set master sheet,button locations
void newuiMenu::SetPlacements(int x, int y, int options_x, int options_y, int options_w, int options_h, int title_x,
                              int title_y, tAlignment align) {
  m_sheetx = x;
  m_sheety = y;
  m_optionsx = options_x;
  m_optionsy = options_y;
  m_optionsw = options_w;
  m_optionsh = options_h;
  m_titlex = title_x;
  m_titley = title_y;
  m_align = align;
}

// overridable draws the window background before gadgets
void newuiMenu::OnDraw() {
  // draw background
  m_bkg->draw(0, 0);

  // draw title
  if (m_cursheetidx != -1 && m_hassheet[m_cursheetidx]) {
    UITextItem *title = m_sheetbtn[m_cursheetidx].GetTitle();
    UITextItem m_texttitle(MONITOR15_NEWUI_FONT, title->GetBuffer(), NEWUI_MONITORFONT_COLOR);

    m_texttitle.draw(m_titlex - 8 + (NEWUI_MEDWIN_TITLE_W - m_texttitle.width()) / 2, m_titley);
  }

  // draws gadgets.
  UIWindow::OnDraw();
}

// overridable: called in Destroy
void newuiMenu::OnDestroy() {
  int i;

  if (m_bkg) {
    Newui_resources.Free(m_bkg);
    m_bkg = NULL;
  }

  for (i = 0; i < m_nsheets; i++) {
    if (m_hassheet[i]) {
      m_sheets[i].Destroy();
      m_sheetbtn[i].Destroy();
      m_hassheet[i] = false;
    }
  }

  m_nsheets = 0;

  SetUICallback(m_uiframe_cb);

  UIWindow::OnDestroy();
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS, large (fullscreen) menu

//	creates a menu
void newuiLargeMenu::Create() {
  m_bkg = Newui_resources.Load(NEWUI_LRGWIN_FILE);
  newuiMenu::Create();
  newuiMenu::SetPlacements(NEWUI_LRGWIN_SHEET_X, NEWUI_LRGWIN_SHEET_Y, NEWUI_LRGWIN_OPTIONS_X, NEWUI_LRGWIN_OPTIONS_Y,
                           NEWUI_LRGWIN_OPTIONS_W, NEWUI_LRGWIN_OPTIONS_H, NEWUI_LRGWIN_TITLE_X, NEWUI_LRGWIN_TITLE_Y,
                           NEWUI_ALIGN_HORIZ);
}

//	adds an option to a menu, returns a newuiSheet object to add user interface to.
newuiSheet *newuiLargeMenu::AddOption(int16_t id, const char *title, int size) {
  return newuiMenu::AddOption(id, title, size);
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS, small message box
#define MBTN_OK 0
#define MBTN_CANCEL 1

newuiMessageBox::newuiMessageBox() { m_bkg = NULL; }

void newuiMessageBox::Create(const char *title, int type) {
  ASSERT(title);
  m_bkg = Newui_resources.Load(NEWUI_MSGBOX_FILE);

  UIWindow::Create((Max_window_w - m_bkg->width()) / 2, (Max_window_h - m_bkg->height()) / 2, m_bkg->width(),
                   m_bkg->height());

  m_sheet.Create(this, title, NEWUIMENU_SMALL, NEWUI_MSGBOX_SHEET_X, NEWUI_MSGBOX_SHEET_Y);

  if (type == MSGBOX_OK) {
    m_btn[MBTN_OK].Create(this, UID_OK, TXT_OK, NEWUI_MSGBOX_BUTTONS_X, NEWUI_MSGBOX_BUTTONS_Y, NEWUI_BTNF_FRAMED);
    AddAcceleratorKey(KEY_ESC, UID_OK);
  } else if (type == MSGBOX_OKCANCEL) {
    m_btn[MBTN_OK].Create(this, UID_OK, TXT_OK, NEWUI_MSGBOX_BUTTONS_X, NEWUI_MSGBOX_BUTTONS_Y, NEWUI_BTNF_FRAMED);
    m_btn[MBTN_CANCEL].Create(this, UID_CANCEL, TXT_CANCEL, NEWUI_MSGBOX_BUTTONS_X,
                              NEWUI_MSGBOX_BUTTONS_Y + NEWUI_MSGBOX_BUTTONS_H, NEWUI_BTNF_FRAMED);
  } else if (type == MSGBOX_YESNO) {
    m_btn[MBTN_OK].Create(this, UID_OK, TXT_YES, NEWUI_MSGBOX_BUTTONS_X, NEWUI_MSGBOX_BUTTONS_Y, NEWUI_BTNF_FRAMED);
    m_btn[MBTN_CANCEL].Create(this, UID_CANCEL, TXT_NO, NEWUI_MSGBOX_BUTTONS_X,
                              NEWUI_MSGBOX_BUTTONS_Y + NEWUI_MSGBOX_BUTTONS_H, NEWUI_BTNF_FRAMED);
    m_btn[MBTN_OK].SetHotkey(KEY_Y);
    m_btn[MBTN_CANCEL].SetHotkey(KEY_N);
  }
}

void newuiMessageBox::AddButton(const char *title, int slot, int key) {
  ASSERT(slot >= 0 && slot < NEWUI_MSGBOX_MAXBTNS);

  if (m_btn[slot].IsCreated()) {
    m_btn[slot].Destroy();
  }

  m_btn[slot].Create(this, slot, title, NEWUI_MSGBOX_BUTTONS_X,
                     NEWUI_MSGBOX_BUTTONS_Y2 + NEWUI_MSGBOX_BUTTONS_H2 * slot, NEWUI_BTNF_FRAMED);
  if (key) {
    m_btn[slot].SetHotkey(key);
  }
}

// grab the message box's sheet.
newuiSheet *newuiMessageBox::GetSheet() { return &m_sheet; }

// do user interface, return UID_OK or UID_CANCEL or UID_??? (UID_OK and UID_CANCEL are predefined)
int newuiMessageBox::DoUI() {
  int res;
  m_sheet.Realize();
  res = ::DoUI();
  m_sheet.Unrealize();

  return res;
}

void newuiMessageBox::OnDestroy() {
  int i;

  if (m_bkg) {
    Newui_resources.Free(m_bkg);
    m_bkg = NULL;
  }

  m_sheet.Destroy();

  for (i = 0; i < NEWUI_MSGBOX_MAXBTNS; i++) {
    if (m_btn[i].IsCreated()) {
      m_btn[i].Destroy();
    }
  }

  UIWindow::OnDestroy();
}

// overridable draws the window background before gadgets
void newuiMessageBox::OnDraw() {
  // draw background
  m_bkg->draw(0, 0);

  UITextItem title(MONITOR9_NEWUI_FONT, m_sheet.GetTitle(), NEWUI_MONITORFONT_COLOR);
  title.draw(NEWUI_MSGBOX_SHEET_X, NEWUI_MSGBOX_SHEET_Y - 16);

  // draws gadgets.
  UIWindow::OnDraw();
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS contains gadgets

// constants used in newuiSheet for gadget types. hidden from user.

#define GADGET_GROUP 0 // repositions column, row alignment
#define GADGET_HGROUP 1
#define GADGET_STATIC_TXT 2 // static text
#define GADGET_BUTTON 3     //	small mono state button
#define GADGET_CHECKBOX 4   // small two state button
#define GADGET_RADIO 5      // small two state radio
#define GADGET_LBUTTON 6    // large equivalents
#define GADGET_LCHECKBOX 7
#define GADGET_LRADIO 8
#define GADGET_SLIDER 9          // slider
#define GADGET_EDITBOX 10        // edit control
#define GADGET_EDITBOXPASS 11    // edit control
#define GADGET_EDITBOXNUM 12     // edit control
#define GADGET_LISTBOX 13        // listbox
#define GADGET_STATIC_BMP 14     // static bitmap
#define GADGET_COMBOBOX 15       // combo box
#define GADGET_HOTSPOT 16        // hotspot
#define GADGET_CHANGEABLE_TXT 17 // changeable text

newuiSheet::newuiSheet() {
  m_gadgetlist = NULL;
  m_gadgetlimit = 0;
  m_ngadgets = 0;
  m_realized = false;
}

void newuiSheet::Create(UIWindow *menu, const char *title, int n_items, int sx, int sy) {
  int i;

  if (title) {
    m_title = mem_strdup(title);
  } else {
    m_title = NULL;
  }
  m_gadgetlimit = n_items;
  m_ngadgets = 0;
  if (n_items) {
    m_gadgetlist = (newuiSheet::t_gadget_desc *)mem_malloc(n_items * sizeof(newuiSheet::t_gadget_desc));
  } else {
    m_gadgetlist = NULL;
  }

  m_parent = menu;
  m_sx = sx;
  m_sy = sy;
  m_realized = false;
  m_initial_focus_id = -1;

  for (i = 0; i < m_gadgetlimit; i++) {
    m_gadgetlist[i].obj.gadget = NULL;
    m_gadgetlist[i].title = NULL;
    m_gadgetlist[i].id = -1;
    m_gadgetlist[i].internal = NULL;
  }
}

// deallocates memory
void newuiSheet::Destroy() {
  Unrealize();

  newuiSheet::Reset();

  if (m_gadgetlist)
    mem_free(m_gadgetlist);
  if (m_title)
    mem_free(m_title);
  m_title = NULL;
  m_gadgetlist = NULL;
  m_ngadgets = 0;
}

void newuiSheet::Reset() {
  int i;

  ASSERT(!m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    if (m_gadgetlist[i].title) {
      mem_free(m_gadgetlist[i].title);
    }
    if (m_gadgetlist[i].internal) {
      if (m_gadgetlist[i].type == GADGET_LISTBOX) {
        newuiListBox *lb = (newuiListBox *)m_gadgetlist[i].internal;
        lb->Destroy();
        delete lb;
      } else if (m_gadgetlist[i].type == GADGET_SLIDER) {
        mem_free(m_gadgetlist[i].internal);
      } else if (m_gadgetlist[i].type == GADGET_EDITBOX || m_gadgetlist[i].type == GADGET_EDITBOXNUM ||
                 m_gadgetlist[i].type == GADGET_EDITBOXPASS) {
        mem_free(m_gadgetlist[i].internal);
      } else if (m_gadgetlist[i].type == GADGET_COMBOBOX) {
        newuiComboBox *cb = (newuiComboBox *)m_gadgetlist[i].internal;
        cb->Destroy();
        delete cb;
      } else if (m_gadgetlist[i].type == GADGET_CHANGEABLE_TXT) {
        mem_free(m_gadgetlist[i].parm.p);
      } else if (m_gadgetlist[i].type != GADGET_HOTSPOT) {
        Int3(); // get samir.
      }
    }
  }

  m_ngadgets = 0;
  m_initial_focus_id = -1;
}

//	set focus on this gadget specified by id upon realization.
void newuiSheet::SetInitialFocusedGadget(int16_t id) { m_initial_focus_id = id; }

// call this to initialize gadgets specified above in parent window
void newuiSheet::Realize() {
  int i, first_radio_index = -1, last_toggle_index = -1, gx = m_sx, gy = m_sy;
  newuiRadioButton *prev_radio = NULL;
  bool horizontal_align = false, hotspot_group = false, toggles_group = false;
  newuiEditBox *focus_edit = NULL;
  UIGadget *focus_gadget = NULL;

  if (m_realized)
    return;

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    newuiButton *btn;
    newuiCheckBox *cbox;
    newuiRadioButton *radio;
    newuiSlider *slider;
    newuiListBox *lb;
    newuiEditBox *edit;
    newuiComboBox *cb;
    newuiHotspot *hot;
    UIText *text;
    UIStatic *bmp;
    int16_t flags;
    bool bval;

    switch (desc->type) {
    case GADGET_HGROUP:
    case GADGET_GROUP:
      horizontal_align = (desc->type == GADGET_GROUP) ? false : true;
      gx = desc->parm.s[0] + m_sx;
      gy = desc->parm.s[1] + m_sy;
      if (desc->title) {
        text = new UIText;
        UITextItem item{MONITOR9_NEWUI_FONT, desc->title, NEWUI_MONITORFONT_COLOR};
        text->Create(m_parent, &item, gx, gy);
        desc->obj.gadget = text;

        // determine pixel offset to first control if we stuffed the offset into desc->id (-1 = default)
        if (desc->id != -1) {
          gy += text->H() + desc->id;
        } else {
          gy += text->H();
        }
      } else {
        desc->obj.gadget = NULL;
      }

      if (toggles_group && last_toggle_index != -1) {
        newuiSheet::t_gadget_desc *desc = &m_gadgetlist[last_toggle_index];
        desc->obj.chbox->SetFlag(UIF_GROUP_END);
      }

      prev_radio = NULL;
      hotspot_group = false;
      toggles_group = false;
      first_radio_index = -1;
      last_toggle_index = -1;
      break;

    case GADGET_STATIC_TXT: {
      text = new UIText;
      UITextItem item{MONITOR9_NEWUI_FONT, desc->title, NEWUI_MONITORFONT_COLOR};
      text->Create(m_parent, &item, gx, gy);
      if (horizontal_align)
        gx += text->W() + 2;
      else
        gy += text->H();
      desc->obj.gadget = text;
      break;
    }
    case GADGET_CHANGEABLE_TXT: {
      text = new UIText;
      UITextItem item{MONITOR9_NEWUI_FONT, (const char *)desc->parm.p, NEWUI_MONITORFONT_COLOR};
      text->Create(m_parent, &item, gx, gy);
      if (horizontal_align)
        gx += text->W() + 2;
      else
        gy += text->H();
      desc->obj.text = text;
      break;
    }

    case GADGET_STATIC_BMP: {
      bmp = new UIStatic;
      UIBitmapItem item{desc->parm.i};
      bmp->Create(m_parent, &item, gx, gy, 10, 10);
      if (horizontal_align)
        gx += bmp->W() + 2;
      else
        gy += bmp->H();
      desc->obj.gadget = bmp;
      break;
    }
    case GADGET_BUTTON:
      btn = new newuiButton;
      btn->Create(m_parent, desc->id, desc->title, gx, gy, desc->parm.i);
      if (horizontal_align)
        gx += btn->W() + 2;
      else
        gy += btn->H();
      desc->obj.button = btn;
      break;

    case GADGET_CHECKBOX:
      cbox = new newuiCheckBox;
      cbox->Create(m_parent, desc->id, desc->title, gx, gy, false);
      if (!toggles_group) {
        toggles_group = true;
        cbox->SetFlag(UIF_GROUP_START);
      }
      last_toggle_index = i;
      if (desc->parm.b)
        cbox->SetCheck(true);
      if (horizontal_align)
        gx += cbox->W() + 2;
      else
        gy += cbox->H();
      desc->obj.chbox = cbox;
      break;

    case GADGET_RADIO:
      if (first_radio_index == -1)
        first_radio_index = i;
      radio = new newuiRadioButton;
      radio->Create(m_parent, prev_radio, desc->id, desc->title, gx, gy, false);
      if (m_gadgetlist[first_radio_index].parm.i == (i - first_radio_index)) {
        radio->Activate();
      }
      if (horizontal_align)
        gx += radio->W() + 2;
      else
        gy += radio->H();
      desc->obj.radio = radio;
      prev_radio = radio;
      break;

    case GADGET_LBUTTON:
      btn = new newuiButton;
      btn->Create(m_parent, desc->id, desc->title, gx, gy, desc->parm.i | NEWUI_BTNF_LONG);
      if (horizontal_align)
        gx += btn->W() + 2;
      else
        gy += btn->H();
      desc->obj.button = btn;
      break;

    case GADGET_LCHECKBOX:
      cbox = new newuiCheckBox;
      cbox->Create(m_parent, desc->id, desc->title, gx, gy, true);
      if (!toggles_group) {
        toggles_group = true;
        cbox->SetFlag(UIF_GROUP_START);
      }
      last_toggle_index = i;
      if (desc->parm.b)
        cbox->SetCheck(true);
      if (horizontal_align)
        gx += cbox->W() + 2;
      else
        gy += cbox->H();
      desc->obj.chbox = cbox;
      break;

    case GADGET_LRADIO:
      if (first_radio_index == -1)
        first_radio_index = i;
      radio = new newuiRadioButton;
      radio->Create(m_parent, prev_radio, desc->id, desc->title, gx, gy, true);
      if (m_gadgetlist[first_radio_index].parm.i == (i - first_radio_index)) {
        radio->Activate();
      }
      if (horizontal_align)
        gx += radio->W() + 2;
      else
        gy += radio->H();
      desc->obj.radio = radio;
      prev_radio = radio;
      break;

    case GADGET_HOTSPOT:
      hot = new newuiHotspot;
      bval = desc->internal ? true : false;
      hot->Create(m_parent, desc->id, desc->title, gx, gy, desc->parm.s[0], desc->parm.s[1],
                  (bval && !hotspot_group)  ? UIF_GROUP_START
                  : (bval && hotspot_group) ? UIF_GROUP_END
                                            : 0);

      if (bval && !hotspot_group) {
        hotspot_group = true;
      } else if (bval && hotspot_group) {
        hotspot_group = false;
      }

      if (horizontal_align)
        gx += hot->W() + 2;
      else
        gy += hot->H();
      desc->obj.hot = hot;
      break;

    case GADGET_SLIDER:
      slider = new newuiSlider;
      slider->Create(m_parent, desc->id, desc->title, gx, gy, desc->parm.s[1]);
      slider->SetPos(desc->parm.s[0]);
      if (desc->internal) {
        slider->SetUnits((tSliderSettings *)desc->internal);
      }
      if (horizontal_align)
        gx += slider->W() + 4;
      else
        gy += slider->H() + 2;
      desc->obj.slider = slider;
      break;

    case GADGET_EDITBOX:
    case GADGET_EDITBOXPASS:
    case GADGET_EDITBOXNUM:
      ASSERT(desc->internal);
      edit = new newuiEditBox;
      flags = (desc->type == GADGET_EDITBOXPASS) ? UIED_PASSWORD : (desc->type == GADGET_EDITBOXNUM) ? UIED_NUMBERS : 0;

      // awful hack, but no more room to store passed in parameters.  note that we should never have an edit
      // box with a width greater than 4096 pixels in the lifetime of this system.
      edit->Create(m_parent, desc->id, desc->title, gx, gy, (desc->parm.s[0] & 0xfff), flags);
      edit->SetBufferLen(desc->parm.s[1]);
      edit->SetText((char *)desc->internal);

      if (desc->parm.s[0] & 0x1000) {
        edit->EnableOnQuickEscapeBehavior(true);
      }

      if (!focus_edit) {
        focus_edit = edit;
      }

      if (horizontal_align)
        gx += edit->W() + 4;
      else
        gy += edit->H() + 2;
      desc->obj.edit = edit;
      break;

    case GADGET_LISTBOX:
      lb = (newuiListBox *)desc->internal;
      ASSERT(lb);
      lb->Move(gx, gy, lb->W(), lb->H());
      m_parent->AddGadget(lb);
      if (horizontal_align)
        gx += lb->W() + 4;
      else
        gy += lb->H() + 2;
      desc->obj.lb = lb;
      break;

    case GADGET_COMBOBOX:
      cb = (newuiComboBox *)desc->internal;
      ASSERT(cb);
      cb->Move(gx, gy, cb->W(), cb->H());
      m_parent->AddGadget(cb);
      if (horizontal_align)
        gx += cb->W() + 4;
      else
        gy += cb->H() + 2;
      desc->obj.cb = cb;
      break;

    default:
      Int3();
    }
    desc->changed = false;

    if (desc->obj.gadget) {
      if (desc->obj.gadget->GetID() > -1 && desc->obj.gadget->GetID() == m_initial_focus_id) {
        focus_gadget = desc->obj.gadget;
      }
    }
  }

  if (toggles_group) {
    if (last_toggle_index != -1) {
      newuiSheet::t_gadget_desc *desc = &m_gadgetlist[last_toggle_index];
      desc->obj.chbox->SetFlag(UIF_GROUP_END);
    }
    toggles_group = false;
  }

  if (focus_gadget) {
    m_parent->SetFocusOnGadget(focus_gadget);
  } else if (focus_edit) {
    m_parent->SetFocusOnGadget(focus_edit);
    focus_edit->Activate();
  }

  m_realized = true;
}

// call this to release gadgets specified above in parent window
void newuiSheet::Unrealize() {
  int i, first_radio_index = -1;

  if (!m_realized)
    return;

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];

    if (desc->obj.gadget) {
      switch (desc->type) {
      case GADGET_HGROUP:
      case GADGET_GROUP:
        first_radio_index = -1;
        if (desc->title && desc->obj.gadget) {
          desc->obj.gadget->Destroy();
          delete desc->obj.gadget;
        }
        break;
      case GADGET_LCHECKBOX:
      case GADGET_CHECKBOX:
        desc->parm.b = desc->obj.chbox->IsChecked();
        desc->obj.chbox->Destroy();
        delete desc->obj.chbox;
        break;
      case GADGET_RADIO:
      case GADGET_LRADIO:
        if (first_radio_index == -1)
          first_radio_index = i;
        if (desc->obj.radio->IsActivated()) {
          m_gadgetlist[first_radio_index].parm.i = i - first_radio_index;
        }
        desc->obj.radio->Destroy();
        delete desc->obj.radio;
        break;
      case GADGET_SLIDER:
        desc->parm.s[0] = desc->obj.slider->GetPos();
        desc->obj.slider->Destroy();
        delete desc->obj.slider;
        break;

      case GADGET_HOTSPOT:
        desc->obj.hot->Destroy();
        delete desc->obj.hot;
        break;

      case GADGET_BUTTON:
      case GADGET_LBUTTON:
        desc->obj.button->Destroy();
        delete desc->obj.button;
        break;

      case GADGET_LISTBOX:
        m_parent->RemoveGadget(desc->obj.lb);
        break;

      case GADGET_COMBOBOX:
        m_parent->RemoveGadget(desc->obj.cb);
        break;

      case GADGET_EDITBOX:
      case GADGET_EDITBOXPASS:
      case GADGET_EDITBOXNUM:
        desc->obj.edit->GetText((char *)desc->internal, (desc->parm.s[1]) + 1);
        desc->obj.edit->Destroy();
        delete desc->obj.edit;
        break;

      case GADGET_CHANGEABLE_TXT:
        desc->obj.text->Destroy();
        delete desc->obj.gadget;
        break;

      default:
        desc->obj.gadget->Destroy();
        delete desc->obj.gadget;
      }

      desc->obj.gadget = NULL;
    }
  }

  m_realized = false;
}

//	refreshes gadget states with values passed to the pointers returned by the below functions.
void newuiSheet::UpdateChanges() {
  int i, first_radio_index = 0;

  ASSERT(m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    bool bval;
    int16_t sval;
    char sbuftest[EDIT_BUFLEN_MAX];

    switch (desc->type) {
    case GADGET_HGROUP:
    case GADGET_GROUP:
      first_radio_index = -1;
      break;

    case GADGET_LCHECKBOX:
    case GADGET_CHECKBOX:
      bval = desc->obj.chbox->IsChecked();
      if (desc->parm.b != bval) {
        desc->obj.chbox->SetCheck(desc->parm.b);
      }
      break;

    case GADGET_LRADIO:
    case GADGET_RADIO:
      // check if new index is same as current index.
      if (first_radio_index == -1)
        first_radio_index = i;
      if (m_gadgetlist[first_radio_index].parm.i == (i - first_radio_index)) {
        // possible request for change of radio button state here.
        bval = desc->obj.radio->IsActivated();
        if (!bval) {
          // wasn't active before so lets activate it now.
          desc->obj.radio->Activate();
        }
      }
      break;

    case GADGET_SLIDER:
      sval = desc->obj.slider->GetPos();
      if (desc->parm.s[0] != sval) {
        desc->obj.slider->SetPos(desc->parm.s[0]);
        desc->parm.s[0] = desc->obj.slider->GetPos();
      }
      break;

    case GADGET_EDITBOX:
    case GADGET_EDITBOXNUM:
    case GADGET_EDITBOXPASS:
      desc->obj.edit->GetText(sbuftest, EDIT_BUFLEN_MAX);
      if (strcmp(sbuftest, (char *)desc->internal) != 0) {
        desc->obj.edit->SetText((const char *) desc->internal);
      }
      break;

    case GADGET_CHANGEABLE_TXT: {
      UITextItem item{MONITOR9_NEWUI_FONT, (const char *)desc->parm.p, NEWUI_MONITORFONT_COLOR};
      desc->obj.text->SetTitle(&item);
      break;
    }
    }
    desc->changed = false;
  }
}

//	refreshes return values of gadgets, so they are accessible by the pointers returned by below functions
void newuiSheet::UpdateReturnValues() {
  int i, first_radio_index = -1;

  ASSERT(m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    bool bval;
    int16_t sval;
    char sbuftest[EDIT_BUFLEN_MAX];

    if (desc->obj.gadget) {
      switch (desc->type) {
      case GADGET_HGROUP:
      case GADGET_GROUP:
        first_radio_index = -1;
        break;
      case GADGET_LCHECKBOX:
      case GADGET_CHECKBOX:
        bval = desc->obj.chbox->IsChecked();
        if (desc->parm.b != bval) {
          desc->parm.b = bval;
          desc->changed = true;
        }
        break;
      case GADGET_RADIO:
      case GADGET_LRADIO:
        if (first_radio_index == -1)
          first_radio_index = i;
        bval = desc->obj.radio->IsActivated();
        if (bval && m_gadgetlist[first_radio_index].parm.i != (i - first_radio_index)) {
          m_gadgetlist[first_radio_index].parm.i = (i - first_radio_index);
          m_gadgetlist[first_radio_index].changed = true;
        }
        break;
      case GADGET_SLIDER:
        sval = desc->obj.slider->GetPos();
        if (desc->parm.s[0] != sval) {
          desc->parm.s[0] = sval;
          desc->changed = true;
        }
        break;

      case GADGET_EDITBOX:
      case GADGET_EDITBOXNUM:
      case GADGET_EDITBOXPASS:
        desc->obj.edit->GetText(sbuftest, EDIT_BUFLEN_MAX);
        if (strcmp(sbuftest, (char *)desc->internal) != 0) {
          strcpy((char *)desc->internal, sbuftest);
          desc->changed = true;
        }
        break;

      default:
        desc->changed = false;
      }
    }
  }
}

// call these functions to determine if a pointer's value has changed after call to UpdateReturnValues (internal)
bool newuiSheet::HasChanged(bool *bptr) {
  int i;

  ASSERT(m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    if (desc->obj.gadget) {
      switch (desc->type) {
      case GADGET_LCHECKBOX:
      case GADGET_CHECKBOX:
        if ((&desc->parm.b) == bptr) {
          return desc->changed;
        }
        break;
      }
    }
  }

  return false;
}

bool newuiSheet::HasChanged(int *iptr) {
  int i;

  ASSERT(m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    if (desc->obj.gadget) {
      switch (desc->type) {
      case GADGET_RADIO:
      case GADGET_LRADIO:
        if ((&desc->parm.i) == iptr) {
          return desc->changed;
        }
        break;
      }
    }
  }

  return false;
}

bool newuiSheet::HasChanged(int16_t *sptr) {
  int i;

  ASSERT(m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    if (desc->obj.gadget) {
      switch (desc->type) {
      case GADGET_SLIDER:
        if ((&desc->parm.s[0]) == sptr) {
          return desc->changed;
        }
        break;
      }
    }
  }

  return false;
}

bool newuiSheet::HasChanged(char *cptr) {
  int i;

  ASSERT(m_realized);

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];
    if (desc->obj.gadget) {
      switch (desc->type) {
      case GADGET_EDITBOX:
      case GADGET_EDITBOXNUM:
      case GADGET_EDITBOXPASS:
        if (desc->internal == cptr) {
          return desc->changed;
        }
        break;
      }
    }
  }

  return false;
}

UIGadget *newuiSheet::GetGadget(int16_t id) {
  int i;

  for (i = 0; i < m_ngadgets; i++) {
    newuiSheet::t_gadget_desc *desc = &m_gadgetlist[i];

    if (desc->obj.gadget && id == (int16_t)desc->obj.gadget->GetID()) {
      switch (desc->type) {
      case GADGET_STATIC_TXT:
        return desc->obj.gadget;
      case GADGET_STATIC_BMP:
        return desc->obj.gadget;
      case GADGET_BUTTON:
        return desc->obj.button;
      case GADGET_HOTSPOT:
        return desc->obj.hot;
      case GADGET_CHECKBOX:
        return desc->obj.chbox;
      case GADGET_RADIO:
        return desc->obj.radio;
      case GADGET_LBUTTON:
        return desc->obj.button;
      case GADGET_LCHECKBOX:
        return desc->obj.chbox;
      case GADGET_LRADIO:
        return desc->obj.radio;
      case GADGET_SLIDER:
        return desc->obj.slider;
      case GADGET_EDITBOX:
      case GADGET_EDITBOXPASS:
      case GADGET_EDITBOXNUM:
        return desc->obj.edit;
      case GADGET_LISTBOX:
        return desc->obj.lb;
      case GADGET_COMBOBOX:
        return desc->obj.cb;
      case GADGET_CHANGEABLE_TXT:
        return desc->obj.text;

      default:
        return desc->obj.gadget;
      }
    }
  }

  Int3();
  return NULL;
}

newuiSheet::t_gadget_desc *newuiSheet::AddGadget(int16_t id, int8_t type, const char *title) {
  int i = m_ngadgets;

  ASSERT(!m_realized);
  ASSERT(m_gadgetlimit > m_ngadgets);
  if (m_gadgetlimit <= m_ngadgets) {
    Error("Internal error in newuiSheet::AddGadget (ngadgets=%d, id=%d, type=%d, title=%s)\n", m_ngadgets, (int)id,
          (int)type, title ? title : "NULL");
    return NULL;
  }

  m_gadgetlist[i].id = id;
  m_gadgetlist[i].type = type;
  m_gadgetlist[i].title = title ? mem_strdup(title) : NULL;
  m_gadgetlist[i].obj.gadget = NULL;
  m_gadgetlist[i].parm.i = 0;
  m_gadgetlist[i].changed = false;
  m_gadgetlist[i].internal = NULL;

  m_ngadgets++;

  return &m_gadgetlist[i];
}

//	creates gadget list.
void newuiSheet::NewGroup(const char *title, int16_t x, int16_t y, tAlignment align, int16_t pix_offset) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(-1, (align == NEWUI_ALIGN_HORIZ) ? GADGET_HGROUP : GADGET_GROUP, title);
  gadget->parm.s[0] = x;
  gadget->parm.s[1] = y;
  gadget->id = pix_offset;
}

//	adds standard button to current group.
void newuiSheet::AddButton(const char *title, int16_t id, int16_t flags) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_BUTTON, title);
  gadget->parm.i = flags;
}

//	adds standard long button to current group.
void newuiSheet::AddLongButton(const char *title, int16_t id, int16_t flags) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_LBUTTON, title);
  gadget->parm.i = flags;
}

//	adds checkbox to current group.  initial state of checkbox can be set.
bool *newuiSheet::AddCheckBox(const char *title, bool init_state, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_CHECKBOX, title);
  gadget->parm.b = init_state;
  return &gadget->parm.b;
}

//	adds checkbox to current group.  initial state of checkbox can be set.
bool *newuiSheet::AddLongCheckBox(const char *title, bool init_state, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_LCHECKBOX, title);
  gadget->parm.b = init_state;
  return &gadget->parm.b;
}

// adds a radio button to current group.  initial state of radio may be set
int *newuiSheet::AddFirstRadioButton(const char *title, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_RADIO, title);
  gadget->parm.i = 0;
  return &gadget->parm.i;
}

// adds a radio button to current group.  initial state of radio may be set
void newuiSheet::AddRadioButton(const char *title, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_RADIO, title);
  gadget->parm.i = -1;
}

// adds a radio button to current group.  initial state of radio may be set
int *newuiSheet::AddFirstLongRadioButton(const char *title, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_LRADIO, title);
  gadget->parm.i = 0;
  return &gadget->parm.i;
}

// adds a radio button to current group.  initial state of radio may be set
void newuiSheet::AddLongRadioButton(const char *title, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_LRADIO, title);
  gadget->parm.i = -1;
}

// adds a slider, set the range for it too.
int16_t *newuiSheet::AddSlider(const char *title, int16_t range, int16_t init_pos, tSliderSettings *settings, int16_t id) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_SLIDER, title);
  gadget->parm.s[0] = init_pos;
  gadget->parm.s[1] = range;

  if (settings) {
    gadget->internal = mem_malloc(sizeof(tSliderSettings));
    memcpy(gadget->internal, settings, sizeof(tSliderSettings));
  } else {
    gadget->internal = NULL;
  }

  return &gadget->parm.s[0];
}

//	adds a static text item
void newuiSheet::AddText(const char *text, ...) {
  std::va_list arglist;
  char buf[512];
  int len;

  va_start(arglist, text);
  len = std::vsnprintf(buf, 512, text, arglist);
  va_end(arglist);

  newuiSheet::t_gadget_desc *gadget = AddGadget(-1, GADGET_STATIC_TXT, buf);

  gadget->parm.b = false; // means small text.
}

// adds a static bitmap
void newuiSheet::AddBitmap(int bm_handle) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(-1, GADGET_STATIC_BMP, NULL);
  gadget->parm.i = bm_handle;
}

//	adds a static text item
char *newuiSheet::AddChangeableText(int buflen) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(-1, GADGET_CHANGEABLE_TXT, NULL);
  gadget->internal = (void *)(size_t)buflen;
  gadget->parm.p = mem_malloc(buflen);
  return (char *)gadget->parm.p;
}

// adds a hotspot :(, should word wrap too.
void newuiSheet::AddHotspot(const char *title, int16_t w, int16_t h, int16_t id, bool group) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_HOTSPOT, title);
  gadget->parm.s[0] = w;
  gadget->parm.s[1] = h;
  gadget->internal = (void *)(group);
}

// adds a listbox
newuiListBox *newuiSheet::AddListBox(int16_t w, int16_t h, int16_t id, uint16_t flags) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_LISTBOX, NULL);
  newuiListBox *lb = new newuiListBox;
  lb->Create(m_parent, id, 0, 0, w, h, flags);
  m_parent->RemoveGadget(lb);
  gadget->internal = lb;
  return lb;
}

// adds a listbox
newuiComboBox *newuiSheet::AddComboBox(int16_t id, uint16_t flags) {
  newuiSheet::t_gadget_desc *gadget = AddGadget(id, GADGET_COMBOBOX, NULL);
  newuiComboBox *cb = new newuiComboBox;
  cb->Create(m_parent, id, 0, 0, flags);
  m_parent->RemoveGadget(cb);
  gadget->internal = cb;
  return cb;
}

// adds an edit box
char *newuiSheet::AddEditBox(const char *title, int16_t maxlen, int16_t w, int16_t id, int16_t flags, bool on_escape_quit) {
  int8_t type = GADGET_EDITBOX;
  if (flags & UIED_PASSWORD) {
    type = GADGET_EDITBOXPASS;
  } else if (flags & UIED_NUMBERS) {
    type = GADGET_EDITBOXNUM;
  }

  newuiSheet::t_gadget_desc *gadget = AddGadget(id, type, title);

  ASSERT(maxlen < EDIT_BUFLEN_MAX);
  ASSERT(w <= 0xfff);

  char *strbuf = (char *)mem_malloc(maxlen + 1);
  strbuf[0] = 0;
  gadget->internal = strbuf;
  gadget->parm.s[0] = (w & 0xfff);
  gadget->parm.s[1] = maxlen;

  // awful hack to store extra info into gadget structure. width should never exceed 4096
  if (on_escape_quit) {
    gadget->parm.s[0] |= (0x1000);
  }

  return (char *)gadget->internal;
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS simple buttons

newuiButton::newuiButton() {
  m_bkg = NULL;
  m_litbkg = NULL;
  m_text = NULL;
}

void newuiButton::Create(UIWindow *menu, int16_t id, const char *name, int16_t x, int16_t y, int16_t flags) {
  UITextItem item{""};
  UIButton::Create(menu, id, &item, x, y, 10, 8, flags | UIF_FIT);

  if (flags & NEWUI_BTNF_FRAMED) {
    ASSERT(!(flags & NEWUI_BTNF_LONG)); // remove this if art is added.
    if (!m_bkg) {
      m_bkg = Newui_resources.Load((flags & NEWUI_BTNF_LONG) ? NEWUI_LBTNFRAMED_FILE : NEWUI_BTNFRAMED_FILE);
    }
    if (!m_litbkg) {
      m_litbkg = Newui_resources.Load((flags & NEWUI_BTNF_LONG) ? NEWUI_LBTNLITFRAMED_FILE : NEWUI_BTNLITFRAMED_FILE);
    }
  }

  newuiButton::InitStates(name, (flags & NEWUI_BTNF_LONG) != 0);
}

void newuiTinyButton::Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y) {
  m_bkg = Newui_resources.Load(NEWUI_TINYBTN_FILE);
  m_litbkg = Newui_resources.Load(NEWUI_TINYBTNLIT_FILE);
  newuiButton::Create(wnd, id, name, x, y);
}

// override: called when resized or before drawing.
void newuiButton::OnFormat() {
  m_W = GetStateItem(m_State)->width();
  m_H = GetStateItem(m_State)->height();

  UIGadget::OnFormat();
}

void newuiButton::InitStates(const char *name, bool is_long, int16_t flags) {
  if (!m_bkg) {
    m_bkg = Newui_resources.Load(is_long ? NEWUI_LBTN_FILE : NEWUI_BTN_FILE);
  }

  if (!m_litbkg) {
    m_litbkg = Newui_resources.Load(is_long ? NEWUI_LBTNLIT_FILE : NEWUI_BTNLIT_FILE);
  }

  if (name && !m_text) {
    m_text = GadgetSmallText(name);
  }

  SetStateItem(UI_BTS_DISABLED, m_bkg);
  SetStateItem(UI_BTS_INACTIVE, m_bkg);
  SetStateItem(UI_BTS_HILITE, m_bkg);
  SetStateItem(UI_BTS_ACTIVATED, m_litbkg);

  OnFormat();
}

void newuiButton::OnDestroy() {
  if (m_bkg) {
    Newui_resources.Free(m_bkg);
    m_bkg = NULL;
  }
  if (m_litbkg) {
    Newui_resources.Free(m_litbkg);
    m_litbkg = NULL;
  }
  if (m_text) {
    delete m_text;
    m_text = NULL;
  }

  UIButton::OnDestroy();
}

void newuiButton::OnDraw() {
  uint8_t alpha = IsDisabled() ? 128 : 255;

  if (GetStateItem(m_State)) {
    GetStateItem(m_State)->set_alpha(alpha);
    GetStateItem(m_State)->draw(0, 0);
  }

  if (m_text) {
    m_text->set_alpha(alpha);
    m_text->draw((m_W - m_text->width()) / 2, (m_H - m_text->height()) / 2);
  }
}

void newuiButton::OnLostFocus() {
  if (m_text) {
    m_text->set_flags(0);
    m_text->set_color(NEWUI_GADGETFONT_COLOR);
  }
  UIButton::OnLostFocus();
}

void newuiButton::OnGainFocus() {
  if (m_text) {
    m_text->set_color(NEWUI_GADGETFONT_HICOLOR);
    m_text->set_flags(UISNAZZYTEXTF_BLINKING);
  }
  UIButton::OnGainFocus();
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS a large option button used in menus.

void newuiMenuOptionButton::Create(newuiMenu *menu, newuiMenuOptionButton *last, int16_t id, const char *name, int16_t x,
                                   int16_t y, bool mono_press) {
  m_bkg = Newui_resources.Load(NEWUI_LRGBTN_FILE);
  m_litbkg = Newui_resources.Load(NEWUI_LRGBTNLIT_FILE);
  m_text = GadgetLargeText(name);
  m_mono_press = mono_press;
  m_prev_btn = last;
  m_next_btn = NULL;
  if (m_prev_btn) {
    m_prev_btn->m_next_btn = this;
  }

  newuiButton::Create(menu, id, name, x, y);
}

void newuiMenuOptionButton::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN) {
    if ((m_State != UI_BTS_ACTIVATED) && PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my)) {
      m_State = UI_BTS_ACTIVATED;
      LOCK_FOCUS(this);
      //	mprintf(0, "mouse down in button gadget (%d)\n", GetID());
      if (m_mono_press) {
        //	mprintf(0, "selected button gadget (%d)\n", GetID());
        OnSelect();
        m_State = UI_BTS_HILITE;
      }
    }
  }
}

void newuiMenuOptionButton::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    if (m_State == UI_BTS_ACTIVATED) {
      if (PT_IN_GADGET(UIGadget::m_Wnd, this, UI_input.mx, UI_input.my)) {
        m_State = UI_BTS_HILITE;
        //	if (!m_mono_press) {
        OnSelect();
        //	}
      } else {
        m_State = UI_BTS_INACTIVE;
      }
    }
    UNLOCK_FOCUS(this);
  }
}

void newuiMenuOptionButton::OnKeyDown(int key) {
  if (key == KEY_DOWN || key == KEY_RIGHT) {
    if (m_next_btn) {
      if (UIGadget::IsLocked()) {
        UNLOCK_FOCUS(this);
      }
      m_Wnd->SetFocusOnGadget(m_next_btn, true);
    }
  } else if (key == KEY_UP || key == KEY_LEFT) {
    if (m_prev_btn) {
      if (UIGadget::IsLocked()) {
        UNLOCK_FOCUS(this);
      }
      m_Wnd->SetFocusOnGadget(m_prev_btn, true);
    }
  }
}

void newuiMenuOptionButton::OnKeyUp(int key) {}

//////////////////////////////////////////////////////////////////////////////
//	CLASS creates an arrow button that is sensitive to touch (when down, always select)

void newuiArrowButton::Create(UIWindow *wnd, int16_t id, int16_t type, const char *name, int16_t x, int16_t y) {
  switch (type) {
  case NEWUI_ARROW_LEFT:
    m_bkg = Newui_resources.Load(NEWUI_LARR_FILE);
    m_litbkg = Newui_resources.Load(NEWUI_LARRLIT_FILE);
    break;
  case NEWUI_ARROW_RIGHT:
    m_bkg = Newui_resources.Load(NEWUI_RARR_FILE);
    m_litbkg = Newui_resources.Load(NEWUI_RARRLIT_FILE);
    break;
  case NEWUI_ARROW_UP:
    m_bkg = Newui_resources.Load(NEWUI_UARR_FILE);
    m_litbkg = Newui_resources.Load(NEWUI_UARRLIT_FILE);
    break;
  case NEWUI_ARROW_DOWN:
    m_bkg = Newui_resources.Load(NEWUI_DARR_FILE);
    m_litbkg = Newui_resources.Load(NEWUI_DARRLIT_FILE);
    break;
  case NEWUI_ARROW_CBUP:
    m_bkg = Newui_resources.Load(NEWUI_UARRCB_FILE);
    m_litbkg = Newui_resources.Load(NEWUI_UARRLITCB_FILE);
    break;
  case NEWUI_ARROW_CBDOWN:
    m_bkg = Newui_resources.Load(NEWUI_DARRCB_FILE);
    m_litbkg = Newui_resources.Load(NEWUI_DARRLITCB_FILE);
    break;
  default:
    Int3();
  }

  newuiButton::Create(wnd, id, name, x, y);
  UIGadget::SetDatum(type);

  m_timer = 0.0f;
  m_selecttimer = 0.0f;
  m_hidden = false;
}

void newuiArrowButton::Show(bool show) { m_hidden = !show; }

void newuiArrowButton::OnMouseBtnDown(int btn) {
  bool mouse_in_gadget =
      PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my); // DAJ Added to keep stray clicks from changing values

  if (btn == UILMSEBTN && mouse_in_gadget) {
    if (m_State == UI_BTS_HILITE) {
      if (!m_hidden) {
        m_State = UI_BTS_ACTIVATED;
        LOCK_FOCUS(this);
        m_timer = 0.0f;
      }
    }
    if (m_State == UI_BTS_ACTIVATED) {
      // this is so that select messages get set at correct times
      if (m_hidden) {
        m_State = UI_BTS_HILITE;
        UNLOCK_FOCUS(this);
      } else {
        if (m_timer >= m_selecttimer) {
          if (m_selecttimer == 0.0f) {
            m_selecttimer = 0.5f;
          } else if (m_selecttimer == 0.5f) {
            m_selecttimer = 0.050f;
          }
          OnSelect(); // DAJ moved from above the m_selecttimer set since this is recursive
          m_timer = 0.0f;
        }
        m_timer += UIFrameTime;
      }
    }
  }
}

void newuiArrowButton::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    if (m_State == UI_BTS_ACTIVATED) {
      if (PT_IN_GADGET(UIGadget::m_Wnd, this, UI_input.mx, UI_input.my)) {
        m_State = UI_BTS_HILITE;
      } else {
        m_State = UI_BTS_INACTIVE;
      }
    }
    UNLOCK_FOCUS(this);

    m_selecttimer = 0.0f;
    m_timer = 0.0f;
  }
}

void newuiArrowButton::OnDraw() {
  if (m_hidden)
    return;

  newuiButton::OnDraw();
}

//////////////////////////////////////////////////////////////////////////////
//	CLASS a new check box: note that newuiButton and UICheckBox will share the same UIButton base
//	since bott newuiButton and UICheckBox inherit UIButton virtually.

newuiCheckBox::newuiCheckBox() {}

void newuiCheckBox::Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y, bool is_long) {
  m_bkg = Newui_resources.Load(is_long ? NEWUI_LCHKBTN_FILE : NEWUI_CHKBTN_FILE);
  m_litbkg = Newui_resources.Load(is_long ? NEWUI_LCHKBTNLIT_FILE : NEWUI_CHKBTNLIT_FILE);

  UITextItem item{""};
  UICheckBox::Create(wnd, id, &item, x, y, 10, 8, UIF_FIT);
  newuiButton::InitStates(name, is_long);
}

// this will use the newuiButton drawing scheme
void newuiCheckBox::OnDraw() { newuiButton::OnDraw(); }

//////////////////////////////////////////////////////////////////////////////
//	CLASS a new radio button

newuiRadioButton::newuiRadioButton() {}

void newuiRadioButton::Create(UIWindow *wnd, UIRadioButton *prev_rb, int16_t id, const char *name, int16_t x, int16_t y,
                              bool is_long) {
  m_bkg = Newui_resources.Load(is_long ? NEWUI_LBTN_FILE : NEWUI_BTN_FILE);
  m_litbkg = Newui_resources.Load(is_long ? NEWUI_LCHKBTNLIT_FILE : NEWUI_CHKBTNLIT_FILE);

  UITextItem item{""};
  UIRadioButton::Create(wnd, prev_rb, id, &item, x, y, 10, 8, UIF_FIT);
  newuiButton::InitStates(name, is_long);
}

// this will use the newuiButton drawing scheme
void newuiRadioButton::OnDraw() { newuiButton::OnDraw(); }

//////////////////////////////////////////////////////////////////////////////
//	CLASS a new slider.

newuiSlider::newuiSlider() {
  m_pos = m_unitrange = 0;
  m_bar_bmp = NULL;
  m_title = NULL;
}

void newuiSlider::Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y, int16_t range) {
  ASSERT(range > 0);

  if (name) {
    m_title = MonitorSmallText(name);
  }

  m_pos = range;
  m_unitrange = range;
  m_bar_bmp = Newui_resources.Load(NEWUI_SLIDER_FILE);

  UIGadget::Create(wnd, id, x, y, 10, 10, 0);

  m_unit_settings.type = -1;
}

void newuiSlider::Offset(int16_t offs) { newuiSlider::SetPos(m_pos + offs); }

void newuiSlider::SetPos(int16_t pos) {
  if (pos < 0)
    pos = 0;
  if (pos > m_unitrange)
    pos = m_unitrange;
  m_pos = pos;
}

void newuiSlider::SetRange(int16_t range) { m_unitrange = range; }

// when gadget is added to a window (AddGadget is called)
void newuiSlider::OnAttachToWindow() {
  int16_t bx = m_X, by = m_Y;

  if (m_title) {
    by += m_title->height() + 5;
    bx += 2;
  }

  m_minus_btn.Create(m_Wnd, -1, NEWUI_ARROW_LEFT, NULL, bx, by);
  m_minus_btn.SetFlag(UIF_NOTIFYMASTERSEL);
  AttachSlaveGadget(&m_minus_btn);
  m_plus_btn.Create(m_Wnd, -1, NEWUI_ARROW_RIGHT, NULL, bx + m_bar_bmp->width() - 24, by);
  m_plus_btn.SetFlag(UIF_NOTIFYMASTERSEL);
  AttachSlaveGadget(&m_plus_btn);
}

// when gadget is detached from window
void newuiSlider::OnDetachFromWindow() {
  if (m_plus_btn.IsCreated()) {
    DetachSlaveGadget(&m_plus_btn);
    m_plus_btn.Destroy();
  }
  if (m_minus_btn.IsCreated()) {
    DetachSlaveGadget(&m_minus_btn);
    m_minus_btn.Destroy();
  }
}

void newuiSlider::SetUnits(tSliderSettings *settings) {
  if (settings == NULL) {
    m_unit_settings.type = -1;
  } else {
    memcpy(&m_unit_settings, settings, sizeof(m_unit_settings));
  }
}

void newuiSlider::OnFormat() {
  if (m_bar_bmp) {
    m_W = m_bar_bmp->width();
    m_H = m_bar_bmp->height();
    if (m_title) {
      m_H += m_title->height();
    }
  }
}

void newuiSlider::OnLostFocus() {
  if (m_title) {
    m_title->set_flags(0);
  }
}

void newuiSlider::OnGainFocus() {
  if (m_title) {
    m_title->set_flags(UISNAZZYTEXTF_BLINKING);
  }
}

// override: behavior when key pressed.
void newuiSlider::OnKeyDown(int key) {
  if (key == KEY_LEFT) {
    newuiSlider::Offset(-1);
    UIGadget::OnSelect();
  }
  if (key == KEY_RIGHT) {
    newuiSlider::Offset(1);
    UIGadget::OnSelect();
  }
}

// override: behavior when key released.
void newuiSlider::OnKeyUp(int key) {}

void newuiSlider::OnDraw() {
  int ox = 0, oy = 0;
  int x, lx;
  float percent_full, delta_g, green_intensity;

  percent_full = (float)m_pos / (float)m_unitrange;

  // draw units value if available
  if (m_unit_settings.type > -1) {
    char str[8];

    switch (m_unit_settings.type) {
    case SLIDER_UNITS_INT:
      snprintf(str, sizeof(str), "%d",
               m_unit_settings.min_val.i +
                   (int)floor((m_unit_settings.max_val.i - m_unit_settings.min_val.i) * percent_full + 0.5f));
      break;
    case SLIDER_UNITS_FLOAT:
      snprintf(str, sizeof(str), "%.2f",
               m_unit_settings.min_val.f + (m_unit_settings.max_val.f - m_unit_settings.min_val.f) * percent_full);
      break;
    case SLIDER_UNITS_PERCENT:
      snprintf(str, sizeof(str), "%d%%", (int)((percent_full * 100.0f) + 0.5f));
      break;
    default:
      Int3();
      str[0] = 0;
    }

    UITextItem value_txt(MONITOR9_NEWUI_FONT, str, NEWUI_MONITORFONT_COLOR);
    value_txt.draw(ox + m_W - value_txt.width() - 1, oy + 1);
  }

  // draw graphic bar first
  if (m_title) {
    m_title->draw(ox, oy + 1);
    oy += m_title->height() + 2;
  }

  // draw bar frame
  if (m_bar_bmp) {
    m_bar_bmp->draw(ox, oy);
    ox += 20; // move to where bar will be filled in.
    oy += 2;
  }

  // draw slider bar now.
  int width = m_bar_bmp->width() - 42;
  int height = m_bar_bmp->height() - 6;

  lx = (percent_full * width) + ox;
  delta_g = (lx - ox) ? (percent_full * 255.0f) / (lx - ox) : 0.0f;
  green_intensity = 0.0f;

  for (x = ox; x < lx; x++) {
    ui_DrawLine(GR_RGB(0, green_intensity, 0), x, oy + 1, x, oy + height - 1);
    green_intensity += delta_g;
  }
}

void newuiSlider::OnDestroy() {
  if (m_bar_bmp) {
    Newui_resources.Free(m_bar_bmp);
    m_bar_bmp = NULL;
  }
  if (m_title) {
    delete m_title;
    m_title = NULL;
  }
}

// this function will handle when an arrow button was pressed
void newuiSlider::OnNotifySelect(UIGadget *g) {
  switch (g->GetDatum()) {
  case NEWUI_ARROW_LEFT:
    newuiSlider::Offset(-1);
    break;
  case NEWUI_ARROW_RIGHT:
    newuiSlider::Offset(1);
    break;
  }

  UIGadget::OnSelect();
}

//	CLASS a new listbox. uses less memory than the old listbox hopefully.

newuiListBox::newuiListBox() {
  m_ItemList = NULL;
  m_Virt2Real = NULL;
  m_Real2Virt = NULL;
  selectchange_fn = NULL;
  selectchange_id_fn = NULL;
  m_callbackptr = NULL;
  m_NumItems = 0;
  m_SelectedIndex = -1;
  m_Index = 0;
  m_NumVisibleItems = 0;
  m_mse_clicked = false;
  m_nclicks = 0;
  m_mse_x = 0;
  m_mse_y = 0;
  m_click_time = 0.0f;
}

void newuiListBox::Create(UIWindow *wnd, int16_t id, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t flags) {
  m_ItemList = NULL;
  m_Virt2Real = NULL;
  m_Real2Virt = NULL;
  selectchange_fn = NULL;
  selectchange_id_fn = NULL;
  m_callbackptr = NULL;
  m_NumItems = 0;
  m_SelectedIndex = -1;
  m_Index = 0;
  m_NumVisibleItems = 0;
  m_boffs = 12;
  m_nclicks = 0;
  m_mse_clicked = false;
  m_click_time = 0.0f;

  m_pieces[N_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_N_FILE);
  m_pieces[NE_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_NE_FILE);
  m_pieces[E_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_E_FILE);
  m_pieces[SE_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_SE_FILE);
  m_pieces[S_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_S_FILE);
  m_pieces[SW_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_SW_FILE);
  m_pieces[W_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_W_FILE);
  m_pieces[NW_PIECE_IDX] = Newui_resources.Load(NEWUI_LB_NW_FILE);

  // determine true width and height (snap width and height to 32 pixel boundaries
  int16_t p_w = LB_PIECE_WIDTH, p_h = LB_PIECE_HEIGHT;
  int16_t t_width = (w / p_w);
  int16_t t_height = (h / p_h);
  if (w % p_w)
    t_width++;
  if (h % p_h)
    t_height++;
  w = t_width * p_w;
  h = t_height * p_h;

  UIGadget::Create(wnd, id, x, y, w, h, flags);
}

// functions to add or remove items,
void newuiListBox::AddItem(const char *name) {
  char **temp;
  int i;
  int *tempvirt2real, *tempreal2virt;
  int real_index = -1;

  if (m_Flags & UILB_NOSORT) {
    // insert without sort

    if ((m_NumItems % LISTBOX_BUFFER_SIZE) == 0) {
      //	dynamically allocated memory for listbox, expand as needed.
      temp = (char **)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(char *));
      tempvirt2real = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));
      tempreal2virt = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));

      if (m_ItemList) {
        for (i = 0; i < m_NumItems; i++) {
          temp[i] = m_ItemList[i];
          tempvirt2real[i] = m_Virt2Real[i];
          tempreal2virt[i] = m_Real2Virt[i];
        }

        mem_free(m_ItemList);
        mem_free(m_Virt2Real);
        mem_free(m_Real2Virt);
      }
      m_ItemList = temp;
      m_Virt2Real = tempvirt2real;
      m_Real2Virt = tempreal2virt;
    }

    real_index = m_NumItems;
  } else {
    // only text item listboxes!

    // insert with sorting
    if ((m_NumItems % LISTBOX_BUFFER_SIZE) == 0) {
      //	dynamically allocated memory for listbox, expand as needed.
      int oidx = 0, cidx = 0;
      int pidx = 0;
      int result;

      temp = (char **)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(char *));
      tempvirt2real = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));
      tempreal2virt = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));

      real_index = -1;

      if (m_ItemList) {
        while (oidx <= m_NumItems) {
          if (oidx == m_NumItems) {
            if (real_index == -1) {
              real_index = oidx;
            } else {
              temp[cidx] = m_ItemList[pidx];
              tempreal2virt[cidx] = m_Real2Virt[pidx];
            }
            oidx++;
            continue;
          }

          if (m_Flags & UILB_CASESENSITIVE)
            result = strcmp(m_ItemList[cidx], name);
          else
            result = stricmp(m_ItemList[cidx], name);
          if (result < 0) {
            // copy old
            temp[cidx] = m_ItemList[pidx];
            tempreal2virt[cidx] = m_Real2Virt[pidx];
            cidx++;
            pidx++;
          } else if (result >= 0) {
            // see if we need to insert, if not just keep copying
            if (real_index == -1) {
              real_index = cidx;
              cidx++;
            } else {
              temp[cidx] = m_ItemList[pidx];
              tempreal2virt[cidx] = m_Real2Virt[pidx];
              cidx++;
              pidx++;
            }
          }
          oidx++;
        }
        ASSERT(real_index != -1);

        // now we need to fix m_Virt2Real to represent the new structure,
        // all values>=real_index must be incremented
        for (oidx = 0; oidx <= m_NumItems; oidx++) {
          if (oidx < m_NumItems) {
            tempvirt2real[oidx] = m_Virt2Real[oidx];

            // if(oidx!=real_index){
            if (tempvirt2real[oidx] >= real_index)
              tempvirt2real[oidx]++;
          }
        }

        mem_free(m_ItemList);
        mem_free(m_Virt2Real);
        mem_free(m_Real2Virt);
      } else {
        real_index = 0;
      }

      m_ItemList = temp;
      m_Virt2Real = tempvirt2real;
      m_Real2Virt = tempreal2virt;
    } else {
      // find where to insert, without allocating memory
      int oidx = 0, cidx = 0;
      real_index = -1;
      int result;

      int old_r2v;
      char *old_item = NULL;

      while (oidx <= m_NumItems) {

        if (oidx == m_NumItems) {
          // we're past the slot of the old buffer
          if (real_index == -1) {
            // we haven't set the real index yet, so it has to go here
            real_index = m_NumItems;
          } else {
            // the real index has been set, we're still pulling back
            m_Real2Virt[cidx] = old_r2v;
            m_ItemList[cidx] = old_item;
          }
          oidx++;
          continue;
        } else {
          if (m_Flags & UILB_CASESENSITIVE)
            result = strcmp(m_ItemList[cidx], name);
          else
            result = stricmp(m_ItemList[cidx], name);
        }

        if (result < 0) {
          // we haven't gotten to the string yet, keep as they are
          cidx++;
        } else if (result >= 0) {
          // see if we need to insert, if not just keep copying
          if (real_index == -1) {
            // we need to insert here
            real_index = cidx;
            old_item = m_ItemList[cidx];
            old_r2v = m_Real2Virt[cidx];
            cidx++;
          } else {
            // old_item and old_r2v should be set!
            ASSERT(old_item);
            char *oi;
            int or2v;

            or2v = m_Real2Virt[cidx];
            oi = m_ItemList[cidx];

            m_Real2Virt[cidx] = old_r2v;
            m_ItemList[cidx] = old_item;
            old_r2v = or2v;
            old_item = oi;

            cidx++;
          }
        }

        // continue on
        oidx++;
      }

      ASSERT(real_index != -1);

      // now we need to fix m_Virt2Real to represent the new structure,
      // all values>=real_index must be incremented
      cidx = 0;
      for (oidx = 0; oidx <= m_NumItems; oidx++) {
        if (oidx != real_index) {
          if (m_Virt2Real[cidx] >= real_index)
            m_Virt2Real[cidx]++;
          cidx++;
        }
      }
    }
  }

  //	copy item passed to list.
  m_ItemList[real_index] = mem_strdup(name);
  m_Virt2Real[m_NumItems] = real_index;
  m_Real2Virt[real_index] = m_NumItems;
  m_NumItems++;

  if (real_index <= m_SelectedIndex) {
    // adjust selected index
    if (m_SelectedIndex < m_NumItems - 1)
      m_SelectedIndex++;
  }
}

void newuiListBox::RemoveItem(const char *name) {
  int i, j, found = -1;

  for (i = 0; i < m_NumItems; i++) {
    int res;
    res = (m_Flags & UILB_CASESENSITIVE) ? stricmp(m_ItemList[i], name) : strcmp(m_ItemList[i], name);
    if (res == 0) {
      found = i;
      mem_free(m_ItemList[found]);
      m_ItemList[found] = NULL;
      break;
    }
  }
  if (found == -1) {
    mprintf(0, "newuiListBox:: Didn't find item to remove!\n");
    return;
  }

  // found is the real index to remove
  // go through virt2real and subtract one from values of found or higher
  // go through real2virt and move everything from index found on down, and subtract
  //	1 from those with value of found or higher
  int real_index = found;              // index to remove
  int virt_index = m_Real2Virt[found]; // index to remove
  int real_thresh = virt_index;
  int virt_thresh = real_index;

  for (j = 0; j < (m_NumItems - 1); j++) {
    if (j >= real_index) {
      m_ItemList[j] = m_ItemList[j + 1];
      m_Real2Virt[j] = m_Real2Virt[j + 1];
    }

    if (j >= virt_index) {
      m_Virt2Real[j] = m_Virt2Real[j + 1];
    }

    if (m_Real2Virt[j] >= real_thresh)
      m_Real2Virt[j]--;

    if (m_Virt2Real[j] >= virt_thresh)
      m_Virt2Real[j]--;
  }
  m_NumItems--;

  if (real_index <= m_SelectedIndex) {
    // adjust selected index
    if (m_SelectedIndex > 0)
      m_SelectedIndex--;
  }
}

void newuiListBox::RemoveAll() {
  m_SelectedIndex = -1;

  if (m_ItemList) {
    int i;
    for (i = 0; i < m_NumItems; i++) {
      if (m_ItemList[i])
        mem_free(m_ItemList[i]);
    }
    mem_free(m_ItemList);
  }

  if (m_Virt2Real)
    mem_free(m_Virt2Real);

  if (m_Real2Virt)
    mem_free(m_Real2Virt);

  m_ItemList = NULL;
  m_Virt2Real = NULL;
  m_Real2Virt = NULL;
  m_Index = m_NumItems = 0;
}

// item information
int newuiListBox::GetCurrentIndex() {
  if (m_NumItems == 0)
    return 0;

  if (m_SelectedIndex < 0)
    return m_SelectedIndex;

  if (!m_Real2Virt)
    return 0;

  int virt_index = m_Real2Virt[m_SelectedIndex];
  ASSERT(virt_index >= 0 && virt_index < m_NumItems);
  return virt_index;
}

void newuiListBox::SetCurrentIndex(int index) {
  if (m_NumItems == 0)
    return;

  if (index >= 0 && index < m_NumItems) {
    int real_index = m_Virt2Real[index], old_index = m_SelectedIndex;
    int i = 0, y;

    ASSERT(real_index >= 0 && real_index < m_NumItems);
    m_SelectedIndex = real_index;

    // determine how many items fit in a listbox the long way.
    for (i = 0, y = m_boffs; i < m_NumItems; i++) {
      UITextItem item(m_ItemList[i]);
      item.set_font(MONITOR9_NEWUI_FONT);

      y += item.height();
      if (y > (m_H - m_boffs - item.height())) {
        i++;
        break;
      }
    }

    if (m_SelectedIndex < m_Index) {
      m_Index = m_SelectedIndex;
    }
    if (m_SelectedIndex >= (m_Index + i)) {
      m_Index = m_SelectedIndex - i + 1;
    }
    if (m_Index < 0) {
      m_Index = 0;
    }

    // call callbacks if selection really changed.
    if (old_index != m_SelectedIndex) {
      if (selectchange_fn)
        (*selectchange_fn)(index);
      if (selectchange_id_fn)
        (*selectchange_id_fn)(GetID(), m_callbackptr);
    }
  }
}

void newuiListBox::SetInternalCurrentIndex(int index) {}

bool newuiListBox::GetCurrentItem(char *buffer, int buflen) {
  return newuiListBox::GetItem(m_Real2Virt[m_SelectedIndex], buffer, buflen);
}

bool newuiListBox::GetItem(int index, char *buffer, int buflen) {
  if (m_NumItems == 0) {
    return false;
    *buffer = 0;
  }

  if (index >= 0 && index < m_NumItems) {
    int real_index = m_Virt2Real[index];
    ASSERT(real_index >= 0 && real_index < m_NumItems);
    strncpy(buffer, m_ItemList[real_index], buflen - 1);
    buffer[buflen - 1] = 0;
    return true;
  }

  return false;
}

bool newuiListBox::SetCurrentItem(const char *name) {
  int i, found = 0;

  for (i = 0; i < m_NumItems; i++) {
    int res = (m_Flags & UILB_CASESENSITIVE) ? stricmp(m_ItemList[i], name) : strcmp(m_ItemList[i], name);
    if (res == 0) {
      SetCurrentIndex(m_Real2Virt[i]);
      found = 1;
      break;
    }
  }

  if (!found) {
    mprintf(0, "newuiListBox::SelectItem item not found!\n");
    return false;
  }

  return true;
}

// set callbacks
void newuiListBox::SetSelectChangeCallback(void (*fn)(int)) { selectchange_fn = fn; }

void newuiListBox::SetSelectChangeCallback(void (*fn)(int, void *), void *ptr) {
  selectchange_id_fn = fn;
  m_callbackptr = ptr;
}

// override: behavior when gadget loses input focus.
void newuiListBox::OnLostFocus() {}

// override: behavior when gadget gains input focus.
void newuiListBox::OnGainFocus() {}

// behavior when gadget is being drawn.
void newuiListBox::OnDraw() {
  int t_width = (m_W / 32), tx, x;
  int t_height = (m_H / 32), ty, y;

  //	draw tiles.
  tx = x = 0;
  ty = y = 0;

  // top row.
  m_pieces[NW_PIECE_IDX]->draw(x, y);
  tx++;
  x += LB_PIECE_WIDTH;
  while (tx++ < (t_width - 1)) {
    m_pieces[N_PIECE_IDX]->draw(x, y);
    x += LB_PIECE_WIDTH;
  }
  m_pieces[NE_PIECE_IDX]->draw(x, y);
  tx++;
  x = 0;
  y += LB_PIECE_HEIGHT;
  ty++;

  //	mid rows.
  while (ty++ < (t_height - 1)) {
    m_pieces[W_PIECE_IDX]->draw(x, y);
    x += LB_PIECE_WIDTH;
    tx = 1;
    while (tx++ < (t_width - 1)) {
      x += LB_PIECE_WIDTH;
    }
    m_pieces[E_PIECE_IDX]->draw(x, y);
    tx++;
    x = 0;
    y += LB_PIECE_HEIGHT;
  }

  //	bottom row.
  m_pieces[SW_PIECE_IDX]->draw(x, y);
  x += LB_PIECE_WIDTH;
  tx = 1;
  while (tx++ < (t_width - 1)) {
    m_pieces[S_PIECE_IDX]->draw(x, y);
    x += LB_PIECE_WIDTH;
  }
  m_pieces[SE_PIECE_IDX]->draw(x, y);
  tx++;
  ty++;

  // draw text?
  int i;
  uint8_t alpha = 255;
  bool auto_select = ((m_Flags & UILB_AUTOSELECT) > 0);
  bool use_scroll = true;

  ui_SetTextClip(m_boffs, m_boffs, m_W - m_boffs - m_up_btn.W(), m_H - m_boffs);

  for (i = m_Index, y = m_boffs; i < m_NumItems; i++) {
    UITextItem item(m_ItemList[i]);
    item.set_font(MONITOR9_NEWUI_FONT);

    if (m_mse_clicked) {
      if (m_mse_y >= y && m_mse_y <= (y + item.height() - 1)) {
        if (m_mse_x > m_boffs && m_mse_x < (m_W - m_boffs - 12)) {
          newuiListBox::SetCurrentIndex((m_Real2Virt) ? m_Real2Virt[i] : 0);
          //	item.set_font(GADGET9_NEWUI_FONT);
        }
      }
    }

    y += item.height();
    if (y > (m_H - m_boffs - item.height())) {
      break;
    }
  }

  m_mse_clicked = false;

  if (m_SelectedIndex == -1 && m_NumItems > 0) {
    newuiListBox::SetCurrentIndex(m_Real2Virt[0]);
  }

  for (i = m_Index, y = m_boffs; i < m_NumItems; i++) {
    UITextItem item(m_ItemList[i]);

    item.set_font(MONITOR9_NEWUI_FONT);
    item.set_color(NEWUI_MONITORFONT_COLOR);

    if (m_SelectedIndex == i) {
      // draw a bar?
      ddgr_color bar_color;
      //	item.set_font(GADGET9_NEWUI_FONT);
      //	item.set_color(NEWUI_GADGETFONT_COLOR);
      bar_color = m_infocus ? GR_RGB(0, 64, 0) : GR_RGB(0, 32, 0);
      ui_DrawRect(bar_color, m_boffs, y, m_W - m_boffs - m_up_btn.W(), y + item.height());
    }

    if (!m_infocus) {
      item.set_alpha(192);
    }

    item.draw(m_boffs, y);

    y += item.height();
    if (y > (m_H - m_boffs - item.height())) {
      i++;
      break;
    }
  }

  if (m_NumItems) {
    if (use_scroll && auto_select) {
      if (m_SelectedIndex < m_Index)
        newuiListBox::SetCurrentIndex(m_Real2Virt[m_Index]);
      if (m_SelectedIndex > i)
        newuiListBox::SetCurrentIndex(m_Real2Virt[i]);
    }
  }

  m_NumVisibleItems = (i - m_Index);

  ui_ResetTextClip();
}

//	behavior when key is pressed.
void newuiListBox::OnKeyDown(int key) {
  if (key == KEY_SPACEBAR) {

  } else {
    int new_selected_index = m_SelectedIndex;

    if (key == KEY_UP) {
      if (m_SelectedIndex > 0) {
        new_selected_index = m_SelectedIndex - 1;
      }
    } else if (key == KEY_DOWN) {
      if (m_SelectedIndex < (m_NumItems - 1)) {
        new_selected_index = m_SelectedIndex + 1;
      }
    } else if (key == KEY_PAGEUP) {
      if (m_SelectedIndex != m_Index) {
        new_selected_index = m_Index;
      } else {
        new_selected_index = m_SelectedIndex - m_NumVisibleItems;
        if (new_selected_index < 0)
          new_selected_index = 0;
      }
    } else if (key == KEY_PAGEDOWN) {
      if (m_SelectedIndex != (m_Index + m_NumVisibleItems - 1)) {
        new_selected_index = (m_Index + m_NumVisibleItems - 1);
      } else {
        new_selected_index = m_SelectedIndex + m_NumVisibleItems;
        if (new_selected_index >= m_NumItems)
          new_selected_index = m_NumItems - 1;
      }
    }
    newuiListBox::SetCurrentIndex((m_Real2Virt) ? m_Real2Virt[new_selected_index] : 0);
  }
}

// behavior when key is released.
void newuiListBox::OnKeyUp(int key) {}

// behavior when mouse button is pressed.
void newuiListBox::OnMouseBtnDown(int btn) {
  bool mouse_in_gadget = PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my);

  if (btn == UILMSEBTN && mouse_in_gadget) {
    float time_delta = 0.0f, old_click_time;
    m_mse_x = SCREEN_TO_GAD_X(this, UI_input.mx);
    m_mse_y = SCREEN_TO_GAD_Y(this, UI_input.my);
    m_mse_clicked = true;

    old_click_time = m_click_time;
    m_click_time = UI_TIME();

    time_delta = m_click_time - old_click_time;
    if (time_delta > UI_DBLCLICK_DELAY) {
      m_nclicks = 0;
    }

    if (m_nclicks == 0) {
      LOCK_FOCUS(this);
      m_nclicks = 1;
      //	mprintf(0, "click 1\n");
    } else if (m_nclicks == 2) {
      //	mprintf(0, "click 2\n");
      LOCK_FOCUS(this);
      if (((m_click_time - old_click_time) < UI_DBLCLICK_DELAY)) {
        if (abs(m_mse_x - m_last_mse_x) < UI_DBLCLICK_MSEDELTA && abs(m_mse_y - m_last_mse_y) < UI_DBLCLICK_MSEDELTA) {
          if (m_NumItems > 0 && m_SelectedIndex > -1) {
            int y, i;
            for (i = m_Index, y = m_boffs; i < m_NumItems; i++) {
              UITextItem item(m_ItemList[i]);
              item.set_font(MONITOR9_NEWUI_FONT);

              if (m_mse_y >= y && m_mse_y <= (y + item.height() - 1)) {
                if (m_mse_x > m_boffs && m_mse_x < (m_W - m_boffs - 12)) {
                  OnSelect();
                  //	mprintf(0, "select!\n");
                  m_nclicks = 0;
                  break;
                }
              }
              y += item.height();
              if (y > (m_H - m_boffs - item.height())) {
                break;
              }
            }
            UNLOCK_FOCUS(this);
          }
        }
      }
      if (m_nclicks == 2)
        m_nclicks = 3;
    }
    m_last_mse_x = m_mse_x;
    m_last_mse_y = m_mse_y;
  } else if (btn == UILMSEBTN && !mouse_in_gadget) {
    if (IsLocked())
      UNLOCK_FOCUS(this);
    m_nclicks = 0;
  }
}

// behavior when mouse button is released.
void newuiListBox::OnMouseBtnUp(int btn) {
  bool mouse_in_gadget = PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my);

  if (btn == UILMSEBTN && mouse_in_gadget) {
    UNLOCK_FOCUS(this);
    if (m_nclicks == 1)
      m_nclicks = 2;
    else if (m_nclicks == 3)
      m_nclicks = 0;
    m_last_selected_index = m_SelectedIndex;
  }
}

// this function will handle when an arrow button was pressed
void newuiListBox::OnNotifySelect(UIGadget *g) {
  switch (g->GetDatum()) {
  case NEWUI_ARROW_UP:
    newuiListBox::Offset(-1);
    break;
  case NEWUI_ARROW_DOWN:
    newuiListBox::Offset(1);
    break;
  }
}

// when a listbox item was double clicked (or entered)
void newuiListBox::OnSelect() { UIGadget::OnSelect(); }

// called when destroyed.
void newuiListBox::OnDestroy() {
  int i;

  if (m_up_btn.IsCreated())
    m_up_btn.Destroy();
  if (m_down_btn.IsCreated())
    m_down_btn.Destroy();

  for (i = 0; i < m_NumItems; i++) {
    mem_free(m_ItemList[i]);
  }

  if (m_ItemList)
    mem_free(m_ItemList);
  if (m_Real2Virt)
    mem_free(m_Real2Virt);
  if (m_Virt2Real)
    mem_free(m_Virt2Real);

  m_ItemList = NULL;
  m_Real2Virt = NULL;
  m_Virt2Real = NULL;

  Newui_resources.Free(m_pieces[N_PIECE_IDX]);
  Newui_resources.Free(m_pieces[NE_PIECE_IDX]);
  Newui_resources.Free(m_pieces[E_PIECE_IDX]);
  Newui_resources.Free(m_pieces[SE_PIECE_IDX]);
  Newui_resources.Free(m_pieces[S_PIECE_IDX]);
  Newui_resources.Free(m_pieces[SW_PIECE_IDX]);
  Newui_resources.Free(m_pieces[W_PIECE_IDX]);
  Newui_resources.Free(m_pieces[NW_PIECE_IDX]);

  UIGadget::OnDestroy();
}

// override: behavior when gadget is processed
void newuiListBox::OnUserProcess() {}

// when gadget is added to a window (AddGadget is called)
void newuiListBox::OnAttachToWindow() {
  m_up_btn.Create(m_Wnd, -1, NEWUI_ARROW_UP, NULL, m_X + m_W - m_boffs - 8, m_Y + m_boffs - 1);
  m_up_btn.SetFlag(UIF_NOTIFYMASTERSEL);
  AttachSlaveGadget(&m_up_btn);

  m_down_btn.Create(m_Wnd, -1, NEWUI_ARROW_DOWN, NULL, m_X + m_W - m_boffs - 8, m_Y + m_H - m_boffs - 19);
  m_down_btn.SetFlag(UIF_NOTIFYMASTERSEL);
  AttachSlaveGadget(&m_down_btn);
}

void newuiListBox::OnDetachFromWindow() {
  DetachSlaveGadget(&m_down_btn);
  m_down_btn.Destroy();
  DetachSlaveGadget(&m_up_btn);
  m_up_btn.Destroy();
}

void newuiListBox::Offset(int16_t offs) {
  m_Index = m_Index + offs;
  if (m_Index < 0) {
    m_Index = 0;
  } else if (m_Index >= (m_NumItems - m_NumVisibleItems)) {
    m_Index = m_NumItems - m_NumVisibleItems;
  }
}

//	CLASS a new listbox. uses less memory than the old listbox hopefully.

newuiComboBox::newuiComboBox() {
  m_ItemList = NULL;
  m_Virt2Real = NULL;
  m_Real2Virt = NULL;
  selectchange_fn = NULL;
  m_NumItems = 0;
  m_Index = 0;
}

void newuiComboBox::Create(UIWindow *wnd, int16_t id, int16_t x, int16_t y, uint16_t flags) {
  m_ItemList = NULL;
  m_Virt2Real = NULL;
  m_Real2Virt = NULL;
  selectchange_fn = NULL;
  m_NumItems = 0;
  m_Index = 0;
  m_showup = m_showdown = false;

  m_barbmp = Newui_resources.Load(NEWUI_CB_FILE);
  m_boffs = 12;

  // determine true width and height (snap width and height to 32 pixel boundaries
  UIGadget::Create(wnd, id, x, y, m_barbmp->width(), m_barbmp->height(), flags);
}

// functions to add or remove items,
void newuiComboBox::AddItem(const char *name) {
  char **temp;
  int i;
  int *tempvirt2real, *tempreal2virt;
  int real_index = -1;

  if (m_Flags & UILB_NOSORT) {
    // insert without sort

    if ((m_NumItems % LISTBOX_BUFFER_SIZE) == 0) {
      //	dynamically allocated memory for listbox, expand as needed.
      temp = (char **)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(char *));
      tempvirt2real = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));
      tempreal2virt = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));

      if (m_ItemList) {
        for (i = 0; i < m_NumItems; i++) {
          temp[i] = m_ItemList[i];
          tempvirt2real[i] = m_Virt2Real[i];
          tempreal2virt[i] = m_Real2Virt[i];
        }

        mem_free(m_ItemList);
        mem_free(m_Virt2Real);
        mem_free(m_Real2Virt);
      }
      m_ItemList = temp;
      m_Virt2Real = tempvirt2real;
      m_Real2Virt = tempreal2virt;
    }

    real_index = m_NumItems;
  } else {
    // only text item listboxes!

    // insert with sorting
    if ((m_NumItems % LISTBOX_BUFFER_SIZE) == 0) {
      //	dynamically allocated memory for listbox, expand as needed.
      int oidx = 0, cidx = 0;
      int pidx = 0;
      int result;

      temp = (char **)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(char *));
      tempvirt2real = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));
      tempreal2virt = (int *)mem_malloc((m_NumItems + LISTBOX_BUFFER_SIZE) * sizeof(int));

      real_index = -1;

      if (m_ItemList) {
        while (oidx <= m_NumItems) {
          if (oidx == m_NumItems) {
            if (real_index == -1) {
              real_index = oidx;
            } else {
              temp[cidx] = m_ItemList[pidx];
              tempreal2virt[cidx] = m_Real2Virt[pidx];
            }
            oidx++;
            continue;
          }

          if (m_Flags & UILB_CASESENSITIVE)
            result = strcmp(m_ItemList[cidx], name);
          else
            result = stricmp(m_ItemList[cidx], name);
          if (result < 0) {
            // copy old
            temp[cidx] = m_ItemList[pidx];
            tempreal2virt[cidx] = m_Real2Virt[pidx];
            cidx++;
            pidx++;
          } else if (result >= 0) {
            // see if we need to insert, if not just keep copying
            if (real_index == -1) {
              real_index = cidx;
              cidx++;
            } else {
              temp[cidx] = m_ItemList[pidx];
              tempreal2virt[cidx] = m_Real2Virt[pidx];
              cidx++;
              pidx++;
            }
          }
          oidx++;
        }
        ASSERT(real_index != -1);

        // now we need to fix m_Virt2Real to represent the new structure,
        // all values>=real_index must be incremented
        for (oidx = 0; oidx <= m_NumItems; oidx++) {
          if (oidx < m_NumItems) {
            tempvirt2real[oidx] = m_Virt2Real[oidx];

            // if(oidx!=real_index){
            if (tempvirt2real[oidx] >= real_index)
              tempvirt2real[oidx]++;
          }
        }

        mem_free(m_ItemList);
        mem_free(m_Virt2Real);
        mem_free(m_Real2Virt);
      } else {
        real_index = 0;
      }

      m_ItemList = temp;
      m_Virt2Real = tempvirt2real;
      m_Real2Virt = tempreal2virt;
    } else {
      // find where to insert, without allocating memory
      int oidx = 0, cidx = 0;
      real_index = -1;
      int result;

      int old_r2v;
      char *old_item = NULL;

      while (oidx <= m_NumItems) {

        if (oidx == m_NumItems) {
          // we're past the slot of the old buffer
          if (real_index == -1) {
            // we haven't set the real index yet, so it has to go here
            real_index = m_NumItems;
          } else {
            // the real index has been set, we're still pulling back
            m_Real2Virt[cidx] = old_r2v;
            m_ItemList[cidx] = old_item;
          }
          oidx++;
          continue;
        } else {
          if (m_Flags & UILB_CASESENSITIVE)
            result = strcmp(m_ItemList[cidx], name);
          else
            result = stricmp(m_ItemList[cidx], name);
        }

        if (result < 0) {
          // we haven't gotten to the string yet, keep as they are
          cidx++;
        } else if (result >= 0) {
          // see if we need to insert, if not just keep copying
          if (real_index == -1) {
            // we need to insert here
            real_index = cidx;
            old_item = m_ItemList[cidx];
            old_r2v = m_Real2Virt[cidx];
            cidx++;
          } else {
            // old_item and old_r2v should be set!
            ASSERT(old_item);
            char *oi;
            int or2v;

            or2v = m_Real2Virt[cidx];
            oi = m_ItemList[cidx];

            m_Real2Virt[cidx] = old_r2v;
            m_ItemList[cidx] = old_item;
            old_r2v = or2v;
            old_item = oi;

            cidx++;
          }
        }

        // continue on
        oidx++;
      }

      ASSERT(real_index != -1);

      // now we need to fix m_Virt2Real to represent the new structure,
      // all values>=real_index must be incremented
      cidx = 0;
      for (oidx = 0; oidx <= m_NumItems; oidx++) {
        if (oidx != real_index) {
          if (m_Virt2Real[cidx] >= real_index)
            m_Virt2Real[cidx]++;
          cidx++;
        }
      }
    }
  }

  //	copy item passed to list.
  m_ItemList[real_index] = mem_strdup(name);
  m_Virt2Real[m_NumItems] = real_index;
  m_Real2Virt[real_index] = m_NumItems;
  m_NumItems++;

  if (real_index <= m_Index) {
    // adjust selected index
    if (m_Index < m_NumItems - 1)
      m_Index++;
  }
}

void newuiComboBox::RemoveItem(const char *name) {
  int i, j, found = -1;

  for (i = 0; i < m_NumItems; i++) {
    int res;
    res = (m_Flags & UILB_CASESENSITIVE) ? stricmp(m_ItemList[i], name) : strcmp(m_ItemList[i], name);
    if (res == 0) {
      found = i;
      mem_free(m_ItemList[found]);
      m_ItemList[found] = NULL;
      break;
    }
  }
  if (found == -1) {
    mprintf(0, "newuiComboBox:: Didn't find item to remove!\n");
    return;
  }

  // found is the real index to remove
  // go through virt2real and subtract one from values of found or higher
  // go through real2virt and move everything from index found on down, and subtract
  //	1 from those with value of found or higher
  int real_index = found;              // index to remove
  int virt_index = m_Real2Virt[found]; // index to remove
  int real_thresh = virt_index;
  int virt_thresh = real_index;

  for (j = 0; j < (m_NumItems - 1); j++) {
    if (j >= real_index) {
      m_ItemList[j] = m_ItemList[j + 1];
      m_Real2Virt[j] = m_Real2Virt[j + 1];
    }

    if (j >= virt_index) {
      m_Virt2Real[j] = m_Virt2Real[j + 1];
    }

    if (m_Real2Virt[j] >= real_thresh)
      m_Real2Virt[j]--;

    if (m_Virt2Real[j] >= virt_thresh)
      m_Virt2Real[j]--;
  }
  m_NumItems--;

  if (real_index <= m_Index) {
    // adjust selected index
    m_Index--;
  }
}

void newuiComboBox::RemoveAll() {
  if (m_ItemList) {
    int i;
    for (i = 0; i < m_NumItems; i++) {
      if (m_ItemList[i])
        mem_free(m_ItemList[i]);
    }
    mem_free(m_ItemList);
  }

  if (m_Virt2Real)
    mem_free(m_Virt2Real);

  if (m_Real2Virt)
    mem_free(m_Real2Virt);

  m_ItemList = NULL;
  m_Virt2Real = NULL;
  m_Real2Virt = NULL;
  m_Index = m_NumItems = 0;
}

// item information
int newuiComboBox::GetCurrentIndex() {
  if (m_NumItems == 0)
    return 0;

  if (!m_Real2Virt)
    return 0;

  int virt_index = m_Real2Virt[m_Index];
  ASSERT(virt_index >= 0 && virt_index < m_NumItems);
  return virt_index;
}

void newuiComboBox::SetCurrentIndex(int index) {
  if (m_NumItems == 0)
    return;

  if (index >= 0 && index < m_NumItems) {
    int real_index = m_Virt2Real[index], old_index = m_Index;

    ASSERT(real_index >= 0 && real_index < m_NumItems);
    m_Index = real_index;
    if (m_Index < 0) {
      m_Index = 0;
    }

    // call callbacks if selection really changed.
    if (old_index != m_Index) {
      if (selectchange_fn)
        (*selectchange_fn)(index);
    }
  }
}

bool newuiComboBox::GetCurrentItem(char *buffer, int buflen) {
  return newuiComboBox::GetItem(m_Real2Virt[m_Index], buffer, buflen);
}

bool newuiComboBox::GetItem(int index, char *buffer, int buflen) {
  if (m_NumItems == 0) {
    return false;
    *buffer = 0;
  }

  if (index >= 0 && index < m_NumItems) {
    int real_index = m_Virt2Real[index];
    ASSERT(real_index >= 0 && real_index < m_NumItems);
    strncpy(buffer, m_ItemList[real_index], buflen - 1);
    buffer[buflen - 1] = 0;
    return true;
  }

  return false;
}

bool newuiComboBox::SetCurrentItem(const char *name) {
  int i, found = 0;

  for (i = 0; i < m_NumItems; i++) {
    int res = (m_Flags & UILB_CASESENSITIVE) ? stricmp(m_ItemList[i], name) : strcmp(m_ItemList[i], name);
    if (res == 0) {
      SetCurrentIndex(m_Real2Virt[i]);
      found = 1;
      break;
    }
  }

  if (!found) {
    mprintf(0, "newuiComboBox::SelectItem item not found!\n");
    return false;
  }

  return true;
}

// set callbacks
void newuiComboBox::SetSelectChangeCallback(void (*fn)(int)) { selectchange_fn = fn; }

// behavior when gadget is being drawn.
void newuiComboBox::OnDraw() {
  m_barbmp->draw(0, 0);
  bool auto_select = ((m_Flags & UILB_AUTOSELECT) > 0);
  bool use_scroll = true;

  ui_SetTextClip(m_boffs, 1, m_W - m_boffs - m_up_btn.W(), m_H - 1);

  // decide whether to show arrows. , tricky code.
  if (m_NumItems > 1) {
    if (m_Index < (m_NumItems - 1) && !m_showdown) {
      m_showdown = true;
      m_down_btn.Show(true);
    }
    if (m_Index > 0 && !m_showup) {
      m_showup = true;
      m_up_btn.Show(true);
    }
  }

  if (m_Index == (m_NumItems - 1) && m_showdown) {
    m_showdown = false;
    m_down_btn.Show(false);
  }
  if (m_Index == 0 && m_showup) {
    m_showup = false;
    m_up_btn.Show(false);
  }

  // use gamma 192 for non focus.
  if (m_NumItems && m_Index < m_NumItems && m_Index >= 0) {
    UITextItem text(MONITOR9_NEWUI_FONT, m_ItemList[m_Index], NEWUI_MONITORFONT_COLOR);
    text.draw(m_boffs + 8, 4);
  }

  ui_ResetTextClip();
}

//	behavior when key is pressed.
void newuiComboBox::OnKeyDown(int key) {
  int new_selected_index = m_Index;

  if (key == KEY_UP) {
    if (m_Index > 0) {
      new_selected_index = m_Index - 1;
    }
  } else if (key == KEY_DOWN) {
    if (m_Index < (m_NumItems - 1)) {
      new_selected_index = m_Index + 1;
    }
  }
  newuiComboBox::SetCurrentIndex((m_Real2Virt) ? m_Real2Virt[new_selected_index] : 0);
}

// this function will handle when an arrow button was pressed
void newuiComboBox::OnNotifySelect(UIGadget *g) {
  switch (g->GetDatum()) {
  case NEWUI_ARROW_CBUP:
    newuiComboBox::OnKeyDown(KEY_UP);
    break;
  case NEWUI_ARROW_CBDOWN:
    newuiComboBox::OnKeyDown(KEY_DOWN);
    break;
  }
}

// when a listbox item was double clicked (or entered)
void newuiComboBox::OnSelect() { UIGadget::OnSelect(); }

// called when destroyed.
void newuiComboBox::OnDestroy() {
  int i;

  if (m_up_btn.IsCreated())
    m_up_btn.Destroy();
  if (m_down_btn.IsCreated())
    m_down_btn.Destroy();

  for (i = 0; i < m_NumItems; i++) {
    mem_free(m_ItemList[i]);
  }

  if (m_ItemList)
    mem_free(m_ItemList);
  if (m_Real2Virt)
    mem_free(m_Real2Virt);
  if (m_Virt2Real)
    mem_free(m_Virt2Real);

  m_ItemList = NULL;
  m_Real2Virt = NULL;
  m_Virt2Real = NULL;

  Newui_resources.Free(m_barbmp);

  UIGadget::OnDestroy();
}

// when gadget is added to a window (AddGadget is called)
void newuiComboBox::OnAttachToWindow() {
  m_boffs = 16;
  m_up_btn.Create(m_Wnd, -1, NEWUI_ARROW_CBUP, NULL, m_X + 4, m_Y + 3);
  m_up_btn.SetFlag(UIF_NOTIFYMASTERSEL);
  m_showup = true;
  AttachSlaveGadget(&m_up_btn);
  //	m_showup = false;
  //	m_Wnd->RemoveGadget(&m_up_btn);

  m_down_btn.Create(m_Wnd, -1, NEWUI_ARROW_CBDOWN, NULL, m_X + m_W - m_boffs - 8, m_Y + 3);
  m_down_btn.SetFlag(UIF_NOTIFYMASTERSEL);
  AttachSlaveGadget(&m_down_btn);
  m_showdown = true;
  //	m_showdown = false;
  //	m_Wnd->RemoveGadget(&m_down_btn);
}

void newuiComboBox::OnDetachFromWindow() {
  if (m_showdown) {
    DetachSlaveGadget(&m_down_btn);
    m_showdown = false;
  }
  m_down_btn.Destroy();
  if (m_showup) {
    DetachSlaveGadget(&m_up_btn);
    m_showup = false;
  }
  m_up_btn.Destroy();
}

//	CLASS newuiEditBox

newuiEditBox::newuiEditBox() { m_title = NULL; }

void newuiEditBox::Create(UIWindow *wnd, int16_t id, const char *name, int16_t x, int16_t y, int16_t w, int16_t flags) {
  //	if (name) {
  //		m_title = new UISnazzyTextItem(0, MONITOR9_NEWUI_FONT, name, NEWUI_MONITORFONT_COLOR);
  //	}
  UIEdit::Create(wnd, (int)id, x, y, w ? w : EDIT_GADGET_WIDTH, EDIT_GADGET_HEIGHT, flags | UIF_BORDER);

  //	if (m_title) {
  //		UIEdit::SetTextBounds(m_title->width()+12, m_W-1);
  //	}
  //	else {
  UIEdit::SetTextBounds(1, m_W - 1, -1);
  //	}

  UIEdit::SetColor(NEWUI_MONITORFONT_COLOR);
  UIEdit::SetFont(MONITOR9_NEWUI_FONT);

  m_quick_escape_enable = false;
}

void newuiEditBox::EnableOnQuickEscapeBehavior(bool do_it) { m_quick_escape_enable = do_it; }

void newuiEditBox::OnDestroy() {
  if (m_title) {
    delete m_title;
    m_title = NULL;
  }

  UIEdit::OnDestroy();
}

void newuiEditBox::OnDraw() {
  ui_DrawBox(GR_RGB(128, 128, 128), 0, 0, m_W, m_H);
  if (m_title) {
    if (HasFocus()) {
      m_title->set_flags(UISNAZZYTEXTF_BLINKING);
    } else {
      m_title->set_flags(0);
    }
    m_title->draw(0, 0);
  }

  DrawText();
}

void newuiEditBox::OnKeyDown(int key) {
  UIEdit::OnKeyDown(key);
  if (key == KEY_ESC && m_quick_escape_enable) {
    UIEdit::SetText(NEWUI_EDIT_CANCELED_STR);
    OnSelect();
  }
}

// the new classic hotspot CLASS

newuiHotspot::newuiHotspot() { m_title = NULL; }

void newuiHotspot::Create(UIWindow *wnd, int16_t id, const char *title, int16_t x, int16_t y, int16_t w, int16_t h, int16_t flags) {
  if (title) {
    m_title = mem_strdup(title);
  } else {
    m_title = NULL;
  }

  m_alpha = 0;
  m_alpha_adjust = 0;
  m_mse_timer = -1.0f;

  UIGadget::Create(wnd, id, x, y, w, h, flags);
}

void newuiHotspot::OnDraw() {
  static char buf[256];
  char *strptr;
  int y = 2, x = 2;

  textaux_WordWrap(m_title, buf, m_W - 22, MONITOR9_NEWUI_FONT);

  strptr = strtok(buf, "\n");
  while (strptr) {
    UITextItem text(MONITOR9_NEWUI_FONT, strptr, NEWUI_MONITORFONT_COLOR);
    ddgr_color col =
        (m_alpha_adjust != 0) ? GR_RGB(160 + m_alpha, 160 + m_alpha, 0 + m_alpha) : NEWUI_MONITORFONT_COLOR;
    text.set_color(col);
    text.set_alpha((m_alpha_adjust != 0) ? 255 : 128);
    text.draw(x, y);
    y += text.height();
    x = 20;

    strptr = strtok(NULL, "\n");
  }

  if (m_alpha_adjust != 0) {
    m_alpha += m_alpha_adjust;
    if (m_alpha < 0) {
      m_alpha = 0;
      m_alpha_adjust = 6;
    } else if (m_alpha > 94) {
      m_alpha = 94;
      m_alpha_adjust = -6;
    }
  }
  if (!m_infocus) {
    m_alpha_adjust = 0;
    m_alpha = 0;
  }
}

void newuiHotspot::OnDestroy() {
  if (m_title) {
    mem_free(m_title);
    m_title = NULL;
  }

  UIGadget::OnDestroy();
}

void newuiHotspot::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN) {
    LOCK_FOCUS(this);
    if (m_mse_timer > -1.0f) {
      if ((UI_TIME() - m_mse_timer) < UI_DBLCLICK_DELAY) {
        if (PT_IN_GADGET(UIGadget::m_Wnd, this, UI_input.mx, UI_input.my)) {
          UNLOCK_FOCUS(this);
          OnSelect();
        }
      }
      m_mse_timer = -1.0f;
    }
  }
}

void newuiHotspot::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    UNLOCK_FOCUS(this);

    if (PT_IN_GADGET(UIGadget::m_Wnd, this, UI_input.mx, UI_input.my)) {
      if (m_mse_timer == -1.0f) {
        m_mse_timer = UI_TIME();
      }
    }
  }
}

void newuiHotspot::OnGainFocus() {
  m_alpha = 0;
  m_alpha_adjust = 6;
}

void newuiHotspot::OnLostFocus() {
  m_alpha = 0;
  m_alpha_adjust = 0;
}

///////////////////////////////////////////////////////////////////////////////
// CLASS, sizable window

newuiTiledWindow::newuiTiledWindow() {
  m_startui_cb = NULL;
  m_endui_cb = NULL;
  m_draw_cb = NULL;
  m_onframe_cb = NULL;
  m_data = NULL;
  m_title[0] = 0;
  m_realized = false;
}

void newuiTiledWindow::Create(const char *title, int16_t x, int16_t y, int16_t w, int16_t h, int flags) {
  if (title) {
    ASSERT(strlen(title) < (sizeof(m_title) - 1));
  }

  //	adjust w and height acoordingly with bitmap background width and height.
  int bk_width = (w / TW_PIECE_WIDTH) + ((w % TW_PIECE_WIDTH) ? 1 : 0);
  int bk_height = (h / TW_PIECE_HEIGHT) + ((h % TW_PIECE_HEIGHT) ? 1 : 0);

  if (bk_width < 4)
    bk_width = 4;
  if (bk_height < 4)
    bk_height = 4;

  w = bk_width * TW_PIECE_WIDTH;
  h = bk_height * TW_PIECE_HEIGHT;

  UIWindow::Create(x, y, w, h, flags | UIF_CENTER);

  if (title) {
    strcpy(m_title, title);
  } else {
    m_title[0] = 0;
  }

  // initialze stuff
  m_startui_cb = NULL;
  m_endui_cb = NULL;
  m_draw_cb = NULL;
  m_onframe_cb = NULL;
  m_data = NULL;
  m_realized = false;

  m_sheet.Create(this, NULL, 96, NEWUI_TILED_SHEET_X, title ? NEWUI_TILED_SHEET_Y : NEWUI_TILED_TITLE_Y);

  // graphics.
  m_pieces[N_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_N_FILE);
  m_pieces[NE_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_NE_FILE);
  m_pieces[E_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_E_FILE);
  m_pieces[SE_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_SE_FILE);
  m_pieces[S_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_S_FILE);
  m_pieces[SW_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_SW_FILE);
  m_pieces[W_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_W_FILE);
  m_pieces[NW_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_NW_FILE);
  m_pieces[C_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_C_FILE);

  m_pieces[TL_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_TITLE_L_FILE);
  m_pieces[TC_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_TITLE_C_FILE);
  m_pieces[TR_PIECE_IDX] = Newui_resources.Load(NEWUI_WIN_TITLE_R_FILE);
}

// grab a newui interface from it.
newuiSheet *newuiTiledWindow::GetSheet() { return &m_sheet; }

// do user interface on it.
int newuiTiledWindow::DoUI() {
  // start ui.
  UI_frame_result = -1;
  ui_ShowCursor();

  if (m_startui_cb) {
    (*m_startui_cb)(this, m_data);
  }

  if (!m_realized) {
    m_sheet.Realize();
    m_realized = true;
  }

  // refreshes gadgets on current sheet.
  m_sheet.UpdateChanges();

  //	this should poll UI_frame_result.
  while (UI_frame_result == -1) {

    App()->defer();
    DoUIFrame();
    if (m_onframe_cb) {
      (*m_onframe_cb)(this, m_data);
    }
    if (m_draw_cb) {
      ui_StartDraw(m_X, m_Y, m_X + m_W, m_Y + m_H);
      (*m_draw_cb)(this, m_data);
      ui_EndDraw();
      ui_DoCursor();
    }
    rend_Flip();
  }

  // refreshes gadgets on current sheet.
  m_sheet.UpdateReturnValues();

  if (m_endui_cb) {
    (*m_endui_cb)(this, m_data);
  }

  // cleanup
  ui_HideCursor();
  ui_Flush();

  return UI_frame_result;
}

void newuiTiledWindow::SetData(void *data) { m_data = data; }

// set callbacks
// first called when DoUI is called.
void newuiTiledWindow::SetOnStartUICB(void (*fn)(newuiTiledWindow *, void *)) { m_startui_cb = fn; }

// called when DoUI returns
void newuiTiledWindow::SetOnEndUICB(void (*fn)(newuiTiledWindow *, void *)) { m_endui_cb = fn; }

// called before rend_Flip but after ui has drawn. (SetUICallback is before ui has been rendered)
void newuiTiledWindow::SetOnDrawCB(void (*fn)(newuiTiledWindow *, void *)) { m_draw_cb = fn; }

// called after DoUIFrame is called.   for immediate results.
void newuiTiledWindow::SetOnUIFrameCB(void (*fn)(newuiTiledWindow *, void *)) { m_onframe_cb = fn; }

#include "newui.h"

// Returns the index of the tile bitmap to draw along the top of the window
int newuiTiledWindow::GetTopTileIndex(int tx, int window_width) {
  int title_width, left, right;

  // Get size of the title
  int flags = GetFlags();
  switch (NEWUI_GETTITLEBAR(flags)) {
  case NUWF_TITLENONE:
    return N_PIECE_IDX;
  case NUWF_TITLESMALL:
    title_width = 2;
    break;
  case NUWF_TITLEMED:
    title_width = 4;
    break;
  case NUWF_TITLELARGE:
    title_width = 6;
    break;
  }

  // If one width is odd and other even, then add an extra tile to the title
  if ((window_width ^ title_width) & 1)
    title_width++;

  // Get positions of left & right edges
  left = window_width / 2 - title_width / 2 - 1;
  right = left + title_width + 1;

  // Clip to edges
  if (left < 0)
    left = 0;
  if (right >= window_width)
    right = window_width - 1;

  // Bail if no room for title
  if (left >= right)
    return N_PIECE_IDX;

  if (tx == left)
    return TL_PIECE_IDX;
  else if (tx == right)
    return TR_PIECE_IDX;
  else if ((tx > left) && (tx < right))
    return TC_PIECE_IDX;
  else
    return N_PIECE_IDX;
}

void newuiTiledWindow::OnDraw() {
  //	draw tiles.
  int tx, ty;
  int bk_width = (m_W / TW_PIECE_WIDTH) + ((m_W % TW_PIECE_WIDTH) ? 1 : 0);
  int bk_height = (m_H / TW_PIECE_HEIGHT) + ((m_H % TW_PIECE_HEIGHT) ? 1 : 0);
  int corner_tw = TW_CORNER_WIDTH / TW_PIECE_WIDTH;
  int corner_th = TW_CORNER_HEIGHT / TW_PIECE_HEIGHT;

  // fill background
  for (ty = 1; ty < (bk_height - 1); ty++) {
    for (tx = 1; tx < (bk_width - 1); tx++) {
      m_pieces[C_PIECE_IDX]->draw(tx * TW_PIECE_WIDTH, ty * TW_PIECE_HEIGHT);
    }
  }

  // do sides
  for (ty = corner_th; ty < (bk_height - corner_th); ty++) {
    m_pieces[W_PIECE_IDX]->draw(0, ty * TW_PIECE_HEIGHT);
    m_pieces[E_PIECE_IDX]->draw((bk_width - 1) * TW_PIECE_WIDTH, ty * TW_PIECE_HEIGHT);
  }

  for (tx = corner_tw; tx < (bk_width - corner_tw); tx++) {

    m_pieces[GetTopTileIndex(tx - corner_tw, bk_width - 2 * corner_tw)]->draw(tx * TW_PIECE_WIDTH, 0);
    m_pieces[S_PIECE_IDX]->draw(tx * TW_PIECE_WIDTH, (bk_height - 1) * TW_PIECE_HEIGHT);
  }

  // do corners.
  m_pieces[NW_PIECE_IDX]->draw(0, 0);
  m_pieces[NE_PIECE_IDX]->draw((bk_width - corner_tw) * TW_PIECE_WIDTH, 0);
  m_pieces[SE_PIECE_IDX]->draw((bk_width - corner_tw) * TW_PIECE_WIDTH, (bk_height - corner_th) * TW_PIECE_HEIGHT);
  m_pieces[SW_PIECE_IDX]->draw(0, (bk_height - corner_th) * TW_PIECE_HEIGHT);

  // do title
  UITextItem text(MONITOR15_NEWUI_FONT, m_title, NEWUI_MONITORFONT_COLOR);
  text.draw(NEWUI_TILED_TITLE_X, NEWUI_TILED_TITLE_Y);
}

void newuiTiledWindow::OnDestroy() {
  Newui_resources.Free(m_pieces[N_PIECE_IDX]);
  Newui_resources.Free(m_pieces[NE_PIECE_IDX]);
  Newui_resources.Free(m_pieces[E_PIECE_IDX]);
  Newui_resources.Free(m_pieces[SE_PIECE_IDX]);
  Newui_resources.Free(m_pieces[S_PIECE_IDX]);
  Newui_resources.Free(m_pieces[SW_PIECE_IDX]);
  Newui_resources.Free(m_pieces[W_PIECE_IDX]);
  Newui_resources.Free(m_pieces[NW_PIECE_IDX]);
  Newui_resources.Free(m_pieces[C_PIECE_IDX]);

  Newui_resources.Free(m_pieces[TL_PIECE_IDX]);
  Newui_resources.Free(m_pieces[TC_PIECE_IDX]);
  Newui_resources.Free(m_pieces[TR_PIECE_IDX]);

  m_startui_cb = NULL;
  m_endui_cb = NULL;
  m_draw_cb = NULL;
  m_onframe_cb = NULL;
  m_data = NULL;

  m_sheet.Destroy();

  UIWindow::OnDestroy();
}
