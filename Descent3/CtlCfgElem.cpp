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

 * $Logfile: /DescentIII/main/CtlCfgElem.cpp $
 * $Revision: 26 $
 * $Date: 3/20/00 12:03p $
 * $Author: Matt $
 *
 * Control config element gadgets
 *
 * $Log: /DescentIII/main/CtlCfgElem.cpp $
 *
 * 26    3/20/00 12:03p Matt
 * Merge of Duane's post-1.3 changes.
 * Added Mac international keys (Mac only)
 *
 * 25    10/22/99 10:47a Matt
 * Mac merge
 *
 * 24    7/30/99 1:05p Samir
 * read POVs before buttons since most controllers map hat positions to
 * buttons as well.
 *
 * 23    7/16/99 11:15a Samir
 * multiple hat support
 *
 * 22    6/11/99 1:15a Samir
 * localization issues.
 *
 * 21    5/20/99 9:11p Samir
 * no bind '-' and '=' keys.
 *
 * 20    5/06/99 1:40a Samir
 * adjusted some text.
 *
 * 19    4/29/99 2:59p Samir
 * added help and made CTRL-C clear for controller screens.
 *
 * 18    4/29/99 2:23a Samir
 * moved binding text functions to wincontroller.cpp and new text for
 * multiple joysticks.
 *
 * 17    4/15/99 1:38a Jeff
 * changes for linux compile
 *
 * 16    4/14/99 12:35p Samir
 * localization issues.
 *
 * 15    4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 14    3/23/99 9:04p Samir
 * moved mouse binding text to mouse library.
 *
 * 13    3/09/99 6:26p Samir
 * flush mouse queue after configuring button.
 *
 * 12    3/05/99 4:34p Samir
 * multiplayer bug in controller config.
 *
 * 11    3/02/99 1:17p Samir
 * resume and suspend controls for config instead of directly going
 * through controller. this is done so mask_controllers gets called with
 * the latest Current_pillot.read_controller values...
 *
 * 10    2/26/99 2:09a Samir
 * added '?' button.
 *
 * 9     2/21/99 6:36p Samir
 * focusing changes and key input changes to ui.,
 *
 * 8     2/16/99 12:07p Samir
 * redid controller config with new ui.
 *
 * 7     1/28/99 3:58p Jeff
 * localization update
 *
 * 6     11/30/98 4:54p Samir
 * added rear view config item.
 *
 * 5     10/23/98 12:51p Samir
 * bail out of config if server says so: note there still is a bug with
 * this system.
 *
 * 4     10/18/98 1:07p Samir
 * tweaked user interface for controller config.
 *
 * 3     10/17/98 7:31p Samir
 * added invertible axes
 *
 * 2     9/30/98 4:37p Samir
 * 'incremental checkin'
 *
 * 1     9/28/98 3:47p Samir
 * initial revision.
 *
 * $NoKeywords: $
 */

#include "CtlCfgElem.h"
#include "descent.h"

#include "Macros.h"
#include "ddio.h"
#include "application.h"
#include "renderer.h"
#include "stringtable.h"
#include "gamefont.h"
#include "localization.h"

#include <string.h>

// all controller binding texts
static char Ctltext_KeyBindings[][16] = {"",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "bspc\0\0\0\0\0\0",
                                         "tab\0\0\0\0\0\0",
                                         "q",
                                         "w",
                                         "e",
                                         "r",
                                         "t",
                                         "y",
                                         "u",
                                         "i",
                                         "o",
                                         "p",
                                         "[",
                                         "]",
                                         "enter\0\0\0\0\0",
                                         "lctrl\0\0\0\0\0",
                                         "a",
                                         "s",
                                         "d",
                                         "f",
                                         "g",
                                         "h",
                                         "j",
                                         "k",
                                         "l",
                                         ";",
                                         "'",
                                         "`",
                                         "lshft\0\0\0\0\0",
                                         "\\",
                                         "z",
                                         "x",
                                         "c",
                                         "v",
                                         "b",
                                         "n",
                                         "m",
                                         ",",
                                         ".",
                                         "/",
                                         "rshft\0\0\0\0\0",
                                         "pad*\0\0\0\0\0",
                                         "lalt\0\0\0\0\0",
                                         "spc\0\0\0\0\0",
                                         "caps\0\0\0\0\0",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "num\0\0\0\0\0",
                                         "sclk\0\0\0\0\0",
                                         "pad7\0\0\0\0\0",
                                         "pad8\0\0\0\0\0",
                                         "pad9\0\0\0\0\0",
                                         "pad-\0\0\0\0\0",
                                         "pad4\0\0\0\0\0",
                                         "pad5\0\0\0\0\0",
                                         "pad6\0\0\0\0\0",
                                         "pad+\0\0\0\0\0",
                                         "pad1\0\0\0\0\0",
                                         "pad2\0\0\0\0\0",
                                         "pad3\0\0\0\0\0",
                                         "pad0\0\0\0\0\0",
                                         "pad.\0\0\0\0\0",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "pad�\0\0\0\0\0\0",
                                         "rctrl\0\0\0\0\0",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "pad/\0\0\0\0\0\0",
                                         "",
                                         "",
                                         "ralt\0\0\0\0\0\0",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "home\0\0\0\0\0\0",
                                         "up\0\0\0\0\0\0\0",
                                         "pgup\0\0\0\0\0\0",
                                         "",
                                         "left\0\0\0\0\0\0",
                                         "",
                                         "right\0\0\0\0\0\0",
                                         "",
                                         "end\0\0\0\0\0\0\0",
                                         "down\0\0\0\0\0\0",
                                         "pgdn\0\0\0\0\0\0",
                                         "ins\0\0\0\0\0\0",
                                         "del\0\0\0\0\0\0",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         ""};

static int16_t key_binding_indices[] = {
    KEY_BACKSP,    KEY_TAB,      KEY_ENTER, KEY_LCTRL,     KEY_LSHIFT,   KEY_RSHIFT, KEY_PADMULTIPLY, KEY_LALT,
    KEY_SPACEBAR,  KEY_CAPSLOCK, 0x45,      KEY_SCROLLOCK, KEY_PAD7,     KEY_PAD8,   KEY_PAD9,        KEY_PADMINUS,
    KEY_PAD4,      KEY_PAD5,     KEY_PAD6,  KEY_PADPLUS,   KEY_PAD1,     KEY_PAD2,   KEY_PAD3,        KEY_PAD0,
    KEY_PADPERIOD, KEY_PADENTER, KEY_RCTRL, KEY_PADDIVIDE, KEY_RALT,     KEY_HOME,   KEY_UP,          KEY_PAGEUP,
    KEY_LEFT,      KEY_RIGHT,    KEY_END,   KEY_DOWN,      KEY_PAGEDOWN, KEY_INSERT, KEY_DELETE,      0xff};

#define NUM_KEYBINDSTRINGS (sizeof(Ctltext_KeyBindings) / sizeof(char *))

#define F_ELEM_HILITE 0x1
#define F_ELEM_ACTIVE 0x2
#define F_ELEM_INVERTED 0x4

#define CFGELEM_BTN_X 132

/*
$$TABLE_GAMEFILE "SmallButton.ogf"
$$TABLE_GAMEFILE "SmallButtonLit.ogf"
$$TABLE_GAMEFILE "TinyButton.ogf"
$$TABLE_GAMEFILE "TinyButtonLit.ogf"
*/
#define NEWUI_BTN_FILE "SmallButton.ogf"
#define NEWUI_BTNLIT_FILE "SmallButtonLit.ogf"
#define NEWUI_TINYBTN_FILE "TinyButton.ogf"
#define NEWUI_TINYBTNLIT_FILE "TinyButtonLit.ogf"

extern char Ctltext_AxisBindings[][16];
extern char Ctltext_PovBindings[][16];
extern char Ctltext_MseBtnBindings[][32];
extern char Ctltext_MseAxisBindings[][32];

void Localize_ctl_bindings() {
  char **strtable;
  int n_strings, i;

  // keyboard translations.
  // no need to do for english!
  if (Localization_GetLanguage() == LANGUAGE_ENGLISH)
    return;

  if (CreateStringTable("bindkey.str", &strtable, &n_strings)) {
    i = 0;
    while (key_binding_indices[i] != 0xff) {
      if (i >= n_strings) {
        break;
      }
      strcpy(Ctltext_KeyBindings[key_binding_indices[i]], strtable[i]);
      i++;
    }
    DestroyStringTable(strtable, n_strings);
  }

  // mouse translations.
  if (CreateStringTable("bindmse.str", &strtable, &n_strings)) {
    for (i = 0; i < 6; i++) {
      if (i >= n_strings) {
        break;
      }
      strcpy(Ctltext_MseBtnBindings[i], strtable[i]);
    }
    for (i = 0; i < 3; i++) {
      if ((i + 6) >= n_strings) {
        break;
      }
      strcpy(Ctltext_MseAxisBindings[i], strtable[i + 6]);
    }
    DestroyStringTable(strtable, n_strings);
  }

  // joystick translations.
  if (CreateStringTable("bindjoy.str", &strtable, &n_strings)) {
    for (i = 0; i < 6; i++) {
      if (i >= n_strings) {
        break;
      }
      strcpy(Ctltext_AxisBindings[i + 1], strtable[i]);
    }
    for (i = 0; i < 4; i++) {
      if ((i + 6) >= n_strings) {
        break;
      }
      strcpy(Ctltext_PovBindings[i + 1], strtable[i + 6]);
    }
    DestroyStringTable(strtable, n_strings);
  }
}

//////////////////////////////////////////////////////////////////////////////
const char *cfg_binding_text(ct_type ctype, uint8_t ctrl, uint8_t binding) {
  const char *str;

  if (ctrl == NULL_CONTROLLER) {
    return NULL;
  }

  switch (ctype) {
  case ctKey: {
    ASSERT(binding < NUM_KEYBINDSTRINGS);
    str = Ctltext_KeyBindings[binding];
    break;
  }

  case ctPOV:
  case ctPOV2:
  case ctPOV3:
  case ctPOV4:
  case ctMouseButton:
  case ctButton:
  case ctMouseAxis:
  case ctAxis:
    str = Controller->get_binding_text(ctype, ctrl, binding);
    break;

  default:
    if (ctype == ctNone) {
      Int3();
    }
    return ("");
  }

  return str;
}

//////////////////////////////////////////////////////////////////////////////
//
class cfg_element_ui : public newuiMessageBox {
  uint8_t m_element;    // element passed and returned.
  uint8_t m_controller; // controller.
  int8_t m_alpha;      // used for fx.
  ct_type m_type;

public:
  void Create(const char *title, ct_type type, uint8_t controller, uint8_t element);
  uint8_t GetElement() const { return m_element; };
  uint8_t GetController() const { return m_controller; };
  ct_type GetType() const { return m_type; };
  int DoUI();

protected:
  virtual void OnDraw();
};

//////////////////////////////////////////////////////////////////////////////
//

UIBitmapItem *cfg_element::m_btn_bmp_lit = NULL;
UIBitmapItem *cfg_element::m_btn_bmp = NULL;
UIBitmapItem *cfg_element::m_xbtn_bmp_lit = NULL;
UIBitmapItem *cfg_element::m_xbtn_bmp = NULL;
int16_t cfg_element::m_count = 0;

// MTS: unused?
bool key_cfg_element(uint8_t *element, uint8_t *flags);

//////////////////////////////////////////////////////////////////////////////
//

void cfg_element::Create(UIWindow *wnd, int str_i, int x, int y, int fnid, int id) {
  m_title = TXT(str_i);
  m_fnid = (int8_t)fnid;
  m_slot = 0;
  m_curslot = -1;
  m_flags = 0;
  m_slot_alpha = 255;
  m_blink_state = 0;

  if (cfg_element::m_count == 0) {
    cfg_element::m_btn_bmp_lit = newui_LoadBitmap(IGNORE_TABLE(NEWUI_BTNLIT_FILE));
    cfg_element::m_btn_bmp = newui_LoadBitmap(IGNORE_TABLE(NEWUI_BTN_FILE));
    cfg_element::m_xbtn_bmp_lit = newui_LoadBitmap(IGNORE_TABLE(NEWUI_TINYBTNLIT_FILE));
    cfg_element::m_xbtn_bmp = newui_LoadBitmap(IGNORE_TABLE(NEWUI_TINYBTN_FILE));
  }
  cfg_element::m_count++;

  UIGadget::Create(wnd, id, x, y, 10, 10, 0);

  if (id == -1) {
    UIGadget::Disable();
  }
}

void cfg_element::OnFormat() {
  UITextItem title(MONITOR9_NEWUI_FONT, m_title, NEWUI_MONITORFONT_COLOR);
  m_W = CFGELEM_BTN_X + (N_CFGELEM_SLOTS * (m_btn_bmp->width() + 2));
  m_H = title.height();
}

void cfg_element::OnDraw() {
  // draw text, then buttons, then...
  UITextItem title(MONITOR9_NEWUI_FONT, m_title, NEWUI_MONITORFONT_COLOR);

  int x = 0, i;

  if (m_infocus) {
    title.set_alpha(m_slot_alpha);
  }

  if (m_fnid != -1) {
    UITextItem text(GADGET9_NEWUI_FONT, "?", NEWUI_GADGETFONT_COLOR);
    if (m_curslot == CFGELEM_SLOT_CLEAR && CHECK_FLAG(m_flags, F_ELEM_HILITE)) {
      m_xbtn_bmp_lit->draw(x, 0);
    } else {
      m_xbtn_bmp->draw(x, 0);
    }
    text.draw(x + (m_xbtn_bmp->width() - text.width()) / 2, 1 + (m_xbtn_bmp->height() - text.height()) / 2);
    x += 28;
  }

  title.draw(x, 0);

  if (m_fnid != -1) {
    ct_type ctype[CTLBINDS_PER_FUNC];
    uint8_t cfgflags[CTLBINDS_PER_FUNC];
    ct_config_data cfgdata;
    tCfgDataParts cfgparts;

    x = CFGELEM_BTN_X;

    Controller->get_controller_function(m_fnid, ctype, &cfgdata, cfgflags);
    parse_config_data(&cfgparts, ctype[0], ctype[1], cfgdata);

    for (i = 0; i < N_CFGELEM_SLOTS; i++) {
      const char *txt;
      uint8_t one_binding = (i == 0) ? cfgparts.bind_0 : cfgparts.bind_1;
      uint8_t one_ctrlbind = (i == 0) ? cfgparts.ctrl_0 : cfgparts.ctrl_1;

      txt = cfg_binding_text(ctype[i], one_ctrlbind, one_binding);

      // draw button
      if (CHECK_FLAG(m_flags, F_ELEM_HILITE) && m_curslot == i) {
        m_btn_bmp_lit->draw(x, 0);
      } else {
        m_btn_bmp->draw(x, 0);
      }

      // draw text
      if (txt) {
        UITextItem text(GADGET9_NEWUI_FONT, txt, NEWUI_GADGETFONT_COLOR);

        if (m_infocus) {
          if (m_curslot == i) {
            text.set_alpha(m_slot_alpha);
          }
        }

        text.draw(x + (m_btn_bmp->width() - text.width()) / 2, (m_btn_bmp->height() - text.height()) / 2);
      }

      x += (m_btn_bmp->width() + 2);
    }

    m_slot_alpha += m_blink_state;
    if (m_slot_alpha == 25) {
      m_blink_state = 25;
    } else if (m_slot_alpha == 250) {
      m_blink_state = -25;
    }
  }
}

void cfg_element::OnKeyDown(int key) {
  if (key == KEY_RIGHT && m_curslot < (N_CFGELEM_SLOTS - 1)) {
    m_curslot++;
  } else if (key == KEY_LEFT && m_curslot > 0) {
    m_curslot--;
  } else if (key == (KEY_CTRLED + KEY_C)) {
    // clear binding.
    tCfgDataParts cfgparts;
    ct_type ctype_fn[CTLBINDS_PER_FUNC];
    uint8_t cfgflags_fn[CTLBINDS_PER_FUNC];
    ct_config_data ccfgdata_fn;

    Controller->get_controller_function(m_fnid, ctype_fn, &ccfgdata_fn, cfgflags_fn);
    parse_config_data(&cfgparts, ctype_fn[0], ctype_fn[1], ccfgdata_fn);
    if (m_curslot == 0) {
      cfgparts.bind_0 = NULL_BINDING;
      cfgparts.ctrl_0 = NULL_CONTROLLER;
    } else if (m_curslot == 1) {
      cfgparts.bind_1 = NULL_BINDING;
      cfgparts.ctrl_1 = NULL_CONTROLLER;
    }
    ccfgdata_fn = unify_config_data(&cfgparts);
    Controller->set_controller_function(m_fnid, ctype_fn, ccfgdata_fn, cfgflags_fn);

  } else if (key == (KEY_SHIFTED + KEY_SLASH)) {
    m_slot = CFGELEM_SLOT_CLEAR;
    OnSelect();
  }
}

void cfg_element::OnMouseBtnDown(int btn) {
  if (btn == UILMSEBTN) {
    int gadmx = SCREEN_TO_GAD_X(this, UI_input.mx), gadmy = SCREEN_TO_GAD_Y(this, UI_input.my);
    int x = 0;
    int8_t curslot;

    // determine what is the current slot
    curslot = -1;

    if (PT_IN_RECT(gadmx, gadmy, x, 0, x + m_xbtn_bmp->width(), m_xbtn_bmp->height())) {
      curslot = CFGELEM_SLOT_CLEAR;
    }

    x = CFGELEM_BTN_X;
    if (PT_IN_RECT(gadmx, gadmy, x, 0, x + m_btn_bmp->width(), m_btn_bmp->height())) {
      curslot = 0;
    }

    x += m_btn_bmp->width() + 2;
    if (PT_IN_RECT(gadmx, gadmy, x, 0, x + m_btn_bmp->width(), m_btn_bmp->height())) {
      curslot = 1;
    }

    // if not active and mouse button is down in a box, flag as active if not already active.
    if (!CHECK_FLAG(m_flags, F_ELEM_ACTIVE)) {
      m_slot = -1;
      if (curslot != -1) {
        m_flags |= F_ELEM_ACTIVE;
        LOCK_FOCUS(this);
        m_curslot = curslot;
      }
    }

    // if gadget is active, then check if we should be highlighted
    if (CHECK_FLAG(m_flags, F_ELEM_ACTIVE)) {
      if (curslot != -1 && m_curslot == curslot) {
        m_flags |= F_ELEM_HILITE;
      } else {
        m_flags &= (~F_ELEM_HILITE);
      }
    }
  }
}

void cfg_element::OnMouseBtnUp(int btn) {
  if (btn == UILMSEBTN) {
    // only do something if active.
    if (CHECK_FLAG(m_flags, F_ELEM_ACTIVE)) {
      UNLOCK_FOCUS(this);
      if (CHECK_FLAG(m_flags, F_ELEM_HILITE)) {
        OnSelect();
        m_slot = m_curslot;
      } else {
        m_slot = -1;
      }
    }
    m_flags &= ~(F_ELEM_HILITE + F_ELEM_ACTIVE);
    //		m_curslot = -1;
  }
}

void cfg_element::OnLostFocus() {
  m_blink_state = 0;
  m_slot_alpha = 250;
}

void cfg_element::OnGainFocus() {
  m_slot_alpha = 250;
  m_blink_state = -25;
  m_curslot = 0;
}

void cfg_element::OnDestroy() {
  cfg_element::m_count--;
  if (cfg_element::m_count <= 0) {
    cfg_element::m_count = 0;
    newui_FreeBitmap(cfg_element::m_btn_bmp);
    newui_FreeBitmap(cfg_element::m_btn_bmp_lit);
    newui_FreeBitmap(cfg_element::m_xbtn_bmp);
    newui_FreeBitmap(cfg_element::m_xbtn_bmp_lit);
  }
}

// calls configuration routines
bool cfg_element::Configure(ct_type *new_elem_type, uint8_t *controller, uint8_t *new_cfg_element, int8_t *cfg_slot) {
  cfg_element_ui cfg_box;
  ct_type ctype_fn[CTLBINDS_PER_FUNC];
  uint8_t cfgflags_fn[CTLBINDS_PER_FUNC];
  ct_config_data ccfgdata_fn;
  tCfgDataParts cfgparts;
  uint8_t element, ctrl;
  bool configure = false;

  int8_t fnid = m_fnid;
  int8_t slot = m_slot;

  if (m_fnid == -1) {
    Int3(); // get samir
    return false;
  }

  // determine which configuration pipe to go down
  Controller->get_controller_function(fnid, ctype_fn, &ccfgdata_fn, cfgflags_fn);

  if (!new_elem_type) {
    cfgparts.bind_0 = NULL_BINDING;
    cfgparts.bind_1 = NULL_BINDING;
    cfgparts.ctrl_0 = NULL_CONTROLLER;
    cfgparts.ctrl_1 = NULL_CONTROLLER;

    ccfgdata_fn = unify_config_data(&cfgparts);
    cfgflags_fn[0] = 0;
    cfgflags_fn[1] = 0;

    Controller->set_controller_function(fnid, ctype_fn, ccfgdata_fn, cfgflags_fn);
    return false;
  }

  ASSERT(slot < N_CFGELEM_SLOTS && slot >= 0);

  parse_config_data(&cfgparts, ctype_fn[0], ctype_fn[1], ccfgdata_fn);
  element = (slot == 0) ? cfgparts.bind_0 : cfgparts.bind_1;
  ctrl = (slot == 0) ? cfgparts.ctrl_0 : cfgparts.ctrl_1;

  // check if we can configure this slot.
  switch (ctype_fn[slot]) {
  case ctNone:
    break;
  case ctKey:
    configure = true;
    break;
  case ctMouseButton:
  case ctButton:
  case ctPOV:
  case ctPOV2:
  case ctPOV3:
  case ctPOV4:
  case ctAxis:
  case ctMouseAxis:
    configure = true;
    break;
  }

  // do configuration requested
  *new_elem_type = ctNone;
  *new_cfg_element = NULL_BINDING;
  *controller = NULL_CONTROLLER;
  *cfg_slot = -1;
  if (configure) {
    const char *txt = m_title;
    cfg_box.Create(txt, ctype_fn[slot], ctrl, element);
    cfg_box.Open();
    if (cfg_box.DoUI() == UID_OK) {
      *new_elem_type = cfg_box.GetType();
      *new_cfg_element = cfg_box.GetElement();
      *controller = cfg_box.GetController();
      *cfg_slot = m_slot;
      configure = true;
    } else {
      configure = false;
    }
    cfg_box.Close();
    cfg_box.Destroy();
  }

  return configure;
}

//////////////////////////////////////////////////////////////////////////////
bool key_cfg_element(uint8_t *element, uint8_t *flags) {
  //	put up configuration dialog

  return true;
}

void cfg_element_ui::Create(const char *title, ct_type type, uint8_t controller, uint8_t element) {
  m_controller = controller;
  m_element = element;
  m_type = type;

  newuiMessageBox::Create(title, MSGBOX_NULL);

  // put appropriate instructions in messagebox
  newuiSheet *sheet = newuiMessageBox::GetSheet();

  switch (type) {
  case ctNone:
    break;
  case ctKey:
    sheet->AddText(TXT_CTLBINDHELP1);
    break;
  case ctButton:
  case ctMouseButton:
  case ctPOV:
  case ctPOV2:
  case ctPOV3:
  case ctPOV4:
    sheet->AddText(TXT_CTLBINDHELP2_0);
    sheet->AddText(TXT_CTLBINDHELP2_1);
    break;

  case ctAxis:
  case ctMouseAxis:
    sheet->AddText(TXT_CTLBINDHELP3_0);
    sheet->AddText(TXT_CTLBINDHELP3_1);
    break;
  }
}

#define GCV_CONTROLLER(_r) (CONTROLLER_CTL1_INFO(CONTROLLER_INFO(ccfgdata)))
#define GCV_VALUE(_r) (CONTROLLER_CTL1_VALUE(CONTROLLER_VALUE(ccfgdata)))
#define GCV_VALID_RESULT(_r) (CONTROLLER_CTL1_INFO(CONTROLLER_INFO(ccfgdata)) != (int8_t)NULL_CONTROLLER)

int cfg_element_ui::DoUI() {
  extern void ddio_MouseQueueFlush();

  int retval = UID_OK;
  bool quit = false, catch_press = false;
  int8_t adj;

  m_alpha = 16;
  adj = -1;

  ui_HideCursor();

  Descent->delay(0.3f);
  ResumeControls();
  Control_poll_flag = false; // under multiplayer, the game frame is still running, so don't let
                             // assignments make it down to game frame (HACK)
  newuiMessageBox::GetSheet()->Realize();
  while (!quit) {
    int key;

    Descent->defer();
    key = ddio_KeyInKey();

    // quit if escape pressed
    if (key == KEY_ESC) {
      retval = UID_CANCEL;
      quit = true;
    }

    // input must go here.
    switch (m_type) {
    case ctKey: {
      // perform simple key processing.
      if (key > 0) {
        if (Ctltext_KeyBindings[key & 0xff]) {
          m_element = (key & 0xff);
          quit = true;
        } else {
          //	here tell user that this key can't be bound.
        }
      }
      break;
    }
    case ctButton:
    case ctMouseButton:
    case ctPOV:
    case ctPOV2:
    case ctPOV3:
    case ctPOV4: {
      ct_config_data ccfgdata;
      ct_type new_type;

      // get each type of input.
      Controller->poll();

      ccfgdata = Controller->get_controller_value(ctMouseButton);
      new_type = ctMouseButton;
      if (!GCV_VALID_RESULT(ccfgdata)) {
        ccfgdata = Controller->get_controller_value(ctPOV);
        new_type = ctPOV;
        if (!GCV_VALID_RESULT(ccfgdata)) {
          ccfgdata = Controller->get_controller_value(ctPOV2);
          new_type = ctPOV2;
          if (!GCV_VALID_RESULT(ccfgdata)) {
            ccfgdata = Controller->get_controller_value(ctPOV3);
            new_type = ctPOV3;
            if (!GCV_VALID_RESULT(ccfgdata)) {
              ccfgdata = Controller->get_controller_value(ctPOV4);
              new_type = ctPOV4;
              if (!GCV_VALID_RESULT(ccfgdata)) {
                ccfgdata = Controller->get_controller_value(ctButton); // read hats before buttons
                new_type = ctButton;
              }
            }
          }
        }
      }
      if (GCV_VALID_RESULT(ccfgdata) && !catch_press) {
        m_type = new_type;
        m_element = GCV_VALUE(ccfgdata);
        m_controller = GCV_CONTROLLER(ccfgdata);
        catch_press = true;
        //	mprintf(0, "HERE?\n");
      } else if (catch_press) {
        quit = true;
        //	mprintf(0, "THERE?\n");
      }
      break;
    }

    case ctAxis:
    case ctMouseAxis: {
      ct_config_data ccfgdata;
      ct_type new_type;

      // get each type of input.
      Controller->poll();

      ccfgdata = Controller->get_controller_value(ctAxis);
      new_type = ctAxis;

      if (!GCV_VALID_RESULT(ccfgdata)) {
        ccfgdata = Controller->get_controller_value(ctMouseAxis);
        new_type = ctMouseAxis;
      }
      if (GCV_VALID_RESULT(ccfgdata)) {
        m_type = new_type;
        m_element = GCV_VALUE(ccfgdata);
        m_controller = GCV_CONTROLLER(ccfgdata);
        quit = true;
      }
      break;
    }

    case ctNone:
      quit = true;
      break;

    default:
      Int3();
      quit = true;
    }

    DoUIFrameWithoutInput();
    rend_Flip();

    if (GetUIFrameResult() == NEWUIRES_FORCEQUIT) {
      quit = true;
    }

    m_alpha += adj;
    if (m_alpha < -15) {
      m_alpha = -15;
      adj = 1;
    } else if (m_alpha > 16) {
      m_alpha = 16;
      adj = -1;
    }
  }
  newuiMessageBox::GetSheet()->Unrealize();

  SuspendControls();

  ui_ShowCursor();
  ddio_MouseQueueFlush();
  ui_Flush();

  return UID_OK;
}

void cfg_element_ui::OnDraw() {
  UITextItem prompt(MONITOR9_NEWUI_FONT, "?", NEWUI_MONITORFONT_COLOR, (uint8_t)(m_alpha * 8) + 127);

  newuiMessageBox::OnDraw();

  prompt.draw(16, 60);
}
