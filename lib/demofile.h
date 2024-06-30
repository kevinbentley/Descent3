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

 * $Logfile: /DescentIII/main/lib/demofile.h $
 * $Revision: 25 $
 * $Date: 7/21/99 12:03p $
 * $Author: Kevin $
 *
 *
 *
 * $Log: /DescentIII/main/lib/demofile.h $
 *
 * 25    7/21/99 12:03p Kevin
 * Changed version numbers around
 *
 * 24    4/25/99 10:19p Matt
 * Fixed multiplayer and demo problems will killing an object from script,
 * and cleaned up the death code a bit in the process.
 *
 * 23    3/12/99 7:53p Jeff
 * save player rotating balls info, handle obj_observer with obj_player,
 * handle objects that use life left, handle 2d sound playing
 *
 * 22    3/11/99 11:40a Kevin
 * New stuff for multi
 *
 * 21    3/10/99 2:25p Kevin
 * Save/Load and Demo file fixes
 *
 * 20    2/25/99 11:01a Matt
 * Added new explosion system.
 *
 * 19    2/23/99 12:45a Jeff
 * added support for in-game-cinematics in demo system
 *
 * 18    2/22/99 9:21p Kevin
 * Added DT_CINEMATICS
 *
 * 17    2/08/99 7:05p Kevin
 * Trying to get demo system working with powerup scripts
 *
 * 16    1/23/99 10:12p Kevin
 * Added the start of osiris support into the demo system
 *
 * 15    11/24/98 3:57p Kevin
 * Demo system immprovements
 *
 * 14    11/24/98 12:08p Kevin
 *
 * 13    11/24/98 10:41a Kevin
 * Demo system
 *
 * 12    11/23/98 4:52p Kevin
 * Demo system enhancments
 *
 * 11    11/23/98 3:11p Kevin
 * Demo system
 *
 * 10    11/19/98 5:40p Kevin
 * Demo system
 *
 * 9     11/17/98 4:17p Kevin
 * Demo recording system
 *
 * 8     11/11/98 2:46p Kevin
 * Demo recording system work
 *
 * 7     11/09/98 4:12p Kevin
 *
 * 6     11/05/98 5:54p Kevin
 * Demo system work
 *
 * 5     10/08/98 12:00p Kevin
 * Demo system work
 *
 * 4     10/06/98 5:46p Kevin
 * Added new configuration for demo
 *
 * 3     10/05/98 12:09p Kevin
 * Converted projects to VC6 and demo file stuff added
 *
 * 2     10/05/98 10:32a Kevin
 * Initial Version
 *
 * 1     10/05/98 10:22a Kevin
 *
 * $NoKeywords: $
 */

#ifndef _DEMO_FILE_HEADER_
#define _DEMO_FILE_HEADER_

#include <cstdint>
#include <array>

#include "object_external_struct.h"

extern char Demo_fname[_MAX_PATH * 2];

extern uint32_t Demo_flags;
extern bool Demo_paused;
extern bool Demo_do_one_frame;
extern bool Demo_restart;
extern bool Demo_auto_play;
extern bool Demo_make_movie;
extern float Demo_frame_ofs;
extern std::array<uint16_t, MAX_OBJECTS> Demo_obj_map;
#define DF_NONE 0
#define DF_RECORDING 1
#define DF_PLAYBACK 2

#define D3_DEMO_SIG "D3DEM"
#define D3_DEMO_SIG_NEW "D3DM1"

#define DT_OBJ 1             // Object data
#define DT_NEW_FRAME 2       // Start of a new frame
#define DT_WEAPON_FIRE 3     // Someone fired a weapon
#define DT_HUD_MESSAGE 4     // Display a hud message
#define DT_3D_SOUND 5        // Play a 3d sound (associated with a weapon firing usually)
#define DT_OBJ_CREATE 6      // A new object was created...
#define DT_OBJ_ANIM 7        // Object animation has changed
#define DT_OBJ_TURRET 8      // Object's turrets have changed
#define DT_OBJ_EXPLODE 9     // Explode object
#define DT_PLAYER_DEATH 10   // Player died
#define DT_COLLIDE_PLR 11    // Player collided with a weapon
#define DT_COLLIDE_GEN 12    // generic collided with a weapon
#define DT_ATTACH 13         // Attach some objects
#define DT_ATTACH_RAD 14     // Attach some objects with a radius?
#define DT_UNATTACH 15       // Unattach some stuff
#define DT_WEAP_FIRE_FLAG 16 // flags like spraying and on/off
#define DT_PLAYER_INFO 17    // Player 1's info like energy/sheilds, etc.
#define DT_MSAFE 18          // MSAFE data (ie script stuff)
#define DT_POWERUP 19        // Powerups data
#define DT_CINEMATICS 20     // Cinematic info
#define DT_PERSISTANT_HUD 21 // Persistant hud message
#define DT_SETOBJDEAD 22     // Mark an object as dead
#define DT_PLAYERBALLS 23    // Rotating balls around player ship
#define DT_PLAYERTYPECHNG 24 // Player type is changing
#define DT_SETOBJLIFELEFT 25 // Object is getting OF_LIFELEFT flag changed
#define DT_2D_SOUND 26       // Play a 2d sound

// If not recording prompts user for filename and starts recording if successfull
// If recording, close the demo file
void DemoToggleRecording();

void DemoWriteChangedObj(object *op);

void DemoWriteHeader();

void DemoStartNewFrame();

void DemoWriteHudMessage(uint32_t color, bool blink, char *msg);

void DemoWriteChangedObjects();

void DemoWriteWeaponFire(uint16_t objectnum, vector *pos, vector *dir, uint16_t weaponnum,
                         uint16_t weapobjnum, int16_t gunnum);

void DemoWriteObjCreate(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient, int parent_handle,
                        object *obj);

void DemoWriteTurretChanged(uint16_t objnum);

int DemoReadHeader();

int DemoPlaybackFile(char *filename);

bool LoadDemoDialog();

void DemoFrame();

void DemoAbort(bool deletefile = false);

void DemoWriteKillObject(object *hit_obj, object *killer, float damage, int death_flags, float delay, int seed);

void DemoWritePlayerDeath(object *player, bool melee, int fate = -1);

void DemoWrite3DSound(int16_t soundidx, uint16_t objnum, int priority, float volume = 0.5f);

void DemoWriteCollidePlayerWeapon(object *playerobj, object *weapon, vector *collision_point, vector *collision_normal,
                                  bool f_reverse_normal, void *hit_info);

void DemoWriteCollideGenericWeapon(object *robotobj, object *weapon, vector *collision_point, vector *collision_normal,
                                   bool f_reverse_normal, void *hit_info);

void DemoReadCollidePlayerWeapon(void);

void DemoReadCollideGenericWeapon(void);

void DemoReadNewFrame(void);

void DemoWriteObjAnimChanged(uint16_t objnum);

void DemoWriteAttachObjRad(object *parent, char parent_ap, object *child, float rad);

void DemoReadAttachObjRad(void);

void DemoWriteAttachObj(object *parent, char parent_ap, object *child, char child_ap, bool f_aligned);

void DemoReadAttachObj(void);

void DemoWriteUnattachObj(object *child);

void DemoReadUnattachObj(void);

void DemoPostPlaybackMenu(void);

void DemoReadObjWeapFireFlagChanged(void);

void DemoWriteObjWeapFireFlagChanged(int16_t objnum);

void DemoWritePlayerInfo(void);

void DemoReadPlayerInfo(void);

void DemoPlayAutoDemo(void);

void DemoWriteMSafe(uint8_t *data, uint16_t len);

void DemoReadMSafe();

void DemoWritePowerup(uint8_t *data, uint16_t len);

void DemoReadPowerups();

void DemoReadCinematics();

void DemoWriteCinematics(uint8_t *data, uint16_t len);

void DemoWritePersistantHUDMessage(ddgr_color color, int x, int y, float time, int flags, int sound_index, char *msg);

void DemoReadPersistantHUDMessage();

void DemoWriteSetObjDead(object *obj);
void DemoReadSetObjDead();

void DemoWritePlayerBalls(int pnum);
void DemoReadPlayerBalls(void);

void DemoWritePlayerTypeChange(int slot, bool stop_observing = false, int observer_mode = -1, int piggy_objnum = -1);
void DemoReadPlayerTypeChange(void);

void DemoWriteObjLifeLeft(object *obj);
void DemoReadObjLifeLeft(void);

void DemoWrite2DSound(int16_t soundidx, float volume = 0.5f);
void DemoRead2DSound(void);

#endif
