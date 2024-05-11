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

#ifndef LIBMVE_SOUND_INTERFACE_H_
#define LIBMVE_SOUND_INTERFACE_H_

#include <cstdint>
#include <deque>
#include <memory>

namespace D3 {

class ISoundDevice {
protected:
  std::unique_ptr<std::deque<int16_t>> m_sound_buffer;
  bool m_is_compressed = false;

public:
  ISoundDevice() { m_sound_buffer = std::make_unique<std::deque<int16_t>>(); };
  virtual void Play() {};
  virtual void Stop() {};
  virtual void Lock() {};
  virtual void Unlock() {};

  std::unique_ptr<std::deque<int16_t>> &GetBuffer() { return m_sound_buffer; }
  [[nodiscard]] bool IsCompressed() const { return m_is_compressed; };

};

}
#endif // LIBMVE_SOUND_INTERFACE_H_
