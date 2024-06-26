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

#ifdef __OSIRIS_IMPORT_H_
#define OSIRISEXTERN extern
#else
#define OSIRISEXTERN
#endif

#include "osiris_common.h"

#if defined(__LINUX__) || defined(ANDROID)
#include "linux_lib.h"
#endif

// ===========================================================

// void mprintf(int n, const char *format, ... );
// prints a debug message out to the monochrome monitor
typedef void (*mprintf_fp)(int n, const char *format, ...);
OSIRISEXTERN mprintf_fp mprintf;

// The main calling function for multisafe functions
typedef void (*MSafe_CallFunction_fp)(int type, msafe_struct *mstruct);
OSIRISEXTERN MSafe_CallFunction_fp MSafe_CallFunction;

// The main calling function for extracting multisafe data
typedef void (*MSafe_GetValue_fp)(int type, msafe_struct *mstruct);
OSIRISEXTERN MSafe_GetValue_fp MSafe_GetValue;

//	bool Obj_CallEvent(int objnum,int event,tOSIRISEventInfo *ei);
//	Sends an event to an object.  Returns true if the default action should
//	continue to process.
typedef bool (*Obj_CallEvent_fp)(int objnum, int event, tOSIRISEventInfo *ei);
OSIRISEXTERN Obj_CallEvent_fp Obj_CallEvent;

//	bool Trgr_CallEvent(int trignum,int event,tOSIRISEventInfo *ei);
//	Sends an event to a trigger.  Returns true if the default action should
//	continue to process.
typedef bool (*Trgr_CallEvent_fp)(int trignum, int event, tOSIRISEventInfo *ei);
OSIRISEXTERN Trgr_CallEvent_fp Trgr_CallEvent;

//	void Sound_TouchFile(char *sound_name);
//	Touches a sound file so it loads into memory
typedef void (*Sound_TouchFile_fp)(char *sound_name);
OSIRISEXTERN Sound_TouchFile_fp Sound_TouchFile;

//	int Obj_FindID(const char *object_name);
//	searches for an object id given it's name
typedef int (*Obj_FindID_fp)(const char *object_name);
OSIRISEXTERN Obj_FindID_fp Obj_FindID;

//	int Obj_FindType(const char *object_name);
//	searches for an object type given it's name
typedef int (*Obj_FindType_fp)(const char *object_name);
OSIRISEXTERN Obj_FindType_fp Obj_FindType;

//	int Wpn_FindID(const char *weapon_name);
//	searches through the weapons for a name and returns the id
typedef int (*Wpn_FindID_fp)(const char *weapon_name);
OSIRISEXTERN Wpn_FindID_fp Wpn_FindID;

//	float Obj_GetTimeLived(int objhandle);
//	returns how long an object has lived
typedef float (*Obj_GetTimeLived_fp)(int objhandle);
OSIRISEXTERN Obj_GetTimeLived_fp Obj_GetTimeLived;

//	void Obj_GetGunPos(int objhandle,int gun_number,vector *gun_pnt,vector *gun_normal);
//	returns information about a gunpoint of an object
typedef void (*Obj_GetGunPos_fp)(int objhandle, int gun_number, vector *gun_pnt, vector *gun_normal);
OSIRISEXTERN Obj_GetGunPos_fp Obj_GetGunPosFP;

static inline void Obj_GetGunPos(int objhandle, int gun_number, vector *gun_pnt, vector *gun_normal = NULL) {
  Obj_GetGunPosFP(objhandle, gun_number, gun_pnt, gun_normal);
}

//	void Obj_GetGroundPos(int objhandle,int ground_number,vector *ground_pnt,vector *ground_normal);
//	returns information about a groundpoint of an object
typedef void (*Obj_GetGroundPos_fp)(int objhandle, int ground_number, vector *ground_pnt, vector *ground_normal);
OSIRISEXTERN Obj_GetGroundPos_fp Obj_GetGroundPosFP;
static inline void Obj_GetGroundPos(int objhandle, int ground_number, vector *ground_pnt,
                                    vector *ground_normal = NULL) {
  Obj_GetGroundPosFP(objhandle, ground_number, ground_pnt, ground_normal);
}

//	void Room_Value(int roomnum, char op, char vhandle, void *ptr);
typedef void (*Room_Value_fp)(int roomnum, char op, char vhandle, void *ptr, int index);
OSIRISEXTERN Room_Value_fp Room_ValueFP;

static inline void Room_Value(int roomnum, char op, char vhandle, void *ptr, int index = 0) {
  Room_ValueFP(roomnum, op, vhandle, ptr, index);
}

//	uint8_t Room_IsValid(int roomnum);
//	returns 0 if the room is not valid.  1 if the room is a terrain cell. 2 if the room is a room segment
typedef uint8_t (*Room_IsValid_fp)(int roomnum);
OSIRISEXTERN Room_IsValid_fp Room_IsValid;

//	int Obj_GetAttachParent(int childhandle);
//	returns the handle to the parent of the given attached child
typedef int (*Obj_GetAttachParent_fp)(int childhandle);
OSIRISEXTERN Obj_GetAttachParent_fp Obj_GetAttachParent;

//	int Obj_GetNumAttachSlots(int objhandle);
//	returns the number of attach slots an object has.
typedef int (*Obj_GetNumAttachSlots_fp)(int objhandle);
OSIRISEXTERN Obj_GetNumAttachSlots_fp Obj_GetNumAttachSlots;

//	int Obj_GetAttachChildHandle(int objhandle,char attachpoint);
//	returns the handle to the child attached on the specified attach point of an object
typedef int (*Obj_GetAttachChildHandle_fp)(int objhandle, char attachpoint);
OSIRISEXTERN Obj_GetAttachChildHandle_fp Obj_GetAttachChildHandle;

//	int Obj_AttachObjectAP(int parenthandle,char parent_ap,int childhandle,char child_ap,uint8_t f_use_aligned);
//	Attaches one object to another object based on their attach points
typedef int (*Obj_AttachObjectAP_fp)(int parenthandle, char parent_ap, int childhandle, char child_ap,
                                     uint8_t f_use_aligned);
OSIRISEXTERN Obj_AttachObjectAP_fp Obj_AttachObjectAP;

//	int Obj_AttachObjectRad(int parenthandle,char parent_ap,int childhandle,float percent_rad);
//	Attached one object to another based on radius
typedef int (*Obj_AttachObjectRad_fp)(int parenthandle, char parent_ap, int childhandle, float percent_rad);
OSIRISEXTERN Obj_AttachObjectRad_fp Obj_AttachObjectRad;

//	void Obj_UnattachFromParent(int objhandle);
//	Detaches an object from it's parent
typedef void (*Obj_UnattachFromParent_fp)(int objhandle);
OSIRISEXTERN Obj_UnattachFromParent_fp Obj_UnattachFromParent;

//	void Obj_UnattachChild(int objhandle,char parent_ap);
//	Detaches a child object from it's parent
typedef void (*Obj_UnattachChild_fp)(int objhandle, char parent_ap);
OSIRISEXTERN Obj_UnattachChild_fp Obj_UnattachChild;

//	void Obj_UnattachChildren(int objhandle);
//	Detaches all children from a parent
typedef void (*Obj_UnattachChildren_fp)(int objhandle);
OSIRISEXTERN Obj_UnattachChildren_fp Obj_UnattachChildren;

//	int FVI_RayCast(int objhandle,vector *p0,vector *p1,int start_roomnum,float rad,int flags,ray_info *ri);
//	Shoots out a ray, returns it's fate
typedef int (*FVI_RayCast_fp)(int objhandle, vector *p0, vector *p1, int start_roomnum, float rad, int flags,
                              ray_info *ri);
OSIRISEXTERN FVI_RayCast_fp FVI_RayCast;

//	int AI_GetPathID(char *string);
//	searches through GamePath index and returns index of path matching name returns -1 if not found
typedef int (*AI_GetPathID_fp)(char *string);
OSIRISEXTERN AI_GetPathID_fp AI_GetPathID;

//	int AI_GoalFollowPathSimple(int objhandle,int path_id,int guid,int flags);
typedef int (*AI_GoalFollowPathSimple_fp)(int objhandle, int path_id, int guid, int flags, int slot);
OSIRISEXTERN AI_GoalFollowPathSimple_fp AI_GoalFollowPathSimpleFP;
static inline int AI_GoalFollowPathSimple(int objhandle, int path_id, int guid, int flags, int slot = 3) {
  return AI_GoalFollowPathSimpleFP(objhandle, path_id, guid, flags, slot);
}

//	int AI_PowerSwitch(int objhandle,uint8_t f_power_on);
typedef int (*AI_PowerSwitch_fp)(int objhandle, uint8_t f_power_on);
OSIRISEXTERN AI_PowerSwitch_fp AI_PowerSwitch;

//	void AI_Value(int objhandle, char op, char vtype, void *ptr);
typedef void (*AI_Value_fp)(int objhandle, char op, char vtype, void *ptr);
OSIRISEXTERN AI_Value_fp AI_Value;

//	void Obj_Value(int objhandle, char op, char vtype, void *ptr);
typedef void (*Obj_Value_fp)(int objhandle, char op, char vtype, void *ptr, int index);
OSIRISEXTERN Obj_Value_fp Obj_ValueFP;

static inline void Obj_Value(int objhandle, char op, char vtype, void *ptr, int index = 0) {
  Obj_ValueFP(objhandle, op, vtype, ptr, index);
}

//	void Matcen_Value(int matcen_handle, char op, char vtype, void *ptr, int prod_index = 0);
typedef void (*Matcen_Value_fp)(int matcen_handle, char op, char vtype, void *ptr, int prod_index);
OSIRISEXTERN Matcen_Value_fp Matcen_ValueFP;
static inline void Matcen_Value(int matcen_handle, char op, char vtype, void *ptr, int prod_index = 0) {
  Matcen_ValueFP(matcen_handle, op, vtype, ptr, prod_index);
}

//	uint8_t AI_TurnTowardsVectors(int objhandle,vector *fvec,vector *uvec);
typedef uint8_t (*AI_TurnTowardsVectors_fp)(int objhandle, vector *fvec, vector *uvec);
OSIRISEXTERN AI_TurnTowardsVectors_fp AI_TurnTowardsVectors;

//	void AI_SetType(int objhandle,int type);
typedef void (*AI_SetType_fp)(int objhandle, int type);
OSIRISEXTERN AI_SetType_fp AI_SetType;

//	vector AI_FindHidePos(int hideobjhandle,int viewobjhandle,float time,int *hide_room);
typedef vector (*AI_FindHidePos_fp)(int hideobjhandle, int viewobjhandle, float time, int *hide_room);
OSIRISEXTERN AI_FindHidePos_fp AI_FindHidePos;

//	int AI_GoalAddEnabler(int objhandle,int goal_index,int enabler_type,float percent,float interval,void *ptr);
typedef int (*AI_GoalAddEnabler_fp)(int objhandle, int goal_index, int enabler_type, float percent, float interval,
                                    void *ptr);
OSIRISEXTERN AI_GoalAddEnabler_fp AI_GoalAddEnabler;

//	int AI_AddGoal(int objhandle,int goal_type,int level,float influence, int guid, int flags, ... );
typedef float (*AI_AddGoal_fp)(int objhandle, int goal_type, int level, float influence, int guid, int flags, ...);
OSIRISEXTERN AI_AddGoal_fp AI_AddGoal;

//	void AI_ClearGoal(int objhandle,int goal_index);
typedef void (*AI_ClearGoal_fp)(int objhandle, int goal_index);
OSIRISEXTERN AI_ClearGoal_fp AI_ClearGoal;

//	int AI_FindObjOfType(int objhandle,int type, bool f_ignore_init_room, int parent_handle = OBJECT_HANDLE_NONE);
typedef int (*AI_FindObjOfType_fp)(int objhandle, int type, int id, bool f_ignore_init_room, int parent_handle);
OSIRISEXTERN AI_FindObjOfType_fp AI_FindObjOfTypeFP;
static inline int AI_FindObjOfType(int objhandle, int type, int id, bool f_ignore_init_room,
                                   int parent_handle = OBJECT_HANDLE_NONE) {
  return AI_FindObjOfTypeFP(objhandle, type, id, f_ignore_init_room, parent_handle);
}
//	vector AI_GetRoomPathPoint(int roomnum);
typedef vector (*AI_GetRoomPathPoint_fp)(int roomnum);
OSIRISEXTERN AI_GetRoomPathPoint_fp AI_GetRoomPathPoint;

//	int AI_FindEnergyCenter(int objhandle);
typedef int (*AI_FindEnergyCenter_fp)(int objhandle);
OSIRISEXTERN AI_FindEnergyCenter_fp AI_FindEnergyCenter;

//	float AI_GetDistToObj(int objhandle,int otherobjhandle);
typedef float (*AI_GetDistToObj_fp)(int objhandle, int otherobjhandle);
OSIRISEXTERN AI_GetDistToObj_fp AI_GetDistToObj;

//	int AI_SetGoalFlags(int objhandle,int goal_handle,int flags,uint8_t f_enable);
typedef int (*AI_SetGoalFlags_fp)(int objhandle, int goal_handle, int flags, uint8_t f_enable);
OSIRISEXTERN AI_SetGoalFlags_fp AI_SetGoalFlags;

//	void AI_SetGoalCircleDist(int objhandle,int goal_handle,float dist);
typedef void (*AI_SetGoalCircleDist_fp)(int objhandle, int goal_handle, float dist);
OSIRISEXTERN AI_SetGoalCircleDist_fp AI_SetGoalCircleDist;

//	int File_ReadBytes(uint8_t *buffer, int count, void *fileptr);
// Reads the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO READ STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes read.
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int (*File_ReadBytes_fp)(uint8_t *buffer, int count, void *fileptr);
OSIRISEXTERN File_ReadBytes_fp File_ReadBytes;

//	int File_ReadInt(void *fileptr);
// The following functions read numeric vales from a CFILE.  All values are
// stored in the file in Intel (little-endian) format.  These functions
// will convert to big-endian if required.
// These funtions will throw an exception of if the value cannot be read,
// so do not call these if you don't require the data to be present.

// Read and return an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int (*File_ReadInt_fp)(void *fileptr);
OSIRISEXTERN File_ReadInt_fp File_ReadInt;

//	int16_t File_ReadShort(void *fileptr);
// Read and return a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int16_t (*File_ReadShort_fp)(void *fileptr);
OSIRISEXTERN File_ReadShort_fp File_ReadShort;

//	int8_t File_ReadByte(void *fileptr);
// Read and return a byte (8 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef int8_t (*File_ReadByte_fp)(void *fileptr);
OSIRISEXTERN File_ReadByte_fp File_ReadByte;

//	float File_ReadFloat(void *fileptr);
// Read and return a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef float (*File_ReadFloat_fp)(void *fileptr);
OSIRISEXTERN File_ReadFloat_fp File_ReadFloat;

//	double File_ReadDouble(void *fileptr);
// Read and return a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
typedef double (*File_ReadDouble_fp)(void *fileptr);
OSIRISEXTERN File_ReadDouble_fp File_ReadDouble;

//	int File_ReadString(char *buf,size_t n,void *fileptr);
// Reads a string from a CFILE.  If the file is type binary, this
// function reads until a NULL or EOF is found.  If the file is text,
// the function reads until a newline or EOF is found.  The string is always
// written to the destination buffer null-terminated, without the newline.
// Parameters:  buf - where the string is written
//					n - the maximum string length, including the terminating 0
//					cfp - the CFILE pointer
// Returns the number of bytes in the string, before the terminator
// Does not generate an exception on EOF
typedef int (*File_ReadString_fp)(char *buf, size_t n, void *fileptr);
OSIRISEXTERN File_ReadString_fp File_ReadString;

//	int File_WriteBytes(const uint8_t *buf,int count,void *fileptr);
// Writes the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO WRITE STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes written.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef int (*File_WriteBytes_fp)(const uint8_t *buf, int count, void *fileptr);
OSIRISEXTERN File_WriteBytes_fp File_WriteBytes;

//	int File_WriteString(const char *buf,void *fileptr);
// Writes a null-terminated string to a file.  If the file is type binary,
// the string is terminated in the file with a null.  If the file is type
// text, the string is terminated with a newline.
// Parameters:	buf - pointer to the string
//					cfp = the CFILE pointer
// Returns the number of bytes written
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef int (*File_WriteString_fp)(const char *buf, void *fileptr);
OSIRISEXTERN File_WriteString_fp File_WriteString;

//	void File_WriteInt(int i,void *fileptr);
// The following functions write numeric vales to a CFILE.  All values are
// stored to the file in Intel (little-endian) format.
// All these throw an exception if there's an error on write.

// Write an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*File_WriteInt_fp)(int i, void *fileptr);
OSIRISEXTERN File_WriteInt_fp File_WriteInt;

//	void File_WriteShort(int16_t s,void *fileptr);
// Write a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*File_WriteShort_fp)(int16_t s, void *fileptr);
OSIRISEXTERN File_WriteShort_fp File_WriteShort;

//	void File_WriteByte(int8_t b,void *fileptr);
// Write a byte (8 bits).  If the byte is a newline & the file is a text file, writes a CR/LF pair.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*File_WriteByte_fp)(int8_t b, void *fileptr);
OSIRISEXTERN File_WriteByte_fp File_WriteByte;

//	void File_WriteFloat(float f,void *fileptr);
// Write a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*File_WriteFloat_fp)(float f, void *fileptr);
OSIRISEXTERN File_WriteFloat_fp File_WriteFloat;

//	void File_WriteDouble(double d,void *fileptr);
// Write a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
typedef void (*File_WriteDouble_fp)(double d, void *fileptr);
OSIRISEXTERN File_WriteDouble_fp File_WriteDouble;

//	void *Scrpt_MemAlloc(tOSIRISMEMCHUNK *mem_info);
//		Allocates a chunk of memory to be associated with a script.  It will automatically
//	save this memory to disk on game save, and will pass the pointer to this memory on EVT_MEMRESTORE
typedef void *(*Scrpt_MemAlloc_fp)(tOSIRISMEMCHUNK *mem_info);
OSIRISEXTERN Scrpt_MemAlloc_fp Scrpt_MemAlloc;

//	void Scrpt_MemFree(void *memory_ptr);
//		Frees a chunk of memory that was allocated by Scrpt_MemAlloc().
typedef void (*Scrpt_MemFree_fp)(void *memory_ptr);
OSIRISEXTERN Scrpt_MemFree_fp Scrpt_MemFree;

//	void Scrpt_CancelTimer(int timer_id);
//		Cancels a timer thats in use, given it's ID
typedef void (*Scrpt_CancelTimer_fp)(int timer_id);
OSIRISEXTERN Scrpt_CancelTimer_fp Scrpt_CancelTimer;

//	int Scrpt_CreateTimer(tOSIRISTIMER *timer_info);
//		Adds a timer to the list to be processed.  You'll receive a EVT_TIMER when the timer is signaled.
//	Returns an id to the timer, which can be used to cancel a timer. -1 on error.
typedef int (*Scrpt_CreateTimer_fp)(tOSIRISTIMER *timer_info);
OSIRISEXTERN Scrpt_CreateTimer_fp Scrpt_CreateTimer;

//	void MSafe_DoPowerup (msafe_struct *mstruct);
//	Does whatever magic needs to be done to get the default powerups to work
typedef void (*MSafe_DoPowerup_fp)(msafe_struct *mstruct);
OSIRISEXTERN MSafe_DoPowerup_fp MSafe_DoPowerup;

// int Obj_Create()(uint8_t type,uint16_t id,int roomnum,vector *pos,const matrix *orient,int parent_handle)
typedef int (*Obj_Create_fp)(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient, int parent_handle,
                             vector *initial_velocity);
OSIRISEXTERN Obj_Create_fp Obj_CreateFP;
static inline int Obj_Create(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient = NULL,
                             int parent_handle = 0, vector *initial_velocity = NULL) {
  return Obj_CreateFP(type, id, roomnum, pos, orient, parent_handle, initial_velocity);
}
// float Game_GetTime() (void)
typedef float (*Game_GetTime_fp)(void);
OSIRISEXTERN Game_GetTime_fp Game_GetTime;

// float Game_GetFrameTime() (void)
typedef float (*Game_GetFrameTime_fp)(void);
OSIRISEXTERN Game_GetFrameTime_fp Game_GetFrameTime;

// void Obj_WBValue() (int obj_handle, char wb_index, char op, char vtype, void *ptr, char g_index)
typedef void (*Obj_WBValue_fp)(int obj_handle, char wb_index, char op, char vtype, void *ptr, char g_index);
OSIRISEXTERN Obj_WBValue_fp Obj_WBValueFP;
static inline void Obj_WBValue(int obj_handle, char wb_index, char op, char vtype, void *ptr, char g_index = 0) {
  Obj_WBValueFP(obj_handle, wb_index, op, vtype, ptr, g_index);
}

// uint8_t Scrpt_TimerExists(int handle);
typedef uint8_t (*Scrpt_TimerExists_fp)(int handle);
OSIRISEXTERN Scrpt_TimerExists_fp Scrpt_TimerExists;

typedef void (*Matcen_Reset_fp)(int handle);
OSIRISEXTERN Matcen_Reset_fp Matcen_Reset;

typedef void (*Matcen_Copy_fp)(int dhandle, int shandle);
OSIRISEXTERN Matcen_Copy_fp Matcen_Copy;

typedef int (*Matcen_Create_fp)(char *name);
OSIRISEXTERN Matcen_Create_fp Matcen_Create;

typedef int (*Matcen_FindID_fp)(char *str);
OSIRISEXTERN Matcen_FindID_fp Matcen_FindID;

//	void Msn_FlagSet(int flag,uint8_t value);
//	Sets/Clears mission flags. flag is which mission flag to set/clear (1-32)
//	value is 0 to clear, or 1 to set
typedef void (*Msn_FlagSet_fp)(int flag, uint8_t value);
OSIRISEXTERN Msn_FlagSet_fp Msn_FlagSet;

//	int Msn_FlagGet(int flag);
//	Gets a mission flag. flag is what mission flag to get.  Returns 1 if set, 0 if not.
typedef int (*Msn_FlagGet_fp)(int flag);
OSIRISEXTERN Msn_FlagGet_fp Msn_FlagGet;

typedef void (*Player_Value_fp)(int obj_handle, char op, char vhandle, void *ptr, int index);
OSIRISEXTERN Player_Value_fp Player_ValueFP;
static inline void Player_Value(int obj_handle, char op, char vhandle, void *ptr, int index = 0) {
  Player_ValueFP(obj_handle, op, vhandle, ptr, index);
}

typedef void (*Obj_SetCustomAnim_fp)(int handle, float start, float end, float time, char flags, int sound_handle,
                                     char next_anim_type);
OSIRISEXTERN Obj_SetCustomAnim_fp Obj_SetCustomAnimFP;
static inline void Obj_SetCustomAnim(int handle, float start, float end, float time, char flags, int sound_handle = -1,
                                     char next_anim_type = -1) {
  Obj_SetCustomAnimFP(handle, start, end, time, flags, sound_handle, next_anim_type);
}

typedef void (*Player_AddHudMessage_fp)(int handle, const char *str);
OSIRISEXTERN Player_AddHudMessage_fp Player_AddHudMessage;

typedef void (*Obj_Ghost_fp)(int handle, bool f_ghost);
OSIRISEXTERN Obj_Ghost_fp Obj_Ghost;

typedef void (*Obj_Burning_fp)(int handle, float time, float damage_per_second);
OSIRISEXTERN Obj_Burning_fp Obj_BurningFP;
static inline void Obj_Burning(int handle, float time, float damage_per_second = 1.0f) {
  Obj_BurningFP(handle, time, damage_per_second);
}

typedef bool (*Obj_IsEffect_fp)(int handle, int type_flag);
OSIRISEXTERN Obj_IsEffect_fp Obj_IsEffect;

//	opens a cfile for reading/writing (works just like fopen())
typedef void *(*File_Open_fp)(const char *filename, const char *mode);
OSIRISEXTERN File_Open_fp File_Open;

//	closes a cfile (like fclose())
typedef void (*File_Close_fp)(void *fileptr);
OSIRISEXTERN File_Close_fp File_Close;

//	returns the current position of the file (like ftell())
typedef int (*File_Tell_fp)(void *fileptr);
OSIRISEXTERN File_Tell_fp File_Tell;

//	returns 1 if the file is at the EOF, else 0 (like feof())
typedef uint8_t (*File_eof_fp)(void *fileptr);
OSIRISEXTERN File_eof_fp File_eof;

typedef void (*Sound_Stop_fp)(int s_handle, bool f_immediately);
OSIRISEXTERN Sound_Stop_fp Sound_StopFP;
static inline void Sound_Stop(int s_handle, bool f_immediately = true) { Sound_StopFP(s_handle, f_immediately); }

typedef int (*Sound_Play2d_fp)(int obj_handle, int s_id, float volume);
OSIRISEXTERN Sound_Play2d_fp Sound_Play2dFP;
static inline int Sound_Play2d(int obj_handle, int s_id, float volume = 1.0f) {
  return Sound_Play2dFP(obj_handle, s_id, volume);
}

typedef int (*Sound_Play3d_fp)(int obj_handle, int s_id, float volume);
OSIRISEXTERN Sound_Play3d_fp Sound_Play3dFP;
static inline int Sound_Play3d(int obj_handle, int s_id, float volume = 1.0f) {
  return Sound_Play3dFP(obj_handle, s_id, volume);
}

typedef int (*Sound_FindId_fp)(const char *s_name);
OSIRISEXTERN Sound_FindId_fp Sound_FindId;

typedef bool (*AI_IsObjFriend_fp)(int obj_handle, int it_handle);
OSIRISEXTERN AI_IsObjFriend_fp AI_IsObjFriend;

typedef bool (*AI_IsObjEnemy_fp)(int obj_handle, int it_handle);
OSIRISEXTERN AI_IsObjEnemy_fp AI_IsObjEnemy;

typedef bool (*AI_GoalValue_fp)(int obj_handle, char g_index, char op, char vtype, void *ptr, char index);
OSIRISEXTERN AI_GoalValue_fp AI_GoalValueFP;
static inline bool AI_GoalValue(int obj_handle, char g_index, char op, char vtype, void *ptr, char index = 0) {
  return AI_GoalValueFP(obj_handle, g_index, op, vtype, ptr, index);
}

typedef int (*AI_GetNearbyObjs_fp)(vector *pos, int init_roomnum, float rad, int *object_handle_list, int max_elements,
                                   bool f_lightmap_only, bool f_only_players_and_ais,
                                   bool f_include_non_collide_objects, bool f_stop_at_closed_doors);
OSIRISEXTERN AI_GetNearbyObjs_fp AI_GetNearbyObjsFP;
static inline int AI_GetNearbyObjs(vector *pos, int init_roomnum, float rad, int *object_handle_list, int max_elements,
                                   bool f_lightmap_only, bool f_only_players_and_ais = true,
                                   bool f_include_non_collide_objects = false, bool f_stop_at_closed_doors = true) {
  return AI_GetNearbyObjsFP(pos, init_roomnum, rad, object_handle_list, max_elements, f_lightmap_only,
                            f_only_players_and_ais, f_include_non_collide_objects, f_stop_at_closed_doors);
}

typedef char (*AI_GetCurGoalIndex_fp)(int obj_handle);
OSIRISEXTERN AI_GetCurGoalIndex_fp AI_GetCurGoalIndex;

// Allocates a block of global memory for this module, of size amount_of_memory.
// unique_identfier is the script provided unique ID which is used throughout.
// script_identifier is the pointer of data provided to the script in it's InitializeDLL function (really the name of
// the script) Returns -1 if there isn't enough available memory Returns -2 if the unique identifier passed in is
// already used, but the requested amount_of_memory is different If the memory has already been allocated, it will
// return the handle.
typedef OMMSHANDLE (*OMMS_Malloc_fp)(size_t amount_of_memory, uint32_t unique_identifier, char *script_identifier);
OSIRISEXTERN OMMS_Malloc_fp OMMS_Malloc;

//	Attaches to a block of global OMMS memory.  As long as at least one module (or script) is
//	attached to a module, the memory will not be deleted. (Increments the reference count)
//	Returns NULL if the memory couldn't be attached (it has been either free'd or never malloced)
typedef void *(*OMMS_Attach_fp)(OMMSHANDLE handle);
OSIRISEXTERN OMMS_Attach_fp OMMS_Attach;

//	Detaches a block of global OMMS memory. (Reduces the reference count).
typedef void (*OMMS_Detach_fp)(OMMSHANDLE handle);
OSIRISEXTERN OMMS_Detach_fp OMMS_Detach;

//	Frees a block of global memory
//	Only has affect if you are attached to the memory.  Memory will _ONLY_ be deleted when the
//	following conditions are meant for the shared memory block:
//	1) The reference count for the global memory is at 0 (OMMS_Attach() adds to reference count, OMMS_Detach()
// subtracts). 	2) OMMS_Free() has been called for the block of global memory. 	The conditions can happen in any order,
// but
// as soon as both are satisfied, the memory 	becomes deleted and any pointer returned by OMMS_Attach() becomes
// invalid.
//
//	handle : the value returned by OMMS_Malloc()
typedef void (*OMMS_Free_fp)(OMMSHANDLE handle);
OSIRISEXTERN OMMS_Free_fp OMMS_Free;

//	Returns an OMMSHANDLE to a block of global memory allocated by a module/script.  Pass
//	in the unique_identifier and the script_identifier that was passed in the OMMS_Malloc().
//	Note: script_identifier is really the filename of the module that called the OMMS_Malloc().
//	Returns -1 if the module was never OMMS_Malloc()'d.
typedef OMMSHANDLE (*OMMS_Find_fp)(uint32_t unique_identifier, char *script_identifier);
OSIRISEXTERN OMMS_Find_fp OMMS_Find;

//	Returns information about the OMMS memory given it's handle returned from the OMMS_Find() or
//	OMMS_Malloc(). Returns 0 if the handle was invalid, 1 if the information has been filled in;
//	Pass NULL in for those parameters you don't need information about.
typedef char (*OMMS_GetInfo_fp)(OMMSHANDLE handle, uint32_t *mem_size, uint32_t *uid, uint16_t *reference_count,
                                uint8_t *has_free_been_called);
OSIRISEXTERN OMMS_GetInfo_fp OMMS_GetInfo;

//	Starts an in-game cinematic sequence.  text_string is the text to be displayed
//	use pipes (|) to seperate lines.
typedef bool (*Cine_Start_fp)(tGameCinematic *info, const char *text_string);
OSIRISEXTERN Cine_Start_fp Cine_Start;

//	Stops and clears up a in-game cinematic.
typedef void (*Cine_Stop_fp)(void);
OSIRISEXTERN Cine_Stop_fp Cine_Stop;

// Looks up the id's of the sound, room, trigger, object, ect. based on the name
typedef int (*Scrpt_FindSoundName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindSoundName_fp Scrpt_FindSoundName;

typedef int (*Scrpt_FindRoomName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindRoomName_fp Scrpt_FindRoomName;

typedef int (*Scrpt_FindTriggerName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindTriggerName_fp Scrpt_FindTriggerName;

typedef int (*Scrpt_FindObjectName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindObjectName_fp Scrpt_FindObjectName;

typedef int (*Scrpt_GetTriggerRoom_fp)(int trigger_id);
OSIRISEXTERN Scrpt_GetTriggerRoom_fp Scrpt_GetTriggerRoom;

typedef int (*Scrpt_GetTriggerFace_fp)(int trigger_id);
OSIRISEXTERN Scrpt_GetTriggerFace_fp Scrpt_GetTriggerFace;

typedef int (*Scrpt_FindDoorName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindDoorName_fp Scrpt_FindDoorName;

typedef int (*Scrpt_FindTextureName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindTextureName_fp Scrpt_FindTextureName;

typedef void (*Game_CreateRandomSparks_fp)(int num_sparks, vector *pos, int roomnum, int which_index,
                                           float force_scalar);
OSIRISEXTERN Game_CreateRandomSparks_fp Game_CreateRandomSparksFP;
static inline void Game_CreateRandomSparks(int num_sparks, vector *pos, int roomnum, int which_index = -1,
                                           float force_scalar = 1.0f) {
  return Game_CreateRandomSparksFP(num_sparks, pos, roomnum, which_index, force_scalar);
}

//		Cancels a timer given its ID
typedef void (*Scrpt_CancelTimerID_fp)(int id);
OSIRISEXTERN Scrpt_CancelTimerID_fp Scrpt_CancelTimerID;

// disable/enable ship
typedef void (*Game_EnableShip_fp)(const char *ship_name, bool enable);
OSIRISEXTERN Game_EnableShip_fp Game_EnableShip;

// is ship enabled
typedef bool (*Game_IsShipEnabled_fp)(const char *ship_name);
OSIRISEXTERN Game_IsShipEnabled_fp Game_IsShipEnabled;

// gets information about a path point
// pass NULL for parameters not needed.
//	pathid: path number
//	point: which path point
// returns true if operation was successful
typedef bool (*Path_GetInformation_fp)(int pathid, int point, vector *pos, int *room, matrix *orient);
OSIRISEXTERN Path_GetInformation_fp Path_GetInformationFP;
static inline bool Path_GetInformation(int pathid, int point, vector *pos = NULL, int *room = NULL,
                                       matrix *orient = NULL) {
  return Path_GetInformationFP(pathid, point, pos, room, orient);
}
// starts a canned cinematic sequence
typedef void (*Cine_StartCanned_fp)(tCannedCinematicInfo *info);
OSIRISEXTERN Cine_StartCanned_fp Cine_StartCanned;

typedef int (*Scrpt_FindMatcenName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindMatcenName_fp Scrpt_FindMatcenName;

typedef int (*Scrpt_FindPathName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindPathName_fp Scrpt_FindPathName;

typedef int (*Scrpt_FindLevelGoalName_fp)(const char *name);
OSIRISEXTERN Scrpt_FindLevelGoalName_fp Scrpt_FindLevelGoalName;

typedef void (*LGoal_Value_fp)(char op, char vtype, void *ptr, int g_index, int i_index);
OSIRISEXTERN LGoal_Value_fp LGoal_ValueFP;
static inline void LGoal_Value(char op, char vtype, void *ptr, int g_index = -1, int i_index = -1) {
  LGoal_ValueFP(op, vtype, ptr, g_index, i_index);
}

typedef int (*Obj_MakeListOfType_fp)(int objhandle, int type, int id, bool f_ignore_init_room, int parent_handle,
                                     int max_recorded, int *handles);
OSIRISEXTERN Obj_MakeListOfType_fp Obj_MakeListOfType;

typedef void (*Obj_Kill_fp)(int handle, int killer_handle, float damage, int flags, float min_time, float max_time);
OSIRISEXTERN Obj_Kill_fp Obj_Kill;

// typedef bool (*AI_AreRoomsReachable_fp)(int room1, int room2);
// OSIRISEXTERN AI_AreRoomsReachable_fp AI_AreRoomsReachable;

typedef bool (*AI_IsDestReachable_fp)(int handle, int room);
OSIRISEXTERN AI_IsDestReachable_fp AI_IsDestReachable;

typedef bool (*AI_IsObjReachable_fp)(int handle, int target);
OSIRISEXTERN AI_IsObjReachable_fp AI_IsObjReachable;

typedef char (*Game_GetDiffLevel_fp)(void);
OSIRISEXTERN Game_GetDiffLevel_fp Game_GetDiffLevel;

/*
0:LANGUAGE_ENGLISH
1:LANGUAGE_GERMAN
2:LANGUAGE_SPANISH
3:LANGUAGE_ITALIAN
4:LANGUAGE_FRENCH
*/
typedef int (*Game_GetLanguage_fp)(void);
OSIRISEXTERN Game_GetLanguage_fp Game_GetLanguage;

// Sets/Gets information about a path.
// If you change is PV_ALL (or any of it's individual components), pass in a pointer to an
// osiris_path_node_info struct.  For the others, you must pass in an appropriate pointer
// (i.e. an int* for PV_I_NUMNODES).  You can only set PV_ALL components.
//	for PV_I_NUMNODES, path_id MUST be specified, node_id is ignored
//	for PV_I_NUMPATHS, path_id and node_id are ignored
//	for PV_CS_NAME, path_id MUST be specified, node_id is ignored
//	for PV_ALL components, path_id and node_id MUST be valid.
typedef void (*Path_Value_fp)(int path_id, int node_id, char op, int changes, void *ptr);
OSIRISEXTERN Path_Value_fp Path_Value;

// ===========================================================

//	osicommon_Initialize
//	Initializes module's functions
void osicommon_Initialize(tOSIRISModuleInit *mi);
#ifndef __OSIRIS_IMPORT_H_
void osicommon_Initialize(tOSIRISModuleInit *mi) {
  int i = 0;
  mprintf = (mprintf_fp)mi->fp[i++];
  MSafe_CallFunction = (MSafe_CallFunction_fp)mi->fp[i++];
  MSafe_GetValue = (MSafe_GetValue_fp)mi->fp[i++];
  Obj_CallEvent = (Obj_CallEvent_fp)mi->fp[i++];
  Trgr_CallEvent = (Trgr_CallEvent_fp)mi->fp[i++];
  Sound_TouchFile = (Sound_TouchFile_fp)mi->fp[i++];
  Obj_FindID = (Obj_FindID_fp)mi->fp[i++];
  Wpn_FindID = (Wpn_FindID_fp)mi->fp[i++];
  Obj_GetTimeLived = (Obj_GetTimeLived_fp)mi->fp[i++];
  Obj_GetGunPosFP = (Obj_GetGunPos_fp)mi->fp[i++];
  Room_ValueFP = (Room_Value_fp)mi->fp[i++];
  Room_IsValid = (Room_IsValid_fp)mi->fp[i++];
  Obj_GetAttachParent = (Obj_GetAttachParent_fp)mi->fp[i++];
  Obj_GetNumAttachSlots = (Obj_GetNumAttachSlots_fp)mi->fp[i++];
  Obj_GetAttachChildHandle = (Obj_GetAttachChildHandle_fp)mi->fp[i++];
  Obj_AttachObjectAP = (Obj_AttachObjectAP_fp)mi->fp[i++];
  Obj_AttachObjectRad = (Obj_AttachObjectRad_fp)mi->fp[i++];
  Obj_UnattachFromParent = (Obj_UnattachFromParent_fp)mi->fp[i++];
  Obj_UnattachChild = (Obj_UnattachChild_fp)mi->fp[i++];
  Obj_UnattachChildren = (Obj_UnattachChildren_fp)mi->fp[i++];
  FVI_RayCast = (FVI_RayCast_fp)mi->fp[i++];
  AI_GetPathID = (AI_GetPathID_fp)mi->fp[i++];
  AI_GoalFollowPathSimpleFP = (AI_GoalFollowPathSimple_fp)mi->fp[i++];
  AI_PowerSwitch = (AI_PowerSwitch_fp)mi->fp[i++];
  AI_TurnTowardsVectors = (AI_TurnTowardsVectors_fp)mi->fp[i++];
  AI_SetType = (AI_SetType_fp)mi->fp[i++];
  AI_FindHidePos = (AI_FindHidePos_fp)mi->fp[i++];
  AI_GoalAddEnabler = (AI_GoalAddEnabler_fp)mi->fp[i++];
  AI_AddGoal = (AI_AddGoal_fp)mi->fp[i++];
  AI_ClearGoal = (AI_ClearGoal_fp)mi->fp[i++];
  AI_Value = (AI_Value_fp)mi->fp[i++];
  AI_FindObjOfTypeFP = (AI_FindObjOfType_fp)mi->fp[i++];
  AI_GetRoomPathPoint = (AI_GetRoomPathPoint_fp)mi->fp[i++];
  AI_FindEnergyCenter = (AI_FindEnergyCenter_fp)mi->fp[i++];
  AI_GetDistToObj = (AI_GetDistToObj_fp)mi->fp[i++];
  AI_SetGoalFlags = (AI_SetGoalFlags_fp)mi->fp[i++];
  AI_SetGoalCircleDist = (AI_SetGoalCircleDist_fp)mi->fp[i++];
  File_ReadBytes = (File_ReadBytes_fp)mi->fp[i++];
  File_ReadInt = (File_ReadInt_fp)mi->fp[i++];
  File_ReadShort = (File_ReadShort_fp)mi->fp[i++];
  File_ReadByte = (File_ReadByte_fp)mi->fp[i++];
  File_ReadFloat = (File_ReadFloat_fp)mi->fp[i++];
  File_ReadDouble = (File_ReadDouble_fp)mi->fp[i++];
  File_ReadString = (File_ReadString_fp)mi->fp[i++];
  File_WriteBytes = (File_WriteBytes_fp)mi->fp[i++];
  File_WriteString = (File_WriteString_fp)mi->fp[i++];
  File_WriteInt = (File_WriteInt_fp)mi->fp[i++];
  File_WriteShort = (File_WriteShort_fp)mi->fp[i++];
  File_WriteByte = (File_WriteByte_fp)mi->fp[i++];
  File_WriteFloat = (File_WriteFloat_fp)mi->fp[i++];
  File_WriteDouble = (File_WriteDouble_fp)mi->fp[i++];
  Scrpt_MemAlloc = (Scrpt_MemAlloc_fp)mi->fp[i++];
  Scrpt_MemFree = (Scrpt_MemFree_fp)mi->fp[i++];
  Scrpt_CancelTimer = (Scrpt_CancelTimer_fp)mi->fp[i++];
  Scrpt_CreateTimer = (Scrpt_CreateTimer_fp)mi->fp[i++];
  MSafe_DoPowerup = (MSafe_DoPowerup_fp)mi->fp[i++];
  Obj_CreateFP = (Obj_Create_fp)mi->fp[i++];
  Game_GetTime = (Game_GetTime_fp)mi->fp[i++];
  Game_GetFrameTime = (Game_GetFrameTime_fp)mi->fp[i++];
  Obj_WBValueFP = (Obj_WBValue_fp)mi->fp[i++];
  Scrpt_TimerExists = (Scrpt_TimerExists_fp)mi->fp[i++];
  Obj_ValueFP = (Obj_Value_fp)mi->fp[i++];
  Matcen_ValueFP = (Matcen_Value_fp)mi->fp[i++];
  Matcen_Reset = (Matcen_Reset_fp)mi->fp[i++];
  Matcen_Copy = (Matcen_Copy_fp)mi->fp[i++];
  Matcen_Create = (Matcen_Create_fp)mi->fp[i++];
  Matcen_FindID = (Matcen_FindID_fp)mi->fp[i++];
  Msn_FlagSet = (Msn_FlagSet_fp)mi->fp[i++];
  Msn_FlagGet = (Msn_FlagGet_fp)mi->fp[i++];
  Player_ValueFP = (Player_Value_fp)mi->fp[i++];
  Obj_SetCustomAnimFP = (Obj_SetCustomAnim_fp)mi->fp[i++];
  Player_AddHudMessage = (Player_AddHudMessage_fp)mi->fp[i++];
  Obj_Ghost = (Obj_Ghost_fp)mi->fp[i++];
  Obj_BurningFP = (Obj_Burning_fp)mi->fp[i++];
  Obj_IsEffect = (Obj_IsEffect_fp)mi->fp[i++];
  File_Open = (File_Open_fp)mi->fp[i++];
  File_Close = (File_Close_fp)mi->fp[i++];
  File_Tell = (File_Tell_fp)mi->fp[i++];
  File_eof = (File_eof_fp)mi->fp[i++];
  Sound_StopFP = (Sound_Stop_fp)mi->fp[i++];
  Sound_Play2dFP = (Sound_Play2d_fp)mi->fp[i++];
  Sound_Play3dFP = (Sound_Play3d_fp)mi->fp[i++];
  Sound_FindId = (Sound_FindId_fp)mi->fp[i++];
  AI_IsObjFriend = (AI_IsObjFriend_fp)mi->fp[i++];
  AI_IsObjEnemy = (AI_IsObjEnemy_fp)mi->fp[i++];
  AI_GoalValueFP = (AI_GoalValue_fp)mi->fp[i++];
  AI_GetNearbyObjsFP = (AI_GetNearbyObjs_fp)mi->fp[i++];
  AI_GetCurGoalIndex = (AI_GetCurGoalIndex_fp)mi->fp[i++];
  OMMS_Malloc = (OMMS_Malloc_fp)mi->fp[i++];
  OMMS_Attach = (OMMS_Attach_fp)mi->fp[i++];
  OMMS_Detach = (OMMS_Detach_fp)mi->fp[i++];
  OMMS_Free = (OMMS_Free_fp)mi->fp[i++];
  OMMS_Find = (OMMS_Find_fp)mi->fp[i++];
  OMMS_GetInfo = (OMMS_GetInfo_fp)mi->fp[i++];
  Cine_Start = (Cine_Start_fp)mi->fp[i++];
  Cine_Stop = (Cine_Stop_fp)mi->fp[i++];
  Scrpt_FindSoundName = (Scrpt_FindSoundName_fp)mi->fp[i++];
  Scrpt_FindRoomName = (Scrpt_FindRoomName_fp)mi->fp[i++];
  Scrpt_FindTriggerName = (Scrpt_FindTriggerName_fp)mi->fp[i++];
  Scrpt_FindObjectName = (Scrpt_FindObjectName_fp)mi->fp[i++];
  Scrpt_GetTriggerRoom = (Scrpt_GetTriggerRoom_fp)mi->fp[i++];
  Scrpt_GetTriggerFace = (Scrpt_GetTriggerFace_fp)mi->fp[i++];
  Scrpt_FindDoorName = (Scrpt_FindDoorName_fp)mi->fp[i++];
  Scrpt_FindTextureName = (Scrpt_FindTextureName_fp)mi->fp[i++];
  Game_CreateRandomSparksFP = (Game_CreateRandomSparks_fp)mi->fp[i++];
  Scrpt_CancelTimerID = (Scrpt_CancelTimerID_fp)mi->fp[i++];
  Obj_GetGroundPosFP = (Obj_GetGroundPos_fp)mi->fp[i++];
  Game_EnableShip = (Game_EnableShip_fp)mi->fp[i++];
  Game_IsShipEnabled = (Game_IsShipEnabled_fp)mi->fp[i++];
  Path_GetInformationFP = (Path_GetInformation_fp)mi->fp[i++];
  Cine_StartCanned = (Cine_StartCanned_fp)mi->fp[i++];
  Scrpt_FindMatcenName = (Scrpt_FindMatcenName_fp)mi->fp[i++];
  Scrpt_FindPathName = (Scrpt_FindPathName_fp)mi->fp[i++];
  Scrpt_FindLevelGoalName = (Scrpt_FindLevelGoalName_fp)mi->fp[i++];
  Obj_FindType = (Obj_FindType_fp)mi->fp[i++];
  LGoal_ValueFP = (LGoal_Value_fp)mi->fp[i++];
  Obj_MakeListOfType = (Obj_MakeListOfType_fp)mi->fp[i++];
  Obj_Kill = (Obj_Kill_fp)mi->fp[i++];
  //	AI_AreRoomsReachable = (AI_AreRoomsReachable_fp)mi->fp[i++];
  AI_IsDestReachable = (AI_IsDestReachable_fp)mi->fp[i++];
  AI_IsObjReachable = (AI_IsObjReachable_fp)mi->fp[i++];
  Game_GetDiffLevel = (Game_GetDiffLevel_fp)mi->fp[i++];
  Game_GetLanguage = (Game_GetLanguage_fp)mi->fp[i++];
  Path_Value = (Path_Value_fp)mi->fp[i++];
}
#endif

#ifndef __OSIRIS_IMPORT_H_
#define __OSIRIS_IMPORT_H_
#endif
