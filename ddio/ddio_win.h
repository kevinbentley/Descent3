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

 * $Logfile: /DescentIII/Main/ddio_win/ddio_win.h $
 * $Revision: 11 $
 * $Date: 4/09/99 12:02p $
 * $Author: Samir $
 *
 * <insert description of file here>
 *
 * $Log: /DescentIII/Main/ddio_win/ddio_win.h $
 *
 * 11    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 10    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 9     10/15/98 6:48p Samir
 * added timer hooks.
 *
 * 8     6/29/98 6:43p Samir
 * Took out GetMsgProc and legacy keyboard variables.
 *
 * 7     5/08/98 12:54p Samir
 * newer unused mouse handler.
 *
 * 6     3/31/98 12:46p Samir
 * keyboard IO system better.  uses getmsgproc windows hook.
 *
 * 5     12/10/97 1:12p Samir
 * Use timestamp from DirectInput Key calls.
 *
 * 4     10/16/97 2:29p Samir
 * Changed DirectInput Keyboard to FOREGROUND
 *
 * 3     8/13/97 3:02p Samir
 * A 'cleaner' way to do DirectInput mouse stuff.
 *
 * 2     8/01/97 7:30p Samir
 * Better NT keyboard support.
 *
 * 7     5/08/97 1:57p Samir
 * Moved keys info structure to ddio_common.h
 *
 * 6     4/16/97 11:32a Samir
 * Added z axis support.
 *
 * 5     1/23/97 2:24p Samir
 * Took out ddio_KeyHandler prototype.
 *
 * $NoKeywords: $
 */

#ifndef DDIO_WIN_H
#define DDIO_WIN_H

#include <cstdint>
#include <windows.h>
#include "pstypes.h"
#include "win/DirectX/dinput.h"

class oeWin32Application;

struct dinput_data {
  HWND hwnd;
  LPDIRECTINPUT lpdi;
  bool preemptive;
};

extern dinput_data DInputData;
extern bool DDIO_init;
extern bool DDIO_preemptive;

bool ddio_JoyHandler();
float ddio_TickToSeconds(uint32_t ticks);

#ifdef _DEBUG
void ddio_DebugMessage(unsigned err, char *fmt, ...);
#define DDIO_MESSAGE(_m) ddio_DebugMessage _m
#else
#define DDIO_MESSAGE(_m)
#endif

#define MAKE_DDIO_TIME(_ms) ddio_TickToSeconds(_ms)

//	hook in timer function at certain period.  returns a handle to this function
DWORD timer_HookFunction(void(CALLBACK *fncptr)(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR), UINT period);

//	clears function from hook list specified by a handle returned from HookFunction
void timer_ReleaseFunction(DWORD func);

#endif
