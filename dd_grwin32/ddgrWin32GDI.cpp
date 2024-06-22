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

 * $Logfile: /DescentIII/Main/ddgr_win32/ddgrWin32GDI.cpp $
 * $Revision: 10 $
 * $Date: 10/02/98 11:15a $
 * $Author: Jeff $
 *
 *	DDGR v2.0 GDI(X) implementation
 *
 * $Log: /DescentIII/Main/ddgr_win32/ddgrWin32GDI.cpp $
 *
 * 10    10/02/98 11:15a Jeff
 * added HBITMAP, HFONT and HBRUSH type casts where needed to satisfy the
 * compiler
 *
 * 9     6/02/98 12:46p Samir
 * removed restriction of ddgr system when going to true-color
 * resolutions.
 *
 * 8     4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 7     4/09/98 11:00a Samir
 * took out assertion in ddgr_gdi_Close that caused errors and assertions
 * to 'crap' out.
 *
 * 6     11/14/97 12:32p Samir
 * DirectDraw works under GDIX windowed subsystem (NORMAL cooperative
 * mode).
 *
 * 5     9/23/97 12:15p Jason
 * fixed color bug
 *
 * 4     9/12/97 4:13p Samir
 * Added some private data access functions and more DirectX
 * functionality.
 *
 * 3     8/12/97 10:43p Matt
 * Fixed RGB conversion bug
 *
 * 5     6/16/97 4:46p Samir
 * OpenGL works in window too.
 *
 * 4     6/13/97 3:01p Samir
 * Fixed flip assertions and OpenGL imp.
 *
 * 3     6/13/97 1:24p Samir
 * FlipVideo doesn't flip when no backbuffer, so just do nothing.
 *
 * 2     6/13/97 12:24p Samir
 * Fixed OpenGLDC hack and removed assert in lock if data ptr = NULL
 *
 * 1     6/12/97 6:33p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include "ddgrWin32.h"
#include "ddgrWin32GDI.h"
#include "winapp.h"
#include "mono.h"
#include "pserror.h"
#include "gr.h"

/*	Global Library Data
 */
tDDGRGDIInternalData DDGR_GDI_lib_data;

/*	Primary Interface Functions
 */

//	---------------------------------------------------------------------------
//	initializes the objects needed to use GDI

bool ddgr_gdi_Init(bool fullscreen, bool ddraw) {
  HRESULT hres;

  GDI_DATA(fullscreen) = fullscreen;
  GDI_DATA(hPrimaryWnd) = Win32App()->windowHandle();

  GDI_DATA(lpDD) = NULL;
  if (ddraw) {
    hres = DirectDrawCreate(NULL, &GDI_DATA(lpDD), NULL);
    if (hres != DD_OK) {
      ddgr_PushError("Failure to initialize DirectDraw driver (%d)", LOWORD(hres));
      return false;
    }
  }

  //	Initialize DirectDraw exclusive system if we're going fullscreen, and GDIX system
  if (GDI_DATA(fullscreen)) {
    if (ddraw) {
      hres = GDI_DATA(lpDD)->SetCooperativeLevel(GDI_DATA(hPrimaryWnd),
                                                 DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);

      if (hres != DD_OK) {
        ddgr_PushError("Failed to set DirectDraw fullscreen access level (%d)", LOWORD(hres));
        return false;
      }
    } else {
      // grab all device modes for the current display device.
      unsigned i;
      for (i = 0; i < GDI_MAX_DEVMODES; i++) {
        if (EnumDisplaySettings(NULL, i, &GDI_DATA(devmodes[i])) == FALSE) {
          break;
        }
        HDC hdc = GetDC(GDI_DATA(hPrimaryWnd));

        if (GDI_DATA(devmodes[i].dmBitsPerPel) == (uint32_t)GetDeviceCaps(hdc, BITSPIXEL) &&
            GDI_DATA(devmodes[i].dmPelsWidth) == (uint32_t)GetDeviceCaps(hdc, HORZRES) &&
            GDI_DATA(devmodes[i].dmPelsHeight) == (uint32_t)GetDeviceCaps(hdc, VERTRES))
          GDI_DATA(olddispmode) = i;

        ReleaseDC(GDI_DATA(hPrimaryWnd), hdc);
      }
    }

    GDI_DATA(ddraw) = ddraw;
  } else {
    if (ddraw) {
      hres = GDI_DATA(lpDD)->SetCooperativeLevel(GDI_DATA(hPrimaryWnd), DDSCL_NORMAL);
      if (hres != DD_OK) {
        ddgr_PushError("Failed to set DirectDraw normal access level (%d)", LOWORD(hres));
        return false;
      }
    }
  }

  GDI_DATA(hOffscreenDC) = NULL;
  GDI_DATA(vidrefs) = 0; // reset video reference count.
  GDI_DATA(init) = true;

  mprintf(0, "GDI system initialized.\n");

  return true;
}

//	---------------------------------------------------------------------------
//	Deinitialized GDI objects

void ddgr_gdi_Close() {
  if (GDI_DATA(hOffscreenDC)) {
    DeleteDC(GDI_DATA(hOffscreenDC));
  }

  if (GDI_DATA(fullscreen)) {
    if (GDI_DATA(ddraw)) {
      //	For full screen, deinitialize directdraw/
      if (GDI_DATA(lpDD)) {
        GDI_DATA(lpDD)->RestoreDisplayMode();
        GDI_DATA(lpDD)->Release();
      }
      GDI_DATA(lpDD) = NULL;
    } else {
      //	do a ChangeDisplaySettings to old mode.
      LONG lres;
      GDI_DATA(devmodes[GDI_DATA(olddispmode)]).dmFields =
          DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFLAGS | DM_DISPLAYFREQUENCY;

      lres = ChangeDisplaySettings(&GDI_DATA(devmodes[GDI_DATA(olddispmode)]), 0);
      ASSERT(lres == DISP_CHANGE_SUCCESSFUL);
    }
  }

  GDI_DATA(hPrimaryWnd) = NULL;
  GDI_DATA(init) = false;

  mprintf(0, "GDI system closed.\n");
}

//	---------------------------------------------------------------------------
//	Initializes the video surface for blting
//	note that is the surface specified is a back buffer by sf->flags, then we need
//	to create a GDI bitmap for the back buffer, and our visible screen is the front buffer

bool ddgr_gdi_surf_InitVideo(ddgr_surface *sf) {
  tGDISurface *gdisf, *gdisf2;

  //	we need to create a DC for our GDI bitmaps if this is first ref to video surface.
  if (GDI_DATA(vidrefs) == 0) {
    //	if we are in fullscreen, do display mode change
    HDC hdc;

    if (GDI_DATA(fullscreen)) {
      if (GDI_DATA(ddraw)) {
        HRESULT hres;

        hres = GDI_DATA(lpDD)->SetDisplayMode(sf->w, sf->h, sf->bpp);
        if (hres != DD_OK) {
          ddgr_PushError("Unable to set DirectDraw display mode in fullscreen (%d)\n", LOWORD(hres));
          return false;
        }
      } else {
        // grab all device modes for the current display device.
        unsigned i;
        for (i = 0; i < GDI_MAX_DEVMODES; i++) {
          LONG lres;
          if ((int)GDI_DATA(devmodes[i].dmBitsPerPel) == sf->bpp && (int)GDI_DATA(devmodes[i].dmPelsWidth) == sf->w &&
              (int)GDI_DATA(devmodes[i].dmPelsHeight) == sf->h) {
            //	do a ChangeDisplaySettings to old mode.
            GDI_DATA(devmodes[i]).dmFields =
                DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFLAGS | DM_DISPLAYFREQUENCY;

            lres = ChangeDisplaySettings(&GDI_DATA(devmodes[i]), 0);
            ASSERT(lres == DISP_CHANGE_SUCCESSFUL);
            break;
          }
        }
      }
    }
    //	HACKS FOR OPENGL, WILL CHANGE SOON.
    hdc = CreateCompatibleDC(NULL);
    if (hdc == NULL) {
      ddgr_PushError("Unable to create offscreen device context (%x).", GetLastError());
      return false;
    }
    GDI_DATA(hOffscreenDC) = hdc;
  }

  GDI_DATA(vidrefs)++; // increment vidref count

  gdisf = new tGDISurface;
  gdisf->hbm = NULL;
  gdisf->data = NULL;
  gdisf->rowsize = NULL;
  gdisf->hwnd = NULL;

  // this means that we are capturing the screen, not creating a screen.
  //	get the screen's width and height and bitdepth
  if (sf->flags == 0) {
    sf->w = (int)GetDeviceCaps(GDI_DATA(hOffscreenDC), HORZRES);
    sf->h = (int)GetDeviceCaps(GDI_DATA(hOffscreenDC), VERTRES);
    sf->bpp = (int)GetDeviceCaps(GDI_DATA(hOffscreenDC), BITSPIXEL);
  }

  HDC hdc = GetDC(NULL);
  int tbpp = GetDeviceCaps(hdc, BITSPIXEL);
  ReleaseDC(NULL, hdc);

  if (tbpp < sf->bpp) {
    ddgr_PushError("Desktop color depth must be set to a %d-bit color mode or greater.\n", sf->bpp);
    return false;
  }

  //	we create a dummy surface for the screen's back buffer, or our accessable buffer
  //	specifying SURFFLAG_BACKBUFFER ensures that we create a GDI bitmap of size requested
  //	in 'sf' and it will be our renderable bitmap, or OUR primary render buffer
  if (sf->flags & SURFFLAG_BACKBUFFER) {
    ddgr_surface back_sf;
    back_sf.w = sf->w;
    back_sf.h = sf->h;
    back_sf.bpp = sf->bpp;
    back_sf.type = SURFTYPE_GENERIC;

    if (!ddgr_gdi_surf_Create(&back_sf)) {
      ddgr_PushError((0, "Failed to create back buffer <%s>", sf->name));
      delete gdisf;
      return false;
    }

    //	set our front buffer to this newly created surface and delete the gdi bitmap object
    gdisf2 = (tGDISurface *)back_sf.obj;
    gdisf->hbm = gdisf2->hbm;
    gdisf->data = gdisf2->data;
    gdisf->rowsize = gdisf2->rowsize;
    gdisf->backbuffer = true;
    delete gdisf2;
  } else {
    gdisf->hbm = NULL; // this is really just the screen.
    gdisf->backbuffer = false;
  }

  gdisf->hwnd = GDI_DATA(hPrimaryWnd);

  sf->obj = (void *)gdisf;

  return true;
}

//	---------------------------------------------------------------------------
//	deinitializes the DC created in InitVideo

void ddgr_gdi_surf_CloseVideo(ddgr_surface *sf) {
  tGDISurface *bm = (tGDISurface *)sf->obj;

  ASSERT(GDI_DATA(vidrefs) > 0);

  GDI_DATA(vidrefs)--;
  if (GDI_DATA(vidrefs) == 0) {
    if (GDI_DATA(fullscreen)) {
    }
    //	HACK for OPENGL support.
    DeleteDC(GDI_DATA(hOffscreenDC));
  }

  if (sf->flags & SURFFLAG_BACKBUFFER)
    DeleteObject(bm->hbm); // eliminate back buffer

  delete bm;
}

//	---------------------------------------------------------------------------
//	flip, does absolutely nothing

bool ddgr_gdi_surf_FlipVideo(ddgr_surface *sf) {
  HBITMAP old_bmp, h_sbm;
  HDC hdc_dest;
  RECT rect;
  int dw, dh;
  tGDISurface *bm = (tGDISurface *)sf->obj;

  ASSERT(bm->hwnd != NULL);

  //	don't give an error if there's no backbuffer.
  if (!bm->backbuffer)
    return true;

  h_sbm = bm->hbm;

  //	if we associated another window with our screem, then make sure their DC is the dest.
  //	other wise, use our base window's DC for destination, and select our front buffer as the
  //	source bitmap into our driver's DC.
  //	if (bm->hwnd == NULL) {
  //		hdc_dest = GetDC(GDI_DATA(hwnd));
  //		GetClientRect(GDI_DATA(hwnd),&rect);
  //	}
  //	else {
  hdc_dest = GetDC(bm->hwnd);
  GetClientRect(bm->hwnd, &rect);
  //	}

  dw = rect.right - rect.left;
  dh = rect.bottom - rect.top;

  old_bmp = (HBITMAP)SelectObject(GDI_DATA(hOffscreenDC), h_sbm);

  BOOL bltres = BitBlt(hdc_dest, 0, 0, dw, dh, GDI_DATA(hOffscreenDC), 0, 0, SRCCOPY);

  SelectObject(GDI_DATA(hOffscreenDC), old_bmp);

  ReleaseDC(bm->hwnd, hdc_dest);

  return (bltres) ? true : false;
}

//	---------------------------------------------------------------------------
//	Creates a GDI DIBitmap

bool ddgr_gdi_surf_Create(ddgr_surface *sf) {
  tGDISurface *bm;

  //	set up bitmap header
  int nw = sf->w;
  if (nw % 4)
    nw = ((sf->w / 4) * 4) + 4;

  bm = new tGDISurface;

  if (sf->bpp == BPP_8) {
    tDIBHeader8 header;

    header.bmi.biSize = sizeof(BITMAPINFOHEADER);
    header.bmi.biWidth = nw;
    header.bmi.biHeight = -sf->h; // Always a top down bitmap!!
    header.bmi.biPlanes = 1;
    header.bmi.biBitCount = sf->bpp;
    header.bmi.biCompression = BI_BITFIELDS;
    header.bmi.biSizeImage = 0;
    header.bmi.biXPelsPerMeter = 0;
    header.bmi.biYPelsPerMeter = 0;
    header.bmi.biClrUsed = 0;
    header.bmi.biClrImportant = 0;

    bm->hbm = CreateDIBSection(GDI_DATA(hOffscreenDC), (BITMAPINFO *)&header, DIB_RGB_COLORS, &bm->data, NULL, 0);
  } else {
    tDIBHeader header;
    header.bmi.biSize = sizeof(BITMAPINFOHEADER);
    header.bmi.biWidth = nw;
    header.bmi.biHeight = -sf->h; // Always a top down bitmap!!
    header.bmi.biPlanes = 1;
    header.bmi.biBitCount = sf->bpp;
    header.bmi.biCompression = BI_BITFIELDS;
    header.bmi.biSizeImage = 0;
    header.bmi.biXPelsPerMeter = 0;
    header.bmi.biYPelsPerMeter = 0;
    header.bmi.biClrUsed = 0;
    header.bmi.biClrImportant = 0;

    //	setup RGB bit masks
    if (sf->bpp == BPP_16) {
      header.red_mask = 0x7c00;
      header.green_mask = 0x03e0;
      header.blue_mask = 0x001f;
      bm->rowsize = nw * 2;
    } else if (sf->bpp == BPP_32 || sf->bpp == BPP_24) {
      header.red_mask = 0x00ff0000;
      header.green_mask = 0x0000ff00;
      header.blue_mask = 0x000000ff;
      bm->rowsize = nw * 4;
    }

    bm->hbm = CreateDIBSection(GDI_DATA(hOffscreenDC), (BITMAPINFO *)&header, DIB_RGB_COLORS, &bm->data, NULL, 0);
  }

  if (!bm->hbm) {
    ddgr_PushError("CreateDIBSection failed.");
    delete bm;
    return false;
  }
  bm->hwnd = NULL; // This is set by application

  sf->obj = (void *)bm;

  return true;
}

//	---------------------------------------------------------------------------
//	destroys the DIB allocated from create

void ddgr_gdi_surf_Destroy(ddgr_surface *sf) {
  tGDISurface *bm = (tGDISurface *)sf->obj;

  ASSERT(bm->hbm);

  DeleteObject(bm->hbm);

  delete bm;
}

//	Clears a GDI surface.
void ddgr_gdi_surf_Clear(ddgr_surface *dsf, ddgr_color col, int l, int t, int w, int h) {
  HBITMAP old_bmp;
  HBRUSH clr_brush, old_brush;
  HDC hdc;
  tGDISurface *dbm = (tGDISurface *)dsf->obj;
  int red, green, blue;
  ddgr_color color = col;

  switch (dsf->bpp) {
  case BPP_16:
    red = GR_COLOR_RED(color);
    green = GR_COLOR_GREEN(color);
    blue = GR_COLOR_BLUE(color);
    break;

  case BPP_32:
  case BPP_24:
    red = (color & 0x00ff0000) >> 16;
    green = (color & 0x0000ff00) >> 8;
    blue = (color & 0x000000ff);
    break;

  default:
    Int3(); // BAD
  }

  clr_brush = CreateSolidBrush(RGB((BYTE)red, (BYTE)green, (BYTE)blue));

  //	Are we clearing the primary display?
  if (dbm->hbm == NULL) {
    if (dbm->hwnd)
      hdc = GetDC(dbm->hwnd);
    else
      hdc = GetDC(GDI_DATA(hPrimaryWnd));
  } else {
    hdc = GDI_DATA(hOffscreenDC);
    old_bmp = (HBITMAP)SelectObject(hdc, dbm->hbm);
  }
  old_brush = (HBRUSH)SelectObject(hdc, clr_brush);

  Rectangle(hdc, l, t, l + w, t + h);

  SelectObject(hdc, old_brush);

  if (dbm->hbm == NULL) {
    // do if clearing was done on primary display.
    if (dbm->hwnd)
      ReleaseDC(dbm->hwnd, hdc);
    else
      ReleaseDC(GDI_DATA(hPrimaryWnd), hdc);
  } else {
    SelectObject(hdc, old_bmp);
  }

  DeleteObject(clr_brush);
}

//	---------------------------------------------------------------------------
//	blts one GDI bitmap to another.  Ability to blt directly to the screen is also
//	supported.

bool ddgr_gdi_surf_Blt(ddgr_surface *dsf, int dx, int dy, ddgr_surface *ssf, int sx, int sy, int sw, int sh) {
  HBITMAP old_bmp;
  HBITMAP old_bmp2;
  HDC hdc_dest;
  tGDISurface *dbm = (tGDISurface *)dsf->obj;
  tGDISurface *sbm = (tGDISurface *)ssf->obj;

  //	note that if our destination bitmap is the 'screen', then we use the GDI hwnd DC
  //	else we use the DC of the window specified in the destination.
  if (dbm->hbm == NULL) {
    if (dbm->hwnd == NULL)
      hdc_dest = GetDC(GDI_DATA(hPrimaryWnd));
    else
      hdc_dest = GetDC(dbm->hwnd);
  } else {
    hdc_dest = CreateCompatibleDC(NULL);
    old_bmp2 = (HBITMAP)SelectObject(hdc_dest, dbm->hbm);
  }

  old_bmp = (HBITMAP)SelectObject(GDI_DATA(hOffscreenDC), sbm->hbm);

  BOOL bltres = BitBlt(hdc_dest, dx, dy, sw, sh, GDI_DATA(hOffscreenDC), sx, sy, SRCCOPY);

  SelectObject(GDI_DATA(hOffscreenDC), old_bmp);

  if (dbm->hbm == NULL) {
    if (dbm->hwnd == NULL)
      ReleaseDC(GDI_DATA(hPrimaryWnd), hdc_dest);
    else
      ReleaseDC(dbm->hwnd, hdc_dest);
  } else {
    SelectObject(hdc_dest, old_bmp2);
    DeleteDC(hdc_dest);
  }

  return (bltres) ? true : false;
}

//	---------------------------------------------------------------------------
//	simply extracts the data and rowsize from the DDGR object in 'sf'

bool ddgr_gdi_surf_Lock(ddgr_surface *sf, void **ptr, int *rowsize) {
  tGDISurface *bm = (tGDISurface *)sf->obj;

  *ptr = bm->data;
  *rowsize = bm->rowsize;

  return true;
}

//	---------------------------------------------------------------------------
//	invalidates the data and rowsize in 'sf'

bool ddgr_gdi_surf_Unlock(ddgr_surface *sf, void *ptr) { return true; }

//	---------------------------------------------------------------------------
//	attaches a window handle to this surface. useful in clearing and blting to
//	screens.

void ddgr_gdi_surf_AttachHandle(ddgr_surface *sf, unsigned handle) {
  tGDISurface *gbm = (tGDISurface *)sf->obj;

  gbm->hwnd = (HWND)handle;
}
