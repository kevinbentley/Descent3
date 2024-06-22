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

// Lightmap info
#include "pstypes.h"

#include "lightmap_info.h"
#include "lightmap.h"
#include "mono.h"
#include "ddgr.h"
#include "grdefs.h"
#include "renderer.h"
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "dedicated_server.h"

int Num_of_lightmap_info = 0;
lightmap_info *LightmapInfo = NULL;

static uint16_t *Free_lmi_list = NULL;

void CloseLightmapInfos() {
  bool final_lightmap = true;

  if (LightmapInfo)
    mem_free(LightmapInfo);

  if (Free_lmi_list)
    mem_free(Free_lmi_list);

  LightmapInfo = NULL;
  Free_lmi_list = NULL;
}

// Sets all the lightmaps to unused
void InitLightmapInfo(int nummaps) {
  int i;

  if (Dedicated_server)
    return;

  if (nummaps == 0) {
    LightmapInfo = (lightmap_info *)mem_malloc(MAX_LIGHTMAP_INFOS * sizeof(lightmap_info));
    ASSERT(LightmapInfo);
    Free_lmi_list = (uint16_t *)mem_malloc(MAX_LIGHTMAP_INFOS * sizeof(uint16_t));
    ASSERT(Free_lmi_list);

    for (i = 0; i < MAX_LIGHTMAP_INFOS; i++) {
      LightmapInfo[i].used = 0;
      Free_lmi_list[i] = i;
    }
  }
  /* //DAJ this did not work! the lm_FreeLightmap() is refcount-- not a free()
                  else {
                  LightmapInfo=(lightmap_info *)mem_malloc (nummaps*sizeof(lightmap_info));
                  ASSERT (LightmapInfo);
                  Free_lmi_list=(uint16_t *)mem_malloc (nummaps*sizeof(uint16_t));
                  ASSERT (Free_lmi_list);


                  for (i=0;i<nummaps;i++)
                  {
                          LightmapInfo[i].used=0;
                          Free_lmi_list[i]=i;
                  }
          }
  */
  Num_of_lightmap_info = 0;
  atexit(CloseLightmapInfos);
}
// Allocs a lightmap of w x h size
// Returns lightmap handle if successful, -1 if otherwise

int AllocLightmapInfo(int w, int h, int type, bool alloc_lightmap) {
  int n, i;

  if (Dedicated_server)
    Int3(); // Shouldn't be here!

  if (Num_of_lightmap_info > MAX_LIGHTMAP_INFOS)
    Int3(); // Get Jason, ran out of lightmaps!

  n = Free_lmi_list[Num_of_lightmap_info++];
  ASSERT(LightmapInfo[n].used == 0);

  ASSERT(n >= 0 && n < MAX_LIGHTMAP_INFOS);

  /*for (i=Highest_lmi_index;i<MAX_LIGHTMAP_INFOS;i++)
  {
          if (LightmapInfo[i].used==0)
          {
                  n=i;
                  break;
          }
  }*/

  // If we can't find a free slot in which to alloc, bail out
  /*if (i==MAX_LIGHTMAP_INFOS)
  {
          Int3();
          mprintf(0,"ERROR! Couldn't find a free lightmap info to alloc!\n");
          return -1;
  }*/

  memset(&LightmapInfo[n], 0, sizeof(lightmap_info));

  ASSERT(w >= 2 && h >= 2);

  if (alloc_lightmap) {
    LightmapInfo[n].lm_handle = lm_AllocLightmap(w, h);
    ASSERT(LightmapInfo[n].lm_handle != BAD_LM_INDEX); // Make sure we have a valid lightmap

    uint16_t *dest_data = lm_data(LightmapInfo[n].lm_handle);

    // Set the lightmap to be transparent
    for (i = 0; i < w * h; i++)
      dest_data[i] = NEW_TRANSPARENT_COLOR;
  }

  LightmapInfo[n].used = 1;
  LightmapInfo[n].type = type;
  LightmapInfo[n].dynamic = BAD_LM_INDEX;
  LightmapInfo[n].spec_map = -1;
  LightmapInfo[n].width = w;
  LightmapInfo[n].height = h;
  LightmapInfo[n].x1 = 0;
  LightmapInfo[n].y1 = 0;

  return n;
}

// Given a handle, frees the lightmap memory and flags this lightmap as unused
void FreeLightmapInfo(int handle) {
  ASSERT(handle >= 0 && handle <= MAX_LIGHTMAP_INFOS);

  if (Dedicated_server)
    return;

  // when we free up our rooms, which frees up lightmaps, the lightmap array
  // may already be freed
  if (!LightmapInfo)
    return;

  if (LightmapInfo[handle].used < 1)
    return;

  LightmapInfo[handle].used--;

  if (LightmapInfo[handle].used == 0) {
    if (!Dedicated_server)
      rend_FreePreUploadedTexture(LightmapInfo[handle].lm_handle, MAP_TYPE_LIGHTMAP);
    lm_FreeLightmap(LightmapInfo[handle].lm_handle);

    Free_lmi_list[--Num_of_lightmap_info] = handle;
  }
}

// Gets the width of this lightmap_info handle
int lmi_w(int handle) {
  if (!LightmapInfo[handle].used) {
    Int3(); // Get Jason
    return 0;
  }

  return (LightmapInfo[handle].width);
}

// Gets the height of this lightmap_info handle
int lmi_h(int handle) {
  if (!LightmapInfo[handle].used) {
    Int3(); // Get Jason
    return 0;
  }

  return (LightmapInfo[handle].height);
}

// TODO: MTS: unused?
// Softens the edges of lightmaps so there are fewer artifaces
void ShadeLightmapInfoEdges(int type) {
  int i;

  for (i = 0; i < MAX_LIGHTMAP_INFOS; i++) {
    if (LightmapInfo[i].used && LightmapInfo[i].type == type) {
      uint16_t *src_data;
      uint16_t *dest_data = lm_data(LightmapInfo[i].lm_handle);
      int w = lmi_w(i);
      int h = lmi_h(i);
      int x, y;

      src_data = (uint16_t *)mem_malloc(w * h * 2);
      ASSERT(src_data);

      memcpy(src_data, dest_data, w * h * 2);

      for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
          if (!(src_data[y * w + x] & OPAQUE_FLAG)) {
            int r = 0, g = 0, b = 0;
            int num = 0;
            ddgr_color color;
            uint16_t color16;

            // Left edge
            if (x != 0) {

              color16 = src_data[y * w + (x - 1)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }

              if (y != 0) {
                color16 = src_data[(y - 1) * w + (x - 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }

              if (y != h - 1) {
                color16 = src_data[(y + 1) * w + (x - 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }
            }

            // Right edge
            if (x != (w - 1)) {

              color16 = src_data[y * w + (x + 1)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }

              if (y != 0) {
                color16 = src_data[(y - 1) * w + (x + 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }

              if (y != h - 1) {
                color16 = src_data[(y + 1) * w + (x + 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }
            }

            if (y != 0) {
              color16 = src_data[(y - 1) * w + (x)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }
            }
            if (y != h - 1) {
              color16 = src_data[(y + 1) * w + (x)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }
            }

            if (num > 0) {
              r /= num;
              g /= num;
              b /= num;
              color16 = GR_RGB16(r, g, b);
              dest_data[y * w + x] = OPAQUE_FLAG | color16;
            }
          }
        }
      }
      mem_free(src_data);
    }
  }
}

// TODO: MTS: unused?
// Blurs the lightmaps so a dithering pattern is less noticeable
void BlurLightmapInfos(int type) {
  int i;

  for (i = 0; i < MAX_LIGHTMAP_INFOS; i++) {
    if (LightmapInfo[i].used && LightmapInfo[i].type == type) {
      uint16_t *src_data;
      uint16_t *dest_data = lm_data(LightmapInfo[i].lm_handle);
      int w = lmi_w(i);
      int h = lmi_h(i);
      int x, y;

      src_data = (uint16_t *)mem_malloc(w * h * 2);
      ASSERT(src_data);

      memcpy(src_data, dest_data, w * h * 2);

      for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
          if (src_data[y * w + x] & OPAQUE_FLAG) {
            int r = 0, g = 0, b = 0;
            int num = 0;
            ddgr_color color;
            uint16_t color16;

            color16 = src_data[y * w + (x)];
            color = GR_16_TO_COLOR(color16);
            r += GR_COLOR_RED(color);
            g += GR_COLOR_GREEN(color);
            b += GR_COLOR_BLUE(color);
            num++;

            // Left edge
            if (x != 0) {

              color16 = src_data[y * w + (x - 1)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }

              if (y != 0) {
                color16 = src_data[(y - 1) * w + (x - 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }

              if (y != h - 1) {
                color16 = src_data[(y + 1) * w + (x - 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }
            }

            // Right edge
            if (x != (w - 1)) {

              color16 = src_data[y * w + (x + 1)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }

              if (y != 0) {
                color16 = src_data[(y - 1) * w + (x + 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }

              if (y != h - 1) {
                color16 = src_data[(y + 1) * w + (x + 1)];
                if (color16 & OPAQUE_FLAG) {
                  color = GR_16_TO_COLOR(color16);
                  r += GR_COLOR_RED(color);
                  g += GR_COLOR_GREEN(color);
                  b += GR_COLOR_BLUE(color);
                  num++;
                }
              }
            }

            if (y != 0) {
              color16 = src_data[(y - 1) * w + (x)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }
            }
            if (y != h - 1) {
              color16 = src_data[(y + 1) * w + (x)];
              if (color16 & OPAQUE_FLAG) {
                color = GR_16_TO_COLOR(color16);
                r += GR_COLOR_RED(color);
                g += GR_COLOR_GREEN(color);
                b += GR_COLOR_BLUE(color);
                num++;
              }
            }

            if (num > 0) {
              r /= num;
              g /= num;
              b /= num;
              color16 = GR_RGB16(r, g, b);
              dest_data[y * w + x] = OPAQUE_FLAG | color16;
            }
          }
        }
      }
      mem_free(src_data);
    }
  }
}
