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

 * $Logfile: /DescentIII/main/gamesave.cpp $
 * $Revision: 75 $
 * $Date: 9/05/01 12:26p $
 * $Author: Matt $
 *
 *
 *
 * $Log: /DescentIII/main/gamesave.cpp $
 *
 * 75    9/05/01 12:26p Matt
 * Flush low-level mouse click queue before bringing up buddy, save, and
 * load menus since these menus would otherwise get clicks that occurred
 * before they existed.
 *
 * 74    4/19/00 5:14p Matt
 * From Duane for 1.4
 * Mac-only change: ensure dialog is cleared after saving screenshot.
 *
 * 73    10/22/99 10:57a Matt
 * Mac merge
 *
 * 72    7/22/99 11:46a Chris
 *
 * 71    7/21/99 7:17p Chris
 * Fixed an attach related crash in the load/save game code
 *
 * 70    5/24/99 7:23p Samir
 * pass current string length to DoEditDialog.  crash otherwise for long
 * savegames.
 *
 * 69    5/21/99 11:14p Samir
 * savegames save hud timer and special text states. restore too.
 *
 * 68    5/20/99 2:48a Matt
 * Auto-waypoints now stored & used per player.  Manual waypoints will all
 * players, once Jason makes it work.
 *
 * 67    5/12/99 6:01p Jeff
 * flip order of saving/loading objects and players
 *
 * 66    5/12/99 12:25p Kevin
 * save & restore Current_mission.game_state_flags
 *
 * 65    5/06/99 6:11p Kevin
 * fixes for save/load game syste. Also require CD again and added some
 * heat.net stuff
 *
 * 64    5/02/99 7:18p Samir
 * changed titles on messageboxes and don't put up loadgame dialog if
 * there are no savegames.
 *
 * 63    4/30/99 3:05p Kevin
 * doh
 *
 * 62    4/30/99 3:03p Kevin
 * improved times restored count
 *
 * 61    4/29/99 11:25a Kevin
 * Added room damage to save game
 *
 * 60    4/28/99 2:14a Samir
 * save and load Game messages in savegame.
 *
 * 59    4/26/99 4:33p Samir
 * made stringtable change.
 *
 * 58    4/23/99 10:28p Kevin
 * fixed problems with minimal install and demo/savegames
 *
 * 57    4/23/99 8:28p Kevin
 * trying to get doors working in save/load games
 *
 * 56    4/23/99 7:33p Kevin
 * save weather effects and reset the HUD to show the correct ship
 *
 * 55    4/22/99 4:13p Matt
 * Deleted sounds array from the object struct, since it was never used.
 *
 * 54    4/20/99 11:45a Samir
 * added autosave
 *
 * 53    4/16/99 12:39a Matt
 * Disable Soar on non-Windows systems.
 *
 * 52    4/15/99 5:40p Samir
 * save current music region and restore it.
 *
 * 51    4/15/99 1:39a Jeff
 * changes for linux compile
 *
 * 50    4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 49    4/06/99 10:44p Samir
 * Fixed residue from changes to UID_OK and UID_CANCEL.
 *
 * 48    4/05/99 10:54a Matt
 * Added auto-waypoint system
 *
 * 47    3/23/99 6:09p Kevin
 * Marker text saved
 *
 * 46    3/23/99 10:24a Samir
 * check valid bitmap handle in LoadGame.
 *
 * 45    3/22/99 5:12p Samir
 * added snapshot to savegame.
 *
 * 44    3/11/99 9:09p Jeff
 * fixed remaining known bugs in demo system (DemoWriteObjCreate being
 * called twice and </<= problems with
 * Highest_room_index/Highest_object_index).
 *
 * 43    3/10/99 6:20p Jeff
 * many fixes to demo system.  Fixed IGC so cameras move...fixed osiris to
 * be restored correctly, and it handles errors on restore
 *
 * 42    3/10/99 2:25p Kevin
 * Save/Load and Demo file fixes
 *
 * 41    3/08/99 10:52a Jason
 * save/load texture changes on room faces
 *
 * 40    3/04/99 6:30p Jeff
 * saves out current waypoint and matcens
 *
 * 39    3/04/99 6:19p Kevin
 * was using the wrong string
 *
 * 38    3/03/99 7:20p Jeff
 * save/restore some ai path information
 *
 * 37    3/03/99 12:56a Kevin
 * Added some HUD messages. Needs to be localized.
 *
 * 36    3/02/99 6:39p Jeff
 * level goals working in save/load game
 *
 * 35    3/02/99 4:41p Jeff
 * Fixed inventory save/load
 *
 * 34    3/02/99 2:49p Samir
 * will not allow savegames with no names.
 *
 * 33    3/02/99 1:48p Kevin
 * Fixed collision with external rooms
 *
 * 32    3/01/99 9:03p Kevin
 * OEM Beta 4
 *
 * 31    3/01/99 4:38p Samir
 * made done button cancel in gamesave menus.
 *
 * 30    3/01/99 11:41a Kevin
 * More progress...
 *
 * 29    3/01/99 4:59a Samir
 * redid load and save game menus.
 *
 * 28    2/28/99 10:50p Kevin
 *
 * 26    2/27/99 4:41p Kevin
 * Fixed(?) some load/save bugs
 *
 * 25    2/26/99 6:48p Kevin
 * Fixes to load/save game, and change minor version for OEM beta 3
 *
 * 24    2/24/99 9:57a Kevin
 * Added error messages if you try to save a game while in multi
 *
 * 23    2/23/99 9:58p Kevin
 * trying to get attach working
 *
 * 22    2/23/99 5:13p Kevin
 * Fixed it so objects with lightmaps will retain their lightmaps when a
 * game is saved & loaded.
 *
 * 21    2/22/99 2:04p Jason
 * added different damages for players and generics
 *
 * 20    2/07/99 1:17a Jeff
 * peppered UI dialogs that were missing NEWUIRES_FORCEQUIT to handle it
 *
 * 19    2/02/99 12:43p Kevin
 * Fixes to the Save/Load game system, and the demo system to work with
 * the new OSIRIS
 *
 * 18    1/29/99 12:47p Matt
 * Rewrote the doorway system
 *
 * 17    1/23/99 10:10p Kevin
 * Added the start of osiris support into the demo system
 *
 * 16    1/22/99 8:53p Jeff
 * added custom-default script overrides
 *
 * 15    1/18/99 2:46p Matt
 * Combined flags & flags2 fields in object struct
 *
 * 14    1/13/99 6:37a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 13    1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 12    11/11/98 2:46p Kevin
 * Demo recording system work
 *
 * 11    10/06/98 5:45p Kevin
 * Added new configuration for demo
 *
 * 10    9/22/98 3:56p Samir
 * special demo code doesn't allow pilot and mission stuff.
 *
 * 9     8/25/98 3:44p Samir
 * make sure and return false if no save games.
 *
 * 8     8/20/98 6:45p Samir
 * new interfaces for load-save.
 *
 * 7     8/20/98 10:52a Samir
 * fixed some ui probs
 *
 * 6     8/19/98 5:35p Samir
 * saved triggers, spew, viseffects, weapons, room data xcept texture per
 * face changes, one real strange bug where robots in the same room as you
 * don't appear but fire at you.
 *
 * 5     8/18/98 3:50p Matt
 * Maybe fixed bug
 *
 * 4     8/18/98 3:05p Samir
 * save game with no weapons or fireballs.
 *
 * 3     8/18/98 11:17a Samir
 * for the sake of the team.
 *
 * 2     8/18/98 1:12a Samir
 * rudimentary savegame.  pretty damn buggy when loading.
 *
 * $NoKeywords: $
 */

#include "gamesave.h"
#include "descent.h"
#include "newui.h"
#include "cfile.h"
#include "Mission.h"
#include "gamesequence.h"
#include "gameevent.h"
#include "gameloop.h"
#include "game.h"
#include "stringtable.h"
#include "object.h"
#include "objinfo.h"
#include "gametexture.h"
#include "bitmap.h"
#include "ddio.h"
#include "door.h"
#include "doorway.h"
#include "ship.h"
#include "soar.h"
#include "hud.h"
#include "weapon.h"
#include "viseffect.h"
#include "room.h"
#include "trigger.h"
#include "spew.h"
#include "osiris_dll.h"
#include "levelgoal.h"
#include "aistruct.h"
#include <string.h>
#include "matcen.h"
#include "hud.h"
#include "marker.h"
#include "d3music.h"
#include "weather.h"

// function prototypes.

void SGSSnapshot(CFILE *fp);

#define SAVE_HOTSPOT_ID 0x1000
#define N_SAVE_SLOTS 8
#define GAMESAVE_WND_W 448
#define GAMESAVE_WND_H 384
#define GAMESAVE_SLOT_W 336
#define GAMESAVE_SLOT_H 18
#define GAMESAVE_SLOT_H2 22
#define GAMESAVE_HELP_Y 2
#define GAMESAVE_HELP_X 12
#define GAMESAVE_SLOT_Y 140
#define GAMESAVE_SLOT_Y2 110
#define GAMESAVE_SLOT_X 12

// we need this directory to load the savegame from
static char LGS_Path[_MAX_PATH];

extern int Times_game_restored;
// available for all.
int Quicksave_game_slot = -1;

void QuickSaveGame() {
  if (Game_mode & GM_MULTI) {
    DoMessageBox(TXT_ERROR, TXT_CANT_SAVE_MULTI, MSGBOX_OK);
    return;
  }

#ifdef _DEBUG
  if (GetFunctionMode() == EDITOR_GAME_MODE || !Current_mission.filename) {
    DoMessageBox(TXT_ERROR, "You need to be playing a mission.", MSGBOX_OK);
    return;
  }
#endif

  if (Quicksave_game_slot == -1) {
    SaveGameDialog();
  } else {
    // verify savegame still exists in the appropriate slot, if not just run dialog, if so then save
    char filename[PSFILENAME_LEN + 1];
    char pathname[_MAX_PATH];
    char desc[GAMESAVE_DESCLEN + 1];
    FILE *fp;
    int i;

    i = Quicksave_game_slot;

    snprintf(filename, sizeof(filename), "saveg00%d", i);
    ddio_MakePath(pathname, Base_directory, "savegame", filename, NULL);

    fp = fopen(pathname, "rb");
    if (fp) {
      // slot valid, save here.
      fclose(fp);
      if (GetGameStateInfo(pathname, desc)) {
        if (SaveGameState(pathname, desc)) {
          AddHUDMessage(TXT_QUICKSAVE);
          return; // we're okay. game saved. put up hud message?
        }
        DoMessageBox(TXT_ERROR, TXT_SAVEGAMEFAILED, MSGBOX_OK);
      }
    }
    Quicksave_game_slot = -1;
    SaveGameDialog();
  }
}

void SaveGameDialog() {
  newuiTiledWindow wnd;
  newuiSheet *sheet;
  int i, res;

  char savegame_dir[_MAX_PATH];
  char pathname[_MAX_PATH];
  char filename[PSFILENAME_LEN + 1];
  char desc[GAMESAVE_DESCLEN + 1];
  bool occupied_slot[N_SAVE_SLOTS];

  if (Game_mode & GM_MULTI) {
    DoMessageBox(TXT_ERROR, TXT_CANT_SAVE_MULTI, MSGBOX_OK);
    return;
  }

#ifdef _DEBUG
  if (!Current_mission.filename) {
    DoMessageBox(TXT_ERROR, "You need to be playing a mission.", MSGBOX_OK);
    return;
  }
#endif

  // setup paths.
  ddio_MakePath(savegame_dir, Base_directory, "savegame", NULL);
  //	ddio_MakePath(pathname, savegame_dir, "*.sav", NULL); -unused

  // create savegame directory if it didn't exist before.
  if (!ddio_DirExists(savegame_dir)) {
    if (!ddio_CreateDir(savegame_dir)) {
      DoMessageBox(TXT_ERROR, TXT_ERRCREATEDIR, MSGBOX_OK);
      return;
    }
  }

  // open window
  wnd.Create(TXT_SAVEGAME, 0, 0, GAMESAVE_WND_W, GAMESAVE_WND_H);
  wnd.Open();
  sheet = wnd.GetSheet();

  sheet->NewGroup(NULL, GAMESAVE_HELP_X, GAMESAVE_HELP_Y);
  sheet->AddText(TXT_SAVEGAMEHELP);

  sheet->NewGroup(NULL, GAMESAVE_SLOT_X, GAMESAVE_SLOT_Y2);
  // generate save slots.
  for (i = 0; i < N_SAVE_SLOTS; i++) {
    FILE *fp;
    bool ingroup = (i == 0 || i == (N_SAVE_SLOTS - 1)) ? true : false;

    snprintf(filename, sizeof(filename), "saveg00%d", i);
    ddio_MakePath(pathname, savegame_dir, filename, NULL);

    occupied_slot[i] = false;

    fp = fopen(pathname, "rb");
    if (fp) {
      fclose(fp);

      if (GetGameStateInfo(pathname, desc)) {
        sheet->AddHotspot(desc, GAMESAVE_SLOT_W, GAMESAVE_SLOT_H2, SAVE_HOTSPOT_ID + i, ingroup);
        occupied_slot[i] = true;
      } else {
        sheet->AddHotspot(TXT_ILLEGALSAVEGAME, GAMESAVE_SLOT_W, GAMESAVE_SLOT_H2, SAVE_HOTSPOT_ID + i, ingroup);
      }
    } else {
      sheet->AddHotspot(TXT_EMPTY, GAMESAVE_SLOT_W, GAMESAVE_SLOT_H2, SAVE_HOTSPOT_ID + i, ingroup);
    }
  }

  sheet->NewGroup(NULL, GAMESAVE_WND_W - 148, GAMESAVE_WND_H - 100);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);

  // Mouse clicks from gameplay will be read by the dialog without this flush
  ddio_MouseQueueFlush();

  // do ui.
  do {
    res = wnd.DoUI();
    if (res == NEWUIRES_FORCEQUIT) {
      break;
    } else if (res >= SAVE_HOTSPOT_ID && res < (SAVE_HOTSPOT_ID + N_SAVE_SLOTS)) {
      newuiHotspot *hot;
      const char *hot_desc;
      int slot = res - SAVE_HOTSPOT_ID;
      bool do_save = false;

      // fill edit box with current description.
      hot = (newuiHotspot *)sheet->GetGadget(res);
      ASSERT(hot);
      hot_desc = hot->GetTitle();

      if (occupied_slot[slot]) {
        strcpy(desc, hot_desc);
      } else {
        desc[0] = 0;
      }

    reenter_save:
      if (DoEditDialog(TXT_DESCRIPTION, desc, sizeof(desc) - 1)) {
        // perform check for duplicate names
        // do not allow for empty or space only descriptions
        if (strlen(desc) == 0) {
          DoMessageBox("", TXT_SAVEGAMENAME, MSGBOX_OK);
          goto reenter_save;
        }
        for (i = 0; i < N_SAVE_SLOTS; i++) {
          hot = (newuiHotspot *)sheet->GetGadget(SAVE_HOTSPOT_ID + i);
          hot_desc = hot->GetTitle();

          if (occupied_slot[i] && stricmp(hot_desc, desc) == 0 && slot != i) {
            DoMessageBox("", TXT_SAVEGAMEDUP, MSGBOX_OK);
            goto reenter_save;
          }
        }

        do_save =
            occupied_slot[slot] ? (DoMessageBox(TXT_WARNING, TXT_OVERWRITESAVE, MSGBOX_YESNO) ? true : false) : true;

        if (do_save) {
          snprintf(filename, sizeof(filename), "saveg00%d", slot);
          ddio_MakePath(pathname, savegame_dir, filename, NULL);
          if (!SaveGameState(pathname, desc)) {
            DoMessageBox("", TXT_SAVEGAMEFAILED, MSGBOX_OK);
          } else {
            AddHUDMessage(TXT_QUICKSAVE);
            res = UID_CANCEL;
            Quicksave_game_slot = slot;
          }
        }
      }
    }
  } while (res != UID_CANCEL);

  wnd.Close();
  wnd.Destroy();
}

////////////////////////////////////////////////////////////////////////////////////////
struct tLoadGameDialogData {
  int cur_slot;
  chunked_bitmap chunk;
};

#if defined(__LINUX__)
void LoadGameDialogCB(newuiTiledWindow *wnd, void *data)
#else
void __cdecl LoadGameDialogCB(newuiTiledWindow *wnd, void *data)
#endif
{
  tLoadGameDialogData *cb_data = (tLoadGameDialogData *)data;
  UIGadget *cur_gadget;
  int id;

  cur_gadget = wnd->GetFocus();

  for (id = SAVE_HOTSPOT_ID; id < (SAVE_HOTSPOT_ID + N_SAVE_SLOTS); id++) {
    if (cur_gadget->GetID() == id) {
      break;
    }
  }

  if (id < (SAVE_HOTSPOT_ID + N_SAVE_SLOTS) && id != cb_data->cur_slot) {
    // new bitmap to be displayed!
    char filename[PSFILENAME_LEN + 1];
    char pathname[_MAX_PATH];
    char savegame_dir[_MAX_PATH];
    char desc[GAMESAVE_DESCLEN + 1];
    int bm_handle;

    if (cb_data->chunk.bm_array) {
      bm_DestroyChunkedBitmap(&cb_data->chunk);
    }

    mprintf(0, "savegame slot=%d\n", id - SAVE_HOTSPOT_ID);

    ddio_MakePath(savegame_dir, Base_directory, "savegame", NULL);
    snprintf(filename, sizeof(filename), "saveg00%d", (id - SAVE_HOTSPOT_ID));
    ddio_MakePath(pathname, savegame_dir, filename, NULL);

    if (GetGameStateInfo(pathname, desc, &bm_handle)) {
      if (bm_handle > 0) {
        bm_CreateChunkedBitmap(bm_handle, &cb_data->chunk);
        bm_FreeBitmap(bm_handle);
      }
    }
    cb_data->cur_slot = id;
  }

  // draw bitmap if there is one
  if (cb_data->chunk.bm_array) {
    UIBitmapItem bm_item;
    int x, y;
    bm_item.set_chunked_bitmap(&cb_data->chunk);
    x = (wnd->W() - bm_item.width()) / 2;
    y = (wnd->H() - bm_item.height()) / 4;
    bm_item.draw(x, y);
  }
}

bool LoadGameDialog() {
  tLoadGameDialogData lgd_data;
  newuiTiledWindow wnd;
  newuiSheet *sheet;
  int i, res;
  bool retval = true;

  char savegame_dir[_MAX_PATH];
  char pathname[_MAX_PATH];
  char filename[PSFILENAME_LEN + 1];
  char desc[GAMESAVE_DESCLEN + 1];
  bool occupied_slot[N_SAVE_SLOTS], loadgames_avail = false;

  if (Game_mode & GM_MULTI) {
    DoMessageBox(TXT_ERROR, TXT_CANT_LOAD_MULTI, MSGBOX_OK);
    return false;
  }

  // setup paths.
  ddio_MakePath(savegame_dir, Base_directory, "savegame", NULL);
  ddio_MakePath(pathname, savegame_dir, "*.sav", NULL);

  // create savegame directory if it didn't exist before.
  if (!ddio_DirExists(savegame_dir)) {
    DoMessageBox(TXT_ERROR, TXT_ERRNOSAVEGAMES, MSGBOX_OK);
    return false;
  }

  // open window
  wnd.Create(TXT_LOADGAME, 0, 0, GAMESAVE_WND_W, GAMESAVE_WND_H);
  wnd.Open();
  sheet = wnd.GetSheet();

  sheet->NewGroup(NULL, GAMESAVE_HELP_X, GAMESAVE_HELP_Y);
  sheet->AddText(TXT_LOADGAMEHELP);

  sheet->NewGroup(NULL, GAMESAVE_SLOT_X, GAMESAVE_SLOT_Y);

  // generate save slots.
  lgd_data.cur_slot = SAVE_HOTSPOT_ID;
  lgd_data.chunk.bm_array = NULL;

  for (i = 0; i < N_SAVE_SLOTS; i++) {
    FILE *fp;
    bool ingroup = (i == 0 || i == (N_SAVE_SLOTS - 1)) ? true : false;

    snprintf(filename, sizeof(filename), "saveg00%d", i);
    ddio_MakePath(pathname, savegame_dir, filename, NULL);

    occupied_slot[i] = false;

    fp = fopen(pathname, "rb");
    if (fp) {
      int bm_handle;
      int *pbm_handle;
      fclose(fp);

      if (lgd_data.cur_slot == (SAVE_HOTSPOT_ID + i)) {
        pbm_handle = &bm_handle;
      } else {
        pbm_handle = NULL;
      }

      if (GetGameStateInfo(pathname, desc, pbm_handle)) {
        sheet->AddHotspot(desc, GAMESAVE_SLOT_W, GAMESAVE_SLOT_H, SAVE_HOTSPOT_ID + i, ingroup);
        occupied_slot[i] = true;
        loadgames_avail = true;

        // create chunk
        if (pbm_handle && bm_handle > 0) {
          if (lgd_data.chunk.bm_array) {
            bm_DestroyChunkedBitmap(&lgd_data.chunk);
          }
          bm_CreateChunkedBitmap(bm_handle, &lgd_data.chunk);
          bm_FreeBitmap(bm_handle);
        }
      } else {
        sheet->AddHotspot(TXT_ILLEGALSAVEGAME, GAMESAVE_SLOT_W, GAMESAVE_SLOT_H, SAVE_HOTSPOT_ID + i, ingroup);
      }
    } else {
      sheet->AddHotspot(TXT_EMPTY, GAMESAVE_SLOT_W, GAMESAVE_SLOT_H, SAVE_HOTSPOT_ID + i, ingroup);
    }
  }

  if (!loadgames_avail) {
    wnd.Close();
    DoMessageBox("", TXT_ERRNOSAVEGAMES, MSGBOX_OK);
    wnd.Open();
    retval = false;
    goto loadgame_fail;
  }

  sheet->NewGroup(NULL, GAMESAVE_WND_W - 148, GAMESAVE_WND_H - 100);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);

  wnd.SetData(&lgd_data);
  wnd.SetOnDrawCB(LoadGameDialogCB);

  // Mouse clicks from gameplay will be read by the dialog without this flush
  ddio_MouseQueueFlush();

  // do ui.
  do {
    res = wnd.DoUI();
    if (res == NEWUIRES_FORCEQUIT) {
      retval = false;
      break;
    } else if (res >= SAVE_HOTSPOT_ID && res < (SAVE_HOTSPOT_ID + N_SAVE_SLOTS)) {
      int slot = res - SAVE_HOTSPOT_ID;

      if (occupied_slot[slot]) {
        snprintf(filename, sizeof(filename), "saveg00%d", slot);
        ddio_MakePath(pathname, savegame_dir, filename, NULL);
        strcpy(LGS_Path, pathname);
        SetGameState(GAMESTATE_LOADGAME);
        res = UID_CANCEL;
      }
    } else if (res == UID_CANCEL) {
      retval = false;
    }
  } while (res != UID_CANCEL);

loadgame_fail:
  if (lgd_data.chunk.bm_array) {
    bm_DestroyChunkedBitmap(&lgd_data.chunk);
  }

  wnd.Close();
  wnd.Destroy();

  return retval;
}

//////////////////////////////////////////////////////////////////////////////

// loads savegame as specified from LoadGameDialog.
bool LoadCurrentSaveGame() {
  int retval = LoadGameState(LGS_Path);
  if (retval != LGS_OK) {
    Int3();
    DoMessageBox(TXT_ERROR, TXT_LOADGAMEFAILED, MSGBOX_OK);
    return false;
  }
  AddHUDMessage(TXT_GAMERESTORED);
  return true;
}

//////////////////////////////////////////////////////////////////////////////

//	give a description and slot number (0 to GAMESAVE_SLOTS-1)
bool SaveGameState(const char *pathname, const char *description) {
  CFILE *fp;
  char buf[GAMESAVE_DESCLEN + 1];
  int16_t pending_music_region;

  fp = cfopen(pathname, "wb");
  if (!fp)
    return false;

  // Delete the old games restored count.
  char countpath[_MAX_PATH * 2];
  strcpy(countpath, pathname);
  strcat(countpath, ".cnt");
  CFILE *countfp;
  countfp = cfopen(countpath, "wb");
  if (countfp) {
    cf_WriteInt(countfp, Times_game_restored);
    cfclose(countfp);
  }

  //	save out header
  START_VERIFY_SAVEFILE(fp);
  ASSERT(strlen(description) < sizeof(buf));
  strcpy(buf, description);
  cf_WriteBytes((uint8_t *)buf, sizeof(buf), fp);
  cf_WriteShort(fp, GAMESAVE_VERSION);

  SGSSnapshot(fp); // Save snapshot? MUST KEEP THIS HERE.

  //	write out translation tables
  SGSXlateTables(fp);

  //	write out gamemode information

  //	write out mission level information
  cf_WriteShort(fp, (int16_t)Current_mission.cur_level);

  if (Current_mission.filename && (stricmp("d3_2.mn3", Current_mission.filename) == 0)) {
    cf_WriteString(fp, "d3.mn3");
  } else {
    cf_WriteString(fp, Current_mission.filename ? Current_mission.filename : "");
  }

  cf_WriteInt(fp, Current_mission.game_state_flags);

  cf_WriteFloat(fp, Gametime);
  cf_WriteInt(fp, FrameCount);
  cf_WriteInt(fp, Current_waypoint);

  pending_music_region = D3MusicGetPendingRegion();
  if (pending_music_region < 0) {
    pending_music_region = D3MusicGetRegion();
  }
  cf_WriteShort(fp, pending_music_region);

  // cf_WriteInt(fp,Times_game_restored);
  // Save weather
  cf_WriteInt(fp, sizeof(Weather));
  cf_WriteBytes((uint8_t *)&Weather, sizeof(Weather), fp);

  // Save active doorways
  cf_WriteInt(fp, MAX_ACTIVE_DOORWAYS);
  cf_WriteInt(fp, Num_active_doorways);

  for (int d = 0; d < MAX_ACTIVE_DOORWAYS; d++) {
    cf_WriteInt(fp, Active_doorways[d]);
  }

  // save out room information.
  SGSRooms(fp);

  // save out triggers
  SGSTriggers(fp);

  // save out object information.
  SGSObjects(fp);

  // players
  SGSPlayers(fp);

  // save out matcens
  SGSMatcens(fp);

  // save out viseffects
  SGSVisEffects(fp);

  // save out spew
  SGSSpew(fp);

  // Save OSIRIS stuff
  Osiris_SaveSystemState(fp);

  // Save Level goal info
  Level_goals.SaveLevelGoalInfo(fp);

  // save out game messages from console. (must occur AFTER players are written out!!!)
  SGSGameMessages(fp);

  // save out special hud item states.
  SGSHudState(fp);

  // end
  END_VERIFY_SAVEFILE(fp, "Total save");
  cfclose(fp);

  return true;
}

//////////////////////////////////////////////////////////////////////////////

template <typename T, size_t sz>
void save_data_table(CFILE *fp, const std::array<T, sz>& data) {
  int16_t highest_index = -1;
  for (int16_t i = 0; i < sz; i++)
    if (data[i].used)
      highest_index = i;

  gs_WriteShort(fp, highest_index + 1);
  for (int16_t i = 0; i <= highest_index; i++)
    cf_WriteString(fp, data[i].used ? data[i].name : "");
}

//	writes out translation tables.
void SGSXlateTables(CFILE *fp) {
  START_VERIFY_SAVEFILE(fp);
  //	create object info translation table
  int16_t i, highest_index = -1;

  for (i = 0; i < MAX_OBJECT_IDS; i++)
    if (Object_info[i].type != OBJ_NONE)
      highest_index = i;

  gs_WriteShort(fp, highest_index + 1);

  for (i = 0; i <= highest_index; i++)
    cf_WriteString(fp, (Object_info[i].type != OBJ_NONE) ? Object_info[i].name : "");

  //	write out polymodel list.
  save_data_table(fp, Poly_models);

  // save out door list
  save_data_table(fp, Doors);

  // save out ship list
  save_data_table(fp, Ships);

  // save out weapons list
  save_data_table(fp, Weapons);

  // save out textures list
  save_data_table(fp, GameTextures);

  //	write out bitmap handle list.   look at all Objects that are fireballs and
  //	 save their handles-names.
  for (i = 0; i <= Highest_object_index; i++)
    if (Objects[i].type == OBJ_FIREBALL) {
      if (Objects[i].ctype.blast_info.bm_handle > -1) {
        gs_WriteShort(fp, Objects[i].ctype.blast_info.bm_handle);
        cf_WriteString(fp, GameBitmaps[Objects[i].ctype.blast_info.bm_handle].name);
      }
    }
  gs_WriteShort(fp, -1); // terminate bitmap list
  cf_WriteString(fp, "");
  END_VERIFY_SAVEFILE(fp, "Xlate save");
}

extern uint8_t AutomapVisMap[MAX_ROOMS];
//	initializes rooms
void SGSRooms(CFILE *fp) {
  int i, f, p;

  gs_WriteShort(fp, (int16_t)Highest_room_index);

  gs_WriteShort(fp, MAX_ROOMS);

  for (i = 0; i < MAX_ROOMS; i++) {
    gs_WriteByte(fp, AutomapVisMap[i]);
  }

  for (i = 0; i <= Highest_room_index; i++) {
    gs_WriteByte(fp, Rooms[i].used);
    if (Rooms[i].used) {
      // we need to save some room info out.
      gs_WriteInt(fp, Rooms[i].flags);
      gs_WriteByte(fp, Rooms[i].pulse_time);
      gs_WriteByte(fp, Rooms[i].pulse_offset);
      gs_WriteVector(fp, Rooms[i].wind);
      gs_WriteFloat(fp, Rooms[i].last_render_time);
      gs_WriteFloat(fp, Rooms[i].fog_depth);
      gs_WriteFloat(fp, Rooms[i].fog_r);
      gs_WriteFloat(fp, Rooms[i].fog_g);
      gs_WriteFloat(fp, Rooms[i].fog_b);
      gs_WriteFloat(fp, Rooms[i].damage);

      //??	gs_WriteFloat(fp, Rooms[i].ambient_sound); // need to save an index of sounds.

      // save additional face information here.
      // save texture changes
      int num_changed = 0;
      for (f = 0; f < Rooms[i].num_faces; f++) {
        if (Rooms[i].faces[f].flags & FF_TEXTURE_CHANGED)
          num_changed++;
      }
      cf_WriteShort(fp, num_changed);
      for (f = 0; f < Rooms[i].num_faces; f++) {
        if (Rooms[i].faces[f].flags & FF_TEXTURE_CHANGED) {
          cf_WriteShort(fp, f);
          cf_WriteShort(fp, Rooms[i].faces[f].tmap);
        }
      }

      for (p = 0; p < Rooms[i].num_portals; p++) {
        gs_WriteInt(fp, Rooms[i].portals[p].flags);
      }

      // save doorway info
      if (Rooms[i].flags & RF_DOOR) {
        doorway *dp = Rooms[i].doorway_data;
        ASSERT(dp != NULL);
        gs_WriteByte(fp, dp->state);
        gs_WriteByte(fp, dp->flags);
        gs_WriteByte(fp, dp->keys_needed);
        gs_WriteFloat(fp, dp->position);
        gs_WriteFloat(fp, dp->dest_pos);
        gs_WriteInt(fp, dp->sound_handle);
        gs_WriteInt(fp, dp->activenum);
        gs_WriteInt(fp, dp->doornum);
      }
    }
  }
}

//	saves out events
void SGSEvents(CFILE *fp) {}

//	saves out triggers
void SGSTriggers(CFILE *fp) {
  int i;

  gs_WriteShort(fp, (int16_t)Num_triggers);

  for (i = 0; i < Num_triggers; i++) {
    gs_WriteShort(fp, Triggers[i].flags);
    gs_WriteShort(fp, Triggers[i].activator);

    // write script info
    //@@		SGSScript(fp, &Triggers[i].script);
  }
}

// players
void SGSPlayers(CFILE *fp) {
  // player struct needs savin
  player *plr = &Players[0];

  gs_WriteShort(fp, sizeof(player));
  cf_WriteBytes((uint8_t *)plr, sizeof(player), fp);
  if (plr->guided_obj)
    gs_WriteInt(fp, plr->guided_obj->handle);

  // save inventory and countermeasures
  plr->inventory.SaveInventory(fp);
  plr->counter_measures.SaveInventory(fp);
}

// save viseffects
void SGSVisEffects(CFILE *fp) {
  int i, count = 0;

  // count up all viseffects to write out.
  for (i = 0; i <= Highest_vis_effect_index; i++)
    if (VisEffects[i].type != VIS_NONE)
      count++;

  gs_WriteShort(fp, (int16_t)count);

  for (i = 0; i <= Highest_vis_effect_index; i++) {
    if (VisEffects[i].type != VIS_NONE)
      cf_WriteBytes((uint8_t *)&VisEffects[i], sizeof(vis_effect), fp);
  }
}

extern int Physics_NumLinked;
extern std::array<int, MAX_OBJECTS> PhysicsLinkList;
extern char MarkerMessages[MAX_PLAYERS * 2][MAX_MARKER_MESSAGE_LENGTH];
extern int Marker_message;
void InsureSaveGame(CFILE *fp) { cf_WriteInt(fp, 0xF00D4B0B); }

#define INSURE_SAVEFILE
// InsureSaveGame(fp)

//	saves out objects
void SGSObjects(CFILE *fp) {
  int i, j;

  START_VERIFY_SAVEFILE(fp);

  // Save marker info (text)
  cf_WriteInt(fp, Marker_message);
  cf_WriteShort(fp, (int16_t)MAX_PLAYERS * 2);
  for (i = 0; i < MAX_PLAYERS * 2; i++) {
    cf_WriteShort(fp, strlen(MarkerMessages[i]) + 1);
    cf_WriteBytes((uint8_t *)MarkerMessages[i], strlen(MarkerMessages[i]) + 1, fp);
  }

  // this method should maintain the object list as it currently stands in the level
  cf_WriteShort(fp, (int16_t)Highest_object_index);

  // save what objects are stuck to each other
  cf_WriteInt(fp, MAX_OBJECTS);
  cf_WriteInt(fp, Physics_NumLinked);
  for (i = 0; i < MAX_OBJECTS; i++) {
    cf_WriteInt(fp, PhysicsLinkList[i]);
  }

  // save AI information
  //////////////////////////////////
  cf_WriteInt(fp, MAX_DYNAMIC_PATHS);
  cf_WriteInt(fp, MAX_NODES);

  int s;
  for (i = 0; i < MAX_DYNAMIC_PATHS; i++) {
    cf_WriteShort(fp, AIDynamicPath[i].num_nodes);
    cf_WriteShort(fp, AIDynamicPath[i].use_count);
    cf_WriteInt(fp, AIDynamicPath[i].owner_handle);

    for (s = 0; s < MAX_NODES; s++) {
      cf_WriteFloat(fp, AIDynamicPath[i].pos[s].x);
      cf_WriteFloat(fp, AIDynamicPath[i].pos[s].y);
      cf_WriteFloat(fp, AIDynamicPath[i].pos[s].z);
      cf_WriteInt(fp, AIDynamicPath[i].roomnum[s]);
    }
  }

  cf_WriteInt(fp, MAX_ROOMS);
  cf_WriteInt(fp, AIAltPathNumNodes);

  for (i = 0; i < MAX_ROOMS; i++) {
    cf_WriteInt(fp, AIAltPath[i]);
  }

  ///////////////////////////////////

  for (i = 0; i <= Highest_object_index; i++) {
    object *op = &Objects[i];
    poly_model *pm = &Poly_models[op->rtype.pobj_info.model_num];

    gs_WriteInt(fp, 0xBADB0B);
    // we don't save deleted objects or room objects since they're reconstructed on loadlevel
    gs_WriteByte(fp, (int8_t)op->type);

    if (op->type == OBJ_NONE)
      continue;
    gs_WriteByte(fp, (int8_t)op->lighting_render_type);

    // Store whether or not we have a pointer to lighting_info
    gs_WriteByte(fp, op->lighting_info ? 1 : 0);
    if (op->lighting_info) {
      cf_WriteBytes((uint8_t *)op->lighting_info, sizeof(*op->lighting_info), fp);
    }

    // these objects FOR NOW won't be saved
    gs_WriteInt(fp, op->handle);
    ASSERT((op->handle & HANDLE_OBJNUM_MASK) == i);

    // type and handle info.
    gs_WriteByte(fp, (int8_t)op->dummy_type);
    //	positional information
    gs_WriteInt(fp, op->roomnum);
    gs_WriteVector(fp, op->pos);
    gs_WriteVector(fp, op->last_pos);
    gs_WriteMatrix(fp, op->orient);

    // write out object name
    int ii;
    ii = (op->name) ? strlen(op->name) : 0;
    gs_WriteByte(fp, ii);
    if (ii > 0)
      cf_WriteBytes((uint8_t *)op->name, ii, fp);

    //	data universal to all objects that need to be saved.
    gs_WriteShort(fp, (int16_t)op->id);
    gs_WriteInt(fp, static_cast<int32_t>(op->flags));
    gs_WriteByte(fp, (int8_t)op->control_type);
    gs_WriteByte(fp, (int8_t)op->movement_type);
    gs_WriteByte(fp, (int8_t)op->render_type);

    gs_WriteShort(fp, (int16_t)op->renderframe);
    gs_WriteFloat(fp, op->size);
    gs_WriteFloat(fp, op->shields);
    gs_WriteByte(fp, op->contains_type);
    gs_WriteByte(fp, op->contains_id);
    gs_WriteByte(fp, op->contains_count);
    gs_WriteFloat(fp, op->creation_time);
    gs_WriteFloat(fp, op->lifeleft);
    gs_WriteFloat(fp, op->lifetime);
    gs_WriteInt(fp, op->parent_handle);

    // attachment info.
    gs_WriteInt(fp, op->attach_ultimate_handle);
    gs_WriteInt(fp, op->attach_parent_handle);
    if ((op->attach_ultimate_handle) && (OBJECT_HANDLE_NONE != op->attach_ultimate_handle)) {
      mprintf(0, "Object %d has an ultimate parent of %d (%d)\n", i, OBJNUM(ObjGet(op->attach_ultimate_handle)),
               op->attach_parent_handle);
    }
    if ((op->attach_ultimate_handle) && (OBJECT_HANDLE_NONE != op->attach_parent_handle)) {
      mprintf(0, "Object %d has a parent of %d (%d)\n", i, OBJNUM(ObjGet(op->attach_parent_handle)),
               op->attach_parent_handle);
    }

    gs_WriteInt(fp, pm->n_attach);
    if (pm->n_attach) {
      mprintf(0, "Object %d has %d attach points.\n", i, pm->n_attach);

      if (op->attach_children) {
        gs_WriteInt(fp, 1);

        for (j = 0; j < pm->n_attach; j++)
          gs_WriteInt(fp, op->attach_children[j]);
      } else {
        gs_WriteInt(fp, 0);
      }
    }

    INSURE_SAVEFILE;

    gs_WriteByte(fp, op->attach_type);
    gs_WriteShort(fp, op->attach_index);
    gs_WriteFloat(fp, op->attach_dist);
    gs_WriteVector(fp, op->min_xyz);
    gs_WriteVector(fp, op->max_xyz);
    gs_WriteFloat(fp, op->impact_size);
    gs_WriteFloat(fp, op->impact_time);
    gs_WriteFloat(fp, op->impact_player_damage);
    gs_WriteFloat(fp, op->impact_generic_damage);
    gs_WriteFloat(fp, op->impact_force);

    // write out custom default script info
    ii = (op->custom_default_script_name) ? strlen(op->custom_default_script_name) : 0;
    gs_WriteByte(fp, ii);
    if (ii > 0)
      cf_WriteBytes((uint8_t *)op->custom_default_script_name, ii, fp);

    ii = (op->custom_default_module_name) ? strlen(op->custom_default_module_name) : 0;
    gs_WriteByte(fp, ii);
    if (ii > 0)
      cf_WriteBytes((uint8_t *)op->custom_default_module_name, ii, fp);

    INSURE_SAVEFILE;

    gs_WriteShort(fp, (int16_t)op->position_counter);

    INSURE_SAVEFILE;

    //	write out all structures here.
    // movement info.
    gs_WriteShort(fp, sizeof(op->mtype));
    cf_WriteBytes((uint8_t *)&op->mtype, sizeof(op->mtype), fp);

    INSURE_SAVEFILE;

    // Control info, determined by CONTROL_TYPE
    gs_WriteShort(fp, sizeof(op->ctype));
    cf_WriteBytes((uint8_t *)&op->ctype, sizeof(op->ctype), fp);

    INSURE_SAVEFILE;

    // save ai information.
    SGSObjAI(fp, op->ai_info);

    INSURE_SAVEFILE;
    // save out rendering information
    gs_WriteShort(fp, sizeof(op->rtype));
    cf_WriteBytes((uint8_t *)&op->rtype, sizeof(op->rtype), fp);

    cf_WriteFloat(fp, op->size);
    if (op->render_type == RT_POLYOBJ) {
      // Do Animation stuff
      custom_anim multi_anim_info;
      ObjGetAnimUpdate(i, &multi_anim_info);
      cf_WriteBytes((uint8_t *)&multi_anim_info, sizeof(multi_anim_info), fp);
    }

    INSURE_SAVEFILE;

    // dynamic weapon battery info!!
    SGSObjWB(fp, op, (op->type == OBJ_PLAYER) ? MAX_WBS_PER_OBJ : pm->num_wbs);

    INSURE_SAVEFILE;

    // save effect info!
    SGSObjEffects(fp, op);

    INSURE_SAVEFILE;

    // save script stuff.
    //@@		SGSScript(fp, &op->script);

    // special things local to object
    SGSObjSpecial(fp, op);
  }
  mprintf(0, "highest obj index = %d, ", Highest_object_index);
  END_VERIFY_SAVEFILE(fp, "Objects save");
}

//	saves ai
void SGSObjAI(CFILE *fp, const ai_frame *ai) {
  gs_WriteByte(fp, (ai ? 1 : 0));
  if (!ai)
    return;

  gs_WriteShort(fp, sizeof(ai_frame));
  cf_WriteBytes((uint8_t *)ai, sizeof(ai_frame), fp);
}

//	saves script
//@@void SGSScript(CFILE *fp, const script_info *script)
//@@{
//@@	int i,j;
//@@
//@@//	ugh, write out script info.
//@@	gs_WriteByte(fp, (script->thread ? 1 : 0));
//@@
//@@	if (script->name)
//@@		cf_WriteString(fp, script->name);
//@@	else
//@@		cf_WriteString(fp, "");
//@@
//@@	gs_WriteShort(fp, script->num_parms);
//@@	gs_WriteShort(fp, script->is_custom);
//@@	for (i = 0; i < script->num_parms; i++)
//@@	{
//@@		gs_WriteByte(fp, script->parms[i].type);
//@@		gs_WriteFloat(fp, script->parms[i].val.x);
//@@		gs_WriteFloat(fp, script->parms[i].val.y);
//@@		gs_WriteFloat(fp, script->parms[i].val.z);
//@@	}
//@@
//@@// write out thread data if necessary
//@@	if (script->thread) {
//@@		const vector *mem = D3XGetThreadMem(script->thread->mem_handle);
//@@		uint16_t mem_size = script->thread->prog->map[script->thread->prog_idx].mem;
//@@
//@@		gs_WriteShort(fp, mem_size);
//@@		if (mem) {
//@@			for (j = 0; j < mem_size; j++)
//@@				gs_WriteVector(fp, mem[j]);
//@@		}
//@@	}
//@@}

//	saves fx
void SGSObjEffects(CFILE *fp, const object *op) {
  effect_info_s *ei = op->effect_info;

  gs_WriteByte(fp, (ei ? 1 : 0));
  if (ei) {
    gs_WriteShort(fp, sizeof(effect_info_s));
    cf_WriteBytes((uint8_t *)ei, sizeof(effect_info_s), fp);
  }
}

//	saves wb
void SGSObjWB(CFILE *fp, object *op, int num_wbs) {
  int i;

  if (op->dynamic_wb) {
    gs_WriteByte(fp, (int8_t)num_wbs);
    for (i = 0; i < num_wbs; i++) {
      dynamic_wb_info *dwb = &op->dynamic_wb[i];
      cf_WriteBytes((uint8_t *)dwb, sizeof(dynamic_wb_info), fp);
    }
  } else {
    gs_WriteByte(fp, 0);
  }
}

// saves special object info
void SGSObjSpecial(CFILE *fp, const object *op) {}

// load spew
void SGSSpew(CFILE *fp) {
  int i;

  gs_WriteShort(fp, (int16_t)spew_count);
  for (i = 0; i < MAX_SPEW_EFFECTS; i++) {
    gs_WriteByte(fp, SpewEffects[i].inuse ? true : false);
    if (SpewEffects[i].inuse)
      cf_WriteBytes((uint8_t *)&SpewEffects[i], sizeof(spewinfo), fp);
  }
}

// save matcens
void SGSMatcens(CFILE *fp) {
  cf_WriteInt(fp, Num_matcens);

  for (int i = 0; i < Num_matcens; i++) {
    ASSERT(Matcen[i]);

    Matcen[i]->SaveData(fp);
  }
}

#define HUD_RENDER_ZOOM 0.56f
void SGSSnapshot(CFILE *fp) {
  extern void ResetFacings(); // render.cpp

  const int SGSSNAP_WIDTH = 160, SGSSNAP_HEIGHT = 120;
  int oldfilepos, bm_handle;

  oldfilepos = cftell(fp);

  // Set up for rendering
  StartFrame(0, 0, Max_window_w, Max_window_h);
  g3_StartFrame(&Viewer_object->pos, &Viewer_object->orient, HUD_RENDER_ZOOM);

  // Reset facings for mine stuff
  ResetFacings();

  // Render the world
  GameRenderWorld(Viewer_object, &Viewer_object->pos, Viewer_object->roomnum, &Viewer_object->orient, Render_zoom,
                  false);

  // Done rendering
  g3_EndFrame();
  EndFrame();
  rend_Flip();
  bm_handle = bm_AllocBitmap(Max_window_w, Max_window_h, 0);

  cf_WriteByte(fp, (bm_handle > 0) ? 1 : 0);

  if (bm_handle > 0) {
    // Tell our renderer lib to take a screen shot
    rend_Screenshot(bm_handle);
    bm_ChangeSize(bm_handle, SGSSNAP_WIDTH, SGSSNAP_HEIGHT);

    try {
      if (bm_SaveBitmap(fp, bm_handle) < 0) {
        cfseek(fp, oldfilepos, SEEK_SET);
        cf_WriteByte(fp, 0);
      }
    } catch (cfile_error) {
      cfseek(fp, oldfilepos, SEEK_SET);
      cf_WriteByte(fp, 0);
    }

    bm_FreeBitmap(bm_handle);
  }
}

//@@		switch (op->control_type)
//@@		{
//@@		case CT_NONE:
//@@		case CT_AI:
//@@		case CT_FLYING:			//the player is flying
//@@		case CT_FLYTHROUGH:		//the flythrough system
//@@		case CT_SLEW:				//slewing
//@@		case CT_PARTICLE:			//Particle
//@@			break;
//@@		case CT_EXPLOSION:		//explosion sequencer
//@@			gs_WriteFloat(fp, op_expl->spawn_time);
//@@			gs_WriteFloat(fp,	op_expl->delete_time);
//@@			gs_WriteShort(fp, op_expl->delete_objnum);
//@@			gs_WriteShort(fp, op_expl->attach_parent);
//@@			gs_WriteShort(fp, op_expl->prev_attach);
//@@			gs_WriteShort(fp, op_expl->next_attach);
//@@			break;
//@@		case CT_DEBRIS:			//this is a piece of debris
//@@			gs_WriteFloat(fp, op->ctype.dying_info.delay_time);
//@@			gs_WriteBool(fp, op->ctype.dying_info.f_death_anim);
//@@			break;
//@@		case CT_POWERUP:			//animating powerup blob
//@@			gs_WriteInt(fp, op->ctype.powerup_info.count);
//@@			gs_WriteInt(fp, op->ctype.powerup_info.flags);
//@@			break;
//@@		case CT_SPLINTER:			//Splinter
//@@			gs_WriteByte(fp, (int8_t)op_splint->subobj_num);
//@@			gs_WriteShort(fp, op_splint->facenum);
//@@			for (j = 0; j < MAX_VERTS_PER_SPLINTER; j++)
//@@				gs_WriteVector(fp, op_splint->verts[j]);
//@@			gs_WriteVector(fp, op_splint->center);
//@@			break;
//@@		case CT_WEAPON:			//laser, etc.
//@@			gs_WriteShort(fp, op_wpn->parent_type);
//@@			gs_WriteShort(fp, op_wpn->src_gun_num);
//@@			gs_WriteInt(fp, op_wpn->last_hit_handle);
//@@			gs_WriteInt(fp, op_wpn->track_handle);
//@@			gs_WriteInt(fp, op_wpn->hit_status);
//@@			gs_WriteVector(fp, op_wpn->hit_pnt);
//@@			gs_WriteVector(fp, op_wpn->hit_wall_pnt);
//@@			gs_WriteVector(fp, op_wpn->hit_wall_normal);
//@@			gs_WriteInt(fp, op_wpn->hit_room);
//@@			gs_WriteInt(fp, op_wpn->hit_pnt_room);
//@@			gs_WriteShort(fp, op_wpn->hit_face);
//@@			gs_WriteFloat(fp, op_wpn->multiplier);
//@@			gs_WriteFloat(fp, op_wpn->thrust_left);
//@@			gs_WriteFloat(fp, op_wpn->last_drop_time);
//@@			break;
//@@
//@@		default:
//@@			Int3();
//@@		}

//@@		if (op->type == OBJ_FIREBALL) {
//@@			gs_WriteFloat(fp, op->ctype.blast_info.max_size);
//@@			gs_WriteInt(fp, op->ctype.blast_info.bm_handle);
//@@		}

//@@		const int N_SHARD_VERTS = 3;
//@@		switch (op->render_type)
//@@		{
//@@		case RT_NONE:
//@@		case RT_EDITOR_SPHERE:
//@@		case RT_FIREBALL:
//@@		case RT_LINE:
//@@		case RT_PARTICLE:
//@@		case RT_SPLINTER:
//@@		case RT_ROOM:
//@@			break;
//@@		case RT_WEAPON:
//@@			if (!(op->flags & OF_POLYGON_OBJECT))
//@@				break;
//@@		case RT_POLYOBJ:
//@@			gs_WriteShort(fp, pobji->model_num);
//@@			gs_WriteShort(fp, pobji->dying_model_num);
//@@			gs_WriteFloat(fp, pobji->anim_start_frame);
//@@			gs_WriteFloat(fp, pobji->anim_frame);
//@@			gs_WriteFloat(fp, pobji->anim_end_frame);
//@@			gs_WriteFloat(fp, pobji->anim_time);
//@@			gs_WriteInt(fp, (int)pobji->anim_flags);
//@@			gs_WriteFloat(fp, pobji->max_speed);
//@@			gs_WriteInt(fp, (int)pobji->subobj_flags);
//@@			gs_WriteInt(fp, pobji->tmap_override);
//@@		//!!	multi_anim_save here
//@@			break;
//@@
//@@		case RT_SHARD:
//@@			for (j = 0; j < N_SHARD_VERTS; j++)
//@@				gs_WriteVector(fp, op->rtype.shard_info.points[j]);
//@@			for (j = 0; j < N_SHARD_VERTS; j++)
//@@				gs_WriteFloat(fp, op->rtype.shard_info.u[j]);
//@@			for (j = 0; j < N_SHARD_VERTS; j++)
//@@				gs_WriteFloat(fp, op->rtype.shard_info.v[j]);
//@@			gs_WriteVector(fp, op->rtype.shard_info.normal);
//@@			gs_WriteShort(fp, op->rtype.shard_info.tmap);
//@@			break;
//@@
//@@		default:
//@@			Int3();
//@@		}

// AI WRITES
//@@// the FUN begins.
//@@	gs_WriteByte(fp, ai->ai_class);
//@@	gs_WriteByte(fp, ai->ai_type);
//@@
//@@// write path info
//@@	const ai_path_info *path = &ai->path;
//@@	gs_WriteInt(fp, path->flags);
//@@	gs_WriteShort(fp, path->cur_path);
//@@	gs_WriteShort(fp, path->cur_node);
//@@	gs_WriteShort(fp, path->num_paths);
//@@	gs_WriteShort(fp, path->goal_index);
//@@
//@@	for (i = 0; i < MAX_JOINED_PATHS; i++)
//@@	{
//@@		gs_WriteByte(fp, path->path_id[i]);
//@@		gs_WriteByte(fp, path->path_type[i]);
//@@		gs_WriteShort(fp, path->path_start_node[i]);
//@@		gs_WriteShort(fp, path->path_end_node[i]);
//@@		gs_WriteShort(fp, path->path_flags[i]);
//@@	}
//@@
//@@// continue
//@@	gs_WriteFloat(fp, ai->max_velocity);
//@@	gs_WriteFloat(fp, ai->max_delta_velocity);
//@@	gs_WriteFloat(fp, ai->max_turn_rate);
//@@	gs_WriteFloat(fp, ai->max_delta_turn_rate);
//@@	gs_WriteFloat(fp, ai->attack_vel_percent);
//@@	gs_WriteFloat(fp, ai->flee_vel_percent);
//@@	gs_WriteFloat(fp, ai->dodge_vel_percent);
//@@	gs_WriteFloat(fp, ai->circle_distance);
//@@	gs_WriteFloat(fp, ai->dodge_percent);
//@@
//@@	for (i = 0; i < 2; i++)
//@@	{
//@@		gs_WriteFloat(fp, ai->melee_damage[i]);
//@@		gs_WriteFloat(fp, ai->melee_latency[i]);
//@@	}
//@@
//@@	for (i = 0; i < MAX_AI_SOUNDS; i++)
//@@	{
//@@		gs_WriteInt(fp, ai->sound[i]);
//@@		gs_WriteFloat(fp, ai->last_sound_time[i]);
//@@	}
//@@	gs_WriteShort(fp, ai->last_played_sound_index);
//@@
//@@	gs_WriteByte(fp, ai->movement_type);
//@@	gs_WriteByte(fp, ai->movement_subtype);
//@@	gs_WriteByte(fp, ai->animation_type);
//@@	gs_WriteByte(fp, ai->next_animation_type);
//@@	gs_WriteByte(fp, ai->next_movement);
//@@	gs_WriteByte(fp, ai->current_wb_firing);
//@@	gs_WriteByte(fp, ai->last_wb_firing);
//@@
//@@//	goals
//@@	for (i = 0;i < MAX_GOALS; i++)
//@@		SGSObjAIGoal(fp, &ai->goals[i]);
//@@
//@@//	continue
//@@	gs_WriteInt(fp, ai->target_handle);
//@@	gs_WriteFloat(fp, ai->next_target_update_time);
//@@	gs_WriteFloat(fp, ai->dist_to_target);
//@@	gs_WriteVector(fp, ai->vec_to_target);
//@@	gs_WriteFloat(fp, ai->last_check_see_target_time);
//@@	gs_WriteVector(fp, ai->last_see_target_pos);
//@@	gs_WriteFloat(fp, ai->last_see_target_time);
//@@	gs_WriteFloat(fp, ai->weapon_speed);
//@@	gs_WriteFloat(fp, ai->next_melee_time);
//@@	gs_WriteFloat(fp, ai->last_render_time);
//@@	gs_WriteFloat(fp, ai->next_flinch_time);
//@@	gs_WriteInt(fp, ai->status_reg);
//@@	gs_WriteInt(fp, ai->flags);
//@@	gs_WriteInt(fp, ai->notify_flags);
//@@
//@@// notify events (MUST BE WRITTEN OUT AT A LATER DATE)
//@@
//@@// Normalized movement and facing information
//@@	gs_WriteVector(fp, ai->movement_dir);
//@@	gs_WriteVector(fp, ai->rot_thrust_vector);
//@@	gs_WriteFloat(fp, ai->fov);
//@@	gs_WriteInt(fp, ai->anim_sound_handle);
//@@	gs_WriteFloat(fp, ai->frustration);
//@@	gs_WriteFloat(fp, ai->curiousity);
//@@	gs_WriteFloat(fp, ai->fire_spread);
//@@	gs_WriteFloat(fp, ai->agression);
//@@	gs_WriteFloat(fp, ai->night_vision);
//@@	gs_WriteFloat(fp, ai->fog_vision);
//@@	gs_WriteFloat(fp, ai->lead_accuracy);
//@@	gs_WriteFloat(fp, ai->lead_varience);
//@@	gs_WriteFloat(fp, ai->fight_team);
//@@	gs_WriteFloat(fp, ai->fight_same);
//@@	gs_WriteFloat(fp, ai->hearing);
//@@	gs_WriteFloat(fp, ai->roaming);
//@@	gs_WriteFloat(fp, ai->life_preservation);
//@@
//@@	gs_WriteShort(fp, ai->awareness);

//@@void SGSObjAIGoal(CFILE *fp, const goal *g)
//@@{
//@@	int i;
//@@
//@@	gs_WriteByte(fp, (g->used ? 1 : 0));
//@@	if (!g->used)
//@@		return;
//@@
//@@	gs_WriteInt(fp, g->type);
//@@	gs_WriteByte(fp, g->activation_level);
//@@	gs_WriteShort(fp, g->influence);
//@@
//@@// write goal info
//@@	switch (g->type)
//@@	{
//@@		case AIG_HIDE_FROM_OBJ:
//@@			gs_WriteInt(fp, g->g_info.handle);
//@@			gs_WriteFloat(fp, g->g_info.time);
//@@			break;
//@@
//@@		case AIG_WANDER_AROUND:
//@@			gs_WriteInt(fp, g->g_info.roomnum);
//@@			break;
//@@
//@@		case AIG_DODGE_OBJ:
//@@		case AIG_MOVE_RELATIVE_OBJ:
//@@			gs_WriteInt(fp, g->g_info.handle);
//@@			break;
//@@
//@@		case AIG_MOVE_RELATIVE_OBJ_VEC:
//@@			gs_WriteInt(fp, g->g_info.handle);
//@@			gs_WriteInt(fp, g->g_info.subtype);
//@@			break;
//@@
//@@		case AIG_GUARD_AREA:
//@@			gs_WriteVector(fp, g->g_info.pos);
//@@			break;
//@@
//@@		case AIG_GET_TO_OBJ:
//@@			gs_WriteInt(fp, g->g_info.handle);
//@@			gs_WriteVector(fp, g->g_info.pos);
//@@			break;
//@@
//@@		case AIG_GET_TO_POS:
//@@			gs_WriteInt(fp, g->g_info.roomnum);
//@@			gs_WriteVector(fp, g->g_info.pos);
//@@			break;
//@@
//@@		case AIG_FOLLOW_PATH: // This must be fixed -- chrishack
//@@			gs_WriteInt(fp, g->g_info.id);
//@@			break;
//@@	}
//@@
//@@// write goal enabler
//@@	gs_WriteByte(fp, g->num_enablers);
//@@	for (i = 0; i < g->num_enablers; i++)
//@@	{
//@@		gs_WriteByte(fp, g->enabler[i].enabler_type);
//@@
//@@		switch (g->enabler[i].enabler_type)
//@@		{
//@@		case AIE_AI_STATUS_FLAG:
//@@			gs_WriteInt(fp, g->enabler[i].flags);
//@@			break;
//@@		}
//@@
//@@		gs_WriteFloat(fp, g->enabler[i].percent_enable);
//@@		gs_WriteFloat(fp, g->enabler[i].check_interval);
//@@		gs_WriteFloat(fp, g->enabler[i].last_check_time);
//@@		gs_WriteByte(fp, g->enabler[i].bool_next_enabler_op);
//@@	}
//@@
//@@// continue
//@@	gs_WriteFloat(fp, g->circle_distance);
//@@	gs_WriteInt(fp, g->status_reg);
//@@	gs_WriteFloat(fp, g->start_time);
//@@	gs_WriteFloat(fp, g->next_path_time);
//@@	gs_WriteFloat(fp, g->dist_to_goal);
//@@	gs_WriteVector(fp, g->vec_to_target);
//@@	gs_WriteFloat(fp, g->last_check_see_target_time);
//@@	gs_WriteVector(fp, g->last_see_target_pos);
//@@	gs_WriteFloat(fp, g->last_see_target_time);
//@@	gs_WriteFloat(fp, g->next_target_update_time);
//@@	gs_WriteShort(fp, g->flags);
//@@}
//@@

// EFFECTS INFO STRUCTURE
//@@		gs_WriteInt(fp, ei->type_flags);
//@@		gs_WriteFloat(fp, ei->alpha);
//@@
//@@//		if (op->type == OBJ_POWERUP) {
//@@			gs_WriteFloat(fp, ei->last_object_hit_time);
//@@			gs_WriteInt(fp, ei->last_object_hit);
//@@//		}
//@@//		if (ei->type_flags & EF_DEFORM) {
//@@			gs_WriteFloat(fp, ei->deform_range);
//@@			gs_WriteFloat(fp, ei->deform_time);
//@@//		}
//@@//		if (ei->type_flags & EF_VOLUME_CHANGING) {
//@@			gs_WriteFloat(fp, ei->volume_change_time);
//@@			gs_WriteVector(fp, ei->volume_old_pos);
//@@			gs_WriteFloat(fp, ei->volume_old_room);
//@@//		}
//@@//		if (ei->type_flags & EF_VOLUME_LIT) {
//@@			gs_WriteByte(fp, (int8_t)ei->dynamic_this_frame);
//@@			gs_WriteFloat(fp, ei->dynamic_red);
//@@			gs_WriteFloat(fp, ei->dynamic_green);
//@@			gs_WriteFloat(fp, ei->dynamic_blue);
//@@//		}
//@@//		if (ei->type_flags & EF_CLOAKED) {
//@@			gs_WriteFloat(fp, ei->cloak_time);
//@@//		}
//@@//		if (ei->type_flags & EF_COLORED) {
//@@			gs_WriteFloat(fp, ei->color_time);
//@@			gs_WriteFloat(fp, ei->r);
//@@			gs_WriteFloat(fp, ei->g);
//@@			gs_WriteFloat(fp, ei->b);
//@@//		}
//@@//		if (ei->type_flags & EF_NAPALMED) {
//@@			gs_WriteFloat(fp, ei->damage_time);
//@@			gs_WriteFloat(fp, ei->damage_per_second);
//@@			gs_WriteFloat(fp, ei->last_damage_time);
//@@			gs_WriteInt(fp, ei->damage_handle);
//@@//		}
//@@//		if (ei->type_flags & EF_FREEZE) {
//@@			gs_WriteFloat(fp, ei->freeze_scalar);
//@@//		}
//@@//		if (ei->type_flags & EF_LINE_ATTACH) {
//@@			gs_WriteInt(fp, ei->attach_line_handle);
//@@//		}

//	 Weapon Battery Info
//@@			gs_WriteFloat(fp, dwb->last_fire_time);
//@@			gs_WriteByte(fp, dwb->cur_firing_mask);
//@@
//@@			for (j = 0; j < MAX_WB_TURRETS; j++)
//@@			{
//@@				gs_WriteFloat(fp, dwb->norm_turret_angle[j]);
//@@				gs_WriteFloat(fp, dwb->turret_next_think_time[j]);
//@@				gs_WriteByte(fp, dwb->turret_direction[j]);
//@@			}
//@@
//@@			gs_WriteByte(fp, dwb->wb_anim_mask);
//@@			gs_WriteFloat(fp, dwb->wb_anim_frame);
//@@			gs_WriteVector(fp, dwb->cur_target);
//@@			gs_WriteByte(fp, dwb->upgrade_level);
//@@			gs_WriteInt(fp, dwb->flags);
