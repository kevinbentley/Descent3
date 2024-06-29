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

 * $Logfile: /DescentIII/Main/editor/AnimStatesDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:37 $
 * $Author: kevinb $
 *
 * AnimStatesDialog.cpp : implementation file
 *
 * $Log: not supported by cvs2svn $
 *
 * 17    10/22/99 6:04p Jeff
 * fixed bugs and compiler errors resulting from mac code merge
 *
 * 16    9/21/99 5:06p Chris
 * Faster animation dialog updates - an editor ONLY change
 *
 * 15    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 14    5/03/98 5:38p Chris
 * Added sounds to anim page
 *
 * 13    4/16/98 2:56p Chris
 * Added birth Animation
 *
 * 12    4/13/98 2:20p Chris
 * IDLe works (kindof)
 *
 * 11    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 10    2/16/98 2:49p Chris
 * Made the MAX_SUBOBJECTS determine the number of normalized_time values
 * to be processed.  No longer a 'literal' problem.
 *
 * 9     2/16/98 2:47a Chris
 * Massive improvements to the animation system and the AI
 *
 * 8     12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 7     12/17/97 3:17p Jason
 * fixed potential fabs/abs bug
 *
 * 6     10/05/97 5:30a Chris
 * Added more support for TIMED animations
 *
 * 5     9/08/97 11:51a Chris
 * Added support for entering seconds-per-cycle animation information
 *
 * 4     8/08/97 11:45a Matt
 * Made anim states dialog keep local copy of anim array.  The caller then
 * copies the data to his own array if the user exits from the dialog via
 * OK.
 *
 * 3     8/06/97 1:35p Matt
 * Changes for new generic object_info struct which replace robot-specific
 * structure
 *
 * 2     7/24/97 6:35p Matt
 * Created symbolic constant for default zoom, and used it every place
 * that specifies zoom
 *
 * $NoKeywords: $
 */

#include "mfc_compatibility.h"
#include "editor.h"
#include "AnimStatesDialog.h"
#include "polymodel.h"
#include "gr.h"
#include "soundpage.h"
#include "soundload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimStatesDialog dialog

CAnimStatesDialog::CAnimStatesDialog(int render_handle, anim_elem *anim_info, CWnd *pParent /*=NULL*/)
    : CDialog(CAnimStatesDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CAnimStatesDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

  m_render_handle = render_handle;

  for (int i = 0; i < NUM_MOVEMENT_CLASSES; i++)
    for (int j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
      // m_anim[i][j] = anim_info[i][j];
      m_anim[i].elem[j] = anim_info[i].elem[j];
    }

  m_setup_sound_dialogs = false;
}

void CAnimStatesDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAnimStatesDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimStatesDialog, CDialog)
//{{AFX_MSG_MAP(CAnimStatesDialog)
ON_BN_CLICKED(IDC_ALERT_CHECK, OnAlertCheck)
ON_BN_CLICKED(IDC_DEATH_CHECK, OnDeathCheck)
ON_BN_CLICKED(IDC_FLINCH_CHECK, OnFlinchCheck)
ON_BN_CLICKED(IDC_GOTO_FLYING_CHECK, OnGotoFlyingCheck)
ON_BN_CLICKED(IDC_GOTO_JUMPING_CHECK, OnGotoJumpingCheck)
ON_BN_CLICKED(IDC_GOTO_ROLLING_CHECK, OnGotoRollingCheck)
ON_BN_CLICKED(IDC_GOTO_STANDING_CHECK, OnGotoStandingCheck)
ON_BN_CLICKED(IDC_GOTO_WALKING_CHECK, OnGotoWalkingCheck)
ON_BN_CLICKED(IDC_IDLE_CHECK, OnIdleCheck)
ON_BN_CLICKED(IDC_MELEE1_CHECK, OnMelee1Check)
ON_BN_CLICKED(IDC_MELEE1_RECOIL_CHECK, OnMelee1RecoilCheck)
ON_BN_CLICKED(IDC_MELEE2_CHECK, OnMelee2Check)
ON_BN_CLICKED(IDC_MELEE2_RECOIL_CHECK, OnMelee2RecoilCheck)
ON_BN_CLICKED(IDC_MISSILE1_CHECK, OnMissile1Check)
ON_BN_CLICKED(IDC_MISSILE1_RECOIL_CHECK, OnMissile1RecoilCheck)
ON_BN_CLICKED(IDC_MISSILE2_CHECK, OnMissile2Check)
ON_BN_CLICKED(IDC_MISSILE2_RECOIL_CHECK, OnMissile2RecoilCheck)
ON_BN_CLICKED(IDC_QUIRK_CHECK, OnQuirkCheck)
ON_BN_CLICKED(IDC_SPECIAL1_CHECK, OnSpecial1Check)
ON_BN_CLICKED(IDC_SPECIAL2_CHECK, OnSpecial2Check)
ON_BN_CLICKED(IDC_SPECIAL3_CHECK, OnSpecial3Check)
ON_BN_CLICKED(IDC_SPECIAL4_CHECK, OnSpecial4Check)
ON_BN_CLICKED(IDC_SPECIAL5_CHECK, OnSpecial5Check)
ON_BN_CLICKED(IDC_TAUNT_CHECK, OnTauntCheck)
ON_CBN_SELENDOK(IDC_CURRENT_ANIMATION_PULLDOWN, OnSelendokCurrentAnimationPulldown)
ON_CBN_SELENDOK(IDC_CURRENT_STATE_PULLDOWN, OnSelendokCurrentStatePulldown)
ON_WM_TIMER()
ON_EN_KILLFOCUS(IDC_ALERT_FROM_EDIT, OnKillfocusAlertFromEdit)
ON_EN_KILLFOCUS(IDC_ALERT_TO_EDIT, OnKillfocusAlertToEdit)
ON_EN_KILLFOCUS(IDC_DEATH_FROM_EDIT, OnKillfocusDeathFromEdit)
ON_EN_KILLFOCUS(IDC_DEATH_TO_EDIT, OnKillfocusDeathToEdit)
ON_EN_KILLFOCUS(IDC_FLINCH_FROM_EDIT, OnKillfocusFlinchFromEdit)
ON_EN_KILLFOCUS(IDC_FLINCH_TO_EDIT, OnKillfocusFlinchToEdit)
ON_EN_KILLFOCUS(IDC_FLYING_FROM_EDIT, OnKillfocusFlyingFromEdit)
ON_EN_KILLFOCUS(IDC_FLYING_TO_EDIT, OnKillfocusFlyingToEdit)
ON_EN_KILLFOCUS(IDC_IDLE_FROM_EDIT, OnKillfocusIdleFromEdit)
ON_EN_KILLFOCUS(IDC_IDLE_TO_EDIT, OnKillfocusIdleToEdit)
ON_EN_KILLFOCUS(IDC_JUMPING_FROM_EDIT, OnKillfocusJumpingFromEdit)
ON_EN_KILLFOCUS(IDC_JUMPING_TO_EDIT, OnKillfocusJumpingToEdit)
ON_EN_KILLFOCUS(IDC_MELEE1_FROM_EDIT, OnKillfocusMelee1FromEdit)
ON_EN_KILLFOCUS(IDC_MELEE1_TO_EDIT, OnKillfocusMelee1ToEdit)
ON_EN_KILLFOCUS(IDC_MELEE2_FROM_EDIT, OnKillfocusMelee2FromEdit)
ON_EN_KILLFOCUS(IDC_MISSILE1_FROM_EDIT, OnKillfocusMissile1FromEdit)
ON_EN_KILLFOCUS(IDC_MISSILE1_TO_EDIT, OnKillfocusMissile1ToEdit)
ON_EN_KILLFOCUS(IDC_MISSILE2_FROM_EDIT, OnKillfocusMissile2FromEdit)
ON_EN_KILLFOCUS(IDC_MISSILE2_TO_EDIT, OnKillfocusMissile2ToEdit)
ON_EN_KILLFOCUS(IDC_MRECOIL1_TO_EDIT, OnKillfocusMrecoil1ToEdit)
ON_EN_KILLFOCUS(IDC_MRECOIL1_FROM_EDIT, OnKillfocusMrecoil1FromEdit)
ON_EN_KILLFOCUS(IDC_MRECOIL2_FROM_EDIT, OnKillfocusMrecoil2FromEdit)
ON_EN_KILLFOCUS(IDC_MRECOIL2_TO_EDIT, OnKillfocusMrecoil2ToEdit)
ON_EN_KILLFOCUS(IDC_QUIRK_FROM_EDIT, OnKillfocusQuirkFromEdit)
ON_EN_KILLFOCUS(IDC_QUIRK_TO_EDIT, OnKillfocusQuirkToEdit)
ON_EN_KILLFOCUS(IDC_RECOIL1_FROM_EDIT, OnKillfocusRecoil1FromEdit)
ON_EN_KILLFOCUS(IDC_RECOIL1_TO_EDIT, OnKillfocusRecoil1ToEdit)
ON_EN_KILLFOCUS(IDC_RECOIL2_FROM_EDIT, OnKillfocusRecoil2FromEdit)
ON_EN_KILLFOCUS(IDC_RECOIL2_TO_EDIT, OnKillfocusRecoil2ToEdit)
ON_EN_KILLFOCUS(IDC_ROLLING_FROM_EDIT, OnKillfocusRollingFromEdit)
ON_EN_KILLFOCUS(IDC_ROLLING_TO_EDIT, OnKillfocusRollingToEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL1_FROM_EDIT, OnKillfocusSpecial1FromEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL1_TO_EDIT, OnKillfocusSpecial1ToEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL2_FROM_EDIT, OnKillfocusSpecial2FromEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL2_TO_EDIT, OnKillfocusSpecial2ToEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL3_FROM_EDIT, OnKillfocusSpecial3FromEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL3_TO_EDIT, OnKillfocusSpecial3ToEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL4_FROM_EDIT, OnKillfocusSpecial4FromEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL4_TO_EDIT, OnKillfocusSpecial4ToEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL5_FROM_EDIT, OnKillfocusSpecial5FromEdit)
ON_EN_KILLFOCUS(IDC_SPECIAL5_TO_EDIT, OnKillfocusSpecial5ToEdit)
ON_EN_KILLFOCUS(IDC_STANDING_FROM_EDIT, OnKillfocusStandingFromEdit)
ON_EN_KILLFOCUS(IDC_STANDING_TO_EDIT, OnKillfocusStandingToEdit)
ON_EN_KILLFOCUS(IDC_TAUNT_FROM_EDIT, OnKillfocusTauntFromEdit)
ON_EN_KILLFOCUS(IDC_TAUNT_TO_EDIT, OnKillfocusTauntToEdit)
ON_EN_KILLFOCUS(IDC_WALKING_FROM_EDIT, OnKillfocusWalkingFromEdit)
ON_EN_KILLFOCUS(IDC_WALKING_TO_EDIT, OnKillfocusWalkingToEdit)
ON_EN_KILLFOCUS(IDC_MELEE2_TO_EDIT, OnKillfocusMelee2ToEdit)
ON_BN_CLICKED(IDC_RESET_ANIM_ZERO, OnResetAnimZero)
ON_BN_CLICKED(IDC_ROT_LEFT, OnRotLeft)
ON_BN_CLICKED(IDC_ROT_RIGHT, OnRotRight)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT1, OnKillfocusSecPerCycleEdit1)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT2, OnKillfocusSecPerCycleEdit2)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT3, OnKillfocusSecPerCycleEdit3)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT4, OnKillfocusSecPerCycleEdit4)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT5, OnKillfocusSecPerCycleEdit5)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT6, OnKillfocusSecPerCycleEdit6)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT7, OnKillfocusSecPerCycleEdit7)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT8, OnKillfocusSecPerCycleEdit8)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT9, OnKillfocusSecPerCycleEdit9)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT10, OnKillfocusSecPerCycleEdit10)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT11, OnKillfocusSecPerCycleEdit11)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT12, OnKillfocusSecPerCycleEdit12)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT13, OnKillfocusSecPerCycleEdit13)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT14, OnKillfocusSecPerCycleEdit14)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT15, OnKillfocusSecPerCycleEdit15)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT16, OnKillfocusSecPerCycleEdit16)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT17, OnKillfocusSecPerCycleEdit17)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT18, OnKillfocusSecPerCycleEdit18)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT19, OnKillfocusSecPerCycleEdit19)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT20, OnKillfocusSecPerCycleEdit20)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT21, OnKillfocusSecPerCycleEdit21)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT22, OnKillfocusSecPerCycleEdit22)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT23, OnKillfocusSecPerCycleEdit23)
ON_EN_KILLFOCUS(IDC_SEC_PER_CYCLE_EDIT24, OnKillfocusSecPerCycleEdit24)
ON_CBN_SELENDOK(IDC_ANIM_SOUND0_PULLDOWN, OnSelendokAnimSound0Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND1_PULLDOWN, OnSelendokAnimSound1Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND2_PULLDOWN, OnSelendokAnimSound2Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND10_PULLDOWN, OnSelendokAnimSound10Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND11_PULLDOWN, OnSelendokAnimSound11Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND12_PULLDOWN, OnSelendokAnimSound12Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND13_PULLDOWN, OnSelendokAnimSound13Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND14_PULLDOWN, OnSelendokAnimSound14Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND15_PULLDOWN, OnSelendokAnimSound15Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND16_PULLDOWN, OnSelendokAnimSound16Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND17_PULLDOWN, OnSelendokAnimSound17Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND18_PULLDOWN, OnSelendokAnimSound18Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND19_PULLDOWN, OnSelendokAnimSound19Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND20_PULLDOWN, OnSelendokAnimSound20Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND21_PULLDOWN, OnSelendokAnimSound21Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND22_PULLDOWN, OnSelendokAnimSound22Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND23_PULLDOWN, OnSelendokAnimSound23Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND3_PULLDOWN, OnSelendokAnimSound3Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND4_PULLDOWN, OnSelendokAnimSound4Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND5_PULLDOWN, OnSelendokAnimSound5Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND6_PULLDOWN, OnSelendokAnimSound6Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND7_PULLDOWN, OnSelendokAnimSound7Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND8_PULLDOWN, OnSelendokAnimSound8Pulldown)
ON_CBN_SELENDOK(IDC_ANIM_SOUND9_PULLDOWN, OnSelendokAnimSound9Pulldown)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimStatesDialog message handlers

void CAnimStatesDialog::OnAlertCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_ALERT].used = IsDlgButtonChecked(IDC_ALERT_CHECK);
}

void CAnimStatesDialog::OnDeathCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_DEATH].used = IsDlgButtonChecked(IDC_DEATH_CHECK);
}

void CAnimStatesDialog::OnFlinchCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_FLINCH].used = IsDlgButtonChecked(IDC_FLINCH_CHECK);
}

void CAnimStatesDialog::OnGotoFlyingCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_ALERT_FLYING].used = IsDlgButtonChecked(IDC_GOTO_FLYING_CHECK);
}

void CAnimStatesDialog::OnGotoJumpingCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_ALERT_JUMPING].used = IsDlgButtonChecked(IDC_GOTO_JUMPING_CHECK);
}

void CAnimStatesDialog::OnGotoRollingCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_ALERT_ROLLING].used = IsDlgButtonChecked(IDC_GOTO_ROLLING_CHECK);
}

void CAnimStatesDialog::OnGotoStandingCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_ALERT_STANDING].used = IsDlgButtonChecked(IDC_GOTO_STANDING_CHECK);
}

void CAnimStatesDialog::OnGotoWalkingCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_ALERT_WALKING].used = IsDlgButtonChecked(IDC_GOTO_WALKING_CHECK);
}

void CAnimStatesDialog::OnIdleCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_IDLE].used = IsDlgButtonChecked(IDC_IDLE_CHECK);
}

void CAnimStatesDialog::OnMelee1Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MELEE1].used = IsDlgButtonChecked(IDC_MELEE1_CHECK);
}

void CAnimStatesDialog::OnMelee1RecoilCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MELEE1_RECOIL].used = IsDlgButtonChecked(IDC_MELEE1_RECOIL_CHECK);
}

void CAnimStatesDialog::OnMelee2Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MELEE2].used = IsDlgButtonChecked(IDC_MELEE2_CHECK);
}

void CAnimStatesDialog::OnMelee2RecoilCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MELEE1_RECOIL].used = IsDlgButtonChecked(IDC_MELEE1_RECOIL_CHECK);
}

void CAnimStatesDialog::OnMissile1Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_BIRTH].used = IsDlgButtonChecked(IDC_MISSILE1_CHECK);
}

void CAnimStatesDialog::OnMissile1RecoilCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MISSILE1_RECOIL].used = IsDlgButtonChecked(IDC_MISSILE1_RECOIL_CHECK);
}

void CAnimStatesDialog::OnMissile2Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MISSILE2].used = IsDlgButtonChecked(IDC_MISSILE2_CHECK);
}

void CAnimStatesDialog::OnMissile2RecoilCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_MISSILE2_RECOIL].used = IsDlgButtonChecked(IDC_MISSILE2_RECOIL_CHECK);
}

void CAnimStatesDialog::OnQuirkCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_QUIRK].used = IsDlgButtonChecked(IDC_QUIRK_CHECK);
}

void CAnimStatesDialog::OnSpecial1Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_IDLE_STANDING].used = IsDlgButtonChecked(IDC_SPECIAL1_CHECK);
}

void CAnimStatesDialog::OnSpecial2Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_IDLE_FLYING].used = IsDlgButtonChecked(IDC_SPECIAL2_CHECK);
}

void CAnimStatesDialog::OnSpecial3Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_IDLE_ROLLING].used = IsDlgButtonChecked(IDC_SPECIAL3_CHECK);
}

void CAnimStatesDialog::OnSpecial4Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_IDLE_WALKING].used = IsDlgButtonChecked(IDC_SPECIAL4_CHECK);
}

void CAnimStatesDialog::OnSpecial5Check() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_GOTO_IDLE_JUMPING].used = IsDlgButtonChecked(IDC_SPECIAL5_CHECK);
}

void CAnimStatesDialog::OnTauntCheck() {
  int mc = m_current_state;

  m_anim[mc].elem[AS_TAUNT].used = IsDlgButtonChecked(IDC_TAUNT_CHECK);
}

void CAnimStatesDialog::OnSelendokCurrentAnimationPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_CURRENT_ANIMATION_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_CURRENT_ANIMATION_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  for (i = 0; i < NUM_ANIMS_PER_CLASS; i++) {
    if (!stricmp(Anim_state_names[i], name))
      break;
  }

  ASSERT(i != NUM_ANIMS_PER_CLASS);

  m_current_anim = i;

  UpdateDialog();
}

void CAnimStatesDialog::OnSelendokCurrentStatePulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_CURRENT_STATE_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_CURRENT_STATE_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    if (!stricmp(Movement_class_names[i], name))
      break;
  }

  ASSERT(i != NUM_MOVEMENT_CLASSES);

  m_current_state = i;

  UpdateDialog();
}

BOOL CAnimStatesDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  m_current_state = 0;
  m_current_anim = 0;

  CWnd::SetTimer(1, 50, NULL);

  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnimStatesDialog::OnTimer(UINT nIDEvent) {
  UpdateAnimStateView();

  CDialog::OnTimer(nIDEvent);
}

void CAnimStatesDialog::OnKillfocusAlertFromEdit() { KillFocusFroms(IDC_ALERT_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusAlertToEdit() { KillFocusTos(IDC_ALERT_TO_EDIT); }

#define NUM_ANIM_FRAMES 30

// Draws the object based on the current animation state
void CAnimStatesDialog::UpdateAnimStateView() {
  int mc = m_current_state;
  int anim = m_current_anim;
  CWnd *objectwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  static int frame = 0;
  grHardwareSurface surf;

  if (m_anim[mc].elem[anim].used != 1)
    return;

  // Bail out if the "to" frame is less than the "from" frame (ie backwards)
  if (m_anim[mc].elem[anim].to < m_anim[mc].elem[anim].from)
    return;

  float frame_diff = (float)abs(m_anim[mc].elem[anim].to - m_anim[mc].elem[anim].from);
  float frame_start = m_anim[mc].elem[anim].from;

  frame++;
  if (frame == NUM_ANIM_FRAMES)
    frame = 0;

  objectwnd = GetDlgItem(IDC_ANIMSTATE_VIEW);
  objectwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  bm_handle = m_render_handle; // GetObjectImage(m_current_id);

  vector zero_vector;
  vector view_vector = {0, 0, -20};
  matrix id_matrix, rot_matrix;
  poly_model *pm = GetPolymodelPointer(bm_handle);

  vm_MakeZero(&zero_vector);
  vm_MakeIdentity(&id_matrix);

  float norm_angles[MAX_SUBOBJECTS];
  float keyframe = frame_start + frame_diff * ((float)frame / (float)NUM_ANIM_FRAMES);

  SetNormalizedTimeAnim(keyframe, norm_angles, pm);

  vm_AnglesToMatrix(&rot_matrix, 0, m_SpinFrame * 400, 0);
  view_vector.z = -(fabs(pm->maxs.z - pm->mins.z) * 2);

  surf.create(128, 128, BPP_16);
  grViewport *vport = new grViewport(&surf);
  StartEditorFrame(vport, &view_vector, &id_matrix, D3_DEFAULT_ZOOM);
  DrawPolygonModel(&zero_vector, &rot_matrix, bm_handle, norm_angles, 0, 1.0, 1.0, 1.0);
  EndEditorFrame();

  x = rect.left + ((rect.right - rect.left) / 2) - surf.width() / 2;
  y = rect.top + ((rect.bottom - rect.top) / 2) - surf.height() / 2;
  Desktop_surf->blt(x, y, &surf);

  delete vport;
  surf.free();
}

void CAnimStatesDialog::UpdateDialog() {
  CEdit *ebox;
  char str[20];
  int mc = m_current_state;
  int max_states = 24;
  int control_froms[] = {IDC_ALERT_FROM_EDIT,    IDC_DEATH_FROM_EDIT,    IDC_MISSILE1_FROM_EDIT, IDC_RECOIL1_FROM_EDIT,
                         IDC_MISSILE2_FROM_EDIT, IDC_RECOIL2_FROM_EDIT,  IDC_MELEE1_FROM_EDIT,   IDC_MRECOIL1_FROM_EDIT,
                         IDC_MELEE2_FROM_EDIT,   IDC_MRECOIL2_FROM_EDIT, IDC_IDLE_FROM_EDIT,     IDC_QUIRK_FROM_EDIT,
                         IDC_FLINCH_FROM_EDIT,   IDC_TAUNT_FROM_EDIT,    IDC_SPECIAL1_FROM_EDIT, IDC_SPECIAL2_FROM_EDIT,
                         IDC_SPECIAL3_FROM_EDIT, IDC_SPECIAL4_FROM_EDIT, IDC_SPECIAL5_FROM_EDIT, IDC_STANDING_FROM_EDIT,
                         IDC_FLYING_FROM_EDIT,   IDC_ROLLING_FROM_EDIT,  IDC_WALKING_FROM_EDIT,  IDC_JUMPING_FROM_EDIT};

  int control_tos[] = {IDC_ALERT_TO_EDIT,    IDC_DEATH_TO_EDIT,    IDC_MISSILE1_TO_EDIT, IDC_RECOIL1_TO_EDIT,
                       IDC_MISSILE2_TO_EDIT, IDC_RECOIL2_TO_EDIT,  IDC_MELEE1_TO_EDIT,   IDC_MRECOIL1_TO_EDIT,
                       IDC_MELEE2_TO_EDIT,   IDC_MRECOIL2_TO_EDIT, IDC_IDLE_TO_EDIT,     IDC_QUIRK_TO_EDIT,
                       IDC_FLINCH_TO_EDIT,   IDC_TAUNT_TO_EDIT,    IDC_SPECIAL1_TO_EDIT, IDC_SPECIAL2_TO_EDIT,
                       IDC_SPECIAL3_TO_EDIT, IDC_SPECIAL4_TO_EDIT, IDC_SPECIAL5_TO_EDIT, IDC_STANDING_TO_EDIT,
                       IDC_FLYING_TO_EDIT,   IDC_ROLLING_TO_EDIT,  IDC_WALKING_TO_EDIT,  IDC_JUMPING_TO_EDIT};

  int control_spc[] = {
      IDC_SEC_PER_CYCLE_EDIT1,  IDC_SEC_PER_CYCLE_EDIT2,  IDC_SEC_PER_CYCLE_EDIT3,  IDC_SEC_PER_CYCLE_EDIT4,
      IDC_SEC_PER_CYCLE_EDIT5,  IDC_SEC_PER_CYCLE_EDIT6,  IDC_SEC_PER_CYCLE_EDIT7,  IDC_SEC_PER_CYCLE_EDIT8,
      IDC_SEC_PER_CYCLE_EDIT9,  IDC_SEC_PER_CYCLE_EDIT10, IDC_SEC_PER_CYCLE_EDIT11, IDC_SEC_PER_CYCLE_EDIT12,
      IDC_SEC_PER_CYCLE_EDIT13, IDC_SEC_PER_CYCLE_EDIT14, IDC_SEC_PER_CYCLE_EDIT15, IDC_SEC_PER_CYCLE_EDIT16,
      IDC_SEC_PER_CYCLE_EDIT17, IDC_SEC_PER_CYCLE_EDIT18, IDC_SEC_PER_CYCLE_EDIT19, IDC_SEC_PER_CYCLE_EDIT20,
      IDC_SEC_PER_CYCLE_EDIT21, IDC_SEC_PER_CYCLE_EDIT22, IDC_SEC_PER_CYCLE_EDIT23, IDC_SEC_PER_CYCLE_EDIT24};

  int anim_sounds[] = {
      IDC_ANIM_SOUND0_PULLDOWN,  IDC_ANIM_SOUND1_PULLDOWN,  IDC_ANIM_SOUND2_PULLDOWN,  IDC_ANIM_SOUND3_PULLDOWN,
      IDC_ANIM_SOUND4_PULLDOWN,  IDC_ANIM_SOUND5_PULLDOWN,  IDC_ANIM_SOUND6_PULLDOWN,  IDC_ANIM_SOUND7_PULLDOWN,
      IDC_ANIM_SOUND8_PULLDOWN,  IDC_ANIM_SOUND9_PULLDOWN,  IDC_ANIM_SOUND10_PULLDOWN, IDC_ANIM_SOUND11_PULLDOWN,
      IDC_ANIM_SOUND12_PULLDOWN, IDC_ANIM_SOUND13_PULLDOWN, IDC_ANIM_SOUND14_PULLDOWN, IDC_ANIM_SOUND15_PULLDOWN,
      IDC_ANIM_SOUND16_PULLDOWN, IDC_ANIM_SOUND17_PULLDOWN, IDC_ANIM_SOUND18_PULLDOWN, IDC_ANIM_SOUND19_PULLDOWN,
      IDC_ANIM_SOUND20_PULLDOWN, IDC_ANIM_SOUND21_PULLDOWN, IDC_ANIM_SOUND22_PULLDOWN, IDC_ANIM_SOUND23_PULLDOWN};

  CheckDlgButton(IDC_ALERT_CHECK, m_anim[mc].elem[AS_ALERT].used ? 1 : 0);
  CheckDlgButton(IDC_DEATH_CHECK, m_anim[mc].elem[AS_DEATH].used ? 1 : 0);
  CheckDlgButton(IDC_MISSILE1_CHECK, m_anim[mc].elem[AS_BIRTH].used ? 1 : 0);
  CheckDlgButton(IDC_MISSILE1_RECOIL_CHECK, m_anim[mc].elem[AS_MISSILE1_RECOIL].used ? 1 : 0);
  CheckDlgButton(IDC_MISSILE2_CHECK, m_anim[mc].elem[AS_MISSILE2].used ? 1 : 0);
  CheckDlgButton(IDC_MISSILE2_RECOIL_CHECK, m_anim[mc].elem[AS_MISSILE2_RECOIL].used ? 1 : 0);
  CheckDlgButton(IDC_MELEE1_CHECK, m_anim[mc].elem[AS_MELEE1].used ? 1 : 0);
  CheckDlgButton(IDC_MELEE1_RECOIL_CHECK, m_anim[mc].elem[AS_MELEE1_RECOIL].used ? 1 : 0);
  CheckDlgButton(IDC_MELEE2_CHECK, m_anim[mc].elem[AS_MELEE2].used ? 1 : 0);
  CheckDlgButton(IDC_MELEE2_RECOIL_CHECK, m_anim[mc].elem[AS_MELEE2_RECOIL].used ? 1 : 0);
  CheckDlgButton(IDC_QUIRK_CHECK, m_anim[mc].elem[AS_QUIRK].used ? 1 : 0);
  CheckDlgButton(IDC_IDLE_CHECK, m_anim[mc].elem[AS_IDLE].used ? 1 : 0);
  CheckDlgButton(IDC_TAUNT_CHECK, m_anim[mc].elem[AS_TAUNT].used ? 1 : 0);
  CheckDlgButton(IDC_FLINCH_CHECK, m_anim[mc].elem[AS_FLINCH].used ? 1 : 0);
  CheckDlgButton(IDC_SPECIAL1_CHECK, m_anim[mc].elem[AS_GOTO_IDLE_STANDING].used ? 1 : 0);
  CheckDlgButton(IDC_SPECIAL2_CHECK, m_anim[mc].elem[AS_GOTO_IDLE_FLYING].used ? 1 : 0);
  CheckDlgButton(IDC_SPECIAL3_CHECK, m_anim[mc].elem[AS_GOTO_IDLE_ROLLING].used ? 1 : 0);
  CheckDlgButton(IDC_SPECIAL4_CHECK, m_anim[mc].elem[AS_GOTO_IDLE_WALKING].used ? 1 : 0);
  CheckDlgButton(IDC_SPECIAL5_CHECK, m_anim[mc].elem[AS_GOTO_IDLE_JUMPING].used ? 1 : 0);
  CheckDlgButton(IDC_GOTO_STANDING_CHECK, m_anim[mc].elem[AS_GOTO_ALERT_STANDING].used ? 1 : 0);
  CheckDlgButton(IDC_GOTO_FLYING_CHECK, m_anim[mc].elem[AS_GOTO_ALERT_FLYING].used ? 1 : 0);
  CheckDlgButton(IDC_GOTO_WALKING_CHECK, m_anim[mc].elem[AS_GOTO_ALERT_WALKING].used ? 1 : 0);
  CheckDlgButton(IDC_GOTO_ROLLING_CHECK, m_anim[mc].elem[AS_GOTO_ALERT_ROLLING].used ? 1 : 0);
  CheckDlgButton(IDC_GOTO_JUMPING_CHECK, m_anim[mc].elem[AS_GOTO_ALERT_JUMPING].used ? 1 : 0);

  int i;
  for (i = 0; i < max_states; i++) {
    ebox = (CEdit *)GetDlgItem(control_froms[i]);
    itoa(m_anim[mc].elem[i].from, str, 10);
    ebox->SetWindowText(str);

    ebox = (CEdit *)GetDlgItem(control_tos[i]);
    itoa(m_anim[mc].elem[i].to, str, 10);
    ebox->SetWindowText(str);

    ebox = (CEdit *)GetDlgItem(control_spc[i]);
    sprintf(str, "%f", m_anim[mc].elem[i].spc);
    ebox->SetWindowText(str);
  }

  if (!m_setup_sound_dialogs) {
    m_setup_sound_dialogs = true;

    for (i = 0; i < max_states; i++) {
      SendDlgItemMessage(anim_sounds[i], CB_RESETCONTENT, 0, 0);
    }
    for (i = 0; i < MAX_SOUNDS; i++) {
      if (Sounds[i].used) {
        for (int j = 0; j < max_states; j++) {
          SendDlgItemMessage(anim_sounds[j], CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
        }
      }
    }
  }

  for (i = 0; i < max_states; i++) {
    if (m_anim[mc].elem[i].anim_sound_index >= 0 && m_anim[mc].elem[i].anim_sound_index < MAX_SOUNDS &&
        Sounds[m_anim[mc].elem[i].anim_sound_index].used != 0)
      SendDlgItemMessage(anim_sounds[i], CB_SELECTSTRING, 0,
                         (LPARAM)(LPCTSTR)Sounds[m_anim[mc].elem[i].anim_sound_index].name);
    else
      SendDlgItemMessage(anim_sounds[i], CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");
  }

  SendDlgItemMessage(IDC_CURRENT_STATE_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++)
    SendDlgItemMessage(IDC_CURRENT_STATE_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Movement_class_names[i]);

  SendDlgItemMessage(IDC_CURRENT_STATE_PULLDOWN, CB_SELECTSTRING, 0,
                     (LPARAM)(LPCTSTR)Movement_class_names[m_current_state]);

  SendDlgItemMessage(IDC_CURRENT_ANIMATION_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (i = 0; i < NUM_ANIMS_PER_CLASS; i++)
    SendDlgItemMessage(IDC_CURRENT_ANIMATION_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Anim_state_names[i]);

  SendDlgItemMessage(IDC_CURRENT_ANIMATION_PULLDOWN, CB_SELECTSTRING, 0,
                     (LPARAM)(LPCTSTR)Anim_state_names[m_current_anim]);

  UpdateAnimStateView();
}

void CAnimStatesDialog::KillFocusFroms(int num) {
  int control_froms[] = {IDC_ALERT_FROM_EDIT,    IDC_DEATH_FROM_EDIT,    IDC_MISSILE1_FROM_EDIT, IDC_RECOIL1_FROM_EDIT,
                         IDC_MISSILE2_FROM_EDIT, IDC_RECOIL2_FROM_EDIT,  IDC_MELEE1_FROM_EDIT,   IDC_MRECOIL1_FROM_EDIT,
                         IDC_MELEE2_FROM_EDIT,   IDC_MRECOIL2_FROM_EDIT, IDC_IDLE_FROM_EDIT,     IDC_QUIRK_FROM_EDIT,
                         IDC_FLINCH_FROM_EDIT,   IDC_TAUNT_FROM_EDIT,    IDC_SPECIAL1_FROM_EDIT, IDC_SPECIAL2_FROM_EDIT,
                         IDC_SPECIAL3_FROM_EDIT, IDC_SPECIAL4_FROM_EDIT, IDC_SPECIAL5_FROM_EDIT, IDC_STANDING_FROM_EDIT,
                         IDC_FLYING_FROM_EDIT,   IDC_ROLLING_FROM_EDIT,  IDC_WALKING_FROM_EDIT,  IDC_JUMPING_FROM_EDIT};

  char str[20];
  int mc = m_current_state;

  PageInPolymodel(m_render_handle);

  int min_keyframe = Poly_models[m_render_handle].frame_min;
  int max_keyframe = Poly_models[m_render_handle].frame_max;
  int i;
  int max_states = 24;

  for (i = 0; i < max_states; i++)
    if (control_froms[i] == num)
      break;

  ASSERT(i != max_states);

  int anim_state = i;

  CEdit *ebox = (CEdit *)GetDlgItem(num);
  ebox->GetWindowText(str, 20);

  int frame = atoi(str);

  if (frame < min_keyframe)
    frame = min_keyframe;
  else if (frame > max_keyframe)
    frame = max_keyframe;

  m_anim[mc].elem[anim_state].from = frame;
  UpdateDialog();
}

void CAnimStatesDialog::KillFocusSPC(int num) {
  int control_spc[] = {
      IDC_SEC_PER_CYCLE_EDIT1,  IDC_SEC_PER_CYCLE_EDIT2,  IDC_SEC_PER_CYCLE_EDIT3,  IDC_SEC_PER_CYCLE_EDIT4,
      IDC_SEC_PER_CYCLE_EDIT5,  IDC_SEC_PER_CYCLE_EDIT6,  IDC_SEC_PER_CYCLE_EDIT7,  IDC_SEC_PER_CYCLE_EDIT8,
      IDC_SEC_PER_CYCLE_EDIT9,  IDC_SEC_PER_CYCLE_EDIT10, IDC_SEC_PER_CYCLE_EDIT11, IDC_SEC_PER_CYCLE_EDIT12,
      IDC_SEC_PER_CYCLE_EDIT13, IDC_SEC_PER_CYCLE_EDIT14, IDC_SEC_PER_CYCLE_EDIT15, IDC_SEC_PER_CYCLE_EDIT16,
      IDC_SEC_PER_CYCLE_EDIT17, IDC_SEC_PER_CYCLE_EDIT18, IDC_SEC_PER_CYCLE_EDIT19, IDC_SEC_PER_CYCLE_EDIT20,
      IDC_SEC_PER_CYCLE_EDIT21, IDC_SEC_PER_CYCLE_EDIT22, IDC_SEC_PER_CYCLE_EDIT23, IDC_SEC_PER_CYCLE_EDIT24};
  char str[20];
  int mc = m_current_state;
  int i;
  int max_states = 24;

  // Find the index into the array
  for (i = 0; i < max_states; i++)
    if (control_spc[i] == num)
      break;

  // Make sure that we find it
  ASSERT(i != max_states);

  int anim_state = i;

  CEdit *ebox = (CEdit *)GetDlgItem(num);
  ebox->GetWindowText(str, 20);

  float spc = atof(str);

  if (spc <= 0.0 || spc >= 10000.0)
    spc = 1.0f;

  m_anim[mc].elem[anim_state].spc = spc;
  UpdateDialog();
}

void CAnimStatesDialog::KillFocusTos(int num) {
  int control_tos[] = {IDC_ALERT_TO_EDIT,    IDC_DEATH_TO_EDIT,    IDC_MISSILE1_TO_EDIT, IDC_RECOIL1_TO_EDIT,
                       IDC_MISSILE2_TO_EDIT, IDC_RECOIL2_TO_EDIT,  IDC_MELEE1_TO_EDIT,   IDC_MRECOIL1_TO_EDIT,
                       IDC_MELEE2_TO_EDIT,   IDC_MRECOIL2_TO_EDIT, IDC_IDLE_TO_EDIT,     IDC_QUIRK_TO_EDIT,
                       IDC_FLINCH_TO_EDIT,   IDC_TAUNT_TO_EDIT,    IDC_SPECIAL1_TO_EDIT, IDC_SPECIAL2_TO_EDIT,
                       IDC_SPECIAL3_TO_EDIT, IDC_SPECIAL4_TO_EDIT, IDC_SPECIAL5_TO_EDIT, IDC_STANDING_TO_EDIT,
                       IDC_FLYING_TO_EDIT,   IDC_ROLLING_TO_EDIT,  IDC_WALKING_TO_EDIT,  IDC_JUMPING_TO_EDIT};

  char str[20];
  int mc = m_current_state;
  int min_keyframe = Poly_models[m_render_handle].frame_min;
  int max_keyframe = Poly_models[m_render_handle].frame_max;
  int i;
  int max_states = 24;

  for (i = 0; i < max_states; i++)
    if (control_tos[i] == num)
      break;

  ASSERT(i != max_states);

  int anim_state = i;

  CEdit *ebox = (CEdit *)GetDlgItem(num);
  ebox->GetWindowText(str, 20);

  int frame = atoi(str);

  if (frame < min_keyframe)
    frame = min_keyframe;
  else if (frame > max_keyframe)
    frame = max_keyframe;

  m_anim[mc].elem[anim_state].to = frame;
  UpdateDialog();
}

void CAnimStatesDialog::OnKillfocusDeathFromEdit() { KillFocusFroms(IDC_DEATH_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusDeathToEdit() { KillFocusTos(IDC_DEATH_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusFlinchFromEdit() { KillFocusFroms(IDC_FLINCH_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusFlinchToEdit() { KillFocusTos(IDC_FLINCH_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusFlyingFromEdit() { KillFocusFroms(IDC_FLYING_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusFlyingToEdit() { KillFocusTos(IDC_FLYING_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusIdleFromEdit() { KillFocusFroms(IDC_IDLE_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusIdleToEdit() { KillFocusTos(IDC_IDLE_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusJumpingFromEdit() { KillFocusFroms(IDC_JUMPING_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusJumpingToEdit() { KillFocusTos(IDC_JUMPING_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusMelee1FromEdit() { KillFocusFroms(IDC_MELEE1_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusMelee1ToEdit() { KillFocusTos(IDC_MELEE1_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusMelee2FromEdit() { KillFocusFroms(IDC_MELEE2_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusMissile1FromEdit() { KillFocusFroms(IDC_MISSILE1_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusMissile1ToEdit() { KillFocusTos(IDC_MISSILE1_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusMissile2FromEdit() { KillFocusFroms(IDC_MISSILE2_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusMissile2ToEdit() { KillFocusTos(IDC_MISSILE2_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusMrecoil1ToEdit() { KillFocusTos(IDC_MRECOIL1_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusMrecoil1FromEdit() { KillFocusFroms(IDC_MRECOIL1_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusMrecoil2FromEdit() { KillFocusFroms(IDC_MRECOIL2_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusMrecoil2ToEdit() { KillFocusTos(IDC_MRECOIL2_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusQuirkFromEdit() { KillFocusFroms(IDC_QUIRK_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusQuirkToEdit() { KillFocusTos(IDC_QUIRK_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusRecoil1FromEdit() { KillFocusFroms(IDC_RECOIL1_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusRecoil1ToEdit() { KillFocusTos(IDC_RECOIL1_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusRecoil2FromEdit() { KillFocusFroms(IDC_RECOIL2_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusRecoil2ToEdit() { KillFocusTos(IDC_RECOIL2_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusRollingFromEdit() { KillFocusFroms(IDC_ROLLING_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusRollingToEdit() { KillFocusTos(IDC_ROLLING_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial1FromEdit() { KillFocusFroms(IDC_SPECIAL1_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial1ToEdit() { KillFocusTos(IDC_SPECIAL1_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial2FromEdit() { KillFocusFroms(IDC_SPECIAL2_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial2ToEdit() { KillFocusTos(IDC_SPECIAL2_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial3FromEdit() { KillFocusFroms(IDC_SPECIAL3_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial3ToEdit() { KillFocusTos(IDC_SPECIAL3_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial4FromEdit() { KillFocusFroms(IDC_SPECIAL4_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial4ToEdit() { KillFocusTos(IDC_SPECIAL4_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial5FromEdit() { KillFocusFroms(IDC_SPECIAL5_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusSpecial5ToEdit() { KillFocusTos(IDC_SPECIAL5_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusStandingFromEdit() { KillFocusFroms(IDC_STANDING_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusStandingToEdit() { KillFocusTos(IDC_STANDING_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusTauntFromEdit() { KillFocusFroms(IDC_TAUNT_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusTauntToEdit() { KillFocusTos(IDC_TAUNT_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusWalkingFromEdit() { KillFocusFroms(IDC_WALKING_FROM_EDIT); }

void CAnimStatesDialog::OnKillfocusWalkingToEdit() { KillFocusTos(IDC_WALKING_TO_EDIT); }

void CAnimStatesDialog::OnKillfocusMelee2ToEdit() { KillFocusTos(IDC_MELEE2_TO_EDIT); }

void CAnimStatesDialog::OnResetAnimZero() {
  int mc = m_current_state;

  memset(m_anim[mc].elem, 0, NUM_ANIMS_PER_CLASS * sizeof(anim_entry));
  UpdateDialog();
}

void CAnimStatesDialog::OnRotLeft() { m_SpinFrame -= 3; }

void CAnimStatesDialog::OnRotRight() { m_SpinFrame += 3; }

// Copy data from CAnimStatesDialog class to anim struct
void CAnimStatesDialog::GetAnimData(anim_elem *anim_info) {
  for (int i = 0; i < NUM_MOVEMENT_CLASSES; i++)
    for (int j = 0; j < NUM_ANIMS_PER_CLASS; j++)
      anim_info[i].elem[j] = m_anim[i].elem[j];
}

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit1() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT1); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit2() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT2); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit3() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT3); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit4() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT4); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit5() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT5); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit6() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT6); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit7() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT7); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit8() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT8); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit9() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT9); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit10() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT10); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit11() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT11); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit12() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT12); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit13() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT13); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit14() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT14); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit15() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT15); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit16() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT16); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit17() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT17); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit18() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT18); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit19() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT19); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit20() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT20); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit21() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT21); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit22() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT22); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit23() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT23); }

void CAnimStatesDialog::OnKillfocusSecPerCycleEdit24() { KillFocusSPC(IDC_SEC_PER_CYCLE_EDIT24); }

void CAnimStatesDialog::KillFocusAnimSoundName(int num) {
  int anim_sounds[] = {
      IDC_ANIM_SOUND0_PULLDOWN,  IDC_ANIM_SOUND1_PULLDOWN,  IDC_ANIM_SOUND2_PULLDOWN,  IDC_ANIM_SOUND3_PULLDOWN,
      IDC_ANIM_SOUND4_PULLDOWN,  IDC_ANIM_SOUND5_PULLDOWN,  IDC_ANIM_SOUND6_PULLDOWN,  IDC_ANIM_SOUND7_PULLDOWN,
      IDC_ANIM_SOUND8_PULLDOWN,  IDC_ANIM_SOUND9_PULLDOWN,  IDC_ANIM_SOUND10_PULLDOWN, IDC_ANIM_SOUND11_PULLDOWN,
      IDC_ANIM_SOUND12_PULLDOWN, IDC_ANIM_SOUND13_PULLDOWN, IDC_ANIM_SOUND14_PULLDOWN, IDC_ANIM_SOUND15_PULLDOWN,
      IDC_ANIM_SOUND16_PULLDOWN, IDC_ANIM_SOUND17_PULLDOWN, IDC_ANIM_SOUND18_PULLDOWN, IDC_ANIM_SOUND19_PULLDOWN,
      IDC_ANIM_SOUND20_PULLDOWN, IDC_ANIM_SOUND21_PULLDOWN, IDC_ANIM_SOUND22_PULLDOWN, IDC_ANIM_SOUND23_PULLDOWN};

  int mc = m_current_state;
  int cur;

  char name[200];

  cur = SendDlgItemMessage(anim_sounds[num], CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(anim_sounds[num], CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  m_anim[mc].elem[num].anim_sound_index = FindSoundName(name);

  UpdateDialog();
}

void CAnimStatesDialog::OnSelendokAnimSound0Pulldown() { KillFocusAnimSoundName(0); }

void CAnimStatesDialog::OnSelendokAnimSound1Pulldown() { KillFocusAnimSoundName(1); }

void CAnimStatesDialog::OnSelendokAnimSound2Pulldown() { KillFocusAnimSoundName(2); }

void CAnimStatesDialog::OnSelendokAnimSound10Pulldown() { KillFocusAnimSoundName(10); }

void CAnimStatesDialog::OnSelendokAnimSound11Pulldown() { KillFocusAnimSoundName(11); }

void CAnimStatesDialog::OnSelendokAnimSound12Pulldown() { KillFocusAnimSoundName(12); }

void CAnimStatesDialog::OnSelendokAnimSound13Pulldown() { KillFocusAnimSoundName(13); }

void CAnimStatesDialog::OnSelendokAnimSound14Pulldown() { KillFocusAnimSoundName(14); }

void CAnimStatesDialog::OnSelendokAnimSound15Pulldown() { KillFocusAnimSoundName(15); }

void CAnimStatesDialog::OnSelendokAnimSound16Pulldown() { KillFocusAnimSoundName(16); }

void CAnimStatesDialog::OnSelendokAnimSound17Pulldown() { KillFocusAnimSoundName(17); }

void CAnimStatesDialog::OnSelendokAnimSound18Pulldown() { KillFocusAnimSoundName(18); }

void CAnimStatesDialog::OnSelendokAnimSound19Pulldown() { KillFocusAnimSoundName(19); }

void CAnimStatesDialog::OnSelendokAnimSound20Pulldown() { KillFocusAnimSoundName(20); }

void CAnimStatesDialog::OnSelendokAnimSound21Pulldown() { KillFocusAnimSoundName(21); }

void CAnimStatesDialog::OnSelendokAnimSound22Pulldown() { KillFocusAnimSoundName(22); }

void CAnimStatesDialog::OnSelendokAnimSound23Pulldown() { KillFocusAnimSoundName(23); }

void CAnimStatesDialog::OnSelendokAnimSound3Pulldown() { KillFocusAnimSoundName(3); }

void CAnimStatesDialog::OnSelendokAnimSound4Pulldown() { KillFocusAnimSoundName(4); }

void CAnimStatesDialog::OnSelendokAnimSound5Pulldown() { KillFocusAnimSoundName(5); }

void CAnimStatesDialog::OnSelendokAnimSound6Pulldown() { KillFocusAnimSoundName(6); }

void CAnimStatesDialog::OnSelendokAnimSound7Pulldown() { KillFocusAnimSoundName(7); }

void CAnimStatesDialog::OnSelendokAnimSound8Pulldown() { KillFocusAnimSoundName(8); }

void CAnimStatesDialog::OnSelendokAnimSound9Pulldown() { KillFocusAnimSoundName(9); }
