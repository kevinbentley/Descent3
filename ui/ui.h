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

 * $Logfile: /DescentIII/Main/Lib/ui.h $
 * $Revision: 75 $
 * $Date: 5/17/99 5:19p $
 * $Author: Samir $
 *
 *	UI system
 *
 * $Log: /DescentIII/Main/Lib/ui.h $
 *
 * 75    5/17/99 5:19p Samir
 * added ability for edit box to autoselect when hitting the max number of
 * characters typable.
 *
 * 74    5/02/99 2:08a Samir
 * added Enable and Disable and only accept locking of button if mouse is
 * inside the button.
 *
 * 73    4/29/99 2:21a Samir
 * added flag for gadgets.
 *
 * 72    4/28/99 1:54a Samir
 * visual tweaks to text
 *
 * 71    4/26/99 7:46p Samir
 * you can get flags from a window now.
 *
 * 70    4/16/99 4:02a Jeff
 * include linux_fix.h for linxu builds...reduces errors
 *
 * 69    4/15/99 1:45a Jeff
 * changes for linux compile
 *
 * 68    4/03/99 9:26p Jeff
 * changed dialogs that weren't using UID_OK and UID_CANCEL to use and
 * handle them properly
 *
 * 67    3/23/99 9:02p Samir
 * up accelerator count for windows to 48.
 *
 * 66    2/28/99 3:25a Samir
 * added flag to input only numbers.
 *
 * 65    2/26/99 2:12a Samir
 * added window accelrators
 *
 * 64    2/22/99 8:13p Samir
 * added slave gadget system that only uses mouse input from window, but
 * defers keys to its master.
 *
 * 63    2/21/99 6:36p Samir
 * focusing changes and key input changes to ui.,
 *
 * 62    2/17/99 8:32p Samir
 * fixed bugs in remove gadget, added callbacks for attaching and
 * detaching gadgets.
 *
 * 61    2/16/99 12:08p Samir
 * added gadget notification system.
 *
 * 60    1/18/99 5:08a Jeff
 * added some flags related to sorted listboxes
 *
 * 59    12/30/98 12:16p Kevin
 * Auto Mission Download system
 *
 * 58    11/03/98 7:05p Samir
 * added word wrapping console.
 *
 * 57    10/20/98 12:14p Jeff
 * added color to the UIGroup
 *
 * 56    10/19/98 6:30p Jeff
 * changes made for detail variables.  Put in preset values.  Preset
 * options.  Removed terrain_cast from detail.  Put new callbacks in
 * UIListBox and UISlider
 *
 * 55    10/19/98 12:18p Samir
 * made tabbing between edit controls possible.
 *
 * 54    10/17/98 11:26a Samir
 * fixed some edit box scrolling issues.
 *
 * 53    10/16/98 1:42p Jeff
 * updated UIGroup
 *
 * 52    10/07/98 11:25a Jeff
 * created UIGroup
 *
 * 51    9/30/98 4:34p Samir
 * added enable function.
 *
 * 50    9/22/98 3:57p Samir
 * listbox prob fixed again.
 *
 * 49    9/14/98 11:22a Samir
 * enhanced editboxes
 *
 * 48    9/02/98 6:50p Samir
 * added new combo box.
 *
 * 47    8/27/98 5:03p Kevin
 * Prettied up multiplayer screens and fixed some bugs.
 *
 * 46    8/27/98 2:52p Samir
 * changing window system to work in two modes.
 *
 * 45    8/26/98 12:25p Samir
 * fixed the whole editbox, keyboard access mess.
 *
 * 44    8/25/98 7:08p Samir
 * select how keys are sent to a gadget.
 *
 * 43    8/25/98 5:27p Samir
 * new focusing rules for keyboard.
 *
 * 42    8/24/98 3:12p Samir
 * fixed text clipping
 *
 * 41    8/11/98 11:38a Samir
 * fixed listbox probs yet again. arrows on side this time.
 *
 * 40    7/29/98 3:26p Samir
 * fixed some listbox mouse problems.
 *
 * 39    6/23/98 5:05p Samir
 * console supports color per line ONLY.
 *
 * 38    6/22/98 7:31p Samir
 * added UIEdit::Activate, which activates an edit box manually.
 *
 * 37    6/22/98 2:15p Samir
 * added UIConsoleGadget.
 *
 * 36    6/05/98 5:58p Jeff
 * Added a way to change the items for the states of a HotSpot
 *
 * 35    6/05/98 5:35p Samir
 * massive improvement in UI keyboard interface.
 *
 * 34    5/22/98 5:02p Jeff
 * Added a flag for radio buttons so the button part won't be drawn (just
 * the text)
 *
 * 33    5/08/98 3:58p Samir
 * added ability to move a UI object.
 *
 * 32    4/29/98 1:04p Jeff
 * fixed up the UIListBox a bit (color control and scroll buttons)
 *
 * 31    4/29/98 11:55a Samir
 * allow user to change color of selected listbox item.
 *
 * 30    4/24/98 2:42a Samir
 * added UICheckBox
 *
 * 29    4/13/98 7:02p Samir
 * made some things protected.
 *
 * 28    3/13/98 5:18p Jeff
 * Added 2 flags for new UIListBox for scrolling and some member vars for
 * UIListBox
 *
 * 27    3/10/98 7:25p Samir
 * Changes to UISlider
 *
 * 26    3/10/98 12:48p Samir
 * Fixed flags for UIWindow so centering is supported.
 *
 * 25    3/09/98 5:05p Samir
 * Added callback to selection change function.
 *
 * 24    3/09/98 3:43p Samir
 * Made some window flag changes.
 *
 * 23    3/06/98 10:48a Samir
 * Check if button is active.
 *
 * 22    3/05/98 6:40p Samir
 * Implemented radio buttons.
 *
 * 21    3/04/98 12:08p Samir
 * Slider fixed.
 *
 * 20    2/26/98 2:50p Samir
 * Did some stuff with UISlider.
 *
 * 19    2/15/98 7:07p Samir
 * Revamped way keys like up and down are handled in window system.
 *
 * 18    2/13/98 6:34p Samir
 * Added UIStatic class.
 *
 * 17    2/10/98 4:55p Samir
 * Added radio buttons.
 *
 * 16    2/02/98 7:36p Samir
 * Added UIObject::Destroy.
 *
 * 15    1/30/98 7:03p Samir
 * Added UIConsole.
 *
 * 14    1/23/98 5:45p Samir
 * Added OnUserProcess to UIWindow class.
 *
 * 13    1/18/98 4:22p Samir
 * Implemented new UIItem system.
 *
 * 12    1/13/98 6:59p Jeff
 * (Samir) moved defines from UIlib.h to ui.h.
 *
 * 11    1/13/98 4:32p Samir
 * Made tUIInput a shared structure to be used by ui_DoFrame to return UI
 * input values.
 *
 * 10    1/13/98 4:28p Samir
 * Added sliders.
 *
 * 9     1/09/98 12:01p Samir
 * Added prototypes for sliders, listboxes, and scrollbars.
 *
 * 8     1/08/98 12:17p Samir
 * Added TitledWindow and modified the UI interface for polling.
 *
 * 7     1/05/98 4:55p Samir
 * Took out m_Flags from child classes of UIGadget
 *
 * 6     1/05/98 4:36p Samir
 * Moved centering and fittext control flags to UIGadget class.
 *
 * 5     1/05/98 4:19p Samir
 * UIGadget has fewer pure virtuals.
 *
 * 4     1/05/98 3:48p Jason
 * added SetAllText function for buttons
 *
 * 3     1/05/98 3:18p Samir
 * Added some button flags.
 *
 * 2     1/02/98 12:49p Samir
 * Edit control and static control added.
 *
 * 1     12/30/97 4:37p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#ifndef UI_H
#define UI_H

#if defined(__LINUX__)
#include "linux_fix.h" //for stricmp's through code
#endif

#include "uires.h"

#include "pstypes.h"
#include "pserror.h"
#include "grdefs.h"

//	Class identification

typedef unsigned tUIClass;

const tUIClass uiObject = 0, uiWindow = 1, uiTitledWindow = 2, uiGadget = 3, uiHotspot = 4, uiButton = 5, uiEdit = 6,
               uiText = 7, uiSlider = 8, uiVScrollBar = 9, uiListBox = 10;

const tUIClass uiNewClass = 100;

typedef int tUIBmpHandle;

class UIObject;
class UIGadget;
class UIInterface;
class UIItem;
class UITextItem;
class UIWindow;
//	----------------------------------------------------------------------------
//	UIObject
//		The absolute primitive for the UI system.   All UI class are derived from
//		tUIObject.

class UIObject {
  bool m_Created; // is this object created?

  //	variables shared by the entire UI hierarchy
protected:
  int m_X, m_Y; //	Location of UIObject relative to some other object.
  int m_W, m_H; // Dimensions of the UIObject

public:
  UIObject();
  virtual ~UIObject();

  void Create(int x, int y, int w, int h); // define the ui object.
  void Destroy() { m_Created = false; };
  bool IsCreated() const { return m_Created; };

  //	data access
  int X() const { return m_X; }; // access the X,Y,W,H fields.
  int Y() const { return m_Y; };
  int W() const { return m_W; };
  int H() const { return m_H; };

  //	moves the object.
  void Move(int x, int y, int w, int h);

  //	inheritable operations
public:
  virtual tUIClass Class() const { // Overide this function to name the class
    return uiObject;
  };
};

//	----------------------------------------------------------------------------
//	UIGadget
//		A gadget is a user interface item which a mouse or keyboard may interact with.
//		Gadgets typically are managed by their parent interface.
//		All buttons, checkboxes, listboxes, etc use tUIGadget as their parent.

// flags
#define UIF_CENTER 0x01
#define UIF_FIT 0x02
#define UIF_BORDER 0x04                  // for certain gadgets specifies that the border be drawn.
#define UIF_SLAVE 0x10                   // gadget never gets focus from ui system directly (child gadgets).
#define UIF_NOTIFYMASTERSEL 0x20         // when slave gadget is selected, the master will know.
#define UIF_PROCESS_MENU 0x40            // use this to create a 'menu style' window (Options menu)
#define UIF_PROCESS_ALL UIF_PROCESS_MENU // to maintain compatibility with older code.
#define UIF_GROUP_START 0x80             // starts a group of gadgets that use the up and down arrows to move between
#define UIF_GROUP_END 0x100              // ends a group

#define UIF_CUSTOMF 0x200 // use this flag and any higher for custom gadget flags, a list of predefs below

#define UILB_NOSCROLL 0x800       // turns off automatic scroll buttons on UIListBox
#define UILB_AUTOSELECT 0x1000    // turns on automatic change of SelectedIndex if scrolled out of view
#define UILB_NOSORT 0x2000        // disables sorting in a listbox
#define UILB_CASESENSITIVE 0x4000 // only if !UILB_NOSORT. Makes the sorting case sensitive

#define UIRB_NOBUTTON 0x800 // disables the drawing of the button on the left of the text of a radio button

#define UIED_PASSWORD 0x800    // special password masking for edit box text (*)
#define UIED_NUMBERS 0x1000    // only accept numbers for input!
#define UIED_AUTOSELECT 0x2000 // selects when input reaches buffer length.

//	any flags after 0x10000-0x40000000 are reserved internal to gadget controls

//	ids
#define UID_OK 0xEE
#define UID_CANCEL 0xEF

class UIGadget : public UIObject {
  friend class UIWindow;

  UIGadget *m_Prev;
  UIGadget *m_Next; // for maintaining list of linked gadgets.

  // master gadgets
  UIGadget *m_MasterGadget; // select target
  UIGadget *m_CurrentSlave; // current slave gadget in master.

  // slave gadgets
  UIGadget *m_SlaveGadgets; // contains a list of slave gadgets.
  UIGadget *m_NextSlave;
  UIGadget *m_PrevSlave;

  //	information for gadgets
private:
  int m_ID;      // id value of gadget.
  int16_t m_Datum; // used to pass info around.
  uint16_t m_Hotkey;
  int m_SavedW, m_SavedH; // saved values of width and height.
  bool m_Disabled;        // is gadget disabled?

  static int m_LastKey;       // the last key pressed.
  static int m_LastKeyCount;  // number of times last key was pressed.
  static float m_LastKeyTime; // last key time.

  bool TrapKey(int key); // used to manage keypresses so repeating isn't quick.
  void UntrapKey(int key);
  void CheckFocusOnSlaves(int mx, int my);

//	universal variables
#ifdef __LINUX__ // gcc has a hard time tracing through some of the derived classes that access m_Wnd
public:
#else
protected:
#endif
  UIWindow *m_Wnd; // the gadget's parent window

protected:
  int m_Flags;    // flags
  bool m_infocus; // gadget has focus.

  int GetSavedW() const { return m_SavedW; };
  int GetSavedH() const { return m_SavedH; };
  inline bool HasFocus() const;
  UIGadget *GetPrevUsableGadget(); // gets next gadget lower in chain that's not disabled
  UIGadget *GetNextUsableGadget(); // gets next gadget higher in chain that's not disabled
  void LostFocus();                // called by window system
  void GainFocus();                // called by window system
  void LockFocus();                // forces input to this gadget
  void UnlockFocus();              // releases lock on input to gadget.

//	called from outside gadget hierarchy.
#ifdef __LINUX__ // gcc has a hard time tracing through the dervived classes of newuiButton and thinks it can't access
                 // OnFormat()
public:
#else
protected:
#endif
  virtual void OnFormat(); // override: called when resized or before drawing.

protected:
  virtual void OnLostFocus(){};        // override: behavior when gadget loses input focus.
  virtual void OnGainFocus(){};        // override: behavior when gadget gains input focus.
  virtual void OnAttachToWindow(){};   // override: when gadget is attached to window, this is called.
  virtual void OnDetachFromWindow(){}; // override: when gadget is detached from window, this is called.
  virtual void OnDraw() = 0;           // MUST override: behavior when gadget is being drawn.

  //	called by Process.
protected:
  virtual void OnKeyDown(int key){};               // override: behavior when key is pressed.
  virtual void OnKeyUp(int key){};                 // override: behavior when key is released.
  virtual void OnMouseBtnDown(int btn){};          // override: behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn){};            // override: behavior when mouse button is released.
  virtual void OnDestroy(){};                      // override: behavior when gadget is destroyed.
  virtual void OnUserProcess(){};                  // override: behavior when gadget is processed
  virtual void OnNotifySelect(UIGadget *sender){}; // override: send gadget select message to another gadget.

  //	typically this function is called by a child class when we want
  //	to tell the caller that this gadget was selected for something.
  virtual void OnSelect(); // override: behavior when gadget is selected.

public:
  virtual void OnNotify(UIGadget *){}; // usually called by a child gadget of a gadget.

public:
  UIGadget();
  virtual ~UIGadget();

  UIWindow *GetWindow() { // returns the parent window for a gadget.
    return m_Wnd;
  };

  //	returns link in gadget chain.
  UIGadget *Next() const { return m_Next; };
  UIGadget *Prev() const { return m_Prev; };

  //	defines the graphical representation of a gadget within a window.
  //	ALL Gadgets must have a wnd.
  void Create(UIWindow *wnd, int id, int x, int y, int w, int h, int flags);
  void Destroy();

  //	interprets input on this gadget.  this gadget is in focus.
  void Process(bool do_keys = true, bool do_mouse = true, bool do_user = true);
  bool IsLocked() const; // is this gadget's focus locked?

  //	settings
  void SetHotkey(int key); // set this when key is pressed, selects gadget.
  int GetID() const { return m_ID; };
  int16_t GetDatum() const { return m_Datum; };
  void SetDatum(int16_t datum) { m_Datum = datum; };
  bool IsDisabled() { return m_Disabled; }; // returns disabled state.
  void Disable() { m_Disabled = true; };    // disables gadget.
  void Enable() { m_Disabled = false; };    // enables gadget.
  int GetFlags() const { return m_Flags; }; // gets flags for gadget.
  void SetFlag(int flag);
  void ClearFlag(int flag);

  // OnSelect messages to another gadget
  void AttachSlaveGadget(UIGadget *gadget);
  void DetachSlaveGadget(UIGadget *gadget);

  //	class id
  virtual tUIClass Class() const { // Overide this function to name the class
    return uiGadget;
  };
};

//	----------------------------------------------------------------------------
//	UIHotspot
//		This is simply a region within the parent window that when clicked on
//		or key pressed, does something.

class UIHotspot : public UIGadget {
  UIItem *m_ItemOff, *m_ItemOn; // off and on states items.
  UIItem *m_ItemCur;            // current item.

protected:
  virtual void OnKeyDown(int key);      // override: behavior when key is pressed.
  virtual void OnKeyUp(int key){};      // override: behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // override: behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // override: behavior when mouse button is released.
  virtual void OnFormat();              // override: called when resized or before drawing.
  virtual void OnDraw();                // override: behavior when gadget is being drawn.
  virtual void OnLostFocus();           // override: behavior when gadget loses input focus.
  virtual void OnGainFocus();           // override: behavior when gadget gains input focus.
  virtual void OnDestroy();             // override: behavior when gadget is destroyed.

public:
  UIHotspot();
  virtual ~UIHotspot();

  //	optional key, when pressed, triggers hotspot.
  void Create(UIWindow *wnd, int id, int key, UIItem *itemoff, UIItem *itemon, int x, int y, int w, int h,
              int flags = 0);

  // sets the items for the on/off state of the hotspot
  void SetStates(UIItem *itemoff, UIItem *itemon);

  //	class id
  virtual tUIClass Class() const { // Overide this function to name the class
    return uiHotspot;
  };
};

//	tUIButton family
//		this family contains buttons, radio buttons, and checkboxes

//	states
#define UI_BTS_NUM 4
#define UI_BTS_DISABLED 0
#define UI_BTS_INACTIVE 1
#define UI_BTS_HILITE 2
#define UI_BTS_ACTIVATED 3

//	----------------------------------------------------------------------------
//	UIButton
//		This is a simple 2 state button (push down or push up)
//		Buttons have properties of gadgets, plus bitmap information per state.

class UIButton : public UIGadget {
private:
  UIItem *m_Items[UI_BTS_NUM];     // UI Items for each state
  ddgr_color m_Colors[UI_BTS_NUM]; // Backgrounds for states

  static int m_ButtonFont; // button fonts.

protected:
  int m_State; // state of button

  UIItem *GetStateItem(int state) {
    ASSERT(state < UI_BTS_NUM);
    return m_Items[state];
  };

  int GetColor(int state) const {
    ASSERT(state < UI_BTS_NUM);
    return m_Colors[state];
  };

public:
  static void SetDefaultFont(int font) { // sets the button font
    UIButton::m_ButtonFont = font;
  };

public:
  UIButton();
  virtual ~UIButton();

  void Create(UIWindow *parent, int id, UIItem *title, int x, int y, int w, int h, int flags = 0);

  virtual tUIClass Class() const { // Overide this function to name the class
    return uiButton;
  };

  //	settings
  void SetStateItem(int state, UIItem *item); // sets the background bitmap for a specified button state
  void SetAllStates(UIItem *item);            // Sets text for all states
  void SetColor(int state, ddgr_color col);
  void Disable(); // this adds to the gadget equivalent
  void Enable();  // this adds to the gadget equivalent

  //	inheritable operations
protected:
  virtual void OnLostFocus(); // behavior when gadget loses input focus.
  virtual void OnGainFocus(); // behavior when gadget gains input focus.
  virtual void OnDraw();      // behavior when gadget is being drawn.
  virtual void OnFormat();    // override: called when resized or before drawing.

  //	called by Process.
protected:
  virtual void OnKeyDown(int key);      // behavior when key is pressed.
  virtual void OnKeyUp(int key);        // behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released.
  virtual void OnDestroy();             // override: behavior when gadget is destroyed.

  //	typically this function is called by a child class when we want
  //	to tell the caller that this gadget was selected for something.
  //	virtual void OnSelect();						// override: behavior when gadget is
  // selected.
};

//	check boxes use most of the behavior of default buttons.
//		the only difference is how states are set when an item is selected.
class UICheckBox : virtual public UIButton {
public:
  UICheckBox();

  void Create(UIWindow *parent, int id, UIItem *title, int x, int y, int w, int h, int flags);

  void SetCheck(bool state); // turns on button (of off)
  bool IsChecked() const     //	returns true if button is set.
  {
    return (m_State == UI_BTS_ACTIVATED) ? true : false;
  };

protected:
  virtual void OnDraw();   // behavior when gadget is being drawn.
  virtual void OnFormat(); // override: called when resized or before drawing.

  virtual void OnLostFocus();           // behavior when gadget loses input focus.
  virtual void OnGainFocus();           // behavior when gadget gains input focus.
  virtual void OnKeyDown(int key);      // behavior when key is pressed.
  virtual void OnKeyUp(int key);        // behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released.
};

//	radio buttons use most of the behavior of default buttons.
//		the only difference is how states are set when an item is selected.
class UIRadioButton : virtual public UIButton {
  UIRadioButton *m_PrevRB; // previous radio button in group.
  UIRadioButton *m_NextRB; // next radio button in group.

  void ActivateButton(); // activates this button, deactivating all others.

public:
  UIRadioButton();

  // flags.  the group flags are set internally by Create.  if prev_rb is NULL, that's the start.
  void Create(UIWindow *parent, UIRadioButton *prev_rb, int id, UIItem *title, int x, int y, int w, int h, int flags);

  void Activate();         // turns on button, turns off others in group.
  bool IsActivated() const //	returns true if button is set.
  {
    return (m_State == UI_BTS_ACTIVATED) ? true : false;
  };

protected:
  virtual void OnDraw();   // behavior when gadget is being drawn.
  virtual void OnFormat(); // override: called when resized or before drawing.

  virtual void OnLostFocus();           // behavior when gadget loses input focus.
  virtual void OnGainFocus();           // behavior when gadget gains input focus.
  virtual void OnKeyDown(int key);      // behavior when key is pressed.
  virtual void OnKeyUp(int key);        // behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released.
};

//	----------------------------------------------------------------------------
//	UIStatic
//		Just a static image/text/etc.

class UIStatic : public UIGadget {
protected:
  UIPrimativeItem *m_Background;
  UIItem *m_Title;

public:
  UIStatic();
  virtual ~UIStatic();

  void Create(UIWindow *parent, UIItem *item, int x, int y, int w, int h, int flags = 0);
  void SetBackground(UIPrimativeItem *prim);
  void SetTitle(UIItem *item);
  UIItem *GetItem() const { return m_Title; };

protected:
  virtual void OnDraw();    // behavior when gadget is being drawn.
  virtual void OnFormat();  // override: called when resized or before drawing.
  virtual void OnDestroy(); // called when gadget is being nuked.
};

//	----------------------------------------------------------------------------
//	UIText
//		This is a simple text.

class UIText : public UIStatic {
public:
  void Create(UIWindow *parent, UITextItem *text, int x, int y, int flags = 0);

  //	inheritable operations
protected:
  virtual void OnFormat(); // override: called when resized or before drawing.
};

//	----------------------------------------------------------------------------
//	UIProgress
//		Progress Bar

class UIProgress : public UIStatic {
public:
  void Create(UIWindow *parent, int x, int y, int w, int h, int flags = 0);
  void Update(float progress); // Call with a value from 0-1.0 to specify progress

  //	inheritable operations
protected:
  float m_Progress;
  int m_ProgressWidth;
  virtual void OnDraw();   // behavior when gadget is being drawn.
  virtual void OnFormat(); // override: called when resized or before drawing.
};

//	----------------------------------------------------------------------------
//	UIGroup
//		Draws a group box on to the window

class UIGroup : public UIStatic {
public:
  UIGroup();
  ~UIGroup();
  void Create(UIWindow *parent, char *label, int x, int y, int w, int h, ddgr_color label_color = GR_WHITE,
              ddgr_color box_color = GR_WHITE, int flags = 0);

  //	inheritable operations
protected:
  bool m_bTextCreated;
  UIText m_tLabel;
  char *m_Label;
  ddgr_color m_LabelColor;
  ddgr_color m_BoxColor;
  virtual void OnDraw();
  virtual void OnDestroy();
};

//	----------------------------------------------------------------------------
//	UIEdit
//		A single line edit control.

#define KEYDOWN_FIRST_DELAY 0.5f
#define KEYDOWN_REPEAT_DELAY 0.10f

class UIEdit : public UIGadget {
  char *m_TextBuf;        // Text buffer for edit control.
  int m_FontHandle;       // font for edit control. (default -1 = window's font)
  int m_BufSize;          // buffersize
  int m_Color;            // color of text.
  int m_CursorPosX;       // text cursor position within box.
  bool m_Active;          // active?
  int m_CurPos;           // cursor postion in buffer.
  int m_StartPos;         // active start position in buffer of what's drawn.
  int m_X1b, m_X2b, m_Yb; // x boundaries of text.
  int m_ScrollThresh;     // scrolling x threshold.
  bool m_UpdateCount;     // used to update scroll position on next draw frame.

  //	called from outside gadget hierarchy.
protected:
  void DrawText();                              // draws text in box
  void Deactivate();                            // deactivates edit box (use if you know what you're doing.)
  void SetTextBounds(int x1, int x2, int yoff); // horizontal clipping of text within editbox

  //	called from outside gadget hierarchy.
protected:
  virtual void OnLostFocus(); // override: behavior when gadget loses input focus.
  virtual void OnGainFocus(); // override: behavior when gadget gains input focus.
  virtual void OnDraw();      // behavior when gadget is being drawn.

  //	called by Process.
protected:
  virtual void OnKeyDown(int key);      //	behavior when key is pressed.
  virtual void OnKeyUp(int key);        // behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released.
  virtual void OnSelect();
  virtual void OnDestroy(); // override: behavior when gadget is destroyed.

public:
  UIEdit();
  virtual ~UIEdit();

  void Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags = 0);

  //	settings
  void SetBufferLen(int length);       // sets the length of the input buffer.
  void SetText(const char *text);            // sets the text buffer.
  void GetText(char *buffer, int len); // retrieve text in edit control.
  void SetFont(int font);              // sets font of control (default is window's font.)
  void SetColor(ddgr_color col);       // sets color of text.
  void Activate();                     // activates edit box manually (allows editing.)

  virtual tUIClass Class() const { // Overide this function to name the class
    return uiEdit;
  };
};

//	----------------------------------------------------------------------------
//	UISlider
//		A simple slider

class UISlider : public UIGadget {
  void (*selectchange_fn)(int);            // callback when selection changes in slider
  void (*selectchange_id_fn)(int, void *); // callback when selection changes in slider, also returns the ID
  void *m_callbackptr;                     // user defined callback pointer
  int m_Pos;                               // this is the returned value as shown in the range.
  int m_Range;                             // returned value of slider is 0 to m_Range-1.
  int m_PixelWidth;                        // used to get the current position of slider.
  float m_IntervalWidth;                   // width of one tick o
  int switch_x, switch_y;                  // little box width and height.
  int switch_w, switch_h;

  UIItem *switch_item; // slider switch item
  UIItem *slider_item; // slider item

public:
  UISlider();
  virtual ~UISlider();

  void Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags = 0);

  //	sets visual characteristics of slider.
  void SetSliderSwitchItem(UIItem *item);
  void SetSliderItem(UIItem *item);

  virtual tUIClass Class() const { // Overide this function to name the class
    return uiSlider;
  };

  //	settings
  void SetRange(int range); // sets range of scroll bar
  int GetRange() const {    // range of scroll bar
    return m_Range;
  };
  void SetPos(int pos) { // sets the position of the slider.
    if (pos < 0)
      pos = 0;
    else if (pos >= m_Range)
      pos = m_Range - 1;
    m_Pos = pos;
  };
  int GetPos() const { // gets position of slider.
    return m_Pos;
  };

  void SetSelectChangeCallback(void (*fn)(int));
  void SetSelectChangeCallback(void (*fn)(int, void *), void *ptr);

  //	called from outside gadget hierarchy.
protected:
  virtual void OnFormat();              // override: called when resized or before drawing.
  virtual void OnLostFocus(){};         // override: behavior when gadget loses input focus.
  virtual void OnGainFocus(){};         // override: behavior when gadget gains input focus.
  virtual void OnDraw();                // behavior when gadget is being drawn.
  virtual void OnDestroy();             // behavior when gadget is being destroyed.
  virtual void OnKeyDown(int key);      //	behavior when key is pressed.
  virtual void OnKeyUp(int key);        // behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released.
  virtual void OnSelect();              // override
};

//	----------------------------------------------------------------------------
//	UIListBox
//		A listbox may contain text items
//		Allows the user to scroll through them too.

#define LISTBOX_BUFFER_SIZE 20

class UIListBox : public UIGadget {
  void (*selectchange_fn)(int);            // callback when selection changes in listbox.
  void (*selectchange_id_fn)(int, void *); // callback when selection changes in listbox..also return the ID
  void *m_callbackptr;                     // user defined callback pointer
  ddgr_color m_SelectColor;                // selected text color
  ddgr_color m_HiliteColor;                // color of hilite bar
  int m_LastMseX, m_LastMseY;              // used for double clicking.
  uint8_t m_Alpha;                           // alpha value of listbox.

  bool MseCheckSelect(int x, int y);        // check if x and y selection hits a selected item.
  void SetInternalSelectedIndex(int index); //  call by listbox system.

protected:
  int m_TextOffX, m_TextOffY;   // offset of text to border.
  int m_ArrowWidth;             // with of arrow.
  int m_CX, m_CY, m_CX2, m_CY2; // clipping text.

public:
  UIListBox();
  virtual ~UIListBox();

  void Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags = 0);

  virtual tUIClass Class() const { // Overide this function to name the class
    return uiListBox;
  };

  //	settings
  void AddItem(const UIItem *item);    // adds an item to the list, no sorting
  void RemoveItem(const UIItem *item); // removes an item from the list.
  void RemoveAll();                    // empties listbox
  void SelectItem(const UIItem *item); // selects the given item in the list.
  UIItem *GetItem(int index) const;    // returns the item at listbox index given.

  int GetListIndex() const;     // returns the current listbox index
  void SetListIndex(int index); // sets the index of a listbox

  int GetSelectedIndex() const;          // returns which item index is selected
  void SetSelectedIndex(int index);      // selects an item based on index and moves listbox
  void SetSelectedColor(ddgr_color col); // selected text color.
  void SetHiliteColor(ddgr_color col);   // sets the hilite bar color

  void SetSelectChangeCallback(void (*fn)(int));
  void SetSelectChangeCallback(void (*fn)(int, void *), void *ptr);

  //	called from outside gadget hierarchy.
protected:
  virtual void OnLostFocus();           // override: behavior when gadget loses input focus.
  virtual void OnGainFocus();           // override: behavior when gadget gains input focus.
  virtual void OnDraw();                // behavior when gadget is being drawn.
  virtual void OnKeyDown(int key);      //	behavior when key is pressed.
  virtual void OnKeyUp(int key);        // behavior when key is released.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released.
  virtual void OnSelect();
  virtual void OnDestroy();     // called when destroyed.
  virtual void OnUserProcess(); // override: behavior when gadget is processed

private:
  UIItem **m_ItemList; // list of items in listbox
  int *m_Virt2Real;    // translates virtual(user) id to real index
  int *m_Real2Virt;    // translates real index into virtual(user) id

  float m_ClickTime; // done to check for double clicks?
  int m_MouseState;  // done for mouse selection.
  int m_MouseX, m_MouseY;
  int m_NumItems;                 // number of items in list.
  int m_SelectedIndex;            // current selected index into listbox
  int m_Index;                    // current index of visible items.
  bool m_ShowDown, m_ShowUp;      // whether the down and up arrows are displayed
  int m_UpArrowY0, m_DownArrowY0; // up and down arrow y locations.
  int m_UpArrowY1, m_DownArrowY1; // up and down arrow y max locations.
  int m_NumVisibleItems;          // number of visible items in list viewport.

public:
  int GetNumItems() const { return m_NumItems; };
};

//	----------------------------------------------------------------------------
//	UIComboBox
//		A listbox may contain text items, BUT only one will be visible
//		Allows the user to scroll through them too.

class UIComboBox : public UIGadget {
public:
  UIComboBox();
  virtual ~UIComboBox();

  void Create(UIWindow *parent, int id, int x, int y, int w, int h, int flags = 0);

private:
  UIItem **m_ItemList; // list of items in listbox
  int m_nItems;        // number of items.
  int m_ArrY, m_ArrH;  // up and down arrow dimensions
  int m_UpArrX, m_UpArrW, m_DownArrX, m_DownArrW;
  int m_Index;                  // current index.
  void (*selectchange_fn)(int); // callback when selection changes in listbox.
  bool m_ShowUp, m_ShowDown;
  float m_scrolltimer; // scroll timer for delay in mouse.
  int m_scrollstage;   // determines how scrolling will work.

public:
  void AddItem(const UIItem *item);
  void RemoveItem(const UIItem *item); // removes an item from the list.
  void RemoveAll();                    // empties listbox
  void SelectItem(const UIItem *item); // selects the given item in the list.
  UIItem *GetItem(int index) const;    // returns the item at listbox index given.

  int GetSelectedIndex() const { // returns which item index is selected
    return m_Index;
  };
  void SetSelectedIndex(int index); // sets the selected index.

  void SetSelectChangeCallback(void (*fn)(int));

protected:
  virtual void OnDraw();                // behavior when gadget is being drawn.
  virtual void OnKeyDown(int key);      //	behavior when key is pressed.
  virtual void OnMouseBtnDown(int btn); // behavior when mouse button is pressed.
  virtual void OnMouseBtnUp(int btn);   // behavior when mouse button is released
  virtual void OnSelect();
  virtual void OnDestroy(); // called when destroyed.

protected:
  int m_CX, m_CY, m_CX2, m_CY2; // text clippers.
};

//	----------------------------------------------------------------------------
//	UIConsoleGadget
//		a console that's a gadget within a window

class UIConsoleGadget : public UIGadget {
  int m_ConsoleFont;       // standard font for text in console
  ddgr_color *m_ColorRows; // color per row.
  char *m_ConsoleBuffer;   // text buffer of console.
  int m_Rows, m_Cols;      // dimensions in text.
  int m_VisRows;           // visible rows and columns
  int m_VisRowStart;       // scroll start of visible region of buffer.
  int m_CurRow, m_CurCol;  // current row and column of text pointer
  int m_OffX, m_OffY;
  int m_Rowsize;          // rowsize of character buffer.
  ddgr_color m_LineColor; // color of current line.
  int m_LineIndex;        // index within current row memory-wise(not column wise).
  int m_PutsBufLen;       // current length of puts buffer
  char *m_PutsBuffer;     // puts buffer.

private:
  void PutChar(int ch); // outputs a character onto the console.
  void Scroll();        // scrolls window.

protected:
  virtual void OnDraw();        // behavior when gadget is being drawn.
  virtual void OnUserProcess(); // behavior when gadget is processed
  virtual void OnDestroy();     // behavior when gadget is destroyed.

public:
  UIConsoleGadget();
  virtual ~UIConsoleGadget();

  //	font = console font, NOT GADGET FONT.   This font is used to proportion window
  void Create(UIWindow *parent, int id, int x, int y, int font, int cols, int rows, int flags = UIF_BORDER);

  //	functions
  void puts(ddgr_color color, const char *str);
};

//	----------------------------------------------------------------------------
//	UIWindow
//		A window contains different UIGadgets.
//		This is where all objects will interact with the user.
#define N_WINDOW_ACCELS 48

class UIWindow : public UIObject {
  friend class UIGadget;

  UIGadget *m_GadgetHead; // gadget list for window
  UIGadget *m_GadgetTail;
  UIGadget *m_GadgetCur;
  UIGadget *m_LockedGadget; // marks a particular gadget that will always have focus
  UIItem *m_BackItem;       // background UI item.

  float m_KeyTime; // time when key went down.

  ddgr_color m_BackColor; // unconditional background color
  int m_FontHandle;
  int m_LastKey;       // the last key pressed.
  int m_LastKeyCount;  // number of times last key was pressed.
  float m_LastKeyTime; // last key time.
  bool m_HoldHotkeys;
  bool m_ResetCurGadget;   // next process will reset current gadget to 1st valid one.
  bool m_CurGadgetInGroup; // is m_GadgetCur inside a group?
  struct {
    int key;
    int id;
  } m_Accelerators[N_WINDOW_ACCELS]; // used for quick key press interaction
  int m_naccels;

  static int m_WindowFont; // global window default font

private:
  bool TrapKey(int key);
  void UntrapKey(int key);
  void LockFocusOnGadget(UIGadget *gadget); // forces a particular gadget into focus, always until unlocked.
  void UnlockFocusOnGadget();

protected:
  ddgr_color GetBackColor() const { return m_BackColor; };

  int m_Flags; // window flags.

  //	inheritable actions
protected:
  virtual void OnDraw();           // overridable draws the window background before gadgets
  virtual void OnUserProcess();    // overridable: runs after window is processed, to supplement it.
  virtual void OnDestroy(){};      // overridable: called in Destroy
  virtual void OnKeyDown(int key); //	behavior when key is pressed.
  virtual void OnKeyUp(int key);   // behavior when key is released.

public:
  static void SetDefaultFont(int font) { // sets the default font for any window
    UIWindow::m_WindowFont = font;
  };

public:
  UIWindow();
  virtual ~UIWindow();

  void Destroy(); // must call if you created window. will be called in destructor

  void Create(int x, int y, int w, int h, int flags = 0);
  int GetFlags() const { return m_Flags; };

  // used to mark key pressed to id numbers
  void AddAcceleratorKey(int key, int id);
  void ResetAcceleratorKey();

  //	gadget management
  void AddGadget(UIGadget *gadget);    //	adds a gadget to the gadget list
  void RemoveGadget(UIGadget *gadget); // removes a gadget from the list.
  UIGadget *GetGadgetFromID(int id);   // returns the gadget pointer given an id if in window
  void SetFocusOnGadget(UIGadget *gadget, bool key = false);

  UIGadget *GetFocus() { return m_GadgetCur; };

  //	input/output management
  virtual int Process(); // handles gadget selection/focus and calls gadgets.
  void Render();         // renders one window frame.
  void Open();           // adds window to ui list.
  void Close();          // removes window from ui list.

  //	settings
  void SetFont(int handle);        // sets window's font.
  void SetBackItem(UIItem *item) { // sets the background drawing item.
    if (m_BackItem)
      delete m_BackItem;
    m_BackItem = NULL;
    if (item)
      m_BackItem = item->CopyUIItem();
  };                                  //
  void SetBackColor(ddgr_color col) { // sets the background color.  this is ALWAYS first, then the backitem
    m_BackColor = col;
  };

  void HoldHotkeys() { m_HoldHotkeys = true; }; // no hotkeys will be processed until ResumeHotkeys is called.
  void ResumeHotkeys() { m_HoldHotkeys = false; };

  //	class id
  virtual tUIClass Class() const { // Overide this function to name the class
    return uiWindow;
  };

  // OBSOLETE
  void LockKeyFocusOnGadget(UIGadget *gadget); // forces all keyinput onto one gadget. (be wary)
};

//	Special windows
//		titled window (functions as a standard dialog box.), without modality though.

class UITitledWindow : public UIWindow {
  UITextItem m_Title;    // title of window
  int m_CaptionColor;    // caption's color.
  int m_BorderThickness; // border thickness.

public:
  UITitledWindow();
  virtual ~UITitledWindow();

  void Create(UITextItem &title, int x, int y, int w, int h);

  //	class id
  virtual tUIClass Class() const { // Overide this function to name the class
    return uiTitledWindow;
  };

  // settings
  void SetText(UITextItem &text) { // sets the text for a window title.
    m_Title = text;
  };
  void SetCaptionColor(ddgr_color col) { // sets the color of the caption region
    m_CaptionColor = col;
  };
  void SetBorderThickness(int thickness) { // sets the pixel thickness of the border
    m_BorderThickness = thickness;
  };

  int GetBorderThickness() const { return m_BorderThickness; }; // returns border thickness.

  //	inheritable actions
protected:
  virtual void OnDraw(); // overridable draws the window background before gadgets
};

//	UIConsole
//		should display a simple console window where anyone can dump text into

class UIConsole : public UIWindow {
  UIConsoleGadget m_Console;

protected:
  virtual void OnDraw();

public:
  UIConsole();
  virtual ~UIConsole();

  //	font = console font, NOT GADGET FONT.   This font is used to proportion window
  void Create(int x, int y, int font, int cols, int rows);
  void Destroy();

  //	functions
  void puts(const char *str);
  void puts(ddgr_color col, const char *str);
};

//	other inline functions
inline bool UIGadget::HasFocus() const { return ((m_Wnd->GetFocus() == this) ? true : false); };

#include "uisys.h"
#include "uidraw.h"

#endif
