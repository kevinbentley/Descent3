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

#include "win_sound.h"

namespace D3 {

MovieSoundDevice::MovieSoundDevice(int sample_rate, uint16_t sample_size, uint8_t channels, uint32_t buf_size,
                                   bool is_compressed) {
  m_is_compressed = is_compressed;

  m_lpDS = nullptr;
  m_lpDSB = nullptr;

  m_WFE.wFormatTag = WAVE_FORMAT_PCM;
  m_WFE.nChannels = channels;
  m_WFE.nSamplesPerSec = sample_rate;
  m_WFE.nAvgBytesPerSec = sample_rate * channels * sample_size;
  m_WFE.nBlockAlign = channels * sample_size;
  m_WFE.wBitsPerSample = sample_size * 8;

  // Initialize DSound
  if (FAILED(DirectSoundCreate(nullptr, &m_lpDS, nullptr))) {
    return;
  }
  // Set Cooperative Level
  HWND hWnd = GetForegroundWindow();
  if (hWnd == nullptr) {
    hWnd = GetDesktopWindow();
  }
  if (FAILED(m_lpDS->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE))) {
    return;
  }

  // Create Primary Buffer
  DSBUFFERDESC dsbd;
  ZeroMemory(&dsbd, sizeof(dsbd));
  dsbd.dwSize = sizeof(DSBUFFERDESC);
  dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
  dsbd.dwBufferBytes = 0;
  dsbd.lpwfxFormat = nullptr;

  LPDIRECTSOUNDBUFFER lpDSB = nullptr;
  if (FAILED(m_lpDS->CreateSoundBuffer(&dsbd, &lpDSB, nullptr))) {
    return;
  }

  // Set Primary Buffer Format
  if (FAILED(lpDSB->SetFormat(&m_WFE))) {
    return;
  }

  // Create Second Sound Buffer
  dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS;
  dsbd.dwBufferBytes = (buf_size + (buf_size >> 1)) & ~3;
  dsbd.lpwfxFormat = &m_WFE;

  if (FAILED(m_lpDS->CreateSoundBuffer(&dsbd, &m_lpDSB, nullptr))) {
    return;
  }
}

MovieSoundDevice::~MovieSoundDevice() {
  if (m_lpDSB != nullptr) {
    m_lpDSB->Stop();
    m_lpDSB->Release();
  }
  m_sound_buffer.reset();
}

void MovieSoundDevice::Play() {
  if (!m_lpDSB)
    return;

  // Check if the DirectSound was created successfully
  if (m_lpDS == nullptr) {
    return;
  }

  LPBYTE lpvAudio1 = nullptr, lpvAudio2 = nullptr;
  DWORD dwBytesAudio1 = 0, dwBytesAudio2 = 0;

  if (FAILED(m_lpDSB->Lock(0, (DWORD)GetBuffer()->size() * 2, reinterpret_cast<LPVOID *>(&lpvAudio1), &dwBytesAudio1,
                           reinterpret_cast<LPVOID *>(&lpvAudio2), &dwBytesAudio2, DSBLOCK_FROMWRITECURSOR)))
    return;

  if (dwBytesAudio1 > 0) {
    memset(lpvAudio1, 0, dwBytesAudio1);
    auto limit = std::min(dwBytesAudio1 / 2, (DWORD)GetBuffer()->size());
    for (int i = 0; i < limit; i += 2) {
      int16_t sample = GetBuffer()->front();
      GetBuffer()->pop_front();
      lpvAudio1[i] = sample & 0xff;
      lpvAudio1[i + 1] = sample >> 8;
    }
  }

  if (dwBytesAudio2 > 0) {
    memset(lpvAudio2, 0, dwBytesAudio2);
    auto limit = std::min(dwBytesAudio2 / 2, (DWORD)GetBuffer()->size());
    for (int i = 0; i < limit; i += 2) {
      int16_t sample = GetBuffer()->front();
      GetBuffer()->pop_front();
      lpvAudio2[i] = sample & 0xff;
      lpvAudio2[i + 1] = sample >> 8;
    }
  }

  m_lpDSB->Unlock(lpvAudio1, dwBytesAudio1, lpvAudio2, dwBytesAudio2);

  // Begin Play
  m_lpDSB->Play(0, 0, DSBPLAY_LOOPING);

}

void MovieSoundDevice::Stop() {
  if (m_lpDSB != nullptr) {

    m_lpDSB->Stop();

    // Empty the buffer
    LPVOID lpvAudio1 = nullptr;
    DWORD dwBytesAudio1 = 0;
    HRESULT hr = m_lpDSB->Lock(0, 0, &lpvAudio1, &dwBytesAudio1, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
    if (FAILED(hr)) {
      return;
    }
    memset(lpvAudio1, 0, dwBytesAudio1);
    m_lpDSB->Unlock(lpvAudio1, dwBytesAudio1, nullptr, 0);

    // Move the current play position to begin
    m_lpDSB->SetCurrentPosition(0);
  }
}

void MovieSoundDevice::Lock(){}

void MovieSoundDevice::Unlock(){}

} // namespace D3
