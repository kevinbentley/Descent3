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

 * $Logfile: /DescentIII/main/audiotaunts.h $
 * $Revision: 4 $
 * $Date: 4/29/99 11:02p $
 * $Author: Jeff $
 *
 * in-game audio taunt API
 *
 * $Log: /DescentIII/main/audiotaunts.h $
 *
 * 4     4/29/99 11:02p Jeff
 * added the ability for the server to set audio taunt delay time via
 * command line option and/or dedicated server console
 *
 * 3     3/22/99 6:20p Jeff
 * added 2 more audio taunts.  a mulitplayer event when someone plays an
 * audio taunt.  option to disable audio taunts.
 *
 * 2     1/27/99 5:47p Jeff
 * audio taunts implemented!
 *
 * 1     1/27/99 1:31a Jeff
 *
 * $NoKeywords: $
 */

#ifndef __AUDIO_TAUNT_H_
#define __AUDIO_TAUNT_H_

// Error codes:
#define TAUNTIMPERR_NOERROR 0
#define TAUNTIMPERR_NOTFOUND 1
#define TAUNTIMPERR_NOTRIFF 2
#define TAUNTIMPERR_NOTWAVE 3
#define TAUNTIMPERR_INVALIDFILE 4
#define TAUNTIMPERR_NOTSUPPORTED 5
#define TAUNTIMPERR_INVALIDCHANNELS 6
#define TAUNTIMPERR_INVALIDSAMPLES 7
#define TAUNTIMPERR_INVALIDBITDEPTH 8
#define TAUNTIMPERR_NODATA 9
#define TAUNTIMPERR_OSFEXISTS 10
#define TAUNTIMPERR_INTERNALERR 11
#define TAUNTIMPERR_COMPRESSIONFAILURE 12
#define TAUNTIMPERR_OUTOFMEM 13
#define TAUNTIMPERR_NOOPENOSF 14

//	taunt_GetError
//
//	Returns more information about a failed import
int taunt_GetError(void);

//	taunt_GetErrorString
//	Returns a string describing an error code
const char *taunt_GetErrorString(int error);

//	taunt_ImportWave
//	Given a fully qualified wave_filename (location of a .wav) and a fully
//	qualified outputfilename (where the .osf is to go), it will convert and
//	compress the wav file.
bool taunt_ImportWave(char *wave_filename, char *outputfilename);

//	taunt_PlayTauntFile
//
//	Given a path to an .osf file, it will play it
bool taunt_PlayTauntFile(const char *filename);

//	taunt_PlayPlayerTaunt
//
//	Given a playernum, and which taunt (0 or 1) it will play that taunt
bool taunt_PlayPlayerTaunt(int pnum, int index);

// taunt_AreEnabled
//
//	Returns true if taunts are enabled
bool taunt_AreEnabled(void);

// taunt_Enable
//
//	Enables/Disables audio_taunts for the player
void taunt_Enable(bool enable);

// taunt_DelayTime()
//
//	Returns the delay time between taunts
float taunt_DelayTime(void);

// taunt_SetDelayTime()
//
//	Sets the taunt delay time
void taunt_SetDelayTime(float t);

#endif
