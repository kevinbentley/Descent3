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

#ifndef SOUNDLOAD_H_
#define SOUNDLOAD_H_

#include "ssl_lib.h"

extern int Num_sounds;
extern int Num_sound_files;

// Frees sound index n
void FreeSoundFile(int n);

// Gets next sound file from n that has actually been alloced
int GetNextSoundFile(int n);

// Gets previous sound file from n that has actually been alloced
int GetPrevSoundFile(int n);

// Given a filename, loads the sound file.
int LoadSoundFile(const char *filename, float import_volume, bool f_get_data = false);

// Sets all sounds to unused
void InitSounds();

// Allocs a sound for use, returns -1 if error, else index on success
int AllocSound();

// Frees sound index n
void FreeSound(int n);

// Gets next sound from n that has actually been alloced
int GetNextSound(int n);

// Gets previous sound from n that has actually been alloced
int GetPrevSound(int n);

// Searches thru all sounds for a specific name, returns -1 if not found
// or index of sound with name
int FindSoundName(const char *name);

// Given a filename, loads the sound.
int LoadSound(const char *filename);

// This is a very confusing function.  It takes all the sounds that we have loaded
// and remaps then into their proper places (if they are static).
void RemapSounds();

#endif
