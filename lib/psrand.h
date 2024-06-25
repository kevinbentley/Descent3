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

 * $Logfile: /DescentIII/Main/lib/psrand.h $
 * $Revision: 2 $
 * $Date: 4/21/99 11:05a $
 * $Author: Kevin $
 *
 * Outrage random number generator code
 *
 * $Log: /DescentIII/Main/lib/psrand.h $
 *
 * 2     4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 1     4/21/99 10:16a Kevin
 *
 * $NoKeywords: $
 */

#pragma once

#include <cstdint>
#include <cstdlib>

#include <type_traits>

#define D3_RAND_MAX 0x7fff

// Seed the random number generator with the given number.
void ps_srand(const std::uint32_t seed);

// Return a random integer in the range [0, D3_RAND_MAX].
std::int32_t ps_rand(void);

namespace D3 {
// Return a random integer in the range [min, max].
template <typename T = std::int32_t>
std::enable_if_t<std::is_integral_v<T>, T> RandomInt(const T min = 0, const T max = D3_RAND_MAX) {
  return min + ps_rand() % (std::abs(max - min) + 1);
}

// Return a random float in the range [min, max].
template <typename T = float>
std::enable_if_t<std::is_floating_point_v<T>, T> RandomFloat(const T min = 0, const T max = 1) {
  return min + (ps_rand() / (T)D3_RAND_MAX) * std::abs(max - min);
}

// Return true with the frequency of chance, and false with the inverse frequency of chance.
template <typename T = float> std::enable_if_t<std::is_floating_point_v<T>, bool> RandomBool(const T chance = 0.5) {
  return ps_rand() / (T)D3_RAND_MAX < chance;
}
}; // namespace D3
