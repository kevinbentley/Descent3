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

 * $Logfile: /DescentIII/Main/2dlib/pen.cpp $
 * $Revision: 5 $
 * $Date: 12/19/97 5:28p $
 * $Author: Samir $
 *
 * line and rectangle drawing
 *
 * $Log: /DescentIII/Main/2dlib/pen.cpp $
 *
 * 5     12/19/97 5:28p Samir
 * Took out old rasterization code.  Moved to renderer library.
 *
 * 4     12/19/97 5:23p Samir
 * Cleaned up a lot of code to call renderer code.
 *
 * 3     12/19/97 12:31p Samir
 * Better renderer support.
 *
 * 21    6/16/97 4:45p Samir
 * Added rendering line hooks.
 *
 * 20    6/12/97 6:29p Samir
 *
 * 19    6/06/97 12:18p Samir
 * OpenGL HACKS to call renderer for some drawing functions.  Must fix.
 *
 * 18    5/29/97 5:59p Samir
 * Convert clipping from fix math to float math.
 *
 * 17    4/11/97 3:56 PM Jeremy
 * replaced calls of ddgr_H/Vline to gr_h/vline
 *
 * 16    4/08/97 12:53p Samir
 * Fixed  hline clipping fuckup.
 *
 * 15    4/08/97 11:30a Jason
 * made circles not draw if they are touching the edge ofthe viewport
 *
 * 14    4/08/97 10:42a Jason
 * fixed bug with hline
 *
 * 13    4/01/97 4:37p Samir
 * Simply better circle functions using viewport line and pixel functions.
 * made an hline function that clips and a setpixel function that clips.
 *
 * 12    4/01/97 3:56p Samir
 * Cheap clipping for scanlines.  Should fix this so it's cleaner.
 *
 * 11    4/01/97 1:51p Samir
 * Fixed clipping of circles.
 *
 * 10    4/01/97 1:40p Samir
 * Circle functions
 *
 * 9     3/27/97 11:11a Samir
 * Moved code from ddgr library to 2dlib because it was ANSI compliant and
 * should work on all systems
 *
 * 8     2/28/97 2:52 PM Jeremy
 * removed inline declaration of grViewport::clip_line
 *
 * 7     2/27/97 6:14p Samir
 * moved higher level ddgr pen code to this library.
 *
 * 6     2/07/97 6:04p Matt
 * Renamed vm_FixMulDiv() to FixMulDiv()
 *
 * 5     2/04/97 11:14a Samir
 * Improved clipping system by adding a separate clipport based off of the
 * viewport's rectangle in it's parent surface
 *
 * $NoKeywords: $
 */

#include "lib2d.h"
#include "pserror.h"
#include "renderer.h"

#define CLIP_LEFT (vp_InitLeft + vp_Left)
#define CLIP_TOP (vp_InitTop + vp_Top)
#define CLIP_RIGHT (vp_InitLeft + vp_Right)
#define CLIP_BOTTOM (vp_InitTop + vp_Bottom)

void grViewport::hline(ddgr_color col, int x1, int x2, int y1) {
  ASSERT(vp_Locked);

  x1 = global_x(x1);
  y1 = global_y(y1);
  x2 = global_x(x2);

  if (x1 > x2) {
    int t = x2;
    x2 = x1;
    x1 = t;
  }

  if (y1 < CLIP_TOP)
    return;
  if (y1 > CLIP_BOTTOM)
    return;
  if (x1 > CLIP_RIGHT)
    return;
  if (x2 < CLIP_LEFT)
    return;
  if (x1 < CLIP_LEFT)
    x1 = CLIP_LEFT;
  if (x2 > CLIP_RIGHT)
    x2 = CLIP_RIGHT;

  rend_SetFlatColor(col);
  rend_DrawLine(x1, y1, x2, y1);
}

//	grViewport::line
//		draws a clipped line

void grViewport::line(ddgr_color color, int x1, int y1, int x2, int y2) {
  int xa, ya, xb, yb;
  ASSERT(vp_Locked);

  xa = global_x(x1);
  ya = global_y(y1);
  xb = global_x(x2);
  yb = global_y(y2);

  rend_SetFlatColor(color);
  rend_DrawLine(x1, y1, x2, y2);
}

void grViewport::rect(ddgr_color color, int l, int t, int r, int b) {
  ASSERT(vp_Locked);

  l = global_x(l);
  t = global_y(t);
  r = global_x(r);
  b = global_y(b);

  rend_SetFlatColor(color);
  rend_DrawLine(l, t, r, t);
  rend_DrawLine(r, t, r, b);
  rend_DrawLine(l, b, r, b);
  rend_DrawLine(l, t, l, b);
}

void grViewport::fillrect(ddgr_color color, int l, int t, int r, int b) {
  ASSERT(vp_Locked);

  l = global_x(l);
  t = global_y(t);
  r = global_x(r);
  b = global_y(b);

  rend_FillRect(color, l, t, r, b);
}

void grViewport::circle(ddgr_color col, int xc, int yc, int r) {
  ASSERT(vp_Locked);

  xc = global_x(xc);
  yc = global_y(yc);

  rend_SetFlatColor(col);
  rend_DrawCircle(xc, yc, r);
}

void grViewport::fillcircle(ddgr_color col, int xc, int yc, int r) {
  ASSERT(vp_Locked);

  xc = global_x(xc);
  yc = global_y(yc);

  rend_FillCircle(col, xc, yc, r);
}
