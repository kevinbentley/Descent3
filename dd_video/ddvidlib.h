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

 * $Logfile: /DescentIII/Main/ddvid_win32/ddvidlib.h $
 * $Revision: 4 $
 * $Date: 3/06/98 2:22p $
 * $Author: Samir $
 *
 *	Video library internal header
 *
 * $Log: /DescentIII/Main/ddvid_win32/ddvidlib.h $
 *
 * 4     3/06/98 2:22p Samir
 * Added fullscreen windowed version.
 *
 * 3     2/03/98 3:12p Samir
 * Enable access to directdraw object by DDAccess libraries.
 *
 * 2     12/30/97 1:54p Samir
 * Upped max modes.
 *
 * 1     12/23/97 5:46p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#ifndef DDVIDLIB_H
#define DDVIDLIB_H

#include "ddvid.h"

#include <windows.h>
#include <ddraw.h>
#include <stdlib.h>

#define VM_MAX_MODES 96

const int VID_GDIF_SUBSYSTEM = 0, // GDI fullscreen subsystem
    VID_GDI_SUBSYSTEM = 1,        // GDI subsystem
    VID_GDIX_SUBSYSTEM = 2,       // GDIX subsystem (GDI+DirectX)
    VID_DX_SUBSYSTEM = 3;         // DIRECTX subsystem

struct tDDVideoInfo {
  HWND hWnd;
  HWND hVidWnd;
  int subsystem;

  LPDIRECTDRAW lpDD;
  LPDIRECTDRAWSURFACE lpDDSFront;
  LPDIRECTDRAWSURFACE lpDDSBack;
  DDSURFACEDESC DDModes[VM_MAX_MODES];
  int nDDModes;
  int curmode;
  char *surf_data;

  struct {
    HBITMAP hBackBmp;
    HDC hBackDC;
    char *data;
    int pitch;
    int w, h, color_depth;
    int ndevmodes;
    int olddevmode;
    int curdevmode;
  } gdi;
};

//	driver info.
extern tDDVideoInfo DDVideo_info;

// inits fullscreen system
bool ddvidfs_Init();

//	closes fullscreen system
void ddvidfs_Close();

//	uses direct draw.  if paged, allows frame buffer access.
bool ddvidfs_SetVideoMode(int w, int h, int color_depth, bool paged);

//	closes video mode for fs
void ddvidfs_CloseVideo();

//	flips screen if there's a back buffer
void ddvidfs_VideoFlip();

//	returns the directdraw object
uint32_t ddvidfs_GetDirectDrawObject();

// inits windowed system
bool ddvidwin_Init();

//	closes windowed system
void ddvidwin_Close();

//	creates an offscreen back bitmap if needed. otherwise doesn't do a thing really.
bool ddvidwin_SetVideoMode(int w, int h, int color_depth, bool paged, bool reschange = false);

//	closes video mode for fs
void ddvidwin_CloseVideo();

//	flips screen if there's a back buffer
void ddvidwin_VideoFlip();

#endif
