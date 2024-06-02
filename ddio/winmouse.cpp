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

// ----------------------------------------------------------------------------
//      Mouse Interface
// ----------------------------------------------------------------------------

#include <cstdlib>
#include <cmath>

#include "pserror.h"
#include "mono.h"
#include "ddio.h"
#include "ddio_win.h"
#include "winapp.h"
#include "psclass.h"

struct t_mse_button_info {
  bool is_down[N_MSEBTNS];
  uint8_t down_count[N_MSEBTNS];
  uint8_t up_count[N_MSEBTNS];
  DWORD time_down[N_MSEBTNS]; // in milliseconds windows ticks
  DWORD time_up[N_MSEBTNS];
};

struct t_mse_event {
  int16_t btn;
  int16_t state;
};

#define MOUSE_ZMIN 0 // mouse wheel z min and max (increments of 120 = 10 units)
#define MOUSE_ZMAX 1200
#define N_DIMSEBTNS 4                     // # of REAL mouse buttons
#define MSEBTN_WHL_UP (N_DIMSEBTNS)       // button index for mouse wheel up
#define MSEBTN_WHL_DOWN (N_DIMSEBTNS + 1) // button index for mouse wheel down

// taken from winuser.h
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x20a
#endif

bool rawInputOpened = false;

// ----------------------------------------------------------------------------

static bool DDIO_mouse_init = 0;

static struct mses_state {
  LPDIRECTINPUTDEVICE lpdimse;
  RECT brect;              // limit rectangle of absolute mouse coords
  int16_t x, y, z;           // current x,y,z in absolute mouse coords
  int16_t cx, cy, cz;        // prior values of x,y,z from last mouse frame
  int16_t zmin, zmax;        // 3 dimensional mouse devices use this
  int btn_mask, btn_flags; // btn_flags are the avaiable buttons on this device in mask form.
  float timer;             // done to keep track of mouse polling. [ISB] this is in InjectD3 but not here?
  bool emulated;           // are we emulating direct input?
  bool acquired;
  bool suspended;
  int8_t cursor_count;
  float x_aspect, y_aspect; // used in calculating coordinates returned from ddio_MouseGetState
  HANDLE hmseevt;           // signaled if mouse input is awaiting.
  int16_t dx, dy, dz, imm_dz;
  int16_t mode;         // mode of mouse operation.
  int16_t nbtns, naxis; // device caps.
} DDIO_mouse_state;

// Normally mouse events use ticks, attempting to use timer_GetTime which has more accuracy to smooth over bug with
// mouse buttons dropping.
float localDownStart[N_MSEBTNS];
float localUpStart[N_MSEBTNS];

static t_mse_button_info DIM_buttons;
static tQueue<t_mse_event, 16> MB_queue;

int wheelAccum = 0;

void DDIOShowCursor(BOOL show) {
  if (show) {
    if (DDIO_mouse_state.cursor_count == -1) {
      ShowCursor(TRUE);
    }
    DDIO_mouse_state.cursor_count = 0;
  } else {
    if (DDIO_mouse_state.cursor_count == 0) {
      ShowCursor(FALSE);
    }
    DDIO_mouse_state.cursor_count = -1;
  }
}

void ddio_MouseMode(int mode) {
  DDIO_mouse_state.mode = mode;
}

void ddio_MouseQueueFlush() {
  memset(&DIM_buttons, 0, sizeof(DIM_buttons));
  MB_queue.flush();

  // Need to clear the new arrays, since otherwise the game will think you're holding down a button when leaving a UI
  // screen.
  memset(localDownStart, 0, sizeof(localDownStart));
  memset(localUpStart, 0, sizeof(localUpStart));
}

void ddio_MouseReset() {
  // get relative window rect, 0/0 - width-1/height-1
  GetClientRect(DInputData.hwnd, &DDIO_mouse_state.brect);
  // restrict mouse cursor to actual screen coords of the window
  RECT clipRect = DDIO_mouse_state.brect;
  ClientToScreen(DInputData.hwnd, reinterpret_cast<POINT *>(&clipRect.left));
  ClientToScreen(DInputData.hwnd, reinterpret_cast<POINT *>(&clipRect.right));
  ClipCursor(&clipRect);

  DDIO_mouse_state.zmin = MOUSE_ZMIN;
  DDIO_mouse_state.zmax = MOUSE_ZMAX;

  //    set up new coordinates for mouse pointer.
  DDIO_mouse_state.btn_mask = 0;
  DDIO_mouse_state.dx = 0;
  DDIO_mouse_state.dy = 0;
  DDIO_mouse_state.dz = 0;
  DDIO_mouse_state.imm_dz = 0;
  DDIO_mouse_state.x = (DDIO_mouse_state.brect.right + DDIO_mouse_state.brect.left) / 2;
  DDIO_mouse_state.y = (DDIO_mouse_state.brect.bottom + DDIO_mouse_state.brect.top) / 2;
  DDIO_mouse_state.z = (DDIO_mouse_state.zmax + DDIO_mouse_state.zmin) / 2;
  DDIO_mouse_state.cx = DDIO_mouse_state.x;
  DDIO_mouse_state.cy = DDIO_mouse_state.y;
  DDIO_mouse_state.cz = 0;
  DDIO_mouse_state.x_aspect = 1.0f;
  DDIO_mouse_state.y_aspect = 1.0f;

  // reset button states
  ddio_MouseQueueFlush();
}

// return mouse button down time.
// This function has been hacked to use timer_GetTime which can be much more accurate.
float ddio_MouseBtnDownTime(int btn) {
  // DWORD ticks, curticks = GetTickCount();
  float time, curtime = timer_GetTime();

  // ASSERT(btn >= 0 && btn < N_MSEBTNS);

  if (DIM_buttons.is_down[btn]) {
    time = curtime - localDownStart[btn];
    DIM_buttons.time_down[btn] = (int)(curtime * 1000);
    localDownStart[btn] = curtime;
  } else {
    time = localUpStart[btn] - localDownStart[btn];
    localUpStart[btn] = localDownStart[btn] = 0;
    DIM_buttons.time_down[btn] = DIM_buttons.time_up[btn] = 0;
  }

  DIM_buttons.is_down[MSEBTN_WHL_UP] = false;
  DIM_buttons.is_down[MSEBTN_WHL_DOWN] = false;

  return time;
}

int ddio_MouseGetState(int *x, int *y, int *dx, int *dy, int *z, int *dz) {
  //    update mouse timer.
  int btn_mask = DDIO_mouse_state.btn_mask;

  DDIO_mouse_state.timer = timer_GetTime();

  //    get return values.
  if (x)
    *x = DDIO_mouse_state.x;
  if (y)
    *y = DDIO_mouse_state.y;
  if (z)
    *z = DDIO_mouse_state.z;
  if (dx)
    *dx = DDIO_mouse_state.dx;
  if (dy)
    *dy = DDIO_mouse_state.dy;
  if (dz)
    *dz = DDIO_mouse_state.dz;

  DDIO_mouse_state.dx = 0;
  DDIO_mouse_state.dy = 0;
  DDIO_mouse_state.dz = 0;
  DDIO_mouse_state.btn_mask = 0;

  DIM_buttons.is_down[MSEBTN_WHL_UP] = false;
  DIM_buttons.is_down[MSEBTN_WHL_DOWN] = false;

  return btn_mask;
}

void ddio_InternalMouseFrame() {
  int btn_mask = 0;

  // These need to be continually maintained, since a small number of inputs rely on it being set every frame.
  if (DIM_buttons.is_down[0])
    btn_mask |= MOUSE_LB;
  if (DIM_buttons.is_down[1])
    btn_mask |= MOUSE_RB;
  if (DIM_buttons.is_down[2])
    btn_mask |= MOUSE_CB;
  if (DIM_buttons.is_down[3])
    btn_mask |= MOUSE_B4;
  if (DIM_buttons.is_down[4])
    btn_mask |= MOUSE_B5;
  if (DIM_buttons.is_down[5])
    btn_mask |= MOUSE_B6;
  if (DIM_buttons.is_down[6])
    btn_mask |= MOUSE_B7;
  if (DIM_buttons.is_down[7])
    btn_mask |= MOUSE_B8;

  DDIO_mouse_state.btn_mask = btn_mask;
}

void MouseError() { MessageBoxA(nullptr, "Failed to init raw input for mouse", "Error", MB_ICONERROR); }

int RawInputHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  uint32_t buttons;
  t_mse_event ev;
  float curtime = timer_GetTime();

  if (DDIO_mouse_state.suspended) {
    DDIO_mouse_state.btn_mask = 0;
    DDIO_mouse_state.dx = 0;
    DDIO_mouse_state.dy = 0;
    DDIO_mouse_state.dz = 0;
    return 0;
  }

  HRAWINPUT rawinputHandle = (HRAWINPUT)lParam;
  UINT size = 0;
  UINT result = GetRawInputData(rawinputHandle, RID_INPUT, 0, &size, sizeof(RAWINPUTHEADER));
  if (result == 0 && size > 0) {
    void *buf = malloc(size);
    if (!buf) {
      return 0;
    }
    result = GetRawInputData(rawinputHandle, RID_INPUT, buf, &size, sizeof(RAWINPUTHEADER));

    if (result >= 0) {
      RAWINPUT *rawinput = (RAWINPUT *)buf;
      if (rawinput->header.dwType == RIM_TYPEMOUSE) {
        buttons = rawinput->data.mouse.ulButtons;
        if (buttons & RI_MOUSE_LEFT_BUTTON_DOWN && !DIM_buttons.is_down[0]) {
          DIM_buttons.down_count[0]++;
          DIM_buttons.time_down[0] = GetTickCount();
          localDownStart[0] = curtime;
          DIM_buttons.is_down[0] = true;
          DDIO_mouse_state.btn_mask |= MOUSE_LB;
          ev.btn = 0;
          ev.state = true;
          MB_queue.send(ev);
          /*if (hack)
          {
                  fprintf(hack, "MB1 down at %f\n", timer_GetTime());
          }*/
        } else if (buttons & RI_MOUSE_LEFT_BUTTON_UP && DIM_buttons.is_down[0]) {
          DIM_buttons.up_count[0]++;
          DIM_buttons.is_down[0] = false;
          DIM_buttons.time_up[0] = GetTickCount();
          localUpStart[0] = curtime;
          DDIO_mouse_state.btn_mask &= ~MOUSE_LB;
          ev.btn = 0;
          ev.state = false;
          MB_queue.send(ev);
          /*if (hack)
          {
                  fprintf(hack, "MB1 up at %f\n", timer_GetTime());
          }*/
        }
        if (buttons & RI_MOUSE_RIGHT_BUTTON_DOWN && !DIM_buttons.is_down[1]) {
          DIM_buttons.down_count[1]++;
          DIM_buttons.time_down[1] = GetTickCount();
          localDownStart[1] = curtime;
          DIM_buttons.is_down[1] = true;
          DDIO_mouse_state.btn_mask |= MOUSE_RB;
          ev.btn = 1;
          ev.state = true;
          MB_queue.send(ev);
        } else if (buttons & RI_MOUSE_RIGHT_BUTTON_UP && DIM_buttons.is_down[1]) {
          DIM_buttons.up_count[1]++;
          DIM_buttons.is_down[1] = false;
          DIM_buttons.time_up[1] = GetTickCount();
          localUpStart[1] = curtime;
          DDIO_mouse_state.btn_mask &= ~MOUSE_RB;
          ev.btn = 1;
          ev.state = false;
          MB_queue.send(ev);
        }
        if (buttons & RI_MOUSE_MIDDLE_BUTTON_DOWN && !DIM_buttons.is_down[2]) {
          DIM_buttons.down_count[2]++;
          DIM_buttons.time_down[2] = GetTickCount();
          localDownStart[2] = curtime;
          DIM_buttons.is_down[2] = true;
          DDIO_mouse_state.btn_mask |= MOUSE_CB;
          ev.btn = 2;
          ev.state = true;
          MB_queue.send(ev);
        } else if (buttons & RI_MOUSE_MIDDLE_BUTTON_UP && DIM_buttons.is_down[2]) {
          DIM_buttons.up_count[2]++;
          DIM_buttons.is_down[2] = false;
          DIM_buttons.time_up[2] = GetTickCount();
          localUpStart[2] = curtime;
          DDIO_mouse_state.btn_mask &= ~MOUSE_CB;
          ev.btn = 2;
          ev.state = false;
          MB_queue.send(ev);
        }

        // JC: Imported extra mouse buttons code from Piccu Engine 2924ad2
        if (buttons & RI_MOUSE_BUTTON_4_DOWN && !DIM_buttons.is_down[3])
        {
          DIM_buttons.down_count[3]++;
          DIM_buttons.time_down[3] = curtime;
          DIM_buttons.is_down[3] = true;
          DDIO_mouse_state.btn_mask |= MOUSE_B4;
          ev.btn = 3;
          ev.state = true;
          MB_queue.send(ev);
        }
        else if (buttons & RI_MOUSE_BUTTON_4_UP && DIM_buttons.is_down[3])
        {
          DIM_buttons.up_count[3]++;
          DIM_buttons.is_down[3] = false;
          DIM_buttons.time_up[3] = curtime;
          DDIO_mouse_state.btn_mask &= ~MOUSE_B4;
          ev.btn = 3;
          ev.state = false;
          MB_queue.send(ev);
        }
        if (buttons & RI_MOUSE_BUTTON_5_DOWN && !DIM_buttons.is_down[6])
        {
          DIM_buttons.down_count[6]++;
          DIM_buttons.time_down[6] = curtime;
          DIM_buttons.is_down[6] = true;
          DDIO_mouse_state.btn_mask |= MOUSE_B7;
          ev.btn = 6;
          ev.state = true;
          MB_queue.send(ev);
        } else if (buttons & RI_MOUSE_BUTTON_5_UP && DIM_buttons.is_down[6])
        {
          DIM_buttons.up_count[6]++;
          DIM_buttons.is_down[6] = false;
          DIM_buttons.time_up[6] = curtime;
          DDIO_mouse_state.btn_mask &= ~MOUSE_B7;
          ev.btn = 6;
          ev.state = false;
          MB_queue.send(ev);
        }

        if (buttons & RI_MOUSE_WHEEL) {
          wheelAccum += (int)(int16_t)rawinput->data.mouse.usButtonData;
          if (wheelAccum >= WHEEL_DELTA) {
            DIM_buttons.down_count[MSEBTN_WHL_UP]++;
            DIM_buttons.up_count[MSEBTN_WHL_UP]++;
            DIM_buttons.is_down[MSEBTN_WHL_UP] = true;
            DIM_buttons.time_down[MSEBTN_WHL_UP] = GetTickCount();
            DIM_buttons.time_up[MSEBTN_WHL_UP] = GetTickCount() + 100;
            localDownStart[MSEBTN_WHL_UP] = curtime;
            localUpStart[MSEBTN_WHL_UP] = curtime + .1f;
            wheelAccum = 0;
          } else if (wheelAccum <= -WHEEL_DELTA) {
            DIM_buttons.down_count[MSEBTN_WHL_DOWN]++;
            DIM_buttons.up_count[MSEBTN_WHL_DOWN]++;
            DIM_buttons.is_down[MSEBTN_WHL_DOWN] = true;
            DIM_buttons.time_down[MSEBTN_WHL_DOWN] = GetTickCount();
            DIM_buttons.time_up[MSEBTN_WHL_DOWN] = GetTickCount() + 100;
            localDownStart[MSEBTN_WHL_DOWN] = curtime;
            localUpStart[MSEBTN_WHL_DOWN] = curtime + .1f;
            wheelAccum = 0;
          }
        }

        DDIO_mouse_state.dx += rawinput->data.mouse.lLastX;
        DDIO_mouse_state.dy += rawinput->data.mouse.lLastY;
        // DDIO_mouse_state.btn_mask = buttons;
      }

      DDIO_mouse_state.x += rawinput->data.mouse.lLastX;
      DDIO_mouse_state.y += rawinput->data.mouse.lLastY;
      DDIO_mouse_state.z = 0;

      // check bounds of mouse cursor.
      if (DDIO_mouse_state.x < DDIO_mouse_state.brect.left)
        DDIO_mouse_state.x = (int16_t)DDIO_mouse_state.brect.left;
      if (DDIO_mouse_state.x >= DDIO_mouse_state.brect.right)
        DDIO_mouse_state.x = (int16_t)DDIO_mouse_state.brect.right - 1;
      if (DDIO_mouse_state.y < DDIO_mouse_state.brect.top)
        DDIO_mouse_state.y = (int16_t)DDIO_mouse_state.brect.top;
      if (DDIO_mouse_state.y >= DDIO_mouse_state.brect.bottom)
        DDIO_mouse_state.y = (int16_t)DDIO_mouse_state.brect.bottom - 1;
      if (DDIO_mouse_state.z > DDIO_mouse_state.zmax)
        DDIO_mouse_state.z = (int16_t)DDIO_mouse_state.zmax;
      if (DDIO_mouse_state.z < DDIO_mouse_state.zmin)
        DDIO_mouse_state.z = (int16_t)DDIO_mouse_state.zmin;
    }

    free(buf);
  }
  return 0;
}

bool InitNewMouse() {
  int i;
  if (!rawInputOpened) {
    RAWINPUTDEVICE rawInputDevice = {};

    rawInputDevice.usUsage = 0x0002;
    rawInputDevice.usUsagePage = 0x0001;
    //TODO: This code should be renabled when some solution for mouse capturing is decided on.
    // The game should free the capture when the cursor is visible, and recapture it when it isn't visible.
    // Account for the original mode.
    if (DDIO_mouse_state.mode == MOUSE_EXCLUSIVE_MODE)
      rawInputDevice.dwFlags = RIDEV_CAPTUREMOUSE | RIDEV_NOLEGACY;
    else
      rawInputDevice.dwFlags = 0;

    rawInputDevice.hwndTarget = DInputData.hwnd;

    if (RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)) == FALSE) {
      Error("InitNewMouse: HID Registration failed: %d", GetLastError());
      return false;
    }

    // HACK: Need to flush messages for this to work.
    MSG msg;

    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }

    DInputData.app->add_handler(WM_INPUT, (tOEWin32MsgCallback)&RawInputHandler);

    DDIO_mouse_state.timer = timer_GetTime();
    DDIO_mouse_state.naxis = 2;
    DDIO_mouse_state.nbtns = N_DIMSEBTNS + 3; // always have a mousewheel. [ISB] disgusting hack: Can't change mousewheel bindings for old pilots, so make button 5 after the two mouse wheel buttons.
    for (i = 0; i < DDIO_mouse_state.nbtns; i++) {
      DDIO_mouse_state.btn_flags |= (1 << i);
    }

    memset(&DIM_buttons, 0, sizeof(t_mse_button_info));
    rawInputOpened = true;
  }
  return true;
}

bool ddio_MouseInit() {
  tWin32OS os;
  int major, minor;

  // see if we need to emulate directinput.
  os = oeWin32Application::version(&major, &minor);
  DDIO_mouse_state.emulated = true;
  DDIO_mouse_state.lpdimse = NULL;

  InitNewMouse();

  // standard initialization
  DDIO_mouse_state.emulated = (DDIO_mouse_state.lpdimse) ? false : true;
  DDIO_mouse_state.cursor_count = ShowCursor(TRUE); // get initial count
  while (DDIO_mouse_state.cursor_count >= 0)        // hide cursor until truly hidden.
  {
    DDIO_mouse_state.cursor_count = ShowCursor(FALSE);
  }

  DDIOShowCursor(DDIO_mouse_state.mode == MOUSE_EXCLUSIVE_MODE ? FALSE : TRUE);

  DDIO_mouse_state.suspended = false;
  ddio_MouseReset();
  DDIO_mouse_init = true;

  return true;
}

// here we deinitialize our Mouse from DirectInput.
void ddio_MouseClose() {
  if (!DDIO_mouse_init)
    return;

  if (rawInputOpened) {
    RAWINPUTDEVICE rawInputDevice = {};

    rawInputDevice.usUsage = 0x0002;
    rawInputDevice.usUsagePage = 0x0001;
    rawInputDevice.dwFlags = RIDEV_REMOVE;
    rawInputDevice.hwndTarget = 0; // not sure why?

    if (RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)) == FALSE) {
      rawInputOpened = false;
      DDIO_mouse_init = false;
      Error("ddio_MouseClose: HID Registration failed: %d", GetLastError());
    }
    DInputData.app->remove_handler(WM_INPUT, (tOEWin32MsgCallback)&RawInputHandler);
    rawInputOpened = false;
  }

  DDIO_mouse_init = false;
}

// used to prevent mouse input from being registered
void ddio_InternalMouseSuspend() {
  if (!DDIO_mouse_init)
    return;

  DDIO_mouse_state.suspended = true;
}

void ddio_InternalMouseResume() {
  if (!DDIO_mouse_init)
    return;

  DDIO_mouse_state.suspended = false;
}

// return mouse button down time
int ddio_MouseBtnDownCount(int btn) {
  if (btn < 0 || btn >= N_MSEBTNS)
    return 0;
  int n_downs = DIM_buttons.down_count[btn];

  if (n_downs) {

    DIM_buttons.down_count[btn] = 0;
  }

  return n_downs;
}

// return mouse button up count
int ddio_MouseBtnUpCount(int btn) {
  if (btn < 0 || btn >= N_MSEBTNS)
    return 0;
  int n_ups = DIM_buttons.up_count[btn];
  DIM_buttons.up_count[btn] = 0;
  return n_ups;
}

// get device caps
int ddio_MouseGetCaps(int *btn, int *axis) {
  *btn = (int)DDIO_mouse_state.nbtns;
  *axis = (int)DDIO_mouse_state.naxis;

  return DDIO_mouse_state.btn_flags;
}

//      gets limits on the position of the mouse cursor (or atleast what's returned from GetState)
void ddio_MouseGetLimits(int *left, int *top, int *right, int *bottom, int *zmin, int *zmax) {
  *left = DDIO_mouse_state.brect.left;
  *top = DDIO_mouse_state.brect.top;
  *right = DDIO_mouse_state.brect.right;
  *bottom = DDIO_mouse_state.brect.bottom;

  if (zmin)
    *zmin = DDIO_mouse_state.zmin;
  if (zmax)
    *zmax = DDIO_mouse_state.zmax;
}

//      sets limits on the position of the mouse cursor (or atleast what's returned from GetState)
void ddio_MouseSetLimits(int left, int top, int right, int bottom, int zmin, int zmax) {
  bool zaxis = (DDIO_mouse_state.naxis >= 3);
  SetRect(&DDIO_mouse_state.brect, left, top, right, bottom);
  DDIO_mouse_state.zmin = (!zmin && zaxis) ? MOUSE_ZMIN : zmin;
  DDIO_mouse_state.zmax = (!zmax && zaxis) ? MOUSE_ZMAX : zmax;
  DDIO_mouse_state.cx = (right + left) / 2;
  DDIO_mouse_state.cy = (bottom + top) / 2;
}

// virtual coordinate system for mouse (match to video resolution set for optimal mouse usage.
void ddio_MouseSetVCoords(int width, int height) { ddio_MouseSetLimits(0, 0, width, height); }

// gets a mouse button event, returns false if none.
bool ddio_MouseGetEvent(int *btn, bool *state) {
  t_mse_event evt;

  if (MB_queue.recv(&evt)) {
    *btn = (int)evt.btn;
    *state = evt.state ? true : false;
    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
char Ctltext_MseBtnBindings[N_MSEBTNS][32] = {"mse-l\0\0\0\0\0\0\0\0\0\0\0\0",
                                              "mse-r\0\0\0\0\0\0\0\0\0\0\0\0",
                                              "mse-c\0\0\0\0\0\0\0\0\0\0\0\0",
                                              "mse-b4\0\0\0\0\0\0\0\0\0\0\0",
                                              "msew-u\0\0\0\0\0\0\0\0\0\0\0",
                                              "msew-d\0\0\0\0\0\0\0\0\0\0\0",
                                              "mse-b5",
                                              ""};

char Ctltext_MseAxisBindings[][32] = {"mse-X\0\0\0\0\0\0\0\0\0\0\0\0", "mse-Y\0\0\0\0\0\0\0\0\0\0\0\0",
                                      "msewheel\0\0\0\0\0\0\0\0\0\0"};

// returns string to binding.
const char *ddio_MouseGetBtnText(int btn) {
  if (btn >= N_MSEBTNS || btn < 0)
    return ("");
  return Ctltext_MseBtnBindings[btn];
}

const char *ddio_MouseGetAxisText(int axis) {
  if (axis >= (sizeof(Ctltext_MseAxisBindings) / sizeof(char *)) || axis < 0)
    return ("");
  return Ctltext_MseAxisBindings[axis];
}
