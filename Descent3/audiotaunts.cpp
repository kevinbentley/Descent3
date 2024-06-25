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

#include <string.h>
#include <stdlib.h>

#include "mono.h"
#include "debug.h"
#include "pserror.h"
#include "pstypes.h"
#include "audiotaunts.h"
#include "cfile.h"
#include "audio_encode.h"
#include "byteswap.h"
#include "mem.h"
#include "ddio.h"
#include "manage.h"
#include "streamaudio.h"
#include "multi.h"
#include "game.h"
#include "stringtable.h"
#include "game2dll.h"
#include "player.h"

struct tWaveFile {
  int sample_length;
  int np_sample_length;
  int samples_per_second;
  int16_t bits_per_sample;
  int16_t number_channels;
  uint8_t *sample_8bit;
  int16_t *sample_16bit;
};

// returns:
//	0: no error
//	1: file not found
//	2: not RIFF format
//	3: not WAVE file
//	4: invalid block length
//	5: invalid file/unknown
//	6: format not supported
//	7: invalid num of channels
//	8: invalid samples
//	9: invalid bit (8 or 16)
//	10: no data
static char taunt_LoadWaveFile(char *filename, tWaveFile *wave);

static int TauntLastError = TAUNTIMPERR_NOERROR;
static bool Audio_taunts_enabled = true;
static float Audio_taunt_delay_time = 5.0f;

// taunt_Enable
//
//	Enables/Disables audio_taunts for the player
void taunt_Enable(bool enable) { Audio_taunts_enabled = enable; }

// taunt_AreEnabled
//
//	Returns true if taunts are enabled
bool taunt_AreEnabled(void) { return Audio_taunts_enabled; }

// taunt_DelayTime()
//
//	Returns the delay time between taunts
float taunt_DelayTime(void) {
  if (Audio_taunt_delay_time < 0)
    Audio_taunt_delay_time = 5.0f;

  return Audio_taunt_delay_time;
}

// taunt_SetDelayTime()
//
//	Sets the taunt delay time
void taunt_SetDelayTime(float t) { Audio_taunt_delay_time = t; }

//	taunt_PlayTauntFile
//
//	Given a path to an .osf file, it will play it
bool taunt_PlayTauntFile(const char *filename) {
  if (!Audio_taunts_enabled)
    return false;

  int ret = StreamPlay(filename, (MAX_GAME_VOLUME / 2.0f), 0);
  return true;
}

//	taunt_PlayPlayerTaunt
//
//	Given a playernum, and which taunt (0 or 1) it will play that taunt
bool taunt_PlayPlayerTaunt(int pnum, int index) {
  if (!(Game_mode & GM_MULTI))
    return false;

  if (index < 0 || index > 3) {
    mprintf(0, "TAUNT: invalid index %d\n", index);
    return false;
  }

  if ((NetPlayers[pnum].flags & NPF_CONNECTED) && (NetPlayers[pnum].sequence == NETSEQ_PLAYING)) {
    char fullpath[_MAX_PATH];
    char *file;
    switch (index) {
    case 0:
      file = NetPlayers[pnum].voice_taunt1;
      break;
    case 1:
      file = NetPlayers[pnum].voice_taunt2;
      break;
    case 2:
      file = NetPlayers[pnum].voice_taunt3;
      break;
    case 3:
      file = NetPlayers[pnum].voice_taunt4;
      break;
    }

    ddio_MakePath(fullpath, LocalCustomSoundsDir, file, NULL);

    if (!cfexist(fullpath)) {
      mprintf(0, "TAUNT: file %s doesn't exist (pnum=%d)\n", fullpath, pnum);
      return false;
    }

    DLLInfo.me_handle = Objects[Players[pnum].objnum].handle;
    DLLInfo.it_handle = OBJECT_HANDLE_NONE;
    CallGameDLL(EVT_CLIENT_PLAYERPLAYSAUDIOTAUNT, &DLLInfo);

    return taunt_PlayTauntFile(fullpath);
  }

  return false;
}

//	taunt_GetError
//
//	Returns more information about a failed import
int taunt_GetError(void) { return TauntLastError; }

//	taunt_GetErrorString
//	Returns a string describing an error code
// !!! FIXME: This could just return a string literal and not strcpy it.
const char *taunt_GetErrorString(int error) {
  static char str[256];

  switch (error) {
  case TAUNTIMPERR_NOTFOUND:
    strcpy(str, TXT_FILENOTFOUND);
    break;
  case TAUNTIMPERR_NOTRIFF:
    strcpy(str, TXT_NOTRIFF);
    break;
  case TAUNTIMPERR_NOTWAVE:
    strcpy(str, TXT_NOTWAVE);
    break;
  case TAUNTIMPERR_INVALIDFILE:
    strcpy(str, TXT_INVALIDFILE);
    break;
  case TAUNTIMPERR_NOTSUPPORTED:
    strcpy(str, TXT_FORMATNOTSUPPORTED);
    break;
  case TAUNTIMPERR_INVALIDCHANNELS:
    strcpy(str, TXT_MUSTBEMONO);
    break;
  case TAUNTIMPERR_INVALIDSAMPLES:
    strcpy(str, TXT_BADSAMPLERATE);
    break;
  case TAUNTIMPERR_INVALIDBITDEPTH:
    strcpy(str, TXT_BADBITDEPTH);
    break;
  case TAUNTIMPERR_NODATA:
    strcpy(str, TXT_NODATAINWAVE);
    break;
  case TAUNTIMPERR_OSFEXISTS:
    strcpy(str, TXT_OSFALREADYEXISTS);
    break;
  case TAUNTIMPERR_INTERNALERR:
    strcpy(str, TXT_INTERNALERROR);
    break;
  case TAUNTIMPERR_COMPRESSIONFAILURE:
    strcpy(str, TXT_COMPRESSFAIL);
    break;
  case TAUNTIMPERR_OUTOFMEM:
    strcpy(str, TXT_OUTOFMEMORY);
    break;
  case TAUNTIMPERR_NOOPENOSF:
    strcpy(str, TXT_CANTOPENOSF);
    break;
  default:
    strcpy(str, TXT_NOERROR);
    break;
  }
  return str;
}

//	taunt_ImportWave
//	Given a fully qualified wave_filename (location of a .wav) and a fully
//	qualified outputfilename (where the .osf is to go), it will convert and
//	compress the wav file.
#define FILEBUFFER_LENGTH (4 * 1024)
bool taunt_ImportWave(char *wave_filename, char *outputfilename) {
  ASSERT(wave_filename);
  ASSERT(outputfilename);
  bool ret = true;
  CFILE *file = NULL;
  int amount_to_flush;
  tWaveFile wavdata;
  int samples, rate, chan;
  char temp_filename[_MAX_PATH];
  char osftemp_filename[_MAX_PATH];
  uint8_t *StaticFileBuffer = NULL;
  *temp_filename = *osftemp_filename = '\0';
  OSFArchive osf;
  CFILE *fpin = NULL;
  bool osfopened;
  osfopened = false;

  if (!wave_filename || !outputfilename) {
    TauntLastError = TAUNTIMPERR_NOTFOUND;
    return false;
  }

  // first make sure the wave file exists
  if (!cfexist(wave_filename)) {
    mprintf(0, "AudioTaunt: Can't Import wav, missing %s\n", wave_filename);
    TauntLastError = TAUNTIMPERR_NOTFOUND;
    return false;
  }

  // make sure the output file doesn't exist so we don't overwrite
  if (cfexist(outputfilename)) {
    mprintf(0, "AudioTaunt: Can't Import wav, %s already exists\n", outputfilename);
    TauntLastError = TAUNTIMPERR_OSFEXISTS;
    return false;
  }

  // Open the file and import
  char wave_ret = taunt_LoadWaveFile(wave_filename, &wavdata);
  if (wave_ret != 0) {
    mprintf(0, "TAUNT: Unable to load wave\n");
    switch (wave_ret) {
    case 1:
      TauntLastError = TAUNTIMPERR_NOTFOUND;
      break;
    case 2:
      TauntLastError = TAUNTIMPERR_NOTRIFF;
      break;
    case 3:
      TauntLastError = TAUNTIMPERR_NOTWAVE;
      break;
    case 4:
    case 5:
      TauntLastError = TAUNTIMPERR_INVALIDFILE;
      break;
    case 6:
      TauntLastError = TAUNTIMPERR_NOTSUPPORTED;
      break;
    case 7:
      TauntLastError = TAUNTIMPERR_INVALIDCHANNELS;
      break;
    case 8:
      TauntLastError = TAUNTIMPERR_INVALIDSAMPLES;
      break;
    case 9:
      TauntLastError = TAUNTIMPERR_INVALIDBITDEPTH;
      break;
    case 10:
      TauntLastError = TAUNTIMPERR_NODATA;
      break;
    }
    ret = false;
    goto error;
  }

  // at this point we have a loaded wave file in memory and information about it
  // now we need to compress it, first it must be written as raw data to a temp
  // file.

  if (!ddio_GetTempFileName(Descent3_temp_directory, "d3o", temp_filename)) {
    mprintf(0, "TAUNT: Unable to create temp filename\n");
    ret = false;
    TauntLastError = TAUNTIMPERR_INTERNALERR;
    goto error;
  }

  file = cfopen(temp_filename, "wb");
  if (!file) {
    mprintf(0, "TAUNT: Unable to open temp filename\n");
    ret = false;
    TauntLastError = TAUNTIMPERR_INTERNALERR;
    goto error;
  }

  /*
  amount_to_flush = (wavdata.bits_per_sample==8)?wavdata.sample_length:wavdata.sample_length*2;

  if(wavdata.bits_per_sample==8 && wavdata.sample_8bit ){
          cf_WriteBytes(wavdata.sample_8bit,amount_to_flush,file);
  }else if(wavdata.bits_per_sample==16 && wavdata.sample_16bit ){
          //flip bytes(?)..NOTE SPEEDUP WARNING..THIS IS DONE IN WAVE LOAD..REMOVE IT?
          for(int count = 0; count < (int)wavdata.sample_length; count++)
          {
                  wavdata.sample_16bit[count] = INTEL_SHORT(wavdata.sample_16bit[count]);
          }

          cf_WriteBytes((uint8_t *)wavdata.sample_16bit,amount_to_flush,file);
  }else{
          mprintf(0,"TAUNT: Confusion to bits per sample (%d)\n",wavdata.bits_per_sample);
          ret = false;
          goto error;
  }
  mprintf(0,"TAUNT: Wrote to temp file %s\n",temp_filename);
  cfclose(file); file = NULL;
  */

  amount_to_flush = (wavdata.sample_8bit) ? wavdata.sample_length : wavdata.sample_length * 2;

  ASSERT(wavdata.sample_16bit != NULL); // only 16 bit should be coming out

  // flip bytes(?)..NOTE SPEEDUP WARNING..THIS IS DONE IN WAVE LOAD..REMOVE IT?
  int count;
  for (count = 0; count < (int)wavdata.sample_length; count++) {
    wavdata.sample_16bit[count] = INTEL_SHORT(wavdata.sample_16bit[count]);
  }

  cf_WriteBytes((uint8_t *)wavdata.sample_16bit, amount_to_flush, file);
  cfclose(file);
  file = NULL;

  samples = wavdata.bits_per_sample;
  rate = wavdata.samples_per_second;
  chan = wavdata.number_channels;

  if (!ddio_GetTempFileName(Descent3_temp_directory, "d3o", osftemp_filename)) {
    mprintf(0, "TAUNT: Unable to create osftemp filename\n");
    TauntLastError = TAUNTIMPERR_INTERNALERR;
    ret = false;
    goto error;
  }

  if (!aenc_Compress(temp_filename, osftemp_filename, NULL, &samples, &rate, &chan, NULL, NULL)) {
    // unable to compress
    mprintf(0, "Unable to compress\n");
    ret = false;
    TauntLastError = TAUNTIMPERR_COMPRESSIONFAILURE;
    goto error;
  }

  // at this point osftemp_filename is a compressed file, now to convert it
  // to osf format
  //	start writing out data.
  tOSFDigiHdr digihdr;
  uint32_t filelen, nblocks, i;
  int format;

  StaticFileBuffer = (uint8_t *)mem_malloc(FILEBUFFER_LENGTH);
  if (!StaticFileBuffer) {
    ret = false;
    mprintf(0, "Out of memory\n");
    TauntLastError = TAUNTIMPERR_OUTOFMEM;
    goto error;
  }

  fpin = cfopen(osftemp_filename, "rb");
  if (!fpin) {
    mprintf(0, "Unable to open temp file to make osf\n");
    ret = false;
    TauntLastError = TAUNTIMPERR_INTERNALERR;
    goto error;
  }

  filelen = (uint32_t)cfilelength(fpin);
  nblocks = filelen / FILEBUFFER_LENGTH;

  if (!osf.Open(outputfilename, true)) {
    ret = false;
    mprintf(0, "Unable to open osf to write\n");
    TauntLastError = TAUNTIMPERR_NOOPENOSF;
    goto error;
  }
  osfopened = true;

  //	write out data.
  for (i = 0; i < nblocks; i++) {
    if (!cf_ReadBytes(StaticFileBuffer, FILEBUFFER_LENGTH, fpin)) {
      mprintf(0, "Error reading from osf temp\n");
      ret = false;
      TauntLastError = TAUNTIMPERR_INTERNALERR;
      goto error;
    }
    if (!osf.WriteBlock(StaticFileBuffer, FILEBUFFER_LENGTH)) {
      mprintf(0, "Error writing to osf\n");
      TauntLastError = TAUNTIMPERR_INTERNALERR;
      ret = false;
      goto error;
    }
  }

  if (filelen % FILEBUFFER_LENGTH) {
    if (!cf_ReadBytes(StaticFileBuffer, filelen % FILEBUFFER_LENGTH, fpin)) {
      mprintf(0, "Error reading from osf temp\n");
      TauntLastError = TAUNTIMPERR_INTERNALERR;
      ret = false;
      goto error;
    }
    if (!osf.WriteBlock(StaticFileBuffer, filelen % FILEBUFFER_LENGTH)) {
      mprintf(0, "Error writing to osf\n");
      TauntLastError = TAUNTIMPERR_INTERNALERR;
      ret = false;
      goto error;
    }
  }

  digihdr.measure = 44100;

  format = 0;
  if (wavdata.number_channels == 1) {
    format |= SAF_MONO_MASK;
  } else {
    format |= SAF_STEREO_MASK;
  }

  if (wavdata.sample_16bit) {
    format |= SAF_16BIT_MASK;
  } else {
    format |= SAF_8BIT_MASK;
  }

  //	save header info
  char osftitle[256];
  ddio_SplitPath(outputfilename, NULL, osftitle, NULL);

  if (!osf.SaveHeader(OSF_DIGITAL_STRM, OSF_DIGIACM_STRM, format, samples, filelen, &digihdr, osftitle)) {
    mprintf(0, "Failed to write out OSF header info.");
    TauntLastError = TAUNTIMPERR_INTERNALERR;
    ret = false;
    goto error;
  }

  osf.Close();

error:
  if (file) {
    cfclose(file);
  }

  if (osfopened)
    osf.Close();

  if (fpin) {
    cfclose(fpin);
  }

  if (cfexist(osftemp_filename)) {
    ddio_DeleteFile(osftemp_filename);
  }

  if (cfexist(temp_filename)) {
    ddio_DeleteFile(temp_filename);
  }

  if (StaticFileBuffer) {
    mem_free(StaticFileBuffer);
  }

  // free memory for wave file
  if (wavdata.sample_16bit)
    mem_free(wavdata.sample_16bit);
  if (wavdata.sample_8bit)
    mem_free(wavdata.sample_8bit);

  return ret;
}

#define SOUND_FILE_SAMPLE_ALIGNMENT 4
char taunt_LoadWaveFile(char *filename, tWaveFile *wave) {
  // File pointer to sound file
  CFILE *cfptr;

  wave->sample_16bit = NULL;
  wave->sample_8bit = NULL;
  wave->np_sample_length = 0;
  wave->sample_length = 0;

  cfptr = NULL;
  char format_type[80];       // ASCII name of format type
  uint16_t fmttag = 0;  // Numerical format type
  uint32_t ckid;         // Current chunk's ID
  uint32_t cksize;       // Current chunk's size in bytes
  uint32_t filesize;     // Size of the sound file
  uint32_t nextseek = 0; // Location of the next seek
  uint32_t aligned_size; // Sound files are aligned to SOUND_FILE_SAMPLE_ALIGNMENT samples

  // Sound format information
  int samples_per_second;
  int16_t bits_per_sample;
  int16_t number_channels;
  char error_code = 0;

  // Used to read temporary long values
  uint32_t temp_long;

  // Flags for if we previously read data or a format
  char f_data, f_fmt = 0;

  // Loop counter
  int count;

  // Open the wave file
  if ((cfptr = cfopen(filename, "rb")) == NULL) {
    error_code = 1;
    mprintf(0, "TAUNT: Wav %s not found\n", filename);
    goto error_state;
  }

  // Make sure that it is a RIFF format
  temp_long = (uint32_t)cf_ReadInt(cfptr);
  if (temp_long != 0x46464952) {
    error_code = 2;
    mprintf(0, "TAUNT: Wav Load: %s is not a RIFF format file\n", filename);
    goto error_state;
  }

  // The first item is the filesize minus the RIFF type specifier and filesize (add current location for total filesize)
  filesize = cf_ReadInt(cfptr);
  filesize += cftell(cfptr);

  // Make sure it is a wave file
  temp_long = (uint32_t)cf_ReadInt(cfptr);
  if (temp_long != 0x45564157) {
    error_code = 3;
    mprintf(0, "TAUNT: Wav Load:  %s is not a WAVE file\n", filename);
    goto error_state;
  }
  nextseek = cftell(cfptr);

  // Read in the chunks
  while (nextseek < filesize - 9) // Need room for chunk and its header
  {
    // Move the the beginning of the next chunck
    cfseek(cfptr, nextseek, SEEK_SET);

    // Read in the chunk size and type
    ckid = cf_ReadInt(cfptr);
    cksize = cf_ReadInt(cfptr);
    if (cksize <= 0) {
      error_code = 4;
      mprintf(0, "TAUNT: Wav Load: %s has an invalid block length\n", filename);
      goto error_state;
    }

    // Determine where the next chunk begins
    nextseek = cksize + cftell(cfptr);

    // Determine what to do with the chunk
    switch (ckid) {
    case 0x20746D66: // Format Chunk
      // Make sure that this format was not preceeded by another format without data inbetween them.
      if (f_fmt) {
        error_code = 5;
        mprintf(0, "TAUNT: Wav Load: Found 2 formats in a row in file %s\n", filename);
        goto error_state;
      }

      // Read in the format type
      fmttag = (uint16_t)cf_ReadShort(cfptr);

      switch (fmttag) {
      // We only support WAVE_FORMAT_PCM currently
      default:
      case 0x0000:
        strcpy(format_type, "WAVE_FORMAT_UNKNOWN");
        break;
      case 0x0001:
        strcpy(format_type, "WAVE_FORMAT_PCM");
        break;
      case 0x0002:
        strcpy(format_type, "WAVE_FORMAT_ADPCM");
        break;
      case 0x0005:
        strcpy(format_type, "WAVE_FORMAT_IBM_CVSD");
        break;
      case 0x0006:
        strcpy(format_type, "WAVE_FORMAT_ALAW");
        break;
      case 0x0007:
        strcpy(format_type, "WAVE_FORMAT_MULAW");
        break;
      case 0x0010:
        strcpy(format_type, "WAVE_FORMAT_OKI_ADPCM");
        break;
      case 0x0011:
        strcpy(format_type, "WAVE_FORMAT_DVI_ADPCM");
        break;
      case 0x0015:
        strcpy(format_type, "WAVE_FORMAT_DIGISTD");
        break;
      case 0x0016:
        strcpy(format_type, "WAVE_FORMAT_DIGIFIX");
        break;
      case 0x0020:
        strcpy(format_type, "WAVE_FORMAT_YAMAHA_ADPCM");
        break;
      case 0x0021:
        strcpy(format_type, "WAVE_FORMAT_SONARC");
        break;
      case 0x0022:
        strcpy(format_type, "WAVE_FORMAT_DSPGROUP_TRUESPEECH");
        break;
      case 0x0023:
        strcpy(format_type, "WAVE_FORMAT_ECHOSC1");
        break;
      case 0x0024:
        strcpy(format_type, "WAVE_FORMAT_AUDIOFILE_AF18");
        break;
      case 0x0101:
        strcpy(format_type, "IBM_FORMAT_MULAW");
        break;
      case 0x0102:
        strcpy(format_type, "IBM_FORMAT_ALAW");
        break;
      case 0x0103:
        strcpy(format_type, "IBM_FORMAT_ADPCM");
        break;
      case 0x0200:
        strcpy(format_type, "WAVE_FORMAT_CREATIVE_ADPCM");
        break;
      }

      // Currently, we only support PCM wave files
      if (fmttag != 0x0001) {
        error_code = 6;
        mprintf(0, "TAUNT Wav Load: %s is a type %s wavefile, we only support WAVE_FORMAT_PCM waves.\n",
                filename,format_type);
        goto error_state;
      }

      // Get the number of channels
      number_channels = cf_ReadShort(cfptr);
      if (number_channels != 1) {
        error_code = 7;
        mprintf(0, "TAUNT Wav Load: Invalid number of channels(%d)in %s, we want mono samples only.\n",
                number_channels, filename);
        goto error_state;
      }

      // Get the number of samples per second
      samples_per_second = cf_ReadInt(cfptr);
      if (samples_per_second != 22050) {
        error_code = 8;
        mprintf(0, "TAUNT Wav Load: Invalid sample per second(%d)in %s, we want 22k samples only.\n",
                samples_per_second, filename);
        goto error_state;
      }

      // get the Average bytes per second (ignore it)
      cf_ReadInt(cfptr);

      // Get the Block Alignment (ignore it)
      cf_ReadShort(cfptr);

      // Get the Bits per sample
      bits_per_sample = cf_ReadShort(cfptr);
      if (bits_per_sample != 8 && bits_per_sample != 16) {
        error_code = 9;
        mprintf(0, "TAUNT Wav Load: Invalid bits per sample(%d)in %s, we want 8 or 16 bit samples only.\n",
                bits_per_sample, filename);
        goto error_state;
      }

      // We did find a new format type
      f_fmt = 1;
      f_data = 0;
      break;

    // Data Chunk
    case 0x61746164:
      if (!f_fmt) {
        error_code = 5;
        mprintf(0, "TAUNT Wav Load: Format Chunk not defined before Data Chunk\n");
        goto error_state;
      }

      // It is either 8 or 16 bit as validated from above
      if (bits_per_sample == 8) {
        int num_needed = 0;

        // Force sample alignment
        if ((cksize - 1) % SOUND_FILE_SAMPLE_ALIGNMENT) {
          num_needed = SOUND_FILE_SAMPLE_ALIGNMENT - ((cksize - 1) % SOUND_FILE_SAMPLE_ALIGNMENT);
          aligned_size = cksize + num_needed;
        } else {
          aligned_size = cksize;
        }

        wave->sample_length = aligned_size;
        wave->np_sample_length = cksize;
        wave->sample_8bit = (uint8_t *)mem_malloc(aligned_size);

        cf_ReadBytes((uint8_t *)wave->sample_8bit, cksize, cfptr);

        if (aligned_size != cksize)
          memset(wave->sample_8bit + cksize, 128, num_needed);
      } else {
        int num_needed = 0;

        wave->sample_length = cksize / 2;
        wave->np_sample_length = cksize / 2;

        if ((wave->sample_length - 1) % SOUND_FILE_SAMPLE_ALIGNMENT) {
          num_needed = (SOUND_FILE_SAMPLE_ALIGNMENT - ((wave->sample_length - 1) % SOUND_FILE_SAMPLE_ALIGNMENT)) * 2;
          wave->sample_length = cksize / 2 + num_needed / 2;
        }

        wave->sample_16bit = (int16_t *)mem_malloc(cksize + num_needed);

        cf_ReadBytes((uint8_t *)wave->sample_16bit, cksize, cfptr);
        for (count = 0; count < (int)cksize / 2; count++) {
          wave->sample_16bit[count] = INTEL_SHORT(wave->sample_16bit[count]);
        }

        if (num_needed)
          memset(wave->sample_16bit + (cksize / 2), 0, num_needed);
      }

      // We found data, clear format flag
      f_data = 1;
      f_fmt = 0; // Multiple waveforms, per file, are allowed
      break;

    // Undefined chunk
    default:
      break;
    }
  }

  // Close the file
  cfclose(cfptr);
  cfptr = NULL;

  if (wave->sample_16bit == NULL) {
    ASSERT(wave->sample_8bit);

    wave->sample_16bit = (int16_t *)mem_malloc(wave->sample_length * sizeof(int16_t));

    // NOTE:  Interesting note on sound conversion:  16 bit sounds are signed (0 biase).  8 bit sounds are unsigned
    // (+128 biase).
    for (count = 0; count < (int)wave->sample_length; count++) {
      wave->sample_16bit[count] = (((int16_t)wave->sample_8bit[count]) - 128) * 256;
    }

    mem_free(wave->sample_8bit);
    wave->sample_8bit = NULL;
  }

error_state:

  if (error_code != 0) {
    // free memory and set to NULL
    if (wave->sample_16bit)
      mem_free(wave->sample_16bit);
    if (wave->sample_8bit)
      mem_free(wave->sample_8bit);
    wave->sample_16bit = NULL;
    wave->sample_8bit = NULL;
  } else {
    wave->samples_per_second = samples_per_second;
    wave->bits_per_sample = bits_per_sample;
    wave->number_channels = number_channels;
  }

  if (cfptr)
    cfclose(cfptr);

  return error_code;
}
