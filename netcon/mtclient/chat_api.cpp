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
 */

#ifdef WIN32
#include "windows.h"
#endif

#include <cstdio>
#include <cstring>

#ifdef __LINUX__
#include <sys/time.h>
#include <unistd.h>
#endif

#include "chat_api.h"
#include "grdefs.h"
#include "mtstrings.h"
#include "networking.h"

extern const char *GetString(int d);

typedef void *(*mem_malloc_fp)(int size);
extern mem_malloc_fp DLLmem_malloc;

typedef void (*mem_free_fp)(void *memblock);
extern mem_free_fp DLLmem_free;

typedef int (*nw_Asyncgethostbyname_fp)(uint32_t *ip, int command, const char *hostname);
extern nw_Asyncgethostbyname_fp DLLnw_Asyncgethostbyname;

typedef int (*PollUI_fp)();
extern PollUI_fp DLLPollUI;

#ifndef RELEASE
#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)
#else
#define DLLmprintf(...)
#endif

typedef void (*Debug_ConsolePrintf_fp)(int n, const char *format, ...);
extern Debug_ConsolePrintf_fp DLLDebug_ConsolePrintf;
#define MAXCHATBUFFER 500

SOCKET Chatsock;
SOCKADDR_IN Chataddr;
int Socket_connecting = 0;
char Nick_name[33];
char Orignial_nick_name[33];
int Nick_variety = 0;
char szChat_channel[33] = "";
char Input_chat_buffer[MAXCHATBUFFER] = "";
char Chat_tracker_id[33];
char Getting_user_channel_info_for[33] = "";
char Getting_user_tracker_info_for[33] = "";
int Getting_user_channel_error = 0;
int Getting_user_tracker_error = 0;
char User_req_tracker_id[100] = ""; // These are oversized for saftey
char User_req_channel[100] = "";
char *User_list = nullptr;
char *Chan_list = nullptr;
int Socket_connected = 0;
int Chat_server_connected = 0;
int Joining_channel = 0;
int Joined_channel = 0;
int GettingChannelList = 0;
int GettingUserTID = 0;
int GettingUserChannel = 0;

Chat_user *Firstuser, *Curruser;
Chat_command *Firstcommand, *Currcommand;
Chat_channel *Firstchannel, *Currchannel;

void ChatInit() {
  Socket_connecting = 0;
  Nick_name[0] = 0;
  Orignial_nick_name[0] = 0;
  Nick_variety = 0;
  szChat_channel[0] = '\0';
  Input_chat_buffer[0] = '\0';
  Chat_tracker_id[0] = 0;
  Getting_user_channel_info_for[0] = '\0';
  Getting_user_tracker_info_for[0] = '\0';
  Getting_user_channel_error = 0;
  Getting_user_tracker_error = 0;
  User_req_tracker_id[0] = '\0';
  User_req_channel[0] = '\0';
  User_list = nullptr;
  Chan_list = nullptr;
  Socket_connected = 0;
  Chat_server_connected = 0;
  Joining_channel = 0;
  Joined_channel = 0;
  GettingChannelList = 0;
  GettingUserTID = 0;
  GettingUserChannel = 0;
}

// Return codes:
//-2 Already connected
//-1 Failed to connect
// 0 Connecting
// 1 Connected
// Call it once with the server IP address, and it will return immediately
// with 0. Keep calling it until it returns something other than 0
// note: the nickname may be changed if someone with that name already
// exists (Scourge1 for instance)
int ConnectToChatServer(const char *serveraddr, int16_t chat_port, char *nickname, char *trackerid) {
  char signon_str[100];

  // if(Socket_connected && ) return -2;

  if (!Socket_connecting) {
    strcpy(Nick_name, nickname);
    for (uint32_t l = 0; l < strlen(Nick_name); l++)
      if (Nick_name[l] == ' ')
        Nick_name[l] = '_';
    strcpy(Orignial_nick_name, nickname);
    strcpy(Chat_tracker_id, trackerid);

    Firstuser = nullptr;
    Firstcommand = nullptr;
    Chat_server_connected = 0;
    FlushChatCommandQueue();

    if (chat_port == 0) {
      // AfxMessageBox("Invalid chat port, must be host.com:port (ie. irc.dal.net:6667)");
      return -1;
    }

    Chatsock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == Chatsock) {
      // AfxMessageBox("Unable to open socket!");
      return -1;
    }

    memset(&Chataddr, 0, sizeof(SOCKADDR_IN));
    Chataddr.sin_family = AF_INET;
    Chataddr.sin_addr.s_addr = INADDR_ANY;
    Chataddr.sin_port = 0;

    if (SOCKET_ERROR == bind(Chatsock, (SOCKADDR *)&Chataddr, sizeof(sockaddr))) {
      // AfxMessageBox("Unable to bind socket!");
      return -1;
    }

#ifdef WIN32
    unsigned long arg = 1;
    ioctlsocket(Chatsock, FIONBIO, &arg);
#else // WIN32
    fcntl(Chatsock, F_SETFL, fcntl(Chatsock, F_GETFL, 0) | O_NONBLOCK);
#endif

    /*
    HOSTENT *he;
    he = gethostbyname(chat_server);
    if(!he)
    {
            //AfxMessageBox("Unable to gethostbyname.\n");
            return -1;
    }

    memcpy(&Chataddr.sin_addr.s_addr, he->h_addr_list[0],4);//&iaddr, 4);

    */

    int rcode;
    uint32_t ip;

    DLLnw_Asyncgethostbyname(&ip, NW_AGHBN_LOOKUP, serveraddr);
    do {
      rcode = DLLnw_Asyncgethostbyname(&ip, NW_AGHBN_READ, serveraddr);
      if (99 == DLLPollUI()) {
        return 0;
      }
    } while (rcode == 0);

    if (rcode != 1) {
      DLLmprintf(0, "Unable to gethostbyname(\"%s\").\n", serveraddr);
      DLLmprintf(0, "WSAGetLastError() returned %d.\n", WSAGetLastError());
      DLLnw_Asyncgethostbyname(nullptr, NW_AGHBN_CANCEL, nullptr);
      return 0;
    }
    memcpy(&Chataddr.sin_addr.s_addr, &ip, 4);

    Chataddr.sin_port = htons(chat_port);

    if (SOCKET_ERROR == connect(Chatsock, (SOCKADDR *)&Chataddr, sizeof(SOCKADDR_IN))) {
      int ret = WSAGetLastError();
#ifndef __LINUX__
      if (WSAEWOULDBLOCK == WSAGetLastError())
#else
      if (EINPROGRESS == ret || 0 == ret)
#endif
      {
        DLLmprintf(0, "Beginning socket connect\n");
        Socket_connecting = 1;
        return 0;
      }
    } else {
      // This should never happen, connect should always return WSAEWOULDBLOCK
      DLLmprintf(0, "connect returned too soon!\n");
      Socket_connecting = 1;
      Socket_connected = 1;
      DLLmprintf(0, "Socket connected, sending user and nickname request\n");
      snprintf(signon_str, sizeof(signon_str), "/USER %s %s %s :%s", "user", "user", "user", Chat_tracker_id);
      SendChatString(signon_str, 1);
      snprintf(signon_str, sizeof(signon_str), "/NICK %s", Nick_name);
      SendChatString(signon_str, 1);
      return 0;
    }
  } else {
    if (Chat_server_connected) {
      return 1;
    }

    if (!Socket_connected) {
      // Do a few select to check for an error, or to see if we are writeable (connected)
      fd_set write_fds, error_fds;

#ifdef WIN32
      TIMEVAL timeout;
#else
      struct timeval timeout;
#endif

      timeout.tv_sec = 0;
      timeout.tv_usec = 0;

      FD_ZERO(&write_fds);
      FD_SET(Chatsock, &write_fds);
      // Writable -- that means it's connected
      if (select(Chatsock + 1, nullptr, &write_fds, nullptr, &timeout)) {
        Socket_connected = 1;
        DLLmprintf(0, "Socket connected, sending user and nickname request\n");
        snprintf(signon_str, sizeof(signon_str), "/USER %s %s %s :%s", "user", "user", "user", Chat_tracker_id);
        SendChatString(signon_str, 1);
        snprintf(signon_str, sizeof(signon_str), "/NICK %s", Nick_name);
        SendChatString(signon_str, 1);
        return 0;
        // Now we are waiting for Chat_server_connected
      }
      FD_ZERO(&error_fds);
      FD_SET(Chatsock, &error_fds);
      // error -- that means it's not going to connect
      if (select(Chatsock + 1, nullptr, nullptr, &error_fds, &timeout)) {
        DLLmprintf(0, "Select returned an error!\n");
        return -1;
      }
      return 0;
    }
  }

  return 0;
}

// Call it to close the connection. It returns immediately
void DisconnectFromChatServer() {
  if (!Socket_connected)
    return;
  SendChatString("/QUIT", 1);
  shutdown(Chatsock, 2);
#ifdef WIN32
  closesocket(Chatsock);
#else
  close(Chatsock);
#endif
  Socket_connecting = 0;
  Socket_connected = 0;
  Input_chat_buffer[0] = '\0';
  if (User_list) {
    DLLmem_free(User_list);
    User_list = nullptr;
  }
  if (Chan_list) {
    DLLmem_free(Chan_list);
    Chan_list = nullptr;
  }

  Chat_server_connected = 0;
  Joining_channel = 0;
  Joined_channel = 0;
  RemoveAllChatUsers();
  FlushChatCommandQueue();
  FlushChannelList();
}

// returns NULL if no line is there to print, otherwise returns a string to
// print (all preformatted of course)
const char *GetChatText() {

  if (!Socket_connected)
    return nullptr;

  // ChatGetString will do the formatting
  return ChatGetString();
}

// Send a string to be sent as chat, or scanned for messages (/msg <user>
// string)
const char *SendChatString(const char *line, int raw) {
  char szCmd[200];
  char szTarget[50];
  if (!Socket_connected)
    return nullptr;

  if (line[0] == '/') {

    // Start off by getting the command
    strcpy(szCmd, GetWordNum(0, line + 1));
    if (stricmp(szCmd, "msg") == 0) {
      strcpy(szTarget, GetWordNum(1, line + 1));
      snprintf(szCmd, sizeof(szCmd), "PRIVMSG %s :%s\n\r", szTarget, line + strlen("/msg ") + strlen(szTarget) + 1);
      send(Chatsock, szCmd, strlen(szCmd), 0);
      szCmd[strlen(szCmd) - 2] = '\0';
      return ParseIRCMessage(szCmd, MSG_LOCAL);
    }
    if (stricmp(szCmd, "me") == 0) {
      snprintf(szCmd, sizeof(szCmd), "PRIVMSG %s :\001ACTION %s\001\n\r", szChat_channel, line + strlen("/me "));
      send(Chatsock, szCmd, strlen(szCmd), 0);
      szCmd[strlen(szCmd) - 2] = '\0';
      return ParseIRCMessage(szCmd, MSG_LOCAL);
    }
    if (stricmp(szCmd, "xyz") == 0) {
      // Special command to send raw irc commands
      snprintf(szCmd, sizeof(szCmd), "%s\n\r", line + strlen("/xyz "));
      send(Chatsock, szCmd, strlen(szCmd), 0);
      return nullptr;
    }
    if (stricmp(szCmd, "list") == 0) {
      snprintf(szCmd, sizeof(szCmd), "%s\n\r", line + 1);
      send(Chatsock, szCmd, strlen(szCmd), 0);
      return nullptr;
    }
    if (raw) {
      snprintf(szCmd, sizeof(szCmd), "%s\n\r", line + 1);
      send(Chatsock, szCmd, strlen(szCmd), 0);
      return nullptr;
    }
    return "Unrecognized command";

  } else {
    if (szChat_channel[0]) {
      snprintf(szCmd, sizeof(szCmd), "PRIVMSG %s :%s\n\r", szChat_channel, line);
      send(Chatsock, szCmd, strlen(szCmd), 0);
      szCmd[strlen(szCmd) - 2] = '\0';
      return ParseIRCMessage(szCmd, MSG_LOCAL);
    }
  }

  return nullptr;
}

// Returns a structure which contains a command and possible some data (like
// a user joining or leaving) if one is waiting
// This tells you if you need to add a user from the userlist, remove a user,
// etc. Also for status messages, like if you get knocked
// off the server for some reason.
Chat_command *GetChatCommand() {
  if (!Socket_connected)
    return nullptr;
  return GetChatCommandFromQueue();
}

// This function returns a list of users in the current channel, in one
// string, separated by spaces, terminated by a null
// (Spaces aren't allowed as part of a nickname)
char *GetChatUserList() {
  int iuser_list_length = 0;
  ;
  if (User_list) {
    DLLmem_free(User_list);
    User_list = nullptr;
  }
  if (!Socket_connected)
    return nullptr;

  Curruser = Firstuser;
  while (Curruser) {
    iuser_list_length += strlen(Curruser->nick_name) + 1;
    Curruser = Curruser->next;
  }
  Curruser = Firstuser;
  User_list = (char *)DLLmem_malloc(iuser_list_length + 1);
  User_list[0] = '\0';
  while (Curruser) {
    strcat(User_list, Curruser->nick_name);
    strcat(User_list, " ");
    Curruser = Curruser->next;
  }

  return User_list;
}

// Call this to set/join a channel. Since we can't be sure that we will be
// able to join that channel, check it for completion
// You can't be in more than one channel at a time with this API, so you
// leave the current channel before trying to join
// a new one. Because of this if the join fails, make sure you try to join
// another channel, or the user wont be able to chat
//-1 Failed to join
// 0 joining
// 1 successfully joined
int SetNewChatChannel(const char *channel) {
  char partstr[100];
  if (!Socket_connected)
    return -1;
  if (Joining_channel == 1) {
    if (Joined_channel == 1) {
      // We made it in!
      Joining_channel = 0;
      return 1;
    } else if (Joined_channel == -1) {
      // Error -- we got a message that the channel was invite only, or we were banned or something
      Joining_channel = 0;
      strcpy(szChat_channel, "");
      return -1;
    }
  } else {
    if (szChat_channel[0]) {
      snprintf(partstr, sizeof(partstr), "/PART %s", szChat_channel);
      SendChatString(partstr, 1);
    }
    strcpy(szChat_channel, channel);
    snprintf(partstr, sizeof(partstr), "/JOIN %s", szChat_channel);
    SendChatString(partstr, 1);
    Joining_channel = 1;
    Joined_channel = 0;
  }

  return 0;
}

const char *ChatGetString() {
  char ch[2];
  char *p;
  int bytesread = 1;
  static char return_string[MAXCHATBUFFER];

  while ((bytesread != 0) && (bytesread != SOCKET_ERROR)) {
    bytesread = recv(Chatsock, ch, 1, 0);
    if (bytesread == SOCKET_ERROR) {
      uint32_t lerror = WSAGetLastError();
#ifndef __LINUX__
      if (WSAEWOULDBLOCK != lerror)
#else
      if (WSAEWOULDBLOCK != lerror && 0 != lerror)
#endif
      {
        DLLmprintf(0, "recv caused an error: %d\n", lerror);
      }
      return nullptr;
    }
    if (bytesread) {
      ch[1] = '\0';
      // DLLmprintf(0,ch);
      if ((ch[0] == 0x0a) || (ch[0] == 0x0d)) {
        if (Input_chat_buffer[0] == '\0') {
          // Blank line, ignore it
          return nullptr;
        }
        strcpy(return_string, Input_chat_buffer);
        Input_chat_buffer[0] = '\0';
        // DLLmprintf(0,"->|%s\n",return_string);
        p = ParseIRCMessage(return_string, MSG_REMOTE);

        return p;
      }
      strcat(Input_chat_buffer, ch);
    } else {
      // Select said we had read data, but 0 bytes read means disconnected
      DLLmprintf(0, "Disconnected! Doh!");
      AddChatCommandToQueue(CC_DISCONNECTED, nullptr, 0);
      return nullptr;
    }
  }
  return nullptr;
}

const char *GetWordNum(int num, const char *l_String) {
  static char strreturn[600];
  static char ptokstr[600];
  char seps[10] = " \n\r\t";
  char *token, *strstart;

  strstart = ptokstr;

  strcpy(ptokstr, l_String);

  token = strtok(ptokstr, seps);

  for (int i = 0; i != num; i++) {
    token = strtok(nullptr, seps);
  }
  if (token) {
    strcpy(strreturn, token);
  } else {
    return "";
  }
  // check for the ':' char....
  if (token[0] == ':') {
    // Its not pretty, but it works, return the rest of the string
    strcpy(strreturn, l_String + ((token - strstart) + 1));
  }

  // return the appropriate response.
  return strreturn;
}

int AddChatUser(const char *nickname) {
  Curruser = Firstuser;
  while (Curruser) {
    if (stricmp(nickname, Curruser->nick_name) == 0)
      return 0;
    Curruser = Curruser->next;
  }

  Curruser = Firstuser;
  if (Firstuser == nullptr) {
    Firstuser = (Chat_user *)DLLmem_malloc(sizeof(Chat_user));
    // ASSERT(Firstuser);
    strcpy(Firstuser->nick_name, nickname);
    Firstuser->next = nullptr;
    AddChatCommandToQueue(CC_USER_JOINING, nickname, strlen(nickname) + 1);
    return 1;
  } else {
    while (Curruser->next) {
      Curruser = Curruser->next;
    }
    Curruser->next = (Chat_user *)DLLmem_malloc(sizeof(Chat_user));
    Curruser = Curruser->next;
    // ASSERT(Curruser);
    strcpy(Curruser->nick_name, nickname);
    Curruser->next = nullptr;
    AddChatCommandToQueue(CC_USER_JOINING, nickname, strlen(nickname) + 1);
    return 1;
  }
}

int RemoveChatUser(char *nickname) {
  Chat_user *prv_user = nullptr;

  Curruser = Firstuser;
  while (Curruser) {
    if (stricmp(nickname, Curruser->nick_name) == 0) {
      if (prv_user) {
        prv_user->next = Curruser->next;

      } else {
        Firstuser = Curruser->next;
      }
      AddChatCommandToQueue(CC_USER_LEAVING, Curruser->nick_name, strlen(Curruser->nick_name) + 1);
      DLLmem_free(Curruser);
      return 1;
    }
    prv_user = Curruser;
    Curruser = Curruser->next;
  }
  return 0;
}

void RemoveAllChatUsers() {
  Chat_user *tmp_user = nullptr;
  Curruser = Firstuser;
  while (Curruser) {
    tmp_user = Curruser->next;
    AddChatCommandToQueue(CC_USER_LEAVING, Curruser->nick_name, strlen(Curruser->nick_name) + 1);
    DLLmem_free(Curruser);
    Curruser = tmp_user;
  }
  Firstuser = nullptr;
}

char *ParseIRCMessage(char *Line, int iMode) {
  char szRemLine[MAXLOCALSTRING];
  const char *pszTempStr;
  char szPrefix[MAXLOCALSTRING];
  char szHackPrefix[MAXLOCALSTRING];
  char szTarget[MAXLOCALSTRING];
  char szNick[MAXLOCALSTRING];
  char szCmd[MAXLOCALSTRING];
  char szCTCPCmd[MAXLOCALSTRING];

  static char szResponse[MAXLOCALSTRING];

  int iNickLen;
  int iPrefixLen = 0;

  szPrefix[0] = '\0';
  szNick[0] = '\0';

  if (strlen(Line) >= MAXLOCALSTRING) {
    return nullptr;
  }
  // Nick included....
  if (iMode == MSG_REMOTE) {
    strcpy(szRemLine, Line);
    // Start by getting the prefix
    szHackPrefix[0] = '\0';
    if (Line[0] == ':') {
      //
      pszTempStr = GetWordNum(0, Line + 1);
      strcpy(szPrefix, pszTempStr);
      strcpy(szHackPrefix, pszTempStr);
      strcpy(szRemLine, Line + 1 + strlen(szPrefix));
    }
    // Next, get the Nick
    pszTempStr = strtok(szHackPrefix, "!");
    if (pszTempStr) {
      strcpy(szNick, pszTempStr);
    } else {
      strncpy(szNick, szPrefix, 31);
      szNick[31] = 0;
    }
    // strcpy(NewMsg.Nickname,szNick);
    iNickLen = strlen(szNick);
    iPrefixLen = strlen(szPrefix);
  } else if (iMode == MSG_LOCAL) {
    strcpy(szRemLine, Line);
    strcpy(szNick, Nick_name);
    strcpy(szPrefix, Nick_name);
    // strcpy(NewMsg.Nickname,szNick);
    iNickLen = -2;
    iPrefixLen = -2;
  }
  // Next is the command
  pszTempStr = GetWordNum(0, szRemLine);
  if (pszTempStr[0]) {
    strcpy(szCmd, pszTempStr);
  } else {
    // Shouldn't ever happen, but we can't be sure of what the host will send us.
    return nullptr;
  }

  // Move the szRemLine string up
  strcpy(szRemLine, Line + iPrefixLen + strlen(szCmd) + 2);
  // Now parse the commands!
  // printf("%s",szCmd);
  if (stricmp(szCmd, "PRIVMSG") == 0) {
    pszTempStr = GetWordNum(0, szRemLine);
    strcpy(szTarget, pszTempStr);
    strcpy(szRemLine, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + 4);
    if (szRemLine[0] == ':') {
      strcpy(szCTCPCmd, GetWordNum(0, szRemLine + 1));
      if (szCTCPCmd[strlen(szCTCPCmd) - 1] == 0x01)
        szCTCPCmd[strlen(szCTCPCmd) - 1] = 0x00;

    } else {
      strcpy(szCTCPCmd, GetWordNum(0, szRemLine));
      if (szCTCPCmd[strlen(szCTCPCmd) - 1] == 0x01)
        szCTCPCmd[strlen(szCTCPCmd) - 1] = 0x00;
    }
    if (szCTCPCmd[0] == 0x01) {
      // Handle ctcp message
      strcpy(szRemLine, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + strlen(szCTCPCmd) + 6);
      szRemLine[strlen(szRemLine) - 1] = '\0'; // null out the ending 0x01
      if (stricmp(szCTCPCmd + 1, "ACTION") == 0) {
        // Posture
        snprintf(szResponse, sizeof(szResponse), "\1\xff\x28\x28* %s %s", szNick, szRemLine);
        return szResponse;
      }
      if (iMode == MSG_LOCAL) {
        strcpy(szHackPrefix, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + 4);
        szRemLine[strlen(szRemLine) - 1] = '\0';
        snprintf(szResponse, sizeof(szResponse), "** CTCP %s %s %s", szTarget, szCTCPCmd + 1, szRemLine);
        return szResponse;
      }
      if (stricmp(szCTCPCmd + 1, "PING") == 0) {
        snprintf(szResponse, sizeof(szResponse), "/NOTICE %s :\001PING %s\001", szNick,
                 szRemLine); // Don't need the trailing \001 because szremline has it.
        SendChatString(szResponse, 1);
        return nullptr;
      }
      if (stricmp(szCTCPCmd + 1, "VERSION") == 0) {
        // reply with a notice version & copyright
        // sprintf(szTempLine,"NOTICE %s :\001VERSION Copyright(c)\001\n",szNick);

        return nullptr;
      }
      strcpy(szRemLine, 1 + GetWordNum(0, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + 4));
      szRemLine[strlen(szRemLine) - 1] = '\0';
      snprintf(szResponse, sizeof(szResponse), "** CTCP Message from %s (%s)", szNick, szRemLine);
      return nullptr; // szResponse;
    }
    // differentiate between channel and private
    if ((szTarget[0] == '#') || (szTarget[0] == '+')) {
      pszTempStr = GetWordNum(0, szRemLine);
      snprintf(szResponse, sizeof(szResponse), "\1\xff\xff\xff[%s] %s", szNick, pszTempStr);
      return szResponse;
    } else {
      if (iMode == MSG_LOCAL) {
        pszTempStr = GetWordNum(0, szRemLine);
        snprintf(szResponse, sizeof(szResponse), TXT_PXO_PRIVMSGTO, szTarget, pszTempStr);
      } else {
        pszTempStr = GetWordNum(0, szRemLine);
        snprintf(szResponse, sizeof(szResponse), TXT_PXO_PRIVMSGFROM, szNick, pszTempStr);
      }
      return szResponse;
    }
  }
  // don't handle any other messages locally.
  if (iMode == MSG_LOCAL) {
    return nullptr;
  }

  if (stricmp(szCmd, "NOTICE") == 0) {

    pszTempStr = GetWordNum(0, szRemLine);
    strcpy(szTarget, pszTempStr);
    strcpy(szRemLine, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + 4);
    if (szRemLine[0] == ':') {
      strcpy(szCTCPCmd, GetWordNum(0, szRemLine + 1));
      if (szCTCPCmd[strlen(szCTCPCmd) - 1] == 0x01)
        szCTCPCmd[strlen(szCTCPCmd) - 1] = 0x00;

    } else {
      strcpy(szCTCPCmd, GetWordNum(0, szRemLine));
      if (szCTCPCmd[strlen(szCTCPCmd) - 1] == 0x01)
        szCTCPCmd[strlen(szCTCPCmd) - 1] = 0x00;
    }
    if (szCTCPCmd[0] == 0x01) {
      // Handle ctcp message
      strcpy(szRemLine, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + strlen(szCTCPCmd) + 6);
      szRemLine[strlen(szRemLine) - 1] = '\0'; // null out the ending 0x01
      if (stricmp(szCTCPCmd + 1, "PING") == 0) {
        // This is a ping response, figure out time and print
        // sprintf(NewMsg.Message,"** Ping Response from %s: %ums",szNick,ulping);
        return nullptr;
      }

      // Default message
      strcpy(szRemLine, 1 + GetWordNum(0, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + 4));
      szRemLine[strlen(szRemLine) - 1] = '\0';
      snprintf(szResponse, sizeof(szResponse), "** CTCP Message from %s (%s)", szNick, szRemLine);
      return nullptr; // szResponse;
    }
    strncpy(szResponse, szRemLine, sizeof(szResponse));
    return nullptr;
  }
  if (stricmp(szCmd, "JOIN") == 0) {
    // see if it is me!
    if (stricmp(Nick_name, szNick) == 0) {
      // Yup, it's me!
      // if(stricmp(szChat_channel,GetWordNum(0,szRemLine))==0)
      //{
      Joined_channel = 1;
      // if(stricmp(szChat_channel,"#autoselect")==0)
      //{
      strcpy(szChat_channel, GetWordNum(0, szRemLine));
      AddChatCommandToQueue(CC_YOURCHANNEL, szChat_channel, strlen(szChat_channel) + 1);

      //}
      // CC_YOURCHANNEL
      //}
    }
    AddChatUser(szNick);

    pszTempStr = GetWordNum(0, szRemLine);
    strcpy(szTarget, pszTempStr);
    // strcpy(szRemLine,Line+iPrefixLen+strlen(szCmd)+strlen(szTarget)+3);

    // strcpy(NewMsg.Channel,szTarget);

    AddChatUser(szNick);
    snprintf(szResponse, sizeof(szResponse), "** %s has joined %s", szNick, szTarget);
    return nullptr; // szResponse;
    // Add them to the userlist too!
  }
  if (stricmp(szCmd, "PART") == 0) {
    pszTempStr = GetWordNum(0, szRemLine);
    strcpy(szTarget, pszTempStr);
    strcpy(szRemLine, Line + iPrefixLen + strlen(szCmd) + strlen(szTarget) + 3);
    // see if it is me!
    if (stricmp(Nick_name, szNick) == 0) {
      // Yup, it's me!
      // szChat_channel[0]=NULL;
      RemoveAllChatUsers();
    }

    RemoveChatUser(szNick);
    return nullptr;
    // Remove them to the userlist too!
  }
  if (stricmp(szCmd, "KICK") == 0) {
    pszTempStr = GetWordNum(0, szRemLine);
    strcpy(szTarget, pszTempStr);
    pszTempStr = GetWordNum(1, szRemLine);
    strcpy(szHackPrefix, pszTempStr);
    pszTempStr = GetWordNum(2, szRemLine);
    // see if it is me!
    if (stricmp(Nick_name, GetWordNum(1, szRemLine)) == 0) {
      // Yup, it's me!
      szChat_channel[0] = '\0';
      // bNewStatus=1;
      AddChatCommandToQueue(CC_KICKED, nullptr, 0);
      RemoveAllChatUsers();
    }
    // sprintf(szResponse,"*** %s has kicked %s from channel %s (%s)",szNick,szHackPrefix,szTarget,pszTempStr);
    // Remove them to the userlist too!
    RemoveChatUser(szNick);
    return nullptr; // szResponse;
  }
  if (stricmp(szCmd, "NICK") == 0) {
    // see if it is me!
    if (stricmp(Nick_name, szNick) == 0) {
      // Yup, it's me!
      strcpy(Nick_name, GetWordNum(0, szRemLine));
    }
    char nicks[70];
    snprintf(nicks, sizeof(nicks), "%s %s", szNick, GetWordNum(0, szRemLine));
    AddChatCommandToQueue(CC_NICKCHANGED, nicks, strlen(nicks) + 1);
    RemoveChatUser(szNick);
    AddChatUser(GetWordNum(0, szRemLine));
    // sprintf(szResponse,"*** %s is now known as %s",szNick,GetWordNum(0,szRemLine));
    return nullptr; // szResponse;
  }
  if (stricmp(szCmd, "PING") == 0) {
    // respond with pong (GetWordNum(0,szRemLine))
    snprintf(szResponse, sizeof(szResponse), "/PONG :%s", GetWordNum(0, szRemLine));
    SendChatString(szResponse, 1);
    return nullptr;
  }
  if (stricmp(szCmd, "MODE") == 0) {
    // Channel Mode info
    return nullptr;
  }

  if (stricmp(szCmd, "401") == 0) {
    // This is whois user info, we can get their tracker info from here.  -5
    char szWhoisUser[33];
    strcpy(szWhoisUser, GetWordNum(1, szRemLine));
    Getting_user_tracker_error = 1;
    Getting_user_channel_error = 1;

    snprintf(szResponse, sizeof(szResponse), TXT_PXO_ERRORNOTONLINE, szWhoisUser);
    return szResponse;
  }
  if (stricmp(szCmd, "311") == 0) {
    char szWhoisUser[33];
    strcpy(szWhoisUser, GetWordNum(1, szRemLine));
    // This is whois user info, we can get their tracker info from here.  -5
    // if(stricmp(Getting_user_tracker_info_for,szWhoisUser)==0)
    //{
    strcpy(User_req_tracker_id, GetWordNum(5, szRemLine));
    //}
    return nullptr;
  }
  if (stricmp(szCmd, "319") == 0) {
    char szWhoisUser[33];
    strcpy(szWhoisUser, GetWordNum(1, szRemLine));
    // This is whois channel info -- what channel they are on		-2
    // if(stricmp(Getting_user_channel_info_for,szWhoisUser)==0)
    //{
    strcpy(User_req_channel, GetWordNum(2, szRemLine));
    //}
    return nullptr;
  }

  // End of whois and we didn't get a channel means they aren't in a channel.
  if (stricmp(szCmd, "318") == 0) {
    if (!*User_req_channel) {
      User_req_channel[0] = '*';
    }
  }

  if (stricmp(szCmd, "321") == 0) {
    // start of channel list
    FlushChannelList();
    GettingChannelList = 1;
    return nullptr;
  }
  if (stricmp(szCmd, "322") == 0) {
    // channel list data
    if (GettingChannelList == 1) {
      char channel_list_name[33];
      char sztopic[200];
      strcpy(sztopic, GetWordNum(3, szRemLine));
      strcpy(channel_list_name, GetWordNum(1, szRemLine));
      AddChannel(channel_list_name, atoi(GetWordNum(2, szRemLine)), sztopic);
    }
    return nullptr;
  }
  if (stricmp(szCmd, "323") == 0) {
    // end of channel list
    GettingChannelList = 2;
    return nullptr;
  }
  if (stricmp(szCmd, "324") == 0) {
    // Channel Mode info
    return nullptr;
  }

  if (stricmp(szCmd, "332") == 0) {
    // Channel Topic, update status bar.
    if (stricmp(szChat_channel, szTarget) == 0) {
      // strncpy(szChanTopic,GetWordNum(2,szRemLine),70);
    }
    // sprintf(NewMsg.Message,"*** %s has changed the topic to: %s",szNick,GetWordNum(2,szRemLine));

    return nullptr;
  }
  if (stricmp(szCmd, "TOPIC") == 0) {
    // Channel Topic, update status bar.
    if (stricmp(szChat_channel, szTarget) == 0) {
      // strncpy(szChanTopic,GetWordNum(1,szRemLine),70);
    }
    // sprintf(NewMsg.Message,"*** %s has changed the topic to: %s",szNick,GetWordNum(1,szRemLine));
    return nullptr;
  }
  if (stricmp(szCmd, "QUIT") == 0) {
    // Remove the user!
    RemoveChatUser(szNick);
    return nullptr;
  }
  if (stricmp(szCmd, "376") == 0) // end of motd, trigger autojoin...
  {
    if (!Chat_server_connected) {
      DLLmprintf(0, "Connected to chat server!\n");
      Chat_server_connected = 1;
      // We want to make sure we know our nick. This is somewhat of a hack
      strcpy(Nick_name, GetWordNum(0, szRemLine + 1));
    }
    return nullptr;
  }
  if ((stricmp(szCmd, "377") == 0) || (stricmp(szCmd, "372") == 0) || (stricmp(szCmd, "372") == 0)

  ) {
    // Stip the message, and display it.
    pszTempStr = GetWordNum(3, Line);
    snprintf(szResponse, sizeof(szResponse), "\1\xcf\xf8\xb9%s", pszTempStr);
    return szResponse;
  }
  // Ignore these messages
  if (((stricmp(szCmd, "366") == 0)) || (stricmp(szCmd, "333") == 0) || // Who set the topic
      (stricmp(szCmd, "329") == 0))                                     // Time Channel created
  /*
  (stricmp(szCmd,"305")==0) ||
  (stricmp(szCmd,"306")==0) ||
  (stricmp(szCmd,"311")==0) || //WHOIS stuff
  (stricmp(szCmd,"312")==0) ||
  (stricmp(szCmd,"313")==0) ||
  (stricmp(szCmd,"317")==0) ||
  (stricmp(szCmd,"318")==0) ||
  (stricmp(szCmd,"319")==0) ||
  */

  {
    return nullptr;
  }
  if (stricmp(szCmd, "353") == 0) {

    // Names in the channel.
    pszTempStr = GetWordNum(3, Line + iPrefixLen + strlen(szCmd) + 2);
    strcpy(szRemLine, pszTempStr);
    pszTempStr = strtok(szRemLine, " ");

    while (pszTempStr) {
      if (pszTempStr[0] == '@') {
        AddChatUser(pszTempStr + 1);
      } else if (pszTempStr[0] == '+') {
        AddChatUser(pszTempStr + 1);
      } else {
        AddChatUser(pszTempStr);
      }
      pszTempStr = strtok(nullptr, " ");
    }
    return nullptr;
  }
  // MOTD Codes
  if ((stricmp(szCmd, "001") == 0) || (stricmp(szCmd, "002") == 0) || (stricmp(szCmd, "003") == 0) ||
      (stricmp(szCmd, "004") == 0) || (stricmp(szCmd, "251") == 0) || (stricmp(szCmd, "254") == 0) ||
      (stricmp(szCmd, "255") == 0) || (stricmp(szCmd, "265") == 0) || (stricmp(szCmd, "375") == 0) ||
      (stricmp(szCmd, "372") == 0) || (stricmp(szCmd, "375") == 0)) {
    // Stip the message, and display it.
    pszTempStr = GetWordNum(3, Line);
    strcpy(szResponse, pszTempStr);
    return nullptr;
    // return szResponse;
  }
  if (stricmp(szCmd, "432") == 0) {
    // Channel Mode info
    snprintf(szResponse, sizeof(szResponse), "%s", TXT_PXO_BADNICK);
    AddChatCommandToQueue(CC_DISCONNECTED, nullptr, 0);
    return szResponse;
  }
  if (stricmp(szCmd, "433") == 0) {
    // Channel Mode info
    char new_nick[33];
    snprintf(new_nick, sizeof(new_nick), "%s%d", Orignial_nick_name, Nick_variety);
    strcpy(Nick_name, new_nick);
    Nick_variety++;
    snprintf(szResponse, sizeof(szResponse), "/NICK %s", new_nick);
    SendChatString(szResponse, 1);
    return nullptr;
  }
  // Default print
  strcpy(szResponse, Line);
  // return szResponse;
  return nullptr;
}

void AddChatCommandToQueue(int command, const void *data, int len) {
  Currcommand = Firstcommand;
  if (Firstcommand == nullptr) {
    Firstcommand = (Chat_command *)DLLmem_malloc(sizeof(Chat_command));
    // ASSERT(Firstcommand);
    Firstcommand->next = nullptr;
    Currcommand = Firstcommand;
  } else {
    while (Currcommand->next) {
      Currcommand = Currcommand->next;
    }
    Currcommand->next = (Chat_command *)DLLmem_malloc(sizeof(Chat_command));
    // ASSERT(Currcommand->next);
    Currcommand = Currcommand->next;
  }
  Currcommand->command = command;
  if (len && data)
    memcpy(&Currcommand->data, data, len);
  Currcommand->next = nullptr;
}

Chat_command *GetChatCommandFromQueue() {
  static Chat_command response_cmd;
  Chat_command *tmp_cmd;
  if (!Firstcommand)
    return nullptr;
  Currcommand = Firstcommand;
  memcpy(&response_cmd, Currcommand, sizeof(Chat_command));
  tmp_cmd = Currcommand->next;
  DLLmem_free(Firstcommand);
  Firstcommand = tmp_cmd;
  return &response_cmd;
}

void FlushChatCommandQueue() {
  Chat_command *tmp_cmd;
  Currcommand = Firstcommand;

  while (Currcommand) {
    tmp_cmd = Currcommand->next;
    DLLmem_free(Currcommand);
    Currcommand = tmp_cmd;
  }
  Firstcommand = nullptr;
}

void FlushChannelList() {
  Chat_channel *tmp_chan;
  Currchannel = Firstchannel;

  while (Currchannel) {
    tmp_chan = Currchannel->next;
    DLLmem_free(Currchannel);
    Currchannel = tmp_chan;
  }
  Firstchannel = nullptr;
}
char *GetChannelList() {
  int ichan_list_length = 0;
  char sznumusers[10];

  if (GettingChannelList != 2)
    return nullptr;
  if (!Socket_connected)
    return nullptr;

  if (Chan_list) {
    DLLmem_free(Chan_list);
    Chan_list = nullptr;
  }

  Currchannel = Firstchannel;
  while (Currchannel) {
    ichan_list_length += strlen(Currchannel->topic) + 1 + strlen(Currchannel->channel_name) + 1 +
                         5; // 1 for the space, and 4 for the number of users 0000-9999 + space
    Currchannel = Currchannel->next;
  }
  Currchannel = Firstchannel;
  Chan_list = (char *)DLLmem_malloc(ichan_list_length + 1);
  Chan_list[0] = '\0';
  while (Currchannel) {
    strcat(Chan_list, "$");
    strcat(Chan_list, Currchannel->channel_name);
    strcat(Chan_list, " ");
    snprintf(sznumusers, sizeof(sznumusers), "%d ", Currchannel->users);
    strcat(Chan_list, sznumusers);
    strcat(Chan_list, Currchannel->topic); // fgets
    strcat(Chan_list, " ");
    Currchannel = Currchannel->next;
  }
  FlushChannelList();
  GettingChannelList = 0;
  return Chan_list;
}

void AddChannel(char *channel, uint16_t numusers, char *topic) {
  Currchannel = Firstchannel;
  if (Firstchannel == nullptr) {
    Firstchannel = (Chat_channel *)DLLmem_malloc(sizeof(Chat_channel));
    // ASSERT(Firstchannel);
    strcpy(Firstchannel->channel_name, channel);
    strcpy(Firstchannel->topic, topic);
    Firstchannel->users = numusers;
    Firstchannel->next = nullptr;
    Currchannel = Firstchannel;
  } else {
    while (Currchannel->next) {
      Currchannel = Currchannel->next;
    }
    Currchannel->next = (Chat_channel *)DLLmem_malloc(sizeof(Chat_channel));
    // ASSERT(Currchannel->next);
    Currchannel = Currchannel->next;
    strcpy(Currchannel->channel_name, channel);
    strcpy(Currchannel->topic, topic);
    Currchannel->users = numusers;
  }
  Currchannel->next = nullptr;
}

char *GetTrackerIdByUser(const char *nickname) {
  char szWhoisCmd[100];

  if (nickname == (char *)-1) {
    GettingUserTID = 0;
    Getting_user_tracker_error = 0;
    return nullptr;
  } else if (GettingUserTID) {
    if (Getting_user_tracker_error) {
      Getting_user_tracker_error = 0;
      GettingUserTID = 0;
      return (char *)-1;
    }

    if (*User_req_tracker_id) {
      GettingUserTID = 0;
      return User_req_tracker_id;
    }
  } else {
    strcpy(Getting_user_tracker_info_for, nickname);
    snprintf(szWhoisCmd, sizeof(szWhoisCmd), "/WHOIS %s", nickname);
    User_req_tracker_id[0] = '\0';
    SendChatString(szWhoisCmd, 1);
    GettingUserTID = 1;
  }
  return nullptr;
}

char *GetChannelByUser(const char *nickname) {
  char szWhoisCmd[100];

  if (nickname == (char *)-1) {
    GettingUserChannel = 0;
    Getting_user_channel_error = 0;
    return nullptr;
  } else if (GettingUserChannel) {
    if (Getting_user_channel_error) {
      Getting_user_channel_error = 0;
      GettingUserChannel = 0;
      return (char *)-1;
    }
    if (*User_req_channel) {
      GettingUserChannel = 0;
      return User_req_channel;
    }
  } else {
    strcpy(Getting_user_channel_info_for, nickname);
    User_req_channel[0] = '\0';
    snprintf(szWhoisCmd, sizeof(szWhoisCmd), "/WHOIS %s", nickname);
    SendChatString(szWhoisCmd, 1);
    GettingUserChannel = 1;
  }
  return nullptr;
}
