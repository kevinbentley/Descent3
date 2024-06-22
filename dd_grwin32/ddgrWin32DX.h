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

 * $Logfile: /DescentIII/Main/ddgr_win32/ddgrWin32DX.h $
 * $Revision: 2 $
 * $Date: 9/12/97 4:13p $
 * $Author: Samir $
 *
 *	DirectX Subsystem Implementation of ddgr library
 *
 * $Log: /DescentIII/Main/ddgr_win32/ddgrWin32DX.h $
 *
 * 2     9/12/97 4:13p Samir
 * Added some private data access functions and more DirectX
 * functionality.
 *
 * $NoKeywords: $
 */

/*	Functions
 */

#ifndef DDGRWIN32DX_H
#define DDGRWIN32DX_H

#include <windows.h>

#include "ddgr.h"
#include "ddraw.h"

class oeApplication;

/* Data structures
 */
struct tDXSurface {
  LPDIRECTDRAWSURFACE lpdds;
  LPDIRECTDRAWSURFACE lpddsback;
  bool backbuffer;
};

#define DX_MAX_DEVMODES 32
struct tDDGRDXInternalData // Internal data for DX subsystem
{
  bool init;         // is library initialized
  LPDIRECTDRAW lpDD; // DirectDraw Object for video manipulation
  HWND hPrimaryWnd;  // window owning display
  int vidrefs;       // Number of surface references to hPrimaryWnd.
  tDXSurface vidsurf;
  DDSURFACEDESC vidmodes[DX_MAX_DEVMODES]; // Device modes for GDI subsystem (not GDIX)
};

/*	Externs */
extern tDDGRDXInternalData DDGR_DX_lib_data;

/*	Macros */
#define DX_DATA(_c) DDGR_DX_lib_data._c

//	Initializes DX subsystem
bool ddgr_dx_Init();

//	Closes DX subsystem
void ddgr_dx_Close();

//	Initializes the display for use with the DX subsystem.
bool ddgr_dx_surf_InitVideo(ddgr_surface *sf);

//	Deinitializes the video surface
void ddgr_dx_surf_CloseVideo(ddgr_surface *sf);

//	flips the buffers in a surface.  really only useful for video screens
bool ddgr_dx_surf_FlipVideo(ddgr_surface *sf);

/*	input:
                sf->name is optional.
                sf->w, sf->h, sf->bpp are mandatory
                sf->type and sf->flags are mandatory.
        output:
                sf->obj = surface object.
                sf->locks = 0
*/
bool ddgr_dx_surf_Create(ddgr_surface *sf);
void ddgr_dx_surf_Destroy(ddgr_surface *sf);

/*	retrieves a pointer to surface memory.  allowed to lock one surface multiple times.
                ptr is the returned pointer to surface memory.  used to unlock surface also
                rowsize is the size in bytes of one row of memory.
*/
bool ddgr_dx_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize);
bool ddgr_dx_surf_Unlock(ddgr_surface *sf, void *ptr);

//	attaches an OS handle to a surface
void ddgr_dx_surf_AttachHandle(ddgr_surface *sf, unsigned handle);

//	The only graphic primatives
//	clear
//	blt.
void ddgr_dx_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h);
bool ddgr_dx_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh);

#endif
