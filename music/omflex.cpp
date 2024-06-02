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

 * $Logfile: /DescentIII/Main/music/omflex.cpp $
 * $Revision: 14 $
 * $Date: 4/01/99 4:50p $
 * $Author: Matt $
 *
 * Read OMF file lexical analyzer.
 *
 * $Log: /DescentIII/Main/music/omflex.cpp $
 *
 * 14    4/01/99 4:50p Matt
 * Took out Warning() function, chaning those calls to mprintf()
 *
 * 13    2/27/99 6:52p Samir
 * fixed label-region scope problem.
 *
 * 12    1/28/99 2:22p Samir
 * simplified music system for D3.
 *
 * 11    12/15/98 10:22a Samir
 * upped max labels.
 *
 * 10    12/11/98 3:28p Samir
 * added start of regions
 *
 * 9     12/08/98 11:41a Samir
 * added new region commands.
 *
 * 8     12/07/98 2:57p Samir
 * added transitions for combat.
 *
 * 7     12/03/98 12:48p Samir
 * speed up sequencer so that gap between samples isn't too big.
 *
 * 6     11/20/98 5:20p Samir
 * added a bunch of high level scripting commands.
 *
 * 5     11/16/98 4:15p Samir
 * added death.
 *
 * 4     11/13/98 2:27p Samir
 * new music system.
 *
 * 3     8/10/98 5:56p Samir
 * new command for end of combat music added.
 *
 * 2     7/28/98 5:43p Samir
 * reorg of music system.
 *
 * 1     7/28/98 11:48a Samir
 * moved from sequencer.cpp
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <cstdlib>

#include "music.h"
#include "musiclib.h"
#include "inffile.h"
#include "mem.h"
#include "mono.h"
#include "pserror.h"


//	OMF INF FILE READ
#define OMFFILEERR_ADDSECTION INFFILE_CUSTOM        // error adding section to list.
#define OMFFILEERR_INSOVERFLOW (INFFILE_CUSTOM + 1) // too many instructions!
#define OMFFILEERR_LBLOVERFLOW (INFFILE_CUSTOM + 2) // too many labels!
#define OMFFILEERR_GOTO (INFFILE_CUSTOM + 3)        // no goto label exists
#define OMFFILEERR_SYNTAX (INFFILE_CUSTOM + 4)      // syntax error.

static const char *OMFCommands[OMFCMD_NUM] = {
    "stream", "section", "play",      "endsection", "label", "compare", "lcmp", "llpt", "lplc", "inci", "seti",
    "ifi",    "region",  "endregion", "q2",         "blt",   "bgt",     "beq",  "bnif", "goto", "wait"};
static int OMFLex(const char *command);

int OMFLex(const char *command) {
  for (int i = 0; i < OMFCMD_NUM; i++) {
    if (strcmp(OMFCommands[i], command) == 0)
      return i;
  }

  return INFFILE_ERROR;
}

#define ADD_NEW_INS_NUM(_cmd, _num)                                                                                    \
  do {                                                                                                                 \
    if (temp_ins_idx == MAX_MUSIC_INSTRUCTIONS) {                                                                      \
      cmd = OMFFILEERR_INSOVERFLOW;                                                                                    \
      goto force_error;                                                                                                \
    }                                                                                                                  \
    temp_ins_buf[temp_ins_idx].cmd = (_cmd);                                                                           \
    temp_ins_buf[temp_ins_idx++].opr.num = (_num);                                                                     \
  } while (0)

#define ADD_NEW_INS_STR(_cmd, _str)                                                                                    \
  do {                                                                                                                 \
    if (temp_ins_idx == MAX_MUSIC_INSTRUCTIONS) {                                                                      \
      cmd = OMFFILEERR_INSOVERFLOW;                                                                                    \
      goto force_error;                                                                                                \
    }                                                                                                                  \
    temp_ins_buf[temp_ins_idx].cmd = (_cmd);                                                                           \
    temp_ins_buf[temp_ins_idx++].opr.str = alloc_and_copy_str((_str));                                                 \
  } while (0)

// takes a filename containing oms data.
bool OutrageMusicSeq::LoadTheme(const char *file) {
  const int MAX_FILE_LABELS = 256;

  InfFile inf;
  char operand[INFFILE_LINELEN]; // operand
  int theme_type;
  music_ins temp_ins_buf[MAX_MUSIC_INSTRUCTIONS];
  int temp_ins_idx = 0;
  int16_t cur_region;
  struct {
    char *name;
    int16_t index;
    int16_t region;
  } labels[MAX_FILE_LABELS];
  int n_labels = 0, n_relabels = 0;
  bool in_region = false;

  // reset list management for new theme.
  m_tracklist.reset();
  m_ins_curptr = m_ins_buffer;
  m_str_curptr = m_str_buffer;

  //	open file
  if (!file)
    return false;

  if (!inf.Open(file, "[theme file]", OMFLex)) {
    mprintf(0, "Unable to find requested theme %s or bad file.\n", file);
    return false;
  }

  cur_region = 0;

  // perform FIRST PASS for LABELS
  while (inf.ReadLine()) {
    int cmd;
    bool ifi_block;
    ifi_block = false;
    while ((cmd = inf.ParseLine(operand, INFFILE_LINELEN)) > INFFILE_ERROR) {
      switch (cmd) {
      case OMFCMD_LABEL:
        if (n_labels == MAX_FILE_LABELS) {
          cmd = OMFFILEERR_LBLOVERFLOW;
          goto force_pre_error;
        }
        labels[n_labels].index = temp_ins_idx;
        labels[n_labels].region = cur_region;
        labels[n_labels++].name = mem_strdup(operand);
        break;
      case OMFCMD_SECTION:
      case OMFCMD_REGION:
        temp_ins_idx = 0;
        break;
      case OMFCMD_ENDREGION:
        cur_region++;
        break;
      case OMFCMD_STREAM:
        break;
      case OMFCMD_BNIF:
      case OMFCMD_BLT:
      case OMFCMD_BGT:
      case OMFCMD_BEQ:
      case OMFCMD_GOTO:
      case OMFCMD_ENDSECTION:
      case OMFCMD_WAIT:
      case OMFCMD_COMPARE:
      case OMFCMD_LLPT:
      case OMFCMD_SETI:
      case OMFCMD_LCMP:
      case OMFCMD_LPLC:
      case OMFCMD_INCI:
        temp_ins_idx++;
        break;
      case OMFCMD_IFI:
        temp_ins_idx++;
        ifi_block = true;
        break;
      case OMFCMD_PLAY:
        temp_ins_idx++;
        temp_ins_idx++;
        break;
      }
    }

    if (ifi_block) {
      temp_ins_idx++;
    }
  force_pre_error:
    if (cmd == INFFILE_ERROR) {
      mprintf(0, "Error in music file %s line %d.\n", file, inf.line());
      Int3();
    } else if (cmd == OMFFILEERR_LBLOVERFLOW) {
      mprintf(0, "Error in music file %s line %d (too many labels).\n", file, inf.line());
      Int3();
    }
  }

  inf.Close();

  // reopen for SECOND PASS (actual code read)
  if (!inf.Open(file, "[theme file]", OMFLex)) {
    mprintf(0, "Unable to find requested theme %s or bad file.\n", file);
    return false;
  }

  theme_type = -1;
  cur_region = 0;

  while (inf.ReadLine()) {
    int cmd, i;
    bool ifi_block;
    ifi_block = false;

    while ((cmd = inf.ParseLine(operand, INFFILE_LINELEN)) > INFFILE_ERROR) {
      switch (cmd) {
      case OMFCMD_REGION:
        if (in_region) {
          cmd = OMFFILEERR_SYNTAX;
          goto force_error;
        }
        temp_ins_idx = 0;
        in_region = true;
        break;

      case OMFCMD_ENDREGION:
        in_region = false;
        cur_region++;
        break;

      case OMFCMD_STREAM: {
        char *sym = strchr(operand, '$'); // symbol AFTER '$'
        if (!sym) {
          cmd = INFFILE_ERROR;
          goto force_error;
        }
        sym[0] = 0;
        m_tracklist.add(operand, &sym[1]); // sym[0] was '$' now null terminator
      } break;

      case OMFCMD_LABEL:
        // already taken care of.
        ASSERT(labels[n_relabels].index == temp_ins_idx);
        n_relabels++;
        break;

      case OMFCMD_BNIF:
      case OMFCMD_BLT:
      case OMFCMD_BGT:
      case OMFCMD_BEQ:
      case OMFCMD_GOTO:
        for (i = 0; i < n_labels; i++) {
          if (labels[i].region == cur_region && strcmp(operand, labels[i].name) == 0) {
            ADD_NEW_INS_NUM(cmd, labels[i].index);
            break;
          }
        }
        if (i == n_labels) {
          cmd = OMFFILEERR_GOTO;
          goto force_error;
        }
        break;

      case OMFCMD_SECTION:
        if (!in_region) {
          cmd = OMFFILEERR_SYNTAX;
          goto force_error;
        }
        if (strcmp(operand, "intro") == 0) {
          theme_type = OMS_THEME_TYPE_INTRO;
        } else if (strcmp(operand, "idle") == 0) {
          theme_type = OMS_THEME_TYPE_IDLE;
        } else if (strcmp(operand, "combat") == 0) {
          theme_type = OMS_THEME_TYPE_COMBAT;
        } else if (strcmp(operand, "death") == 0) {
          theme_type = OMS_THEME_TYPE_DEATH;
        } else if (strcmp(operand, "idle_combat") == 0) {
          theme_type = OMS_THEME_TYPE_IDLE_TO_COMBAT;
        } else if (strcmp(operand, "combat_idle") == 0) {
          theme_type = OMS_THEME_TYPE_COMBAT_TO_IDLE;
        }

        temp_ins_idx = 0; // reset instruction buffer
        break;

      case OMFCMD_ENDSECTION:
        ADD_NEW_INS_NUM(OMFCMD_ENDSECTION, 0);
        if (!AddToList((int16_t)cur_region, (int16_t)theme_type, temp_ins_idx, temp_ins_buf)) {
          cmd = OMFFILEERR_ADDSECTION;
          goto force_error;
        }
        theme_type = -1;
        break;

      case OMFCMD_PLAY:
        ADD_NEW_INS_NUM(OMFCMD_PLAY, 0);
        ADD_NEW_INS_NUM(OMFCMD_MPLAY, 0);
        break;

      case OMFCMD_WAIT:
        ADD_NEW_INS_NUM(OMFCMD_WAIT, strcmp(operand, "finished") ? 0 : 1);
        break;

      case OMFCMD_COMPARE: {
        tMusicVal val;
        sscanf(operand, "r%hd", &val);
        ADD_NEW_INS_NUM(OMFCMD_COMPARE, val);
        break;
      }

      case OMFCMD_LLPT:
        ADD_NEW_INS_STR(OMFCMD_LLPT, operand);
        break;

      case OMFCMD_SETI:
      case OMFCMD_LCMP:
      case OMFCMD_LPLC:
        ADD_NEW_INS_NUM(cmd, (tMusicVal)atoi(operand));
        break;

      case OMFCMD_INCI:
        ADD_NEW_INS_NUM(cmd, 0);
        break;

      case OMFCMD_IFI:
        ADD_NEW_INS_NUM(cmd, (tMusicVal)atoi(operand));
        ifi_block = true;
        break;
      }
    }

    if (ifi_block) {
      ADD_NEW_INS_NUM(OMFCMD_ENDIFI, 0);
    }

  force_error:
    if (cmd == INFFILE_ERROR) {
      mprintf(0, "Error in music file %s line %d.\n", file, inf.line());
      Int3();
    } else if (cmd == OMFFILEERR_ADDSECTION) {
      mprintf(0, "Error in music file %s line %d (failed to add section).\n", file, inf.line());
      Int3();
    } else if (cmd == OMFFILEERR_INSOVERFLOW) {
      mprintf(0, "Error in music file %s line %d (too many instructions).\n", file, inf.line());
      Int3();
    }
  }

  // free any memory
  while (n_labels) {
    mem_free(labels[n_labels - 1].name);
    n_labels--;
  }

  // close file
  inf.Close();

  return true;
}
