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

 * $Logfile: /DescentIII/Main/model/polymodel.cpp $
 * $Revision: 152 $
 * $Date: 10/08/01 4:20p $
 * $Author: Matt $
 *
 * Jason should put something here
 *
 * $Log: /DescentIII/Main/model/polymodel.cpp $
 *
 * 152   10/08/01 4:20p Matt
 * Added system to check for errors when reading in add-on data.
 *
 * 151   10/01/01 1:58p Matt
 * In release build, Increment the used count when loading a model that's
 * already in memory.  This was already done in non-release builds.
 *
 * 150   5/10/00 2:43p Jeff
 * fixed bug when paging in data if the tablefile specifies a full path to
 * a primative instead of just a filename (bug in 3rd party tablefile
 * editors)
 *
 * 149   4/19/00 5:34p Matt
 * From Duane for 1.4
 * Check for glow_info memory already allocated before mallocing
 *
 * 148   10/21/99 2:40p Kevin
 * Mac merge
 *
 * 147   10/16/99 6:40p Jeff
 * swaped way of determining textures for objects on load
 *
 * 146   10/14/99 3:02p Jeff
 * correctly look up texture names
 *
 * 145   7/08/99 5:48p Jason
 * changes for new bumpmapping system in 1.1 update patch
 *
 * 144   6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 143   5/18/99 10:31a Jason
 * polymodel stuff wasn't getting paged in before drawing
 *
 * 142   5/14/99 2:04p Jason
 * added polymodel errors to catch bugs
 *
 * 141   4/28/99 1:55a Samir
 * error instead of assert when we can't open a model for paging in a
 * polymodel.
 *
 * 140   4/19/99 3:50p Jeff
 * fixed mem_free/copy-paste bug, wasn't setting the correct pointer to
 * NULL after free
 *
 * 139   4/19/99 4:00a Jeff
 * fixed min/max for Linux
 *
 * 138   4/09/99 12:51p Jason
 * fixed bug with new lookup code
 *
 * 137   4/09/99 12:06p Jason
 * made model setup code faster
 *
 * 136   4/08/99 11:45a Jason
 * greatly sped up the time it takes to get model anges/positions by
 * precalculation
 *
 * 135   3/05/99 11:24a Jason
 * fixed pesky no-lightmap drawing problem that has plagued me for the
 * last 10 months
 *
 * 134   2/16/99 12:42p Kevin
 * Improvements to the paging data progress indicator
 *
 * 133   2/10/99 4:58p Jeff
 * put assert if pageinpolymodel file open fails
 *
 * 132   2/09/99 7:01p Kevin
 * First work for new and improved progress screen while loading a level.
 * Note that this is a hack at this point, while I get the details worked
 * out, then I'll make it cleaner.
 *
 * 131   1/15/99 3:04p Jason
 * fixed polymodel data freeing problem
 *
 * 130   1/13/99 12:43p Jason
 * added some more detail settings
 *
 * 129   10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 128   10/13/98 5:25p Jason
 * fixed zero faced submodel problem
 *
 * 127   10/12/98 10:59a Jason
 * fixed zero length malloc
 *
 * 126   10/12/98 9:35a Jason
 * New polymodel memory scheme
 *
 * 125   10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 124   10/08/98 2:27p Jason
 * sped up table file loading
 *
 * 123   10/07/98 5:29p Chris
 * Added SOF_THRUSTER support
 *
 * 122   10/07/98 3:40p Chris
 * Added $thruster
 *
 * 121   9/11/98 4:04p Jason
 * added better multitexture support
 *
 * 120   8/27/98 11:16a Jason
 * fixed math bug in GetPolymodelPointInWorld
 *
 * 119   8/25/98 12:22p Jason
 * more changes for cockpits
 *
 * 118   8/24/98 6:43p Keneta
 * Long proofed the turrets and weapon batteries
 *
 * 117   8/24/98 2:44p Jason
 * checked in so Samir can test
 *
 * 116   8/21/98 5:14p Jason
 * made better memory use of primitives
 *
 * 115   8/18/98 11:38a Jason
 * fixed polymodel fog lighting
 *
 * 114   8/18/98 11:26a Matt
 * Changed outline code to only outline polymodel objects when they're
 * being rendered in the mine, and not when they're being drawn in the
 * editor, main menu, cockpit, etc.
 *
 * 113   8/17/98 12:10p Chris
 * Fixed MAJOR bug in getting gunpoint positions
 *
 * 112   8/16/98 9:52p Chris
 * Added some error checking for the attach system
 *
 * 111   8/14/98 4:00p Jason
 * added specular objects outside
 *
 * 110   8/13/98 6:56p Jason
 * made objects foggable correctly
 *
 * 109   8/12/98 12:04p Chris
 * Attach system version .5 (still needs more work to be multiplayer
 * friendly)
 *
 * 108   8/07/98 2:49p Keneta
 * fixed number of subobjects assertion
 *
 * 107   8/04/98 2:32p Chris
 * Improved attach code added more fixes to the AABB partial computation
 * patch
 *
 * 106   7/31/98 11:52a Chris
 * Weapons can be persistent.  Added ability for objects to be manually
 * set for no object collisions.
 *
 * 105   7/30/98 1:13p Chris
 * Improved attach point code
 *
 * 104   7/29/98 5:05p Chris
 * Made more of the wb info dynamically allocated.  Added Attach points to
 * the polymodel structure
 *
 * 103   7/27/98 10:39a Jason
 * added customizable skins
 *
 * 102   7/02/98 2:49p Chris
 *
 * 101   7/02/98 2:47p Chris
 * Dynamic weapon info is now dynamically allocated
 * Dynamic weapon info is now dynamically allocated
 *
 * 100   6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 99    5/27/98 5:17p Jason
 * fixed some bugs for the E3 Demo
 *
 * 98    5/15/98 3:24p Keneta
 *
 * 97    4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 96    4/24/98 1:35p Jason
 * Don't sort non-alphaed polymodels
 *
 * 95    4/22/98 12:10p Chris
 * Fixed path length problems
 *
 * 94    4/17/98 12:45p Jason
 * various changes for multiplayer
 *
 * 93    4/15/98 3:28p Jason
 * changed glow stuff to work with new system
 *
 * 92    4/07/98 3:35p Jason
 * possible fix for polymodel paging bug
 *
 * 91    4/06/98 3:03p Jason
 * added polygon rendering overlays
 *
 * 90    4/03/98 12:23p Jason
 * dealt with overlay types being loaded from disk more than once
 *
 * 89    4/03/98 11:55a Jason
 * fixed polymodel paging problem
 *
 * 88    4/03/98 10:07a Chris
 * Added support for objects getting their size computed when the
 * polymodel is paged in the first time as an object
 *
 * 87    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 86    4/01/98 6:23p Jason
 * added a slew of stuff for multiplayer
 *
 * 85    3/31/98 3:49p Jason
 * added memory lib
 *
 * 84    3/31/98 11:12a Brent
 * added assert for max textures
 *
 * 83    3/30/98 12:27a Jason
 * fixed memory leaks as reported by BoundsChecker
 *
 * 82    3/25/98 5:51p Chris
 * Added full model/body animations for weapon firing
 *
 * 81    3/24/98 2:12p Brent
 * fixed another glowcount bug
 *
 * 80    3/24/98 12:47p Brent
 * fixed glow bug
 *
 * 79    3/24/98 12:38p Brent
 * added assert
 *
 * 78    3/23/98 10:03a Chris
 * Added independant wb animations
 *
 * 77    3/19/98 4:30p Samir
 * added ability to mark subobjects as layered.
 *
 * 76    3/18/98 6:24p Samir
 * Fixed some bugs with normalizing MONITORs and added VIEWER flag.
 *
 * 75    3/16/98 11:34a Chris
 * Polymodels have 3 levels of AABB (object, subobject, and face level)
 *
 * 74    3/10/98 2:03p Chris
 * Added support for 0.0 angle fov
 *
 * 73    2/16/98 4:05p Jason
 * render polymodels sorted or unsorted depending on whether or not they
 * have alpha faces
 *
 * 72    2/16/98 2:49p Chris
 * Made the MAX_SUBOBJECTS determine the number of normalized_time values
 * to be processed.  No longer a 'literal' problem.
 *
 * 71    2/16/98 2:25p Jason
 * fixed bad indexing into subobjects problem
 *
 * 70    2/16/98 2:12p Jason
 * fixed bug with lightmaps and door shells
 *
 * 69    2/13/98 6:59p Chris
 * FIxed the normalized_time array from being smaller than the number of
 * subobjects.  Also update newstyle_fi.cpp
 *
 * 68    2/13/98 12:44p Jason
 * upped max number of subobjects
 *
 * 67    2/10/98 3:50p Jason
 * added pulsing walls
 *
 * 66    2/06/98 8:08p Jason
 * fixed size problem with facing subobjects
 *
 * 65    2/06/98 6:44p Jason
 * made polymodels replace themselves if they find the same name
 *
 * 64    2/06/98 4:33p Jason
 * fixed facing model sizes
 *
 * 63    2/06/98 1:45p Jason
 * No really, I fixed the min max problem.
 *
 * 62    2/06/98 12:53p Jason
 * fixed object min max stuff
 *
 * 61    2/04/98 9:28p Jason
 * added the ability to have models that always face you
 *
 * 60    1/26/98 4:32p Jason
 * took out some goofy mprintfs
 *
 * 59    1/23/98 5:39p Matt
 * Removed some door frontface error checking now more thoroughly handled
 * in WorldObjectsDoorDialog.cpp
 *
 * 58    1/23/98 11:16a Luke
 * Remove a really old Assert that limitted which types could animate
 *
 * 57    1/13/98 3:46p Jason
 * fixed memory corruption bug introduced by my last rev
 *
 * 56    1/13/98 3:09p Jason
 * added glow effect for engines
 *
 * 55    1/02/98 1:03p Jason
 * fixed memory deallocation leak in FreePolymodel
 *
 * 54    12/31/97 3:34p Jason
 * added alpha per vertex for polymodels
 *
 * 53    12/08/97 6:18p Jason
 * more tweaks for destroyable buildings
 *
 * 52    11/17/97 6:28p Mark
 * FROM Jason:fixed memory leak
 *
 * 51    11/17/97 12:02p Jason
 * added extra newstyle variable set
 *
 * 50    11/10/97 3:33p Jason
 * ignore whitespace
 *
 * 49    11/04/97 4:58p Samir
 * Added 4 more monitors.
 *
 * 48    10/30/97 10:53a Jason
 * set color model to be MONO when drawing gouraud shaded polymodels
 *
 * 47    10/28/97 6:37p Samir
 * Submodels now can be monitors.
 *
 * 46    10/28/97 11:10a Jason
 * tweaked subojbect rotation
 *
 * 45    10/24/97 11:57a Jason
 * fixed memory leak
 *
 * 44    10/23/97 2:07p Jason
 * fixed some problems with debris not spinning about their center point
 *
 * 43    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 42    10/06/97 6:39p Jason
 * fixed frame min/max problem
 *
 * 41    10/05/97 5:30a Chris
 * Added more support for TIMED animations
 *
 * 40    10/01/97 7:00p Jason
 * did more work on object lightmaps
 *
 * 39    9/30/97 6:40p Jason
 * got lightmap stuff sort of working with objects
 *
 * 38    9/29/97 3:48p Jason
 * added more code to support new timed models
 *
 * 37    9/26/97 12:09p Jason
 * made positional/rotational animations have differing
 * track_min/track_max
 *
 * 36    9/25/97 4:54p Jason
 * added timer info to polymodels
 *
 * 35    9/18/97 1:27p Matt
 * Cleaned up object struct
 *
 * 34    9/17/97 10:59a Chris
 * Added a new way to compute radi
 *
 * 33    9/15/97 11:11a Jason
 * fixed mins/maxs to be based on the center of the model
 *
 * 32    9/12/97 5:38p Jason
 * got doors working
 *
 * 31    9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 30    9/10/97 6:01p Jason
 * fixed double used variable bug
 *
 * 29    9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 28    9/09/97 6:55p Jason
 * better error checking for model usage counts
 *
 * 27    9/09/97 6:15p Jason
 * made dynamic lighting on objects more memory efficient
 *
 * 26    9/09/97 11:05a Jason
 * fixed wacky bizarre problem with instancing and positional
 * interpolation
 *
 * 25    9/05/97 1:29p Jason
 * revamped generic object lighting
 *
 * 24    9/04/97 5:38p Jason
 * fixed dumb bug that was fixed a long time ago...model positional
 * interpolation
 *
 * 23    9/04/97 3:49p Chris
 * Added additional turret information from pofgen, added ground plane
 * stuff
 *
 * 22    9/03/97 4:41p Chris
 * Moved some code so that pofview will compile
 *
 * 21    9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 20    8/25/97 6:19p Chris
 * Added support for knowing which subobject a gun point is linked to
 *
 * 19    8/24/97 1:40p Jason
 * don't compute normals on model load...let pofgen do it
 *
 * 18    8/22/97 12:13p Jason
 * made rotators work on keyframe 1 instead of keyframe 0 since max
 * insists on some weird "start axis" for keyframe 0
 *
 * 17    8/20/97 4:24p Matt
 * Removed unused code
 *
 * 16    8/20/97 3:16p Chris
 * Added some hooks for turrets
 *
 * 15    8/08/97 4:38p Jason
 * added sliding textures for models
 *
 * 14    8/08/97 2:30p Jason
 * added error checking for rotators without keyframes
 *
 * 13    8/08/97 10:58a Jason
 * fixed out of bounds error
 *
 * 12    8/07/97 3:19p Jason
 * only remap models when explicitely told to
 *
 * 11    8/06/97 3:07p Jason
 * fixed problem where polymodels were being freed twice
 *
 * 10    8/06/97 12:40p Jason
 * fixed some potentially serious memory problems
 *
 * 9     8/05/97 5:18p Jason
 * fixed circular dependencies with child/parents
 *
 * 8     8/03/97 2:25p Jason
 * made polymodels use less memory
 *
 * 7     7/28/97 1:14p Chris
 * Added support for sub-object visability.  Plus, debris.
 *
 * 6     7/23/97 11:48a Jason
 * added support for newstyle pof format
 *
 * 5     7/22/97 1:34a Jason
 * added code to support newstyle polymodels
 *
 * 4     7/15/97 4:27p Mark
 *
 * 36    6/24/97 6:13p Matt
 * Got rid of DrawPolygonObject(), since it required the inclusion of
 * object.h, which is a main directory header file (& thus shouldn't be
 * accessible by a library).
 *
 * 34    5/20/97 7:21p Jason
 * fixed stupid off-by-one bug
 *
 * 33    5/20/97 5:52p Jason
 * tweaked a couple of things with magnitude division
 *
 * 32    5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 31    5/19/97 11:46a Jason
 * normalize rotation vectors
 *
 * 30    5/16/97 3:13p Jason
 * fixed more problems with model rotation
 *
 * 29    5/16/97 1:24p Jason
 * changed the way models work their angle magic
 * Now its much more intuitive
 *
 * 28    5/16/97 12:04p Jason
 * better memory use for rotational keyframes
 *
 * 27    5/15/97 4:23p Jason
 * swap interpreted model data for mac
 *
 * 26    5/14/97 11:57p Jason
 * made polymodels use far less memory
 *
 * 25    5/14/97 7:45p Jason
 * fixed polymodel bug where it would not get deallocated correctly
 *
 *
 * 24    5/13/97 5:59p Jason
 * fixed yet another local transform bug
 *
 * 23    5/13/97 12:43p Jason
 * fixed a delta rotation problem, plus add interpolated rotational axis
 *
 * 22    5/08/97 5:11p Jason
 * fixed bug with animation rotation keyframes
 *
 * 21    5/08/97 1:16p Jason
 * made ChangeEndName work with device independant calls
 *
 * 20    4/30/97 5:43p Jason
 * remap polymodels when pagefile is done loading
 *
 * 19    4/28/97 6:46p Jason
 * made ships have multiple gun points
 *
 * 18    4/21/97 5:29p Jason
 * got animating textures to work on polygonal objects
 *
 * 17    4/21/97 4:09p Jason
 * added GetNormalizedKeyframe function
 *
 * 16    4/04/97 11:48a Jason
 * render polygon objects as linear maps
 *
 * 15    4/02/97 5:21p Jason
 * added the ability for pages to free the models that they point to
 *
 * 14    3/26/97 3:29p Jason
 * made robots work/render
 *
 * 13    3/18/97 5:22p Jason
 * took out dumb mprintfs
 *
 * 12    3/14/97 5:54p Jason
 * made positional interpolation work with 3d doors
 *
 * 11    3/14/97 10:55a Jason
 * made polymodels use delta angles instead of absolute angles
 *
 * 10    3/13/97 6:13p Jason
 * got poly doors working
 *
 * 9     3/07/97 3:59p Samir
 * Took out include to memory.h for portability.
 *
 * 8     3/05/97 3:10p Jason
 * added FreeAllModels call
 *
 * 7     3/05/97 12:17p Jason
 * took out autoloading of the ship.pof upon startup
 *
 * 6     3/04/97 11:52a Jason
 * made polymodels remap correctly
 *
 * 5     3/03/97 6:21p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */


#include "objinfo.h"
#include "polymodel.h"
#include "pserror.h"
#include "3d.h"
#include "mono.h"
#include "bitmap.h"
#include "renderer.h"
#include "manage.h"
#include "gametexture.h"
#include "lighting.h"
#include "ddio.h"
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "robotfire.h"
#include "mem.h"
#include "gamesequence.h"

#include <algorithm>

int Num_poly_models = 0;
std::array<poly_model, MAX_POLY_MODELS> Poly_models;

std::array<g3Point, MAX_POLYGON_VECS> Robot_points;

vector Interp_pos_instance_vec = {0, 0, 0};
std::array<vector, MAX_SUBOBJECTS> Instance_vec_stack;
int Instance_vec_cnt = 0;

#ifdef _DEBUG
// Flag to draw an outline around the faces
bool Polymodel_outline_mode = 0;
#endif

#define ID_OHDR 'RDHO'           // POF file header
#define ID_SOBJ 'JBOS'           // Subobject header
#define ID_IDTA 'ATDI'           // Interpreter data
#define ID_TXTR 'RTXT'           // Texture filename list
#define ID_INFO 'FNIP'           // POF file information, like command line, etc
#define ID_GRID 'DIRG'           // Grid information
#define ID_GPNT 'TNPG'           // gun points
#define ID_ROT_ANIM 'INAR'       // angular animation data
#define ID_POS_ANIM 'INAP'       // positional animation data
#define ID_ANIM 'MINA'           // angular information
#define ID_WBS 'TABW'            // Weapon Battery Info
#define ID_GROUND 'DNRG'         // Ground Plane info
#define ID_ATTACH 'HCTA'         // Attach points
#define ID_ATTACH_NORMALS 'HTAN' // Attach uvecs

int Polymodel_use_effect = 0;
polymodel_effect Polymodel_effect;
polymodel_light_type Polymodel_light_type = POLYMODEL_LIGHTING_STATIC;
float Polylighting_static_red;
float Polylighting_static_green;
float Polylighting_static_blue;
uint8_t *Polylighting_gouraud;
lightmap_object *Polylighting_lightmap_object;

vector *Polymodel_light_direction, Polymodel_fog_plane, Polymodel_specular_pos, Polymodel_fog_portal_vert,
    Polymodel_bump_pos;

static inline void RecursiveAssignWB(poly_model *pm, int sm_index, int wb_index);
static void FindWBSubobjects(poly_model *pm);
/// Sets aside a polymodel for use.
/// Errors and returns -1 if none free.
static int AllocPolyModel();
static void ReadModelVector(vector *vec, CFILE *infile);
static void ReadModelStringLen(char *ptr, int len, CFILE *infile);
/// Given a modelnumber, opens the original pof file and attempts to rematch that
/// models textures with the bitmaps with have in memory.
static int ReloadModelTextures(int modelnum);
static void SetPolymodelProperties(bsp_info *subobj, char *props);
static void MinMaxSubmodel(poly_model *pm, bsp_info *sm, vector offset);
static void FindMinMaxForModel(poly_model *pm);
static int ReadNewModelFile(int polynum, CFILE *infile);
static void SetNormalizedTimeObjTimed(object *obj, float *normalized_time);
static void SetNormalizedTimeAnimTimed(float frame, float *normalized_time, poly_model *pm);
static void FreeAllModels();
/// Given a model pointer and an array of floats that go from 0..1, calculate the interpolated
/// position/angle of each corresponding subobject.
static void SetModelAnglesAndPosTimed(poly_model *po, float *normalized_time, uint32_t subobj_flags);
static void BuildModelAngleMatrix(matrix *mat, angle ang, vector *axis);

int findtextbmpname = 0;
int findtextname = 0;

void WBClearInfo(poly_model *pm) { pm->num_wbs = 0; }

inline void RecursiveAssignWB(poly_model *pm, int sm_index, int wb_index) {
  int flags;
  int i;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  flags = wb_index << WB_INDEX_SHIFT;

  pm->submodel[sm_index].flags |= flags | SOF_WB;

  for (i = 0; i < pm->submodel[sm_index].num_children; i++) {
    RecursiveAssignWB(pm, pm->submodel[sm_index].children[i], wb_index);
  }
}

void FindWBSubobjects(poly_model *pm) {
  int i;
  bool found;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  for (i = 0; i < pm->n_models; i++) {
    if (pm->submodel[i].flags & SOF_TURRET) {
      int j;
      found = false;

      for (j = 0; j < pm->num_wbs; j++) {
        int k;

        for (k = 0; k < pm->poly_wb[j].num_turrets; k++) {
          if (pm->poly_wb[j].turret_index[k] == i) {
            found = true;
            RecursiveAssignWB(pm, i, j);
          }

          if (found)
            break;
        }

        if (found)
          break;
      }
    }
  }
}

// Sets aside a polymodel for use
// Errors and returns -1 if none free
int AllocPolyModel() {
  for (int i = 0; i < MAX_POLY_MODELS; i++)
    if (Poly_models[i].used == 0) {
      WBClearInfo(&Poly_models[i]);
      memset(&Poly_models[i], 0, sizeof(poly_model));
      Poly_models[i].used = 1;
      Poly_models[i].flags |= PMF_NOT_RESIDENT; // not in memory yet!
      return i;
    }

  Error("Couldn't find a free polymodel!");
  return -1;
}

// Frees all the polymodel data, but doesn't free the actual polymodel itself
void FreePolymodelData(int i) {
  int t;

  for (t = 0; t < Poly_models[i].n_models; t++) {
    if (Poly_models[i].submodel) {
      if (Poly_models[i].submodel[t].keyframe_axis) {
        mem_free(Poly_models[i].submodel[t].keyframe_axis);
        Poly_models[i].submodel[t].keyframe_axis = NULL;
      }

      if (Poly_models[i].submodel[t].tick_pos_remap) {
        mem_free(Poly_models[i].submodel[t].tick_pos_remap);
        Poly_models[i].submodel[t].tick_pos_remap = NULL;
      }

      if (Poly_models[i].submodel[t].tick_ang_remap) {
        mem_free(Poly_models[i].submodel[t].tick_ang_remap);
        Poly_models[i].submodel[t].tick_ang_remap = NULL;
      }

      if (Poly_models[i].submodel[t].keyframe_angles) {
        mem_free(Poly_models[i].submodel[t].keyframe_angles);
        Poly_models[i].submodel[t].keyframe_angles = NULL;
      }
      if (Poly_models[i].submodel[t].keyframe_matrix) {
        mem_free(Poly_models[i].submodel[t].keyframe_matrix);
        Poly_models[i].submodel[t].keyframe_matrix = NULL;
      }

      if (Poly_models[i].submodel[t].keyframe_pos) {
        mem_free(Poly_models[i].submodel[t].keyframe_pos);
        Poly_models[i].submodel[t].keyframe_pos = NULL;
      }

      if (Poly_models[i].submodel[t].verts) {
        mem_free(Poly_models[i].submodel[t].verts);
        Poly_models[i].submodel[t].verts = NULL;
      }

      if (Poly_models[i].submodel[t].vertnorms) {
        mem_free(Poly_models[i].submodel[t].vertnorms);
        Poly_models[i].submodel[t].vertnorms = NULL;
      }

      if (Poly_models[i].submodel[t].alpha) {
        mem_free(Poly_models[i].submodel[t].alpha);
        Poly_models[i].submodel[t].alpha = NULL;
      }

      if (Poly_models[i].submodel[t].vertnum_memory) {
        mem_free(Poly_models[i].submodel[t].vertnum_memory);
        Poly_models[i].submodel[t].vertnum_memory = NULL;
      }

      if (Poly_models[i].submodel[t].u_memory) {
        mem_free(Poly_models[i].submodel[t].u_memory);
        Poly_models[i].submodel[t].u_memory = NULL;
      }

      if (Poly_models[i].submodel[t].v_memory) {
        mem_free(Poly_models[i].submodel[t].v_memory);
        Poly_models[i].submodel[t].v_memory = NULL;
      }

      if (Poly_models[i].flags & PMF_TIMED) {
        if (Poly_models[i].submodel[t].rot_start_time) {
          mem_free(Poly_models[i].submodel[t].rot_start_time);
          Poly_models[i].submodel[t].rot_start_time = NULL;
        }

        if (Poly_models[i].submodel[t].pos_start_time) {
          mem_free(Poly_models[i].submodel[t].pos_start_time);
          Poly_models[i].submodel[t].pos_start_time = NULL;
        }
      }

      if (Poly_models[i].submodel[t].flags & (SOF_GLOW | SOF_THRUSTER)) {
        mem_free(Poly_models[i].submodel[t].glow_info);
        Poly_models[i].submodel[t].glow_info = NULL;
      }

      if (Poly_models[i].submodel[t].faces) {
        mem_free(Poly_models[i].submodel[t].faces);
        Poly_models[i].submodel[t].faces = NULL;

        if (Poly_models[i].submodel[t].face_min) {
          mem_free(Poly_models[i].submodel[t].face_min);
          Poly_models[i].submodel[t].face_min = NULL;
        }
        if (Poly_models[i].submodel[t].face_max) {
          mem_free(Poly_models[i].submodel[t].face_max);
          Poly_models[i].submodel[t].face_max = NULL;
        }
      }
    }
  }

  if (Poly_models[i].model_data) {
    mem_free(Poly_models[i].model_data);
    Poly_models[i].model_data = NULL;
  }
  if (Poly_models[i].gun_slots) {
    mem_free(Poly_models[i].gun_slots);
    Poly_models[i].gun_slots = NULL;
  }
  if (Poly_models[i].poly_wb) {
    mem_free(Poly_models[i].poly_wb);
    Poly_models[i].poly_wb = NULL;
  }
  if (Poly_models[i].attach_slots) {
    mem_free(Poly_models[i].attach_slots);
    Poly_models[i].attach_slots = NULL;
  }

  if (Poly_models[i].ground_slots) {
    mem_free(Poly_models[i].ground_slots);
    Poly_models[i].ground_slots = NULL;
  }
  if (Poly_models[i].submodel) {
    mem_free(Poly_models[i].submodel);
    Poly_models[i].submodel = NULL;
  }

  Poly_models[i].flags |= PMF_NOT_RESIDENT;
  Poly_models[i].n_models = 0;
}

// Frees polymodel located in index of Poly_models array
void FreePolyModel(int i) {
  ASSERT(Poly_models[i].used > 0);

  Poly_models[i].used--;

  if (Poly_models[i].used)
    return;

  FreePolymodelData(i);

  Poly_models[i].used = 0;
  Poly_models[i].flags |= PMF_NOT_RESIDENT;
}

void ReadModelVector(vector *vec, CFILE *infile) {
  vec->x = cf_ReadFloat(infile);
  vec->y = cf_ReadFloat(infile);
  vec->z = cf_ReadFloat(infile);
}

void ReadModelStringLen(char *ptr, int len, CFILE *infile) {
  int i;

  int mlen = cf_ReadInt(infile);
  for (i = 0; i < mlen; i++)
    ptr[i] = cf_ReadByte(infile);
}

// Given a modelnumber, opens the original pof file and attempts to rematch that
// models textures with the bitmaps with have in memory
int ReloadModelTextures(int modelnum) {
  CFILE *infile;
  int done = 0, id, len;
  poly_model *pm = &Poly_models[modelnum];

  ASSERT(!(Poly_models[modelnum].flags & PMF_NOT_RESIDENT));

  infile = cfopen(Poly_models[modelnum].name, "rb");
  if (!infile)
    return 0;

  id = cf_ReadInt(infile);

  if (id != 'OPSP')
    Error("Bad ID in model file!");
  cf_ReadInt(infile); // skip version

  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }

    id = cf_ReadInt(infile);  // read chunk type
    len = cf_ReadInt(infile); // read chunk length

    switch (id) {
    case ID_TXTR: {
      // Texture filename list
      int i, n;
      char name_buf[128];

      n = cf_ReadInt(infile);
      if (n != pm->n_textures) {
        Int3(); // Get Jason, new model doesn't match old model!!!
        cfclose(infile);
        return 0;
      }

      for (i = 0; i < n; i++) {
        int ret;
        char temp[256];

        // Read the name of this texture
        ReadModelStringLen(name_buf, 127, infile);

        strcpy(temp, name_buf);
        strcat(temp, ".OGF");
        ret = FindTextureBitmapName(temp);
        if (ret == -1) {
          // See if its already in memory
          ret = FindTextureName(name_buf);
          if (ret == -1) {
            ret = 0;
            // mprintf(0,"Object texture %s is not in memory!\n",name_buf);
          }
        }

        pm->textures[i] = ret;
        if (GameTextures[ret].alpha < .99)
          pm->flags |= PMF_ALPHA;
      }

      done = 1;
      break;
    }

    default:
      cfseek(infile, len, SEEK_CUR);
      break;
    }
  }

  cfclose(infile);
  return 1;
}

void BuildModelAngleMatrix(matrix *mat, angle ang, vector *axis) {
  float x, y, z;
  float s, c, t;

  x = axis->x;
  y = axis->y;
  z = axis->z;

  s = (float)FixSin(ang);
  c = (float)FixCos(ang);
  t = 1.0f - c;

  mat->rvec.x = t * x * x + c;
  mat->rvec.y = t * x * y + s * z;
  mat->rvec.z = t * x * z - s * y;

  mat->uvec.x = t * x * y - s * z;
  mat->uvec.y = t * y * y + c;
  mat->uvec.z = t * y * z + s * x;

  mat->fvec.x = t * x * z + s * y;
  mat->fvec.y = t * y * z - s * x;
  mat->fvec.z = t * z * z + c;
}

void SetPolymodelProperties(bsp_info *subobj, char *props) {
  // first, extract the command

  int len, i;
  char command[200], data[200];

  len = strlen(props);

  if (len < 3)
    return; // nothing to set!

  for (i = 0; i < len; i++) {
    command[i] = props[i];
    if (command[i] == '=') {
      i++;
      break; // we've found some data!
    }
  }

  command[i] = 0;

  if (len != i) {
    int datastart = i;

    for (; i < len; i++) {
      data[i - datastart] = props[i];
    }
    data[i - datastart] = 0;
  }

  // now act on the command/data pair

  if (!stricmp(command, "$rotate=")) {
    // constant rotation for a subobject
    float spinrate = atof(data);

    if (spinrate <= 0 || spinrate > 20)
      return; // bad data

    subobj->flags |= SOF_ROTATE;
    subobj->rps = 1.0f / spinrate;

    return;
  }

  if (!strnicmp(command, "$jitter", 7)) {
    // this subobject is a jittery object
    subobj->flags |= SOF_JITTER;

    return;
  }

  if (!strnicmp(command, "$shell", 6)) {
    // this subobject is a door shell

    subobj->flags |= SOF_SHELL;

    return;
  }
  if (!strnicmp(command, "$facing", 7)) {
    // this subobject always faces you
    subobj->flags |= SOF_FACING;
    return;
  }

  if (!strnicmp(command, "$frontface", 10)) {
    // this subobject is a door front

    subobj->flags |= SOF_FRONTFACE;

    return;
  }

  if (!stricmp(command, "$glow=")) {
    float r, g, b;
    float size;
    int num_found;

    ASSERT(!(subobj->flags & (SOF_GLOW | SOF_THRUSTER)));

    num_found = sscanf(data, " %f, %f, %f, %f", &r, &g, &b, &size);

    ASSERT(num_found == 4);

    subobj->flags |= SOF_GLOW;

    if (subobj->glow_info == NULL) // DAJ may already exist
      subobj->glow_info = (glowinfo *)mem_malloc(sizeof(glowinfo));

    subobj->glow_info->glow_r = r;
    subobj->glow_info->glow_g = g;
    subobj->glow_info->glow_b = b;
    subobj->glow_info->glow_size = size;

    return;
  }

  if (!stricmp(command, "$thruster=")) {
    float r, g, b;
    float size;
    int num_found;

    ASSERT(!(subobj->flags & (SOF_GLOW | SOF_THRUSTER)));

    num_found = sscanf(data, " %f, %f, %f, %f", &r, &g, &b, &size);

    ASSERT(num_found == 4);

    subobj->flags |= SOF_THRUSTER;

    if (subobj->glow_info == NULL) // DAJ may already exist
      subobj->glow_info = (glowinfo *)mem_malloc(sizeof(glowinfo));

    subobj->glow_info->glow_r = r;
    subobj->glow_info->glow_g = g;
    subobj->glow_info->glow_b = b;
    subobj->glow_info->glow_size = size;

    return;
  }

  if (!stricmp(command, "$fov=")) {
    float fov_angle;
    float turret_spr;
    float reaction_time;
    int num_found;

    num_found = sscanf(data, " %f, %f, %f", &fov_angle, &turret_spr, &reaction_time);

    ASSERT(num_found == 3);

    if (fov_angle < 0.0f || fov_angle > 360.0f) {
      // Bad data
      ASSERT(0);
      fov_angle = 1.0;
    }

    // .4 is really fast and really arbitrary
    if (turret_spr < 0.0f || turret_spr > 60.0f) {
      // Bad data
      ASSERT(0);
      turret_spr = 1.0f;
    }

    // 10 seconds is really slow and really arbitrary
    if (reaction_time < 0.0f || reaction_time > 10.0f) {
      // Bad data
      ASSERT(0);
      reaction_time = 10.0;
    }

    subobj->flags |= SOF_TURRET;
    subobj->fov = fov_angle / 720.0f; // 720 = 360 * 2 and we want to make fov the amount we can move in either
                                      // direction it has a minimum value of (0.0) to [0.5]
    subobj->rps = 1.0 / turret_spr;   // convert spr to rps (rotations per second)
    subobj->think_interval = reaction_time;

    return;
  }

  if (!stricmp(command, "$monitor01")) {
    // this subobject is a monitor
    subobj->flags |= SOF_MONITOR1;
    return;
  }

  if (!stricmp(command, "$monitor02")) {
    // this subobject is a 2nd monitor
    subobj->flags |= SOF_MONITOR2;
    return;
  }

  if (!stricmp(command, "$monitor03")) {
    // this subobject is a 3rd monitor
    subobj->flags |= SOF_MONITOR3;
    return;
  }

  if (!stricmp(command, "$monitor04")) {
    // this subobject is a 4th monitor
    subobj->flags |= SOF_MONITOR4;
    return;
  }

  if (!stricmp(command, "$monitor05")) {
    // this subobject is a 4th monitor
    subobj->flags |= SOF_MONITOR5;
    return;
  }

  if (!stricmp(command, "$monitor06")) {
    // this subobject is a 4th monitor
    subobj->flags |= SOF_MONITOR6;
    return;
  }

  if (!stricmp(command, "$monitor07")) {
    // this subobject is a 4th monitor
    subobj->flags |= SOF_MONITOR7;
    return;
  }

  if (!stricmp(command, "$monitor08")) {
    // this subobject is a 4th monitor
    subobj->flags |= SOF_MONITOR8;
    return;
  }

  if (!stricmp(command, "$viewer")) {
    // this subobject is a viewer
    subobj->flags |= SOF_VIEWER;
    return;
  }

  if (!stricmp(command, "$layer")) {
    // this subobject is a layer to be drawn after original object.
    subobj->flags |= SOF_LAYER;
    return;
  }
  if (!stricmp(command, "$custom")) {
    // this subobject has custom textures/colors
    subobj->flags |= SOF_CUSTOM;

    return;
  }
}

void MinMaxSubmodel(poly_model *pm, bsp_info *sm, vector offset) {

  offset += sm->offset;
  // Get max
  if ((sm->max.x + offset.x) > pm->maxs.x)
    pm->maxs.x = sm->max.x + offset.x;
  if ((sm->max.y + offset.y) > pm->maxs.y)
    pm->maxs.y = sm->max.y + offset.y;
  if ((sm->max.z + offset.z) > pm->maxs.z)
    pm->maxs.z = sm->max.z + offset.z;

  // Get min
  if ((sm->min.x + offset.x) < pm->mins.x)
    pm->mins.x = sm->min.x + offset.x;
  if ((sm->min.y + offset.y) < pm->mins.y)
    pm->mins.y = sm->min.y + offset.y;
  if ((sm->min.z + offset.z) < pm->mins.z)
    pm->mins.z = sm->min.z + offset.z;

  for (int i = 0; i < sm->num_children; i++)
    MinMaxSubmodel(pm, &pm->submodel[sm->children[i]], offset);
}

void FindMinMaxForModel(poly_model *pm) {

  vector zero_vec;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  vm_MakeZero(&zero_vec);
  pm->mins.x = pm->mins.y = pm->mins.z = 90000;
  pm->maxs.x = pm->maxs.y = pm->maxs.z = -90000;

  for (int i = 0; i < pm->n_models; i++) {
    bsp_info *sm = &pm->submodel[i];
    if (sm->parent == -1)
      MinMaxSubmodel(pm, sm, zero_vec);
  }
}

int ReadNewModelFile(int polynum, CFILE *infile) {
  int version, done = 0, i, t, version_major;
  int id, len;
  poly_model *pm = &Poly_models[polynum];
  int timed = 0;

  ASSERT(pm->new_style);

  id = cf_ReadInt(infile);

  if (id != 'OPSP')
    Error("Bad ID in model file!");

  // Version is major*100+minor
  // So, major = version / 100;
  //     minor = version % 100;

  version = cf_ReadInt(infile);
  if (version < 18) {
    mprintf(0, "Old POF Version of %d fixed up to %d\n", version, version * 100);
    version *= 100;
  }

  if (version < PM_COMPATIBLE_VERSION || version > PM_OBJFILE_VERSION) {
    mprintf(0, "Bad version (%d) in model file!\n", version);
    Int3();
    return 0;
  }

  pm->version = version;
  version_major = version / 100;

  if (version_major >= 21)
    pm->flags |= PMF_LIGHTMAP_RES;
  if (version_major >= 22) {
    timed = 1;
    pm->flags |= PMF_TIMED;
    pm->frame_min = 0;
    pm->frame_max = 0;
  }

  pm->n_attach = 0;

  memset(&pm->view_pos, 0, sizeof(pm->view_pos));

  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }

    id = cf_ReadInt(infile);
    len = cf_ReadInt(infile);

    switch (id) {
    case ID_OHDR: {
      // Object header

      // mprintf(0,"Object header...\n");

      pm->n_models = cf_ReadInt(infile);
      pm->rad = cf_ReadFloat(infile);

      pm->submodel = (bsp_info *)mem_malloc(sizeof(bsp_info) * pm->n_models);
      ASSERT(pm->submodel != NULL);
      memset(pm->submodel, 0, sizeof(bsp_info) * pm->n_models);

      ReadModelVector(&pm->mins, infile);
      ReadModelVector(&pm->maxs, infile);

      // pm->n_detail_levels = cf_ReadInt(infile);
      int det = cf_ReadInt(infile); // skip detail

      for (i = 0; i < det; i++) {
        // pm->detail[i] = cf_ReadInt(infile);
        // pm->detail_depth[i] = 0.0f;
        cf_ReadInt(infile);
      }

      // Adjust min/maxs to be based on zero
      /*vector temp_vec=pm->maxs-pm->mins;

      temp_vec/=2;

      pm->mins=-temp_vec;
      pm->maxs=temp_vec;*/

      break;
    }

    case ID_SOBJ: {
      // Subobject header
      int n;
      char props[MAX_PROP_LEN];
      float d;

      // mprintf(0,"Got chunk SOBJ, len=%d\n",len);

      n = cf_ReadInt(infile);

      ASSERT(n < pm->n_models);

      pm->submodel[n].min.x = pm->submodel[n].min.y = pm->submodel[n].min.z = 90000;
      pm->submodel[n].max.x = pm->submodel[n].max.y = pm->submodel[n].max.z = -90000;

      pm->submodel[n].parent = cf_ReadInt(infile);

      ReadModelVector(&pm->submodel[n].norm, infile);

      d = cf_ReadFloat(infile);
      ReadModelVector(&pm->submodel[n].pnt, infile);
      ReadModelVector(&pm->submodel[n].offset, infile);

      pm->submodel[n].rad = cf_ReadFloat(infile); // radius

      pm->submodel[n].tree_offset = cf_ReadInt(infile); // offset
      pm->submodel[n].data_offset = cf_ReadInt(infile); // offset

      if (pm->version > 1805)
        ReadModelVector(&pm->submodel[n].geometric_center, infile);
      else {
        // for old models, hack in 0,0,0, which says the geometric center is
        // equal to pivot point, which is not always true.
        vm_MakeZero(&pm->submodel[n].geometric_center);
      }

      pm->submodel[n].name[0] = '\0';

      ReadModelStringLen(pm->submodel[n].name, PAGENAME_LEN, infile);
      ReadModelStringLen(props, MAX_PROP_LEN, infile); // and the user properites

      SetPolymodelProperties(&pm->submodel[n], props);

      pm->submodel[n].movement_type = cf_ReadInt(infile);
      pm->submodel[n].movement_axis = cf_ReadInt(infile);

      if (pm->submodel[n].name[0] == '\0')
        strcpy(pm->submodel[n].name, "unknown object name");

      memset(&pm->submodel[n].angs, 0, sizeof(angvec));

      // Skip freespace chunks
      int n_chunks = cf_ReadInt(infile);
      if (n_chunks > 0) {
        for (i = 0; i < n_chunks; i++)
          cf_ReadInt(infile);
      }

      int nverts = cf_ReadInt(infile);
      ASSERT(nverts < MAX_POLYGON_VECS);

      if (nverts) {
        pm->submodel[n].verts = (vector *)mem_malloc(nverts * sizeof(vector));
        pm->submodel[n].vertnorms = (vector *)mem_malloc(nverts * sizeof(vector));
        pm->submodel[n].alpha = (float *)mem_malloc(nverts * sizeof(float));
        ASSERT(pm->submodel[n].verts);
        ASSERT(pm->submodel[n].vertnorms);
        ASSERT(pm->submodel[n].alpha);
      } else {
        // Let me take a moment right here to say how annoying it is that I can't
        // set all these pointers to NULL with one assignment on the same line due
        // to the stupid strong typying they've added to C.
        pm->submodel[n].verts = NULL;
        pm->submodel[n].vertnorms = NULL;
        pm->submodel[n].alpha = NULL;
      }

      pm->submodel[n].nverts = nverts;

      for (i = 0; i < nverts; i++) {
        ReadModelVector(&pm->submodel[n].verts[i], infile);

        // Get max
        if (pm->submodel[n].verts[i].x > pm->submodel[n].max.x)
          pm->submodel[n].max.x = pm->submodel[n].verts[i].x;
        if (pm->submodel[n].verts[i].y > pm->submodel[n].max.y)
          pm->submodel[n].max.y = pm->submodel[n].verts[i].y;
        if (pm->submodel[n].verts[i].z > pm->submodel[n].max.z)
          pm->submodel[n].max.z = pm->submodel[n].verts[i].z;

        // Get min
        if (pm->submodel[n].verts[i].x < pm->submodel[n].min.x)
          pm->submodel[n].min.x = pm->submodel[n].verts[i].x;
        if (pm->submodel[n].verts[i].y < pm->submodel[n].min.y)
          pm->submodel[n].min.y = pm->submodel[n].verts[i].y;
        if (pm->submodel[n].verts[i].z < pm->submodel[n].min.z)
          pm->submodel[n].min.z = pm->submodel[n].verts[i].z;
      }
      for (i = 0; i < nverts; i++)
        ReadModelVector(&pm->submodel[n].vertnorms[i], infile);

      // Read alpha per vertex
      if (version_major >= 23) {
        for (i = 0; i < nverts; i++) {
          pm->submodel[n].alpha[i] = cf_ReadFloat(infile);
          if (pm->submodel[n].alpha[i] < .99)
            pm->flags |= PMF_ALPHA;
        }
      } else {
        for (i = 0; i < nverts; i++)
          pm->submodel[n].alpha[i] = 1.0;
      }

      int nfaces = cf_ReadInt(infile);
      pm->submodel[n].num_faces = nfaces;

      if (nfaces) {
        pm->submodel[n].faces = (polyface *)mem_malloc(nfaces * sizeof(polyface));
        pm->submodel[n].face_min = (vector *)mem_malloc(nfaces * sizeof(vector));
        pm->submodel[n].face_max = (vector *)mem_malloc(nfaces * sizeof(vector));
        ASSERT(pm->submodel[n].faces);
      } else {
        pm->submodel[n].faces = NULL;
        pm->submodel[n].face_max = NULL;
        pm->submodel[n].face_min = NULL;
      }

      // Find out how much space we'll need
      bsp_info *sm = &pm->submodel[n];

      vector tvec;
      int current_count = 0;

      int save_position = cftell(infile);
      int *start_index;

      if (nfaces) {
        start_index = (int *)mem_malloc(sizeof(int) * nfaces);
        ASSERT(start_index);
      } else
        start_index = NULL;

      uint8_t tempbuf[2000];

      for (i = 0; i < nfaces; i++) {
        ReadModelVector(&tvec, infile);
        int num_verts = cf_ReadInt(infile);

        ASSERT(num_verts < 100);
        ASSERT(num_verts > 0);
        start_index[i] = current_count;
        current_count += num_verts;

        // Skip the rest
        if (cf_ReadInt(infile))
          cf_ReadInt(infile);
        else
          cf_ReadBytes(tempbuf, 3, infile);

        cf_ReadBytes(tempbuf, 12 * num_verts, infile);

        if (version_major >= 21)
          cf_ReadBytes(tempbuf, 8, infile);
      }

      // Allocate our space
      if (current_count) {
        sm->vertnum_memory = (int16_t *)mem_malloc(current_count * sizeof(int16_t));
        ASSERT(sm->vertnum_memory);

        sm->u_memory = (float *)mem_malloc(current_count * sizeof(float));
        ASSERT(sm->u_memory);

        sm->v_memory = (float *)mem_malloc(current_count * sizeof(float));
        ASSERT(sm->v_memory);
      } else {
        sm->vertnum_memory = NULL;
        sm->u_memory = NULL;
        sm->v_memory = NULL;
      }

      // Now go through and set up our fake pointers
      for (i = 0; i < nfaces; i++) {
        sm->faces[i].vertnums = &sm->vertnum_memory[start_index[i]];
        sm->faces[i].u = &sm->u_memory[start_index[i]];
        sm->faces[i].v = &sm->v_memory[start_index[i]];
      }

      // Reset our file pointer and free the temp memory
      cfseek(infile, save_position, SEEK_SET);

      if (start_index)
        mem_free(start_index);

      for (i = 0; i < nfaces; i++) {
        ReadModelVector(&pm->submodel[n].faces[i].normal, infile);

        int num_verts = cf_ReadInt(infile);
        pm->submodel[n].faces[i].nverts = num_verts;

        int textured = cf_ReadInt(infile);
        if (textured) {
          pm->submodel[n].faces[i].texnum = cf_ReadInt(infile);

        } else {
          pm->submodel[n].faces[i].texnum = -1;
          uint8_t r, g, b;
          r = cf_ReadByte(infile);
          g = cf_ReadByte(infile);
          b = cf_ReadByte(infile);
          pm->submodel[n].faces[i].color = GR_RGB(r, g, b);
        }

        for (t = 0; t < pm->submodel[n].faces[i].nverts; t++) {
          int val;
          vector *min_ptr = &pm->submodel[n].face_min[i];
          vector *max_ptr = &pm->submodel[n].face_max[i];
          vector *v_ptr;

          val = cf_ReadInt(infile);
          pm->submodel[n].faces[i].vertnums[t] = val;
          pm->submodel[n].faces[i].u[t] = cf_ReadFloat(infile);
          pm->submodel[n].faces[i].v[t] = cf_ReadFloat(infile);

          v_ptr = &pm->submodel[n].verts[pm->submodel[n].faces[i].vertnums[t]];

          if (t == 0) {
            *min_ptr = *max_ptr = *v_ptr;
          } else {
            if (v_ptr->x < min_ptr->x)
              min_ptr->x = v_ptr->x;
            else if (v_ptr->x > max_ptr->x)
              max_ptr->x = v_ptr->x;

            if (v_ptr->y < min_ptr->y)
              min_ptr->y = v_ptr->y;
            else if (v_ptr->y > max_ptr->y)
              max_ptr->y = v_ptr->y;

            if (v_ptr->z < min_ptr->z)
              min_ptr->z = v_ptr->z;
            else if (v_ptr->z > max_ptr->z)
              max_ptr->z = v_ptr->z;
          }
        }

        // Do lightmap res computation
        if (version_major >= 21) {
          float xdiff, ydiff;

          xdiff = cf_ReadFloat(infile);
          ydiff = cf_ReadFloat(infile);
        }
      }

      break;
    }

    case ID_GPNT:
      pm->n_guns = cf_ReadInt(infile);
      pm->gun_slots = (w_bank *)mem_malloc(sizeof(w_bank) * pm->n_guns);
      ASSERT(pm->gun_slots != NULL);

      for (i = 0; i < pm->n_guns; i++) {
        w_bank *bank = &pm->gun_slots[i];

        // In Version 19.08 and beyond, gunpoints are associated to their parent object.
        if (version >= 19 * 100 + 8) {
          bank->parent = cf_ReadInt(infile);
        } else {
          bank->parent = 0;
        }

        ReadModelVector(&bank->pnt, infile);
        ReadModelVector(&bank->norm, infile);
      }
      break;

    case ID_ATTACH:
      pm->n_attach = cf_ReadInt(infile);
      if (pm->n_attach) {
        pm->attach_slots = (a_bank *)mem_malloc(sizeof(a_bank) * pm->n_attach);
        ASSERT(pm->attach_slots != NULL);

        for (i = 0; i < pm->n_attach; i++) {
          a_bank *bank = &pm->attach_slots[i];

          bank->parent = cf_ReadInt(infile);
          ReadModelVector(&bank->pnt, infile);
          ReadModelVector(&bank->norm, infile);
          bank->f_uvec = false;
        }
      } else {
        pm->attach_slots = NULL;
      }
      break;

    case ID_ATTACH_NORMALS: {
      bool f_uvec = false;
      int num_normals;

      if (pm->n_attach == (num_normals = cf_ReadInt(infile)))
        f_uvec = true;
      else {
        mprintf(0, "WARNING: Ingoring ATTACH normals - total number doesn't match number of attach points\n");
        // Int3();
        DataError("Model <%s> specifies %d attach points but only contains %d attach normals\n", pm->name, pm->n_attach,
                  num_normals);
      }

      if (num_normals) {
        for (i = 0; i < num_normals; i++) {
          vector temp;
          a_bank *bank = &pm->attach_slots[i];

          cf_ReadInt(infile);
          ReadModelVector(&temp, infile);
          ReadModelVector(&bank->uvec, infile);
          bank->f_uvec = f_uvec;
        }
      } else {
        pm->attach_slots = NULL;
      }
      break;
    }

    case ID_WBS: {
      int i;
      int j;

      // Get the number of weapon batteries on this object
      pm->num_wbs = cf_ReadInt(infile);

      if (pm->num_wbs) {
        pm->poly_wb = (poly_wb_info *)mem_malloc(sizeof(poly_wb_info) * pm->num_wbs);

        // Get each individual wb info struct
        for (i = 0; i < pm->num_wbs; i++) {
          pm->poly_wb[i].num_gps = cf_ReadInt(infile);
          for (j = 0; j < pm->poly_wb[i].num_gps; j++) {
            if (j <= 7)
              pm->poly_wb[i].gp_index[j] = cf_ReadInt(infile);
            else
              cf_ReadInt(infile);
          }

          if (pm->poly_wb[i].num_gps > 8)
            pm->poly_wb[i].num_gps = 8;

          pm->poly_wb[i].num_turrets = cf_ReadInt(infile);
          for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
            if (j <= 7)
              pm->poly_wb[i].turret_index[j] = cf_ReadInt(infile);
            else
              cf_ReadInt(infile);
          }
          if (pm->poly_wb[i].num_turrets > 8)
            pm->poly_wb[i].num_turrets = 8;
        }
      } else {
        pm->poly_wb = NULL;
      }

      break;
    }

    case ID_GROUND:
      pm->n_ground = cf_ReadInt(infile);
      pm->ground_slots = (w_bank *)mem_malloc(sizeof(w_bank) * pm->n_ground);
      ASSERT(pm->ground_slots != NULL);

      for (i = 0; i < pm->n_ground; i++) {
        w_bank *bank = &pm->ground_slots[i];

        bank->parent = cf_ReadInt(infile);

        ReadModelVector(&bank->pnt, infile);
        ReadModelVector(&bank->norm, infile);
      }
      break;

    case ID_TXTR: {
      // Texture filename list
      int i, n;
      char name_buf[128];

      // mprintf(0,"Got chunk TXTR, len=%d\n",len);

      n = cf_ReadInt(infile);
      pm->n_textures = n;
      ASSERT(n < MAX_MODEL_TEXTURES);

      for (i = 0; i < n; i++) {
        int ret;
        char temp[256];

        // Read the name of this texture
        ReadModelStringLen(name_buf, 127, infile);

        strcpy(temp, name_buf);
        strcat(temp, ".OGF");

        ret = FindTextureBitmapName(temp);
        if (ret == -1) {
          // See if its already in memory
          ret = FindTextureName(name_buf);
          if (ret == -1) {
            ret = 0;
            // mprintf(0,"Object texture %s is not in memory!\n",name_buf);
          }
        }

        pm->textures[i] = ret;
        if (GameTextures[ret].alpha < .99)
          pm->flags |= PMF_ALPHA;
      }

      break;
    }

    case ID_ROT_ANIM:
    case ID_ANIM: {
      int nframes;
      // mprintf(0,"ROT ANIM chunk!!!\n");

      if (!timed) {
        nframes = cf_ReadInt(infile);
        pm->num_key_angles = nframes;
      }

      for (int i = 0; i < pm->n_models; i++) {

        if (timed) {
          pm->submodel[i].num_key_angles = cf_ReadInt(infile);
          pm->submodel[i].rot_track_min = cf_ReadInt(infile);
          pm->submodel[i].rot_track_max = cf_ReadInt(infile);

          if (pm->submodel[i].rot_track_min < pm->frame_min)
            pm->frame_min = pm->submodel[i].rot_track_min;
          if (pm->submodel[i].rot_track_max > pm->frame_max)
            pm->frame_max = pm->submodel[i].rot_track_max;
        } else {
          pm->submodel[i].num_key_angles = nframes;
        }

        pm->submodel[i].keyframe_axis = (vector *)mem_malloc((pm->submodel[i].num_key_angles + 1) * sizeof(vector));
        pm->submodel[i].keyframe_angles = (int *)mem_malloc((pm->submodel[i].num_key_angles + 1) * sizeof(int));
        pm->submodel[i].keyframe_matrix = (matrix *)mem_malloc((pm->submodel[i].num_key_angles + 1) * sizeof(matrix));
        if (timed) {
          pm->submodel[i].rot_start_time = (int *)mem_malloc((pm->submodel[i].num_key_angles + 1) * sizeof(int));
          ASSERT(pm->submodel[i].rot_start_time != NULL);

          int num_ticks = (pm->submodel[i].rot_track_max - pm->submodel[i].rot_track_min);

          if (num_ticks > 0) {
            pm->submodel[i].tick_ang_remap = (uint16_t *)mem_malloc(num_ticks * 2);
            ASSERT(pm->submodel[i].tick_ang_remap);
          } else {
            pm->submodel[i].tick_ang_remap = NULL;
          }
        }

        ASSERT(pm->submodel[i].keyframe_axis != NULL);
        ASSERT(pm->submodel[i].keyframe_angles != NULL);
        ASSERT(pm->submodel[i].keyframe_matrix != NULL);

        for (int t = 0; t < pm->submodel[i].num_key_angles; t++) {
          vector *axis;
          float mag;

          if (timed)
            pm->submodel[i].rot_start_time[t] = cf_ReadInt(infile);

          ReadModelVector(&pm->submodel[i].keyframe_axis[t + 0], infile);
          axis = &pm->submodel[i].keyframe_axis[t + 0];

          mag = vm_GetMagnitude(axis);
          if (mag > 0)
            pm->submodel[i].keyframe_axis[t] /= mag;

          pm->submodel[i].keyframe_angles[t + 0] = cf_ReadInt(infile);
          // if this axis is backwards, rotate the angle the other direction
          if (t == 0) {
            /*if (pm->submodel[i].keyframe_angles[0]>=32768)
            {
                    mprintf(0,"\nFlipping suboject %s!\n",pm->submodel[i].name);
                    pm->submodel[i].keyframe_angles[0]*=-1;
            }*/
          }
          /*else
                  dir=vm_DotProduct (axis,&pm->submodel[i].keyframe_axis[1]);

          if (dir<0)
          {
                  pm->submodel[i].keyframe_angles[t+0]*=-1;
                  pm->submodel[i].keyframe_axis[t+0]*=-1.0;
          }*/
        }
      }

      break;
    }

    case ID_POS_ANIM: {
      int nframes;

      // mprintf(0,"POS ANIM chunk!!!\n");
      if (!timed) {
        nframes = cf_ReadInt(infile);
        pm->num_key_pos = nframes;
      }

      for (int i = 0; i < pm->n_models; i++) {
        if (timed) {
          pm->submodel[i].num_key_pos = cf_ReadInt(infile);
          pm->submodel[i].pos_track_min = cf_ReadInt(infile);
          pm->submodel[i].pos_track_max = cf_ReadInt(infile);

          if (pm->submodel[i].pos_track_min < pm->frame_min)
            pm->frame_min = pm->submodel[i].pos_track_min;
          if (pm->submodel[i].pos_track_max > pm->frame_max)
            pm->frame_max = pm->submodel[i].pos_track_max;

          int num_ticks = (pm->submodel[i].pos_track_max - pm->submodel[i].pos_track_min);

          if (num_ticks > 0) {
            pm->submodel[i].tick_pos_remap = (uint16_t *)mem_malloc(num_ticks * 2);
            ASSERT(pm->submodel[i].tick_pos_remap);
          } else {
            pm->submodel[i].tick_pos_remap = NULL;
          }

        } else
          pm->submodel[i].num_key_pos = nframes;

        pm->submodel[i].keyframe_pos = (vector *)mem_malloc((pm->submodel[i].num_key_pos + 1) * sizeof(vector));
        ASSERT(pm->submodel[i].keyframe_pos != NULL);

        if (timed) {
          pm->submodel[i].pos_start_time = (int *)mem_malloc((pm->submodel[i].num_key_pos + 1) * sizeof(int));
          ASSERT(pm->submodel[i].pos_start_time != NULL);
        }

        for (int t = 0; t < pm->submodel[i].num_key_pos; t++) {
          if (timed)
            pm->submodel[i].pos_start_time[t] = cf_ReadInt(infile);

          ReadModelVector(&pm->submodel[i].keyframe_pos[t + 0], infile);
        }
      }

      break;
    }
    default:
      // mprintf(0,"Unknown chunk <%c%c%c%c>, len = %d\n",id,id>>8,id>>16,id>>24,len);
      cfseek(infile, len, SEEK_CUR);
      break;
    }
  }

  // Set the greater of keyframe of positions or keyframe angles to to be max keyframes
  pm->max_keys = std::max(pm->num_key_pos, pm->num_key_angles);

  // Build animation keyframe matrices

  matrix base_matrix, dest_matrix, temp_matrix;
  int cur_angle;
  int parent;

  for (i = 0; i < pm->n_models; i++) {
    vm_MakeIdentity(&base_matrix);

    bsp_info *sm = &pm->submodel[i];

    int newt;
    for (newt = 0; newt < sm->num_key_angles; newt++) {
      cur_angle = sm->keyframe_angles[newt];
      BuildModelAngleMatrix(&temp_matrix, cur_angle, &sm->keyframe_axis[newt]);
      vm_MakeIdentity(&dest_matrix);
      dest_matrix = temp_matrix * base_matrix;
      base_matrix = dest_matrix;
      sm->keyframe_matrix[newt] = base_matrix;
    }

    // Build children
    parent = pm->submodel[i].parent;

    if (parent == i) {
      pm->submodel[i].parent = -1;

    } else if (parent != -1) {
      pm->submodel[parent].children[pm->submodel[parent].num_children] = i;
      pm->submodel[parent].num_children++;
    }

    if (pm->submodel[i].num_key_angles == 0 && (pm->submodel[i].flags & SOF_ROTATE)) {
      mprintf(0, "You have a rotator that has no keyframe on model %s.\n", pm->name);
      pm->submodel[i].flags &= ~SOF_ROTATE;
    } else if (pm->submodel[i].num_key_angles == 0 && (pm->submodel[i].flags & SOF_TURRET)) {
      mprintf(0, "You have a turret that has no keyframe on model %s.\n", pm->name);
      pm->submodel[i].flags &= ~SOF_TURRET;
    }

    // Figure out the size of this facing subobject
    if (pm->submodel[i].flags & SOF_FACING) {
      ASSERT(pm->submodel[i].num_faces == 1); // This facing has more than one face
      vector vecs[30];
      vector avg;

      int newt;
      for (newt = 0; newt < pm->submodel[i].faces[0].nverts; newt++) {
        vecs[newt] = pm->submodel[i].verts[pm->submodel[i].faces[0].vertnums[newt]];
      }

      pm->submodel[i].rad = (sqrt(vm_GetCentroid(&avg, vecs, pm->submodel[i].faces[0].nverts)) / 2);

      pm->flags |= PMF_FACING;
    }

    if (pm->submodel[i].flags & (SOF_GLOW | SOF_THRUSTER)) {
      ASSERT(pm->submodel[i].num_faces == 1); // This glow has more than one face
      vector vecs[30];

      for (t = 0; t < pm->submodel[i].faces[0].nverts; t++)
        vecs[t] = pm->submodel[i].verts[pm->submodel[i].faces[0].vertnums[t]];

      vm_GetNormal(&pm->submodel[i].glow_info->normal, &vecs[0], &vecs[1], &vecs[2]);

      pm->flags |= PMF_FACING; // Set this so we know when to draw
    }

    // Now build the tick/keyframe remap list
    int num_ticks = (pm->submodel[i].pos_track_max - pm->submodel[i].pos_track_min);
    for (t = 0; timed && t < num_ticks; t++) {
      int done = 0;
      int current_tick = sm->pos_track_min + t;

      if (sm->num_key_pos > 1) {
        for (int k = sm->num_key_pos - 1; k >= 0 && !done; k--) {
          if (current_tick >= sm->pos_start_time[k]) {
            sm->tick_pos_remap[t] = k;
            done = 1;
          }
        }

        if (done == 0) {
          mprintf(0, "Couldn't get a good keyframe!\n");
          Int3();
        }
      }
    }

    // Now build the tick/keyframe remap list
    num_ticks = (pm->submodel[i].rot_track_max - pm->submodel[i].rot_track_min);
    for (t = 0; timed && t < num_ticks; t++) {
      if (sm->num_key_angles > 1) {
        int done = 0;
        int current_tick = sm->rot_track_min + t;
        for (int k = sm->num_key_angles - 1; k >= 0 && !done; k--) {
          if (current_tick >= sm->rot_start_time[k]) {
            sm->tick_ang_remap[t] = k;
            done = 1;
          }
        }

        if (done == 0) {
          mprintf(0, "Couldn't get a good keyframe!\n");
          Int3();
        }
      }
    }
  }

  pm->flags &= ~PMF_NOT_RESIDENT; // mark it as in memory

  // Find Min/Max of whole model
  FindMinMaxForModel(pm);

  // adjust positional interpolation frames


  FindWBSubobjects(pm);

  // Set as newstyle
  pm->new_style = 1;

  if (pm->n_models > MAX_SUBOBJECTS) {
    mprintf(0, "This model has more than the max number of subobjects! (%d)\n", MAX_SUBOBJECTS);
    Int3();
    FreePolyModel(pm - std::data(Poly_models));
    return 0;
  }

  return 1;
}

// given a filename, reads in a POF and returns an index into the Poly_models array
// returns -1 if something is wrong
int LoadPolyModel(const char *filename, int pageable) {
  char name[256];
  char fname[256], pname[256], extname[256];
  int i, polynum = -1;
  CFILE *infile = NULL;
  int overlay = 0;

  ASSERT(Num_poly_models >= 0);
  ASSERT(Num_poly_models < MAX_POLY_MODELS);

  ChangePolyModelName(filename, name);

  // If this polymodel is already in memory, just use that index
  i = FindPolyModelName(name);
  if (i != -1) {
#ifdef RELEASE
    Poly_models[i].used++;
    return i;
#endif

    int old_used = Poly_models[i].used;
    int not_res = 0;

    if (Poly_models[i].flags & PMF_NOT_RESIDENT)
      not_res = 1;

    mprintf(1, "Model '%s' usage count is now %d.\n", Poly_models[i].name, Poly_models[i].used + 1);

    Poly_models[i].used = 1;
    FreePolyModel(i);

    memset(&Poly_models[i], 0, sizeof(poly_model));
    WBClearInfo(&Poly_models[i]);
    Poly_models[i].used = old_used + 1;
    if (not_res)
      Poly_models[i].flags = PMF_NOT_RESIDENT;

    overlay = 1;
    polynum = i;
  }

  // Not in memory, so we must load it

  ddio_SplitPath(filename, pname, fname, extname);

  if (!pageable) {
    infile = cfopen(filename, "rb");
    if (!infile)
      return -1;
  }

  if (!overlay)
    polynum = AllocPolyModel();
  else {
    if (!(Poly_models[polynum].flags & PMF_NOT_RESIDENT)) {
      if (pageable) {
        infile = cfopen(filename, "rb");
        if (!infile)
          return -1;
      }
      pageable = 0;
    }
  }

  ASSERT(polynum >= 0);

  // Used for progress bar when loading the level
  if (infile) {
    paged_in_count += cfilelength(infile);
    paged_in_num++;
  }

  // if this is an oof instead of a pof, flag it as such
  if (!stricmp(".OOF", extname)) {
    Poly_models[polynum].new_style = 1;
  } else
    Poly_models[polynum].new_style = 0;

  // mprintf(0,"Loading model %s\n",name);
  strcpy(Poly_models[polynum].name, name);

  int ret = 0;
  if (!pageable)
    ret = ReadNewModelFile(polynum, infile);
  else
    ret = 1;

  if (infile)
    cfclose(infile);

  Poly_models[polynum].id = polynum;

  if (ret)
    return polynum; // loaded successfully

  return -1; // damn, didn't load
}

// Pages in a polymodel if its not already in memory
void PageInPolymodel(int polynum, int type, float *size_ptr) {
  if (!(Poly_models[polynum].flags & PMF_NOT_RESIDENT)) {
    if (!(Poly_models[polynum].flags & PMF_SIZE_COMPUTED))
      if (type != -1) {
        ComputeDefaultSize(type, polynum, size_ptr);
      }
    return;
  }

  mprintf(0, "Paging in polymodel %s.\n", Poly_models[polynum].name);

  CFILE *infile;
  infile = (CFILE *)cfopen(Poly_models[polynum].name, "rb");

  if (!infile) {
    // due to a bug in some 3rd party tablefile editors, full paths might
    // have been used when they shouldn't have been
    char *end_ptr, *start_ptr;
    start_ptr = Poly_models[polynum].name;
    end_ptr = start_ptr + strlen(start_ptr) - 1;
    while ((end_ptr >= start_ptr) && (*end_ptr != '\\'))
      end_ptr--;
    if (end_ptr < start_ptr) {
      Error("Failed to page in %s.", Poly_models[polynum].name);
      return;
    }

    ASSERT(*end_ptr == '\\');
    end_ptr++;

    infile = (CFILE *)cfopen(end_ptr, "rb");
    if (!infile) {
      Error("Failed to page in %s.", Poly_models[polynum].name);
      return;
    }
  }

  //	ASSERT(infile);

  int ret = ReadNewModelFile(polynum, infile);

  cfclose(infile);
  ASSERT(ret > 0);

  // See if textures need to be remapped
  int remap = 0;
  for (int t = 0; t < Poly_models[polynum].n_textures; t++)
    if (Poly_models[polynum].textures[t] == 0) // is there a bad texture?
      remap = 1;

  if (remap == 1) {
    // remap the damn textures
    mprintf(0, "Remapping model textures for model %s.\n", Poly_models[polynum].name);
    ReloadModelTextures(polynum);
  }

  if (type != -1) {
    ComputeDefaultSize(type, polynum, size_ptr);
  }
}

// Gets a pointer to a polymodel.  Pages it in if neccessary
poly_model *GetPolymodelPointer(int polynum) {
  if (Poly_models[polynum].flags & PMF_NOT_RESIDENT)
    PageInPolymodel(polynum);

  return (&Poly_models[polynum]);
}

// MTS: only used in this file.
// gets the filename from a path
void ChangePolyModelName(const char *src, char *dest) {
  int limit;
  char path[256], ext[256], filename[256];

  limit = PAGENAME_LEN - 5;

  ddio_SplitPath(src, path, filename, ext);

  // Make sure we don't go over our name length limit
  strncpy(dest, filename, limit);

  strcat(dest, ext);
}
// Searches thru all polymodels for a specific name, returns -1 if not found
// or index of polymodel with name
int FindPolyModelName(const char *name) {
  int i;

  for (i = 0; i < MAX_POLY_MODELS; i++)
    if (Poly_models[i].used && !stricmp(Poly_models[i].name, name))
      return i;

  return -1;
}

// Sets a positional instance
void StartPolyModelPosInstance(vector *posvec) {

  Interp_pos_instance_vec = *posvec;

  Instance_vec_stack[Instance_vec_cnt] = Interp_pos_instance_vec;
  Instance_vec_cnt++;
}

// Pops a positional instance
void DonePolyModelPosInstance() {
  Instance_vec_cnt--;

  if (Instance_vec_cnt == 0)
    memset(&Interp_pos_instance_vec, 0, sizeof(vector));
  else
    Interp_pos_instance_vec = Instance_vec_stack[Instance_vec_cnt];
}

void SetNormalizedTimeObjTimed(object *obj, float *normalized_time) {
  int i, j;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  object_info *obj_info = &Object_info[obj->id];

  if (obj->type == OBJ_PLAYER || obj->type == OBJ_WEAPON)
    return;

  // Setup all the subobjects for the keyframe
  float frame = obj->rtype.pobj_info.anim_frame;

  for (i = 0; i < pm->n_models; i++) {
    bsp_info *sm = &pm->submodel[i];
    int x = (sm->flags & SOF_WB_MASKS) >> WB_INDEX_SHIFT;

    if (!(sm->flags & SOF_TURRET) &&
        !((sm->flags & SOF_WB) && ((obj_info->static_wb[x].flags & WBF_ANIM_MASKS) == WBF_ANIM_LOCAL))) {
      if (frame <= sm->rot_track_min)
        normalized_time[i] = 0.0;
      else if (frame >= sm->rot_track_max)
        normalized_time[i] = 1.0;
      else {
        float total_time = sm->rot_track_max - sm->rot_track_min;
        normalized_time[i] = (frame - sm->rot_track_min) / total_time;
      }
    } else if ((sm->flags & SOF_WB) && !(sm->flags & SOF_TURRET)) {
      static float w_frame;
      ASSERT(x >= 0 && x < MAX_WBS_PER_OBJ);

      if (obj->dynamic_wb)
        w_frame = obj->dynamic_wb[x].wb_anim_frame;
      else
        w_frame = 0;

      if (w_frame <= sm->rot_track_min)
        normalized_time[i] = 0.0;
      else if (w_frame >= sm->rot_track_max)
        normalized_time[i] = 1.0;
      else {
        float total_time = sm->rot_track_max - sm->rot_track_min;
        normalized_time[i] = (w_frame - sm->rot_track_min) / total_time;
      }
    }
  }

  // Now, override angles of weapon bank turrets
  if (obj->dynamic_wb) {
    for (i = 0; i < pm->num_wbs; i++) {
      for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
        int sobj_index;

        sobj_index = pm->poly_wb[i].turret_index[j];
        normalized_time[sobj_index] = obj->dynamic_wb[i].norm_turret_angle[j];
      }
    }
  } else {
    for (i = 0; i < pm->num_wbs; i++) {
      for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
        int sobj_index;

        sobj_index = pm->poly_wb[i].turret_index[j];
        normalized_time[sobj_index] = 0;
      }
    }
  }
}

void SetNormalizedTimeObj(object *obj, float *normalized_time) {
  int i, j;

  if (Poly_models[obj->rtype.pobj_info.model_num].flags & PMF_TIMED) {
    SetNormalizedTimeObjTimed(obj, normalized_time);
    return;
  }

  float norm_anim_frame = GetNormalizedKeyframe(obj->rtype.pobj_info.model_num, obj->rtype.pobj_info.anim_frame);

  // Setup all the subobjects for the keyframe
  for (i = 0; i < Poly_models[obj->rtype.pobj_info.model_num].n_models; i++)
    normalized_time[i] = norm_anim_frame;

  // Currently, we are not handling player weapons in this manner
  // chrishack -- weapons with turrets -- COOL.
  if (obj->type == OBJ_PLAYER || obj->type == OBJ_WEAPON)
    return;

  ASSERT(obj->type == OBJ_POWERUP || obj->type == OBJ_ROBOT || obj->type == OBJ_BUILDING || obj->type == OBJ_DEBRIS ||
         obj->type == OBJ_DOOR || obj->type == OBJ_CLUTTER);

  // Now, override angles of weapon bank turrets
  for (i = 0; i < Poly_models[obj->rtype.pobj_info.model_num].num_wbs; i++) {
    for (j = 0; j < Poly_models[obj->rtype.pobj_info.model_num].poly_wb[i].num_turrets; j++) {
      int sobj_index;

      sobj_index = Poly_models[obj->rtype.pobj_info.model_num].poly_wb[i].turret_index[j];
      normalized_time[sobj_index] = obj->dynamic_wb[i].norm_turret_angle[j];
    }
  }
}

void SetNormalizedTimeAnimTimed(float frame, float *normalized_time, poly_model *pm) {
  int i, j;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  for (i = 0; i < pm->n_models; i++) {
    bsp_info *sm = &pm->submodel[i];

    if (frame <= sm->rot_track_min)
      normalized_time[i] = 0.0;
    else if (frame >= sm->rot_track_max)
      normalized_time[i] = 1.0;
    else {
      float total_time = sm->rot_track_max - sm->rot_track_min;
      normalized_time[i] = (frame - sm->rot_track_min) / total_time;
    }
  }

  // Now, override angles of weapon bank turrets
  for (i = 0; i < pm->num_wbs; i++) {
    for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
      int sobj_index;

      sobj_index = pm->poly_wb[i].turret_index[j];
      normalized_time[sobj_index] = 0.0;
    }
  }
}

// This is for non-rotated turrets or rotators
void SetNormalizedTimeAnim(float anim_frame, float *normalized_time, poly_model *pm) {
  int i, j;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  float norm_anim_frame = anim_frame / pm->max_keys;

  if (pm->flags & PMF_TIMED) {
    SetNormalizedTimeAnimTimed(anim_frame, normalized_time, pm);
    return;
  }

  // Setup all the subobjects for the keyframe
  for (i = 0; i < pm->n_models; i++)
    normalized_time[i] = norm_anim_frame;

  // Now, override angles of weapon bank turrets
  for (i = 0; i < pm->num_wbs; i++) {
    for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
      int sobj_index;

      sobj_index = pm->poly_wb[i].turret_index[j];
      normalized_time[sobj_index] = 0.0;
    }
  }
}

// Given a model pointer and an array of floats that go from 0..1, calculate the angles of each
// corresponding subobject
void SetModelAngles(poly_model *po, float *normalized_angles) {
  int i;

  ASSERT(!(po->flags & PMF_NOT_RESIDENT));

  if (po->num_key_angles > 0 && normalized_angles) {
    // get time per keyframe state
    float state_time = 1.0 / (po->num_key_angles - 1);
    float cur_state_time;
    int cur_state;
    float normal_state_time;

    for (i = 0; i < po->n_models; i++) {
      // Don't rotate turrets or auto-rotators or weapon battery submodels
      if (!(po->submodel[i].flags & (SOF_ROTATE | SOF_TURRET))) {

        // Find out which keyframe we're at

        cur_state = normalized_angles[i] / state_time;
        matrix dest_matrix;

        // Find out how far into that keyframe we are
        cur_state_time = normalized_angles[i] - ((float)cur_state * state_time);
        normal_state_time = cur_state_time / state_time;

        // Now do a parametric adjustment on the angles

        int cur_angle = 0;

        // If we're already at the high point of the interpolation then just
        // stuff some values
        if (cur_state == po->num_key_angles - 1) {
          vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &po->submodel[i].keyframe_matrix[po->num_key_angles - 1]);
          continue;
        }

        dest_matrix = po->submodel[i].keyframe_matrix[cur_state] +
                      ((po->submodel[i].keyframe_matrix[cur_state + 1] - po->submodel[i].keyframe_matrix[cur_state]) *
                       normal_state_time);

        vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &dest_matrix);
        // po->submodel[i].mod_matrix=dest_matrix;

      } else if (po->submodel[i].flags & SOF_ROTATE) {
        float flrot = Gametime * po->submodel[i].rps;
        int introt = flrot;

        float fdiff = flrot - introt;

        ASSERT(fdiff >= 0 && fdiff <= 1);

        // fdiff now equals 0 to 1
        matrix temp_matrix;
        vector temp_vec;
        if (po->new_style)
          temp_vec = po->submodel[i].keyframe_axis[1];
        else
          temp_vec = po->submodel[i].norm;

        BuildModelAngleMatrix(&temp_matrix, fdiff * 65535, &temp_vec);
        vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &temp_matrix);
      } else if (po->submodel[i].flags & SOF_TURRET) {
        matrix temp_matrix;
        if (po->new_style)
          BuildModelAngleMatrix(&temp_matrix, normalized_angles[i] * 65535, &po->submodel[i].keyframe_axis[1]);
        else
          BuildModelAngleMatrix(&temp_matrix, normalized_angles[i] * 65535, &po->submodel[i].norm);

        vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &temp_matrix);
      }
    }
  } else {
    for (i = 0; i < po->n_models; i++) {
      if (po->submodel[i].flags & SOF_ROTATE) {
        float flrot = Gametime * po->submodel[i].rps;
        int introt = flrot;

        float fdiff = flrot - introt;

        ASSERT(fdiff >= 0 && fdiff <= 1);

        // fdiff now equals 0 to 1
        matrix temp_matrix;
        vector temp_vec;
        if (po->new_style)
          temp_vec = po->submodel[i].keyframe_axis[1];
        else
          temp_vec = po->submodel[i].norm;

        BuildModelAngleMatrix(&temp_matrix, fdiff * 65535, &temp_vec);
        vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &temp_matrix);
      } else if (po->submodel[i].flags & SOF_TURRET) {
        // We need to find where in this rotation is relative to gametime
        float flrot = Gametime;
        int introt = flrot;

        float fdiff = flrot - introt;

        // fdiff now equals 0 to 1
        matrix temp_matrix;
        if (po->new_style)
          BuildModelAngleMatrix(&temp_matrix, fdiff * 65535, &po->submodel[i].keyframe_axis[0]);
        else
          BuildModelAngleMatrix(&temp_matrix, fdiff * 65535, &po->submodel[i].norm);

        vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &temp_matrix);
      } else {
        po->submodel[i].angs.h = 0;
        po->submodel[i].angs.p = 0;
        po->submodel[i].angs.h = 0;
      }
    }
  }
}

// Given a model pointer and an array of floats that go from 0..1, calculate the interpolated
// position of each corresponding subobject
void SetModelInterpPos(poly_model *po, float *normalized_pos) {
  int i;

  ASSERT(!(po->flags & PMF_NOT_RESIDENT));

  if (normalized_pos && po->num_key_pos > 0) {
    for (i = 0; i < po->n_models; i++) {
      bsp_info *sm = &po->submodel[i];

      // get time per keyframe state
      float state_time = 1.0 / (po->num_key_pos - 1);
      float cur_state_time;
      int cur_state;
      float normal_state_time;

      // Find out which keyframe we're at
      cur_state = normalized_pos[i] / state_time;

      // Find out how far into that keyframe we are
      cur_state_time = normalized_pos[i] - ((float)cur_state * state_time);
      normal_state_time = cur_state_time / state_time;

      // Now do a parametric adjustment on the positions

      vector total_delta_pos = {0, 0, 0};
      vector subpos;
      vector final_pos;

      // If we're already at the high point of the interpolation then just
      // stuff some values
      if (cur_state == sm->num_key_pos - 1) {
        po->submodel[i].mod_pos = po->submodel[i].keyframe_pos[po->num_key_pos - 1];
        continue;
      }

      if (cur_state == 0)
        po->submodel[i].mod_pos = normal_state_time * po->submodel[i].keyframe_pos[1];
      else {
        vm_SubVectors(&subpos, &po->submodel[i].keyframe_pos[cur_state + 1], &po->submodel[i].keyframe_pos[cur_state]);
        final_pos = po->submodel[i].keyframe_pos[cur_state] + (subpos * normal_state_time);
        po->submodel[i].mod_pos = final_pos;
      }
    }
  } else {
    for (i = 0; i < po->n_models; i++) {
      po->submodel[i].mod_pos.x = 0;
      po->submodel[i].mod_pos.y = 0;
      po->submodel[i].mod_pos.z = 0;
    }
  }
}

// Sets the effect used by a polymodel
void SetPolymodelEffect(polymodel_effect *poly_effect) { Polymodel_effect = *poly_effect; }

// Given a model pointer and an array of floats that go from 0..1, calculate the interpolated
// position/angle of each corresponding subobject
void SetModelAnglesAndPosTimed(poly_model *po, float *normalized_time, uint32_t subobj_flags) {
  int i;

  ASSERT(!(po->flags & PMF_NOT_RESIDENT));

  if (normalized_time) {
    // get time per keyframe state

    for (i = 0; i < po->n_models; i++) {
      bsp_info *sm = &po->submodel[i];
      int int_tick, current_frame, total_ticks;
      float normal_state_time, current_tick;

      if (!(subobj_flags & (1 << i)))
        continue;

      if (sm->num_key_pos <= 1) {
        vm_MakeZero(&sm->mod_pos);
        goto do_angles;
      }

      if (normalized_time[i] == 1.0) {
        sm->mod_pos = sm->keyframe_pos[sm->num_key_pos - 1];
        goto do_angles;
      }

      // Find out which keyframe we're at
      total_ticks = sm->pos_track_max - sm->pos_track_min;
      current_tick = (normalized_time[i] * total_ticks) + sm->pos_track_min;
      int_tick = current_tick;
      current_frame = sm->tick_pos_remap[int_tick - sm->pos_track_min];

      ASSERT(current_frame >= 0 && current_frame <= sm->num_key_pos - 1);

      if (current_frame == sm->num_key_pos - 1) {
        sm->mod_pos = sm->keyframe_pos[sm->num_key_pos - 1];
        goto do_angles;
      } else {
        int ticks_between_frames = sm->pos_start_time[current_frame + 1] - sm->pos_start_time[current_frame];
        float this_tick = current_tick - sm->pos_start_time[current_frame];
        normal_state_time = (float)this_tick / (float)ticks_between_frames;

        vector subpos;
        vm_SubVectors(&subpos, &sm->keyframe_pos[current_frame + 1], &sm->keyframe_pos[current_frame]);
        sm->mod_pos = sm->keyframe_pos[current_frame] + (subpos * normal_state_time);
      }

    // Now do angle stuff here
    do_angles:
      // Don't rotate turrets or auto-rotators
      if (!(sm->flags & (SOF_TURRET | SOF_ROTATE))) {
        if (sm->num_key_angles <= 1) {
          sm->angs.p = 0;
          sm->angs.h = 0;
          sm->angs.b = 0;
          continue;
        }

        if (normalized_time[i] == 1.0) {
          vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &po->submodel[i].keyframe_matrix[sm->num_key_angles - 1]);
          continue;
        }

        // Find out which keyframe we're at
        total_ticks = sm->rot_track_max - sm->rot_track_min;
        current_tick = (normalized_time[i] * total_ticks) + sm->rot_track_min;
        int_tick = current_tick;
        current_frame = sm->tick_ang_remap[int_tick - sm->rot_track_min];

        ASSERT(current_frame >= 0 && current_frame <= sm->num_key_angles - 1);

        if (current_frame == sm->num_key_angles - 1) {
          vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &po->submodel[i].keyframe_matrix[sm->num_key_angles - 1]);
          continue;
        } else {
          int ticks_between_frames = sm->rot_start_time[current_frame + 1] - sm->rot_start_time[current_frame];
          float this_tick = current_tick - sm->rot_start_time[current_frame];
          normal_state_time = (float)this_tick / (float)ticks_between_frames;

          // Now do a parametric adjustment on the angles

          matrix dest_matrix =
              sm->keyframe_matrix[current_frame] +
              ((sm->keyframe_matrix[current_frame + 1] - sm->keyframe_matrix[current_frame]) * normal_state_time);

          vm_ExtractAnglesFromMatrix(&sm->angs, &dest_matrix);
        }

      } else {
        // Adjust special subobjects
        if (po->submodel[i].flags & SOF_ROTATE) {
          float flrot = Gametime * po->submodel[i].rps;
          int introt = flrot;

          float fdiff = flrot - introt;

          ASSERT(fdiff >= 0 && fdiff <= 1);

          // fdiff now equals 0 to 1
          matrix temp_matrix;
          vector temp_vec;
          if (po->new_style)
            temp_vec = po->submodel[i].keyframe_axis[1];
          else
            temp_vec = po->submodel[i].norm;

          BuildModelAngleMatrix(&temp_matrix, fdiff * 65535, &temp_vec);
          vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &temp_matrix);
        } else if (po->submodel[i].flags & SOF_TURRET) {
          matrix temp_matrix;
          if (po->new_style)
            BuildModelAngleMatrix(&temp_matrix, normalized_time[i] * 65535, &po->submodel[i].keyframe_axis[1]);
          else
            BuildModelAngleMatrix(&temp_matrix, normalized_time[i] * 65535, &po->submodel[i].norm);

          vm_ExtractAnglesFromMatrix(&po->submodel[i].angs, &temp_matrix);
        }
      }
    }

  } else {
    for (i = 0; i < po->n_models; i++) {
      po->submodel[i].mod_pos.x = 0;
      po->submodel[i].mod_pos.y = 0;
      po->submodel[i].mod_pos.z = 0;

      po->submodel[i].angs.p = 0;
      po->submodel[i].angs.h = 0;
      po->submodel[i].angs.b = 0;
    }
  }
}

// Sets the position and rotation of a polymodel.  Used for rendering and collision detection
void SetModelAnglesAndPos(poly_model *po, float *normalized_time, uint32_t subobj_flags) {
  ASSERT(!(po->flags & PMF_NOT_RESIDENT));

  if (po->flags & PMF_TIMED) {
    SetModelAnglesAndPosTimed(po, normalized_time, subobj_flags);
    return;
  } else {
    SetModelAngles(po, normalized_time);
    SetModelInterpPos(po, normalized_time);
  }
}

static vector Instance_fog_plane_stack[MAX_SUBOBJECTS];
static vector Instance_fog_portal_vert_stack[MAX_SUBOBJECTS];
static vector Instance_light_stack[MAX_SUBOBJECTS];
static vector Instance_specular_pos[MAX_SUBOBJECTS];
static vector Instance_bump_pos[MAX_SUBOBJECTS];

static int Instance_light_cnt = 0;

void StartLightInstance(vector *pos, matrix *orient) {
  int gouraud = 0, specular = 0, fogged = 0, bumped = 0;

  if (Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD)
    gouraud = 1;
  if (Polymodel_use_effect && Polymodel_effect.type & PEF_FOGGED_MODEL)
    fogged = 1;
  if (Polymodel_use_effect && Polymodel_effect.type & (PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES))
    specular = 1;
  if (Polymodel_use_effect && (Polymodel_effect.type & PEF_BUMPMAPPED))
    bumped = 1;

  if (gouraud)
    Instance_light_stack[Instance_light_cnt] = *Polymodel_light_direction;
  if (fogged) {
    Instance_fog_plane_stack[Instance_light_cnt] = Polymodel_fog_plane;
    Instance_fog_portal_vert_stack[Instance_light_cnt] = Polymodel_fog_portal_vert;
  }

  if (specular)
    Instance_specular_pos[Instance_light_cnt] = Polymodel_specular_pos;

  if (bumped)
    Instance_bump_pos[Instance_light_cnt] = Polymodel_bump_pos;

  Instance_light_cnt++;

  vector temp_vec;

  if (gouraud) {
    vm_MatrixMulVector(&temp_vec, Polymodel_light_direction, orient);
    *Polymodel_light_direction = temp_vec;
  }
  if (fogged) {
    vector tempv = Polymodel_fog_portal_vert - *pos;
    vm_MatrixMulVector(&temp_vec, &tempv, orient);
    Polymodel_fog_portal_vert = temp_vec;

    vm_MatrixMulVector(&temp_vec, &Polymodel_fog_plane, orient);
    Polymodel_fog_plane = temp_vec;
  }
  if (specular) {
    vector tempv = Polymodel_specular_pos - *pos;
    vm_MatrixMulVector(&temp_vec, &tempv, orient);
    Polymodel_specular_pos = temp_vec;
  }

  if (bumped) {
    vector tempv = Polymodel_bump_pos - *pos;
    vm_MatrixMulVector(&temp_vec, &tempv, orient);
    Polymodel_bump_pos = temp_vec;
  }
}
void DoneLightInstance() {
  ASSERT(Instance_light_cnt != 0);
  Instance_light_cnt--;

  if (Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD)
    *Polymodel_light_direction = Instance_light_stack[Instance_light_cnt];

  if (Polymodel_use_effect && Polymodel_effect.type & PEF_FOGGED_MODEL) {
    Polymodel_fog_plane = Instance_fog_plane_stack[Instance_light_cnt];
    Polymodel_fog_portal_vert = Instance_fog_portal_vert_stack[Instance_light_cnt];
  }

  if (Polymodel_use_effect && Polymodel_effect.type & (PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES))
    Polymodel_specular_pos = Instance_specular_pos[Instance_light_cnt];

  if (Polymodel_use_effect && (Polymodel_effect.type & PEF_BUMPMAPPED))
    Polymodel_bump_pos = Instance_bump_pos[Instance_light_cnt];
}

// Draws a polygon model to the viewport
// Normalized_time is an array of floats from 0 to 1 that represent how far into
// an animation state we are

// This is the static light version
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags, float r, float g,
                      float b, uint32_t f_render_sub, uint8_t use_effect, uint8_t overlay) {
  poly_model *po;

  ASSERT(Poly_models[model_num].used);
  ASSERT(!(Poly_models[model_num].flags & PMF_NOT_RESIDENT));

  GetPolymodelPointer(model_num);

  Polymodel_use_effect = use_effect;
  Polymodel_light_type = POLYMODEL_LIGHTING_STATIC;
  Polylighting_static_red = r;
  Polylighting_static_green = g;
  Polylighting_static_blue = b;

  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);

  po = &Poly_models[model_num];

  g3_StartInstanceMatrix(pos, orient);

  if (Polymodel_use_effect && Polymodel_effect.type & PEF_FOGGED_MODEL) {
    Polymodel_fog_plane = Polymodel_effect.fog_plane;
    Polymodel_fog_portal_vert = Polymodel_effect.fog_portal_vert;
  }

  if (Polymodel_use_effect && Polymodel_effect.type & (PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES))
    Polymodel_specular_pos = Polymodel_effect.spec_light_pos;

  if (Polymodel_use_effect && (Polymodel_effect.type & PEF_BUMPMAPPED))
    Polymodel_bump_pos = Polymodel_effect.bump_light_pos;

  StartLightInstance(pos, orient);

  SetModelAnglesAndPos(po, normalized_time, f_render_sub);

  if (f_render_sub == 0xFFFFFFFF || overlay) // draw entire object
  {
    if (po->new_style) {
      RenderPolygonModel(po, f_render_sub);
    }
  } else {
    ASSERT(po->new_style == 1);

    rend_SetAlphaType(ATF_CONSTANT + ATF_VERTEX);

    int i;
    for (i = 0; i < po->n_models; i++) {
      if ((f_render_sub & (1 << i))) {
        if (i != 0) {
          vector ofs;
          vector save_offset;

          // if submodel, rotate around its center point, not pivot point

          ofs = (po->submodel[i].min + po->submodel[i].max) / 2;
          save_offset = po->submodel[i].offset;
          vm_MakeZero(&po->submodel[i].offset);
          vm_MakeZero(&po->submodel[i].mod_pos);
          memset(&po->submodel[i].angs, 0, sizeof(angvec));
          ofs *= -1;

          po->submodel[i].offset = ofs;
          RenderSubmodel(po, &po->submodel[i], f_render_sub);

          po->submodel[i].offset = save_offset;
        } else
          RenderSubmodel(po, &po->submodel[i], f_render_sub);
      }
    }
  }

  DoneLightInstance();
  g3_DoneInstance();
}

// This draws a gouraud shaded version
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags, vector *lightdir,
                      float r, float g, float b, uint32_t f_render_sub, uint8_t use_effect, uint8_t overlay) {
  poly_model *po;
  vector light_vec = *lightdir;

  Polymodel_use_effect = use_effect;

  ASSERT(Poly_models[model_num].used);
  ASSERT(!(Poly_models[model_num].flags & PMF_NOT_RESIDENT));

  GetPolymodelPointer(model_num);

  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);

  Polymodel_light_type = POLYMODEL_LIGHTING_GOURAUD;
  Polylighting_static_red = r;
  Polylighting_static_green = g;
  Polylighting_static_blue = b;

  Polymodel_light_direction = &light_vec;

  if (Polymodel_use_effect && Polymodel_effect.type & PEF_FOGGED_MODEL) {
    Polymodel_fog_plane = Polymodel_effect.fog_plane;
    Polymodel_fog_portal_vert = Polymodel_effect.fog_portal_vert;
  }

  if (Polymodel_use_effect && Polymodel_effect.type & (PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES))
    Polymodel_specular_pos = Polymodel_effect.spec_light_pos;

  if (Polymodel_use_effect && (Polymodel_effect.type & PEF_BUMPMAPPED))
    Polymodel_bump_pos = Polymodel_effect.bump_light_pos;

  g3_StartInstanceMatrix(pos, orient);
  StartLightInstance(pos, orient);

  po = &Poly_models[model_num];
  SetModelAnglesAndPos(po, normalized_time, f_render_sub);

  if (f_render_sub == 0xFFFFFFFF || overlay) // draw entire object
  {
    if (po->new_style)
      RenderPolygonModel(po, f_render_sub);
  } else {
    ASSERT(po->new_style == 1);

    rend_SetAlphaType(ATF_CONSTANT + ATF_VERTEX);

    int i;
    for (i = 0; i < po->n_models; i++) {
      if ((f_render_sub & (1 << i))) {
        if (i != 0) {
          vector ofs;
          vector save_offset;

          // if submodel, rotate around its center point, not pivot point

          ofs = (po->submodel[i].min + po->submodel[i].max) / 2;
          save_offset = po->submodel[i].offset;
          vm_MakeZero(&po->submodel[i].offset);
          vm_MakeZero(&po->submodel[i].mod_pos);
          memset(&po->submodel[i].angs, 0, sizeof(angvec));
          ofs *= -1;

          po->submodel[i].offset = ofs;
          RenderSubmodel(po, &po->submodel[i], f_render_sub);

          po->submodel[i].offset = save_offset;
        } else
          RenderSubmodel(po, &po->submodel[i], f_render_sub);
      }
    }
  }

  g3_DoneInstance();
  DoneLightInstance();
}

// This draws a lightmap shaded version
void DrawPolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, int flags,
                      lightmap_object *lm_object, uint32_t f_render_sub, uint8_t use_effect, uint8_t overlay) {
  poly_model *po;

  ASSERT(Poly_models[model_num].used);
  ASSERT(!(Poly_models[model_num].flags & PMF_NOT_RESIDENT));

  GetPolymodelPointer(model_num);

  Polymodel_use_effect = use_effect;

  rend_SetLighting(LS_NONE);
  Polymodel_light_type = POLYMODEL_LIGHTING_LIGHTMAP;
  Polylighting_lightmap_object = lm_object;

  if (Polymodel_use_effect && Polymodel_effect.type & PEF_FOGGED_MODEL) {
    Polymodel_fog_plane = Polymodel_effect.fog_plane;
    Polymodel_fog_portal_vert = Polymodel_effect.fog_portal_vert;
  }

  if (Polymodel_use_effect && Polymodel_effect.type & (PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES))
    Polymodel_specular_pos = Polymodel_effect.spec_light_pos;

  if (Polymodel_use_effect && (Polymodel_effect.type & PEF_BUMPMAPPED))
    Polymodel_bump_pos = Polymodel_effect.bump_light_pos;

  g3_StartInstanceMatrix(pos, orient);
  StartLightInstance(pos, orient);

  po = &Poly_models[model_num];
  SetModelAnglesAndPos(po, normalized_time, f_render_sub);

  if (f_render_sub == 0xFFFFFFFF || overlay) // draw entire object
  {
    if (po->new_style)
      RenderPolygonModel(po, f_render_sub);
  } else {
    ASSERT(po->new_style == 1);

    rend_SetAlphaType(ATF_CONSTANT + ATF_VERTEX);

    int i;
    for (i = 0; i < po->n_models; i++) {
      if ((f_render_sub & (1 << i))) {
        if (i != 0) {
          vector ofs;
          vector save_offset;

          // if submodel, rotate around its center point, not pivot point

          ofs = (po->submodel[i].min + po->submodel[i].max) / 2;
          save_offset = po->submodel[i].offset;
          vm_MakeZero(&po->submodel[i].offset);
          vm_MakeZero(&po->submodel[i].mod_pos);
          memset(&po->submodel[i].angs, 0, sizeof(angvec));
          ofs *= -1;

          po->submodel[i].offset = ofs;
          RenderSubmodel(po, &po->submodel[i], f_render_sub);

          po->submodel[i].offset = save_offset;
        } else
          RenderSubmodel(po, &po->submodel[i], f_render_sub);
      }
    }
  }

  g3_DoneInstance();
  DoneLightInstance();
  rend_SetOverlayType(OT_NONE);
}

void FreeAllModels() {
  for (int i = 0; i < MAX_POLY_MODELS; i++) {
    if (Poly_models[i].used > 0) {
      Poly_models[i].used = 1;

      FreePolyModel(i);
    }
  }
}

// Inits our models array and loads our ship pof
int InitModels() {
  for (int i = 0; i < MAX_POLY_MODELS; i++) {
    memset(&Poly_models[i], 0, sizeof(poly_model));
    Poly_models[i].used = 0;
  }

  atexit(FreeAllModels);

  return 1;
}

// MTS: used only in this file.
// Given an actual keyframe number, returns the normalized (0 to 1) position of that
// keyframe
// Handle is an index into the Poly_models array
float GetNormalizedKeyframe(int handle, float num) {
  poly_model *pm = &Poly_models[handle];

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  ASSERT(pm->used);
  ASSERT(num >= 0 && num <= pm->max_keys);

  return ((num / (float)pm->max_keys));
}

// Goes through all poly models and gets all missing textures
void RemapPolyModels() {
  int i;

  for (i = 0; i < MAX_POLY_MODELS; i++) {
    int remap = 0;

    if (Poly_models[i].used == 0 || (Poly_models[i].flags & PMF_NOT_RESIDENT))
      continue;

    for (int t = 0; t < Poly_models[i].n_textures; t++)
      if (Poly_models[i].textures[t] == 0) // is there a bad texture?
        remap = 1;

    if (remap == 1) {
      // remap the damn textures
      mprintf(0, "Remapping model textures for model %s.\n", Poly_models[i].name);
      ReloadModelTextures(i);
    }
  }
}

// MTS: not used?
// Returns the total number of faces in a model
int CountFacesInPolymodel(poly_model *pm) {
  int i;
  ASSERT(pm->used > 0);
  int count = 0;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  for (i = 0; i < pm->n_models; i++) {
    if (IsNonRenderableSubmodel(pm, i))
      continue;

    count += pm->submodel[i].num_faces;
  }

  return count;
}

// Given an object, a submodel, and a vertex number, calculates the world position
// of that point
void GetPolyModelPointInWorld(vector *dest, poly_model *pm, vector *wpos, matrix *orient, int subnum, vector *pos,
                              vector *norm) {
  bsp_info *sm = &pm->submodel[subnum];
  float normalized_time[MAX_SUBOBJECTS];
  int i;

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  if (!pm->new_style)
    return;

  for (i = 0; i < MAX_SUBOBJECTS; i++)
    normalized_time[i] = 0.0;

  SetModelAnglesAndPos(pm, normalized_time);

  vector pnt = *pos;
  int mn = subnum;
  vector cur_norm;

  if (norm != NULL)
    cur_norm = *norm;

  matrix m;

  // Instance up the tree for this gun
  while (mn != -1) {
    vector tpnt;

    vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
    vm_TransposeMatrix(&m);

    tpnt = pnt * m;

    if (norm != NULL)
      cur_norm = cur_norm * m;

    pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

    mn = pm->submodel[mn].parent;
  }

  // now instance for the entire object
  m = *orient;
  vm_TransposeMatrix(&m);

  if (norm != NULL)
    *norm = (cur_norm * m);
  *dest = pnt * m;
  *dest += (*wpos);
}

void GetPolyModelPointInWorld(vector *dest, poly_model *pm, vector *wpos, matrix *orient, int subnum,
                              float *normalized_time, vector *pos, vector *norm) {
  bsp_info *sm = &pm->submodel[subnum];

  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  if (!pm->new_style)
    return;

  SetModelAnglesAndPos(pm, normalized_time);

  vector pnt = *pos;
  int mn = subnum;
  vector cur_norm;

  if (norm != NULL)
    cur_norm = *norm;

  matrix m;

  // Instance up the tree for this gun
  while (mn != -1) {
    vector tpnt;

    vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
    vm_TransposeMatrix(&m);

    tpnt = pnt * m;

    if (norm != NULL)
      cur_norm = cur_norm * m;

    pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

    mn = pm->submodel[mn].parent;
  }

  // now instance for the entire object
  m = *orient;
  vm_TransposeMatrix(&m);

  if (norm != NULL)
    *norm = (cur_norm * m);
  *dest = pnt * m;
  *dest += (*wpos);
}

// Returns 1 if this submodel shouldn't be rendered
int IsNonRenderableSubmodel(poly_model *pm, int submodelnum) {
  ASSERT(pm->used);
  ASSERT(!(pm->flags & PMF_NOT_RESIDENT));

  if ((pm->submodel[submodelnum].flags & SOF_FRONTFACE) || (pm->submodel[submodelnum].flags & SOF_SHELL))
    return 1;

  if (pm->submodel[submodelnum].num_faces == 0)
    return 1;

  return 0;
}
