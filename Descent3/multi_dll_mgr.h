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

 * $Logfile: /DescentIII/main/multi_dll_mgr.h $
 * $Revision: 19 $
 * $Date: 4/25/99 5:02p $
 * $Author: Kevin $
 *
 * Multi player DLL interface manager
 *
 * $Log: /DescentIII/main/multi_dll_mgr.h $
 *
 * 19    4/25/99 5:02p Kevin
 * Bunches of multiplayer UI improvements
 *
 * 18    4/08/99 3:41p Kevin
 * Added some stuff for the scoring API. Not functional yet.
 *
 * 17    1/12/99 2:55p Jeff
 * added/finished the waiting for player's to join dialog
 *
 * 16    12/08/98 3:28p Jeff
 * created and exported UI Checkbox wrappers
 *
 * 15    11/19/98 5:56p Jeff
 * created Slider wrappers
 *
 * 14    10/29/98 7:00p Jeff
 * create some new UI function wrappers
 *
 * 13    9/15/98 12:42p Jason
 * got dedicated server actually working
 *
 * 12    8/31/98 10:14a Kevin
 * Misc. multi-UI fixes
 *
 * 11    8/27/98 5:03p Kevin
 * Prettied up multiplayer screens and fixed some bugs.
 *
 * 10    8/24/98 10:55a Kevin
 * new directplay stuff
 *
 * 9     8/07/98 12:40p Jeff
 * added some functions
 *
 * 8     7/20/98 2:34p Kevin
 * Re-wrote the DLL wrapper, to allow for better expandability
 *
 * 6     6/24/98 6:40p Kevin
 * Added help to main dll menu
 *
 * 5     6/24/98 3:24p Kevin
 * Updated PXO screens with chat, etc.
 *
 * 4     6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 3     6/01/98 10:09a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 2     5/18/98 12:16p Kevin
 * Initial version
 *
 * 1     5/18/98 12:07p Kevin
 *
 * $NoKeywords: $
 */

#ifndef _multi_dll_header
#define _multi_dll_header

#define MT_EVT_LOGIN 1
#define MT_EVT_FIRST_FRAME 2
#define MT_EVT_FRAME 3
#define MT_EVT_GAME_OVER 4
#define MT_EVT_GET_HELP 5
#define MT_AUTO_LOGIN 6
#define MT_AUTO_START 7 // A dedicated server is starting this DLL

struct multi_api {
  int *objs;
  int *rooms;
  int *terrain;
  int *players;
  int *netgame;
  int *netplayers;
  int *ships;
  // TODO: be an actual function declaration
  int *fp[200]; // function pointers
  int *vp[200]; // variable pointers
};

#define MAX_AUTO_LOGIN_STUFF_LEN 50
extern char Auto_login_name[MAX_AUTO_LOGIN_STUFF_LEN];
extern char Auto_login_pass[MAX_AUTO_LOGIN_STUFF_LEN];
extern char Auto_login_addr[MAX_AUTO_LOGIN_STUFF_LEN];
extern char Auto_login_port[MAX_AUTO_LOGIN_STUFF_LEN];

void GetMultiAPI(multi_api *api);
void FreeMultiDLL();
int LoadMultiDLL(const char *name);
void CallMultiDLL(int eventnum);

void SetUITextItemText(UITextItem *uit, char *newtext, uint32_t color);
void *NewUIWindowCreate(int x, int y, int w, int h, int flags);
void NewUIWindowDestroy(NewUIWindow *deswin);
void NewUIWindowOpen(NewUIWindow *deswin);
void NewUIWindowClose(NewUIWindow *deswin);
void *TextCreate(UIWindow *parentwin, UITextItem *textitem, int x, int y, int flags);
void TextSetTitle(UIText *text, UITextItem *textitem);
void *EditCreate(UIWindow *parentwin, int id, int x, int y, int w, int h, int flags);
void *ButtonCreate(UIWindow *parentwin, int id, UITextItem *titleitem, int x, int y, int w, int h, int flags);
void *ListCreate(UIWindow *parentwin, int id, int x, int y, int w, int h, int flags);
void ListRemoveAll(UIListBox *item);
void ListAddItem(UIListBox *item, UITextItem *uitext);
void ListRemoveItem(UIListBox *item, UITextItem *txtitem);
void ListSelectItem(UIListBox *item, UITextItem *txtitem);
const char *ListGetItem(UIListBox *item, int index);
int ListGetSelectedIndex(UIListBox *item);
void ListSetSelectedIndex(UIListBox *item, int index);
void EditSetText(NewUIEdit *item, const char *buff);
void EditGetText(NewUIEdit *item, char *buff, int len);
void DatabaseRead(const char *label, char *entry, int *entrylen);
void DatabaseWrite(const char *label, const char *entry, int entrylen);
void DescentDefer(void);
void *NewUIGameWindowCreate(int x, int y, int w, int h, int flags = UIF_PROCESS_ALL);
void NewUIGameWindowDestroy(NewUIGameWindow *item);
void NewUIGameWindowOpen(NewUIGameWindow *item);
void NewUIGameWindowClose(NewUIGameWindow *item);
void *HotSpotCreate(UIWindow *parentwin, int id, int key, UIItem *txtitemoff, UIItem *txtitemon, int x, int y, int w,
                    int h, int flags);
void HotSpotSetStates(UIHotspot *hs, UIItem *texton, UIItem *textoff);
int PollUI(void);
void RemoveUITextItem(void *item);
void *CreateNewUITextItem(const char *newtext, uint32_t color, int font = -1);
void RemoveUIBmpItem(void *item);
void *CreateNewUIBmpItem(int handle, uint8_t alpha);
void CloseSplashScreen(void);
void CreateSplashScreen(const char *msg, int usecancel);
void *UIConsoleGadgetCreate(UIWindow *parentid, int id, int x, int y, int font, int cols, int rows, int flags);
void UIConsoleGadgetputs(UIConsoleGadget *item, const char *str);
void NewUIWindowSetFocusOnEditGadget(UIEdit *item, UIWindow *parent);
void *OldListCreate(UIWindow *parentitem, int id, int x, int y, int w, int h, int flags);
void OldListRemoveAll(UIListBox *item);
void OldListAddItem(UIListBox *item, UITextItem *uitext);
void OldListRemoveItem(UIListBox *item, UITextItem *txtitem);
void OldListSelectItem(UIListBox *item, UITextItem *txtitem);
void *OldEditCreate(UIWindow *parentitem, int id, int x, int y, int w, int h, int flags);
void OldEditGetText(UIEdit *item, char *buff, int len);
void OldEditSetText(UIEdit *item, const char *newtext);
const char *OldListGetItem(UIListBox *item, int index);
int OldListGetSelectedIndex(UIListBox *item);
void ToggleUICallback(int state);
void SetOldEditBufferLen(UIEdit *item, int len);
void NewUIWindowLoadBackgroundImage(NewUIWindow *item, const char *image_name);
void DeleteUIItem(void *delitem);
void DatabaseReadInt(const char *label, int *val);
void DatabaseWriteInt(const char *label, int val);
void GadgetDestroy(UIGadget *item);
int GetUIItemWidth(void *item);
int GetUIItemHeight(void *item);
void *SliderCreate(UIWindow *parent, int id, int x, int y, int flags = 0);
void SliderSetRange(UISlider *slider, int range);
int SliderGetRange(UISlider *slider);
void SliderSetPos(UISlider *slider, int pos);
int SliderGetPos(UISlider *slider);
void SliderSetSelectChangeCallback(UISlider *slider, void (*fn)(int));
void SliderSetSelectChangeCallbackWData(UISlider *slider, void (*fn)(int, void *), void *ptr);
void *CheckBoxCreate(UIWindow *parent, int id, UIItem *title, int x, int y, int w, int h, int flags);
void CheckBoxSetCheck(UICheckBox *cb, bool state);
bool CheckBoxIsChecked(UICheckBox *cb);
void GetUIItemPosition(UIObject *item, int *x, int *y, int *w, int *h);

void ScoreAPIFrameInterval();
void ScoreAPIGameOver();
void ScoreAPIPlayerJoin(int playernum);
void ScoreAPIPlayerLeft(int playernum);
void ScoreAPIPlayerEntered(int playernum);
void ScoreAPIPlayerKilled(int killer, int killed);

#endif
