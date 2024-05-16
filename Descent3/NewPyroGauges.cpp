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

 * $Logfile: /DescentIII/main/NewPyroGauges.cpp $
 * $Revision: 10 $
 * $Date: 4/17/99 6:15p $
 * $Author: Samir $
 *
 *	New Pyro GX Gauge rendering functions
 *
 * $Log: /DescentIII/main/NewPyroGauges.cpp $
 *
 * 10    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 9     12/29/97 5:44p Samir
 * Took out references to grViewport and old 2d library.
 *
 * 8     11/17/97 10:49a Samir
 * Fadeouts and Fadeins 90% working.
 *
 * 7     11/16/97 6:56p Samir
 * Started fade out system for weapon gauges.   Also put name of weapon in
 * box.
 *
 * 6     11/14/97 5:30p Samir
 * Now we get more information about the gauge's world position.
 *
 * 5     11/14/97 12:54p Samir
 * Bad shield ring gauge.
 *
 * 4     11/11/97 1:27p Samir
 * Weapon gauges partially working.   Still needs work.
 *
 * 3     11/04/97 7:27p Jason
 * made shield ring draw correctly
 *
 * 2     11/04/97 6:24p Samir
 * Semi functioning shield gauges.
 *
 * 1     10/30/97 3:27p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include "NewPyroGauges.h"
#include "gauges.h"
#include "gamefont.h"
#include "game.h"
#include "hud.h"
#include "grdefs.h"
#include "bitmap.h"
#include "player.h"
#include "polymodel.h"
#include "3d.h"
#include "renderer.h"
#include "gametexture.h"

//	how long it takes for a weapon gauge to fade out/in
#define GAUGE_WEAPON_FADE_TIME 1.0f

//////////////////////////////////////////////////////////////////////////////

static struct {
  int ringbmp;
} NewPyroGaugeData;

//////////////////////////////////////////////////////////////////////////////

static void GetCenterPoint(int *x, int *y, vector *wpos);

void NewPyroInitGauges() {
  int texhandle;
  texhandle = FindTextureName("GaugeShieldRing");
  if (texhandle == -1) {
    Int3(); // Samir.
    NewPyroGaugeData.ringbmp = -1;
    return;
  } else {
    NewPyroGaugeData.ringbmp = GetTextureBitmap(texhandle, 0);
  }
}

//////////////////////////////////////////////////////////////////////////////
//	Energy gauges

//	shield gauge handler
void NewPyroShieldGauge(tGauge *gauge, tGaugePos *pos) {
  //	we need to get the rectangular position in screen coords of the submodel for this gauge.
  //	find center point of face/polygon.
  //@@	int cx, cy,x,y;
  //@@	char str[8];
  //@@
  //@@	GetCenterPoint(&cx, &cy, &pos->center);

  //@@	START_TEXT_BLOCK_ALPHA(0.7f)
  //@@	{
  //@@		int text_spacing = parentvp->get_text_spacing();
  //@@		parentvp->set_font("small");
  //@@		parentvp->set_text_color(GR_RGB(255,128,128));
  //@@		parentvp->set_text_spacing(0);
  //@@		rend_SetCharacterParameters (parentvp->get_text_color(), parentvp->get_text_color(),
  // parentvp->get_text_color(), parentvp->get_text_color());
  //@@		sprintf(str, "%d", (int)Players[Player_num].shields);
  //@@		x = cx - (parentvp->get_text_line_width(str)/2);
  //@@		y = cy - (parentvp->get_current_font_height()/2);
  //@@		parentvp->printf(x,y,str);
  //@@		parentvp->set_text_spacing(text_spacing);
  //@@	}
  //@@	END_TEXT_BLOCK
}

#define NUM_SHIELD_SEGMENTS 36

float Zfactor = 2.0f;

//	ship status gauge
void NewPyroShipGauge(tGauge *gauge, tGaugePos *pos) {
  //	we should draw at least an octogonal polygon with the shield gauge texture.
  //@@	g3Point inner_points[NUM_SHIELD_SEGMENTS];
  //@@	g3Point outer_points[NUM_SHIELD_SEGMENTS];
  //@@	g3Point center_pnt;
  //@@	g3Point *pntlist[4];
  //@@	poly_model *pm = HudGetPolyModel();
  //@@	bsp_info *sm = &pm->submodel[gauge->submodel];
  //@@
  //@@	float lifenorm, outoffset, zdepth, zdiff;
  //@@	int ring_increment, ring_angle;
  //@@	int num_segs, i;
  //@@	int bmphandle = NewPyroGaugeData.ringbmp;
  //@@
  //@@//	determine depth of ring.
  //@@	lifenorm = Players[Player_num].shields/(float)INITIAL_SHIELDS;
  //@@	if (lifenorm > 1.0f) lifenorm = 1.0f;
  //@@	outoffset = 32.0f + (lifenorm * 16.0f);
  //@@
  //@@//	prepare renderer
  //@@	rend_SetLighting(LS_NONE);
  //@@	rend_SetTextureType (TT_LINEAR);
  //@@	rend_SetAlphaType (AT_CONSTANT+AT_TEXTURE);
  //@@	rend_SetAlphaValue (0.75f * 255);
  //@@	rend_SetZBufferState (0);
  //@@
  //@@//	do 3d stuff
  //@@	g3_RotatePoint (&center_pnt,&pos->center);
  //@@	g3_ProjectPoint (&center_pnt);
  //@@
  //@@	num_segs=NUM_SHIELD_SEGMENTS;
  //@@	ring_increment=65536/num_segs;
  //@@	ring_angle=0;
  //@@	zdiff = (sm->max.z - sm->min.z);
  //@@
  //@@	for (i=0;i<num_segs;i++,ring_angle+=ring_increment)
  //@@	{
  //@@		float ring_sin=FixSin(ring_angle);
  //@@		float ring_cos=FixCos(ring_angle);

  //@@//@@		inner_points[i].p3_x = center_pnt.p3_x + ring_cos*1.5;
  //@@//@@		inner_points[i].p3_y = center_pnt.p3_y + ring_sin*1.5;
  //@@//@@		inner_points[i].p3_z = center_pnt.p3_z + ring_sin*zdiff;
  //@@//@@		inner_points[i].p3_codes = 0;
  //@@//@@		inner_points[i].p3_flags = 0;
  //@@//@@		outer_points[i].p3_x = center_pnt.p3_x + ring_cos*(1.5f + lifenorm*1.5f);
  //@@//@@		outer_points[i].p3_y = center_pnt.p3_y + ring_sin*(1.5f + lifenorm*1.5f);
  //@@//@@		outer_points[i].p3_z = center_pnt.p3_z + ring_sin*zdiff;
  //@@//@@		outer_points[i].p3_codes = 0;
  //@@//@@		outer_points[i].p3_flags = 0;
  //@@//@@		g3_ProjectPoint(&inner_points[i]);
  //@@//@@		g3_ProjectPoint(&outer_points[i]);
  //@@//@@
  //@@//@@		inner_points[i].p3_z = 0;
  //@@//@@		outer_points[i].p3_z = 0;
  //@@
  //@@		zdepth = 1.0f - (ring_sin/zdiff);
  //@@
  //@@		inner_points[i].p3_sx=center_pnt.p3_sx + (ring_cos*32.0f)/zdepth;
  //@@		inner_points[i].p3_sy=center_pnt.p3_sy + (ring_sin*32.0f)/zdepth;
  //@@
  //@@		outer_points[i].p3_sx=center_pnt.p3_sx + (ring_cos*outoffset)/zdepth;
  //@@		outer_points[i].p3_sy=center_pnt.p3_sy + (ring_sin*outoffset)/zdepth;
  //@@
  //@@		inner_points[i].p3_z=0;
  //@@		outer_points[i].p3_z=0;
  //@@
  //@@		inner_points[i].p3_flags |=PF_PROJECTED;
  //@@		outer_points[i].p3_flags |=PF_PROJECTED;
  //@@
  //@@	}
  //@@
  //@@	for (i=0;i<num_segs;i++)
  //@@	{
  //@@		int next=(i+1)%num_segs;
  //@@
  //@@		outer_points[i].p3_u=0;
  //@@		outer_points[next].p3_u=1.0;
  //@@		outer_points[i].p3_v=0;
  //@@		outer_points[next].p3_v=0;
  //@@
  //@@		inner_points[i].p3_u=0;
  //@@		inner_points[next].p3_u=1.0;
  //@@		inner_points[i].p3_v=1;
  //@@		inner_points[next].p3_v=1;
  //@@
  //@@		pntlist[0]=&outer_points[i];
  //@@		pntlist[1]=&outer_points[next];
  //@@		pntlist[2]=&inner_points[next];
  //@@		pntlist[3]=&inner_points[i];
  //@@
  //@@		rend_DrawPolygon (bmphandle,pntlist,4);
  //@@	}
  //@@
  //@@	rend_SetZBufferState (1);
}

//////////////////////////////////////////////////////////////////////////////
//	Energy gauges

void NewPyroEnergyDigitalGauge(tGauge *gauge, tGaugePos *pos) {
  //	we need to get the rectangular position in screen coords of the submodel for this gauge.
  //	find center point of face/polygon.
  //@@	int cx, cy,x,y;
  //@@	char str[8];
  //@@
  //@@	GetCenterPoint(&cx, &cy, &pos->center);
  //@@
  //@@	START_TEXT_BLOCK_ALPHA(0.7f)
  //@@	{
  //@@		int text_spacing = parentvp->get_text_spacing();
  //@@		parentvp->set_font("small");
  //@@		parentvp->set_text_color(GR_RGB(192,192,128));
  //@@		parentvp->set_text_spacing(0);
  //@@		rend_SetCharacterParameters (parentvp->get_text_color(), parentvp->get_text_color(),
  // parentvp->get_text_color(), parentvp->get_text_color());
  //@@		sprintf(str, "%d", (int)Players[Player_num].energy);
  //@@		x = cx - (parentvp->get_text_line_width(str)/2);
  //@@		y = cy - (parentvp->get_current_font_height()/2);
  //@@		parentvp->printf(x,y,str);
  //@@		parentvp->set_text_spacing(text_spacing);
  //@@	}
  //@@	END_TEXT_BLOCK
}

void NewPyroEnergyAnalogGauge(tGauge *gauge, tGaugePos *pos) {}

//////////////////////////////////////////////////////////////////////////////
//	Weapon gauges

void NewPyroPrimaryWeaponGauge(tGauge *gauge, tGaugePos *pos) {
  //@@	static float fade_time = 0.0f;
  //@@	static int fade_state = 0;
  //@@	float gauge_alpha;
  //@@	poly_model *pm;
  //@@	bsp_info *sm;
  //@@
  //@@	pm = HudGetPolyModel();
  //@@	sm = &pm->submodel[gauge->submodel];
  //@@
  //@@//	first time initialization of gauge
  //@@	if (!gauge->init) {
  //@@		GameTextures[pm->textures[gauge->texindex]].bm_handle =
  //@@				Weapons[Players[Player_num].primary_weapon].hud_image_handle;
  //@@		fade_state = 0;
  //@@		return;
  //@@	}
  //@@
  //@@	gauge_alpha = 1.0f;
  //@@
  //@@//	handle starting fade in and fade out.
  //@@	if (gauge->modified) {
  //@@	//	alter texture of gauge submodel face 0 to param once faded out.
  //@@		fade_state = 1;						// go to fade out.
  //@@		gauge->modified = false;
  //@@		fade_time = 0.0f;
  //@@	}
  //@@
  //@@//	handle fade.
  //@@	if (fade_state == 1) {
  //@@	//	fade out.
  //@@		gauge_alpha = 1.0f - (fade_time/GAUGE_WEAPON_FADE_TIME);
  //@@		if (fade_time >= GAUGE_WEAPON_FADE_TIME) {
  //@@			GameTextures[pm->textures[gauge->texindex]].bm_handle =
  //@@				Weapons[Players[Player_num].primary_weapon].hud_image_handle;
  //@@			fade_time = 0.0f;
  //@@			fade_state = 2;					// advance to fade in
  //@@		}
  //@@		else
  //@@			fade_time += Frametime;
  //@@		GameTextures[pm->textures[gauge->texindex]].alpha = gauge_alpha;
  //@@	}
  //@@	else if (fade_state == 2) {
  //@@	//	fade in!
  //@@		gauge_alpha = (fade_time/GAUGE_WEAPON_FADE_TIME);
  //@@		if (fade_time >= GAUGE_WEAPON_FADE_TIME) {
  //@@			fade_time = 0.0f;
  //@@			fade_state = 0;					// null fade state
  //@@		}
  //@@		else
  //@@			fade_time += Frametime;
  //@@		GameTextures[pm->textures[gauge->texindex]].alpha = gauge_alpha;
  //@@	}
  //@@
  //@@//	do weapon name text.
  //@@	if (fade_state == 0) {
  //@@		int x,y,cx,cy;
  //@@		char str[PAGENAME_LEN];
  //@@		GetCenterPoint(&cx, &cy, &pos->center);
  //@@
  //@@		START_TEXT_BLOCK_ALPHA(gauge_alpha)
  //@@		{
  //@@			int text_spacing = parentvp->get_text_spacing();
  //@@			parentvp->set_font("small");
  //@@			parentvp->set_text_color(GR_RGB(0,192,0));
  //@@			parentvp->set_text_spacing(0);
  //@@			rend_SetCharacterParameters (parentvp->get_text_color(), parentvp->get_text_color(),
  // parentvp->get_text_color(), parentvp->get_text_color());
  //@@			sprintf(str, "%s", Weapons[Players[Player_num].primary_weapon].name);
  //@@			x = cx - (parentvp->get_text_line_width(str)/3);
  //@@			y = cy - (parentvp->get_current_font_height()/3);
  //@@			parentvp->printf(x,y,str);
  //@@			parentvp->set_text_spacing(text_spacing);
  //@@		}
  //@@		END_TEXT_BLOCK
  //@@		GameTextures[pm->textures[gauge->texindex]].alpha = gauge_alpha;
  //@@	}
}

void NewPyroSecondaryWeaponGauge(tGauge *gauge, tGaugePos *pos) {
  //@@	static float fade_time = 0.0f;
  //@@	static int fade_state = 0;
  //@@	float gauge_alpha;
  //@@	poly_model *pm;
  //@@	bsp_info *sm;
  //@@
  //@@	pm = HudGetPolyModel();
  //@@	sm = &pm->submodel[gauge->submodel];
  //@@
  //@@//	first time initialization of gauge
  //@@	if (!gauge->init) {
  //@@		GameTextures[pm->textures[gauge->texindex]].bm_handle =
  //@@				Weapons[Players[Player_num].secondary_weapon].hud_image_handle;
  //@@		fade_state = 0;
  //@@		return;
  //@@	}
  //@@
  //@@	gauge_alpha = 1.0f;
  //@@
  //@@//	handle starting fade in and fade out.
  //@@	if (gauge->modified) {
  //@@	//	alter texture of gauge submodel face 0 to param once faded out.
  //@@		fade_state = 1;						// go to fade out.
  //@@		gauge->modified = false;
  //@@		fade_time = 0.0f;
  //@@	}
  //@@
  //@@//	handle fade.
  //@@	if (fade_state == 1) {
  //@@	//	fade out.
  //@@		gauge_alpha = 1.0f - (fade_time/GAUGE_WEAPON_FADE_TIME);
  //@@		if (fade_time >= GAUGE_WEAPON_FADE_TIME) {
  //@@			GameTextures[pm->textures[gauge->texindex]].bm_handle =
  //@@				Weapons[Players[Player_num].secondary_weapon].hud_image_handle;
  //@@			fade_time = 0.0f;
  //@@			fade_state = 2;					// advance to fade in
  //@@		}
  //@@		else
  //@@			fade_time += Frametime;
  //@@		GameTextures[pm->textures[gauge->texindex]].alpha = gauge_alpha;
  //@@	}
  //@@	else if (fade_state == 2) {
  //@@	//	fade in!
  //@@		gauge_alpha = (fade_time/GAUGE_WEAPON_FADE_TIME);
  //@@		if (fade_time >= GAUGE_WEAPON_FADE_TIME) {
  //@@			fade_time = 0.0f;
  //@@			fade_state = 0;					// null fade state
  //@@		}
  //@@		else
  //@@			fade_time += Frametime;
  //@@		GameTextures[pm->textures[gauge->texindex]].alpha = gauge_alpha;
  //@@	}
  //@@
  //@@//	do weapon name text.
  //@@	if (fade_state == 0) {
  //@@		int x,y,cx,cy;
  //@@		char str[PAGENAME_LEN];
  //@@		GetCenterPoint(&cx, &cy, &pos->center);
  //@@
  //@@		START_TEXT_BLOCK_ALPHA(gauge_alpha)
  //@@		{
  //@@			int text_spacing = parentvp->get_text_spacing();
  //@@			parentvp->set_font("small");
  //@@			parentvp->set_text_color(GR_RGB(0,192,0));
  //@@			parentvp->set_text_spacing(0);
  //@@			rend_SetCharacterParameters (parentvp->get_text_color(), parentvp->get_text_color(),
  // parentvp->get_text_color(), parentvp->get_text_color());
  //@@			sprintf(str, "%s", Weapons[Players[Player_num].secondary_weapon].name);
  //@@			x = cx - (parentvp->get_text_line_width(str)/1.5f);
  //@@			y = cy - (parentvp->get_current_font_height()/3);
  //@@			parentvp->printf(x,y,str);
  //@@			parentvp->set_text_spacing(text_spacing);
  //@@		}
  //@@		END_TEXT_BLOCK
  //@@		GameTextures[pm->textures[gauge->texindex]].alpha = gauge_alpha;
  //@@	}
}

//////////////////////////////////////////////////////////////////////////////////////////

//	This function will return the center point of a flat face in global screen coordinates
void GetCenterPoint(int *x, int *y, vector *wpos) {
  g3Point pt;

  g3_RotatePoint(&pt, wpos);
  g3_ProjectPoint(&pt);

  *x = (int)pt.p3_sx;
  *y = (int)pt.p3_sy;
}
