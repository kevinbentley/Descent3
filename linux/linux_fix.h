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

#ifndef __LINUX_FIX_H_
#define __LINUX_FIX_H_

#include <sys/stat.h>

#define LOKI_VERSION ""

#define HGLOBAL void *
#define SOCKET int

void GlobalFree(void *);
void *GlobalAlloc(int flags, int size);
void *GlobalLock(HGLOBAL hMem);
void Sleep(int millis);
char *strupr(char *string);

#define _stat stat

// Replace missing defines from stdlib.h
#define _MAX_PATH 260  /* max. length of full pathname*/
#define _MAX_FNAME 256 /* max. length of path component*/
#define _MAX_EXT 256   /* max. length of extension component*/
#if !defined(MAX_PATH)
#define MAX_PATH _MAX_PATH
#endif
// _cdecl replacement
#define __cdecl __attribute__((cdecl))
// _stdcall replacement
#define _stdcall __attribute__((stdcall))

#define stricmp(a, b) strcasecmp(a, b)
#define strnicmp(a, b, c) strncasecmp(a, b, c)
#define _chmod(a, b) chmod(a, b)
#if defined(__aarch64__)
#define _finite(a) isfinite(a)
#else
#define _finite(a) finite(a)
#endif

#endif
