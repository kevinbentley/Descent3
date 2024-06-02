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

#include <limits>

#include "musicapi.h"
#include "music.h"
#include "mono.h"
#include "pserror.h"

// generic constants
#define MUSIC_IDLE_TIME 240.0f // how many seconds before background music silences.

// flags for musicAI
#define MUSICAIF_PLAYERDEAD 0x1
#define MUSICAIF_PLAYERINVUL 0x2
#define MUSICAIF_STARTLEVEL 0x4 // game started a new level
#define MUSICAIF_HOSTILES 0x8   // there are hostiles around
#define MUSICAIF_NEWREGION 0x40

// names of themes. (match to music.h THEME_TYPES)
const char *const Music_type_names[] = {"No song",    "Intro song",       "Idle song",       "Combat song",
                                        "Death song", "Idle-Combat song", "Combat-Idle song"};

// global data
#ifdef _DEBUG
bool Music_debug_verbose = false; // debug flag for music system
#endif

// in library data.
static OutrageMusicSeq Music_seq;
static bool Music_on = false;
static bool Allow_music = false;
static float Music_volume = 1.0f;

// music ai structure.
static struct {
  float peace_timer; // how long has player been out of combat.
  int flags;         // current state of music AI.
  int cur_song;      // current song
  int n_hostiles;    // number of hostiles ai thinks there are.
  tMusicVal trigger;
  int16_t pending_region;   // pending region change.
  bool was_toggled_on;    // music was turned on by user.
  bool immediate_switch;  // force switch immediately for regions
  bool restart_sequencer; // restarts sequencer next frame.
} MusicAI;

//	handles operations on current events.
static void D3MusicSongSelector();

// creates music ai struction from music info passed in.
static void D3MusicAI(tMusicSeqInfo *music_info);

///////////////////////////////////////////////////////////////////////////////

void InitD3Music(bool allow_music) {
  Music_on = false;
  Allow_music = allow_music;
}

void CloseD3Music() { Music_on = false; }

// is music system on?
bool IsD3MusicOn() { return Music_on; }

//	starts up the music sequencer
void D3MusicStart(const char *theme_file) {
  if (theme_file && Music_seq.Init(theme_file)) {
    Music_on = true;
    Music_seq.SetVolume(Music_volume);
  } else {
    Music_on = false;
  }

  if (!Allow_music) {
    Music_on = false;
  }

  if (Music_on) {
    if (Music_volume > 0.0f) {
      Music_seq.Start();
    } else {
      Music_on = false; // volume was 0.0f, so don't mark music as on since we don't start
    }
  }

  // reset AI state.
  MusicAI.cur_song = OMS_THEME_TYPE_NONE;
  //@@	MusicAI.mood_default = MUSIC_MOOD_DEFAULT;
  //@@	MusicAI.mood = MUSIC_MOOD_DEFAULT;
  MusicAI.flags = 0;
  MusicAI.n_hostiles = 0;
  MusicAI.was_toggled_on = false;
  MusicAI.pending_region = -1;
  MusicAI.restart_sequencer = false;
  MusicAI.immediate_switch = false;
  D3MusicSetRegion(0);

  // reset AI timers
  MusicAI.peace_timer = 0.0f;
}

//	stops the music sequencer
void D3MusicStop() {
  Music_seq.Stop();
  Music_seq.Shutdown();
  Music_on = false;
}

//	execute music sequencer.
void D3MusicDoFrame(tMusicSeqInfo *music_info) {
  // update music ai with new music info
  if (!Music_on)
    return;

  D3MusicAI(music_info);

  // handle current events.
  D3MusicSongSelector();

  //	run frame.
  Music_seq.Frame(music_info->frametime);

  // end
  music_info->cur_loop_name = Music_seq.GetCurrentLoopName(&music_info->cur_loop_count);
  music_info->cur_song = MusicAI.cur_song;
}

// toggle music system.
void D3MusicToggle() {
  Music_on = (!Music_on && Allow_music && Music_volume > 0.0f) ? true : false;
  if (Music_on) {
    Music_seq.Start();
    MusicAI.was_toggled_on = true;
  } else {
    Music_seq.Stop();
    MusicAI.was_toggled_on = false;
  }
}

// toggle music system.
void D3MusicToggle(bool state) {
  if (state && !Music_on && Allow_music && Music_volume > 0.0f) {
    Music_seq.Start();
    MusicAI.was_toggled_on = true;
    Music_on = true;
  } else if (!state && Music_on) {
    Music_seq.Stop();
    MusicAI.was_toggled_on = false;
    Music_on = false;
  }
}

// pauses and or resumes music
void D3MusicPause() { Music_seq.Pause(); }

void D3MusicResume() { Music_seq.Resume(); }

// volume stuff
float D3MusicGetVolume() { return Music_volume; }

void D3MusicSetVolume(float vol) {
  const float kEpsilon = std::numeric_limits<float>::min();
  if (vol <= kEpsilon) {
    Music_seq.Stop();
    MusicAI.was_toggled_on = false;
    Music_on = false;
  } else if (Music_volume <= kEpsilon) {
    Music_on = true;
    MusicAI.was_toggled_on = true;
    if (MusicAI.pending_region == -1) {
      MusicAI.pending_region = D3MusicGetRegion();
    }
    Music_seq.Start();
  }
  Music_seq.SetVolume(vol);
  Music_volume = vol;
}

//	New Interface
//	Sequencing within level.
//		play intro track.
//		play main background music.
//		occasionally switch to other ambient music options.
//		when hostility towards player is upped, play 'hostile' music.
//		when player enters combat (player takes damage from hostile), switch to combat music.
//		fade out background music after 2-3 minutes if no change in state.
//

// creates music ai struction from music info passed in.
void D3MusicAI(tMusicSeqInfo *music_info) {
  // determine flags state.
  if (music_info->player_dead) {
    MusicAI.flags |= MUSICAIF_PLAYERDEAD;
  } else {
    MusicAI.flags &= (~MUSICAIF_PLAYERDEAD);
  }

  if (music_info->started_level) {
    MusicAI.flags |= MUSICAIF_STARTLEVEL;
    MusicAI.peace_timer = 0.0f;
  } else {
    MusicAI.flags &= (~MUSICAIF_STARTLEVEL);
  }

  if (music_info->n_hostiles && !(MusicAI.flags & MUSICAIF_HOSTILES)) {
    MusicAI.flags |= MUSICAIF_HOSTILES;
    MusicAI.peace_timer = 0.0f;
  } else if (!music_info->n_hostiles && (MusicAI.flags & MUSICAIF_HOSTILES)) {
    // make sure hostiles flags is cleared once. when no hostiles, but hostiles flag is on.
    MusicAI.flags &= (~MUSICAIF_HOSTILES);
    MusicAI.peace_timer = 0.0f;
    //@@		MusicAI.mood_timer = 0.0f;
  }

  //@@//	set mood timers
  //@@	if (!CHECK_FLAG(MusicAI.flags, MUSICAIF_NEGMOODTIMER) && MusicAI.mood < 0) {
  //@@		MusicAI.flags |= MUSICAIF_NEGMOODTIMER;
  //@@		MusicAI.negmood_timer = 0.0f;
  //@@	}
  //@@	if (CHECK_FLAG(MusicAI.flags, MUSICAIF_NEGMOODTIMER) && MusicAI.mood >=0) {
  //@@		MusicAI.flags &= (~MUSICAIF_NEGMOODTIMER);
  //@@		MusicAI.negmood_timer = 0.0f;
  //@@	}
  //@@	if (!CHECK_FLAG(MusicAI.flags, MUSICAIF_POSMOODTIMER) && MusicAI.mood > 0) {
  //@@		MusicAI.flags |= MUSICAIF_POSMOODTIMER;
  //@@		MusicAI.posmood_timer = 0.0f;
  //@@	}
  //@@	if (CHECK_FLAG(MusicAI.flags, MUSICAIF_POSMOODTIMER) && MusicAI.mood <=0) {
  //@@		MusicAI.flags &= (~MUSICAIF_POSMOODTIMER);
  //@@		MusicAI.posmood_timer = 0.0f;
  //@@	}

  //@@// determine mood of music
  //@@	float shield_scalar = (float)music_info->player_shield_level/MUSIC_PLR_SHIELD_LVLS;
  //@@	if (shield_scalar > 1.0f) shield_scalar = 1.0f;

  //@@// being damaged saddens mood
  //@@	if (music_info->player_damaged) {
  //@@		MusicAI.mood -= ((1.0f-shield_scalar)*MUSIC_MOOD_DAMAGE_MOD);
  //@@	}

  //@@// killing someone HOSTILE raises one's mood.
  //@@	MusicAI.mood += (music_info->n_hostiles_player_killed*MUSIC_MOOD_KILLS_MOD);

  //@@// a reduction in hostiles will also modify mood positively, and more hostiles has the opposite effect.
  //@@	if ((music_info->n_hostiles-MusicAI.n_hostiles)) {
  //@@		MusicAI.mood -=
  //((1.5f-shield_scalar)*((music_info->n_hostiles-MusicAI.n_hostiles)*MUSIC_MOOD_HOSTILES_MOD));
  //@@	}

  //@@// if no hostiles and mood != mood_default, then modify mood until it equals 0 again.  do it every second.
  //@@	if (MusicAI.mood != MusicAI.mood_default) {
  //@@		int16_t mod = (MusicAI.flags & MUSICAIF_HOSTILES) ? 1 : 2;
  //@@		float time_mod = (MusicAI.flags & MUSICAIF_HOSTILES) ? 0.2f : 0.2f;
  //@@		if (MusicAI.mood_timer >= time_mod) {
  //@@			if (MusicAI.mood > MusicAI.mood_default) {
  //@@				MusicAI.mood -= mod;
  //@@				if (MusicAI.mood < MusicAI.mood_default) MusicAI.mood = MusicAI.mood_default;
  //@@			}
  //@@			if (MusicAI.mood < MusicAI.mood_default) {
  //@@				MusicAI.mood += mod;
  //@@				if (MusicAI.mood > MusicAI.mood_default) MusicAI.mood = MusicAI.mood_default;
  //@@			}
  //@@			MusicAI.mood_timer = 0.0f;
  //@@		}
  //@@		MusicAI.mood_timer += music_info->frametime;
  //@@	}
  //@@
  //@@	if (CHECK_FLAG(MusicAI.flags, MUSICAIF_NEGMOODTIMER)) {
  //@@		MusicAI.negmood_timer += music_info->frametime;
  //@@	}
  //@@	if (CHECK_FLAG(MusicAI.flags, MUSICAIF_POSMOODTIMER)) {
  //@@		MusicAI.posmood_timer += music_info->frametime;
  //@@	}
  //@@
  // other stuff
  MusicAI.n_hostiles = music_info->n_hostiles;

  if (!MusicAI.n_hostiles) { // how long have we been without hostiles
    MusicAI.peace_timer += music_info->frametime;
  }

  //@@	if (MusicAI.flags & MUSICAIF_PLAYERDEAD) {	// if dead, mood is always set to default.
  //@@		MusicAI.mood = MusicAI.mood_default;
  //@@	}

  // output
  //@@	Music_seq.SetRegister(MUSICREG_MOOD_VALUE, MusicAI.mood);
  //@@	Music_seq.SetRegister(MUSICREG_POSMOOD_TIMER, MusicAI.posmood_timer);
  //@@	Music_seq.SetRegister(MUSICREG_NEGMOOD_TIMER, MusicAI.negmood_timer);
  Music_seq.SetRegister(MUSICREG_PEACE_TIMER, MusicAI.peace_timer);
  Music_seq.SetRegister(MUSICREG_TRIGGER_VALUE, MusicAI.trigger);

  music_info->peace_timer = MusicAI.peace_timer;
  //@@	music_info->mood = MusicAI.mood;
  //@@	music_info->nmood_timer = MusicAI.negmood_timer;
  //@@	music_info->pmood_timer = MusicAI.posmood_timer;

  if (MusicAI.trigger > 0) {
    MusicAI.trigger = MUSICTRIGGER_NONE;
  }
}

//	handles operations on current events.
void D3MusicSongSelector() {
  oms_q_evt evt;

  if ((MusicAI.cur_song != OMS_THEME_TYPE_DEATH) && (MusicAI.flags & MUSICAIF_PLAYERDEAD)) {
    MusicAI.cur_song = OMS_THEME_TYPE_DEATH;
    Music_seq.StartSong(MusicAI.cur_song, false);
  }

  if (MusicAI.was_toggled_on) {
    if (MusicAI.pending_region > -1) {
      Music_seq.SetCurrentRegion(MusicAI.pending_region);
      MusicAI.pending_region = -1;
    }
    MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
    MusicAI.peace_timer = 0.0f;
    Music_seq.StartSong(MusicAI.cur_song, false);
    MusicAI.was_toggled_on = false;
  }

  // intro music will always play at start of level.
  if (MusicAI.flags & MUSICAIF_STARTLEVEL) {
    MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
    Music_seq.SetCurrentRegion(0);
    Music_seq.StartSong(MusicAI.cur_song, false);
  }
  if (MusicAI.pending_region > -1 && MusicAI.immediate_switch) {
    MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
    Music_seq.SetCurrentRegion(MusicAI.pending_region);
    Music_seq.StartSong(MusicAI.cur_song, false);
    MusicAI.pending_region = -1;
    MusicAI.immediate_switch = false;
  }

  // process events and songs.
  do {
    if (!Music_seq.m_output_q.recv(&evt)) {
      evt.cmd = OMS_EVT_NONE;
    }

    switch (MusicAI.cur_song) {
    case OMS_THEME_TYPE_NONE:
      if (MusicAI.pending_region > -1) {
        mprintf(0, "D3MUSIC: new region request processed.\n");
        MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
        Music_seq.SetCurrentRegion(MusicAI.pending_region);
        Music_seq.StartSong(MusicAI.cur_song, true);
        MusicAI.pending_region = -1;
      }
      break;

    case OMS_THEME_TYPE_IDLE: // IDLE MUSIC CURRENTLY PLAYING
      if (evt.cmd == OMS_EVT_SONGENDED) {
        MusicAI.cur_song = OMS_THEME_TYPE_NONE;
        //	if (Music_seq.GetCurrentRegion() == 0) {
        //		mprintf(0, "Ending Region 0.\n");
        //		MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
        //		Music_seq.SetCurrentRegion(1);
        //		Music_seq.StartSong(MusicAI.cur_song, true);
        //	}
        //	else {
        //		mprintf(0, "D3MUSIC: Song ended normally?\n");
        //	}
      } else if (evt.cmd == OMS_EVT_LOOPENDING) {
        // shall we switch regions?
        if (MusicAI.pending_region > -1) {
          mprintf(0, "D3MUSIC: new region request processed.\n");
          MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
          Music_seq.SetCurrentRegion(MusicAI.pending_region);
          Music_seq.StartSong(MusicAI.cur_song, true);
          MusicAI.pending_region = -1;
        }
      }
      break;

    case OMS_THEME_TYPE_DEATH:
      if (!(MusicAI.flags & MUSICAIF_PLAYERDEAD)) {
        MusicAI.cur_song = OMS_THEME_TYPE_IDLE;
        MusicAI.peace_timer = 0.0f;
        Music_seq.StartSong(MusicAI.cur_song, false);
      }
      break;

    default:
      Int3();
    }
  } while (evt.cmd != OMS_EVT_NONE);
}

//	set music region
void D3MusicSetRegion(int16_t region, bool immediate) {
  if (Music_seq.GetCurrentRegion() != region) {
    MusicAI.immediate_switch = immediate;
    MusicAI.pending_region = region;
    //@@	if (MusicAI.immediate_switch) {
    //@@	// at next frame, start again!
    //@@		Music_seq.Pause();
    //@@		MusicAI.restart_sequencer = true;
    //@@	}
  }
}

// retreives current region
int16_t D3MusicGetRegion() { return Music_seq.GetPlayingRegion(); }

// retreives current PLAYING region.
int16_t D3MusicGetPendingRegion() { return MusicAI.pending_region; }

// starts special in-game cinematic music
void D3MusicStartCinematic() {}

// stops special in-game cinematic music
void D3MusicStopCinematic() {}
