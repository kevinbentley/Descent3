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

 * $Logfile: /DescentIII/Main/terrainrender.cpp $
 * $Revision: 242 $
 * $Date: 9/06/01 12:15p $
 * $Author: Matt $
 *
 * Terrain rendering code
 *
 * $Log: /DescentIII/Main/terrainrender.cpp $
 *
 * 242   9/06/01 12:15p Matt
 * Added bounds checking for postrender list.
 *
 * 241   4/19/00 5:30p Matt
 * From Duane for 1.4
 * Mac sky changes
 *
 * 240   3/20/00 12:21p Matt
 * Merge of Duane's post-1.3 changes.
 * Caching optimization.
 *
 * 239   10/21/99 9:29p Jeff
 * B.A. Macintosh code merge
 *
 * 238   10/21/99 5:27p Gwar
 * fixed a pesky crash
 *
 * 237   10/21/99 4:33p Gwar
 * objects weren't displaying in NEWEDITOR release build
 *
 * 236   10/12/99 10:55a Gwar
 * added DrawTerrainOutline for NEWEDITOR
 *
 * 235   10/12/99 10:19a Gwar
 * adding terrain support to NEWEDITOR
 *
 * 234   7/28/99 3:40p Kevin
 * Macintosh!
 *
 * 233   5/13/99 3:42p Ardussi
 * changes for compiling on the Mac
 *
 * 232   5/07/99 7:22p Jason
 * changes for cards with low videomemory
 *
 * 230   5/05/99 6:09p 3dsmax
 * checked in dumb hack for now
 *
 * 229   4/27/99 3:36p Jason
 * fixed terrain occlusion bug
 *
 * 228   4/23/99 7:18p Jason
 * fixed some multiplayer issues with observer mode
 *
 * 227   4/22/99 12:05p Jason
 * fixed some more direct3d issues
 *
 * 226   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 225   4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 224   4/16/99 11:33p Jeff
 * ifdef out some terrain triangle draw code, needs software renderer (for
 * linux)
 *
 * 223   4/16/99 12:37a Matt
 * Made Windows & Linux versions use the same qsort calls.
 *
 * 222   4/15/99 1:43a Jeff
 * changes for linux compile
 *
 * 221   4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 220   4/03/99 2:20p Jason
 * added better heat damage effect
 *
 * 219   4/01/99 1:19p Jason
 * draw band even with textured sky
 *
 * 218   3/31/99 11:41a Jason
 * added support for attached thick lightning
 *
 * 217   3/01/99 2:39p Jason
 * fixed star and halo rendering
 *
 * 216   2/26/99 3:26p Jason
 * made satellites clip properly
 *
 * 215   2/19/99 4:26p Jason
 * more work on Katmai support
 *
 * 214   2/19/99 12:04p Jason
 * took out sky band
 *
 * 213   2/17/99 1:59p Jason
 * fixed some postrender issues
 *
 * 212   2/17/99 1:05p Jason
 * revamped object/face/terrain selection code
 *
 * 211   2/16/99 12:39a Matt
 * Removed render_objs from terrain_segment and created parallel array
 *
 * 210   2/09/99 12:10p Jason
 * rewriting indoor engine
 *
 * 209   2/08/99 5:07p Jason
 * orthogonalize sky rotation matrix
 *
 * 208   2/05/99 3:37p Jason
 * added/fixed features for the designers
 *
 * 207   2/04/99 12:17p Kevin
 * Small fix for release builds
 *
 * 206   2/04/99 12:13p Jason
 * fixed release array
 *
 * 205   2/01/99 10:51a Jason
 * fixed outlines on terrain
 *
 * 204   1/29/99 11:29a Jason
 * added misc bug fixes/features
 *
 * 203   1/24/99 5:43p Jason
 * changes for terrain tiling
 *
 * 202   1/24/99 2:11a Jason
 * fixed dumb texture UV problem
 *
 * 201   1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 200   1/21/99 11:17a Jason
 * fixed terrain rendering problem at the edges of the map
 *
 * 199   1/20/99 3:50p Jason
 * fixed automap problem
 *
 * 197   1/20/99 2:48p Jason
 * more terrain speedups
 *
 * 196   1/20/99 1:40p Jason
 * terrain speedups
 *
 * 195   1/20/99 10:50a Jason
 * added new terrain
 *
 * 194   12/29/98 6:12p Jason
 * stupid fix for level designers
 *
 * 193   12/17/98 2:18p Jason
 * fixed mip mapping problem
 *
 * 192   12/11/98 2:43p Jason
 * tweaked snow
 *
 * 191   12/09/98 1:09p Jason
 * second draft of automap
 *
 * 190   11/18/98 5:10p Jason
 * fixed z buffer snow
 *
 * 189   11/18/98 4:30p Jason
 * added some functionality to terrain fog
 *
 * 188   11/18/98 2:54p Jason
 * added snow effect
 *
 * 187   11/06/98 5:42p Jason
 * took out terrain casting
 *
 * 186   10/22/98 4:02p Jason
 * made lightmaps draw even in nolightmap mode
 *
 * 185   10/22/98 10:21a Jason
 * fixed wrap/clamp problem
 *
 * 184   10/21/98 9:28p Jason
 * Made no lightmaps work globally
 *
 * 183   10/21/98 8:40p Jason
 * testing for Mark
 *
 * 182   10/21/98 6:54p Jason
 * changes for shitty direct3d cards
 *
 * 181   10/19/98 6:30p Jeff
 * changes made for detail variables.  Put in preset values.  Preset
 * options.  Removed terrain_cast from detail.  Put new callbacks in
 * UIListBox and UISlider
 *
 * 180   10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 179   10/07/98 5:17p Jason
 * fixed lighting on the terrain
 *
 * 178   10/03/98 11:21p Matt
 * Added system to seperately control outline mode for mine, terrain, sky,
 * & objects
 *
 * 177   10/02/98 5:31p Jason
 * tweaks for statelimited stuff
 *
 * 176   10/02/98 12:26p Jason
 * fixed fogging of indoor rooms
 *
 * 175   9/29/98 3:00p Jason
 * fixed state limited bug with lightmaps
 *
 * 174   9/29/98 2:02p Jason
 * fixed external rooms rendering even when they shouldn't
 *
 * 173   9/25/98 9:25p Jason
 * did some graphics optimizations
 *
 * 172   9/25/98 11:58a Jason
 * various rendering optimizations
 *
 * 171   9/24/98 12:57p Jason
 * more state limited optimizations
 *
 * 170   9/23/98 11:16a Jason
 * fixed some lightmap problems
 *
 * 169   9/22/98 11:46a Jason
 * made terrain lightmap rendering more state friendly
 *
 * 168   9/17/98 6:51p Jason
 * fixed streaking vectors
 *
 * 167   9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 166   9/11/98 5:09p Jason
 * made terrain state-change friendly
 *
 * 165   8/25/98 6:34p Craig
 * Include terrain outline func in non-editor debug versions.
 *
 * 164   8/25/98 1:50p Jason
 * made outlines draw in ndebug mode, instead of editor mode
 *
 * 163   8/19/98 5:48p Jason
 * made robots have at least a mininum amount of lighting
 *
 * 162   8/19/98 2:19p Jeff
 * moved detail globals to a struct
 *
 * 161   8/17/98 5:27p Jason
 * fixed dynamic lighting for objects above the terrain ceiling
 *
 * 160   8/14/98 4:00p Jason
 * added specular objects outside
 *
 * 159   8/06/98 11:00a Jason
 * added blurred stars
 *
 * 158   8/04/98 2:55p Jason
 * added motion blurred stars
 *
 * 157   7/24/98 4:49p Jason
 * made terrain casting work again
 *
 * 156   7/20/98 12:04p Jason
 * added per level satellite lighting
 *
 * 155   6/24/98 7:03p Jason
 * fixed omega and external room sorting problem
 *
 * 154   6/24/98 3:56p Jason
 * added code for new omega cannon
 *
 * 153   6/16/98 2:56p Jason
 * fixed terrain occlusion bug with objects
 *
 * 152   6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 151   6/12/98 5:15p Jason
 * added dynamic volume light system
 *
 * 150   6/10/98 12:23p Jason
 * added new skies
 *
 * 149   6/04/98 6:45p Jason
 * made objects use the terrain occlusion system
 *
 * 148   5/26/98 6:54p Jason
 * viseffect optimizations
 *
 * 147   5/25/98 3:46p Jason
 * added better light glows
 *
 * 146   5/14/98 2:17p Jason
 * more changes to be memory friendly
 *
 * 145   5/14/98 12:56p Jason
 * changes to help lower memory usage
 *
 * 144   5/11/98 7:03p Jason
 * fixed terrain bug with microwave effect
 *
 * 143   5/06/98 6:18p Jason
 * improved terrain raycasting
 *
 * 142   5/05/98 6:27p Chris
 * Added BBoxs and spheres to external rooms (in mode 2)
 *
 * 141   5/05/98 5:28p Jason
 * more terrain speedups
 *
 * 140   5/05/98 4:38p Jason
 * added raycasting test stuff
 *
 * 139   5/04/98 8:04p Jason
 * made wireframe sky view
 *
 * 138   5/01/98 5:46p Jason
 * fixed external room popping bug
 *
 * 137   5/01/98 3:51p Jason
 * sped up terrain rendering by precaching all megacell lod bitmaps
 *
 * 136   5/01/98 12:42p Jason
 * slight framerate enhancement
 *
 * 135   4/30/98 6:45p Jason
 * more changes for weather
 *
 * 134   4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 133   4/29/98 3:27p Jason
 * added weather engine
 *
 * 132   4/29/98 11:38a Jason
 * added some weather effects (first pass)
 *
 * 131   4/23/98 12:21p Jason
 * fixed rendering bug if satellite values were out of range
 *
 * 130   4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 129   4/17/98 3:57p Jason
 * added microwave effect
 *
 * 128   4/10/98 6:04p Jason
 * fixed some lighting issues
 *
 * 127   4/03/98 1:36p Jason
 * saved some memory
 *
 * 126   4/01/98 11:26a Jeff
 * Added an editor bool to skip Terrain object rendering
 *
 * 125   3/26/98 10:54a Jason
 * tweaked some stuff for size independant terrain
 *
 * 124   3/17/98 5:02p Jason
 * sped up rendering the terrain from the mine by a large amount
 *
 * 123   3/09/98 4:54p Jason
 * don't render objects that can't been seen through a portal
 *
 * 122   3/06/98 2:33p Jason
 * fixed potential memory overwrite bug
 *
 * 121   3/06/98 2:17p Jason
 * sped up terrain by making lod'd triangles quads
 *
 * 120   2/25/98 2:05p Jason
 * did FOV and object visibility changes
 *
 * 119   2/17/98 2:22p Jason
 * fixed some potential z sorting problems
 *
 * 118   2/12/98 1:32p Jason
 * got mipmapping working
 *
 * 117   2/10/98 5:42p Jason
 * fixed object rendering with RT_ROOM type
 *
 * 116   2/10/98 10:28a Matt
 * Got rid of compile warning
 *
 * 115   2/09/98 7:31p Matt
 * Changed object rendering code to not look at Viewer_object to determine
 * whether to render the object
 *
 * 114   2/05/98 6:02p Jason
 * fixed bug my previous rev introduced
 *
 * 113   2/05/98 4:41p Jason
 * fixed off by one bug
 *
 * 112   2/05/98 12:35p Jason
 * fixed screen clearing problem with gouraud sky
 *
 * 111   2/04/98 6:58p Matt
 * Fixed viseffect rendering on terrain.
 *
 * 110   2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 109   2/02/98 3:19p Jason
 * made stars draw with different colors
 *
 * 108   1/30/98 12:12p Jason
 * fixed LOD bug.  This gives us twice the framerate in hilly areas!!!
 *
 * 107   1/29/98 5:50p Matt
 * Changed old camera object type to be viewer object (for editor), and
 * now camera objects will just be for game cameras.
 *
 * 106   1/28/98 4:06p Jason
 * made stars not darken so much on blur
 *
 * 105   1/28/98 3:55p Jason
 * added stars after the textured sky
 *
 * 104   1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 103   1/20/98 2:17p Jason
 * fixed weird sorting problem with objects and viseffects
 *
 * 102   1/20/98 12:10p Jason
 * implemented vis effect system
 *
 * 101   1/16/98 8:06p Jason
 * added selectable halos and atmosphere blends to satellites
 *
 * 100   1/16/98 3:05p Jason
 * fixed LOD cracking at terrain edges
 *
 * 99    1/16/98 2:47p Jason
 * tweaked some things for speed reasons
 *
 * 98    1/16/98 1:04p Jason
 * don't do update environment
 *
 * 97    1/15/98 6:32p Jason
 * added v wrapping for sky textures
 *
 * 96    1/15/98 12:42p Jason
 * big fix for terrain sky rendering
 *
 * 95    1/12/98 3:34p Jason
 * sped up indoor rendering by clipping faces against portals
 *
 * 94    1/07/98 4:19p Jason
 * added dome to terrain sky
 *
 * 93    1/06/98 1:29p Matt
 * Cleaned up interfaces to rendering routines, deleted unused code, etc.
 *
 * 92    1/02/98 6:08p Jason
 * fixed bug with alphaed moons and halos
 *
 * 90    12/30/97 5:45p Jason
 * added toggleable fog
 *
 * 89    12/29/97 5:44p Samir
 * Took out references to grViewport and old 2d library.
 *
 * 88    12/19/97 5:58p Jason
 * fixed out-of-bounds bug
 *
 * 87    12/19/97 5:38p Jason
 * fixed errors with 2d/3d integration
 *
 * 86    12/19/97 12:20p Jason
 * changes for better 2d/3d system integration
 *
 * 85    12/18/97 3:29p Jason
 * fixed some lightmap wrapping issues
 *
 * 84    12/17/97 5:26p Jason
 * added support for selectable wraparound sky
 *
 * 83    12/17/97 4:08p Jason
 * took out fog (again)
 *
 * 82    12/10/97 6:54p Jason
 * toned down star blur effect
 *
 * 81    12/09/97 7:13p Jason
 * added support for blurred lines in hardware
 *
 * 80    12/01/97 10:52a Jason
 * separated satellite and star rendering flags
 *
 * 79    11/21/97 5:33p Jason
 * fixed far clip bug
 *
 * 78    11/19/97 5:23p Jason
 * added terrain dynamic lighting
 *
 * 77    11/17/97 8:33p Jason
 * fixed bug with object selection introduced by last rev
 *
 * 76    11/17/97 6:13p Mark
 * allowed object 0 to be selected
 *
 * 75    11/10/97 12:21p Jason
 * implemented different object visibility
 *
 * 74    11/10/97 12:00p Jason
 * fixed view scaling bug in g3_DrawRotatedBitmap
 *
 * 73    10/30/97 4:38p Jason
 * special cased highest-lod in DrawTerrainTrianglesHardware
 *
 * 72    10/29/97 12:37p Jason
 * fixed tjoint problems
 *
 * 71    10/28/97 2:06p Jason
 * check for backfaces early
 *
 * 70    10/17/97 1:23p Jason
 * took out references to bitmap8bit.h
 *
 * 69    10/13/97 5:06p Chris
 * Made it compile in the main project (outline mode only in editor)
 *
 * 68    10/10/97 6:31p Jason
 * added extra level of detail level
 *
 * 67    10/09/97 11:11a Jason
 * turned fog back on for now
 *
 * 66    10/08/97 4:34p Jason
 * fixed line drawing problems
 *
 * 65    10/06/97 6:39p Jason
 * got terrain objects working with lightmaps/radiosity
 *
 * 64    10/02/97 6:45p Jason
 * optimized terrain rotation
 *
 * 63    10/02/97 6:21p Jason
 * checked in for matt
 *
 *
 * 62    10/02/97 3:48p Matt
 * Don't render room (via room object) if terrain renderer was called from
 * room renderer
 *
 * 61    10/02/97 2:45p Jason
 * got invisible terrain cells working
 *
 * 60    10/01/97 7:51p Matt
 * Added code for external rooms
 *
 * 59    9/30/97 4:20p Jason
 * took out terrain object light
 *
 * 58    9/29/97 5:40p Jason
 * patched circular linked list bug
 *
 * 57    9/21/97 7:57p Jason
 * separated hardware/software rendering pipes, plus got lightmaps working
 * with tmap2's
 *
 * 56    9/21/97 7:17p Jason
 * Made terrain lightmaps work again
 *
 * 55    9/18/97 1:24p Matt
 * Changed terrain object rendering to keep its data locally, instead of
 * in the object struct
 *
 * 54    9/17/97 5:08p Jason
 * took out fog (maybe just temporary)
 *
 *
 * 53    9/17/97 12:02p Jason
 * ripped out segment engine
 *
 * 52    9/12/97 7:06p Jason
 * fixed bug with MAX_RENDER_ROOMS being too low
 *
 * 51    9/12/97 5:17p Jason
 * fixed problem where buildings could be lower than terrain, thus
 * generating error
 *
 * 50    9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 49    9/09/97 6:17p Jason
 * fixed bug with color model and dynamic objects
 *
 * 48    9/09/97 6:15p Jason
 * Added groovy dynamic terrain lighting system
 *
 * 47    9/09/97 1:12p Jason
 * fixed color model bug
 *
 * 46    9/09/97 11:44a Jason
 * changed the way alpha works with the renderer
 *
 * 45    9/08/97 4:13p Jason
 * added colored lighting for the terrain
 *
 * 44    9/05/97 4:38p Jason
 * incremental updates
 *
 * 43    9/02/97 11:07a Jason
 * added alpha component to uvl struct
 *
 * 42    8/29/97 11:41a Jason
 * made textures not clamp if renderering the mine view
 *
 * 41    8/26/97 10:23a Jason
 * added some asserts, plus clamping for terrain textures
 *
 * 40    8/20/97 6:18p Jason
 * fixed memory corruption bug
 *
 * 39    8/20/97 4:22p Matt
 * Took out unneeded extern
 *
 * 38    8/19/97 5:12p Jason
 * (hopefully) fixed the polygon object popping problem
 *
 * 37    8/07/97 5:06p Jason
 * added new tiling system for terrain
 *
 * 36    8/07/97 3:19p Jason
 * replaced old terrain tmap system with new one
 *
 * 35    8/07/97 11:47a Jason
 * got tmap2s rotatable by themselves
 *
 * 34    8/06/97 5:00p Jason
 * ripped out lightmaps pending a better lighting system for terrain
 *
 * 33    8/06/97 11:43a Jason
 * made lightmaps work correctly in the terrain
 *
 * 32    8/01/97 5:46p Jason
 * did some housekeeping
 *
 * 31    7/31/97 3:28p Jason
 * fixed bug where memory would get corrupted when drawing newstyle
 * gouraud objects
 *
 * 30    7/29/97 5:33p Jason
 * precompute the edge rotation list
 *
 * 29    7/29/97 10:28a Jason
 * added RenderOBject abstraction layer
 *
 * 28    7/28/97 5:23p Jason
 * added features to lod engine - namely dynamic texture generation
 *
 * 27    7/28/97 1:14p Chris
 * Added support for sub-object visability.  Plus, debris.
 *
 * 26    7/25/97 5:25p Jason
 * fixed multiple bugs in terrain LOD engine
 *
 * 25    7/23/97 6:27p Jason
 * added code to support terrain simplification
 *
 * 24    7/21/97 1:59p Jason
 * added user adjustable fog parameters
 *
 * 23    7/20/97 8:37p Jason
 * fixed some fog problems
 *
 * 22    7/20/97 7:37p Jason
 * added new sky
 *
 * 21    7/20/97 3:40p Jason
 * got room/terrain links working (at least in the terrain)
 *
 * 20    7/18/97 7:25p Jason
 * do object drawing rather better
 *
 * 19    7/17/97 3:00p Jason
 * changed "moons" to be called satellites since we're going to have suns
 * and other things in orbit
 *
 *
 * 18    7/16/97 5:20p Jason
 * implemented selection of moons with mouse click
 *
 * 17    7/16/97 4:18p Matt
 * Changes to work with changed 3d draw functions
 *
 * 16    7/15/97 7:40p Jason
 * made fogplane obscenely close
 *
 * 15    7/15/97 6:44p Mark
 *
 * 14    7/15/97 5:32p Jason
 * got simple static lighting working with objects
 *
 * 13    7/15/97 4:57p Mark
 * Corrected usage of UseHardware flag
 *
 * 12    7/15/97 4:54p Jason
 * made water not move its friends
 *
 * 11    7/15/97 4:18p Matt
 * Don't do water undulation on tiles that have tmap2's on them
 *
 * 10    7/15/97 4:11p Jason
 * added focus selection to terrain objects
 *
 * 9     7/15/97 3:33p Jason
 * fixed some object sorting problems
 *
 * 8     7/15/97 3:09p Jason
 * fixed dumb bug that I introduced in my last rev
 *
 * 7     7/15/97 2:59p Matt
 * Added assert
 *
 * 39    6/24/97 4:24p Jason
 * changes for y only terrain
 *
 * 38    6/24/97 12:45p Jason
 * checked in for safety
 *
 * 37    6/17/97 11:35a Jason
 * checked in for safety
 *
 * 36    6/16/97 2:34p Jason
 * added 3dfx support
 *
 * 35    6/12/97 12:26p Jason
 * fixed dumb rotational bug
 *
 * 34    5/22/97 5:16p Jason
 * added tmap2 capability to the terrain
 *
 * 33    5/21/97 3:40p Jason
 * added terrain editing stuff
 *
 * 32    5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 31    5/16/97 4:53p Jason
 * made terrain clear the screen only when called from inside a mine
 *
 * 30    5/15/97 4:37p Jason
 * fixed some terrain bugs
 *
 * 29    5/15/97 3:28a Jason
 * tried to get subwindow clearing to work with terrain - but it won't
 * until samir fixes lock_clear
 *
 * 28    5/13/97 11:34a Samir
 * Changed some NDEBUGs to ifdef EDITORs
 *
 * 27    5/11/97 1:31p Matt
 * Added code to only render terrain that might be visible  when terrain
 * called from the mine renderer.
 *
 * $NoKeywords: $
 */
#ifdef NEWEDITOR
#include "neweditor\globals.h"
void RenderMine(int viewer_roomnum, int flag_automap, int called_from_terrain, bool render_all, bool outline, bool flat,
                prim *prim);
#endif
#include "terrain.h"
#include "grdefs.h"
#include "3d.h"
#include "pstypes.h"
#include "pserror.h"
#include "renderer.h"
#include "gametexture.h"
#include "descent.h"
#include "render.h"
#include "game.h"
#include "texture.h"
#include "ddio.h"
#include "polymodel.h"
#include "lighting.h"
#include "vecmat.h"
#include "renderobject.h"
#include "findintersection.h"
#include "weapon.h"
#include "weather.h"
#include "viseffect.h"
#ifdef EDITOR
#include "editor\d3edit.h"
#endif
#include "fireball.h"
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "gameloop.h"
#include "postrender.h"
#include "Macros.h"
#include "psrand.h"
#include "player.h"

#include <algorithm>

#define TERRAIN_PERSPECTIVE_TEXTURE_DEPTH 1 * TERRAIN_SIZE
#define LOD_ROW_SIZE (MAX_LOD_SIZE + 1)
int DrawTerrainTrianglesSoftware(int index, int bm_handle, int upper_left, int lower_right);
int DrawTerrainTrianglesHardware(int index, int bm_handle, int upper_left, int lower_right);
int DrawTerrainTrianglesHardwareNoLight(int index, int bm_handle, int upper_left, int lower_right);
void DrawTerrainLightmapsHardware(int index, int upper_left, int lower_right);
void DrawSky(vector *veye, matrix *vorient);
function_mode View_mode;
int ManageFramerate = 0;
int MinAllowableFramerate = 15;
uint8_t Fast_terrain = 1;
float Far_fog_border;
vector Terrain_viewer_eye;
uint8_t Terrain_from_mine = 0;
uint8_t Show_invisible_terrain = 0;
int Terrain_objects_drawn = 0;
vector Last_frame_stars[MAX_STARS];
float Terrain_texture_distance = DEFAULT_TEXTURE_DISTANCE;
int Check_terrain_portal = 0;
static vector Temp_sky_vectors[MAX_HORIZON_PIECES][6];
static vector Temp_sky_vectors_unrotated[MAX_HORIZON_PIECES][6];
// Last time terrain was rendered
float Last_terrain_render_time = -1;
// Sets UV's based on 90 degree rotations
float TerrainUSpeedup[4][LOD_ROW_SIZE * LOD_ROW_SIZE];
float TerrainVSpeedup[4][LOD_ROW_SIZE * LOD_ROW_SIZE];
#if (!defined(RELEASE) || defined(NEWEDITOR))
// for building a render list for each terrain cell
int render_next[MAX_OBJECTS];
#endif
void DrawPlayerOnWireframe();
float Clip_scale_left, Clip_scale_top, Clip_scale_right, Clip_scale_bot;
#ifdef NEWEDITOR
bool Rendering_main_view = true;
#endif
void InitTerrainRenderSpeedups() {
  // Figure out a table of values for rotated uv points
  for (int y = 0; y <= MAX_LOD_SIZE; y++) {
    for (int x = 0; x <= MAX_LOD_SIZE; x++) {
      TerrainUSpeedup[0][(y * LOD_ROW_SIZE) + x] = (float)x / (float)MAX_LOD_SIZE;
      TerrainVSpeedup[0][(y * LOD_ROW_SIZE) + x] = (float)y / (float)MAX_LOD_SIZE;
      TerrainUSpeedup[1][(y * LOD_ROW_SIZE) + x] = 1.0 - ((float)y / (float)MAX_LOD_SIZE);
      TerrainVSpeedup[1][(y * LOD_ROW_SIZE) + x] = (float)x / (float)MAX_LOD_SIZE;
      TerrainUSpeedup[2][(y * LOD_ROW_SIZE) + x] = 1.0 - ((float)x / (float)MAX_LOD_SIZE);
      TerrainVSpeedup[2][(y * LOD_ROW_SIZE) + x] = 1.0 - ((float)y / (float)MAX_LOD_SIZE);
      TerrainUSpeedup[3][(y * LOD_ROW_SIZE) + x] = ((float)y / (float)MAX_LOD_SIZE);
      TerrainVSpeedup[3][(y * LOD_ROW_SIZE) + x] = 1.0 - ((float)x / (float)MAX_LOD_SIZE);
    }
  }
}
// codes a point for visibility in the window passed to RenderTerrain()
uint8_t CodeTerrainPoint(g3Point *p) {
  uint8_t cc = 0;
  if (p->p3_sx > Clip_scale_right)
    cc |= CC_OFF_RIGHT;
  if (p->p3_sx < Clip_scale_left)
    cc |= CC_OFF_LEFT;
  if (p->p3_sy > Clip_scale_bot)
    cc |= CC_OFF_BOT;
  if (p->p3_sy < Clip_scale_top)
    cc |= CC_OFF_TOP;
  return cc;
}
// Returns true if light can hit this segment/heighth bit
int IsTerrainDynamicChecked(int seg, int bit) {
  if (seg < 0 || seg >= (TERRAIN_WIDTH * TERRAIN_DEPTH))
    return 1;
  if (bit >= 8)
    return 1;
  uint8_t val = Terrain_dynamic_table[seg] & (1 << bit);
  if (val)
    return 1;
  return 0;
}
// Gets the dynamic light value for this position
float GetTerrainDynamicScalar(vector *pos, int seg) {
  float cube_values[10];
  int y_increment = MAX_TERRAIN_HEIGHT / 8;
  int y_int = pos->y / y_increment;
  int x_int = pos->x / TERRAIN_SIZE;
  int z_int = pos->z / TERRAIN_SIZE;

  float x_norm = (pos->x / TERRAIN_SIZE) - x_int;
  float z_norm = (pos->z / TERRAIN_SIZE) - z_int;
  float y_norm = (pos->y / y_increment) - y_int;
  if (y_norm < 0) {
    y_norm = 0;
    y_int = 0;
  }
  if (y_norm > 1) {
    y_norm = 1.0;
    y_int = 7;
  }
  if (x_norm < 0 || x_norm > 1 || z_norm < 0 || z_norm > 1)
    return .5;
  float left_norm, right_norm, top_norm, bottom_norm, scalar;

  cube_values[0] = IsTerrainDynamicChecked(seg, y_int);
  cube_values[1] = IsTerrainDynamicChecked(seg + TERRAIN_WIDTH, y_int);
  cube_values[2] = IsTerrainDynamicChecked(seg + TERRAIN_WIDTH + 1, y_int);
  cube_values[3] = IsTerrainDynamicChecked(seg + 1, y_int);
  cube_values[4] = IsTerrainDynamicChecked(seg, y_int + 1);
  cube_values[5] = IsTerrainDynamicChecked(seg + TERRAIN_WIDTH, y_int + 1);
  cube_values[6] = IsTerrainDynamicChecked(seg + TERRAIN_WIDTH + 1, y_int + 1);
  cube_values[7] = IsTerrainDynamicChecked(seg + 1, y_int + 1);
  left_norm = ((1 - z_norm) * cube_values[0]) + (z_norm * cube_values[1]);
  right_norm = ((1 - z_norm) * cube_values[3]) + (z_norm * cube_values[2]);
  bottom_norm = ((1 - x_norm) * left_norm) + (x_norm * right_norm);
  left_norm = ((1 - z_norm) * cube_values[4]) + (z_norm * cube_values[5]);
  right_norm = ((1 - z_norm) * cube_values[7]) + (z_norm * cube_values[6]);
  top_norm = ((1 - x_norm) * left_norm) + (x_norm * right_norm);
  scalar = ((1 - y_norm) * bottom_norm) + (y_norm * top_norm);
  ASSERT(scalar >= 0 && scalar <= 1);
  return scalar;
}
// Takes a min,max vector and makes a surrounding cube from it
void MakePointsFromMinMax(vector *corners, vector *minp, vector *maxp);
struct obj_sort_item {
  int objnum;
  float dist;
  int vis_effect;
};
// Compare function for room face sort
static int obj_sort_func(const obj_sort_item *a, const obj_sort_item *b) {
  if (a->dist < b->dist)
    return -1;
  else if (a->dist > b->dist)
    return 1;
  else
    return 0;
}
// Returns true if the object is outside of our terrain portal
int ObjectOutOfPortal(object *obj) {
  g3Point pnt1, pnt2;
  uint8_t anded = 0xff;
  g3_RotatePoint(&pnt1, &obj->min_xyz);
  if (pnt1.p3_codes & CC_BEHIND)
    return 0;
  g3_ProjectPoint(&pnt1);
  anded &= CodeTerrainPoint(&pnt1);
  g3_RotatePoint(&pnt2, &obj->max_xyz);
  if (pnt2.p3_codes & CC_BEHIND)
    return 0;
  g3_ProjectPoint(&pnt2);
  anded &= CodeTerrainPoint(&pnt2);
  if (anded)
    return 1;
  return 0;
}
obj_sort_item objs_to_render[MAX_OBJECTS + MAX_VIS_EFFECTS];
obj_sort_item rooms_to_render[MAX_ROOMS];
// Checks to see if this object can even be seen from our current viewpoint
// By shooting rays to it
// Returns true if any of the rays hit
int ShootRaysToObject(object *obj) {
  vector corners[8];
  if (obj->type == OBJ_ROOM) {
    room *rp = &Rooms[obj->id];
    MakePointsFromMinMax(corners, &rp->min_xyz, &rp->max_xyz);
  } else {
    MakePointsFromMinMax(corners, &obj->min_xyz, &obj->max_xyz);
  }
  fvi_info hit_info;
  fvi_query fq;
  fq.p0 = &Viewer_object->pos;
  fq.startroom = Viewer_object->roomnum;
  fq.rad = 0.0f;
  fq.flags = FQ_NO_RELINK | FQ_EXTERNAL_ROOMS_AS_SPHERE | FQ_IGNORE_EXTERNAL_ROOMS;
  fq.thisobjnum = OBJNUM(Viewer_object);
  fq.ignore_obj_list = NULL;

  for (int i = 0; i < 8; i++) {
    fq.p1 = &corners[i];
    int fate = fvi_FindIntersection(&fq, &hit_info);
    /*g3Point pnt1,pnt2;
    vector fpnt = *fq.p0 + 3.0 * Viewer_object->orient.fvec;
    g3_RotatePoint (&pnt1,&fpnt);
    g3_RotatePoint (&pnt2,&hit_info.hit_pnt);
    g3_DrawLine ((GR_RGB(255,255,255)),&pnt1,&pnt2);*/
    if (fate == HIT_NONE)
      return 1;
  }
  return 0;
}
// Returns true if the external room is in the view cone
// Else returns false
bool ExternalRoomVisible(room *rp, vector *center, float *zdist) {
  ASSERT(rp->flags & RF_EXTERNAL);
  g3Point pnt;
  uint8_t ccode;

  vector corners[8];
  g3_RotatePoint(&pnt, center);
  *zdist = pnt.p3_z;
  MakePointsFromMinMax(corners, &rp->min_xyz, &rp->max_xyz);
  uint8_t andbyte = 0xff;
  for (int t = 0; t < 8; t++) {
    g3_RotatePoint(&pnt, &corners[t]);
    ccode = g3_CodePoint(&pnt);
    if (!ccode)
      return true;
    andbyte &= ccode;
  }
  if (andbyte)
    return false;
  return true;
}
// Render all the rooms out on the terrain for this frame
void RenderTerrainRooms() {
  object *obj;
#ifdef EDITOR
  if (!Terrain_render_ext_room_objs)
    return;
#endif

  int room_count = 0;
  float zdist;
  int use_occlusion = 0;
  int src_occlusion_index;
  int i;
  if (Terrain_from_mine)
    return;
  if ((Terrain_checksum + 1) == Terrain_occlusion_checksum) {
    use_occlusion = 1;
    int oz = (Viewer_object->pos.z / TERRAIN_SIZE) / OCCLUSION_SIZE;
    int ox = (Viewer_object->pos.x / TERRAIN_SIZE) / OCCLUSION_SIZE;
    if (oz < 0 || oz >= OCCLUSION_SIZE || ox < 0 || ox >= OCCLUSION_SIZE)
      use_occlusion = 0;
    src_occlusion_index = oz * OCCLUSION_SIZE + ox;
  }
  for (i = 0; i <= Highest_object_index; i++) {
    obj = &Objects[i];
    if (obj->type != OBJ_ROOM)
      continue;

    if (obj->flags & OF_DEAD)
      continue;
    if (obj->render_type == RT_NONE)
      continue;
    if (!OBJECT_OUTSIDE(obj))
      continue;
    float size = obj->size;

    if (use_occlusion) {
      int y1 = (obj->pos.z / TERRAIN_SIZE) / OCCLUSION_SIZE;
      int x1 = (obj->pos.x / TERRAIN_SIZE) / OCCLUSION_SIZE;
      int dest_occlusion_index = (y1 * OCCLUSION_SIZE);
      dest_occlusion_index += x1;
      int occ_byte = dest_occlusion_index / 8;
      int occ_bit = dest_occlusion_index % 8;
      if (obj->pos.y < MAX_TERRAIN_HEIGHT) {
        if (!(Terrain_occlusion_map[src_occlusion_index][occ_byte] & (1 << occ_bit)))
          continue;
      }
    }
    if (!ExternalRoomVisible(&Rooms[obj->id], &obj->pos, &zdist))
      continue;
    if (!IsPointVisible(&obj->pos, size, &zdist))
      continue;

    if (Check_terrain_portal && ObjectOutOfPortal(obj))
      continue;
    /*if (!Terrain_from_mine)
    {
            if (!ShootRaysToObject (obj))
                    continue;
    }*/
    rooms_to_render[room_count].vis_effect = 0;
    rooms_to_render[room_count].objnum = OBJNUM(obj);
    rooms_to_render[room_count].dist = zdist;
    room_count++;
  }
  // Sort and draw rooms
  qsort(rooms_to_render, room_count, sizeof(*rooms_to_render), (int (*)(const void *, const void *))obj_sort_func);
  for (i = room_count - 1; i >= 0; i--) {
    int objnum = rooms_to_render[i].objnum;
    object *obj = &Objects[objnum];
#ifndef NEWEDITOR
    RenderMine(obj->id, 0, 1);
#else
    RenderMine(obj->id, 0, 1, 1, 0, 0, NULL);
#endif
// Draw a surrounding sphere
#if (defined(_DEBUG) && !defined(NEWEDITOR))
    if (Game_show_sphere == 2)
      DrawDebugInfo(obj);
#endif
  }
}
// Renders every visible terrain object
void RenderAllTerrainObjects() {
  object *obj;
  int snows[500];
  int num_snows = 0;
  int obj_count = 0;
  float zdist;
  int use_occlusion = 0;
  int src_occlusion_index;
  int i;
  if ((Terrain_checksum + 1) == Terrain_occlusion_checksum) {
    use_occlusion = 1;
    int oz = (Viewer_object->pos.z / TERRAIN_SIZE) / OCCLUSION_SIZE;
    int ox = (Viewer_object->pos.x / TERRAIN_SIZE) / OCCLUSION_SIZE;
    if (oz < 0 || oz >= OCCLUSION_SIZE || ox < 0 || ox >= OCCLUSION_SIZE)
      use_occlusion = 0;
    src_occlusion_index = oz * OCCLUSION_SIZE + ox;
  }
  for (i = 0; i <= Highest_object_index; i++) {
    obj = &Objects[i];
    if (obj == Viewer_object)
      continue;
    // Don't draw piggybacked objects
    if (Viewer_object->type == OBJ_OBSERVER && i == Players[Viewer_object->id].piggy_objnum)
      continue;
    if (obj->type == OBJ_ROOM)
      continue;

    if (obj->type == OBJ_NONE)
      continue;
    if (obj->flags & OF_DEAD)
      continue;
    if (obj->render_type == RT_NONE)
      continue;
    if (!OBJECT_OUTSIDE(obj))
      continue;
    float size = obj->size;

    // Special case weapons with streamers
    if (obj->type == OBJ_WEAPON && (Weapons[obj->id].flags & WF_STREAMER))
      size = Weapons[obj->id].phys_info.velocity.z;
    if (use_occlusion) {
      int y1 = (obj->pos.z / TERRAIN_SIZE) / OCCLUSION_SIZE;
      int x1 = (obj->pos.x / TERRAIN_SIZE) / OCCLUSION_SIZE;
      int dest_occlusion_index = (y1 * OCCLUSION_SIZE);
      dest_occlusion_index += x1;
      int occ_byte = dest_occlusion_index / 8;
      int occ_bit = dest_occlusion_index % 8;
      if (obj->pos.y + obj->size < MAX_TERRAIN_HEIGHT) {
        if (!(Terrain_occlusion_map[src_occlusion_index][occ_byte] & (1 << occ_bit)))
          continue;
      }
    }
    if (obj->type == OBJ_WEAPON && Weapons[obj->id].flags & WF_ELECTRICAL) {
      // Automatically render all electrical objects
      zdist = 0;
    } else {
      if (!IsPointVisible(&obj->pos, size, &zdist))
        continue;

      if (Check_terrain_portal && ObjectOutOfPortal(obj))
        continue;
    }

    if (UseHardware) {
      if (Num_postrenders < MAX_POSTRENDERS) {
        Postrender_list[Num_postrenders].type = PRT_OBJECT;
        Postrender_list[Num_postrenders].z = zdist;
        Postrender_list[Num_postrenders++].objnum = OBJNUM(obj);
      }
    } else {
      objs_to_render[obj_count].vis_effect = 0;
      objs_to_render[obj_count].objnum = OBJNUM(obj);
      objs_to_render[obj_count].dist = zdist;
      obj_count++;
    }
  }
#ifndef NEWEDITOR
  for (i = 0; i <= Highest_vis_effect_index; i++) {
    vis_effect *vis = &VisEffects[i];

    if (vis->type == VIS_NONE)
      continue;
    if (vis->flags & VF_DEAD)
      continue;
    if (!ROOMNUM_OUTSIDE(vis->roomnum))
      continue;
    // Special case snow
    if (vis->id == SNOWFLAKE_INDEX) {
      snows[num_snows] = vis - VisEffects;
      num_snows++;
    } else {
      if ((vis->flags & VF_WINDSHIELD_EFFECT) || IsPointVisible(&vis->pos, vis->size, &zdist)) {
        if (vis->flags & VF_WINDSHIELD_EFFECT)
          zdist = 0;
        if (UseHardware) {
          if (Num_postrenders < MAX_POSTRENDERS) {
            Postrender_list[Num_postrenders].type = PRT_VISEFFECT;
            Postrender_list[Num_postrenders].z = zdist;
            Postrender_list[Num_postrenders++].objnum = vis - VisEffects;
          }
        } else {
          objs_to_render[obj_count].vis_effect = 1;
          objs_to_render[obj_count].objnum = vis - VisEffects;
          objs_to_render[obj_count].dist = zdist;
          obj_count++;
        }
      }
    }
  }
#endif

  // Sort objects
  qsort(objs_to_render, obj_count, sizeof(*objs_to_render), (int (*)(const void *, const void *))obj_sort_func);
  // Render the objects
  for (i = obj_count - 1; i >= 0; i--) {
    int vis_effect = objs_to_render[i].vis_effect;
    int objnum = objs_to_render[i].objnum;
    if (vis_effect)
      DrawVisEffect(&VisEffects[objnum]);
    else
      RenderObject(&Objects[objnum]);
  }
  // Render snows
  rend_SetZBufferWriteMask(0);
  for (i = 0; i < num_snows; i++)
    DrawVisEffect(&VisEffects[snows[i]]);
  rend_SetZBufferWriteMask(1);
  rend_SetZBufferState(1);
  rend_SetWrapType(WT_WRAP);
}
#define FOG_LAYER_HEIGHT (TERRAIN_HEIGHT_INCREMENT * 30.5f)
// Draws a flat fog layer
void DrawFogLayer() {
  vector worldvec[4];
  g3Point pnt[4], *pntlist[6];
  rend_SetFlatColor(GR_RGB(132, 132, 255));
  rend_SetAlphaValue(64);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_NONE);
  worldvec[0].x = 0;
  worldvec[0].y = FOG_LAYER_HEIGHT;
  worldvec[0].z = 0;
  worldvec[1].x = 0;
  worldvec[1].y = FOG_LAYER_HEIGHT;
  worldvec[1].z = TERRAIN_DEPTH * TERRAIN_SIZE;
  worldvec[2].x = TERRAIN_WIDTH * TERRAIN_SIZE;
  worldvec[2].y = FOG_LAYER_HEIGHT;
  worldvec[2].z = TERRAIN_DEPTH * TERRAIN_SIZE;
  worldvec[3].x = TERRAIN_WIDTH * TERRAIN_SIZE;
  worldvec[3].y = FOG_LAYER_HEIGHT;
  worldvec[3].z = 0;
  for (int i = 0; i < 4; i++) {
    g3_RotatePoint(&pnt[i], &worldvec[i]);
    pntlist[i] = &pnt[i];
  }
  g3_DrawPoly(4, pntlist, 0);
}
#define CLOUD_LAYER_HEIGHT (TERRAIN_HEIGHT_INCREMENT * 320.0f)
// Draws a flat fog layer
void DrawCloudLayer() {
  vector worldvec[4];
  g3Point pnt[4], *pntlist[6];
  rend_SetFlatColor(GR_RGB(192, 192, 255));
  rend_SetAlphaValue(32);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_NONE);
  worldvec[0].x = -(TERRAIN_SIZE * 100);
  worldvec[0].y = CLOUD_LAYER_HEIGHT;
  worldvec[0].z = (TERRAIN_SIZE * (100 + TERRAIN_DEPTH));

  worldvec[1].x = -(TERRAIN_SIZE * 100);
  worldvec[1].y = CLOUD_LAYER_HEIGHT;
  worldvec[1].z = -(TERRAIN_SIZE * (100));

  worldvec[2].x = (TERRAIN_SIZE * (100 + TERRAIN_WIDTH));
  worldvec[2].y = CLOUD_LAYER_HEIGHT;
  worldvec[2].z = -(TERRAIN_SIZE * (100));

  worldvec[3].x = (TERRAIN_SIZE * (100 + TERRAIN_WIDTH));
  worldvec[3].y = CLOUD_LAYER_HEIGHT;
  worldvec[3].z = (TERRAIN_SIZE * (100 + TERRAIN_DEPTH));
  for (int i = 0; i < 4; i++) {
    g3_RotatePoint(&pnt[i], &worldvec[i]);
    pntlist[i] = &pnt[i];
  }
  g3_DrawPoly(4, pntlist, 0);
}
// left,top,right,bot are optional parameters.  Omiting them (or setting them to -1) will
// render to the whole screen.  Passing valid values will only render tiles visible in the
// specified window (though it won't clip those tiles to the window)
void RenderTerrain(uint8_t from_mine, int left, int top, int right, int bot) {
  static int first = 1;
  if (first) {
    InitTerrainRenderSpeedups();
    first = 0;
  }

  // Get the size of the current render window
  int render_width, render_height;
  rend_GetProjectionParameters(&render_width, &render_height);
  float w2 = ((float)render_width - 1) / 2.0f;
  float h2 = ((float)render_height - 1) / 2.0f;

  // Set up vars for (psuedo-)clipping window
  if (left < 0) {
    Check_terrain_portal = 0;
    left = 0;
  } else {
    int w = right - left;
    int h = bot - top;

    // If the portal takes up more than 50% the screen space then we don't check against it
    float threshold = (render_width * render_height) * 0.5f;
    if (w * h > threshold) {
      Check_terrain_portal = 0;
    } else {
      Check_terrain_portal = 1;
    }
  }

  if (top < 0) {
    top = 0;
  }
  if ((right == -1) || right > render_width)
    right = render_width - 1;
  if ((bot == -1) || bot > render_height)
    bot = render_height - 1;
  Clip_scale_left = left;
  Clip_scale_right = right;
  Clip_scale_top = top;
  Clip_scale_bot = bot;
  if (!Terrain_sky.textured) {
    rend_FillRect(Terrain_sky.sky_color, left, top, right + 1, bot + 1);
  }

  rend_SetFlatColor(Terrain_sky.sky_color);
  View_mode = GetFunctionMode();

  // Set this so we don't do reentrant rendering between terrain/mine
  Terrain_from_mine = from_mine;

#ifndef NEWEDITOR
  // See if we're supposed change the fog plane distance based on our framerate
  if (View_mode != EDITOR_MODE && ManageFramerate) {
    float fps = GetFPS();
    if (fps < MinAllowableFramerate) {
      if (Detail_settings.Terrain_render_distance > TERRAIN_SIZE) {
        Detail_settings.Terrain_render_distance -= (float)(TERRAIN_SIZE / 4);
      }
    } else if (fps > MinAllowableFramerate + 1) {
      if (Detail_settings.Terrain_render_distance < 60 * TERRAIN_SIZE) {
        Detail_settings.Terrain_render_distance += (float)(TERRAIN_SIZE / 4);
      }
    }
  }
#endif

#ifndef NEWEDITOR
  const float kTerrainRenderDistance = Detail_settings.Terrain_render_distance;
#else
  const float kTerrainRenderDistance = 1200.0f;
#endif
  VisibleTerrainZ = kTerrainRenderDistance * Matrix_scale.z;
  Far_fog_border = VisibleTerrainZ;

  // Set up our z wall
  g3_SetFarClipZ(VisibleTerrainZ);

  // Get the viewer position & orientation
  vector viewer_eye;
  matrix viewer_orient;
  g3_GetViewPosition(&viewer_eye);
  g3_GetViewMatrix(&viewer_orient);

  // Get all of the cells visible to us
  int nt = GetVisibleTerrain(&viewer_eye, &viewer_orient);

  // Set this to really far away so our sky can render
  g3_SetFarClipZ(60000);
  rend_SetFogState(0);

  // Draw the sky
  DrawSky(&viewer_eye, &viewer_orient);

  //// Set up our z wall
  rend_SetZBufferState(1);
  rend_SetZBufferWriteMask(1);
  g3_SetFarClipZ(VisibleTerrainZ);

#ifndef NEWEDITOR
  if ((Terrain_sky.flags & TF_FOG) && (UseHardware || (!UseHardware && Lighting_on))) {
    rend_SetZValues(0, VisibleTerrainZ);
    rend_SetFogState(1);
    rend_SetFogBorders(VisibleTerrainZ * Terrain_sky.fog_scalar, Far_fog_border);
    rend_SetFogColor(Terrain_sky.fog_color);
  } else
#endif
  {
    rend_SetZValues(0, 5000);
  }

  // And display!
  if (nt > 0) {
    DisplayTerrainList(nt);
  }

  // Draw rooms
  RenderTerrainRooms();

  // Show objects
  if (nt < 1 || UseHardware) {
    RenderAllTerrainObjects();
  }

  mprintf_at(2, 5, 0, "Objs Drawn=%5d", Terrain_objects_drawn);
  Last_terrain_render_time = Gametime;
}

// Draws a segment of lightning that is always facing you
// Vectors are in world coords
void DrawLightningSegment(vector *from, vector *to) {
  vector src_vecs[2], world_vecs[6];
  g3Point rot_src_pnts[2], world_points[6], *pntlist[6];
  static float alphas[] = {0.3f, 1.0f, 0.3f, 0.3f, 1.0f, 0.3f};
  src_vecs[0] = *from;
  src_vecs[1] = *to;

  g3_RotatePoint(&rot_src_pnts[0], &src_vecs[0]);
  g3_RotatePoint(&rot_src_pnts[1], &src_vecs[1]);
  if (rot_src_pnts[0].p3_codes & rot_src_pnts[1].p3_codes)
    return; // Don't draw because both points are off screen
  vector rvec = Viewer_object->orient.rvec * 10;

  // Put all points so that they face the viewer
  world_vecs[0] = src_vecs[0] - rvec;
  world_vecs[1] = src_vecs[0];
  world_vecs[2] = src_vecs[0] + rvec;
  world_vecs[3] = src_vecs[1] + rvec;
  world_vecs[4] = src_vecs[1];
  world_vecs[5] = src_vecs[1] - rvec;
  for (int i = 0; i < 6; i++) {
    g3_RotatePoint(&world_points[i], &world_vecs[i]);
    world_points[i].p3_flags |= PF_RGBA;
    world_points[i].p3_r = .2f;
    world_points[i].p3_g = .4f;
    world_points[i].p3_b = 1.0f;
    world_points[i].p3_a = alphas[i];
    pntlist[i] = &world_points[i];
  }
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_GOURAUD);
  rend_SetAlphaType(AT_SATURATE_VERTEX);
  rend_SetColorModel(CM_RGB);
  g3_ProjectPoint(&world_points[1]);
  g3_ProjectPoint(&world_points[4]);
  rend_DrawSpecialLine(&world_points[1], &world_points[4]);
  g3_DrawPoly(6, pntlist, 0);
}
#define PUSH_LIGHTNING_TREE(f, l, sp)                                                                                  \
  {                                                                                                                    \
    froms[si] = f;                                                                                                     \
    stack_level[si] = l;                                                                                               \
    splits[si] = sp;                                                                                                   \
    si++;                                                                                                              \
  }
#define POP_LIGHTNING_TREE()                                                                                           \
  {                                                                                                                    \
    si--;                                                                                                              \
    cur_from = froms[si];                                                                                              \
    level = stack_level[si];                                                                                           \
    cur_splits = splits[si];                                                                                           \
  }
// Draws an entire strip of lightning
void DrawLightning(void) {
  angvec player_angs;
  matrix mat;
  vector froms[50];
  int si = 0, level;
  int stack_level[50];
  int splits[50];
  int cur_splits = 0;
  int new_heading;
  float scalar;
  scalar = ((ps_rand() % 1000) - 500) / 500.0;
  scalar *= 15000;
  vm_ExtractAnglesFromMatrix(&player_angs, &Viewer_object->orient);
  new_heading = (player_angs.h + (int)scalar) % 65536;
  vm_AnglesToMatrix(&mat, 0, new_heading, 0);
  // Put the starting point way up in the air
  float ylimit = (-(Viewer_object->pos.y * 2)) + (ps_rand() % 400);
  vector cur_from = Viewer_object->pos + (mat.fvec * 4000);
  vector new_vec;
  cur_from.y += 800.0f;
  cur_from.y += (ps_rand() % 100);
  // Set some states

  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetAlphaValue(.5 * 255);
  rend_SetLighting(LS_NONE);
  int bm_handle;

  // See if we should drawn an origin bitmap
  if (ps_rand() % 3) {
    // Pick an origin bitmap
    if (ps_rand() % 2)
      bm_handle = Fireballs[LIGHTNING_ORIGIN_INDEXA].bm_handle;
    else
      bm_handle = Fireballs[LIGHTNING_ORIGIN_INDEXB].bm_handle;
    // Draw the origin bitmap
    int size = 300 + (ps_rand() % 200);
    g3_DrawRotatedBitmap(&cur_from, 0, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
  }
  PUSH_LIGHTNING_TREE(cur_from, 0, 0)
  while (si > 0) {
    POP_LIGHTNING_TREE()
    ASSERT(level < 50);
    float x_adjust = ((ps_rand() % 200) - 100) / 100.0;
    float y_adjust = .3 + ((ps_rand() % 100) / 100.0);

    new_vec = cur_from;
    new_vec += x_adjust * (mat.rvec * 70);
    new_vec -= y_adjust * (mat.uvec * 100);
    DrawLightningSegment(&cur_from, &new_vec);
    if (cur_from.y < ylimit) // We're close to the ground, so just bail!
      continue;

    if ((ps_rand() % ((level * level * 20) + 8)) == 0 && cur_splits < 2) {
      // Make this branch split
      PUSH_LIGHTNING_TREE(new_vec, level, cur_splits + 1)
      PUSH_LIGHTNING_TREE(new_vec, level, cur_splits + 1)
    } else {
      PUSH_LIGHTNING_TREE(new_vec, level, cur_splits)
    }
  }
}
// Draws a lightning sky
void DrawLightningSky(void) {
  int t, k, tw;
  float r, g, b;

  g3Point pnt[4], *pntlist[6];

  rend_SetTextureType(TT_FLAT);
  rend_SetColorModel(CM_RGB);
  rend_SetLighting(LS_GOURAUD);
  rend_SetAlphaType(AT_SATURATE_VERTEX);

  // figure out colors for sky
  r = .8f;
  g = .8f;
  b = 1.0;
  // Draw top part
  for (t = 0; t < MAX_HORIZON_PIECES; t++) {
    tw = (t + 1) % MAX_HORIZON_PIECES;
    pnt[0].p3_vec = Temp_sky_vectors[t][0];
    pnt[0].p3_vecPreRot = Temp_sky_vectors_unrotated[t][0];
    pnt[1].p3_vec = Temp_sky_vectors[tw][1];
    pnt[1].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][1];
    pnt[2].p3_vec = Temp_sky_vectors[t][1];
    pnt[2].p3_vecPreRot = Temp_sky_vectors_unrotated[t][1];

    for (k = 0; k < 3; k++) {
      g3Point *p = &pnt[k];
      p->p3_flags = PF_RGBA | PF_ORIGPOINT;
      g3_CodePoint(p);
      p->p3_a = .3f;
      p->p3_r = r;
      p->p3_g = g;
      p->p3_b = b;
    }
    pntlist[0] = &pnt[0];
    pntlist[1] = &pnt[1];
    pntlist[2] = &pnt[2];
    g3_DrawPoly(3, pntlist, 0);
  }
  // Draw bottom part
  for (int i = 1; i < 5; i++) {
    for (t = 0; t < MAX_HORIZON_PIECES; t++) {
      tw = (t + 1) % MAX_HORIZON_PIECES;
      pnt[0].p3_vec = Temp_sky_vectors[t][i];
      pnt[0].p3_vecPreRot = Temp_sky_vectors_unrotated[t][i];
      pnt[1].p3_vec = Temp_sky_vectors[tw][i];
      pnt[1].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][i];
      pnt[2].p3_vec = Temp_sky_vectors[tw][i + 1];
      pnt[2].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][i + 1];
      pnt[3].p3_vec = Temp_sky_vectors[t][i + 1];
      pnt[3].p3_vecPreRot = Temp_sky_vectors_unrotated[t][i + 1];

      for (k = 0; k < 4; k++) {
        g3Point *p = &pnt[k];
        p->p3_flags = PF_RGBA | PF_ORIGPOINT;
        g3_CodePoint(p);
        p->p3_a = .3f;
        p->p3_r = r;
        p->p3_g = g;
        p->p3_b = b;
        pntlist[k] = p;
      }
      g3_DrawPoly(4, pntlist, 0);
    }
  }
}
// Draws the gouraud sky
void DrawGouraudSky(void) {
  int t, k, tw;
  float sr, sg, sb, hr, hg, hb;

  g3Point pnt[4], *pntlist[6];
  g3UVL uvls[10];
  if (Terrain_sky.sky_color == Terrain_sky.horizon_color)
    return; // No sense in drawing anything
  rend_SetTextureType(TT_FLAT);
  rend_SetColorModel(CM_RGB);
  rend_SetAlphaType(AT_ALWAYS);
  // figure out colors for sky
  {
    sr = (float)GR_COLOR_RED(Terrain_sky.sky_color) / 255.0;
    sg = (float)GR_COLOR_GREEN(Terrain_sky.sky_color) / 255.0;
    sb = (float)GR_COLOR_BLUE(Terrain_sky.sky_color) / 255.0;
    hr = (float)GR_COLOR_RED(Terrain_sky.horizon_color) / 255.0;
    hg = (float)GR_COLOR_GREEN(Terrain_sky.horizon_color) / 255.0;
    hb = (float)GR_COLOR_BLUE(Terrain_sky.horizon_color) / 255.0;
  }
  for (t = 0; t < MAX_HORIZON_PIECES; t++) {
    tw = (t + 1) % MAX_HORIZON_PIECES;
    pnt[0].p3_vec = Temp_sky_vectors[t][4];
    pnt[0].p3_vecPreRot = Temp_sky_vectors_unrotated[t][4];
    uvls[0].r = sr;
    uvls[0].g = sg;
    uvls[0].b = sb;

    pnt[1].p3_vec = Temp_sky_vectors[tw][4];
    pnt[1].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][4];
    uvls[1].r = sr;
    uvls[1].g = sg;
    uvls[1].b = sb;

    pnt[2].p3_vec = Temp_sky_vectors[tw][5];
    pnt[2].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][5];
    uvls[2].r = hr;
    uvls[2].g = hg;
    uvls[2].b = hb;

    pnt[3].p3_vec = Temp_sky_vectors[t][5];
    pnt[3].p3_vecPreRot = Temp_sky_vectors_unrotated[t][5];
    uvls[3].r = hr;
    uvls[3].g = hg;
    uvls[3].b = hb;

    for (k = 0; k < 4; k++) {
      g3Point *p = &pnt[k];
      p->p3_flags = PF_RGBA | PF_ORIGPOINT;
      g3_CodePoint(p);
      pntlist[k] = p;
      p->p3_uvl = uvls[k];
    }
    g3_DrawPoly(4, pntlist, 0);
  }
}
// Draws the sky textures
void DrawTexturedSky(void) {
  int t, k, tw;
  float sr, sg, sb, hr, hg, hb;

  // Change terrain sky if needed
  int dome_bm = GetTextureBitmap(Terrain_sky.dome_texture, 0);

  g3Point pnt[6], *pntlist[6];
  g3UVL uvls[10];

  rend_SetWrapType(WT_WRAP);
  rend_SetTextureType(TT_PERSPECTIVE);
  rend_SetColorModel(CM_MONO);
  rend_SetAlphaType(ATF_TEXTURE);
  g3_SetTriangulationTest(1);

  // Draw top part
  for (t = 0; t < MAX_HORIZON_PIECES; t++) {
    tw = (t + 1) % MAX_HORIZON_PIECES;
    pnt[0].p3_vec = Temp_sky_vectors[t][0];
    pnt[0].p3_vecPreRot = Temp_sky_vectors_unrotated[t][0];
    uvls[0].u = Terrain_sky.horizon_u[t][0];
    uvls[0].v = Terrain_sky.horizon_v[t][0];

    pnt[1].p3_vec = Temp_sky_vectors[tw][1];
    pnt[1].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][1];
    uvls[1].u = Terrain_sky.horizon_u[tw][1];
    uvls[1].v = Terrain_sky.horizon_v[tw][1];

    pnt[2].p3_vec = Temp_sky_vectors[t][1];
    pnt[2].p3_vecPreRot = Temp_sky_vectors_unrotated[t][1];
    uvls[2].u = Terrain_sky.horizon_u[t][1];
    uvls[2].v = Terrain_sky.horizon_v[t][1];

    for (k = 0; k < 3; k++) {
      g3Point *p = &pnt[k];
      p->p3_flags = PF_UV | PF_L | PF_ORIGPOINT;
      g3_CodePoint(p);
      p->p3_uvl = uvls[k];
      p->p3_l = 1;
    }

#if (defined(EDITOR) || defined(NEWEDITOR))
    ddgr_color oldcolor;
    if (TSearch_on) {
      rend_SetPixel(GR_RGB(0, 255, 0), TSearch_x, TSearch_y);
      oldcolor = rend_GetPixel(TSearch_x, TSearch_y); // will be different in 15/16-bit color
    }
#endif

    pntlist[0] = &pnt[0];
    pntlist[1] = &pnt[1];
    pntlist[2] = &pnt[2];
    g3_DrawPoly(3, pntlist, dome_bm);

#if (defined(EDITOR) || defined(NEWEDITOR))
    if (TSearch_on) {
      ddgr_color newcolor = rend_GetPixel(TSearch_x, TSearch_y);
      if (newcolor != oldcolor) {
        TSearch_seg = t;
        TSearch_found_type = TSEARCH_FOUND_SKY_DOME;
      }
    }
#endif
  }

  // Draw bottom part
  for (int i = 1; i < 4; i++) {
    for (t = 0; t < MAX_HORIZON_PIECES; t++) {
      tw = (t + 1) % MAX_HORIZON_PIECES;
      pnt[0].p3_vec = Temp_sky_vectors[t][i];
      pnt[0].p3_vecPreRot = Temp_sky_vectors_unrotated[t][i];
      uvls[0].u = Terrain_sky.horizon_u[t][i];
      uvls[0].v = Terrain_sky.horizon_v[t][i];

      pnt[1].p3_vec = Temp_sky_vectors[tw][i];
      pnt[1].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][i];
      uvls[1].u = Terrain_sky.horizon_u[tw][i];
      uvls[1].v = Terrain_sky.horizon_v[tw][i];

      pnt[2].p3_vec = Temp_sky_vectors[tw][i + 1];
      pnt[2].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][i + 1];
      uvls[2].u = Terrain_sky.horizon_u[tw][i + 1];
      uvls[2].v = Terrain_sky.horizon_v[tw][i + 1];

      pnt[3].p3_vec = Temp_sky_vectors[t][i + 1];
      pnt[3].p3_vecPreRot = Temp_sky_vectors_unrotated[t][i + 1];
      uvls[3].u = Terrain_sky.horizon_u[t][i + 1];
      uvls[3].v = Terrain_sky.horizon_v[t][i + 1];

      for (k = 0; k < 4; k++) {
        g3Point *p = &pnt[k];
        p->p3_flags = PF_UV | PF_L | PF_ORIGPOINT;
        g3_CodePoint(p);
        pntlist[k] = p;
        p->p3_uvl = uvls[k];
        p->p3_l = 1;
      }
#if (defined(EDITOR) || defined(NEWEDITOR))
      ddgr_color oldcolor;
      if (TSearch_on) {
        rend_SetPixel(GR_RGB(0, 255, 0), TSearch_x, TSearch_y);
        oldcolor = rend_GetPixel(TSearch_x, TSearch_y); // will be different in 15/16-bit color
      }
#endif

      g3_DrawPoly(4, pntlist, dome_bm);
#if (defined(EDITOR) || defined(NEWEDITOR))
      if (TSearch_on) {
        ddgr_color newcolor = rend_GetPixel(TSearch_x, TSearch_y);
        if (newcolor != oldcolor) {
          TSearch_seg = t;
          TSearch_found_type = TSEARCH_FOUND_SKY_DOME;
        }
      }
#endif
    }
  }
  // Now draw band
  rend_SetTextureType(TT_FLAT);
  rend_SetColorModel(CM_RGB);
  rend_SetAlphaType(AT_ALWAYS);

  // figure out colors for sky
  {
    sr = (float)GR_COLOR_RED(Terrain_sky.sky_color) / 255.0;
    sg = (float)GR_COLOR_GREEN(Terrain_sky.sky_color) / 255.0;
    sb = (float)GR_COLOR_BLUE(Terrain_sky.sky_color) / 255.0;
    hr = (float)GR_COLOR_RED(Terrain_sky.horizon_color) / 255.0;
    hg = (float)GR_COLOR_GREEN(Terrain_sky.horizon_color) / 255.0;
    hb = (float)GR_COLOR_BLUE(Terrain_sky.horizon_color) / 255.0;
  }

  for (t = 0; t < MAX_HORIZON_PIECES; t++) {
    tw = (t + 1) % MAX_HORIZON_PIECES;
    pnt[0].p3_vec = Temp_sky_vectors[t][4];
    pnt[0].p3_vecPreRot = Temp_sky_vectors_unrotated[t][4];
    uvls[0].r = sr;
    uvls[0].g = sg;
    uvls[0].b = sb;

    pnt[1].p3_vec = Temp_sky_vectors[tw][4];
    pnt[1].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][4];
    uvls[1].r = sr;
    uvls[1].g = sg;
    uvls[1].b = sb;

    pnt[2].p3_vec = Temp_sky_vectors[tw][5];
    pnt[2].p3_vecPreRot = Temp_sky_vectors_unrotated[tw][5];
    uvls[2].r = hr;
    uvls[2].g = hg;
    uvls[2].b = hb;

    pnt[3].p3_vec = Temp_sky_vectors[t][5];
    pnt[3].p3_vecPreRot = Temp_sky_vectors_unrotated[t][5];
    uvls[3].r = hr;
    uvls[3].g = hg;
    uvls[3].b = hb;

    for (k = 0; k < 4; k++) {
      g3Point *p = &pnt[k];
      p->p3_flags = PF_RGBA | PF_ORIGPOINT;
      g3_CodePoint(p);
      pntlist[k] = p;
      p->p3_uvl = uvls[k];
    }
    g3_DrawPoly(4, pntlist, 0);
  }
  g3_SetTriangulationTest(0);
  rend_SetWrapType(WT_WRAP);
}

// Draws the sky textures
void DrawWireframeSky(void) {
  int t, k, tw, i;
  g3Point pnt[6];

  // Draw top part
  for (t = 0; t < MAX_HORIZON_PIECES; t++) {
    tw = (t + 1) % MAX_HORIZON_PIECES;
    pnt[0].p3_vec = Temp_sky_vectors[t][0];
    pnt[1].p3_vec = Temp_sky_vectors[tw][1];
    pnt[2].p3_vec = Temp_sky_vectors[t][1];

    for (k = 0; k < 3; k++) {
      g3_CodePoint(&pnt[k]);
      pnt[k].p3_flags = 0;
    }

    for (k = 0; k < 3; k++)
      g3_DrawLine(GR_RGB(255, 255, 255), &pnt[k], &pnt[(k + 1) % 3]);
  }
  // Draw bottom parts
  for (i = 1; i < 5; i++) {
    for (t = 0; t < MAX_HORIZON_PIECES; t++) {
      tw = (t + 1) % MAX_HORIZON_PIECES;
      pnt[0].p3_vec = Temp_sky_vectors[t][i];
      pnt[1].p3_vec = Temp_sky_vectors[tw][i];
      pnt[2].p3_vec = Temp_sky_vectors[tw][i + 1];
      pnt[3].p3_vec = Temp_sky_vectors[t][i + 1];
      for (k = 0; k < 4; k++) {
        g3_CodePoint(&pnt[k]);
        pnt[k].p3_flags = 0;
      }

      for (k = 0; k < 4; k++)
        g3_DrawLine(GR_RGB(255, 255, 255), &pnt[k], &pnt[(k + 1) % 4]);
    }
  }
}
// Draws the atmosphere over a satellite
void DrawAtmosphereBlend(vector *pos, angle rotAngle, float w, float h, int bm, float r, float g, float b) {
  g3Point pnt;
  if (g3_RotatePoint(&pnt, pos) & CC_BEHIND)
    return;

  // create the rotation matrix
  matrix rotMatrix;
  vm_AnglesToMatrix(&rotMatrix, 0, 0, rotAngle);

  // get the view matrix
  matrix viewToWorld;
  g3_GetUnscaledMatrix(&viewToWorld);
  viewToWorld = ~viewToWorld;

  // combine the matrices into one
  matrix rotationToWorld = rotMatrix * viewToWorld;

  // setup the rotation vectors
  vector rotVectors[4];
  rotVectors[0].x = -w;
  rotVectors[0].y = h;
  rotVectors[1].x = w;
  rotVectors[1].y = h;
  rotVectors[2].x = w;
  rotVectors[2].y = -h;
  rotVectors[3].x = -w;
  rotVectors[3].y = -h;

  // rotate the points
  g3Point rotPoints[8], *pntList[8];
  int i;
  for (i = 0; i < 4; ++i) {
    rotVectors[i].z = 0.0f;
    rotVectors[i] = (rotVectors[i] * rotationToWorld) + (*pos);

    // setup the point
    g3_RotatePoint(&rotPoints[i], &rotVectors[i]);
    rotPoints[i].p3_flags |= PF_UV | PF_RGBA;
    rotPoints[i].p3_r = r;
    rotPoints[i].p3_g = g;
    rotPoints[i].p3_b = b;
    rotPoints[i].p3_a = 0.4f;

    pntList[i] = &rotPoints[i];
  }

  rotPoints[0].p3_u = 0.0f;
  rotPoints[0].p3_v = 0.0f;
  rotPoints[1].p3_u = 1.0f;
  rotPoints[1].p3_v = 0.0f;
  rotPoints[2].p3_u = 1.0f;
  rotPoints[2].p3_v = 1.0f;
  rotPoints[3].p3_u = 0.0f;
  rotPoints[3].p3_v = 1.0f;

  // and draw!!
  rend_SetLighting(LS_NONE);
  rend_SetFlatColor(Terrain_sky.sky_color);
  rend_SetAlphaType(AT_TEXTURE_VERTEX);
  rend_SetTextureType(TT_FLAT);
  g3_DrawPoly(4, pntList, bm);
}

// Draws our pretty stars
void DrawStars(matrix *vorient) {
  rend_SetLighting(LS_NONE);
  rend_SetTextureType(TT_FLAT);
  rend_SetOverlayType(OT_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetAlphaType(AT_VERTEX);
  rend_SetZBufferState(0);
  g3_SetFarClipZ(6000000);
  vector tempvec;
  if (Rendering_main_view && Terrain_sky.flags & TF_ROTATE_STARS && Terrain_sky.rotate_rate > 0) {
    matrix mat;
    vm_AnglesToMatrix(&mat, 0, Terrain_sky.rotate_rate * Frametime * (65536.0 / 360.0), 0);
    vm_Orthogonalize(&mat);
    for (int i = 0; i < MAX_STARS; i++) {
      vm_MatrixMulVector(&tempvec, &Terrain_sky.star_vectors[i], &mat);
      Terrain_sky.star_vectors[i] = tempvec;
    }
  }
  for (int i = 0; i < MAX_STARS; i++) {
    g3Point starpnt, lastpnt;
    vector streak_vec;
    float mag;
    // Rotate star
    tempvec = Terrain_sky.star_vectors[i];
    vm_MatrixMulVector(&starpnt.p3_vec, &tempvec, vorient);
    starpnt.p3_flags = PF_RGBA;
    // Get streaking line from last frame
    if (Rendering_main_view) {
      streak_vec = Last_frame_stars[i] - starpnt.p3_vec;
      mag = vm_GetMagnitudeFast(&streak_vec);
    } else {
      mag = 0.0f;
    }

    if (Rendering_main_view && mag > 9000.0) {
      streak_vec /= mag;
      float norm = (mag / 90000);
      if (norm > 1)
        norm = 1.0;
      float revnorm = 1.0 - (norm * 4);
      if (revnorm < 0)
        revnorm = 0;
      float color_norm = (.6 + (revnorm * .4));

      lastpnt.p3_vec = starpnt.p3_vec + ((norm * .75 * 90000) * streak_vec);
      lastpnt.p3_flags = PF_RGBA;
      lastpnt.p3_a = 0;
      starpnt.p3_a = color_norm;

      g3_CodePoint(&starpnt);
      g3_CodePoint(&lastpnt);
      rend_SetFlatColor(Terrain_sky.star_color[i]);
      g3_DrawSpecialLine(&starpnt, &lastpnt);
    } else {
      starpnt.p3_flags = PF_RGBA;
      if (!g3_CodePoint(&starpnt)) // only draw if this point is on screen
      {
        starpnt.p3_a = 1.0;

        g3_ProjectPoint(&starpnt);
        lastpnt = starpnt;
        lastpnt.p3_sx++;
        rend_SetFlatColor(Terrain_sky.star_color[i]);
        rend_DrawSpecialLine(&starpnt, &lastpnt);
        // rend_SetPixel (Terrain_sky.star_color[i],starpnt.p3_sx,starpnt.p3_sy);
      }
    }
    if (Rendering_main_view)
      Last_frame_stars[i] = starpnt.p3_vec;
  }
  rend_SetZBufferState(1);
  g3_SetFarClipZ(60000);
}
// Draw the suns,moons,stars, horizon, etc
void DrawSky(vector *veye, matrix *vorient) {
  int i, t;

  vector tempvec;

  rend_SetLighting(LS_GOURAUD);
  rend_SetZBufferState(0);
  rend_SetZBufferWriteMask(0);

  // If the sky is rotating, update the horizon vectors accordingly
  if (Rendering_main_view && Terrain_sky.flags & TF_ROTATE_SKY && Terrain_sky.rotate_rate > 0) {
    matrix mat;
    vm_AnglesToMatrix(&mat, 0, Terrain_sky.rotate_rate * Frametime * (65536.0 / 360.0), 0);
    vm_Orthogonalize(&mat);
    for (i = 0; i < 6; i++) {
      for (t = 0; t < MAX_HORIZON_PIECES; t++) {
        vector rot_vec;
        tempvec = Terrain_sky.horizon_vectors[t][i];
        vm_MatrixMulVector(&rot_vec, &tempvec, &mat);
        Terrain_sky.horizon_vectors[t][i] = rot_vec;
      }
    }
  }

  for (i = 0; i < 6; i++) {
    for (t = 0; t < MAX_HORIZON_PIECES; t++) {
      tempvec = Terrain_sky.horizon_vectors[t][i];
      tempvec.y -= veye->y * 0.5f;
      vm_MatrixMulVector(&Temp_sky_vectors[t][i], &tempvec, vorient);

      tempvec = Terrain_sky.horizon_vectors[t][i];
      tempvec.x += veye->x;
      tempvec.z += veye->z;
      tempvec.y += veye->y * 0.5f;
      Temp_sky_vectors_unrotated[t][i] = tempvec;
    }
  }
  float sr = (float)GR_COLOR_RED(Terrain_sky.sky_color) / 255.0;
  float sg = (float)GR_COLOR_GREEN(Terrain_sky.sky_color) / 255.0;
  float sb = (float)GR_COLOR_BLUE(Terrain_sky.sky_color) / 255.0;
  if (!Terrain_sky.textured) {
    DrawGouraudSky();
  } else {
    DrawTexturedSky();
  }

  if (Terrain_sky.flags & TF_STARS) {
    DrawStars(vorient);
  }

  if (Terrain_sky.flags & TF_SATELLITES) {
    rend_SetWrapType(WT_CLAMP);
    rend_SetColorModel(CM_MONO);

    // do satellites
    for (i = 0; i < Terrain_sky.num_satellites; i++) {
      int bm_handle = GetTextureBitmap(Terrain_sky.satellite_texture[i], 0);
      vector subvec = Terrain_sky.satellite_vectors[i] - *veye;
      float size = Terrain_sky.satellite_size[i];

      // Get position, angle of satellite
      vm_NormalizeVector(&subvec);
      tempvec = *veye + (subvec * (Terrain_sky.radius * 3));

#ifndef NEWEDITOR
      texture *tex = &GameTextures[Terrain_sky.satellite_texture[i]];
#else
      ned_texture_info *tex = &GameTextures[Terrain_sky.satellite_texture[i]];
#endif
      float str = Terrain_sky.satellite_r[i];
      float stg = Terrain_sky.satellite_g[i];
      float stb = Terrain_sky.satellite_b[i];
      float maxc = std::max({str, stg, stb});
      float r, g, b;
      if (maxc > 1.0) {
        r = str / maxc;
        g = stg / maxc;
        b = stb / maxc;
      } else {
        r = str;
        g = stg;
        b = stb;
      }
#ifndef NEWEDITOR
      // Draw halo
      if (Terrain_sky.satellite_flags[i] & TSF_HALO) {
        rend_SetZBufferWriteMask(0);
        DrawColoredRing(&tempvec, r, g, b, .4f, 0, size * 1.2, .3f, 0, 0);
        rend_SetZBufferWriteMask(1);
      }
#endif
      // Draw satellite
      if (tex->flags & TF_SATURATE)
        rend_SetAlphaType(AT_SATURATE_TEXTURE);
      else
        rend_SetAlphaType(AT_CONSTANT + AT_TEXTURE);
      rend_SetLighting(LS_NONE);
      rend_SetAlphaValue(tex->alpha * 255);
// Check to see if the user clicked on a satellite
#if (defined(EDITOR) || defined(NEWEDITOR))
      ddgr_color oldcolor;
      if (TSearch_on) {
        rend_SetPixel(GR_RGB(0, 255, 0), TSearch_x, TSearch_y);
        oldcolor = rend_GetPixel(TSearch_x, TSearch_y); // will be different in 15/16-bit color
      }
#endif

      g3_SetTriangulationTest(1);
      g3_DrawPlanarRotatedBitmap(&tempvec, &subvec, 0, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0),
                                 bm_handle);
      g3_SetTriangulationTest(0);

      // Draw atmosphere blend
      if (UseHardware) {
        if (Terrain_sky.satellite_flags[i] & TSF_ATMOSPHERE) {
          angvec angs;
          vm_ExtractAnglesFromMatrix(&angs, vorient);
          DrawAtmosphereBlend(&tempvec, angs.b, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle, sr,
                              sg, sb);
        }
      }

#if (defined(EDITOR) || defined(NEWEDITOR))
      if (TSearch_on) {
        if (rend_GetPixel(TSearch_x, TSearch_y) != oldcolor) {
          TSearch_seg = i;
          TSearch_found_type = TSEARCH_FOUND_SATELLITE;
        }
      }
#endif
    }
  }
#ifndef NEWEDITOR
  if ((Weather.flags & WEATHER_FLAGS_LIGHTNING) && Weather.lightning_sequence == 2) {
    DrawLightning();
    Weather.lightning_sequence = 0;
  }

  if ((Weather.flags & WEATHER_FLAGS_LIGHTNING) && Weather.lightning_sequence == 1) {
    DrawLightningSky();
    Weather.lightning_sequence = 2;
  }
#endif
  //	DrawCloudLayer();
#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_SKY))
    DrawWireframeSky();
#endif

  rend_SetAlphaValue(255);
  rend_SetZBufferState(1);
}

int AddRenderObjectToTerrainSeg(int n, int objnum);
// Checks to see if we should render objects and also sets which order the objects
// should be rendered in
void SortTerrainObjectsForRendering(int cellcount) {
  int i, segnum;
  object *obj;
#if (!defined(RELEASE) || defined(NEWEDITOR))
  for (i = 0; i < cellcount; i++)
    Terrain_seg_render_objs[Terrain_list[i].segment] = -1;
#endif

  // Go through each object and do trivial rejection
  for (i = 0; i <= Highest_object_index; i++) {
#if (!defined(RELEASE) || defined(NEWEDITOR))
    render_next[i] = -1;
#endif
    obj = &Objects[i];
    if (obj->type == OBJ_NONE)
      continue;
    if (obj->render_type == RT_NONE)
      continue;
    if (!OBJECT_OUTSIDE(obj))
      continue;
    // Ok, we know that we can see this point.  If its segment is in our list
    // then make this object draw right after this segment is drawn.  Otherwise
    // just draw it
    segnum = CELLNUM(obj->roomnum);
    ASSERT(segnum >= 0 && segnum <= (TERRAIN_WIDTH * TERRAIN_DEPTH));
    if (Terrain_rotate_list[segnum] == TS_FrameCount) {
      AddRenderObjectToTerrainSeg(segnum, i);
    } else
      AddRenderObjectToTerrainSeg(Terrain_list[cellcount - 1].segment, i);
  }
}
#if (defined(EDITOR) || defined(NEWEDITOR))
#define CROSS_WIDTH 8.0
#define CROSS_HEIGHT 8.0
void TerrainDrawCurrentVert(int tcell) {
  if (TerrainSelected[tcell]) {
    g3Point pnt;
    pnt.p3_flags = 0;
    pnt.p3_vec = World_point_buffer[tcell].p3_vec;
    g3_ProjectPoint(&pnt); // make sure projected

    rend_SetFlatColor(GR_RGB(0, 250, 0));
    rend_DrawLine(pnt.p3_sx - CROSS_WIDTH, pnt.p3_sy, pnt.p3_sx, pnt.p3_sy - CROSS_HEIGHT);
    rend_DrawLine(pnt.p3_sx, pnt.p3_sy - CROSS_HEIGHT, pnt.p3_sx + CROSS_WIDTH, pnt.p3_sy);
    rend_DrawLine(pnt.p3_sx + CROSS_WIDTH, pnt.p3_sy, pnt.p3_sx, pnt.p3_sy + CROSS_HEIGHT);
    rend_DrawLine(pnt.p3_sx, pnt.p3_sy + CROSS_HEIGHT, pnt.p3_sx - CROSS_WIDTH, pnt.p3_sy);
  }
}
#endif
#if (!defined(RELEASE) || defined(NEWEDITOR))
__inline void DrawTerrainOutline(int tcell, int nverts, g3Point **pointlist)
{
  int i;
  g3Point tpnt[256];
  g3Point *tpnt_list[256];
  for (i = 0; i < nverts; i++) {
    tpnt[i] = *pointlist[i];
    tpnt_list[i] = &tpnt[i];
  }
#if (defined(EDITOR) || defined(NEWEDITOR))
  if (TerrainSelected[tcell]) {
    for (i = 0; i < nverts - 1; i++)
      g3_DrawLine(GR_RGB(255, 255, 255), tpnt_list[i], tpnt_list[i + 1]);
    g3_DrawLine(GR_RGB(255, 255, 255), tpnt_list[i], tpnt_list[0]);
  } else
#endif
  {
    for (i = 0; i < nverts - 1; i++)
      g3_DrawLine(GR_RGB(128, 128, 128), tpnt_list[i], tpnt_list[i + 1]);
    g3_DrawLine(GR_RGB(128, 128, 128), tpnt_list[i], tpnt_list[0]);
  }
}
#endif
int TerrainSortingFunction(const terrain_render_info *a, terrain_render_info *b) { return b->z - a->z; }
void SortTerrainList(int cellcount) {
  int i, t, k;
  int lod, simplemul;
  int n[4];

  for (i = 0; i < cellcount; i++) {
    t = Terrain_list[i].segment;
    lod = Terrain_list[i].lod;
#if (!defined(RELEASE) || defined(NEWEDITOR))
    Terrain_seg_render_objs[t] = -1;
#endif

    simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
    Terrain_list[i].z = 0.0f;
    n[0] = t;
    n[1] = t + (TERRAIN_WIDTH * simplemul);
    n[2] = t + (TERRAIN_WIDTH * simplemul) + simplemul;
    n[3] = t + simplemul;
    for (k = 0; k < 4; k++)
      if (n[k] <= 65535)
        Terrain_list[i].z += World_point_buffer[n[k]].p3_vec.z;
    Terrain_list[i].z /= 4;
  }
  // Sort the faces
  qsort(Terrain_list, cellcount, sizeof(*Terrain_list), (int (*)(const void *, const void *))TerrainSortingFunction);
}
// Returns the number of points to rotate, plus the actual numbers of the points
// are returned in the "n" array
int BuildEdgeLists(int *n, int tlist_index) {
  int lod, simplemul;
  int t, k;
  int smul_x, smul_z; // for tracing the very edge of the terrain

  // Now match up all edges of the differing levels of detail
  int cx, cz;
  int transcount;
  int offset;
  int maplod;
  int start = 0;
  int seg;
  int answer;
  int edgecount = 0;
  int edge1, edge2;
  float delta, cury;
  int max_edge_size = 1 << (MAX_TERRAIN_LOD - 1);

  t = Terrain_list[tlist_index].segment;
  lod = Terrain_list[tlist_index].lod;
  simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
  ASSERT(simplemul <= max_edge_size);
  cx = t % TERRAIN_WIDTH;
  cz = t / TERRAIN_WIDTH;
  if (cx == TERRAIN_WIDTH - simplemul) {
    if (lod == MAX_TERRAIN_LOD - 1)
      return 0;

    smul_x = simplemul - 1;
  } else
    smul_x = simplemul;
  if (cz == TERRAIN_DEPTH - simplemul) {
    if (lod == MAX_TERRAIN_LOD - 1)
      return 0;

    smul_z = simplemul - 1;
  } else
    smul_z = simplemul;
  if (lod != MAX_TERRAIN_LOD - 1) {
    // Bottom edge
    // |       |
    // 2-------1

    Terrain_list[tlist_index].bottom_edge = 0;
    Terrain_list[tlist_index].bottom_count = 0;
    transcount = 0;
    if (cz != 0) {
      edge1 = t + smul_x;
      edge2 = t;
      delta = (Terrain_seg[edge2].mody - Terrain_seg[edge1].mody) / smul_x;
      cury = Terrain_seg[edge1].mody;

      offset = ((cz - 1) * TERRAIN_WIDTH) + cx + smul_x;
      for (k = 0; k < smul_x; k++, cury += delta) {
        maplod = TerrainJoinMap[offset - k];
        answer = TerrainEdgeTest[maplod][k + simplemul - smul_x];
        if (answer || k == 0) {
          seg = t + smul_x - k;
          n[transcount + start] = seg;
          Terrain_seg[seg].mody = cury;

          Terrain_list[tlist_index].bottom_edge |= (1 << k);
          Terrain_list[tlist_index].bottom_count++;

          transcount++;
        }
      }
    } else {
      Terrain_list[tlist_index].bottom_edge |= 1;
      Terrain_list[tlist_index].bottom_count++;
      seg = t + smul_x;
      n[transcount + start] = seg;
      transcount++;
    }

    start += transcount;
    // Right edge
    //---1
    //	  |
    //	  |
    //-- 2

    Terrain_list[tlist_index].right_edge = 0;
    Terrain_list[tlist_index].right_count = 0;
    transcount = 0;
    offset = ((cz + smul_z) * TERRAIN_WIDTH) + cx + smul_x;
    edge1 = t + smul_x + (smul_z * TERRAIN_WIDTH);
    edge2 = t + smul_x;
    delta = (Terrain_seg[edge2].mody - Terrain_seg[edge1].mody) / smul_z;
    cury = Terrain_seg[edge1].mody;
    for (k = 0; k < smul_z; k++, cury += delta) {
      maplod = TerrainJoinMap[offset - (k * TERRAIN_WIDTH)];
      answer = TerrainEdgeTest[maplod][k + simplemul - smul_z];
      if (answer || k == 0) {
        seg = t + smul_x + ((smul_z - k) * TERRAIN_WIDTH);
        n[transcount + start] = seg;
        Terrain_seg[seg].mody = cury;
        Terrain_list[tlist_index].right_edge |= (1 << k);
        Terrain_list[tlist_index].right_count++;
        transcount++;
      }
    }
    start += transcount;
    // Top edge
    // 1--------2
    // |        |

    Terrain_list[tlist_index].top_edge = 0;
    Terrain_list[tlist_index].top_count = 0;
    transcount = 0;
    offset = cx + ((cz + smul_z) * TERRAIN_WIDTH);
    edge1 = t + (smul_z * TERRAIN_WIDTH);
    edge2 = t + smul_x + (smul_z * TERRAIN_WIDTH);
    delta = (Terrain_seg[edge2].mody - Terrain_seg[edge1].mody) / smul_x;
    cury = Terrain_seg[edge1].mody;
    for (k = 0; k < smul_x; k++, cury += delta) {
      maplod = TerrainJoinMap[offset + k];
      answer = TerrainEdgeTest[maplod][k];
      if (answer || k == 0) {
        seg = (t + k) + (smul_z * TERRAIN_WIDTH);
        n[transcount + start] = seg;
        Terrain_seg[seg].mody = cury;
        Terrain_list[tlist_index].top_edge |= (1 << k);
        Terrain_list[tlist_index].top_count++;
        transcount++;
      }
    }
    start += transcount;
    // left edge
    // 2----
    // |
    // |
    // 1----
    Terrain_list[tlist_index].left_edge = 0;
    Terrain_list[tlist_index].left_count = 0;
    transcount = 0;
    if (cx != 0) {
      offset = (cz * TERRAIN_WIDTH) + cx - 1;
      edge1 = t;
      edge2 = t + (smul_z * TERRAIN_WIDTH);
      delta = (Terrain_seg[edge2].mody - Terrain_seg[edge1].mody) / smul_z;
      cury = Terrain_seg[edge1].mody;
      for (k = 0; k < smul_z; k++, cury += delta) {
        maplod = TerrainJoinMap[offset + (k * TERRAIN_WIDTH)];
        answer = TerrainEdgeTest[maplod][k];
        if (answer || k == 0) {
          seg = t + (k * TERRAIN_WIDTH);
          n[transcount + start] = seg;
          Terrain_seg[seg].mody = cury;
          Terrain_list[tlist_index].left_edge |= (1 << k);
          Terrain_list[tlist_index].left_count++;
          transcount++;
        }
      }
    } else {
      seg = t;
      n[transcount + start] = seg;
      Terrain_list[tlist_index].left_edge |= 1;
      Terrain_list[tlist_index].left_count++;
      transcount++;
    }

    edgecount = start + transcount;
  } else {
    n[0] = t;
    n[1] = t + TERRAIN_WIDTH;
    n[2] = t + TERRAIN_WIDTH + 1;
    n[3] = t + 1;
    Terrain_list[tlist_index].left_edge = 1;
    Terrain_list[tlist_index].bottom_edge = 1;
    Terrain_list[tlist_index].right_edge = 1;
    Terrain_list[tlist_index].top_edge = 1;
    edgecount = 4;
  }
  return edgecount;
}
// This function rotates all the points that we can see.
// If a cell is a low-res cell, then we rotate all the points down each edge
// of the cell to make sure any higher res blocks that touch the cell don't
// appear with cracks
vector Terrain_alter_vec = {19, -19, 19};
void RotateTerrainList(int cellcount, bool from_automap) {
  int lod, simplemul, edgecount;
  int i, n[200], t, k, cx, cz;
  vector camlight = Terrain_sky.lightsource;
  vm_NormalizeVector(&camlight);
  // Reset all modified y values for the corners of each cell
  for (i = 0; i < cellcount; i++) {
    int ax, az;
    t = Terrain_list[i].segment;
    lod = Terrain_list[i].lod;
    simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
    cx = t & (TERRAIN_WIDTH - 1);
    cz = t >> 8;

    ax = az = simplemul;

    if (cx + ax >= TERRAIN_WIDTH)
      ax = (TERRAIN_WIDTH - 1) - cx;
    if (cz + az >= TERRAIN_DEPTH)
      az = (TERRAIN_DEPTH - 1) - cz;

    n[0] = t;
    n[1] = t + (TERRAIN_WIDTH * az);
    n[2] = t + (az * TERRAIN_WIDTH) + ax;
    n[3] = t + ax;
    // This could be in a loop, but I unrolled it for speed
    Terrain_seg[n[0]].mody = Terrain_seg[n[0]].y;
    Terrain_seg[n[1]].mody = Terrain_seg[n[1]].y;
    Terrain_seg[n[2]].mody = Terrain_seg[n[2]].y;
    Terrain_seg[n[3]].mody = Terrain_seg[n[3]].y;
    if (StateLimited || from_automap) // Setup for sorting later
    {
      int unique_id;
      unique_id = Terrain_tex_seg[Terrain_seg[t].texseg_index].tex_index;
      State_elements[i].facenum = i;
      State_elements[i].sort_key = unique_id + (Terrain_seg[t].lm_quad << 24);
    }
  }
  for (i = 0; i < cellcount; i++) {
    edgecount = BuildEdgeLists(n, i);
    for (k = 0; k < edgecount; k++) {
      if (Terrain_rotate_list[n[k]] != TS_FrameCount) {
        Terrain_rotate_list[n[k]] = TS_FrameCount;
        GlobalTransCount++;

        cx = n[k] % TERRAIN_WIDTH;
        cz = n[k] / TERRAIN_WIDTH;

        World_point_buffer[n[k]].p3_flags = PF_UV | PF_UV2;
        if (Terrain_seg[n[k]].mody == Terrain_seg[n[k]].y) {
          GetPreRotatedPoint(&World_point_buffer[n[k]], cx, cz, Terrain_seg[n[k]].ypos);
        } else {
          GetSpecialRotatedPoint(&World_point_buffer[n[k]], cx, cz, Terrain_seg[n[k]].mody);
        }

        if (Viewer_object->effect_info && (Viewer_object->effect_info->type_flags & EF_DEFORM)) {
          float val = (((ps_rand() % 1000) - 500.0f) / 500.0f) * Viewer_object->effect_info->deform_time;
          vector jitterVec = Terrain_alter_vec * (Viewer_object->effect_info->deform_range * val);
          World_point_buffer[n[k]].p3_vec += jitterVec;
          World_point_buffer[n[k]].p3_vecPreRot += jitterVec;
        }
        g3_CodePoint(&World_point_buffer[n[k]]);
      }
    }
  }
}

// Puts a 1 in upperleft,lowerright if those triangles are visible
void TerrainCellVisible(int index, int *upper_left, int *lower_right) {
  int seg = Terrain_list[index].segment;
  int lod = Terrain_list[index].lod;
  int simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
  int cx, cz, smul_x, smul_z;

  vector tempv;
  vector *corner[4];

  cx = seg % TERRAIN_WIDTH;
  cz = seg / TERRAIN_WIDTH;
  if (cx + simplemul == TERRAIN_WIDTH)
    smul_x = simplemul - 1;
  else
    smul_x = simplemul;
  if (cz + simplemul == TERRAIN_DEPTH)
    smul_z = simplemul - 1;
  else
    smul_z = simplemul;

  // Note - this is upper left and proceeds clockwise
  corner[0] = &World_point_buffer[seg + (TERRAIN_WIDTH * smul_z)].p3_vec;
  corner[1] = &World_point_buffer[seg + (TERRAIN_WIDTH * smul_z) + smul_x].p3_vec;
  corner[2] = &World_point_buffer[seg].p3_vec;
  corner[3] = &World_point_buffer[seg + smul_x].p3_vec;

  vm_GetPerp(&tempv, corner[0], corner[1], corner[2]);
  if ((tempv * *corner[1]) < 0)
    *upper_left = 1;
  else
    *upper_left = 0;

  // Now do lower right
  vm_GetPerp(&tempv, corner[2], corner[1], corner[3]);
  if ((tempv * *corner[1]) < 0)
    *lower_right = 1;
  else
    *lower_right = 0;
}

void DisplayTerrainList(int cellcount, bool from_automap) {
  int total = 0, on, t, i, lod, simplemul;
  int bm_handle;
  bool draw_lightmap = false;
  int savecell;
  int obj_to_draw;
  Terrain_objects_drawn = 0;
  rend_SetWrapType(WT_WRAP);
  if (!UseHardware)
    rend_SetColorModel(CM_MONO);
  else {
    rend_SetColorModel(CM_RGB);
    rend_SetTextureType(TT_LINEAR);
    rend_SetAlphaType(ATF_CONSTANT + ATF_TEXTURE);
    rend_SetLighting(LS_NONE);
    if (!StateLimited || UseMultitexture)
      draw_lightmap = true;
  }
  RotateTerrainList(cellcount, from_automap);
  if (!UseHardware) {
    SortTerrainList(cellcount);
    SortTerrainObjectsForRendering(cellcount);
  }
  // If state limited, sort by texture
  if (StateLimited || from_automap)
    SortStates(State_elements, cellcount);
  if (from_automap) {
    savecell = cellcount;
    cellcount = 0;
  }

  for (i = 0; i < cellcount; i++) {
    int cx, cz;
    int seg_to_render;
    if (StateLimited)
      seg_to_render = State_elements[i].facenum;
    else
      seg_to_render = i;
    t = Terrain_list[seg_to_render].segment;
    lod = Terrain_list[seg_to_render].lod;
    simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);

    cx = t % TERRAIN_WIDTH;
    cz = t / TERRAIN_WIDTH;

    if (cx < TERRAIN_WIDTH - simplemul && cz < TERRAIN_DEPTH - simplemul || lod != (MAX_TERRAIN_LOD - 1)) {
      int ul, lr; // upper_left,lower_right
      if (Terrain_seg[t].flags & TF_INVISIBLE)
        if (!Show_invisible_terrain)
          goto draw_objects; // bad! No gotos! -JL
      // Check to see if these triangles are visible if they're the smallest lod
      TerrainCellVisible(seg_to_render, &ul, &lr);

      total += (ul + lr);
      if (ul == 0 && lr == 0)
        goto draw_objects;

      bm_handle = GetTextureBitmap(Terrain_tex_seg[Terrain_seg[t].texseg_index].tex_index, 0);

      if (UseHardware) {
        if (draw_lightmap)
          on = DrawTerrainTrianglesHardware(seg_to_render, bm_handle, ul, lr);
        else
          on = DrawTerrainTrianglesHardwareNoLight(seg_to_render, bm_handle, ul, lr);

      } else
        on = DrawTerrainTrianglesSoftware(seg_to_render, bm_handle, ul, lr);
    }

  draw_objects:;
// Now draw any objects in this segment
#if (!defined(RELEASE) || defined(NEWEDITOR))
    if (!UseHardware) {
      obj_to_draw = Terrain_seg_render_objs[t];

      while (obj_to_draw != -1) {

        if (Objects[obj_to_draw].type != OBJ_ROOM)
          RenderObject(&Objects[obj_to_draw]);
        obj_to_draw = render_next[obj_to_draw];
      }
      Terrain_seg_render_objs[t] = -1;
    }
#endif
  }
#if (defined(EDITOR) || defined(NEWEDITOR))
  if (!UseHardware) {
#if (!defined(RELEASE) || defined(NEWEDITOR))
    for (i = 0; i < cellcount; i++) {
      t = Terrain_list[i].segment;
      Terrain_seg_render_objs[t] = -1;
    }
#endif

    if ((View_mode == EDITOR_MODE) && OUTLINE_ON(OM_TERRAIN)) {
      for (i = 0; i < cellcount; i++) {
        t = Terrain_list[i].segment;
        if (TerrainSelected[t] && Terrain_rotate_list[t] == TS_FrameCount)
          TerrainDrawCurrentVert(t);
      }
    }
  }
#endif
  // Draw lightmaps if this is state limited
  if ((UseHardware && !draw_lightmap) || from_automap) {
    if (from_automap) {
      rend_SetAlphaType(AT_CONSTANT);
      cellcount = savecell;
    } else
      rend_SetAlphaType(AT_LIGHTMAP_BLEND);
    rend_SetAlphaValue(255);
    rend_SetLighting(LS_NONE);
    rend_SetOverlayType(OT_NONE);
    rend_SetTextureType(TT_PERSPECTIVE);
    rend_SetWrapType(WT_WRAP);
    rend_SetZBias(-.5f);

    for (i = 0; i < cellcount; i++) {
      int ul, lr;
      int seg_to_render;
      seg_to_render = State_elements[i].facenum;
      TerrainCellVisible(seg_to_render, &ul, &lr);
      if (ul == 0 && lr == 0)
        continue;
      DrawTerrainLightmapsHardware(seg_to_render, ul, lr);
    }
    rend_SetZBias(0);
  }

  rend_SetOverlayType(OT_NONE);
  rend_SetWrapType(WT_WRAP);

  mprintf_at(2, 1, 0, "%5d cells", cellcount);
  mprintf_at(2, 2, 0, "%5d trans", GlobalTransCount);
  mprintf_at(2, 3, 0, "Tdepth=%5d", TotalDepth);
}
// Arrays for drawing
static int src[256];
static g3Point base[256];
static g3Point *slist[256];
// Draws the 2 triangles of the Terrainlist[index] (software)
int DrawTerrainTrianglesSoftware(int index, int bm_handle, int upper_left, int lower_right) {
  /*
  #ifndef __LINUX__
          int i,tlist[4],close=0,lit=0;
          float closest_z=9999;
          int color;
          int n=Terrain_list[index].segment;
          int lod=Terrain_list[index].lod;

          terrain_segment *tseg=&Terrain_seg[n];
          terrain_tex_segment *texseg=&Terrain_tex_seg[tseg->texseg_index];
          int rotation=texseg->rotation & 0x0F;
          int tile=texseg->rotation >> 4;
          int simplemul=1<<((MAX_TERRAIN_LOD-1)-lod);
          int cx,cz,smul_x,smul_z;
          #if (defined(EDITOR) || defined(NEWEDITOR))
                  ddgr_color oldcolor;
          #endif
          cx=n%TERRAIN_WIDTH;
          cz=n/TERRAIN_WIDTH;
          int subx=cx % MAX_LOD_SIZE;
          int subz=(MAX_LOD_SIZE-1)-((cz+(simplemul-1)) % MAX_LOD_SIZE);
          if (cx+simplemul==TERRAIN_WIDTH)
                  smul_x=simplemul-1;
          else
                  smul_x=simplemul;
          if (cz+simplemul==TERRAIN_DEPTH)
                  smul_z=simplemul-1;
          else
                  smul_z=simplemul;

          // Note - this is upper left and proceeds lockwise
          tlist[0]=n+(TERRAIN_WIDTH*smul_z);
          tlist[1]=n+(TERRAIN_WIDTH*smul_z)+(smul_x);
          tlist[2]=n+(smul_x);
          tlist[3]=n;
          rend_SetOverlayType (OT_NONE);
          for (close=0,i=0;i<4;i++)
          {
                  base[i]=*((g3Point *)&World_point_buffer[tlist[i]]);
                  base[i].p3_flags|=(PF_L|PF_RGBA);
                  base[i].p3_l=Ubyte_to_float[Terrain_seg[tlist[i]].l];

                  // only do perspective if all the points are inside our range
                  if (!UseHardware)
                  {
                          if (base[i].p3_vec.z<TERRAIN_PERSPECTIVE_TEXTURE_DEPTH)
                                  close=1;
                          if (base[i].p3_vec.z<closest_z)
                                  closest_z=base[i].p3_vec.z;
                  }
          }
          base[0].p3_u=TerrainUSpeedup[rotation][subz*LOD_ROW_SIZE+subx]*tile;
          base[0].p3_v=TerrainVSpeedup[rotation][subz*LOD_ROW_SIZE+subx]*tile;
          base[1].p3_u=TerrainUSpeedup[rotation][subz*LOD_ROW_SIZE+subx+simplemul]*tile;
          base[1].p3_v=TerrainVSpeedup[rotation][subz*LOD_ROW_SIZE+subx+simplemul]*tile;
          base[2].p3_u=TerrainUSpeedup[rotation][((subz+simplemul)*LOD_ROW_SIZE)+subx+simplemul]*tile;
          base[2].p3_v=TerrainVSpeedup[rotation][((subz+simplemul)*LOD_ROW_SIZE)+subx+simplemul]*tile;
          base[3].p3_u=TerrainUSpeedup[rotation][((subz+simplemul)*LOD_ROW_SIZE)+subx]*tile;
          base[3].p3_v=TerrainVSpeedup[rotation][((subz+simplemul)*LOD_ROW_SIZE)+subx]*tile;

          rend_SetLighting (Lighting_on?LS_GOURAUD:LS_NONE);

          #if (defined(EDITOR) || defined(NEWEDITOR))
                  if (TSearch_on)
                  {
                          rend_SetPixel(GR_RGB(0,255,0),TSearch_x,TSearch_y);
                          oldcolor = rend_GetPixel(TSearch_x,TSearch_y);			//will be different in
  15/16-bit color
                  }
          #endif

          // Make sure the triangle faces us and if so draw
          // Upper left triangle
          if (!upper_left)
                  goto draw_lower_right;
          src[0]=0;
          src[1]=1;
          src[2]=3;

          for (lit=0,i=0;i<3;i++)
          {
                  if (base[src[i]].p3_z<=Far_fog_border)
                          lit=1;

                  slist[i]=&base[src[i]];
          }

          if (!lit && Lighting_on)
          {
                  rend_SetTextureType(TT_FLAT);
                  rend_SetFlatColor (0);
                  g3_DrawPoly(3,slist,0);
          }
          else
          {
                  // If we're past our texturing distance, flat shade!
                  if (closest_z>Terrain_texture_distance)
                  {
                          rend_SetTextureType (TT_FLAT);
                          int lightval=Ubyte_to_float [tseg->l]*(MAX_TEXTURE_SHADES-1);
                          int pix=*bm_data(bm_handle,0);
                          int fadepixel=(TexShadeTable16[lightval][pix>>8])+TexShadeTable8[lightval][pix & 0xFF];
                          color=GR_16_TO_COLOR (fadepixel);
                          rend_SetFlatColor (color);
                          g3_DrawPoly(3,slist,0);
                  }
                  else
                  {
                          if (close)
                                  rend_SetTextureType (TT_PERSPECTIVE);
                          else
                                  rend_SetTextureType (TT_LINEAR);

                          g3_DrawPoly(3,slist,bm_handle);
                  }
          }
  #if (!defined(RELEASE) || defined(NEWEDITOR))
                  if (OUTLINE_ON(OM_TERRAIN))
                          DrawTerrainOutline(n,3, slist);
  #endif
          // Now do lower right triangle
          draw_lower_right:
          if (!lower_right)
                  return 0;
          src[0]=3;
          src[1]=1;
          src[2]=2;
          for (lit=0,i=0;i<3;i++)
          {
                  if (base[src[i]].p3_z<=Far_fog_border)
                          lit=1;

                  slist[i]=&base[src[i]];
          }
          if (!lit && Lighting_on)
          {
                  rend_SetTextureType(TT_FLAT);
                  rend_SetFlatColor (0);
                  g3_DrawPoly(3,slist,0);
          }
          else
          {
                  // If we're past our texturing distance, flat shade!
                  if (closest_z>Terrain_texture_distance)
                  {
                          rend_SetTextureType (TT_FLAT);
                          int lightval=Ubyte_to_float[tseg->l]*(MAX_TEXTURE_SHADES-1);
                          int pix=*bm_data(bm_handle,0);
                          int fadepixel=(TexShadeTable16[lightval][pix>>8])+TexShadeTable8[lightval][pix & 0xFF];
                          color=GR_16_TO_COLOR (fadepixel);
                          rend_SetFlatColor (color);
                          g3_DrawPoly(3,slist,0);
                  }
                  else
                  {
                          if (close)
                                  rend_SetTextureType (TT_PERSPECTIVE);
                          else
                                  rend_SetTextureType (TT_LINEAR);
                  }

                  g3_DrawPoly(3,slist,bm_handle);
          }

          #if (!defined(RELEASE) || defined(NEWEDITOR))
          if (OUTLINE_ON(OM_TERRAIN))
                  DrawTerrainOutline(n,3, slist);
          #endif
          #if (defined(EDITOR) || defined(NEWEDITOR))
                  if (TSearch_on)
                  {
                          if (rend_GetPixel(TSearch_x,TSearch_y) != oldcolor)
                          {
                                  TSearch_seg = n;
                                  TSearch_found_type=TSEARCH_FOUND_TERRAIN;
                          }
                  }
          #endif
  #endif//__LINUX__
          */
  return 0;
}
// Draws the 2 triangles of the Terrainlist[index] (hardware)
int DrawTerrainTrianglesHardware(int index, int bm_handle, int upper_left, int lower_right) {
  int i;
  int cur_seg;
  int n = Terrain_list[index].segment;
  int lod = Terrain_list[index].lod;
  int bottom_start, left_start, right_start;
  int point_count = 0;
  int points_this_triangle = 0;

  terrain_segment *tseg = &Terrain_seg[n];
  terrain_tex_segment *texseg = &Terrain_tex_seg[tseg->texseg_index];
  int rotator = texseg->rotation & 0x0F;
  int tile = texseg->rotation >> 4;
  int simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
  int cx, cz, smul_x, smul_z;
  cx = n % TERRAIN_WIDTH;
  cz = n / TERRAIN_WIDTH;

  // Get lightmap coordinates
  float lightmap_u = (cx % 128) / 128.0;
  float lightmap_v = (128 - ((cz % 128) + simplemul)) / 128.0;
  float uvadjust;
  int draw_big_square = 0;
  int subx = cx % MAX_LOD_SIZE;
  int subz = (MAX_LOD_SIZE - 1) - ((cz + (simplemul - 1)) % MAX_LOD_SIZE);
  bool solid_square = 1;
  int testt = 0, testr = 0, testb = 0, testl = 0;
  // Check to make sure we don't access memory that is off the map
  if (cx + simplemul == TERRAIN_WIDTH) {
    smul_x = simplemul - 1;
    solid_square = 0;
  } else
    smul_x = simplemul;
  if (cz + simplemul == TERRAIN_DEPTH) {
    solid_square = 0;
    smul_z = simplemul - 1;
  } else
    smul_z = simplemul;
  // Build a list of points for our polygon.  We must do it this way to
  // prevent tjoint cracking
  // Do simpler operation if at highest level of detail
  if (lod == (MAX_TERRAIN_LOD - 1)) {
    uvadjust = (simplemul / 128.0);
    cur_seg = n + (TERRAIN_WIDTH * smul_z);
    base[0] = World_point_buffer[cur_seg];

    cur_seg = n + (TERRAIN_WIDTH * smul_z) + smul_x;
    base[1] = World_point_buffer[cur_seg];

    cur_seg = n + smul_x;
    base[2] = World_point_buffer[cur_seg];

    base[3] = World_point_buffer[n];

    base[0].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx];
    base[0].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx];
    base[1].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx + 1];
    base[1].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx + 1];
    base[2].p3_u = tile * TerrainUSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx + 1];
    base[2].p3_v = tile * TerrainVSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx + 1];
    base[3].p3_u = tile * TerrainUSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx];
    base[3].p3_v = tile * TerrainVSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx];

    base[0].p3_u2 = lightmap_u;
    base[0].p3_v2 = lightmap_v;
    base[1].p3_u2 = lightmap_u + uvadjust;
    base[1].p3_v2 = lightmap_v;
    base[2].p3_u2 = lightmap_u + uvadjust;
    base[2].p3_v2 = lightmap_v + uvadjust;

    base[3].p3_u2 = lightmap_u;
    base[3].p3_v2 = lightmap_v + uvadjust;
  } else {
    uvadjust = (simplemul / 128.0) / simplemul;
    float uvmul = uvadjust * simplemul;
    if (solid_square) {
      right_start = Terrain_list[index].top_count;
      bottom_start = right_start + Terrain_list[index].right_count;
      left_start = bottom_start + Terrain_list[index].bottom_count;
      point_count = left_start + Terrain_list[index].left_count;

      for (i = 0; i < simplemul; i++) {
        // Top edge
        if (Terrain_list[index].top_edge & (1 << i)) {
          cur_seg = n + i + (TERRAIN_WIDTH * smul_z);
          base[testt] = World_point_buffer[cur_seg];

          base[testt].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];
          base[testt].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];

          base[testt].p3_u2 = lightmap_u + (i * uvadjust);
          base[testt].p3_v2 = lightmap_v;
          slist[testt] = &base[testt];
          testt++;
        }
        // Right edge
        if (Terrain_list[index].right_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * (smul_z - i)) + smul_x;
          base[right_start + testr] = World_point_buffer[cur_seg];

          base[right_start + testr].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + simplemul];
          base[right_start + testr].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + simplemul];

          base[right_start + testr].p3_u2 = lightmap_u + uvmul;
          base[right_start + testr].p3_v2 = lightmap_v + (i * uvadjust);
          slist[right_start + testr] = &base[right_start + testr];
          testr++;
        }
        // Bottom edge
        if (Terrain_list[index].bottom_edge & (1 << i)) {
          cur_seg = n + (smul_x - i);
          base[bottom_start + testb] = World_point_buffer[cur_seg];

          base[bottom_start + testb].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + simplemul) * LOD_ROW_SIZE) + (subx + simplemul) - i];
          base[bottom_start + testb].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + simplemul) * LOD_ROW_SIZE) + (subx + simplemul) - i];
          base[bottom_start + testb].p3_u2 = lightmap_u + uvmul - (i * uvadjust);
          base[bottom_start + testb].p3_v2 = lightmap_v + uvmul;
          slist[bottom_start + testb] = &base[bottom_start + testb];
          testb++;
        }
        // left edge
        if (Terrain_list[index].left_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * i);
          base[left_start + testl] = World_point_buffer[cur_seg];

          base[left_start + testl].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + simplemul - i) * LOD_ROW_SIZE) + subx];
          base[left_start + testl].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + simplemul - i) * LOD_ROW_SIZE) + subx];

          base[left_start + testl].p3_u2 = lightmap_u;
          base[left_start + testl].p3_v2 = lightmap_v + uvmul - (i * uvadjust);
          slist[left_start + testl] = &base[left_start + testl];
          testl++;
        }
      }
    } else {
      right_start = Terrain_list[index].top_count;
      bottom_start = right_start + Terrain_list[index].right_count;
      left_start = bottom_start + Terrain_list[index].bottom_count;
      point_count = left_start + Terrain_list[index].left_count;

      for (i = 0; i < smul_x; i++) {
        // top edge
        if (Terrain_list[index].top_edge & (1 << i)) {
          cur_seg = n + i + (TERRAIN_WIDTH * smul_z);
          base[testt] = World_point_buffer[cur_seg];

          base[testt].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];
          base[testt].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE];

          base[testt].p3_u2 = lightmap_u + (i * uvadjust);
          base[testt].p3_v2 = lightmap_v;
          slist[testt] = &base[testt];
          testt++;
        }
        // Bottom edge
        if (Terrain_list[index].bottom_edge & (1 << i)) {
          cur_seg = n + (smul_x - i);
          base[bottom_start + testb] = World_point_buffer[cur_seg];

          base[bottom_start + testb].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + smul_z) * LOD_ROW_SIZE) + subx + smul_x - i];
          base[bottom_start + testb].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + smul_z) * LOD_ROW_SIZE) + subx + smul_x - i];
          base[bottom_start + testb].p3_u2 = lightmap_u + uvmul - (i * uvadjust);
          base[bottom_start + testb].p3_v2 = lightmap_v + uvmul;
          slist[bottom_start + testb] = &base[bottom_start + testb];
          testb++;
        }
      }

      for (i = 0; i < smul_z; i++) {
        // Right edge
        if (Terrain_list[index].right_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * (smul_z - i)) + smul_x;
          base[right_start + testr] = World_point_buffer[cur_seg];

          base[right_start + testr].p3_u = tile * TerrainUSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + smul_x];
          base[right_start + testr].p3_v = tile * TerrainVSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + smul_x];

          base[right_start + testr].p3_u2 = lightmap_u + uvmul;
          base[right_start + testr].p3_v2 = lightmap_v + (i * uvadjust);
          slist[right_start + testr] = &base[right_start + testr];
          testr++;
        }
        // left edge
        if (Terrain_list[index].left_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * i);
          base[left_start + testl] = World_point_buffer[cur_seg];

          base[left_start + testl].p3_u = tile * TerrainUSpeedup[rotator][((subz + smul_z - i) * LOD_ROW_SIZE) + subx];
          base[left_start + testl].p3_v = tile * TerrainVSpeedup[rotator][((subz + smul_z - i) * LOD_ROW_SIZE) + subx];

          base[left_start + testl].p3_u2 = lightmap_u;
          base[left_start + testl].p3_v2 = lightmap_v + uvmul - (i * uvadjust);
          slist[left_start + testl] = &base[left_start + testl];
          testl++;
        }
      }
    }
  }

  rend_SetOverlayType(OT_BLEND);
  rend_SetOverlayMap(TerrainLightmaps[tseg->lm_quad]);

  // Make sure the triangle faces us and if so draw
  // Upper left triangle
  if (lod != (MAX_TERRAIN_LOD - 1))
    draw_big_square = 1;
  if (!upper_left && !draw_big_square)
    goto draw_lower_right;

  if (lod == (MAX_TERRAIN_LOD - 1)) {
    slist[0] = &base[0];
    slist[1] = &base[1];
    slist[2] = &base[3];
    points_this_triangle = 3;
  } else {
    points_this_triangle = point_count;
  }

  g3_DrawPoly(points_this_triangle, slist, bm_handle);
#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_TERRAIN))
    DrawTerrainOutline(n, points_this_triangle, slist);
#endif
  // If we're LOD'd, we've already drawn our 1 polygon.  Return!
  if (draw_big_square)
    return 0;

// Now do lower right triangle
draw_lower_right:
  if (!lower_right)
    return 0;
  slist[0] = &base[3];
  slist[1] = &base[1];
  slist[2] = &base[2];
  points_this_triangle = 3;

  g3_DrawPoly(points_this_triangle, slist, bm_handle);

#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_TERRAIN))
    DrawTerrainOutline(n, points_this_triangle, slist);
#endif
  return 0;
}
// Draws the 2 triangles of the Terrainlist[index] (hardware)
int DrawTerrainTrianglesHardwareNoLight(int index, int bm_handle, int upper_left, int lower_right) {
  int i;
  int cur_seg;
  int n = Terrain_list[index].segment;
  int lod = Terrain_list[index].lod;
  int bottom_start, left_start, right_start;
  int point_count = 0;
  int points_this_triangle = 0;

  terrain_segment *tseg = &Terrain_seg[n];
  terrain_tex_segment *texseg = &Terrain_tex_seg[tseg->texseg_index];
  int rotator = texseg->rotation & 0x0F;
  int tile = texseg->rotation >> 4;
  int simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
  int cx, cz, smul_x, smul_z;
  cx = n % TERRAIN_WIDTH;
  cz = n / TERRAIN_WIDTH;

  int draw_big_square = 0;
  int subx = cx % MAX_LOD_SIZE;
  int subz = (MAX_LOD_SIZE - 1) - ((cz + (simplemul - 1)) % MAX_LOD_SIZE);
  bool solid_square = 1;
  int testt = 0, testr = 0, testb = 0, testl = 0;
  // Check to make sure we don't access memory that is off the map
  if (cx + simplemul == TERRAIN_WIDTH) {
    smul_x = simplemul - 1;
    solid_square = 0;
  } else
    smul_x = simplemul;
  if (cz + simplemul == TERRAIN_DEPTH) {
    solid_square = 0;
    smul_z = simplemul - 1;
  } else
    smul_z = simplemul;
  // Build a list of points for our polygon.  We must do it this way to
  // prevent tjoint cracking
  // Do simpler operation if at highest level of detail
  if (lod == (MAX_TERRAIN_LOD - 1)) {
    cur_seg = n + (TERRAIN_WIDTH * smul_z);
    base[0] = World_point_buffer[cur_seg];

    cur_seg = n + (TERRAIN_WIDTH * smul_z) + smul_x;
    base[1] = World_point_buffer[cur_seg];

    cur_seg = n + smul_x;
    base[2] = World_point_buffer[cur_seg];

    base[3] = World_point_buffer[n];

    base[0].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx];
    base[0].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx];
    base[1].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx + 1];
    base[1].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx + 1];
    base[2].p3_u = tile * TerrainUSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx + 1];
    base[2].p3_v = tile * TerrainVSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx + 1];
    base[3].p3_u = tile * TerrainUSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx];
    base[3].p3_v = tile * TerrainVSpeedup[rotator][(subz + 1) * LOD_ROW_SIZE + subx];
  } else {
    if (solid_square) {
      right_start = Terrain_list[index].top_count;
      bottom_start = right_start + Terrain_list[index].right_count;
      left_start = bottom_start + Terrain_list[index].bottom_count;
      point_count = left_start + Terrain_list[index].left_count;

      for (i = 0; i < simplemul; i++) {
        // Top edge
        if (Terrain_list[index].top_edge & (1 << i)) {
          cur_seg = n + i + (TERRAIN_WIDTH * smul_z);
          base[testt] = World_point_buffer[cur_seg];

          base[testt].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];
          base[testt].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];

          slist[testt] = &base[testt];
          testt++;
        }
        // Right edge
        if (Terrain_list[index].right_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * (smul_z - i)) + smul_x;
          base[right_start + testr] = World_point_buffer[cur_seg];

          base[right_start + testr].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + simplemul];
          base[right_start + testr].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + simplemul];

          slist[right_start + testr] = &base[right_start + testr];
          testr++;
        }
        // Bottom edge
        if (Terrain_list[index].bottom_edge & (1 << i)) {
          cur_seg = n + (smul_x - i);
          base[bottom_start + testb] = World_point_buffer[cur_seg];

          base[bottom_start + testb].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + simplemul) * LOD_ROW_SIZE) + subx + simplemul - i];
          base[bottom_start + testb].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + simplemul) * LOD_ROW_SIZE) + subx + simplemul - i];
          slist[bottom_start + testb] = &base[bottom_start + testb];
          testb++;
        }
        // left edge
        if (Terrain_list[index].left_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * i);
          base[left_start + testl] = World_point_buffer[cur_seg];

          base[left_start + testl].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + simplemul - i) * LOD_ROW_SIZE) + subx];
          base[left_start + testl].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + simplemul - i) * LOD_ROW_SIZE) + subx];

          slist[left_start + testl] = &base[left_start + testl];
          testl++;
        }
      }
    } else {
      right_start = Terrain_list[index].top_count;
      bottom_start = right_start + Terrain_list[index].right_count;
      left_start = bottom_start + Terrain_list[index].bottom_count;
      point_count = left_start + Terrain_list[index].left_count;

      for (i = 0; i < smul_x; i++) {
        // top edge
        if (Terrain_list[index].top_edge & (1 << i)) {
          cur_seg = n + i + (TERRAIN_WIDTH * smul_z);
          base[testt] = World_point_buffer[cur_seg];

          base[testt].p3_u = tile * TerrainUSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];
          base[testt].p3_v = tile * TerrainVSpeedup[rotator][subz * LOD_ROW_SIZE + subx + i];

          slist[testt] = &base[testt];
          testt++;
        }
        // Bottom edge
        if (Terrain_list[index].bottom_edge & (1 << i)) {
          cur_seg = n + (smul_x - i);
          base[bottom_start + testb] = World_point_buffer[cur_seg];

          base[bottom_start + testb].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + simplemul) * LOD_ROW_SIZE) + subx + simplemul - i];
          base[bottom_start + testb].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + simplemul) * LOD_ROW_SIZE) + subx + simplemul - i];

          slist[bottom_start + testb] = &base[bottom_start + testb];
          testb++;
        }
      }

      for (i = 0; i < smul_z; i++) {
        // Right edge
        if (Terrain_list[index].right_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * (smul_z - i)) + smul_x;
          base[right_start + testr] = World_point_buffer[cur_seg];

          base[right_start + testr].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + simplemul];
          base[right_start + testr].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + i) * LOD_ROW_SIZE) + subx + simplemul];

          slist[right_start + testr] = &base[right_start + testr];
          testr++;
        }
        // left edge
        if (Terrain_list[index].left_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * i);
          base[left_start + testl] = World_point_buffer[cur_seg];

          base[left_start + testl].p3_u =
              tile * TerrainUSpeedup[rotator][((subz + simplemul - i) * LOD_ROW_SIZE) + subx];
          base[left_start + testl].p3_v =
              tile * TerrainVSpeedup[rotator][((subz + simplemul - i) * LOD_ROW_SIZE) + subx];
          slist[left_start + testl] = &base[left_start + testl];
          testl++;
        }
      }
    }
  }
#if (defined(EDITOR) || defined(NEWEDITOR))
  ddgr_color oldcolor;
  if (TSearch_on) {
    rend_SetPixel(GR_RGB(0, 255, 0), TSearch_x, TSearch_y);
    oldcolor = rend_GetPixel(TSearch_x, TSearch_y); // will be different in 15/16-bit color
  }
#endif

  rend_SetOverlayType(OT_NONE);

  // Make sure the triangle faces us and if so draw
  // Upper left triangle
  if (lod != (MAX_TERRAIN_LOD - 1))
    draw_big_square = 1;
  if (!upper_left && !draw_big_square)
    goto draw_lower_right;

  if (lod == (MAX_TERRAIN_LOD - 1)) {
    slist[0] = &base[0];
    slist[1] = &base[1];
    slist[2] = &base[3];
    points_this_triangle = 3;
  } else {
    points_this_triangle = point_count;
  }

  g3_DrawPoly(points_this_triangle, slist, bm_handle);
#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_TERRAIN))
    DrawTerrainOutline(n, points_this_triangle, slist);
#endif
  // If we're LOD'd, we've already drawn our 1 polygon.  Return!
  if (draw_big_square)
    return 0;

// Now do lower right triangle
draw_lower_right:
  if (!lower_right)
    return 0;
  slist[0] = &base[3];
  slist[1] = &base[1];
  slist[2] = &base[2];
  points_this_triangle = 3;

  g3_DrawPoly(points_this_triangle, slist, bm_handle);
#if (defined(EDITOR) || defined(NEWEDITOR))
  if (TSearch_on) {
    if (rend_GetPixel(TSearch_x, TSearch_y) != oldcolor) {
      TSearch_seg = n;
      TSearch_found_type = TSEARCH_FOUND_TERRAIN;
    }
  }
#endif
#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_TERRAIN))
    DrawTerrainOutline(n, points_this_triangle, slist);
#endif
  return 0;
}
// Draws the 2 triangles of the Terrainlist[index] (hardware)
void DrawTerrainLightmapsHardware(int index, int upper_left, int lower_right) {
  int i;
  int cur_seg;
  int n = Terrain_list[index].segment;
  int lod = Terrain_list[index].lod;
  int bottom_start, left_start, right_start;
  int point_count = 0;
  int points_this_triangle = 0;

  terrain_segment *tseg = &Terrain_seg[n];
  int simplemul = 1 << ((MAX_TERRAIN_LOD - 1) - lod);
  int cx, cz, smul_x, smul_z;
  cx = n % TERRAIN_WIDTH;
  cz = n / TERRAIN_WIDTH;

  // Get lightmap coordinates
  float lightmap_u = (cx % 128) / 128.0;
  float lightmap_v = (128 - ((cz % 128) + simplemul)) / 128.0;
  float uvadjust;
  int draw_big_square = 0;
  bool solid_square = 1;
  int testt = 0, testr = 0, testb = 0, testl = 0;
  // Check to make sure we don't access memory that is off the map
  if (cx + simplemul == TERRAIN_WIDTH) {
    smul_x = simplemul - 1;
    solid_square = 0;
  } else
    smul_x = simplemul;
  if (cz + simplemul == TERRAIN_DEPTH) {
    solid_square = 0;
    smul_z = simplemul - 1;
  } else
    smul_z = simplemul;
  // Build a list of points for our polygon.  We must do it this way to
  // prevent tjoint cracking
  // Do simpler operation if at highest level of detail
  if (lod == (MAX_TERRAIN_LOD - 1)) {
    uvadjust = (simplemul / 128.0);
    cur_seg = n + (TERRAIN_WIDTH * smul_z);
    base[0] = World_point_buffer[cur_seg];

    cur_seg = n + (TERRAIN_WIDTH * smul_z) + smul_x;
    base[1] = World_point_buffer[cur_seg];

    cur_seg = n + smul_x;
    base[2] = World_point_buffer[cur_seg];

    base[3] = World_point_buffer[n];

    base[0].p3_u = lightmap_u;
    base[0].p3_v = lightmap_v;
    base[1].p3_u = lightmap_u + uvadjust;
    base[1].p3_v = lightmap_v;
    base[2].p3_u = lightmap_u + uvadjust;
    base[2].p3_v = lightmap_v + uvadjust;

    base[3].p3_u = lightmap_u;
    base[3].p3_v = lightmap_v + uvadjust;
  } else {
    uvadjust = (simplemul / 128.0) / simplemul;
    float uvmul = uvadjust * simplemul;
    if (solid_square) {
      right_start = Terrain_list[index].top_count;
      bottom_start = right_start + Terrain_list[index].right_count;
      left_start = bottom_start + Terrain_list[index].bottom_count;
      point_count = left_start + Terrain_list[index].left_count;

      for (i = 0; i < simplemul; i++) {
        // Top edge
        if (Terrain_list[index].top_edge & (1 << i)) {
          cur_seg = n + i + (TERRAIN_WIDTH * smul_z);
          base[testt] = World_point_buffer[cur_seg];

          base[testt].p3_u = lightmap_u + (i * uvadjust);
          base[testt].p3_v = lightmap_v;
          slist[testt] = &base[testt];
          testt++;
        }
        // Right edge
        if (Terrain_list[index].right_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * (smul_z - i)) + smul_x;
          base[right_start + testr] = World_point_buffer[cur_seg];

          base[right_start + testr].p3_u = lightmap_u + uvmul;
          base[right_start + testr].p3_v = lightmap_v + (i * uvadjust);
          slist[right_start + testr] = &base[right_start + testr];
          testr++;
        }
        // Bottom edge
        if (Terrain_list[index].bottom_edge & (1 << i)) {
          cur_seg = n + (smul_x - i);
          base[bottom_start + testb] = World_point_buffer[cur_seg];

          base[bottom_start + testb].p3_u = lightmap_u + uvmul - (i * uvadjust);
          base[bottom_start + testb].p3_v = lightmap_v + uvmul;
          slist[bottom_start + testb] = &base[bottom_start + testb];
          testb++;
        }
        // left edge
        if (Terrain_list[index].left_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * i);
          base[left_start + testl] = World_point_buffer[cur_seg];

          base[left_start + testl].p3_u = lightmap_u;
          base[left_start + testl].p3_v = lightmap_v + uvmul - (i * uvadjust);
          slist[left_start + testl] = &base[left_start + testl];
          testl++;
        }
      }
    } else {
      right_start = Terrain_list[index].top_count;
      bottom_start = right_start + Terrain_list[index].right_count;
      left_start = bottom_start + Terrain_list[index].bottom_count;
      point_count = left_start + Terrain_list[index].left_count;

      for (i = 0; i < smul_x; i++) {
        // top edge
        if (Terrain_list[index].top_edge & (1 << i)) {
          cur_seg = n + i + (TERRAIN_WIDTH * smul_z);
          base[testt] = World_point_buffer[cur_seg];

          base[testt].p3_u = lightmap_u + (i * uvadjust);
          base[testt].p3_v = lightmap_v;
          slist[testt] = &base[testt];
          testt++;
        }
        // Bottom edge
        if (Terrain_list[index].bottom_edge & (1 << i)) {
          cur_seg = n + (smul_x - i);
          base[bottom_start + testb] = World_point_buffer[cur_seg];

          base[bottom_start + testb].p3_u = lightmap_u + uvmul - (i * uvadjust);
          base[bottom_start + testb].p3_v = lightmap_v + uvmul;
          slist[bottom_start + testb] = &base[bottom_start + testb];
          testb++;
        }
      }

      for (i = 0; i < smul_z; i++) {
        // Right edge
        if (Terrain_list[index].right_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * (smul_z - i)) + smul_x;
          base[right_start + testr] = World_point_buffer[cur_seg];

          base[right_start + testr].p3_u = lightmap_u + uvmul;
          base[right_start + testr].p3_v = lightmap_v + (i * uvadjust);
          slist[right_start + testr] = &base[right_start + testr];
          testr++;
        }
        // left edge
        if (Terrain_list[index].left_edge & (1 << i)) {
          cur_seg = n + (TERRAIN_WIDTH * i);
          base[left_start + testl] = World_point_buffer[cur_seg];

          base[left_start + testl].p3_u = lightmap_u;
          base[left_start + testl].p3_v = lightmap_v + uvmul - (i * uvadjust);
          slist[left_start + testl] = &base[left_start + testl];
          testl++;
        }
      }
    }
  }

  // Make sure the triangle faces us and if so draw
  // Upper left triangle
  if (lod != (MAX_TERRAIN_LOD - 1))
    draw_big_square = 1;
  if (!upper_left && !draw_big_square)
    goto draw_lower_right;

  if (lod == (MAX_TERRAIN_LOD - 1)) {
    slist[0] = &base[0];
    slist[1] = &base[1];
    slist[2] = &base[3];
    points_this_triangle = 3;
  } else {
    points_this_triangle = point_count;
  }

  g3_DrawPoly(points_this_triangle, slist, TerrainLightmaps[tseg->lm_quad], MAP_TYPE_LIGHTMAP);
#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_TERRAIN))
    DrawTerrainOutline(n, points_this_triangle, slist);
#endif
  // If we're LOD'd, we've already drawn our 1 polygon.  Return!
  if (draw_big_square)
    return;

// Now do lower right triangle
draw_lower_right:
  if (!lower_right)
    return;
  slist[0] = &base[3];
  slist[1] = &base[1];
  slist[2] = &base[2];
  points_this_triangle = 3;

  g3_DrawPoly(points_this_triangle, slist, TerrainLightmaps[tseg->lm_quad], MAP_TYPE_LIGHTMAP);

#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (OUTLINE_ON(OM_TERRAIN))
    DrawTerrainOutline(n, points_this_triangle, slist);
#endif
}
// Adds object obj to terrain segment n.
// This object will be rendered immediately following the rendering of this
// terrain segment
int AddRenderObjectToTerrainSeg(int n, int objnum) {
// Uses a linked list to keep track of what objects are in this segment
#if (!defined(RELEASE) || defined(NEWEDITOR))
  if (Terrain_seg_render_objs[n] == objnum)
    return 0;
  // New object points at first in list
  render_next[objnum] = Terrain_seg_render_objs[n];
  // New object becomes first in list
  Terrain_seg_render_objs[n] = objnum;
#endif

  return (0);
}
