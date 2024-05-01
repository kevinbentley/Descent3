/*
 * Copyright (C) 2002-2024 D2X Project
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

/*
 *
 * INTERNAL header - not to be included outside of libmve
 *
 */

#ifndef _DECODERS_H
#define _DECODERS_H

extern int g_width, g_height;
extern void *g_vBackBuf1, *g_vBackBuf2;

extern void decodeFrame8(unsigned char *pFrame, unsigned char *pMap, int mapRemain, unsigned char *pData,
                         int dataRemain);
extern void decodeFrame16(unsigned char *pFrame, unsigned char *pMap, int mapRemain, unsigned char *pData,
                          int dataRemain);

#endif // _DECODERS_H
