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

 * $Logfile: /DescentIII/Main/renderer/lnxscreenmode.h $
 * $Revision: 1.3 $
 * $Date: 2004/02/09 04:14:52 $
 * $Author: kevinb $
 *
 *
 *
 * $Log: lnxscreenmode.h,v $
 * Revision 1.3  2004/02/09 04:14:52  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.2  2000/04/28 20:25:51  icculus
 * Updates, cleanups, and SDLification.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:49  icculus
 * initial checkin
 *
 *
 * 3     9/06/99 9:21p Jeff
 * lock video mode switching, don't set viewport when restoring (causing a
 * bunch of screen garbage)
 *
 * 2     9/05/99 9:41p Jeff
 * first checkin of Linux Screen manager
 *
 * $NoKeywords: $
 */

#ifndef __LNXVIDEOMODE_H__
#define __LNXVIDEOMODE_H__

#ifdef __LINUX__
#include "linux_fix.h"
#endif
#include <SDL.h>

#define MODE_OK 0
#define MODE_HSYNC 1 /* hsync out of range */
#define MODE_VSYNC 2 /* vsync out of range */
#define MODE_BAD 255 /* unspecified reason */

class CLnxVideoModes {
public:
  CLnxVideoModes();
  ~CLnxVideoModes();

  bool Init(void); // Display *dpy,int screen);
  void RestoreVideoMode(void);

  // bool QueryExtension(Display *dpy);
  //	void GetModeLine(Display *dpy,int screen,int *dotclock,XF86VidModeModeLine *modeline);

  bool SwitchResolution(int width, int height);
  void Lock(bool lock);

  SDL_Rect **getModes(void) { return m_ModeInfoList; }
  Uint32 getSDLFlags(void) { return (sdlflags); }

private:
  //	bool SwitchToMode(XF86VidModeModeInfo *mode);
  bool LoadLibraries(void);

  bool m_Inited;
  bool m_VideoResolutionChanged;
  int m_NumVideoModes;
  //	XF86VidModeModeInfo **m_ModeInfoList;
  SDL_Rect **m_ModeInfoList;
  Uint32 sdlflags;
  //	Display *m_Display;
  //	int m_Screen;
};

extern CLnxVideoModes LinuxVideoMode;

#endif
