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

 * $Logfile: /DescentIII/Main/ui/UIButton.cpp $
 * $Revision: 29 $
 * $Date: 5/02/99 7:18p $
 * $Author: Samir $
 *
 *	Button code.
 *
 * $Log: /DescentIII/Main/ui/UIButton.cpp $
 *
 * 29    5/02/99 7:18p Samir
 * a little better error checking with mouse input.  also with fix from
 * grtext.cpp, fixed phony button problem.
 *
 * 28    5/02/99 6:09p Samir
 * unlock focus for buttons when mouse goes up regardless of state.
 *
 * 27    5/02/99 2:08a Samir
 * added Enable and Disable and only accept locking of button if mouse is
 * inside the button.
 *
 * 26    5/01/99 1:14a Samir
 * fixed mouse sequencing probs with selections being canceled out by
 * UISystem.
 *
 * 25    4/17/99 5:59a Jeff
 * Linux wants m_ButtonFont defined
 *
 * 24    4/14/99 1:52a Jeff
 * fixed case mismatched #includes
 *
 * 23    3/09/99 12:21p Samir
 * only allow checking of boxes if mouse is in checkbox at all times, not
 * when clicked on once.
 *
 * 22    2/21/99 6:36p Samir
 * focusing changes and key input changes to ui.,
 *
 * 21    2/16/99 11:58a Samir
 * format buttons to fit their state.
 *
 * 20    12/08/98 3:18p Samir
 * checking a check box calls OnSelect
 *
 * 19    9/30/98 4:33p Samir
 * disabled gadgets display dim text.
 *
 * 18    9/23/98 3:00p Samir
 * took out unnecessary code.
 *
 * 17    5/22/98 5:02p Jeff
 * Added a flag for radio buttons so the button part won't be drawn (just
 * the text)
 *
 * 16    5/22/98 1:31p Jeff
 * changed text saturation for radio button
 *
 * 15    5/01/98 6:23p Samir
 * darkened buttons a bit.
 *
 * 14    4/24/98 2:42a Samir
 * added UICheckBox
 *
 * 13    3/10/98 12:50p Samir
 * Added highlight to radio button.
 *
 * 12    3/05/98 6:40p Samir
 * Implemented radio buttons.
 *
 * 11    2/10/98 4:55p Samir
 * Added radio buttons.
 *
 * 10    1/30/98 7:05p Samir
 * Each gadget now has their own coordinate system.
 *
 * 9     1/23/98 5:34p Samir
 * Allow for nonpersistant UIItems.
 *
 * 8     1/18/98 4:22p Samir
 * Implemented new UIItem system.
 *
 * 7     1/13/98 4:29p Samir
 * Added gadget buttons.
 *
 * 6     1/08/98 12:18p Samir
 * Buttons draw text color based off of UITextItem color.
 *
 * 5     1/05/98 4:36p Samir
 * Moved centering and fittext control flags to UIGadget class.
 *
 * 4     1/05/98 3:48p Jason
 * added SetAllText function for buttons
 *
 * 3     1/05/98 3:18p Samir
 * Added some button flags.
 *
 * 2     1/02/98 12:43p Samir
 * New UIButton interface.
 *
 * 1     12/30/97 4:36p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include "UIlib.h"

#include <string.h>

#if defined(__LINUX__) || defined(ANDROID)
int UIButton::m_ButtonFont;
#endif

//	tUIButton
//		This is a simple 2 state button (push down or push up)
//		Buttons have properties of gadgets, plus bitmap information per state.

UIButton::UIButton() {
  m_Items[UI_BTS_DISABLED] = NULL;
  m_Items[UI_BTS_INACTIVE] = NULL;
  m_Items[UI_BTS_HILITE] = NULL;
  m_Items[UI_BTS_ACTIVATED] = NULL;
}

UIButton::~UIButton() {}

//	if text = NULL, no text printed out.
void UIButton::Create(UIWindow *parent, int id, UIItem *item, int x, int y, int w, int h, int flags) {
  if (item) {
    m_Items[UI_BTS_DISABLED] = item->CopyUIItem();
    m_Items[UI_BTS_INACTIVE] = item->CopyUIItem();
    m_Items[UI_BTS_HILITE] = item->CopyUIItem();
    m_Items[UI_BTS_ACTIVATED] = item->CopyUIItem();
  }

  SetColor(UI_BTS_DISABLED, GR_DARKGRAY);
  SetColor(UI_BTS_INACTIVE, GR_DARKGRAY);
  SetColor(UI_BTS_HILITE, GR_RGB(128, 128, 128));
  SetColor(UI_BTS_ACTIVATED, GR_RGB(128, 128, 128));

  m_State = UI_BTS_INACTIVE; // current state of button.

  UIGadget::Create(parent, id, x, y, w, h, flags);
}

// sets the background bitmap for a specified button state
void UIButton::SetStateItem(int state, UIItem *item) {
  ASSERT(state < UI_BTS_NUM);
  if (m_Items[state]) {
    delete m_Items[state];
    m_Items[state] = NULL;
  }
  if (item)
    m_Items[state] = item->CopyUIItem();
}

// sets the background color for a specified button state
void UIButton::SetColor(int state, ddgr_color col) {
  ASSERT(state < UI_BTS_NUM);

  m_Colors[state] = col;
}

// sets text for all states.
void UIButton::SetAllStates(UIItem *item) {
  for (int i = 0; i < UI_BTS_NUM; i++)
    SetStateItem(i, item);
}

//	Inheritable operations

// override: behavior when gadget is destroyed.
void UIButton::OnDestroy() {
  UIGadget::OnDestroy();

  SetStateItem(UI_BTS_DISABLED, NULL);
  SetStateItem(UI_BTS_INACTIVE, NULL);
  SetStateItem(UI_BTS_HILITE, NULL);
  SetStateItem(UI_BTS_ACTIVATED, NULL);
}

// behavior when gadget loses input focus.
void UIButton::OnLostFocus() {
  if (m_State == UI_BTS_HILITE)
    m_State = UI_BTS_INACTIVE;
}

// behavior when gadget gains input focus.
void UIButton::OnGainFocus() {
  if (m_State != UI_BTS_ACTIVATED)
    m_State = UI_BTS_HILITE;
}

// override: called when resized or before drawing.
void UIButton::OnFormat() {
  if (m_Flags & UIF_FIT) {
    m_W = m_Items[m_State]->width() + 20;
    m_H = m_Items[m_State]->height() + 8;
  }

  UIGadget::OnFormat();
}

// behavior when gadget is being drawn.
void UIButton::OnDraw() {
  //	do state based drawing
  //	determine colors here.
  if (IsDisabled())
    m_State = UI_BTS_DISABLED;

  switch (m_State) {
  case UI_BTS_ACTIVATED:
  case UI_BTS_HILITE:
    ui_DrawLTBox(GR_BLACK, GR_LIGHTGRAY, 0, 0, m_W, m_H);
    break;

  case UI_BTS_INACTIVE:
    ui_DrawLTBox(GR_LIGHTGRAY, GR_BLACK, 0, 0, m_W, m_H);
    break;

  case UI_BTS_DISABLED:
    ui_DrawLTBox(GR_DARKGRAY, GR_DARKGRAY, 0, 0, m_W, m_H);
    break;

  default:
    Int3();
  }

  ui_DrawRect(m_Colors[m_State], 1, 1, m_W - 1, m_H - 1);

  if (m_Items[m_State]) {
    int x = (m_W / 2 - m_Items[m_State]->width() / 2);
    int y = (m_H / 2 - m_Items[m_State]->height() / 2);
    m_Items[m_State]->draw(x, y, IsDisabled() ? uiDrawFaded : uiDrawNormal);
  }
}

// behavior when key is pressed.
void UIButton::OnKeyDown(int key) {}

// behavior when key is released.
void UIButton::OnKeyUp(int key) {}

// behavior when mouse button is pressed.
void UIButton::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN) {
    if (m_State != UI_BTS_ACTIVATED && PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my)) {
      m_State = UI_BTS_ACTIVATED;
      LOCK_FOCUS(this);
      //	mprintf(0, "Mouse down, locking gadget.\n");
    } else if (m_State == UI_BTS_ACTIVATED && !PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my)) {
      m_State = UI_BTS_HILITE;
    }
  }
}

// behavior when mouse button is released.
void UIButton::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    if (m_State == UI_BTS_ACTIVATED) {
      if (PT_IN_GADGET(UIGadget::m_Wnd, this, UI_input.mx, UI_input.my)) {
        OnSelect();
      }
      m_State = UI_BTS_HILITE;
    }
    //	mprintf(0, "Mouse up, unlocking gadget.\n");
    UNLOCK_FOCUS(this);
  }
}

// this adds to the gadget equivalent
void UIButton::Disable() {
  UIGadget::Disable();
  m_State = UI_BTS_DISABLED;
}

// this adds to the gadget equivalent
void UIButton::Enable() {
  UIGadget::Enable();

  if (HasFocus()) {
    m_State = UI_BTS_HILITE;
  } else {
    m_State = UI_BTS_INACTIVE;
  }
}

//	UIRadioButton
//		This is a simple 2 state button (push down or push up)
//		Buttons have properties of gadgets, plus bitmap information per state.

UIRadioButton::UIRadioButton() { m_PrevRB = m_NextRB = NULL; }

void UIRadioButton::Create(UIWindow *parent, UIRadioButton *prev_rb, int id, UIItem *title, int x, int y, int w, int h,
                           int flags) {
  UIButton::Create(parent, id, title, x, y, w, h, flags);

  //	create link in radio button chain.
  m_PrevRB = prev_rb;
  m_NextRB = NULL;
  if (m_PrevRB) {
    m_NextRB = m_PrevRB->m_NextRB;
    if (m_NextRB) {
      m_NextRB->m_PrevRB = this;
    }
    m_PrevRB->m_NextRB = this;
  }

  if (!m_PrevRB) {
    UIGadget::SetFlag(UIF_GROUP_START);
  } else {
    m_PrevRB->ClearFlag(UIF_GROUP_END);
  }
  if (!m_NextRB) {
    UIGadget::SetFlag(UIF_GROUP_END);
  }

  //	THIS PROBLEM IS PROBABLY DUE TO THE CALLER'S FAULT!
  ASSERT(m_PrevRB != this);
}

// turns on button, turns off others in group.
void UIRadioButton::Activate() { ActivateButton(); }

// behavior when gadget is being drawn.
void UIRadioButton::OnDraw() {
  char btnstr[3];
  int iterations = 0;

  if (IsDisabled())
    m_State = UI_BTS_DISABLED;

  switch (m_State) {
  case UI_BTS_HILITE:
    iterations = 1;
  case UI_BTS_INACTIVE:
  case UI_BTS_DISABLED:
    if (m_Flags & UIRB_NOBUTTON)
      strcpy(btnstr, " ");
    else
      snprintf(btnstr, sizeof(btnstr), "%c ", UI_RADIO_OFF_CHAR);
    break;
  case UI_BTS_ACTIVATED:
    iterations = 1;
    if (m_Flags & UIRB_NOBUTTON)
      strcpy(btnstr, " ");
    else
      snprintf(btnstr, sizeof(btnstr), "%c ", UI_RADIO_ON_CHAR);
    break;

  default:
    btnstr[0] = 0;
  }

  UITextItem btn(btnstr, GetStateItem(m_State)->get_color(), GetStateItem(m_State)->get_alpha());

  btn.draw(0, 0, IsDisabled() ? uiDrawFaded : uiDrawNormal);
  GetStateItem(m_State)->draw(ui_GetTextWidth(btnstr), 0, IsDisabled() ? uiDrawFaded : uiDrawNormal);

  while (iterations--) {
    btn.draw(0, 0, uiDrawAlphaSaturate);
    GetStateItem(m_State)->draw(ui_GetTextWidth(btnstr), 0, uiDrawAlphaSaturate);
  }
}

// override: called when resized or before drawing.
void UIRadioButton::OnFormat() {
  if (m_Flags & UIF_FIT) {
    char btnstr[3];
    if (m_Flags & UIRB_NOBUTTON)
      strcpy(btnstr, " ");
    else
      snprintf(btnstr, sizeof(btnstr), "%c ", UI_RADIO_OFF_CHAR);

    UITextItem btn(btnstr, GetStateItem(m_State)->get_color(), GetStateItem(m_State)->get_alpha());

    m_W = GetStateItem(m_State)->width() + btn.width();
    m_H = GetStateItem(m_State)->height() + 8;
  }

  UIGadget::OnFormat();
}

// behavior when gadget loses input focus.
void UIRadioButton::OnLostFocus() {}

// behavior when gadget gains input focus.
void UIRadioButton::OnGainFocus() {}

// behavior when key is pressed.
void UIRadioButton::OnKeyDown(int key) {
  if (key == KEY_SPACEBAR || key == KEY_ENTER)
    ActivateButton();
}

// behavior when key is released.
void UIRadioButton::OnKeyUp(int key) {}

// behavior when mouse button is pressed.
void UIRadioButton::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN && !this->IsLocked()) {
    if (PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my)) {
      ActivateButton();
      LOCK_FOCUS(this);
    }
  }
}

// behavior when mouse button is released.
void UIRadioButton::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    UNLOCK_FOCUS(this);
  }
}

// activates this button, deactivating all others.
void UIRadioButton::ActivateButton() {
  //	okay, start through list
  UIRadioButton *radiolist = this;

  while (radiolist->m_PrevRB)
    radiolist = radiolist->m_PrevRB;

  // deactivate all buttons until we hit the current button, then activate it.
  while (radiolist) {
    if (radiolist == this) {
      radiolist->m_State = UI_BTS_ACTIVATED;
      OnSelect();
    } else {
      radiolist->m_State = UI_BTS_INACTIVE;
    }

    radiolist = radiolist->m_NextRB;
  }
}

//////////////////////////////////////////////////////////////////////////////
//	UICheckBox
//		This is a simple 2 state button (push down or push up)
//		Buttons have properties of gadgets, plus bitmap information per state.

UICheckBox::UICheckBox() {}

void UICheckBox::Create(UIWindow *parent, int id, UIItem *title, int x, int y, int w, int h, int flags) {
  UIButton::Create(parent, id, title, x, y, w, h, flags);
  SetCheck(false);
}

// turns on button, turns off others in group.
void UICheckBox::SetCheck(bool state) {
  if (state) {
    m_State = UI_BTS_ACTIVATED;
  } else {
    m_State = UI_BTS_INACTIVE;
  }
}

// behavior when gadget is being drawn.
void UICheckBox::OnDraw() {
  char btnstr[3];
  int iterations = 1;

  ui_DrawSetTextType(UI_TEXTTYPE_SATURATE);

  if (IsDisabled())
    m_State = UI_BTS_DISABLED;

  switch (m_State) {
  case UI_BTS_HILITE:
    iterations = 2;
  case UI_BTS_INACTIVE:
  case UI_BTS_DISABLED:
    snprintf(btnstr, sizeof(btnstr), "%c ", UI_CHECKBOX_OFF_CHAR);
    break;
  case UI_BTS_ACTIVATED:
    iterations = 2;
    snprintf(btnstr, sizeof(btnstr), "%c ", UI_CHECKBOX_ON_CHAR);
    break;

  default:
    btnstr[0] = 0;
  }

  UITextItem btn(btnstr, GetStateItem(m_State)->get_color(), GetStateItem(m_State)->get_alpha());

  while (iterations--) {
    btn.draw(0, 0);
    GetStateItem(m_State)->draw(ui_GetTextWidth(btnstr), 0, IsDisabled() ? uiDrawFaded : uiDrawNormal);
  }

  ui_DrawSetTextType(0);
}

// override: called when resized or before drawing.
void UICheckBox::OnFormat() {
  if (m_Flags & UIF_FIT) {
    char btnstr[3];
    snprintf(btnstr, sizeof(btnstr), "%c ", UI_CHECKBOX_OFF_CHAR);

    UITextItem btn(btnstr, GetStateItem(m_State)->get_color(), GetStateItem(m_State)->get_alpha());

    m_W = GetStateItem(m_State)->width() + btn.width();
    m_H = GetStateItem(m_State)->height() + 8;
  }

  UIGadget::OnFormat();
}

// behavior when gadget loses input focus.
void UICheckBox::OnLostFocus() {}

// behavior when gadget gains input focus.
void UICheckBox::OnGainFocus() {}

// behavior when key is pressed.
void UICheckBox::OnKeyDown(int key) {
  if (key == KEY_SPACEBAR || key == KEY_ENTER) {
    SetCheck((m_State == UI_BTS_ACTIVATED) ? false : true);
    OnSelect();
  }
}

// behavior when key is released.
void UICheckBox::OnKeyUp(int key) {}

// behavior when mouse button is pressed.
void UICheckBox::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN && !this->IsLocked()) {
    if (PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my)) {
      SetCheck((m_State == UI_BTS_ACTIVATED) ? false : true);
      OnSelect();
      LOCK_FOCUS(this);
    }
  }
}

// behavior when mouse button is released.
void UICheckBox::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    UNLOCK_FOCUS(this);
  }
}
