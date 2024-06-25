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

#ifndef __LNXCON_HPP_
#define __LNXCON_HPP_

////////////////////////////////////////////////
// NULL driver functions
extern void con_null_Printf(const char *fmt, ...);
extern bool con_null_Input(char *buf, int buflen);
extern void con_null_Defer(void);
extern bool con_null_Create(void);
extern void con_null_Destroy(void);

// put some data up on the screen
extern void con_null_Puts(int window, const char *str);

////////////////////////////////////////////////
// raw driver functions
extern void con_raw_Printf(const char *fmt, ...);
extern bool con_raw_Input(char *buf, int buflen);
extern void con_raw_Defer(void);
extern bool con_raw_Create(void);
extern void con_raw_Destroy(void);
extern void con_raw_Puts(int window, const char *str);

#endif
