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

 * $Logfile: /DescentIII/Main/D3Launch/BitmapButtonEx.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:56:51 $
 * $Author: kevinb $
 *
 *
 *
 * $Log: not supported by cvs2svn $
 *
 * 25    11/05/98 2:16p Nate
 * Added keyboard support
 *
 * 24    10/30/98 12:09p Nate
 * Fixed clicking on light problem.
 *
 * 23    10/18/98 5:53p Nate
 *
 * 22    10/08/98 6:23p Nate
 * Fixed a few bugs.
 *
 * 21    10/02/98 7:08p Nate
 * Added animation button support.
 *
 * 20    10/01/98 11:51a Nate
 * Fixed the 256-color text problem (finally...)
 *
 * 19    9/30/98 5:21p Nate
 *
 * 18    9/22/98 12:12p Nate
 * Fixed logo text problem.
 *
 * 17    9/22/98 11:33a Nate
 * Added support for logo button text.
 *
 * 16    9/18/98 6:47p Nate
 *
 * 15    9/18/98 6:32p Nate
 *
 * 14    9/18/98 5:19p Nate
 * Made the bitmap button font look a *little* better
 *
 * 13    9/14/98 3:55p Nate
 * Removed debugging output from Button drawing
 *
 * 12    9/14/98 3:48p Nate
 * DrawItem now uses a CClientDC, and AutoLoad is no longer needed (Setup
 * now handles all necessary attachment and sizing  tasks)
 *
 * 11    9/13/98 2:39p Nate
 * Added re-selecting of default bitmaps and palettes for the device
 * contexts.
 *
 * 10    9/10/98 5:17p Nate
 * Added text messages which can be drawn on top of the button.
 *
 * 9     9/03/98 6:57p Nate
 * Fixed StretchBlt() problem by doing some 256 color conversions
 *
 * 8     9/02/98 6:41p Nate
 * Sped up button drawing in 256 color
 *
 * 7     9/01/98 7:15p Nate
 * Major Revision #2
 *
 * 6     8/31/98 6:44p Nate
 * Major Revision
 *
 * 5     8/24/98 7:06p Nate
 * Added new AutoUpdate features, and fixed display glitches
 *
 * 4     8/12/98 9:21a Nate
 * Fixed "gray-button-background" flicker
 *
 * 3     8/10/98 10:44a Nate
 * Added Language selection support
 *
 * 2     8/05/98 11:54a Nate
 * Initial Version
 *
 * $NoKeywords: $
 */

// BitmapButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "D3Launch.h"
#include "BitmapButtonEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Text position values for the standard option button
#define LEFTBUTTON_TEXT_XOFFSET 85
#define RIGHTBUTTON_TEXT_XOFFSET 85
#define BUTTON_TEXT_YOFFSET 17
#define BUTTON_TEXT_WIDTH 132
#define BUTTON_TEXT_HEIGHT 17

// Text position values for the logo button
#define TOPBUTTON_TEXT_XOFFSET 86
#define TOPBUTTON_TEXT_YOFFSET 80
#define TOPBUTTON_TEXT_WIDTH 135
#define TOPBUTTON_TEXT_HEIGHT 17

// Define text colors for button states
#define UP_TEXT_COLOR PALETTERGB(162, 167, 204)
#define UP_TEXT_SHADOW_COLOR PALETTERGB(139, 146, 190)
#define DOWN_TEXT_COLOR PALETTERGB(255, 255, 255)
#define DOWN_TEXT_SHADOW_COLOR PALETTERGB(192, 192, 192)
#define LIT_TEXT_COLOR PALETTERGB(255, 255, 255)
#define LIT_TEXT_SHADOW_COLOR PALETTERGB(192, 192, 192)
#define DISABLED_TEXT_COLOR PALETTERGB(128, 128, 128)
#define DISABLED_TEXT_SHADOW_COLOR PALETTERGB(128, 128, 128)

/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonEx

CBitmapButtonEx::CBitmapButtonEx() {
  m_MouseOverBtn = FALSE;
  m_Hidden = FALSE;

  m_TextMessage = "";                // Default to no string message
  m_Orientation = LEFT_ORIENTED_BTN; // Default to left orientation

  m_AnimBitmaps = NULL;
  m_NumAnimFrames = 0;
  m_CurrAnimFrame = 0;
  m_IgnoreDisabled = FALSE;
}

CBitmapButtonEx::~CBitmapButtonEx() {
  // Delete the allocated bitmaps
  if (m_AnimBitmaps != NULL)
    delete[] m_AnimBitmaps;

  // Detach this from the button object
  Detach();
}

BEGIN_MESSAGE_MAP(CBitmapButtonEx, CBitmapButton)
//{{AFX_MSG_MAP(CBitmapButtonEx)
ON_WM_ERASEBKGND()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonEx message handlers

// Draw the button
void CBitmapButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
  // TODO: Add your code to draw the specified item
  CBitmap *bitmap;
  CPalette *palette;
  COLORREF old_color, new_color, new_shadow_color;
  CFont *old_font = NULL;
  CBitmap *old_bitmap = NULL;
  CPalette *old_palette = NULL;
  int old_mode = 0;
  UINT old_alignment = 0;

  // If button is hidden, don't draw it
  if (m_Hidden)
    return;

  // Get button's state and draw appropriate bitmap
  if (m_AnimBitmaps != NULL) {
    bitmap = &m_AnimBitmaps[m_CurrAnimFrame];
    new_color = DOWN_TEXT_COLOR;
    new_shadow_color = DOWN_TEXT_SHADOW_COLOR;
  } else if (lpDrawItemStruct->itemState & ODS_SELECTED) {
    bitmap = &m_DownBitmap;
    new_color = DOWN_TEXT_COLOR;
    new_shadow_color = DOWN_TEXT_SHADOW_COLOR;
  } else if (!m_IgnoreDisabled && lpDrawItemStruct->itemState & ODS_DISABLED) {
    bitmap = &m_DisabledBitmap;
    new_color = DISABLED_TEXT_COLOR;
    new_shadow_color = DISABLED_TEXT_SHADOW_COLOR;
  } else if (m_MouseOverBtn || lpDrawItemStruct->itemState & ODS_FOCUS) {
    bitmap = &m_MouseBitmap;
    new_color = LIT_TEXT_COLOR;
    new_shadow_color = LIT_TEXT_SHADOW_COLOR;
  } else {
    bitmap = &m_UpBitmap;
    new_color = UP_TEXT_COLOR;
    new_shadow_color = UP_TEXT_SHADOW_COLOR;
  }

  // Use the Application default palette (speeds things up in 256 color)
  palette = &Editor()->m_palette;

  // RECT rect=lpDrawItemStruct->rcItem;

  // Obtain the client window for this button
  CClientDC *dc;
  try {
    dc = new CClientDC(this);
  } catch (CResourceException) {
    OutputDebugString("Could not get ClientDC for bitmap button!\n");
  }

  CDC memDC;

  CRect crect;
  GetClientRect(&crect);

  BITMAP m_bmInfo; // Bitmap info
  bitmap->GetObject(sizeof(BITMAP), &m_bmInfo);

  // Select and realize the palette
  if (dc->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && palette->m_hObject != NULL) {
    old_palette = dc->SelectPalette(palette, TRUE);
    dc->RealizePalette();
  }

  if (memDC.CreateCompatibleDC(dc) == 0)
    OutputDebugString("CreateCompatibleDC() failed.\n");

  if ((old_bitmap = memDC.SelectObject(bitmap)) == NULL)
    OutputDebugString("SelectObject() failed!\n");

  dc->StretchBlt(0, 0, crect.Width(), crect.Height(), &memDC, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);

  // If the button contains a text message, display it
  if (!m_TextMessage.IsEmpty()) {

    // old_font = (CFont *)dc->SelectStockObject( ANSI_VAR_FONT );
    old_font = dc->SelectObject(&m_btn_font);
    old_mode = dc->SetBkMode(TRANSPARENT);
    old_alignment = dc->SetTextAlign(TA_CENTER | TA_TOP);
    old_color = dc->SetTextColor(new_shadow_color);

    dc->ExtTextOut(m_TextStartPoint.x - 1, m_TextStartPoint.y, ETO_CLIPPED, &m_TextClipBox, m_TextMessage, NULL);
    dc->SetTextColor(new_color);

    // dc->Rectangle(&m_TextClipBox);
    dc->ExtTextOut(m_TextStartPoint.x, m_TextStartPoint.y, ETO_CLIPPED, &m_TextClipBox, m_TextMessage, NULL);
    // dc->DrawText(m_TextMessage,&m_TextClipBox,DT_CENTER);

    dc->SetTextColor(old_color);
    dc->SetTextAlign(old_alignment);
    dc->SetBkMode(old_mode);

    if (old_font != NULL)
      dc->SelectObject(old_font);
  }

  if (old_bitmap != NULL)
    memDC.SelectObject(old_bitmap);

  if (old_palette != NULL)
    dc->SelectPalette(old_palette, FALSE);

  if (memDC.DeleteDC() == 0)
    OutputDebugString("DeleteDC() failed!\n");

  delete dc;

  // CBitmapButton::DrawItem(lpDrawItemStruct);
}

// Sets up the button for use
bool CBitmapButtonEx::Setup(UINT nID, CWnd *parent, int orient /*=LEFT_ORIENTED_BTN*/) {
  CString res_name, title;

  if (parent == NULL)
    return FALSE;

  // Let the bitmap class set things up for us
  // NOTE:this function will also cause a redundant loading of bitmaps
  //		since CBitmapButton will store copies for itself, however,
  //		it is this funciton which automatically sets up the button's
  //		size, position, etc. from the resources...
  // AutoLoad(nID,parent);

  // Attach this button instance to the proper button resource
  HWND hwnd;
  parent->GetDlgItem(nID, &hwnd);
  if (Attach(hwnd) == 0)
    OutputDebugString("Attach() failed!\n");

  // Setup the text alignment values
  m_Orientation = orient;

  // Fill in text parameters for different button orientations
  int width, height;
  if (m_Orientation == TOP_ORIENTED_BTN) {

    // top oriented button
    m_TextStartPoint.x = int(TOPBUTTON_TEXT_XOFFSET * DlgWidthModifier);
    m_TextStartPoint.y = int(TOPBUTTON_TEXT_YOFFSET * DlgHeightModifier);

    width = int(TOPBUTTON_TEXT_WIDTH * DlgWidthModifier);
    height = int(TOPBUTTON_TEXT_HEIGHT * DlgHeightModifier);

  } else if (m_Orientation == LEFT_ORIENTED_BTN) {

    // left oriented button
    m_TextStartPoint.x = int(LEFTBUTTON_TEXT_XOFFSET * DlgWidthModifier);
    m_TextStartPoint.y = int(BUTTON_TEXT_YOFFSET * DlgHeightModifier);

    width = int(BUTTON_TEXT_WIDTH * DlgWidthModifier);
    height = int(BUTTON_TEXT_HEIGHT * DlgHeightModifier);

  } else {

    // right oriented button
    m_TextStartPoint.x = int(RIGHTBUTTON_TEXT_XOFFSET * DlgWidthModifier);
    m_TextStartPoint.y = int(BUTTON_TEXT_YOFFSET * DlgHeightModifier);

    width = int(BUTTON_TEXT_WIDTH * DlgWidthModifier);
    height = int(BUTTON_TEXT_HEIGHT * DlgHeightModifier);
  }

  // Now compute the text bounding box from the button parameters
  m_TextClipBox.left = m_TextStartPoint.x - (width / 2);
  m_TextClipBox.top = m_TextStartPoint.y;

  m_TextClipBox.right = m_TextClipBox.left + width;
  m_TextClipBox.bottom = m_TextClipBox.top + height;

  // Set the font for the normal option buttons
  m_btn_font.CreateFont(int(14 * DlgHeightModifier), int(8 * DlgWidthModifier), 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        PROOF_QUALITY, 0, _T("Arial Bold"));

  // Set the font for the logo buttons
  m_logobtn_font.CreateFont(int(14 * DlgHeightModifier), int(8 * DlgWidthModifier), 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            PROOF_QUALITY, 0, _T("Arial Bold"));

  // Load the bitmaps and palettes that we will use
  Load(nID, parent);

  // Resize the buttons to match the proportions of the dialog
  BITMAP bm;
  m_UpBitmap.GetObject(sizeof(BITMAP), &bm);
  SetWindowPos(NULL, 0, 0, int(bm.bmWidth * DlgWidthModifier), int(bm.bmHeight * DlgHeightModifier),
               SWP_NOMOVE | SWP_NOZORDER);

  return TRUE;
}

// Sets up the animation button for use
bool CBitmapButtonEx::AnimSetup(UINT nID, CWnd *parent, int num_frames) {
  CString res_name, title;

  if (num_frames == 0)
    return FALSE;

  if (parent == NULL)
    return FALSE;

  // Let the bitmap class set things up for us
  // NOTE:this function will also cause a redundant loading of bitmaps
  //		since CBitmapButton will store copies for itself, however,
  //		it is this funciton which automatically sets up the button's
  //		size, position, etc. from the resources...
  // AutoLoad(nID,parent);

  // Set the number of frames
  m_NumAnimFrames = num_frames;

  // Attach this button instance to the proper button resource
  HWND hwnd;
  parent->GetDlgItem(nID, &hwnd);
  if (Attach(hwnd) == 0)
    OutputDebugString("Attach() failed!\n");

  // Load the bitmaps and palettes that we will use
  AnimLoad(nID, parent);

  // Resize the buttons to match the proportions of the dialog
  BITMAP bm;
  m_AnimBitmaps[0].GetObject(sizeof(BITMAP), &bm);
  SetWindowPos(NULL, 0, 0, int(bm.bmWidth * DlgWidthModifier), int(bm.bmHeight * DlgHeightModifier),
               SWP_NOMOVE | SWP_NOZORDER);

  return TRUE;
}

// Loads the bitmaps for the button given
//	U - up position
//	D - down position
//	M - lit (mouse is over it) position
//	X -	disabled
bool CBitmapButtonEx::Load(UINT nID, CWnd *parent) {
  CString res_name, title;

  if (parent == NULL)
    return FALSE;

  parent->GetDlgItemText(nID, title);

  OutputDebugString("title =");
  OutputDebugString(title);
  OutputDebugString("\n");

  res_name.Format("%s%s", title, "U");
  GetBitmapAndPalette(res_name, &m_UpBitmap, NULL);
  res_name.Format("%s%s", title, "D");
  GetBitmapAndPalette(res_name, &m_DownBitmap, NULL);
  res_name.Format("%s%s", title, "M");
  GetBitmapAndPalette(res_name, &m_MouseBitmap, NULL);
  res_name.Format("%s%s", title, "X");
  GetBitmapAndPalette(res_name, &m_DisabledBitmap, NULL);

  return (TRUE);
}

// Loads the animation bitmaps for the button given
// Format: nameX where X is the frame #
bool CBitmapButtonEx::AnimLoad(UINT nID, CWnd *parent) {
  CString res_name, title;
  int j;

  if (parent == NULL)
    return FALSE;

  parent->GetDlgItemText(nID, title);

  OutputDebugString("title =");
  OutputDebugString(title);
  OutputDebugString("\n");

  // Allocate bitmap objects
  if (m_NumAnimFrames == 0)
    return FALSE;
  m_AnimBitmaps = new CBitmap[m_NumAnimFrames];
  if (m_AnimBitmaps == NULL)
    return FALSE;

  // Load in the bitmaps
  for (j = 0; j < m_NumAnimFrames; j++) {
    res_name.Format("%s%d", title, j);
    GetBitmapAndPalette(res_name, &m_AnimBitmaps[j], NULL);
  }

  return (TRUE);
}

// Lights/un-Lights the button
void CBitmapButtonEx::Light(bool bLight) { m_MouseOverBtn = (bLight) ? TRUE : FALSE; }

// Hides/un-Hides the button (and disables/enables it)
void CBitmapButtonEx::Hide(bool bHide) {
  m_Hidden = (bHide) ? TRUE : FALSE;
  EnableWindow(!m_Hidden);
}

// Sets the button's text message
void CBitmapButtonEx::SetText(UINT nID) { m_TextMessage.LoadString(nID); }

// Increments the animation frame
void CBitmapButtonEx::DoNextAnimFrame(void) {
  m_CurrAnimFrame++;
  if (m_CurrAnimFrame == m_NumAnimFrames)
    m_CurrAnimFrame = 0;
}

// This function is called whenever the button's background needs to
// be erased. It simply returns saying that the button's background has already
// been erased - this is necessary to prevent the "gray-button-background"
// flicker during window updates
BOOL CBitmapButtonEx::OnEraseBkgnd(CDC *pDC) {
  // TODO: Add your message handler code here and/or call default

  // return CBitmapButton::OnEraseBkgnd(pDC);
  return 1;
}
