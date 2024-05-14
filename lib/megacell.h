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

#ifndef MEGACELL_H
#define MEGACELL_H

#include "pstypes.h"
#include "manage.h"
#include "gametexture.h"

#define MAX_MEGACELLS 100

#define DEFAULT_MEGACELL_WIDTH 8
#define DEFAULT_MEGACELL_HEIGHT 8

#define MAX_MEGACELL_WIDTH 8
#define MAX_MEGACELL_HEIGHT 8

struct megacell {
  char name[PAGENAME_LEN];
  int8_t width;
  int8_t height;

  int16_t texture_handles[MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT];
  int flags;
  uint8_t used;
};

extern int Num_megacells;
extern megacell Megacells[MAX_MEGACELLS];

// Sets all MEGACELLs to unused
void InitMegacells();

// Allocs a MEGACELL for use, returns -1 if error, else index on success
int AllocMegacell();

// Frees MEGACELL index n
void FreeMegacell(int n);

// Gets next MEGACELL from n that has actually been alloced
int GetNextMegacell(int n);

// Gets previous MEGACELL from n that has actually been alloced
int GetPrevMegacell(int n);

// Searches thru all MEGACELLs for a specific name, returns -1 if not found
// or index of MEGACELL with name
int FindMegacellName(const char *name);

#endif
