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

 * $Logfile: /DescentIII/main/pilot_class.h $
 * $Revision: 17 $
 * $Date: 3/20/00 12:07p $
 * $Author: Matt $
 *
 * Pilot class and access functions
 *
 * $Log: /DescentIII/main/pilot_class.h $
 *
 * 17    3/20/00 12:07p Matt
 * Merge of Duane's post-1.3 changes.
 * Changed difficulty level to be a global variable instead of a function
 * call
 *
 * 16    10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 15    7/20/99 1:18p Samir
 * save state of rearviews between game through the pilot file.
 *
 * 14    5/02/99 12:56a Jeff
 * save ship permissions at highest level achieved and use that on restore
 * to a level previously played
 *
 * 13    4/30/99 1:29p Samir
 * added save for key ramping
 *
 * 12    4/27/99 1:56p Jeff
 * audio taunts stuff in pilot menu, added stringtables
 *
 * 11    4/25/99 2:33a Jeff
 * fixed bug trying to read pilot files that are too new
 *
 * 10    4/20/99 7:29p Jeff
 * added guidebot name
 *
 * 9     4/15/99 2:55p Samir
 * added UI for mouselook.
 *
 * 8     4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 7     4/05/99 5:13p Samir
 * added game toggles.
 *
 * 6     4/03/99 2:19a Jeff
 * added profanity filter stuff
 *
 * 5     3/22/99 6:22p Jeff
 * added 2 more audio taunts.  a mulitplayer event when someone plays an
 * audio taunt.  option to disable audio taunts.
 *
 * 4     3/15/99 9:24p Gwar
 *
 * 3     2/18/99 5:56p Jeff
 * added weapon select data
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

#ifndef __PILOT_CLASS_H_
#define __PILOT_CLASS_H_

#include "pstypes.h"
#include "controls.h"
#include "controller.h"
#include "cfile.h"
#include "weapon.h"
#include "config.h"

// YUCK!
#include "descent.h" //just for MSN_NAMELEN

/*
=======================================================================

IIIIIIIII MM     MM PPPP   OOOO  RRRR  TTTTTTT   AA   NN   NN TTTTTTT
   II     MM     MM P   P O    O R   R    T      AA   NNN  NN    T
   II     M M   M M P   P O    O R   R    T     A  A  NN N NN    T
   II     M  M M  M P  P  O    O R  R     T     A  A  NN N NN    T
   II     M  M M  M PPP   O    O RRR      T    AAAAAA NN  NNN    T
   II     M   M   M P     O    O R  R     T    A    A NN  NNN    T
IIIIIIIII N       N P      OOOO  R   R    T    A    A NN   NN    T

=======================================================================

  If you add new data members to the pilot class, you _must_ do the following:

  1) Add functionality to the pilot::initialize();
  2) Add functionality to the pilot::clean();
  3) Add functionality to the pilot::verify();
  4) Create a pilot::write_ function
  5) Create a corresponding pilot::read_ function
  6) Add to calls to your write_ and read_ functions in pilot::flush() and pilot::read()
*/

// Maximum size of the pilot name
#define PILOT_STRING_SIZE 20
// Invalid Pilot Pic ID
#define PPIC_INVALID_ID 65535
// should be put somewhere else, but here for the demo.
#define N_MOUSE_AXIS 2
#define N_JOY_AXIS 6

// Number of multiplayer taunts
#define MAX_PILOT_TAUNTS 8
// Maximum string length of a taunt
#define PILOT_TAUNT_SIZE 60

// file error codes
#define PLTW_NO_ERROR 0      // there was no error
#define PLTW_NO_FILENAME 1   // no filename has been set
#define PLTW_FILE_EXISTS 2   // the file already exists
#define PLTW_FILE_CANTOPEN 3 // file couldn't be opened
#define PLTW_CFILE_FATAL 4   // a CFILE error had occurred
#define PLTW_UNKNOWN_FATAL 5 // an unknown exception occurred

#define PLTR_NO_ERROR 0      // there was no error
#define PLTR_NO_FILENAME 1   // no filename has been set
#define PLTR_FILE_NOEXIST 2  // the file doesn't exist to read
#define PLTR_FILE_CANTOPEN 3 // file couldn't be opened
#define PLTR_CFILE_FATAL 4   // a CFILE error had occurred
#define PLTR_UNKNOWN_FATAL 5 // an uknown exception occurred
#define PLTR_TOO_NEW 6       // pilot file too new

struct tMissionData {
  uint8_t highest_level;            // highlest level completed in the mission
  int ship_permissions;           // Ship permissions at highest level achieved
  bool finished;                  // was mission finished? (different than highest level,btw)
  char mission_name[MSN_NAMELEN]; // name of the mission (from the mission file)
  int num_restores;               // number of game loads for this mission
  int num_saves;                  // number of game saves for this mission
};

struct cntrldata {
  int id;
  ct_type type[2];
  ct_config_data value;
  uint8_t flags[2];
};

class pilot {

public:
  ~pilot();
  pilot();
  pilot(pilot *copy);
  pilot(char *fname);

  // This function guts the data so it's virgin (fresh for reading)
  // frees any memory that needs to be freed, etc.
  // if reset is true, it resets all data to what it is at initialization
  // else it is an unknown state
  void clean(bool reset = true);

  // This function verifies all the pilot data, making sure nothing is out of whack
  // It will correct any messed data.
  void verify(void);

  // This function makes the pilot file so it's write pending, meaning that
  // on the next call to flush, it will actually write out the data.  There is
  // no need to constantly do file access unless it's really needed
  void write(void);

  // This function makes certain that the pilot data is up to date with the
  // actual pilot file, writing if needed.
  int flush(bool new_file);

  // This function sets the filename that is associated with this pilot
  void set_filename(char *fname);
  void get_filename(char *fname);

  // This function reads in the data from file (from the filename associated)
  // into the pilot data.
  int read(bool skip_control_set, bool skip_mission_data);

public:
  // data access functions
  void set_name(const char *name);
  void get_name(char *name);

  void set_ship(const char *ship);
  void get_ship(char *ship);

  void set_multiplayer_data(const char *logo = NULL, const char *audio1 = NULL, const char *audio2 = NULL, const uint16_t *ppic = NULL,
                            const char *audio3 = NULL, const char *audio4 = NULL);
  void get_multiplayer_data(char *logo = NULL, char *audio1 = NULL, char *audio2 = NULL, uint16_t *ppic = NULL,
                            char *audio3 = NULL, char *audio4 = NULL);

  void set_difficulty(uint8_t diff);
  void get_difficulty(uint8_t *diff);

  void set_hud_data(uint8_t *hmode = NULL, uint16_t *hstat = NULL, uint16_t *hgraphicalstat = NULL, int *gw_w = NULL,
                    int *gw_h = NULL);
  void get_hud_data(uint8_t *hmode = NULL, uint16_t *hstat = NULL, uint16_t *hgraphicalstat = NULL, int *gw_w = NULL,
                    int *gw_h = NULL);

  void set_profanity_filter(bool enable);
  void get_profanity_filter(bool *enabled);

  void set_audiotaunts(bool enable);
  void get_audiotaunts(bool *enabled);

  void set_guidebot_name(char *name);
  void get_guidebot_name(char *name);

  void add_mission_data(tMissionData *data);
  void edit_mission_data(int index, tMissionData *data);
  void get_mission_data(int index, tMissionData *data);
  int find_mission_data(const char *mission_name);

private:
  void initialize(void); // initializes all the data (for constructors)
  bool write_pending;    // data has changed and pilot data is out of sync with file
private:
  // internal file access functions
  void write_name(CFILE *file);
  void write_ship_info(CFILE *file);
  void write_custom_multiplayer_data(CFILE *file);
  void write_difficulty(CFILE *file);
  void write_hud_data(CFILE *file);
  void write_mission_data(CFILE *file);
  void write_taunts(CFILE *file);
  void write_weapon_select(CFILE *file);
  void write_controls(CFILE *file);
  void write_profanity_filter(CFILE *file);
  void write_audiotaunts(CFILE *file);
  void write_gameplay_toggles(CFILE *file);
  void write_guidebot_name(CFILE *file);

  // for the read functions, skip is true if the data should actually
  // just be skipped and not processed
  int file_version;
  void read_name(CFILE *file, bool skip);
  void read_ship_info(CFILE *file, bool skip);
  void read_custom_multiplayer_data(CFILE *file, bool skip);
  void read_difficulty(CFILE *file, bool skip);
  void read_hud_data(CFILE *file, bool skip);
  void read_mission_data(CFILE *file, bool skip);
  void read_taunts(CFILE *file, bool skip);
  void read_weapon_select(CFILE *file);
  void read_controls(CFILE *file, bool skip);
  void read_profanity_filter(CFILE *file, bool skip);
  void read_audiotaunts(CFILE *file, bool skip);
  void read_gameplay_toggles(CFILE *file, bool skip);
  void read_guidebot_name(CFILE *file, bool skip);

private:
  //--- Pilot data				---//
  //--- Try to preserve alignment	---//
  char *filename;      // filename location of this pilot
  char *name;          // name of the pilot (used in the game)
  char *ship_logo;     // ship logo for multiplayer play (filename)
  char *ship_model;    // what ship does this pilot fly
  char *audio1_file;   // audio taunt #1 (filename)
  char *audio2_file;   // audio taunt #2 (filename)
  char *audio3_file;   // audio taunt #1 (filename)
  char *audio4_file;   // audio taunt #2 (filename)
  char *guidebot_name; // guidebot name

  uint16_t picture_id; // pilot picture image id
  uint8_t difficulty;  // difficulty setting for this pilot (DIFFICULTY_*)
  uint8_t hud_mode;    // hud display mode
  bool profanity_filter_on, audiotaunts;

  uint16_t hud_stat; // hud layout using the STAT mask
  uint16_t hud_graphical_stat;

  int game_window_w, game_window_h; // game window size

  int num_missions_flown;     // number of mission's flown
  tMissionData *mission_data; // mission data

  uint16_t PrimarySelectList[MAX_PRIMARY_WEAPONS];
  uint16_t SecondarySelectList[MAX_SECONDARY_WEAPONS];

  tGameToggles gameplay_toggles; // special options in config menu.

public:
  char taunts[MAX_PILOT_TAUNTS][PILOT_TAUNT_SIZE]; // taunt macros

  cntrldata controls[NUM_CONTROLLER_FUNCTIONS]; // controller settings
  float mouse_sensitivity[N_MOUSE_AXIS];        // axis sensitivities
  float joy_sensitivity[N_JOY_AXIS];            // axis sensitivities
  float key_ramping;
  char read_controller;   // do we read the controller port also (beyond keyboard/mouse)
  bool mouselook_control; // mouselook control.
  bool lrearview_enabled;
  bool rrearview_enabled; // are these small views enabled?

  uint8_t ingame_difficulty; // DAJ for optimization
};

#endif
