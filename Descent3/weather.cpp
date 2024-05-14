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

#include "pserror.h"
#include "pstypes.h"
#include "fireball.h"
#include "weather.h"
#include "viseffect.h"
#include "object.h"
#include "terrain.h"
#include "room.h"
#include "game.h"
#include "soundload.h"
#include "hlsoundlib.h"
#include "sounds.h"

#include <stdlib.h>

#include "psrand.h"
weather Weather = {0};

/// Makes droplets appear on the windshield, plus makes rain fall in the distance.
static void DoRainEffect();

int ThunderA_sound_handle = -1;
int ThunderB_sound_handle = -1;

// resets the weather so there is nothing happening
void ResetWeather() {
  Weather.flags = 0;
  Weather.last_lightning_evaluation_time = 0;
}

// Makes droplets appear on the windshield, plus makes rain fall in the distance
void DoRainEffect() {
  // See how many droplets to create on the windshield
  // This is dependant on how fast the player is moving forward
  int randval = 1 + ((1.0 - Weather.rain_intensity_scalar) * MAX_RAIN_INTENSITY);

  if (randval < 20)
    randval = 20;

  vector vel = Viewer_object->mtype.phys_info.velocity;
  float mag = vm_GetMagnitudeFast(&vel);
  vel /= mag;

  float scalar = vm_DotProduct(&vel, &Viewer_object->orient.fvec);

  vector upvec = {0, 1.0, 0};

  scalar *= (1 + (mag / 100));

  randval -= scalar * 10;

  if (randval < 2)
    randval = 2;
  else if (randval > 80)
    randval = 80;

  if ((upvec * Viewer_object->orient.uvec) < 0)
    randval = 8000; // Make sure rain does fall upwards

  if (Viewer_object->type == OBJ_PLAYER && OBJECT_OUTSIDE(Viewer_object) && (ps_rand() % randval) == 0) {
    // Put some droplets on the windshield
    vector pos = {0, 0, 0};

    pos.x = ((ps_rand() % 1000) - 500) / 250.0;
    pos.y = ((ps_rand() % 1000) - 500) / 350.0;
    pos.z = 3.0;

    int visnum = VisEffectCreate(VIS_FIREBALL, RAINDROP_INDEX, Viewer_object->roomnum, &pos);
    if (visnum >= 0) {
      vis_effect *vis = &VisEffects[visnum];
      float life = .4 + ((ps_rand() % 500) / 1000.0);
      vis->lifeleft = life;
      vis->lifetime = life;
      vis->size = .01 + ((ps_rand() % 500) / 3000.0);

      if (vis->size > .05) {
        Sound_system.Play2dSound(SOUND_RAINDROP);
      }

      vis->flags |= VF_WINDSHIELD_EFFECT;
    }
  }

  // Create some rain in the distance

  if (OBJECT_OUTSIDE(Viewer_object)) {
    int num = 20 + (ps_rand() % 15);
    angvec angs;
    int i;

    vm_ExtractAnglesFromMatrix(&angs, &Viewer_object->orient);
    matrix mat;
    vm_AnglesToMatrix(&mat, 0, angs.h, 0);

    for (i = 0; i < num; i++) {
      vector pos = Viewer_object->pos;

      float z = ((ps_rand() % 1000) / 1000.0) * 700;
      float x = (((ps_rand() % 1000) - 500) / 500.0) * 300;
      float y = (((ps_rand() % 1000) - 500) / 500.0) * 200;

      pos += x * mat.rvec;
      pos += y * mat.uvec;
      pos += z * mat.fvec;

      // Create falling rain
      int visnum = VisEffectCreate(VIS_FIREBALL, FADING_LINE_INDEX, Viewer_object->roomnum, &pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];
        float life = .001f;
        vis->lifeleft = life;
        vis->lifetime = life;
        vis->lighting_color = GR_RGB16(200, 200, 255);
        vis->end_pos = pos;
        vis->end_pos.y += 20;
        vis->flags |= VF_WINDSHIELD_EFFECT;
        vis->pos -= (Viewer_object->mtype.phys_info.velocity / 2);
      }
    }

    num /= 2;
    for (i = 0; i < num; i++) {
      vector pos = Viewer_object->pos;

      float z = ((ps_rand() % 1000) / 1000.0) * 700;
      float x = (((ps_rand() % 1000) - 500) / 500.0) * 300;
      float y = (((ps_rand() % 1000) - 500) / 500.0) * 200;

      pos += x * mat.rvec;
      pos += y * mat.uvec;
      pos += z * mat.fvec;

      if (pos.z < 0 || pos.z >= TERRAIN_DEPTH * TERRAIN_SIZE)
        continue;
      if (pos.x < 0 || pos.x >= TERRAIN_WIDTH * TERRAIN_SIZE)
        continue;

      // Create puddle drops on the terrain
      vector norm;
      float ypos = GetTerrainGroundPoint(&pos, &norm);
      pos.y = ypos;
      int visnum = VisEffectCreate(VIS_FIREBALL, PUDDLEDROP_INDEX, Viewer_object->roomnum, &pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];
        float life = .2f;
        float size = .7 + ((ps_rand() % 10) / 20.0);
        vis->lifeleft = life;
        vis->lifetime = life;
        vis->end_pos = norm;
        vis->flags |= VF_PLANAR;
      }
    }
  }
}

// Creates snow for this frame
void DoSnowEffect() {
  if (OBJECT_OUTSIDE(Viewer_object)) {
    int num = 20 + (ps_rand() % 15);

    if (Weather.snowflakes_to_create + num > 250) {
      num = 250 - Weather.snowflakes_to_create;

      if (num < 1) {
        Weather.snowflakes_to_create = 0;
        return;
      }
    }

    // angvec angs;
    matrix mat;

    // vm_ExtractAnglesFromMatrix (&angs,&Viewer_object->orient);
    // vm_AnglesToMatrix (&mat,0,angs.h,0);

    mat = Viewer_object->orient;

    for (int i = 0; i < num; i++) {
      vector pos = Viewer_object->pos;

      float z = ((ps_rand() % 1000) / 1000.0) * 300;
      float x = (((ps_rand() % 1000) - 500) / 500.0) * 200;
      int y = (ps_rand() % 80);

      pos += x * mat.rvec;
      pos += y * mat.uvec;
      pos += z * mat.fvec;

      if (pos.z < 0 || pos.z >= TERRAIN_DEPTH * TERRAIN_SIZE)
        continue;
      if (pos.x < 0 || pos.x >= TERRAIN_WIDTH * TERRAIN_SIZE)
        continue;

      // Create falling rain
      vector down_vec = {0, -30, 0};
      int visnum = VisEffectCreate(VIS_FIREBALL, SNOWFLAKE_INDEX, Viewer_object->roomnum, &pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];
        float life = 1.5 + ((ps_rand() % 100) / 100.0);
        vis->lifeleft = life;
        vis->lifetime = life;
        vis->lighting_color = GR_RGB16(200, 200, (ps_rand() % 50) + 200);
        vis->size = ((ps_rand() % 1000) / 1000.0) + .5;

        vis->flags |= VF_WINDSHIELD_EFFECT | VF_USES_LIFELEFT;

        vis->velocity = down_vec;
      }
    }
  }

  Weather.snowflakes_to_create = 0;
}

// does all the weather stuff that is going to be done for this frame
void DoWeatherForFrame() {
  int i;
  int hear_thunder = 0;

  if (OBJECT_OUTSIDE(Player_object))
    hear_thunder = 1;
  else {
    int roomnum = Player_object->roomnum;
    room *rp = &Rooms[roomnum];

    for (i = 0; i < rp->num_portals && hear_thunder == 0; i++) {
      if (rp->portals[i].croom == -1)
        hear_thunder = 1;
      else if (Rooms[rp->portals[i].croom].flags & RF_EXTERNAL)
        hear_thunder = 1;
    }
  }

  if (Weather.flags & WEATHER_FLAGS_RAIN)
    DoRainEffect();

  if (Weather.flags & WEATHER_FLAGS_SNOW)
    DoSnowEffect();

  if (Weather.flags & WEATHER_FLAGS_LIGHTNING) {
    if ((Gametime - Weather.last_lightning_evaluation_time) > Weather.lightning_interval_time) {
      // Check to see if we should draw some lightning
      Weather.last_lightning_evaluation_time = Gametime;
      ASSERT(Weather.lightning_rand_value > 0);
      if (ps_rand() <= Weather.lightning_rand_value) {
        // Start the lightning sequence
        Weather.lightning_sequence = 1;

        if ((ps_rand() % 7) == 0 && hear_thunder)
          Sound_system.Play2dSound(SOUND_LIGHTNING);
      }

      if (hear_thunder && (ps_rand() % (Weather.lightning_rand_value * 3)) == 0) {
        if (ThunderA_sound_handle == -1)
          ThunderA_sound_handle = FindSoundName("ThunderA");
        if (ThunderB_sound_handle == -1)
          ThunderB_sound_handle = FindSoundName("ThunderB");

        if (ps_rand() % 2)
          Sound_system.Play2dSound(ThunderA_sound_handle);
        else
          Sound_system.Play2dSound(ThunderB_sound_handle);
      }
    }
  }
}

// Sets the state of the rain to on or off, plus sets the intensity of the rain (0 to 1)
void SetRainState(int on, float intensity) {
  if (on) {
    Weather.flags |= WEATHER_FLAGS_RAIN;
    Weather.rain_intensity_scalar = intensity;
  } else {
    Weather.flags &= ~WEATHER_FLAGS_RAIN;
  }
}

// Sets the state of the rain to on or off, plus sets the intensity of the rain (0 to 1)
void SetSnowState(int on, float intensity) {
  if (on) {
    Weather.flags |= WEATHER_FLAGS_SNOW;
    Weather.snow_intensity_scalar = intensity;
  } else {
    Weather.flags &= ~WEATHER_FLAGS_SNOW;
  }
}

// Sets the state of lightning to on or off, plus allows the setting of how often to check
// for lightning and the randomness at which lightning happens
void SetLightningState(int on, float interval_time, int randval) {
  if (on) {
    Weather.flags |= WEATHER_FLAGS_LIGHTNING;
    Weather.lightning_sequence = 0;
    Weather.lightning_rand_value = randval;
    Weather.lightning_interval_time = interval_time;
  } else {
    Weather.flags &= ~WEATHER_FLAGS_LIGHTNING;
  }
}
