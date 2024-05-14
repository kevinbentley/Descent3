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

* $Logfile: /descent3/main/megacell.cpp $
* $Revision: 3 $
* $Date: 6/06/97 5:25p $
* $Author: Mark $
*
* $Log: /descent3/main/megacell.cpp $
 *
 * 3     6/06/97 5:25p Mark
 * FROM JASON:Fixed megacell bug
 *
 * 2     6/05/97 2:52p Jason
 * added megacell functions
 *
 * 1     6/05/97 10:56a Jason
 *

*
* $NoKeywords: $
*/

#include "pstypes.h"
#include "pserror.h"
#include "terrain.h"
#include "texture.h"
#include "gametexture.h"
#include "megacell.h"
#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

megacell Megacells[MAX_MEGACELLS];
int Num_megacells = 0;

// Sets all megacells to unused
void InitMegacells() {
  for (int i = 0; i < MAX_MEGACELLS; i++) {
    Megacells[i].used = 0;
    Megacells[i].name[0] = 0;
  }
  Num_megacells = 0;
}

// Allocs a megacell for use, returns -1 if error, else index on success
int AllocMegacell() {
  for (int i = 0; i < MAX_MEGACELLS; i++) {
    if (Megacells[i].used == 0) {
      memset(&Megacells[i], 0, sizeof(megacell));
      Megacells[i].used = 1;
      Megacells[i].width = DEFAULT_MEGACELL_WIDTH;
      Megacells[i].height = DEFAULT_MEGACELL_HEIGHT;
      Num_megacells++;
      return i;
    }
  }

  Int3(); // No megacells free!
  return -1;
}

// Frees megacell index n
void FreeMegacell(int n) {
  ASSERT(Megacells[n].used > 0);

  Megacells[n].used = 0;
  Megacells[n].name[0] = 0;
  Num_megacells--;
}

// Gets next megacell from n that has actually been alloced
int GetNextMegacell(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_MEGACELLS);

  if (Num_megacells == 0)
    return 0;

  for (i = n + 1; i < MAX_MEGACELLS; i++)
    if (Megacells[i].used)
      return i;
  for (i = 0; i < n; i++)
    if (Megacells[i].used)
      return i;

  // this is the only one

  return n;
}

// Gets previous megacell from n that has actually been alloced
int GetPrevMegacell(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_MEGACELLS);

  if (Num_megacells == 0)
    return 0;

  for (i = n - 1; i >= 0; i--) {
    if (Megacells[i].used)
      return i;
  }
  for (i = MAX_MEGACELLS - 1; i > n; i--) {
    if (Megacells[i].used)
      return i;
  }

  // this is the only one
  return n;
}
// Searches thru all megacells for a specific name, returns -1 if not found
// or index of megacell with name
int FindMegacellName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_MEGACELLS; i++)
    if (Megacells[i].used && !stricmp(name, Megacells[i].name))
      return i;

  return -1;
}
