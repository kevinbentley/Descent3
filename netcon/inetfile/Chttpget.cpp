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

 * $Logfile: /DescentIII/Main/inetfile/Chttpget.cpp $
 * $Revision: 1.4 $
 * $Date: 2001/01/13 21:48:46 $
 * $Author: icculus $
 *
 * HTTP Client class (get only)
 *
 * $Log: Chttpget.cpp,v $
 * Revision 1.4  2001/01/13 21:48:46  icculus
 * patched to (re)compile on win32.
 *
 * Revision 1.3  2000/06/29 06:41:23  icculus
 * mad commits.
 *
 * Revision 1.2  2000/06/03 14:30:21  icculus
 * 1.4 code merge and pthread->SDL thread conversion.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 26    10/22/99 3:40p Kevin
 * mac merge fixes
 *
 * 25    10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 24    9/08/99 6:37p Jeff
 * fixed http/ftp downloading for Linux, should all work fine now.
 *
 * 23    8/22/99 12:32a Jeff
 * fixed select calls for Linux.  Ported Kevin's new http stuff to Linux
 *
 * 22    8/21/99 9:14p Kevin
 * Added support for redirection
 *
 * 21    8/21/99 6:33p Kevin
 * Fixed Proxy Stuff
 *
 * 20    8/21/99 6:48a Jeff
 * Linux port
 *
 * 19    8/20/99 3:01p Kevin
 * Added support for Proxies (I hope!)
 *
 * 18    8/15/99 6:38p Jeff
 * fixed compile error
 *
 * 17    8/15/99 6:26p Kevin
 *
 * 16    4/14/99 1:20a Jeff
 * fixed case mismatched #includes
 *
 * 15    3/03/99 12:28a Nate
 * sped up something or other when the connection is done
 *
 * 14    2/03/99 4:20p Kevin
 * Got multiplayer working with .mn3 files, and setup autodownloading
 *
 * 13    1/27/99 5:49p Kevin
 *
 * 12    1/27/99 5:38p Kevin
 *
 * 11    12/30/98 12:15p Kevin
 * Auto Mission Download system
 *
 * 10    10/12/98 4:59p Kevin
 * Added delay to thread when cancelled...
 *
 * 9     10/12/98 4:49p Nate
 * More fixes
 *
 * 8     10/12/98 1:54p Nate
 * Fixed bug
 *
 * 7     10/12/98 11:30a Kevin
 * More memory stuff
 *
 * 6     10/08/98 12:59p Nate
 * fixed cancel
 *
 * 5     10/08/98 9:57a Kevin
 * made transfer cancellable
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
 * 1     5/27/98 9:52a Kevin
 *
 * 1     5/25/98 5:31p Kevin
 * Initial version
 *
 * $NoKeywords: $
 */

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#include <process.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "inetgetfile.h"
#include "Chttpget.h"

#ifndef WIN32
#include "mem.h"
#else
#define mem_malloc(a) malloc(a)
#define mem_free(a) free(a)
#endif

#if defined(__LINUX__) || defined(ANDROID)

#include "SDL_thread.h"

inline void Sleep(int millis) {
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = millis * 1000;
  select(0, NULL, NULL, NULL, &tv);
}
#endif

#define NW_AGHBN_CANCEL 1
#define NW_AGHBN_LOOKUP 2
#define NW_AGHBN_READ 3

#if !defined(__LINUX__) && !defined(ANDROID)
static void HTTPObjThread(void *obj);
static void __cdecl http_gethostbynameworker(void *parm);
#else
static int HTTPObjThread(void *obj);
static int http_gethostbynameworker(void *parm);
#endif

static int http_Asyncgethostbyname(uint32_t *ip, int command, char *hostname);

#if !defined(__LINUX__) && !defined(ANDROID)
void HTTPObjThread(void *obj)
#else
int HTTPObjThread(void *obj)
#endif
{
  ((ChttpGet *)obj)->WorkerThread();
  ((ChttpGet *)obj)->m_Aborted = true;
  // OutputDebugString("http transfer exiting....\n");

#if defined(__LINUX__) || defined(ANDROID)
  return 0;
#endif
}

void ChttpGet::AbortGet() {
#ifdef WIN32
  OutputDebugString("Aborting....\n");
#endif
  m_Aborting = true;
  while (!m_Aborted)
    Sleep(50); // Wait for the thread to end
#ifdef WIN32
  OutputDebugString("Aborted....\n");
#endif
}

ChttpGet::ChttpGet(char *URL, char *localfile, char *proxyip, uint16_t proxyport) {
  m_ProxyEnabled = true;
  m_ProxyIP = proxyip;
  m_ProxyPort = proxyport;
  GetFile(URL, localfile);
}

ChttpGet::ChttpGet(char *URL, char *localfile) {
  m_ProxyEnabled = false;
  GetFile(URL, localfile);
}

void ChttpGet::PrepSocket(char *URL) {

  m_DataSock = socket(AF_INET, SOCK_STREAM, 0);
  if (INVALID_SOCKET == m_DataSock) {
    m_State = HTTP_STATE_SOCKET_ERROR;
    return;
  }

#ifdef WIN32
  unsigned long arg = 1;
  ioctlsocket(m_DataSock, FIONBIO, &arg);
#else // WIN32
  fcntl(m_DataSock, F_SETFL, fcntl(m_DataSock, F_GETFL, 0) | O_NONBLOCK);
#endif

  char *pURL = URL;
  if (strnicmp(URL, "http:", 5) == 0) {
    pURL += 5;
    while (*pURL == '/') {
      pURL++;
    }
  }
  // There shouldn't be any : in this string
  if (strchr(pURL, ':')) {
    m_State = HTTP_STATE_URL_PARSING_ERROR;
    return;
  }
  // read the filename by searching backwards for a /
  // then keep reading until you find the first /
  // when you found it, you have the host and dir
  char *filestart = NULL;
  char *dirstart = NULL;
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
    m_State = HTTP_STATE_URL_PARSING_ERROR;
    return;
  } else {
    strcpy(m_szDir, dirstart); //,(filestart-dirstart));
    // m_szDir[(filestart-dirstart)] = NULL;
    strncpy(m_szHost, pURL, (dirstart - pURL));
    m_szHost[(dirstart - pURL) - 1] = '\0';
  }
}

void ChttpGet::GetFile(char *URL, char *localfile) {
  m_DataSock = INVALID_SOCKET;
  m_iBytesIn = 0;
  m_iBytesTotal = 0;
  m_State = HTTP_STATE_STARTUP;
  ;
  m_Aborting = false;
  m_Aborted = false;

  strncpy(m_URL, URL, MAX_URL_LEN - 1);
  m_URL[MAX_URL_LEN - 1] = 0;

  LOCALFILE = fopen(localfile, "wb");
  if (NULL == LOCALFILE) {
    m_State = HTTP_STATE_CANT_WRITE_FILE;
    return;
  }

  PrepSocket(URL);

#ifdef WIN32
  if (NULL == _beginthread(HTTPObjThread, 0, this)) {
    m_State = HTTP_STATE_INTERNAL_ERROR;
    return;
  }
#elif defined(__LINUX__) || defined(ANDROID)
  //	pthread_t thread;
  SDL_Thread *thread;

  if (!inet_LoadThreadLib()) {
    m_State = HTTP_STATE_INTERNAL_ERROR;
    return;
  }

  //	if(df_pthread_create(&thread,NULL,HTTPObjThread,this)!=0)
  thread = SDL_CreateThread(HTTPObjThread, "httpget", this);
  if (thread == NULL) {
    m_State = HTTP_STATE_INTERNAL_ERROR;
    return;
  }
#endif
}

ChttpGet::~ChttpGet() {
  if (m_DataSock != INVALID_SOCKET) {
    shutdown(m_DataSock, 2);
#if !defined(__LINUX__) && !defined(ANDROID)
    closesocket(m_DataSock);
#else
    close(m_DataSock);
#endif
  }
}

int ChttpGet::GetStatus() { return m_State; }

uint32_t ChttpGet::GetBytesIn() { return m_iBytesIn; }

uint32_t ChttpGet::GetTotalBytes() { return m_iBytesTotal; }

void ChttpGet::WorkerThread() {
  char szCommand[1000];
  char *p;
  int irsp = 0;
  ConnectSocket();
  if (m_Aborting) {
    fclose(LOCALFILE);
    return;
  }
  if (m_State != HTTP_STATE_CONNECTED) {
    fclose(LOCALFILE);
    return;
  }
  snprintf(szCommand, sizeof(szCommand), "GET %s%s HTTP/1.1\nAccept: */*\nAccept-Encoding: deflate\nHost: %s\n\n\n",
           m_ProxyEnabled ? "" : "/", m_ProxyEnabled ? m_URL : m_szDir, m_szHost);
  send(m_DataSock, szCommand, strlen(szCommand), 0);
  p = GetHTTPLine();
  if (p && strnicmp("HTTP/", p, 5) == 0) {
    char *pcode;
    pcode = strchr(p, ' ') + 1;
    if (!pcode) {
      m_State = HTTP_STATE_UNKNOWN_ERROR;
      fclose(LOCALFILE);
      return;
    }
    pcode[3] = '\0';
    irsp = atoi(pcode);

    if (irsp == 0) {
      m_State = HTTP_STATE_UNKNOWN_ERROR;
      fclose(LOCALFILE);
      return;
    }
    if (irsp == 301) {

      // This is a redirection! woohoo, what fun we are going to have.
      // Next thing we need to do is find where it's redirected to.
      // We do that by looking for a "Location: xxxx" line.

      int idataready = 0;
      do {
        p = GetHTTPLine();
        if (p == NULL) {
          m_State = HTTP_STATE_UNKNOWN_ERROR;
          fclose(LOCALFILE);
          return;
        }
        if (*p == '\0') {
          idataready = 1;
          break;
        }
        if (strnicmp(p, "Location:", strlen("Location:")) == 0) {
          char *s = strchr(p, ' ') + 1;

          // Then, once we've found that, we close the sockets & reissue the whole freakin request.
          shutdown(m_DataSock, 2);

#ifdef WIN32
          closesocket(m_DataSock);
#else
          close(m_DataSock);
#endif

          m_DataSock = INVALID_SOCKET;

          // New location to look at is in 's'
          PrepSocket(s);
          WorkerThread();
          return;
        }
      } while (!idataready);
    }
    if (irsp == 200) {
      int idataready = 0;
      do {
        p = GetHTTPLine();
        if (p == NULL) {
          m_State = HTTP_STATE_UNKNOWN_ERROR;
          fclose(LOCALFILE);
          return;
        }
        if (*p == '\0') {
          idataready = 1;
          break;
        }
        if (strnicmp(p, "Content-Length:", strlen("Content-Length:")) == 0) {
          char *s = strchr(p, ' ') + 1;
          p = s;
          if (s) {
            while (*s) {
              if (!isdigit(*s)) {
                *s = '\0';
              }
              s++;
            };
            m_iBytesTotal = atoi(p);
          }
        }
      } while (!idataready);
      ReadDataChannel();
      return;
    }
    m_State = HTTP_STATE_FILE_NOT_FOUND;
    fclose(LOCALFILE);
    return;
  } else {
    m_State = HTTP_STATE_UNKNOWN_ERROR;
    fclose(LOCALFILE);
    return;
  }
}

int ChttpGet::ConnectSocket() {
  // HOSTENT *he;
  uint32_t ip;
  SERVENT *se;
  SOCKADDR_IN hostaddr;

  int rcode = 0;

  if (m_Aborting)
    return 0;

  ip = inet_addr((const char *)m_szHost);

  if (ip == INADDR_NONE) {
    http_Asyncgethostbyname(&ip, NW_AGHBN_LOOKUP, m_szHost);
    rcode = 0;
    do {
      if (m_Aborting) {
        http_Asyncgethostbyname(&ip, NW_AGHBN_CANCEL, m_szHost);
        return 0;
      }
      rcode = http_Asyncgethostbyname(&ip, NW_AGHBN_READ, m_szHost);
    } while (rcode == 0);
  }

  if (rcode == -1) {
    m_State = HTTP_STATE_HOST_NOT_FOUND;
    return 0;
  }
  // m_ControlSock
  if (m_Aborting)
    return 0;
  se = getservbyname("http", NULL);
  if (m_Aborting)
    return 0;
  if (se == NULL) {
    hostaddr.sin_port = htons(80);
  } else {
    hostaddr.sin_port = se->s_port;
  }
  hostaddr.sin_family = AF_INET;
  // ip = htonl(ip);
  memcpy(&hostaddr.sin_addr, &ip, 4);

  if (m_ProxyEnabled) {
    // This is on a proxy, so we need to make sure to connect to the proxy machine
    ip = inet_addr((const char *)m_ProxyIP);

    if (ip == INADDR_NONE) {
      http_Asyncgethostbyname(&ip, NW_AGHBN_LOOKUP, m_ProxyIP);
      rcode = 0;
      do {
        if (m_Aborting) {
          http_Asyncgethostbyname(&ip, NW_AGHBN_CANCEL, m_ProxyIP);
          return 0;
        }
        rcode = http_Asyncgethostbyname(&ip, NW_AGHBN_READ, m_ProxyIP);
      } while (rcode == 0);

      if (rcode == -1) {
        m_State = HTTP_STATE_HOST_NOT_FOUND;
        return 0;
      }
    }
    // Use either the proxy port or 80 if none specified
    hostaddr.sin_port = htons(m_ProxyPort ? m_ProxyPort : 80);
    // Copy the proxy address...
    memcpy(&hostaddr.sin_addr, &ip, 4);
  }
  // Now we will connect to the host
  fd_set wfds;

  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  int serr = connect(m_DataSock, (SOCKADDR *)&hostaddr, sizeof(SOCKADDR));
  int cerr = WSAGetLastError();
  if (serr) {
#if defined(__LINUX__) || defined(ANDROID)
    while ((cerr == WSAEALREADY) || (cerr == WSAEINVAL) || (cerr == WSAEWOULDBLOCK) || (cerr == EINPROGRESS))
#else
    while ((cerr == WSAEALREADY) || (cerr == WSAEINVAL) || (cerr == WSAEWOULDBLOCK))
#endif
    {
      FD_ZERO(&wfds);
      FD_SET(m_DataSock, &wfds);
      if (select(m_DataSock + 1, NULL, &wfds, NULL, &timeout)) {
        serr = 0;
        break;
      }
      if (m_Aborting)
        return 0;
      serr = connect(m_DataSock, (SOCKADDR *)&hostaddr, sizeof(SOCKADDR));
      if (serr == 0)
        break;
      cerr = WSAGetLastError();
      if (cerr == WSAEISCONN) {
        serr = 0;
        break;
      }
    };
  }
  if (serr) {
    m_State = HTTP_STATE_CANT_CONNECT;
    return 0;
  }
  m_State = HTTP_STATE_CONNECTED;
  return 1;
}

char *ChttpGet::GetHTTPLine() {
  uint32_t iBytesRead;
  char chunk[2];
  uint32_t igotcrlf = 0;
  memset(recv_buffer, 0, 1000);
  do {
    chunk[0] = '\0';
    bool gotdata = false;
    do {
      iBytesRead = recv(m_DataSock, chunk, 1, 0);

      if (SOCKET_ERROR == iBytesRead) {
        int error = WSAGetLastError();
#if defined(__LINUX__) || defined(ANDROID)
        if (WSAEWOULDBLOCK == error || 0 == error)
#else
        if (WSAEWOULDBLOCK == error)
#endif
        {
          gotdata = false;
          continue;
        } else {
          return NULL;
        }
      } else {
        gotdata = true;
      }
    } while (!gotdata);

    if (chunk[0] == 0x0d) {
      // This should always read a 0x0a
      do {
        iBytesRead = recv(m_DataSock, chunk, 1, 0);

        if (SOCKET_ERROR == iBytesRead) {
          int error = WSAGetLastError();
#if defined(__LINUX__) || defined(ANDROID)
          if (WSAEWOULDBLOCK == error || 0 == error)
#else
          if (WSAEWOULDBLOCK == error)
#endif
          {
            gotdata = false;
            continue;
          } else {
            return NULL;
          }
        } else {
          gotdata = true;
        }
      } while (!gotdata);
      igotcrlf = 1;
    } else {
      chunk[1] = '\0';
      strcat(recv_buffer, chunk);
    }

  } while (igotcrlf == 0);
  return recv_buffer;
}

uint32_t ChttpGet::ReadDataChannel() {
  char sDataBuffer[4096]; // Data-storage buffer for the data channel
  int nBytesRecv = 0;     // Bytes received from the data channel

  fd_set wfds;

  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 500;

  m_State = HTTP_STATE_RECEIVING;
  do {
    FD_ZERO(&wfds);
    FD_SET(m_DataSock, &wfds);

    if ((m_iBytesTotal) && (m_iBytesIn == m_iBytesTotal)) {
      break;
    }

    select(m_DataSock + 1, &wfds, NULL, NULL, &timeout);

    if (m_Aborting) {
      fclose(LOCALFILE);
      return 0;
    }

    nBytesRecv = recv(m_DataSock, (char *)&sDataBuffer, sizeof(sDataBuffer), 0);

    if (m_Aborting) {
      fclose(LOCALFILE);
      return 0;
    }

    if (SOCKET_ERROR == nBytesRecv) {
      int error = WSAGetLastError();
#if defined(__LINUX__) || defined(ANDROID)
      if (WSAEWOULDBLOCK == error || 0 == error)
#else
      if (WSAEWOULDBLOCK == error)
#endif
      {
        nBytesRecv = 1;
        continue;
      }
    }
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
    m_State = HTTP_STATE_RECV_FAILED;
    return 0;
  } else {
    // OutputDebugString("HTTP File complete!\n");
    // done!
    m_State = HTTP_STATE_FILE_RECEIVED;
    return 1;
  }
}

static async_dns_lookup httpaslu;
static async_dns_lookup *http_lastaslu = NULL;

int http_Asyncgethostbyname(uint32_t *ip, int command, char *hostname) {

  if (command == NW_AGHBN_LOOKUP) {
    if (http_lastaslu)
      http_lastaslu->abort = true;

    async_dns_lookup *newaslu;
    newaslu = (async_dns_lookup *)mem_malloc(sizeof(async_dns_lookup));
    memset(&newaslu->ip, 0, sizeof(uint32_t));
    newaslu->host = hostname;
    newaslu->done = false;
    newaslu->error = false;
    newaslu->abort = false;
    http_lastaslu = newaslu;
    httpaslu.done = false;

#ifdef WIN32
    _beginthread(http_gethostbynameworker, 0, newaslu);
#elif defined(__LINUX__) || defined(ANDROID)
    //		pthread_t thread;
    if (!inet_LoadThreadLib()) {
      return 0;
    }

    //		df_pthread_create(&thread,NULL,http_gethostbynameworker,newaslu);
    newaslu->threadId = SDL_CreateThread(http_gethostbynameworker, "httpdns", newaslu);
#endif
    return 1;
  } else if (command == NW_AGHBN_CANCEL) {
    if (http_lastaslu)
      http_lastaslu->abort = true;

#if defined(__LINUX__) || defined(ANDROID)
    SDL_WaitThread(http_lastaslu->threadId, NULL);
#endif

    http_lastaslu = NULL;
  } else if (command == NW_AGHBN_READ) {
    if (!http_lastaslu)
      return -1;
    if (httpaslu.done) {
      // free(http_lastaslu);
#if defined(__LINUX__) || defined(ANDROID)
      SDL_WaitThread(http_lastaslu->threadId, NULL);
#endif

      http_lastaslu = NULL;
      memcpy(ip, &httpaslu.ip, sizeof(uint32_t));
      return 1;
    } else if (httpaslu.error) {
#if defined(__LINUX__) || defined(ANDROID)
      SDL_WaitThread(http_lastaslu->threadId, NULL);
#endif

      mem_free(http_lastaslu);
      http_lastaslu = NULL;
      return -1;
    } else
      return 0;
  }
  return -2;
}

// This is the worker thread which does the lookup.
#if !defined(__LINUX__) && !defined(ANDROID)
void __cdecl http_gethostbynameworker(void *parm)
#else
int http_gethostbynameworker(void *parm)
#endif
{
#if defined(__LINUX__) || defined(ANDROID)
  // df_pthread_detach(df_pthread_self());
#endif
  async_dns_lookup *lookup = (async_dns_lookup *)parm;
  HOSTENT *he = gethostbyname(lookup->host);
  if (he == NULL) {
    lookup->error = true;
#if defined(__LINUX__) || defined(ANDROID)
    return 0;
#else
    return;
#endif
  } else if (!lookup->abort) {
    memcpy(&lookup->ip, he->h_addr_list[0], sizeof(uint32_t));
    lookup->done = true;
    memcpy(&httpaslu, lookup, sizeof(async_dns_lookup));
  }
  mem_free(lookup);

#if defined(__LINUX__) || defined(ANDROID)
  return 0;
#endif
}
