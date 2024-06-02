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

 * $Logfile: /DescentIII/Main/config.h $
 * $Revision: 28 $
 * $Date: 10/22/99 10:42a $
 * $Author: Matt $
 *
 * Header file for configuration functions (video, sound, etc)
 *
 * $Log: /DescentIII/Main/config.h $
 *
 * 28    10/22/99 10:42a Matt
 * Mac merge
 *
 * 27    6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 26    4/24/99 8:39p Samir
 * added ship sounds toggle.
 *
 * 25    3/22/99 4:26p Samir
 * added toggles for guided missile view and reticle.
 *
 * 24    2/28/99 3:22a Samir
 * reformatted video menu.
 *
 * 23    2/16/99 12:05p Samir
 * revamped ui for config menus.
 *
 * 22    1/31/99 7:25p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 21    12/09/98 5:28p Jason
 * added more options
 *
 * 20    11/10/98 5:14p Jeff
 * added Force Feedback configuration
 *
 * 19    10/19/98 7:08p Jeff
 * moved preset detail defines to config.cpp and updated them
 *
 * 18    10/19/98 6:30p Jeff
 * changes made for detail variables.  Put in preset values.  Preset
 * options.  Removed terrain_cast from detail.  Put new callbacks in
 * UIListBox and UISlider
 *
 * 17    10/15/98 1:33p Jeff
 * removed amount of debris detail level.  Added powerup halo detail
 * level.  Added predef detail level settings
 *
 * 16    10/12/98 3:01p Jeff
 * added vsync and more detail level settings
 *
 * 15    8/27/98 6:23p Jeff
 * changed autoleveling in config so it is a slider...had to convert
 * global from bool->uint8_t.  Added fast headlight and mirrored surfaces to
 * config menu
 *
 * 14    8/19/98 2:19p Jeff
 * moved detail globals to a struct
 *
 * 13    6/19/98 5:40p Samir
 * added hud configuration.
 *
 * 12    5/23/98 6:34p Jeff
 * All options menus are up-to-date, added Detail Level menu
 *
 * 11    5/06/98 4:32p Samir
 * screen res mode changes.
 *
 * 10    5/06/98 3:29p Jeff
 * changed whats needed for screen resolution change
 *
 * 9     4/06/98 4:57p Jeff
 * Added a dynamic lighting box in video config
 *
 * 8     3/05/98 11:32a Jeff
 *
 * 7     3/02/98 7:19p Jeff
 * Added Gamma slider support
 *
 * 6     3/02/98 3:29p Jeff
 * Convert d3.cfg from a binary to a text file
 *
 * 5     2/27/98 5:35p Jeff
 * Added in loading and saving of a game configuration file
 *
 * 4     2/24/98 3:44p Jeff
 * Basic structure, including some components added
 *
 * 3     2/23/98 5:35p Jeff
 * General shell created
 *
 * 2     2/23/98 5:16p Jeff
 * Initial creation
 *
 * $NoKeywords: $
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cstdint>

// Main menu configuration functions
// ------------------------------------------------------
// ConfigForceFeedback
//	Purpose:
//	Configures your Force Feedback device on your computer
// ------------------------------------------------------
void ConfigForceFeedback(void);

// General option toggles
struct tGameToggles {
  bool show_reticle;
  bool guided_mainview;
  bool ship_noises;
};

extern tGameToggles Game_toggles;

// this list should match the list in config.cpp to work.
#define N_SUPPORTED_VIDRES 8

#define RES_512X384 0
#define RES_640X480 1
#define RES_800X600 2
#define RES_960X720 3
#define RES_1024X768 4
#define RES_1280X960 5
#define RES_1600X1200 6
// stored resolution list and desired game resolution
struct tVideoResolution {
  uint16_t width;
  uint16_t height;
};

extern tVideoResolution Video_res_list[];
extern int Game_video_resolution;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// KEEP THESE MEMBERS IN THE SAME ORDER, IF YOU ADD,REMOVE, OR CHANGE ANYTHING IN THIS STRUCT, MAKE SURE YOU
// UPDATE DetailPresetLow,DetailPresetMed,DetailPresetHigh AND DetailPresetVHi IN CONFIG.CPP
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
struct tDetailSettings {
  float Terrain_render_distance; // VisibleTerrainDistance
  float Pixel_error;             // PixelErrorTolerance
  bool Specular_lighting;        // DoSpecularPass
  bool Dynamic_lighting;         // Enable_dynamic_lighting
  bool Fast_headlight_on;
  bool Mirrored_surfaces;
  bool Fog_enabled;
  bool Coronas_enabled;
  bool Procedurals_enabled;
  bool Powerup_halos;
  bool Scorches_enabled;
  bool Weapon_coronas_enabled;
  bool Bumpmapping_enabled;
  uint8_t Specular_mapping_type;
  uint8_t Object_complexity; // 0 = low, 1 = medium, 2=high
};

// Call this with one of the above defines to set the detail level to a predefined set (custom level is ignored)
void ConfigSetDetailLevel(int level);
// returns the current detail level that the given tDetailSettings is at
int ConfigGetDetailLevel(tDetailSettings *ds);

#define DETAIL_LEVEL_LOW 0
#define DETAIL_LEVEL_MED 1
#define DETAIL_LEVEL_HIGH 2
#define DETAIL_LEVEL_VERY_HIGH 3
#define DETAIL_LEVEL_CUSTOM 4

extern tDetailSettings Detail_settings;
extern int Default_detail_level;

// displays new options menu
extern void OptionsMenu();
#endif
