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

 * $Logfile: /DescentIII/Main/editor/editorView.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:37 $
 * $Author: kevinb $
 *
 * Main Editor View which contains the different views of the mine
 *
 * $Log: not supported by cvs2svn $
 *
 * 72    10/14/99 4:21p Matt
 * Added code to remove duplicate faces from a room.
 *
 * 71    10/07/99 3:12p Matt
 * Added a function to flip the view 180 degrees.
 *
 * 70    9/15/99 1:55p Matt
 * Added the option to allow rooms or groups placed on the terrain to
 * either align with the terrain or with gravity.
 *
 * 69    9/07/99 12:10p Matt
 * Added a function to propagate a texture to all adjacent coplanar faces
 * in a room.
 *
 * 68    8/24/99 4:24p Matt
 * Added a function to rotate a placed room by 45 degrees.
 *
 * 67    5/08/99 6:39p Matt
 * Added a function to delete a face and all faces connected to it.
 *
 * 66    5/08/99 1:38a Matt
 * Fixed typo.
 *
 * 65    4/30/99 6:52p Matt
 * Added a function to merge an object's geometry into a room.
 *
 * 64    4/28/99 12:51a Matt
 * Added some funtions to edit face geometry.
 *
 * 63    4/19/99 12:10a Matt
 * Added a menu item to delete a vertex from a face.
 *
 * 62    4/06/99 10:23a Matt
 *
 * 61    3/31/99 12:58p Matt
 * Added snap-point-to-face
 *
 * 60    3/29/99 6:46p Matt
 * Added menu item to fix/remove degenerate faces
 *
 * 59    3/27/99 7:10p Matt
 * Strip leading & trailing spaces before check for duplicate names.
 *
 * 58    3/23/99 11:15p Matt
 * Added message when rooms combined.
 *
 * 57    3/23/99 5:12p Matt
 * Added function to combine rooms.
 *
 * 56    3/01/99 10:39p Matt
 * Added menu options to set & clear room center points
 *
 * 55    3/01/99 10:39a Matt
 * Strip leading and trailing spaces from object, trigger, and room names
 * on level load and when the names are entered.
 *
 * 54    2/28/99 10:40p Matt
 * Check for name already in use when entering a name.
 *
 * 53    2/28/99 6:31p Matt
 * Disable z-buffer button if OpenGL is being used in the editor.
 *
 * 52    2/03/99 1:10p Matt
 * Changed the paletted room current faces to be stored in a seperate
 * array, instead of in the room structure.
 *
 * 51    1/25/99 11:12a Matt
 * If the marked face is deleted, reset it.
 *
 * 50    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 49    1/15/99 10:50a Matt
 * Added rename room to Room menu & added shortcut key
 *
 * 48    12/30/98 6:49p Matt
 * When un-placing a door, free the room that the placed door was using
 *
 * 47    12/23/98 10:53a Matt
 * Added functions to create a face
 *
 * 46    10/05/98 9:45a Matt
 * Use windows function to get cursor position instead of ddio function.
 *
 * 45    10/03/98 11:21p Matt
 * Added system to seperately control outline mode for mine, terrain, sky,
 * & objects
 *
 * 44    10/03/98 8:31p Matt
 * Added Join Rooms Exact function.
 *
 * 43    9/18/98 1:27p Jason
 * cleaned up renderer initting
 *
 * 42    9/09/98 4:07p Matt
 * Added Smooth Bridge function
 *
 * 41    9/08/98 6:12p Matt
 * Added code to check for and fix duplicate and unused points.
 *
 * 40    9/08/98 12:06p Jason
 * added ReInit openGL button
 *
 * 39    9/07/98 10:58p Matt
 * Added snap point to point.
 *
 * 38    9/04/98 3:34p Matt
 * Added groovy vertex snap code
 *
 * 37    9/04/98 12:29p Matt
 * Added marked edge & vertex in the editor
 *
 * 36    8/31/98 4:36p Matt
 * Added status message
 *
 * 35    6/25/98 7:15p Matt
 * Added a function to delete a pair of portals.
 *
 * 34    6/23/98 2:45p Matt
 * Added option when propagating to all faces in a room to only do so to
 * ones with the same texture.
 *
 * 33    6/08/98 12:28p Matt
 * Added a function to triangulate a face
 *
 * 32    5/22/98 4:47p Matt
 * Added menu item to propagate a texture to all the faces in a room.
 *
 * 31    4/27/98 6:41p Matt
 * Added code to join all adjacent faces between two rooms
 *
 * 30    4/16/98 11:50a Matt
 * Made snap code work for placed groups.
 *
 * 29    2/16/98 1:27p Matt
 * Added function to snap the placed room to a vertex/edge on the base
 * room/face
 *
 * 28    2/11/98 12:39p Matt
 * Implemented Delete Face menu item.
 *
 * 27    1/29/98 2:15p Samir
 * Implemented ObjectListModeless and Toolbar button.
 *
 * 26    1/27/98 6:15p Samir
 * Added Object toolbar button.
 *
 * 25    1/20/98 4:08p Matt
 * Added function to swap current and marked room:face.  Added some
 * addition error checking to bridge function.
 *
 * 24    1/06/98 12:39p Matt
 * Added some error checking
 *
 * 23    11/05/97 7:13p Matt
 * Added join rooms function
 *
 * 22    10/03/97 3:37p Matt
 * Added menu item to place a building on the terrain
 *
 * 21    9/24/97 3:22p Matt
 * Added Drop Room function
 *
 * 20    9/17/97 1:24p Matt
 * Ripped out segment code
 *
 * 19    9/17/97 11:21a Matt
 * Ripped out segment code
 *
 * 18    9/16/97 4:09p Jason
 * implemented software zbuffer
 *
 * 17    9/14/97 11:06p Matt
 * Fixed up Room menu
 *
 * 16    9/11/97 5:46p Jason
 * first pass at getting doors to work with room engine
 *
 * 15    8/29/97 3:37p Samir
 * Took out segment tab constant.
 *
 * 14    8/22/97 9:32a Matt
 * Don't allow place room to a face that already has a room on it.
 *
 * 13    8/21/97 6:00p Matt
 * Added delete current room function
 *
 * 12    8/19/97 5:58p Samir
 * OLE additions
 *
 * 11    8/19/97 10:54a Matt
 * Added remove placed room option
 *
 * 10    8/18/97 6:59p Matt
 * Implemented Place Room/Attach room system
 *
 * 9     8/04/97 12:52p Matt
 * Added hooks for mark & bridge
 *
 * 8     8/01/97 6:10p Matt
 * Added hooks for attach room
 *
 * 7     7/28/97 11:29a Samir
 * Fixed editor->game goofiness.  Isolated GrWnd creation and destruction
 * to a couple of functions.
 *
 * 6     7/25/97 6:16p Samir
 * Fixed the tile-cascade switching/default madness.
 *
 * 5     7/22/97 7:07p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 4     7/22/97 10:33a Matt
 * Added functions for new room menu
 *
 * 29    6/30/97 1:29p Jason
 * added netherspace stuff
 *
 * 28    6/03/97 4:55p Mark
 *
 * 28	6/3/97	4:38p Jeff
 *	Added Context Sensitive Help for Keypads
 *
 * 27    5/27/97 3:30p Matt
 * Added editor button to toggle lighting
 *
 * 26    5/08/97 7:29p Matt
 * Made seperate viewers for mine & terrain, and cleaned up code the
 * switched between modes
 *
 * 25    5/06/97 3:49p Matt
 * Unlink/relink viewer object when switching between mine and terrain
 * views
 *
 * 24    5/06/97 1:17p Jason
 * checked in for matt
 *
 * 23    4/03/97 1:17p Matt
 * Took out support for toolbar movement mode toggle button, now that that
 * function has been moved to the object keypad.
 *
 * 22    4/02/97 8:07p Matt
 * Added variable & button to toggle object move state
 *
 * 21    3/31/97 5:57p Matt
 * Revamped mine update flags
 *
 * 20    3/21/97 5:02p Jason
 * make player_object switch the OF_OVER_TERRAIN flag to on when changing
 * to terrain view...temporary
 *
 * 19    3/17/97 7:41p Samir
 * Fixed editor interface problems with updating triggers and doorways in
 * keypads when loading new levels (must fix some more).
 *
 * 18    3/13/97 6:12p Jason
 * set default height above terrain
 *
 * 17    3/07/97 4:54p Jason
 * made editor save position of terrain/mine when switching between modes
 *
 *
 * 16    3/07/97 4:18p Jason
 * implemented terrain functionality in the editor
 *
 * 15    2/28/97 6:37p Matt
 * Added variable & toggle button for box selection mode
 *
 * 14    2/20/97 1:30p Samir
 * Defined main_view.
 *
 * 13    2/11/97 1:42p Samir
 * Moved file opening and closing to editorDoc where it should be.
 *
 * 12    2/10/97 5:40p Matt
 * Code to handle several File menu options
 *
 * 11    2/07/97 7:41p Matt
 * Hooked in next & prev segment & side funcs
 *
 * 10    1/23/97 4:09p Samir
 * Added stuff for toggling wireframe, texture windows, tiling or
 * cascading
 *
 * 9     1/21/97 12:51p Samir
 * GrWnds created based on D3EditState info
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "editor.h"

#include "editorDoc.h"
#include "editorView.h"
#include "MainFrm.h"
#include "TextureDialog.h"
#include "EditLineDialog.h"
#include "RoomKeypadDialog.h"
#include "game.h"

#include "d3edit.h"
#include "mono.h"

#include "render.h"
#include "HRoom.h"
#include "HFile.h"
#include "erooms.h"
#include "args.h"

#include "terrain.h"
#include "texture.h"

#include "mem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorView

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
//{{AFX_MSG_MAP(CEditorView)
ON_WM_SIZE()
ON_WM_DESTROY()
ON_COMMAND(ID_BUTTON_OUTLINE, OnButtonOutline)
ON_UPDATE_COMMAND_UI(ID_BUTTON_OUTLINE, OnUpdateButtonOutline)
ON_UPDATE_COMMAND_UI(ID_VIEW_TEXTUREMINE, OnUpdateViewTexturemine)
ON_COMMAND(ID_VIEW_TEXTUREMINE, OnViewTexturemine)
ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAMEMINE, OnUpdateViewWireframemine)
ON_COMMAND(ID_VIEW_WIREFRAMEMINE, OnViewWireframemine)
ON_WM_PARENTNOTIFY()
ON_COMMAND(ID_WINDOW_TILE, OnWindowTile)
ON_COMMAND(ID_WINDOW_CASCADE, OnWindowCascade)
ON_COMMAND(ID_BUTTON_WINDOWSELECTION, OnButtonWindowSelection)
ON_UPDATE_COMMAND_UI(ID_BUTTON_WINDOWSELECTION, OnUpdateButtonWindowSelection)
ON_COMMAND(ID_BUTTON_LIGHTING, OnButtonLighting)
ON_UPDATE_COMMAND_UI(ID_BUTTON_LIGHTING, OnUpdateButtonLighting)
ON_WM_HELPINFO()
ON_COMMAND(ID_ROOM_ADD, OnRoomAdd)
ON_COMMAND(ID_ROOM_GRABTEXTURE, OnRoomGrabTexture)
ON_COMMAND(ID_ROOM_NEXTFACE, OnRoomNextFace)
ON_COMMAND(ID_ROOM_PREVIOUSFACE, OnRoomPreviousFace)
ON_COMMAND(ID_ROOM_SELECTBYNUMBER, OnRoomSelectByNumber)
ON_COMMAND(ID_ROOM_ATTACHROOM, OnRoomAttachRoom)
ON_COMMAND(ID_ROOM_BUILDBRIDGE, OnRoomBuildBridge)
ON_COMMAND(ID_ROOM_MARK, OnRoomMark)
ON_COMMAND(ID_ROOM_PLACEROOM, OnRoomPlaceRoom)
ON_UPDATE_COMMAND_UI(ID_ROOM_ATTACHROOM, OnUpdateRoomAttachRoom)
ON_COMMAND(ID_ROOM_UNPLACEROOM, OnRoomUnPlaceRoom)
ON_UPDATE_COMMAND_UI(ID_ROOM_UNPLACEROOM, OnUpdateRoomUnPlaceRoom)
ON_COMMAND(ID_ROOM_DELETE, OnRoomDelete)
ON_COMMAND(ID_ROOM_SELECTFACEBYNUMBER, OnRoomSelectFaceByNumber)
ON_COMMAND(ID_ROOM_SAVECURRENTROOM, OnRoomSaveCurrentRoom)
ON_COMMAND(ID_ZBUTTON, OnZbutton)
ON_UPDATE_COMMAND_UI(ID_ZBUTTON, OnUpdateZbutton)
ON_COMMAND(ID_ROOM_DROPROOM, OnRoomDropRoom)
ON_COMMAND(ID_ROOM_PLACETERRAINROOM, OnRoomPlaceTerrainRoom)
ON_COMMAND(ID_ROOM_JOINROOMS, OnRoomJoinRooms)
ON_COMMAND(ID_ROOM_SWAPMAKEDANDCURRENTROOMFACE, OnRoomSwapMarkedAndCurrentRoomFace)
ON_COMMAND(ID_ROOM_DELETEFACE, OnRoomDeleteFace)
ON_COMMAND(ID_ROOM_SNAPPLACEDROOM, OnRoomSnapPlacedRoom)
ON_UPDATE_COMMAND_UI(ID_ROOM_SNAPPLACEDROOM, OnUpdateRoomSnapPlacedRoom)
ON_COMMAND(ID_ROOM_JOIN_ADJACENT_FACES, OnRoomJoinAdjacentFaces)
ON_COMMAND(ID_ROOM_PROPAGATETOALL, OnRoomPropagateToAll)
ON_COMMAND(ID_ROOM_SPLITFACE, OnRoomSplitFace)
ON_COMMAND(ID_ROOM_DELETEPORTAL, OnRoomDeletePortal)
ON_COMMAND(ID_ROOM_SNAPPOINTTOEDGE, OnRoomSnapPointToEdge)
ON_COMMAND(ID_ROOM_UNDOSNAP, OnRoomUndoSnap)
ON_UPDATE_COMMAND_UI(ID_ROOM_UNDOSNAP, OnUpdateRoomUndoSnap)
ON_COMMAND(ID_ROOM_SNAPPOINTTOPOINT, OnRoomSnapPointToPoint)
ON_COMMAND(ID_REINIT_OPENGL, OnReinitOpengl)
ON_UPDATE_COMMAND_UI(ID_REINIT_OPENGL, OnUpdateReinitOpengl)
ON_COMMAND(ID_FILE_REMOVEEXTRAPOINTS, OnFileRemoveExtraPoints)
ON_COMMAND(ID_ROOM_BUILDSMOOTHBRIDGE, OnRoomBuildSmoothBridge)
ON_COMMAND(ID_ROOM_JOINROOMSEXACT, OnRoomJoinRoomsExact)
ON_COMMAND(ID_ROOM_STARTNEWFACE, OnRoomStartNewFace)
ON_COMMAND(ID_ROOM_FINISHNEWFACE, OnRoomFinishNewFace)
ON_COMMAND(ID_ROOM_ADDVERTTONEWFACE, OnRoomAddVertToNewFace)
ON_COMMAND(ID_ROOM_RENAMEROOM, OnRoomRenameRoom)
ON_COMMAND(ID_ROOM_SETCENTERFROMVIEWER, OnRoomSetCenterFromViewer)
ON_COMMAND(ID_ROOM_CLEARCENTERPOINT, OnRoomClearCenterPoint)
ON_UPDATE_COMMAND_UI(ID_ROOM_CLEARCENTERPOINT, OnUpdateRoomClearCenterPoint)
ON_UPDATE_COMMAND_UI(ID_ROOM_SETCENTERFROMVIEWER, OnUpdateRoomSetCenterFromViewer)
ON_COMMAND(ID_ROOM_COMBINE, OnRoomCombine)
ON_COMMAND(ID_FILE_FIXDEGENERATEFACES, OnFileFixDegenerateFaces)
ON_COMMAND(ID_ROOM_SNAPPOINTTOFACE, OnRoomSnapPointToFace)
ON_COMMAND(ID_ROOM_LINKTONEWEXTERNAL, OnRoomLinkToNewExternal)
ON_COMMAND(ID_ROOM_DELETEVERT, OnRoomDeleteVert)
ON_COMMAND(ID_ROOM_FACE_ADDVERTTOEDGE, OnRoomFaceAddVertToEdge)
ON_COMMAND(ID_ROOM_FACE_MOVEVERTONEDGE, OnRoomFaceMoveVertOnEdge)
ON_COMMAND(ID_ROOM_FACE_SPLITFACE, OnRoomFaceSplitFace)
ON_COMMAND(ID_ROOM_FACE_DELETEVERTONEDGE, OnRoomFaceDeleteVertOnEdge)
ON_COMMAND(ID_ROOM_MERGEOBJECTINTOROOM, OnRoomMergeObjectIntoRoom)
ON_COMMAND(ID_ROOM_DELETECONNECTEDFACES, OnRoomDeleteConnectedFaces)
ON_COMMAND(ID_ROOM_ROTATEPLACEDROOM45DEGREES, OnRoomRotatePlacedRoom45Degrees)
ON_COMMAND(ID_ROOM_PROPAGATETOADJACENTCOPLANARFACES, OnRoomPropagateToAdjacentCoplanarFaces)
ON_COMMAND(ID_VIEW_FLIP, OnViewFlip)
ON_COMMAND(ID_FILE_REMOVEDUPLICATEFACESFROMCURRENTROOM, OnFileRemoveDuplicateFacesFromCurrentRoom)
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

END_MESSAGE_MAP()

//	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
//	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)

/////////////////////////////////////////////////////////////////////////////
// CEditorView construction/destruction

CEditorView::CEditorView() {
  // TODO: add construction code here
  m_grwndCreated = FALSE;
  m_grwndActive = FALSE;
}

CEditorView::~CEditorView() {}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT &cs) {
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  m_grwndActive = TRUE; // This should be moved to OnCreate or something like it

  return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEditorView printing

BOOL CEditorView::OnPreparePrinting(CPrintInfo *pInfo) {
  // default preparation
  return DoPreparePrinting(pInfo);
}

void CEditorView::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
  // TODO: add extra initialization before printing
}

void CEditorView::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
  // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CEditorView::OnCancelEditSrvr() { GetDocument()->OnDeactivateUI(FALSE); }

/////////////////////////////////////////////////////////////////////////////
// CEditorView drawing

void CEditorView::OnDraw(CDC *pDC) {
  CEditorDoc *pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  // TODO: add draw code for native data here
  if (!Editor()->paused()) {
    if (Editor()->wireframe_view)
      m_grwndWireframe.Render();
    if (Editor()->textured_view)
      m_grwndTexture.Render();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CEditorView diagnostics

#ifdef _DEBUG
void CEditorView::AssertValid() const { CView::AssertValid(); }

void CEditorView::Dump(CDumpContext &dc) const { CView::Dump(dc); }

CEditorDoc *CEditorView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
  return (CEditorDoc *)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditorView message handlers

void CEditorView::OnInitialUpdate() {
  CView::OnInitialUpdate();

  // TODO: Add your specialized code here and/or call the base class
  Editor()->main_view = this;

  CWnd *wnd = GetParent();

  wnd->Invalidate(FALSE);

  mprintf(0, "CEditorView::OnInitialUpdate.\n");
}

void CEditorView::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);

  // TODO: Add your message handler code here
  //	ReCreate wireframe and texture screen/windows
  if (!m_grwndActive)
    return;

  KillChildViews();

  if (cx && cy) {
    CreateChildViews();
  }
}

void CEditorView::OnDestroy() {
  Editor()->main_view = NULL;
  CView::OnDestroy();
}

void CEditorView::DeactivateView() {
  KillChildViews();
  m_grwndActive = FALSE; // Tell system that this view should not function
}

void CEditorView::ActivateView() {
  CreateChildViews();
  m_grwndActive = TRUE; // This view is active and functional
}

/*	Since this code is shared by a couple of functions, and is critical that the code
        is the same for both functions, I place all the code here.
*/
void CEditorView::KillChildViews() {
  if (m_grwndCreated) {
    if (Editor()->wireframe_view)
      m_grwndWireframe.DestroyWindow();
    if (Editor()->textured_view)
      m_grwndTexture.DestroyWindow();
    m_grwndCreated = FALSE;
  }
}

void CEditorView::CreateChildViews() {
  RECT view_rect, wire_rect, texture_rect;

  if (m_grwndCreated)
    return;

  GetClientRect(&view_rect);
  SetRect(&texture_rect, 0, 0, 0, 0);

  //	if we tile windows, then texture window will be reset to default width, height
  //	wireframe window will be sized depending on the existance of the texture view.
  if (D3EditState.texscr_visible) {
    if (D3EditState.tile_views)
      SetRect(&texture_rect, view_rect.left, view_rect.top, view_rect.left + CALC_PIXELS_WITH_ASPECTX(TEXSCREEN_WIDTH),
              view_rect.top + CALC_PIXELS_WITH_ASPECTY(TEXSCREEN_HEIGHT));
    else
      SetRect(&texture_rect, D3EditState.texscr_x, D3EditState.texscr_y, D3EditState.texscr_x + D3EditState.texscr_w,
              D3EditState.texscr_y + D3EditState.texscr_h);
    m_grwndTexture.Create(texture_rect, !D3EditState.tile_views, this);
  }

  if (D3EditState.wirescr_visible) {
    if (D3EditState.tile_views)
      SetRect(&wire_rect, view_rect.left, view_rect.top + texture_rect.bottom + 2, view_rect.right, view_rect.bottom);
    else
      SetRect(&wire_rect, D3EditState.wirescr_x, D3EditState.wirescr_y, D3EditState.wirescr_x + D3EditState.wirescr_w,
              D3EditState.wirescr_y + D3EditState.wirescr_h);
    m_grwndWireframe.Create(wire_rect, !D3EditState.tile_views, this);
  }

  m_grwndCreated = TRUE;
}

#include "ddio.h"

void CEditorView::OnButtonOutline() {
  CMenu popup;

  if (popup.CreatePopupMenu())
    if (!SetupPopup(&popup))
      Int3();

  POINT pnt;
  GetCursorPos(&pnt);

  if (!popup.TrackPopupMenu(TPM_LEFTALIGN, pnt.x - 20, pnt.y - 10, this, NULL))
    mprintf(0, "TrackPopupMenu error!\n");

  //	Outline_mode ^= OM_ON;
  //	EditorStatus("Outline mode turned %s",OUTLINE_ON(0)?"ON":"OFF");
  //	State_changed = 1;
}

void CEditorView::OnUpdateButtonOutline(CCmdUI *pCmdUI) { pCmdUI->SetCheck(OUTLINE_ON(0)); }

void CEditorView::OnUpdateViewTexturemine(CCmdUI *pCmdUI) { pCmdUI->SetCheck(D3EditState.texscr_visible); }

void CEditorView::OnViewTexturemine() {
  RECT texture_rect;

  D3EditState.texscr_visible = !D3EditState.texscr_visible;

  if (!D3EditState.texscr_visible) {
    if (D3EditState.tile_views) {
      DeactivateView();
      ActivateView();
    } else if (Editor()->textured_view)
      m_grwndTexture.DestroyWindow();
  } else {
    if (D3EditState.tile_views) { // for tiling, reinit the views.
      DeactivateView();
      ActivateView();
    } else {
      SetRect(&texture_rect, D3EditState.texscr_x, D3EditState.texscr_y, D3EditState.texscr_x + D3EditState.texscr_w,
              D3EditState.texscr_y + D3EditState.texscr_h);
      m_grwndTexture.Create(texture_rect, TRUE, this);
    }
  }
}

void CEditorView::OnUpdateViewWireframemine(CCmdUI *pCmdUI) { pCmdUI->SetCheck(D3EditState.wirescr_visible); }

void CEditorView::OnViewWireframemine() {
  RECT wire_rect;

  D3EditState.wirescr_visible = !D3EditState.wirescr_visible;

  if (!D3EditState.wirescr_visible) {
    if (D3EditState.tile_views) {
      DeactivateView();
      ActivateView();
    } else if (Editor()->wireframe_view)
      m_grwndWireframe.DestroyWindow();
  } else {
    if (D3EditState.tile_views) { // for tiling, reinit the views
      DeactivateView();
      ActivateView();
    } else {
      SetRect(&wire_rect, D3EditState.wirescr_x, D3EditState.wirescr_y, D3EditState.wirescr_x + D3EditState.wirescr_w,
              D3EditState.wirescr_y + D3EditState.wirescr_h);
      m_grwndWireframe.Create(wire_rect, TRUE, this);
    }
  }
}

//	 We do this so that we can tell if the texture or wireframe views were closed by the user
//
void CEditorView::OnParentNotify(UINT message, LPARAM lParam) {
  CView::OnParentNotify(message, lParam);

  //	Is the texture or wireframe window closing?
  switch (message) {
  case WM_CREATE:
    if (HIWORD(lParam) == IDC_TEXTURE_WND) {
      GetParent()->GetMenu()->CheckMenuItem(ID_VIEW_TEXTUREMINE, MF_BYCOMMAND | MF_CHECKED);
    } else if (HIWORD(lParam) == IDC_WIREFRAME_WND) {
      GetParent()->GetMenu()->CheckMenuItem(ID_VIEW_WIREFRAMEMINE, MF_BYCOMMAND | MF_CHECKED);
    }
    break;

  case WM_DESTROY:
    if (HIWORD(lParam) == IDC_TEXTURE_WND) {
      GetParent()->GetMenu()->CheckMenuItem(ID_VIEW_TEXTUREMINE, MF_BYCOMMAND | MF_UNCHECKED);
    } else if (HIWORD(lParam) == IDC_WIREFRAME_WND) {
      GetParent()->GetMenu()->CheckMenuItem(ID_VIEW_WIREFRAMEMINE, MF_BYCOMMAND | MF_UNCHECKED);
    }
    break;
  }
}

// ----------------------------------------------------------------------------
//	window menu options

void CEditorView::OnWindowTile() {
  // TODO: Add your command handler code here
  D3EditState.tile_views = 1;
  ((CMainFrame *)GetParentFrame())->DockKeypad(TRUE);
  DeactivateView();
  ActivateView();
}

void CEditorView::OnWindowCascade() {
  // TODO: Add your command handler code here
  D3EditState.tile_views = 0;
  ((CMainFrame *)GetParentFrame())->DockKeypad(FALSE);
  DeactivateView();
  ActivateView();
}

void CEditorView::OnButtonWindowSelection() {
  D3EditState.box_selection_mode = -(D3EditState.box_selection_mode - IN_WINDOW - ACROSS_EDGE);
  EditorStatus("Box selection set to %s", (D3EditState.box_selection_mode == IN_WINDOW) ? "IN WINDOW" : "ACROSS EDGE");
}

void CEditorView::OnUpdateButtonWindowSelection(CCmdUI *pCmdUI) {
  pCmdUI->SetCheck(D3EditState.box_selection_mode == ACROSS_EDGE);
}

void CEditorView::OnButtonLighting() {
  Lighting_on = !Lighting_on;
  EditorStatus("Lighting turned %s", Lighting_on ? "ON" : "OFF");
  State_changed = 1;
}

void CEditorView::OnUpdateButtonLighting(CCmdUI *pCmdUI) { pCmdUI->SetCheck(Lighting_on); }

BOOL CEditorView::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  switch (D3EditState.keypad_current) {
  case TAB_TEXTURE_KEYPAD:
    WinHelp(HID_TEXTURETAB, HELP_CONTEXT);
    break;

  case TAB_OBJECTS_KEYPAD:
    WinHelp(HID_OBJECTTAB, HELP_CONTEXT);
    break;

  case TAB_LIGHTING_KEYPAD:
    WinHelp(HID_LIGHTINGTAB, HELP_CONTEXT);
    break;

  case TAB_PATHS_KEYPAD:
    WinHelp(HID_PATHSTAB, HELP_CONTEXT);
    break;

  case TAB_TRIGGER_KEYPAD:
    WinHelp(HID_TRIGGERTAB, HELP_CONTEXT);
    break;

  case TAB_DOORWAY_KEYPAD:
    WinHelp(HID_DOORWAYTAB, HELP_CONTEXT);
    break;

  case TAB_TERRAIN_KEYPAD:
    WinHelp(HID_TERRAINTAB, HELP_CONTEXT);
    break;

  case TAB_MEGACELL_KEYPAD:
    WinHelp(HID_MEGACELLTAB, HELP_CONTEXT);
    break;

  case TAB_ROOM_KEYPAD:
    WinHelp(HID_ROOMTAB, HELP_CONTEXT);
    break;

  default:
    WinHelp(HID_DEFAULT, HELP_CONTEXT);
    // return CView::OnHelpInfo(pHelpInfo);
  }
  return TRUE;
}

void CEditorView::OnRoomAdd() { AddRoom(); }

void CEditorView::OnRoomDelete() {
  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete Room %d?", ROOMNUM(Curroomp)) != IDYES)
    return;

  DeleteRoomFromMine(Curroomp);

  World_changed = 1;
}

void CEditorView::OnRoomGrabTexture() { Editor()->main_frame->m_TextureDialog->OnTexpadGrab(); }

void CEditorView::OnRoomNextFace() {
  SelectNextFace();

  EditorStatus("Face %d selected.", Curface);
}

void CEditorView::OnRoomPreviousFace() {
  SelectPrevFace();

  EditorStatus("Face %d selected.", Curface);
}

void CEditorView::OnRoomSelectByNumber() {
  int n;

  if (InputNumber(&n, "Select Room", "Enter room number to select", this)) {

    if ((n > Highest_room_index) || !Rooms[n].used) {
      OutrageMessageBox("Invalid room number.");
      return;
    }

    Curroomp = &Rooms[n];
    Curface = Curedge = Curvert = 0;
    Curportal = -1;

    EditorStatus("Room %d selected.", n);

    State_changed = 1;
  }
}

void CEditorView::OnRoomPlaceRoom() {
  if (D3EditState.current_room == -1) {
    OutrageMessageBox("You must have a current room for this operation");
    return;
  }

  if (Curroomp->faces[Curface].portal_num != -1) {
    OutrageMessageBox("There's already a connection at the current room:face.");
    return;
  }

  PlaceRoom(Curroomp, Curface, D3EditState.current_room, Current_faces[D3EditState.current_room - FIRST_PALETTE_ROOM],
            -1);
}

void CEditorView::OnRoomAttachRoom() {
  ASSERT(Placed_room != -1);

  AttachRoom();
}

void CEditorView::OnRoomBuildBridge() {
  if ((Markedroomp == NULL) || (Markedface == -1)) {
    OutrageMessageBox("You must have a marked face to use this function.");
    return;
  }

  if ((Markedroomp == Curroomp) && (Markedface == Curface)) {
    OutrageMessageBox("The marked room:face must be different from the current room:face.");
    return;
  }

  BuildBridge(Curroomp, Curface, Markedroomp, Markedface);
}

void CEditorView::OnRoomJoinRooms() {
  if ((Markedroomp == NULL) || (Markedface == -1)) {
    OutrageMessageBox("You must have a marked face to use this function.");
    return;
  }

  JoinRooms(Curroomp, Curface, Markedroomp, Markedface);
}

void CEditorView::OnRoomMark() { SetMarkedRoom(); }

void CEditorView::OnUpdateRoomAttachRoom(CCmdUI *pCmdUI) { pCmdUI->Enable(Placed_room != -1); }

void CEditorView::OnRoomUnPlaceRoom() {
  if (Placed_door != -1) {
    FreeRoom(&Rooms[Placed_room]);
    Placed_door = -1;
  }

  Placed_room = -1;
  Placed_group = NULL;

  State_changed = 1;
}

void CEditorView::OnUpdateRoomUnPlaceRoom(CCmdUI *pCmdUI) {
  if (Placed_room != -1) {
    pCmdUI->SetText((Placed_door != -1) ? "Un-place Door" : "Un-place Room");
    pCmdUI->Enable(1);
  } else if (Placed_group != NULL) {
    pCmdUI->SetText("Un-place Group");
    pCmdUI->Enable(1);
  } else
    pCmdUI->Enable(0);
}

void CEditorView::OnRoomSelectFaceByNumber() {
  int n;

  if (InputNumber(&n, "Select Face", "Enter face number to select", this)) {

    if (n >= Curroomp->num_faces) {
      OutrageMessageBox("Invalid face number.");
      return;
    }

    Curface = n;
    Curedge = Curvert = 0;

    EditorStatus("Face %d selected.", Curface);

    State_changed = 1;
  }
}

void CEditorView::OnRoomSaveCurrentRoom() { Editor()->main_frame->m_RoomDialog->OnSaveRoomLocally(); }

void CEditorView::OnZbutton() {
  // TODO: Add your command handler code here
  Use_software_zbuffer = !Use_software_zbuffer;
  // tex_SetZBufferState (Use_software_zbuffer); // LGT: not defined
  State_changed = 1;
}

void CEditorView::OnUpdateZbutton(CCmdUI *pCmdUI) {
  static bool first_time = 1, opengl;
  if (first_time) {
    first_time = 0;
    opengl = (FindArg("-WindowGL") != 0);
  }

  pCmdUI->Enable(!opengl);
  pCmdUI->SetCheck(opengl || Use_software_zbuffer);
}

void CEditorView::OnRoomDropRoom() {
  if (D3EditState.current_room == -1) {
    OutrageMessageBox("You must have a current room for this operation");
    return;
  }

  DropRoom(Curroomp, Curface, D3EditState.current_room);
}

void CEditorView::OnRoomPlaceTerrainRoom() {
  int cellnum;

  if (D3EditState.current_room == -1) {
    OutrageMessageBox("You must have a current room for this operation");
    return;
  }

  if (Current_faces[D3EditState.current_room - FIRST_PALETTE_ROOM] == -1) {
    OutrageMessageBox("You must have a face selected on the current room for this operation");
    return;
  }

  if (Num_terrain_selected != 1) {
    OutrageMessageBox("You must have one and only one cell selected this operation");
    return;
  } else {
    for (cellnum = 0; cellnum < TERRAIN_WIDTH * TERRAIN_DEPTH; cellnum++)
      if (TerrainSelected[cellnum])
        break;

    ASSERT(cellnum != TERRAIN_WIDTH * TERRAIN_DEPTH);
  }

  int result = OutrageMessageBox(MBOX_YESNOCANCEL, "Do you want to align to the terrain? NO will align with gravity.");

  if (result == IDCANCEL)
    return;

  PlaceExternalRoom(cellnum, D3EditState.current_room, Current_faces[D3EditState.current_room - FIRST_PALETTE_ROOM],
                    (result == IDYES));
}

void CEditorView::OnRoomSwapMarkedAndCurrentRoomFace() {
  if (Markedroomp == NULL)
    return;

  room *troomp = Markedroomp;
  int tface = Markedface, tedge = Markededge, tvert = Markedvert;

  Markedroomp = Curroomp;
  Markedface = Curface;
  Markededge = Curedge;
  Markedvert = Curvert;

  Curroomp = troomp;
  Curface = tface;
  Curedge = tedge;
  Curvert = tvert;

  State_changed = 1;

  EditorStatus("Current room:face set to %d:%d; marked room:face set to %d:%d", ROOMNUM(Curroomp), Curface,
               ROOMNUM(Markedroomp), Markedface);
}

void CEditorView::OnRoomDeleteFace() {
  if (Curroomp->faces[Curface].portal_num != -1) {
    OutrageMessageBox("You cannot delete a face that is part of a portal.");
    return;
  }

  if (Curroomp->num_faces == 1) {
    OutrageMessageBox("You cannot delete the only face in a room.");
    return;
  }

  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete Face %d from Room %d?", Curface,
                        ROOMNUM(Curroomp)) != IDYES)
    return;

  DeleteRoomFace(Curroomp, Curface);

  EditorStatus("Face %d deleted from room %d.", ROOMNUM(Curroomp), Curface);

  if (Curface == Curroomp->num_faces)
    Curface--;

  if (Markedface == Curroomp->num_faces)
    Markedface--;

  World_changed = 1;
}

void CEditorView::OnRoomSnapPlacedRoom() {
  ASSERT((Placed_room != -1) || (Placed_group != NULL));

  if ((Curroomp != Placed_baseroomp) || (Curface != Placed_baseface)) {
    OutrageMessageBox("The current room & face must be the same as the base room & face for this operation.");
    return;
  }

  SnapRoom(Curvert);
}

void CEditorView::OnUpdateRoomSnapPlacedRoom(CCmdUI *pCmdUI) {
  pCmdUI->Enable(((Placed_room != -1) || (Placed_group != NULL)) && (Placed_baseroomp != NULL));

  if (Placed_room != -1) {
    pCmdUI->SetText((Placed_door != -1) ? "Snap Placed Door" : "Snap Placed Room");
    pCmdUI->Enable(1);
  } else if (Placed_group != NULL) {
    pCmdUI->SetText("Snap Placed Group");
    pCmdUI->Enable(1);
  } else
    pCmdUI->Enable(0);
}

void CEditorView::OnRoomJoinAdjacentFaces() {
  if (Markedroomp == NULL) {
    OutrageMessageBox("You must have a Marked Room for this operation.");
    return;
  }

  if (Markedroomp == Curroomp) {
    OutrageMessageBox("The Marked room cannot be the same as the Current room for this operation.");
    return;
  }

  JoinAllAdjacentFaces(Curroomp, Markedroomp);
}

void CEditorView::OnRoomPropagateToAll() {
  int answer;

  answer = OutrageMessageBox(
      MBOX_YESNOCANCEL,
      "Propagate only to faces with the same texture?\n(Answering No will propagate to all faces in the room.)");

  if (answer == IDCANCEL)
    return;

  PropagateToAllFaces(Curroomp, Curface, (answer == IDYES));
}

void CEditorView::OnRoomSplitFace() {
  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to triangulate the current face?") == IDYES)
    TriangulateFace(Curroomp, Curface, Curvert);
}

void CEditorView::OnRoomDeletePortal() {
  if (Curportal == -1) {
    OutrageMessageBox("You must have a current portal for this operation.");
    return;
  }

  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete portal %d from room %d (& its connecting portal)?",
                        Curportal, ROOMNUM(Curroomp)) == IDYES) {
    DeletePortalPair(Curroomp, Curportal);
    Curportal = -1;
  }
}

void CEditorView::OnRoomSnapPointToEdge() {
  if (Markedroomp == NULL) {
    OutrageMessageBox("You must have a marked vertex to use this function.");
    return;
  }

  SnapPointToEdge(
      Markedroomp, Markedroomp->faces[Markedface].face_verts[Markedvert],
      &Curroomp->verts[Curroomp->faces[Curface].face_verts[Curedge]],
      &Curroomp->verts[Curroomp->faces[Curface].face_verts[(Curedge + 1) % Curroomp->faces[Curface].num_verts]]);
}

void CEditorView::OnRoomUndoSnap() { UndoSnap(); }

void CEditorView::OnUpdateRoomUndoSnap(CCmdUI *pCmdUI) { pCmdUI->Enable(Snap_roomnum != -1); }

void CEditorView::OnRoomSnapPointToPoint() {
  if (Markedroomp == NULL) {
    OutrageMessageBox("You must have a marked vertex to use this function.");
    return;
  }

  SnapPointToPoint(Markedroomp, Markedroomp->faces[Markedface].face_verts[Markedvert], Curroomp,
                   Curroomp->faces[Curface].face_verts[Curvert]);
}

void CEditorView::OnReinitOpengl() {
  // TODO: Add your command handler code here
  if (FindArg("-WindowGL")) {
    EditorStatus("Reinitting OpenGL");
    rend_Close();
    rend_Init(RENDERER_OPENGL, Descent, &Render_preferred_state);
  } else {
    EditorStatus("OpenGL command line argument not set.");
  }
}

void CEditorView::OnUpdateReinitOpengl(CCmdUI *pCmdUI) {}

void CEditorView::OnFileRemoveExtraPoints() { RemoveAllDuplicateAndUnusedPoints(); }

void CEditorView::OnRoomBuildSmoothBridge() {
  if ((Markedroomp == NULL) || (Markedface == -1)) {
    OutrageMessageBox("You must have a marked face to use this function.");
    return;
  }

  if ((Markedroomp == Curroomp) && (Markedface == Curface)) {
    OutrageMessageBox("The marked room:face must be different from the current room:face.");
    return;
  }

  BuildSmoothBridge(Markedroomp, Markedface, Curroomp, Curface);
}

void CEditorView::OnRoomJoinRoomsExact() {
  if ((Markedroomp == NULL) || (Markedface == -1)) {
    OutrageMessageBox("You must have a marked face to use this function.");
    return;
  }

  JoinRoomsExact(Curroomp, Curface, Markedroomp, Markedface);
}

#define POPUP_OUTLINE_ON 0x60
#define POPUP_OUTLINE_MINE 0x61
#define POPUP_OUTLINE_TERRAIN 0x62
#define POPUP_OUTLINE_SKY 0x63
#define POPUP_OUTLINE_OBJECTS 0x64

bool CEditorView::SetupPopup(CMenu *popup) {
  bool ret;
  ret = true;
  int grayed = (Outline_mode & OM_ON) ? 0 : MF_GRAYED;

  if (!popup->AppendMenu((Outline_mode & OM_ON) ? MF_CHECKED : MF_UNCHECKED, POPUP_OUTLINE_ON, "On"))
    ret = false;
  if (!popup->AppendMenu(grayed + ((Outline_mode & OM_MINE) ? MF_CHECKED : MF_UNCHECKED), POPUP_OUTLINE_MINE, "Mine"))
    ret = false;
  if (!popup->AppendMenu(grayed + ((Outline_mode & OM_TERRAIN) ? MF_CHECKED : MF_UNCHECKED), POPUP_OUTLINE_TERRAIN,
                         "Terrain"))
    ret = false;
  if (!popup->AppendMenu(grayed + ((Outline_mode & OM_SKY) ? MF_CHECKED : MF_UNCHECKED), POPUP_OUTLINE_SKY, "Sky"))
    ret = false;
  if (!popup->AppendMenu(grayed + ((Outline_mode & OM_OBJECTS) ? MF_CHECKED : MF_UNCHECKED), POPUP_OUTLINE_OBJECTS,
                         "Objects"))
    ret = false;

  return ret;
}

BOOL CEditorView::OnCommand(WPARAM wParam, LPARAM lParam) {
  int old_outline_mode = Outline_mode;

  if (HIWORD(wParam) == 0) {
    switch (LOWORD(wParam)) {
    case POPUP_OUTLINE_ON:
      Outline_mode ^= OM_ON;
      EditorStatus("Outline mode turned %s", OUTLINE_ON(0) ? "ON" : "OFF");
      break;
    case POPUP_OUTLINE_MINE:
      Outline_mode ^= OM_MINE;
      EditorStatus("Mine outline turned %s", OUTLINE_ON(OM_MINE) ? "ON" : "OFF");
      break;
    case POPUP_OUTLINE_TERRAIN:
      Outline_mode ^= OM_TERRAIN;
      EditorStatus("Terrain outline turned %s", OUTLINE_ON(OM_TERRAIN) ? "ON" : "OFF");
      break;
    case POPUP_OUTLINE_SKY:
      Outline_mode ^= OM_SKY;
      EditorStatus("Sky outline turned %s", OUTLINE_ON(OM_SKY) ? "ON" : "OFF");
      break;
    case POPUP_OUTLINE_OBJECTS:
      Outline_mode ^= OM_OBJECTS;
      EditorStatus("Object outline turned %s", OUTLINE_ON(OM_OBJECTS) ? "ON" : "OFF");
      break;
    }
  }

  State_changed = (Outline_mode != old_outline_mode);

  return CView::OnCommand(wParam, lParam);
}

void CEditorView::OnRoomStartNewFace() { StartNewFace(); }

void CEditorView::OnRoomFinishNewFace() { EndNewFace(); }

void CEditorView::OnRoomAddVertToNewFace() { AddNewFaceVert(); }

#include "osiris_predefs.h"
extern bool StripLeadingTrailingSpaces(char *s);

void RenameRoom() {
  char tempname[ROOM_NAME_LEN + 1] = "";

  if (Curroomp->name) {
    ASSERT(strlen(Curroomp->name) <= ROOM_NAME_LEN);
    strcpy(tempname, Curroomp->name);
  }

try_again:;
  if (!InputString(tempname, ROOM_NAME_LEN, "Room Name", "Enter a new name:"))
    return;

  if (StripLeadingTrailingSpaces(tempname))
    EditorMessageBox("Note: Leading and/or trailing spaces have been removed from this name (\"%s\")", tempname);

  int n = osipf_FindRoomName(tempname);
  if ((n != -1) && (n != ROOMNUM(Curroomp))) {
    EditorMessageBox("Room %d already has this name.", n);
    goto try_again;
  }

  if (Curroomp->name) {
    mem_free(Curroomp->name);
    Curroomp->name = NULL;
  }

  if (strlen(tempname)) {
    Curroomp->name = (char *)mem_malloc(strlen(tempname) + 1);
    strcpy(Curroomp->name, tempname);
  }

  World_changed = 1;
}

void CEditorView::OnRoomRenameRoom() { RenameRoom(); }

void CEditorView::OnUpdateRoomSetCenterFromViewer(CCmdUI *pCmdUI) { pCmdUI->Enable(!OBJECT_OUTSIDE(Viewer_object)); }

void CEditorView::OnRoomSetCenterFromViewer() {
  ASSERT(!OBJECT_OUTSIDE(Viewer_object));

  if (Viewer_object->roomnum != ROOMNUM(Curroomp)) {
    EditorMessageBox("The viewer must be in the current room for this operation.");
    return;
  }

  room *rp = &Rooms[Viewer_object->roomnum];

  rp->path_pnt = Viewer_object->pos;
  rp->flags |= RF_MANUAL_PATH_PNT;

  EditorStatus("Center point set for room %d", ROOMNUM(Curroomp));

  World_changed = 1;
}

void CEditorView::OnUpdateRoomClearCenterPoint(CCmdUI *pCmdUI) {
  pCmdUI->Enable((Editor_view_mode == VM_MINE) && ((Curroomp->flags & RF_MANUAL_PATH_PNT) != 0));
}

void CEditorView::OnRoomClearCenterPoint() {
  ASSERT(Curroomp->flags & RF_MANUAL_PATH_PNT);

  Curroomp->flags &= ~RF_MANUAL_PATH_PNT;

  EditorStatus("Center point cleared for room %d", ROOMNUM(Curroomp));

  World_changed = 1;
}

void CEditorView::OnRoomCombine() {
  if (Markedroomp == NULL) {
    OutrageMessageBox("You must have a Marked Room for this operation.");
    return;
  }

  int marked_roomnum = ROOMNUM(Markedroomp);

  if (CombineRooms(Curroomp, Markedroomp))
    EditorStatus("Room %d merged into room %d\n", marked_roomnum, ROOMNUM(Curroomp));
}

void FixDegenerateFaces();

void CEditorView::OnFileFixDegenerateFaces() { FixDegenerateFaces(); }

void CEditorView::OnRoomSnapPointToFace() {
  if (Markedroomp == NULL) {
    OutrageMessageBox("You must have a marked vertex to use this function.");
    return;
  }

  SnapPointToFace(Markedroomp, Markedroomp->faces[Markedface].face_verts[Markedvert],
                  &Curroomp->verts[Curroomp->faces[Curface].face_verts[Curedge]], &Curroomp->faces[Curface].normal);
}

#define MARK_TEXTURE 1

void CEditorView::OnRoomLinkToNewExternal() {
  void LinkToExternalRoom(room * rp, int nfaces, int *facenums);
  int n = 0, facelist[MAX_FACES_PER_ROOM];

  for (int i = 0; i < Curroomp->num_faces; i++) {
    if ((Curroomp->faces[i].portal_num == -1) && (Curroomp->faces[i].tmap == MARK_TEXTURE))
      facelist[n++] = i;
  }

  if (n) {
    if (OutrageMessageBox(MBOX_YESNO, "Do you want to create a new room linked to the %d selected faces in room %d?", n,
                          ROOMNUM(Curroomp)) != IDYES)
      return;

    LinkToExternalRoom(Curroomp, n, facelist);
  } else
    OutrageMessageBox("You have no faces selected in room %d.\n\nTo select a face, texture it with Texture %d, \"%s\".",
                      ROOMNUM(Curroomp), MARK_TEXTURE, GameTextures[MARK_TEXTURE].name);
}

void CEditorView::OnRoomDeleteVert() {
  if (Curroomp->faces[Curface].num_verts <= 3) {
    OutrageMessageBox("You cannot delete a vertex from a face with three or fewer vertices.");
    return;
  }

  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete vertex %d (%d) from room %d face %d?", Curvert,
                        Curroomp->faces[Curface].face_verts[Curvert], ROOMNUM(Curroomp), Curface) == IDYES) {
    DeletePointFromFace(Curroomp, Curface, Curvert);
    Curvert = 0;
  }
}

void CEditorView::OnRoomFaceAddVertToEdge() {
  void SplitEdge(room * rp, int facenum, int edgenum, float position);

  char buf[10] = "0.5";

  if (InputString(buf, sizeof(buf), "New point position",
                  "Please enter the position of the new point, from 0.0 to 1.0")) {
    SplitEdge(Curroomp, Curface, Curedge, atof(buf));
    Curvert = Curedge + 1;
  }
}

void CEditorView::OnRoomFaceMoveVertOnEdge() {
  void MoveVert(room * rp, int facenum, int vertnum, float new_position);

  char buf[10] = "0.5";

  if (InputString(buf, sizeof(buf), "New point position",
                  "Please enter the new position of the point, from 0.0 to 1.0")) {
    MoveVert(Curroomp, Curface, Curvert, atof(buf));
  }
}

void CEditorView::OnRoomFaceSplitFace() {
  void SplitFace(room * rp, int facenum, int v0, int v1);

  if ((Curroomp != Markedroomp) || (Curface != Markedface)) {
    OutrageMessageBox("Cannot split face: the Marked & Current faces must be the same for this operation.");
    return;
  }

  int n_faces = Curroomp->num_faces;

  SplitFace(Curroomp, Curface, Curvert, Markedvert);

  Curface = n_faces - 1;
  Curedge = Curvert = 0;
  Markedroomp = NULL;
}

void CEditorView::OnRoomFaceDeleteVertOnEdge() {
  void DeleteVert(room * rp, int facenum, int vertnum);

  DeleteVert(Curroomp, Curface, Curvert);
}

void CEditorView::OnRoomMergeObjectIntoRoom() {
  if (MergeObjectIntoRoom(Curroomp, Cur_object_index))
    Cur_object_index = -1;
}

void CEditorView::OnRoomDeleteConnectedFaces() {
  if (OutrageMessageBox(
          MBOX_YESNO,
          "This function will delete all faces connected to room %d face %d.  This could be very dangerous.\n\n"
          "Are you sure you want to continue?",
          ROOMNUM(Curroomp), Curface) != IDYES)
    return;

  DeleteAllConnectedFaces(Curroomp, Curface);

  Curface = 0;

  if (Markedroomp == Curroomp)
    Markedroomp = NULL;
}

void CEditorView::OnRoomRotatePlacedRoom45Degrees() {
  Placed_room_angle += 65536 / 8;

  ComputePlacedRoomMatrix();

  State_changed = 1;
}

void CEditorView::OnRoomPropagateToAdjacentCoplanarFaces() {
  extern void PropagateToConnectedFaces(room * rp, int facenum);

  PropagateToConnectedFaces(Curroomp, Curface);
}

void CEditorView::OnViewFlip() {
  Viewer_object->orient.fvec = -Viewer_object->orient.fvec;
  Viewer_object->orient.rvec = -Viewer_object->orient.rvec;

  Viewer_moved = 1;
}

void CEditorView::OnFileRemoveDuplicateFacesFromCurrentRoom() { RemoveDuplicateFaces(Curroomp); }
