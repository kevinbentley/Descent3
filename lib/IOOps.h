/*
 * Descent 3
 * Copyright (C) 2024 Descent Developers
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
#pragma once

#include <cstdint>
#include <istream>
#include <ostream>

#include "byteswap.h"

namespace D3 {

template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
static inline std::ostream &bin_write(std::ostream &output, T value, bool is_little_endian = true,
                                      size_t n = sizeof(T)) {
  value = is_little_endian ? convert_le(value) : convert_be(value);
  output.write(reinterpret_cast<const char *>(&value), n);

  return output;
}

template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
static inline std::istream &bin_read(std::istream &input, T &value, bool is_little_endian = true, size_t n = sizeof(T)) {
  input.read(reinterpret_cast<char *>(&value), n);
  value = is_little_endian ? convert_le(value) : convert_be(value);

  return input;
}

} // namespace D3
