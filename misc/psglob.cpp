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

 * $Logfile: /DescentIII/Main/misc/psglob.cpp $
 * $Revision: 3 $
 * $Date: 4/15/99 11:10p $
 * $Author: Jeff $
 *
 * string globbing functions
 *
 * $Log: /DescentIII/Main/misc/psglob.cpp $
 *
 * 3     4/15/99 11:10p Jeff
 * fixed gcc warning
 *
 * 2     1/07/99 10:51p Jeff
 * added psglob and support to do find in files for hog files
 *
 * $NoKeywords: $
 */

#include "psglob.h"
#include <stdlib.h>
#include <ctype.h>

#if defined(__LINUX__) || defined(ANDROID)
#include <ctype.h>
#endif

// Returns 1 if string contains globbing characters in it
int PSGlobHasPattern(char *string) {
  char *p = string;
  char c;
  int open = 0;

  while ((c = *p++) != '\0') {
    switch (c) {
    case '?':
    case '*':
      return 1;
    case '[': // Open brackets must have a matching close bracket in order to be a glob
      open++;
      continue;
    case ']':
      if (open)
        return 1;
      continue;
    case '\\':
      if (*p++ == '\0')
        return 0;
    }
  }

  return 0;
}

//	PSGlobMatch
//	Matches the pattern passed in to the string in text.  If the pattern matches
//	it returns 1, if not, it returns 0. In order to have a match, the following
//	conditions must be met:
//	1) The entire string (text) is used for matching.
//	2) '*' matches any sequence of characters.
//	3) '?' matches any character
//	4) [SET] matches any character in the specified set.
//	5) [!SET] matches any character _not_ in the specified set.
//		A set is composed of characters or ranges.  A range looks like
//		character hyphen character (as in 0-9 or A-Z). [0-9a-zA-Z_] is the set
//		of all characters allowed in C identifiers.
//	6) Any other character in the pattern must be matched exactly.(see 9)
//	7) Because of the syntactic significance of []*?!- and \ to match
//		these characters exactly, preced it with a '\'.
//	8) If dot_special is not zero, '*' and '?' do not match '.' at the beginning of text
//	9) If case_sensitive is 0, than case does not matter for the non-pattern characters
int PSGlobMatch(char *pattern, char *text, int case_sensitive, int dot_special) {
  char *p = pattern, *t = text;
  char c;

  while ((c = *p++) != '\0') {
    switch (c) {
    case '?':
      if (*t == '\0' || (dot_special && t == text && *t == '.'))
        return 0;
      else
        ++t;
      break;
    case '\\':
      if (*p++ != *t++)
        return 0;
      break;
    case '*':
      if (dot_special && t == text && *t == '.')
        return 0;
      return PSGlobMatchAfterStar(p, case_sensitive, t);
    case '[': {
      char c1 = *t++;
      int invert;

      if (!c1)
        return (0);

      invert = ((*p == '!') || (*p == '^'));
      if (invert)
        p++;
      c = *p++;

      while (1) {
        char cstart = c, cend = c;
        if (c == '\\') {
          cstart = *p++;
          cend = cstart;
        }

        if (c == '\0')
          return 0;
        c = *p++;

        if (c == '-' && *p != ']') {
          cend = *p++;
          if (cend == '\\')
            cend = *p++;
          if (cend == '\0')
            return 0;
          c = *p++;
        }

        if (c1 >= cstart && c1 <= cend)
          goto match;
        if (c == ']')
          break;
      }

      if (!invert)
        return 0;
      break;
    match:
      /* Skip the rest of the [...] construct that already matched.  */
      while (c != ']') {
        if (c == '\0')
          return 0;
        c = *p++;
        if (c == '\0')
          return 0;
        else if (c == '\\')
          ++p;
      }

      if (invert)
        return 0;
      break;
    }
    default:
      if (case_sensitive) {
        if (c != *t++)
          return 0;
      } else {
        if (tolower(c) != tolower(*t++))
          return 0;
      }
    }
  }

  return *t == '\0';
}

// Like PSGlobMatch, but match pattern against any final segment of text
int PSGlobMatchAfterStar(char *pattern, int case_sensitive, char *text) {
  char *p = pattern, *t = text;
  char c, c1;

  while ((c = *p++) == '?' || c == '*') {
    if (c == '?' && *t++ == '\0')
      return 0;
  }

  if (c == '\0')
    return 1;
  if (c == '\\')
    c1 = *p;
  else
    c1 = c;

  while (1) {
    if (case_sensitive) {
      if ((c == '[' || *t == c1) && PSGlobMatch(p - 1, t, case_sensitive, 0))
        return 1;
    } else {
      if ((c == '[' || tolower(*t) == tolower(c1)) && PSGlobMatch(p - 1, t, case_sensitive, 0))
        return 1;
    }

    if (*t++ == '\0')
      return 0;
  }
}
