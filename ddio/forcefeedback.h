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

 * $Logfile: /DescentIII/Main/lib/forcefeedback.h $
 * $Revision: 15 $
 * $Date: 7/28/99 3:23p $
 * $Author: Kevin $
 *
 * Low-Level ForceFeedback header
 *
 * $Log: /DescentIII/Main/lib/forcefeedback.h $
 *
 * 15    7/28/99 3:23p Kevin
 * Macintosh
 *
 * 14    4/16/99 8:28p Jeff
 * moved placement of #endif
 *
 * 13    4/15/99 1:44a Jeff
 * changes for linux compile
 *
 * 12    1/30/99 11:27p Jeff
 * added immersion support
 *
 * 11    1/28/99 12:09p Jeff
 * added force feedback to player shake...fixed spelling error in define
 * for forcefeedback
 *
 * 10    1/13/99 6:48a Jeff
 * made file linux friendly (removed dinput specific stuff to ifdef)
 *
 * 8     11/10/98 5:16p Jeff
 * updated forcefeedback system...pretty complete now
 *
 * 7     11/06/98 7:00p Jeff
 * first round of new force feedback installed
 *
 * 6     11/03/98 6:43p Jeff
 * new low-level & high level Force Feedback system implemented, handles
 * window losing focus, etc.
 *
 * 5     10/12/98 3:49p Jeff
 * struct changes
 *
 * 4     9/21/98 11:10a Jeff
 * general update, new low level, small high level implementation
 *
 * 3     9/18/98 7:38p Jeff
 * creation of low-level forcefeedback and beginning of high-level
 * forcefeedback
 *
 * 2     9/15/98 12:05p Jeff
 * initial creation of low-level forcefeedback
 *
 * $NoKeywords: $
 */
#ifndef __DDIO_FORCEFEEDBACK_H_
#define __DDIO_FORCEFEEDBACK_H_
#include <cstdint>
#include "pstypes.h"
#include "string.h"
#define kMAX_Str 80
#define kInfinite_Duration 0xFFFFFF
#define FF_USEENVELOPE 0x01
#define HZ_to_uS(hz) ((int)(1000000.0 / (double)(hz) + 0.5))
#define DDIO_FF_MAXEFFECTS 30
#if defined(WIN32)
// WINDOWS
#include "win/DirectX/dinput.h"
#define FF_DEGREES DI_DEGREES
#define FF_NOMINALMAX DI_FFNOMINALMAX
#define FF_SECONDS DI_SECONDS
#else
#define FF_DEGREES 360      // fake value
#define FF_NOMINALMAX 10000 // fake value
#define FF_SECONDS 1000     // fake value
#endif
#define FORCEPROJECT void *
enum tDevice {
  kJoy1 = 0,
  kJoy2,
  kJoy3,
  kJoy4,
  kJoy5,
  kJoy6,
  kJoy7,
  kJoy8,
  kJoy9,
  kJoy10,
  kJoy11,
  kJoy12,
  kJoy13,
  kJoy14,
  kJoy15,
  kJoy16,
  kMaxJoy,
  kMouse,
  kKeyBoard,
  kAllDevices
};
enum tJoyButtons {
  kNoButton = -1,
  kButton0 = 0,
  kButton1,
  kButton2,
  kButton3,
  kButton4,
  kButton5,
  kButton6,
  kButton7,
  kButton8,
  kButton9,
  kButton10,
  kButton31 = 31,
  kButtonMax
};
enum tDeviceMask {
  kStick = 1 << 0,
  kWheel = 1 << 1,
  kGamePad = 1 << 2,
};
struct tFFJoyInfo {
  int ButtonMask;
  int AxisMask;
  tDeviceMask DevType;
  char Name[kMAX_Str];
};
enum tLoadEffect {
  kDontPlayNow = 0,
  kPlayNow,
  kPlayNowIfModified,
};
enum tEffType {
  kConstant = 0,
  kRamp,
  kCustom,
  kWave_Square,
  kWave_Sine,
  kWave_Triangle,
  kWave_SawUp,
  kWave_SawDown,
  kCondition_Spring,
  kCondition_Damper,
  kCondition_Inertia,
  kCondition_Friction,
  kMaxEffectSubTypes
};
struct tEffConstant {
  int32_t Mag; // +- 10,000
};
struct tEffRamp {
  int32_t Start; // +- 10,000
  int32_t End;   // +- 10,000
};
struct tEffWave {
  uint32_t Mag;   // 0 to 10,000
  int32_t Offset;         // +- 10,000
  uint32_t Phase; // 0 to 35,999
  uint32_t Period;
};
struct tEffCondition {
  int32_t Offset;                      // +- 10,000
  int32_t PositiveCoefficient;         // +- 10,000
  int32_t NegativeCoefficient;         // +- 10,000
  uint32_t PositiveSaturation; // 0 to 10,000
  uint32_t NegativeSaturation; // 0 to 10,000
  int32_t DeadBand;                    // 0 to 10,000
};
struct tEffCustom {
  int Channels;
  int Period;
  int Samples;
  int32_t *ForceData;
};
union tEffInfo {
  tEffConstant Constant;
  tEffRamp Ramp;
  tEffWave Wave;
  tEffCondition Condition;
  tEffCustom Custom;
};
struct tEffEnvelope {
  uint32_t AttackLevel;
  uint32_t AttackTime;
  uint32_t FadeLevel;
  uint32_t FadeTime;
};
enum tEffAxis { kXAxisOnly, kYAxisOnly, kBothAxes };
struct tFFB_Effect {
  int Flags;
  tEffType Type;
  // tEffInfo			TypeInfo[2];
  tEffInfo TypeInfo;
  uint32_t Duration;
  uint32_t Gain; // 0-10000 -- scales all magnitudes and envelope
  uint32_t Period;
  tEffAxis Axis;
  tJoyButtons Trigger;
  uint32_t TriggerRepeatTime;
  int32_t Direction; // 0 to 360 deg.
  tEffEnvelope Envelope;
};
extern bool ddForce_found;   // a Force Feedback device was found
extern bool ddForce_enabled; // Force Feedback is ready and can be used
// ===================================================================
//									Function Prototypes
// ===================================================================
// -------------------------------------------------------------------
//	ddio_ff_AttachForce
//	Purpose:
//		Attaches variables initialized in the general ddio system to
//	the force feedback system.
// -------------------------------------------------------------------
void ddio_ff_AttachForce(void);
// -------------------------------------------------------------------
//	ddio_ff_DetachForce
//	Purpose:
//		Detaches variables used by the force-feedback system from the
//	ddio system
// -------------------------------------------------------------------
void ddio_ff_DetachForce(void);
// -------------------------------------------------------------------
// ddio_ff_Init
// Purpose:
//    Initialize force feedback if available.
// -------------------------------------------------------------------
int ddio_ff_Init(void);
// -------------------------------------------------------------------
// ddio_ffjoy_Init
// Purpose:
//    Creates and acquires all joysticks
//
// Input:
//    None
//
// Return:
//    # of sticks acquired
//
// Description:
//
// -------------------------------------------------------------------
int ddio_ffjoy_Init(void);
// -------------------------------------------------------------------
// ddio_ff_Acquire
// Purpose:
//    Acquires a direct input device for use.
//
// Input:
//    The device to acquire (use kDI_MaxJoy to acquire all available
//    joysticks).
//
// Return:
//    # of devices acquired.
//
// Description:
//    Call this to gain access to a device after the device has been
//    created & after regaining the focus after losing it.
//
// -------------------------------------------------------------------
int ddio_ff_Acquire(tDevice dev);
// -------------------------------------------------------------------
// ddio_ff_Unacquire
// Purpose:
//    Unacquires a direct input device
//
// Input:
//    The device to unacquire (use kDI_MaxJoy to unacquire all available
//    joysticks).
//
// Return:
//    # of devices unacquired.
//
// Description:
//    Call this to lose access to a device after the device has been
//    aquired
//
// -------------------------------------------------------------------
int ddio_ff_Unacquire(tDevice dev);
// -------------------------------------------------------------------
// ddio_ff_SetCoopLevel
// -------------------------------------------------------------------
static int ddio_ff_SetCoopLevel(tDevice dev, int coop_level);
// -------------------------------------------------------------------
// ddio_ffjoy_Query
// Purpose:
//    Besides checking what buttons/axis are available, this function
//    also checks for force feedback support.
// -------------------------------------------------------------------
int ddio_ffjoy_Query(int dev, int *but_flags, int *axis_flags);
/*
========================================================================
                                Force Feedback Effect Functions
========================================================================
*/
// -------------------------------------------------------------------
//	ddio_ff_GetInfo
//	Purpose:
//		Returns information about the current state of the low-level
//	Force Feedback system.
// -------------------------------------------------------------------
void ddio_ff_GetInfo(bool *ff_found, bool *ff_enabled);
// -------------------------------------------------------------------
// ddio_ffb_Pause
// Purpose:
//    Pause the FFB output on the given device.  Use ddio_ffb_Continue to
//    continue where you left off.
// -------------------------------------------------------------------
void ddio_ffb_Pause(tDevice dev);
// -------------------------------------------------------------------
// ddio_ffb_Continue
// Purpose:
//    Unpause the FFB output on the given device.  Complimentary to
//    ddio_ffb_Pause.
// -------------------------------------------------------------------
void ddio_ffb_Continue(tDevice dev);
// -------------------------------------------------------------------
// ddio_ffb_Enable
// Purpose:
//    Must be called after initialization in order to activate the
//    device.
//    Use ddio_ffb_Pause & ddio_ffb_Continue if you want disable forces
//    temporarily and resume later.
// -------------------------------------------------------------------
void ddio_ffb_Enable(tDevice dev);
// -------------------------------------------------------------------
// ddio_ffb_Disable
// Purpose:
//    Turns off FFB, but effects still play on processor.
// -------------------------------------------------------------------
void ddio_ffb_Disable(tDevice dev);
// -------------------------------------------------------------------
// ddio_ffb_effectCreate
// Purpose:
//    Create a single effect for future playback.
//    Effect is given a logical ID
// -------------------------------------------------------------------
int ddio_ffb_effectCreate(tDevice dev, tFFB_Effect *eff);
// -------------------------------------------------------------------
// ddio_ffb_DestroyAll
//	Purpose:
//		Destroys all created effects
// -------------------------------------------------------------------
void ddio_ffb_DestroyAll(void);
// -------------------------------------------------------------------
// ddio_ffb_effectPlay
// Purpose:
//    Play an effect that was previously created.
// -------------------------------------------------------------------
void ddio_ffb_effectPlay(int16_t eID);
// -------------------------------------------------------------------
// ddio_ffb_effectStop
// Purpose:
//    Stop a single effect.
// -------------------------------------------------------------------
void ddio_ffb_effectStop(int16_t eID);
// -------------------------------------------------------------------
// ddio_ffb_effectStopAll
// Purpose:
//    Stops all forces on the given device.
// -------------------------------------------------------------------
void ddio_ffb_effectStopAll(tDevice dev);
// -------------------------------------------------------------------
// ddio_ffb_effectUnload
// Purpose:
//    Unload a single effect...  Necessary to make room for other
//    effects.
// -------------------------------------------------------------------
void ddio_ffb_effectUnload(int16_t eID);
// -------------------------------------------------------------------
// ddio_ffb_effectModify
// Purpose:
//    Modifies a single effect, only if the given parameters are
//    different from what's currently loaded.
// -------------------------------------------------------------------
void ddio_ffb_effectModify(int16_t eID, int *Direction, uint32_t *Duration, uint32_t *Gain, uint32_t *Period,
                           tEffInfo *TypeInfo, tEffEnvelope *Envelope);
// -------------------------------------------------------------------
// ddio_ffb_GetEffectData
// Purpose:
//    Retrieves affect data for the given parameters, pass NULL for those you don't want
// -------------------------------------------------------------------
void ddio_ffb_GetEffectData(int16_t eID, int *Direction, uint32_t *Duration, uint32_t *Gain, uint32_t *Period,
                            tEffInfo *TypeInfo, tEffEnvelope *Envelope);
// -------------------------------------------------------------------
// ddio_ffjoy_EnableAutoCenter
// Purpose:
//	Disables/Enables the autocentering of the joystick
// -------------------------------------------------------------------
void ddio_ffjoy_EnableAutoCenter(tDevice dev, bool enable);
// -------------------------------------------------------------------
// ddio_ffjoy_SetGain
// Purpose:
//	Sets the gain for joystick, pass a value of 0-1
// -------------------------------------------------------------------
void ddio_ffjoy_SetGain(tDevice dev, float value);
// -------------------------------------------------------------------
// ddio_ffjoy_IsAutoCentered
// Purpose:
//	Returns true if the joystick is set for autocentering
// -------------------------------------------------------------------
bool ddio_ffjoy_IsAutoCentered(tDevice dev);
// -------------------------------------------------------------------
// ddio_ffjoy_SupportAutoCenter
// Purpose:
//	Returns true if the FF joystick supports auto centering
// -------------------------------------------------------------------
bool ddio_ffjoy_SupportAutoCenter(tDevice dev);
/*
===========================================================================
                        Private Functions
===========================================================================
*/
#if defined(WIN32)
// -------------------------------------------------------------------
// ddio_ffjoy_AcquireErr
// Purpose:
//    Handle success/err reporting
// -------------------------------------------------------------------
static int ddio_ffjoy_AcquireErr(HRESULT res, int dev_num);
// -------------------------------------------------------------------
// FFEnumCallback
// Purpose:
//    Initialize all connected joysticks.
//
// Input:
//    pdinst   info about the current joystick being enumed.
//    pvRef    the direct input object that was passed in before
//             starting the enum process.
// Return:
//   DIENUM_CONTINUE    continue calling us with any more devices
//   DIENUM_STOP        all done, don't call us back anymore, go away.
// -------------------------------------------------------------------
BOOL CALLBACK FFEnumCallback(LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef);
#endif
//	Given a filename resource, this loads the file and creates a resource
//	for it.  It returns a handle to that resource.
//	If it returns NULL, then it couldn't load the project.
//	Make sure device is aquired before calling.
FORCEPROJECT ddio_ForceLoadProject(char *filename, tDevice dev);
//	Unloads a FORCEPROJECT file
void ddio_ForceUnloadProject(FORCEPROJECT prj);
//	Given a handle to a resource, and the name of the effect to load
//	it will load that effect.  Returns the effect ID, or -1 if it couldn't
//	be created
int ddio_CreateForceFromProject(FORCEPROJECT project, const char *forcename);
#endif
