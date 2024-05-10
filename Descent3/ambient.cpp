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

 * $Logfile: /DescentIII/Main/ambient.cpp $
 * $Revision: 13 $
 * $Date: 8/10/99 2:10p $
 * $Author: Gwar $
 *
 * Ambient sound system
 *
 * $Log: /DescentIII/Main/ambient.cpp $
 *
 * 13    8/10/99 2:10p Gwar
 * added sound support to neweditor
 *
 * 12    5/10/99 10:00p Ardussi
 * changes to compile on Mac
 *
 * 11    4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 10    4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 9     3/24/99 7:49p Jason
 * fixed multiplayer bugs
 *
 * 8     2/10/99 4:44p Jeff
 * table file parser stuff
 *
 * 7     2/10/99 2:31p Matt
 * Deleted some unused code and fixed a slightly stupid thing.
 *
 * 6     1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 5     10/09/98 4:13p Matt
 * Don't specify explicit path for ambient sound pattern file.
 *
 * 4     10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 3     8/20/98 12:35p Matt
 * Added nice editing for ambient sound patterns
 *
 * 2     8/17/98 8:32p Craig
 * Fixed Matt's bug.
 *
 * 1     8/17/98 7:00p Matt
 * Added ambient sound system
 *
 */

#include <stdlib.h>
#include <string.h>

#include "ambient.h"

#include "hlsoundlib.h"

#include "room.h"
#include "game.h"
#include "psrand.h"

#define MAX_AMBIENT_SOUND_PATTERNS 100
asp Ambient_sound_patterns[MAX_AMBIENT_SOUND_PATTERNS];
int Num_ambient_sound_patterns = 0;

static void ProcessASP(asp *asp);
static void FreeAmbientSoundData();

// Computes a floating-point pseudo-random number.
// Returns value in the range 0..1, with the precision 1/D3_RAND_MAX
static float randf() { return ((float)ps_rand()) / ((float)D3_RAND_MAX); }

// Process an Ambient Sound Pattern
void ProcessASP(asp *asp) {
  // Check for empty ASP
  if (!asp->num_sounds)
    return;

  // Decrement delay
  asp->delay -= Frametime;

  // Time to play?
  if (asp->delay < 0.0) {

    // Figure out which sound to play
    int roll = (ps_rand() * 100) / (D3_RAND_MAX + 1); // roll = 0..99
    int s;

    for (s = 0; s < asp->num_sounds; s++)
      if ((roll -= asp->sounds[s].probability) < 0)
        break;

    ASSERT(s < asp->num_sounds);

    // Play sound i
    ase *sound = &asp->sounds[s];
    float volume = sound->min_volume + (sound->max_volume - sound->min_volume) * randf();
    Sound_system.Play2dSound(sound->handle, volume);

    // Compute delay until next sound
    asp->delay = asp->min_delay + (asp->max_delay - asp->min_delay) * randf();
  }
}

// Does the ambient sound processing for one frame, maybe playing a sound or two
void DoAmbientSounds() {
  if (OBJECT_OUTSIDE(Viewer_object))
    return;

  room *rp = &Rooms[Viewer_object->roomnum];

  if (rp->ambient_sound != -1)
    ProcessASP(&Ambient_sound_patterns[rp->ambient_sound]);
}

// Initializes the ambient sounds for the current level
void InitAmbientSounds() {
  // Loop through all ambient sound patterns
  for (int p = 0; p < Num_ambient_sound_patterns; p++) {
    asp *asp = &Ambient_sound_patterns[p];

    // Initialize delay
    asp->delay = asp->min_delay + (asp->max_delay - asp->min_delay) * randf();

    // Make sure the probabilities add up
    int prob = 0;
    for (int s = 0; s < asp->num_sounds; s++)
      prob += asp->sounds[s].probability;
    if (asp->num_sounds && prob != 100) {
      Int3();
      asp->sounds[0].probability += 100 - prob; // make it total 100
    }
  }
}

#include "ddio.h"
#include "soundload.h"
#include "descent.h"
#include "mem.h"

// Close down ambient sound system and free data
void FreeAmbientSoundData() {
  for (int p = 0; p < Num_ambient_sound_patterns; p++)
    if (Ambient_sound_patterns[p].num_sounds)
      mem_free(Ambient_sound_patterns[p].sounds);

  Num_ambient_sound_patterns = 0;
}

// Initialize the ambient sound system
void InitAmbientSoundSystem() {
  atexit(FreeAmbientSoundData);

  ReadAmbientData();

  // Get rid of deleted patterns
  for (int p = 0; p < Num_ambient_sound_patterns; p++) {

    asp *asp = &Ambient_sound_patterns[p];

    if (!asp->name[0]) {
      Ambient_sound_patterns[p] = Ambient_sound_patterns[Num_ambient_sound_patterns - 1];
      Num_ambient_sound_patterns--;
    }
  }
}

// Return the index of a named ambient sound pattern
// Returns number, or -1 if can't find
int FindAmbientSoundPattern(char *aspname) {
  if (!aspname[0])
    return -1;

  for (int i = 0; i < Num_ambient_sound_patterns; i++)
    if (stricmp(Ambient_sound_patterns[i].name, aspname) == 0)
      return i;

  return -1;
}

// Returns a pointer to the name of the specified ambient sound pattern
char *AmbientSoundPatternName(int n) { return Ambient_sound_patterns[n].name; }

#define AMBIENT_FILE_ID "ASPF"
#define AMBIENT_FILE_VERSION 0

// Reads data from the ambient sound data file
void ReadAmbientData() {
  CFILE *ifile;
  char file_id[sizeof(AMBIENT_FILE_ID)];
  int version;

  // Get rid of any old data
  FreeAmbientSoundData();

  // Build filename
  ifile = cfopen(AMBIENT_FILE_NAME, "rb");

  if (!ifile) {
    Int3();
    return;
  }

  // Read file ID
  cf_ReadBytes((uint8_t *)file_id, strlen(AMBIENT_FILE_ID), ifile);
  if (strncmp(file_id, AMBIENT_FILE_ID, strlen(AMBIENT_FILE_ID)) != 0) {
    Int3();
    cfclose(ifile);
    return;
  }

  // Read version
  version = cf_ReadInt(ifile);

  if (version > AMBIENT_FILE_VERSION) {
    Int3();
    cfclose(ifile);
    return;
  }

  // Get the number of patterns
  Num_ambient_sound_patterns = cf_ReadInt(ifile);

  // Read the patterns
  for (int p = 0; p < Num_ambient_sound_patterns; p++) {

    asp *asp = &Ambient_sound_patterns[p];

    cf_ReadString(asp->name, sizeof(asp->name), ifile);

    asp->min_delay = cf_ReadFloat(ifile);
    asp->max_delay = cf_ReadFloat(ifile);

    asp->num_sounds = cf_ReadInt(ifile);

    if (asp->num_sounds > 0)
      asp->sounds = (ase *)mem_malloc(sizeof(*asp->sounds) * asp->num_sounds);
    else
      asp->sounds = NULL;

    int prob = 0;
    for (int s = 0; s < asp->num_sounds; s++) {
      char tbuf[PAGENAME_LEN];

      cf_ReadString(tbuf, sizeof(tbuf), ifile);
      asp->sounds[s].handle = FindSoundName(IGNORE_TABLE(tbuf));

      asp->sounds[s].min_volume = cf_ReadFloat(ifile);
      asp->sounds[s].max_volume = cf_ReadFloat(ifile);
      asp->sounds[s].probability = cf_ReadInt(ifile);

      prob += asp->sounds[s].probability;
    }

    if (asp->num_sounds && (prob != 100)) {
      Int3();
      asp->sounds[0].probability += 100 - prob; // make it total 100
    }
  }

  cfclose(ifile);
}

#ifdef NEWEDITOR
extern char D3HogDir[_MAX_PATH * 2];
#endif

// Writes data from the ambient sound data file
void WriteAmbientData() {
  char filename[_MAX_PATH];
  CFILE *ofile;

#ifndef NEWEDITOR
  ddio_MakePath(filename, Base_directory, "data", "misc", AMBIENT_FILE_NAME, NULL);
#else
  ddio_MakePath(filename, D3HogDir, "data", "misc", AMBIENT_FILE_NAME, NULL);
#endif
  ofile = cfopen(filename, "wb");

  if (!ofile) {
    Int3();
    return;
  }

  // Write file ID & version
  cf_WriteBytes((uint8_t *)AMBIENT_FILE_ID, strlen(AMBIENT_FILE_ID), ofile);
  cf_WriteInt(ofile, AMBIENT_FILE_VERSION);

  // Write the number of patterns
  cf_WriteInt(ofile, Num_ambient_sound_patterns);

  // Read the patterns
  for (int p = 0; p < Num_ambient_sound_patterns; p++) {

    asp *asp = &Ambient_sound_patterns[p];

    cf_WriteString(ofile, asp->name);

    cf_WriteFloat(ofile, asp->min_delay);
    cf_WriteFloat(ofile, asp->max_delay);

    cf_WriteInt(ofile, asp->num_sounds);

    for (int s = 0; s < asp->num_sounds; s++) {
      cf_WriteString(ofile, Sounds[asp->sounds[s].handle].name);

      cf_WriteFloat(ofile, asp->sounds[s].min_volume);
      cf_WriteFloat(ofile, asp->sounds[s].max_volume);
      cf_WriteInt(ofile, asp->sounds[s].probability);
    }
  }

  cfclose(ofile);
}
