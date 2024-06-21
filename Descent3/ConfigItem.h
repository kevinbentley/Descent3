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

 * $Logfile: /DescentIII/main/ConfigItem.h $
 * $Revision: 8 $
 * $Date: 10/19/98 6:30p $
 * $Author: Jeff $
 *
 * Contains the class info for ConfigItem [config dialog UI objects]
 *
 * $Log: /DescentIII/main/ConfigItem.h $
 *
 * 8     10/19/98 6:30p Jeff
 * changes made for detail variables.  Put in preset values.  Preset
 * options.  Removed terrain_cast from detail.  Put new callbacks in
 * UIListBox and UISlider
 *
 * 7     10/16/98 1:42p Jeff
 * added CIF_USEGROUP and general dialog look
 *
 * 6     9/02/98 2:54p Jeff
 * added defines for text colors to be used throughout the game...fixed up
 * buddy menu too
 *
 * 5     6/05/98 5:59p Jeff
 * Added a CIT_CHECKBOX style
 *
 * 4     5/23/98 6:33p Jeff
 * Added some flags for the slider, and fixed it up a bit
 *
 * 3     5/22/98 5:02p Jeff
 * Increased functionality
 *
 * 2     5/21/98 10:35p Jeff
 * Initial creation
 *
 * $NoKeywords: $
 */

#ifndef __CONFIGITEM_H_
#define __CONFIGITEM_H_

#include "newui.h"

#if defined(__LINUX__) || defined(ANDROID)
void CIListBoxCallback(int ID, void *);
void CISliderCallback(int ID, void *);
#endif

// config item types
#define CIT_HOTSPOTLIST 0x01
#define CIT_SLIDER 0x02
#define CIT_ONOFFBUTTON 0x03
#define CIT_LISTBOX 0x04
#define CIT_YESNOBUTTON 0x05
#define CIT_RADIOBUTTON 0x06
#define CIT_CHECKBOX 0x07

// config item value types
#define CIV_BOOL 0x01
#define CIV_INT 0x02
#define CIV_FLOAT 0x03

// config item flags
#define CIF_PERCENT 0x01   // tells a slider to display a percent sign
#define CIF_NODECIMAL 0x02 // tells a slider not to display a decimal point (float sliders only)
#define CIF_USEGROUP 0x04  // places a group box around the configitem (CIT_RADIOBUTTON only)

#define HOTSPOTLIST_GAP 8      // the horizontal gap between hotspot lists
#define LISTBOX_LABELGAP 3     // the vertical gap between label and listbox
#define RADIOBUTTON_LABELGAP 3 // the vertical gap between label and radiobutton list
#define RADIOBUTTON_GAP 3      // the vertical gap between radiobuttons

int GetUniqueID(void);

class ConfigItem {
public:
  ConfigItem();
  ~ConfigItem();

  // create functions
  bool Create(NewUIGameWindow *parentwnd, int type, char *label, int x, int y, int w, int h, int initialvalue,
              int flags, int item_x);
  bool Create(NewUIGameWindow *parentwnd, int type, char *label, int x, int y, int w, int h, bool initialvalue,
              int flags, int item_x);
  bool Create(NewUIGameWindow *parentwnd, int type, char *label, int x, int y, int w, int h, float initialvalue,
              int flags, int item_x);

  // destroy function
  void Destroy(void);

  // gets the current value (returns true on success)
  bool GetCurrentValue(int *currvalue);
  bool GetCurrentValue(bool *currvalue);
  bool GetCurrentValue(float *currvalue);

  // sets the current value for the item
  bool SetCurrentValue(int currvalue, bool call_callback = true);
  bool SetCurrentValue(bool currvalue, bool call_callback = true);
  bool SetCurrentValue(float currvalue, bool call_callback = true);

  // gets the initial value (returns true on success)
  bool GetInitialValue(int *initvalue);
  bool GetInitialValue(bool *initvalue);
  bool GetInitialValue(float *initvalue);

  // set range
  void SetRange(int min, int max, int range);
  void SetRange(float min, float max, int range);

  // sets a callback for when an item changes
  void SetCallback(void (*callback)(float));
  void SetCallback(void (*callback)(int));
  void SetCallback(void (*callback)(bool));

  // updates the config item (pass in result from DoUI)
  void Update(int result);

  // adds items to the config item (count is number of items, followed by a list of UITextItems)
  void Add(int count, ...);

  friend void CIListBoxCallback(int ID, void *);
  friend void CISliderCallback(int ID, void *);

private:
  bool Create(NewUIGameWindow *parentwnd, int type, int flags, int x, int y, int w, int h, char *label, int item_x);
  void UpdateHotSpotList(int index);
  void UpdateSlider(int index, bool call_callback = true);
  void UpdateOnOffButton(int index);
  void UpdateListBox(int index);
  void UpdateYesNoButton(int index);
  void UpdateRadioButton(int index);
  void UpdateCheckBox(int index);

  bool m_bAlive; // true is the config item has been created not destroyed yet
  // Initial value of the config item
  union {
    bool m_bInitial;
    int m_iInitial;
    float m_fInitial;
  };
  // current value of the config item
  union {
    bool m_bCurrentValue;
    int m_iCurrentValue;
    float m_fCurrentValue;
  };
  int m_X, m_Y, m_W, m_H;   // x,y, width and height for the config item
  int curr_x, curr_y;       // current x and y (relative to m_X and m_Y)
  int m_iFlags;             // flags for config item
  int m_iType;              // how is this config item represented
  int *m_iID;               // unique ID[s] of the config item
  int m_iNumIDs;            // number of IDs
  int m_iItems;             // number of items associated with this config item
  int m_iValueType;         // what kind of value is this config item holding
  UIText m_tLabel;          // Text item for the label
  UIGroup m_gGroup;         // Group box if needed
  int m_auxX;               // contains the original x passed in
  int m_auxY;               // contains the original y passed in
  UIText m_tLabel2;         // Used for Sliders
  NewUIGameWindow *m_hWnd;  // parent window
  UITextItem **m_tiList;    // list of text items for config item
  int m_tiCount;            // number of text items
  UIHotspot **m_hsList;     // list of hotspot items
  int m_hsCount;            // number of hotspot items
  NewUISlider **m_sList;    // list of slider items
  int m_sCount;             // number of sliders
  UIRadioButton **m_rbList; // list of radio buttons
  int m_rbCount;            // number of radio buttons
  NewUIButton **m_bList;    // list of button items
  int m_bCount;             // number of buttons
  NewUIListBox **m_lbList;  // list of list boxes
  int m_lbCount;            // number of list boxes
  float m_fMin, m_fMax;     // range min/max
  int m_iRange;             // range
  float m_fUnit;            // scale between min->max to fit in range
  char *m_labeltext;        // we need to save the label for group boxes
  void (*m_fCallback)(float);
  void (*m_iCallback)(int);
  void (*m_bCallback)(bool);
};

#endif
