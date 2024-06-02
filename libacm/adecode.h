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

#ifndef AUDIODECODE_H_
#define AUDIODECODE_H_

#include <cstdint>

namespace AudioDecoder {

class IAudioDecoder {
public:
  virtual ~IAudioDecoder() {}

  // Read data from the audio decoder.
  //   pBuffer: The buffer to receive the data from
  //    amount: How much data to read
  // Returns the number of bytes read - zero when we're at the end of the file
  virtual uint32_t Read(void *pBuffer, uint32_t amount) = 0;
};

// Create an audio decoder
// You supply a function for reading bytes from the compressed data via a
// void* pData handle, and the handle itself (typically a FILE *).
// Create_AudioDecoder returns a new AudioDecoder which can be used to
// read uncompressed decoded data from the compressed stream,
// and also returns the number of channels (1 or 2), the sample rate
// (e.g. 22050), and the number of samples contained in the compressed file
// (in case you want to pre-allocate a buffer to load them all into memory).
typedef int32_t (*ReadDataFunction)(void *pData, void *pBuffer, uint32_t amount);
IAudioDecoder *CreateDecoder(ReadDataFunction reader, void *pData, uint32_t &numChannels, uint32_t &sampleRate,
                             uint32_t &sampleCount);

} // namespace AudioDecoder

#endif
