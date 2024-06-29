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
#include "pserror.h"
#include "3d.h"
#include "HardwareInternal.h"

static int free_point_num = -1;
static g3Point temp_points[MAX_POINTS_IN_POLY];
static g3Point *free_points[MAX_POINTS_IN_POLY];
vector Clip_plane_point;

void InitFreePoints(void)
{
	int i;

	for( i = 0; i < MAX_POINTS_IN_POLY; i++ )
	{
		free_points[i] = &temp_points[i];
	}
	free_point_num = 0;
}

g3Point *GetTempPoint(void)
{
	ASSERT(free_point_num < MAX_POINTS_IN_POLY);

	g3Point *p = free_points[ free_point_num++ ];
	p->p3_flags = PF_TEMP_POINT;
	return p;
}

void FreeTempPoint(g3Point *p)
{
	if( free_point_num < 1 )
	{
		mprintf((1,"clipper: no temp points to free\n"));
		free_point_num = 1;
		Int3();
	}
	ASSERT( p->p3_flags & PF_TEMP_POINT );

	free_points[ --free_point_num ] = p;

	p->p3_flags &= ~PF_TEMP_POINT;
}

//Verify that all the temp points are free, and free them it they are not.
#ifdef _DEBUG
void CheckTempPoints(void)
{
	if( free_point_num )
	{
		Int3();
		InitFreePoints();
	}
}
#endif

//Free up any temp points (created by the clipper) in the given pointlist
//Parameters:	pointlist - pointer to list of pointers to points, returned by g3_ClipPolygon()
//				nv - the number of points in pointlist
void g3_FreeTempPoints( g3Point **pointlist, int nv )
{
	// Go through list
	int i;
	for( i = 0; i < nv; i++ )
	{
		if( pointlist[i]->p3_flags & PF_TEMP_POINT )
		{
			FreeTempPoint( pointlist[i] );
		}
	}

	// Make sure all temp points are freed
	CheckTempPoints();
}

// Clips an edge against the far plane
g3Point *ClipFarEdge( g3Point *on_pnt, g3Point *off_pnt )
{
	float z_on  = on_pnt->p3_z;
	float z_off = off_pnt->p3_z;

	float k = 1.0f - ((z_off-Far_clip_z) / (z_off-z_on));

	g3Point *tmp = GetTempPoint();
	tmp->p3_z = on_pnt->p3_z + ((off_pnt->p3_z-on_pnt->p3_z) * k);
	tmp->p3_x = on_pnt->p3_x + ((off_pnt->p3_x-on_pnt->p3_x) * k);
	tmp->p3_y = on_pnt->p3_y + ((off_pnt->p3_y-on_pnt->p3_y) * k);

	if (on_pnt->p3_flags & PF_UV)
	{
		tmp->p3_u = on_pnt->p3_u + ((off_pnt->p3_u-on_pnt->p3_u) * k);
		tmp->p3_v = on_pnt->p3_v + ((off_pnt->p3_v-on_pnt->p3_v) * k);
		tmp->p3_flags |= PF_UV;
	}

	if (on_pnt->p3_flags & PF_UV2)
	{
		tmp->p3_u2 = on_pnt->p3_u2 + ((off_pnt->p3_u2-on_pnt->p3_u2) * k);
		tmp->p3_v2 = on_pnt->p3_v2 + ((off_pnt->p3_v2-on_pnt->p3_v2) * k);
		tmp->p3_flags |= PF_UV2;
	}

	if (on_pnt->p3_flags & PF_L)
	{
		tmp->p3_l = on_pnt->p3_l + ((off_pnt->p3_l-on_pnt->p3_l) * k);
		tmp->p3_flags |= PF_L;
	}

	if (on_pnt->p3_flags & PF_RGBA)
	{
		tmp->p3_r = on_pnt->p3_r + ((off_pnt->p3_r-on_pnt->p3_r) * k);
		tmp->p3_g = on_pnt->p3_g + ((off_pnt->p3_g-on_pnt->p3_g) * k);
		tmp->p3_b = on_pnt->p3_b + ((off_pnt->p3_b-on_pnt->p3_b) * k);
		tmp->p3_a = on_pnt->p3_a + ((off_pnt->p3_a-on_pnt->p3_a) * k);
		tmp->p3_flags |= PF_RGBA;
	}

	g3_CodePoint(tmp);
	return tmp;
}

// Clips an edge against the far plane
g3Point *ClipCustomEdge( g3Point *on_pnt, g3Point *off_pnt )
{
	g3Point *tmp = GetTempPoint();

	vector ray_direction = off_pnt->p3_vec - on_pnt->p3_vec;
	ray_direction.x /= Matrix_scale.x;
	ray_direction.y /= Matrix_scale.y;
	ray_direction.z /= Matrix_scale.z;

	vector w = on_pnt->p3_vec - Clip_plane_point;
	w.x /= Matrix_scale.x;
	w.y /= Matrix_scale.y;
	w.z /= Matrix_scale.z;

	float k, den = -(Clip_plane * ray_direction);
	if( den == 0.0f )
	{
		k = 1.0f;
	}
	else 
	{
		float num =  Clip_plane * w;
		k = num / den;
	}

	tmp->p3_vec = on_pnt->p3_vec + ((off_pnt->p3_vec-on_pnt->p3_vec) * k);

	if (on_pnt->p3_flags & PF_UV)
	{
		tmp->p3_u = on_pnt->p3_u + ((off_pnt->p3_u-on_pnt->p3_u) * k);
		tmp->p3_v = on_pnt->p3_v + ((off_pnt->p3_v-on_pnt->p3_v) * k);
		tmp->p3_flags |= PF_UV;
	}

	if (on_pnt->p3_flags & PF_UV2)
	{
		tmp->p3_u2 = on_pnt->p3_u2 + ((off_pnt->p3_u2-on_pnt->p3_u2) * k);
		tmp->p3_v2 = on_pnt->p3_v2 + ((off_pnt->p3_v2-on_pnt->p3_v2) * k);
		tmp->p3_flags |= PF_UV2;
	}

	if (on_pnt->p3_flags & PF_L)
	{
		tmp->p3_l = on_pnt->p3_l + ((off_pnt->p3_l-on_pnt->p3_l) * k);
		tmp->p3_flags |= PF_L;
	}

	if (on_pnt->p3_flags & PF_RGBA)
	{
		tmp->p3_r = on_pnt->p3_r + ((off_pnt->p3_r-on_pnt->p3_r) * k);
		tmp->p3_g = on_pnt->p3_g + ((off_pnt->p3_g-on_pnt->p3_g) * k);
		tmp->p3_b = on_pnt->p3_b + ((off_pnt->p3_b-on_pnt->p3_b) * k);
		tmp->p3_a = on_pnt->p3_a + ((off_pnt->p3_a-on_pnt->p3_a) * k);
		tmp->p3_flags |= PF_RGBA;
	}

	g3_CodePoint(tmp);
	return tmp;
}

//clips an edge against one plane. 
g3Point *ClipEdge( int plane_flag, g3Point *on_pnt, g3Point *off_pnt )
{
	float a,b,k;
	g3Point *tmp;

	//compute clipping value k = (xs-zs) / (xs-xe-zs+ze)
	//use x or y as appropriate, and negate x/y value as appropriate

	if (plane_flag & CC_OFF_FAR)
	{
		return ClipFarEdge (on_pnt,off_pnt);
	}

	if ((plane_flag & CC_OFF_CUSTOM) && Clip_custom)
	{
		return ClipCustomEdge (on_pnt,off_pnt);
	}

	if (plane_flag & (CC_OFF_RIGHT | CC_OFF_LEFT))
	{
		a = on_pnt->p3_x;
		b = off_pnt->p3_x;
	}
	else
	{
		a = on_pnt->p3_y;
		b = off_pnt->p3_y;
	}

	if (plane_flag & (CC_OFF_LEFT | CC_OFF_BOT))
	{
		a = -a;
		b = -b;
	}

	k = (a - on_pnt->p3_z) / ((a - on_pnt->p3_z) - b + off_pnt->p3_z);	//(xs-zs) / (xs-zs-xe+ze)

	tmp = GetTempPoint();

	tmp->p3_x = on_pnt->p3_x + ((off_pnt->p3_x-on_pnt->p3_x) * k);
	tmp->p3_y = on_pnt->p3_y + ((off_pnt->p3_y-on_pnt->p3_y) * k);

	if (plane_flag & (CC_OFF_TOP|CC_OFF_BOT))
	{
		tmp->p3_z = tmp->p3_y;
	}
	else
	{
		tmp->p3_z = tmp->p3_x;
	}

	if (plane_flag & (CC_OFF_LEFT|CC_OFF_BOT))
	{
		tmp->p3_z = -tmp->p3_z;
	}

	if (on_pnt->p3_flags & PF_UV)
	{
		tmp->p3_u = on_pnt->p3_u + ((off_pnt->p3_u-on_pnt->p3_u) * k);
		tmp->p3_v = on_pnt->p3_v + ((off_pnt->p3_v-on_pnt->p3_v) * k);

		tmp->p3_flags |= PF_UV;
	}

	if (on_pnt->p3_flags & PF_UV2)
	{
		tmp->p3_u2 = on_pnt->p3_u2 + ((off_pnt->p3_u2-on_pnt->p3_u2) * k);
		tmp->p3_v2 = on_pnt->p3_v2 + ((off_pnt->p3_v2-on_pnt->p3_v2) * k);

		tmp->p3_flags |= PF_UV2;
	}

	if (on_pnt->p3_flags & PF_L)
	{
		tmp->p3_l = on_pnt->p3_l + ((off_pnt->p3_l-on_pnt->p3_l) * k);
		tmp->p3_flags |= PF_L;
	}

	if (on_pnt->p3_flags & PF_RGBA)
	{
		tmp->p3_r = on_pnt->p3_r + ((off_pnt->p3_r-on_pnt->p3_r) * k);
		tmp->p3_g = on_pnt->p3_g + ((off_pnt->p3_g-on_pnt->p3_g) * k);
		tmp->p3_b = on_pnt->p3_b + ((off_pnt->p3_b-on_pnt->p3_b) * k);
		tmp->p3_a = on_pnt->p3_a + ((off_pnt->p3_a-on_pnt->p3_a) * k);
		tmp->p3_flags |= PF_RGBA;
	}

	g3_CodePoint(tmp);

	return tmp;	
}

//clips a line to the viewing pyramid.
void ClipLine(g3Point **p0,g3Point **p1,uint8_t codes_or)
{
	int plane_flag;
	g3Point *old_p1;

	//might have these left over
	//(*p0)->p3_flags &= ~(PF_UV|PF_L|PF_RGBA|PF_UV2);
	//(*p1)->p3_flags &= ~(PF_UV|PF_L|PF_RGBA|PF_UV2);

	for (plane_flag=1;plane_flag<=32;plane_flag<<=1)
	{
		if (codes_or & plane_flag)
		{
			if ((*p0)->p3_codes & plane_flag)
			{
				//swap!
				g3Point *t=*p0;
				*p0=*p1;
				*p1=t;
			}

			old_p1 = *p1;

			*p1 = ClipEdge(plane_flag,*p0,*p1);

			codes_or = (*p0)->p3_codes | (*p1)->p3_codes;	//get new codes

			if (old_p1->p3_flags & PF_TEMP_POINT)
			{
				FreeTempPoint(old_p1);
			}
		}
	}
}

int ClipPlane(int plane_flag,g3Point **src,g3Point **dest,int *nv,g3Codes *cc)
{
	int i,prev,next;
	g3Point **save_dest=dest;

	//Init codes
	cc->cc_and = 0xff; cc->cc_or = 0;

	for (i=0,prev=*nv-1,next=1;i<*nv;i++)
	{
		if (src[i]->p3_codes & plane_flag)
		{
			//cur point off?
			if (! (src[prev]->p3_codes & plane_flag))
			{
				//prev not off?
				*dest = ClipEdge(plane_flag,src[prev],src[i]);
				cc->cc_or  |= (*dest)->p3_codes;
				cc->cc_and &= (*dest)->p3_codes;
				dest++;
			}

			if (! (src[next]->p3_codes & plane_flag))
			{
				*dest = ClipEdge(plane_flag,src[next],src[i]);
				cc->cc_or  |= (*dest)->p3_codes;
				cc->cc_and &= (*dest)->p3_codes;
				dest++;
			}

			//see if must free discarded point
			if (src[i]->p3_flags & PF_TEMP_POINT)
			{
				FreeTempPoint(src[i]);
			}
		}
		else
		{
			//cur not off, copy to dest buffer
			*dest++ = src[i];

			cc->cc_or  |= src[i]->p3_codes;
			cc->cc_and &= src[i]->p3_codes;
		}

		prev = i;
		if (++next == *nv)
		{
			next = 0;
		}
	}

	return (dest-save_dest);
}

//temp buffers for clipping
static g3Point *Vbuf0[MAX_POINTS_IN_POLY];
static g3Point *Vbuf1[MAX_POINTS_IN_POLY];

//Clips a polygon
//Parameters:	pointlist - pointer to a list of pointers to points
//					nv - the number of points in the polygon
//					cc - the clip codes for this polygon
//Returns:	a pointer to a list of pointer of points in the clipped polygon
//NOTE: You MUST call g3_FreeTempPoints() when you're done with the clipped polygon
g3Point **g3_ClipPolygon(g3Point **pointlist,int *nv,g3Codes *cc)
{
	int plane_flag;
	g3Point **dest;

	dest = Vbuf0;

	//&	ASSERT(free_point_num == 0);	//DAJ UTB CMO
	if(free_point_num!=0){
		mprintf((1,"clipper: leftover temp point\n"));
		free_point_num = 0;
		Int3();
	}

	for (plane_flag=1;plane_flag<=32;plane_flag<<=1)
	{
		if (cc->cc_or & plane_flag)
		{

			*nv = ClipPlane(plane_flag,pointlist,dest,nv,cc);

			if (cc->cc_and)		//clipped away
				return dest;

			pointlist = dest;
			dest = (pointlist == Vbuf0) ? Vbuf1 : Vbuf0;
		}
	}
	return pointlist;		//we swapped after we copied
}


// sets the z distance of the far clipping plane
void g3_SetFarClipZ(float z)
{
	Far_clip_z = z;
}

// Sets up a custom clipping plane - g3_StartFrame must be called before this is called
void g3_SetCustomClipPlane(uint8_t state,vector *pnt,vector *normal)
{
	Clip_custom=state;
	if (state)
	{
		vector tempv;
		vector norm=*normal;

		tempv = *pnt - View_position;
		Clip_plane_point = tempv * View_matrix;

		Clip_plane=norm * Unscaled_matrix;//View_matrix;
		vm_NormalizeVector(&Clip_plane);
	}
}
