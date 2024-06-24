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

 * $Logfile: /DescentIII/Main/mem/mem.cpp $
 * $Revision: 56 $
 * $Date: 1/03/02 5:27p $
 * $Author: Matt $
 *
 * Memory library
 *
 * $Log: /DescentIII/Main/mem/mem.cpp $
 *
 * 56    1/03/02 5:27p Matt
 * Add a longlong cast to prevent math overflow.
 *
 * 55    4/19/00 5:33p Matt
 * From Duane for 1.4
 * Close renderer on malloc fail error exit
 * Mac changes
 *
 * 54    10/21/99 2:25p Kevin
 * Mac merge
 *
 * 53    8/10/99 5:12p Jeff
 * added a debug function to dump the current state of the mem library to
 * file
 *
 * 52    7/28/99 2:22p Kevin
 * Macintosh Stuff
 *
 * 51    5/13/99 5:06p Ardussi
 * changes for compiling on the Mac
 *
 * 50    5/02/99 12:24a Jason
 * mem was incorrectly choosing lowmem mode on 64 meg machines
 *
 * 49    4/30/99 5:07p Kevin
 * misc dedicated server, networking and low memory enhancements
 *
 * 48    4/16/99 10:42p Jeff
 * moved global variables out of window scope code to all builds for linux
 *
 * 47    4/15/99 11:09p Jeff
 * fixed mem_strdup for linux
 *
 * 46    4/15/99 9:22p Jeff
 * Changes for Linux version
 *
 * 45    4/12/99 2:23p Kevin
 * fixed missing symbol
 *
 * 44    4/12/99 1:13p Kevin
 * Moved call to GetLastError and played with some debugging
 *
 * 43    3/17/99 11:19a 3dsmax
 * Took out debugging
 *
 * 42    3/16/99 4:49p Kevin
 * Fixed realloc
 *
 * 41    3/15/99 4:32p Jeff
 * fixed code so mem library compiles correctly
 *
 * 40    3/15/99 11:24a Kevin
 * Improved memory leak detection for mem_strdup and turned on debugging
 *
 * 39    3/14/99 2:31p Kevin
 * Added mem_heapcheck() function for debugging
 *
 * 38    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 37    2/28/99 6:30p Kevin
 * Added a call to Error() when unable to alloc memory
 *
 * 36    1/09/99 4:40p Jeff
 * added some ifdefs and fixes to get files to compile under Linux
 *
 * 35    1/05/99 3:46p Matt
 * For Kevin, added call to GetLastError()
 *
 * 34    11/05/98 2:00p Sean
 *
 * 33    11/05/98 11:23a Kevin
 * fixed bug that caused it not to work under NT
 *
 * 32    10/30/98 11:23a Samir
 *
 * 31    10/30/98 11:10a Kevin
 * doh! fixed ifdef
 *
 * 30    10/30/98 11:01a Kevin
 * took out mem debug stuff for nt users (temp)
 *
 * 29    10/28/98 5:01p Kevin
 * Improved debugging aids in mem lib
 *
 * 28    10/21/98 7:18p Matt
 * Added quick-exit system to not free individual mem chunks on exit,
 * since the whole heap gets freed at the end.
 *
 * 27    10/18/98 9:11p Matt
 * Took the program name out of some error messages.
 *
 * 26    10/18/98 6:21p Matt
 * Changed a Debug_ConsolePrintf() to mprintf() since the former doesn't
 * exist in a Release build and the latter compiles out.
 *
 * 25    10/17/98 12:46p Kevin
 * Beta 4 fixes
 *
 * 24    10/15/98 12:15p Kevin
 * put in heap checking code
 *
 * 23    10/15/98 11:59a Kevin
 * removed useage of timer_GetTime and FindArg
 *
 * 22    10/14/98 11:25p Jeff
 * commented out call to HeapDestroy() to keep NT users from crashing on
 * exit because it destroys the heap before Sound thread closes
 *
 * 21    10/14/98 7:20p Kevin
 * More dsp changes...
 *
 * 20    10/14/98 4:39p Matt
 * Changed OutrageMessageBox() calls to use either Error() or
 * EditorMessageBox()
 *
 * 19    10/13/98 3:42p Kevin
 * bug fixes
 *
 * 18    10/12/98 8:39p Kevin
 * removed mprintf's and fixed some smallish bugs
 *
 * 17    10/12/98 11:32a Kevin
 * doh! heap size was 160 megs
 *
 * 16    10/12/98 11:25a Kevin
 * doh!
 *
 * 15    10/12/98 10:55a Kevin
 * Don't use memory lib for editor currently
 *
 * 14    10/12/98 10:22a Samir
 * made mem_strdup take a const char pointer.
 *
 * 13    10/09/98 7:40p Kevin
 *
 * 12    10/09/98 6:55p Kevin
 * fized bug with zero byte mallocs and mem_size
 *
 * 11    10/09/98 3:32p Kevin
 * New memory library
 *
 * 10    10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 9     10/08/98 2:40p Kevin
 *
 * 8     10/08/98 12:00p Kevin
 * Demo system work
 *
 * 7     9/22/98 3:55p Samir
 * ifdef out stuff for non-debug version.
 *
 * 6     8/31/98 12:42p Samir
 * added some debug code.
 *
 * 5     7/31/98 5:44p Samir
 * improved memory debugging.
 *
 * $NoKeywords: $
 */
#ifndef __LINUX__
#include <new.h>
#endif
#if defined(MACOSX)

#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
// Non-Linux Includes
#include <windows.h>
#include <crtdbg.h>
#else
#endif
#include <cstdint>

#include "mem.h"
#include "pserror.h"

// #define MEM_DEBUG

#ifdef MEM_USE_RTL
#pragma message("mem.cpp: Compiling For Run-Time Library usage")
#endif

#ifdef MEM_DEBUG
#pragma message("mem.cpp: Compiling with Debug Settings")
#endif

#ifdef MEM_LOGFILE
#pragma message("mem.cpp: Compiling with logfile support")
#endif

int Total_mem_used = 0;
int Mem_high_water_mark = 0;

#define MEM_NO_MEMORY_PTR 0xdeadbeef
#define MEM_MAX_MALLOCS 199999
#define MEM_GAURDIAN_SIG 0x2bad
#define MEM_MALLOC_TO_SORT 10000

struct mem_alloc_info {
  int len;
  void *ptr;
  uint16_t line;
  char file[17];
};

static void *Mem_failsafe_block = nullptr;

bool Mem_low_memory_mode = false;
bool Mem_superlow_memory_mode = false;
// If this is set, the mem library ignores mem_free() calls.  All the memory is then freed at once on exit.
bool Mem_quick_exit = false;

#if defined(__LINUX__)
// Linux memory management
int LnxTotalMemUsed;

void mem_shutdown() {}

void mem_Init() { LnxTotalMemUsed = 0; }

int mem_GetTotalMemoryUsed() { return LnxTotalMemUsed; }

void *mem_malloc_sub(int size, const char *file, int line) {
  void *new_mem = malloc(size);
  if (!new_mem) {
    mprintf(0, "Out of memory allocating %d bytes: line %d in %s\n", size, line, file);
    Int3();
    return nullptr;
  }
  LnxTotalMemUsed += size;
  return new_mem;
}

void mem_free_sub(void *memblock) {
  if (memblock) {
#if defined(MACOSX)
    LnxTotalMemUsed -= malloc_size(memblock);
#else
    LnxTotalMemUsed -= malloc_usable_size(memblock);
#endif
    free(memblock);
  }
}

void mem_error_msg(const char *file, int line, int size) {
  mprintf(0, "Memory error (size=%d) line %d in %s\n", size, line, file);
  Int3();
}

char *mem_strdup_sub(const char *string, const char *file, int line) {
  char *ret = strdup(string);
  if (!ret) {
    mprintf(0, "Out of memory allocating %d bytes: line %d in %s\n", strlen(string) + 1, line, file);
    Int3();
    return nullptr;
  }
  return ret;
}

void *mem_realloc_sub(void *mem, int size) { return realloc(mem, size); }

int mem_size_sub(void *memblock) {
#ifdef MACOSX
  return malloc_size(memblock);
#else
  return malloc_usable_size(memblock);
#endif
}

bool mem_dumpmallocstofile(char *filename) { return false; }

#pragma mark -

#else // defined(__LINUX__)
// Windows memory management

// Uncomment this to detect memory leaks and memory overwrites. Slows down mallocs and frees a little.
// #define MEM_DEBUG	1
// Uncomment this if you want everything written to "memory.out"
// #define MEM_LOGFILE	1

#ifdef MEM_USE_RTL
#undef MEM_DEBUG
#endif

class MemClass {
public:
  ~MemClass();
};
class MemClass Mymem;
/* modify these lines to establish data type */
typedef mem_alloc_info *T;  /* type of item to be stored */
typedef int hashTableIndex; /* index into hash table */
#define compEQ(a, b) ((a)->ptr == (b)->ptr)
struct Node {
  struct Node *next; /* next node */
  T data;             /* data stored in node */
};
Node *findNode(T data);
void deleteNode(T data);
Node *insertNode(T data);
hashTableIndex hash(T data);
Node **hashTable;
int hashTableSize = MEM_MAX_MALLOCS;
#ifdef MEM_DEBUG
mem_alloc_info mem_info[MEM_MAX_MALLOCS];
int Mem_next_slot = 0;
int Mem_highest_used_slot = 0;
FILE *mem_out = NULL;
int Mem_mallocs_since_last_sort = 0;
/*
#undef new
void *operator new(uint32_t size, char *file, int line)
{
  return mem_malloc_sub(size, file, line);
}
void *operator new [](uint32_t size, char *file, int line)
{
  return mem_malloc_sub(size, file, line);
}
void *operator new(uint32_t size)
{
        return mem_malloc_sub(size,"unknown",0);
}
void operator delete(void *ptr)
{
        mem_free_sub(ptr);
}
*/
#endif
int handle_program_memory_depletion(size_t size);
HANDLE Heap;
void mem_Init() {
#if defined(WIN32) || defined(__LINUX__)
  //	allocate failsafe block for memory used by any functions after we run out of memory.
  // (printf for instance needs heap memory, as well as our error library.)
  MEMORYSTATUS ms;
#ifdef MEM_DEBUG
  hashTable = (Node **)malloc(hashTableSize * sizeof(Node *));
  for (int a = 0; a < hashTableSize; a++) {
    hashTable[a] = NULL;
  }
#ifdef MEM_LOGFILE
  {
    mem_out = fopen("memory.out", "wt");
    ASSERT(mem_out);
  }
#endif
  for (int i = 0; i < MEM_MAX_MALLOCS; i++) {
    mem_info[i].ptr = (void *)MEM_NO_MEMORY_PTR;
  }
#endif

  GlobalMemoryStatus(&ms);
  Heap = HeapCreate(HEAP_NO_SERIALIZE, 16000000, 0); // GetProcessHeap();
  if (!Heap) {
    mprintf(0, "Unable to create memory heap! error: %d\n", GetLastError());
    Error("Unable to create memory heap; your system may not have enough memory to run.");
  }
  ASSERT(Heap);
  HeapCompact(Heap, 0);
  mprintf(0, "System Memory Status:\n");
  mprintf(0, "Percent of memory in use: %d\n", ms.dwMemoryLoad);
  mprintf(0, "Bytes of physical memory : %d\n", ms.dwTotalPhys);
  mprintf(0, "Free physical memory bytes  : %d\n", ms.dwAvailPhys);
  mprintf(0, "Available virtual memory : %d\n", ms.dwAvailPageFile);

  // See if there is enough memory to run
  if (((int64_t)ms.dwAvailPageFile + ms.dwAvailPhys) < (50 * 1024 * 1024)) {
    Error("Your system doesn't have enough available memory to continue.\r\n\r\nMemory Statistics:\r\nTotal Physical: "
          "%d\r\nAvaliable Physical: %d\r\nAvailable Virtual: %d\r\n\r\nYou may be able to continue by rebooting, or "
          "freeing up some disk space.",
          ms.dwTotalPhys, ms.dwAvailPhys, ms.dwAvailPageFile);
    return;
  } else if ((ms.dwTotalPhys) < (62 * 1024 * 1024)) {
    mprintf(0, "Using low memory mode!\n");
    Mem_low_memory_mode = true;
    return;
  } else if ((ms.dwTotalPhys) < (46 * 1024 * 1024)) {
    mprintf(0, "Using super low memory mode!\n");
    Mem_low_memory_mode = true;
    Mem_superlow_memory_mode = true;
    return;
  }
#else
#ifdef MEM_DEBUG
  hashTable = (Node **)malloc(hashTableSize * sizeof(Node *));
  for (int a = 0; a < hashTableSize; a++) {
    hashTable[a] = NULL;
  }
#ifdef MEM_LOGFILE
  {
    mem_out = fopen("memory.out", "wt");
    ASSERT(mem_out);
  }
#endif
  for (int i = 0; i < MEM_MAX_MALLOCS; i++) {
    mem_info[i].ptr = (void *)MEM_NO_MEMORY_PTR;
  }
#endif
  Heap = NULL;

  Mem_failsafe_block = mem_malloc(128);
  if (!Mem_failsafe_block) {
    Error("No available heap memory.");
  }
  return;
#endif
#if defined(WIN32) || defined(__LINUX__)
  Mem_failsafe_block = mem_malloc(128);
  if (!Mem_failsafe_block) {
    Error("No available heap memory.");
  }
  _set_new_handler(handle_program_memory_depletion);
  int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
#ifdef _DEBUG
  flags |= _CRTDBG_ALLOC_MEM_DF;
#endif
  _CrtSetDbgFlag(flags);
  // atexit(mem_Free);
#endif
}
// Returns the number of dynamically allocated bytes
int mem_GetTotalMemoryUsed() { return Total_mem_used; }
bool bail_now = false;
// Allocates a block of memory and returns a pointer to it
void *mem_malloc_sub(int size, const char *file, int line) {
  // float mstart = timer_GetTime();
  void *retp;
#ifdef MEM_USE_RTL
  retp = malloc(size);
  return retp;
#else
#if defined(WIN32)
  if (!Heap) {
    return 0;
  }
#endif
  if (size < 0) {
    mprintf(0, "Some bozo is trying to allocate a negative length of memory!\n");
    mprintf(0, "Offending file: %s line: %d\n", file, line);
    Int3();
    return NULL;
  } else if (size == 0) {
    mprintf(0, "Warning: Zero byte malloc in %s line %d!\n", file, line);
    Int3();
    return (void *)MEM_NO_MEMORY_PTR;
  }
  mem_alloc_info *mi = NULL;
  mem_alloc_info no_track_mi;
  bool track_node = true;
#ifdef MEM_DEBUG
  if (!bail_now) {
    if (mem_info[Mem_next_slot].ptr == (void *)MEM_NO_MEMORY_PTR) {
      mi = &mem_info[Mem_next_slot];
      Mem_next_slot++;
      if (Mem_next_slot > Mem_highest_used_slot)
        Mem_highest_used_slot = Mem_next_slot;
    } else {
      for (int i = 0; i < MEM_MAX_MALLOCS; i++) {
        if (mem_info[i].ptr == (void *)MEM_NO_MEMORY_PTR) {
          mi = &mem_info[i];
          Mem_next_slot = i + 1;
          if (i > Mem_highest_used_slot)
            Mem_highest_used_slot = i;
          break;
        }
      }
    }
  }
  if (bail_now || (mi == NULL))
#else

#endif
  {

    mi = &no_track_mi;
    if (bail_now == false) {
      track_node = false;
#ifdef MEM_DEBUG
      mprintf(0, "Out of memory tracking slots!!!!\n");
#endif
    }
    bail_now = true;
  }
#ifndef MEM_DEBUG
  mi->ptr = HeapAlloc(Heap, HEAP_NO_SERIALIZE, size);
#else
  mi->ptr = HeapAlloc(Heap, HEAP_NO_SERIALIZE, size + 2);
  mi->len = size;
  uint16_t mem_sig = MEM_GAURDIAN_SIG;
  memcpy(((char *)mi->ptr) + size, (void *)&mem_sig, 2);
  int flen = strlen(file);
  int lofs = 0;
  // Strip down the filename to be < 16 bytes
  if (flen > 16)
    lofs = flen - 16;

  strcpy(mi->file, file + lofs);
  mi->line = line;
#ifdef MEM_LOGFILE
  fprintf(mem_out, "%s,%d,%d,%d\n", mi->file, mi->line, size, HeapSize(Heap, 0, mi->ptr));
#endif
#endif
  int errors;
  if (mi->ptr == NULL) {
    errors = GetLastError();
    mprintf(0, "Unable to alloc memory in mem_malloc_sub()!\n");
    Int3();
    ASSERT(mi->ptr);
    Error("Out of memory, unable to continue.");
    mem_error_msg(file, line, size);
    return 0;
  }

  retp = mi->ptr;

  Total_mem_used += size;
  if (Mem_high_water_mark < Total_mem_used) {
    Mem_high_water_mark = Total_mem_used;
  }
#ifdef MEM_DEBUG
  if (track_node)
    insertNode(mi);
#endif
  return retp;
#endif
}
// Frees a previously allocated block of memory
void mem_free_sub(void *memblock) {
#ifndef MEM_DEBUG
  if (Mem_quick_exit)
    return;
#endif
#ifdef MEM_USE_RTL
  free(memblock);
  return;
#else
#if defined(WIN32)
  if (!Heap) {
    return;
  }
#endif
  if (memblock == 0)
    return;
  if ((void *)MEM_NO_MEMORY_PTR == memblock) {
    return;
  }
#ifdef MEM_DEBUG
  mem_alloc_info findmem;
  mem_alloc_info *freemem;
  findmem.ptr = memblock;
  Node *mynode = findNode(&findmem);
  if (mynode) {
    freemem = mynode->data;
    freemem->ptr = (void *)MEM_NO_MEMORY_PTR;
    uint16_t mem_sig = MEM_GAURDIAN_SIG;
    if (memcmp((char *)memblock + freemem->len, &mem_sig, 2) != 0) {
      // Corrupted memory found when we went to free it.
      mprintf(0, "Memory block found to be damaged when it was freed!\n");
      Int3();
    }
    Total_mem_used -= freemem->len;
    HeapFree(Heap, HEAP_NO_SERIALIZE, memblock);
    deleteNode(mynode->data);
    return;
  } else {
    mprintf(0, "Warning, hash lookup of memory block failed!\n");
    HeapFree(Heap, HEAP_NO_SERIALIZE, memblock);
    return;
  }
#endif
  HeapFree(Heap, HEAP_NO_SERIALIZE, memblock);
#endif
}
int handle_program_memory_depletion(size_t size) {
  // Release character buffer memory.
  mem_free(Mem_failsafe_block);
  Mem_failsafe_block = NULL;
  Error("Unable to allocate %d bytes of memory.", size);
  // Tell new to stop allocation attempts.
  return 0;
}
//	prints out a memory error message
void mem_error_msg(const char *file, int line, int size) {
  Error("Attempt to allocate %d bytes of memory in %s line %d failed.", size, file, line);
}
// int strdup_malloc_line = 0;
char *mem_strdup_sub(const char *src, const char *file, int line) {
#if defined(WIN32)
  if (!Heap) {
    return 0;
  }
#endif
  int len = strlen(src) + 1;
  // strdup_malloc_line = __LINE__+1;
  // Leave this line here!
  char *dest = (char *)mem_malloc_sub(len, file, line);
  strcpy(dest, src);
  return dest;
}
void *mem_realloc_sub(void *memblock, int size) {
#ifdef MEM_USE_RTL
  void *retp = realloc(memblock, size);
  return retp;
#else
#if defined(WIN32)
  if (!Heap) {
    return 0;
  }
#endif
  if ((void *)MEM_NO_MEMORY_PTR == memblock) {
    return mem_malloc(size);
  }
#ifdef MEM_DEBUG
  for (int i = 0; i < MEM_MAX_MALLOCS; i++) {
    if (mem_info[i].ptr == (void *)memblock) {
      mem_info[i].ptr = (void *)MEM_NO_MEMORY_PTR;
      Total_mem_used -= mem_info[i].len;

      deleteNode(&mem_info[i]);

      mem_info[i].ptr = HeapReAlloc(Heap, 0, memblock, size + 2);
      uint16_t mem_sig = MEM_GAURDIAN_SIG;
      memcpy(((char *)mem_info[i].ptr) + size, (void *)&mem_sig, 2);
      mem_info[i].len = size;
      Total_mem_used += size;

      insertNode(&mem_info[i]);

      return mem_info[i].ptr;
    }
  }
#endif
  void *retp = HeapReAlloc(Heap, 0, memblock, size);
  return retp;
#endif
}

int mem_size_sub(void *memblock) {
#ifdef MEM_USE_RTL
  return _msize(memblock);
#else // MEM_USE_RTL
#if defined(WIN32)
  if (!Heap) {
    return 0;
  }
#endif
  if ((void *)MEM_NO_MEMORY_PTR == memblock) {
    return 0;
  }
  return HeapSize(Heap, 0, memblock);
#endif
}

void mem_shutdown();
MemClass::~MemClass() { mem_shutdown(); }
//	memory routines
void mem_shutdown() {
  //	free failsafe memory block.
  mprintf(0, "Shutting down memory system.\n");
  if (Mem_failsafe_block) {
    mem_free(Mem_failsafe_block);
    Mem_failsafe_block = NULL;
  }
#ifdef MEM_DEBUG
  free(hashTable);
  if (Total_mem_used)
    mprintf(0, "%d bytes leaked in mem_malloc heap!\n", Total_mem_used);
#ifdef MEM_LOGFILE
  fclose(mem_out);
#endif
  mprintf(0, "Looking for memory leaks.\n");
  for (int i = 0; i < MEM_MAX_MALLOCS; i++) {
    if (mem_info[i].ptr != (void *)MEM_NO_MEMORY_PTR) {
      mprintf(0, "Memory leaked from %s line %d length %d.\n", mem_info[i].file, mem_info[i].line, mem_info[i].len);
      /*
      //mprintf(0,"%d\n",strdup_malloc_line);
      if( (strcmp(mem_info[i].file,"main\\mem\\mem.cpp")==0) && (mem_info[i].line==(strdup_malloc_line+1)) )
      {

              mprintf(0,"Memory leak from mem_strdup() (%s)\n",mem_info[i].ptr);
      }
      */
    }
  }
  mprintf(0, "Done looking for memory leaks.\n");
  mprintf(0, "Memory library high water mark: %d\n", Mem_high_water_mark);
  Mem_next_slot = 0;
#endif
  if (Heap) {
    HeapDestroy(Heap);
    Heap = NULL;
  }
}

#ifdef MEM_DEBUG
// accessory stuff for mem_dumpallocstofile()
struct allocdumpt {
  mem_alloc_info *data;
};

static int *sorted_allocs = NULL;

int mem_allocdump_cmp(allocdumpt *elem1, allocdumpt *elem2) {
  int res;
  res = strcmp(elem1->data->file, elem2->data->file);
  if (res != 0)
    return (res < 0) ? -1 : 1;

  if (elem1->data->line < elem2->data->line)
    return -1;
  else if (elem1->data->line > elem2->data->line)
    return 1;

  if (elem1->data->len < elem2->data->len)
    return -1;
  else if (elem1->data->len > elem2->data->len)
    return 1;

  return 0;
}

#endif

bool mem_dumpmallocstofile(char *filename) {
#ifdef MEM_DEBUG
  FILE *file;
  file = fopen(filename, "wt");
  if (!file)
    return false;

  int h_table_idx, num_allocs = 0;
  mem_alloc_info *alloc_info;
  char buffer[384];

  for (h_table_idx = 0; h_table_idx < MEM_MAX_MALLOCS; h_table_idx++) {
    if (mem_info[h_table_idx].ptr != (void *)MEM_NO_MEMORY_PTR) {
      num_allocs++;
    }
  }

  allocdumpt *allocs;
  int curr_idx, i;
  allocs = (allocdumpt *)malloc(sizeof(allocdumpt) * num_allocs);
  sorted_allocs = (int *)malloc(sizeof(int) * num_allocs);
  curr_idx = 0;

  for (h_table_idx = 0; h_table_idx < MEM_MAX_MALLOCS; h_table_idx++) {
    if (mem_info[h_table_idx].ptr != (void *)MEM_NO_MEMORY_PTR) {
      allocs[curr_idx++].data = &mem_info[h_table_idx];
    }
  }

  // sort the list of allocs for easier reading
  for (i = 0; i < num_allocs; i++)
    sorted_allocs[i] = i;
  qsort(allocs, num_allocs, sizeof(allocdumpt), (int (*)(const void *, const void *))mem_allocdump_cmp);

  // dump it out
  int last_unique;
  last_unique = -1;

  for (i = 0; i < num_allocs; i++) {
    curr_idx = sorted_allocs[i];
    alloc_info = (mem_alloc_info *)allocs[curr_idx].data;

    if (last_unique != -1) {
      // see if we are just repeating
      mem_alloc_info *last_alloc;
      last_alloc = (mem_alloc_info *)allocs[sorted_allocs[last_unique]].data;
      if ((!strcmp(last_alloc->file, alloc_info->file)) && (last_alloc->line == alloc_info->line)) {
        // its the same!
        continue;
      }
    }

    last_unique = i;

    if (i < num_allocs - 1) {
      // see if we have multiple of the same line
      mem_alloc_info *next_alloc;
      next_alloc = (mem_alloc_info *)allocs[sorted_allocs[i + 1]].data;
      if ((!strcmp(next_alloc->file, alloc_info->file)) && (next_alloc->line == alloc_info->line)) {
        // we have multiple of the same line!
        // see how many we have of this line
        int repeat_count = 1;
        int total_size = alloc_info->len;
        i++;
        while (i < num_allocs) {
          next_alloc = (mem_alloc_info *)allocs[sorted_allocs[i]].data;
          if ((!strcmp(next_alloc->file, alloc_info->file)) && (next_alloc->line == alloc_info->line)) {
            repeat_count++;
            total_size += next_alloc->len;
          } else {
            break;
          }
          i++;
        }

        sprintf(buffer, "\n--Repeated %d Times--\n", repeat_count);
        fputs(buffer, file);

        sprintf(buffer, "*[%d bytes total]\tFile %s Line %d\n", total_size, alloc_info->file, alloc_info->line);
        fputs(buffer, file);

        continue;
      }
    }

    sprintf(buffer, "[%d bytes]\tFile %s Line %d\n", alloc_info->len, alloc_info->file, alloc_info->line);
    fputs(buffer, file);
  }

  free(sorted_allocs);
  free(allocs);

  fclose(file);
  return true;
#else
  return false;
#endif
}

void mem_heapcheck(void) {
#ifdef MEM_DEBUG
  for (int i = 0; i < MEM_MAX_MALLOCS; i++) {
    mem_alloc_info *freemem;
    if (mem_info[i].ptr == (void *)MEM_NO_MEMORY_PTR)
      continue;
    freemem = &mem_info[i];
    uint16_t mem_sig = MEM_GAURDIAN_SIG;
    if (memcmp((char *)freemem->ptr + freemem->len, &mem_sig, 2) != 0) {
      mprintf(0, "Memory block found to be damaged in mem_heapcheck()!\n");
      mprintf(0, "Originally allocated from file %s, line %d\n", freemem->file, freemem->line);
      Int3();
    }
  }
#endif
}
hashTableIndex hash(T data) {
  /***********************************
   *  hash function applied to data  *
   ***********************************/
  uint32_t hval = (uint32_t)data->ptr;
  return (hval % MEM_MAX_MALLOCS);
}
Node *insertNode(T data) {
  Node *p, *p0;
  hashTableIndex bucket;
  /************************************************
   *  allocate node for data and insert in table  *
   ************************************************/
  /* insert node at beginning of list */
  bucket = hash(data);
  if ((p = (Node *)malloc(sizeof(Node))) == 0) {
    fprintf(stderr, "out of memory (insertNode)\n");
    exit(1);
  }
  p0 = hashTable[bucket];
  hashTable[bucket] = p;
  p->next = p0;
  p->data = data;
  return p;
}
void deleteNode(T data) {
  Node *p0, *p;
  hashTableIndex bucket;
  /********************************************
   *  delete node containing data from table  *
   ********************************************/
  /* find node */
  p0 = 0;
  bucket = hash(data);
  p = hashTable[bucket];
  while (p && !compEQ(p->data, data)) {
    p0 = p;
    p = p->next;
  }
  if (!p)
    return;
  /* p designates node to delete, remove it from list */
  if (p0)
    /* not first node, p0 points to previous node */
    p0->next = p->next;
  else
    /* first node on chain */
    hashTable[bucket] = p->next;
  free(p);
}
Node *findNode(T data) {
  Node *p;
  /*******************************
   *  find node containing data  *
   *******************************/
  p = hashTable[hash(data)];
  while (p && !compEQ(p->data, data))
    p = p->next;
  return p;
}
#endif
