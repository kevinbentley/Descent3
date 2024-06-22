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

 * $Logfile: /DescentIII/Main/ddvid_win32/vidWin32Win.cpp $
 * $Revision: 5 $
 * $Date: 10/02/98 11:15a $
 * $Author: Jeff $
 *
 *	Windowed version of video library.
 *
 * $Log: /DescentIII/Main/ddvid_win32/vidWin32Win.cpp $
 *
 * 5     10/02/98 11:15a Jeff
 * added HBITMAP, HFONT and HBRUSH type casts where needed to satisfy the
 * compiler
 *
 * 4     6/04/98 7:04p Samir
 * assert res-switch to be at least 16bpp.
 *
 * 3     4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 2     3/06/98 2:22p Samir
 * Added fullscreen windowed version.
 *
 * 1     12/23/97 5:46p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include "ddvidlib.h"
#include "pserror.h"
#include "winapp.h"

//////////////////////////////////////////////////////////////////////////////
//	Variables

struct tDIBHeader // used to create and manipulate DIBs (a 16/32BPP surface only)
{
  BITMAPINFOHEADER bmi;
  DWORD red_mask;
  DWORD green_mask;
  DWORD blue_mask;
};

//////////////////////////////////////////////////////////////////////////////
//	Functions

// inits fullscreen system
bool ddvidwin_Init() {
  // grab all device modes for the current display device.
  unsigned i = 0;
  DEVMODE devmode;

  while (EnumDisplaySettings(NULL, i, &devmode)) {
    HDC hdc = CreateCompatibleDC(NULL);

    if (devmode.dmBitsPerPel == (uint32_t)GetDeviceCaps(hdc, BITSPIXEL) &&
        devmode.dmPelsWidth == (uint32_t)GetSystemMetrics(SM_CXSCREEN) &&
        devmode.dmPelsHeight == (uint32_t)GetSystemMetrics(SM_CYSCREEN)) {
      if (Win32App()->NT() && devmode.dmDisplayFrequency == (uint32_t)GetDeviceCaps(hdc, VREFRESH))
        DDVideo_info.gdi.olddevmode = i;
      else if (!Win32App()->NT())
        DDVideo_info.gdi.olddevmode = i;
    }

    DeleteDC(hdc);
    i++;
  }
  DDVideo_info.gdi.ndevmodes = i;

  DDVideo_info.gdi.curdevmode = DDVideo_info.gdi.olddevmode;

  return true;
}

//	closes windowed system
void ddvidwin_Close() {
  DEVMODE devmode;

  if (DDVideo_info.gdi.hBackDC) {
    DeleteDC(DDVideo_info.gdi.hBackDC);
    DDVideo_info.gdi.hBackDC = NULL;
  }

  if (DDVideo_info.gdi.hBackBmp) {
    DeleteObject(DDVideo_info.gdi.hBackBmp);
    DDVideo_info.gdi.hBackBmp = NULL;
  }

  //	if the current display mode is different than the default one, then restore default display mode
  if (DDVideo_info.gdi.olddevmode != DDVideo_info.gdi.curdevmode) {
    LONG lres;

    EnumDisplaySettings(NULL, DDVideo_info.gdi.olddevmode, &devmode);

    devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFLAGS | DM_DISPLAYFREQUENCY;

    lres = ChangeDisplaySettings(&devmode, 0);
    ASSERT(lres == DISP_CHANGE_SUCCESSFUL);
  }
}

//	creates an offscreen back bitmap if needed. otherwise doesn't do a thing really
bool ddvidwin_SetVideoMode(int w, int h, int color_depth, bool paged, bool reschange) {
  HDC hdc;
  int i;

  DDVideo_info.hVidWnd = DDVideo_info.hWnd;

  //	if resolution change, then do it.
  if (reschange) {
    int mode = 0;
    bool found_mode = false;
    DEVMODE devmode, curdevmode;

    EnumDisplaySettings(NULL, mode, &curdevmode);
    curdevmode.dmPelsWidth = 0;
    curdevmode.dmPelsHeight = 0;
    curdevmode.dmBitsPerPel = 0;

    // check for display mode query match.
    for (i = 0; i < DDVideo_info.gdi.ndevmodes; i++) {
      EnumDisplaySettings(NULL, i, &devmode);

      if (color_depth == (int)devmode.dmBitsPerPel) {
        if ((int)devmode.dmPelsWidth >= w && (int)curdevmode.dmPelsWidth < w)
          if ((int)devmode.dmPelsHeight >= h && (int)curdevmode.dmPelsHeight < h) {
            mode = i;
            found_mode = true;
            EnumDisplaySettings(NULL, mode, &curdevmode);
          }
      }
    }

    if (!found_mode) {
      //	we couldn't find a mode, error!
      Error("Unable to set Win32 device display mode (%dx%dx%d).", w, h, color_depth);
    }

    if (DDVideo_info.gdi.curdevmode != mode) {
      EnumDisplaySettings(NULL, mode, &devmode);

      devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFLAGS | DM_DISPLAYFREQUENCY;

      ASSERT(devmode.dmBitsPerPel >= BPP_16);
      LONG lres = ChangeDisplaySettings(&devmode, 0);
      ASSERT(lres == DISP_CHANGE_SUCCESSFUL);
      DDVideo_info.gdi.curdevmode = mode;
    }
  }

  //	create a DC for blting and back buffer creation.
  hdc = CreateCompatibleDC(NULL);
  if (hdc == NULL) {
    Error("Unable to create offscreen device context (%x).", GetLastError());
    return false;
  }

  DDVideo_info.gdi.hBackDC = hdc;
  DDVideo_info.gdi.w = w;
  DDVideo_info.gdi.h = h;
  DDVideo_info.gdi.color_depth = color_depth;

  //	create offscreen back buffer if paged mode is requested.
  if (paged) {
    int nw = w;
    if (nw % 4)
      nw = ((w / 4) * 4) + 4;
    tDIBHeader header;

    if (color_depth == BPP_16) {
      header.bmi.biSize = sizeof(BITMAPINFOHEADER);
      header.bmi.biWidth = nw;
      header.bmi.biHeight = -h; // Always a top down bitmap!!
      header.bmi.biPlanes = 1;
      header.bmi.biBitCount = BPP_16;
      header.bmi.biCompression = BI_BITFIELDS;
      header.bmi.biSizeImage = 0;
      header.bmi.biXPelsPerMeter = 0;
      header.bmi.biYPelsPerMeter = 0;
      header.bmi.biClrUsed = 0;
      header.bmi.biClrImportant = 0;

      //	setup RGB bit masks
      header.red_mask = 0x7c00;
      header.green_mask = 0x03e0;
      header.blue_mask = 0x001f;
      DDVideo_info.gdi.pitch = nw * 2;
    }

    DDVideo_info.gdi.hBackBmp = CreateDIBSection(DDVideo_info.gdi.hBackDC, (BITMAPINFO *)&header, DIB_RGB_COLORS,
                                                 (void **)&DDVideo_info.gdi.data, NULL, 0);

    if (!DDVideo_info.gdi.hBackBmp) {
      Error("CreateDIBSection failed (%x).", GetLastError());
    }
  }

  return true;
}

//	closes video mode for fs
void ddvidwin_CloseVideo() {
  //	delete DC if it exists.
  if (DDVideo_info.gdi.hBackDC) {
    DeleteDC(DDVideo_info.gdi.hBackDC);
    DDVideo_info.gdi.hBackDC = NULL;
  }

  //	destroy old back bitmap
  if (DDVideo_info.gdi.hBackBmp) {
    DeleteObject(DDVideo_info.gdi.hBackBmp);
    DDVideo_info.gdi.hBackBmp = NULL;
  }
}

//	retrieves screen information for windowed version
void ddvidwin_GetVideoProperties(int *w, int *h, int *color_depth) {
  *w = DDVideo_info.gdi.w;
  *h = DDVideo_info.gdi.h;
  *color_depth = DDVideo_info.gdi.color_depth;
}

//	flips screen if there's a back buffer
void ddvidwin_VideoFlip() {
  HBITMAP old_bmp, h_sbm;
  HDC hdc_dest;
  RECT rect;
  int dw, dh;

  ASSERT(DDVideo_info.hVidWnd != NULL);

  //	don't give an error if there's no backbuffer.
  if (!DDVideo_info.gdi.hBackBmp)
    return;

  h_sbm = DDVideo_info.gdi.hBackBmp;

  hdc_dest = GetDC(DDVideo_info.hVidWnd);
  GetClientRect(DDVideo_info.hVidWnd, &rect);

  dw = rect.right - rect.left;
  dh = rect.bottom - rect.top;

  old_bmp = (HBITMAP)SelectObject(DDVideo_info.gdi.hBackDC, h_sbm);

  BOOL bltres = BitBlt(hdc_dest, 0, 0, dw, dh, DDVideo_info.gdi.hBackDC, 0, 0, SRCCOPY);

  SelectObject(DDVideo_info.gdi.hBackDC, old_bmp);

  ReleaseDC(DDVideo_info.hVidWnd, hdc_dest);
}
