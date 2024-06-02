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



#ifndef UISYS_H
#define UISYS_H

/////////////////////////////////////////////////////////////////////////////
//	DEFINITIONS

#define UIMSEBTN_PRESSED 1
#define UIMSEBTN_RELEASED 2
#define UIMSEBTN_CLICKED 3

#define UIKEY_PRESSED 1
#define UIKEY_RELEASED 2
#define UIKEY_CLICKED 3

//	variables (OnMouseDown, etc)
#define UILMSEBTN 1
#define UIRMSEBTN 2

// mouse click properties
#define UI_DBLCLICK_DELAY 0.60f
#define UI_DBLCLICK_MSEDELTA 4

struct tUIInitInfo {
  int window_font; // default font for windows
  int w, h;        // width and height of screen.
};

struct tUIInput {
  int mx, my, last_mx, last_my;
  int b1_status, b1_last_status;
  int b1_count;
  int key, last_key;
  int key_status, last_key_status;
  float cur_time;

  bool key_first_press; // if the key was really pressed or just held down.
  bool printscreen;
};

//	user interface frame time
extern float UIFrameTime;

//	user input structure
extern tUIInput UI_input;
extern int UI_screen_width, UI_screen_height;

class oeApplication;

//////////////////////////////////////////////////////////////////////////////
//	MACROS

#define ISKEYPRESSED(_k)                                                                                               \
  ((UI_input.key == (_k) && (UI_input.key_status == UIKEY_PRESSED || UI_input.key_status == UIKEY_CLICKED)) ? true     \
                                                                                                            : false)
#define ISKEYRELEASED(_k) ((UI_input.key == (_k) && UI_input.key_status == UIKEY_RELEASED) ? true : false)

//	inlined supporter functions
static inline bool PT_IN_GADGET(UIWindow *wnd, UIGadget *gadget, int x, int y) {
  int gl, gt, gr, gb;
  gl = wnd->X() + gadget->X();
  gt = wnd->Y() + gadget->Y();
  gr = wnd->X() + gadget->X() + gadget->W();
  gb = wnd->Y() + gadget->Y() + gadget->H();

  if (x >= gl && x < gr)
    if (y >= gt && y < gb)
      return true;

  return false;
}

static inline bool PT_IN_RECT(int x, int y, int l, int t, int w, int h) {
  if (x >= l && x < (l + w) && y >= t && y < (t + h))
    return true;
  else
    return false;
}

static inline int SCREEN_TO_WND_X(UIWindow *wnd, int x) { return (x - wnd->X()); }

static inline int SCREEN_TO_WND_Y(UIWindow *wnd, int y) { return (y - wnd->Y()); }

static inline int SCREEN_TO_GAD_X(UIGadget *gad, int x) { return (SCREEN_TO_WND_X(gad->GetWindow(), x) - gad->X()); }

static inline int SCREEN_TO_GAD_Y(UIGadget *gad, int y) { return (SCREEN_TO_WND_Y(gad->GetWindow(), y) - gad->Y()); }

#define LOCK_FOCUS(_gadget) (_gadget)->LockFocus();

#define UNLOCK_FOCUS(_gadget) (_gadget)->UnlockFocus();

static inline float UI_TIME() { return UI_input.cur_time; }

//////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS

//	call this function to initialize the UI system. pass a viewport where all UI will occur
void ui_Init(oeApplication *app, tUIInitInfo *init_info);

// closes UI system.  do this when setting a new surface.
void ui_Close();

//	set user interface screen resolution
void ui_SetScreenMode(int w, int h);

//	adds a window to the ui list. it is topmost, and has focus.
void ui_AddWindow(UIWindow *wnd);

//	removes a window from ui list.if topmost, the next topmost window has focus.
void ui_RemoveAllWindows();

//	removes a window from ui list.if topmost, the next topmost window has focus.
void ui_RemoveWindow(UIWindow *wnd);

//	does a ui frame given a list of windows. returns result list.
int ui_DoFrame(bool input = true);

//	does a ui frame and gets mouse and key information.
int ui_DoFrame(tUIInput *input, bool doinput = true);

//	ability to load/use mouse cursors
void ui_UseCursor(const char *fname);

//	hide and show cursor. effects are cumulative (returns whether the cursor was already shown or hidden.)
bool ui_ShowCursor();      // return value false if cursor is currently visible.
bool ui_HideCursor();      // return value true if cursor was already hidden
bool ui_IsCursorVisible(); // is the cursor visible?

//	frees ui input cache
void ui_Flush();

// does screen shot
void ui_DoScreenshot();

#endif
