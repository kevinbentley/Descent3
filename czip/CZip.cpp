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

 * $Logfile: /DescentIII/Main/czip/CZip.cpp $
 * $Revision: 2 $
 * $Date: 8/27/98 3:26p $
 * $Author: Jeff $
 *
 * General CZip class functions
 *
 * $Log: /DescentIII/Main/czip/CZip.cpp $
 *
 * 2     8/27/98 3:26p Jeff
 * intial creation
 *
 * 1     8/27/98 3:26p Jeff
 *
 * $NoKeywords: $
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

#include "pserror.h"
#include "CZip.h"

CZip::CZip() {
  bfile = NULL;
  file = NULL;
  ok_to_raw_write = ok_to_raw_read = false;
}

CZip::~CZip() {}

// Opens an archive file for reading
//	open_raw = if this is true, then the file MUST be of the raw compressed type.  You cannot
//			open an OCF by raw.  If a raw type archive is opened, you may only use the read
//			byte type functions (ReadRaw*())
//	returns true on success
bool CZip::OpenInputArchive(char *filename, bool open_raw) {
  if (bfile)
    return false;

  m_bRawType = open_raw;
  bfile = OpenInputBitFile(filename);
  if (!bfile)
    return false;

  bool ret = false;

  // read in the header based on what type of file it is
  if (open_raw) {
    // it should be a raw compressed file
    uint8_t type;
    if (ReadRawHeader(bfile->file, &type)) {
      ret = true;
      m_iCompressionType = type;
      PrepareDecompressor(bfile);
    }
  } else {
    // it should be an OCF file
    uint8_t type;
    tFileInfo temp;
    if (ReadOCFHeader(bfile->file, &temp, &type)) {
      ret = true;
    }
    VFseek(bfile->file, 0, SEEK_SET);
    /*
                    tFileInfo *info;
                    int count = GetOCFFileList(bfile,&info);
                    if(count<=0 || !info)
                            printf("Unable to get filelist\n");
                    else{
                            for(int i=0;i<count;i++){
                                    printf("%s = %d =
       %d\n",info[i].filename,info[i].compressed_size,info[i].expanded_size);
                            }
                            free(info);
                    }
                    */
  }

  if (!ret && bfile != NULL) {
    CloseInputBitFile(bfile);
    bfile = NULL;
  }

  return ret;
}

// Opens an archive file for writing
//	open_raw = if this is true, then the output archive will be of the raw compressed type.
//			You must used the write byte type functions (WriteRaw*())
//	compression_type = You only need to specify this if you opened raw
//	returns true on success
bool CZip::OpenOutputArchive(char *filename, bool open_raw, int compression_type) {
  if (bfile)
    return false;
  bool ret = false;

  bfile = OpenOutputBitFile(filename);
  if (!bfile)
    return false;

  m_bRawType = open_raw;
  m_iCompressionType = compression_type;

  if (open_raw) {
    // write out header
    if (WriteRawHeader(bfile->file, compression_type)) {
      // everything's ok
      ret = true;
    }
    PrepareCompressor(bfile);
  } else {
    // can't do much here, since we don't know what file is going to be compressed yet
    ret = true;
  }

  if (!ret && bfile != NULL) {
    CloseInputBitFile(bfile);
    bfile = NULL;
  }

  return ret;
}

//	Reads in a Raw type file header
//	returns true on succes, if so, compr_type contains the compression type
bool CZip::ReadRawHeader(tVirtualFile *file, uint8_t *compr_type) {
  int magic_num;

  if (!VFread(&magic_num, sizeof(int), 1, file))
    return false;

  if (magic_num != 0x52415743)
    return false;

  // it looks good, get our compression type and scram
  uint8_t type;
  if (!VFread(&type, 1, 1, bfile->file))
    return false;

  // valid compression type?

  *compr_type = type;
  return true;
}

//	Writes out a Raw type file header
//	returns true on succes
bool CZip::WriteRawHeader(tVirtualFile *file, uint8_t compr_type) {
  int magic_num = 0x52415743;

  // check compression type!?

  if (!VFwrite(&magic_num, sizeof(int), 1, file))
    return false;

  if (!VFwrite(&compr_type, 1, 1, file))
    return false;

  return true;
}

//	Reads in an OCF header
//	returns true on success, info is filled in the appropriate values,compr_type is compression type
bool CZip::ReadOCFHeader(tVirtualFile *file, tFileInfo *info, uint8_t *compr_type) {
  int magic_num;

  if (!VFread(&magic_num, sizeof(int), 1, file))
    return false;

  if (magic_num != 0x4D495241)
    return false;

  // it looks good, its an OCF at least
  uint8_t version;
  if (!VFread(&version, 1, 1, file))
    return false;

  if (version != OCF_VERSION)
    return false;

  // version is corrent, fill in the rest
  uint8_t filename_size;
  char buffer[300];
  int lo_time, hi_time;
  uint8_t ctype;
  int compressed_size, expand_size;
  uint8_t last_ditch_value;

  if (!VFread(&filename_size, 1, 1, file))
    return false;

  if (filename_size <= 0)
    return false;

  if (!VFread(buffer, 1, filename_size, file))
    return false;
  buffer[filename_size] = '\0';

  if (!VFread(&lo_time, sizeof(int), 1, file))
    return false;

  if (!VFread(&hi_time, sizeof(int), 1, file))
    return false;

  if (!VFread(&ctype, 1, 1, file))
    return false;

  if (!VFread(&compressed_size, sizeof(int), 1, file))
    return false;

  if (!VFread(&expand_size, sizeof(int), 1, file))
    return false;

  if (!VFread(&last_ditch_value, 1, 1, file))
    return false;

  if (last_ditch_value != 0x01)
    return false;

  // everything went ok, *whew*
  *compr_type = ctype;
  strcpy(info->filename, buffer);
  info->lo_time = lo_time;
  info->hi_time = hi_time;
  info->compressed_size = compressed_size;
  info->expanded_size = expand_size;
  return true;
}

//	Writes out an OCF header
//	returns true on success
bool CZip::WriteOCFHeader(tVirtualFile *file, tFileInfo *info, uint8_t compr_type, int header_pos) {
  int magic_num = 0x4D495241;
  uint8_t filename_size;
  uint8_t last_ditch_value;
  uint8_t version;
  bool ret = false;

  int filepos = VFtell(file);         // save the position of the file restorfilepos:
  VFseek(file, header_pos, SEEK_SET); // get to the begining of the header

  if (!VFwrite(&magic_num, sizeof(int), 1, file))
    goto restorfilepos;

  version = OCF_VERSION;
  if (!VFwrite(&version, 1, 1, file))
    goto restorfilepos;

  // version is corrent, fill in the rest
  filename_size = strlen(info->filename);
  last_ditch_value = 0x01;

  if (!VFwrite(&filename_size, 1, 1, file))
    goto restorfilepos;

  if (!VFwrite(info->filename, 1, filename_size, file))
    goto restorfilepos;

  if (!VFwrite(&info->lo_time, sizeof(int), 1, file))
    goto restorfilepos;

  if (!VFwrite(&info->hi_time, sizeof(int), 1, file))
    goto restorfilepos;

  if (!VFwrite(&compr_type, 1, 1, file))
    goto restorfilepos;

  if (!VFwrite(&info->compressed_size, sizeof(int), 1, file))
    goto restorfilepos;

  if (!VFwrite(&info->expanded_size, sizeof(int), 1, file))
    goto restorfilepos;

  if (!VFwrite(&last_ditch_value, 1, 1, file))
    goto restorfilepos;

  ret = true;
restorfilepos:
  VFseek(file, filepos, SEEK_SET); // restore the file pos
  return ret;
}

//	Writes out a 'dummy' OCF header, just give what the final filename is
//	you must call this before you compress data, then when done, call the read WriteOCFHeader
bool CZip::WriteDummyOCFHeader(tVirtualFile *file, char *filename) {
  int itemp = 0;
  uint8_t btemp = 0;

  if (!VFwrite(&itemp, sizeof(int), 1, file))
    return false;

  if (!VFwrite(&btemp, 1, 1, file))
    return false;

  // version is corrent, fill in the rest
  uint8_t filename_size = strlen(filename);

  if (!VFwrite(&filename_size, 1, 1, file))
    return false;

  if (!VFwrite(filename, 1, filename_size, file))
    return false;

  if (!VFwrite(&itemp, sizeof(int), 2, file))
    return false;

  if (!VFwrite(&btemp, 1, 1, file))
    return false;

  if (!VFwrite(&itemp, sizeof(int), 2, file))
    return false;

  if (!VFwrite(&btemp, 1, 1, file))
    return false;
  return true;
}

//	Prepares one of the decompressors for raw reading
void CZip::PrepareDecompressor(BITFILE *bfile) {
  switch (m_iCompressionType) {
  case COMPT_HUFFADAPT_0:
    ha_PrepareDecompress();
    break;
  default:
    Int3();
    break;
  };
}

//	Prepares one of the compressors for raw reading
void CZip::PrepareCompressor(BITFILE *bfile) {
  switch (m_iCompressionType) {
  case COMPT_HUFFADAPT_0:
    ha_PrepareCompress();
    break;
  default:
    Int3();
    break;
  };
}

// Closes an archive that was opened for input
void CZip::CloseInputArchive(void) {
  if (m_bRawType) {
    switch (m_iCompressionType) {
    case COMPT_HUFFADAPT_0:
      ha_CloseRawDecompress();
      break;
    default:
      Int3();
      break;
    };
  }

  // any more work to do?
  if (bfile)
    CloseInputBitFile(bfile);
  bfile = NULL;
}

// Closes an archive that was opened for output
void CZip::CloseOutputArchive(void) {
  // if we have an OCF file, write the real header out
  if (!m_bRawType) {
    // write out an int of 0 (signifing EOF)
    int fake_magic = 0;
    VFseek(bfile->file, 0, SEEK_END);
    VFwrite(&fake_magic, sizeof(int), 1, bfile->file);
  } else {
    // since we are writing a raw, we need to finish it up
    switch (m_iCompressionType) {
    case COMPT_HUFFADAPT_0:
      ha_CloseRawCompress(bfile);
      break;
    default:
      Int3();
      break;
    };
  }

  if (bfile)
    CloseOutputBitFile(bfile);
  bfile = NULL;
}

//	Adds a given file to the archive
//	You may only add files to OCF files (you passed false for open_raw when you opened)
//	compression_type = what type of compression you want to use
bool CZip::AddFileToArchive(char *filename, int compression_type) {
  if (!bfile)
    return false;
  if (m_bRawType)
    return false;

  file = VFopen(filename, "rb");
  if (!file)
    return false;

  // Add to the end of the file, so we need to move to the end, back up sizeof(int) to remove
  // header
  VFseek(bfile->file, int(0 - sizeof(int)), SEEK_END);

  int compressed_size = -1;
  int header_start = VFtell(bfile->file);

  switch (compression_type) {
  case COMPT_NONE:
  case COMPT_SHANFANO:
    VFclose(file);
    return false;
    break;
  case COMPT_HUFFBAS:
    WriteDummyOCFHeader(bfile->file, filename);
    compressed_size = hb_CompressFile(file, bfile);
    break;
  case COMPT_HUFFADAPT_0:
    WriteDummyOCFHeader(bfile->file, filename);
    compressed_size = ha_CompressFile(file, bfile);
    break;
  default:
    VFclose(file);
    return false;
  };

  if (compressed_size == -1) {
    VFclose(file);
    return false;
  }

  // fill in the info
  struct _stat st;

  strcpy(current_file.filename, filename);
  _stat(filename, &st);
  current_file.expanded_size = st.st_size;
  VFclose(file);

  current_file.compressed_size = compressed_size;
  // TODO: Get FileTimes
  current_file.lo_time = current_file.hi_time = 0;

  m_iCompressionType = compression_type;

  WriteOCFHeader(bfile->file, &current_file, m_iCompressionType, header_start);

  return true;
}

//	Extracts a file from an OCF archive
//	filename = The filename specified within the archive
//	destfilename = The output filename (what it should get extracted to) pass NULL if it
//				is the same as the original filename
bool CZip::ExtractFileFromArchive(char *filename, char *destfilename) {
  if (!bfile)
    return false;
  if (m_bRawType)
    return false;

  file = VFopen((destfilename) ? destfilename : filename, "wb");
  if (!file)
    return false;

  int pos = FindFileInOCF(bfile->file, filename);
  if (pos == -1)
    return false;
  VFseek(bfile->file, pos, SEEK_SET);

  // read in header
  uint8_t compr_type;
  if (!ReadOCFHeader(bfile->file, &current_file, &compr_type))
    return false;

  m_iCompressionType = compr_type;

  switch (m_iCompressionType) {
  case COMPT_NONE:
  case COMPT_SHANFANO:
    VFclose(file);
    return false;
    break;
  case COMPT_HUFFBAS:
    hb_ExpandFile(bfile, file);
    break;
  case COMPT_HUFFADAPT_0:
    ha_ExpandFile(bfile, file);
    break;
  default:
    VFclose(file);
    return false;
  };

  VFclose(file);
  return true;
}

//	Searches through the opened OCF looking for filename, returns the file position
//	of the file if found, or -1 if not.
int CZip::FindFileInOCF(tVirtualFile *file, char *filename) {
  int old_pos = VFtell(file);
  VFseek(file, 0, SEEK_SET); // go to the beginning of the file

  int magic_num, pos;
  uint8_t version, filename_size;
  uint8_t buffer[300];
  bool done = false;
  int compsize;

  while (!done) {
    // make sure we have an OCF
    pos = VFtell(file);
    VFread(&magic_num, sizeof(int), 1, file);
    if (magic_num != 0x4D495241) {
      // we don't have an OCF, or end of file
      VFseek(file, old_pos, SEEK_SET);
      return -1;
    }
    VFread(&version, 1, 1, file);
    VFread(&filename_size, 1, 1, file);
    VFread(buffer, 1, filename_size, file);
    buffer[filename_size] = '\0';
    if (!stricmp(filename, (char *)buffer)) {
      // we found it...back up a couple bytes
      VFseek(file, old_pos, SEEK_SET);
      return pos;
    }

    // no luck with this file, move to the header of the next
    VFseek(file, 9, SEEK_CUR);               // get to the compressed size
    VFread(&compsize, sizeof(int), 1, file); // we need this
    VFseek(file, 5 + compsize, SEEK_CUR);    // move 5 bytes (rest of header) + data
  }

  VFseek(file, old_pos, SEEK_SET);
  return -1; // couldn't find it
}

//	Gets a list of files in the OCF, make sure you free up the array after use
//	returns the number of files in the OCF
//	0 or -1 on error (-1 is out of memory)
int CZip::GetFileList(tFileInfo **info) {
  if (m_bRawType)
    return 0;
  if (!bfile)
    return 0;
  return GetOCFFileList(bfile, info);
}

//	Gets a list of files in the OCF, make sure you free up the array after use
//	returns the number of files in the OCF
//	0 or -1 on error (-1 is out of memory)
int CZip::GetOCFFileList(BITFILE *bfile, tFileInfo **info) {
  int count = 0;

  tVirtualFile *file = bfile->file;

  // first find out how many files there are
  int old_pos = VFtell(file);
  VFseek(file, 0, SEEK_SET); // go to the beginning of the file

  int magic_num, compsize;
  uint8_t filename_size;
  bool done = false;

  while (!done) {
    // make sure we have an OCF
    VFread(&magic_num, sizeof(int), 1, file);
    if (magic_num != 0x4D495241) {
      // we don't have an OCF, or end of file
      break;
    }
    VFseek(file, 1, SEEK_CUR);
    VFread(&filename_size, 1, 1, file);
    VFseek(file, filename_size + 9, SEEK_CUR);
    VFread(&compsize, sizeof(int), 1, file); // we need this
    VFseek(file, 5 + compsize, SEEK_CUR);    // move 5 bytes (rest of header) + data
    count++;
  }

  if (!count) {
    VFseek(file, old_pos, SEEK_SET);
    return 0;
  }
  *info = (tFileInfo *)malloc(sizeof(tFileInfo) * count);
  if (!info) {
    VFseek(file, old_pos, SEEK_SET);
    return -1;
  }

  tFileInfo *files;
  files = *info;

  // now go back through and get the files
  VFseek(file, 0, SEEK_SET);

  for (int index = 0; index < count; index++) {
    VFseek(file, 5, SEEK_CUR); // skip magic num and version
    VFread(&filename_size, 1, 1, file);
    VFread(files[index].filename, 1, filename_size, file);
    files[index].filename[filename_size] = '\0';
    VFread(&files[index].lo_time, sizeof(int), 1, file);
    VFread(&files[index].hi_time, sizeof(int), 1, file);
    VFseek(file, 1, SEEK_CUR); // skip compression type
    VFread(&files[index].compressed_size, sizeof(int), 1, file);
    VFread(&files[index].expanded_size, sizeof(int), 1, file);
    VFseek(file, files[index].compressed_size + 1, SEEK_CUR); // skip data and last ditch
  }

  VFseek(file, old_pos, SEEK_SET);
  return count;
}

int CZip::ReadBytes(char *data, int count) {
  if (!m_bRawType)
    return 0;

  int c = 0;
  while (count) {
    data[c] = ReadRawByte();
    c++;
    count--;
  }

  return 1;
}

void CZip::WriteBytes(char *data, int count) {
  if (!m_bRawType)
    return;

  int c = 0;
  while (count) {
    WriteRawByte(data[c]);
    c++;
    count--;
  }
}

uint8_t CZip::ReadRawByte(void) {
  if (!m_bRawType)
    return -1;

  uint8_t data = 0;
  switch (m_iCompressionType) {
  case COMPT_HUFFADAPT_0:
    if (!ha_ReadRawByte(&data, bfile))
      data = 0;
    break;
  }
  return data;
}
uint16_t CZip::ReadRawShort(void) {
  if (!m_bRawType)
    return -1;

  // need to read 2 bytes
  uint16_t data = 0;
  data = ReadRawByte();
  data = (data << 8) | (ReadRawByte());
  return data;
}
uint32_t CZip::ReadRawInt(void) {
  if (!m_bRawType)
    return -1;

  // need to read 4 bytes
  uint32_t data = 0;
  data = ReadRawByte();
  data = (data << 8) | (ReadRawByte());
  data = (data << 8) | (ReadRawByte());
  data = (data << 8) | (ReadRawByte());

  return data;
}
float CZip::ReadRawFloat(void) {
  if (!m_bRawType)
    return -1.0f;

  // need to read 4 bytes
  int data = 0;
  data = ReadRawByte();
  data = (data << 8) | (ReadRawByte());
  data = (data << 8) | (ReadRawByte());
  data = (data << 8) | (ReadRawByte());

  return *((float *)&data);
}
void CZip::WriteRawByte(uint8_t value) {
  switch (m_iCompressionType) {
  case COMPT_HUFFADAPT_0:
    ha_WriteRawByte(value, bfile);
    break;
  }
}

void CZip::WriteRawShort(uint16_t value) {
  if (!m_bRawType)
    return;
  // write 2 bytes
  uint8_t data;
  data = ((value & 0xFF00) >> 8);
  WriteRawByte(data);
  data = (value & 0xFF);
  WriteRawByte(data);
}
void CZip::WriteRawInt(uint32_t value) {
  if (!m_bRawType)
    return;
  // write 4 bytes
  uint8_t data;
  data = ((value & 0xFF000000) >> 24);
  WriteRawByte(data);
  data = ((value & 0xFF0000) >> 16);
  WriteRawByte(data);
  data = ((value & 0xFF00) >> 8);
  WriteRawByte(data);
  data = (value & 0xFF);
  WriteRawByte(data);
}
void CZip::WriteRawFloat(float value) {
  if (!m_bRawType)
    return;
  // write 4 bytes
  uint8_t data;
  uint32_t v = 0;
  v = *((int *)&value);

  data = ((v & 0xFF000000) >> 24);
  WriteRawByte(data);
  data = ((v & 0xFF0000) >> 16);
  WriteRawByte(data);
  data = ((v & 0xFF00) >> 8);
  WriteRawByte(data);
  data = (v & 0xFF);
  WriteRawByte(data);
}

bool CZip::RawEOF(void) {
  if (!m_bRawType)
    return true;

  return !(ok_to_raw_read);
}
