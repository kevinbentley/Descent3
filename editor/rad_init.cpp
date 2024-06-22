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

#include "stdafx.h"
#include "editor.h"
#include "LightingStatus.h"
#include "radiosity.h"
#include "pserror.h"
#include "findintersection.h"
#include "hemicube.h"
#include "descent.h"
#include "rad_cast.h"
#include "ddio.h"
#include "vecmat.h"
#include <stdlib.h>
#include "mem.h"

// Some radiosity globals
int Shoot_method = SM_HEMICUBE;
int Hemicube_resolution = 1024;

int Ignore_terrain = 0;
int Ignore_satellites = 0;

float rad_TotalFlux = 0.0f;
float rad_Convergence = 1.0f;

int rad_NumSurfaces;
int rad_NumElements;

float *rad_FormFactors;

int rad_StepCount = 0;
int rad_MaxStep = 1;
int rad_DoneCalculating = 0;

float rad_TotalUnsent = 0.0f;

rad_surface *rad_MaxSurface = NULL;
rad_surface *rad_Surfaces;

int UseVolumeLights = 0; // User selectable to do volumelights
int Calculate_specular_lighting = 0;

// Specular variable
float *Room_strongest_value[MAX_ROOMS][4];

// Tells radiosity renderer to do volume lighting
int Do_volume_lighting = 0;

volume_element *Volume_elements[MAX_VOLUME_ELEMENTS];

// Shoot_from_patch tells us whether or not we're shooting from the center of
// a surface or if we must shoot from the center of each of its individual elements
// Shoot_from_patch=1 is much faster
int Shoot_from_patch = 1;

int DoRadiosityRun(int method, rad_surface *light_surfaces, int count) {
  float start_time;

  mprintf(0, "Calculating radiosity on %d faces.\n", count);

  rad_Surfaces = light_surfaces;
  rad_NumSurfaces = count;

  Shoot_method = method;

  start_time = timer_GetTime();

  InitRadiosityRun();

  // Setup our window
  CLightingStatus dlg;

  dlg.Create(IDD_LIGHTINGSTATUS);

  CalculateRadiosity();

  dlg.DestroyWindow();
  CloseRadiosityRun();

  // Print time taken
  mprintf(0, "\nLighting took %.4f seconds.\n", timer_GetTime() - start_time);

  return 1;
}

// Sets up our radiosity run
void InitRadiosityRun() {
  rad_TotalFlux = 0.0f;
  rad_StepCount = 0;
  rad_DoneCalculating = 0;

  // Clear key buffer
  //	ddio_KeyFrame();
  ddio_KeyFlush();

  CountElements();
  CalculateArea();
  InitExitance();

  if (Shoot_method == SM_HEMICUBE) {
    SetupFormFactors();
    InitHemicube(Hemicube_resolution);
  }
}

// Initalizes memory for form factors
void SetupFormFactors() {
  ASSERT(rad_NumElements > 0);

  rad_FormFactors = (float *)mem_malloc(rad_NumElements * sizeof(float));
  ASSERT(rad_FormFactors != NULL);
}

void CalculateAreaForSurface(rad_surface *sp) {
  int i;

  vector normal;

  vm_GetPerp(&normal, &sp->verts[0], &sp->verts[1], &sp->verts[2]);
  sp->area = (vm_GetMagnitude(&normal) / 2);

  for (i = 2; i < sp->num_verts - 1; i++) {
    vm_GetPerp(&normal, &sp->verts[0], &sp->verts[i], &sp->verts[i + 1]);
    sp->area += (vm_GetMagnitude(&normal) / 2);
  }

  sp->surface_area = sp->area;
  sp->element_area = sp->area / (sp->xresolution * sp->yresolution);
}

void CalculateAreaForElement(rad_element *ep) {
  int i;

  vector normal;

  if (ep->flags & EF_IGNORE) {
    ep->area = .0000001f;
    return;
  }

  vm_GetPerp(&normal, &ep->verts[0], &ep->verts[1], &ep->verts[2]);
  ep->area = (vm_GetMagnitude(&normal) / 2);

  for (i = 2; i < ep->num_verts - 1; i++) {
    vm_GetPerp(&normal, &ep->verts[0], &ep->verts[i], &ep->verts[i + 1]);
    ep->area += (vm_GetMagnitude(&normal) / 2);
  }

  if (ep->area < .05)
    ep->flags |= EF_SMALL;
  if (ep->area == 0) {
    ep->flags |= EF_IGNORE;
    ep->area = .00000001f;
  }
}

// Calculates the area of the surfaces and elements in our environment
void CalculateArea() {
  rad_surface *surf;
  int i, t;

  for (i = 0; i < rad_NumSurfaces; i++) {
    surf = &rad_Surfaces[i];

    CalculateAreaForSurface(surf);

    for (t = 0; t < surf->xresolution * surf->yresolution; t++) {
      rad_element *ep = &surf->elements[t];
      CalculateAreaForElement(ep);
    }
  }
}

// Counts the total number of elements we have to work with
void CountElements() {
  rad_surface *surf;
  int i;

  rad_NumElements = 0;

  for (i = 0; i < rad_NumSurfaces; i++) {
    surf = &rad_Surfaces[i];

    rad_NumElements += (surf->xresolution * surf->yresolution);
  }
  mprintf(0, "Number of elements=%d\n", rad_NumElements);
}

// Initializes the exitances for all surfaces
void InitExitance() {
  int i;

  for (i = 0; i < rad_NumSurfaces; i++) {
    SetExitanceForSurface(&rad_Surfaces[i]);
  }
}

// Gets the spectral emittance for a surface
void GetEmittance(rad_surface *surf, spectra *dest) { *dest = surf->emittance; }

// Sets all the elements of a surface to their initial unshot exitance values
void SetExitanceForSurface(rad_surface *surf) {
  int i;

  surf->exitance = surf->emittance;

  for (i = 0; i < surf->xresolution * surf->yresolution; i++) {
    if (Shoot_from_patch) {
      surf->elements[i].exitance.r = 0;
      surf->elements[i].exitance.g = 0;
      surf->elements[i].exitance.b = 0;
    } else
      surf->elements[i].exitance = surf->emittance;
  }

  rad_TotalFlux += GetUnsentFlux(surf);
}

// Find the surface we want to shoot from
void UpdateUnsentValues() {
  float cur_unsent;
  float max_unsent = 0.0f;
  float sat_max_unsent = 0.0f;
  int use_sat = 0;
  int i;
  rad_surface *sat_surface;

  static int last_report_time = -10;

  rad_TotalUnsent = 0.0f;
  rad_MaxSurface = NULL;

  // Go through all the surfaces searching for the surface with the greatest
  // exitance yet to be shot

  for (i = 0; i < rad_NumSurfaces; i++) {
    rad_surface *surf = &rad_Surfaces[i];
    cur_unsent = GetUnsentFlux(surf);
    rad_TotalUnsent += cur_unsent;

    if (cur_unsent > max_unsent) {
      max_unsent = cur_unsent;
      rad_MaxSurface = surf;
    }

    // Always give satellites priority
    if (surf->surface_type == ST_SATELLITE && cur_unsent > 0) {
      if (cur_unsent > sat_max_unsent) {
        use_sat = 1;
        sat_max_unsent = cur_unsent;
        sat_surface = surf;
      }
    }
  }

  // Update convergence
  if (rad_TotalFlux > .0001)
    rad_Convergence = fabs(rad_TotalUnsent) / rad_TotalFlux;
  else
    rad_Convergence = 0.0;

  mprintf_at(2, 3, 0, "Left=%f  ", rad_Convergence);

  if (timer_GetTime() - last_report_time > 10.0) {
    mprintf(0, "Percentage left=%f\n", rad_Convergence);
    last_report_time = timer_GetTime();
  }

  if (use_sat)
    rad_MaxSurface = sat_surface;

  if (!use_sat && Shoot_method == SM_SWITCH_AFTER_SATELLITES) {
    SetupFormFactors();
    InitHemicube(Hemicube_resolution);
    Shoot_method = SM_HEMICUBE;
  }

  // No energy left to shoot?
  if (rad_MaxSurface == NULL || rad_TotalUnsent == 0)
    rad_DoneCalculating = 1;
}

// Finds the world coordinate center of a surface
void GetCenterOfSurface(rad_surface *sp, vector *dest) { vm_GetCentroid(dest, sp->verts, sp->num_verts); }

// Finds the world coordinate center of a surface
void GetCenterOfElement(rad_element *ep, vector *dest) { vm_GetCentroid(dest, ep->verts, ep->num_verts); }

void CalculateRadiosity() {
  int key;

  while (!rad_DoneCalculating) {
    if (rad_StepCount >= rad_MaxStep) {
      rad_DoneCalculating = 1;
      break;
    }
    mprintf_at(2, 2, 0, "Lightcount=%d   ", rad_StepCount);

    DoRadiosityIteration();

    rad_StepCount++;

    App()->defer();
    //		ddio_KeyFrame();
    while ((key = ddio_KeyInKey()) != 0) {
      if (key == KEY_LAPOSTRO) {
        rad_DoneCalculating = 1;
        break;
      }
    }
  }

  // Clear key buffer
  ddio_KeyFlush();
}

// returns the amount of unsent flux from a surface
float GetUnsentFlux(rad_surface *surface) {
  float flux;

  flux = surface->exitance.r + surface->exitance.g + surface->exitance.b;

  if (surface->surface_type != ST_SATELLITE)
    flux *= surface->area;

  return flux;
}

float GetMaxColor(spectra *sp) {
  float m;

  m = std::max<float>(sp->r, sp->g);
  m = std::max<float>(sp->b, m);

  return m;
}

int FixEdges = 0;
extern void AddSpectra(spectra *dest, spectra *a, spectra *b);

void NormalizeExitance() {
  int i, t;
  float rmax = 0.0f;

  for (i = 0; i < rad_NumSurfaces; i++) {
    rad_surface *surf = &rad_Surfaces[i];
    spectra *emit = &surf->emittance;

    for (t = 0; t < surf->xresolution * surf->yresolution; t++) {
      rad_element *ep = &surf->elements[t];

      if (ep->flags & EF_IGNORE)
        continue;

      if (Shoot_from_patch) {
        ep->exitance.r += emit->r;
        ep->exitance.g += emit->g;
        ep->exitance.b += emit->b;
      }

      /*			if (ep->exitance.r>1)
                                      ep->exitance.r=1;
                              if (ep->exitance.g>1)
                                      ep->exitance.g=1;
                              if (ep->exitance.b>1)
                                      ep->exitance.b=1;*/

      rmax = GetMaxColor(&ep->exitance);

      if (rmax > 1.0 && rmax > 0.0) {
        ep->exitance.r /= rmax;
        ep->exitance.g /= rmax;
        ep->exitance.b /= rmax;
      }
    }
  }
}

// Shuts down the radiosity stuff, freeing memory, etc
void CloseRadiosityRun() {

  NormalizeExitance();
  if (Shoot_method == SM_HEMICUBE) {
    mem_free(rad_FormFactors);
    CloseHemicube();
  }
}
void Calculate() {

  if (Shoot_method == SM_HEMICUBE)
    CalculateFormFactorsHemiCube();
  else
    CalculateFormFactorsRaycast();

  // Set unshot exitance for MaxSurface to zero
  rad_MaxSurface->exitance.r = 0;
  rad_MaxSurface->exitance.g = 0;
  rad_MaxSurface->exitance.b = 0;
  rad_MaxSurface->flags &= ~SF_LIGHTSOURCE;
}

// Does one iteration of ray-casting radiosity
int DoRadiosityIteration() {
  UpdateUnsentValues();

  if (!rad_DoneCalculating)
    Calculate();

  return 1;
}
