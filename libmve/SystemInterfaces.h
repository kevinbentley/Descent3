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

#ifndef MVE_SYSTEM_INTERFACES_H__
#define MVE_SYSTEM_INTERFACES_H__

#include <cstdint>

// Max&Min values for settings
#define LNXSND_VOLUME_MAX 0
#define LNXSND_VOLUME_MIN (-10000)
#define LNXSND_PAN_LEFT (-10000)
#define LNXSND_PAN_RIGHT 10000

// Status/Buffer flags
#define LNXSND_PLAYING 0x0001
#define LNXSND_LOOPING 0x0002

// Buffer lock flags
#define LNXSND_LOCK_FROMWRITECURSOR 0x0001
#define LNXSND_LOCK_ENTIREBUFFER 0x0002

// Capability flags
#define LNXSND_CAPS_PRIMARYBUFFER 0x0001
#define LNXSND_CAPS_CTRLVOLUME 0x0080
#define LNXSND_CAPS_CTRLPAN 0x0040
#define LNXSND_CAPS_CTRLFREQUENCY 0x0020
#define LNXSND_CAPS_CTRLDEFAULT 0x00E0
#define LNXSND_CAPS_LOCSOFTWARE 0x0008
#define LNXSND_CAPS_LOCHARDWARE 0x0004

struct SoundWAVEFormatEx {
  uint16_t wFormatTag;
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
  uint16_t cbSize;
};
#define SOUND_WAVE_FORMAT_PCM 0x01

struct SysSoundCaps {
  uint32_t dwFlags;
  uint32_t dwBufferBytes;
};

class SysSoundBufferDesc {
public:
  SoundWAVEFormatEx *lpwfxFormat;
  uint32_t dwBufferBytes;
  uint32_t dwFlags;
};

class ISysSoundBuffer {
public:
  ////////////////////////////
  // Release
  ////////////////////////////
  // Releases the memory associated with a sound buffer.  This pointer is
  // no longer valid after return.
  //
  // Returns:
  //       -1 : Invalid Parameter
  //        0 : Ok!
  virtual int Release() = 0;

  //////////////////////////////
  // SetVolume
  //////////////////////////////
  // Sets the volume of a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : Cannot set volume
  //       -2 : Invalid parameters
  virtual int SetVolume(int32_t vol) = 0;

  ///////////////////////////
  // SetPan
  ///////////////////////////
  // Sets the pan of a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : Cannot set pan
  //       -2 : Invalid parameters
  virtual int SetPan(int32_t pan) = 0;

  /////////////////////////
  // Stop
  /////////////////////////
  // Stops a buffer from playing
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int Stop() = 0;

  /////////////////////////
  // Play
  /////////////////////////
  // Starts a buffer playing (or changes the flags for a buffer currently
  // playing).
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int Play(uint32_t flags) = 0;

  ////////////////////////////
  // GetCaps
  ////////////////////////////
  // Get the capabilities of a sound buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int GetCaps(SysSoundCaps *caps) = 0;

  //////////////////////////////
  // GetStatus
  //////////////////////////////
  // Returns the status of a buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int GetStatus(uint32_t *status) = 0;

  ///////////////////////////////////////
  // GetCurrentPosition
  ///////////////////////////////////////
  // Returns the current play and write positions of the buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int GetCurrentPosition(uint32_t *ppos, uint32_t *wpos) = 0;

  ///////////////////////////////////////
  // SetCurrentPosition
  ///////////////////////////////////////
  // Sets the current play position of the buffer
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int SetCurrentPosition(uint32_t pos) = 0;

  /////////////////////////
  // Lock
  /////////////////////////
  // Locks the given buffer, returning pointer(s) to the buffer(s) along with
  // available the size of the buffer(s) for writing.
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int Lock(uint32_t pos, uint32_t numbytes, void **ptr1, uint32_t *numbytes1, void **ptr2,
                   uint32_t *numbytes2, uint32_t flags) = 0;

  ///////////////////////////
  // Unlock
  ///////////////////////////
  // Unlocks a buffer.
  //
  // Returns:
  //        0 : no error
  //       -1 : invalid parameters
  virtual int Unlock(void *ptr1, uint32_t num1, void *ptr2, uint32_t num2) = 0;
};

class ISoundDevice {
public:
  ///////////////////////////////
  // CreateSoundBuffer
  ///////////////////////////////
  // Creates a sound buffer to be used with mixing and output.
  //
  // Returns:
  //       -1 : Invalid Parameter
  //       -2 : Out of memory
  //        0 : Ok!
  virtual int CreateSoundBuffer(SysSoundBufferDesc *lbdesc, ISysSoundBuffer **lsndb) = 0;
};

#endif
