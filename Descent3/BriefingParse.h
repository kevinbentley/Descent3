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

 * $Logfile: /DescentIII/main/BriefingParse.h $
 * $Revision: 7 $
 * $Date: 4/17/99 6:15p $
 * $Author: Samir $
 *
 *
 *
 * $Log: /DescentIII/main/BriefingParse.h $
 *
 * 7     4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 6     4/16/99 1:51a Jeff
 * include linux fix for stricmp
 *
 * 5     4/14/99 3:56a Jeff
 * fixed case mismatch in #includes
 *
 * 4     1/04/99 12:32p Jeff
 * added support for mission flag parsing
 *
 * 3     9/11/98 6:06p Jeff
 * Briefing Editor completed
 *
 * 2     9/09/98 7:02p Jeff
 * Initial Creation
 *
 * $NoKeywords: $
 */

#ifndef __BRIEFPARSE_H_
#define __BRIEFPARSE_H_

#if defined(__LINUX__) || defined(ANDROID)
#include "linux_fix.h" //for stricmp
#endif

#include "TelComEfxStructs.h"
#include "grdefs.h"

//	Return codes of ParseBriefing
#define PBERR_FILENOTEXIST -1
#define PBERR_NOERR 0

struct tBriefParseCallbacks {
  void (*AddTextEffect)(TCTEXTDESC* desc, char *text, char *description, int id);
  void (*AddBmpEffect)(TCBMPDESC* desc, char *description);
  void (*AddMovieEffect)(TCMOVIEDESC* desc, char *description);
  void (*AddBkgEffect)(TCBKGDESC* desc, char *description);
  void (*AddPolyEffect)(TCPOLYDESC* desc, char *description);
  void (*AddSoundEffect)(TCSNDDESC* desc, char *description);
  void (*AddButtonEffect)(TCBUTTONDESC* desc, char *description, int id);
  void (*StartScreen)(int screen_num, char *description, char *layout, uint32_t mask_set, uint32_t mask_unset);
  void (*EndScreen)();
  bool (*LoopCallback)();
  void (*SetTitle)(char *title);
  void (*SetStatic)(float amount);
  void (*SetGlitch)(float amount);
  void (*AddVoice)(char *filename, int flags,char *description);
};

struct tTextBufferDesc {
  TCTEXTDESC textdesc;
  int text_id;
  int teffect;
  char description[128];
};

class CBriefParse {
public:
  CBriefParse();
  ~CBriefParse();
  void SetCallbacks(tBriefParseCallbacks *cb);
  int ParseBriefing(const char *filename);

private:
  void (*AddTextEffect)(TCTEXTDESC* desc, char *text, char *description, int id);
  void (*AddBmpEffect)(TCBMPDESC* desc, char *description);
  void (*AddMovieEffect)(TCMOVIEDESC* desc, char *description);
  void (*AddBkgEffect)(TCBKGDESC* desc, char *description);
  void (*AddPolyEffect)(TCPOLYDESC* desc, char *description);
  void (*AddSoundEffect)(TCSNDDESC* desc, char *description);
  void (*AddButtonEffect)(TCBUTTONDESC* desc, char *description, int id);
  void (*StartScreen)(int screen_num, char *desc, char *layout, uint32_t mask_set, uint32_t mask_unset);
  void (*EndScreen)();
  bool (*LoopCallback)();
  void (*SetTitle)(char *title);
  void (*SetStatic)(float amount);
  void (*SetGlitch)(float amount);
  void (*AddVoice)(char *filename, int flags, char *description);

  void ParseError(const char *msg, const char *p = NULL);
  const char *ParseComma(const char *p);
  const char *ParseFloat(const char *p, float *f);
  const char *ParseInt(const char *p, int *i);
  const char *ParseString(const char *p, char *buf, int bufsize);
  const char *ParseToken(const char *p, char *buf, int bufsize);
  const char *SkipWhite(const char *p);
  const char *ParseKeyword(const char *p, int *keyword_id);
  bool ParseButtonEffect(const char *p);
  bool ParseTextEffect(const char *p, tTextBufferDesc *tbd);

  int linenum;
  bool parse_error;
};

#endif
