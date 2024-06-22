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

 * $Logfile: /DescentIII/Main/ddgr_win32/ddgrWin32DX.cpp $
 * $Revision: 2 $
 * $Date: 9/12/97 4:13p $
 * $Author: Samir $
 *
 *	DirectX implementation of DDGR library.
 *
 * $Log: /DescentIII/Main/ddgr_win32/ddgrWin32DX.cpp $
 *
 * 2     9/12/97 4:13p Samir
 * Added some private data access functions and more DirectX
 * functionality.
 *
 * $NoKeywords: $
 */

#include "ddgrWin32.h"
#include "ddgrWin32DX.h"
#include "winapp.h"
#include "mono.h"
#include "pserror.h"

tDDGRDXInternalData DDGR_DX_lib_data;

//	Initializes DX subsystem
bool ddgr_dx_Init() {
  DX_DATA(hPrimaryWnd) = Win32App()->windowHandle();

  DX_DATA(lpDD) = NULL;

  //	Initialize DirectDraw system if we're going fullscreen, and GDIX system
  HRESULT hres;

  hres = DirectDrawCreate(NULL, &DX_DATA(lpDD), NULL);
  if (hres != DD_OK) {
    ddgr_PushError("Failure to initialize DirectDraw driver (%d)", LOWORD(hres));
    return false;
  }

  hres =
      DX_DATA(lpDD)->SetCooperativeLevel(DX_DATA(hPrimaryWnd), DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);

  if (hres != DD_OK) {
    ddgr_PushError("Failed to set DirectDraw fullscreen access level (%d)", LOWORD(hres));
    return false;
  }

  DX_DATA(vidrefs) = 0; // reset video reference count.
  DX_DATA(init) = true;

  mprintf(0, "DX system initialized.\n");

  return true;
}

//	Closes DX subsystem
void ddgr_dx_Close() {
  ASSERT(DX_DATA(vidrefs) == 0);

  if (DX_DATA(lpDD)) {
    DX_DATA(lpDD)->RestoreDisplayMode();
    DX_DATA(lpDD)->Release();
  }
  DX_DATA(lpDD) = NULL;
  DX_DATA(hPrimaryWnd) = NULL;
  DX_DATA(init) = false;

  mprintf(0, "DX system closed.\n");
}

//	Initializes the display for use with the DX subsystem.
bool ddgr_dx_surf_InitVideo(ddgr_surface *sf) {
  tDXSurface *dxsf;
  DDSURFACEDESC ddsd;

  //	we need to create a primary surface from the display mode we set, and possibly a backbuffer if
  //	requested.
  if (DX_DATA(vidrefs) == 0) {
    HRESULT hres;
    DDSCAPS ddscaps;

    hres = DX_DATA(lpDD)->SetDisplayMode(sf->w, sf->h, sf->bpp);
    if (hres != DD_OK) {
      ddgr_PushError("Unable to set DirectDraw display mode (%d)\n", LOWORD(hres));
      return false;
    }

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwBackBufferCount = 1;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;

    hres = DX_DATA(lpDD)->CreateSurface(&ddsd, &DX_DATA(vidsurf.lpdds), NULL);
    if (hres != DD_OK) {
      ddgr_PushError("Unable to capture DirectDraw display surface (%d)\n", LOWORD(hres));
      return false;
    }

    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

    hres = DX_DATA(vidsurf.lpdds)->GetAttachedSurface(&ddscaps, &DX_DATA(vidsurf.lpddsback));
    if (hres != DD_OK) {
      ddgr_PushError("Unable to capture DirectDraw display back surface (%d)\n", LOWORD(hres));
      return false;
    }
  }

  DX_DATA(vidrefs)++; // increment vidref count

  dxsf = new tDXSurface;
  dxsf->lpdds = DX_DATA(vidsurf.lpdds);

  // this means that we are capturing the screen, not creating a screen.
  //	get the screen's width and height and bitdepth
  if (sf->flags == 0) {
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    dxsf->lpdds->GetSurfaceDesc(&ddsd);
    sf->w = ddsd.dwWidth;
    sf->h = ddsd.dwHeight;
    sf->bpp = ddsd.ddpfPixelFormat.dwRGBBitCount;
  }

  //	we create a dummy surface for the screen's back buffer, or our accessable buffer
  //	specifying SURFFLAG_BACKBUFFER ensures that we create a GDI bitmap of size requested
  //	in 'sf' and it will be our renderable bitmap, or OUR primary render buffer
  if (sf->flags & SURFFLAG_BACKBUFFER) {
    //	set our front buffer to this newly created surface and delete the gdi bitmap object
    dxsf->lpddsback = DX_DATA(vidsurf.lpddsback);
    dxsf->backbuffer = true;
  } else {
    dxsf->lpddsback = NULL;
    dxsf->backbuffer = false;
  }

  sf->obj = (void *)dxsf;

  return true;
}

//	Deinitializes the video surface
void ddgr_dx_surf_CloseVideo(ddgr_surface *sf) {
  tDXSurface *bm = (tDXSurface *)sf->obj;

  ASSERT(DX_DATA(vidrefs) > 0);

  DX_DATA(vidrefs)--;
  if (DX_DATA(vidrefs) == 0) {
    DX_DATA(vidsurf.lpdds)->Release();
    DX_DATA(vidsurf.lpdds) = NULL;
    DX_DATA(vidsurf.lpddsback) = NULL;
  }

  delete bm;
}

//	flips the buffers in a surface.  really only useful for video screens
bool ddgr_dx_surf_FlipVideo(ddgr_surface *sf) {
  tDXSurface *bm = (tDXSurface *)sf->obj;
  HRESULT hres;

  if (bm->backbuffer && (sf->flags & SURFFLAG_BACKBUFFER)) {
    hres = bm->lpdds->Flip(NULL, 0);
    if (hres == DDERR_WASSTILLDRAWING || hres == DD_OK)
      return true;
    else
      return false;
  }

  return true;
}

/*	input:
                sf->name is optional.
                sf->w, sf->h, sf->bpp are mandatory
                sf->type and sf->flags are mandatory.
        output:
                sf->obj = surface object.
                sf->locks = 0
*/
bool ddgr_dx_surf_Create(ddgr_surface *sf) { return true; }

void ddgr_dx_surf_Destroy(ddgr_surface *sf) {}

/*	retrieves a pointer to surface memory.  allowed to lock one surface multiple times.
                ptr is the returned pointer to surface memory.  used to unlock surface also
                rowsize is the size in bytes of one row of memory.
*/
bool ddgr_dx_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize) {
  HRESULT hres;
  DDSURFACEDESC ddsd;
  tDXSurface *bm = (tDXSurface *)sf->obj;

  memset(&ddsd, 0, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);

  if (bm->backbuffer)
    hres = bm->lpddsback->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
  else
    hres = bm->lpdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);

  if (hres != DD_OK) {
    ddgr_PushError("Unable to set lock DirectDraw surface(%d)\n", LOWORD(hres));
    return false;
  }

  *rowsize = (int)ddsd.lPitch;
  *ptr = ddsd.lpSurface;

  return true;
}

bool ddgr_dx_surf_Unlock(ddgr_surface *sf, void *ptr) {
  HRESULT hres;
  tDXSurface *bm = (tDXSurface *)sf->obj;

  if (bm->backbuffer)
    hres = bm->lpddsback->Unlock(ptr);
  else
    hres = bm->lpdds->Unlock(ptr);

  if (hres != DD_OK) {
    ddgr_PushError("Unable to unlock DirectDraw surface(%d)\n", LOWORD(hres));
    return false;
  }

  return true;
}

//	attaches an OS handle to a surface
void ddgr_dx_surf_AttachHandle(ddgr_surface *sf, unsigned handle) {}

//	The only graphic primatives
//	clear
//	blt.
void ddgr_dx_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h) {
  HRESULT hres;
  DDBLTFX ddbltfx;
  tDXSurface *dbm = (tDXSurface *)dsf->obj;
  LPDIRECTDRAWSURFACE lpdds;
  RECT rect;

  lpdds = (dbm->backbuffer) ? dbm->lpddsback : dbm->lpdds;

  memset(&ddbltfx, 0, sizeof(DDBLTFX));
  ddbltfx.dwSize = sizeof(ddbltfx);
  ddbltfx.dwFillColor = RGB(DDGR_COLOR_RED(col), DDGR_COLOR_GREEN(col), DDGR_COLOR_BLUE(col));
  SetRect(&rect, l, t, l + w - 1, t + h - 1);

  hres = lpdds->Blt(&rect, // dest rect
                    NULL,  // src surface
                    NULL,  // src rect
                    DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
}

bool ddgr_dx_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh) {
  HRESULT hres;
  tDXSurface *sbm = (tDXSurface *)ssf->obj;
  tDXSurface *dbm = (tDXSurface *)dsf->obj;
  LPDIRECTDRAWSURFACE lpddsd;
  LPDIRECTDRAWSURFACE lpddss;
  RECT srect, drect;

  if (ssf->flags & SURFFLAG_BACKBUFFER)
    lpddss = sbm->lpddsback;
  else
    lpddss = sbm->lpdds;

  if (dsf->flags & SURFFLAG_BACKBUFFER)
    lpddsd = dbm->lpddsback;
  else
    lpddsd = dbm->lpdds;

  SetRect(&srect, sx, sy, sx + sw - 1, sy + sh - 1);
  SetRect(&drect, dx, dy, dx + sw - 1, dy + sh + 1);

  hres = lpddsd->Blt(&drect, lpddss, &srect, DDBLT_WAIT, NULL);
  if (hres != DD_OK) {
    ddgr_PushError("Unable to blt surface %s to DirectDraw surface %s(%d)\n", ssf->name, dsf->name, LOWORD(hres));
    return false;
  }

  return true;
}
