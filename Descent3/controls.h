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

 * $Logfile: /DescentIII/Main/controls.h $
 * $Revision: 36 $
 * $Date: 10/21/99 6:04p $
 * $Author: Matt $
 *
 * Game controls header
 *
 * $Log: /DescentIII/Main/controls.h $
 *
 * 36    10/21/99 6:04p Matt
 * Mac merge
 *
 * 35    7/15/99 5:39p Samir
 * upped max joystick sensitivity to 4.0 from 2.0.
 *
 * 34    4/30/99 10:52p Samir
 * fixed energy-to-shield usage and made Load and Save COnfig take a
 * pilot.
 *
 * 33    4/24/99 6:29p Jason
 * changed mouse sensitivity
 *
 * 32    3/22/99 6:20p Jeff
 * added 2 more audio taunts.  a mulitplayer event when someone plays an
 * audio taunt.  option to disable audio taunts.
 *
 * 31    2/26/99 2:13a Samir
 * added audio taunt keys.
 *
 * 30    2/16/99 12:07p Samir
 * redid controller config with new ui.
 *
 * 29    1/13/99 6:37a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 28    12/09/98 1:09p Jason
 * second draft of automap
 *
 * 27    12/02/98 11:39a Samir
 * added better code to handle changes in controller function list for
 * pilot files (needed to have a constant giving number of controller
 * functions in demo 1.0)
 *
 * 26    11/30/98 4:54p Samir
 * added rear view config item.
 *
 * 25    11/30/98 1:09p Samir
 * added rear view toggle.
 *
 * 24    10/21/98 10:36a Samir
 * added code to turn on or off joystick or mouse.
 *
 * 23    10/08/98 10:52a Samir
 * added countermeasure and weapon cycling.
 *
 * 22    9/17/98 3:24p Samir
 * added headlight configuration.
 *
 * 21    8/31/98 6:49p Jeff
 * made inventory and countermeasure keys customizable
 *
 * 20    8/31/98 12:39p Samir
 * added code to resume controllers when restoring game mode.
 *
 * 19    6/18/98 4:44p Samir
 * added changes for multiple configs for joystick controls.
 *
 * 18    5/19/98 3:36p Samir
 * added automap key.
 *
 * 17    5/12/98 3:04p Samir
 * added button control for pbh.
 *
 * 16    4/27/98 7:24p Samir
 * poll controller at specified rate.
 *
 * 15    4/09/98 2:23p Jason
 * added guided/afterburner stuff
 *
 * 14    4/08/98 3:44p Samir
 * added toggle bank and configuration for afterburner
 *
 * 13    4/02/98 7:58p Samir
 * Fixed up control setting saving and restoring.
 *
 * 12    3/13/98 8:55p Jeff
 * Various changes to move control configuration into Pilot file
 *
 * 11    2/16/98 7:15p Matt
 * Added fire_secondary_down_state
 *
 * 10    2/16/98 3:01p Samir
 * Added fire_primary_down_state and changed some configuration.
 *
 * 9     2/15/98 7:06p Samir
 * Added functions to save controller state.
 *
 * 8     2/12/98 8:48p Matt
 * Changed controls system to keep the reading of the controls seperate
 * from using the results.  Got rid of the Controls global.
 *
 * 7     1/12/98 6:28p Samir
 * New keys for sliding and use RCTRL for firing too.
 *
 * 6     12/05/97 10:59a Samir
 * Somewhat revised controls for keyboard.   Joystick now has variable
 * sensitivity.
 *
 * 5     12/03/97 7:32p Samir
 * More D2 like keyboard movement.
 *
 * 4     11/05/97 3:45p Samir
 * InitControls will close the previous call to InitControls.
 *
 * 3     10/30/97 4:02p Matt
 * Added the flare
 *
 * 2     8/29/97 1:49p Samir
 * Added toggliing slide.
 *
 * 8     4/24/97 12:10p Samir
 * Added weapon firing for primary and secondary weapons.
 *
 * 7     4/23/97 1:06p Samir
 * Implemented Suspend and Resume Controls as well as newer control system
 *
 * 6     4/17/97 2:48p Samir
 * ReadFlyingControls renamed from read_flying_controls to match naming
 * convention rules.
 *
 * 5     4/16/97 1:03p Samir
 * Added fire primary button information
 *
 * 4     4/14/97 3:29p Samir
 * Implemented game controls structure.
 *
 * 3     4/14/97 12:55p Samir
 * Added primary fire button
 *
 * 2     4/11/97 2:15p Samir
 * game controls functions defined for movement.
 *
 * $NoKeywords: $
 */

#ifndef CONTROLS_H
#define CONTROLS_H

#include "object.h"
#include "controller.h"

class gameController;
class pilot;

#define READF_MOUSE 0x2
#define READF_JOY 0x1
#define JOY_AXIS_SENS_RANGE 4.0f
#define MSE_AXIS_SENS_RANGE 4.0f

// used to set or get axis sensitivity
#define HEADING_AXIS 0
#define PITCH_AXIS 1
#define BANK_AXIS 2
#define HORIZONTAL_AXIS 3
#define VERTICAL_AXIS 4
#define THROTTLE_AXIS 5

//	Controller functions
const int NUM_CTLFUNCS_DEMOv1_0 = 63;
const int NUM_CONTROLLER_FUNCTIONS = 73;

const int ctfFORWARD_THRUSTAXIS = 0, ctfFORWARD_THRUSTKEY = 1, ctfREVERSE_THRUSTKEY = 2, ctfUP_THRUSTAXIS = 3,
          ctfUP_THRUSTKEY = 4, ctfDOWN_THRUSTKEY = 5, ctfRIGHT_THRUSTAXIS = 6, ctfRIGHT_THRUSTKEY = 7,
          ctfLEFT_THRUSTKEY = 8, ctfPITCH_DOWNAXIS = 9, ctfPITCH_DOWNKEY = 10, ctfPITCH_UPKEY = 11,
          ctfBANK_RIGHTAXIS = 12, ctfBANK_RIGHTKEY = 13, ctfBANK_LEFTKEY = 14, ctfHEADING_RIGHTAXIS = 15,
          ctfHEADING_RIGHTKEY = 16, ctfHEADING_LEFTKEY = 17, ctfFIREPRIMARY_BUTTON = 18, ctfFIREPRIMARY_KEY = 19,
          ctfFIREPRIMARY_KEY2 = 20, ctfFIRESECONDARY_BUTTON = 21, ctfFIRESECONDARY_KEY = 22, ctfTOGGLE_SLIDEKEY = 23,
          ctfTOGGLE_SLIDEBUTTON = 24, ctfFIREFLARE_KEY = 25, ctfFIREFLARE_BUTTON = 26, ctfUP_BUTTON = 27,
          ctfDOWN_BUTTON = 28, ctfLEFT_BUTTON = 29, ctfRIGHT_BUTTON = 30, ctfAFTERBURN_KEY = 31,
          ctfAFTERBURN_BUTTON = 32, ctfFORWARD_BUTTON = 33, ctfREVERSE_BUTTON = 34, ctfTOGGLE_BANKKEY = 35,
          ctfTOGGLE_BANKBUTTON = 36, ctfHEADING_LEFTBUTTON = 37, ctfHEADING_RIGHTBUTTON = 38, ctfPITCH_UPBUTTON = 39,
          ctfPITCH_DOWNBUTTON = 40, ctfBANK_LEFTBUTTON = 41, ctfBANK_RIGHTBUTTON = 42, ctfAUTOMAP_KEY = 43,
          ctfPREV_INVKEY = 44, ctfNEXT_INVKEY = 45, ctfINV_USEKEY = 46, ctfPREV_CNTMSKEY = 47, ctfNEXT_CNTMSKEY = 48,
          ctfCNTMS_USEKEY = 49, ctfHEADLIGHT_KEY = 50, ctfHEADLIGHT_BUTTON = 51, ctfAUTOMAP_BUTTON = 52,
          ctfPREV_INVBTN = 53, ctfNEXT_INVBTN = 54, ctfINV_USEBTN = 55, ctfPREV_CNTMSBTN = 56, ctfNEXT_CNTMSBTN = 57,
          ctfCNTMS_USEBTN = 58, ctfWPNSEL_PCYCLEKEY = 59, ctfWPNSEL_PCYCLEBTN = 60, ctfWPNSEL_SCYCLEKEY = 61,
          ctfWPNSEL_SCYCLEBTN = 62, ctfREARVIEW_KEY = 63, ctfREARVIEW_BTN = 64, ctfAUDIOTAUNT1_KEY = 65,
          ctfAUDIOTAUNT1_BTN = 66, ctfAUDIOTAUNT2_KEY = 67, ctfAUDIOTAUNT2_BTN = 68, ctfAUDIOTAUNT3_KEY = 69,
          ctfAUDIOTAUNT3_BTN = 70, ctfAUDIOTAUNT4_KEY = 71, ctfAUDIOTAUNT4_BTN = 72;

struct game_controls {
  //	movement values
  //	these values are from -1.0 to 1.0.-
  float pitch_thrust;
  float heading_thrust;
  float bank_thrust;
  float vertical_thrust;
  float sideways_thrust;
  float forward_thrust;
  float afterburn_thrust;

  // these values modify thrust
  bool toggle_slide;
  bool toggle_bank;

  //	this is for weapon control
  int fire_primary_down_count;
  bool fire_primary_down_state;
  float fire_primary_down_time;
  int fire_secondary_down_count;
  bool fire_secondary_down_state;
  float fire_secondary_down_time;

  // The flare
  int fire_flare_down_count;
  int rearview_down_count;
  bool rearview_down_state;
};

//	This value should be set at initialization time.  Use for remote controlling.
extern char *Controller_ip;

//	Controller object.
extern gameController *Controller;

// determines if controller is being polled.
extern bool Control_poll_flag;

//
extern ct_function Controller_needs[NUM_CONTROLLER_FUNCTIONS];

//	initializes control system
void InitControls();
void CloseControls();

//	polls controller at a certain framerate.
void PollControls();

//	suspends and or resumes the control system.  this deactivates or reactivates any
//	preemptive controller polling we setup.
void SuspendControls();
void ResumeControls();

// Read the keyboard & other controllers.  Fills in the specified structure.
void ReadPlayerControls(game_controls *controls);

//	reinits the controller, hence restoring default controller configurations
void RestoreDefaultControls();

//	load in controller configurations
void LoadControlConfig(pilot *plt = NULL);

//	save controller configurations.
void SaveControlConfig(pilot *plt = NULL);

// Reads movement only
void DoMovement(game_controls *controls);

#endif
