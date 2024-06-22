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

 * $Logfile: /DescentIII/Main/ddio_win/winforcefeedback.cpp $
 * $Revision: 19 $
 * $Date: 4/09/99 12:02p $
 * $Author: Samir $
 *
 * Low-level force feedback
 *
 * $Log: /DescentIII/Main/ddio_win/winforcefeedback.cpp $
 *
 * 19    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 18    3/28/99 5:53p Jeff
 * fixed iforce crashes
 *
 * 17    3/11/99 5:52p Jeff
 * always compile in immersion support
 *
 * 16    1/31/99 11:11p Jeff
 * made immersion support as a dynamically loadable dll, and compiled in
 * by default
 *
 * 15    1/30/99 11:27p Jeff
 * added immersion support
 *
 * 14    1/28/99 12:09p Jeff
 * added force feedback to player shake...fixed spelling error in define
 * for forcefeedback
 *
 * 13    11/18/98 5:50p Jeff
 * added some cheap recoil effects for ForceFeedback...not fully
 * implemented
 *
 * 12    11/10/98 5:16p Jeff
 * updated forcefeedback system...pretty complete now
 *
 * 11    11/06/98 7:00p Jeff
 * first round of new force feedback installed
 *
 * 10    11/03/98 6:43p Jeff
 * new low-level & high level Force Feedback system implemented, handles
 * window losing focus, etc.
 *
 * 9     11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 8     10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 7     10/12/98 3:49p Jeff
 * struct changes
 *
 * 6     10/02/98 12:04p Jeff
 * fixed forcefeedback bug if it couldn't disable autocenter
 *
 * 5     9/22/98 3:55p Samir
 * ifdef out stuff for non-debug version.
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

#if 0

#include <cstdarg>
#include <cstdio>

#include <stdlib.h>
#include <math.h>

#include "pserror.h"
#include "mono.h"
#include "ddio.h"
#include "ddio_win.h"
#include "application.h"
#include "forcefeedback.h"
#include "mem.h"
#include "dinput.h"

//#include "iforce2.h"

void ddio_LoadImmersionDLL(void);
void ddio_FreeImmersionDLL(void);


void PrintDirectInputErrorString( HRESULT hr,const char *format, ... );

#define DDIO_JOY_COOP_FLAGS (DISCL_EXCLUSIVE | DISCL_BACKGROUND)

bool ddForce_found = false;	//a Force Feedback device was found
bool ddForce_enabled = false;	//Force Feedback is ready and can be used


// Force Feedback Effect Data
// --------------------------
const GUID *effectGUID[kMaxEffectSubTypes] =	{
	&GUID_ConstantForce,
	&GUID_RampForce,   
	&GUID_CustomForce, 
	// period
	&GUID_Square,
	&GUID_Sine,
	&GUID_Triangle,    
	&GUID_SawtoothUp,  
	&GUID_SawtoothDown,
	// condition
	&GUID_Spring,
	&GUID_Damper,
	&GUID_Inertia,
	&GUID_Friction
};

union tEffectClasses {
	DICONSTANTFORCE   constant;
	DIRAMPFORCE       ramp;
	DIPERIODIC        period;
	DICONDITION       condition;
	DICUSTOMFORCE     custom;
};

struct tEffect {
	DIEFFECT       general;
	tEffectClasses specific;
	DIENVELOPE     envelope;
	LONG           direction[2];
}tddEffect;

static tddEffect                ddEffect[DDIO_FF_MAXEFFECTS];

// DInput Data
// -----------
static LPDIRECTINPUT          DI                   = NULL; 
static LPDIRECTINPUTDEVICE    DID1_Rat             = NULL;
static LPDIRECTINPUTDEVICE    DID1_Key             = NULL;
static LPDIRECTINPUTDEVICE2   DID2_Joy[kMaxJoy];
static LPDIRECTINPUTEFFECT    DIE_hEffect[DDIO_FF_MAXEFFECTS];

// Joystick Data
// -------------
static int           maskFFB                       = 0;
static int           numJoy                        = 0;
static int           numEffects                    = 0;
static char          isWheel[kMaxJoy];
static char          joyName[kMaxJoy][_MAX_PATH];
static DWORD         dwAxes[2]                     = { DIJOFS_X, DIJOFS_Y };

// Private Functions
// -----------------
BOOL CALLBACK FFEnumCallback(LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef);
static int		ddio_ffjoy_AcquireErr(HRESULT res, int dev_num);
static int		ddio_ffjoy_UnacquireErr(HRESULT res, int dev_num);

static int		ddio_ff_SetCoopLevel(tDevice dev, int coop_level);
int ddio_ffb_Init(void);

void *getwindowhandle(void)
{
	 return DInputData.hwnd;
}

/*
=====================================================================
=																	=
=			Device & Low-Level Driver Functions						=
=																	=
=====================================================================
*/

LPDIRECTINPUTDEVICE2 ddio_ff_get_joystick_obj(tDevice dev)
{
	return DID2_Joy[(int)dev];
}


// -------------------------------------------------------------------
//	ddio_ff_AttachForce
//	Purpose:
//		Attaches variables initialized in the general ddio system to
//	the force feedback system.
// -------------------------------------------------------------------
void ddio_ff_AttachForce(void)
{
	ddio_LoadImmersionDLL();

	for(int i=0;i<kMaxJoy;i++)
		DID2_Joy[i] = NULL;

	maskFFB  = 0;
	numJoy   = 0;
	DI = DInputData.lpdi;
	ddForce_enabled = ddForce_found = false;
}

// -------------------------------------------------------------------
//	ddio_ff_DetachForce
//	Purpose:
//		Detaches variables used by the force-feedback system from the
//	ddio system
// -------------------------------------------------------------------
void ddio_ff_DetachForce(void)
{
	int i;

	if(DI){
		// Release All Joystick Devices
		// ----------------------------
		for (i=0; i<kMaxJoy; i++){  
			if (DID2_Joy[i]){  
				IDirectInputDevice2_Unacquire(DID2_Joy[i]);
				IDirectInputDevice2_Release(DID2_Joy[i]);
				DID2_Joy[i] = NULL;
			}
		}
	}
	DI = NULL;
	DID1_Rat = NULL;
	DID1_Key = NULL;
	numEffects = 0;
	maskFFB  = 0;
	numJoy   = 0;
	ddForce_enabled = ddForce_found = false;

	ddio_FreeImmersionDLL();
}

// -------------------------------------------------------------------
// ddio_ff_Init
// Purpose:
//    Initialize force feedback if available.
// -------------------------------------------------------------------
int ddio_ff_Init(void)
{
	if (!numJoy)
		ddio_ffjoy_Init();

	if (maskFFB){
		int i;  
		for (i=kJoy1; i<kMaxJoy; i++){  
			if (DID2_Joy[i] && (maskFFB & (1<<i)))
				IDirectInputDevice2_SendForceFeedbackCommand(DID2_Joy[i],DISFFC_RESET);
		}

		ddForce_found = true;
		ddForce_enabled = true;
	}
	return maskFFB;
}

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
static BOOL (__stdcall *FF_CB_PTR)( LPCDIDEVICEINSTANCE,LPVOID);
int ddio_ffjoy_Init(void)
{
	// Make sure Main DInput OBJ has been created
	// ------------------------------------------ 
	if (!DI){
		ddio_ff_Init();
		
		if (!DI){
			mprintf(0,"ddio_ffjoy_Init: Dinput not initialized yet\n");
			return FALSE;
		}
	}

	// Don't do this if it's already successfully been done
	// ----------------------------------------------------
	if (!numJoy){
		int i;

		FF_CB_PTR = FFEnumCallback;
		DI->EnumDevices(DIDEVTYPE_JOYSTICK,FF_CB_PTR,DI,DIEDFL_ATTACHEDONLY);

		for (i=0; i<numJoy; i++){  
			ddio_ffjoy_Query(i, NULL, NULL);
		}
	}

	// Only attempt to acquire if a joy device is present
	// --------------------------------------------------
	if (numJoy)
		ddio_ff_Acquire(kMaxJoy);

   return(numJoy);
}

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
int ddio_ff_Acquire(tDevice dev)
{
	int i,cnt=0;

	if(DI){
		if (dev == kAllDevices){
			cnt += ddio_ff_Acquire(kMaxJoy);
			return cnt;
		}

		switch (dev){
		case kMaxJoy:
			{
				for (i=0; i<kMaxJoy; i++){
					if (DID2_Joy[i]){
						if (ddio_ffjoy_AcquireErr(IDirectInputDevice2_Acquire(DID2_Joy[i]),i))
							cnt++;
					}
				}
				return cnt;
            }break;
         default:
			 if (dev > kAllDevices){
				 mprintf(0,"ddio_ff_Acquire: Invalid device ID, out of range\n");
				 return 0;
			 }else{
				 if (DID2_Joy[dev]){
					 int ret = ddio_ffjoy_AcquireErr(IDirectInputDevice2_Acquire(DID2_Joy[dev]),dev);
					 return ret;
				 }
			 }break;
		}
	}else
		mprintf(0,"ddio_ff_Acquire: Direct Input object not initialized...\n");

	return cnt;
}

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
int ddio_ff_Unacquire(tDevice dev)
{
	int i,cnt=0;

	if(DI){
		if (dev == kAllDevices){
			cnt += ddio_ff_Unacquire(kMaxJoy);
			return cnt;
		}

		switch (dev){
		case kMaxJoy:
			{
				for (i=0; i<kMaxJoy; i++){
					if (DID2_Joy[i]){
						if (ddio_ffjoy_UnacquireErr(IDirectInputDevice2_Unacquire(DID2_Joy[i]),i))
							cnt++;
					}
				}
				return cnt;
            }break;
         default:
			 if (dev > kAllDevices){
				 mprintf(0,"ddio_ff_Unacquire: Invalid device ID, out of range\n");
				 return 0;
			 }else{
				 if (DID2_Joy[dev]){
					 int ret = ddio_ffjoy_UnacquireErr(IDirectInputDevice2_Unacquire(DID2_Joy[dev]),dev);
					 return ret;
				 }
			 }break;
		}
	}else
		mprintf(0,"ddio_ff_Unacquire: Direct Input object not initialized...\n");

	return cnt;
}


// -------------------------------------------------------------------
// ddio_ff_SetCoopLevel
// -------------------------------------------------------------------
static int ddio_ff_SetCoopLevel(tDevice dev, int coop_level)
{
	HWND hwin;

	if (!(hwin=(HWND)getwindowhandle()))
	{
		mprintf(0,"ddio_ff_SetCoopLevel: couldn't get window handle\n");
	}

	// Set a single joystick
	// ---------------------
	if (dev < kMaxJoy){
		if (DID2_Joy[dev]){
			// Set the cooperative level to share the device
			// ---------------------------------------------
			if (IDirectInputDevice2_SetCooperativeLevel(DID2_Joy[dev], (HWND)getwindowhandle(), coop_level)!= DI_OK){ 
				mprintf(0,"ddio_ff_SetCoopLevel: Could not set dinput device coop level\n");
				return 0; 
			}
		}
	}else// Set all single joysticks
		if (dev == kMaxJoy){
			int i;
			for (i=kJoy1; i<kMaxJoy; i++){
				ddio_ff_SetCoopLevel((tDevice)i, coop_level);
			}
		}

	return 1;
}

// -------------------------------------------------------------------
// DIEnumJoysticks_Callback
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

BOOL CALLBACK FFEnumCallback(LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef)
{
	LPDIRECTINPUT        pdi   = (LPDIRECTINPUT)pvRef;
	LPDIRECTINPUTDEVICE  pdev;

	if (DIDEVTYPEJOYSTICK_WHEEL == GET_DIDEVICE_SUBTYPE(pdinst->dwDevType))
		isWheel[numJoy] = TRUE;
	else
		isWheel[numJoy] = FALSE;

	// Create an instance of the device
	// --------------------------------   
	if (IDirectInput_CreateDevice(pdi, pdinst->guidInstance, &pdev, NULL)!= DI_OK){ 
		mprintf(0,"DIEnumJoysticks_Callback: Could not create dinput device obj\n");
		return DIENUM_CONTINUE; 
	}

	// Set the data format to the default
	// ---------------------------------- 
	if (IDirectInputDevice_SetDataFormat(pdev, &c_dfDIJoystick)!= DI_OK){ 
		mprintf(0,"DIEnumJoysticks_Callback: Could not set dinput device data format\n");
		IDirectInputDevice_Unacquire(pdev);
		IDirectInputDevice_Release (pdev); 
		return DIENUM_CONTINUE; 
	}

	// Get the DID2 from DID1 
	// ----------------------
	if (IDirectInputDevice_QueryInterface(pdev, IID_IDirectInputDevice2, (void **) &DID2_Joy[numJoy])!= DI_OK){
		mprintf(0,"DIEnumJoysticks_Callback: QueryInterface did not return DI_OK\n");
		IDirectInputDevice_Unacquire(pdev);
		IDirectInputDevice_Release (pdev);
		return DIENUM_CONTINUE; 
	}

	// Set the cooperative level 
	// -------------------------
	if (!ddio_ff_SetCoopLevel((tDevice)numJoy, DDIO_JOY_COOP_FLAGS)){
		mprintf(0,"DIEnumJoysticks_Callback: Could not set dinput coop level\n");
		return FALSE;
	}

	// Done with Device1
	// -----------------
	IDirectInputDevice_Unacquire(pdev);
	IDirectInputDevice_Release (pdev);

	// Device was added successfully
	// -----------------------------
	numJoy++;

	return DIENUM_CONTINUE;
}


// -------------------------------------------------------------------
// ddio_ffjoy_Query
// Purpose:
//    Besides checking what buttons/axis are available, this function
//    also checks for force feedback support.
// -------------------------------------------------------------------
int ddio_ffjoy_Query(int dev, int* but_flags, int* axis_flags)
{
	uint32_t                     i,bit;
	DIDEVCAPS               DICaps; 
	DIDEVICEOBJECTINSTANCE  DIObjInst; 
	DWORD                   DIAxisOFS[6] =			{	DIJOFS_X,
														DIJOFS_Y,
														DIJOFS_Z,
														DIJOFS_RX,
														DIJOFS_SLIDER(0),
														DIJOFS_SLIDER(1) };

	// Make sure Main DInput OBJ has been created
	// ------------------------------------------ 
	if (!DI){
		ddio_ff_Init();
		if (!DI){
			mprintf(0,"ddio_ffjoy_Query: Dinput not initialized yet\n");
			return FALSE;
		}
	}

	if (!DID2_Joy[dev]){
		mprintf(0,"ddio_ffjoy_Query: device not found #%d\n",dev);
		return 0;
	}

	if (!numJoy){
		if (but_flags)*but_flags=0;
		if (axis_flags)*axis_flags=0;
		return 0;
	}

	ddio_ff_Acquire((tDevice)dev);

	DICaps.dwSize = sizeof(DIDEVCAPS);

	if (IDirectInputDevice2_GetCapabilities(DID2_Joy[dev],&DICaps) != DI_OK){
		mprintf(0,"ddio_ffjoy_Query: Failed getting device caps\n");
		return 0;
	}

	if (DICaps.dwFlags & DIDC_FORCEFEEDBACK){
		mprintf(0,"ddio_ff_joy_Query: ffb support\n");
		maskFFB |= 1<<dev;
	}

	DIObjInst.dwSize = sizeof(DIDEVICEOBJECTINSTANCE); 

	// Get the Axis flags
	// ------------------
	if (but_flags){
		*but_flags = 0;

		for (i=0,bit=0; i<DICaps.dwButtons && bit < 32; bit++){
			if (IDirectInputDevice2_GetObjectInfo(DID2_Joy[dev],&DIObjInst,DIJOFS_BUTTON(bit), DIPH_BYOFFSET)== DI_OK){
				*but_flags |= 1<<bit;
				++i;
			}
		}
	}

	// Get the Axis flags
	// ------------------
	if (axis_flags){
		*axis_flags = 0;

		for (i=0,bit=0; i<DICaps.dwAxes && bit < 8; ++bit){
			if (IDirectInputDevice2_GetObjectInfo(DID2_Joy[dev],&DIObjInst,DIAxisOFS[bit], DIPH_BYOFFSET)== DI_OK){
				*axis_flags |= 1<<bit;
				++i;
			}
		}
	}

	return 1;
}


// -------------------------------------------------------------------
// ddio_ffjoy_EnableAutoCenter
// Purpose:
//	Disables/Enables the autocentering of the joystick
// -------------------------------------------------------------------
void ddio_ffjoy_EnableAutoCenter(tDevice dev,bool enable)
{
	DIPROPDWORD DIPropAutoCenter;
	DIPropAutoCenter.diph.dwSize = sizeof(DIPropAutoCenter);
	DIPropAutoCenter.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	DIPropAutoCenter.diph.dwObj = 0;  
	DIPropAutoCenter.diph.dwHow = DIPH_DEVICE;

	DIPropAutoCenter.dwData = (enable)?DIPROPAUTOCENTER_ON:DIPROPAUTOCENTER_OFF; 

	if (dev >= kMaxJoy){
		return;
	}

	if (DID2_Joy[dev] && (maskFFB & 1<<dev)){
		ddio_ff_Unacquire(dev);
		HRESULT hr = DID2_Joy[dev]->SetProperty(DIPROP_AUTOCENTER,&DIPropAutoCenter.diph);
		ddio_ff_Acquire(dev);
		
		if (FAILED(hr)){
			PrintDirectInputErrorString(hr,"Force: Failed to change autocenter property.");
		} 
	}
}

// -------------------------------------------------------------------
// ddio_ffjoy_SetGain
// Purpose:
//	Sets the gain for joystick, pass a value of 0-1
// -------------------------------------------------------------------
void ddio_ffjoy_SetGain(tDevice dev,float value)
{
	DIPROPDWORD DIPropAutoCenter;
	DIPropAutoCenter.diph.dwSize = sizeof(DIPropAutoCenter);
	DIPropAutoCenter.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	DIPropAutoCenter.diph.dwObj = 0;  
	DIPropAutoCenter.diph.dwHow = DIPH_DEVICE;

	DIPropAutoCenter.dwData = (DWORD)(value*10000.0f);

	if (dev >= kMaxJoy){
		return;
	}

	if (DID2_Joy[dev] && (maskFFB & 1<<dev)){
		HRESULT hr = DID2_Joy[dev]->SetProperty(DIPROP_FFGAIN ,&DIPropAutoCenter.diph);
		
		if (FAILED(hr)){
			PrintDirectInputErrorString(hr,"Force: Failed to set gain.");
		} 
	}
}

// -------------------------------------------------------------------
// ddio_ffjoy_IsAutoCentered
// Purpose:
//	Returns true if the joystick is set for autocentering
// -------------------------------------------------------------------
bool ddio_ffjoy_IsAutoCentered(tDevice dev)
{
	DIPROPDWORD DIPropAutoCenter;
	DIPropAutoCenter.diph.dwSize = sizeof(DIPropAutoCenter);
	DIPropAutoCenter.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	DIPropAutoCenter.diph.dwObj = 0;  
	DIPropAutoCenter.diph.dwHow = DIPH_DEVICE;

	if (dev >= kMaxJoy){
		return false;
	}

	if (DID2_Joy[dev] && (maskFFB & 1<<dev)){
		ddio_ff_Unacquire(dev);
		HRESULT hr = DID2_Joy[dev]->GetProperty(DIPROP_AUTOCENTER,&DIPropAutoCenter.diph);
		ddio_ff_Acquire(dev);

		if (FAILED(hr)){
			PrintDirectInputErrorString(hr,"Force: Failed to get autocenter property");
			return false;
		} 
		return (DIPropAutoCenter.dwData)?true:false;
	}
	return false;	
}

// -------------------------------------------------------------------
// ddio_ffjoy_SupportAutoCenter
// Purpose:
//	Returns true if the FF joystick supports auto centering
// -------------------------------------------------------------------
bool ddio_ffjoy_SupportAutoCenter(tDevice dev)
{
	if (dev >= kMaxJoy){
		return false;
	}

	if (DID2_Joy[dev] && (maskFFB & 1<<dev)){
		//check this device
		bool set = ddio_ffjoy_IsAutoCentered(dev);

		DIPROPDWORD DIPropAutoCenter;
		DIPropAutoCenter.diph.dwSize = sizeof(DIPropAutoCenter);
		DIPropAutoCenter.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		DIPropAutoCenter.diph.dwObj = 0;  
		DIPropAutoCenter.diph.dwHow = DIPH_DEVICE;
		DIPropAutoCenter.dwData = (set)?DIPROPAUTOCENTER_ON:DIPROPAUTOCENTER_OFF; 


		ddio_ff_Unacquire(dev);
		HRESULT hr = DID2_Joy[dev]->SetProperty(DIPROP_AUTOCENTER,&DIPropAutoCenter.diph);
		ddio_ff_Acquire(dev);

		switch(hr){
		case DI_OK:
		case S_FALSE:
			return true;
		default:
			PrintDirectInputErrorString(hr,"");
			return false;
		}
	}

	return false;
}

/*
=============================================================================
=																			=
=			Force Feedback Effect Functions									=
=																			=
=============================================================================
*/

// -------------------------------------------------------------------
//	ddio_ff_GetInfo
//	Purpose:
//		Returns information about the current state of the low-level
//	Force Feedback system.
// -------------------------------------------------------------------
void ddio_ff_GetInfo(bool *ff_found,bool *ff_enabled)
{
	if(ddForce_found){
		if(ff_found)
			*ff_found = true;
		if(ff_enabled)
			*ff_enabled = ddForce_enabled;

	}else{
		if(ff_found)
			*ff_found = false;
		if(ff_enabled)
			*ff_enabled = false;
	}
}


// -------------------------------------------------------------------
// ddio_ffb_Pause
// Purpose:
//    Pause the FFB output on the given device.  Use ddio_ffb_Continue to
//    continue where you left off.
// -------------------------------------------------------------------
void ddio_ffb_Pause(tDevice dev)
{
	if (dev == kMaxJoy){
		int i;
		for (i=0; i<kMaxJoy; i++){  
			ddio_ffb_Pause((tDevice)i);
		}
		return;
	}

	if (DID2_Joy[dev] && (maskFFB & 1<<dev))
		IDirectInputDevice2_SendForceFeedbackCommand(DID2_Joy[dev],DISFFC_PAUSE);
}
   
// -------------------------------------------------------------------
// ddio_ffb_Continue
// Purpose:
//    Unpause the FFB output on the given device.  Complimentary to
//    ddio_ffb_Pause.
// -------------------------------------------------------------------
void ddio_ffb_Continue(tDevice dev)
{
	if (dev == kMaxJoy){
		int i;
		for (i=0; i<kMaxJoy; i++){  
			ddio_ffb_Continue((tDevice)i);
		}
		return;
	}

	if (DID2_Joy[dev] && (maskFFB & 1<<dev))
		IDirectInputDevice2_SendForceFeedbackCommand(DID2_Joy[dev],DISFFC_CONTINUE);
}

// -------------------------------------------------------------------
// ddio_ffb_Enable
// Purpose:
//    Must be called after initialization in order to activate the 
//    device.
//    Use ddio_ffb_Pause & ddio_ffb_Continue if you want disable forces
//    temporarily and resume later.
// -------------------------------------------------------------------
void ddio_ffb_Enable(tDevice dev)
{
	if (DID2_Joy[dev] && (maskFFB & 1<<dev)){
		IDirectInputDevice2_SendForceFeedbackCommand(DID2_Joy[dev],DISFFC_SETACTUATORSON);
		ddForce_enabled = true;
	}
}

// -------------------------------------------------------------------
// ddio_ffb_Disable
// Purpose:
//    Turns off FFB, but effects still play on processor.
// -------------------------------------------------------------------
void ddio_ffb_Disable(tDevice dev)
{
	if (DID2_Joy[dev] && (maskFFB & 1<<dev)){
		ddForce_enabled = false;
		IDirectInputDevice2_SendForceFeedbackCommand(DID2_Joy[dev],DISFFC_SETACTUATORSOFF);
	}
}

// -------------------------------------------------------------------
// ddio_ffb_DestroyAll
//	Purpose:
//		Destroys all created effects
// -------------------------------------------------------------------
void ddio_ffb_DestroyAll(void)
{
	numEffects = 0;
}

// -------------------------------------------------------------------
// ddio_ffb_effectCreate
// Purpose:
//    Create a single effect for future playback.
//    Effect is given a logical ID
// -------------------------------------------------------------------
int ddio_ffb_effectCreate(tDevice dev, tFFB_Effect* eff)
{
	HRESULT hr;

	if (numEffects >= DDIO_FF_MAXEFFECTS){
		mprintf(0,"ddio_ffb_effectCreate: Reached hardcoded limit for # of effects.\n");
		return -1;
	}

	if (!(DID2_Joy[dev] && (maskFFB & 1<<dev)) )
		return(-1);

	// Important stuff
	ddEffect[numEffects].general.dwDuration              = eff->Duration;
	ddEffect[numEffects].general.dwSamplePeriod          = eff->Period;
	ddEffect[numEffects].general.dwGain                  = eff->Gain;
	ddEffect[numEffects].general.dwTriggerButton         = (eff->Trigger==kNoButton?DIEB_NOTRIGGER:DIJOFS_BUTTON(eff->Trigger));
	ddEffect[numEffects].general.dwTriggerRepeatInterval = eff->TriggerRepeatTime;
	ddEffect[numEffects].direction[0]                    = eff->Direction;
	memcpy(&ddEffect[numEffects].specific,&eff->TypeInfo,sizeof(tEffectClasses));

	// COM related
	ddEffect[numEffects].general.dwSize                  = sizeof(DIEFFECT); 
	ddEffect[numEffects].general.cAxes                   = isWheel[dev]?1:2; 
	ddEffect[numEffects].general.rgdwAxes                = &dwAxes[0]; 
	ddEffect[numEffects].general.dwFlags                 = DIEFF_POLAR | DIEFF_OBJECTOFFSETS; 
	ddEffect[numEffects].general.lpvTypeSpecificParams   = &ddEffect[numEffects].specific;  
	ddEffect[numEffects].general.rglDirection            = (LONG *)ddEffect[numEffects].direction;
	ddEffect[numEffects].direction[1]                    = 0L;
	ddEffect[numEffects].general.lpEnvelope              = NULL;

	if(eff->Flags&FF_USEENVELOPE){
		ddEffect[numEffects].envelope.dwSize			 = sizeof(DIENVELOPE);
		ddEffect[numEffects].envelope.dwAttackLevel		 = eff->Envelope.AttackLevel;
		ddEffect[numEffects].envelope.dwAttackTime		 = eff->Envelope.AttackTime;
		ddEffect[numEffects].envelope.dwFadeLevel		 = eff->Envelope.FadeLevel;
		ddEffect[numEffects].envelope.dwFadeTime		 = eff->Envelope.FadeTime;
		ddEffect[numEffects].general.lpEnvelope			 = &ddEffect[numEffects].envelope;
	}


	switch (eff->Type){
    case kConstant:
		ddEffect[numEffects].general.cbTypeSpecificParams    = sizeof(DICONSTANTFORCE);
		break;
	case kRamp:
		ddEffect[numEffects].general.cbTypeSpecificParams    = sizeof(DIRAMPFORCE);
		break;
    case kCustom:
        ddEffect[numEffects].general.cbTypeSpecificParams    = sizeof(DICUSTOMFORCE);
		break;
	case kWave_Square:
	case kWave_Sine:
	case kWave_Triangle:
	case kWave_SawUp:
	case kWave_SawDown:
        ddEffect[numEffects].general.cbTypeSpecificParams    = sizeof(DIPERIODIC);
		break;
	case kCondition_Spring:
	case kCondition_Damper:
	case kCondition_Inertia:
	case kCondition_Friction:
		ddEffect[numEffects].general.cbTypeSpecificParams    = sizeof(DICONDITION);
		break;
	default:
		mprintf(0,"ddio_ffb_effectCreate: bad effect subType\n");
		return -1;
	}

	hr=IDirectInputDevice2_CreateEffect(	DID2_Joy[dev], 
											*effectGUID[eff->Type], 
											(LPCDIEFFECT)           &ddEffect[numEffects], 
											(LPDIRECTINPUTEFFECT*)  &DIE_hEffect[numEffects], 0);

	switch (hr){
	case DI_OK:
		ddio_ffb_effectUnload(numEffects);
		numEffects++;
		return (numEffects-1);
	case DIERR_DEVICENOTREG:
		mprintf(0,"ddio_ffb_effectCreate: effect not created, DIERR_DEVICENOTREG\n");
		return -1;
	case DIERR_DEVICEFULL:
		mprintf(0,"ddio_ffb_effectCreate: effect not created, DIERR_DEVICEFULL\n");
		return -1;
	default:
		PrintDirectInputErrorString(hr,"Force Effect Create");
		break;
	}
	return -1;
}

// -------------------------------------------------------------------
// ddio_ffb_effectPlay
// Purpose:
//    Play an effect that was previously created.
// -------------------------------------------------------------------
void ddio_ffb_effectPlay(int16_t eID)
{
	if(eID<0 || eID>=DDIO_FF_MAXEFFECTS){
		Int3();	//invalid eID
		return;
	}
	bool try_again = true;

ff_try:
	HRESULT hr = IDirectInputEffect_Start(DIE_hEffect[eID],1,0);


	if(FAILED(hr)){
		PrintDirectInputErrorString(hr,"Force Play");
		if(try_again){
			ddio_ff_Acquire(kMaxJoy);
			try_again = false;
			goto ff_try;
		}			
	}

}

// -------------------------------------------------------------------
// ddio_ffb_effectStop
// Purpose:
//    Stop a single effect.
// -------------------------------------------------------------------
void ddio_ffb_effectStop(int16_t eID)
{
	if(eID<0 || eID>=DDIO_FF_MAXEFFECTS){
		Int3();	//invalid eID
		return;
	}

	IDirectInputEffect_Stop(DIE_hEffect[eID]);
}

// -------------------------------------------------------------------
// ddio_ffb_effectStopAll
// Purpose:
//    Stops all forces on the given device.
// -------------------------------------------------------------------
void ddio_ffb_effectStopAll(tDevice dev)
{
	if (DID2_Joy[dev] && (maskFFB & 1<<dev) )
		IDirectInputDevice2_SendForceFeedbackCommand(DID2_Joy[dev],DISFFC_STOPALL);
}

// -------------------------------------------------------------------
// ddio_ffb_effectUnload
// Purpose:
//    Unload a single effect...  Necessary to make room for other
//    effects.
// -------------------------------------------------------------------
void ddio_ffb_effectUnload(int16_t eID)
{
	if(eID<0 || eID>=DDIO_FF_MAXEFFECTS){
		Int3();	//invalid eID
		return;
	}
	IDirectInputEffect_Unload(DIE_hEffect[eID]);
}


// -------------------------------------------------------------------
// ddio_ffb_effectModify
// Purpose:
//    Modifies a single effect, only if the given parameters are
//    different from what's currently loaded.
// -------------------------------------------------------------------
void ddio_ffb_effectModify(int16_t eID, int*	Direction, uint32_t* Duration, uint32_t* Gain, uint32_t* Period, tEffInfo* TypeInfo, tEffEnvelope* Envelope)
{
	uint32_t flags = 0;
	
	//return;

	if (Direction){
		if (ddEffect[eID].direction[0] != *Direction){
			ddEffect[eID].direction[0] = *Direction;
			flags |= DIEP_DIRECTION;
		}
	}

	if (Duration){
		if (ddEffect[eID].general.dwDuration != *Duration){
			ddEffect[eID].general.dwDuration = *Duration;
			flags |= DIEP_DURATION;
		}
	}

   if (Gain){
	   if (ddEffect[eID].general.dwGain != *Gain){
		   ddEffect[eID].general.dwGain = *Gain;
		   flags |= DIEP_GAIN;
	   }
   }

   if (Period){
      if (ddEffect[eID].general.dwSamplePeriod != *Period){
		  ddEffect[eID].general.dwSamplePeriod = *Period;
		  flags |= DIEP_SAMPLEPERIOD;
      }
   }

   if (TypeInfo){
	   if (!memcmp( &ddEffect[eID].specific, TypeInfo, ddEffect[eID].general.cbTypeSpecificParams)){
		   memcpy( &ddEffect[eID].specific, TypeInfo, ddEffect[eID].general.cbTypeSpecificParams);
		   flags |= DIEP_TYPESPECIFICPARAMS;
	   }
   }

   if (Envelope){
	   if (ddEffect[eID].envelope.dwAttackLevel != Envelope->AttackLevel ||
		   ddEffect[eID].envelope.dwAttackTime  != Envelope->AttackTime  ||
		   ddEffect[eID].envelope.dwFadeLevel   != Envelope->FadeLevel   ||
		   ddEffect[eID].envelope.dwFadeTime    != Envelope->FadeTime     ){
		   ddEffect[eID].envelope.dwAttackLevel  = Envelope->AttackLevel;
		   ddEffect[eID].envelope.dwAttackTime   = Envelope->AttackTime;
		   ddEffect[eID].envelope.dwFadeLevel    = Envelope->FadeLevel;
		   ddEffect[eID].envelope.dwFadeTime     = Envelope->FadeTime;
		   flags |= DIEP_ENVELOPE;
	   }
   }
   
   if (!flags)
	   return;

   IDirectInputEffect_SetParameters(DIE_hEffect[eID], (LPCDIEFFECT)&ddEffect[eID], flags);
}

// -------------------------------------------------------------------
// ddio_ffb_GetEffectData
// Purpose:
//    Retrieves affect data for the given parameters, pass NULL for those you don't want
// -------------------------------------------------------------------
void ddio_ffb_GetEffectData(int16_t eID, int*	Direction, uint32_t* Duration, uint32_t* Gain, uint32_t* Period, tEffInfo* TypeInfo, tEffEnvelope* Envelope)
{
	if (Direction){
		*Direction = ddEffect[eID].direction[0];
	}

	if (Duration){
		*Duration = ddEffect[eID].general.dwDuration;
	}

   if (Gain){
		*Gain = ddEffect[eID].general.dwGain;
   }

   if (Period){
		*Period = ddEffect[eID].general.dwSamplePeriod;
   }

   if (TypeInfo){
	   memcpy( TypeInfo,&ddEffect[eID].specific,ddEffect[eID].general.cbTypeSpecificParams);
   }

   if (Envelope){
	   Envelope->AttackLevel = ddEffect[eID].envelope.dwAttackLevel;
	   Envelope->AttackTime = ddEffect[eID].envelope.dwAttackTime;
	   Envelope->FadeLevel = ddEffect[eID].envelope.dwFadeLevel;
	   Envelope->FadeTime = ddEffect[eID].envelope.dwFadeTime;
   }
}


//====================================================================
//                     Private Fuctions
//====================================================================

// -------------------------------------------------------------------
// ddio_ffjoy_AcquireErr
// Purpose:
//    Handle success/err reporting
// -------------------------------------------------------------------
static int ddio_ffjoy_AcquireErr(HRESULT res, int dev_num)
{
	if (res == DI_OK){
		mprintf(0,"device #%d acquired\n",dev_num);
		return TRUE;
	}
	else
	if (res == S_FALSE){
		mprintf(0,"device #%d already acquired\n",dev_num);
		return TRUE;
	}
	else
	if (res == DIERR_INVALIDPARAM){
		mprintf(0,"device %d DIERR_INVALIDPARAM\n",dev_num);
		return FALSE;
	}
	else
	if (res == DIERR_OTHERAPPHASPRIO){
		mprintf(0,"device %d DIERR_OTHERAPPHASPRIO\n",dev_num);
		return TRUE;
	}
	else
		mprintf(0,"Unknown Error acquiring device %d\n",dev_num);
	
	return FALSE;
}

// -------------------------------------------------------------------
// ddio_ffjoy_UnacquireErr
// Purpose:
//    Handle success/err reporting
// -------------------------------------------------------------------
static int ddio_ffjoy_UnacquireErr(HRESULT res, int dev_num)
{
	if (res == DI_OK){
		mprintf(0,"device #%d unacquired\n",dev_num);
		return TRUE;
	}
	else
	if (res == S_FALSE){
		mprintf(0,"device #%d already unacquired\n",dev_num);
		return TRUE;
	}
	else
	if (res == DIERR_INVALIDPARAM){
		mprintf(0,"device %d DIERR_INVALIDPARAM\n",dev_num);
		return FALSE;
	}
	else
	if (res == DIERR_OTHERAPPHASPRIO){
		mprintf(0,"device %d DIERR_OTHERAPPHASPRIO\n",dev_num);
		return TRUE;
	}
	else
		mprintf(0,"Unknown Error unacquiring device %d\n",dev_num);
	
	return FALSE;
}


/*
*****************************************************************

  Immersion

*****************************************************************
*/
#if 0
#pragma message("Compiling Immersion Support.")

HMODULE ImmersionHandle = NULL;
typedef HIFORCEPROJECT (__stdcall *IFLoadProjectFile_fp)(LPCSTR pProjectFileName,LPDIRECTINPUTDEVICE2A pDevice );
IFLoadProjectFile_fp d_IFLoadProjectFile = NULL;

typedef BOOL (__stdcall *IFReleaseProject_fp)(HIFORCEPROJECT hProject);
IFReleaseProject_fp d_IFReleaseProject = NULL;

typedef LPDIRECTINPUTEFFECT *(__stdcall *IFCreateEffects_fp)(HIFORCEPROJECT hProject,LPCSTR pObjectName,int *pNumEffects );
IFCreateEffects_fp d_IFCreateEffects = NULL;


void ddio_LoadImmersionDLL(void)
{
	if(ImmersionHandle!=NULL){
		ddio_FreeImmersionDLL();
	}

	ImmersionHandle = LoadLibrary("IForce2.dll");
	
	if(ImmersionHandle==NULL){
		//not found
		mprintf(0,"Force: Unable to find Immersion DLL\n");
		return;
	}

	//get functions
	d_IFLoadProjectFile = (IFLoadProjectFile_fp)GetProcAddress(ImmersionHandle,"_IFLoadProjectFile@8");
	d_IFReleaseProject = (IFReleaseProject_fp)GetProcAddress(ImmersionHandle,"_IFReleaseProject@4");
	d_IFCreateEffects = (IFCreateEffects_fp)GetProcAddress(ImmersionHandle,"_IFCreateEffects@12");

	if( !d_IFLoadProjectFile	||
		!d_IFReleaseProject		||
		!d_IFCreateEffects){
		mprintf(0,"Force: Unable to bind Immersion functions\n");
		ddio_FreeImmersionDLL();
		return;
	}

	mprintf(0,"Immersion IFORCE2 DLL loaded successfully\n");
}

void ddio_FreeImmersionDLL(void)
{
	if(ImmersionHandle){
		FreeLibrary(ImmersionHandle);
		ImmersionHandle = NULL;
		d_IFLoadProjectFile = NULL;
		d_IFReleaseProject = NULL;
		d_IFCreateEffects = NULL;
	}
}

//	Given a filename resource, this loads the file and creates a resource
//	for it.  It returns a handle to that resource.
//	If it returns NULL, then it couldn't load the project.
//	Make sure device is aquired before calling.
FORCEPROJECT ddio_ForceLoadProject(char *filename,tDevice dev)
{
	if(!d_IFLoadProjectFile){
		return NULL;
	}

	if( dev < 0 || dev >kMaxJoy ){
		mprintf(0,"illegal device id passed to ddio_ForceLoadProject() - %d\n",(int)dev);
		return NULL;
	}

	HIFORCEPROJECT prj = d_IFLoadProjectFile(filename,DID2_Joy[dev]);
	return (FORCEPROJECT)prj;
}

//	Unloads a FORCEPROJECT file
void ddio_ForceUnloadProject(FORCEPROJECT prj)
{
	if(!d_IFReleaseProject)
		return;

	if(!prj)
		return;

	d_IFReleaseProject((HIFORCEPROJECT)prj);
}

//	Given a handle to a resource, and the name of the effect to load
//	it will load that effect.  Returns the effect ID, or -1 if it couldn't
//	be created
int ddio_CreateForceFromProject(FORCEPROJECT project,const char *forcename)
{
	if(!d_IFCreateEffects){
		return -1;
	}

	LPDIRECTINPUTEFFECT * gppdie;
	HIFORCEPROJECT prj;

	if(!project)
		return -1;

	prj = (HIFORCEPROJECT)project;
	
	gppdie = d_IFCreateEffects(prj,forcename,NULL);

	if( !gppdie ){
		return -1;
	}

	DIE_hEffect[numEffects] = *gppdie;
	numEffects++;
	return (numEffects-1);
}

#else
#pragma message("Not Compiling For Immersion Support.")
//	Given a filename resource, this loads the file and creates a resource
//	for it.  It returns a handle to that resource.
//	If it returns NULL, then it couldn't load the project.
//	Make sure device is aquired before calling.
FORCEPROJECT ddio_ForceLoadProject(char *filename,tDevice dev)
{
	return NULL;
}

//	Unloads a FORCEPROJECT file
void ddio_ForceUnloadProject(FORCEPROJECT prj)
{
	return;
}

//	Given a handle to a resource, and the name of the effect to load
//	it will load that effect.  Returns the effect ID, or -1 if it couldn't
//	be created
int ddio_CreateForceFromProject(FORCEPROJECT project,const char *forcename)
{
	return -1;
}

void ddio_LoadImmersionDLL(void)
{
}

void ddio_FreeImmersionDLL(void)
{
}

#endif


//==========================================================
// Function: PrintDirectInputErrorString
//
// Description:
//		Prints a debug message(s) of errors based on error
//	code passed in.
//
//==========================================================
void PrintDirectInputErrorString( HRESULT hr,const char *format, ... )
{
#ifdef RELEASE
	return;
#endif
	char buffer[2048];

	std::va_list marker;
	va_start(marker,format);
	std::vsnprintf(buffer,2048,format,marker); 
	va_end(marker);
	strcat(buffer,": \n");

	if(hr==S_FALSE){
		strcat(buffer,"*S_FALSE\n");
		mprintf(0,buffer);
		return;
	}

	if(hr==DI_BUFFEROVERFLOW)
		strcat(buffer,"*The device buffer overflowed and some input was lost. This value is equal to the S_FALSE standard COM return value.\n");
	if(hr==DI_DOWNLOADSKIPPED)
		strcat(buffer,"*The parameters of the effect were successfully updated, but the effect could not be downloaded because the associated device was not acquired in exclusive mode. \n");
	if(hr==DI_EFFECTRESTARTED)
		strcat(buffer,"*The effect was stopped, the parameters were updated, and the effect was restarted.\n");
	if(hr==DI_NOEFFECT)
		strcat(buffer,"*The operation had no effect. This value is equal to the S_FALSE standard COM return value.\n");
	if(hr==DI_NOTATTACHED)
		strcat(buffer,"*The device exists but is not currently attached. This value is equal to the S_FALSE standard COM return value.\n");
	if(hr==DI_OK)
		strcat(buffer,"*The operation completed successfully. This value is equal to the S_OK standard COM return value.\n");
	if(hr==DI_POLLEDDEVICE)
		strcat(buffer,"*The device is a polled device. As a result, device buffering will not collect any data and event notifications will not be signaled until the IDirectInputDevice2::Poll method is called.\n");
	if(hr==DI_PROPNOEFFECT)
		strcat(buffer,"*The change in device properties had no effect. This value is equal to the S_FALSE standard COM return value.\n");
	if(hr==DI_TRUNCATED)
		strcat(buffer,"*The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.\n");
	if(hr==DI_TRUNCATEDANDRESTARTED)
		strcat(buffer,"*Equal to DI_EFFECTRESTARTED | DI_TRUNCATED.\n");
	if(hr==DIERR_ACQUIRED)
		strcat(buffer,"*The operation cannot be performed while the device is acquired.\n");
	if(hr==DIERR_ALREADYINITIALIZED)
		strcat(buffer,"*This object is already initialized\n");
	if(hr==DIERR_BADDRIVERVER)
		strcat(buffer,"*The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.\n");
	if(hr==DIERR_BETADIRECTINPUTVERSION)
		strcat(buffer,"*The application was written for an unsupported prerelease version of DirectInput.\n");
	if(hr==DIERR_DEVICEFULL)
		strcat(buffer,"*The device is full.\n");
	if(hr==DIERR_DEVICENOTREG)
		strcat(buffer,"*The device or device instance is not registered with DirectInput. This value is equal to the REGDB_E_CLASSNOTREG standard COM return value.\n");
	if(hr==DIERR_EFFECTPLAYING)
		strcat(buffer,"*The parameters were updated in memory but were not downloaded to the device because the device does not support updating an effect while it is still playing. \n");
	if(hr==DIERR_HASEFFECTS)
		strcat(buffer,"*The device cannot be reinitialized because there are still effects attached to it.\n");
	if(hr==DIERR_GENERIC)
		strcat(buffer,"*An undetermined error occurred inside the DirectInput subsystem. This value is equal to the E_FAIL standard COM return value.\n");
	if(hr==DIERR_HANDLEEXISTS)
		strcat(buffer,"*The device already has an event notification associated with it. This value is equal to the E_ACCESSDENIED standard COM return value.\n");
	if(hr==DIERR_INCOMPLETEEFFECT)
		strcat(buffer,"*The effect could not be downloaded because essential information is missing. For example, no axes have been associated with the effect, or no type-specific information has been supplied.\n");
	if(hr==DIERR_INPUTLOST)
		strcat(buffer,"*Access to the input device has been lost. It must be reacquired.\n");
	if(hr==DIERR_INVALIDPARAM)
		strcat(buffer,"*An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.\n");
	if(hr==DIERR_MOREDATA)
		strcat(buffer,"*Not all the requested information fitted into the buffer.\n");
	if(hr==DIERR_NOAGGREGATION)
		strcat(buffer,"*This object does not support aggregation.\n");
	if(hr==DIERR_NOINTERFACE)
		strcat(buffer,"*The specified interface is not supported by the object. This value is equal to the E_NOINTERFACE standard COM return value.\n");
	if(hr==DIERR_NOTACQUIRED)
		strcat(buffer,"*The operation cannot be performed unless the device is acquired.\n");
	if(hr==DIERR_NOTBUFFERED)
		strcat(buffer,"*The device is not buffered. Set the DIPROP_BUFFERSIZE property to enable buffering. \n");
	if(hr==DIERR_NOTDOWNLOADED)
		strcat(buffer,"*The effect is not downloaded.\n");
	if(hr==DIERR_NOTEXCLUSIVEACQUIRED)
		strcat(buffer,"*The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode. \n");
	if(hr==DIERR_NOTFOUND)
		strcat(buffer,"*The requested object does not exist.\n");
	if(hr==DIERR_NOTINITIALIZED)
		strcat(buffer,"*This object has not been initialized.\n");
	if(hr==DIERR_OBJECTNOTFOUND)
		strcat(buffer,"*The requested object does not exist.\n");
	if(hr==DIERR_OLDDIRECTINPUTVERSION)
		strcat(buffer,"*The application requires a newer version of DirectInput.\n");
	if(hr==DIERR_OTHERAPPHASPRIO)
		strcat(buffer,"*Another application has a higher priority level, preventing this call from succeeding. This value is equal to the E_ACCESSDENIED standard COM return value. This error can be returned when an application has only foreground access to a device but is attempting to acquire the device while in the background. \n");
	if(hr==DIERR_OUTOFMEMORY)
		strcat(buffer,"*The DirectInput subsystem couldn't allocate sufficient memory to complete the call. This value is equal to the E_OUTOFMEMORY standard COM return value.\n");
	if(hr==DIERR_READONLY)
		strcat(buffer,"*The specified property cannot be changed. This value is equal to the E_ACCESSDENIED standard COM return value.\n");
	//@@if(hr==DIERR_REPORTFULL)
	//@@	strcat(buffer,"*More information was requested to be sent than can be sent to the device.\n");
	//@@if(hr==DIERR_UNPLUGGED)
	//@@	strcat(buffer,"*The operation could not be completed because the device is not plugged in.\n");
	if(hr==DIERR_UNSUPPORTED)
		strcat(buffer,"*The function called is not supported at this time. This value is equal to the E_NOTIMPL standard COM return value. \n");
	if(hr==E_PENDING)
		strcat(buffer,"*Data is not yet available.\n");
	mprintf(0,buffer);
}

#else

#include "forcefeedback.h"

void ddio_ff_GetInfo(bool *ff_found, bool *ff_enabled) {
  if (ff_found) {
    *ff_found = false;
  }

  if (ff_enabled) {
    *ff_enabled = false;
  }
}

void ddio_ffb_Pause(tDevice dev) {}

void ddio_ffb_Continue(tDevice dev) {}

int ddio_ff_Acquire(tDevice dev) { return 0; }

void ddio_ffjoy_EnableAutoCenter(tDevice dev, bool enable) {}

void ddio_ffjoy_SetGain(tDevice dev, float value) {}

bool ddio_ffjoy_SupportAutoCenter(tDevice dev) { return false; }

void ddio_ffb_DestroyAll(void) {}

void ddio_ffb_effectPlay(int16_t eID) {}

void ddio_ffb_effectModify(int16_t eID, int *Direction, uint32_t *Duration, uint32_t *Gain, uint32_t *Period,
                           tEffInfo *TypeInfo, tEffEnvelope *Envelope) {}

int ddio_ffb_effectCreate(tDevice dev, tFFB_Effect *eff) { return -1; }

int ddio_CreateForceFromProject(FORCEPROJECT project, const char *forcename) { return -1; }

void ddio_ForceUnloadProject(FORCEPROJECT prj) {}

FORCEPROJECT ddio_ForceLoadProject(char *filename, tDevice dev) { return NULL; }

int ddio_ffjoy_Init(void) { return 0; }

int ddio_ff_Init(void) { return 0; }

void ddio_ff_AttachForce(void) {}

void ddio_ff_DetachForce(void) {}

LPDIRECTINPUTDEVICE2 ddio_ff_get_joystick_obj(tDevice dev) { return NULL; }

#endif
