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

 * $Logfile: /DescentIII/Main/lib/pstring.h $
 * $Revision: 3 $
 * $Date: 12/16/98 1:57p $
 * $Author: Samir $
 *
 * Safe string manipulation and creation functions
 *
 * $Log: /DescentIII/Main/lib/pstring.h $
 *
 * 3     12/16/98 1:57p Samir
 * Replaced CleanupString2 with CleanupStr
 *
 * 2     11/01/98 1:56a Jeff
 * added pstring.cpp/.h
 *
 * $NoKeywords: $
 */

#ifndef PSTRING_H
#define PSTRING_H

#include <cstring>

// CleanupStr
//    This function strips all leading and trailing spaces, keeping internal spaces. This goes for tabs too.
std::size_t CleanupStr(char *dest, const char *src, std::size_t destlen);

#endif
