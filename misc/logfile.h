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


#ifndef LOGFILE_H
#define LOGFILE_H

void log_Enable(bool enable);
void log_Disable();

class logfile {
  void *fp;

public:
  logfile(); // simple constructor
  ~logfile();

  void start(const char *fname, const char *longname = 0); // restarts the logfile (opens a new one.)
  void end();

  void printf(const char *fmt, ...);
  void puts(const char *msg);
  void update(); // call to update logfile on disk (done by OS otherwise)
};

#endif
