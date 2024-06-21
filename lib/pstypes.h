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

#ifndef _TYPES_H
#define _TYPES_H

#include <cstdlib>
#include <cstdint>

#if defined(__LINUX__) || defined(ANDROID)
#include "linux_fix.h"
#endif

// The maximum length for a file name, including extension.  It *does not* include the
// terminating NULL, so a buffer to hold a filename needs to be PSFILENAME_LEN+1 bytes long.
#define PSFILENAME_LEN 35

// The maximum length of a path (or path+filename).  The seems (from looking at the code) to
// include the terminating NULL. lengthened to 512 to prevent problems with some long pathnames.
#define PSPATHNAME_LEN _MAX_PATH

#if !defined(__APPLE__)
#define HOST_BIGENDIAN @HOST_BIGENDIAN @
#else
#if defined(__BIG_ENDIAN__)
#define HOST_BIGENDIAN 1
#define MACOSXPPC 1
#elif defined(__LITTLE_ENDIAN__)
#define HOST_BIGENDIAN 0
#define MACOSX86 1
#else
#error "Unknown HOST_BIGENDIAN!"
#endif
#endif

#endif
