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

 * $Logfile: /DescentIII/Main/ddgr_win32/ddgrWin32GDI.h $
 * $Revision: 2 $
 * $Date: 9/12/97 4:13p $
 * $Author: Samir $
 *
 *	DDGR v2.0 GDI(X) implementation,.
 *
 * $Log: /DescentIII/Main/ddgr_win32/ddgrWin32GDI.h $
 *
 * 2     9/12/97 4:13p Samir
 * Added some private data access functions and more DirectX
 * functionality.
 *
 * 1     6/12/97 6:34p Samir
 * initial revision
 *
 * $NoKeywords: $
 */

#ifndef DDGRWIN32GDI_H
#define DDGRWIN32GDI_H

#include <windows.h>

#include "ddgr.h"
#include "ddraw.h"

class oeApplication;

/* Data structures
 */
#define GDI_MAX_DEVMODES 30
struct tDDGRGDIInternalData // Internal data for GDI subsystem
{
  bool init;                          // is library initialized
  bool ddraw;                         // do we use DirectDraw for display mode changing.
  LPDIRECTDRAW lpDD;                  // DirectDraw Object for video manipulation
  HWND hPrimaryWnd;                   // window owning display
  HDC hOffscreenDC;                   // DC for our generic surfaces.
  bool fullscreen;                    // Should we run in fullscreen?
  int vidrefs;                        // Number of surface references to hPrimaryWnd.
  int olddispmode;                    // old display mode for GDI subsystem only (not GDIX)
  DEVMODE devmodes[GDI_MAX_DEVMODES]; // Device modes for GDI subsystem (not GDIX)
};

struct tGDISurface {
  HBITMAP hbm;     // windows DIB section bitmap handle
  void *data;      // pointer to bitmap bits
  bool backbuffer; // is this a dual-page surface? (hbm is offscreen)
  int rowsize;     // rowsize of bitmap bits array
  HWND hwnd;       // window attached to surface
};

struct tDIBHeader // used to create and manipulate DIBs (a 16/32BPP surface only)
{
  BITMAPINFOHEADER bmi;
  DWORD red_mask;
  DWORD green_mask;
  DWORD blue_mask;
};

struct tDIBHeader8 // used to create and manipulate DIBs (a 16/32BPP surface only)
{
  BITMAPINFOHEADER bmi;
  RGBQUAD rgb[256];
};

/*	Externs */
extern tDDGRGDIInternalData DDGR_GDI_lib_data;

/*	Macros */
#define GDI_DATA(_c) DDGR_GDI_lib_data._c

/*	Functions
 */

//	Initializes GDI subsystem
bool ddgr_gdi_Init(bool fullscreen, bool ddraw);

//	Closes GDI subsystem
void ddgr_gdi_Close();

//	Initializes the display for use with the GDI subsystem.
bool ddgr_gdi_surf_InitVideo(ddgr_surface *sf);

//	Deinitializes the video surface
void ddgr_gdi_surf_CloseVideo(ddgr_surface *sf);

//	flips the buffers in a surface.  really only useful for video screens
bool ddgr_gdi_surf_FlipVideo(ddgr_surface *sf);

/*	input:
                sf->name is optional.
                sf->w, sf->h, sf->bpp are mandatory
                sf->type and sf->flags are mandatory.
        output:
                sf->obj = surface object.
                sf->locks = 0
*/
bool ddgr_gdi_surf_Create(ddgr_surface *sf);
void ddgr_gdi_surf_Destroy(ddgr_surface *sf);

/*	retrieves a pointer to surface memory.  allowed to lock one surface multiple times.
                ptr is the returned pointer to surface memory.  used to unlock surface also
                rowsize is the size in bytes of one row of memory.
*/
bool ddgr_gdi_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize);
bool ddgr_gdi_surf_Unlock(ddgr_surface *sf, void *ptr);

//	attaches an OS handle to a surface
void ddgr_gdi_surf_AttachHandle(ddgr_surface *sf, unsigned handle);

//	The only graphic primatives
//	clear
//	blt.
void ddgr_gdi_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h);
bool ddgr_gdi_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);

#endif
