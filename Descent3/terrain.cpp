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

#include <cstdlib>

#ifdef NEWEDITOR
#include "neweditor\globals.h"
#endif
#include "vecmat.h"
#include "mono.h"
#include "terrain.h"
#include "pserror.h"
#include "gametexture.h"
#include "lighting.h"
#include "lightmap.h"
#include "weather.h"
#include <string.h>
#include "mem.h"
#include "dedicated_server.h"
#include "psrand.h"
#ifdef EDITOR
#include "editor\d3edit.h"
#endif

#include <algorithm>

#define SKY_RADIUS 2500.0
#define DEFAULT_LIGHT_SOURCE                                                                                           \
  { 0, TERRAIN_SIZE * 100, 0 }

// How far we can see (in world coordinates)
float VisibleTerrainZ;

terrain_segment Terrain_seg[TERRAIN_WIDTH * TERRAIN_DEPTH];
terrain_tex_segment Terrain_tex_seg[TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH];
terrain_sky Terrain_sky;

#if (!defined(RELEASE) || defined(NEWEDITOR))
// first object to render after cell has been rendered (only used for SW renderer)
int16_t Terrain_seg_render_objs[TERRAIN_WIDTH * TERRAIN_DEPTH];
#endif

// Our lighting maps for the terrain, one for each quadrant (starting at lower left)
int TerrainLightmaps[4];

// A list of terrain to render
terrain_render_info Terrain_list[MAX_CELLS_TO_RENDER];

uint16_t *Terrain_rotate_list; // which points have been sub/rotated this frame
g3Point *World_point_buffer; // Rotated points

// The min/max values for a particular region of terrain
uint8_t *Terrain_min_height_int[7];
uint8_t *Terrain_max_height_int[7];
// Texture values for a particular region

// Terrain dynamic lighting table
uint8_t Terrain_dynamic_table[TERRAIN_WIDTH * TERRAIN_DEPTH];

// Terrain normals depending on LOD
terrain_normals *TerrainNormals[MAX_TERRAIN_LOD];

// Max deltas per terrain lod block
float *TerrainDeltaBlocks[MAX_TERRAIN_LOD];

// Tracks edges of LOD
uint8_t TerrainJoinMap[TERRAIN_WIDTH * TERRAIN_DEPTH];

// Terrain Y values
float Terrain_y_values[256];

#if (defined(EDITOR) || defined(NEWEDITOR))
uint8_t TerrainSelected[TERRAIN_WIDTH * TERRAIN_DEPTH];
int Num_terrain_selected = 0;
int Editor_LOD_engine_off = 1;
bool Terrain_render_ext_room_objs = true;
#endif

int TSearch_on = 0, TSearch_found_type, TSearch_x, TSearch_y, TSearch_seg, TSearch_face;

int Terrain_LOD_engine_off = 0;

int TerrainEdgeTest[MAX_TERRAIN_LOD][16];
uint8_t TerrainEdgeJump[MAX_TERRAIN_LOD];

// Unique terrain geometry identifier
int Terrain_checksum = -1;

// Occlusion data for knowing what to draw
uint8_t Terrain_occlusion_map[256][32];
int Terrain_occlusion_checksum = -2;

// returns the index of the highest float
int GetHighestDelta(float *deltas, int count) {
  int high_index = -999;
  float high_delta = -99999;
  int i;

  for (i = 0; i < count; i++) {
    if ((deltas[i]) > (high_delta)) {
      high_index = i;
      high_delta = deltas[i];
    }
  }

  ASSERT(high_index < count);

  return high_index;
}

float RecurseLODDeltas(int x1, int y1, int x2, int y2, int lod) {
  float deltas[6];
  float maxdelta;
  float v0, v1, v2, v3;
  int edgex = x2, edgey = y2;
  int i, t;

  if (x1 % 2)
    Int3();
  if (x2 % 2)
    Int3();
  if (y1 % 2)
    Int3();
  if (y2 % 2)
    Int3();

  int midx = ((x2 - x1) / 2) + x1;
  int midy = ((y2 - y1) / 2) + y1;

  if (x2 == TERRAIN_WIDTH)
    edgex = TERRAIN_WIDTH - 1;
  if (y2 == TERRAIN_DEPTH)
    edgey = TERRAIN_DEPTH - 1;

  // starts from lower left, proceeds clockwise
  v0 = Terrain_seg[y1 * TERRAIN_WIDTH + x1].y;
  v1 = Terrain_seg[edgey * TERRAIN_WIDTH + x1].y;
  v2 = Terrain_seg[edgey * TERRAIN_WIDTH + edgex].y;
  v3 = Terrain_seg[y1 * TERRAIN_WIDTH + edgex].y;

  deltas[0] = fabs(Terrain_seg[(midy)*TERRAIN_WIDTH + midx].y - (((v2 - v0) / 2) + v0));
  deltas[1] = fabs(Terrain_seg[(midy)*TERRAIN_WIDTH + midx].y - (((v3 - v1) / 2) + v1));

  // left edge
  deltas[2] = fabs(Terrain_seg[(midy)*TERRAIN_WIDTH + x1].y - (((v1 - v0) / 2) + v0));

  // top edge
  deltas[3] = fabs(Terrain_seg[(y2)*TERRAIN_WIDTH + midx].y - (((v2 - v1) / 2) + v1));

  // right edge
  deltas[4] = fabs(Terrain_seg[(midy)*TERRAIN_WIDTH + x2].y - (((v3 - v2) / 2) + v2));

  // bottom edge
  deltas[5] = fabs(Terrain_seg[(y1)*TERRAIN_WIDTH + midx].y - (((v3 - v0) / 2) + v0));

  maxdelta = deltas[GetHighestDelta(deltas, 6)];

  if (lod != MAX_TERRAIN_LOD - 2) {
    deltas[0] = RecurseLODDeltas(x1, midy, midx, y2, lod + 1);
    deltas[1] = RecurseLODDeltas(midx, midy, x2, y2, lod + 1);
    deltas[2] = RecurseLODDeltas(midx, y1, x2, midy, lod + 1);
    deltas[3] = RecurseLODDeltas(x1, y1, midx, midy, lod + 1);

    if (deltas[0] == SHUTOFF_LOD_INVISIBLE && deltas[1] == SHUTOFF_LOD_INVISIBLE &&
        deltas[2] == SHUTOFF_LOD_INVISIBLE && deltas[3] == SHUTOFF_LOD_INVISIBLE) {
      maxdelta = SHUTOFF_LOD_INVISIBLE;
    } else {
      for (i = 0; i < 4; i++) {
        if (deltas[i] == SHUTOFF_LOD_INVISIBLE)
          deltas[i] = SHUTOFF_LOD_DELTA;
      }

      float maxdelta2 = deltas[GetHighestDelta(deltas, 4)];
      if (maxdelta2 > maxdelta)
        maxdelta = maxdelta2;
    }
  }

  // Now check if there is anything special about this level of detail that
  // excludes it from being used in the engine
  if (lod == MAX_TERRAIN_LOD - 2) {
    int total_counted = 0, total_invis = 0;

    for (i = y1; i < y2; i++) {
      for (t = x1; t < x2; t++, total_counted++) {
        if ((Terrain_seg[i * TERRAIN_WIDTH + t].flags & TF_INVISIBLE)) {
          maxdelta = SHUTOFF_LOD_DELTA;
          total_invis++;
        }
      }
    }

    // See if we can completely turn off this LOD
    if (total_invis == total_counted)
      maxdelta = SHUTOFF_LOD_INVISIBLE;
  }

  return (maxdelta);
}

// returns highest slopechange
float GetGreatestSlopeChange(float *slopes, int count) {
  float high_delta = -90000.0f;
  int i, t;

  for (i = 0; i < count; i++) {
    for (t = 0; t < count; t++) {
      if ((fabs(slopes[t] - slopes[i])) > high_delta) {
        high_delta = fabs(slopes[t] - slopes[i]);
      }
    }
  }

  return high_delta;
}

void GenerateSingleLODDelta(int sx, int sz) {
  int w, h, i, z, x;
  int simplemul, rowsize;
  int chunk_size = 1 << (MAX_TERRAIN_LOD - 1);

  sx *= chunk_size;
  sz *= chunk_size;

  int save_x = sx;
  int save_z = sz;

  // Starts from lower-left, going clockwise
  // 0 is lowest_level_detail (blunt)
  for (i = 0; i < MAX_TERRAIN_LOD - 1; i++) {
    w = chunk_size >> ((MAX_TERRAIN_LOD - 1) - i);
    h = chunk_size >> ((MAX_TERRAIN_LOD - 1) - i);

    simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - i);
    rowsize = TERRAIN_WIDTH / simplemul;

    sx = save_x;
    sz = save_z;

    sx /= simplemul;
    sz /= simplemul;

    for (z = sz; z < sz + h; z++) {
      for (x = sx; x < sx + w; x++) {
        float delta;

        delta =
            RecurseLODDeltas(x * simplemul, (z * simplemul), (x * simplemul) + simplemul, z * simplemul + simplemul, i);
        TerrainDeltaBlocks[i][z * rowsize + x] = delta;
      }
    }
  }
}

void GenerateLODDeltas() {
  int w, h, i, z, x;
  int simplemul, rowsize;
  // Starts from lower-left, going clockwise
  for (i = 0; i < MAX_TERRAIN_LOD - 1; i++) {
    w = TERRAIN_WIDTH >> ((MAX_TERRAIN_LOD - 1) - i);
    h = TERRAIN_DEPTH >> ((MAX_TERRAIN_LOD - 1) - i);

    simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - i);
    rowsize = TERRAIN_WIDTH / simplemul;

    for (z = 0; z < h; z++) {
      for (x = 0; x < w; x++) {
        float delta;

        delta =
            RecurseLODDeltas(x * simplemul, (z * simplemul), (x * simplemul) + simplemul, z * simplemul + simplemul, i);
        TerrainDeltaBlocks[i][z * rowsize + x] = delta;
      }
    }
  }
}

// Returns a unique checksum for the current terrain geometry
int GetTerrainGeometryChecksum() {
  int total = 0;

  for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    total += (Terrain_seg[i].ypos + i);
  }

  return total;
}

// Builds the min max quadtree data for terrain VSD
void BuildMinMaxTerrain() {
  int i, w, h, start, x, y, cell;
  int row_width, xoffset, yoffset, total_rows;
  int minheight, maxheight, cellheight;

  mprintf(0, "Building min/max terrain table.\n");

  // Calculate our integer y positions (0-255)
  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    float fl;

#if (!defined(RELEASE) || defined(NEWEDITOR))
    Terrain_seg_render_objs[i] = -1;
#endif

    fl = Terrain_seg[i].ypos * TERRAIN_HEIGHT_INCREMENT;

    Terrain_seg[i].y = fl;
  }

  int check = GetTerrainGeometryChecksum();

  if (check == Terrain_checksum)
    return;

  Terrain_checksum = check;

  // Generate level of detail deltas
  if (!Dedicated_server)
    GenerateLODDeltas();

  for (i = 0; i < 7; i++) {
    row_width = 1 << i;
    total_rows = 1 << i;
    int yspeed_offset = 0;

    for (yoffset = 0; yoffset < total_rows; yoffset++, yspeed_offset += row_width) {
      for (xoffset = 0; xoffset < row_width; xoffset++) {
        w = TERRAIN_WIDTH >> i;
        h = TERRAIN_WIDTH >> i;

        start = ((yoffset * (TERRAIN_WIDTH >> i)) * TERRAIN_WIDTH);
        start += (xoffset * (TERRAIN_WIDTH >> i));

        minheight = 999;
        maxheight = 0;

        if (h < TERRAIN_DEPTH)
          h++;
        if (w < TERRAIN_DEPTH)
          w++;

        int terrain_offset = 0;
        for (y = 0; y < h; y++, terrain_offset += TERRAIN_WIDTH) {
          for (x = 0; x < w; x++) {
            cell = start + (terrain_offset) + x;
            cellheight = Terrain_seg[cell].ypos;

            if (cellheight < minheight)
              minheight = cellheight;
            if (cellheight > maxheight)
              maxheight = cellheight;
          }
        }

        if (minheight < 0)
          minheight = 0;
        if (maxheight > 255)
          maxheight = 255;

        Terrain_min_height_int[i][yspeed_offset + xoffset] = (minheight);
        Terrain_max_height_int[i][yspeed_offset + xoffset] = (maxheight);
      }
    }
  }
}

// Changes the terrain mesh for deformation effect
void DeformTerrainPoint(int x, int z, int change_height) {
  terrain_segment *tseg = &Terrain_seg[z * TERRAIN_WIDTH + x];
  int i;

  change_height += tseg->ypos;

  change_height = std::clamp(change_height, 0, 255);

  tseg->ypos = change_height;
  tseg->y = tseg->ypos * TERRAIN_HEIGHT_INCREMENT;

  int sx = std::max(0, x - 1);
  int sz = std::max(0, z - 1);

  // Update min/max
  for (i = 0; i < 7; i++) {
    int row_width = 1 << i;
    int div = 256 >> i;

    for (int t = sz; t <= z; t++) {
      for (int k = sx; k <= x; k++) {

        int offset = ((t / div) * row_width) + (k / div);

        if (tseg->ypos > Terrain_max_height_int[i][offset])
          Terrain_max_height_int[i][offset] = tseg->ypos;
        if (tseg->ypos < Terrain_min_height_int[i][offset])
          Terrain_min_height_int[i][offset] = tseg->ypos;
      }
    }
  }

  // Update normals

  for (i = sz; i <= z; i++) {
    for (int t = sx; t <= x; t++) {
      vector a, b, c;
      terrain_segment *tseg0 = &Terrain_seg[i * TERRAIN_WIDTH + t];
      terrain_segment *tseg1 = &Terrain_seg[(i + 1) * TERRAIN_WIDTH + t];
      terrain_segment *tseg2 = &Terrain_seg[((i + 1) * TERRAIN_WIDTH) + t + 1];
      terrain_segment *tseg3 = &Terrain_seg[(i * TERRAIN_WIDTH) + t + 1];

      // Do upper left triangle
      a.x = t * TERRAIN_SIZE;
      a.y = tseg0->y;
      a.z = i * TERRAIN_SIZE;

      b.x = t * TERRAIN_SIZE;
      b.y = tseg1->y;
      b.z = (i + 1) * TERRAIN_SIZE;

      c.x = (t + 1) * TERRAIN_SIZE;
      c.y = tseg2->y;
      c.z = (i + 1) * TERRAIN_SIZE;

      vm_GetNormal(&TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal1, &a, &b, &c);

      // Now do lower right triangle
      a.x = t * TERRAIN_SIZE;
      a.y = tseg0->y;
      a.z = i * TERRAIN_SIZE;

      b.x = (t + 1) * TERRAIN_SIZE;
      b.y = tseg2->y;
      b.z = (i + 1) * TERRAIN_SIZE;

      c.x = (t + 1) * TERRAIN_SIZE;
      c.y = tseg3->y;
      c.z = (i)*TERRAIN_SIZE;

      vm_GetNormal(&TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal2, &a, &b, &c);
    }
  }
}

void UpdateSingleTerrainLightmap(int which);
void DeformTerrain(vector *pos, int depth, float size) {
  int startx, startz, endx, endz;
  int changed[4] = {0, 0, 0, 0};
  vector local_pos = *pos;

  startx = (pos->x / TERRAIN_SIZE) - (size / TERRAIN_SIZE);
  startz = (pos->z / TERRAIN_SIZE) - (size / TERRAIN_SIZE);
  endx = (pos->x / TERRAIN_SIZE) + (size / TERRAIN_SIZE);
  endz = (pos->z / TERRAIN_SIZE) + (size / TERRAIN_SIZE);

  startx = std::max(0, startx);
  startz = std::max(0, startz);
  endx = std::min(TERRAIN_WIDTH - 1, endx);
  endz = std::min(TERRAIN_DEPTH - 1, endz);

  int i, t;

  vector cur_vec;
  vector up_vec = {0, 1, 0};

  local_pos.y = 0;

  cur_vec.x = startx * TERRAIN_SIZE;
  cur_vec.y = 0;
  cur_vec.z = startz * TERRAIN_SIZE;

  float max_dist = vm_VectorDistanceQuick(&local_pos, &cur_vec);

  for (i = startz; i <= endz; i++, cur_vec.z += TERRAIN_SIZE) {
    cur_vec.x = startx * TERRAIN_SIZE;
    for (t = startx; t <= endx; t++, cur_vec.x += TERRAIN_SIZE) {
      terrain_segment *tseg = &Terrain_seg[i * TERRAIN_WIDTH + t];

      if ((up_vec * TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal1) < .5)
        continue; // not flat enough
      if ((up_vec * TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal2) < .5)
        continue; // not flat enough

      float dist = 1.0 - (vm_VectorDistanceQuick(&local_pos, &cur_vec) / max_dist);

      int height_change = -(dist * (float)depth);
      int light_change = height_change * 2;

      DeformTerrainPoint(t, i, height_change);

      tseg->r = std::max(0, tseg->r + light_change);
      tseg->g = std::max(0, tseg->g + light_change);
      tseg->b = std::max(0, tseg->b + light_change);

      int which = ((i / 128) * 2) + (t / 128);
      changed[which] = 1;
    }
  }

  int div = (1 << (MAX_TERRAIN_LOD - 1));

  startx /= div;
  startz /= div;
  endx /= div;
  endz /= div;

  GenerateSingleLODDelta(startx, startz);
  GenerateSingleLODDelta(endx, startz);
  GenerateSingleLODDelta(endx, endz);
  GenerateSingleLODDelta(startx, endz);

  for (i = 0; i < 4; i++) {
    if (changed[i])
      UpdateSingleTerrainLightmap(i);
  }
}

// Builds normals for the currently loaded terrain
void BuildTerrainNormals() {
  int i, t, l, z, x;
  vector a, b, c;
  int simplemul;
  vector up_norm = {0, 1.0, 0};

  // Set all to be initially up
  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    TerrainNormals[MAX_TERRAIN_LOD - 1][i].normal1 = up_norm;
    TerrainNormals[MAX_TERRAIN_LOD - 1][i].normal2 = up_norm;
  }

  for (l = MAX_TERRAIN_LOD - 1; l < MAX_TERRAIN_LOD; l++) {
    simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - l);

    for (z = 0, i = 0; i < TERRAIN_DEPTH - simplemul; i += simplemul, z++) {
      for (x = 0, t = 0; t < TERRAIN_WIDTH - simplemul; t += simplemul, x++) {
        terrain_segment *tseg = &Terrain_seg[i * TERRAIN_WIDTH + t];
        terrain_segment *tseg0 = &Terrain_seg[i * TERRAIN_WIDTH + t];
        terrain_segment *tseg1 = &Terrain_seg[(i + simplemul) * TERRAIN_WIDTH + t];
        terrain_segment *tseg2 = &Terrain_seg[((i + simplemul) * TERRAIN_WIDTH) + t + simplemul];
        terrain_segment *tseg3 = &Terrain_seg[(i * TERRAIN_WIDTH) + t + simplemul];

        // Do upper left triangle
        a.x = t * TERRAIN_SIZE;
        a.y = tseg0->y;
        a.z = i * TERRAIN_SIZE;

        b.x = t * TERRAIN_SIZE;
        b.y = tseg1->y;
        b.z = (i + simplemul) * TERRAIN_SIZE;

        c.x = (t + simplemul) * TERRAIN_SIZE;
        c.y = tseg2->y;
        c.z = (i + simplemul) * TERRAIN_SIZE;

        vm_GetNormal(&TerrainNormals[l][z * (TERRAIN_WIDTH / simplemul) + x].normal1, &a, &b, &c);

        // Now do lower right triangle
        a.x = t * TERRAIN_SIZE;
        a.y = tseg0->y;
        a.z = i * TERRAIN_SIZE;

        b.x = (t + simplemul) * TERRAIN_SIZE;
        b.y = tseg2->y;
        b.z = (i + simplemul) * TERRAIN_SIZE;

        c.x = (t + simplemul) * TERRAIN_SIZE;
        c.y = tseg3->y;
        c.z = (i)*TERRAIN_SIZE;

        vm_GetNormal(&TerrainNormals[l][z * (TERRAIN_WIDTH / simplemul) + x].normal2, &a, &b, &c);
      }
    }
  }
}

void GenerateTerrainLight() {
  // Generates a lighting value for every terrain cell
  int i;

  GenerateLightSource();

  vector camera_light = Terrain_sky.lightsource;

  vm_NormalizeVector(&camera_light);

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    float dp = (-vm_DotProduct(&camera_light, &TerrainNormals[MAX_TERRAIN_LOD - 1][i].normal1) + 1.0) / 2;
    Terrain_seg[i].l = Float_to_ubyte(dp);
    Terrain_seg[i].r = Terrain_seg[i].l;
    Terrain_seg[i].g = Terrain_seg[i].l;
    Terrain_seg[i].b = Terrain_seg[i].l;
  }

  UpdateTerrainLightmaps();
}

void CloseTerrain(void) {
  int i;

  for (i = MAX_TERRAIN_LOD - 1; i < MAX_TERRAIN_LOD; i++)
    mem_free(TerrainNormals[i]);

  for (i = 0; i < 7; i++) {
    if (Terrain_min_height_int[i])
      mem_free(Terrain_min_height_int[i]);
    if (Terrain_max_height_int[i])
      mem_free(Terrain_max_height_int[i]);
  }

  if (!Dedicated_server) {
    mem_free(Terrain_rotate_list);
    mem_free(World_point_buffer);

    for (i = 0; i < MAX_TERRAIN_LOD - 1; i++)
      mem_free(TerrainDeltaBlocks[i]);
  }
}

// Given a 3space triplet, computes the u,v coords for a texture map at that position
// on a sphere.
void SphereMap(float x, float y, float z, float radius, float *u, float *v, int h) {
  if (y < 0)
    Int3();

  float fh = h;

  // produces u from 0 to 1
  *u = fh / (65536.0 / 16.005); // account for floating point precision error

  *v = acos(y / radius) / (PI / 2); // v=.5 to 1
  *v /= .5;                         // v=1 to 2
  *v -= 1;                          // v=0 to 1
}

void SetupSkyTexture() {

  int first_top_texture;

  // Find first sky texture
  first_top_texture = FindTextureName("CloudySky");
  if (first_top_texture < 0)
    first_top_texture = 0;

  Terrain_sky.dome_texture = first_top_texture;

  // Figure out the sky color

  Terrain_sky.sky_color = GR_RGB(0, 0, 255);

  if (!Terrain_sky.textured)
    Terrain_sky.sky_color = GR_RGB(8, 0, 32);
  Terrain_sky.fog_color = GR_RGB(4, 0, 16);
  Terrain_sky.horizon_color = GR_RGB(128, 32, 32);
  Terrain_sky.textured = 1;
  Terrain_sky.rotate_rate = 0;
}

// Compute a parametric sphere for our sky.
void SetupSky(float radius, int flags, uint8_t randit) {
  int jump = 65536 / MAX_HORIZON_PIECES;
  int top = ((65536 / 4) * 3) + (65536 / 8);

  int i, t;

  Terrain_sky.radius = radius;
  Terrain_sky.flags = flags;

  int horizon_r = GR_COLOR_RED(Terrain_sky.horizon_color);
  int horizon_g = GR_COLOR_GREEN(Terrain_sky.horizon_color);
  int horizon_b = GR_COLOR_BLUE(Terrain_sky.horizon_color);

  float rad_diff = radius - SKY_RADIUS;

  // Figure out where our points in the inside of the sphere are
  for (i = 0; i < 6; i++) {
    const int increment = 16384 / 5;
    const angle pitch = (65536 - 16384) + (i * increment);

    for (t = 0; t < MAX_HORIZON_PIECES; t++) {
      vector *vec = &Terrain_sky.horizon_vectors[t][i];

      matrix tempm;
      vm_AnglesToMatrix(&tempm, pitch, t * jump, 0);
      vm_ScaleVector(vec, &tempm.fvec, SKY_RADIUS / 2);

      vec->y -= MAX_TERRAIN_HEIGHT;
      vec->y += (rad_diff / 4);
    }
  }

  // Now figure out texture UVS
  for (i = 0; i < 5; i++) {
    float scalar = (float)i / 4.0;
    int angle_increment = 65536 / MAX_HORIZON_PIECES;
    for (t = 0; t < MAX_HORIZON_PIECES; t++) {
      float cur_sin = FixSin(t * angle_increment) * scalar;
      float cur_cos = FixCos(t * angle_increment) * scalar;

      cur_sin = (cur_sin + 1) / 2;
      cur_cos = (cur_cos + 1) / 2;

      Terrain_sky.horizon_u[t][i] = cur_cos;
      Terrain_sky.horizon_v[t][i] = cur_sin;
    }
  }

  int highcount = 0; // keep track of what stars are close to the top of the sphere
                     // don't draw too many of them
  if (!randit)
    return;

  for (i = 0; i < MAX_STARS; i++) {
    vector starvec;
    matrix tempm;
    int p;
    top = ((65536 / 4) * 3);
    int highlimit = MAX_STARS / 8;

    p = ps_rand() % (65336 / 4);

    while (highcount > highlimit && p < 6000)
      p = ps_rand() % (65336 / 4);

    if (p < 6000)
      highcount++;

    vm_AnglesToMatrix(&tempm, (top + p) % 65336, (ps_rand() * ps_rand()) % 65536, 0);
    vm_ScaleVector(&starvec, &tempm.fvec, Terrain_sky.radius * 500);
    Terrain_sky.star_vectors[i] = starvec;

    // Now figure out the color of this star.  The closer to horizon it is, the
    // dimmer it is
    float ynorm = starvec.y / (Terrain_sky.radius * 500);

    float color_norm = ynorm * 2;
    color_norm = std::clamp(color_norm, 0.2f, 1.0f);
    int color = ps_rand() % 6;
    int r, g, b;

    if (color <= 2) {
      r = 255;
      g = 255;
      b = 255;
    } else if (color == 3) {
      r = 255;
      g = 200;
      b = 200;
    } else if (color == 4) {
      r = 255;
      g = 200;
      b = 255;
    } else {
      r = 255;
      g = 255;
      b = 200;
    }

    r = ((1.0 - color_norm) * horizon_r) + (color_norm * r);
    g = ((1.0 - color_norm) * horizon_g) + (color_norm * g);
    b = ((1.0 - color_norm) * horizon_b) + (color_norm * b);

    Terrain_sky.star_color[i] = GR_RGB(r, g, b);
  }

  for (i = 0; i < MAX_SATELLITES; i++) {
    vector satellitevec;
    matrix tempm;

    int p = ps_rand() % (65336 / 8);
    top = ((65536 / 4) * 3) + (4096); // don't do satellites that are straight up

    vm_AnglesToMatrix(&tempm, (top + p) % 65336, (ps_rand() * ps_rand()) % 65536, 0);
    vm_ScaleVector(&satellitevec, &tempm.fvec, Terrain_sky.radius * 3);
    Terrain_sky.satellite_vectors[i] = satellitevec;
    Terrain_sky.satellite_size[i] = 500;
  }
}

// Loads a pcx bitmap to be used as a height map
int LoadPCXTerrain(char *filename) {
  CFILE *infile;
  int run = 0, i, total, j, n;
  int16_t xmin, ymin, xmax, ymax;
  int width, height;
  uint8_t buf;
  uint8_t *lando;

  if ((infile = cfopen(filename, "rb")) == NULL)
    return (0);

  cf_ReadInt(infile);
  xmin = cf_ReadShort(infile);
  ymin = cf_ReadShort(infile);
  xmax = cf_ReadShort(infile);
  ymax = cf_ReadShort(infile);

  for (n = 0; n < 116; n++)
    cf_ReadByte(infile);

  width = 1 + xmax - xmin;
  height = 1 + ymax - ymin;

  total = width * height;

  lando = (uint8_t *)mem_malloc(total);

  mprintf(0, "Heightmap is %d x %d\n", width, height);

  while (run < total) {
    buf = cf_ReadByte(infile);
    if (buf >= 192) {
      uint8_t tb = 0;
      tb = cf_ReadByte(infile);
      for (i = 0; i < (buf - 192); i++, run++)
        lando[run] = tb;
    } else {
      lando[run] = buf;
      run++;
    }
  }

  cfclose(infile);

  for (i = 0; i < TERRAIN_DEPTH; i++)
    for (j = 0; j < TERRAIN_WIDTH; j++) {
      n = (int)lando[((i % height) * width) + (j % width)];

      Terrain_seg[((TERRAIN_WIDTH - 1) - i) * TERRAIN_WIDTH + j].ypos = n;
    }

  mem_free(lando);
  BuildMinMaxTerrain();
  BuildTerrainNormals();
  GenerateTerrainLight();

#if (defined(EDITOR) || defined(NEWEDITOR))
  memset(TerrainSelected, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);
  Num_terrain_selected = 0;
  World_changed = 1;
#endif

  return (1);
}

// Called whenever a new level is initted
void ResetTerrain(int force) {
  int i, t;
  int tex_index = FindTextureName("RainbowTexture");

  if (tex_index < 0)
    tex_index = 4; // stuff some random value

  for (i = 0; i < TERRAIN_DEPTH; i++) {
    for (t = 0; t < TERRAIN_WIDTH; t++) {
#if (!defined(RELEASE) || defined(NEWEDITOR))
      Terrain_seg_render_objs[i * TERRAIN_WIDTH + t] = -1;
#endif
      Terrain_seg[i * TERRAIN_WIDTH + t].objects = -1;
      Terrain_seg[i * TERRAIN_WIDTH + t].flags = 0;
      Terrain_seg[i * TERRAIN_WIDTH + t].lm_quad = ((i / 128) * 2) + (t / 128);
      Terrain_seg[i * TERRAIN_WIDTH + t].texseg_index = ((i >> 3) * TERRAIN_TEX_WIDTH) + (t >> 3);

      Terrain_dynamic_table[i * TERRAIN_WIDTH + t] = 0xFF;
    }
  }

  for (i = 0; i < TERRAIN_TEX_DEPTH; i++) {
    for (t = 0; t < TERRAIN_TEX_WIDTH; t++) {
      int s = i * TERRAIN_TEX_WIDTH + t;
      Terrain_tex_seg[s].tex_index = tex_index;
      Terrain_tex_seg[s].rotation = (1 << 4);
    }
  }

  if (force) {
    Terrain_checksum = -1;

    for (i = 0; i < TERRAIN_DEPTH; i++) {
      for (t = 0; t < TERRAIN_WIDTH; t++) {
        Terrain_seg[i * TERRAIN_WIDTH + t].y = 0;
        Terrain_seg[i * TERRAIN_WIDTH + t].ypos = 0;
      }
    }

    for (i = 0; i < 7; i++) {
      int size = 1 << i;
      memset(Terrain_min_height_int[i], 0, size * size);
      memset(Terrain_max_height_int[i], 0, size * size);
    }

    if (!Dedicated_server) {
      for (i = 0; i < MAX_TERRAIN_LOD - 1; i++) {
        int w = TERRAIN_WIDTH >> ((MAX_TERRAIN_LOD - 1) - i);
        int h = TERRAIN_DEPTH >> ((MAX_TERRAIN_LOD - 1) - i);

        memset(TerrainDeltaBlocks[i], 0, w * h * sizeof(float));
      }
    }
  }

  BuildTerrainNormals();

  for (i = 0; i < MAX_SATELLITES; i++) {
    Terrain_sky.satellite_texture[i] = 111;
    Terrain_sky.satellite_flags[i] = 0;
  }

  GenerateTerrainLight();

#if (defined(EDITOR) || defined(NEWEDITOR))
  memset(TerrainSelected, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);
#endif

  memset(TerrainJoinMap, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);

  Terrain_sky.damage_per_second = 0;
  Terrain_sky.fog_scalar = .85f;
  SetupSkyTexture();
  ResetWeather();
}

// Takes our 1st satellite and fills in the appropriate values in the lightsource vector
void GenerateLightSource() {
  Terrain_sky.lightsource.x = FixCos(Terrain_sky.lightangle);
  Terrain_sky.lightsource.z = FixSin(Terrain_sky.lightangle);
}

void InitTerrain(void) {
  int i, w, h, t;

  // set sky texture to unused
  Terrain_sky.textured = 0;

  // Setup stuff for rendering
  if (!Dedicated_server) {
    Terrain_rotate_list = (uint16_t *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH * sizeof(uint16_t));
    ASSERT(Terrain_rotate_list);

    World_point_buffer = (g3Point *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH * sizeof(g3Point));
    ASSERT(World_point_buffer);

    // Allocate space for lod delta tree and unique texture IDs
    for (i = 0; i < MAX_TERRAIN_LOD - 1; i++) {
      w = TERRAIN_WIDTH >> ((MAX_TERRAIN_LOD - 1) - i);
      h = TERRAIN_DEPTH >> ((MAX_TERRAIN_LOD - 1) - i);

      TerrainDeltaBlocks[i] = (float *)mem_malloc(w * h * sizeof(float));
    }
  }

  // Allocate space for lod normals

  for (i = MAX_TERRAIN_LOD - 1; i < MAX_TERRAIN_LOD; i++) {
    w = TERRAIN_WIDTH >> ((MAX_TERRAIN_LOD - 1) - i);
    h = TERRAIN_DEPTH >> ((MAX_TERRAIN_LOD - 1) - i);

    TerrainNormals[i] = (terrain_normals *)mem_malloc(w * h * sizeof(terrain_normals));
    memset(TerrainNormals[i], 0, w * h * sizeof(terrain_normals));
  }

  // Allocate space for our min/max tables
  for (i = 0; i < 7; i++) {
    w = 1 << i;
    h = 1 << i;

    // Index 1 cuts the whole thing into 4ths, index 2 into 8ths, etc
    Terrain_min_height_int[i] = (uint8_t *)mem_malloc(w * h * sizeof(uint8_t));
    Terrain_max_height_int[i] = (uint8_t *)mem_malloc(w * h * sizeof(uint8_t));

    ASSERT(Terrain_min_height_int[i] != NULL);
    ASSERT(Terrain_max_height_int[i] != NULL);
  }

  Terrain_sky.lightangle = 0;
  Terrain_sky.num_satellites = 1;
  Terrain_sky.damage_per_second = 0;

  SetupSky(SKY_RADIUS, TF_STARS | TF_SATELLITES, 1);
  GenerateLightSource();

  for (i = 0; i < 4; i++) {
    TerrainLightmaps[i] = lm_AllocLightmap(128, 128);
    ASSERT(TerrainLightmaps[i] != BAD_LM_INDEX);
    GameLightmaps[TerrainLightmaps[i]].flags |= LF_WRAP;
  }

  for (i = 0; i < MAX_TERRAIN_LOD; i++) {
    int simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - i);
    int answer;

    TerrainEdgeJump[i] = simplemul;

    for (t = 0; t < 16; t++) {
      if (t == 0)
        answer = 1;
      else {
        if (t % simplemul == 0)
          answer = 1;
        else
          answer = 0;
      }
      TerrainEdgeTest[i][t] = answer;
    }
  }

  // Setup dome textures
  Terrain_sky.dome_texture = 0;

  atexit(CloseTerrain);
}

void UpdateSingleTerrainLightmap(int which) {
  int w = lm_w(TerrainLightmaps[which]);
  int i, t;

  GameLightmaps[TerrainLightmaps[which]].flags |= LF_CHANGED;

  int sx = (which % 2) * 128;
  int sz = (which / 2) * 128;

  for (i = sz; i < sz + 128; i++) {
    for (t = sx; t < sx + 128; t++) {
      int tseg = i * TERRAIN_WIDTH + t;
      terrain_segment *tp = &Terrain_seg[tseg];

      uint16_t color = GR_RGB16(tp->r, tp->g, tp->b);
      uint16_t *data = lm_data(TerrainLightmaps[which]);

      int x = t % 128;
      int y = 127 - (i % 128);

      data[y * w + x] = OPAQUE_FLAG | color;
    }
  }
}

// Generates lightmaps based on the info given by the .light field of each Terrain_seg
void UpdateTerrainLightmaps() {
  int i, t;

  // First make the wraparounds work right

  // lower-left strip
  for (i = 0; i < 128; i++) {
    Terrain_seg[i * TERRAIN_WIDTH].r = Terrain_seg[i * TERRAIN_WIDTH + 128].r;
    Terrain_seg[i * TERRAIN_WIDTH].g = Terrain_seg[i * TERRAIN_WIDTH + 128].g;
    Terrain_seg[i * TERRAIN_WIDTH].b = Terrain_seg[i * TERRAIN_WIDTH + 128].b;

    Terrain_seg[i].r = Terrain_seg[128 * TERRAIN_WIDTH + i].r;
    Terrain_seg[i].g = Terrain_seg[128 * TERRAIN_WIDTH + i].g;
    Terrain_seg[i].b = Terrain_seg[128 * TERRAIN_WIDTH + i].b;
  }

  // lower-right strip
  for (i = 0; i < 128; i++) {
    Terrain_seg[i * TERRAIN_WIDTH + 255].r = Terrain_seg[i * TERRAIN_WIDTH + 127].r;
    Terrain_seg[i * TERRAIN_WIDTH + 255].g = Terrain_seg[i * TERRAIN_WIDTH + 127].g;
    Terrain_seg[i * TERRAIN_WIDTH + 255].b = Terrain_seg[i * TERRAIN_WIDTH + 127].b;

    Terrain_seg[i + 128].r = Terrain_seg[128 * TERRAIN_WIDTH + i + 128].r;
    Terrain_seg[i + 128].g = Terrain_seg[128 * TERRAIN_WIDTH + i + 128].g;
    Terrain_seg[i + 128].b = Terrain_seg[128 * TERRAIN_WIDTH + i + 128].b;
  }

  // upper-left strip
  for (i = 0; i < 128; i++) {
    Terrain_seg[(i + 128) * TERRAIN_WIDTH].r = Terrain_seg[(i + 128) * TERRAIN_WIDTH + 128].r;
    Terrain_seg[(i + 128) * TERRAIN_WIDTH].g = Terrain_seg[(i + 128) * TERRAIN_WIDTH + 128].g;
    Terrain_seg[(i + 128) * TERRAIN_WIDTH].b = Terrain_seg[(i + 128) * TERRAIN_WIDTH + 128].b;

    Terrain_seg[255 * TERRAIN_WIDTH + i].r = Terrain_seg[127 * TERRAIN_WIDTH + i].r;
    Terrain_seg[255 * TERRAIN_WIDTH + i].g = Terrain_seg[127 * TERRAIN_WIDTH + i].g;
    Terrain_seg[255 * TERRAIN_WIDTH + i].b = Terrain_seg[127 * TERRAIN_WIDTH + i].b;
  }

  // upper-right strip
  for (i = 0; i < 128; i++) {
    Terrain_seg[(i + 128) * TERRAIN_WIDTH + 255].r = Terrain_seg[(i + 128) * TERRAIN_WIDTH + 127].r;
    Terrain_seg[(i + 128) * TERRAIN_WIDTH + 255].g = Terrain_seg[(i + 128) * TERRAIN_WIDTH + 127].g;
    Terrain_seg[(i + 128) * TERRAIN_WIDTH + 255].b = Terrain_seg[(i + 128) * TERRAIN_WIDTH + 127].b;

    Terrain_seg[255 * TERRAIN_WIDTH + i + 128].r = Terrain_seg[127 * TERRAIN_WIDTH + i + 128].r;
    Terrain_seg[255 * TERRAIN_WIDTH + i + 128].g = Terrain_seg[127 * TERRAIN_WIDTH + i + 128].g;
    Terrain_seg[255 * TERRAIN_WIDTH + i + 128].b = Terrain_seg[127 * TERRAIN_WIDTH + i + 128].b;
  }

  int w = lm_w(TerrainLightmaps[0]);

  for (i = 0; i < TERRAIN_DEPTH; i++) {
    for (t = 0; t < TERRAIN_WIDTH; t++) {
      int tseg = i * TERRAIN_WIDTH + t;
      terrain_segment *tp = &Terrain_seg[tseg];
      int x = t % 128;
      int y = 127 - (i % 128);
      int which = ((i / 128) * 2) + (t / 128);

      uint16_t color = GR_RGB16(tp->r, tp->g, tp->b);
      uint16_t *data = lm_data(TerrainLightmaps[which]);

      data[y * w + x] = OPAQUE_FLAG | color;
    }
  }

  for (i = 0; i < 4; i++) {
    GameLightmaps[TerrainLightmaps[i]].flags |= LF_CHANGED;
    GameLightmaps[TerrainLightmaps[i]].flags &= ~LF_LIMITS;
  }
}

// Builds the surface normal for terrain segment n
void BuildNormalForTerrainSegment(int n) {
  int i, t;

  vector a, b, c;

  if (n < 0 || n >= (TERRAIN_WIDTH - 1) * (TERRAIN_DEPTH - 1))
    return;

  i = n / TERRAIN_WIDTH;
  t = n % TERRAIN_WIDTH;

  a.x = t * TERRAIN_SIZE;
  a.y = Terrain_seg[(i * TERRAIN_WIDTH) + (t)].y;
  a.z = i * TERRAIN_SIZE;

  b.x = t * TERRAIN_SIZE;
  b.y = Terrain_seg[(i * TERRAIN_WIDTH) + (t + TERRAIN_WIDTH)].y;
  b.z = (i + 1) * TERRAIN_SIZE;

  c.x = (t + 1) * TERRAIN_SIZE;
  c.y = Terrain_seg[(i * TERRAIN_WIDTH) + (t + TERRAIN_WIDTH + 1)].y;
  c.z = (i + 1) * TERRAIN_SIZE;

  vm_GetNormal(&TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal1, &a, &b, &c);

  a.x = t * TERRAIN_SIZE;
  a.y = Terrain_seg[(i * TERRAIN_WIDTH) + (t)].y;
  a.z = i * TERRAIN_SIZE;

  b.x = (t + 1) * TERRAIN_SIZE;
  b.y = Terrain_seg[(i * TERRAIN_WIDTH) + (t + TERRAIN_WIDTH + 1)].y;
  b.z = (i + 1) * TERRAIN_SIZE;

  c.x = (t + 1) * TERRAIN_SIZE;
  c.y = Terrain_seg[(i * TERRAIN_WIDTH) + (t + 1)].y;
  c.z = (i)*TERRAIN_SIZE;

  vm_GetNormal(&TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal2, &a, &b, &c);
}

// Builds the vertex normal for terrain segment n
void BuildLightingNormalForSegment(int n) {
  int i, t, hback, vback;
  vector temp;

  if (n < 0 || n >= (TERRAIN_WIDTH - 1) * (TERRAIN_DEPTH - 1))
    return;

  i = n / TERRAIN_WIDTH;
  t = n % TERRAIN_WIDTH;

  if (i == 0)
    vback = TERRAIN_DEPTH - 1;
  else
    vback = i - 1;

  if (t == 0)
    hback = TERRAIN_WIDTH - 1;
  else
    hback = t - 1;

  vm_MakeZero(&temp);

  vm_AddVectors(&temp, &temp, &TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + hback].normal2);
  vm_AddVectors(&temp, &temp, &TerrainNormals[MAX_TERRAIN_LOD - 1][i * TERRAIN_WIDTH + t].normal2);
  vm_AddVectors(&temp, &temp, &TerrainNormals[MAX_TERRAIN_LOD - 1][(vback)*TERRAIN_WIDTH + hback].normal1);
  vm_AddVectors(&temp, &temp, &TerrainNormals[MAX_TERRAIN_LOD - 1][(vback)*TERRAIN_WIDTH + t].normal2);

  vm_AverageVector(&temp, 4);
  //	vm_NormalizeVectorFast (&temp);
}
