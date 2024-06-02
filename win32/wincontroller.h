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

 * $Logfile: /DescentIII/Main/Lib/Win/WinController.h $
 * $Revision: 27 $
 * $Date: 7/26/99 12:00p $
 * $Author: Samir $
 *
 * Win32 controller header.
 *
 * $Log: /DescentIII/Main/Lib/Win/WinController.h $
 *
 * 27    7/26/99 12:00p Samir
 * added code to read config files for different controllers.
 *
 * 26    7/20/99 4:53p Samir
 * added ability to manually set the deadzone for a controller.
 *
 * 25    7/16/99 11:14a Samir
 * multiple hat support and improved direct input support.
 *
 * 24    5/03/99 12:36p Samir
 * poll mouse deltas and button masks not as often, to allow deltas to
 * accumulate. also decreased normalizer for mouse axes'.
 *
 * 23    4/29/99 2:23a Samir
 * moved binding text functions to wincontroller.cpp and new text for
 * multiple joysticks.
 *
 * 22    4/26/99 4:31p Samir
 * get_mouse_raw_values now returns screen coords, not deltas.
 *
 * 21    4/24/99 5:39p Samir
 * mouse control now framerate independant.
 *
 * 20    4/16/99 2:02p Kevin
 * Added mouselook support
 *
 * 19    2/16/99 11:59a Samir
 * added proper constants for controller and binding null values.
 *
 * 18    12/18/98 6:00p Samir
 * added enable_function.
 *
 * 17    10/24/98 2:18p Samir
 * added mouse and joytick raw value retrieval functions.
 *
 * 16    10/21/98 10:36a Samir
 * added code to turn on or off joystick or mouse.
 *
 * 15    10/18/98 7:29p Samir
 * made assign_function public.
 *
 * 14    10/17/98 7:31p Samir
 * added invertible axes
 *
 * 13    9/10/98 12:39p Samir
 * added senstivity issures for controller.
 *
 * 12    6/29/98 6:47p Samir
 * made suspended flag an int.
 *
 * 11    6/18/98 4:48p Samir
 * added changes for multiple configs for joystick controls.
 *
 * 10    2/24/98 11:03a Samir
 * Added flush function to controller system.
 *
 * 9     2/17/98 10:59a Samir
 * Added invalid controller type.
 *
 * 8     2/16/98 3:04p Samir
 * ctAxis instead of ctXAxis, ctYAxis, etc.
 *
 * 7     2/13/98 6:38p Samir
 * Added get and set controller function.
 *
 * 6     12/05/97 12:49p Samir
 * POV timing support
 *
 * 5     12/05/97 10:58a Samir
 * Null zone for joysticks applied here.
 *
 * 4     12/03/97 7:35p Samir
 * Newer joystick library support and some POV.
 *
 * 3     11/05/97 3:46p Samir
 * Use C runtime calls for thread creattion.
 *
 * 2     10/29/97 4:44p Samir
 * Added ctDownCount format.
 *
 * 7     5/12/97 1:20p Samir
 * Preemptive thread for joystick buttons.
 *
 * 6     4/23/97 1:07p Samir
 * Now we can poll for either positonal or evaluator data.
 *
 * 5     4/16/97 1:04p Samir
 * For get packet, allow one to return an alternate format value if that
 * function supports it.
 *
 * 4     4/16/97 12:27p Samir
 * Added mouse support.
 *
 * 3     4/14/97 12:56p Samir
 * Added information for button timings.
 *
 * 2     4/11/97 2:13p Samir
 * Win32 controller interface works for keyboards and DirectInput devices
 * through (not mouse yet).
 *
 * $NoKeywords: $
 */

#ifndef WINCONTROLLER_H
#define WINCONTROLLER_H

#include "controller.h"
#include "joystick.h"

#define NULL_WINCONTROLLER ((int8_t)NULL_CONTROLLER)

const int CTF_POV = 64, // POV control
    CTF_POV2 = 128,     // POV 2
    CTF_POV3 = 256,     // POV 3
    CTF_POV4 = 512;     // POV 4

const unsigned CTF_X_AXIS = (1 << (CT_X_AXIS - 1)), // AXIS constants for ctAxis
    CTF_Y_AXIS = (1 << (CT_Y_AXIS - 1)), CTF_Z_AXIS = (1 << (CT_Z_AXIS - 1)), CTF_R_AXIS = (1 << (CT_R_AXIS - 1)),
               CTF_U_AXIS = (1 << (CT_U_AXIS - 1)), CTF_V_AXIS = (1 << (CT_V_AXIS - 1));

const unsigned CT_MAX_CONTROLLERS = 32, CT_MAX_ELEMENTS = 255, CT_MAX_EXTCTLS = 16, CT_MAX_BUTTONS = 32;

//	rules for adding controllers
//		any nonstandard special controllers should be added to the below list starting at
//		CTID_MOUSE-1 (meaning a value of -3, -4 and so on)

const int CTID_KEYBOARD = -1, // always -1 for keyboards
    CTID_MOUSE = -2,          // always -2 for mice
    CTID_INVALID = -3;        // invalid controller

//	External controls
//		these are standard controllers handled through DDIO interface
//		like joysticks, etc.

const int CTID_EXTCONTROL0 = 0;

class gameWinController : public gameController {
public:
  //	initialization of controller with needs
  gameWinController(int num_funcs, ct_function *funcs, char *remote_adr = NULL);
  virtual ~gameWinController();

  virtual void suspend();
  virtual void resume();

  //	this functions polls the controllers if needed.  some systems may not need to implement
  //	this function.
  virtual void poll();

  //	flushes all controller information
  virtual void flush();

  //	returns the value of a requested controller type.
  virtual ct_config_data get_controller_value(ct_type type_req);

  //	sets the configuration of a function
  virtual void set_controller_function(int id, const ct_type *type, ct_config_data value, const uint8_t *flags);

  //	returns information about a requested function
  virtual void get_controller_function(int id, ct_type *type, ct_config_data *value, uint8_t *flags);

  //	temporarily enables or disables a function
  virtual void enable_function(int id, bool enable);

  virtual bool get_packet(int id, ct_packet *packet, ct_format alt_format = ctNoFormat);

  // gets sensitivity of axis item
  virtual float get_axis_sensitivity(ct_type axis_type, uint8_t axis);

  // sets sensitivity of axis item
  virtual void set_axis_sensitivity(ct_type axis_type, uint8_t axis, float val);

  // assigns an individual function
  virtual int assign_function(ct_function *fn);

  // activates or deactivates mouse and or controller
  virtual void mask_controllers(bool joystick, bool mouse);

  // retrieves binding text for desired function, binding, etc.
  virtual const char *get_binding_text(ct_type type, uint8_t ctrl, uint8_t bind);

  // get raw values for the controllers
  virtual int get_mouse_raw_values(int *x, int *y);
  virtual unsigned get_joy_raw_values(int *x, int *y);

  //	toggles use of deadzone for controllers. ctl can be 0 to ???
  // dead zone is from 0.0 to 0.5
  void set_controller_deadzone(int ctl, float deadzone);

private:
  int m_NumControls;               // number of controllers available
  int m_Suspended;                 // is controller polling suspended?
  bool m_JoyActive, m_MouseActive; // enables or disables mouse, joystick control

  struct t_controller {
    int id;
    uint16_t flags;
    uint16_t buttons;
    unsigned btnmask;
    float normalizer[CT_NUM_AXES];
    float sens[CT_NUM_AXES];
    float sensmod[CT_NUM_AXES];
    float deadzone;
  } m_ControlList[CT_MAX_CONTROLLERS]; // the control list.

  struct ct_element {
    ct_format format;
    int8_t ctl[CTLBINDS_PER_FUNC];
    uint8_t value[CTLBINDS_PER_FUNC];
    ct_type ctype[CTLBINDS_PER_FUNC];
    uint8_t flags[2];
    bool enabled;
  } m_ElementList[CT_MAX_ELEMENTS];

  bool enum_controllers(char *remote_adr);

  //	sets up an elements information structure
  void assign_element(int id, ct_element *elem);

  //	this returns an index into the control list.
  int8_t get_axis_controller(uint8_t axis);

  //	returns controller with specified button
  int8_t get_button_controller(uint8_t btn);

  //	returns the controller with a pov hat
  int8_t get_pov_controller(uint8_t pov);

  //	note controller is index into ControlList.
  float get_axis_value(int8_t controller, uint8_t axis, ct_format format, bool invert = false);

  //	get value of button in  seconds, presses, etc.
  float get_button_value(int8_t controller, ct_format format, uint8_t button);

  //	get value of pov (using JOYPOV values)
  float get_pov_value(int8_t controller, ct_format format, uint8_t pov_number, uint8_t pov);

  //	get keyboard info
  float get_key_value(int key, ct_format format);

  // okay, now search for a '****.ctl' file in the current directory.
  void parse_ctl_file(int devnum, const char *ctlname);

private:
  struct t_msestate {
    int m_deltaX, m_deltaY, m_deltaZ;
    int m_absX, m_absY;
    uint32_t m_buttonMask;
  } m_MseState;

  struct t_extctlstate {
    int x, y, z, r, u, v;
    int pov[JOYPOV_NUM];
    int last_pov[JOYPOV_NUM];
    float povstarts[JOYPOV_NUM][JOYPOV_DIR];
    float povtimes[JOYPOV_NUM][JOYPOV_DIR];
    uint8_t povpresses[JOYPOV_NUM][JOYPOV_DIR];
    unsigned buttons;
    uint8_t btnpresses[CT_MAX_BUTTONS];
    float btnstarts[CT_MAX_BUTTONS];
    float btntimes[CT_MAX_BUTTONS];
  } m_ExtCtlStates[CT_MAX_EXTCTLS];

  //	thread info.
  int64_t m_frame_timer_ms;
  float m_frame_time;

  //	note id is id value from controller in control list.
  void extctl_getpos(int id);
  void extctl_geteval(int id);

  //	this gets timings for mouse buttons
  void mouse_geteval();
};

#endif
