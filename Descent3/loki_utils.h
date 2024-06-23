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

/* stubs for the little bits of loki_utils we actually need. */

#ifndef _INCL_LOKI_UTILS_H_
#define _INCL_LOKI_UTILS_H_

// never liked these register option thingys...
#define loki_register_stdoptions()
#define loki_registeroption(x, y, z)
#define loki_setgamename(x, y, z)

#ifdef __cplusplus
extern "C" {
#endif

void loki_initialize(int argc, char **argv, char *desc);
const char *loki_getdatapath(void);
const char *loki_getprefpath(void);

#ifdef __cplusplus
}
#endif

#endif
