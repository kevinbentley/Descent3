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

 * $Logfile: /DescentIII/Main/Lib/inetgetfile.h $
 * $Revision: 1.6 $
 * $Date: 2004/03/21 17:11:39 $
 * $Author: kevinb $
 *
 * InternetGetFile Class header
 *
 * $Log: inetgetfile.h,v $
 * Revision 1.6  2004/03/21 17:11:39  kevinb
 * Fixes so linux will compile again. Tested with gcc-2.96
 *
 * Revision 1.5  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.4  2004/02/09 04:14:51  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.3  2000/09/22 19:05:09  icculus
 * updated.
 *
 * Revision 1.2  2000/06/03 14:33:51  icculus
 * Merge with Outrage 1.4 tree...
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 10    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 9     8/23/99 5:12p Kevin
 * Proxy support for http
 *
 * 8     8/21/99 6:48a Jeff
 * Linux port
 *
 * 7     4/17/99 5:49a Jeff
 * changes made so it compiles under Linux
 *
 * 6     4/14/99 3:59a Jeff
 * fixed case mismatches in #includes
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
 * 1     5/27/98 9:54a Kevin
 *
 * 1     5/25/98 5:31p Kevin
 * Initial version
 *
 * $NoKeywords: $
 */
#ifndef _INET_GETFILE_HEADER_
#define _INET_GETFILE_HEADER_

// At the end of this file is an example of usage

#if defined(__LINUX__)
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/time.h>
#include <unistd.h>

#include "linux_fix.h"

// Linux includes/defines
#if !MACOSX
#include <linux/types.h>
// #include <linux/if.h>
#endif

#define BOOL bool

#ifndef SOCKET
#define SOCKET int
#endif

#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr
#define INVALID_SOCKET -1
#define HOSTENT struct hostent
#define SERVENT struct servent
#define TIMEVAL struct timeval
// Winsock = sockets error translation
#define WSAEWOULDBLOCK EWOULDBLOCK
#define WSAEINVAL EINVAL
#define WSAENOPROTOOPT ENOPROTOOPT
#define WSAEALREADY EALREADY
#define WSAEISCONN EISCONN
#define SOCKET_ERROR -1

#ifndef WSAGetLastError
#define WSAGetLastError() errno
#endif



/*
typedef int (*pthread_create_fp)(pthread_t *__thread,__const pthread_attr_t *__attr,void *(*__start_routine) (void
*),void *__arg); typedef void (*pthread_exit_fp)(void *__retval); typedef int (*pthread_detach_fp)(pthread_t __th);
typedef pthread_t (*pthread_self_fp)(void);

extern pthread_create_fp df_pthread_create;
extern pthread_exit_fp df_pthread_exit;
extern pthread_detach_fp df_pthread_detach;
extern pthread_self_fp df_pthread_self;
*/

bool inet_LoadThreadLib(void);

#endif

#include "CFtp.h"
#include "Chttpget.h"

#define INET_ERROR_NO_ERROR 0
#define INET_ERROR_BADPARMS 1
#define INET_ERROR_CANT_WRITE_FILE 2
#define INET_ERROR_CANT_PARSE_URL 3
#define INET_ERROR_BAD_FILE_OR_DIR 4
#define INET_ERROR_HOST_NOT_FOUND 5
#define INET_ERROR_UNKNOWN_ERROR 6
#define INET_ERROR_NO_MEMORY 7

#define INET_STATE_CONNECTING 1
#define INET_STATE_ERROR 2
#define INET_STATE_RECEIVING 3
#define INET_STATE_GOT_FILE 4

class InetGetFile {
public:
  InetGetFile(char *URL, char *localfile);
  InetGetFile(char *URL, char *localfile, char *proxyip, int16_t proxyport);
  ~InetGetFile();
  BOOL IsFileReceived();
  BOOL IsFileError();
  BOOL IsConnecting();
  BOOL IsReceiving();
  int GetErrorCode();
  int GetBytesIn();
  int GetTotalBytes();
  void AbortGet();

protected:
  CFtpGet *ftp;
  ChttpGet *http;
  BOOL m_bUseHTTP;
  int m_ErrorCode;
  int m_State;
  int m_HardError;
};

#endif

/*

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "inetgetfile.h"

int main(int argc,char **argv)
{
        uint32_t LastPrintbytes = time(NULL);
        InetGetFile *inetfile;
        WSADATA	ws_data;
        WORD ver=MAKEWORD(1,1);

        int error=WSAStartup(ver,&ws_data);
        inetfile = new
InetGetFile("http://www.volition-inc.com/images/download/freespace/fsdemo1x-12u.exe","e:\\fsdemo1x-12u.exe"); do
        {
                if(inetfile->IsFileReceived())
                {
                        printf("File received\n");
                        break;
                }
                if(inetfile->IsFileError())
                {
                        printf("File not received. Error code: %d\n",inetfile->GetErrorCode());
                        break;
                }
                if(time(NULL)-LastPrintbytes>=1)
                {
                        int ipct = 0;
                        if(inetfile->GetTotalBytes())
                        {
                                ipct = 100*(float)((float)inetfile->GetBytesIn()/(float)inetfile->GetTotalBytes());
                        }
                        printf("Received %d Bytes out of %d
(%d%%).\n",inetfile->GetBytesIn(),inetfile->GetTotalBytes(),ipct); LastPrintbytes = time(NULL);
                }


        }while(!kbhit());
        return 0;

}



 */
