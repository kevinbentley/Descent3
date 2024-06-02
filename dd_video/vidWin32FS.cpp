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

 * $Logfile: /DescentIII/Main/ddvid_win32/vidWin32FS.cpp $
 * $Revision: 7 $
 * $Date: 7/15/98 5:56p $
 * $Author: Samir $
 *
 *	Fullscreen version of Win32 library
 *
 * $Log: /DescentIII/Main/ddvid_win32/vidWin32FS.cpp $
 *
 * 7     7/15/98 5:56p Samir
 * commented out GDIX subsystem.
 *
 * 6     6/04/98 7:04p Samir
 * assert res-switch to be at least 16bpp.
 *
 * 5     3/04/98 5:01p Samir
 * May have fixed problem with restoring old display modes.
 *
 * 4     2/03/98 3:12p Samir
 * Enable access to directdraw object by DDAccess libraries.
 *
 * 3     12/30/97 3:35p Samir
 * Added dummy mode to help in mode selection.
 *
 * 2     12/30/97 2:31p Jason
 * Fixed mode finder. (samir)
 *
 * 1     12/23/97 5:46p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include "ddvidlib.h"
#include "pserror.h"
#include "grdefs.h"

//	DirectDraw Display mode enumeration callback
HRESULT WINAPI DDEnumModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext);

// inits fullscreen system
bool ddvidfs_Init() {
  HRESULT hres;

  hres = DirectDrawCreate(NULL, &DDVideo_info.lpDD, NULL);

  if (hres != DD_OK) {
    Error("Failure to initialize DirectDraw driver. (%d)", LOWORD(hres));
  }

  hres =
      DDVideo_info.lpDD->SetCooperativeLevel(DDVideo_info.hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
  if (hres != DD_OK) {
    Error("Failed to set access mode for DirectDraw driver. (%d)", LOWORD(hres));
  }

  //	dummy mode
  DDVideo_info.DDModes[DDVideo_info.nDDModes].ddpfPixelFormat.dwRGBBitCount = 0;
  DDVideo_info.DDModes[DDVideo_info.nDDModes].dwWidth = 0;
  DDVideo_info.DDModes[DDVideo_info.nDDModes].dwHeight = 0;
  DDVideo_info.nDDModes++;

  //	enumerate all display modes.
  if (DDVideo_info.lpDD->EnumDisplayModes(0, NULL, NULL, DDEnumModesCallback) != DD_OK) {
    mprintf(0, "DDVID error: Error enumerating display modes.\n");
    return false;
  }

  mprintf(0, "Video fullscreen system initialized.\n");

  return true;
}

//	closes fullscreen system
void ddvidfs_Close() {
  if (DDVideo_info.lpDDSFront)
    DDVideo_info.lpDDSFront->Release();

  if (DDVideo_info.lpDD) {
    DDVideo_info.lpDD->RestoreDisplayMode();
    DDVideo_info.lpDD->SetCooperativeLevel(NULL, DDSCL_NORMAL);
    DDVideo_info.lpDD->Release();
    DDVideo_info.lpDD = NULL;
  }

  DDVideo_info.lpDDSFront = NULL;
  DDVideo_info.lpDDSBack = NULL;
  DDVideo_info.hWnd = NULL;
  DDVideo_info.nDDModes = 0;
}

//	uses direct draw.  if paged, allows frame buffer access.
bool ddvidfs_SetVideoMode(int w, int h, int color_depth, bool paged) {
  HRESULT hres;
  DDSCAPS ddscaps;
  DDSURFACEDESC ddsd;
  int i, mode;
  bool found_mode;

  mode = 0;
  found_mode = false;

  //	find closest match for video mode.
  for (i = 0; i < DDVideo_info.nDDModes; i++) {
    if (color_depth == (int)DDVideo_info.DDModes[i].ddpfPixelFormat.dwRGBBitCount) {
      if (DDVideo_info.DDModes[i].dwWidth >= (DWORD)w && DDVideo_info.DDModes[mode].dwWidth < (DWORD)w)
        if (DDVideo_info.DDModes[i].dwHeight >= (DWORD)h && DDVideo_info.DDModes[mode].dwHeight < (DWORD)h) {
          mode = i;
          found_mode = true;
        }
    }
  }

  if (!found_mode) {
    //	we couldn't find a mode, error!
    return false;
  }

  if (DDVideo_info.curmode != mode) {

    //	mode should contain the video mode.
    hres = DDVideo_info.lpDD->SetDisplayMode(DDVideo_info.DDModes[mode].dwWidth, DDVideo_info.DDModes[mode].dwHeight,
                                             DDVideo_info.DDModes[mode].ddpfPixelFormat.dwRGBBitCount);
    ASSERT(DDVideo_info.DDModes[mode].ddpfPixelFormat.dwRGBBitCount >= BPP_16);
    if (hres != DD_OK)
      Error("Unable to set DirectDraw display mode. (%d)", LOWORD(hres));
  }

  DDVideo_info.curmode = mode;

  //	if not paged, then this is a single paged system (no lfb access, good for opengl)
  if (!paged)
    return true;

  //	now create surface, dependant on whether an extra page was requested
  memset(&ddsd, 0, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);

  if (paged) {
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwBackBufferCount = 1;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
  } else {
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
  }

  hres = DDVideo_info.lpDD->CreateSurface(&ddsd, &DDVideo_info.lpDDSFront, NULL);
  if (hres != DD_OK)
    Error("Unable to capture DirectDraw display surface. (%d)", LOWORD(hres));

  if (paged) {
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

    hres = DDVideo_info.lpDDSFront->GetAttachedSurface(&ddscaps, &DDVideo_info.lpDDSBack);
    if (hres != DD_OK) {
      mprintf(0, "Unable to capture DirectDraw display back surface (%d)", LOWORD(hres));
      return false;
    }
  } else {
    DDVideo_info.lpDDSBack = NULL;
  }

  return true;
}

//	closes video mode for fs
void ddvidfs_CloseVideo() {
  //	uninitialize old screen
  if (DDVideo_info.lpDDSFront) {
    DDVideo_info.lpDDSFront->Release();
    DDVideo_info.lpDDSFront = NULL;
    DDVideo_info.lpDDSBack = NULL;
  }
}

//	flips screen if there's a back buffer
void ddvidfs_VideoFlip() {
  if (DDVideo_info.lpDDSBack)
    DDVideo_info.lpDDSFront->Flip(NULL, DDFLIP_WAIT);
}

//	returns the directdraw object
uint32_t ddvidfs_GetDirectDrawObject() { return (uint32_t)DDVideo_info.lpDD; }

//	DirectDraw Display mode enumeration callback
HRESULT WINAPI DDEnumModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext) {
  if (DDVideo_info.nDDModes < VM_MAX_MODES) {
    memcpy(&DDVideo_info.DDModes[DDVideo_info.nDDModes], lpDDSurfaceDesc, sizeof(DDSURFACEDESC));
    DDVideo_info.nDDModes++;
  }

  return DDENUMRET_OK;
}
