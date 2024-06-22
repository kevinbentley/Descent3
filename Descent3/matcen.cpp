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

 * $Logfile: /DescentIII/main/matcen.cpp $
 * $Revision: 71 $
 * $Date: 4/19/00 5:35p $
 * $Author: Matt $
 *
 * Matcen code
 *
 * $Log: /DescentIII/main/matcen.cpp $
 *
 * 71    4/19/00 5:35p Matt
 * From Duane for 1.4
 * Added include
 *
 * 70    3/20/00 12:14p Matt
 * Merge of Duane's post-1.3 changes.
 * Check for bad array index.  This change duplicates Jason's fix of the
 * same bug, but Duane's code looks a little more thorough.
 *
 * 69    1/24/00 11:49p Jason
 * Fixed array indexing error with matcens
 *
 * 68    10/21/99 4:50p Matt
 * Mac merge
 *
 * 67    8/15/99 12:22p Gwar
 * more matcen support in NEWEDITOR (almost done)
 *
 * 66    8/12/99 7:55p Gwar
 * fixed a compiler warning
 *
 * 65    8/11/99 9:15p Gwar
 * matcen support for NEWEDITOR
 *
 * 64    7/28/99 4:05p Kevin
 * Mac
 *
 * 63    5/19/99 3:24p Jason
 * fixed wrong ordering of InitObjectScripts and MultiSendObject
 *
 * 62    5/10/99 10:22p Ardussi
 * changes to compile on Mac
 *
 * 61    5/09/99 1:15a Jason
 * got rid of weird post production effect
 *
 * 60    5/05/99 4:51p Jason
 * don't tile matcens so much
 *
 * 59    5/04/99 8:51p Chris
 * Fixed homing missile problem (a PTMC matcen created robot would have a
 * parent of a non-AI object).  Homers use the ultimate parent.  Fun bug.
 * :)
 *
 * 58    5/03/99 1:15p Jason
 * fixed matcen procedural effect
 *
 * 57    5/02/99 10:26p Matt
 * Fixed silly little bug
 *
 * 56    5/02/99 7:30p Jason
 * added "none" type procedural creation effect
 *
 * 55    5/02/99 6:55p Jeff
 * fixed bug where a sound based off an object would not play because the
 * object wasn't created yet (Jason)
 *
 * 54    4/29/99 4:50p Chris
 * Fixed matcen and Osiris created objects so thier ambient sounds play
 *
 * 53    4/25/99 3:16p Chris
 * Fixed a coop bug with matcen functioning on the server
 *
 * 52    4/23/99 11:28a Jason
 * fixed matcen viseffect problem
 *
 * 51    4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 50    4/19/99 3:45a Jeff
 * fixed min/max problem
 *
 * 49    4/18/99 10:55p Chris
 * matcens now have defualts sounds
 *
 * 48    4/14/99 2:51a Jeff
 * fixed some case mismatched #includes
 *
 * 47    4/12/99 6:15p Samir
 * Sound priorities pass 1
 *
 * 46    4/02/99 3:58p Jason
 * sped up vis effect stuff
 *
 * 45    3/22/99 11:24a Chris
 * Matcen generates an osiris call even if no object is produced
 *
 * 44    3/05/99 9:57a Chris
 * Fixed bugs with walkers
 *
 * 43    3/04/99 3:24p Chris
 * FIxed matcens and walkers
 *
 * 42    2/24/99 10:58a Dan
 * CHRIS - Fixed the external room matcen problem
 *
 * 41    2/19/99 4:49p Dan
 * Matcens *should* be able to be placed on external rooms
 *
 * 40    2/19/99 4:41p Dan
 * External rooms can now be matcens...  (Objects are created in the
 * connection room)
 *
 * 39    2/13/99 4:24p Chris
 * Fixed an off by one bug in num_prod_type
 *
 * 38    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 37    2/09/99 1:23p Matt
 * Added object-generated notification event
 *
 */

#ifdef NEWEDITOR
#include "globals.h"
#endif

#include "matcen.h"
#include "game.h"
#include "sounds.h"
#include "ssl_lib.h"
#include "string.h"
#include "soundload.h"
#include "room.h"
#include "object.h"
#include "objinfo.h"
#include "findintersection.h"
#ifndef NEWEDITOR
#include "multi.h"
#endif
#include <stdlib.h>
#include "fireball.h"
#include "weapon.h"
#include "polymodel.h"
#include "hlsoundlib.h"
#include "viseffect.h"
#include "viseffect_external.h"
#include "damage.h"
#include "physics.h"
#include "mem.h"
#include "ObjScript.h"
#ifndef NEWEDITOR
#include "player.h"
#include "osiris_dll.h"
#endif
#include "psrand.h"
#include "demofile.h"


#include <algorithm>

// Beginning of the real file
#define LEVEL_DATA_MATCEN_VERSION 1
#define GAME_DATA_MATCEN_VERSION 1

#if (defined(EDITOR) || defined(NEWEDITOR))

char *MatcenEffectStrings[NUM_MATCEN_EFFECTS] = {"Line lightning", "Line sinewave", "Procedural lightning", "None"};

#endif

int Num_matcens = 0;
matcen *Matcen[MAX_MATCENS];
bool Matcen_created = false;

matcen::matcen() {
  int i;

  m_prod_mode = MMODE_NOTPROD;
  m_cur_saturation_count = 0;

  m_num_prod_types = 0;
  m_control_type = MPC_SCRIPT;
  m_type = MT_UNASSIGNED;
  m_creation_effect = MEFFECT_LINE_LIGHTNING;

  // Get lightning handle in case we need it
  m_creation_texture = FindTextureName("Matcen Lightning");
  if (m_creation_texture == -1)
    m_creation_texture = 0;

  m_num_spawn_pnts = 0;

  m_roomnum = MATCEN_ERROR;

  for (i = 0; i < MAX_SPAWN_PNTS; i++) {
    m_spawn_pnt[i] = MATCEN_ERROR;
  }

  m_max_prod = 0;

  for (i = 0; i < MAX_PROD_TYPES; i++) {
    m_prod_type[i] = MATCEN_ERROR;
    m_prod_time[i] = 1.0f;
    m_prod_priority[i] = 100;
    m_max_prod_type[i] = 3;
  }

  m_sounds[MATCEN_ACTIVE_SOUND] = FindSoundName("AmbMatCenRun");
  m_sounds[MATCEN_DISABLE_SOUND] = -1;
  m_sounds[MATCEN_PROD_SOUND] = FindSoundName("AmbMatCenProduce");

  m_speed_multi = 1.0f;

  m_max_alive_children = -1;
  m_num_alive = 0;
  m_alive_list = NULL;

  m_preprod_time = 1.5f;
  m_postprod_time = 1.0f;

  m_status = 0;

  m_create_pnt = Zero_vector;
  m_create_room = MATCEN_ERROR;

  m_cached_prod_index = -1;
  m_cached_prod_time = 0.0f;

  Reset();
}

matcen::~matcen() {
  if (m_alive_list) {
    mem_free(m_alive_list);
  }
}

bool matcen::SetMaxProd(int max_p) {
  if (max_p < -1) {
    return false;
  }

  m_max_prod = max_p;

  ComputeNextProdInfo();

  return true;
}

int matcen::GetMaxProd() { return m_max_prod; }

#ifndef NEWEDITOR

bool matcen::StartObjProd() {
  if (m_cached_prod_index < 0 || m_max_prod_type[m_cached_prod_index] >= m_num_prod_type[m_cached_prod_index])
    ComputeNextProdInfo();

  if (m_status & (MSTAT_DONE_PROD | MSTAT_ACTIVE_PAUSE | MSTAT_DISABLED))
    return false;

  if (m_prod_mode != MMODE_NOTPROD)
    return false;

  if (!(m_status & (MSTAT_ACTIVE)))
    return false;

  if (m_max_prod <= m_num_prod && m_max_prod != -1) {
    mprintf(0, "MATCEN: Done\n");
    m_status |= MSTAT_DONE_PROD;
    return false;
  }

  if (m_cached_prod_index < 0)
    return false;

  // Guarentees against designer error
  pos_state pos;
  matrix idmat = Identity_matrix;

  int croom = m_create_room;
  if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
    croom = GetTerrainRoomFromPos(&m_create_pnt);
  }

  pos.position = &m_create_pnt;
  pos.orient = &idmat;
  pos.roomnum = croom;

  Sound_system.StopSoundLooping(Sound_system.Play3dSound(m_sounds[MATCEN_PROD_SOUND], SND_PRIORITY_HIGH, &pos));

  m_status &= ~MSTAT_NEVER_PROD;

  m_prod_mode_time = 0.0f;
  m_prod_mode = MMODE_PREPROD;
  m_cur_saturation_count = 0;

  return true;
}

bool matcen::DoObjProd() {
  int objnum;
  int p_handle = OBJECT_HANDLE_NONE;
  bool script_initted = false;

  ASSERT(m_prod_mode == MMODE_PREPROD);
  ASSERT(m_type == MT_ROOM || m_type == MT_OBJECT);

  if (m_type == MT_OBJECT) {
    object *parent = ObjGet(m_objref);
    ASSERT(parent);

    if (parent->control_type == CT_AI || parent->type == OBJ_PLAYER) {
      p_handle = parent->handle;
    }
  }

  ComputeCreatePnt();
  matrix orient;
  vector fvec = Player_object->pos - m_create_pnt;
  vm_NormalizeVector(&fvec);

  vm_VectorToMatrix(&orient, &fvec, NULL, NULL);

  if (m_prod_type[m_cached_prod_index] >= 0) {
    int croom = m_create_room;
    Matcen_created = true;

    if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
      croom = GetTerrainRoomFromPos(&m_create_pnt);
    }

    objnum = ObjCreate(Object_info[m_prod_type[m_cached_prod_index]].type, m_prod_type[m_cached_prod_index], croom,
                       &m_create_pnt, &orient, p_handle);
    Matcen_created = false;

    if (objnum >= 0 && (Object_info[m_prod_type[m_cached_prod_index]].flags & OIF_CONTROL_AI) &&
        (Object_info[m_prod_type[m_cached_prod_index]].ai_info->movement_type != MC_FLYING)) {
      vector gp;
      object *obj = &Objects[objnum];

      if (PhysCalcGround(&gp, NULL, obj, 0)) {
        fvi_info hit_info;
        fvi_query fq;
        int fate;
        vector start = obj->pos;
        vector end = obj->pos - 2000.0f * obj->orient.uvec;

        fq.p0 = &start;
        fq.p1 = &end;
        fq.startroom = obj->roomnum;

        fq.rad = 0.0f;
        fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS;
        fq.thisobjnum = OBJNUM(obj);
        fq.ignore_obj_list = NULL;

        fate = fvi_FindIntersection(&fq, &hit_info);

        if (fate != HIT_NONE) {
          float ps;
          float pr;
          float diff;

          ps = (gp - obj->pos) * obj->orient.uvec;
          pr = (hit_info.hit_pnt - obj->pos) * obj->orient.uvec;

          if (ps != pr) {
            diff = ps - pr;
            obj->pos -= diff * obj->orient.uvec;
            ObjSetPos(obj, &obj->pos, obj->roomnum, NULL, false);
            obj->flags |= OF_MOVED_THIS_FRAME;

            m_create_pnt = obj->pos;
          }
        }
      }
    }

    if (objnum >= 0) {
      // Make it fade in for a second
      Objects[objnum].effect_info->type_flags |= EF_FADING_IN;
      Objects[objnum].effect_info->fade_time = 1.0;
      Objects[objnum].effect_info->fade_max_time = 1.0;

      object *obj = &Objects[objnum];

      if (Game_mode & GM_MULTI) {
        // ASSERT (Netgame.local_role==LR_SERVER);
        if (Netgame.local_role == LR_SERVER) {
          MultiSendObject(&Objects[objnum], 0);
        }
      }

      InitObjectScripts(obj);
      script_initted = true;

      if (IS_GENERIC(obj->type)) {
        int ambient_sound = Object_info[obj->id].sounds[GSI_AMBIENT];
        if (ambient_sound != SOUND_NONE_INDEX) {
          Sound_system.Play3dSound(ambient_sound, SND_PRIORITY_LOWEST, obj);
          if (Game_mode & GM_MULTI)
            MultiPlay3dSound(ambient_sound, objnum, SND_PRIORITY_LOW);
          if (Demo_flags == DF_RECORDING)
            DemoWrite3DSound(ambient_sound, objnum, SND_PRIORITY_LOW);
        }
      }
    }
  } else {
    objnum = -1;
  }

  // Send notification event
  tOSIRISEventInfo ei;
  if (objnum >= 0)
    ei.evt_matcen_create.it_handle = Objects[objnum].handle;
  else
    ei.evt_matcen_create.it_handle = OBJECT_HANDLE_NONE;
  ei.evt_matcen_create.id = FindMatcenIndex(m_name);
  Osiris_CallLevelEvent(EVT_MATCEN_CREATE, &ei);

  if (objnum >= 0) {
    if (!script_initted)
      InitObjectScripts(&Objects[objnum]);
    AddToAliveList(Objects[objnum].handle);

    m_last_prod_objref = Objects[objnum].handle;
  } else {
    m_last_prod_objref = OBJECT_HANDLE_NONE;
  }

  m_status |= MSTAT_CREATE_OBJ_FRAME;

  m_last_prod_type_index = m_cached_prod_index;
  m_num_prod_type[m_cached_prod_index]++;
  m_num_prod++;

  m_prod_mode_time = 0.0f;
  m_prod_mode = MMODE_POSTPROD;
  m_cur_saturation_count = 0;

  return true;
}

bool matcen::DoAliveListFrame() {
  int i, j;

  for (i = 0; i < m_num_alive; i++) {
    if (!ObjGet(m_alive_list[i])) {
      for (j = i; j < m_num_alive - 1; j++) {
        m_alive_list[j] = m_alive_list[j + 1];
      }

      m_num_alive--;
      i--; // Example - 6 is now 5 (after 5 was deleted); so we need to check 5 again...
    }
  }

  return true;
}

bool matcen::AddToAliveList(int objref) {
  if (m_max_alive_children > 0 && m_max_alive_children > m_num_alive) {
    m_alive_list[m_num_alive++] = objref;
  }

  return false;
}

bool matcen::FinishObjProd() {
  ASSERT(m_prod_mode == MMODE_POSTPROD);

  m_prod_mode_time = 0.0f;
  m_prod_mode = MMODE_NOTPROD;
  m_cur_saturation_count = 0;

  ComputeNextProdInfo();

  return false;
}

#endif // NEWEDITOR

bool matcen::SetAttach(int attach) {
  m_roomnum = attach;
  ComputeCreatePnt();

  return true;
}

int matcen::GetAttach() { return m_roomnum; }

char matcen::GetAttachType() { return m_type; }

bool matcen::SetAttachType(char type) {
  if (type == MT_OBJECT || type == MT_ROOM || type == MT_UNASSIGNED) {
    m_type = type;
    return true;
  }

  return false;
}

char matcen::GetControlType() { return m_control_type; }

bool matcen::SetControlType(char type) {
  if (type >= 0 && type < MAX_MATCEN_CONTROL_TYPES) {
    m_control_type = type;
    return true;
  }

  return false;
}

char matcen::GetNumSpawnPnts() { return m_num_spawn_pnts; }

bool matcen::SetNumSpawnPnts(char num_s) {
  if (num_s >= 0 && num_s <= MAX_SPAWN_PNTS) {
    m_num_spawn_pnts = num_s;
    ComputeCreatePnt();
    return true;
  }

  return false;
}

bool matcen::ComputeCreatePnt() {
  if (m_status & MSTAT_MANUAL_UPDATE_CREATE_PNT) {
    return true;
  } else if (m_type != MT_UNASSIGNED) {
    float spawn_dist;

    if (m_cached_prod_index >= 0 && m_cached_prod_index < m_num_prod_types && m_prod_type[m_cached_prod_index] >= 0 &&
        m_prod_type[m_cached_prod_index] <= MAX_OBJECT_TYPES &&
        Object_info[m_prod_type[m_cached_prod_index]].type != OBJ_NONE) {
      spawn_dist = Object_info[m_prod_type[m_cached_prod_index]].size + 1.0f;
    } else {
      spawn_dist = 8.0f;
    }

    if (m_type == MT_ROOM) {
      bool f_computed = false;

      if (!(m_roomnum >= 0 && m_roomnum <= Highest_room_index && Rooms[m_roomnum].used))
        goto error;

      if (m_num_spawn_pnts) {
        int i;
        int num_valid_faces = 0;
        room *rp = &Rooms[m_roomnum];

        m_create_pnt = Zero_vector;

        for (i = 0; i < m_num_spawn_pnts; i++) {
          if (m_spawn_pnt[i] >= 0 && m_spawn_pnt[i] < rp->num_faces) {
            face *fp = &rp->faces[m_spawn_pnt[i]];
            int y;

            m_spawn_vec[num_valid_faces].x = m_spawn_vec[num_valid_faces].y = m_spawn_vec[num_valid_faces].z = 0;

            for (y = 0; y < fp->num_verts; y++)
              m_spawn_vec[num_valid_faces] += rp->verts[fp->face_verts[y]];

            m_spawn_vec[num_valid_faces] /= fp->num_verts;
            m_create_pnt += m_spawn_vec[num_valid_faces];

            m_spawn_normal[num_valid_faces] = fp->normal;

            num_valid_faces++;
          }
        }

        if (num_valid_faces) {
          m_create_pnt /= num_valid_faces;

          for (i = 0; i < num_valid_faces; i++) {
            // Compute the vector to the m_create_pnt
            vector to_dist = m_create_pnt - m_spawn_vec[i];
            float dot = m_spawn_normal[i] * to_dist;

            if (dot < spawn_dist) {
              float add_dist = spawn_dist - dot;
              m_create_pnt += (add_dist * m_spawn_normal[i]);
            }
          }

          f_computed = true;
        }
      }

      if (!f_computed) {
        m_create_pnt = Rooms[m_roomnum].path_pnt;
      }

      m_create_room = m_roomnum;
    } else {
      ASSERT(m_type == MT_OBJECT);
      object *master_obj = ObjGet(m_objref);
      bool f_computed = false;

      if (!master_obj)
        goto error;

      if (m_num_spawn_pnts) {
        int i;
        int num_valid_gps = 0;

        m_create_pnt = Zero_vector;

        for (i = 0; i < m_num_spawn_pnts; i++) {
          if (WeaponCalcGun(&m_spawn_vec[num_valid_gps], &m_spawn_normal[num_valid_gps], master_obj, m_spawn_pnt[i])) {
            m_create_pnt += m_spawn_vec[num_valid_gps];
            num_valid_gps++;
          }
        }

        if (num_valid_gps) {
          m_create_pnt /= num_valid_gps;

          for (i = 0; i < num_valid_gps; i++) {
            // Compute the vector to the m_create_pnt
            vector to_dist = m_create_pnt - m_spawn_vec[i];
            float dot = m_spawn_normal[i] * to_dist;

            if (dot < spawn_dist) {
              float add_dist = spawn_dist - dot;
              m_create_pnt += (add_dist * m_spawn_normal[i]);
            }
          }

          f_computed = true;
        }
      }

      if (!f_computed) {
        m_create_pnt = master_obj->pos;
      }

      // Determine the correct creation room
      fvi_query fq;
      fvi_info hit_info;

      fq.p0 = &master_obj->pos;
      fq.startroom = master_obj->roomnum;
      fq.p1 = &m_create_pnt;
      fq.rad = 0.0f;
      fq.thisobjnum = -1;
      fq.ignore_obj_list = NULL;
      fq.flags = FQ_IGNORE_WALLS;

      fvi_FindIntersection(&fq, &hit_info);
      m_create_room = hit_info.hit_room;
    }
  }

error:
  return false;
}

bool matcen::GetCreatePnt(vector *pnt) {
  ComputeCreatePnt();
  *pnt = m_create_pnt;
  return true;
}

bool matcen::SetCreatePnt(vector *pnt) {
  if (m_status & MSTAT_MANUAL_UPDATE_CREATE_PNT) {
    m_create_pnt = *pnt;
    return true;
  }

  return false;
}

int matcen::GetCreateRoom() {
  ComputeCreatePnt();

  return m_create_room;
}

bool matcen::SetCreateRoom(int room) {
  if ((m_status & MSTAT_MANUAL_UPDATE_CREATE_PNT)) // chrishack -- add room validation
  {
    m_create_room = room;
    return true;
  }

  return false;
}

int matcen::GetSpawnPnt(char s_index) {
  if (s_index >= 0 && s_index < MAX_SPAWN_PNTS)
    return m_spawn_pnt[s_index];

  return MATCEN_ERROR;
}

bool matcen::SetSpawnPnt(char s_index, int s_value) {
  if (s_index >= 0 && s_index < MAX_SPAWN_PNTS) {
    m_spawn_pnt[s_index] = s_value;
    ComputeCreatePnt();
    return true;
  }

  return false;
}

bool matcen::SetName(const char *name) {
  strcpy(m_name, name);

  return true;
}

void matcen::GetName(char *name) { strcpy(name, m_name); }

void matcen::SaveData(CFILE *fp) {
  int i, j;
  int len;

  cf_WriteInt(fp, MATCEN_LOADSAVE_VERSION);

  cf_WriteShort(fp, MAX_SPAWN_PNTS);
  cf_WriteShort(fp, MAX_PROD_TYPES);
  cf_WriteShort(fp, MAX_MATCEN_SOUNDS);

  len = strlen(m_name) + 1; // Accounts for NULL charactor
  cf_WriteShort(fp, len);
  for (i = 0; i < len; i++) {
    cf_WriteByte(fp, m_name[i]);
  }

  cf_WriteByte(fp, m_num_prod_types);
  cf_WriteByte(fp, m_control_type);
  cf_WriteByte(fp, m_type);
  cf_WriteByte(fp, m_creation_effect);
  cf_WriteShort(fp, m_creation_texture);

  cf_WriteInt(fp, m_num_spawn_pnts);

  cf_WriteInt(fp, m_roomnum);

  cf_WriteFloat(fp, m_create_pnt.x);
  cf_WriteFloat(fp, m_create_pnt.y);
  cf_WriteFloat(fp, m_create_pnt.z);

  cf_WriteInt(fp, m_create_room);

  for (i = 0; i < MAX_SPAWN_PNTS; i++) {
    cf_WriteInt(fp, m_spawn_pnt[i]);

    cf_WriteFloat(fp, m_spawn_vec[i].x);
    cf_WriteFloat(fp, m_spawn_vec[i].y);
    cf_WriteFloat(fp, m_spawn_vec[i].x);

    cf_WriteFloat(fp, m_spawn_normal[i].x);
    cf_WriteFloat(fp, m_spawn_normal[i].y);
    cf_WriteFloat(fp, m_spawn_normal[i].x);
  }

  cf_WriteInt(fp, m_max_prod);

  for (i = 0; i < MAX_PROD_TYPES; i++) {
    int type = m_prod_type[i];

    if (type >= 0) {
      len = strlen(Object_info[type].name) + 1; // Accounts for NULL charactor
      cf_WriteShort(fp, len);
      for (j = 0; j < len; j++) {
        cf_WriteByte(fp, Object_info[type].name[j]);
      }
    } else {
      cf_WriteShort(fp, 1);
      cf_WriteByte(fp, '\0');
    }

    cf_WriteFloat(fp, m_prod_time[i]);
    cf_WriteInt(fp, m_prod_priority[i]);
    cf_WriteInt(fp, m_max_prod_type[i]);
  }

  cf_WriteShort(fp, m_max_alive_children);
  if (m_max_alive_children > 0) {
    cf_WriteShort(fp, m_num_alive);
    for (i = 0; i < m_num_alive; i++) {
      cf_WriteInt(fp, m_alive_list[i]);
    }
  }

  cf_WriteFloat(fp, m_preprod_time);
  cf_WriteFloat(fp, m_postprod_time);

  // Convert these to names
  for (i = 0; i < MAX_MATCEN_SOUNDS; i++) {
    len = strlen(Sounds[m_sounds[i]].name) + 1; // Accounts for NULL charactor
    cf_WriteShort(fp, len);
    for (j = 0; j < len; j++) {
      cf_WriteByte(fp, Sounds[m_sounds[i]].name[j]);
    }
  }

  cf_WriteFloat(fp, m_speed_multi);

  cf_WriteByte(fp, m_prod_mode);
  cf_WriteFloat(fp, m_prod_mode_time);

  cf_WriteInt(fp, m_status);

  cf_WriteInt(fp, m_num_prod);
  cf_WriteInt(fp, m_last_prod_type_index);
  cf_WriteFloat(fp, m_last_prod_finish_time);

  cf_WriteInt(fp, m_cached_prod_index);
  cf_WriteFloat(fp, m_cached_prod_time);

  cf_WriteFloat(fp, m_next_active_check_time);
  cf_WriteByte(fp, m_last_active_check_result);

  cf_WriteInt(fp, m_last_prod_objref);

  for (i = 0; i < MAX_PROD_TYPES; i++) {
    cf_WriteInt(fp, m_num_prod_type[i]);
  }

  cf_WriteInt(fp, m_sound_active_handle);
}

extern int16_t texture_xlate[];
void matcen::LoadData(CFILE *fp) {
  int i, j;
  int len;

  int16_t max_spawn_pnts;
  int16_t max_prod_types;
  int16_t max_matcen_sounds;

  int version = cf_ReadInt(fp);

  max_spawn_pnts = cf_ReadShort(fp);
  ASSERT(max_spawn_pnts <= MAX_SPAWN_PNTS);
  max_prod_types = cf_ReadShort(fp);
  ASSERT(max_prod_types <= MAX_PROD_TYPES);
  max_matcen_sounds = cf_ReadShort(fp);
  ASSERT(max_matcen_sounds <= MAX_MATCEN_SOUNDS);

  len = cf_ReadShort(fp);
  ASSERT(len <= MAX_MATCEN_NAME_LEN);
  for (i = 0; i < len; i++) {
    m_name[i] = cf_ReadByte(fp);
  }

  m_num_prod_types = cf_ReadByte(fp);
  m_control_type = cf_ReadByte(fp);
  m_type = cf_ReadByte(fp);
  m_creation_effect = cf_ReadByte(fp);

  if (version >= 2)
    m_creation_texture = texture_xlate[cf_ReadShort(fp)];

  m_num_spawn_pnts = cf_ReadInt(fp);

  m_roomnum = cf_ReadInt(fp);

  m_create_pnt.x = cf_ReadFloat(fp);
  m_create_pnt.y = cf_ReadFloat(fp);
  m_create_pnt.z = cf_ReadFloat(fp);

  m_create_room = cf_ReadInt(fp);

  for (i = 0; i < max_spawn_pnts; i++) {
    m_spawn_pnt[i] = cf_ReadInt(fp);

    m_spawn_vec[i].x = cf_ReadFloat(fp);
    m_spawn_vec[i].y = cf_ReadFloat(fp);
    m_spawn_vec[i].z = cf_ReadFloat(fp);

    m_spawn_normal[i].x = cf_ReadFloat(fp);
    m_spawn_normal[i].y = cf_ReadFloat(fp);
    m_spawn_normal[i].z = cf_ReadFloat(fp);
  }

  m_max_prod = cf_ReadInt(fp);

  char temp_name[256];
  for (i = 0; i < max_prod_types; i++) {
    len = cf_ReadShort(fp);
    for (j = 0; j < len; j++) {
      {
        temp_name[j] = cf_ReadByte(fp);
      }
    }

    m_prod_type[i] = FindObjectIDName(temp_name);

    m_prod_time[i] = cf_ReadFloat(fp);
    m_prod_priority[i] = cf_ReadInt(fp);
    m_max_prod_type[i] = cf_ReadInt(fp);
  }

  m_max_alive_children = cf_ReadShort(fp);
  if (m_max_alive_children > 0) {
    m_num_alive = cf_ReadShort(fp);
    m_alive_list = (int *)mem_malloc(sizeof(int) * m_max_alive_children);

    for (i = 0; i < m_num_alive; i++) {
      m_alive_list[i] = cf_ReadInt(fp);
    }
  } else {
    m_num_alive = 0;
    m_alive_list = NULL;
  }

  m_preprod_time = cf_ReadFloat(fp);
  m_postprod_time = cf_ReadFloat(fp);

  // Convert these to names
  for (i = 0; i < max_matcen_sounds; i++) {
    char sound_name[256];

    len = cf_ReadShort(fp);
    for (j = 0; j < len; j++) {
      sound_name[j] = cf_ReadByte(fp);
    }

    m_sounds[i] = FindSoundName(sound_name);
  }

  m_speed_multi = cf_ReadFloat(fp);

  m_prod_mode = cf_ReadByte(fp);
  m_prod_mode_time = cf_ReadFloat(fp);

  m_status = cf_ReadInt(fp);

  m_num_prod = cf_ReadInt(fp);
  m_last_prod_type_index = cf_ReadInt(fp);
  m_last_prod_finish_time = cf_ReadFloat(fp);

  m_cached_prod_index = cf_ReadInt(fp);
  m_cached_prod_time = cf_ReadFloat(fp);

  m_next_active_check_time = cf_ReadFloat(fp);
  m_last_active_check_result = (cf_ReadByte(fp) != 0);

  m_last_prod_objref = cf_ReadInt(fp);

  for (i = 0; i < max_prod_types; i++) {
    m_num_prod_type[i] = cf_ReadInt(fp);
  }

  if (version >= 3)
    m_sound_active_handle = cf_ReadInt(fp);
}

char matcen::GetNumProdTypes() { return m_num_prod_types; }

bool matcen::SetNumProdTypes(char num_prod_types) {
  if (num_prod_types >= 0 && num_prod_types <= MAX_PROD_TYPES) {
    if ((m_num_prod_types < num_prod_types || num_prod_types == -1) && (m_status & MSTAT_DONE_PROD)) {
      ComputeNextProdInfo();
    }

    m_num_prod_types = num_prod_types;
    return true;
  }

  return false;
}

bool matcen::GetProdInfo(char index, int *type_id, int *priority, float *time, int *max_prod) {
  if (index >= 0 && index < MAX_PROD_TYPES) {
    if (type_id)
      *type_id = m_prod_type[index];

    if (priority)
      *priority = m_prod_priority[index];

    if (time)
      *time = m_prod_time[index];

    if (max_prod)
      *max_prod = m_max_prod_type[index];

    return true;
  }

  return false;
}

bool matcen::SetProdInfo(char index, int *type_id, int *priority, float *time, int *max_prod) {
  if (index >= 0 && index < MAX_PROD_TYPES) {
    if (type_id && (*type_id >= -1))
      m_prod_type[index] = *type_id;

    if (priority && (*priority >= 0))
      m_prod_priority[index] = *priority;

    if (time && (*time >= 0.0f))
      m_prod_time[index] = *time;

    if (max_prod && (*max_prod >= -1)) {
      if (*max_prod == -1 && m_max_prod_type[index] < *max_prod && (m_status & MSTAT_DONE_PROD)) {
        ComputeNextProdInfo();
      }

      m_max_prod_type[index] = *max_prod;
    }

    return true;
  }

  return false;
}

float matcen::GetProdMultiplier() { return m_speed_multi; }

bool matcen::SetProdMultiplier(float multi) {
  if (multi >= 0.0f) {
    m_speed_multi = multi;
    return true;
  }

  return false;
}

int matcen::GetStatus() { return m_status; }

bool matcen::ComputeNextProdInfo() {
  int i;

  if (m_status & (MSTAT_DISABLED))
    return false;

  m_status &= ~MSTAT_DONE_PROD;

  if (m_max_prod <= m_num_prod && m_max_prod != -1) {
    mprintf(0, "MATCEN: Done\n");
    m_status |= MSTAT_DONE_PROD;
    return false;
  }

  ASSERT(m_prod_mode == MMODE_NOTPROD);

  int cur_index;
  bool f_do = true;

  if (m_status & MSTAT_RANDOM_PROD_ORDER) {
    int total_priorities = 0;

    for (i = 0; i < m_num_prod_types; i++) {
      if ((m_max_prod_type[i] == -1 || m_max_prod_type[i] > m_num_prod_type[i]) && m_prod_type[i] >= -1) {
        total_priorities += m_prod_priority[i];
      }
    }

    if (total_priorities <= 0) {
      f_do = false;
    } else {
      int r_val = ps_rand() % total_priorities;
      bool f_looking = true;

      i = 0;

      do {
        ASSERT(i < m_num_prod_types);

        if ((m_max_prod_type[i] == -1 || m_max_prod_type[i] > m_num_prod_type[i]) && m_prod_type[i] >= -1) {
          r_val -= m_prod_priority[i];

          if (r_val <= 0) {
            cur_index = i;
            f_looking = false;
          }
        }

        i++;
      } while (f_looking);
    }
  } else {
    cur_index = -1;
    int best_priority = -1;

    for (i = 0; i < m_num_prod_types; i++) {
      if ((m_max_prod_type[i] == -1 || m_max_prod_type[i] > m_num_prod_type[i]) && m_prod_type[i] >= -1 &&
          m_prod_priority[i] > best_priority) {
        cur_index = i;
        best_priority = m_prod_priority[i];
      }
    }

    if (cur_index == -1) {
      f_do = false;
    }
  }

  if (f_do) {
    m_cached_prod_index = cur_index;
    m_cached_prod_time = Gametime + m_prod_time[cur_index];

    return true;
  }

  m_cached_prod_index = -1;
  m_status |= MSTAT_DONE_PROD;
  return false;
}

bool matcen::SetStatus(int status, bool f_enable) // Not all flags are settable
{
  status &= ~(MSTAT_DONE_PROD | MSTAT_NEVER_PROD);
  m_last_active_check_result = (m_status & MSTAT_ACTIVE) != 0;

  if (f_enable) {
    bool f_recompute = false;

    if ((m_prod_mode == MMODE_NOTPROD) && (status & MSTAT_ACTIVE) && !(m_status & MSTAT_ACTIVE)) {
      f_recompute = true;
    }

    m_status |= status;

    if (f_recompute) {
      ComputeNextProdInfo();
    }
  } else {
    m_status &= ~status;
  }

#ifdef NEWEDITOR

  ASSERT(!(m_status & MSTAT_ACTIVE));

#else

  bool cur_active = (m_status & MSTAT_ACTIVE) != 0;

  if (cur_active && !m_last_active_check_result) {
    if (m_type == MT_OBJECT) {
      object *obj = ObjGet(m_objref);

      if (obj)
        m_sound_active_handle = Sound_system.Play3dSound(m_sounds[MATCEN_ACTIVE_SOUND], SND_PRIORITY_NORMAL, obj);
    } else {
      pos_state pos;
      matrix idmat = Identity_matrix;

      int croom = m_create_room;
      if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
        croom = GetTerrainRoomFromPos(&m_create_pnt);
      }

      pos.position = &m_create_pnt;
      pos.orient = &idmat;
      pos.roomnum = croom;

      m_sound_active_handle = Sound_system.Play3dSound(m_sounds[MATCEN_ACTIVE_SOUND], SND_PRIORITY_NORMAL, &pos);
    }
  } else if (!cur_active && m_last_active_check_result) {
    Sound_system.StopSoundLooping(m_sound_active_handle);
  }

#endif // NEWEDITOR

  return true;
}

#ifndef NEWEDITOR

void matcen::CheckActivateStatus() {
  m_next_active_check_time = Gametime + MATCEN_ACTIVE_CHECK_RATE +
                             (MATCEN_ACTIVE_CHECK_VARIENCE * (((float)ps_rand()) / ((float)D3_RAND_MAX) - .5f));
  m_last_active_check_result = (m_status & MSTAT_ACTIVE) != 0;

  // Determine if active
  if (m_status & (MSTAT_PROD_TILL_DONE)) {
    m_status |= MSTAT_ACTIVE;
  } else {
    switch (m_control_type) {
    case MPC_SCRIPT:
      break;

    case MPC_WHILE_PLAYER_VISIBLE:
    case MPC_AFTER_PLAYER_VISIBLE: {
      m_status &= ~MSTAT_ACTIVE;

      // Determine the correct creation room
      fvi_query fq;
      fvi_info hit_info;
      int fate;

      int croom = m_create_room;
      if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
        croom = GetTerrainRoomFromPos(&m_create_pnt);
      }

      fq.p0 = &m_create_pnt;
      fq.startroom = croom;
      fq.p1 = &Player_object->pos;
      fq.rad = 0.0f;
      fq.thisobjnum = -1;
      fq.ignore_obj_list = NULL;
      fq.flags = FQ_NO_RELINK | FQ_CHECK_OBJS | FQ_ONLY_DOOR_OBJ;

      fate = fvi_FindIntersection(&fq, &hit_info);

      if (fate == HIT_NONE)
        m_status |= MSTAT_ACTIVE;
    } break;

    case MPC_WHILE_PLAYER_NEAR:
    case MPC_AFTER_PLAYER_NEAR: {
      m_status &= ~MSTAT_ACTIVE;

      if (m_create_room == -1) {
      } else if (ROOMNUM_OUTSIDE(m_create_room) || (m_create_room <= Highest_room_index && Rooms[m_create_room].used &&
                                                    (Rooms[m_create_room].flags & RF_EXTERNAL))) {
        if (vm_VectorDistance(&Player_object->pos, &m_create_pnt) <= MATCEN_OUTSIDE_NEAR_DIST) {
          m_status |= MSTAT_ACTIVE;
        }
      } else if (m_create_room >= 0 && m_create_room <= Highest_room_index && Rooms[m_create_room].used) {
        room *rp = &Rooms[m_create_room];

        if (m_create_room == Player_object->roomnum) {
          m_status |= MSTAT_ACTIVE;
        } else {
          int x;

          for (x = 0; x < rp->num_portals; x++) {
            int c_room = rp->portals[x].croom;
            if (c_room < 0 && (vm_VectorDistance(&Player_object->pos, &m_create_pnt) <= MATCEN_OUTSIDE_NEAR_DIST)) {
              m_status |= MSTAT_ACTIVE;
            } else {
              if (c_room == Player_object->roomnum) {
                m_status |= MSTAT_ACTIVE;
              }
            }

            // Already active; so stop checking
            if (m_status & MSTAT_ACTIVE) {
              break;
            }
          }
        }
      }
    } break;

    default:
      Int3(); // Get Chris immediately
      break;
    }
  }

  bool cur_active = (m_status & MSTAT_ACTIVE) != 0;

  if (cur_active && !m_last_active_check_result) {
    if (m_type == MT_OBJECT) {
      object *obj = ObjGet(m_objref);

      if (obj)
        m_sound_active_handle = Sound_system.Play3dSound(m_sounds[MATCEN_ACTIVE_SOUND], SND_PRIORITY_NORMAL, obj);
    } else {
      pos_state pos;
      matrix idmat = Identity_matrix;

      int croom = m_create_room;
      if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
        croom = GetTerrainRoomFromPos(&m_create_pnt);
      }

      pos.position = &m_create_pnt;
      pos.orient = &idmat;
      pos.roomnum = croom;

      m_sound_active_handle = Sound_system.Play3dSound(m_sounds[MATCEN_ACTIVE_SOUND], SND_PRIORITY_NORMAL, &pos);
    }
  } else if (!cur_active && m_last_active_check_result) {
    Sound_system.StopSoundLooping(m_sound_active_handle);
  }

  if (cur_active && (m_control_type == MPC_AFTER_PLAYER_NEAR || m_control_type == MPC_AFTER_PLAYER_VISIBLE))
    m_status |= MSTAT_PROD_TILL_DONE;
}

#define MATCEN_DAMAGE_PER_SECOND 20.0f
#define MATCEN_DAMAGE_DIST 10.0f
#define MATCEN_FORCE 60000.0f

void matcen::DoThinkFrame() {
  if ((Game_mode & GM_MULTI) && Netgame.local_role != LR_SERVER)
    return;

  if (m_type == MT_UNASSIGNED)
    return;

  // If disabled and not finishing up a production...
  if ((m_prod_mode == MMODE_NOTPROD) && (m_status & MSTAT_DISABLED))
    return;

  if (m_type == MT_OBJECT) {
    object *parent = ObjGet(m_objref);

    if (!parent) {
      m_prod_mode_time = 0.0f;
      m_prod_mode = MMODE_NOTPROD;
      m_cur_saturation_count = 0;

      m_type = MT_UNASSIGNED;
      return;
    }

    if ((m_prod_mode != MMODE_NOTPROD &&
         (parent->movement_type == MT_PHYSICS || parent->movement_type == MT_WALKING)) ||
        (m_status & MSTAT_COMPUTE_CREATE_PNT_EVERY_FRAME)) {
      ComputeCreatePnt();
    }
  }

  // Increment time
  m_prod_mode_time += Frametime;

  // Do alive children frame
  if (m_max_alive_children > 0) {
    DoAliveListFrame();
  }

  // Determine if it is time to start a production
  switch (m_prod_mode) {
  case MMODE_NOTPROD: {
    if (!(m_status & (MSTAT_DONE_PROD | MSTAT_ACTIVE_PAUSE)) && (m_num_alive != m_max_alive_children)) {

      if (Gametime >= m_next_active_check_time) {
        CheckActivateStatus();
      }

      if ((m_status & MSTAT_ACTIVE) && (Gametime >= m_cached_prod_time) && (m_cached_prod_index >= 0)) {
        StartObjProd();
      }
    } else if ((m_status & MSTAT_DONE_PROD) && (m_status & MSTAT_ACTIVE)) {
      Sound_system.StopSoundLooping(m_sound_active_handle);
      m_status &= ~MSTAT_ACTIVE;
    }
  } break;

  case MMODE_PREPROD: {
    if (m_prod_mode_time >= m_preprod_time)
      DoObjProd();
  } break;

  case MMODE_POSTPROD: {
    m_status &= ~MSTAT_CREATE_OBJ_FRAME;

    if (m_prod_mode_time >= m_postprod_time)
      FinishObjProd();
  } break;

  default:
    Int3(); // get chris immediately
    break;
  }

  if ((!(m_status & MSTAT_NOT_HURT_PLAYER)) && (m_prod_mode == MMODE_PREPROD || m_prod_mode == MMODE_POSTPROD)) {
    float damage = MATCEN_DAMAGE_PER_SECOND * Frametime;
    if (Game_mode & GM_MULTI) {
      // Multiplayer targetting (Major difference is that robot will ignore players while infighting in single player)
      for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (!((NetPlayers[i].flags & NPF_CONNECTED) && (NetPlayers[i].sequence >= NETSEQ_PLAYING)))
          continue;

        object *p = &Objects[Players[i].objnum];
        if (p->type == OBJ_GHOST)
          continue;

        int croom = m_create_room;
        if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
          croom = GetTerrainRoomFromPos(&m_create_pnt);
        }

        if (croom != p->roomnum)
          continue;

        vector dir = p->pos - m_create_pnt;
        float dist = vm_NormalizeVector(&dir) - p->size;
        if (dist >= MATCEN_DAMAGE_DIST)
          continue;

        if (Netgame.local_role == LR_SERVER) {
          ApplyDamageToPlayer(p, p, PD_ENERGY_WEAPON, damage);
        }

        if (p == Player_object) {
          dir *= MATCEN_FORCE;

          vector movement_pos, movement_vec, pos;
          PhysicsDoSimLinear(*p, pos, dir, p->mtype.phys_info.velocity, movement_vec, movement_pos, Frametime, 1);
        }
      }
    } else {
      object *p = Player_object;
      if (p->type != OBJ_GHOST) {
        int croom = m_create_room;
        if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
          croom = GetTerrainRoomFromPos(&m_create_pnt);
        }

        if (croom == p->roomnum) {
          vector dir = p->pos - m_create_pnt;

          float dist = vm_NormalizeVector(&dir) - p->size;
          if (dist < MATCEN_DAMAGE_DIST) {
            ApplyDamageToPlayer(p, p, PD_ENERGY_WEAPON, damage);

            dir *= MATCEN_FORCE;

            vector movement_pos, movement_vec, pos;
            PhysicsDoSimLinear(*p, pos, dir, p->mtype.phys_info.velocity, movement_vec, movement_pos, Frametime, 1);
          }
        }
      }
    }
  }
}

void matcen::DoRenderFrame() {
  // MATCEN NOTE:  The objref of the created object is valid from the creation time to the
  // creation of the next object

  // Useful member variables:
  //    m_prod_mode         -- See below
  //		m_last_prod_objref
  //		m_prod_mode_time    -- Zero the first frame of the current production mode
  //		m_preprod_time
  //		m_postprod_time

  // Useful status members:
  // MSTAT_CREATE_OBJ_FRAME

  // DAJ	FIXES YET ANOTHER BUG WHERE THE ARRAY INDEX IS NOT CHECKED BEFORE USE (m_prod_type[m_cached_prod_index]
  // == -1)
  if (!(m_cached_prod_index >= 0 && m_cached_prod_index < m_num_prod_types && m_prod_type[m_cached_prod_index] >= 0 &&
        m_prod_type[m_cached_prod_index] <= MAX_OBJECT_TYPES &&
        Object_info[m_prod_type[m_cached_prod_index]].type != OBJ_NONE))
    return;

  // MATCEN NOTE: If an effect does something graphical, add it here
  switch (m_prod_mode) {
  case MMODE_NOTPROD: {
    switch (m_creation_effect) {
    case MEFFECT_LINE_LIGHTNING:
    default:
      return;
    }
  } break;

  case MMODE_PREPROD: {
    switch (m_creation_effect) {
    case MEFFECT_LINE_LIGHTNING: {
      int i;

      int oi_index = m_prod_type[m_cached_prod_index];

      if (oi_index < 0 || oi_index >= MAX_POLY_MODELS)
        break;

      PageInPolymodel(Object_info[oi_index].render_handle, Object_info[oi_index].type, &Object_info[oi_index].size);
      float size;

      if (oi_index >= 0)
        size = Object_info[oi_index].size * 1.5;
      else
        size = 0.0f;

      if (m_cur_saturation_count < 1) {
        for (i = 0; i < m_num_spawn_pnts; i++) {
          int croom = m_create_room;
          if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
            croom = GetTerrainRoomFromPos(&m_create_pnt);
          }

          m_spawn_vis_effects[m_cur_saturation_count][i] = -1;

          int visnum = VisEffectCreate(VIS_FIREBALL, LIGHTNING_BOLT_INDEX, croom, &m_create_pnt);
          if (visnum >= 0) {
            vis_effect *vis = &VisEffects[visnum];
            vis->lifeleft = .8f;
            vis->lifetime = .8f;
            vis->end_pos = m_spawn_vec[i];
            vis->flags = VF_USES_LIFELEFT | VF_EXPAND;
            vis->velocity.x = .8f;
            vis->velocity.y = 1;
            m_spawn_vis_effects[m_cur_saturation_count][i] = visnum;
          }
        }
        m_cur_saturation_count++;
      }

      // Move the viseffects if needed
      for (i = 0; i < m_cur_saturation_count; i++) {
        for (int t = 0; t < m_num_spawn_pnts; t++) {
          int visnum = m_spawn_vis_effects[i][t];
          if (visnum == -1)
            continue;

          ASSERT(visnum >= 0 && visnum < MAX_VIS_EFFECTS);
          vis_effect *vis = &VisEffects[visnum];

          vis->pos = m_create_pnt;
          vis->end_pos = m_spawn_vec[t];
        }
      }

      vector center = m_create_pnt;
      size = (m_prod_mode_time / m_preprod_time) * size;

      if (size > 0.0)
        DrawColoredDisk(&center, 0.3f, 0.5f, 1.0f, .7f, 0, size, 1);

    } break;

    case MEFFECT_LINE_SINE_WAVE: {
      int i;

      int oi_index = m_prod_type[m_cached_prod_index];

      if (oi_index < 0 || oi_index >= MAX_POLY_MODELS)
        break;

      PageInPolymodel(Object_info[oi_index].render_handle, Object_info[oi_index].type, &Object_info[oi_index].size);
      float size;

      if (oi_index >= 0)
        size = Object_info[oi_index].size * 1.5;
      else
        size = 0.0f;

      if (m_cur_saturation_count < 1) {
        for (i = 0; i < m_num_spawn_pnts; i++) {
          int croom = m_create_room;
          if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
            croom = GetTerrainRoomFromPos(&m_create_pnt);
          }

          m_spawn_vis_effects[m_cur_saturation_count][i] = -1;

          int visnum = VisEffectCreate(VIS_FIREBALL, SINE_WAVE_INDEX, croom, &m_create_pnt);
          if (visnum >= 0) {
            vis_effect *vis = &VisEffects[visnum];
            vis->lifeleft = 1;
            vis->lifetime = 1;
            vis->end_pos = m_spawn_vec[i];
            vis->flags = VF_USES_LIFELEFT | VF_EXPAND;
            vis->velocity.x = 1;
            vis->velocity.y = 1;
            m_spawn_vis_effects[m_cur_saturation_count][i] = visnum;
          }
        }

        m_cur_saturation_count++;
      }

      // Move the viseffects if needed
      for (i = 0; i < m_cur_saturation_count; i++) {
        for (int t = 0; t < m_num_spawn_pnts; t++) {
          int visnum = m_spawn_vis_effects[i][t];

          if (visnum == -1)
            continue;

          ASSERT(visnum >= 0 && visnum < MAX_VIS_EFFECTS);

          vis_effect *vis = &VisEffects[visnum];

          vis->pos = m_create_pnt;
          vis->end_pos = m_spawn_vec[t];
        }
      }

      vector center = m_create_pnt;
      size = (m_prod_mode_time / m_preprod_time) * size;

      if (size > 0.0)
        DrawColoredDisk(&center, 0.6f, 0.4f, 1.0f, .7f, 0, size, 1);
    } break;

    case MEFFECT_PROCEDURAL_LIGHTNING: {
      int i;

      int oi_index = m_prod_type[m_cached_prod_index];
      PageInPolymodel(Object_info[oi_index].render_handle, Object_info[oi_index].type, &Object_info[oi_index].size);
      float size;

      if (oi_index >= 0)
        size = Object_info[oi_index].size * 1.5;
      else
        size = 0.0f;

      if (m_cur_saturation_count < MAX_MATCEN_EFFECT_SATURATION) {
        for (i = 0; i < m_num_spawn_pnts; i++) {
          int croom = m_create_room;
          if (!ROOMNUM_OUTSIDE(m_create_room) && (Rooms[m_create_room].flags & RF_EXTERNAL)) {
            croom = GetTerrainRoomFromPos(&m_create_pnt);
          }

          m_spawn_vis_effects[m_cur_saturation_count][i] = -1;

          int visnum = VisEffectCreate(VIS_FIREBALL, THICK_LIGHTNING_INDEX, croom, &m_create_pnt);
          if (visnum >= 0) {
            vis_effect *vis = &VisEffects[visnum];

            vis->end_pos = m_spawn_vec[i];
            vis->lifeleft = 1;
            vis->lifetime = 1;
            vis->flags = VF_USES_LIFELEFT | VF_EXPAND | VF_LINK_TO_VIEWER;
            vis->billboard_info.width = std::max<float>(1, size / 2);
            vis->billboard_info.texture = 1;
            vis->velocity.x = 1;
            vis->velocity.y = 1;
            vis->velocity.z = .5;
            vis->lighting_color = GR_RGB16(255, 255, 255);

            vis->custom_handle = m_creation_texture;
            vis->size = vm_VectorDistanceQuick(&vis->pos, &vis->end_pos);
            m_spawn_vis_effects[m_cur_saturation_count][i] = visnum;
          }
        }
        m_cur_saturation_count++;
      }

      // Move the viseffects if needed
      for (i = 0; i < m_cur_saturation_count; i++) {
        for (int t = 0; t < m_num_spawn_pnts; t++) {
          int visnum = m_spawn_vis_effects[i][t];

          if (visnum == -1)
            continue;

          ASSERT(visnum >= 0 && visnum < MAX_VIS_EFFECTS);

          vis_effect *vis = &VisEffects[visnum];
          vis->pos = m_create_pnt;
          vis->end_pos = m_spawn_vec[t];
        }
      }

      vector center = m_create_pnt;
      size = (m_prod_mode_time / m_preprod_time) * size;

      if (size > 0.0)
        DrawColoredDisk(&center, 0.3f, 0.5f, 1.0f, .7f, 0, size, 1);

    } break;

    default:
      return;
    }
  } break;

  case MMODE_POSTPROD: {

    /*switch(m_creation_effect)
    {


    }*/

    return;

  } break;

  default:
    Int3(); // Get chris immediately
  }
}

#endif // NEWEDITOR

char matcen::GetCreationEffect() { return m_creation_effect; }

bool matcen::SetCreationEffect(char effect_index) {
  if (effect_index < 0 || effect_index >= NUM_MATCEN_EFFECTS)
    return false;

  m_creation_effect = effect_index;

  // MATCEN NOTE: Set default preprod and postprod stuff here

  // MATCEN NOTE: In addition, status flags can be set by effect type.  See Chris if
  // this is done as there are default functionality and script interaction issues
  switch (m_creation_effect) {
  case MEFFECT_LINE_LIGHTNING:
    m_preprod_time = 1.5f;
    m_postprod_time = 1.0f;
    break;
  case MEFFECT_LINE_SINE_WAVE:
    m_preprod_time = 0.25f;
    m_postprod_time = 0.0f;
    break;
  default:
    m_preprod_time = 1.5f;
    m_postprod_time = 1.0f;
    break;
  }

  return true;
}

void matcen::SetCreationTexture(int16_t texnum) { m_creation_texture = texnum; }

int16_t matcen::GetCreationTexture() { return m_creation_texture; }

int matcen::GetSound(char sound_type) {
  if (sound_type >= 0 && sound_type < MAX_MATCEN_SOUNDS) {
    return m_sounds[sound_type];
  }

  return MATCEN_ERROR;
}

bool matcen::SetSound(char sound_type, int sound_index) {
  if (sound_type >= 0 && sound_type < MAX_MATCEN_SOUNDS) {
    m_sounds[sound_type] = sound_index;
  }
  return false;
}

void matcen::Reset() {
  int i;

  // Resets the a matcen
  m_status &= ~(MSTAT_DONE_PROD | MSTAT_ACTIVE | MSTAT_ACTIVE_PAUSE | MSTAT_PROD_TILL_DONE | MSTAT_PROD_ONE_PAUSE |
                MSTAT_PROD_ONE_DISABLE);

  m_num_prod = 0;
  m_last_prod_type_index = MATCEN_ERROR;
  m_last_prod_finish_time = 0.0;

  m_last_active_check_result = false;
  m_next_active_check_time = 0.0;

  m_prod_mode_time = 0.0f;

  for (i = 0; i < MAX_PROD_TYPES; i++) {
    m_num_prod_type[i] = 0;
  }

  m_last_prod_objref = OBJECT_HANDLE_NONE;

  ComputeCreatePnt();

  if (m_prod_mode == MMODE_NOTPROD) {
    m_cached_prod_index = -1;
    m_cached_prod_time = 0.0f;

    ComputeNextProdInfo();
  }
}

int matcen::GetMaxAliveChildren() { return m_max_alive_children; }

bool matcen::SetMaxAliveChildren(int max_alive) {
  // If the max_alive value is valid...
  if (max_alive >= -1 && max_alive != 0 && max_alive <= MAX_MATCEN_ALIVE_CHILDREN) {
    int *temp;
    int i;

    // Allocate the alive children list
    if (max_alive > 0) {
      temp = (int *)mem_malloc(sizeof(int) * max_alive);
    } else {
      temp = NULL;
    }

    // Determine the current number of alive (and tracked) children
    if (m_alive_list && temp) {
      m_num_alive = (max_alive < m_num_alive) ? max_alive : m_num_alive;

      for (i = 0; i < m_num_alive; i++) {
        temp[i] = m_alive_list[i];
      }
    } else {
      m_num_alive = 0;
    }

    // Cleanup the old list
    if (m_alive_list) {
      mem_free(m_alive_list);
    }

    // Setup the new list pointer and max alive children value
    m_alive_list = temp;
    m_max_alive_children = max_alive;

    return true;
  }

  return false;
}

float matcen::GetPreProdTime() { return m_preprod_time; }

bool matcen::SetPreProdTime(float time) {
  float upper_bound;

  // MATCEN NOTE: Check if valid for effect here
  switch (m_creation_effect) {
  case MEFFECT_LINE_LIGHTNING:
    upper_bound = 2.0f;
    break;
  case MEFFECT_LINE_SINE_WAVE:
    upper_bound = 2.0f;
    break;
  default:
    upper_bound = 2.0f;
    break;
  }

  if (time >= 0.0f && time <= upper_bound) {
    m_preprod_time = time;
    return true;
  }

  return false;
}

float matcen::GetPostProdTime() { return m_postprod_time; }

bool matcen::SetPostProdTime(float time) {
  float upper_bound;

  // MATCEN NOTE: Check if valid for effect here
  switch (m_creation_effect) {
  case MEFFECT_LINE_LIGHTNING:
    upper_bound = 2.0f;
    break;
  case MEFFECT_LINE_SINE_WAVE:
    upper_bound = 2.0f;
    break;
  default:
    upper_bound = 2.0f;
    break;
  }

  if (time >= 0.0f && time <= upper_bound) {
    m_postprod_time = time;
    return true;
  }

  return false;
}

int FindMatcenIndex(const char *name) {
  int i;
  char temp[MAX_MATCEN_NAME_LEN];

  for (i = 0; i < Num_matcens; i++) {
    Matcen[i]->GetName(temp);

    if (!(stricmp(temp, name))) {
      return i;
    }
  }
  return MATCEN_ERROR;
}

int CreateMatcen(const char *name, bool *f_name_changed) {
  if (Num_matcens < MAX_MATCENS) {
    Matcen[Num_matcens] = new matcen;
    Matcen[Num_matcens++]->SetName(name);

    *f_name_changed = false;

    return Num_matcens - 1;
  }

  return MATCEN_ERROR;
}

void InitMatcens() {
  int i;

  Num_matcens = 0;

  for (i = 0; i < MAX_MATCENS; i++) {
    Matcen[i] = NULL;
  }

  atexit(DestroyAllMatcens);
}

#if defined(__LINUX__)
void DestroyAllMatcens()
#else
void __cdecl DestroyAllMatcens()
#endif
{
  int i;

  for (i = 0; i < Num_matcens; i++) {
    if (Matcen[i]) {
      delete Matcen[i];
    }
  }

  Num_matcens = 0;
}

#ifndef NEWEDITOR

void DoMatcensFrame() {
  int i;

  for (i = 0; i < Num_matcens; i++) {
    if (Matcen[i]) {
      Matcen[i]->DoThinkFrame();
    }
  }
}

#endif // NEWEDITOR

void InitMatcensForLevel() {
  int i;

  for (i = 0; i < Num_matcens; i++) {
    if (Matcen[i]) {
      Matcen[i]->Reset();
    }
  }
}

#ifndef NEWEDITOR

void DoMatcensRenderFrame() {
  int i;

  for (i = 0; i < Num_matcens; i++) {
    if (Matcen[i]) {
      Matcen[i]->DoRenderFrame();
    }
  }
}

#endif // NEWEDITOR

void DestroyMatcen(int id, bool f_resort = false) {
#if (!defined(EDITOR) && !defined(NEWEDITOR))
  f_resort = false;
#endif

  if (MatcenValid(id)) {
    delete Matcen[id];
    Matcen[id] = NULL;

    Num_matcens--;

    if (f_resort) {
      while (id < Num_matcens) {
        Matcen[id] = Matcen[id + 1];
        id++;
      }
    }
  }
}

bool MatcenValid(int id) { return (id >= 0 && id < Num_matcens && Matcen[id]); }
