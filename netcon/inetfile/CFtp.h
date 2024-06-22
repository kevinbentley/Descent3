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

 * $Logfile: /DescentIII/Main/lib/CFtp.h $
 * $Revision: 1.3 $
 * $Date: 2004/02/09 04:14:51 $
 * $Author: kevinb $
 *
 * FTP Client class (get only)
 *
 * $Log: CFtp.h,v $
 * Revision 1.3  2004/02/09 04:14:51  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.2  2000/06/03 14:30:33  icculus
 * 1.4 code merge and pthread->SDL thread conversion.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 4     8/21/99 6:48a Jeff
 * Linux port
 *
 * 3     7/31/98 11:40a Kevin
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
#ifndef _CFTP_HEADER_
#define _CFTP_HEADER_

#include <cstdint>

#define FTP_STATE_INTERNAL_ERROR 0
#define FTP_STATE_SOCKET_ERROR 1
#define FTP_STATE_URL_PARSING_ERROR 2
#define FTP_STATE_CONNECTING 3
#define FTP_STATE_HOST_NOT_FOUND 4
#define FTP_STATE_CANT_CONNECT 5
#define FTP_STATE_LOGGING_IN 6
#define FTP_STATE_LOGIN_ERROR 7
#define FTP_STATE_LOGGED_IN 8
#define FTP_STATE_DIRECTORY_INVALID 9
#define FTP_STATE_FILE_NOT_FOUND 10
#define FTP_STATE_RECEIVING 11
#define FTP_STATE_FILE_RECEIVED 12
#define FTP_STATE_UNKNOWN_ERROR 13
#define FTP_STATE_RECV_FAILED 14
#define FTP_STATE_CANT_WRITE_FILE 15
#define FTP_STATE_STARTUP 16

#if WIN32
typedef UINT_PTR SOCKET;
#endif

#ifdef __LINUX__
extern int FTPObjThread(void *obj);
#else
extern void FTPObjThread(void *obj);
#endif

class CFtpGet {

public:
  CFtpGet(char *URL, char *localfile, char *Username = NULL, char *Password = NULL);
  ~CFtpGet();
  int GetStatus();
  uint32_t GetBytesIn();
  uint32_t GetTotalBytes();
  void AbortGet();

  void WorkerThread();

protected:
  int ConnectControlSocket();
  int LoginHost();
  uint32_t SendFTPCommand(char *command);
  uint32_t ReadFTPServerReply();
  uint32_t GetFile();
  uint32_t IssuePort();
  uint32_t ReadDataChannel();
  void FlushControlChannel();

  uint32_t m_iBytesIn;
  uint32_t m_iBytesTotal;
  uint32_t m_State;

  bool m_Aborting;
  bool m_Aborted;

  char m_szUserName[100];
  char m_szPassword[100];
  char m_szHost[200];
  char m_szDir[200];
  char m_szFilename[100];

  char recv_buffer[1000];

  SOCKET m_ListenSock;
  SOCKET m_DataSock;
  SOCKET m_ControlSock;

  FILE *LOCALFILE;
};

#endif
