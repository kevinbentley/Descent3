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

 * $Logfile: /DescentIII/Main/czip/BitIO.cpp $
 * $Revision: 2 $
 * $Date: 8/27/98 3:26p $
 * $Author: Jeff $
 *
 * Bit input/output to a file
 *
 * $Log: /DescentIII/Main/czip/BitIO.cpp $
 *
 * 2     8/27/98 3:26p Jeff
 * intial creation
 *
 * 1     8/27/98 3:26p Jeff
 *
 * $NoKeywords: $
 */

#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <sys/stat.h>
#include <errno.h>
#include <Macros.h>
#include "CZip.h"

BITFILE *CZip::OpenInputBitFile(char *filename) {
  BITFILE *bit_file;
  bit_file = (BITFILE *)malloc(sizeof(BITFILE));
  if (!bit_file)
    return NULL;
  // bit_file->file = fopen(filename,"rb");
  bit_file->file = VFopen(filename, "rb");
  bit_file->rack = 0;
  bit_file->mask = 0x80;
  if (!bit_file->file) {
    free(bit_file);
    return NULL;
  }
  return (bit_file);
}

static bool fexist(const char *filename) {
  FILE *cfp;

  cfp = fopen(filename, "rb");

  if (!cfp) {            // Didn't get file.  Why?
    if (errno == EACCES) // File exists, but couldn't open it
      return true;       //..so say it exists on the disk
    return false;        // Say we didn't find the file
  }
  return true;
}

BITFILE *CZip::OpenOutputBitFile(char *filename) {
  BITFILE *bit_file;
  bit_file = (BITFILE *)malloc(sizeof(BITFILE));
  if (!bit_file)
    return NULL;
  // does file exist?
  if (fexist(filename)) {
    bit_file->file = VFopen(filename, "r+b");
  } else {
    bit_file->file = VFopen(filename, "wb");
  }

  bit_file->rack = 0;
  bit_file->mask = 0x80;
  if (!bit_file->file) {
    free(bit_file);
    return NULL;
  }
  return (bit_file);
}

void CZip::CloseInputBitFile(BITFILE *bfile) {
  // fclose(bfile->file);
  int size = VFclose(bfile->file);
  free(bfile);
}

void CZip::CloseOutputBitFile(BITFILE *bfile) {
  if (bfile->mask != 0x80) {
    // if(putc(bfile->rack,bfile->file) != bfile->rack ){
    if (VFputc(bfile->rack, bfile->file) != bfile->rack) {
      // fatal error closing file
    }
  }
  // fclose(bfile->file);
  int size = VFclose(bfile->file);
  free(bfile);
}

void CZip::FlushOutputBitFile(BITFILE *bfile) {
  if (bfile->mask != 0x80) {
    if (VFputc(bfile->rack, bfile->file) != bfile->rack) {
      // fatal error closing file
    }
    bfile->rack = 0;
    bfile->mask = 0x80;
  }
}

void CZip::OutputBit(BITFILE *bfile, int bit) {
  if (bit)
    bfile->rack |= bfile->mask;
  bfile->mask >>= 1;
  if (bfile->mask == 0) {
    // if(putc(bfile->rack,bfile->file)!=bfile->rack){
    if (VFputc(bfile->rack, bfile->file) != bfile->rack) {
      // fatal error
    }
    bfile->rack = 0;
    bfile->mask = 0x80;
  }
}

void CZip::OutputBits(BITFILE *bfile, uint32_t code, int count) {
  uint32_t mask;
  mask = 1L << (count - 1);
  while (mask != 0) {
    if (mask & code)
      bfile->rack |= bfile->mask;
    bfile->mask >>= 1;
    if (bfile->mask == 0) {
      // if(putc(bfile->rack,bfile->file)!=bfile->rack){
      if (VFputc(bfile->rack, bfile->file) != bfile->rack) {
        // fatal error
      }
      bfile->rack = 0;
      bfile->mask = 0x80;
    }
    mask >>= 1;
  }
}

int CZip::InputBit(BITFILE *bfile) {
  int value;
  if (bfile->mask == 0x80) {
    // bfile->rack = getc(bfile->file);
    bfile->rack = VFgetc(bfile->file);
    if (bfile->rack == EOF) {
      // fatal error
    }
  }
  value = bfile->rack & bfile->mask;
  bfile->mask >>= 1;
  if (bfile->mask == 0)
    bfile->mask = 0x80;
  return (value ? 1 : 0);
}

uint32_t CZip::InputBits(BITFILE *bfile, int bitcount) {
  uint32_t mask;
  uint32_t return_value;

  mask = 1L << (bitcount - 1);
  return_value = 0;
  while (mask != 0) {
    if (bfile->mask == 0x80) {
      // bfile->rack = getc(bfile->file);
      bfile->rack = VFgetc(bfile->file);
      if (bfile->rack == EOF) {
        // fatal error
      }
    }
    if (bfile->rack & bfile->mask)
      return_value |= mask;
    mask >>= 1;
    bfile->mask >>= 1;
    if (bfile->mask == 0)
      bfile->mask = 0x80;
  }
  return return_value;
}

void CZip::FilePrintBinary(FILE *file, uint32_t code, int bits) {
  uint32_t mask;
  mask = 1 << (bits - 1);
  while (mask != 0) {
    if (code & mask)
      fputc('1', file);
    else
      fputc('0', file);
    mask >>= 1;
  }
}

tVirtualFile *CZip::VFopen(const char *filename, const char *flags, int size) {
  tVirtualFile *f;
  f = (tVirtualFile *)malloc(sizeof(tVirtualFile));
  if (!f)
    return NULL;

  if (!filename) {
    // open a memory virtual file
    f->type = VFT_MEM;
    f->count = 0;
    f->size = size;
    f->file_size = 0;
    f->memory = (uint8_t *)malloc(size);
    if (!f->memory) {
      free(f);
      return NULL;
    }
  } else {
    // open a file

    f->type = VFT_FILE;
    f->count = 0;
    f->size = 0xFFFFFFFF;
    f->file = fopen(filename, flags);
    if (!f->file) {
      free(f);
      return NULL;
    }
    struct _stat st;
    _stat(filename, &st);
    f->file_size = st.st_size;
  }
  return f;
}

int CZip::VFclose(tVirtualFile *f) {
  int s = 0;
  if (!f)
    return s;

  s = f->file_size;

  if (f->type) {
    // memory
    if (f->memory)
      free(f->memory);
  } else {
    // file
    s = fseek(f->file, 0, SEEK_END);
    if (f->file)
      fclose(f->file);
  }
  free(f);
  return s;
}

int CZip::VFputc(int value, tVirtualFile *file) {
  int ret = value;
  if (file->type) {
    // memory
    if (file->count < file->size)
      file->memory[file->count] = value;
    else
      ret = EOF;
  } else {
    // disk
    ret = fputc(value, file->file);
  }
  if (ret != EOF)
    file->count++;
  if (file->count > file->file_size)
    file->file_size = file->count;
  return ret;
}

int CZip::VFgetc(tVirtualFile *file) {
  int ret = EOF;
  if (file->type) {
    // memory
    if (file->count < file->size)
      ret = file->memory[file->count];
  } else {
    // disk
    ret = fgetc(file->file);
  }

  if (ret != EOF)
    file->count++;
  if (file->count > file->file_size)
    file->file_size = file->count;
  return ret;
}

int CZip::VFwrite(void *buf, int size, int count, tVirtualFile *file) {
  uint8_t *buffer = (uint8_t *)buf;
  if (file->type) {
    // memory
    int c = std::min(count, (file->size - file->count) / size);
    for (int i = 0; i < c; i++) {
      memcpy(&file->memory[file->count], buffer, size);
      file->count += size;
      buffer += size;
    }
    if (file->count > file->file_size)
      file->file_size = file->count;
    return c;
  } else {
    // disk
    return fwrite(buffer, size, count, file->file);
  }
}

int CZip::VFread(void *buf, int size, int count, tVirtualFile *file) {
  uint8_t *buffer = (uint8_t *)buf;
  if (file->type) {
    // memory
    int c = std::min(count, (file->size - file->count) / size);
    for (int i = 0; i < c; i++) {
      memcpy(buffer, &file->memory[file->count], size);
      file->count += size;
      buffer += size;
    }
    if (file->count > file->file_size)
      file->file_size = file->count;
    return c;
  } else {
    // disk
    return fread(buffer, size, count, file->file);
  }
}

int CZip::VFtell(tVirtualFile *file) {
  if (file->type)
    return file->count;
  else
    return ftell(file->file);
}

int CZip::VFseek(tVirtualFile *file, int offset, int origin) {
  if (file->type) {
    switch (origin) {
    case SEEK_SET:
      if (file->size < offset || offset < 0)
        return 1;
      file->count = offset;
      if (file->count > file->file_size)
        file->file_size = file->count;
      return 0;
      break;
    case SEEK_CUR: {
      int newpos = file->count + offset;
      if (newpos < 0 || newpos >= file->size)
        return 1;
      file->count = newpos;
      if (file->count > file->file_size)
        file->file_size = file->count;
      return 0;
    } break;
    case SEEK_END:
      int newpos = file->file_size - 1 + offset;
      if (offset == 0 && newpos < 0)
        newpos = 0;
      if (newpos < 0 || newpos >= file->size)
        return 1;
      file->count = newpos;
      if (file->count > file->file_size)
        file->file_size = file->count;
      return 0;
      break;
    }
    return 1;
  } else
    return fseek(file->file, offset, origin);
}
