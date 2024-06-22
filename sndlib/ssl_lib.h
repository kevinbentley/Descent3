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

 * $Logfile: /DescentIII/Main/lib/ssl_lib.h $
 * $Revision: 57 $
 * $Date: 3/20/00 12:27p $
 * $Author: Matt $
 *
 * Header for shared sound library
 *
 * $Log: /DescentIII/Main/lib/ssl_lib.h $
 *
 * 57    3/20/00 12:27p Matt
 * Merge of Duane's post-1.3 changes.
 * Lower MAX_SOUNDS and MAX_SOUND_FILES for Mac.
 *
 * 56    10/23/99 3:24p 3dsmax
 *
 * 55    10/21/99 4:05p Chris
 * Removed a bad thing
 *
 * 54    10/21/99 1:48p Kevin
 * Mac Merge
 *
 * 53    10/08/99 4:29p Chris
 * Added the forcefield and glass breaking override options
 *
 * 52    8/23/99 5:29p Samir
 * incremental EAX 2.0 checkin
 *
 * 51    8/10/99 2:08p Gwar
 * added sound support to neweditor
 *
 * 50    5/20/99 1:00a Samir
 * changes in ordering of EAX and NONE mixers.
 *
 * 49    5/11/99 2:08a 3dsmax
 *
 * 48    5/11/99 2:05a 3dsmax
 * Increased MAX_SOUNDS so we can work
 *
 * 47    4/30/99 12:56p Kevin
 * Lowered values for MAX_SOUNDS, MAX_ROOMS, MAX_TEXTURES and MAX_OBJIDS.
 * Talk to me before changing any of these again.
 *
 * 46    4/27/99 2:10p Samir
 * added code to set the desired sound card given the descriptive name of
 * a sound card.
 *
 * 45    4/14/99 3:43p Matt
 * Increased the number of sounds from 700 to 750.  When I lowered this
 * number to 700 recently, I counted that we were using around 600 sounds.
 * Either I miscounted or we added a lot of sounds in the last few days.
 *
 * 44    4/11/99 5:04p Matt
 * Reduced the maximum number of sounds from 1000 to 700.  Currently we're
 * only using 607 sounds, and the new static sound remapping code doesn't
 * require any extra space, so 700 is probably ok for now at least.
 *
 * 43    4/10/99 5:09p Samir
 * beginning to add prioritization of sounds code.  currently non
 * functional, but allows me to change all calls to Play3dSound so that I
 * can test later.
 *
 * 42    4/06/99 8:29p Samir
 * added error check system.
 *
 * 41    3/30/99 4:44p Matt
 * Increased max sounds from 700 to 1000
 *
 * 40    3/29/99 11:01a Samir
 * added prototypes for 3d sound environment options.
 *
 * 39    3/17/99 4:20p Samir
 * added functions to pause and resume individual sounds.
 *
 * 38    1/14/99 6:10p Samir
 * added DirectSound buffer duplication code.
 *
 * 37    1/11/99 5:51p Samir
 * reverb on the buffer level.
 *
 * 36    1/08/99 6:31p Samir
 * added reverb
 *
 * 35    12/23/98 11:49a Samir
 * added EAX mixer.
 *
 * 34    10/28/98 3:56p Chris
 *
 * 33    10/28/98 3:55p Chris
 * Resized the buffers
 *
 * 32    10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 31    10/14/98 5:12p Samir
 * added a null SOUND_MIXER.
 *
 * 30    8/10/98 5:55p Samir
 * added element in play_info to specify streaming buffer size.
 *
 * 29    7/24/98 5:23p Samir
 * moved sound variables from soundload to ssl_lib.h (and WAV file stuff)
 *
 * 28    7/09/98 8:34p Samir
 * added parameter to play_information.
 *
 * 27    7/06/98 1:49p Samir
 * added some error checking.
 *
 * 26    6/29/98 10:44p Chris
 * Added support for SIF_ONCE_PER_OBJ
 *
 * 25    6/29/98 7:35p Chris
 * Increased sound buffer size
 *
 * 24    6/29/98 4:15p Chris
 * Streaming audio works
 *
 * 23    6/29/98 9:29a Chris
 * Added some support for Direct Sound 3d
 *
 * 22    6/25/98 11:28a Chris
 * Added some DS3d support
 *
 * 21    6/24/98 6:43p Chris
 * Furthered the endless work on the sound system
 *
 * 20    6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 19    6/19/98 3:09p Chris
 * Improved IsSoundPlaying
 *
 * 18    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 17    6/17/98 7:04p Chris
 * Added support for 8bit stream data to be played by our 16bit sound
 * mixer
 *
 * 16    6/17/98 4:39p Chris
 * Added the playing of 8bit samples with the 16 bit sound mixer
 *
 * 15    6/16/98 4:46p Chris
 * Revision 2 of the stream audio stuff
 *
 * 14    6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 13    2/15/98 7:12p Chris
 * More improvements to the sound lib
 *
 * 12    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 11    1/06/98 2:12p Chris
 * Added muffled sounds v.1 and made 3d sounds keep their roomnum.
 *
 * 10    1/05/98 3:54p Chris
 * Added ambient and explosion sounds
 *
 * 9     1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 8     12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 7     12/30/97 2:15p Chris
 * Adding further support for software 3d stuff
 *
 * 6     12/29/97 4:50p Chris
 * Added SPF_NO_UPDATE
 *
 * 5     12/22/97 6:19p Chris
 * Working on new mixer functionality
 *
 * 4     12/18/97 12:26p Chris
 * Incremental new lib improvements
 *
 * 3     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 2     11/21/97 1:10p Chris
 * Incremental Improvements
 *
 * 18    6/11/97 2:31p Samir
 * Incorporated changes in gameos to new system
 *
 * 17    5/22/97 5:15p Chris
 *
 * 16    5/05/97 5:41a Chris
 * Changed an include for MacMAN!
 *
 * 15    4/29/97 8:03a Chris
 * Improved the sound code.  High-level sound now
 * fully uses the flags in the sound page and it
 * resulted in a simpilier coding interface  :)
 *
 * 14    4/28/97 11:21a Chris
 * Incremental improvements is the sound system
 *
 * 13    4/24/97 4:19a Chris
 * Modified the pos_state struct to be more compact.
 *
 * 12    4/24/97 3:25a Chris
 * // Added some more support for 3d sounds
 *
 * 11    4/03/97 8:37p Chris
 * Added the Main_OS object pass in the sound library
 * initialization code.
 *
 * 10    4/01/97 2:13p Jason
 * changes for sound page functionality
 *
 * 9     4/01/97 10:00a Chris
 *
 * 8     3/17/97 5:12p Chris
 * Allowed new sound code to be demo'ed.
 *
 * 7     3/14/97 12:10p Chris
 * Made a nice C++ abstract type for the low-level.  It should make the
 * MacMan very joyful.  :)
 *
 * 6     2/07/97 5:48p Matt
 * Renamed vector.h to vecmat.h to fix DevStudio problem
 *
 * $NoKeywords: $
 */

#ifndef __SSL_LIB_H__
#define __SSL_LIB_H__

#include "vecmat.h"

#ifndef NEWEDITOR
#include "manage.h"
#else
#include "..\neweditor\ned_TableFile.h"
#endif

class oeApplication; // reference to oeApplication class.

#define MAX_GAME_VOLUME 1.0f // helps against clipping

// Size of streaming buffers
#define STREAM_BUFFER_SIZE 4096 //(4 * 1024)

// object information needed by the sound code.  Calling code should copy data into here & pass to sound
struct pos_state {
  vector *position; // Where in the world is this object
  matrix *orient;
  vector *velocity;
  int roomnum;
};

// #define MAX_EFFECT_OFFSETS 5

//	sound priority values.
#define SND_PRIORITY_CRITICAL 5 // usually streams have this priority, bumps off any other sounds.
#define SND_PRIORITY_HIGHEST 4
#define SND_PRIORITY_HIGH 3
#define SND_PRIORITY_NORMAL 2
#define SND_PRIORITY_LOW 1
#define SND_PRIORITY_LOWEST 0

struct play_information {

  void *(*m_stream_cback)(void *user_data, int handle, int *size); // Streaming callback
  void *m_stream_data;                                             // passed in
  int m_stream_size;                                               // passed in
  int m_stream_handle;                                             // passed in
  int m_stream_bufsize;                                            // passed in
  void *user_data; // this is passed to the stream callback by the caller that defined this.

  uint8_t sample_skip_interval; // Allows us to skip samples (i.e. simulate lower sampling rates)
  uint8_t priority;             // priority of sound.
  uint16_t m_stream_format;     // passed in

  //	internal data.
  int m_samples_played;

  float samples_per_22khz_sample; // passed in
  float left_volume;
  float right_volume;

  float m_ticks;
};

struct sound_file_info {
  char name[PAGENAME_LEN];
  char used;
  int use_count; // how many buffers does this sound take up.

  uint8_t *sample_8bit; // 8bit sound data
  int16_t *sample_16bit;        // 16bit sound data

  int sample_length;    // Length of sound in samples
  int np_sample_length; // non-padded

};

struct sound_info {
  char name[PAGENAME_LEN];
  char used;

  int sample_index;

  int loop_start;          // Start byte of repeated loop for looping samples
  int loop_end;            // End byte of repeating loop for looping samples
  uint32_t flags;      // 2d/3d, variable frequency
  float max_distance;      // Maximum distance in which a sound is heard
  float min_distance;      // Sound gets no louder at min_distance
  int inner_cone_angle;    // Angle in which sound is played at full base volume
  int outer_cone_angle;    // Angle in which sound is at its lowest base volume
  float outer_cone_volume; // A sounds lowest base volume level
  float import_volume;     // Volume multiplier
};

// Supported sound mixers
#define SOUND_MIXER_SOFTWARE_16 0
#define SOUND_MIXER_DS_16 1
#define SOUND_MIXER_DS_8 2
#define SOUND_MIXER_DS3D_16 3
#define SOUND_MIXER_AUREAL 4       // Unused, outdated 3D sound technology
#define SOUND_MIXER_CREATIVE_EAX 6 // switched because launcher uses 5 as NONE.
#define SOUND_MIXER_NONE 5

// Support sound qualities
#define SQT_NORMAL 0
#define SQT_HIGH 1
// Parameters of the sound library
#define SLF_USE_3D 1     // Use 3d effects
#define SLF_DELTA_FREQ 2 // Use frequency shifts (i.e. water effects)
#define SLF_USE_16_BIT 4 // Use 16bit samples (else 8bit)
#define SLF_USE_22_KHZ 8 // Use 22khz (else 44khz)
#define SLF_PAUSED 16    // Sound library is currently paused
#define SLF_FULL_3D 32   // Full 3d hardware support
#define SLF_MOST_3D 64   // No fully static 3d -- i.e. cockpit type stuff (use 2d instead)
#define SLF_LIGHT_3D 128 // Dynamically updating 3d sounds if sound is longer than a given threshold
#define SLF_GOOD_2D 256  // all linked sounds update position
#define SLF_OK_2D 512    // if a sound is longer than a threshold, it updates

// Sound Properties Flags
#define SPF_LOOPED 1     // Sound is looped
#define SPF_FIXED_FREQ 2 // No doppler shift
#define SPF_OBJ_UPDATE 4 // Sound updates with attached object movements
#define SPF_FOREVER 8    // Always plays in high-level, this flag should be ignored in low-level
#define SPF_PLAYS_EXCLUSIVELY 16
#define SPF_PLAYS_ONCE 32
#define SPF_USE_CONE 64
#define SPF_LISTENER_UPDATE 128 // Sound updates with listener movements
#define SPF_ONCE_PER_OBJ 256

// Sound Instance flags (Move this out of here)
#define SIF_UNUSED 0     // Not a valid sound item
#define SIF_PLAYING_2D 1 // Sound is currently playing
#define SIF_PLAYING_3D 2
#define SIF_OBJ_UPDATE 4
#define SIF_TOO_FAR 8 // We will play it, but it currently too far away(stop sound in low-level)
#define SIF_NO_3D_EFFECTS 16
#define SIF_LOOPING 32
#define SIF_STREAMING_8_M 64
#define SIF_STREAMING_16_M 128
#define SIF_STREAMING_8_S 256
#define SIF_STREAMING_16_S 512
#define SIF_STREAMING (64 | 128 | 256 | 512)

// What is the sound cone linked to (and mask to make it else to look at the important bits)
#define SPFT_CONE_LINK_MASK 0x00000300
#define SPFT_CONE_LINK_OBJECT 0x00000000
#define SPFT_CONE_LINK_TURRET1 0x00000100
#define SPFT_CONE_LINK_TURRET2 0x00000200
#define SPFT_CONE_LINK_TURRET3 0x00000300

// Direction of the sound cone relative to its link (and mask to make it else to look at the important bits)
#define SPFT_CONE_DIR_MASK 0x00000C00
#define SPFT_CONE_DIR_FORWARD 0x00000000
#define SPFT_CONE_DIR_BACKWARD 0x00000400
#define SPFT_CONE_DIR_UPWARD 0x00000800
#define SPFT_CONE_DIR_DOWNWARD 0x00000C00

// Sound kill types
#define SKT_STOP_AFTER_LOOP 0  // Allows a looping sample to play until the end of the sample
#define SKT_STOP_IMMEDIATELY 1 // Stops and cleans up after a sound (For StopAllSounds)
#define SKT_HOLD_UNTIL_STOP 2  // Hold until sound stops.

// Sound Library Internal Error Codes
#define SSL_OK 0
#define SSL_ERROR_GENERIC (-1)
#define SSL_ERROR_SAMPLE_NODATA (-2)
#define SSL_ERROR_STREAMMIXER (-3)

// Sound Status
#define SSF_UNUSED 0
#define SSF_PLAY_NORMAL 1
#define SSF_PLAY_LOOPING 2
#define SSF_PAUSED 4
#define SSF_PLAY_STREAMING 8
#define SSF_BUFFERED_LOOP 64
#define SSF_BUFFERED_STRM 128

#define SBT_PRIMARY 0
#define SBT_2D 1
#define SBT_3D 2

// looping methods
#define DSLOOP_SMART_METHOD 0
#define DSLOOP_BUFFER_METHOD 1
#define DSLOOP_STREAM_METHOD 2

#define DSBUFLOOP_INIT_STEP (-1)
#define DSBUFLOOP_LOOP_STEP 0
#define DSBUFLOOP_FINISH_STEP 1

// used to time threads.

// This is the update rate at which to call sound_mixer::DoFrame()
// (sleep this amount each frame of the thread)
#define DSPB_TICK_INTERVAL .01 // Primary buffer update rate (in seconds)
#define DSPB_TICK_MILLISECONDS (DSPB_TICK_INTERVAL * 1000)


// structure to get and set environment values
#define ENV3DVALF_DOPPLER 1
#define ENV3DVALF_GEOMETRY 2

struct t3dEnvironmentValues {
  int flags; // use flags above

  float doppler_scalar; // values from 0.0f to ???? (1.0f = normal)
};

struct t3dEnvironmentToggles {
  int flags;     // use flags above
  int supported; // returns flag values to inform caller of supported features (doppler, ie.)

  bool doppler;  // state of doppler effects
  bool geometry; // support hardware geometry
};

/////////////////////////////////////////////////////////////////////////////////
// Looping constants

class llsGeometry;

class llsSystem {
protected:
  llsGeometry *m_geometry; // geometry object.
  int m_lib_error_code;    // library error code
  char m_error_text[512];  // text for error.

protected:
  void SetError(int code) { m_lib_error_code = code; };
  void ErrorText(const char *fmt, ...); // error text function called inside library.  a stack is kept of errors
  virtual void CheckForErrors();  // called by sound library every frame to reset error count.

  // Public functions
public:
  llsSystem();
  virtual ~llsSystem() = default;

  // may be called before init (must be to be valid, the card passed here will be initialized in InitSoundLib)
  virtual void SetSoundCard(const char *name) = 0;

  // Starts the sound library, maybe have it send back some information -- 3d support?
  virtual int InitSoundLib(char mixer_type, uint8_t max_sounds_played) = 0;
  // Cleans up after the Sound Library
  virtual void DestroySoundLib() = 0;

  // Locks and unlocks sounds (used when changing play_info data)
  virtual bool LockSound(int sound_uid) = 0;
  virtual bool UnlockSound(int sound_uid) = 0;

  virtual bool SetSoundQuality(char quality) = 0;
  virtual char GetSoundQuality() = 0;
  virtual bool SetSoundMixer(char mixer_type) = 0;
  virtual char GetSoundMixer() = 0;

  // Plays a 2d sound
  virtual int PlaySound2d(play_information *play_info, int sound_index, float volume, float pan, bool f_looped) = 0;
  virtual int PlayStream(play_information *play_info) = 0;

  virtual void SetListener(pos_state *cur_pos) = 0;
  virtual int PlaySound3d(play_information *play_info, int sound_index, pos_state *cur_pos, float master_volume,
                          bool f_looped, float reverb = 0.5f) = 0; //, uint16_t frequency)
  virtual void AdjustSound(int sound_uid, float f_volume, float f_pan, uint16_t frequency) = 0;
  virtual void AdjustSound(int sound_uid, pos_state *cur_pos, float adjusted_volume, float reverb = 0.5f) = 0;

  virtual void StopAllSounds() = 0;

  // Checks if a sound is playing (removes finished sound);
  virtual bool IsSoundInstancePlaying(int sound_uid) = 0;
  virtual int IsSoundPlaying(int sound_index) = 0;

  //	virtual void AdjustSound(int sound_uid, play_information *play_info) = 0;

  // Stops 2d and 3d sounds
  virtual void StopSound(int sound_uid, uint8_t f_immediately = SKT_STOP_IMMEDIATELY) = 0;

  // Pause all sounds/resume all sounds
  virtual void PauseSounds() = 0;
  virtual void ResumeSounds() = 0;
  virtual void PauseSound(int sound_uid) = 0;
  virtual void ResumeSound(int sound_uid) = 0;

  virtual bool CheckAndForceSoundDataAlloc(int sound_file_index) = 0;

  // Begin sound frame
  virtual void SoundStartFrame() = 0;

  // End sound frame
  virtual void SoundEndFrame() = 0;

  // Returns current error code
  int GetLastError() {
    int code = m_lib_error_code;
    m_lib_error_code = 0;
    return code;
  };

  // environmental sound interface
  // volume modifier (0-1), damping(0-1), 1 = complete, 0 = none
  //	decay 0.1 to 100 seconds, how long it takes for a sound to die.
  virtual bool SetGlobalReverbProperties(float volume, float damping, float decay) = 0;

  // set special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void SetEnvironmentValues(const t3dEnvironmentValues *env) = 0;

  // get special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void GetEnvironmentValues(t3dEnvironmentValues *env) = 0;

  // enable special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void SetEnvironmentToggles(const t3dEnvironmentToggles *env) = 0;

  // get states of special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void GetEnvironmentToggles(t3dEnvironmentToggles *env) = 0;

  // returns interface to sound geometry manipulation if available.
  virtual llsGeometry *GetGeometryInterface() { return m_geometry; };
  /////////////////////////////////////////////////////////////////////////////////
  // set auxillary 3d sound properties
  virtual bool SoundPropertySupport() const { return false; };

  // sound obstruction from 0 to 1.0 (1.0  = fully obstructed)
  virtual void SetSoundProperties(int sound_uid, float obstruction){};
};

//	TAKEN FROM SNDLIB SOUNDLOAD.CPP TO SEPARATE CODE REQUIRED BY THE LOWLEVEL SYSTEM AND THE
//	HIGH LEVEL SYSTEM - Samir

#ifndef NEWEDITOR
#define MAX_SOUNDS 1000
#define MAX_SOUND_FILES 1000
extern sound_info Sounds[MAX_SOUNDS];
#else
#include "..\neweditor\ned_Sound.h"
#endif

extern sound_file_info SoundFiles[MAX_SOUND_FILES];

//	loads a sound from a wavefile.
char SoundLoadWaveFile(const char *filename, float percent_volume, int sound_file_index, bool f_high_quality,
                       bool f_load_sample_data, int *e_type = nullptr);

void SoundLoadFree(int sound_file_index);

#endif
