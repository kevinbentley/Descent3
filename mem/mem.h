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

 * $Logfile: /DescentIII/Main/lib/mem.h $
 * $Revision: 18 $
 * $Date: 3/20/00 12:26p $
 * $Author: Matt $
 *
 * Memory header.
 *
 * $Log: /DescentIII/Main/lib/mem.h $
 *
 * 18    3/20/00 12:26p Matt
 * Merge of Duane's post-1.3 changes.
 * Added declaration
 *
 * 17    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 16    8/10/99 5:12p Jeff
 * added a debug function to dump the current state of the mem library to
 * file
 *
 * 15    3/15/99 11:24a Kevin
 * Improved memory leak detection for mem_strdup and turned on debugging
 *
 * 14    10/13/98 3:42p Kevin
 * bug fixes
 *
 * 13    10/13/98 9:25a Kevin
 *
 * 12    10/12/98 8:39p Kevin
 * removed mprintf's and fixed some smallish bugs
 *
 * 11    10/12/98 11:54a Kevin
 *
 * 10    10/12/98 10:55a Kevin
 * Don't use memory lib for editor currently
 *
 * 9     10/12/98 10:22a Samir
 * made mem_strdup take a const char pointer.
 *
 * 8     10/09/98 3:32p Kevin
 * New memory library
 *
 * 7     10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 6     10/08/98 2:40p Kevin
 *
 * 5     7/31/98 5:44p Samir
 * improved memory debugging.
 *
 * $NoKeywords: $
 */

#ifndef MEM_H
#define MEM_H

// Memory management debugging
#ifdef MEM_USE_RTL
#define mem_malloc(d) malloc(d) // Use this if your going to run BoundsChecker
#define mem_free(d) free(d)
#define mem_strdup(d) strdup(d)
#define mem_size(d) mem_size_sub(d)
#define mem_realloc(d, e) realloc(d, e)
#else
// Use this if your going to NOT run BoundsChecker
#define mem_malloc(d) mem_malloc_sub(d, __FILE__, __LINE__)
#define mem_free(d) mem_free_sub(d)
#define mem_strdup(d) mem_strdup_sub(d, __FILE__, __LINE__)
#define mem_size(d) mem_size_sub(d)
#define mem_realloc(d, e) mem_realloc_sub(d, e)
#endif

extern bool Mem_low_memory_mode;
extern bool Mem_superlow_memory_mode; // DAJ

//	use if you want to manually print out a memory error
#define mem_error() mem_error_msg(__FILE__, __LINE__)

//	initializes memory library.
void mem_Init();

// shutsdown memory
void mem_shutdown();

// Returns the number of dynamically allocated bytes
int mem_GetTotalMemoryUsed();

// Allocates a block of memory and returns a pointer to it
void *mem_malloc_sub(int size, const char *file, int line);

// Frees a previously allocated block of memory
void mem_free_sub(void *memblock);

//	prints out a memory error message
void mem_error_msg(const char *file, int line, int size = -1);

char *mem_strdup_sub(const char *src, const char *file, int line);

void *mem_realloc_sub(void *memblock, int size);

int mem_size_sub(void *memblock);

bool mem_dumpmallocstofile(char *filename);

void mem_heapcheck();

#endif
