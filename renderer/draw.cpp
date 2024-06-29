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
#include "RendererConfig.h"
#ifndef USE_SOFTWARE_TNL

#include "3d.h"
#include "HardwareInternal.h"
#include "renderer.h"

#define round(v) ( (int)( ((v) + 0.5f) ) )

//draws a line. takes two points.  returns true if drew
void g3_DrawLine(ddgr_color color,g3Point *p0,g3Point *p1)
{
	uint8_t codes_or;
	bool was_clipped=0;

	if (p0->p3_codes & p1->p3_codes)
		return;

	codes_or = p0->p3_codes | p1->p3_codes;

	if (codes_or)
	{
		ClipLine(&p0,&p1,codes_or);
		was_clipped = 1;
	}

	if (!(p0->p3_flags & PF_PROJECTED))
	{
		g3_ProjectPoint(p0);
	}

	if (!(p1->p3_flags & PF_PROJECTED))
	{
		g3_ProjectPoint(p1);
	}

	rend_SetFlatColor (color);
	rend_DrawLine( round(p0->p3_sx),round(p0->p3_sy),round(p1->p3_sx),round(p1->p3_sy));

	//If was clipped, free temp points
	if (was_clipped)
	{
		if (p0->p3_flags & PF_TEMP_POINT)
		{
			FreeTempPoint(p0);
		}

		if (p1->p3_flags & PF_TEMP_POINT)
		{
			FreeTempPoint(p1);
		}

		//Make sure all temp points have been freed
		CheckTempPoints();
	}
}

//draws a line based on the current setting of render states. takes two points.  returns true if drew
void g3_DrawSpecialLine(g3Point *p0,g3Point *p1)
{
	uint8_t codes_or;
	bool was_clipped=0;

	if (p0->p3_codes & p1->p3_codes)
		return;

	codes_or = p0->p3_codes | p1->p3_codes;

	if (codes_or)
	{

		ClipLine(&p0,&p1,codes_or);

		was_clipped = 1;
	}

	if (!(p0->p3_flags & PF_PROJECTED))
		g3_ProjectPoint(p0);

	if (!(p1->p3_flags & PF_PROJECTED))
		g3_ProjectPoint(p1);

	rend_DrawSpecialLine (p0,p1);

	//If was clipped, free temp points
	if (was_clipped)
	{
		if (p0->p3_flags & PF_TEMP_POINT)
			FreeTempPoint(p0);

		if (p1->p3_flags & PF_TEMP_POINT)
			FreeTempPoint(p1);

		//Make sure all temp points have been freed
		CheckTempPoints();
	}
}

//returns true if a plane is facing the viewer. takes the unrotated surface 
//normal of the plane, and a point on it.  The normal need not be normalized
bool g3_CheckNormalFacing(vector *v,vector *norm)
{
	vector tempv;

	tempv = View_position - *v;

	return ((tempv * *norm) > 0);
}

bool DoFacingCheck(vector *norm,g3Point **vertlist,vector *p)
{
	if (norm)
	{
		//have normal
		ASSERT(norm->x || norm->y || norm->z);
		return g3_CheckNormalFacing(p,norm);
	}
	else
	{
		//normal not specified, so must compute
		vector tempv;
		//get three points (rotated) and compute normal
		vm_GetPerp(&tempv,&vertlist[0]->p3_vec,&vertlist[1]->p3_vec,&vertlist[2]->p3_vec);
		return ((tempv * vertlist[1]->p3_vec) < 0);
	}
}

//like g3_DrawPoly(), but checks to see if facing.  If surface normal is
//NULL, this routine must compute it, which will be slow.  It is better to 
//pre-compute the normal, and pass it to this function.  When the normal
//is passed, this function works like g3_CheckNormalFacing() plus
//g3_DrawPoly().
void g3_CheckAndDrawPoly(int nv,g3Point **pointlist,int bm,vector *norm,vector *pnt)
{
	if (DoFacingCheck(norm,pointlist,pnt))
		g3_DrawPoly(nv,pointlist,bm);
}

int Triangulate_test = 0;

//draw a polygon
//Parameters:	nv - the number of verts in the poly
//					pointlist - a pointer to a list of pointers to points
//					bm - the bitmap handle if texturing.  ignored if flat shading
// Returns 0 if clipped away
int g3_DrawPoly(int nv,g3Point **pointlist,int bm,int map_type,g3Codes *clip_codes)
{
	int i;
	g3Codes cc;
	bool was_clipped=0;

	if( Triangulate_test && (nv > 3) )
	{
		g3Point *tripoints[3];
		int sum=0;

		for (i=0;i<nv-2;i++) 
		{
			tripoints[0] = pointlist[0];
			tripoints[1] = pointlist[i+1];
			tripoints[2] = pointlist[i+2];
			sum += g3_DrawPoly( 3, tripoints, bm, map_type );
		}

		return sum;
	}

	//Initialize or just used the ones passed in
	if( clip_codes )
	{
		cc = *clip_codes;
	}
	else
	{
		cc.cc_or  = 0;
		cc.cc_and = 0xff;

		//Get codes for this polygon, and copy uvls into points
		for( i = 0; i < nv; ++i ) 
		{
			uint8_t c = pointlist[i]->p3_codes;
			cc.cc_and &= c;
			cc.cc_or  |= c;
		}
	}

	//All points off screen?
	if( cc.cc_and )
		return 0;

	//One or more point off screen, so clip
	if( cc.cc_or )
	{
		//Clip the polygon, getting pointer to new buffer
		pointlist = g3_ClipPolygon( pointlist, &nv, &cc );

		//Flag as clipped so temp points will be freed
		was_clipped = 1;

		//Check for polygon clipped away, or clip otherwise failed
		if( (nv==0) || (cc.cc_or&CC_BEHIND) || cc.cc_and )
			goto free_points;
	}

	//Make list of 2d coords (& check for overflow)
	for( i = 0; i < nv; ++i )
	{
		g3Point *p = pointlist[i];

		//Project if needed
		if( !(p->p3_flags&PF_PROJECTED) )
		{
			g3_ProjectPoint(p);
		}
	}

	//Draw!
	rend_DrawPolygon3D( bm, pointlist, nv, map_type );

free_points:;

	//If was clipped, free temp points
	if( was_clipped )
	{
		g3_FreeTempPoints( pointlist, nv );
	}

	return 1;
}

//draw a sortof sphere - i.e., the 2d radius is proportional to the 3d
//radius, but not to the distance from the eye
void g3_DrawSphere(ddgr_color color,g3Point *pnt,float rad)
{
	if (! (pnt->p3_codes & CC_BEHIND))
	{
		if (! (pnt->p3_flags & PF_PROJECTED))
			g3_ProjectPoint(pnt);

		rend_FillCircle(color, pnt->p3_sx, pnt->p3_sy,(rad * Matrix_scale.x * Window_w2 / pnt->p3_z));
	}
}

//draws a bitmap with the specified 3d width & height 
// If offsets  are not -1, then the blitter draws not from the upper left hand 
// corner of the bitmap, but from size*offsetx,size*offsety
// See Jason for explaination
void g3_DrawBitmap(vector *pos,float width,float height,int bm,int color)
{
	g3Point pnt;
	float w, h;
	int dx, dy, dw, dh;
	float u0 = 0.0, u1 = 1.0;
	float v0 = 0.0, v1 = 1.0;

	if (g3_RotatePoint(&pnt, pos) & CC_BEHIND)
		return;

	if (pnt.p3_codes & CC_OFF_FAR)
		return;


	g3_ProjectPoint(&pnt);

	// Calculate the 4 corners of this bitmap

	w = (width * Window_w2) / pnt.p3_z * Matrix_scale.x;
	h = (height * Window_h2) / pnt.p3_z * Matrix_scale.y;

	dw = w;	//should round, right?
	dh = h;

	if (dw == 0 && dh == 0)
		return;

	dx = pnt.p3_sx - dw;
	dy = pnt.p3_sy - dh;

	// Now clip to make sure we're on screen

	int x1 = dx;
	int y1 = dy;
	int x2 = dx + dw * 2;
	int y2 = dy + dh * 2;

	if (x2 - x1 == 0)
		return;
	if (y2 - y1 == 0)
		return;

	float xstep = (u1 - u0) / (x2 - x1);
	float ystep = (v1 - v0) / (y2 - y1);

	// Clip x dimension
	if (x1 < 0)
	{
		u0 = (xstep * (-x1));
		x1 = 0;
	}
	else if (x1 > (Window_width - 1))
		return;

	if (x2 > (Window_width - 1))
	{
		u1 -= (xstep * (x2 - (Window_width - 1)));
		x2 = Window_width - 1;
	}
	else if (x2 < 0)
		return;

	// Clip y dimension
	if (y1 < 0)
	{
		v0 = (ystep * (-y1));
		y1 = 0;
	}
	else if (y1 > (Window_height - 1))
		return;

	if (y2 > (Window_height - 1))
	{
		v1 -= (ystep * (y2 - (Window_height - 1)));
		y2 = (Window_height - 1);
	}
	else if (y2 < 0)
		return;

	// And draw!!
	rend_DrawScaledBitmapWithZ(x1, y1, x2, y2, bm, u0, v0, u1, v1, pnt.p3_z, color);
}

// Draws a bitmap that has been rotated about its center.  Angle of rotation is passed as 'rot_angle'
void g3_DrawRotatedBitmap(vector *pos,angle rot_angle,float width,float height,int bm,int color)
{
	g3Point pnt, rot_points[8], * pntlist[8];
	vector rot_vectors[4];
	matrix rot_matrix;
	float w, h;
	int i;

	if (g3_RotatePoint(&pnt, pos) & CC_BEHIND)
		return;

	if (pnt.p3_codes & CC_OFF_FAR)
		return;

	vm_AnglesToMatrix(&rot_matrix, 0, 0, rot_angle);

	rot_matrix.rvec *= Matrix_scale.x;
	rot_matrix.uvec *= Matrix_scale.y;


	w = width;
	h = height;

	rot_vectors[0].x = -w;
	rot_vectors[0].y = h;

	rot_vectors[1].x = w;
	rot_vectors[1].y = h;

	rot_vectors[2].x = w;
	rot_vectors[2].y = -h;

	rot_vectors[3].x = -w;
	rot_vectors[3].y = -h;

	for (i = 0; i < 4; i++)
	{
		rot_vectors[i].z = 0;
		vm_MatrixMulVector(&rot_points[i].p3_vec, &rot_vectors[i], &rot_matrix);

		rot_points[i].p3_flags = PF_UV | PF_RGBA;
		rot_points[i].p3_l = 1.0;
		rot_points[i].p3_vec += pnt.p3_vec;

		g3_CodePoint(&rot_points[i]);
		pntlist[i] = &rot_points[i];
	}

	rot_points[0].p3_u = 0;
	rot_points[0].p3_v = 0;

	rot_points[1].p3_u = 1;
	rot_points[1].p3_v = 0;

	rot_points[2].p3_u = 1;
	rot_points[2].p3_v = 1;

	rot_points[3].p3_u = 0;
	rot_points[3].p3_v = 1;

	// And draw!!
	rend_SetTextureType(TT_LINEAR);

	if (color != -1)
	{
		rend_SetLighting(LS_FLAT_GOURAUD);
		rend_SetFlatColor(color);
	}

	g3_DrawPoly(4, pntlist, bm);
}

// Draws a bitmap on a specific plane.  Also does rotation.  Angle of rotation is passed as 'rot_angle'
void g3_DrawPlanarRotatedBitmap(vector *pos,vector *norm,angle rot_angle,float width,float height,int bm)
{
	matrix rot_matrix;
	vm_VectorToMatrix( &rot_matrix, norm, NULL, NULL );
	vm_TransposeMatrix( &rot_matrix );

	matrix twist_matrix;
	vm_AnglesToMatrix( &twist_matrix, 0, 0, rot_angle );

	float w = width;
	float h = height;

	vector rot_vectors[4];
	rot_vectors[0] =  (twist_matrix.rvec * -w);
	rot_vectors[0] += (twist_matrix.uvec * h); 

	rot_vectors[1] =  (twist_matrix.rvec * w);
	rot_vectors[1] += (twist_matrix.uvec * h);

	rot_vectors[2] =  (twist_matrix.rvec * w);
	rot_vectors[2] -= (twist_matrix.uvec * h);

	rot_vectors[3] =  (twist_matrix.rvec * -w);
	rot_vectors[3] -= (twist_matrix.uvec * h);

	int i;
	for( i = 0; i < 4; ++i )
	{	
		vector temp_vec = rot_vectors[i];
		vm_MatrixMulVector( &rot_vectors[i], &temp_vec, &rot_matrix );
	}

	g3Point rot_points[8],*pntlist[8];
	for( i = 0; i < 4; ++i )
	{		
		rot_vectors[i] += *pos;

		g3_RotatePoint( &rot_points[i], &rot_vectors[i] );
		rot_points[i].p3_flags |= PF_UV|PF_L;
		rot_points[i].p3_l     = 1.0f;

		pntlist[i] = &rot_points[i];
	}

	rot_points[0].p3_u = 0.0f;
	rot_points[0].p3_v = 0.0f;

	rot_points[1].p3_u = 1.0f;
	rot_points[1].p3_v = 0.0f;

	rot_points[2].p3_u = 1.0f;
	rot_points[2].p3_v = 1.0f;

	rot_points[3].p3_u = 0.0f;
	rot_points[3].p3_v = 1.0f;

	// And draw!!
	rend_SetTextureType( TT_LINEAR );
	g3_DrawPoly( 4, pntlist, bm );
}


//Draw a wireframe box aligned with the screen.  Used for the editor.
//Parameters:	color - the color to draw the lines
//					pnt - the center point
//					rad - specifies the width/2 & height/2 of the box
void g3_DrawBox(ddgr_color color,g3Point *pnt,float rad)
{
	if (! (pnt->p3_codes & CC_BEHIND))
	{
		if (! (pnt->p3_flags & PF_PROJECTED))
			g3_ProjectPoint(pnt);

		float w,h;

		w = rad * Matrix_scale.x * Window_w2 / pnt->p3_z;
		h = rad * Matrix_scale.y * Window_h2 / pnt->p3_z;

		rend_DrawLine(round(pnt->p3_sx-w),round(pnt->p3_sy-h),round(pnt->p3_sx+w),round(pnt->p3_sy-h));
		rend_DrawLine(round(pnt->p3_sx+w),round(pnt->p3_sy-h),round(pnt->p3_sx+w),round(pnt->p3_sy+h));
		rend_DrawLine(round(pnt->p3_sx+w),round(pnt->p3_sy+h),round(pnt->p3_sx-w),round(pnt->p3_sy+h));
		rend_DrawLine(round(pnt->p3_sx-w),round(pnt->p3_sy+h),round(pnt->p3_sx-w),round(pnt->p3_sy-h));
	}
}

// Sets the triangulation test to on or off
void g3_SetTriangulationTest (int state)
{
	Triangulate_test = state;
}

#endif
