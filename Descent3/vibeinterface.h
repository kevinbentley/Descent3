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

#ifndef VIBE_H_
#define VIBE_H_

#include "application.h"
#include "vecmat_external.h"
#include "controls.h"

// Initialize IntelliVIBE
void VIBE_Init(void);

// Shutdown IntelliVIBE
void VIBE_Close(void);

// Control functions
// Informs us of a quater-frame tick
void VIBE_DoQuaterFrame(bool first_frame);
void VIBE_WeaponFire(int weapon_index);
void VIBE_DoControls(game_controls *controls);
void VIBE_PlayerRespawn(void);
void VIBE_PlayerDeath(void);
void VIBE_DoForce(vector *force_vec);
void VIBE_DoPlayerDamage(float damage_amount);
void VIBE_DoLevelEnd(void);

#endif
