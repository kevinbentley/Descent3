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

// WorldObjectsGenericDialog.cpp : implementation file
//

#include <filesystem>

#include "mfc_compatibility.h"
#include "editor.h"
#include "WorldObjectsGenericDialog.h"
#include "PhysicsDlg.h"
#include "AISettingsDlg.h"
#include "objinfo.h"
#include "polymodel.h"
#include "AnimStatesDialog.h"
#include "EditLineDialog.h"
#include "genericpage.h"
#include "RobotEditWeaponsDialog.h"
#include "GenericLightDialog.h"
#include "robotfire.h"
#include "ddio.h"
#include "soundload.h"
#include "objinit.h"
#include "gametexture.h"
#include "vclip.h"
#include "QuickCompile.h"
#include "mem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldObjectsGenericDialog dialog

// Data for copy/paste object
object_info Copy_object;

CWorldObjectsGenericDialog::CWorldObjectsGenericDialog(CWnd *pParent /*=NULL*/)
    : CDialog(CWorldObjectsGenericDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWorldObjectsGenericDialog)
  m_type_name = _T("");
  m_current = 0;
  m_sInvenDescription = _T("");
  m_sInvenIconName = _T("");
  //}}AFX_DATA_INIT
}

void CWorldObjectsGenericDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWorldObjectsGenericDialog)
  DDX_Control(pDX, IDC_GENERIC_AMBIENT_SOUND_COMBO, m_ambient_sound_combo);
  DDX_Control(pDX, IDC_GENERIC_EXPLOSION_SOUND_COMBO, m_explosion_sound_combo);
  DDX_Text(pDX, IDC_GENERIC_TYPE_NAME, m_type_name);
  DDX_Text(pDX, IDC_GENERIC_ID_EDIT, m_current);
  DDX_Text(pDX, IDC_GENERIC_INVEN_DESCRIPTION, m_sInvenDescription);
  DDV_MaxChars(pDX, m_sInvenDescription, 180);
  DDX_Text(pDX, IDC_GENERIC_INVEN_ICONNAME, m_sInvenIconName);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldObjectsGenericDialog, CDialog)
//{{AFX_MSG_MAP(CWorldObjectsGenericDialog)
ON_BN_CLICKED(IDC_GENERIC_EDIT_AI, OnGenericEditAI)
ON_BN_CLICKED(IDC_GENERIC_EDIT_PHYSICS, OnGenericEditPhysics)
ON_BN_CLICKED(IDC_GENERIC_USES_AI, OnGenericUsesAI)
ON_BN_CLICKED(IDC_GENERIC_USES_PHYSICS, OnGenericUsesPhysics)
ON_BN_CLICKED(IDC_GENERIC_ADD_NEW, OnGenericAddNew)
ON_BN_CLICKED(IDC_GENERIC_CHECKED_OUT, OnGenericCheckedOut)
ON_BN_CLICKED(IDC_GENERIC_CHECKIN, OnGenericCheckIn)
ON_BN_CLICKED(IDC_GENERIC_DEFINE_ANIMSTATES, OnGenericDefineAnimStates)
ON_BN_CLICKED(IDC_GENERIC_DELETE, OnGenericDelete)
ON_BN_CLICKED(IDC_GENERIC_LOCK, OnGenericLock)
ON_BN_CLICKED(IDC_GENERIC_NEXT, OnGenericNext)
ON_BN_CLICKED(IDC_GENERIC_PREV, OnGenericPrev)
ON_BN_CLICKED(IDC_GENERIC_CHANGE_MODEL, OnGenericChangeModel)
ON_BN_CLICKED(IDC_GENERIC_CHANGE_NAME, OnGenericChangeName)
ON_WM_TIMER()
ON_CBN_SELENDOK(IDC_GENERIC_NAME_PULLDOWN, OnSelendokGenericNamePulldown)
ON_EN_KILLFOCUS(IDC_GENERIC_SIZE_EDIT, OnKillfocusGenericSizeEdit)
ON_BN_CLICKED(IDC_GENERIC_COPY, OnGenericCopy)
ON_BN_CLICKED(IDC_GENERIC_PASTE, OnGenericPaste)
ON_EN_KILLFOCUS(IDC_GENERIC_SCRIPT_ID_EDIT, OnKillfocusGenericScriptIDEdit)
ON_BN_CLICKED(IDC_GENERIC_UNDO_LOCK, OnGenericUndoLock)
ON_BN_CLICKED(IDC_GENERIC_DESTROYABLE, OnGenericDestroyable)
ON_EN_KILLFOCUS(IDC_GENERIC_HITPOINT_EDIT, OnKillfocusGenericHitpointEdit)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_GENERIC_WEAPON_INFO_BUTTON, OnGenericWeaponInfoButton)
ON_BN_CLICKED(IDC_GENERIC_LIGHT_BUTTON, OnGenericLightButton)
ON_BN_CLICKED(IDC_DEFAULT_RADIUS_BUTTON, OnDefaultRadiusButton)
ON_BN_CLICKED(IDC_SELSCRIPT, OnSelScript)
ON_BN_CLICKED(IDC_GENERIC_CONCUSSIVE_CHECK, OnGenericConcussiveCheck)
ON_EN_KILLFOCUS(IDC_GENERIC_IMPACT_DAMAGE_EDIT, OnKillfocusGenericImpactDamageEdit)
ON_EN_KILLFOCUS(IDC_GENERIC_IMPACT_SIZE_EDIT, OnKillfocusGenericImpactSizeEdit)
ON_BN_CLICKED(IDC_NOLOD, OnNolod)
ON_BN_CLICKED(IDC_HIRES_RADIO, OnHiresRadio)
ON_BN_CLICKED(IDC_MEDRES_RADIO, OnMedresRadio)
ON_BN_CLICKED(IDC_LORES_RADIO, OnLoresRadio)
ON_EN_KILLFOCUS(IDC_GENERIC_IMPACT_TIME_EDIT, OnKillfocusGenericImpactTimeEdit)
ON_CBN_SELENDOK(IDC_GENERIC_EXPLOSION_SOUND_COMBO, OnSelendokGenericExplosionSoundCombo)
ON_CBN_SELENDOK(IDC_GENERIC_AMBIENT_SOUND_COMBO, OnSelendokGenericAmbientSoundCombo)
ON_EN_KILLFOCUS(IDC_GENERIC_INVEN_DESCRIPTION, OnKillfocusGenericInvenDescription)
ON_EN_KILLFOCUS(IDC_GENERIC_INVEN_ICONNAME, OnKillfocusGenericInvenIconname)
ON_BN_CLICKED(IDC_OVERRIDE, OnOverride)
ON_BN_CLICKED(IDC_GENERIC_INVEN_SELECTABLE, OnGenericInvenSelectable)
ON_BN_CLICKED(IDC_GENERIC_INVEN_NONUSEABLE, OnGenericInvenNonuseable)
ON_EN_KILLFOCUS(IDC_LOD_DISTANCE_EDIT, OnKillfocusLodDistanceEdit)
ON_BN_CLICKED(IDC_INVTYPE_GAME, OnInvtypeGame)
ON_BN_CLICKED(IDC_INVTYPE_MISSION, OnInvtypeMission)
ON_BN_CLICKED(IDC_INVEN_NOREMOVE, OnInvenNoremove)
ON_BN_CLICKED(IDC_INVEN_VISWHENUSED, OnInvenViswhenused)
ON_CBN_SELENDOK(IDC_DEATH_POWERUP1_PULLDOWN, OnSelendokDeathPowerup1Pulldown)
ON_EN_KILLFOCUS(IDC_DEATH_POWERUP1_NUM_EDIT, OnKillfocusDeathPowerup1NumEdit)
ON_EN_KILLFOCUS(IDC_DEATH_POWERUP1_PERCENT_EDIT, OnKillfocusDeathPowerup1PercentEdit)
ON_EN_KILLFOCUS(IDC_DEATH_POWERUP2_NUM_EDIT, OnKillfocusDeathPowerup2NumEdit)
ON_EN_KILLFOCUS(IDC_DEATH_POWERUP2_PERCENT_EDIT, OnKillfocusDeathPowerup2PercentEdit)
ON_CBN_SELENDOK(IDC_DEATH_POWERUP2_PULLDOWN, OnSelendokDeathPowerup2Pulldown)
ON_BN_CLICKED(IDC_DEATH_POWERUP_USE2_IF_HAVE1_CHECK, OnDeathPowerupUse2IfHave1Check)
ON_BN_CLICKED(IDC_GENERIC_DEATH_SPEW_2_IF_ZERO_1, OnGenericDeathSpew2IfZero1)
ON_EN_KILLFOCUS(IDC_SCRIPTNAME, OnKillfocusScriptname)
ON_BN_CLICKED(IDC_COMPILEMODULE, OnCompilemodule)
ON_EN_KILLFOCUS(IDC_SCRIPT_OVERRIDE, OnKillfocusScriptOverride)
ON_BN_CLICKED(IDC_GENERIC_AI_SCRIPTED_DEATH, OnGenericAiScriptedDeath)
ON_EN_KILLFOCUS(IDC_RESPAWN_SCALAR_EDIT, OnKillfocusRespawnScalarEdit)
ON_BN_CLICKED(IDC_GENERIC_DEATHS, OnGenericDeaths)
ON_EN_KILLFOCUS(IDC_GENERIC_SCORE_EDIT, OnKillfocusGenericScoreEdit)
ON_EN_KILLFOCUS(IDC_GENERIC_AMMO_EDIT, OnKillfocusGenericAmmoEdit)
ON_BN_CLICKED(IDC_OBJ_CEILING_CHECK, OnObjCeilingCheck)
ON_BN_CLICKED(IDC_OBJECT_FLY_THROUGH_RENDERED_PORTALS, OnObjectFlyThroughRenderedPortals)
ON_BN_CLICKED(IDC_NSC_BUTTON, OnNscButton)
ON_BN_CLICKED(IDC_DSMPBD_CHECK, OnDsmpbdCheck)
ON_BN_CLICKED(IDC_GENERIC_AMBIENT, OnGenericAmbient)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldObjectsGenericDialog message handlers

void CWorldObjectsGenericDialog::EnableDisableAll(bool flag) {
  ((CButton *)GetDlgItem(IDC_GENERIC_USES_AI))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_USES_PHYSICS))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_CHECKED_OUT))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_CHECKIN))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_DEFINE_ANIMSTATES))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_DELETE))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_LOCK))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_UNDO_LOCK))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_NEXT))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_PREV))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_EDIT_PHYSICS))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_EDIT_AI))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_COPY))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_CHANGE_NAME))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_CHANGE_MODEL))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_SIZE_EDIT))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_DESTROYABLE))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_AI_SCRIPTED_DEATH))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_OBJ_CEILING_CHECK))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_HITPOINT_EDIT))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_SCORE_EDIT))->EnableWindow(flag);
  ((CButton *)GetDlgItem(IDC_GENERIC_AMMO_EDIT))->EnableWindow(flag);
}

// Returns true if the specified object is locked
bool CWorldObjectsGenericDialog::IsLocked(int n) {
  return (mng_FindTrackLock(Object_info[n].name, PAGETYPE_GENERIC) != -1);
}

// Returns the number of locked items of the current type
int CWorldObjectsGenericDialog::CountLockedItems() {
  int lock_count = 0;
  int first, n;

  first = n = GetObjectID(m_type);

  if (first == -1)
    return 0;

  do {
    if (IsLocked(n))
      lock_count++;
    n = GetNextObjectID(n);
  } while (n != first);

  return lock_count;
}

#define NULL_NAME "<none>"

void CWorldObjectsGenericDialog::UpdateDialog() {
  CEdit *ebox;
  CButton *bbox;
  int first, n;
  char txt[100];
  int i;

  if (m_current == -1) {
    // ebox=(CEdit *) GetDlgItem (IDC_GENERIC_NAME_EDIT);
    // ebox->SetWindowText ("NONE");
    EnableDisableAll(0);

    // Show paste button if you have the network, and there's an object in the copy buffer
    ((CButton *)GetDlgItem(IDC_GENERIC_PASTE))->EnableWindow(Network_up && (Copy_object.type != OBJ_NONE));

    return;
  }

  EnableDisableAll(1);

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_MODEL_NAME_EDIT);

  PageInPolymodel(Object_info[m_current].render_handle);

  if (m_lod == 0)
    ebox->SetWindowText(Poly_models[Object_info[m_current].render_handle].name);
  else if (m_lod == 1) {
    if (Object_info[m_current].med_render_handle == -1)
      ebox->SetWindowText("No model defined");
    else
      ebox->SetWindowText(Poly_models[Object_info[m_current].med_render_handle].name);
  } else {
    if (Object_info[m_current].lo_render_handle == -1)
      ebox->SetWindowText("No model defined");
    else
      ebox->SetWindowText(Poly_models[Object_info[m_current].lo_render_handle].name);
  }

  // Do LOD distance edit box
  ebox = (CEdit *)GetDlgItem(IDC_LOD_DISTANCE_EDIT);

  if (m_lod == 0)
    ebox->SetWindowText("0");
  else if (m_lod == 1) {
    sprintf(txt, "%f", Object_info[m_current].med_lod_distance);
    ebox->SetWindowText(txt);
  } else {
    sprintf(txt, "%f", Object_info[m_current].lo_lod_distance);
    ebox->SetWindowText(txt);
  }

  int poly_handle;
  if (m_lod == 0)
    poly_handle = Object_info[m_current].render_handle;
  else if (m_lod == 1)
    poly_handle = Object_info[m_current].med_render_handle;
  else
    poly_handle = Object_info[m_current].lo_render_handle;

  if (poly_handle == -1)
    sprintf(txt, "Num polys: NA");
  else {
    PageInPolymodel(poly_handle);
    sprintf(txt, "Num polys: %d", CountFacesInPolymodel(&Poly_models[poly_handle]));
  }
  ebox = (CEdit *)GetDlgItem(IDC_NUM_POLYS);
  ebox->SetWindowText(txt);

  // Print out texture RAM usage
  ebox = (CEdit *)GetDlgItem(IDC_TEXTURE_RAM_TEXT);
  if (poly_handle == -1)
    sprintf(txt, "Texture RAM: NA");
  else {
    int tram = GetTextureUsageForPolymodel(poly_handle);
    sprintf(txt, "Texture RAM: %dK", tram / 1000);
  }
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_RESPAWN_SCALAR_EDIT);
  sprintf(txt, "%f", Object_info[m_current].respawn_scalar);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_IMPACT_SIZE_EDIT);
  sprintf(txt, "%f", Object_info[m_current].impact_size);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_IMPACT_TIME_EDIT);
  sprintf(txt, "%f", Object_info[m_current].impact_time);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_IMPACT_DAMAGE_EDIT);
  sprintf(txt, "%f", Object_info[m_current].damage);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP1_NUM_EDIT);
  sprintf(txt, "%d", Object_info[m_current].dspew_number[0]);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP2_NUM_EDIT);
  sprintf(txt, "%d", Object_info[m_current].dspew_number[1]);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP1_PERCENT_EDIT);
  sprintf(txt, "%f", Object_info[m_current].dspew_percent[0] * 100.0f);
  ebox->SetWindowText(txt);

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP2_PERCENT_EDIT);
  sprintf(txt, "%f", Object_info[m_current].dspew_percent[1] * 100.0f);
  ebox->SetWindowText(txt);

  bbox = (CButton *)GetDlgItem(IDC_GENERIC_USES_PHYSICS);
  bbox->SetCheck(Object_info[m_current].flags & OIF_USES_PHYSICS);
  ((CButton *)GetDlgItem(IDC_GENERIC_EDIT_PHYSICS))->EnableWindow(Object_info[m_current].flags & OIF_USES_PHYSICS);

  bbox = (CButton *)GetDlgItem(IDC_DEATH_POWERUP_USE2_IF_HAVE1_CHECK);
  bbox->SetCheck(Object_info[m_current].f_dspew & DSF_ONLY_IF_PLAYER_HAS_OBJ_1);

  bbox = (CButton *)GetDlgItem(IDC_GENERIC_DEATH_SPEW_2_IF_ZERO_1);
  bbox->SetCheck(Object_info[m_current].f_dspew & DSF_ONLY_IF_NO_1);

  // Update the sound combo boxes
  m_explosion_sound_combo.SetSelected(Object_info[m_current].sounds[GSI_EXPLODE]);
  m_ambient_sound_combo.SetSelected(Object_info[m_current].sounds[GSI_AMBIENT]);

  SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE)
      SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[i].name);
  }
  if (Object_info[m_current].dspew[0] >= 0 && Object_info[m_current].dspew[0] < MAX_OBJECT_IDS &&
      Object_info[Object_info[m_current].dspew[0]].type != OBJ_NONE)
    SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Object_info[Object_info[m_current].dspew[0]].name);
  else
    SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);

  SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE)
      SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[i].name);
  }
  if (Object_info[m_current].dspew[1] >= 0 && Object_info[m_current].dspew[1] < MAX_OBJECT_IDS &&
      Object_info[Object_info[m_current].dspew[1]].type != OBJ_NONE)
    SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Object_info[Object_info[m_current].dspew[1]].name);
  else
    SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);

  // Edit AI box
  bbox = (CButton *)GetDlgItem(IDC_GENERIC_USES_AI);
  bbox->SetCheck(Object_info[m_current].flags & OIF_CONTROL_AI);
  ((CButton *)GetDlgItem(IDC_GENERIC_EDIT_AI))->EnableWindow(Object_info[m_current].flags & OIF_CONTROL_AI);

  // Weapon Info box
  ((CButton *)GetDlgItem(IDC_GENERIC_WEAPON_INFO_BUTTON))
      ->EnableWindow(Poly_models[Object_info[m_current].render_handle].num_wbs > 0);

  // Update the size in the edit box
  sprintf(txt, "%.2f", Object_info[m_current].size);
  ((CEdit *)GetDlgItem(IDC_GENERIC_SIZE_EDIT))->SetWindowText(txt);

  // Edit hitpoint box
  bbox = (CButton *)GetDlgItem(IDC_GENERIC_DESTROYABLE);
  bbox->SetCheck(Object_info[m_current].flags & OIF_DESTROYABLE);
  ((CButton *)GetDlgItem(IDC_GENERIC_HITPOINT_EDIT))->EnableWindow(Object_info[m_current].flags & OIF_DESTROYABLE);
  ((CButton *)GetDlgItem(IDC_GENERIC_SCORE_EDIT))->EnableWindow(Object_info[m_current].flags & OIF_DESTROYABLE);

  bbox = (CButton *)GetDlgItem(IDC_GENERIC_AI_SCRIPTED_DEATH);
  bbox->SetCheck(Object_info[m_current].flags & OIF_AI_SCRIPTED_DEATH);

  bbox = (CButton *)GetDlgItem(IDC_OBJ_CEILING_CHECK);
  bbox->SetCheck(Object_info[m_current].flags & OIF_DO_CEILING_CHECK);

  bbox = (CButton *)GetDlgItem(IDC_OBJECT_FLY_THROUGH_RENDERED_PORTALS);
  bbox->SetCheck(Object_info[m_current].flags & OIF_IGNORE_FORCEFIELDS_AND_GLASS);

  bbox = (CButton *)GetDlgItem(IDC_NSC_BUTTON);
  bbox->SetCheck(Object_info[m_current].flags & OIF_NO_DIFF_SCALE_DAMAGE);

  bbox = (CButton *)GetDlgItem(IDC_DSMPBD_CHECK);
  bbox->SetCheck(Object_info[m_current].flags & OIF_NO_DIFF_SCALE_MOVE);

  bbox = (CButton *)GetDlgItem(IDC_GENERIC_AMBIENT);
  bbox->SetCheck(Object_info[m_current].flags & OIF_AMBIENT_OBJECT);

  // Update the hit points in the edit box
  sprintf(txt, (Object_info[m_current].flags & OIF_DESTROYABLE) ? "%d" : "", Object_info[m_current].hit_points);
  ((CEdit *)GetDlgItem(IDC_GENERIC_HITPOINT_EDIT))->SetWindowText(txt);

  // Update the score in the edit box
  sprintf(txt, (Object_info[m_current].flags & OIF_DESTROYABLE) ? "%d" : "", Object_info[m_current].score);
  ((CEdit *)GetDlgItem(IDC_GENERIC_SCORE_EDIT))->SetWindowText(txt);

  // Update ammo control
  sprintf(txt, "%d", Object_info[m_current].ammo_count);
  ((CEdit *)GetDlgItem(IDC_GENERIC_AMMO_EDIT))->SetWindowText(txt);
  ((CButton *)GetDlgItem(IDC_GENERIC_AMMO_TEXT))->EnableWindow(Object_info[m_current].type == OBJ_POWERUP);
  ((CButton *)GetDlgItem(IDC_GENERIC_AMMO_EDIT))->EnableWindow(Object_info[m_current].type == OBJ_POWERUP);

  // Show script handle
  //	sprintf(txt,(Object_info[m_current].script_handle==-1)?"None":"%d",Object_info[m_current].script_handle);
  //	((CEdit *) GetDlgItem(IDC_GENERIC_SCRIPT_ID_EDIT))->SetWindowText(txt);

  // Enabled show checked out button if there are items checked out
  ((CButton *)GetDlgItem(IDC_GENERIC_CHECKED_OUT))->EnableWindow(m_locked_count > 0);

  // Show the current ID
  sprintf(txt, "%d", m_current);
  ((CEdit *)GetDlgItem(IDC_GENERIC_ID_EDIT))->SetWindowText(txt);

  // Show paste button if you have the network, and there's an object in the copy buffer
  ((CButton *)GetDlgItem(IDC_GENERIC_PASTE))->EnableWindow(Network_up && (Copy_object.type != OBJ_NONE));

  // Show delete button if page is locked
  ((CButton *)GetDlgItem(IDC_GENERIC_DELETE))->EnableWindow(IsLocked(m_current));

  // Show lock button if network is up, and item not already locked
  ((CButton *)GetDlgItem(IDC_GENERIC_LOCK))->EnableWindow(Network_up && !IsLocked(m_current));

  // Show checkin button if network is up, and item is locked
  ((CButton *)GetDlgItem(IDC_GENERIC_CHECKIN))->EnableWindow(Network_up && IsLocked(m_current));

  // Show undo lock button if network is up, and item is locked
  ((CButton *)GetDlgItem(IDC_GENERIC_UNDO_LOCK))->EnableWindow(Network_up && IsLocked(m_current));

  // Show add new button if network is up
  ((CButton *)GetDlgItem(IDC_GENERIC_ADD_NEW))->EnableWindow(Network_up);

  // Reset name pulldown list
  SendDlgItemMessage(IDC_GENERIC_NAME_PULLDOWN, CB_RESETCONTENT, 0, 0);
  first = n = GetObjectID(m_type);
  if (first != -1) {
    do {
      SendDlgItemMessage(IDC_GENERIC_NAME_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[n].name);
      n = GetNextObjectID(n);
    } while (n != first);
    n = SendDlgItemMessage(IDC_GENERIC_NAME_PULLDOWN, CB_FINDSTRINGEXACT, 0,
                           (LPARAM)(LPCTSTR)Object_info[m_current].name);
    ASSERT(n != CB_ERR);
    SendDlgItemMessage(IDC_GENERIC_NAME_PULLDOWN, CB_SETCURSEL, n, 0);
  }

  // Reset script edit box
  ebox = (CEdit *)GetDlgItem(IDC_SCRIPTNAME);
  if (!Object_info[m_current].module_name[0])
    ebox->SetWindowText("null");
  else
    ebox->SetWindowText(Object_info[m_current].module_name);

  ebox = (CEdit *)GetDlgItem(IDC_SCRIPT_OVERRIDE);
  if (!Object_info[m_current].script_name_override[0])
    ebox->SetWindowText("null");
  else
    ebox->SetWindowText(Object_info[m_current].script_name_override);

  bbox = (CButton *)GetDlgItem(IDC_GENERIC_INVEN_SELECTABLE);
  bbox->SetCheck(Object_info[m_current].flags & OIF_INVEN_SELECTABLE);

  bbox = (CButton *)GetDlgItem(IDC_GENERIC_INVEN_NONUSEABLE);
  bbox->SetCheck(Object_info[m_current].flags & OIF_INVEN_NONUSEABLE);

  bbox = (CButton *)GetDlgItem(IDC_INVEN_NOREMOVE);
  bbox->SetCheck(Object_info[m_current].flags & OIF_INVEN_NOREMOVE);

  bbox = (CButton *)GetDlgItem(IDC_INVEN_VISWHENUSED);
  bbox->SetCheck(Object_info[m_current].flags & OIF_INVEN_VISWHENUSED);

  if (Object_info[m_current].flags & OIF_INVEN_TYPE_MISSION) {
    bbox = (CButton *)GetDlgItem(IDC_INVTYPE_MISSION);
    bbox->SetCheck(true);
    bbox = (CButton *)GetDlgItem(IDC_INVTYPE_GAME);
    bbox->SetCheck(false);
  } else {
    bbox = (CButton *)GetDlgItem(IDC_INVTYPE_GAME);
    bbox->SetCheck(true);
    bbox = (CButton *)GetDlgItem(IDC_INVTYPE_MISSION);
    bbox->SetCheck(false);
  }

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_INVEN_DESCRIPTION);
  if (!Object_info[m_current].description)
    ebox->SetWindowText("<no description>");
  else
    ebox->SetWindowText(Object_info[m_current].description);

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_INVEN_ICONNAME);
  if (!Object_info[m_current].icon_name[0])
    ebox->SetWindowText("<no icon>");
  else
    ebox->SetWindowText(Object_info[m_current].icon_name);

  ebox = (CEdit *)GetDlgItem(IDC_NOLOD);
  if (m_lod == 0)
    ebox->EnableWindow(FALSE);
  else if (m_lod == 1) {
    if (Object_info[m_current].med_render_handle == -1)
      ebox->EnableWindow(FALSE);
    else
      ebox->EnableWindow(TRUE);
  } else {
    if (Object_info[m_current].lo_render_handle == -1)
      ebox->EnableWindow(FALSE);
    else
      ebox->EnableWindow(TRUE);
  }

  bbox = (CButton *)GetDlgItem(IDC_HIRES_RADIO);
  bbox->SetCheck(m_lod == 0);

  bbox = (CButton *)GetDlgItem(IDC_MEDRES_RADIO);
  bbox->SetCheck(m_lod == 1);

  bbox = (CButton *)GetDlgItem(IDC_LORES_RADIO);
  bbox->SetCheck(m_lod == 2);

  // Update the picture
  UpdateObjectView();
}

BOOL CWorldObjectsGenericDialog::OnInitDialog() {
  static bool first_time = 1;

  m_type_name = Object_type_names[m_type];
  m_lod = 0;

  Copy_object.description = NULL;

  CDialog::OnInitDialog();

  // Start the timer
  CWnd::SetTimer(1, 50, NULL);

  // Make sure we have a valid object
  if (Object_info[m_current].type != m_type)
    m_current = GetObjectID(m_type);

  // Find out how many locked items
  m_locked_count = CountLockedItems();

  // Init copy/paste
  if (first_time) {
    Copy_object.type = OBJ_NONE;
    first_time = 0;
  }

  CEdit *edit = (CEdit *)GetDlgItem(IDC_GENERIC_INVEN_DESCRIPTION);
  edit->LimitText(0);

  // Initialize sound combo boxes
  m_explosion_sound_combo.Init(Object_info[m_current].sounds[GSI_EXPLODE]);
  m_ambient_sound_combo.Init(Object_info[m_current].sounds[GSI_AMBIENT]);

  // Update all the fields
  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorldObjectsGenericDialog::OnGenericEditAI() {
  CAISettingsDlg dlg(Object_info[m_current].ai_info);

  dlg.DoModal();
}

void CWorldObjectsGenericDialog::OnGenericEditPhysics() {
  CPhysicsDlg dlg(&Object_info[m_current].phys_info);

  dlg.DoModal();
}

void CWorldObjectsGenericDialog::OnGenericUsesAI() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_USES_AI);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_CONTROL_AI;
  else
    Object_info[m_current].flags &= ~OIF_CONTROL_AI;

  ((CButton *)GetDlgItem(IDC_GENERIC_EDIT_AI))->EnableWindow(Object_info[m_current].flags & OIF_CONTROL_AI);
}

void CWorldObjectsGenericDialog::OnGenericUsesPhysics() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_USES_PHYSICS);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_USES_PHYSICS;
  else
    Object_info[m_current].flags &= ~OIF_USES_PHYSICS;

  ((CButton *)GetDlgItem(IDC_GENERIC_EDIT_PHYSICS))->EnableWindow(Object_info[m_current].flags & OIF_USES_PHYSICS);
}

// Gets a name from the user, making sure it's unique
// Returns true if got new name, false if cancelled.
// the data in buf not changed if cancel is pressed
bool InputObjectName(char *buf, int len, char *title, char *prompt, CWnd *wnd) {
  if (len > (PAGENAME_LEN - 1))
    len = PAGENAME_LEN - 1;

  char *tempbuf = (char *)mem_malloc(len);

  strncpy(tempbuf, buf, len - 1);
  tempbuf[len - 1] = '\0';

try_again:

  if (!InputString(tempbuf, len, title, prompt, wnd)) {
    mem_free(tempbuf);
    return 0;
  }

  if (FindObjectIDName(tempbuf) != -1) {
    OutrageMessageBox("The name you specified is already in use.  Enter another name.");
    goto try_again;
  }

  strcpy(buf, tempbuf);
  mem_free(tempbuf);

  return 1;
}

void CWorldObjectsGenericDialog::OnGenericAddNew() {
  char filename[256], dir[256], fname[256], ext[32];
  char cur_name[100], *t;
  int img_handle;
  int object_handle;
  int c = 1, finding_name = 1;

  ASSERT(Network_up);

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_model_dir, sizeof(Current_model_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  ChangePolyModelName(filename, cur_name);

  if ((FindPolyModelName(fname)) != -1) {
    OutrageMessageBox("You must rename your model to something else because there is already a model with that name!");
    return;
  }

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadPolyModel(filename, 0);

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that model file.");
    return;
  }

  // Get a default name
  strcpy(cur_name, fname);   // Start with the filename
  t = strchr(cur_name, '.'); // Strip the extention
  if (!t)
    t = cur_name + strlen(cur_name);
  *t = 0;
  do { // Make sure the name not already in use
    int c = 0;

    if (FindObjectIDName(cur_name) == -1)
      break;

    *t = 0;
    sprintf(cur_name, "%s%d", cur_name, ++c);
  } while (1);
  cur_name[0] = toupper(cur_name[0]); // make first char uppercase

// Get the object name from the user
retry_name:

  if (!InputObjectName(cur_name, sizeof(cur_name), "Object name", "Enter a name for your object:", this))
    return;

  if (FindObjectIDName(cur_name) != -1) {
    OutrageMessageBox("That name is taken, please choose another.");
    goto retry_name;
  }

  // Alloc an object and give a name not already taken by some other object

  object_handle = AllocObjectID(m_type, true, true, true);

  if (object_handle == -1) {
    OutrageMessageBox("Cannot add object: There are no free object slots.");
    return;
  }

  strcpy(Object_info[object_handle].name, cur_name);

  Object_info[object_handle].render_handle = img_handle;

  // figure out size of object
  ComputeDefaultSize(Object_info[object_handle].type, img_handle, &Object_info[object_handle].size);

  // Init some stuff
  Object_info[object_handle].flags = OIF_DESTROYABLE;
  Object_info[object_handle].hit_points = 100;
  memset(&Object_info[object_handle].lighting_info, 0, sizeof(light_info));
  Object_info[object_handle].lighting_info.timebits = 0xFFFFFFFF;
  if (m_type == OBJ_BUILDING)
    Object_info[object_handle].lighting_info.lighting_render_type = LRT_LIGHTMAPS;
  else
    Object_info[object_handle].lighting_info.lighting_render_type = LRT_GOURAUD;

  // Finally, save a local copy of the model/anim and alloc a tracklock
  mprintf(0, "Making a copy of this model locally...\n");

  std::filesystem::path destname = LocalModelsDir / Poly_models[Object_info[object_handle].render_handle].name;
  cf_CopyFile(destname, filename);

  mng_AllocTrackLock(cur_name, PAGETYPE_GENERIC);

  m_current = object_handle;

  RemapStaticIDs();

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericCheckedOut() {
  char str[10000];
  int total = 0;

  mng_DisplayLockList(TableUser);

  sprintf(str, "User %s has these objects held locally:\n\n", TableUser);
  for (int i = 0; i < MAX_TRACKLOCKS; i++) {

    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_GENERIC) {

      int n = FindObjectIDName(GlobalTrackLocks[i].name);

      ASSERT(n != -1);

      if (Object_info[n].type == m_type) { // found one of our type
        strcat(str, "   ");
        strcat(str, GlobalTrackLocks[i].name);
        strcat(str, "\n");
        total++;
      }
    }
  }

  if (total != 0) // Display list
    MessageBox(str, "Textures", MB_OK);
}

void CWorldObjectsGenericDialog::OnGenericCheckIn() {
  mngs_Pagelock temp_pl;
  int r;

  if (m_current == -1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure we own this object
  strcpy(temp_pl.name, Object_info[m_current].name);
  temp_pl.pagetype = PAGETYPE_GENERIC;

  r = mng_CheckIfPageOwned(&temp_pl, TableUser);
  if (r < 0)
    OutrageMessageBox(ErrorString);
  else if (r == 0)
    OutrageMessageBox(InfoString);
  else {
    // Change the pagelock state to UNLOCKED
    strcpy(temp_pl.holder, "UNLOCKED");
    if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
      MessageBox(ErrorString, "Error!");
      mng_EraseLocker();
      return;
    } else {
      // Now actually replace the copy on the net with our local one

      if (!mng_ReplacePage(Object_info[m_current].name, Object_info[m_current].name, m_current, PAGETYPE_GENERIC, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this object anim/model to the network for all

        std::filesystem::path srcname = LocalModelsDir / Poly_models[Object_info[m_current].render_handle].name;
        std::filesystem::path destname = NetModelsDir / Poly_models[Object_info[m_current].render_handle].name;
        cf_CopyFile(destname, srcname);

        if (Object_info[m_current].med_render_handle != -1) {
          srcname = LocalModelsDir / Poly_models[Object_info[m_current].med_render_handle].name;
          destname = NetModelsDir / Poly_models[Object_info[m_current].med_render_handle].name;
          cf_CopyFile(destname, srcname);
        }

        if (Object_info[m_current].lo_render_handle != -1) {
          srcname = LocalModelsDir / Poly_models[Object_info[m_current].lo_render_handle].name;
          destname = NetModelsDir / Poly_models[Object_info[m_current].lo_render_handle].name;
          cf_CopyFile(destname, srcname);
        }

        OutrageMessageBox("Object checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Object_info[m_current].name, PAGETYPE_GENERIC, 1);

        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Object_info[m_current].name, PAGETYPE_GENERIC);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericDefineAnimStates() {
  if (m_current == -1)
    return;

  CAnimStatesDialog dlg(Object_info[m_current].render_handle, Object_info[m_current].anim);

  if (dlg.DoModal() == IDOK) // Copy back into object
    dlg.GetAnimData(Object_info[m_current].anim);
}

void CWorldObjectsGenericDialog::OnGenericDelete() {
  int answer, tl;
  mngs_Pagelock pl;
  int old_current;

  if (m_current == -1)
    return;

  // Check to see if we even have it locked
  if ((tl = mng_FindTrackLock(Object_info[m_current].name, PAGETYPE_GENERIC)) == -1) {
    OutrageMessageBox("This object is not yours to delete.  Lock first.");
    return;
  }

  // Make sure its to be deleted
  answer = MessageBox("Are you sure you want to delete this object?", Object_info[m_current].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Object_info[m_current].name);
  pl.pagetype = PAGETYPE_GENERIC;

  // Check to see if this is a local object only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(Object_info[m_current].name, PAGETYPE_GENERIC, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else // if its network, delete it from both the net and local drives
  {

    mng_FreeTrackLock(tl);
    mng_DeletePage(Object_info[m_current].name, PAGETYPE_GENERIC, 0);
    mng_DeletePage(Object_info[m_current].name, PAGETYPE_GENERIC, 1);

    mng_DeletePagelock(Object_info[m_current].name, PAGETYPE_GENERIC);
  }

  // Advance to the next object
  old_current = m_current;
  m_current = GetNextObjectID(m_current);
  if (m_current == old_current)
    m_current = -1;

  FreePolyModel(Object_info[old_current].render_handle);

  if (Object_info[old_current].med_render_handle != -1)
    FreePolyModel(Object_info[old_current].med_render_handle);
  if (Object_info[old_current].lo_render_handle != -1)
    FreePolyModel(Object_info[old_current].lo_render_handle);

  FreeObjectID(old_current);
  mng_EraseLocker();

  OutrageMessageBox("Object deleted.");

  RemapStaticIDs();

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericLock() {
  mngs_Pagelock temp_pl;
  mngs_generic_page page;
  int r;

  if (m_current == -1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, Object_info[m_current].name);
  temp_pl.pagetype = PAGETYPE_GENERIC;

  r = mng_CheckIfPageLocked(&temp_pl);
  if (r == 2) {
    int answer;
    answer = OutrageMessageBox(MBOX_YESNO, "This page is not even in the table file, or the database maybe corrupt.  "
                                           "Override to 'Unlocked'? (Select NO if you don't know what you're doing)");
    if (answer == IDYES) {
      strcpy(temp_pl.holder, "UNLOCKED");
      if (!mng_ReplacePagelock(temp_pl.name, &temp_pl))
        MessageBox(ErrorString, "Error!");
    }
  } else if (r < 0)
    OutrageMessageBox(ErrorString);
  else if (r == 1)
    OutrageMessageBox(InfoString);
  else {
    // Everything is ok.  Tell the network we're locking it and get a copy to
    // our local drive

    strcpy(temp_pl.holder, TableUser);
    if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
      MessageBox(ErrorString, "Error!");
      mng_EraseLocker();
      return;
    } else {
      // Search thru the net pagefile and get a new copy in RAM in case anyone
      // changed it since we started the editor
      if (mng_FindSpecificGenericPage(temp_pl.name, &page)) {
        if (mng_AssignGenericPageToObjInfo(&page, m_current)) {
          if (!mng_ReplacePage(Object_info[m_current].name, Object_info[m_current].name, m_current, PAGETYPE_GENERIC,
                               1)) {
            OutrageMessageBox("There was problem writing that page locally!");
            mng_EraseLocker();
            return;
          }
          OutrageMessageBox("Object locked.");
        } else
          OutrageMessageBox(
              "There was a problem loading this object.  You might encounter problems in dealing with it.  Good luck!");

        mng_AllocTrackLock(Object_info[m_current].name, PAGETYPE_GENERIC);
        UpdateDialog();
      } else
        OutrageMessageBox("Couldn't find that object in the table file!");
    }
  }
  mng_EraseLocker();
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericNext() {
  m_current = GetNextObjectID(m_current);
  m_lod = 0;

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericPrev() {
  m_current = GetPrevObjectID(m_current);
  m_lod = 0;

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericChangeModel() {
  char filename[255];
  char curname[255];
  char fname[255];
  char dir[255];
  char ext[100];
  int img_handle;
  int c = 1, finding_name = 1;
  int model = 0;

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_model_dir, sizeof(Current_model_dir)))
    return;

  ChangePolyModelName(filename, curname);

  ddio_SplitPath(filename, dir, fname, ext);

  if ((FindPolyModelName(curname)) != -1) {

    int answer = MessageBox("There is already a model in memory with this name.  Are you sure you want to replace it?",
                            fname, MB_YESNO);
    if (answer == IDNO)
      return;
  }

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadPolyModel(filename, 0);

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that animation/model file.");
    return;
  }

  if (m_lod == 0) {
    ChangeOldModelsForObjects(Object_info[m_current].render_handle, img_handle);
    FreePolyModel(Object_info[m_current].render_handle);
    Object_info[m_current].render_handle = img_handle;
  } else if (m_lod == 1) {
    if (Object_info[m_current].med_render_handle != -1)
      FreePolyModel(Object_info[m_current].med_render_handle);

    Object_info[m_current].med_render_handle = img_handle;
  } else {
    if (Object_info[m_current].lo_render_handle != -1)
      FreePolyModel(Object_info[m_current].lo_render_handle);

    Object_info[m_current].lo_render_handle = img_handle;
  }

  // A new model might induce a new weapon stucture
  if (OutrageMessageBox(MBOX_YESNO, "Would you like to clear the weapon battery info?") == IDYES) {
    WBClearInfo(Object_info[m_current].static_wb);
  }
  // Finally, save a local copy of the model

  sprintf(curname, "%s\\%s", LocalModelsDir.u8string().c_str(), Poly_models[img_handle].name);
  cf_CopyFile(curname, filename);

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericChangeName() {
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this ship locked, if not reset name and bail
  int p = mng_FindTrackLock(Object_info[m_current].name, PAGETYPE_GENERIC);
  if (p == -1) {
    OutrageMessageBox("You must lock this object if you wish to change its name.");
    return;
  }

// Get new name
retry_name:
  strcpy(name, Object_info[m_current].name);
  if (!InputObjectName(name, sizeof(name), "Object name", "Enter a new name for this object:", this))
    return;

  if (FindObjectIDName(name) != -1) {
    OutrageMessageBox("That name is taken, please choose another.");
    goto retry_name;
  }

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Object_info[m_current].name);
  pl.pagetype = PAGETYPE_GENERIC;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Object_info[m_current].name, name, PAGETYPE_GENERIC);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Object_info[m_current].name);
    strcpy(Object_info[m_current].name, name);

    mng_ReplacePage(oldname, Object_info[m_current].name, m_current, PAGETYPE_GENERIC, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Object_info[m_current].name, name);
  mng_EraseLocker();

  RemapStaticIDs();

  // check to see if current has been remapped
  if (Object_info[m_current].type != m_type)
    m_current = GetObjectID(m_type);

  UpdateDialog();
}

#define NUM_ANIM_FRAMES 30

void CWorldObjectsGenericDialog::UpdateObjectView(void) {
  CWnd *objwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  static int frame = 0, spin_frame = 0;
  static int last_object = -1;
  static int last_render_handle = -1;
  static int object_dir = 0;

  if (m_current == -1)
    return;

  if (object_dir == 0) {
    frame++;
    if (frame == NUM_ANIM_FRAMES) {
      frame = NUM_ANIM_FRAMES - 1;
      object_dir = 1;
    }
  } else {
    frame--;
    if (frame == -1) {
      frame = 0;
      object_dir = 0;
    }
  }

  objwnd = GetDlgItem(IDC_GENERIC_OBJECTVIEW);
  objwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  int render_handle;

  if (m_lod == 0)
    render_handle = Object_info[m_current].render_handle;
  else if (m_lod == 1)
    render_handle = Object_info[m_current].med_render_handle;
  else
    render_handle = Object_info[m_current].lo_render_handle;

  if (last_object != m_current || last_render_handle != render_handle) {
    Desktop_surf->clear(rect.left, rect.top, w, h);
    last_object = m_current;
    last_render_handle = render_handle;
  }

  bm_handle = render_handle;

  if (bm_handle == -1)
    return;

  vector zero_vector;
  vector view_vector = {0, 0, -20};
  matrix id_matrix, rot_matrix;
  poly_model *pm = GetPolymodelPointer(bm_handle);

  vm_MakeZero(&zero_vector);
  vm_MakeIdentity(&id_matrix);

  float norm_angles[256];

  float keyframe = pm->frame_min + (pm->frame_max - pm->frame_min) * ((float)frame / (float)NUM_ANIM_FRAMES);

  SetNormalizedTimeAnim(keyframe, norm_angles, pm);

  spin_frame++;

  vm_AnglesToMatrix(&rot_matrix, 0, spin_frame * 400, 0);
  view_vector.z = -(fabs(pm->maxs.z - pm->mins.z) * 2);

  m_ObjectSurf.create(128, 128, BPP_16);
  grViewport *vport = new grViewport(&m_ObjectSurf);
  StartEditorFrame(vport, &view_vector, &id_matrix, D3_DEFAULT_ZOOM);
  DrawPolygonModel(&zero_vector, &rot_matrix, bm_handle, norm_angles, 0, 1.0, 1.0, 1.0);
  EndEditorFrame();

  x = rect.left + ((rect.right - rect.left) / 2) - m_ObjectSurf.width() / 2;
  y = rect.top + ((rect.bottom - rect.top) / 2) - m_ObjectSurf.height() / 2;
  Desktop_surf->blt(x, y, &m_ObjectSurf);

  delete vport;
  m_ObjectSurf.free();
}

void CWorldObjectsGenericDialog::OnTimer(UINT nIDEvent) {
  UpdateObjectView();

  CDialog::OnTimer(nIDEvent);
}

void CWorldObjectsGenericDialog::OnSelendokGenericNamePulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_GENERIC_NAME_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_GENERIC_NAME_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindObjectIDName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted object list, but probably nothing.");
  } else {
    ASSERT(Object_info[i].type == m_type);
    m_current = i;
  }

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusGenericSizeEdit() {
  char str[20];

  ((CEdit *)GetDlgItem(IDC_GENERIC_SIZE_EDIT))->GetWindowText(str, 20);

  Object_info[m_current].size = atof(str);
}

void CWorldObjectsGenericDialog::OnKillfocusGenericScriptIDEdit() {
  /*
  char str[20];

  ((CEdit *) GetDlgItem(IDC_GENERIC_SCRIPT_ID_EDIT))->GetWindowText(str,20);

  strcpy(Object_info[m_current].script_name, str);
  */
}

void CWorldObjectsGenericDialog::OnGenericCopy() {
  if (m_current != -1) {
    if (Copy_object.description) {
      mem_free(Copy_object.description);
    }

    Copy_object = Object_info[m_current];

    Copy_object.description = NULL;

    if (!Object_info[m_current].description)
      Copy_object.description = mem_strdup("<no description>");
    else
      Copy_object.description = mem_strdup(Object_info[m_current].description);
  }

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericPaste() {
  char temp_name[PAGENAME_LEN + 10]; // need to add some space for the "CopyxOf"
  int n;

  ASSERT(Network_up);

  ASSERT(Copy_object.type != OBJ_NONE);

  if (Copy_object.type != m_type) {
    if (OutrageMessageBox(MBOX_YESNO, "You are about to paste a %s object as a %s.  Is this OK?",
                          Object_type_names[Copy_object.type], Object_type_names[m_type]) != IDYES)
      return;
  }

  // Get the name of the new object
  strcpy(temp_name, Copy_object.name);
  if (FindObjectIDName(temp_name) != -1) {
    int c = 2;
    sprintf(temp_name, "CopyOf%s", Copy_object.name);
    do { // Make sure the name not already in use
      if (FindObjectIDName(temp_name) == -1)
        break;
      sprintf(temp_name, "Copy%dOf%s", c, Copy_object.name);
      c++;
    } while (1);
  }

  if (!InputObjectName(temp_name, sizeof(temp_name), "Object name", "Enter a name for your object:", this)) // bail
    return;

  // Get a slot for this object
  n = AllocObjectID(m_type, true, true, true);

  if (n == -1) {
    OutrageMessageBox("Cannot paste object: There are no free object slots.");
    return;
  }

  // Copy into new slot
  Object_info[n] = Copy_object;

  Object_info[n].description = Copy_object.description;
  Copy_object.description = NULL;

  // Set type and name
  Object_info[n].type = m_type;
  strcpy(Object_info[n].name, temp_name);

  // Increment the used count of the polymodels
  Poly_models[Object_info[m_current].render_handle].used++;
  if (Object_info[m_current].med_render_handle != -1)
    Poly_models[Object_info[m_current].med_render_handle].used++;
  if (Object_info[m_current].lo_render_handle != -1)
    Poly_models[Object_info[m_current].lo_render_handle].used++;

  // Make this the current item
  m_current = n;

  // Add this to paging system
  mng_AllocTrackLock(Object_info[n].name, PAGETYPE_GENERIC);

  // I'm not sure if this belongs here
  RemapStaticIDs();

  UpdateDialog();
}

// When closing, save all our checked out objects locally so we know
// what stuff to flag as "checked out" the next time we start up
void CWorldObjectsGenericDialog::SaveGenericsOnClose() {
  int i, t;

  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_GENERIC) {
      t = FindObjectIDName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);

      mng_ReplacePage(Object_info[t].name, Object_info[t].name, t, PAGETYPE_GENERIC, 1);
    }
  }
}

void CWorldObjectsGenericDialog::OnDestroy() {
  CDialog::OnDestroy();

  if (Copy_object.description) {
    mem_free(Copy_object.description);
    Copy_object.description = NULL;
  }

  SaveGenericsOnClose();

  ObjReInitAll();
}

BOOL CWorldObjectsGenericDialog::DestroyWindow() { return CDialog::DestroyWindow(); }

void CWorldObjectsGenericDialog::OnGenericUndoLock() {
  int tl;
  mngs_Pagelock pl;
  mngs_generic_page page;

  if (m_current == -1)
    return;

  // Should have this item locked
  if ((tl = mng_FindTrackLock(Object_info[m_current].name, PAGETYPE_GENERIC)) == -1)
    return;

  // Make sure its to be deleted
  if (OutrageMessageBox(MBOX_YESNO,
                        "Are you sure you want to undo your lock and lose any changes you may have made?") != IDYES)
    return;

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Object_info[m_current].name);
  pl.pagetype = PAGETYPE_GENERIC;

  mng_FreeTrackLock(tl);

  // Delete local page
  if (!mng_DeletePage(Object_info[m_current].name, PAGETYPE_GENERIC, 1)) {
    mprintf(0, ErrorString);
    Int3();
  }

  // Get old data from net
  if (!mng_FindSpecificGenericPage(pl.name, &page))
    Int3();

  // Copy old get into our local array
  if (!mng_AssignGenericPageToObjInfo(&page, m_current))
    Int3();

  // We're done
  mng_EraseLocker();

  // Update the display
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericDestroyable() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_DESTROYABLE);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_DESTROYABLE;
  else
    Object_info[m_current].flags &= ~OIF_DESTROYABLE;

  ((CButton *)GetDlgItem(IDC_GENERIC_HITPOINT_EDIT))->EnableWindow(Object_info[m_current].flags & OIF_DESTROYABLE);
  ((CButton *)GetDlgItem(IDC_GENERIC_SCORE_EDIT))->EnableWindow(Object_info[m_current].flags & OIF_DESTROYABLE);
}

void CWorldObjectsGenericDialog::OnKillfocusGenericHitpointEdit() {
  char str[20];

  ((CEdit *)GetDlgItem(IDC_GENERIC_HITPOINT_EDIT))->GetWindowText(str, 20);

  Object_info[m_current].hit_points = atoi(str);
}

void CWorldObjectsGenericDialog::OnGenericWeaponInfoButton() {
  RobotEditWeaponsDialog dlg(Object_info[m_current].static_wb,
                             GetPolymodelPointer(Object_info[m_current].render_handle));

  if (dlg.DoModal() == IDOK)
    dlg.GetData();
}

void CWorldObjectsGenericDialog::OnGenericLightButton() {
  if (m_current == -1)
    return;

  CGenericLightDialog dlg(&Object_info[m_current].lighting_info);
  dlg.DoModal();

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnDefaultRadiusButton() {
  ComputeDefaultSize(Object_info[m_current].type, Object_info[m_current].render_handle, &Object_info[m_current].size);

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnSelScript() {
  CString filter = "D3 Compiled Scripts (*.dll)|*.dll||";

  char filename[_MAX_PATH];
  char pathname[_MAX_PATH], name[_MAX_PATH];
  strcpy(pathname, LocalScriptDir);

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, pathname, sizeof(pathname)))
    return;

  ddio_SplitPath(filename, NULL, name, NULL);
  sprintf(filename, "%s.dll", name);

  strcpy(Object_info[m_current].module_name, filename);

  UpdateDialog();

  /*
  // TODO: Add your control notification handler code here
  CScriptSelect dlg(REF_OBJTYPE);

  if (dlg.DoModal() == IDOK) {
          strcpy(Object_info[m_current].script_name, (LPCSTR)dlg.m_ScriptName);
          UpdateDialog();
  }
  */
}

void CWorldObjectsGenericDialog::OnGenericConcussiveCheck() {
  // TODO: Add your control notification handler code here
}

void CWorldObjectsGenericDialog::OnKillfocusGenericImpactDamageEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_IMPACT_DAMAGE_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].damage = atof(str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusGenericImpactSizeEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_IMPACT_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].impact_size = atof(str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnNolod() {
  // TODO: Add your control notification handler code here
  if (m_lod == 0) {
    MessageBox("You must have a hi-res model.");
    return;
  }

  else if (m_lod == 1) {
    FreePolyModel(Object_info[m_current].med_render_handle);
    Object_info[m_current].med_render_handle = -1;

  } else {
    FreePolyModel(Object_info[m_current].lo_render_handle);
    Object_info[m_current].lo_render_handle = -1;
  }

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnHiresRadio() {
  m_lod = 0;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnMedresRadio() {
  m_lod = 1;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnLoresRadio() {
  m_lod = 2;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusGenericImpactTimeEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_IMPACT_TIME_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].impact_time = atof(str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnSelendokGenericExplosionSoundCombo() {
  Object_info[m_current].sounds[GSI_EXPLODE] = m_explosion_sound_combo.GetSelected();
}

void CWorldObjectsGenericDialog::OnSelendokGenericAmbientSoundCombo() {

  Object_info[m_current].sounds[GSI_AMBIENT] = m_ambient_sound_combo.GetSelected();
}

void CWorldObjectsGenericDialog::OnKillfocusGenericInvenDescription() {
  CEdit *ebox;
  char str[255];

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_INVEN_DESCRIPTION);
  ebox->GetWindowText(str, 180);

  if (Object_info[m_current].description) {
    mem_free(Object_info[m_current].description);
    Object_info[m_current].description = NULL;
  }

  if ((strlen(str) > 0) && (strcmp(str, "<no description>"))) {
    Object_info[m_current].description = mem_strdup(str);
  } else {
    ebox->SetWindowText("<no description>");
  }

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusGenericInvenIconname() {
  CEdit *ebox;
  char str[255];

  ebox = (CEdit *)GetDlgItem(IDC_GENERIC_INVEN_ICONNAME);
  ebox->GetWindowText(str, 180);

  strcpy(Object_info[m_current].icon_name, str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnOverride() {
  int n = m_current;
  mngs_Pagelock temp_pl;

  strcpy(temp_pl.name, Object_info[n].name);
  temp_pl.pagetype = PAGETYPE_GENERIC;

  mng_OverrideToUnlocked(&temp_pl);
}

void CWorldObjectsGenericDialog::OnGenericInvenSelectable() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_INVEN_SELECTABLE);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_INVEN_SELECTABLE;
  else
    Object_info[m_current].flags &= ~OIF_INVEN_SELECTABLE;
}

void CWorldObjectsGenericDialog::OnGenericInvenNonuseable() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_INVEN_NONUSEABLE);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_INVEN_NONUSEABLE;
  else
    Object_info[m_current].flags &= ~OIF_INVEN_NONUSEABLE;
}

void CWorldObjectsGenericDialog::OnKillfocusLodDistanceEdit() {
  CEdit *ebox;
  char str[255];
  float dist;

  ebox = (CEdit *)GetDlgItem(IDC_LOD_DISTANCE_EDIT);
  ebox->GetWindowText(str, 180);
  dist = atof(str);

  if (dist < 0)
    return;

  if (m_lod == 1) {
    Object_info[m_current].med_lod_distance = dist;
  } else if (m_lod == 2) {
    Object_info[m_current].lo_lod_distance = dist;
  }

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnInvtypeGame() {
  Object_info[m_current].flags &= ~OIF_INVEN_TYPE_MISSION;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnInvtypeMission() {
  Object_info[m_current].flags |= OIF_INVEN_TYPE_MISSION;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnInvenNoremove() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_INVEN_NOREMOVE);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_INVEN_NOREMOVE;
  else
    Object_info[m_current].flags &= ~OIF_INVEN_NOREMOVE;
}

void CWorldObjectsGenericDialog::OnInvenViswhenused() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_INVEN_VISWHENUSED);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_INVEN_VISWHENUSED;
  else
    Object_info[m_current].flags &= ~OIF_INVEN_VISWHENUSED;
}

void CWorldObjectsGenericDialog::OnSelendokDeathPowerup1Pulldown() {
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_DEATH_POWERUP1_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Object_info[m_current].dspew[0] = FindObjectIDName(name);

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusDeathPowerup1NumEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP1_NUM_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].dspew_number[0] = atoi(str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusDeathPowerup1PercentEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP1_PERCENT_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].dspew_percent[0] = atof(str) / 100.0f;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusDeathPowerup2NumEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP2_NUM_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].dspew_number[1] = atoi(str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnKillfocusDeathPowerup2PercentEdit() {
  CEdit *ebox;
  char str[20];

  ebox = (CEdit *)GetDlgItem(IDC_DEATH_POWERUP2_PERCENT_EDIT);
  ebox->GetWindowText(str, 20);

  Object_info[m_current].dspew_percent[1] = atof(str) / 100.0f;
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnSelendokDeathPowerup2Pulldown() {
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_DEATH_POWERUP2_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Object_info[m_current].dspew[1] = FindObjectIDName(name);

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnDeathPowerupUse2IfHave1Check() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_DEATH_POWERUP_USE2_IF_HAVE1_CHECK);

  if (btn->GetCheck())
    Object_info[m_current].f_dspew |= DSF_ONLY_IF_PLAYER_HAS_OBJ_1;
  else
    Object_info[m_current].f_dspew &= ~DSF_ONLY_IF_PLAYER_HAS_OBJ_1;

  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericDeathSpew2IfZero1() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_DEATH_SPEW_2_IF_ZERO_1);

  if (btn->GetCheck())
    Object_info[m_current].f_dspew |= DSF_ONLY_IF_NO_1;
  else
    Object_info[m_current].f_dspew &= ~DSF_ONLY_IF_NO_1;

  UpdateDialog();
}
int CWorldObjectsGenericDialog::GetTextureUsageForPolymodel(int modelnum) {
  poly_model *pm = &Poly_models[modelnum];
  int total = 0;
  uint8_t already_used[100];

  memset(already_used, 0, 100);

  ASSERT(pm && pm->used != 0);

  for (int i = 0; i < pm->n_models; i++) {
    bsp_info *sm = &pm->submodel[i];

    for (int t = 0; t < sm->num_faces; t++) {
      polyface *fp = &sm->faces[t];

      if (fp->texnum != -1 && !already_used[fp->texnum]) {
        already_used[fp->texnum] = 1;

        int texnum = pm->textures[fp->texnum];

        texture *texp = &GameTextures[texnum];

        if (texnum == 0)
          continue; // don't count error texture

        if (texp->used) {
          if (texp->flags & TF_ANIMATED) {
            vclip *vc = &GameVClips[texp->bm_handle];
            for (int j = 0; j < vc->num_frames; j++) {
              int bm_handle = vc->frames[j];
              int mem_this_tex = bm_w(bm_handle, 0) * bm_h(bm_handle, 0);
              if (bm_mipped(bm_handle))
                mem_this_tex += (mem_this_tex / 3);

              mem_this_tex *= 2;

              total += mem_this_tex;
            }
          } else {
            int mem_this_tex = bm_w(texp->bm_handle, 0) * bm_h(texp->bm_handle, 0);
            if (bm_mipped(texp->bm_handle))
              mem_this_tex += (mem_this_tex / 3);

            mem_this_tex *= 2;

            total += mem_this_tex;
          }
        }
      }
    }
  }

  return total;
}

void CWorldObjectsGenericDialog::OnKillfocusScriptname() {
  char str[MAX_MODULENAME_LEN];

  ((CEdit *)GetDlgItem(IDC_SCRIPTNAME))->GetWindowText(str, MAX_MODULENAME_LEN);

  if (!strcmp(str, "null")) {
    Object_info[m_current].module_name[0] = '\0';
    UpdateDialog();
    return;
  }

  strcpy(Object_info[m_current].module_name, str);
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnCompilemodule() {
  CQuickCompile dlg(Object_info[m_current].module_name);
  dlg.DoModal();

  switch (dlg.ret_value) {
  case -1: // does not exist
    break;
  case 0: // failed compile
    break;
  case 1: // success
    break;
  };
}

void CWorldObjectsGenericDialog::OnKillfocusScriptOverride() {
  char str[PAGENAME_LEN];

  ((CEdit *)GetDlgItem(IDC_SCRIPT_OVERRIDE))->GetWindowText(str, PAGENAME_LEN);

  if (!strcmp(str, "null")) {
    Object_info[m_current].script_name_override[0] = '\0';
    UpdateDialog();
    return;
  }

  strncpy(Object_info[m_current].script_name_override, str, PAGENAME_LEN - 1);
  Object_info[m_current].script_name_override[PAGENAME_LEN - 1] = '\0';
  UpdateDialog();
}

void CWorldObjectsGenericDialog::OnGenericAiScriptedDeath() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_AI_SCRIPTED_DEATH);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_AI_SCRIPTED_DEATH;
  else
    Object_info[m_current].flags &= ~OIF_AI_SCRIPTED_DEATH;
}

void CWorldObjectsGenericDialog::OnKillfocusRespawnScalarEdit() {
  CEdit *ebox;
  char str[20];
  float val;

  ebox = (CEdit *)GetDlgItem(IDC_RESPAWN_SCALAR_EDIT);
  ebox->GetWindowText(str, 20);

  val = atof(str);

  if (val < -1)
    val = -1;
  if (val > 10000)
    val = 10000;

  Object_info[m_current].respawn_scalar = val;
  UpdateDialog();
}

#include "GenericDeathDialog.h"

void CWorldObjectsGenericDialog::OnGenericDeaths() {
  CGenericDeathDialog dlg(&Object_info[m_current]);

  dlg.DoModal();
}

void CWorldObjectsGenericDialog::OnKillfocusGenericScoreEdit() {
  char str[20];

  ((CEdit *)GetDlgItem(IDC_GENERIC_SCORE_EDIT))->GetWindowText(str, 20);

  Object_info[m_current].score = atoi(str);
}

void CWorldObjectsGenericDialog::OnKillfocusGenericAmmoEdit() {
  char str[20];

  ((CEdit *)GetDlgItem(IDC_GENERIC_AMMO_EDIT))->GetWindowText(str, 20);

  Object_info[m_current].ammo_count = atoi(str);
}

void CWorldObjectsGenericDialog::OnObjCeilingCheck() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_OBJ_CEILING_CHECK);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_DO_CEILING_CHECK;
  else
    Object_info[m_current].flags &= ~OIF_DO_CEILING_CHECK;
}

void CWorldObjectsGenericDialog::OnObjectFlyThroughRenderedPortals() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_OBJECT_FLY_THROUGH_RENDERED_PORTALS);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_IGNORE_FORCEFIELDS_AND_GLASS;
  else
    Object_info[m_current].flags &= ~OIF_IGNORE_FORCEFIELDS_AND_GLASS;
}

void CWorldObjectsGenericDialog::OnNscButton() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_NSC_BUTTON);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_NO_DIFF_SCALE_DAMAGE;
  else
    Object_info[m_current].flags &= ~OIF_NO_DIFF_SCALE_DAMAGE;
}

void CWorldObjectsGenericDialog::OnDsmpbdCheck() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_DSMPBD_CHECK);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_NO_DIFF_SCALE_MOVE;
  else
    Object_info[m_current].flags &= ~OIF_NO_DIFF_SCALE_MOVE;
}

void CWorldObjectsGenericDialog::OnGenericAmbient() {
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_GENERIC_AMBIENT);

  if (btn->GetCheck())
    Object_info[m_current].flags |= OIF_AMBIENT_OBJECT;
  else
    Object_info[m_current].flags &= ~OIF_AMBIENT_OBJECT;
}
