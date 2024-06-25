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

 * $Logfile: /DescentIII/Main/misc/psrand.cpp $
 * $Revision: 2 $
 * $Date: 4/21/99 11:05a $
 * $Author: Kevin $
 *
 * Outrage random number generator code
 *
 * $Log: /DescentIII/Main/misc/psrand.cpp $
 *
 * 2     4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 1     4/21/99 10:16a Kevin
 *
 * $NoKeywords: $
 */

#include "psrand.h"

std::int32_t ps_holdrand = 1;

// These are adapted from the C runtime lib. Pretty simple.

void ps_srand(const std::uint32_t seed) { ps_holdrand = static_cast<std::int32_t>(seed); }

std::int32_t ps_rand(void) { return ((ps_holdrand = ps_holdrand * 214013 + 2531011) >> 16) & 0x7fff; }
