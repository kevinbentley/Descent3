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

#ifndef __CZIPFILE_H_
#define __CZIPFILE_H_

#include <cstdio>
#include <cstdint>
#ifdef __LINUX__
#include "linux_fix.h"
#endif

#define OCF_VERSION 0x01

////////////////////////////////////////
// Compression Types
#define COMPT_NONE 255      // No compression, just stored (Not Implemented Yet)
#define COMPT_SHANFANO 0    // Shannon-Fano Compression
#define COMPT_HUFFBAS 1     // Huffman Encoding, Basic
#define COMPT_HUFFADAPT_0 2 // Huffman Encoding, Adaptive Order 0

// Virtual file (disk or memory files)
#define VFT_FILE 0
#define VFT_MEM 1

/*
 *File Formats:
 *-------------
 *		Compression Types
 *		=================
 *		0 - Shannon-Fano (Can't be used for raw files)
 *		1 - Huffman Basic (Can't be used for raw files)
 *		2 - Huffman Adaptive Order-0
 *
 *
 *	OCF File Type
 *	-------------
 *		4	-	Magic Number		(0x4D495241)
 *		1	-	Version				(Current 0x01)
 *		1	-	Filename length
 *		x	-	Original Filename
 *		8	-	Original Filetime
 *		1	-	Compression Type (see above)
 *		4	-	Compressed Filesize
 *		4	-	Expanded Filesize
 *		1	-	0x01
 *		x	-	Compressed Data
 *		-------> Repeat for multiple files
 *
 *
 *	raw compressed files	(any file extension, for use with readbyte, writebyte, etc)
 *	--------------------
 *		4	-	Magic Number		(0x52415743)
 *		1	-	Compression Type (see above)
 *		x	-	Compressed Data
 *
 */

#define uint8_t uint8_t
#define uint32_t uint32_t
#define uint16_t uint16_t

struct tVirtualFile {
  uint8_t type;
  int count;
  int size;      // only used for memory...size allocated for buffer
  int file_size; // max count we reached
  union {
    FILE *file;
    uint8_t *memory;
  };
};

////////////////////////////
// BitIO			//////
////////////////////////
struct BITFILE {
  tVirtualFile *file;
  uint8_t mask;
  int rack;
};

/////////////////////////////
// HuffmanBasic		///////
/////////////////////////
struct tH0Node { // tHuffman0TreeNode
  uint32_t count;
  uint32_t saved_count;
  int child0, child1;
};

struct tH0Code {
  uint32_t code;
  int code_bits;
};

///////////////////////////
// Huffman Adaptive	//////
/////////////////////////
#define SYMBOL_COUNT 258
#define NODE_TABLE_COUNT ((SYMBOL_COUNT * 2) - 1)
struct tHANode {
  uint32_t weight;
  int parent;
  bool child_is_leaf;
  int child;
};

struct tHATree {
  int leaf[SYMBOL_COUNT];
  int next_free_node;
  tHANode nodes[NODE_TABLE_COUNT];
};

struct tFileInfo {
  char filename[_MAX_PATH]; // filename
  int lo_time, hi_time;     // filetime
  int compressed_size;      //
  int expanded_size;        //
};

////////////////////////////////////////////////
//	CZip Class Header				//////////
////////////////////////////////////////////
class CZip {
public:
  CZip();
  ~CZip();

  // Opens an archive file for reading
  //	open_raw = if this is true, then the file MUST be of the raw compressed type.  You cannot
  //			open an OCF by raw.  If a raw type archive is opened, you may only use the read
  //			byte type functions (ReadRaw*())
  //	returns true on success
  bool OpenInputArchive(char *filename, bool open_raw = false);

  // Opens an archive file for writing
  //	open_raw = if this is true, then the output archive will be of the raw compressed type.
  //			You must used the write byte type functions (WriteRaw*())
  //	compression_type = You only need to specify this if you opened raw
  //	returns true on success
  bool OpenOutputArchive(char *filename, bool open_raw = false, int compression_type = -1);

  // Closes an archive that was opened for input
  void CloseInputArchive(void);

  // Closes an archive that was opened for output
  void CloseOutputArchive(void);

  //	Adds a given file to the archive
  //	You may only add files to OCF files (you passed false for open_raw when you opened)
  //	compression_type = what type of compression you want to use
  bool AddFileToArchive(char *filename, int compression_type = COMPT_HUFFADAPT_0);

  //	Extracts a file from an OCF archive
  //	filename = The filename specified within the archive
  //	destfilename = The output filename (what it should get extracted to) pass NULL if it
  //				is the same as the original filename
  bool ExtractFileFromArchive(char *filename, char *destfilename = NULL);

  //	Gets a list of files in the OCF, make sure you free up the array after use
  //	returns the number of files in the OCF
  //	0 or -1 on error (-1 is out of memory)
  int GetFileList(tFileInfo **info);

  /////////////////////////////////////////
  //	Raw type compressed files operations only
  int ReadBytes(char *data, int count);
  void WriteBytes(char *data, int count);
  uint8_t ReadRawByte(void);
  uint16_t ReadRawShort(void);
  uint32_t ReadRawInt(void);
  float ReadRawFloat(void);
  void WriteRawByte(uint8_t value);
  void WriteRawShort(uint16_t value);
  void WriteRawInt(uint32_t value);
  void WriteRawFloat(float value);
  bool RawEOF(void);

private:
  ////////////////////////////////
  // CZip Variables
  BITFILE *bfile;
  tVirtualFile *file;
  bool m_bRawType;
  int m_iCompressionType;
  tFileInfo current_file;
  //	Reads in a Raw type file header
  //	returns true on succes, if so, compr_type contains the compression type
  bool ReadRawHeader(tVirtualFile *file, uint8_t *compr_type);
  //	Writes out a Raw type file header
  //	returns true on succes
  bool WriteRawHeader(tVirtualFile *file, uint8_t compr_type);
  //	Reads in an OCF header
  //	returns true on success, info is filled in the appropriate values,compr_type is compression type
  bool ReadOCFHeader(tVirtualFile *file, tFileInfo *info, uint8_t *compr_type);
  //	Writes out an OCF header
  //	returns true on success
  bool WriteOCFHeader(tVirtualFile *file, tFileInfo *info, uint8_t compr_type, int header_pos);
  //	Writes out a 'dummy' OCF header, just give what the final filename is
  //	you must call this before you compress data, then when done, call the read WriteOCFHeader
  bool WriteDummyOCFHeader(tVirtualFile *file, char *filename);
  //	Searches through the opened OCF looking for filename, returns the file position
  //	of the file if found, or -1 if not.
  int FindFileInOCF(tVirtualFile *file, char *filename);
  //	Gets a list of files in the OCF, make sure you free up the array after use
  //	returns the number of files in the OCF
  //	0 or -1 on error (-1 is out of memory)
  int GetOCFFileList(BITFILE *file, tFileInfo **info);
  //	Prepares one of the decompressors for raw reading
  void PrepareDecompressor(BITFILE *bfile);
  //	Prepares one of the compressors for raw reading
  void PrepareCompressor(BITFILE *bfile);

  ////////////////////////////////////////////
  // BitIO
  BITFILE *OpenInputBitFile(char *filename);
  BITFILE *OpenOutputBitFile(char *filename);
  void OutputBit(BITFILE *bfile, int bit);
  void OutputBits(BITFILE *bfile, uint32_t code, int count);
  int InputBit(BITFILE *bfile);
  uint32_t InputBits(BITFILE *bfile, int bitcount);
  void CloseInputBitFile(BITFILE *bfile);
  void CloseOutputBitFile(BITFILE *bfile);
  void FilePrintBinary(FILE *file, uint32_t code, int bits);
  tVirtualFile *VFopen(const char *filename, const char *flags, int size = 0);
  int VFclose(tVirtualFile *f);
  int VFputc(int value, tVirtualFile *file);
  int VFgetc(tVirtualFile *file);
  int VFwrite(void *buffer, int size, int count, tVirtualFile *file);
  int VFread(void *buffer, int size, int count, tVirtualFile *file);
  int VFtell(tVirtualFile *file);
  int VFseek(tVirtualFile *file, int offset, int origin);
  void FlushOutputBitFile(BITFILE *bfile);

  //////////////////////////////////////////////
  // HuffmanBase
  int hb_CompressFile(tVirtualFile *input, BITFILE *output);
  bool hb_ExpandFile(BITFILE *input, tVirtualFile *output);
  void hb_compress_data(tVirtualFile *input, BITFILE *output, tH0Code *codes);
  void hb_expand_data(BITFILE *input, tVirtualFile *output, tH0Node *nodes, int root_node);
  void hb_count_bytes(tVirtualFile *input, uint32_t *long_counts);
  void hb_scale_counts(uint32_t *long_counts, tH0Node *nodes);
  int hb_build_tree(tH0Node *nodes);
  void hb_convert_tree_to_code(tH0Node *nodes, tH0Code *codes, uint32_t code_so_far, int bits, int node);
  void hb_output_counts(BITFILE *output, tH0Node *nodes);
  void hb_input_counts(BITFILE *input, tH0Node *nodes);

  //////////////////////////////////////////////
  // Huffman Adaptive
  tHATree Tree;
  bool ok_to_raw_write, ok_to_raw_read;
  int ha_CompressFile(tVirtualFile *input, BITFILE *output);
  void ha_ExpandFile(BITFILE *input, tVirtualFile *output);
  void ha_InitializeTree(tHATree *tree);
  void ha_EncodeSymbol(tHATree *tree, uint32_t c, BITFILE *output);
  int ha_DecodeSymbol(tHATree *tree, BITFILE *input);
  void ha_UpdateModel(tHATree *tree, int c);
  void ha_RebuildTree(tHATree *tree);
  void ha_swap_nodes(tHATree *tree, int i, int j);
  void ha_add_new_node(tHATree *tree, int c);
  void ha_CloseRawDecompress(void);
  bool ha_ReadRawByte(uint8_t *data, BITFILE *input);
  void ha_PrepareDecompress(void);
  void ha_CloseRawCompress(BITFILE *output);
  void ha_WriteRawByte(uint8_t data, BITFILE *output);
  void ha_PrepareCompress(void);
};

#endif
