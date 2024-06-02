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

 * $Logfile: /DescentIII/Main/lib/Chttpget.h $
 * $Revision: 1.2 $
 * $Date: 2004/02/09 04:14:51 $
 * $Author: kevinb $
 *
 * HTTP Client class (get only)
 *
 * $Log: Chttpget.h,v $
 * Revision 1.2  2004/02/09 04:14:51  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 7     8/21/99 9:14p Kevin
 * Added support for redirection
 *
 * 6     8/21/99 6:48a Jeff
 * Linux port
 *
 * 5     8/20/99 3:01p Kevin
 * Added support for Proxies (I hope!)
 *
 * 4     7/31/98 12:19p Nate
 * Fixed http abort problem.
 *
 * 3     7/31/98 11:57a Kevin
 * Added new functions for getting state
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/27/98 9:54a Kevin
 *
 * 1     5/25/98 5:31p Kevin
 * Initial version
 *
 * $NoKeywords: $
 */
#ifndef _CHTTPGET_HEADER_
#define _CHTTPGET_HEADER_

#include <cstdint>
#include "networking.h"

#define HTTP_STATE_INTERNAL_ERROR 0
#define HTTP_STATE_SOCKET_ERROR 1
#define HTTP_STATE_URL_PARSING_ERROR 2
#define HTTP_STATE_CONNECTING 3
#define HTTP_STATE_HOST_NOT_FOUND 4
#define HTTP_STATE_CANT_CONNECT 5
#define HTTP_STATE_CONNECTED 6
#define HTTP_STATE_FILE_NOT_FOUND 10
#define HTTP_STATE_RECEIVING 11
#define HTTP_STATE_FILE_RECEIVED 12
#define HTTP_STATE_UNKNOWN_ERROR 13
#define HTTP_STATE_RECV_FAILED 14
#define HTTP_STATE_CANT_WRITE_FILE 15
#define HTTP_STATE_STARTUP 16

#define MAX_URL_LEN 300

class ChttpGet {
public:
  ChttpGet(char *URL, char *localfile);
  ChttpGet(char *URL, char *localfile, char *proxyip, uint16_t proxyport);
  void PrepSocket(char *URL);
  ~ChttpGet();
  void GetFile(char *URL, char *localfile);
  int GetStatus();
  uint32_t GetBytesIn();
  uint32_t GetTotalBytes();
  void AbortGet();
  void WorkerThread();
  bool m_Aborted;

protected:
  int ConnectSocket();
  char *GetHTTPLine();
  uint32_t ReadDataChannel();
  uint32_t m_iBytesIn;
  uint32_t m_iBytesTotal;
  uint32_t m_State;
  bool m_ProxyEnabled;
  char *m_ProxyIP;
  char m_URL[MAX_URL_LEN];
  uint16_t m_ProxyPort;

  char m_szUserName[100];
  char m_szPassword[100];
  char m_szHost[200];
  char m_szDir[200];
  char m_szFilename[100];

  bool m_Aborting;

  SOCKET m_DataSock;

  FILE *LOCALFILE;
  char recv_buffer[1000];
};

#endif
