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
*/

#ifndef __LNXDRAW_H_
#define __LNXDRAW_H_

// #include "dyna_xwin.h"
// #include "dyna_xext.h"

#include <SDL.h>

struct LnxVideoDesc {
  //	Display *dDisplay;  // Which X-Windows Display to use
  int nScreen; // Which X-Windows screen to use
};

struct LnxWindowDesc {
  uint32_t bpp;      // bits per pixel.
  uint32_t dwFlags;  // flags for window
  uint32_t dwWidth;  // width of the created window
  uint32_t dwHeight; // height of the created window
  uint32_t dwXPos;   // Top-Left X position
  uint32_t dwYPos;   // Top-Left Y position

  char *lpszName; // Window name
  //	Window *pre_created_window; // Window already created
  //	XVisualInfo pre_created_visinfo;
};
// #define LNXDRAWF_USEPRECREATEDWIN	0x01

struct LnxWindow {
  //	XSizeHints      *lpSizeHints;
  //	XWMHints        *lpWmHints;
  //	XClassHint      *lpClassHints;
  //	Visual          *lpXvisual;
  //	Window          wWindow;
  SDL_Surface *surface;
  //	bool            bHaveSharedMemory;
  bool bLocked;
  //	bool            WindowPreCreated;
  //	XVisualInfo     viVisualInfo;
  //	Colormap        cmColorMap;
  uint8_t *lpBuffer;
  //	GC              m_GC;
  //	XImage          *lpImage;
  //	XShmSegmentInfo shmInfo;
  uint32_t dwWidth;  // width of the created window
  uint32_t dwHeight; // height of the created window
  bool fullScreen;

  uint32_t lock_x, lock_y, lock_w, lock_h;
  uint8_t *lock_ptr;
};

//////////////////////
// LnxDraw_InitVideo
//////////////////////
// Initializes the Linux video system (for X-Windows)
//
// Returns:
//       0 : no error
//      -1 : invalid parameter
//      -2 : already initialized
int LnxDraw_InitVideo(LnxVideoDesc *ldesc);

/////////////////////////
// LnxDraw_CreateWindow
/////////////////////////

// Creates and displays a window
//
// Returns:
//       0 : no error (handle in lphandle)
//      -1 : invalid parameter
//      -2 : Display not opened
//      -3 : Out of memory
int LnxDraw_CreateWindow(LnxWindowDesc *ldesc, LnxWindow **lphandle);

//////////////////////////
// LnxDraw_DestroyWindow
//////////////////////////
// Closes and deletes a window
//
// Returns:
//       0 : no error
//      -1 : invalid parameter
int LnxDraw_DestroyWindow(LnxWindow *handle);

////////////////////////
// LnxDraw_LockSurface
////////////////////////
// Locks the window surface, giving you a pointer to write data to
//
// Returns:
//       true : success
//       false : error
bool LnxDraw_LockSurface(LnxWindow *wnd, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
                         uint8_t **ptr, int *pitch);

//////////////////////////
// LnxDraw_UnlockSurface
//////////////////////////
// Unlocks the window surface, blitting the buffer
//
void LnxDraw_UnlockSurface(LnxWindow *wnd, uint8_t *ptr);

////////////////////////////
/// LnxDraw_Blit
////////////////////////////
// Blits a buffer to the window
//
// Returns:
//       0 : no error
//      -1 : invalid parameter
//      -2 : unknown error
int LnxDraw_Blit(LnxWindow *wnd, uint8_t *ptr, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

////////////////////////
// LnxDraw_GetRGBMasks
////////////////////////
// Returns the RGB masks for the display
//
// Returns:
//       0 : no error
//      -1 : invalid parameters
int LnxDraw_GetRGBMasks(LnxWindow *wnd, uint32_t *r, uint32_t *g, uint32_t *b);

#endif
