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

* $Logfile: /DescentIII/Main/inetfile/CFtp.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:58:00 $
* $Author: kevinb $
*
* FTP Client class (get only)
*
* $Log: not supported by cvs2svn $
 *
 * 8     10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 7     9/08/99 6:37p Jeff
 * fixed http/ftp downloading for Linux, should all work fine now.
 *
 * 6     8/22/99 12:32a Jeff
 * fixed select calls for Linux.  Ported Kevin's new http stuff to Linux
 *
 * 5     8/21/99 6:48a Jeff
 * Linux port
 *
 * 4     4/14/99 1:20a Jeff
 * fixed case mismatched #includes
 *
 * 3     7/31/98 11:40a Kevin
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

#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__LINUX__) || defined(ANDROID)
// sorry, I'm lazy, I guess we could copy the defines
// that we need to transalte winsock->linux into this header...but no need to now
#include "inetgetfile.h"
#endif

#ifdef MACINTOSH
#include "macsock.h"
#endif

#include "CFtp.h"

#if defined(__LINUX__) || defined(ANDROID)
void *FTPObjThread(void *obj)
#else
void FTPObjThread(void *obj)
#endif
{
  ((CFtpGet *)obj)->WorkerThread();
#if defined(__LINUX__) || defined(ANDROID)
  return NULL;
#endif
}

void CFtpGet::AbortGet() {
  m_Aborting = true;
  while (!m_Aborted)
    ; // Wait for the thread to end
  fclose(LOCALFILE);
}

CFtpGet::CFtpGet(char *URL, char *localfile, char *Username, char *Password) {
  SOCKADDR_IN listensockaddr;
  m_State = FTP_STATE_STARTUP;

  m_ListenSock = INVALID_SOCKET;
  m_DataSock = INVALID_SOCKET;
  m_ControlSock = INVALID_SOCKET;
  m_iBytesIn = 0;
  m_iBytesTotal = 0;
  m_Aborting = false;
  m_Aborted = false;

  LOCALFILE = fopen(localfile, "wb");
  if (NULL == LOCALFILE) {
    m_State = FTP_STATE_CANT_WRITE_FILE;
    return;
  }

  if (Username) {
    strcpy(m_szUserName, Username);
  } else {
    strcpy(m_szUserName, "anonymous");
  }
  if (Password) {
    strcpy(m_szPassword, Password);
  } else {
    strcpy(m_szPassword, "pxouser@pxo.net");
  }
  m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
  if (INVALID_SOCKET == m_ListenSock) {
    int iWinsockErr = WSAGetLastError();
    m_State = FTP_STATE_SOCKET_ERROR;
    return;
  } else {
    listensockaddr.sin_family = AF_INET;
    listensockaddr.sin_port = 0;
    listensockaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the listen socket
    if (bind(m_ListenSock, (SOCKADDR *)&listensockaddr, sizeof(SOCKADDR))) {
      // Couldn't bind the socket
      int iWinsockErr = WSAGetLastError();
      m_State = FTP_STATE_SOCKET_ERROR;
      return;
    }

    // Listen for the server connection
    if (listen(m_ListenSock, 1)) {
      // Couldn't listen on the socket
      int iWinsockErr = WSAGetLastError();
      m_State = FTP_STATE_SOCKET_ERROR;
      return;
    }
  }
  m_ControlSock = socket(AF_INET, SOCK_STREAM, 0);
  if (INVALID_SOCKET == m_ControlSock) {
    m_State = FTP_STATE_SOCKET_ERROR;
    return;
  }
  // Parse the URL
  // Get rid of any extra ftp:// stuff
  char *pURL = URL;
  if (strnicmp(URL, "ftp:", 4) == 0) {
    pURL += 4;
    while (*pURL == '/') {
      pURL++;
    }
  }
  // There shouldn't be any : in this string
  if (strchr(pURL, ':')) {
    m_State = FTP_STATE_URL_PARSING_ERROR;
    return;
  }
  // read the filename by searching backwards for a /
  // then keep reading until you find the first /
  // when you found it, you have the host and dir
  char *filestart = NULL;
  char *dirstart;
  for (int i = strlen(pURL); i >= 0; i--) {
    if (pURL[i] == '/') {
      if (!filestart) {
        filestart = pURL + i + 1;
        dirstart = pURL + i + 1;
        strcpy(m_szFilename, filestart);
      } else {
        dirstart = pURL + i + 1;
      }
    }
  }
  if ((dirstart == NULL) || (filestart == NULL)) {
    m_State = FTP_STATE_URL_PARSING_ERROR;
    return;
  } else {
    strncpy(m_szDir, dirstart, (filestart - dirstart));
    m_szDir[(filestart - dirstart)] = '\0';
    strncpy(m_szHost, pURL, (dirstart - pURL));
    m_szHost[(dirstart - pURL) - 1] = '\0';
  }
  // At this point we should have a nice host,dir and filename

#ifdef WIN32
  if (NULL == _beginthread(FTPObjThread, 0, this)) {
    m_State = FTP_STATE_INTERNAL_ERROR;
    return;
  }
#elif defined(__LINUX__) || defined(ANDROID)
  pthread_t thread;
  if (!inet_LoadThreadLib()) {
    m_State = FTP_STATE_INTERNAL_ERROR;
    return;
  }
  if (df_pthread_create(&thread, NULL, FTPObjThread, this) != 0) {
    m_State = FTP_STATE_INTERNAL_ERROR;
    return;
  }
#endif
  m_State = FTP_STATE_CONNECTING;
}

CFtpGet::~CFtpGet() {
  if (m_ListenSock != INVALID_SOCKET) {
    shutdown(m_ListenSock, 2);
#if !defined(__LINUX__) && !defined(ANDROID)
    closesocket(m_ListenSock);
#else
    close(m_ListenSock);
#endif
  }
  if (m_DataSock != INVALID_SOCKET) {
    shutdown(m_DataSock, 2);
#if !defined(__LINUX__) && !defined(ANDROID)
    closesocket(m_DataSock);
#else
    close(m_DataSock);
#endif
  }
  if (m_ControlSock != INVALID_SOCKET) {
    shutdown(m_ControlSock, 2);
#if !defined(__LINUX__) && !defined(ANDROID)
    closesocket(m_ControlSock);
#else
    close(m_ControlSock);
#endif
  }
}

// Returns a value to specify the status (ie. connecting/connected/transferring/done)
int CFtpGet::GetStatus() { return m_State; }

uint32_t CFtpGet::GetBytesIn() { return m_iBytesIn; }

uint32_t CFtpGet::GetTotalBytes() { return m_iBytesTotal; }

// This function does all the work -- connects on a blocking socket
// then sends the appropriate user and password commands
// and then the cwd command, the port command then get and finally the quit
void CFtpGet::WorkerThread() {
  ConnectControlSocket();
  if (m_State != FTP_STATE_LOGGING_IN) {
    return;
  }
  LoginHost();
  if (m_State != FTP_STATE_LOGGED_IN) {
    return;
  }
  GetFile();

  // We are all done now, and state has the current state.
  m_Aborted = true;
}

uint32_t CFtpGet::GetFile() {

  // Start off by changing into the proper dir.
  char szCommandString[200];
  int rcode;

  sprintf(szCommandString, "TYPE I\r\n");
  rcode = SendFTPCommand(szCommandString);
  if (rcode >= 400) {
    m_State = FTP_STATE_UNKNOWN_ERROR;
    return 0;
  }
  if (m_Aborting)
    return 0;
  if (m_szDir[0]) {
    sprintf(szCommandString, "CWD %s\r\n", m_szDir);
    rcode = SendFTPCommand(szCommandString);
    if (rcode >= 400) {
      m_State = FTP_STATE_DIRECTORY_INVALID;
      return 0;
    }
  }
  if (m_Aborting)
    return 0;
  if (!IssuePort()) {
    m_State = FTP_STATE_UNKNOWN_ERROR;
    return 0;
  }
  if (m_Aborting)
    return 0;
  sprintf(szCommandString, "RETR %s\r\n", m_szFilename);
  rcode = SendFTPCommand(szCommandString);
  if (rcode >= 400) {
    m_State = FTP_STATE_FILE_NOT_FOUND;
    return 0;
  }
  if (m_Aborting)
    return 0;
  // Now we will try to determine the file size...
  char *p, *s;
  p = strchr(recv_buffer, '(');
  if (p) {
    p++;
    s = strchr(p, ' ');
    *s = '\0';
    m_iBytesTotal = atoi(p);
  }
  if (m_Aborting)
    return 0;

  m_DataSock = accept(m_ListenSock, NULL, NULL); //(SOCKADDR *)&sockaddr,&iAddrLength);
                                                 // Close the listen socket
#if !defined(__LINUX__) && !defined(ANDROID)
  closesocket(m_ListenSock);
#else
  close(m_ListenSock);
#endif
  if (m_DataSock == INVALID_SOCKET) {
    int iWinsockErr = WSAGetLastError();
    m_State = FTP_STATE_SOCKET_ERROR;
    return 0;
  }
  if (m_Aborting)
    return 0;

  ReadDataChannel();

  m_State = FTP_STATE_FILE_RECEIVED;
  return 1;
}

uint32_t CFtpGet::IssuePort() {

  char szCommandString[200];
  SOCKADDR_IN listenaddr; // Socket address structure
  int iLength;            // Length of the address structure
  uint32_t nLocalPort;    // Local port for listening
  uint32_t nReplyCode;    // FTP server reply code

  // Get the address for the hListenSocket
  iLength = sizeof(listenaddr);
  if (getsockname(m_ListenSock, (SOCKADDR *)&listenaddr, &iLength) == SOCKET_ERROR) {
    int iWinsockErr = WSAGetLastError();
    m_State = FTP_STATE_SOCKET_ERROR;
    return 0;
  }

  // Extract the local port from the hListenSocket
  nLocalPort = listenaddr.sin_port;

  // Now, reuse the socket address structure to
  // get the IP address from the control socket.
  if (getsockname(m_ControlSock, (SOCKADDR *)&listenaddr, &iLength) == SOCKET_ERROR) {
    int iWinsockErr = WSAGetLastError();
    m_State = FTP_STATE_SOCKET_ERROR;
    return 0;
  }

#ifdef WIN32
  // Format the PORT command with the correct numbers.
  sprintf(szCommandString, "PORT %d,%d,%d,%d,%d,%d\r\n", listenaddr.sin_addr.S_un.S_un_b.s_b1,
          listenaddr.sin_addr.S_un.S_un_b.s_b2, listenaddr.sin_addr.S_un.S_un_b.s_b3,
          listenaddr.sin_addr.S_un.S_un_b.s_b4, nLocalPort & 0xFF, nLocalPort >> 8);
#else
  union {
    struct {
      uint8_t s_b1, s_b2, s_b3, s_b4;
    } S_un_b;
    struct {
      uint16_t s_w1, s_w2;
    } S_un_w;
    uint32_t S_addr;
  } S_un;

  S_un.S_addr = (uint32_t)listenaddr.sin_addr.s_addr;
  // Format the PORT command with the correct numbers.
  sprintf(szCommandString, "PORT %d,%d,%d,%d,%d,%d\r\n", S_un.S_un_b.s_b1, S_un.S_un_b.s_b2, S_un.S_un_b.s_b3,
          S_un.S_un_b.s_b4, nLocalPort & 0xFF, nLocalPort >> 8);
#endif

  // Tell the server which port to use for data.
  nReplyCode = SendFTPCommand(szCommandString);
  if (nReplyCode != 200) {
#if defined(__LINUX__) || defined(ANDROID)
    // I don't know if this is just Linux or do to a bug I fixed while porting to linux
    // for some reason I kept getting reply 250 here and have to read again to get the
    // "200 PORT Command OK" or whatever
    if (nReplyCode != 250 || (ReadFTPServerReply() != 200)) // ummmmmmmm
#endif
    {
      int iWinsockErr = WSAGetLastError();
      m_State = FTP_STATE_SOCKET_ERROR;
      return 0;
    }
  }

  return 1;
}

int CFtpGet::ConnectControlSocket() {
  HOSTENT *he;
  SERVENT *se;
  SOCKADDR_IN hostaddr;
  he = gethostbyname(m_szHost);
  if (he == NULL) {
    m_State = FTP_STATE_HOST_NOT_FOUND;
    return 0;
  }
  // m_ControlSock
  if (m_Aborting)
    return 0;
  se = getservbyname("ftp", NULL);

  if (se == NULL) {
    hostaddr.sin_port = htons(21);
  } else {
    hostaddr.sin_port = se->s_port;
  }
  hostaddr.sin_family = AF_INET;
  memcpy(&hostaddr.sin_addr, he->h_addr_list[0], 4);
  if (m_Aborting)
    return 0;
  // Now we will connect to the host
  if (connect(m_ControlSock, (SOCKADDR *)&hostaddr, sizeof(SOCKADDR))) {
    int iWinsockErr = WSAGetLastError();
    m_State = FTP_STATE_CANT_CONNECT;
    return 0;
  }
  m_State = FTP_STATE_LOGGING_IN;
  return 1;
}

int CFtpGet::LoginHost() {
  char szLoginString[200];
  int rcode;

  sprintf(szLoginString, "USER %s\r\n", m_szUserName);
  rcode = SendFTPCommand(szLoginString);
  if (rcode >= 400) {
    m_State = FTP_STATE_LOGIN_ERROR;
    return 0;
  }
  sprintf(szLoginString, "PASS %s\r\n", m_szPassword);
  rcode = SendFTPCommand(szLoginString);
  if (rcode >= 400) {
    m_State = FTP_STATE_LOGIN_ERROR;
    return 0;
  }

  m_State = FTP_STATE_LOGGED_IN;
  return 1;
}

uint32_t CFtpGet::SendFTPCommand(char *command) {

  FlushControlChannel();
  // Send the FTP command
  if (SOCKET_ERROR == (send(m_ControlSock, command, strlen(command), 0))) {
    int iWinsockErr = WSAGetLastError();
    // Return 999 to indicate an error has occurred
    return (999);
  }

  // Read the server's reply and return the reply code as an integer
  return (ReadFTPServerReply());
}

uint32_t CFtpGet::ReadFTPServerReply() {
  uint32_t rcode;
  uint32_t iBytesRead;
  char chunk[2];
  char szcode[5];
  uint32_t igotcrlf = 0;
  memset(recv_buffer, 0, 1000);
  do {
    chunk[0] = '\0';
    iBytesRead = recv(m_ControlSock, chunk, 1, 0);

    if (iBytesRead == SOCKET_ERROR) {
      int iWinsockErr = WSAGetLastError();
#if defined(__LINUX__) || defined(ANDROID)
      if (0 == iWinsockErr) {
        continue;
      }
#endif
      // Return 999 to indicate an error has occurred
      return (999);
    }

    if ((chunk[0] == 0x0a) || (chunk[0] == 0x0d)) {
      if (recv_buffer[0] != '\0') {
        igotcrlf = 1;
      }
    } else {
      chunk[1] = '\0';
      strcat(recv_buffer, chunk);
    }

  } while (igotcrlf == 0);

  if (recv_buffer[3] == '-') {
    // Hack -- must be a MOTD
    return ReadFTPServerReply();
  }
  if (recv_buffer[3] != ' ') {
    // We should have 3 numbers then a space
    return 999;
  }
  memcpy(szcode, recv_buffer, 3);
  szcode[3] = '\0';
  rcode = atoi(szcode);
  // Extract the reply code from the server reply and return as an integer
  return (rcode);
}

uint32_t CFtpGet::ReadDataChannel() {
  char sDataBuffer[4096]; // Data-storage buffer for the data channel
  int nBytesRecv;         // Bytes received from the data channel
  m_State = FTP_STATE_RECEIVING;
  if (m_Aborting)
    return 0;
  do {
    if (m_Aborting)
      return 0;
    nBytesRecv = recv(m_DataSock, (char *)&sDataBuffer, sizeof(sDataBuffer), 0);

#if defined(__LINUX__) || defined(ANDROID)
    if (nBytesRecv == -1) {
      int iWinsockErr = WSAGetLastError();
      if (iWinsockErr == 0) {
        nBytesRecv = 1;
        continue;
      }
    }
#endif

    m_iBytesIn += nBytesRecv;
    if (nBytesRecv > 0) {
      fwrite(sDataBuffer, nBytesRecv, 1, LOCALFILE);
      // Write sDataBuffer, nBytesRecv
    }
  } while (nBytesRecv > 0);
  fclose(LOCALFILE);
  // Close the file and check for error returns.
  if (nBytesRecv == SOCKET_ERROR) {
    // Ok, we got a socket error -- xfer aborted?
    m_State = FTP_STATE_RECV_FAILED;
    return 0;
  } else {
    // done!
    m_State = FTP_STATE_FILE_RECEIVED;
    return 1;
  }
}

void CFtpGet::FlushControlChannel() {
  fd_set read_fds;
  TIMEVAL timeout;
  int bytesin = 0;
  char flushbuff[3];

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  FD_ZERO(&read_fds);
  FD_SET(m_ControlSock, &read_fds);

  while (select(m_ControlSock + 1, &read_fds, NULL, NULL, &timeout)) {
    recv(m_ControlSock, flushbuff, 1, 0);
  }
}
