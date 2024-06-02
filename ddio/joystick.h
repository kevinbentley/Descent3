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

 * $Logfile: /DescentIII/Main/Lib/joystick.h $
 * $Revision: 11 $
 * $Date: 10/21/99 9:27p $
 * $Author: Jeff $
 *
 *	Joystick interface.
 *
 * $Log: /DescentIII/Main/Lib/joystick.h $
 *
 * 11    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 10    7/28/99 3:19p Kevin
 * Mac Stuff
 *
 * 9     7/26/99 11:59a Samir
 * add code to get name of joystick
 *
 * 8     7/16/99 11:14a Samir
 * multiple hat support and improved direct input support.
 *
 * 7     4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 6     6/18/98 4:49p Samir
 * modified for better mouse support?
 *
 * 5     6/02/98 4:37p Samir
 * multiple joysticks supported.
 *
 * 4     6/01/98 4:27p Samir
 * pov may return multiple positions.
 *
 * 3     12/05/97 12:49p Samir
 * New POV constants.
 *
 * 2     12/03/97 7:33p Samir
 * Newer joystick library.
 *
 * 1     11/24/97 3:27p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <cstdint>

//	joystick ids.  used to initialize a stick and get its position
#define MAX_JOYSTICKS 8
#define JOYPOV_NUM 4

//	these flags tell what axes these controllers control.
#define JOYFLAG_XVALID 1
#define JOYFLAG_YVALID 2
#define JOYFLAG_ZVALID 4
#define JOYFLAG_RVALID 8
#define JOYFLAG_UVALID 16
#define JOYFLAG_VVALID 32
#define JOYFLAG_POVVALID 64
#define JOYFLAG_POV2VALID 128
#define JOYFLAG_POV3VALID 256
#define JOYFLAG_POV4VALID 512

//	set in joystate.pov
#define JOYPOV_DIR 8
#define JOYPOV_MAXVAL 0x100
#define JOYPOV_UP 0
#define JOYPOV_RIGHT 0x40
#define JOYPOV_DOWN 0x80
#define JOYPOV_LEFT 0xc0
#define JOYPOV_CENTER 0xff

#define JOYAXIS_RANGE 256

typedef int tJoystick;

#define JOYSTICK_1 0
#define JOYSTICK_2 1
#define JOYSTICK_3 2
#define JOYSTICK_4 3
#define JOYSTICK_5 4
#define JOYSTICK_6 5
#define JOYSTICK_7 6
#define JOYSTICK_8 7

struct tJoyInfo {
  char name[128];
  unsigned axes_mask;
  unsigned num_btns;
  int minx, maxx;
  int miny, maxy;
  int minz, maxz;
  int minr, maxr;
  int minu, maxu;
  int minv, maxv;
};

//	shared between joystick remote server and local client.
#define JOY_PORT 3192
#define JOY_REQTERM "RTRM"
#define JOY_TERM "TERM"
#define JOY_POS "POSI"
#define JOY_INFO "INFO"
#define JOY_POLL "POLL"

struct tJoyPacket {
  char coda[4]; // used to identify packet
  char buf[128];
};

struct tJoyPos {
  int x;
  int y;
  int z;
  int r;
  int u;
  int v;
  unsigned buttons;
  unsigned btn;
  unsigned pov[JOYPOV_NUM];
};

//	joystick system initialization
bool joy_Init(bool emulation);
void joy_Close();

//	retreive information about joystick.
void joy_GetJoyInfo(tJoystick joy, tJoyInfo *info);

//	retreive position of joystick
void joy_GetPos(tJoystick joy, tJoyPos *pos);

//	retreive uncalibrated position of joystick
void joy_GetRawPos(tJoystick joy, tJoyPos *pos);

//	returns true if joystick valid
bool joy_IsValid(tJoystick joy);

// run by ddio_Frame
void ddio_InternalJoyFrame();

// DAJ Added to support InSprocket
#endif
