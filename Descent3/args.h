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

#ifndef ARGS_H
#define ARGS_H

#define MAX_ARGS 30
#define MAX_CHARS_PER_ARG 100
extern char GameArgs[MAX_ARGS][MAX_CHARS_PER_ARG];

// Gathers all arguments
void GatherArgs(const char *str);
void GatherArgs(char **argv);

// Returns index of argument sought, or 0 if not found
int FindArg(const char *which, int start = 1);
int FindArgChar(const char *which, char singleCharArg);

const char *GetArg(int index);

#endif
