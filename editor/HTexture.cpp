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

 * $Logfile: /DescentIII/Main/editor/HTexture.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * HTexture implementation
 *
 * $Log: not supported by cvs2svn $
 *
 * 37    12/27/99 8:26a Gwar
 *
 * 36    8/30/99 12:55p Gwar
 * added a parameter to HTexturePropagateToFace to not change the texture
 * of the target face
 *
 * 35    7/30/99 1:19p Gwar
 * don't set World_changed in NEWEDITOR
 *
 * 34    7/24/99 5:25a Gwar
 * NEWEDITOR changes to HTextureApplyToRoomFace
 *
 * 33    7/04/99 4:56p Gwar
 * changes for texture management in NEWEDITOR
 *
 * 32    5/19/99 12:19a Gwar
 * #define Curroomp, Curface, etc as members of prim struct in NEWEDITOR
 * -- this allows the main room frame and level window to share these
 * variables and makes them non-global (i.e. no more sync problem between
 * world and room views)
 *
 * 31    5/03/99 2:06a Gwar
 * added HTexture.cpp to project
 *
 * 30    1/20/99 10:50a Jason
 * added new terrain
 *
 * 29    10/21/98 1:27p Jason
 * fixed texture u2,v2 sliding problems
 *
 * 28    8/16/98 4:24p Matt
 * When copying UVs from one face to another, only copy u & v, and not
 * other fields in the uv structure.
 *
 * 27    8/15/98 5:04p Matt
 * Added code to copy a texture & UVs from one face to another
 *
 * 26    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 25    4/16/98 10:42a Matt
 * Made texture propagation work across rooms.
 *
 * 24    4/02/98 12:23p Jason
 * trimmed some fat from our structures
 *
 * 23    9/23/97 12:20p Jason
 * fixed bug where rotating a texture would cause alphas and u2,v2s to
 * become corrupt
 *
 * 22    9/17/97 1:36p Samir
 * Fixed some new prototypes.
 *
 * 21    9/17/97 11:57a Matt
 * Ripped out segment code
 *
 * 19    8/21/97 6:01p Matt
 * Use groovy new FindSharedEdge() function
 *
 * 18    8/13/97 9:52a Matt
 * Combined slide left/right/up/down into one function, and the same with
 * rotate left/right
 *
 * 17    8/07/97 5:06p Jason
 * added new tiling system for terrain
 *
 * 16    8/07/97 3:19p Jason
 * replaced old terrain tmap system with new one
 *
 * 15    8/01/97 4:53p Jason
 * made a more general PropagateTextureToFace function call
 *
 * 14    7/22/97 7:08p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 13    7/18/97 7:38p Jason
 * finished room/terrain texture modifications
 *
 * 12    7/16/97 6:31p Jason
 * changed defaut texture uvs for terrain
 *
 * 15    6/24/97 12:41p Jason
 * checked in for safety
 *
 * 14    6/18/97 11:14a Mark
 * FROM JASON:Fixed dumb terrain rotational bug
 *
 * 13    6/17/97 4:16p Jason
 * added some terrain features
 *
 * 12    6/17/97 11:35a Jason
 * checked in for safety
 *
 * 11    6/06/97 4:57p Jason
 * more nifty megacell/tmap2 features
 *
 * 10    6/04/97 1:32p Matt
 * Changed Side_to_verts[] and Side_opposite[] to be arrays of ints, which
 * should be faster than bytes.
 *
 * 9     5/30/97 3:32p Samir
 * When rotating textures, lighting preserved
 *
 * 8     5/02/97 7:21p Matt
 * Added code to rotate tmap2's
 *
 * 7     4/17/97 4:03p Samir
 * Apply Tmap 1 and Tmap2 implemented, but no Tmap2 rendering is occurring
 * yet.
 *
 * 6     3/31/97 5:58p Matt
 * Revamped mine update flags
 *
 * 5     3/31/97 3:50p Samir
 * Set default texture uvs should work for side not whole segment.
 *
 * 4     2/26/97 6:40p Samir
 * changed g3s_uvl to g3UVL
 *
 * 3     2/26/97 3:59p Samir
 * Most scaling, rotating, sliding and flipping work.
 *
 * 2     2/20/97 11:59a Samir
 * Fixed bugs
 *
 * 1     2/20/97 11:50a Samir
 *
 * $NoKeywords: $
 */

#include "HTexture.h"

#ifndef NEWEDITOR
#include "d3edit.h"
#endif

#include "roomuvs.h"
#include "gametexture.h"
#include "terrain.h"
#include "room.h"
#include "descent.h"
#include "erooms.h"

#define HTEX_CALIB_VAL ((float)(1.0 / 128.0))

//	---------------------------------------------------------------------------
//	internal function prototypes
//	---------------------------------------------------------------------------

void HTextureRoomStretch(room *rp, int facenum, int edge, int direction);
void HTextureRotUVPoint(g3UVL *uvrot, float *rotmat, roomUVL *uv, g3UVL *uvcenter);
void HTextureCreate2DRotMat(float *rotmat, angle ang);
void HTextureRotUVTerrainPoint(g3UVL *uvrot, float *rotmat, g3UVL *uv, g3UVL *uvcenter);
void GetUVLForRoomPoint(int roomnum, int facenum, int vertnum, roomUVL *uvl);
int HTextureGetTopVertexForFace(int roomnum, int facenum);
int HTextureGetBottomVertexForFace(int roomnum, int facenum);
int HTextureGetLeftVertexForFace(int roomnum, int facenum);
int HTextureGetRightVertexForFace(int roomnum, int facenum);
void HTextureRotUVPointsOnRoomFace(room *roomp, int facenum, float *rotmat, g3UVL *uvcenter);
void HTextureComputeUVRoomFaceCenter(g3UVL *uvcenter, room *roomp, int facenum);
void HTextureTerrainStretch(int edge, int direction);

//	---------------------------------------------------------------------------
//	Functions to manipulate textures within the mine, through segments
//	---------------------------------------------------------------------------

// Apply the specified texture to the specified room:face
void HTextureApplyToRoomFace(room *rp, int facenum, int tnum) {
  ASSERT(rp->used);

#ifdef NEWEDITOR
  if (tnum == -1)
    return;
  if (rp->faces[facenum].tmap >= 0)
    SwitchTexture(rp, rp->faces[facenum].tmap, tnum);
#endif

  rp->faces[facenum].tmap = tnum;
}

// Copy texture from current face to adjacent face, tiling the UV coordinates
// Parameters:	destrp,destface - room:face that the propagate is based on
//					srcrp,srcface - room:face that is changed
// Return:	1 if success, 0 if faces not adjacent
int HTexturePropagateToFace(room *destrp, int destface, room *srcrp, int srcface, bool tex) {
  face *dfp = &destrp->faces[destface];
  face *sfp = &srcrp->faces[srcface];
  int v0, v1;

  // Get shared edge
  if (destrp != srcrp) { // Faces in different rooms
    if (!FindSharedEdgeAcrossRooms(destrp, destface, srcrp, srcface, &v0, &v1))
      return 0;
  } else { // Faces in same room
    if (!FindSharedEdge(dfp, sfp, &v0, &v1))
      return 0;
  }

  if (tex) {
#ifdef NEWEDITOR
    SwitchTexture(destrp, dfp->tmap, sfp->tmap);
#endif

    // Copy texture from Curface
    dfp->tmap = sfp->tmap;
  }

  // Assign uvs from shared edge to rest of verts in face
  AssignUVsToFace(destrp, destface, &sfp->face_uvls[(v1 + 1) % sfp->num_verts], &sfp->face_uvls[v1], v0,
                  (v0 + 1) % dfp->num_verts);

  // Success
  return 1;
}

// Copy texture UVs from one face to another
// Parameters:	destrp,destface - room:face that is changed
//					srcrp,srcface - room:face to copy from
//					offset - vert 0 on source is assigned to vert offset on dest
// Return:	1 if success, 0 if faces don't have the same number of verts
int HTextureCopyUVsToFace(room *destrp, int destface, room *srcrp, int srcface, int offset) {
  face *dfp = &destrp->faces[destface];
  face *sfp = &srcrp->faces[srcface];

  // Make sure faces have the same number of vertices
  if (dfp->num_verts != sfp->num_verts)
    return 0;

  // Copy UV values
  for (int i = 0; i < dfp->num_verts; i++) {
    dfp->face_uvls[(i + offset) % dfp->num_verts].u = sfp->face_uvls[i].u;
    dfp->face_uvls[(i + offset) % dfp->num_verts].v = sfp->face_uvls[i].v;
  }

  // Success!
#ifndef NEWEDITOR
  World_changed = 1;
#endif
  return 1;
}

//	texture flipping

void HTextureFlipX() {
  int i;

  if (Editor_view_mode == VM_TERRAIN) {
    // terrain_segment oldseg;

    for (i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
      if (TerrainSelected[i]) {
        /*oldseg=Terrain_seg[i];
        Terrain_seg[i].u[0]=oldseg.u[1];
        Terrain_seg[i].u[1]=oldseg.u[0];
        Terrain_seg[i].u[2]=oldseg.u[3];
        Terrain_seg[i].u[3]=oldseg.u[2];

        Terrain_seg[i].v[0]=oldseg.v[1];
        Terrain_seg[i].v[1]=oldseg.v[0];
        Terrain_seg[i].v[2]=oldseg.v[3];
        Terrain_seg[i].v[3]=oldseg.v[2];*/
      }
    }
  } else {
    ASSERT(Curroomp->used);

    for (int i = 0; i < Curroomp->faces[Curface].num_verts; i++)
      Curroomp->faces[Curface].face_uvls[i].u = 1 - Curroomp->faces[Curface].face_uvls[i].u;
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureFlipY() {
  int i;

  if (Editor_view_mode == VM_TERRAIN) {
    terrain_segment oldseg;

    for (i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
      if (TerrainSelected[i]) {
        oldseg = Terrain_seg[i];
        /*Terrain_seg[i].v[0]=oldseg.v[3];
        Terrain_seg[i].v[1]=oldseg.v[2];
        Terrain_seg[i].v[2]=oldseg.v[1];
        Terrain_seg[i].v[3]=oldseg.v[0];

        Terrain_seg[i].u[0]=oldseg.u[3];
        Terrain_seg[i].u[1]=oldseg.u[2];
        Terrain_seg[i].u[2]=oldseg.u[1];
        Terrain_seg[i].u[3]=oldseg.u[0];*/
      }
    }
  } else {
    ASSERT(Curroomp->used);

    for (int i = 0; i < Curroomp->faces[Curface].num_verts; i++)
      Curroomp->faces[Curface].face_uvls[i].v = 1 - Curroomp->faces[Curface].face_uvls[i].v;
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureSlide(room *rp, int facenum, float right, float up) {
  ASSERT(rp != NULL);
  ASSERT(rp->used);

  if (Editor_view_mode == VM_TERRAIN) {
    /*int i;
    for (i=0;i<TERRAIN_DEPTH*TERRAIN_WIDTH;i++)
    {
            if (TerrainSelected[i])
            {
                    for (int t=0;t<4;t++)
                    {
                            float val=Terrain_UV_lookup[Terrain_seg[i].u[t]];

                            val+=(1.0/32.0);

                            Terrain_seg[i].u[t]=TerrainLookupUV(val);
                    }

            }

    }
    */
    return;

  } else { // mine
    for (int i = 0; i < rp->faces[facenum].num_verts; i++) {
      rp->faces[facenum].face_uvls[i].u -= right / 128.0f;
      rp->faces[facenum].face_uvls[i].v += up / 128.0f;
    }
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureRotate(room *roomp, int facenum, angle ang) {
  g3UVL uvcenter;
  float rotmat[4];

  HTextureCreate2DRotMat(rotmat, ang);

  if (Editor_view_mode == VM_TERRAIN && ang == 0x4000) {
    for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
      if (TerrainSelected[i]) {
        /*int f=(Terrain_seg[i].rotation_factor&0x0F);
        f++;
        f%=4;

        Terrain_seg[i].rotation_factor&=0xF0;
        Terrain_seg[i].rotation_factor|=(f);*/
      }
    }

    return;
  } else {
    HTextureComputeUVRoomFaceCenter(&uvcenter, roomp, facenum);
    HTextureRotUVPointsOnRoomFace(roomp, facenum, rotmat, &uvcenter);
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureStretchMore(room *rp, int face, int edge) {
  if (Editor_view_mode == VM_TERRAIN) {
    HTextureTerrainStretch(edge, 1 * D3EditState.texscale);
  } else {
    HTextureRoomStretch(rp, face, edge, 1 * D3EditState.texscale);
  }
}

void HTextureStretchLess(room *rp, int face, int edge) {
  if (Editor_view_mode == VM_TERRAIN) {
    HTextureTerrainStretch(edge, (-1 * D3EditState.texscale));
  } else {
    HTextureRoomStretch(rp, face, edge, (-1 * D3EditState.texscale));
  }
}

void HTextureSetDefault(room *rp, int face) {
  if (Editor_view_mode == VM_TERRAIN) {
    for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
      if (TerrainSelected[i]) {
        int index = Terrain_seg[i].texseg_index;
        Terrain_tex_seg[index].rotation = 0;
      }
    }
    World_changed = 1;
  } else if (Editor_view_mode == VM_ROOM) {
    //@@Stretch_scale_x = (float)1.0;
    //@@Stretch_scale_y = (float)1.0;

    for (int i = 0; i < rp->faces[face].num_verts; i++) {
      float saveu2 = rp->faces[face].face_uvls[i].u2;
      float savev2 = rp->faces[face].face_uvls[i].v2;

      GetUVLForRoomPoint(ROOMNUM(rp), face, i, &rp->faces[face].face_uvls[i]);

      rp->faces[face].face_uvls[i].u2 = saveu2;
      rp->faces[face].face_uvls[i].v2 = savev2;
    }
  } else {
    //@@Stretch_scale_x = (float)1.0;
    //@@Stretch_scale_y = (float)1.0;

    for (int i = 0; i < rp->faces[face].num_verts; i++) {
      float saveu2 = rp->faces[face].face_uvls[i].u2;
      float savev2 = rp->faces[face].face_uvls[i].v2;

      GetUVLForRoomPoint(ROOMNUM(rp), face, i, &rp->faces[face].face_uvls[i]);

      rp->faces[face].face_uvls[i].u2 = saveu2;
      rp->faces[face].face_uvls[i].v2 = savev2;
    }
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureNextEdge() {
  Curedge++;

  if (Editor_view_mode == VM_TERRAIN) {
    if (Curedge >= 4)
      Curedge = 0;
  } else // mine
  {
    if (Curedge >= Curroomp->faces[Curface].num_verts)
      Curedge = 0;
  }

  State_changed = 1;
}

//	---------------------------------------------------------------------------
//	functions used by HTexture operations
//	---------------------------------------------------------------------------

//	direction = -1 or 1 depending on direction
// Stretches all vertices towards or away from a given edge
// Depending on the geometry of the face, this can cause distortions
void HTextureRoomStretch(room *rp, int facenum, int edge, int direction) {
  int next_edge = (edge + 1) % rp->faces[facenum].num_verts;

  // find deltas
  float du = rp->faces[facenum].face_uvls[next_edge].u - rp->faces[facenum].face_uvls[edge].u;
  float dv = rp->faces[facenum].face_uvls[next_edge].v - rp->faces[facenum].face_uvls[edge].v;

  // rotate delta's 90 degrees
  float nu = -dv;
  float nv = du;

  // Find a magnitude to shift by
  float mag = sqrt((nv * nv) + (nu * nu));
  nv /= mag;
  nu /= mag;

  nv /= 64.0;
  nu /= 64.0;

  // Apply to all verts except for our edge
  for (int i = 0; i < rp->faces[facenum].num_verts; i++) {
    if (i == edge || i == next_edge)
      continue;

    rp->faces[facenum].face_uvls[i].v -= (nv * direction);
    rp->faces[facenum].face_uvls[i].u -= (nu * direction);
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureTerrainStretch(int edge, int direction) {
  int i;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
    }
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

void HTextureComputeUVRoomFaceCenter(g3UVL *uvcenter, room *roomp, int facenum) {
  int i;
  face *facep = &roomp->faces[facenum];

  uvcenter->u = 0;
  uvcenter->v = 0;

  for (i = 0; i < facep->num_verts; i++) {
    uvcenter->u += facep->face_uvls[i].u;
    uvcenter->v += facep->face_uvls[i].v;
  }

  uvcenter->u /= i;
  uvcenter->v /= i;
}

void HTextureRotUVPoint(g3UVL *uvrot, float *rotmat, roomUVL *uv, g3UVL *uvcenter) {
  uvrot->u = ((uv->u - uvcenter->u) * rotmat[0]) + ((uv->v - uvcenter->v) * rotmat[1]) + uvcenter->u;
  uvrot->v = ((uv->u - uvcenter->u) * rotmat[2]) + ((uv->v - uvcenter->v) * rotmat[3]) + uvcenter->v;
}

void HTextureRotUVPointsOnRoomFace(room *roomp, int facenum, float *rotmat, g3UVL *uvcenter) {
  int v;
  face *facep = &roomp->faces[facenum];
  g3UVL tuv;

  for (v = 0; v < facep->num_verts; v++) {
    HTextureRotUVPoint(&tuv, rotmat, &facep->face_uvls[v], uvcenter);
    facep->face_uvls[v].u = tuv.u;
    facep->face_uvls[v].v = tuv.v;
  }
}

void HTextureCreate2DRotMat(float *rotmat, angle ang) {
  float sinang, cosang;

  sinang = FixSin(ang);
  cosang = FixCos(ang);

  rotmat[0] = cosang;
  rotmat[1] = sinang;
  rotmat[2] = -sinang;
  rotmat[3] = cosang;
}

void HTextureRotUVTerrainPoint(g3UVL *uvrot, float *rotmat, g3UVL *uv, g3UVL *uvcenter) {
  uvrot->u = ((uv->u - uvcenter->u) * rotmat[0]) + ((uv->v - uvcenter->v) * rotmat[1]) + uvcenter->u;
  uvrot->v = ((uv->u - uvcenter->u) * rotmat[2]) + ((uv->v - uvcenter->v) * rotmat[3]) + uvcenter->v;
}

// returns the index in the face_verts array for the leftmost point on this face
int HTextureGetLeftVertexForFace(int roomnum, int facenum) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE];

  ASSERT(Rooms[roomnum].used);
  ASSERT(Rooms[roomnum].faces[facenum].num_verts >= 3);

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  int i;
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++)
    avg_vert += Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

  avg_vert /= i;

  // Make the orientation matrix
  fvec = Rooms[roomnum].faces[facenum].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    vector vert = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];
    vector rot_vert;

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find left most point
  int leftmost_point = -1;
  float leftmost_x = 900000.00f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].x < leftmost_x) {
      leftmost_point = i;
      leftmost_x = verts[i].x;
    }
  }

  ASSERT(leftmost_point != -1);
  return leftmost_point;
}

// returns the index in the face_verts array for the topmost point on this face
int HTextureGetTopVertexForFace(int roomnum, int facenum) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE];

  ASSERT(Rooms[roomnum].used);
  ASSERT(Rooms[roomnum].faces[facenum].num_verts >= 3);

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  int i;
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++)
    avg_vert += Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

  avg_vert /= i;

  // Make the orientation matrix
  fvec = Rooms[roomnum].faces[facenum].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    vector vert = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];
    vector rot_vert;

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find top most point
  int topmost_point = -1;
  float topmost_y = -900000.0f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].y > topmost_y) {
      topmost_point = i;
      topmost_y = verts[i].y;
    }
  }

  ASSERT(topmost_point != -1);

  return topmost_point;
}

// returns the index in the face_verts array for the rightmost point on this face
int HTextureGetRightVertexForFace(int roomnum, int facenum) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE];

  ASSERT(Rooms[roomnum].used);
  ASSERT(Rooms[roomnum].faces[facenum].num_verts >= 3);

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  int i;
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++)
    avg_vert += Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

  avg_vert /= i;

  // Make the orientation matrix
  fvec = Rooms[roomnum].faces[facenum].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    vector vert = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];
    vector rot_vert;

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find right most point
  int rightmost_point = -1;
  float rightmost_x = -900000.00f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].x > rightmost_x) {
      rightmost_point = i;
      rightmost_x = verts[i].x;
    }
  }

  ASSERT(rightmost_point != -1);
  return rightmost_point;
}

// returns the index in the face_verts array for the most point on this face
int HTextureGetBottomVertexForFace(int roomnum, int facenum) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE];

  ASSERT(Rooms[roomnum].used);
  ASSERT(Rooms[roomnum].faces[facenum].num_verts >= 3);

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  int i;
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++)
    avg_vert += Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

  avg_vert /= i;

  // Make the orientation matrix
  fvec = Rooms[roomnum].faces[facenum].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    vector vert = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];
    vector rot_vert;

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find bottom most point
  int bottommost_point = -1;
  float bottommost_y = 900000.0f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].y < bottommost_y) {
      bottommost_point = i;
      bottommost_y = verts[i].y;
    }
  }

  ASSERT(bottommost_point != -1);

  return bottommost_point;
}

/*void HTextureGetBoxUVLForFace (room *rp,facenum)
{
        int l,r,t,b;
        vector lpoint,rpoint,tpoint,bpoint;
        g3UVL luvl,ruvl,tuvl,buvl,xchange,ychange;

        b=HTextureGetBottomVertexForFace (roomnum,facenum);
        t=HTextureGetTopVertexForFace (roomnum,facenum);
        l=HTextureGetLeftVertexForFace (roomnum,facenum);
        r=HTextureGetRightVertexForFace (roomnum,facenum);

        lpoint=rp->verts[rp->faces[facenum].face_verts[l]];
        rpoint=rp->verts[rp->faces[facenum].face_verts[r]];
        tpoint=rp->verts[rp->faces[facenum].face_verts[t]];
        bpoint=rp->verts[rp->faces[facenum].face_verts[b]];

        luvl=rp->faces[facenum].face_uvls[l];
        ruvl=rp->faces[facenum].face_uvls[r];
        tuvl=rp->faces[facenum].face_uvls[t];
        buvl=rp->faces[facenum].face_uvls[b];

        xchange.u=ruvl.u-luvl.u;
        xchange.v=ruvl.v-luvl.v;

        ychange=buvl.u-tuvl.u;
        ychange=buvl.v-tuvl.v;

}*/
