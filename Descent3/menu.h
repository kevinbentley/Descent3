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

 * $Logfile: /DescentIII/main/menu.h $
 * $Revision: 5 $
 * $Date: 4/17/99 6:15p $
 * $Author: Samir $
 *
 * menu header
 *
 * $Log: /DescentIII/main/menu.h $
 *
 * 5     4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 4     12/15/98 4:28p Jeff
 * added mission data information to the pilot files to save what the
 * highest level they achieved on a mission is.  Added level select dialog
 * (not hooked up) and level warp cheat.
 *
 * 3     5/24/98 2:58a Jeff
 * Options menu changes.  MenuOptions now takes a parameter, whether its
 * being called from the game or not
 *
 * 2     3/02/98 5:53p Samir
 * Added MenuOptions prototype.
 *
 * 3     4/29/97 5:29p Samir
 * New game calls mission functions.
 *
 * 2     2/10/97 11:49a Jason
 * checked in for samir
 *
 * 1     2/04/97 2:50p Samir
 *
 * $NoKeywords: $
 */

#ifndef MENU_H
#define MENU_H

#include "pstypes.h"
#include "grdefs.h"

#define MAX_MENUS 5

#define MAX_MENU_ITEMS 50
#define MENU_STRING_LEN 70

#define MF_NORMAL_ANIMATED 1
#define MF_SELECT_ANIMATED 2

#define MAX_MENU_TYPES 5

enum menu_type {
  MENU_TYPE_BUTTON,
  MENU_TYPE_TEXT,
  MENU_TYPE_RADIOBUTTON,
  MENU_TYPE_CHECKBOX,
  MENU_TYPE_TEXTBOX
};

struct menu_item {
  menu_type mtype;
  char name[MENU_STRING_LEN];

  int normal_handle; // The anim/bitmap associated with this unhighlighted item
  int select_handle; // The anim/bitmap associated with the selected menu

  int flags; // see MF types above

  int x, y;

  ddgr_color normal_color, selected_color;

};

struct menu {
  int num_items;

  menu_item items[MAX_MENU_ITEMS];
  uint8_t used;
};

extern bool IsRestoredGame;
extern bool FirstGame;

//	returns whether we decided to quit the game or not
//	this displays the main menu options and runs the menu system
int MainMenu();

//	opens options menu.
// ingame = true (if calling while playing the game)
void MenuOptions(bool ingame);

// DisplayLevelWarpDlg
//	pass in the max level allowed to be chosen, if -1, than all levels are allowed (a.k.a level warp cheat)
int DisplayLevelWarpDlg(int max_level);

#endif
