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

struct InstanceContext
{
	matrix m_viewMatrix;		// matrix
	matrix m_unscaledMatrix;	// unscaled matrix
	vector m_viewPosition;		// position
	float  m_modelView[4][4];	// model/view transform
};

#define MAX_INSTANCE_DEPTH	30
static InstanceContext sInstanceStack[MAX_INSTANCE_DEPTH];
static int sInstanceDepth = 0;

//instance at specified point with specified orientation
void g3_StartInstanceMatrix( vector *pos, matrix *orient )
{
	ASSERT( orient != NULL );
	ASSERT( sInstanceDepth < MAX_INSTANCE_DEPTH );

	sInstanceStack[sInstanceDepth].m_viewMatrix     = View_matrix;
	sInstanceStack[sInstanceDepth].m_viewPosition   = View_position;
	sInstanceStack[sInstanceDepth].m_unscaledMatrix = Unscaled_matrix;
	memcpy( sInstanceStack[sInstanceDepth].m_modelView, gTransformModelView, sizeof(gTransformModelView) );
	++sInstanceDepth;

	//step 1: subtract object position from view position
	vector tempv = View_position - *pos;

	//step 2: rotate view vector through object matrix
	View_position = tempv * *orient;

	//step 3: rotate object matrix through view_matrix (vm = ob * vm)
	matrix tempm, tempm2 = ~*orient;

	tempm = tempm2 * View_matrix;
	View_matrix = tempm;

	tempm = tempm2 * Unscaled_matrix;
	Unscaled_matrix = tempm;

	// transform the model/view matrix
	g3_GetModelViewMatrix( &View_position, &Unscaled_matrix, (float*)gTransformModelView );
	g3_UpdateFullTransform();
}


//instance at specified point with specified orientation
void g3_StartInstanceAngles(vector *pos,angvec *angles)
{
	if( angles == NULL )
	{
		matrix ident;
		vm_MakeIdentity( &ident );
		g3_StartInstanceMatrix( pos, &ident );
		return;
	}

	matrix tm;
	vm_AnglesToMatrix( &tm, angles->p, angles->h, angles->b );

	g3_StartInstanceMatrix( pos, &tm );
}


//pops the old context
void g3_DoneInstance()
{
	--sInstanceDepth;
	ASSERT( sInstanceDepth >= 0 );

	View_position   = sInstanceStack[sInstanceDepth].m_viewPosition;
	View_matrix     = sInstanceStack[sInstanceDepth].m_viewMatrix;
	Unscaled_matrix = sInstanceStack[sInstanceDepth].m_unscaledMatrix;
	memcpy( gTransformModelView, sInstanceStack[sInstanceDepth].m_modelView, sizeof(gTransformModelView) );
	g3_UpdateFullTransform();
}