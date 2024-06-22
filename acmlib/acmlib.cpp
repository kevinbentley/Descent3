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



#include "adecode.h"
#include "mem.h"

#ifdef __cplusplus
extern "C" {
#endif

AudioDecoder *Create_AudioDecoder(ReadFunction *reader, void *data, unsigned *pChannels, unsigned *pSampleRate,
                                  int32_t *pSampleCount) {
  return (AudioDecoder *)mem_malloc(sizeof(AudioDecoder));
}

// Read from audio decoder at most the specified qty of bytes
// (each sample takes two bytes).
// Returns zero when the end of file is reached.
unsigned __cdecl AudioDecoder_Read(AudioDecoder *ad, void *buf, unsigned qty) { return 0; }

// Close audio decoder
void __cdecl AudioDecoder_Close(AudioDecoder *ad) {
  if (ad)
    mem_free(ad);
}

// Optional interface for supplying your own malloc and free functions
// Default is to use standard malloc and free.

void __cdecl AudioDecoder_MallocFree(ad_malloc *fn_malloc, ad_free *fn_free) {}

#ifdef __cplusplus
};
#endif
