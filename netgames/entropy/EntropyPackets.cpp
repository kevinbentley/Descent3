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

 * $Logfile: /DescentIII/Main/entropy/EntropyPackets.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:57:41 $
 * $Author: kevinb $
 *
 * <insert description of file here>
 *
 * $Log: EntropyPackets.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:57:41  kevinb
 * initial 1.5 import
 *
 *
 * 10    5/21/99 10:03a Jeff
 * hopefully filled in any remaining gaps related to have more than you
 * can carry virus loads
 *
 * 9     5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 8     5/12/99 11:28a Jeff
 * added sourcesafe comment block
 *
 * $NoKeywords: $
 */

#include "gamedll_header.h"
#include <string.h>
#include "idmfc.h"
#include "Entropystr.h"
#include "EntropyAux.h"

extern IDMFC *DMFCBase;
extern room *dRooms;
extern object *dObjects;

void SendTakeOverPacket(int newteam, int oldteam, int room, int victor) {
  int count = 0;

  uint8_t data[MAX_GAME_DATA_SIZE];
  DMFCBase->StartPacket(data, SPID_TAKEOVER, &count);

  MultiAddByte(newteam, data, &count);
  MultiAddByte(oldteam, data, &count);
  MultiAddByte(victor, data, &count);
  MultiAddInt(room, data, &count);

  DMFCBase->SendPacket(data, count, SP_ALL);
}

void ReceiveTakeOverPacket(uint8_t *data) {
  uint8_t newteam, oldteam;
  int room;
  int count = 0;
  int victor;

  newteam = MultiGetByte(data, &count);
  oldteam = MultiGetByte(data, &count);
  victor = MultiGetByte(data, &count);
  room = MultiGetInt(data, &count);
  TakeOverRoom(newteam, oldteam, room, victor);
}

// Handles when we get a new player packet
void GetGameStartPacket(uint8_t *data) {
  int i, count = 0;

  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    if (MultiGetByte(data, &count)) {
      NumberOfKillsSinceLastDeath[i] = MultiGetInt(data, &count);
      int num_virus = MultiGetInt(data, &count);
      int v_count;
      RemoveVirusFromPlayer(i, true);

      for (v_count = 0; v_count < num_virus; v_count++) {
        DLLInvAddTypeID(i, OBJ_POWERUP, virus_id, -1, -1, 0, TXT_VIRUS);
      }
    }
  }

  for (i = 0; i < NUM_TEAMS; i++) {
    TeamScore[i] = MultiGetInt(data, &count);
  }
}

// Handles sending a new player packet
void SendGameStartPacket(int pnum) {
  int count = 0;
  int i;

  uint8_t data[MAX_GAME_DATA_SIZE];
  DMFCBase->StartPacket(data, SPID_NEWPLAYER, &count);

  for (i = 0; i < DLLMAX_PLAYERS; i++) {
    if (DMFCBase->CheckPlayerNum(i)) {
      MultiAddByte(1, data, &count);
      MultiAddInt(NumberOfKillsSinceLastDeath[i], data, &count);
      MultiAddInt(DLLInvGetTypeIDCount(i, OBJ_POWERUP, virus_id), data, &count);
    } else {
      MultiAddByte(0, data, &count);
    }
  }

  for (i = 0; i < NUM_TEAMS; i++) {
    MultiAddInt(TeamScore[i], data, &count);
  }

  DMFCBase->SendPacket(data, count, pnum);

  // send over the rest
  SendRoomInfo(pnum);
}

void SendClientPickupVirus(int player_num) {
  int start, count = 0;
  uint8_t data[MAX_GAME_DATA_SIZE];
  DMFCBase->StartPacket(data, SPID_PICKUPVIRUS, &count);
  start = count;

  MultiAddByte(player_num, data, &count);
  ReceivePickupVirus(&data[start]);
  DMFCBase->SendPacket(data, count, SP_ALL);
}

void ReceivePickupVirus(uint8_t *data) {
  int player_num, count = 0;
  player_num = MultiGetByte(data, &count);

  DLLInvAddTypeID(player_num, OBJ_POWERUP, virus_id, -1, -1, 0, TXT_VIRUS);

  if (player_num == DMFCBase->GetPlayerNum()) {
    DLLAddHUDMessage(TXT_PICKUPVIRUS);
  }
}

#define RT_REDLAB 0
#define RT_REDREP 1
#define RT_REDENG 2
#define RT_BLULAB 3
#define RT_BLUREP 4
#define RT_BLUENG 5

// FIXME: MTS: only used in this file.
void SendRoomInfo(int pnum) {
  char *room_info = NULL;
  int flags, r, i;
  room_info = (char *)malloc(sizeof(char) * RoomCount);
  if (!room_info)
    return;

  for (r = 0; r < RoomCount; r++) {
    flags = dRooms[RoomList[r]].flags;

    if (flags & RF_SPECIAL1) {
      room_info[r] = RT_REDLAB;
    }
    if (flags & RF_SPECIAL2) {
      room_info[r] = RT_REDENG;
    }
    if (flags & RF_SPECIAL3) {
      room_info[r] = RT_REDREP;
    }
    if (flags & RF_SPECIAL4) {
      room_info[r] = RT_BLULAB;
    }
    if (flags & RF_SPECIAL5) {
      room_info[r] = RT_BLUENG;
    }
    if (flags & RF_SPECIAL6) {
      room_info[r] = RT_BLUREP;
    }
  }

  int count = 0;

  uint8_t data[MAX_GAME_DATA_SIZE];
  DMFCBase->StartPacket(data, SPID_ROOMINFO, &count);

  for (i = 0; i < RoomCount; i++) {
    MultiAddByte(room_info[i], data, &count);
  }

  for (i = 0; i < NUM_TEAMS; i++) {
    MultiAddInt(TeamOwnedRooms[i], data, &count);
  }

  DMFCBase->SendPacket(data, count, pnum);

  free(room_info);
}

void ReceiveRoomInfo(uint8_t *data) {
  int i, count = 0;
  int flag;
  char *room_info;
  room_info = (char *)malloc(sizeof(char) * RoomCount);
  if (!room_info) {
    FatalError("Out of Memory");
    return;
  }

  for (i = 0; i < RoomCount; i++) {
    room_info[i] = MultiGetByte(data, &count);

    switch (room_info[i]) {
    case RT_REDLAB:
      flag = RF_SPECIAL1;
      PaintRoomWithTexture(LabText[RED_TEAM], RoomList[i]);
      break;
    case RT_REDENG:
      flag = RF_SPECIAL2;
      PaintRoomWithTexture(EnergyText[RED_TEAM], RoomList[i]);
      break;
    case RT_REDREP:
      flag = RF_SPECIAL3;
      PaintRoomWithTexture(RepairText[RED_TEAM], RoomList[i]);
      break;
    case RT_BLULAB:
      flag = RF_SPECIAL4;
      PaintRoomWithTexture(LabText[BLUE_TEAM], RoomList[i]);
      break;
    case RT_BLUENG:
      flag = RF_SPECIAL5;
      PaintRoomWithTexture(EnergyText[BLUE_TEAM], RoomList[i]);
      break;
    case RT_BLUREP:
      flag = RF_SPECIAL6;
      PaintRoomWithTexture(RepairText[BLUE_TEAM], RoomList[i]);
      break;
    default:
      flag = 0;
    }
    room *rp = &dRooms[RoomList[i]];
    rp->flags &= ~RF_SPECIAL1;
    rp->flags &= ~RF_SPECIAL2;
    rp->flags &= ~RF_SPECIAL3;
    rp->flags &= ~RF_SPECIAL4;
    rp->flags &= ~RF_SPECIAL5;
    rp->flags &= ~RF_SPECIAL6;
    rp->flags |= flag;
    rp->room_change_flags |= RCF_GOALSPECIAL_FLAGS;
  }
  free(room_info);

  for (i = 0; i < NUM_TEAMS; i++) {
    TeamOwnedRooms[i] = MultiGetInt(data, &count);
  }
}

void SendVirusCreate(object *obj) {
  int start, count = 0;

  uint8_t data[MAX_GAME_DATA_SIZE];
  DMFCBase->StartPacket(data, SPID_VIRUSCREATE, &count);
  start = count;

  int objnum = obj - dObjects;
  MultiAddInt(objnum, data, &count);
  DoVirusCreate(&data[start]);
  DMFCBase->SendPacket(data, count, SP_ALL);
}

void DoVirusCreate(uint8_t *data) {
  int s_objnum, l_objnum, count = 0;

  s_objnum = MultiGetInt(data, &count);

  l_objnum = DMFCBase->ConvertServerToLocalObjnum(s_objnum);

  if (l_objnum != -1) {
    DLLCreateRandomSparks(rand() % 150 + 100, &dObjects[l_objnum].pos, dObjects[l_objnum].roomnum, HOT_SPARK_INDEX,
                          (rand() % 3) + 2);
  }
}
