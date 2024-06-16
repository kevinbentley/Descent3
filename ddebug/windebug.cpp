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

 * $Logfile: /DescentIII/Main/win32/windebug.cpp $
 * $Revision: 33 $
 * $Date: 9/15/01 1:46p $
 * $Author: Kevin $
 *
 * Win32 Debugging 'kernal'
 *
 * $Log: /DescentIII/Main/win32/windebug.cpp $
 *
 * 33    9/15/01 1:46p Kevin
 * Added -nocrashbox to suppress crash dialog box
 *
 * 32    5/19/99 2:43a Jeff
 * handle some possible crashes.  The UCT->Localtime doesn't seem to work,
 * although it is setup correctly.
 *
 * 31    5/18/99 9:48p Kevin
 * adjust time to time zone for Jeff
 *
 * 30    5/07/99 5:46p Jason
 * changes for gamegauge release
 *
 * 29    4/18/99 1:18p Kevin
 * Demo2 build changes
 *
 * 28    4/12/99 7:14p Samir
 * added multiple pages per mono window.
 *
 * 27    4/01/99 11:07a Kevin
 * Added some more usefull debugging info
 *
 * 26    4/01/99 9:40a Matt
 * Fixed dump_text_to_clipboard.  It used to allocate a fixed number of
 * bytes to allow space for adding CRs to strings, but now I actually
 * count the number needed and allocate that much.
 *
 * 25    3/29/99 6:50p Kevin
 * Added some parameters to the log file
 *
 * 24    2/16/99 11:25a Kevin
 * Took out testing code.
 *
 * 23    2/16/99 12:36a Kevin
 * Fixes for release builds of OEM V3 and KAtmai
 *
 * 22    2/15/99 1:22p Kevin
 * Changes for GameGauge
 *
 * 21    2/13/99 1:56p Kevin
 *
 * 20    1/05/99 4:28p Kevin
 * Moved exception handling code to windebug.cpp
 *
 * 19    1/05/99 3:55p Kevin
 * Added structured exception handling
 *
 * 18    10/18/98 8:52p Matt
 * Revamped debug/error system.
 *
 * 17    10/12/98 10:20a Samir
 * added parameter to debug init.
 *
 * 16    10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 15    6/23/98 2:40p Matt
 * Added Yes/No/Cancel type to OutrageMessageBox() and
 * Debug_MesssageBox(), and changed return value from a bool to an
 * integer.
 *
 * 14    4/21/98 2:30p Matt
 * dump_text_to_clipboard() wasn't putting terminating null on text string
 *
 * 13    4/08/98 7:19p Samir
 * Added runtime debugging option.
 *
 * 12    4/07/98 9:21p Samir
 * Added volition's call stack and memory dump code.  This will only
 * happen if you run the game without the -debug argument.
 *
 * 11    4/03/98 5:15p Samir
 * Implemented simple debug message filtering.
 *
 * 10    3/20/98 2:43p Samir
 * Some better Int3 support.
 *
 * 9     1/29/98 12:24p Samir
 * Added logfile support.
 *
 * 8     1/28/98 4:45p Samir
 * Mono check stuff.
 *
 * 7     1/28/98 11:56a Samir
 * Code to check for monochrome debug.
 *
 * 6     1/28/98 11:17a Samir
 * Added debugbreak stuff.
 *
 * 5     10/15/97 3:05p Samir
 * NT mono output works.
 *
 * 4     10/13/97 2:41p Samir
 * Debug breaks now are macros to work depending on the operating system.
 *
 * 3     9/04/97 12:00p Matt
 * Changed Debug_MessageBox() to return bool instead of int, since it was
 * already being used that way.
 *
 * 2     7/28/97 3:46p Samir
 * NT mono stubbed out.
 *
 * 18    6/11/97 1:10p Samir
 * Fixed up function names.
 *
 * 17    3/31/97 3:50p Samir
 * MessageBox should be task modal.
 *
 * 16    3/18/97 2:14p Samir
 * DebugBreak called instead of Int3
 *
 * 15    3/17/97 8:10p Matt
 * Don't print to monochrome screen unless D3_MONO evironment var is set
 *
 * 14    3/14/97 4:15p Matt
 * Changed title of OutrageMessageBox() dialogs
 *
 * 13    3/10/97 12:29p Samir
 * Moved mono code and altered lowlevel console interface to machine
 * library.
 *
 * 12    3/10/97 11:13a Samir
 * Changes made to reflect deletion of OSDebug class from system
 *
 * 11    3/04/97 7:15p Samir
 * Fixed bug in message_box, caused an Int3.
 *
 * 10    3/04/97 1:00p Samir
 * Fixed return type prototype errors.
 *
 * 9     3/04/97 12:55p Samir
 * Added types of messageboxes.
 *
 * 8     3/03/97 5:07p Samir
 * stupid
 *
 * 7     3/03/97 4:36p Samir
 * Removed instances of pserror.h code.  this is a lower level lib than
 * that!
 *
 * 6     2/27/97 7:00p Samir
 * Removed windows.h from oewin_os.h and moved to library.
 *
 * 5     2/26/97 7:04p Samir
 * Added Win32 DebugBreak
 *
 * 4     2/18/97 7:00p Samir
 * Now print out last Win32 error too.
 *
 * 3     1/31/97 3:31p Samir
 * forgot to use OSWINDBG_MAX_STRINGS constant in array init.
 *
 * 2     1/30/97 6:49p Samir
 * Added some winDebug code for interface with error handler
 *
 * 1     1/28/97 2:32p Samir
 * Standard debugging functions
 *
 * $NoKeywords: $
 */

#include <windows.h>
#include <cstdarg>
#include <cstdlib>
#include <cstdint>

#include "d3_version.h"
#include "debug.h"
#include "mem.h"
#include "mono.h"

///////////////////////////////////////////////////////////////////////////////

bool Debug_break = false;

char *Debug_DumpInfo();

///////////////////////////////////////////////////////////////////////////////

bool Debug_Init(bool debugger, bool mono_debug) {
  // initialization of debugging consoles.

#ifndef RELEASE

  Debug_break = debugger;

  if (Debug_break) {
    mprintf(0, "Debug Break enabled.\n");
  }

#endif // ifndef RELEASE

  return true;
}

/*	Message Box functions  */

// Does a messagebox with a stack dump
// Messagebox shows topstring, then stack dump, then bottomstring
// Return types are as the same the Windows return values
int Debug_ErrorBox(int type, const char *title, const char *topstring, const char *bottomstring) {
  int answer;
  char *dumptext = Debug_DumpInfo();
  // HWND wnd = GetActiveWindow();

  // ShowWindow(wnd, SW_SHOWMINNOACTIVE);

  DWORD flags;
  if (type == OSMBOX_OK)
    flags = MB_OK;
  else if (type == OSMBOX_YESNO)
    flags = MB_YESNO;
  else if (type == OSMBOX_YESNOCANCEL)
    flags = MB_YESNOCANCEL;
  else if (type == OSMBOX_ABORTRETRYIGNORE)
    flags = MB_ABORTRETRYIGNORE;
  else if (type == OSMBOX_OKCANCEL)
    flags = MB_OKCANCEL;
  else
    debug_break();

  char *tmpbuf = (char *)mem_malloc(
      strlen(dumptext) + strlen(topstring) + strlen(bottomstring) +
                      10); // malloc(strlen(dumptext) + strlen(topstring) + strlen(bottomstring) + 10);

  strcpy(tmpbuf, topstring);
  if (dumptext[0]) {
    strcat(tmpbuf, "\r\n\r\n");
    strcat(tmpbuf, dumptext);
  }
  if (bottomstring[0]) {
    strcat(tmpbuf, "\r\n\r\n");
    strcat(tmpbuf, bottomstring);
  }

  wsprintf(tmpbuf, "%s\r\n\r\n%s\r\n\r\n%s", topstring, dumptext, bottomstring);

  ShowCursor(TRUE);
  answer = MessageBox(NULL, tmpbuf, title, flags | MB_TASKMODAL | MB_SETFOREGROUND); // what's MB_ICONHAND?
  ShowCursor(FALSE);

  // free(tmpbuf);
  mem_free(tmpbuf);

  //	ShowWindow(wnd, SW_SHOWMAXIMIZED);

  return answer;
}

// Return types are the same the Windows return values
int Debug_MessageBox(int type, const char *title, const char *str) {
  DWORD flags;
  int answer;
  HWND wnd = GetActiveWindow();

  if (type == OSMBOX_OK)
    flags = MB_OK;
  else if (type == OSMBOX_YESNO)
    flags = MB_YESNO;
  else if (type == OSMBOX_YESNOCANCEL)
    flags = MB_YESNOCANCEL;
  else if (type == OSMBOX_ABORTRETRYIGNORE)
    flags = MB_ABORTRETRYIGNORE;
  else
    DebugBreak();

  ShowCursor(TRUE);
  //	ShowWindow(wnd, SW_SHOWMINNOACTIVE);
  answer = MessageBox(nullptr, str, title, flags | MB_TASKMODAL | MB_SETFOREGROUND);
  ShowCursor(FALSE);
  //	ShowWindow(wnd, SW_SHOWMAXIMIZED);

  return answer;
}

///////////////////////////////////////////////////////////////////////////////
//	This CODE SHOULD ONLY BE USED IN A DEBUGGABLE VERSION.

#ifndef _WIN64
#define SHOW_CALL_STACK // Uncomment SHOW_CALL_STACK to show the call stack in terminal cases
// #define DUMPRAM
#endif // _WIN64

#ifdef SHOW_CALL_STACK

class DumpBuffer {
public:
  enum { BUFFER_SIZE = 32000 };
  DumpBuffer();
  void Clear();
  void Printf(const char *format, ...);
  void SetWindowText(HWND hWnd) const;
  char buffer[BUFFER_SIZE];

private:
  char *current;
};

class PE_Debug {
public:
  PE_Debug();
  ~PE_Debug();
  void ClearReport();
  int DumpDebugInfo(DumpBuffer &dumpBuffer, const BYTE *caller, HINSTANCE hInstance);
  void Display();

private:
  // Report data
  enum { MAX_MODULENAME_LEN = 512, VA_MAX_FILENAME_LEN = 256 };
  char latestModule[MAX_MODULENAME_LEN];
  char latestFile[VA_MAX_FILENAME_LEN];
  // File mapping data
  HANDLE hFile;
  HANDLE hFileMapping;
  PIMAGE_DOS_HEADER fileBase;
  // Pointers to debug information
  PIMAGE_NT_HEADERS NT_Header;
  PIMAGE_COFF_SYMBOLS_HEADER COFFDebugInfo;
  PIMAGE_SYMBOL COFFSymbolTable;
  int COFFSymbolCount;
  const char *stringTable;

  void ClearFileCache();
  void ClearDebugPtrs();
  void MapFileInMemory(const char *module);
  void FindDebugInfo();
  void DumpSymbolInfo(DumpBuffer &dumpBuffer, DWORD relativeAddress);
  void DumpLineNumber(DumpBuffer &dumpBuffer, DWORD relativeAddress);
  PIMAGE_COFF_SYMBOLS_HEADER GetDebugHeader();
  PIMAGE_SECTION_HEADER SectionHeaderFromName(const char *name);
  const char *GetSymbolName(PIMAGE_SYMBOL sym);
};

DumpBuffer ::DumpBuffer() { Clear(); }

void DumpBuffer ::Clear() { current = buffer; }

void DumpBuffer ::Printf(const char *format, ...) {
  // protect against obvious buffer overflow
  if (current - buffer < BUFFER_SIZE) {
    va_list argPtr;
    va_start(argPtr, format);
    int count = wvsprintf(current, format, argPtr);
    va_end(argPtr);
    current += count;
  }
}

void DumpBuffer ::SetWindowText(HWND hWnd) const { SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)buffer); }

///////////////////////////////////////////////////////////////////////////////

// Add an offset to a pointer and cast to a given type; may be
// implemented as a template function but Visual C++ has some problems.
#define BasedPtr(type, ptr, ofs) (type)((DWORD)(ptr) + (DWORD)(ofs))

PE_Debug ::PE_Debug() {
  // Init file mapping cache
  hFileMapping = 0;
  hFile = INVALID_HANDLE_VALUE;
  fileBase = 0;
  ClearDebugPtrs();
  ClearReport();
}

PE_Debug ::~PE_Debug() { ClearFileCache(); }

void PE_Debug ::ClearReport() {
  latestModule[0] = 0;
  latestFile[0] = 0;
}

void PE_Debug ::ClearDebugPtrs() {
  NT_Header = NULL;
  COFFDebugInfo = NULL;
  COFFSymbolTable = NULL;
  COFFSymbolCount = 0;
  stringTable = NULL;
}

void PE_Debug ::ClearFileCache() {
  if (fileBase) {
    UnmapViewOfFile(fileBase);
    fileBase = 0;
  }
  if (hFileMapping != 0) {
    CloseHandle(hFileMapping);
    hFileMapping = 0;
  }
  if (hFile != INVALID_HANDLE_VALUE) {
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
  }
}

void PE_Debug ::DumpLineNumber(DumpBuffer &dumpBuffer, DWORD relativeAddress) {
  PIMAGE_LINENUMBER line = BasedPtr(PIMAGE_LINENUMBER, COFFDebugInfo, COFFDebugInfo->LvaToFirstLinenumber);
  DWORD lineCount = COFFDebugInfo->NumberOfLinenumbers;
  const DWORD none = (DWORD)-1;
  DWORD maxAddr = 0;
  DWORD lineNum = none;
  for (DWORD i = 0; i < lineCount; i++) {
    if (line->Linenumber != 0) // A regular line number
    {
      // look for line with bigger address <= relativeAddress
      if (line->Type.VirtualAddress <= relativeAddress && line->Type.VirtualAddress > maxAddr) {
        maxAddr = line->Type.VirtualAddress;
        lineNum = line->Linenumber;
      }
    }
    line++;
  }
  if (lineNum != none)
    dumpBuffer.Printf("  line %d\r\n", lineNum);
  //  else
  //  dumpBuffer.Printf( "  line <unknown>\r\n" ) ;
}

const char *PE_Debug ::GetSymbolName(PIMAGE_SYMBOL sym) {
  const int NAME_MAX_LEN = 64;
  static char buf[NAME_MAX_LEN];
  if (sym->N.Name.Short != 0) {
    strncpy(buf, (const char *)sym->N.ShortName, 8);
    buf[8] = 0;
  } else {
    strncpy(buf, stringTable + sym->N.Name.Long, NAME_MAX_LEN);
    buf[NAME_MAX_LEN - 1] = 0;
  }
  return (buf);
}

void unmangle(char *dst, const char *src) {
  // strcpy( dst, src );
  // return;

  src++;
  while ((*src) && (*src != ' ') && (*src != '@')) {
    *dst++ = *src++;
  }
  *dst++ = 0;
}

#ifdef DUMPRAM

struct MemSymbol {
  int section;
  int offset;
  int size;
  char name[132];
};

int Num_symbols = 0;
int Max_symbols = 0;
MemSymbol *Symbols;

void InitSymbols() {
  Num_symbols = 0;
  Max_symbols = 5000;
  Symbols = (MemSymbol *)mem_malloc(Max_symbols * sizeof(MemSymbol));
  if (!Symbols) {
    Max_symbols = 0;
  }
}

void Add_Symbol(int section, int offset, const char *name, char *module) {
  if (Num_symbols >= Max_symbols) {
    return;
  }

  MemSymbol *sym = &Symbols[Num_symbols++];

  sym->section = section;
  sym->offset = offset;
  sym->size = -1;

  strcpy(sym->name, name);
  strcat(sym->name, "(");
  strcat(sym->name, module);
  strcat(sym->name, ")");
}

int Sym_compare(const void *arg1, const void *arg2) {
  MemSymbol *sym1 = (MemSymbol *)arg1;
  MemSymbol *sym2 = (MemSymbol *)arg2;

  if (sym1->section < sym2->section) {
    return -1;
  } else if (sym1->section > sym2->section) {
    return 1;
  } else {
    if (sym1->offset > sym2->offset) {
      return 1;
    } else {
      return -1;
    }
  }
}

int Sym_compare1(const void *arg1, const void *arg2) {
  MemSymbol *sym1 = (MemSymbol *)arg1;
  MemSymbol *sym2 = (MemSymbol *)arg2;

  if (sym1->size < sym2->size) {
    return 1;
  } else if (sym1->size > sym2->size) {
    return -1;
  } else {
    return 0;
  }
}

void DumpSymbols() {
  int i;

  qsort(Symbols, Num_symbols, sizeof(MemSymbol), Sym_compare);

  for (i = 0; i < Num_symbols; i++) {
    MemSymbol *sym1 = &Symbols[i];
    MemSymbol *sym2 = &Symbols[i + 1];
    if ((i < Num_symbols - 1) && (sym1->section == sym2->section)) {
      sym1->size = sym2->offset - sym1->offset;
    } else {
      sym1->size = -1;
    }
  }

  qsort(Symbols, Num_symbols, sizeof(MemSymbol), Sym_compare1);

  FILE *fp = fopen("memory.out", "wt");

  fprintf(fp, "%-60s %8s %8s\n", "Name", "Size", "Total");

  int total_size = 0;
  for (i = 0; i < Num_symbols; i++) {
    MemSymbol *sym = &Symbols[i];
    if (sym->size > 0)
      total_size += sym->size;
    fprintf(fp, "%-60s %8d %8d\n", sym->name, sym->size, total_size);
  }

  fclose(fp);

  mem_free(Symbols);
  Symbols = NULL;
  _asm int 3
}
#endif

void PE_Debug::DumpSymbolInfo(DumpBuffer &dumpBuffer, DWORD relativeAddress) {
  // Variables to keep track of function symbols
  PIMAGE_SYMBOL currentSym = COFFSymbolTable;
  PIMAGE_SYMBOL fnSymbol = NULL;
  DWORD maxFnAddress = 0;

#ifdef DUMPRAM
  InitSymbols();
#endif

  // Variables to keep track of file symbols
  PIMAGE_SYMBOL fileSymbol = NULL;
  PIMAGE_SYMBOL latestFileSymbol = NULL;
  for (int i = 0; i < COFFSymbolCount; i++) {

    // Look for .text section where relativeAddress belongs to.
    // Keep track of the filename the .text section belongs to.
    if (currentSym->StorageClass == IMAGE_SYM_CLASS_FILE) {
      latestFileSymbol = currentSym;
    }

    // Borland uses "CODE" instead of the standard ".text" entry
    // Microsoft uses sections that only _begin_ with .text
    const char *symName = GetSymbolName(currentSym);

    if (strnicmp(symName, ".text", 5) == 0 || stricmp(symName, "CODE") == 0) {
      if (currentSym->Value <= relativeAddress) {
        PIMAGE_AUX_SYMBOL auxSym = (PIMAGE_AUX_SYMBOL)(currentSym + 1);
        if (currentSym->Value + auxSym->Section.Length >= relativeAddress) {
          fileSymbol = latestFileSymbol;
        }
      }
    }

    // Look for the function with biggest address <= relativeAddress
    BOOL isFunction = ISFCN(currentSym->Type); // Type == 0x20, See WINNT.H
    if (isFunction &&
        (currentSym->StorageClass == IMAGE_SYM_CLASS_EXTERNAL || currentSym->StorageClass == IMAGE_SYM_CLASS_STATIC)) {

      if (currentSym->Value <= relativeAddress && currentSym->Value > maxFnAddress) {
        maxFnAddress = currentSym->Value;
        fnSymbol = currentSym;
      }
    }

#ifdef DUMPRAM
    if (!isFunction && (currentSym->SectionNumber > -1)) {
      if ((symName[0] == '_' && symName[1] != '$') || (symName[0] == '?')) {

        char pretty_module[1024];

        if (fileSymbol) {
          const char *auxSym = (const char *)(latestFileSymbol + 1);
          char tmpFile[VA_MAX_FILENAME_LEN];
          strcpy(tmpFile, auxSym);
          strcpy(pretty_module, tmpFile);
          char *p = pretty_module + strlen(pretty_module) - 1;
          // Move p to point to first letter of EXE filename
          while ((*p != '\\') && (*p != '/') && (*p != ':'))
            p--;
          p++;
          if (strlen(p) < 1) {
            strcpy(pretty_module, "<unknown>");
          } else {
            memmove(pretty_module, p, strlen(p) + 1);
          }
        } else {
          strcpy(pretty_module, "");
        }

        Add_Symbol(currentSym->SectionNumber, currentSym->Value, symName, pretty_module);
      }
    }
#endif

    // Advance counters, skip aux symbols
    i += currentSym->NumberOfAuxSymbols;
    currentSym += currentSym->NumberOfAuxSymbols;
    currentSym++;
  }

#ifdef DUMPRAM
  DumpSymbols();
#endif

  // dump symbolic info if found
  if (fileSymbol) {
    const char *auxSym = (const char *)(fileSymbol + 1);

    if (stricmp(latestFile, auxSym)) {
      strcpy(latestFile, auxSym);
      // JAS      dumpBuffer.Printf( "  file: %s\r\n", auxSym ) ;
    }
  } else {
    latestFile[0] = 0;
    // JAS    dumpBuffer.Printf( "  file: unknown\r\n" ) ;
  }

  if (fnSymbol) {
    char tmp_name[1024];
    unmangle(tmp_name, GetSymbolName(fnSymbol));
    dumpBuffer.Printf("    %s()", tmp_name);
  } else {
    dumpBuffer.Printf("    <unknown>");
  }
}

PIMAGE_SECTION_HEADER PE_Debug ::SectionHeaderFromName(const char *name) {
  PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(NT_Header);
  for (unsigned i = 0; i < NT_Header->FileHeader.NumberOfSections; i++) {
    if (strnicmp((const char *)section->Name, name, IMAGE_SIZEOF_SHORT_NAME) == 0)
      return (section);
    else
      section++;
  }
  return 0;
}

PIMAGE_COFF_SYMBOLS_HEADER PE_Debug ::GetDebugHeader() {
  // Some files have a wrong entry in the COFF header, so
  // first check if the debug info exists at all
  if (NT_Header->FileHeader.PointerToSymbolTable == 0)
    return (0);
  DWORD debugDirRVA = NT_Header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress;
  if (debugDirRVA == 0)
    return (0);

  // The following values must be calculated differently for MS/Borland files
  PIMAGE_DEBUG_DIRECTORY debugDir;
  DWORD size;

  // Borland files have the debug directory at the beginning of a .debug section
  PIMAGE_SECTION_HEADER debugHeader = SectionHeaderFromName(".debug");
  if (debugHeader && debugHeader->VirtualAddress == debugDirRVA) {
    debugDir = (PIMAGE_DEBUG_DIRECTORY)(debugHeader->PointerToRawData + (DWORD)fileBase);
    size = NT_Header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size * sizeof(IMAGE_DEBUG_DIRECTORY);
  } else
  // Microsoft debug directory is in the .rdata section
  {
    debugHeader = SectionHeaderFromName(".rdata");
    if (debugHeader == 0)
      return (0);
    size = NT_Header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
    DWORD offsetInto_rdata = debugDirRVA - debugHeader->VirtualAddress;
    debugDir = BasedPtr(PIMAGE_DEBUG_DIRECTORY, fileBase, debugHeader->PointerToRawData + offsetInto_rdata);
  }

  // look for COFF debug info
  DWORD debugFormats = size / sizeof(IMAGE_DEBUG_DIRECTORY);
  for (DWORD i = 0; i < debugFormats; i++) {
    if (debugDir->Type == IMAGE_DEBUG_TYPE_COFF)
      return ((PIMAGE_COFF_SYMBOLS_HEADER)((DWORD)fileBase + debugDir->PointerToRawData));
    else
      debugDir++;
  }
  return (NULL);
}

void PE_Debug ::FindDebugInfo() {
  ClearDebugPtrs();
  // Put everything into a try/catch in case the file has wrong fields
  try {
    // Verify that fileBase is a valid pointer to a DOS header
    if (fileBase && fileBase->e_magic == IMAGE_DOS_SIGNATURE) {
      // Get a pointer to the PE header
      NT_Header = BasedPtr(PIMAGE_NT_HEADERS, fileBase, fileBase->e_lfanew);

      // Verify that NT_Header is a valid pointer to a NT header
      if (NT_Header && NT_Header->Signature == IMAGE_NT_SIGNATURE) {
        // Get a pointer to the debug header if any
        COFFDebugInfo = GetDebugHeader();

        // Get a pointer to the symbol table and retrieve the number of symbols
        if (NT_Header->FileHeader.PointerToSymbolTable)
          COFFSymbolTable = BasedPtr(PIMAGE_SYMBOL, fileBase, NT_Header->FileHeader.PointerToSymbolTable);
        COFFSymbolCount = NT_Header->FileHeader.NumberOfSymbols;

        // The string table starts right after the symbol table
        stringTable = (const char *)(COFFSymbolTable + COFFSymbolCount);
      }
    }
  } catch (...) {
    // Header wrong, do nothing
  }
}

void PE_Debug ::MapFileInMemory(const char *module) {
  ClearFileCache();
  hFile = CreateFile(module, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile != INVALID_HANDLE_VALUE) {
    hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hFileMapping != 0)
      fileBase = (PIMAGE_DOS_HEADER)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
  }
  // NB: open files/mapping are closed later in ClearFileCache
}

int PE_Debug::DumpDebugInfo(DumpBuffer &dumpBuffer, const BYTE *caller, HINSTANCE hInstance) {
  // Avoid to open, map and looking for debug header/symbol table
  // by caching the latest and comparing the actual module with
  // the latest one.
  static char module[MAX_MODULENAME_LEN];
  GetModuleFileName(hInstance, module, MAX_MODULENAME_LEN);

  // New module
  if (stricmp(latestModule, module)) {
    strcpy(latestModule, module);
    // JAS    dumpBuffer.Printf( "Module: %s\r\n", module );
    MapFileInMemory(module);
    FindDebugInfo();
  }

  char pretty_module[1024];

  strcpy(pretty_module, module);
  char *p = pretty_module + strlen(pretty_module) - 1;
  // Move p to point to first letter of EXE filename
  while ((*p != '\\') && (*p != '/') && (*p != ':'))
    p--;
  p++;
  if (strlen(p) < 1) {
    strcpy(pretty_module, "<unknown>");
  } else {
    memmove(pretty_module, p, strlen(p) + 1);
  }

  if (fileBase) {
    // Put everything into a try/catch in case the file has wrong fields
    try {
      DWORD relativeAddress = caller - (BYTE *)hInstance;
      // Dump symbolic information and line number if available
      if (COFFSymbolCount != 0 && COFFSymbolTable != NULL) {
        DumpSymbolInfo(dumpBuffer, relativeAddress);
        if (COFFDebugInfo)
          DumpLineNumber(dumpBuffer, relativeAddress);
        return 1;
      } else {
        // dumpBuffer.Printf( "Call stack is unavailable, because there is\r\nno COFF debugging info in this
        // module.\r\n" ) ; JAS dumpBuffer.Printf( "  no debug information\r\n" ) ;
        dumpBuffer.Printf("    %s %08x()\r\n", pretty_module, caller);
        return 0;
      }
    } catch (...) {
      // Header wrong, do nothing
      return 0;
    }
  } else {
    dumpBuffer.Printf("    %s %08x()\r\n", pretty_module, caller);
    // JAS dumpBuffer.Printf( "  module not accessible\r\n" ) ;
    // JAS dumpBuffer.Printf( "    address: %8X\r\n", caller ) ;
    return 0;
  }
}

void DumpCallsStack(DumpBuffer &dumpBuffer) {
  const char *separator = "------------------------------------------------------------------\r\n";
  static PE_Debug PE_debug;

  dumpBuffer.Printf("\r\nCall stack:\r\n");
  dumpBuffer.Printf(separator);

  // The structure of the stack frames is the following:
  // EBP -> parent stack frame EBP
  //        return address for this call ( = caller )
  // The chain can be navigated iteratively, after the
  // initial value of EBP is loaded from the register
  DWORD parentEBP, retval;
  MEMORY_BASIC_INFORMATION mbi;
  HINSTANCE hInstance;

  int depth = 0;

  __asm MOV parentEBP, EBP

      do {
    depth++;
    if (depth > 16)
      break;

    if ((parentEBP & 3) || IsBadReadPtr((DWORD *)parentEBP, sizeof(DWORD))) {
      break;
    }
    parentEBP = *(DWORD *)parentEBP;

    BYTE **NextCaller = ((BYTE **)parentEBP + 1);

    if (IsBadReadPtr(NextCaller, sizeof(BYTE *))) {
      break;
    }

    BYTE *caller = *NextCaller; // Error sometimes!!!

    // Skip the first EBP as it points to AssertionFailed, which is
    // uninteresting for the user

    if (depth > 1) {

      // Get the instance handle of the module where caller belongs to
      retval = VirtualQuery(caller, &mbi, sizeof(mbi));

      // The instance handle is equal to the allocation base in Win32
      hInstance = (HINSTANCE)mbi.AllocationBase;

      if ((retval == sizeof(mbi)) && hInstance) {
        if (!PE_debug.DumpDebugInfo(dumpBuffer, caller, hInstance)) {
          // break;
        }
      } else {
        break; // End of the call chain
      }
    }
  }
  while (TRUE)
    ;

  dumpBuffer.Printf(separator);
  PE_debug.ClearReport(); // Prepare for future calls
}

// This ought to be local to VerboseAssert, but it
// causes problems in Visual C++ (in the CRTL init phase)
static DumpBuffer dumpBuffer;

#endif // SHOW_CALL_STACK

///////////////////////////////////////////////////////////////////////////////

void dump_text_to_clipboard(char *text);

char *Debug_DumpInfo() {
#ifdef SHOW_CALL_STACK
  dumpBuffer.Clear();
  DumpCallsStack(dumpBuffer);
  dump_text_to_clipboard(dumpBuffer.buffer);

  dumpBuffer.Printf("\r\n[ This info has been copied to the clipboard for pasting to a bug report. ]\r\n");

  return dumpBuffer.buffer;
#else
  return ("");
#endif
}

///////////////////////////////////////////////////////////////////////////////

void DumpTextToClipboard(char *text) {
  char *ptr;

  // Count number of carriage returns to be added
  char last_char = 0;
  int extra = 0;
  ptr = text;
  while (*ptr) {
    if ((*ptr == '\n') && (last_char != '\r')) {
      extra++;
    }
    last_char = *ptr++;
  }

  // Length of string with CRs added
  int len = strlen(text) + extra + 1;

  char *h_text = (char *)mem_malloc(len);
  if (!h_text)
    return;
  if (!ptr)
    return;

  // copy then, if you find any \n's without \r's, then add in the \r.
  last_char = 0;
  while (*text) {
    if ((*text == '\n') && (last_char != '\r')) {
      *ptr++ = '\r';
    }
    last_char = *text;
    *ptr++ = last_char;
    text++;
  }
  *ptr = 0; // terminate string
  GlobalUnlock(h_text);
  OpenClipboard(NULL);
  EmptyClipboard();
  SetClipboardData(CF_TEXT, h_text);
  CloseClipboard();
}

void dump_text_to_clipboard(char *text) { DumpTextToClipboard(text); }

// Translate the exception code into something human readable.

static const char *GetExceptionDescription(DWORD ExceptionCode) {
  struct ExceptionNames {
    DWORD ExceptionCode;
    char *ExceptionName;
  };

  ExceptionNames ExceptionMap[] = {
      {0x40010005, "a Control-C"},
      {0x40010008, "a Control-Break"},
      {0x80000002, "a Datatype Misalignment"},
      {0x80000003, "a Breakpoint"},
      {0xc0000005, "an Access Violation"},
      {0xc0000006, "an In Page Error"},
      {0xc0000017, "a No Memory"},
      {0xc000001d, "an Illegal Instruction"},
      {0xc0000025, "a Noncontinuable Exception"},
      {0xc0000026, "an Invalid Disposition"},
      {0xc000008c, "a Array Bounds Exceeded"},
      {0xc000008d, "a Float Denormal Operand"},
      {0xc000008e, "a Float Divide by Zero"},
      {0xc000008f, "a Float Inexact Result"},
      {0xc0000090, "a Float Invalid Operation"},
      {0xc0000091, "a Float Overflow"},
      {0xc0000092, "a Float Stack Check"},
      {0xc0000093, "a Float Underflow"},
      {0xc0000094, "an Integer Divide by Zero"},
      {0xc0000095, "an Integer Overflow"},
      {0xc0000096, "a Privileged Instruction"},
      {0xc00000fD, "a Stack Overflow"},
      {0xc0000142, "a DLL Initialization Failed"},
      {0xe06d7363, "a Microsoft C++ Exception"},
  };

  for (int i = 0; i < sizeof(ExceptionMap) / sizeof(ExceptionMap[0]); i++)
    if (ExceptionCode == ExceptionMap[i].ExceptionCode)
      return ExceptionMap[i].ExceptionName;

  return "Unknown exception type";
}

static void PrintFileTime(char *sztime, FILETIME ftime) {
  SYSTEMTIME systime, fixtime;
  *sztime = NULL;

  if (FileTimeToSystemTime(&ftime, &fixtime)) {
    if (SystemTimeToTzSpecificLocalTime(NULL, &fixtime, &systime)) {
      wsprintf(sztime, "%d/%d/%d %02d:%02d:%02d", systime.wMonth, systime.wDay, systime.wYear, systime.wHour,
               systime.wMinute, systime.wSecond);
    } else {
      wsprintf(sztime, "Unknown Time");
    }
  }
}

// Print information about a code module (DLL or EXE) such as its size,
// location, time stamp, etc.

static void ShowModuleInfo(HANDLE LogFile, HINSTANCE ModuleHandle) {
  char FmtString[2000];
  DWORD bytesout;
  char ModName[_MAX_PATH];
  __try {
    if (GetModuleFileName(ModuleHandle, ModName, sizeof(ModName)) > 0) {
      // If GetModuleFileName returns greater than zero then this must
      // be a valid code module address. Therefore we can try to walk
      // our way through its structures to find the link time stamp.
      IMAGE_DOS_HEADER *DosHeader = (IMAGE_DOS_HEADER *)ModuleHandle;
      if (IMAGE_DOS_SIGNATURE != DosHeader->e_magic)
        return;
      IMAGE_NT_HEADERS *NTHeader = (IMAGE_NT_HEADERS *)((char *)DosHeader + DosHeader->e_lfanew);
      if (IMAGE_NT_SIGNATURE != NTHeader->Signature)
        return;
      // Open the code module file so that we can get its file date
      // and size.
      HANDLE ModuleFile =
          CreateFile(ModName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
      char TimeBuffer[100] = "";
      DWORD FileSize = 0;
      if (ModuleFile != INVALID_HANDLE_VALUE) {
        FileSize = GetFileSize(ModuleFile, 0);
        FILETIME LastWriteTime;
        if (GetFileTime(ModuleFile, 0, 0, &LastWriteTime)) {
          PrintFileTime(TimeBuffer + lstrlen(TimeBuffer), LastWriteTime);
        }
        CloseHandle(ModuleFile);
      }

      wsprintf(FmtString, "%s,\taddr: 0x%08x\tsize:%d\t[%s]\r\n", ModName, ModuleHandle, FileSize,
               TimeBuffer); // NTHeader->FileHeader.TimeDateStamp,
      WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
    }
  }
  // Handle any exceptions by continuing from this point.
  __except (EXCEPTION_EXECUTE_HANDLER) {
  }
}

// Scan memory looking for code modules (DLLs or EXEs). VirtualQuery is used
// to find all the blocks of address space that were reserved or committed,
// and ShowModuleInfo will display module information if they are code
// modules.

static void RecordModuleList(HANDLE LogFile) {
  char FmtString[2000];
  DWORD bytesout;
  wsprintf(FmtString, "\r\n"
                      "Modules:\r\n");
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
  SYSTEM_INFO SystemInfo;
  GetSystemInfo(&SystemInfo);
  const size_t PageSize = SystemInfo.dwPageSize;
  // Set NumPages to the number of pages in the 4GByte address space,
  // while being careful to avoid overflowing ints.
  const size_t NumPages = 4 * size_t((1024 * 1024 * 1024) / PageSize);
  size_t pageNum = 0;
  void *LastAllocationBase = 0;
  while (pageNum < NumPages) {
    MEMORY_BASIC_INFORMATION MemInfo;
    if (VirtualQuery((void *)(pageNum * PageSize), &MemInfo, sizeof(MemInfo))) {
      if (MemInfo.RegionSize > 0) {
        // Adjust the page number to skip over this block of memory.
        pageNum += MemInfo.RegionSize / PageSize;
        if (MemInfo.State == MEM_COMMIT && MemInfo.AllocationBase > LastAllocationBase) {
          // Look for new blocks of committed memory, and try
          // recording their module names - this will fail
          // gracefully if they aren't code modules.
          LastAllocationBase = MemInfo.AllocationBase;
          ShowModuleInfo(LogFile, (HINSTANCE)LastAllocationBase);
        }
      } else
        pageNum += (64 * 1024) / PageSize;
    } else
      pageNum += (64 * 1024) / PageSize;
  }
}

// Record information about the user's system, such as processor type, amount
// of memory, etc.

static void RecordSystemInformation(HANDLE LogFile) {
  char FmtString[2000];
  DWORD bytesout;
  FILETIME CurrentTime;
  GetSystemTimeAsFileTime(&CurrentTime);
  char TimeBuffer[100];

  PrintFileTime(TimeBuffer, CurrentTime);

  wsprintf(FmtString, "Error occurred at %s.\r\n", TimeBuffer);
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
  char ModuleName[_MAX_PATH];
  if (GetModuleFileName(0, ModuleName, sizeof(ModuleName)) <= 0)
    lstrcpy(ModuleName, "Unknown");

  wsprintf(FmtString, "Module: %s.\r\n", ModuleName);
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);

  MEMORYSTATUS ms;
  ms.dwLength = sizeof(ms);
  GlobalMemoryStatus(&ms);
  // Print out the amount of physical memory, rounded up.
  wsprintf(FmtString, "System Memory Status:\r\n");
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
  wsprintf(FmtString, "Percent of memory in use: %d\r\n", ms.dwMemoryLoad);
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
  wsprintf(FmtString, "Bytes of physical memory : %d\r\n", ms.dwTotalPhys);
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
  wsprintf(FmtString, "Free physical memory bytes  : %d\r\n", ms.dwAvailPhys);
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
  wsprintf(FmtString, "Available virtual memory : %d\r\n\r\n", ms.dwAvailPageFile);
  WriteFile(LogFile, FmtString, lstrlen(FmtString), &bytesout, 0);
}
/*
extern bool Debug_break;
extern char *Debug_DumpInfo();
*/
#define FORMAT_REG                                                                                                     \
  "Registers:\r\nEAX=%08x CS=%04x EIP=%08x EFLGS=%08x\r\nEBX=%08x SS=%04x ESP=%08x EBP=%08x\r\nECX=%08x DS=%04x "      \
  "ESI=%08x FS=%04x\r\nEDX=%08x ES=%04x EDI=%08x GS=%04x\r\n"
#define FORMAT_SEP "\r\n--------------------------------------------------------------------------------\r\n"
#define FORMATCRLF "\r\n"

const int NumCodeBytes = 16;   // Number of code bytes to record.
const int MaxStackDump = 2048; // Maximum number of DWORDS in stack dumps.
const int StackColumns = 8;    // Number of columns in stack dump.

extern int no_debug_dialog;

int __cdecl RecordExceptionInfo(PEXCEPTION_POINTERS data, const char *Message) {
  static int BeenHere;
  if (BeenHere) // Going recursive! That must mean this routine crashed!
    return EXCEPTION_CONTINUE_SEARCH;
  BeenHere = true;

#ifndef _WIN64
  PEXCEPTION_RECORD Exception = data->ExceptionRecord;
  PCONTEXT Context = data->ContextRecord;
  const char *desc = GetExceptionDescription(Exception->ExceptionCode);

  // An Int3()
  if (0x80000003 == Exception->ExceptionCode) {
    BeenHere = false;
    return EXCEPTION_CONTINUE_SEARCH;
  }

  char topmsg[500];
  char tmpmsg[1000];
  char bottommsg[1000] = "";
  char callstack[1000] = "";

  wsprintf(topmsg, "Execution in %s was stopped by %s", Message, desc);

  wsprintf(bottommsg, FORMAT_REG, Context->Eax, Context->SegCs, Context->Eip, Context->EFlags, Context->Ebx,
           Context->SegSs, Context->Esp, Context->Ebp, Context->Ecx, Context->SegDs, Context->Esi, Context->SegFs,
           Context->Edx, Context->SegEs, Context->Edi, Context->SegGs);

  HANDLE LogFile =
      CreateFile("error.log", GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, 0);
  if (LogFile != INVALID_HANDLE_VALUE) {

    char *p = Debug_DumpInfo();
    lstrcpy(callstack, p);

    DWORD NumBytes;
    SetFilePointer(LogFile, 0, 0, FILE_END);

    WriteFile(LogFile, topmsg, lstrlen(topmsg), &NumBytes, 0);
    WriteFile(LogFile, FORMATCRLF, lstrlen(FORMATCRLF), &NumBytes, 0);

    char Username[100];
    DWORD unamelen = 99;
    char Machinename[200];
    DWORD cnamelen = 199;
    GetUserName(Username, &unamelen);
    GetComputerName(Machinename, &cnamelen);
    wsprintf(callstack, "Username: %s\r\nMachineName: %s\r\n", Username, Machinename);
    WriteFile(LogFile, callstack, lstrlen(callstack), &NumBytes, 0);

#if (defined(RELEASE) && (!defined(DEMO)))
    wsprintf(callstack, "Descent 3 Release build %s\r\n", D3_GIT_HASH);
    WriteFile(LogFile, callstack, lstrlen(callstack), &NumBytes, 0);
#endif
    RecordSystemInformation(LogFile);
    RecordModuleList(LogFile);

    WriteFile(LogFile, bottommsg, lstrlen(bottommsg), &NumBytes, 0);
    WriteFile(LogFile, FORMAT_SEP, lstrlen(FORMAT_SEP), &NumBytes, 0);

    DWORD *pStack = (DWORD *)Context->Esp;
    DWORD *pStackTop;
    __asm {
			mov	eax, fs:[4]
			mov pStackTop, eax
    }
    if (pStackTop > pStack + MaxStackDump) pStackTop = pStack + MaxStackDump;
    int Count = 0;

    char buffer[1000] = "";
    const int safetyzone = 50;
    char *nearend = buffer + sizeof(buffer) - safetyzone;
    char *output = buffer;
    while (pStack + 1 <= pStackTop) {
      if ((Count % StackColumns) == 0)
        output += wsprintf(output, "%08x: ", pStack);
      char *Suffix = " ";
      if ((++Count % StackColumns) == 0 || pStack + 2 > pStackTop)
        Suffix = "\r\n";
      output += wsprintf(output, "%08x%s", *pStack, Suffix);
      pStack++;
      // Check for when the buffer is almost full, and flush it to disk.
      if (output > nearend) {
        wsprintf(tmpmsg, "%s", buffer);
        WriteFile(LogFile, tmpmsg, lstrlen(tmpmsg), &NumBytes, 0);
        buffer[0] = 0;
        output = buffer;
      }
    }
    CloseHandle(LogFile);
  }

  if ((!Debug_break) && (!no_debug_dialog))
    Debug_ErrorBox(OSMBOX_OK, "Error", topmsg, bottommsg);
#endif // _WIN64

  if (no_debug_dialog)
    exit(0);
  BeenHere = false;
  if (Debug_break)
    return EXCEPTION_CONTINUE_SEARCH;
  else
    return EXCEPTION_EXECUTE_HANDLER;
}
