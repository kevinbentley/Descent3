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

 *	Video library.
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <cstdlib>

#include "ddvid.h"
#include "lnxapp.h"

struct tinfo {
  int width, height, bytesperpixel, linewidth;
};

struct tDDVideoInfo {
  // vga_modeinfo *info;
  tinfo *info;
  bool paged;
};

//////////////////////////////////////////////////////////////////////////////
//	Variables

tDDVideoInfo DDVideo_info;
static bool DDVideo_init = false;

//////////////////////////////////////////////////////////////////////////////
//	Prototypes

//////////////////////////////////////////////////////////////////////////////
//	Functions

//	called first to allow fullscreen video access
bool ddvid_Init(char *driver) {
  int subsys_id;

  //	preinitialize system.
  if (!DDVideo_init) {
    DDVideo_info.info = NULL;
    atexit(ddvid_Close);
  } else {
    ddvid_Close();
  }

  DDVideo_init = true;

  // vga_init();
  return true;
}

//	closes ddvid system manually.
void ddvid_Close() {
  if (!DDVideo_init)
    return;

  /*
    if(vga_getcurrentmode()!=TEXT)
      vga_setmode(TEXT);
  */
  DDVideo_init = false;
}

//	sets the appropriate video mode.
bool ddvid_SetVideoMode(int w, int h, int color_depth, bool paged) {
  /*
    ASSERT(DDVideo_init);

    int mode = -1;

    if( (w==640) && (h==480) ){
      switch(color_depth){
      case BPP_8:
        mode = G640x480x256;
        break;
      case BPP_16:
        mode = G640x480x32K;
        break;
      case BPP_24:
        mode = G640x480x64K;
        break;
      case BPP_32:
        mode = G640x480x16M;
        break;
      }
    }else
      if( (w==512) && (h==384) ){
        mode = -1;
      }else
        if( (w==800) && (h==600) ){
          switch(color_depth){
          case BPP_8:
            mode = G800x600x256;
            break;
          case BPP_16:
            mode = G800x600x32K;
            break;
          case BPP_24:
            mode = G800x600x64K;
            break;
          case BPP_32:
            mode = G800x600x16M;
            break;
          }
        }

    if(mode==-1)
      return false;

    if(!vga_hasmode(mode))
      return false;

    DDVideo_info.info = vga_getmodeinfo(mode);

    DDVideo_info.paged = (bool)(DDVideo_info.info->flags&HAVE_RWPAGE);

    if( (paged) && (!(DDVideo_info.paged)) ){
      DDVideo_info.info = NULL;
      Error("Pages not supported by mode %d\n",mode);
      return false;
    }

    vga_setmode(mode);
  */
  return true;
}

//	sets screen handle
void ddvid_SetVideoHandle(unsigned handle) {}
