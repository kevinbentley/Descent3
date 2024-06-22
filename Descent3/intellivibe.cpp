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

 * $Logfile: /DescentIII/Main/intellivibe.cpp $
 * $Revision: 5 $
 * $Date: 4/28/00 6:49p $
 * $Author: Jeff $
 *
 * IntelliVIBE interface
 *
 * $Log: /DescentIII/Main/intellivibe.cpp $
 *
 * 5     4/28/00 6:49p Jeff
 * created stub functions for non-win32
 *
 * 4     3/30/00 6:00p Jeff
 * changed name of ivibe dll
 *
 * 3     1/27/00 12:04p Jeff
 * updated IntelliVIBE to match new specs
 *
 * 2     1/26/00 9:20p Jeff
 * added support for IntelliVIBE DLL
 *
 * $NoKeywords: $
 */

#include "vibeinterface.h"

#ifndef WIN32
void VIBE_Init() {}
void VIBE_Close(void) {}
void VIBE_DoFrame(void) {}
void VIBE_WeaponFire(int weapon_index) {}
void VIBE_DoControls(game_controls *controls) {}
void VIBE_PlayerRespawn(void) {}
void VIBE_PlayerDeath(void) {}
void VIBE_DoForce(vector *force_vec, int weapon_index) {}
void VIBE_DoPlayerDamage(float damage_amount) {}
void VIBE_DoQuaterFrame(bool) {}
void VIBE_DoForce(vector *) {}
void VIBE_DoLevelEnd(void) {}
#else

#include "intellivibe.h"
#include "winapp.h"
#include "module.h"
#include "mono.h"
#include "object_external_struct.h"

static module IntelliVIBE_module = {NULL};
static d3_intellivibe IntelliVIBE_state; // our current state
static IntelliVIBE_Initialize_fp IVIBE_Initialize = NULL;
static IntelliVIBE_Shutdown_fp IVIBE_Shutdown = NULL;
static IntelliVIBE_DoQuaterFrame_fp IVIBE_DoQuaterFrame = NULL;

#define TEST_MODULE(x)                                                                                                 \
  {                                                                                                                    \
    if (!(x)) {                                                                                                        \
      mprintf(0, "IntelliVIBE unable to find: %s\n", #x);                                                            \
      mod_FreeModule(&IntelliVIBE_module);                                                                             \
      IntelliVIBE_module.handle = NULL;                                                                                \
      return;                                                                                                          \
    }                                                                                                                  \
  }
void VIBE_Init() {
  if (!mod_LoadModule(&IntelliVIBE_module, "ivibe_D3.dll")) {
    mprintf(0, "Unable to load IntelliVIBE DLL\n");
    IntelliVIBE_module.handle = NULL;
    return;
  }

  // resolve our functions
  IVIBE_Initialize = (IntelliVIBE_Initialize_fp)mod_GetSymbol(&IntelliVIBE_module, "IntelliVIBE_Initialize", 4);
  IVIBE_Shutdown = (IntelliVIBE_Shutdown_fp)mod_GetSymbol(&IntelliVIBE_module, "IntelliVIBE_Shutdown", 0);
  IVIBE_DoQuaterFrame =
      (IntelliVIBE_DoQuaterFrame_fp)mod_GetSymbol(&IntelliVIBE_module, "IntelliVIBE_DoQuaterFrame", 4);

  // make sure everything went ok
  TEST_MODULE(IVIBE_Initialize);
  TEST_MODULE(IVIBE_Shutdown);
  TEST_MODULE(IVIBE_DoQuaterFrame);

  d3_init_info info;
  info.hinst = Win32App()->instance();
  info.hwnd = Win32App()->windowHandle();

  ASSERT(IVIBE_Initialize != NULL);
  if (!IVIBE_Initialize(&info)) {
    mprintf(0, "IntelliVIBE_Initialize failed\n");
    mod_FreeModule(&IntelliVIBE_module);
    IntelliVIBE_module.handle = NULL;
    return;
  }

  // Initialize our current state
  memset(&IntelliVIBE_state, 0, sizeof(IntelliVIBE_state));

  atexit(VIBE_Close);
}

void VIBE_Close(void) {
  if (IntelliVIBE_module.handle == NULL)
    return;
  ASSERT(IVIBE_Shutdown != NULL);

  IVIBE_Shutdown();
  mod_FreeModule(&IntelliVIBE_module);
  IntelliVIBE_module.handle = NULL;
}

extern bool Game_paused;
extern float Frametime;
extern float Gametime;
extern float Shake_magnitude;
extern object *Player_object;

// Informs us of a quater-frame tick
void VIBE_DoQuaterFrame(bool first_frame) {
  if (IntelliVIBE_module.handle == NULL)
    return;
  ASSERT(IVIBE_DoQuaterFrame != NULL);

  static char quater_frame_count = 0;

  if (first_frame) {
    // reset the flags
    IntelliVIBE_state.flags = 0;
    IntelliVIBE_state.damage_info.damage_amount = 0;
    IntelliVIBE_state.force_info.force_vector.x = IntelliVIBE_state.force_info.force_vector.y =
        IntelliVIBE_state.force_info.force_vector.z = 0;
    quater_frame_count = 0;
  } else {
    quater_frame_count++;
  }

  // set our frametime and stuff
  IntelliVIBE_state.frame_info.frametime = Frametime;
  IntelliVIBE_state.frame_info.gametime = Gametime;
  IntelliVIBE_state.frame_info.game_paused = (Game_paused) ? 1 : 0;

  // reset the quaterframe flags
  IntelliVIBE_state.flags &=
      ~(VIBEFLAG_QUATERFRAME_0 | VIBEFLAG_QUATERFRAME_1 | VIBEFLAG_QUATERFRAME_2 | VIBEFLAG_QUATERFRAME_3);

  // set the flag for which quaterframe we are on
  switch (quater_frame_count) {
  case 0:
    IntelliVIBE_state.flags |= VIBEFLAG_QUATERFRAME_0;
    break;
  case 1:
    IntelliVIBE_state.flags |= VIBEFLAG_QUATERFRAME_1;
    break;
  case 2:
    IntelliVIBE_state.flags |= VIBEFLAG_QUATERFRAME_2;
    break;
  case 3:
    IntelliVIBE_state.flags |= VIBEFLAG_QUATERFRAME_3;
    break;
  }

  // send a quaterframe tick to IntelliVIBE
  IVIBE_DoQuaterFrame(&IntelliVIBE_state);
}

void VIBE_WeaponFire(int weapon_index) {
  IntelliVIBE_state.fire_info.weapon_index = weapon_index;
  IntelliVIBE_state.flags |= VIBEFLAG_WEAPON_FIRED;
}

void VIBE_DoControls(game_controls *controls) {
  IntelliVIBE_state.controls_info.pitch_thrust = controls->pitch_thrust;
  IntelliVIBE_state.controls_info.heading_thrust = controls->heading_thrust;
  IntelliVIBE_state.controls_info.bank_thrust = controls->bank_thrust;
  IntelliVIBE_state.controls_info.vertical_thrust = controls->vertical_thrust;
  IntelliVIBE_state.controls_info.sideways_thrust = controls->sideways_thrust;
  IntelliVIBE_state.controls_info.forward_thrust = controls->forward_thrust;
  IntelliVIBE_state.controls_info.afterburn_thrust = controls->afterburn_thrust;
  IntelliVIBE_state.controls_info.shake_magnitude = Shake_magnitude;
  IntelliVIBE_state.controls_info.current_velocity.x = Player_object->mtype.phys_info.velocity.x;
  IntelliVIBE_state.controls_info.current_velocity.y = Player_object->mtype.phys_info.velocity.y;
  IntelliVIBE_state.controls_info.current_velocity.z = Player_object->mtype.phys_info.velocity.z;
}

void VIBE_PlayerRespawn(void) { IntelliVIBE_state.flags |= VIBEFLAG_PLAYER_RESPAWN; }

void VIBE_PlayerDeath(void) { IntelliVIBE_state.flags |= VIBEFLAG_PLAYER_DEAD; }

void VIBE_DoForce(vector *force_vec) {
  vector curr_force;
  memcpy(&curr_force, &IntelliVIBE_state.force_info.force_vector, sizeof(vector));

  // add them up...we can have more than one a frame
  curr_force += *force_vec;
  memcpy(&IntelliVIBE_state.force_info.force_vector, &curr_force, sizeof(vector));

  IntelliVIBE_state.flags |= VIBEFLAG_FORCE_APPLIED;
}

void VIBE_DoPlayerDamage(float damage_amount) {
  IntelliVIBE_state.damage_info.damage_amount += damage_amount;
  IntelliVIBE_state.flags |= VIBEFLAG_PLAYER_DAMAGED;
}

void VIBE_DoLevelEnd(void) {
  IntelliVIBE_state.flags |= VIBEFLAG_LEVEL_END;

  // force a frame
  VIBE_DoQuaterFrame(false);
}

#endif
