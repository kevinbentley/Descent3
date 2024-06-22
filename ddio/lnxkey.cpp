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

 * $Logfile: /DescentIII/Main/ddio_lnx/lnxkey.cpp $
 * $Revision: 1.3 $
 * $Date: 2004/02/25 00:04:06 $
 * $Author: ryan $
 *
 * Linux keyboard routines
 *
 * $Log: lnxkey.cpp,v $
 * Revision 1.3  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.2  2000/04/27 11:17:07  icculus
 * Removed some keyboard drivers, added SDL hooks.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:33  icculus
 * initial checkin
 *
 *
 * 13    7/14/99 9:06p Jeff
 * added comment header
 *
 * $NoKeywords: $
 */

/*
 * Linux Keyboard Interface, Non-SVGALIB Implementation
 * $NoKeywords: $
 */

// ----------------------------------------------------------------------------
//	Keyboard Interface
// ----------------------------------------------------------------------------
#include "lnxapp.h"
#include "ddio.h"
#include "mono.h"

volatile struct tLnxKeys {
  union {
    int up_ticks;
    float up_time;
  };
  union {
    int down_ticks;
    float down_time;
  };
  bool status;
} LKeys[DDIO_MAX_KEYS];

// null mode ddio
bool ddio_null_InternalKeyInit(ddio_init_info *init_info);
void ddio_null_InternalKeyClose();
bool ddio_null_InternalKeyState(uint8_t key);
void ddio_null_InternalKeySuspend();
void ddio_null_InternalKeyResume();
float ddio_null_InternalKeyDownTime(uint8_t key);
void ddio_null_InternalResetKey(uint8_t key);
bool ddio_null_KeyFrame();
void ddio_null_InternalKeyFrame(void);

// sdl mode ddio
bool ddio_sdl_InternalKeyInit(ddio_init_info *init_info);
void ddio_sdl_InternalKeyClose();
bool ddio_sdl_InternalKeyState(uint8_t key);
void ddio_sdl_InternalKeySuspend();
void ddio_sdl_InternalKeyResume();
float ddio_sdl_InternalKeyDownTime(uint8_t key);
void ddio_sdl_InternalResetKey(uint8_t key);
bool ddio_sdl_KeyFrame();
void ddio_sdl_InternalKeyFrame(void);

enum {
  Input_null,
  Input_sdl // Input_svga,Input_xwin
} Keyboard_mode;

// ----------------------------------------------------------------------------
//	Initialization of keyboard device.
// ----------------------------------------------------------------------------

bool ddio_InternalKeyInit(ddio_init_info *init_info) {

  // determine if we are to use SDL or null mode
  Keyboard_mode = (App()->flags() & APPFLAG_USESERVICE) ? Input_null : Input_sdl;

  switch (Keyboard_mode) {
  case Input_null:
    return ddio_null_InternalKeyInit(init_info);
  case Input_sdl:
    return ddio_sdl_InternalKeyInit(init_info);
  }

  return false;
}

void ddio_InternalKeyClose() {
  switch (Keyboard_mode) {
  case Input_null:
    return ddio_null_InternalKeyClose();
  case Input_sdl:
    return ddio_sdl_InternalKeyClose();
  }
}

bool ddio_InternalKeyState(uint8_t key) {
  switch (Keyboard_mode) {
  case Input_null:
    return ddio_null_InternalKeyState(key);
  case Input_sdl:
    return ddio_sdl_InternalKeyState(key);
  }

  return false;
}

void ddio_InternalKeySuspend() {
  switch (Keyboard_mode) {
  case Input_null:
    ddio_null_InternalKeySuspend();
    break;
  case Input_sdl:
    return ddio_sdl_InternalKeySuspend();
  }
}

void ddio_InternalKeyResume() {
  switch (Keyboard_mode) {
  case Input_null:
    ddio_null_InternalKeyResume();
    break;
  case Input_sdl:
    return ddio_sdl_InternalKeyResume();
  }
}

float ddio_InternalKeyDownTime(uint8_t key) {
  switch (Keyboard_mode) {
  case Input_null:
    return ddio_null_InternalKeyDownTime(key);
  case Input_sdl:
    return ddio_sdl_InternalKeyDownTime(key);
  }

  return 0.0f;
}

void ddio_InternalResetKey(uint8_t key) {
  switch (Keyboard_mode) {
  case Input_null:
    ddio_null_InternalResetKey(key);
    break;
  case Input_sdl:
    return ddio_sdl_InternalResetKey(key);
  }
}

bool ddio_KeyFrame() {
  switch (Keyboard_mode) {
  case Input_sdl:
    break;
  case Input_null:
    return ddio_null_KeyFrame();
  }

  return true;
}

void ddio_InternalKeyFrame(void) {
  switch (Keyboard_mode) {
  case Input_null:
    ddio_null_InternalKeyFrame();
    break;
  case Input_sdl:
    return ddio_sdl_InternalKeyFrame();
  }
}

void ddio_SetKeyboardLanguage(int) {}
