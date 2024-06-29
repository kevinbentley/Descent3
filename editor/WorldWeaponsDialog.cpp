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

 * $Logfile: /DescentIII/Main/editor/WorldWeaponsDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:40 $
 * $Author: kevinb $
 *
 * WorldWeaponsDialog.cpp : implementation file
 *
 * $Log: not supported by cvs2svn $
 *
 * 86    10/24/99 9:34a Chris
 *
 * 85    10/21/99 1:33p Jeff
 * fixed compile error
 *
 * 84    4/12/99 12:29p Jeff
 * added recoil_force to weapon's page
 *
 * 83    4/05/99 4:39p Jason
 * added groovy new smoke trails
 *
 * 82    2/22/99 3:55p Jason
 * added generic damage boxes
 *
 * 81    2/22/99 2:03p Jason
 * added different damages for players and generics
 *
 * 80    2/08/99 5:18p Jason
 * took out EMD effect and added more weapon options
 *
 * 79    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 78    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 77    10/15/98 6:46p Chris
 * Added custom size for weapons
 *
 * 76    10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 75    9/08/98 5:27p Jason
 * added WF_NO_ROTATE flag to weapons
 *
 * 74    9/01/98 4:41p Matt
 * Removed obsolete fields in the weapon structure
 *
 * 73    8/06/98 12:58p Chris
 * Added new homing flags
 *
 * 72    8/03/98 1:09p Jason
 * added some more weapons flags
 *
 * 71    7/31/98 11:52a Chris
 * Weapons can be persistent.  Added ability for objects to be manually
 * set for no object collisions.
 *
 * 70    7/30/98 4:35p Jason
 * added more weapon checkboxes
 *
 * 69    7/30/98 11:09a Jason
 * added weapons that freeze and deform terrain
 *
 * 68    7/01/98 12:11p Jason
 * added countermeasures
 *
 * 67    6/30/98 3:35p Jason
 * adding countermeasures
 *
 * 66    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 65    6/22/98 6:26p Jason
 * added gravity field effect for weapons
 *
 * 64    6/19/98 12:04p Jason
 *
 * 63    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 62    5/25/98 8:36p Matt
 * Added code to set different sizes for different weapon scorch marks.
 * Also, don't leave scorch marks on lights.
 *
 * 61    5/25/98 6:39p Jason
 * got icons working for weapons
 *
 * 60    5/22/98 12:34p Matt
 * Added scorch mark/bullet hole system.
 *
 * 59    5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 58    5/18/98 4:46p Mark
 * Bail on a current weapon of -1
 *
 * 57    5/07/98 2:46p Chris
 *
 * 56    5/07/98 2:44p Chris
 *
 * 55    5/07/98 2:39p Chris
 * Added death_dot and bounce sound for weapons
 *
 * 54    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 53    4/17/98 2:00p Jason
 * added cool object effects
 *
 * 52    4/15/98 12:22p Jason
 * lots of miscellaneous stuff pertaining to lighting and vis effects
 *
 * 51    4/10/98 12:39p Jason
 * added expanding explosion bitmaps
 *
 * 50    4/09/98 4:49p Chris
 * Allowed the copying and pasting of weapons
 *
 * 49    4/07/98 3:31p Jason
 * got particle effects working with weapons
 *
 * 48    4/06/98 4:53p Jason
 * got pageable polymodels working correctly with editor
 *
 * 47    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 46    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 45    3/11/98 4:57p Chris
 * Changed the ComputeDefualtSize function call
 *
 * 44    3/09/98 8:12a Chris
 * Added the start of the homing code
 *
 * 43    2/26/98 2:48p Mark
 * fixed changing of fire image handle stuff
 *
 * 42    2/25/98 3:48p Jason
 * added ifl to list of discharge files
 *
 * 41    2/19/98 1:52p Jason
 * added emergency override to unlock function
 *
 * 40    2/11/98 2:04p Jason
 * got spawning weapons working
 *
 * 39    2/09/98 3:18p Matt
 * Added checkbox to set Enable Camera property for a weapon
 *
 * 38    2/05/98 6:29p Jason
 * added user settable explode time/size
 *
 * 37    2/05/98 4:28p Jason
 * made models selectable on add weapon
 *
 * 36    2/05/98 12:37p Jason
 * added more weapon effects
 *
 * 35    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 34    1/29/98 6:06p Jason
 * added new weapons
 *
 * 33    1/28/98 5:37p Jason
 * added streamer weapons
 *
 * 32    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 31    12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 30    12/08/97 6:46p Jason
 * reenabled editing of thrusttime
 *
 * 29    12/05/97 11:26a Jason
 * fixed smoke pulldown bug
 *
 * 28    12/05/97 11:02a Mark
 * If there was no current selection for the pulldown smoke menu, then
 * don't do anything.  -Samir
 *
 * 27    12/04/97 12:15p Jason
 * gave designers the ability to set their own weapon-to-wall hit vclips
 *
 * 26    12/03/97 11:54a Jason
 * added designer-settable smoketrails
 *
 * 25    12/02/97 5:31p Samir
 * New file dialog interface implemented.
 *
 * 24    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 23    11/14/97 10:09p Jason
 * added model sizing functionality
 *
 * 22    11/06/97 6:18p Jason
 * added support for electrical weapons
 *
 * 21    11/05/97 11:09a Jason
 * fixed stupid window naming bug I introduced
 *
 * 20    11/04/97 5:16p Jason
 * disable blob size window if this is a model
 *
 * 19    11/04/97 2:46p Jason
 * changes to weapon system
 *
 * 18    11/02/97 4:27p Matt
 * Made physics dialog copy data back into original struct, instead of
 * having the caller do it.
 *
 * 17    10/30/97 5:57p Matt
 * Fixed bug that prevented clearing of smoke flag
 *
 * 16    10/30/97 5:00p Jason
 * Made weapons use generic lighting code
 *
 * 15    10/30/97 2:53p Matt
 * Revamped weapon dialog
 *
 * 14    10/29/97 1:27p Chris
 * Added PF_STICK for weapons
 *
 * 13    10/22/97 4:19p Jason
 * added smoke trail effects
 *
 * 12    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 11    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 10    9/17/97 1:35p Matt
 * Fixed some compiler warnings
 *
 * 9     9/17/97 10:59a Chris
 * Added a new way to compute radi
 *
 * 8     9/09/97 6:55p Jason
 * better error checking for model usage counts
 *
 * 7     9/03/97 3:53p Jason
 * got objects to cast light
 *
 * 6     8/08/97 2:25p Matt
 * Took out error messages which are now handled by mng_MakeLocker()
 *
 * 5     8/07/97 5:24p Chris
 * Expanded the weapon system
 *
 * 4     8/06/97 4:33p Chris
 * Expanded the weapons page
 *
 * 3     7/24/97 6:11p Matt
 * Created symbolic constant for default zoom, and used it every place
 * that specifies zoom
 *
 * $NoKeywords: $
 */

#include "mfc_compatibility.h"
#include "editor.h"
#include "WorldWeaponsDialog.h"
#include "manage.h"
#include "vclip.h"
#include "bitmap.h"
#include "weaponpage.h"
#include "weapon.h"
#include "polymodel.h"
#include "soundpage.h"
#include "soundload.h"
#include "object.h"
#include "gametexture.h"
#include "PhysicsDlg.h"
#include "EditLineDialog.h"
#include "GenericLightDialog.h"
#include "ddio.h"
#include "mem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldWeaponsDialog dialog

CWorldWeaponsDialog::CWorldWeaponsDialog(CWnd *pParent /*=NULL*/) : CDialog(CWorldWeaponsDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWorldWeaponsDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CWorldWeaponsDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWorldWeaponsDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldWeaponsDialog, CDialog)
//{{AFX_MSG_MAP(CWorldWeaponsDialog)
ON_BN_CLICKED(IDC_ADD_WEAPON, OnAddWeapon)
ON_BN_CLICKED(IDC_DELETE_WEAPON, OnDeleteWeapon)
ON_BN_CLICKED(IDC_CHECKIN_WEAPON, OnCheckinWeapon)
ON_BN_CLICKED(IDC_LOCK_WEAPON, OnLockWeapon)
ON_BN_CLICKED(IDC_NEXT_WEAPON, OnNextWeapon)
ON_BN_CLICKED(IDC_PREV_WEAPON, OnPrevWeapon)
ON_BN_CLICKED(IDC_LOAD_WEAPON_ANIM, OnLoadWeaponAnim)
ON_CBN_SELENDOK(IDC_WEAPON_PULLDOWN, OnSelendokWeaponPulldown)
ON_BN_CLICKED(IDC_WEAPONS_OUT, OnWeaponsOut)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_LOAD_WEAPON_DISCHARGE, OnLoadWeaponDischarge)
ON_CBN_SELENDOK(IDC_FIRE_SOUND_PULLDOWN, OnSelendokFireSoundPulldown)
ON_CBN_SELENDOK(IDC_WEAPON_WALL_SOUND_PULLDOWN, OnSelendokWeaponWallSoundPulldown)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_WEAPON_HOMING_CHECK, OnWeaponHomingCheck)
ON_BN_CLICKED(IDC_WEAPON_COLLIDE_WITH_SIBLING_CHECK, OnWeaponCollideWithSiblingCheck)
ON_BN_CLICKED(IDC_WEAPON_USE_PARENT_VELOCITY_CHECK, OnWeaponUseParentVelocityCheck)
ON_EN_KILLFOCUS(IDC_WEAPON_THRUST_EDIT, OnKillfocusWeaponThrustTimeEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_BLOB_SIZE_EDIT, OnKillfocusWeaponBlobSizeEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_IMPACT_SIZE_EDIT, OnKillfocusWeaponImpactSizeEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_LIFE_TIME_EDIT, OnKillfocusWeaponLifeTimeEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_DAMAGE_EDIT, OnKillfocusWeaponDamageEdit)
ON_BN_CLICKED(IDC_SMOKE_CHECK, OnSmokeCheck)
ON_BN_CLICKED(IDC_EDIT_PHYSICS, OnEditPhysics)
ON_BN_CLICKED(IDC_CHANGE_NAME, OnChangeName)
ON_BN_CLICKED(IDC_WEAPON_LIGHT_INFO, OnWeaponLightInfo)
ON_BN_CLICKED(IDC_ENERGY_RADIO, OnEnergyRadio)
ON_BN_CLICKED(IDC_MATTER_RADIO, OnMatterRadio)
ON_BN_CLICKED(IDC_ELECTRICAL_CHECK, OnElectricalCheck)
ON_BN_CLICKED(IDC_DEFAULT_SIZE, OnDefaultSize)
ON_EN_KILLFOCUS(IDC_WEAPON_IMPACT_TIME_EDIT, OnKillfocusWeaponImpactTimeEdit)
ON_CBN_SELENDOK(IDC_SMOKE_PULLDOWN, OnSelendokSmokePulldown)
ON_CBN_SELENDOK(IDC_EXPLODE_PULLDOWN, OnSelendokExplodePulldown)
ON_BN_CLICKED(IDC_SPRAY_CHECK, OnSprayCheck)
ON_BN_CLICKED(IDC_INSTANT_CHECK, OnInstantCheck)
ON_BN_CLICKED(IDC_INVISIBLE, OnInvisible)
ON_BN_CLICKED(IDC_RING, OnRing)
ON_BN_CLICKED(IDC_EXPLODE_RING, OnExplodeRing)
ON_BN_CLICKED(IDC_PLANAR_BLAST, OnPlanarBlast)
ON_BN_CLICKED(IDC_SATURATE_CHECK, OnSaturateCheck)
ON_EN_KILLFOCUS(IDC_WEAPON_ALPHA_EDIT, OnKillfocusWeaponAlphaEdit)
ON_BN_CLICKED(IDC_PLANAR_CHECK, OnPlanarCheck)
ON_EN_KILLFOCUS(IDC_EXPLODE_SIZE_EDIT, OnKillfocusExplodeSizeEdit)
ON_EN_KILLFOCUS(IDC_EXPLODE_TIME_EDIT, OnKillfocusExplodeTimeEdit)
ON_CBN_SELENDOK(IDC_WEAPON_SPAWN_PULLDOWN, OnSelendokWeaponSpawnPulldown)
ON_EN_KILLFOCUS(IDC_WEAPON_SPAWN_EDIT, OnKillfocusWeaponSpawnEdit)
ON_BN_CLICKED(IDC_SPAWNS_ON_IMPACT, OnSpawnsOnImpact)
ON_BN_CLICKED(IDC_SPAWNS_ON_TIMEOUT, OnSpawnsOnTimeout)
ON_BN_CLICKED(IDC_OVERRIDE, OnOverride)
ON_EN_KILLFOCUS(IDC_PARTICLE_COUNT_EDIT, OnKillfocusParticleCountEdit)
ON_EN_KILLFOCUS(IDC_PARTICLE_LIFE_EDIT, OnKillfocusParticleLifeEdit)
ON_EN_KILLFOCUS(IDC_PARTICLE_SIZE_EDIT, OnKillfocusParticleSizeEdit)
ON_CBN_SELENDOK(IDC_PARTICLE_PULLDOWN, OnSelendokParticlePulldown)
ON_BN_CLICKED(IDC_WEAPON_COPY_BUTTON, OnWeaponCopyButton)
ON_BN_CLICKED(IDC_WEAPON_PASTE_BUTTON, OnWeaponPasteButton)
ON_BN_CLICKED(IDC_EXPANDING_CHECK, OnExpandingCheck)
ON_BN_CLICKED(IDC_MUZZLE_FLASH, OnMuzzleFlash)
ON_BN_CLICKED(IDC_MICROWAVE, OnMicrowave)
ON_BN_CLICKED(IDC_NAPALM, OnNapalm)
ON_CBN_SELENDOK(IDC_WEAPON_BOUNCE_SOUND_COMBO, OnSelendokWeaponBounceSoundCombo)
ON_EN_KILLFOCUS(IDC_WEAPON_IMPACT_TIME_EDIT2, OnKillfocusWeaponImpactTimeEdit2)
ON_EN_KILLFOCUS(IDC_WEAPON_IMPACT_DAMAGE_EDIT, OnKillfocusWeaponImpactDamageEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_IMPACT_FORCE_EDIT, OnKillfocusWeaponImpactForceEdit)
ON_CBN_SELENDOK(IDC_SCORCH_PULLDOWN, OnSelendokScorchPulldown)
ON_EN_KILLFOCUS(IDC_WEAPON_SCORCH_SIZE_EDIT, OnKillfocusWeaponScorchSizeEdit)
ON_CBN_SELENDOK(IDC_SMALLIMG_PULLDOWN, OnSelendokSmallimgPulldown)
ON_CBN_SELENDOK(IDC_SPAWN2_PULLDOWN, OnSelendokSpawn2Pulldown)
ON_EN_KILLFOCUS(IDC_ALTERNATE_CHANCE_EDIT, OnKillfocusAlternateChanceEdit)
ON_BN_CLICKED(IDC_REVERSE_SMOKE_CHECK, OnReverseSmokeCheck)
ON_BN_CLICKED(IDC_GRAVITY_FIELD_CHECK, OnGravityFieldCheck)
ON_EN_KILLFOCUS(IDC_GRAVITY_SIZE, OnKillfocusGravitySize)
ON_EN_KILLFOCUS(IDC_GRAVITY_TIME, OnKillfocusGravityTime)
ON_BN_CLICKED(IDC_COUNTERMEASURE_CHECK, OnCountermeasureCheck)
ON_BN_CLICKED(IDC_SPAWNS_ROBOT_CHECK, OnSpawnsRobotCheck)
ON_CBN_SELENDOK(IDC_SPAWN_ROBOT_PULLDOWN, OnSelendokSpawnRobotPulldown)
ON_EN_KILLFOCUS(IDC_TERRIAN_DAMAGE_SIZE, OnKillfocusTerrianDamageSize)
ON_EN_KILLFOCUS(IDC_TERRAIN_DAMAGE_DEPTH, OnKillfocusTerrainDamageDepth)
ON_BN_CLICKED(IDC_FREEZE_CHECK, OnFreezeCheck)
ON_BN_CLICKED(IDC_SILENT_HOMING_CHECK, OnSilentHomingCheck)
ON_BN_CLICKED(IDC_HOMED_SPLIT_CHECK, OnHomedSplitCheck)
ON_EN_KILLFOCUS(IDC_HOMING_FOV_TEXT, OnKillfocusHomingFovText)
ON_BN_CLICKED(IDC_NO_ROTATE_CHECK, OnNoRotateCheck)
ON_BN_CLICKED(IDC_CUSTOM_SIZE_CHECK, OnCustomSizeCheck)
ON_EN_KILLFOCUS(IDC_CUSTOM_SIZE_EDIT, OnKillfocusCustomSizeEdit)
ON_BN_CLICKED(IDC_TIMEOUT_WALL_CHECK, OnTimeoutWallCheck)
ON_BN_CLICKED(IDC_ENABLE_CAMERA, OnEnableCamera)
ON_EN_KILLFOCUS(IDC_WEAPON_GENERIC_DAMAGE_EDIT, OnKillfocusWeaponGenericDamageEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_IMPACT_GENERIC_DAMAGE_EDIT, OnKillfocusWeaponImpactGenericDamageEdit)
ON_BN_CLICKED(IDC_PLANAR_SMOKE_CHECK, OnPlanarSmokeCheck)
ON_EN_KILLFOCUS(IDC_WEAPON_THRUST_TIME_EDIT, OnKillfocusWeaponThrustTimeEdit)
ON_EN_KILLFOCUS(IDC_WEAPON_RECOIL_FORCE_EDIT, OnKillfocusWeaponRecoilForceEdit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldWeaponsDialog message handlers

void CWorldWeaponsDialog::OnAddWeapon() {
  char filename[255], dir[255], fname[128], ext[32];
  char cur_name[100];
  int bm_handle, weapon_handle;
  int c = 1, finding_name = 1;
  int anim = 0, model = 0;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  MessageBox("First select what this weapons image will be on the cockpit (HUD)");

  CString filter =
      "Descent III files "
      "(*.itl,*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ifl,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl;*.itl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_weapon_dir, sizeof(Current_weapon_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  bm_handle = LoadWeaponHudImage(filename, &anim);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  weapon_handle = AllocWeapon();

  while (finding_name) {
    sprintf(cur_name, "%s%d", fname, c);
    if (FindWeaponName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(Weapons[weapon_handle].name, cur_name);

  if (anim)
    Weapons[weapon_handle].flags |= WF_HUD_ANIMATED;
  else
    Weapons[weapon_handle].flags &= ~WF_HUD_ANIMATED;

  Weapons[weapon_handle].hud_image_handle = bm_handle;

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[Weapons[weapon_handle].hud_image_handle].name);
    bm_SaveFileBitmap(filename, Weapons[weapon_handle].hud_image_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameVClips[Weapons[weapon_handle].hud_image_handle].name);
    SaveVClip(filename, Weapons[weapon_handle].hud_image_handle);
  }

  // Now do the firing image

  MessageBox("Now select what this weapons discharge image/model will be when it is fired!");

  CString ffilter =
      "Descent III files "
      "(*.ifl,*.tga,*.bbm,*.lbm,*.ogf,*.pcx,*.pof,*.oof)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.pof;*.oof;*.oaf;*.ifl;*.itl||";

  if (!OpenFileDialog(this, (LPCSTR)ffilter, filename, Current_weapon_dir, sizeof(Current_weapon_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  anim = 0;
  bm_handle = LoadWeaponFireImage(filename, &model, &anim, 0);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/model file.");
    return;
  }

  // figure out size of the weapon
  if (model) {
    ComputeDefaultSize(OBJ_WEAPON, bm_handle, &Weapons[weapon_handle].size);
  } else {
    Weapons[weapon_handle].size = DEFAULT_WEAPON_SIZE;
  }

  if (!model) {
    if (anim)
      Weapons[weapon_handle].flags |= WF_IMAGE_VCLIP;
    else
      Weapons[weapon_handle].flags |= WF_IMAGE_BITMAP;
  } else {
    Weapons[weapon_handle].flags &= ~WF_IMAGE_BITMAP;
    Weapons[weapon_handle].flags &= ~WF_ELECTRICAL;
    Weapons[weapon_handle].flags &= ~WF_IMAGE_VCLIP;
  }

  Weapons[weapon_handle].fire_image_handle = bm_handle;

  mprintf(0, "Making a copy of this bitmap/model locally...\n");

  if (!model) {
    if (!anim) {
      sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
        GameBitmaps[Weapons[weapon_handle].fire_image_handle].name);
      bm_SaveFileBitmap(filename, Weapons[weapon_handle].fire_image_handle);
    } else {
      sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
        GameVClips[Weapons[weapon_handle].fire_image_handle].name);
      SaveVClip(filename, Weapons[weapon_handle].fire_image_handle);
    }
  } else {
    std::filesystem::path destname = LocalModelsDir / Poly_models[Weapons[weapon_handle].fire_image_handle].name;
    cf_CopyFile(destname, filename);
  }

  mng_AllocTrackLock(cur_name, PAGETYPE_WEAPON);

  D3EditState.current_weapon = weapon_handle;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnDeleteWeapon() {
  int answer, tl;
  mngs_Pagelock pl;
  int n = D3EditState.current_weapon;

  if (Num_weapons < 1)
    return;

  // Check to see if we even have it locked
  if ((tl = mng_FindTrackLock(Weapons[n].name, PAGETYPE_WEAPON)) == -1) {
    OutrageMessageBox("This weapon is not yours to delete.  Lock first.");
    return;
  }

  // Make sure its to be deleted
  answer = MessageBox("Are you sure you want to delete this weapon?", Weapons[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Weapons[n].name);
  pl.pagetype = PAGETYPE_WEAPON;

  // Check to see if this is a local weapon only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(Weapons[n].name, PAGETYPE_WEAPON, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else // if its network, delete it from both the net and local drives
  {

    mng_FreeTrackLock(tl);
    mng_DeletePage(Weapons[n].name, PAGETYPE_WEAPON, 1);
    mng_DeletePage(Weapons[n].name, PAGETYPE_WEAPON, 0);
    mng_DeletePagelock(Weapons[n].name, PAGETYPE_WEAPON);
  }

  // Advance to the next weapon
  D3EditState.current_weapon = GetNextWeapon(n);

  // Free weapon images
  if (Weapons[n].flags & WF_HUD_ANIMATED)
    FreeVClip(Weapons[n].hud_image_handle);
  else
    bm_FreeBitmap(Weapons[n].hud_image_handle);

  if (Weapons[n].fire_image_handle != -1) {
    if (Weapons[n].flags & WF_IMAGE_BITMAP)
      bm_FreeBitmap(Weapons[n].fire_image_handle);
    else if (Weapons[n].flags & WF_IMAGE_VCLIP)
      FreeVClip(Weapons[n].fire_image_handle);
    else
      FreePolyModel(Weapons[n].fire_image_handle);
  }

  FreeWeapon(n);
  mng_EraseLocker();

  OutrageMessageBox("Weapon deleted.");

  RemapWeapons();

  UpdateDialog();
}

void CWorldWeaponsDialog::OnCheckinWeapon() {
  int n = D3EditState.current_weapon;
  mngs_Pagelock temp_pl;
  int r;

  if (Num_weapons < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure we own this weapon
  strcpy(temp_pl.name, Weapons[n].name);
  temp_pl.pagetype = PAGETYPE_WEAPON;

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

      if (!mng_ReplacePage(Weapons[n].name, Weapons[n].name, n, PAGETYPE_WEAPON, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this weapon anim/image to the network for all
        std::filesystem::path srcname, destname;
        if (Weapons[n].flags & WF_HUD_ANIMATED) {
          srcname = LocalManageGraphicsDir / GameVClips[Weapons[n].hud_image_handle].name;
          destname = ManageGraphicsDir / GameVClips[Weapons[n].hud_image_handle].name;
        } else {
          srcname = LocalManageGraphicsDir / GameBitmaps[Weapons[n].hud_image_handle].name;
          destname = ManageGraphicsDir / GameBitmaps[Weapons[n].hud_image_handle].name;
        }

        cf_CopyFile(destname, srcname);

        if (Weapons[n].flags & WF_IMAGE_BITMAP) {
          srcname = LocalManageGraphicsDir / GameBitmaps[Weapons[n].fire_image_handle].name;
          destname = ManageGraphicsDir, GameBitmaps[Weapons[n].fire_image_handle].name;

        } else if (Weapons[n].flags & WF_IMAGE_VCLIP) {
          srcname = LocalManageGraphicsDir / GameVClips[Weapons[n].fire_image_handle].name;
          destname = ManageGraphicsDir / GameVClips[Weapons[n].fire_image_handle].name;
        } else {
          srcname = LocalModelsDir / Poly_models[Weapons[n].fire_image_handle].name;
          destname = NetModelsDir / Poly_models[Weapons[n].fire_image_handle].name;
        }

        cf_CopyFile(destname, srcname);

        OutrageMessageBox("Weapon checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Weapons[n].name, PAGETYPE_WEAPON, 1);
        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Weapons[n].name, PAGETYPE_WEAPON);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }
}

void CWorldWeaponsDialog::OnLockWeapon() {
  int n = D3EditState.current_weapon;
  mngs_Pagelock temp_pl;
  mngs_weapon_page weaponpage;
  int r;

  if (Num_weapons < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, Weapons[n].name);
  temp_pl.pagetype = PAGETYPE_WEAPON;

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
  }

  else if (r < 0)
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
      if (mng_FindSpecificWeaponPage(temp_pl.name, &weaponpage, 0)) {
        if (mng_AssignWeaponPageToWeapon(&weaponpage, n)) {
          if (!mng_ReplacePage(Weapons[n].name, Weapons[n].name, n, PAGETYPE_WEAPON, 1)) {
            OutrageMessageBox("There was problem writing that page locally!");
            mng_EraseLocker();
            return;
          }

          OutrageMessageBox("Weapon locked.");
        } else
          OutrageMessageBox(
              "There was a problem loading this weapon.  You might encounter problems in dealing with it.  Good luck!");

        mng_AllocTrackLock(Weapons[n].name, PAGETYPE_WEAPON);
        UpdateDialog();
      } else
        OutrageMessageBox("Couldn't find that weapon in the table file!");
    }
  }
  mng_EraseLocker();
}

void CWorldWeaponsDialog::OnNextWeapon() {
  D3EditState.current_weapon = GetNextWeapon(D3EditState.current_weapon);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnPrevWeapon() {
  D3EditState.current_weapon = GetPrevWeapon(D3EditState.current_weapon);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnLoadWeaponAnim() {
  char filename[255];
  int bm_handle;
  int anim = 0;

  CString filter =
      "Descent III files (*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_weapon_dir, sizeof(Current_weapon_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  bm_handle = LoadWeaponHudImage(filename, &anim);

  if (bm_handle < 0) {
    OutrageMessageBox("Could not load that bitmap...restoring previous bitmap.");
    return;
  }
  int n = D3EditState.current_weapon;

  Weapons[n].hud_image_handle = bm_handle;

  if (anim)
    Weapons[n].flags |= WF_HUD_ANIMATED;
  else
    Weapons[n].flags &= ~WF_HUD_ANIMATED;

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  std::filesystem::path curname;
  if (anim) {
    curname = LocalManageGraphicsDir / GameVClips[Weapons[n].hud_image_handle].name;
    SaveVClip(curname, Weapons[n].hud_image_handle);

  } else {
    curname = LocalManageGraphicsDir / GameBitmaps[Weapons[n].hud_image_handle].name;
    bm_SaveFileBitmap(curname, Weapons[n].hud_image_handle);
  }

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokWeaponPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_WEAPON_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_WEAPON_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindWeaponName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted weapon list, but probably nothing.");
    UpdateDialog();
    return;
  }

  D3EditState.current_weapon = i;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnWeaponsOut() {
  char str[10000];
  int total = 0;

  mng_DisplayLockList(TableUser);

  sprintf(str, "User %s has these weapons held locally:\n\n", TableUser);
  for (int i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_WEAPON) {
      char temp[90];

      sprintf(temp, "%s", GlobalTrackLocks[i].name);
      strcat(str, temp);
      strcat(str, "\n");
      total++;
    }
  }

  if (total != 0) {
    // Display that string
    MessageBox(str, "Weapons", MB_OK);
  }
}

// When closing, save all our checked out weapons locally so we know
// what stuff to flag as "checked out" the next time we start up
void CWorldWeaponsDialog::SaveWeaponsOnClose() {
  int i, t;

  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_WEAPON) {
      t = FindWeaponName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);
      mng_ReplacePage(Weapons[t].name, Weapons[t].name, t, PAGETYPE_WEAPON, 1);
    }
  }
}

#define NULL_NAME "<none>"

void CWorldWeaponsDialog::UpdateDialog() {
  CEdit *ebox;
  CButton *bbox;
  int n = D3EditState.current_weapon;
  char str[50];

  if (Num_weapons < 1) {
    bbox = (CButton *)GetDlgItem(IDC_NEXT_WEAPON);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_PREV_WEAPON);
    bbox->EnableWindow(FALSE);

    return;
  } else {
    bbox = (CButton *)GetDlgItem(IDC_NEXT_WEAPON);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_PREV_WEAPON);
    bbox->EnableWindow(TRUE);
  }

  if (!Weapons[n].used)
    n = D3EditState.current_weapon = GetNextWeapon(n);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_VCLIP_EDIT);
  if (Weapons[n].flags & WF_HUD_ANIMATED)
    ebox->SetWindowText(GameVClips[Weapons[n].hud_image_handle].name);
  else
    ebox->SetWindowText(GameBitmaps[Weapons[n].hud_image_handle].name);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_DISCHARGE_EDIT);

  if (Weapons[n].flags & WF_IMAGE_BITMAP)
    ebox->SetWindowText(GameBitmaps[Weapons[n].fire_image_handle].name);
  else if (Weapons[n].flags & WF_IMAGE_VCLIP)
    ebox->SetWindowText(GameVClips[Weapons[n].fire_image_handle].name);
  else
    ebox->SetWindowText(Poly_models[Weapons[n].fire_image_handle].name);

  bbox = (CButton *)GetDlgItem(IDC_CHECKIN_WEAPON);
  if (mng_FindTrackLock(Weapons[n].name, PAGETYPE_WEAPON) == -1) {
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_WEAPON);
    bbox->EnableWindow(TRUE);
  } else {
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_WEAPON);
    bbox->EnableWindow(FALSE);
  }

  SendDlgItemMessage(IDC_WEAPON_PULLDOWN, CB_RESETCONTENT, 0, 0);

  for (int i = 0; i < MAX_WEAPONS; i++) {
    if (Weapons[i].used)
      SendDlgItemMessage(IDC_WEAPON_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Weapons[i].name);
  }
  SendDlgItemMessage(IDC_WEAPON_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Weapons[n].name);

  SendDlgItemMessage(IDC_FIRE_SOUND_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      SendDlgItemMessage(IDC_FIRE_SOUND_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
  }
  if (Weapons[n].sounds[WSI_FIRE] >= 0 && Weapons[n].sounds[WSI_FIRE] < MAX_SOUNDS &&
      Sounds[Weapons[n].sounds[WSI_FIRE]].used != 0)
    SendDlgItemMessage(IDC_FIRE_SOUND_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Sounds[Weapons[n].sounds[WSI_FIRE]].name);
  else
    SendDlgItemMessage(IDC_FIRE_SOUND_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");

  SendDlgItemMessage(IDC_WEAPON_BOUNCE_SOUND_COMBO, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      SendDlgItemMessage(IDC_WEAPON_BOUNCE_SOUND_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
  }
  if (Weapons[n].sounds[WSI_BOUNCE] >= 0 && Weapons[n].sounds[WSI_BOUNCE] < MAX_SOUNDS &&
      Sounds[Weapons[n].sounds[WSI_BOUNCE]].used != 0)
    SendDlgItemMessage(IDC_WEAPON_BOUNCE_SOUND_COMBO, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Sounds[Weapons[n].sounds[WSI_BOUNCE]].name);
  else
    SendDlgItemMessage(IDC_WEAPON_BOUNCE_SOUND_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");

  SendDlgItemMessage(IDC_WEAPON_WALL_SOUND_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      SendDlgItemMessage(IDC_WEAPON_WALL_SOUND_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
  }
  if (Weapons[n].sounds[WSI_IMPACT_WALL] >= 0 && Weapons[n].sounds[WSI_IMPACT_WALL] < MAX_SOUNDS &&
      Sounds[Weapons[n].sounds[WSI_IMPACT_WALL]].used != 0)
    SendDlgItemMessage(IDC_WEAPON_WALL_SOUND_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Sounds[Weapons[n].sounds[WSI_IMPACT_WALL]].name);
  else
    SendDlgItemMessage(IDC_WEAPON_WALL_SOUND_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");

  SendDlgItemMessage(IDC_SMOKE_PULLDOWN, CB_RESETCONTENT, 0, 0);

  if (Weapons[n].flags & WF_SMOKE) {
    for (int i = 0; i < MAX_TEXTURES; i++) {
      if (GameTextures[i].used)
        SendDlgItemMessage(IDC_SMOKE_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
    }
  }

  if ((Weapons[n].flags & WF_SMOKE) && Weapons[n].smoke_handle >= 0 && GameTextures[Weapons[n].smoke_handle].used)
    SendDlgItemMessage(IDC_SMOKE_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)GameTextures[Weapons[n].smoke_handle].name);
  else
    SendDlgItemMessage(IDC_SMOKE_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");

  // Do scorch pulldown
  SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  for (int i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
  }

  if ((Weapons[n].scorch_handle >= 0) && GameTextures[Weapons[n].scorch_handle].used)
    SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)GameTextures[Weapons[n].scorch_handle].name);
  else
    SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);

  // Do icon pulldown
  SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  for (int i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
  }

  if ((Weapons[n].icon_handle >= 0) && GameTextures[Weapons[n].icon_handle].used)
    SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)GameTextures[Weapons[n].icon_handle].name);
  else
    SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);

  SendDlgItemMessage(IDC_EXPLODE_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      SendDlgItemMessage(IDC_EXPLODE_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
  }

  if (Weapons[n].explode_image_handle >= 0 && GameTextures[Weapons[n].explode_image_handle].used)
    SendDlgItemMessage(IDC_EXPLODE_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)GameTextures[Weapons[n].explode_image_handle].name);
  else {
    SendDlgItemMessage(IDC_EXPLODE_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");
    Weapons[n].explode_image_handle = -1;
  }

  // Do particle handle
  SendDlgItemMessage(IDC_PARTICLE_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      SendDlgItemMessage(IDC_PARTICLE_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
  }

  if (Weapons[n].particle_handle >= 0 && GameTextures[Weapons[n].particle_handle].used)
    SendDlgItemMessage(IDC_PARTICLE_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)GameTextures[Weapons[n].particle_handle].name);
  else {
    SendDlgItemMessage(IDC_PARTICLE_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");
    Weapons[n].particle_handle = -1;
  }

  // Do spawn handles
  SendDlgItemMessage(IDC_WEAPON_SPAWN_PULLDOWN, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_SPAWN2_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_WEAPONS; i++) {
    if (Weapons[i].used) {
      SendDlgItemMessage(IDC_WEAPON_SPAWN_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Weapons[i].name);
      SendDlgItemMessage(IDC_SPAWN2_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Weapons[i].name);
    }
  }

  if (Weapons[n].spawn_handle >= 0 && Weapons[Weapons[n].spawn_handle].used)
    SendDlgItemMessage(IDC_WEAPON_SPAWN_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Weapons[Weapons[n].spawn_handle].name);
  else {
    SendDlgItemMessage(IDC_WEAPON_SPAWN_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");
    Weapons[n].spawn_handle = -1;
  }

  if (Weapons[n].alternate_spawn_handle >= 0 && Weapons[Weapons[n].alternate_spawn_handle].used)
    SendDlgItemMessage(IDC_SPAWN2_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Weapons[Weapons[n].alternate_spawn_handle].name);
  else {
    SendDlgItemMessage(IDC_SPAWN2_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");
    Weapons[n].alternate_spawn_handle = -1;
  }

  // Do spawn robot stuff
  SendDlgItemMessage(IDC_SPAWN_ROBOT_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (int i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type == OBJ_ROBOT)
      SendDlgItemMessage(IDC_SPAWN_ROBOT_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[i].name);
  }

  if (Weapons[n].robot_spawn_handle >= 0 && Object_info[Weapons[n].robot_spawn_handle].type == OBJ_ROBOT)
    SendDlgItemMessage(IDC_SPAWN_ROBOT_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)Object_info[Weapons[n].robot_spawn_handle].name);
  else {
    SendDlgItemMessage(IDC_SPAWN_ROBOT_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "\0");
    Weapons[n].robot_spawn_handle = -1;
  }

  CheckDlgButton(IDC_WEAPON_HOMING_CHECK, Weapons[n].phys_info.flags & PF_HOMING ? 1 : 0);

  CheckDlgButton(IDC_WEAPON_COLLIDE_WITH_SIBLING_CHECK, Weapons[n].phys_info.flags & PF_HITS_SIBLINGS ? 1 : 0);
  CheckDlgButton(IDC_WEAPON_USE_PARENT_VELOCITY_CHECK, Weapons[n].phys_info.flags & PF_USES_PARENT_VELOCITY ? 1 : 0);
  CheckDlgButton(IDC_SMOKE_CHECK, Weapons[n].flags & WF_SMOKE ? 1 : 0);
  CheckDlgButton(IDC_PLANAR_SMOKE_CHECK, Weapons[n].flags & WF_PLANAR_SMOKE ? 1 : 0);

  CheckDlgButton(IDC_NO_ROTATE_CHECK, Weapons[n].flags & WF_NO_ROTATE ? 1 : 0);
  CheckDlgButton(IDC_CUSTOM_SIZE_CHECK, Weapons[n].flags & WF_CUSTOM_SIZE ? 1 : 0);
  CheckDlgButton(IDC_HOMED_SPLIT_CHECK, Weapons[n].flags & WF_HOMING_SPLIT ? 1 : 0);
  CheckDlgButton(IDC_SILENT_HOMING_CHECK, Weapons[n].flags & WF_SILENT_HOMING ? 1 : 0);
  CheckDlgButton(IDC_TIMEOUT_WALL_CHECK, Weapons[n].flags & WF_TIMEOUT_WALL ? 1 : 0);
  CheckDlgButton(IDC_FREEZE_CHECK, Weapons[n].flags & WF_FREEZE ? 1 : 0);
  CheckDlgButton(IDC_COUNTERMEASURE_CHECK, Weapons[n].flags & WF_COUNTERMEASURE ? 1 : 0);
  CheckDlgButton(IDC_SPAWNS_ROBOT_CHECK, Weapons[n].flags & WF_SPAWNS_ROBOT ? 1 : 0);
  CheckDlgButton(IDC_GRAVITY_FIELD_CHECK, Weapons[n].flags & WF_GRAVITY_FIELD ? 1 : 0);
  CheckDlgButton(IDC_MATTER_RADIO, Weapons[n].flags & WF_MATTER_WEAPON ? 1 : 0);
  CheckDlgButton(IDC_ENERGY_RADIO, (Weapons[n].flags & WF_MATTER_WEAPON) == 0 ? 1 : 0);
  CheckDlgButton(IDC_ELECTRICAL_CHECK, (Weapons[n].flags & WF_ELECTRICAL) ? 1 : 0);
  CheckDlgButton(IDC_SPRAY_CHECK, (Weapons[n].flags & WF_SPRAY) ? 1 : 0);
  CheckDlgButton(IDC_INSTANT_CHECK, (Weapons[n].flags & WF_STREAMER) ? 1 : 0);
  CheckDlgButton(IDC_MUZZLE_FLASH, (Weapons[n].flags & WF_MUZZLE) ? 1 : 0);
  CheckDlgButton(IDC_MICROWAVE, (Weapons[n].flags & WF_MICROWAVE) ? 1 : 0);
  CheckDlgButton(IDC_NAPALM, (Weapons[n].flags & WF_NAPALM) ? 1 : 0);
  CheckDlgButton(IDC_INVISIBLE, (Weapons[n].flags & WF_INVISIBLE) ? 1 : 0);
  CheckDlgButton(IDC_RING, (Weapons[n].flags & WF_RING) ? 1 : 0);
  CheckDlgButton(IDC_EXPLODE_RING, (Weapons[n].flags & WF_BLAST_RING) ? 1 : 0);
  CheckDlgButton(IDC_SATURATE_CHECK, (Weapons[n].flags & WF_SATURATE) ? 1 : 0);
  CheckDlgButton(IDC_PLANAR_CHECK, (Weapons[n].flags & WF_PLANAR) ? 1 : 0);
  CheckDlgButton(IDC_EXPANDING_CHECK, (Weapons[n].flags & WF_EXPAND) ? 1 : 0);
  CheckDlgButton(IDC_PLANAR_BLAST, (Weapons[n].flags & WF_PLANAR_BLAST) ? 1 : 0);
  CheckDlgButton(IDC_ENABLE_CAMERA, (Weapons[n].flags & WF_ENABLE_CAMERA) ? 1 : 0);
  CheckDlgButton(IDC_SPAWNS_ON_IMPACT, (Weapons[n].flags & WF_SPAWNS_IMPACT) ? 1 : 0);
  CheckDlgButton(IDC_SPAWNS_ON_TIMEOUT, (Weapons[n].flags & WF_SPAWNS_TIMEOUT) ? 1 : 0);
  CheckDlgButton(IDC_REVERSE_SMOKE_CHECK, (Weapons[n].flags & WF_REVERSE_SMOKE) ? 1 : 0);

  ebox = (CEdit *)GetDlgItem(IDC_GRAVITY_SIZE);
  sprintf(str, "%f", Weapons[n].gravity_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_GRAVITY_TIME);
  sprintf(str, "%f", Weapons[n].gravity_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_DAMAGE_EDIT);
  sprintf(str, "%f", Weapons[n].player_damage);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_GENERIC_DAMAGE_EDIT);
  sprintf(str, "%f", Weapons[n].generic_damage);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_BLOB_SIZE_EDIT);
  sprintf(str, "%f", Weapons[n].size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_SCORCH_SIZE_EDIT);
  sprintf(str, "%f", Weapons[n].scorch_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_ALTERNATE_CHANCE_EDIT);
  sprintf(str, "%d", Weapons[n].alternate_chance);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_ALPHA_EDIT);
  sprintf(str, "%f", Weapons[n].alpha);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_EXPLODE_TIME_EDIT);
  sprintf(str, "%f", Weapons[n].explode_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_SPAWN_EDIT);
  sprintf(str, "%d", Weapons[n].spawn_count);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_EXPLODE_SIZE_EDIT);
  sprintf(str, "%f", Weapons[n].explode_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_PARTICLE_SIZE_EDIT);
  sprintf(str, "%f", Weapons[n].particle_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_PARTICLE_LIFE_EDIT);
  sprintf(str, "%f", Weapons[n].particle_life);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_PARTICLE_COUNT_EDIT);
  sprintf(str, "%d", Weapons[n].particle_count);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_DEFAULT_SIZE);
  if ((Weapons[n].flags & WF_IMAGE_BITMAP) || (Weapons[n].flags & WF_IMAGE_VCLIP)) {
    ebox->EnableWindow(FALSE);
    ebox = (CEdit *)GetDlgItem(IDC_SIZE_MESSAGE);
    ebox->SetWindowText(" ");
  } else {
    ebox->EnableWindow(TRUE);
    ebox = (CEdit *)GetDlgItem(IDC_SIZE_MESSAGE);

    PageInPolymodel(Weapons[n].fire_image_handle);

    if (Poly_models[Weapons[n].fire_image_handle].new_style &&
        (Poly_models[Weapons[n].fire_image_handle].flags & PMF_TIMED)) {
      float temp_size;

      if (Weapons[n].size != ComputeDefaultSize(OBJ_WEAPON, Weapons[n].fire_image_handle, &temp_size))
        ebox->SetWindowText("Using custom size");
      else
        ebox->SetWindowText("Using model size");
    } else
      ebox->SetWindowText("Not timed .oof");
  }

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_SIZE_EDIT);
  sprintf(str, "%f", Weapons[n].impact_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_TIME_EDIT2);
  sprintf(str, "%f", Weapons[n].impact_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_DAMAGE_EDIT);
  sprintf(str, "%f", Weapons[n].impact_player_damage);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_GENERIC_DAMAGE_EDIT);
  sprintf(str, "%f", Weapons[n].impact_generic_damage);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_FORCE_EDIT);
  sprintf(str, "%f", Weapons[n].impact_force);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_THRUST_TIME_EDIT);
  sprintf(str, "%f", Weapons[n].thrust_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_RECOIL_FORCE_EDIT);
  sprintf(str, "%f", Weapons[n].recoil_force);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_HOMING_FOV_TEXT);
  sprintf(str, "%f", acos(Weapons[n].homing_fov) * (360.0 / PI));
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_CUSTOM_SIZE_EDIT);
  sprintf(str, "%f", Weapons[n].custom_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_LIFE_TIME_EDIT);
  sprintf(str, "%f", Weapons[n].life_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_TERRIAN_DAMAGE_SIZE);
  sprintf(str, "%f", Weapons[n].terrain_damage_size);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_TERRAIN_DAMAGE_DEPTH);
  sprintf(str, "%d", Weapons[n].terrain_damage_depth);
  ebox->SetWindowText(str);

  UpdateWeaponView();
}

void CWorldWeaponsDialog::UpdateWeaponView() {
  int n = D3EditState.current_weapon;
  CWnd *weaponwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  static int frame = 0;
  static int last_weapon = -1;
  static int last_image_handle = -1;
  int clearit = 0;

  if (Num_weapons < 1)
    return;

  frame++;

  weaponwnd = GetDlgItem(IDC_WEAPONVIEW);
  weaponwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  if (last_weapon != n || last_image_handle != Weapons[n].hud_image_handle) {
    Desktop_surf->clear(rect.left, rect.top, w, h);
    last_weapon = n;
    last_image_handle = Weapons[n].hud_image_handle;
    clearit = 1;
  }

  bm_handle = GetWeaponHudImage(n, frame);

  m_WeaponSurf.create(128, 128, bm_bpp(bm_handle));
  m_WeaponSurf.load(bm_handle);

  x = rect.left + ((rect.right - rect.left) / 2) - m_WeaponSurf.width() / 2;
  y = rect.top + ((rect.bottom - rect.top) / 2) - m_WeaponSurf.height() / 2;

  Desktop_surf->blt(x, y, &m_WeaponSurf);
  m_WeaponSurf.free();

  weaponwnd = GetDlgItem(IDC_WEAPONFIREVIEW);
  weaponwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  if (clearit)
    Desktop_surf->clear(rect.left, rect.top, w, h);

  bm_handle = GetWeaponFireImage(n, frame);

  if ((Weapons[n].flags & WF_IMAGE_BITMAP) || (Weapons[n].flags & WF_IMAGE_VCLIP)) {
    m_WeaponSurf.create(bm_w(bm_handle, 0), bm_h(bm_handle, 0), bm_bpp(bm_handle));
    m_WeaponSurf.load(bm_handle);

    x = rect.left + ((rect.right - rect.left) / 2) - m_WeaponSurf.width() / 2;
    y = rect.top + ((rect.bottom - rect.top) / 2) - m_WeaponSurf.height() / 2;

    Desktop_surf->blt(x, y, &m_WeaponSurf);
    m_WeaponSurf.free();
  } else {
    vector zero_vector;
    vector view_vector = {0, 0, -2};
    matrix id_matrix, rot_matrix;

    vm_MakeZero(&zero_vector);
    vm_MakeIdentity(&id_matrix);
    vm_AnglesToMatrix(&rot_matrix, 0, frame * 400, 0);

    m_WeaponSurf.create(128, 128, BPP_16);
    grViewport *vport = new grViewport(&m_WeaponSurf);
    StartEditorFrame(vport, &view_vector, &id_matrix, D3_DEFAULT_ZOOM);
    DrawPolygonModel(&zero_vector, &rot_matrix, bm_handle, NULL, 0, 1.0, 1.0, 1.0);
    EndEditorFrame();

    x = rect.left + ((rect.right - rect.left) / 2) - m_WeaponSurf.width() / 2;
    y = rect.top + ((rect.bottom - rect.top) / 2) - m_WeaponSurf.height() / 2;
    Desktop_surf->blt(x, y, &m_WeaponSurf);

    delete vport;
    m_WeaponSurf.free();
  }

  Desktop_surf->attach_to_window((unsigned)NULL);
}

BOOL CWorldWeaponsDialog::DestroyWindow() {
  // TODO: Add your specialized code here and/or call the base class

  SaveWeaponsOnClose();
  return CDialog::DestroyWindow();
}

BOOL CWorldWeaponsDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  CWnd::SetTimer(1, 50, NULL);

  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorldWeaponsDialog::OnTimer(UINT nIDEvent) {
  // TODO: Add your message handler code here and/or call default

  UpdateWeaponView();

  CDialog::OnTimer(nIDEvent);
}

void CWorldWeaponsDialog::OnLoadWeaponDischarge() {
  char filename[255];
  int bm_handle;
  int model = 0;
  int anim = 0;

  CString filter =
      "Descent III files "
      "(*.oaf,*.ifl,*.tga,*.bbm,*.lbm,*.ogf,*.pcx,*.pof,*.oof)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.pof;*.oof;*.oaf;*.ifl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_weapon_dir, sizeof(Current_weapon_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  bm_handle = LoadWeaponFireImage(filename, &model, &anim, 0);

  if (bm_handle < 0) {
    OutrageMessageBox("Could not load that image...restoring previous image.");
    return;
  }
  int n = D3EditState.current_weapon;

  Weapons[n].fire_image_handle = bm_handle;

  if (!model) {
    if (anim) {
      Weapons[n].flags |= WF_IMAGE_VCLIP;
      Weapons[n].flags &= ~WF_IMAGE_BITMAP;
    } else {
      Weapons[n].flags |= WF_IMAGE_BITMAP;
      Weapons[n].flags &= ~WF_IMAGE_VCLIP;
    }
  } else {
    Weapons[n].flags &= ~WF_IMAGE_BITMAP;
    Weapons[n].flags &= ~WF_IMAGE_VCLIP;
    Weapons[n].flags &= ~WF_ELECTRICAL;
  }

  mprintf(0, "Making a copy of this bitmap/model locally...\n");

  if (!model) {
    if (!anim) {
      sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
        GameBitmaps[Weapons[n].fire_image_handle].name);
      bm_SaveFileBitmap(filename, Weapons[n].fire_image_handle);
    } else {
      sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
        GameVClips[Weapons[n].fire_image_handle].name);
      SaveVClip(filename, Weapons[n].fire_image_handle);
    }
  } else {
    std::filesystem::path destname = LocalModelsDir / Poly_models[Weapons[n].fire_image_handle].name;
    cf_CopyFile(destname, filename);
  }

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokFireSoundPulldown() {
  int cur;
  char name[200];
  int n = D3EditState.current_weapon;

  cur = SendDlgItemMessage(IDC_FIRE_SOUND_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_FIRE_SOUND_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].sounds[WSI_FIRE] = FindSoundName(name);
}

void CWorldWeaponsDialog::OnSelendokWeaponWallSoundPulldown() {
  int cur;
  char name[200];
  int n = D3EditState.current_weapon;

  cur = SendDlgItemMessage(IDC_WEAPON_WALL_SOUND_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_WEAPON_WALL_SOUND_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].sounds[WSI_IMPACT_WALL] = FindSoundName(name);
}

BOOL CWorldWeaponsDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  WinHelp(HID_WEAPONSDLG, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CWorldWeaponsDialog::OnWeaponHomingCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_WEAPON_HOMING_CHECK);

  if (c)
    Weapons[n].phys_info.flags |= PF_HOMING;
  else
    Weapons[n].phys_info.flags &= ~PF_HOMING;
}

void CWorldWeaponsDialog::OnWeaponCollideWithSiblingCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_WEAPON_COLLIDE_WITH_SIBLING_CHECK);

  if (c)
    Weapons[n].phys_info.flags |= PF_HITS_SIBLINGS;
  else
    Weapons[n].phys_info.flags &= ~PF_HITS_SIBLINGS;
}

void CWorldWeaponsDialog::OnWeaponUseParentVelocityCheck() {
  // TODO: Add your control notification handler code here
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_WEAPON_USE_PARENT_VELOCITY_CHECK);

  if (c)
    Weapons[n].phys_info.flags |= PF_USES_PARENT_VELOCITY;
  else
    Weapons[n].phys_info.flags &= ~PF_USES_PARENT_VELOCITY;
}

void CWorldWeaponsDialog::OnKillfocusWeaponBlobSizeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_BLOB_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].size = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponImpactSizeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].impact_size = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponThrustTimeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_THRUST_TIME_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].thrust_time = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponLifeTimeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_LIFE_TIME_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].life_time = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponDamageEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;
  float val;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_DAMAGE_EDIT);
  ebox->GetWindowText(str, 20);

  val = atof(str);
  if (val < -200)
    val = -200.0f;
  if (val > 4000.0)
    val = 4000.0f;
  Weapons[n].player_damage = val;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnSmokeCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SMOKE_CHECK);

  if (c)
    Weapons[n].flags |= WF_SMOKE;
  else
    Weapons[n].flags &= ~WF_SMOKE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnEditPhysics() {
  int n = D3EditState.current_weapon;

  CPhysicsDlg dlg(&Weapons[n].phys_info);

  dlg.DoModal();
}

// Gets a name from the user, making sure it's unique
// Returns true if got new name, false if cancelled.
// the data in buf not changed if cancel is pressed
bool InputWeaponName(char *buf, int len, char *title, char *prompt, CWnd *wnd) {
  char *tempbuf = (char *)mem_malloc(len);

  strcpy(tempbuf, buf);

try_again:

  if (!InputString(tempbuf, len, title, prompt, wnd)) {
    mem_free(tempbuf);
    return 0;
  }

  if (FindWeaponName(tempbuf) != -1) {
    OutrageMessageBox("The name you specified is already in use.  Enter another name.");
    goto try_again;
  }

  strcpy(buf, tempbuf);
  mem_free(tempbuf);

  return 1;
}

void CWorldWeaponsDialog::OnChangeName() {
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;
  int n = D3EditState.current_weapon;

  // Make sure we have this ship locked, if not reset name and bail
  int p = mng_FindTrackLock(Weapons[n].name, PAGETYPE_WEAPON);
  if (p == -1) {
    OutrageMessageBox("You must lock this weapon if you wish to change its name.");
    return;
  }

  // Get new name
  strcpy(name, Weapons[n].name);
  if (!InputWeaponName(name, sizeof(name), "Weapon name", "Enter a new name for this weapon:", this))
    return;

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Weapons[n].name);
  pl.pagetype = PAGETYPE_WEAPON;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Weapons[n].name, name, PAGETYPE_WEAPON);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Weapons[n].name);
    strcpy(Weapons[n].name, name);

    mng_ReplacePage(oldname, Weapons[n].name, n, PAGETYPE_WEAPON, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Weapons[n].name, name);
  mng_EraseLocker();

  RemapWeapons();

  // check to see if current has been remapped
  if (!Weapons[n].used)
    D3EditState.current_weapon = GetNextWeapon(n);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnWeaponLightInfo() {
  int n = D3EditState.current_weapon;

  CGenericLightDialog dlg(&Weapons[n].lighting_info);
  dlg.DoModal();

  UpdateDialog();
}

void CWorldWeaponsDialog::OnEnergyRadio() {
  int n = D3EditState.current_weapon;

  Weapons[n].flags &= ~WF_MATTER_WEAPON;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnMatterRadio() {
  int n = D3EditState.current_weapon;

  Weapons[n].flags |= WF_MATTER_WEAPON;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnElectricalCheck() {

  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_ELECTRICAL_CHECK);

  if (!((Weapons[n].flags & WF_IMAGE_BITMAP) || (Weapons[n].flags & WF_IMAGE_VCLIP))) {
    mprintf(0, "The firing image must be a bitmap(not a model) for 'electrical' to work!\n");
    return;
  }

  if (c)
    Weapons[n].flags |= WF_ELECTRICAL;
  else
    Weapons[n].flags &= ~WF_ELECTRICAL;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnDefaultSize() {
  int n = D3EditState.current_weapon;
  poly_model *pm = GetPolymodelPointer(Weapons[n].fire_image_handle);

  if (!pm->new_style || !(pm->flags & PMF_TIMED)) {
    OutrageMessageBox("This model must be a timed oof for this function to work!");
    return;
  }

  ComputeDefaultSize(OBJ_WEAPON, Weapons[n].fire_image_handle, &Weapons[n].size);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponImpactTimeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_FORCE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].impact_force = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokSmokePulldown() {
  int n = D3EditState.current_weapon;

  if (!(Weapons[n].flags & WF_SMOKE))
    return;

  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SMOKE_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SMOKE_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].smoke_handle = FindTextureName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokScorchPulldown() {
  int n = D3EditState.current_weapon;
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SCORCH_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  if (strcmp(name, NULL_NAME) == 0)
    Weapons[n].scorch_handle = -1;
  else
    Weapons[n].scorch_handle = FindTextureName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokExplodePulldown() {
  int n = D3EditState.current_weapon;

  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_EXPLODE_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_EXPLODE_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].explode_image_handle = FindTextureName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSprayCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SPRAY_CHECK);

  if (!(Weapons[n].flags & WF_IMAGE_VCLIP)) {
    mprintf(0, "The firing image must be a bitmap(not a model) for spray to work!\n");
    return;
  }

  if (c)
    Weapons[n].flags |= WF_SPRAY;
  else
    Weapons[n].flags &= ~WF_SPRAY;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnInstantCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_INSTANT_CHECK);

  if (c)
    Weapons[n].flags |= WF_STREAMER;
  else
    Weapons[n].flags &= ~WF_STREAMER;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnInvisible() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_INVISIBLE);

  if (c)
    Weapons[n].flags |= WF_INVISIBLE;
  else
    Weapons[n].flags &= ~WF_INVISIBLE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnRing() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_RING);

  if (c)
    Weapons[n].flags |= WF_RING;
  else
    Weapons[n].flags &= ~WF_RING;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnExplodeRing() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_EXPLODE_RING);

  if (c)
    Weapons[n].flags |= WF_BLAST_RING;
  else
    Weapons[n].flags &= ~WF_BLAST_RING;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnPlanarBlast() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_PLANAR_BLAST);

  if (c)
    Weapons[n].flags |= WF_PLANAR_BLAST;
  else
    Weapons[n].flags &= ~WF_PLANAR_BLAST;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSaturateCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SATURATE_CHECK);

  if (c)
    Weapons[n].flags |= WF_SATURATE;
  else
    Weapons[n].flags &= ~WF_SATURATE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponAlphaEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_ALPHA_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].alpha = atof(str);
  if (Weapons[n].alpha < 0)
    Weapons[n].alpha = 0;
  if (Weapons[n].alpha > 1)
    Weapons[n].alpha = 1;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnPlanarCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_PLANAR_CHECK);

  if (c)
    Weapons[n].flags |= WF_PLANAR;
  else
    Weapons[n].flags &= ~WF_PLANAR;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusExplodeSizeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_EXPLODE_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].explode_size = atof(str);
  if (Weapons[n].explode_size < 0)
    Weapons[n].explode_size = 0;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusExplodeTimeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_EXPLODE_TIME_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].explode_time = atof(str);
  if (Weapons[n].explode_time < 0)
    Weapons[n].explode_time = 0;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnEnableCamera() {
  CButton *btn;
  int n = D3EditState.current_weapon;

  btn = (CButton *)GetDlgItem(IDC_ENABLE_CAMERA);

  if (btn->GetCheck())
    Weapons[n].flags |= WF_ENABLE_CAMERA;
  else
    Weapons[n].flags &= ~WF_ENABLE_CAMERA;
}

void CWorldWeaponsDialog::OnSelendokWeaponSpawnPulldown() {
  int n = D3EditState.current_weapon;

  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_WEAPON_SPAWN_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_WEAPON_SPAWN_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].spawn_handle = FindWeaponName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponSpawnEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_SPAWN_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].spawn_count = atoi(str);

  if (Weapons[n].spawn_count < 0)
    Weapons[n].spawn_count = 0;
  if (Weapons[n].spawn_count > 20)
    Weapons[n].spawn_count = 20;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSpawnsOnImpact() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SPAWNS_ON_IMPACT);

  if (c)
    Weapons[n].flags |= WF_SPAWNS_IMPACT;
  else
    Weapons[n].flags &= ~WF_SPAWNS_IMPACT;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSpawnsOnTimeout() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SPAWNS_ON_TIMEOUT);

  if (c)
    Weapons[n].flags |= WF_SPAWNS_TIMEOUT;
  else
    Weapons[n].flags &= ~WF_SPAWNS_TIMEOUT;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnOverride() {
  int n = D3EditState.current_weapon;
  mngs_Pagelock temp_pl;

  strcpy(temp_pl.name, Weapons[n].name);
  temp_pl.pagetype = PAGETYPE_WEAPON;

  mng_OverrideToUnlocked(&temp_pl);
}

void CWorldWeaponsDialog::OnKillfocusParticleCountEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_PARTICLE_COUNT_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].particle_count = atoi(str);
  if (Weapons[n].particle_count < 0)
    Weapons[n].particle_count = 0;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusParticleLifeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_PARTICLE_LIFE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].particle_life = atof(str);
  if (Weapons[n].particle_life < 0)
    Weapons[n].particle_life = 0;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusParticleSizeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_PARTICLE_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].particle_size = atof(str);
  if (Weapons[n].particle_size < 0)
    Weapons[n].particle_size = 0;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokParticlePulldown() {
  int n = D3EditState.current_weapon;

  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_PARTICLE_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_PARTICLE_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].particle_handle = FindTextureName(name);

  UpdateDialog();
}

weapon WeaponCopyBuffer;
bool f_has_weapon = false;

void CWorldWeaponsDialog::OnWeaponCopyButton() {
  int n = D3EditState.current_weapon;

  WeaponCopyBuffer = Weapons[n];
  f_has_weapon = true;
}

void CWorldWeaponsDialog::OnWeaponPasteButton() {
  int n = D3EditState.current_weapon;
  char name[256];

  strcpy(name, Weapons[n].name);

  if (f_has_weapon) {
    Weapons[n] = WeaponCopyBuffer;
    strcpy(Weapons[n].name, name);

    UpdateDialog();
  } else {
    OutrageMessageBox(MB_OK, "No weapon in paste buffer.\n");
  }
}

void CWorldWeaponsDialog::OnExpandingCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_EXPANDING_CHECK);

  if (c)
    Weapons[n].flags |= WF_EXPAND;
  else
    Weapons[n].flags &= ~WF_EXPAND;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnMuzzleFlash() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_MUZZLE_FLASH);

  if (c)
    Weapons[n].flags |= WF_MUZZLE;
  else
    Weapons[n].flags &= ~WF_MUZZLE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnMicrowave() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_MICROWAVE);

  if (c)
    Weapons[n].flags |= WF_MICROWAVE;
  else
    Weapons[n].flags &= ~WF_MICROWAVE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnNapalm() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_NAPALM);

  if (c)
    Weapons[n].flags |= WF_NAPALM;
  else
    Weapons[n].flags &= ~WF_NAPALM;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokWeaponBounceSoundCombo() {
  int cur;
  char name[200];
  int n = D3EditState.current_weapon;

  cur = SendDlgItemMessage(IDC_WEAPON_BOUNCE_SOUND_COMBO, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_WEAPON_BOUNCE_SOUND_COMBO, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].sounds[WSI_BOUNCE] = FindSoundName(name);
}

void CWorldWeaponsDialog::OnKillfocusWeaponImpactTimeEdit2() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_TIME_EDIT2);
  ebox->GetWindowText(str, 20);

  Weapons[n].impact_time = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponImpactDamageEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_DAMAGE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].impact_player_damage = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponImpactForceEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_FORCE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].impact_force = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponScorchSizeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_SCORCH_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].scorch_size = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokSmallimgPulldown() {
  int n = D3EditState.current_weapon;
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SMALLIMG_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  if (strcmp(name, NULL_NAME) == 0)
    Weapons[n].icon_handle = -1;
  else
    Weapons[n].icon_handle = FindTextureName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokSpawn2Pulldown() {
  int n = D3EditState.current_weapon;

  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SPAWN2_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SPAWN2_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].alternate_spawn_handle = FindWeaponName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusAlternateChanceEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;
  int val;

  ebox = (CEdit *)GetDlgItem(IDC_ALTERNATE_CHANCE_EDIT);
  ebox->GetWindowText(str, 20);

  val = atoi(str);
  if (val < 0 || val > 100) {
    OutrageMessageBox("Alternate chance value must be between 0 and 100!");

  } else {
    Weapons[n].alternate_chance = val;
  }

  UpdateDialog();
}

void CWorldWeaponsDialog::OnReverseSmokeCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_REVERSE_SMOKE_CHECK);

  if (c)
    Weapons[n].flags |= WF_REVERSE_SMOKE;
  else
    Weapons[n].flags &= ~WF_REVERSE_SMOKE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnGravityFieldCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_GRAVITY_FIELD_CHECK);

  if (c)
    Weapons[n].flags |= WF_GRAVITY_FIELD;
  else
    Weapons[n].flags &= ~WF_GRAVITY_FIELD;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusGravitySize() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_GRAVITY_SIZE);
  ebox->GetWindowText(str, 20);

  Weapons[n].gravity_size = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusGravityTime() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_GRAVITY_TIME);
  ebox->GetWindowText(str, 20);

  Weapons[n].gravity_time = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnCountermeasureCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_COUNTERMEASURE_CHECK);

  if (c)
    Weapons[n].flags |= WF_COUNTERMEASURE;
  else
    Weapons[n].flags &= ~WF_COUNTERMEASURE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSpawnsRobotCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SPAWNS_ROBOT_CHECK);

  if (c)
    Weapons[n].flags |= WF_SPAWNS_ROBOT;
  else
    Weapons[n].flags &= ~WF_SPAWNS_ROBOT;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSelendokSpawnRobotPulldown() {
  int n = D3EditState.current_weapon;

  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SPAWN_ROBOT_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SPAWN_ROBOT_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Weapons[n].robot_spawn_handle = FindObjectIDName(name);

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusTerrianDamageSize() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_TERRIAN_DAMAGE_SIZE);
  ebox->GetWindowText(str, 20);

  float val = atof(str);
  if (val < 0)
    val = 0;
  if (val > 100)
    val = 100;

  Weapons[n].terrain_damage_size = val;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusTerrainDamageDepth() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_TERRAIN_DAMAGE_DEPTH);
  ebox->GetWindowText(str, 20);

  int val = atoi(str);
  if (val < 0)
    val = 0;
  if (val > 255)
    val = 255;

  Weapons[n].terrain_damage_depth = val;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnFreezeCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_FREEZE_CHECK);

  if (c)
    Weapons[n].flags |= WF_FREEZE;
  else
    Weapons[n].flags &= ~WF_FREEZE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnSilentHomingCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_SILENT_HOMING_CHECK);

  if (c)
    Weapons[n].flags |= WF_SILENT_HOMING;
  else
    Weapons[n].flags &= ~WF_SILENT_HOMING;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnHomedSplitCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_HOMED_SPLIT_CHECK);

  if (c)
    Weapons[n].flags |= WF_HOMING_SPLIT;
  else
    Weapons[n].flags &= ~WF_HOMING_SPLIT;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusHomingFovText() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_HOMING_FOV_TEXT);
  ebox->GetWindowText(str, 20);

  Weapons[n].homing_fov = cos(atof(str) * PI / (360.0));
  UpdateDialog();
}

void CWorldWeaponsDialog::OnNoRotateCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_NO_ROTATE_CHECK);

  if (c)
    Weapons[n].flags |= WF_NO_ROTATE;
  else
    Weapons[n].flags &= ~WF_NO_ROTATE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnCustomSizeCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_CUSTOM_SIZE_CHECK);

  if (c)
    Weapons[n].flags |= WF_CUSTOM_SIZE;
  else
    Weapons[n].flags &= ~WF_CUSTOM_SIZE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusCustomSizeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_CUSTOM_SIZE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].custom_size = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnTimeoutWallCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_TIMEOUT_WALL_CHECK);

  if (c)
    Weapons[n].flags |= WF_TIMEOUT_WALL;
  else
    Weapons[n].flags &= ~WF_TIMEOUT_WALL;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponGenericDamageEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;
  float val;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_GENERIC_DAMAGE_EDIT);
  ebox->GetWindowText(str, 20);

  val = atof(str);
  if (val < -200)
    val = -200.0f;
  if (val > 4000.0)
    val = 4000.0f;
  Weapons[n].generic_damage = val;
  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponImpactGenericDamageEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_IMPACT_GENERIC_DAMAGE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].impact_generic_damage = atof(str);
  UpdateDialog();
}

void CWorldWeaponsDialog::OnPlanarSmokeCheck() {
  int n = D3EditState.current_weapon;
  int c = IsDlgButtonChecked(IDC_PLANAR_SMOKE_CHECK);

  if (c)
    Weapons[n].flags |= WF_PLANAR_SMOKE;
  else
    Weapons[n].flags &= ~WF_PLANAR_SMOKE;

  UpdateDialog();
}

void CWorldWeaponsDialog::OnKillfocusWeaponRecoilForceEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_weapon;

  ebox = (CEdit *)GetDlgItem(IDC_WEAPON_RECOIL_FORCE_EDIT);
  ebox->GetWindowText(str, 20);

  Weapons[n].recoil_force = atof(str);
  UpdateDialog();
}
