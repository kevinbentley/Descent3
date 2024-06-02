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



#ifndef UIDRAW_H
#define UIDRAW_H

//	Graphics Primatives.
void ui_StartDraw(int left, int top, int right, int bottom);
void ui_EndDraw();

//	sets text clipping within the startdraw region
void ui_SetTextClip(int left, int top, int right, int bottom);
void ui_ResetTextClip();

//	draw primatives
void ui_DrawSetAlpha(uint8_t alpha);
void ui_DrawLine(ddgr_color color, int x1, int y1, int x2, int y2);
void ui_DrawBox(ddgr_color, int l, int t, int r, int b);
void ui_DrawLTBox(ddgr_color lt_col, ddgr_color rb_col, int l, int t, int r, int b);
void ui_DrawRect(ddgr_color, int l, int t, int r, int b);

//	draws all textures derived from ui_bm_handle.
void ui_DrawBitmap(UIBitmapItem *bi, int x, int y, uint8_t alpha);
int ui_GetBitmapWidth(UIBitmapItem *bi);
int ui_GetBitmapHeight(UIBitmapItem *bi);

//	sets font for text drawing.
void ui_DrawSetFont(int handle);
int ui_DrawGetFont();
int ui_GetFontHeight();
void ui_SetCharAlpha(uint8_t alpha);
int ui_GetTextWidth(const char *text);
int ui_GetTextHeight(const char *text);

#define UI_TEXTTYPE_SATURATE 1
#define UI_TEXTTYPE_SHADOW 2
void ui_DrawSetTextType(int type);

//	draws a line of text.
void ui_DrawString(ddgr_color col, int x, int y, const char *str);
void ui_DrawCenteredString(ddgr_color col, int xoff, int y, const char *str);

#endif
