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

 * $Logfile: /DescentIII/main/Lib/psglob.h $
 * $Revision: 2 $
 * $Date: 1/07/99 10:51p $
 * $Author: Jeff $
 *
 * string globbing function header
 *
 * $Log: /DescentIII/main/Lib/psglob.h $
 *
 * 2     1/07/99 10:51p Jeff
 * added psglob and support to do find in files for hog files
 *
 * 1     1/07/99 7:28p Jeff
 *
 * $NoKeywords: $
 */

#ifndef __PSGLOB_H_
#define __PSGLOB_H_

// Returns 1 if string contains globbing characters in it
int PSGlobHasPattern(char *string);

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
int PSGlobMatch(char *pattern, char *text, int case_sensitive, int dot_special);

// Like PSGlobMatch, but match pattern against any final segment of text
int PSGlobMatchAfterStar(char *pattern, int case_sensitive, char *text);

#endif
