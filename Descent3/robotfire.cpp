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

#include "robotfire.h"
#include "object.h"
#include "objinfo.h"

#include "config.h" // for game toggles.
#include "objinfo.h"
#include "weapon.h"
#include "ship.h"
#include "game.h"
#include "polymodel.h"
#include "sounds.h"
#include "hlsoundlib.h"
#include "multi.h"
#include "player.h"
#include "demofile.h"
#include "SmallViews.h"
#include "physics.h"
#include "AIMain.h"

#include <stdlib.h>

#include "psrand.h"
// Fires a multiplayer and AI on/off weapon
void FireOnOffWeapon(object *objp) {
  if (objp->type == OBJ_PLAYER) {
    int slot = objp->id;

    int ship_index = Players[slot].ship_index;
    int wb_index = Players[slot].weapon[PW_PRIMARY].index;

    if (WBIsBatteryReady(objp, &Ships[ship_index].static_wb[wb_index], wb_index)) {
      WBFireBattery(objp, &Ships[ship_index].static_wb[wb_index], 0, wb_index);
    }
  } else if (objp->ai_info) {
    char wb_index = objp->ai_info->last_special_wb_firing;
    if (wb_index > MAX_WBS_PER_OBJ) { // DAJ
      mprintf(2, "FireOnOffWeapon wb_index %d > MAX_WBS_PER_OBJ\n", wb_index);
      return;
    }

    if (WBIsBatteryReady(objp, &Object_info[objp->id].static_wb[wb_index], wb_index)) {
      WBFireBattery(objp, &Object_info[objp->id].static_wb[wb_index], 0, wb_index);
    }
  }
}

void WBSetupFireAnim(object *obj, otype_wb_info *static_wb, int wb_index) {
  dynamic_wb_info *p_dwb = &obj->dynamic_wb[wb_index];

  p_dwb->wb_anim_mask = p_dwb->cur_firing_mask;

  if (static_wb->anim_start_frame != static_wb->anim_end_frame) {
    p_dwb->flags |= DWBF_ANIMATING;
    p_dwb->wb_anim_frame = static_wb->anim_start_frame[p_dwb->cur_firing_mask];
  }

  if (static_wb->anim_start_frame[p_dwb->cur_firing_mask] == static_wb->anim_fire_frame[p_dwb->cur_firing_mask]) {
    WBFireBattery(obj, static_wb, wb_index);
    p_dwb->flags |= DWBF_ANIM_FIRED;
  }
}

void WBFireAnimFrame(object *obj, otype_wb_info *static_wb, int wb_index) {
  dynamic_wb_info *p_dwb = &obj->dynamic_wb[wb_index];
  const int cur_mask = p_dwb->wb_anim_mask;

  p_dwb->wb_anim_frame += Frametime * ((static_wb->anim_end_frame[cur_mask] - static_wb->anim_start_frame[cur_mask]) /
                                       static_wb->anim_time[cur_mask]);

  if ((p_dwb->flags & DWBF_ANIM_FIRED) == 0) {
    if (p_dwb->wb_anim_frame >= static_wb->anim_fire_frame[cur_mask]) {
      WBFireBattery(obj, static_wb, wb_index);
      p_dwb->flags |= DWBF_ANIM_FIRED;
    }
  }

  if (p_dwb->wb_anim_frame >= static_wb->anim_end_frame[cur_mask]) {
    p_dwb->wb_anim_frame = 0.0;
    p_dwb->flags &= ~(DWBF_ANIM_FIRED | DWBF_ANIMATING);
  }
}

bool WBIsBatteryReady(object *obj, otype_wb_info *static_wb, int wb_index) {
  dynamic_wb_info *p_dwb = &obj->dynamic_wb[wb_index];
  float scalar = 1.0;
  float quad_time = 0.0f;

  if (obj->type == OBJ_PLAYER)
    scalar = Players[obj->id].weapon_recharge_scalar;

  if (p_dwb->flags & DWBF_QUAD) {
    // Add 25% on the firing time of quaded weapons
    quad_time = static_wb->gp_fire_wait[p_dwb->cur_firing_mask] * 0.25f;
  }

  if (!(p_dwb->flags & DWBF_ANIMATING) &&
      (p_dwb->last_fire_time + (static_wb->gp_fire_wait[p_dwb->cur_firing_mask] * scalar) + quad_time) < Gametime) {
    return true;
  }

  return false;
}

#include "stringtable.h"

// Allows for multiple configurations of a single wb
void WBFireBattery(object *obj, otype_wb_info *static_wb, int poly_wb_index, int dynamic_wb_index,
                   float damage_scalar) {
  int cur_m_bit;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  vector ave_pos;
  int num_fired = 0;
  vm_MakeZero(&ave_pos);
  pos_state cur_pos;
  dynamic_wb_info *p_dwb = &obj->dynamic_wb[dynamic_wb_index];
  int weapon_obj;
  int must_send = 0;
  int first = 1;
  int saved_weapon_id = 0;

  uint8_t fire_mask;

  if (p_dwb->flags & DWBF_QUAD)
    fire_mask = static_wb->gp_quad_fire_mask;
  else
    fire_mask = static_wb->gp_fire_masks[p_dwb->cur_firing_mask];

  for (cur_m_bit = 0; cur_m_bit < pm->poly_wb[poly_wb_index].num_gps; cur_m_bit++) {
    if (fire_mask & (0x01 << cur_m_bit)) {
      saved_weapon_id = static_wb->gp_weapon_index[cur_m_bit];
      weapon_obj = FireWeaponFromObject(
          obj, static_wb->gp_weapon_index[cur_m_bit], pm->poly_wb[poly_wb_index].gp_index[cur_m_bit],
          (static_wb->flags & WBF_FIRE_FVEC) != 0, (static_wb->flags & WBF_FIRE_TARGET) != 0);

      if (first) {
        first = 0;
        if (obj->type == OBJ_PLAYER && obj->id == Player_num &&
            Weapons[static_wb->gp_weapon_index[cur_m_bit]].recoil_force > 0) {
          vector force_vec = obj->orient.fvec * -Weapons[static_wb->gp_weapon_index[cur_m_bit]].recoil_force;
          phys_apply_force(obj, &force_vec);
        }
      }

      if (weapon_obj >= 0) {
        ave_pos += Objects[weapon_obj].pos;
        Objects[weapon_obj].ctype.laser_info.multiplier = damage_scalar;
        num_fired++;

        // If this is a permissable game, accelerate this object for one frame by the client ping time
        if ((Game_mode & GM_MULTI) && Netgame.local_role == LR_CLIENT && (Netgame.flags & NF_PERMISSABLE))
          Objects[weapon_obj].flags |= OF_PING_ACCELERATE;

        if (Weapons[Objects[weapon_obj].id].flags & WF_COUNTERMEASURE)
          must_send = 1;
      }
    }
  }

  if (num_fired) {
    ave_pos /= num_fired;

    cur_pos.roomnum = obj->roomnum;
    cur_pos.position = &ave_pos;
    cur_pos.orient = &obj->orient; // chrishack -- incorrect for directional sounds
                                   // chrishack -- actually we only need an fvec (direction of fire -- NOT OBJECT)

    if (Game_mode & GM_MULTI) {
      if (Netgame.local_role == LR_SERVER) {
        if (obj->control_type == CT_AI) {
          // Stuff the sound
          MultiSendRobotFireSound(static_wb->fm_fire_sound_index[p_dwb->cur_firing_mask], OBJNUM(obj));
        }
      }
    }
    if (Demo_flags == DF_RECORDING) {
      DemoWrite3DSound(static_wb->fm_fire_sound_index[p_dwb->cur_firing_mask], OBJNUM(obj), SND_PRIORITY_HIGHEST);
    }
    if (obj == Viewer_object)
      Sound_system.Play3dSound(static_wb->fm_fire_sound_index[p_dwb->cur_firing_mask], SND_PRIORITY_HIGHEST, &cur_pos,
                               MAX_GAME_VOLUME, SIF_NO_3D_EFFECTS);
    else
      Sound_system.Play3dSound(static_wb->fm_fire_sound_index[p_dwb->cur_firing_mask], SND_PRIORITY_HIGHEST, &cur_pos);

    if (obj->type == OBJ_PLAYER) {
      ain_hear hear;
      hear.f_directly_player = true;
      hear.hostile_level = 1.0f;
      hear.curiosity_level = 0.0f;
      hear.max_dist = Sounds[static_wb->fm_fire_sound_index[p_dwb->cur_firing_mask]].max_distance;
      AINotify(obj, AIN_HEAR_NOISE, (void *)&hear);
    }
  }

  if ((static_wb->flags & WBF_GUIDED) && obj->type == OBJ_PLAYER) {
    ASSERT(num_fired <= 1); // Only one guided can be fired at a time
    if (num_fired > 0) {
      if (Players[obj->id].guided_obj != NULL) // if there already is a guided, release it
      {
        ReleaseGuidedMissile(obj->id);
      }

      Players[obj->id].guided_obj = &Objects[weapon_obj];
      Objects[weapon_obj].mtype.phys_info.flags |= (PF_HOMING | PF_GUIDED);

      // draw guided view in small window
      if (!Game_toggles.guided_mainview && obj->id == Player_num) {
        int window = (Missile_camera_window < 0) ? SVW_LEFT : Missile_camera_window;
        CreateSmallView(window, Objects[weapon_obj].handle, SVF_POPUP + SVF_BIGGER + SVF_CROSSHAIRS, 0.0,
                        D3_DEFAULT_ZOOM, -1, TXT_HUD_GUIDED);
      }
    }
  }

  if ((static_wb->flags & WBF_USER_TIMEOUT) && obj->type == OBJ_PLAYER) {
    ASSERT(num_fired <= 1); // Only one guided can be fired at a time
    if (num_fired > 0) {
      if (Players[obj->id].user_timeout_obj != NULL) // if there already is a guided, release it
      {
        ReleaseUserTimeoutMissile(obj->id);
      }

      Players[obj->id].user_timeout_obj = &Objects[weapon_obj];
    }
  }

  if (num_fired >= 1 && obj->type == OBJ_PLAYER && obj->id == Player_num && (Game_mode & GM_MULTI) &&
      !(Netgame.flags & NF_PERMISSABLE)) {
    ship *ship = &Ships[Players[obj->id].ship_index];
    otype_wb_info *wb = &ship->static_wb[dynamic_wb_index];
    int on_off_weapon = (wb->flags & WBF_ON_OFF);

    if (!on_off_weapon) // Normal projectile weapon
    {
      MultiSendFirePlayerWB(Player_num, dynamic_wb_index, p_dwb->cur_firing_mask, must_send, damage_scalar);
    }
  }

  // Don't do any of this if its the local client and a permissable netgame
  if (!((Game_mode & GM_MULTI) && obj->type == OBJ_PLAYER && obj->id == Player_num && Netgame.flags & NF_PERMISSABLE)) {
    p_dwb->last_fire_time = Gametime;

    if (num_fired >= 1 && obj->type == OBJ_PLAYER) {
      Players[obj->id].last_fire_weapon_time = Gametime;
    }

    if (static_wb->flags & WBF_RANDOM_FIRE_ORDER) {
      p_dwb->cur_firing_mask = ((float)ps_rand() / (float)D3_RAND_MAX) * static_wb->num_masks;
    } else {
      p_dwb->cur_firing_mask++;
    }

    if (p_dwb->cur_firing_mask >= static_wb->num_masks)
      p_dwb->cur_firing_mask = 0;
  }

  if (obj->ai_info) {
    for (cur_m_bit = 0; cur_m_bit < pm->poly_wb[poly_wb_index].num_gps; cur_m_bit++) {
      if (static_wb->gp_fire_masks[p_dwb->cur_firing_mask] & (0x01 << cur_m_bit)) {
        int weapon_id = static_wb->gp_weapon_index[cur_m_bit];

        if (Weapons[weapon_id].phys_info.flags & PF_FIXED_VELOCITY)
          obj->ai_info->weapon_speed = Weapons[weapon_id].phys_info.velocity.z;
        else if (Weapons[weapon_id].phys_info.flags & PF_USES_THRUST)
          obj->ai_info->weapon_speed = Weapons[weapon_id].phys_info.full_thrust / Weapons[weapon_id].phys_info.drag;
        else
          obj->ai_info->weapon_speed = 0.0;
        break;
      }
    }
  }

  // RType Code...
  if (!((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
    if (obj->type == OBJ_PLAYER && obj->id >= 0) {
      object *bobj = ObjGet(Buddy_handle[obj->id]);
      if (bobj && bobj->type == OBJ_ROBOT && (bobj->ai_info->flags & AIF_GB_MIMIC_PLAYER_FIRING_HACK)) {
        if (dynamic_wb_index != OMEGA_INDEX && dynamic_wb_index != NAPALM_INDEX && dynamic_wb_index < 10) {
          FireWeaponFromObject(bobj, saved_weapon_id, 0, true, false);
        }
      }
    }
  }
}

void WBFireBattery(object *obj, otype_wb_info *static_wb, int wb_index) {
  WBFireBattery(obj, static_wb, wb_index, wb_index);
}

void WBClearInfo(object *obj) {
  int i, j;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  int num_wbs = pm->num_wbs;

  if (obj->type == OBJ_PLAYER)
    num_wbs = MAX_WBS_PER_OBJ;

  for (i = 0; i < num_wbs; i++) {
    obj->dynamic_wb[i].last_fire_time = -1.0f;
    obj->dynamic_wb[i].cur_firing_mask = 0;

    for (j = 0; j < MAX_WB_TURRETS; j++) {
      obj->dynamic_wb[i].norm_turret_angle[j] = 0.0f;
      obj->dynamic_wb[i].turret_direction[j] = WB_MOVE_STILL;
      obj->dynamic_wb[i].turret_next_think_time[j] = 0.0f;
    }

    obj->dynamic_wb[i].wb_anim_mask = 0;
    obj->dynamic_wb[i].wb_anim_frame = 0.0f;

    vm_MakeZero(&obj->dynamic_wb[i].cur_target);

    obj->dynamic_wb[i].flags = DWBF_ENABLED | DWBF_AUTOMATIC;
  }
}

void WBClearInfo(otype_wb_info static_wb[]) {
  int i;
  int j;

  if (static_wb == NULL)
    return;

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    static_wb[i].aiming_gp_index = 0;
    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      static_wb[i].gp_weapon_index[j] = LASER_INDEX;
    }

    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      static_wb[i].fm_fire_sound_index[j] = SOUND_NONE_INDEX;
      static_wb[i].anim_start_frame[j] = 0.0;
      static_wb[i].anim_fire_frame[j] = 0.0;
      static_wb[i].anim_end_frame[j] = 0.0;
      static_wb[i].anim_time[j] = 0.0;
    }

    static_wb[i].num_masks = 1;

    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      static_wb[i].gp_fire_masks[j] = 0;
      static_wb[i].gp_fire_wait[j] = 1.0f;
    }
    // Makes sure a robot with a weapon bank can fire it even if the artist forget to set the weapon info for
    // this robot
    static_wb[i].gp_fire_masks[0] = 1;

    static_wb[i].flags = 0;
    static_wb[i].aiming_flags = 0;
    static_wb[i].aiming_3d_dot = 0.9f;
    static_wb[i].aiming_3d_dist = 1000.0f;
    static_wb[i].aiming_XZ_dot = 0.9f;
  }
}

// If the wb_index is negative, all wbs are enabled/disabled
void WBEnable(object *obj, int wb_index, bool f_enable) {
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  int i;

  if (wb_index < 0) {
    for (i = 0; i < pm->num_wbs; i++) {
      WBEnable(obj, i, f_enable);
    }
  } else {
    if ((obj->type != OBJ_PLAYER && wb_index < pm->num_wbs) || (obj->type == OBJ_PLAYER)) {
      if (f_enable)
        obj->dynamic_wb[wb_index].flags |= DWBF_ENABLED;
      else
        obj->dynamic_wb[wb_index].flags &= ~DWBF_ENABLED;
    }
  }
}
