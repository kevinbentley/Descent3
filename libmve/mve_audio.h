/*
 * Copyright (C) 2002-2024 D2X Project
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

#ifndef INCLUDED_MVE_AUDIO_H
#define INCLUDED_MVE_AUDIO_H

/**
 * Process input data and send parsed data into queue buffer
 * @param buffer output queue buffer
 * @param data input data
 * @param is_compress true if input data is compressed
 */
void mveaudio_process(std::unique_ptr<std::deque<int16_t>> &buffer, unsigned char *data, bool is_compressed = true);

#endif /* INCLUDED_MVE_AUDIO_H */
