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

 * $Logfile: /DescentIII/Main/Lib/unzip.h $
 * $Revision: 3 $
 * $Date: 8/15/99 8:07p $
 * $Author: Jeff $
 *
 * Unzip class
 *
 * $Log: /DescentIII/Main/Lib/unzip.h $
 *
 * 3     8/15/99 8:07p Jeff
 * handle disk write errors when extracting
 *
 * 2     8/13/99 8:01p Jeff
 * initial creation of zip class
 *
 * $NoKeywords: $
 */

#ifndef __UNZIP_H
#define __UNZIP_H

#include <cstdint>
#include <stdio.h>
#include "pstypes.h"

struct zipentry {
  uint32_t cent_file_header_sig;
  uint8_t version_made_by;
  uint8_t host_os;
  uint8_t version_needed_to_extract;
  uint8_t os_needed_to_extract;
  uint16_t general_purpose_bit_flag;
  uint16_t compression_method;
  uint16_t last_mod_file_time;
  uint16_t last_mod_file_date;
  uint32_t crc32;
  uint32_t compressed_size;
  uint32_t uncompressed_size;
  uint16_t filename_length;
  uint16_t extra_field_length;
  uint16_t file_comment_length;
  uint16_t disk_number_start;
  uint16_t internal_file_attrib;
  uint32_t external_file_attrib;
  uint32_t offset_lcl_hdr_frm_frst_disk;
  char *name;
};

class ZIP {
public:
  // constructor/destructor
  ZIP();
  ~ZIP();

public:
  // opens a zip file for reading
  // returns true on success
  bool OpenZip(const char *path);

  // closes an open zip file
  void CloseZip(void);

  // Reads the current zip entry from the zip file (and moves
  // to the next entry).  Returns NULL if there are no more entries
  zipentry *ReadNextZipEntry(void);

  // Resets a ZIP file to the first entry
  void Rewind(void);

  // Reads a file from the given zip entry into a buffer in memory
  //	-1 : no ZIP file open
  //	-2 : corrupt file
  //	-3 : Version too new
  //	-4 : OS not supported
  //	-5 : No Disk Spanning
  //	-6 : Error inflating
  //	-7 : Compression Type Not Supported
  int ReadFile(zipentry *ent, char *data);

  //	Extracts a file from the given zip entry into another file
  //	-1 : no ZIP file open
  //	-2 : corrupt file
  //	-3 : Version too new
  //	-4 : OS not supported
  //	-5 : No Disk Spanning
  //	-6 : Error inflating
  //	-7 : Compression Type Not Supported
  //	-8 : Unable to open output
  //	-9 : Error writing to file
  int ExtractFile(zipentry *ent, const char *filename);

private:
  bool FindECDSignature(char *buffer, int buflen, int *offset);
  int ReadECD(void);
  int ReadZipData(zipentry *ent, char *data);
  int ReadZipDataToFile(zipentry *ent, FILE *file);
  int SeekToCompressedData(zipentry *ent);
  int InflateFile(FILE *in_file, unsigned in_size, uint8_t *out_data, unsigned out_size);
  int InflateFileToFile(FILE *in_file, unsigned in_size, FILE *file, unsigned out_size);

private:
  bool m_open;
  char *m_zip;   // zip name
  FILE *m_fp;    // zip handler
  int32_t m_length; // length of zip file

  char *m_ecd;           // end_of_cent_dir data
  unsigned m_ecd_length; // end_of_cent_dir length

  char *m_cd; // cent_dir data

  unsigned m_cd_pos; // position in cent_dir

  zipentry m_ent; // buffer for readzip

  // end_of_cent_dir
  uint32_t m_end_of_cent_dir_sig;
  uint16_t m_number_of_this_disk;
  uint16_t m_number_of_disk_start_cent_dir;
  uint16_t m_total_entries_cent_dir_this_disk;
  uint16_t m_total_entries_cent_dir;
  uint32_t m_size_of_cent_dir;
  uint32_t m_offset_to_start_of_cent_dir;
  uint16_t m_zipfile_comment_length;
  char *m_zipfile_comment; // pointer in ecd
};

// Compare two filename without using directory
int CompareZipFileName(const char *zipfile, const char *file);

#endif
