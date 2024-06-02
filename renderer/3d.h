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

 * $Logfile: /DescentIII/Main/Lib/3d.h $
 * $Revision: 36 $
 * $Date: 10/21/99 9:27p $
 * $Author: Jeff $
 *
 * Header file for Descent 3 3d library
 *
 * $Log: /DescentIII/Main/Lib/3d.h $
 *
 * 36    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 35    5/13/99 10:57p Jason
 * added extra parameter to g3_DrawPoly
 *
 * 34    4/22/99 5:14p Matt
 * Changed the and & or fields in the grCodes struct to cc_and & cc_or,
 * since the former names didn't work with some compilers.
 *
 * 33    3/26/99 3:53p Jason
 * returned clip codes to their original order
 *
 * 32    3/26/99 3:25p Jason
 * fixed remaining mirror problems
 *
 * 31    2/19/99 4:26p Jason
 * more work on Katmai support
 *
 * 30    2/18/99 5:45p Jason
 * added custom clip plane
 *
 * 29    1/26/99 6:39p Jason
 * added wall effects code
 *
 * 28    5/25/98 3:45p Jason
 * made g3_DrawPoly return 1 if it drew
 *
 * 27    5/20/98 5:43p Jason
 * incremental checkin for bumpmapping
 *
 * 26    5/19/98 12:27p Jason
 * cleaned up some 3d stuff
 *
 * 25    5/14/98 12:56p Jason
 * changes to help lower memory usage
 *
 * 24    4/01/98 12:02p Jason
 * incremental checkin for rendering changes
 *
 * 23    2/05/98 11:14a Jason
 * added g3_DrawPlanarRotatedBitmap function
 *
 * 22    1/28/98 5:36p Jason
 * added streamer weapons
 *
 * 21    1/07/98 3:57p Jason
 * fixed spelling of triangulation (doh!)
 *
 * 20    1/07/98 3:55p Jason
 * made Triangulate test a user callable function
 *
 *
 * 19    12/29/97 5:49p Samir
 * 3d.h doesn't include gr.h anymore.
 *
 * 18    12/23/97 10:59a Samir
 * Temporarily put gr.h back in.
 *
 * 17    12/22/97 7:21p Samir
 * replaced ddvid.h with grdefs.h
 *
 * 16    12/22/97 6:57p Samir
 * Removed instances of gr.h
 *
 * 15    12/19/97 12:20p Jason
 * changes for better 2d/3d system integration
 *
 * 14    11/10/97 12:10p Jason
 * implemented g3_GetMatrixScale
 *
 * 13    10/22/97 4:18p Jason
 * added g3_DrawRotatedBitmap
 *
 * 12    10/17/97 5:09p Jason
 * added more fireball stuff
 *
 * 11    10/15/97 2:27p Jason
 * changes for prelim fireball stuff
 *
 * 10    10/13/97 3:56p Jason
 * made a better 3d bitmap system
 *
 * 9     9/16/97 4:23p Matt
 * Made ClipPolygon() a public function (g3_ClipPolygon()), and added
 * g3_FreeTempPoints().
 *
 * 8     9/10/97 3:50p Jason
 * added code for instancing the unscaled view matrix
 *
 * 7     9/04/97 11:59a Matt
 * Added new function  g3_ResetFarClipZ()
 *
 * 6     9/03/97 2:20p Samir
 * Added function to get viewer matrix.
 *
 * 5     9/02/97 11:07a Jason
 * added alpha component to uvl struct
 *
 * 4     8/20/97 4:17p Matt
 * Added g3_GetViewPosition()
 *
 * 3     8/04/97 6:40p Jason
 * added 2nd level UV floats for lightmaps
 *
 * 2     7/16/97 4:12p Matt
 * Changed and cleaned up a bunch of stuff:
 *
 * 1. Modified clipper to not change the order of the vertices
 * 2. Cleaned up drawer/clipper integration
 * 3. Renamed internal functions to conform to nameing standards
 * 4. Changed tmap drawer to not take list of uvls.  UVL values must now
 * be added to the points by the caller
 * 5. Renamed g3_DrawTmap() to g3_DrawPoly(), and killed the old
 * g3_DrawPoly()
 * 6. Made line always do 3d clip if they go offscreen
 *
 * 14    6/25/97 5:45p Matt
 * Made 3D draw functions void, to get rid of warnings about bool return
 * values that were never used anyway.
 *
 * 13    5/08/97 8:11p Matt
 * Added code to create subwindows that show a subsection of the 3d view
 *
 * 12    4/10/97 2:24p Jason
 * added the existance of a far clip plane.
 *
 * 11    4/01/97 5:17p Matt
 * Got g3_DrawSphere() working
 *
 * 10    2/28/97 10:43a Matt
 * Added g3_DrawBox() to draw a wireframe box (used to show the current
 * object in the editor).
 *
 * 9     2/27/97 5:01p Jason
 * added 3d model functionality and created model library
 *
 * 8     2/26/97 6:00p Matt
 * Renamed 3d lib structs for D3 naming convention
 *
 * 7     2/21/97 7:29p Matt
 * Added rgb fields to g3s_uvl struct
 *
 * 6     2/19/97 3:32p Matt
 * gr_DrawPoly() now takes the color
 *
 * 5     2/07/97 5:58p Matt
 * Took out now-obsolete jason_point struct
 * Renamed vector.h to vecmat.h
 *
 * $NoKeywords: $
 */

#ifndef _3D_H
#define _3D_H

#include "pstypes.h"
#include "vecmat.h" //the vector/matrix library
#include "grdefs.h"
#include "float.h"

extern int g3d_interp_outline; // if on, polygon models outlined in white

extern vector Matrix_scale; // how the matrix is currently scaled

// Structure for storing u,v,light values.  This structure doesn't have a
// prefix because it was defined somewhere else before it was moved here
struct g3UVL {
  // texture coordinates
  float u, v;
  float u2, v2;

  union {
    float l; // intensity lighting
    float r;
  };
  float g, b, a; // rgba lighting
};

// Structure to store clipping codes in a word
struct g3Codes {
  uint8_t cc_or, cc_and;
};

// flags for point structure
#define PF_PROJECTED 1  // has been projected, so sx,sy valid
#define PF_FAR_ALPHA 2  // past fog zone
#define PF_TEMP_POINT 4 // created during clip
#define PF_UV 8         // has uv values set
#define PF_L 16         // has lighting values set
#define PF_RGBA 32      // has RGBA lighting values set
#define PF_UV2 64       // has lightmap uvs as well
#define PF_ORIGPOINT 128

// clipping codes flags
#define CC_OFF_LEFT 1
#define CC_OFF_RIGHT 2
#define CC_OFF_BOT 4
#define CC_OFF_TOP 8
#define CC_OFF_FAR 16
#define CC_OFF_CUSTOM 32
#define CC_BEHIND 128

// Used to store rotated points for mines.  Has frame count to indicate
// if rotated, and flag to indicate if projected.
struct g3Point {
  float p3_sx, p3_sy;  // screen x&y
  uint8_t p3_codes;      // clipping codes
  uint8_t p3_flags;      // projected?
  int16_t p3_pad;        // keep structure longword aligned
  vector p3_vec;       // x,y,z of rotated point
  vector p3_vecPreRot; // original XYZ of the point
  g3UVL p3_uvl;        // uv & lighting values
};

// macros to reference x,y,z elements of a 3d point
#define p3_x p3_vec.x
#define p3_y p3_vec.y
#define p3_z p3_vec.z

// macros to reference individual elements of the uvls struct
#define p3_u p3_uvl.u
#define p3_v p3_uvl.v
#define p3_l p3_uvl.l
#define p3_r p3_uvl.r
#define p3_g p3_uvl.g
#define p3_b p3_uvl.b
#define p3_a p3_uvl.a
#define p3_u2 p3_uvl.u2
#define p3_v2 p3_uvl.v2

// Functions in library

// 3d system startup and shutdown:

// initialize the 3d system
void g3_Init(void);

// close down the 3d system
void g3_Close(void);

// Frame setup functions:

// start the frame, specifying view position, matrix, & zoom
void g3_StartFrame(vector *view_pos, matrix *view_matrix, float zoom);

// end the frame
void g3_EndFrame(void);

// get the current view position
void g3_GetViewPosition(vector *vp);

//	returns the current view matrix
void g3_GetViewMatrix(matrix *mat);

//	returns the current unscaled view matrix
void g3_GetUnscaledMatrix(matrix *mat);

// Instancing

// instance at specified point with specified orientation
void g3_StartInstanceMatrix(vector *pos, matrix *orient);

// instance at specified point with specified orientation
void g3_StartInstanceAngles(vector *pos, angvec *angles);

// pops the old context
void g3_DoneInstance();

// Misc utility functions:

// get current field of view.  Fills in angle for x & y
void g3_GetFOV(float *fov_x, float *fov_y);

// get zoom.  For a given window size, return the zoom which will achieve
// the given FOV along the given axis.
float g3_GetZoom(char axis, float fov, int16_t window_width, int16_t window_height);

// returns the normalized, unscaled view vectors
void g3_GetViewVectors(vector *forward, vector *up, vector *right);

// returns true if a plane is facing the viewer. takes the unrotated surface
// normal of the plane, and a point on it.  The normal need not be normalized
bool g3_CheckNormalFacing(vector *v, vector *norm);

// Point definition and rotation functions:

// returns codes_and & codes_or of a list of points numbers
g3Codes g3_CheckCodes(int nv, g3Point **pointlist);

// rotates a point. returns codes.  does not check if already rotated
uint8_t g3_RotatePoint(g3Point *dest, vector *src);

// projects a point
void g3_ProjectPoint(g3Point *point);

// calculate the depth of a point - returns the z coord of the rotated point
float g3_CalcPointDepth(vector *pnt);

// from a 2d point, compute the vector through that point
void g3_Point2Vec(vector *v, int16_t sx, int16_t sy);

// code a point.  fills in the p3_codes field of the point, and returns the codes
uint8_t g3_CodePoint(g3Point *point);

// delta rotation functions
vector *g3_RotateDeltaX(vector *dest, float dx);
vector *g3_RotateDeltaY(vector *dest, float dy);
vector *g3_RotateDeltaZ(vector *dest, float dz);
vector *g3_RotateDeltaVec(vector *dest, vector *src);
uint8_t g3_AddDeltaVec(g3Point *dest, g3Point *src, vector *deltav);

// Drawing functions:
// draw a polygon
// Parameters:	nv - the number of verts in the poly
//					pointlist - a pointer to a list of pointers to points
//					bm - the bitmap handle if texturing.  ignored if flat shading
int g3_DrawPoly(int nv, g3Point **pointlist, int bm, int map_type = 0, g3Codes *clip_codes = NULL);

// draw a sortof sphere - i.e., the 2d radius is proportional to the 3d
// radius, but not to the distance from the eye
void g3_DrawSphere(ddgr_color color, g3Point *pnt, float rad);

// like g3_DrawPoly(), but checks to see if facing.  If surface normal is
// NULL, this routine must compute it, which will be slow.  It is better to
// pre-compute the normal, and pass it to this function.  When the normal
// is passed, this function works like g3_CheckNormalFacing() plus
// g3_DrawPoly().
void g3_CheckAndDrawPoly(int nv, g3Point **pointlist, int bm, vector *norm, vector *pnt);

// draws a line. takes two points.
void g3_DrawLine(ddgr_color color, g3Point *p0, g3Point *p1);

// draws a bitmap with the specified 3d width & height
// returns 1 if off screen, 0 if drew
void g3_DrawBitmap(vector *pos, float width, float height, int bm, int color = -1);

// Draws a bitmap that has been rotated about its center.  Angle of rotation is passed as 'rot_angle'
void g3_DrawRotatedBitmap(vector *pos, angle rot_angle, float width, float height, int bm, int color = -1);

// specifies 2d drawing routines to use instead of defaults.  Passing
// NULL for either or both restores defaults
void g3_SetSpecialRender(void (*tmap_drawer)(), void (*flat_drawer)(), int (*line_drawer)());

// Object functions:

// init code for bitmap models
void g3_InitPolygonModel(void *model_ptr);

// un-initialize, i.e., convert color entries back to RGB15
void g3_UninitPolygonModel(void *model_ptr);

// alternate interpreter for morphing object
void g3_DrawMorphingModel(void *model_ptr, int *model_bitmaps, angvec *anim_angles, float light, vector *new_points);

// this remaps the 15bpp colors for the models into a new palette.  It should
// be called whenever the palette changes
void g3_RemapInterpColors(void);

// Draw a wireframe box aligned with the screen.  Used for the editor.
// Parameters:	color - the color to draw the lines
//					pnt - the center point
//					rad - specifies the width/2 & height/2 of the box
void g3_DrawBox(ddgr_color color, g3Point *pnt, float rad);

// Sets up a custom clipping plane - g3_StartFrame must be called before this is called
void g3_SetCustomClipPlane(uint8_t state, vector *pnt, vector *normal);

// sets the z distance of the far clipping plane
void g3_SetFarClipZ(float z);

// Disables the far clip plane
static inline void g3_ResetFarClipZ() { g3_SetFarClipZ(FLT_MAX); }

// Clips a polygon
// Parameters:	pointlist - pointer to a list of pointers to points
//					nv - the number of points in the polygon
//					cc - the clip codes for this polygon
// Returns:	a pointer to a list of pointer of points in the clipped polygon
// NOTE: You MUST call g3_FreeTempPoints() when you're done with the clipped polygon
g3Point **g3_ClipPolygon(g3Point **pointlist, int *nv, g3Codes *cc);

// Free up any temp points (created by the clipper) in the given pointlist
// Parameters:	pointlist - pointer to list of pointers to points, returned by g3_ClipPolygon()
//					nv - the number of points in pointlist
void g3_FreeTempPoints(g3Point **pointlist, int nv);

// Gets the matrix scale vector
void g3_GetMatrixScale(vector *matrix_scale);

// Sets the triangulation test to on or off
void g3_SetTriangulationTest(int state);

// draws a line based on the current setting of render states. takes two points.  returns true if drew
void g3_DrawSpecialLine(g3Point *p0, g3Point *p1);

// Draws a bitmap on a specific plane.  Also does rotation.  Angle of rotation is passed as 'rot_angle'
void g3_DrawPlanarRotatedBitmap(vector *pos, vector *norm, angle rot_angle, float width, float height, int bm);

void g3_TransformVert(float res[4], float pt[4], float a[4][4]);
void g3_TransformMult(float res[4][4], float a[4][4], float b[4][4]);
void g3_TransformTrans(float res[4][4], float t[4][4]);
void g3_GetModelViewMatrix(const vector *viewPos, const matrix *viewMatrix, float *mvMat);
extern float gTransformViewPort[4][4];
extern float gTransformProjection[4][4];
extern float gTransformModelView[4][4];
extern float gTransformFull[4][4];

void g3_RefreshTransforms(bool usePassthru);

#endif
