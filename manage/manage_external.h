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

 * $Logfile: /DescentIII/main/lib/manage_external.h $
 * $Revision: 4 $
 * $Date: 2/10/99 4:38p $
 * $Author: Matt $
 *
 * Any defines, structs, etc. manage related that can be exported to DLLs
 *
 * $Log: /DescentIII/main/lib/manage_external.h $
 *
 * 4     2/10/99 4:38p Matt
 * Misc. changes for table file parsing
 *
 * 3     2/05/99 7:03p Jeff
 * table file parsing macros put in
 *
 * 2     1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * $NoKeywords: $
 */

#ifndef __MANAGE_EXTERNAL_H_
#define __MANAGE_EXTERNAL_H_

#define PAGENAME_LEN 35

// Use this macro around your parameter in a table-file lookup, etc. to have the
// table file parser ignore this instance of the function (because you might be
// using one of the $$TABLE_ defines in a comment to force add items
#define IGNORE_TABLE(s) s

// Use these macros around literal strings that are in arrays.
// NOTE that these strings must be inside curly braces
#define TBL_SOUND(s) s
#define TBL_GENERIC(s) s
#define TBL_GAMEFILE(s) s

#endif
