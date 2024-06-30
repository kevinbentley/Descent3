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

 * $Logfile: /DescentIII/Main/lib/polymodel.h $
 * $Revision: 83 $
 * $Date: 7/08/99 5:47p $
 * $Author: Jason $
 *
 * Header for polygon model loading funcs
 *
 * $Log: /DescentIII/Main/lib/polymodel.h $
 *
 * 83    7/08/99 5:47p Jason
 * changes for new bumpmapping system in 1.1 update patch
 *
 * 82    6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 81    4/09/99 12:06p Jason
 * made model setup code faster
 *
 * 80    1/21/99 11:16p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 79    1/20/99 5:36p Jason
 * added custom glows for teams
 *
 * 78    1/13/99 12:43p Jason
 * added some more detail settings
 *
 * 77    1/07/99 5:01p Keneta
 * added more polymodel slots
 *
 * 76    11/30/98 3:59p Jason
 * changed dynamic lighting to be better
 *
 * 75    10/12/98 9:30a Jason
 * new polymodel memory scheme
 *
 * 74    10/07/98 5:07p Jason
 * added new polymodel effect type
 *
 * 73    10/07/98 3:40p Chris
 * Added $thruster
 *
 * 72    9/09/98 7:09p Jason
 * changed afterburner effect for ships
 *
 * 71    8/31/98 1:35p Keneta
 * Made some use count unsigned shorts
 *
 * 70    8/24/98 1:01p Jason
 * made object specular faces selectable by texture
 *
 * 69    8/21/98 5:14p Jason
 * made better memory use of primitives
 *
 * 68    8/18/98 11:38a Jason
 * fixed polymodel fog lighting
 *
 * 67    8/18/98 11:26a Matt
 * Changed outline code to only outline polymodel objects when they're
 * being rendered in the mine, and not when they're being drawn in the
 * editor, main menu, cockpit, etc.
 *
 * 66    8/14/98 4:00p Jason
 * added specular objects outside
 *
 * 65    8/13/98 6:56p Jason
 * made objects foggable correctly
 *
 * 64    8/12/98 12:04p Chris
 * Attach system version .5 (still needs more work to be multiplayer
 * friendly)
 *
 * 63    8/04/98 2:32p Chris
 * Improved attach code added more fixes to the AABB partial computation
 * patch
 *
 * 62    7/29/98 5:05p Chris
 * Made more of the wb info dynamically allocated.  Added Attach points to
 * the polymodel structure
 *
 * 61    7/27/98 10:39a Jason
 * added customizable skins
 *
 * 60    6/22/98 7:31p Samir
 * added mask for monitors.
 *
 * 59    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 58    5/13/98 12:06p Jason
 * trimmed some memory usage
 *
 * 57    4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 56    4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 55    4/17/98 12:45p Jason
 * various changes for multiplayer
 *
 * 54    4/15/98 3:28p Jason
 * changed glow stuff to work with new system
 *
 * 53    4/07/98 6:22p Samir
 * restored a couple of variables to the poly_model array that were used
 * elsewhere in the code.  left out the nasty one though.
 *
 * 52    4/07/98 5:59p Jason
 * saved about 15 megs of storage by deleting an unused array
 *
 * 51    4/06/98 3:03p Jason
 * added polygon rendering overlays
 *
 * 50    4/03/98 1:13p Jason
 * shaved off a few more bytes from the polyface structure
 *
 * 49    4/03/98 10:07a Chris
 * Added support for objects getting their size computed when the
 * polymodel is paged in the first time as an object
 *
 * 48    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 47    4/02/98 12:22p Jason
 * changes for deformation effect
 *
 * 46    4/01/98 6:23p Jason
 * added a slew of stuff for multiplayer
 *
 * 45    3/31/98 11:12a Brent
 * upped number of textures for the undisciplined bastard know as BRENT
 *
 * 44    3/29/98 11:58p Jason
 * saved some memory with object lightmaps
 *
 * 43    3/26/98 2:14p Jason
 * added dynamic lighting for objects
 *
 * 42    3/24/98 5:16p Jason
 * upped polyvecs for that fucker brent
 *
 * 41    3/23/98 10:03a Chris
 * Added independant wb animations
 *
 * 40    3/19/98 4:30p Samir
 * added ability to mark subobjects as layered.
 *
 * 39    3/18/98 6:24p Samir
 * Fixed some bugs with normalizing MONITORs and added VIEWER flag.
 *
 * 38    3/16/98 3:47p Jason
 * got rid of circular dependencies for objects and polymodels
 *
 * 37    3/16/98 3:24p Chris
 * Removed my the object.h dependancy
 *
 * 36    3/16/98 11:34a Chris
 * Polymodels have 3 levels of AABB (object, subobject, and face level)
 *
 * 35    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 34    3/11/98 4:59p Chris
 * Added a few new sphere types (wall and anim)
 *
 * 33    3/10/98 6:54p Chris
 * All start and end frame for ComputeDefaultSize
 *
 * 32    2/17/98 12:19p Jason
 * upped max polymodel count to 500
 *
 * 31    2/16/98 2:49p Chris
 * Made the MAX_SUBOBJECTS determine the number of normalized_time values
 * to be processed.  No longer a 'literal' problem.
 *
 * 30    2/16/98 2:12p Jason
 * fixed bug with lightmaps and door shells
 *
 * 29    2/13/98 12:44p Jason
 * upped max number of subobjects
 *
 * 28    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 27    1/13/98 3:09p Jason
 * added glow effect for engines
 *
 * 26    12/31/97 3:34p Jason
 * added alpha per vertex for polymodels
 *
 * 25    11/17/97 6:28p Mark
 * FROM Jason:fixed memory leak
 *
 * 24    11/06/97 4:18p Samir
 * texture numbers are now shorts in polymodel
 *
 * 23    11/04/97 4:58p Samir
 * Added 4 more monitors.
 *
 * 22    10/28/97 6:37p Samir
 * Submodels now can be monitors.
 *
 * 21    10/23/97 2:07p Jason
 * fixed some problems with debris not spinning about their center point
 *
 * 20    10/01/97 7:00p Jason
 * did more work on object lightmaps
 *
 * 19    9/30/97 6:40p Jason
 * got lightmap stuff sort of working with objects
 *
 * 18    9/26/97 12:09p Jason
 * made positional/rotational animations have differing
 * track_min/track_max
 *
 * 17    9/25/97 4:54p Jason
 * added timer info to polymodels
 *
 * 16    9/17/97 10:59a Chris
 * Added a new way to compute radi
 *
 * 15    9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 14    9/10/97 5:36p Jason
 * changed version number for new oofs
 *
 * 13    9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 12    9/09/97 6:15p Jason
 * made dynamic lighting on objects more memory efficient
 *
 * 11    9/04/97 3:49p Chris
 * Added additional turret information from pofgen, added ground plane
 * stuff
 *
 * 10    9/03/97 4:11p Chris
 * Moved some code so that pofview will compile
 *
 * 9     9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 8     8/25/97 6:19p Chris
 * Added support for knowing which subobject a gun point is linked to
 *
 * 7     8/20/97 3:16p Chris
 * Added some hooks for turrets
 *
 * 6     8/03/97 2:25p Jason
 * made polymodels use less memory
 *
 * 5     7/28/97 1:16p Chris
 *
 * 4     7/23/97 11:48a Jason
 * added support for newstyle pof format
 *
 * 3     7/22/97 1:34a Jason
 * added code to support newstyle polymodels
 *
 * 18    6/24/97 6:13p Matt
 * Got rid of DrawPolygonObject(), since it required the inclusion of
 * object.h, which is a main directory header file (& thus shouldn't be
 * accessible by a library).
 *
 * $NoKeywords: $
 */

#ifndef POLYMODEL_H
#define POLYMODEL_H

#include <array>

#include "manage.h"
#include "pstypes.h"
#include "vecmat.h"
#include "3d.h"
#include "robotfirestruct.h"
#include "polymodel_external.h"
#include "object_external_struct.h"

#define PM_COMPATIBLE_VERSION 1807
#define PM_OBJFILE_VERSION 2300

#define WB_INDEX_SHIFT 16      // bits to shift over to get the weapon battery index (after masking out flags)
#define SOF_WB_MASKS 0x01F0000 // Room for 32 weapon batteries (currently we only use 21 slots)

#define SOF_MONITOR_MASK 0x0ff0 // mask for monitors

extern int Num_poly_models;
extern std::array<poly_model, MAX_POLY_MODELS> Poly_models;

extern int Polymodel_use_effect;
extern polymodel_effect Polymodel_effect;
extern polymodel_light_type Polymodel_light_type;
extern float Polylighting_static_red;
extern float Polylighting_static_green;
extern float Polylighting_static_blue;
extern uint8_t *Polylighting_gouraud;
extern vector *Polymodel_light_direction, Polymodel_fog_portal_vert, Polymodel_fog_plane, Polymodel_specular_pos,
    Polymodel_bump_pos;
extern lightmap_object *Polylighting_lightmap_object;

extern vector Model_eye_position;
extern vector Interp_pos_instance_vec;
extern std::array<g3Point, MAX_POLYGON_VECS> Robot_points;

// Flag to draw an outline around the faces
extern bool Polymodel_outline_mode;

static inline float POLY_WIDTH(int model_num) { return Poly_models[model_num].maxs.x - Poly_models[model_num].mins.x; }

static inline float POLY_HEIGHT(int model_num) { return Poly_models[model_num].maxs.y - Poly_models[model_num].mins.y; }

static inline float POLY_DEPTH(int model_num) { return Poly_models[model_num].maxs.z - Poly_models[model_num].mins.z; }

// given a filename, reads in a POF and returns an index into the Poly_models array
// returns -1 if something is wrong
int LoadPolyModel(const char *filename, int pageable);

// gets the filename from a path, plus appends our .pof extension
void ChangePolyModelName(const char *src, char *dest);

// Searches thru all polymodels for a specific name, returns -1 if not found
// or index of polymodel with name
int FindPolyModelName(const char *name);

// Draws a polygon model to the viewport
// Normalized_time is an array of floats from 0 to 1 that represent how far into
// an animation state we are

// This one is for static lighting - ie 1 light value for the entire model
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags, float r, float g,
                      float b, uint32_t f_render_sub = 0xFFFFFFFF, uint8_t use_effect = 0, uint8_t overlay = 0);

// This one is for gouraud shading - the lightdir is the normalized light direction, and lightscalar is a 0-1 scalar to
// apply
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags, vector *lightdir,
                      float r, float g, float b, uint32_t f_render_sub = 0xFFFFFFFF, uint8_t use_effect = 0,
                      uint8_t overlay = 0);

// This one is for lightmap rendering
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags,
                      lightmap_object *lm_object, uint32_t f_render_sub, uint8_t use_effect = 0, uint8_t overlay = 0);

// gives the interpreter an array of points to use
void g3_SetInterpPoints(g3Point *pointlist);

// calls the object interpreter to render an object.  The object renderer
// is really a seperate pipeline. returns true if drew
int InterpPolygonModel(poly_model *pm);

// Inits our models array
int InitModels();

// Frees polymodel located in index of Poly_models array
void FreePolyModel(int index);

// Given an actual keyframe number, returns the normalized (0 to 1) position of that
// keyframe.  Handle is an index into the Poly_models array
float GetNormalizedKeyframe(int handle, float num);

// Goes through all poly models and gets all missing textures
void RemapPolyModels();

// For macintosh, we must swap the interpreted model code
void SwapPolymodelData(uint8_t *data);

// Sets a positional instance
void StartPolyModelPosInstance(vector *posvec);

// Pops a positional instance
void DonePolyModelPosInstance();

void SetModelAngles(poly_model *po, float *normalized_angles);
void SetModelInterpPos(poly_model *po, float *normalized_pos);

void SetNormalizedTimeObj(object *obj, float *normalized_time);
void SetNormalizedTimeAnim(float norm_anim_frame, float *normalized_time, poly_model *pm);

void WBClearInfo(poly_model *pm);

// Computes the size of a polymodel.
float ComputeDefaultSize(int type, int handle, float *size_ptr);

// Returns the total number of faces in a model
int CountFacesInPolymodel(poly_model *pm);

// Rendering functions
int RenderPolygonModel(poly_model *, uint32_t f_render_sub = 0xFFFFFFFF);
void RenderSubmodel(poly_model *pm, bsp_info *sm, uint32_t f_render_sub);

//	returns point within polymodel/submodel in world coordinates.
void GetPolyModelPointInWorld(vector *dest, poly_model *pm, vector *wpos, matrix *orient, int subnum, vector *pos,
                              vector *norm = NULL);
void GetPolyModelPointInWorld(vector *dest, poly_model *pm, vector *wpos, matrix *orient, int subnum,
                              float *normalized_time, vector *pos, vector *norm = NULL);

// Returns 1 if this submodel shouldn't be rendered
int IsNonRenderableSubmodel(poly_model *pm, int submodelnum);

// Sets the effect used by a polymodel
void SetPolymodelEffect(polymodel_effect *);

// Pages in a polymodel if its not already in memory
void PageInPolymodel(int polynum, int type = -1, float *size_ptr = NULL);

// Gets a pointer to a polymodel.  Pages it in if neccessary
poly_model *GetPolymodelPointer(int polynum);

// Frees all the polymodel data, but doesn't free the actual polymodel itself
void FreePolymodelData(int i);

// Sets the position and rotation of a polymodel.  Used for rendering and collision detection
void SetModelAnglesAndPos(poly_model *po, float *normalized_time, uint32_t subobj_flags = 0xFFFFFFFF);

extern void DoneLightInstance();
extern void StartLightInstance(vector *, matrix *);

#endif
