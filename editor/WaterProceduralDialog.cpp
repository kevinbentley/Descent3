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

// WaterProceduralDialog.cpp : implementation file
//

#include "mfc_compatibility.h"
#include "editor.h"
#include "game.h"
#include "manage.h"
#include "texpage.h"

#include "WaterProceduralDialog.h"
// #include "procedurals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaterProceduralDialog dialog

#define MAX_SLIDER_RANGE 255

CWaterProceduralDialog::CWaterProceduralDialog(CWnd *pParent /*=NULL*/)
    : CDialog(CWaterProceduralDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWaterProceduralDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CWaterProceduralDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWaterProceduralDialog)
  DDX_Control(pDX, IDC_WP_LIGHT_SLIDER, m_light_slider);
  DDX_Control(pDX, IDC_WP_THICKNESS_SLIDER, m_thickness_slider);
  DDX_Control(pDX, IDC_WP_SIZE_SLIDER, m_size_slider);
  DDX_Control(pDX, IDC_WP_HEIGHT_SLIDER, m_height_slider);
  DDX_Control(pDX, IDC_WP_FREQUENCY_SLIDER, m_frequency_slider);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaterProceduralDialog, CDialog)
//{{AFX_MSG_MAP(CWaterProceduralDialog)
ON_CBN_SELENDOK(IDC_PROCEDURAL_PULLDOWN, OnSelendokProceduralPulldown)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_CLEAR_PROCEDURALS, OnClearProcedurals)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_EN_KILLFOCUS(IDC_PROC_EVAL_TIME_EDIT, OnKillfocusProcEvalTimeEdit)
ON_EN_KILLFOCUS(IDC_PROC_OSC_TIME_EDIT, OnKillfocusProcOscTimeEdit)
ON_EN_KILLFOCUS(IDC_PROC_OSC_VALUE_EDIT, OnKillfocusProcOscValueEdit)
ON_BN_CLICKED(IDC_COPY_PROCEDURAL, OnCopyProcedural)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaterProceduralDialog message handlers

void CWaterProceduralDialog::OnSelendokProceduralPulldown() {
  int cur = SendDlgItemMessage(IDC_PROCEDURAL_PULLDOWN, CB_GETCURSEL, 0, 0);
  m_proc_type = cur;
  UpdateDialog();
}

static static_proc_element save_elements[8000];
BOOL CWaterProceduralDialog::DestroyWindow() {
  // TODO: Add your specialized code here and/or call the base class
  CWnd::KillTimer(1);

  int n = D3EditState.texdlg_texture;

  int save_num = 0;

  // Restore our static proc elements
  save_num = GameTextures[n].procedural->num_static_elements;

  if (save_num > 0)
    memcpy(save_elements, GameTextures[n].procedural->static_proc_elements, save_num * sizeof(static_proc_element));

  FreeStaticProceduralsForTexture(n);
  Sleep(2000);

  if (save_num > 0) {
    AllocateStaticProceduralsForTexture(n, save_num);
    memcpy(GameTextures[n].procedural->static_proc_elements, save_elements, save_num * sizeof(static_proc_element));
    GameTextures[n].procedural->num_static_elements = save_num;
  } else {
    GameTextures[n].flags &= ~(TF_PROCEDURAL | TF_WATER_PROCEDURAL);
  }

  bm_FreeBitmap(m_window_bitmap);
  m_TextureSurf.free();

  return CDialog::DestroyWindow();
}

void CWaterProceduralDialog::PrintValue(int whichbox, uint8_t val) {
  CEdit *ebox;
  char str[255];

  ebox = (CEdit *)GetDlgItem(whichbox);
  sprintf(str, "%d", val);
  ebox->SetWindowText(str);
}

void CWaterProceduralDialog::UpdateDialog() {
  int n = D3EditState.texdlg_texture;

  CEdit *ebox;
  char str[255];
  ebox = (CEdit *)GetDlgItem(IDC_PROC_EVAL_TIME_EDIT);
  sprintf(str, "%f", GameTextures[n].procedural->evaluation_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_PROC_OSC_TIME_EDIT);
  sprintf(str, "%f", GameTextures[n].procedural->osc_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_PROC_OSC_VALUE_EDIT);
  sprintf(str, "%d", GameTextures[n].procedural->osc_value);
  ebox->SetWindowText(str);

  // Update procedural box
  SendDlgItemMessage(IDC_PROCEDURAL_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; stricmp("End", WaterProcNames[i]) != 0; i++) {
    SendDlgItemMessage(IDC_PROCEDURAL_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)WaterProcNames[i]);
  }
  SendDlgItemMessage(IDC_PROCEDURAL_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)WaterProcNames[m_proc_type]);

  // fill in the combo box for copy procedural data
  CComboBox *combo;
  combo = (CComboBox *)GetDlgItem(IDC_PROC_COPY_LIST);
  combo->ResetContent();
  for (int i = 0; i < MAX_TEXTURES; i++) {
    if (!GameTextures[i].used)
      continue;
    if (i == D3EditState.texdlg_texture)
      continue;
    if (!(GameTextures[i].flags & TF_PROCEDURAL))
      continue;
    if (!(GameTextures[i].flags & TF_WATER_PROCEDURAL))
      continue;
    combo->AddString(GameTextures[i].name);
  }
  combo->SetCurSel(0);
}

void CWaterProceduralDialog::UpdateProcView() {
  int n = D3EditState.texdlg_texture;

  FrameCount++;

  CWnd *texwnd;
  RECT rect;

  texwnd = GetDlgItem(IDC_WATER_PROCEDURAL_VIEW);
  texwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  int bm_handle = GetTextureBitmap(n, 0, 1);

  if (GameBitmaps[bm_handle].flags & BF_MIPMAPPED)
    GameBitmaps[m_window_bitmap].flags |= BF_MIPMAPPED;

  bm_ScaleBitmapToBitmap(m_window_bitmap, bm_handle);

  m_TextureSurf.load(m_window_bitmap);

  int x = rect.left + ((rect.right - rect.left) / 2) - m_TextureSurf.width() / 2;
  int y = rect.top + ((rect.bottom - rect.top) / 2) - m_TextureSurf.height() / 2;

  Desktop_surf->blt(x, y, &m_TextureSurf);

  // Do slider values
  m_frequency = 255 - m_frequency_slider.GetPos();
  m_height = m_height_slider.GetPos();
  m_size = m_size_slider.GetPos();

  GameTextures[n].procedural->light = m_light_slider.GetPos();
  GameTextures[n].procedural->thickness = m_thickness_slider.GetPos();

  PrintValue(IDC_SIZE_TEXT, m_size);
  PrintValue(IDC_HEIGHT_TEXT, m_height);
  PrintValue(IDC_FREQ_TEXT, 255 - m_frequency);
  PrintValue(IDC_LIGHT_TEXT, GameTextures[n].procedural->light);
  PrintValue(IDC_THICKNESS_TEXT, GameTextures[n].procedural->thickness);
}

void CWaterProceduralDialog::OnTimer(UINT nIDEvent) {
  // TODO: Add your message handler code here and/or call default
  UpdateProcView();

  CDialog::OnTimer(nIDEvent);
}

BOOL CWaterProceduralDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  CWnd::SetTimer(1, 33, NULL); // 30 frames per second

  int save_num = 0;
  int n = D3EditState.texdlg_texture;

  // Make a temp buffer for our static elements
  if (GameTextures[n].procedural->num_static_elements > 0) {
    save_num = GameTextures[n].procedural->num_static_elements;
    memcpy(save_elements, GameTextures[n].procedural->static_proc_elements, save_num * sizeof(static_proc_element));
  }

  FreeStaticProceduralsForTexture(n);
  Sleep(2000);
  AllocateStaticProceduralsForTexture(n, 8000);

  memcpy(GameTextures[n].procedural->static_proc_elements, save_elements, save_num * sizeof(static_proc_element));
  GameTextures[n].procedural->num_static_elements = save_num;

  m_button_down = 0;
  m_proc_type = 0;
  m_size = 1;
  m_height = 1;
  m_frequency = 0;

  // Alloc bitmap
  CWnd *texwnd;
  RECT rect;

  texwnd = GetDlgItem(IDC_WATER_PROCEDURAL_VIEW);
  texwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;

  m_window_bitmap = bm_AllocBitmap(w, h, ((w * h) / 3) * 2);
  ASSERT(m_window_bitmap >= 0);
  m_TextureSurf.create(bm_w(m_window_bitmap, 0), bm_h(m_window_bitmap, 0), bm_bpp(m_window_bitmap));

  m_frequency_slider.SetRange(0, MAX_SLIDER_RANGE);
  m_frequency_slider.SetPos(255 - m_frequency);

  m_height_slider.SetRange(1, MAX_SLIDER_RANGE);
  m_height_slider.SetPos(m_height);

  m_size_slider.SetRange(1, MAX_SLIDER_RANGE);
  m_size_slider.SetPos(m_size);

  m_light_slider.SetRange(0, 12);
  m_light_slider.SetPos(GameTextures[n].procedural->light);

  m_thickness_slider.SetRange(0, 12);
  m_thickness_slider.SetPos(GameTextures[n].procedural->thickness);

  UpdateDialog();

  // TODO: Add extra initialization here

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaterProceduralDialog::OnClearProcedurals() { ClearAllProceduralsFromTexture(D3EditState.texdlg_texture); }

void CWaterProceduralDialog::HarvestValue(int whichbox, uint8_t *val) {
  CEdit *ebox;
  char name[20];
  int num = 0;

  ebox = (CEdit *)GetDlgItem(whichbox);
  ebox->GetWindowText(name, 20);

  num = atoi(name);
  if (num < 0)
    num = 0;
  if (num > 255)
    num = 255;

  *val = num;

  UpdateDialog();
}

void CWaterProceduralDialog::OnLButtonDown(UINT nFlags, CPoint point) {
  CPoint tpoint = point;
  CWnd *texwnd;
  RECT rect;
  int n = D3EditState.texdlg_texture;

  texwnd = GetDlgItem(IDC_WATER_PROCEDURAL_VIEW);
  texwnd->GetWindowRect(&rect);

  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;

  MapWindowPoints(texwnd, &tpoint, 1);

  if (tpoint.x < 0)
    return;
  if (tpoint.y < 0)
    return;

  if (tpoint.x >= w)
    return;
  if (tpoint.y >= h)
    return;

  int bm_handle = GameTextures[n].procedural->procedural_bitmap;
  int bw = bm_w(bm_handle, 0);
  int bh = bm_h(bm_handle, 0);

  int dest_x = ((float)tpoint.x * (float)((float)bw / (float)w));
  int dest_y = ((float)tpoint.y * (float)((float)bh / (float)h));

  CreateElement(tpoint.x, tpoint.y);

  m_button_down = 1;

  CDialog::OnLButtonDown(nFlags, point);
}

void CWaterProceduralDialog::OnLButtonUp(UINT nFlags, CPoint point) {
  m_button_down = 0;
  CDialog::OnLButtonUp(nFlags, point);
}

void CWaterProceduralDialog::OnMouseMove(UINT nFlags, CPoint point) {
  CPoint tpoint = point;
  CWnd *texwnd;
  RECT rect;
  int n = D3EditState.texdlg_texture;

  if (m_button_down == 0)
    return;

  texwnd = GetDlgItem(IDC_WATER_PROCEDURAL_VIEW);
  texwnd->GetWindowRect(&rect);

  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;

  MapWindowPoints(texwnd, &tpoint, 1);

  if (tpoint.x < 0)
    return;
  if (tpoint.y < 0)
    return;

  if (tpoint.x >= w)
    return;
  if (tpoint.y >= h)
    return;

  if (m_proc_type != PROC_WATER_NONE)
    CreateElement(tpoint.x, tpoint.y);

  CDialog::OnMouseMove(nFlags, point);
}

// Creates a procedural element at x,y
static_proc_element *CWaterProceduralDialog::CreateElement(int x, int y) {
  int n = D3EditState.texdlg_texture;
  proc_struct *procedural = GameTextures[n].procedural;

  int index;

  if (GameTextures[n].procedural->num_static_elements >= MAX_PROC_ELEMENTS)
    return NULL;
  else
    index = GameTextures[n].procedural->num_static_elements;

  static_proc_element *proc_elem = &procedural->static_proc_elements[index];

  CWnd *texwnd;
  RECT rect;

  texwnd = GetDlgItem(IDC_WATER_PROCEDURAL_VIEW);
  texwnd->GetWindowRect(&rect);

  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;

  int bm_handle = GameTextures[n].procedural->procedural_bitmap;
  int bw = bm_w(bm_handle, 0);
  int bh = bm_h(bm_handle, 0);

  int dest_x = ((float)x * (float)((float)bw / (float)w));
  int dest_y = ((float)y * (float)((float)bh / (float)h));

  proc_elem->type = m_proc_type;

  proc_elem->x1 = dest_x;
  proc_elem->y1 = dest_y;
  proc_elem->size = m_size;
  proc_elem->speed = m_height;
  proc_elem->frequency = m_frequency;

  procedural->num_static_elements++;

  return &procedural->static_proc_elements[index];
}

void CWaterProceduralDialog::OnKillfocusProcEvalTimeEdit() {
  int n = D3EditState.texdlg_texture;

  CEdit *ebox;
  char name[20];
  float num = 0;

  ebox = (CEdit *)GetDlgItem(IDC_PROC_EVAL_TIME_EDIT);
  ebox->GetWindowText(name, 20);

  num = atof(name);
  if (num < 0)
    num = 0;
  if (num > 255)
    num = 255;

  GameTextures[n].procedural->evaluation_time = num;

  UpdateDialog();
}

void CWaterProceduralDialog::OnKillfocusProcOscTimeEdit() {
  int n = D3EditState.texdlg_texture;

  CEdit *ebox;
  char name[20];
  float num = 0;

  ebox = (CEdit *)GetDlgItem(IDC_PROC_OSC_TIME_EDIT);
  ebox->GetWindowText(name, 20);

  num = atof(name);
  if (num < 0)
    num = 0;
  if (num > 255)
    num = 255;

  GameTextures[n].procedural->osc_time = num;

  UpdateDialog();
}

void CWaterProceduralDialog::OnKillfocusProcOscValueEdit() {
  int n = D3EditState.texdlg_texture;

  CEdit *ebox;
  char name[20];
  int num = 0;

  ebox = (CEdit *)GetDlgItem(IDC_PROC_OSC_VALUE_EDIT);
  ebox->GetWindowText(name, 20);

  num = atoi(name);
  if (num < 0)
    num = 0;
  if (num > 200)
    num = 200;

  GameTextures[n].procedural->osc_value = num;

  UpdateDialog();
}

void CWaterProceduralDialog::OnCopyProcedural() {
  // get the name of the texture
  CComboBox *combo;
  CString str;
  int src_id;

  combo = (CComboBox *)GetDlgItem(IDC_PROC_COPY_LIST);
  combo->GetLBText(combo->GetCurSel(), str);
  src_id = FindTextureName(str.GetBuffer(0));
  ASSERT(src_id != -1);

  bool do_pal = false;
  char buffer[512];
  sprintf(buffer, "Are you sure you want to replace the procedural elements of %s with %s?",
          GameTextures[D3EditState.texdlg_texture].name, GameTextures[src_id].name);
  if (MessageBox(buffer, "Confirm", MB_YESNO) != IDYES)
    return;
  if (MessageBox("Would you like to replace the palette also?", "Palette", MB_YESNO) == IDYES)
    do_pal = true;

  mngs_texture_page src_page, dest_page;
  mng_AssignTextureToTexPage(src_id, &src_page);
  mng_AssignTextureToTexPage(D3EditState.texdlg_texture, &dest_page);

  ClearAllProceduralsFromTexture(D3EditState.texdlg_texture);
  FreeProceduralForTexture(D3EditState.texdlg_texture);

  int i;
  if (src_page.tex_struct.flags & TF_WATER_PROCEDURAL)
    dest_page.tex_struct.flags |= TF_WATER_PROCEDURAL;
  else
    dest_page.tex_struct.flags &= ~TF_WATER_PROCEDURAL;

  if (do_pal) {
    for (i = 0; i < 255; i++) {
      dest_page.proc_palette[i] = src_page.proc_palette[i];
    }
  }
  dest_page.proc_heat = src_page.proc_heat;
  dest_page.proc_light = src_page.proc_light;
  dest_page.proc_thickness = src_page.proc_thickness;
  dest_page.proc_evaluation_time = src_page.proc_evaluation_time;
  dest_page.osc_time = src_page.osc_time;
  dest_page.osc_value = src_page.osc_value;
  dest_page.num_proc_elements = src_page.num_proc_elements;

  for (i = 0; i < dest_page.num_proc_elements; i++) {
    dest_page.proc_type[i] = src_page.proc_type[i];
    dest_page.proc_frequency[i] = src_page.proc_frequency[i];
    dest_page.proc_speed[i] = src_page.proc_speed[i];
    dest_page.proc_size[i] = src_page.proc_size[i];
    dest_page.proc_x1[i] = src_page.proc_x1[i];
    dest_page.proc_y1[i] = src_page.proc_y1[i];
    dest_page.proc_x2[i] = src_page.proc_x2[i];
    dest_page.proc_y2[i] = src_page.proc_y2[i];
  }

  AllocateProceduralForTexture(D3EditState.texdlg_texture);
  AllocateStaticProceduralsForTexture(D3EditState.texdlg_texture, dest_page.num_proc_elements);
  GameTextures[D3EditState.texdlg_texture].procedural->num_static_elements = dest_page.num_proc_elements;
  GameTextures[D3EditState.texdlg_texture].procedural->heat = dest_page.proc_heat;
  GameTextures[D3EditState.texdlg_texture].procedural->light = dest_page.proc_light;
  GameTextures[D3EditState.texdlg_texture].procedural->thickness = dest_page.proc_thickness;
  GameTextures[D3EditState.texdlg_texture].procedural->evaluation_time = dest_page.proc_evaluation_time;
  GameTextures[D3EditState.texdlg_texture].procedural->osc_time = dest_page.osc_time;
  GameTextures[D3EditState.texdlg_texture].procedural->osc_value = dest_page.osc_value;

  // Last 2 colors are the same
  dest_page.proc_palette[255] = dest_page.proc_palette[254];
  memcpy(GameTextures[D3EditState.texdlg_texture].procedural->palette, dest_page.proc_palette, 256 * 2);

  for (i = 0; i < dest_page.num_proc_elements; i++) {
    static_proc_element *proc = &GameTextures[D3EditState.texdlg_texture].procedural->static_proc_elements[i];
    proc->type = dest_page.proc_type[i];
    proc->frequency = dest_page.proc_frequency[i];
    proc->speed = dest_page.proc_speed[i];
    proc->size = dest_page.proc_size[i];
    proc->x1 = dest_page.proc_x1[i];
    proc->y1 = dest_page.proc_y1[i];
    proc->x2 = dest_page.proc_x2[i];
    proc->y2 = dest_page.proc_y2[i];
  }

  UpdateDialog();
}
