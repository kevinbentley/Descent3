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

 * $Logfile: /DescentIII/Main/manage/pagelock.cpp $
 * $Revision: 42 $
 * $Date: 5/17/99 2:09p $
 * $Author: Jeff $
 *
 * Jason should put something here
 *
 * $Log: /DescentIII/Main/manage/pagelock.cpp $
 *
 * 42    5/17/99 2:09p Jeff
 * fixed tablefile logging
 *
 * 41    5/14/99 12:15p Jason
 * added page logging
 *
 * 40    4/30/99 8:53p Matt
 * Added a "voice" directory for gamefiles.
 *
 * 39    4/22/99 7:08p Matt
 * Reduced the number of object sounds from 3 to 2, since we were only
 * using two.
 *
 * 38    4/18/99 4:49p Matt
 * Took out code that hacked in ammo amounts for weapon powerups, and
 * added code to set the counts on the page and read and write to the
 * table file.
 *
 * 37    4/14/99 10:46a Kevin
 * Removed OutrageMessageBox from release builds
 *
 * 36    4/14/99 1:33a Jeff
 * fixed case mismatched #includes
 *
 * 35    4/12/99 12:49p Jeff
 * added recoil_force to weapon's page
 *
 * 34    4/09/99 12:51p Jason
 * corrected bug sound resolving code
 *
 * 33    4/06/99 6:02p Matt
 * Added score system
 *
 * 32    3/30/99 6:11p Jason
 * changed pagelock version
 *
 * 31    3/29/99 11:20a Matt
 * Added more flexibility to death delays, and added fade away deaths.
 *
 * 30    3/04/99 1:47p Jason
 * fixed some manage problems
 *
 *
 * 29    3/01/99 12:54a Matt
 * Incremented table file version
 *
 * 28    2/23/99 12:39p Jason
 * added more options for generic objects
 *
 * 27    2/22/99 2:03p Jason
 * added different damages for players and generics
 *
 * 26    2/03/99 1:58a Matt
 * Added a system to show all pages locked.
 *
 * 25    2/02/99 8:44a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 24    12/30/98 5:17p Jeff
 * changes made to handle script name override, to override the name of
 * the script to use in a module.
 *
 * 23    12/21/98 5:27p Jeff
 * added osiris module information to door page.  Fixed up dialogs for
 * objects and doors for script interface (added a browse button)
 *
 * 22    12/17/98 7:26p Jeff
 * new script system data
 *
 * 21    12/17/98 12:50p Jason
 * changed doorpage
 *
 * 20    12/01/98 4:31p Chris
 * Checked in a massive amount of AI work.  Improved flocking code.  :)
 * (Still hacked lightly).  In addition, I am moving toward using the
 * composite dir.  :)
 *
 * 19    11/19/98 8:25p Chris
 *
 * 18    11/13/98 12:30p Jason
 * changes for weapons
 *
 * 17    11/06/98 11:24a Jason
 * fixed length bug
 *
 * 16    11/05/98 7:55p Jason
 * changes for new manage system
 *
 * 15    10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 14    10/14/98 5:15p Jason
 * added version checking to the table file
 *
 * 13    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 12    6/05/98 12:54p Jason
 * fixed stupid pagelock bug
 *
 * 11    6/03/98 3:46p Jason
 * made megacell system more robust
 *
 * 10    5/04/98 5:13p Jason
 * better error handling
 *
 * 9     3/19/98 1:15p Jason
 * more error checking
 *
 * 8     3/19/98 12:02p Jason
 * added better error checking to pagelocks
 *
 * 7     2/19/98 1:52p Jason
 * added emergency override to unlock function
 *
 * 6     10/06/97 3:30p Samir
 * FROM JASON: added error message
 *
 * 5     9/25/97 2:19p Jason
 * added test case to EraseLocker
 *
 * 4     9/25/97 11:22a Jason
 * added error checking to EraseLocker
 *
 * 3     8/12/97 12:07p Matt
 * Treat old robot locks as generic locks
 *
 * 2     8/08/97 1:48p Matt
 * Change mng_MakeLocker() bring up dialog if no network, and give the
 * player a chance to retry if someone else has the database locked.
 *
 * 16    3/17/97 6:52p Jason
 * added mprintf to locker file error
 *
 * 15    3/13/97 7:38p Matt
 * Added include of string.h
 *
 * 14    3/13/97 6:42 PM Jeremy
 * #included <errno.h> and unincluded <windows.h>
 *
 * 13    3/03/97 6:21p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "pstypes.h"
#include "pserror.h"
#include "mono.h"
#include "mem.h"

#ifndef RELEASE
#include <ctime>
#endif

#define CURRENT_TABLE_VERSION 22
extern const char *PageNames[];

void mng_InitPagelocks() {
  // If there is not a pagelock file, create one with a dummy header.

  CFILE *infile = nullptr, *outfile = nullptr;
  mngs_Pagelock testlock;

  if (!Network_up)
    return;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (infile == NULL) {
    outfile = (CFILE *)cfopen(TableLockFilename, "wb");
    if (!outfile) {
      Error("Error creating table lock file!");
      return;
    }
    testlock.pagetype = PAGETYPE_UNKNOWN;
    strcpy(testlock.name, "DUMMY PAGE");
    strcpy(testlock.holder, "NOT HELD AT ALL");
    mng_WritePagelock(outfile, &testlock);

    cfclose(outfile);
  } else
    cfclose(infile);
}

// Checks to see if the locker file is present.
// Returns pointer to locker's name, or NULL if the file is unlocked
char *mng_CheckIfLockerPresent() {
  CFILE *infile;
  int i = 0;
  static char lockname[200];

  ASSERT(Network_up);

  infile = (CFILE *)cfopen(LockerFile, "rb");
  if (!infile)
    return NULL;

  cf_ReadString(lockname, sizeof(lockname), infile);

  mprintf(0, "%s has already got exlusive access to the table file.\n", lockname);

  cfclose(infile);

  return lockname;
}

// Returns 1 if we have the most up to date code for the manage system, else 0
int TableVersionCurrent() {
  CFILE *infile;

  if (!cfexist(VersionFile))
    return 1; // Doesn't exist, so go ahead

  infile = (CFILE *)cfopen(VersionFile, "rb");
  if (!infile) {
    mprintf(0, "Couldn't open the version file for querying!\n");
    return 0;
  }

  int version = cf_ReadInt(infile);

  cfclose(infile);

  if (version > CURRENT_TABLE_VERSION)
    return 0;

  return 1;
}

// Call this before any chokepoint functions are executed.
// Locks the whole table system for our exclusive use
int mng_MakeLocker() {
  CFILE *outfile = nullptr;
  int len;
  char *locker;

  len = strlen(TableUser);
#ifndef RELEASE
  if (!Network_up) {
    OutrageMessageBox("Error: You are not connected to the network.");
    return 0;
  }

  // See if someone else has the file locked
  do {
    locker = mng_CheckIfLockerPresent();
    if (locker) {
      strupr(locker);
      if (OutrageMessageBox(MBOX_YESNO,
                            "The network database is already locked by %s.\nIt will probably become available if you "
                            "wait a few moments.\n\nWould you like to try again?",
                            locker) != IDYES)
        return 0;
    }
  } while (locker);

  // Make sure the version is current
  if (!TableVersionCurrent()) {
    OutrageMessageBox("You must do a source update and recompile.  Your table file code is outdated!");
    return 0;
  }

  outfile = (CFILE *)cfopen(LockerFile, "wb");
  if (!outfile) {
    OutrageMessageBox("Error opening the locker file!");
    mprintf(0, "couldn't open the locker file!\n");
    return 0;
  }
#endif
  for (int i = 0; i < len; i++)
    cf_WriteByte(outfile, TableUser[i]);
  cfclose(outfile);
  return 1;
}

// Simply erases the Lockerfile
void mng_EraseLocker() {

#ifndef RELEASE
  int count = 0;
  int done = 0;

  while (!done) {
    CFILE *fp = (CFILE *)cfopen(LockerFile, "rt");
    if (!fp)
      return;
    else
      cfclose(fp);

    if (remove(LockerFile)) {
      if (count >= 10) {
        OutrageMessageBox("There was a problem deleting the locker file...get Jason immediately!");
        return;
      } else
        count++;
    } else {
      done = 1;
    }
  }

  // Now update the version info
  count = 0;
  while (1) {
    CFILE *fp = (CFILE *)cfopen(VersionFile, "wb");
    if (!fp) {
      if (count >= 10) {
        OutrageMessageBox("There was a problem opening the version file...get Jason immediately!");
        return;
      } else
        count++;
    } else {
      cf_WriteInt(fp, CURRENT_TABLE_VERSION);
      cfclose(fp);
      return;
    }
  }
#endif
}

int mng_CheckIfPageLocked(mngs_Pagelock *pl) {
  // Given a page name, checks to see if it is locked.
  // Returns 1 if locked, 0 if not.

  CFILE *infile;
  mngs_Pagelock testlock;
  int r, done = 0;

  if (!Network_up)
    return 1;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (infile == NULL) {
    strcpy(ErrorString, "There was a problem opening the table lock file for reading.");
    return -1;
  }

  while (!done) {
    r = mng_ReadPagelock(infile, &testlock);
    if (r == 0) {
      done = 1;
      r = 2;
    } else {
      if (!stricmp(pl->name, testlock.name)) {
        int test = 0;
        if (pl->pagetype == testlock.pagetype) {
          if (!stricmp(testlock.holder, "UNLOCKED"))
            r = 0;
          else {
            snprintf(InfoString, sizeof(InfoString), "User %s already has this page locked.", testlock.holder);
            if (!stricmp(testlock.holder, TableUser))
              r = 0;
            else
              r = 1;
          }
          strcpy(pl->holder, testlock.holder);
          done = 1;
        }
      }
    }
  }

  cfclose(infile);
  return r;
}

int mng_CheckIfPageOwned(mngs_Pagelock *pl, char *owner) {
  // Given a page name, checks to see if it is locked by owner.
  // Returns 1 if locked by owner, 0 if not.

  CFILE *infile;
  mngs_Pagelock testlock;
  int r, done = 0;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (infile == NULL) {
    strcpy(ErrorString, "There was a problem opening the table lock file for reading.");
    Int3();
    return -1;
  }

  while (!done) {
    r = mng_ReadPagelock(infile, &testlock);
    if (r == 0) {
      // We've reached the end of file, must be a new page and nobody owns it
      done = 1;
      r = 2;
    } else {
      if (!stricmp(pl->name, testlock.name) && pl->pagetype == testlock.pagetype) {
        if (!stricmp(testlock.holder, owner))
          r = 1;
        else {
          snprintf(InfoString, sizeof(InfoString), "User %s does not have this page locked.", owner);
          r = 0;
        }
        done = 1;
      }
    }
  }

  cfclose(infile);
  return r;
}

int mng_ReadPagelock(CFILE *fp, mngs_Pagelock *pl) {
  // Reads a pagelock from the fp file.  Returns 1 if successfully read, 0 if eof was encountered.

  char c;
  int i;

  if (cfeof(fp))
    return 0;

  // Read type of page
  pl->pagetype = cf_ReadByte(fp);

  // Convert old robot locks to generic locks
  if (pl->pagetype == PAGETYPE_ROBOT)
    pl->pagetype = PAGETYPE_GENERIC;

  // Read the name of this page
  for (i = 0; i < PAGELOCK_NAME_LEN; i++) {
    c = cf_ReadByte(fp);
    pl->name[i] = c;
  }

  // Read the user who has this page locked.
  for (i = 0; i < PAGELOCK_NAME_LEN; i++) {
    c = cf_ReadByte(fp);
    pl->holder[i] = c;
  }

  pl->name[PAGELOCK_NAME_LEN] = 0;
  pl->holder[PAGELOCK_NAME_LEN] = 0;

  if (pl->pagetype == PAGETYPE_POWERUP) {
    mprintf(0, "Powerup lock: %d, %s, %s\n", pl->pagetype, pl->name, pl->holder);
  }

  return 1;
}

int mng_ReplacePagelock(char *name, mngs_Pagelock *pl) {
  // Given a pagelock, replaces the one already inside the lock file, or if not present, adds it to
  // the lock file.  Returns 0 on error, or 1 if successful.

  CFILE *infile, *outfile;
  int replaced = 0;
  int done = 0;

  mngs_Pagelock temp_pl;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    Int3(); // Get Jason
    return 0;
  }
  outfile = (CFILE *)cfopen(TempTableLockFilename, "wb");
  if (!outfile) {
    cfclose(infile);
    strcpy(ErrorString, "Couldn't open temporary table lock file!");
    Int3(); // Get Jason
    return 0;
  }

  while (!done) {
    if (mng_ReadPagelock(infile, &temp_pl)) {
      if (!stricmp(temp_pl.name, name) && pl->pagetype == temp_pl.pagetype) {
        // This is the page we want to replace, so write the new one out.
        mng_WritePagelock(outfile, pl);
        replaced = 1;
      } else {
        mng_WritePagelock(outfile, &temp_pl);
      }
    } else {

      if (!replaced) {
        // This is a new page, so append it to the end of file.
        mng_WritePagelock(outfile, pl);
        strcpy(InfoString, "Page was successfully added.");
      } else
        strcpy(InfoString, "Page was successfully replaced.");
      done = 1;
    }
  }
  cfclose(infile);
  cfclose(outfile);

  if (!SwitcherooFiles(TableLockFilename.u8string().c_str(), TempTableLockFilename)) {
    Int3();
    return 0;
  }

// Log this change
#ifndef RELEASE
  std::filesystem::path pathstr = std::filesystem::path(NetD3Dir) / "TableLog";
  FILE *logfile = fopen(pathstr.u8string().c_str(), "at");
  if (logfile) {
    char str[255 + 32];
    char date[255];
    time_t t;
    t = time(NULL);
    strftime(date, 254, "[%a %m/%d/%y %H:%M:%S]", localtime(&t));
    snprintf(str, sizeof(str), "%s Page %s (%s) last touched by %s\n", date, name, PageNames[pl->pagetype], TableUser);
    fwrite(str, 1, strlen(str), logfile);
    fflush(logfile);
    fclose(logfile);
  }
#endif

  return 1; // successful!
}

// Given a name and a pagetype, deletes the one already inside the lock file
int mng_DeletePagelock(char *name, int pagetype) {
  CFILE *infile, *outfile;
  int done = 0, deleted = 0;
  mngs_Pagelock temp_pl;

  mprintf(0, "Deleting pagelock %s.\n", name);

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    return 0;
  }
  outfile = (CFILE *)cfopen(TempTableLockFilename, "wb");
  if (!outfile) {
    cfclose(infile);
    strcpy(ErrorString, "Couldn't open temporary table lock file!");
    return 0;
  }

  while (!done) {
    if (mng_ReadPagelock(infile, &temp_pl)) {
      if (!stricmp(temp_pl.name, name) && pagetype == temp_pl.pagetype)
        deleted = 1;
      else
        mng_WritePagelock(outfile, &temp_pl);

    } else
      done = 1;
  }
  cfclose(infile);
  cfclose(outfile);

  if (!deleted) {
    Int3(); // Get Jason!
  }

  if (remove(TableLockFilename)) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem deleting the temp file - errno %d", errno);
    return (0);
  }
  if (rename(TempTableLockFilename, TableLockFilename.u8string().c_str())) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem renaming the temp file - errno %d", errno);

    return (0);
  }
  return 1; // successful!
}

// Given a list of names and a pagetype, deletes the ones already inside the lock file
int mng_DeletePagelockSeries(char *names[], int num, int pagetype) {
  CFILE *infile, *outfile;
  int done = 0, deleted = 0;
  mngs_Pagelock temp_pl;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    return 0;
  }
  outfile = (CFILE *)cfopen(TempTableLockFilename, "wb");
  if (!outfile) {
    cfclose(infile);
    strcpy(ErrorString, "Couldn't open temporary table lock file!");
    return 0;
  }

  while (!done) {
    if (mng_ReadPagelock(infile, &temp_pl)) {
      if (pagetype == temp_pl.pagetype) {
        int found = -1;

        for (int i = 0; i < num && found == -1; i++) {
          if (!stricmp(names[i], temp_pl.name)) {
            found = i;
          }
        }

        if (found == -1)
          mng_WritePagelock(outfile, &temp_pl);
        else
          mprintf(0, "Deleting pagelock %s.\n", names[found]);
      } else
        mng_WritePagelock(outfile, &temp_pl);

    } else
      done = 1;
  }
  cfclose(infile);
  cfclose(outfile);

  if (remove(TableLockFilename)) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem deleting the temp file - errno %d", errno);
    return (0);
  }
  if (rename(TempTableLockFilename, TableLockFilename.u8string().c_str())) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem renaming the temp file - errno %d", errno);

    return (0);
  }
  return 1; // successful!
}

// Goes through the pagelock table and deletes all duplicate entries
int mng_DeleteDuplicatePagelocks() {
  CFILE *infile; //,*outfile;
  int done = 0, deleted = 0;
  mngs_Pagelock temp_pl;
  mngs_Pagelock *already_read;
  int num = 0, duplicates = 0, i;

  already_read = (mngs_Pagelock *)mem_malloc(sizeof(mngs_Pagelock) * 8000);
  ASSERT(already_read);

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    return 0;
  }
  /*	outfile=(CFILE *)cfopen (TempTableLockFilename,"wb");
          if (!outfile)
          {
                  cfclose (infile);
                  strcpy (ErrorString,"Couldn't open temporary table lock file!");
                  return 0;
          }*/

  while (!done) {
    if (mng_ReadPagelock(infile, &temp_pl)) {
      int found = -1;
      for (i = 0; i < num; i++) {
        if (temp_pl.pagetype == already_read[i].pagetype && !stricmp(temp_pl.name, already_read[i].name)) {
          mprintf(0, "Found duplicated %s\n", temp_pl.name);
          found = i;
          duplicates++;
        }
      }

      if (found == -1) {
        // Hurray, a new entry
        strcpy(already_read[num].name, temp_pl.name);
        already_read[num].pagetype = temp_pl.pagetype;
        num++;
        ASSERT(num < 8000);
      }

    } else
      done = 1;
  }
  cfclose(infile);

  mprintf(0, "Found %d duplicates!\n", duplicates);
  /*	cfclose (outfile);

          if (remove (TableLockFilename))
          {
                  sprintf (ErrorString,"There was a problem deleting the temp file - errno %d",errno);
                  return (0);
          }
          if (rename (TempTableLockFilename,TableLockFilename))
          {
                  sprintf (ErrorString,"There was a problem renaming the temp file - errno %d",errno);

                  return (0);
          }*/
  mem_free(already_read);
  return 1; // successful!
}

// Given a list of names and a pagetype, unlocks the ones already inside the lock file
int mng_UnlockPagelockSeries(const char *names[], int *pagetypes, int num) {
  ASSERT(num < 500);

  uint8_t already_done[500];
  memset(already_done, 0, 500);

  CFILE *infile, *outfile;
  int done = 0, deleted = 0;
  mngs_Pagelock temp_pl;
  int total = 0;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    return 0;
  }
  outfile = (CFILE *)cfopen(TempTableLockFilename, "wb");
  if (!outfile) {
    cfclose(infile);
    strcpy(ErrorString, "Couldn't open temporary table lock file!");
    return 0;
  }

  while (!done) {
    if (mng_ReadPagelock(infile, &temp_pl)) {
      int found = -1;
      for (int i = 0; i < num && found == -1; i++) {
        if (!stricmp(names[i], temp_pl.name)) {
          found = i;
        }
      }

      if (found == -1)
        mng_WritePagelock(outfile, &temp_pl);
      else {
        if (pagetypes[found] == temp_pl.pagetype) {
          if (already_done[found]) {
            mprintf(0, "Found duplicate=%s\n", names[found]);
          } else {
            mprintf(0, "Replacing pagelock %s to UNLOCKED.\n", names[found]);
            strcpy(temp_pl.holder, "UNLOCKED");
            mng_WritePagelock(outfile, &temp_pl);
            total++;
            already_done[found] = 1;
          }

        } else
          mng_WritePagelock(outfile, &temp_pl);
      }

    } else
      done = 1;
  }
  cfclose(infile);
  cfclose(outfile);

  mprintf(0, "Unlocked %d pages\n", total);

  if (remove(TableLockFilename)) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem deleting the temp file - errno %d", errno);
    return (0);
  }
  if (rename(TempTableLockFilename, TableLockFilename.u8string().c_str())) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem renaming the temp file - errno %d", errno);

    return (0);
  }
  return 1; // successful!
}

// Writes a given pagelock out to the file pointed to by fp
void mng_WritePagelock(CFILE *fp, mngs_Pagelock *pl) {
  int i;

  // Write pagetype
  cf_WriteByte(fp, pl->pagetype);

  // Write name
  for (i = 0; i < PAGELOCK_NAME_LEN; i++)
    cf_WriteByte(fp, pl->name[i]);

  // Who owns this page?
  for (i = 0; i < PAGELOCK_NAME_LEN; i++)
    cf_WriteByte(fp, pl->holder[i]);
}

int mng_GetListOfLocks(mngs_Pagelock *pl, int max, char *who) {
  // Given a list of pagelocks, a max number allowed, and a specified user "who", fills in the
  // given pagelocks with all the pages that are locked by "who".

  CFILE *infile;
  mngs_Pagelock temp_pl;
  int done = 0, num = 0;

  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    return -1;
  }

  while (!done) {
    // Read in a page, compare it with the owner we're searching for.  If found, make a copy of it.

    if (mng_ReadPagelock(infile, &temp_pl)) {
      if (((who == NULL) && stricmp(temp_pl.holder, "UNLOCKED")) ||
          ((who != NULL) && (!stricmp(temp_pl.holder, who)))) {
        pl[num] = temp_pl;
        num++;
        if (num >= max)
          done = 1;
      }

    } else
      done = 1;
  }

  cfclose(infile);
  return num;
}

// Takes a pagelock and sets its holder name to UNLOCKED
void mng_OverrideToUnlocked(mngs_Pagelock *temp_pl) {
  int r;
#ifndef RELEASE
  r = mng_CheckIfPageOwned(temp_pl, TableUser);

  if (r == 1) {
    OutrageMessageBox("You own this page, so there is no use in you setting it to unlocked!");
    return;
  }

  int answer = OutrageMessageBox(
      MBOX_YESNO,
      "Are you sure you wish to override this page to unlocked? (choose 'NO' if you don't know what you're doing!)");

  if (answer == IDNO)
    return;

  answer = OutrageMessageBox(MBOX_YESNO,
                             "Do you wish to actually erase this pagelock? (Again, answer NO if you are not sure!)");

  if (!mng_MakeLocker())
    return;

  strcpy(temp_pl->holder, "UNLOCKED");

  if (answer == IDNO) {
    if (!mng_ReplacePagelock(temp_pl->name, temp_pl))
      OutrageMessageBox(ErrorString, "Error!");
    else {
      OutrageMessageBox("Page set to unlocked.");
    }
  } else {
    // Given a name and a pagetype, deletes the one already inside the lock file
    if (!mng_DeletePagelock(temp_pl->name, temp_pl->pagetype)) {
      OutrageMessageBox(ErrorString, "Error!");
    } else
      OutrageMessageBox("Pagelock deleted!");
  }
#endif
  mng_EraseLocker();
}
