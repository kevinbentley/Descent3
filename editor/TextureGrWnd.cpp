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

 * $Logfile: /DescentIII/Main/editor/TextureGrWnd.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * Texture view of mine.
 *
 * $Log: not supported by cvs2svn $
 *
 * 122   9/30/99 6:35p Matt
 * Added code to scale the UVs of a texture based on the size of the
 * texture when the texture is applied to a face.  This will cause the
 * applied texture to have the make 3D texel size at the old texture.
 *
 * 121   4/22/99 11:41a Jason
 * fixed right clicking problem (temp fix)
 *
 * 120   4/19/99 6:55p Jason
 * fixed satellite grabbing problem
 *
 * 119   4/18/99 10:55p Chris
 * Added ignore own concussive blasts
 *
 * 118   4/18/99 5:42a Chris
 * Added the FQ_IGNORE_RENDER_THROUGH_PORTALS flag
 *
 * 117   4/15/99 5:49p Chris
 * Fixed a bug with rendering the BOAPath nodes
 *
 * 116   4/14/99 3:13p Chris
 * Beginning to add BoaNode stuff
 *
 * 115   4/03/99 7:39p Matt
 * Don't allow player objects to be given names.
 *
 * 114   3/27/99 7:10p Matt
 * Strip leading & trailing spaces before check for duplicate names.
 *
 * 113   3/02/99 5:54p Jason
 * fixed right mouse clicking with opengl
 *
 * 112   3/01/99 10:39a Matt
 * Strip leading and trailing spaces from object, trigger, and room names
 * on level load and when the names are entered.
 *
 * 111   2/28/99 10:40p Matt
 * Check for name already in use when entering a name.
 *
 * 110   2/21/99 4:20p Matt
 * Added SoundSource objects (and reformatted parts of the object header
 * files).
 *
 * 109   2/19/99 12:04p Jason
 * took out sky band
 *
 * 108   2/17/99 7:06p Kevin
 *
 * 107   2/17/99 5:47p Dan
 * fixed dumb bug
 *
 * 106   2/17/99 1:05p Jason
 * revamped object/face/terrain selection code
 *
 * 105   2/10/99 5:49p Dan
 * fixed fog bug
 *
 * 104   2/09/99 12:25p Jason
 * fixed dumb bug
 *
 * 103   2/09/99 12:16p Jason
 * fixed postrender problem
 *
 * 102   2/09/99 11:36a Dan
 * error checking (m_last_start_rooom invalid, initialized it) Samir
 *
 * 101   2/09/99 9:59a Chris
 * Quick compile patch and changed code to use BOA_IsVisible()
 *
 * 100   2/08/99 6:39p Jason
 * first pass at new indoor engine
 *
 * 99    2/03/99 1:10p Matt
 * Changed the paletted room current faces to be stored in a seperate
 * array, instead of in the room structure.
 *
 * 98    2/01/99 5:47p Nate
 * Implemented Editing/Adding of Dallas Scripts
 *
 * 97    2/01/99 4:24p Matt
 * Added Edit Script and New Script (though they don't do anything yet) to
 * object right-click dialog, and deleted Copy UID and Properties.
 *
 * 96    1/27/99 1:20p Jason
 * made r key rotate the terrain texture
 *
 * 95    1/24/99 12:37a Jeff
 * removed compile warnings
 *
 * 94    1/22/99 8:54p Jeff
 * added custom-default script overrides
 *
 * 93    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 92    1/20/99 10:50a Jason
 * added new terrain
 *
 * 91    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 90    12/22/98 2:05p Matt
 * Mark the world as changed when an object name is changed.
 *
 * 89    12/21/98 11:30p Matt
 * Added names for objects
 *
 * 88    10/22/98 10:33a Sean
 * fixed windowed opengl lighting
 *
 * 87    10/18/98 2:06p Matt
 * Bail out of FindRoomFace if the starting room isn't in use any more.
 * This can happen if you click on the texture window after loading a
 * level or doing a New but before the new level has a chance to render.
 *
 * 86    10/06/98 12:27p Sean
 * More state changes
 *
 * 85    10/06/98 11:29a Jason
 * fixed state limited WindowGL
 *
 * 84    10/02/98 5:31p Jason
 * tweaks for statelimited stuff
 *
 * 83    10/02/98 4:24p Jason
 * more attempts to fix Riva128 opengl stuttering
 *
 * 82    10/02/98 4:22p Jason
 * made multipass turn off for gl rendering
 *
 * 81    10/01/98 10:39a Luke
 * FROM JASON: Attempted to fix GL problem....
 *
 * 80    9/30/98 10:25a Jason
 * another attempt to the get the OpenGL window thing working reliably...
 *
 * 79    9/18/98 1:27p Jason
 * cleaned up renderer initting
 *
 * 78    8/15/98 5:04p Matt
 * Added code to copy a texture & UVs from one face to another
 *
 * 77    7/21/98 12:04p Jason
 * V key now tells if the marked room and current room can see each other
 *
 * 76    6/16/98 3:04p Jason
 * fixed framecount bug
 *
 * 75    6/10/98 12:23p Jason
 * added new skies
 *
 * 74    6/09/98 6:16p Jason
 * added some features for windowed opengl
 *
 * 73    6/09/98 4:47p Jason
 * added windowed openGL mode
 *
 * 72    6/04/98 6:16p Jason
 * added terrain occlusion system
 *
 * 71    5/26/98 7:01p Samir
 * new script selection technique that knows what list of scripts to
 * choose from for an object.
 *
 * 70    5/04/98 3:23p Samir
 * only select custom scripts for right clicking.
 *
 * 69    5/01/98 3:51p Jason
 * sped up terrain rendering by precaching all megacell lod bitmaps
 *
 * 68    5/30/98 10:16p Chris
 * Fixed some bad spelling
 *
 * 67    4/21/98 2:43p Matt
 * Added system to disable render updates while deleting large numbers of
 * rooms, since the mine is not stable until this operation is done.
 *
 * 66    4/21/98 12:16a Samir
 * Hopefully if you change script definition, it's reflected as you edit
 * it.
 *
 * 65    4/16/98 10:42a Matt
 * Made texture propagation work across rooms.
 *
 * 64    3/12/98 7:30p Chris
 * Added ObjSetOrient
 *
 * 63    3/02/98 4:03p Samir
 * Simplied script editing and selection code.
 *
 * 62    2/25/98 4:06p Samir
 * Isolated parameter passing data functions.
 *
 * 61    2/24/98 1:50p Jason
 * added V key to check distance from plane for vertices
 *
 * 60    2/10/98 12:25p Samir
 * m_StartFlip should be rest when flip begins.
 *
 * 59    2/10/98 10:48a Matt
 * Moved editor code from gamepath.cpp to epath.cpp
 *
 * 58    2/09/98 6:06p Matt
 * Made Render_all_external_rooms not affect Room View
 *
 * 57    1/30/98 6:05p Matt
 * Use new function to set current editor object
 *
 * 56    1/26/98 6:31p Chris
 * User define paths now render in mine and terrain views
 *
 * 55    1/26/98 4:33p Samir
 * Added ability to copy object ids.
 *
 * 54    1/23/98 3:06p Samir
 * Script selection with parameters.
 *
 * 53    1/20/98 4:12p Samir
 * New script housekeeping system.
 *
 * 52    1/19/98 6:20p Samir
 * Rightclicking brings up menu in terrain.
 *
 * 51    1/16/98 12:41p Matt
 * Took out old debug/test code
 *
 * 50    1/15/98 12:42p Jason
 * big fix for terrain sky rendering
 *
 * 49    1/07/98 4:19p Jason
 * added dome to terrain sky
 *
 * 48    1/06/98 1:27p Matt
 * Cleaned up interfaces to rendering routines, deleted unused code, etc.
 *
 * 47    1/02/98 6:40p Matt
 * User renderer library (instead of viewport) functions to draw lines and
 * to set and read pixels.  Also made FindRoomFace() work without
 * Render_viewport.
 *
 * 46    12/29/97 5:44p Samir
 * Took out references to grViewport and old 2d library.
 *
 * 45    12/19/97 12:29p Samir
 * Oops.
 *
 * 44    12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 43    12/17/97 5:26p Jason
 * added support for selectable wraparound sky
 *
 * 42    12/01/97 4:20p Jason
 * shadow and lighting changes
 *
 * 41    11/21/97 5:33p Jason
 * print light value when clicking on terrain cell
 *
 * 40    11/17/97 8:33p Jason
 * fixed bug with object selection introduced by last rev
 *
 * 39    11/17/97 6:13p Mark
 * allowed object 0 to be selected
 *
 * 38    11/03/97 7:02p Matt
 * Added better warning message
 *
 * 37    10/31/97 12:14p Jason
 * do a texture screen update after placing a new satellite image
 *
 * 36    9/30/97 2:12p Samir
 * Fully implemeted the Object Script Properties dialog.
 *
 * 35    9/22/97 6:18p Matt
 * Removed include of stub.h
 *
 * 34    9/17/97 1:00p Samir
 * Took out Room_engine and all segment references I could find.
 *
 * 33    9/16/97 6:32p Jason
 * made texture selection on terrain print relevant info
 *
 * 32    9/06/97 3:21p Matt
 * Reset cur portal when room changes
 *
 * 31    9/03/97 8:00p Samir
 * Implemented most of the fixes for the object moving system.
 *
 * 30    9/02/97 2:17p Samir
 * Move objects in Terrain now.
 *
 * 29    8/29/97 1:51p Samir
 * When mouse down in an object, invoke ObjectMoveManager
 *
 * 28    8/28/97 11:53a Matt
 * Don't try to propagate from a face to itself
 *
 * 27    8/27/97 5:19p Jason
 * made ShowRadProgress fill the entire texture window
 *
 * 26    8/26/97 4:37p Jason
 * added floating point hemicube rasterizer, plus "heat" visualization
 *
 * 25    8/22/97 10:16a Matt
 * When change curroom & curface, reset curvert & curedge also
 *
 * 24    8/22/97 10:15a Jason
 * Added error checking to ShowRadView
 *
 * 23    8/18/97 5:57p Jason
 * made radiosity better
 *
 * 22    8/01/97 4:53p Jason
 * made a more general PropagateTextureToFace function call
 *
 * 21    7/29/97 12:07p Matt
 * Took out texturing in room view, & made selecting a face in room view
 * not change the global current room/face
 *
 * 20    7/24/97 6:11p Matt
 * Created symbolic constant for default zoom, and used it every place
 * that specifies zoom
 *
 * 19    7/22/97 7:08p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 18    7/20/97 7:37p Jason
 * added new sky
 *
 * 17    7/18/97 5:49p Jason
 * flag room changed is you change it
 *
 * 16    7/17/97 3:00p Jason
 * changed "moons" to be called satellites since we're going to have suns
 * and other things in orbit
 *
 *
 * 15    7/16/97 5:20p Jason
 * implemented selection of moons with mouse click
 *
 * 14    7/16/97 4:07p Jason
 * fixed all the remaining drop-out bugs
 *
 * 13    7/15/97 4:19p Jason
 * added object focus for terrain
 *
 * 39    6/30/97 3:54p Jeff
 * Add object properties dialog
 *
 * 38    6/30/97 2:31p Jason
 * took out room rendering from the mine-segment rendering loop
 *
 * 37    6/30/97 1:30p Jason
 * added netherspace stuff
 *
 * 36    6/30/97 12:33p Jeff
 * Added message map and support for right-click popup menu
 *
 * 35    6/30/97 11:34a Jeff
 *
 * 34    6/27/97 5:19p Jeff
 *
 * 33    6/27/97 2:49p Jason
 * added hacked way to change textures for rooms (temporary)
 *
 * 32    6/26/97 4:55p Jason
 * fixed dumb bug
 *
 * 31    6/26/97 4:45p Jason
 * added control_right_click function for box selection
 *
 * 30    6/26/97 4:06p Jason
 * no collision detection if Flat_terrain is set
 *
 * 29    6/25/97 5:30p Jason
 * added code to readin/display a room
 *
 * 28    6/06/97 4:57p Jason
 * more nifty megacell/tmap2 features
 *
 * 27    6/06/97 4:33p Jason
 * added cool stuff for megacells
 *
 * 26    6/05/97 6:58p Jason
 * added more megacell functionality
 *
 * 25    5/22/97 5:15p Jason
 * added tmap2 capability to the terrain
 *
 * 24    5/15/97 3:28a Jason
 * tried to get subwindow clearing to work with terrain - but it won't
 * until samir fixes lock_clear
 *
 * 23    5/08/97 7:46p Matt
 * Added called_from_terrain parm for RenderMine()
 *
 * 22    5/08/97 6:43p Jason
 * added support for terrain/mine reentry handling
 *
 * 21    5/05/97 4:47p Jason
 * made terrain and mine rendering work without explicit calls to
 * g3_Startframe in their main function calls
 * This allows us to integrate mine/terrain engines nicely
 *
 * 20    4/09/97 2:00p Jason
 * moved DrawAllPaths function to gamepath where it belongs
 *
 * 19    4/08/97 10:42a Jason
 * implemented path following interface
 *
 * 18    4/02/97 3:24p Jason
 * changed Viewer_moved back to TV_changed because it didn't do what I
 * thought it would do, namely only update the textured view!
 *
 * 17    4/02/97 2:48p Jason
 * changed TV_changed to viewer move to reforce drawing of textured view,
 * but not wireframe
 *
 * 16    3/31/97 5:58p Matt
 * Revamped mine update flags
 *
 * 15    3/20/97 11:55a Jason
 * changes for terrain editing/drawing
 *
 * 14    3/07/97 4:18p Jason
 * implemented terrain functionality in the editor
 *
 * 13    2/28/97 9:35a Matt
 * Added code to select objects by clicking on them in the texture window.
 *
 * 12    2/27/97 4:26p Matt
 * Fixed curseg selection status messages
 *
 * 11    2/26/97 7:35p Samir
 * Moved TextureGrWnd.h after stdafx.h to get rid of warning and errors.
 *
 * 10    2/20/97 5:37p Samir
 * SHIFT + LEFTBUTTONDOWN = Apply texture.
 *
 * 9     2/19/97 11:06a Samir
 * Only flip screen if we rendered but did not hit the left button down
 * key to prevent green screen flash.
 *
 * 8     2/18/97 7:57p Matt
 * Added code to select a segment by clicking on it in the texture-mapped
 * window
 *
 * 7     2/03/97 8:01p Matt
 * New name and parms for render function
 *
 * 6     2/03/97 5:20p Samir
 * Added gr.h header
 *
 * 5     1/30/97 6:25p Samir
 * Implemented a non-working caption bar system and made some changes for
 * Jason.
 *
 * 4     1/23/97 4:56p Samir
 * Handles saving screen positions of windows and tileability.
 *
 * 3     1/21/97 12:42p Samir
 * Floatable-resizable views
 *
 * $NoKeywords: $
 */

#include "stdafx.h"

#include "TextureGrWnd.h"

#include "winapp.h"
#include "editor.h"
#include "render.h"
#include "manage.h"
#include "gr.h"
#include "boa.h"
#include "gameloop.h"
#include "descent.h"
#include "terrain.h"
#include "HTexture.h"
#include "terraindialog.h"
#include "room.h"
#include "roomuvs.h"
#include "mainfrm.h"
#include <string.h>
#include "ObjMoveManager.h"
#include "lightmap_info.h"
#include "lightmap.h"
#include "EditLineDialog.h"
#include "CustDefaultScriptSelect.h"
#include "erooms.h"
#include "ebnode.h"

#include <assert.h>

#include "mono.h"
#include "3d.h"
#include "gr.h"
#include "ddio.h"
#include "epath.h"
#include "megacell.h"
#include "ObjectPropertiesDialog.h"
#include "ObjectClipboard.h"
#include "radiosity.h"
#include "hemicube.h"
#include "args.h"
#include "game.h"
#include "DallasMainDlg.h"
#include "postrender.h"
#include "SoundSourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// These defines are for the right-click popup menu
#define POPUP_PROPERTIES 0x60
#define POPUP_DELETE 0x61
#define POPUP_PASTE 0x62
#define POPUP_CUT 0x63
#define POPUP_COPY 0x64
#define POPUP_COPYID 0x66
#define POPUP_OBJNAME 0x69
#define POPUP_EDITNAME 0x6a
#define POPUP_CUSTOMDEFAULTSCRIPT 0x6b
#define POPUP_EDITSCRIPT 0x6c
#define POPUP_NEWSCRIPT 0x6d
#define POPUP_SOUND 0x6e

grViewport *rad_Viewport;
static int DoOpenGL = 0;

/////////////////////////////////////////////////////////////////////////////
// CTextureGrWnd

CTextureGrWnd::CTextureGrWnd() : CGrWnd("TextureScreen") {
  m_StartFlip = FALSE;
  m_last_start_room = -1;
}

CTextureGrWnd::~CTextureGrWnd() {}

BEGIN_MESSAGE_MAP(CTextureGrWnd, CWnd)
//{{AFX_MSG_MAP(CTextureGrWnd)
ON_WM_SIZE()
ON_WM_PAINT()
ON_WM_DESTROY()
ON_WM_MOVE()
ON_WM_CREATE()
ON_WM_SYSCOMMAND()
ON_WM_NCACTIVATE()
ON_WM_NCPAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_RBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DrawPlayerOnWireframe();

bool Disable_editor_rendering = 0;
static int first_time = 1;

extern int Just_returned_from_game;
extern float Just_returned_time;
int Successive_count = 0;

HWND save_wnd;

void CTextureGrWnd::TexGrStartOpenGL() {
  if (DoOpenGL) {
    app = (oeWin32Application *)Descent;
    StateLimited = 1;
    save_wnd = Win32App()->windowHandle();;
    app->m_hWnd = (HWnd)m_hWnd;
    // rend_SetOpenGLWindowState (1,Descent,NULL); // LGT: not defined anymore
    rend_ClearScreen(0);
    StateLimited = 1;
    UseMultitexture = 0;
    NoLightmaps = false;
  }
}

void CTextureGrWnd::TexGrStopOpenGL() {
  if (DoOpenGL) {
    // rend_SetOpenGLWindowState (0,Descent,NULL); // LGT: not defined anymore
    app->m_hWnd = (HWnd)save_wnd;
  }
}

void CTextureGrWnd::Render() {
  if (first_time) {
    first_time = 0;
    if (FindArg("-WindowGL"))
      DoOpenGL = 1;
  }

  if (DoOpenGL) {
    if (Just_returned_from_game) {
      Successive_count++;
      if (Successive_count < 2) {
        mprintf(0, "Not doing opengl!\n");
        DoOpenGL = 0;
        first_time = 1;
      } else {
        Just_returned_from_game = 0;
        Successive_count = 0;
      }
    }
  }

  if (Disable_editor_rendering)
    return;

  FrameCount++;

  if (m_grScreen == NULL)
    return;
  if (m_grViewport == NULL)
    return;

  rad_Viewport = m_grViewport;

  TexGrStartOpenGL();

  ResetPostrenderList();
  // Reset fog
  Num_fogged_rooms_this_frame = 0;
  if (Editor_view_mode == VM_ROOM) {
    if ((D3EditState.current_room == -1) || (Rooms[D3EditState.current_room].used < 1)) {
      TexGrStopOpenGL();
      return;
    }

    // Disable render-all-rooms in room view
    bool save_RAER = Render_all_external_rooms;
    Render_all_external_rooms = 0;

    // Render
    TGWRenderMine(&Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM, D3EditState.current_room);

    // Restore render-all-rooms state
    Render_all_external_rooms = save_RAER;
  } else if (Editor_view_mode == VM_TERRAIN) {

    if (GetFunctionMode() == EDITOR_MODE) {
      DrawPlayerOnWireframe();
      if (!Flat_terrain && (Viewer_object->pos.y < GetTerrainGroundPoint(&Viewer_object->pos) + 5))
        Viewer_object->pos.y = GetTerrainGroundPoint(&Viewer_object->pos) + 5;
    }

    StartEditorFrame(m_grViewport, &Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM);
    RenderTerrain(0);
    //	we need to save these for object movement.
    g3_GetViewPosition(&m_ViewPos);
    g3_GetViewMatrix(&m_ViewMatrix);
    EndEditorFrame();

    if (KEY_STATE(KEY_X)) {
      vector pos;
      float yval;

      ComputeTerrainSegmentCenter(&pos, (128 * TERRAIN_WIDTH) + 128);
      yval = GetTerrainGroundPoint(&pos);

      pos.y = yval;
      Viewer_object->pos = pos;
      ObjSetOrient(Viewer_object, &Identity_matrix);
      World_changed = 1;
    }
  } else // Mine view
  {
    TGWRenderMine(&Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM, Viewer_object->roomnum);
  }

  PostRender(Viewer_object->roomnum);

  // Draws all User Defined Paths
  DrawAllPaths(m_grViewport, &Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM);
  EBNode_Draw(EBN_draw_type, m_grViewport, &Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM);

  TexGrStopOpenGL();

  m_StartFlip = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTextureGrWnd message handlers

BOOL CTextureGrWnd::Create(RECT &rect, BOOL movable, CWnd *pParent) {
  RECT new_rect;
  DWORD dwstyle;

  dwstyle = (movable ? GRWND_STYLE : GRWND_STATIC_STYLE);

  ::CopyRect(&new_rect, &rect);
  ::AdjustWindowRect(&new_rect, dwstyle, FALSE);

  //	We want this window to start at rect.left, rect.top.
  if (new_rect.left < rect.left) {
    int offx;
    offx = rect.left - new_rect.left;
    new_rect.left += offx;
    new_rect.right += offx;
  }
  if (new_rect.top < rect.top) {
    int offy;
    offy = rect.top - new_rect.top;
    new_rect.top += offy;
    new_rect.bottom += offy;
  }

  ::CopyRect(&rect, &new_rect);

  m_grCreated = TRUE;
  m_Movable = movable;

  lstrcpy(m_Name, "Texture");

  ObjectInBuffer = false;

  return CWnd::Create(NULL, m_Name, dwstyle, rect, pParent, IDC_TEXTURE_WND);
}

void CTextureGrWnd::OnSize(UINT nType, int cx, int cy) {
  RECT rect;
  char text[32];

  CGrWnd::OnSize(nType, cx, cy);

  if (m_Movable) { // don't define these if this box is static
    D3EditState.texscr_w = cx;
    D3EditState.texscr_h = cy;
  }

  GetClientRect(&rect);
  sprintf(text, "Texture (%dx%d)", rect.right - rect.left, rect.bottom - rect.top);
  lstrcpy(m_Name, text);
  SetWindowText(m_Name);
}

void CTextureGrWnd::OnPaint() {
  CPaintDC dc(this); // device context for painting

  //	Draw what's on the screen back page to the desktop
  if (Editor()->paused())
    return;

  if (m_StartFlip) { // do if a flip was signaled
    m_StartFlip = FALSE;

    if (DoOpenGL) {
      HWND save_wnd;
      oeWin32Application *app;

      app = (oeWin32Application *)Descent;

      save_wnd = (HWND)app->m_hWnd;
      app->m_hWnd = (HWnd)m_hWnd;
      // rend_SetOpenGLWindowState (1,Descent,NULL);  // LGT: not defined anymore

      rend_Flip();

      // rend_SetOpenGLWindowState (0,Descent,NULL);  // LGT: not defined anymore
      app->m_hWnd = (HWnd)save_wnd;
    } else {
      m_grScreen->flip();
      m_grViewport->clear();
    }
  }

  // Do not call CWnd::OnPaint() for painting messages
  if (!m_Movable) { // print out window title, since there is no caption
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(192, 192, 192));
    dc.TextOut(10, 10, m_Name, lstrlen(m_Name));
    //		m_grViewport->puts(10,10, m_Name);
  }
}

void CTextureGrWnd::OnDestroy() {
  //	mprintf(0, "CTextureGrWnd::OnDestroy:: m_grScreen\n");
  CGrWnd::OnDestroy();
  Editor()->textured_view = NULL;
}

void CTextureGrWnd::OnMove(int x, int y) {
  CGrWnd::OnMove(x, y);

  //	Must do this to adjust window rect to view's client.
  if (m_Movable) {
    RECT rect;
    GetWindowRect(&rect);
    GetParent()->ScreenToClient(&rect);
    D3EditState.texscr_x = rect.left;
    D3EditState.texscr_y = rect.top;
  }
}

int CTextureGrWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CGrWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO: Add your specialized creation code here
  Editor()->textured_view = this;

  return 0;
}

void CTextureGrWnd::OnSysCommand(UINT nID, LPARAM lParam) {
  // TODO: Add your message handler code here and/or call default
  //	take care of 'close' box for one thing

  switch (nID) {
  case SC_CLOSE:
    D3EditState.texscr_visible = 0;
    break;
  }

  CWnd::OnSysCommand(nID, lParam);
}

BOOL CTextureGrWnd::OnNcActivate(BOOL bActive) {
  // TODO: Add your message handler code here and/or call default

  return CGrWnd::OnNcActivate(bActive);
}

void CTextureGrWnd::OnNcPaint() { CGrWnd::OnNcPaint(); }

int Tracing_drops = 0;
int Drop_seg = 0;

int CTextureGrWnd::TGWFindRoomFace(int x, int y, int *roomnum, int *facenum) {
  /*if (m_last_start_room == -1)
          return 0;
  if (! Rooms[m_last_start_room].used)
          return 0;

  int ret;

  StartEditorFrame(m_grViewport,&m_last_viewer_eye,&m_last_viewer_orient,m_last_zoom);

  ret = FindRoomFace(x,y,m_last_start_room,roomnum,facenum);
  PostRender(Viewer_object->roomnum);

  EndEditorFrame();*/

  return 0;
}

int CTextureGrWnd::TGWFindLightmapFace(int x, int y, int *roomnum, int *facenum, int *lumel_num) {
  /*if (! Rooms[m_last_start_room].used)
          return 0;

  int ret;

  StartEditorFrame(m_grViewport,&m_last_viewer_eye,&m_last_viewer_orient,m_last_zoom);

  ret = FindLightmapFace(x,y,m_last_start_room,roomnum,facenum,lumel_num);

  EndEditorFrame();*/

  return 0;
}

void CTextureGrWnd::TGWRenderMine(vector *pos, matrix *orient, float zoom, int start_roomnum) {
  if (start_roomnum < 0 || start_roomnum > MAX_ROOMS + MAX_PALETTE_ROOMS)
    return;

  // save these vars for possible use by FindRoomFace()
  m_last_viewer_eye = *pos;
  m_last_viewer_orient = *orient;
  m_last_zoom = zoom;
  m_last_start_room = start_roomnum;

  StartEditorFrame(m_grViewport, pos, orient, zoom);
  FrameCount++;

  RenderMine(start_roomnum, 0, 0);
  PostRender(Viewer_object->roomnum);

  //	we need to save these for object movement.
  g3_GetViewPosition(&m_ViewPos);
  g3_GetViewMatrix(&m_ViewMatrix);

  EndEditorFrame();
}

// Set the current object
void SelectObject(int objnum);

void CTextureGrWnd::OnLButtonDown(UINT nFlags, CPoint point) {
  TexGrStartOpenGL();

  ResetPostrenderList();

  if (Editor_view_mode == VM_ROOM) {
    TSearch_found_type = -1;
    TSearch_seg = -1;
    TSearch_on = 1;
    TSearch_x = point.x;
    TSearch_y = point.y;

    TGWRenderMine(&Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM, Viewer_object->roomnum);

    TSearch_on = 0;

    if (TSearch_found_type == TSEARCH_FOUND_MINE) {
      Current_faces[TSearch_seg - FIRST_PALETTE_ROOM] = TSearch_face;
      EditorStatus("Face %d selected.", TSearch_face);
      State_changed = 1;
      return;
    }
  } else if (Editor_view_mode == VM_TERRAIN) {
    TSearch_found_type = -1;
    TSearch_seg = -1;
    TSearch_on = 1;
    TSearch_x = point.x;
    TSearch_y = point.y;

    StartEditorFrame(m_grViewport, &Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM);
    RenderTerrain(0);
    PostRender(Viewer_object->roomnum);
    EndEditorFrame();
    TSearch_on = 0;
    if (TSearch_found_type != -1) {

      // Check for objects
      if (TSearch_found_type == TSEARCH_FOUND_OBJECT) {
        // Found an object
        mprintf(0, "Found an object! objnum=%d\n", TSearch_seg);
        SelectObject(TSearch_seg);
        // start object moving if mouse down in an object.
        ObjMoveManager.Start(this, m_grViewport->width(), m_grViewport->height(), &m_ViewPos, &m_ViewMatrix, point.x,
                             point.y);
      }

      if (TSearch_found_type == TSEARCH_FOUND_SKY_DOME) {
        if (nFlags & MK_SHIFT) {
          Terrain_sky.dome_texture = D3EditState.texdlg_texture;

          World_changed = 1;
          TV_changed = 1;
        }
      }

      // Check for satellite
      if (TSearch_found_type == TSEARCH_FOUND_SATELLITE) {
        if (nFlags & MK_SHIFT) {
          Terrain_sky.satellite_texture[TSearch_seg] = D3EditState.texdlg_texture;
          Editor()->main_frame->m_TerrainDialog->SetCurrentMoon(TSearch_seg);
          World_changed = 1;
          TV_changed = 1;
        }

        else {
          Editor()->main_frame->m_TerrainDialog->SetCurrentMoon(TSearch_seg);
          if (KEY_STATE(KEY_G))
            D3EditState.texdlg_texture = Terrain_sky.satellite_texture[TSearch_seg];
        }
      }

      if (TSearch_found_type == TSEARCH_FOUND_TERRAIN) {
        if (KEY_STATE(KEY_P)) {
          Tracing_drops = 1;
          Drop_seg = TSearch_seg;
          Terrain_tex_seg[Terrain_seg[Drop_seg].texseg_index].tex_index = 0;
        } else if (KEY_STATE(KEY_R)) {
          // Rotate this texture
          int val = Terrain_tex_seg[Terrain_seg[TSearch_seg].texseg_index].rotation & 0x0F;
          val++;
          val %= 4;
          Terrain_tex_seg[Terrain_seg[TSearch_seg].texseg_index].rotation &= ~0x0F;
          Terrain_tex_seg[Terrain_seg[TSearch_seg].texseg_index].rotation |= val;

          TV_changed = 1;
        }

        if (nFlags & MK_SHIFT) {

          Terrain_tex_seg[Terrain_seg[TSearch_seg].texseg_index].tex_index = D3EditState.texdlg_texture;
          TV_changed = 1;
        } else if (nFlags & MK_CONTROL) {
          if (TerrainSelected[TSearch_seg]) {
            TerrainSelected[TSearch_seg] = 0;
            Num_terrain_selected--;
          } else {
            TerrainSelected[TSearch_seg] = 1;
            Num_terrain_selected++;
          }
          TV_changed = 1;
        } else {
          memset(TerrainSelected, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);
          EditorStatus("Cell %d selected. Light=%d Height=%.2f (%d).  Texture=%s", TSearch_seg,
                       Terrain_seg[TSearch_seg].l, Terrain_seg[TSearch_seg].y, Terrain_seg[TSearch_seg].ypos,
                       GameTextures[Terrain_tex_seg[Terrain_seg[TSearch_seg].texseg_index].tex_index].name);
          TerrainSelected[TSearch_seg]++;
          Num_terrain_selected = 1;
          TV_changed = 1;
        }
      }
    }
  } else {
    int roomnum, facenum;

    //	mprintf(0,"ButtonDown %d,%d\n",point.x,point.y);
    TSearch_found_type = -1;
    TSearch_seg = -1;
    TSearch_on = 1;
    TSearch_x = point.x;
    TSearch_y = point.y;

    TGWRenderMine(&Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM, Viewer_object->roomnum);
    TSearch_on = 0;

    // this looks at the last frame rendered
    if (TSearch_found_type == TSEARCH_FOUND_OBJECT) {
      // Found a face or object
      m_StartFlip = FALSE; // unsignal flip.
      SelectObject(TSearch_seg);
      // start object moving if mouse down in an object.
      ObjMoveManager.Start(this, m_grViewport->width(), m_grViewport->height(), &m_ViewPos, &m_ViewMatrix, point.x,
                           point.y);
    } else if (TSearch_found_type == TSEARCH_FOUND_MINE) {
      roomnum = TSearch_seg;
      facenum = TSearch_face;

      if (nFlags & MK_SHIFT) { // apply current texture to face
        HTextureApplyToRoomFace(&Rooms[TSearch_seg], TSearch_face, D3EditState.texdlg_texture);
        EditorStatus("Texture %d applied to room %d face %d\n", D3EditState.texdlg_texture, TSearch_seg, TSearch_face);
        World_changed = 1;
      } else if (KEY_STATE(KEY_J)) // apply texture, scaling UVs based on texture size
      {
        int old_width = bm_w(GetTextureBitmap(Rooms[TSearch_seg].faces[TSearch_face].tmap, 0), 0);
        int new_width = bm_w(GetTextureBitmap(D3EditState.texdlg_texture, 0), 0);
        HTextureApplyToRoomFace(&Rooms[TSearch_seg], TSearch_face, D3EditState.texdlg_texture);
        ScaleFaceUVs(&Rooms[TSearch_seg], TSearch_face, (float)old_width / new_width);
        EditorStatus("Texture %d applied to room %d face %d\n", D3EditState.texdlg_texture, TSearch_seg, TSearch_face);
        World_changed = 1;
      } else if (KEY_STATE(KEY_P)) {
        // P + Click = Propagate from current face
        if ((TSearch_seg == ROOMNUM(Curroomp)) && (TSearch_face == Curface))
          EditorStatus("Cannot propagate from a face to itself.");
        else if (HTexturePropagateToFace(&Rooms[roomnum], facenum, Curroomp, Curface)) {
          EditorStatus("Texture propagated from %d:%d to %d:%d\n", ROOMNUM(Curroomp), Curface, roomnum, facenum);
          World_changed = 1;
        } else {
          OutrageMessageBox("Room:face %d:%d is not adjacent to Current room:face (%d:%d)", roomnum, facenum,
                            ROOMNUM(Curroomp), Curface);
          return;
        }
      } else if (KEY_STATE(KEY_E)) {
        // C + Click = Copy uv values from marked face
        static int last_copy_marked_room = -1, last_copy_marked_face = -1;
        static int last_copy_room = -1, last_copy_face = -1;
        static int count;

        if (Markedroomp == NULL) {
          OutrageMessageBox("You must have a marked face for this operation.");
          return;
        }

        if ((roomnum == ROOMNUM(Markedroomp)) && (facenum == Markedface))
          EditorStatus("Cannot copy from a face to itself.");
        else {
          if ((last_copy_marked_room == ROOMNUM(Markedroomp)) && (last_copy_marked_face == Markedface) &&
              (last_copy_room == roomnum) && (last_copy_face == facenum))
            count++;
          else {
            count = 0;
            last_copy_marked_room = ROOMNUM(Markedroomp);
            last_copy_marked_face = Markedface;
            last_copy_room = roomnum;
            last_copy_face = facenum;
          }

          if (HTextureCopyUVsToFace(&Rooms[roomnum], facenum, Markedroomp, Markedface, count)) {
            Rooms[roomnum].faces[facenum].tmap = Markedroomp->faces[Markedface].tmap;
            EditorStatus("Texture & UVs copied from %d:%d to %d:%d (rotation = %d/%d)\n", ROOMNUM(Markedroomp),
                         Markedface, roomnum, facenum, count % Markedroomp->faces[Markedface].num_verts,
                         Markedroomp->faces[Markedface].num_verts);
            World_changed = 1;
          } else
            EditorStatus("Can't copy UVs: faces don't have the same number of vertices.");
        }
      } else if (KEY_STATE(KEY_N)) {
        vector vec = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[0]];
        vector norm = Rooms[roomnum].faces[facenum].normal;
        float plane_dist = -(vec.x * norm.x + vec.y * norm.y + vec.z * norm.z);
        int i;
        for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
          vec = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];
          float dist = vec.x * norm.x + vec.y * norm.y + vec.z * norm.z + plane_dist;
          mprintf(0, "Vertex %d distance from plane=%f\n", i, dist);
        }
      } else if (KEY_STATE(KEY_V)) {
        // Do visibility check
        int rooma = (Markedroomp - Rooms);
        int roomb = (Curroomp - Rooms);
        int answer = BOA_IsVisible(rooma, roomb);

        mprintf(0, "Answer 1 is %d\n", answer);

        answer = BOA_IsVisible(roomb, rooma);

        mprintf(0, "Answer 2 is %d\n", answer);
      } else { // Just change curface
        State_changed = 1;
        EditorStatus("Current room:face set to %d:%d", roomnum, facenum);
      }

      // All clicks on face change the current face
      Curroomp = &Rooms[roomnum];
      Curface = facenum;
      Curedge = Curvert = 0;
      Curportal = -1;
    }
  }

  TexGrStopOpenGL();

  CWnd::OnLButtonDown(nFlags, point);
}

void CTextureGrWnd::OnMouseMove(UINT nFlags, CPoint point) { CWnd::OnMouseMove(nFlags, point); }

void CTextureGrWnd::OnRButtonDown(UINT nFlags, CPoint point) {
  int n = D3EditState.current_megacell;
  int newobjnum = -1;
  bool do_popup = false;

  TexGrStartOpenGL();

  if (Editor_view_mode == VM_TERRAIN) {
    TSearch_seg = -1;
    TSearch_on = 1;
    TSearch_x = point.x;
    TSearch_y = point.y;
    TSearch_found_type = -1;

    StartEditorFrame(m_grViewport, &Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM);
    RenderTerrain(0);
    PostRender(Viewer_object->roomnum);
    EndEditorFrame();
    TSearch_on = 0;
    if (TSearch_found_type == TSEARCH_FOUND_TERRAIN) {
      if (nFlags & MK_SHIFT) {
        int w = Megacells[n].width;
        int h = Megacells[n].height;

        for (int i = 0; i < h; i++) {
          for (int t = 0; t < w; t++) {
            int terrain_x = (TSearch_seg % TERRAIN_WIDTH) + t;
            int terrain_z = (TSearch_seg / TERRAIN_WIDTH) - i;
            int mx, my;

            if (terrain_x < 0 || terrain_x >= TERRAIN_WIDTH)
              continue;
            if (terrain_z < 0 || terrain_z >= TERRAIN_DEPTH)
              continue;

            if (D3EditState.randomize_megacell) {
              mx = rand() % w;
              my = rand() % h;
            } else {
              mx = t;
              my = i;
            }

            TV_changed = 1;
          }
        }
      }
      if (nFlags & MK_CONTROL) {
        int x, z, i, t;

        for (i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
          if (TerrainSelected[i]) {
            x = i % TERRAIN_WIDTH;
            z = i / TERRAIN_WIDTH;

            break;
          }
        }

        if (i == TERRAIN_DEPTH * TERRAIN_WIDTH)
          return; // nothing to do!

        Num_terrain_selected = 0;
        memset(TerrainSelected, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);

        int terrain_x = (TSearch_seg % TERRAIN_WIDTH);
        int terrain_z = (TSearch_seg / TERRAIN_WIDTH);

        int width = abs(terrain_x - x);
        int height = abs(terrain_z - z);
        int start_x = x;
        int start_z = z;

        if (terrain_x < x)
          start_x = terrain_x;
        if (terrain_z < z)
          start_z = terrain_z;

        for (i = 0; i <= height; i++)
          for (t = 0; t <= width; t++) {
            Num_terrain_selected++;
            TerrainSelected[((i + start_z) * TERRAIN_WIDTH) + start_x + t] = 1;
          }
      }
    }
    // Check for objects
    else if (TSearch_found_type == TSEARCH_FOUND_OBJECT) {
      newobjnum = TSearch_seg;
      do_popup = true;

      mprintf(0, "Found an object! objnum=%d\n", newobjnum);
      SelectObject(newobjnum);

      Render();
      RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    }
  }
  // Code to put up popup menu when right clicking
  else {
    int roomnum, facenum;

    TSearch_found_type = -1;
    TSearch_seg = -1;
    TSearch_on = 1;
    TSearch_x = point.x;
    TSearch_y = point.y;

    TGWRenderMine(&Viewer_object->pos, &Viewer_object->orient, D3_DEFAULT_ZOOM, Viewer_object->roomnum);
    TSearch_on = 0;

    // this looks at the last frame rendered
    if (TSearch_found_type == TSEARCH_FOUND_MINE || TSearch_found_type == TSEARCH_FOUND_OBJECT) {
      roomnum = TSearch_seg;
      facenum = TSearch_face;
      m_StartFlip = FALSE; // unsignal flip.
      mprintf(0, "found point: %d %d %d\n", roomnum, facenum);

      do_popup = true;

      if (TSearch_found_type == TSEARCH_FOUND_OBJECT) { // found an object
        newobjnum = (roomnum);
        SelectObject(newobjnum);
      }
    }

    Render();
    RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
  }

  //	right click popup menu
  if (do_popup) {
    CMenu popup;
    bool ret = true;
    char *title = NULL;

    if (newobjnum > -1)
      title = Objects[newobjnum].name;

    if (popup.CreatePopupMenu())
      ret = SetupPopup(&popup, title);
    else {
      mprintf(0, "Warning: Could not create popup menu!\n");
      ret = false;
    }

    if (newobjnum > -1) {
      object *foundobj = &Objects[newobjnum];
      if (!ObjectInBuffer)
        popup.EnableMenuItem(POPUP_PASTE, MF_GRAYED);
      if (foundobj->control_type != CT_SOUNDSOURCE)
        popup.EnableMenuItem(POPUP_SOUND, MF_GRAYED);
    } else {
      popup.EnableMenuItem(POPUP_OBJNAME, MF_GRAYED);
      popup.EnableMenuItem(POPUP_EDITNAME, MF_GRAYED);
      popup.EnableMenuItem(POPUP_EDITSCRIPT, MF_GRAYED);
      popup.EnableMenuItem(POPUP_NEWSCRIPT, MF_GRAYED);
      popup.EnableMenuItem(POPUP_CUT, MF_GRAYED);
      popup.EnableMenuItem(POPUP_COPY, MF_GRAYED);
      popup.EnableMenuItem(POPUP_SOUND, MF_GRAYED);
      if (!ObjectInBuffer)
        popup.EnableMenuItem(POPUP_PASTE, MF_GRAYED);
      popup.EnableMenuItem(POPUP_DELETE, MF_GRAYED);
    }

    if (ret)
      if (!popup.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y + 20, this, NULL))
        mprintf(0, "TrackPopupMenu error!\n");
  }

  TexGrStopOpenGL();

  CWnd::OnRButtonDown(nFlags, point);
}

//=================
//	Sets up the popup menu for a right click
// Parameters:	popup: pointer to CMenu object
// Returns:	true if everything went ok
// Notes: The CMenu object must be initialized before sent to this function (use CreatePopupMenu())
//=================
bool CTextureGrWnd::SetupPopup(CMenu *popup, char *title) {
  bool ret;
  ret = true;

  if (!popup->AppendMenu(MF_STRING + MF_DISABLED, POPUP_OBJNAME, title ? title : "(no name)")) {
    ret = false;
    mprintf(0, "Warning: Could not add Title to popup\n");
  }
  if (!popup->AppendMenu(MF_SEPARATOR)) {
    ret = false;
    mprintf(0, "Warning: Could not add seperator to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_COPY, "Copy")) {
    ret = false;
    mprintf(0, "Warning: Could not add Copy to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_CUT, "Cut")) {
    ret = false;
    mprintf(0, "Warning: Could not add Cut to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_PASTE, "Paste")) {
    ret = false;
    mprintf(0, "Warning: Could not add Paste to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_DELETE, "Delete")) {
    ret = false;
    mprintf(0, "Warning: Could not add Delete to popup\n");
  }
  if (!popup->AppendMenu(MF_SEPARATOR)) {
    ret = false;
    mprintf(0, "Warning: Could not add seperator to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_EDITNAME, "Edit Name")) {
    ret = false;
    mprintf(0, "Warning: Could not add Edit Name to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_SOUND, "Sound")) {
    ret = false;
    mprintf(0, "Warning: Could not add Sound to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_EDITSCRIPT, "Edit Dallas Scripts")) {
    ret = false;
    mprintf(0, "Warning: Could not add Edit Script to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_NEWSCRIPT, "New Dallas Script")) {
    ret = false;
    mprintf(0, "Warning: Could not add New Script to popup\n");
  }
  if (!popup->AppendMenu(MF_STRING, POPUP_CUSTOMDEFAULTSCRIPT, "Set a custom default script")) {
    ret = false;
    mprintf(0, "Warning: Could not add Set a custom default script to popup\n");
  }
  //@@if(!popup->AppendMenu(MF_STRING,POPUP_PROPERTIES,"Properties"))
  //@@{
  //@@	ret=false;
  //@@	mprintf(0,"Warning: Could not add Properties to popup\n");
  //@@}
  //@@if(!popup->AppendMenu(MF_STRING,POPUP_COPYID,"Copy UID"))
  //@@{
  //@@	ret=false;
  //@@	mprintf(0,"Warning: Could not add Copy UID to popup\n");
  //@@}
  return ret;
}

void UpdateProperties(CObjectPropertiesDialog *prop_dlg) {

  object *curobj;
  curobj = &Objects[Cur_object_index];

  curobj->mtype.phys_info.velocity.x = prop_dlg->m_fVelocityX;
  curobj->mtype.phys_info.velocity.y = prop_dlg->m_fVelocityY;
  curobj->mtype.phys_info.velocity.z = prop_dlg->m_fVelocityZ;

  curobj->mtype.phys_info.thrust.x = prop_dlg->m_fThrustX;
  curobj->mtype.phys_info.thrust.y = prop_dlg->m_fThrustY;
  curobj->mtype.phys_info.thrust.z = prop_dlg->m_fThrustZ;

  curobj->mtype.phys_info.rotvel.x = prop_dlg->m_fRotVelX;
  curobj->mtype.phys_info.rotvel.y = prop_dlg->m_fRotVelY;
  curobj->mtype.phys_info.rotvel.z = prop_dlg->m_fRotVelZ;

  curobj->mtype.phys_info.rotthrust.x = prop_dlg->m_fRotThrustX;
  curobj->mtype.phys_info.rotthrust.y = prop_dlg->m_fRotThrustY;
  curobj->mtype.phys_info.rotthrust.z = prop_dlg->m_fRotThrustZ;

  curobj->mtype.phys_info.turnroll = prop_dlg->m_sTurnrollAngle;
  curobj->mtype.phys_info.num_bounces = prop_dlg->m_iNumBounces;
  curobj->mtype.phys_info.mass = prop_dlg->m_fMass;
  curobj->mtype.phys_info.drag = prop_dlg->m_fDrag;
  curobj->mtype.phys_info.rotdrag = prop_dlg->m_fRotDrag;
  curobj->mtype.phys_info.full_thrust = prop_dlg->m_fFullThrust;
  curobj->mtype.phys_info.full_rotthrust = prop_dlg->m_fFullRotThrust;
  curobj->mtype.phys_info.max_turnroll_rate = prop_dlg->m_fMaxTurnrollrate;
  curobj->mtype.phys_info.turnroll_ratio = prop_dlg->m_fTurnrollRatio;
  curobj->mtype.phys_info.wiggle_amplitude = prop_dlg->m_fWiggleAmplitude;
  curobj->mtype.phys_info.wiggles_per_sec = prop_dlg->m_fWigglesPerSecond;

  curobj->mtype.phys_info.flags = 0;

  if (prop_dlg->m_bTurnroll)
    curobj->mtype.phys_info.flags |= PF_TURNROLL;
  if (prop_dlg->m_bLevelling)
    curobj->mtype.phys_info.flags |= PF_LEVELING;
  if (prop_dlg->m_bBounce)
    curobj->mtype.phys_info.flags |= PF_BOUNCE;
  if (prop_dlg->m_bWiggle)
    curobj->mtype.phys_info.flags |= PF_WIGGLE;
  if (prop_dlg->m_bSticks)
    curobj->mtype.phys_info.flags |= PF_STICK;
  if (prop_dlg->m_bPersistent)
    curobj->mtype.phys_info.flags |= PF_PERSISTENT;
  if (prop_dlg->m_bUsesThrust)
    curobj->mtype.phys_info.flags |= PF_USES_THRUST;
  if (prop_dlg->m_bGravity)
    curobj->mtype.phys_info.flags |= PF_GRAVITY;
  if (prop_dlg->m_bMagnetism)
    curobj->mtype.phys_info.flags |= PF_IGNORE_OWN_CONC_FORCES;
  if (prop_dlg->m_bWind)
    curobj->mtype.phys_info.flags |= PF_WIND;

  if ((prop_dlg->m_bUnlimitedBounce) || (!prop_dlg->m_bBounce)) {
    curobj->mtype.phys_info.num_bounces = -1;
  }
}

#include "osiris_predefs.h"
extern bool StripLeadingTrailingSpaces(char *s);

BOOL CTextureGrWnd::OnCommand(WPARAM wParam, LPARAM lParam) {
  // TODO: Add your specialized code here and/or call the base class
  if (HIWORD(wParam) == 0) {
    switch (LOWORD(wParam)) {
    case POPUP_EDITSCRIPT: {
      mprintf(0, "Edit script for object %d\n", Cur_object_index);
      // Nate: Add code here to edit/view an object's scripts

      // Make sure Dallas is open
      if (Editor()->m_DallasModelessDlgPtr == NULL) {
        Editor()->m_DallasModelessDlgPtr = new CDallasMainDlg;
        Editor()->m_DallasModelessDlgPtr->Create(IDD_DALLAS_MAIN_DIALOG, this);
        Editor()->m_DallasModelessDlgPtr->ShowWindow(SW_SHOW);
      } else
        Editor()->m_DallasModelessDlgPtr->ShowWindow(SW_RESTORE);

      object *curobj = &Objects[Cur_object_index];
      if (curobj->name == NULL)
        break;

      // Tell Dallas to add a new script with this object as the owner
      Editor()->m_DallasModelessDlgPtr->m_ScriptOwnerType = OBJECT_TYPE;
      Editor()->m_DallasModelessDlgPtr->m_ScriptOwnerHandle = curobj->handle;
      Editor()->m_DallasModelessDlgPtr->PostMessage(WM_HIGHLIGHT_SCRIPTS);
    } break;

    case POPUP_NEWSCRIPT: {
      mprintf(0, "Add new script for object %d\n", Cur_object_index);
      // Nate: Add code here to create a new script for an object

      // Make sure Dallas is open
      if (Editor()->m_DallasModelessDlgPtr == NULL) {
        Editor()->m_DallasModelessDlgPtr = new CDallasMainDlg;
        Editor()->m_DallasModelessDlgPtr->Create(IDD_DALLAS_MAIN_DIALOG, this);
        Editor()->m_DallasModelessDlgPtr->ShowWindow(SW_SHOW);
      } else
        Editor()->m_DallasModelessDlgPtr->ShowWindow(SW_RESTORE);

      object *curobj = &Objects[Cur_object_index];
      if (curobj->name == NULL)
        break;

      // Tell Dallas to highlight all scripts that have this object as the owner
      Editor()->m_DallasModelessDlgPtr->m_ScriptOwnerType = OBJECT_TYPE;
      Editor()->m_DallasModelessDlgPtr->m_ScriptOwnerHandle = curobj->handle;
      Editor()->m_DallasModelessDlgPtr->PostMessage(WM_ADD_SCRIPT);
    } break;

    case POPUP_EDITNAME: {
      if (Objects[Cur_object_index].type == OBJ_PLAYER) {
        EditorMessageBox("You cannot name a player object.");
        break;
      }

      char tempname[OBJ_NAME_LEN + 1] = "";
      object *curobj = &Objects[Cur_object_index];
      if (curobj->name) {
        ASSERT(strlen(curobj->name) <= OBJ_NAME_LEN);
        strcpy(tempname, curobj->name);
      }

    try_again:;
      if (!InputString(tempname, OBJ_NAME_LEN, "Object Name", "Enter a new name:"))
        break;

      if (StripLeadingTrailingSpaces(tempname))
        EditorMessageBox("Note: Leading and/or trailing spaces have been removed from this name (\"%s\")", tempname);

      int handle = osipf_FindObjectName(tempname);
      if ((handle != OBJECT_HANDLE_NONE) && (handle != curobj->handle)) {
        EditorMessageBox("Object %d already has this name.", OBJNUM(ObjGet(handle)));
        goto try_again;
      }

      if (curobj->name) {
        mem_free(curobj->name);
        curobj->name = NULL;
      }

      if (strlen(tempname)) {
        curobj->name = (char *)mem_malloc(strlen(tempname) + 1);
        strcpy(curobj->name, tempname);
      }

      World_changed = 1;

      break;
    }

    case POPUP_CUSTOMDEFAULTSCRIPT: {
      object *curobj = &Objects[Cur_object_index];

      CCustDefaultScriptSelect dlg;

      if (curobj->custom_default_script_name)
        dlg.m_Name = curobj->custom_default_script_name;
      else
        dlg.m_Name = "";

      if (curobj->custom_default_module_name)
        dlg.m_Module = curobj->custom_default_module_name;
      else
        dlg.m_Module = "";

      if (dlg.DoModal()) {

        if (curobj->custom_default_module_name) {
          mem_free(curobj->custom_default_module_name);
          curobj->custom_default_module_name = NULL;
        }

        if (curobj->custom_default_script_name) {
          mem_free(curobj->custom_default_script_name);
          curobj->custom_default_script_name = NULL;
        }

        if (!dlg.m_Module.IsEmpty()) {
          char module_name[MAX_MODULENAME_LEN];
          curobj->custom_default_module_name = (char *)mem_malloc(dlg.m_Module.GetLength() + 1);

          ddio_SplitPath(dlg.m_Module.GetBuffer(0), NULL, module_name, NULL);
          strcpy(curobj->custom_default_module_name, module_name);
        }

        if (!dlg.m_Name.IsEmpty()) {
          curobj->custom_default_script_name = (char *)mem_malloc(dlg.m_Name.GetLength() + 1);
          strcpy(curobj->custom_default_script_name, dlg.m_Name.GetBuffer(0));
        }
      }

      World_changed = 1; //?

    } break;

      //@@case POPUP_PROPERTIES:
      //@@	{
      //@@		CObjectPropertiesDialog prop_dlg;
      //@@		object *curobj=&Objects[Cur_object_index];
      //@@		mprintf(0,"Properties selected\n");
      //@@		if(prop_dlg.DoModal()==IDOK) UpdateProperties(&prop_dlg);
      //@@		break;
      //@@	}
      //@@
      //@@case POPUP_COPYID:
      //@@	Copied_object_id = Objects[Cur_object_index].handle;
      //@@	break;

    case POPUP_DELETE:
      if (!ObjectDelete())
        OutrageMessageBox("Could not Delete Object!");
      break;
    case POPUP_PASTE:
      if (!ObjectPaste())
        OutrageMessageBox("Could not Paste Object!");
      break;
    case POPUP_CUT:
      if (!ObjectCut())
        OutrageMessageBox("Could not Cut Object!");
      break;
    case POPUP_COPY:
      if (!ObjectCopy())
        OutrageMessageBox("Could not Copy Object!");
      break;

    case POPUP_SOUND: {
      CSoundSourceDialog dlg(&Objects[Cur_object_index].ctype.soundsource_info);
      dlg.DoModal();
    }
    }
  }
  return CWnd::OnCommand(wParam, lParam);
}

// Shows radiosity progress in the texture window.
// This function needs to go in this file because of the stupid MFC
// problems that occur if you try to access MFC member variables from a non-
// MFC file
void ShowRadView() {
  grSurface *cur_surf;
  int i, t;

  CTextureGrWnd *tview = Editor()->textured_view;

  cur_surf = rad_Viewport->lock();
  uint16_t *dest = (uint16_t *)cur_surf->data();
  int rowsize = cur_surf->rowsize() / 2;

  int height = cur_surf->height();
  int width = cur_surf->width();

  fix du = IntToFix(rad_Hemicube.ff_res) / cur_surf->width();
  fix dv = IntToFix(rad_Hemicube.ff_res) / cur_surf->height();
  fix u, v;

  for (v = 0, i = 0; i < height; i++, v += dv)
    for (u = 0, t = 0; t < width; t++, u += du) {
      int x = FixToInt(u);
      int y = FixToInt(v);

      int color = rad_Hemicube.id_grid[y * rad_Hemicube.ff_res + x];
      if (color == -1)
        dest[i * rowsize + t] = 0;
      else
        dest[i * rowsize + t] = GR_COLOR_TO_16(color);
    }

  rad_Viewport->unlock();
  tview->Invalidate();
  tview->SendMessage(WM_PAINT);

  World_changed = 1;
}
