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
 * $Revision: 14 $
 * $Author: Kevin $
 * $Date: 7/28/99 4:01p $
 *
 * main menu user interface items
 *
 * $Log: /DescentIII/main/mmItem.h $
 *
 * 14    7/28/99 4:01p Kevin
 * Mac
 *
 * 13    4/29/99 3:21a Samir
 * reorganized main menu music to work in config, multiplayer, whereever.
 *
 * 12    4/15/99 2:32p Kevin
 * Added some code for the Demo
 *
 * 11    4/15/99 1:40a Jeff
 * changes for linux compile
 *
 * 10    4/02/99 3:03p Samir
 * opengl doesn't use main menu movie.
 *
 * 9     3/18/99 10:13a Samir
 * new main menu interface.
 *
 * 8     2/26/99 5:34p Samir
 * oem screen.
 *
 * 7     10/22/98 12:46a Matt
 * Made MenuScene() public.
 *
 * 6     10/20/98 6:24p Samir
 * moved menu down.
 *
 * 5     10/20/98 3:52p Samir
 * tweaked main menu look.
 *
 * 4     10/13/98 3:16p Samir
 * enhanced gadgets some more with new effects (added Credits option).
 *
 * 3     10/12/98 4:40p Samir
 * fancy effect for hotspots in main menu.
 *
 * 2     10/12/98 1:46p Samir
 * initial new main menu
 *
 */
#ifndef MMITEM_H
#define MMITEM_H
#include "newui.h"
#include "psclass.h"
#include "gamefont.h"
#if ((!defined(OEM)) && (!defined(DEMO)))
#define MOVIE_MENU
#endif
#define MMITEM_ALPHA 192                   // default alpha
#define MMITEM_SAT 0                       // default saturation
#define MMITEM_FONT MENU_FONT              // default font
#define MMITEM_COLOR GR_RGB(255, 255, 255) // default color of main menu
#define MMITEM_X (Max_window_w * 3 / 5)    // x position of menu text
#define MMITEM_Y 175                       // y position of menu text start
#define N_MMENU_ITEMS 10                   // modify this value to set the maximum main menu items avail.
#define MM_STARTMENU_TYPE 1                // start menu group (used in mmInterface::AddITem)
#define MM_ENDMENU_TYPE 2                  // end menu group
// main menu sounds
#define N_MM_SOUNDS 2
#define MM_SELECT_SOUND 0
#define MM_FOCUS_SOUND 1
// main menu music
#define MM_MUSIC_REGION 0
#define NEWGAME_MUSIC_REGION 1
#define OPTIONS_MUSIC_REGION 2
#define MULTI_MUSIC_REGION 3
//	mmItem FX list.
enum tmmItemFX {
  mmItemFXNull,
  mmItemFXNormal, // displays item with normal alpha, color, saturation.
  mmItemFXFadeInToBright,
  mmItemFXFadeOutToNormal // fade in and out to and from brighten
};

void MenuScene(); // display menu scene
/////////////////////////////////////////////////////////////////////
// gcc doesn't like the tQueue template in psclass.h
#if defined(__LINUX__) || defined(ANDROID)
//	tQueue
//		a circular queue implementation
class tmmItemQueue {
#define tmmItemSIZE 8
  tmmItemFX m_items[tmmItemSIZE];
  int16_t m_head, m_tail;

public:
  tmmItemQueue() { m_head = m_tail = 0; };
  ~tmmItemQueue(){};
  void send(tmmItemFX &item) { // sends an item onto the queue
    int16_t temp = m_tail + 1;
    if (temp == tmmItemSIZE)
      temp = 0;
    if (temp != m_head) {
      m_items[m_tail] = item;
      m_tail = temp;
    }
  };
  bool recv(tmmItemFX *item) { // returns an item from the queue, false if no item.
    if (m_head == m_tail)
      return false;
    *item = m_items[m_head++];
    if (m_head == tmmItemSIZE)
      m_head = 0;
    return true;
  };
  void flush() { // flush queue entries.
    m_head = m_tail = 0;
  };
};
#endif
//////////////////////////////////////////////////////////////////////
class mmInterface;
// class mmItem
class mmItem : public UIGadget {
  char *m_text;  // text for item
  int16_t m_alpha; // alpha for text item
  int16_t m_satcount;
  tmmItemFX m_curfx; // current effect
#if !defined(__LINUX__) && !defined(ANDROID)
  tQueue<tmmItemFX, 8> m_fxqueue; // special effects queue
#else
  tmmItemQueue m_fxqueue;
#endif
  ddgr_color m_colors[6];       // colors for menu (4 corners and 2 mid points)
  float m_process_speed;        // speed gadget is processed (state changes, etc every x seconds)
  float m_last_frametime;       // last frame's time.
  static mmInterface *m_window; // attached window
public:
  mmItem();
  virtual ~mmItem();

public:
  //	attaches a window to all mmitems.
  static void AttachInterface(mmInterface *wnd);
  void Create(int id, int key, int x, int y, const char *text, int flags, tmmItemFX init_fx = mmItemFXNormal);
  void AddEffect(tmmItemFX fx);
  void ClearEffects();

protected:
  virtual void OnMouseBtnDown(int btn); // override: behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // override: behavior when mouse button is released.
  virtual void OnFormat();              // override: called when resized or before drawing.
  virtual void OnDraw();                // override: behavior when gadget is being drawn.
  virtual void OnLostFocus();           // override: behavior when gadget loses input focus.
  virtual void OnGainFocus();           // override: behavior when gadget gains input focus.
  virtual void OnDestroy();             // override: behavior when gadget is destroyed.
  virtual void OnUserProcess();         // override: behavior when gadget is processed
  virtual void OnSelect();
};
//	Main Menu Interface Object
struct tCinematic;
class mmInterface : public UIWindow {
  int m_nmenu_items;                 // number of menu items available.
  mmItem m_menuitems[N_MMENU_ITEMS]; // main menu items
#ifdef MOVIE_MENU
  tCinematic *m_movie; // menu movie handle
#endif
  tLargeBitmap m_art; // artwork for the bitmap
public:
  // type MM_STARTMENU_TYPE = start, type MM_ENDMENU_TYPE = end, (1+2) = start and end, type 0 = normal
  bool AddItem(int id, int key, const char *text, int type = 0);
  void Create();
  int DoUI(); //	does user interface.
public:
  int SoundHandles[N_MM_SOUNDS];
  void SetMusicRegion(int region);
  friend void MenuScene(); // display menu scene
protected:
  virtual void OnDestroy(); // destroys window.
private:
  void CopyrightText(); // displays the copyright text
};
#endif
