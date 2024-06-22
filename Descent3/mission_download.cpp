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

 * $Logfile: /DescentIII/Main/mission_download.cpp $
 * $Revision: 29 $
 * $Date: 10/21/01 6:34p $
 * $Author: Kevin $
 *
 *  Mission file downloading system
 *
 *
 * $Log: /DescentIII/Main/mission_download.cpp $
 *
 * 29    10/21/01 6:34p Kevin
 * minor fix to prevent a buffer overflow (not a reported bug, just
 * something I noticed and thought was a good idea to avoid).
 *
 * 28    8/29/01 4:04p Matt
 * Changed download directory from pxo.net to outrage.com
 *
 * 27    4/28/00 6:48p Jeff
 * created _strlwr for linux
 *
 * 26    4/19/00 5:18p Matt
 * From Duane for 1.4
 * ifdef-out mod download code for Mac
 *
 * 25    3/26/00 10:29p Kevin
 * MOD Downloader for 1.4 patch.
 *
 * 24    11/04/99 12:35a Chris
 * Added support for Merc
 *
 * 23    10/22/99 1:36p Matt
 * Mac merge
 *
 * 22    10/18/99 1:27p Kevin
 * Added cf_IsFileInHog
 *
 * 21    8/23/99 5:12p Kevin
 * Proxy support
 *
 * 20    8/15/99 8:07p Jeff
 * display interface when extracting files from a zip
 *
 * 19    8/15/99 4:27p Kevin
 * possibly fixed mission download bug
 *
 * 18    8/13/99 8:00p Jeff
 * handle zip files with new unzip class
 *
 * 17    7/21/99 3:48p Kevin
 * changed left border.
 *
 * 16    5/18/99 10:31p Kevin
 * fixed problem with joining d3.mn3 games and using the minimum install
 * level
 *
 * 15    4/23/99 6:02p Kevin
 * fixed bug when you can't download a mission
 *
 * 14    4/14/99 3:56a Jeff
 * fixed case mismatch in #includes
 *
 * 13    4/07/99 9:38a Kevin
 * Fixed bug when there were no URLs in the mission file
 *
 * 12    4/03/99 9:26p Jeff
 * changed dialogs that weren't using UID_OK and UID_CANCEL to use and
 * handle them properly
 *
 * 11    3/23/99 8:57a Kevin
 * Fixed a bug if the user hits cancel
 *
 * 10    3/03/99 2:32p Kevin
 *
 * 9     3/03/99 12:33a Kevin
 * Minor OEM changes
 *
 * 8     2/07/99 1:17a Jeff
 * peppered UI dialogs that were missing NEWUIRES_FORCEQUIT to handle it
 *
 * 7     2/03/99 4:20p Kevin
 * Got multiplayer working with .mn3 files, and setup autodownloading
 *
 * 6     1/29/99 5:22p Jeff
 * localization
 *
 * 5     12/30/98 12:42p Kevin
 * Mission downloading localization
 *
 * 4     12/30/98 12:19p Kevin
 *
 * 3     12/30/98 12:15p Kevin
 * Auto Mission Download system
 *
 * 2     12/28/98 2:22p Kevin
 * Initial mission downloading system
 *
 * 1     12/28/98 11:42a Kevin
 *
 *
 */

#include <stdio.h>

#include "pstypes.h"
#include "mem.h"
#include "args.h"
#include "descent.h"
#include "networking.h"
#include "multi.h"
#include "ui.h"
#include "newui.h"
#include "ddio.h"
#include "stringtable.h"
#include "multi_dll_mgr.h"
// #include "inetgetfile.h"
#include "grtext.h"
#include "Mission.h"
#include "mission_download.h"
#include "renderer.h"

#include "unzip.h"

int Got_url;
msn_urls msn_URL = {"", {"", "", "", "", ""}};
msn_urls Net_msn_URLs;

extern char Proxy_server[200];
extern int16_t Proxy_port;

int msn_ExtractZipFile(char *zipfilename, char *mn3name);

// Request a URL structure from a server containing a list of download locations
// For the current mission being played
msn_urls *msn_GetURL(network_address *net_addr) {

  int count = 0;
  int size;
  int tries = 0;
  uint8_t data[MAX_GAME_DATA_SIZE];
  float start_time;
  network_address from_addr;

  size = START_DATA(MP_ASK_FOR_URL, data, &count);
  END_DATA(count, data, size);

  Got_url = -1;

  while (tries < 5 && Got_url == -1) {
    // Send the request
    ASSERT(size > 0);
    nw_Send(net_addr, data, count, 0);
    tries++;

    start_time = timer_GetTime();
    while ((timer_GetTime() - start_time < URL_ASK_POLL_TIME) && Got_url == -1) {
      int packsize;
      while (((packsize = nw_Receive(Multi_receive_buffer, &from_addr)) > 0) && Got_url == -1) {
        MultiProcessBigData(Multi_receive_buffer, packsize, &from_addr);
      }
    }
  }

  if (tries >= 5 || Got_url != 1)
    return NULL;

  return &msn_URL;
}

// Get the list of URLs in the msn file
msn_urls *msn_GetURL(char *msnfile) {
  // static msn_urls url;
  // strcpy(url.msnname,msnfile);
  return &Net_msn_URLs;
}

#define MSN_DWNLD_CHOICE_H 256
#define MSN_DWNLD_CHOICE_W 512

// Present the user with a list of URLs to download from. Return the 0 based selection, or -1 if cancel is hit.
int msn_ShowDownloadChoices(msn_urls *urls) {
  UITextItem title_text(TXT_DOWNLOADPROMPT, UICOL_WINDOW_TITLE);
  UITextItem title1_text(TXT_DONTHAVEMSN, UICOL_WINDOW_TITLE);
  UITextItem header_text(TXT_DOWNLOADMSN, UICOL_TEXT_NORMAL);
  UIHotspot ok_hot;
  UIHotspot cancel_hot;
  NewUIListBox choices_list;

  NewUIGameWindow menu_wnd;

  UIText texts[10];

  int exit_menu = 0;
  int ret = 0;

  menu_wnd.Create(10, 10, MSN_DWNLD_CHOICE_W, MSN_DWNLD_CHOICE_H, UIF_PROCESS_ALL | UIF_CENTER);
  texts[0].Create(&menu_wnd, &header_text, 0, 8, UIF_CENTER);
  texts[1].Create(&menu_wnd, &title_text, 0, 55, UIF_CENTER);
  texts[2].Create(&menu_wnd, &title1_text, 0, 35, UIF_CENTER);

  UITextItem ok_off(TXT_OK, UICOL_HOTSPOT_LO, UIALPHA_HOTSPOT_LO);
  UITextItem ok_on(TXT_OK, UICOL_HOTSPOT_HI, UIALPHA_HOTSPOT_HI);
  UITextItem cancel_off(TXT_CANCEL, UICOL_HOTSPOT_LO, UIALPHA_HOTSPOT_LO);
  UITextItem cancel_on(TXT_CANCEL, UICOL_HOTSPOT_HI, UIALPHA_HOTSPOT_HI);

  int ok_x, cancel_x;
  GetCenteredTextPos(menu_wnd.W(), 20, ok_on.width(), cancel_on.width(), &ok_x, &cancel_x);

  ok_hot.Create(&menu_wnd, UID_OK, KEY_ENTER, &ok_off, &ok_on, ok_x, MSN_DWNLD_CHOICE_H - OKCANCEL_YOFFSET, 0, 0,
                UIF_FIT);
  cancel_hot.Create(&menu_wnd, UID_CANCEL, KEY_ESC, &cancel_off, &cancel_on, cancel_x,
                    MSN_DWNLD_CHOICE_H - OKCANCEL_YOFFSET, 0, 0, UIF_FIT);

  choices_list.Create(&menu_wnd, 1, 0, 70, 480, 128, UIF_CENTER | UILB_NOSORT);
  choices_list.SetSelectedColor(UICOL_LISTBOX_HI);
  choices_list.SetHiliteColor(UICOL_LISTBOX_HI);
  choices_list.RemoveAll();

  UITextItem urlti[MAX_MISSION_URL_COUNT];
  // urls
  int i;
  int urlcount = 0;
  for (i = 0; i < MAX_MISSION_URL_COUNT; i++) {
    if (urls->URL[i][0]) {
      urlti[i] = UITextItem(urls->URL[i], UICOL_LISTBOX_LO);
      choices_list.AddItem(&urlti[i]);
      urlcount++;
    }
  }
  if (urlcount == 0) {
    // Message that the mission can't be downloaded
    DoMessageBox(TXT_ERROR, TXT_FMTCANTDNLD, MSGBOX_OK);
    menu_wnd.Destroy();
    return -1;
  }
  menu_wnd.Open();

  while (!exit_menu) {
    int res;

    res = DoUI();
    switch (res) {
    case NEWUIRES_FORCEQUIT:
    case UID_CANCEL:
      ret = -1;
      menu_wnd.Close();
      exit_menu = 1;
      break;
    case UID_OK:
      ret = choices_list.GetSelectedIndex();
      menu_wnd.Close();
      exit_menu = 1;
      break;
    }
  }
  menu_wnd.Destroy();
  return ret;
}

#define MSN_REFRESH_INTERVAL .5

#define MSN_DWNLD_STATUS_H 256
#define MSN_DWNLD_STATUS_W 512

#define MSN_BORDER_W 30
#define MSN_BORDER_H 40

#define MSN_COL_1 MSN_BORDER_W
#define MSN_COL_2 ((MSN_DWNLD_STATUS_W / 2) + (MSN_BORDER_W / 2))

#define MSN_ROW_1 MSN_BORDER_H
#define MSN_ROW_2 (MSN_BORDER_H + 30)
#define MSN_ROW_3 (MSN_BORDER_H + 60)
#define MSN_ROW_4 (MSN_BORDER_H + 90)
#define MSN_ROW_5 (MSN_BORDER_H + 120)

#define DOWNLOAD_STATUS_URL_TEXT TXT_FMTDOWNLOADING
#define DOWNLOAD_STATUS_RCVD_TEXT TXT_FMTRECEIVED
#define DOWNLOAD_STATUS_TOTAL_TEXT TXT_FMTTOTAL
#define DOWNLOAD_STATUS_ELAPS_TEXT TXT_FMTTIMEELAPSED
#define DOWNLOAD_STATUS_TIME_R_TEXT TXT_FMTTIMELEFT
#define DOWNLOAD_STATUS_XFERRATE_TEXT TXT_FMTXFERRATE

#define MSN_MAX_STRING_LEN 100

// Start downloading the file at the url specifies, showing a status screen
// Return codes:
// 0 Failed or cancelled
// 1 Success
int msn_DownloadWithStatus(char *url, char *filename) {
  return 0;
  /*
  char qualfile[_MAX_PATH*2];
  float last_refresh;
  int total_bytes = 0;
  int received_bytes = 0;
  int time_elapsed = 0;
  int time_remain = 0;
  int xfer_rate = 0;
  int starttime = timer_GetTime();
  bool file_is_zip = false;

  //check to see if we are downloading a zip file
  char *url_ptr;
  url_ptr = url + strlen(url);
  while(url_ptr > url && *url_ptr!='.') url_ptr--;
  if(*url_ptr=='.')
  {
          //now see if the rest of the extension is ZIP
          if(!stricmp(url_ptr,".ZIP"))
          {
                  mprintf(0,"We're downloading a zip file!!!\n");
                  file_is_zip = true;
          }
  }

  char fmturl[MSN_MAX_STRING_LEN];
  char fmtrcvd[MSN_MAX_STRING_LEN];
  char fmttotal[MSN_MAX_STRING_LEN];
  char fmtelaps[MSN_MAX_STRING_LEN];
  char fmttimer[MSN_MAX_STRING_LEN];
  char fmtrate[MSN_MAX_STRING_LEN];

  sprintf(fmturl,DOWNLOAD_STATUS_URL_TEXT,url);
  msn_ClipURLToWidth(MSN_DWNLD_STATUS_W-(MSN_COL_1+MSN_BORDER_W),fmturl);
  sprintf(fmtrcvd,DOWNLOAD_STATUS_RCVD_TEXT,received_bytes);
  sprintf(fmttotal,DOWNLOAD_STATUS_TOTAL_TEXT,total_bytes);
  sprintf(fmtelaps,DOWNLOAD_STATUS_ELAPS_TEXT,msn_SecondsToString(time_elapsed));
  sprintf(fmttimer,DOWNLOAD_STATUS_TIME_R_TEXT,msn_SecondsToString(time_remain));
  sprintf(fmtrate,DOWNLOAD_STATUS_XFERRATE_TEXT,xfer_rate);

  if(file_is_zip)
  {
          char fname[_MAX_FNAME];
          char *s_ptr,*d_ptr;
          s_ptr = filename;
          d_ptr = fname;
          while(*s_ptr && *s_ptr!='.'){ *d_ptr = *s_ptr; s_ptr++; d_ptr++;}
          *d_ptr = '\0';
          strcat(fname,".zip");
          ddio_MakePath(qualfile,D3MissionsDir,fname,NULL);
  }else
  {
          ddio_MakePath(qualfile,D3MissionsDir,filename,NULL);
  }
  InetGetFile *getmsnfile;
  if(Proxy_server[0])
  {
          getmsnfile = new InetGetFile(url,qualfile,Proxy_server,Proxy_port);
  }
  else
  {
          getmsnfile = new InetGetFile(url,qualfile);
  }

  UITextItem title_text(TXT_MD_DOWNLOADSTATUS,UICOL_TEXT_NORMAL);

  UIHotspot cancel_hot;

  UITextItem download_text(fmturl,UICOL_TEXT_NORMAL);;
  UITextItem rcvd_text(fmtrcvd,UICOL_TEXT_NORMAL);
  UITextItem total_text(fmttotal,UICOL_TEXT_NORMAL);
  UITextItem elaps_text(fmtelaps,UICOL_TEXT_NORMAL);
  UITextItem time_r_text(fmttimer,UICOL_TEXT_NORMAL);
  UITextItem rate_text(fmtrate,UICOL_TEXT_NORMAL);

  NewUIGameWindow menu_wnd;

  UIText texts[10];
  UIProgress progress;

  int exit_menu=0;
  int ret=0;

  menu_wnd.Create(10,10,MSN_DWNLD_STATUS_W,MSN_DWNLD_STATUS_H,UIF_PROCESS_ALL | UIF_CENTER);
  texts[0].Create (&menu_wnd,&title_text,0,8,UIF_CENTER);
  texts[1].Create (&menu_wnd,&download_text,MSN_COL_1,MSN_ROW_1,0);
  texts[2].Create (&menu_wnd,&rcvd_text,MSN_COL_1,MSN_ROW_2,0);
  texts[3].Create (&menu_wnd,&total_text,MSN_COL_2,MSN_ROW_2,0);
  texts[4].Create (&menu_wnd,&elaps_text,MSN_COL_1,MSN_ROW_3,0);
  texts[5].Create (&menu_wnd,&time_r_text,MSN_COL_2,MSN_ROW_3,0);
  texts[6].Create (&menu_wnd,&rate_text,MSN_COL_1,MSN_ROW_4,0);

  UITextItem cancel_off(TXT_CANCEL,UICOL_HOTSPOT_LO,UIALPHA_HOTSPOT_LO);
  UITextItem cancel_on(TXT_CANCEL,UICOL_HOTSPOT_HI,UIALPHA_HOTSPOT_HI);

  progress.Create(&menu_wnd,MSN_COL_1,MSN_ROW_5,MSN_DWNLD_STATUS_W-(MSN_BORDER_W*2),35,0);

  int cancel_x = 0;

  cancel_hot.Create(&menu_wnd, UID_CANCEL, KEY_ESC, &cancel_off,&cancel_on,
                                                                  cancel_x, MSN_DWNLD_STATUS_H - OKCANCEL_YOFFSET,
  0,0,UIF_FIT|UIF_CENTER); menu_wnd.Open();

  last_refresh = timer_GetTime()-MSN_REFRESH_INTERVAL;

  while (!exit_menu)
  {
          int res;

          if((timer_GetTime()-last_refresh)>MSN_REFRESH_INTERVAL)
          {

                  //Update the dialog
                  //mprintf(0,"!");

                  if(getmsnfile->IsFileReceived())
                  {
                          //File transfer successful!
                          mprintf(0,"Succesfully received the file!\n");
                          exit_menu = 1;

                          if(file_is_zip)
                          {
                                  // now we gotta handle the zip file
                                  ret = msn_ExtractZipFile(qualfile,filename);
                          }else
                          {
                                  ret = 1;
                          }
                  }

                  if(getmsnfile->IsFileError())
                  {
                          //File transfer Error!
                          DoMessageBox(TXT_ERROR,TXT_FMTCANTDNLD,MSGBOX_OK);
                          //Delete the file that didn't finish!
                          ddio_DeleteFile(qualfile);
                          mprintf(0,"Couldn't download the file! Error: %d\n",getmsnfile->GetErrorCode());
                          exit_menu = 1;
                          ret = 0;
                  }

                  last_refresh = timer_GetTime();
                  received_bytes = getmsnfile->GetBytesIn();
                  total_bytes = getmsnfile->GetTotalBytes();

                  time_elapsed = timer_GetTime()-starttime;

                  if(total_bytes)
                  {
                          time_remain = ((float)(total_bytes-received_bytes))/((float)(received_bytes/time_elapsed));
                  }
                  if(time_elapsed&&received_bytes)
                  {
                          xfer_rate = ((float)(received_bytes/time_elapsed));
                  }
                  texts[1].Destroy();
                  texts[2].Destroy();
                  texts[3].Destroy();
                  texts[4].Destroy();
                  texts[5].Destroy();
                  texts[6].Destroy();

                  sprintf(fmturl,DOWNLOAD_STATUS_URL_TEXT,url);
                  msn_ClipURLToWidth(MSN_DWNLD_STATUS_W-(MSN_COL_1+MSN_BORDER_W),fmturl);
                  sprintf(fmtrcvd,DOWNLOAD_STATUS_RCVD_TEXT,received_bytes);
                  sprintf(fmttotal,DOWNLOAD_STATUS_TOTAL_TEXT,total_bytes);
                  sprintf(fmtelaps,DOWNLOAD_STATUS_ELAPS_TEXT,msn_SecondsToString(time_elapsed));
                  sprintf(fmttimer,DOWNLOAD_STATUS_TIME_R_TEXT,msn_SecondsToString(time_remain));
                  msn_ClipURLToWidth(MSN_DWNLD_STATUS_W-(MSN_COL_2+MSN_BORDER_W),fmttimer);
                  sprintf(fmtrate,DOWNLOAD_STATUS_XFERRATE_TEXT,xfer_rate);

                  download_text = UITextItem (fmturl,UICOL_TEXT_NORMAL);;
                  rcvd_text = UITextItem (fmtrcvd,UICOL_TEXT_NORMAL);
                  total_text = UITextItem (fmttotal,UICOL_TEXT_NORMAL);
                  elaps_text = UITextItem (fmtelaps,UICOL_TEXT_NORMAL);
                  time_r_text = UITextItem (fmttimer,UICOL_TEXT_NORMAL);
                  rate_text = UITextItem (fmtrate,UICOL_TEXT_NORMAL);

                  texts[1].Create (&menu_wnd,&download_text,MSN_COL_1,MSN_ROW_1,0);
                  texts[2].Create (&menu_wnd,&rcvd_text,MSN_COL_1,MSN_ROW_2,0);
                  texts[3].Create (&menu_wnd,&total_text,MSN_COL_2,MSN_ROW_2,0);
                  texts[4].Create (&menu_wnd,&elaps_text,MSN_COL_1,MSN_ROW_3,0);
                  texts[5].Create (&menu_wnd,&time_r_text,MSN_COL_2,MSN_ROW_3,0);
                  texts[6].Create (&menu_wnd,&rate_text,MSN_COL_1,MSN_ROW_4,0);

                  progress.Update(((float)((float)received_bytes)/((float)total_bytes)));
                  //mprintf(0,"@");
          }
          //mprintf(0,"-In");
          res = PollUI();
          //mprintf(0,"-Out");
          switch(res)
          {
          case UID_CANCEL:
                  getmsnfile->AbortGet();
                  ddio_DeleteFile(qualfile);
                  exit_menu = 1;
                  ret = 0;
                  break;
          }
  }
  menu_wnd.Close();
  menu_wnd.Destroy();
  delete getmsnfile;
  return ret;
  */
}

void msn_DoAskForURL(uint8_t *indata, network_address *net_addr) {
  static msn_urls *url;
  int count = 0;
  int size;
  int i;
  uint8_t data[MAX_GAME_DATA_SIZE];
  int num_urls = 0;

  if (Netgame.local_role == LR_SERVER) {
    size = START_DATA(MP_CUR_MSN_URLS, data, &count);

    url = msn_GetURL(Netgame.mission);
    if (url) {
      for (i = 0; i < MAX_MISSION_URL_COUNT; i++) {
        if (url->URL[0]) {
          num_urls++;
        }
      }
    }
    // length of the msn
    int msnlen = strlen(Netgame.mission) + 1;
    MultiAddByte(msnlen, data, &count);
    // Copy the mission name
    memcpy(data + count, url->URL[i], msnlen);
    count += msnlen;

    // Silly copy  protection. Don't download the mn3 if
    //"clang.wav" is in it.
    if (cf_IsFileInHog(Netgame.mission, "clang.wav")) {
      num_urls = 0;
      return;
    }

    // Number of URLs
    MultiAddByte(num_urls, data, &count);
    for (i = 0; i < num_urls; i++) {
      uint16_t urllen = strlen(url->URL[i]) + 1;
      if ((count + urllen) >= MAX_GAME_DATA_SIZE) {
        // if for some reason the URLS exceed what a packet can send
        // rather than overflow the memory buffer, just don't send out the packet.
        // I would just fit any URLS that I can but this is safer to put in a patch.
        return;
      }

      // Write the lenght of the url
      MultiAddUshort(urllen, data, &count);
      // Now write the url
      memcpy(data + count, url->URL[i], urllen);
      count += urllen;
    }
    END_DATA(count, data, size);
    nw_Send(net_addr, data, count, 0);
  }
}

void msn_DoCurrMsnURLs(uint8_t *data, network_address *net_addr) {
  int count = 0;
  int num_urls = 0;
  int i;

  memset(&msn_URL, 0, sizeof(msn_URL));

  SKIP_HEADER(data, &count);
  // Get the mission name
  int msnlen = MultiGetByte(data, &count);
  memcpy(&msn_URL.msnname, data + count, msnlen);
  count += msnlen;
  num_urls = MultiGetByte(data, &count);

  for (i = 0; i < num_urls; i++) {
    uint16_t urllen = MultiGetUshort(data, &count);
    memcpy(msn_URL.URL[i], data + count, urllen);
    count += urllen;
  }
  Got_url = 1;
}

// Check if a file exists.
// If it does, return true
// If it doesn't attempt to download it. On success return true
// Otherwise return false
int msn_CheckGetMission(network_address *net_addr, char *filename) {
#ifdef OEM
  return 1;
#else
  if ((stricmp(filename, "d3_2.mn3") == 0) || (stricmp(filename, "d3.mn3") == 0)) {
    const char *p = GetMultiCDPath(filename);
    return p ? 1 : 0;
  }

  char pathname[_MAX_PATH];
  ddio_MakePath(pathname, D3MissionsDir, filename, NULL);
  if (cfexist(filename) || cfexist(pathname)) {
    return 1;
  }

  msn_urls *murls;

  murls = msn_GetURL(net_addr);
  if (murls) {
    int sel = msn_ShowDownloadChoices(murls);
    if (sel != -1) {
      // Get the item that was selected!
      mprintf(0, "Downloading missions file from %s\n", murls->URL[sel]);
      if (msn_DownloadWithStatus(murls->URL[sel], filename)) {
        return 1;
      }
    }
  } else {
    DoMessageBox(TXT_ERROR, TXT_FMTCANTDNLD, MSGBOX_OK);
  }
  return 0;
#endif
}

void msn_ClipURLToWidth(int width, char *string) {
  if (!string)
    return;

  int string_length = strlen(string);

  int size = 0;
  char save = string[0];
  string[0] = '\0';
  while (size < string_length) {
    if ((grtext_GetTextLineWidth(string)) >= width) {
      return;
    }
    // replace the char and move to the next
    string[size] = save;
    size++;
    save = string[size];
    string[size] = '\0';
  }
}

char *msn_SecondsToString(int time_sec) {
  static char fmttime[100];
  char fmttemp[100] = "";
  int hours;
  int minutes;
  int seconds;
  int i;
  fmttime[0] = '\0';
  hours = time_sec / 3600;
  i = time_sec % 3600;
  minutes = i / 60;
  seconds = time_sec % 60;
  if (hours) {
    snprintf(fmttemp, sizeof(fmttemp), TXT_FMTTIMEHOUR, hours);
    strcat(fmttime, " ");
    strcat(fmttime, fmttemp);
  }
  if (minutes) {
    snprintf(fmttemp, sizeof(fmttemp), TXT_FMTTIMEMIN, minutes);
    strcat(fmttime, " ");
    strcat(fmttime, fmttemp);
  }
  if (seconds) {
    snprintf(fmttemp, sizeof(fmttemp), TXT_FMTTIMESEC, seconds);
    strcat(fmttime, fmttemp);
  }
  return fmttime;
}

void _get_zipfilename(char *output, char *directory, char *zipfilename) {
  char *s = strrchr(zipfilename, '/');
  if (s)
    s++;
  else
    s = zipfilename;

  ddio_MakePath(output, directory, s, NULL);
}

// return 0 on failure
// return 1 on success
int msn_ExtractZipFile(char *zipfilename, char *mn3name) {

  mprintf(0, "Extracting ZIP File (%s) to missions directory\n", zipfilename);
  if (!cfexist(zipfilename)) {
    mprintf(0, "Zip file doesn't exist\n");
    return 0;
  }

  char mission_directory[_MAX_PATH];
  char output_filename[_MAX_PATH];
  char buffer[256 + 32];

  ddio_MakePath(mission_directory, LocalD3Dir, "missions", NULL);

  // now go through the zip file and extract all the files out that we can
  ZIP zfile;
  zipentry *ze;

  if (!zfile.OpenZip(zipfilename)) {
    mprintf(0, "Unable to open zip file\n");
    return 0;
  }

  NewUIGameWindow window;
  UIConsoleGadget console;

  // Create all the UI Items
  window.Create(0, 0, 384, 288);
  console.Create(&window, 0x99, 25, 25, 0, 35, 18, 0);
  window.Open();

  bool found_mn3 = false;
  bool process_file;

  while ((ze = zfile.ReadNextZipEntry()) != NULL) {
    if (ze->crc32 == 0)
      continue; // skip directories

    App()->defer();
    process_file = true;

    mprintf(0, "Processesing: %s\n", ze->name);

    if (ze->compression_method == 0x0000 || ze->compression_method == 0x0008) {
      char *rfile = strrchr(ze->name, '/');
      if (rfile)
        rfile++;
      else
        rfile = ze->name;

      snprintf(buffer, sizeof(buffer), "%s %s...", (ze->compression_method == 0x0000) ? "Extracting" : "Inflating",
               rfile);
      console.puts(GR_GREEN, buffer);

      // create the filename for this file
      _get_zipfilename(output_filename, mission_directory, ze->name);

      if (cfexist(output_filename)) {
        snprintf(buffer, sizeof(buffer), "%s already exists. Overwrite?", output_filename);
        if (DoMessageBox("Confirm", buffer, MSGBOX_YESNO, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL)) {
          // delete the file
          mprintf(0, "Deleting %s\n", zipfilename);
          if (!ddio_DeleteFile(output_filename)) {
            process_file = false;
            console.puts(GR_GREEN, "[Unable to Write] ");
          } else {
            console.puts(GR_GREEN, "[Overwriting] ");
          }
        } else {
          process_file = false;
          console.puts(GR_GREEN, "[Skipped] ");
        }
      }

      // extract this file
      if (process_file) {
        // update the screen
        DoUIFrame();
        rend_Flip();

        int ret = zfile.ExtractFile(ze, output_filename);
        if (ret < 0) {
          if (ret == -9) {
            mprintf(0, " Error writing to file\n");
            snprintf(buffer, sizeof(buffer), "\nError writing to file (Out of space?)");
          } else {
            mprintf(0, " Error %d extracting file\n", ret);
            snprintf(buffer, sizeof(buffer), "\nError %d extracting file", ret);
          }
          console.puts(GR_GREEN, buffer);
          if (cfexist(output_filename)) {
            ddio_DeleteFile(output_filename);
          }
        } else {
          // check the CRC
          uint32_t crc = cf_GetfileCRC(output_filename);
          if (crc == ze->crc32) {
            console.puts(GR_GREEN, "CRC OK");

            // check to see if we extracted our mn3
            if (CompareZipFileName(ze->name, mn3name)) {
              found_mn3 = true;
            }
          } else {
            console.puts(GR_GREEN, "CRC FAIL!");
            ddio_DeleteFile(output_filename);
          }
        }
      }

    } else {
      mprintf(0, "Unsupported compression for file (%s)\n", ze->name);
      console.puts(GR_GREEN, "Unsupported compression!!");
    }

    console.puts(GR_GREEN, "\n");
    DoUIFrame();
    rend_Flip();
  }
  zfile.CloseZip();

  if (DoMessageBox("Confirm", "Do you want to delete the zip file? It is no longer needed.", MSGBOX_YESNO,
                   UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL)) {
    // delete the file
    mprintf(0, "Deleting %s\n", zipfilename);
    ddio_DeleteFile(zipfilename);
  }

  window.Close();
  window.Destroy();

  if (!found_mn3)
    return 0;

  return 1;
}

#ifdef __LINUX__
char *_strlwr(char *string) {
  char *ptr = string;
  while (*ptr) {
    *ptr = tolower(*ptr);
    ptr++;
  }
  return string;
}
#endif

#define MOD_URL_BASEPATH "http://www.descent3.com/mods/" // WAS: "http://www.pxo.net/descent3/mods/"

int CheckGetD3M(char *d3m) {
#if !defined(OEM)

  char modurl[MAX_MISSION_URL_LEN + 1];
  char *lowurl;
  char pathname[_MAX_PATH];
  char *fixedd3m = NULL;

  ddio_MakePath(pathname, LocalD3Dir, "Netgames", d3m, NULL);
  if (cfexist(d3m) || cfexist(pathname)) {
    return 1;
  }

  // Now we need to replace evil spaces with underscores, so the downloader will work
  fixedd3m = mem_strdup(d3m);
  char *p = fixedd3m;
  while (*p) {
    if (*p == ' ') {
      *p = '_';
    }
    p++;
  }
  // This should be the url we can download from.
  int iurlbase = FindArg("-d3mbaseurl");
  if (!iurlbase) {
    strcpy(modurl, MOD_URL_BASEPATH);
  } else {
    strcpy(modurl, GameArgs[iurlbase + 1]);
  }

  strcat(modurl, fixedd3m);

  lowurl = mem_strdup(_strlwr(modurl));
  mprintf(0, "Downloading mod file from %s\n", modurl);

  if (ModDownloadWithStatus(modurl, d3m)) {
    mem_free(fixedd3m);
    return 1;
  }

  mem_free(lowurl);
  mem_free(fixedd3m);
  return 0;
#endif
}

// Start downloading the file at the url specifies, showing a status screen
// Return codes:
// 0 Failed or cancelled
// 1 Success
int ModDownloadWithStatus(char *url, char *filename) {
  return 0;
  /*
  char qualfile[_MAX_PATH*2];
  float last_refresh;
  int total_bytes = 0;
  int received_bytes = 0;
  int time_elapsed = 0;
  int time_remain = 0;
  int xfer_rate = 0;
  int starttime = timer_GetTime();
  bool file_is_zip = false;

  //check to see if we are downloading a zip file
  char *url_ptr;
  url_ptr = url + strlen(url);
  while(url_ptr > url && *url_ptr!='.') url_ptr--;
  if(*url_ptr=='.')
  {
          //now see if the rest of the extension is ZIP
          if(!stricmp(url_ptr,".ZIP"))
          {
                  mprintf(0,"We're downloading a zip file!!!\n");
                  file_is_zip = true;
          }
  }

  char fmturl[MSN_MAX_STRING_LEN];
  char fmtrcvd[MSN_MAX_STRING_LEN];
  char fmttotal[MSN_MAX_STRING_LEN];
  char fmtelaps[MSN_MAX_STRING_LEN];
  char fmttimer[MSN_MAX_STRING_LEN];
  char fmtrate[MSN_MAX_STRING_LEN];

  sprintf(fmturl,DOWNLOAD_STATUS_URL_TEXT,url);
  msn_ClipURLToWidth(MSN_DWNLD_STATUS_W-(MSN_COL_1+MSN_BORDER_W),fmturl);
  sprintf(fmtrcvd,DOWNLOAD_STATUS_RCVD_TEXT,received_bytes);
  sprintf(fmttotal,DOWNLOAD_STATUS_TOTAL_TEXT,total_bytes);
  sprintf(fmtelaps,DOWNLOAD_STATUS_ELAPS_TEXT,msn_SecondsToString(time_elapsed));
  sprintf(fmttimer,DOWNLOAD_STATUS_TIME_R_TEXT,msn_SecondsToString(time_remain));
  sprintf(fmtrate,DOWNLOAD_STATUS_XFERRATE_TEXT,xfer_rate);

  if(file_is_zip)
  {
          char fname[_MAX_FNAME];
          char *s_ptr,*d_ptr;
          s_ptr = filename;
          d_ptr = fname;
          while(*s_ptr && *s_ptr!='.'){ *d_ptr = *s_ptr; s_ptr++; d_ptr++;}
          *d_ptr = '\0';
          strcat(fname,".zip");
          ddio_MakePath(qualfile, LocalD3Dir, "Netgames", fname, NULL);
          //ddio_MakePath(qualfile,D3MissionsDir,fname,NULL);
  }else
  {
          //ddio_MakePath(qualfile,D3MissionsDir,filename,NULL);
          ddio_MakePath(qualfile, LocalD3Dir, "Netgames", filename, NULL);
  }
  InetGetFile *getmsnfile;
  if(Proxy_server[0])
  {
          getmsnfile = new InetGetFile(url,qualfile,Proxy_server,Proxy_port);
  }
  else
  {
          getmsnfile = new InetGetFile(url,qualfile);
  }
  //InetGetFile getmsnfile(url,qualfile);

  UITextItem title_text(TXT_MD_DOWNLOADSTATUS,UICOL_TEXT_NORMAL);

  UIHotspot cancel_hot;

  UITextItem download_text(fmturl,UICOL_TEXT_NORMAL);;
  UITextItem rcvd_text(fmtrcvd,UICOL_TEXT_NORMAL);
  UITextItem total_text(fmttotal,UICOL_TEXT_NORMAL);
  UITextItem elaps_text(fmtelaps,UICOL_TEXT_NORMAL);
  UITextItem time_r_text(fmttimer,UICOL_TEXT_NORMAL);
  UITextItem rate_text(fmtrate,UICOL_TEXT_NORMAL);

  NewUIGameWindow menu_wnd;

  UIText texts[10];
  UIProgress progress;

  int exit_menu=0;
  int ret=0;

  menu_wnd.Create(10,10,MSN_DWNLD_STATUS_W,MSN_DWNLD_STATUS_H,UIF_PROCESS_ALL | UIF_CENTER);
  texts[0].Create (&menu_wnd,&title_text,0,8,UIF_CENTER);
  texts[1].Create (&menu_wnd,&download_text,MSN_COL_1,MSN_ROW_1,0);
  texts[2].Create (&menu_wnd,&rcvd_text,MSN_COL_1,MSN_ROW_2,0);
  texts[3].Create (&menu_wnd,&total_text,MSN_COL_2,MSN_ROW_2,0);
  texts[4].Create (&menu_wnd,&elaps_text,MSN_COL_1,MSN_ROW_3,0);
  texts[5].Create (&menu_wnd,&time_r_text,MSN_COL_2,MSN_ROW_3,0);
  texts[6].Create (&menu_wnd,&rate_text,MSN_COL_1,MSN_ROW_4,0);

  UITextItem cancel_off(TXT_CANCEL,UICOL_HOTSPOT_LO,UIALPHA_HOTSPOT_LO);
  UITextItem cancel_on(TXT_CANCEL,UICOL_HOTSPOT_HI,UIALPHA_HOTSPOT_HI);

  progress.Create(&menu_wnd,MSN_COL_1,MSN_ROW_5,MSN_DWNLD_STATUS_W-(MSN_BORDER_W*2),35,0);

  int cancel_x = 0;

  cancel_hot.Create(&menu_wnd, UID_CANCEL, KEY_ESC, &cancel_off,&cancel_on,
                                                                  cancel_x, MSN_DWNLD_STATUS_H - OKCANCEL_YOFFSET,
  0,0,UIF_FIT|UIF_CENTER); menu_wnd.Open();

  last_refresh = timer_GetTime()-MSN_REFRESH_INTERVAL;

  while (!exit_menu)
  {
          int res;

          if((timer_GetTime()-last_refresh)>MSN_REFRESH_INTERVAL)
          {

                  //Update the dialog
                  //mprintf(0,"!");

                  if(getmsnfile->IsFileReceived())
                  {
                          //File transfer successful!
                          mprintf(0,"Succesfully received the file!\n");
                          exit_menu = 1;

                          if(file_is_zip)
                          {
                                  // now we gotta handle the zip file
                                  ret = msn_ExtractZipFile(qualfile,filename);
                          }else
                          {
                                  ret = 1;
                          }
                  }

                  if(getmsnfile->IsFileError())
                  {
                          //File transfer Error!
                          DoMessageBox(TXT_ERROR,TXT_FMTCANTDNLD,MSGBOX_OK);
                          //Delete the file that didn't finish!
                          ddio_DeleteFile(qualfile);
                          mprintf(0,"Couldn't download the file! Error: %d\n",getmsnfile->GetErrorCode());
                          exit_menu = 1;
                          ret = 0;
                  }

                  last_refresh = timer_GetTime();
                  received_bytes = getmsnfile->GetBytesIn();
                  total_bytes = getmsnfile->GetTotalBytes();

                  time_elapsed = timer_GetTime()-starttime;

                  if(total_bytes)
                  {
                          time_remain = ((float)(total_bytes-received_bytes))/((float)(received_bytes/time_elapsed));
                  }
                  if(time_elapsed&&received_bytes)
                  {
                          xfer_rate = ((float)(received_bytes/time_elapsed));
                  }
                  texts[1].Destroy();
                  texts[2].Destroy();
                  texts[3].Destroy();
                  texts[4].Destroy();
                  texts[5].Destroy();
                  texts[6].Destroy();

                  sprintf(fmturl,DOWNLOAD_STATUS_URL_TEXT,url);
                  msn_ClipURLToWidth(MSN_DWNLD_STATUS_W-(MSN_COL_1+MSN_BORDER_W),fmturl);
                  sprintf(fmtrcvd,DOWNLOAD_STATUS_RCVD_TEXT,received_bytes);
                  sprintf(fmttotal,DOWNLOAD_STATUS_TOTAL_TEXT,total_bytes);
                  sprintf(fmtelaps,DOWNLOAD_STATUS_ELAPS_TEXT,msn_SecondsToString(time_elapsed));
                  sprintf(fmttimer,DOWNLOAD_STATUS_TIME_R_TEXT,msn_SecondsToString(time_remain));
                  msn_ClipURLToWidth(MSN_DWNLD_STATUS_W-(MSN_COL_2+MSN_BORDER_W),fmttimer);
                  sprintf(fmtrate,DOWNLOAD_STATUS_XFERRATE_TEXT,xfer_rate);

                  download_text = UITextItem (fmturl,UICOL_TEXT_NORMAL);;
                  rcvd_text = UITextItem (fmtrcvd,UICOL_TEXT_NORMAL);
                  total_text = UITextItem (fmttotal,UICOL_TEXT_NORMAL);
                  elaps_text = UITextItem (fmtelaps,UICOL_TEXT_NORMAL);
                  time_r_text = UITextItem (fmttimer,UICOL_TEXT_NORMAL);
                  rate_text = UITextItem (fmtrate,UICOL_TEXT_NORMAL);

                  texts[1].Create (&menu_wnd,&download_text,MSN_COL_1,MSN_ROW_1,0);
                  texts[2].Create (&menu_wnd,&rcvd_text,MSN_COL_1,MSN_ROW_2,0);
                  texts[3].Create (&menu_wnd,&total_text,MSN_COL_2,MSN_ROW_2,0);
                  texts[4].Create (&menu_wnd,&elaps_text,MSN_COL_1,MSN_ROW_3,0);
                  texts[5].Create (&menu_wnd,&time_r_text,MSN_COL_2,MSN_ROW_3,0);
                  texts[6].Create (&menu_wnd,&rate_text,MSN_COL_1,MSN_ROW_4,0);

                  progress.Update(((float)((float)received_bytes)/((float)total_bytes)));
                  //mprintf(0,"@");
          }
          //mprintf(0,"-In");
          res = PollUI();
          //mprintf(0,"-Out");
          switch(res)
          {
          case UID_CANCEL:
                  getmsnfile->AbortGet();
                  ddio_DeleteFile(qualfile);
                  exit_menu = 1;
                  ret = 0;
                  break;
          }
  }
  menu_wnd.Close();
  menu_wnd.Destroy();
  delete getmsnfile;
  return ret;
  */
}
