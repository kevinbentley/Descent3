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
#include "3d.h"
#include "HardwareInternal.h"
#include <float.h>

vector	View_position;
float	View_zoom;

float	Far_clip_z=FLT_MAX; 		// set to a really really far distance initially

uint8_t	Clip_custom=0;
float	Clip_plane_distance=0;
vector	Clip_plane;

matrix	Unscaled_matrix;		//before scaling
matrix	View_matrix;

vector	Matrix_scale;			//how the matrix is scaled, window_scale * zoom

int		Window_width;			//the actual width
int		Window_height;			//the actual height

float	Window_w2;				//width/2
float	Window_h2;				//height/2

float gTransformViewPort[4][4];
float gTransformProjection[4][4];
float gTransformModelView[4][4];
float gTransformFull[4][4];
