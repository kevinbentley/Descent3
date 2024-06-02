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

 * $Logfile: /DescentIII/Main/wincontroller/WinController.cpp $
 * $Revision: 81 $
 * $Date: 4/19/00 5:36p $
 * $Author: Matt $
 *
 * Win32 controller interface
 *
 * $Log: /DescentIII/Main/wincontroller/WinController.cpp $
 *
 * 81    4/19/00 5:36p Matt
 * Added command-line option to adjust mouse sensitivity
 *
 * 80    10/25/99 3:09p Kevin
 * added -mlooksens
 *
 * 79    10/25/99 9:40a Kevin
 * made mouselook less sensitive
 *
 * 78    9/23/99 12:04p Jeff
 * ttok out framecap for joystick polling (samir)
 *
 * 77    8/19/99 10:41a Samir
 * fixed potentially bad bugs.
 *
 * 76    8/17/99 2:09p Samir
 * fixed U-axis get_controller_value bug.
 *
 * 75    8/11/99 6:06p Samir
 * added flag to determine whether packet contained mouse info.
 *
 * 74    7/30/99 1:06p Samir
 * fixed hat code for direct input and apply sensitivities for calibration
 * of axes.
 *
 * 73    7/26/99 12:00p Samir
 * added code to read config files for different controllers.
 *
 * 72    7/20/99 4:53p Samir
 * added ability to manually set the deadzone for a controller.
 *
 * 71    7/16/99 11:16a Samir
 * poll joystick and mouse axial movement once every 20-30 frames a sec to
 * improve smoothness of motion.
 *
 * 70    6/11/99 1:15a Samir
 * localization issues.
 *
 * 69    5/19/99 12:32p Kevin
 * adjusted mouselook sensitivity
 *
 * 68    5/19/99 12:05p Samir
 * made mouse less sensitive by default again since it was pumped up so
 * high that the sliders didn't make much of a difference (not for
 * mouselook).
 *
 * 67    5/19/99 11:18a Kevin
 * fixed problem with mouselook and guided missiles
 *
 * 66    5/13/99 6:41p Samir
 * made mouse even more 'sensitive'.
 *
 * 65    5/03/99 12:36p Samir
 * poll mouse deltas and button masks not as often, to allow deltas to
 * accumulate. also decreased normalizer for mouse axes'.
 *
 * 64    5/01/99 10:49a Kevin
 * made mouselook obey player control masks (for training mission)
 *
 * 63    4/29/99 3:00p Samir
 * don't specify joystick number for joystick #1.
 *
 * 62    4/29/99 2:23a Samir
 * moved binding text functions to wincontroller.cpp and new text for
 * multiple joysticks.
 *
 * 61    4/26/99 4:31p Samir
 * get_mouse_raw_values now returns screen coords, not deltas.
 *
 * 60    4/24/99 5:39p Samir
 * mouse control now framerate independant.
 *
 * 59    4/21/99 10:58a Samir
 * set sensitivity for all controllers, not just active ones.
 *
 * 58    4/19/99 6:09p Kevin
 * removed annoying mprintf
 *
 * 57    4/17/99 8:25p Samir
 * fixed digital return values for mouse button states.
 *
 * 56    4/16/99 3:17p Kevin
 * More mouselook support
 *
 * 55    4/16/99 2:02p Kevin
 * Added mouselook support
 *
 * 54    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 53    4/01/99 11:26a Samir
 * correctly autodetect mouse buttons.
 *
 * 52    3/30/99 4:08p Matt
 * Fixed compile warning.
 *
 * 51    3/29/99 6:44p Kevin
 * For Samir
 *
 * 50    3/29/99 6:07p Samir
 * don't use z axis for mouse again.
 *
 * 49    3/23/99 9:06p Samir
 * new mouse interface implemented.
 *
 * 48    3/03/99 2:31p Samir
 * don't look for Z-axis for mouse for now. buggy.
 *
 * 47    3/01/99 9:42a Matt
 * Fixed compile warnings
 *
 * 46    3/01/99 12:18a Samir
 * fixed evil bug with z axis mouse range being 0, hence get_axis_value
 * would normalize the z axis with a bogus value, hence,
 * get_controller_value was hosed for mouse axis reading, and
 * configuration was messed up.  Only found in optimized build.
 *
 * 45    2/26/99 2:10a Samir
 * weird thing I did.
 *
 * 44    2/21/99 6:40p Samir
 * mouse control will fake more axes and buttons.
 *
 * 43    2/16/99 11:59a Samir
 * added proper constants for controller and binding null values.
 *
 * 42    1/29/99 2:31p Samir
 * error checking for set_controller_function.
 *
 * 41    12/18/98 6:00p Samir
 * added enable_function.
 *
 * 40    12/17/98 5:59p Samir
 * modified mouse control.
 *
 * 39    12/02/98 12:48p Samir
 * cleaned up get_axis_value.
 *
 * 38    10/24/98 2:18p Samir
 * added mouse and joytick raw value retrieval functions.
 *
 * 37    10/21/98 7:19p Samir
 * fixed idiotic bug in flush.
 *
 * 36    10/21/98 10:36a Samir
 * added code to turn on or off joystick or mouse.
 *
 * 35    10/19/98 1:39p Samir
 * took out mse_x message,.
 *
 * 34    10/19/98 10:48a Samir
 * made mouse control a bit more responsive in some ways.
 *
 * 33    10/19/98 9:54a Samir
 * fixed something, don't know what.
 *
 * 32    10/18/98 7:29p Samir
 * made assign_function public.
 *
 * 31    10/17/98 7:31p Samir
 * added invertible axes
 *
 * 30    9/10/98 12:39p Samir
 * added senstivity issures for controller.
 *
 * 29    7/24/98 3:54p Samir
 * improved mouse handling.
 *
 * 28    6/29/98 6:42p Samir
 * Properly handle controller pausing and resumption.
 *
 * 27    6/18/98 4:48p Samir
 * added changes for multiple configs for joystick controls.
 *
 * 26    6/02/98 4:37p Samir
 * multiple joysticks supported.
 *
 * 25    6/01/98 4:27p Samir
 * pov may return multiple positions.
 *
 * 24    5/15/98 3:13p Samir
 * added 2 key support for controller functions.
 *
 * 23    5/12/98 3:10p Samir
 * correctly ramp up controller axis values.
 *
 * 22    5/01/98 3:52p Samir
 * added digital control for POV hats and joytick buttons.
 *
 * 21    4/08/98 3:43p Samir
 * fixed some button/button capping problems.
 *
 * 20    4/02/98 8:04p Samir
 * took out mprintf
 *
 * 19    4/02/98 7:57p Samir
 * make sure controller is reset to -1 if element is invalid, BUT DON'T
 * reset value.  Only reset value when in assign_function, NOT in
 * assign_element.
 *
 * 18    3/31/98 7:48p Samir
 * probably fixed controller bugs.
 *
 * 17    3/31/98 6:14p Samir
 * better checking when assigning values to elements.
 *
 * 16    3/16/98 3:25p Samir
 * improved proofchecking of controller element validity when getting
 * information.
 *
 * 15    2/24/98 11:03a Samir
 * Added flush function to controller system.
 *
 * 14    2/17/98 10:59a Samir
 * Mark all controllers not used as invalid.
 *
 * 13    2/17/98 10:10a Samir
 * Fixed another logic bug, same function.
 *
 * 12    2/17/98 10:08a Samir
 * Fixed logic bug in get_button_value.
 *
 * 11    2/16/98 9:28p Samir
 * Fixed up some code to retrieve state of buttons, axes, etc.
 *
 * 10    2/16/98 3:04p Samir
 * ctAxis instead of ctXAxis, ctYAxis, etc.
 *
 * 9     2/13/98 6:38p Samir
 * Added get and set controller function.
 *
 * 8     12/10/97 11:16a Samir
 * Joystick button timing should be fixed.
 *
 * 7     12/05/97 12:49p Samir
 * POV timing support
 *
 * 6     12/05/97 10:58a Samir
 * Null zone for joysticks applied here.
 *
 * 5     12/03/97 7:35p Samir
 * Newer joystick library support and some POV.
 *
 * 4     11/05/97 3:46p Samir
 * Use C runtime calls for thread creattion.
 *
 * 3     10/29/97 4:44p Samir
 * Added ctDownCount format.
 *
 * 2     10/17/97 11:37a Samir
 * Changed highest task priority from TIME_CRITICAL to HIGHEST.
 *
 * 10    6/09/97 12:21p Chris
 *
 * 9     5/21/97 3:51p Samir
 * changed ct_need to ct_function
 *
 * 8     5/12/97 1:20p Samir
 * Preemptive thread for joystick buttons.
 *
 * 7     4/23/97 1:07p Samir
 * Now we can poll for either positonal or evaluator data.
 *
 * 6     4/16/97 3:29p Samir
 * Moved timer poll outside button loop
 *
 * 5     4/16/97 1:04p Samir
 * For get packet, allow one to return an alternate format value if that
 * function supports it.
 *
 * 4     4/16/97 12:27p Samir
 * Added mouse support.
 *
 * 3     4/14/97 12:55p Samir
 * Controllers support timing of buttons presses.
 *
 * 2     4/11/97 2:13p Samir
 * Win32 controller interface works for keyboards and DirectInput devices
 * through (not mouse yet).
 *
 * $NoKeywords: $
 */

#include "wincontroller.h"

#include <cmath>

#include "pserror.h"
#include "ddio.h"
#include "joystick.h"
#include "Macros.h"
#include "inffile.h"

// Sorry! This is needed for the semi-hacky mouselook support
#include "descent.h"
#include "player.h"
#include "object.h"
#include "pilot.h"
#include "multi.h"
#include "game.h"
// End of hacky includes

extern float Mouselook_sensitivity;
extern float Mouse_sensitivity;

#define JOY_DEADZONE 0.20f
#define MOUSE_DEADZONE 0.00f

static float WinControllerTimer = 0.0f;
static int64_t g_last_frame_timer_ms = -1;
static float g_accum_frame_time = 0.0f;

//	Functions to create and destroy a game controller object.

gameController *CreateController(int num_needs, ct_function *needs, char *remote_ip) {
  return new gameWinController(num_needs, needs, remote_ip);
}

void DestroyController(gameController *ctl) { delete ctl; }

//	gameWinController subset of gameController class

gameWinController::gameWinController(int num_funcs, ct_function *funcs, char *remote_adr)
    : gameController(num_funcs, funcs) {
  enum_controllers(remote_adr);

  for (int i = 0; i < num_funcs; i++) {
    assign_function(&funcs[i]);
  }

  m_Suspended = 0;
  m_frame_timer_ms = -1;
  m_frame_time = 1.0f;
  g_last_frame_timer_ms = -1;
  g_accum_frame_time = 0.0f;

  gameWinController::flush();
}

gameWinController::~gameWinController() {}

//	DDIO takes care of our keyboard information, so we don't need to check that control (preemptive)
//	DDIO does handle the mouse, but we need to poll this information
//	DDIO does handle to joystick or external controls but we also need to poll this information

#define CONTROLLER_POLLING_TIME 50
#define MOUSE_POLLING_TIME (1.0f / 20.0f)

void gameWinController::poll() {
  int64_t cur_frame_timer_ms;

  if (m_Suspended)
    return;

  cur_frame_timer_ms = timer_GetMSTime();
  if (m_frame_timer_ms == -1) {
    // don't poll this frame.
    m_frame_timer_ms = cur_frame_timer_ms;
    g_last_frame_timer_ms = cur_frame_timer_ms;
    g_accum_frame_time = 0.0f;
    return;
  }

  m_frame_time = (float)((cur_frame_timer_ms - m_frame_timer_ms) / 1000.0);
  m_frame_timer_ms = cur_frame_timer_ms;
  g_accum_frame_time += m_frame_time;

  if (g_accum_frame_time >= MOUSE_POLLING_TIME) {
    g_accum_frame_time = 0.0f;
  }

  for (int ctl = 0; ctl < m_NumControls; ctl++) {
    if (m_ControlList[ctl].id >= CTID_EXTCONTROL0) {
      extctl_getpos(m_ControlList[ctl].id);
    } else if (m_ControlList[ctl].id == CTID_MOUSE) {
      mouse_geteval();
    }
  }
}

void gameWinController::suspend() { m_Suspended = 1; }

void gameWinController::resume() {
  m_Suspended = 0;
  m_frame_timer_ms = -1;
  m_frame_time = 1.0f;
}

//	flushes all controller information
void gameWinController::flush() {
  bool old_mse = m_MouseActive, old_joy = m_JoyActive;

  ddio_KeyFlush();
  ddio_MouseQueueFlush();

  // does real flush
  mask_controllers(false, false);
  mask_controllers(old_joy, old_mse);
}

bool gameWinController::get_packet(int id, ct_packet *packet, ct_format alt_format) {
  float val = (float)0.0;
  int i;

  ASSERT(id < CT_MAX_ELEMENTS);

  packet->format = (alt_format != ctNoFormat) ? alt_format : m_ElementList[id].format;
  alt_format = packet->format;

  WinControllerTimer = timer_GetTime();
  packet->flags = 0;

  if (!m_ElementList[id].enabled) {
    goto skip_packet_read;
  }

  //	check if the element's controller is valid.

  for (i = 0; i < CTLBINDS_PER_FUNC; i++) {
    uint8_t value = m_ElementList[id].value[i];
    int8_t controller = m_ElementList[id].ctl[i];

    if (controller == -1 || m_ControlList[controller].id == CTID_INVALID) {
      continue;
    }
    switch (m_ElementList[id].ctype[i]) {
    case ctKey:
      if (value) {
        val = get_key_value(value, alt_format);
        if (KEY_STATE(value))
          packet->flags |= CTPK_ELEMENTACTIVE;
      }
      break;

    case ctMouseAxis:
      packet->flags |= CTPK_MOUSE;
    case ctAxis:
      val = get_axis_value(controller, value, alt_format, (m_ElementList[id].flags[i] & CTFNF_INVERT) ? true : false);
      if (m_ElementList[id].flags[i] & CTFNF_INVERT) {
        if (alt_format == ctDigital) {
          val = (val == 0.0f) ? 1.0f : 0.0f;
        } else if (alt_format == ctAnalog) {
          val = -val;
        }
      }
      break;

    case ctMouseButton:
      packet->flags |= CTPK_MOUSE;
    case ctButton:
      val = get_button_value(controller, alt_format, value);
      break;

    case ctPOV:
      val = get_pov_value(controller, alt_format, 0, value);
      break;
    case ctPOV2:
    case ctPOV3:
    case ctPOV4:
      val = get_pov_value(controller, alt_format, (m_ElementList[id].ctype[i] - ctPOV2) + 1, value);
      break;

    default:
      Int3();
      val = 0.0f;
    }

    if (val)
      break;
  }

skip_packet_read:
  if (val)
    packet->flags |= CTPK_ELEMENTACTIVE;

  packet->value = val;

  return true;
}

//	returns the value of a requested controller type.
ct_config_data gameWinController::get_controller_value(ct_type type_req) {
  //	will return the current value of a requested control type.
  ct_config_data val = MAKE_CONFIG_DATA(INVALID_CONTROLLER_INFO, NULL_BINDING);
  int i, j;

  switch (type_req) {
    int pov_n;

  case ctKey:
    val = makeword(0, ddio_KeyInKey());
    break;

  case ctButton:
    for (i = 2; i < m_NumControls; i++) {
      for (j = 0; j < m_ControlList[i].buttons; j++) {
        if (m_ExtCtlStates[m_ControlList[i].id].btnpresses[j] &&
            !(m_ExtCtlStates[m_ControlList[i].id].buttons & (1 << j))) {
          val = MAKE_CONFIG_DATA(CONTROLLER_CTL_INFO(i, NULL_CONTROLLER), CONTROLLER_CTL_VALUE(j + 1, NULL_BINDING));
          return val;
        }
      }
    }
    break;

  case ctMouseButton:
    for (j = 0; j < CT_MAX_BUTTONS; j++) {
      if (ddio_MouseBtnUpCount(j)) {
        //	mprintf(0, "MseBtn %d down\n", j);
        val = MAKE_CONFIG_DATA(CONTROLLER_CTL_INFO(1, NULL_CONTROLLER), CONTROLLER_CTL_VALUE(j + 1, NULL_BINDING));
        return val;
      }
    }
    break;

  case ctAxis:
    for (i = 2; i < m_NumControls; i++) {
      float pos;
      float limit;
      unsigned ctl = CONTROLLER_CTL_INFO(i, NULL_CONTROLLER);

      if (m_ControlList[i].flags & CTF_V_AXIS) {
        limit = (m_ControlList[i].sens[CT_V_AXIS - 1] > 1.5f)   ? 0.95f
                : (m_ControlList[i].sens[CT_V_AXIS - 1] > 1.0f) ? 0.80f
                                                                : (m_ControlList[i].sens[CT_V_AXIS - 1] / 2);
        pos = get_axis_value(i, CT_V_AXIS, ctAnalog);
        mprintf(0, "pos=%.2f\n", pos);
        if (fabs(pos) > limit)
          val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_V_AXIS, NULL_BINDING));
      }
      if (m_ControlList[i].flags & CTF_U_AXIS) {
        limit = (m_ControlList[i].sens[CT_U_AXIS - 1] > 1.5f)   ? 0.95f
                : (m_ControlList[i].sens[CT_U_AXIS - 1] > 1.0f) ? 0.80f
                                                                : (m_ControlList[i].sens[CT_U_AXIS - 1] / 2);
        pos = get_axis_value(i, CT_U_AXIS, ctAnalog);
        if (fabs(pos) > limit)
          val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_U_AXIS, NULL_BINDING));
      }
      if (m_ControlList[i].flags & CTF_R_AXIS) {
        limit = (m_ControlList[i].sens[CT_R_AXIS - 1] > 1.5f)   ? 0.95f
                : (m_ControlList[i].sens[CT_R_AXIS - 1] > 1.0f) ? 0.80f
                                                                : (m_ControlList[i].sens[CT_R_AXIS - 1] / 2);
        pos = get_axis_value(i, CT_R_AXIS, ctAnalog);
        if (fabs(pos) > limit)
          val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_R_AXIS, NULL_BINDING));
      }
      if (m_ControlList[i].flags & CTF_Z_AXIS) {
        limit = (m_ControlList[i].sens[CT_Z_AXIS - 1] > 1.5f)   ? 0.95f
                : (m_ControlList[i].sens[CT_Z_AXIS - 1] > 1.0f) ? 0.80f
                                                                : (m_ControlList[i].sens[CT_Z_AXIS - 1] / 2);
        pos = get_axis_value(i, CT_Z_AXIS, ctAnalog);
        if (fabs(pos) > limit)
          val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_Z_AXIS, NULL_BINDING));
      }
      if (m_ControlList[i].flags & CTF_Y_AXIS) {
        limit = (m_ControlList[i].sens[CT_Y_AXIS - 1] > 1.5f)   ? 0.95f
                : (m_ControlList[i].sens[CT_Y_AXIS - 1] > 1.0f) ? 0.80f
                                                                : (m_ControlList[i].sens[CT_Y_AXIS - 1] / 2);
        pos = get_axis_value(i, CT_Y_AXIS, ctAnalog);
        if (fabs(pos) > limit)
          val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_Y_AXIS, NULL_BINDING));
      }
      if (m_ControlList[i].flags & CTF_X_AXIS) {
        limit = (m_ControlList[i].sens[CT_X_AXIS - 1] > 1.5f)   ? 0.95f
                : (m_ControlList[i].sens[CT_X_AXIS - 1] > 1.0f) ? 0.80f
                                                                : (m_ControlList[i].sens[CT_X_AXIS - 1] / 2);
        pos = get_axis_value(i, CT_X_AXIS, ctAnalog);
        if (fabs(pos) > limit)
          val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_X_AXIS, NULL_BINDING));
      }
    }
    break;

  case ctMouseAxis: {
    float pos = 0.0f;
    unsigned ctl = CONTROLLER_CTL_INFO(1, NULL_CONTROLLER), i = 1;

    ASSERT(m_ControlList[i].id == CTID_MOUSE);

    if (m_ControlList[i].flags & CTF_V_AXIS) {
      pos = get_axis_value(i, CT_V_AXIS, ctAnalog);
      if (fabs(pos) >= 0.50f)
        val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_V_AXIS, NULL_BINDING));
    }
    if (m_ControlList[i].flags & CTF_U_AXIS) {
      pos = get_axis_value(i, CT_U_AXIS, ctAnalog);
      if (fabs(pos) >= 0.50f)
        val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_U_AXIS, NULL_BINDING));
    }
    if (m_ControlList[i].flags & CTF_R_AXIS) {
      pos = get_axis_value(i, CT_R_AXIS, ctAnalog);
      if (fabs(pos) >= 0.50f)
        val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_R_AXIS, NULL_BINDING));
    }
    if (m_ControlList[i].flags & CTF_Z_AXIS) {
      pos = get_axis_value(i, CT_Z_AXIS, ctAnalog);
      if (fabs(pos) >= 0.90f)
        val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_Z_AXIS, NULL_BINDING));
    }
    if (m_ControlList[i].flags & CTF_Y_AXIS) {
      pos = get_axis_value(i, CT_Y_AXIS, ctAnalog);
      //	mprintf(0, "y=%.2f   ", pos);
      if (fabs(pos) >= 0.90f)
        val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_Y_AXIS, NULL_BINDING));
    }
    if (m_ControlList[i].flags & CTF_X_AXIS) {
      pos = get_axis_value(i, CT_X_AXIS, ctAnalog);
      //	mprintf(0, "x=%.2f\n", pos);
      if (fabs(pos) >= 0.90f)
        val = MAKE_CONFIG_DATA(ctl, CONTROLLER_CTL_VALUE(CT_X_AXIS, NULL_BINDING));
    }
  } break;

  case ctPOV:
  case ctPOV2:
  case ctPOV3:
  case ctPOV4:
    if (type_req == ctPOV) {
      pov_n = 0;
    } else {
      pov_n = (type_req - ctPOV2) + 1;
    }
    for (i = 2; i < m_NumControls; i++) {
      float pos;
      int ctl = CONTROLLER_CTL_INFO(i, -1);

      if (m_ControlList[i].flags & (CTF_POV << pov_n)) {
        pos = get_pov_value(i, ctDigital, pov_n, JOYPOV_RIGHT);
        if (pos)
          val = makeword(ctl, CONTROLLER_CTL_VALUE(JOYPOV_RIGHT, 0));
      }
      if (m_ControlList[i].flags & (CTF_POV << pov_n)) {
        pos = get_pov_value(i, ctDigital, pov_n, JOYPOV_LEFT);
        if (pos)
          val = makeword(ctl, CONTROLLER_CTL_VALUE(JOYPOV_LEFT, 0));
      }
      if (m_ControlList[i].flags & (CTF_POV << pov_n)) {
        pos = get_pov_value(i, ctDigital, pov_n, JOYPOV_DOWN);
        if (pos)
          val = makeword(ctl, CONTROLLER_CTL_VALUE(JOYPOV_DOWN, 0));
      }
      if (m_ControlList[i].flags & (CTF_POV << pov_n)) {
        pos = get_pov_value(i, ctDigital, pov_n, JOYPOV_UP);
        if (pos)
          val = makeword(ctl, CONTROLLER_CTL_VALUE(JOYPOV_UP, 0));
      }
    }
    break;
  }

  return val;
}

//	temporarily enables or disables a function
void gameWinController::enable_function(int id, bool enable) { m_ElementList[id].enabled = enable; }

//	returns information about a requested function
void gameWinController::get_controller_function(int id, ct_type *type, ct_config_data *value, uint8_t *flags) {
  type[0] = m_ElementList[id].ctype[0];
  type[1] = m_ElementList[id].ctype[1];
  *value = makeword(CONTROLLER_CTL_INFO(m_ElementList[id].ctl[0], m_ElementList[id].ctl[1]),
                    CONTROLLER_CTL_VALUE(m_ElementList[id].value[0], m_ElementList[id].value[1]));
  flags[0] = m_ElementList[id].flags[0];
  flags[1] = m_ElementList[id].flags[1];
}

//	sets the configuration of a function
void gameWinController::set_controller_function(int id, const ct_type *type, ct_config_data value, const uint8_t *flags) {
  ct_element elem;

  if (id >= CT_MAX_ELEMENTS)
    return;

  // auto assign keyboard controller if type is key.
  if (type[0] == ctKey)
    elem.ctl[0] = CONTROLLER_CTL1_INFO(0);
  else
    elem.ctl[0] = CONTROLLER_CTL1_INFO(CONTROLLER_INFO(value));

  if (type[1] == ctKey)
    elem.ctl[1] = CONTROLLER_CTL2_INFO(0);
  else
    elem.ctl[1] = CONTROLLER_CTL2_INFO(CONTROLLER_INFO(value));

  elem.ctype[0] = type[0];
  elem.ctype[1] = type[1];
  elem.format = m_ElementList[id].format;
  elem.value[0] = CONTROLLER_CTL1_VALUE(CONTROLLER_VALUE(value));
  elem.value[1] = CONTROLLER_CTL2_VALUE(CONTROLLER_VALUE(value));
  elem.flags[0] = flags[0];
  elem.flags[1] = flags[1];
  elem.enabled = m_ElementList[id].enabled;

  //	if controller doesn't exist, set it to invalid.
  if (elem.ctl[0] > CT_MAX_CONTROLLERS)
    elem.ctl[0] = NULL_WINCONTROLLER;
  if (elem.ctl[1] >= CT_MAX_CONTROLLERS)
    elem.ctl[1] = NULL_WINCONTROLLER;

  assign_element(id, &elem);
}

// activates or deactivates mouse and or controller
void gameWinController::mask_controllers(bool joystick, bool mouse) {
  int i, j;

  m_JoyActive = joystick;
  m_MouseActive = mouse;

  if (!m_MouseActive) {
    m_MseState.m_deltaX = 0;
    m_MseState.m_deltaY = 0;
    m_MseState.m_deltaZ = 0;
    m_MseState.m_absX = 0;
    m_MseState.m_absY = 0;
    m_MseState.m_buttonMask = 0;
  }

  if (!m_JoyActive) {
    for (int ctl = 0; ctl < m_NumControls; ctl++) {
      if (m_ControlList[ctl].id >= CTID_EXTCONTROL0) {
        //	handle buttons
        int dev = m_ControlList[ctl].id;
        m_ExtCtlStates[dev].x = (m_ControlList[ctl].normalizer[0]);
        m_ExtCtlStates[dev].y = (m_ControlList[ctl].normalizer[1]);
        m_ExtCtlStates[dev].z = (m_ControlList[ctl].normalizer[2]);
        m_ExtCtlStates[dev].r = (m_ControlList[ctl].normalizer[3]);
        m_ExtCtlStates[dev].u = (m_ControlList[ctl].normalizer[4]);
        m_ExtCtlStates[dev].v = (m_ControlList[ctl].normalizer[5]);
        for (j = 0; j < JOYPOV_NUM; j++) {
          m_ExtCtlStates[dev].pov[j] = JOYPOV_CENTER;
          m_ExtCtlStates[dev].last_pov[j] = JOYPOV_CENTER;
        }
        for (j = 0; j < JOYPOV_NUM; j++) {
          for (i = 0; i < JOYPOV_DIR; i++) {
            m_ExtCtlStates[dev].povstarts[j][i] = (float)0.0;
            m_ExtCtlStates[dev].povtimes[j][i] = (float)0.0;
            m_ExtCtlStates[dev].povpresses[j][i] = 0;
          }
        }

        m_ExtCtlStates[dev].buttons = 0;
        for (i = 0; i < CT_MAX_BUTTONS; i++) {
          m_ExtCtlStates[dev].btnpresses[i] = 0;
          m_ExtCtlStates[dev].btntimes[i] = (float)0.0;
          m_ExtCtlStates[dev].btnstarts[i] = (float)0.0;
        }
      }
    }
  }
}

// get raw values for the controllers
int gameWinController::get_mouse_raw_values(int *x, int *y) {
  if (m_Suspended)
    return 0;

  *x = m_MseState.m_absX;
  *y = m_MseState.m_absY;

  return m_MseState.m_buttonMask;
}

unsigned gameWinController::get_joy_raw_values(int *x, int *y) {
  unsigned btn = 0;

  if (m_Suspended)
    return 0;

  for (int ctl = 0; ctl < m_NumControls; ctl++) {
    int dev = m_ControlList[ctl].id;

    if (dev >= CTID_EXTCONTROL0) {
      *x = m_ExtCtlStates[dev].x;
      *y = m_ExtCtlStates[dev].y;
      btn = m_ExtCtlStates[dev].buttons;
      if (*x || *y || btn)
        return btn;
    }
  }

  return 0;
}

//	note controller is index into ControlList.
float gameWinController::get_axis_value(int8_t controller, uint8_t axis, ct_format format, bool invert) {
  if (controller <= NULL_WINCONTROLLER || controller >= CT_MAX_CONTROLLERS)
    return 0.0f;

  struct gameWinController::t_controller *ctldev = &m_ControlList[controller];
  if (ctldev->id == CTID_INVALID)
    return 0.0f;

#ifdef _DEBUG
  if (m_ControlList[controller].id == CTID_KEYBOARD) {
    Int3();
    return 0.0f;
  }
#endif

  //	verify controller axis
  const int axisIndex = axis - 1;
  if (!CHECK_FLAG(ctldev->flags, 1 << axisIndex))
    return 0.0f;

  //	get raw value
  float axisval = 0.0f;
  switch (axis) {
  //	note we take care of mouse controls and external controls here
  case CT_X_AXIS:
    axisval = (float)((ctldev->id == CTID_MOUSE) ? m_MseState.m_deltaX : m_ExtCtlStates[ctldev->id].x);
    break;
  case CT_Y_AXIS:
    axisval = (float)((ctldev->id == CTID_MOUSE) ? m_MseState.m_deltaY : m_ExtCtlStates[ctldev->id].y);
    break;
  case CT_Z_AXIS:
    axisval = (float)((ctldev->id == CTID_MOUSE) ? m_MseState.m_deltaZ : m_ExtCtlStates[ctldev->id].z);
    break;
  case CT_R_AXIS:
    axisval = (float)m_ExtCtlStates[ctldev->id].r;
    break;
  case CT_U_AXIS:
    axisval = (float)m_ExtCtlStates[ctldev->id].u;
    break;
  case CT_V_AXIS:
    axisval = (float)m_ExtCtlStates[ctldev->id].v;
    break;
  default:
    Int3(); // NOT A VALID AXIS
  }

  // create normalizer
  float normalizer, nullzone;
  if (ctldev->id == CTID_MOUSE) {
    const float kMinFrameTime = 0.000001f;
    if (m_frame_time < kMinFrameTime) {
      m_frame_time = kMinFrameTime;
    }

    normalizer = ctldev->normalizer[axisIndex] * m_frame_time;
    nullzone = MOUSE_DEADZONE;
  } else {
    // really small deadzones will not take joystick drift into account, hence your mouse control will be cancelled out.
    normalizer = ctldev->normalizer[axisIndex];
    nullzone = (m_ControlList[controller].deadzone < 0.05f) ? 0.05f : m_ControlList[controller].deadzone;
  }

  // joystick needs to be normalized to -1.0 to 1.0
  float val = (axisval / normalizer) - ((ctldev->id == CTID_MOUSE) ? 0.0f : 1.0f);

  //	calculate adjusted value
  if (val > nullzone) {
    val = (val - nullzone) / (1.0f - nullzone);
  } else if (val < -nullzone) {
    val = (val + nullzone) / (1.0f - nullzone);
  } else {
    val = 0.0f;
  }

  val *= ctldev->sensmod[axisIndex] * ctldev->sens[axisIndex];
  val += 1.0f;

  if (val < 0.0f)
    val = 0.0f;
  if (val > 2.0f)
    val = 2.0f;

  // determine value based off requested format.
  if (format == ctDigital) {
    val = (val < 1.0f) ? 0.0f : 1.0f;
  } else if (format == ctAnalog) {
    val -= 1.0f;
  } else {
    val = 0.0f;
    mprintf(1, "gameController::axis unsupported format for function.\n");
  }

  ct_packet key_slide1, key_bank;

  get_packet(ctfTOGGLE_SLIDEKEY, &key_slide1);
  get_packet(ctfTOGGLE_BANKKEY, &key_bank);

  if (key_slide1.value || key_bank.value) {
    // Don't do mouse look if either toggle is happening
    return val;
  }

  if ((Current_pilot.mouselook_control) && (GAME_MODE == GetFunctionMode())) {
    // Don't do mouselook controls if they aren't enabled in multiplayer
    if ((Game_mode & GM_MULTI) && (!(Netgame.flags & NF_ALLOW_MLOOK)))
      return val;

    // Account for guided missile control
    if (Players[Player_num].guided_obj)
      return val;

    if ((axis == CT_X_AXIS) && (ctldev->id == CTID_MOUSE) && (val != 0.0f)) {
      if (!(Players[Player_num].controller_bitflags & PCBF_HEADINGLEFT) && val < 0.0f) {
        val = 0.0f;
      }

      if (!(Players[Player_num].controller_bitflags & PCBF_HEADINGRIGHT) && val > 0.0f) {
        val = 0.0f;
      }

      if (invert) {
        val = -val;
      }

      matrix orient;
      vm_AnglesToMatrix(&orient, 0.0f, val * Mouselook_sensitivity, 0.0f);

      Objects[Players[Player_num].objnum].orient = Objects[Players[Player_num].objnum].orient * orient;

      vm_Orthogonalize(&Objects[Players[Player_num].objnum].orient);
      ObjSetOrient(&Objects[Players[Player_num].objnum], &Objects[Players[Player_num].objnum].orient);
      return 0.0f;
    }

    if ((axis == CT_Y_AXIS) && (ctldev->id == CTID_MOUSE) && (val != 0.0f)) {
      if (!(Players[Player_num].controller_bitflags & PCBF_PITCHUP) && val < 0.0f) {
        val = 0.0f;
      }

      if (!(Players[Player_num].controller_bitflags & PCBF_PITCHDOWN) && val > 0.0f) {
        val = 0.0f;
      }

      if (invert) {
        val = -val;
      }

      matrix orient;
      vm_AnglesToMatrix(&orient, val * Mouselook_sensitivity, 0.0f, 0.0f);

      Objects[Players[Player_num].objnum].orient = Objects[Players[Player_num].objnum].orient * orient;

      vm_Orthogonalize(&Objects[Players[Player_num].objnum].orient);
      ObjSetOrient(&Objects[Players[Player_num].objnum], &Objects[Players[Player_num].objnum].orient);
      return 0.0f;
    }
  }

  // Adjust mouse sensitivity
  if (((axis == CT_X_AXIS) || (axis == CT_Y_AXIS)) && (ctldev->id == CTID_MOUSE)) {
    val *= Mouse_sensitivity;
  }

  return val;
}

float gameWinController::get_button_value(int8_t controller, ct_format format, uint8_t button) {
  float val = (float)0.0;

  if (controller <= NULL_WINCONTROLLER || controller >= CT_MAX_CONTROLLERS) {
    return 0.0f;
  }
  if (m_ControlList[controller].id == CTID_INVALID) {
    return 0.0f;
  }

#ifdef _DEBUG
  if (m_ControlList[controller].id == CTID_KEYBOARD) {
    Int3();
    return 0.0f;
  }
#endif

  if (button == NULL_BINDING) {
    return val;
  }

  //	buttons are idenitifed as 0=none, 1 = button 1, etc.  so if we have a valid button, then
  //	decrement counter.
  button--;

  // verify valid button.
  if ((unsigned)button >= m_ControlList[controller].buttons)
    return val;

  switch (format) {
    //	note we take care of mouse controls and external controls here
  case ctDownCount:
    if (m_ControlList[controller].id == CTID_MOUSE) {
      val = (float)ddio_MouseBtnDownCount(button);
    } else {
      val = (float)m_ExtCtlStates[m_ControlList[controller].id].btnpresses[button];
      m_ExtCtlStates[m_ControlList[controller].id].btnpresses[button] = 0;
    }
    break;

  case ctTime:
    if (m_ControlList[controller].id == CTID_MOUSE) {
      val = ddio_MouseBtnDownTime(button);
    } else {
      if (!(m_ExtCtlStates[m_ControlList[controller].id].buttons & (1 << button))) {
        val = m_ExtCtlStates[m_ControlList[controller].id].btntimes[button];
        m_ExtCtlStates[m_ControlList[controller].id].btnstarts[button] = (float)0.0;
        m_ExtCtlStates[m_ControlList[controller].id].btntimes[button] = (float)0.0;
      } else {
        val = WinControllerTimer - m_ExtCtlStates[m_ControlList[controller].id].btnstarts[button];
        m_ExtCtlStates[m_ControlList[controller].id].btnstarts[button] = WinControllerTimer;
        m_ExtCtlStates[m_ControlList[controller].id].btntimes[button] = (float)0.0;
      }
    }
    break;

  case ctDigital:
    if (m_ControlList[controller].id == CTID_MOUSE) {
      if (m_MseState.m_buttonMask & (1 << button))
        val = 1.0f;
    } else if (m_ExtCtlStates[m_ControlList[controller].id].buttons & (1 << button)) {
      val = 1.0f;
    }
    break;

  default:
    mprintf(1, "gameController::button unsupported format for function\n");
  }

  return val;
}

//	do some pov stuff
float gameWinController::get_pov_value(int8_t controller, ct_format format, uint8_t pov_number, uint8_t pov) {
  float val = (float)0.0;

  if (controller <= NULL_WINCONTROLLER || controller >= CT_MAX_CONTROLLERS) {
    return val;
  }
  if (m_ControlList[controller].id == CTID_INVALID) {
    return val;
  }
#ifdef _DEBUG
  if (m_ControlList[controller].id == CTID_KEYBOARD) {
    Int3();
    return 0.0f;
  }
#endif
  if (!(m_ControlList[controller].flags & (CTF_POV << pov_number))) {
    return val;
  }

  int pov_index = pov / (JOYPOV_MAXVAL / JOYPOV_DIR);
  int cur_pov_index = m_ExtCtlStates[m_ControlList[controller].id].pov[pov_number] / (JOYPOV_MAXVAL / JOYPOV_DIR);

  switch (format) {
    //	note we take care of mouse controls and external controls here
  case ctDownCount:
    if (pov_index == JOYPOV_DIR)
      val = 0.0f;
    else {
      val = m_ExtCtlStates[m_ControlList[controller].id].povpresses[pov_number][pov_index];
      m_ExtCtlStates[m_ControlList[controller].id].povpresses[pov_number][pov_index] = 0;
    }
    break;

  case ctDigital: {
    if (m_ExtCtlStates[m_ControlList[controller].id].pov[pov_number] == JOYPOV_CENTER)
      val = 0.0f;
    else if ((cur_pov_index == 0 || cur_pov_index == 1 || cur_pov_index == 7) && (pov == JOYPOV_UP))
      val = 1.0f;
    else if ((cur_pov_index == 1 || cur_pov_index == 2 || cur_pov_index == 3) && (pov == JOYPOV_RIGHT))
      val = 1.0f;
    else if ((cur_pov_index == 3 || cur_pov_index == 4 || cur_pov_index == 5) && (pov == JOYPOV_DOWN))
      val = 1.0f;
    else if ((cur_pov_index == 5 || cur_pov_index == 6 || cur_pov_index == 7) && (pov == JOYPOV_LEFT))
      val = 1.0f;
    break;
  }

  case ctTime:
    if (cur_pov_index == pov_index) {
      val = WinControllerTimer - m_ExtCtlStates[m_ControlList[controller].id].povstarts[pov_number][pov_index];
      m_ExtCtlStates[m_ControlList[controller].id].povstarts[pov_number][pov_index] = WinControllerTimer;
      m_ExtCtlStates[m_ControlList[controller].id].povtimes[pov_number][pov_index] = 0.0f;
    } else {
      val = m_ExtCtlStates[m_ControlList[controller].id].povtimes[pov_number][pov_index];
      m_ExtCtlStates[m_ControlList[controller].id].povstarts[pov_number][pov_index] = 0.0f;
      m_ExtCtlStates[m_ControlList[controller].id].povtimes[pov_number][pov_index] = 0.0f;
    }
    break;

  default:
    mprintf(1, "gameController::pov unsupported format for function\n");
  }

  return val;
}

//	get keyboard info
float gameWinController::get_key_value(int key, ct_format format) {
  float val = (float)0.0;

  ASSERT(key < DDIO_MAX_KEYS);

  switch (format) {
    //	note we take care of mouse controls and external controls here
  case ctDigital:
    if (KEY_STATE(key))
      val = 1.0f;
    break;

  case ctDownCount:
    val = (float)ddio_KeyDownCount(key);
    break;

  case ctTime:
    val = (float)ddio_KeyDownTime(key);
    break;

  default:
    mprintf(1, "gameController::key unsupported format for function\n");
  }

  return val;
}

int gameWinController::assign_function(ct_function *func) {
  //	for now this is a straight forward translation (that is, no mapping of needs to controller
  //	list to create elements.
  ct_element elem;
  int i;

  for (i = 0; i < CTLBINDS_PER_FUNC; i++) {
    elem.ctl[i] = NULL_WINCONTROLLER;

    switch (func->ctype[i]) {
      int pov_n;

    case ctNone:
      break;
    case ctKey:
      elem.ctl[i] = 0;
      break;
    case ctAxis:
      elem.ctl[i] = get_axis_controller(func->value[i]);
      break;

    case ctButton:
      elem.ctl[i] = get_button_controller(func->value[i]);
      break;

    case ctMouseAxis:
      elem.ctl[i] = 1;
      break;

    case ctMouseButton:
      //	find a free mouse button.
      if ((m_ControlList[1].btnmask & (1 << (func->value[i] - 1))) &&
          ((func->value[i] - 1) < m_ControlList[1].buttons)) {
        elem.ctl[i] = 1;
      }
      break;

    case ctPOV:
    case ctPOV2:
    case ctPOV3:
    case ctPOV4:
      if (func->ctype[i] == ctPOV) {
        pov_n = 0;
      } else {
        pov_n = (func->ctype[i] - ctPOV2) + 1;
      }
      elem.ctl[i] = get_pov_controller(pov_n);
      break;
    }

    elem.ctype[i] = func->ctype[i];
    elem.value[i] = func->value[i];
  }

  elem.format = func->format;
  elem.flags[0] = func->flags[0];
  elem.flags[1] = func->flags[1];
  elem.enabled = true;

  assign_element(func->id, &elem);

  return func->id;
}

//	sets up an elements information structure
void gameWinController::assign_element(int id, ct_element *elem) {
  //	assign element, check to see if valid.
  int i;

  m_ElementList[id].format = elem->format;
  m_ElementList[id].flags[0] = elem->flags[0];
  m_ElementList[id].flags[1] = elem->flags[1];
  m_ElementList[id].enabled = elem->enabled;

  //	look through each controller and validate each element
  for (i = 0; i < CTLBINDS_PER_FUNC; i++) {
    m_ElementList[id].ctl[i] = elem->ctl[i];
    m_ElementList[id].value[i] = elem->value[i];
    m_ElementList[id].ctype[i] = elem->ctype[i];

    if (m_ElementList[id].ctl[i] != NULL_WINCONTROLLER) {
      // this function shouldn't do any error checking!!!!  keep same controller values and bindings unless
      // bindings are truly bogus.
      switch (m_ElementList[id].ctype[i]) {
      case ctMouseButton:
      case ctButton:
        if (elem->value[i] > CT_MAX_BUTTONS) {
          m_ElementList[id].ctl[i] = NULL_WINCONTROLLER;
          m_ElementList[id].value[i] = NULL_BINDING;
        }
        break;
      case ctMouseAxis:
      case ctAxis:
        //					if (!(m_ControlList[elem->ctl[i]].flags & (1<<(elem->value[i]-1))))
        //						m_ElementList[id].ctl[i] = NULL_WINCONTROLLER;
        break;
      case ctPOV:
      case ctPOV2:
      case ctPOV3:
      case ctPOV4:
        //					if (!(m_ControlList[elem->ctl[i]].flags & CTF_POV))
        //						m_ElementList[id].ctl[i] = NULL_WINCONTROLLER;
        break;
      case ctKey:
        break;
      default:
        m_ElementList[id].value[i] = NULL_BINDING;
        m_ElementList[id].ctl[i] = NULL_WINCONTROLLER;
      }
    } else {
      m_ElementList[id].value[i] = NULL_BINDING;
    }
  }
}

int8_t gameWinController::get_axis_controller(uint8_t axis) {
  //	start from controller 2 because 0, and 1 are reserved for keyboard and mouse
  if (axis == NULL_BINDING)
    return NULL_WINCONTROLLER;

  for (int i = 2; i < m_NumControls; i++)
    if ((m_ControlList[i].flags & (1 << (axis - 1))) && m_ControlList[i].id != CTID_INVALID)
      return i;

  return NULL_WINCONTROLLER;
}

int8_t gameWinController::get_button_controller(uint8_t btn) {
  unsigned mask;

  //	buttons range from 1-CT_MAX_BUTTONS
  ASSERT(btn <= CT_MAX_BUTTONS);
  if (btn == NULL_BINDING)
    return NULL_WINCONTROLLER;

  mask = 1 << (btn - 1);

  //	start from controller 2 because 0, and 1 are reserved for keyboard and mouse
  for (int i = 2; i < m_NumControls; i++)
    //@@		if (((unsigned)btn < m_ControlList[i].buttons) && !(m_ControlList[i].btnmask & mask) &&
    //(m_ControlList[i].id
    //!= CTID_INVALID)) {
    if (((unsigned)btn < m_ControlList[i].buttons) && (m_ControlList[i].id != CTID_INVALID)) {
      //@@			m_ControlList[i].btnmask |= mask;
      return i;
    }

  return NULL_WINCONTROLLER;
}

//	returns the controller with a pov hat
int8_t gameWinController::get_pov_controller(uint8_t pov) {
  //	start from controller 2 because 0, and 1 are reserved for keyboard and mouse
  uint16_t pov_flag = CTF_POV << (pov);

  for (int i = 2; i < m_NumControls; i++)
    if ((m_ControlList[i].flags & pov_flag) && m_ControlList[i].id != CTID_INVALID)
      return i;

  return NULL_WINCONTROLLER;
}

//	enumerate all controllers on system
bool gameWinController::enum_controllers(char *remote_adr) {
  const float kNormalizerMouseX = 640.0f;
  const float kNormalizerMouseY = 480.0f;
  const float kNormalizerMouseZ = 100.0f;

  int num_devs = 0, dev;
  int i;

  for (i = 0; i < CT_MAX_CONTROLLERS; i++)
    m_ControlList[i].id = CTID_INVALID;

  //	Add keyboard controller
  m_ControlList[num_devs].id = CTID_KEYBOARD;
  m_ControlList[num_devs].buttons = 0;
  m_ControlList[num_devs].flags = 0;
  num_devs++;

  //	add mouse controller
  int left, top, right, bottom, zmin, zmax; // btns, axes,
  int nbtns, naxis, btnmask;
  ddio_MouseGetLimits(&left, &top, &right, &bottom, &zmin, &zmax);
  btnmask = ddio_MouseGetCaps(&nbtns, &naxis);

  // we will try to support a mouse with 3 axis and N_MSEBTNS buttons.
  m_ControlList[num_devs].id = CTID_MOUSE;
  m_ControlList[num_devs].buttons = nbtns;
  m_ControlList[num_devs].flags = CTF_X_AXIS | CTF_Y_AXIS; // | (naxis>=3 ? CTF_Z_AXIS : 0);
  m_ControlList[num_devs].btnmask = btnmask;
  m_ControlList[num_devs].normalizer[0] = kNormalizerMouseX;
  m_ControlList[num_devs].normalizer[1] = kNormalizerMouseY;
  m_ControlList[num_devs].normalizer[2] = kNormalizerMouseZ;
  m_ControlList[num_devs].sens[0] = 1.0f;
  m_ControlList[num_devs].sens[1] = 1.0f;
  m_ControlList[num_devs].sens[2] = 1.0f;
  m_ControlList[num_devs].sensmod[0] = 1.0f;
  m_ControlList[num_devs].sensmod[1] = 1.0f;
  m_ControlList[num_devs].sensmod[2] = 1.0f;
  num_devs++;

  //	we should initialize multiple controls
  //	before doing this, MAKE SURE REMOTE CONTROL SUPPORTS IT.
  for (dev = JOYSTICK_1; dev <= JOYSTICK_8; dev++) {
    tJoyInfo jc;

    //	check if device is plugged in.
    if (joy_IsValid(dev)) {
      // query the joystick's capabilites to see if joystick is truly valid
      joy_GetJoyInfo((tJoystick)dev, &jc);

      m_ControlList[num_devs].id = dev;
      m_ControlList[num_devs].buttons = jc.num_btns;
      m_ControlList[num_devs].btnmask = 0;
      m_ControlList[num_devs].flags =
          CTF_X_AXIS | CTF_Y_AXIS | ((jc.axes_mask & JOYFLAG_ZVALID) ? CTF_Z_AXIS : 0) |
          ((jc.axes_mask & JOYFLAG_RVALID) ? CTF_R_AXIS : 0) | ((jc.axes_mask & JOYFLAG_UVALID) ? CTF_U_AXIS : 0) |
          ((jc.axes_mask & JOYFLAG_VVALID) ? CTF_V_AXIS : 0) | ((jc.axes_mask & JOYFLAG_POVVALID) ? CTF_POV : 0) |
          ((jc.axes_mask & JOYFLAG_POV2VALID) ? CTF_POV2 : 0) | ((jc.axes_mask & JOYFLAG_POV3VALID) ? CTF_POV3 : 0) |
          ((jc.axes_mask & JOYFLAG_POV4VALID) ? CTF_POV4 : 0);
      m_ControlList[num_devs].normalizer[0] = (jc.maxx - jc.minx) / 2.0f;
      m_ControlList[num_devs].normalizer[1] = (jc.maxy - jc.miny) / 2.0f;
      m_ControlList[num_devs].normalizer[2] = (jc.maxz - jc.minz) / 2.0f;
      m_ControlList[num_devs].normalizer[3] = (jc.maxr - jc.minr) / 2.0f;
      m_ControlList[num_devs].normalizer[4] = (jc.maxu - jc.minu) / 2.0f;
      m_ControlList[num_devs].normalizer[5] = (jc.maxv - jc.minv) / 2.0f;

      for (i = 0; i < CT_NUM_AXES; i++) {
        m_ControlList[num_devs].sens[i] = 1.0f;
        m_ControlList[num_devs].sensmod[i] = 1.0f;
      }
      m_ControlList[num_devs].deadzone = JOY_DEADZONE;

      mprintf(0, "Controller %s found.\n", jc.name);

      // okay, now search for a '****.ctl' file in the current directory.
      parse_ctl_file(num_devs, jc.name);

      num_devs++;
      if (num_devs == CT_MAX_CONTROLLERS)
        break;
    }
  }
  for (i = num_devs; i < CT_MAX_CONTROLLERS; i++) {
    m_ControlList[i].id = CTID_INVALID;
  }

  m_NumControls = num_devs;

  gameWinController::flush();

  return 1;
}

//	---------------------------------------------------------------------------
//	controller functions

void gameWinController::extctl_getpos(int id) {
  tJoyPos ji;
  float timer_val;
  int i;

  if (!m_JoyActive) {
    return;
  }

  timer_val = timer_GetTime();

  joy_GetRawPos((tJoystick)id, &ji);

  //	if (g_accum_frame_time == 0.0f) {
  m_ExtCtlStates[id].x = (int)ji.x;
  m_ExtCtlStates[id].y = (int)ji.y;
  m_ExtCtlStates[id].z = (int)ji.z;
  m_ExtCtlStates[id].r = (int)ji.r;
  m_ExtCtlStates[id].u = (int)ji.u;
  m_ExtCtlStates[id].v = (int)ji.v;

  for (i = 0; i < JOYPOV_NUM; i++) {
    //	when pov changes position and new position is not in center, then set a new start time.
    m_ExtCtlStates[id].last_pov[i] = m_ExtCtlStates[id].pov[i];
    m_ExtCtlStates[id].pov[i] = ji.pov[i];
    int pov_index = m_ExtCtlStates[id].pov[i] / (JOYPOV_MAXVAL / JOYPOV_DIR);
    int last_pov_index = m_ExtCtlStates[id].last_pov[i] / (JOYPOV_MAXVAL / JOYPOV_DIR);

    if (m_ExtCtlStates[id].pov[i] != m_ExtCtlStates[id].last_pov[i]) {
      if (m_ExtCtlStates[id].pov[i] != JOYPOV_CENTER)
        m_ExtCtlStates[id].povstarts[i][pov_index] = timer_val;
      if (m_ExtCtlStates[id].last_pov[i] != JOYPOV_CENTER)
        m_ExtCtlStates[id].povtimes[i][last_pov_index] = timer_val - m_ExtCtlStates[id].povstarts[i][last_pov_index];
      m_ExtCtlStates[id].povpresses[i][pov_index]++;
    }
    if (m_ExtCtlStates[id].pov[i] != JOYPOV_CENTER) {
      m_ExtCtlStates[id].povtimes[i][pov_index] = timer_val - m_ExtCtlStates[id].povstarts[i][pov_index];
    }
  }
  //	}

  //	handle buttons
  for (i = 0; i < CT_MAX_BUTTONS; i++) {
    //	case if we read time before doing this again.
    if ((ji.buttons & (1 << i)) && (m_ExtCtlStates[id].btnstarts[i] == (float)0.0))
      m_ExtCtlStates[id].btnstarts[i] = timer_val;
    if ((ji.buttons & (1 << i)) && !(m_ExtCtlStates[id].buttons & (1 << i))) {
      m_ExtCtlStates[id].btnpresses[i]++;
      m_ExtCtlStates[id].btnstarts[i] = timer_val;
      //	mprintf(0, "Start time for %d = %f\n", i, timer_val);
    }

    if (ji.buttons & (1 << i)) // if button is down
      m_ExtCtlStates[id].btntimes[i] = timer_val - m_ExtCtlStates[id].btnstarts[i];
    else if (m_ExtCtlStates[id].buttons & (1 << i)) // if button is up and last pass it was down.
      m_ExtCtlStates[id].btntimes[i] = timer_val - m_ExtCtlStates[id].btnstarts[i];
  }

  m_ExtCtlStates[id].buttons = ji.buttons;
}

void gameWinController::extctl_geteval(int id) {}

void gameWinController::mouse_geteval() {
  if (!m_MouseActive)
    return;

  if (g_accum_frame_time != 0.0f)
    return;

  int x, y, dx, dy;
  uint32_t btnmask = (uint32_t)ddio_MouseGetState(&x, &y, &dx, &dy);

  m_MseState.m_deltaX = dx;
  m_MseState.m_deltaY = dy;
  m_MseState.m_deltaZ = 0;
  m_MseState.m_absX = x;
  m_MseState.m_absY = y;
  m_MseState.m_buttonMask = btnmask;

  mprintf_at(1, 5, 30, "btnmask=%08d\n", btnmask);
}

// gets sensitivity of axis item
float gameWinController::get_axis_sensitivity(ct_type axis_type, uint8_t axis) {
  axis--;
  ASSERT(axis < CT_NUM_AXES);

  switch (axis_type) {
  case ctMouseAxis:
    return m_ControlList[1].sens[axis];

  case ctAxis:
    return m_ControlList[2].sens[axis];

  default:
    Int3();
  }

  return 0.0f;
}

// sets sensitivity of axis item
void gameWinController::set_axis_sensitivity(ct_type axis_type, uint8_t axis, float val) {
  int i;

  axis--;
  ASSERT(axis < CT_NUM_AXES);

  switch (axis_type) {
  case ctMouseAxis:
    m_ControlList[1].sens[axis] = val;
    break;
  case ctAxis:
    for (i = 2; i < CT_MAX_CONTROLLERS; i++)
      m_ControlList[i].sens[axis] = val;
    break;
  default:
    Int3();
  }
}

//	toggles use of deadzone for controllers. ctl can be 0 to ???
// dead zone is from 0.0 to 0.5
void gameWinController::set_controller_deadzone(int ctl, float deadzone) {
  if (ctl < 0 || ctl >= (m_NumControls - 2)) {
    return;
  }
  if (deadzone < 0.0f)
    deadzone = 0.0f;
  if (deadzone > 0.9f)
    deadzone = 0.9f;

  m_ControlList[ctl + 2].deadzone = deadzone;
}

char Ctltext_AxisBindings[][16] = {"", "X-axis", "Y-axis", "Z-axis", "R-axis", "U-axis", "V-axis"};

char Ctltext_BtnBindings[][16] = {"",      "btn1",  "btn2",  "btn3",  "btn4",  "btn5",  "btn6",  "btn7",  "btn8",
                                  "btn9",  "btn10", "btn11", "btn12", "btn13", "btn14", "btn15", "btn16", "btn17",
                                  "btn18", "btn19", "btn20", "btn21", "btn22", "btn23", "btn24", "btn25", "btn26",
                                  "btn27", "btn28", "btn29", "btn30", "btn31", "btn32"};

char Ctltext_PovBindings[][16] = {"", "pov-U", "pov-R", "pov-D", "pov-L"};

#define NUM_AXISBINDSTRINGS (sizeof(Ctltext_AxisBindings) / sizeof(Ctltext_AxisBindings[0]))
#define NUM_BTNBINDSTRINGS (sizeof(Ctltext_BtnBindings) / sizeof(Ctltext_AxisBindings[0]))

// retrieves binding text for desired function, binding, etc.
const char *gameWinController::get_binding_text(ct_type type, uint8_t ctrl, uint8_t bind) {
  static char binding_text[16];
  const char *str;

  if (ctrl == NULL_CONTROLLER) {
    return NULL;
  }

  switch (type) {
    int pov_n;

  case ctAxis: {
    ASSERT(bind < NUM_AXISBINDSTRINGS);
    str = Ctltext_AxisBindings[bind];
    if ((ctrl - 2) > 0) {
      sprintf(binding_text, "J%d:%s", (ctrl - 2) + 1, str);
    } else {
      return str;
    }
    break;
  }

  case ctMouseAxis: {
    str = ddio_MouseGetAxisText(((int8_t)bind) - 1);
    return str;
  }

  case ctButton: {
    ASSERT(bind < NUM_BTNBINDSTRINGS);
    str = Ctltext_BtnBindings[bind];
    if ((ctrl - 2) > 0) {
      sprintf(binding_text, "J%d:%s", (ctrl - 2) + 1, str);
    } else {
      return str;
    }
    break;
  }

  case ctMouseButton: {
    str = ddio_MouseGetBtnText(((int8_t)bind) - 1);
    return str;
  }

  case ctPOV:
  case ctPOV2:
  case ctPOV3:
  case ctPOV4: {
    uint16_t povpos = bind;

    if (type == ctPOV) {
      pov_n = 0;
    } else {
      pov_n = (type - ctPOV2) + 1;
    }
    if (povpos == JOYPOV_UP)
      str = Ctltext_PovBindings[1];
    else if (povpos == JOYPOV_DOWN)
      str = Ctltext_PovBindings[3];
    else if (povpos == JOYPOV_LEFT)
      str = Ctltext_PovBindings[4];
    else if (povpos == JOYPOV_RIGHT)
      str = Ctltext_PovBindings[2];
    else
      str = Ctltext_PovBindings[0];
    if ((ctrl - 2) > 0) {
      if (pov_n) {
        sprintf(binding_text, "J%d:%s%d", (ctrl - 2) + 1, str, pov_n);
      } else {
        sprintf(binding_text, "J%d:%s", (ctrl - 2) + 1, str);
      }
    } else {
      if (pov_n) {
        sprintf(binding_text, "%s%d", str, pov_n);
      } else {
        return str;
      }
    }
    break;
  }

  case ctKey:
    break;

  default:
    if (type == ctNone) {
      Int3();
    }
    binding_text[0] = 0;
  }

  return binding_text;
}

//	CTL file parser
#define N_CTLCMDS 9
#define CTLCMD_NAME 0
#define CTLCMD_AXIS 1
#define CTLCMD_DEAD 2
#define CTLCMD_SX 3
#define CTLCMD_SY 4
#define CTLCMD_SZ 5
#define CTLCMD_SR 6
#define CTLCMD_SU 7
#define CTLCMD_SV 8

const char *CTLCommands[N_CTLCMDS] = {"name",     "axis",     "deadzone", "sensmodx", "sensmody",
                                      "sensmodz", "sensmodr", "sensmodu", "sensmodv"};

int CTLLex(const char *command) {
  int i;
  for (i = 0; i < N_CTLCMDS; i++) {
    if (strcmp(CTLCommands[i], command) == 0)
      return i;
  }

  return INFFILE_ERROR;
}

// okay, now search for a '****.ctl' file in the current directory.
void gameWinController::parse_ctl_file(int devnum, const char *ctlname) {
  //	parse each file until we find a name match, no name match, just return
  char filename[_MAX_FNAME];
  int i;

  if (ddio_FindFileStart("*.ctl", filename)) {
    do {
      InfFile file;
      bool found_name = false;

      if (file.Open(filename, "[controller settings]", CTLLex)) {
        // parse each line, setting the appropriate values, etc.
        while (file.ReadLine()) {
          int cmd;
          char operand[128];

          while ((cmd = file.ParseLine(operand, INFFILE_LINELEN)) > INFFILE_ERROR) {
            // we want to assert that the name command comes before any other to verify
            // this is the file we really want to change.
            switch (cmd) {
            case CTLCMD_NAME:
              if (strcmp(ctlname, operand) != 0)
                goto cancel_file_parse;
              found_name = true;
              break;

            case CTLCMD_DEAD: // deadzone
              if (!found_name)
                goto cancel_file_parse;
              else {
                m_ControlList[devnum].deadzone = atof(operand);
              }
              break;

            case CTLCMD_AXIS: // allowable axis.
                              // format of command is "+Z-R"
                              //	this would add a Z axis to the controller.  -R would remove the Rudder.
                              // you can do this for X,Y,Z,R,U,V.
              if (!found_name)
                goto cancel_file_parse;
              else {
                int slen = strlen(operand);
                for (i = 0; i <= slen; i += 2) {
                  int axis_flag;
                  if ((i + 1) <= slen) {
                    char axis_cmd = tolower(operand[i + 1]);
                    if (axis_cmd == 'x')
                      axis_flag = CTF_X_AXIS;
                    else if (axis_cmd == 'y')
                      axis_flag = CTF_Y_AXIS;
                    else if (axis_cmd == 'z')
                      axis_flag = CTF_Z_AXIS;
                    else if (axis_cmd == 'r')
                      axis_flag = CTF_R_AXIS;
                    else if (axis_cmd == 'u')
                      axis_flag = CTF_U_AXIS;
                    else if (axis_cmd == 'v')
                      axis_flag = CTF_V_AXIS;
                    else
                      axis_flag = 0;
                    if (operand[i] == '+') {
                      m_ControlList[devnum].flags |= axis_flag;
                    } else if (operand[i] == '-') {
                      m_ControlList[devnum].flags &= (~axis_flag);
                    } else {
                      goto cancel_file_parse;
                    }
                  } else {
                    break; // this should break out of the axis search but continue with the file
                  }
                }
              }
              break;

            case CTLCMD_SX: // allow modification of global sensitivity modifiers
            case CTLCMD_SY:
            case CTLCMD_SZ:
            case CTLCMD_SR:
            case CTLCMD_SU:
            case CTLCMD_SV: {
              int idx = (cmd - CTLCMD_SX);
              m_ControlList[devnum].sensmod[idx] = atof(operand);
              break;
            }
            }
          }
        }
      cancel_file_parse:
        file.Close();
      }
    } while (ddio_FindNextFile(filename));
    ddio_FindFileClose();
  }
}

//	These functions allow one to find a file
//		You use FindFileStart by giving it a wildcard (like *.*, *.txt, u??.*, whatever).  It returns
//		a filename in namebuf.
//		Use FindNextFile to get the next file found with the wildcard given in FindFileStart.
//		Use FindFileClose to end your search.
bool ddio_FindFileStart(const char *wildcard, char *namebuf);
bool ddio_FindNextFile(char *namebuf);
void ddio_FindFileClose();
