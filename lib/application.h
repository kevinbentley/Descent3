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

 * $Logfile: /DescentIII/Main/lib/application.h $
 * $Revision: 11 $
 * $Date: 7/28/99 3:29p $
 * $Author: Kevin $
 *
 *	Generic Application object.  Used to pass info to libraries
 *
 * $Log: /DescentIII/Main/lib/application.h $
 *
 * 11    7/28/99 3:29p Kevin
 * Macintosh!
 *
 * 10    4/15/99 1:44a Jeff
 * changes for linux compile
 *
 * 9     10/08/98 7:26p Samir
 * changed the prototype for the defer handler callback.
 *
 * 8     9/14/98 4:03p Samir
 * added console support.
 *
 * 7     3/23/98 8:04p Samir
 * defer handler now returns a bool.
 *
 * 6     2/26/98 1:00p Samir
 * Added application activation functions.
 *
 * 5     2/23/98 4:30p Samir
 * added init function to oeApplication.
 *
 * 4     10/16/97 2:30p Samir
 * Added Idle processing.
 *
 * 3     9/16/97 1:04p Samir
 * Added delay function.
 *
 * 2     7/28/97 3:46p Samir
 * Added OEAPP_TOPMOST flag.
 *
 * 2     6/11/97 2:39p Samir
 * Added destructors.
 *
 * 1     6/10/97 4:55p Samir
 * New App object.
 *
 * $NoKeywords: $
 */
#ifndef APP_H
#define APP_H
#include "pstypes.h"
/*	Basic Application data types */
/*	Application Object
                This object entails initialization and cleanup of all operating system
                elements, as well as data that libraries may need to initialize their
                systems.  Look under the specific header file for a platform for information
                about what's needed for the target machine.
*/
/*	Application flags */
const int OEAPP_WINDOWED = 1, // App will run in a window. May not be supported.
    OEAPP_FULLSCREEN = 2,     // App will run in fullscreen.  May not be supported.
    OEAPP_TOPMOST = 4,        // App will be on the topmost display.  May not be supported.
    OEAPP_CONSOLE = 8;        // App will run in a console style window.
class oeApplication {
protected:
  bool m_AppActive;

public:
  oeApplication() { m_AppActive = true; };
  virtual ~oeApplication(){};
  //	initializes the object
  virtual void init() = 0;
  //	Function to retrieve information from object through a platform defined structure.
  virtual void get_info(void *buffer) = 0;
  //	Function to get the flags
  virtual int flags(void) const = 0;
  //	defer returns some flags.   essentially this function defers program control to OS.
  virtual unsigned defer() = 0;
  //	suspends application for a certain amout of time...
  virtual void delay(float secs) = 0;
  //	set a function to run when deferring to OS.
  virtual void set_defer_handler(void (*func)(bool)) = 0;

public:
  //	checks if the application is active
  bool active() const { return m_AppActive; };
  void activate() { m_AppActive = true; };
  void deactivate() { m_AppActive = false; };
};
/*	This section includes the platform-specific header files
        Add a platform to this list once implemented:
                Win32				Samir		Win32App.h			06/97
*/
// #if defined(WIN32)
// #include "win\win32app.h"
// #elif defined(__LINUX__)
#include "lnxapp.h"
// #endif
#endif // APP_H
