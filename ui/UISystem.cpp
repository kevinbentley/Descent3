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

 * $Logfile: /DescentIII/Main/ui/UISystem.cpp $
 * $Revision: 44 $
 * $Date: 3/20/00 12:30p $
 * $Author: Matt $
 *
 *	UI system code.
 *
 * $Log: /DescentIII/Main/ui/UISystem.cpp $
 *
 * 44    3/20/00 12:30p Matt
 * Merge of Duane's post-1.3 changes.
 * Mac-only debugging change.
 *
 * 43    10/21/99 3:33p Kevin
 * Mac merge!
 *
 * 42    7/28/99 2:03p Kevin
 * Macintosh Changes
 *
 * 41    5/05/99 6:48p Samir
 * hack to get pause key to properly register in UI system.
 *
 * 40    5/01/99 1:14a Samir
 * fixed mouse sequencing probs with selections being canceled out by
 * UISystem.
 *
 * 39    4/14/99 1:54a Jeff
 * fixed case mismatched #includes
 *
 * 38    4/01/99 11:28a Samir
 * never flush mouse during ui_Flush.  This will screw up emulated mouse
 * input and maybe mess up some hardware mouse support from the ddio
 * library.
 *
 * 37    3/23/99 9:02p Samir
 * added mouse flush for ui flush. also made keyboard flush too.
 *
 * 36    2/21/99 6:38p Samir
 * mouse and key input better. buffered mouse.
 *
 * 35    1/28/99 6:49p Samir
 * frame limit ui system.
 *
 * 34    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 33    10/19/98 2:50p Samir
 * added function to cleanup ui windows.
 *
 * 32    10/16/98 5:54p Samir
 * to prevent infinite loops, error check.
 *
 * 31    10/16/98 5:53p Samir
 * redid add and remove window mechanisms.
 *
 * 30    10/13/98 8:23p Samir
 * added more keyboard input options.
 *
 * 29    10/13/98 3:47p Samir
 * added function to check if a cursor is visible
 *
 * 28    10/06/98 7:31p Samir
 * changed behavior of mouse b1_count calculation.
 *
 * 27    10/02/98 5:47p Samir
 * changed behavior of mouse cursor.
 *
 * 26    9/30/98 4:32p Samir
 * added frametime value.
 *
 * 25    9/27/98 3:52p Samir
 * made mouse input delay 25 fps.
 *
 * 24    9/01/98 4:12p Samir
 * added screenshot caparbilities.
 *
 * 23    8/31/98 4:08p Samir
 * don't reset mouse position when flushing ui.
 *
 * 22    8/24/98 3:13p Samir
 * fixed swimming of mouse.
 *
 * 21    6/30/98 6:13p Samir
 * call ddio_MouseReset on ui_SetScreenMode.
 *
 * 20    6/29/98 6:44p Samir
 * redid ui input polling.
 *
 * 19    6/05/98 5:35p Samir
 * massive improvement in UI keyboard interface.
 *
 * 18    5/06/98 4:34p Samir
 * added function to set ui screen resolution.
 *
 * 17    5/05/98 5:15p Samir
 * ui system now takes a width and height too
 *
 * 16    4/10/98 7:51p Samir
 * added ui_Flush
 *
 * 15    3/24/98 4:27p Samir
 * To check key states in ui_Poll, calls ddio_GetAdjKeyValue.
 *
 * 14    3/18/98 6:25p Samir
 * Don't turn Z-buffering back on.
 *
 * 13    3/10/98 12:50p Samir
 * Made UI_screen_width & height accessable.
 *
 * 12    2/18/98 2:39p Samir
 * fixed mouse cursor clipping.
 *
 * 11    2/17/98 2:22p Jason
 * fixed some potential z sorting problems
 *
 * 10    2/13/98 6:36p Samir
 * Added ability to prevent input polling and mouse input.
 *
 * 9     2/11/98 5:55p Samir
 * Hide and Show cursor aren't cumulative now.
 *
 * 8     2/02/98 7:35p Samir
 * Added show/hide cursor functions.
 *
 * 7     1/30/98 7:07p Samir
 * Cleaned up Window handling code.
 *
 * 6     1/18/98 4:22p Samir
 * Changed some UI initialization stuff.
 *
 * 5     1/16/98 1:27p Jeff
 * Poll always at least once.
 *
 * 4     1/13/98 4:32p Samir
 * Made tUIInput a shared structure to be used by ui_DoFrame to return UI
 * input values.
 *
 * 3     1/08/98 12:17p Samir
 * Added TitledWindow and modified the UI interface for polling.
 *
 * 2     1/02/98 12:48p Samir
 * Better keyboard support and full mouse cursor support.
 *
 * 1     12/30/97 4:36p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */
#include "UIlib.h"
#include "application.h"
#include "bitmap.h"
#include "ddvid.h"
#include "renderer.h"
#include "psclass.h"
#include "Macros.h"
#define UI_MOUSE_HOTX 2
#define UI_MOUSE_HOTY 2
#define UI_FRAMETIME 0.05
//////////////////////////////////////////////////////////////////////////////
//	VARIABLES
struct tUIWindowNode {
  UIWindow *wnd;
  struct tUIWindowNode *next;
  struct tUIWindowNode *prev;
};
//	user input structure
tUIInput UI_input;
//	user output structure
tUIOutput UI_output;
int UI_screen_width, UI_screen_height;
float UI_aspect_x = 1.0f;
float UI_aspect_y = 1.0f;
//	application object
static bool UI_init = false;
static int UI_cursor_bm = -1;
static tUIWindowNode *UIWindowList = NULL;
static tUIWindowNode *UIWindowTail = NULL;
static UIWindow *UIWindowFocus = NULL;
static int UI_cursor_show = 0;
float UIFrameTime = 0.0f;
bool ui_MousePoll(bool buttons);
bool ui_KeyPoll();
void ui_UpdateWindows();
//////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS
//	call this function to initialize the UI system. pass a surface where all UI will occur
void ui_Init(tUIInitInfo *init_info) {
  //	initialize variables
  if (UI_init) {
    ui_Close();
  }
  //	clear out input poller.
  ui_Flush();
  UI_cursor_bm = -1;
  UI_cursor_show = 0;
  UIWindowList = NULL;
  UIWindowTail = NULL;
  UITextItem::SetDefaultFont(init_info->window_font);
  ui_SetScreenMode(init_info->w, init_info->h);
  UI_init = true;
}
//	frees ui input cache
void ui_Flush() {
//	UI_input.mx = 0;
//	UI_input.last_mx = 0;
//	UI_input.my = 0;
//	UI_input.last_my = 0;
  UI_input.b1_status = 0;
  UI_input.b1_last_status = 0;
  UI_input.b1_count = 0;
  UIFrameTime = 0.0f;
  UI_input.cur_time = timer_GetTime();
  ui_KeyFlush();
}
//	flushes out key input info currently in ui.
void ui_KeyFlush() {
  UI_input.key = 0;
  UI_input.key_first_press = false;
  UI_input.key_status = 0;
  UI_input.last_key = 0;
  UI_input.last_key_status = 0;
  UI_input.printscreen = false;
  ddio_KeyFlush();
}
// closes UI system.  do this when setting a new surface.
void ui_Close() {
  if (UI_cursor_bm > -1) {
    bm_FreeBitmap(UI_cursor_bm);
    UI_cursor_bm = -1;
  }
  //	delete window node list.
  ui_RemoveAllWindows();
  UI_init = false;
}
//	retrieves input for user interface
//		mouse
//		keyboard
//		possibly joystick?
bool ui_MousePoll(bool buttons) {
  int mx, my;
  static int btn_mask = 0;
  int msebtn;
  bool state;
  if (!buttons) {
    //	get all input, mouse maintains persistent button info. key doesn't.
    btn_mask = ddio_MouseGetState(&mx, &my, NULL, NULL);
    UI_input.last_mx = UI_input.mx;
    UI_input.last_my = UI_input.my;
    UI_input.mx = mx;
    UI_input.my = my;
  } else if (UI_cursor_show) {
    // if bX_count is 0, then repeat processing can occur, otherwise only real mouse events are processed.
    if (ddio_MouseGetEvent(&msebtn, &state)) {
      // mprintf(2, "mouse #%d state %d at %04d %04d\n", msebtn, UI_input.b1_status, UI_input.mx, UI_input.my);
      if (msebtn == 0) {
        UI_input.b1_last_status = UI_input.b1_status;
        UI_input.b1_status = state ? UIMSEBTN_PRESSED : UIMSEBTN_RELEASED;
        UI_input.b1_count = 1;
        //	mprintf(0, "M");
        return true;
      } else {
        UI_input.b1_status = 0;
      }
    } else {
      if (UI_input.b1_count == 0) {
        // this frame, there was no down or up event, so now we can check if we should
        // report button 1's state.
        UI_input.b1_last_status = UI_input.b1_status;
        UI_input.b1_count = 1;
        if (CHECK_FLAG(btn_mask, MOUSE_LB)) {
          // process repeat key events.
          UI_input.b1_status = UIMSEBTN_PRESSED;
          //	mprintf(0, "m");
          return true;
        }
        UI_input.b1_status = 0;
      }
    }
  }
  return false;
}
bool ui_KeyPoll() {
  int key;
  key = ddio_KeyInKey();
  if (key == KEY_PRINT_SCREEN)
    UI_input.printscreen = true;
  UI_input.last_key = UI_input.key;
  UI_input.last_key_status = UI_input.key_status;
  // messy hack for pause key
  if ((key & 0x00ff) == KEY_PAUSE) {
    key = key & 0xff;
  }
  UI_input.key = key;
  if (UI_input.key) {
    if (ddio_GetAdjKeyState(UI_input.key)) {
      UI_input.key_status = UIKEY_PRESSED;
      UI_input.key_first_press = true;
    } else {
      UI_input.key_status = UIKEY_CLICKED;
      UI_input.key_first_press = true;
    }
  } else if (UI_input.last_key && UI_input.last_key_status == UIKEY_PRESSED) {
    if (ddio_GetAdjKeyState(UI_input.last_key)) {
      UI_input.key = UI_input.last_key;
      UI_input.key_status = UIKEY_PRESSED;
      UI_input.key_first_press = false;
    } else {
      UI_input.key_status = UIKEY_RELEASED;
      UI_input.key = UI_input.last_key;
      UI_input.key_first_press = false;
    }
  } else {
    UI_input.key_status = 0;
    UI_input.key_first_press = false;
  }
  //	mprintf(0, "key=%d status=%d.\n", UI_input.key, UI_input.key_status);
  return UI_input.key ? true : false;
}
//	ability to load/use mouse cursors
void ui_UseCursor(const char *fname) {
  if (UI_cursor_bm > -1)
    bm_FreeBitmap(UI_cursor_bm);
  UI_cursor_bm = bm_AllocLoadFileBitmap(fname, 0);
  ASSERT(UI_cursor_bm > -1);
}
//	adds a window to the ui list.
void ui_AddWindow(UIWindow *wnd) {
  tUIWindowNode *newnode = new tUIWindowNode;

  if (!UIWindowList) {
    // first item to add to list.
    UIWindowList = newnode;
    newnode->prev = NULL;
  } else {
    // add to existing list.
    tUIWindowNode *node = UIWindowList;
    while (node->next) {
      node = node->next;
    }
    node->next = newnode;
    newnode->prev = node;
  }
  newnode->next = NULL;
  newnode->wnd = wnd;
  UIWindowTail = newnode;
}
//	removes a window from ui list.if topmost, the next topmost window has focus.
void ui_RemoveAllWindows() {
  int count = 0;
  while (UIWindowTail) {
    ui_RemoveWindow(UIWindowTail->wnd);
    count++;
    ASSERT(count < 50);
  }
  if (count) {
    mprintf(0, "%d UI windows left open.  Closed them!\n", count);
  }
}
//	removes a window from ui list.
void ui_RemoveWindow(UIWindow *wnd) {
  tUIWindowNode *node = UIWindowList;
  bool found_wnd = false;
  while (node) {
    if (node->wnd == wnd) {
      // we found a node.
      if (node->prev) {
        node->prev->next = node->next;
      }
      if (node->next) {
        node->next->prev = node->prev;
      }
      if (node == UIWindowList) {
        UIWindowList = NULL;
        UIWindowList = node->next;
      }
      if (node == UIWindowTail) {
        UIWindowTail = NULL;
        UIWindowTail = node->prev;
      }
      delete node;
      found_wnd = true;
      break;
    }
    node = node->next;
  }
  ASSERT(found_wnd);
}
//	Procedure to find which window should gain focus in the
//		first check what window contains mouse pointer and save that window
//		check if keystroke,
//			then adjust focus and save as current focus
//		else
//			set current focus = saved mouse focus.
void ui_DoWindowFocus() {
  //	right now, the topmost window always has focus!
  tUIWindowNode *wndnode = UIWindowTail;
  if (wndnode)
    UIWindowFocus = wndnode->wnd;
  else
    UIWindowFocus = NULL;
}
//	returns a result and processes input of a window in focus
int ui_ProcessFocusedWindow() {
  int res = -1;
  int res2;
  //	no input processing, just render frame
  //	process the window in focus.
  // process at least once regardless of input (for user processes.)
  // get keys.   get mouse while real events (non ui manuipulated) are there.
  ui_MousePoll(false);
  if (UIWindowFocus) {
    UI_input.b1_count = 0; // button one state reset.
    ui_KeyPoll();
    ui_MousePoll(true);
    do {
      res2 = UIWindowFocus->Process();
      if (res2 != -1)
        res = res2;
    } while (ui_MousePoll(true));
  }
  return res;
}
//	updates all visible windows.
void ui_UpdateWindows() {
  tUIWindowNode *wndnode = UIWindowList;
  while (wndnode) {
    if (wndnode->next == NULL) {
    }
    wndnode->wnd->Render();
    wndnode = wndnode->next;
  }
}
//	do cursor display and update
void ui_DoCursor() {
  ui_StartDraw(0, 0, UI_screen_width, UI_screen_height);

  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetZBufferState(0);
  rend_SetAlphaType(AT_CONSTANT + AT_TEXTURE);
  rend_SetAlphaValue(255);

  // This function needs to get called do if there are no windows, stuff gets drawn using
  // the ui_StartDraw and ui_EndDraw
  if (UI_cursor_show && UI_cursor_bm > -1) {
    ui_MousePoll(false); // DAJ

    float u0 = 0.0f, v0 = 0.0f, u1 = 1.0f, v1 = 1.0f;
    int cur_w = bm_w(UI_cursor_bm, 0);
    int cur_h = bm_h(UI_cursor_bm, 0);
    if (UI_input.mx > (UI_screen_width - cur_w))
      u1 = ((float)(UI_screen_width - UI_input.mx)) / ((float)cur_w);
    if (UI_input.my > (UI_screen_height - cur_h))
      v1 = ((float)(UI_screen_height - UI_input.my)) / ((float)cur_h);
    if (UI_input.mx < UI_MOUSE_HOTX)
      u0 = (float)(UI_MOUSE_HOTX - UI_input.mx) / (float)cur_w;
    if (UI_input.my < UI_MOUSE_HOTY)
      v0 = (float)(UI_MOUSE_HOTY - UI_input.my) / (float)cur_h;
    //	mprintf_at(1,5,30,"mx=%d my=%d   ", UI_input.mx,UI_input.my);
    rend_DrawScaledBitmap(UI_input.mx - UI_MOUSE_HOTX, UI_input.my - UI_MOUSE_HOTY,
                          UI_input.mx + (int)((float)cur_w * u1) - UI_MOUSE_HOTX,
                          UI_input.my + (int)((float)cur_h * v1) - UI_MOUSE_HOTY, UI_cursor_bm, u0, v0, u1, v1);
  }
  ui_EndDraw();
}
//	ui_DoFrame
//		polls input
//		does a ui frame given a list of windows
int ui_DoFrame(bool input) {
  int res = -1;
  if (!UI_init)
    return res;

  // reset this flag here, so that print screen is valid only until next call to ui_DoFrame
  if (input)
    UI_input.printscreen = false;
  if (input) {
    ui_DoWindowFocus();              //	determine window with current input focus.
    res = ui_ProcessFocusedWindow(); //	process focused window

    //		int64_t cur_time = timer_GetMSTime();
    while ((timer_GetTime() - UI_input.cur_time) < UI_FRAMETIME) {
    };

    float temp_time = timer_GetTime();
    UIFrameTime = temp_time - UI_input.cur_time;
    UI_input.cur_time = temp_time;
  }
  ui_UpdateWindows();
  ui_DoCursor(); //	update mouse cursor position

  return res;
}
//	does a ui frame and gets mouse and key information.
int ui_DoFrame(tUIInput *input, bool doinput) {
  int res;
  res = ui_DoFrame(doinput);
  *input = UI_input;
  return res;
}
//	hide and show cursor. effects are cumulative
bool ui_ShowCursor() {
  if (!UI_cursor_show) {
    UI_cursor_show = 1;
    return false;
  }
  return true;
}
bool ui_HideCursor() {
  if (UI_cursor_show) {
    UI_cursor_show = 0;
    return false;
  }
  return true; // cursor was hidden before.
}
//	set user interface screen resolution
void ui_SetScreenMode(int w, int h) {
  int old_w = UI_screen_width;
  int old_h = UI_screen_height;
  UI_screen_width = w;
  UI_screen_height = h;
  UI_aspect_x = (float)w / (float)FIXED_SCREEN_WIDTH;
  UI_aspect_y = (float)h / (float)FIXED_SCREEN_HEIGHT;
  ddio_MouseReset();
  //	ddio_MouseSetLimits(0,0, UI_screen_width, UI_screen_height);
  ddio_MouseSetVCoords(UI_screen_width, UI_screen_height);
  UI_input.cur_time = timer_GetTime();
  //	reposition all active open windows to their correct locations in this new resolution
  //@@	tUIWindowNode *wndnode = UIWindowList;
  //@@	float scalar_x = -1.0f + (float)w/(float)old_w;
  //@@	float scalar_y = -1.0f +  (float)h/(float)old_h;
  //@@
  //@@	while (wndnode)
  //@@	{
  //@@		wndnode->wnd->Move(wndnode->wnd->X() + (int)(scalar_x*old_w), wndnode->wnd->Y() + (int)(scalar_y*old_h),
  //@@						wndnode->wnd->W(), wndnode->wnd->H());
  //@@		wndnode = wndnode->next;
  //@@	}
}
bool ui_IsCursorVisible() { return UI_cursor_show ? true : false; }
