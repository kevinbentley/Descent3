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

#include <cstdarg>
#include <cstdio>

#include "DllWrappers.h"
#include "pserror.h"
#include "cfile.h"
#include "gamefont.h"
#include "grdefs.h"
#include "descent.h"
#include "ddio.h"
#include "movie.h"
#include "program.h"
#include "object.h"
#include "objinit.h"
#include "player.h"
#include "newui.h"
#include "hlsoundlib.h"
#include "appdatabase.h"
#include "attach.h"
#include "game.h"
#include "demofile.h"
#include "pilot.h"
#include "audiotaunts.h"
#include "ship.h"
#include "hud.h"
#include "cockpit.h"

int D3W_Play3dSound(int sound_index, object *cur_obj, float volume, int flags) {
  if (Demo_flags == DF_RECORDING) {
    DemoWrite3DSound(sound_index, OBJNUM(cur_obj), 1, volume);
  }

  return Sound_system.Play3dSound(sound_index, cur_obj, volume, flags);
}

int D3W_Play2dSound(int sound_index, float volume) {
  if (Demo_flags == DF_RECORDING) {
    DemoWrite2DSound(sound_index, volume);
  }

  return Sound_system.Play2dSound(sound_index, volume);
}

void D3W_TouchSound(int sound_index) { Sound_system.CheckAndForceSoundDataAlloc(sound_index); }

// Inventory CheckItem wrapper
bool InvCheckItem(int playernum, int type, int id) {
  ASSERT((playernum >= 0) && (playernum < MAX_PLAYERS));

  return Players[playernum].inventory.CheckItem(type, id);
}

// Inventory AddItemTypeID wrapper
bool InvAddTypeID(int playernum, int type, int id, int aux_type, int aux_id, int flags, const char *description) {
  ASSERT((playernum >= 0) && (playernum < MAX_PLAYERS));

  return Players[playernum].inventory.Add(type, id, &Objects[Players[playernum].objnum], aux_type, aux_id, flags, description);
}

// Inventory Remove wrapper
bool InvRemove(int playernum, int type, int id) {
  ASSERT((playernum >= 0) && (playernum < MAX_PLAYERS));

  return Players[playernum].inventory.Remove(type, id);
}

// Inventory GetTypeIDCount wrapper
int InvGetTypeIDCount(int playernum, int type, int id) {
  ASSERT((playernum >= 0) && (playernum < MAX_PLAYERS));

  return Players[playernum].inventory.GetTypeIDCount(type, id);
}

// Inventory Reset wrapper
void InvReset(int playernum, bool reset_all) {
  ASSERT((playernum >= 0) && (playernum < MAX_PLAYERS));

  Players[playernum].inventory.Reset(true, (reset_all) ? INVRESET_ALL : INVRESET_DEATHSPEW);
}

// mprintf
void MonoPrintf(int n, char *format, ...) {}

// wrapper for cfopen
void OpenCFILE(CFILE **handle, const char *filename, const char *mode) { *handle = cfopen(filename, mode); }

// wrapper for ObjGetUltimateParent
void GetUltimateParentForObject(object **parent, object *child) { *parent = ObjGetUltimateParent(child); }

void SetObjectDeadFlagDLL(object *obj, bool tell_clients_to_remove, bool tell_clients_to_play_sound) {
  SetObjectDeadFlag(obj, tell_clients_to_remove, tell_clients_to_play_sound);
}

void assertdll(int x, const char *expression, const char *file, int line) {
#ifndef RELEASE
  if (!(unsigned)(x)) {
    mprintf(0, "Assertion failed (%s) in %s line %d.\n", expression, file, line);
    if (Debug_break)
      DEBUG_BREAK();
    else
      AssertionFailed(expression, file, line);
  }
#endif
}

void RetrieveUICallback(void **fn) { *fn = (void *)GetUICallback(); }

bool dDatabaseRead1(const char *label, char *entry, int *entrylen) { return Database()->read(label, entry, entrylen); }

bool dDatabaseRead2(const char *label, void *entry, int wordsize) { return Database()->read(label, entry, wordsize); }

bool dDatabaseRead3(const char *label, bool *entry) { return Database()->read(label, entry); }

bool dDatabaseWrite1(const char *label, const char *entry, int entrylen) {
  return Database()->write(label, entry, entrylen);
}

bool dDatabaseWrite2(const char *label, int entry) { return Database()->write(label, entry); }

// Attaches 2 objects via attach points on each.  The f_used_aligned allows for an aligned connection.
// NOTE: The child always moves to the parent
bool dAttachObject(object *parent, char parent_ap, object *child, char child_ap, bool f_use_aligned) {
  return AttachObject(parent, parent_ap, child, child_ap, f_use_aligned);
}

// Attaches a child object to a parent object by a percent of the radius of the child.
// NOTE: The child always moves to the parent and not the reverse
bool dAttachObjectRadius(object *parent, char parent_ap, object *child, float percent_rad) {
  return AttachObject(parent, parent_ap, child, percent_rad);
}

// Unattaches a child from an attach point
bool dUnattachChild(object *parent, char parent_ap) { return UnattachChild(parent, parent_ap); }

// Unattaches an object from its parent
bool dUnattachFromParent(object *child) { return UnattachFromParent(child); }

// Unattaches all children from a parent object
bool dUnattachChildren(object *parent) { return UnattachChildren(parent); }

bool dObjGet(int handle, object **obj) {
  *obj = ObjGet(handle);
  return (*obj) ? true : false;
}

// Set a vector to {0,0,0}
void dvm_MakeZeroVector(vector *v) { vm_MakeZero(v); }

void dvm_MakeZeroAngle(angvec *v) { vm_MakeZero(v); }

void dStartFrame(int x, int y, int x2, int y2, bool clear) { StartFrame(x, y, x2, y2, clear); }

// ObjSetPos, that automatically sets the OF_MOVED_THIS_FRAME
void ObjSetPosAndMarkMoved(object *obj, vector *pos, int roomnum, matrix *orient, bool f_update_attached_children) {
  if (obj) {
    ObjSetPos(obj, pos, roomnum, orient, f_update_attached_children);
    if (Demo_flags == DF_RECORDING)
      DemoWriteChangedObj(obj); // using this instead of setting the flag, since the flag
                                // has a good chance of getting cleared before it is
                                // written
    // obj->flags |= OF_MOVED_THIS_FRAME;
  }
}

// SetObjectDeadFlag that automatically writes out demo data
void dSetObjectDeadFlagWDemo(object *obj, bool tell_clients_to_remove, bool tell_clients_to_play_sound) {
  if (Demo_flags == DF_RECORDING) {
    DemoWriteSetObjDead(obj);
  }

  SetObjectDeadFlag(obj, tell_clients_to_remove, tell_clients_to_play_sound);
}

void dSetAudioTaunts(bool enable) {
  // If the F6 menu can make perm changes, uncomment the next two lines (and comment the 3rd)
  // Current_pilot.set_audiotaunts(enable);
  // PltWriteFile(&Current_pilot,false);

  // Leave this line uncommented for non-perm changes
  taunt_Enable(enable);
}

// Changes the ship_index for a given player
void ChangePlayerShipIndex(int pnum, int ship_index) {
  int ObjInitTypeSpecific(object * objp, bool reinitializing);

  if (pnum < 0 || pnum >= MAX_PLAYERS)
    return;
  if (Players[pnum].start_roomnum == -1)
    return; // this player doesn't exist
  if (ship_index < 0 || ship_index >= MAX_SHIPS)
    return;
  if (!Ships[ship_index].used)
    return;

  bool isme = (pnum == Player_num) ? true : false;

  if (isme) {
    FreeCockpit();
    CloseShipHUD();
  }

  PlayerChangeShip(pnum, ship_index);

  // reset physics, model, etc.
  ObjInitTypeSpecific(&Objects[Players[pnum].objnum], 0);

  if (isme) {
    InitShipHUD(Players[pnum].ship_index);
    InitCockpit(Players[pnum].ship_index);

    if (GetHUDMode() == HUD_COCKPIT)
      SetHUDMode(HUD_COCKPIT);
    else if (GetHUDMode() == HUD_FULLSCREEN)
      SetHUDMode(HUD_FULLSCREEN);
  }
}

///////////////////////////////////////////////////////////////////
// adds a type/id item to the inventory (returns true on success)
bool dInven_Add(Inventory *inven, int type, int id, object *parent, int aux_type, int aux_id, int flags,
                char *description) {
  return inven->Add(type, id, parent, aux_type, aux_id, flags, description);
}

// adds an object to the inventory (marked by it's objhandle)
bool dInven_AddObject(Inventory *inven, int object_handle, int flags, char *description) {
  return inven->AddObject(object_handle, flags, description);
}

// adds a special cased CounterMeasure into the inventory
bool dInven_AddCounterMeasure(Inventory *inven, int id, int aux_type, int aux_id, int flags, char *description) {
  return inven->AddCounterMeasure(id, aux_type, aux_id, flags, description);
}

//	removes an item from the inventory (reduces it's count by one...if there is no more, then it goes bye-bye)
//	to remove an object that was added via objhandle, then pass the objhandle
//	in the 'type' parameter, and don't pass in an id.
bool dInven_Remove(Inventory *inven, int type, int id) { return inven->Remove(type, id); }

// uses an item in the inventory (also reduces its count by one...if there is no more, then it goes bye-bye)
bool dInven_Use(Inventory *inven, int type, int id, object *parent) { return inven->Use(type, id, parent); }

// uses an item in the inventory (given it's objhandle).
bool dInven_UseObjHandle(Inventory *inven, int objhandle, object *parent) { return inven->Use(objhandle, parent); }

// returns how many unique type/ids are in the inventory
int dInven_Size(Inventory *inven) { return inven->Size(); }

// returns true if there is an item in the inventory with the given type/id (or objhandle if id is -1, pass the object
// handle as the type parameter)
bool dInven_CheckItem(Inventory *inven, int type, int id) { return inven->CheckItem(type, id); }

// Resets the inventory, cleaning it out
// in_game: set to true if this is being called from during gameplay
// reset_stage:
//		INVRESET_ALL:			Reset _EVERYTHING_
//		INVRESET_LEVELCHANGE:	Remove everything except those that last across levels
//		INVRESET_DEATHSPEW:		Remove everything except those that do not spew (Default)
void dInven_Reset(Inventory *inven, bool in_game, int reset_stage) { inven->Reset(in_game, reset_stage); }

// resets the position pointer in the list to the beginning
void dInven_ResetPos(Inventory *inven) { inven->ResetPos(); }

// moves the position pointer to the next inventory item
// skip : if true then skip over non-selectable items
void dInven_NextPos(Inventory *inven, bool skip) { inven->NextPos(skip); }

// moves the position pointer to the previous inventory item
// skip : if true then skip over non-selectable items
void dInven_PrevPos(Inventory *inven, bool skip) { inven->PrevPos(skip); }

// returns the type/id of the item at the current position
// return true if it is a real object (meaning it was placed in the inventory
// via an object handle...so id will be -1)
bool dInven_GetPosTypeID(Inventory *inven, int &type, int &id) { return inven->GetPosTypeID(type, id); }

// returns the aux type/id of the item
// return true if it is a real object (meaning it was placed in the inventory
// via an object handle...so id will be -1)
bool dInven_GetAuxPosTypeID(Inventory *inven, int &type, int &id) { return inven->GetAuxPosTypeID(type, id); }

// returns the description of the item at the current position
char *dInven_GetPosDescription(Inventory *inven) { return inven->GetPosDescription(); }

// returns the icon name of the item at the current position
char *dInven_GetPosIconName(Inventory *inven) { return inven->GetPosIconName(); }

// returns the name of the item at the current position
char *dInven_GetPosName(Inventory *inven) { return inven->GetPosName(); }

// return information about the current position item
// return true if it is a real object
bool dInven_GetPosInfo(Inventory *inven, uint16_t &iflags, int &flags) { return inven->GetPosInfo(iflags, flags); }

// returns the count of the item at the current position
int dInven_GetPosCount(Inventory *inven) { return inven->GetPosCount(); }

// returns true if the position pointer is at the begining of the inventory list
bool dInven_AtBeginning(Inventory *inven) { return inven->AtBeginning(); }

// returns false if the position pointer is at the end of the inventory list
bool dInven_AtEnd(Inventory *inven) { return inven->AtEnd(); }

// jump right to an item in the inventory
void dInven_GotoPos(Inventory *inven, int newpos) { inven->GotoPos(newpos); }

// jump right to an item in the inventory give it's type and id
// to jump to an item that was added via object handle, pass the object
// handle in as the type, and make id -1.
void dInven_GotoPosTypeID(Inventory *inven, int type, int id) { inven->GotoPos(type, id); }

// uses the currently selected item
bool dInven_UsePos(Inventory *inven, object *parent) { return inven->UsePos(parent); }

// returns the 'index' position of the current position
int dInven_GetPos(Inventory *inven) { return inven->GetPos(); }

// checks the pos, if its on a nonselectable item it will move to the next selectable (NULL if none)
void dInven_ValidatePos(Inventory *inven, bool forward) { inven->ValidatePos(forward); }

// returns whether an item is selectable
bool dInven_IsSelectable(Inventory *inven) { return inven->IsSelectable(); }

bool dInven_IsUsable(Inventory *inven) { return inven->IsUsable(); }

// returns how many of an type/id is in the inventory
// for object handle items, pass the object handle in as the type and leave
// id as -1
int dInven_GetTypeIDCount(Inventory *inven, int type, int id) { return inven->GetTypeIDCount(type, id); }

// searches the inventory for the specified type/id, sets the pos to it
// for object handle items, pass the object handle in as the type and leave
// id as -1
bool dInven_FindPos(Inventory *inven, int type, int id) { return inven->FindPos(type, id); }

// gets a detailed list of information about what is in the inventory
// returns the number of items filled in.
int dInven_GetInventoryItemList(Inventory *inven, tInvenList *list, int max_amount, int *cur_sel) {
  return inven->GetInventoryItemList(list, max_amount, cur_sel);
}
