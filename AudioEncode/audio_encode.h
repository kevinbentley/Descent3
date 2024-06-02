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

 * $Logfile: /DescentIII/Main/lib/audio_encode.h $
 * $Revision: 1 $
 * $Date: 1/27/99 1:33a $
 * $Author: Jeff $
 *
 * Header file for audio compression library
 *
 * $Log: /DescentIII/Main/lib/audio_encode.h $
 *
 * 1     1/27/99 1:33a Jeff
 *
 * $NoKeywords: $
 */

#ifndef __AUDIO_ENCODE_H_
#define __AUDIO_ENCODE_H_

// input_levels (default 7 or for 2k total)
// input_samples (default 16 or for 2k total)
// input_rate (default 22K)
// input_channels (default 1)
// input_factor (compression factor) (default 4 for 22K, 8 for 44K)
// input_volscale (Volume scaling) (slightly <= 1.0, default ,97)
bool aenc_Compress(char *input_filename, char *output_filename, int *input_levels = nullptr, int *input_samples = nullptr,
                  int *input_rate = nullptr, int *input_channels = nullptr, float *input_factor = nullptr,
                  float *input_volscale = nullptr);

#endif
