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

 * $Logfile: /DescentIII/main/pilot_class.cpp $
 * $Revision: 30 $
 * $Date: 3/20/00 12:19p $
 * $Author: Matt $
 *
 * Pilot class and access functions
 *
 * $Log: /DescentIII/main/pilot_class.cpp $
 *
 * 30    3/20/00 12:19p Matt
 * Merge of Duane's post-1.3 changes.
 * Default to full-screen mode on Mac.
 * Mouse sensitivity change (Mac only)
 *
 * 29    10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 28    8/10/99 5:12p Jeff
 * fixed compiler warnings
 *
 * 27    8/06/99 4:25p Samir
 * set key ramping speed globally when loading pilot file.
 *
 * 26    7/20/99 1:18p Samir
 * save state of rearviews between game through the pilot file.
 *
 * 25    5/21/99 10:42p Jeff
 * init pilot ship to Pyro-GL for dedicated server needs
 *
 * 24    5/09/99 1:48a Jeff
 * default rookie
 *
 * 23    5/02/99 12:56a Jeff
 * save ship permissions at highest level achieved and use that on restore
 * to a level previously played
 *
 * 22    5/01/99 1:36a Samir
 * oops forgot to update pilot version number!
 *
 * 21    4/30/99 1:29p Samir
 * added save for key ramping
 *
 * 20    4/27/99 4:18p Jeff
 * fixed crash
 *
 * 19    4/27/99 3:58p Jeff
 * added kiddie settings
 *
 * 18    4/27/99 1:56p Jeff
 * audio taunts stuff in pilot menu, added stringtables
 *
 * 17    4/25/99 2:32a Jeff
 * fixed bug trying to read pilot files that are too new
 *
 * 16    4/24/99 8:40p Samir
 * added toggle to pilot for ship sounds.
 *
 * 15    4/20/99 7:28p Jeff
 * added guidebot name
 *
 * 14    4/17/99 8:25p Samir
 * took out graphical option for inventory display.  no time.
 *
 * 13    4/15/99 2:55p Samir
 * added UI for mouselook.
 *
 * 12    4/05/99 5:13p Samir
 * added game toggles.
 *
 * 11    4/03/99 2:18a Jeff
 * added profanity filter stuff
 *
 * 10    3/22/99 6:22p Jeff
 * added 2 more audio taunts.  a mulitplayer event when someone plays an
 * audio taunt.  option to disable audio taunts.
 *
 * 9     3/15/99 9:24p Gwar
 *
 * 8     3/05/99 2:44p Samir
 * needs to be cleaned up later, but mouse and joystick sensitivities are
 * read in always, and set by the controller system.   A cancel method
 * needs to be implemented for these functions.
 *
 * 7     3/03/99 5:09p Samir
 * default to graphical hud!
 *
 * 6     2/25/99 8:55p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 5     2/24/99 12:55p Samir
 * refresh weapon select info in pilot_class when writing out pilot file.
 *
 * 4     2/18/99 5:55p Jeff
 * added weapon select data
 *
 * 3     2/16/99 12:00p Samir
 * added new video resolution swtich test.
 *
 * 2     2/15/99 7:50p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 1     2/15/99 3:18a Jeff
 * initial creation
 *
 * $NoKeywords: $
 */

#include "pilot_class.h"
#include "ddio.h"
#include "hud.h"
#include "mem.h"
#include "pserror.h"
#include "mono.h"
#include "config.h"
#include "ship.h"
#include <string.h>
#include <stdlib.h>

#include "application.h"
#include "appdatabase.h"

#include "stringtable.h"

#define __PILOT_H_ // don't want to include pilot.h right now
#include "difficulty.h"
#include "audiotaunts.h"

#include <algorithm>

extern void grtext_SetProfanityFilter(bool enabled);

extern float Key_ramp_speed;

#define PLT_FILE_VERSION 0x2B // pilot file version

// pilot file version history
#define PFV_REARVIEWINFO 0x2B    // (SAMIR) save current state of rear small view.
#define PFV_SHIPPERMISSIONS 0x2A // (JEFF) save highest level ship permission in mission data
#define PFV_KEYRAMPING 0x29      // (SAMIR) added save of keyboard ramping value.
#define PFV_AUDIOTAUNTS 0x28     // (JEFF) added audiotaunts
#define PFV_GUIDEBOTNAME 0x26    // (JEFF) added guidebot name
#define PFV_MOUSELOOK 0x25       //	(SAMIR) added mouselook option to pilot.
#define PFV_GAMETOGGLES 0x24     // (SAMIR) gameplay toggles
#define PFV_PROFANITY 0x23       // (JEFF) added profanity filter
#define PFV_AUDIOTAUNT3N4 0x22   // (JEFF) added saving of audio taunts 3 & 4 (and save/restore count for mission data)
#define PFV_WEAPONSELECT 0x21    // (JEFF) added saving weapon select

pilot::~pilot() { clean(false); }

pilot::pilot() {
  write_pending = false;
  initialize();
}

pilot::pilot(pilot *copy) {
  write_pending = true;
  initialize();
}

pilot::pilot(char *fname) {
  write_pending = true;
  initialize();
}

// initializes all the data (for constructors)
void pilot::initialize(void) {
  int i;

  filename = NULL;
  name = NULL;
  ship_model = mem_strdup("Pyro-GL");
  ship_logo = NULL;
  audio1_file = NULL;
  audio2_file = NULL;
  audio3_file = NULL;
  audio4_file = NULL;
  guidebot_name = mem_strdup("GB");
  picture_id = PPIC_INVALID_ID;
  difficulty = DIFFICULTY_ROOKIE;
  hud_mode = (uint8_t)HUD_COCKPIT;
  hud_stat = 0;
  hud_graphical_stat = STAT_STANDARD;
  game_window_w = Video_res_list[Game_video_resolution].width;
  game_window_h = Video_res_list[Game_video_resolution].height;
  num_missions_flown = 0;
  mission_data = NULL;
  mouselook_control = false;
  key_ramping = 0.35f;
  lrearview_enabled = false;
  rrearview_enabled = false;

  bool kiddie_settings = true;

  if (Database) {
    Database()->read("ProfanityPrevention", &kiddie_settings);
  }

  if (kiddie_settings) {
    profanity_filter_on = true;
    audiotaunts = false;
  } else {
    profanity_filter_on = false;
    audiotaunts = true;
  }

  gameplay_toggles.guided_mainview = false;
  gameplay_toggles.show_reticle = true;
  gameplay_toggles.ship_noises = true;

  // Copy taunts
  for (i = 0; i < MAX_PILOT_TAUNTS; i++) {
    strcpy(taunts[i], TXT(TXT_TAUNT_TEXT + i));
  }

  read_controller = READF_MOUSE + READF_JOY;

  if (Controller) {
    for (i = 0; i < NUM_CONTROLLER_FUNCTIONS; i++) {
      Controller->get_controller_function(Controller_needs[i].id, controls[i].type, &controls[i].value,
                                          controls[i].flags);
      controls[i].id = Controller_needs[i].id;
    }
  } else {
    for (i = 0; i < NUM_CONTROLLER_FUNCTIONS; i++) {
      memset(&controls[i], 0, sizeof(cntrldata));
    }
  }

  for (i = 0; i < N_MOUSE_AXIS; i++) {
    mouse_sensitivity[i] = 1.0f;
  }

  for (i = 0; i < N_JOY_AXIS; i++) {
    joy_sensitivity[i] = 1.0f;
  }

  for (i = 0; i < MAX_PRIMARY_WEAPONS; i++)
    PrimarySelectList[i] = DefaultPrimarySelectList[i];

  for (i = 0; i < MAX_SECONDARY_WEAPONS; i++)
    SecondarySelectList[i] = DefaultSecondarySelectList[i];
}

// This function guts the data so it's virgin (fresh for reading)
// frees any memory that needs to be freed, etc.
void pilot::clean(bool reset) {
  if (filename) {
    mem_free(filename);
    filename = NULL;
  }

  if (name) {
    mem_free(name);
    name = NULL;
  }

  if (ship_model) {
    mem_free(ship_model);
    ship_model = NULL;
  }

  if (ship_logo) {
    mem_free(ship_logo);
    ship_logo = NULL;
  }

  if (audio1_file) {
    mem_free(audio1_file);
    audio1_file = NULL;
  }

  if (audio2_file) {
    mem_free(audio2_file);
    audio2_file = NULL;
  }

  if (audio3_file) {
    mem_free(audio3_file);
    audio3_file = NULL;
  }

  if (audio4_file) {
    mem_free(audio4_file);
    audio4_file = NULL;
  }

  if (mission_data) {
    mem_free(mission_data);
    mission_data = NULL;
  }

  if (guidebot_name) {
    mem_free(guidebot_name);
    guidebot_name = NULL;
  }

  if (reset)
    initialize();
}

// This function verifies all the pilot data, making sure nothing is out of whack
// It will correct any messed data.
void pilot::verify(void) {
  int i;
  for (i = 0; i < MAX_PRIMARY_WEAPONS; i++) {
    PrimarySelectList[i] = GetAutoSelectPrimaryWpnIdx(i);
  }
  for (i = 0; i < MAX_SECONDARY_WEAPONS; i++) {
    SecondarySelectList[i] = GetAutoSelectSecondaryWpnIdx(i);
  }

  gameplay_toggles.guided_mainview = Game_toggles.guided_mainview;
  gameplay_toggles.show_reticle = Game_toggles.show_reticle;
  gameplay_toggles.ship_noises = Game_toggles.ship_noises;

  // kill graphical stat for inventory and reset to text version
  if (hud_graphical_stat & STAT_INVENTORY) {
    hud_graphical_stat = hud_graphical_stat & (~STAT_INVENTORY);
    hud_stat = hud_stat | STAT_INVENTORY;
  }

  key_ramping = Key_ramp_speed;

  /*
  bool had_to_change = false;

  //first check the ship mode
  bool found_model = false;
  for(int i=0;i<MAX_SHIPS;i++){
          if(Ships[i].used && !stricmp(Ships[i].name,Pilot->ship_model) ){
                  found_model = true;
                  break;
          }
  }

  if(!found_model){
          //we couldn't find the ship model
          had_to_change = true;
          strcpy(Pilot->ship_model,DEFAULT_SHIP);
  }

  //check the custom texture
  if(Pilot->ship_logo[0]!='\0'){
          if(cfexist(Pilot->ship_logo)==CF_NOT_FOUND){
                  //couldn't find the custom texture
                  Pilot->ship_logo[0] = '\0';
                  had_to_change = true;
          }
  }

  //check audio files
  if(Pilot->audio1_file[0]!='\0'){
          if(cfexist(Pilot->audio1_file)==CF_NOT_FOUND){
                  //couldn't find the custom texture
                  Pilot->audio1_file[0] = '\0';
                  had_to_change = true;
          }
  }

  if(Pilot->audio2_file[0]!='\0'){
          if(cfexist(Pilot->audio2_file)==CF_NOT_FOUND){
                  //couldn't find the custom texture
                  Pilot->audio2_file[0] = '\0';
                  had_to_change = true;
          }
  }

  char temp_buffer[PILOT_STRING_SIZE];
  if(Pilot->picture_id!=PPIC_INVALID_ID && !PPic_GetPilot(Pilot->picture_id,temp_buffer,PILOT_STRING_SIZE)){
          //the pilot picture id is invalid
          Pilot->picture_id = PPIC_INVALID_ID;
          had_to_change = true;
  }

  return had_to_change;
  */
}

// This function makes the pilot file so it's write pending, meaning that
// on the next call to flush, it will actually write out the data.  There is
// no need to constantly do file access unless it's really needed
void pilot::write(void) { write_pending = true; }

// This function makes certain that the pilot data is up to date with the
// actual pilot file, writing if needed.
int pilot::flush(bool new_file) {
  if (!write_pending)
    return PLTW_NO_ERROR; // no need to write, data hasn't changed

  if (!filename) {
    Int3();
    return PLTW_NO_FILENAME; // no filename was given
  }

  CFILE *file;
  char real_filename[_MAX_PATH];

  // open and process file
  ddio_MakePath(real_filename, Base_directory, filename, NULL);

  if (new_file && cfexist(real_filename)) {
    // the file already exists, we can't write out
    mprintf(0, "PLTW: File (%s) exists, can't create\n", real_filename);
    return PLTW_FILE_EXISTS;
  }

  try {
    verify();

    file = cfopen(real_filename, "wb");
    if (!file) {
      mprintf(0, "PLTW: File (%s) can't be opened\n", real_filename);
      return PLTW_FILE_CANTOPEN;
    }

    // Write out our fileversion
    file_version = PLT_FILE_VERSION;
    cf_WriteInt(file, file_version);

    write_name(file);
    write_ship_info(file);
    write_custom_multiplayer_data(file);
    write_difficulty(file);
    write_profanity_filter(file);
    write_audiotaunts(file);
    write_hud_data(file);
    write_mission_data(file);
    write_taunts(file);
    write_weapon_select(file);
    write_gameplay_toggles(file); // version 0x24 PFV_GAMETOGGLES
    write_guidebot_name(file);
    write_controls(file);

    cfclose(file);

  } catch (cfile_error) {
    // catch and handle CFILE errors
    mprintf(0, "PLTW: CFILE Exception writing data\n");
    Int3();
    try {
      cfclose(file);
    } catch (...) {
      mprintf(0, "PLTW: Unable to close file due to exception\n");
    }
    return PLTW_CFILE_FATAL;
  } catch (...) {
    // catch all errors
    mprintf(0, "PLTW: Unknown exception writing data\n");
    Int3();
    try {
      cfclose(file);
    } catch (...) {
      mprintf(0, "PLTW: Unable to close file due to exception\n");
    }
    return PLTW_UNKNOWN_FATAL;
  }

  write_pending = false;

  return PLTW_NO_ERROR;
}

// This function sets the filename that is associated with this pilot
void pilot::set_filename(char *fname) {
  if (filename) {
    mem_free(filename);
    filename = NULL;
  }

  filename = mem_strdup(fname);
}

void pilot::get_filename(char *fname) {
  if (filename) {
    strcpy(fname, filename);
  } else {
    *fname = '\0';
  }
}

// This function reads in the data from file (from the filename associated)
// into the pilot data.
int pilot::read(bool skip_config, bool skip_mission_data) {
  if (!filename) {
    Int3();
    return PLTR_NO_FILENAME; // no filename was given
  }

  CFILE *file;
  char real_filename[_MAX_PATH];

  // open and process file
  ddio_MakePath(real_filename, Base_directory, filename, NULL);

  if (!cfexist(real_filename)) {
    // the file already exists, we can't write out
    mprintf(0, "PLTR: File (%s) does not exist\n", real_filename);
    return PLTR_FILE_NOEXIST;
  }

  try {
    file = cfopen(real_filename, "rb");
    if (!file) {
      mprintf(0, "PLTR: File (%s) can't be opened\n", real_filename);
      return PLTR_FILE_CANTOPEN;
    }

    // Write out our fileversion
    file_version = cf_ReadInt(file);

    if (file_version > PLT_FILE_VERSION) {
      // too new!!
      cfclose(file);
      return PLTR_TOO_NEW;
    }

    //////////////////////////////////////////////
    read_name(file, false);
    read_ship_info(file, false);
    read_custom_multiplayer_data(file, false);
    read_difficulty(file, false);
    if (file_version >= PFV_PROFANITY) {
      read_profanity_filter(file, false);
    }
    if (file_version >= PFV_AUDIOTAUNTS) {
      read_audiotaunts(file, false);
    }

    read_hud_data(file, false);
    read_mission_data(file, skip_mission_data);
    read_taunts(file, false);

    if (file_version >= PFV_WEAPONSELECT) {
      read_weapon_select(file);
    }

    if (file_version >= PFV_GAMETOGGLES) {
      read_gameplay_toggles(file, false);
    }

    if (file_version >= PFV_GUIDEBOTNAME) {
      read_guidebot_name(file, false);
    }

    read_controls(file, skip_config);

    //////////////////////////////////////////////
    int wpn;
    for (wpn = 0; wpn < MAX_PRIMARY_WEAPONS; wpn++) {
      SetAutoSelectPrimaryWpnIdx(wpn, PrimarySelectList[wpn]);
    }
    for (wpn = 0; wpn < MAX_SECONDARY_WEAPONS; wpn++) {
      SetAutoSelectSecondaryWpnIdx(wpn, SecondarySelectList[wpn]);
    }

    Game_toggles.guided_mainview = gameplay_toggles.guided_mainview;
    Game_toggles.show_reticle = gameplay_toggles.show_reticle;
    Game_toggles.ship_noises = gameplay_toggles.ship_noises;

    Key_ramp_speed = key_ramping;

    cfclose(file);
  } catch (cfile_error) {
    // catch and handle CFILE errors
    mprintf(0, "PLTR: CFILE Exception reading data\n");
    Int3();
    try {
      cfclose(file);
    } catch (...) {
      mprintf(0, "PLTR: Unable to close file due to exception\n");
    }
    verify();
    return PLTR_CFILE_FATAL;
  } catch (...) {
    // catch all errors
    mprintf(0, "PLTR: Unknown exception reading data\n");
    Int3();
    try {
      cfclose(file);
    } catch (...) {
      mprintf(0, "PLTR: Unable to close file due to exception\n");
    }
    verify();
    return PLTR_UNKNOWN_FATAL;
  }

  verify();
  return PLTR_NO_ERROR;
}

void pilot::set_name(const char *n) {
  if (name) {
    mem_free(name);
    name = NULL;
  }
  if (n) {
    int length = strlen(n);
    int size = std::min(PILOT_STRING_SIZE - 1, length);
    name = (char *)mem_malloc(size + 1);
    if (name) {
      strncpy(name, n, size);
      name[size] = '\0';
    }
  }
  write_pending = true;
}
void pilot::get_name(char *n) {
  if (n) {
    if (name) {
      strcpy(n, name);
    } else {
      *n = '\0';
    }
  }
}

void pilot::set_ship(const char *ship) {
  if (ship_model) {
    mem_free(ship_model);
    ship_model = NULL;
  }
  if (ship) {
    int length = strlen(ship);
    int size = std::min(PAGENAME_LEN - 1, length);
    ship_model = (char *)mem_malloc(size + 1);
    if (ship_model) {
      strncpy(ship_model, ship, size);
      ship_model[size] = '\0';
    }
  }
  write_pending = true;
}
void pilot::get_ship(char *ship) {
  if (ship) {
    if (ship_model) {
      strcpy(ship, ship_model);
    } else {
      *ship = '\0';
    }
  }
}

void pilot::set_multiplayer_data(const char *logo, const char *audio1, const char *audio2, const uint16_t *ppic, const char *audio3, const char *audio4) {
  if (logo) {
    if (ship_logo) {
      mem_free(ship_logo);
      ship_logo = NULL;
    }
    ship_logo = mem_strdup(logo);
    if (ship_logo) {
      int len = strlen(ship_logo);
      if (len >= PAGENAME_LEN) {
        ship_logo[PAGENAME_LEN - 1] = '\0';
      }
    }
    write_pending = true;
  }
  ////////////
  if (audio1) {
    if (audio1_file) {
      mem_free(audio1_file);
      audio1_file = NULL;
    }
    audio1_file = mem_strdup(audio1);
    if (audio1_file) {
      int len = strlen(audio1_file);
      if (len >= PAGENAME_LEN) {
        audio1_file[PAGENAME_LEN - 1] = '\0';
      }
    }
    write_pending = true;
  }
  ////////////
  if (audio2) {
    if (audio2_file) {
      mem_free(audio2_file);
      audio2_file = NULL;
    }
    audio2_file = mem_strdup(audio2);
    if (audio2_file) {
      int len = strlen(audio2_file);
      if (len >= PAGENAME_LEN) {
        audio2_file[PAGENAME_LEN - 1] = '\0';
      }
    }
    write_pending = true;
  }
  ////////////
  if (ppic) {
    picture_id = *ppic;
    write_pending = true;
  }
  ////////////
  if (audio3) {
    if (audio3_file) {
      mem_free(audio3_file);
      audio3_file = NULL;
    }
    audio3_file = mem_strdup(audio3);
    if (audio3_file) {
      int len = strlen(audio3_file);
      if (len >= PAGENAME_LEN) {
        audio3_file[PAGENAME_LEN - 1] = '\0';
      }
    }
    write_pending = true;
  }
  ////////////
  if (audio4) {
    if (audio4_file) {
      mem_free(audio4_file);
      audio4_file = NULL;
    }
    audio4_file = mem_strdup(audio4);
    if (audio4_file) {
      int len = strlen(audio4_file);
      if (len >= PAGENAME_LEN) {
        audio4_file[PAGENAME_LEN - 1] = '\0';
      }
    }
    write_pending = true;
  }
}
void pilot::get_multiplayer_data(char *logo, char *audio1, char *audio2, uint16_t *ppic, char *audio3, char *audio4) {
  if (logo) {
    if (ship_logo) {
      strcpy(logo, ship_logo);
    } else {
      *logo = '\0';
    }
  }

  if (audio1) {
    if (audio1_file) {
      strcpy(audio1, audio1_file);
    } else {
      *audio1 = '\0';
    }
  }

  if (audio2) {
    if (audio2_file) {
      strcpy(audio2, audio2_file);
    } else {
      *audio2 = '\0';
    }
  }

  if (audio3) {
    if (audio3_file) {
      strcpy(audio3, audio3_file);
    } else {
      *audio3 = '\0';
    }
  }

  if (audio4) {
    if (audio4_file) {
      strcpy(audio4, audio4_file);
    } else {
      *audio4 = '\0';
    }
  }

  if (ppic) {
    *ppic = picture_id;
  }
}

void pilot::set_difficulty(uint8_t diff) {
  difficulty = diff;
  write_pending = true;
}
void pilot::get_difficulty(uint8_t *diff) {
  if (diff) {
    *diff = difficulty;
  }
}

void pilot::set_profanity_filter(bool enable) {
  profanity_filter_on = enable;
  write_pending = true;
  grtext_SetProfanityFilter(enable);
}

void pilot::get_profanity_filter(bool *enabled) {
  if (enabled) {
    *enabled = profanity_filter_on;
  }
}

void pilot::set_audiotaunts(bool enable) {
  audiotaunts = enable;
  write_pending = true;
  taunt_Enable(enable);
}

void pilot::get_audiotaunts(bool *enabled) {
  if (enabled) {
    *enabled = audiotaunts;
  }
}

void pilot::set_guidebot_name(char *name) {
  if (guidebot_name) {
    mem_free(guidebot_name);
    guidebot_name = NULL;
  }

  if (name) {
    guidebot_name = mem_strdup(name);
  } else {
    guidebot_name = mem_strdup("GB");
  }
}

void pilot::get_guidebot_name(char *name) {
  if (guidebot_name) {
    strcpy(name, guidebot_name);
  } else {
    strcpy(name, "GB");
  }
}

void pilot::set_hud_data(uint8_t *hmode, uint16_t *hstat, uint16_t *hgraphicalstat, int *gw_w, int *gw_h) {
  if (hmode) {
    // should do checking here
    switch (*hmode) {
    case HUD_COCKPIT:
    case HUD_FULLSCREEN:
      hud_mode = *hmode;
      write_pending = true;
      break;
    default:
      mprintf(0, "PILOT: Trying to set hode mode to invalid mode (%d)\n", *hmode);
    }
  }

  if (hstat) {
    hud_stat = *hstat;
    write_pending = true;
  }

  if (hgraphicalstat) {
    hud_graphical_stat = *hgraphicalstat;
    write_pending = true;
  }

  if (gw_w) {
    game_window_w = *gw_w;
    write_pending = true;
  }

  if (gw_h) {
    game_window_h = *gw_h;
    write_pending = true;
  }
}
void pilot::get_hud_data(uint8_t *hmode, uint16_t *hstat, uint16_t *hgraphicalstat, int *gw_w, int *gw_h) {
  if (hmode) {
    *hmode = hud_mode;
  }

  if (hstat) {
    *hstat = hud_stat;
  }

  if (hgraphicalstat) {
    *hgraphicalstat = hud_graphical_stat;
  }

  if (gw_w) {
    *gw_w = game_window_w;
  }

  if (gw_h) {
    *gw_h = game_window_h;
  }
}

void pilot::add_mission_data(tMissionData *mdata) {
  if (!mdata) {
    Int3();
    return;
  }

  if (find_mission_data(mdata->mission_name) != -1) {
    Int3();
    mprintf(0, "Mission already exists\n");
    return;
  }

  mprintf(0, "Adding new mission data for (%s)\n", mdata->mission_name);

  tMissionData *new_data = (tMissionData *)mem_malloc((num_missions_flown + 1) * sizeof(tMissionData));
  if (!new_data) {
    mprintf(0, "Out of memory\n");
    return;
  }

  ASSERT(num_missions_flown >= 0);

  if (mission_data && num_missions_flown > 0) {
    memcpy(new_data, mission_data, sizeof(tMissionData) * num_missions_flown);
    mem_free(mission_data);
  }

  mission_data = new_data;

  memcpy(&mission_data[num_missions_flown], mdata, sizeof(tMissionData));

  num_missions_flown++;
}
void pilot::edit_mission_data(int index, tMissionData *mdata) {
  if (index < 0 || index >= num_missions_flown) {
    mprintf(0, "Invalid mission index\n");
    Int3();
    return;
  }

  if (!mission_data) {
    Int3();
    mprintf(0, "No mission data\n");
    return;
  }

  if (!mdata) {
    Int3();
    return;
  }

  memcpy(&mission_data[index], mdata, sizeof(tMissionData));
}

void pilot::get_mission_data(int index, tMissionData *mdata) {
  if (index < 0 || index >= num_missions_flown) {
    mprintf(0, "Invalid mission index\n");
    Int3();
    return;
  }

  if (!mission_data) {
    Int3();
    mprintf(0, "No mission data\n");
    return;
  }

  if (!mdata) {
    Int3();
    return;
  }

  memcpy(mdata, &mission_data[index], sizeof(tMissionData));
}

int pilot::find_mission_data(const char *mission_name) {
  if (num_missions_flown <= 0) {
    ASSERT(num_missions_flown == 0);
    return -1;
  }

  ASSERT(mission_data);
  if (!mission_data)
    return -1;

  for (int i = 0; i < num_missions_flown; i++) {
    if (!stricmp(mission_data[i].mission_name, mission_name)) {
      return i;
    }
  }

  return -1;
}

// internal file access functions
// for the read functions, skip is true if the data should actually
// just be skipped and not processed

void pilot::write_name(CFILE *file) {
  if (!name) {
    // write out a dummy name
    cf_WriteString(file, "No Name");
    return;
  }

  cf_WriteString(file, name);
}

void pilot::read_name(CFILE *file, bool skip) {
  char buffer[PILOT_STRING_SIZE];

  cf_ReadString(buffer, PILOT_STRING_SIZE, file);

  if (!skip) {
    if (name) {
      mem_free(name);
      name = NULL;
    }
    name = mem_strdup(buffer);
  }
}

void pilot::write_ship_info(CFILE *file) {
  if (ship_model) {
    cf_WriteString(file, ship_model);
  } else {
    cf_WriteString(file, DEFAULT_SHIP);
  }
}

void pilot::read_ship_info(CFILE *file, bool skip) {
  char buffer[PAGENAME_LEN];

  cf_ReadString(buffer, PAGENAME_LEN, file);

  if (!skip) {
    if (ship_model) {
      mem_free(ship_model);
      ship_model = NULL;
    }
    ship_model = mem_strdup(buffer);
  }
}

void pilot::write_custom_multiplayer_data(CFILE *file) {
  if (ship_logo) {
    cf_WriteString(file, ship_logo);
  } else {
    cf_WriteString(file, "");
  }

  if (audio1_file) {
    cf_WriteString(file, audio1_file);
  } else {
    cf_WriteString(file, "");
  }

  if (audio2_file) {
    cf_WriteString(file, audio2_file);
  } else {
    cf_WriteString(file, "");
  }

  if (audio3_file) {
    cf_WriteString(file, audio3_file);
  } else {
    cf_WriteString(file, "");
  }

  if (audio4_file) {
    cf_WriteString(file, audio4_file);
  } else {
    cf_WriteString(file, "");
  }

  cf_WriteShort(file, picture_id);
}

void pilot::read_custom_multiplayer_data(CFILE *file, bool skip) {
  char buffer[PAGENAME_LEN];
  uint16_t temp;

  cf_ReadString(buffer, PAGENAME_LEN, file);
  if (!skip) {
    if (ship_logo) {
      mem_free(ship_logo);
      ship_logo = NULL;
    }
    ship_logo = mem_strdup(buffer);
  }

  cf_ReadString(buffer, PAGENAME_LEN, file);
  if (!skip) {
    if (audio1_file) {
      mem_free(audio1_file);
      audio1_file = NULL;
    }
    audio1_file = mem_strdup(buffer);
  }

  cf_ReadString(buffer, PAGENAME_LEN, file);
  if (!skip) {
    if (audio2_file) {
      mem_free(audio2_file);
      audio2_file = NULL;
    }
    audio2_file = mem_strdup(buffer);
  }

  if (file_version >= PFV_AUDIOTAUNT3N4) {
    cf_ReadString(buffer, PAGENAME_LEN, file);
    if (!skip) {
      if (audio3_file) {
        mem_free(audio3_file);
        audio3_file = NULL;
      }
      audio3_file = mem_strdup(buffer);
    }

    cf_ReadString(buffer, PAGENAME_LEN, file);
    if (!skip) {
      if (audio4_file) {
        mem_free(audio4_file);
        audio4_file = NULL;
      }
      audio4_file = mem_strdup(buffer);
    }
  }

  temp = cf_ReadShort(file);
  if (!skip) {
    picture_id = temp;
  }
}

void pilot::write_difficulty(CFILE *file) { cf_WriteByte(file, difficulty); }

void pilot::read_difficulty(CFILE *file, bool skip) {
  uint8_t temp;

  temp = cf_ReadByte(file);
  if (!skip) {
    difficulty = temp;
  }
}

void pilot::write_profanity_filter(CFILE *file) { cf_WriteByte(file, (profanity_filter_on) ? 1 : 0); }

void pilot::read_profanity_filter(CFILE *file, bool skip) {
  bool temp;

  temp = cf_ReadByte(file) ? true : false;
  if (!skip) {
    profanity_filter_on = temp;
    grtext_SetProfanityFilter(profanity_filter_on);
  }
}

void pilot::write_audiotaunts(CFILE *file) { cf_WriteByte(file, (audiotaunts) ? 1 : 0); }

void pilot::read_audiotaunts(CFILE *file, bool skip) {
  bool temp;

  temp = cf_ReadByte(file) ? true : false;
  if (!skip) {
    audiotaunts = temp;
    taunt_Enable(audiotaunts);
  }
}

void pilot::write_guidebot_name(CFILE *file) {
  if (guidebot_name) {
    cf_WriteByte(file, 1);
    cf_WriteString(file, guidebot_name);
  } else {
    cf_WriteByte(file, 0);
  }
}

void pilot::read_guidebot_name(CFILE *file, bool skip) {
  if (guidebot_name) {
    mem_free(guidebot_name);
    guidebot_name = NULL;
  }

  int len = cf_ReadByte(file);
  char buffer[256];

  if (len) {
    cf_ReadString(buffer, 256, file);
    guidebot_name = mem_strdup(buffer);
  } else {
    guidebot_name = mem_strdup("GB");
  }
}

void pilot::write_hud_data(CFILE *file) {
  cf_WriteByte(file, hud_mode);
  cf_WriteShort(file, hud_stat);
  cf_WriteShort(file, hud_graphical_stat);
  cf_WriteInt(file, game_window_w);
  cf_WriteInt(file, game_window_h);

  //	PFV_REARVIEWINFO
  cf_WriteByte(file, (int8_t)lrearview_enabled);
  cf_WriteByte(file, (int8_t)rrearview_enabled);
}

void pilot::read_hud_data(CFILE *file, bool skip) {
  uint8_t temp_b;
  uint16_t temp_s;
  int temp_i;

  temp_b = cf_ReadByte(file);
  if (!skip) {
    hud_mode = temp_b;
  }

  temp_s = cf_ReadShort(file);
  if (!skip) {
    hud_stat = temp_s;
  }

  temp_s = cf_ReadShort(file);
  if (!skip) {
    hud_graphical_stat = temp_s;
  }

  temp_i = cf_ReadInt(file);
  if (!skip) {
    game_window_w = temp_i;
  }

  temp_i = cf_ReadInt(file);
  if (!skip) {
    game_window_h = temp_i;
  }

  // kill graphical stat for inventory and reset to text version
  if (!skip) {
    if (hud_graphical_stat & STAT_INVENTORY) {
      hud_graphical_stat = hud_graphical_stat & (~STAT_INVENTORY);
      hud_stat = hud_stat | STAT_INVENTORY;
    }
  }

  // read smallview state
  if (file_version >= PFV_REARVIEWINFO) {
    lrearview_enabled = (bool)(cf_ReadByte(file) != 0);
    rrearview_enabled = (bool)(cf_ReadByte(file) != 0);
  } else {
    lrearview_enabled = false;
    rrearview_enabled = false;
  }
}

void pilot::write_mission_data(CFILE *file) {
  int i;
  cf_WriteInt(file, num_missions_flown);

  for (i = 0; i < num_missions_flown; i++) {
    cf_WriteByte(file, mission_data[i].highest_level);
    cf_WriteByte(file, mission_data[i].finished);
    cf_WriteString(file, mission_data[i].mission_name);
    cf_WriteInt(file, mission_data[i].num_restores);
    cf_WriteInt(file, mission_data[i].num_saves);
    cf_WriteInt(file, mission_data[i].ship_permissions);
  }
}

void pilot::read_mission_data(CFILE *file, bool skip) {
  int temp_i, i, temp_perm;
  uint8_t temp_b1, temp_b2;
  int temp_restores = 0, temp_saves = 0;
  char temp_s[MSN_NAMELEN];

  skip = false; // hard code it so we always read this

  temp_i = cf_ReadInt(file);
  if (!skip) {
    num_missions_flown = temp_i;
  }

  if (temp_i <= 0) {
    // no more data to read
    return;
  }

  if (!skip) {
    // allocate needed memory
    if (mission_data) {
      mem_free(mission_data);
      mission_data = NULL;
    }
    mission_data = (tMissionData *)mem_malloc(sizeof(tMissionData) * num_missions_flown);
    if (!mission_data) {
      // out of memory
      num_missions_flown = 0;
      skip = true;
    }
  }

  for (i = 0; i < temp_i; i++) {
    temp_b1 = cf_ReadByte(file);
    temp_b2 = cf_ReadByte(file);
    cf_ReadString(temp_s, MSN_NAMELEN, file);

    if (file_version >= PFV_AUDIOTAUNT3N4) {
      temp_restores = cf_ReadInt(file);
      temp_saves = cf_ReadInt(file);
    } else {
      temp_restores = temp_saves = 0;
    }

    if (file_version >= PFV_SHIPPERMISSIONS) {
      temp_perm = cf_ReadInt(file);
    } else {
      temp_perm = Default_ship_permission;
    }

    if (!skip) {
      mission_data[i].highest_level = temp_b1;
      mission_data[i].ship_permissions = temp_perm;
      mission_data[i].finished = (temp_b2) ? true : false;
      mission_data[i].num_restores = temp_restores;
      mission_data[i].num_saves = temp_saves;
      strcpy(mission_data[i].mission_name, temp_s);
    }
  }
}

void pilot::write_taunts(CFILE *file) {
  int i;
  cf_WriteByte(file, MAX_PILOT_TAUNTS);

  for (i = 0; i < MAX_PILOT_TAUNTS; i++) {
    cf_WriteString(file, taunts[i]);
  }
}

void pilot::read_taunts(CFILE *file, bool skip) {
  int i;
  int num_taunts_in_file = cf_ReadByte(file);

  if (!skip) {
    for (i = 0; i < num_taunts_in_file; i++) {
      cf_ReadString(taunts[i], PILOT_TAUNT_SIZE, file);
    }

    // blank any remaining taunts
    for (; i < MAX_PILOT_TAUNTS; i++) {
      taunts[i][0] = '\0';
    }

  } else {
    char buffer[PILOT_TAUNT_SIZE];
    for (i = 0; i < num_taunts_in_file; i++) {
      cf_ReadString(buffer, PILOT_TAUNT_SIZE, file);
    }
  }
}

void pilot::write_controls(CFILE *file) {
  int i;

  cf_WriteByte(file, read_controller);
  cf_WriteByte(file, NUM_CONTROLLER_FUNCTIONS);

  for (i = 0; i < NUM_CONTROLLER_FUNCTIONS; i++) {
    cf_WriteInt(file, (int)controls[i].id);
    cf_WriteInt(file, (int)controls[i].type[0]);
    cf_WriteInt(file, (int)controls[i].type[1]);
    cf_WriteInt(file, (int)controls[i].value);
    cf_WriteByte(file, (int8_t)controls[i].flags[0]);
    cf_WriteByte(file, (int8_t)controls[i].flags[1]);
  }

  cf_WriteByte(file, N_MOUSE_AXIS);
  for (i = 0; i < N_MOUSE_AXIS; i++) {
    cf_WriteFloat(file, mouse_sensitivity[i]);
    mprintf(0, "pilot mousesens[%d]=%f\n", i, mouse_sensitivity[i]);
  }

  cf_WriteByte(file, N_JOY_AXIS);
  for (i = 0; i < N_JOY_AXIS; i++) {
    cf_WriteFloat(file, joy_sensitivity[i]);
  }
  cf_WriteFloat(file, key_ramping); // 0x29- keyramping

  cf_WriteByte(file, (mouselook_control ? 1 : 0)); // version 0x25 - mouselook
}

void pilot::read_controls(CFILE *file, bool skip) {
  float temp_f;
  uint8_t temp_b;
  int i;

  // Controller data
  temp_b = cf_ReadByte(file);

  // alway read this?
  read_controller = temp_b;

  temp_b = cf_ReadByte(file);

  for (i = 0; i < temp_b; i++) {
    int id, y;
    ct_type type[2];
    ct_config_data value;

    id = cf_ReadInt(file);
    type[0] = (ct_type)cf_ReadInt(file);
    type[1] = (ct_type)cf_ReadInt(file);
    value = (ct_config_data)cf_ReadInt(file);

    for (y = 0; y < temp_b; y++) {
      if (Controller_needs[y].id == id) {
        if (type[0] == ctNone) // do this if there are new functions that don't have ctNone.
          type[0] = Controller_needs[y].ctype[0];
        if (type[1] == ctNone) // do this if there are new functions that don't have ctNone.
          type[1] = Controller_needs[y].ctype[1];
        break;
      }
    }

    controls[y].id = id;
    controls[y].type[0] = type[0];
    controls[y].type[1] = type[1];
    controls[y].value = value;
    controls[y].flags[0] = (uint8_t)cf_ReadByte(file);
    controls[y].flags[1] = (uint8_t)cf_ReadByte(file);

    if (!skip)
      Controller->set_controller_function(controls[y].id, controls[y].type, controls[y].value, controls[y].flags);
  }

  // fill in remainder of pilot controls array.
  for (; i < NUM_CONTROLLER_FUNCTIONS; i++) {
    Controller->get_controller_function(Controller_needs[i].id, controls[i].type, &controls[i].value,
                                        controls[i].flags);
  }

  // Set controller enabled masks
  if (!skip && Controller) {
    Controller->mask_controllers((read_controller & READF_JOY) ? true : false,
                                 (read_controller & READF_MOUSE) ? true : false);
  }

  // mouse sensitivity
  temp_b = cf_ReadByte(file);
  for (i = 0; i < temp_b; i++) {
    temp_f = cf_ReadFloat(file);
    mouse_sensitivity[i] = temp_f;
    mprintf(0, "pilot mousesens[%d]=%f\n", i, mouse_sensitivity[i]);
  }
  for (; i < N_MOUSE_AXIS; i++) {
    mouse_sensitivity[i] = 1.0f;
  }

  // joystick sensitivity
  temp_b = cf_ReadByte(file);
  for (i = 0; i < temp_b; i++) {
    temp_f = cf_ReadFloat(file);
    joy_sensitivity[i] = temp_f;
  }
  for (; i < N_JOY_AXIS; i++) {
    joy_sensitivity[i] = 1.0f;
  }

  if (file_version >= PFV_KEYRAMPING) {
    temp_f = cf_ReadFloat(file);
    key_ramping = temp_f;
  }
  if (file_version >= PFV_MOUSELOOK) {
    temp_b = cf_ReadByte(file);
    mouselook_control = temp_b ? true : false;
  }
}

void pilot::write_weapon_select(CFILE *file) {
  int i;

  cf_WriteShort(file, MAX_PRIMARY_WEAPONS);
  for (i = 0; i < MAX_PRIMARY_WEAPONS; i++) {
    cf_WriteShort(file, PrimarySelectList[i]);
  }

  cf_WriteShort(file, MAX_SECONDARY_WEAPONS);
  for (i = 0; i < MAX_SECONDARY_WEAPONS; i++) {
    cf_WriteShort(file, SecondarySelectList[i]);
  }
}

void pilot::read_weapon_select(CFILE *file) {
  int i;
  int count;

  count = cf_ReadShort(file);
  for (i = 0; i < count; i++) {
    PrimarySelectList[i] = cf_ReadShort(file);
  }
  for (; i < MAX_PRIMARY_WEAPONS; i++) {
    // PrimarySelectList[i] = 0;
  }

  count = cf_ReadShort(file);
  for (i = 0; i < count; i++) {
    SecondarySelectList[i] = cf_ReadShort(file);
  }
  for (; i < MAX_SECONDARY_WEAPONS; i++) {
    // SecondarySelectList[i] = 0;
  }
}

void pilot::read_gameplay_toggles(CFILE *file, bool skip) {
  uint8_t count, i;
  bool toggles[16];

  for (i = 0; i < 16; i++)
    toggles[i] = false;

  count = (uint8_t)cf_ReadByte(file);
  if (count > 16) {
    Int3();
    count = 16;
  } // bad, very bad.

  for (i = 0; i < count; i++) {
    toggles[i] = (bool)(cf_ReadByte(file) ? true : false);
  }

  // define toggles.
  if (!skip) {
    gameplay_toggles.guided_mainview = toggles[0];
    gameplay_toggles.show_reticle = toggles[1];

    // verify that we are setting values correctly, if new toggles are added to pilot.
    gameplay_toggles.ship_noises = (count < 3) ? true : toggles[2];
  }
}

void pilot::write_gameplay_toggles(CFILE *file) {
  // number of toggles to write out!
  cf_WriteByte(file, 3);

  cf_WriteByte(file, (int8_t)gameplay_toggles.guided_mainview);
  cf_WriteByte(file, (int8_t)gameplay_toggles.show_reticle);
  cf_WriteByte(file, (int8_t)gameplay_toggles.ship_noises);
}
