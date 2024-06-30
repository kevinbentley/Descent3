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

 * $Logfile: /DescentIII/Main/renderobject.cpp $
 * $Revision: 182 $
 * $Date: 10/03/01 11:35p $
 * $Author: Kevin $
 *
 * Code to render objects
 *
 * $Log: /DescentIII/Main/renderobject.cpp $
 *
 * 182   10/03/01 11:35p Kevin
 * multiplayer stripes appear in demo playback
 *
 * 181   10/12/99 11:07a Jeff
 * created virus infected effect
 *
 * 180   9/21/99 2:55p Jeff
 * use powerup color for spark colors
 *
 * 179   9/20/99 5:35p Jeff
 * added -nosparkles command line option to turn off powerup sparkles
 *
 * 178   9/20/99 5:30p Jeff
 * added pretty powerup particles for Katmai systems
 *
 * 177   9/18/99 9:28p Jeff
 * motion blur robots and debris
 *
 * 176   8/09/99 3:27p Jeff
 * fixed render bug with typing indicator
 *
 * 175   7/28/99 3:44p Kevin
 * Mac!
 *
 * 174   7/20/99 1:00p Jason
 * added auto katmai support
 *
 * 173   7/08/99 5:47p Jason
 * changes for new bumpmapping system in 1.1 update patch
 *
 * 172   5/26/99 3:03a Jason
 * fixed bug where flags attached to players would render incorrectly in
 * multplayer (specifially ctf flags)
 *
 * 171   5/13/99 3:41p Ardussi
 * changes for compiling on the Mac
 *
 * 170   5/12/99 3:25p Jason
 * don't render powerup glows if their render type is RT_NONE
 *
 * 169   5/08/99 1:50p Jason
 * fixed some player colors
 *
 * 168   5/03/99 9:27p Jason
 * fixed one of Chris's bugs with the attach system
 *
 * 167   4/29/99 4:58p Jason
 * fixed typing indicator problem
 *
 * 166   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 165   4/19/99 3:25p Jason
 *
 * 164   4/19/99 3:46a Jeff
 * fixed min/max for Linux
 *
 * 163   4/17/99 4:51p Jason
 * fixed stupid headlight issue for good
 *
 * 162   4/16/99 11:53a Jason
 * fixed some lighting issues
 *
 * 161   4/14/99 7:21p Jason
 * made ships more visible in multiplayer
 *
 * 160   4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 159   4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 158   4/06/99 1:51p Jason
 * added new mass driver effect
 *
 * 157   4/06/99 10:23a Chris
 * More "render even though the parent is invisible" cases
 *
 * 156   4/03/99 4:56p Jason
 * fixed deform effect just a little
 *
 * 155   4/03/99 2:20p Jason
 * added better heat damage effect
 *
 * 154   3/29/99 4:02p Chris
 * Patched/Hacked a solution to the invis. after landing problem.
 *
 * 153   3/22/99 11:16a Jason
 * Katmai enhancements
 *
 * 152   3/04/99 11:44a Jeff
 * made it so typing indicator is at max 64x64 when rendering
 *
 * 151   3/03/99 4:51p Jason
 * fixed divide by zero problem
 *
 * 150   2/24/99 11:51p Jason
 * fixed object bug for matt
 *
 * 149   2/23/99 12:40p Jason
 * added more options for generic objects
 *
 * 148   2/22/99 3:37p Jason
 * fixed LOD problems
 *
 * 147   2/21/99 4:20p Matt
 * Added SoundSource objects (and reformatted parts of the object header
 * files).
 *
 * 146   2/18/99 11:05a Jason
 * fixed some cloak effects
 *
 * 145   2/17/99 1:05p Jason
 * revamped object/face/terrain selection code
 *
 * 144   2/15/99 4:11p Jason
 * made non-vis objects kill all their attach sounds/objects
 *
 * 143   2/10/99 12:47p Jeff
 * fixed up typing indicator
 *
 * 142   2/09/99 6:53p Jeff
 * implemented 'typing inidcator' in multiplayer...players that are typing
 * messages have an icon on them
 *
 * 141   2/09/99 9:59a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 140   2/05/99 3:00p Jason
 * fixed bug with my last rev
 *
 * 139   2/05/99 12:19p Jason
 * fixed object selection
 *
 * 138   2/02/99 8:43a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 137   1/27/99 6:08p Jason
 * first pass at markers
 *
 * 136   1/21/99 11:29p Jason
 * took out misplaced no_glow flag
 *
 * 135   1/20/99 5:36p Jason
 * added custom glows for teams
 *
 * 134   1/19/99 4:22p Matt
 * Added the ability for objects to have their own lighting info,
 * different from the default lighting for that type of object.
 *
 * 133   1/13/99 12:43p Jason
 * added some more detail settings
 *
 * 132   1/13/99 6:38a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 131   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 130   12/14/98 10:53a Jason
 * added bright player ships option
 *
 * 129   12/10/98 7:09p Jason
 * added cloak fade
 *
 * 128   12/10/98 12:27p Jason
 * added cooler specular mapping for objects
 *
 * 127   12/07/98 3:02p Jason
 * added multi_logo_state
 *
 * 126   11/11/98 7:18p Jeff
 * changes made so that a dedicated server's team is always -1 (team game
 * or not)
 *
 * 125   11/11/98 12:33p Jason
 * changed black player color
 *
 * 124   10/21/98 9:28p Jason
 * Made no lightmaps work globally
 *
 * 123   10/21/98 7:55p Jason
 * d3d changes
 *
 * 122   10/21/98 7:30p Jason
 * more direct3d changes
 *
 * 121   10/19/98 3:16p Jason
 * additional error checking for lightning
 *
 * 120   10/18/98 4:25p Jason
 * fixes for fogged objects
 *
 * 119   10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 118   10/16/98 2:38p Jason
 * made powerup halo detail setting work
 *
 * 117   10/16/98 2:24p Jason
 * changes for the demo
 *
 * 116   10/14/98 6:24p Jason
 * made object complexity work
 *
 * 115   10/08/98 5:59p Jason
 * fixed object and room popping with small views
 *
 * 114   10/07/98 5:04p Jason
 * made spheres work in WindowGL mode
 *
 * 113   10/02/98 1:47p Jason
 * added lod player ships
 *
 * 112   10/02/98 12:23p Jason
 * took off sight vector
 *
 * 111   10/02/98 11:46a Jason
 * checked in for samir
 *
 * 110   10/01/98 6:10p Jason
 * added EVT_CLIENT_GETCOLOREDNAME
 *
 * 109   10/01/98 4:41p Jason
 * fixed colors in team games
 *
 * 108   10/01/98 4:09p Jason
 * added multicolor ship stuff
 *
 * 107   9/29/98 12:49p Jason
 * worked on matcen effects and lightning
 *
 * 106   9/24/98 12:57p Jason
 * more state limited optimizations
 *
 * 105   9/21/98 5:08p Jason
 * made damage shield not rotate when you get hit
 *
 * 104   9/21/98 1:03p Jason
 * make sparky damage lightning ramp up depending on amount of damage
 *
 * 103   9/18/98 8:23p Jason
 * fixed insidious vis effect errors
 *
 * 102   9/17/98 6:08p Jason
 * more tweaks for effects
 *
 * 101   9/17/98 3:03p Jason
 * added lightning and invul hit effects
 *
 * 100   9/10/98 12:18p Jason
 * more changes to afterburner/thrust effect
 *
 * 99    9/09/98 7:09p Jason
 * changed afterburner effect for ships
 *
 * 98    8/27/98 5:19p Jason
 * added first rev of reflected surfaces
 *
 * 97    8/24/98 1:01p Jason
 * made object specular faces selectable by texture
 *
 * 96    8/19/98 2:19p Jeff
 * moved detail globals to a struct
 *
 * 95    8/18/98 11:38a Jason
 * fixed polymodel fog lighting
 *
 * 94    8/14/98 4:00p Jason
 * added specular objects outside
 *
 * 93    8/13/98 6:57p Jason
 * made fogged objects render correctly
 *
 * 92    8/12/98 6:38p Jeff
 * don't render ghosted objects (type==OBJ_DUMMY)
 *
 * 91    8/03/98 3:59p Chris
 * Added support for FQ_IGNORE_WEAPONS, added .000001 attach code, fix a
 * bug in polymodel collision detection
 *
 * 90    8/03/98 2:59p Jeff
 * player names only check doors for visibility
 *
 * 89    8/03/98 11:06a Jason
 * made custom textures work correctly
 *
 * 88    7/30/98 11:12a Jason
 * fixed player names showing up when cloaked
 *
 * 87    7/28/98 3:29p Jason
 * fixed z buffer bug with damage disk
 *
 * 86    7/27/98 5:59p Jason
 * added piggyback mode plus multiplayer colors
 *
 * 85    7/02/98 6:30p Jason
 * added some multiplayer stuff for Jeff
 *
 * 84    6/30/98 6:36p Chris
 * Added rev .1 of multiplayer animations - BTW  It is totally not done.
 *
 * 83    6/25/98 5:17p Jason
 * added multiple colored balls for players
 *
 * 82    6/22/98 12:27p Jason
 * fixed stupid bug with my last rev
 *
 * 81    6/22/98 12:15p Jason
 * took out cheap LOD effect with robots
 *
 * 80    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 79    6/11/98 12:48p Jason
 * added better spewing weapons
 *
 * 78    5/11/98 10:41a Jason
 * made clutter object lodable
 *
 * 77    5/05/98 6:26p Chris
 * Added BBoxs and spheres to external rooms (in mode 2)
 *
 * 76    5/04/98 7:26p Chris
 * Allowed turning off of submodels on robots
 *
 * 75    5/04/98 3:51p Matt
 * Finished (for now) with breaking glass.
 *
 * 74    5/04/98 12:28p Matt
 * Added shard objects
 *
 * 73    5/03/98 8:42p Chris
 *
 * 72    5/03/98 8:36p Chris
 * Additional debug info
 *
 * 71    4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 70    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 69    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 68    4/17/98 3:57p Jason
 * added microwave effect
 *
 * 67    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 66    4/15/98 3:28p Jason
 * changed glow stuff to work with new system
 *
 * 65    4/13/98 3:51p Chris
 * Added sphere bubbles to weapons (when wanted)  and fixed a small FVI
 * bug
 *
 * 64    4/10/98 12:41p Jason
 * sped up lighting a little
 *
 * 63    4/08/98 12:58p Jason
 * fixed cloak effect in software
 *
 * 62    4/07/98 5:01p Jason
 * more tweaks to cloak effect
 *
 * 61    4/07/98 4:49p Jason
 * fixed cloak problem
 *
 * 60    4/06/98 2:54p Jason
 * yet more multiplayer changes
 *
 * 59    4/02/98 12:24p Jason
 * trimmed some fat from our structures
 *
 * 58    4/01/98 6:23p Jason
 * added a slew of stuff for multiplayer
 *
 * 57    4/01/98 12:02p Jason
 * incremental checkin for rendering changes
 *
 * 56    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 55    3/20/98 2:18p Jason
 * changes for multiplayer
 *
 * 54    3/19/98 7:15p Jason
 * more changes for multiplayer
 *
 * 53    3/13/98 7:00p Chris
 * EDITOR to _DEBUG
 *
 * 52    3/13/98 12:10p Jason
 * draw a bit of a ring around polygon glows
 *
 * 51    3/11/98 4:59p Chris
 * Added a few new sphere types (wall and anim)
 *
 * 50    3/10/98 5:15p Chris
 * DEL+B shows the bounding-sphere of an object
 *
 * 49    3/09/98 5:58p Jason
 * draw powerups with saturated alpha rings
 *
 * 48    3/09/98 4:54p Jason
 * don't render objects that can't been seen through a portal
 *
 * 47    2/25/98 4:31p Jason
 * changes for explosions
 *
 * 46    2/25/98 2:05p Jason
 * did FOV and object visibility changes
 *
 * 45    2/20/98 1:46p Chris
 * JASON:  Made dynamic lighting only occur if the object is rendered
 *
 * 44    2/11/98 6:58p Matt
 * Changed the way cameras are rendered, so they show up on the terrain as
 * well.
 *
 * 43    2/11/98 6:38p Jason
 * tweaking the glow effects for engines
 *
 * 42    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 41    2/04/98 2:52p Jason
 * made length of glow dependant on whether or not the player is thrusting
 *
 * 40    1/30/98 6:07p Matt
 * Added code and menu items to deal with camera objects
 *
 * 39    1/30/98 2:56p Matt
 * Added support for small views.  Made R toggle rear view, and Delete-F8
 * show a view from object 2.  Also changed main window render flow so
 * could share code with small views.
 *
 * 38    1/28/98 5:37p Jason
 * added streamer weapons
 *
 * 37    1/23/98 11:21a Jason
 * incremental multiplayer checkin
 *
 * 36    1/21/98 6:09p Jason
 * Got player deaths working in multiplayer
 *
 * 35    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 34    1/20/98 2:17p Jason
 * fixed weird sorting problem with objects and viseffects
 *
 * 33    1/20/98 12:10p Jason
 * implemented vis effect system
 *
 * 32    1/13/98 4:04p Jason
 * changes for engine glow
 *
 * 31    1/13/98 3:09p Jason
 * added glow effect for engines
 *
 * 30    1/05/98 5:59p Jason
 * tweaked z bias code
 *
 * 29    12/08/97 6:18p Jason
 * more tweaks for destroyable buildings
 *
 * 28    12/08/97 5:22p Jason
 * added code for destroyable buildings that leave their base object
 * around
 *
 * 27    11/25/97 1:36p Jason
 * adjusted LOD switch levels
 *
 * 26    11/25/97 1:17p Jason
 * added lod system for certain objects
 *
 * 25    11/18/97 12:26a Sean
 * I don't know (Chris)
 *
 * 24    11/11/97 8:40p Chris
 * Added an assert.
 *
 * 23    11/05/97 6:03p Jason
 * added disky colored lighting effects
 *
 * 22    11/05/97 12:20p Jason
 * made powerups render with halos
 *
 * 21    10/28/97 11:34a Chris
 * Fixed a bug in the animation code (if keyframe = 0 and the object
 * animates, we need to set the angles)
 *
 * 20    10/23/97 11:34p Chris
 * Fixed problems with idle animations
 *
 * 19    10/23/97 5:36p Jason
 * added splinter objects (probably temporary)
 *
 * 18    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 17    10/03/97 5:57p Chris
 * Added support for debug fvi_line
 *
 * 16    10/03/97 4:43p Chris
 * added debug fvi call and object type line
 *
 * 15    10/01/97 7:00p Jason
 * did more work on object lightmaps
 *
 * 14    10/01/97 11:35a Jason
 * added IsObjectVisible function
 *
 * 13    9/30/97 5:08p Chris
 * No changes
 *
 * 12    9/22/97 6:20p Matt
 * Removed obsolete code
 *
 * 11    9/16/97 5:04p Matt
 * Changed conditional for debug code
 *
 * 10    9/12/97 5:38p Jason
 * got doors working
 *
 * 9     9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 8     9/09/97 6:15p Jason
 * made dynamic lighting on objects more memory efficient
 *
 * 7     9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 6     8/20/97 5:19p Matt
 * Draw selected bracket instead of box for current object
 *
 * $NoKeywords: $
 */
#include "object.h"
#include "object_lighting.h"
#include "3d.h"
#include "polymodel.h"
#include "renderer.h"
#include "weapon.h"
#include "fireball.h"
#include "descent.h"
#include "renderobject.h"
#include "AIMain.h"
#include "objinfo.h"
#include "splinter.h"
#include "fireball.h"
#include "descent.h"
#include "render.h"
#include "gametexture.h"
#include "game.h"
#include "player.h"
#include "damage.h"
#include "gameloop.h"
#include "findintersection.h"
#include "grtext.h"
#include "gamefont.h"
#include "config.h"
#include "viseffect.h"
#include "game2dll.h"
#include "marker.h"
#include "ship.h"
#include "psrand.h"

#include <string.h>
#ifdef EDITOR
#include "editor\d3edit.h"
#endif

#include <algorithm>

// what darkening level to use when cloaked
#define CLOAKED_FADE_LEVEL 28
#define CLOAK_FADEIN_DURATION_PLAYER F2_0
#define CLOAK_FADEOUT_DURATION_PLAYER F2_0
#define CLOAK_FADEIN_DURATION_ROBOT F1_0
#define CLOAK_FADEOUT_DURATION_ROBOT F1_0
#define RO_STATIC 0
#define RO_GOURAUD 1
#define RO_LIGHTMAPS 2
extern uint8_t Use_motion_blur;
uint8_t RenderObjectType = RO_STATIC;
float RenderObjectStaticRedValue = 1.0f;
float RenderObjectStaticGreenValue = 1.0f;
float RenderObjectStaticBlueValue = 1.0f;
float RenderObjectStaticScalar = 1.0f;
uint8_t *RenderObjectGouraudValue = NULL;
lightmap_object *RenderObjectLightmapObject = NULL;
vector RenderObject_LightDirection;

float Last_powerup_sparkle_time = 0.0f;
bool Render_powerup_sparkles = false;
// Do powerup sparkles and stuff
void DrawPowerupSparkles(object *obj);

// Draws the glowing disk around a powerup
void DrawPowerupGlowDisk(object *obj);
// Draws a damage disk around a powerup
void DrawPlayerDamageDisk(object *obj);
void DrawPlayerInvulSphere(object *obj);
void DrawPlayerSightVector(object *obj);
// Draws this players name on the hud
void DrawPlayerNameOnHud(object *obj);
// Draws a rotating ball around the player
void DrawPlayerRotatingBall(object *obj);
// Creates lightning sparks on a damaged object
void DrawSparkyDamageLightning(object *obj);
// Creates Virus infected lightning on an object
void DrawVirusLightning(object *obj);

#ifdef EDITOR
// Draws the little corner brackets around the selected object
// Actually, only draws those either in front or in back of the object, based on front_flag
void DrawObjectSelectionBrackets(object *obj, bool front_flag) {
  vector viewvec;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  float line_len;
  // Get vector from object to viewer
  g3_GetViewPosition(&viewvec);
  viewvec -= obj->pos;
  // Get length of line segments we're drawing
  line_len = (pm->maxs.x - pm->mins.x) * 0.2f;
  // Do each corner
  for (int c = 0; c < 8; c++) {
    vector corner;
    // Get the corner relative to the object
    corner = (obj->orient.rvec * ((c & 1) ? pm->mins.x : pm->maxs.x)) +
             (obj->orient.uvec * ((c & 2) ? pm->mins.y : pm->maxs.y)) +
             (obj->orient.fvec * ((c & 4) ? pm->mins.z : pm->maxs.z));
    // See if this corner is in front or in back of the object, as specified
    if (((corner * viewvec) > 0.0) != front_flag)
      continue;
    // Get absolute position in 3-space
    corner += obj->pos;
    // Draw line for each axis at this corner
    for (int a = 0; a < 3; a++) {
      g3Point pp0, pp1;
      vector t;
      // Grab the x,y, or z axis, and scale by the line segment length
      t = corner + ((((vector *)&obj->orient)[a]) * ((c & (1 << a)) ? line_len : -line_len));
      // Rotate both ends of the line
      g3_RotatePoint(&pp0, &corner);
      g3_RotatePoint(&pp1, &t);
      // Draw!
      g3_DrawLine(GR_RGB(255, 255, 255), &pp0, &pp1);
    }
  }
}
#endif
#ifdef _DEBUG
static float ArrayX[10][20] = {{-1, 1, 1, -1, -1},
                               {-.25, 0.0, 0.0, 0.0, -1.0, 1.0},
                               {-1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0},
                               {-1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -.5},
                               {-1.0, -1.0, -1.0, 1.0, 1.0, 1.0},
                               {-1.0, 1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0},
                               {-1.0, 1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0},
                               {-1.0, 1.0, 1.0, 1.0},
                               {-1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0},
                               {1.0, -1.0, -1.0, 1.0, 1.0, 1.0}};
static float ArrayY[10][20] = {{1, 1, -1, -1, 1},
                               {.75, 1.0, 1.0, -1.0, -1.0, -1.0},
                               {1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, -1.0, -1.0},
                               {1.0, 1.0, -1.0, -1.0, -1.0, 0, 0.0},
                               {1.0, 0.0, 0.0, 0.0, 1.0, -1.0},
                               {1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, -1.0, -1.0},
                               {1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0, 0.0, 0.0, 0.0},
                               {1.0, 1.0, 1.0, -1.0},
                               {1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 0.0, 0.0},
                               {1.0, 1.0, 0.0, 0.0, 1.0, -1.0}};
static int NumOfPoints[] = {5, 6, 10, 7, 6, 10, 10, 4, 10, 6};
static void DrawNumber(int num, vector pos, float size, ddgr_color c1) {
  g3Point basepnt, rot_pnt[20];
  int num_array[10];
  int i, j;
  int total = num;
  size /= 2;
  if (num < 0) {
    num *= -1;
    num += 10000;
  }
  int num_numbers = (int)(log10f((float)num) + 1);
  if (num_numbers > 10) {
    mprintf(0, "Cannot represent a number with over 10 digits\n");
    Int3();
    return;
  }

  for (j = num_numbers - 1; j >= 0; j--) {
    num_array[j] = total / ((int)powf(10.0f, (float)j));
    total -= num_array[j] * (int)powf(10.0f, (float)j);
  }
  for (j = 0; j < num_numbers; j++) {
    vector cur_pos;

    if (num_numbers & 0x00000001)
      cur_pos = pos + (2.1 * size * ((num_numbers >> 1) - j)) * Viewer_object->orient.rvec;
    else
      cur_pos = pos + (2.1 * size * ((num_numbers >> 1) - j) - size) * Viewer_object->orient.rvec;
    g3_RotatePoint(&basepnt, &cur_pos);
    for (i = 0; i < NumOfPoints[num_array[j]]; i++) {
      rot_pnt[i] = basepnt;
      rot_pnt[i].p3_vec.x += (ArrayX[num_array[j]][i] * size);
      rot_pnt[i].p3_vec.y += (ArrayY[num_array[j]][i] * size);
      rot_pnt[i].p3_flags = 0;
      g3_CodePoint(&rot_pnt[i]);
      g3_ProjectPoint(&rot_pnt[i]);
    }
    for (i = 0; i < NumOfPoints[num_array[j]] - 1; i++) {
      g3Point p1, p2;
      p1 = rot_pnt[i];
      p2 = rot_pnt[i + 1];

      g3_DrawLine(c1, &p1, &p2);
    }
  }
}
static inline bool object_object_AABB(object *obj1, object *obj2) {
  bool overlap = true;
  if (obj1->max_xyz.x < obj2->min_xyz.x || obj2->max_xyz.x < obj1->min_xyz.x || obj1->max_xyz.z < obj2->min_xyz.z ||
      obj2->max_xyz.z < obj1->min_xyz.z || obj1->max_xyz.y < obj2->min_xyz.y || obj2->max_xyz.y < obj1->min_xyz.y)
    overlap = false;

  return overlap;
}
// Given a face, computes the upper left corner of the face
void ComputeDebugVisFaceUpperLeft(room *rp, face *fp, vector *upper_left, float *xdiff, float *ydiff, vector *center) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE];
  vector rot_vert;
  int i;

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  for (i = 0; i < fp->num_verts; i++)
    avg_vert += rp->verts[fp->face_verts[i]];
  avg_vert /= fp->num_verts;
  // Make the orientation matrix
  // Reverse the normal because we're looking "at" the face, not from it
  fvec = -fp->normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < fp->num_verts; i++) {
    vector vert = rp->verts[fp->face_verts[i]];

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);
    verts[i] = rot_vert;
  }
  // Find left most point
  int leftmost_point = -1;
  float leftmost_x = 900000.00f; // a big number
  for (i = 0; i < fp->num_verts; i++) {
    if (verts[i].x < leftmost_x) {
      leftmost_point = i;
      leftmost_x = verts[i].x;
    }
  }
  ASSERT(leftmost_point != -1);
  // Find top most point
  int topmost_point = -1;
  float topmost_y = -900000.0f; // a big number
  for (i = 0; i < fp->num_verts; i++) {
    if (verts[i].y > topmost_y) {
      topmost_point = i;
      topmost_y = verts[i].y;
    }
  }
  ASSERT(topmost_point != -1);
  // Find right most point
  int rightmost_point = -1;
  float rightmost_x = -900000.00f; // a big number
  for (i = 0; i < fp->num_verts; i++) {
    if (verts[i].x > rightmost_x) {
      rightmost_point = i;
      rightmost_x = verts[i].x;
    }
  }
  ASSERT(rightmost_point != -1);
  // Find bottom most point
  int bottommost_point = -1;
  float bottommost_y = 900000.0f; // a big number
  for (i = 0; i < fp->num_verts; i++) {
    if (verts[i].y < bottommost_y) {
      bottommost_point = i;
      bottommost_y = verts[i].y;
    }
  }
  ASSERT(bottommost_point != -1);
  // now set the base vertex, which is where we base uv 0,0 on
  vector base_vector;
  base_vector.x = verts[leftmost_point].x;
  base_vector.y = verts[topmost_point].y;
  base_vector.z = 0;
  // Figure out grid resolution
  *xdiff = verts[rightmost_point].x - verts[leftmost_point].x;
  *ydiff = verts[topmost_point].y - verts[bottommost_point].y;

  // Find upper left corner
  vm_TransposeMatrix(&trans_matrix);
  vm_MatrixMulVector(&rot_vert, &base_vector, &trans_matrix);
  *upper_left = rot_vert + avg_vert;
  *center = avg_vert;
}

#define VIS_TABLE_RESOLUTION 6
void DrawRoomVisPnts(object *obj) {
  int roomnum = obj->roomnum;
  if ((!ROOMNUM_OUTSIDE(roomnum)) && (roomnum != -1) && (Rooms[roomnum].used)) {
    room *rp = &Rooms[roomnum];
    int t;
    int j;
    for (t = 0; t < rp->num_portals; t++) {
      face *src_fp = &rp->faces[rp->portals[t].portal_face];
      float src_width, src_height;
      vector src_upper_left, src_center;
      matrix src_matrix;
      vector src_verts[MAX_VERTS_PER_FACE], *src_vertp[MAX_VERTS_PER_FACE];
      for (j = 0; j < src_fp->num_verts; j++) {
        src_verts[j] = rp->verts[src_fp->face_verts[j]];
        src_vertp[j] = &src_verts[j];
      }
      vector fvec = -src_fp->normal;
      vm_VectorToMatrix(&src_matrix, &fvec, NULL, NULL);
      ComputeDebugVisFaceUpperLeft(rp, src_fp, &src_upper_left, &src_width, &src_height, &src_center);

      if (src_width > VIS_TABLE_RESOLUTION) {
        float num = src_width / VIS_TABLE_RESOLUTION;
        src_width = VIS_TABLE_RESOLUTION;
        src_upper_left += (src_matrix.rvec * (num / 2));
        src_matrix.rvec *= num;
      }
      if (src_height > VIS_TABLE_RESOLUTION) {
        float num = src_height / VIS_TABLE_RESOLUTION;
        src_height = VIS_TABLE_RESOLUTION;
        src_upper_left -= (src_matrix.uvec * (num / 2));
        src_matrix.uvec *= num;
      }
      vector src_vector, src_ybase;
      src_ybase = src_upper_left;
      for (int sy = 0; sy < src_height; sy++, src_ybase -= src_matrix.uvec) {
        src_vector = src_ybase;
        for (int sx = 0; sx < src_width; sx++, src_vector += src_matrix.rvec) {
          vector src2 = src_vector;
          //						vector subvec=src_center-src_vector;
          //							float mag=vm_GetMagnitudeFast (&subvec);
          //							subvec/=(mag*4);
          //							src2+=subvec;
          if ((check_point_to_face(&src2, &src_fp->normal, src_fp->num_verts, src_vertp))) {
            DrawColoredDisk(&src2, 1.0f, 0.0f, 0.0f, .1f, .7f, 0.25f, 1);
            continue;
          }

          src2 += 0.1f * rp->faces[rp->portals[t].portal_face].normal;
          if (!fvi_QuickRoomCheck(&src2, rp, false) && !fvi_QuickRoomCheck(&src2, rp, true)) {
            DrawColoredDisk(&src2, 0.0f, 1.0f, 0.0f, .1f, .7f, 0.25f, 1);
            continue;
          }
          DrawColoredDisk(&src2, 0.0f, 0.0f, 1.0f, .1f, .7f, 0.25f, 1);
        }
      }
    }
  }
}
void DrawDebugInfo(object *obj) {
  matrix m;
  m = obj->orient;
  vm_TransposeMatrix(&m);
  if (obj->type == OBJ_ROOM) {
    DrawColoredDisk(&obj->pos, 0.0f, 0.0f, 1.0f, .1f, .7f, obj->size, 1);
  } else {
    if (Game_show_sphere == 1) {
      vector center = obj->pos + Poly_models[obj->rtype.pobj_info.model_num].wall_size_offset * m;
      DrawColoredDisk(&center, 0.0f, 0.0f, 1.0f, .1f, .7f, Poly_models[obj->rtype.pobj_info.model_num].wall_size, 1);
    } else if (Game_show_sphere == 2) {
      vector center = obj->pos + Poly_models[obj->rtype.pobj_info.model_num].anim_size_offset * m;
      DrawColoredDisk(&center, 0.0f, 0.1f, .9f, .1f, .7f, Poly_models[obj->rtype.pobj_info.model_num].anim_size, 1);
    } else if (Game_show_sphere == 3) {
      DrawColoredDisk(&obj->pos, 0.1f, 0.2f, .9f, .1f, .7f, obj->size, 1);
    }
  }
  g3Point g3p[8];
  memset(g3p, 0, 8 * sizeof(g3Point));
  vector pos[9];
  // g3p[0].p3_vec = obj->pos;
  // g3p[1].p3_vec = obj->rtype.line_info.end_pos;

  ddgr_color c1;
  if (!object_object_AABB(obj, Player_object))
    c1 = GR_RGB(255, 0, 0);
  else
    c1 = GR_RGB(255, 255, 255);
  pos[0] = obj->max_xyz;
  pos[1] = obj->max_xyz;
  pos[1].z = obj->min_xyz.z;
  pos[2] = obj->min_xyz;
  pos[2].y = obj->max_xyz.y;
  pos[3] = obj->max_xyz;
  pos[3].x = obj->min_xyz.x;
  pos[4] = obj->max_xyz;
  pos[4].y = obj->min_xyz.y;
  pos[5] = obj->min_xyz;
  pos[5].x = obj->max_xyz.x;
  pos[6] = obj->min_xyz;
  pos[7] = obj->min_xyz;
  pos[7].z = obj->max_xyz.z;

  pos[8] = obj->pos;
  pos[8].y += .8f * obj->size;
  g3_RotatePoint(&g3p[0], &pos[0]);
  g3_RotatePoint(&g3p[1], &pos[1]);
  g3_RotatePoint(&g3p[2], &pos[2]);
  g3_RotatePoint(&g3p[3], &pos[3]);
  g3_RotatePoint(&g3p[4], &pos[4]);
  g3_RotatePoint(&g3p[5], &pos[5]);
  g3_RotatePoint(&g3p[6], &pos[6]);
  g3_RotatePoint(&g3p[7], &pos[7]);
  g3_DrawLine(c1, &g3p[0], &g3p[1]);
  g3_DrawLine(c1, &g3p[1], &g3p[2]);
  g3_DrawLine(c1, &g3p[2], &g3p[3]);
  g3_DrawLine(c1, &g3p[3], &g3p[0]);
  g3_DrawLine(c1, &g3p[0], &g3p[4]);
  g3_DrawLine(c1, &g3p[1], &g3p[5]);
  g3_DrawLine(c1, &g3p[2], &g3p[6]);
  g3_DrawLine(c1, &g3p[3], &g3p[7]);
  g3_DrawLine(c1, &g3p[4], &g3p[5]);
  g3_DrawLine(c1, &g3p[5], &g3p[6]);
  g3_DrawLine(c1, &g3p[6], &g3p[7]);
  g3_DrawLine(c1, &g3p[7], &g3p[4]);
  DrawNumber(OBJNUM(obj), obj->pos, 1.0, GR_RGB(255, 255, 255));

  if (!OBJECT_OUTSIDE(obj)) {
    if (obj->roomnum != Player_object->roomnum)
      c1 = GR_RGB(255, 0, 0);
    else
      c1 = GR_RGB(255, 255, 255);
    DrawNumber(obj->roomnum, obj->max_xyz, 0.50, c1);
  }
}
#endif
// Draw a shard
void DrawShardObject(object *obj) {
  shard_info_s *si = &obj->rtype.shard_info;
  bool flip = 0;
  g3Point rotated_points[3];
  g3Point *pointlist[3];
  uint8_t codes_and = 0xff;
  g3_StartInstanceMatrix(&obj->pos, &obj->orient);
  // Build list of points and UVLs for this face
  for (int i = 0; i < 3; i++) {
    uint8_t c;
    g3Point *p = &rotated_points[i];
    c = g3_RotatePoint(p, &si->points[i]);
    codes_and &= c;
    p->p3_uvl.u = si->u[i];
    p->p3_uvl.v = si->v[i];
    p->p3_uvl.a = 1.0;    // GameTextures[si->tmap].alpha;
    p->p3_flags |= PF_UV; // + PF_L;	// + PF_UV2 + PF_RGBA;	//has uv and l set
    p->p3_uvl.l = 1.0;
    pointlist[i] = &rotated_points[i];
  }
  // Check for backside
  if (!g3_CheckNormalFacing(&obj->pos, &si->normal)) {
    g3Point *t = pointlist[1];
    pointlist[1] = pointlist[2];
    pointlist[2] = t;
  }
  // Done with 3D
  g3_DoneInstance();
  // Check if face off screen
  if (codes_and)
    return;
  // Get bitmap handle
  int bm_handle = GetTextureBitmap(si->tmap, 0);
  ASSERT(bm_handle != -1);
  float alpha = GameTextures[si->tmap].alpha;
  alpha = 0.2 + alpha * 0.8; // Make less transparent
  // Set alpha, transparency, & lighting for this face
  rend_SetAlphaType(ATF_CONSTANT);
  rend_SetAlphaValue(alpha * 255);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  // Select texture type
  rend_SetTextureType(TT_LINEAR);
  // Draw the polygon
  g3_DrawPoly(3, pointlist, bm_handle);
}
// Sets up the light states for an outdoor object to be rendered
bool SetupTerrainObject(object *obj) {
  vector camlight = Terrain_sky.lightsource;
  vm_NormalizeVector(&camlight);
#ifdef EDITOR
  if (!Terrain_render_ext_room_objs)
    return false;
#endif

  obj->flags |= OF_SAFE_TO_RENDER;
  RenderObject_SetLightDirection(&camlight);
  rend_SetColorModel(CM_MONO);
  if (obj->render_type == RT_POLYOBJ ||
      (obj->render_type == RT_WEAPON &&
       !((Weapons[obj->id].flags & WF_IMAGE_BITMAP) || (Weapons[obj->id].flags & WF_IMAGE_VCLIP)))) {
    float scalar_r, scalar_g, scalar_b, scalar;
    if (obj->type == OBJ_POWERUP) {
      scalar = 1.0;
      scalar_r = 1.0;
      scalar_g = 1.0;
      scalar_b = 1.0;
    } else {
      scalar = GetTerrainDynamicScalar(&obj->pos, CELLNUM(obj->roomnum));
      if (obj->effect_info && (obj->effect_info->type_flags & EF_VOLUME_LIT)) {
        scalar_r = std::min<float>(1, scalar + (obj->effect_info->dynamic_red));
        scalar_g = std::min<float>(1, scalar + (obj->effect_info->dynamic_green));
        scalar_b = std::min<float>(1, scalar + (obj->effect_info->dynamic_blue));
        // If this is a robot, make it at least 10% for each RGB component
        if (obj->type == OBJ_ROBOT) {
          scalar_r = std::max<float>(.1, scalar_r);
          scalar_g = std::max<float>(.1, scalar_g);
          scalar_b = std::max<float>(.1, scalar_b);
        }
        if (obj->type == OBJ_PLAYER && ((Players[obj->id].flags & PLAYER_FLAGS_HEADLIGHT) ||
                                        ((Game_mode & GM_MULTI) && (Netgame.flags & NF_BRIGHT_PLAYERS)))) {
          scalar_r = 1;
          scalar_g = 1;
          scalar_b = 1;
        }
      } else {
        scalar_r = scalar;
        scalar_g = scalar;
        scalar_b = scalar;
      }
    }

    if (obj->lighting_render_type == LRT_STATIC || Poly_models[obj->rtype.pobj_info.model_num].new_style == 0)
      RenderObject_SetStatic(scalar_r, scalar_g, scalar_b);
    else if (obj->lighting_render_type == LRT_GOURAUD || NoLightmaps) {
      vector lightdir = {0, -1.0, 0}; // straight down for now
      RenderObject_SetGouraud(&lightdir, scalar_r, scalar_g, scalar_b, scalar);
    } else if (obj->lighting_render_type == LRT_LIGHTMAPS) {
      if (obj->lm_object.used == 0)
        RenderObject_SetStatic(scalar_r, scalar_g, scalar_b);
      else
        RenderObject_SetLightmaps(&obj->lm_object);
    }
  } else {
    RenderObject_SetStatic(1, 1, 1);
  }
  return true;
}
// Sets up the light states for an indoor object to be rendered
bool SetupMineObject(object *objp) {
  if (objp->lighting_render_type == LRT_STATIC || Poly_models[objp->rtype.pobj_info.model_num].new_style == 0) {
    RenderObject_SetStatic(1.0f, 1.0f, 1.0f);
  } else if (objp->lighting_render_type == LRT_GOURAUD || NoLightmaps) {
    float scalar_r = 1.0, scalar_g = 1.0, scalar_b = 1.0;

    vector lightdir = {0, -1.0, 0}; // straight down for now

    // Get the volume light for this object
    if (objp->effect_info && (objp->effect_info->type_flags & EF_VOLUME_LIT) &&
        !(Rooms[objp->roomnum].flags & RF_EXTERNAL)) {
      vector vpos = objp->pos;
      if (Render_mirror_for_room)
        vpos = objp->last_pos;
      if (objp->effect_info->type_flags & EF_VOLUME_CHANGING) {
        float old_r, old_g, old_b;
        float new_r, new_g, new_b;
        GetRoomDynamicScalar(&objp->effect_info->volume_old_pos, &Rooms[objp->effect_info->volume_old_room], &old_r,
                             &old_g, &old_b);
        GetRoomDynamicScalar(&vpos, &Rooms[objp->roomnum], &new_r, &new_g, &new_b);
        scalar_r =
            (old_r * objp->effect_info->volume_change_time) + ((1 - objp->effect_info->volume_change_time) * new_r);
        scalar_g =
            (old_g * objp->effect_info->volume_change_time) + ((1 - objp->effect_info->volume_change_time) * new_g);
        scalar_b =
            (old_b * objp->effect_info->volume_change_time) + ((1 - objp->effect_info->volume_change_time) * new_b);
      } else
        GetRoomDynamicScalar(&vpos, &Rooms[objp->roomnum], &scalar_r, &scalar_g, &scalar_b);

      scalar_r = std::min<float>(1, scalar_r + (objp->effect_info->dynamic_red));
      scalar_g = std::min<float>(1, scalar_g + (objp->effect_info->dynamic_green));
      scalar_b = std::min<float>(1, scalar_b + (objp->effect_info->dynamic_blue));
      // If this is a robot, make it at least 10% for each RGB component
      if (objp->type == OBJ_ROBOT) {
        scalar_r = std::max<float>(.1, scalar_r);
        scalar_g = std::max<float>(.1, scalar_g);
        scalar_b = std::max<float>(.1, scalar_b);
      }

      if (objp->type == OBJ_PLAYER && (Game_mode & GM_MULTI)) {
        if (Netgame.flags & NF_BRIGHT_PLAYERS) {
          scalar_r = 1;
          scalar_g = 1;
          scalar_b = 1;
        } else {
          // Make this ship brighter based on its speed
          float speed_norm;
          speed_norm = std::min<float>(vm_GetMagnitudeFast(&objp->mtype.phys_info.velocity) / 20.0, 1);
          speed_norm *= 1;
          speed_norm += 1;
          scalar_r = std::min<float>(1, scalar_r * speed_norm);
          scalar_g = std::min<float>(1, scalar_g * speed_norm);
          scalar_b = std::min<float>(1, scalar_b * speed_norm);
        }
      }
      if (objp->type == OBJ_PLAYER && (Players[objp->id].flags & PLAYER_FLAGS_HEADLIGHT)) {
        scalar_r = 1;
        scalar_g = 1;
        scalar_b = 1;
      }
    }
    RenderObject_SetGouraud(&lightdir, scalar_r, scalar_g, scalar_b);
  } else if (objp->lighting_render_type == LRT_LIGHTMAPS) {
    if (objp->lm_object.used == 0)
      RenderObject_SetStatic(1.0f, 1.0f, 1.0f);
    else
      RenderObject_SetLightmaps(&objp->lm_object);
  }
  return true;
}

bool GetLinearPosition(vector *points, float *times, int num_points, float t, vector *pos) {
  // find between which points is the time
  int min_point;
  for (min_point = 0; min_point < num_points - 1; min_point++) {
    if (times[min_point] <= t && t <= times[min_point + 1]) {
      break;
    }
  }
  if (min_point == (num_points - 1))
    return false;
  ASSERT(times[min_point] <= t && t <= times[min_point + 1]);

  t -= times[min_point];
  float d = times[min_point + 1] - times[min_point];
  float newt = t / d;

  vector vd;
  float mag;
  vd = points[min_point + 1] - points[min_point];
  mag = vm_GetMagnitude(&vd);
  vm_NormalizeVector(&vd);
  vd *= (mag * newt);

  *pos = points[min_point] + vd;
  return true;
}

// -----------------------------------------------------------------------------
//	Render an object.  Calls one of several routines based on type
void RenderObject(object *obj) {
  float normalized_time[MAX_SUBOBJECTS];
  bool render_it = false;
  if (obj->type == OBJ_NONE) {
    mprintf(1, "ERROR!!!! Bogus obj %d in room %d is rendering!\n", OBJNUM(obj), obj->roomnum);
    Int3();
    return;
  }
  if (obj->type == OBJ_DUMMY)
    return;
  if (obj->flags & OF_ATTACHED) {
    // See if we should be rendered, because our attach parent might be invisible
    object *parent_obj = ObjGet(obj->attach_ultimate_handle);
    if (!parent_obj)
      return;
    if (parent_obj->render_type == RT_NONE && parent_obj->type != OBJ_POWERUP &&
        (parent_obj->type == OBJ_PLAYER || parent_obj->movement_type != MT_NONE))
      return;
  }
  if (OBJECT_OUTSIDE(obj))
    render_it = SetupTerrainObject(obj);
  else
    render_it = SetupMineObject(obj);
  if (!render_it)
    return;
  if (!(obj->flags & OF_SAFE_TO_RENDER))
    return;
  // Mark this a rendered this frame
  obj->flags |= OF_RENDERED;
  // If we're not rendering from a mirror, mark this object as rendered
  if (Render_mirror_for_room == false)
    obj->flags &= ~OF_SAFE_TO_RENDER;
  obj->renderframe = FrameCount % 65536;
  if (obj->control_type == CT_AI && (GetFunctionMode() == GAME_MODE || GetFunctionMode() == EDITOR_GAME_MODE)) {
    AI_RenderedList[AI_NumRendered] = OBJNUM(obj);
    AI_NumRendered += 1;
  }
#ifdef EDITOR
  ddgr_color oldcolor;
  if (TSearch_on && obj->type != OBJ_ROOM) {
    rend_SetPixel(GR_RGB(16, 255, 64), TSearch_x, TSearch_y);
    oldcolor = rend_GetPixel(TSearch_x, TSearch_y); // will be different in 15/16-bit color
  }
#endif
  switch (obj->render_type) {
  case RT_NONE:
    break;
  case RT_EDITOR_SPHERE: // to render objects in editor mode
#ifdef EDITOR
    if ((GetFunctionMode() == EDITOR_MODE)) { // only render if in editor mode
      if (!UseHardware) {
        g3Point sphere_point;
        g3_RotatePoint(&sphere_point, &obj->pos);
        g3_DrawSphere(obj->rtype.sphere_color, &sphere_point, obj->size);
      } else {
        // Let me take this opportunity to say how much it pisses me off that
        // the DrawColoredDisk() function takes r,g,b as floats, when the standard
        // in our graphics system is to pass color as a ddgr_color
        float r = (float)GR_COLOR_RED(obj->rtype.sphere_color) / 255.0,
              g = (float)GR_COLOR_GREEN(obj->rtype.sphere_color) / 255.0,
              b = (float)GR_COLOR_BLUE(obj->rtype.sphere_color) / 255.0;
        DrawColoredDisk(&obj->pos, r, g, b, 1, 1, obj->size, 0);
      }
    }
#endif
    break;
  case RT_POLYOBJ:
#ifdef EDITOR
    if ((GetFunctionMode() == EDITOR_MODE) && (OBJNUM(obj) == Cur_object_index))
      DrawObjectSelectionBrackets(obj, 0); // draw back brackets
#endif
    if (obj->rtype.pobj_info.anim_frame || (Poly_models[obj->rtype.pobj_info.model_num].frame_max !=
                                            Poly_models[obj->rtype.pobj_info.model_num].frame_min)) {
      SetNormalizedTimeObj(obj, normalized_time);
      RenderObject_DrawPolymodel(obj, normalized_time);
    } else {
      RenderObject_DrawPolymodel(obj, NULL);
    }

    ////////////////////////////////////////////
    /////////////MOTION BLUR////////////////////
    if (Use_motion_blur && (obj->type == OBJ_ROBOT || obj->type == OBJ_DEBRIS) &&
        Object_map_position_history[OBJNUM(obj)] != -1) {
      float vel_mag;                  // velocity magnitude
      float sphere_size_perc = 0.20f; // percentage of object size
      float AFT = 1.0f / 20.0f;       // Assumed frame time
      int num_iterations;             // number of iterations

      vel_mag = fabs(vm_GetMagnitude(&obj->mtype.phys_info.velocity));
      num_iterations = (vel_mag * AFT) / (sphere_size_perc * obj->size);

      if (num_iterations > 12)
        num_iterations = 12;

      if (num_iterations >= 1) {
        vector saved_pos;
        float saved_alpha_fac;
        vector positions[MAX_POSITION_HISTORY + 1];
        float times[MAX_POSITION_HISTORY + 1];

        // save the position of the object, because we'll have to restore it
        saved_pos = obj->pos;
        saved_alpha_fac = rend_GetAlphaFactor();

        int pos_slot = Object_map_position_history[OBJNUM(obj)];
        int i, c_pos = Object_position_head;

        // fill in the positions, starting with our current one
        for (i = 0; i < MAX_POSITION_HISTORY + 1; i++) {
          if (i == 0) {
            positions[i] = obj->pos;
            times[i] = 0;
          } else {
            positions[i] = Object_position_samples[pos_slot].pos[c_pos];
            times[i] = Gametime - Last_position_history_update[c_pos];
            c_pos++;
            c_pos = c_pos % MAX_POSITION_HISTORY;
          }
        }

        float t_interval; // time interval
        float alpha_step; // opacity stepping
        float total_time; // total time of samples

        t_interval = AFT / ((float)num_iterations + 1);
        alpha_step = 1.0f / (num_iterations + 1);
        total_time = times[MAX_POSITION_HISTORY] - times[0];
        ASSERT(total_time > 0);

        float curr_alpha = 1.0f - alpha_step;
        float curr_t = t_interval;
        float full_time = AFT / total_time; // how much of the interval we want to go across

        for (i = 0; i < num_iterations; i++) {
          if (!GetLinearPosition(positions, times, MAX_POSITION_HISTORY + 1, curr_t, &obj->pos))
            break;

          rend_SetAlphaFactor(curr_alpha);

          // render the iteration
          if (obj->rtype.pobj_info.anim_frame || (Poly_models[obj->rtype.pobj_info.model_num].frame_max !=
                                                  Poly_models[obj->rtype.pobj_info.model_num].frame_min)) {
            RenderObject_DrawPolymodel(obj, normalized_time);
          } else {
            RenderObject_DrawPolymodel(obj, NULL);
          }

          // update
          curr_alpha -= alpha_step;
          curr_t += t_interval;
        }

        obj->pos = saved_pos;
        rend_SetAlphaFactor(saved_alpha_fac);
      }
    }
    ////////////////////////////////////////////

#ifdef _DEBUG
    if (Game_show_sphere) {
      DrawDebugInfo(obj);
    }
#endif

    // Render that powerup glow
    if (obj->type == OBJ_POWERUP) {
      DrawPowerupGlowDisk(obj);
      DrawPowerupSparkles(obj);
    }

    if (obj->type == OBJ_PLAYER) {
      DrawPlayerDamageDisk(obj);
      DrawPlayerRotatingBall(obj);
      DrawPlayerNameOnHud(obj);
      DrawPlayerTypingIndicator(obj);
      DrawPlayerInvulSphere(obj);
    }
    if (obj->type == OBJ_PLAYER || obj->type == OBJ_ROBOT || (obj->type == OBJ_BUILDING && obj->ai_info)) {
      DrawSparkyDamageLightning(obj);
      DrawVirusLightning(obj);
    }

    break;
  case RT_FIREBALL:
    DrawFireballObject(obj);
    break;
  case RT_WEAPON:
    DrawWeaponObject(obj);

#ifdef _DEBUG
    if (Game_show_sphere) {
      DrawDebugInfo(obj);
    }
#endif
    break;
  case RT_SPLINTER:
    DrawSplinterObject(obj);
    break;
  case RT_SHARD:
    DrawShardObject(obj);
    break;
#ifdef _DEBUG
  case RT_LINE: {
    g3Point g3p[2];
    memset(g3p, 0, 2 * sizeof(g3Point));
    // g3p[0].p3_vec = obj->pos;
    // g3p[1].p3_vec = obj->rtype.line_info.end_pos;

    g3_RotatePoint(&g3p[0], &obj->pos);
    g3_RotatePoint(&g3p[1], &obj->rtype.line_info.end_pos);
    g3_DrawLine(GR_RGB(255, 255, 255), &g3p[0], &g3p[1]);
    break;
  }
#endif
  default:
    Error("Unknown render_type <%d>", obj->render_type);
  }
#ifdef NEWDEMO
  if (obj->render_type != RT_NONE)
    if (Newdemo_state == ND_STATE_RECORDING) {
      if (!WasRecorded[OBJNUM(obj)]) {
        newdemo_record_RenderObject(obj);
        WasRecorded[OBJNUM(obj)] = 1;
      }
    }
#endif
    //??	Max_linear_depth = mld_save;
    // Mark selected objects
#ifdef EDITOR
  if ((GetFunctionMode() == EDITOR_MODE) && (OBJNUM(obj) == Cur_object_index)) {
    if (obj->render_type != RT_POLYOBJ) {
      g3Point pnt;
      g3_RotatePoint(&pnt, &obj->pos);
      g3_DrawBox(GR_RGB(255, 255, 255), &pnt, obj->size);
    } else {                               // polygon model
      DrawObjectSelectionBrackets(obj, 1); // draw front brackets
    }
  }
#endif // ifdef EDITOR
#ifdef EDITOR
  if (TSearch_on) {
    if (rend_GetPixel(TSearch_x, TSearch_y) != oldcolor) {
      TSearch_found_type = TSEARCH_FOUND_OBJECT;
      TSearch_seg = OBJNUM(obj);
      mprintf(0, "TR:objnum=%d\n", OBJNUM(obj));
    }
  }
#endif
}
// Sets the polygon render object type to static (one lightval for whole object)
void RenderObject_SetStatic(float r, float g, float b) {
  RenderObjectType = RO_STATIC;
  RenderObjectStaticRedValue = r;
  RenderObjectStaticGreenValue = g;
  RenderObjectStaticBlueValue = b;
  RenderObjectStaticScalar = 1.0;
}
// Sets the polygon render object type to gouraud (one lightval for each vertex)
void RenderObject_SetGouraud(vector *dir, float r, float g, float b, float scalar) {
  RenderObject_LightDirection = *dir;
  RenderObjectStaticRedValue = r;
  RenderObjectStaticGreenValue = g;
  RenderObjectStaticBlueValue = b;
  RenderObjectStaticScalar = scalar;
  RenderObjectType = RO_GOURAUD;
}
// Sets the object render to draw a polymodel with lightmaps applied
void RenderObject_SetLightmaps(lightmap_object *lmobject) {
  ASSERT(lmobject->used);
  RenderObjectType = RO_LIGHTMAPS;
  RenderObjectLightmapObject = lmobject;
}

std::array<ddgr_color, 32> Player_colors = {
    GR_RGB(255, 0, 0),     GR_RGB(0, 32, 255),   GR_RGB(0, 255, 0),   GR_RGB(255, 255, 0),   GR_RGB(32, 64, 96),
    GR_RGB(255, 0, 255),   GR_RGB(255, 128, 0),  GR_RGB(128, 128, 0), GR_RGB(0, 128, 0),     GR_RGB(0, 32, 128),
    GR_RGB(0, 128, 128),   GR_RGB(128, 0, 128),  GR_RGB(128, 0, 0),   GR_RGB(128, 128, 255), GR_RGB(255, 128, 255),
    GR_RGB(255, 128, 128), GR_RGB(128, 64, 0),   GR_RGB(128, 0, 255), GR_RGB(0, 255, 128),   GR_RGB(255, 64, 0),
    GR_RGB(128, 255, 0),   GR_RGB(255, 0, 128),  GR_RGB(64, 64, 128), GR_RGB(128, 64, 64),   GR_RGB(255, 192, 128),
    GR_RGB(255, 255, 128), GR_RGB(128, 128, 64), GR_RGB(64, 128, 64), GR_RGB(128, 0, 64),    GR_RGB(255, 192, 0),
    GR_RGB(255, 255, 255), GR_RGB(128, 128, 128)};

bool is_multi_demo = false;

// Actually draws a polygon model based on the light parameters set by the above
// functions
void RenderObject_DrawPolymodel(object *obj, float *normalized_times) {
  int model_num;
  int use_effect = 0;
  vector obj_pos = obj->pos;
  polymodel_effect pe = {0};

  // Do cloak effect on player
  if (UseHardware) {
    if (obj->effect_info && (obj->effect_info->type_flags & EF_FADING_OUT)) {
      pe.type = PEF_ALPHA;
      pe.alpha = .08 + (.92 * (obj->effect_info->fade_time / obj->effect_info->fade_max_time));
      use_effect = 1;
    }
    if (obj->effect_info && (obj->effect_info->type_flags & EF_FADING_IN)) {
      pe.type = PEF_ALPHA;
      pe.alpha = .08 + (.92 * (1.0 - (obj->effect_info->fade_time / obj->effect_info->fade_max_time)));
      use_effect = 1;
    }
    if (obj->effect_info && (obj->effect_info->type_flags & EF_CLOAKED)) {
      pe.type = PEF_ALPHA | PEF_DEFORM;
      pe.alpha = .13f;
      pe.deform_range = .1f;

      use_effect = 1;
    }
    if (obj->type == OBJ_PLAYER) {
      // Draw thrust/afterburner cooler
      pe.type |= PEF_GLOW_SCALAR;
      pe.glow_length_scalar = (Players[obj->id].thrust_mag);
      pe.glow_size_scalar = (Players[obj->id].thrust_mag);

      pe.glow_length_scalar += (Players[obj->id].afterburner_mag * 3);
      pe.glow_size_scalar += (Players[obj->id].afterburner_mag * .5);
      float adjustment = (ps_rand() % 100 - 50);
      adjustment /= 50.0;
      pe.glow_length_scalar += (.2 * adjustment);

      use_effect = 1;
      // Make Katmai glows longer
      if (Katmai) {
        pe.glow_length_scalar *= 1.5;
      }
      // hack to make multiplayer demos work!
      if (is_multi_demo || (Game_mode & GM_MULTI)) {
        if (Num_teams > 1) {
          int teamnum = PlayerGetTeam(obj->id);

          pe.type |= PEF_CUSTOM_COLOR | PEF_CUSTOM_GLOW;
          pe.custom_color = Player_colors[teamnum];
          pe.glow_r = GR_COLOR_RED(pe.custom_color) / 255.0;
          pe.glow_g = GR_COLOR_GREEN(pe.custom_color) / 255.0;
          pe.glow_b = GR_COLOR_BLUE(pe.custom_color) / 255.0;

          use_effect = 1;
        } else {
          pe.type |= PEF_CUSTOM_COLOR;
          pe.custom_color = Player_colors[obj->id];

          use_effect = 1;
        }
        if (Multi_logo_state && GameTextures[Players[obj->id].custom_texture_handle].bm_handle != 0) {
          pe.type |= PEF_CUSTOM_TEXTURE;

          pe.custom_texture = Players[obj->id].custom_texture_handle;

          use_effect = 1;
        }
      }
    }
    // Deform this object if needed
    if (obj->effect_info && (obj->effect_info->type_flags & EF_DEFORM)) {
      pe.type |= PEF_DEFORM;
      pe.deform_range = obj->effect_info->deform_range * obj->effect_info->deform_time;
      float val = obj->effect_info->deform_time;
      if (val > 1)
        val = 1;

      pe.type |= PEF_COLOR;
      pe.r = 1.0;
      pe.g = 1 - (val / 2);
      pe.b = 1 - (val / 2);

      use_effect = 1;
    }
    // If the viewer is deformed, warp his view somewhat
    if (Viewer_object->effect_info && (Viewer_object->effect_info->type_flags & EF_DEFORM)) {
      pe.type |= PEF_DEFORM;
      pe.deform_range = Viewer_object->effect_info->deform_range * Viewer_object->effect_info->deform_time;
      float val = Viewer_object->effect_info->deform_time;
      if (val > 1)
        val = 1;

      use_effect = 1;
      // switch object position a little
      float moveval = 10.0 * val * Viewer_object->effect_info->deform_range;
      obj_pos.x += (((ps_rand() % 1000) - 500) / 500.0) * moveval;
      obj_pos.y += (((ps_rand() % 1000) - 500) / 500.0) * moveval;
      obj_pos.z += (((ps_rand() % 1000) - 500) / 500.0) * moveval;
    }
    // If this is a powerup, fade it out near the end of its life
    if (obj->type == OBJ_POWERUP && (obj->flags & OF_USES_LIFELEFT) && obj->lifeleft < 5) {
      pe.type |= PEF_ALPHA | PEF_DEFORM;
      pe.alpha = obj->lifeleft / 5.0;
      pe.deform_range = .2f * (1.0 - (obj->lifeleft / 5.0));

      use_effect = 1;
    }
    // Fog this object if needed
    if (!OBJECT_OUTSIDE(obj) && (Rooms[obj->roomnum].flags & RF_FOG) && Room_fog_plane_check != -1) {
      pe.type |= PEF_FOGGED_MODEL;
      pe.fog_distance = Room_fog_distance;
      pe.fog_eye_distance = Room_fog_eye_distance;
      pe.fog_plane_check = Room_fog_plane_check;
      pe.fog_portal_vert = Room_fog_portal_vert;
      pe.fog_plane = Room_fog_plane;
      pe.fog_depth = Rooms[obj->roomnum].fog_depth;
      pe.fog_r = Rooms[obj->roomnum].fog_r;
      pe.fog_g = Rooms[obj->roomnum].fog_g;
      pe.fog_b = Rooms[obj->roomnum].fog_b;

      use_effect = 1;
    }
    // Apply specularity from dynamic lights
    if (obj->effect_info) {
      if ((obj->effect_info->type_flags & EF_SPECULAR)) {
        if (obj->type == OBJ_POWERUP)
          pe.type |= PEF_SPECULAR_MODEL;
        else
          pe.type |= PEF_SPECULAR_FACES;

        pe.spec_light_pos = obj->effect_info->spec_pos;
        pe.spec_r = obj->effect_info->spec_r;
        pe.spec_g = obj->effect_info->spec_g;
        pe.spec_b = obj->effect_info->spec_b;
        pe.spec_scalar = 1.0;
        use_effect = 1;
      }
    }
    // Apply specularity from outdoor satellites
    if (OBJECT_OUTSIDE(obj) && obj->lighting_render_type == LRT_GOURAUD && Detail_settings.Specular_lighting &&
        !(Object_info[obj->id].lighting_info.flags & OLF_NO_SPECULARITY)) {
      if (obj->effect_info && !(obj->effect_info->type_flags & EF_SPECULAR)) {
        if (obj->type == OBJ_POWERUP)
          pe.type |= PEF_SPECULAR_MODEL;
        else
          pe.type |= PEF_SPECULAR_FACES;

        pe.spec_light_pos = Terrain_sky.satellite_vectors[0];
        pe.spec_r = 1.0;
        pe.spec_g = 1.0;
        pe.spec_b = 1.0;
        pe.spec_scalar = RenderObjectStaticScalar;
        use_effect = 1;
      }
    }
    if (Detail_settings.Bumpmapping_enabled && (obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER)) {
      pe.bump_light_pos = obj->pos;
      pe.bump_light_pos.y += 100;
      pe.bump_scalar = 1;
      pe.type |= PEF_BUMPMAPPED;
      use_effect = 1;
    }
  }
  // Pick a lod model to use if eligible
  if (obj->lighting_render_type == LRT_STATIC || obj->lighting_render_type == LRT_GOURAUD) {
    if (obj->type == OBJ_POWERUP || obj->type == OBJ_ROBOT || obj->type == OBJ_CLUTTER) {
      g3Point pnt;
      float detail_scalar = 1.0;
      g3_RotatePoint(&pnt, &obj->pos);
      if (Detail_settings.Object_complexity == 0)
        detail_scalar = .6f;
      else if (Detail_settings.Object_complexity == 2)
        detail_scalar = 1.2f;
      if (pnt.p3_z < (Object_info[obj->id].med_lod_distance * detail_scalar))
        model_num = obj->rtype.pobj_info.model_num;
      else if (pnt.p3_z < (Object_info[obj->id].lo_lod_distance * detail_scalar)) {
        if (Object_info[obj->id].med_render_handle != -1)
          model_num = Object_info[obj->id].med_render_handle;
        else {
          model_num = obj->rtype.pobj_info.model_num;
        }
      } else {
        if (Object_info[obj->id].lo_render_handle != -1)
          model_num = Object_info[obj->id].lo_render_handle;
        else {
          model_num = obj->rtype.pobj_info.model_num;
          if (Object_info[obj->id].med_render_handle != -1)
            model_num = Object_info[obj->id].med_render_handle;
          else
            model_num = obj->rtype.pobj_info.model_num;
        }
      }
    } else if (obj->type == OBJ_MARKER) {
      model_num = Marker_polynum;
    } else if (obj->type == OBJ_PLAYER && !(Players[obj->id].flags & (PLAYER_FLAGS_DYING | PLAYER_FLAGS_DEAD))) {
      g3Point pnt;
      g3_RotatePoint(&pnt, &obj->pos);
      int ship_num = Players[obj->id].ship_index;
      float detail_scalar = 1.0;
      if (Detail_settings.Object_complexity == 0)
        detail_scalar = .6f;
      else if (Detail_settings.Object_complexity == 2)
        detail_scalar = 1.2f;
      if (pnt.p3_z < (Ships[ship_num].med_lod_distance * detail_scalar))
        model_num = obj->rtype.pobj_info.model_num;
      else if (pnt.p3_z < (Ships[ship_num].lo_lod_distance * detail_scalar)) {
        if (Ships[ship_num].med_render_handle != -1)
          model_num = Ships[ship_num].med_render_handle;
        else {
          model_num = obj->rtype.pobj_info.model_num;
        }
      } else {
        if (Ships[ship_num].lo_render_handle != -1)
          model_num = Ships[ship_num].lo_render_handle;
        else {
          model_num = obj->rtype.pobj_info.model_num;
          if (Ships[ship_num].med_render_handle != -1)
            model_num = Ships[ship_num].med_render_handle;
          else
            model_num = obj->rtype.pobj_info.model_num;
        }
      }
    } else
      model_num = obj->rtype.pobj_info.model_num;
  } else
    model_num = obj->rtype.pobj_info.model_num;
  if (obj->type == OBJ_BUILDING && obj->flags & OF_USE_DESTROYED_POLYMODEL) {
    if (Object_info[obj->id].lo_render_handle != -1)
      model_num = Object_info[obj->id].lo_render_handle;
  }
  // Set effects
  if (use_effect)
    SetPolymodelEffect(&pe);
  if (RenderObjectType == RO_STATIC) {
    // Draw this object with static light
    int overlay = 0;
    if ((obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER) && obj->rtype.pobj_info.subobj_flags != 0xFFFFFFFF)
      overlay = 1;

    DrawPolygonModel(&obj_pos, &obj->orient, model_num, normalized_times, 0, RenderObjectStaticRedValue,
                     RenderObjectStaticGreenValue, RenderObjectStaticBlueValue, obj->rtype.pobj_info.subobj_flags,
                     use_effect, overlay);
  } else if (RenderObjectType == RO_GOURAUD || NoLightmaps) {
    // Draw this object with gouraud static light
    int overlay = 0;
    if ((obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER) && obj->rtype.pobj_info.subobj_flags != 0xFFFFFFFF)
      overlay = 1;
    DrawPolygonModel(&obj_pos, &obj->orient, model_num, normalized_times, 0, &RenderObject_LightDirection,
                     RenderObjectStaticRedValue, RenderObjectStaticGreenValue, RenderObjectStaticBlueValue,
                     obj->rtype.pobj_info.subobj_flags, use_effect, overlay);
  } else if (RenderObjectType == RO_LIGHTMAPS) {
    int overlay = 0;
    if ((obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER) && obj->rtype.pobj_info.subobj_flags != 0xFFFFFFFF)
      overlay = 1;
    // If this object is a destroyed building then do something different with it
    DrawPolygonModel(&obj_pos, &obj->orient, model_num, normalized_times, 0, RenderObjectLightmapObject,
                     obj->rtype.pobj_info.subobj_flags, use_effect, overlay);
  } else
    Int3(); // Get Jason
}
// Sets the direction of the lightsource to be used when calculating vertex lighting
// The light source vector should be in the models coordinate space
void RenderObject_SetLightDirection(vector *dir) { RenderObject_LightDirection = *dir; }
// draw an object that has one bitmap & doesn't rotate
void obj_draw_blob(object *obj, int bmnum) {
  //	int	orientation=0;
  //	grs_bitmap * bm = &GameBitmaps[bmnum];
  //
  //
  //	if (obj->type == OBJ_FIREBALL)
  //		orientation = (obj-Objects) & 7;
  //
  //	orientation = global_orientation;
  //
  //	PIGGY_PAGE_IN( bmi );
  //
  //	if (bm->bm_w > bm->bm_h)
  //
  //		g3_draw_bitmap(&obj->pos,obj->size,fixmuldiv(obj->size,bm->bm_h,bm->bm_w),bm, orientation);
  //
  //	else
  //
  //		g3_draw_bitmap(&obj->pos,fixmuldiv(obj->size,bm->bm_w,bm->bm_h),obj->size,bm, orientation);
}
extern float Far_clip_z;
int Point_visible_last_frame = -1;
// Given a position in 3space and a size, returns whether or not that sized point is
// visible from the current view matrix
int IsPointVisible(vector *pos, float size, float *pointz) {
  g3Point pnt;
  uint8_t ccode;
  static float last_render_fov = -1;
  static vector left_normal, right_normal, top_normal, bottom_normal, view_position;
  static matrix unscaled_matrix;

  g3_RotatePoint(&pnt, pos);
  ccode = g3_CodePoint(&pnt);
  if (pointz != NULL)
    *pointz = pnt.p3_z;
  if (ccode) // the center point is off, find out if the whole object is off
  {
    float dotp;

    if (pnt.p3_z < -size)
      return 0; // behind plane!
    if (pnt.p3_z > Far_clip_z + size)
      return 0; // too far away!
    if (Render_FOV != last_render_fov) {
      last_render_fov = Render_FOV;
      int angle_adjust = (Render_FOV / 2) * (65536 / 360);
      vector rvec = {1, 0, 0};
      vector lvec = {-1, 0, 0};
      vector tvec = {0, 1, 0};
      vector bvec = {0, -1, 0};
      matrix temp_mat;
      vm_AnglesToMatrix(&temp_mat, 0, 65536 - angle_adjust, 0);
      right_normal = rvec * temp_mat;
      vm_AnglesToMatrix(&temp_mat, 0, angle_adjust, 0);
      left_normal = lvec * temp_mat;
      vm_AnglesToMatrix(&temp_mat, 65536 - angle_adjust, 0, 0);
      bottom_normal = bvec * temp_mat;
      vm_AnglesToMatrix(&temp_mat, angle_adjust, 0, 0);
      top_normal = tvec * temp_mat;
    }
    // Get unscaled matrix stuff
    if (Point_visible_last_frame != FrameCount) {
      Point_visible_last_frame = FrameCount;
      g3_GetUnscaledMatrix(&unscaled_matrix);
      g3_GetViewPosition(&view_position);
    }
    vector temp_vec = *pos - view_position;
    pnt.p3_vec = temp_vec * unscaled_matrix;
    if (ccode & CC_OFF_RIGHT) {
      dotp = vm_DotProduct(&right_normal, &pnt.p3_vec);
      if (dotp > size)
        return 0;
    }
    if (ccode & CC_OFF_LEFT) {
      dotp = vm_DotProduct(&left_normal, &pnt.p3_vec);
      if (dotp > size)
        return 0;
    }

    if (ccode & CC_OFF_TOP) {
      dotp = vm_DotProduct(&top_normal, &pnt.p3_vec);
      if (dotp > size)
        return 0;
    }
    if (ccode & CC_OFF_BOT) {
      dotp = vm_DotProduct(&bottom_normal, &pnt.p3_vec);
      if (dotp > size)
        return 0;
    }
    return 1;
  }
  // Center point is on, must be visible
  return 1;
}

// Do powerup sparkles and stuff
void DrawPowerupSparkles(object *obj) {
  extern bool Render_mirror_for_room;
  if (!Render_powerup_sparkles)
    return;

  if (Game_paused)
    return;

  // we want to render if
  // a) we are not rendering in a mirror
  // b) we are rendering a mirror but the object is not visible from our position
  if (Render_mirror_for_room && !IsPointVisible(&obj->pos, obj->size, NULL))
    return;

  if (obj->render_type != RT_POLYOBJ)
    return;

  // check to see if it's time to update
  if (Last_powerup_sparkle_time < POWERUP_SPARKLE_INTERVAL)
    return;

  int num_sparks = ps_rand() & 7;
  float obj_size_delta = obj->size * 0.3f;

  // Create some sparks
  for (int i = 0; i < num_sparks; ++i) {
    const int randnum = ps_rand() % 10;

    int index;
    switch (randnum) {
    case 0:
      index = HOT_SPARK_INDEX;
      break;
    case 1:
      index = COOL_SPARK_INDEX;
      break;
    default:
      index = GRAY_SPARK_INDEX;
      break;
    }

    vector pos_delta;
    pos_delta.x = (ps_rand() % 100) - 50;
    pos_delta.y = (ps_rand() % 100) - 80;
    pos_delta.z = (ps_rand() % 100) - 50;
    vm_NormalizeVector(&pos_delta);
    pos_delta = obj->last_pos + (obj_size_delta * pos_delta);

    int sparknum = VisEffectCreate(VIS_FIREBALL, index, obj->roomnum, &pos_delta);
    if (sparknum >= 0) {
      vis_effect *vis = &VisEffects[sparknum];

      vis->end_pos = vis->pos;
      vis->movement_type = MT_PHYSICS;
      vis->mass = 1000.0f;
      vis->drag = 0.2f;
      vis->phys_flags |= PF_GRAVITY | PF_NO_COLLIDE;

      vis->velocity.x = (ps_rand() % 50) - 25;
      vis->velocity.y = -10 - (ps_rand() % 20);
      vis->velocity.z = (ps_rand() % 50) - 25;
      vm_NormalizeVector(&vis->velocity);
      vis->velocity *= 3.0f + (ps_rand() % 4);

      vis->size = 0.05f + ((ps_rand() % 10) * 0.008f);
      vis->flags |= VF_USES_LIFELEFT;

      const float lifetime = 0.25f + ((ps_rand() % 10) * 0.05f);
      vis->lifeleft = lifetime;
      vis->lifetime = lifetime;

      light_info *li = ObjGetLightInfo(obj);
      if (li) {
        vis->lighting_color = GR_RGB16(li->red_light1 * 255.0f, li->green_light1 * 255.0f, li->blue_light1 * 255.0f);
      } else {
        vis->lighting_color = GR_RGB16(255, 255, 255);
      }
    }
  }
}

#define POWERUP_HALO_ALPHA .3f
// Draws the glowing disk around a powerup
void DrawPowerupGlowDisk(object *obj) {
  ASSERT(obj->type == OBJ_POWERUP);
  if (!Detail_settings.Powerup_halos)
    return;
  if (obj->render_type == RT_NONE)
    return;
  if (Viewer_object->effect_info && Viewer_object->effect_info->type_flags & EF_DEFORM)
    return;
  light_info *li = ObjGetLightInfo(obj);
  int objnum = OBJNUM(obj);
  float size_adjust = FixSin((objnum * 5000) + (FrameCount * 600));
  size_adjust += 1.0;
  size_adjust /= 2; // now in range 0 to 1.0
  size_adjust += .5;
  vector subvec = obj->pos - Viewer_object->pos;
  float mag = vm_GetMagnitudeFast(&subvec);
  if (mag < 40)
    return;

  float alpha_scalar = 1;
  if (obj->flags & OF_USES_LIFELEFT) {
    if (obj->lifeleft < 5)
      alpha_scalar = (obj->lifeleft / 5.0);
  }
  if (mag < 70) {
    alpha_scalar *= ((mag - 40) / 30.0);
  }

  // Draw lo-res disk
  DrawColoredDisk(&obj->pos, li->red_light1, li->green_light1, li->blue_light1, POWERUP_HALO_ALPHA * alpha_scalar, 0.0f,
                  (obj->size / 2) + size_adjust, 0, 2);
}
// Draws the glowing disk around a player indicating damage
void DrawPlayerDamageDisk(object *obj) {
  // if (!(Game_mode & GM_MULTI))
  //	return;		// only in multiplayer

  ASSERT(obj->type == OBJ_PLAYER);
  if (obj == Viewer_object)
    return; // don't do me
  float damage_norm = Players[obj->id].damage_magnitude / MAX_DAMAGE_MAG;
  if (damage_norm > 1.0)
    damage_norm = 1.0;
  if (damage_norm < .001)
    return;
  rend_SetZBias(-obj->size);
  int bm_handle;
  int objnum = OBJNUM(obj);
  float rot_temp = .25; // Higher is faster
  int int_game = Gametime / rot_temp;
  float diff = Gametime - (int_game * rot_temp);
  int rot_angle = diff * 65536;
  rot_angle = 0;
  bm_handle = Fireballs[SHIP_HIT_INDEX].bm_handle;

  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetZBufferWriteMask(0);

  rend_SetAlphaValue(.4 * damage_norm * 255);
  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);
  g3_DrawRotatedBitmap(&obj->pos, rot_angle, obj->size, (obj->size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0),
                       bm_handle);
  rend_SetZBufferWriteMask(1);
  rend_SetZBias(0);
}
// Draws the red sphere around a player indicating invulnerability
void DrawPlayerInvulSphere(object *obj) {
  // if (!(Game_mode & GM_MULTI))
  //	return;		// only in multiplayer

  ASSERT(obj->type == OBJ_PLAYER);
  if (Viewer_object == obj)
    return; // don't do me
  if (!(Players[obj->id].flags & PLAYER_FLAGS_INVULNERABLE))
    return;
  if (Players[obj->id].invul_magnitude < .05)
    return;

  int bm_handle = Fireballs[INVUL_HIT_INDEX].bm_handle;
  // Figure out the position and orientation to draw this
  vector hit_pos = obj->pos + (Players[obj->id].invul_vector * obj->size);
  vector norm_vec = Players[obj->id].invul_vector;
  // Check to see that we're ok with the length of the vector
  float mag = vm_GetMagnitudeFast(&norm_vec);
  if (mag < 1)
    return;
  norm_vec /= mag;

  // Now draw!
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetZBufferWriteMask(0);
  rend_SetAlphaValue(.6 * Players[obj->id].invul_magnitude * 255);
  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);
  g3_DrawPlanarRotatedBitmap(&hit_pos, &norm_vec, 0, 3, 3, bm_handle);
  rend_SetZBufferWriteMask(1);
}
// Draws a rotating ball around the player
void DrawPlayerRotatingBall(object *obj) {
  ASSERT(obj->type == OBJ_PLAYER);
  if (Players[obj->id].num_balls < 1)
    return;
  static int first = 1;
  static int bm_handle;
  vector worldpos;
  rend_SetColorModel(CM_RGB);
  rend_SetLighting(LS_GOURAUD);
  rend_SetTextureType(TT_LINEAR);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetAlphaValue(.3 * 255);
  rend_SetZBufferWriteMask(0);
  if (first) {
    int texhandle = FindTextureName("WhiteGlowingBall");
    if (texhandle == -1)
      bm_handle = 0;
    else
      bm_handle = GetTextureBitmap(texhandle, 0);
    first = 0;
  }
  for (int i = 0; i < Players[obj->id].num_balls; i++) {
    PlayerGetBallPosition(&worldpos, obj->id, i);
    // Get color of balls
    ddgr_color color =
        GR_RGB(Players[obj->id].ball_r[i] * 255, Players[obj->id].ball_g[i] * 255, Players[obj->id].ball_b[i] * 255);
    g3_DrawBitmap(&worldpos, obj->size / 4, ((obj->size / 4) * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle,
                  color);
  }
  rend_SetZBufferWriteMask(1);
}
// Draws the 'typing message' icon indicator above an object
void DrawPlayerTypingIndicator(object *obj) {
  if (!(Game_mode & GM_MULTI))
    return;
  int slot = obj->id;
  if (slot == Player_num)
    return;
  if (NetPlayers[slot].sequence != NETSEQ_PLAYING)
    return;
  uint32_t bit = (0x01 << slot);
  if (!(Players_typing & bit))
    return;
  if (obj->effect_info && obj->effect_info->type_flags & EF_CLOAKED)
    return;
  static int type_indicator_model = -2;
  if (type_indicator_model == -2)
    type_indicator_model = FindTextureName("TypingIndicator");
  if (type_indicator_model < 0)
    return;
  int bm_handle = GetTextureBitmap(type_indicator_model, 0);
  float IndicatorTan;
  float rad = (float)(3.14 * (float)(10) / 180.0);
  IndicatorTan = tan(rad);
  // See if its in our viewcone
  vector subvec = obj->pos - Player_object->pos;
  vm_NormalizeVectorFast(&subvec);
  if ((vm_DotProduct(&subvec, &Player_object->orient.fvec)) < IndicatorTan)
    return;
  if ((vm_VectorDistanceQuick(&Viewer_object->pos, &obj->pos) > 800.0f))
    return;
  // Find out if it is o.k. to draw here.
  fvi_query fq;
  fvi_info hit_data;
  int fate;
  fq.p0 = &Player_object->pos;
  fq.startroom = Player_object->roomnum;
  fq.p1 = &obj->pos;
  fq.rad = 0;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;
  fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS;
  fate = fvi_FindIntersection(&fq, &hit_data);
  if (fate == HIT_NONE || (fate == HIT_SPHERE_2_POLY_OBJECT && hit_data.hit_object[0] == (OBJNUM(obj)))) {
    // Draw this indicator on the hud
    g3Point pnt;
    int bmh, bmw;
    g3Point *pntlist[32], points[4];
    g3Codes cc;
    uint8_t code;

    cc.cc_and = 0xFF;
    cc.cc_or = 0;

    int b_w = std::min(bm_w(bm_handle, 0), 32);
    int b_h = std::min(bm_h(bm_handle, 0), 32);
    bmw = b_w / 2;
    bmh = b_h / 2;

    g3_RotatePoint(&pnt, fq.p1);
    g3_ProjectPoint(&pnt);

    points[0].p3_vec.x = pnt.p3_vec.x - bmw;
    points[0].p3_vec.y = pnt.p3_vec.y + bmh + 5;
    points[0].p3_vec.z = pnt.p3_vec.z;
    points[0].p3_u = 0;
    points[0].p3_v = 0;

    points[1].p3_vec.x = pnt.p3_vec.x + bmw;
    points[1].p3_vec.y = pnt.p3_vec.y + bmh + 5;
    points[1].p3_vec.z = pnt.p3_vec.z;
    points[1].p3_u = 1;
    points[1].p3_v = 0;

    points[2].p3_vec.x = pnt.p3_vec.x + bmw;
    points[2].p3_vec.y = pnt.p3_vec.y - bmh + 5;
    points[2].p3_vec.z = pnt.p3_vec.z;
    points[2].p3_u = 1;
    points[2].p3_v = 1;

    points[3].p3_vec.x = pnt.p3_vec.x - bmw;
    points[3].p3_vec.y = pnt.p3_vec.y - bmh + 5;
    points[3].p3_vec.z = pnt.p3_vec.z;
    points[3].p3_u = 0;
    points[3].p3_v = 1;

    for (int i = 0; i < 4; i++) {
      points[i].p3_flags |= PF_UV;
      pntlist[i] = &points[i];
      code = g3_CodePoint(pntlist[i]);
      g3_ProjectPoint(pntlist[i]);

      cc.cc_and &= code;
      cc.cc_or |= code;
    }
    rend_SetAlphaType(AT_CONSTANT_TEXTURE);
    rend_SetAlphaValue(200);
    rend_SetWrapType(WT_CLAMP);
    rend_SetLighting(LS_NONE);
    rend_SetOverlayType(OT_NONE);
    rend_SetColorModel(CM_MONO);
    rend_SetTextureType(TT_LINEAR);
    g3_DrawPoly(4, pntlist, bm_handle, 0, &cc);
  }
}
// Draws the player name on the hud
void DrawPlayerNameOnHud(object *obj) {
  if (!(Game_mode & GM_MULTI))
    return;
  int slot = obj->id;
  int color;
  if (slot == Player_num)
    return;
  if (NetPlayers[slot].sequence != NETSEQ_PLAYING)
    return;
  if (HudNameTan <= 0)
    return;
  if (obj->effect_info && obj->effect_info->type_flags & EF_CLOAKED)
    return;

  // Get color to draw this name in
  DLLInfo.me_handle = obj->handle;
  CallGameDLL(EVT_CLIENT_GETCOLOREDNAME, &DLLInfo);
  color = DLLInfo.iRet;
  if (color < 0)
    return;

  // See if its in our viewcone
  vector subvec = obj->pos - Player_object->pos;
  vm_NormalizeVectorFast(&subvec);
  if ((vm_DotProduct(&subvec, &Player_object->orient.fvec)) < HudNameTan)
    return;
  // Find out if it is o.k. to draw here.
  fvi_query fq;
  fvi_info hit_data;
  int fate;
  fq.p0 = &Player_object->pos;
  fq.startroom = Player_object->roomnum;
  fq.p1 = &obj->pos;
  fq.rad = 0;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;
  fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS;
  fate = fvi_FindIntersection(&fq, &hit_data);
  if (fate == HIT_NONE || (fate == HIT_SPHERE_2_POLY_OBJECT && hit_data.hit_object[0] == (OBJNUM(obj)))) {
    int half = Game_window_w / 2;
    // Draw this name on the hud
    g3Point pnt;
    g3_RotatePoint(&pnt, fq.p1);
    g3_ProjectPoint(&pnt);
    //	put a centered name string in the text buffer.

    grtext_SetFont(HUD_FONT);
    grtext_SetColor(color);
    grtext_CenteredPrintf(pnt.p3_sx - half, pnt.p3_sy, Players[slot].callsign);
    grtext_Flush();
  }
}
// Creates lightning sparks on a damaged object
void DrawSparkyDamageLightning(object *obj) {
  float max_shields = 100;
  if (obj->type == OBJ_ROBOT || obj->type == OBJ_CLUTTER || obj->type == OBJ_BUILDING)
    max_shields = Object_info[obj->id].hit_points;
  if (obj->type == OBJ_PLAYER)
    max_shields = INITIAL_SHIELDS;
  // If less than 30% shields, make some lightning every now and then
  if (max_shields > 0 && (obj->shields / max_shields) < .3 && obj->shields >= 0) {
    float shield_norm = (obj->shields / max_shields) / .3;
    shield_norm = 1 - shield_norm;
    ASSERT(shield_norm >= 0 && shield_norm <= 1);
    int shield_modulo = 20 - (12 * shield_norm);
    if (shield_modulo < 1)
      shield_modulo = 1;
    if ((ps_rand() % shield_modulo) == 0) {
      poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
      if (pm->n_models == 0)
        return;
      int subnum = ps_rand() % pm->n_models;
      if (IsNonRenderableSubmodel(pm, subnum))
        return;

      bsp_info *sm = &pm->submodel[subnum];
      if (sm->nverts == 0)
        return;
      int visnum = VisEffectCreate(VIS_FIREBALL, LIGHTNING_BOLT_INDEX, obj->roomnum, &obj->pos);
      if (visnum >= 0) {
        vis_effect *vis = &VisEffects[visnum];
        vis->lifeleft = 1.0;
        vis->lifetime = 1.0;
        vis->end_pos = obj->pos;
        vis->velocity.x = .15f;
        vis->velocity.y = 3;
        vis->attach_info.obj_handle = obj->handle;
        vis->attach_info.subnum = subnum;
        vis->attach_info.vertnum = ps_rand() % sm->nverts;
        vis->attach_info.end_vertnum = ps_rand() % sm->nverts;
        vis->attach_info.modelnum = obj->rtype.pobj_info.model_num;
        vis->flags = VF_USES_LIFELEFT | VF_EXPAND | VF_ATTACHED;
      }
    }
  }
}

// Creates Virus infected lightning on an object
void DrawVirusLightning(object *obj) {
  if (!obj->effect_info)
    return;
  if (!(obj->effect_info->type_flags & EF_VIRUS_INFECTED))
    return;

  float shield_norm = (float)(ps_rand() % D3_RAND_MAX) / (float)D3_RAND_MAX;
  shield_norm = 1 - shield_norm;

  ASSERT(shield_norm >= 0 && shield_norm <= 1);
  int shield_modulo = 20 - (16 * shield_norm);
  if (shield_modulo < 1)
    shield_modulo = 1;
  if ((ps_rand() % shield_modulo) == 0) {
    poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
    if (pm->n_models == 0)
      return;
    int subnum = ps_rand() % pm->n_models;
    if (IsNonRenderableSubmodel(pm, subnum))
      return;

    bsp_info *sm = &pm->submodel[subnum];
    if (sm->nverts == 0)
      return;
    int visnum = VisEffectCreate(VIS_FIREBALL, GRAY_LIGHTNING_BOLT_INDEX, obj->roomnum, &obj->pos);
    if (visnum >= 0) {
      vis_effect *vis = &VisEffects[visnum];
      vis->lifeleft = 1.0;
      vis->lifetime = 1.0;
      vis->end_pos = obj->pos;
      vis->velocity.x = .15f;
      vis->velocity.y = 3;
      vis->attach_info.obj_handle = obj->handle;
      vis->attach_info.subnum = subnum;
      vis->attach_info.vertnum = ps_rand() % sm->nverts;
      vis->attach_info.end_vertnum = ps_rand() % sm->nverts;
      vis->attach_info.modelnum = obj->rtype.pobj_info.model_num;
      vis->flags = VF_USES_LIFELEFT | VF_EXPAND | VF_ATTACHED;
      vis->lighting_color = GR_RGB16(40, 250, 40);
    }
  }
}

void DrawPlayerSightVector(object *obj) {
  if (obj->type != OBJ_PLAYER || obj->id != Player_num)
    return;
  if (Player_has_camera == 0 || Player_camera_objnum == -1)
    return;
  // Cast a ray to see where it ends up
  fvi_query fq;
  fvi_info hit_data;
  int fate;
  vector end_pos = obj->pos + (obj->orient.fvec * 500);

  fq.p0 = &obj->pos;
  fq.startroom = obj->roomnum;
  fq.p1 = &end_pos;
  fq.rad = 0;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;
  fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS;
  fate = fvi_FindIntersection(&fq, &hit_data);
  rend_SetAlphaType(AT_VERTEX);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);
  vector vecs[2];
  g3Point pnts[2];

  vecs[0] = obj->pos;
  vecs[1] = hit_data.hit_pnt;
  for (int i = 0; i < 2; i++) {
    g3_RotatePoint(&pnts[i], &vecs[i]);
    pnts[i].p3_flags |= PF_RGBA;
    pnts[i].p3_r = 1;
    pnts[i].p3_g = 0;
    pnts[i].p3_b = 0;
  }
  pnts[0].p3_a = .1f;
  pnts[1].p3_a = .05f;
  g3_DrawSpecialLine(&pnts[0], &pnts[1]);
}
