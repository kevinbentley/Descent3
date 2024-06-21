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

 * $Logfile: /DescentIII/Main/inetfile/inetgetfile.cpp $
 * $Revision: 1.2 $
 * $Date: 2000/06/03 14:33:51 $
 * $Author: icculus $
 *
 * InternetGetFile Class
 *
 * $Log: inetgetfile.cpp,v $
 * Revision 1.2  2000/06/03 14:33:51  icculus
 * Merge with Outrage 1.4 tree...
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 10    10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 9     9/08/99 6:37p Jeff
 * fixed http/ftp downloading for Linux, should all work fine now.
 *
 * 8     8/23/99 5:12p Kevin
 * Proxy support for http
 *
 * 7     8/21/99 6:48a Jeff
 * Linux port
 *
 * 6     4/14/99 1:20a Jeff
 * fixed case mismatched #includes
 *
 * 5     7/31/98 11:57a Kevin
 * Added new functions for getting state
 *
 * 4     7/31/98 11:40a Kevin
 *
 * 3     7/31/98 11:17a Nate
 * Fixed memory leak and added memory alloc checking.
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/27/98 9:52a Kevin
 *
 * 1     5/25/98 5:31p Kevin
 * Initial version
 *
 * $NoKeywords: $
 */

#if defined(WIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// include inetgetfile.h before CFtp.h and Chttpget.h because it has some winsock defines
// to make Linux happy
#include "inetgetfile.h"
#include "CFtp.h"
#include "Chttpget.h"

extern char *Proxy_server;
extern int16_t Proxy_port;

#if defined(__LINUX__) || defined(ANDROID)
/*  ryan sez: use SDL.
pthread_create_fp df_pthread_create = NULL;
pthread_exit_fp df_pthread_exit = NULL;
pthread_detach_fp df_pthread_detach = NULL;
pthread_self_fp df_pthread_self = NULL;
*/
bool inet_LoadThreadLib(void) {
  return true;
  /*
          if(df_pthread_create)
                  return true;

          void *lib;

          lib = dlopen("libpthread.so",RTLD_GLOBAL|RTLD_NOW);
          if(!lib)
          {
                  return false;
          }

          df_pthread_create = (pthread_create_fp)dlsym(lib,"pthread_create");
          df_pthread_detach = (pthread_detach_fp)dlsym(lib,"pthread_detach");
          df_pthread_self = (pthread_self_fp)dlsym(lib,"pthread_self");

          if(!df_pthread_create || !df_pthread_detach || !df_pthread_self)
          {
                  df_pthread_create = NULL;	//this variable I use to see if the library is loaded
                  return false;
          }

          // don't close the library...we need it open for future use
          // and we can't close it on atexit() because linux will segfault for some stupid reason
          return true;
  */
}
#endif

void InetGetFile::AbortGet() {
  if (m_bUseHTTP) {
    http->AbortGet();
  } else {
    ftp->AbortGet();
  }
}

InetGetFile::InetGetFile(char *URL, char *localfile, char *proxyip, int16_t proxyport) {
  m_HardError = 0;
  http = NULL;
  ftp = NULL;
  if ((URL == NULL) || (localfile == NULL)) {
    m_HardError = INET_ERROR_BADPARMS;
  }
  if (strstr(URL, "http:")) {
    m_bUseHTTP = true;
    http = new ChttpGet(URL, localfile, proxyip, proxyport);
    if (http == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else if (strstr(URL, "HTTP:")) {
    m_bUseHTTP = true;
    http = new ChttpGet(URL, localfile, proxyip, proxyport);
    if (http == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else if (strstr(URL, "FTP:")) {
    m_bUseHTTP = false;
    ftp = new CFtpGet(URL, localfile);
    if (ftp == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else if (strstr(URL, "ftp:")) {
    m_bUseHTTP = false;
    ftp = new CFtpGet(URL, localfile);
    if (ftp == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else {
    m_HardError = INET_ERROR_CANT_PARSE_URL;
  }
  Sleep(1000);
}

InetGetFile::InetGetFile(char *URL, char *localfile) {
  m_HardError = 0;
  http = NULL;
  ftp = NULL;
  if ((URL == NULL) || (localfile == NULL)) {
    m_HardError = INET_ERROR_BADPARMS;
  }
  if (strstr(URL, "http:")) {
    m_bUseHTTP = true;
    http = new ChttpGet(URL, localfile);
    if (http == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else if (strstr(URL, "HTTP:")) {
    m_bUseHTTP = true;
    http = new ChttpGet(URL, localfile);
    if (http == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else if (strstr(URL, "FTP:")) {
    m_bUseHTTP = false;
    ftp = new CFtpGet(URL, localfile);
    if (ftp == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else if (strstr(URL, "ftp:")) {
    m_bUseHTTP = false;
    ftp = new CFtpGet(URL, localfile);
    if (ftp == NULL)
      m_HardError = INET_ERROR_NO_MEMORY;
  } else {
    m_HardError = INET_ERROR_CANT_PARSE_URL;
  }
  Sleep(1000);
}

InetGetFile::~InetGetFile() {
  if (http != NULL)
    delete http;
  if (ftp != NULL)
    delete ftp;
}

BOOL InetGetFile::IsConnecting() {
  int state;
  if (m_bUseHTTP) {
    state = http->GetStatus();
  } else if (ftp) {
    state = ftp->GetStatus();
  } else {
    return false;
  }
  if (state == FTP_STATE_CONNECTING) {
    return true;
  } else {
    return false;
  }
}

BOOL InetGetFile::IsReceiving() {
  int state = 0;
  if (m_bUseHTTP) {
    state = http->GetStatus();
  } else if (ftp) {
    state = ftp->GetStatus();
  }
  if (state == FTP_STATE_RECEIVING) {
    return true;
  } else {
    return false;
  }
}

BOOL InetGetFile::IsFileReceived() {
  int state = 0;
  if (m_bUseHTTP) {
    state = http->GetStatus();
  } else if (ftp) {
    state = ftp->GetStatus();
  }
  if (state == FTP_STATE_FILE_RECEIVED) {
    return true;
  } else {
    return false;
  }
}

BOOL InetGetFile::IsFileError() {
  int state;
  if (m_HardError)
    return true;
  if (m_bUseHTTP) {
    state = http->GetStatus();
  } else if (ftp) {
    state = ftp->GetStatus();
  }
  switch (state) {

  case FTP_STATE_URL_PARSING_ERROR:
  case FTP_STATE_HOST_NOT_FOUND:
  case FTP_STATE_DIRECTORY_INVALID:
  case FTP_STATE_FILE_NOT_FOUND:
  case FTP_STATE_CANT_CONNECT:
  case FTP_STATE_LOGIN_ERROR:
  case FTP_STATE_INTERNAL_ERROR:
  case FTP_STATE_SOCKET_ERROR:
  case FTP_STATE_UNKNOWN_ERROR:
  case FTP_STATE_RECV_FAILED:
  case FTP_STATE_CANT_WRITE_FILE:
    return true;
  case FTP_STATE_CONNECTING:
    return false;
  default:
    return false;
  }
}

int InetGetFile::GetErrorCode() {
  int state;
  if (m_HardError)
    return m_HardError;
  if (m_bUseHTTP) {
    state = http->GetStatus();
  } else if (ftp) {
    state = ftp->GetStatus();
  }
  switch (state) {

  case FTP_STATE_URL_PARSING_ERROR:
    return INET_ERROR_CANT_PARSE_URL;

  case FTP_STATE_HOST_NOT_FOUND:
    return INET_ERROR_HOST_NOT_FOUND;

  case FTP_STATE_DIRECTORY_INVALID:
  case FTP_STATE_FILE_NOT_FOUND:
    return INET_ERROR_BAD_FILE_OR_DIR;

  case FTP_STATE_CANT_CONNECT:
  case FTP_STATE_LOGIN_ERROR:
  case FTP_STATE_INTERNAL_ERROR:
  case FTP_STATE_SOCKET_ERROR:
  case FTP_STATE_UNKNOWN_ERROR:
  case FTP_STATE_RECV_FAILED:

    return INET_ERROR_UNKNOWN_ERROR;

  case FTP_STATE_CANT_WRITE_FILE:
    return INET_ERROR_CANT_WRITE_FILE;
  default:
    return INET_ERROR_NO_ERROR;
  }
}

int InetGetFile::GetTotalBytes() {
  if (m_bUseHTTP) {
    return http->GetTotalBytes();
  } else if (ftp) {
    return ftp->GetTotalBytes();
  } else
    return 0;
}

int InetGetFile::GetBytesIn() {
  if (m_bUseHTTP) {
    return http->GetBytesIn();
  } else if (ftp) {
    return ftp->GetBytesIn();
  } else
    return 0;
}
