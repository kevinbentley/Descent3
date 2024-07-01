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

 * $Logfile: /DescentIII/Main/newui_filedlg.cpp $
 * $Revision: 22 $
 * $Date: 10/25/99 10:46a $
 * $Author: Matt $
 *
 * File Dialog using NewUI class
 *
 * $Log: /DescentIII/Main/newui_filedlg.cpp $
 *
 * 22    10/25/99 10:46a Matt
 * Code from Duane that allows users to double-click on a directory in the
 * file dialog to open that folder.
 *
 * 21    9/07/99 4:33p Jeff
 * fixed crash due to not setting a pointer to NULL
 *
 * 20    5/10/99 10:23p Ardussi
 * changes to compile on Mac
 *
 * 19    5/10/99 9:21p Samir
 * Ardussi pointed out this small but significant error when checking for
 * valid path.
 *
 * 18    4/20/99 3:11p Jeff
 * handle invalid initial directory
 *
 * 17    4/20/99 3:07p Jeff
 * save last directory
 *
 * 16    4/20/99 11:46a Samir
 * numerous ui 'feel' fixes.
 *
 * 15    4/14/99 3:56a Jeff
 * fixed case mismatch in #includes
 *
 * 14    2/28/99 6:14p Jeff
 * use UID_OK and UID_CANCEL
 *
 * 13    2/28/99 2:57a Jeff
 * got rid of useless hotspots
 *
 * 12    2/28/99 2:23a Jeff
 * use new ui
 *
 * 11    1/29/99 5:22p Jeff
 * localization
 *
 * 10    1/27/99 5:47p Jeff
 * put up a message that files are being gathered...ease the fear of crash
 *
 * 9     1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 8     10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 7     9/28/98 4:35p Jeff
 * general UI changes and improvements
 *
 * 6     9/23/98 6:19p Jeff
 * finished up (hopefully) updating the config/ui dialogs to meet our
 * standard.  Keyboard/joystick config still needs some work
 *
 * 5     9/02/98 2:54p Jeff
 * added defines for text colors to be used throughout the game...fixed up
 * buddy menu too
 *
 * 4     8/19/98 2:18p Jeff
 * changed ddio_CleanPath
 *
 * 3     7/30/98 12:31p Jeff
 *
 * 2     7/29/98 5:39p Jeff
 * initial creation
 *
 * $NoKeywords: $
 */

#include <cstdlib>
#include <cstring>
#include <filesystem>

#include "mono.h"
#include "renderer.h"
#include "render.h"
#include "ddio.h"
#include "descent.h"
#include "game.h"
#include "cfile.h"
#include "application.h"
#include "newui.h"
#include "grtext.h"
#include "gamefont.h"
#include "stringtable.h"
#include "ConfigItem.h" //for colors
#include "mem.h"

newuiListBox *path_list = NULL;
char *path_edit = NULL;
char *working_filename = NULL;
char *working_listpath = NULL;
newuiSheet *fdlg_working_sheet = NULL;

char NewuiFileDlg_lastpath[_MAX_PATH] = {'\0'};

// border size of the UI window
#define UI_BORDERSIZE 20

// returns the number of files in path p, that matches wildcard
// it fills in buffer (up to maxcount) with the files found
int GetFilesInPath(char **buffer, int maxcount, const char *p, const char *wildcard);

// returns the number of directories in path p
// it fills in buffer (up to maxcount) with the directories found
int GetDirectoriesInPath(char **buffer, int maxcount, const char *p);

// Updates the given listbox with the directories and files that match wildcards (each wildcard seperates by a ;)
void UpdateFileList(newuiListBox *lb, const char *path, char *wildcards);

// Callback function for listbox
void FileSelectCallback(int index);

void FDlg_EnableWaitMessage(bool enable) {
#define FDWM_HEIGHT 128
#define FDWM_WIDTH 256

  static NewUIGameWindow *msgbox = NULL;
  static bool opened = false;
  newuiSheet *sheet;

  if (opened == enable) {
    Int3();
  }

  opened = enable;

  if (enable) {
    msgbox = new NewUIGameWindow;
    if (msgbox) {

      msgbox->Create(0, 0, FDWM_WIDTH, FDWM_HEIGHT, UIF_PROCESS_ALL | UIF_CENTER);

      sheet = msgbox->GetSheet();
      sheet->NewGroup(NULL, 45, 25);
      sheet->AddText(TXT_GETTINGFILES);

      msgbox->Open();
      sheet->Realize();

      // fake a DoUI
      DoUIFrame();
      rend_Flip();
    }
  } else {

    if (msgbox) {
      msgbox->Close();
      msgbox->Destroy();
      delete msgbox;
    }
    msgbox = NULL;
  }
}

bool IsDirectoryItem(char *item) {
  if (*item != ' ')
    return false;
  if (*(item + 1) != '[')
    return false;
  if (item[strlen(item) - 1] == ']')
    return true;
  return false;
}
// Callback function for listbox
void FileSelectCallback(int index) {
  if ((!path_edit) || (!working_filename) || (!path_list) || (!working_listpath))
    return;

  char file[_MAX_PATH];
  path_list->GetCurrentItem(file, _MAX_PATH);
  if (IsDirectoryItem(file))
    return; // we don't care about directories

  strncpy(working_filename, file, _MAX_FNAME - 1);
  working_filename[_MAX_FNAME - 1] = '\0';

  ddio_MakePath(file, working_listpath, working_filename, NULL);

  strncpy(path_edit, file, _MAX_PATH - 1);
  path_edit[_MAX_PATH - 1] = '\0';
  mprintf(0, "New Path: %s\n", path_edit);
  fdlg_working_sheet->UpdateChanges();
}

//	Displays a file/directory dialog box
//		path	- Initial path, will contain the chosen file/path on exit with true, must be at least _MAX_PATH
// in size 		title	- Title of the dialog 		wildc	- semicolon (;) seperated list of wildcards to
// be shown 		flags	- see header PFDF_ for flags
bool DoPathFileDialog(bool save_dialog, char *path, const char *title, const char *wildc, int flags) {
#define HS_CANCEL 0
#define HS_OK 1
#define HS_UPDIR 0
#define ED_WILDCARD 0
#define ED_FILENAME 1
#define ID_LISTBOX 25
#define ID_UPDIR 26
#define ID_WILDCARD 27
#define ID_FILENAME 28
#define ID_CANCEL UID_CANCEL
#define ID_OK UID_OK
  newuiTiledWindow window;
  newuiSheet *sheet;
  newuiListBox *listbox;
  char *edits[2];

  char wildcards[256];
  char working_path[_MAX_PATH];
  char working_file[_MAX_FNAME];

  if (!path)
    return false;
  if (!title)
    return false;
  if (!wildc)
    return false;

  strcpy(wildcards, wildc);
  strcpy(working_file, "");

  // figure out the correct path
  char oldpath[_MAX_PATH];
  ddio_GetWorkingDir(oldpath, _MAX_PATH);
  if (!ddio_SetWorkingDir(path)) {
    // try to use last good path
    if (!ddio_SetWorkingDir(NewuiFileDlg_lastpath)) {
      strcpy(path, LocalD3Dir);
    } else {
      strcpy(path, NewuiFileDlg_lastpath);
    }
  }
  ddio_SetWorkingDir(oldpath);

  // Create all the UI Items
  window.Create(title, 0, 0, 384, 288);
  fdlg_working_sheet = sheet = window.GetSheet();

  sheet->NewGroup(NULL, 10, 0);
  listbox = sheet->AddListBox(268, 100, ID_LISTBOX);

  sheet->NewGroup(NULL, 0, 145);
  edits[ED_FILENAME] = sheet->AddEditBox(NULL, _MAX_PATH, 300, ID_FILENAME);
  edits[ED_WILDCARD] = sheet->AddEditBox(NULL, 256, 150, ID_WILDCARD);
  sheet->AddLongButton(TXT_UPTOPARENTDIR, ID_UPDIR);

  sheet->NewGroup(NULL, 200, 160);
  sheet->AddButton((save_dialog) ? TXT_SAVE : TXT_OPEN, ID_OK);
  sheet->AddButton(TXT_CANCEL, ID_CANCEL);

  working_filename = working_file;
  working_listpath = working_path;
  path_edit = edits[ED_FILENAME];
  path_list = listbox;

  listbox->SetSelectChangeCallback(FileSelectCallback);

  ddio_CleanPath(working_path, path);
  UpdateFileList(listbox, working_path, wildcards);

  strncpy(edits[ED_FILENAME], working_path, _MAX_PATH - 1);
  edits[ED_FILENAME][_MAX_PATH - 1] = '\0';

  strncpy(edits[ED_WILDCARD], wildcards, 255);
  edits[ED_WILDCARD][255] = '\0';

  bool ret = false;
  bool exit_menu = false;

  sheet->SetInitialFocusedGadget(ID_LISTBOX);

  window.Open();
  while (!exit_menu) {
    int res = window.DoUI();

    // handle all UI results.
    switch (res) {
    case ID_OK: {
      strcpy(path, edits[ED_FILENAME]);

      if (path[0] == '\0') {
        DoMessageBox(TXT_ERROR, TXT_ERRCHOOSEFILE, MSGBOX_OK);
      } else {
        if (std::filesystem::is_directory(path)) {
          char newpath[_MAX_PATH];
          char file[_MAX_PATH];
          int selection = listbox->GetCurrentIndex();
          if ((selection >= 0) && (listbox->GetCurrentItem(file, _MAX_PATH))) {
            if (*file) {
              strcpy(working_file, "");

              // ok the user double clicked on a directory
              // convert file without the brackets
              file[strlen(file) - 1] = '\0';
              if (strlen(working_path) != 0)
                ddio_MakePath(newpath, working_path, file + 2, NULL);
              else
                strcpy(newpath, file + 2);

              UpdateFileList(listbox, newpath, wildcards);
              ddio_CleanPath(working_path, newpath);

              strncpy(edits[ED_FILENAME], working_path, _MAX_PATH - 1);
              edits[ED_FILENAME][_MAX_PATH - 1] = '\0';
            }
          }
          //						DoMessageBox(TXT_ERROR,TXT_ERRCHOOSEFILE,MSGBOX_OK);
        } else {
          if (flags & PFDF_FILEMUSTEXIST) {
            if (!cfexist(path)) {
              DoMessageBox(TXT_ERROR, TXT_ERRFILENOTEXIST, MSGBOX_OK);
            } else {
              ddio_SplitPath(path, NewuiFileDlg_lastpath, NULL, NULL);
              ret = exit_menu = true;
            }
          } else {
            ddio_SplitPath(path, NewuiFileDlg_lastpath, NULL, NULL);
            ret = exit_menu = true;
          }
        }
      }
    } break;
    case ID_CANCEL:
      ret = false;
      exit_menu = true;
      break;
    case ID_LISTBOX: {
      char newpath[_MAX_PATH];
      char file[_MAX_PATH];
      // check to see if the double clicked on a dir
      int selection = listbox->GetCurrentIndex();

      if ((selection >= 0) && (listbox->GetCurrentItem(file, _MAX_PATH))) {
        if (*file) {
          if (IsDirectoryItem(file)) {
            strcpy(working_file, "");

            // ok the user double clicked on a directory
            // convert file without the brackets
            file[strlen(file) - 1] = '\0';
            if (strlen(working_path) != 0)
              ddio_MakePath(newpath, working_path, file + 2, NULL);
            else
              strcpy(newpath, file + 2);

            UpdateFileList(listbox, newpath, wildcards);
            ddio_CleanPath(working_path, newpath);

            strncpy(edits[ED_FILENAME], working_path, _MAX_PATH - 1);
            edits[ED_FILENAME][_MAX_PATH - 1] = '\0';
          } else {
            // double click on a file
            strcpy(working_file, file);
            FileSelectCallback(selection);
            strcpy(file, edits[ED_FILENAME]);

            // the user wants a file
            if (flags & PFDF_FILEMUSTEXIST) {
              if (cfexist(file)) {
                exit_menu = true;
                ret = true;
                strcpy(path, file);
                ddio_SplitPath(path, NewuiFileDlg_lastpath, NULL, NULL);
              } else {
                // invalid file
                DoMessageBox(TXT_ERROR, TXT_ERRCHOOSEFILE, MSGBOX_OK);
              }
            } else {
              strcpy(path, file);
              exit_menu = true;
              ret = true;
              ddio_SplitPath(path, NewuiFileDlg_lastpath, NULL, NULL);
            }
          }
        }
      }
    } break;
    case ID_UPDIR: {
      char newpath[_MAX_PATH];
      strcpy(working_file, "");
      ddio_GetParentPath(newpath, working_path);
      strcpy(working_path, newpath);

      UpdateFileList(listbox, working_path, wildcards);
      strncpy(edits[ED_FILENAME], working_path, _MAX_PATH - 1);
      edits[ED_FILENAME][_MAX_PATH - 1] = '\0';
    } break;
    case ID_WILDCARD: {
      strcpy(wildcards, edits[ED_WILDCARD]);
      UpdateFileList(listbox, working_path, wildcards);
    } break;
    case ID_FILENAME: {
      char c[_MAX_PATH];
      strcpy(c, edits[ED_FILENAME]);

      if (strlen(c) > 0) {
        if (!std::filesystem::is_directory(c)) {
          // the user wants a file
          if (flags & PFDF_FILEMUSTEXIST) {
            if (cfexist(c)) {
              strcpy(path, c);
              exit_menu = true;
              ret = true;
              ddio_SplitPath(path, NewuiFileDlg_lastpath, NULL, NULL);
            } else {
              // invalid file
              DoMessageBox(TXT_ERROR, TXT_ERRFILENOTEXIST, MSGBOX_OK);
            }
          } else {
            strcpy(path, c);
            ddio_SplitPath(path, NewuiFileDlg_lastpath, NULL, NULL);
            exit_menu = true;
            ret = true;
          }
        } else {
          // just change directories
          strcpy(working_path, c);
          UpdateFileList(listbox, working_path, wildcards);
        }
      }
    } break;
    }
  }

  if (ret) {
    mprintf(0, "Selected Filename: %s\n", path);
  } else {
    mprintf(0, "Cancel!\n");
  }

  window.Close();
  window.Destroy();

  working_filename = NULL;
  working_listpath = NULL;
  path_edit = NULL;
  path_list = NULL;

  return ret;
}

// returns the number of files in path p, that matches wildcard
// it fills in buffer (up to maxcount) with the files found
int GetFilesInPath(char **buffer, int maxcount, const char *p, const char *wildcard) {
  ASSERT(buffer);
  ASSERT(p);
  ASSERT(wildcard);
  if (maxcount <= 0)
    return 0;

  char old_path[_MAX_PATH], path[_MAX_PATH];
  ddio_GetWorkingDir(old_path, _MAX_PATH);
  if (!ddio_SetWorkingDir(p)) {
    // directory doesn't exist
    ddio_SetWorkingDir(old_path);
    return -1;
  }

  ddio_GetWorkingDir(path, _MAX_PATH);
  if (stricmp(path, p)) {
    // the working dir is not the same as the passed in path, so try to create a correct path and set it
    ddio_MakePath(path, p, "", NULL);
    if (!ddio_SetWorkingDir(path)) {
      ddio_SetWorkingDir(old_path);
      return -1;
    }
  }

  int count = 0;
  char tempbuffer[_MAX_PATH];

  if (ddio_FindFileStart(wildcard, tempbuffer)) {
    if (!std::filesystem::is_directory(tempbuffer)) {
      buffer[count] = mem_strdup(tempbuffer);
      count++;
    }

    bool done = false;

    while (!done) {
      if (ddio_FindNextFile(tempbuffer)) {
        if (!std::filesystem::is_directory(tempbuffer)) {
          if (count < maxcount)
            buffer[count] = mem_strdup(tempbuffer);
          count++;
        }
      } else
        done = true;
    }
  }
  ddio_FindFileClose();
  ddio_SetWorkingDir(old_path);
  return count;
}

// returns the number of directories in path p
// it fills in buffer (up to maxcount) with the directories found
int GetDirectoriesInPath(char **buffer, int maxcount, const char *p) {
  ASSERT(buffer);
  ASSERT(p);
  if (maxcount <= 0)
    return 0;

  int i;
  for (i = 0; i < maxcount; i++) {
    buffer[i] = NULL;
  }

  char old_path[_MAX_PATH], path[_MAX_PATH];

  ddio_GetWorkingDir(old_path, _MAX_PATH);
  if (!ddio_SetWorkingDir(p)) {
    // directory doesn't exist
    ddio_SetWorkingDir(old_path);
    return -1;
  }

  ddio_GetWorkingDir(path, _MAX_PATH);
  if (stricmp(path, p)) {
    // the working dir is not the same as the passed in path, so try to create a correct path and set it
    ddio_MakePath(path, p, "", NULL);
    if (!ddio_SetWorkingDir(path)) {
      ddio_SetWorkingDir(old_path);
      return -1;
    }
  }

  int count = 0;
  char tempbuffer[_MAX_PATH];

  if (ddio_FindFileStart("*", tempbuffer)) {
    if (std::filesystem::is_directory(tempbuffer)) {
      buffer[count] = mem_strdup(tempbuffer);
      count++;
    }

    bool done = false;

    while (!done) {
      if (ddio_FindNextFile(tempbuffer)) {
        if (std::filesystem::is_directory(tempbuffer)) {
          if (count < maxcount)
            buffer[count] = mem_strdup(tempbuffer);
          count++;
        }
      } else
        done = true;
    }
  }
  ddio_FindFileClose();
  ddio_SetWorkingDir(old_path);
  return count;
}

// Updates the given listbox with the directories and files that match wildcards (each wildcard seperates by a ;)
void UpdateFileList(newuiListBox *lb, const char *path, char *wildcards) {
  FDlg_EnableWaitMessage(true);
  lb->RemoveAll();

  // if path is NULL or 0 length string then just list the directories
  if ((!path) || (*path == '\0')) {
    char *roots[30];
    int rootcount = ddio_GetFileSysRoots((char **)&roots, 30);
    if (!rootcount) {
      FDlg_EnableWaitMessage(false);
      return;
    }
    char tempbuffer[5];
    for (int i = 0; i < rootcount; i++) {
      if (roots[i]) {
        snprintf(tempbuffer, sizeof(tempbuffer), " [%s]", roots[i]);
        lb->AddItem(tempbuffer);
        mem_free(roots[i]);
      }
    }
    FDlg_EnableWaitMessage(false);
    return;
  }

  char **dirs = NULL;
  char *tempdir[1];
  char fullpath[_MAX_PATH];
  ddio_GetRootFromPath(path, fullpath);
  if (!stricmp(path, fullpath)) {
    // we are are the root of the drive, make a dummy path
    ddio_MakePath(fullpath, path, "", NULL);
  } else {
    // just use this
    strcpy(fullpath, path);
  }

  int dircount = GetDirectoriesInPath((char **)&tempdir, 1, fullpath);
  if (dircount == -1) {
    // invalid directory/path
    DoMessageBox(TXT_ERROR, TXT_ERRPATHNOTVALID, MSGBOX_OK);
    FDlg_EnableWaitMessage(false);
    return;
  }

  if (tempdir[0])
    mem_free(tempdir[0]);
  if (dircount > 0) {
    dirs = (char **)mem_malloc(sizeof(char *) * dircount);
    if (!dirs) {
      // out of memory!
      dircount = 0;
    } else {
      GetDirectoriesInPath(dirs, dircount, fullpath);
    }
  } else {
    dircount = 0;
    dirs = NULL;
  }

  // figure out how many wildcards we have, and allocate accordingly
  int wildcard_count = 0;
  char *wc = NULL;
  char **wc_strings = NULL;
  int *wc_count = NULL;
  char ***filelist = NULL;
  int total_files = 0;
  int wildcard_len = 0;
  char *strptr = NULL;

  // save the wildcards
  wc = (char *)mem_malloc(strlen(wildcards) + 2);
  if (!wc) {
    FDlg_EnableWaitMessage(false);
    return;
  }

  // make sure there is a tailing ;
  strcpy(wc, wildcards);
  wildcard_len = strlen(wildcards);
  if (wc[wildcard_len - 1] != ';') {
    wc[wildcard_len] = ';';
    wc[wildcard_len + 1] = '\0';
  }

  // break up wildcard string, counting the number of wildcards as we go
  strptr = wc;
  while (*strptr != '\0') {
    if (*strptr == ';') {
      *strptr = '\0';
      wildcard_count++;
    }
    strptr++;
  }

  if (wildcard_count > 0) {
    wc_strings = (char **)mem_malloc(sizeof(char *) * wildcard_count);
    wc_count = (int *)mem_malloc(sizeof(int) * wildcard_count);

    if ((wc_strings) && (wc_count)) {
      int e;

      // get each individual string of the wildcard strings
      strptr = wc;
      for (e = 0; e < wildcard_count; e++) {
        wc_strings[e] = mem_strdup(strptr);
        strptr += strlen(strptr) + 1;
      }

      // malloc memory...an array of (array of char *) for each wildcard
      filelist = (char ***)mem_malloc(sizeof(char **) * wildcard_count);
      if (!filelist) {
        // there was an error allocating the memory
        if (wc) {
          mem_free(wc);
          wc = NULL;
        }
        for (e = 0; e < wildcard_count; e++) {
          if (wc_strings[e])
            mem_free(wc_strings[e]);
          wc_count[e] = 0;
          filelist[e] = NULL;
        }

        mem_free(wc_strings);
        wc_strings = NULL;
        goto wildcard_err;
      }

      char *templist[1];
      int count;

      total_files = 0;

      for (e = 0; e < wildcard_count; e++) {
        // we just need to get how many of each wildcard there is in the directory
        templist[0] = NULL;
        count = GetFilesInPath((char **)&templist, 1, path, wc_strings[e]);
        if (count == -1) {
          // invalid path
          wc_count[e] = 0;
          filelist[e] = NULL;
        } else {
          total_files += count;
          if (templist[0]) {
            mem_free(templist[0]);
            templist[0] = NULL;
          }

          if (count > 0) {
            // now we need to get all the files for the wildcard
            filelist[e] = (char **)mem_malloc(sizeof(char *) * count);
            if (filelist[e]) {
              GetFilesInPath(filelist[e], count, path, wc_strings[e]);
              wc_count[e] = count;
            } else {
              wc_count[e] = 0;
            }
          } else {
            filelist[e] = NULL;
            wc_count[e] = 0;
          }
        } // end if(count==-1)

        // we don't need the wildcard anymore, we can free it up
        if (wc_strings[e])
          mem_free(wc_strings[e]);
      } // end for(e=0;e<wildcard_count;e++)

      // free up allocated memory that we don't need anymore
      mem_free(wc_strings);
      if (wc)
        mem_free(wc);

      wc_strings = NULL;
      wc = NULL;
    } else {
      // we couldn't allocate memory for wildcard strings
      total_files = 0;
      filelist = NULL;
      if (wc_count) {
        for (int e = 0; e < wildcard_count; e++)
          wc_count[e] = 0;
      }
    }
  }

wildcard_err:
  if ((dircount + total_files) == 0) {
    FDlg_EnableWaitMessage(false);
    return;
  }

  // lbfilelist = new UITextItem[dircount+total_files];
  char tempbuffer[_MAX_PATH + 1];
  int i;

  for (i = 0; i < dircount; i++) {
    if (dirs[i]) {
      snprintf(tempbuffer, sizeof(tempbuffer), " [%s]", dirs[i]);
      lb->AddItem(tempbuffer);
      mem_free(dirs[i]);
    }
  }
  i = dircount;
  if (total_files > 0) {
    for (int j = 0; j < wildcard_count; j++) {
      int num_files;
      char **wc_filelist;
      num_files = wc_count[j];
      if (num_files > 0) {
        wc_filelist = filelist[j];
        for (int k = 0; k < num_files; k++) {
          if (wc_filelist[k]) {
            lb->AddItem(wc_filelist[k]);
            i++;
            mem_free(wc_filelist[k]);
            wc_filelist[k] = NULL;
          }
        }
        if (wc_filelist) {
          mem_free(wc_filelist);
          wc_filelist = NULL;
        }
      }
    }
  }

  if (dirs)
    mem_free(dirs);
  if (filelist)
    mem_free(filelist);
  if (wc_count)
    mem_free(wc_count);
  FDlg_EnableWaitMessage(false);
}
