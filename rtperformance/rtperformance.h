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

#ifndef _RUN_TIME_PROFILING_
#define _RUN_TIME_PROFILING_

#include <cstdint>

// uncomment the following if you want to enable Run-time Profiling
#ifndef RELEASE
#define USE_RTP
#endif

#if defined(__LINUX__)
// #if defined(__LINUX__)
#ifdef USE_RTP
#undef USE_RTP // no rtp for now
#endif
#endif

// use INT64 for 64bit integers
#ifdef USE_RTP
#if defined(__LINUX__)
#define INT64 int64_t
#else
#define INT64 signed __int64
#endif
#else
#define INT64 uint8_t
#endif


//		struct of information to be saved per frame (note: use INT64 for timer info)
// -----------------------------------------------------------------------------------
struct tRTFrameInfo {
  INT64 frame_num; // the frame number, used internally
  INT64 renderframe_time;
  INT64 multiframe_time;
  INT64 musicframe_time;
  INT64 ambsound_frame_time;
  INT64 weatherframe_time;
  INT64 playerframe_time;
  INT64 doorframe_time;
  INT64 levelgoal_time;
  INT64 matcenframe_time;
  INT64 objframe_time;
  INT64 aiframeall_time;
  INT64 processkeys_time;
  INT64 normalevent_time;
  INT64 ct_flying_time;
  INT64 ct_aidoframe_time;
  INT64 ct_weaponframe_time;
  INT64 ct_explosionframe_time;
  INT64 ct_debrisframe_time;
  INT64 ct_splinterframe_time;
  INT64 mt_physicsframe_time;
  INT64 mt_walkingframe_time;
  INT64 mt_shockwave_time;
  INT64 obj_doeffect_time;
  INT64 obj_move_player_time;
  INT64 obj_d3xint_time;
  INT64 obj_objlight_time;
  INT64 cycle_anim;
  INT64 vis_eff_move;
  INT64 phys_link;
  INT64 obj_do_frm;
  INT64 fvi_time;

  int texture_uploads;
  int polys_drawn;
  int fvi_calls;
  float frame_time; // how long the frame took.  A float because it's already calc'd so we might as well save it
};

//		Flags for Runtime Performance Counters (these are 64 bit)
// --------------------------------------------------------------------
#define RTI_FRAMETIME 0x00000001
#define RTI_RENDERFRAMETIME 0x00000002
#define RTI_MULTIFRAMETIME 0x00000004
#define RTI_MUSICFRAMETIME 0x00000008
#define RTI_AMBSOUNDFRAMETIME 0x00000010
#define RTI_WEATHERFRAMETIME 0x00000020
#define RTI_PLAYERFRAMETIME 0x00000040
#define RTI_DOORFRAMETIME 0x00000080
#define RTI_LEVELGOALTIME 0x00000100
#define RTI_MATCENFRAMETIME 0x00000200
#define RTI_OBJFRAMETIME 0x00000400
#define RTI_AIFRAMETIME 0x00000800
#define RTI_PROCESSKEYTIME 0x00001000
#define RTI_TEXTUREUPLOADS 0x00002000
#define RTI_POLYSDRAWN 0x00004000

//		Macros to be used internally and externally
// --------------------------------------------------

#ifndef USE_RTP

#define RTP_CLOCKTOSECONDS(c1, c2, t)
#define RTP_CLOCKSECONDS(c, t)
#define RTP_RECORDVALUE(member, value)
#define RTP_INCRVALUE(member, amount)
#define RTP_DECRVALUE(member, amount)
#define RTP_GETVALUE(member, value)
#define RTP_STARTTIME(member)
#define RTP_tSTARTTIME(member, time)
#define RTP_ENDTIME(member)
#define RTP_tENDTIME(member, time)
#define RTP_GETCLOCK(time)
#define RTP_STARTINCTIME(member)
#define RTP_ENDINCTIME(member)
#define RTP_ENABLEFLAGS(flags)
#define RTP_DISABLEFLAGS(flags)

#else

#define RTP_ENABLEFLAGS(flags) rtp_EnableFlags(flags)

#define RTP_DISABLEFLAGS(flags) rtp_EnableFlags(flags)

// given 2 clocks (INT64's) it will return the time in seconds between them (double)
// (internal use)
// c1 = start time
// c2 = end time
// t = time in seconds
#define RTP_CLOCKTOSECONDS(c1, c2, t)                                                                                  \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      INT64 diff = (c2) - (c1);                                                                                        \
      t = ((double)diff) / ((double)Runtime_performance_clockfreq);                                                    \
    }                                                                                                                  \
  } while (0)

// given a clock time, it will convert it to seconds
#define RTP_CLOCKSECONDS(c, t)                                                                                         \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      t = ((double)c) / ((double)Runtime_performance_clockfreq);                                                       \
    }                                                                                                                  \
  } while (0)

// sets a value of a member of the current tRTFrameInfo frame
// (external use)
// member = the member of the tRTFrameInfo to set
// value = the value to set it to
#define RTP_RECORDVALUE(member, value)                                                                                 \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member = (value);                                                                                \
    }                                                                                                                  \
  } while (0)

// increments a value of a member of the current tRTFrameInfo frame
// (external use)
// member = the member of the tRTFrameInfo to increment
// amount = how much to increment it
#define RTP_INCRVALUE(member, amount)                                                                                  \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member += (amount);                                                                              \
    }                                                                                                                  \
  } while (0)

// decrements a value of a member of the current tRTFrameInfo frame
// (external use)
// member = the member of the tRTFrameInfo to decrement
// amount = how much to decrement it
#define RTP_DECRVALUE(member, amount)                                                                                  \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member -= (amount);                                                                              \
    }                                                                                                                  \
  } while (0)

// returns the value of a member of the current tRTFrameInfo frame
// (external use)
// member = the member to retrieve
// value = where to store the value
#define RTP_GETVALUE(member, value)                                                                                    \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      value = RTP_SingleFrame.member;                                                                                  \
    }                                                                                                                  \
  } while (0)

// starts a frame time calculation for a time member of the tRTFrameInfo frame
// this version calls the clock to get the current time
// member = member to start recording time on
#define RTP_STARTTIME(member)                                                                                          \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member = rtp_GetClock();                                                                         \
    }                                                                                                                  \
  } while (0)

// starts a frame time calculation given a time to start it with (similar to the above
// except you give it the starting time).  This should be used (along with
// RTP_tENDTIME(member,time)) in places where you do a bunch of frame times in a row
// to reduce the number of calls to rtp_GetClock(), however, this way will give
// a few cycles off, compared to the RTP_STARTTIME(member)/RTP_ENDTIME(member) way
// member = member to start recording time on
#define RTP_tSTARTTIME(member, time)                                                                                   \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member = time;                                                                                   \
    }                                                                                                                  \
  } while (0)

// ends a frame time calculation for a member of tRTFrameInfo frame
// member = member to stop recording time for
#define RTP_ENDTIME(member)                                                                                            \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member = rtp_GetClock() - RTP_SingleFrame.member;                                                \
    }                                                                                                                  \
  } while (0)

// same as above, but will return the time that it stopped the recording time
#define RTP_tENDTIME(member, time)                                                                                     \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      time = rtp_GetClock();                                                                                           \
      RTP_SingleFrame.member = time - RTP_SingleFrame.member;                                                          \
    }                                                                                                                  \
  } while (0)

// returns the current clock time
#define RTP_GETCLOCK(time)                                                                                             \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      time = rtp_GetClock();                                                                                           \
    }                                                                                                                  \
  } while (0)

// Starts a frame time calculation, but when ending the frame, it will increment the time by
// the difference instead of just setting it
// RTP_STARTINCTIME and RTP_ENDINCTIME must be in the same scope
#define RTP_STARTINCTIME(member)                                                                                       \
  INT64 __start_time_;                                                                                                 \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      __start_time_ = rtp_GetClock();                                                                                  \
    }                                                                                                                  \
  } while (0)

// Ends a frame time calculation and increments the member by the time for that frame
#define RTP_ENDINCTIME(member)                                                                                         \
  do {                                                                                                                 \
    if (Runtime_performance_enabled) {                                                                                 \
      RTP_SingleFrame.member += (rtp_GetClock() - __start_time_);                                                      \
    }                                                                                                                  \
  } while (0)

#endif

//		Internal Global Vars
// ------------------------------
extern tRTFrameInfo RTP_SingleFrame;
extern INT64 Runtime_performance_clockfreq;
extern uint8_t Runtime_performance_enabled;

/*
void rtp_Init
        This function initilizes the runtime performance system so it's ready to be used
*/
void rtp_Init(void);

/*
void rtp_EnableFlags
        This function enables the performance profiling of whatever flags you pass in
*/
void rtp_EnableFlags(INT64 flags);

/*
void rtp_DisableFlags
        This function disables the performance profiling of whatever flags you pass in
*/
void rtp_DisableFlags(INT64 flags);

/*
void rtp_StartLog
        Calling this function will reset the log and start a new log, recording immediatly
*/
void rtp_StartLog(void);

/*
void rtp_StopLog
        Calling this function will stop the currently processing log and write it out to
        file.
*/
void rtp_StopLog(void);

/*
void rtp_PauseLog
        Calling this function will pause the log recording until rtp_ResumeLog is called
*/
void rtp_PauseLog(void);

/*
void rtp_ResumeLog
        Calling this will resume a paused log, starting at where it left off
*/
void rtp_ResumeLog(void);

/*
void rtp_RecordFrame
        Calling this will record the data of the frame into the internal log, and prepare for
        the next frame
*/
void rtp_RecordFrame(void);

/*
INT64 rtp_GetClock
        Returns the current hi-resolution clock value...no checking for overflow
*/
INT64 rtp_GetClock(void);

/*
void rtp_WriteBufferLog
        Writes the buffer of frames to file...
*/
void rtp_WriteBufferLog(void);

#endif
