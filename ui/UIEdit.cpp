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

 * $Logfile: /DescentIII/Main/ui/UIEdit.cpp $
 * $Revision: 33 $
 * $Date: 10/21/99 3:30p $
 * $Author: Kevin $
 *
 *	Edit control
 *
 * $Log: /DescentIII/Main/ui/UIEdit.cpp $
 *
 * 33    10/21/99 3:30p Kevin
 * mac merge
 *
 * 32    5/17/99 5:19p Samir
 * added ability for edit box to autoselect when hitting the max number of
 * characters typable.
 *
 * 31    5/06/99 1:24a Samir
 * upped editbox maxlength to 512
 *
 * 30    5/06/99 1:20a Samir
 * allow editboxes with max buffer length of 280
 *
 * 29    4/28/99 1:54a Samir
 * visual tweaks to text
 *
 * 28    4/21/99 12:42p Samir
 * change some communication betwen UIEdit and child classes.
 *
 * 27    4/20/99 11:46a Samir
 * numerous ui 'feel' fixes.
 *
 * 26    4/14/99 1:52a Jeff
 * fixed case mismatched #includes
 *
 * 25    2/28/99 3:25a Samir
 * added flag to input only numbers.
 *
 * 24    2/21/99 6:36p Samir
 * focusing changes and key input changes to ui.,
 *
 * 23    10/19/98 12:18p Samir
 * made tabbing between edit controls possible.
 *
 * 22    10/17/98 11:26a Samir
 * fixed some edit box scrolling issues.
 *
 * 21    10/13/98 8:23p Samir
 * communication between gadget and window and edit system to work
 * together.
 *
 * 20    10/06/98 7:30p Samir
 * activate listbox when created.
 *
 * 19    9/30/98 4:33p Samir
 * disabled gadgets display dim text.
 *
 * 18    9/24/98 1:13p Samir
 * edit box a bit better.
 *
 * 17    9/14/98 11:22a Samir
 * enhanced editboxes
 *
 * 16    8/26/98 12:25p Samir
 * fixed the whole editbox, keyboard access mess.
 *
 * 15    8/25/98 5:36p Samir
 * added call to lock key focus in Activate too.
 *
 * 14    8/25/98 5:27p Samir
 * new focusing rules for keyboard.
 *
 * 13    6/22/98 7:31p Samir
 * added UIEdit::Activate, which activates an edit box manually.
 *
 * 12    6/22/98 3:46p Samir
 * fixed bug in UIEdit password system.
 *
 * 11    6/22/98 2:52p Samir
 * call Onselect for UIEdit boxes if edit is pressed.
 *
 * 10    6/22/98 2:15p Samir
 * implemented border flag.
 *
 * 9     6/15/98 5:27p Kevin
 * Fixed bug in UIEdit::GetText where m_TextBuf was NULL
 *
 * 8     5/25/98 8:17p Samir
 * fixed some UI bugs with edit boxes.
 *
 * 7     4/13/98 7:02p Samir
 * made some things protected.
 *
 * 6     3/10/98 11:03a Jeff
 * changed strcpy to strncpy in GetText
 *
 * 5     1/30/98 7:05p Samir
 * Each gadget now has their own coordinate system.
 *
 * 4     1/18/98 4:23p Samir
 * Moved object destruction code to a virtual OnDestroy function for
 * gadgets.  Must destroy window too.
 *
 * 3     1/13/98 4:27p Samir
 * Keyboard timing delay stored UIGadget.  Moved from UIEdit.
 *
 * 2     1/05/98 4:36p Samir
 * Moved centering and fittext control flags to UIGadget class.
 *
 * 1     1/02/98 12:49p Samir
 * Initial revision.
 *
 *
 * $NoKeywords: $
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "ui.h"
#include "ddio_common.h"
#include "grtext.h"
#include "Macros.h"
#include "mem.h"


static UIEdit *UI_current_editbox = NULL;

//	----------------------------------------------------------------------------
//	UIEdit
//		A single line edit control.

UIEdit::UIEdit() {
  m_TextBuf = NULL;
  m_BufSize = 0;
  m_FontHandle = -1;
}

UIEdit::~UIEdit() {}

void UIEdit::Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags) {
  m_BufSize = 32;
  m_TextBuf = (char *)mem_malloc(m_BufSize + 1);
  m_TextBuf[0] = 0;
  m_CursorPosX = 0;
  m_Color = GR_WHITE;
  m_Active = false;
  m_StartPos = -1;
  m_CurPos = 0;
  UIGadget::Create(parent, id, x, y, w, h, flags);
  SetTextBounds(2, m_W - 2, 0);
  m_ScrollThresh = 0;
  m_UpdateCount = false;
  //	UIEdit::Activate();
}

void UIEdit::SetTextBounds(int x1, int x2, int yoff) {
  m_X1b = x1;
  m_X2b = x2;
  m_Yb = yoff;
}

void UIEdit::SetColor(ddgr_color col) { m_Color = col; }

#define EDIT_BUFLEN_MAX 1025 // DAJ utb 512

//	setings
// sets the length of the input buffer.
void UIEdit::SetBufferLen(int length) {
  char *newbuf;
  ASSERT(length < EDIT_BUFLEN_MAX); // there are several places in the code that depend on something like this.

  newbuf = (char *)mem_malloc(length + 1);
  strncpy(newbuf, m_TextBuf, length);
  newbuf[length] = 0;
  if (m_TextBuf) {
    mem_free(m_TextBuf);
  }
  m_TextBuf = newbuf;
  m_BufSize = length;
  m_UpdateCount = false;
}

// sets the text buffer.
void UIEdit::SetText(const char *text) {
  ASSERT(strlen(text) <= (unsigned)m_BufSize);

  if (CHECK_FLAG(m_Flags, UIED_NUMBERS)) {
    int num = atoi(text);
    sprintf(m_TextBuf, "%d", num);
  } else {
    strcpy(m_TextBuf, text);
  }

  m_CurPos = strlen(m_TextBuf);
  m_StartPos = -1;
  m_UpdateCount = false;
}

// retrieve text in edit control.
void UIEdit::GetText(char *buffer, int len) {
  //	ASSERT(strlen(m_TextBuf) < (unsigned)len);
  if (!m_TextBuf) {
    buffer[0] = '\0';
    return;
  }
  strncpy(buffer, m_TextBuf, len - 1);
  buffer[len - 1] = 0;
}

// sets font of control (default is window's font.)
void UIEdit::SetFont(int font) { m_FontHandle = font; }

void UIEdit::Activate() {
  if (UI_current_editbox) {
    UI_current_editbox->Deactivate();
  }

  m_Wnd->HoldHotkeys();
  m_Active = true;
  UI_current_editbox = this;
  m_UpdateCount = false;

  //	mprintf(0, "activating edit box\n");
}

// deactivates edit box (use if you know what you're doing.)
void UIEdit::Deactivate() {
  //	mprintf(0, "deactivating edit box\n");

  m_Active = false;
  UI_current_editbox = NULL;
  m_Wnd->ResumeHotkeys();
}

//	Overrides

void UIEdit::OnDestroy() {
  UIGadget::OnDestroy();

  if (m_TextBuf) {
    mem_free(m_TextBuf);
  }

  // if editbox is being destroyed and is the current editbox, reset to NULL.
  if (UI_current_editbox == this)
    UI_current_editbox = NULL;
}

// override: behavior when gadget loses input focus.
void UIEdit::OnLostFocus() {
  //	mprintf(0, "Edit control lost focus.\n");
  UIEdit::Deactivate();
}

// override: behavior when gadget gains input focus.
void UIEdit::OnGainFocus() {
  //	mprintf(0, "Edit control gained focus.\n");
}

// behavior when gadget is being drawn.
void UIEdit::OnDraw() {
  if (m_Flags & UIF_BORDER) {
    ui_DrawBox(GR_RGB(128, 128, 128), m_X1b - 1, 0, m_X2b + 1, m_H);
  }

  DrawText();
}

void UIEdit::DrawText() {
  char buffer[EDIT_BUFLEN_MAX];
  int str_w, i, cursor_w;

  if (m_FontHandle > -1)
    ui_DrawSetFont(m_FontHandle);

  // I need an extra character.
  ASSERT(strlen(m_TextBuf) < sizeof(buffer));

  if (m_Flags & UIED_PASSWORD) {
    memset(buffer, '*', strlen(m_TextBuf));
    buffer[strlen(m_TextBuf)] = 0;
  } else {
    strcpy(buffer, m_TextBuf);
  }

  if (m_Active || HasFocus())
    ui_SetCharAlpha(255);
  else
    ui_SetCharAlpha(164);

  if (IsDisabled())
    ui_SetCharAlpha(96);

  // we must set StartPos if StartPos is -1
  if (m_StartPos < 0) {
    m_StartPos = 0;
    cursor_w = ui_GetTextWidth("_");
    str_w = ui_GetTextWidth(&buffer[m_StartPos]);
    while ((m_X1b + str_w) > (m_X2b - cursor_w)) {
      m_StartPos++;
      str_w = ui_GetTextWidth(&buffer[m_StartPos]);
    }
  }

  // determine how much of string to draw at one time.
  i = 0;

  cursor_w = ui_GetTextWidth("_") * 2;
  str_w = ui_GetTextWidth(&buffer[m_StartPos]);
  while ((m_X1b + str_w) > (m_X2b - cursor_w) && ((int)strlen(buffer) > m_StartPos)) {
    buffer[strlen(buffer) - 1] = 0;
    str_w = ui_GetTextWidth(&buffer[m_StartPos]);
    i++;
  }

  // if i is > 0, then the string displayed overlaps the boundaries of the listbox
  m_ScrollThresh = i ? (strlen(buffer)) : 0;

  if (m_ScrollThresh && m_UpdateCount) {
    m_StartPos++;
    m_UpdateCount = false;
  }

  // if cursor position is outside viewing region, we must adjust the viewing region.
  //	i = strlen(buffer);
  //	while (m_CurPos > i)
  //		m_CurPos--;

  ui_DrawSetTextType(0);
  ui_DrawString(m_Color, m_X1b, m_Yb + (m_H / 2 - ui_GetFontHeight() / 2), &buffer[m_StartPos]);

  if (m_Active) {
    buffer[m_CurPos] = 0;
    str_w = ui_GetTextWidth(buffer + m_StartPos);
    if (((int)UI_TIME()) % 2)
      ui_DrawString(m_Color, m_X1b + str_w + 1, m_Yb + (m_H / 2 - ui_GetFontHeight() / 2), "_");
  }
}

//	behavior when key is pressed.
void UIEdit::OnKeyDown(int key) {
  int ascii = grfont_KeyToAscii(m_FontHandle, key);
  int len = strlen(m_TextBuf);
  int i;

  if (!m_Active) {
    UIEdit::Activate();
  }

  if (key == KEY_ESC || key == KEY_ENTER) {
    UIEdit::Deactivate();
    if (key == KEY_ENTER) {
      UIGadget::OnSelect(); // do this to enforce pressing enter ONLY causes OnSelect to work.
    }
  } else if (key == KEY_DELETE) {
    for (i = m_CurPos; i < len; i++)
      m_TextBuf[i] = m_TextBuf[i + 1];
  } else {
    if (m_CurPos < m_BufSize) {
      if (CHECK_FLAG(m_Flags, UIED_NUMBERS)) {
        if (ascii < '0' || ascii > '9') {
          goto skip_add_to_buffer;
        }
      }

      if (ascii >= 32 && ascii < 127 && len < m_BufSize) {
        // insert character
        for (i = len; i >= m_CurPos; i--)
          m_TextBuf[i + 1] = m_TextBuf[i];
        // adjust scroll region if cursor will go out of visible region.
        mprintf(0, "scroll=%d, curpos=%d\n", m_ScrollThresh, m_CurPos);
        //				if (m_ScrollThresh<=m_CurPos && m_ScrollThresh)
        //					m_StartPos++;
        m_TextBuf[m_CurPos++] = (char)ascii;
        m_UpdateCount = true;
        if (m_CurPos == m_BufSize && CHECK_FLAG(m_Flags, UIED_AUTOSELECT)) {
          UIEdit::Deactivate();
          UIGadget::OnSelect();
          return;
        }
      }
    }

  skip_add_to_buffer:
    if (m_CurPos < len) {
      if (key == KEY_RIGHT) {
        if (m_ScrollThresh <= m_CurPos && m_ScrollThresh) {
          m_StartPos++;
        }
        //				Update_count = true;
        m_CurPos++;
      }
    }

    if (m_CurPos > 0) {
      if (key == KEY_LEFT) {
        m_CurPos--;
      } else if (key == KEY_BACKSP) {
        // delete character
        for (i = m_CurPos - 1; i < len; i++)
          m_TextBuf[i] = m_TextBuf[i + 1];

        m_CurPos--;
      }
      if (m_CurPos < m_StartPos)
        m_StartPos = m_CurPos;
    }
  }
}

// behavior when key is released.
void UIEdit::OnKeyUp(int key) {}

// behavior when mouse button is pressed.
void UIEdit::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN) {
    if (!m_Active) {
      UIEdit::Activate();
    } else if (!PT_IN_GADGET(m_Wnd, this, UI_input.mx, UI_input.my) && m_Wnd->GetFocus()) {
      //	click outside control and in another control, then deactivate, this means we've accepted the input.
      UIEdit::Deactivate();
    }
  }
}

// behavior when mouse button is released.
void UIEdit::OnMouseBtnUp(int btn) {}

void UIEdit::OnSelect() {
  // except do this to release key focus on this edit box.
  UIEdit::Deactivate();
  UIGadget::OnSelect();
}
