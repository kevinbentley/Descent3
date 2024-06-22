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

 * $Logfile: /DescentIII/Main/D3Launch/AudioTab.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:56:51 $
 * $Author: kevinb $
 *
 *
 *
 * $Log: not supported by cvs2svn $
 *
 * 39    9/29/99 10:39a Nate
 * Aureal OEM now allows other mixers
 *
 * 38    8/19/99 6:13p Samir
 * detect vortex1 chipsets.
 *
 * 37    6/09/99 2:46p Nate
 * Minor changes for different builds
 *
 * 35    5/20/99 1:08p Samir
 * fixed EAX check.
 *
 * 34    5/20/99 12:53p Nate
 * Added GLSetup window, EAX mixer support, and CHFlight+Mouseman Mode
 * options
 *
 * 33    4/27/99 10:41p Nate
 * Added 16bit dsound support
 *
 * 32    3/29/99 4:34p Samir
 * better checking of results from Aureal initialization.
 *
 * 31    3/29/99 4:25p Nate
 * changed aureal check.
 *
 * 30    3/29/99 4:08p Samir
 * check for Aureal 2.0 reflections to see if hardware is supported.
 *
 * 29    3/29/99 3:52p Samir
 * Check for occlusions feature in Aureal after initialized.
 *
 * 28    3/29/99 3:21p Samir
 * added aureal 2.0 check.
 *
 * 27    3/29/99 3:14p Nate
 * Added OEM_GENERIC
 *
 * 26    3/04/99 12:07p Nate
 * Made Software the default mixer (if it's available)
 *
 * 25    2/28/99 5:31p Nate
 * Disabled DS3D and Aureal mixers for the Voodoo3 OEM
 *
 * 24    2/05/99 3:51p Nate
 * Added conditional compilation directives for OEM support
 *
 * 23    10/23/98 6:48p Nate
 * more fixes.
 *
 * 22    10/23/98 5:29p Nate
 * Small fixes.
 *
 * 21    10/21/98 4:51p Nate
 * More fixes.
 *
 * 20    10/18/98 2:43p Nate
 * Dimmed D3D and Aureal Mixer options for the demo
 *
 * 19    10/15/98 10:54a Nate
 * Added Launcher Sound toggling
 *
 * 18    10/14/98 5:52p Nate
 * More fixes
 *
 * 17    10/14/98 11:37a Nate
 * Added default to DS8 for Chris
 *
 * 16    10/13/98 3:03p Nate
 * More fixes and changes.
 *
 * 15    10/12/98 8:16p Nate
 * Commented out "old Aureal DLL" messages for now
 *
 * 14    10/12/98 7:13p Nate
 * Fixed several bugs.
 *
 * 13    10/10/98 4:05p Nate
 * Added detection/scanning window messages
 *
 * 12    10/10/98 2:33p Nate
 * More fixes.
 *
 * 11    10/08/98 6:23p Nate
 * Fixed a few bugs.
 *
 * 10    9/25/98 6:57p Nate
 * If no card is in registry, the list box now defaults to none.
 *
 * 9     9/22/98 3:33p Nate
 * Added conditional compiling to help system (can toggle between HTML and
 * standard windows help)
 *
 * 8     9/21/98 5:40p Nate
 * Incorporated the new HTML help system
 *
 * 7     9/21/98 12:12p Nate
 * Changed "Soundcard" registry value name to "SoundcardName"
 *
 * 6     9/01/98 7:15p Nate
 * Major Revision #2
 *
 * 5     8/31/98 6:44p Nate
 * Major Revision
 *
 * 4     8/10/98 10:44a Nate
 * Added Language selection support
 *
 * 3     8/05/98 4:52p Nate
 * Added registry reading and writing.
 *
 * 2     8/05/98 11:54a Nate
 * Initial Version
 *
 * $NoKeywords: $
 */

// AudioTab.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "afxext.h"
#include "D3Launch.h"
#include "D3LaunchDlg.h"
#include "AudioTab.h"

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <objbase.h>
#include <initguid.h>

#include "ia3dapi.h"
#include "ia3dutil.h"
#include "eax.h"

#include "OS_Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_CARDS 32

#define SBT_PRIMARY 0

// Supported sound mixers (for saving to registry)
#define SOUND_MIXER_SOFTWARE_16 0
#define SOUND_MIXER_DS_16 1
#define SOUND_MIXER_DS_8 2
#define SOUND_MIXER_DS3D_16 3
#define SOUND_MIXER_AUREAL_16 4
#define SOUND_MIXER_NONE 5
#define SOUND_MIXER_EAX 6

// Setup available mixer flags
#define SOFTWARE_MIXER 0x01
#define DS8BIT_MIXER 0x02
#define DS16BIT_MIXER 0x04
#define DS3D_MIXER 0x08
#define AUREAL_MIXER 0x10 // Unused
#define EAX_MIXER 0x20

struct SoundCard {
  GUID guid;
  LPGUID pguid;

  char name[1024]; // Name of the device
  UINT mixers;     // Mixers supported by device
};

static SoundCard Cards[MAX_CARDS];
static int Num_cards;

// the callback for the DirectSound enumeration process
BOOL WINAPI dsound_enum_callback(GUID FAR *lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPVOID lpContext) {
  SoundCard *card = &Cards[Num_cards++];

  if (lpGuid) {
    memmove(&card->guid, lpGuid, sizeof(GUID));
    card->pguid = &card->guid;
  } else {
    memset(&card->guid, 0, sizeof(GUID));
    card->pguid = NULL;
  }

  // Save name of device
  sprintf(card->name, "%s", lpDeviceDescription);

  return TRUE;
}

// Creates a  Primary direct sound buffer
HRESULT
CreateDSBuffer(LPDIRECTSOUND lpDirectSound, int buffer_type, LPDIRECTSOUNDBUFFER *lp_lp_dsb, DWORD sound_bytes,
               DWORD frequency, bool f_is_stereo, bool f_is_16_bit, bool positional) {
  DSBUFFERDESC dsbd;
  tWAVEFORMATEX fmt;
  HRESULT result;

  if (frequency != 44100 && frequency != 22050 && frequency != 11025)
    return 0;

  if (lpDirectSound == NULL)
    return 0;

  // Setup the wave format
  fmt.nChannels = (f_is_stereo) ? 2 : 1;
  fmt.wBitsPerSample = (f_is_16_bit) ? 16 : 8;
  fmt.nSamplesPerSec = ((DWORD)frequency);
  fmt.nBlockAlign = fmt.nChannels * (fmt.wBitsPerSample >> 3);
  fmt.nAvgBytesPerSec = ((DWORD)fmt.nSamplesPerSec) * ((DWORD)fmt.nBlockAlign);
  fmt.wFormatTag = WAVE_FORMAT_PCM;

  // Setup the secondary direct sound buffer
  memset(&dsbd, 0, sizeof(dsbd));
  dsbd.lpwfxFormat = (LPWAVEFORMATEX)&fmt;
  dsbd.dwSize = sizeof(DSBUFFERDESC);
  dsbd.dwBufferBytes = sound_bytes;

  // Setup for Software 16 bit mixer
  dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2;

  if (buffer_type != SBT_PRIMARY)
    return 0;

  // m_primary_frequency = m_current_frequency = frequency;
  // m_primary_bit_depth = fmt.wBitsPerSample;
  // m_primary_alignment   = fmt.nBlockAlign;

  dsbd.lpwfxFormat = NULL;
  dsbd.dwBufferBytes = 0;
  dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_GETCURRENTPOSITION2;
  if (positional) {
    dsbd.dwFlags |= DSBCAPS_CTRL3D;
  }

  // Create the buffer
  result = lpDirectSound->CreateSoundBuffer(&dsbd, lp_lp_dsb, 0);

  if (result == DS_OK && buffer_type == SBT_PRIMARY) {
    // Succeeded. Set primary buffer to desired format.
    result = (*lp_lp_dsb)->SetFormat(&fmt);
  }

  return result;
}

BOOL CreativeEAXCheck(LPDIRECTSOUND lpds) {
  BOOL retval = FALSE;
  DWORD properties = 0;
  ULONG ulAnswer = 0;
  LPKSPROPERTYSET lpksps = NULL;
  WAVEFORMATEX wave;
  DSBUFFERDESC dsbdesc;
  LPDIRECTSOUNDBUFFER lpdsb = NULL;

  const DWORD EAX_ENVIRONMENTS_AVAILABLE = 1, EAX_BUFFERMIX_AVAILABLE = 2;

  memset(&wave, 0, sizeof(WAVEFORMATEX));
  wave.wFormatTag = WAVE_FORMAT_PCM;
  wave.nChannels = 1;
  wave.nSamplesPerSec = 11025;
  wave.wBitsPerSample = 8;
  wave.nBlockAlign = wave.wBitsPerSample / 8 * wave.nChannels;
  wave.nAvgBytesPerSec = wave.nSamplesPerSec * wave.nBlockAlign;

  memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
  dsbdesc.dwSize = sizeof(DSBUFFERDESC);
  dsbdesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRL3D;
  dsbdesc.dwBufferBytes = DSBSIZE_MIN * 2;
  dsbdesc.lpwfxFormat = &wave;

  if (FAILED(lpds->CreateSoundBuffer(&dsbdesc, &lpdsb, NULL))) {
    retval = FALSE;
  } else if (FAILED(lpdsb->QueryInterface(IID_IKsPropertySet, (LPVOID *)&lpksps))) {
    retval = FALSE;
  } else if (FAILED(lpksps->QuerySupport(DSPROPSETID_EAX_ReverbProperties, DSPROPERTY_EAX_ALL, &ulAnswer))) {
    retval = FALSE;
  } else {
    if ((ulAnswer & KSPROPERTY_SUPPORT_SET | KSPROPERTY_SUPPORT_GET) ==
        (KSPROPERTY_SUPPORT_SET | KSPROPERTY_SUPPORT_GET)) {
      properties |= EAX_ENVIRONMENTS_AVAILABLE;
      if (FAILED(lpksps->QuerySupport(DSPROPSETID_EAXBUFFER_ReverbProperties, DSPROPERTY_EAXBUFFER_REVERBMIX,
                                      &ulAnswer))) {
        retval = FALSE;
      } else {
        properties |= EAX_BUFFERMIX_AVAILABLE;
      }
    } else {
      retval = FALSE;
    }
  }

  if (lpksps) {
    lpksps->Release();
  }
  if (lpdsb) {
    lpdsb->Release();
  }

  if (properties & (EAX_BUFFERMIX_AVAILABLE + EAX_ENVIRONMENTS_AVAILABLE)) {
    retval = TRUE;
  }

  return retval;
}

// Checks capabilities of given directsound device to see which mixers
// it can handle
bool DetermineMixerOptions(LPDIRECTSOUND lpDirectSound, UINT &mixer_flags) {
  DSCAPS dscaps;
  HRESULT hr;

  // Default to just having DirectSound 8 bit available
  mixer_flags = DS8BIT_MIXER;

  dscaps.dwSize = sizeof(DSCAPS);
  hr = lpDirectSound->GetCaps(&dscaps);
  if (hr != DS_OK) {
    return FALSE;
  }

  /* We have decided to remove Direct Sound mixers as an option
          // Check DirectSound 8 Bit support
          if(dscaps.dwFlags & DSCAPS_PRIMARY8BIT)
                  mixer_flags |= DS8BIT_MIXER;
          else
                  mixer_flags &= ~DS8BIT_MIXER;
  */
  // Check DirectSound 16 Bit support
  if (dscaps.dwFlags & DSCAPS_PRIMARY16BIT)
    mixer_flags |= DS16BIT_MIXER;
  else
    mixer_flags &= ~DS16BIT_MIXER;

#if (!defined(DEMO) && !defined(OEM_VOODOO3))
  // Check DirectSound 3D Bit support
  if (dscaps.dwMaxHw3DAllBuffers > 0)
    mixer_flags |= DS3D_MIXER;
  else
    mixer_flags &= ~DS3D_MIXER;
#endif

  // Check for Software and Creative EAX support
  //////////////////////////////////////////////
  if (dscaps.dwFlags & DSCAPS_EMULDRIVER)
    return TRUE; // In NT or bad sound card, so don't set software flag

  // Set the Cooperative level AND make sure it is ok to do it
  HRESULT scl_status;
  scl_status = lpDirectSound->SetCooperativeLevel(pLaunchDlg->m_hWnd, DSSCL_WRITEPRIMARY);
  if (scl_status != DS_OK)
    return TRUE; // don't set software flag

  // EAX support
  if (CreativeEAXCheck(lpDirectSound)) {
    mixer_flags |= EAX_MIXER;
  }

  // Try and create a buffer
  HRESULT result;
  LPDIRECTSOUNDBUFFER lp_primary_buffer;
  lp_primary_buffer = NULL;

  // test software
  result = CreateDSBuffer(lpDirectSound, SBT_PRIMARY, &lp_primary_buffer, 0, 22050, true, true, false);

  // Make sure buffer was created successfully
  if (lp_primary_buffer == NULL)
    return TRUE;

  if (result != DS_OK) {
    lp_primary_buffer->Release();
    return TRUE;
  }

  // Determine if we are running NT or have a bad Win95 sound card
  {
    DSBCAPS dsbcaps;
    dsbcaps.dwSize = sizeof(DSBCAPS);
    lp_primary_buffer->GetCaps(&dsbcaps);

    // Is you want to see the caps, here is where -- mprintf all you want
    if (!(dsbcaps.dwFlags & DSBCAPS_LOCHARDWARE)) {
      lp_primary_buffer->Release();
      return TRUE;
    }
  }

  // Release the buffer
  lp_primary_buffer->Release();

  // Device passed all four software tests, so set the flag
  mixer_flags |= SOFTWARE_MIXER;

  return TRUE;
}

typedef BOOL(CALLBACK *LPFN_DIRECTSOUNDENUMERATE)(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext);
typedef HRESULT(CALLBACK *LPFN_DIRECTSOUNDCREATE)(GUID FAR *lpGuid, LPDIRECTSOUND *ppDS, IUnknown FAR *pUnkOuter);

// Adds any Direct Sound devices to the list of available sound settings
void check_direct_sound() {
  int j;
  HINSTANCE ds_dll_handle;
  HRESULT dsrval;
  LPFN_DIRECTSOUNDENUMERATE pfn_DirectSoundEnumerate;
  LPFN_DIRECTSOUNDCREATE pfn_DirectSoundCreate;
  LPDIRECTSOUND lpDirectSound;

  ds_dll_handle = LoadLibrary("dsound.dll");
  if (ds_dll_handle == NULL)
    return;

  // Get function pointers from DLL
  pfn_DirectSoundEnumerate = (LPFN_DIRECTSOUNDENUMERATE)GetProcAddress(ds_dll_handle, "DirectSoundEnumerateA");
  if (pfn_DirectSoundEnumerate == NULL) {
    OutputDebugString("Could not find DirectSoundEnumerate()\n");
    goto DSoundCleanup;
  }

  pfn_DirectSoundCreate = (LPFN_DIRECTSOUNDCREATE)GetProcAddress(ds_dll_handle, "DirectSoundCreate");
  if (pfn_DirectSoundCreate == NULL) {
    OutputDebugString("Could not find DirectSoundCreate()\n");
    goto DSoundCleanup;
  }

  // Enumerate sound cards/devices on user's system
  dsrval = pfn_DirectSoundEnumerate((LPDSENUMCALLBACKA)dsound_enum_callback, NULL);
  if (dsrval != DS_OK) {
    OutputDebugString("DirectSoundEnumerate failed.\n");
    goto DSoundCleanup;
  }

  // Evaluate mixer capabilities for each device
  for (j = 1; j < Num_cards; j++) {

    // No matter what, allow default mixer to be selected
    Cards[j].mixers = DS8BIT_MIXER;

    // Initialize Direct sound and get available mixers
    if (DirectSoundCreate(Cards[j].pguid, &lpDirectSound, NULL) == DS_OK) {
      // Creation succeeded.
      // lpDirectSound->lpVtbl->SetCooperativeLevel(lpDirectSound, hwnd, DSSCL_NORMAL);
      // .
      // . Place code to access DirectSound object here.
      // .
      DetermineMixerOptions(lpDirectSound, Cards[j].mixers);
      lpDirectSound->Release();
    } else {
      OutputDebugString("DirectSoundCreate failed.\n");
      // goto DSoundCleanup;
    }

#if (!defined(DEMO) && !defined(OEM_VOODOO3))
    // Try to initialize Aureal 3D sound
    { Cards[j].mixers &= ~AUREAL_MIXER; }
#endif
  }

DSoundCleanup:
  FreeLibrary(ds_dll_handle);
  return;
}

/////////////////////////////////////////////////////////////////////////////
// CAudioTab property page

IMPLEMENT_DYNCREATE(CAudioTab, CPropertyPage)

CAudioTab::CAudioTab() : CPropertyPage(CAudioTab::IDD) {
  //{{AFX_DATA_INIT(CAudioTab)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

CAudioTab::~CAudioTab() {}

// Fills in Cards and Num_cards
void detect_sound_cards(int really_detect) {
  Num_cards = 0;

  CString no_sound_msg;
  no_sound_msg.LoadString(IDS_AUDIOTAB_NO_SOUND);

  // Setup "None" card slot
  strcpy(Cards[Num_cards].name, no_sound_msg);
  Cards[Num_cards].mixers = 0;
  Cards[Num_cards].pguid = NULL;
  memset(&Cards[Num_cards].guid, 0, sizeof(GUID));
  Num_cards++;

  if (really_detect) {
    check_direct_sound();
  }
}

void CAudioTab::DoDataExchange(CDataExchange *pDX) {
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAudioTab)
  DDX_Control(pDX, IDC_LAUNCHER_SND_CHECK, m_LauncherSndCheck);
  DDX_Control(pDX, IDC_AUDIO_LIST, m_audio_list);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAudioTab, CPropertyPage)
//{{AFX_MSG_MAP(CAudioTab)
ON_BN_CLICKED(IDC_BTN_AUDIO_DETECT, OnBtnAudioDetect)
ON_CBN_SELCHANGE(IDC_AUDIO_LIST, OnSelchangeAudioList)
ON_WM_HELPINFO()
ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioTab message handlers

void CAudioTab::OnBtnAudioDetect() {
  // TODO: Add your control notification handler code here
  int i;

  // Set the wait cursor
  CWaitCursor wc;

  // Display the scanning window
  m_MsgDlg.m_ScanningMsg.LoadString(IDS_AUDIOTAB_SCANNING);
  m_MsgDlg.m_WaitMsg.LoadString(IDS_PLEASE_WAIT_MSG);
  m_MsgDlg.Create(IDD_MSG_DLG, this);
  m_MsgDlg.ShowWindow(SW_SHOW);
  m_MsgDlg.UpdateData(FALSE);

  m_audio_list.ResetContent();
  detect_sound_cards(1);

  // Remove the scanning window
  m_MsgDlg.DestroyWindow();

  for (i = 0; i < Num_cards; i++)
    m_audio_list.InsertString(i, Cards[i].name);

  // Set selection and available mixer settings
  m_audio_list.SetCurSel(Num_cards - 1);
  EnableMixerSettings(Cards[Num_cards - 1].mixers);

  // Automatically default to software (if available)
  SetMixerButton(DetermineDefaultMixer(Num_cards - 1), Cards[Num_cards - 1].mixers);
}

void CAudioTab::OnOK() {
  bool ds16_supported;

  int current = m_audio_list.GetCurSel();

  if ((current < 0) || (current >= Num_cards)) {
    current = 0;
  }

  // See if the chosen card supports direct sound 16 bit
  if (Cards[current].mixers & DS16BIT_MIXER)
    ds16_supported = TRUE;
  else
    ds16_supported = FALSE;

  os_config_write_string(szSectionName, "SoundcardName", Cards[current].name);

  int mixer_id;
  mixer_id = GetMixerButton();

  // For Chris, make DS8 be the mixer if user has a card selected
  // (other than No sound) and no sound mixers could be detected for
  // the device
  if (current > 0 && mixer_id == SOUND_MIXER_NONE)
    mixer_id = SOUND_MIXER_DS_8;

  // If user has ds16 support, and has chosen direct sound, use it
  if (mixer_id == SOUND_MIXER_DS_8 && ds16_supported)
    mixer_id = SOUND_MIXER_DS_16;

  // Write out the default mixer
  os_config_write_uint(NULL, "SoundMixer", mixer_id);

  // Write out the Launcher sound setting
  LauncherSoundEnabled = m_LauncherSndCheck.GetCheck();
  os_config_write_uint(szSectionName, "LauncherSoundEnabled", LauncherSoundEnabled);

  CPropertyPage::OnOK();
}

BOOL CAudioTab::OnInitDialog() {
  CPropertyPage::OnInitDialog();

  // TODO: Add extra initialization here
  char *current_card;
  int i, current;
  int allow_user_to_choose_ds3d = 0;
  UINT mixer_id;

  // Set the wait cursor
  CWaitCursor wc;

  // Clear the box
  m_audio_list.ResetContent();

  // Display the scanning window
  m_MsgDlg.m_ScanningMsg.LoadString(IDS_AUDIOTAB_SCANNING);
  m_MsgDlg.m_WaitMsg.LoadString(IDS_PLEASE_WAIT_MSG);
  m_MsgDlg.Create(IDD_MSG_DLG, this);
  m_MsgDlg.ShowWindow(SW_SHOW);
  m_MsgDlg.UpdateData(FALSE);

  // Detect all cards and fill the list
  detect_sound_cards(1);
  for (i = 0; i < Num_cards; i++)
    m_audio_list.InsertString(i, Cards[i].name);

  // Remove the scanning window
  m_MsgDlg.DestroyWindow();

  // Get current card name from the registry
  current_card = os_config_read_string(szSectionName, "SoundcardName", NULL);

  // Get the currently selected mixer
  mixer_id = os_config_read_uint(NULL, "SoundMixer", SOUND_MIXER_NONE);

  current = -1;
  if (current_card) {
    i = m_audio_list.FindStringExact(-1, current_card);
    if (i != CB_ERR)
      current = i;
    else {
      // User's selected card could not be detected!
      CString card_missing_msg, title_msg;
      card_missing_msg.Format(IDS_AUDIOTAB_CARD_MISSING, current_card);
      title_msg.LoadString(IDS_AUDIOTAB_WARNING);
      MessageBox(card_missing_msg, title_msg, MB_OK | MB_ICONEXCLAMATION);
    }
  } else if (Num_cards > 0) {
    current = 0;
  }

  if (current < 0) {
    current = Num_cards - 1;
    mixer_id = DetermineDefaultMixer(current);
  }

  // If it's the first time since install, autodetect the best card
  if (Editor()->m_straight_to_setup) {
    current = DetermineBestCard();
    mixer_id = DetermineDefaultMixer(current);
  }

  // Set the current selection and available mixers
  m_audio_list.SetCurSel(current);
  EnableMixerSettings(Cards[current].mixers);

  SetMixerButton(mixer_id, Cards[current].mixers);

  // Set the Launcher sound check button if necessary
  LauncherSoundEnabled = os_config_read_uint(szSectionName, "LauncherSoundEnabled", 1);
  m_LauncherSndCheck.SetCheck(LauncherSoundEnabled);

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CAudioTab::OnSelchangeAudioList() {
  // TODO: Add your control notification handler code here
  int index;
  index = m_audio_list.GetCurSel();
  if (index != CB_ERR && index < Num_cards) {
    EnableMixerSettings(Cards[index].mixers);

    // Automatically default to software (if available)
    SetMixerButton(DetermineDefaultMixer(index), Cards[index].mixers);
  }
}

// Determine the sound card with the most available mixers (for auto-detection)
int CAudioTab::DetermineBestCard(void) {
  int card_pos = 0;
  int j;

  for (j = 0; j < Num_cards; j++)
    if (Cards[j].mixers >= Cards[card_pos].mixers)
      card_pos = j;

  return (card_pos);
}

// Enables/disables mixer options according to given mixer flags
void CAudioTab::EnableMixerSettings(UINT mixers) {
  HWND hwnd;

  GetDlgItem(IDC_MIXER_SOFTWARE, &hwnd);
  ::EnableWindow(hwnd, mixers & SOFTWARE_MIXER);

  GetDlgItem(IDC_MIXER_DS8BIT, &hwnd);
  ::EnableWindow(hwnd, mixers & DS8BIT_MIXER);

  /* We're not handling directsound 8 or 16 visually anymore
          GetDlgItem(IDC_MIXER_DS16BIT,&hwnd);
          ::EnableWindow(hwnd, mixers & DS16BIT_MIXER);
  */

  GetDlgItem(IDC_MIXER_DS3D, &hwnd);
  ::EnableWindow(hwnd, mixers & DS3D_MIXER);

  GetDlgItem(IDC_MIXER_EAX, &hwnd);
  ::EnableWindow(hwnd, mixers & EAX_MIXER);
}

// selects the radio button corresponding to given registry ID
void CAudioTab::SetMixerButton(int mixer_id, UINT mixer_flags) {
  // Turn them all off
  ((CButton *)GetDlgItem(IDC_MIXER_SOFTWARE))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_MIXER_DS16BIT))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_MIXER_DS8BIT))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_MIXER_DS3D))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_MIXER_EAX))->SetCheck(0);

  // Now, check the appropriate one
  switch (mixer_id) {
  case SOUND_MIXER_SOFTWARE_16:
    if (mixer_flags & SOFTWARE_MIXER)
      ((CButton *)GetDlgItem(IDC_MIXER_SOFTWARE))->SetCheck(1);
    break;

  // Now set and DS mixer to Default
  case SOUND_MIXER_DS_16:
    if (mixer_flags & DS16BIT_MIXER)
      ((CButton *)GetDlgItem(IDC_MIXER_DS8BIT))->SetCheck(1);
    break;

  case SOUND_MIXER_DS_8:
    if (mixer_flags & DS8BIT_MIXER)
      ((CButton *)GetDlgItem(IDC_MIXER_DS8BIT))->SetCheck(1);
    break;

  case SOUND_MIXER_DS3D_16:
    if (mixer_flags & DS3D_MIXER)
      ((CButton *)GetDlgItem(IDC_MIXER_DS3D))->SetCheck(1);
    break;
  case SOUND_MIXER_EAX:
    if (mixer_flags & EAX_MIXER)
      ((CButton *)GetDlgItem(IDC_MIXER_EAX))->SetCheck(1);
    break;
  default:
    break;
  }
}

// Returns the registry ID for the selected radio button
int CAudioTab::GetMixerButton(void) {
  int mixer_id = SOUND_MIXER_NONE;

  if (((CButton *)GetDlgItem(IDC_MIXER_SOFTWARE))->GetCheck() == 1)
    mixer_id = SOUND_MIXER_SOFTWARE_16;
  /*
          else if ( ((CButton *) GetDlgItem(IDC_MIXER_DS16BIT))->GetCheck() == 1 )
                  mixer_id=SOUND_MIXER_DS_16;
  */
  else if (((CButton *)GetDlgItem(IDC_MIXER_DS8BIT))->GetCheck() == 1)
    mixer_id = SOUND_MIXER_DS_8;
  else if (((CButton *)GetDlgItem(IDC_MIXER_DS3D))->GetCheck() == 1)
    mixer_id = SOUND_MIXER_DS3D_16;
  else if (((CButton *)GetDlgItem(IDC_MIXER_EAX))->GetCheck() == 1)
    mixer_id = SOUND_MIXER_EAX;

  return (mixer_id);
}

// Returns the default mixer for a given card index
UINT CAudioTab::DetermineDefaultMixer(int card_index) {
  int mixer_type;

  // make 8 bit direct sound the generic default
  mixer_type = SOUND_MIXER_DS_8;

  // make sure index is valid
  if (card_index < 0 || card_index >= Num_cards)
    return (mixer_type);

  // if mixer supports software, make it the default
  if (Cards[card_index].mixers & SOFTWARE_MIXER)
    mixer_type = SOUND_MIXER_SOFTWARE_16;

  return (mixer_type);
}

// Display the html help file
BOOL CAudioTab::OnHelpInfo(HELPINFO *pHelpInfo) {
#ifdef USE_HTML_HELP_SYSTEM
  CWaitCursor wc;
  help_launch(AUDIOTAB_HELP);
  return 1;
#else
  return CPropertyPage::OnHelpInfo(pHelpInfo);
#endif
}

// Display the html help file
afx_msg LRESULT CAudioTab::OnCommandHelp(WPARAM wParam, LPARAM lParam) {
#ifdef USE_HTML_HELP_SYSTEM
  help_launch(AUDIOTAB_HELP);
  return 1;
#else
  return CPropertyPage::OnCommandHelp(wParam, lParam);
#endif
}
