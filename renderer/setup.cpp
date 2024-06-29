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
#include <stdlib.h>
#include <string.h>
#include "3d.h"
#include "pserror.h"
#include "HardwareInternal.h"
#include "renderer.h"

//User-specified aspect ratio, stored as w/h
static float sAspect = 0.0f;

//initialize the 3d system
void g3_Init(void)
{
	atexit(g3_Close);
}

//close down the 3d system
void g3_Close(void)
{
}

//allows the program to specify an aspect ratio that overrides the renderer's
//The parameter is the w/h of the screen pixels
void g3_SetAspectRatio(float aspect)
{
	sAspect = aspect;
}

// returns the user-specified aspect ratio used to override the renderer's
float g3_GetAspectRatio() { return sAspect; }

void g3_GetViewPortMatrix( float *viewMat )
{
	// extract the viewport data from the renderer
	int viewportWidth, viewportHeight;
	int viewportX, viewportY;
	rend_GetProjectionScreenParameters( viewportX, viewportY, viewportWidth, viewportHeight );

	float viewportWidthOverTwo  =  ((float)viewportWidth) * 0.5f;
	float viewportHeightOverTwo = ((float)viewportHeight) * 0.5f;

	// setup the matrix
	memset( viewMat, 0, sizeof(float) * 16 );
	viewMat[0]  = viewportWidthOverTwo;
	viewMat[5]  = -viewportHeightOverTwo;
	viewMat[12] = viewportWidthOverTwo + (float)viewportX;
	viewMat[13] = viewportHeightOverTwo + (float)viewportY;	
	viewMat[10] = viewMat[15] = 1.0f;
}

void g3_GetProjectionMatrix( float zoom, float *projMat )
{
	// get window size
	int viewportWidth, viewportHeight;
	rend_GetProjectionParameters( &viewportWidth, &viewportHeight );

	float s = ((float)Window_width / Window_height);

	// setup the matrix
	memset( projMat, 0, sizeof(float) * 16 );

	// calculate 1/tan(fov)
	//Convert zoom into vertical FOV for my convenience, since I'm locking the Y FOV when the screen gets wider. 
	zoom *= 3.f / 4.f;

	float oOT = 1.0f / zoom;

	float znear = 1.0f;
	float zfar = 10000.f; //debug

	float C = -((zfar + znear) / (zfar - znear));
	float D = -((2 * zfar * znear) / (zfar - znear));

	// fill in the matrix
	if (s <= 1.0f)
	{
		projMat[0] = oOT;
		projMat[5] = oOT * s;
	}
	else
	{
		projMat[0] = oOT / s;
		projMat[5] = oOT;
	}
	projMat[10] = C;
	projMat[11] = -1;
	projMat[14] = D;
	/*projMat[10] =  1.0f;
	projMat[11] =  1.0f;
	projMat[14] = -1.0f;*/
}

//start the frame
void g3_StartFrame(vector *view_pos,matrix *view_matrix,float zoom)
{
	// initialize the viewport transform
	g3_GetViewPortMatrix( (float*)gTransformViewPort );
	g3_GetProjectionMatrix( zoom, (float*)gTransformProjection );
	g3_GetModelViewMatrix( view_pos, view_matrix, (float*)gTransformModelView );
	g3_UpdateFullTransform();

	//[ISB] Update the common uniform block for all 3D shaders. 
	rend_UpdateCommon((float*)gTransformProjection, (float*)gTransformModelView);

	// get window size
	rend_GetProjectionParameters( &Window_width, &Window_height );

	//Set vars for projection
	Window_w2 = ((float)Window_width)  * 0.5f;
	Window_h2 = ((float)Window_height) * 0.5f;

	//float s = screen_aspect * (float) Window_height / (float) Window_width;
	//[ISB] Just use the aspect of the window, the screen aspect is not important since pixels are all square
	float s = ((float)Window_width / Window_height);// / (4.f / 3.f);

	if( s <= 1.0f )
	{
		//scale x
		Matrix_scale.x = 1.0f;
		Matrix_scale.y = s;
	}
	else 
	{
		Matrix_scale.y = 1.0f;
		Matrix_scale.x = 1.0f / s;
	}

	//Convert zoom into vertical FOV for my convenience, since I'm locking the Y FOV when the screen gets wider. 
	zoom *= 3.f / 4.f;

	Matrix_scale.z = 1.0f;

	//Set the view variables
	View_position   = *view_pos;
	View_zoom       =  zoom;
	Unscaled_matrix = *view_matrix;

	//zoom by scaling x and y
	//[ISB] This no longer will scale Z to apply FOV, since it causes problems with the depth ranges. 
	float oOZ = 1.0f / View_zoom;
	Matrix_scale.x = Matrix_scale.x * oOZ;
	Matrix_scale.y = Matrix_scale.y * oOZ;

	//Scale the matrix elements
	View_matrix.rvec = Unscaled_matrix.rvec * Matrix_scale.x;
	View_matrix.uvec = Unscaled_matrix.uvec * Matrix_scale.y;
	View_matrix.fvec = Unscaled_matrix.fvec * Matrix_scale.z;

	//Reset the list of free points
	InitFreePoints();

	//Reset the far clip plane
	g3_ResetFarClipZ();
}

//this doesn't do anything, but is here for completeness
void g3_EndFrame(void)
{
	//make sure temp points are free
	CheckTempPoints();
}

//get the current view position
void g3_GetViewPosition(vector *vp)
{
	*vp = View_position;
}

void g3_GetViewMatrix(matrix *mat)
{
	*mat = View_matrix;
}

void g3_GetUnscaledMatrix(matrix *mat)
{
	*mat = Unscaled_matrix;
}

// Gets the matrix scale vector
void g3_GetMatrixScale(vector *matrix_scale)
{
	*matrix_scale=Matrix_scale;
}
