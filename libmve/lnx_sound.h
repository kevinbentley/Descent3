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

#ifndef LIBMVE_LNX_SOUND_H_
#define LIBMVE_LNX_SOUND_H_

#include <SDL_audio.h>

#include "sound_interface.h"

namespace D3 {

class MovieSoundDevice : ISoundDevice {
private:
  SDL_AudioDeviceID m_device_id = 0;

public:
  MovieSoundDevice(int sample_rate, uint16_t sample_size, uint8_t channels, uint32_t buf_size, bool is_compressed);
  ~MovieSoundDevice();

  [[nodiscard]] bool IsInitialized() const { return m_device_id > 0 ? true : false; }

  void static SDLAudioCallback(void *userdata, unsigned char *stream, int len);

  void Play() override;
  void Stop() override;
  void Lock() override;
  void Unlock() override;

  using ISoundDevice::GetBuffer;
  using ISoundDevice::IsCompressed;

};

}

#endif // LIBMVE_LNX_SOUND_H_
