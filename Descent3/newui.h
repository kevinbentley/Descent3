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

 * $Logfile: /DescentIII/Main/newui.h $
 * $Revision: 49 $
 * $Date: 4/27/99 8:51a $
 * $Author: Matt $
 *
 *	New UI Enhancements for D3
 *
 * $Log: /DescentIII/Main/newui.h $
 *
 * 49    4/27/99 8:51a Matt
 * Added defines for dialog title sizes
 *
 * 48    4/26/99 9:12p Matt
 * Made the hotspot color full bright for old newui to make up for the
 * removal of saturation.
 *
 * 47    4/25/99 3:35a Jeff
 * added a please wait popup dialog when entering telcom
 *
 * 46    4/24/99 11:13p Jeff
 * added flags for creating a newui window for a title bar
 *
 * 45    4/20/99 3:32p Kevin
 * made it possible for an edit box to not have a cancel button... used it
 * for choosing team count for server
 *
 * 44    4/16/99 3:58a Jeff
 * for linux builds include linux_fix.h to get rid of some errors for
 * stricmp
 *
 * 43    4/15/99 5:28p Samir
 * added advanced messagebox
 *
 * 42    3/05/99 11:38a Kevin
 * new color scheme
 *
 * 41    3/03/99 5:14a Jeff
 * added DoWaitMessage()
 *
 * 40    2/28/99 3:06a Jeff
 * adjust ok/cancel y offset for new ui artwork
 *
 * 39    2/27/99 8:34p Samir
 * NewuiGameWindow inherits newuiTiledWindow.
 *
 * 38    2/21/99 6:39p Samir
 * new edit box.
 *
 * 37    2/16/99 12:06p Samir
 * added new ui api.
 *
 * 36    12/09/98 4:17p Samir
 * messageboxes use new art.
 *
 * 35    11/10/98 5:17p Jeff
 * fixed define for OK_CANCEL for new ui artwork
 *
 * 34    10/07/98 6:27p Samir
 * added code to quit menus if mutliplayer bailed.
 *
 * 33    10/06/98 5:34p Jeff
 * various UI changes/improvements
 *
 * 32    9/28/98 4:35p Jeff
 * general UI changes and improvements
 *
 * 31    9/23/98 3:08p Jeff
 * updated the colors and various other items of config and UI
 *
 * 30    9/22/98 3:55p Samir
 * moved simple callback to NewUI system.
 *
 * 29    9/02/98 6:50p Samir
 * added new combo box.
 *
 * 28    9/02/98 2:54p Jeff
 * added defines for text colors to be used throughout the game...fixed up
 * buddy menu too
 *
 * 27    8/27/98 2:52p Samir
 * changing window system to work in two modes.
 *
 * 26    8/20/98 6:46p Samir
 * added DoEditDialog.
 *
 * 25    8/19/98 2:18p Jeff
 * changed ddio_CleanPath
 *
 * 24    8/14/98 7:37p Matt
 * Since PSFILENAME_LEN is now considered to be the max length of the
 * string itself (not counting the terminating null), buffers for file
 * name need to be PSFILENAME_LEN+1 bytes long.
 *
 * 23    7/29/98 5:39p Jeff
 * added DoPathFileDialog
 *
 * 22    6/22/98 2:34p Samir
 * added ability to use a bitmap as background for NewUIWindows.
 *
 * 21    6/05/98 5:35p Samir
 * added Class functions to all newui classes.
 *
 * 20    5/26/98 8:16p Samir
 * implemented UIFileDialog's ONDestroy function.
 *
 * 19    5/25/98 8:18p Samir
 * File dialogs implemented.
 *
 * 18    5/19/98 6:23p Samir
 * added NewUIButton
 *
 * 17    4/29/98 12:55p Samir
 * added titile bar to NewUIWindow.
 *
 * 16    4/13/98 7:01p Samir
 * added snazzy listbox and edit box art.
 *
 * 15    3/24/98 10:45a Samir
 * Added GetUICallback.
 *
 * 14    3/13/98 12:00p Jeff
 * Fixed up DoMessageBox so the text position is correct, it prints a
 * window title, and you can specify text color
 *
 * 13    3/11/98 2:35p Samir
 * New message box implemented.
 *
 * 12    3/10/98 7:26p Samir
 * Added new slider.
 *
 * 11    3/10/98 12:49p Samir
 * Bitmapped dialog  supported.
 *
 * 10    3/02/98 5:53p Samir
 * Default value for alpha of windows is set.
 *
 * 9     2/15/98 7:07p Samir
 * Updated NewUIWindow to UIWindow's changes.
 *
 * 8     2/13/98 6:37p Samir
 * Added DoUIFrameWithoutInput.
 *
 * 7     2/02/98 4:31p Samir
 * Added prototype for DoUIFrame.
 *
 * 6     1/30/98 7:04p Samir
 * Added the first NewUIWindow class.
 *
 * 5     1/26/98 2:15p Samir
 * Message box params are char*.
 *
 * 4     1/13/98 6:29p Samir
 * Moved Large Bitmap code from Menu.cpp to newui.cpp.
 *
 * 3     1/08/98 12:18p Samir
 * New menu interface.
 *
 * 2     1/05/98 10:56a Samir
 * New menu stuff.
 *
 * 1     1/02/98 2:09p Samir
 * Initial revision
 *
 *
 * $NoKeywords: $
 */

#ifndef NEWUI_H
#define NEWUI_H

#if defined(__LINUX__) || defined(ANDROID)
#include "linux_fix.h" //fix some of the stricmp's
#endif

#include "newui_core.h"

// flags for creating a newui window
#define NUWF_TITLENONE 0x00000000    // don't display a title bar
#define NUWF_TITLESMALL 0x00100000   // display a small title bar
#define NUWF_TITLEMED 0x00200000     // display a medium size title bar
#define NUWF_TITLELARGE 0x00300000   // display a large title bar
#define NUWF_TITLEBARMASK 0x00300000 // mask to use with flags to get title bar flags

#define NEWUI_GETTITLEBAR(flags) (flags & NUWF_TITLEBARMASK)

// the sizes of the various title bars
#define NUW_TITLESMALL_WIDTH 64
#define NUW_TITLEMED_WIDTH 128
#define NUW_TITLELARGE_WIDTH 196

//////////////////////////////////////////////////////////////////////////////
//	Definitions

// The following defines are RGB definitions for colors that should be used throughout the UI for text
#define UICOL_HOTSPOT_LO                                                                                               \
  GR_RGB(85, 234, 3) // Color for a hotspot when it isn't in focus//GR_RGB(50,50,255)		// Color for a hotspot
                     // when it isn't in focus
#define UICOL_HOTSPOT_HI GR_WHITE                // Color for a hotspot when it is in focus
#define UICOL_TEXT_NORMAL GR_RGB(206, 254, 241)  // Color for text that is used for labels
#define UICOL_WINDOW_TITLE GR_RGB(207, 248, 105) // Color for window title text
#define UICOL_TEXT_AUX GR_RGB(200, 200, 200)     // Color for auxillary text (text that isn't a label)
#define UICOL_LISTBOX_LO GR_RGB(85, 234, 3)      // Color for listbox text that isn't in focus
#define UICOL_LISTBOX_HI GR_RGB(207, 248, 105)   // Color for listbox text that is in focus
#define UICOL_BUTTON_LO GR_RGB(85, 234, 3)       // Color for text on a button that isn't in focus
#define UICOL_BUTTON_HI GR_RGB(207, 248, 105)    // Color for text on a button that is in focus
#define UIALPHA_HOTSPOT_LO 192                   // Alpha value for hotspots not in focus
#define UIALPHA_HOTSPOT_HI 255                   // Alpha value for hotspots in focus

// returns x coordinates to use to determine center position of text items for in a window/dialog
//	width	- total width of dialog/window
//	gap		- size (in pixels) of the gap you want between the left and right item
//	left_item_width - the width (in pixels) of the left item
//	right_item_width - the widht (in pixels) of the right item
//	lx		- will contain the left item's x coord
//	rx		- will contain the right item's x coord
void GetCenteredTextPos(int width, int gap, int left_item_width, int right_item_width, int *lx, int *rx);
// returns x coordinates to use to determine center position of text items for in a window/dialog
//	width	- total width of dialog/window
//	gap		- size (in pixels) of the gap you want between the left and right item
//	left_item_width - the width (in pixels) of the left item
//	middle_item_width - the width (in pixels) of the middle item
//	right_item_width - the width (in pixels) of the right item
//	lx		- will contain the left item's x coord
//	rx		- will contain the right item's x coord
//	mx		- will contain the middle item's x coord
void GetCenteredTextPos(int width, int gap, int left_item_width, int middle_item_width, int right_item_width, int *lx,
                        int *mx, int *rx);

// The following defines are y offset values to be used for "OK","Cancel" and "Done" (take the height of the window
// minus the offset to get the correct y)
#define OKCANCEL_YOFFSET 50 // subtract this from the height of the window

#define UI_BORDERSIZE 20

#define NEWUIBMP_NUM 48

//	bitmap ids for user interface bitmaps.
#define NEWUIBMP_DIALOG_CORNER1 0
#define NEWUIBMP_DIALOG_CORNER2 1
#define NEWUIBMP_DIALOG_CORNER3 2
#define NEWUIBMP_DIALOG_CORNER4 3
#define NEWUIBMP_DIALOG_HORIZTOP 4
#define NEWUIBMP_DIALOG_VERTRIGHT 5
#define NEWUIBMP_DIALOG_HORIZBOT 6
#define NEWUIBMP_DIALOG_VERTLEFT 7
#define NEWUIBMP_DIALOG_BACK 8
#define NEWUIBMP_DIALOG_PANEL 9
#define NEWUIBMP_MSGBOX_LEFT 10
#define NEWUIBMP_MSGBOX_RIGHT 11
#define NEWUIBMP_MSGBOX_CENTER 12
#define NEWUIBMP_SLIDER_BAR 13
#define NEWUIBMP_SLIDER_BUTTON 14
#define NEWUIBMP_EDIT_LEFT 15
#define NEWUIBMP_EDIT_CENTER 16
#define NEWUIBMP_EDIT_RIGHT 17
#define NEWUIBMP_LIST_CORNER1 18
#define NEWUIBMP_LIST_CORNER2 19
#define NEWUIBMP_LIST_CORNER3 20
#define NEWUIBMP_LIST_CORNER4 21
#define NEWUIBMP_LIST_HORIZTOP 22
#define NEWUIBMP_LIST_VERTRIGHT 23
#define NEWUIBMP_LIST_HORIZBOT 24
#define NEWUIBMP_LIST_VERTLEFT 25
#define NEWUIBMP_LIST_BACK 26
#define NEWUIBMP_BTN_UP 27
#define NEWUIBMP_BTN_DOWN 28
#define NEWUIBMP_BTN_HILITE 29
#define NEWUIBMP_BTN_UP_L 30
#define NEWUIBMP_BTN_DOWN_L 31
#define NEWUIBMP_BTN_HILITE_L 32
#define NEWUIBMP_BTN_UP_R 33
#define NEWUIBMP_BTN_DOWN_R 34
#define NEWUIBMP_BTN_HILITE_R 35

//	Large Bitmap system
struct tLargeBitmap {
  int bmps_w;
  int bmps_h;
  int *bm_array;
};

//	alpha for all NewUIWindows.
extern uint8_t NewUIWindow_alpha;

//////////////////////////////////////////////////////////////////////////////
//	Core interface with UI system

//	load in D3 user interface resources
void NewUIInit();

//	closes New UI system
void NewUIClose();

//	shows or hides windows
void OpenUIWindow(UIWindow *wnd);
void CloseUIWindow(UIWindow *wnd);

//////////////////////////////////////////////////////////////////////////////
//	quick and dirty functions

// Displays a 'temporary' dialog with a message
// for example:
//	...
//	DoWaitMessage(true,"Please Wait...");
//	... //some code
//	DoWaitMessage(false);
void DoWaitMessage(bool enable, const char *message = NULL);
void DoWaitPopup(bool enable, const char *message = NULL);

//	puts up a message box with a title and message.
int DoMessageBox(const char *title, const char *msg, int type, ddgr_color title_color = UICOL_WINDOW_TITLE,
                 ddgr_color text_color = UICOL_TEXT_NORMAL);

//	puts up a message box with a title and message.
//	define text for buttons, btn0_title, btn1_title, ..., until NULL.
// also define hotkey for button immediately after title is defined.
//
//	DoMessageBoxAdvanced("Title", "Hi", "Abort", KEY_A, "Retry", KEY_R, "Cancel", KEY_ESC, NULL)
//
// if button with btn0_title pressed, returns 0, btn1_title, returns 1, etc.
// safe for up to three buttons.
int DoMessageBoxAdvanced(const char *title, const char *msg, const char *btn0_title, int key0, ...);

// edit dialog.
bool DoEditDialog(const char *title, char *buffer, int buflen, bool showcancel = true);

// puts up a file selector box
// Parameters:	max_filename_len - the max length for the filename. filebuf have a length of at least max_filename_len+1
bool DoFileDialog(const char *title, const char *search_path, const char *ext, char *filebuf,
                  unsigned max_filename_len);

#define PFDF_FILEMUSTEXIST 0x0001
//	Displays a file dialog that is very much like a Windows file dialog (you can move around directories)
//	save_dialog = is this dialog being used to save file, or load a file.  If save, than pass true
//	path =	on entry is the initial path to start in (must be set...set to 0 length string to go to root directory)
//			on exit it is the absolute path to selected file on return (if return is true) must be at least
//_MAX_PATH in size 	title = Title of the dialog 	wildc = semicolon seperated list of wildcards
//("*.txt;*.doc;*.exe")
bool DoPathFileDialog(bool save_dialog, char *path, const char *title, const char *wildc, int flags);

//////////////////////////////////////////////////////////////////////////////
//	quick and dirty functions

int LoadLargeBitmap(const char *filename, tLargeBitmap *bmp);
void FreeLargeBitmap(tLargeBitmap *bmp);
void DrawLargeBitmap(tLargeBitmap *bmp, int x, int y, float alpha);

//////////////////////////////////////////////////////////////////////////////
//	NewUI Classes

const tUIClass newuiWindow = uiNewClass, newuiGameWindow = uiNewClass + 1;
//		newuiMessageBox = uiNewClass+2,
//		newuiSlider	= uiNewClass+3,
//		newuiEdit = uiNewClass+4,
//		newuiListBox = uiNewClass+5,
//		newuiButton = uiNewClass+6;

const tUIClass newuiNewClass = 1000;

//	NewUIGameWindow
//		this draws a UI window, but with a not-so-cool faded background.

class NewUIWindow : public UIWindow {
  chunked_bitmap m_Chunk;

public:
  NewUIWindow();

  void Create(int x, int y, int w, int h, int flags = UIF_PROCESS_MENU);

  virtual tUIClass Class() const { // Overide this function to name the class
    return newuiWindow;
  };

  //	specify filename of image to use as background.
  void LoadBackgroundImage(const char *image_name);

  //	ui system overridables
protected:
  virtual void OnDraw();    // overridable draws the window background before gadgets
  virtual void OnDestroy(); // when window is nuked.
};

//	NewUIGameWindow
//		this draws a UI window, but with the cool standard game dialog background.

class NewUIGameWindow : public newuiTiledWindow {
public:
  NewUIGameWindow();

  void Create(int x, int y, int w, int h, int flags = UIF_PROCESS_MENU);

  virtual tUIClass Class() const { // Overide this function to name the class
    return newuiGameWindow;
  };
};

//	NewUIMessageBox
//		this draws a UI window, but with the cool standard game dialog background.

class NewUIMessageBox : public NewUIGameWindow {
public:
  NewUIMessageBox();

  void Create(int x, int y, int w, int flags = 0);
};

//	NewUISlider
//		this draws a nicer loking slider.

class NewUISlider : public UISlider {
  UIBitmapItem m_SliderBar;
  UIBitmapItem m_Slider;

public:
  void Create(UIWindow *parent, int id, int x, int y, int flags = 0);
};

//	NewUIEdit
//		this draws a nicer edit box

class NewUIEdit : public UIEdit {
  UIBitmapItem m_EditLeft;
  UIBitmapItem m_EditCen;
  UIBitmapItem m_EditRight;

  int m_TileWidth;

public:
  void Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags = 0);

  //	ui system overridables
protected:
  virtual void OnDraw(); // overridable draws the background first
};

//	NewUIListBox
//		this draws a nicer list box

class NewUIListBox : public UIListBox {
  UIBitmapItem m_BackNW;
  UIBitmapItem m_BackN;
  UIBitmapItem m_BackNE;
  UIBitmapItem m_BackE;
  UIBitmapItem m_BackSE;
  UIBitmapItem m_BackS;
  UIBitmapItem m_BackSW;
  UIBitmapItem m_BackW;
  UIBitmapItem m_Back;

  int m_TileWidth;
  int m_TileHeight;

public:
  void Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags = 0);

  //	ui system overridables
protected:
  virtual void OnDraw(); // overridable draws the background first
};

//	NewUIComboBox
//		displays a listbox just one item.

class NewUIComboBox : public UIComboBox {
  UIBitmapItem m_CmbLeft;
  UIBitmapItem m_CmbCen;
  UIBitmapItem m_CmbRight;

  int m_TileWidth;

public:
  void Create(UIWindow *parent, int id, int x, int y, int w, int flags = 0);

  //	ui system overridables
protected:
  virtual void OnDraw(); // overridable draws the background first
};

//	NewUIButton
//		a nicer fixed size button.

class NewUIButton : public UIButton {
  UIBitmapItem m_BtnUpL, m_BtnUpC, m_BtnUpR;
  UIBitmapItem m_BtnDownL, m_BtnDownC, m_BtnDownR;
  UIBitmapItem m_BtnHiliteL, m_BtnHiliteC, m_BtnHiliteR;

  UIItem *m_BtnTitle;

  int m_TileWidth;

public:
  NewUIButton() { m_BtnTitle = NULL; };

  virtual ~NewUIButton() {
    if (m_BtnTitle)
      delete m_BtnTitle;
  };

  void Create(UIWindow *parent, int id, UIItem *item, int x, int y, int w, int h, int flags = 0);
  void SetTitle(UIItem *item);

  //	ui system overridables
protected:
  virtual void OnDraw();   // overridable draws the background first
  virtual void OnFormat(); // override: called when resized or before drawing.
};

//	NewUIFileDialog
//		this draws a file lister.

class NewUIFileDialog : public NewUIGameWindow {
  NewUIListBox m_ListBox;
  NewUIButton m_Ok;
  NewUIButton m_Cancel;
  UIText m_TitleStr;

  UITextItem *m_FileItems; // file item array.

  char m_SearchPath[_MAX_PATH];
  char m_SearchExt[PSFILENAME_LEN + 1];
  char m_NewPath[_MAX_PATH];

private:
  void UpdateList();

public:
  void Create(const char *title, int x, int y, int w, int h, const char *path, const char *filecard);

  void SetSearchPath(const char *path);
  const char *GetFilename();

public:
  //	call this function to execute dialog.
  virtual bool DoModal();

protected:
  virtual void OnDestroy();
};

#endif
