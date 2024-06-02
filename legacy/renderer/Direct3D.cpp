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

#include <windows.h>
#include "DDAccess.h" // This module has access to machine-dependent variables.
#include "pstypes.h"
#include "pserror.h"
#include "application.h"
#include "renderer.h"
#include "3d.h"
#include "bitmap.h"
#include "lightmap.h"
#include "rend_d3d.h"
#include "d3dtypes.h"
#include "d3d.h"
#include "ddraw.h"
#include "grdefs.h"
#include "module.h"
#include "bumpmap.h"
#include "mem.h"
#include "rtperformance.h"
#include "appdatabase.h"

#include <algorithm>

static oeApplication *ParentApplication;

extern int FindArg(const char *);

extern oeAppDatabase *Database;

rendering_state D3D_state = {0}; // set initted to zero
renderer_preferred_state D3D_preferred_state = {0, 1, 1.5};

int D3D_polys_drawn = 0;
int D3D_verts_processed = 0;
int D3D_sets_this_frame[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int D3D_uploads = 0;
int D3D_num_texelfx = 0;
static int D3D_last_frame_polys_drawn = 0;
static int D3D_last_frame_verts_processed = 0;
static int D3D_last_uploads = 0;

#define NUM_TEXTURE_CLASSES 8

// Specific DirectDraw/Direct3D variables
LPDIRECTDRAW lpDD1 = NULL;
LPDIRECTDRAW4 lpDD = NULL;
LPDIRECT3D3 lpD3D = NULL;
LPDIRECT3DDEVICE3 lpD3DDevice = NULL;
LPDIRECT3DDEVICE lpD3DDeviceEB = NULL;
LPDIRECTDRAWSURFACE4 lpBackBuffer = NULL;
LPDIRECTDRAWSURFACE4 lpFrontBuffer = NULL;
LPDIRECTDRAWSURFACE4 lpZBuffer = NULL;
LPDIRECTDRAWCOLORCONTROL lpColorControl = NULL;
LPDIRECTDRAWGAMMACONTROL lpGammaControl = NULL;

LPDIRECT3DVIEWPORT3 lpViewport = NULL;
LPDIRECT3DTEXTURE2 lpTextureInterface = NULL;

LPDIRECTDRAWSURFACE4 *BitmapTextureSurfaces, *LightmapTextureSurfaces, *UploadSurfaces, *Upload4444Surfaces,
    *UploadBumpmapSurfaces, *BumpmapTextureSurfaces = NULL;

int d3d_EnvironmentMap = -1;

#define MAX_D2D_DEVICES 6
#define MAX_D3D_DEVICES 6

struct d3d_device {
  GUID guid_2d;
  LPGUID pguid_2d;

  GUID guid_3d;
  LPGUID pguid_3d;

  char name[1024];
};

d3d_device D2D_devices[MAX_D2D_DEVICES];
d3d_device D3D_devices[MAX_D3D_DEVICES];

int Num_d2d_devices = 0;
int Num_d3d_devices = 0;

// Cache variables
int d3d_Cache_tick = 0;
static int Last_texture_bound[3] = {-1, -1, -1};

// For zbuffer enumeration
#define MAX_ZDEPTHS 16
int NumZDepths = 0;
DDPIXELFORMAT ZPixFormats[MAX_ZDEPTHS];

// For texture format enumeration
#define MAX_TEXTURE_FORMATS 128
int Num_texture_formats = 0;
DDPIXELFORMAT RGB_texture_format, Texture_4444_format, Compressed_texture_format, Bumpmap_texture_format;
DDPIXELFORMAT TextureFormats[MAX_TEXTURE_FORMATS];

bool D3D_multitexture_state = false;
bool D3D_bumpmap_state = false;
uint8_t D3D_frame_started = 0;
float d3d_FogDiff = 0;

// For verifying the texture/alpha types before rendering
int Alpha_always_set = -1;

// Alpha to multiply by
static float Alpha_multiplier = 1.0;
static float d3d_Alpha_factor = 1.0f;

// Caps for this device
bool d3d_MultiTexture = false;
bool d3d_WBuffer = false;
bool d3d_ZBias = false;
bool d3d_CanMip = false;
bool d3d_CanGamma = false;
bool d3d_CanFog = false;
bool d3d_CanZCompare = false;
bool d3d_CanBumpmap = false;
bool d3d_CanCompress = false;
bool d3d_TextureMemories = false;
bool d3d_IsRiva128 = false;
bool d3d_SubpixelCorrect = true;

float d3d_WBias = 0, UV_diff = 0;

void d3d_SetD3DIdentity(D3DMATRIX *mat) {
  memset(mat, 0, sizeof(D3DMATRIX));
  mat->_11 = 1;
  mat->_22 = 1;
  mat->_33 = 1;
  mat->_44 = 1;
}

void d3d_SetWBufferDepth(float dvWFar) {
  HRESULT res;
  D3DMATRIX matWorld;
  D3DMATRIX matView;
  D3DMATRIX matProj;

  d3d_SetD3DIdentity(&matWorld);
  d3d_SetD3DIdentity(&matView);
  d3d_SetD3DIdentity(&matProj);

  res = lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
  res = lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);

  matProj._43 = 0;
  matProj._34 = 1;
  matProj._44 = 1;
  matProj._33 = 1 / (dvWFar - 1) + 1;

  res = lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProj);
}

// Get the capabilities of the Direct3D device
void d3d_GetCaps() {
  d3d_TextureMemories = false;
  d3d_CanFog = false;
  d3d_MultiTexture = false;
  d3d_WBuffer = false;
  d3d_ZBias = false;
  d3d_CanMip = false;
  d3d_CanGamma = false;
  d3d_CanZCompare = false;
  d3d_WBias = 0;
  d3d_CanBumpmap = false;
  d3d_IsRiva128 = false;
  d3d_SubpixelCorrect = true;

  // Check whether the device supports real multitexturing (if not, we're
  // going to emulate it using multipass rendering)
  D3DDEVICEDESC ddHwDesc, ddSwDesc;
  ddHwDesc.dwSize = sizeof(D3DDEVICEDESC);
  ddSwDesc.dwSize = sizeof(D3DDEVICEDESC);
  lpD3DDevice->GetCaps(&ddHwDesc, &ddSwDesc);

  // See if we have separate texture memories
  if (ddHwDesc.dwDevCaps & D3DDEVCAPS_SEPARATETEXTUREMEMORIES) {
    d3d_TextureMemories = true;
    mprintf(0, "Device has texture memories!\n");
  }

  // Check to see if this device supports bumpmapping
  if (ddHwDesc.dwTextureOpCaps & D3DTEXOPCAPS_BUMPENVMAP) {
    d3d_CanBumpmap = true;
    mprintf(0, "Device support bumpmapping!\n");
  } else {
    mprintf(0, "Device DOES NOT support bumpmapping!\n");
  }

  if (!FindArg("-bumped")) {
    d3d_CanBumpmap = false;
    mprintf(0, "Turning off bumpmapping because switch not found.\n");
  }

  // Check if the device supports single pass multiple texture.
  if (ddHwDesc.wMaxSimultaneousTextures > 1) {
    if (ddHwDesc.dwTextureOpCaps & D3DTEXOPCAPS_MODULATE) {
      d3d_MultiTexture = true;
      UseMultitexture = true;
    } else {
      UseMultitexture = false;
      d3d_TextureMemories = false;
    }
  }

  if (FindArg("-NoMultitexture")) {
    d3d_MultiTexture = false;
    UseMultitexture = false;
    d3d_TextureMemories = false;
  }

  if (d3d_MultiTexture)
    mprintf(0, "Device has multitexture caps!\n");
  else
    mprintf(0, "Device DOES NOT have multitexture caps!\n");

  // Get triangle caps and check for caps
  LPD3DPRIMCAPS pdpc = &ddHwDesc.dpcTriCaps;

  // Check for Z compare caps
  if (pdpc->dwZCmpCaps & D3DPCMPCAPS_LESSEQUAL) {
    d3d_CanZCompare = true;
    mprintf(0, "Device HAS Z compare caps!\n");
  } else
    mprintf(0, "Device DOES NOT have Z compare caps!\n");

  // Check if it supports Wbuffering
  if (pdpc->dwRasterCaps & D3DPRASTERCAPS_WBUFFER) {
    mprintf(0, "Device has Wbuffer!\n");
    d3d_WBuffer = true;
    UseWBuffer = true;
  } else {
    mprintf(0, "Device DOES NOT have Wbuffer!\n");
    d3d_WBuffer = false;
    UseWBuffer = false;
  }

  // Check for zbias
  if (pdpc->dwRasterCaps & D3DPRASTERCAPS_ZBIAS) {
    mprintf(0, "Device has ZBias!\n");
    d3d_ZBias = true;
  } else {
    mprintf(0, "Device DOES NOT have ZBias!\n");
    d3d_ZBias = false;
  }

  // Check for fog table
  if (pdpc->dwRasterCaps & D3DPRASTERCAPS_FOGVERTEX) {
    mprintf(0, "Device has Fogtable!\n");
    d3d_CanFog = true;
  } else {
    mprintf(0, "Device DOES NOT have Fogtable!\n");
    d3d_CanFog = false;
  }

  if (FindArg("-NoOutdoorFog"))
    d3d_CanFog = false;

  // Check for mip mapping
  if (pdpc->dwTextureFilterCaps & (D3DPTFILTERCAPS_MIPLINEAR)) {
    d3d_CanMip = true;
    mprintf(0, "Device has mip map capabilities!\n");
  } else {
    d3d_CanMip = false;
    mprintf(0, "Device DOES NOT have mip map capabilities!\n");
  }

  // Get the interface to the gamma control
  int ddrval = lpFrontBuffer->QueryInterface(IID_IDirectDrawGammaControl, (LPVOID *)&lpGammaControl);
  if (ddrval != DD_OK)
    mprintf(0, "D3D_INIT: QueryInterface for gamma failed.\n");
  else {
    mprintf(0, "Gamma interface detection successful!\n");
    d3d_CanGamma = true;
  }

  DDCAPS hcaps, helcaps;
  memset(&hcaps, 0, sizeof(DDCAPS));
  memset(&helcaps, 0, sizeof(DDCAPS));
  hcaps.dwSize = sizeof(DDCAPS);
  helcaps.dwSize = sizeof(DDCAPS);

  lpDD->GetCaps(&hcaps, &helcaps);
  if (hcaps.dwCaps2 & DDCAPS2_PRIMARYGAMMA) {
    mprintf(0, "Device DOES NOT have gamma support.\n");
  } else {
    mprintf(0, "Secondary gamma detection successful!\n");
  }

  // Now detect for riva128 (only if wbuffer is not detected for that card)
  DDDEVICEIDENTIFIER did;
  lpDD->GetDeviceIdentifier(&did, 0);
  if (d3d_WBuffer == false && did.dwVendorId == 0x12d2) {
    if (did.dwDeviceId == 0x18 || did.dwDeviceId == 0x19) {
      d3d_IsRiva128 = true;
      // NoLightmaps=true;
      mprintf(0, "Device IS Riva128!\n");
    } else {
      mprintf(0, "Device IS NOT Riva128!\n");
    }
  }

  if (FindArg("-subpixelcorrect"))
    d3d_SubpixelCorrect = false;
}

// Sets up an enviroment variable string for our gamma
void d3d_SetGammaString(float val) {
  char *envstring = "SST_GAMMA";

  char envvalue[10];

  sprintf(envvalue, "%f", val);
  SetEnvironmentVariable(envstring, envvalue);
  mprintf(0, "Setting D3D gamma to %f\n", val);
}

// Places a device into our global list of 3d devices to choose from
HRESULT WINAPI d3d_Enumerate3DDevice(LPGUID lpGUID, LPSTR lpDeviceDescription, LPSTR lpDeviceName,
                                     LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext) {
  int use_it = 0;

  if (lpHWDesc && lpHWDesc->dwFlags != 0)
    use_it = 1;

  if (use_it) {
    mprintf(0, "Found 3d device %s: %s\n", lpDeviceName, lpDeviceDescription);
    d3d_device *d2d = (d3d_device *)lpContext;
    d3d_device *d3d = (d3d_device *)&D3D_devices[Num_d3d_devices++];

    if (lpGUID) {
      memmove(&d3d->guid_3d, lpGUID, sizeof(GUID));
      d3d->pguid_3d = &d3d->guid_3d;
    } else {
      memset(&d3d->guid_3d, 0, sizeof(GUID));
      d3d->pguid_3d = NULL;
    }

    memmove(&d3d->guid_2d, &d2d->guid_2d, sizeof(GUID));
    if (d2d->pguid_2d) {
      d3d->pguid_2d = &d3d->guid_2d;
    } else {
      d3d->pguid_2d = NULL;
    }

    strcat(d3d->name, d2d->name);
  }

  return D3DENUMRET_OK;
}

// Places a device into our global list of 2d devices to choose from
BOOL WINAPI d3d_Enumerate2DDevice(LPGUID lpGUID, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPVOID lpContext) {
  d3d_device *d2d = (d3d_device *)&D2D_devices[Num_d2d_devices++];

  mprintf(0, "Found 2d device %s: %s\n", lpDeviceName, lpDeviceDescription);

  if (lpGUID) {
    memmove(&d2d->guid_2d, lpGUID, sizeof(GUID));
    d2d->pguid_2d = &d2d->guid_2d;
  } else {
    memset(&d2d->guid_2d, 0, sizeof(GUID));
    d2d->pguid_2d = NULL;
  }

  strcpy(d2d->name, lpDeviceDescription);

  return D3DENUMRET_OK;
}

// Enumerates the zbuffer types we have to choose from
HRESULT WINAPI d3d_EnumZPixelFormats(LPDDPIXELFORMAT pixfmt, LPVOID lpContext) {
  if (NumZDepths >= MAX_ZDEPTHS)
    return D3DENUMRET_OK;
  if (!(pixfmt->dwFlags & DDPF_ZBUFFER))
    return D3DENUMRET_OK;

  ZPixFormats[NumZDepths++] = *pixfmt;

  return D3DENUMRET_OK;
}

// Enumerates the texture pixel formats we have to choose from
HRESULT WINAPI d3d_EnumTexturePixelFormats(LPDDPIXELFORMAT pixfmt, LPVOID lpContext) {
  if (Num_texture_formats >= MAX_TEXTURE_FORMATS)
    return D3DENUMRET_CANCEL;

  TextureFormats[Num_texture_formats++] = *pixfmt;

  return D3DENUMRET_OK;
}

// Sets up the best device to use
d3d_device *d3d_PollDevices() {
  int i;
  HRESULT ddrval;

  Num_d2d_devices = 0;
  Num_d3d_devices = 0;

  ddrval = DirectDrawEnumerate(d3d_Enumerate2DDevice, NULL);
  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: DirectDrawEnumerate failed.\n");
    goto D3DError;
  }

  // Go through all 2d devices then create their 3d devices to create the total
  // number of 3d devices to to choose from
  mprintf(0, "Found %d 2d devices...checking for 3d devices.\n", Num_d2d_devices);

  for (i = 0; i < Num_d2d_devices; i++) {

    d3d_device *d2d = (d3d_device *)&D2D_devices[i];

    // Create direct draw surface
    ddrval = DirectDrawCreate(d2d->pguid_2d, &lpDD1, NULL);
    if (ddrval != DD_OK) {
      mprintf(0, "D3D_INIT: DirectDrawCreate failed.\n");
      goto D3DError;
    }

    ddrval = lpDD1->QueryInterface(IID_IDirect3D3, (LPVOID *)&lpD3D);
    if (ddrval != DD_OK) {
      lpD3D = NULL;
      mprintf(0, "D3D_INIT: QueryInterface failed.\n");
      goto D3DError;
    }

    // Enumerate this 3d device
    ddrval = lpD3D->EnumDevices(d3d_Enumerate3DDevice, d2d);
    if (ddrval != DD_OK) {
      mprintf(0, "WIN_DD32: D3D enum devices failed. (0x%x)\n", ddrval);
    }

    lpD3D->Release();
    lpD3D = NULL;

    lpDD1->Release();
    lpDD1 = NULL;
  }

  for (i = 0; i < Num_d3d_devices; i++) {
    mprintf(0, "D3D Device %d: %s\n", i, D3D_devices[i].name);
  }

  if (Num_d3d_devices <= 0) {
    mprintf(0, "No D3D device found!\n");
    return NULL;
  }

  if (Num_d3d_devices > 0) {
    int use_device = 0;

    if (Num_d3d_devices > 1) {
      char tempbuffer[255];
      int templen = 255;
      mprintf(0, "More than one D3D device found!\n");

      Database->read("RenderingDeviceName", tempbuffer, &templen);

      int done = 0;
      for (i = 0; i < Num_d3d_devices && !done; i++) {
        if (!stricmp(tempbuffer, D3D_devices[i].name)) {
          use_device = i;
          done = 1;
        }
      }

      if (done == 0)
        use_device = 0;
    }

    // use_device=Num_d3d_devices-1;

    if (FindArg("-useseconddevice") && Num_d3d_devices > 1)
      use_device = Num_d3d_devices - 1;

    mprintf(0, "Using %s\n", D3D_devices[use_device].name);

    // Use the last device.
    return &D3D_devices[use_device];
  }

  return NULL;

D3DError:
  mprintf(0, "Direct3D Polling failed.\n");
  return NULL;
}

// Returns the number of bits used in a mask
WORD d3d_GetNumOfBits(DWORD dwMask) {
  WORD wBits = 0;
  while (dwMask) {
    dwMask = dwMask & (dwMask - 1);
    wBits++;
  }

  return wBits;
}

int d3d_GetTexClass(int handle, int map_type) {
  int w, tex_class;

  if (map_type == MAP_TYPE_LIGHTMAP)
    w = GameLightmaps[handle].square_res;
  else if (map_type == MAP_TYPE_BUMPMAP)
    w = GameBumpmaps[handle].width;
  else
    w = bm_w(handle, 0);

  if (w == 256)
    tex_class = 0;
  else if (w == 128)
    tex_class = 1;
  else if (w == 64)
    tex_class = 2;
  else if (w == 32)
    tex_class = 3;
  else {
    mprintf(0, "Bad class for d3d!\n");
    Int3();
  }

  return tex_class;
}

// Given a bitmap handle, a map type, and a destination d3d slot, takes the data
// from the application and massages it for direct3d's consumption
void d3d_UploadBitmapToSurface(int handle, int map_type, int slot, int new_upload) {
  DDSURFACEDESC2 surf_desc;
  LPDIRECTDRAWSURFACE4 dest_sp, upload_sp;

  HRESULT ddrval;
  int w, h;
  uint16_t *src_data;

  // mprintf(0,"Uploading bitmap %d type %d\n",handle,map_type);
  // mprintf(0,"Slot=%d handle=%d\n",slot,handle);

  ASSERT(slot != -1);
  ASSERT(slot == handle);

  int tex_class = d3d_GetTexClass(handle, map_type);

  if (map_type == MAP_TYPE_BITMAP) {
    w = bm_w(handle, 0);
    h = bm_h(handle, 0);

    ASSERT(GameBitmaps[handle].cache_slot == handle);

    if (bm_format(handle) == BITMAP_FORMAT_4444)
      upload_sp = Upload4444Surfaces[tex_class];
    else
      upload_sp = UploadSurfaces[tex_class];
    dest_sp = BitmapTextureSurfaces[slot];

    src_data = bm_data(handle, 0);
  } else if (map_type == MAP_TYPE_BUMPMAP) {
    w = bump_w(handle);
    h = bump_h(handle);

    ASSERT(GameBumpmaps[handle].cache_slot == handle);
    dest_sp = BumpmapTextureSurfaces[slot];
    src_data = bump_data(handle);
  } else {
    w = lm_w(handle);
    h = lm_h(handle);

    ASSERT(GameLightmaps[handle].cache_slot == handle);
    dest_sp = LightmapTextureSurfaces[slot];
    upload_sp = UploadSurfaces[tex_class];

    src_data = lm_data(handle);
  }

  ASSERT(dest_sp != NULL);

  memset(&surf_desc, 0, sizeof(DDSURFACEDESC2));
  surf_desc.dwSize = sizeof(DDSURFACEDESC2);
  surf_desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

  // Now that we have a lock, blit this bitmap to the surface
  if (map_type == MAP_TYPE_BUMPMAP) {
    ddrval = dest_sp->Lock(NULL, &surf_desc, DDLOCK_WAIT, NULL);
    if (ddrval != DD_OK) {
      mprintf(0, "D3D:Normal upload lock error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
      return;
    }

    uint16_t *dest_data = (uint16_t *)surf_desc.lpSurface;

    memcpy(dest_data, src_data, w * h * 2);

    // Unlock the surface
    dest_sp->Unlock(NULL);
  } else if (map_type == MAP_TYPE_LIGHTMAP) {
    // Light maps aren't square, but our surfaces are...
    int partial_replace = 0;
    RECT lmap_rect;

    if (!new_upload && (GameLightmaps[handle].flags & LF_LIMITS)) {
      partial_replace = 1;
      lmap_rect.left = 0;
      lmap_rect.right = w;

      lmap_rect.top = GameLightmaps[handle].cy1;
      lmap_rect.bottom = GameLightmaps[handle].cy2;
      ddrval = upload_sp->Lock(&lmap_rect, &surf_desc, DDLOCK_WAIT | DDLOCK_WRITEONLY, NULL);
      // ddrval=dest_sp->Lock(&lmap_rect,&surf_desc,DDLOCK_WAIT|DDLOCK_WRITEONLY,NULL);
    } else
      ddrval = upload_sp->Lock(NULL, &surf_desc, DDLOCK_WAIT | DDLOCK_WRITEONLY, NULL);
    // ddrval=dest_sp->Lock(NULL,&surf_desc,DDLOCK_WAIT|DDLOCK_WRITEONLY,NULL);

    if (ddrval != DD_OK) {
      mprintf(0, "D3D:Upload lock error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
      return;
    }

    uint16_t *left_data = (uint16_t *)surf_desc.lpSurface;
    int bm_left = 0;
    int size = GameLightmaps[handle].square_res;

    if (partial_replace) {
      int y1 = (GameLightmaps[handle].cy1);
      int y2 = (GameLightmaps[handle].cy2);
      int ph = (y2 - y1);

      bm_left += (w * y1);

      for (int i = 0; i < ph; i++, left_data += size, bm_left += w) {
        uint16_t *dest_data = left_data;
        for (int t = 0; t < w; t++) {
          *dest_data++ = src_data[bm_left + t];
        }
      }

      // Unlock the lightmap surface
      upload_sp->Unlock(&lmap_rect);
      dest_sp->Blt(&lmap_rect, upload_sp, &lmap_rect, DDBLT_WAIT, NULL);
    }

    else {
      for (int i = 0; i < h; i++, left_data += size, bm_left += w) {
        uint16_t *dest_data = left_data;
        for (int t = 0; t < w; t++) {
          *dest_data++ = src_data[bm_left + t];
        }
      }

      // Unlock the lightmap surface
      upload_sp->Unlock(NULL);
      dest_sp->Blt(NULL, upload_sp, NULL, DDBLT_WAIT, NULL);
    }

  } else // Must bit a bitmap
  {
    if (d3d_CanMip && map_type == MAP_TYPE_BITMAP && GameBitmaps[handle].flags & BF_MIPMAPPED) {
      LPDIRECTDRAWSURFACE4 dest_mipsurf = dest_sp;

      DDSCAPS2 ddsCaps;
      ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
      for (int i = 0; i < NUM_MIP_LEVELS; i++) {
        ddrval = upload_sp->Lock(NULL, &surf_desc, DDLOCK_WAIT, NULL);
        if (ddrval != DD_OK) {
          mprintf(0, "D3D:mip=%d Upload lock error %d! %s\n", i, ddrval, d3d_ErrorString(ddrval));
          return;
        }

        src_data = bm_data(handle, i);
        w = bm_w(handle, i);
        h = bm_h(handle, i);
        uint16_t *dest_data = (uint16_t *)surf_desc.lpSurface;

        // Copy the raw data into the directx surface
        int pitch_diff = (surf_desc.lPitch / 2) - w;
        for (int y = 0; y < h; y++, dest_data += pitch_diff) {
          for (int x = 0; x < w; x++) {
            *dest_data++ = *src_data++;
          }
        }

        upload_sp->Unlock(NULL);
        dest_mipsurf->Blt(NULL, upload_sp, NULL, DDBLT_WAIT, NULL);

        if (i != NUM_MIP_LEVELS - 1) // Get next mip surface
        {
          if (bm_format(handle) == BITMAP_FORMAT_4444)
            upload_sp = Upload4444Surfaces[tex_class + 1 + i];
          else
            upload_sp = UploadSurfaces[tex_class + 1 + i];

          ddrval = dest_mipsurf->GetAttachedSurface(&ddsCaps, &dest_mipsurf);
          if (ddrval != DD_OK) {
            mprintf(0, "Couldn't get attached dest mip surface %d!\n", i);
            return;
          }
          dest_mipsurf->Release();
        }
      }

    } else {
      // Do a non-mipped bitmap
      ddrval = upload_sp->Lock(NULL, &surf_desc, DDLOCK_WAIT, NULL);
      if (ddrval != DD_OK) {
        mprintf(0, "D3D:Normal upload lock error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
        return;
      }

      uint16_t *dest_data = (uint16_t *)surf_desc.lpSurface;

      memcpy(dest_data, src_data, w * h * 2);

      // Unlock the surface
      upload_sp->Unlock(NULL);
      dest_sp->Blt(NULL, upload_sp, NULL, DDBLT_WAIT, NULL);
    }
  }

  if (map_type == MAP_TYPE_BITMAP)
    GameBitmaps[handle].flags &= ~BF_CHANGED;
  else if (map_type == MAP_TYPE_BUMPMAP)
    GameBumpmaps[handle].flags &= ~BUMPF_CHANGED;
  else
    GameLightmaps[handle].flags &= ~(LF_CHANGED | LF_LIMITS);

  D3D_uploads++;
}

// Returns index into the global array of texture interfaces we have
int d3d_CreateTextureFromBitmap(int bm_handle, int map_type) {
  int w, h;
  int retval = -1;
  HRESULT ddrval;

  // mprintf(0,"Creating texture from handle %d type %d\n",bm_handle,map_type);

  if (map_type == MAP_TYPE_BUMPMAP) {
    ASSERT(GameBumpmaps[bm_handle].cache_slot == -1);

    w = bump_w(bm_handle);
    h = bump_h(bm_handle);
  } else if (map_type == MAP_TYPE_LIGHTMAP) {
    ASSERT(GameLightmaps[bm_handle].cache_slot == -1);

    w = GameLightmaps[bm_handle].square_res;
    h = GameLightmaps[bm_handle].square_res;

  } else {
    ASSERT(GameBitmaps[bm_handle].cache_slot == -1);
    w = bm_w(bm_handle, 0);
    h = bm_h(bm_handle, 0);
    // Pointer to a bitmap surface
  }

  // Create a texture interface and make it auto-managed
  DDSURFACEDESC2 ddsd;

  memset(&ddsd, 0, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  ddsd.dwFlags = DDSD_CAPS;
  ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
  ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
  ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

  ddsd.dwWidth = w;
  ddsd.dwHeight = h;

  if (map_type == MAP_TYPE_BITMAP && bm_format(bm_handle) == BITMAP_FORMAT_4444) {
    ddsd.ddpfPixelFormat = Texture_4444_format;
    ddsd.ddsCaps.dwCaps2 |= DDSCAPS2_HINTSTATIC;
  } else if (d3d_CanCompress && map_type == MAP_TYPE_BITMAP && bm_format(bm_handle) == BITMAP_FORMAT_1555 &&
             (GameBitmaps[bm_handle].flags & BF_COMPRESSABLE)) {
    ddsd.ddpfPixelFormat = Compressed_texture_format;
    ddsd.ddpfPixelFormat.dwFlags = DDPF_FOURCC;
    ddsd.ddpfPixelFormat.dwFourCC = FOURCC_DXT1;
    ddsd.ddsCaps.dwCaps2 |= DDSCAPS2_HINTSTATIC;

  } else if (map_type == MAP_TYPE_BUMPMAP) {
    ddsd.ddpfPixelFormat = Bumpmap_texture_format;

    ddsd.ddpfPixelFormat.dwFlags = DDPF_BUMPDUDV;
    ddsd.ddpfPixelFormat.dwBumpBitCount = 16;
    ddsd.ddpfPixelFormat.dwBumpDuBitMask = 0x000000ff;
    ddsd.ddpfPixelFormat.dwBumpDvBitMask = 0x0000ff00;
    ddsd.ddpfPixelFormat.dwBumpLuminanceBitMask = 0x00000000;
  } else {
    if (map_type == MAP_TYPE_LIGHTMAP) {
      ddsd.ddsCaps.dwCaps2 |= DDSCAPS2_HINTDYNAMIC;
    } else if (map_type == MAP_TYPE_BITMAP && GameBitmaps[bm_handle].flags & BF_MIPMAPPED)
      ddsd.ddsCaps.dwCaps2 |= DDSCAPS2_HINTSTATIC;

    ddsd.ddpfPixelFormat = RGB_texture_format;
  }

  if (d3d_CanMip && map_type == MAP_TYPE_BITMAP && GameBitmaps[bm_handle].flags & BF_MIPMAPPED) {
    ddsd.dwFlags |= DDSD_MIPMAPCOUNT;
    ddsd.dwMipMapCount = NUM_MIP_LEVELS;
    ddsd.ddsCaps.dwCaps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP;
  }

  // Assign the correct texture stage
  if (d3d_TextureMemories) {
    ddsd.dwFlags |= DDSD_TEXTURESTAGE;
    if (map_type == MAP_TYPE_LIGHTMAP)
      ddsd.dwTextureStage = 1;
    else
      ddsd.dwTextureStage = 0;
  }

  int dest_index;

  if (map_type == MAP_TYPE_BITMAP) {
    dest_index = bm_handle;
    ASSERT(GameBitmaps[bm_handle].cache_slot == -1);

    ddrval = lpDD->CreateSurface(&ddsd, &BitmapTextureSurfaces[dest_index], NULL);
  } else if (map_type == MAP_TYPE_BUMPMAP) {
    dest_index = bm_handle;
    ASSERT(GameBumpmaps[bm_handle].cache_slot == -1);

    ddrval = lpDD->CreateSurface(&ddsd, &BumpmapTextureSurfaces[dest_index], NULL);
  } else {
    dest_index = bm_handle;
    ASSERT(GameLightmaps[bm_handle].cache_slot == -1);

    ddrval = lpDD->CreateSurface(&ddsd, &LightmapTextureSurfaces[dest_index], NULL);
  }

  if (ddrval != DD_OK) {
    mprintf(0, "Creating texture surface failed!\n");
    return -1;
  }

  ASSERT(dest_index == bm_handle);

  if (map_type == MAP_TYPE_LIGHTMAP) {
    GameLightmaps[bm_handle].cache_slot = bm_handle;

    d3d_UploadBitmapToSurface(bm_handle, map_type, dest_index, 1);
    retval = dest_index;
  } else if (map_type == MAP_TYPE_BUMPMAP) {
    GameBumpmaps[bm_handle].cache_slot = bm_handle;

    d3d_UploadBitmapToSurface(bm_handle, map_type, dest_index, 1);
    retval = dest_index;

  } else {
    GameBitmaps[bm_handle].cache_slot = bm_handle;
    d3d_UploadBitmapToSurface(bm_handle, map_type, dest_index, 1);
    retval = dest_index;
  }

  return retval;
}

// Frees all the memory used by the texture cache
void d3d_FreeTextureCache() {
  int i;

  if (UploadSurfaces) {
    for (i = 0; i < NUM_TEXTURE_CLASSES; i++) {
      UploadSurfaces[i]->Release();
    }

    mem_free(UploadSurfaces);
    UploadSurfaces = NULL;
  }

  if (Upload4444Surfaces) {
    for (i = 0; i < NUM_TEXTURE_CLASSES; i++) {
      Upload4444Surfaces[i]->Release();
    }

    mem_free(Upload4444Surfaces);
    Upload4444Surfaces = NULL;
  }

  if (BitmapTextureSurfaces) {
    for (i = 0; i < MAX_BITMAPS; i++) {
      if (GameBitmaps[i].cache_slot != -1) {
        if (GameBitmaps[i].cache_slot != i) {
          mprintf(0, "Error cache slot is %d when it should be %d!\n", GameBitmaps[i].cache_slot, i);
        }

        ASSERT(GameBitmaps[i].cache_slot == i);

        d3d_FreePreUploadedTexture(i, MAP_TYPE_BITMAP);
      }
    }

    mem_free(BitmapTextureSurfaces);
    BitmapTextureSurfaces = NULL;
  }

  if (BumpmapTextureSurfaces) {
    for (i = 0; i < MAX_BUMPMAPS; i++) {
      if (GameBumpmaps[i].cache_slot != -1) {
        ASSERT(GameBumpmaps[i].cache_slot == i);
        d3d_FreePreUploadedTexture(i, MAP_TYPE_BUMPMAP);
      }
    }
    mem_free(BumpmapTextureSurfaces);
    BumpmapTextureSurfaces = NULL;
  }

  if (LightmapTextureSurfaces) {
    for (i = 0; i < MAX_LIGHTMAPS; i++) {
      if (GameLightmaps[i].cache_slot != -1) {
        ASSERT(GameLightmaps[i].cache_slot == i);
        d3d_FreePreUploadedTexture(i, MAP_TYPE_LIGHTMAP);
      }
    }
    mem_free(LightmapTextureSurfaces);
    LightmapTextureSurfaces = NULL;
  }
}

// Creates the surfaces we use for uploading
int d3d_CreateUploadSurfaces() {
  int i;
  HRESULT ddrval;

  for (i = 0; i < NUM_TEXTURE_CLASSES; i++) {
    // Create a texture interface and make it auto-managed
    DDSURFACEDESC2 ddsd;

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

    ddsd.dwWidth = 256 >> i;
    ddsd.dwHeight = 256 >> i;

    ddsd.ddpfPixelFormat = RGB_texture_format;

    ddrval = lpDD->CreateSurface(&ddsd, &UploadSurfaces[i], NULL);

    if (ddrval != DD_OK) {
      mprintf(0, "Creating 1555 texture surface failed!\n");
      return 0;
    }
  }

  // Now create 4444 surfaces
  for (i = 0; i < NUM_TEXTURE_CLASSES; i++) {
    // Create a texture interface and make it auto-managed
    DDSURFACEDESC2 ddsd;

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
    ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

    ddsd.dwWidth = 256 >> i;
    ddsd.dwHeight = 256 >> i;

    ddsd.ddpfPixelFormat = Texture_4444_format;

    ddrval = lpDD->CreateSurface(&ddsd, &Upload4444Surfaces[i], NULL);

    if (ddrval != DD_OK) {
      mprintf(0, "Creating 4444 texture surface failed!\n");
      return 0;
    }
  }

  return 1;
}

// Loads an environment map for bumpmapping. Returns 1 on success, 0 on fail
int d3d_LoadEnvironmentMap() {
  if (d3d_EnvironmentMap != -1)
    return 1;

  d3d_EnvironmentMap = bm_AllocLoadFileBitmap("Environment.ogf", 0);

  if (d3d_EnvironmentMap < 0)
    return 0;

  return 1;
}

// Initializes the texture cache for Direct3D
int d3d_TextureCacheInit() {
  int i;

  // Clear our cache slots
  for (i = 0; i < MAX_LIGHTMAPS; i++) {
    GameLightmaps[i].cache_slot = -1;
  }

  for (i = 0; i < MAX_BITMAPS; i++) {
    GameBitmaps[i].cache_slot = -1;
  }

  for (i = 0; i < MAX_BUMPMAPS; i++) {
    GameBumpmaps[i].cache_slot = -1;
  }

  // Allocate room to hold all our surfaces
  UploadSurfaces = (LPDIRECTDRAWSURFACE4 *)mem_malloc(NUM_TEXTURE_CLASSES * sizeof(LPDIRECTDRAWSURFACE4));
  if (UploadSurfaces == NULL) {
    mprintf(0, "Couldn't allocate memory for UploadSurfaces!\n");

    rend_SetErrorMessage("Couldn't alloc mem for UploadSurfaces!");
    return 0;
  }

  // Allocate room to hold all our 4444 surfaces
  Upload4444Surfaces = (LPDIRECTDRAWSURFACE4 *)mem_malloc(NUM_TEXTURE_CLASSES * sizeof(LPDIRECTDRAWSURFACE4));
  if (Upload4444Surfaces == NULL) {
    mprintf(0, "Couldn't allocate memory for Upload4444Surfaces!\n");

    rend_SetErrorMessage("Couldn't alloc mem for Upload4444Surfaces!");
    return 0;
  }

  BitmapTextureSurfaces = (LPDIRECTDRAWSURFACE4 *)mem_malloc(MAX_BITMAPS * sizeof(LPDIRECTDRAWSURFACE4));
  if (BitmapTextureSurfaces == NULL) {
    mprintf(0, "Couldn't allocate memory for BitmapTextureSurfaces!\n");

    rend_SetErrorMessage("Couldn't alloc mem for BitmapTextureSurfaces!");
    return 0;
  }

  // Allocate room to hold all our surfaces
  LightmapTextureSurfaces = (LPDIRECTDRAWSURFACE4 *)mem_malloc(MAX_LIGHTMAPS * sizeof(LPDIRECTDRAWSURFACE4));
  if (LightmapTextureSurfaces == NULL) {
    mprintf(0, "Couldn't allocate memory for LightmapTextureSurfaces!\n");
    rend_SetErrorMessage("Couldn't alloc mem for LightmapTextureSurfaces!");
    return 0;
  }

  if (d3d_CanBumpmap) {
    BumpmapTextureSurfaces = (LPDIRECTDRAWSURFACE4 *)mem_malloc(MAX_BUMPMAPS * sizeof(LPDIRECTDRAWSURFACE4));
    if (BumpmapTextureSurfaces == NULL) {
      mprintf(0, "Couldn't allocate memory for BumpmapTextureSurfaces!\n");
      rend_SetErrorMessage("Couldn't alloc mem for BumpmapTextureSurfaces!");
      return 0;
    }

    if (!d3d_LoadEnvironmentMap()) {
      mprintf(0, "couldn't load env map\n");
      return 0;
    }
  }

  // Enumerate those texture formats
  lpD3DDevice->EnumTextureFormats(d3d_EnumTexturePixelFormats, 0);
  if (Num_texture_formats < 1) {
    mprintf(0, "No texture formats available!\n");
    rend_SetErrorMessage("No valid texture formats available!");
    return 0;
  }

  // Find a pixel format with 1555
  int found_format = -1;
  for (i = 0; i < Num_texture_formats && found_format == -1; i++) {
    DDPIXELFORMAT *pf = &TextureFormats[i];

    int rcount, gcount, bcount, acount;

    rcount = d3d_GetNumOfBits(pf->dwRBitMask);
    gcount = d3d_GetNumOfBits(pf->dwGBitMask);
    bcount = d3d_GetNumOfBits(pf->dwBBitMask);
    acount = d3d_GetNumOfBits(pf->dwRGBAlphaBitMask);

    if (rcount == 5 && gcount == 5 && bcount == 5 && acount == 1) {
      found_format = i;
      mprintf(1, "Alpha bit mask is %d!\n", pf->dwRGBAlphaBitMask);
    }
  }

  if (found_format == -1) {
    mprintf(0, "Couldn't find a valid 1555 pixel format!\n");
    rend_SetErrorMessage("Couldn't find a valid 1555 pixel format!  Card doesn't support 1555 format!");
    return 0;
  }

  RGB_texture_format = TextureFormats[found_format];

  // Find a pixel format with 4444
  found_format = -1;
  for (i = 0; i < Num_texture_formats && found_format == -1; i++) {
    DDPIXELFORMAT *pf = &TextureFormats[i];

    int rcount, gcount, bcount, acount;

    rcount = d3d_GetNumOfBits(pf->dwRBitMask);
    gcount = d3d_GetNumOfBits(pf->dwGBitMask);
    bcount = d3d_GetNumOfBits(pf->dwBBitMask);
    acount = d3d_GetNumOfBits(pf->dwRGBAlphaBitMask);

    if (rcount == 4 && gcount == 4 && bcount == 4 && acount == 4) {
      found_format = i;
      mprintf(1, "Alpha bit mask is %d!\n", pf->dwRGBAlphaBitMask);
    }
  }

  if (found_format == -1) {
    mprintf(0, "Couldn't find a valid 4444 pixel format!\n");
    rend_SetErrorMessage("Couldn't find a valid 4444 pixel format!  Card doesn't support 1555 format!");
    return 0;
  }

  Texture_4444_format = TextureFormats[found_format];

  // Find a pixel format with bumpmapping (if supported)
  if (d3d_CanBumpmap) {
    found_format = -1;
    for (i = 0; i < Num_texture_formats && found_format == -1; i++) {
      DDPIXELFORMAT *pf = &TextureFormats[i];

      if (pf->dwFlags & DDPF_BUMPDUDV) {
        if (pf->dwBumpBitCount == 16 && pf->dwBumpDuBitMask == 0x000000ff && pf->dwBumpDvBitMask == 0x0000ff00 &&
            pf->dwBumpLuminanceBitMask == 0) {
          found_format = i;
          mprintf(0, "Found a suitable bumpmapping format\n");
        }
      }
    }

    if (found_format == -1) {
      mprintf(0, "Couldn't find a valid bumpmap pixel format!\n");
      d3d_CanBumpmap = false;
    } else
      Bumpmap_texture_format = TextureFormats[found_format];
  }

  // Check to see if it supports S3 compression
  // Find a pixel format with 1555
  found_format = -1;

  for (i = 0; i < Num_texture_formats && found_format == -1; i++) {
    DDPIXELFORMAT *pf = &TextureFormats[i];

    int rcount, gcount, bcount, acount;

    rcount = d3d_GetNumOfBits(pf->dwRBitMask);
    gcount = d3d_GetNumOfBits(pf->dwGBitMask);
    bcount = d3d_GetNumOfBits(pf->dwBBitMask);
    acount = d3d_GetNumOfBits(pf->dwRGBAlphaBitMask);

    if (pf->dwFourCC == FOURCC_DXT1) {
      found_format = i;
      mprintf(0, "Compress format: r=%d g=%d b=%d a=%d\n", rcount, gcount, bcount, acount);
      mprintf(1, "Texture compression alpha bit mask is %d!\n", pf->dwRGBAlphaBitMask);
    }
  }

  if (found_format == -1 || FindArg("-nocompress")) {
    mprintf(0, "Device doesn't support texture compression!\n");
    d3d_CanCompress = false;
  } else {
    mprintf(0, "Device DOES support texture compression!\n");
    d3d_CanCompress = true;
    Compressed_texture_format = TextureFormats[found_format];
  }

  if (!d3d_CreateUploadSurfaces())
    return 0;

  return 1;
}

// Sets up some default rendering states for Direct3D
void d3d_SetDefaultStates() {
  // lpD3DDevice->SetLightState(  D3DLIGHTSTATE_AMBIENT,  0xffffffff );
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATER);
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0);
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

  if (d3d_MultiTexture) {
    // Set second texel unit stages
    lpD3DDevice->SetTextureStageState(1, D3DTSS_MINFILTER, D3DTFN_LINEAR);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

    lpD3DDevice->SetTextureStageState(1, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);

    D3D_multitexture_state = false;
  }

  if (d3d_CanBumpmap) {
    D3D_bumpmap_state = false;
    float _val = 0;

    lpD3DDevice->SetTextureStageState(1, D3DTSS_MIPFILTER, D3DTFP_LINEAR);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 1);

    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT00, *(DWORD *)(&(_val = 1.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT01, *(DWORD *)(&(_val = 0.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT10, *(DWORD *)(&(_val = 0.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT11, *(DWORD *)(&(_val = 1.0f)));

    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVLSCALE, *(DWORD *)(&(_val = 1.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVLOFFSET, *(DWORD *)(&(_val = 0.0f)));

    lpD3DDevice->SetTextureStageState(2, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
  }

  lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
  lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);

  // Choose Wbuffer or straight zbuffer

  d3d_SetZBufferState(1);

  D3D_state.cur_color = 0x00FFFFFF;
  D3D_state.cur_bilinear_state = -1;
  D3D_state.cur_zbuffer_state = 1;
  D3D_state.cur_texture_quality = -1;
  D3D_state.cur_texture_type = TT_PERSPECTIVE_SPECIAL; // D3D doesn't support this state, so when d3d_SetTextureType
                                                       // gets called we're guaranteed this will get set right
  D3D_state.cur_light_state = LS_GOURAUD;
  D3D_state.cur_color_model = CM_MONO;
  D3D_state.cur_bilinear_state = -1;
  D3D_state.cur_alpha_type = -1;

  Alpha_always_set = -1;

  d3d_SetWrapType(WT_WRAP);

  if (D3D_preferred_state.filtering)
    d3d_SetFiltering(1);
  else
    d3d_SetFiltering(0);

  if (D3D_preferred_state.mipping)
    d3d_SetMipState(1);
  else
    d3d_SetMipState(0);

  d3d_SetAlphaValue(255);
  d3d_SetAlphaType(AT_ALWAYS);
  d3d_SetZBufferState(1);
  d3d_SetZValues(0, 3000);
  d3d_SetGammaValue(D3D_preferred_state.gamma);

  d3d_SetFlatColor(GR_RGB(255, 128, 255));

  D3D_state.screen_width = D3D_preferred_state.width;
  D3D_state.screen_height = D3D_preferred_state.height;

  if (d3d_WBuffer)
    d3d_SetWBufferDepth(5000);

  mprintf(0, "Direct3D initted to %d x %d\n", D3D_state.screen_width, D3D_state.screen_height);

  Last_texture_bound[0] = -1;
  Last_texture_bound[1] = -1;
  Last_texture_bound[2] = -1;
}

// Returns true if we're using DirectX 6.0
bool d3d_UsingDX6() {
  LONG lResult;
  HKEY hKey = NULL;
  int dx_version = 0;

  lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\DirectX", NULL, KEY_QUERY_VALUE, &hKey);

  if (lResult == ERROR_SUCCESS) {
    char version[32];
    DWORD dwType, dwLen;

    dwLen = 32;
    lResult = RegQueryValueEx(hKey, "Version", NULL, &dwType, (uint8_t *)version, &dwLen);

    if (lResult == ERROR_SUCCESS) {
      dx_version = atoi(strstr(version, ".") + 1);
    } else {
      int val;
      DWORD dwType, dwLen;

      dwLen = 4;
      lResult = RegQueryValueEx(hKey, "InstalledVersion", NULL, &dwType, (uint8_t *)&val, &dwLen);

      if (lResult == ERROR_SUCCESS) {

        dx_version = val;
      }

      RegCloseKey(hKey);
    }
  }

  if (dx_version >= 6)
    return true;

  return false;
}

// Sets up our Direct3D rendering context
// Returns 1 if ok, 0 if something bad
int d3d_Init(oeApplication *app, renderer_preferred_state *pref_state) {
  HRESULT ddrval;
  HWND hwnd;
  d3d_device *dd;
  DDSURFACEDESC2 ddsd2;
  DDSCAPS2 ddscaps;
  int retval = 1;
  bool retried = false;
  int found_format = -1, i;

  if (!d3d_UsingDX6()) {
    rend_SetErrorMessage("DirectX 6 is not properly installed.");
    return 0;
  }

  ParentApplication = app;

  if (pref_state != &D3D_preferred_state)
    D3D_preferred_state = *pref_state;

TryAgain:

  // Poll for valid 3d devices
  dd = d3d_PollDevices();

  if (!dd) {
    mprintf(1, "ERROR: No Direct3D devices found!!!");
    rend_SetErrorMessage("No Direct3D devices found!!!");
    return 0;
  }

  hwnd = (HWND)((oeWin32Application *)app)->m_hWnd;

  // Create our direct draw stuff
  ddrval = DirectDrawCreate(dd->pguid_2d, &lpDD1, NULL);

  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: DirectDrawCreate failed.\n");
    rend_SetErrorMessage("DirectDrawCreate failed.");

    goto D3DError;
  }

  ddrval = lpDD1->QueryInterface(IID_IDirectDraw4, (LPVOID *)&lpDD);
  if (ddrval != DD_OK) {
    lpDD = NULL;
    rend_SetErrorMessage("DirectDrawCreate2 failed.");
    mprintf(0, "D3D_INIT: DirectDrawCreate2 failed.\n");
    goto D3DError;
  }

  ddrval = lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);

  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: SetCooperativeLevel EXCLUSIVE failed.\n D3D_Error=%s\n", d3d_ErrorString(ddrval));
    rend_SetErrorMessage("SetCoopLevel EXCULUSIVE failed.");
    goto D3DError;
  }

  // Go to full screen!
  if (D3D_preferred_state.bit_depth != 16 && D3D_preferred_state.bit_depth != 32)
    D3D_preferred_state.bit_depth = 16;

  mprintf(0, "Opening screen with bit-depth of %d.\n", D3D_preferred_state.bit_depth);

  ddrval =
      lpDD->SetDisplayMode(D3D_preferred_state.width, D3D_preferred_state.height, D3D_preferred_state.bit_depth, 0, 0);

  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: SetDisplayMode failed, trying default!\n");

    retval = -1;
    D3D_preferred_state.width = 640;
    D3D_preferred_state.height = 480;
    D3D_preferred_state.bit_depth = 16;

    ddrval = lpDD->SetDisplayMode(D3D_preferred_state.width, D3D_preferred_state.height, 16, 0, 0);

    if (ddrval != DD_OK) {
      mprintf(0, "D3D_INIT: SetDisplayMode failed.\n");
      rend_SetErrorMessage("SetDisplayMode failed.");
      goto D3DError;
    }
  }

  memset(&ddsd2, 0, sizeof(ddsd2));

  ddsd2.dwSize = sizeof(ddsd2);
  ddsd2.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
  ddsd2.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_3DDEVICE | DDSCAPS_COMPLEX;
  ddsd2.dwBackBufferCount = 1;

  ddrval = lpDD->CreateSurface(&ddsd2, &lpFrontBuffer, NULL);
  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: CreateSurface (Front) failed.\n");
    rend_SetErrorMessage("CreateSurface (front) failed.");
    goto D3DError;
  }

  memset(&ddscaps, 0, sizeof(DDSCAPS2));
  ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

  ddrval = lpFrontBuffer->GetAttachedSurface(&ddscaps, &lpBackBuffer);
  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: GetAttachedSurface (Back) failed. Erorr=%s\n", d3d_ErrorString(ddrval));
    rend_SetErrorMessage("CreateSurface (back) failed.");
    goto D3DError;
  }

  // Create the Direct3d device
  ddrval = lpDD->QueryInterface(IID_IDirect3D3, (LPVOID *)&lpD3D);
  if (ddrval != DD_OK) {
    lpD3D = NULL;
    mprintf(0, "D3D_INIT: QueryInterface failed.\n");
    rend_SetErrorMessage("QueryInterface D3D failed.");
    goto D3DError;
  }

  // Enumerate Z Buffer
  NumZDepths = 0;
  lpD3D->EnumZBufferFormats(dd->guid_3d, d3d_EnumZPixelFormats, 0);

  if (NumZDepths == 0) {
    mprintf(0, "D3D_INIT: Couldn't find zbuffer format!\n");
    rend_SetErrorMessage("Couldn't find a zbuffer format!");
    goto D3DError;
  }

  // Create a z-buffer and attach it to the backbuffer
  memset(&ddsd2, 0, sizeof(ddsd2));
  ddsd2.dwSize = sizeof(ddsd2);
  ddsd2.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
  ddsd2.dwWidth = D3D_preferred_state.width;
  ddsd2.dwHeight = D3D_preferred_state.height;
  memset(&ddsd2.ddpfPixelFormat, 0, sizeof(ddsd2.ddpfPixelFormat));

  found_format = 0;
  // Try to find a 32bit z buffer
  if (FindArg("-z32bit")) {
    for (i = 0; i < NumZDepths && found_format == -1; i++) {
      if (ZPixFormats[i].dwZBufferBitDepth == 32)
        found_format = i;
    }

    // Couldn't find a 32bit z, just use first one
    if (found_format == -1)
      found_format = 0;
    else
      mprintf(0, "Found a 32bit zbuffer.\n");
  }

  ddsd2.ddpfPixelFormat = ZPixFormats[found_format];

  // This should be used for hardware
  ddsd2.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
  ddrval = lpDD->CreateSurface(&ddsd2, &lpZBuffer, NULL);
  if (ddrval != DD_OK) {
    mprintf(0, "D3D_INIT: Create Zbuffer failed.\nError=%s\n", d3d_ErrorString(ddrval));
    rend_SetErrorMessage("Creating zbuffer failed.");
    goto D3DError;
  }

  if (lpBackBuffer->AddAttachedSurface(lpZBuffer) != DD_OK) {
    mprintf(0, "D3D_INIT: Attach Zbuffer failed.\n");
    rend_SetErrorMessage("Attach ZBuffer failed.");
    goto D3DError;
  }

  // Create the D3D device
  ddrval = lpD3D->CreateDevice(dd->guid_3d, lpBackBuffer, &lpD3DDevice, 0);

  if (ddrval != DD_OK) {
    rend_SetErrorMessage("Create D3D Device3 failed.");
    mprintf(0, "D3D_INIT: Create D3D Device3 failed. %s\n", d3d_ErrorString(ddrval));

    if (retried == false) {
      retried = true;
      d3d_Close();
      D3D_preferred_state.width = 640;
      D3D_preferred_state.height = 480;
      D3D_preferred_state.bit_depth = 16;
      retval = -1;
      goto TryAgain;
    } else {
      goto D3DError;
    }
  }

  // Create and add viewport

  ddrval = lpD3D->CreateViewport(&lpViewport, NULL);
  if (ddrval != DD_OK) {
    rend_SetErrorMessage("CreateViewport failed.");
    mprintf(0, "D3D_INIT: CreateViewport failed.\n");
    goto D3DError;
  }

  ddrval = lpD3DDevice->AddViewport(lpViewport);
  if (ddrval != DD_OK) {
    rend_SetErrorMessage("AddViewport failed.");
    mprintf(0, "D3D_INIT: AddViewport failed.\n");
    goto D3DError;
  }

  // Setup the viewport for a reasonable viewing area
  D3DVIEWPORT2 viewdata;

  memset(&viewdata, 0, sizeof(viewdata));

  // Compensate for aspect ratio

  viewdata.dwSize = sizeof(viewdata);
  viewdata.dwX = viewdata.dwY = 0;
  viewdata.dwWidth = D3D_preferred_state.width;
  viewdata.dwHeight = D3D_preferred_state.height;
  viewdata.dvMinZ = 0.0F;
  viewdata.dvMaxZ = 5000.0;
  viewdata.dvClipX = -1.0;
  viewdata.dvClipY = -((float)D3D_preferred_state.height / (float)D3D_preferred_state.width);
  viewdata.dvClipWidth = 2.0;
  viewdata.dvClipHeight = ((float)D3D_preferred_state.height / (float)D3D_preferred_state.width) * 2;

  ddrval = lpViewport->SetViewport2(&viewdata);

  if (ddrval != DD_OK) {
    rend_SetErrorMessage("SetViewport failed.");
    mprintf(0, "D3D_INIT: SetViewport failed.\n");
    goto D3DError;
  }

  ddrval = lpD3DDevice->SetCurrentViewport(lpViewport);
  if (ddrval != DD_OK) {
    rend_SetErrorMessage("SetCurrentViewport failed.");
    mprintf(0, "D3D_INIT: SetCurrentViewport failed.\n");
    goto D3DError;
  }

  d3d_GetCaps();

  if (!d3d_TextureCacheInit()) {
    goto D3DError;
  }

  mprintf(0, "Direct3D Initialized OK!\n");

  d3d_SetDefaultStates();

  D3D_state.initted = 1;

  return retval;

D3DError:
  mprintf(0, "Direct3D Initialization failed.\n");

  d3d_Close();
  Int3();

  return 0;
}

// Releases the rendering context
void d3d_Close() {

  if (lpColorControl) {
    lpColorControl->Release();
    lpColorControl = NULL;
  }

  if (lpViewport) {
    lpViewport->Release();
    lpViewport = NULL;
  }

  if (lpD3DDevice) {
    lpD3DDevice->Release();
    lpD3DDevice = NULL;
  }

  if (lpZBuffer) {
    lpZBuffer->Release();
    lpZBuffer = NULL;
  }

  if (lpBackBuffer) {
    lpBackBuffer->Release();
    lpBackBuffer = NULL;
  }

  if (lpFrontBuffer) {
    lpFrontBuffer->Release();
    lpFrontBuffer = NULL;
  }

  if (lpD3D) {
    lpD3D->EvictManagedTextures();
    d3d_FreeTextureCache();
    lpD3D->Release();
    lpD3D = NULL;
  }

  if (lpDD1) {

    HRESULT ddrval;
    HWND hwnd = (HWND)((oeWin32Application *)ParentApplication)->m_hWnd;

    ddrval = lpDD->RestoreDisplayMode();
    if (ddrval != DD_OK) {
      mprintf(0, "RestoreDisplayMode failed (0x%x)\n", ddrval);
    }

    ddrval = lpDD->SetCooperativeLevel(hwnd, DDSCL_NORMAL);
    if (ddrval != DD_OK) {
      mprintf(0, "WIN_DD32: SetCooperativeLevel W Failed (0x%x)\n", ddrval);
    }

    lpDD1->Release();
    lpDD1 = NULL;
  }

  D3D_state.initted = 0;
}

// Sets the flat color...used for screen clears and the like
void d3d_SetFlatColor(ddgr_color color) {
  if (D3D_state.cur_color == color)
    return;

  D3D_state.cur_color = color;
}

// returns the alpha that we should use
int d3d_GetAlphaMultiplier() {
  switch (D3D_state.cur_alpha_type) {
  case AT_ALWAYS:
    return 255;
  case AT_CONSTANT:
    return D3D_state.cur_alpha;
  case AT_TEXTURE:
    return 255;
  case AT_CONSTANT_TEXTURE:
    return D3D_state.cur_alpha;
  case AT_VERTEX:
    return 255;
  case AT_CONSTANT_TEXTURE_VERTEX:
  case AT_CONSTANT_VERTEX:
    return D3D_state.cur_alpha;
  case AT_TEXTURE_VERTEX:
    return 255;
  case AT_LIGHTMAP_BLEND:
  case AT_LIGHTMAP_BLEND_SATURATE:
    return D3D_state.cur_alpha;
  case AT_SATURATE_TEXTURE:
    return D3D_state.cur_alpha;
  case AT_SATURATE_VERTEX:
    return 255;
  case AT_SATURATE_CONSTANT_VERTEX:
    return D3D_state.cur_alpha;
  case AT_SATURATE_TEXTURE_VERTEX:
    return 255;
  case AT_SPECULAR:
    return 255;
  default:
    mprintf(0, "Unrecognized alpha type=%d\n", D3D_state.cur_alpha_type);
    // Int3();		// no type defined,get jason
    return 255;
  }
}

// Sets the alpha multiply factor
void d3d_SetAlphaMultiplier() { Alpha_multiplier = d3d_GetAlphaMultiplier(); }

extern bool Force_one_texture;
// Sets up our bitmap/lightmap/bumpmap to be the next thing drawn
int d3d_MakeBitmapCurrent(int handle, int map_type, int tn) {
  LPDIRECT3DTEXTURE2 tex_interface;
  HRESULT ddrval;
  LPDIRECTDRAWSURFACE4 sp;

  if (map_type == MAP_TYPE_BITMAP) {
    if (Force_one_texture)
      handle = 0;

    if (GameBitmaps[handle].cache_slot == -1) {
      int retval = d3d_CreateTextureFromBitmap(handle, map_type);
      if (retval < 0)
        return 0;
    } else {
      if (GameBitmaps[handle].flags & BF_CHANGED) {
        d3d_UploadBitmapToSurface(handle, map_type, GameBitmaps[handle].cache_slot, 0);
      }
    }

    ASSERT(GameBitmaps[handle].cache_slot != -1);

    sp = BitmapTextureSurfaces[GameBitmaps[handle].cache_slot];
  } else if (map_type == MAP_TYPE_BUMPMAP) {
    if (GameBumpmaps[handle].cache_slot == -1) {
      int retval = d3d_CreateTextureFromBitmap(handle, map_type);
      if (retval < 0)
        return 0;
    } else {
      if (GameBumpmaps[handle].flags & BUMPF_CHANGED) {
        d3d_UploadBitmapToSurface(handle, map_type, GameBumpmaps[handle].cache_slot, 0);
      }
    }

    ASSERT(GameBumpmaps[handle].cache_slot != -1);

    sp = BumpmapTextureSurfaces[GameBumpmaps[handle].cache_slot];
  } else {
    if (Force_one_texture)
      handle = 0;

    if (GameLightmaps[handle].cache_slot == -1) {
      int retval = d3d_CreateTextureFromBitmap(handle, map_type);
      if (retval < 0)
        return 0;
    } else {
      if (GameLightmaps[handle].flags & LF_CHANGED) {
        d3d_UploadBitmapToSurface(handle, map_type, GameLightmaps[handle].cache_slot, 0);
      }
    }

    ASSERT(GameLightmaps[handle].cache_slot != -1);
    sp = LightmapTextureSurfaces[GameLightmaps[handle].cache_slot];
  }

  int texnum = handle;
  if (map_type == MAP_TYPE_LIGHTMAP)
    texnum += 100000;
  else if (map_type == MAP_TYPE_BUMPMAP)
    texnum += 200000;

  if (Last_texture_bound[tn] != texnum) {
    ddrval = sp->QueryInterface(IID_IDirect3DTexture2, (void **)&tex_interface);
    if (ddrval != S_OK) {
      mprintf(0, "D3D:MakeBitmapCurrent error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
      return 0;
    }

    if (lpD3DDevice->SetTexture(tn, tex_interface) != D3D_OK) {
      tex_interface->Release();
      return 0;
    }

    D3D_sets_this_frame[0]++;
    Last_texture_bound[tn] = texnum;
    tex_interface->Release();
  }

  return 1;
}

// Sets up our rendering pipeline for bumpmapping
void d3d_SetBumpmappingBlendModes(bool state) {
  ASSERT(d3d_CanBumpmap);

  if (D3D_bumpmap_state == state)
    return;

  D3D_bumpmap_state = state;

  if (state) {
    // Bump Texture
    //
    lpD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BUMPENVMAP);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);

    float _val = 0;

    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT00, *(DWORD *)(&(_val = 1.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT01, *(DWORD *)(&(_val = 0.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT10, *(DWORD *)(&(_val = 0.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVMAT11, *(DWORD *)(&(_val = 1.0f)));

    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVLSCALE, *(DWORD *)(&(_val = 1.0f)));
    lpD3DDevice->SetTextureStageState(1, D3DTSS_BUMPENVLOFFSET, *(DWORD *)(&(_val = 0.0f)));

    // Environment Texture
    //

    lpD3DDevice->SetTextureStageState(2, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 1);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);

    // Environment Texture
    //
    // lpD3DDevice->SetTexture(2, d3d_EnvironmentMap);
  } else {
    lpD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);

    lpD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
  }
}

// Turns on/off multitexture blending
void d3d_SetMultiTextureBlendMode(bool state) {
  if (D3D_multitexture_state == state && D3D_bumpmap_state == 0)
    return;

  D3D_multitexture_state = state;
  D3D_bumpmap_state = 0;

  if (state) {
    if (Overlay_type == OT_BLEND_SATURATE) {
      lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
      lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_ADD);
    } else {
      lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
      lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    }
  } else {
    lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
  }
}

struct FlatVertex {
  float x, y, z;
  float w;
  DWORD color;
  DWORD specular;
};

struct TextureVertex {
  float x, y, z;
  float w;
  DWORD color;
  DWORD specular;
  float u1, v1;
};

struct MultiTextureVertex {
  float x, y, z;
  float w;
  DWORD color;
  DWORD specular;
  float u1, v1;
  float u2, v2;
};

static TextureVertex TVerts[100];
static MultiTextureVertex MTVerts[100];
static FlatVertex FlatVerts[100];

// Takes nv vertices and draws the polygon defined by those vertices.
void d3d_DrawFlatPolygon(g3Point **p, int nv) {
  HRESULT ddrval;

  int alpha = Alpha_multiplier * d3d_Alpha_factor;

  for (int i = 0; i < nv; i++) {
    int r, g, b;
    g3Point *pnt = p[i];
    TVerts[i].x = pnt->p3_sx + D3D_state.clip_x1;
    TVerts[i].y = pnt->p3_sy + D3D_state.clip_y1;
    TVerts[i].z = std::max(0, 1.0 - (1.0 / (pnt->p3_z + (Z_bias + d3d_WBias))));
    TVerts[i].w = 1.0 / (pnt->p3_z + Z_bias + d3d_WBias);

    TVerts[i].u1 = pnt->p3_u;
    TVerts[i].v1 = pnt->p3_v;

    if (D3D_state.cur_alpha_type & ATF_VERTEX)
      alpha = (pnt->p3_a * (float)Alpha_multiplier * d3d_Alpha_factor);

    if (D3D_state.cur_fog_state) {

      float fog;
      DWORD fogval;

      if (pnt->p3_z < D3D_state.cur_fog_start)
        fogval = 255;
      else if (pnt->p3_z > D3D_state.cur_fog_end)
        fogval = 0;
      else {
        float val = pnt->p3_z - D3D_state.cur_fog_start;
        fog = val / d3d_FogDiff;
        fogval = ((1 - fog) * 255.0);
      }

      TVerts[i].specular = (fogval << 24);
    }

    if (D3D_state.cur_light_state != LS_NONE) {
      // Do lighting based on intesity (MONO) or colored (RGB)
      if (D3D_state.cur_color_model == CM_MONO) {
        r = pnt->p3_l * 255.0;
        g = pnt->p3_l * 255.0;
        b = pnt->p3_l * 255.0;
      } else {
        if (D3D_state.cur_light_state == LS_FLAT_GOURAUD) {
          r = GR_COLOR_RED(D3D_state.cur_color);
          g = GR_COLOR_GREEN(D3D_state.cur_color);
          b = GR_COLOR_BLUE(D3D_state.cur_color);
        } else {
          r = pnt->p3_r * 255.0;
          g = pnt->p3_g * 255.0;
          b = pnt->p3_b * 255.0;
        }
      }
    } else {
      r = GR_COLOR_RED(D3D_state.cur_color);
      g = GR_COLOR_GREEN(D3D_state.cur_color);
      b = GR_COLOR_BLUE(D3D_state.cur_color);
    }

    TVerts[i].color = (alpha << 24) | (r << 16) | (g << 8) | b;
  }

  D3D_polys_drawn++;
  D3D_verts_processed += nv;
  ddrval =
      lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, D3DFVF_TEX1 | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_XYZRHW,
                                 (LPVOID)TVerts, nv, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS);

  if (ddrval != DD_OK) {
    mprintf(0, "D3D:DrawFlatPolygon error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
  }
}

// Draws an bumpmapped polygon over the existing polygon
int d3d_DrawBumpmappedPolygon(g3Point **p, int nv, int handle) {

  ASSERT(Overlay_type == OT_NONE);
  //	ASSERT (BumpmapTextureSurfaces[handle] != NULL);

  HRESULT ddrval;

  int alpha = Alpha_multiplier * d3d_Alpha_factor;
  float one_over_cur_far_z = 1.0 / D3D_state.cur_far_z;

  for (int i = 0; i < nv; i++) {
    int r, g, b;

    g3Point *pnt = p[i];
    MultiTextureVertex *tvert = &MTVerts[i];

    tvert->x = pnt->p3_sx + D3D_state.clip_x1;
    tvert->y = pnt->p3_sy + D3D_state.clip_y1;
    tvert->z = std::max(0, 1.0 - (1.0 / (pnt->p3_z + (Z_bias + d3d_WBias))));
    tvert->w = 1.0 / (pnt->p3_z + Z_bias + d3d_WBias);

    tvert->u1 = pnt->p3_u;
    tvert->v1 = pnt->p3_v;

    tvert->u2 = pnt->p3_u2;
    tvert->v2 = pnt->p3_v2;

    if (D3D_state.cur_alpha_type & ATF_VERTEX)
      alpha = (pnt->p3_a * (float)Alpha_multiplier * d3d_Alpha_factor);

    if (D3D_state.cur_fog_state) {

      float fog;
      DWORD fogval;

      if (pnt->p3_z < D3D_state.cur_fog_start)
        fogval = 255;
      else if (pnt->p3_z > D3D_state.cur_fog_end)
        fogval = 0;
      else {
        float val = pnt->p3_z - D3D_state.cur_fog_start;
        fog = val / d3d_FogDiff;
        fogval = ((1 - fog) * 255.0);
      }

      tvert->specular = (fogval << 24);
    }

    if (D3D_state.cur_light_state != LS_NONE) {
      // Do lighting based on intesity (MONO) or colored (RGB)
      if (D3D_state.cur_color_model == CM_MONO) {
        r = pnt->p3_l * 255.0;
        g = pnt->p3_l * 255.0;
        b = pnt->p3_l * 255.0;
      } else {
        if (D3D_state.cur_light_state == LS_FLAT_GOURAUD) {
          r = GR_COLOR_RED(D3D_state.cur_color);
          g = GR_COLOR_GREEN(D3D_state.cur_color);
          b = GR_COLOR_BLUE(D3D_state.cur_color);
        } else {
          r = pnt->p3_r * 255.0;
          g = pnt->p3_g * 255.0;
          b = pnt->p3_b * 255.0;
        }
      }
    } else {
      r = 255;
      g = 255;
      b = 255;
    }

    tvert->color = (alpha << 24) | (r << 16) | (g << 8) | b;
  }

  if (!d3d_MakeBitmapCurrent(handle, MAP_TYPE_BITMAP, 0)) {
    mprintf(0, "Couldn't make the map current!\n");
    return 0;
  }

  if (!d3d_MakeBitmapCurrent(Bump_map, MAP_TYPE_BUMPMAP, 1)) {
    mprintf(0, "could not set bump mapping blend modes\n");
    return 0;
  }

  if (d3d_EnvironmentMap == -1) {
    mprintf(0, "Couldn't make environment map!\n");
    return 0;
  }

  if (!d3d_MakeBitmapCurrent(d3d_EnvironmentMap, MAP_TYPE_BITMAP, 2)) {
    mprintf(0, "Couldn't set environment map!\n");
    return 0;
  }

  d3d_SetBumpmappingBlendModes(1);

  D3D_polys_drawn++;
  D3D_verts_processed += nv;

  ddrval =
      lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, D3DFVF_TEX2 | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_XYZRHW,
                                 (LPVOID)MTVerts, nv, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS);

  if (ddrval != DD_OK) {
    mprintf(0, "D3D:DrawBumpmappedPolygon error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
  }

  return 1;
}

// Draws an overlay polygon over the existing polygon
void d3d_DrawMultiTexturePolygon(g3Point **p, int nv, int handle, int map_type) {
  HRESULT ddrval;

  int alpha = Alpha_multiplier * d3d_Alpha_factor;
  float one_over_square_res = 1.0 / GameLightmaps[Overlay_map].square_res;
  float one_over_cur_far_z = 1.0 / D3D_state.cur_far_z;

  float xscalar = (float)GameLightmaps[Overlay_map].width * one_over_square_res;
  float yscalar = (float)GameLightmaps[Overlay_map].height * one_over_square_res;

  float lmdiff = (1.0 / GameLightmaps[Overlay_map].square_res) / 2.0;

  for (int i = 0; i < nv; i++) {
    int r, g, b;

    g3Point *pnt = p[i];
    MultiTextureVertex *tvert = &MTVerts[i];

    tvert->x = pnt->p3_sx + D3D_state.clip_x1;
    tvert->y = pnt->p3_sy + D3D_state.clip_y1;
    tvert->z = std::max(0, 1.0 - (1.0 / (pnt->p3_z + (Z_bias + d3d_WBias))));
    tvert->w = 1.0 / (pnt->p3_z + Z_bias + d3d_WBias);

    tvert->u1 = pnt->p3_u + UV_diff;
    tvert->v1 = pnt->p3_v + UV_diff;

    tvert->u2 = (pnt->p3_u2 * xscalar) + lmdiff;
    tvert->v2 = (pnt->p3_v2 * yscalar) + lmdiff;

    if (D3D_state.cur_alpha_type & ATF_VERTEX)
      alpha = (pnt->p3_a * (float)Alpha_multiplier * d3d_Alpha_factor);

    if (D3D_state.cur_fog_state) {

      float fog;
      DWORD fogval;

      if (pnt->p3_z < D3D_state.cur_fog_start)
        fogval = 255;
      else if (pnt->p3_z > D3D_state.cur_fog_end)
        fogval = 0;
      else {
        float val = pnt->p3_z - D3D_state.cur_fog_start;
        fog = val / d3d_FogDiff;
        fogval = ((1 - fog) * 255.0);
      }

      tvert->specular = (fogval << 24);
    }

    if (D3D_state.cur_light_state != LS_NONE) {
      // Do lighting based on intesity (MONO) or colored (RGB)
      if (D3D_state.cur_color_model == CM_MONO) {
        r = pnt->p3_l * 255.0;
        g = pnt->p3_l * 255.0;
        b = pnt->p3_l * 255.0;
      } else {
        if (D3D_state.cur_light_state == LS_FLAT_GOURAUD) {
          r = GR_COLOR_RED(D3D_state.cur_color);
          g = GR_COLOR_GREEN(D3D_state.cur_color);
          b = GR_COLOR_BLUE(D3D_state.cur_color);
        } else {
          r = pnt->p3_r * 255.0;
          g = pnt->p3_g * 255.0;
          b = pnt->p3_b * 255.0;
        }
      }
    } else {
      r = 255;
      g = 255;
      b = 255;
    }

    tvert->color = (alpha << 24) | (r << 16) | (g << 8) | b;
  }

  if (!d3d_MakeBitmapCurrent(handle, map_type, 0)) {
    mprintf(0, "Couldn't make the map current!\n");
    return;
  }

  if (!d3d_MakeBitmapCurrent(Overlay_map, MAP_TYPE_LIGHTMAP, 1)) {
    mprintf(0, "Couldn't make the map current!\n");
    return;
  }

  d3d_SetMultiTextureBlendMode(true);

  D3D_polys_drawn++;
  D3D_verts_processed += nv;
  ddrval =
      lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, D3DFVF_TEX2 | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_XYZRHW,
                                 (LPVOID)MTVerts, nv, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS);

  if (ddrval != DD_OK) {
    mprintf(0, "D3D:DrawPolygon error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
  }
}

// Takes nv vertices anddraws the polygon defined by those vertices.  Uses bitmap "handle"
// as a texture
void d3d_DrawPolygon(int handle, g3Point **p, int nv, int map_type) {
  HRESULT ddrval;
  TextureVertex *tvert_ptr;
  int i;

  if (d3d_CanBumpmap && Bumpmap_ready) {
    ASSERT(Overlay_type == OT_NONE);

    if (!d3d_DrawBumpmappedPolygon(p, nv, handle)) {
      mprintf(0, "error in d3d_DrawBumpmappedPolygon\n");
    }

    rend_SetBumpmapReadyState(0, 0);

    return;
  }

  if (d3d_CanBumpmap && D3D_bumpmap_state)
    d3d_SetBumpmappingBlendModes(0);

  if ((!D3D_state.cur_texture_quality)) {
    if (D3D_state.cur_alpha_type == AT_SPECULAR) {
      if (!d3d_MakeBitmapCurrent(handle, map_type, 0))
        return;
    }

    if (d3d_MultiTexture) // If this device can do multitexture, clear it so it won't
      d3d_SetMultiTextureBlendMode(false);

    d3d_DrawFlatPolygon(p, nv);

    return;
  }

  // Figure out subpixel correction for UVs
  if (d3d_SubpixelCorrect) {
    if (map_type == MAP_TYPE_BITMAP) {
      UV_diff = (1.0 / (float)bm_w(handle, 0)) / 2.0;
    } else if (map_type == MAP_TYPE_LIGHTMAP) {
      UV_diff = (1.0 / (float)lm_w(handle)) / 2.0;
    } else
      UV_diff = 0;
  } else
    UV_diff = 0;

  if (Overlay_type != OT_NONE && d3d_MultiTexture) {
    d3d_DrawMultiTexturePolygon(p, nv, handle, map_type);

    return;
  }

  int alpha = Alpha_multiplier * d3d_Alpha_factor;

  for (i = 0; i < nv; i++) {
    int r, g, b;

    g3Point *pnt = p[i];
    tvert_ptr = &TVerts[i];
    tvert_ptr->x = pnt->p3_sx + D3D_state.clip_x1;
    tvert_ptr->y = pnt->p3_sy + D3D_state.clip_y1;
    tvert_ptr->z = std::max(0, 1.0 - (1.0 / (pnt->p3_z + (Z_bias + d3d_WBias))));
    tvert_ptr->w = 1.0 / (pnt->p3_z + Z_bias + d3d_WBias);

    tvert_ptr->u1 = pnt->p3_u + UV_diff;
    tvert_ptr->v1 = pnt->p3_v + UV_diff;

    if (D3D_state.cur_alpha_type & ATF_VERTEX)
      alpha = (pnt->p3_a * (float)Alpha_multiplier * d3d_Alpha_factor);

    if (D3D_state.cur_fog_state) {

      float fog;
      DWORD fogval;

      if (pnt->p3_z < D3D_state.cur_fog_start)
        fogval = 255;
      else if (pnt->p3_z > D3D_state.cur_fog_end)
        fogval = 0;
      else {
        float val = pnt->p3_z - D3D_state.cur_fog_start;
        fog = val / d3d_FogDiff;
        fogval = ((1 - fog) * 255.0);
      }

      tvert_ptr->specular = (fogval << 24);
    }

    if (D3D_state.cur_light_state != LS_NONE) {
      if (D3D_state.cur_light_state == LS_FLAT_GOURAUD) {
        r = GR_COLOR_RED(D3D_state.cur_color);
        g = GR_COLOR_GREEN(D3D_state.cur_color);
        b = GR_COLOR_BLUE(D3D_state.cur_color);
      } else {
        // Do lighting based on intesity (MONO) or colored (RGB)
        if (D3D_state.cur_color_model == CM_MONO) {
          r = pnt->p3_l * 255.0;
          g = r;
          b = r;
        } else {
          r = pnt->p3_r * 255.0;
          g = pnt->p3_g * 255.0;
          b = pnt->p3_b * 255.0;
        }
      }
    } else {
      r = 255;
      g = 255;
      b = 255;
    }

    tvert_ptr->color = (alpha << 24) | (r << 16) | (g << 8) | b;
  }

  if (!d3d_MakeBitmapCurrent(handle, map_type, 0)) {
    mprintf(0, "Couldn't make the map current!\n");
    return;
  }

  if (d3d_MultiTexture) // If this device can do multitexture, clear it so it won't
    d3d_SetMultiTextureBlendMode(false);

  D3D_polys_drawn++;
  D3D_verts_processed += nv;
  ddrval =
      lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, D3DFVF_TEX1 | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_XYZRHW,
                                 (LPVOID)TVerts, nv, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS);

  // Now draw an overlay
  if (Overlay_type != OT_NONE) {
    if (Overlay_type == OT_BLEND || Overlay_type == OT_BLEND_SATURATE) {
      int8_t atype = D3D_state.cur_alpha_type;

      if (Overlay_type == OT_BLEND)
        d3d_SetAlphaType(AT_LIGHTMAP_BLEND);
      else
        d3d_SetAlphaType(AT_LIGHTMAP_BLEND_SATURATE);

      if (!d3d_MakeBitmapCurrent(Overlay_map, MAP_TYPE_LIGHTMAP, 0)) {
        mprintf(0, "Couldn't make the map current!\n");
        return;
      }

      float xscalar = (float)GameLightmaps[Overlay_map].width / (float)GameLightmaps[Overlay_map].square_res;
      float yscalar = (float)GameLightmaps[Overlay_map].height / (float)GameLightmaps[Overlay_map].square_res;

      for (int i = 0; i < nv; i++) {
        g3Point *pnt = p[i];

        TVerts[i].u1 = pnt->p3_u2 * xscalar;
        TVerts[i].v1 = pnt->p3_v2 * yscalar;
      }

      D3D_polys_drawn++;
      D3D_verts_processed += nv;
      ddrval = lpD3DDevice->DrawPrimitive(
          D3DPT_TRIANGLEFAN,
          (1 << D3DFVF_TEXCOUNT_SHIFT) | D3DFVF_TEX0 | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_XYZRHW, (LPVOID)TVerts,
          nv, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS);
      d3d_SetAlphaType(atype);
    }
  }

  if (ddrval != DD_OK) {
    mprintf(0, "D3D:DrawPolygon error %d! %s\n", ddrval, d3d_ErrorString(ddrval));
  }
}

// Does whatever needs to be done to get D3D ready for the current frame
void d3d_BeginFrame(int x1, int y1, int x2, int y2, int clear_flags) {
  HRESULT ddrval;

  //	ASSERT (D3D_frame_started==0);

  ASSERT(x1 >= 0 && x1 <= D3D_state.screen_width);
  ASSERT(x2 >= 0 && x2 <= D3D_state.screen_width);
  ASSERT(y1 >= 0 && y1 <= D3D_state.screen_height);
  ASSERT(y2 >= 0 && y2 <= D3D_state.screen_height);

  D3D_state.clip_x1 = x1;
  D3D_state.clip_y1 = y1;
  D3D_state.clip_x2 = x2;
  D3D_state.clip_y2 = y2;

  ddrval = lpD3DDevice->BeginScene();
  if (ddrval != D3D_OK) {
    mprintf(0, "D3D:Failed to begin scene!\n%s\n", d3d_ErrorString(ddrval));
    return;
  }

  D3D_frame_started = 1;

  D3DRECT myrect;

  myrect.x1 = x1;
  myrect.x2 = x2;
  myrect.y1 = y1;
  myrect.y2 = y2;

  if (clear_flags & RF_CLEAR_ZBUFFER) {
    if (clear_flags & RF_CLEAR_COLOR) {
      lpViewport->Clear2(1UL, &myrect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3D_state.cur_color, 1.0f, 0L);
    } else {
      lpViewport->Clear2(1UL, &myrect, D3DCLEAR_ZBUFFER, D3D_state.cur_color, 1.0f, 0L);
    }
  } else if (clear_flags & RF_CLEAR_COLOR) {
    lpViewport->Clear2(1UL, &myrect, D3DCLEAR_TARGET, D3D_state.cur_color, 1.0f, 0L);
  }
}

// Ends the frame
void d3d_EndFrame() {
  ASSERT(D3D_frame_started);
  HRESULT ddrval;
  ddrval = lpD3DDevice->EndScene();
  if (ddrval != D3D_OK) {
    mprintf(0, "D3D:Failed to end scene!\n%s\n", d3d_ErrorString(ddrval));
    return;
  }

  D3D_frame_started = 0;
}
// Flips the screen
void d3d_Flip() {
  HRESULT ddrval;

  ASSERT(D3D_frame_started == 0);

TryFlipAgain:
  if (lpFrontBuffer->IsLost() == DDERR_SURFACELOST) {
    lpFrontBuffer->Restore();
  }
  if (lpBackBuffer->IsLost() == DDERR_SURFACELOST) {
    lpBackBuffer->Restore();
  }
  if (lpZBuffer->IsLost() == DDERR_SURFACELOST) {
    lpZBuffer->Restore();
  }

  if (D3D_preferred_state.vsync_on)
    ddrval = lpFrontBuffer->Flip(NULL, DDFLIP_WAIT);
  else
    ddrval = lpFrontBuffer->Flip(NULL, NULL);

  if (ddrval == DDERR_SURFACELOST) {
    mprintf(0, "Front surface lost... attempting to restore...\n");
    Sleep(500); // Wait 1/2 second
    goto TryFlipAgain;
  }
/*else if (ddrval != DD_OK )
{
        mprintf(0,"D3D:Fullscreen flip failed! %s\n",d3d_ErrorString(ddrval) );
}*/

// Print stats from the current frame
#ifndef RELEASE
  int i;
  RTP_INCRVALUE(texture_uploads, D3D_uploads);
  RTP_INCRVALUE(polys_drawn, D3D_polys_drawn);
  mprintf_at(1, 1, 0, "Uploads=%d    Polys=%d   Verts=%d    ", D3D_uploads, D3D_polys_drawn, D3D_verts_processed);
  mprintf_at(1, 2, 0, "Sets= 0:%d   1:%d   2:%d   3:%d   ", D3D_sets_this_frame[0], D3D_sets_this_frame[1],
              D3D_sets_this_frame[2], D3D_sets_this_frame[3]);
  mprintf_at(1, 3, 0, "Sets= 4:%d   5:%d  ", D3D_sets_this_frame[4], D3D_sets_this_frame[5]);
  for (i = 0; i < 8; i++)
    D3D_sets_this_frame[i] = 0;
#endif

  D3D_last_frame_polys_drawn = D3D_polys_drawn;
  D3D_last_frame_verts_processed = D3D_verts_processed;
  D3D_last_uploads = D3D_uploads;

  D3D_polys_drawn = 0;
  D3D_verts_processed = 0;
  D3D_uploads = 0;
}

// Sets our texturing type (ie linear,persective,flat,etc)
void d3d_SetTextureType(texture_type state) {
  if (state != TT_FLAT)
    state = TT_PERSPECTIVE;

  if (state == D3D_state.cur_texture_type)
    return;

  D3D_sets_this_frame[1]++;

  switch (state) {
  case TT_FLAT:
    D3D_state.cur_texture_quality = 0;
    lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    break;
  case TT_LINEAR:
  case TT_LINEAR_SPECIAL:
  case TT_PERSPECTIVE:
  case TT_PERSPECTIVE_SPECIAL:
    lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

    D3D_state.cur_texture_quality = 2;
    break;
  default:
    Int3(); // huh? Get Jason
    break;
  }
  D3D_state.cur_texture_type = state;
}

// Sets the lighting state of D3D
void d3d_SetLightingState(light_state state) {
  // Don't do redundant state sets
  if (state == D3D_state.cur_light_state)
    return;

  D3D_sets_this_frame[2]++;

  switch (state) {
  case LS_NONE:
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
    D3D_state.cur_light_state = LS_NONE;
    break;
  case LS_FLAT_GOURAUD:
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
    D3D_state.cur_light_state = LS_FLAT_GOURAUD;
    break;
  case LS_GOURAUD:
  case LS_PHONG:
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
    D3D_state.cur_light_state = LS_GOURAUD;
    break;
  default:
    Int3();
    break;
  }
}

// Sets the D3D color model (either rgb or mono)
void d3d_SetColorModel(color_model state) {
  // Don't do redundant state sets
  if (state == D3D_state.cur_color_model)
    return;

  switch (state) {
  case CM_MONO:
    D3D_state.cur_color_model = CM_MONO;
    break;
  case CM_RGB:
    D3D_state.cur_color_model = CM_RGB;
    break;
  default:
    Int3();
    break;
  }
}

// Sets the state of bilinear filtering for our textures
void d3d_SetFiltering(int8_t state) {
  int8_t curstate = (int8_t)state;

  if (curstate == D3D_state.cur_bilinear_state)
    return;

  D3D_sets_this_frame[3]++;

  D3D_state.cur_bilinear_state = curstate;

  if (state && D3D_preferred_state.filtering) {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_LINEAR);
  } else {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_POINT);
  }
}

// Sets the state of zbuffering to on or off
void d3d_SetZBufferState(int8_t state) {
  if (state == D3D_state.cur_zbuffer_state)
    return;

  D3D_sets_this_frame[4]++;

  D3D_state.cur_zbuffer_state = state;

  if (state) {
    if (d3d_WBuffer)
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
    else
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);

  } else {
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
  }
}

int Last_z_buffer_write_mask_state = -1;

void d3d_SetZBufferWriteMask(int state) {
  if (state == Last_z_buffer_write_mask_state)
    return;

  D3D_sets_this_frame[4]++;

  Last_z_buffer_write_mask_state = state;

  if (state) {
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
  } else {
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
  }
}

// Sets our near and far clipping planes
void d3d_SetZValues(float nearz, float farz) {
  D3D_state.cur_near_z = nearz;
  D3D_state.cur_far_z = farz;
}

// Clears the display to a specified color
void d3d_ClearScreen(ddgr_color color) {
  D3DRECT myrect;

  myrect.x1 = 0;
  myrect.x2 = D3D_state.screen_width;
  myrect.y1 = 0;
  myrect.y2 = D3D_state.screen_height;

  lpViewport->Clear2(1UL, &myrect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0L);
}

// Clears the zbuffer
void d3d_ClearZBuffer() {
  D3DRECT myrect;

  myrect.x1 = 0;
  myrect.x2 = D3D_state.screen_width;
  myrect.y1 = 0;
  myrect.y2 = D3D_state.screen_height;

  lpViewport->Clear2(1UL, &myrect, D3DCLEAR_ZBUFFER, 0, 1.0f, 0L);
}

// Fills a rectangle on the display
void d3d_FillRect(ddgr_color color, int x1, int y1, int x2, int y2) {
  D3DRECT myrect;

  myrect.x1 = x1 + D3D_state.clip_x1;
  myrect.x2 = x2 + D3D_state.clip_x1;
  myrect.y1 = y1 + D3D_state.clip_y1;
  myrect.y2 = y2 + D3D_state.clip_y1;

  lpViewport->Clear2(1UL, &myrect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0L);
}

// Sets a pixel on the display
void d3d_SetPixel(ddgr_color color, int x, int y) {}

// Sets the alpha value
void d3d_SetAlphaValue(uint8_t val) {
  D3D_state.cur_alpha = val;
  d3d_SetAlphaMultiplier();
}

// Sets the overall alpha scale factor (all alpha values are scaled by this value)
// usefull for motion blur effect
void d3d_SetAlphaFactor(float val) { d3d_Alpha_factor = val; }

// Returns the current Alpha factor
float d3d_GetAlphaFactor(void) { return d3d_Alpha_factor; }

void d3d_SetAlwaysAlpha(bool state) {
  if (state) {
    if (Alpha_always_set != 1) {
      D3D_sets_this_frame[5]++;
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_ALWAYS);
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
      Alpha_always_set = 1;
    }
  } else {
    if (Alpha_always_set != 0) {
      D3D_sets_this_frame[5]++;
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATER);
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0);
      lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
      Alpha_always_set = 0;
    }
  }
}

// Sets the type of alpha blending you want
void d3d_SetAlphaType(int8_t atype) {

  if (atype == D3D_state.cur_alpha_type)
    return; // No redundant state setting

  D3D_sets_this_frame[5]++;

  switch (atype) {
  case AT_ALWAYS:
    d3d_SetAlwaysAlpha(true);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    break;
  case AT_TEXTURE:
    d3d_SetAlwaysAlpha(true);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_BLENDTEXTUREALPHA);
    break;
  case AT_CONSTANT:
    d3d_SetAlwaysAlpha(false);

    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

    break;
  case AT_LIGHTMAP_BLEND:
    d3d_SetAlwaysAlpha(false);

    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCCOLOR);

    // lpD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_BLENDTEXTUREALPHA );
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    break;
  case AT_VERTEX:
  case AT_CONSTANT_VERTEX:
    d3d_SetAlwaysAlpha(false);

    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
    break;
  case AT_CONSTANT_TEXTURE:
  case AT_CONSTANT_TEXTURE_VERTEX:
  case AT_TEXTURE_VERTEX:
    d3d_SetAlwaysAlpha(false);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
    break;
  case AT_SATURATE_VERTEX:
  case AT_SATURATE_CONSTANT_VERTEX:
    d3d_SetAlwaysAlpha(false);

    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
    break;
  case AT_SATURATE_TEXTURE:
  case AT_SATURATE_TEXTURE_VERTEX:
  case AT_LIGHTMAP_BLEND_SATURATE:
    d3d_SetAlwaysAlpha(false);

    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    break;
  case AT_SPECULAR:
    d3d_SetAlwaysAlpha(false);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
    break;
  default:
    //			Int3();		// no type defined,get jason
    break;
  }

  D3D_state.cur_alpha_type = atype;
  d3d_SetAlphaMultiplier();
}

// Sets the near and far plane of fog
// Note, the d3d_Far_z variable must be valid for this function to work correctly
void d3d_SetFogBorders(float nearz, float farz) {

  D3D_state.cur_fog_start = nearz;
  D3D_state.cur_fog_end = farz;

  d3d_FogDiff = farz - nearz;

  return;
}

// Sets the fog state to on or off
void d3d_SetFogState(int8_t state) {
  if (!d3d_CanFog)
    state = 0;

  // if (state==D3D_state.cur_fog_state)
  //	return;

  if (state && d3d_CanFog) {
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, D3D_state.cur_fog_color);
  } else {
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
  }

  D3D_state.cur_fog_state = state;
}

// sets fog color
void d3d_SetFogColor(ddgr_color fogcolor) {
  if (fogcolor == D3D_state.cur_fog_color)
    return;

  lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, D3D_state.cur_fog_color);
  D3D_state.cur_fog_color = fogcolor;
}

// Draws a 2d line
void d3d_DrawLine(int x1, int y1, int x2, int y2) {
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetAlphaValue(255);
  rend_SetLighting(LS_NONE);
  rend_SetTextureType(TT_FLAT);

  g3Point p1, p2;

  if (x1 < 0)
    x1 = 0;
  if (y1 < 0)
    y1 = 0;
  if (x1 >= D3D_state.clip_x2)
    x1 = D3D_state.clip_x2 - 1;
  if (y1 >= D3D_state.clip_y2)
    y1 = D3D_state.clip_y2 - 1;

  if (x2 < 0)
    x2 = 0;
  if (y2 < 0)
    y2 = 0;
  if (x2 >= D3D_state.clip_x2)
    x2 = D3D_state.clip_x2 - 1;
  if (y2 >= D3D_state.clip_y2)
    y2 = D3D_state.clip_y2 - 1;

  p1.p3_sx = x1;
  p1.p3_sy = y1;
  p2.p3_sx = x2;
  p2.p3_sy = y2;

  p1.p3_z = .001f;
  p2.p3_z = .001f;

  d3d_DrawSpecialLine(&p1, &p2);
}

// Sets the D wrapping type
void d3d_SetWrapType(wrap_type val) {
  if (val == D3D_state.cur_wrap_type)
    return;

  D3D_sets_this_frame[6]++;

  D3D_state.cur_wrap_type = val;

  if (val == WT_WRAP) {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
  } else if (val == WT_CLAMP) {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

  } else if (val == WT_WRAP_V) {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
    lpD3DDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
  } else
    Int3(); // Get Jason
}

// Fills in projection variables
void d3d_GetProjectionParameters(int *width, int *height) {
  *width = D3D_state.clip_x2 - D3D_state.clip_x1;
  *height = D3D_state.clip_y2 - D3D_state.clip_y1;
}

// Returns the aspect ratio of the physical screen
float d3d_GetAspectRatio() {
  float aspect_ratio = (float)((3.0 * D3D_state.screen_width) / (4.0 * D3D_state.screen_height));
  return aspect_ratio;
}

// Draws a line using the states set by the renderer lib
void d3d_DrawSpecialLine(g3Point *p0, g3Point *p1) {
  int alpha = Alpha_multiplier * d3d_Alpha_factor;

  for (int i = 0; i < 2; i++) {
    int r, g, b;
    g3Point *pnt = p0;

    if (i)
      pnt = p1;

    FlatVerts[i].x = pnt->p3_sx + D3D_state.clip_x1;
    FlatVerts[i].y = pnt->p3_sy + D3D_state.clip_y1;
    // FlatVerts[i].z=std::min(1.0,(pnt->p3_z+(Z_bias+d3d_WBias))/D3D_state.cur_far_z);
    FlatVerts[i].z = std::max(0, 1.0 - (1.0 / (pnt->p3_z + (Z_bias + d3d_WBias))));
    FlatVerts[i].w = 1.0 / (pnt->p3_z + Z_bias + d3d_WBias);

    if (D3D_state.cur_alpha_type & ATF_VERTEX)
      alpha = (pnt->p3_a * (float)Alpha_multiplier * d3d_Alpha_factor);

    if (D3D_state.cur_fog_state) {

      float fog;
      DWORD fogval;

      if (pnt->p3_z < D3D_state.cur_fog_start)
        fogval = 255;
      else if (pnt->p3_z > D3D_state.cur_fog_end)
        fogval = 0;
      else {
        float val = pnt->p3_z - D3D_state.cur_fog_start;
        fog = val / d3d_FogDiff;
        fogval = ((1 - fog) * 255.0);
      }

      FlatVerts[i].specular = (fogval << 24);
    }

    if (D3D_state.cur_light_state != LS_NONE) {
      // Do lighting based on intesity (MONO) or colored (RGB)
      if (D3D_state.cur_color_model == CM_MONO) {
        r = pnt->p3_l * 255.0;
        g = pnt->p3_l * 255.0;
        b = pnt->p3_l * 255.0;
      } else {
        if (D3D_state.cur_light_state == LS_FLAT_GOURAUD) {
          r = GR_COLOR_RED(D3D_state.cur_color);
          g = GR_COLOR_GREEN(D3D_state.cur_color);
          b = GR_COLOR_BLUE(D3D_state.cur_color);
        } else {
          r = pnt->p3_r * 255.0;
          g = pnt->p3_g * 255.0;
          b = pnt->p3_b * 255.0;
        }
      }
    } else {
      r = GR_COLOR_RED(D3D_state.cur_color);
      g = GR_COLOR_GREEN(D3D_state.cur_color);
      b = GR_COLOR_BLUE(D3D_state.cur_color);
    }

    FlatVerts[i].color = (alpha << 24) | (r << 16) | (g << 8) | b;
  }
  lpD3DDevice->DrawPrimitive(D3DPT_LINELIST, D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_XYZRHW, (LPVOID)FlatVerts, 2,
                             D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS);
}

void d3d_SetMipState(int8_t state) {
  D3D_state.cur_mip_state = state;

  if (d3d_CanMip && state) {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_POINT);
  } else {
    lpD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_NONE);
  }
}

// Sets up a some global preferences for D3D
int d3d_SetPreferredState(renderer_preferred_state *pref_state) {
  int retval = 1;
  renderer_preferred_state old_state = D3D_preferred_state;
  mprintf(0, "In D3d_SetPreferredState\n");

  D3D_preferred_state = *pref_state;

  if (D3D_state.initted) {
    int reinit = 0;

    // Change gamma if needed
    if (pref_state->width != D3D_state.screen_width || pref_state->height != D3D_state.screen_height ||
        pref_state->bit_depth != old_state.bit_depth)
      reinit = 1;

    if (reinit) {
      d3d_Close();
      retval = d3d_Init(ParentApplication, &D3D_preferred_state);
    } else {
      if (old_state.gamma != pref_state->gamma) {
        d3d_SetGammaValue(pref_state->gamma);
      }

      if (old_state.mipping != pref_state->mipping) {
        d3d_SetMipState(pref_state->mipping);
      }
    }
  } else
    D3D_preferred_state = *pref_state;

  return retval;
}

// Sets the resolution that D3D uses
void d3d_SetResolution(int width, int height) {
  D3D_preferred_state.width = width;
  D3D_preferred_state.height = height;

  if (D3D_state.initted) {
    if (width != D3D_state.screen_width || height != D3D_state.screen_height) {
      d3d_Close();
      d3d_Init(ParentApplication, &D3D_preferred_state);
    }
  }
}

// Sets the gamma correction value
void d3d_SetGammaValue(float val) {
  D3D_preferred_state.gamma = val;

  if (!d3d_CanGamma)
    return;

  mprintf(0, "Setting gamma to %f\n", val);

  DDGAMMARAMP rampvals;

  for (int i = 0; i < 256; i++) {
    float norm = (float)i / 255.0;

    float newval = powf(norm, 1.0f / val);

    newval *= 65535;

    newval = std::min(65535, newval);
    newval = std::max(0, newval);

    rampvals.red[i] = newval;
    rampvals.green[i] = newval;
    rampvals.blue[i] = newval;
  }

  HRESULT rval = lpGammaControl->SetGammaRamp(0, &rampvals);
  mprintf(0, "Gamma return val is %d (%x) (%s)\n", rval, rval, d3d_ErrorString(rval));
}

// Gets the current state of the renderer
void d3d_GetRenderState(rendering_state *rstate) { memcpy(rstate, &D3D_state, sizeof(rendering_state)); }

// Sets the coplanar z bias for rendered polygons
void d3d_SetCoplanarPolygonOffset(float factor) {
  int16_t depth_level;

  if (d3d_ZBias && !d3d_WBuffer) {
    depth_level = (factor * 2);
    lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS, depth_level);
  } else {
    if (d3d_WBuffer)
      d3d_WBias = -factor / 4.0;
    else
      d3d_WBias = -factor;
  }
}

// Creates a on the video card if needed
void d3d_PreUploadTextureToCard(int handle, int map_type) {
  if (map_type == MAP_TYPE_BITMAP) {
    if (GameBitmaps[handle].cache_slot == -1) {
      d3d_CreateTextureFromBitmap(handle, map_type);
    }
  } else if (map_type == MAP_TYPE_BUMPMAP) {
    if (GameBumpmaps[handle].cache_slot == -1) {
      d3d_CreateTextureFromBitmap(handle, map_type);
    }
  } else {
    if (GameLightmaps[handle].cache_slot == -1) {
      d3d_CreateTextureFromBitmap(handle, map_type);
    }
  }
}

// Evicts local texture memory
void d3d_FreePreUploadedTexture(int handle, int map_type) {
  if (map_type == MAP_TYPE_BITMAP) {
    if (GameBitmaps[handle].cache_slot != -1) {
      BitmapTextureSurfaces[GameBitmaps[handle].cache_slot]->Release();
      GameBitmaps[handle].cache_slot = -1;
    }
  } else if (map_type == MAP_TYPE_BUMPMAP) {
    if (GameBumpmaps[handle].cache_slot != -1) {
      BumpmapTextureSurfaces[GameBumpmaps[handle].cache_slot]->Release();
      GameBumpmaps[handle].cache_slot = -1;
    }
  } else {
    if (GameLightmaps[handle].cache_slot != -1) {
      LightmapTextureSurfaces[GameLightmaps[handle].cache_slot]->Release();
      GameLightmaps[handle].cache_slot = -1;
    }
  }
}

int d3d_lfb_locked = 0;

// Locks the linear frame buffer for application access
void d3d_GetLFBLock(renderer_lfb *lfb) {
  if (d3d_lfb_locked != 0) {
    mprintf(0, "ERROR!!! You are trying to get an lfb lock and there already is one!\n");
    lfb->data = NULL;
    return;
  }

  DDSURFACEDESC2 surf_desc;
  HRESULT ddrval;

  memset(&surf_desc, 0, sizeof(DDSURFACEDESC2));
  surf_desc.dwSize = sizeof(DDSURFACEDESC2);
  surf_desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

  ddrval = lpBackBuffer->Lock(NULL, &surf_desc, DDLOCK_WAIT, NULL);

  if (ddrval == DD_OK) {
    lfb->data = (uint16_t *)surf_desc.lpSurface;
    lfb->bytes_per_row = surf_desc.lPitch;
    d3d_lfb_locked = 1;
  } else {
    lfb->data = NULL;
    lfb->bytes_per_row = 0;
  }
}

// Releases the previous LFB lock
void d3d_ReleaseLFBLock(renderer_lfb *lfb) {
  if (d3d_lfb_locked != 1) {
    mprintf(0, "ERROR!!! You are trying to release an LFB lock and there is none!\n");
    return;
  }

  // Release the lock
  lpBackBuffer->Unlock(NULL);
  d3d_lfb_locked = 0;
}

uint8_t d3d_Framebuffer_ready = 0;
uint16_t *d3d_Framebuffer_translate = NULL;

// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void d3d_SetFrameBufferCopyState(bool state) {
  if (state) {

    bool bit15 = false;
    ASSERT(d3d_Framebuffer_ready == 0);
    ASSERT(D3D_preferred_state.bit_depth == 16);
    d3d_Framebuffer_ready = 1;
    d3d_Framebuffer_translate = (uint16_t *)mem_malloc(32768 * 2);

    ASSERT(d3d_Framebuffer_translate);

    // Figure out to do 15 or 16bit
    DDPIXELFORMAT ddpf;
    ddpf.dwSize = sizeof(ddpf);
    HRESULT ddrval = lpFrontBuffer->GetPixelFormat(&ddpf);
    if (ddrval != DD_OK) {
      Int3();
      return;
    }

    bit15 = (ddpf.dwGBitMask == 0x03e0) ? true : false;

    for (int i = 0; i < 32768; i++) {
      int r = (i >> 10) & 0x1f;
      int g = (i >> 5) & 0x1f;
      int b = (i) & 0x1f;

      if (bit15 == false) {
        g <<= 1;

        d3d_Framebuffer_translate[i] = (r << 11) | (g << 5) | (b);
      } else {
        d3d_Framebuffer_translate[i] = (r << 10) | (g << 5) | (b);
      }
    }
  } else {
    ASSERT(d3d_Framebuffer_ready == 1);
    d3d_Framebuffer_ready = 0;
    mem_free(d3d_Framebuffer_translate);
  }
}

// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y
void d3d_CopyBitmapToFramebuffer(int bm_handle, int x, int y) {
  renderer_lfb lfb;

  ASSERT(d3d_Framebuffer_ready);

  lfb.data = NULL;
  lfb.type = LFB_LOCK_WRITE;

  d3d_GetLFBLock(&lfb);

  if (lfb.data == NULL)
    return; // No copy!

  int w = bm_w(bm_handle, 0);
  int h = bm_h(bm_handle, 0);

  uint16_t *dptr = lfb.data;
  uint16_t *sptr = (uint16_t *)bm_data(bm_handle, 0);

  dptr += (y * (lfb.bytes_per_row / 2));
  dptr += x;

  int i, t;

  for (i = 0; i < h; i++, dptr += (lfb.bytes_per_row / 2)) {
    for (t = 0; t < w; t++, sptr++) {
      dptr[t] = d3d_Framebuffer_translate[(*sptr & ~OPAQUE_FLAG)];
    }
  }

  d3d_ReleaseLFBLock(&lfb);
}

// Takes a screenshot of the frontbuffer and puts it into the passed bitmap handle
void d3d_Screenshot(int bm_handle) {
  uint16_t *dest_data;
  int i, t;
  DDSURFACEDESC2 surf_desc;
  HRESULT ddrval;
  int bitdepth;

  ASSERT((bm_w(bm_handle, 0)) == D3D_state.screen_width);
  ASSERT((bm_h(bm_handle, 0)) == D3D_state.screen_height);

  DDPIXELFORMAT ddpf;
  // do 8bit or 16bit copy depending on surface type
  ddpf.dwSize = sizeof(ddpf);
  ddrval = lpFrontBuffer->GetPixelFormat(&ddpf);
  if (ddrval != DD_OK)
    return;

  bitdepth = ddpf.dwRGBBitCount;

  dest_data = bm_data(bm_handle, 0);

  memset(&surf_desc, 0, sizeof(DDSURFACEDESC2));
  surf_desc.dwSize = sizeof(DDSURFACEDESC2);
  surf_desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

  ddrval = lpFrontBuffer->Lock(NULL, &surf_desc, DDLOCK_WAIT, NULL);

  if (ddrval == DD_OK) {
    int w = D3D_state.screen_width, h = D3D_state.screen_height;

    if (bitdepth == 16 || bitdepth == 15) {
      int shorts_per_row = surf_desc.lPitch / 2;
      bool bit15 = (ddpf.dwGBitMask == 0x03e0) ? true : false;

      uint16_t pix;

      uint16_t *rptr;
      rptr = (uint16_t *)surf_desc.lpSurface;

      // Go through and read our pixels

      if (bit15 == false) {
        // Do 16bit
        for (i = 0; i < h; i++) {
          for (t = 0; t < w; t++) {
            pix = rptr[i * shorts_per_row + t];

            int r = (pix >> 11 & 0x1f) << 3;
            int g = (pix >> 5 & 0x3f) << 2;
            int b = (pix & 0x1f) << 3;

            r = std::min(255, (float)r * 1.4f);
            g = std::min(255, (float)g * 1.4f);
            b = std::min(255, (float)b * 1.4f);

            pix = GR_RGB16(r, g, b);

            dest_data[i * w + t] = OPAQUE_FLAG | pix;
          }
        }

      } else {
        // Do 15 bit
        for (i = 0; i < h; i++) {
          for (t = 0; t < w; t++) {
            pix = rptr[i * shorts_per_row + t];

            int r = (pix >> 10 & 0x1f) << 3;
            int g = (pix >> 5 & 0x1f) << 3;
            int b = (pix & 0x1f) << 3;

            r = std::min(255, (float)r * 1.4f);
            g = std::min(255, (float)g * 1.4f);
            b = std::min(255, (float)b * 1.4f);

            pix = GR_RGB16(r, g, b);

            dest_data[i * w + t] = OPAQUE_FLAG | pix;
          }
        }
      }
    } else {
      int shorts_per_row = surf_desc.lPitch / 2;
      int ints_per_row = surf_desc.lPitch / 4;

      uint32_t pix;

      uint32_t *rptr;
      rptr = (uint32_t *)surf_desc.lpSurface;

      // Go through and read our pixels
      for (i = 0; i < h; i++) {
        for (t = 0; t < w; t++) {
          pix = rptr[i * ints_per_row + t];

          int r = (pix >> 16 & 0xff);
          int g = (pix >> 8 & 0xff);
          int b = (pix & 0xff);

          r = std::min(255, (float)r * 1.4f);
          g = std::min(255, (float)g * 1.4f);
          b = std::min(255, (float)b * 1.4f);

          int16_t short_pix = GR_RGB16(r, g, b);

          dest_data[i * w + t] = OPAQUE_FLAG | short_pix;
        }
      }
    }

    // Release the lock
    lpFrontBuffer->Unlock(NULL);
  } else {
    mprintf(0, "Couldn't get a lock to d3d front buffer!\n");
    Int3();
  }
}

// Returns a string describing the passed in error
const char *d3d_ErrorString(int error) {
  switch (error) {
  case DD_OK:
    return "No error.\0";
  case DDERR_ALREADYINITIALIZED:
    return "This object is already initialized.\0";
  case DDERR_BLTFASTCANTCLIP:
    return "Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
  case DDERR_CANNOTATTACHSURFACE:
    return "This surface can not be attached to the requested surface.\0";
  case DDERR_CANNOTDETACHSURFACE:
    return "This surface can not be detached from the requested surface.\0";
  case DDERR_CANTCREATEDC:
    return "Windows can not create any more DCs.\0";
  case DDERR_CANTDUPLICATE:
    return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
  case DDERR_CLIPPERISUSINGHWND:
    return "An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
  case DDERR_COLORKEYNOTSET:
    return "No src color key specified for this operation.\0";
  case DDERR_CURRENTLYNOTAVAIL:
    return "Support is currently not available.\0";
  case DDERR_DIRECTDRAWALREADYCREATED:
    return "A DirectDraw object representing this driver has already been created for this process.\0";
  case DDERR_EXCEPTION:
    return "An exception was encountered while performing the requested operation.\0";
  case DDERR_EXCLUSIVEMODEALREADYSET:
    return "An attempt was made to set the cooperative level when it was already set to exclusive.\0";
  case DDERR_GENERIC:
    return "Generic failure.\0";
  case DDERR_HEIGHTALIGN:
    return "Height of rectangle provided is not a multiple of reqd alignment.\0";
  case DDERR_HWNDALREADYSET:
    return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or "
           "palettes created.\0";
  case DDERR_HWNDSUBCLASSED:
    return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring "
           "state.\0";
  case DDERR_IMPLICITLYCREATED:
    return "This surface can not be restored because it is an implicitly created surface.\0";
  case DDERR_INCOMPATIBLEPRIMARY:
    return "Unable to match primary surface creation request with existing primary surface.\0";
  case DDERR_INVALIDCAPS:
    return "One or more of the caps bits passed to the callback are incorrect.\0";
  case DDERR_INVALIDCLIPLIST:
    return "DirectDraw does not support the provided cliplist.\0";
  case DDERR_INVALIDDIRECTDRAWGUID:
    return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
  case DDERR_INVALIDMODE:
    return "DirectDraw does not support the requested mode.\0";
  case DDERR_INVALIDOBJECT:
    return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
  case DDERR_INVALIDPARAMS:
    return "One or more of the parameters passed to the function are incorrect.\0";
  case DDERR_INVALIDPIXELFORMAT:
    return "The pixel format was invalid as specified.\0";
  case DDERR_INVALIDPOSITION:
    return "Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
  case DDERR_INVALIDRECT:
    return "Rectangle provided was invalid.\0";
  case DDERR_LOCKEDSURFACES:
    return "Operation could not be carried out because one or more surfaces are locked.\0";
  case DDERR_NO3D:
    return "There is no 3D present.\0";
  case DDERR_NOALPHAHW:
    return "Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
  case DDERR_NOBLTHW:
    return "No blitter hardware present.\0";
  case DDERR_NOCLIPLIST:
    return "No cliplist available.\0";
  case DDERR_NOCLIPPERATTACHED:
    return "No clipper object attached to surface object.\0";
  case DDERR_NOCOLORCONVHW:
    return "Operation could not be carried out because there is no color conversion hardware present or available.\0";
  case DDERR_NOCOLORKEY:
    return "Surface doesn't currently have a color key\0";
  case DDERR_NOCOLORKEYHW:
    return "Operation could not be carried out because there is no hardware support of the destination color key.\0";
  case DDERR_NOCOOPERATIVELEVELSET:
    return "Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
  case DDERR_NODC:
    return "No DC was ever created for this surface.\0";
  case DDERR_NODDROPSHW:
    return "No DirectDraw ROP hardware.\0";
  case DDERR_NODIRECTDRAWHW:
    return "A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
  case DDERR_NOEMULATION:
    return "Software emulation not available.\0";
  case DDERR_NOEXCLUSIVEMODE:
    return "Operation requires the application to have exclusive mode but the application does not have exclusive "
           "mode.\0";
  case DDERR_NOFLIPHW:
    return "Flipping visible surfaces is not supported.\0";
  case DDERR_NOGDI:
    return "There is no GDI present.\0";
  case DDERR_NOHWND:
    return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
  case DDERR_NOMIRRORHW:
    return "Operation could not be carried out because there is no hardware present or available.\0";
  case DDERR_NOOVERLAYDEST:
    return "Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to "
           "establish a destination.\0";
  case DDERR_NOOVERLAYHW:
    return "Operation could not be carried out because there is no overlay hardware present or available.\0";
  case DDERR_NOPALETTEATTACHED:
    return "No palette object attached to this surface.\0";
  case DDERR_NOPALETTEHW:
    return "No hardware support for 16 or 256 color palettes.\0";
  case DDERR_NORASTEROPHW:
    return "Operation could not be carried out because there is no appropriate raster op hardware present or "
           "available.\0";
  case DDERR_NOROTATIONHW:
    return "Operation could not be carried out because there is no rotation hardware present or available.\0";
  case DDERR_NOSTRETCHHW:
    return "Operation could not be carried out because there is no hardware support for stretching.\0";
  case DDERR_NOT4BITCOLOR:
    return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color "
           "palette.\0";
  case DDERR_NOT4BITCOLORINDEX:
    return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color "
           "index palette.\0";
  case DDERR_NOT8BITCOLOR:
    return "DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
  case DDERR_NOTAOVERLAYSURFACE:
    return "Returned when an overlay member is called for a non-overlay surface.\0";
  case DDERR_NOTEXTUREHW:
    return "Operation could not be carried out because there is no texture mapping hardware present or available.\0";
  case DDERR_NOTFLIPPABLE:
    return "An attempt has been made to flip a surface that is not flippable.\0";
  case DDERR_NOTFOUND:
    return "Requested item was not found.\0";
  case DDERR_NOTLOCKED:
    return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, "
           "has been attempted.\0";
  case DDERR_NOTPALETTIZED:
    return "The surface being used is not a palette-based surface.\0";
  case DDERR_NOVSYNCHW:
    return "Operation could not be carried out because there is no hardware support for vertical blank synchronized "
           "operations.\0";
  case DDERR_NOZBUFFERHW:
    return "Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
  case DDERR_NOZOVERLAYHW:
    return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z "
           "layering of overlays.\0";
  case DDERR_OUTOFCAPS:
    return "The hardware needed for the requested operation has already been allocated.\0";
  case DDERR_OUTOFMEMORY:
    return "DirectDraw does not have enough memory to perform the operation.\0";
  case DDERR_OUTOFVIDEOMEMORY:
    return "DirectDraw does not have enough memory to perform the operation.\0";
  case DDERR_OVERLAYCANTCLIP:
    return "The hardware does not support clipped overlays.\0";
  case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
    return "Can only have ony color key active at one time for overlays.\0";
  case DDERR_OVERLAYNOTVISIBLE:
    return "Returned when GetOverlayPosition is called on a hidden overlay.\0";
  case DDERR_PALETTEBUSY:
    return "Access to this palette is being refused because the palette is already locked by another thread.\0";
  case DDERR_PRIMARYSURFACEALREADYEXISTS:
    return "This process already has created a primary surface.\0";
  case DDERR_REGIONTOOSMALL:
    return "Region passed to Clipper::GetClipList is too small.\0";
  case DDERR_SURFACEALREADYATTACHED:
    return "This surface is already attached to the surface it is being attached to.\0";
  case DDERR_SURFACEALREADYDEPENDENT:
    return "This surface is already a dependency of the surface it is being made a dependency of.\0";
  case DDERR_SURFACEBUSY:
    return "Access to this surface is being refused because the surface is already locked by another thread.\0";
  case DDERR_SURFACEISOBSCURED:
    return "Access to surface refused because the surface is obscured.\0";
  case DDERR_SURFACELOST:
    return "Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object "
           "representing this surface should have Restore called on it.\0";
  case DDERR_SURFACENOTATTACHED:
    return "The requested surface is not attached.\0";
  case DDERR_TOOBIGHEIGHT:
    return "Height requested by DirectDraw is too large.\0";
  case DDERR_TOOBIGSIZE:
    return "Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
  case DDERR_TOOBIGWIDTH:
    return "Width requested by DirectDraw is too large.\0";
  case DDERR_UNSUPPORTED:
    return "Action not supported.\0";
  case DDERR_UNSUPPORTEDFORMAT:
    return "FOURCC format requested is unsupported by DirectDraw.\0";
  case DDERR_UNSUPPORTEDMASK:
    return "Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
  case DDERR_VERTICALBLANKINPROGRESS:
    return "Vertical blank is in progress.\0";
  case DDERR_WASSTILLDRAWING:
    return "Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is "
           "incomplete.\0";
  case DDERR_WRONGMODE:
    return "This surface can not be restored because it was created in a different mode.\0";
  case DDERR_XALIGN:
    return "Rectangle provided was not horizontally aligned on required boundary.\0";
  case D3DERR_BADMAJORVERSION:
    return "D3DERR_BADMAJORVERSION\0";
  case D3DERR_BADMINORVERSION:
    return "D3DERR_BADMINORVERSION\0";
  case D3DERR_EXECUTE_LOCKED:
    return "D3DERR_EXECUTE_LOCKED\0";
  case D3DERR_EXECUTE_NOT_LOCKED:
    return "D3DERR_EXECUTE_NOT_LOCKED\0";
  case D3DERR_EXECUTE_CREATE_FAILED:
    return "D3DERR_EXECUTE_CREATE_FAILED\0";
  case D3DERR_EXECUTE_DESTROY_FAILED:
    return "D3DERR_EXECUTE_DESTROY_FAILED\0";
  case D3DERR_EXECUTE_LOCK_FAILED:
    return "D3DERR_EXECUTE_LOCK_FAILED\0";
  case D3DERR_EXECUTE_UNLOCK_FAILED:
    return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
  case D3DERR_EXECUTE_FAILED:
    return "D3DERR_EXECUTE_FAILED\0";
  case D3DERR_EXECUTE_CLIPPED_FAILED:
    return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
  case D3DERR_TEXTURE_NO_SUPPORT:
    return "D3DERR_TEXTURE_NO_SUPPORT\0";
  case D3DERR_TEXTURE_NOT_LOCKED:
    return "D3DERR_TEXTURE_NOT_LOCKED\0";
  case D3DERR_TEXTURE_LOCKED:
    return "D3DERR_TEXTURELOCKED\0";
  case D3DERR_TEXTURE_CREATE_FAILED:
    return "D3DERR_TEXTURE_CREATE_FAILED\0";
  case D3DERR_TEXTURE_DESTROY_FAILED:
    return "D3DERR_TEXTURE_DESTROY_FAILED\0";
  case D3DERR_TEXTURE_LOCK_FAILED:
    return "D3DERR_TEXTURE_LOCK_FAILED\0";
  case D3DERR_TEXTURE_UNLOCK_FAILED:
    return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
  case D3DERR_TEXTURE_LOAD_FAILED:
    return "D3DERR_TEXTURE_LOAD_FAILED\0";
  case D3DERR_MATRIX_CREATE_FAILED:
    return "D3DERR_MATRIX_CREATE_FAILED\0";
  case D3DERR_MATRIX_DESTROY_FAILED:
    return "D3DERR_MATRIX_DESTROY_FAILED\0";
  case D3DERR_MATRIX_SETDATA_FAILED:
    return "D3DERR_MATRIX_SETDATA_FAILED\0";
  case D3DERR_SETVIEWPORTDATA_FAILED:
    return "D3DERR_SETVIEWPORTDATA_FAILED\0";
  case D3DERR_MATERIAL_CREATE_FAILED:
    return "D3DERR_MATERIAL_CREATE_FAILED\0";
  case D3DERR_MATERIAL_DESTROY_FAILED:
    return "D3DERR_MATERIAL_DESTROY_FAILED\0";
  case D3DERR_MATERIAL_SETDATA_FAILED:
    return "D3DERR_MATERIAL_SETDATA_FAILED\0";
  case D3DERR_LIGHT_SET_FAILED:
    return "D3DERR_LIGHT_SET_FAILED\0";
  default:
    return "Unrecognized error value.\0";
  }
}

// Returns 1 if the renderer supports bumpmapping
int d3d_SupportsBumpmapping() {
  if (d3d_CanBumpmap)
    return 1;

  return 0;
}

// returns directdraw object
void *d3d_DirectDrawObj(void **frontsurf, void **backsurf) {
  *backsurf = (void *)lpBackBuffer;
  *frontsurf = (void *)lpFrontBuffer;

  return lpDD1;
}

// Resets the texture cache
void d3d_ResetCache() {
  d3d_FreeTextureCache();
  d3d_TextureCacheInit();
}

// returns rendering statistics for the frame
void d3d_GetStatistics(tRendererStats *stats) {
  stats->poly_count = D3D_last_frame_polys_drawn;
  stats->vert_count = D3D_last_frame_verts_processed;
  stats->texture_uploads = D3D_last_uploads;
}
