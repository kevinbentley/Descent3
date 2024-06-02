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

 * $Logfile: /DescentIII/Main/Lib/ddio_common.h $
 * $Revision: 1.3 $
 * $Date: 2004/02/09 04:14:51 $
 * $Author: kevinb $
 *
 * Common DDIO functions
 *
 * $Log: ddio_common.h,v $
 * Revision 1.3  2004/02/09 04:14:51  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.2  2000/09/22 19:04:37  icculus
 * SDLK_WORLD support
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 20    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 19    5/11/99 11:18a Jeff
 * added serial support
 *
 * 18    4/24/99 5:41p Samir
 * moved key to ascii, ascii to key to the ddio_common library.
 *
 * 17    4/22/99 2:48a Jeff
 * fixed changed prototype
 *
 * 16    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 15    2/21/99 6:38p Samir
 * mouse and key input better. buffered mouse.
 *
 * 14    1/25/99 6:47p Samir
 * allow slow keyboard
 *
 * 13    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 12    10/20/98 12:58a Jeff
 * added a way to force a lo-resolution timer
 *
 * 11    9/17/98 12:50p Samir
 * added ddio_KeyFlushKey.
 *
 * 10    8/12/98 2:54p Matt
 * Renamed the slash and backslash key constants.
 *
 * 9     7/01/98 4:55p Samir
 * new simplified mouse system.
 *
 * 8     6/30/98 4:20p Samir
 * added ddio_Close as standalone.   ddio_Init will no longer close
 * itself.
 *
 * 7     6/24/98 3:26p Samir
 * changed codes for pause and NUMLOCK, since they seem different under
 * windows.
 *
 * 6     3/24/98 4:26p Samir
 * added function to return the state of an adjusted key.
 *
 * 5     2/25/98 6:11p Samir
 * Added functions to better deal with key flushing.
 *
 * 4     12/10/97 1:12p Samir
 * Pass time to ddio_UpdateKeyState
 *
 * 3     10/29/97 4:14p Samir
 * Keep record of key down count per key.
 *
 * 2     10/16/97 2:28p Samir
 * move keyboard init into ddio_init and added preemptive select for
 * keyboard.
 *
 * 4     6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 3     5/09/97 6:45p Samir
 * Common keystate update function
 *
 * 2     5/08/97 1:55p Samir
 * Move initialization stuff to ddio_common.h
 *
 * 1     5/08/97 12:34p Samir
 * Moved functions from ddio.h to ddio_common.h
 *
 * $NoKeywords: $
 */

#ifndef DDIO_COMMON_H
#define DDIO_COMMON_H

#include <cstdint>

#include "application.h"

#define DDIO_MOUSE_LITE 2 // some ddio systems support the 'lite' extension of mice.

struct ddio_init_info {
  oeApplication *obj; // App object used to initialize to IO system
  bool key_emulation; // keyboard emulation
  bool joy_emulation; // joystick emulation
};

// ----------------------------------------------------------------------------
//	Keyboard Initialization and destruction functions
// ----------------------------------------------------------------------------

//	Initializes DDIO system
bool ddio_Init(ddio_init_info *init_info);
void ddio_Close();

//	suspends ddio input system
void ddio_Suspend();
void ddio_Resume();

// performs io per frame.
void ddio_Frame();

//	initializes keyboard
bool ddio_KeyInit(ddio_init_info *init_info);

//	closes keyboard
void ddio_KeyClose();

//	Handles keyboard queue management(TAKES ADJUSTED KEY VALUES)
void ddio_AddKeyToQueue(int key);

//	Updates timing info for keys
void ddio_UpdateKeyState(int key, bool isdown);

//	given a key code defined below, returns time in seconds since last call.
float ddio_KeyDownTime(int key);

//	return number of times a key's been down since last call.
int ddio_KeyDownCount(int key);

//	returns the state of an ADJUSTED KEY VALUE
bool ddio_GetAdjKeyState(int adj_key);

//	flush keyboard queue
void ddio_KeyFlush();

// flushes an individual key's timing values.
void ddio_KeyFlushKey(int key);

//	gets ADJUSTED KEY from queue
int ddio_KeyInKey();

//	determine if there are ADJUSTED keys in keyqueue
int ddio_KeyPeek();

//	handle input of keyboard per frame.
bool ddio_KeyFrame();

//	converts keycode to ASCII
int ddio_KeyToAscii(int code);

//	converts ascii code to key
int ddio_AsciiToKey(int ascii);

// sets type of keyboard to emulate
#define KBLANG_AMERICAN 0
#define KBLANG_BRITISH 1
#define KBLANG_FRENCH 2
#define KBLANG_GERMAN 3

void ddio_SetKeyboardLanguage(int language);

// ----------------------------------------------------------------------------
//	KEYBOARD CONSTANTS
// ----------------------------------------------------------------------------

//	array of key states.
extern volatile int16_t DDIO_key_down_count[];
extern volatile uint8_t DDIO_key_state[];

#define KEY_STATE(_c) DDIO_key_state[_c]
#define DDIO_MAX_KEYS 256

//	masks used to specify current keycode state matched with scancode
#define KEY_SHIFTED 0x100
#define KEY_ALTED 0x200
#define KEY_CTRLED 0x400
#define KEY_DEBUGGED 0x800

//	used when defining a system code to use in KeyUpdateState
//	masks
#define KEY_STATE_DOWN 0x80000000
#define KEY_STATE_SYSTEM 0x40000000

//	codes
#define KEY_0 0x0B
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C
#define KEY_MINUS 0x0C
#define KEY_EQUAL 0x0D
#define KEY_SLASH 0x35     // was KEY_DIVIDE in Descent & D2
#define KEY_BACKSLASH 0x2B // was KEY_SLASH in Descent and D2
#define KEY_BSLASH_UK 0x56 // UK keyboards have diffent backslash scan code
#define KEY_COMMA 0x33
#define KEY_PERIOD 0x34
#define KEY_SEMICOL 0x27
#define KEY_LBRACKET 0x1A
#define KEY_RBRACKET 0x1B
#define KEY_RAPOSTRO 0x28
#define KEY_LAPOSTRO 0x29
#define KEY_ESC 0x01
#define KEY_ENTER 0x1C
#define KEY_BACKSP 0x0E
#define KEY_TAB 0x0F
#define KEY_SPACEBAR 0x39
#define KEY_NUMLOCK 0xC5
#define KEY_SCROLLOCK 0x46
#define KEY_CAPSLOCK 0x3A
#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36
#define KEY_LALT 0x38
#define KEY_RALT 0xB8
#define KEY_LCTRL 0x1D
#define KEY_RCTRL 0x9D

#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x57
#define KEY_F12 0x58

#define KEY_PAD0 0x52
#define KEY_PAD1 0x4F
#define KEY_PAD2 0x50
#define KEY_PAD3 0x51
#define KEY_PAD4 0x4B
#define KEY_PAD5 0x4C
#define KEY_PAD6 0x4D
#define KEY_PAD7 0x47
#define KEY_PAD8 0x48
#define KEY_PAD9 0x49
#define KEY_PADMINUS 0x4A
#define KEY_PADPLUS 0x4E
#define KEY_PADPERIOD 0x53
#define KEY_PADDIVIDE 0xB5
#define KEY_PADMULTIPLY 0x37
#define KEY_PADENTER 0x9C

#define KEY_INSERT 0xD2
#define KEY_HOME 0xC7
#define KEY_PAGEUP 0xC9
#define KEY_DELETE 0xD3
#define KEY_END 0xCF
#define KEY_PAGEDOWN 0xD1
#define KEY_UP 0xC8
#define KEY_DOWN 0xD0
#define KEY_LEFT 0xCB
#define KEY_RIGHT 0xCD
#define KEY_PRINT_SCREEN 0xB7
#define KEY_PAUSE 0x45

#define KEY_WORLD0 0x54
#define KEY_WORLD1 0x55
#define KEY_WORLD2 0x56
#define KEY_WORLD3 0x57
#define KEY_WORLD4 0x58
#define KEY_WORLD5 0x59
#define KEY_WORLD6 0x5A
#define KEY_WORLD7 0x5B
#define KEY_WORLD8 0x5C
#define KEY_WORLD9 0x5D
#define KEY_WORLD10 0x5E
#define KEY_WORLD11 0x5F
#define KEY_WORLD12 0x60
#define KEY_WORLD13 0x61
#define KEY_WORLD14 0x62
#define KEY_WORLD15 0x63
#define KEY_WORLD16 0x64
#define KEY_WORLD17 0x65
#define KEY_WORLD18 0x66
#define KEY_WORLD19 0x67
#define KEY_WORLD20 0x68
#define KEY_WORLD21 0x69
#define KEY_WORLD22 0x6A
#define KEY_WORLD23 0x6B
#define KEY_WORLD24 0x6C
#define KEY_WORLD25 0x6D
#define KEY_WORLD26 0x6E
#define KEY_WORLD27 0x6F
#define KEY_WORLD28 0x70
#define KEY_WORLD29 0x71
#define KEY_WORLD30 0x72
#define KEY_WORLD31 0x73
#define KEY_WORLD32 0x74
#define KEY_WORLD33 0x75
#define KEY_WORLD34 0x76
#define KEY_WORLD35 0x77
#define KEY_WORLD36 0x78
#define KEY_WORLD37 0x79
#define KEY_WORLD38 0x7A
#define KEY_WORLD39 0x7B
#define KEY_WORLD40 0x7C
#define KEY_WORLD41 0x7D
#define KEY_WORLD42 0x7E
#define KEY_WORLD43 0x7F
#define KEY_WORLD44 0x80
#define KEY_WORLD45 0x81
#define KEY_WORLD46 0x82
#define KEY_WORLD47 0x83
#define KEY_WORLD48 0x84
#define KEY_WORLD49 0x85
#define KEY_WORLD50 0x86
#define KEY_WORLD51 0x87
#define KEY_WORLD52 0x88
#define KEY_WORLD53 0x89
#define KEY_WORLD54 0x8A
#define KEY_WORLD55 0x8B
#define KEY_WORLD56 0x8C
#define KEY_WORLD57 0x8D
#define KEY_WORLD58 0x8E
#define KEY_WORLD59 0x8F
#define KEY_WORLD60 0x90
#define KEY_WORLD61 0x91
#define KEY_WORLD62 0x92
#define KEY_WORLD63 0x93
#define KEY_WORLD64 0x94
#define KEY_WORLD65 0x95
#define KEY_WORLD66 0x96
#define KEY_WORLD67 0x97
#define KEY_WORLD68 0x98
#define KEY_WORLD69 0x99
#define KEY_WORLD70 0x9A
#define KEY_WORLD71 0x9B
// --- rcg07312000 ...skip...
#define KEY_WORLD72 0xE1
#define KEY_WORLD73 0xE2
#define KEY_WORLD74 0xE3
#define KEY_WORLD75 0xE4
#define KEY_WORLD76 0xE5
#define KEY_WORLD77 0xE6
#define KEY_WORLD78 0xE7
#define KEY_WORLD79 0xE8
#define KEY_WORLD80 0xE9
#define KEY_WORLD81 0xE0
#define KEY_WORLD82 0xEA
#define KEY_WORLD83 0xEB
#define KEY_WORLD84 0xEC
#define KEY_WORLD85 0xED
#define KEY_WORLD86 0xEE
#define KEY_WORLD87 0xEF
#define KEY_WORLD88 0xF0
#define KEY_WORLD89 0xF1
#define KEY_WORLD90 0xF2
#define KEY_WORLD91 0xF3
#define KEY_WORLD92 0xF4
#define KEY_WORLD93 0xF5
#define KEY_WORLD94 0xF6
#define KEY_WORLD95 0xF7

#define KEY_CMD 0xE0 // DAJ mac command key

#endif
