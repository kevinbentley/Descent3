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

#ifndef MUSICLIB_H
#define MUSICLIB_H

#define OMFCMD_NUM 22

#define OMFCMD_STREAM 0     // associates a symbol with a stream filename
#define OMFCMD_SECTION 1    // begins a theme
#define OMFCMD_PLAY 2       // plays a sample specified through llpt and lplc
#define OMFCMD_ENDSECTION 3 // ends a theme
#define OMFCMD_LABEL 4      // defines a label for branching
#define OMFCMD_COMPARE 5    // compares a register rX to what's loaded via lcmp
#define OMFCMD_LCMP 6       // loads NUMBER into lcmp
#define OMFCMD_LLPT 7       // specifies next play will load the sample specified
#define OMFCMD_LPLC 8       // specifies next play will loop sample n times
#define OMFCMD_INCI 9       // increments 'I' counter
#define OMFCMD_SETI 10      // sets 'I' counter
#define OMFCMD_IFI 11       // if 'I' counter == n then inst1;inst2;...;inst n
#define OMFCMD_REGION 12    // specifies a start of a named region
#define OMFCMD_ENDREGION 13 // specifies the end of a named region

#define OMFCMD_BRANCHING 15
#define OMFCMD_BLT 15  // branch if rX < lcmp
#define OMFCMD_BGT 16  // branch if rX > lcmp
#define OMFCMD_BEQ 17  // branch if rX == lcmp
#define OMFCMD_BNIF 18 // branch if stream playing is NOT finished.
#define OMFCMD_GOTO 19 // unconditional goto a label
#define OMFCMD_WAIT 20 // tells the system to wait

// undocumented codes.
#define OMFCMD_MPLAY 200  // internal code.
#define OMFCMD_ENDIFI 201 // end of ifi conditional.

#endif
