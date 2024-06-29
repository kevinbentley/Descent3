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

#include "args.h"
#include "mono.h"
#include <string.h>

#if defined(_WIN32)
#define strcasecmp stricmp
#endif

// rcg07062000 used to be static.
static int TotalArgs = 0;
char GameArgs[MAX_ARGS][MAX_CHARS_PER_ARG];

const char *GetArg(int index) {
  if (index >= TotalArgs || index == 0)
    return NULL;
  return GameArgs[index];
}

// Gathers all arguments
void GatherArgs(const char *str) {
  int i, t;
  static int curarg = 1; // DAJ made static
  int len = strlen(str);
  bool gotquote = false;
  for (t = 0, i = 0; i < len; i++) {
    if (t == 0) {
      if (str[i] == '\"') {
        gotquote = true;
        continue;
      }
    }
    if (gotquote) {
      if (str[i] != '\"' && str[i] != 0)
        GameArgs[curarg][t++] = str[i];
      else {
        GameArgs[curarg][t] = 0;
        t = 0;
        gotquote = false;
        curarg++;
      }
    } else {
      if (str[i] != ' ' && str[i] != 0)
        GameArgs[curarg][t++] = str[i];
      else {
        GameArgs[curarg][t] = 0;
        t = 0;
        curarg++;
      }
    }
  }
  GameArgs[curarg][t] = 0;
  curarg++;
  TotalArgs = curarg;

  for (int q = 0; q < TotalArgs; q++)
    mprintf(0, "GatherArgs: Arg (%d) is [%s].", q, GameArgs[q]);
}

void GatherArgs(char **argv) {
  TotalArgs = 0;

  for (int i = 0; ((i < MAX_ARGS) && (argv[i] != NULL)); i++) {
    TotalArgs++;
    strncpy(GameArgs[i], argv[i], MAX_CHARS_PER_ARG);
  } // for

  for (int q = 0; q < TotalArgs; q++)
    mprintf(0, "GatherArgs: Arg (%d) is [%s].", q, GameArgs[q]);
} // GatherArgs

// Strip '-', '--', and '+' flag prefix, so --foo, -foo, +foo => foo, but pass through - -- + ++
const char *SkipArgPrefix(const char *arg) {
  if (*arg != '\0' && *(arg + 1) != '\0') {
    if (*arg == '-') {
      if (*(arg + 1) == '-' && *(arg + 2) != '\0') {
        return arg + 2;
      }
      if (*(arg + 1) != '-') {
        return arg + 1;
      }
    } else if (*arg == '+' && *(arg + 1) != '+') {
      return arg + 1;
    }
  }
  return arg;
}

int FindArg(const char *which, int start) {
  if (which == nullptr)
    return 0;

  auto which_matches = [which = SkipArgPrefix(which)](char *arg) -> bool {
    return strcasecmp(which, SkipArgPrefix(arg)) == 0;
  };

  for (int i = start; i <= TotalArgs; i++) {
    if (which_matches(GameArgs[i])) {
      mprintf(0, "FindArg: Found [%s] at argument index (%d).", which, i);
      return i;
    }
  }

  if (start == 1) {
    mprintf(0, "FindArg: Did not find [%s] on command line.", which);
  } else {
    mprintf(0, "FindArg: Did not find [%s] on command line at index %i or after index %i.", which, start, start);
  }
  return 0;
}

// Returns index of argument sought, or 0 if not found
int FindArgChar(const char *which, char singleCharArg) {
  for (int i = 1; i <= TotalArgs; i++) {
    char *str = GameArgs[i];
    if (str[0] == '-' && str[1] == singleCharArg && str[2] == '\0') {
      mprintf(0, "FindArg: Found [-%c] at argument index (%d).", singleCharArg, i);
      return i;
    }
  }

  return FindArg(which);
}
