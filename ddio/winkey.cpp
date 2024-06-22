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

 * $Logfile: /DescentIII/Main/ddio_win/winkey.cpp $
 * $Revision: 36 $
 * $Date: 4/24/99 5:41p $
 * $Author: Samir $
 *
 * Keyboard IO with DirectInput 3.0
 *
 * $Log: /DescentIII/Main/ddio_win/winkey.cpp $
 *
 * 36    4/24/99 5:41p Samir
 * moved key to ascii, ascii to key to the ddio_common library.
 *
 * 35    4/22/99 2:02a Jeff
 * pass ddio_init_info through to keyboard handlers
 *
 * 34    3/05/99 3:27p Samir
 * screenshot key works properly now.
 *
 * 33    3/02/99 2:01p Samir
 * some small directinput changes. (note, for D3, we're now using emulated
 * key input because of the silly pause and numlock issue which for some
 * reason fails to work properly under DirectInput.
 *
 * 32    3/01/99 12:39a Samir
 * key ups only occur when key was initially down.  because of this,
 * ddio_KeyFlush cleared the down events, but if the user released after
 * flush, the up event would leak through and cause the illusion of key
 * presses leaking through.  HOPEFULLY this doesn't break anything else,
 * but I played through the game a bit and it seems to work fine.
 *
 * 31    2/25/99 10:43p Matt
 * Took out mprintf()
 *
 * 30    2/21/99 6:38p Samir
 * mouse and key input better. buffered mouse.
 *
 * 29    2/05/99 1:16p Samir
 * reset low level keys when flushing keyboard in the high level.  added a
 * function to the low level to reset the status of a key, called from
 * high level key flush.
 *
 * 28    2/04/99 12:31p Samir
 * use our timer for key capture if we're using the hook method.
 *
 * 27    1/28/99 6:22p Samir
 * may fix thread issues.
 *
 * 26    1/25/99 7:27p Samir
 * fixed timing issues with emulated keyboard key down times. (Win32 sends
 * multiple keydown messages, so  ignore them.)
 *
 * 25    1/25/99 6:47p Samir
 * allow slow keyboard
 *
 * 24    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 23    10/22/98 11:06a Samir
 * added numeric keypad ascii translations.
 *
 * 22    10/21/98 12:02p Samir
 * properly update odd keys when they are released throug
 * ddio_KeyGetDownTime.
 *
 * 21    10/16/98 12:15p Samir
 * took out ddio_KeyFrame
 *
 * 20    10/15/98 6:48p Samir
 * added timer hooks.
 *
 * 19    9/17/98 12:50p Samir
 * language.
 *
 * 18    6/29/98 6:43p Samir
 * Took out GetMsgProc and legacy keyboard variables.
 *
 * 17    4/09/98 6:56p Samir
 * PRINTSCREEN MUST WORK.
 *
 * 16    4/08/98 8:40p Samir
 * Screen shots work with print screen by checking VK code.
 *
 * 15    3/31/98 12:46p Samir
 * keyboard IO system better.  uses getmsgproc windows hook.
 *
 * 14    3/24/98 11:21a Samir
 * redid key handler.
 *
 * 13    2/25/98 6:11p Samir
 * Added functions to better deal with key flushing.
 *
 * 12    1/21/98 6:46p Samir
 * NT and 95 should have same keyboard behavior for framed handlers.
 *
 * 11    1/02/98 12:52p Samir
 * Added ascii->keycode translation tables
 *
 * 10    12/10/97 1:12p Samir
 * Use timestamp from DirectInput Key calls.
 *
 * 9     11/07/97 6:17p Samir
 * Rollbacked some more efficient code since it slowed down some machines
 * in the editor.   Sleep thread until closed a little faster.
 *
 * 8     10/23/97 2:59p Samir
 * Keyboard thread uses C runtime lib functions, and definitely ends.
 *
 * 7     10/22/97 4:37p Samir
 * Thread doesn't end if thread is still blocking, I think.
 *
 * 6     10/17/97 5:03p Samir
 * Default to preemptive keyboard handler (not under NT).
 *
 * 5     10/16/97 5:35p Samir
 * Use different cooperative level for Win95 vs. NT.
 *
 * 4     10/16/97 2:29p Samir
 * Changed DirectInput Keyboard to FOREGROUND
 *
 * 3     8/01/97 8:14p Samir
 * Fixed keyboard handler for NT to work with extended keys.
 *
 * 2     8/01/97 7:30p Samir
 * Better NT keyboard support.
 *
 * 14    5/23/97 4:09p Samir
 * Keyboard thread uses new task system.
 *
 * 13    5/09/97 6:45p Samir
 * Took out shared keyboard code from handler to ddio_common
 *
 * 12    5/08/97 1:56p Samir
 * Moved a bunch of keyboard code to ddio_common library.
 *
 * 11    3/20/97 11:08a Samir
 * Added function to peek for keys in queue without removing them.
 *
 * 10    3/13/97 3:02p Samir
 * Hopefully fixed keyboard thread problem.
 *
 * 9     2/20/97 9:58a Matt
 * Took out Int3() for directinput key buffer overflow, which would get
 * hit if you switched to another task, typed a bunch, and switched back
 * into the editor
 *
 * 8     1/23/97 2:22p Samir
 * Keyboard thread now blocks properly, and added functionality for
 * nonpreemptive keyboard polling.
 *
 * 7     1/20/97 3:46p Samir
 * RCS header check in
 *
 * $NoKeywords: $
 */

// ----------------------------------------------------------------------------
//	Keyboard Interface
// ----------------------------------------------------------------------------

#include "pserror.h"
#include "mono.h"
#include "ddio.h"
#include "ddio_win.h"
#include "winapp.h"
#include "TaskSystem.h"

#include <stdlib.h>
#include <process.h>

// ----------------------------------------------------------------------------
//	Local global data
// ----------------------------------------------------------------------------
#define DIKEY_BUFFER_SIZE 32

static struct tWinKeyData {
  LPDIRECTINPUTDEVICE lpdikey; // key device
  HANDLE evtnotify;            // notify event
  HHOOK winhook;               // windows hook
  uintptr_t thread;            // thread id
  //osMutex keyframe_mutex;      // mutex between
                               // internal key frame and key thread.
  bool nextframe;              // used for mutexing between keyframe and thread.
  bool acquired;               // device acquired?
  bool thread_active;          // used in thread.
  bool suspended;
} WKD = {NULL, NULL, NULL, 0xffffffff, false, false, false, true};

volatile struct tWinKeys {
  union {
    DWORD up_ticks; // windows ticks when key went up last
    float up_time;
  };
  union {
    DWORD down_ticks; // windows ticks when key went down last
    float down_time;
  };
  bool status;     // is it down?
  bool mutex_flag; // done for mutexing between ddio_Internal and KeyThread
  uint16_t mutex_data;
} WKeys[DDIO_MAX_KEYS];

static int DDIO_key_language = KBLANG_AMERICAN;

///////////////////////////////////////////////////////////////////////////////
//	Initializes DirectInputDevice keyboard if we are under Win9x or at least NT5
//	we set the cooperative level, etc.
LPDIRECTINPUTDEVICE dikey_Init(LPDIRECTINPUT lpdi, HWND hwnd);

//	Shutsdown DirectInputDevice keyboard if passed device is valid.
void dikey_Shutdown(LPDIRECTINPUTDEVICE lpdikey);

// sets up preemptive keyboard handling.
HANDLE dikey_EnableNotify(LPDIRECTINPUTDEVICE lpdikey);

//	disables event based notification.
bool dikey_DisableNotify(LPDIRECTINPUTDEVICE lpdikey, HANDLE evthandle);

//	acquires or unacquires device
// returns device acquisition state.
bool dikey_Acquire(LPDIRECTINPUTDEVICE lpdikey, bool acquire);

// emulated keyboard functionality
bool ddio_Win_KeyInit();
void ddio_Win_KeyClose();

int ddio_KeyHandler(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

// DirectInput Keyboard Thread
void __cdecl dikey_Thread(void *dp);

// translates scan code to foreign equivs.
uint8_t xlate_scancode(uint8_t scan_code);

///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
//	Initialization of keyboard device.
// ----------------------------------------------------------------------------

// this version will try to initialize a direct input keyboard device.  if it fails
// it falls back to the old keyboard hook (less reliable but works.)
bool ddio_InternalKeyInit(ddio_init_info *init_info) {
  bool emulated = init_info->key_emulation;

  LPDIRECTINPUTDEVICE lpdikey = NULL;
  int i;

  // reset key list
  for (i = 0; i < DDIO_MAX_KEYS; i++) {
    WKeys[i].down_ticks = 0;
    WKeys[i].up_ticks = 0;
    WKeys[i].status = false;
  }

  // start init.
  if (!emulated) {
    lpdikey = dikey_Init(DInputData.lpdi, (HWND)DInputData.app->m_hWnd);
  }

retry_key_init:
  if (lpdikey) {
    //	direct input keyboard can work, so we initialize preemptive handling of the keyboard
    HANDLE hevt = dikey_EnableNotify(lpdikey);

    if (hevt) {
      // event handling will work, so let's create the keyboard thread.
      bool acquired = dikey_Acquire(lpdikey, true);
      if (acquired) {
        //	create keyboard thread
        WKD.thread_active = true;
        WKD.lpdikey = lpdikey;
        WKD.thread = 0;
        WKD.evtnotify = hevt;
        WKD.acquired = acquired;
        WKD.winhook = NULL;
        WKD.suspended = false;
        WKD.nextframe = false;
        uintptr_t thrid = _beginthread(dikey_Thread, 0, nullptr);
        if (thrid == -1) {
          mprintf(0, "DDIO: DI_Keyboard thread failed to initialize.\n");
          WKD.thread_active = false;
          WKD.lpdikey = NULL;
          WKD.thread = 0xffffffff;
          WKD.evtnotify = NULL;
          WKD.acquired = false;
          WKD.winhook = NULL;
          WKD.suspended = false;
          acquired = dikey_Acquire(lpdikey, false);
          dikey_DisableNotify(lpdikey, hevt);
          dikey_Shutdown(lpdikey);
          lpdikey = NULL;
        } else {
          // success!  init data.
          // set priority of thread too.
          WKD.thread = thrid;
          if (SetThreadPriority((HANDLE)thrid, THREAD_PRIORITY_TIME_CRITICAL) == FALSE) {
            SetThreadPriority((HANDLE)thrid, THREAD_PRIORITY_HIGHEST);
          }
          mprintf(0, "DDIO: DI_Keyboard initialized.\n");
        }
      } else {
        // failed to acquire device? can't do.
        dikey_DisableNotify(lpdikey, hevt);
        dikey_Shutdown(lpdikey);
        lpdikey = NULL;
      }
    } else {
      // somehow event notification failed, can't do.
      dikey_Shutdown(lpdikey);
      lpdikey = NULL;
    }

    if (lpdikey == NULL) {
      goto retry_key_init;
    }
  } else {
    // here, initialize hook procedure.
    return ddio_Win_KeyInit();
  }

  return true;
}

//	this will shutdown direct input or the windows hook, whichever was chosen.
void ddio_InternalKeyClose() {
  if (WKD.lpdikey) {
    // deactivate thread and free it, then unacquire device, disable event notification, and shutdown!
    WKD.thread_active = false;
    SetEvent(WKD.evtnotify);
    Sleep(500);
    WKD.acquired = dikey_Acquire(WKD.lpdikey, false);
    dikey_DisableNotify(WKD.lpdikey, WKD.evtnotify);
    dikey_Shutdown(WKD.lpdikey);
    WKD.thread = 0xffffffff;
    WKD.evtnotify = NULL;
    WKD.lpdikey = NULL;
    mprintf(0, "DDIO: DI_Keyboard shutdown.\n");
  }
  if (WKD.winhook) {
    ddio_Win_KeyClose();
  }
}

// handled internally if keyboard system needs additional processing per frame
void ddio_InternalKeyFrame() {}

//////////////////////////////////////////////////////////////////////////////
// Miscellaneous API
//////////////////////////////////////////////////////////////////////////////

// returns if key is up or down
bool ddio_InternalKeyState(uint8_t key) { return WKeys[key].status; }

float ddio_InternalKeyDownTime(uint8_t key) {
  float down_time = 0.0f;
  if (WKeys[key].status) {
    if (WKD.winhook) {
      float timer = timer_GetTime();
      down_time = timer - WKeys[key].down_time;
      WKeys[key].down_time = timer;
    } else {
      DWORD curtickcount = GetTickCount();
      DWORD ticks = curtickcount - WKeys[key].down_ticks;
      if (ticks == 0) {
        // mprintf(0, "ticks=%d\n", ticks);
      }
      WKeys[key].down_ticks = curtickcount;
      down_time = (ticks / 1000.0f);
    }
  } else {
    if (WKD.winhook) {
      down_time = WKeys[key].up_time - WKeys[key].down_time;
      WKeys[key].down_time = WKeys[key].up_time = 0.0f;
    } else {
      DWORD ticks = WKeys[key].up_ticks - WKeys[key].down_ticks;
      WKeys[key].down_ticks = 0;
      WKeys[key].up_ticks = 0;
      down_time = (ticks / 1000.0f);
    }
  }

  return down_time;
}

// flush a key internally
void ddio_InternalResetKey(uint8_t key) {
  WKeys[key].down_ticks = 0;
  WKeys[key].up_ticks = 0;
  WKeys[key].status = false;
  WKeys[key].mutex_flag = false;
  WKeys[key].mutex_data = 0;
}

// sets type of keyboard to emulate
// #define KBLANG_AMERICAN		0
// #define KBLANG_BRITISH		1
// #define KBLANG_FRENCH		2
// #define KBLANG_GERMAN		3

void ddio_SetKeyboardLanguage(int language) { DDIO_key_language = language; }

// translates scan code to foreign equivs.
uint8_t xlate_scancode(uint8_t scan_code) {
  uint8_t code = scan_code;

  if (DDIO_key_language == KBLANG_FRENCH) {
    switch (scan_code) {
    case KEY_A:
      code = KEY_Q;
      break;
    case KEY_M:
      code = KEY_COMMA;
      break;
    case KEY_Q:
      code = KEY_A;
      break;
    case KEY_W:
      code = KEY_Z;
      break;
    case KEY_Z:
      code = KEY_W;
      break;
    case KEY_SEMICOL:
      code = KEY_M;
      break;
    case KEY_COMMA:
      code = KEY_SEMICOL;
      break;
    }
  } else if (DDIO_key_language == KBLANG_GERMAN) {
    switch (scan_code) {
    case KEY_Y:
      code = KEY_Z;
      break;
    case KEY_Z:
      code = KEY_Y;
      break;
    }
  } else if (DDIO_key_language == KBLANG_BRITISH) {
    if (scan_code == KEY_BSLASH_UK) { // KEY_SLASH_UK == 0x56
      code = KEY_SLASH;               // KEY_SLASH is really the backslash, 0x2B
    }
  }

  return code;
}

//////////////////////////////////////////////////////////////////////////////
//	DirectInput Functions
//////////////////////////////////////////////////////////////////////////////

inline bool IS_NT4_OR_LOWER() {
  int maj, min;
  tWin32OS os = oeWin32Application::version(&maj, &min);
  return (os == WinNT && maj < 5) ? true : false;
}

//	Initializes DirectInputDevice keyboard if we are under Win9x or at least NT5
//	we set the cooperative level, etc.
LPDIRECTINPUTDEVICE dikey_Init(LPDIRECTINPUT lpdi, HWND hwnd) {
  LPDIRECTINPUTDEVICE lpdikey;
  HRESULT hr;

  if (IS_NT4_OR_LOWER()) {
    return NULL;
  }

  // see if we can get the keyboard device.
  hr = lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL);
  if (hr != DI_OK) {
    DDIO_MESSAGE((hr, "DI_Keyboard initialization failed."));
    return NULL;
  }

  hr = lpdikey->SetDataFormat(&c_dfDIKeyboard);
  if (hr != DI_OK) {
    DDIO_MESSAGE((hr, "DI_Keyboard data format specification failed."));
    lpdikey->Release();
    return NULL;
  }

  hr = lpdikey->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
  if (hr != DI_OK) {
    DDIO_MESSAGE((hr, "DI_Keyboard set cooperative level failed."));
    lpdikey->Release();
    return NULL;
  }

  return lpdikey;
}

//	Shutsdown DirectInputDevice keyboard if passed device is valid.
void dikey_Shutdown(LPDIRECTINPUTDEVICE lpdikey) {
  if (lpdikey) {
    lpdikey->Release();
  }
}

// sets up preemptive keyboard handling.
HANDLE dikey_EnableNotify(LPDIRECTINPUTDEVICE lpdikey) {
  if (lpdikey) {
    HANDLE hEvt = CreateEvent(NULL, TRUE, FALSE, "DDIOKeyEvent");
    HRESULT hr;
    DIPROPDWORD dipropdw = {
        {
            sizeof(DIPROPDWORD),
            sizeof(DIPROPHEADER),
            0,
            DIPH_DEVICE,
        },
        DIKEY_BUFFER_SIZE,
    };

    if (!hEvt) {
      DDIO_MESSAGE((0, "DI_Keyboard failed to init system event."));
      return NULL;
    }

    // set event
    hr = lpdikey->SetEventNotification(hEvt);
    if (hr != DI_OK) {
      DDIO_MESSAGE((hr, "DI_Keyboard failed to set preemptive key event notification."));
      CloseHandle(hEvt);
      return NULL;
    }

    // set key buffer size
    hr = lpdikey->SetProperty(DIPROP_BUFFERSIZE, &dipropdw.diph);
    if (FAILED(hr)) {
      DDIO_MESSAGE((hr, "DI_keyboard buffering failed."));
      lpdikey->SetEventNotification(NULL);
      CloseHandle(hEvt);
      return NULL;
    }

    return hEvt;
  }

  return NULL;
}

//	disables event based notification.
bool dikey_DisableNotify(LPDIRECTINPUTDEVICE lpdikey, HANDLE evthandle) {
  if (lpdikey) {
    lpdikey->SetEventNotification(NULL);
    CloseHandle(evthandle);
    return true;
  }

  return false;
}

//	acquires or unacquires device
// returns device acquisition state.
bool dikey_Acquire(LPDIRECTINPUTDEVICE lpdikey, bool acquire) {
  HRESULT hr = acquire ? lpdikey->Acquire() : lpdikey->Unacquire();

  if (FAILED(hr)) {
    DDIO_MESSAGE((hr, "DI_keyboard acquire/unacquire fail."));
    return !acquire;
  }

  return acquire;
}

// DirectInput Keyboard Thread
void __cdecl dikey_Thread(void *dp) {
  unsigned event_count = 0;

  GetAsyncKeyState(VK_PAUSE); // this will tell if the 'pause' key is toggled

  while (WKD.thread_active) {
    // this thread will hold until the direct input key event has been signaled by the OS.
    //	after this, we will get all the keys in the io buffer and register them with the
    // key system.

    switch (WaitForSingleObject(WKD.evtnotify, INFINITE)) {
    case WAIT_TIMEOUT: // this shouldn't happen, but if it does, no big deal.
      break;
    case WAIT_ABANDONED: // usually means calling thread quit.
      WKD.thread_active = false;
      break;
    case WAIT_OBJECT_0: // event was signalled normally
    {
      DIDEVICEOBJECTDATA diobjdata[DIKEY_BUFFER_SIZE];
      DWORD diobjitems = DIKEY_BUFFER_SIZE;
      HRESULT hr;
      //	SHORT async_key_state;
      uint8_t key;

      int i;

      // don't read if suspended!
      if (WKD.suspended) {
        break;
      }

      event_count++;

      // attempt acquisition if keyboard not already acquired
      if (!WKD.acquired) {
        WKD.acquired = dikey_Acquire(WKD.lpdikey, true);
      }
      if (WKD.acquired) {
        hr = WKD.lpdikey->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diobjdata, &diobjitems, 0);
        if (SUCCEEDED(hr)) {
          // the pause is key under Windows seems to act kinda strange.  it's a toggle button
          // and USUALLY is preceeded by a KEY_LCTRL press.  If a pause toggle was indicated, flush the
          // keyboard and quit.

          //	note that dwOfs is the acutal key that is either down or up, and dwData tells us if
          //	it is up or down.  So place on key array, and in queue.
          for (i = 0; i < (int)diobjitems; i++) {
            key = xlate_scancode((uint8_t)(diobjdata[i].dwOfs));
            if (diobjdata[i].dwData & 0x80) {
              if (WKeys[key].status) {
                WKeys[key].up_ticks = 0;
              }
              WKeys[key].down_ticks = diobjdata[i].dwTimeStamp;
              WKeys[key].status = true;
              if (key == KEY_LCTRL) {
                WKeys[key].mutex_flag = true;
              }
              mprintf(0, "dkey=%x\n", key);
            } else {
              if (WKeys[key].status) {
                WKeys[key].up_ticks = diobjdata[i].dwTimeStamp;
                WKeys[key].status = false;
                mprintf(0, "ukey=%x\n", key);
              }
            }

            ddio_UpdateKeyState(key, WKeys[key].status);
          }
        } else {
          if (hr == DIERR_INPUTLOST) {
            WKD.acquired = dikey_Acquire(WKD.lpdikey, true);
          } else {
            DDIO_MESSAGE((hr, "DI_keyboard unable to read."));
          }
        }
      }
    } break;
    }

    ResetEvent(WKD.evtnotify);
  }

  DDIO_MESSAGE((0, "DI_Keyboard thread ended."));
}

void ddio_InternalKeySuspend() {
  if (WKD.lpdikey && WKD.acquired) {
    WKD.acquired = dikey_Acquire(WKD.lpdikey, false);
  }
  WKD.suspended = true;
}

void ddio_InternalKeyResume() {
  if (WKD.lpdikey && !WKD.acquired) {
    WKD.acquired = dikey_Acquire(WKD.lpdikey, true);
  }
  WKD.suspended = false;
}

//	Win32 non-threaded version

bool ddio_Win_KeyInit() {
  /*	Initialize hook handlers */
  WKD.winhook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, Win32App()->instance(),
                                 GetCurrentThreadId());
  if (!WKD.winhook) {
    return false;
  }

  mprintf(0, "Keyboard initialized.\n");

  return true;
}

void ddio_Win_KeyClose() {
  /*	Free up message handlers */
  if (WKD.winhook) {
    UnhookWindowsHookEx(WKD.winhook);
    WKD.winhook = NULL;
  }

  mprintf(0, "Keyboard released.\n");
}

// ----------------------------------------------------------------------------
//	non DirectInput keyboard handler
// ----------------------------------------------------------------------------

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
  int res;

  if (code < 0) {
    return CallNextHookEx(WKD.winhook, code, wParam, lParam);
  }

  if (lParam & 0x80000000)
    res = ddio_KeyHandler(0, WM_KEYUP, wParam, lParam);
  else
    res = ddio_KeyHandler(0, WM_KEYDOWN, wParam, lParam);

  return (!res);
}

int ddio_KeyHandler(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  uint8_t scan_code;
  float timer = timer_GetTime();

  if (!WKD.winhook)
    return 1;

  switch (msg) {
  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
    scan_code = (uint8_t)((lParam >> 16) & 0xff);
    if (lParam & 0x01000000)
      scan_code |= 0x80;

    scan_code = xlate_scancode(scan_code);

    //	print screen is a weird case.   only accept key ups.
    if (wParam != VK_SNAPSHOT) {
      if (!WKeys[scan_code].status) {
        WKeys[scan_code].up_time = 0;
        WKeys[scan_code].down_time = timer;
      } else {
        WKeys[scan_code].up_time = 0;
      }
      WKeys[scan_code].status = true;
      ddio_UpdateKeyState(scan_code, true);
    }
    break;

  case WM_KEYUP:
  case WM_SYSKEYUP:
    scan_code = (uint8_t)((lParam >> 16) & 0xff);
    if (lParam & 0x01000000)
      scan_code |= 0x80;

    scan_code = xlate_scancode(scan_code);

    //	handle special keys.  print screen, we will simulate the keypress.
    if (wParam == VK_SNAPSHOT) {
      scan_code = KEY_PRINT_SCREEN;
      WKeys[scan_code].down_time = timer;
      WKeys[scan_code].status = true;
      ddio_UpdateKeyState(scan_code, true);
    }
    if (WKeys[scan_code].status) {
      WKeys[scan_code].status = false;
      WKeys[scan_code].up_time = timer;
      ddio_UpdateKeyState(scan_code, false);
    }

    break;
  }

  return 1;
}
