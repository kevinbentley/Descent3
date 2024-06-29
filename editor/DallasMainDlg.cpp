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

* $Logfile: /DescentIII/Main/editor/DallasMainDlg.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:57:37 $
* $Author: kevinb $
*
* This is the code for the main dialog of the DALLAS graphical scripting interface
*
* $Log: not supported by cvs2svn $
 *
 * 87    10/23/99 6:16p Nate
 * Added support for Polish Message Files
 *
 * 86    10/08/99 4:55p Nate
 * Dallas will now attempt to load the english .msg if a foreign language
 * .msg cannot be found
 *
 * 85    8/31/99 12:05p Nate
 * Copy command now displays an "Invalid Copy" message and returns if
 * selected item cannot be copied (instead of just copying the entire
 * script)
 *
 * 84    8/30/99 4:11p Nate
 * Added copy/paste for conditions, log ops, and nested if-then clauses
 *
 * 83    6/17/99 10:24a Kevin
 * Made things work in a release build
 *
 * 82    6/09/99 7:05p Jeff
 * stub functions added.  #ifdef NEWEDITORs added, files changed, to get
 * Dallas integrated into new editor
 *
 * 81    5/21/99 7:32p Nate
 * Added Save and Restore ability to the custom script section
 *
 * 80    5/07/99 10:54a Nate
 * Added fix for fitting more scripts in the script type popup menu
 *
 * 79    5/04/99 6:53p Jeff
 * added event for when a player dies
 *
 * 78    4/27/99 4:27p Jeff
 * added player respawn osiris event
 *
 * 77    4/14/99 6:03p Nate
 * Added Event Type specification to Dallas Script Highlighting system.
 *
 * 76    4/02/99 2:16p Nate
 * Added AI Init event
 *
 * 75    4/01/99 6:02p Nate
 * added clipping of long messages when reading them in
 *
 * 74    3/30/99 4:47p Jeff
 * added level events for when IGC occurs for a player
 *
 * 73    3/17/99 3:57p Nate
 * Added localization support for message files, and added level check to
 * script grouping system
 *
 * 72    3/11/99 10:51a Nate
 * Added deletion of "Untitled" Dallas files when doing a New from editor
 *
 * 71    3/03/99 3:07p Nate
 * Temporarily allow designer to select named players
 *
 * 70    3/03/99 12:05a Nate
 * Added IT to AI goal complete event, added dynamic message file name
 * determination, and made it so you can't select a named player for an
 * object type
 *
 * 69    2/22/99 1:17p Nate
 * Added 'level goal item complete' event
 *
 * 68    2/22/99 1:18a Jeff
 * added handling for evt_use
 *
 * 67    2/20/99 6:07p Nate
 * Added Level Goal events
 *
 * 66    2/19/99 5:35p Nate
 * Added new types and events
 *
 * 65    2/17/99 4:14p Nate
 * Added condition query shortcuts
 *
 * 64    2/17/99 11:36a Nate
 * Fixed mprintf in script checksum code
 *
 * 63    2/17/99 10:57a Nate
 * Added script checksum code for Jeff
 *
 * 62    2/11/99 7:26p Nate
 * Added check to save button to make sure editor is up before doing
 * anything
 *
 * 61    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 60    2/08/99 7:40p Nate
 * Fixed up event names to reflect IT's
 *
 * 59    2/08/99 3:53p Nate
 * Added new event types
 *
 * 58    2/07/99 4:43p Nate
 * Added OWNER selection to Door parameter types
 *
 * 57    2/05/99 11:52a Nate
 * Added importing/exporting of scripts
 *
 * 56    2/03/99 7:20p Nate
 * Fixed clipboard bug and added script chaining option
 *
 * 55    2/03/99 2:19p Nate
 * Added cool drag-n-drop support
 *
 * 54    2/03/99 11:57a Nate
 * Added script highlighting interface
 *
 * 53    2/03/99 10:37a Nate
 * Max popup items per column is now 40 for Luke
 *
 * 52    2/02/99 7:41p Nate
 * Added columnization of popup menus
 *
 * 51    2/02/99 8:43a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 50    2/01/99 4:15p Nate
 * Changed TIMER HANDLE to TIMER ID to match DallasFuncs
 *
 * 49    2/01/99 3:48p Nate
 * Added fix to INVALID_SCRIPT_ID errors
 *
 * 48    2/01/99 2:41p Nate
 * Added title bar display of level and modified indicator
 *
 * 47    1/29/99 4:41p Nate
 * A few minor tweaks and fixes
 *
 * 46    1/28/99 9:41p Nate
 * Added tons of new stuff
 *
 * 45    1/26/99 1:15p Nate
 * Added UserTypes Workshop implementation
 *
 * 44    1/25/99 7:16p Nate
 * Added UserTypes dialog (non-functional)
 *
 * 43    1/25/99 2:38p Nate
 * Added Valid Flag Mask range support.
 *
 * 42    1/24/99 4:49p Nate
 * Added code for Dallas Save Format Version 1, but didn't enable it yet
 *
 * 41    1/23/99 5:52p Nate
 * Added flag support
 *
 * 40    1/21/99 8:56p Nate
 * Added warnings when saving objects
 *
 * 39    1/20/99 3:51p Nate
 * Added Specific Name parameter type 'a'
 *
 * 38    1/19/99 7:37p Nate
 * Added sound selection prompt dialog
 *
 * 37    1/19/99 12:18p Nate
 * Made it so Owner objects can now be "other"
 *
 * 36    1/19/99 10:35a Nate
 * Fixed Other object submenu bug
 *
 * 35    1/18/99 2:29p Nate
 * Added support for default parameters and valid range specification
 *
 * 34    1/17/99 6:29p Nate
 * Layed groundwork for default parameter values and valid parameter
 * ranges
 *
 * 33    1/15/99 7:31p Nate
 * Added some more interface features/fixes
 *
 * 32    1/15/99 2:05p Nate
 * Added collapse/expand all, fixed me and delete problems, made dlg
 * longer
 *
 * 31    1/15/99 10:37a Nate
 * Fixed highest room index bug
 *
 * 30    1/14/99 6:11p Nate
 * Added Trigger Script support and many other things, too numerous to
 * count.
 *
 * 29    1/13/99 7:28p Nate
 * Added message file reading from created script
 *
 * 28    1/13/99 10:50a Nate
 * Fixed up copy/pase, added highlighting of all scripts matching
 * specified owner
 *
 * 27    1/12/99 7:32p Nate
 * Added copy and paste support
 *
 * 26    1/12/99 4:45p Nate
 * Added max exec time support, added more interface features
 *
 * 25    1/11/99 8:42p Nate
 * Added script parameter support
 *
 * 24    1/11/99 6:40p Nate
 * Added ENUM support
 *
 * 23    1/11/99 10:19a Nate
 * Fixed AND/OR insertion bug
 *
 * 22    1/08/99 12:32p Nate
 * Added glue function validation upon loading scripts
 *
 * 21    1/07/99 10:17p Nate
 * Added first round of script loading code...
 *
 * 20    1/06/99 7:09p Nate
 * Added saving of scripts
 *
 * 19    1/06/99 1:13p Nate
 * Added support for IT objects and ELSE clauses
 *
 * 18    1/05/99 8:00p Nate
 * Added conditional code creation... fixed up interface yet a little
 * more.
 *
 * 17    1/05/99 2:03p Nate
 * Fixed up events and conditional interface a little
 *
 * 16    1/04/99 7:34p Nate
 * Added rough interface for Conditions
 *
 * 15    1/02/99 3:22p Matt
 * Added support for SaveRestoreState() (new code emailed to me from Jeff)
 *
 * 14    12/23/98 6:44p Nate
 * Added reading in of queries
 *
 * 13    12/23/98 4:03p Nate
 * Added code to implement as a modeless dialog
 *
 * 12    12/23/98 12:43p Nate
 * Fixed small message file parse bug.
 *
 * 11    12/23/98 12:35p Nate
 * Added use of level name in Dallas script file naming system.
 *
 * 10    12/22/98 3:55p Nate
 * Added object and room assignments
 *
 * 9     12/21/98 8:00p Nate
 * Added creation of shell code, started conditional interface.
 *
 * 8     12/20/98 4:29p Nate
 * Added script grouping code (based upon owner, then event type)
 *
 * 7     12/18/98 3:10p Nate
 * Added more interface features.
 *
 * 6     12/17/98 9:48p Nate
 * Added editing of paramaters
 *
 * 5     12/16/98 8:45p Nate
 * Added loading of Actions
 *
 * 4     12/15/98 7:47p Nate
 * Added inserting and deleting of default script trees.
 *
 * 3     12/13/98 6:08p Nate
 * Implemented the Message List interface
 *
 * 2     12/11/98 6:45p Nate
 * Initial Version
*
* $NoKeywords: $
*/

// DallasMainDlg.cpp : implementation file
//

#include "stdafx.h"

#include <string.h>
#include <ctype.h>
#include <io.h>

#include "pserror.h"
#include "cfile.h"
#include "mem.h"
#include "mono.h"
#include "ddio.h"
#include "manage.h"
#include "object.h"
#include "room.h"
#include "trigger.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "gametexture.h"
#include "gamepath.h"
#include "matcen.h"
#include "levelgoal.h"

#ifdef NEWEDITOR
#include "globals.h"
#include "NewEditor.h"
#else
#include "editor.h"
#include "editorDoc.h"
#include "osiris_predefs.h"
#include "descent.h"
#endif

#include "ScriptCompilerAPI.h"
#include "DallasMainDlg.h"
#include "DallasGenericPromptDlg.h"
#include "DallasVectorPromptDialog.h"
#include "DallasSoundDlg.h"
#include "DallasStrmAudioDlg.h"
#include "DallasTextureDlg.h"
#include "DallasFlagDlg.h"
#include "DallasImportDlg.h"
#include "DallasUserTypesDlg.h"
#include "DallasUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// Macro and function to make writing out text to a file a bit easier
#define O(x) OutToFile x
CFILE *CurrentOutputFile;
int CurrentTabLevel;

// Writes out text to CurrentFile
void OutToFile(char *format, ...) {
  char buffer[1024];

  if (CurrentOutputFile == NULL)
    return;

  va_list marker;
  va_start(marker, format);
  std::vsprintf(buffer, format, marker);
  cf_WriteString(CurrentOutputFile, buffer);
  va_end(marker);
}

#define DALLASFUNCS_FILENAME "dallasfuncs.cpp"

#define NOT_SPECIFIED_MSG "<NOT_SPECIFIED>"

#define LEVEL_ID_NAME "ID_LEVEL_0000"
#define LEVEL_CLASS_NAME "LevelScript_0000"

// Global declaration of event information database
#define UNKNOWN_EVENT_STRING "*Unknown Event*"
#define UNKNOWN_EVENT_CODE_NAME "EVT_UNKNOWN"
#define UNKNOWN_EVENT_DATA_LINE "// No event data line found!"
EventInfoItem event_info[] = {
    {COLLIDE_EVENT_TYPE, "Collided (with IT)", "EVT_COLLIDE", "tOSIRISEVTCOLLIDE *event_data=&data->evt_collide;",
     OBJECT_MASK | HAS_IT_MASK},
    {ACTIVATED_EVENT_TYPE, "Activated (by IT)", "EVT_COLLIDE", "tOSIRISEVTCOLLIDE *event_data=&data->evt_collide;",
     TRIGGER_MASK | HAS_IT_MASK},
    {CREATED_EVENT_TYPE, "Created", "EVT_CREATED", "tOSIRISEVTCREATED *event_data=&data->evt_created;", OBJECT_MASK},
    {DAMAGED_EVENT_TYPE, "Damaged (by IT)", "EVT_DAMAGED", "tOSIRISEVTDAMAGED *event_data=&data->evt_damaged;",
     OBJECT_MASK | HAS_IT_MASK},
    {DESTROYED_EVENT_TYPE, "Destroyed", "EVT_DESTROY", "tOSIRISEVTDESTROY *event_data=&data->evt_destroy;",
     OBJECT_MASK},
    {FRAME_INTERVAL_EVENT_TYPE, "Frame Interval", "EVT_INTERVAL", "tOSIRISEVTINTERVAL *event_data=&data->evt_interval;",
     OBJECT_MASK | LEVEL_MASK},
    {LEVEL_START_EVENT_TYPE, "Level Start", "EVT_LEVELSTART", "tOSIRISEVTLEVELSTART *event_data=&data->evt_levelstart;",
     LEVEL_MASK},
    {LEVEL_END_EVENT_TYPE, "Level End", "EVT_LEVELEND", "tOSIRISEVTLEVELEND *event_data=&data->evt_levelend;",
     LEVEL_MASK},
    {CHANGE_SEGMENT_EVENT_TYPE, "Changed Segment", "EVT_CHANGESEG",
     "tOSIRISEVTCHANGESEG *event_data=&data->evt_changeseg;", OBJECT_MASK},
    {TIMER_EVENT_TYPE, "Timer (TIMER ID) Went Off", "EVT_TIMER", "tOSIRISEVTTIMER *event_data=&data->evt_timer;",
     OBJECT_MASK | LEVEL_MASK | HAS_TIMERID_MASK},
    {AI_INIT_EVENT_TYPE, "AI-Initialized", "EVT_AI_INIT", "tOSIRISEVTAIINIT *event_data=&data->evt_ai_init;",
     OBJECT_MASK},
    {AIN_OBJKILLED_EVENT_TYPE, "AI-Target (IT) Killed", "EVT_AIN_OBJKILLED",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_objkilled;", OBJECT_MASK | HAS_IT_MASK},
    {AIN_SEEPLAYER_EVENT_TYPE, "AI-Saw Target (IT)", "EVT_AIN_SEEPLAYER",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_seeplayer;", OBJECT_MASK | HAS_IT_MASK},
    {AIN_WHITOBJECT_EVENT_TYPE, "AI-Weapon Damaged Target (IT)", "EVT_AIN_WHITOBJECT",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_whitobject;", OBJECT_MASK | HAS_IT_MASK},
    {AIN_GOALCOMPLETE_EVENT_TYPE, "AI-Goal (GOAL ID) Completed (by IT)", "EVT_AIN_GOALCOMPLETE",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_goalcomplete;",
     OBJECT_MASK | LEVEL_MASK | HAS_GOALID_MASK | HAS_IT_MASK},
    {AIN_GOALFAIL_EVENT_TYPE, "AI-Goal (GOAL ID) Failed", "EVT_AIN_GOALFAIL",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_goalfail;", OBJECT_MASK | LEVEL_MASK | HAS_GOALID_MASK},
    {AIN_MELHIT_EVENT_TYPE, "AI-Melee Hit on Target (IT)", "EVT_AIN_MELEE_HIT",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_melee_hit;", OBJECT_MASK | HAS_IT_MASK},
    {AIN_MELATTACKFRAME_EVENT_TYPE, "AI-Melee Attack Frame", "EVT_AIN_MELEE_ATTACK_FRAME",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_melee_attack_frame;", OBJECT_MASK},
    {AIN_MOVIE_STARTED_EVENT_TYPE, "AI-Movie Started", "EVT_AIN_MOVIE_START",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_movie_start;", OBJECT_MASK},
    {AIN_MOVIE_ENDED_EVENT_TYPE, "AI-Movie Ended", "EVT_AIN_MOVIE_END",
     "tOSIRISEVTAINOTIFY *event_data=&data->evt_ain_movie_end;", OBJECT_MASK},
    {CHILD_DIED_EVENT_TYPE, "A Child (IT) Has Died", "EVT_CHILD_DIED",
     "tOSIRISEVTCHILDDIED *event_data=&data->evt_child_died;", OBJECT_MASK | HAS_IT_MASK},
    {DOOR_CLOSED_EVENT_TYPE, "Door Closed", "EVT_DOOR_CLOSE", "tOSIRISEVTDOORCLOSE *event_data=&data->evt_door_close;",
     DOOR_OBJECT_MASK},
    {DOOR_ACTIVATED_EVENT_TYPE, "Door Activated", "EVT_DOOR_ACTIVATE",
     "tOSIRISEVTDOORACTIVATE *event_data=&data->evt_door_activate;", DOOR_OBJECT_MASK},
    {MATCEN_NOTIFY_EVENT_TYPE, "Matcen (MATCEN ID) Has Spawned (an IT)", "EVT_MATCEN_CREATE",
     "tOSIRISEVTMATCENCREATE *event_data=&data->evt_matcen_create;", LEVEL_MASK | HAS_MATCENID_MASK | HAS_IT_MASK},
    {LGOAL_COMPLETED_EVENT_TYPE, "Level Goal (LEVEL GOAL ID) Completed", "EVT_LEVEL_GOAL_COMPLETE",
     "tOSIRISEVTLEVELGOALCOMPLETE *event_data=&data->evt_level_goal_complete;", LEVEL_MASK | HAS_LEVGOALID_MASK},
    {LGOAL_ITEM_COMPLETE_EVENT_TYPE, "Level Goal (LEVEL GOAL ID) Item Completed", "EVT_LEVEL_GOAL_ITEM_COMPLETE",
     "tOSIRISEVTLEVELGOALITEMCOMPLETE *event_data=&data->evt_level_goal_item_complete;",
     LEVEL_MASK | HAS_LEVGOALID_MASK},
    {ALL_LGOALS_COMPLETE_EVENT_TYPE, "All Level Goals Completed", "EVT_ALL_LEVEL_GOALS_COMPLETE",
     "tOSIRISEVTALLLEVELGOALSCOMPLETE *event_data=&data->evt_all_level_goals_complete;", LEVEL_MASK},
    {PLAYER_MOVIE_START_TYPE, "Movie Starts With Player Target", "EVT_PLAYER_MOVIE_START",
     "tOSIRISEVTPLAYERMOVIESTART *event_data=&data->evt_player_movie_start;", LEVEL_MASK},
    {PLAYER_MOVIE_END_TYPE, "Movie Ends With Player Target", "EVT_PLAYER_MOVIE_END",
     "tOSIRISEVTPLAYERMOVIEEND *event_data=&data->evt_player_movie_end;", LEVEL_MASK},
    {USED_EVENT_TYPE, "Used (by IT)", "EVT_USE", "tOSIRISEVTUSE *event_data=&data->evt_use;",
     OBJECT_MASK | HAS_IT_MASK},
    {PLAYER_RESPAWN_TYPE, "Player (IT) respawns", "EVT_PLAYER_RESPAWN",
     "tOSIRISEVTPLAYERRESPAWN *event_data=&data->evt_player_respawn;", LEVEL_MASK | HAS_IT_MASK},
    {PLAYER_DIES_TYPE, "Player (IT) dies", "EVT_PLAYER_DIES",
     "tOSIRISEVTPLAYERDIES *event_data=&data->evt_player_dies;", LEVEL_MASK | HAS_IT_MASK},
    {-1, "", "", "", 0}};

// Global declaration of expression operator information database
#define UNKNOWN_EXPOP_STRING "???"
ExpOpInfoItem expop_info[] = {
    {EQUAL_TO, "=", "Equal To (==)", "==", COMPARISON_OPERATOR_TYPE},
    {NOT_EQUAL_TO, "!=", "Not Equal To (!=)", "!=", COMPARISON_OPERATOR_TYPE},
    {GREATER_THAN, ">", "Greater Than (>)", ">", COMPARISON_OPERATOR_TYPE},
    {LESS_THAN, "<", "Less Than (<)", "<", COMPARISON_OPERATOR_TYPE},
    {GREATER_THAN_OR_EQUAL_TO, ">=", "Greater Than or Equal To (>=)", ">=", COMPARISON_OPERATOR_TYPE},
    {LESS_THAN_OR_EQUAL_TO, "<=", "Less Than or Equal To (<=)", "<=", COMPARISON_OPERATOR_TYPE},
    {IS_TRUE, "is TRUE", "Is TRUE (!=0)", "==true", BINARY_OPERATOR_TYPE},
    {IS_FALSE, "is FALSE", "Is FALSE (==0)", "==false", BINARY_OPERATOR_TYPE},
    {-1, "", "", ""}};

// Global declaration of literal info database
#define UNKNOWN_LITERAL_STRING "UNKNOWN"
ParamMenuItem param_menu_item[] = {{DOOR_PARAMETER_TYPE, "Door"},
                                   {OBJECT_PARAMETER_TYPE, "Object"},
                                   {ROOM_PARAMETER_TYPE, "Room"},
                                   {TRIGGER_PARAMETER_TYPE, "Trigger"},
                                   {INT_PARAMETER_TYPE, "Integer"},
                                   {BOOL_PARAMETER_TYPE, "Bool"},
                                   {FLOAT_PARAMETER_TYPE, "Float"},
                                   {VECTOR_PARAMETER_TYPE, "Vector"},
                                   {STRING_PARAMETER_TYPE, "String"},
                                   {PERCENTAGE_PARAMETER_TYPE, "Percentage"},
                                   {ENUM_PARAMETER_TYPE, "Enumerated Types"},
                                   {SCRIPT_PARAMETER_TYPE, "Script"},
                                   {SOUND_PARAMETER_TYPE, "Sound"},
                                   {SPECNAME_PARAMETER_TYPE, "Specific Name"},
                                   {TEXTURE_PARAMETER_TYPE, "Texture"},
                                   {FLAG_PARAMETER_TYPE, "Flag"},
                                   {PATH_PARAMETER_TYPE, "Path"},
                                   {MATCEN_PARAMETER_TYPE, "Matcen"},
                                   {LEVEL_GOAL_PARAMETER_TYPE, "Level Goal"},
                                   {STRM_AUDIO_PARAMETER_TYPE, "Streaming Audio File"},
                                   {-1, ""}};

#define MAX_MESSAGES 10 // max messages to process during a message deferral

// Processes and waiting messages
void DeferMsgs(void) {
  MSG msg;
  for (int MsgCount = MAX_MESSAGES; MsgCount && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE); MsgCount--) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

bool Compiling = FALSE;
CString CompilerOutputText = "";
CEdit *help_edit_ctrl = NULL;

// Gets compiler output and displays it
#define HELP_EDIT_CTRL_HEIGHT 7
void CompilerCallback(char *text) {
  CompilerOutputText += text;

  if (help_edit_ctrl == NULL)
    return;
  help_edit_ctrl->SetWindowText(CompilerOutputText.GetBuffer(0));

  int total_lines = help_edit_ctrl->GetLineCount();
  int curr_index = help_edit_ctrl->GetFirstVisibleLine();
  if ((total_lines - curr_index) > HELP_EDIT_CTRL_HEIGHT) {
    // we need to scroll down a line
    help_edit_ctrl->LineScroll((total_lines - curr_index) - HELP_EDIT_CTRL_HEIGHT);
  }

  DeferMsgs();
}

/////////////////////////////////////////////////////////////////////////////
// CDallasMainDlg dialog

CDallasMainDlg::CDallasMainDlg(CWnd *pParent /*=NULL*/) : CDialog(CDallasMainDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CDallasMainDlg)
  //}}AFX_DATA_INIT

  InitAll();

  help_edit_ctrl = &m_HelpEdit;

  m_pDragImage = NULL;
  m_bLDragging = FALSE;
  m_hitemDrag = NULL;
  m_hitemDrop = NULL;
}

void CDallasMainDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDallasMainDlg)
  DDX_Control(pDX, IDC_EVENT_COMBO, m_EventList);
  DDX_Control(pDX, IDC_EVENT_TREE, m_ScriptTree);
  DDX_Control(pDX, IDC_HELP_EDIT, m_HelpEdit);
  DDX_Control(pDX, IDC_MESSAGE_LIST, m_MessageList);
  DDX_Control(pDX, IDC_MESSAGE_EDIT, m_MessageEdit);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDallasMainDlg, CDialog)
//{{AFX_MSG_MAP(CDallasMainDlg)
ON_BN_CLICKED(IDC_NEW_MESSAGE_BUTTON, OnNewMessageButton)
ON_BN_CLICKED(IDC_DELETE_MESSAGE_BUTTON, OnDeleteMessageButton)
ON_LBN_SELCHANGE(IDC_MESSAGE_LIST, OnSelchangeMessageList)
ON_EN_CHANGE(IDC_MESSAGE_EDIT, OnChangeMessageEdit)
ON_LBN_DBLCLK(IDC_MESSAGE_LIST, OnDblclkMessageList)
ON_BN_CLICKED(IDC_CHANGE_MESSAGE_NAME_BUTTON, OnChangeMessageNameButton)
ON_WM_CLOSE()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_NEW_EVENT_BUTTON, OnNewScriptButton)
ON_BN_CLICKED(IDC_INSERT_EVENT_BUTTON, OnInsertScriptButton)
ON_BN_CLICKED(IDC_DELETE_EVENT_BUTTON, OnDeleteScriptButton)
ON_NOTIFY(NM_RCLICK, IDC_EVENT_TREE, OnRclickEventTree)
ON_NOTIFY(NM_DBLCLK, IDC_EVENT_TREE, OnDblclkScriptTree)
ON_NOTIFY(TVN_SELCHANGED, IDC_EVENT_TREE, OnSelchangedScriptTree)
ON_BN_CLICKED(IDC_SAVE_BUTTON, OnSaveButton)
ON_NOTIFY(TVN_KEYDOWN, IDC_EVENT_TREE, OnKeydownEventTree)
ON_BN_CLICKED(IDC_COPY_BUTTON, OnCopyButton)
ON_BN_CLICKED(IDC_PASTE_BUTTON, OnPasteButton)
ON_BN_CLICKED(IDC_HIGHLIGHT_BUTTON, OnHighlightButton)
ON_BN_CLICKED(IDC_EXPAND_ALL_BUTTON, OnExpandAllButton)
ON_BN_CLICKED(IDC_COLLAPSE_ALL_BUTTON, OnCollapseAllButton)
ON_BN_CLICKED(IDC_UTYPES_BUTTON, OnUtypesButton)
ON_NOTIFY(TVN_BEGINDRAG, IDC_EVENT_TREE, OnBegindragEventTree)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_BN_CLICKED(IDC_ALLOBJ_RADIO, OnAllobjRadio)
ON_BN_CLICKED(IDC_ALLTRIG_RADIO, OnAlltrigRadio)
ON_BN_CLICKED(IDC_NONE_RADIO, OnNoneRadio)
ON_BN_CLICKED(IDC_SPECIFIC_RADIO, OnSpecificRadio)
ON_BN_CLICKED(IDC_LEVEL_RADIO, OnLevelRadio)
ON_BN_CLICKED(IDC_IMPORT_BUTTON, OnImportButton)
ON_BN_CLICKED(IDC_EXPORT_BUTTON, OnExportButton)
ON_BN_CLICKED(IDC_EVENT_RADIO, OnEventRadio)
ON_CBN_SELCHANGE(IDC_EVENT_COMBO, OnSelchangeEventCombo)
//}}AFX_MSG_MAP
ON_WM_ACTIVATE()
ON_MESSAGE(WM_HIGHLIGHT_SCRIPTS, OnHighlightScripts)
ON_MESSAGE(WM_ADD_SCRIPT, OnAddScript)
ON_MESSAGE(WM_ADD_SCRIPT_AND_HIGHLIGHT, OnAddScriptAndHighlight)
ON_COMMAND_RANGE(ASSIGN_COMMAND_RANGE_START, ASSIGN_COMMAND_RANGE_END, OnMenuSelectionOfTypeAssign)
ON_COMMAND_RANGE(ADD_COMMAND_RANGE_START, ADD_COMMAND_RANGE_END, OnMenuSelectionOfTypeAdd)
ON_COMMAND_RANGE(REPLACE_COMMAND_RANGE_START, REPLACE_COMMAND_RANGE_END, OnMenuSelectionOfTypeReplace)
ON_COMMAND_RANGE(DELETE_COMMAND_RANGE_START, DELETE_COMMAND_RANGE_END, OnMenuSelectionOfTypeDelete)
END_MESSAGE_MAP()

// Sets up the dialog before it is displayed
BOOL CDallasMainDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  // CString msg;
  // msg.Format("Starting ID: %d\nEnding ID: %d",STARTING_COMMAND_ID,DELETE_COMMAND_RANGE_END);
  // MessageBox(msg,"Used ID Range",MB_OK);

  // Setup the tree image list
  CBitmap bm;

  m_TreeImageList.Create(16, 16, 0, 19, 0);

  bm.LoadBitmap(IDB_DALLAS_TREE_ICONS_BITMAP);
  m_TreeImageList.Add(&bm, &bm);
  m_ScriptTree.SetImageList(&m_TreeImageList, TVSIL_NORMAL);

  // Setup the Message List GUI and data
  m_MessageEdit.SetLimitText(MAX_MESSAGE_LEN);

  // Make sure everything is cleared out, then load in everything
  Refresh();
  Compiling = FALSE;

  // m_ScriptOwnerType=LEVEL_TYPE;
  // m_ScriptOwnerHandle=0;
  // PostMessage(WM_ADD_SCRIPT_AND_HIGHLIGHT);

  // Set the highlighting to none
  ClearHighlightRadioButtons();
  ((CButton *)GetDlgItem(IDC_NONE_RADIO))->SetCheck(1);
  OnNoneRadio();
  FillHighlightEventList();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

// Gets called whenever Dallas is activated, allows for validating of script values
void CDallasMainDlg::OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized) {
  CDialog::OnActivate(nState, pWndOther, bMinimized);

#ifndef NEWEDITOR
  // Make sure we're in the editor
  if (GetFunctionMode() != EDITOR_MODE)
    return;
#endif

  if (pWndOther == NULL)
    return;

  CWnd *parent_window;
  parent_window = pWndOther->GetParent();

  // If Dallas has been activated because it's returned from a child popup,
  // then get out of here...
  if (parent_window != NULL) {
    if (this->m_hWnd == parent_window->m_hWnd)
      return;
  }

  // Make sure it's been activated, then scan the tree for bad values
  if (nState == WA_ACTIVE || nState == WA_CLICKACTIVE) {
    ClearNameLists();
    FillNameListsFromTree(TVI_ROOT, FALSE);
  }
}

// Saves all data
void CDallasMainDlg::OnSaveButton() {
  CString temp_str;
  char fullpath[_MAX_PATH];

#ifndef NEWEDITOR
  // Make sure we're in the editor
  if (GetFunctionMode() != EDITOR_MODE)
    return;
#endif

  Compiling = TRUE;

  // Create the script source file
  if (!CreateScriptFile(m_ScriptFilename.GetBuffer(0))) {
    Compiling = FALSE;
    return;
  }
  SetModified(FALSE);

  // Write out the message list
  CreateMsgTableFile(m_ScriptMessagesFilename.GetBuffer(0));

  // Get the full DLL path, and delete the DLL
  ddio_MakePath(fullpath, LocalScriptDir, m_ScriptDLLFilename.GetBuffer(0), NULL);
  ddio_DeleteFile(fullpath);

  // Attempt to compile it and create the dll
  CompilerOutputText = "";
  tCompilerInfo ci;
  ci.callback = CompilerCallback;
  ci.script_type = ST_LEVEL;

  strcpy(ci.source_filename, m_ScriptFilename.GetBuffer(0));
  ScriptCompile(&ci);

  // Check to see if the DLL has been created
  ddio_MakePath(fullpath, LocalScriptDir, m_ScriptDLLFilename.GetBuffer(0), NULL);
  if (_access(fullpath, 0x00) == -1) {
    MessageBox("The compile failed.  See output for error details.", "Compiler Error");
  }

  Compiling = FALSE;
}

// Called when the cancel button is pressed
void CDallasMainDlg::OnCancel() {
  if (Compiling)
    return;

  if (ModifiedPrompt() == IDNO)
    return;

  // Shut it all down
  DestroyWindow();

  // CDialog::OnCancel();
}

// Called just before the window is destroyed
void CDallasMainDlg::OnDestroy() {
  CDialog::OnDestroy();

  // Peform clean-up
  ClearAll();
}

// Destroy this instance
void CDallasMainDlg::PostNcDestroy() {
  help_edit_ctrl = NULL;

  // Set the pointer back to null so rest of app knows Dallas has shut down
#ifdef NEWEDITOR
  CNewEditorApp *theApp = (CNewEditorApp *)AfxGetApp();
  theApp->DallasDone();
#else
  theApp.m_DallasModelessDlgPtr = NULL;
#endif

  // Delete the Dallas instance
  delete this;
}

// Called before the window is closed
void CDallasMainDlg::OnClose() {
  if (Compiling)
    return;
  if (ModifiedPrompt() == IDNO)
    return;

  // Shut it all down
  DestroyWindow();
  // CDialog::OnClose();
}

// HACK to handle the pressing of the ENTER button (DOESN'T WORK RIGHT NOW)
void CDallasMainDlg::OnOK() {
  if (Compiling)
    return;

  HTREEITEM selected_item;

  // Pressing ENTER will now cause an edit popup to appear for selected node
  selected_item = m_ScriptTree.GetSelectedItem();
  if (selected_item == NULL)
    return;
  AssignSpecificValue();
}

// Launches the UserTypes Dialog
void CDallasMainDlg::OnUtypesButton() {
  CDallasUserTypesDlg dlg;

  dlg.DoModal();

  UpdateTreeText(TVI_ROOT);
}

/////////////////////////////////////////////////////////////////////////////
// CDallasMainDlg message handlers
/////////////////////////////////////////////////////////////////////////////

// Adds a new (default) message to the message list
void CDallasMainDlg::OnNewMessageButton() {
  CString new_name;

  // Create the new name
  new_name.Format("%s%d", DEFAULT_MESSAGE_NAME, m_NextMessageID);

  // Make sure the default name isn't already taken
  while (FindMessageInList(new_name.GetBuffer(0)) != NULL) {
    m_NextMessageID++;
    new_name.Format("%s%d", DEFAULT_MESSAGE_NAME, m_NextMessageID);
  }

  // Add it to the list
  AddToMessageList(new_name.GetBuffer(0), DEFAULT_MESSAGE_TEXT);
  m_NextMessageID++;

  // Now let the user change the name if they want to
  OnDblclkMessageList();

  // And then set focus to the message entry box
  m_MessageEdit.SetFocus();

  SetModified(TRUE);
}

// Deletes the currently selected message from the list
void CDallasMainDlg::OnDeleteMessageButton() {
  int index;
  tMessageListEntry *msg_entry;

  index = m_MessageList.GetCurSel();
  if (index == LB_ERR)
    return;

  // Get the entry for this item
  msg_entry = (tMessageListEntry *)m_MessageList.GetItemData(index);

  // Mark this entry as being free
  DeleteMessageListEntry(msg_entry->name);

  // Delete the list box item and update edit boxes
  m_MessageList.DeleteString(index);
  OnSelchangeMessageList();

  SetModified(TRUE);
}

// Callback for when the Message List Box selection changes
void CDallasMainDlg::OnSelchangeMessageList() {
  int index;
  CString name;
  tMessageListEntry *msg_entry;

  index = m_MessageList.GetCurSel();
  if (index == LB_ERR) {
    m_MessageEdit.SetWindowText("");
    return;
  }

  // Get the entry for this item
  msg_entry = (tMessageListEntry *)m_MessageList.GetItemData(index);

  // Set the edit boxes to reflect the appropriate data
  m_MessageEdit.SetWindowText(msg_entry->message);
}

// Allows user to change the name of the string
void CDallasMainDlg::OnDblclkMessageList() {
  CDallasGenericPromptDlg dlg;
  int index;
  tMessageListEntry *msg_entry;
  CString message, old_name;

  index = m_MessageList.GetCurSel();
  if (index == LB_ERR)
    return;

  // Get the entry for this item
  msg_entry = (tMessageListEntry *)m_MessageList.GetItemData(index);

  // Display the prompt dialog
  old_name = msg_entry->name;
  dlg.m_DialogTitle = "Message Name Prompt";
  dlg.m_PromptText = "Enter the new name for this message:";
  dlg.m_PromptData = old_name;
  dlg.m_MaxDataLength = MAX_MESSAGE_NAME_LEN;

  if (dlg.DoModal() == IDCANCEL)
    return;

  // Check if the message name is valid
  char *msgname = dlg.m_PromptData.GetBuffer(0);
  if (strlen(msgname) == 0)
    return;
  for (uint32_t j = 0; j < strlen(msgname); j++)
    if (isspace(msgname[j]) || (!isalnum(msgname[j]) && msgname[j] != '_')) {
      MessageBox("That message ID is invalid!\n\nAn ID may only contain letters and numbers",
                 "Invalid Message ID Error", MB_OK | MB_ICONEXCLAMATION);
      return;
    }

  // Check if the message name already exists in the list
  if (FindMessageInList(msgname) != NULL && strcmp(msgname, old_name.GetBuffer(0)) != 0) {
    MessageBox("That message ID is already in use!\n\nYou must enter a UNIQUE message ID.", "Invalid Message ID Error",
               MB_OK | MB_ICONEXCLAMATION);
    return;
  }

  // Store the message
  message = msg_entry->message;

  // Remove the old name from list box
  OnDeleteMessageButton();

  // Now, add the new name (and old message) back in
  AddToMessageList(dlg.m_PromptData.GetBuffer(0), message.GetBuffer(0));

  // Update any old messageID's in the tree to use the new name
  UpdateStringParams(TVI_ROOT, old_name.GetBuffer(0), dlg.m_PromptData.GetBuffer(0));
  SetModified(TRUE);
}

// Does the same thing as double-clicking a name (allows you to change it)
void CDallasMainDlg::OnChangeMessageNameButton() {
  // TODO: Add your control notification handler code here
  OnDblclkMessageList();
}

// Updates the text for the message being edited
void CDallasMainDlg::OnChangeMessageEdit() {
  // TODO: If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CDialog::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  // TODO: Add your control notification handler code here
  int index;
  CString name, new_message;
  char *message;

  index = m_MessageList.GetCurSel();
  if (index == LB_ERR)
    return;

  m_MessageList.GetText(index, name);

  message = FindMessageInList(name.GetBuffer(0));
  if (message == NULL)
    return;
  m_MessageEdit.GetWindowText(new_message);
  strcpy(message, new_message.GetBuffer(0));
  SetModified(TRUE);
}

// Adds a new default script to the end of the list
void CDallasMainDlg::OnNewScriptButton() {
  HTREEITEM new_node;

  int new_id = GetLowestUnusedScriptID();

  new_node = CreateDefaultScriptTree(new_id);
  if (new_node != NULL) {
    if (new_id == m_NextScriptID)
      m_NextScriptID++;
    m_ScriptTree.SelectItem(new_node);
    AssignSpecificValue();
  }
}

// Inserts a new default script before the currently selected script
void CDallasMainDlg::OnInsertScriptButton() {
  HTREEITEM new_node;

  int new_id = GetLowestUnusedScriptID();

  new_node = CreateDefaultScriptTree(new_id, m_ScriptTree.GetSelectedItem());
  if (new_node != NULL) {
    if (new_id == m_NextScriptID)
      m_NextScriptID++;
    m_ScriptTree.SelectItem(new_node);
    AssignSpecificValue();
  }
}

// Deletes the currently selected script
void CDallasMainDlg::OnDeleteScriptButton() {
  HTREEITEM script_header_node;

  script_header_node = GetParentNodeOfType(m_ScriptTree.GetSelectedItem(), SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  if (DeletePrompt("Are you sure you want to delete this script?") == IDYES) {
    FreeTreeItem(script_header_node);
    SetModified(TRUE);
  }
}

// Do a script copy
void CDallasMainDlg::OnCopyButton() { PerformScriptCopy(); }

// Do a script paste
void CDallasMainDlg::OnPasteButton() { PerformScriptPaste(); }

// Collapses all node from the selected node on down
void CDallasMainDlg::OnExpandAllButton() {
  HTREEITEM selected_node;

  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  ExpandAll(selected_node, TVE_EXPAND);
  m_ScriptTree.EnsureVisible(selected_node);
}

// Collapses all node from the selected node on down
void CDallasMainDlg::OnCollapseAllButton() {
  HTREEITEM selected_node;

  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  ExpandAll(selected_node, TVE_COLLAPSE);
  m_ScriptTree.EnsureVisible(selected_node);
}

// Handles the script highlighting
void CDallasMainDlg::OnHighlightButton() {
  HTREEITEM selected_node, owner_node;

  selected_node = m_ScriptTree.GetSelectedItem();
  owner_node = GetScriptOwnerNode(selected_node);
  if (owner_node == NULL)
    return;

  tTreeNodeData *data = (tTreeNodeData *)m_ScriptTree.GetItemData(owner_node);
  if (data == NULL)
    return;

  m_ScriptOwnerType = data->ID;
  m_ScriptOwnerHandle = data->int_val;

  HighlightAllScripts();

  ClearHighlightRadioButtons();
  ((CButton *)GetDlgItem(IDC_SPECIFIC_RADIO))->SetCheck(1);
}

// Calls up edit dialogs when double clicking on a node
void CDallasMainDlg::OnDblclkScriptTree(NMHDR *pNMHDR, LRESULT *pResult) {
  // TODO: Add your control notification handler code here

  *pResult = 0;
}

// Displays a context sensitive pop-up menu
void CDallasMainDlg::OnRclickEventTree(NMHDR *pNMHDR, LRESULT *pResult) {
  POINT pt;
  TVHITTESTINFO hit_info;

  ::GetCursorPos(&pt);
  m_ScriptTree.ScreenToClient(&pt);
  hit_info.pt = pt;

  // Check to see if the mouse is lined up with a tree item
  m_ScriptTree.HitTest(&hit_info);
  if (hit_info.flags & TVHT_ONITEM || hit_info.flags & TVHT_ONITEMRIGHT || hit_info.flags & TVHT_ONITEMINDENT) {

    // Select the item
    m_ScriptTree.SelectItem(hit_info.hItem);

    // Convert back to screen coordinates for displaying the menu
    m_ScriptTree.ClientToScreen(&pt);

    DisplayFloatingPopupMenu(hit_info.hItem, pt);
  }

  *pResult = 0;
}

// Displays a context sensitive pop-up menu for the given node at the given screen pt
void CDallasMainDlg::DisplayFloatingPopupMenu(HTREEITEM node, POINT &pt) {
  int valid_return_type;
  CString valid_return_name;
  tTreeNodeData *data;

  if (node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return;

  // Call the appropriate Menu Creation function
  switch (data->type) {
  case SCRIPT_HEADER_NODE:
    DisplayScriptHeaderNodeMenu(&pt);
    break;
  case SCRIPT_OWNER_NODE:
    DisplayScriptOwnerNodeMenu(&pt);
    break;
  case SCRIPT_EVENT_NODE:
    DisplayScriptEventNodeMenu(&pt, GetScriptOwnerType(node), ScriptHasADoorMe(node));
    break;
  case CONDITIONAL_HEADER_NODE:
    break;
  case ACTIONS_HEADER_NODE:
    DisplayActionHeaderNodeMenu(&pt, data->ID, data->subID, CanAppendElseToNode(node));
    break;
  case CONDITIONAL_STATEMENT_NODE:
    DisplayConditionalStatementNodeMenu(&pt);
    break;
  case EXPRESSION_NODE:
    valid_return_type = GetValidParamType(node, valid_return_name);
    DisplayExpressionNodeMenu(&pt, valid_return_type, valid_return_name.GetBuffer(0));
    break;
  case EXPRESSION_OPERATOR_NODE:
    DisplayExpressionOperatorNodeMenu(&pt, data->ID);
    break;
  case ACTION_STATEMENT_NODE:
    DisplayActionStatementNodeMenu(&pt);
    break;
  case LOGICAL_OPERATOR_NODE:
    DisplayLogicalOperatorNodeMenu(&pt);
    break;
  case PARAMETER_NODE:
    valid_return_type = GetValidParamType(node, valid_return_name);
    DisplayParameterNodeMenu(&pt, data->ID, data->name, valid_return_type, valid_return_name.GetBuffer(0),
                             ScriptHasAnIt(node), ScriptHasAMe(node), ScriptHasADoorMe(node), ScriptHasAGoalID(node),
                             ScriptHasATimerID(node), ScriptHasAMatcenID(node), ScriptHasALevelGoalID(node));
    break;
  case PARAMETER_OPERATOR_NODE:
    break;
  case UNKNOWN_NODE:
    break;
  default:
    break;
  }
}

// Displays appropriate help for the newly selected item
void CDallasMainDlg::OnSelchangedScriptTree(NMHDR *pNMHDR, LRESULT *pResult) {
  NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;

  // TODO: Add your control notification handler code here
  HTREEITEM selected_item;
  tTreeNodeData *data;

  selected_item = m_ScriptTree.GetSelectedItem();
  if (selected_item == NULL)
    return;

  data = GetNearestFunctionNode(selected_item);
  if (data != NULL) {
    // If it's an action node, display the help
    if (data->type == ACTION_STATEMENT_NODE) {
      char *help = GetActionHelp(data->ID);
      if (help != NULL)
        m_HelpEdit.SetWindowText(help);
    }

    // If it's a query node, display the help
    if (data->type == EXPRESSION_NODE) {
      char *help = GetQueryHelp(data->ID);
      if (help != NULL)
        m_HelpEdit.SetWindowText(help);
    }
  }

  *pResult = 0;
}

// Allow keyboard input for the tree control
void CDallasMainDlg::OnKeydownEventTree(NMHDR *pNMHDR, LRESULT *pResult) {
  TV_KEYDOWN *pTVKeyDown = (TV_KEYDOWN *)pNMHDR;
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(pTVKeyDown->hdr.idFrom);
  HTREEITEM hSelectedItem = tree->GetSelectedItem();

  switch (pTVKeyDown->wVKey) {
  case VK_INSERT:
    break;

  case VK_DELETE:
    break;

  case VK_SPACE:
    tree->Expand(hSelectedItem, TVE_TOGGLE);
    break;
  }

  *pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// External DALLAS messaging system
/////////////////////////////////////////////////////////////////////////////

LRESULT CDallasMainDlg::OnHighlightScripts(WPARAM, LPARAM) {
  HighlightAllScripts();

  ClearHighlightRadioButtons();
  ((CButton *)GetDlgItem(IDC_SPECIFIC_RADIO))->SetCheck(1);

  return 0;
}

LRESULT CDallasMainDlg::OnAddScript(WPARAM, LPARAM) {
  HTREEITEM new_node;

  int new_id = GetLowestUnusedScriptID();

  new_node = CreateDefaultScriptTree(new_id);
  if (new_node != NULL) {
    if (new_id == m_NextScriptID)
      m_NextScriptID++;
    m_ScriptTree.SelectItem(new_node);

    // Assign given data to owner
    HTREEITEM owner_node = GetScriptOwnerNode(new_node);
    if (owner_node != NULL) {
      tTreeNodeData *data = (tTreeNodeData *)m_ScriptTree.GetItemData(owner_node);
      if (data != NULL) {
        data->ID = m_ScriptOwnerType;
        data->int_val = m_ScriptOwnerHandle;
        if (data->ID == OBJECT_TYPE) {
          object *objp = ObjGet(data->int_val);
          if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
            data->int_val = OBJECT_HANDLE_NONE;
            strcpy(data->str_val, "");
          } else {
            strcpy(data->str_val, objp->name);
          }
        } else if (data->ID == TRIGGER_TYPE) {
          if (data->int_val < 0 || data->int_val >= Num_triggers) {
            data->int_val = NOT_SPECIFIED_TYPE;
            strcpy(data->str_val, "");
          } else {
            strcpy(data->str_val, Triggers[data->int_val].name);
          }
        } else {
          strcpy(data->str_val, "");
        }
        UpdateNodeText(owner_node);
      }
    }
    // Prompt the user for the name of this script
    AssignSpecificValue();
  }
  return 0;
}

LRESULT CDallasMainDlg::OnAddScriptAndHighlight(WPARAM, LPARAM) {
  HTREEITEM new_node;

  int new_id = GetLowestUnusedScriptID();

  new_node = CreateDefaultScriptTree(new_id);
  if (new_node != NULL) {
    if (new_id == m_NextScriptID)
      m_NextScriptID++;
    m_ScriptTree.SelectItem(new_node);

    // Assign given data to owner
    HTREEITEM owner_node = GetScriptOwnerNode(new_node);
    if (owner_node != NULL) {
      tTreeNodeData *data = (tTreeNodeData *)m_ScriptTree.GetItemData(owner_node);
      if (data != NULL) {
        data->ID = m_ScriptOwnerType;
        data->int_val = m_ScriptOwnerHandle;
        if (data->ID == OBJECT_TYPE) {
          object *objp = ObjGet(data->int_val);
          if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
            data->int_val = OBJECT_HANDLE_NONE;
            strcpy(data->str_val, "");
          } else {
            strcpy(data->str_val, objp->name);
          }
        } else if (data->ID == TRIGGER_TYPE) {
          if (data->int_val < 0 || data->int_val >= Num_triggers) {
            data->int_val = NOT_SPECIFIED_TYPE;
            strcpy(data->str_val, "");
          } else {
            strcpy(data->str_val, Triggers[data->int_val].name);
          }
        } else {
          strcpy(data->str_val, "");
        }
        UpdateNodeText(owner_node);
      }
    }

    // Highlight all the scripts
    HighlightAllScripts();

    ClearHighlightRadioButtons();
    ((CButton *)GetDlgItem(IDC_SPECIFIC_RADIO))->SetCheck(1);

    // Prompt the user for the name of this script
    AssignSpecificValue();
  }
  return 0;
}

// Displays the "are you sure?" dialog
int CDallasMainDlg::ModifiedPrompt(void) {
  // If current file has been modified, check with user first...
  if (!m_Modified)
    return (IDYES);
  if (MessageBox("Your changes will be lost. Proceed?", "Script Has Been Modified", MB_YESNO) == IDYES)
    return (IDYES);
  return (IDNO);
}

// Sets the modified flag
void CDallasMainDlg::SetModified(bool value) {
  m_Modified = value;
  SetTitleBar();
}

#define DALLAS_TITLE_STRING "Dallas Graphical Script Editor v1.0"

// Updates the Dallas title bar
void CDallasMainDlg::SetTitleBar(void) {
  CString title;

  // Get the current level name
  char filename[_MAX_PATH + 1];

  if (m_ScriptFilename.IsEmpty())
    strcpy(filename, "Untitled");
  else
    ddio_SplitPath(m_ScriptFilename.GetBuffer(0), NULL, filename, NULL);

  title.Format("%s - %s%s", DALLAS_TITLE_STRING, filename, (m_Modified) ? "*" : "");
  SetWindowText(title.GetBuffer(0));
}

/////////////////////////////////////////////////////////////////////////////
// Floating Popup Menu Callbacks
/////////////////////////////////////////////////////////////////////////////

// Translates the type of Assign being requested
void CDallasMainDlg::OnMenuSelectionOfTypeAssign(UINT nID) {
  // Check for the assigning of a message name
  if (nID >= ASSIGN_SCRIPT_ID_RANGE_START && nID < ASSIGN_SCRIPT_ID_RANGE_END)
    AssignScriptID(nID - ASSIGN_SCRIPT_ID_RANGE_START);

  // Check for the assigning of an execution time
  if (nID >= ASSIGN_EXEC_TIME_ID_RANGE_START && nID < ASSIGN_EXEC_TIME_ID_RANGE_END)
    AssignExecTime(nID - ASSIGN_EXEC_TIME_ID_RANGE_START);

  // Check for the assigning of a chain option
  if (nID >= ASSIGN_CHAIN_ID_RANGE_START && nID < ASSIGN_CHAIN_ID_RANGE_END)
    AssignChainOption(nID - ASSIGN_CHAIN_ID_RANGE_START);

  // Check for the entering of a specific value (i.e. popup dialog)
  if (nID == ASSIGN_SPECIFIC_VALUE_ID)
    AssignSpecificValue();

  // Check for the entering of a specific value (i.e. popup dialog)
  if (nID == ASSIGN_TRUE_ID)
    AssignBooleanValue(TRUE);
  if (nID == ASSIGN_FALSE_ID)
    AssignBooleanValue(FALSE);

  // Check for the assigning of a message name
  if (nID >= ASSIGN_MESSAGE_ID_RANGE_START && nID < ASSIGN_MESSAGE_ID_RANGE_END)
    AssignMessageName(nID - ASSIGN_MESSAGE_ID_RANGE_START);

  // Check for the assigning of an event type
  if (nID >= ASSIGN_EVENT_ID_RANGE_START && nID < ASSIGN_EVENT_ID_RANGE_END)
    AssignEventType(nID - ASSIGN_EVENT_ID_RANGE_START);

  // Check for the assigning of a level owner
  if (nID == ASSIGN_LEVEL_ID)
    AssignNamedValue(LEVEL_TYPE, 0x000);

  // Check for the assigning of a trigger owner
  if (nID >= ASSIGN_TRIGGER_ID_RANGE_START && nID < ASSIGN_TRIGGER_ID_RANGE_END)
    AssignNamedValue(TRIGGER_TYPE, nID - ASSIGN_TRIGGER_ID_RANGE_START);

  // Check for the assigning of object none
  if (nID == ASSIGN_OBJECT_NONE_ID)
    AssignNamedValue(OBJECT_TYPE, OBJECT_NONE_HANDLE);

  // Check for the assigning of object IT
  if (nID == ASSIGN_OBJECT_IT_ID)
    AssignNamedValue(OBJECT_TYPE, OBJECT_IT_HANDLE);

  // Check for the assigning of object ME
  if (nID == ASSIGN_OBJECT_ME_ID)
    AssignNamedValue(OBJECT_TYPE, OBJECT_ME_HANDLE);

  // Check for the assigning of a named object
  if (nID >= ASSIGN_OBJECT_ID_RANGE_START && nID < ASSIGN_OBJECT_ID_RANGE_END)
    AssignNamedValue(OBJECT_TYPE, nID - ASSIGN_OBJECT_ID_RANGE_START);

  // Check for the assigning of a named room
  if (nID >= ASSIGN_ROOM_ID_RANGE_START && nID < ASSIGN_ROOM_ID_RANGE_END)
    AssignNamedValue(ROOM_TYPE, nID - ASSIGN_ROOM_ID_RANGE_START);

  // Check for the assigning of an expression operator
  if (nID >= ASSIGN_EXPOP_ID_RANGE_START && nID < ASSIGN_EXPOP_ID_RANGE_END)
    AssignExpOpType(nID - ASSIGN_EXPOP_ID_RANGE_START);

  // Check for the assigning of enum GoalID
  if (nID == ASSIGN_ENUM_GOAL_ID)
    AssignEnumValueType(ENUM_GOALID_VALUE);

  // Check for the assigning of enum TimerID
  if (nID == ASSIGN_ENUM_TIMER_ID)
    AssignEnumValueType(ENUM_TIMERID_VALUE);

  // Check for the assigning of enum MatcenID
  if (nID == ASSIGN_ENUM_MATCEN_ID)
    AssignEnumValueType(ENUM_MATCENID_VALUE);

  // Check for the assigning of an enum value
  if (nID >= ASSIGN_ENUM_VALUE_ID_RANGE_START && nID < ASSIGN_ENUM_VALUE_ID_RANGE_END)
    AssignEnumValueType(nID - ASSIGN_ENUM_VALUE_ID_RANGE_START);

  // Check for the assigning of a path
  if (nID >= ASSIGN_PATH_ID_RANGE_START && nID < ASSIGN_PATH_ID_RANGE_END)
    AssignNamedValue(PATH_TYPE, nID - ASSIGN_PATH_ID_RANGE_START);

  // Check for the assigning of a matcen
  if (nID == ASSIGN_MATCEN_EVENT_ID)
    AssignNamedValue(MATCEN_TYPE, MATCEN_ID_VALUE);

  // Check for the assigning of a matcen
  if (nID >= ASSIGN_MATCEN_ID_RANGE_START && nID < ASSIGN_MATCEN_ID_RANGE_END)
    AssignNamedValue(MATCEN_TYPE, nID - ASSIGN_MATCEN_ID_RANGE_START);

  // Check for the assigning of a level goal
  if (nID == ASSIGN_LEVEL_GOAL_ID)
    AssignNamedValue(LEVEL_GOAL_TYPE, LEVEL_GOAL_ID_VALUE);

  // Check for the assigning of a level goal
  if (nID >= ASSIGN_LEVEL_GOAL_ID_RANGE_START && nID < ASSIGN_LEVEL_GOAL_ID_RANGE_END)
    AssignNamedValue(LEVEL_GOAL_TYPE, nID - ASSIGN_LEVEL_GOAL_ID_RANGE_START);
}

// Translates the type of Add being requested
void CDallasMainDlg::OnMenuSelectionOfTypeAdd(UINT nID) {
  // Check for adding of a nested IF-THEN clause
  if (nID == ADD_IF_THEN_CLAUSE_ID)
    AddNestedIfThenClause();

  // Check for adding of a nested ELSE clause
  if (nID == ADD_ELSE_CLAUSE_ID)
    AddNestedElseClause();

  // Check for adding of a nested IF-THEN-ELSE clause
  if (nID == ADD_IF_THEN_ELSE_CLAUSE_ID)
    AddNestedIfThenElseClause();

  // Check for the adding of a DO_NOTHING Action
  if (nID == ADD_DO_NOTHING_ACTION_ID)
    AddActionStatementNode(DO_NOTHING_ID);

  // Check for the adding of a specific Action
  if (nID >= ADD_ACTION_ID_RANGE_START && nID < ADD_ACTION_ID_RANGE_END)
    AddActionStatementNode(nID - ADD_ACTION_ID_RANGE_START);

  // Check for the adding of a logical operator
  if (nID >= ADD_LOGOP_ID_RANGE_START && nID < ADD_LOGOP_ID_RANGE_END)
    AddLogicalOperatorNode(nID - ADD_LOGOP_ID_RANGE_START);

  // Check for the adding of a logical operator
  if (nID >= INSERT_LOGOP_ID_RANGE_START && nID < INSERT_LOGOP_ID_RANGE_END)
    InsertLogicalOperatorNode(nID - INSERT_LOGOP_ID_RANGE_START);

  // Check for the adding of a condition
  if (nID >= ADD_CONDITION_ID_RANGE_START && nID < ADD_CONDITION_ID_RANGE_END)
    AddConditionalStatementNode(nID - ADD_CONDITION_ID_RANGE_START);

  // Check for the adding of a binary condition (query)
  if (nID >= ADD_COND_QBIN_ID_RANGE_START && nID < ADD_COND_QBIN_ID_RANGE_END)
    AddConditionalStatementNode(BINARY_STATEMENT, nID - ADD_COND_QBIN_ID_RANGE_START);

  // Check for the adding of a comparison condition (query)
  if (nID >= ADD_COND_QCOMP_ID_RANGE_START && nID < ADD_COND_QCOMP_ID_RANGE_END)
    AddConditionalStatementNode(COMPARISON_STATEMENT, nID - ADD_COND_QCOMP_ID_RANGE_START);
}

// Handle replace commands
void CDallasMainDlg::OnMenuSelectionOfTypeReplace(UINT nID) {
  // Check for the replacement of a node with a specific Query
  if (nID >= REPLACE_QUERY_ID_RANGE_START && nID < REPLACE_QUERY_ID_RANGE_END)
    ReplaceWithQueryNode(nID - REPLACE_QUERY_ID_RANGE_START);

  // Check for the replacement of a node with a Literal
  if (nID >= REPLACE_LITERAL_ID_RANGE_START && nID < REPLACE_LITERAL_ID_RANGE_END)
    ReplaceWithLiteralNode(nID - REPLACE_LITERAL_ID_RANGE_START, 0);

  // Check for the replacement of a node with a Literal enumeration
  if (nID >= REPLACE_LIT_ENUM_ID_RANGE_START && nID < REPLACE_LIT_ENUM_ID_RANGE_END)
    ReplaceWithLiteralNode(ENUM_PARAMETER_TYPE, nID - REPLACE_LIT_ENUM_ID_RANGE_START);

  // Check for the replacement of a node with a Literal flag
  if (nID >= REPLACE_LIT_FLAG_ID_RANGE_START && nID < REPLACE_LIT_FLAG_ID_RANGE_END)
    ReplaceWithLiteralNode(FLAG_PARAMETER_TYPE, nID - REPLACE_LIT_FLAG_ID_RANGE_START);

  // Check for the replacement of a node with a DO_NOTHING Action
  if (nID == REPLACE_DO_NOTHING_ACTION_ID)
    ReplaceWithActionNode(DO_NOTHING_ID);

  // Check for the replacement of a node with an action
  if (nID >= REPLACE_ACTION_ID_RANGE_START && nID < REPLACE_ACTION_ID_RANGE_END)
    ReplaceWithActionNode(nID - REPLACE_ACTION_ID_RANGE_START);

  // Check for the replacement of a node with a logical operator
  if (nID >= REPLACE_LOGOP_ID_RANGE_START && nID < REPLACE_LOGOP_ID_RANGE_END)
    ReplaceWithLogOpNode(nID - REPLACE_LOGOP_ID_RANGE_START);

  // Check for the replacement of a node with a condition
  if (nID >= REPLACE_CONDITION_ID_RANGE_START && nID < REPLACE_CONDITION_ID_RANGE_END)
    ReplaceWithConditionNode(nID - REPLACE_CONDITION_ID_RANGE_START);

  // Check for the replacement of a node with a binary condition (query)
  if (nID >= REPLACE_COND_QBIN_ID_RANGE_START && nID < REPLACE_COND_QBIN_ID_RANGE_END)
    ReplaceWithConditionNode(BINARY_STATEMENT, nID - REPLACE_COND_QBIN_ID_RANGE_START);

  // Check for the replacement of a node with a comparison condition (query)
  if (nID >= REPLACE_COND_QCOMP_ID_RANGE_START && nID < REPLACE_COND_QCOMP_ID_RANGE_END)
    ReplaceWithConditionNode(COMPARISON_STATEMENT, nID - REPLACE_COND_QCOMP_ID_RANGE_START);
}

// Handle delete commands
void CDallasMainDlg::OnMenuSelectionOfTypeDelete(UINT nID) {
  HTREEITEM selected_node, parent_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Save the parent of this node
  parent_node = m_ScriptTree.GetParentItem(selected_node);

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Handle Delete all's
  if (nID == DELETE_ALL_ID) {
    switch (data->type) {
    case ACTION_STATEMENT_NODE:
      FreeTreeItem(selected_node);
      ConfirmAfterDelete(parent_node);
      SetModified(TRUE);
      break;
    case CONDITIONAL_STATEMENT_NODE:
      FreeTreeItem(selected_node);
      ConfirmAfterDelete(parent_node);
      SetModified(TRUE);
      break;
    case LOGICAL_OPERATOR_NODE:
      FreeTreeItem(selected_node);
      ConfirmAfterDelete(parent_node);
      SetModified(TRUE);
      break;
    case ACTIONS_HEADER_NODE:
      if (data->ID == NESTED) {
        if (data->subID == THEN_CLAUSE) {
          HTREEITEM temp_node;

          // Delete the IF clause
          temp_node = m_ScriptTree.GetPrevSiblingItem(selected_node);
          if (GetNodeType(temp_node) == CONDITIONAL_HEADER_NODE)
            FreeTreeItem(temp_node);

          // Delete the ELSE clause (if it exists)
          temp_node = m_ScriptTree.GetNextSiblingItem(selected_node);
          if (GetNodeType(temp_node) == ACTIONS_HEADER_NODE)
            FreeTreeItem(temp_node);

          // Delete the THEN clause
          FreeTreeItem(selected_node);
        } else { // Delete just the ELSE clause
          FreeTreeItem(selected_node);
        }
        ConfirmAfterDelete(parent_node);
        SetModified(TRUE);
      }
      break;
    }
    return;
  }

  // Handle Delete children only's
  if (nID == DELETE_CHILDREN_ONLY_ID) {
    switch (data->type) {
    case ACTIONS_HEADER_NODE:
      if (DeletePrompt("Are you sure you want to delete all children of this Clause?") == IDYES) {
        FreeTreeItemChildren(selected_node);
        ConfirmAfterDelete(selected_node);
        SetModified(TRUE);
      }
      break;
    }
    return;
  }
}

// Displays a deletion prompt
int CDallasMainDlg::DeletePrompt(char *msg) {
  CString title = "Deletion Prompt";
  return (MessageBox(msg, title.GetBuffer(0), MB_YESNO | MB_ICONQUESTION));
}

// Makes sure everything is as it should be after a delete
void CDallasMainDlg::ConfirmAfterDelete(HTREEITEM parent) {
  tTreeNodeData *data;
  HTREEITEM new_node;

  if (parent == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(parent);
  if (data == NULL)
    return;

  // Make sure IF statement has one child!
  if (data->type == CONDITIONAL_HEADER_NODE) {
    if (GetChildCount(parent) != 1) {
      FreeTreeItemChildren(parent);
      new_node = CreateDefaultConditionalStatementNode(parent);
      if (new_node != NULL)
        m_ScriptTree.SelectItem(new_node);
    }
    return;
  }

  // Make sure THEN statement has at least one child
  if (data->type == ACTIONS_HEADER_NODE) {
    if (GetChildCount(parent) == 0) {
      new_node = CreateDefaultActionStatementNode(parent);
      if (new_node != NULL)
        m_ScriptTree.SelectItem(new_node);
    }
    return;
  }

  // Make sure Logical operators have right number of children
  if (data->type == LOGICAL_OPERATOR_NODE) {
    if (data->ID == AND_TYPE || data->ID == OR_TYPE) {
      if (GetChildCount(parent) < 2) {
        new_node = CreateDefaultConditionalStatementNode(parent);
        if (new_node != NULL)
          m_ScriptTree.SelectItem(new_node);
      }
    }
    return;
  }
}

/////////////////////////////////////////////////////////////////////////////
// General Refresh functions
/////////////////////////////////////////////////////////////////////////////

// Performs all basic initialization tasks
void CDallasMainDlg::InitAll(void) {
  m_Modified = FALSE;

  InitTree();
  InitMessageList();
  InitEnumDatabase();
  InitFlagDatabase();
  InitFunctionDatabases();
  InitScriptGroupingList();
  InitObjectHandleList();
  InitCustomScriptStorage();
  InitNameLists();

  CurrentOutputFile = NULL;
  CurrentTabLevel = 0;

  m_ScriptOwnerType = NONE_TYPE;
  m_ScriptOwnerHandle = 0;
}

// Frees up all DALLAS memory
void CDallasMainDlg::ClearAll(void) {
  ClearMessageList();
  ClearEnumDatabase();
  ClearFlagDatabase();
  ClearFunctionDatabases();
  ClearTree();
  ClearScriptGroupingList();
  ClearObjectHandleList();
  ClearCustomScriptStorage();
  ClearNameLists();
}

// Loads in everything
void CDallasMainDlg::LoadAll(void) {
  // Parse the message file (string table) for this level
  ParseMsgTableFile(m_ScriptMessagesFilename.GetBuffer(0));

  // Parse actions into the Action Database
  ParseFunctionFile(m_DallasFunctionsFilename.GetBuffer(0));
  ParseFunctionFile(m_ScriptFilename.GetBuffer(0), FALSE);

  // Read in the saved script tree
  ParseSourceScript(m_ScriptFilename.GetBuffer(0));

  // Read in the custom script text
  ParseCustomScriptFile(m_ScriptFilename.GetBuffer(0), FALSE);
}

// Sets all the filenames to match the currently loaded level
void CDallasMainDlg::SetAllFilenames(void) {
  // Set the Dallas Functions Filename
  m_DallasFunctionsFilename = DALLASFUNCS_FILENAME;

  // Get the current level name
  char filename[_MAX_PATH + 1];

  CString level_fname;
#ifdef NEWEDITOR
  level_fname = Level_name;
#else
  level_fname = theApp.main_doc->GetPathName();
#endif

  if (level_fname.IsEmpty())
    strcpy(filename, "Untitled");
  else
    ddio_SplitPath(level_fname.GetBuffer(0), NULL, filename, NULL);

  // Create the script source filename
  m_ScriptFilename.Format("%s.cpp", filename);

  // Create the script DLL filename
  m_ScriptDLLFilename.Format("%s.dll", filename);

  // Create the message table filename
  m_ScriptMessagesFilename.Format("%s.msg", filename);
}

// Sets all the filenames to match the given level name
void CDallasMainDlg::SetAllFilenamesToThis(char *level_path) {
  if (level_path == NULL)
    return;

  // Set the Dallas Functions Filename
  m_DallasFunctionsFilename = DALLASFUNCS_FILENAME;

  // Get the current level name
  char filename[_MAX_PATH + 1];

  CString level_fname;
  level_fname = level_path;

  if (level_fname.IsEmpty())
    strcpy(filename, "Untitled");
  else
    ddio_SplitPath(level_fname.GetBuffer(0), NULL, filename, NULL);

  // Create the script source filename
  m_ScriptFilename.Format("%s.cpp", filename);

  // Create the script DLL filename
  m_ScriptDLLFilename.Format("%s.dll", filename);

  // Create the message table filename
  m_ScriptMessagesFilename.Format("%s.msg", filename);

  // Reflect changes in the title bar
  SetTitleBar();
}

// Does a complete refresh of DALLAS
void CDallasMainDlg::Refresh(void) {
  // Make sure everything is cleared out
  ClearAll();

  // Set all the filenames to match the currently loaded level
  SetAllFilenames();

  // Load in everything
  LoadAll();

  // Highlight the appropriate scripts
  HighlightAllScripts();

  SetModified(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// Manage System functions
/////////////////////////////////////////////////////////////////////////////

void CDallasMainDlg::CheckinScriptFiles(void) {}

void CDallasMainDlg::CheckoutScriptFiles(void) {}

void CDallasMainDlg::DeleteScriptFiles(void) {}

/////////////////////////////////////////////////////////////////////////////
// Tree Control Functions
/////////////////////////////////////////////////////////////////////////////

// Performs any necessary initialization of the tree control (and node data)
void CDallasMainDlg::InitTree(void) {
  m_NextScriptID = 0;
  m_ClipboardNode = NULL;
}

// Performs any necessary de-initialization of the tree control (and node data)
void CDallasMainDlg::ClearTree(void) {
  FreeTreeItemChildren(TVI_ROOT);
  m_NextScriptID = 0;
  m_ClipboardNode = NULL;
}

// Obtains the string name for an event type
char *CDallasMainDlg::GetEventTypeString(int type) {
  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == type)
      return (event_info[j].name);

  return (UNKNOWN_EVENT_STRING);
}

// Updates the text for every node in the tree
void CDallasMainDlg::UpdateTreeText(HTREEITEM parent) {
  HTREEITEM child;

  if (parent == NULL)
    return;

  // Process the children
  child = m_ScriptTree.GetChildItem(parent);
  while (child != NULL) {
    UpdateTreeText(child);
    UpdateNodeText(child);

    // Get the next child
    child = m_ScriptTree.GetNextSiblingItem(child);
  }
}

// Obtains the in-code DEFINE name for an event type
char *CDallasMainDlg::GetEventCodeName(int type) {
  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == type)
      return (event_info[j].code_name);

  return (UNKNOWN_EVENT_CODE_NAME);
}

// Obtains the data line for an event type
char *CDallasMainDlg::GetEventDataLine(int type) {
  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == type)
      return (event_info[j].data_line);

  return (UNKNOWN_EVENT_DATA_LINE);
}

// Obtains the string name for a logical operator type
void CDallasMainDlg::GetLogicalOperatorTypeString(int type, CString &string) {
  switch (type) {
  case AND_TYPE:
    string = "AND";
    break;
  case OR_TYPE:
    string = "OR";
    break;
  default:
    string = "Unknown";
    break;
  }
}

// Checks to see if the given script has an IT (based upon the event type)
bool CDallasMainDlg::ScriptHasAnIt(HTREEITEM script_node) {
  // Check the owner type (only triggers and objects can have an it)
  // int owner_type=GetScriptOwnerType(script_node);
  // if(owner_type!=OBJECT_TYPE && owner_type!=TRIGGER_TYPE)
  //	return FALSE;

  // Check the script's event type
  int event_type = GetScriptEventType(script_node);

  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == event_type) {
      if (event_info[j].flags & HAS_IT_MASK)
        return TRUE;
      else
        return FALSE;
    }

  return FALSE;
}

// Checks to see if the given script has an ME (based upon the event type)
bool CDallasMainDlg::ScriptHasAMe(HTREEITEM script_node) {
  // Check the owner type (only an object owner can have a me)
  int owner_type = GetScriptOwnerType(script_node);
  if (owner_type != OBJECT_TYPE)
    return FALSE;

  return TRUE;
}

// Checks to see if the given script has a ME of type DOOR (based upon the event type)
bool CDallasMainDlg::ScriptHasADoorMe(HTREEITEM script_node) {
  HTREEITEM owner_node;
  tTreeNodeData *data;

  owner_node = GetScriptOwnerNode(script_node);
  if (owner_node == NULL)
    return (FALSE);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(owner_node);
  if (data == NULL)
    return (FALSE);

  // Check the owner type (only an object owner can have a me)
  if (data->ID != OBJECT_TYPE)
    return FALSE;

  // Make sure it's a Door object
  object *objp = ObjGet(data->int_val);
  if (objp == NULL || objp->type != OBJ_DOOR || objp->name == NULL)
    return FALSE;

  return TRUE;
}

// Checks to see if the given script has an GoalID (based upon the event type)
bool CDallasMainDlg::ScriptHasAGoalID(HTREEITEM script_node) {
  // Check the owner type (only levels and objects can have a GoalID)
  int owner_type = GetScriptOwnerType(script_node);
  if (owner_type != OBJECT_TYPE && owner_type != LEVEL_TYPE)
    return FALSE;

  // Check the script's event type
  int event_type = GetScriptEventType(script_node);

  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == event_type) {
      if (event_info[j].flags & HAS_GOALID_MASK)
        return TRUE;
      else
        return FALSE;
    }

  return FALSE;
}

// Checks to see if the given script has a Timer ID (based upon the event type)
bool CDallasMainDlg::ScriptHasATimerID(HTREEITEM script_node) {
  // Check the owner type (only levels and objects can have a MatcenID)
  int owner_type = GetScriptOwnerType(script_node);
  if (owner_type != OBJECT_TYPE && owner_type != LEVEL_TYPE)
    return FALSE;

  // Check the script's event type
  int event_type = GetScriptEventType(script_node);

  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == event_type) {
      if (event_info[j].flags & HAS_TIMERID_MASK)
        return TRUE;
      else
        return FALSE;
    }

  return FALSE;
}

// Checks to see if the given script has a Matcen ID (based upon the event type)
bool CDallasMainDlg::ScriptHasAMatcenID(HTREEITEM script_node) {
  // Check the owner type (only levels and objects can have a MatcenID)
  int owner_type = GetScriptOwnerType(script_node);
  if (owner_type != OBJECT_TYPE && owner_type != LEVEL_TYPE)
    return FALSE;

  // Check the script's event type
  int event_type = GetScriptEventType(script_node);

  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == event_type) {
      if (event_info[j].flags & HAS_MATCENID_MASK)
        return TRUE;
      else
        return FALSE;
    }

  return FALSE;
}

// Checks to see if the given script has a Level Goal ID (based upon the event type)
bool CDallasMainDlg::ScriptHasALevelGoalID(HTREEITEM script_node) {
  // Check the owner type (only levels and objects can have a MatcenID)
  int owner_type = GetScriptOwnerType(script_node);
  if (owner_type != LEVEL_TYPE)
    return FALSE;

  // Check the script's event type
  int event_type = GetScriptEventType(script_node);

  for (int j = 0; event_info[j].type >= 0; j++)
    if (event_info[j].type == event_type) {
      if (event_info[j].flags & HAS_LEVGOALID_MASK)
        return TRUE;
      else
        return FALSE;
    }

  return FALSE;
}

//	Checks to see if a given node is a clause of the given type
bool CDallasMainDlg::NodeIsIfClause(HTREEITEM node) {
  tTreeNodeData *data;

  if (node == NULL)
    return (FALSE);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL || data->type != CONDITIONAL_HEADER_NODE)
    return (FALSE);

  if (data->ID != NESTED)
    return (FALSE);

  return (TRUE);
}

//	Checks to see if a given node is a clause of the given type
bool CDallasMainDlg::NodeIsClauseOfType(HTREEITEM node, int type) {
  tTreeNodeData *data;

  if (node == NULL)
    return (FALSE);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL || data->type != ACTIONS_HEADER_NODE)
    return (FALSE);

  if (data->ID != NESTED)
    return (FALSE);
  if (data->subID != type)
    return (FALSE);

  return (TRUE);
}

// Checks to see if it's ok to add an else clause to the given node
bool CDallasMainDlg::CanAppendElseToNode(HTREEITEM node) {
  HTREEITEM next_node;

  // Make sure given node is a nested THEN
  if (!NodeIsClauseOfType(node, THEN_CLAUSE))
    return (FALSE);

  // Make sure this node doesn't already have an else
  next_node = m_ScriptTree.GetNextSiblingItem(node);
  if (NodeIsClauseOfType(next_node, ELSE_CLAUSE))
    return (FALSE);

  return (TRUE);
}

// Obtains the string name for an expression operator type
char *CDallasMainDlg::GetExpressionOperatorTypeString(int type) {
  for (int j = 0; expop_info[j].type >= 0; j++)
    if (expop_info[j].type == type)
      return (expop_info[j].name);

  return (UNKNOWN_EXPOP_STRING);
}

// Obtains the string name for an expression operator type
char *CDallasMainDlg::GetExpressionOperatorCodeName(int type) {
  for (int j = 0; expop_info[j].type >= 0; j++)
    if (expop_info[j].type == type)
      return (expop_info[j].code_name);

  return (UNKNOWN_EXPOP_STRING);
}

// Obtains the string name for a literal
char *CDallasMainDlg::GetLiteralName(int type) {
  for (int j = 0; param_menu_item[j].type >= 0; j++)
    if (param_menu_item[j].type == type)
      return (param_menu_item[j].name);

  return (UNKNOWN_LITERAL_STRING);
}

// Updates the text display of the given node
void CDallasMainDlg::UpdateNodeText(HTREEITEM node) {
  CString new_text;
  tTreeNodeData *data;

  if (node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return;

  // Format and set the new text
  FormatTreeText(new_text, data, node);
  m_ScriptTree.SetItemText(node, new_text.GetBuffer(0));
}

// Updates the text of given node and all parent nodes above the given node
void CDallasMainDlg::UpdateAllParentNodesText(HTREEITEM node) {
  HTREEITEM parent;

  if (node == NULL)
    return;

  UpdateNodeText(node);

  parent = m_ScriptTree.GetParentItem(node);
  while (parent != NULL) {
    UpdateNodeText(parent);
    parent = m_ScriptTree.GetParentItem(parent);
  }
}

// Formats the given string according to the given node data
void CDallasMainDlg::FormatTreeText(CString &text, tTreeNodeData *data, HTREEITEM node /*=NULL*/) {
  CString tmp_str1, tmp_str2;
  object *objp;

  // Make sure given data is valid
  if (data == NULL)
    return;

  // Format the text according to the tree node type
  switch (data->type) {
  case SCRIPT_HEADER_NODE:
    text.Format("Script %.03d: %s", data->ID, data->name);
    break;
  case SCRIPT_OWNER_NODE:
    switch (data->ID) {
    case OBJECT_TYPE:
      if (data->int_val == OBJECT_HANDLE_NONE) {
        text.Format("Owner: %s (Object)", NONE_STRING);
        break;
      }
      objp = ObjGet(data->int_val);
      if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL)
        text.Format("Owner: *OBJECT_ERROR*");
      else
        text.Format("Owner: %s (Object)", objp->name);
      break;
    case TRIGGER_TYPE:
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        text.Format("Owner: %s (Trigger)", NOT_SPECIFIED_STRING);
        break;
      }
      if (data->int_val < 0 || data->int_val >= Num_triggers)
        text.Format("Owner: *INVALID_TRIGGER*");
      else
        text.Format("Owner: %s (Trigger)", Triggers[data->int_val].name);
      break;
    case LEVEL_TYPE:
      text.Format("Owner: Level");
      break;
    default:
      text.Format("Owner: %s", NOT_SPECIFIED_STRING);
      break;
    }
    break;
  case SCRIPT_EVENT_NODE:
    text.Format("Event: %s", GetEventTypeString(data->ID));
    break;
  case CONDITIONAL_HEADER_NODE:
    text.Format("If the following condition is met:");
    break;
  case ACTIONS_HEADER_NODE:
    if (data->ID == TOP_LEVEL && data->int_val == BREAK_SCRIPT_CHAIN)
      tmp_str2 = " and BREAK script chain";
    else
      tmp_str2 = "";
    if (data->ID == TOP_LEVEL && data->subID == 1)
      tmp_str1.Format(" (only do once%s)", tmp_str2);
    else if (data->ID == TOP_LEVEL && data->subID == 2)
      tmp_str1.Format(" (only do twice%s)", tmp_str2);
    else if (data->ID == TOP_LEVEL && data->subID >= 3)
      tmp_str1.Format(" (only do %d times%s)", data->subID, tmp_str2);
    else
      tmp_str1.Format("%s", tmp_str2);
    if (data->ID == NESTED && data->subID == ELSE_CLAUSE)
      text.Format("Else, perform these actions:");
    else
      text.Format("Then perform the following actions%s:", tmp_str1);
    break;
  case CONDITIONAL_STATEMENT_NODE:
    if (data->ID == ALWAYS_STATEMENT)
      text.Format("%s", ALWAYS_STRING);
    else
      FormatConditionText(text, node);
    break;
  case EXPRESSION_NODE:
    FormatQueryNodeText(tmp_str1, node);
    text.Format("%s: %s", data->name, tmp_str1);
    break;
  case EXPRESSION_OPERATOR_NODE:
    text.Format("Operation: %s", GetExpressionOperatorTypeString(data->subID));
    break;
  case ACTION_STATEMENT_NODE:
    if (data->ID == DO_NOTHING_ID)
      text.Format("%s", DO_NOTHING_STRING);
    else
      FormatActionNodeText(text, node);
    break;
  case LOGICAL_OPERATOR_NODE:
    GetLogicalOperatorTypeString(data->ID, tmp_str1);
    text.Format("%s", tmp_str1);
    break;
  case PARAMETER_NODE:
    FormatParameterValueText(tmp_str1, data);
    text.Format("%s: %s", data->name, tmp_str1.GetBuffer(0));
    break;
  case PARAMETER_OPERATOR_NODE:
    text.Format("this is a parameter operator");
    break;
  case CLIPBOARD_HEADER_NODE:
    text.Format("Clipboard");
    break;
  case UNKNOWN_NODE:
    text.Format("Unknown Type");
    break;
  default:
    text.Format("REALLY Unknown Type");
    break;
  }
}

// Formats the text for a Conditional Statement according to it and its children
void CDallasMainDlg::FormatConditionText(CString &text, HTREEITEM condition_node) {
  tTreeNodeData *data;
  HTREEITEM child_node;

  // Make sure given node is valid
  if (condition_node == NULL) {
    text = "*ERROR*";
    return;
  }

  // Get node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(condition_node);
  if (data == NULL) {
    text = "*ERROR*";
    return;
  }

  // Make sure given data node is a conditional statement node
  if (data->type != CONDITIONAL_STATEMENT_NODE) {
    text = "<Not a Conditional Statement>";
    return;
  }

  text = "(";

  // Get the first child (literal or query)
  child_node = m_ScriptTree.GetChildItem(condition_node);
  if (child_node != NULL) {
    CString temp_str;
    FormatGenericExpressionText(temp_str, child_node);
    text += temp_str;
  } else {
    text += "???";
  }

  text += ") ";

  // Get the second child (expression operator)
  if (child_node != NULL) {
    child_node = m_ScriptTree.GetNextSiblingItem(child_node);
    if (child_node != NULL) {
      CString temp_str;
      FormatGenericExpressionText(temp_str, child_node);
      text += temp_str;
    } else {
      text += "???";
    }
  }

  // If it's a comparison, get the third child (literal or query)
  if (child_node != NULL && data->ID == COMPARISON_STATEMENT) {
    child_node = m_ScriptTree.GetNextSiblingItem(child_node);
    if (child_node != NULL) {
      CString temp_str;
      FormatGenericExpressionText(temp_str, child_node);
      text += " (";
      text += temp_str;
      text += ")";
    } else {
      text += " (???)";
    }
  }
}

// Formats a child node of a conditional statement node
void CDallasMainDlg::FormatGenericExpressionText(CString &text, HTREEITEM gen_exp_node) {
  tTreeNodeData *data;

  // Make sure given node is valid
  if (gen_exp_node == NULL) {
    text = "*ERROR*";
    return;
  }

  // Get node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(gen_exp_node);
  if (data == NULL) {
    text = "*ERROR*";
    return;
  }

  // See if it's a parameter node
  if (data->type == PARAMETER_NODE) {
    FormatParameterValueText(text, data);
    return;
  }

  // See if it's a query node
  if (data->type == EXPRESSION_NODE) {
    FormatQueryNodeText(text, gen_exp_node);
    return;
  }

  // See if it's an expression operator node
  if (data->type == EXPRESSION_OPERATOR_NODE) {
    text.Format("%s", GetExpressionOperatorTypeString(data->subID));
    return;
  }

  text = "<Invalid Expression>";
}

// Formats the text for a Parameter Value according to the given node data
void CDallasMainDlg::FormatParameterValueText(CString &text, tTreeNodeData *data) {
  object *objp;
  char *temp_str;
  char temp_name[_MAX_PATH + 1];

  // Make sure given data is valid
  if (data == NULL) {
    text = "";
    return;
  }

  // Make sure given data node is a parameter node
  if (data->type != PARAMETER_NODE) {
    text = "<Not a Parameter>";
    return;
  }

  // Format the text according to the parameter type and value data
  switch (data->ID) {
  case DOOR_PARAMETER_TYPE:
    if (data->subID == USE_ME_HANDLE) {
      text.Format("OWNER");
      break;
    }
    if (data->int_val == OBJECT_HANDLE_NONE) {
      text.Format("%s", NONE_STRING);
      break;
    }
    objp = ObjGet(data->int_val);
    if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL)
      text.Format("*DOOR_ERROR*");
    else
      text.Format("%s", objp->name);
    break;
  case OBJECT_PARAMETER_TYPE:
    if (data->subID == USE_IT_HANDLE) {
      text.Format("IT");
      break;
    }
    if (data->subID == USE_ME_HANDLE) {
      text.Format("OWNER");
      break;
    }
    if (data->int_val == OBJECT_HANDLE_NONE) {
      text.Format("%s", NONE_STRING);
      break;
    }
    objp = ObjGet(data->int_val);
    if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL)
      text.Format("*OBJECT_ERROR*");
    else
      text.Format("%s", objp->name);
    break;
  case ROOM_PARAMETER_TYPE:
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (data->int_val < 0 || data->int_val > Highest_room_index)
      text.Format("*INVALID_ROOM*");
    else
      text.Format("%s", Rooms[data->int_val].name);
    break;
  case TRIGGER_PARAMETER_TYPE:
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (data->int_val < 0 || data->int_val >= Num_triggers)
      text.Format("*INVALID_TRIGGER*");
    else
      text.Format("%s", Triggers[data->int_val].name);
    break;
  case INT_PARAMETER_TYPE:
    text.Format("%d", data->int_val);
    break;
  case BOOL_PARAMETER_TYPE:
    if (data->int_val)
      text.Format("TRUE");
    else
      text.Format("FALSE");
    break;
  case FLOAT_PARAMETER_TYPE:
    text.Format("%.2f", data->float_val1);
    break;
  case VECTOR_PARAMETER_TYPE:
    text.Format("<%.2f,%.2f,%.2f>", data->float_val1, data->float_val2, data->float_val3);
    break;
  case STRING_PARAMETER_TYPE:
    if (strlen(data->str_val) == 0)
      text.Format("No ID Chosen");
    else {
      /*
      CString msg;
      char *full_msg;
      char short_msg[MAX_STRING_DISPLAY_LEN+1];

      // Display the first X chars in message
      full_msg=FindMessageInList(data->str_val);
      if(full_msg!=NULL) {
              if(strlen(full_msg) > MAX_STRING_DISPLAY_LEN) {
                      strncpy(short_msg,full_msg,MAX_STRING_DISPLAY_LEN);
                      short_msg[MAX_STRING_DISPLAY_LEN]='\0';
                      msg=short_msg;
                      msg+="...";
              }
              else
                      msg=full_msg;
      }
      else
              msg="<Message Not Found>";

      text.Format("%s=\"%s\"",data->str_val,msg);
      */
      text.Format("%s", data->str_val);
    }
    break;
  case PERCENTAGE_PARAMETER_TYPE:
    text.Format("%.1f%%", data->float_val1 * 100.0);
    break;
  case ENUM_PARAMETER_TYPE:
    if (data->subID == USE_GOALID_VALUE) {
      text.Format("GOAL ID");
    } else if (data->subID == USE_TIMERID_VALUE) {
      text.Format("TIMER ID");
    } else if (data->subID == USE_MATCENID_VALUE) {
      text.Format("MATCEN ID");
    } else {
      temp_str = GetEnumValueName(data->name, data->int_val);
      if (temp_str == NULL)
        text.Format("*UNKNOWN_ENUM*");
      else
        text.Format("%s", temp_str);
    }
    break;
  case SCRIPT_PARAMETER_TYPE:
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    text.Format("%d", data->int_val);
    break;
  case SOUND_PARAMETER_TYPE:
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (data->int_val < 0 || data->int_val >= MAX_SOUNDS || !Sounds[data->int_val].used)
      text.Format("*INVALID_SOUND*");
    else
      text.Format("%s", Sounds[data->int_val].name);
    break;
  case SPECNAME_PARAMETER_TYPE:
    if (strlen(data->str_val) == 0)
      text.Format("%s", NOT_SPECIFIED_STRING);
    else
      text.Format("\"%s\"", data->str_val);
    break;
  case TEXTURE_PARAMETER_TYPE:
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (data->int_val < 0 || data->int_val >= MAX_TEXTURES || !GameTextures[data->int_val].used)
      text.Format("*INVALID_TEXTURE*");
    else
      text.Format("%s", GameTextures[data->int_val].name);
    break;
  case FLAG_PARAMETER_TYPE:
    if (!FormatFlagValueNames(data->name, data->int_val, text))
      text.Format("*UNKNOWN_FLAG*");
    break;
  case PATH_PARAMETER_TYPE:
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (data->int_val < 0 || data->int_val >= MAX_GAME_PATHS || !GamePaths[data->int_val].used)
      text.Format("*INVALID_PATH*");
    else
      text.Format("%s", GamePaths[data->int_val].name);
    break;
  case MATCEN_PARAMETER_TYPE:
    if (data->subID == USE_MATCEN_EVENT_ID) {
      text.Format("MATCEN ID");
      break;
    }
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (!MatcenValid(data->int_val))
      text.Format("*INVALID_MATCEN*");
    else {
      char name[MAX_MATCEN_NAME_LEN + 1];
      Matcen[data->int_val]->GetName(name);
      text.Format("%s", name);
    }
    break;
  case LEVEL_GOAL_PARAMETER_TYPE:
    if (data->subID == USE_LEVEL_GOAL_ID) {
      text.Format("LEVEL GOAL ID");
      break;
    }
    if (data->int_val == NOT_SPECIFIED_TYPE) {
      text.Format("%s", NOT_SPECIFIED_STRING);
      break;
    }
    if (Level_goals.GoalGetName(data->int_val, temp_name, _MAX_PATH) < 0)
      text.Format("*INVALID_LEVEL_GOAL*");
    else {
      text.Format("%s", temp_name);
    }
    break;
  case STRM_AUDIO_PARAMETER_TYPE:
    if (strlen(data->str_val) == 0)
      text.Format("%s", NOT_SPECIFIED_STRING);
    else
      text.Format("\"%s\"", data->str_val);
    break;
  default:
    text.Format("Unknown Value Type");
    break;
  }
}

// Parses an action desc, replacing arg blocks with value strings taken from
// its child parameter nodes
void CDallasMainDlg::FormatActionNodeText(CString &text, HTREEITEM action_node) {
  CString name_text, default_text, range_text;
  char *desc;
  tTreeNodeData *data;
  HTREEITEM child;

  if (action_node == NULL) {
    text = "*ERROR*";
    return;
  }

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(action_node);
  if (data == NULL) {
    text = "*ERROR*";
    return;
  }

  if (data->ID == INVALID_FUNCTION_ID) {
    text = INVALID_FUNCTION_NAME;
    return;
  }

  desc = GetActionDesc(data->ID);
  if (desc == NULL) {
    text = "*ERROR*";
    return;
  }

  // obtain the first child
  child = m_ScriptTree.GetChildItem(action_node);

  text = "";
  while ((*desc) != '\0') {
    if ((*desc) == '[') {
      ParseParamBlock(desc, name_text, default_text, range_text);

      if (child == NULL)
        text += "???";
      else {
        CString tmp_str;
        tTreeNodeData *data;

        // Get node's data
        data = (tTreeNodeData *)m_ScriptTree.GetItemData(child);

        if (data->type == PARAMETER_NODE) {
          FormatParameterValueText(tmp_str, data);
          text += tmp_str;
        } else if (data->type == EXPRESSION_NODE) {
          FormatQueryNodeText(tmp_str, child);
          text += "(";
          text += tmp_str;
          text += ")";
        } else
          text += "<Invalid Node>";

        // Get next child
        child = m_ScriptTree.GetNextSiblingItem(child);
      }
    } else {
      text += (*desc);
      desc++;
    }
  }
}

/* OLD VERSION
// Parses an action desc, replacing arg blocks with value strings taken from
// its child parameter nodes
void CDallasMainDlg::FormatActionNodeText(CString &text, HTREEITEM action_node)
{
        char *desc;
        int j;
        tTreeNodeData *data;
        HTREEITEM child;
        bool ok_to_copy;

        if(action_node==NULL) {
                text="*ERROR*";
                return;
        }

        data=(tTreeNodeData *)m_ScriptTree.GetItemData(action_node);
        if(data==NULL) {
                text="*ERROR*";
                return;
        }

        if(data->ID==INVALID_FUNCTION_ID) {
                text=INVALID_FUNCTION_NAME;
                return;
        }

        desc=GetActionDesc(data->ID);
        if(desc==NULL) {
                text="*ERROR*";
                return;
        }

        // obtain the first child
        child=m_ScriptTree.GetChildItem(action_node);

        j=0;
        ok_to_copy=TRUE;
        text="";
        while(desc[j]!='\0') {
                if(desc[j]=='[') {
                        ok_to_copy=FALSE;
                }
                else if(desc[j]==']') {
                        ok_to_copy=TRUE;

                        if(child==NULL)
                                text+="???";
                        else {
                                CString tmp_str;
                                tTreeNodeData *data;

                                // Get node's data
                                data=(tTreeNodeData *)m_ScriptTree.GetItemData(child);

                                if(data->type==PARAMETER_NODE) {
                                        FormatParameterValueText(tmp_str,data);
                                        text+=tmp_str;
                                }
                                else if(data->type==EXPRESSION_NODE) {
                                        FormatQueryNodeText(tmp_str,child);
                                        text+="(";
                                        text+=tmp_str;
                                        text+=")";
                                }
                                else
                                        text+="<Invalid Node>";

                                // Get next child
                                child=m_ScriptTree.GetNextSiblingItem(child);
                        }
                }
                else if(ok_to_copy) {
                        text+=desc[j];
                }

                j++;
        }
}
*/

// Parses a query desc, replacing arg blocks with value strings taken from
// its child parameter nodes
void CDallasMainDlg::FormatQueryNodeText(CString &text, HTREEITEM query_node) {
  CString name_text, default_text, range_text;
  char *desc;
  HTREEITEM child;
  tTreeNodeData *data;

  if (query_node == NULL) {
    text = "*ERROR*";
    return;
  }

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(query_node);
  if (data == NULL) {
    text = "*ERROR*";
    return;
  }

  if (data->ID == INVALID_FUNCTION_ID) {
    text = INVALID_FUNCTION_NAME;
    return;
  }

  desc = GetQueryDesc(data->ID);
  if (desc == NULL) {
    text = "*ERROR*";
    return;
  }

  // obtain the first child
  child = m_ScriptTree.GetChildItem(query_node);

  text = "";

  // Skip over the return type
  desc = strchr(desc, ':');
  if (desc == NULL)
    return;
  desc++;

  while ((*desc) != '\0') {
    if ((*desc) == '[') {
      ParseParamBlock(desc, name_text, default_text, range_text);

      if (child == NULL)
        text += "???";
      else {
        CString tmp_str;
        tTreeNodeData *data;

        // Get node's data
        data = (tTreeNodeData *)m_ScriptTree.GetItemData(child);

        if (data->type == PARAMETER_NODE) {
          FormatParameterValueText(tmp_str, data);
          text += tmp_str;
        } else if (data->type == EXPRESSION_NODE) {
          CString tmp_str;
          FormatQueryNodeText(tmp_str, child);
          text += "(";
          text += tmp_str;
          text += ")";
        } else
          text += "<Invalid Node>";

        // Get next child
        child = m_ScriptTree.GetNextSiblingItem(child);
      }
    } else {
      text += (*desc);
      desc++;
    }
  }
}

/* OLD VERSION
// Parses a query desc, replacing arg blocks with value strings taken from
// its child parameter nodes
void CDallasMainDlg::FormatQueryNodeText(CString &text, HTREEITEM query_node)
{
        char *desc;
        int j;
        HTREEITEM child;
        tTreeNodeData *data;
        bool ok_to_copy, first_colon_found;

        if(query_node==NULL) {
                text="*ERROR*";
                return;
        }

        data=(tTreeNodeData *)m_ScriptTree.GetItemData(query_node);
        if(data==NULL) {
                text="*ERROR*";
                return;
        }

        if(data->ID==INVALID_FUNCTION_ID) {
                text=INVALID_FUNCTION_NAME;
                return;
        }

        desc=GetQueryDesc(data->ID);
        if(desc==NULL) {
                text="*ERROR*";
                return;
        }

        // obtain the first child
        child=m_ScriptTree.GetChildItem(query_node);

        j=0;
        ok_to_copy=FALSE;
        first_colon_found=FALSE;
        text="";
        while(desc[j]!='\0') {
                if(desc[j]=='[') {
                        ok_to_copy=FALSE;
                }
                else if(desc[j]==']') {
                        ok_to_copy=TRUE;

                        if(child==NULL)
                                text+="???";
                        else {
                                CString tmp_str;
                                tTreeNodeData *data;

                                // Get node's data
                                data=(tTreeNodeData *)m_ScriptTree.GetItemData(child);

                                if(data->type==PARAMETER_NODE) {
                                        FormatParameterValueText(tmp_str,data);
                                        text+=tmp_str;
                                }
                                else if(data->type==EXPRESSION_NODE) {
                                        CString tmp_str;
                                        FormatQueryNodeText(tmp_str,child);
                                        text+="(";
                                        text+=tmp_str;
                                        text+=")";
                                }
                                else
                                        text+="<Invalid Node>";

                                // Get next child
                                child=m_ScriptTree.GetNextSiblingItem(child);
                        }
                }
                else if(desc[j]==':' && !first_colon_found) {
                        first_colon_found=TRUE;
                        ok_to_copy=TRUE;
                }
                else if(ok_to_copy) {
                        text+=desc[j];
                }

                j++;
        }
}
*/

// Converts a parameter character ID into a paramter type
int CDallasMainDlg::ConvertParamCharToType(int param_char_ID) {
  int param_type;

  switch (param_char_ID) {
  case 'd':
    param_type = DOOR_PARAMETER_TYPE;
    break;
  case 'o':
    param_type = OBJECT_PARAMETER_TYPE;
    break;
  case 'r':
    param_type = ROOM_PARAMETER_TYPE;
    break;
  case 't':
    param_type = TRIGGER_PARAMETER_TYPE;
    break;
  case 'i':
    param_type = INT_PARAMETER_TYPE;
    break;
  case 'b':
    param_type = BOOL_PARAMETER_TYPE;
    break;
  case 'f':
    param_type = FLOAT_PARAMETER_TYPE;
    break;
  case 'v':
    param_type = VECTOR_PARAMETER_TYPE;
    break;
  case 's':
    param_type = STRING_PARAMETER_TYPE;
    break;
  case 'p':
    param_type = PERCENTAGE_PARAMETER_TYPE;
    break;
  case 'e':
    param_type = ENUM_PARAMETER_TYPE;
    break;
  case 'x':
    param_type = SCRIPT_PARAMETER_TYPE;
    break;
  case 'n':
    param_type = SOUND_PARAMETER_TYPE;
    break;
  case 'a':
    param_type = SPECNAME_PARAMETER_TYPE;
    break;
  case 'u':
    param_type = TEXTURE_PARAMETER_TYPE;
    break;
  case 'g':
    param_type = FLAG_PARAMETER_TYPE;
    break;
  case 'h':
    param_type = PATH_PARAMETER_TYPE;
    break;
  case 'm':
    param_type = MATCEN_PARAMETER_TYPE;
    break;
  case 'l':
    param_type = LEVEL_GOAL_PARAMETER_TYPE;
    break;
  case 'z':
    param_type = STRM_AUDIO_PARAMETER_TYPE;
    break;
  default:
    param_type = UNKNOWN_PARAMETER_TYPE;
    break;
  }

  return (param_type);
}

// Converts a parameter type into a character ID
int CDallasMainDlg::ConvertParamTypeToChar(int param_type) {
  int param_char_ID;

  switch (param_type) {
  case DOOR_PARAMETER_TYPE:
    param_char_ID = 'd';
    break;
  case OBJECT_PARAMETER_TYPE:
    param_char_ID = 'o';
    break;
  case ROOM_PARAMETER_TYPE:
    param_char_ID = 'r';
    break;
  case TRIGGER_PARAMETER_TYPE:
    param_char_ID = 't';
    break;
  case INT_PARAMETER_TYPE:
    param_char_ID = 'i';
    break;
  case BOOL_PARAMETER_TYPE:
    param_char_ID = 'b';
    break;
  case FLOAT_PARAMETER_TYPE:
    param_char_ID = 'f';
    break;
  case VECTOR_PARAMETER_TYPE:
    param_char_ID = 'v';
    break;
  case STRING_PARAMETER_TYPE:
    param_char_ID = 's';
    break;
  case PERCENTAGE_PARAMETER_TYPE:
    param_char_ID = 'p';
    break;
  case ENUM_PARAMETER_TYPE:
    param_char_ID = 'e';
    break;
  case SCRIPT_PARAMETER_TYPE:
    param_char_ID = 'x';
    break;
  case SOUND_PARAMETER_TYPE:
    param_char_ID = 'n';
    break;
  case SPECNAME_PARAMETER_TYPE:
    param_char_ID = 'a';
    break;
  case TEXTURE_PARAMETER_TYPE:
    param_char_ID = 'u';
    break;
  case FLAG_PARAMETER_TYPE:
    param_char_ID = 'g';
    break;
  case PATH_PARAMETER_TYPE:
    param_char_ID = 'h';
    break;
  case MATCEN_PARAMETER_TYPE:
    param_char_ID = 'm';
    break;
  case LEVEL_GOAL_PARAMETER_TYPE:
    param_char_ID = 'l';
    break;
  case STRM_AUDIO_PARAMETER_TYPE:
    param_char_ID = 'z';
    break;
  default:
    param_char_ID = '?';
    break;
  }

  return (param_char_ID);
}

// Turns bold on or off for a specified node
void CDallasMainDlg::SetBoldNodeText(HTREEITEM node, bool bold_on) {
  if (node == NULL)
    return;

  if (bold_on)
    m_ScriptTree.SetItemState(node, TVIS_BOLD, TVIS_BOLD);
  else
    m_ScriptTree.SetItemState(node, ~TVIS_BOLD, TVIS_BOLD);
}

// Checks to see if the parent of the given node is a Conditional Statement
// node of type COMPARISON_STATEMENT
bool CDallasMainDlg::ParentIsComparisonConditional(HTREEITEM node) {
  HTREEITEM parent;
  tTreeNodeData *data;

  if (node == NULL)
    return (FALSE);

  // Get the parent
  parent = m_ScriptTree.GetParentItem(node);
  if (parent == NULL)
    return (FALSE);

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(parent);
  if (data == NULL)
    return (FALSE);

  // Check the parent node
  if (data->type == CONDITIONAL_STATEMENT_NODE && data->ID == COMPARISON_STATEMENT)
    return (TRUE);

  return (FALSE);
}

// If the given node is a parameter or query, it determines its type (or return type)
// and returns it, unless the parent of the given node is a Comparison conditional
// statement.  In this case, any parameter type is allowed
int CDallasMainDlg::GetValidParamType(HTREEITEM node, CString &name) {
  tTreeNodeData *data;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return (-1);

  name = "";

  if (data->type == PARAMETER_NODE) {
    if (ParentIsComparisonConditional(node) && GetChildPosition(node) == 1)
      return (ANY_PARAMETER_TYPE);
    name = data->name;
    return (data->ID);
  }

  if (data->type == EXPRESSION_NODE) {
    if (ParentIsComparisonConditional(node) && GetChildPosition(node) == 1)
      return (ANY_PARAMETER_TYPE);
    return (GetQueryReturnType(data->ID, name));
  }

  return (-1);
}

// If the given node is a parameter or query, it determines its type (or return type)
// and returns it
int CDallasMainDlg::GetParamType(HTREEITEM node, CString &name) {
  tTreeNodeData *data;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return (-1);

  name = "";

  if (data->type == PARAMETER_NODE) {
    name = data->name;
    return (data->ID);
  }

  if (data->type == EXPRESSION_NODE) {
    return (GetQueryReturnType(data->ID, name));
  }

  return (-1);
}

// Attaches the correct bitmap image to a node
void CDallasMainDlg::SetTreeNodeImage(HTREEITEM node) {
  tTreeNodeData *data;
  int temp_id;

  // Make sure node is valid
  if (node == NULL)
    return;

  // Get node data, make sure it's valid
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return;

  // Set the item's display images appropriately
  switch (data->type) {
  case SCRIPT_HEADER_NODE:
    m_ScriptTree.SetItemImage(node, 0, 0);
    break;
  case SCRIPT_OWNER_NODE:
    m_ScriptTree.SetItemImage(node, 10, 10);
    break;
  case SCRIPT_EVENT_NODE:
    m_ScriptTree.SetItemImage(node, 11, 11);
    break;
  case CONDITIONAL_HEADER_NODE:
    if (data->ID == TOP_LEVEL)
      m_ScriptTree.SetItemImage(node, 1, 1);
    else
      m_ScriptTree.SetItemImage(node, 8, 8);
    break;
  case ACTIONS_HEADER_NODE:
    if (data->ID == TOP_LEVEL)
      m_ScriptTree.SetItemImage(node, 2, 2);
    else {
      if (data->subID == THEN_CLAUSE)
        m_ScriptTree.SetItemImage(node, 9, 9);
      else
        m_ScriptTree.SetItemImage(node, 18, 18);
    }
    break;
  case CONDITIONAL_STATEMENT_NODE:
    m_ScriptTree.SetItemImage(node, 3, 3);
    break;
  case EXPRESSION_NODE:
    m_ScriptTree.SetItemImage(node, 16, 16);
    break;
  case EXPRESSION_OPERATOR_NODE:
    m_ScriptTree.SetItemImage(node, 17, 17);
    break;
  case ACTION_STATEMENT_NODE:
    m_ScriptTree.SetItemImage(node, 4, 4);
    break;
  case LOGICAL_OPERATOR_NODE:
    if (data->ID == AND_TYPE)
      m_ScriptTree.SetItemImage(node, 6, 6);
    else if (data->ID == OR_TYPE)
      m_ScriptTree.SetItemImage(node, 5, 5);
    else
      m_ScriptTree.SetItemImage(node, 7, 7);
    break;
  case PARAMETER_NODE:
    // Get image type based upon what kind of parameter it is
    switch (data->ID) {
    case DOOR_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case OBJECT_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case ROOM_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case TRIGGER_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case INT_PARAMETER_TYPE:
      temp_id = 13;
      break;
    case BOOL_PARAMETER_TYPE:
      temp_id = 14;
      break;
    case FLOAT_PARAMETER_TYPE:
      temp_id = 13;
      break;
    case VECTOR_PARAMETER_TYPE:
      temp_id = 15;
      break;
    case STRING_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case PERCENTAGE_PARAMETER_TYPE:
      temp_id = 14;
      break;
    case ENUM_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case SCRIPT_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case SOUND_PARAMETER_TYPE:
      temp_id = 15;
      break;
    case SPECNAME_PARAMETER_TYPE:
      temp_id = 13;
      break;
    case TEXTURE_PARAMETER_TYPE:
      temp_id = 15;
      break;
    case FLAG_PARAMETER_TYPE:
      temp_id = 15;
      break;
    case PATH_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case MATCEN_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case LEVEL_GOAL_PARAMETER_TYPE:
      temp_id = 12;
      break;
    case STRM_AUDIO_PARAMETER_TYPE:
      temp_id = 15;
      break;
    default:
      temp_id = 12;
      break;
    }
    m_ScriptTree.SetItemImage(node, temp_id, temp_id);
    break;
  case PARAMETER_OPERATOR_NODE:
    m_ScriptTree.SetItemImage(node, 13, 13);
    break;
  case CLIPBOARD_HEADER_NODE:
    m_ScriptTree.SetItemImage(node, 19, 19);
    break;
  case UNKNOWN_NODE:
    m_ScriptTree.SetItemImage(node, 0, 0);
    break;
  default:
    m_ScriptTree.SetItemImage(node, 0, 0);
    break;
  }
}

// Adds a node to the tree using the given data
HTREEITEM CDallasMainDlg::AddNodeToTree(HTREEITEM parent, HTREEITEM insertbefore, HTREEITEM src_node,
                                        bool expand /*=FALSE*/) {
  tTreeNodeData *data;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(src_node);
  return (AddNodeToTree(parent, insertbefore, data, expand));
}

// Adds a node to the tree using the given data
HTREEITEM CDallasMainDlg::AddNodeToTree(HTREEITEM parent, HTREEITEM insertbefore, tTreeNodeData *data_node,
                                        bool expand /*=FALSE*/) {
  HTREEITEM added_item, insertafter, new_parent;
  TV_INSERTSTRUCT tvs;
  TV_ITEM tvi;
  tTreeNodeData *new_data_node;
  CString node_text;

  // Allocate a new data node, and copy given data into it
  new_data_node = new tTreeNodeData;
  if (new_data_node == NULL) {
    MessageBox("Unable to Allocate a New Data Node", "Out of Memory Error!", MB_OK | MB_ICONEXCLAMATION);
    return NULL;
  }

  // Copy given data into new node
  (*new_data_node) = (*data_node);

  // Fill out the Item structure
  tvi.mask = TVIF_TEXT;
  // FormatTreeText(node_text,new_data_node);
  // tvi.pszText=node_text.GetBuffer(0);
  tvi.pszText = "";

  // Get the previous child node for "insert before"
  if (insertbefore != TVI_FIRST && insertbefore != TVI_LAST && insertbefore != TVI_SORT) {
    insertafter = m_ScriptTree.GetPrevSiblingItem(insertbefore);
    if (insertafter == NULL)
      insertafter = TVI_FIRST;
    new_parent = parent;
  } else {
    insertafter = insertbefore;
    new_parent = parent;
  }

  // Fill out the Insert structure
  tvs.hInsertAfter = insertafter;
  tvs.hParent = new_parent;
  tvs.item = tvi;

  added_item = m_ScriptTree.InsertItem(&tvs);

  // If add was unsuccessfull, delete the item data
  if (added_item == NULL) {
    delete new_data_node;
    MessageBox("Unable to Allocate a New Tree Node", "Out of Memory Error!", MB_OK | MB_ICONEXCLAMATION);
    return NULL;
  }

  // Set the node data and image
  m_ScriptTree.SetItemData(added_item, (DWORD)new_data_node);
  SetTreeNodeImage(added_item);

  // Set the new node's text
  UpdateNodeText(added_item);

  // Expand the parent if necessary
  if (parent != NULL && expand)
    m_ScriptTree.Expand(parent, TVE_EXPAND);

  return (added_item);
}

//	Frees all data for a tree leaf (and all children of the given leaf)
void CDallasMainDlg::FreeTreeItem(HTREEITEM item) {
  tTreeNodeData *data;

  if (item == NULL)
    return;

  // Free all children of this node
  FreeTreeItemChildren(item);

  // Deallocate the data structure
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(item);
  delete data;

  // Delete the actual tree node
  m_ScriptTree.DeleteItem(item);
}

//	Frees all children of the given leaf, but leaves the given leaf intact
void CDallasMainDlg::FreeTreeItemChildren(HTREEITEM item) {
  HTREEITEM child, old_child;

  if (item == NULL)
    return;

  child = m_ScriptTree.GetChildItem(item);
  while (child) {
    old_child = child;
    child = m_ScriptTree.GetNextSiblingItem(child);
    FreeTreeItem(old_child);
  }
}

// Expands given node and all children
void CDallasMainDlg::ExpandAll(HTREEITEM node, UINT nCode) {
  HTREEITEM child;

  if (node == NULL)
    return;

  child = m_ScriptTree.GetChildItem(node);
  while (child != NULL) {
    ExpandAll(child, nCode);
    child = m_ScriptTree.GetNextSiblingItem(child);
  }

  // Expand this node
  m_ScriptTree.Expand(node, nCode);
}

// Copies the entire tree starting at src_node to the specified destination
HTREEITEM CDallasMainDlg::CopyTree(HTREEITEM dest_parent, HTREEITEM dest_insert_before, HTREEITEM src_node) {
  HTREEITEM dest_node;

  dest_node = AddNodeToTree(dest_parent, dest_insert_before, src_node);
  if (dest_node != NULL) {
    CopyChildren(dest_node, src_node);
    UpdateNodeText(dest_node);
  }

  return (dest_node);
}

// Copies all the children of src_parent to dest_parent
HTREEITEM CDallasMainDlg::CopyChildren(HTREEITEM dest_parent, HTREEITEM src_parent) {
  HTREEITEM src_child, dest_child;

  dest_child = NULL;
  src_child = m_ScriptTree.GetChildItem(src_parent);
  while (src_child != NULL) {
    dest_child = AddNodeToTree(dest_parent, TVI_LAST, src_child);
    if (dest_child == NULL)
      return NULL;
    CopyChildren(dest_child, src_child);
    UpdateNodeText(dest_child);
    src_child = m_ScriptTree.GetNextSiblingItem(src_child);
  }

  return (dest_child);
}

// Returns the position of the given child (i.e. child is the Nth child of parent)
int CDallasMainDlg::GetChildPosition(HTREEITEM child) {
  HTREEITEM node;
  int count;

  if (child == NULL)
    return 0;

  count = 1;
  node = m_ScriptTree.GetPrevSiblingItem(child);
  while (node != NULL) {
    node = m_ScriptTree.GetPrevSiblingItem(node);
    count++;
  }

  return (count);
}

// Returns the Nth child of the given parent (NULL if one doesn't exist)
HTREEITEM CDallasMainDlg::GetNthChild(HTREEITEM parent, int n) {
  HTREEITEM child;
  int count;

  if (parent == NULL || n <= 0)
    return NULL;

  count = 1;
  child = m_ScriptTree.GetChildItem(parent);

  while (child != NULL && count != n) {
    child = m_ScriptTree.GetNextSiblingItem(child);
    count++;
  }

  return (child);
}

// Returns the child count
int CDallasMainDlg::GetChildCount(HTREEITEM parent) {
  HTREEITEM child;
  int count;

  if (parent == NULL)
    return 0;

  count = 0;
  child = m_ScriptTree.GetChildItem(parent);
  while (child != NULL) {
    child = m_ScriptTree.GetNextSiblingItem(child);
    count++;
  }

  return (count);
}

// Returns the script ID for any given node (must be a descendant of SCRIPT_HEADER_NODE though)
int CDallasMainDlg::GetScriptID(HTREEITEM script_node) {
  HTREEITEM script_header_node;
  tTreeNodeData *data;

  script_header_node = GetParentNodeOfType(script_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return (-1);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_header_node);
  if (data == NULL)
    return (-1);

  return (data->ID);
}

// Returns script header node of script matching given script ID (NULL if not found)
HTREEITEM CDallasMainDlg::FindScriptIDNode(int scriptID) {
  HTREEITEM node;

  // Fill up the list
  node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (node != NULL) {
    int id = GetScriptID(node);
    if (id == scriptID) {
      return (node);
    }
    node = m_ScriptTree.GetNextSiblingItem(node);
  }

  return (NULL);
}

// Compare function for GetLowestUnusedScriptID()
int id_list_compare(const void *arg1, const void *arg2) {
  int *num1 = (int *)arg1;
  int *num2 = (int *)arg2;

  if ((*num1) < (*num2))
    return (-1);
  return (1);
}

// Looks through scripts to determine the lowest unused script ID
int CDallasMainDlg::GetLowestUnusedScriptID(void) {
  int *list;
  int size;
  int max_size;
  int lowest_id;
  HTREEITEM node;

  lowest_id = 0;

  // Create the Script ID List
  max_size = GetChildCount(TVI_ROOT);
  if (max_size == 0)
    return (lowest_id);
  list = (int *)mem_malloc(sizeof(int) * max_size);
  if (list == NULL)
    return (m_NextScriptID);

  // Fill up the list
  size = 0;
  node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (node != NULL) {
    int id = GetScriptID(node);
    if (id >= 0 && size < max_size) {
      list[size] = id;
      size++;
    }
    node = m_ScriptTree.GetNextSiblingItem(node);
  }

  // Sort and determine the lowest unused ID
  qsort((void *)list, size, sizeof(int), id_list_compare);

  // Determine the lowest number
  int j;
  lowest_id = 0;
  for (j = 0; j < size; j++) {
    if (lowest_id < list[j])
      break;
    lowest_id = list[j] + 1;
  }

  /* Debugging output
  CString msg, num;
  msg="";
  for(j=0;j<size;j++) {
          num.Format("%d ",list[j]);
          msg+=num;
  }
  num.Format("-> %d ",lowest_id);
  msg+=num;
  MessageBox(msg,"The Script ID List");
  */

  // Free up the list
  mem_free(list);

  return (lowest_id);
}

// Returns the node type of given node
int CDallasMainDlg::GetNodeType(HTREEITEM node) {
  tTreeNodeData *data;

  if (node == NULL)
    return (UNKNOWN_NODE);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return (UNKNOWN_NODE);

  return (data->type);
}

// Returns the script owner type for any given node (must be a descendant of SCRIPT_HEADER_NODE though)
int CDallasMainDlg::GetScriptOwnerType(HTREEITEM script_node) {
  HTREEITEM script_owner_node;
  tTreeNodeData *data;

  script_owner_node = GetScriptOwnerNode(script_node);
  if (script_owner_node == NULL)
    return (-1);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_owner_node);
  if (data == NULL)
    return (-1);

  return (data->ID);
}

// Returns the script event type for any given node (must be a descendant of SCRIPT_HEADER_NODE though)
int CDallasMainDlg::GetScriptEventType(HTREEITEM script_node) {
  HTREEITEM script_event_node;
  tTreeNodeData *data;

  script_event_node = GetScriptEventNode(script_node);
  if (script_event_node == NULL)
    return (-1);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_event_node);
  if (data == NULL)
    return (-1);

  return (data->ID);
}

// Sets the script event type for any given node (must be a descendant of SCRIPT_HEADER_NODE though)
bool CDallasMainDlg::SetScriptEventType(HTREEITEM script_node, int type) {
  HTREEITEM script_event_node;
  tTreeNodeData *data;

  script_event_node = GetScriptEventNode(script_node);
  if (script_event_node == NULL)
    return FALSE;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_event_node);
  if (data == NULL)
    return FALSE;

  data->ID = type;
  UpdateAllParentNodesText(script_event_node);

  return TRUE;
}

// Searches for a parent node (or current node) that matches the given type (returns NULL if none found)
HTREEITEM CDallasMainDlg::GetParentNodeOfType(HTREEITEM child_node, int node_type) {
  HTREEITEM parent;
  tTreeNodeData *data;

  parent = child_node;
  while (parent != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(parent);
    if (data != NULL && data->type == node_type)
      return (parent);
    parent = m_ScriptTree.GetParentItem(parent);
  }

  return (parent);
}

// Returns the data of the closest EXPRESSION or ACTION node to the given node
tTreeNodeData *CDallasMainDlg::GetNearestFunctionNode(HTREEITEM node) {
  HTREEITEM parent;
  tTreeNodeData *data;

  parent = node;
  while (parent != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(parent);
    if (data != NULL && (data->type == EXPRESSION_NODE || data->type == ACTION_STATEMENT_NODE))
      return (data);
    parent = m_ScriptTree.GetParentItem(parent);
  }

  return (NULL);
}

// Searches for either an ACTION_STATEMENT_NODE or an EXPRESSION_NODE
// that is the closest parent to the given PARAMETER_NODE (returns NULL if none found)
HTREEITEM CDallasMainDlg::GetParameterParentNode(HTREEITEM param_node) {
  HTREEITEM parent;
  tTreeNodeData *data;

  // Make sure given node is a parameter node
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(param_node);
  if (data == NULL || data->type != PARAMETER_NODE)
    return NULL;

  // Keep getting the parent until we find a good match (or run out of parents)
  parent = m_ScriptTree.GetParentItem(param_node);
  while (parent != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(parent);
    if (data != NULL && data->type == ACTION_STATEMENT_NODE)
      return (parent);
    if (data != NULL && data->type == EXPRESSION_NODE)
      return (parent);
    parent = m_ScriptTree.GetParentItem(parent);
  }

  return (parent);
}

// Returns the owner node for any given Script node
HTREEITEM CDallasMainDlg::GetScriptOwnerNode(HTREEITEM node) {
  HTREEITEM temp_node;

  // Get the parent Script header node of the given node
  temp_node = GetParentNodeOfType(node, SCRIPT_HEADER_NODE);
  if (temp_node == NULL)
    return NULL;

  // Get the owner node (first child of script header)
  temp_node = m_ScriptTree.GetChildItem(temp_node);

  return (temp_node);
}

// Returns the event node for any given Script node
HTREEITEM CDallasMainDlg::GetScriptEventNode(HTREEITEM node) {
  HTREEITEM temp_node;

  // Get the script owner node
  temp_node = GetScriptOwnerNode(node);
  if (node == NULL)
    return NULL;

  // Get the event node (next node after owner)
  temp_node = m_ScriptTree.GetNextSiblingItem(temp_node);

  return (temp_node);
}

// Returns the conditional header (TOP LEVEL) node for any given Script node
HTREEITEM CDallasMainDlg::GetConditionalHeaderNode(HTREEITEM node) {
  HTREEITEM temp_node;

  // Get the script owner node
  temp_node = GetScriptEventNode(node);
  if (node == NULL)
    return NULL;

  // Get the conditional header node (next node after event node)
  temp_node = m_ScriptTree.GetNextSiblingItem(temp_node);

  return (temp_node);
}

// Returns the action header (TOP LEVEL) node for any given Script node
HTREEITEM CDallasMainDlg::GetActionHeaderNode(HTREEITEM node) {
  HTREEITEM temp_node;

  // Get the script owner node
  temp_node = GetConditionalHeaderNode(node);
  if (node == NULL)
    return NULL;

  // Get the action header node (next node after conditional header)
  temp_node = m_ScriptTree.GetNextSiblingItem(temp_node);

  return (temp_node);
}

// Highlights the headers for all scripts whose owner matches
// the owner specified in m_ScriptOwnerType and m_ScriptOwnerHandle
void CDallasMainDlg::HighlightAllScripts(void) {
  HTREEITEM script_header_node;

  // Group each script header node into the list
  script_header_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_header_node != NULL) {
    HighlightScript(script_header_node);
    script_header_node = m_ScriptTree.GetNextSiblingItem(script_header_node);
  }
}

// Highlights the headers for all scripts whose owner matches
// the owner specified in m_ScriptOwnerType and m_ScriptOwnerHandle
void CDallasMainDlg::HighlightScript(HTREEITEM node) {
  HTREEITEM script_header_node;

  script_header_node = GetParentNodeOfType(node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  HTREEITEM owner_node, event_node;
  tTreeNodeData *data;
  bool owners_match;

  owners_match = FALSE;
  owner_node = GetScriptOwnerNode(script_header_node);
  if (owner_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(owner_node);
    if (data != NULL) {
      if (m_ScriptOwnerType == ALL_OWNERS_TYPE)
        owners_match = TRUE;
      else if (m_ScriptOwnerType == LEVEL_TYPE && data->ID == LEVEL_TYPE)
        owners_match = TRUE;
      else if (m_ScriptOwnerType == ALL_OBJECTS_TYPE && data->ID == OBJECT_TYPE)
        owners_match = TRUE;
      else if (m_ScriptOwnerType == ALL_TRIGGERS_TYPE && data->ID == TRIGGER_TYPE)
        owners_match = TRUE;
      else if (m_ScriptOwnerType == data->ID && m_ScriptOwnerHandle == data->int_val)
        owners_match = TRUE;
    }
  }

  event_node = GetScriptEventNode(script_header_node);
  if (event_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(event_node);
    if (data != NULL) {
      int event_type = GetHighlightedEvent();
      if (event_type != ALL_EVENT_TYPES && data->ID != event_type)
        owners_match = FALSE;
    }
  }

  if (owners_match)
    SetBoldNodeText(script_header_node, TRUE);
  else
    SetBoldNodeText(script_header_node, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// Message List Functions
/////////////////////////////////////////////////////////////////////////////

// Initializes the message list,
// MUST BE CALLED BEFORE USING ANY MESSAGE LIST functions!!!
void CDallasMainDlg::InitMessageList(void) {
  int j;

  // Init the list of message entries to empty
  for (j = 0; j < MAX_MESSAGE_LIST_ENTRIES; j++)
    m_MessageEntryList[j] = NULL;
}

// Clears the message list
void CDallasMainDlg::ClearMessageList(void) {
  int j;

  // Wipeout the list of message entries
  for (j = 0; j < MAX_MESSAGE_LIST_ENTRIES; j++)
    if (m_MessageEntryList[j] != NULL) {
      delete m_MessageEntryList[j];
      m_MessageEntryList[j] = NULL;
    }

  // Reset the next message ID
  m_NextMessageID = 1;

  // Clear the message list and edit boxes
  m_MessageEdit.SetWindowText("");
  m_MessageList.ResetContent();
}

// Adds a message to the list
bool CDallasMainDlg::AddToMessageList(char *name, char *message) {
  tMessageListEntry *empty_slot;
  int index;

  // Make sure no duplicate entries exist
  if (FindMessageInList(name) != NULL) {
    m_MessageListErrorCode = MSG_LIST_DUP_NAME_ERROR;
    return FALSE;
  }

  // Search the list for an empty slot, and add the message
  empty_slot = GetEmptyMessageListEntry();
  if (empty_slot == NULL) {
    m_MessageListErrorCode = MSG_LIST_FULL_ERROR;
    return FALSE;
  }

  // Set the data
  strncpy(empty_slot->name, name, MAX_MESSAGE_NAME_LEN);
  empty_slot->name[MAX_MESSAGE_NAME_LEN] = '\0';
  strncpy(empty_slot->message, message, MAX_MESSAGE_LEN);
  empty_slot->message[MAX_MESSAGE_LEN] = '\0';

  // Add to the list and edit controls
  index = m_MessageList.AddString(name);
  if (index < 0) {
    m_MessageListErrorCode = MSG_LIST_FULL_ERROR;
    return FALSE;
  }

  m_MessageList.SetItemData(index, (DWORD)empty_slot);

  // Set the new selection to be the current selection
  m_MessageList.SetCurSel(index);
  OnSelchangeMessageList();

  return TRUE;
}

// Returns a message matching the given name, or NULL if none found
char *CDallasMainDlg::FindMessageInList(char *name) {
  int j;

  // Scan entry list for given name
  for (j = 0; j < MAX_MESSAGE_LIST_ENTRIES; j++)
    if (m_MessageEntryList[j] != NULL && strcmp(m_MessageEntryList[j]->name, name) == 0)
      return (m_MessageEntryList[j]->message);

  return (NULL);
}

// Deletes a message entry
int CDallasMainDlg::DeleteMessageListEntry(char *name) {
  int j;

  // Scan entry list for given name
  for (j = 0; j < MAX_MESSAGE_LIST_ENTRIES; j++)
    if (m_MessageEntryList[j] != NULL && strcmp(m_MessageEntryList[j]->name, name) == 0) {
      delete m_MessageEntryList[j];
      m_MessageEntryList[j] = NULL;
      return (TRUE);
    }

  return (FALSE);
}

// Returns an available entry slot, or NULL if none exist
tMessageListEntry *CDallasMainDlg::GetEmptyMessageListEntry(void) {
  int j;

  // Scan entry list for an empty slot
  for (j = 0; j < MAX_MESSAGE_LIST_ENTRIES; j++)
    if (m_MessageEntryList[j] == NULL) {
      m_MessageEntryList[j] = new tMessageListEntry;
      return (m_MessageEntryList[j]);
    }

  return (NULL);
}

/////////////////////////////////////////////////////////////////////////////
// Name List functions
/////////////////////////////////////////////////////////////////////////////

// Initialize all the name lists
void CDallasMainDlg::InitNameLists(void) {
  int j;

  // Init the Door list
  for (j = 0; j < MAX_NAMED_DOORS; j++)
    m_DoorList[j] = NULL;
  m_DoorListSize = 0;

  // Init the object list
  for (j = 0; j < MAX_NAMED_OBJECTS; j++)
    m_ObjectList[j] = NULL;
  m_ObjectListSize = 0;

  // Init the Room list
  for (j = 0; j < MAX_NAMED_ROOMS; j++)
    m_RoomList[j] = NULL;
  m_RoomListSize = 0;

  // Init the Trigger list
  for (j = 0; j < MAX_NAMED_TRIGGERS; j++)
    m_TriggerList[j] = NULL;
  m_TriggerListSize = 0;

  // Init the sound list
  for (j = 0; j < MAX_NAMED_SOUNDS; j++)
    m_SoundList[j] = NULL;
  m_SoundListSize = 0;

  // Init the Texture list
  for (j = 0; j < MAX_NAMED_TEXTURES; j++)
    m_TextureList[j] = NULL;
  m_TextureListSize = 0;

  // Init the Specname list
  for (j = 0; j < MAX_SPECNAMES; j++)
    m_SpecnameList[j] = NULL;
  m_SpecnameListSize = 0;

  // Init the Path list
  for (j = 0; j < MAX_NAMED_PATHS; j++)
    m_PathList[j] = NULL;
  m_PathListSize = 0;

  // Init the Matcen list
  for (j = 0; j < MAX_NAMED_MATCENS; j++)
    m_MatcenList[j] = NULL;
  m_MatcenListSize = 0;

  // Init the Goal list
  for (j = 0; j < MAX_NAMED_GOALS; j++)
    m_GoalList[j] = NULL;
  m_GoalListSize = 0;

  // Init the StrmAudio list
  for (j = 0; j < MAX_NAMED_STRM_AUDIO; j++)
    m_StrmAudioList[j] = NULL;
  m_StrmAudioListSize = 0;

  // Init the Message name list
  for (j = 0; j < MAX_MESSAGE_LIST_ENTRIES; j++)
    m_MessageNameList[j] = NULL;
  m_MessageNameListSize = 0;
}

// Empty the name lists
void CDallasMainDlg::ClearNameLists(void) {
  int j;

  // Clear the Door list
  for (j = 0; j < m_DoorListSize; j++)
    if (m_DoorList[j] != NULL) {
      mem_free(m_DoorList[j]);
      m_DoorList[j] = NULL;
    }
  m_DoorListSize = 0;

  // Clear the object list
  for (j = 0; j < m_ObjectListSize; j++)
    if (m_ObjectList[j] != NULL) {
      mem_free(m_ObjectList[j]);
      m_ObjectList[j] = NULL;
    }
  m_ObjectListSize = 0;

  // Clear the Room list
  for (j = 0; j < m_RoomListSize; j++)
    if (m_RoomList[j] != NULL) {
      mem_free(m_RoomList[j]);
      m_RoomList[j] = NULL;
    }
  m_RoomListSize = 0;

  // Clear the Trigger list
  for (j = 0; j < m_TriggerListSize; j++)
    if (m_TriggerList[j] != NULL) {
      mem_free(m_TriggerList[j]);
      m_TriggerList[j] = NULL;
    }
  m_TriggerListSize = 0;

  // Clear the sound list
  for (j = 0; j < m_SoundListSize; j++)
    if (m_SoundList[j] != NULL) {
      mem_free(m_SoundList[j]);
      m_SoundList[j] = NULL;
    }
  m_SoundListSize = 0;

  // Clear the Texture list
  for (j = 0; j < m_TextureListSize; j++)
    if (m_TextureList[j] != NULL) {
      mem_free(m_TextureList[j]);
      m_TextureList[j] = NULL;
    }
  m_TextureListSize = 0;

  // Clear the Specname list
  for (j = 0; j < m_SpecnameListSize; j++)
    if (m_SpecnameList[j] != NULL) {
      mem_free(m_SpecnameList[j]);
      m_SpecnameList[j] = NULL;
    }
  m_SpecnameListSize = 0;

  // Clear the Path list
  for (j = 0; j < m_PathListSize; j++)
    if (m_PathList[j] != NULL) {
      mem_free(m_PathList[j]);
      m_PathList[j] = NULL;
    }
  m_PathListSize = 0;

  // Clear the Matcen list
  for (j = 0; j < m_MatcenListSize; j++)
    if (m_MatcenList[j] != NULL) {
      mem_free(m_MatcenList[j]);
      m_MatcenList[j] = NULL;
    }
  m_MatcenListSize = 0;

  // Clear the Goal list
  for (j = 0; j < m_GoalListSize; j++)
    if (m_GoalList[j] != NULL) {
      mem_free(m_GoalList[j]);
      m_GoalList[j] = NULL;
    }
  m_GoalListSize = 0;

  // Clear the StrmAudio list
  for (j = 0; j < m_StrmAudioListSize; j++)
    if (m_StrmAudioList[j] != NULL) {
      mem_free(m_StrmAudioList[j]);
      m_StrmAudioList[j] = NULL;
    }
  m_StrmAudioListSize = 0;

  // Clear the Message Name list
  for (j = 0; j < m_MessageNameListSize; j++)
    if (m_MessageNameList[j] != NULL) {
      mem_free(m_MessageNameList[j]);
      m_MessageNameList[j] = NULL;
    }
  m_MessageNameListSize = 0;
}

// Search the tree, and fill all of the name lists
// Returns a count of all invalid name fields encountered
int CDallasMainDlg::FillNameListsFromTree(HTREEITEM parent, bool show_notspec_warnings) {
  HTREEITEM child;
  int inv_name_count;

  if (parent == NULL)
    return 0;

  // Search the tree for named things
  inv_name_count = 0;
  child = m_ScriptTree.GetChildItem(parent);
  while (child != NULL) {
    inv_name_count += FillNameListsFromTree(child, show_notspec_warnings);
    inv_name_count += AddNameToListFromTreeNode(child, show_notspec_warnings);
    child = m_ScriptTree.GetNextSiblingItem(child);
  }

  return (inv_name_count);
}

// Checks to see if the node contains a named thing,
// and, if it does, adds it to the appropriate name list
// It returns 1 if an invalid name is found, 0 otherwise
int CDallasMainDlg::AddNameToListFromTreeNode(HTREEITEM node, bool show_notspec_warnings) {
  tTreeNodeData *data;
  int scriptID;

  if (node == NULL)
    return 0;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return 0;

  // Make sure this node isn't in the clipboard
  HTREEITEM script_header_node;
  script_header_node = GetParentNodeOfType(node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return 0;
  if (m_ScriptTree.GetParentItem(script_header_node) != NULL)
    return 0;

  // Get the script ID
  scriptID = GetScriptID(node);
  if (scriptID == -1)
    return 0;

  // See if it's an Owner Node
  if (data->type == SCRIPT_OWNER_NODE) {
    if (data->ID == NOT_SPECIFIED_TYPE) {
      if (show_notspec_warnings)
        IndValNotSpecMsg(scriptID, "Script Owner");
      return 1;
    }
    if (data->ID == LEVEL_TYPE)
      return 0;
    if (data->ID == OBJECT_TYPE) {
      // Check for object None
      if (data->int_val == OBJECT_HANDLE_NONE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Script Owner (Object)");
        return 1;
      }

      // Check for invalid objects
      object *objp = ObjGet(data->int_val);
      if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
        int handle = osipf_FindObjectName(data->str_val);
        if (handle != OBJECT_HANDLE_NONE) {
          if (InvObjPrompt(scriptID, data->int_val, data->str_val, handle) == IDYES) {
            data->int_val = handle;
            UpdateAllParentNodesText(node);
            AddObjectToList(data->str_val);
            return 0;
          }
        }
        InvObjMsg(scriptID, data->int_val, data->str_val);
        data->int_val = OBJECT_HANDLE_NONE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid object names
      if (strcmp(data->str_val, objp->name) != 0) {
        int handle = osipf_FindObjectName(data->str_val);
        if (handle != OBJECT_HANDLE_NONE) {
          if (InvNameObjPrompt(scriptID, data->int_val, data->str_val, objp->name, handle) == IDYES) {
            data->int_val = handle;
            UpdateAllParentNodesText(node);
            AddObjectToList(data->str_val);
            return 0;
          }
        }
        InvNameObjMsg(scriptID, data->int_val, data->str_val, objp->name);
        strcpy(data->str_val, objp->name);
        UpdateAllParentNodesText(node);
        AddObjectToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddObjectToList(objp->name);
      return 0;
    }
    if (data->ID == TRIGGER_TYPE) {
      // Check for not specified triggers
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Script Owner (Trigger)");
        return 1;
      }

      // Check for invalid triggers
      int t = data->int_val;
      if (t < 0 || t >= Num_triggers || t >= MAX_NAMED_TRIGGERS || strlen(Triggers[t].name) == 0) {
        int index = osipf_FindTriggerName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Trigger", t, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddTriggerToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Trigger", t, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid trigger names
      if (strcmp(data->str_val, Triggers[t].name) != 0) {
        int index = osipf_FindTriggerName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Trigger", t, data->str_val, Triggers[t].name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddTriggerToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Trigger", t, data->str_val, Triggers[t].name);
        strcpy(data->str_val, Triggers[t].name);
        UpdateAllParentNodesText(node);
        AddTriggerToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddTriggerToList(Triggers[t].name);
      return 0;
    }
  }

  // See if it's a parameter Node
  if (data->type == PARAMETER_NODE) {
    switch (data->ID) {
    case DOOR_PARAMETER_TYPE: {
      // Check for ME handle
      if (data->subID == USE_ME_HANDLE) {
        if (ScriptHasADoorMe(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "an OWNER (Door object)");
          return 1;
        }
      }

      // Check for IT handle
      if (data->subID == USE_IT_HANDLE)
        return 0;

      // Check for object None
      if (data->int_val == OBJECT_HANDLE_NONE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Door Object");
        return 1;
      }

      // Check for invalid door objects
      object *objp = ObjGet(data->int_val);
      if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
        int handle = osipf_FindDoorName(data->str_val);
        if (handle != OBJECT_HANDLE_NONE) {
          if (InvObjPrompt(scriptID, data->int_val, data->str_val, handle) == IDYES) {
            data->int_val = handle;
            UpdateAllParentNodesText(node);
            AddObjectToList(data->str_val);
            return 0;
          }
        }
        InvObjMsg(scriptID, data->int_val, data->str_val);
        data->int_val = OBJECT_HANDLE_NONE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid door object names
      if (strcmp(data->str_val, objp->name) != 0) {
        int handle = osipf_FindDoorName(data->str_val);
        if (handle != OBJECT_HANDLE_NONE) {
          if (InvNameObjPrompt(scriptID, data->int_val, data->str_val, objp->name, handle) == IDYES) {
            data->int_val = handle;
            UpdateAllParentNodesText(node);
            AddObjectToList(data->str_val);
            return 0;
          }
        }
        InvNameObjMsg(scriptID, data->int_val, data->str_val, objp->name);
        strcpy(data->str_val, objp->name);
        UpdateAllParentNodesText(node);
        AddObjectToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddDoorToList(objp->name);
    } break;
    case OBJECT_PARAMETER_TYPE: {
      // Check for ME and IT handles
      if (data->subID == USE_ME_HANDLE) {
        if (ScriptHasAMe(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "an OWNER (object)");
          return 1;
        }
      }

      if (data->subID == USE_IT_HANDLE) {
        if (ScriptHasAnIt(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "an IT (object)");
          return 1;
        }
      }

      // Check for object None
      if (data->int_val == OBJECT_HANDLE_NONE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Generic Object");
        return 1;
      }

      // Check for invalid objects
      object *objp = ObjGet(data->int_val);
      if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
        int handle = osipf_FindObjectName(data->str_val);
        if (handle != OBJECT_HANDLE_NONE) {
          if (InvObjPrompt(scriptID, data->int_val, data->str_val, handle) == IDYES) {
            data->int_val = handle;
            UpdateAllParentNodesText(node);
            AddObjectToList(data->str_val);
            return 0;
          }
        }
        InvObjMsg(scriptID, data->int_val, data->str_val);
        data->int_val = OBJECT_HANDLE_NONE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid object names
      if (strcmp(data->str_val, objp->name) != 0) {
        int handle = osipf_FindObjectName(data->str_val);
        if (handle != OBJECT_HANDLE_NONE) {
          if (InvNameObjPrompt(scriptID, data->int_val, data->str_val, objp->name, handle) == IDYES) {
            data->int_val = handle;
            UpdateAllParentNodesText(node);
            AddObjectToList(data->str_val);
            return 0;
          }
        }
        InvNameObjMsg(scriptID, data->int_val, data->str_val, objp->name);
        strcpy(data->str_val, objp->name);
        UpdateAllParentNodesText(node);
        AddObjectToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddObjectToList(objp->name);
    } break;
    case ROOM_PARAMETER_TYPE: {
      // Check for not specified rooms
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Room");
        return 1;
      }

      // Check for invalid rooms
      int r = data->int_val;
      if (r < 0 || r > Highest_room_index || !Rooms[r].used || Rooms[r].name == NULL) {
        int index = osipf_FindRoomName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Room", r, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddRoomToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Room", r, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid room names
      if (strcmp(data->str_val, Rooms[r].name) != 0) {
        int index = osipf_FindRoomName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Room", r, data->str_val, Rooms[r].name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddRoomToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Room", r, data->str_val, Rooms[r].name);
        strcpy(data->str_val, Rooms[r].name);
        UpdateAllParentNodesText(node);
        AddRoomToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddRoomToList(Rooms[r].name);
    } break;
    case TRIGGER_PARAMETER_TYPE: {
      // Check for not specified triggers
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Trigger");
        return 1;
      }

      // Check for invalid triggers
      int t = data->int_val;
      if (t < 0 || t >= Num_triggers || t >= MAX_NAMED_TRIGGERS || strlen(Triggers[t].name) == 0) {
        int index = osipf_FindTriggerName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Trigger", t, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddTriggerToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Trigger", t, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid trigger names
      if (strcmp(data->str_val, Triggers[t].name) != 0) {
        int index = osipf_FindTriggerName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Trigger", t, data->str_val, Triggers[t].name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddTriggerToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Trigger", t, data->str_val, Triggers[t].name);
        strcpy(data->str_val, Triggers[t].name);
        UpdateAllParentNodesText(node);
        AddTriggerToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddTriggerToList(Triggers[t].name);
    } break;
    case SOUND_PARAMETER_TYPE: {
      // Check for not specified sounds
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Sound");
        return 1;
      }

      // Check for invalid sounds
      int s = data->int_val;
      if (s < 0 || s >= MAX_SOUNDS || !Sounds[s].used) {
        int index = osipf_FindSoundName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Sound", s, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddSoundToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Sound", s, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid sound names
      if (strcmp(data->str_val, Sounds[s].name) != 0) {
        int index = osipf_FindSoundName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Sound", s, data->str_val, Sounds[s].name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddSoundToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Sound", s, data->str_val, Sounds[s].name);
        strcpy(data->str_val, Sounds[s].name);
        UpdateAllParentNodesText(node);
        AddSoundToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddSoundToList(Sounds[s].name);
    } break;
    case TEXTURE_PARAMETER_TYPE: {
      // Check for not specified textures
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Texture");
        return 1;
      }

      // Check for invalid textures
      int t = data->int_val;
      if (t < 0 || t >= MAX_TEXTURES || !GameTextures[t].used) {
        int index = osipf_FindTextureName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Texture", t, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddTextureToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Texture", t, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid texture names
      if (strcmp(data->str_val, GameTextures[t].name) != 0) {
        int index = osipf_FindTextureName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Texture", t, data->str_val, GameTextures[t].name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddTextureToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Texture", t, data->str_val, GameTextures[t].name);
        strcpy(data->str_val, GameTextures[t].name);
        UpdateAllParentNodesText(node);
        AddTextureToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddTextureToList(GameTextures[t].name);
    } break;
    case PATH_PARAMETER_TYPE: {
      // Check for not specified paths
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Path");
        return 1;
      }

      // Check for invalid paths
      int t = data->int_val;
      if (t < 0 || t >= MAX_GAME_PATHS || !GamePaths[t].used) {
        int index = osipf_FindPathName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Path", t, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddPathToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Path", t, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid path names
      if (strcmp(data->str_val, GamePaths[t].name) != 0) {
        int index = osipf_FindPathName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Path", t, data->str_val, GamePaths[t].name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddPathToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Path", t, data->str_val, GamePaths[t].name);
        strcpy(data->str_val, GamePaths[t].name);
        UpdateAllParentNodesText(node);
        AddPathToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddPathToList(GamePaths[t].name);
    } break;
    case MATCEN_PARAMETER_TYPE: {
      // Check for MATCEN ID
      if (data->subID == USE_MATCEN_EVENT_ID) {
        if (ScriptHasAMatcenID(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "a MATCEN ID (Matcen type)");
          return 1;
        }
      }

      // Check for not specified matcens
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Matcen");
        return 1;
      }

      // Check for invalid matcens
      int t = data->int_val;
      if (!MatcenValid(t)) {
        int index = osipf_FindMatcenName(data->str_val);
        if (index >= 0) {
          if (InvIndValPrompt(scriptID, "Matcen", t, data->str_val, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddMatcenToList(data->str_val);
            return 0;
          }
        }
        InvIndValMsg(scriptID, "Matcen", t, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // Check for invalid matcen names
      char matcen_name[MAX_MATCEN_NAME_LEN + 1];
      Matcen[t]->GetName(matcen_name);
      if (strcmp(data->str_val, matcen_name) != 0) {
        int index = osipf_FindMatcenName(data->str_val);
        if (index >= 0) {
          if (InvNameIndValPrompt(scriptID, "Matcen", t, data->str_val, matcen_name, index) == IDYES) {
            data->int_val = index;
            UpdateAllParentNodesText(node);
            AddMatcenToList(data->str_val);
            return 0;
          }
        }
        InvNameIndValMsg(scriptID, "Matcen", t, data->str_val, matcen_name);
        strcpy(data->str_val, matcen_name);
        UpdateAllParentNodesText(node);
        AddMatcenToList(data->str_val);
        return 0;
      }

      // All is cool, so just add the name
      AddMatcenToList(matcen_name);
    } break;
    case LEVEL_GOAL_PARAMETER_TYPE: {
      // Check for LEVEL GOAL ID
      if (data->subID == USE_LEVEL_GOAL_ID) {
        if (ScriptHasALevelGoalID(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "a LEVEL GOAL ID (Level Goal type)");
          return 1;
        }
      }

      // Check for not specified level goals
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Level Goal");
        return 1;
      }

      // Check for invalid level goals
      int t = osipf_FindLevelGoalName(data->str_val);
      if (t < 0) {
        InvIndValMsg(scriptID, "Level Goal", t, data->str_val);
        data->int_val = NOT_SPECIFIED_TYPE;
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }
      data->int_val = t;

      // All is cool, so just add the name
      AddGoalToList(data->str_val);
    } break;
    case STRM_AUDIO_PARAMETER_TYPE: {
      // Check for not specified streaming audio filenames
      if (strlen(data->str_val) == 0) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Streaming Audio File");
        return 1;
      }

      // Check if filename is invalid
      if (!GamefileExists(data->str_val)) {
        InvIndValMsg(scriptID, "Streaming Audio File", 0, data->str_val);
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // All is cool, so just add the name
      AddStrmAudioToList(data->str_val);
    } break;
    case SPECNAME_PARAMETER_TYPE: {
      // Check for not specified special names
      if (strlen(data->str_val) == 0) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Specific Name");
        return 1;
      }

      // All is cool, so just add the name
      AddSpecnameToList(data->str_val);
    } break;
    case STRING_PARAMETER_TYPE: {
      // Check for not specified messages
      if (strlen(data->str_val) == 0) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Message ID");
        return 1;
      }

      // Check if message name is invalid
      if (FindMessageInList(data->str_val) == NULL) {
        InvIndValMsg(scriptID, "Message ID", 0, data->str_val);
        strcpy(data->str_val, "");
        UpdateAllParentNodesText(node);
        return 1;
      }

      // All is cool, so just add the message name
      AddMessageNameToList(data->str_val);
    } break;
    case ENUM_PARAMETER_TYPE: {
      // Check for GOAL ID and TIMER ID handles
      if (data->subID == USE_GOALID_VALUE) {
        if (ScriptHasAGoalID(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "a GOAL ID (Enumerated type:GoalID)");
          return 1;
        }
      }

      if (data->subID == USE_TIMERID_VALUE) {
        if (ScriptHasATimerID(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "a TIMER ID (Enumerated type:TimerID)");
          return 1;
        }
      }

      if (data->subID == USE_MATCENID_VALUE) {
        if (ScriptHasAMatcenID(node)) {
          return 0;
        } else {
          InvSpecParamMsg(scriptID, "a MATCEN ID (Enumerated type:MatcenID)");
          return 1;
        }
      }

      // Check for invalid enums
      if (GetEnumValueName(data->name, data->int_val) == NULL) {
        IndValNotSpecMsg(scriptID, "Enumerated Type");
        UpdateAllParentNodesText(node);
        return 1;
      }
    } break;
    case SCRIPT_PARAMETER_TYPE: {
      // Check for NOT SPECIFIED script ID's
      if (data->int_val == NOT_SPECIFIED_TYPE) {
        if (show_notspec_warnings)
          IndValNotSpecMsg(scriptID, "Script ID");
        return 1;
      }

      // Check for invalid script ID's
      if (FindScriptIDNode(data->int_val) == NULL) {
        InvIndValMsg(scriptID, "Script ID", data->int_val, "Unknown");
        data->int_val = NOT_SPECIFIED_TYPE;
        UpdateAllParentNodesText(node);
        return 1;
      }
    } break;
    }
    return 0;
  }

  return 0;
}

// Displays the invalid special parameter warning message
void CDallasMainDlg::InvSpecParamMsg(int scriptID, char *type_name) {
  CString msg, title;

  if (type_name == NULL)
    return;

  msg.Format("WARNING: Script #%d references %s even though its selected event (or owner) type does not support one.",
             scriptID, type_name);
  title.Format("Invalid Special Parameter Warning!");
  MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
}

// Displays the NOT SPECIFIED indexed value warning message
void CDallasMainDlg::IndValNotSpecMsg(int scriptID, char *type_name) {
  CString msg, title;

  if (type_name == NULL)
    return;

  msg.Format("WARNING: Script #%d references a %s which has not been specified.", scriptID, type_name);
  title.Format("%s Not Specified Warning!", type_name);
  MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
}

// Displays the invalid indexed value warning message
void CDallasMainDlg::InvIndValMsg(int scriptID, char *type_name, int index, char *name) {
  CString msg, title;

  if (type_name == NULL || name == NULL)
    return;

  msg.Format("WARNING: Script #%d references a %s (index=%d, name=%s) that no longer exists.  It will be changed to "
             "NOT SPECIFIED.",
             scriptID, type_name, index, name);
  title.Format("Invalid %s Warning!", type_name);
  MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
}

// Displays the invalid indexed value prompt
int CDallasMainDlg::InvIndValPrompt(int scriptID, char *type_name, int index, char *name, int new_index) {
  CString msg, title;

  if (type_name == NULL || name == NULL)
    return (IDNO);

  msg.Format("WARNING: Script #%d references a %s (index=%d, name=%s) that no longer exists.  However, another %s "
             "(index=%d) exists with the same name.\n\nDo you want to use this other one instead?",
             scriptID, type_name, index, name, type_name, new_index);
  title.Format("Invalid %s Warning!", type_name);
  return (MessageBox(msg, title, MB_YESNO | MB_ICONEXCLAMATION));
}

// Displays the invalid indexed value name warning message
void CDallasMainDlg::InvNameIndValMsg(int scriptID, char *type_name, int index, char *name, char *new_name) {
  CString msg, title;

  if (type_name == NULL || name == NULL || new_name == NULL)
    return;

  msg.Format("WARNING: Script #%d references a %s (index=%d, name=%s) whose name has changed to \"%s\".  Its name will "
             "be updated.",
             scriptID, type_name, index, name, new_name);
  title.Format("Invalid %s Name Warning!", type_name);
  MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
}

// Displays the invalid indexed value name prompt
int CDallasMainDlg::InvNameIndValPrompt(int scriptID, char *type_name, int index, char *name, char *new_name,
                                        int new_index) {
  CString msg, title;

  if (type_name == NULL || name == NULL || new_name == NULL)
    return (IDNO);

  msg.Format("WARNING: Script #%d references a %s (index=%d, name=%s) whose name has changed to \"%s\".  However, "
             "another %s (index=%d) exists with the old name.\n\nDo you want to use this other one instead?",
             scriptID, type_name, index, name, new_name, type_name, new_index);
  title.Format("Invalid %s Name Warning!", type_name);
  return (MessageBox(msg, title, MB_YESNO | MB_ICONEXCLAMATION));
}

// Displays the invalid Object warning message
void CDallasMainDlg::InvObjMsg(int scriptID, int handle, char *name) {
  CString msg, title;

  if (name == NULL)
    return;

  msg.Format("WARNING: Script #%d references an Object (handle=%d, name=%s) that no longer exists.  It will be changed "
             "to Object NONE.",
             scriptID, handle, name);
  title.Format("Invalid Object Warning!");
  MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
}

// Displays the invalid Object prompt
int CDallasMainDlg::InvObjPrompt(int scriptID, int handle, char *name, int new_handle) {
  CString msg, title;

  if (name == NULL)
    return (IDNO);

  msg.Format("WARNING: Script #%d references an Object (handle=%d, name=%s) that no longer exists.  However, another "
             "object (handle=%d) exists with the same name.\n\nDo you want to use this other one instead?",
             scriptID, handle, name, new_handle);
  title.Format("Invalid Object Warning!");
  return (MessageBox(msg, title, MB_YESNO | MB_ICONEXCLAMATION));
}

// Displays the invalid object name warning message
void CDallasMainDlg::InvNameObjMsg(int scriptID, int handle, char *name, char *new_name) {
  CString msg, title;

  if (name == NULL || new_name == NULL)
    return;

  msg.Format("WARNING: Script #%d references an Object (handle=%d, name=%s) whose name has changed to \"%s\".  Its "
             "name will be updated.",
             scriptID, handle, name, new_name);
  title.Format("Invalid Object Name Warning!");
  MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
}

// Displays the invalid object name prompt
int CDallasMainDlg::InvNameObjPrompt(int scriptID, int handle, char *name, char *new_name, int new_handle) {
  CString msg, title;

  if (name == NULL || new_name == NULL)
    return (IDNO);

  msg.Format(
      "WARNING: Script #%d references an Object (handle=%d, name=%s) whose name has changed to \"%s\".  However, "
      "another object (handle=%d) exists with the old name.\n\nDo you want to use this other one instead?",
      scriptID, handle, name, new_name, new_handle);
  title.Format("Invalid Object Name Warning!");
  return (MessageBox(msg, title, MB_YESNO | MB_ICONEXCLAMATION));
}

// Adds the given door name to the door name list
int CDallasMainDlg::AddDoorToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindDoorInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_DoorListSize >= MAX_NAMED_DOORS)
    return FALSE;

  int pos = m_DoorListSize;
  m_DoorList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_DoorList[pos] == NULL) {
    MessageBox("Out of memory in AddDoorToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_DoorList[pos], name);
  m_DoorListSize++;

  return TRUE;
}

// Returns the list index of the given door name (or -1 if not found)
int CDallasMainDlg::FindDoorInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_DoorListSize; j++)
    if (strcmp(m_DoorList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given object name to the object name list
int CDallasMainDlg::AddObjectToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindObjectInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_ObjectListSize >= MAX_NAMED_OBJECTS)
    return FALSE;

  int pos = m_ObjectListSize;
  m_ObjectList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_ObjectList[pos] == NULL) {
    MessageBox("Out of memory in AddObjectToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_ObjectList[pos], name);
  m_ObjectListSize++;

  return TRUE;
}

// Returns the list index of the given object name (or -1 if not found)
int CDallasMainDlg::FindObjectInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_ObjectListSize; j++)
    if (strcmp(m_ObjectList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Room name to the Room name list
int CDallasMainDlg::AddRoomToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindRoomInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_RoomListSize >= MAX_NAMED_ROOMS)
    return FALSE;

  int pos = m_RoomListSize;
  m_RoomList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_RoomList[pos] == NULL) {
    MessageBox("Out of memory in AddRoomToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_RoomList[pos], name);
  m_RoomListSize++;

  return TRUE;
}

// Returns the list index of the given room name (or -1 if not found)
int CDallasMainDlg::FindRoomInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_RoomListSize; j++)
    if (strcmp(m_RoomList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Trigger name to the Trigger name list
int CDallasMainDlg::AddTriggerToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindTriggerInList(name) >= 0)
    return TRUE;

  // If there's Trigger in the list, add the new name
  if (m_TriggerListSize >= MAX_NAMED_TRIGGERS)
    return FALSE;

  int pos = m_TriggerListSize;
  m_TriggerList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_TriggerList[pos] == NULL) {
    MessageBox("Out of memory in AddTriggerToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_TriggerList[pos], name);
  m_TriggerListSize++;

  return TRUE;
}

// Returns the list index of the given Trigger name (or -1 if not found)
int CDallasMainDlg::FindTriggerInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_TriggerListSize; j++)
    if (strcmp(m_TriggerList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given sound name to the sound name list
int CDallasMainDlg::AddSoundToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindSoundInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_SoundListSize >= MAX_NAMED_SOUNDS)
    return FALSE;

  int pos = m_SoundListSize;
  m_SoundList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_SoundList[pos] == NULL) {
    MessageBox("Out of memory in AddSoundToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_SoundList[pos], name);
  m_SoundListSize++;

  return TRUE;
}

// Returns the list index of the given sound name (or -1 if not found)
int CDallasMainDlg::FindSoundInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_SoundListSize; j++)
    if (strcmp(m_SoundList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Texture name to the Texture name list
int CDallasMainDlg::AddTextureToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindTextureInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_TextureListSize >= MAX_NAMED_TEXTURES)
    return FALSE;

  int pos = m_TextureListSize;
  m_TextureList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_TextureList[pos] == NULL) {
    MessageBox("Out of memory in AddTextureToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_TextureList[pos], name);
  m_TextureListSize++;

  return TRUE;
}

// Returns the list index of the given Texture name (or -1 if not found)
int CDallasMainDlg::FindTextureInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_TextureListSize; j++)
    if (strcmp(m_TextureList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Specname name to the Specname name list
int CDallasMainDlg::AddSpecnameToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindSpecnameInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_SpecnameListSize >= MAX_SPECNAMES)
    return FALSE;

  int pos = m_SpecnameListSize;
  m_SpecnameList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_SpecnameList[pos] == NULL) {
    MessageBox("Out of memory in AddSpecnameToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_SpecnameList[pos], name);
  m_SpecnameListSize++;

  return TRUE;
}

// Returns the list index of the given Specname name (or -1 if not found)
int CDallasMainDlg::FindSpecnameInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_SpecnameListSize; j++)
    if (strcmp(m_SpecnameList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Path name to the Path name list
int CDallasMainDlg::AddPathToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindPathInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_PathListSize >= MAX_NAMED_PATHS)
    return FALSE;

  int pos = m_PathListSize;
  m_PathList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_PathList[pos] == NULL) {
    MessageBox("Out of memory in AddPathToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_PathList[pos], name);
  m_PathListSize++;

  return TRUE;
}

// Returns the list index of the given Path name (or -1 if not found)
int CDallasMainDlg::FindPathInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_PathListSize; j++)
    if (strcmp(m_PathList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Matcen name to the Matcen name list
int CDallasMainDlg::AddMatcenToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindMatcenInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_MatcenListSize >= MAX_NAMED_MATCENS)
    return FALSE;

  int pos = m_MatcenListSize;
  m_MatcenList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_MatcenList[pos] == NULL) {
    MessageBox("Out of memory in AddMatcenToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_MatcenList[pos], name);
  m_MatcenListSize++;

  return TRUE;
}

// Returns the list index of the given Matcen name (or -1 if not found)
int CDallasMainDlg::FindMatcenInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_MatcenListSize; j++)
    if (strcmp(m_MatcenList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Goal name to the Goal name list
int CDallasMainDlg::AddGoalToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindGoalInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_GoalListSize >= MAX_NAMED_GOALS)
    return FALSE;

  int pos = m_GoalListSize;
  m_GoalList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_GoalList[pos] == NULL) {
    MessageBox("Out of memory in AddGoalToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_GoalList[pos], name);
  m_GoalListSize++;

  return TRUE;
}

// Returns the list index of the given Goal name (or -1 if not found)
int CDallasMainDlg::FindGoalInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_GoalListSize; j++)
    if (strcmp(m_GoalList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given StrmAudio name to the StrmAudio name list
int CDallasMainDlg::AddStrmAudioToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindStrmAudioInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_StrmAudioListSize >= MAX_NAMED_STRM_AUDIO)
    return FALSE;

  int pos = m_StrmAudioListSize;
  m_StrmAudioList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_StrmAudioList[pos] == NULL) {
    MessageBox("Out of memory in AddStrmAudioToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_StrmAudioList[pos], name);
  m_StrmAudioListSize++;

  return TRUE;
}

// Returns the list index of the given StrmAudio name (or -1 if not found)
int CDallasMainDlg::FindStrmAudioInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_StrmAudioListSize; j++)
    if (strcmp(m_StrmAudioList[j], name) == 0)
      return (j);

  return (-1);
}

// Adds the given Message name to the Message name list
int CDallasMainDlg::AddMessageNameToList(char *name) {
  // Make sure we've got a name
  if (name == NULL || strlen(name) == 0)
    return FALSE;

  // See if it's already in the list
  if (FindMessageNameInList(name) >= 0)
    return TRUE;

  // If there's room in the list, add the new name
  if (m_MessageNameListSize >= MAX_MESSAGE_LIST_ENTRIES)
    return FALSE;

  int pos = m_MessageNameListSize;
  m_MessageNameList[pos] = (char *)mem_malloc(strlen(name) + 1);
  if (m_MessageNameList[pos] == NULL) {
    MessageBox("Out of memory in AddMessageNameToList()!", "Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  strcpy(m_MessageNameList[pos], name);
  m_MessageNameListSize++;

  return TRUE;
}

// Returns the list index of the given MessageName name (or -1 if not found)
int CDallasMainDlg::FindMessageNameInList(char *name) {
  if (name == NULL)
    return (-1);

  for (int j = 0; j < m_MessageNameListSize; j++)
    if (strcmp(m_MessageNameList[j], name) == 0)
      return (j);

  return (-1);
}

/////////////////////////////////////////////////////////////////////////////
// User Type Workshop Functions
/////////////////////////////////////////////////////////////////////////////

// Fills drop down box with available user types
int CDallasMainDlg::FillUserTypeBox(CComboBox *box) {
  int j, types_added;

  types_added = 0;

  // Clear the box
  box->ResetContent();

  // Add the User Type Names
  for (j = 0; j < m_NumEnums; j++) {
    if (m_EnumDatabase[j].is_user_type) {
      box->AddString(m_EnumDatabase[j].name);
      types_added++;
    }
  }

  // Select the first one
  box->SetCurSel(0);

  return (types_added);
}

// Fills the box with all values for the given User Type
int CDallasMainDlg::FillValuesBox(CListBox *box, char *utype_name) {
  int j, DBslot, values_added;

  values_added = 0;

  // Clear the box
  box->ResetContent();

  // Fill in the values
  DBslot = GetEnumID(utype_name);
  if (DBslot == INVALID_ENUM)
    return (values_added);

  for (j = 0; j < m_EnumDatabase[DBslot].num_values; j++) {
    tEnumValueEntry *value_entry = &m_EnumDatabase[DBslot].values[j];
    if (value_entry->value != -1) {
      box->AddString(value_entry->name);
      values_added++;
    }
  }

  // Select the first one
  box->SetCurSel(0);

  return (values_added);
}

// Adds a value to the user type
// Returns the new position in list, or -1 if add failed
int CDallasMainDlg::AddUserTypeValue(char *utype_name, char *value_name) {
  int j, k, DBslot, new_value;

  if (utype_name == NULL || value_name == NULL)
    return (-1);

  new_value = -1;

  DBslot = GetEnumID(utype_name);
  if (DBslot == INVALID_ENUM)
    return (-1);

  tEnumDBEntry *entry = &m_EnumDatabase[DBslot];
  if (entry->num_values >= (entry->max_values + 2) || entry->num_values >= MAX_ENUM_VALUES)
    return (-1);

  // Find a place to insert the new value
  new_value = 0;
  for (j = 0; j < entry->num_values; j++) {
    tEnumValueEntry *value_entry = &entry->values[j];
    if (new_value < value_entry->value) {
      // Bump the higher ones down the list
      for (k = entry->num_values; k > j; k--) {
        entry->values[k].value = entry->values[k - 1].value;
        entry->values[k].name = entry->values[k - 1].name;
      }
      break;
    }
    new_value = value_entry->value + 1;
  }

  // Store the new value at the current position
  tEnumValueEntry *value_entry = &entry->values[j];
  value_entry->value = new_value;
  value_entry->name = (char *)mem_malloc(strlen(value_name) + 1);
  if (value_entry->name == NULL) {
    MessageBox("ERROR: Out of mem in AddUserTypeValue()!", "Error!");
    return (-1);
  }
  strcpy(value_entry->name, value_name);

  entry->num_values++;

  SetModified(TRUE);

  return (j);
}

// Removes a value
int CDallasMainDlg::DeleteUserTypeValue(char *utype_name, char *value_name) {
  int j, k, DBslot;

  if (utype_name == NULL || value_name == NULL)
    return FALSE;

  DBslot = GetEnumID(utype_name);
  if (DBslot == INVALID_ENUM)
    return FALSE;

  tEnumDBEntry *entry = &m_EnumDatabase[DBslot];

  // Find the value name in the list
  for (j = 0; j < entry->num_values; j++) {
    tEnumValueEntry *value_entry = &entry->values[j];
    if (strcmp(value_name, value_entry->name) == 0) {
      // Free the name memory
      mem_free(value_entry->name);

      // Compact the list
      entry->num_values--;
      for (k = j; k < (entry->num_values); k++) {
        entry->values[k].value = entry->values[k + 1].value;
        entry->values[k].name = entry->values[k + 1].name;
      }
      entry->values[k].name = NULL;
      SetModified(TRUE);
      return TRUE;
    }
  }

  return FALSE;
}

// Changes the name of a value
int CDallasMainDlg::ChangeValueName(char *utype_name, char *old_name, char *new_name) {
  int j, DBslot;

  if (utype_name == NULL || old_name == NULL || new_name == NULL)
    return FALSE;

  DBslot = GetEnumID(utype_name);
  if (DBslot == INVALID_ENUM)
    return FALSE;

  tEnumDBEntry *entry = &m_EnumDatabase[DBslot];

  // Find the value name in the list
  for (j = 0; j < entry->num_values; j++) {
    tEnumValueEntry *value_entry = &entry->values[j];
    if (strcmp(old_name, value_entry->name) == 0) {
      // Free the name memory
      mem_free(value_entry->name);

      // Add the new name
      value_entry->name = (char *)mem_malloc(strlen(new_name) + 1);
      if (value_entry->name == NULL) {
        MessageBox("ERROR: Out of mem in ChangeValueName()!", "Error!");
        return FALSE;
      }
      strcpy(value_entry->name, new_name);
      SetModified(TRUE);

      return TRUE;
    }
  }

  return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Enumeration Database Functions
/////////////////////////////////////////////////////////////////////////////

// Initializes the enum DB for use
void CDallasMainDlg::InitEnumDatabase(void) {
  int j, k;

  for (j = 0; j < MAX_ENUMS; j++) {
    m_EnumDatabase[j].name = NULL;
    for (k = 0; k < MAX_ENUM_VALUES; k++) {
      m_EnumDatabase[j].values[k].name = NULL;
      m_EnumDatabase[j].values[k].value = 0;
    }
    m_EnumDatabase[j].num_values = 0;
  }
  m_NumEnums = 0;
}

// Clears any allocated data for the enums
void CDallasMainDlg::ClearEnumDatabase(void) {
  int j, k;

  for (j = 0; j < m_NumEnums; j++) {
    if (m_EnumDatabase[j].name != NULL) {
      mem_free(m_EnumDatabase[j].name);
      m_EnumDatabase[j].name = NULL;
    }
    for (k = 0; k < m_EnumDatabase[j].num_values; k++) {
      if (m_EnumDatabase[j].values[k].name != NULL) {
        mem_free(m_EnumDatabase[j].values[k].name);
        m_EnumDatabase[j].values[k].name = NULL;
      }
      m_EnumDatabase[j].values[k].value = 0;
    }
    m_EnumDatabase[j].num_values = 0;
  }
  m_NumEnums = 0;
}

// Returns the DB slot matching the given enum type name
int CDallasMainDlg::GetEnumID(char *name) {
  int i;

  if (name == NULL)
    return INVALID_ENUM;

  for (i = 0; i < m_NumEnums; i++)
    if (strcmp(m_EnumDatabase[i].name, name) == 0)
      return i;

  return INVALID_ENUM;
}

// Returns the name bound to an enum value
char *CDallasMainDlg::GetEnumValueName(char *name, int value) {
  int DBslot, j;

  DBslot = GetEnumID(name);
  if (DBslot == INVALID_ENUM)
    return NULL;

  for (j = 0; j < m_EnumDatabase[DBslot].num_values; j++)
    if (m_EnumDatabase[DBslot].values[j].value == value)
      return (m_EnumDatabase[DBslot].values[j].name);

  return NULL;
}

// Obtains the value bound to an enum value name,
// Returns TRUE if value was found, FALSE otherwise
bool CDallasMainDlg::GetEnumValue(char *name, char *value_name, int &value) {
  int DBslot, j;

  DBslot = GetEnumID(name);
  if (DBslot == INVALID_ENUM)
    return FALSE;

  for (j = 0; j < m_EnumDatabase[DBslot].num_values; j++)
    if (strcmp(m_EnumDatabase[DBslot].values[j].name, value_name) == 0) {
      value = m_EnumDatabase[DBslot].values[j].value;
      return TRUE;
    }

  return FALSE;
}

// Fills up the given menu with the available enumeration types
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillEnumTypesMenu(CMenu *enum_menu, int command_offset, char *valid_name) {
  CString name;
  int enum_types_added;
  int i;

  // Set the counts
  enum_types_added = 0;

  // Fill the menu with names of matching enumeration values
  for (i = 0; i < m_NumEnums; i++) {
    name = m_EnumDatabase[i].name;
    if (m_EnumDatabase[i].is_user_type)
      name += "  (USER TYPE)";
    if (strlen(valid_name) == 0 || strcmp(valid_name, m_EnumDatabase[i].name) == 0) {
      enum_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + i, name.GetBuffer(0));
      enum_types_added++;
    } else
      enum_menu->AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, command_offset + i, name.GetBuffer(0));
  }

  return (enum_types_added);
}

// Fills up the given menu with the enumeration values of the given enum name
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillEnumValuesMenu(CMenu *enum_menu, int command_offset, char *enum_name) {
  int enum_values_added;
  int i, DBslot;
  tEnumDBEntry *enum_entry;

  // Set the counts
  enum_values_added = 0;

  // Find the correct enum database entry
  DBslot = GetEnumID(enum_name);
  if (DBslot == INVALID_ENUM)
    return 0;

  enum_entry = &m_EnumDatabase[DBslot];

  // Fill the menu with names of matching enumeration values
  for (i = 0; i < enum_entry->num_values; i++) {
    enum_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + i, enum_entry->values[i].name);
    enum_values_added++;
  }

  return (enum_values_added);
}

/////////////////////////////////////////////////////////////////////////////
// Flag Database Functions
/////////////////////////////////////////////////////////////////////////////

// Initializes the Flag DB for use
void CDallasMainDlg::InitFlagDatabase(void) {
  int j, k;

  for (j = 0; j < MAX_FLAGS; j++) {
    m_FlagDatabase[j].name = NULL;
    for (k = 0; k < MAX_FLAG_VALUES; k++) {
      m_FlagDatabase[j].values[k].name = NULL;
      m_FlagDatabase[j].values[k].value = 0;
    }
    m_FlagDatabase[j].num_values = 0;
  }
  m_NumFlags = 0;
}

// Clears any allocated data for the Flags
void CDallasMainDlg::ClearFlagDatabase(void) {
  int j, k;

  for (j = 0; j < m_NumFlags; j++) {
    if (m_FlagDatabase[j].name != NULL) {
      mem_free(m_FlagDatabase[j].name);
      m_FlagDatabase[j].name = NULL;
    }
    for (k = 0; k < m_FlagDatabase[j].num_values; k++) {
      if (m_FlagDatabase[j].values[k].name != NULL) {
        mem_free(m_FlagDatabase[j].values[k].name);
        m_FlagDatabase[j].values[k].name = NULL;
      }
      m_FlagDatabase[j].values[k].value = 0;
    }
    m_FlagDatabase[j].num_values = 0;
  }
  m_NumFlags = 0;
}

// Returns the DB slot matching the given Flag type name
int CDallasMainDlg::GetFlagID(char *name) {
  int i;

  if (name == NULL)
    return INVALID_FLAG;

  for (i = 0; i < m_NumFlags; i++)
    if (strcmp(m_FlagDatabase[i].name, name) == 0)
      return i;

  return INVALID_FLAG;
}

// Returns the name bound to an flag value
char *CDallasMainDlg::GetFlagValueName(char *name, int value) {
  int DBslot, j;

  DBslot = GetFlagID(name);
  if (DBslot == INVALID_FLAG)
    return NULL;

  for (j = 0; j < m_FlagDatabase[DBslot].num_values; j++)
    if (m_FlagDatabase[DBslot].values[j].value == value)
      return (m_FlagDatabase[DBslot].values[j].name);

  return NULL;
}

// Returns the name bound to an Flag value
bool CDallasMainDlg::FormatFlagValueNames(char *name, int value, CString &text) {
  int DBslot, j;
  bool first_added;

  DBslot = GetFlagID(name);
  if (DBslot == INVALID_FLAG)
    return FALSE;

  first_added = TRUE;
  text = "";
  for (j = 0; j < m_FlagDatabase[DBslot].num_values; j++) {
    if (m_FlagDatabase[DBslot].values[j].value & value) {
      if (!first_added)
        text += ",";
      else {
        text += '[';
        first_added = FALSE;
      }
      text += m_FlagDatabase[DBslot].values[j].name;
    }
  }

  if (text.IsEmpty())
    text = "[NO FLAGS SET]";
  else
    text += ']';

  return TRUE;
}

// Obtains the value bound to an Flag value name,
// Returns TRUE if value was found, FALSE otherwise
bool CDallasMainDlg::GetFlagValue(char *name, char *value_name, int &value) {
  int DBslot, j;

  DBslot = GetFlagID(name);
  if (DBslot == INVALID_FLAG)
    return FALSE;

  for (j = 0; j < m_FlagDatabase[DBslot].num_values; j++)
    if (strcmp(m_FlagDatabase[DBslot].values[j].name, value_name) == 0) {
      value = m_FlagDatabase[DBslot].values[j].value;
      return TRUE;
    }

  return FALSE;
}

// Fills up the given menu with the available flag types
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillFlagTypesMenu(CMenu *flag_menu, int command_offset, char *valid_name) {
  int flag_types_added;
  int i;

  // Set the counts
  flag_types_added = 0;

  // Fill the menu with names of matching Flageration values
  for (i = 0; i < m_NumFlags; i++) {
    if (strlen(valid_name) == 0 || strcmp(valid_name, m_FlagDatabase[i].name) == 0) {
      flag_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + i, m_FlagDatabase[i].name);
      flag_types_added++;
    } else
      flag_menu->AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, command_offset + i, m_FlagDatabase[i].name);
  }

  return (flag_types_added);
}

// Fills up the given CCheckListBox with the flag values of the given flag name
int CDallasMainDlg::FillFlagValuesBox(CCheckListBox *box, char *flag_name, int flags_value, int valid_flags_mask) {
  int flag_values_added;
  int i, DBslot;
  tFlagDBEntry *flag_entry;

  // Set the counts
  flag_values_added = 0;

  // Find the correct enum database entry
  DBslot = GetFlagID(flag_name);
  if (DBslot == INVALID_FLAG)
    return 0;

  flag_entry = &m_FlagDatabase[DBslot];

  // Fill the box with names of matching flag values
  for (i = 0; i < flag_entry->num_values; i++) {
    if (valid_flags_mask == 0 || (flag_entry->values[i].value & valid_flags_mask)) {
      int index;
      index = box->AddString(flag_entry->values[i].name);
      if (index != LB_ERR) {
        box->SetItemData(index, flag_entry->values[i].value);
        if (flag_entry->values[i].value & flags_value)
          box->SetCheck(index, 1);
        else
          box->SetCheck(index, 0);

        /* In case you just wanna dim the invalid flags
        if(valid_flags_mask==0 || (flag_entry->values[i].value & valid_flags_mask))
                box->Enable(index,TRUE);
        else
                box->Enable(index,FALSE);
        */
      }
      flag_values_added++;
    }
  }

  return (flag_values_added);
}

/////////////////////////////////////////////////////////////////////////////
// Action and Query Database Functions
/////////////////////////////////////////////////////////////////////////////

// Initialize the Database Arrays
void CDallasMainDlg::InitFunctionDatabases(void) {
  int j;

  for (j = 0; j < MAX_CATEGORIES; j++)
    m_FunctionCategories[j] = NULL;
  m_NumFunctionCategories = 0;

  for (j = 0; j < MAX_ACTIONS; j++) {
    m_ActionDatabase[j].category = INVALID_CATEGORY;
    m_ActionDatabase[j].desc = NULL;
    m_ActionDatabase[j].func = NULL;
    m_ActionDatabase[j].help = NULL;
  }
  m_NumActions = 0;

  for (j = 0; j < MAX_QUERIES; j++) {
    m_QueryDatabase[j].category = INVALID_CATEGORY;
    m_QueryDatabase[j].desc = NULL;
    m_QueryDatabase[j].func = NULL;
    m_QueryDatabase[j].help = NULL;
  }
  m_NumQueries = 0;
}

// Frees up any allocated memory
void CDallasMainDlg::ClearFunctionDatabases(void) {
  int j;

  for (j = 0; j < m_NumFunctionCategories; j++)
    mem_free(m_FunctionCategories[j]);
  m_NumFunctionCategories = 0;

  for (j = 0; j < m_NumActions; j++) {
    m_ActionDatabase[j].category = INVALID_CATEGORY;
    mem_free(m_ActionDatabase[j].desc);
    m_ActionDatabase[j].desc = NULL;
    mem_free(m_ActionDatabase[j].func);
    m_ActionDatabase[j].func = NULL;
    mem_free(m_ActionDatabase[j].help);
    m_ActionDatabase[j].help = NULL;
  }
  m_NumActions = 0;

  for (j = 0; j < m_NumQueries; j++) {
    m_QueryDatabase[j].category = INVALID_CATEGORY;
    mem_free(m_QueryDatabase[j].desc);
    m_QueryDatabase[j].desc = NULL;
    mem_free(m_QueryDatabase[j].func);
    m_QueryDatabase[j].func = NULL;
    mem_free(m_QueryDatabase[j].help);
    m_QueryDatabase[j].help = NULL;
  }
  m_NumQueries = 0;
}

// Matches an integer ID to a given category name
int CDallasMainDlg::GetFunctionCategoryID(char *catname) {
  for (int i = 0; i < m_NumFunctionCategories; i++)
    if (strcmp(m_FunctionCategories[i], catname) == 0)
      return i;

  return INVALID_CATEGORY;
}

// Handle Parse Errors
void CDallasMainDlg::FunctionFileParseError(int error_code, int linenum, const char *filename) {
  CString err_msg;

  switch (error_code) {
  case INV_CAT_ERR:
    err_msg.Format("ERROR: Invalid category assigned in %s, line %d.", filename, linenum);
    break;
  case INV_ENUM_ERR:
    err_msg.Format("ERROR: Invalid or duplicate enumeration name assigned in %s, line %d.", filename, linenum);
    break;
  case INV_ENUM_VALUE_ERR:
    err_msg.Format("ERROR: Invalid or duplicate enumeration value assigned in %s, line %d.", filename, linenum);
    break;
  case MAX_ENUM_ERR:
    err_msg.Format("ERROR: Maximum enumeration limit reached in %s, line %d.", filename, linenum);
    break;
  case MAX_ENUM_VALUES_ERR:
    err_msg.Format("ERROR: Maximum enumeration value limit reached in %s, line %d.", filename, linenum);
    break;
  case INV_FLAG_ERR:
    err_msg.Format("ERROR: Invalid or duplicate flag name assigned in %s, line %d.", filename, linenum);
    break;
  case INV_FLAG_VALUE_ERR:
    err_msg.Format("ERROR: Invalid or duplicate flag value assigned in %s, line %d.", filename, linenum);
    break;
  case MAX_FLAG_ERR:
    err_msg.Format("ERROR: Maximum flag limit reached in %s, line %d.", filename, linenum);
    break;
  case MAX_FLAG_VALUES_ERR:
    err_msg.Format("ERROR: Maximum flag value limit reached in %s, line %d.", filename, linenum);
    break;
  case NO_MEM_ERR:
    err_msg.Format("ERROR: Ran out of memory while parsing %s, line %d.", filename, linenum);
    break;
  case UEOF_ERR:
    err_msg.Format("ERROR: Unexpected end of file while parsing %s, line %d.", filename, linenum);
    break;
  default:
    err_msg.Format("ERROR: An unknown error was detected in %s, line %d.", filename, linenum);
    break;
  }

  MessageBox(err_msg, "Function Database Parse Error", MB_OK | MB_ICONEXCLAMATION);
}

// Returns a pointer to the action description
char *CDallasMainDlg::GetActionDesc(int ID) {
  if (ID < 0 || ID >= m_NumActions)
    return NULL;

  return (m_ActionDatabase[ID].desc);
}

// Returns a pointer to the action help text
char *CDallasMainDlg::GetActionHelp(int ID) {
  if (ID < 0 || ID >= m_NumActions)
    return NULL;

  return (m_ActionDatabase[ID].help);
}

// Returns a pointer to the action function name
char *CDallasMainDlg::GetActionFunc(int ID) {
  if (ID == DO_NOTHING_ID)
    return DO_NOTHING_STRING;

  if (ID < 0 || ID >= m_NumActions)
    return INVALID_FUNCTION_NAME;

  return (m_ActionDatabase[ID].func);
}

// Searches action list for action matching given function name
int CDallasMainDlg::GetActionFuncID(char *func_name) {
  if (func_name == NULL)
    return INVALID_FUNCTION_ID;

  if (strcmp(DO_NOTHING_STRING, func_name) == 0)
    return DO_NOTHING_ID;

  for (int j = 0; j < m_NumActions; j++)
    if (strcmp(m_ActionDatabase[j].func, func_name) == 0)
      return (j);

  return INVALID_FUNCTION_ID;
}

// Returns a pointer to the query description
char *CDallasMainDlg::GetQueryDesc(int ID) {
  if (ID < 0 || ID >= m_NumQueries)
    return NULL;

  return (m_QueryDatabase[ID].desc);
}

// Returns a pointer to the query help text
char *CDallasMainDlg::GetQueryHelp(int ID) {
  if (ID < 0 || ID >= m_NumQueries)
    return NULL;

  return (m_QueryDatabase[ID].help);
}

// Returns a pointer to the query function name
char *CDallasMainDlg::GetQueryFunc(int ID) {
  if (ID < 0 || ID >= m_NumQueries)
    return INVALID_FUNCTION_NAME;

  return (m_QueryDatabase[ID].func);
}

// Searches query list for query matching given function name
int CDallasMainDlg::GetQueryFuncID(char *func_name) {
  if (func_name == NULL)
    return INVALID_FUNCTION_ID;

  for (int j = 0; j < m_NumQueries; j++)
    if (strcmp(m_QueryDatabase[j].func, func_name) == 0)
      return (j);

  return INVALID_FUNCTION_ID;
}

// Returns the Query's return type (parameter type), or UNKNOWN_PARAMETER_TYPE
int CDallasMainDlg::GetQueryReturnType(int ID, CString &name) {
  char *desc;
  int type;

  name = "";
  desc = GetQueryDesc(ID);
  if (desc == NULL)
    return (UNKNOWN_PARAMETER_TYPE);

  if (!isalpha(desc[0]))
    return (UNKNOWN_PARAMETER_TYPE);
  type = ConvertParamCharToType(desc[0]);

  if (type != ENUM_PARAMETER_TYPE && type != FLAG_PARAMETER_TYPE) {
    if (desc[1] != ':')
      return (UNKNOWN_PARAMETER_TYPE);
    return (type);
  }

  // If it's an enum or flag, we need to get the name of the enum/flag type as well
  if (desc[1] == '(')
    for (int j = 2; (desc[j] != '\0' && desc[j] != ')'); j++)
      name += desc[j];

  return (type);
}

// Parses the given text file, adding categories, actions, and queries, as it finds them
void CDallasMainDlg::ParseFunctionFile(char *filename, bool show_errors /*=TRUE*/) {
  CFILE *ifile;
  char linebuf[2048];
  char *line;
  char helpbuf[2048];
  int linenum;
  char fullpath[_MAX_PATH];

  ddio_MakePath(fullpath, LocalScriptDir, filename, NULL);

  ifile = cfopen(fullpath, "rt");
  if (ifile == NULL) {
    if (show_errors) {
      CString msg;
      msg.Format("Unable to open \"%s\"!", filename);
      MessageBox(msg, "No Function Database Found!", MB_OK | MB_ICONEXCLAMATION);
    }
    return;
  }

  linenum = 0;

  while (!cfeof(ifile)) {

    cf_ReadString(linebuf, sizeof(linebuf), ifile);
    linenum++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(linebuf);
    line = SkipInitialWhitespace(linebuf);

    if (strncmp(line, TAG_CAT, strlen(TAG_CAT)) == 0) { // parse a category block
      bool done = 0;

      do {

        cf_ReadString(linebuf, sizeof(linebuf), ifile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        if (strncmp(line, TAG_END, strlen(TAG_END)) == 0)
          done = 1;
        else if (m_NumFunctionCategories < MAX_CATEGORIES) {
          if (GetFunctionCategoryID(line) == INVALID_CATEGORY) { // don't add duplicate categories
            m_FunctionCategories[m_NumFunctionCategories] = (char *)mem_malloc(strlen(line) + 1);
            if (m_FunctionCategories[m_NumFunctionCategories] == NULL) {
              FunctionFileParseError(NO_MEM_ERR, linenum, filename);
              cfclose(ifile);
              return;
            }
            strcpy(m_FunctionCategories[m_NumFunctionCategories], line);
            m_NumFunctionCategories++;
            if (m_NumFunctionCategories == MAX_CATEGORIES)
              MessageBox("Warning: The Maximum Category limit has been reached!", "Warning!");
          }
        }

      } while (!done && !cfeof(ifile));

      if (!done)
        FunctionFileParseError(UEOF_ERR, linenum, filename);
    } else if (strncmp(line, TAG_USERTYPE, strlen(TAG_USERTYPE)) == 0) { // Parse a user type line
      tEnumDBEntry *enum_entry;
      char *enum_name;
      char *max_value_text;

      // Strip off the name of this user type
      max_value_text = NULL;
      enum_name = strtok(line, WHITESPACE_CHARS);
      if (enum_name != NULL)
        enum_name = strtok(NULL, ":");
      if (enum_name != NULL)
        max_value_text = strtok(NULL, "");
      if (enum_name == NULL || max_value_text == NULL || GetEnumID(enum_name) != INVALID_ENUM) {
        FunctionFileParseError(INV_ENUM_ERR, linenum, filename);
        enum_entry = NULL;
      } else if (m_NumEnums == MAX_ENUMS) {
        FunctionFileParseError(MAX_ENUM_ERR, linenum, filename);
        enum_entry = NULL;
      } else {
        enum_entry = &m_EnumDatabase[m_NumEnums++];
        enum_entry->name = (char *)mem_malloc(strlen(enum_name) + 1);
        if (enum_entry->name == NULL) {
          FunctionFileParseError(NO_MEM_ERR, linenum, filename);
          cfclose(ifile);
          return;
        }
        strcpy(enum_entry->name, enum_name);
        enum_entry->num_values = 0;
        enum_entry->is_user_type = TRUE;
        enum_entry->max_values = atoi(max_value_text);
        if (enum_entry->max_values < 0)
          enum_entry->max_values = 0;
        if (enum_entry->max_values > (MAX_ENUMS - 2))
          enum_entry->max_values = (MAX_ENUMS - 2);

        // Add the default (-1:None) value
        tEnumValueEntry *value_entry;
        value_entry = &enum_entry->values[enum_entry->num_values++];
        value_entry->name = (char *)mem_malloc(strlen(USERTYPE_NONE) + 1);
        if (value_entry->name == NULL) {
          FunctionFileParseError(NO_MEM_ERR, linenum, filename);
          cfclose(ifile);
          return;
        }
        strcpy(value_entry->name, USERTYPE_NONE);
        value_entry->value = -1;
      }
    } else if (strncmp(line, TAG_ENUM, strlen(TAG_ENUM)) == 0) { // Parse an enumeration block
      tEnumDBEntry *enum_entry;
      char *enum_name;
      bool done;

      // Strip off the name of this enumeration type
      enum_name = strtok(line, WHITESPACE_CHARS);
      if (enum_name != NULL)
        enum_name = strtok(NULL, "");
      if (enum_name == NULL || GetEnumID(enum_name) != INVALID_ENUM) {
        FunctionFileParseError(INV_ENUM_ERR, linenum, filename);
        enum_entry = NULL;
      } else if (m_NumEnums == MAX_ENUMS) {
        FunctionFileParseError(MAX_ENUM_ERR, linenum, filename);
        enum_entry = NULL;
      } else {
        enum_entry = &m_EnumDatabase[m_NumEnums++];
        enum_entry->name = (char *)mem_malloc(strlen(enum_name) + 1);
        if (enum_entry->name == NULL) {
          FunctionFileParseError(NO_MEM_ERR, linenum, filename);
          cfclose(ifile);
          return;
        }
        strcpy(enum_entry->name, enum_name);
        enum_entry->num_values = 0;
        enum_entry->is_user_type = FALSE;
        enum_entry->max_values = 0;
      }

      // Parse the enumeration values for this entry
      done = 0;
      do {

        cf_ReadString(linebuf, sizeof(linebuf), ifile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        if (strncmp(line, TAG_END, strlen(TAG_END)) == 0)
          done = 1;
        else if (enum_entry != NULL) {
          tEnumValueEntry *value_entry;
          int enum_value;
          char *enum_value_string;
          char *enum_value_name;

          // Parse out the enum value and value name
          enum_value_string = strtok(line, ":");
          if (enum_value_string != NULL) {
            enum_value = atoi(enum_value_string);
            enum_value_name = strtok(NULL, "");
          }

          if (enum_value_string == NULL || enum_value_name == NULL ||
              GetEnumValueName(enum_entry->name, enum_value) != NULL) {
            FunctionFileParseError(INV_ENUM_VALUE_ERR, linenum, filename);
            value_entry = NULL;
          } else if (enum_entry->num_values == MAX_ENUM_VALUES) {
            FunctionFileParseError(MAX_ENUM_VALUES_ERR, linenum, filename);
            value_entry = NULL;
          } else {
            value_entry = &enum_entry->values[enum_entry->num_values++];
            value_entry->name = (char *)mem_malloc(strlen(enum_value_name) + 1);
            if (value_entry->name == NULL) {
              FunctionFileParseError(NO_MEM_ERR, linenum, filename);
              cfclose(ifile);
              return;
            }
            strcpy(value_entry->name, enum_value_name);
            value_entry->value = enum_value;
          }
        }

      } while (!done && !cfeof(ifile));

      if (!done)
        FunctionFileParseError(UEOF_ERR, linenum, filename);
    } else if (strncmp(line, TAG_FLAG, strlen(TAG_FLAG)) == 0) { // Parse a flag block
      tFlagDBEntry *flag_entry;
      char *flag_name;
      bool done;

      // Strip off the name of this flag type
      flag_name = strtok(line, WHITESPACE_CHARS);
      if (flag_name != NULL)
        flag_name = strtok(NULL, "");
      if (flag_name == NULL || GetFlagID(flag_name) != INVALID_FLAG) {
        FunctionFileParseError(INV_FLAG_ERR, linenum, filename);
        flag_entry = NULL;
      } else if (m_NumFlags == MAX_FLAGS) {
        FunctionFileParseError(MAX_FLAG_ERR, linenum, filename);
        flag_entry = NULL;
      } else {
        flag_entry = &m_FlagDatabase[m_NumFlags++];
        flag_entry->name = (char *)mem_malloc(strlen(flag_name) + 1);
        if (flag_entry->name == NULL) {
          FunctionFileParseError(NO_MEM_ERR, linenum, filename);
          cfclose(ifile);
          return;
        }
        strcpy(flag_entry->name, flag_name);
        flag_entry->num_values = 0;
      }

      // Parse the flag values for this entry
      done = 0;
      do {

        cf_ReadString(linebuf, sizeof(linebuf), ifile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        if (strncmp(line, TAG_END, strlen(TAG_END)) == 0)
          done = 1;
        else if (flag_entry != NULL) {
          tFlagValueEntry *value_entry;
          int flag_value;
          char *flag_value_string;
          char *flag_value_name;

          // Parse out the flag value and value name
          flag_value_string = strtok(line, ":");
          if (flag_value_string != NULL) {
            flag_value = atoi(flag_value_string);
            flag_value_name = strtok(NULL, "");
          }

          if (flag_value_string == NULL || flag_value_name == NULL ||
              GetFlagValueName(flag_entry->name, flag_value) != NULL) {
            FunctionFileParseError(INV_FLAG_VALUE_ERR, linenum, filename);
            value_entry = NULL;
          } else if (flag_entry->num_values == MAX_FLAG_VALUES) {
            FunctionFileParseError(MAX_FLAG_VALUES_ERR, linenum, filename);
            value_entry = NULL;
          } else {
            value_entry = &flag_entry->values[flag_entry->num_values++];
            value_entry->name = (char *)mem_malloc(strlen(flag_value_name) + 1);
            if (value_entry->name == NULL) {
              FunctionFileParseError(NO_MEM_ERR, linenum, filename);
              cfclose(ifile);
              return;
            }
            strcpy(value_entry->name, flag_value_name);
            value_entry->value = flag_value;
          }
        }

      } while (!done && !cfeof(ifile));

      if (!done)
        FunctionFileParseError(UEOF_ERR, linenum, filename);
    } else if (strncmp(line, TAG_ACTION, strlen(TAG_ACTION)) == 0) { // Parse action block
      if (m_NumActions >= MAX_ACTIONS) {
        MessageBox("ERROR: The Maximum Action limit has been exceeded!\n\nParsing must stop immediately.", "ERROR!");
        cfclose(ifile);
        return;
      }
      tActionDBEntry *action = &m_ActionDatabase[m_NumActions++];
      if (m_NumActions == MAX_ACTIONS) {
        MessageBox("Warning: The Maximum Action limit has been reached!", "Warning!");
      }

      // Read category
      cf_ReadString(linebuf, sizeof(linebuf), ifile);
      linenum++;

      // Remove whitespace padding at start and end of line
      RemoveTrailingWhitespace(linebuf);
      line = SkipInitialWhitespace(linebuf);

      action->category = GetFunctionCategoryID(line);
      if (action->category == INVALID_CATEGORY) {
        FunctionFileParseError(INV_CAT_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }

      // Read action description
      cf_ReadString(linebuf, sizeof(linebuf), ifile);
      linenum++;

      // Remove whitespace padding at start and end of line
      RemoveTrailingWhitespace(linebuf);
      line = SkipInitialWhitespace(linebuf);

      action->desc = (char *)mem_malloc(strlen(line) + 1);
      if (action->desc == NULL) {
        FunctionFileParseError(NO_MEM_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }
      strcpy(action->desc, line);

      // Read action function
      cf_ReadString(linebuf, sizeof(linebuf), ifile);
      linenum++;

      // Remove whitespace padding at start and end of line
      RemoveTrailingWhitespace(linebuf);
      line = SkipInitialWhitespace(linebuf);

      action->func = (char *)mem_malloc(strlen(line) + 1);
      if (action->func == NULL) {
        FunctionFileParseError(NO_MEM_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }
      strcpy(action->func, line);

      // Read help
      bool done = 0;
      helpbuf[0] = 0;
      do {

        cf_ReadString(linebuf, sizeof(linebuf), ifile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        if (strncmp(line, TAG_END, strlen(TAG_END)) == 0)
          done = 1;
        else {
          strcat(helpbuf, line);
          strcat(helpbuf, "\r\n");
        }

      } while (!done && !cfeof(ifile));

      if (!done)
        FunctionFileParseError(UEOF_ERR, linenum, filename);

      action->help = (char *)mem_malloc(strlen(helpbuf) + 1);
      if (action->help == NULL) {
        FunctionFileParseError(NO_MEM_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }
      strcpy(action->help, helpbuf);
    } else if (strncmp(line, TAG_QUERY, strlen(TAG_QUERY)) == 0) { // Parse Query block
      if (m_NumQueries >= MAX_QUERIES) {
        MessageBox("ERROR: The Maximum Query limit has been exceeded!\n\nParsing must stop immediately.", "ERROR!");
        cfclose(ifile);
        return;
      }
      tQueryDBEntry *query = &m_QueryDatabase[m_NumQueries++];
      if (m_NumQueries == MAX_QUERIES) {
        MessageBox("Warning: The Maximum Query limit has been reached!", "Warning!");
      }

      // Read category
      cf_ReadString(linebuf, sizeof(linebuf), ifile);
      linenum++;

      // Remove whitespace padding at start and end of line
      RemoveTrailingWhitespace(linebuf);
      line = SkipInitialWhitespace(linebuf);

      query->category = GetFunctionCategoryID(line);
      if (query->category == INVALID_CATEGORY) {
        FunctionFileParseError(INV_CAT_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }

      // Read action description
      cf_ReadString(linebuf, sizeof(linebuf), ifile);
      linenum++;

      // Remove whitespace padding at start and end of line
      RemoveTrailingWhitespace(linebuf);
      line = SkipInitialWhitespace(linebuf);

      query->desc = (char *)mem_malloc(strlen(line) + 1);
      if (query->desc == NULL) {
        FunctionFileParseError(NO_MEM_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }
      strcpy(query->desc, line);

      // Read action function
      cf_ReadString(linebuf, sizeof(linebuf), ifile);
      linenum++;

      // Remove whitespace padding at start and end of line
      RemoveTrailingWhitespace(linebuf);
      line = SkipInitialWhitespace(linebuf);

      query->func = (char *)mem_malloc(strlen(line) + 1);
      if (query->func == NULL) {
        FunctionFileParseError(NO_MEM_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }
      strcpy(query->func, line);

      // Read help
      bool done = 0;
      helpbuf[0] = 0;
      do {

        cf_ReadString(linebuf, sizeof(linebuf), ifile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        if (strncmp(line, TAG_END, strlen(TAG_END)) == 0)
          done = 1;
        else {
          strcat(helpbuf, line);
          strcat(helpbuf, "\r\n");
        }

      } while (!done && !cfeof(ifile));

      if (!done)
        FunctionFileParseError(UEOF_ERR, linenum, filename);

      query->help = (char *)mem_malloc(strlen(helpbuf) + 1);
      if (query->help == NULL) {
        FunctionFileParseError(NO_MEM_ERR, linenum, filename);
        cfclose(ifile);
        return;
      }
      strcpy(query->help, helpbuf);
    }
  }

  cfclose(ifile);
}

// Returns a description copy with the parameter type info removed
void CDallasMainDlg::ParseOutActionVarTypes(char *new_desc, char *old_desc) {
  CString name_text, default_text, range_text;
  CString new_desc_text;

  new_desc_text = "";
  while ((*old_desc) != '\0') {

    // If it's start of a param block, extract the param name
    if ((*old_desc) == '[') {
      ParseParamBlock(old_desc, name_text, default_text, range_text);
      new_desc_text += '[';
      new_desc_text += name_text;
      new_desc_text += ']';
    } else {
      new_desc_text += (*old_desc);
      old_desc++;
    }
  }

  strcpy(new_desc, new_desc_text.GetBuffer(0));
}

/* OLD VERSION
// Returns a description copy with the parameter type info removed
void CDallasMainDlg::ParseOutActionVarTypes(char *new_desc, char *old_desc)
{
        int ok_to_write=TRUE;

        do {
                if(ok_to_write) {
                        (*new_desc)=(*old_desc);
                        new_desc++;
                }

                if((*old_desc)=='[')
                        ok_to_write=FALSE;
                else if((*old_desc)==':')
                        ok_to_write=TRUE;

                old_desc++;

        } while((*old_desc)!='\0');

        (*new_desc)=(*old_desc);
}
*/

// Returns a description copy with the parameter type info removed
void CDallasMainDlg::ParseOutQueryVarTypes(char *new_desc, char *old_desc) {
  CString name_text, default_text, range_text;
  CString new_desc_text;

  new_desc_text = "";

  // Skip the return type section
  old_desc = strchr(old_desc, ':');
  if (old_desc == NULL) {
    strcpy(new_desc, new_desc_text.GetBuffer(0));
    return;
  }
  old_desc++;

  // Parse the rest like it was an action
  ParseOutActionVarTypes(new_desc, old_desc);
}

/* OLD VERSION
// Returns a description copy with the parameter type info removed
void CDallasMainDlg::ParseOutQueryVarTypes(char *new_desc, char *old_desc)
{
        int ok_to_write=FALSE;

        do {
                if(ok_to_write) {
                        (*new_desc)=(*old_desc);
                        new_desc++;
                }

                if((*old_desc)=='[')
                        ok_to_write=FALSE;
                else if((*old_desc)==':')
                        ok_to_write=TRUE;

                old_desc++;

        } while((*old_desc)!='\0');

        (*new_desc)=(*old_desc);
}
*/

// Validates an action node by conforming its parameters to what they should be
// returns FALSE if node was modified significantly, otherwise TRUE
bool CDallasMainDlg::ValidateActionNode(HTREEITEM node, int linenum) {
  CString name_text, default_text, range_text;
  tTreeNodeData *data;
  HTREEITEM child_node;
  int ID;
  char *desc;

  if (node == NULL)
    return TRUE;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL || data->type != ACTION_STATEMENT_NODE)
    return TRUE;

  ID = data->ID;
  if (ID < 0 || ID >= m_NumActions)
    return TRUE;

  desc = GetActionDesc(ID);
  if (desc == NULL)
    return TRUE;

  // Get the first child, if one exists
  child_node = m_ScriptTree.GetChildItem(node);

  // Parse the description, adding default parameter nodes appropriately
  bool modified = FALSE;
  while ((*desc) != '\0') {

    if ((*desc) == '[') { // Note the start of a parameter block

      int param_type = ParseParamBlock(desc, name_text, default_text, range_text);
      if (param_type >= 0) {

        // Check the corresponding param (if it exists) and make it match up
        if (ConformParamNode(node, child_node, param_type, name_text.GetBuffer(0), default_text.GetBuffer(0)))
          modified = TRUE;

        if (child_node != NULL)
          child_node = m_ScriptTree.GetNextSiblingItem(child_node);
      }

    } else {
      desc++;
    }
  }

  // Delete any remaining child parameter nodes (they are no longer used)
  if (child_node != NULL) {
    do {
      HTREEITEM temp_node = child_node;
      child_node = m_ScriptTree.GetNextSiblingItem(child_node);
      FreeTreeItem(temp_node);
    } while (child_node != NULL);

    modified = TRUE;
  }

  if (modified)
    ScriptFileParseError(MODIFIED_FUNC_ERR, linenum, GetScriptID(node), GetActionFunc(ID));

  return (!modified);
}

/* OLD VERSION
// Validates an action node by conforming its parameters to what they should be
// returns FALSE if node was modified significantly, otherwise TRUE
bool CDallasMainDlg::ValidateActionNode(HTREEITEM node, int linenum)
{
        tTreeNodeData *data;
        HTREEITEM child_node;
        int ID;
        char *desc, *desc_copy;

        if(node==NULL) return TRUE;

        data=(tTreeNodeData *)m_ScriptTree.GetItemData(node);
        if(data==NULL || data->type!=ACTION_STATEMENT_NODE) return TRUE;

        ID=data->ID;
        if(ID<0 || ID>=m_NumActions) return TRUE;

        desc=GetActionDesc(ID);
        if(desc==NULL) return TRUE;

        // Get the first child, if one exists
        child_node=m_ScriptTree.GetChildItem(node);

        // Make a copy of description (so null chars can be added)
        desc_copy=(char *)mem_malloc(strlen(desc)+1);
        if(desc_copy==NULL) {
                MessageBox("ERROR: Out of memory in ValidateActionNode()!","Out of Memory
Error!",MB_OK|MB_ICONEXCLAMATION); return FALSE;
        }
        strcpy(desc_copy,desc);

        // Parse the description, adding default parameter nodes appropriately
        int j=0;
        bool start_block_found=FALSE;
        bool type_delim_found=FALSE;
        char *param_name=FALSE;
        int param_type_char=-1;
        int param_type;
        bool modified=FALSE;

        while(desc_copy[j]!='\0') {

                if(desc_copy[j]=='[') {				// Note the start of a parameter block
                        start_block_found=TRUE;
                }
                else if(desc_copy[j]==':' && start_block_found) {		// Note the end of parameter type field
                        type_delim_found=TRUE;
                }
                else if(desc_copy[j]==']') {		// If end of block, add the parameter

                        if(param_type_char!=-1 && param_name!=NULL) {

                                desc_copy[j]='\0';	// mark the end of the variable name

                                // Get the parameter type
                                param_type=ConvertParamCharToType(param_type_char);

                                // Check the corresponding param (if it exists) and make it match up
                                if(ConformParamNode(node,child_node,param_type,param_name))
                                        modified=TRUE;

                                if(child_node!=NULL) child_node=m_ScriptTree.GetNextSiblingItem(child_node);
                        }

                        start_block_found=FALSE;
                        type_delim_found=FALSE;
                        param_name=FALSE;
                        param_type_char=-1;
                }
                else if(start_block_found && param_type_char==-1) {
                        param_type_char=desc_copy[j];
                }
                else if(type_delim_found && param_name==NULL) {
                        param_name=&desc_copy[j];
                }

                j++;
        }

        // Free up the copy memory
        mem_free(desc_copy);

        // Delete any remaining child parameter nodes (they are no longer used)
        if(child_node!=NULL) {
                do {
                        HTREEITEM temp_node=child_node;
                        child_node=m_ScriptTree.GetNextSiblingItem(child_node);
                        FreeTreeItem(temp_node);
                } while(child_node!=NULL);

                modified=TRUE;
        }

        if(modified)
                ScriptFileParseError(MODIFIED_FUNC_ERR,linenum,GetScriptID(node),GetActionFunc(ID));

        return (!modified);
}
*/

// Checks the given param node (if it exists) and makes it match up with the given data
// Returns TRUE if a significant modification had to take place, FALSE otherwise
bool CDallasMainDlg::ConformParamNode(HTREEITEM parent_node, HTREEITEM &param_node, int type, char *name,
                                      char *def_value /*=NULL*/) {
  tTreeNodeData *data;
  CString query_ret_name;
  int index;

  if (parent_node == NULL)
    return FALSE;

  // If the param node doesn't exist, then we need to add a default param
  if (param_node == NULL) {
    CreateDefaultParameterNode(parent_node, TVI_LAST, type, name, def_value);
    return TRUE;
  }

  // See if the node matches the given data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(param_node);
  if (data != NULL) {
    // Check parameter node
    if (data->type == PARAMETER_NODE && data->ID == type) {
      // node matches, so copy over the name in case it's changed (not considered a major mod)
      strcpy(data->name, name);
      UpdateNodeText(param_node);
      return FALSE;
    }

    // If it's a SPECNAME, see if we can transfer it over
    if (data->type == PARAMETER_NODE && data->ID == SPECNAME_PARAMETER_TYPE) {
      if (type == PATH_PARAMETER_TYPE) {
        data->ID = type;
        strcpy(data->name, name);
        index = osipf_FindPathName(data->str_val);
        if (index < 0) {
          data->int_val = NOT_SPECIFIED_TYPE;
          strcpy(data->str_val, "");
          UpdateNodeText(param_node);
          return TRUE;
        }
        data->int_val = index;
        strcpy(data->str_val, GamePaths[index].name);
        UpdateNodeText(param_node);
        return FALSE;
      } else if (type == MATCEN_PARAMETER_TYPE) {
        data->ID = type;
        strcpy(data->name, name);
        data->subID = USE_MATCEN_VALUE;
        index = osipf_FindMatcenName(data->str_val);
        if (index < 0) {
          data->int_val = NOT_SPECIFIED_TYPE;
          strcpy(data->str_val, "");
          UpdateNodeText(param_node);
          return TRUE;
        }
        char matcen_name[MAX_MATCEN_NAME_LEN + 1];
        Matcen[index]->GetName(matcen_name);
        data->int_val = index;
        strcpy(data->str_val, matcen_name);
        UpdateNodeText(param_node);
        return FALSE;
      } else if (type == LEVEL_GOAL_PARAMETER_TYPE) {
        data->ID = type;
        strcpy(data->name, name);
        data->subID = USE_LEVEL_GOAL_VALUE;
        index = osipf_FindLevelGoalName(data->str_val);
        if (index < 0) {
          data->int_val = NOT_SPECIFIED_TYPE;
          strcpy(data->str_val, "");
          UpdateNodeText(param_node);
          return TRUE;
        }
        data->int_val = index;
        UpdateNodeText(param_node);
        return FALSE;
      } else if (type == STRM_AUDIO_PARAMETER_TYPE) {
        data->ID = type;
        strcpy(data->name, name);
        if (!GamefileExists(data->str_val)) {
          strcpy(data->str_val, "");
          UpdateNodeText(param_node);
          return TRUE;
        }
        UpdateNodeText(param_node);
        return FALSE;
      }
    }

    // Check query node
    if (data->type == EXPRESSION_NODE && GetQueryReturnType(data->ID, query_ret_name) == type) {
      // node matches, so copy over the name in case it's changed (not considered a major mod)
      strcpy(data->name, name);
      UpdateNodeText(param_node);
      return FALSE;
    }
  }

  // Since the param node doesn't match up with the data, replace it with a default that does
  HTREEITEM new_node;
  new_node = CreateDefaultParameterNode(parent_node, param_node, type, name, def_value);
  FreeTreeItem(param_node);
  param_node = new_node;
  UpdateNodeText(param_node);

  return TRUE;
}

// Validates a query node by conforming its parameters to what they should be
// returns FALSE if node was modified significantly, otherwise TRUE
bool CDallasMainDlg::ValidateQueryNode(HTREEITEM node, int linenum) {
  CString name_text, default_text, range_text;
  tTreeNodeData *data;
  HTREEITEM child_node;
  int ID;
  char *desc;

  if (node == NULL)
    return TRUE;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL || data->type != EXPRESSION_NODE)
    return TRUE;

  ID = data->ID;
  if (ID < 0 || ID >= m_NumQueries)
    return TRUE;

  desc = strchr(GetQueryDesc(ID), ':');
  if (desc == NULL)
    return TRUE;
  desc++;

  // Get the first child, if one exists
  child_node = m_ScriptTree.GetChildItem(node);

  // Parse the description, adding default parameter nodes appropriately
  bool modified = FALSE;
  while ((*desc) != '\0') {

    if ((*desc) == '[') { // Note the start of a parameter block

      int param_type = ParseParamBlock(desc, name_text, default_text, range_text);
      if (param_type >= 0) {

        // Check the corresponding param (if it exists) and make it match up
        if (ConformParamNode(node, child_node, param_type, name_text.GetBuffer(0), default_text.GetBuffer(0)))
          modified = TRUE;

        if (child_node != NULL)
          child_node = m_ScriptTree.GetNextSiblingItem(child_node);
      }
    } else {
      desc++;
    }
  }

  // Delete any remaining child parameter nodes (they are no longer used)
  if (child_node != NULL) {
    do {
      HTREEITEM temp_node = child_node;
      child_node = m_ScriptTree.GetNextSiblingItem(child_node);
      FreeTreeItem(temp_node);
    } while (child_node != NULL);

    modified = TRUE;
  }

  if (modified)
    ScriptFileParseError(MODIFIED_FUNC_ERR, linenum, GetScriptID(node), GetQueryFunc(ID));

  return (!modified);
}

/* OLD VERSION
// Validates a query node by conforming its parameters to what they should be
// returns FALSE if node was modified significantly, otherwise TRUE
bool CDallasMainDlg::ValidateQueryNode(HTREEITEM node, int linenum)
{
        tTreeNodeData *data;
        HTREEITEM child_node;
        int ID;
        char *desc, *desc_copy;

        if(node==NULL) return TRUE;

        data=(tTreeNodeData *)m_ScriptTree.GetItemData(node);
        if(data==NULL || data->type!=EXPRESSION_NODE) return TRUE;

        ID=data->ID;
        if(ID<0 || ID>=m_NumQueries) return TRUE;

        desc=strchr(GetQueryDesc(ID),':');
        if(desc==NULL) return TRUE;
        desc++;

        // Get the first child, if one exists
        child_node=m_ScriptTree.GetChildItem(node);

        // Make a copy of description (so null chars can be added)
        desc_copy=(char *)mem_malloc(strlen(desc)+1);
        if(desc_copy==NULL) {
                MessageBox("ERROR: Out of memory in ValidateQueryNode()!","Out of Memory
Error!",MB_OK|MB_ICONEXCLAMATION); return FALSE;
        }
        strcpy(desc_copy,desc);

        // Parse the description, adding default parameter nodes appropriately
        int j=0;
        bool start_block_found=FALSE;
        bool type_delim_found=FALSE;
        char *param_name=FALSE;
        int param_type_char=-1;
        int param_type;
        bool modified=FALSE;

        while(desc_copy[j]!='\0') {

                if(desc_copy[j]=='[') {				// Note the start of a parameter block
                        start_block_found=TRUE;
                }
                else if(desc_copy[j]==':' && start_block_found) {		// Note the end of parameter type field
                        type_delim_found=TRUE;
                }
                else if(desc_copy[j]==']') {		// If end of block, add the parameter

                        if(param_type_char!=-1 && param_name!=NULL) {

                                desc_copy[j]='\0';	// mark the end of the variable name

                                // Get the parameter type
                                param_type=ConvertParamCharToType(param_type_char);

                                // Check the corresponding param (if it exists) and make it match up
                                if(ConformParamNode(node,child_node,param_type,param_name))
                                        modified=TRUE;

                                if(child_node!=NULL) child_node=m_ScriptTree.GetNextSiblingItem(child_node);
                        }

                        start_block_found=FALSE;
                        type_delim_found=FALSE;
                        param_name=FALSE;
                        param_type_char=-1;
                }
                else if(start_block_found && param_type_char==-1) {
                        param_type_char=desc_copy[j];
                }
                else if(type_delim_found && param_name==NULL) {
                        param_name=&desc_copy[j];
                }

                j++;
        }

        // Free up the copy memory
        mem_free(desc_copy);

        // Delete any remaining child parameter nodes (they are no longer used)
        if(child_node!=NULL) {
                do {
                        HTREEITEM temp_node=child_node;
                        child_node=m_ScriptTree.GetNextSiblingItem(child_node);
                        FreeTreeItem(temp_node);
                } while(child_node!=NULL);

                modified=TRUE;
        }

        if(modified)
                ScriptFileParseError(MODIFIED_FUNC_ERR,linenum,GetScriptID(node),GetQueryFunc(ID));

        return (!modified);
}
*/

// Fills up the given menu with the categories of actions
// NOTE: Command ID's of menu items start at the given command_offset
void CDallasMainDlg::FillActionMenu(CMenu *action_menu, int command_offset) {
  int j, k, actions_added;

  // Loop through the categories, creating submenu for each one
  for (j = 0; j < m_NumFunctionCategories; j++) {
    CMenu category_submenu;
    category_submenu.CreatePopupMenu();
    actions_added = 0;

    // Scan the list, adding Actions that match the current category
    for (k = 0; k < m_NumActions; k++)
      if (m_ActionDatabase[k].category == j) {
        char *temp_desc = (char *)mem_malloc(strlen(m_ActionDatabase[k].desc) + 1);
        if (temp_desc == NULL) {
          MessageBox("Out of memory error in FillActionMenu()!", "Memory Error!", MB_OK | MB_ICONEXCLAMATION);
          return;
        }
        ParseOutActionVarTypes(temp_desc, m_ActionDatabase[k].desc);
        category_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, (command_offset + k), temp_desc);
        mem_free(temp_desc);
        actions_added++;
      }

    // Detach and add this submenu to the action menu
    ColumnizePopupMenu(&category_submenu);
    if (actions_added == 0)
      action_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)category_submenu.Detach(), m_FunctionCategories[j]);
    else
      action_menu->AppendMenu(MF_POPUP, (UINT_PTR)category_submenu.Detach(), m_FunctionCategories[j]);
  }
}

// Fills up the given menu with the categories of queries
// NOTE: Command ID's of menu items start at the given command_offset
void CDallasMainDlg::FillQueryMenu(CMenu *query_menu, int command_offset, int valid_return_type,
                                   char *valid_return_name) {
  int j, k, queries_added;
  int query_ret_type;
  CString query_ret_name;
  bool types_match;

  // Loop through the categories, creating submenu for each one
  for (j = 0; j < m_NumFunctionCategories; j++) {
    CMenu category_submenu;
    category_submenu.CreatePopupMenu();
    queries_added = 0;

    // Scan the list, adding queries that match the current category
    for (k = 0; k < m_NumActions; k++)
      if (m_QueryDatabase[k].category == j) {
        char *temp_desc = (char *)mem_malloc(strlen(m_QueryDatabase[k].desc) + 1);
        if (temp_desc == NULL) {
          MessageBox("Out of memory error in FillQueryMenu()!", "Memory Error!", MB_OK | MB_ICONEXCLAMATION);
          return;
        }
        ParseOutQueryVarTypes(temp_desc, m_QueryDatabase[k].desc);

        query_ret_type = GetQueryReturnType(k, query_ret_name);

        // See if the types match up
        types_match = FALSE;
        if (valid_return_type == ANY_PARAMETER_TYPE)
          types_match = TRUE;
        else if (valid_return_type == query_ret_type) {
          if (valid_return_type == ENUM_PARAMETER_TYPE || valid_return_type == FLAG_PARAMETER_TYPE) {
            if (strlen(valid_return_name) == 0)
              types_match = TRUE;
            else if (strcmp(valid_return_name, query_ret_name.GetBuffer(0)) == 0)
              types_match = TRUE;
          } else
            types_match = TRUE;
        }

        if (types_match) {
          category_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, (command_offset + k), temp_desc);
          queries_added++;
        } else
          category_submenu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, (command_offset + k), temp_desc);
        mem_free(temp_desc);
      }

    // Detach and add this submenu to the action menu
    ColumnizePopupMenu(&category_submenu);
    if (queries_added == 0)
      query_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)category_submenu.Detach(), m_FunctionCategories[j]);
    else
      query_menu->AppendMenu(MF_POPUP, (UINT_PTR)category_submenu.Detach(), m_FunctionCategories[j]);
  }
}

// Attempts to parse the Nth (indexed at 1) bracketed section of the given function node's desc,
// and obtain from it the parameter name, default string, and range string.
// It returns the param type if successfull, or -1 if the requested Parameter section
// does not exist
int CDallasMainDlg::ParseNthParam(HTREEITEM func_node, int n, CString &name_text, CString &default_text,
                                  CString &range_text) {
  tTreeNodeData *data;

  if (func_node == NULL)
    return (-1);

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(func_node);
  if (data == NULL)
    return (-1);

  // Handle action nodes
  if (data->type == ACTION_STATEMENT_NODE) {
    char *desc = GetActionDesc(data->ID);
    return (ParseNthParam(desc, n, name_text, default_text, range_text));
  }

  // Handle query nodes
  if (data->type == EXPRESSION_NODE) {
    char *desc = GetQueryDesc(data->ID);
    return (ParseNthParam(desc, n, name_text, default_text, range_text));
  }

  return (-1);
}

// Attempts to parse the Nth (indexed at 1) bracketed section of the given action desc,
// and obtain from it the parameter name, default string, and range string.
// It returns the param type if successfull, or -1 if the requested Parameter section
// does not exist
int CDallasMainDlg::ParseNthParam(char *desc, int n, CString &name_text, CString &default_text, CString &range_text) {
  // Check validity of desc and given n
  if (n <= 0 || desc == NULL)
    return (-1);

  // Find the n'th parameter block (bracketed section)
  char *s;
  s = strchr(desc, '[');
  for (int j = 1; j < n; j++)
    if (s != NULL) {
      s++;
      s = strchr(s, '[');
    }

  // Make sure the requested section was found
  if (s == NULL)
    return FALSE;

  // Parse the parameter block into its different sections
  return (ParseParamBlock(s, name_text, default_text, range_text));
}

#define NO_SECTION 0
#define TYPE_SECTION 1
#define NAME_SECTION 2
#define DEFAULT_SECTION 3
#define RANGE_SECTION 4

// Parses the next param block encountered, and, if successfull, returns the
// parameter type (-1 is returned if a parameter block was not found).
// The name, default, and range strings are also set appropriately, and the
// line pointer will be set to the first character after the closing bracket.
int CDallasMainDlg::ParseParamBlock(char_ptr &line, CString &name_text, CString &default_text, CString &range_text) {
  int param_type_char;

  // Set all the return data to empty
  name_text = "";
  default_text = "";
  range_text = "";
  param_type_char = -1;

  // Parse the parameter block
  int currently_parsing = NO_SECTION;
  bool done = FALSE;
  while (!done && (*line) != '\0') {

    char ch = (*line);
    if (ch == '[') { // Start of parameter block
      currently_parsing = TYPE_SECTION;
    } else if (ch == ']') { // End of parameter block
      done = TRUE;
    } else if (ch == ':') { // Start of name section or range section
      if (currently_parsing == NAME_SECTION || currently_parsing == DEFAULT_SECTION)
        currently_parsing = RANGE_SECTION;
      else
        currently_parsing = NAME_SECTION;
    } else if (ch == '=') { // Start of default section
      if (currently_parsing == NAME_SECTION)
        currently_parsing = DEFAULT_SECTION;
    } else { // It is just a character, so parse it appropriately
      switch (currently_parsing) {
      case NO_SECTION:
        break;
      case TYPE_SECTION:
        if (param_type_char == -1)
          param_type_char = ch;
        break;
      case NAME_SECTION:
        name_text += ch;
        break;
      case DEFAULT_SECTION:
        default_text += ch;
        break;
      case RANGE_SECTION:
        range_text += ch;
        break;
      }
    }

    // Get the next character
    line++;
  }

  // If end of line reached before end of block, return an error value
  if (!done)
    return (-1);

  // Otherwise, return what was found
  return (ConvertParamCharToType(param_type_char));
}

#define RANGE_START_NUM 0
#define RANGE_END_NUM 1

// Returns TRUE if the given integer is in the given range, FALSE otherwise
bool CDallasMainDlg::VerifyIntegerRange(int value, char *range_desc) {
  CString num_text;
  int range_start = 0, range_end = 0;

  bool value_in_range = FALSE;
  int currently_parsing = RANGE_START_NUM;
  while ((*range_desc) != '\0') {

    char ch = (*range_desc);
    if (ch == ',') {
      if (currently_parsing == RANGE_START_NUM) {
        range_start = atoi(num_text.GetBuffer(0));
        if (value == range_start)
          value_in_range = TRUE;
      } else {
        range_end = atoi(num_text.GetBuffer(0));
        if (value >= range_start && value <= range_end)
          value_in_range = TRUE;
      }
      num_text = "";
      range_start = 0;
      range_end = 0;
      currently_parsing = RANGE_START_NUM;
    } else if (ch == '|') {
      currently_parsing = RANGE_END_NUM;
      range_start = atoi(num_text.GetBuffer(0));
      num_text = "";
    } else {
      num_text += ch;
    }

    range_desc++;
  }

  // Check the last value range
  if (currently_parsing == RANGE_START_NUM) {
    range_start = atoi(num_text.GetBuffer(0));
    if (value == range_start)
      value_in_range = TRUE;
  } else {
    range_end = atoi(num_text.GetBuffer(0));
    if (value >= range_start && value <= range_end)
      value_in_range = TRUE;
  }

  return (value_in_range);
}

// Returns TRUE if the given float is in the given range, FALSE otherwise
bool CDallasMainDlg::VerifyFloatRange(float value, char *range_desc) {
  CString num_text;
  float range_start = 0.0, range_end = 0.0;

  bool value_in_range = FALSE;
  int currently_parsing = RANGE_START_NUM;
  while ((*range_desc) != '\0') {

    char ch = (*range_desc);
    if (ch == ',') {
      if (currently_parsing == RANGE_START_NUM) {
        range_start = atof(num_text.GetBuffer(0));
        if (value == range_start)
          value_in_range = TRUE;
      } else {
        range_end = atof(num_text.GetBuffer(0));
        if (value >= range_start && value <= range_end)
          value_in_range = TRUE;
      }
      num_text = "";
      range_start = 0.0;
      range_end = 0.0;
      currently_parsing = RANGE_START_NUM;
    } else if (ch == '|') {
      currently_parsing = RANGE_END_NUM;
      range_start = atof(num_text.GetBuffer(0));
      num_text = "";
    } else {
      num_text += ch;
    }

    range_desc++;
  }

  // Check the last value range
  if (currently_parsing == RANGE_START_NUM) {
    range_start = atof(num_text.GetBuffer(0));
    if (value == range_start)
      value_in_range = TRUE;
  } else {
    range_end = atof(num_text.GetBuffer(0));
    if (value >= range_start && value <= range_end)
      value_in_range = TRUE;
  }

  return (value_in_range);
}

/////////////////////////////////////////////////////////////////////////////
// Script Grouping Functions
/////////////////////////////////////////////////////////////////////////////

// Initializes the script grouping list for use
void CDallasMainDlg::InitScriptGroupingList(void) {
  m_ScriptGroupingList = NULL;
  m_NumScriptGroups = 0;
}

// Deletes memory allocated for the Script Grouping list
void CDallasMainDlg::ClearScriptGroupingList(void) {
  int j, k;

  // Free up all the individual script node lists
  for (j = 0; j < m_NumScriptGroups; j++) {
    for (k = 0; k < MAX_EVENT_TYPES; k++) {
      tEventSection *event_section = &m_ScriptGroupingList[j].event_sections[k];
      if (event_section->num_script_nodes > 0) {
        mem_free(event_section->script_node_list);
        event_section->script_node_list = NULL;
        event_section->num_script_nodes = 0;
      }
    }
  }

  // Free up the entire script grouping list
  if (m_NumScriptGroups > 0) {
    mem_free(m_ScriptGroupingList);
    m_ScriptGroupingList = NULL;
    m_NumScriptGroups = 0;
  }
}

// Adds the node into the appropriate event section of the owner group
int CDallasMainDlg::AddNodeToScriptOwnerGroup(int pos, HTREEITEM script_node) {
  HTREEITEM event_node;
  tTreeNodeData *event_data;
  int event_type;

  // Make sure pos is valid
  if (pos < 0 || pos >= m_NumScriptGroups)
    return FALSE;

  // Get the event type
  event_node = GetScriptEventNode(script_node);
  if (event_node == NULL)
    return FALSE;
  event_data = (tTreeNodeData *)m_ScriptTree.GetItemData(event_node);
  if (event_data == NULL)
    return FALSE;
  event_type = event_data->ID;

  // Make sure event type is valid
  if (event_type < 0 || event_type >= MAX_EVENT_TYPES)
    return FALSE;

  tEventSection *event_section = &m_ScriptGroupingList[pos].event_sections[event_type];

  // Add this node to the appropriate event section list
  if (event_section->num_script_nodes == 0)
    event_section->script_node_list = (HTREEITEM *)mem_malloc(sizeof(HTREEITEM) * 1);
  else
    event_section->script_node_list = (HTREEITEM *)mem_realloc(
        event_section->script_node_list, sizeof(HTREEITEM) * (event_section->num_script_nodes + 1));

  if (event_section->script_node_list == NULL)
    return FALSE;
  event_section->num_script_nodes++;

  int new_pos = event_section->num_script_nodes - 1;
  event_section->script_node_list[new_pos] = script_node;

  return TRUE;
}

// Categorizes the given node into the grouping list
int CDallasMainDlg::AddNodeToScriptGroupingList(HTREEITEM script_node) {
  HTREEITEM owner_node;
  tTreeNodeData *data, *owner_data;
  int j;

  // Make sure it's a script header node
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
  if (data == NULL || data->type != SCRIPT_HEADER_NODE)
    return FALSE;

  // Get the owner node data
  owner_node = GetScriptOwnerNode(script_node);
  if (owner_node == NULL)
    return FALSE;
  owner_data = (tTreeNodeData *)m_ScriptTree.GetItemData(owner_node);
  if (owner_data == NULL)
    return FALSE;

  // Search the grouping list for a matching owner group
  for (j = 0; j < m_NumScriptGroups; j++) {
    if (m_ScriptGroupingList[j].owner_type != owner_data->ID)
      continue;

    // If it's not a LEVEL owner, we need to make sure the handles also match
    if (m_ScriptGroupingList[j].owner_type != LEVEL_TYPE) {
      if (m_ScriptGroupingList[j].owner_handle != owner_data->int_val)
        continue;
    }

    return (AddNodeToScriptOwnerGroup(j, script_node));
  }

  // Since owner does not exist, create a new Script Group entry
  if (m_NumScriptGroups == 0)
    m_ScriptGroupingList = (tScriptOwnerGroup *)mem_malloc(sizeof(tScriptOwnerGroup) * 1);
  else
    m_ScriptGroupingList =
        (tScriptOwnerGroup *)mem_realloc(m_ScriptGroupingList, sizeof(tScriptOwnerGroup) * (m_NumScriptGroups + 1));

  if (m_ScriptGroupingList == NULL)
    return FALSE;
  m_NumScriptGroups++;

  // Initialize the new entry
  int new_pos = m_NumScriptGroups - 1;
  m_ScriptGroupingList[new_pos].owner_type = owner_data->ID;
  m_ScriptGroupingList[new_pos].owner_handle = owner_data->int_val;
  for (j = 0; j < MAX_EVENT_TYPES; j++) {
    m_ScriptGroupingList[new_pos].event_sections[j].num_script_nodes = 0;
    m_ScriptGroupingList[new_pos].event_sections[j].script_node_list = NULL;
  }

  // Now add it officially to the grouping list
  return (AddNodeToScriptOwnerGroup(new_pos, script_node));
}

// Adds every script from the tree to the Grouping List
int CDallasMainDlg::BuildScriptGroupingList(void) {
  HTREEITEM script_header_node;

  // Clear the grouping list first
  ClearScriptGroupingList();

  // Group each script header node into the list
  script_header_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_header_node != NULL) {
    AddNodeToScriptGroupingList(script_header_node);
    script_header_node = m_ScriptTree.GetNextSiblingItem(script_header_node);
  }

  return TRUE;
}

// Creates an ID constant name for a given owner node
char *CDallasMainDlg::CreateScriptConstantName(int pos) {
  static CString name = "";

  if (pos < 0 || pos >= m_NumScriptGroups)
    return (name.GetBuffer(0));

  tScriptOwnerGroup *owner_group = &m_ScriptGroupingList[pos];

  switch (owner_group->owner_type) {
  case OBJECT_TYPE:
    name.Format("ID_CUSTOM_OBJECT_%04X", owner_group->owner_handle);
    break;
  case TRIGGER_TYPE:
    name.Format("ID_TRIGGER_%04X", owner_group->owner_handle);
    break;
  case LEVEL_TYPE:
    name.Format("%s", LEVEL_ID_NAME);
    break;
  default:
    name.Format("ID_ILLEGAL_SCRIPT_TYPE");
    break;
  }

  return (name.GetBuffer(0));
}

// Creates a Class name for a given owner node
char *CDallasMainDlg::CreateScriptClassName(int pos) {
  static CString name = "";

  if (pos < 0 || pos >= m_NumScriptGroups)
    return (name.GetBuffer(0));

  tScriptOwnerGroup *owner_group = &m_ScriptGroupingList[pos];

  switch (owner_group->owner_type) {
  case OBJECT_TYPE:
    name.Format("CustomObjectScript_%04X", owner_group->owner_handle);
    break;
  case TRIGGER_TYPE:
    name.Format("TriggerScript_%04X", owner_group->owner_handle);
    break;
  case LEVEL_TYPE:
    name.Format("%s", LEVEL_CLASS_NAME);
    break;
  default:
    name.Format("IllegalScriptType");
    break;
  }

  return (name.GetBuffer(0));
}

// Creates a Class name for a given owner node
char *CDallasMainDlg::CreateScriptGlobalCtrName(int ID) {
  static CString name = "";

  if (ID < 0)
    return (name.GetBuffer(0));

  name.Format("ScriptActionCtr_%03d", ID);

  return (name.GetBuffer(0));
}

/////////////////////////////////////////////////////////////////////////////
// Parsing Functions
/////////////////////////////////////////////////////////////////////////////

CString CurrentParsingFilename = "<FilenameNotSet>";

// Handle Parse Errors
void CDallasMainDlg::ScriptFileParseError(int error_code, int linenum, int script_ID, const char *name) {
  CString err_msg;

  switch (error_code) {
  case UEOS_ERR:
    err_msg.Format("ERROR: Unexpected end of file while parsing %s, line %d.", CurrentParsingFilename.GetBuffer(0),
                   linenum);
    break;
  case INVALID_FUNC_ERR:
    err_msg.Format("ERROR: An invalid glue function name (%s) was encountered in %s, line %d.\n\n"
                   "Hence, Script #%d now contains an invalid action or query that must be replaced.",
                   name, CurrentParsingFilename.GetBuffer(0), linenum, script_ID);
    break;
  case INVALID_NODE_ERR:
    err_msg.Format("ERROR: An invalid script node was encountered in %s, line %d.\n\n."
                   "Because this node could not be added, one or more of your scripts may be corrupt.",
                   CurrentParsingFilename.GetBuffer(0), linenum);
    break;
  case MODIFIED_FUNC_ERR:
    err_msg.Format("ERROR: A glue function (%s) with out of date parameters was encountered in %s, line %d.\n\n"
                   "Hence, Script #%d now contains an action or query that may need to be modified.",
                   name, CurrentParsingFilename.GetBuffer(0), linenum, script_ID);
    break;
  case INVALID_MSGID_ERR:
    err_msg.Format("ERROR: An invalid Message ID (%s) was encountered in %s, line %d.\n\n"
                   "Hence, Script #%d now contains a Message ID that needs to be replaced.",
                   name, CurrentParsingFilename.GetBuffer(0), linenum, script_ID);
    break;
  default:
    err_msg.Format("ERROR: An unknown error was detected in %s, line %d", CurrentParsingFilename.GetBuffer(0), linenum);
    break;
  }

  MessageBox(err_msg, "Script File Parse Error", MB_OK | MB_ICONEXCLAMATION);
}

// Reads in the script source file and calls the various parsers for the
// Appropriate sections
int CDallasMainDlg::ParseSourceScript(char *filename) {
  CFILE *infile;
  char linebuf[2048];
  char tempbuf[256];
  char *line;
  int linenum;
  int valid_lines_read, version;
  char fullpath[_MAX_PATH];
  int rc;

  HTREEITEM last_node_added, current_parent, returned_node;
  bool skip_children;
  int skip_depth;
  bool last_node_childless;

  CurrentParsingFilename = m_ScriptFilename;

  ddio_MakePath(fullpath, LocalScriptDir, filename, NULL);

  // Try to open the file for loading
  infile = cfopen(fullpath, "rt");
  if (!infile) {
    CString msg;
    msg.Format("Unable to open \"%s\"!", filename);
    MessageBox(msg, "No Script Source File Found!", MB_OK | MB_ICONEXCLAMATION);

    // Clear out the Script Tree
    ClearTree();

    // Add the clipboard node
    CreateDefaultClipboardNode();

    return FALSE;
  }

  linenum = 0;

  // Read in and parse each line of the file
  while (!cfeof(infile)) {

    // Clear the buffer
    strcpy(linebuf, "");

    // Read in a line from the file
    cf_ReadString(linebuf, sizeof(linebuf), infile);
    linenum++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(linebuf);
    line = SkipInitialWhitespace(linebuf);

    // Check for Start of Script Block Section
    if (strncmp(line, SCRIPT_BLOCK_START_TAG, strlen(SCRIPT_BLOCK_START_TAG)) == 0) {
      bool done = false;

      // Clear out the Script Tree
      ClearTree();

      // Clear out the name lists
      ClearNameLists();

      // Set valid line counter to track whether we're reading header info or tree nodes
      valid_lines_read = 0;

      // Set tree node trackers so we know where we are in the actual tree
      last_node_added = NULL;
      current_parent = TVI_ROOT;

      // Set variables that allow child nodes to be skipped over
      // when a bad Action or Query node is read in (invalid function name)
      skip_children = FALSE;
      skip_depth = 0;
      last_node_childless = FALSE;

      // Read all the lines in the block
      while (!done && !cfeof(infile)) {

        strcpy(linebuf, "");
        cf_ReadString(linebuf, sizeof(linebuf), infile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        // If it's an empty line or a comment, skip it
        if (strlen(line) == 0 || strncmp(line, "//", 2) == 0)
          continue;

        // Check for End of Script Block Section
        if (strncmp(line, SCRIPT_BLOCK_END_TAG, strlen(SCRIPT_BLOCK_END_TAG)) == 0) {
          done = true;
          continue;
        }

        // Check for Start of User Type values
        if (strncmp(line, USERTYPE_VALS_START_TAG, strlen(USERTYPE_VALS_START_TAG)) == 0) { // Parse a user type block
          tEnumDBEntry *enum_entry;
          char *enum_name;
          int DBslot;
          bool end_of_usertype_found;

          enum_entry = NULL;

          // Strip off the name of this enumeration type
          enum_name = strtok(line, WHITESPACE_CHARS);
          if (enum_name != NULL)
            enum_name = strtok(NULL, "");
          if (enum_name != NULL && (DBslot = GetEnumID(enum_name)) != INVALID_ENUM) {
            enum_entry = &m_EnumDatabase[DBslot];
          }

          // Parse the enumeration values for this user type
          end_of_usertype_found = FALSE;
          do {

            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, USERTYPE_VALS_END_TAG, strlen(USERTYPE_VALS_END_TAG)) == 0)
              end_of_usertype_found = TRUE;
            else if (enum_entry != NULL) {
              tEnumValueEntry *value_entry;
              int enum_value;
              char *enum_value_string;
              char *enum_value_name;

              // Parse out the enum value and value name
              enum_value_string = strtok(line, ":");
              if (enum_value_string != NULL) {
                enum_value = atoi(enum_value_string);
                enum_value_name = strtok(NULL, "");
              }

              if (enum_value_string == NULL || enum_value_name == NULL ||
                  GetEnumValueName(enum_entry->name, enum_value) != NULL) {
                value_entry = NULL;
              } else if (enum_entry->num_values >= MAX_ENUM_VALUES ||
                         enum_entry->num_values >= (enum_entry->max_values + 2)) {
                value_entry = NULL;
              } else {
                value_entry = &enum_entry->values[enum_entry->num_values++];
                value_entry->name = (char *)mem_malloc(strlen(enum_value_name) + 1);
                if (value_entry->name == NULL) {
                  FunctionFileParseError(NO_MEM_ERR, linenum, filename);
                  cfclose(infile);
                  return FALSE;
                }
                strcpy(value_entry->name, enum_value_name);
                value_entry->value = enum_value;
              }
            }

          } while (!end_of_usertype_found && !cfeof(infile));

          continue;
        }

        // Check for Door List Block, and read it in
        if (strncmp(line, DOOR_LIST_START_TAG, strlen(DOOR_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, DOOR_LIST_END_TAG, strlen(DOOR_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddDoorToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Object List Block, and read it in
        if (strncmp(line, OBJECT_LIST_START_TAG, strlen(OBJECT_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, OBJECT_LIST_END_TAG, strlen(OBJECT_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddObjectToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Room List Block, and read it in
        if (strncmp(line, ROOM_LIST_START_TAG, strlen(ROOM_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, ROOM_LIST_END_TAG, strlen(ROOM_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddRoomToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Trigger List Block, and read it in
        if (strncmp(line, TRIGGER_LIST_START_TAG, strlen(TRIGGER_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, TRIGGER_LIST_END_TAG, strlen(TRIGGER_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddTriggerToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Sound List Block, and read it in
        if (strncmp(line, SOUND_LIST_START_TAG, strlen(SOUND_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, SOUND_LIST_END_TAG, strlen(SOUND_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddSoundToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Texture List Block, and read it in
        if (strncmp(line, TEXTURE_LIST_START_TAG, strlen(TEXTURE_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, TEXTURE_LIST_END_TAG, strlen(TEXTURE_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddTextureToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Specname List Block, and read it in
        if (strncmp(line, SPECNAME_LIST_START_TAG, strlen(SPECNAME_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, SPECNAME_LIST_END_TAG, strlen(SPECNAME_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddSpecnameToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Path List Block, and read it in
        if (strncmp(line, PATH_LIST_START_TAG, strlen(PATH_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, PATH_LIST_END_TAG, strlen(PATH_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddPathToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Matcen List Block, and read it in
        if (strncmp(line, MATCEN_LIST_START_TAG, strlen(MATCEN_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, MATCEN_LIST_END_TAG, strlen(MATCEN_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddMatcenToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for Goal List Block, and read it in
        if (strncmp(line, GOAL_LIST_START_TAG, strlen(GOAL_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, GOAL_LIST_END_TAG, strlen(GOAL_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddGoalToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Check for StrmAudio List Block, and read it in
        if (strncmp(line, STRM_AUDIO_LIST_START_TAG, strlen(STRM_AUDIO_LIST_START_TAG)) == 0) {
          bool end_list_found = 0;
          do {
            cf_ReadString(linebuf, sizeof(linebuf), infile);
            linenum++;

            // Remove whitespace padding at start and end of line
            RemoveTrailingWhitespace(linebuf);
            line = SkipInitialWhitespace(linebuf);

            if (strncmp(line, STRM_AUDIO_LIST_END_TAG, strlen(STRM_AUDIO_LIST_END_TAG)) == 0)
              end_list_found = TRUE;
            else if (strlen(line) > 0)
              AddStrmAudioToList(line);

          } while (!end_list_found && !cfeof(infile));

          continue;
        }

        // Is it the start of a child block?
        if (strncmp(line, CHILD_BLOCK_START_TAG, strlen(CHILD_BLOCK_START_TAG)) == 0) {
          last_node_childless = FALSE;
          if (!skip_children) {
            current_parent = last_node_added;
            if (current_parent == NULL)
              current_parent = TVI_ROOT;
          } else {
            skip_depth++;
          }
          continue;
        }

        // Handles Validation of childless function nodes
        if (last_node_added != NULL && last_node_childless) {
          ValidateFunctionNode(last_node_added, linenum);

          // Need this to update node text that depends on subnodes
          UpdateNodeText(last_node_added);

          last_node_childless = FALSE;
        }

        // Is it the end of a child block?
        if (strncmp(line, CHILD_BLOCK_END_TAG, strlen(CHILD_BLOCK_END_TAG)) == 0) {
          if (!skip_children || skip_depth <= 0) {

            skip_children = FALSE;
            skip_depth = 0;

            last_node_added = current_parent;
            if (last_node_added == TVI_ROOT)
              last_node_added = NULL;
            else {
              // Need this to validate a function node once all of its params have been added
              ValidateFunctionNode(last_node_added, linenum);

              // Need this to update node text that depends on subnodes
              UpdateNodeText(last_node_added);
            }

            if (current_parent != TVI_ROOT)
              current_parent = m_ScriptTree.GetParentItem(current_parent);
            if (current_parent == NULL)
              current_parent = TVI_ROOT;
          } else
            skip_depth--;

          continue;
        }

        // If we're skipping children, but the depth is still zero here,
        // then must not be any children to skip!
        if (skip_children && skip_depth <= 0) {
          skip_children = FALSE;
          skip_depth = 0;
        }

        // See if it should be the save version line
        if (valid_lines_read == 0) {
          rc = sscanf(line, "%s %d", tempbuf, &version);
          if (rc == 2 && strcmp(tempbuf, "VERSION") == 0)
            valid_lines_read++;
          continue;
        }

        // See if it should be the next script ID line
        if (valid_lines_read == 1) {
          rc = sscanf(line, "%s %d", tempbuf, &m_NextScriptID);
          if (rc == 2 && strcmp(tempbuf, "NEXT_ID") == 0)
            valid_lines_read++;
          continue;
        }

        // It must be a node then,
        // so (if we're not skipping children) parse it and add it to the tree
        if (!skip_children) {
          if (version >= 1)
            returned_node = ParseScriptNodeLine_v1U(line, linenum, current_parent, skip_children, version);
          else
            returned_node = ParseScriptNodeLine_v0(line, linenum, current_parent, skip_children);

          if (returned_node != NULL) {
            last_node_added = returned_node;
            last_node_childless = TRUE;
            UpdateNodeText(last_node_added);
          } else
            ScriptFileParseError(INVALID_NODE_ERR, linenum, 0, NULL);

          if (returned_node == NULL || skip_children) {
            skip_children = TRUE;
            skip_depth = 0;
          }
        }
      }

      if (!done)
        ScriptFileParseError(UEOS_ERR, linenum, 0, NULL);
    }
  }

  cfclose(infile);

  // Add the clipboard node
  CreateDefaultClipboardNode();

  return TRUE;
}

// VERSION 0: Parses a script node line, and if it's valid, adds it to the given parent
HTREEITEM CDallasMainDlg::ParseScriptNodeLine_v0(char *line, int linenum, HTREEITEM parent, bool &skip_all_children,
                                                 HTREEITEM insert_before /*=TVI_LAST*/) {
  tTreeNodeData node_data;
  bool add_node;
  int index;

  // Make sure given data is ok
  if (line == NULL || parent == NULL || skip_all_children)
    return NULL;

  // Read in the node type
  line = strtok(line, ":");
  if (line == NULL)
    return NULL;
  node_data.type = atoi(line);

  // Read in the rest of this node's data
  add_node = FALSE;
  switch (node_data.type) {
  case SCRIPT_HEADER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    strcpy(node_data.name, line);
    add_node = TRUE;
    break;
  case SCRIPT_OWNER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.int_val = atoi(line);

    // Verify object name
    if (node_data.ID == OBJECT_TYPE) {
      object *objp = ObjGet(node_data.int_val);
      if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
        node_data.int_val = OBJECT_HANDLE_NONE;
        strcpy(node_data.str_val, "");
      } else {
        strcpy(node_data.str_val, objp->name);
      }
    }

    // Verify trigger name
    if (node_data.ID == TRIGGER_TYPE) {
      int t = node_data.int_val;
      if (t < 0 || t >= Num_triggers || t >= MAX_NAMED_TRIGGERS || strlen(Triggers[t].name) == 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      } else {
        strcpy(node_data.str_val, Triggers[t].name);
      }
    }

    add_node = TRUE;
    break;
  case SCRIPT_EVENT_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case CONDITIONAL_HEADER_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case ACTIONS_HEADER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.subID = atoi(line);
    add_node = TRUE;
    break;
  case CONDITIONAL_STATEMENT_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case EXPRESSION_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = GetQueryFuncID(line);
    if (node_data.ID == INVALID_FUNCTION_ID) {
      ScriptFileParseError(INVALID_FUNC_ERR, linenum, GetScriptID(parent), line);
      skip_all_children = TRUE;
    }
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    strcpy(node_data.name, line);
    add_node = TRUE;
    break;
  case EXPRESSION_OPERATOR_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.subID = atoi(line);
    add_node = TRUE;
    break;
  case ACTION_STATEMENT_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = GetActionFuncID(line);
    if (node_data.ID == INVALID_FUNCTION_ID) {
      ScriptFileParseError(INVALID_FUNC_ERR, linenum, GetScriptID(parent), line);
      skip_all_children = TRUE;
    }
    add_node = TRUE;
    break;
  case LOGICAL_OPERATOR_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case PARAMETER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);

    // Get param data based upon what kind of parameter it is
    switch (node_data.ID) {
    case DOOR_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      // Verify door name
      if (node_data.subID == USE_OBJECT_HANDLE) {
        object *objp = ObjGet(node_data.int_val);
        if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
          node_data.int_val = OBJECT_HANDLE_NONE;
          strcpy(node_data.str_val, "");
        } else {
          strcpy(node_data.str_val, objp->name);
        }
      }

      add_node = TRUE;
      break;
    case OBJECT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      // Verify object name
      if (node_data.subID == USE_OBJECT_HANDLE) {
        object *objp = ObjGet(node_data.int_val);
        if (objp == NULL || objp->type == OBJ_NONE || objp->name == NULL) {
          node_data.int_val = OBJECT_HANDLE_NONE;
          strcpy(node_data.str_val, "");
        } else {
          strcpy(node_data.str_val, objp->name);
        }
      }

      add_node = TRUE;
      break;
    case ROOM_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      // Verify room name
      index = node_data.int_val;
      if (index < 0 || index > Highest_room_index || !Rooms[index].used || Rooms[index].name == NULL) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      } else {
        strcpy(node_data.str_val, Rooms[index].name);
      }

      add_node = TRUE;
      break;
    case TRIGGER_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      // Verify trigger name
      index = node_data.int_val;
      if (index < 0 || index >= Num_triggers || index >= MAX_NAMED_TRIGGERS || strlen(Triggers[index].name) == 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      } else {
        strcpy(node_data.str_val, Triggers[index].name);
      }

      add_node = TRUE;
      break;
    case INT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case BOOL_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case FLOAT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val1 = atof(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case VECTOR_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val1 = atof(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val2 = atof(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val3 = atof(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case STRING_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      strcpy(node_data.str_val, line);
      if (FindMessageInList(line) == NULL) {
        strcpy(node_data.str_val, "");
        if (strcmp(line, NOT_SPECIFIED_MSG) != 0)
          ScriptFileParseError(INVALID_MSGID_ERR, linenum, GetScriptID(parent), line);
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case PERCENTAGE_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val1 = atof(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case ENUM_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case SCRIPT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case SOUND_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if (index < 0 || index >= m_SoundListSize)
        node_data.int_val = -1;
      else
        node_data.int_val = FindSoundName(m_SoundList[atoi(line)]);

      if (node_data.int_val < 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");

        // Display warning message here...
      } else {
        strcpy(node_data.str_val, m_SoundList[atoi(line)]);
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case SPECNAME_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      strcpy(node_data.str_val, line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case TEXTURE_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if (index < 0 || index >= m_TextureListSize)
        node_data.int_val = -1;
      else
        node_data.int_val = FindTextureName(m_TextureList[atoi(line)]);

      if (node_data.int_val < 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");

        // Display warning message here...
      } else {
        strcpy(node_data.str_val, m_TextureList[atoi(line)]);
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case FLAG_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case PATH_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if (index < 0 || index >= m_PathListSize)
        node_data.int_val = -1;
      else
        node_data.int_val = osipf_FindPathName(m_PathList[index]);

      if (node_data.int_val < 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");

        // Display warning message here...
      } else {
        strcpy(node_data.str_val, m_PathList[index]);
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case MATCEN_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if (index < 0 || index >= m_MatcenListSize)
        node_data.int_val = -1;
      else
        node_data.int_val = osipf_FindMatcenName(m_MatcenList[index]);

      if (node_data.int_val < 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");

        // Display warning message here...
      } else {
        strcpy(node_data.str_val, m_MatcenList[index]);
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case LEVEL_GOAL_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if (index < 0 || index >= m_GoalListSize)
        node_data.int_val = -1;
      else
        node_data.int_val = osipf_FindLevelGoalName(m_GoalList[index]);

      if (node_data.int_val < 0) {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");

        // Display warning message here...
      } else {
        strcpy(node_data.str_val, m_GoalList[index]);
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case STRM_AUDIO_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if (index < 0 || index >= m_StrmAudioListSize || !GamefileExists(m_StrmAudioList[index]))
        strcpy(node_data.str_val, "");
      else {
        strcpy(node_data.str_val, m_StrmAudioList[index]);

        // Display warning message here...
      }
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    default:
      break;
    }
    break;
  case PARAMETER_OPERATOR_NODE:
    break;
  case UNKNOWN_NODE:
    break;
  default:
    break;
  }

  if (add_node)
    return (AddNodeToTree(parent, insert_before, &node_data));

  return NULL;
}

// VERSION 1: Parses a script node line, and if it's valid, adds it to the given parent
HTREEITEM CDallasMainDlg::ParseScriptNodeLine_v1U(char *line, int linenum, HTREEITEM parent, bool &skip_all_children,
                                                  int version, HTREEITEM insert_before /*=TVI_LAST*/) {
  tTreeNodeData node_data;
  bool add_node;
  int index;
  int scriptID;

  // Make sure given data is ok
  if (line == NULL || parent == NULL || skip_all_children)
    return NULL;

  // Determine what script we're in
  scriptID = -1;
  if (parent != TVI_ROOT)
    scriptID = GetScriptID(parent);

  // Read in the node type
  line = strtok(line, ":");
  if (line == NULL)
    return NULL;
  node_data.type = atoi(line);

  // Read in the rest of this node's data
  add_node = FALSE;
  switch (node_data.type) {
  case SCRIPT_HEADER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    strcpy(node_data.name, line);
    add_node = TRUE;
    break;
  case SCRIPT_OWNER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    index = atoi(line);

    if (node_data.ID == OBJECT_TYPE) {
      if (index >= 0 && index < m_ObjectListSize) {
        node_data.int_val = osipf_FindObjectName(m_ObjectList[index]);
        if (node_data.int_val != OBJECT_HANDLE_NONE) {
          strcpy(node_data.str_val, m_ObjectList[index]);
        } else {
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Object Script Owner", m_ObjectList[index]);
        }
      } else {
        node_data.int_val = OBJECT_HANDLE_NONE;
        strcpy(node_data.str_val, "");
      }
    } else if (node_data.ID == TRIGGER_TYPE) {
      if (index >= 0 && index < m_TriggerListSize) {
        node_data.int_val = osipf_FindTriggerName(m_TriggerList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_TriggerList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Trigger Script Owner", m_TriggerList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }
    } else {
      node_data.int_val = index;
      strcpy(node_data.str_val, "");
    }

    add_node = TRUE;
    break;
  case SCRIPT_EVENT_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case CONDITIONAL_HEADER_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case ACTIONS_HEADER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if (version >= 3) {
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
    } else {
      node_data.int_val = CONTINUE_SCRIPT_CHAIN;
    }
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.subID = atoi(line);
    add_node = TRUE;
    break;
  case CONDITIONAL_STATEMENT_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case EXPRESSION_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = GetQueryFuncID(line);
    if (node_data.ID == INVALID_FUNCTION_ID) {
      ScriptFileParseError(INVALID_FUNC_ERR, linenum, scriptID, line);
      skip_all_children = TRUE;
    }
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    strcpy(node_data.name, line);
    add_node = TRUE;
    break;
  case EXPRESSION_OPERATOR_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.subID = atoi(line);
    add_node = TRUE;
    break;
  case ACTION_STATEMENT_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = GetActionFuncID(line);
    if (node_data.ID == INVALID_FUNCTION_ID) {
      ScriptFileParseError(INVALID_FUNC_ERR, linenum, scriptID, line);
      skip_all_children = TRUE;
    }
    add_node = TRUE;
    break;
  case LOGICAL_OPERATOR_NODE:
    if ((line = strtok(NULL, "")) == NULL)
      return NULL;
    node_data.ID = atoi(line);
    add_node = TRUE;
    break;
  case PARAMETER_NODE:
    if ((line = strtok(NULL, ":")) == NULL)
      return NULL;
    node_data.ID = atoi(line);

    // Get param data based upon what kind of parameter it is
    switch (node_data.ID) {
    case DOOR_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (node_data.subID == USE_OBJECT_HANDLE) {
        if (index >= 0 && index < m_DoorListSize) {
          node_data.int_val = osipf_FindDoorName(m_DoorList[index]);
          if (node_data.int_val != OBJECT_HANDLE_NONE) {
            strcpy(node_data.str_val, m_DoorList[index]);
          } else {
            strcpy(node_data.str_val, "");
            SpecialScriptFileParseError(linenum, scriptID, "Door", m_DoorList[index]);
          }
        } else {
          node_data.int_val = OBJECT_HANDLE_NONE;
          strcpy(node_data.str_val, "");
        }
      } else {
        node_data.int_val = OBJECT_HANDLE_NONE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case OBJECT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (node_data.subID == USE_OBJECT_HANDLE) {
        if (index >= 0 && index < m_ObjectListSize) {
          node_data.int_val = osipf_FindObjectName(m_ObjectList[index]);
          if (node_data.int_val != OBJECT_HANDLE_NONE) {
            strcpy(node_data.str_val, m_ObjectList[index]);
          } else {
            strcpy(node_data.str_val, "");
            SpecialScriptFileParseError(linenum, scriptID, "Object", m_ObjectList[index]);
          }
        } else {
          node_data.int_val = OBJECT_HANDLE_NONE;
          strcpy(node_data.str_val, "");
        }
      } else {
        node_data.int_val = OBJECT_HANDLE_NONE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case ROOM_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_RoomListSize) {
        node_data.int_val = osipf_FindRoomName(m_RoomList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_RoomList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Room", m_RoomList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case TRIGGER_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_TriggerListSize) {
        node_data.int_val = osipf_FindTriggerName(m_TriggerList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_TriggerList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Trigger", m_TriggerList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case INT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case BOOL_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case FLOAT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val1 = atof(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case VECTOR_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val1 = atof(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val2 = atof(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val3 = atof(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case STRING_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      strcpy(node_data.str_val, line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (FindMessageInList(node_data.str_val) == NULL) {
        if (strcmp(node_data.str_val, NOT_SPECIFIED_MSG) != 0)
          ScriptFileParseError(INVALID_MSGID_ERR, linenum, scriptID, line);
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case PERCENTAGE_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.float_val1 = atof(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case ENUM_PARAMETER_TYPE:
      if (version >= 2) {
        if ((line = strtok(NULL, ":")) == NULL)
          return NULL;
        node_data.subID = atoi(line);
      } else {
        node_data.subID = USE_ENUM_VALUE;
      }
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case SCRIPT_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case SOUND_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_SoundListSize) {
        node_data.int_val = osipf_FindSoundName(m_SoundList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_SoundList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Sound", m_SoundList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case SPECNAME_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_SpecnameListSize)
        strcpy(node_data.str_val, m_SpecnameList[index]);
      else
        strcpy(node_data.str_val, "");

      add_node = TRUE;
      break;
    case TEXTURE_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_TextureListSize) {
        node_data.int_val = osipf_FindTextureName(m_TextureList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_TextureList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Texture", m_TextureList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case FLAG_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.int_val = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);
      add_node = TRUE;
      break;
    case PATH_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_PathListSize) {
        node_data.int_val = osipf_FindPathName(m_PathList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_PathList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Path", m_PathList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case MATCEN_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_MatcenListSize) {
        node_data.int_val = osipf_FindMatcenName(m_MatcenList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_MatcenList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Matcen", m_MatcenList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case LEVEL_GOAL_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      node_data.subID = atoi(line);
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_GoalListSize) {
        node_data.int_val = osipf_FindLevelGoalName(m_GoalList[index]);
        if (node_data.int_val >= 0) {
          strcpy(node_data.str_val, m_GoalList[index]);
        } else {
          node_data.int_val = NOT_SPECIFIED_TYPE;
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Level Goal", m_GoalList[index]);
        }
      } else {
        node_data.int_val = NOT_SPECIFIED_TYPE;
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    case STRM_AUDIO_PARAMETER_TYPE:
      if ((line = strtok(NULL, ":")) == NULL)
        return NULL;
      index = atoi(line);
      if ((line = strtok(NULL, "")) == NULL)
        return NULL;
      strcpy(node_data.name, line);

      if (index >= 0 && index < m_StrmAudioListSize) {
        if (GamefileExists(m_StrmAudioList[index])) {
          strcpy(node_data.str_val, m_StrmAudioList[index]);
        } else {
          strcpy(node_data.str_val, "");
          SpecialScriptFileParseError(linenum, scriptID, "Streaming Audio File", m_StrmAudioList[index]);
        }
      } else {
        strcpy(node_data.str_val, "");
      }

      add_node = TRUE;
      break;
    default:
      break;
    }
    break;
  case PARAMETER_OPERATOR_NODE:
    break;
  case UNKNOWN_NODE:
    break;
  default:
    break;
  }

  if (add_node)
    return (AddNodeToTree(parent, insert_before, &node_data));

  return NULL;
}

// Handle Special Parse Errors (Invalid Named Values)
void CDallasMainDlg::SpecialScriptFileParseError(int linenum, int script_ID, char *type_name, const char *name) {
  CString err_msg;

  if (name == NULL || type_name == NULL)
    return;

  err_msg.Format("ERROR: An invalid %s (%s) was encountered in %s, line %d.\n\n"
                 "Hence, Script #%d now contains a %s that needs to be replaced.",
                 type_name, name, CurrentParsingFilename.GetBuffer(0), linenum, script_ID, type_name);

  MessageBox(err_msg, "Script File Parse Error", MB_OK | MB_ICONEXCLAMATION);
}

// Validates a function node by conforming its parameters to what they should be
// returns FALSE if node was modified significantly, otherwise TRUE
bool CDallasMainDlg::ValidateFunctionNode(HTREEITEM node, int linenum) {
  tTreeNodeData *data;

  if (node == NULL)
    return TRUE;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return TRUE;

  if (data->type == EXPRESSION_NODE)
    return (ValidateQueryNode(node, linenum));
  if (data->type == ACTION_STATEMENT_NODE)
    return (ValidateActionNode(node, linenum));

  return TRUE;
}

// Reads in the message list from a file
int CDallasMainDlg::ParseMsgTableFile(char *filename) {
  CFILE *infile;
  char filebuffer[MAX_MSG_FILE_BUFFER_LEN];
  char *line, *msg_start;
  int line_num;
  bool next_msgid_found;
  char fullpath[_MAX_PATH];

  ddio_MakePath(fullpath, LocalScriptDir, filename, NULL);

  // Try to open the file for loading
  infile = cfopen(fullpath, "rt");
  if (!infile) {
    CString msg;
    msg.Format("Unable to open \"%s\"!", filename);
    MessageBox(msg, "Script Message File Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  line_num = 0;
  next_msgid_found = FALSE;

  // Read in and parse each line of the file
  while (!cfeof(infile)) {

    // Clear the buffer
    strcpy(filebuffer, "");

    // Read in a line from the file
    cf_ReadString(filebuffer, MAX_MSG_FILE_BUFFER_LEN, infile);
    line_num++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(filebuffer);
    line = SkipInitialWhitespace(filebuffer);

    // If line is a comment, or empty, discard it
    if (strlen(line) == 0 || strncmp(line, "//", 2) == 0)
      continue;

    if (!next_msgid_found) { // Parse out the last message ID number

      // Grab the first keyword, make sure it's valid
      line = strtok(line, WHITESPACE_CHARS);
      if (line == NULL || strcmp(line, NEXT_MSG_ID_NUM_KEYWORD) != 0)
        continue;

      // Grab the second keyword, and assign it as the next message ID
      line = strtok(NULL, WHITESPACE_CHARS);
      if (line == NULL)
        continue;
      m_NextMessageID = atoi(line);

      next_msgid_found = TRUE;
    } else { // Parse line as a message line

      // Find the start of message, and mark it
      msg_start = strchr(line, '=');
      if (msg_start == NULL)
        continue;
      msg_start[0] = '\0';
      msg_start++;

      // Add the message to the list
      AddToMessageList(line, msg_start);
    }
  }

  cfclose(infile);

  return TRUE;
}

///////////////////////////////////
// Custom Script Block Functions
///////////////////////////////////

// Initializes the data storage space
void CDallasMainDlg::InitCustomScriptStorage(void) {
  m_CustomScriptLines = NULL;

  m_NumCustomScriptLines = 0;
  m_MaxNumCustomScriptLines = 0;
}

// Clears any memory allocated for storage
void CDallasMainDlg::ClearCustomScriptStorage(void) {
  // Clear all the lines
  for (int j = 0; j < m_NumCustomScriptLines; j++) {
    mem_free(m_CustomScriptLines[j]);
    m_CustomScriptLines[j] = NULL;
  }

  // Clear the array of line pointers
  if (m_CustomScriptLines != NULL) {
    mem_free(m_CustomScriptLines);
    m_CustomScriptLines = NULL;
  }

  m_NumCustomScriptLines = 0;
  m_MaxNumCustomScriptLines = 0;
}

// Scans the file for the custom script block and count how many lines are in it
int CDallasMainDlg::CountCustomScriptLines(CFILE *infile) {
  int32_t start_pos;
  int line_count;
  char linebuf[2048];
  bool done;

  line_count = 0;
  done = false;

  // Save the current file position
  start_pos = cftell(infile);

  // Read all the lines in the block
  while (!done && !cfeof(infile)) {

    strcpy(linebuf, "");
    cf_ReadString(linebuf, sizeof(linebuf), infile);

    // Check for End of Script Block Section
    if (strncmp(linebuf, CUSTOM_SCRIPT_BLOCK_END_TAG, strlen(CUSTOM_SCRIPT_BLOCK_END_TAG)) == 0) {
      done = true;
      continue;
    }

    // If it's not the end of custom block tag, then it's a line we need to save
    line_count++;
  }

  // Move file pointer back to the original starting position
  cfseek(infile, start_pos, SEEK_SET);

  return (line_count);
}

// Reads in and stores all the lines in the custom script block
int CDallasMainDlg::ParseCustomScriptFile(char *filename, bool show_errors /*=TRUE*/) {
  CFILE *infile;
  char linebuf[2048];
  char *line;
  int linenum;
  char fullpath[_MAX_PATH];

  CurrentParsingFilename = m_ScriptFilename;

  ddio_MakePath(fullpath, LocalScriptDir, filename, NULL);

  // Try to open the file for loading
  infile = cfopen(fullpath, "rt");
  if (!infile) {
    if (show_errors) {
      CString msg;
      msg.Format("Unable to open \"%s\"!", filename);
      MessageBox(msg, "No Custom Script Source File Found!", MB_OK | MB_ICONEXCLAMATION);
    }
    return FALSE;
  }

  linenum = 0;

  // Read in and parse each line of the file
  while (!cfeof(infile)) {

    // Clear the buffer
    strcpy(linebuf, "");

    // Read in a line from the file
    cf_ReadString(linebuf, sizeof(linebuf), infile);
    linenum++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(linebuf);
    line = SkipInitialWhitespace(linebuf);

    // Check for Start of Script Block Section
    if (strncmp(line, CUSTOM_SCRIPT_BLOCK_START_TAG, strlen(CUSTOM_SCRIPT_BLOCK_START_TAG)) == 0) {
      bool done = false;
      bool warning_issued = false;

      // Count the number of lines in the file, and allocate room for them
      ClearCustomScriptStorage();
      m_MaxNumCustomScriptLines = CountCustomScriptLines(infile);
      if (m_MaxNumCustomScriptLines > 0) {
        m_CustomScriptLines = (char **)mem_malloc(sizeof(char *) * m_MaxNumCustomScriptLines);
        if (m_CustomScriptLines == NULL) {
          MessageBox("ERROR: Ran out of memory allocating custom script block", "Custom Script Parse Error",
                     MB_OK | MB_ICONEXCLAMATION);
          cfclose(infile);
          return FALSE;
        }
      }

      // Read all the lines in the block
      while (!done && !cfeof(infile)) {

        strcpy(linebuf, "");
        cf_ReadString(linebuf, sizeof(linebuf), infile);
        linenum++;

        // Check for End of Script Block Section
        if (strncmp(linebuf, CUSTOM_SCRIPT_BLOCK_END_TAG, strlen(CUSTOM_SCRIPT_BLOCK_END_TAG)) == 0) {
          done = true;
          continue;
        }

        // Store this line
        if (m_NumCustomScriptLines < m_MaxNumCustomScriptLines) {
          m_CustomScriptLines[m_NumCustomScriptLines] = (char *)mem_malloc(strlen(linebuf) + 1);
          if (m_CustomScriptLines[m_NumCustomScriptLines] == NULL) {
            MessageBox("ERROR: Ran out of memory parsing custom script block", "Custom Script Parse Error",
                       MB_OK | MB_ICONEXCLAMATION);
            cfclose(infile);
            return FALSE;
          }
          strcpy(m_CustomScriptLines[m_NumCustomScriptLines], linebuf);
          m_NumCustomScriptLines++;
        } else {
          MessageBox("ERROR: The maximum custom script block line limit has been exceeded.\n\nThe excess lines will "
                     "not be saved.",
                     "Custom Script Parse Error", MB_OK | MB_ICONEXCLAMATION);
          done = TRUE;
        }
      }

      if (!done)
        ScriptFileParseError(UEOS_ERR, linenum, 0, NULL);
    }
  }

  cfclose(infile);

  return TRUE;
}

// Writes out the custom script block
void CDallasMainDlg::WriteCustomScriptBlock(void) {
  if (CurrentOutputFile == NULL)
    return;

  // Create the valid event case statements
  O((" "));
  O(("// ==============================================================="));
  O(("// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS"));
  O(("// ==============================================================="));
  O(("%s", CUSTOM_SCRIPT_BLOCK_START_TAG));

  if (m_NumCustomScriptLines == 0) {
    O((" "));
    O(("// Enter your custom script code here"));
    O((" "));
  } else {
    for (int j = 0; j < m_NumCustomScriptLines; j++)
      O(("%s", m_CustomScriptLines[j]));
  }

  O(("%s", CUSTOM_SCRIPT_BLOCK_END_TAG));
  O(("// ============================================================"));
  O(("// End of Custom Script Block - DO NOT EDIT ANYTHING AFTER THIS"));
  O(("// ============================================================"));
  O((" "));
}

/////////////////////////////////////////////////////////////////////////////
// File Creation Functions
/////////////////////////////////////////////////////////////////////////////

// Writes message list to file
int CDallasMainDlg::CreateMsgTableFile(char *filename) {
  CFILE *outfile;
  CString buffer;
  int count, j;
  tMessageListEntry *msg_data;
  char fullpath[_MAX_PATH];

  ddio_MakePath(fullpath, LocalScriptDir, filename, NULL);

  // Try to open the file for writing
  outfile = cfopen(fullpath, "wt");
  if (!outfile) {
    CString msg;
    msg.Format("Unable to open \"%s\"!", filename);
    MessageBox(msg, "Script Message File Error!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // Write out comment header
  buffer.Format("//////////////////////////////////////////////");
  cf_WriteString(outfile, buffer.GetBuffer(0));
  buffer.Format("// D.A.L.L.A.S. Generated Message Table File");
  cf_WriteString(outfile, buffer.GetBuffer(0));
  buffer.Format("//////////////////////////////////////////////");
  cf_WriteString(outfile, buffer.GetBuffer(0));
  cf_WriteString(outfile, "");

  // Write out the next message ID number
  buffer.Format("%s     %d", NEXT_MSG_ID_NUM_KEYWORD, m_NextMessageID);
  cf_WriteString(outfile, buffer.GetBuffer(0));
  cf_WriteString(outfile, "");

  // Write out the message list comment header
  buffer.Format("// Message List");
  cf_WriteString(outfile, buffer.GetBuffer(0));

  // Write out each message
  count = m_MessageList.GetCount();
  for (j = 0; j < count; j++) {
    msg_data = (tMessageListEntry *)m_MessageList.GetItemData(j);
    if (msg_data) {
      buffer.Format("%s=%s", msg_data->name, msg_data->message);
      cf_WriteString(outfile, buffer.GetBuffer(0));
    }
  }

  cfclose(outfile);

  return TRUE;
}

// Writes out a series of tabs to the CurrentOutputFile
void CDallasMainDlg::TabOver(void) {
  int j;

  if (CurrentOutputFile == NULL)
    return;

  for (j = 0; j < CurrentTabLevel; j++)
    cfprintf(CurrentOutputFile, "\t");
}

// Create the source script CPP file
int CDallasMainDlg::CreateScriptFile(char *filename) {
  char fullpath[_MAX_PATH];
  int j, counter, num_CO_scripts;

  // Fill the name lists (and check for any invalid/not selected fields)
  ClearNameLists();
  if (FillNameListsFromTree(TVI_ROOT, TRUE) != 0) {
    int ret_val;
    ret_val = MessageBox(
        "Due to invalid script data, it is probably unsafe to save and compile.\n\nDo you wish to proceed anyway?",
        "Script Problems Encountered!", MB_YESNO | MB_ICONQUESTION);
    if (ret_val == IDNO)
      return FALSE;
  }

  // Build the organized list of scripts
  BuildScriptGroupingList();

  // Open the file for writing
  ddio_MakePath(fullpath, LocalScriptDir, filename, NULL);
  CurrentOutputFile = cfopen(fullpath, "wt");
  if (CurrentOutputFile == NULL) {
    CString msg, title;
    msg.Format("ERROR: Unable to open %s for output.", fullpath);
    title.Format("Script Save Error!");
    MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // Write out the header info
  O(("/////////////////////////////////////////////////////////////////////"));
  O(("// D.A.L.L.A.S. Generated Level Script - DLL Source File"));
  O(("// "));
  O(("// Filename:	%s", filename));
  O(("// Version:	%d", DALLAS_SAVE_VERSION));
  O(("/////////////////////////////////////////////////////////////////////"));
  O(("#include <stdio.h>"));
  O(("#include <stdlib.h>"));
  O(("#include <string.h>"));
  O(("#include <ctype.h>"));
  O(("#include \"osiris_import.h\""));
  O(("#include \"osiris_common.h\""));
  O(("#include \"%s\"", DALLASFUNCS_FILENAME));
  O((""));

  O(("#ifdef _MSC_VER		//Visual C++ Build"));
  O(("#define STDCALL		__stdcall"));
  O(("#define STDCALLPTR	*STDCALL"));
  O(("#else					//Non-Visual C++ Build"));
  O(("#define STDCALL __attribute__((stdcall))"));
  O(("#define STDCALLPTR	STDCALL*"));
  O(("#endif"));
  O((""));

  O(("#ifdef __cplusplus"));
  O(("extern \"C\"{"));
  O(("#endif"));
  O(("char		STDCALL InitializeDLL(tOSIRISModuleInit *func_list);"));
  O(("void		STDCALL ShutdownDLL(void);"));
  O(("int		STDCALL GetGOScriptID(const char *name,uint8_t is_door);"));
  O(("void		STDCALLPTR CreateInstance(int id);"));
  O(("void		STDCALL DestroyInstance(int id,void *ptr);"));
  O(("int16_t	STDCALL CallInstanceEvent(int id,void *ptr,int event,tOSIRISEventInfo *data);"));
  O(("int		STDCALL GetTriggerScriptID(int trigger_room, int trigger_face );"));
  O(("int		STDCALL GetCOScriptList( int **list, int **id_list );"));
  O(("int		STDCALL SaveRestoreState( void *file_ptr, uint8_t saving_state );"));
  O(("#ifdef __cplusplus"));
  O(("}"));
  O(("#endif"));
  O((""));

  // Write out the script ID list
  O(("// ================="));
  O(("// Script ID Numbers"));
  O(("// ================="));

  counter = 0x000;

  // Write out the level ID
  O(("#define %s			0x%03x", LEVEL_ID_NAME, counter++));
  O((""));

  // Write out the custom object ID's (and count the number of custom object scripts)
  num_CO_scripts = 0;
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {
      O(("#define %s		0x%03x", CreateScriptConstantName(j), counter++));
      num_CO_scripts++;
    }
  O((""));

  // Write out the trigger ID's
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE)
      O(("#define %s		0x%03x", CreateScriptConstantName(j), counter++));
  O((""));

  // Write out the base script class definition
  O(("// ========================"));
  O(("// Script Class Definitions"));
  O(("// ========================"));
  O((""));
  O(("class BaseScript {"));
  O(("public:"));
  O(("	BaseScript();"));
  O(("	~BaseScript();"));
  O(("	virtual int16_t CallEvent(int event, tOSIRISEventInfo *data);"));
  O(("};"));
  O((""));

  // Write out the level script class definition
  O(("class %s : public BaseScript {", LEVEL_CLASS_NAME));
  O(("public:"));
  O(("	int16_t CallEvent(int event, tOSIRISEventInfo *data);"));
  O(("};"));
  O((""));

  // Write out the custom object class definitions
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {
      O(("class %s : public BaseScript {", CreateScriptClassName(j)));
      O(("public:"));
      O(("	int16_t CallEvent(int event, tOSIRISEventInfo *data);"));
      O(("};"));
      O((""));
    }

  // Write out the trigger class definitions
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE) {
      O(("class %s : public BaseScript {", CreateScriptClassName(j)));
      O(("public:"));
      O(("	int16_t CallEvent(int event, tOSIRISEventInfo *data);"));
      O(("};"));
      O((""));
    }

  // Write out the global script action counters
  O(("// ======================"));
  O(("// Global Action Counters"));
  O(("// ======================"));
  O((""));
  O(("#define MAX_ACTION_CTR_VALUE		100000"));
  O((""));

  // Loop through all the scripts, write one global for each script
  HTREEITEM script_node;
  tTreeNodeData *data;

  script_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
    if (data != NULL && data->type == SCRIPT_HEADER_NODE) {
      O(("int %s = 0;", CreateScriptGlobalCtrName(data->ID)));
    }
    script_node = m_ScriptTree.GetNextSiblingItem(script_node);
  }
  O((" "));

  O(("// ========================================"));
  O(("// Function to Clear Global Action Counters"));
  O(("// ========================================"));
  O(("void ClearGlobalActionCtrs(void)"));
  O(("{"));

  // Write out the clear script statements
  script_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
    if (data != NULL && data->type == SCRIPT_HEADER_NODE) {
      O(("	%s = 0;", CreateScriptGlobalCtrName(data->ID)));
    }
    script_node = m_ScriptTree.GetNextSiblingItem(script_node);
  }

  O(("}"));
  O((" "));

  O(("// ========================================"));
  O(("// Function to Save Global Action Counters"));
  O(("// ========================================"));
  O(("void SaveGlobalActionCtrs(void *file_ptr)"));
  O(("{"));

  // Write out the clear script statements
  script_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
    if (data != NULL && data->type == SCRIPT_HEADER_NODE) {
      O(("	File_WriteInt(%s,file_ptr);", CreateScriptGlobalCtrName(data->ID)));
    }
    script_node = m_ScriptTree.GetNextSiblingItem(script_node);
  }

  O(("}"));
  O((" "));

  O(("// ==========================================="));
  O(("// Function to Restore Global Action Counters"));
  O(("// ==========================================="));
  O(("void RestoreGlobalActionCtrs(void *file_ptr)"));
  O(("{"));

  // Write out the clear script statements
  script_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
    if (data != NULL && data->type == SCRIPT_HEADER_NODE) {
      O(("	%s=File_ReadInt(file_ptr);", CreateScriptGlobalCtrName(data->ID)));
    }
    script_node = m_ScriptTree.GetNextSiblingItem(script_node);
  }

  O(("}"));
  O((" "));

  // Write out the Custom Script Block
  WriteCustomScriptBlock();
  O((" "));

  O(("// ================="));
  O(("// Message File Data"));
  O(("// ================="));
  O((" "));
  O(("#define MAX_SCRIPT_MESSAGES	256"));
  O(("#define MAX_MSG_FILEBUF_LEN	1024"));
  O(("#define NO_MESSAGE_STRING		\"*Message Not Found*\""));
  O(("#define INV_MSGNAME_STRING	\"*Message Name Invalid*\""));
  O(("#define WHITESPACE_CHARS	\" \\t\\r\\n\""));
  O((" "));
  O(("// Structure for storing a script message"));
  O(("struct tScriptMessage {"));
  O(("	char *name;			// the name of the message"));
  O(("	char *message;		// the actual message text"));
  O(("};"));
  O((" "));
  O(("// Global storage for level script messages"));
  O(("tScriptMessage *message_list[MAX_SCRIPT_MESSAGES];"));
  O(("int num_messages;"));
  O((" "));

  O(("// ======================"));
  O(("// Message File Functions"));
  O(("// ======================"));
  O((" "));
  O(("// Initializes the Message List"));
  O(("void InitMessageList(void)"));
  O(("{"));
  O(("	for(int j=0;j<MAX_SCRIPT_MESSAGES;j++)"));
  O(("		message_list[j]=NULL;"));
  O(("	num_messages=0;"));
  O(("}"));
  O((" "));
  O(("// Clear the Message List"));
  O(("void ClearMessageList(void)"));
  O(("{"));
  O(("	for(int j=0;j<num_messages;j++) {"));
  O(("		free(message_list[j]->name);"));
  O(("		free(message_list[j]->message);"));
  O(("		free(message_list[j]);"));
  O(("		message_list[j]=NULL;"));
  O(("	}"));
  O(("	num_messages=0;"));
  O(("}"));
  O((" "));
  O(("// Adds a message to the list"));
  O(("int AddMessageToList(char *name, char *msg)"));
  O(("{"));
  O(("	int pos;"));
  O((" "));
  O(("	// Make sure there is room in the list"));
  O(("	if(num_messages>=MAX_SCRIPT_MESSAGES) return false;"));
  O((" "));
  O(("	// Allocate memory for this message entry"));
  O(("	pos=num_messages;"));
  O(("	message_list[pos]=(tScriptMessage *)malloc(sizeof(tScriptMessage));"));
  O(("	if(message_list[pos]==NULL) return false;"));
  O((" "));
  O(("	// Allocate memory for the message name"));
  O(("	message_list[pos]->name=(char *)malloc(strlen(name)+1);"));
  O(("	if(message_list[pos]->name==NULL) {"));
  O(("		free(message_list[pos]);"));
  O(("		return false;"));
  O(("	}"));
  O(("	strcpy(message_list[pos]->name,name);"));
  O((" "));
  O(("	// Allocate memory for the message name"));
  O(("	message_list[pos]->message=(char *)malloc(strlen(msg)+1);"));
  O(("	if(message_list[pos]->message==NULL) {"));
  O(("		free(message_list[pos]->name);"));
  O(("		free(message_list[pos]);"));
  O(("		return false;"));
  O(("	}"));
  O(("	strcpy(message_list[pos]->message,msg);"));
  O(("	num_messages++;"));
  O((" "));
  O(("	return true;"));
  O(("}"));
  O((" "));
  O(("// Removes any whitespace padding from the end of a string"));
  O(("void RemoveTrailingWhitespace(char *s)"));
  O(("{"));
  O(("	int last_char_pos;"));
  O((" "));
  O(("	last_char_pos=strlen(s)-1;"));
  O(("	while(last_char_pos>=0 && isspace(s[last_char_pos])) {"));
  O(("		s[last_char_pos]='\\0';"));
  O(("		last_char_pos--;"));
  O(("	}"));
  O(("}"));
  O((" "));
  O(("// Returns a pointer to the first non-whitespace char in given string"));
  O(("char *SkipInitialWhitespace(char *s)"));
  O(("{"));
  O(("	while((*s)!='\\0' && isspace(*s)) "));
  O(("		s++;"));
  O((" "));
  O(("	return(s);"));
  O(("}"));
  O((" "));
  O(("// Read in the Messages"));
  O(("int ReadMessageFile(char *filename)"));
  O(("{"));
  O(("	void *infile;"));
  O(("	char filebuffer[MAX_MSG_FILEBUF_LEN+1];"));
  O(("	char *line, *msg_start;"));
  O(("	int line_num;"));
  O(("	bool next_msgid_found;"));
  O((" "));
  O(("	// Try to open the file for loading"));
  O(("	infile=File_Open(filename,\"rt\");"));
  O(("	if (!infile) return false;"));
  O((" "));
  O(("	line_num=0;"));
  O(("	next_msgid_found=true;"));
  O((" "));
  O(("	// Clear the message list"));
  O(("	ClearMessageList();"));
  O((" "));
  O(("	// Read in and parse each line of the file"));
  O(("	while (!File_eof(infile)) {"));
  O((" "));
  O(("		// Clear the buffer"));
  O(("		strcpy(filebuffer,\"\");"));
  O((" "));
  O(("		// Read in a line from the file"));
  O(("		File_ReadString(filebuffer, MAX_MSG_FILEBUF_LEN, infile);"));
  O(("		line_num++;"));
  O((" "));
  O(("		// Remove whitespace padding at start and end of line"));
  O(("		RemoveTrailingWhitespace(filebuffer);"));
  O(("		line=SkipInitialWhitespace(filebuffer);"));
  O((" "));
  O(("		// If line is a comment, or empty, discard it"));
  O(("		if(strlen(line)==0 || strncmp(line,\"//\",2)==0)"));
  O(("			continue;"));
  O((" "));
  O(("		if(!next_msgid_found) {		// Parse out the last message ID number"));
  O((" "));
  O(("			// Grab the first keyword, make sure it's valid"));
  O(("			line=strtok(line,WHITESPACE_CHARS);"));
  O(("			if(line==NULL) continue;"));
  O((" "));
  O(("			// Grab the second keyword, and assign it as the next message ID"));
  O(("			line=strtok(NULL,WHITESPACE_CHARS);"));
  O(("			if(line==NULL) continue;"));
  O((" "));
  O(("			next_msgid_found=true;"));
  O(("		}"));
  O(("		else {	// Parse line as a message line"));
  O(("			"));
  O(("			// Find the start of message, and mark it"));
  O(("			msg_start=strchr(line,'=');"));
  O(("			if(msg_start==NULL) continue;"));
  O(("			msg_start[0]='\\0';"));
  O(("			msg_start++;"));
  O(("			"));
  O(("			// Add the message to the list"));
  O(("			AddMessageToList(line,msg_start);"));
  O(("		}"));
  O(("	}"));
  O(("	File_Close(infile);"));
  O((" "));
  O(("	return true;"));
  O(("}"));
  O((" "));
  O(("// Find a message"));
  O(("const char *GetMessage(const char *name)"));
  O(("{"));
  O(("	// Make sure given name is valid"));
  O(("	if(name==NULL) return INV_MSGNAME_STRING;"));
  O((" "));
  O(("	// Search message list for name"));
  O(("	for(int j=0;j<num_messages;j++)"));
  O(("		if(strcmp(message_list[j]->name,name)==0) return(message_list[j]->message);"));
  O((" "));
  O(("	// Couldn't find it"));
  O(("	return NO_MESSAGE_STRING;"));
  O(("}"));
  O((" "));

  // Write out the global name arrays
  WriteNameListArrays();

  O(("// ==============="));
  O(("// InitializeDLL()"));
  O(("// ==============="));
  O(("char STDCALL InitializeDLL(tOSIRISModuleInit *func_list)"));
  O(("{"));
  O(("	osicommon_Initialize((tOSIRISModuleInit *)func_list);"));
#ifndef NEWEDITOR
  O(("	if(func_list->game_checksum!=CHECKSUM)"));
  O(("	{ "));
  O(("		mprintf(0,\"Game-Checksum FAIL!!! (%%ul!=%%ul)\\n\",func_list->game_checksum,CHECKSUM);"));
  O(("		mprintf(0,\"RECOMPILE YOUR SCRIPTS!!!\\n\");"));
  O(("		return 0;"));
  O(("	}"));
#endif
  O((" "));
  O(("	ClearGlobalActionCtrs();"));
  O(("	dfInit();"));
  O(("	InitMessageList();"));
  O((" "));
  O(("	// Build the filename of the message file"));
  O(("	char filename[_MAX_PATH+1];"));
  O(("	char english_filename[_MAX_PATH+1];"));
  O(("	int lang_type;"));
  O(("	if(func_list->script_identifier!=NULL) {"));
  O(("		_splitpath(func_list->script_identifier,NULL,NULL,filename,NULL);"));
  O(("		sprintf(english_filename,\"%%s.msg\",filename);"));
  O(("		lang_type=Game_GetLanguage();"));
  O(("		if(lang_type==LANGUAGE_FRENCH) strcat(filename,\"_FRN\");"));
  O(("		else if(lang_type==LANGUAGE_GERMAN) strcat(filename,\"_GER\");"));
  O(("		else if(lang_type==LANGUAGE_ITALIAN) strcat(filename,\"_ITN\");"));
  O(("		else if(lang_type==LANGUAGE_SPANISH) strcat(filename,\"_SPN\");"));
  O(("		else if(lang_type==LANGUAGE_POLISH) strcat(filename,\"_POL\");"));
  O(("		strcat(filename,\".msg\");"));
  O(("	}"));
  O(("	else {"));
  O(("		strcpy(filename,\"%s\");", m_ScriptMessagesFilename.GetBuffer(0)));
  O(("		lang_type=LANGUAGE_ENGLISH;"));
  O(("	}"));
  O(("	if(!ReadMessageFile(filename)) {"));
  O(("		if(lang_type == LANGUAGE_ENGLISH) {"));
  O(("			mprintf(0,\"ERROR: Could not load message file - %%s\\n\",filename);"));
  O(("		}"));
  O(("		else if(!ReadMessageFile(english_filename)) {"));
  O(("			mprintf(0,\"ERROR: Could not load message file - %%s\\n\",english_filename);"));
  O(("		}"));
  O(("	}"));
  O((" "));

  // Write out the name array lookup code
  WriteNameArrayLookupCode();

  O((" "));
  O(("	return 1;"));
  O(("}"));
  O((""));

  O(("// ============="));
  O(("// ShutdownDLL()"));
  O(("// ============="));
  O(("void STDCALL ShutdownDLL(void)"));
  O(("{"));
  O(("	ClearMessageList();"));
  O(("}"));
  O((""));

  O(("// ==============="));
  O(("// GetGOScriptID()"));
  O(("// ==============="));
  O(("int STDCALL GetGOScriptID(const char *name,uint8_t isdoor)"));
  O(("{"));
  O(("	return -1;"));
  O(("}"));
  O((""));

  O(("// ================"));
  O(("// CreateInstance()"));
  O(("// ================"));
  O(("void STDCALLPTR CreateInstance(int id)"));
  O(("{"));
  O(("	switch(id) {"));

  // Level Case
  O(("		case %s:", LEVEL_ID_NAME));
  O(("			return new %s;", LEVEL_CLASS_NAME));
  O(("			break;"));

  // Custom object Cases
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {
      O(("		case %s:", CreateScriptConstantName(j)));
      O(("			return new %s;", CreateScriptClassName(j)));
      O(("			break;"));
    }

  // Trigger Cases
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE) {
      O(("		case %s:", CreateScriptConstantName(j)));
      O(("			return new %s;", CreateScriptClassName(j)));
      O(("			break;"));
    }

  O(("		default:"));
  O(("			mprintf(0,\"SCRIPT: Illegal ID (%%d)\\n\",id);"));
  O(("			break;"));

  O(("	}"));
  O(("	return NULL;"));
  O(("}"));
  O((""));

  O(("// ================="));
  O(("// DestroyInstance()"));
  O(("// ================="));
  O(("void STDCALL DestroyInstance(int id,void *ptr)"));
  O(("{"));
  O(("	switch(id) {"));

  // Level Case
  O(("		case %s:", LEVEL_ID_NAME));
  O(("			delete ((%s *)ptr);", LEVEL_CLASS_NAME));

  // Custom object Cases
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {
      O(("		case %s:", CreateScriptConstantName(j)));
      O(("			delete ((%s *)ptr);", CreateScriptClassName(j)));
      O(("			break;"));
    }

  // Trigger Cases
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE) {
      O(("		case %s:", CreateScriptConstantName(j)));
      O(("			delete ((%s *)ptr);", CreateScriptClassName(j)));
      O(("			break;"));
    }

  O(("		default:"));
  O(("			mprintf(0,\"SCRIPT: Illegal ID (%%d)\\n\",id);"));
  O(("			break;"));

  O(("	}"));
  O(("}"));
  O((""));

  O(("// ==================="));
  O(("// CallInstanceEvent()"));
  O(("// ==================="));
  O(("int16_t STDCALL CallInstanceEvent(int id,void *ptr,int event,tOSIRISEventInfo *data)"));
  O(("{"));
  O(("	switch(id) {"));

  // Level Case
  O(("		case %s:", LEVEL_ID_NAME));

  // Custom object Cases
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE)
      O(("		case %s:", CreateScriptConstantName(j)));

  // Trigger Cases
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE)
      O(("		case %s:", CreateScriptConstantName(j)));

  O(("			return ((BaseScript *)ptr)->CallEvent(event,data);"));
  O(("			break;"));

  O(("		default:"));
  O(("			mprintf(0,\"SCRIPT: Illegal ID (%%d)\\n\",id);"));
  O(("			break;"));

  O(("	}"));
  O(("	return CONTINUE_CHAIN|CONTINUE_DEFAULT;"));
  O(("}"));
  O((""));

  O(("// =================="));
  O(("// SaveRestoreState()"));
  O(("// =================="));
  O(("int STDCALL SaveRestoreState( void *file_ptr, uint8_t saving_state )"));
  O(("{"));
  O(("	return 0;"));
  O(("}"));
  O((""));

  O(("// ===================="));
  O(("// GetTriggerScriptID()"));
  O(("// ===================="));
  O(("int	STDCALL GetTriggerScriptID(int trigger_room,int trigger_face)"));
  O(("{"));

  // Trigger ID Listing
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE) {
      CString troom_text, tface_text;
      troom_text = "-1";
      tface_text = "-1";
      int t = m_ScriptGroupingList[j].owner_handle;
      if (t >= 0 && t < Num_triggers && t < MAX_NAMED_TRIGGERS && strlen(Triggers[t].name) != 0) {
        int index = FindTriggerInList(Triggers[t].name);
        if (index >= 0) {
          troom_text.Format("Trigger_rooms[%d]", index);
          tface_text.Format("Trigger_faces[%d]", index);
        }
      }

      O(("	if(trigger_room==%s && trigger_face==%s)", troom_text.GetBuffer(0), tface_text.GetBuffer(0)));
      O(("		return %s;", CreateScriptConstantName(j)));
      O((" "));
    }

  O(("	return -1;"));
  O(("}"));
  O((""));

  O(("// ================="));
  O(("// GetCOScriptList()"));
  O(("// ================="));
  O(("int	STDCALL GetCOScriptList( int **list, int **id_list )"));
  O(("{"));

  if (num_CO_scripts == 0) {
    O(("	static int *cust_handle_list=NULL;"));
    O(("	static int *cust_id_list=NULL;"));
  } else {
    O(("	static int cust_handle_list[%d];", num_CO_scripts));
    O(("	static int cust_id_list[%d] = { ", num_CO_scripts));

    // Write out the custom object IDs
    counter = 0;
    for (j = 0; j < m_NumScriptGroups; j++)
      if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {
        counter++;
        if (counter < num_CO_scripts)
          O(("		%s,", CreateScriptConstantName(j)));
        else
          O(("		%s", CreateScriptConstantName(j)));
      }

    O(("	};"));
  }

  // Fill in the custom object handles array
  O((" "));
  counter = 0;
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {

      // Obtain the handle text
      CString handle_text;

      handle_text.Format("0x%04x", OBJECT_HANDLE_NONE);
      object *objp = ObjGet(m_ScriptGroupingList[j].owner_handle);
      if (objp != NULL && objp->type != OBJ_NONE && objp->name != NULL) {
        int index = FindObjectInList(objp->name);
        if (index >= 0 && strlen(objp->name) != 0)
          handle_text.Format("Object_handles[%d]", index);
      }

      if (counter == 0)
        O(("	// Fill in the custom handle list"));
      O(("	cust_handle_list[%d]=%s;", counter, handle_text.GetBuffer(0)));
      counter++;
    }

  O((""));
  O(("	*list = cust_handle_list;"));
  O(("	*id_list = cust_id_list;"));
  O((""));
  O(("	return %d;", num_CO_scripts));
  O(("}"));
  O((""));

  O(("//======================="));
  O(("// Script Implementation "));
  O(("//======================="));
  O((""));

  O(("BaseScript::BaseScript()"));
  O(("{"));
  O(("}"));
  O((""));

  O(("BaseScript::~BaseScript()"));
  O(("{"));
  O(("}"));
  O((""));

  O(("int16_t BaseScript::CallEvent(int event,tOSIRISEventInfo *data)"));
  O(("{"));
  O(("	mprintf(0,\"BaseScript::CallEvent()\\n\");"));
  O(("	return CONTINUE_CHAIN|CONTINUE_DEFAULT;"));
  O(("}"));
  O((""));

  // Create the Level Script Class' CallEvent() method
  O(("int16_t %s::CallEvent(int event,tOSIRISEventInfo *data)", LEVEL_CLASS_NAME));
  O(("{"));
  O(("	switch(event) { "));

  // Find the level script group (if it exists)
  tScriptOwnerGroup *owner_group = NULL;
  ;
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == LEVEL_TYPE)
      owner_group = &m_ScriptGroupingList[j];

  // Create the event cases for the level script
  CreateLevelEventCases(owner_group);

  O(("	}"));
  O(("	return CONTINUE_CHAIN|CONTINUE_DEFAULT;"));
  O(("}"));
  O((""));

  // Create the CallEvent() methods for each custom object script class
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == OBJECT_TYPE) {
      O(("int16_t %s::CallEvent(int event,tOSIRISEventInfo *data)", CreateScriptClassName(j)));
      O(("{"));
      O(("	switch(event) { "));

      // Create the event cases for the custom object script
      owner_group = &m_ScriptGroupingList[j];
      CreateEventCases(owner_group);

      O(("	}"));
      O(("	return CONTINUE_CHAIN|CONTINUE_DEFAULT;"));
      O(("}"));
      O((""));
    }

  // Create the CallEvent() methods for each trigger script class
  for (j = 0; j < m_NumScriptGroups; j++)
    if (m_ScriptGroupingList[j].owner_type == TRIGGER_TYPE) {
      O(("int16_t %s::CallEvent(int event,tOSIRISEventInfo *data)", CreateScriptClassName(j)));
      O(("{"));
      O(("	switch(event) { "));

      // Create the event cases for the trigger script
      owner_group = &m_ScriptGroupingList[j];
      CreateEventCases(owner_group);

      O(("	}"));
      O(("	return CONTINUE_CHAIN|CONTINUE_DEFAULT;"));
      O(("}"));
      O((""));
    }

  // Create the Script Save Block
  WriteScriptSaveBlock();

  cfclose(CurrentOutputFile);
  CurrentOutputFile = NULL;

  return TRUE;
}

// Creates the level event cases
// NOTE: Some level events must always be handled to perform init/load/save/etc.
void CDallasMainDlg::CreateLevelEventCases(tScriptOwnerGroup *owner_group) {
  int j, k;

  if (CurrentOutputFile == NULL)
    return;

  // Handle the saving event
  O(("		case EVT_SAVESTATE:"));
  O(("			{"));
  O(("				tOSIRISEVTSAVESTATE *event_data=&data->evt_savestate;"));
  O(("	"));
  O(("				SaveGlobalActionCtrs(event_data->fileptr);"));
  O(("				dfSave(event_data->fileptr);"));
  O(("#ifdef ENABLE_CUSTOM_SAVE_AND_RESTORE"));
  O(("				dsCustomSave(event_data->fileptr);"));
  O(("#endif"));
  O(("			}"));
  O(("			break;"));

  // Handle the loading event
  O(("		case EVT_RESTORESTATE:"));
  O(("			{"));
  O(("				tOSIRISEVTRESTORESTATE *event_data=&data->evt_restorestate;"));
  O(("	"));
  O(("				RestoreGlobalActionCtrs(event_data->fileptr);"));
  O(("				dfRestore(event_data->fileptr);"));
  O(("#ifdef ENABLE_CUSTOM_SAVE_AND_RESTORE"));
  O(("				dsCustomRestore(event_data->fileptr);"));
  O(("#endif"));
  O(("			}"));
  O(("			break;"));

  // Create the valid event case statements
  for (j = 0; j < MAX_EVENT_TYPES; j++) {
    tEventSection *event_section;
    if (owner_group != NULL)
      event_section = &owner_group->event_sections[j];
    else
      event_section = NULL;

    // See if this case has certain events
    if (j != LEVEL_START_EVENT_TYPE && (event_section == NULL || event_section->num_script_nodes == 0))
      continue;

    O(("		case %s:", GetEventCodeName(j)));
    O(("			{"));

    // Get the event data code line and write it out
    O(("				%s", GetEventDataLine(j)));

    // If it's a LEVEL STARTED event, then initialize all the data
    if (j == LEVEL_START_EVENT_TYPE) {
      O((" "));
      O(("				ClearGlobalActionCtrs();"));
      O(("				dfInit();"));
    }

    // If it's a DESTROYED event, then add the conditional code to
    // break out if the object is being destroyed because the level is ending
    if (j == DESTROYED_EVENT_TYPE) {
      O((" "));
      O(("				// If destroy event is due to level ending, don't run scripts"));
      O(("				if(!event_data->is_dying) break;"));
    }

    // If there is an owner group, do the scripts
    if (event_section != NULL) {
      // Write out all the scripts for this event case
      for (k = 0; k < event_section->num_script_nodes; k++)
        WriteScriptCode(event_section->script_node_list[k]);
    }

    O(("			}"));
    O(("			break;"));
  }
}

// Creates the event cases
void CDallasMainDlg::CreateEventCases(tScriptOwnerGroup *owner_group) {
  int j, k;

  if (CurrentOutputFile == NULL || owner_group == NULL)
    return;

  // Create the valid event case statements
  for (j = 0; j < MAX_EVENT_TYPES; j++) {
    tEventSection *event_section = &owner_group->event_sections[j];
    if (event_section->num_script_nodes == 0)
      continue;
    O(("		case %s:", GetEventCodeName(j)));
    O(("			{"));

    // Get the event data code line and write it out
    O(("				%s", GetEventDataLine(j)));

    // If it's a DESTROYED event, then add the conditional code to
    // break out if the object is being destroyed because the level is ending
    if (j == DESTROYED_EVENT_TYPE) {
      O((" "));
      O(("				// If destroy event is due to level ending, don't run scripts"));
      O(("				if(!event_data->is_dying) break;"));
    }

    // Write out all the scripts for this event case
    for (k = 0; k < event_section->num_script_nodes; k++)
      WriteScriptCode(event_section->script_node_list[k]);

    O(("			}"));
    O(("			break;"));
  }
}

// Writes out the code for the given script (handles the top level IF-THEN)
void CDallasMainDlg::WriteScriptCode(HTREEITEM script_node) {
  HTREEITEM conditional_header_node, action_header_node;
  tTreeNodeData *data;

  if (CurrentOutputFile == NULL || script_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
  if (data == NULL || data->type != SCRIPT_HEADER_NODE)
    return;

  // Comment this section of script
  O((" "));
  O(("				// Script %03d: %s", data->ID, data->name));

  // Set the tab level
  CurrentTabLevel = 4;

  // Write out the top level conditional statement
  conditional_header_node = GetConditionalHeaderNode(script_node);
  WriteConditionalCodeBlock(conditional_header_node);

  // Write out the top level action block
  action_header_node = GetActionHeaderNode(script_node);
  WriteActionCodeBlock(action_header_node);
}

// Writes out the code body for a conditional header block (an IF statement)
void CDallasMainDlg::WriteConditionalCodeBlock(HTREEITEM conditional_header_node) {
  tTreeNodeData *data, *action_hdr_data;
  HTREEITEM child_node, action_hdr_node;

  if (CurrentOutputFile == NULL || conditional_header_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(conditional_header_node);
  if (data == NULL || data->type != CONDITIONAL_HEADER_NODE)
    return;

  // Get the first child (literal or query)
  child_node = m_ScriptTree.GetChildItem(conditional_header_node);
  if (child_node == NULL)
    return;

  TabOver();
  cfprintf(CurrentOutputFile, "if(");

  // Write out the max script execution times conditional (if it's not infinite)
  action_hdr_data = NULL;
  if (data->ID == TOP_LEVEL) {
    action_hdr_node = GetActionHeaderNode(conditional_header_node);
    if (action_hdr_node != NULL) {
      action_hdr_data = (tTreeNodeData *)m_ScriptTree.GetItemData(action_hdr_node);
      if (action_hdr_data != NULL && action_hdr_data->subID != 0) {
        CString tmp_name = CreateScriptGlobalCtrName(GetScriptID(action_hdr_node));
        cfprintf(CurrentOutputFile, "(%s < %d) && (", tmp_name.GetBuffer(0), action_hdr_data->subID);
      }
    }
  }

  // Write out the conditional expressions
  WriteLogicalOpExpression(child_node);

  // If max script execution expression was added, then tack on another parentheses
  if (action_hdr_data != NULL && action_hdr_data->subID != 0) {
    cfprintf(CurrentOutputFile, ")");
  }

  O((")"));
}

// Writes out a logical operation block (AND, OR)
void CDallasMainDlg::WriteLogicalOpExpression(HTREEITEM logop_node) {
  tTreeNodeData *data;
  HTREEITEM child_node;

  if (CurrentOutputFile == NULL || logop_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(logop_node);
  if (data == NULL || (data->type != LOGICAL_OPERATOR_NODE && data->type != CONDITIONAL_STATEMENT_NODE))
    return;

  // If it's a Condition, write it out
  if (data->type == CONDITIONAL_STATEMENT_NODE) {
    WriteConditionalStatement(logop_node);
    return;
  }

  // If it's an AND or an OR, process it
  if (data->ID == AND_TYPE || data->ID == OR_TYPE) {
    child_node = m_ScriptTree.GetChildItem(logop_node);
    while (child_node != NULL) {
      cfprintf(CurrentOutputFile, "(");
      WriteLogicalOpExpression(child_node);
      cfprintf(CurrentOutputFile, ")");
      child_node = m_ScriptTree.GetNextSiblingItem(child_node);
      if (child_node != NULL) {
        if (data->ID == AND_TYPE)
          cfprintf(CurrentOutputFile, " && ");
        else
          cfprintf(CurrentOutputFile, " || ");
      }
    }
  }
}

// Writes out a conditional statement
void CDallasMainDlg::WriteConditionalStatement(HTREEITEM condition_node) {
  tTreeNodeData *data;
  HTREEITEM child_node;

  if (CurrentOutputFile == NULL || condition_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(condition_node);
  if (data == NULL || data->type != CONDITIONAL_STATEMENT_NODE)
    return;

  // If it's an ALWAYS statement, just write out a 1 and get outta here
  if (data->ID == ALWAYS_STATEMENT) {
    cfprintf(CurrentOutputFile, "1");
    return;
  }

  // Get the first child (literal or query)
  child_node = m_ScriptTree.GetChildItem(condition_node);
  if (child_node != NULL) {
    WriteFunctionParameter(child_node);
  } else {
    cfprintf(CurrentOutputFile, "???");
  }

  // Get the second child (expression operator)
  if (child_node != NULL) {
    child_node = m_ScriptTree.GetNextSiblingItem(child_node);
    if (child_node != NULL) {
      tTreeNodeData *child_data;
      child_data = (tTreeNodeData *)m_ScriptTree.GetItemData(child_node);
      if (child_data != NULL && child_data->type == EXPRESSION_OPERATOR_NODE) {
        cfprintf(CurrentOutputFile, "%s", GetExpressionOperatorCodeName(child_data->subID));
      } else
        cfprintf(CurrentOutputFile, "/* Exp Op Error */");
    } else {
      cfprintf(CurrentOutputFile, "/* Exp Op Missing */");
    }
  }

  // If it's a comparison, get the third child (literal or query)
  if (child_node != NULL && data->ID == COMPARISON_STATEMENT) {
    child_node = m_ScriptTree.GetNextSiblingItem(child_node);
    if (child_node != NULL) {
      WriteFunctionParameter(child_node);
    } else {
      cfprintf(CurrentOutputFile, "/* 2nd Comparison Value Missing */");
    }
  }
}

// Writes out a query function call
void CDallasMainDlg::WriteQueryFunctionCall(HTREEITEM query_node) {
  tTreeNodeData *data;

  if (CurrentOutputFile == NULL || query_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(query_node);
  if (data == NULL || data->type != EXPRESSION_NODE)
    return;

  // Check Query ID validity
  if (data->ID < 0 || data->ID >= m_NumQueries) {
    cfprintf(CurrentOutputFile, "/* ERROR: Invalid Query Function Encountered!!! */");
    return;
  }

  // Handle the DALLAS custom queries first
  if (strcmp(m_QueryDatabase[data->ID].func, "qScriptExecuted_DALLAS") == 0) {
    HTREEITEM child_node;
    tTreeNodeData *child_data;
    child_node = m_ScriptTree.GetChildItem(query_node);
    if (child_node == NULL)
      return;
    child_data = (tTreeNodeData *)m_ScriptTree.GetItemData(child_node);
    if (child_data == NULL || child_data->type != PARAMETER_NODE || child_data->ID != SCRIPT_PARAMETER_TYPE)
      return;
    CString tmp_name = CreateScriptGlobalCtrName(child_data->int_val);
    cfprintf(CurrentOutputFile, "(%s > 0)", tmp_name.GetBuffer(0));
    return;
  }
  if (strcmp(m_QueryDatabase[data->ID].func, "qTimesScriptExecuted_DALLAS") == 0) {
    HTREEITEM child_node;
    tTreeNodeData *child_data;
    child_node = m_ScriptTree.GetChildItem(query_node);
    if (child_node == NULL)
      return;
    child_data = (tTreeNodeData *)m_ScriptTree.GetItemData(child_node);
    if (child_data == NULL || child_data->type != PARAMETER_NODE || child_data->ID != SCRIPT_PARAMETER_TYPE)
      return;
    CString tmp_name = CreateScriptGlobalCtrName(child_data->int_val);
    cfprintf(CurrentOutputFile, "%s", tmp_name.GetBuffer(0));
    return;
  }

  // Write out the function name
  cfprintf(CurrentOutputFile, "%s(", m_QueryDatabase[data->ID].func);

  // Write out the parameter arguments
  HTREEITEM param_node;

  param_node = m_ScriptTree.GetChildItem(query_node);
  while (param_node != NULL) {
    WriteFunctionParameter(param_node);
    param_node = m_ScriptTree.GetNextSiblingItem(param_node);
    if (param_node != NULL)
      cfprintf(CurrentOutputFile, ", ");
  }
  cfprintf(CurrentOutputFile, ")");
}

// Writes out the code body for an action header block (the block to immediately follow an IF statement)
void CDallasMainDlg::WriteActionCodeBlock(HTREEITEM action_header_node) {
  HTREEITEM child_node;
  tTreeNodeData *header_data, *data;

  if (action_header_node == NULL)
    return;

  header_data = (tTreeNodeData *)m_ScriptTree.GetItemData(action_header_node);
  if (header_data == NULL || header_data->type != ACTIONS_HEADER_NODE)
    return;

  // Write out starting brace
  TabOver();
  if (header_data->ID == NESTED && header_data->subID == ELSE_CLAUSE)
    O(("else {"));
  else
    O(("{"));

  CurrentTabLevel++;

  child_node = m_ScriptTree.GetChildItem(action_header_node);
  while (child_node != NULL) {

    // Get the type of child node this is
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(child_node);
    if (data != NULL) {
      if (data->type == ACTION_STATEMENT_NODE) {
        WriteActionFunctionCall(child_node);
      } else if (data->type == CONDITIONAL_HEADER_NODE) {
        WriteConditionalCodeBlock(child_node);
      } else if (data->type == ACTIONS_HEADER_NODE) {
        WriteActionCodeBlock(child_node);
      }
    }

    // Get the next node
    child_node = m_ScriptTree.GetNextSiblingItem(child_node);
  }

  // If it's a top level action header node, increment the global counter
  if (header_data->ID == TOP_LEVEL) {
    CString tmp_name = CreateScriptGlobalCtrName(GetScriptID(action_header_node));

    TabOver();
    O((""));
    TabOver();
    O(("// Increment the script action counter"));
    TabOver();
    O(("if(%s < MAX_ACTION_CTR_VALUE) %s++;", tmp_name.GetBuffer(0), tmp_name.GetBuffer(0)));

    // If user wants to break script chain, do it here
    if (header_data->int_val == BREAK_SCRIPT_CHAIN) {
      TabOver();
      O((""));
      TabOver();
      O(("return CONTINUE_DEFAULT;"));
    }
  }

  CurrentTabLevel--;

  // Write out closing brace
  TabOver();
  O(("}"));
}

// Writes out an action function call
void CDallasMainDlg::WriteActionFunctionCall(HTREEITEM action_node) {
  tTreeNodeData *data;

  if (CurrentOutputFile == NULL || action_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(action_node);
  if (data == NULL || data->type != ACTION_STATEMENT_NODE)
    return;

  // Check Action ID validity
  if (data->ID < 0 || data->ID >= m_NumActions) {
    if (data->ID != DO_NOTHING_ID) {
      TabOver();
      O(("// ERROR: Invalid Action Function Encountered!!!"));
    }
    return;
  }

  // Write out the function name
  TabOver();
  cfprintf(CurrentOutputFile, "%s(", m_ActionDatabase[data->ID].func);

  // Write out the parameter arguments
  HTREEITEM param_node;

  param_node = m_ScriptTree.GetChildItem(action_node);
  while (param_node != NULL) {
    WriteFunctionParameter(param_node);
    param_node = m_ScriptTree.GetNextSiblingItem(param_node);
    if (param_node != NULL)
      cfprintf(CurrentOutputFile, ", ");
  }
  O((");"));
}

// Writes out an action function call
void CDallasMainDlg::WriteFunctionParameter(HTREEITEM param_node) {
  tTreeNodeData *data;
  int index;

  if (CurrentOutputFile == NULL || param_node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(param_node);
  if (data == NULL || (data->type != PARAMETER_NODE && data->type != EXPRESSION_NODE))
    return;

  // If it's a query, write out the query function
  if (data->type == EXPRESSION_NODE) {
    WriteQueryFunctionCall(param_node);
    return;
  }

  // Output the parameter values
  switch (data->ID) {
  case DOOR_PARAMETER_TYPE:
    if (data->subID == USE_IT_HANDLE)
      cfprintf(CurrentOutputFile, "event_data->it_handle");
    else if (data->subID == USE_ME_HANDLE)
      cfprintf(CurrentOutputFile, "data->me_handle");
    else {
      int index = FindDoorInList(data->str_val);
      if (index < 0 || strlen(data->str_val) == 0)
        cfprintf(CurrentOutputFile, "%d", OBJECT_HANDLE_NONE);
      else
        cfprintf(CurrentOutputFile, "Door_handles[%d]", index);
    }
    break;
  case OBJECT_PARAMETER_TYPE:
    if (data->subID == USE_IT_HANDLE)
      cfprintf(CurrentOutputFile, "event_data->it_handle");
    else if (data->subID == USE_ME_HANDLE)
      cfprintf(CurrentOutputFile, "data->me_handle");
    else {
      int index = FindObjectInList(data->str_val);
      if (index < 0 || strlen(data->str_val) == 0)
        cfprintf(CurrentOutputFile, "%d", OBJECT_HANDLE_NONE);
      else
        cfprintf(CurrentOutputFile, "Object_handles[%d]", index);
    }
    break;
  case ROOM_PARAMETER_TYPE:
    index = FindRoomInList(data->str_val);
    if (index < 0 || strlen(data->str_val) == 0)
      cfprintf(CurrentOutputFile, "%d", -1);
    else
      cfprintf(CurrentOutputFile, "Room_indexes[%d]", index);
    break;
  case TRIGGER_PARAMETER_TYPE:
    index = FindTriggerInList(data->str_val);
    if (index < 0 || strlen(data->str_val) == 0)
      cfprintf(CurrentOutputFile, "%d", -1);
    else
      cfprintf(CurrentOutputFile, "Trigger_indexes[%d]", index);
    break;
  case INT_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "%d", data->int_val);
    break;
  case BOOL_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "%d", data->int_val);
    break;
  case FLOAT_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "%ff", data->float_val1);
    break;
  case VECTOR_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "NO VECTOR YET");
    break;
  case STRING_PARAMETER_TYPE:
    index = FindMessageNameInList(data->str_val);
    if (index < 0 || strlen(data->str_val) == 0)
      cfprintf(CurrentOutputFile, "\"*MESSAGE_ERROR*\"");
    else
      cfprintf(CurrentOutputFile, "Message_strings[%d]", index);
    break;
  case PERCENTAGE_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "%ff", data->float_val1);
    break;
  case ENUM_PARAMETER_TYPE:
    if (data->subID == USE_GOALID_VALUE)
      cfprintf(CurrentOutputFile, "event_data->goal_uid");
    else if (data->subID == USE_TIMERID_VALUE)
      cfprintf(CurrentOutputFile, "event_data->id");
    else if (data->subID == USE_MATCENID_VALUE)
      cfprintf(CurrentOutputFile, "event_data->id");
    else {
      cfprintf(CurrentOutputFile, "%d", data->int_val);
    }
    break;
  case SCRIPT_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "%d", data->int_val);
    break;
  case SOUND_PARAMETER_TYPE:
    index = FindSoundInList(data->str_val);
    if (index < 0 || strlen(data->str_val) == 0)
      cfprintf(CurrentOutputFile, "%d", -1);
    else
      cfprintf(CurrentOutputFile, "Sound_indexes[%d]", index);
    break;
  case SPECNAME_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "\"%s\"", data->str_val);
    break;
  case TEXTURE_PARAMETER_TYPE:
    index = FindTextureInList(data->str_val);
    if (index < 0 || strlen(data->str_val) == 0)
      cfprintf(CurrentOutputFile, "%d", -1);
    else
      cfprintf(CurrentOutputFile, "Texture_indexes[%d]", index);
    break;
  case FLAG_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "%d", data->int_val);
    break;
  case PATH_PARAMETER_TYPE:
    index = FindPathInList(data->str_val);
    if (index < 0 || strlen(data->str_val) == 0)
      cfprintf(CurrentOutputFile, "%d", -1);
    else
      cfprintf(CurrentOutputFile, "Path_indexes[%d]", index);
    break;
  case MATCEN_PARAMETER_TYPE:
    if (data->subID == USE_MATCEN_EVENT_ID) {
      cfprintf(CurrentOutputFile, "event_data->id");
    } else {
      index = FindMatcenInList(data->str_val);
      if (index < 0 || strlen(data->str_val) == 0)
        cfprintf(CurrentOutputFile, "%d", -1);
      else
        cfprintf(CurrentOutputFile, "Matcen_indexes[%d]", index);
    }
    break;
  case LEVEL_GOAL_PARAMETER_TYPE:
    if (data->subID == USE_LEVEL_GOAL_ID) {
      cfprintf(CurrentOutputFile, "event_data->level_goal_index");
    } else {
      index = FindGoalInList(data->str_val);
      if (index < 0 || strlen(data->str_val) == 0)
        cfprintf(CurrentOutputFile, "%d", -1);
      else
        cfprintf(CurrentOutputFile, "Goal_indexes[%d]", index);
    }
    break;
  case STRM_AUDIO_PARAMETER_TYPE:
    cfprintf(CurrentOutputFile, "\"%s\"", data->str_val);
    break;
  default:
    break;
  }
}

// Creates the tree block (for saving scripts)
void CDallasMainDlg::WriteScriptSaveBlock(void) {
  if (CurrentOutputFile == NULL)
    return;

  // Create the header
  O((" "));
  O((" "));
  O(("/*********************************************************"));
  O(("Script Save Block: DO NOT TOUCH ANYTHING IN THIS BLOCK!!! "));
  O(("**********************************************************"));
  O(("%s", SCRIPT_BLOCK_START_TAG));
  O((" "));
  O(("VERSION		%d", DALLAS_SAVE_VERSION));
  O(("NEXT_ID		%d", m_NextScriptID));
  O((" "));
  O(("// UserType value blocks"));

  // Writes out the name lists
  WriteUserTypeVals();

  O((" "));
  O(("// Name Lists"));
  // Writes out the name lists
  WriteNameLists();

  O((" "));
  O(("// Script Tree Dump"));

  // Write out the list of nodes
  WriteScriptTreeDump();

  O((" "));
  O(("%s", SCRIPT_BLOCK_END_TAG));
  O(("*********************************************************/"));
}

// Writes out the UserType value blocks
void CDallasMainDlg::WriteUserTypeVals(void) {
  int j, k;

  if (CurrentOutputFile == NULL)
    return;

  for (j = 0; j < m_NumEnums; j++) {
    if (m_EnumDatabase[j].is_user_type) {
      O(("%s %s", USERTYPE_VALS_START_TAG, m_EnumDatabase[j].name));
      for (k = 0; k < m_EnumDatabase[j].num_values; k++) {
        tEnumValueEntry *value_entry = &m_EnumDatabase[j].values[k];
        if (value_entry->value != -1)
          O(("%d:%s", value_entry->value, value_entry->name));
      }
      O(("%s", USERTYPE_VALS_END_TAG));
      O((" "));
    }
  }
}

// Writes out the name lists
void CDallasMainDlg::WriteNameLists(void) {
  int j;

  if (CurrentOutputFile == NULL)
    return;

  // Write out the door list
  O(("%s", DOOR_LIST_START_TAG));
  for (j = 0; j < m_DoorListSize; j++)
    O(("%s", m_DoorList[j]));
  O(("%s", DOOR_LIST_END_TAG));
  O((" "));

  // Write out the object list
  O(("%s", OBJECT_LIST_START_TAG));
  for (j = 0; j < m_ObjectListSize; j++)
    O(("%s", m_ObjectList[j]));
  O(("%s", OBJECT_LIST_END_TAG));
  O((" "));

  // Write out the room list
  O(("%s", ROOM_LIST_START_TAG));
  for (j = 0; j < m_RoomListSize; j++)
    O(("%s", m_RoomList[j]));
  O(("%s", ROOM_LIST_END_TAG));
  O((" "));

  // Write out the trigger list
  O(("%s", TRIGGER_LIST_START_TAG));
  for (j = 0; j < m_TriggerListSize; j++)
    O(("%s", m_TriggerList[j]));
  O(("%s", TRIGGER_LIST_END_TAG));
  O((" "));

  // Write out the sound list
  O(("%s", SOUND_LIST_START_TAG));
  for (j = 0; j < m_SoundListSize; j++)
    O(("%s", m_SoundList[j]));
  O(("%s", SOUND_LIST_END_TAG));
  O((" "));

  // Write out the texture list
  O(("%s", TEXTURE_LIST_START_TAG));
  for (j = 0; j < m_TextureListSize; j++)
    O(("%s", m_TextureList[j]));
  O(("%s", TEXTURE_LIST_END_TAG));
  O((" "));

  // Write out the specname list
  O(("%s", SPECNAME_LIST_START_TAG));
  for (j = 0; j < m_SpecnameListSize; j++)
    O(("%s", m_SpecnameList[j]));
  O(("%s", SPECNAME_LIST_END_TAG));
  O((" "));

  // Write out the Path list
  O(("%s", PATH_LIST_START_TAG));
  for (j = 0; j < m_PathListSize; j++)
    O(("%s", m_PathList[j]));
  O(("%s", PATH_LIST_END_TAG));
  O((" "));

  // Write out the Matcen list
  O(("%s", MATCEN_LIST_START_TAG));
  for (j = 0; j < m_MatcenListSize; j++)
    O(("%s", m_MatcenList[j]));
  O(("%s", MATCEN_LIST_END_TAG));
  O((" "));

  // Write out the Goal list
  O(("%s", GOAL_LIST_START_TAG));
  for (j = 0; j < m_GoalListSize; j++)
    O(("%s", m_GoalList[j]));
  O(("%s", GOAL_LIST_END_TAG));
  O((" "));

  // Write out the StrmAudio list
  O(("%s", STRM_AUDIO_LIST_START_TAG));
  for (j = 0; j < m_StrmAudioListSize; j++)
    O(("%s", m_StrmAudioList[j]));
  O(("%s", STRM_AUDIO_LIST_END_TAG));
  O((" "));
}

// Writes out the name list arrays in the code
void CDallasMainDlg::WriteNameListArrays(void) {
  int j;

  if (CurrentOutputFile == NULL)
    return;

  O((" "));
  O(("//======================"));
  O(("// Name List Arrays     "));
  O(("//======================"));
  O((" "));

  // Write out the door list
  O(("#define NUM_DOOR_NAMES		%d", m_DoorListSize));
  if (m_DoorListSize > 0) {
    O(("const char *Door_names[NUM_DOOR_NAMES] = {"));
    for (j = 0; j < (m_DoorListSize - 1); j++)
      O(("	\"%s\",", m_DoorList[j]));
    O(("	\"%s\"", m_DoorList[j]));
    O(("};"));
    O(("int Door_handles[NUM_DOOR_NAMES];"));
  } else {
    O(("const char **Door_names=NULL;"));
    O(("int *Door_handles=NULL;"));
  }
  O((" "));

  // Write out the object list
  O(("#define NUM_OBJECT_NAMES		%d", m_ObjectListSize));
  if (m_ObjectListSize > 0) {
    O(("const char *Object_names[NUM_OBJECT_NAMES] = {"));
    for (j = 0; j < (m_ObjectListSize - 1); j++)
      O(("	\"%s\",", m_ObjectList[j]));
    O(("	\"%s\"", m_ObjectList[j]));
    O(("};"));
    O(("int Object_handles[NUM_OBJECT_NAMES];"));
  } else {
    O(("const char **Object_names=NULL;"));
    O(("int *Object_handles=NULL;"));
  }
  O((" "));

  // Write out the room list
  O(("#define NUM_ROOM_NAMES		%d", m_RoomListSize));
  if (m_RoomListSize > 0) {
    O(("const char *Room_names[NUM_ROOM_NAMES] = {"));
    for (j = 0; j < (m_RoomListSize - 1); j++)
      O(("	\"%s\",", m_RoomList[j]));
    O(("	\"%s\"", m_RoomList[j]));
    O(("};"));
    O(("int Room_indexes[NUM_ROOM_NAMES];"));
  } else {
    O(("const char **Room_names=NULL;"));
    O(("int *Room_indexes=NULL;"));
  }
  O((" "));

  // Write out the Trigger list
  O(("#define NUM_TRIGGER_NAMES		%d", m_TriggerListSize));
  if (m_TriggerListSize > 0) {
    O(("const char *Trigger_names[NUM_TRIGGER_NAMES] = {"));
    for (j = 0; j < (m_TriggerListSize - 1); j++)
      O(("	\"%s\",", m_TriggerList[j]));
    O(("	\"%s\"", m_TriggerList[j]));
    O(("};"));
    O(("int Trigger_indexes[NUM_TRIGGER_NAMES];"));
    O(("int Trigger_faces[NUM_TRIGGER_NAMES];"));
    O(("int Trigger_rooms[NUM_TRIGGER_NAMES];"));
  } else {
    O(("const char **Trigger_names=NULL;"));
    O(("int *Trigger_indexes=NULL;"));
    O(("int *Trigger_faces=NULL;"));
    O(("int *Trigger_rooms=NULL;"));
  }
  O((" "));

  // Write out the sound list
  O(("#define NUM_SOUND_NAMES		%d", m_SoundListSize));
  if (m_SoundListSize > 0) {
    O(("const char *Sound_names[NUM_SOUND_NAMES] = {"));
    for (j = 0; j < (m_SoundListSize - 1); j++)
      O(("	\"%s\",", m_SoundList[j]));
    O(("	\"%s\"", m_SoundList[j]));
    O(("};"));
    O(("int Sound_indexes[NUM_SOUND_NAMES];"));
  } else {
    O(("const char **Sound_names=NULL;"));
    O(("int *Sound_indexes=NULL;"));
  }
  O((" "));

  // Write out the texture list
  O(("#define NUM_TEXTURE_NAMES		%d", m_TextureListSize));
  if (m_TextureListSize > 0) {
    O(("const char *Texture_names[NUM_TEXTURE_NAMES] = {"));
    for (j = 0; j < (m_TextureListSize - 1); j++)
      O(("	\"%s\",", m_TextureList[j]));
    O(("	\"%s\"", m_TextureList[j]));
    O(("};"));
    O(("int Texture_indexes[NUM_TEXTURE_NAMES];"));
  } else {
    O(("const char **Texture_names=NULL;"));
    O(("int *Texture_indexes=NULL;"));
  }
  O((" "));

  // Write out the Path list
  O(("#define NUM_PATH_NAMES		%d", m_PathListSize));
  if (m_PathListSize > 0) {
    O(("const char *Path_names[NUM_PATH_NAMES] = {"));
    for (j = 0; j < (m_PathListSize - 1); j++)
      O(("	\"%s\",", m_PathList[j]));
    O(("	\"%s\"", m_PathList[j]));
    O(("};"));
    O(("int Path_indexes[NUM_PATH_NAMES];"));
  } else {
    O(("const char **Path_names=NULL;"));
    O(("int *Path_indexes=NULL;"));
  }
  O((" "));

  // Write out the Matcen list
  O(("#define NUM_MATCEN_NAMES		%d", m_MatcenListSize));
  if (m_MatcenListSize > 0) {
    O(("const char *Matcen_names[NUM_MATCEN_NAMES] = {"));
    for (j = 0; j < (m_MatcenListSize - 1); j++)
      O(("	\"%s\",", m_MatcenList[j]));
    O(("	\"%s\"", m_MatcenList[j]));
    O(("};"));
    O(("int Matcen_indexes[NUM_MATCEN_NAMES];"));
  } else {
    O(("const char **Matcen_names=NULL;"));
    O(("int *Matcen_indexes=NULL;"));
  }
  O((" "));

  // Write out the Goal list
  O(("#define NUM_GOAL_NAMES		%d", m_GoalListSize));
  if (m_GoalListSize > 0) {
    O(("const char *Goal_names[NUM_GOAL_NAMES] = {"));
    for (j = 0; j < (m_GoalListSize - 1); j++)
      O(("	\"%s\",", m_GoalList[j]));
    O(("	\"%s\"", m_GoalList[j]));
    O(("};"));
    O(("int Goal_indexes[NUM_GOAL_NAMES];"));
  } else {
    O(("const char **Goal_names=NULL;"));
    O(("int *Goal_indexes=NULL;"));
  }
  O((" "));

  // Write out the message name list
  O(("#define NUM_MESSAGE_NAMES		%d", m_MessageNameListSize));
  if (m_MessageNameListSize > 0) {
    O(("const char *Message_names[NUM_MESSAGE_NAMES] = {"));
    for (j = 0; j < (m_MessageNameListSize - 1); j++)
      O(("	\"%s\",", m_MessageNameList[j]));
    O(("	\"%s\"", m_MessageNameList[j]));
    O(("};"));
    O(("const char *Message_strings[NUM_MESSAGE_NAMES];"));
  } else {
    O(("const char **Message_names=NULL;"));
    O(("const char **Message_strings=NULL;"));
  }
  O((" "));
}

// Writes out the name list lookup code
void CDallasMainDlg::WriteNameArrayLookupCode(void) {
  O(("	int j;"));
  O((" "));
  O(("	// Do Door Index lookups"));
  O(("	for(j=0;j<NUM_DOOR_NAMES;j++) "));
  O(("		Door_handles[j]=Scrpt_FindDoorName(Door_names[j]);"));
  O((" "));
  O(("	// Do Object Index lookups"));
  O(("	for(j=0;j<NUM_OBJECT_NAMES;j++) "));
  O(("		Object_handles[j]=Scrpt_FindObjectName(Object_names[j]);"));
  O((" "));
  O(("	// Do Room Index lookups"));
  O(("	for(j=0;j<NUM_ROOM_NAMES;j++) "));
  O(("		Room_indexes[j]=Scrpt_FindRoomName(Room_names[j]);"));
  O((" "));
  O(("	// Do Trigger Index lookups"));
  O(("	for(j=0;j<NUM_TRIGGER_NAMES;j++) {"));
  O(("		Trigger_indexes[j]=Scrpt_FindTriggerName(Trigger_names[j]);"));
  O(("		Trigger_faces[j]=Scrpt_GetTriggerFace(Trigger_indexes[j]);"));
  O(("		Trigger_rooms[j]=Scrpt_GetTriggerRoom(Trigger_indexes[j]);"));
  O(("	}"));
  O((" "));
  O(("	// Do Sound Index lookups"));
  O(("	for(j=0;j<NUM_SOUND_NAMES;j++) "));
  O(("		Sound_indexes[j]=Scrpt_FindSoundName(Sound_names[j]);"));
  O((" "));
  O(("	// Do Texture Index lookups"));
  O(("	for(j=0;j<NUM_TEXTURE_NAMES;j++) "));
  O(("		Texture_indexes[j]=Scrpt_FindTextureName(Texture_names[j]);"));
  O((" "));
  O(("	// Do Path Index lookups"));
  O(("	for(j=0;j<NUM_PATH_NAMES;j++) "));
  O(("		Path_indexes[j]=Scrpt_FindPathName(Path_names[j]);"));
  O((" "));
  O(("	// Do Matcen Index lookups"));
  O(("	for(j=0;j<NUM_MATCEN_NAMES;j++) "));
  O(("		Matcen_indexes[j]=Scrpt_FindMatcenName(Matcen_names[j]);"));
  O((" "));
  O(("	// Do Goal Index lookups"));
  O(("	for(j=0;j<NUM_GOAL_NAMES;j++) "));
  O(("		Goal_indexes[j]=Scrpt_FindLevelGoalName(Goal_names[j]);"));
  O((" "));
  O(("	// Do Message Name lookups"));
  O(("	for(j=0;j<NUM_MESSAGE_NAMES;j++) "));
  O(("		Message_strings[j]=GetMessage(Message_names[j]);"));
}

// Writes out a coded version of all the script nodes in the tree
void CDallasMainDlg::WriteScriptTreeDump(void) {
  HTREEITEM node;
  tTreeNodeData *data;

  if (CurrentOutputFile == NULL)
    return;

  CurrentTabLevel = 0;

  // Write out each script node (and any children)
  node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
    if (data != NULL && data->type == SCRIPT_HEADER_NODE) {
      if (DALLAS_SAVE_VERSION >= 1)
        WriteScriptNodeDump_v1U(node);
      else
        WriteScriptNodeDump_v0(node);

      WriteScriptChildrenDump(node);
    }

    node = m_ScriptTree.GetNextSiblingItem(node);
  }
}

// Writes out codes versions of all children of the given node
void CDallasMainDlg::WriteScriptChildrenDump(HTREEITEM parent, bool filter_on /*=FALSE*/) {
  HTREEITEM child_node;

  if (CurrentOutputFile == NULL || parent == NULL)
    return;

  // Make sure the parent has at least one child
  child_node = m_ScriptTree.GetChildItem(parent);
  if (child_node == NULL)
    return;

  // Write out each child node (and any of their children)
  CurrentTabLevel++;
  TabOver();
  O(("%s", CHILD_BLOCK_START_TAG));
  while (child_node != NULL) {

    if (DALLAS_SAVE_VERSION >= 1)
      WriteScriptNodeDump_v1U(child_node, filter_on);
    else
      WriteScriptNodeDump_v0(child_node);

    WriteScriptChildrenDump(child_node, filter_on);
    child_node = m_ScriptTree.GetNextSiblingItem(child_node);
  }
  TabOver();
  O(("%s", CHILD_BLOCK_END_TAG));
  CurrentTabLevel--;
}

// VERSION 0: Writes out a coded version of the given script node
void CDallasMainDlg::WriteScriptNodeDump_v0(HTREEITEM node) {
  tTreeNodeData *data;
  CString tmp_name;
  int index;
  char goal_name[_MAX_PATH + 1];

  if (CurrentOutputFile == NULL || node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return;

  TabOver();
  switch (data->type) {
  case SCRIPT_HEADER_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d:%s", data->type, data->ID, data->name);
    break;
  case SCRIPT_OWNER_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d:%d", data->type, data->ID, data->int_val);
    break;
  case SCRIPT_EVENT_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case CONDITIONAL_HEADER_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case ACTIONS_HEADER_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d:%d", data->type, data->ID, data->subID);
    break;
  case CONDITIONAL_STATEMENT_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case EXPRESSION_NODE:
    cfprintf(CurrentOutputFile, "%02d:%s:%s", data->type, GetQueryFunc(data->ID), data->name);
    break;
  case EXPRESSION_OPERATOR_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d:%d", data->type, data->ID, data->subID);
    break;
  case ACTION_STATEMENT_NODE:
    cfprintf(CurrentOutputFile, "%02d:%s", data->type, GetActionFunc(data->ID));
    break;
  case LOGICAL_OPERATOR_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case PARAMETER_NODE:
    // Get image type based upon what kind of parameter it is
    switch (data->ID) {
    case DOOR_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, data->int_val, data->name);
      break;
    case OBJECT_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, data->int_val, data->name);
      break;
    case ROOM_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case TRIGGER_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case INT_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case BOOL_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case FLOAT_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%f:%s", data->type, data->ID, data->float_val1, data->name);
      break;
    case VECTOR_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%f:%f:%f:%s", data->type, data->ID, data->float_val1, data->float_val2,
               data->float_val3, data->name);
      break;
    case STRING_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%s:%s", data->type, data->ID, data->str_val, data->name);
      break;
    case PERCENTAGE_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%f:%s", data->type, data->ID, data->float_val1, data->name);
      break;
    case ENUM_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case SCRIPT_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case SOUND_PARAMETER_TYPE:
      if (data->int_val == NOT_SPECIFIED_TYPE)
        index = -1;
      else
        index = FindSoundInList(Sounds[data->int_val].name);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case SPECNAME_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%s:%s", data->type, data->ID, data->str_val, data->name);
      break;
    case TEXTURE_PARAMETER_TYPE:
      if (data->int_val == NOT_SPECIFIED_TYPE)
        index = -1;
      else
        index = FindTextureInList(GameTextures[data->int_val].name);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case FLAG_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case PATH_PARAMETER_TYPE:
      if (data->int_val == NOT_SPECIFIED_TYPE)
        index = -1;
      else
        index = FindPathInList(GamePaths[data->int_val].name);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case MATCEN_PARAMETER_TYPE:
      if (data->subID == USE_MATCEN_VALUE) {
        if (data->int_val == NOT_SPECIFIED_TYPE || !MatcenValid(data->int_val))
          index = -1;
        else {
          char matcen_name[MAX_MATCEN_NAME_LEN + 1];
          Matcen[data->int_val]->GetName(matcen_name);
          index = FindMatcenInList(matcen_name);
        }
      } else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, index, data->name);
      break;
    case LEVEL_GOAL_PARAMETER_TYPE:
      if (data->subID == USE_LEVEL_GOAL_VALUE) {
        if (data->int_val == NOT_SPECIFIED_TYPE || Level_goals.GoalGetName(data->int_val, goal_name, _MAX_PATH) < 0)
          index = -1;
        else {
          index = FindGoalInList(goal_name);
        }
      } else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, index, data->name);
      break;
    case STRM_AUDIO_PARAMETER_TYPE:
      if (strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindStrmAudioInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    default:
      cfprintf(CurrentOutputFile, "%02d:%d:%s", data->type, data->ID, data->name);
      break;
    }
    break;
  case PARAMETER_OPERATOR_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case UNKNOWN_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  default:
    cfprintf(CurrentOutputFile, "%02d:%d", UNKNOWN_NODE, data->ID);
    break;
  }
  O((" "));
}

// VERSION 1: Writes out a coded version of the given script node
void CDallasMainDlg::WriteScriptNodeDump_v1U(HTREEITEM node, bool filter_on /*=FALSE*/) {
  tTreeNodeData *data;
  CString tmp_name;
  int index;

  if (CurrentOutputFile == NULL || node == NULL)
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(node);
  if (data == NULL)
    return;

  TabOver();
  switch (data->type) {
  case SCRIPT_HEADER_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d:%s", data->type, data->ID, data->name);
    break;
  case SCRIPT_OWNER_NODE:
    if (data->ID == OBJECT_TYPE) {
      if (filter_on || data->int_val == OBJECT_HANDLE_NONE || strlen(data->str_val) == 0)
        index = OBJECT_NONE_HANDLE;
      else
        index = FindObjectInList(data->str_val);
    } else if (data->ID == TRIGGER_TYPE) {
      if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindTriggerInList(data->str_val);
    } else
      index = data->int_val;
    cfprintf(CurrentOutputFile, "%02d:%d:%d", data->type, data->ID, index);
    break;
  case SCRIPT_EVENT_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case CONDITIONAL_HEADER_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case ACTIONS_HEADER_NODE:
    if (DALLAS_SAVE_VERSION >= 3) {
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d", data->type, data->ID, data->int_val, data->subID);
    } else {
      cfprintf(CurrentOutputFile, "%02d:%d:%d", data->type, data->ID, data->subID);
    }
    break;
  case CONDITIONAL_STATEMENT_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case EXPRESSION_NODE:
    cfprintf(CurrentOutputFile, "%02d:%s:%s", data->type, GetQueryFunc(data->ID), data->name);
    break;
  case EXPRESSION_OPERATOR_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d:%d", data->type, data->ID, data->subID);
    break;
  case ACTION_STATEMENT_NODE:
    cfprintf(CurrentOutputFile, "%02d:%s", data->type, GetActionFunc(data->ID));
    break;
  case LOGICAL_OPERATOR_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case PARAMETER_NODE:
    // Get image type based upon what kind of parameter it is
    switch (data->ID) {
    case DOOR_PARAMETER_TYPE:
      if (data->subID == USE_OBJECT_HANDLE) {
        if (filter_on || data->int_val == OBJECT_HANDLE_NONE || strlen(data->str_val) == 0)
          index = OBJECT_NONE_HANDLE;
        else
          index = FindDoorInList(data->str_val);
      } else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, index, data->name);
      break;
    case OBJECT_PARAMETER_TYPE:
      if (data->subID == USE_OBJECT_HANDLE) {
        if (filter_on || data->int_val == OBJECT_HANDLE_NONE || strlen(data->str_val) == 0)
          index = OBJECT_NONE_HANDLE;
        else
          index = FindObjectInList(data->str_val);
      } else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, index, data->name);
      break;
    case ROOM_PARAMETER_TYPE:
      if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindRoomInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case TRIGGER_PARAMETER_TYPE:
      if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindTriggerInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case INT_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case BOOL_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case FLOAT_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%f:%s", data->type, data->ID, data->float_val1, data->name);
      break;
    case VECTOR_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%f:%f:%f:%s", data->type, data->ID, data->float_val1, data->float_val2,
               data->float_val3, data->name);
      break;
    case STRING_PARAMETER_TYPE:
      if (filter_on || strlen(data->str_val) == 0)
        tmp_name = NOT_SPECIFIED_MSG;
      else
        tmp_name = data->str_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%s:%s", data->type, data->ID, tmp_name.GetBuffer(0), data->name);
      break;
    case PERCENTAGE_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%f:%s", data->type, data->ID, data->float_val1, data->name);
      break;
    case ENUM_PARAMETER_TYPE:
      if (DALLAS_SAVE_VERSION >= 2) {
        cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, data->int_val, data->name);
      } else {
        cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      }
      break;
    case SCRIPT_PARAMETER_TYPE:
      if (filter_on)
        index = NOT_SPECIFIED_TYPE;
      else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case SOUND_PARAMETER_TYPE:
      if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindSoundInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case SPECNAME_PARAMETER_TYPE:
      if (filter_on || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindSpecnameInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case TEXTURE_PARAMETER_TYPE:
      if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindTextureInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case FLAG_PARAMETER_TYPE:
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, data->int_val, data->name);
      break;
    case PATH_PARAMETER_TYPE:
      if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindPathInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    case MATCEN_PARAMETER_TYPE:
      if (data->subID == USE_MATCEN_VALUE) {
        if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
          index = NOT_SPECIFIED_TYPE;
        else
          index = FindMatcenInList(data->str_val);
      } else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, index, data->name);
      break;
    case LEVEL_GOAL_PARAMETER_TYPE:
      if (data->subID == USE_LEVEL_GOAL_VALUE) {
        if (filter_on || data->int_val == NOT_SPECIFIED_TYPE || strlen(data->str_val) == 0)
          index = NOT_SPECIFIED_TYPE;
        else {
          index = FindGoalInList(data->str_val);
        }
      } else
        index = data->int_val;
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%d:%s", data->type, data->ID, data->subID, index, data->name);
      break;
    case STRM_AUDIO_PARAMETER_TYPE:
      if (filter_on || strlen(data->str_val) == 0)
        index = NOT_SPECIFIED_TYPE;
      else
        index = FindStrmAudioInList(data->str_val);
      cfprintf(CurrentOutputFile, "%02d:%d:%d:%s", data->type, data->ID, index, data->name);
      break;
    default:
      cfprintf(CurrentOutputFile, "%02d:%d:%s", data->type, data->ID, data->name);
      break;
    }
    break;
  case PARAMETER_OPERATOR_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  case UNKNOWN_NODE:
    cfprintf(CurrentOutputFile, "%02d:%d", data->type, data->ID);
    break;
  default:
    cfprintf(CurrentOutputFile, "%02d:%d", UNKNOWN_NODE, data->ID);
    break;
  }
  O((" "));
}

/////////////////////////////////////////////////////////////////////////////
// Object Handle List Functions
/////////////////////////////////////////////////////////////////////////////

// Sets up the object handle list
void CDallasMainDlg::InitObjectHandleList(void) { m_NumObjectHandles = 0; }

// Clears the object handle list
void CDallasMainDlg::ClearObjectHandleList(void) { m_NumObjectHandles = 0; }

// Adds a handle to the list
int CDallasMainDlg::AddToObjectHandleList(int handle) {
  // Is list full?
  if (m_NumObjectHandles == MAX_NAMED_OBJECTS)
    return 0;

  m_ObjectHandleList[m_NumObjectHandles] = handle;
  m_NumObjectHandles++;

  return (m_NumObjectHandles - 1);
}

/////////////////////////////////////////////////////////////////////////////
// Floating Menu Creation Functions
/////////////////////////////////////////////////////////////////////////////

// Fills up the given menu with the object categories
// NOTE: Command ID's of objects items start at the given command_offset
void CDallasMainDlg::FillObjectMenu(CMenu *object_menu, int command_offset, bool show_other) {
  CMenu powerup_submenu, robot_submenu, clutter_submenu, building_submenu, door_submenu, other_submenu;
  int powerups_added, robots_added, clutter_added, buildings_added, doors_added, others_added;
  int i;
  object *objp;

  // Create the category submenus
  powerup_submenu.CreatePopupMenu();
  robot_submenu.CreatePopupMenu();
  clutter_submenu.CreatePopupMenu();
  building_submenu.CreatePopupMenu();
  door_submenu.CreatePopupMenu();
  other_submenu.CreatePopupMenu();

  // Before filling with objects, reset the object handle list
  m_NumObjectHandles = 0;

  // Set the object counts
  powerups_added = 0;
  robots_added = 0;
  clutter_added = 0;
  buildings_added = 0;
  doors_added = 0;
  others_added = 0;

  // Fill the menus with objects that have custom names
  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++) {
    if ((m_NumObjectHandles < MAX_NAMED_OBJECTS) && (objp->name) &&
        (objp->type != OBJ_NONE) /*&& (objp->type != OBJ_PLAYER)*/) {

      // Add the object handle to the handle list
      m_ObjectHandleList[m_NumObjectHandles] = objp->handle;

      // Add menu item to appropriate submenu
      switch (objp->type) {
      case OBJ_POWERUP:
        powerup_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles,
                                   objp->name);
        powerups_added++;
        break;
      case OBJ_ROBOT:
        robot_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles,
                                 objp->name);
        robots_added++;
        break;
      case OBJ_CLUTTER:
        clutter_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles,
                                   objp->name);
        clutter_added++;
        break;
      case OBJ_BUILDING:
        building_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles,
                                    objp->name);
        buildings_added++;
        break;
      case OBJ_DOOR:
        door_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles, objp->name);
        doors_added++;
        break;
      default:
        other_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles,
                                 objp->name);
        others_added++;
        break;
      }
      m_NumObjectHandles++;
    }
  }

  // Add the powerup submenu
  ColumnizePopupMenu(&powerup_submenu);
  if (powerups_added == 0)
    object_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)powerup_submenu.Detach(), "Powerup");
  else
    object_menu->AppendMenu(MF_POPUP, (UINT_PTR)powerup_submenu.Detach(), "Powerup");

  // Add the robot submenu
  ColumnizePopupMenu(&robot_submenu);
  if (robots_added == 0)
    object_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)robot_submenu.Detach(), "Robot");
  else
    object_menu->AppendMenu(MF_POPUP, (UINT_PTR)robot_submenu.Detach(), "Robot");

  // Add the clutter submenu
  ColumnizePopupMenu(&clutter_submenu);
  if (clutter_added == 0)
    object_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)clutter_submenu.Detach(), "Clutter");
  else
    object_menu->AppendMenu(MF_POPUP, (UINT_PTR)clutter_submenu.Detach(), "Clutter");

  // Add the building submenu
  ColumnizePopupMenu(&building_submenu);
  if (buildings_added == 0)
    object_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)building_submenu.Detach(), "Building");
  else
    object_menu->AppendMenu(MF_POPUP, (UINT_PTR)building_submenu.Detach(), "Building");

  // Add the door submenu
  ColumnizePopupMenu(&door_submenu);
  if (doors_added == 0)
    object_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)door_submenu.Detach(), "Door");
  else
    object_menu->AppendMenu(MF_POPUP, (UINT_PTR)door_submenu.Detach(), "Door");

  // Add the other submenu
  ColumnizePopupMenu(&other_submenu);
  if (!show_other || others_added == 0)
    object_menu->AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)other_submenu.Detach(), "Other");
  else
    object_menu->AppendMenu(MF_POPUP, (UINT_PTR)other_submenu.Detach(), "Other");
}

// Fills up the given menu with the named objects of the specified type
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillObjectTypeMenu(CMenu *object_menu, int command_offset, int obj_type) {
  int objects_added;
  int i;
  object *objp;

  // Before filling with objects, reset the object handle list
  m_NumObjectHandles = 0;

  // Set the object counts
  objects_added = 0;

  // Fill the menus with objects that have custom names
  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++) {
    if ((m_NumObjectHandles < MAX_NAMED_OBJECTS) && (objp->name) && (objp->type == obj_type)) {

      // Add the object handle to the handle list
      m_ObjectHandleList[m_NumObjectHandles] = objp->handle;

      // Add the menu item
      object_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + m_NumObjectHandles, objp->name);
      objects_added++;
      m_NumObjectHandles++;
    }
  }

  return (objects_added);
}

// Fills up the given menu with the named rooms
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillRoomMenu(CMenu *room_menu, int command_offset) {
  int rooms_added;
  int i;
  room *rp;

  // Set the room count
  rooms_added = 0;

  // Fill the menus with objects that have custom names
  for (i = 0, rp = Rooms; i <= Highest_room_index; i++, rp++) {
    if ((rp->used) && (rp->name)) {
      room_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + i, rp->name);
      rooms_added++;
    }
  }

  return (rooms_added);
}

// Fills up the given menu with the trigger list
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillTriggerMenu(CMenu *trigger_menu, int command_offset) {
  int t, triggers_added;
  trigger *tp;

  // Scan the list, adding triggers to the list
  triggers_added = 0;

  for (t = 0, tp = Triggers; (t < Num_triggers && t < MAX_NAMED_TRIGGERS); t++, tp++) {
    if (strlen(tp->name) > 0) {
      trigger_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + t, tp->name);
      triggers_added++;
    }
  }

  return (triggers_added);
}

// Fills up the given menu with the path list
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillPathMenu(CMenu *path_menu, int command_offset) {
  int p, paths_added;

  // Scan the list, adding triggers to the list
  paths_added = 0;

  for (p = 0; p < MAX_GAME_PATHS; p++) {
    if (GamePaths[p].used && strlen(GamePaths[p].name) > 0) {
      path_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + p, GamePaths[p].name);
      paths_added++;
    }
  }

  return (paths_added);
}

// Fills up the given menu with the matcen list
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillMatcenMenu(CMenu *matcen_menu, int command_offset) {
  int p, matcens_added;

  // Scan the list, adding triggers to the list
  matcens_added = 0;

  for (p = 0; p < MAX_MATCENS; p++) {
    if (MatcenValid(p)) {
      char matcen_name[MAX_MATCEN_NAME_LEN + 1];
      Matcen[p]->GetName(matcen_name);
      matcen_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + p, matcen_name);
      matcens_added++;
    }
  }

  return (matcens_added);
}

// Fills up the given menu with the level goal list
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillLevelGoalMenu(CMenu *level_goal_menu, int command_offset) {
  int p, goals_added, num_goals;

  // Scan the list, adding triggers to the list
  goals_added = 0;

  num_goals = Level_goals.GetNumGoals();
  for (p = 0; p < num_goals; p++) {
    char goal_name[_MAX_PATH + 1];
    if (Level_goals.GoalGetName(p, goal_name, _MAX_PATH) >= 0) {
      level_goal_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + p, goal_name);
      goals_added++;
    }
  }

  return (goals_added);
}

// Fills up the given menu with the Script ID List
// NOTE: Command ID's of objects items start at the given command_offset
#define MAX_SCRIPT_MENU_NAME_LEN 32
int CDallasMainDlg::FillScriptMenu(CMenu *script_menu, int command_offset) {
  HTREEITEM script_node;
  tTreeNodeData *data;
  int scripts_added, child_pos;

  // Scan the list, adding each script to the list
  scripts_added = 0;
  child_pos = 0;

  script_node = m_ScriptTree.GetChildItem(TVI_ROOT);
  while (script_node != NULL) {
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(script_node);
    if (data->type == SCRIPT_HEADER_NODE) {
      CString menu_string;
      FormatTreeText(menu_string, data);

      // Truncate the name (if necessary) so that more will fit
      char menu_name[MAX_SCRIPT_MENU_NAME_LEN + 3 + 1];
      strncpy(menu_name, menu_string.GetBuffer(0), MAX_SCRIPT_MENU_NAME_LEN);
      menu_name[MAX_SCRIPT_MENU_NAME_LEN] = '\0';
      if (menu_string.GetLength() > MAX_SCRIPT_MENU_NAME_LEN) {
        strcat(menu_name, "...");
      }

      script_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + child_pos, menu_name);
      scripts_added++;
    }
    script_node = m_ScriptTree.GetNextSiblingItem(script_node);
    child_pos++;
  }

  return (scripts_added);
}

// Fills up the given menu with the logical operations
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillLogOpMenu(CMenu *log_op_menu, int command_offset) {
  int log_ops_added;

  // Scan the list, adding triggers to the list
  log_ops_added = 0;
  log_op_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + AND_TYPE, "AND");
  log_op_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + OR_TYPE, "OR");

  return (log_ops_added);
}

// Fills up the given menu with the appropriate expression operators
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillExpOpMenu(CMenu *exp_op_menu, int command_offset, int op_type) {
  int exp_ops_added = 0;
  int j;

  // Scan the list, adding triggers to the list
  for (j = 0; expop_info[j].type >= 0; j++) {
    if (op_type == expop_info[j].op_type) {
      exp_op_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + expop_info[j].type,
                              expop_info[j].menu_name);
      exp_ops_added++;
    } else
      exp_op_menu->AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, command_offset + expop_info[j].type,
                              expop_info[j].menu_name);
  }

  return (exp_ops_added);
}

// Fills up the given menu with the literal's available
// NOTE: Command ID's of objects items start at the given command_offset
int CDallasMainDlg::FillLiteralMenu(CMenu *literal_menu, int command_offset, int enum_command_offset,
                                    int flag_command_offset, int valid_type, char *valid_name) {
  CMenu enum_submenu, flag_submenu;
  int literals_added, j;

  // Create the enum/flag submenus
  enum_submenu.CreatePopupMenu();
  flag_submenu.CreatePopupMenu();

  int types_added = FillEnumTypesMenu(&enum_submenu, enum_command_offset, valid_name);
  int flag_types_added = FillFlagTypesMenu(&flag_submenu, flag_command_offset, valid_name);

  // Scan the list, adding literals
  literals_added = 0;

  for (j = 0; param_menu_item[j].type >= 0; j++) {
    if (valid_type == ANY_PARAMETER_TYPE || valid_type == param_menu_item[j].type) {
      if (j == ENUM_PARAMETER_TYPE) {
        ColumnizePopupMenu(&enum_submenu);
        if (types_added > 0)
          literal_menu->AppendMenu(MF_POPUP, (UINT_PTR)enum_submenu.Detach(), param_menu_item[j].name);
        else
          literal_menu->AppendMenu(MF_GRAYED | MF_POPUP, (UINT_PTR)enum_submenu.Detach(), param_menu_item[j].name);
      } else if (j == FLAG_PARAMETER_TYPE) {
        ColumnizePopupMenu(&flag_submenu);
        if (flag_types_added > 0)
          literal_menu->AppendMenu(MF_POPUP, (UINT_PTR)flag_submenu.Detach(), param_menu_item[j].name);
        else
          literal_menu->AppendMenu(MF_GRAYED | MF_POPUP, (UINT_PTR)flag_submenu.Detach(), param_menu_item[j].name);
      } else
        literal_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + param_menu_item[j].type,
                                 param_menu_item[j].name);
      literals_added++;
    } else
      literal_menu->AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, command_offset + param_menu_item[j].type,
                               param_menu_item[j].name);
  }

  return (literals_added);
}

// Fills up the given menu with the Condition options
// NOTE: Command ID's of objects items start at the given command_offset
void CDallasMainDlg::FillConditionMenu(CMenu *condition_menu, int command_offset) {
  int qbin_cmd_offset, qcomp_cmd_offset;
  CMenu qbin_submenu, qcomp_submenu;

  if (command_offset == ADD_CONDITION_ID_RANGE_START) {
    qbin_cmd_offset = ADD_COND_QBIN_ID_RANGE_START;
    qcomp_cmd_offset = ADD_COND_QCOMP_ID_RANGE_START;
  } else {
    qbin_cmd_offset = REPLACE_COND_QBIN_ID_RANGE_START;
    qcomp_cmd_offset = REPLACE_COND_QCOMP_ID_RANGE_START;
  }

  qbin_submenu.CreatePopupMenu();
  FillQueryMenu(&qbin_submenu, qbin_cmd_offset, BOOL_PARAMETER_TYPE, "");

  qcomp_submenu.CreatePopupMenu();
  FillQueryMenu(&qcomp_submenu, qcomp_cmd_offset, ANY_PARAMETER_TYPE, "");

  // Add basic condition types to the list
  condition_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + ALWAYS_STATEMENT, ALWAYS_STRING);
  condition_menu->AppendMenu(MF_SEPARATOR, 0, "");
  condition_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + BINARY_STATEMENT,
                             "Default Binary Statement");
  condition_menu->AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, command_offset + COMPARISON_STATEMENT,
                             "Default Comparison Statement");
  condition_menu->AppendMenu(MF_SEPARATOR, 0, "");

  ColumnizePopupMenu(&qbin_submenu);
  condition_menu->AppendMenu(MF_POPUP, (UINT_PTR)qbin_submenu.Detach(), "Binary Statement with Query");
  ColumnizePopupMenu(&qcomp_submenu);
  condition_menu->AppendMenu(MF_POPUP, (UINT_PTR)qcomp_submenu.Detach(), "Comparison Statement with Query");
}

// Creates the Popup menu for the Script Header node
void CDallasMainDlg::DisplayScriptHeaderNodeMenu(POINT *point) {
  // Create the popup menu
  CMenu main_menu;
  main_menu.CreatePopupMenu();
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Enter Script Description...");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");
  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Script Owner node
void CDallasMainDlg::DisplayScriptOwnerNodeMenu(POINT *point) {
  // Create the popup menu
  int triggers_added;
  CMenu main_menu, object_submenu, trigger_submenu;
  main_menu.CreatePopupMenu();

  // Fill the object menu
  object_submenu.CreatePopupMenu();
  FillObjectMenu(&object_submenu, ASSIGN_OBJECT_ID_RANGE_START, TRUE);
  ColumnizePopupMenu(&object_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)object_submenu.Detach(), "Object");

  trigger_submenu.CreatePopupMenu();
  triggers_added = FillTriggerMenu(&trigger_submenu, ASSIGN_TRIGGER_ID_RANGE_START);
  ColumnizePopupMenu(&trigger_submenu);
  if (triggers_added == 0)
    main_menu.AppendMenu(MF_POPUP | MF_GRAYED, (UINT_PTR)trigger_submenu.Detach(), "Trigger");
  else
    main_menu.AppendMenu(MF_POPUP, (UINT_PTR)trigger_submenu.Detach(), "Trigger");

  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_LEVEL_ID, "Level");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");
  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Script Event node
void CDallasMainDlg::DisplayScriptEventNodeMenu(POINT *point, int owner_type, bool has_a_door_me) {
  int j;

  // Create the popup menu
  CMenu main_menu;
  main_menu.CreatePopupMenu();

  for (j = 0; event_info[j].type >= 0; j++) {
    if ((owner_type == OBJECT_TYPE && (event_info[j].flags & OBJECT_MASK)) ||
        (owner_type == TRIGGER_TYPE && (event_info[j].flags & TRIGGER_MASK)) ||
        (owner_type == LEVEL_TYPE && (event_info[j].flags & LEVEL_MASK)) ||
        (has_a_door_me && (event_info[j].flags & DOOR_OBJECT_MASK)))
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_EVENT_ID_RANGE_START + event_info[j].type,
                           event_info[j].name);
    else
      main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_EVENT_ID_RANGE_START + event_info[j].type,
                           event_info[j].name);
  }

  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");

  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Logical Operator node
void CDallasMainDlg::DisplayLogicalOperatorNodeMenu(POINT *point) {
  // Create the popup menu
  CMenu main_menu, insert_logop_submenu, condition_submenu, add_logop_submenu;
  CMenu replace_logop_submenu, replace_condition_submenu;

  insert_logop_submenu.CreatePopupMenu();
  FillLogOpMenu(&insert_logop_submenu, INSERT_LOGOP_ID_RANGE_START);

  condition_submenu.CreatePopupMenu();
  FillConditionMenu(&condition_submenu, ADD_CONDITION_ID_RANGE_START);

  add_logop_submenu.CreatePopupMenu();
  FillLogOpMenu(&add_logop_submenu, ADD_LOGOP_ID_RANGE_START);

  replace_condition_submenu.CreatePopupMenu();
  FillConditionMenu(&replace_condition_submenu, REPLACE_CONDITION_ID_RANGE_START);

  replace_logop_submenu.CreatePopupMenu();
  FillLogOpMenu(&replace_logop_submenu, REPLACE_LOGOP_ID_RANGE_START);

  main_menu.CreatePopupMenu();
  ColumnizePopupMenu(&insert_logop_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)insert_logop_submenu.Detach(), "Insert Logical Operator");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  ColumnizePopupMenu(&condition_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)condition_submenu.Detach(), "Add a New Condition");
  ColumnizePopupMenu(&add_logop_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)add_logop_submenu.Detach(), "Add Logical Operator");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  ColumnizePopupMenu(&replace_condition_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_condition_submenu.Detach(), "Replace with a Condition");
  ColumnizePopupMenu(&replace_logop_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_logop_submenu.Detach(), "Replace with a New Logical Operator");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, DELETE_ALL_ID, "Delete this Operator");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");

  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Conditional Statement node
void CDallasMainDlg::DisplayConditionalStatementNodeMenu(POINT *point) {
  // Create the popup menu
  CMenu main_menu, log_op_submenu;
  CMenu replace_logop_submenu, replace_condition_submenu;

  log_op_submenu.CreatePopupMenu();
  FillLogOpMenu(&log_op_submenu, INSERT_LOGOP_ID_RANGE_START);

  replace_condition_submenu.CreatePopupMenu();
  FillConditionMenu(&replace_condition_submenu, REPLACE_CONDITION_ID_RANGE_START);

  replace_logop_submenu.CreatePopupMenu();
  FillLogOpMenu(&replace_logop_submenu, REPLACE_LOGOP_ID_RANGE_START);

  main_menu.CreatePopupMenu();
  ColumnizePopupMenu(&log_op_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)log_op_submenu.Detach(), "Insert Logical Operator");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  ColumnizePopupMenu(&replace_condition_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_condition_submenu.Detach(), "Replace with a New Condition");
  ColumnizePopupMenu(&replace_logop_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_logop_submenu.Detach(), "Replace with a Logical Operator");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, DELETE_ALL_ID, "Delete this Condition");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");

  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Expression node
void CDallasMainDlg::DisplayExpressionNodeMenu(POINT *point, int valid_return_type, char *valid_return_name) {
  CMenu main_menu, replace_with_query_submenu, replace_with_literal_submenu;

  replace_with_query_submenu.CreatePopupMenu();
  FillQueryMenu(&replace_with_query_submenu, REPLACE_QUERY_ID_RANGE_START, valid_return_type, valid_return_name);

  replace_with_literal_submenu.CreatePopupMenu();
  FillLiteralMenu(&replace_with_literal_submenu, REPLACE_LITERAL_ID_RANGE_START, REPLACE_LIT_ENUM_ID_RANGE_START,
                  REPLACE_LIT_FLAG_ID_RANGE_START, valid_return_type, valid_return_name);

  main_menu.CreatePopupMenu();
  ColumnizePopupMenu(&replace_with_query_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_with_query_submenu.Detach(), "Replace with Query");
  ColumnizePopupMenu(&replace_with_literal_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_with_literal_submenu.Detach(), "Replace with Literal");

  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");
  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Expression Operator node
void CDallasMainDlg::DisplayExpressionOperatorNodeMenu(POINT *point, int op_type) {
  CMenu main_menu;
  main_menu.CreatePopupMenu();

  FillExpOpMenu(&main_menu, ASSIGN_EXPOP_ID_RANGE_START, op_type);

  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");
  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Action Statement node
void CDallasMainDlg::DisplayActionStatementNodeMenu(POINT *point) {
  // Create the popup menu
  CMenu main_menu;
  CMenu insert_actions_submenu, replace_actions_submenu;

  insert_actions_submenu.CreatePopupMenu();
  insert_actions_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_DO_NOTHING_ACTION_ID, DO_NOTHING_STRING);
  insert_actions_submenu.AppendMenu(MF_SEPARATOR, 0, "");
  FillActionMenu(&insert_actions_submenu, ADD_ACTION_ID_RANGE_START);

  replace_actions_submenu.CreatePopupMenu();
  replace_actions_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, REPLACE_DO_NOTHING_ACTION_ID,
                                     DO_NOTHING_STRING);
  replace_actions_submenu.AppendMenu(MF_SEPARATOR, 0, "");
  FillActionMenu(&replace_actions_submenu, REPLACE_ACTION_ID_RANGE_START);

  main_menu.CreatePopupMenu();
  ColumnizePopupMenu(&insert_actions_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)insert_actions_submenu.Detach(), "Insert a New Action");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_IF_THEN_CLAUSE_ID, "Insert a Nested IF-THEN Clause");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_IF_THEN_ELSE_CLAUSE_ID,
                       "Insert a Nested IF-THEN-ELSE Clause");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  ColumnizePopupMenu(&replace_actions_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_actions_submenu.Detach(), "Replace with a Different Action");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, DELETE_ALL_ID, "Delete");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");

  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Creates the Popup menu for the Action Header node
void CDallasMainDlg::DisplayActionHeaderNodeMenu(POINT *point, int level_type, int clause_type, bool can_add_else) {
  // Create the popup menu
  CMenu main_menu, add_actions_submenu, select_extimes_submenu, select_chain_submenu;

  add_actions_submenu.CreatePopupMenu();
  add_actions_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_DO_NOTHING_ACTION_ID, DO_NOTHING_STRING);
  add_actions_submenu.AppendMenu(MF_SEPARATOR, 0, "");
  FillActionMenu(&add_actions_submenu, ADD_ACTION_ID_RANGE_START);

  select_extimes_submenu.CreatePopupMenu();
  select_extimes_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING,
                                    ASSIGN_EXEC_TIME_ID_RANGE_START + ENTER_EXEC_TIMES, "Enter number of times...");
  select_extimes_submenu.AppendMenu(MF_SEPARATOR, 0, "");
  select_extimes_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING,
                                    ASSIGN_EXEC_TIME_ID_RANGE_START + EXECUTE_INFINITELY, "Run Infinitely");
  select_extimes_submenu.AppendMenu(MF_SEPARATOR, 0, "");
  select_extimes_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING,
                                    ASSIGN_EXEC_TIME_ID_RANGE_START + EXECUTE_ONCE, "Once");
  select_extimes_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING,
                                    ASSIGN_EXEC_TIME_ID_RANGE_START + EXECUTE_TWICE, "Twice");

  select_chain_submenu.CreatePopupMenu();
  select_chain_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING,
                                  ASSIGN_CHAIN_ID_RANGE_START + CONTINUE_SCRIPT_CHAIN,
                                  "Continue the Script Chain (DEFAULT)");
  select_chain_submenu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING,
                                  ASSIGN_CHAIN_ID_RANGE_START + BREAK_SCRIPT_CHAIN, "Break the Script Chain");

  main_menu.CreatePopupMenu();
  ColumnizePopupMenu(&select_extimes_submenu);
  if (level_type == TOP_LEVEL)
    main_menu.AppendMenu(MF_POPUP, (UINT_PTR)select_extimes_submenu.Detach(), "Select Max Times to Execute");
  else
    main_menu.AppendMenu(MF_GRAYED | MF_POPUP, (UINT_PTR)select_extimes_submenu.Detach(),
                         "Select Max Times to Execute");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  if (level_type == TOP_LEVEL)
    main_menu.AppendMenu(MF_POPUP, (UINT_PTR)select_chain_submenu.Detach(), "Select Script Chaining Option");
  else
    main_menu.AppendMenu(MF_GRAYED | MF_POPUP, (UINT_PTR)select_chain_submenu.Detach(),
                         "Select Script Chaining Option");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  ColumnizePopupMenu(&add_actions_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)add_actions_submenu.Detach(), "Add a New Action");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_IF_THEN_CLAUSE_ID, "Add a Nested IF-THEN Clause");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_IF_THEN_ELSE_CLAUSE_ID,
                       "Add a Nested IF-THEN-ELSE Clause");
  if (can_add_else)
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ADD_ELSE_CLAUSE_ID, "Append an ELSE to this Clause");
  else
    main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ADD_ELSE_CLAUSE_ID, "Append an ELSE to this Clause");
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, DELETE_CHILDREN_ONLY_ID,
                       "Delete all Child Actions and Clauses");
  if (level_type == TOP_LEVEL)
    main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, DELETE_ALL_ID, "Delete this Entire IF-THEN Clause");
  else {
    if (clause_type == THEN_CLAUSE)
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, DELETE_ALL_ID, "Delete this Entire IF-THEN Clause");
    else
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, DELETE_ALL_ID, "Delete this Else Clause");
  }
  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");

  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Displays the popup menus for the various parameter types
void CDallasMainDlg::DisplayParameterNodeMenu(POINT *point, int param_type, char *param_name, int valid_return_type,
                                              char *valid_return_name, bool has_an_it, bool has_a_me,
                                              bool has_a_door_me, bool has_a_goalID, bool has_a_timerID,
                                              bool has_a_matcenID, bool has_a_levgoalID) {
  CMenu main_menu, replace_with_query_submenu, replace_with_literal_submenu;

  replace_with_query_submenu.CreatePopupMenu();
  FillQueryMenu(&replace_with_query_submenu, REPLACE_QUERY_ID_RANGE_START, valid_return_type, valid_return_name);

  replace_with_literal_submenu.CreatePopupMenu();
  FillLiteralMenu(&replace_with_literal_submenu, REPLACE_LITERAL_ID_RANGE_START, REPLACE_LIT_ENUM_ID_RANGE_START,
                  REPLACE_LIT_FLAG_ID_RANGE_START, valid_return_type, valid_return_name);

  main_menu.CreatePopupMenu();

  switch (param_type) {
  case DOOR_PARAMETER_TYPE: {
    if (has_a_door_me)
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_ME_ID, "OWNER");
    else
      main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_ME_ID, "OWNER");

    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    FillObjectTypeMenu(&main_menu, ASSIGN_OBJECT_ID_RANGE_START, OBJ_DOOR);
  } break;
  case OBJECT_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_NONE_ID, NONE_STRING);
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");

    if (has_a_me)
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_ME_ID, "OWNER");
    else
      main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_ME_ID, "OWNER");

    if (has_an_it)
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_IT_ID, "IT");
    else
      main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_OBJECT_IT_ID, "IT");

    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    FillObjectMenu(&main_menu, ASSIGN_OBJECT_ID_RANGE_START, TRUE);
  } break;
  case ROOM_PARAMETER_TYPE: {
    FillRoomMenu(&main_menu, ASSIGN_ROOM_ID_RANGE_START);
  } break;
  case TRIGGER_PARAMETER_TYPE: {
    FillTriggerMenu(&main_menu, ASSIGN_TRIGGER_ID_RANGE_START);
  } break;
  case INT_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Enter Integer Value...");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  } break;
  case BOOL_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_TRUE_ID, "TRUE");
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_FALSE_ID, "FALSE");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  } break;
  case FLOAT_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Enter Float Value...");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  } break;
  case VECTOR_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Enter Vector Values...");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  } break;
  case STRING_PARAMETER_TYPE: {
    int j, num_msgs;

    // Fill list with Message ID Names
    num_msgs = m_MessageList.GetCount();
    for (j = 0; j < num_msgs; j++) {
      CString msg_name;
      m_MessageList.GetText(j, msg_name);
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_MESSAGE_ID_RANGE_START + j,
                           msg_name.GetBuffer(0));
    }
  } break;
  case PERCENTAGE_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Enter Percentage Value...");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  } break;
  case ENUM_PARAMETER_TYPE: {
    if (strcmp(param_name, "GoalID") == 0) {
      if (has_a_goalID)
        main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_ENUM_GOAL_ID, "GOAL ID");
      else
        main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_ENUM_GOAL_ID, "GOAL ID");
      main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    }

    if (strcmp(param_name, "TimerID") == 0) {
      if (has_a_timerID)
        main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_ENUM_TIMER_ID, "TIMER ID");
      else
        main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_ENUM_TIMER_ID, "TIMER ID");
      main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    }

    if (strcmp(param_name, "MatcenID") == 0) {
      if (has_a_matcenID)
        main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_ENUM_MATCEN_ID, "MATCEN ID");
      else
        main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_ENUM_MATCEN_ID, "MATCEN ID");
      main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    }

    FillEnumValuesMenu(&main_menu, ASSIGN_ENUM_VALUE_ID_RANGE_START, param_name);
  } break;
  case SCRIPT_PARAMETER_TYPE: {
    FillScriptMenu(&main_menu, ASSIGN_SCRIPT_ID_RANGE_START);
  } break;
  case SOUND_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID,
                         "Select a Different Sound...");
  } break;
  case SPECNAME_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Enter a Specific Name...");
  } break;
  case TEXTURE_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID,
                         "Select a Different Texture...");
  } break;
  case FLAG_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID, "Select the Flags to Set...");
  } break;
  case PATH_PARAMETER_TYPE: {
    FillPathMenu(&main_menu, ASSIGN_PATH_ID_RANGE_START);
  } break;
  case MATCEN_PARAMETER_TYPE: {
    if (has_a_matcenID)
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_MATCEN_EVENT_ID, "MATCEN ID");
    else
      main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_MATCEN_EVENT_ID, "MATCEN ID");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    FillMatcenMenu(&main_menu, ASSIGN_MATCEN_ID_RANGE_START);
  } break;
  case LEVEL_GOAL_PARAMETER_TYPE: {
    if (has_a_levgoalID)
      main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_LEVEL_GOAL_ID, "LEVEL GOAL ID");
    else
      main_menu.AppendMenu(MF_GRAYED | MF_UNCHECKED | MF_STRING, ASSIGN_LEVEL_GOAL_ID, "LEVEL GOAL ID");
    main_menu.AppendMenu(MF_SEPARATOR, 0, "");
    FillLevelGoalMenu(&main_menu, ASSIGN_LEVEL_GOAL_ID_RANGE_START);
  } break;
  case STRM_AUDIO_PARAMETER_TYPE: {
    main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, ASSIGN_SPECIFIC_VALUE_ID,
                         "Select the Streaming Audio File...");
  } break;
  default:
    break;
  }

  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  ColumnizePopupMenu(&replace_with_query_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_with_query_submenu.Detach(), "Replace with Query");
  ColumnizePopupMenu(&replace_with_literal_submenu);
  main_menu.AppendMenu(MF_POPUP, (UINT_PTR)replace_with_literal_submenu.Detach(), "Replace with Literal");

  main_menu.AppendMenu(MF_SEPARATOR, 0, "");
  main_menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, CANCEL_COMMAND_ID, "Cancel");
  ColumnizePopupMenu(&main_menu);
  main_menu.TrackPopupMenu(0, point->x, point->y, this);
  main_menu.DestroyMenu();
}

// Takes the given popup menu and breaks it into columns
void CDallasMainDlg::ColumnizePopupMenu(CMenu *menu) {
  int screen_height, menu_item_height;
  int item_count;
  int items_per_column;
  int pos;

  if (menu == NULL)
    return;

  item_count = menu->GetMenuItemCount();
  if (item_count == 0)
    return;

  screen_height = GetSystemMetrics(SM_CYSCREEN);
  menu_item_height = GetSystemMetrics(SM_CYMENU);
  if (menu_item_height > 0)
    items_per_column = screen_height / menu_item_height;
  else
    items_per_column = 25;

  // Clip the items per column to a min and max if necessary
  if (items_per_column < 25)
    items_per_column = 25;
  if (items_per_column > 40)
    items_per_column = 40;

  pos = items_per_column;
  while (pos < item_count) {
    CString name;
    UINT id;
    UINT flags;
    UINT state;

    // Get the name of the item
    menu->GetMenuString(pos, name, MF_BYPOSITION);

    // Set the default flags
    flags = MF_BYPOSITION | MF_MENUBARBREAK;

    state = menu->GetMenuState(pos, MF_BYPOSITION);
    if (state & MF_GRAYED)
      flags |= MF_GRAYED;
    if (state & MF_ENABLED)
      flags |= MF_ENABLED;
    if (state & MF_UNCHECKED)
      flags |= MF_UNCHECKED;

    // Get the item ID
    id = menu->GetMenuItemID(pos);
    if (id == 0) { // is it a separator?
      flags |= MF_SEPARATOR;
      id = 0;
    } else if (id == -1) { // is it a popup?
      CMenu *submenu;

      submenu = menu->GetSubMenu(pos);
      if (submenu != NULL) {
        id = (uint32_t)submenu->Detach();
        flags |= MF_POPUP;
      }
    }

    if (name.IsEmpty())
      menu->ModifyMenu(pos, flags, id);
    else
      menu->ModifyMenu(pos, flags, id, name.GetBuffer(0));

    pos += items_per_column;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions to Assign Values To Data Nodes
/////////////////////////////////////////////////////////////////////////////

// Obtains the appropriate script ID
void CDallasMainDlg::AssignScriptID(int pos) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Handle entering Script Header node descriptions
  if (data->type == PARAMETER_NODE && data->ID == SCRIPT_PARAMETER_TYPE) {
    HTREEITEM script_node;
    script_node = GetNthChild(TVI_ROOT, pos + 1);
    if (script_node == NULL)
      return;

    data->int_val = GetScriptID(script_node);
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
  }
}

// Obtains the appropriate data through popup dialogs
void CDallasMainDlg::AssignExecTime(int ID) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Handle entering Script Header node descriptions
  if (data->type == ACTIONS_HEADER_NODE && data->ID == TOP_LEVEL) {
    switch (ID) {
    case ENTER_EXEC_TIMES: {
      CDallasGenericPromptDlg dlg;

      // Display the prompt dialog
      dlg.m_DialogTitle = "Maximum Execution Times Prompt";
      dlg.m_PromptText = "Enter the maximum times to execute script:";
      dlg.m_PromptData.Format("%d", data->subID);
      dlg.m_MaxDataLength = MAX_NDATA_NAME_LEN;

      if (dlg.DoModal() == IDCANCEL)
        return;

      data->subID = atoi(dlg.m_PromptData.GetBuffer(0));
    } break;
    case EXECUTE_INFINITELY:
      data->subID = 0;
      break;
    case EXECUTE_ONCE:
      data->subID = 1;
      break;
    case EXECUTE_TWICE:
      data->subID = 2;
      break;
    }
    UpdateNodeText(selected_node);
    SetModified(TRUE);
  }
}

// Sets the chain option for the action header
void CDallasMainDlg::AssignChainOption(int ID) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Handle entering Script Header node descriptions
  if (data->type == ACTIONS_HEADER_NODE && data->ID == TOP_LEVEL) {
    data->int_val = ID;
    UpdateNodeText(selected_node);
    SetModified(TRUE);
  }
}

// Obtains the appropriate data through popup dialogs
void CDallasMainDlg::AssignSpecificValue(void) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Handle entering Script Header node descriptions
  if (data->type == SCRIPT_HEADER_NODE) {

    CDallasGenericPromptDlg dlg;

    // Display the prompt dialog
    dlg.m_DialogTitle = "Script Description Prompt";
    dlg.m_PromptText = "Enter the new script description:";
    dlg.m_PromptData = data->name;
    dlg.m_MaxDataLength = MAX_NDATA_NAME_LEN;

    if (dlg.DoModal() == IDCANCEL)
      return;

    strncpy(data->name, dlg.m_PromptData.GetBuffer(0), MAX_NDATA_NAME_LEN);
    data->name[MAX_NDATA_NAME_LEN] = '\0';
    UpdateNodeText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Parameter Int value
  if (data->type == PARAMETER_NODE && data->ID == INT_PARAMETER_TYPE) {

    CDallasGenericPromptDlg dlg;

    // Display the prompt dialog
    dlg.m_DialogTitle = "Integer Value Prompt";
    dlg.m_PromptText.Format("Enter value for %s (integer):", data->name);
    dlg.m_PromptData.Format("%d", data->int_val);
    dlg.m_MaxDataLength = MAX_NDATA_NAME_LEN;

    if (dlg.DoModal() == IDCANCEL)
      return;

    int value = atoi(dlg.m_PromptData.GetBuffer(0));

    // If a range is specified, verify that entered value is in it
    CString name_text, default_text, range_text;
    int n, param_type;
    n = GetChildPosition(selected_node);
    param_type = ParseNthParam(m_ScriptTree.GetParentItem(selected_node), n, name_text, default_text, range_text);
    if (param_type >= 0 && !range_text.IsEmpty()) {
      if (!VerifyIntegerRange(value, range_text.GetBuffer(0))) {
        CString msg;
        msg.Format("That value is outside the legal range (%s) for this parameter!", range_text);
        MessageBox(msg, "Invalid Value Entered", MB_OK | MB_ICONEXCLAMATION);
        return;
      }
    }

    data->int_val = value;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Parameter Float value
  if (data->type == PARAMETER_NODE && data->ID == FLOAT_PARAMETER_TYPE) {

    CDallasGenericPromptDlg dlg;

    // Display the prompt dialog
    dlg.m_DialogTitle = "Float Value Prompt";
    dlg.m_PromptText.Format("Enter value for %s (float):", data->name);
    dlg.m_PromptData.Format("%f", data->float_val1);
    dlg.m_MaxDataLength = MAX_NDATA_NAME_LEN;

    if (dlg.DoModal() == IDCANCEL)
      return;

    float value = atof(dlg.m_PromptData.GetBuffer(0));

    // If a range is specified, verify that entered value is in it
    CString name_text, default_text, range_text;
    int n, param_type;
    n = GetChildPosition(selected_node);
    param_type = ParseNthParam(m_ScriptTree.GetParentItem(selected_node), n, name_text, default_text, range_text);
    if (param_type >= 0 && !range_text.IsEmpty()) {
      if (!VerifyFloatRange(value, range_text.GetBuffer(0))) {
        CString msg;
        msg.Format("That value is outside the legal range (%s) for this parameter!", range_text);
        MessageBox(msg, "Invalid Value Entered", MB_OK | MB_ICONEXCLAMATION);
        return;
      }
    }

    data->float_val1 = value;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Parameter Vector value
  if (data->type == PARAMETER_NODE && data->ID == VECTOR_PARAMETER_TYPE) {

    CDallasVectorPromptDialog dlg;

    // Display the prompt dialog
    dlg.m_PromptData1 = data->float_val1;
    dlg.m_PromptData2 = data->float_val2;
    dlg.m_PromptData3 = data->float_val3;

    if (dlg.DoModal() == IDCANCEL)
      return;

    data->float_val1 = dlg.m_PromptData1;
    data->float_val2 = dlg.m_PromptData2;
    data->float_val3 = dlg.m_PromptData3;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Sound value
  if (data->type == PARAMETER_NODE && data->ID == SOUND_PARAMETER_TYPE) {

    CDallasSoundDlg dlg;

    // Display the prompt dialog
    if (data->int_val >= 0 && data->int_val < MAX_SOUNDS && Sounds[data->int_val].used)
      dlg.m_SoundName = Sounds[data->int_val].name;

    if (dlg.DoModal() == IDCANCEL)
      return;

    if (dlg.m_SoundIndex >= 0 && dlg.m_SoundIndex < MAX_SOUNDS && Sounds[dlg.m_SoundIndex].used) {
      data->int_val = dlg.m_SoundIndex;
      strncpy(data->str_val, Sounds[data->int_val].name, MAX_MESSAGE_NAME_LEN);
      data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
    }

    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Streaming Audio value
  if (data->type == PARAMETER_NODE && data->ID == STRM_AUDIO_PARAMETER_TYPE) {

    CDallasStrmAudioDlg dlg;

    // Display the prompt dialog
    if (strlen(data->str_val) > 0)
      dlg.m_Filename = data->str_val;

    if (dlg.DoModal() == IDCANCEL)
      return;

    if (!dlg.m_Filename.IsEmpty()) {
      strncpy(data->str_val, dlg.m_Filename.GetBuffer(0), MAX_MESSAGE_NAME_LEN);
      data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
    }

    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Texture value
  if (data->type == PARAMETER_NODE && data->ID == TEXTURE_PARAMETER_TYPE) {

    CDallasTextureDlg dlg;

    // Display the prompt dialog
    if (data->int_val >= 0 && data->int_val < MAX_TEXTURES && GameTextures[data->int_val].used)
      dlg.m_TextureName = GameTextures[data->int_val].name;

    if (dlg.DoModal() == IDCANCEL)
      return;

    if (dlg.m_TextureIndex >= 0 && dlg.m_TextureIndex < MAX_TEXTURES && GameTextures[dlg.m_TextureIndex].used) {
      data->int_val = dlg.m_TextureIndex;
      strncpy(data->str_val, GameTextures[data->int_val].name, MAX_MESSAGE_NAME_LEN);
      data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
    }

    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Flag value
  if (data->type == PARAMETER_NODE && data->ID == FLAG_PARAMETER_TYPE) {

    CDallasFlagDlg dlg;

    // Display the prompt dialog
    dlg.m_FlagsValue = data->int_val;
    dlg.m_FlagsName = data->name;

    // Get the range (contains valid flags mask)
    CString name_text, default_text, range_text;
    int n, param_type;
    n = GetChildPosition(selected_node);
    param_type = ParseNthParam(m_ScriptTree.GetParentItem(selected_node), n, name_text, default_text, range_text);
    if (param_type >= 0 && !range_text.IsEmpty()) {
      dlg.m_ValidFlagsMask = atoi(range_text.GetBuffer(0));
    }

    if (dlg.DoModal() == IDCANCEL)
      return;

    data->int_val = dlg.m_FlagsValue;

    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Specific Name
  if (data->type == PARAMETER_NODE && data->ID == SPECNAME_PARAMETER_TYPE) {

    CDallasGenericPromptDlg dlg;

    // Display the prompt dialog
    dlg.m_DialogTitle = "Specific Name Prompt";
    dlg.m_PromptText.Format("Enter the specific name for %s:", data->name);
    dlg.m_PromptData = data->str_val;
    dlg.m_MaxDataLength = MAX_MESSAGE_NAME_LEN;

    if (dlg.DoModal() == IDCANCEL)
      return;

    // Check if the message name is valid
    char *newname = dlg.m_PromptData.GetBuffer(0);
    if (strlen(newname) == 0)
      return;
    for (uint32_t j = 0; j < strlen(newname); j++)
      if (newname[j] == '"' || newname[j] == ':') {
        MessageBox("That specific name is invalid!\n\nNo quotes or colons are allowed.", "Invalid Message ID Error",
                   MB_OK | MB_ICONEXCLAMATION);
        return;
      }

    // Copy in the new name
    strncpy(data->str_val, newname, MAX_MESSAGE_NAME_LEN);
    data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Handle entering a Parameter Vector value
  if (data->type == PARAMETER_NODE && data->ID == PERCENTAGE_PARAMETER_TYPE) {

    CDallasGenericPromptDlg dlg;

    // Display the prompt dialog
    dlg.m_DialogTitle = "Percent Value Prompt";
    dlg.m_PromptText.Format("Enter data for %s (as a percentage):", data->name);
    dlg.m_PromptData.Format("%f", data->float_val1 * 100.0);
    dlg.m_MaxDataLength = MAX_NDATA_NAME_LEN;

    if (dlg.DoModal() == IDCANCEL)
      return;

    float value = atof(dlg.m_PromptData.GetBuffer(0)) / 100.0;

    // If a range is specified, verify that entered value is in it
    CString name_text, default_text, range_text;
    int n, param_type;
    n = GetChildPosition(selected_node);
    param_type = ParseNthParam(m_ScriptTree.GetParentItem(selected_node), n, name_text, default_text, range_text);
    if (param_type >= 0 && !range_text.IsEmpty()) {
      if (!VerifyFloatRange(value, range_text.GetBuffer(0))) {
        CString msg;
        msg.Format("That value is outside the legal range (%s) for this parameter!", range_text);
        MessageBox(msg, "Invalid Value Entered", MB_OK | MB_ICONEXCLAMATION);
        return;
      }
    }

    data->float_val1 = value;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // If we're here, then no popup dialog could be displayed,
  // so, instead, display the popup menu for the selected node
  RECT rect;
  if (m_ScriptTree.GetItemRect(selected_node, &rect, TRUE)) {
    POINT pt;

    pt.x = rect.left;
    pt.y = (rect.top + rect.bottom) / 2;
    m_ScriptTree.ClientToScreen(&pt);

    DisplayFloatingPopupMenu(selected_node, pt);
  }
}

// Assigns an owner to a Script Owner Node
void CDallasMainDlg::AssignNamedValue(int type, int handle) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // If it's a script event node, then process accordingly
  if (data->type == SCRIPT_OWNER_NODE) {
    int old_type = data->ID;
    data->ID = type;
    switch (type) {
    case LEVEL_TYPE:
      data->int_val = handle;
      if (old_type != LEVEL_TYPE)
        SetScriptEventType(selected_node, LEVEL_START_EVENT_TYPE);
      break;
    case OBJECT_TYPE:
      if (handle == OBJECT_NONE_HANDLE) {
        data->int_val = OBJECT_HANDLE_NONE;
        data->subID = USE_OBJECT_HANDLE;
        strcpy(data->str_val, "");
      } else {
        data->int_val = m_ObjectHandleList[handle];
        data->subID = USE_OBJECT_HANDLE;
        object *objp = ObjGet(data->int_val);
        if (objp != NULL && objp->name != NULL) {
          strncpy(data->str_val, objp->name, MAX_MESSAGE_NAME_LEN);
          data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
        } else
          strcpy(data->str_val, "");
        if (old_type != OBJECT_TYPE)
          SetScriptEventType(selected_node, COLLIDE_EVENT_TYPE);
      }
      break;
    case TRIGGER_TYPE:
      data->int_val = handle;
      if (data->int_val < 0 || data->int_val >= Num_triggers)
        strcpy(data->str_val, "");
      else {
        strncpy(data->str_val, Triggers[data->int_val].name, MAX_MESSAGE_NAME_LEN);
        data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
      }
      if (old_type != TRIGGER_TYPE)
        SetScriptEventType(selected_node, ACTIVATED_EVENT_TYPE);
      break;
    }
    UpdateNodeText(selected_node);
    SetModified(TRUE);
    HighlightScript(selected_node);
  }

  // If it's a parameter node, then process accordingly
  if (data->type == PARAMETER_NODE) {
    switch (type) {
    case OBJECT_TYPE:
      if (data->ID == OBJECT_PARAMETER_TYPE) {
        if (handle == OBJECT_NONE_HANDLE) {
          data->int_val = OBJECT_HANDLE_NONE;
          data->subID = USE_OBJECT_HANDLE;
          strcpy(data->str_val, "");
        } else if (handle == OBJECT_ME_HANDLE) {
          data->int_val = OBJECT_HANDLE_NONE;
          data->subID = USE_ME_HANDLE;
          strcpy(data->str_val, "");
        } else if (handle == OBJECT_IT_HANDLE) {
          data->int_val = OBJECT_HANDLE_NONE;
          data->subID = USE_IT_HANDLE;
          strcpy(data->str_val, "");
        } else {
          data->int_val = m_ObjectHandleList[handle];
          data->subID = USE_OBJECT_HANDLE;
          object *objp = ObjGet(data->int_val);
          if (objp != NULL && objp->name != NULL) {
            strncpy(data->str_val, objp->name, MAX_MESSAGE_NAME_LEN);
            data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
          } else
            strcpy(data->str_val, "");
        }
      } else if (data->ID == DOOR_PARAMETER_TYPE) {
        if (handle == OBJECT_NONE_HANDLE) {
          data->int_val = OBJECT_HANDLE_NONE;
          data->subID = USE_OBJECT_HANDLE;
          strcpy(data->str_val, "");
        } else if (handle == OBJECT_ME_HANDLE) {
          data->int_val = OBJECT_HANDLE_NONE;
          data->subID = USE_ME_HANDLE;
          strcpy(data->str_val, "");
        } else {
          data->int_val = m_ObjectHandleList[handle];
          data->subID = USE_OBJECT_HANDLE;
          object *objp = ObjGet(data->int_val);
          if (objp != NULL && objp->name != NULL) {
            strncpy(data->str_val, objp->name, MAX_MESSAGE_NAME_LEN);
            data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
          } else
            strcpy(data->str_val, "");
        }
      }
      break;
    case TRIGGER_TYPE:
      if (data->ID == TRIGGER_PARAMETER_TYPE) {
        data->int_val = handle;
        if (data->int_val < 0 || data->int_val >= Num_triggers)
          strcpy(data->str_val, "");
        else {
          strncpy(data->str_val, Triggers[data->int_val].name, MAX_MESSAGE_NAME_LEN);
          data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
        }
      }
      break;
    case ROOM_TYPE:
      if (data->ID == ROOM_PARAMETER_TYPE) {
        data->int_val = handle;
        if (data->int_val < 0 || data->int_val > Highest_room_index)
          strcpy(data->str_val, "");
        else {
          strncpy(data->str_val, Rooms[data->int_val].name, MAX_MESSAGE_NAME_LEN);
          data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
        }
      }
      break;
    case PATH_TYPE:
      if (data->ID == PATH_PARAMETER_TYPE) {
        data->int_val = handle;
        if (data->int_val < 0 || data->int_val >= MAX_GAME_PATHS || !GamePaths[data->int_val].used)
          strcpy(data->str_val, "");
        else {
          strncpy(data->str_val, GamePaths[data->int_val].name, MAX_MESSAGE_NAME_LEN);
          data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
        }
      }
      break;
    case MATCEN_TYPE:
      if (data->ID == MATCEN_PARAMETER_TYPE) {
        if (handle == MATCEN_ID_VALUE) {
          data->subID = USE_MATCEN_EVENT_ID;
          data->int_val = 0;
          strcpy(data->str_val, "");
        } else {
          data->subID = USE_MATCEN_VALUE;
          data->int_val = handle;
          if (!MatcenValid(data->int_val))
            strcpy(data->str_val, "");
          else {
            char matcen_name[MAX_MATCEN_NAME_LEN + 1];
            Matcen[data->int_val]->GetName(matcen_name);
            strncpy(data->str_val, matcen_name, MAX_MESSAGE_NAME_LEN);
            data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
          }
        }
      }
      break;
    case LEVEL_GOAL_TYPE:
      if (data->ID == LEVEL_GOAL_PARAMETER_TYPE) {
        if (handle == LEVEL_GOAL_ID_VALUE) {
          data->subID = USE_LEVEL_GOAL_ID;
          data->int_val = 0;
          strcpy(data->str_val, "");
        } else {
          char goal_name[_MAX_PATH + 1];
          data->subID = USE_LEVEL_GOAL_VALUE;
          data->int_val = handle;
          if (Level_goals.GoalGetName(data->int_val, goal_name, _MAX_PATH) < 0)
            strcpy(data->str_val, "");
          else {
            strncpy(data->str_val, goal_name, MAX_MESSAGE_NAME_LEN);
            data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
          }
        }
      }
      break;
    }
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
  }
}

// Assigns an event type to a Script Event Node
void CDallasMainDlg::AssignEventType(int type) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure it's a script event node
  if (data->type == SCRIPT_EVENT_NODE) {
    data->ID = type;
    UpdateNodeText(selected_node);
    SetModified(TRUE);
  }
}

// Assigns a boolean type to a Bool parameter
void CDallasMainDlg::AssignBooleanValue(int type) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure it's a boolean parameter node
  if (data->type == PARAMETER_NODE && data->ID == BOOL_PARAMETER_TYPE) {
    data->int_val = type;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
  }
}

// Assigns a message name
void CDallasMainDlg::AssignMessageName(int msg_ID) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure it's a boolean parameter node
  if (data->type == PARAMETER_NODE && data->ID == STRING_PARAMETER_TYPE) {
    CString msg_name;
    m_MessageList.GetText(msg_ID, msg_name);
    strncpy(data->str_val, msg_name.GetBuffer(0), MAX_MESSAGE_NAME_LEN);
    data->str_val[MAX_MESSAGE_NAME_LEN] = '\0';
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
  }
}

// Assigns an expression operator type
void CDallasMainDlg::AssignExpOpType(int type) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure it's a script event node
  if (data->type == EXPRESSION_OPERATOR_NODE) {
    data->subID = type;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
  }
}

// Assigns an expression operator type
void CDallasMainDlg::AssignEnumValueType(int type) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure it's a parameter-enum node
  if (data->type == PARAMETER_NODE && data->ID == ENUM_PARAMETER_TYPE) {

    if (type == ENUM_GOALID_VALUE) {
      data->subID = USE_GOALID_VALUE;
      data->int_val = 0;
    } else if (type == ENUM_TIMERID_VALUE) {
      data->subID = USE_TIMERID_VALUE;
      data->int_val = 0;
    } else if (type == ENUM_MATCENID_VALUE) {
      data->subID = USE_MATCENID_VALUE;
      data->int_val = 0;
    } else {
      int DBslot;

      DBslot = GetEnumID(data->name);
      if (DBslot == INVALID_ENUM)
        return;

      if (type < 0 || type >= m_EnumDatabase[DBslot].num_values)
        return;
      data->int_val = m_EnumDatabase[DBslot].values[type].value;
      data->subID = USE_ENUM_VALUE;
    }

    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions to Add Tree Nodes (specific types)
/////////////////////////////////////////////////////////////////////////////

// Adds nested IF-THEN Clause
void CDallasMainDlg::AddNestedIfThenClause(void) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Add node appropriately with respect to selected node
  if (data->type == ACTIONS_HEADER_NODE) {
    CreateDefaultIfThenClause(selected_node, TVI_LAST, NESTED);
    m_ScriptTree.Expand(selected_node, TVE_EXPAND);
  } else {
    CreateDefaultIfThenClause(m_ScriptTree.GetParentItem(selected_node), selected_node, NESTED);
    m_ScriptTree.Expand(m_ScriptTree.GetParentItem(selected_node), TVE_EXPAND);
  }
  SetModified(TRUE);
}

// Adds nested ELSE Clause
void CDallasMainDlg::AddNestedElseClause(void) {
  HTREEITEM selected_node, next_node;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Add node appropriately with respect to selected node
  if (!CanAppendElseToNode(selected_node))
    return;

  // See if there is a node after this one
  next_node = m_ScriptTree.GetNextSiblingItem(selected_node);

  if (next_node == NULL)
    CreateDefaultElseClause(m_ScriptTree.GetParentItem(selected_node), TVI_LAST);
  else
    CreateDefaultElseClause(m_ScriptTree.GetParentItem(next_node), next_node);
  SetModified(TRUE);
}

// Adds nested IF-THEN-ELSE Clause
void CDallasMainDlg::AddNestedIfThenElseClause(void) {
  HTREEITEM selected_node;
  tTreeNodeData *data;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Add node appropriately with respect to selected node
  if (data->type == ACTIONS_HEADER_NODE) {
    CreateDefaultIfThenClause(selected_node, TVI_LAST, NESTED);
    CreateDefaultElseClause(selected_node, TVI_LAST);
    m_ScriptTree.Expand(selected_node, TVE_EXPAND);
  } else {
    CreateDefaultIfThenClause(m_ScriptTree.GetParentItem(selected_node), selected_node, NESTED);
    CreateDefaultElseClause(m_ScriptTree.GetParentItem(selected_node), selected_node);
    m_ScriptTree.Expand(m_ScriptTree.GetParentItem(selected_node), TVE_EXPAND);
  }
  SetModified(TRUE);
}

// Adds a conditional statement node
void CDallasMainDlg::AddConditionalStatementNode(int type, int query_id /*=-1*/) {
  HTREEITEM selected_node, new_condition_node;
  tTreeNodeData *data;

  // Check the ID validity
  if (type < 0 || type >= MAX_CONDITION_TYPES)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for adding a conditional statement
  if (data->type == LOGICAL_OPERATOR_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new condition node
    node_data.type = CONDITIONAL_STATEMENT_NODE;
    node_data.ID = type;

    // Add node appropriately with respect to selected node
    new_condition_node = AddNodeToTree(selected_node, TVI_LAST, &node_data, TRUE);

    // Create default subnodes for a binary condition
    CreateDefaultConditionalStatementSubtree(new_condition_node, type, query_id);

    // Update the new condition node's text to include the expressions
    UpdateNodeText(new_condition_node);
    SetModified(TRUE);
    if (new_condition_node != NULL)
      m_ScriptTree.Expand(new_condition_node, TVE_EXPAND);
  }
}

// Inserts a logical operator node as parent of current node
void CDallasMainDlg::InsertLogicalOperatorNode(int type) {
  HTREEITEM selected_node, new_logop_node;
  tTreeNodeData *data;

  // Check the ID validity
  if (type < 0 || type >= MAX_LOGICAL_OPERATORS)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for inserting a logical operator
  if (data->type == LOGICAL_OPERATOR_NODE || data->type == CONDITIONAL_STATEMENT_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new condition node
    node_data.type = LOGICAL_OPERATOR_NODE;
    node_data.ID = type;

    // Add node appropriately with respect to selected node
    new_logop_node = AddNodeToTree(m_ScriptTree.GetParentItem(selected_node), selected_node, &node_data, TRUE);

    // Now copy the selected item tree over to the new logop
    CopyTree(new_logop_node, TVI_LAST, selected_node);
    m_ScriptTree.Expand(new_logop_node, TVE_EXPAND);

    // Add a default ALWAYS so that the logical operator has TWO children
    CreateDefaultConditionalStatementNode(new_logop_node);

    // Now delete the selected item tree
    m_ScriptTree.SelectItem(new_logop_node);
    FreeTreeItem(selected_node);

    SetModified(TRUE);
  }
}

// Adds a logical operator subtree to the end of selected node's children
void CDallasMainDlg::AddLogicalOperatorNode(int type) {
  HTREEITEM selected_node, new_logop_node;
  tTreeNodeData *data;

  // Check the ID validity
  if (type < 0 || type >= MAX_LOGICAL_OPERATORS)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for inserting a logical operator
  if (data->type == LOGICAL_OPERATOR_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new condition node
    node_data.type = LOGICAL_OPERATOR_NODE;
    node_data.ID = type;

    // Add node appropriately with respect to selected node
    new_logop_node = AddNodeToTree(selected_node, TVI_LAST, &node_data, TRUE);

    // Add a pair of default ALWAYS's so that the logical operator has TWO children
    CreateDefaultConditionalStatementNode(new_logop_node);
    CreateDefaultConditionalStatementNode(new_logop_node);

    if (new_logop_node != NULL)
      m_ScriptTree.Expand(new_logop_node, TVE_EXPAND);

    SetModified(TRUE);
  }
}

// Adds an action statement node
void CDallasMainDlg::AddActionStatementNode(int action_ID) {
  HTREEITEM selected_node, new_action_node;
  tTreeNodeData *data;

  // Check the ID validity
  if ((action_ID < 0 || action_ID >= MAX_ACTIONS) && action_ID != DO_NOTHING_ID)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for adding an Action
  if (data->type == ACTIONS_HEADER_NODE || data->type == ACTION_STATEMENT_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new Action node
    node_data.type = ACTION_STATEMENT_NODE;
    node_data.ID = action_ID;

    // Add node appropriately with respect to selected node
    if (data->type == ACTIONS_HEADER_NODE)
      new_action_node = AddNodeToTree(selected_node, TVI_LAST, &node_data, TRUE);
    else
      new_action_node = AddNodeToTree(m_ScriptTree.GetParentItem(selected_node), selected_node, &node_data, TRUE);

    // If it's a real Action, add in the parameters with appropriate defaults
    AddActionParameterNodes(new_action_node);

    // Update the new action node's text to include the parameters
    UpdateNodeText(new_action_node);
    if (new_action_node != NULL)
      m_ScriptTree.Expand(new_action_node, TVE_EXPAND);

    SetModified(TRUE);
  }
}

// Adds all parameter nodes to the given action node
void CDallasMainDlg::AddActionParameterNodes(HTREEITEM action_node) {
  CString name_text, default_text, range_text;
  tTreeNodeData *data;
  char *desc;

  // Make sure node is valid
  if (action_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(action_node);
  if (data == NULL)
    return;

  // Make sure it's a valid action
  if (data->type != ACTION_STATEMENT_NODE || data->ID < 0 || data->ID >= MAX_ACTIONS)
    return;

  // Get the action description
  desc = GetActionDesc(data->ID);
  if (desc == NULL)
    return;

  // Parse the description, adding default parameter nodes appropriately
  while ((*desc) != '\0') {

    if ((*desc) == '[') { // Note the start of a parameter block
      int param_type = ParseParamBlock(desc, name_text, default_text, range_text);
      if (param_type >= 0 && param_type != UNKNOWN_PARAMETER_TYPE)
        CreateDefaultParameterNode(action_node, TVI_LAST, param_type, name_text.GetBuffer(0),
                                   default_text.GetBuffer(0));
    } else {
      desc++;
    }
  }
  SetModified(TRUE);
}

/* OLD VERSION
// Adds all parameter nodes to the given action node
void CDallasMainDlg::AddActionParameterNodes(HTREEITEM action_node)
{
        tTreeNodeData *data;
        char *desc, *desc_copy;
        int param_type_char, param_type;
        char *param_name;
        bool start_block_found;
        bool type_delim_found;
        int j;

        // Make sure node is valid
        if(action_node==NULL) return;

        // Get the node's data
        data=(tTreeNodeData *)m_ScriptTree.GetItemData(action_node);
        if(data==NULL) return;

        // Make sure it's a valid action
        if(data->type!=ACTION_STATEMENT_NODE || data->ID<0 || data->ID>=MAX_ACTIONS) return;

        // Get the action description
        desc=GetActionDesc(data->ID);
        if(desc==NULL) return;

        // Make a copy of description (so null chars can be added)
        desc_copy=(char *)mem_malloc(strlen(desc)+1);
        if(desc_copy==NULL) {
                MessageBox("ERROR: Out of memory adding action parameter node!","Out of Memory
Error!",MB_OK|MB_ICONEXCLAMATION); return;
        }
        strcpy(desc_copy,desc);

        // Parse the description, adding default parameter nodes appropriately
        j=0;
        start_block_found=FALSE;
        type_delim_found=FALSE;
        param_name=NULL;
        param_type_char=-1;

        while(desc_copy[j]!='\0') {

                if(desc_copy[j]=='[') {				// Note the start of a parameter block
                        start_block_found=TRUE;
                }
                else if(desc_copy[j]==':' && start_block_found) {		// Note the end of parameter type field
                        type_delim_found=TRUE;
                }
                else if(desc_copy[j]==']') {		// If end of block, add the parameter

                        if(param_type_char!=-1 && param_name!=NULL) {

                                desc_copy[j]='\0';	// mark the end of the variable name

                                // Get the parameter type
                                param_type=ConvertParamCharToType(param_type_char);

                                if(param_type!=UNKNOWN_PARAMETER_TYPE)
                                        CreateDefaultParameterNode(action_node,TVI_LAST,param_type,param_name);
                        }

                        start_block_found=FALSE;
                        type_delim_found=FALSE;
                        param_name=NULL;
                        param_type_char=-1;
                }
                else if(start_block_found && param_type_char==-1) {
                        param_type_char=desc_copy[j];
                }
                else if(type_delim_found && param_name==NULL) {
                        param_name=&desc_copy[j];
                }

                j++;
        }

        // Free up the copy memory
        mem_free(desc_copy);
}
*/

// Adds all parameter nodes to the given expression (query) node
void CDallasMainDlg::AddQueryParameterNodes(HTREEITEM query_node) {
  CString name_text, default_text, range_text;
  tTreeNodeData *data;
  char *desc;

  // Make sure node is valid
  if (query_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(query_node);
  if (data == NULL)
    return;

  // Make sure it's a valid action
  if (data->type != EXPRESSION_NODE || data->ID < 0 || data->ID >= MAX_QUERIES)
    return;

  // Get the action description
  desc = GetQueryDesc(data->ID);
  if (desc == NULL)
    return;

  // Parse the description, adding default parameter nodes appropriately
  while ((*desc) != '\0') {

    if ((*desc) == '[') { // Note the start of a parameter block
      int param_type = ParseParamBlock(desc, name_text, default_text, range_text);
      if (param_type >= 0 && param_type != UNKNOWN_PARAMETER_TYPE)
        CreateDefaultParameterNode(query_node, TVI_LAST, param_type, name_text.GetBuffer(0), default_text.GetBuffer(0));
    } else {
      desc++;
    }
  }
  SetModified(TRUE);
}

/*
// Adds all parameter nodes to the given expression (query) node
void CDallasMainDlg::AddQueryParameterNodes(HTREEITEM query_node)
{
        tTreeNodeData *data;
        char *desc, *desc_copy;
        int param_type_char, param_type;
        char *param_name;
        bool start_block_found;
        bool type_delim_found;
        int j;

        // Make sure node is valid
        if(query_node==NULL) return;

        // Get the node's data
        data=(tTreeNodeData *)m_ScriptTree.GetItemData(query_node);
        if(data==NULL) return;

        // Make sure it's a valid action
        if(data->type!=EXPRESSION_NODE || data->ID<0 || data->ID>=MAX_QUERIES) return;

        // Get the action description
        desc=GetQueryDesc(data->ID);
        if(desc==NULL) return;

        // Make a copy of description (so null chars can be added)
        desc_copy=(char *)mem_malloc(strlen(desc)+1);
        if(desc_copy==NULL) {
                MessageBox("ERROR: Out of memory adding query parameter node!","Out of Memory
Error!",MB_OK|MB_ICONEXCLAMATION); return;
        }
        strcpy(desc_copy,desc);

        // Parse the description, adding default parameter nodes appropriately
        j=0;
        start_block_found=FALSE;
        type_delim_found=FALSE;
        param_name=NULL;
        param_type_char=-1;

        while(desc_copy[j]!='\0') {

                if(desc_copy[j]=='[') {				// Note the start of a parameter block
                        start_block_found=TRUE;
                }
                else if(desc_copy[j]==':' && start_block_found) {		// Note the end of parameter type field
                        type_delim_found=TRUE;
                }
                else if(desc_copy[j]==']') {		// If end of block, add the parameter

                        if(param_type_char!=-1 && param_name!=NULL) {

                                desc_copy[j]='\0';	// mark the end of the variable name

                                // Get the parameter type
                                param_type=ConvertParamCharToType(param_type_char);

                                if(param_type!=UNKNOWN_PARAMETER_TYPE)
                                        CreateDefaultParameterNode(query_node,TVI_LAST,param_type,param_name);
                        }

                        start_block_found=FALSE;
                        type_delim_found=FALSE;
                        param_name=NULL;
                        param_type_char=-1;
                }
                else if(start_block_found && param_type_char==-1) {
                        param_type_char=desc_copy[j];
                }
                else if(type_delim_found && param_name==NULL) {
                        param_name=&desc_copy[j];
                }

                j++;
        }

        // Free up the copy memory
        mem_free(desc_copy);
}
*/

///////////////////////////////////
// Functions to Replace Tree Nodes
///////////////////////////////////

// Replaces the currently selected node with a new query
void CDallasMainDlg::ReplaceWithQueryNode(int query_ID) {
  HTREEITEM selected_node, new_query_node;
  tTreeNodeData *data;
  int query_return_type;
  CString query_return_name;

  // Check the ID validity
  if (query_ID < 0 || query_ID >= MAX_QUERIES)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for adding a query
  if (data->type == EXPRESSION_NODE || data->type == PARAMETER_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new query node
    node_data.type = EXPRESSION_NODE;
    node_data.ID = query_ID;

    query_return_type = GetQueryReturnType(query_ID, query_return_name);
    if (query_return_type == ENUM_PARAMETER_TYPE || query_return_type == FLAG_PARAMETER_TYPE)
      strcpy(node_data.name, query_return_name.GetBuffer(0));
    else if (GetNodeType(m_ScriptTree.GetParentItem(selected_node)) == CONDITIONAL_STATEMENT_NODE)
      strcpy(node_data.name, GetLiteralName(query_return_type));
    else
      strcpy(node_data.name, data->name);

    // Add new query node before current node, then delete the current node
    new_query_node = AddNodeToTree(m_ScriptTree.GetParentItem(selected_node), selected_node, &node_data, TRUE);

    // Add in the parameters with appropriate defaults
    AddQueryParameterNodes(new_query_node);

    // Now delete the selected item tree
    m_ScriptTree.SelectItem(new_query_node);
    FreeTreeItem(selected_node);

    // Update the new query node's text to include the parameters
    UpdateAllParentNodesText(new_query_node);

    // If this node is the first of a comparison conditional, make sure third node's type matches
    DoComparisonMatchup(new_query_node);

    if (new_query_node != NULL)
      m_ScriptTree.Expand(new_query_node, TVE_EXPAND);

    SetModified(TRUE);
  }
}

// Replaces the currently selected node with a literal (given a default value)
void CDallasMainDlg::ReplaceWithLiteralNode(int literal_type, int index) {
  HTREEITEM selected_node, new_literal_node;
  tTreeNodeData *data;

  // Check the ID validity
  if (literal_type < 0 || literal_type >= MAX_LITERALS)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for adding a query
  if (data->type == EXPRESSION_NODE || data->type == PARAMETER_NODE) {

    CString tmp_str;
    if (literal_type == ENUM_PARAMETER_TYPE)
      tmp_str = m_EnumDatabase[index].name;
    else if (literal_type == FLAG_PARAMETER_TYPE)
      tmp_str = m_FlagDatabase[index].name;
    else if (GetNodeType(m_ScriptTree.GetParentItem(selected_node)) == CONDITIONAL_STATEMENT_NODE)
      tmp_str = GetLiteralName(literal_type);
    else
      tmp_str = data->name;

    // Create a default parameter node for the chosen literal
    CString name_text, default_text, range_text;
    int n, param_type;
    n = GetChildPosition(selected_node);
    param_type = ParseNthParam(m_ScriptTree.GetParentItem(selected_node), n, name_text, default_text, range_text);
    if (param_type >= 0)
      new_literal_node = CreateDefaultParameterNode(m_ScriptTree.GetParentItem(selected_node), selected_node,
                                                    literal_type, tmp_str.GetBuffer(0), default_text.GetBuffer(0));
    else
      new_literal_node = CreateDefaultParameterNode(m_ScriptTree.GetParentItem(selected_node), selected_node,
                                                    literal_type, tmp_str.GetBuffer(0));

    // Now delete the selected item tree
    m_ScriptTree.SelectItem(new_literal_node);
    FreeTreeItem(selected_node);

    // Update the new literal nodes text
    UpdateAllParentNodesText(new_literal_node);

    // If this node is the first of a comparison conditional, make sure third node's type matches
    DoComparisonMatchup(new_literal_node);

    SetModified(TRUE);
  }
}

// If this node is the first of a comparison conditional, make sure third node's type matches
// If they don't match, remove the third node and replace it with a default param that does match
void CDallasMainDlg::DoComparisonMatchup(HTREEITEM node) {
  int node_type, onode_type;
  CString node_name, onode_name;
  HTREEITEM other_node, new_param_node;

  if (node == NULL)
    return;

  // If it's not the first node of a comparison conditional, nothing need be done
  if (!ParentIsComparisonConditional(node) || GetChildPosition(node) != 1)
    return;

  // ok, it is, so now we need to get the other node being compared
  other_node = GetNthChild(m_ScriptTree.GetParentItem(node), 3);
  if (other_node == NULL)
    return;

  // Get the other node's data
  onode_type = GetParamType(other_node, onode_name);

  // Get this node's data
  node_type = GetParamType(node, node_name);
  if (node_type < 0)
    return;

  // Do the node types match?  If they do, get out of here
  if (node_type == onode_type) {
    if (node_type == ENUM_PARAMETER_TYPE || node_type == FLAG_PARAMETER_TYPE) {
      if (node_name.IsEmpty())
        return;
      else if (strcmp(node_name.GetBuffer(0), onode_name.GetBuffer(0)) == 0)
        return;
    } else
      return;
  }

  // If we're here, then the nodes don't match... so create a matching default param
  CString tmp_str;
  if (node_type == ENUM_PARAMETER_TYPE || node_type == FLAG_PARAMETER_TYPE)
    tmp_str = node_name;
  else
    tmp_str = GetLiteralName(node_type);

  new_param_node =
      CreateDefaultParameterNode(m_ScriptTree.GetParentItem(other_node), other_node, node_type, tmp_str.GetBuffer(0));

  // Now delete the old param node
  FreeTreeItem(other_node);

  // Update the new literal nodes text
  UpdateAllParentNodesText(new_param_node);

  SetModified(TRUE);
}

// Replaces the currently selected node with a new action
void CDallasMainDlg::ReplaceWithActionNode(int action_ID) {
  HTREEITEM selected_node, new_action_node;
  tTreeNodeData *data;

  // Check the ID validity
  if ((action_ID < 0 || action_ID >= MAX_ACTIONS) && action_ID != DO_NOTHING_ID)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for adding an Action
  if (data->type == ACTION_STATEMENT_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new Action node
    node_data.type = ACTION_STATEMENT_NODE;
    node_data.ID = action_ID;

    // Add node appropriately with respect to selected node
    new_action_node = AddNodeToTree(m_ScriptTree.GetParentItem(selected_node), selected_node, &node_data, TRUE);

    // If it's a real Action, add in the parameters with appropriate defaults
    AddActionParameterNodes(new_action_node);

    // Now delete the selected item tree
    m_ScriptTree.SelectItem(new_action_node);
    FreeTreeItem(selected_node);

    // Update the new action node's text to include the parameters
    UpdateNodeText(new_action_node);
    if (new_action_node != NULL)
      m_ScriptTree.Expand(new_action_node, TVE_EXPAND);
    SetModified(TRUE);
  }
}

// Replaces the currently selected node with a new logical operation
void CDallasMainDlg::ReplaceWithLogOpNode(int type) {
  HTREEITEM selected_node, new_logop_node;
  tTreeNodeData *data;

  // Check the ID validity
  if (type < 0 || type >= MAX_LOGICAL_OPERATORS)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // If this node IS a logical operator, just change its data
  if (data->type == LOGICAL_OPERATOR_NODE) {
    data->ID = type;
    UpdateAllParentNodesText(selected_node);
    SetModified(TRUE);
    return;
  }

  // Make sure this node is valid for inserting a logical operator
  if (data->type == LOGICAL_OPERATOR_NODE || data->type == CONDITIONAL_STATEMENT_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new condition node
    node_data.type = LOGICAL_OPERATOR_NODE;
    node_data.ID = type;

    // Add node appropriately with respect to selected node
    new_logop_node = AddNodeToTree(m_ScriptTree.GetParentItem(selected_node), selected_node, &node_data, TRUE);

    // Add a pair of default ALWAYS's so that the logical operator has TWO children
    CreateDefaultConditionalStatementNode(new_logop_node);
    CreateDefaultConditionalStatementNode(new_logop_node);

    // Now delete the selected item tree
    m_ScriptTree.SelectItem(new_logop_node);
    FreeTreeItem(selected_node);

    if (new_logop_node != NULL)
      m_ScriptTree.Expand(new_logop_node, TVE_EXPAND);
    SetModified(TRUE);
  }
}

// Replaces the currently selected node with a new condition
void CDallasMainDlg::ReplaceWithConditionNode(int type, int query_id /*=-1*/) {
  HTREEITEM selected_node, new_condition_node;
  tTreeNodeData *data;

  // Check the ID validity
  if (type < 0 || type >= MAX_CONDITION_TYPES)
    return;

  // Obtain the currently selected node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Get the node's data
  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  // Make sure this node is valid for adding a conditional statement
  if (data->type == LOGICAL_OPERATOR_NODE || data->type == CONDITIONAL_STATEMENT_NODE) {
    tTreeNodeData node_data;

    // Fill in the data appropriately for the new condition node
    node_data.type = CONDITIONAL_STATEMENT_NODE;
    node_data.ID = type;

    // Add node appropriately with respect to selected node
    new_condition_node = AddNodeToTree(m_ScriptTree.GetParentItem(selected_node), selected_node, &node_data, TRUE);

    // Create default subnodes for a binary condition
    CreateDefaultConditionalStatementSubtree(new_condition_node, type, query_id);

    // Now delete the selected item tree
    m_ScriptTree.SelectItem(new_condition_node);
    FreeTreeItem(selected_node);

    // Update the new condition node's text to include the expressions
    UpdateNodeText(new_condition_node);

    if (new_condition_node != NULL)
      m_ScriptTree.Expand(new_condition_node, TVE_EXPAND);
    SetModified(TRUE);
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions to Create (and Add) default Tree Nodes
/////////////////////////////////////////////////////////////////////////////

// Inserts a default script tree before the specified node (or at the end if NULL)
HTREEITEM CDallasMainDlg::CreateDefaultScriptTree(int script_ID, HTREEITEM insert_before /*=NULL*/) {
  HTREEITEM ib_node, parent;
  tTreeNodeData node_data;

  ib_node = GetParentNodeOfType(insert_before, SCRIPT_HEADER_NODE);
  if (ib_node != NULL && m_ScriptTree.GetParentItem(ib_node) != NULL)
    ib_node = m_ClipboardNode;
  if (ib_node == NULL) {
    if (m_ClipboardNode != NULL)
      ib_node = m_ClipboardNode;
    else
      ib_node = TVI_LAST;
  }

  // Create the default Script Header node
  node_data.type = SCRIPT_HEADER_NODE;
  node_data.ID = script_ID;
  strcpy(node_data.name, DEFAULT_SCRIPT_HEADER_STRING);
  parent = AddNodeToTree(TVI_ROOT, ib_node, &node_data);

  // Create the default Script owner node
  node_data.type = SCRIPT_OWNER_NODE;
  node_data.ID = NOT_SPECIFIED_TYPE;
  node_data.int_val = 0;
  AddNodeToTree(parent, TVI_LAST, &node_data);

  // Create the default Event Type Node
  node_data.type = SCRIPT_EVENT_NODE;
  node_data.ID = COLLIDE_EVENT_TYPE;
  AddNodeToTree(parent, TVI_LAST, &node_data);

  CreateDefaultIfThenClause(parent, TVI_LAST, TOP_LEVEL);

  if (parent != NULL)
    m_ScriptTree.Expand(parent, TVE_EXPAND);
  SetModified(TRUE);

  return (parent);
}

// Create default IF-THEN Clause
HTREEITEM CDallasMainDlg::CreateDefaultIfThenClause(HTREEITEM parent, HTREEITEM insert_before, int type) {
  HTREEITEM header;
  tTreeNodeData node_data;

  if (parent == NULL || insert_before == NULL)
    return NULL;

  // Create the default Conditional header Node
  node_data.type = CONDITIONAL_HEADER_NODE;
  node_data.ID = type;
  header = AddNodeToTree(parent, insert_before, &node_data);
  if (header == NULL)
    return (NULL);

  // Create the default conditional statement Node
  CreateDefaultConditionalStatementNode(header);
  if (header != NULL)
    m_ScriptTree.Expand(header, TVE_EXPAND);

  // Create the default Action header Node
  node_data.type = ACTIONS_HEADER_NODE;
  node_data.ID = type;
  if (type == TOP_LEVEL) {
    node_data.subID = 0;
    node_data.int_val = CONTINUE_SCRIPT_CHAIN;
  } else {
    node_data.subID = THEN_CLAUSE;
    node_data.int_val = 0;
  }
  header = AddNodeToTree(parent, insert_before, &node_data);

  // Create the default action statement Node
  CreateDefaultActionStatementNode(header);
  if (header != NULL)
    m_ScriptTree.Expand(header, TVE_EXPAND);
  SetModified(TRUE);

  return (header);
}

// Create default IF-THEN Clause
HTREEITEM CDallasMainDlg::CreateDefaultElseClause(HTREEITEM parent, HTREEITEM insert_before) {
  HTREEITEM header;
  tTreeNodeData node_data;

  if (parent == NULL || insert_before == NULL)
    return NULL;

  // Create the default Action header Node
  node_data.type = ACTIONS_HEADER_NODE;
  node_data.ID = NESTED;
  node_data.subID = ELSE_CLAUSE;
  node_data.int_val = 0;
  header = AddNodeToTree(parent, insert_before, &node_data);

  // Create the default action statement Node
  CreateDefaultActionStatementNode(header);
  if (header != NULL)
    m_ScriptTree.Expand(header, TVE_EXPAND);
  SetModified(TRUE);

  return (header);
}

// Create default conditional statement node
HTREEITEM CDallasMainDlg::CreateDefaultConditionalStatementNode(HTREEITEM parent) {
  tTreeNodeData node_data;

  if (parent == NULL)
    return NULL;

  node_data.type = CONDITIONAL_STATEMENT_NODE;
  node_data.ID = ALWAYS_STATEMENT;
  SetModified(TRUE);

  return (AddNodeToTree(parent, TVI_LAST, &node_data));
}

// Create default conditional statement node
HTREEITEM CDallasMainDlg::CreateDefaultConditionalStatementSubtree(HTREEITEM parent, int type, int query_id /*=-1*/) {
  HTREEITEM last_added_node, first_parm_node;

  if (parent == NULL)
    return NULL;
  if (type == ALWAYS_STATEMENT)
    return NULL;

  // Add default binary subtree
  if (type == BINARY_STATEMENT) {
    first_parm_node = CreateDefaultParameterNode(parent, TVI_LAST, BOOL_PARAMETER_TYPE, "Literal");
    last_added_node = CreateDefaultExpressionOperatorNode(parent, BINARY_OPERATOR_TYPE);
  }

  // Add default comparison subtree
  if (type == COMPARISON_STATEMENT) {
    first_parm_node = CreateDefaultParameterNode(parent, TVI_LAST, FLOAT_PARAMETER_TYPE, "Literal");
    last_added_node = CreateDefaultExpressionOperatorNode(parent, COMPARISON_OPERATOR_TYPE);
    last_added_node = CreateDefaultParameterNode(parent, TVI_LAST, FLOAT_PARAMETER_TYPE, "Literal");
  }

  // Replace first node with a query if necessary
  if (first_parm_node != NULL && query_id >= 0 && query_id < MAX_QUERIES) {

    // Get the node's data
    tTreeNodeData *data = (tTreeNodeData *)m_ScriptTree.GetItemData(first_parm_node);

    // Make sure this node is valid for adding a query
    if (data != NULL && (data->type == EXPRESSION_NODE || data->type == PARAMETER_NODE)) {
      tTreeNodeData node_data;
      int query_return_type;
      HTREEITEM new_query_node;
      CString query_return_name;

      // Fill in the data appropriately for the new query node
      node_data.type = EXPRESSION_NODE;
      node_data.ID = query_id;

      query_return_type = GetQueryReturnType(query_id, query_return_name);
      if (query_return_type == ENUM_PARAMETER_TYPE || query_return_type == FLAG_PARAMETER_TYPE)
        strcpy(node_data.name, query_return_name.GetBuffer(0));
      else if (GetNodeType(m_ScriptTree.GetParentItem(first_parm_node)) == CONDITIONAL_STATEMENT_NODE)
        strcpy(node_data.name, GetLiteralName(query_return_type));
      else
        strcpy(node_data.name, data->name);

      // Add new query node before current node, then delete the current node
      new_query_node = AddNodeToTree(m_ScriptTree.GetParentItem(first_parm_node), first_parm_node, &node_data, TRUE);

      // Add in the parameters with appropriate defaults
      AddQueryParameterNodes(new_query_node);

      // Now delete the selected item tree
      FreeTreeItem(first_parm_node);

      // Update the new query node's text to include the parameters
      UpdateAllParentNodesText(new_query_node);

      // If this node is the first of a comparison conditional, make sure third node's type matches
      DoComparisonMatchup(new_query_node);

      if (new_query_node != NULL)
        m_ScriptTree.Expand(new_query_node, TVE_EXPAND);
    }
  }

  SetModified(TRUE);

  return (last_added_node);
}

// Create default expression operator node
HTREEITEM CDallasMainDlg::CreateDefaultExpressionOperatorNode(HTREEITEM parent, int type) {
  tTreeNodeData node_data;

  if (parent == NULL)
    return NULL;
  if (type != BINARY_OPERATOR_TYPE && type != COMPARISON_OPERATOR_TYPE)
    return NULL;

  node_data.type = EXPRESSION_OPERATOR_NODE;
  node_data.ID = type;

  if (type == BINARY_OPERATOR_TYPE)
    node_data.subID = IS_TRUE;
  else
    node_data.subID = EQUAL_TO;

  SetModified(TRUE);

  return (AddNodeToTree(parent, TVI_LAST, &node_data));
}

// Create default action statement node
HTREEITEM CDallasMainDlg::CreateDefaultActionStatementNode(HTREEITEM parent) {
  tTreeNodeData node_data;

  if (parent == NULL)
    return NULL;

  node_data.type = ACTION_STATEMENT_NODE;
  node_data.ID = DO_NOTHING_ID;

  SetModified(TRUE);

  return (AddNodeToTree(parent, TVI_LAST, &node_data));
}

// Create default parameter node, and assigns it an appropriate default value
// based upon the parameter type
HTREEITEM CDallasMainDlg::CreateDefaultParameterNode(HTREEITEM parent, HTREEITEM insert_before, int param_type,
                                                     char *name, char *def_value /*=NULL*/) {
  tTreeNodeData node_data;

  if (parent == NULL || insert_before == NULL || name == NULL)
    return NULL;

  node_data.type = PARAMETER_NODE;
  node_data.ID = param_type;
  strcpy(node_data.name, name);

  // Store default values
  switch (param_type) {
  case DOOR_PARAMETER_TYPE:
    node_data.int_val = OBJECT_HANDLE_NONE;
    node_data.subID = USE_OBJECT_HANDLE;
    strcpy(node_data.str_val, "");
    break;
  case OBJECT_PARAMETER_TYPE:
    if (def_value != NULL && strlen(def_value) != 0) {
      if (strcmp(def_value, "ME") == 0) {
        node_data.int_val = OBJECT_HANDLE_NONE;
        node_data.subID = USE_ME_HANDLE;
        strcpy(node_data.str_val, "");
        break;
      }
      if (strcmp(def_value, "IT") == 0) {
        node_data.int_val = OBJECT_HANDLE_NONE;
        node_data.subID = USE_IT_HANDLE;
        strcpy(node_data.str_val, "");
        break;
      }
    }
    node_data.int_val = OBJECT_HANDLE_NONE;
    node_data.subID = USE_OBJECT_HANDLE;
    strcpy(node_data.str_val, "");
    break;
  case ROOM_PARAMETER_TYPE:
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case TRIGGER_PARAMETER_TYPE:
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case INT_PARAMETER_TYPE:
    if (def_value == NULL || strlen(def_value) == 0)
      node_data.int_val = 0;
    else
      node_data.int_val = atoi(def_value);
    break;
  case BOOL_PARAMETER_TYPE:
    if (def_value == NULL || strlen(def_value) == 0)
      node_data.int_val = TRUE;
    else {
      if (stricmp(def_value, "false") == 0)
        node_data.int_val = FALSE;
      else
        node_data.int_val = TRUE;
    }
    break;
  case FLOAT_PARAMETER_TYPE:
    if (def_value == NULL || strlen(def_value) == 0)
      node_data.float_val1 = 0.0;
    else
      node_data.float_val1 = atof(def_value);
    break;
  case VECTOR_PARAMETER_TYPE:
    node_data.float_val1 = 0.0;
    node_data.float_val2 = 0.0;
    node_data.float_val3 = 0.0;
    break;
  case STRING_PARAMETER_TYPE:
    strcpy(node_data.str_val, "");
    break;
  case PERCENTAGE_PARAMETER_TYPE:
    if (def_value == NULL || strlen(def_value) == 0)
      node_data.float_val1 = 0.0;
    else
      node_data.float_val1 = atof(def_value);
    break;
  case ENUM_PARAMETER_TYPE: {
    if (def_value != NULL && strlen(def_value) > 0) {
      if (GetEnumValue(name, def_value, node_data.int_val)) {
        node_data.subID = USE_ENUM_VALUE;
        break;
      }
    }

    int DBslot;
    DBslot = GetEnumID(name);
    node_data.subID = USE_ENUM_VALUE;
    if (DBslot != INVALID_ENUM && m_EnumDatabase[DBslot].num_values > 0)
      node_data.int_val = m_EnumDatabase[DBslot].values[0].value;
    else
      node_data.int_val = 0;
  } break;
  case SCRIPT_PARAMETER_TYPE:
    node_data.int_val = GetScriptID(parent);
    if (node_data.int_val < 0)
      node_data.int_val = 0;
    break;
  case SOUND_PARAMETER_TYPE:
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case SPECNAME_PARAMETER_TYPE:
    strcpy(node_data.str_val, "");
    break;
  case TEXTURE_PARAMETER_TYPE:
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case FLAG_PARAMETER_TYPE:
    if (def_value == NULL || strlen(def_value) == 0)
      node_data.int_val = 0;
    else
      node_data.int_val = atoi(def_value);
    break;
  case PATH_PARAMETER_TYPE:
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case MATCEN_PARAMETER_TYPE:
    node_data.subID = USE_MATCEN_VALUE;
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case LEVEL_GOAL_PARAMETER_TYPE:
    node_data.subID = USE_LEVEL_GOAL_VALUE;
    node_data.int_val = NOT_SPECIFIED_TYPE;
    strcpy(node_data.str_val, "");
    break;
  case STRM_AUDIO_PARAMETER_TYPE:
    strcpy(node_data.str_val, "");
    break;
  default:
    break;
  }

  SetModified(TRUE);

  return (AddNodeToTree(parent, insert_before, &node_data));
}

// Creates the clipboard node and puts it into the tree
HTREEITEM CDallasMainDlg::CreateDefaultClipboardNode(void) {
  tTreeNodeData node_data;

  if (m_ClipboardNode != NULL) {
    FreeTreeItem(m_ClipboardNode);
    m_ClipboardNode = NULL;
  }

  node_data.type = CLIPBOARD_HEADER_NODE;
  SetModified(TRUE);

  m_ClipboardNode = AddNodeToTree(TVI_ROOT, TVI_LAST, &node_data);
  return (m_ClipboardNode);
}

///////////////////////////////////
// Functions to Handle Copy/Paste
///////////////////////////////////

// Copies the selected script into the clipboard
void CDallasMainDlg::PerformScriptCopy(void) {
  HTREEITEM selected_node;
  HTREEITEM script_header_node;
  HTREEITEM new_script_node;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // Get the selected tree node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // If it's a conditional statement node, let it be the header
  if (GetNodeType(selected_node) == CONDITIONAL_STATEMENT_NODE) {
    PerformConditionalCopy(selected_node);
    return;
  }

  // If it's a logical operator node, let it be the header
  if (GetNodeType(selected_node) == LOGICAL_OPERATOR_NODE) {
    PerformLogOpCopy(selected_node);
    return;
  }

  // If it's an action node, let it be the header
  if (GetNodeType(selected_node) == ACTION_STATEMENT_NODE) {
    PerformActionCopy(selected_node);
    return;
  }

  // If it's a nested IF clause, let it be the header
  if (NodeIsIfClause(selected_node)) {
    PerformClauseCopy(selected_node);
    return;
  }

  // If it's not a script header node, then it can't be copied
  if (GetNodeType(selected_node) != SCRIPT_HEADER_NODE) {
    MessageBox("Copy/Paste is not supported for the currently selected script item.", "Invalid Copy/Paste", MB_OK);
    return;
  }

  // Get the script header node
  script_header_node = GetParentNodeOfType(selected_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  // If the script header has a parent, then it must be a clipboard node
  if (m_ScriptTree.GetParentItem(script_header_node) != NULL)
    return;

  // If the clipboard, has a script already, kill the old one
  FreeTreeItemChildren(m_ClipboardNode);

  // Now copy the script over to the clipboard
  new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, script_header_node);
  if (new_script_node != NULL) {
    UpdateAllParentNodesText(new_script_node);
    m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
  }
}

// Copies the selected script action into the clipboard
void CDallasMainDlg::PerformActionCopy(HTREEITEM action_node) {
  HTREEITEM script_header_node;
  HTREEITEM new_script_node;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // Get the selected tree node
  if (action_node == NULL)
    return;

  // If it's an action node, let it be the header
  if (GetNodeType(action_node) != ACTION_STATEMENT_NODE)
    return;

  // Get the script header node
  script_header_node = GetParentNodeOfType(action_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  // If the script header has a parent, then it must be a clipboard node
  if (m_ScriptTree.GetParentItem(script_header_node) != NULL)
    return;

  // If the clipboard, has a script already, kill the old one
  FreeTreeItemChildren(m_ClipboardNode);

  // Now copy the action over to the clipboard
  new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, action_node);
  if (new_script_node != NULL) {
    UpdateAllParentNodesText(new_script_node);
    m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
  }
}

// Copies the selected script conditional statement into the clipboard
void CDallasMainDlg::PerformConditionalCopy(HTREEITEM conditional_node) {
  HTREEITEM script_header_node;
  HTREEITEM new_script_node;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // Get the selected tree node
  if (conditional_node == NULL)
    return;

  // If it's an action node, let it be the header
  if (GetNodeType(conditional_node) != CONDITIONAL_STATEMENT_NODE)
    return;

  // Get the script header node
  script_header_node = GetParentNodeOfType(conditional_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  // If the script header has a parent, then it must be a clipboard node
  if (m_ScriptTree.GetParentItem(script_header_node) != NULL)
    return;

  // If the clipboard, has a script already, kill the old one
  FreeTreeItemChildren(m_ClipboardNode);

  // Now copy the conditional statement over to the clipboard
  new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, conditional_node);
  if (new_script_node != NULL) {
    UpdateAllParentNodesText(new_script_node);
    m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
  }
}

// Copies the selected script logical operator into the clipboard
void CDallasMainDlg::PerformLogOpCopy(HTREEITEM logop_node) {
  HTREEITEM script_header_node;
  HTREEITEM new_script_node;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // Get the selected tree node
  if (logop_node == NULL)
    return;

  // If it's a logop node, let it be the header
  if (GetNodeType(logop_node) != LOGICAL_OPERATOR_NODE)
    return;

  // Get the script header node
  script_header_node = GetParentNodeOfType(logop_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  // If the script header has a parent, then it must be a clipboard node
  if (m_ScriptTree.GetParentItem(script_header_node) != NULL)
    return;

  // If the clipboard, has a script already, kill the old one
  FreeTreeItemChildren(m_ClipboardNode);

  // Now copy the logical operator over to the clipboard
  new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, logop_node);
  if (new_script_node != NULL) {
    UpdateAllParentNodesText(new_script_node);
    m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
  }
}

// Copies the selected script if-then-else clause into the clipboard
void CDallasMainDlg::PerformClauseCopy(HTREEITEM clause_node) {
  HTREEITEM script_header_node;
  HTREEITEM new_script_node;
  HTREEITEM if_node, then_node, else_node;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // Get the selected tree node
  if (clause_node == NULL)
    return;

  // Make sure it's an IF header
  if (!NodeIsIfClause(clause_node))
    return;

  // Get the script header node
  script_header_node = GetParentNodeOfType(clause_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  // If the script header has a parent, then it must be a clipboard node
  if (m_ScriptTree.GetParentItem(script_header_node) != NULL)
    return;

  // Get the then clause node
  if_node = clause_node;
  then_node = m_ScriptTree.GetNextSiblingItem(if_node);
  if (!NodeIsClauseOfType(then_node, THEN_CLAUSE))
    return;

  // Get the else clause node
  else_node = m_ScriptTree.GetNextSiblingItem(then_node);
  if (!NodeIsClauseOfType(else_node, ELSE_CLAUSE))
    else_node = NULL;

  // If the clipboard, has a script already, kill the old one
  FreeTreeItemChildren(m_ClipboardNode);

  // Now copy the IF clause over to the clipboard
  new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, if_node);
  if (new_script_node != NULL) {
    UpdateAllParentNodesText(new_script_node);
    m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
  }

  // Now copy the THEN clause over to the clipboard
  new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, then_node);
  if (new_script_node != NULL) {
    UpdateAllParentNodesText(new_script_node);
    m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
  }

  // Now copy the ELSE clause over (if one exists)
  if (else_node != NULL) {
    new_script_node = CopyTree(m_ClipboardNode, TVI_LAST, else_node);
    if (new_script_node != NULL) {
      UpdateAllParentNodesText(new_script_node);
      m_ScriptTree.Expand(m_ClipboardNode, TVE_COLLAPSE);
    }
  }
}

// Inserts the clipboard script before the selected script (or clipboard)
void CDallasMainDlg::PerformScriptPaste(void) {
  HTREEITEM selected_node;
  HTREEITEM src_script_header_node;
  HTREEITEM dest_insert_before;
  HTREEITEM new_script_header;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // Get the clipboard child script
  src_script_header_node = m_ScriptTree.GetChildItem(m_ClipboardNode);
  if (src_script_header_node == NULL)
    return;

  // See if the clipboard has a conditional statement
  if (GetNodeType(src_script_header_node) == CONDITIONAL_STATEMENT_NODE) {
    PerformConditionalPaste(src_script_header_node);
    return;
  }

  // See if the clipboard has a logical operator
  if (GetNodeType(src_script_header_node) == LOGICAL_OPERATOR_NODE) {
    PerformLogOpPaste(src_script_header_node);
    return;
  }

  // See if the clipboard has an action
  if (GetNodeType(src_script_header_node) == ACTION_STATEMENT_NODE) {
    PerformActionPaste(src_script_header_node);
    return;
  }

  // See if the clipboard has an IF clause
  if (NodeIsIfClause(src_script_header_node)) {
    PerformClausePaste(src_script_header_node);
    return;
  }

  // If the clipboard doesn't have a script header, get outta here
  if (GetNodeType(src_script_header_node) != SCRIPT_HEADER_NODE)
    return;

  // Get the selected tree node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  if (selected_node == m_ClipboardNode)
    dest_insert_before = m_ClipboardNode;
  else {
    dest_insert_before = GetParentNodeOfType(selected_node, SCRIPT_HEADER_NODE);
    if (dest_insert_before == NULL)
      return;

    // If the script header has a parent, then it must be a clipboard node
    if (m_ScriptTree.GetParentItem(dest_insert_before) != NULL)
      dest_insert_before = m_ClipboardNode;
  }

  // Now copy the script over to the clipboard
  new_script_header = CopyTree(TVI_ROOT, dest_insert_before, src_script_header_node);
  if (new_script_header == NULL)
    return;

  // Change the script ID for the new node
  tTreeNodeData *data = (tTreeNodeData *)m_ScriptTree.GetItemData(new_script_header);
  if (data == NULL)
    return;

  int new_id = GetLowestUnusedScriptID();
  data->ID = new_id;
  UpdateNodeText(new_script_header);
  HighlightScript(new_script_header);

  if (new_id == m_NextScriptID)
    m_NextScriptID++;

  m_ScriptTree.SelectItem(new_script_header);
  AssignSpecificValue();
  SetModified(TRUE);
}

// Inserts the clipboard action before the selected node (or to end of children)
void CDallasMainDlg::PerformActionPaste(HTREEITEM src_action_node) {
  HTREEITEM selected_node;
  HTREEITEM new_action_node;
  tTreeNodeData *data;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // See if the clipboard has an action
  if (GetNodeType(src_action_node) != ACTION_STATEMENT_NODE)
    return;

  // Get the selected tree node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Make sure it's not the same node!
  if (selected_node == src_action_node)
    return;

  // Make sure it's not in the clipboard
  if (NodeIsInClipboard(selected_node))
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  if (data->type == ACTION_STATEMENT_NODE || (data->type == CONDITIONAL_HEADER_NODE && data->ID == NESTED))
    new_action_node = CopyTree(m_ScriptTree.GetParentItem(selected_node), selected_node, src_action_node);
  else if (data->type == ACTIONS_HEADER_NODE) {
    new_action_node = CopyTree(selected_node, TVI_LAST, src_action_node);
  } else {
    return;
  }

  // Now copy the script over to the clipboard
  if (new_action_node == NULL)
    return;

  UpdateAllParentNodesText(new_action_node);
  SetModified(TRUE);
}

// Replaces selected node with the clipboard conditional statement
void CDallasMainDlg::PerformConditionalPaste(HTREEITEM src_conditional_node) {
  HTREEITEM selected_node;
  HTREEITEM new_conditional_node;
  HTREEITEM parent;
  tTreeNodeData *data;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // See if the clipboard has a conditional statement
  if (GetNodeType(src_conditional_node) != CONDITIONAL_STATEMENT_NODE)
    return;

  // Get the selected tree node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Make sure it's not the same node!
  if (selected_node == src_conditional_node)
    return;

  // Make sure it's not in the clipboard
  if (NodeIsInClipboard(selected_node))
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  if (data->type == CONDITIONAL_STATEMENT_NODE || data->type == LOGICAL_OPERATOR_NODE) {
    new_conditional_node = CopyTree(m_ScriptTree.GetParentItem(selected_node), selected_node, src_conditional_node);
    m_ScriptTree.SelectItem(new_conditional_node);

    // Delete the old conditional
    parent = m_ScriptTree.GetParentItem(selected_node);
    FreeTreeItem(selected_node);

    ConfirmAfterDelete(parent);
    SetModified(TRUE);
  } else {
    return;
  }

  // Now copy the script over to the clipboard
  if (new_conditional_node == NULL)
    return;

  UpdateAllParentNodesText(new_conditional_node);
}

// Replaces selected node with the clipboard logical operator node
void CDallasMainDlg::PerformLogOpPaste(HTREEITEM src_logop_node) {
  HTREEITEM selected_node;
  HTREEITEM new_logop_node;
  HTREEITEM parent;
  tTreeNodeData *data;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // See if the clipboard has a logical operator
  if (GetNodeType(src_logop_node) != LOGICAL_OPERATOR_NODE)
    return;

  // Get the selected tree node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Make sure it's not the same node!
  if (selected_node == src_logop_node)
    return;

  // Make sure it's not in the clipboard
  if (NodeIsInClipboard(selected_node))
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  if (data->type == CONDITIONAL_STATEMENT_NODE || data->type == LOGICAL_OPERATOR_NODE) {
    new_logop_node = CopyTree(m_ScriptTree.GetParentItem(selected_node), selected_node, src_logop_node);
    m_ScriptTree.SelectItem(new_logop_node);

    // Delete the old conditional
    parent = m_ScriptTree.GetParentItem(selected_node);
    FreeTreeItem(selected_node);

    ConfirmAfterDelete(parent);
    SetModified(TRUE);
  } else {
    return;
  }

  // Now copy the script over to the clipboard
  if (new_logop_node == NULL)
    return;

  UpdateAllParentNodesText(new_logop_node);
}

// Inserts the clipboard action before the selected node (or to end of children)
void CDallasMainDlg::PerformClausePaste(HTREEITEM src_clause_node) {
  HTREEITEM selected_node;
  HTREEITEM new_clause_node;
  HTREEITEM if_node, then_node, else_node;
  tTreeNodeData *data;

  // Make sure we have a clipboard
  if (m_ClipboardNode == NULL)
    return;

  // See if the clipboard has an IF clause
  if (!NodeIsIfClause(src_clause_node))
    return;

  // Get the then clause node
  if_node = src_clause_node;
  then_node = m_ScriptTree.GetNextSiblingItem(if_node);
  if (!NodeIsClauseOfType(then_node, THEN_CLAUSE))
    return;

  // Get the else clause node
  else_node = m_ScriptTree.GetNextSiblingItem(then_node);
  if (!NodeIsClauseOfType(else_node, ELSE_CLAUSE))
    else_node = NULL;

  // Get the selected tree node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;

  // Make sure it's not the same node!
  if (selected_node == src_clause_node)
    return;

  // Make sure it's not in the clipboard
  if (NodeIsInClipboard(selected_node))
    return;

  data = (tTreeNodeData *)m_ScriptTree.GetItemData(selected_node);
  if (data == NULL)
    return;

  if (data->type == ACTION_STATEMENT_NODE || (data->type == CONDITIONAL_HEADER_NODE && data->ID == NESTED)) {
    // Copy over IF clause
    new_clause_node = CopyTree(m_ScriptTree.GetParentItem(selected_node), selected_node, if_node);
    UpdateAllParentNodesText(new_clause_node);

    // Copy over THEN clause
    new_clause_node = CopyTree(m_ScriptTree.GetParentItem(selected_node), selected_node, then_node);
    UpdateAllParentNodesText(new_clause_node);

    // Copy over ELSE clause (if one exists)
    if (else_node != NULL) {
      new_clause_node = CopyTree(m_ScriptTree.GetParentItem(selected_node), selected_node, else_node);
      UpdateAllParentNodesText(new_clause_node);
    }
  } else if (data->type == ACTIONS_HEADER_NODE) {
    // Copy over IF clause
    new_clause_node = CopyTree(selected_node, TVI_LAST, if_node);
    UpdateAllParentNodesText(new_clause_node);

    // Copy over THEN clause
    new_clause_node = CopyTree(selected_node, TVI_LAST, then_node);
    UpdateAllParentNodesText(new_clause_node);

    // Copy over ELSE clause (if one exists)
    if (else_node != NULL) {
      new_clause_node = CopyTree(selected_node, TVI_LAST, else_node);
      UpdateAllParentNodesText(new_clause_node);
    }
  } else {
    return;
  }

  // Now copy the script over to the clipboard
  if (new_clause_node == NULL)
    return;

  SetModified(TRUE);
}

// Checks to see if the given node is a child of the clipboard header
bool CDallasMainDlg::NodeIsInClipboard(HTREEITEM node) {
  HTREEITEM parent;

  parent = GetParentNodeOfType(node, CLIPBOARD_HEADER_NODE);

  if (parent == NULL)
    return FALSE;
  else
    return TRUE;
}

///////////////////////////////////////////////
// Functions to search tree and replace values
///////////////////////////////////////////////

// Goes through the tree, and changes old messageID's to the new one
int CDallasMainDlg::UpdateStringParams(HTREEITEM root, char *old_name, char *new_name) {
  HTREEITEM child;
  tTreeNodeData *data;
  int num_changed;

  if (root == NULL)
    return 0;

  // Process the children
  num_changed = 0;
  child = m_ScriptTree.GetChildItem(root);
  while (child != NULL) {
    num_changed += UpdateStringParams(child, old_name, new_name);

    // Check this child to see if it's a string parameter in need of updating
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(child);
    if (data != NULL && data->type == PARAMETER_NODE && data->ID == STRING_PARAMETER_TYPE) {
      if (strcmp(data->str_val, old_name) == 0) {
        strcpy(data->str_val, new_name);
        UpdateAllParentNodesText(child);
        num_changed++;
      }
    }

    // Get the next child
    child = m_ScriptTree.GetNextSiblingItem(child);
  }

  if (num_changed > 0)
    SetModified(TRUE);

  return (num_changed);
}

///////////////////////////////////////////////////////////////////
// Functions to Handle Script Drag-n-Drop
///////////////////////////////////////////////////////////////////

bool CDallasMainDlg::IsDropSource(HTREEITEM item) {
  if (item == NULL)
    return FALSE;

  // See if it's an action node
  if (GetNodeType(item) == ACTION_STATEMENT_NODE) {
    HTREEITEM parent;

    // Make sure it's not in the clipboard
    parent = GetParentNodeOfType(item, SCRIPT_HEADER_NODE);
    if (parent == NULL)
      return FALSE;

    if (m_ScriptTree.GetParentItem(parent) != NULL)
      return FALSE;

    return TRUE;
  }

  // Make sure it's a script header node
  if (GetNodeType(item) != SCRIPT_HEADER_NODE)
    return FALSE;

  // Make sure it's not in the Clipboard
  if (m_ScriptTree.GetParentItem(item) != NULL)
    return FALSE;

  return TRUE;
}

HTREEITEM CDallasMainDlg::GetDropTarget(HTREEITEM item) {
  HTREEITEM target_item, parent_item;

  if (item == NULL || m_hitemDrag == NULL)
    return NULL;

  // See if the dragged node is an action
  if (GetNodeType(m_hitemDrag) == ACTION_STATEMENT_NODE) {
    tTreeNodeData *data;
    HTREEITEM parent;

    // Make sure it's not in the clipboard
    parent = GetParentNodeOfType(item, SCRIPT_HEADER_NODE);
    if (parent == NULL)
      return NULL;

    if (m_ScriptTree.GetParentItem(parent) != NULL)
      return NULL;

    // Make sure it's a valid drop node
    data = (tTreeNodeData *)m_ScriptTree.GetItemData(item);
    if (data == NULL)
      return NULL;

    if (data->type == ACTION_STATEMENT_NODE || (data->type == CONDITIONAL_HEADER_NODE && data->ID == NESTED))
      return (item);

    if (data->type == ACTIONS_HEADER_NODE)
      return (item);

    return NULL;
  }

  // See if it's the clipboard
  if (GetNodeType(item) == CLIPBOARD_HEADER_NODE)
    return (item);

  // Get the script header for the selected node
  target_item = GetParentNodeOfType(item, SCRIPT_HEADER_NODE);
  if (target_item == NULL)
    return NULL;

  parent_item = m_ScriptTree.GetParentItem(target_item);
  if (m_ScriptTree.GetParentItem(target_item) == NULL)
    return (target_item);

  if (GetNodeType(parent_item) == CLIPBOARD_HEADER_NODE)
    return (parent_item);

  return NULL;
}

void CDallasMainDlg::OnBegindragEventTree(NMHDR *pNMHDR, LRESULT *pResult) {
  NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;

  m_hitemDrag = pNMTreeView->itemNew.hItem;
  m_hitemDrop = NULL;
  m_ScriptTree.SelectItem(m_hitemDrag);

  if (!IsDropSource(m_hitemDrag))
    return;

  // get the image list for dragging
  m_pDragImage = m_ScriptTree.CreateDragImage(m_hitemDrag);

  // CreateDragImage() returns NULL if no image list
  // associated with the tree view control
  if (!m_pDragImage)
    return;

  m_bLDragging = TRUE;
  m_pDragImage->BeginDrag(0, CPoint(0, 0));
  POINT pt = pNMTreeView->ptDrag;
  m_ScriptTree.ClientToScreen(&pt);
  m_pDragImage->DragEnter(NULL, pt);
  SetCapture();

  *pResult = 0;
}

void CDallasMainDlg::OnMouseMove(UINT nFlags, CPoint point) {
  HTREEITEM hitem;
  UINT flags;

  if (m_bLDragging) {
    POINT pt = point;
    ClientToScreen(&pt);
    POINT tree_pt = pt;
    m_ScriptTree.ScreenToClient(&tree_pt);
    CImageList::DragMove(pt);
    if ((hitem = m_ScriptTree.HitTest(tree_pt, &flags)) != NULL) {
      CImageList::DragShowNolock(FALSE);
      m_hitemDrop = GetDropTarget(hitem);
      m_ScriptTree.SelectDropTarget(m_hitemDrop);
      CImageList::DragShowNolock(TRUE);
    } else {
      CImageList::DragShowNolock(FALSE);
      m_hitemDrop = NULL;
      m_ScriptTree.SelectDropTarget(m_hitemDrop);
      CImageList::DragShowNolock(TRUE);
    }
  }

  CDialog::OnMouseMove(nFlags, point);
}

void CDallasMainDlg::OnLButtonUp(UINT nFlags, CPoint point) {
  if (m_bLDragging) {
    m_bLDragging = FALSE;
    CImageList::DragLeave(this);
    CImageList::EndDrag();
    ReleaseCapture();
    delete m_pDragImage;

    // Remove drop target highlighting
    m_ScriptTree.SelectDropTarget(NULL);

    if ((m_hitemDrag == m_hitemDrop) || m_hitemDrop == NULL)
      return;

    // See if the dragged node is an action
    if (GetNodeType(m_hitemDrag) == ACTION_STATEMENT_NODE) {
      HTREEITEM new_action_node, parent;
      tTreeNodeData *data;

      data = (tTreeNodeData *)m_ScriptTree.GetItemData(m_hitemDrop);
      if (data == NULL)
        return;

      if (data->type == ACTION_STATEMENT_NODE || (data->type == CONDITIONAL_HEADER_NODE && data->ID == NESTED))
        new_action_node = CopyTree(m_ScriptTree.GetParentItem(m_hitemDrop), m_hitemDrop, m_hitemDrag);
      else if (data->type == ACTIONS_HEADER_NODE) {
        new_action_node = CopyTree(m_hitemDrop, TVI_LAST, m_hitemDrag);
      }

      if (new_action_node == NULL)
        return;
      UpdateAllParentNodesText(new_action_node);
      m_ScriptTree.SelectItem(new_action_node);

      // Delete the old action
      parent = m_ScriptTree.GetParentItem(m_hitemDrag);
      FreeTreeItem(m_hitemDrag);

      ConfirmAfterDelete(parent);
      SetModified(TRUE);

      return;
    }

    // Copy the tree to its new location (and select it)
    HTREEITEM new_script_header = CopyTree(TVI_ROOT, m_hitemDrop, m_hitemDrag);
    if (new_script_header == NULL)
      return;
    UpdateAllParentNodesText(new_script_header);
    m_ScriptTree.SelectItem(new_script_header);

    // Delete the old tree
    FreeTreeItem(m_hitemDrag);
    SetModified(TRUE);
  }

  CDialog::OnLButtonUp(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// Functions to Handle Highlight Interface
///////////////////////////////////////////////////////////////////

void CDallasMainDlg::ClearHighlightRadioButtons(void) {
  ((CButton *)GetDlgItem(IDC_NONE_RADIO))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_SPECIFIC_RADIO))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_LEVEL_RADIO))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_ALLOBJ_RADIO))->SetCheck(0);
  ((CButton *)GetDlgItem(IDC_ALLTRIG_RADIO))->SetCheck(0);
}

void CDallasMainDlg::FillHighlightEventList(void) {
  int i, index;

  m_EventList.ResetContent();

  // Add the "all events" type
  index = m_EventList.AddString("All Event Types");
  if (index != LB_ERR) {
    m_EventList.SetItemData(index, ALL_EVENT_TYPES);
  }

  // Fill the list with the event types
  for (i = 0; event_info[i].type >= 0; i++) {
    index = m_EventList.AddString(event_info[i].name);
    if (index != LB_ERR) {
      m_EventList.SetItemData(index, event_info[i].type);
    }
  }

  SetHighlightedEvent(ALL_EVENT_TYPES);
}

int CDallasMainDlg::GetHighlightedEvent(void) {
  int index = m_EventList.GetCurSel();
  if (index == LB_ERR)
    return ALL_EVENT_TYPES;

  return (m_EventList.GetItemData(index));
}

void CDallasMainDlg::SetHighlightedEvent(int type) {
  int index, total;

  total = m_EventList.GetCount();
  for (index = 0; index < total; index++) {
    int data = m_EventList.GetItemData(index);
    if (data == type) {
      m_EventList.SetCurSel(index);
      break;
    }
  }
}

void CDallasMainDlg::OnAllobjRadio() {
  m_ScriptOwnerType = ALL_OBJECTS_TYPE;
  m_ScriptOwnerHandle = 0;
  // SetHighlightedEvent(ALL_EVENT_TYPES);

  HighlightAllScripts();
}

void CDallasMainDlg::OnAlltrigRadio() {
  m_ScriptOwnerType = ALL_TRIGGERS_TYPE;
  m_ScriptOwnerHandle = 0;

  HighlightAllScripts();
}

void CDallasMainDlg::OnNoneRadio() {
  m_ScriptOwnerType = NONE_TYPE;
  m_ScriptOwnerHandle = 0;

  HighlightAllScripts();
}

void CDallasMainDlg::OnSpecificRadio() { OnHighlightButton(); }

void CDallasMainDlg::OnLevelRadio() {
  m_ScriptOwnerType = LEVEL_TYPE;
  m_ScriptOwnerHandle = 0;

  HighlightAllScripts();
}

void CDallasMainDlg::OnEventRadio() {
  m_ScriptOwnerType = ALL_OWNERS_TYPE;
  m_ScriptOwnerHandle = 0;

  HighlightAllScripts();
}

void CDallasMainDlg::OnSelchangeEventCombo() { HighlightAllScripts(); }

///////////////////////////////////////////////////////////////////
// Functions to Handle Import/Export
///////////////////////////////////////////////////////////////////

// Display a script library file selection dialog
bool CDallasMainDlg::ScriptLibraryFilePrompt(CString &filename, bool use_import_msg) {
  static CString last_path = "";
  CString filter;
  char *default_fname;
  CString title;
  bool dlg_type;

  if (use_import_msg) {
    title = "Import Script from what Library File?";
    dlg_type = TRUE;
  } else {
    title = "Export Script to what Library File?";
    dlg_type = FALSE;
  }

  if (last_path.IsEmpty())
    default_fname = NULL;
  else
    default_fname = last_path.GetBuffer(0);

  filename = "";
  filter = "Dallas Script Library Files (*.dsl)|*.dsl|All Files (*.*)|*.*||";
  CFileDialog dlg_open(dlg_type, NULL, default_fname, OFN_FILEMUSTEXIST, (LPCTSTR)filter, this);
  dlg_open.m_ofn.lpstrTitle = title.GetBuffer(0);
  if (dlg_open.DoModal() == IDCANCEL) {
    return FALSE;
  }

  filename = dlg_open.GetPathName();
  if (filename.Find('.') < 0)
    filename += ".dsl";
  last_path = filename;

  return TRUE;
}

// Scans given .dsl file for given name, and imports it
bool CDallasMainDlg::ImportScriptFromFile(char *filename, char *script_name) {
  CFILE *infile;
  char linebuf[2048];
  char tempbuf[256];
  char *line;
  int linenum;
  int valid_lines_read, version;
  int rc;

  HTREEITEM last_node_added, current_parent, insert_before, returned_node;
  HTREEITEM selected_node, initial_insert_before, new_script_header;
  bool skip_children;
  int skip_depth;
  bool last_node_childless;
  bool ScriptToImportFound;

  // Determine the initial insert before script header node
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return FALSE;
  if (GetNodeType(selected_node) == CLIPBOARD_HEADER_NODE)
    initial_insert_before = selected_node;
  else {
    initial_insert_before = GetParentNodeOfType(selected_node, SCRIPT_HEADER_NODE);
    if (initial_insert_before == NULL)
      return FALSE;
    if (m_ScriptTree.GetParentItem(initial_insert_before) != NULL)
      return FALSE;
  }

  CurrentParsingFilename = filename;
  new_script_header = NULL;

  // Try to open the file for loading
  infile = cfopen(filename, "rt");
  if (!infile) {
    CString msg;
    msg.Format("Unable to open \"%s\"!", filename);
    MessageBox(msg, "Script Library File Not Found!", MB_OK | MB_ICONEXCLAMATION);

    return FALSE;
  }

  linenum = 0;
  ScriptToImportFound = FALSE;

  // Read in and parse each line of the file
  while (!cfeof(infile) && !ScriptToImportFound) {

    // Clear the buffer
    strcpy(linebuf, "");

    // Read in a line from the file
    cf_ReadString(linebuf, sizeof(linebuf), infile);
    linenum++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(linebuf);
    line = SkipInitialWhitespace(linebuf);

    // Check for Start of Script Block Section
    if (strncmp(line, SCRIPT_START_TAG, strlen(SCRIPT_START_TAG)) == 0) {
      bool done = false;

      // Clear out the name lists
      ClearNameLists();

      // Set valid line counter to track whether we're reading header info or tree nodes
      valid_lines_read = 0;

      // Set tree node trackers so we know where we are in the actual tree
      last_node_added = NULL;
      current_parent = TVI_ROOT;

      // Set variables that allow child nodes to be skipped over
      // when a bad Action or Query node is read in (invalid function name)
      skip_children = FALSE;
      skip_depth = 0;
      last_node_childless = FALSE;

      // Read all the lines in the block
      while (!done && !cfeof(infile)) {

        strcpy(linebuf, "");
        cf_ReadString(linebuf, sizeof(linebuf), infile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        // If it's an empty line or a comment, skip it
        if (strlen(line) == 0 || strncmp(line, "//", 2) == 0)
          continue;

        // Check for End of Script Block Section
        if (strncmp(line, SCRIPT_END_TAG, strlen(SCRIPT_END_TAG)) == 0) {
          done = true;
          continue;
        }

        // Is it the start of a child block?
        if (strncmp(line, CHILD_BLOCK_START_TAG, strlen(CHILD_BLOCK_START_TAG)) == 0) {
          last_node_childless = FALSE;
          if (!skip_children) {
            current_parent = last_node_added;
            if (current_parent == NULL)
              current_parent = TVI_ROOT;
          } else {
            skip_depth++;
          }
          continue;
        }

        // Handles Validation of childless function nodes
        if (last_node_added != NULL && last_node_childless) {
          ValidateFunctionNode(last_node_added, linenum);

          // Need this to update node text that depends on subnodes
          UpdateNodeText(last_node_added);

          last_node_childless = FALSE;
        }

        // Is it the end of a child block?
        if (strncmp(line, CHILD_BLOCK_END_TAG, strlen(CHILD_BLOCK_END_TAG)) == 0) {
          if (!skip_children || skip_depth <= 0) {

            skip_children = FALSE;
            skip_depth = 0;

            last_node_added = current_parent;
            if (last_node_added == TVI_ROOT)
              last_node_added = NULL;
            else {
              // Need this to validate a function node once all of its params have been added
              ValidateFunctionNode(last_node_added, linenum);

              // Need this to update node text that depends on subnodes
              UpdateNodeText(last_node_added);
            }

            if (current_parent != TVI_ROOT)
              current_parent = m_ScriptTree.GetParentItem(current_parent);
            if (current_parent == NULL)
              current_parent = TVI_ROOT;
          } else
            skip_depth--;

          continue;
        }

        // If we're skipping children, but the depth is still zero here,
        // then must not be any children to skip!
        if (skip_children && skip_depth <= 0) {
          skip_children = FALSE;
          skip_depth = 0;
        }

        // See if it should be the script name line
        if (valid_lines_read == 0) {
          if (stricmp(line, script_name) == 0)
            ScriptToImportFound = TRUE;
          else
            ScriptToImportFound = FALSE;
          valid_lines_read++;
          continue;
        }

        // See if it should be the save version line
        if (valid_lines_read == 1) {
          rc = sscanf(line, "%s %d", tempbuf, &version);
          if (rc == 2 && strcmp(tempbuf, "VERSION") == 0)
            valid_lines_read++;
          continue;
        }

        // It must be a node then,
        // so (if we're not skipping children) parse it and add it to the tree
        if (!skip_children && ScriptToImportFound) {

          if (initial_insert_before != NULL) {
            insert_before = initial_insert_before;
            initial_insert_before = NULL;
          } else
            insert_before = TVI_LAST;

          if (version >= 1)
            returned_node =
                ParseScriptNodeLine_v1U(line, linenum, current_parent, skip_children, version, insert_before);
          else
            returned_node = ParseScriptNodeLine_v0(line, linenum, current_parent, skip_children, insert_before);

          if (returned_node != NULL) {
            if (new_script_header == NULL)
              new_script_header = returned_node;
            last_node_added = returned_node;
            last_node_childless = TRUE;
            UpdateNodeText(last_node_added);
          } else
            ScriptFileParseError(INVALID_NODE_ERR, linenum, 0, NULL);

          if (returned_node == NULL || skip_children) {
            skip_children = TRUE;
            skip_depth = 0;
          }
        }
      }

      if (!done)
        ScriptFileParseError(UEOS_ERR, linenum, 0, NULL);
    }
  }

  cfclose(infile);

  // Change the script ID for the new script
  if (new_script_header != NULL) {
    tTreeNodeData *data = (tTreeNodeData *)m_ScriptTree.GetItemData(new_script_header);
    if (data != NULL && data->type == SCRIPT_HEADER_NODE) {
      int new_id = GetLowestUnusedScriptID();
      data->ID = new_id;
      UpdateNodeText(new_script_header);
      HighlightScript(new_script_header);

      if (new_id == m_NextScriptID)
        m_NextScriptID++;

      m_ScriptTree.SelectItem(new_script_header);
      AssignSpecificValue();
      SetModified(TRUE);
    }
  }

  return TRUE;
}

#define TEMP_EXPORT_FNAME "DExport.tmp"

// Adds selected script to specified library file
bool CDallasMainDlg::ExportScriptToFile(char *filename, char *script_name) {
  CFILE *infile;
  char linebuf[2048];
  char *line;
  int linenum;
  int valid_lines_read;
  HTREEITEM selected_node, script_header_node;
  bool ReplacingScript;
  bool ScriptReplaced;

  CurrentParsingFilename = filename;

  // Make sure the selected item is valid for exporting
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return FALSE;
  script_header_node = GetParentNodeOfType(selected_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return FALSE;

  // Make sure library file can be written to
  if (_access(filename, 0) != -1) {
    if ((_access(filename, 2)) == -1) {
      CString msg;
      msg.Format("The library file \"%s\" is read-only!", filename);
      MessageBox(msg, "Script Library File Not Writeable!", MB_OK | MB_ICONEXCLAMATION);
      return FALSE;
    }
  }

  // Try to open the file for reading
  infile = cfopen(filename, "rt");

  // Try to open the temp file for writing
  CurrentOutputFile = cfopen(TEMP_EXPORT_FNAME, "wt");
  if (CurrentOutputFile == NULL) {
    CString msg, title;
    msg.Format("ERROR: Unable to open %s for output.", TEMP_EXPORT_FNAME);
    title.Format("Temp File Save Error!");
    MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
    if (infile != NULL)
      cfclose(infile);
    return FALSE;
  }

  // If file doesn't exist, Write out the header info
  if (infile == NULL) {
    O(("/////////////////////////////////////////////////////////////////////"));
    O(("// D.A.L.L.A.S. Generated Script Library File "));
    O(("/////////////////////////////////////////////////////////////////////"));
    O((" "));
  }

  linenum = 0;
  ReplacingScript = FALSE;
  ScriptReplaced = FALSE;

  // Read in and parse each line of the file
  while (infile != NULL && !cfeof(infile)) {

    // Clear the buffer
    strcpy(linebuf, "");

    // Read in a line from the file
    cf_ReadString(linebuf, sizeof(linebuf), infile);
    linenum++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(linebuf);
    line = SkipInitialWhitespace(linebuf);

    // Check for Start of Script Block Section
    if (strncmp(line, SCRIPT_START_TAG, strlen(SCRIPT_START_TAG)) == 0) {
      bool done = false;

      // Write out the start tag
      O(("%s", linebuf));

      // Set valid line counter to track whether we're reading header info or tree nodes
      valid_lines_read = 0;

      // Read all the lines in the block
      while (!done && !cfeof(infile)) {

        strcpy(linebuf, "");
        cf_ReadString(linebuf, sizeof(linebuf), infile);
        linenum++;

        // Remove whitespace padding at start and end of line
        RemoveTrailingWhitespace(linebuf);
        line = SkipInitialWhitespace(linebuf);

        // If it's an empty line or a comment, skip it
        if (strlen(line) == 0 || strncmp(line, "//", 2) == 0) {
          if (!ReplacingScript)
            O(("%s", linebuf));
          continue;
        }

        // Check for End of Script Block Section
        if (strncmp(line, SCRIPT_END_TAG, strlen(SCRIPT_END_TAG)) == 0) {
          if (ReplacingScript) {
            ScriptReplaced = TRUE;
            ReplacingScript = FALSE;
          }
          O(("%s", linebuf));
          done = true;
          continue;
        }

        // See if this script's name matches the given name
        if (valid_lines_read == 0) {
          if (stricmp(line, script_name) == 0) {
            CString msg, title;

            msg.Format("A script named '%s' already exists in this library.\n\nWould you like to replace it with your "
                       "new script?",
                       script_name);
            title.Format("Duplicate Script Name Encountered");

            // Prompt user to see if it should be replaced
            if (MessageBox(msg, title, MB_YESNO | MB_ICONQUESTION) == IDNO) {
              cfclose(infile);
              cfclose(CurrentOutputFile);
              CurrentOutputFile = NULL;
              ddio_DeleteFile(TEMP_EXPORT_FNAME);
              return FALSE;
            }

            // Copy the new script into it's place
            O(("%s", script_name));
            O(("VERSION		%d", DALLAS_SAVE_VERSION));

            CurrentTabLevel = 0;
            if (DALLAS_SAVE_VERSION >= 1)
              WriteScriptNodeDump_v1U(script_header_node, TRUE);
            else
              WriteScriptNodeDump_v0(script_header_node);
            WriteScriptChildrenDump(script_header_node, TRUE);

            ReplacingScript = TRUE;
          } else
            O(("%s", linebuf));

          valid_lines_read++;
          continue;
        }

        if (!ReplacingScript)
          O(("%s", linebuf));
      }

      if (!done)
        ScriptFileParseError(UEOS_ERR, linenum, 0, NULL);
    } else
      O(("%s", linebuf));
  }

  // If the script wasn't replaced, add it at the end
  if (!ScriptReplaced) {
    O(("%s", SCRIPT_START_TAG));
    O(("%s", script_name));
    O(("VERSION		%d", DALLAS_SAVE_VERSION));

    CurrentTabLevel = 0;
    if (DALLAS_SAVE_VERSION >= 1)
      WriteScriptNodeDump_v1U(script_header_node, TRUE);
    else
      WriteScriptNodeDump_v0(script_header_node);
    WriteScriptChildrenDump(script_header_node, TRUE);

    O(("%s", SCRIPT_END_TAG));
    O((" "));
  }

  if (infile != NULL)
    cfclose(infile);

  cfclose(CurrentOutputFile);
  CurrentOutputFile = NULL;

  // Now delete the library input file, and replace it with the temp file
  ddio_DeleteFile(filename);
  if (!CopyFile(TEMP_EXPORT_FNAME, filename, FALSE)) {
    CString msg, title;
    msg.Format("ERROR: Could not copy over temporary library file.\n\nThe export failed.");
    title.Format("Script Export Error!");
    MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
  } else {
    CString msg, title;
    msg.Format("The script was exported successfully!");
    title.Format("Script Export Successful");
    MessageBox(msg, title, MB_OK | MB_ICONINFORMATION);
  }

  ddio_DeleteFile(TEMP_EXPORT_FNAME);

  return TRUE;
}

// Imports a script from a specified Library file
void CDallasMainDlg::OnImportButton() {
  HTREEITEM selected_node, initial_insert_before;
  CString library_filename;

  // Make sure the selected item is valid for importing
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;
  if (GetNodeType(selected_node) == CLIPBOARD_HEADER_NODE)
    initial_insert_before = selected_node;
  else {
    initial_insert_before = GetParentNodeOfType(selected_node, SCRIPT_HEADER_NODE);
    if (initial_insert_before == NULL)
      return;
    if (m_ScriptTree.GetParentItem(initial_insert_before) != NULL)
      return;
  }

  // Display file selection dlg
  if (!ScriptLibraryFilePrompt(library_filename, TRUE))
    return;

  // Scan the file and display scripts that can be imported
  CDallasImportDlg dlg;
  dlg.m_Filename = library_filename;
  if (dlg.DoModal() == IDCANCEL)
    return;
  if (dlg.m_ScriptName.IsEmpty())
    return;

  // Try to import the selected script
  ImportScriptFromFile(library_filename.GetBuffer(0), dlg.m_ScriptName.GetBuffer(0));
}

// Exports a script to a specified Library file
void CDallasMainDlg::OnExportButton() {
  HTREEITEM selected_node, script_header_node;
  CString library_filename;

  // Make sure the selected item is valid for exporting
  selected_node = m_ScriptTree.GetSelectedItem();
  if (selected_node == NULL)
    return;
  script_header_node = GetParentNodeOfType(selected_node, SCRIPT_HEADER_NODE);
  if (script_header_node == NULL)
    return;

  // Display the enter name prompt
  CDallasGenericPromptDlg dlg;
  dlg.m_DialogTitle = "Exported Script Name Prompt";
  dlg.m_PromptText = "Enter the name for this exported script:";
  dlg.m_PromptData = "";
  dlg.m_MaxDataLength = 256;

  if (dlg.DoModal() == IDCANCEL)
    return;
  if (dlg.m_PromptData.IsEmpty())
    return;

  // Display file selection dlg
  if (!ScriptLibraryFilePrompt(library_filename, FALSE))
    return;

  // Try to export the selected script to the specified library file
  ExportScriptToFile(library_filename.GetBuffer(0), dlg.m_PromptData.GetBuffer(0));
}

CDallasMainDlg *GetDallasDialogPtr(void) {
#ifdef NEWEDITOR
  CNewEditorApp *editor_app;
  editor_app = (CNewEditorApp *)AfxGetApp();
#else
  CEditorApp *editor_app;
  editor_app = &theApp;
#endif

  return editor_app->m_DallasModelessDlgPtr;
}
