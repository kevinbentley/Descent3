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

 * $Logfile: /DescentIII/Main/editor/Read3ds.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Code to read .p3d files generated in 3DS Max
 *
 * $Log: not supported by cvs2svn $
 *
 * 26    10/15/99 12:26p Matt
 * Added error checking for too many verts & faces when importing a room.
 * Also, now allow more than the max number of faces, as long as there is
 * a valid number after combining faces.
 *
 * 25    4/13/99 11:23a Jason
 * check for degenerate faces on import
 *
 * 24    2/25/99 10:35a Jason
 * added removal of redundant verts
 *
 * 23    2/04/99 4:40p Matt
 * Added some error checking
 *
 * 22    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 21    12/22/98 2:03p Matt
 * Added room names, and made rooms not compress so that room numbers are
 * suitable for persistant uses.
 *
 * 20    5/01/98 5:55p Jason
 * made combine faces much stricter
 *
 * 19    4/02/98 12:23p Jason
 * trimmed some fat from our structures
 *
 * 18    3/31/98 3:49p Jason
 * added memory lib
 *
 * 17    2/02/98 5:14p Matt
 * Check for bad normals when importing room
 *
 * 16    1/22/98 2:56p Brent
 * Define default textures to unassigned faces
 *
 * 15    1/19/98 2:55p Jason
 * added the ability to have the importer keep the textures on the faces
 * if they are already present in memory
 *
 * 14    12/23/97 11:06a Samir
 * Added pserror.h
 *
 * 13    12/10/97 5:20p Jason
 * set alphas to 1 when importing rooms
 *
 * 12    12/10/97 4:26p Jason
 * don't assign default UVs to room
 *
 * 11    8/21/97 5:57p Matt
 * Use new & modified functions from erooms.cpp
 *
 * 10    8/01/97 3:16p Chris
 *
 * 9     7/21/97 12:11p Matt
 * Fixed stupid bug in concavity check
 *
 * 8     7/21/97 11:39a Jason
 * checked in for matt to debug
 *
 * 7     7/17/97 11:13a Jason
 * fixed bug with reading in rooms - somehow it got broken
 *
 * 7     7/17/97 10:51a Jason
 * fixed bug with normals
 *
 * $NoKeywords: $
 */

#include "read3ds.h"
#include "cfile.h"
#include "room.h"
#include "erooms.h"
#include "gametexture.h"
#include "ddio.h"
#include "pserror.h"
#include <string.h>
#include <stdlib.h>
#include "mem.h"
#include "vecmat.h"

// 3ds MAX id's
#define ID_3DS_MODIFIED 0xbeef
#define ID_OBJ_PROPS 0xdead
#define ID_SPLINE_PATH 0x8001
#define ID_3DSM 0xcfd0
#define ID_3DS 0x4d4d
#define ID_OBJECT 0x4000
#define ID_UNKNOWN 0x3d3d
#define ID_TRI_MESH 0x4100
#define ID_VERTLIST 0x4110
#define ID_FACELIST 0x4120
#define ID_MAT_APP 0x4130
#define ID_VERTEX_MAPPING 0x4140
#define ID_SMOOTH 0x4150
#define ID_MATRIX 0x4160
#define ID_MATERIAL 0xafff
#define ID_MAT_NAME 0xa000
#define ID_MAT_DSIDED 0xa081
#define ID_MAT_DIFFUSE_COLOR 0xa020
#define ID_MAT_TEXTURE 0xa200
#define ID_DIRECT_LIGHT 0x4600
#define OBJECT_NODE_TAG 0xB002

char Reading_properties[255];

#define MAX_MATERIALS 100

struct material {
  char name[PAGENAME_LEN];
  int texhandle;
};

int Num_materials = 0;
material Materials[MAX_MATERIALS];

struct reading_face {
  uint8_t flags;                          // flags for this face (see above)
  int16_t portal_num;                     // which portal this face is part of, or -1 if none
  uint8_t num_verts;                      // how many vertices in this face
  int16_t face_verts[MAX_VERTS_PER_FACE]; // index into list of vertices for this face
  roomUVL face_uvls[MAX_VERTS_PER_FACE];  // index into list of uvls for this face
  vector normal;                          // the surface normal of this face
  int16_t tmap;                           // texture numbers for this face
};

struct reading_room {
  char name[PAGENAME_LEN];
  int flags;           // various room flags
  int num_faces;       // how many poygons in this room
  int num_portals;     // how many connections in this room
  int num_verts;       // how many verts in the room
  reading_face *faces; // pointer to list of faces
  vector *verts;       // array of vertices for this room
  int objects;         // index of first object in this room
  float static_light;  // the amount of light in this room
};

reading_room Reading_room; // the global that we use to keep a temp copy of the room while
                           // we're reading it in

int CombineFaces(reading_face *, reading_face *, reading_face *);

// Our nest level
int Nest_level = 0;

extern void AssignDefaultUVsToRoom(room *rp);

int DeleteUnusedRoomVerts(room *);
int RemoveDuplicatePoints(room *);
int RemoveDuplicateFacePoints(room *);

#define MAX_READING_ROOM_FACES (MAX_FACES_PER_ROOM * 2)

// Opens and reads a 3dsmax file for our rooms.  Allocs a room to carry the data
// Returns the index into the Rooms[] array if successful
// Return -1 on fail
int Read3DSMaxFile(char *filename) {
  uint16_t id;
  int len;
  CFILE *fp;
  int i;

  fp = (CFILE *)cfopen(filename, "rb");
  if (!fp) {
    mprintf(0, "Couldn't open 3dsmax file %s!\n", filename);
    return -1;
  }

  Nest_level = 0;

  // Alloc space for reading stuff in
  Reading_room.faces = (reading_face *)mem_malloc(MAX_READING_ROOM_FACES * sizeof(reading_face));
  Reading_room.verts = (vector *)mem_malloc(MAX_VERTS_PER_ROOM * sizeof(vector));

  Reading_room.num_faces = 0;
  Reading_room.num_verts = 0;

  id = cf_ReadShort(fp);
  len = cf_ReadInt(fp);

  Num_materials = 0;

  if (id == ID_3DS_MODIFIED)
    Parse3DSMaxChunk(fp, len - 6);
  else {
    mprintf(0, "This file is not a 3ds max file!\n");
    cfclose(fp);
    return -1;
  }
  cfclose(fp);

  if ((Reading_room.num_verts == 0) || (Reading_room.num_faces == 0)) {
    OutrageMessageBox("The imported room has %d verts and %d faces.  Aborting import.", Reading_room.num_faces,
                      Reading_room.num_faces);
    return -1;
  }

  if (Reading_room.num_verts > MAX_VERTS_PER_ROOM) {
    OutrageMessageBox("The imported room has %d verts.  The limit is %d.  Aborting import.", Reading_room.num_verts,
                      MAX_VERTS_PER_ROOM);
    return -1;
  }

  if (Reading_room.num_faces > MAX_READING_ROOM_FACES) {
    OutrageMessageBox("The imported room has %d faces.  The limit is %d.  Aborting import.", Reading_room.num_faces,
                      MAX_READING_ROOM_FACES);
    return -1;
  }

  if (Reading_room.num_faces > MAX_FACES_PER_ROOM) {
    OutrageMessageBox("The imported room has %d faces.  The limit after combining faces is %d.\n\nIf there are too "
                      "many faces after combining, this room will not be imported.",
                      Reading_room.num_faces, MAX_FACES_PER_ROOM);
  }

  // Convert our points to left handed space
  for (i = 0; i < Reading_room.num_verts; i++)
    ConvertHandiness(&Reading_room.verts[i]);

  // calculate normals
  int bad_normals = 0;
  for (i = 0; i < Reading_room.num_faces; i++) {
    reading_room *rp = &Reading_room;
    reading_face *mfp = &rp->faces[i];
    // vm_GetNormal(&Reading_room.faces[i].normal,&rp->verts[mfp->face_verts[0]],&rp->verts[mfp->face_verts[1]],&rp->verts[mfp->face_verts[2]]);
    if (!ComputeNormal(&Reading_room.faces[i].normal, Reading_room.faces[i].num_verts, mfp->face_verts, rp->verts)) {
      mprintf(1, "Warning: Low precision normal for face %d\n", i);
      bad_normals++;
    }
  }
  if (bad_normals) {
    OutrageMessageBox("Warning:  The loaded room has %d faces with bad normals -- see the mono screen for details.\n\n"
                      "Coplanar faces in this room have NOT been combined.\n\n"
                      "It is STRONGLY recommended that you fix this room before using it.",
                      bad_normals);
    goto skip_combine;
  }

  // Now make a copy of the relevant Reading_room data into our destination
  int t;
  reading_face destface;

  mprintf(0, "Combining faces, please wait...\n");

TryAgain:

  for (i = 0; i < Reading_room.num_faces; i++) {
    reading_face *a = &Reading_room.faces[i];

    for (t = 0; t < Reading_room.num_faces; t++) {

      reading_face *b = &Reading_room.faces[t];

      if (a == b)
        continue;

      int retval = CombineFaces(&destface, a, b);
      if (retval) {
        // Copy the new face in the place of face a,
        // remove face b and then start over!

        Reading_room.faces[i] = destface;
        int k;
        for (k = t; k < Reading_room.num_faces - 1; k++)
          Reading_room.faces[k] = Reading_room.faces[k + 1];

        Reading_room.num_faces--;

        goto TryAgain;
      }
    }
  }

skip_combine:;

  mprintf(0, "Total faces=%d\n", Reading_room.num_faces);

  if (Reading_room.num_faces > MAX_FACES_PER_ROOM) {
    OutrageMessageBox("The imported room has %d faces.  The limit is %d.  Aborting import.", Reading_room.num_faces,
                      MAX_FACES_PER_ROOM);
    return -1;
  }

  mprintf(0, "Trying to allocate a room for %d verts, %d faces!\n", Reading_room.num_verts, Reading_room.num_faces);
  //	int n=AllocRoom (Reading_room.num_verts,Reading_room.num_faces);
  room *rp = CreateNewRoom(Reading_room.num_verts, Reading_room.num_faces, 1);

  if (rp != NULL) {
    for (i = 0; i < Reading_room.num_verts; i++)
      rp->verts[i] = Reading_room.verts[i];

    for (i = 0; i < Reading_room.num_faces; i++) {
      InitRoomFace(&rp->faces[i], Reading_room.faces[i].num_verts);

      rp->faces[i].normal = Reading_room.faces[i].normal;
      rp->faces[i].num_verts = Reading_room.faces[i].num_verts;

      rp->faces[i].tmap = Reading_room.faces[i].tmap;

      for (t = 0; t < Reading_room.faces[i].num_verts; t++) {
        rp->faces[i].face_verts[t] = Reading_room.faces[i].face_verts[t];
        rp->faces[i].face_uvls[t] = Reading_room.faces[i].face_uvls[t];
      }
    }

    // Reset UV's

    // AssignDefaultUVsToRoom (rp);

    // Remove redundant verts
    DeleteUnusedRoomVerts(rp);
    RemoveDuplicatePoints(rp);
    RemoveDuplicateFacePoints(rp);

    char name[255];
    char path[255];
    char extension[255];
    char roomname[255];

    // Find a unique name for this room

    ddio_SplitPath(filename, path, name, extension);
    int done = 0;
    int count = 1;

    sprintf(roomname, "%s.ORF", name);

    while (!done) {
      int val = FindRoomName(roomname);
      if (val == -1) {
        done = 1;
        continue;
      }
      count++;
      sprintf(roomname, "%s%d.ORF", name, count);
    }

    ASSERT(rp->name == NULL);
    rp->name = (char *)mem_malloc(strlen(roomname) + 1);
    strcpy(rp->name, roomname);

    // Save it out to disk (locally)
    ddio_MakePath(name, LocalRoomsDir.u8string().c_str(), roomname, NULL);
    SaveRoom(ROOMNUM(rp), name);
  }

  // Free our verts

  if (Reading_room.faces)
    mem_free(Reading_room.faces);
  if (Reading_room.verts)
    mem_free(Reading_room.verts);

  return ROOMNUM(rp);
}

// Converts the 3dsmax coordinate space into our left-handed coordinate space
void ConvertHandiness(vector *v) {
  vector v1 = *v;
  v->x = -1.0f * v1.x;
  v->y = v1.z;
  v->z = -1.0f * v1.y;
}

#define skip(f, n) cfseek(f, n, SEEK_CUR)
// Parses a chunk of a 3dsmax file - this function calls itself
void Parse3DSMaxChunk(CFILE *fp, int size) {
  uint16_t id;
  int len;
  int level = Nest_level;
  int i;
  float scale_factor = 0.0254f; // 0.0254 inches/meter

  Nest_level++;

  while (size && !cfeof(fp)) {

    id = cf_ReadShort(fp);
    len = cf_ReadInt(fp);

    if (size < 0) {
      mprintf(0, "%d:chunk error\n", level);
      exit(1);
    }

    switch (id) {
    case ID_UNKNOWN:
      Parse3DSMaxChunk(fp, len - 6);
      break;

    case ID_MAT_NAME: {
      char material_name[PAGENAME_LEN];

      cf_ReadString(material_name, PAGENAME_LEN, fp);

      strcpy(Materials[Num_materials].name, material_name);
      Num_materials++;

      ASSERT(Num_materials < MAX_MATERIALS);
      break;
    }

    case ID_MATERIAL: {
      Parse3DSMaxChunk(fp, len - 6);
      break;
    }

    case ID_MAT_TEXTURE: {
      int i;
      char texture_name[PAGENAME_LEN];

      // Read in Unknown field
      for (i = 0; i < 6; i++)
        cf_ReadByte(fp);

      cf_ReadShort(fp);

      // Read in Unknown field
      for (i = 0; i < 6; i++)
        cf_ReadByte(fp);

      cf_ReadString(texture_name, PAGENAME_LEN, fp);

      // Find the texture that has this bitmap as a name

      int texlen = strlen(texture_name);

      texture_name[texlen - 4] = 0;
      strcat(texture_name, ".OGF");

      int ret = FindTextureBitmapName(texture_name);
      if (ret == -1) {
        mprintf(0, "Couldn't find bitmap %s!\n", texture_name);
        ret = GetNextTexture(0);
      }

      Materials[Num_materials - 1].texhandle = ret;

      skip(fp, len - 6 - 6 - 2 - 6 - (strlen(texture_name) + 1));

      break;
    }
    case ID_MAT_APP: {
      char material_name[PAGENAME_LEN];
      int16_t n_faces, face;
      int done = 0;
      int texnum;

      cf_ReadString(material_name, PAGENAME_LEN, fp);

      n_faces = cf_ReadShort(fp);

      for (int i = 0; i < Num_materials && !done; i++) {
        if (!stricmp(Materials[i].name, material_name)) {
          texnum = Materials[i].texhandle;
          done = 1;
        }
      }

      if (!done) {
        mprintf(0, "Couldn't find material named %s!\n", material_name);
        texnum = GetNextTexture(0);
      }

      while (n_faces--) {
        face = cf_ReadShort(fp);

        Reading_room.faces[face].tmap = texnum;
      }

      break;
    }

    case ID_OBJECT: {
      cf_ReadString(Reading_room.name, PAGENAME_LEN, fp);
      Parse3DSMaxChunk(fp, len - 6 - (strlen(Reading_room.name) + 1));
      break;
    }
    // Special properties for this object/room
    case ID_OBJ_PROPS: {
      cf_ReadString(Reading_properties, 255, fp);
      // Skip next two ints
      cf_ReadInt(fp);
      cf_ReadInt(fp);

      Parse3DSMaxChunk(fp, len - 6 - 4 - 4 - (strlen(Reading_properties) + 1));
      break;
    }

    case ID_TRI_MESH:
      mprintf(0, "Found 3dsmax TRI_MESH chunk!\n");

      Parse3DSMaxChunk(fp, len - 6);
      break;

    // Vertex list
    case ID_VERTLIST: {
      uint16_t num_verts = cf_ReadShort(fp);
      int i;

      if (num_verts > MAX_VERTS_PER_ROOM)
        return;

      mprintf(0, "Reading in %d verts from room!\n", num_verts);

      // Make room for these verts
      Reading_room.num_verts = num_verts;

      for (i = 0; i < num_verts; i++) {
        Reading_room.verts[i].x = cf_ReadFloat(fp);
        Reading_room.verts[i].y = cf_ReadFloat(fp);
        Reading_room.verts[i].z = cf_ReadFloat(fp);

        Reading_room.verts[i] *= scale_factor;
      }

      break;
    }

    case ID_FACELIST: {
      uint16_t num_faces = cf_ReadShort(fp);
      uint16_t a, b, c, flags;
      int i, t, j, this_size;

      if (num_faces > MAX_READING_ROOM_FACES)
        return;

      mprintf(0, "Reading in %d faces!\n", num_faces);

      Reading_room.num_faces = num_faces;
      ASSERT(Reading_room.faces != NULL);

      for (i = 0; i < num_faces; i++) {
        // a,b, and c are indices into the list of vertices for this room
        Reading_room.faces[i].num_verts = 3;

        a = cf_ReadShort(fp);
        b = cf_ReadShort(fp);
        c = cf_ReadShort(fp);

        flags = cf_ReadShort(fp);

        // Set our pointers accordingly
        // We must reverse the ordering of the verts because
        // 3ds has a right handed coordinate system
        Reading_room.faces[i].face_verts[0] = c;
        Reading_room.faces[i].face_verts[1] = b;
        Reading_room.faces[i].face_verts[2] = a;

        Reading_room.faces[i].tmap = GetNextTexture(0);

        Reading_room.faces[i].flags = flags;

        // Read UVs

        float u[3], v[3];
        for (t = 0; t < 3; t++) {
          u[t] = cf_ReadFloat(fp);
          v[t] = cf_ReadFloat(fp);
        }

        for (j = 0; j < 3; j++) {
          Reading_room.faces[i].face_uvls[j].u = u[2 - j];
          Reading_room.faces[i].face_uvls[j].v = -v[2 - j];
          Reading_room.faces[i].face_uvls[j].alpha = 255;
        }
      }

      // get whatever is left in this segment
      this_size = num_faces * ((4 * sizeof(int16_t)) + (6 * sizeof(float)));
      if (len - 6 - this_size)
        Parse3DSMaxChunk(fp, len - 6 - 2 - this_size);

      break;
    }

    case ID_MATRIX: {
      float room_matrix[12];
      int16_t i;
      for (i = 0; i < 12; i++)
        room_matrix[i] = cf_ReadFloat(fp);
      break;
    }

    case OBJECT_NODE_TAG: {
      // printf( "=================== OBJECT_NODE_TAG! =======================\n" );

      Parse3DSMaxChunk(fp, len - 6);
      break;
    }

    default:
      // Skip this stuff
      for (i = 0; i < len - 6; i++)
        cf_ReadByte(fp);
      break;
    }
    size -= len;
  }

  Nest_level--;
}

int next_vertex(reading_face *f, int v) { return f->face_verts[(v + 1) % f->num_verts]; }

int this_vertex(reading_face *f, int v) { return f->face_verts[v]; }

int compute_faces_mapping(reading_face *f, vector *out_norm, float *out_d) {
  int i;
  float ut, vt, len;
  vector point, u, v;
  vector normal;

  vm_MakeZero(&point);
  vm_MakeZero(&normal);

  ut = vt = 0.0f;

  for (i = 0; i < f->num_verts; i++) {
    u.x = f->face_uvls[i].u;
    u.y = f->face_uvls[i].v;
    u.z = 1.0f;

    v.x = f->face_uvls[(i + 1) % f->num_verts].u;
    v.y = f->face_uvls[(i + 1) % f->num_verts].v;
    v.z = 1.0f;

    ut += (float)fabs(u.x - v.x);
    vt += (float)fabs(u.y - v.y);

    normal.x += (u.y - v.y) * (u.z + v.z);
    normal.y += (u.z - v.z) * (u.x + v.x);
    normal.z += (u.x - v.x) * (u.y + v.y);
    point += u;
  }

  len = vm_GetMagnitude(&normal);

  out_norm->x = normal.x / len;
  out_norm->y = normal.y / len;
  out_norm->z = normal.z / len;
  len *= f->num_verts;
  *out_d = (vm_DotProduct(&point, &normal) / len);
  point.x /= f->num_verts;
  point.y /= f->num_verts;
  point.z /= f->num_verts;

  return 0;
}

// Returns 1 if the uv's match
int uvs_match(reading_face *a, int va, reading_face *b, int vb) {
  int f1, f2, flag;
  vector n1, n2;
  float d1, d2;
  float cosTheta;
  float u_err, v_err;

  u_err = (float)fabs((a->face_uvls[va].u - b->face_uvls[vb].u) / ((a->face_uvls[va].u + b->face_uvls[vb].u) / 2.0f));
  v_err = (float)fabs((a->face_uvls[va].v - b->face_uvls[vb].v) / ((a->face_uvls[va].v + b->face_uvls[vb].v) / 2.0f));

  if (u_err + v_err > 0.00001f)
    return 0;

  f1 = compute_faces_mapping(a, &n1, &d1);
  f2 = compute_faces_mapping(b, &n2, &d2);

  if (f1 || f2)
    return 0;

  cosTheta = vm_DotProduct(&n1, &n2);

  if ((cosTheta < 0.99f) || (fabs(d2 - d1) > 0.0001f)) {
    flag = 0;
  } else {
    flag = 1;
  }

  return flag;
}

#define MAX_POINT_DISTANCE_FROM_PLANE .1

int CombineFaces(reading_face *dest, reading_face *a, reading_face *b) {
  int starta, startb, i;
  int va;

  if (!NormalsAreSame(&b->normal, &a->normal))
    return 0;

  if (a->tmap != b->tmap)
    return 0;

  ASSERT(a->num_verts > 2);
  ASSERT(b->num_verts > 2);

  // Compare points to plane
  vector vec = Reading_room.verts[a->face_verts[0]];
  vector norm = a->normal;
  float plane_dist = -(vec.x * norm.x + vec.y * norm.y + vec.z * norm.z);

  for (i = 0; i < b->num_verts; i++) {
    vec = Reading_room.verts[b->face_verts[i]];
    float dist = vec.x * norm.x + vec.y * norm.y + vec.z * norm.z + plane_dist;
    if (fabs(dist) > MAX_POINT_DISTANCE_FROM_PLANE)
      return 0;
  }

  // Go through each vertex and get a match

  for (starta = 0; starta < a->num_verts; starta++) {
    for (startb = 0; startb < b->num_verts; startb++) {
      if ((this_vertex(a, starta) == next_vertex(b, startb)) && (next_vertex(a, starta) == this_vertex(b, startb)) &&
          uvs_match(a, starta, b, (startb + 1) % b->num_verts) &&
          uvs_match(a, (starta + 1) % a->num_verts, b, startb)) {
        // MATCH!!!!!!!!

        dest->num_verts = 0;
        dest->flags = a->flags;
        dest->normal = a->normal; // normal of this face
        dest->tmap = a->tmap;

        for (i = 1; i < a->num_verts; i++) {
          ASSERT(dest->num_verts < MAX_VERTS_PER_FACE);
          dest->face_verts[dest->num_verts] = a->face_verts[(starta + i) % a->num_verts];
          dest->face_uvls[dest->num_verts] = a->face_uvls[(starta + i) % a->num_verts];
          va = dest->face_verts[dest->num_verts];
          dest->num_verts++;
        }

        if ((va == b->face_verts[(startb + 2) % b->num_verts]))
          mprintf(0, "WARNING!!! Faces were combined that caused the loss of a vertex!\n");

        for (i = 1; i < b->num_verts; i++) {
          ASSERT(dest->num_verts < MAX_VERTS_PER_FACE);
          if ((i == 1) && (va == b->face_verts[(startb + i + 1) % b->num_verts]))
            continue;
          else if ((i == 2) && (va == b->face_verts[(startb + i) % b->num_verts]))
            continue;
          else {
            dest->face_verts[dest->num_verts] = b->face_verts[(startb + i) % b->num_verts];
            dest->face_uvls[dest->num_verts] = b->face_uvls[(startb + i) % b->num_verts];
            dest->num_verts++;
          }
        }
        ASSERT(dest->num_verts > 2);

        if ((CheckFaceConcavity(dest->num_verts, dest->face_verts, &dest->normal, Reading_room.verts)) >= 0)
          return 0;

        // Now check for degenerate face
        for (int v = 0; v < dest->num_verts; v++) {
          if (dest->face_verts[v] == dest->face_verts[(v + 2) % dest->num_verts]) {
            return 0;
          }
        }

        return 1;
      }
    }
  }
  return 0;
}
