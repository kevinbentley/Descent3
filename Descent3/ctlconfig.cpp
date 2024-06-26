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

 * $Logfile: /DescentIII/main/ctlconfig.cpp $
 * $Revision: 78 $
 * $Date: 4/19/00 5:25p $
 * $Author: Matt $
 *
 * <insert description of file here>
 *
 * $Log: /DescentIII/main/ctlconfig.cpp $
 *
 * 78    4/19/00 5:25p Matt
 * From Duane for 1.4
 * Several Mac config changes
 * Fixed a bug that caused the deadzone value to be decreased each time
 * you the  config dialog was used.
 *
 * 77    3/20/00 12:03p Matt
 * Merge of Duane's post-1.3 changes.
 * Mac deadzone stuff (Mac only)
 *
 * 76    10/22/99 3:40p Kevin
 * Mac merge fixes
 *
 * 75    10/22/99 10:50a Matt
 * Mac merge
 *
 * 74    7/28/99 4:18p Kevin
 * Macintosh!
 *
 * 73    7/16/99 11:16a Samir
 * multiple hat support.
 *
 * 72    6/10/99 9:07p Samir
 * fixed weapon string name localization issues.
 *
 * 71    5/12/99 1:18p Samir
 * play music during game too when in menus.
 *
 * 70    5/06/99 1:40a Samir
 * adjusted some text.
 *
 * 69    5/02/99 2:19a Samir
 * new weapon autoselect interface (a little more like D2)
 *
 * 68    4/30/99 12:12p Samir
 * added strings for key ramping, other buttons in general config menu.
 *
 * 67    4/29/99 2:59p Samir
 * added help and made CTRL-C clear for controller screens.
 *
 * 66    4/29/99 2:18a Samir
 * updated art for options style menu.
 *
 * 65    4/22/99 3:43p Kevin
 * Training missions show controls on screen
 *
 * 64    4/19/99 5:09p Samir
 * ugh, forgot to destroy revert gadget when unrealizing ui page.
 *
 * 63    4/18/99 4:21p Samir
 * added restore settings for either joystick or keyboard settings.
 *
 * 62    4/15/99 2:55p Samir
 * added UI for mouselook.
 *
 * 61    3/22/99 6:20p Jeff
 * added 2 more audio taunts.  a mulitplayer event when someone plays an
 * audio taunt.  option to disable audio taunts.
 *
 * 60    3/17/99 4:18p Samir
 * added button to calibrate joystick.
 *
 * 59    3/05/99 2:44p Samir
 * needs to be cleaned up later, but mouse and joystick sensitivities are
 * read in always, and set by the controller system.   A cancel method
 * needs to be implemented for these functions.
 *
 * 58    3/05/99 12:24p Samir
 * weapon select screen has more help to determine what's high and what's
 * low.
 *
 * 57    3/03/99 3:41a Samir
 * moved ok and cancel buttons in weapon_select_dialog.
 *
 * 56    3/02/99 1:14p Samir
 * added joystick/mouse enable and gamma help.
 *
 * 55    3/01/99 8:51p Samir
 * fixed potential crash with no forcefeedback.
 *
 * 54    3/01/99 8:12p Samir
 * don;t display force feedback menu if no stick.
 *
 * 53    3/01/99 5:01a Samir
 * made sure NEWUIRES_FORCEQUIT was added to all new interfaces.
 *
 * 52    2/28/99 3:22a Samir
 * added rearview text.
 *
 * 51    2/26/99 2:13a Samir
 * massive reorg of weapon select prec
 *
 * 50    2/24/99 6:21p Samir
 * moved sensitivity sliders to config key/controller and cleaned up
 * weapon select menu.
 *
 * 49    2/24/99 12:41p Samir
 * put in weapon selection.
 *
 * 48    2/23/99 2:00p Samir
 * added keyboard ramping slider.
 *
 * 47    2/19/99 11:07p Samir
 * don't verify control changes if new element has a NULL controller
 * instead of a null binding (hats can have a 'null binding' and be valid.
 *
 * 46    2/16/99 12:07p Samir
 * redid controller config with new ui.
 *
 * 45    2/10/99 3:39p Samir
 * table file parsing stuff
 *
 * 44    1/28/99 3:58p Jeff
 * localization update
 *
 * 43    1/06/99 6:33p Samir
 * more hacks for demo.
 *
 * 42    1/06/99 6:28p Samir
 * demo hack for controller checkbox code not in sync with UI checkbox
 * code.
 *
 * 41    12/17/98 5:59p Samir
 * moved mouse enabled and joy enabled to config menu.
 *
 * 40    11/30/98 4:54p Samir
 * added rear view config item.
 *
 * 39    10/22/98 10:54p Samir
 * put mouse or joystick disabled messages if pilot disabled them, to help
 * those configuring.
 *
 * 38    10/21/98 11:14a Samir
 * added generic code to skip rendering while in game controller config or
 * telcom.
 *
 * 37    10/18/98 7:24p Samir
 * added a reset to defaults options for key and joystick config.
 *
 * 36    10/18/98 1:07p Samir
 * tweaked user interface for controller config.
 *
 * 35    10/17/98 7:33p Samir
 * fixed bug when initializing elements list per panel.
 *
 * 34    10/13/98 6:33p Samir
 * poll mulitplayer every frame if needed in controller config screen.
 *
 * 33    10/07/98 6:29p Samir
 * bail if multiplayer game ended in ui.
 *
 * 32    10/02/98 4:15p Samir
 * added fancy artwork for config screens.
 *
 * 31    10/01/98 12:57p Samir
 * basic weapon autoselect config working.
 *
 * 30    9/30/98 4:35p Samir
 * revamped control configuration ui,
 *
 * 29    9/23/98 6:19p Jeff
 * finished up (hopefully) updating the config/ui dialogs to meet our
 * standard.  Keyboard/joystick config still needs some work
 *
 * 28    9/17/98 3:24p Samir
 * added headlight configuration.
 *
 * 27    9/10/98 12:39p Samir
 * added senstivity issures for controller.
 *
 * 26    8/31/98 6:49p Jeff
 * made inventory and countermeasure keys customizable
 *
 * 25    6/29/98 6:42p Samir
 * Properly handle controller pausing and resumption.
 *
 * 24    6/18/98 5:49p Samir
 * finished controller string localization minus the binding stuff.
 *
 * 23    6/18/98 4:48p Samir
 * added changes for multiple configs for joystick controls.
 *
 * 22    6/17/98 3:27p Jeff
 * Changes made for localization
 *
 * 21    6/16/98 10:38a Jeff
 * localization, strings pulled out to stringtable.h and d3.str
 *
 * 20    6/05/98 5:34p Samir
 * new config system.
 *
 * 19    5/19/98 3:36p Samir
 * added automap key.
 *
 * 18    5/15/98 3:13p Samir
 * added 2 key support for controller functions.
 *
 * 17    5/12/98 3:04p Samir
 * added button control for pbh.
 *
 * 16    5/11/98 4:53p Samir
 * added axis sliding, config.
 *
 * 15    5/05/98 5:15p Samir
 * adjusted menus to work in 512x384 as well as 640x480.
 *
 * 14    4/24/98 2:43a Samir
 * added ability to turn off controller.
 *
 * 13    4/13/98 7:01p Samir
 * added snazzy listbox and edit box art.
 *
 * 12    4/08/98 3:44p Samir
 * added toggle bank and configuration for afterburner
 *
 * 11    3/20/98 1:19p Jeff
 * Changes made to use Default_pilot string for pilot filename to use.
 *
 * 10    3/17/98 2:36p Samir
 * Added Macros.h
 *
 * 9     3/05/98 6:38p Samir
 * Use UI_FONT now.
 *
 * 8     2/16/98 9:27p Samir
 * Simple joystick configuration working.
 *
 * 7     2/16/98 3:02p Samir
 * Joystick config sort of working.
 *
 * 6     2/15/98 7:06p Samir
 * Keyboard configuration system done.  Not joystick.
 *
 * 5     2/13/98 7:10p Samir
 * Fixed prob when pressing ALT (since it set a bit in the return key
 * value that's greater that 256)
 *
 * 4     2/13/98 6:37p Samir
 * Simple keyboard configuration.
 *
 * 3     2/10/98 4:55p Samir
 * Added rudimentary items for controller config.
 *
 * 2     2/10/98 3:45p Samir
 * Added list of configuration items.
 *
 * 1     2/10/98 11:49a Samir
 * Initial revision.
 *
 * $NoKeywords: $
 */
#include "ctlconfig.h"
#include "CtlCfgElem.h"
#include "ctlconfigtxt.h"
#include "game.h"
#include "weapon.h"
#include "pilot.h"
#include "bitmap.h"
#include "multi.h"
#include "gameloop.h"
#include "gamefont.h"
#include "D3ForceFeedback.h"
#include "hlsoundlib.h"
#include "ddio.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////
#define IDV_KCONFIG 10
#define IDV_CCONFIG 11
#define IDV_WPNSEL 17
#define IDV_OPTIONS 18

// used for adjusting settings.
#define CFG_AXIS_SENS_RANGE 20
const int16_t UID_JOYCFG = 0x1000;


//	Setup of config screens.
#define CCITEM_WPN_X 0
#define CCITEM_WPN_Y 20
#define CCITEM_AUX_X 0
#define CCITEM_AUX_Y 160
#define CCITEM_THRUST_X 295
#define CCITEM_THRUST_Y 20
#define CCITEM_ROT_X 295
#define CCITEM_ROT_Y 160
t_cfg_element Cfg_key_elements[] = {
    // column1 -indices 0-15
    {-1, CtlText_WeaponGroup, CCITEM_WPN_X, CCITEM_WPN_Y},
    {ctfFIREPRIMARY_KEY, CtlText_FirePrimary, 0, 0},
    {ctfFIRESECONDARY_KEY, CtlText_FireSecondary, 0, 0},
    {ctfFIREFLARE_KEY, CtlText_FireFlare, 0, 0},
    {ctfWPNSEL_PCYCLEKEY, CtlText_WpnCycP, 0, 0},
    {ctfWPNSEL_SCYCLEKEY, CtlText_WpnCycS, 0, 0},
    {-1, CtlText_MiscGroup, CCITEM_AUX_X, CCITEM_AUX_Y},
    {ctfHEADLIGHT_KEY, CtlText_Headlight, 0, 0},
    {ctfREARVIEW_KEY, CtlText_Rearview, 0, 0},
    {ctfAUTOMAP_KEY, CtlText_Automap, 0, 0},
    {ctfPREV_INVKEY, CtlText_PrevInv, 0, 0},
    {ctfNEXT_INVKEY, CtlText_NextInv, 0, 0},
    {ctfINV_USEKEY, CtlText_InvUse, 0, 0},
    {ctfPREV_CNTMSKEY, CtlText_PrevCntMs, 0, 0},
    {ctfNEXT_CNTMSKEY, CtlText_NextCntMs, 0, 0},
    {ctfCNTMS_USEKEY, CtlText_CntMsUse, 0, 0},
    {ctfAUDIOTAUNT1_KEY, CtlText_AudioTaunt1, 0, 0},
    {ctfAUDIOTAUNT2_KEY, CtlText_AudioTaunt2, 0, 0},
    {ctfAUDIOTAUNT3_KEY, CtlText_AudioTaunt3, 0, 0},
    {ctfAUDIOTAUNT4_KEY, CtlText_AudioTaunt4, 0, 0},
    {-1, CtlText_ThrustGroup, CCITEM_THRUST_X, CCITEM_THRUST_Y},
    {ctfFORWARD_THRUSTKEY, CtlText_Accelerate, 0, 0},
    {ctfREVERSE_THRUSTKEY, CtlText_Reverse, 0, 0},
    {ctfAFTERBURN_KEY, CtlText_Afterburn, 0, 0},
    {ctfTOGGLE_SLIDEKEY, CtlText_ToggleSlide, 0, 0},
    {ctfLEFT_THRUSTKEY, CtlText_SlideLeft, 0, 0},
    {ctfRIGHT_THRUSTKEY, CtlText_SlideRight, 0, 0},
    {ctfUP_THRUSTKEY, CtlText_SlideUp, 0, 0},
    {ctfDOWN_THRUSTKEY, CtlText_SlideDown, 0, 0},
    {-1, CtlText_TurningGroup, CCITEM_ROT_X, CCITEM_ROT_Y},
    {ctfPITCH_UPKEY, CtlText_PitchUp, 0, 0},
    {ctfPITCH_DOWNKEY, CtlText_PitchDown, 0, 0},
    {ctfHEADING_LEFTKEY, CtlText_TurnLeft, 0, 0},
    {ctfHEADING_RIGHTKEY, CtlText_TurnRight, 0, 0},
    {ctfTOGGLE_BANKKEY, CtlText_ToggleBank, 0, 0},
    {ctfBANK_LEFTKEY, CtlText_BankLeft, 0, 0},
    {ctfBANK_RIGHTKEY, CtlText_BankRight, 0, 0}};
#define CCITEM_WPN_X2 0
#define CCITEM_WPN_Y2 20
#define CCITEM_AUX_X2 0
#define CCITEM_AUX_Y2 160
#define CCITEM_THRUST_X2 295
#define CCITEM_THRUST_Y2 20
#define CCITEM_ROT_X2 295
#define CCITEM_ROT_Y2 200
t_cfg_element Cfg_joy_elements[] = {{-1, CtlText_WeaponGroup, CCITEM_WPN_X2, CCITEM_WPN_Y2},
                                    {ctfFIREPRIMARY_BUTTON, CtlText_FirePrimary, 0, 0},
                                    {ctfFIRESECONDARY_BUTTON, CtlText_FireSecondary, 0, 0},
                                    {ctfFIREFLARE_BUTTON, CtlText_FireFlare, 0, 0},
                                    {ctfWPNSEL_PCYCLEBTN, CtlText_WpnCycP, 0, 0},
                                    {ctfWPNSEL_SCYCLEBTN, CtlText_WpnCycS, 0, 0},
                                    {-1, CtlText_MiscGroup, CCITEM_AUX_X2, CCITEM_AUX_Y2},
                                    {ctfHEADLIGHT_BUTTON, CtlText_Headlight, 0, 0},
                                    {ctfREARVIEW_BTN, CtlText_Rearview, 0, 0},
                                    {ctfAUTOMAP_BUTTON, CtlText_Automap, 0, 0},
                                    {ctfPREV_INVBTN, CtlText_PrevInv, 0, 0},
                                    {ctfNEXT_INVBTN, CtlText_NextInv, 0, 0},
                                    {ctfINV_USEBTN, CtlText_InvUse, 0, 0},
                                    {ctfPREV_CNTMSBTN, CtlText_PrevCntMs, 0, 0},
                                    {ctfNEXT_CNTMSBTN, CtlText_NextCntMs, 0, 0},
                                    {ctfCNTMS_USEBTN, CtlText_CntMsUse, 0, 0},
                                    {ctfAUDIOTAUNT1_BTN, CtlText_AudioTaunt1, 0, 0},
                                    {ctfAUDIOTAUNT2_BTN, CtlText_AudioTaunt2, 0, 0},
                                    {ctfAUDIOTAUNT3_BTN, CtlText_AudioTaunt3, 0, 0},
                                    {ctfAUDIOTAUNT4_BTN, CtlText_AudioTaunt4, 0, 0},
                                    {-1, CtlText_ThrustGroup, CCITEM_THRUST_X2, CCITEM_THRUST_Y2},
                                    {ctfFORWARD_THRUSTAXIS, CtlText_Forward, 0, 0},
                                    {ctfFORWARD_BUTTON, CtlText_Accelerate, 0, 0},
                                    {ctfREVERSE_BUTTON, CtlText_Reverse, 0, 0},
                                    {ctfAFTERBURN_BUTTON, CtlText_Afterburn, 0, 0},
                                    {ctfUP_THRUSTAXIS, CtlText_SlideVert, 0, 0},
                                    {ctfRIGHT_THRUSTAXIS, CtlText_SlideHoriz, 0, 0},
                                    {ctfTOGGLE_SLIDEBUTTON, CtlText_ToggleSlide, 0, 0},
                                    {ctfUP_BUTTON, CtlText_SlideUp, 0, 0},
                                    {ctfDOWN_BUTTON, CtlText_SlideDown, 0, 0},
                                    {ctfLEFT_BUTTON, CtlText_SlideLeft, 0, 0},
                                    {ctfRIGHT_BUTTON, CtlText_SlideRight, 0, 0},
                                    {-1, CtlText_TurningGroup, CCITEM_ROT_X2, CCITEM_ROT_Y2},
                                    {ctfPITCH_DOWNAXIS, CtlText_Pitch, 0, 0},
                                    {ctfPITCH_UPBUTTON, CtlText_PitchUp, 0, 0},
                                    {ctfPITCH_DOWNBUTTON, CtlText_PitchDown, 0, 0},
                                    {ctfHEADING_RIGHTAXIS, CtlText_Heading, 0, 0},
                                    {ctfHEADING_LEFTBUTTON, CtlText_TurnLeft, 0, 0},
                                    {ctfHEADING_RIGHTBUTTON, CtlText_TurnRight, 0, 0},
                                    {ctfBANK_RIGHTAXIS, CtlText_Bank, 0, 0},
                                    {ctfTOGGLE_BANKBUTTON, CtlText_ToggleBank, 0, 0},
                                    {ctfBANK_LEFTBUTTON, CtlText_BankLeft, 0, 0},
                                    {ctfBANK_RIGHTBUTTON, CtlText_BankRight, 0, 0}};
#define N_JOY_CFG_FN (sizeof(Cfg_joy_elements) / sizeof(t_cfg_element))
#define N_KEY_CFG_FN (sizeof(Cfg_key_elements) / sizeof(t_cfg_element))
static void ctl_cfg_set_and_verify_changes(int16_t fnid, ct_type elem_type, uint8_t controller, uint8_t elem, int8_t slot);
static void ctl_cfg_element_options_dialog(int16_t fnid);
// used for adjusting settings.
static int weapon_select_dialog(int wpn, bool is_secondary);
#define UID_KEYCFG_ID 0x1000
#define UID_JOYCFG_ID 0x1100
#define UID_PRIMARY_WPN 0x1200
#define UID_PRIMARY_DIS 0x1220
#define UID_SECONDARY_WPN 0x1300
#define UID_SECONDARY_DIS 0x1320
#define UID_WPNLIST 0x1400
#define UID_RESETDEFAULTS 0x2000
#define UID_CFGSETTINGS 0x2001
#define UID_CLEAR_SLOT 0x2002
#define UID_REVERT 0x2003
//////////////////////////////////////////////////////////////////////////////
//
class cfg_screen {
protected:
  newuiSheet *m_sheet;
  newuiLargeMenu *m_menu;

public:
  virtual void setup(newuiLargeMenu *menu) = 0;
  virtual void finish() = 0;
  virtual void realize() = 0;
  virtual void unrealize() = 0;
  virtual void process(int res){};
};
//////////////////////////////////////////////////////////////////////////////
// KEY CONFIG
#define KEYCFG_EXTRAS_X 0
#define KEYCFG_EXTRAS_Y 4
#define KEYCFG_EXTRAS_W 160
class key_cfg_screen : public cfg_screen {
  cfg_element m_elem[N_KEY_CFG_FN];
  newuiButton m_reset_btn;
  newuiButton m_key_settings;
  newuiButton m_revert_btn;
  UIText m_help1_txt;
  UIText m_help2_txt;
  cntrldata m_old_controls[N_KEY_CFG_FN];

public:
  virtual void setup(newuiLargeMenu *menu);
  virtual void finish();
  virtual void process(int res);
  virtual void realize();
  virtual void unrealize();
};
void key_cfg_screen::setup(newuiLargeMenu *menu) {
  int i;
  m_menu = menu;
  m_sheet = menu->AddOption(IDV_KCONFIG, TXT_OPTCUSTKEYB);
  // save original settings.
  for (i = 0; i < N_KEY_CFG_FN; i++) {
    Controller->get_controller_function(Cfg_key_elements[i].fn_id, m_old_controls[i].type, &m_old_controls[i].value,
                                        m_old_controls[i].flags);
  }
}
void key_cfg_screen::finish() {}
void key_cfg_screen::process(int res) {
  int i;
  for (i = 0; i < N_KEY_CFG_FN; i++) {
    if (m_elem[i].GetID() != -1 && m_elem[i].GetID() == res) {
      // we chose a slot to configure.
      uint8_t elem, controller;
      int8_t slot;
      ct_type elem_type;
      if (m_elem[i].GetActiveSlot() == CFGELEM_SLOT_CLEAR) {
        ctl_cfg_element_options_dialog((int16_t)(res - UID_KEYCFG_ID));
      } else if (m_elem[i].Configure(&elem_type, &controller, &elem, &slot)) {
        ctl_cfg_set_and_verify_changes((int16_t)(res - UID_KEYCFG_ID), elem_type, controller, elem, slot);
      }
      break;
    }
  }
  switch (res) {
  case UID_RESETDEFAULTS:
    for (i = 0; i < NUM_CONTROLLER_FUNCTIONS; i++) {
      if (Controller_needs[i].ctype[0] == ctKey) {
        ASSERT(Controller_needs[i].ctype[1] == ctKey);
        Controller->assign_function(&Controller_needs[i]);
      }
    }
    break;
  case UID_CFGSETTINGS:
    key_settings_dialog();
    break;
  case UID_REVERT:
    // restore original settings.
    for (i = 0; i < N_KEY_CFG_FN; i++) {
      Controller->set_controller_function(Cfg_key_elements[i].fn_id, m_old_controls[i].type, m_old_controls[i].value,
                                          m_old_controls[i].flags);
    }
    break;
  }
}
void key_cfg_screen::realize() {
  // create controls
  int i, x = 0, y;
  t_cfg_element *cfg_elem = &Cfg_key_elements[0];
  m_reset_btn.Create(m_menu, UID_RESETDEFAULTS, TXT_RESETTODEFAULT, KEYCFG_EXTRAS_X + m_sheet->X(),
                     KEYCFG_EXTRAS_Y + m_sheet->Y(), NEWUI_BTNF_LONG);
  m_key_settings.Create(m_menu, UID_CFGSETTINGS, TXT_ADJUSTSETTINGS, KEYCFG_EXTRAS_X + m_sheet->X() + KEYCFG_EXTRAS_W,
                        KEYCFG_EXTRAS_Y + m_sheet->Y(), NEWUI_BTNF_LONG);
  m_revert_btn.Create(m_menu, UID_REVERT, TXT_REVERTCONTROLS, KEYCFG_EXTRAS_X + m_sheet->X() + KEYCFG_EXTRAS_W * 2,
                      KEYCFG_EXTRAS_Y + m_sheet->Y(), NEWUI_BTNF_LONG);
  UITextItem itemHelpF1{MONITOR9_NEWUI_FONT, TXT_KEYCFGSCREENHELP1, NEWUI_MONITORFONT_COLOR};
  m_help1_txt.Create(m_menu, &itemHelpF1, 280, 30);
  UITextItem itemHelp{MONITOR9_NEWUI_FONT, TXT_CFGSCREENHELP, NEWUI_MONITORFONT_COLOR};
  m_help2_txt.Create(m_menu, &itemHelp, 280, 40);
  for (i = 0; i < N_KEY_CFG_FN; i++) {
    if (cfg_elem->fn_id == -1) {
      x = cfg_elem->x + m_sheet->X();
      y = cfg_elem->y + m_sheet->Y();
    }
    m_elem[i].Create(m_menu, cfg_elem->text, x, y, cfg_elem->fn_id,
                     (cfg_elem->fn_id == -1) ? -1 : UID_KEYCFG_ID + cfg_elem->fn_id);
    y += m_elem[i].H() + 2;
    cfg_elem++;
  }
}
void key_cfg_screen::unrealize() {
  // create controls
  int i;
  t_cfg_element *cfg_elem = &Cfg_key_elements[0];
  m_help2_txt.Destroy();
  m_help1_txt.Destroy();
  m_key_settings.Destroy();
  m_reset_btn.Destroy();
  m_revert_btn.Destroy();
  for (i = 0; i < N_KEY_CFG_FN; i++) {
    m_elem[i].Destroy();
    cfg_elem++;
  }
}
//////////////////////////////////////////////////////////////////////////////
// JOY CONFIG
class joy_cfg_screen : public cfg_screen {
  cfg_element m_elem[N_JOY_CFG_FN];
  newuiButton m_reset_btn;
  newuiButton m_controller_settings;
  newuiButton m_revert_btn;
  cntrldata m_old_controls[N_JOY_CFG_FN];
  UIText m_help1_txt;
  UIText m_help2_txt;

public:
  virtual void setup(newuiLargeMenu *menu);
  virtual void finish();
  virtual void process(int res);
  virtual void realize();
  virtual void unrealize();
};
// setup user interfaces for each screen.
void joy_cfg_screen::setup(newuiLargeMenu *menu) {
  int i;
  m_menu = menu;
  m_sheet = menu->AddOption(IDV_CCONFIG, TXT_OPTCUSTCONT);

  // save original settings.
  for (i = 0; i < N_JOY_CFG_FN; i++) {
    Controller->get_controller_function(Cfg_joy_elements[i].fn_id, m_old_controls[i].type, &m_old_controls[i].value,
                                        m_old_controls[i].flags);
  }
}
void joy_cfg_screen::finish() {}
void joy_cfg_screen::process(int res) {
  int i;

  for (i = 0; i < N_JOY_CFG_FN; i++) {
    if (m_elem[i].GetID() != -1 && m_elem[i].GetID() == res) {
      // we chose a slot to configure.
      uint8_t elem, controller;
      int8_t slot;
      ct_type elem_type;
      if (m_elem[i].GetActiveSlot() == CFGELEM_SLOT_CLEAR) {
        ctl_cfg_element_options_dialog((int16_t)(res - UID_JOYCFG_ID));
      } else if (m_elem[i].Configure(&elem_type, &controller, &elem, &slot)) {
        ctl_cfg_set_and_verify_changes((int16_t)(res - UID_JOYCFG_ID), elem_type, controller, elem, slot);
      }
      break;
    }
  }
  switch (res) {
  case UID_RESETDEFAULTS:
    for (i = 0; i < NUM_CONTROLLER_FUNCTIONS; i++) {
      if (Controller_needs[i].ctype[0] != ctKey) {
        ASSERT(Controller_needs[i].ctype[1] != ctKey);
        Controller->assign_function(&Controller_needs[i]);
      }
    }
    break;
  case UID_CFGSETTINGS:
    joystick_settings_dialog();
    break;
  case UID_REVERT:
    // restore original settings.
    for (i = 0; i < N_KEY_CFG_FN; i++) {
      Controller->set_controller_function(Cfg_joy_elements[i].fn_id, m_old_controls[i].type, m_old_controls[i].value,
                                          m_old_controls[i].flags);
    }
    break;
  }
}

void joy_cfg_screen::realize() {
  int i, x = 0, y;
  t_cfg_element *cfg_elem = &Cfg_joy_elements[0];
  m_reset_btn.Create(m_menu, UID_RESETDEFAULTS, TXT_RESETTODEFAULT, KEYCFG_EXTRAS_X + m_sheet->X(),
                     KEYCFG_EXTRAS_Y + m_sheet->Y(), NEWUI_BTNF_LONG);
  m_controller_settings.Create(m_menu, UID_CFGSETTINGS, TXT_ADJUSTSETTINGS,
                               KEYCFG_EXTRAS_X + m_sheet->X() + KEYCFG_EXTRAS_W, KEYCFG_EXTRAS_Y + m_sheet->Y(),
                               NEWUI_BTNF_LONG);
  m_revert_btn.Create(m_menu, UID_REVERT, TXT_REVERTCONTROLS, KEYCFG_EXTRAS_X + m_sheet->X() + KEYCFG_EXTRAS_W * 2,
                      KEYCFG_EXTRAS_Y + m_sheet->Y(), NEWUI_BTNF_LONG);
  UITextItem itemHelpF1{MONITOR9_NEWUI_FONT, TXT_JOYCFGSCREENHELP1, NEWUI_MONITORFONT_COLOR};
  m_help1_txt.Create(m_menu, &itemHelpF1, 280, 30);
  UITextItem itemHelp{MONITOR9_NEWUI_FONT, TXT_CFGSCREENHELP, NEWUI_MONITORFONT_COLOR};
  m_help2_txt.Create(m_menu, &itemHelp, 280, 40);
  for (i = 0; i < N_JOY_CFG_FN; i++) {
    if (cfg_elem->fn_id == -1) {
      x = cfg_elem->x + m_sheet->X();
      y = cfg_elem->y + m_sheet->Y();
    }
    m_elem[i].Create(m_menu, cfg_elem->text, x, y, cfg_elem->fn_id,
                     (cfg_elem->fn_id == -1) ? -1 : UID_JOYCFG_ID + cfg_elem->fn_id);
    y += m_elem[i].H() + 2;
    cfg_elem++;
  }
}
void joy_cfg_screen::unrealize() {
  // create controls
  int i;

  m_controller_settings.Destroy();
  t_cfg_element *cfg_elem = &Cfg_joy_elements[0];
  for (i = 0; i < N_JOY_CFG_FN; i++) {
    m_elem[i].Destroy();
    cfg_elem++;
  }
  m_help2_txt.Destroy();
  m_help1_txt.Destroy();
  m_reset_btn.Destroy();
  m_revert_btn.Destroy();
}
//////////////////////////////////////////////////////////////////////////////
// WEAPON SEL CONFIG
#define WPNSEL_PRIMARY_X 70
#define WPNSEL_PRIMARY_Y 170
#define WPNSEL_SECONDARY_X 340
#define WPNSEL_SECONDARY_Y 170
extern float Key_ramp_speed;
class wpnsel_cfg_screen : public cfg_screen {
  UIText m_primary_title;
  UIText m_primary_low;
  UIText m_primary_high;
  newuiTinyButton m_primary_disables[MAX_PRIMARY_WEAPONS];
  newuiButton m_primary_buttons[MAX_PRIMARY_WEAPONS];
  UIText m_secondary_title;
  UIText m_secondary_low;
  UIText m_secondary_high;
  newuiTinyButton m_secondary_disables[MAX_SECONDARY_WEAPONS];
  newuiButton m_secondary_buttons[MAX_SECONDARY_WEAPONS];
  UIText m_weapon_choose;
  newuiButton m_reset_btn;
  int m_selection_status; // -1 = no selection, 0 = primary, 1 = secondary
  int m_switch_slot;

public:
  virtual void setup(newuiLargeMenu *menu);
  virtual void finish();
  virtual void process(int res);
  virtual void realize();
  virtual void unrealize();
};
void wpnsel_cfg_screen::setup(newuiLargeMenu *menu) {
  m_menu = menu;
  m_sheet = menu->AddOption(IDV_WPNSEL, TXT_WPNSELPREC);
  m_sheet->NewGroup(NULL, 0, 20);
  m_sheet->AddText(TXT_WPNCFGHELP0);
  m_sheet->AddText(TXT_WPNCFGHELP1);
  m_selection_status = -1;
  m_switch_slot = -1;
}
void wpnsel_cfg_screen::finish() {}
void wpnsel_cfg_screen::process(int res) {
  int slot, i;
  bool is_secondary = false, do_swap_ui = false, do_disable_ui = false, update_buttons = false;
  mprintf(0, "res=%d\n", res);
  if (m_selection_status == -1) {
    if (res == UID_RESETDEFAULTS) {
      for (i = 0; i < MAX_PRIMARY_WEAPONS; i++)
        SetAutoSelectPrimaryWpnIdx(i, DefaultPrimarySelectList[i]);
      for (i = 0; i < MAX_SECONDARY_WEAPONS; i++)
        SetAutoSelectSecondaryWpnIdx(i, DefaultSecondarySelectList[i]);
      update_buttons = true;
    } else if (res == UID_CLEAR_SLOT) {
      //	figure out id of current gadget highlighted.
      UIGadget *gadget = m_menu->GetFocus();
      if (gadget) {
        // below code will then determine the correct information.
        res = gadget->GetID();
        do_disable_ui = true;
      }
    }
  }
  slot = -1;
  if (res >= UID_PRIMARY_WPN && res < (UID_PRIMARY_WPN + MAX_PRIMARY_WEAPONS) && m_selection_status != 1) {
    slot = res - UID_PRIMARY_WPN;
    is_secondary = false;
    if (!do_disable_ui)
      do_swap_ui = true;
  } else if (res >= UID_SECONDARY_WPN && res < (UID_SECONDARY_WPN + MAX_SECONDARY_WEAPONS) && m_selection_status != 0) {
    slot = res - UID_SECONDARY_WPN;
    is_secondary = true;
    if (!do_disable_ui)
      do_swap_ui = true;
  } else if (res >= UID_PRIMARY_DIS && res < (UID_PRIMARY_DIS + MAX_PRIMARY_WEAPONS) && m_selection_status == -1) {
    slot = res - UID_PRIMARY_DIS;
    is_secondary = false;
    do_disable_ui = true;
  } else if (res >= UID_SECONDARY_DIS && res < (UID_SECONDARY_DIS + MAX_SECONDARY_WEAPONS) &&
             m_selection_status == -1) {
    slot = res - UID_SECONDARY_DIS;
    is_secondary = true;
    do_disable_ui = true;
  }
  mprintf(0, "slot=%d\n", slot);

  // do different uis
  if (do_disable_ui) {
    ASSERT(m_selection_status == -1 && slot != -1);
    uint16_t wpnidx = is_secondary ? GetAutoSelectSecondaryWpnIdx(slot) : GetAutoSelectPrimaryWpnIdx(slot);
    wpnidx = wpnidx ^ WPNSEL_SKIP;
    if (is_secondary) {
      SetAutoSelectSecondaryWpnIdx(slot, wpnidx);
    } else {
      SetAutoSelectPrimaryWpnIdx(slot, wpnidx);
    }
    update_buttons = true;
  }
  // here we see if we are selecting a weapon to switch with another, if one is already selected, we
  // see if the user has selected another (in the same category)
  //
  else if (do_swap_ui) {
    uint16_t wpnidx;
    if (slot != -1) {
      if (m_selection_status == -1) {
        m_switch_slot = slot;
        m_selection_status = is_secondary ? 1 : 0;
        // disable proper controls here.
        for (i = 0; i < MAX_PRIMARY_WEAPONS; i++) {
          if (m_selection_status == 1) {
            m_primary_disables[i].Disable();
            m_primary_buttons[i].Disable();
          } else {
            m_secondary_disables[i].Disable();
            m_secondary_buttons[i].Disable();
          }
        }
        if (!m_weapon_choose.IsCreated()) {
          UIGadget *focused_gadget = m_menu->GetFocus();
          UITextItem item{MONITOR9_NEWUI_FONT, TXT_WPNCFGHELP2, GR_RGB(240, 240, 0)};
          m_weapon_choose.Create(m_menu, &item, WPNSEL_PRIMARY_X, WPNSEL_PRIMARY_Y - 48);
          if (focused_gadget)
            m_menu->SetFocusOnGadget(focused_gadget);
        }
      } else {
        int slot_idx = m_switch_slot;
        uint16_t new_wpnidx =
            is_secondary ? GetAutoSelectSecondaryWpnIdx(m_switch_slot) : GetAutoSelectPrimaryWpnIdx(m_switch_slot);

        ASSERT(m_switch_slot != -1);
        if (slot > m_switch_slot) {
          new_wpnidx =
              is_secondary ? GetAutoSelectSecondaryWpnIdx(m_switch_slot) : GetAutoSelectPrimaryWpnIdx(m_switch_slot);
          while (slot_idx < slot) {
            if (is_secondary) {
              wpnidx = GetAutoSelectSecondaryWpnIdx(slot_idx + 1);
              SetAutoSelectSecondaryWpnIdx(slot_idx, wpnidx);
            } else {
              wpnidx = GetAutoSelectPrimaryWpnIdx(slot_idx + 1);
              SetAutoSelectPrimaryWpnIdx(slot_idx, wpnidx);
            }
            slot_idx++;
          }
          update_buttons = true;
        } else if (slot < m_switch_slot) {
          while (slot_idx > slot) {
            if (is_secondary) {
              wpnidx = GetAutoSelectSecondaryWpnIdx(slot_idx - 1);
              SetAutoSelectSecondaryWpnIdx(slot_idx, wpnidx);
            } else {
              wpnidx = GetAutoSelectPrimaryWpnIdx(slot_idx - 1);
              SetAutoSelectPrimaryWpnIdx(slot_idx, wpnidx);
            }
            slot_idx--;
          }
          update_buttons = true;
        }
        if (is_secondary) {
          SetAutoSelectSecondaryWpnIdx(slot, new_wpnidx);
        } else {
          SetAutoSelectPrimaryWpnIdx(slot, new_wpnidx);
        }
        m_selection_status = -1;
        m_switch_slot = -1;
        if (m_weapon_choose.IsCreated()) {
          m_weapon_choose.Destroy();
        }
      }
    }
  }
  // if above actions modified buttons, refresh em.
  if (update_buttons) {
    wpnsel_cfg_screen::unrealize();
    wpnsel_cfg_screen::realize();
  }
}
void wpnsel_cfg_screen::realize() {
  int i;
  // make sure and reset these here.
  m_selection_status = -1;
  m_switch_slot = -1;

  m_reset_btn.Create(m_menu, UID_RESETDEFAULTS, TXT_RESETTODEFAULT, KEYCFG_EXTRAS_X + m_sheet->X(),
                     KEYCFG_EXTRAS_Y + m_sheet->Y(), NEWUI_BTNF_LONG);
  UITextItem itemPrimaryTitle{MONITOR9_NEWUI_FONT, TXT_PRIMARY};
  m_primary_title.Create(m_menu, &itemPrimaryTitle, WPNSEL_PRIMARY_X, WPNSEL_PRIMARY_Y - 28);
  UITextItem itemSecondaryTitle{MONITOR9_NEWUI_FONT, TXT_SECONDARY};
  m_secondary_title.Create(m_menu, &itemSecondaryTitle, WPNSEL_SECONDARY_X, WPNSEL_SECONDARY_Y - 28);
  UITextItem itemLowPriorityTitle{MONITOR9_NEWUI_FONT, TXT_LOWPRIORITY};
  m_primary_low.Create(m_menu, &itemLowPriorityTitle, WPNSEL_PRIMARY_X, WPNSEL_SECONDARY_Y - 11);
  m_secondary_low.Create(m_menu, &itemLowPriorityTitle, WPNSEL_SECONDARY_X, WPNSEL_SECONDARY_Y - 11);
  for (i = 0; i < MAX_PRIMARY_WEAPONS; i++) {
    int wpnidx;
    char str[64];
    wpnidx = GetAutoSelectPrimaryWpnIdx(i);
    if (wpnidx != WPNSEL_INVALID) {
      if (wpnidx & WPNSEL_SKIP) {
        wpnidx &= (~WPNSEL_SKIP);
        snprintf(str, sizeof(str), TXT_WPNSELBTN, TXT(Static_weapon_names_msg[wpnidx]));
      } else {
        snprintf(str, sizeof(str), "%s", TXT(Static_weapon_names_msg[wpnidx]));
      }
      m_primary_disables[i].Create(m_menu, UID_PRIMARY_DIS + i, "X", WPNSEL_PRIMARY_X, WPNSEL_PRIMARY_Y + i * 12);
      m_primary_buttons[i].Create(m_menu, UID_PRIMARY_WPN + i, str, WPNSEL_PRIMARY_X + 28, WPNSEL_PRIMARY_Y + i * 12,
                                  NEWUI_BTNF_LONG);
    }
    wpnidx = GetAutoSelectSecondaryWpnIdx(i);
    if (wpnidx != WPNSEL_INVALID) {
      if (wpnidx & WPNSEL_SKIP) {
        wpnidx &= (~WPNSEL_SKIP);
        snprintf(str, sizeof(str), TXT_WPNSELBTN, TXT(Static_weapon_names_msg[wpnidx]));
      } else {
        snprintf(str, sizeof(str), "%s", TXT(Static_weapon_names_msg[wpnidx]));
      }
      m_secondary_disables[i].Create(m_menu, UID_SECONDARY_DIS + i, "X", WPNSEL_SECONDARY_X,
                                     WPNSEL_SECONDARY_Y + i * 12);
      m_secondary_buttons[i].Create(m_menu, UID_SECONDARY_WPN + i, str, WPNSEL_SECONDARY_X + 28,
                                    WPNSEL_SECONDARY_Y + i * 12, NEWUI_BTNF_LONG);
    }
  }
  UITextItem itemHighPriority{MONITOR9_NEWUI_FONT, TXT_HIGHPRIORITY};
  m_primary_high.Create(m_menu, &itemHighPriority, WPNSEL_PRIMARY_X, WPNSEL_PRIMARY_Y + i * 12 + 2);
  m_secondary_high.Create(m_menu, &itemHighPriority, WPNSEL_SECONDARY_X, WPNSEL_SECONDARY_Y + i * 12 + 2);
  // add accelerator keys
  m_menu->AddAcceleratorKey(KEY_CTRLED + KEY_C, UID_CLEAR_SLOT);
}
void wpnsel_cfg_screen::unrealize() {
  int i;
  m_menu->ResetAcceleratorKey();
  if (m_weapon_choose.IsCreated()) {
    m_weapon_choose.Destroy();
  }
  for (i = 0; i < MAX_PRIMARY_WEAPONS; i++) {
    m_primary_buttons[i].Destroy();
    m_primary_disables[i].Destroy();
    m_secondary_buttons[i].Destroy();
    m_secondary_disables[i].Destroy();
  }
  m_secondary_high.Destroy();
  m_primary_high.Destroy();

  m_secondary_low.Destroy();
  m_primary_low.Destroy();
  m_secondary_title.Destroy();
  m_primary_title.Destroy();

  m_reset_btn.Destroy();
}
//////////////////////////////////////////////////////////////////////////////
// this will take out any repeats of element and slot in function id.
void ctl_cfg_set_and_verify_changes(int16_t fnid, ct_type elem_type, uint8_t ctrl, uint8_t elem, int8_t slot) {
  ct_type ctype_fn[CTLBINDS_PER_FUNC];
  uint8_t cfgflags_fn[CTLBINDS_PER_FUNC];
  ct_config_data ccfgdata_fn;
  t_cfg_element *fn_list;
  tCfgDataParts cfgparts;
  int i, n_fn;
  if (fnid == -1) {
    Int3(); // get samir
    return;
  }
  ASSERT(slot < N_CFGELEM_SLOTS && slot >= 0);
  if (ctrl == NULL_CONTROLLER) {
    return;
  }
  // if element is repeated anywhere in function list other than 'fnid'[slot] of elem_type, then remove that
  // binding.
  if (elem_type == ctNone) {
    Int3();
    return;
  } else if (elem_type == ctKey) {
    n_fn = N_KEY_CFG_FN;
    fn_list = Cfg_key_elements;
  } else {
    n_fn = N_JOY_CFG_FN;
    fn_list = Cfg_joy_elements;
  }
  for (i = 0; i < n_fn; i++) {
    // get current function.  if element in any slot matches elem_type, and elem, then remove it.
    bool match_found = false;
    Controller->get_controller_function(fn_list[i].fn_id, ctype_fn, &ccfgdata_fn, cfgflags_fn);

    parse_config_data(&cfgparts, ctype_fn[0], ctype_fn[1], ccfgdata_fn);
    if (elem_type == ctype_fn[0] && elem == cfgparts.bind_0 && cfgparts.ctrl_0 == ctrl) {
      // match found! clear this part out.
      cfgparts.bind_0 = NULL_BINDING;
      cfgparts.ctrl_0 = NULL_CONTROLLER;
      match_found = true;
    }
    if (elem_type == ctype_fn[1] && elem == cfgparts.bind_1 && cfgparts.ctrl_1 == ctrl) {
      // match found! clear this part out.
      cfgparts.bind_1 = NULL_BINDING;
      cfgparts.ctrl_1 = NULL_CONTROLLER;
      match_found = true;
    }
    if (match_found) {
      // this will effectively clear any matches found.
      ccfgdata_fn = unify_config_data(&cfgparts);
      Controller->set_controller_function(fn_list[i].fn_id, ctype_fn, ccfgdata_fn, cfgflags_fn);
    }
  }
  Controller->get_controller_function(fnid, ctype_fn, &ccfgdata_fn, cfgflags_fn);

  parse_config_data(&cfgparts, ctype_fn[0], ctype_fn[1], ccfgdata_fn);

  ctype_fn[slot] = elem_type;
  cfgflags_fn[slot] = 0;
  if (slot == 1) {
    cfgparts.bind_1 = elem;
    cfgparts.ctrl_1 = ctrl;
  } else {
    cfgparts.bind_0 = elem;
    cfgparts.ctrl_0 = ctrl;
  }
  ccfgdata_fn = unify_config_data(&cfgparts);
  Controller->set_controller_function(fnid, ctype_fn, ccfgdata_fn, cfgflags_fn);
}
// used as a help/options dialog for each controller config element
void ctl_cfg_element_options_dialog(int16_t fnid) {
  newuiTiledWindow wnd;
  newuiSheet *sheet;
  int *inv_binding[CTLBINDS_PER_FUNC];
  bool *clear_binding[CTLBINDS_PER_FUNC];
  ct_type ctype_fn[CTLBINDS_PER_FUNC];
  uint8_t cfgflags_fn[CTLBINDS_PER_FUNC];
  ct_config_data ccfgdata_fn;

  tCfgDataParts cfgparts;
  int res, y;
  char str[64];

  if (fnid == -1) {
    Int3(); // get samir
    return;
  }
  // determine which configuration pipe to go down
  Controller->get_controller_function(fnid, ctype_fn, &ccfgdata_fn, cfgflags_fn);
  parse_config_data(&cfgparts, ctype_fn[0], ctype_fn[1], ccfgdata_fn);
  switch (ctype_fn[0]) {
  case ctKey:
    strcpy(str, TXT_CFGHELP_KEYB);
    break;
  case ctAxis:
  case ctMouseAxis:
    strcpy(str, TXT_CFGHELP_JOY);
    break;
  case ctButton:
  case ctMouseButton:
  case ctPOV:
  case ctPOV2:
  case ctPOV3:
  case ctPOV4:
    strcpy(str, TXT_CFGHELP_BTNS);
    break;
  default:
    str[0] = 0;
  }
  // open a small window
  wnd.Create(NULL, 0, 0, 320, 192);
  sheet = wnd.GetSheet();
  // the standard ok and cancel buttons
  sheet->NewGroup(NULL, 116, 110, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_OK, UID_OK);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);
  sheet->NewGroup(NULL, 0, 0);
  sheet->AddText(TXT_CFGHELP_TEXT);
  sheet->AddText(str);
  y = 40;
  // check if there's a binding, if so, then check if we should put up invert axis option.
  clear_binding[0] = NULL;
  inv_binding[0] = NULL;
  if (cfgparts.ctrl_0 != NULL_CONTROLLER) {
    snprintf(str, sizeof(str), TXT_CFG_BIND_1, cfg_binding_text(ctype_fn[0], cfgparts.ctrl_0, cfgparts.bind_0));
    sheet->NewGroup(str, 0, y, NEWUI_ALIGN_HORIZ);
    clear_binding[0] = sheet->AddCheckBox(TXT_CFG_CLEAR);
    if (ctype_fn[0] == ctAxis || ctype_fn[0] == ctMouseAxis) {
      sheet->AddText(TXT_CFG_INVERT);
      inv_binding[0] = sheet->AddFirstRadioButton(TXT_NO);
      sheet->AddRadioButton(TXT_YES);
      *inv_binding[0] = CHECK_FLAG(cfgflags_fn[0], CTFNF_INVERT) ? 1 : 0;
    }
    y += 30;
  }
  // check if there's a binding, if so, then check if we should put up invert axis option.
  clear_binding[1] = NULL;
  inv_binding[1] = NULL;
  if (cfgparts.ctrl_1 != NULL_CONTROLLER) {
    snprintf(str, sizeof(str), TXT_CFG_BIND_2, cfg_binding_text(ctype_fn[1], cfgparts.ctrl_1, cfgparts.bind_1));
    sheet->NewGroup(str, 0, y, NEWUI_ALIGN_HORIZ);
    clear_binding[1] = sheet->AddCheckBox(TXT_CFG_CLEAR);
    if (ctype_fn[1] == ctAxis || ctype_fn[1] == ctMouseAxis) {
      sheet->AddText(TXT_CFG_INVERT);
      inv_binding[1] = sheet->AddFirstRadioButton(TXT_NO);
      sheet->AddRadioButton(TXT_YES);
      *inv_binding[1] = CHECK_FLAG(cfgflags_fn[1], CTFNF_INVERT) ? 1 : 0;
    }
    y += 30;
  }
  wnd.Open();
  do {
    res = wnd.DoUI();
    if (res == NEWUIRES_FORCEQUIT) {
      break;
    }
  } while (res != UID_OK && res != UID_CANCEL);
  if (res == UID_OK) {
    if (clear_binding[0] && (*clear_binding[0])) {
      cfgparts.bind_0 = NULL_BINDING;
      cfgparts.ctrl_0 = NULL_CONTROLLER;
    }
    if (clear_binding[1] && (*clear_binding[1])) {
      cfgparts.bind_1 = NULL_BINDING;
      cfgparts.ctrl_1 = NULL_CONTROLLER;
    }
    if (inv_binding[0]) {
      cfgflags_fn[0] = (*inv_binding[0]) ? (cfgflags_fn[0] | CTFNF_INVERT) : (cfgflags_fn[0] & (~CTFNF_INVERT));
    }
    if (inv_binding[1]) {
      cfgflags_fn[1] = (*inv_binding[1]) ? (cfgflags_fn[1] | CTFNF_INVERT) : (cfgflags_fn[1] & (~CTFNF_INVERT));
    }

    ccfgdata_fn = unify_config_data(&cfgparts);
    Controller->set_controller_function(fnid, ctype_fn, ccfgdata_fn, cfgflags_fn);
  }
  wnd.Close();
  wnd.Destroy();
}
// used in weapon selection: returns new slot.
int weapon_select_dialog(int wpn, bool is_secondary) {
  newuiTiledWindow wnd;
  newuiListBox *lbox;
  newuiSheet *sheet;
  int res, i;
  uint16_t retval;
  wpn &= (~WPNSEL_SKIP);
  wnd.Create(NULL, 0, 0, 320, 288);
  sheet = wnd.GetSheet();
  sheet->NewGroup(NULL, 116, 210, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_OK, UID_OK);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);
  sheet->NewGroup(NULL, 0, 0);
  sheet->AddText(TXT_WPNCFGHELP3);
  sheet->AddText(TXT(Static_weapon_names_msg[wpn]));
  sheet->NewGroup(NULL, 0, 40);
  lbox = sheet->AddListBox(192, 160, UID_WPNLIST, UILB_NOSORT);
  // add primaries or secondaries.
  for (i = 0; i < 10; i++) {
    int wpnidx;
    char str[64];
    wpnidx = is_secondary ? GetAutoSelectSecondaryWpnIdx(i) : GetAutoSelectPrimaryWpnIdx(i);
    if (wpnidx != WPNSEL_INVALID) {
      if (wpnidx & WPNSEL_SKIP) {
        wpnidx &= (~WPNSEL_SKIP);
        snprintf(str, sizeof(str), TXT_WPNSELBTN, TXT(Static_weapon_names_msg[wpnidx]));
      } else {
        snprintf(str, sizeof(str), "%s", TXT(Static_weapon_names_msg[wpnidx]));
      }
      lbox->AddItem(str);
    } else {
      lbox->AddItem("ERR-WPN");
    }
  }
  wnd.Open();
  res = wnd.DoUI();
  wnd.Close();
  switch (res) {
  case UID_WPNLIST:
  case UID_OK:
    retval = lbox->GetCurrentIndex();
    break;
  default:
    retval = -1;
  }
  wnd.Destroy();

  return retval;
}
void joystick_calibration() {
}
void joystick_settings_dialog() {
  newuiTiledWindow wnd;
  newuiSheet *sheet;
  int res, i, y;
  int16_t curpos;
  tSliderSettings slider_set;
  char axis_str[N_JOY_AXIS] = {'X', 'Y', 'Z', 'R', 'U', 'V'};
  int16_t *joy_sens[N_JOY_AXIS];
  int16_t *mse_sens[N_MOUSE_AXIS];
  int16_t *ff_gain = NULL;
  bool *ff_enabled = NULL;
  bool *ff_auto_center = NULL;
  bool ff_auto_center_support = false;
  bool ff_found = false;
  bool *joy_enabled;
  bool *mse_enabled;
  int *msectl;

  wnd.Create(TXT_JOYMOUSESETTINGS, 0, 0, 480, 384);
  sheet = wnd.GetSheet();
  // standard ui
  sheet->NewGroup(NULL, 270, 288, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_OK, UID_OK);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);
  // sensitivity sliders for joystick
  sheet->NewGroup(TXT_SENSITIVITY, 0, 0);
  for (i = 0; i < N_JOY_AXIS; i++) {
    char str[16];
    float val = Controller->get_axis_sensitivity(ctAxis, i + 1);
    slider_set.min_val.f = 0.0f;
    slider_set.max_val.f = JOY_AXIS_SENS_RANGE;
    slider_set.type = SLIDER_UNITS_FLOAT;
    curpos = CALC_SLIDER_POS_FLOAT(val, &slider_set, CFG_AXIS_SENS_RANGE);
    snprintf(str, sizeof(str), TXT_CONTAXIS, axis_str[i]);
    joy_sens[i] = sheet->AddSlider(str, CFG_AXIS_SENS_RANGE, curpos, &slider_set);
  }
  sheet->NewGroup(TXT_MSESENS, 0, 220);

  for (i = 0; i < N_MOUSE_AXIS; i++) {
    char str[16];
    float val = Controller->get_axis_sensitivity(ctMouseAxis, i + 1);
    slider_set.min_val.f = 0.0f;
    slider_set.max_val.f = MSE_AXIS_SENS_RANGE;
    slider_set.type = SLIDER_UNITS_FLOAT;
    curpos = CALC_SLIDER_POS_FLOAT(val, &slider_set, CFG_AXIS_SENS_RANGE);
    snprintf(str, sizeof(str), TXT_CONTAXIS, axis_str[i]);
    mse_sens[i] = sheet->AddSlider(str, CFG_AXIS_SENS_RANGE, curpos, &slider_set);
  }
  //	joystick and mouse enabled
  y = 0;
  sheet->NewGroup(TXT_CONTROL_TOGGLES, 210, y);
  joy_enabled = sheet->AddLongCheckBox(TXT_JOYENABLED);
  mse_enabled = sheet->AddLongCheckBox(TXT_CFG_MOUSEENABLED);
  *joy_enabled = CHECK_FLAG(Current_pilot.read_controller, READF_JOY) ? true : false;
  *mse_enabled = CHECK_FLAG(Current_pilot.read_controller, READF_MOUSE) ? true : false;
  y += 50;
  sheet->NewGroup(TXT_MOUSECONTROL, 210, y);
  msectl = sheet->AddFirstLongRadioButton(TXT_MOUSEFLIGHTSIM);
  sheet->AddLongRadioButton(TXT_MOUSELOOK);
  *msectl = Current_pilot.mouselook_control ? 1 : 0;
  y += 50;
  sheet->NewGroup(NULL, 210, y);
  sheet->AddLongButton(TXT_CALIBJOYSTICK, UID_JOYCFG);
  // force feedback stuff
  y += 30;
  ddio_ff_GetInfo(&ff_found, NULL);
  if (ff_found) {
    sheet->NewGroup(TXT_TITLE_FORCEFEEDBACK, 210, y);
    ff_enabled = sheet->AddLongCheckBox(TXT_CFG_FFENABLED, ForceIsEnabled());
    ff_auto_center_support = ddio_ffjoy_SupportAutoCenter(kJoy1);
    if (ff_auto_center_support) {
      // force feedback joystick supports autocentering
      // ----------------------------------------------
      ff_auto_center = sheet->AddLongCheckBox(TXT_CFG_FFAUTOCENTER, ForceIsAutoCenter());
    }
    curpos = (int16_t)(ForceGetGain() * 50.0f);
    slider_set.type = SLIDER_UNITS_PERCENT;
    ff_gain = sheet->AddSlider(TXT_CFG_FORCEGAIN, 50, curpos, &slider_set);
  }
  wnd.Open();
  do {
    res = wnd.DoUI();
    if (res == NEWUIRES_FORCEQUIT) {
      break;
    }
    if (res == UID_JOYCFG) {
      joystick_calibration();
    }
  } while (res != UID_OK && res != UID_CANCEL);
  if (res == UID_OK) {
    float f_temp;

    Current_pilot.read_controller = (*joy_enabled) ? READF_JOY : 0;
    for (i = 0; i < N_JOY_AXIS; i++) {
      float val = CALC_SLIDER_FLOAT_VALUE(*joy_sens[i], 0.0f, JOY_AXIS_SENS_RANGE, CFG_AXIS_SENS_RANGE);
      Controller->set_axis_sensitivity(ctAxis, i + 1, val);
    }
    Current_pilot.read_controller |= (*mse_enabled) ? READF_MOUSE : 0;
    for (i = 0; i < N_MOUSE_AXIS; i++) {
      float val = CALC_SLIDER_FLOAT_VALUE(*mse_sens[i], 0.0f, MSE_AXIS_SENS_RANGE, CFG_AXIS_SENS_RANGE);
      Controller->set_axis_sensitivity(ctMouseAxis, i + 1, val);
    }
    Current_pilot.mouselook_control = (*msectl) ? true : false;
    // force feedback stuff
    if (ff_enabled) {
      if (*ff_enabled) {
        ForceEnable();
      } else {
        ForceDisable();
      }
    }
    if (ff_auto_center_support) {
      if (*ff_auto_center) {
        ForceEnableAutoCenter();
      } else {
        ForceDisableAutoCenter();
      }
    }
    if (ff_gain) {
      f_temp = (*ff_gain) * 0.5f;
      ForceSetGain(f_temp);
    }
  }
  wnd.Close();
  wnd.Destroy();
}
#define CFG_KEY_RAMP_MAX 1.0f
#define CFG_KEY_RAMP_RANGE 20
void key_settings_dialog() {
  newuiTiledWindow wnd;
  newuiSheet *sheet;
  int res;
  int16_t curpos;
  tSliderSettings slider_set;
  int16_t *key_ramp_speed;
  wnd.Create(TXT_KEYSETTINGS, 0, 0, 384, 256);
  sheet = wnd.GetSheet();
  sheet->NewGroup(NULL, 0, 30);
  slider_set.min_val.f = 0.0f;
  slider_set.max_val.f = CFG_KEY_RAMP_MAX;
  slider_set.type = SLIDER_UNITS_FLOAT;
  curpos = CALC_SLIDER_POS_FLOAT(Key_ramp_speed, &slider_set, CFG_KEY_RAMP_RANGE);
  key_ramp_speed = sheet->AddSlider(TXT_KEYRAMPINGTIME, CFG_KEY_RAMP_RANGE, curpos, &slider_set);
  sheet->NewGroup(NULL, 180, 160, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_OK, UID_OK);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);
  wnd.Open();
  do {
    res = wnd.DoUI();
    if (res == NEWUIRES_FORCEQUIT) {
      break;
    }
  } while (res != UID_OK && res != UID_CANCEL);
  if (res == UID_OK) {
    Key_ramp_speed = CALC_SLIDER_FLOAT_VALUE(*key_ramp_speed, 0.0f, CFG_KEY_RAMP_MAX, CFG_KEY_RAMP_RANGE);
  }
  wnd.Close();
  wnd.Destroy();
}
//////////////////////////////////////////////////////////////////////////////
// configure controller new way
struct t_ctlcfgswitchcb_data {
  joy_cfg_screen *joycfg;
  key_cfg_screen *keycfg;
  wpnsel_cfg_screen *wpncfg;
  cfg_screen *curcfg;
};

// called when we switch menus
void CtlConfigSwitchCB(newuiMenu *menu, int16_t old_option_id, int16_t new_option_id, void *data) {
  t_ctlcfgswitchcb_data *cfgdata = (t_ctlcfgswitchcb_data *)data;
  // performs custom gadget deinitialization and reinitilization
  if (cfgdata->curcfg) {
    cfgdata->curcfg->unrealize();
  }

  switch (new_option_id) {
  case IDV_KCONFIG:
    cfgdata->curcfg = cfgdata->keycfg;
    break;
  case IDV_CCONFIG:
    cfgdata->curcfg = cfgdata->joycfg;
    break;
  case IDV_WPNSEL:
    cfgdata->curcfg = cfgdata->wpncfg;
    break;
  default:
    cfgdata->curcfg = NULL;
  }
  if (cfgdata->curcfg) {
    cfgdata->curcfg->realize();
  }
}
// keep multiplayer going!
void CtlConfigUICB() {
  if (Game_mode & (GM_MULTI)) {
    Skip_render_game_frame = true;
    GameFrame();
    Skip_render_game_frame = false;
  } else if (GetFunctionMode() == GAME_MODE) {
    extern void GameProcessMusic();
    float saved_frame_time = Frametime;
    Frametime = UIFrameTime;
    Sound_system.BeginSoundFrame(true);
    GameProcessMusic();
    Sound_system.EndSoundFrame();
    Frametime = saved_frame_time;
  }
}
// the main controller config menu loop
void CtlConfig(int mode) {
  newuiLargeMenu menu;
  joy_cfg_screen joycfg;
  key_cfg_screen keycfg;
  wpnsel_cfg_screen wpncfg;
  t_ctlcfgswitchcb_data cfg_cb_data;
  int res;
  void (*old_callback)() = GetUICallback();
  int old_mode = GetScreenMode();
  // must switch to standard resolution for large window
  SetScreenMode(SM_MENU);
  LoadControlConfig();
  // open menu
  menu.Create();
  menu.Open();
  joycfg.setup(&menu);
  keycfg.setup(&menu);
  wpncfg.setup(&menu);
  cfg_cb_data.joycfg = &joycfg;
  cfg_cb_data.keycfg = &keycfg;
  cfg_cb_data.wpncfg = &wpncfg;
  cfg_cb_data.curcfg = NULL;
  menu.AddSimpleOption(UID_CANCEL, TXT_GEN_EXIT);
  menu.SetCurrentOption((mode == CTLCONFIG_WPNSEL)       ? IDV_WPNSEL
                        : (mode == CTLCONFIG_CONTROLLER) ? IDV_CCONFIG
                                                         : IDV_KCONFIG);
  menu.SetOnOptionSwitchCB(CtlConfigSwitchCB, (void *)&cfg_cb_data);

  //	if(mode==CTLCONFIG_CONTROLLER) {
  //		inSprocket_Configure();
  //	}
  // make sure game is running!
  SetUICallback(CtlConfigUICB);
  // run menu
  do {
    res = menu.DoUI();
    // immediate checking of any option ids.
    if (res == UID_CANCEL || res == NEWUIRES_FORCEQUIT) {
      break; // next pass will quit
    }
    //		if(res == IDV_CCONFIG) {
    //			inSprocket_Configure();
    //		}
    switch (menu.GetCurrentOption()) {
    case IDV_KCONFIG:
      keycfg.process(res);
      break;
    case IDV_CCONFIG:
      joycfg.process(res);
      break;
    case IDV_WPNSEL:
      wpncfg.process(res);
      break;
    };
  } while (1);
  // write them out and close.
  wpncfg.finish();
  keycfg.finish();
  joycfg.finish();
  SaveControlConfig(); // write out config to pilot when destroying window
  PltWriteFile(&Current_pilot);
  menu.Close();
  menu.Destroy();
  SetScreenMode(old_mode);
  SetUICallback(old_callback);
  Skip_render_game_frame = false;
}
int CtlFindBinding(int controlid, bool keyboard) {
  int i = 0;

  if (keyboard) {
    for (i = 0; i < N_KEY_CFG_FN; i++) {
      if (Cfg_key_elements[i].fn_id == controlid)
        return i;
    }
  } else {
    for (i = 0; i < N_JOY_CFG_FN; i++) {
      if (Cfg_joy_elements[i].fn_id == controlid)
        return i;
    }
  }
  return -1;
}
