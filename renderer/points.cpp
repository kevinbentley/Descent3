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
#include <string.h>

extern vector Clip_plane_point;
//code a point.  fills in the p3_codes field of the point, and returns the codes
uint8_t g3_CodePoint(g3Point *p)
{
	uint8_t cc=0;

	if (p->p3_x > p->p3_z)
		cc |= CC_OFF_RIGHT;

	if (p->p3_y > p->p3_z)
		cc |= CC_OFF_TOP;

	if (p->p3_x < -p->p3_z)
		cc |= CC_OFF_LEFT;

	if (p->p3_y < -p->p3_z)
		cc |= CC_OFF_BOT;

	if (p->p3_z < 0)
		cc |= CC_BEHIND;

	if (p->p3_z > Far_clip_z)
		cc |=CC_OFF_FAR;

	// Check to see if we should be clipped to the custom plane
	if (Clip_custom)
	{
		vector vec=p->p3_vec-Clip_plane_point;
		vec.x/=Matrix_scale.x;
		vec.y/=Matrix_scale.y;
		vec.z/=Matrix_scale.z;

		float dp=vec*Clip_plane;
		if( dp < -0.005f )
		{
			cc |= CC_OFF_CUSTOM;
		}
	}

	return p->p3_codes = cc;

}

//rotates a point. returns codes.  does not check if already rotated
uint8_t g3_RotatePoint(g3Point *dest,vector *src)
{
	// store the pre-rotated point
	dest->p3_vecPreRot = *src;

	// find the point offset from the view/camera position
	vector tempv = *src - View_position;

	// rotate the point by the view/camera's orientation
	dest->p3_vec = tempv * View_matrix;

	// determine the flags for the point
	dest->p3_flags = PF_ORIGPOINT;
	return g3_CodePoint( dest );
}

//projects a point
void g3_ProjectPoint(g3Point *p)
{
	if (p->p3_flags & PF_PROJECTED || p->p3_codes & CC_BEHIND)
		return;

	float one_over_z=1.0/p->p3_z;
	p->p3_sx = Window_w2 + (p->p3_x * (Window_w2 * one_over_z));
	p->p3_sy = Window_h2 - (p->p3_y * (Window_h2 * one_over_z));
	p->p3_flags |= PF_PROJECTED;
}

//from a 2d point, compute the vector through that point
void g3_Point2Vec(vector *v,short sx,short sy)
{
	vector tempv;
	matrix tempm;

	tempv.x =  (((sx - Window_w2) / Window_w2) * Matrix_scale.z / Matrix_scale.x);
	tempv.y = -(((sy - Window_h2) / Window_h2) * Matrix_scale.z / Matrix_scale.y);
	tempv.z = 1.0f;

	vm_NormalizeVector(&tempv);

	tempm = ~Unscaled_matrix;

	*v = tempv * tempm;
}

//delta rotation functions
vector *g3_RotateDeltaX(vector *dest,float dx)
{
	dest->x = View_matrix.rvec.x * dx;
	dest->y = View_matrix.uvec.x * dx;
	dest->z = View_matrix.fvec.x * dx;

	return dest;
}

vector *g3_RotateDeltaY(vector *dest,float dy)
{
	dest->x = View_matrix.rvec.y * dy;
	dest->y = View_matrix.uvec.y * dy;
	dest->z = View_matrix.fvec.y * dy;

	return dest;
}

vector *g3_RotateDeltaZ(vector *dest,float dz)
{
	dest->x = View_matrix.rvec.z * dz;
	dest->y = View_matrix.uvec.z * dz;
	dest->z = View_matrix.fvec.z * dz;

	return dest;
}

vector *g3_RotateDeltaVec(vector *dest,vector *src)
{
	*dest = *src * View_matrix;

	return dest;
}

uint8_t g3_AddDeltaVec(g3Point *dest,g3Point *src,vector *deltav)
{
	dest->p3_vec = src->p3_vec + *deltav;

	dest->p3_flags = 0;		//not projected

	return g3_CodePoint(dest);
}

//calculate the depth of a point - returns the z coord of the rotated point
float g3_CalcPointDepth(vector *pnt)
{
	return	((pnt->x - View_position.x) * View_matrix.fvec.x) +
		((pnt->y - View_position.y) * View_matrix.fvec.y) +
		((pnt->z - View_position.z) * View_matrix.fvec.z);
}
