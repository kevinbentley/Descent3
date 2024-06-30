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

/*******************************************************************

 * THIS HEADER HAS BEEN HACKED BY AN EXPERIMENTAL PERL SCRIPT

 * dynafy.pl

 * on 7 Jul 97

 *

 * The new functionality allows glide2x.dll to be loaded dynamically.

 * To do this,

 * 1. #define DYNAHEADER wherever you include this header,

 *    glide.h.


 * 2. You must also #define DYNAHEADER _CREATE_STORAGE in your

 *    file where main() is defined.

 * 3. call GetProcAddresses();

 */

/*

** Copyright (c) 1995, 3Dfx Interactive, Inc.

** All Rights Reserved.

**

** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;

** the contents of this file may not be disclosed to third parties, copied or

** duplicated in any form, in whole or in part, without the prior written

** permission of 3Dfx Interactive, Inc.

**

** RESTRICTED RIGHTS LEGEND:

** Use, duplication or disclosure by the Government is subject to restrictions

** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data

** and Computer Software clause at DFARS 252.227-7013, and/or in similar or

** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -

** rights reserved under the Copyright Laws of the United States.

*/

/*

** GLIDE.H

**

** The following #defines are relevant when using Glide:

**

** One of the following "platform constants" must be defined during

** compilation:

**

**            __DOS__           Defined for 32-bit DOS applications

**            __WIN32__         Defined for 32-bit Windows applications

**            __sparc__         Defined for Sun Solaris/SunOS

**            __linux__         Defined for Linux applications

**            __IRIX__          Defined for SGI Irix applications

**

*/

#ifndef __GLIDE_H__

#define __GLIDE_H__

/* The following include has been replaced

 * by the processed text from the header file.

 * #include <3dfx.h>

 */

/*

** Copyright (c) 1995, 3Dfx Interactive, Inc.

** All Rights Reserved.

**

** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;

** the contents of this file may not be disclosed to third parties, copied or

** duplicated in any form, in whole or in part, without the prior written

** permission of 3Dfx Interactive, Inc.

**

** RESTRICTED RIGHTS LEGEND:

** Use, duplication or disclosure by the Government is subject to restrictions

** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data

** and Computer Software clause at DFARS 252.227-7013, and/or in similar or

** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished  -

** rights reserved under the Copyright Laws of the United States.

**

** $Revision: 1.1.1.1 $

** $Date: 2003/08/26 03:58:12 $

*/

#ifndef __3DFX_H__

#define __3DFX_H__

/*

** basic data types

*/

#include <cstdint>

typedef uint8_t FxU8;

typedef int8_t FxI8;

typedef uint16_t FxU16;

typedef int16_t FxI16;

typedef int32_t FxI32;

typedef uint32_t FxU32;

typedef int FxBool;

typedef float FxFloat;

typedef double FxDouble;

/*

** color types

*/

typedef uint32_t FxColor_t;

struct FxColor4 {
  float r, g, b, a;
};

/*

** fundamental types

*/

#define FXTRUE 1

#define FXFALSE 0

/*

** helper macros

*/

#define FXUNUSED(a) ((a) = (a))

#define FXBIT(i) (1L << (i))

/*

** export macros

*/

#if defined(__MSC__) || defined(__WATCOMC__)

#define FX_ENTRY extern

#define FX_CALL __stdcall

#if defined(MSVC16)

#undef FX_ENTRY

#undef FX_CALL

#define FX_ENTRY

#define FX_CALL

#endif

#elif defined(__DJGPP__)

#define FX_ENTRY extern

#define FX_CALL

#elif defined(__unix__)

#define FX_ENTRY extern

#define FX_CALL

#else

#warning define FX_ENTRY & FX_CALL for your compiler

#define FX_ENTRY extern

#define FX_CALL

#endif

/*

** x86 compiler specific stuff

*/

#if defined(__BORLANDC_)

#define REALMODE

#define REGW(a, b) ((a).x.b)

#define REGB(a, b) ((a).h.b)

#define INT86(a, b, c) int86(a, b, c)

#define INT86X(a, b, c, d) int86x(a, b, c, d)

#define RM_SEG(a) FP_SEG(a)

#define RM_OFF(a) FP_OFF(a)

#elif defined(__WATCOMC__)

#undef FP_SEG

#undef FP_OFF

#define REGW(a, b) ((a).w.b)

#define REGB(a, b) ((a).h.b)

#define INT86(a, b, c) int386(a, b, c)

#define INT86X(a, b, c, d) int386x(a, b, c, d)

#define RM_SEG(a) ((((FxU32)(a)) & 0x000F0000) >> 4)

#define RM_OFF(a) ((FxU16)(a))

#endif

#endif

/* The following include has been replaced

 * by the processed text from the header file.

 * #include <sst1vid.h>

 */

/*

** Copyright (c) 1995, 3Dfx Interactive, Inc.

** All Rights Reserved.

**

** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;

** the contents of this file may not be disclosed to third parties, copied or

** duplicated in any form, in whole or in part, without the prior written

** permission of 3Dfx Interactive, Inc.

**

** RESTRICTED RIGHTS LEGEND:

** Use, duplication or disclosure by the Government is subject to restrictions

** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data

** and Computer Software clause at DFARS 252.227-7013, and/or in similar or

** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -

** rights reserved under the Copyright Laws of the United States.

**

** $Header: /cvs/kevlar.net/descent3/Main/lib/linux/dyna_glide.h,v 1.1.1.1 2003/08/26 03:58:12 kevinb Exp $

** $Log: dyna_glide.h,v $
** Revision 1.1.1.1  2003/08/26 03:58:12  kevinb
** initial 1.5 import
**
 *
 * 2     7/14/99 6:43p Jeff
 * change to load module globally
 *
 * 1     6/22/99 7:02p Jeff
 *
 * 4     2/19/99 11:49a Jason
 * added more resolutions to glide
 *
 * 3     7/06/98 7:16p Jeff
 * LoadGlideDLL no longer windows specific, calls module library
 *
 * 3     7/06/98 10:46a Jeff
 * LoadGlideDLL uses the module library so it isn't Windows specific
 *
 * 2     3/02/98 5:15p Jason
 * added support for dynamically loadable dlls
 *
 * 1     3/02/98 5:15p Jason
 * header file for dynamically loadable dlls

 *

 * 5     7/24/96 3:43p Sellers

 * added 512x384 @ 60 Hz for arcade monitors

 * added 512x256 @ 60 Hz for arcade monitors

 *

 * 4     7/18/96 10:58a Sellers

 * fixed FT and TF clock delay values for lower frequencies with

 * .5/.5 combos

 *

 * 3     6/18/96 6:54p Sellers

 * added sst1InitShutdownSli() to fix Glide Splash screen problems with

 * SLI

 *

 * 2     6/13/96 7:45p Sellers

 * added "voodoo.ini" support

 * added DirectX support

 * misc cleanup

 *

 * 2     6/11/96 1:43p Sellers

 * added support for 60, 75, 85, and 120 Hz refresh rates for "most"

 * resolutions

 *

 * 1     5/08/96 5:43p Paik

 * Video definitions

*/

#ifndef __SST1VID_H__

#define __SST1VID_H__

#ifdef __cplusplus

extern "C" {

#endif

/* Video defines */

typedef FxI32 GrScreenRefresh_t;

#define GR_REFRESH_60Hz         0x00
#define GR_REFRESH_70Hz         0x01
#define GR_REFRESH_72Hz         0x02
#define GR_REFRESH_75Hz         0x03
#define GR_REFRESH_80Hz         0x04
#define GR_REFRESH_90Hz         0x05
#define GR_REFRESH_100Hz        0x06
#define GR_REFRESH_85Hz         0x07
#define GR_REFRESH_120Hz        0x08
#define GR_REFRESH_NONE         0xFF

typedef FxI32 GrScreenResolution_t;

#define GR_RESOLUTION_320x200   0x00
#define GR_RESOLUTION_320x240   0x01
#define GR_RESOLUTION_400x256   0x02
#define GR_RESOLUTION_512x384   0x03
#define GR_RESOLUTION_640x200   0x04
#define GR_RESOLUTION_640x350   0x05
#define GR_RESOLUTION_640x400   0x06
#define GR_RESOLUTION_640x480   0x07
#define GR_RESOLUTION_800x600   0x08
#define GR_RESOLUTION_960x720   0x09
#define GR_RESOLUTION_856x480   0x0A
#define GR_RESOLUTION_512x256   0x0B    /* Glide.dll */
#define GR_RESOLUTION_1024x768  0x0C
#define GR_RESOLUTION_1280x1024 0x0D
#define GR_RESOLUTION_1600x1200 0x0E
#define GR_RESOLUTION_400x300   0x0F    /* Glide2x All voodoos */
#define GR_RESOLUTION_1152x864  0x10
#define GR_RESOLUTION_1280x960  0x11
#define GR_RESOLUTION_1600x1024 0x12
#define GR_RESOLUTION_1792x1344 0x13
#define GR_RESOLUTION_1856x1392 0x14
#define GR_RESOLUTION_1920x1440 0x15
#define GR_RESOLUTION_2048x1536 0x16
#define GR_RESOLUTION_2048x2048 0x17    /* Glide3x Vsa based voodoos, previous max */
/* Extended */
#define GR_RESOLUTION_1280x720  0x18	/* 16:9 */
#define GR_RESOLUTION_1280x800  0x19 	/* 16:10 */
#define GR_RESOLUTION_1360x768  0x1A	/* 16:9 */
#define GR_RESOLUTION_1440x900  0x1B 	/* 16:10 */
#define GR_RESOLUTION_1600x900 	0x1C	/* 16:9 */
#define GR_RESOLUTION_1680x720 	0x1D	/* 21:9 */
#define GR_RESOLUTION_1680x1050 0x1E 	/* 16:10 */
#define GR_RESOLUTION_1792x768 	0x1F	/* 21:9 */
#define GR_RESOLUTION_1920x800 	0x20	/* 21:9 */
#define GR_RESOLUTION_1920x1080 0x21	/* 16:9 */
#define GR_RESOLUTION_1920x1200 0x22	/* 16:10 */
#define GR_RESOLUTION_3840x2160 0x23	/* just for a high max, still invalid */
#define GR_RESOLUTION_NONE      0xFF

#ifdef __cplusplus
}

#endif

#endif /* __SST1VID_H__ */

/* The following include has been replaced

 * by the processed text from the header file.

 * #include <glidesys.h>

 */

/*

** Copyright (c) 1995, 3Dfx Interactive, Inc.

** All Rights Reserved.

**

** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;

** the contents of this file may not be disclosed to third parties, copied or

** duplicated in any form, in whole or in part, without the prior written

** permission of 3Dfx Interactive, Inc.

**

** RESTRICTED RIGHTS LEGEND:

** Use, duplication or disclosure by the Government is subject to restrictions

n** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data

** and Computer Software clause at DFARS 252.227-7013, and/or in similar or

** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -

** rights reserved under the Copyright Laws of the United States.

**

** $Header: /cvs/kevlar.net/descent3/Main/lib/linux/dyna_glide.h,v 1.1.1.1 2003/08/26 03:58:12 kevinb Exp $

** $Log: dyna_glide.h,v $
** Revision 1.1.1.1  2003/08/26 03:58:12  kevinb
** initial 1.5 import
**
 *
 * 2     7/14/99 6:43p Jeff
 * change to load module globally
 *
 * 1     6/22/99 7:02p Jeff
 *
 * 4     2/19/99 11:49a Jason
 * added more resolutions to glide
 *
 * 3     7/06/98 7:16p Jeff
 * LoadGlideDLL no longer windows specific, calls module library
 *
 * 3     7/06/98 10:46a Jeff
 * LoadGlideDLL uses the module library so it isn't Windows specific
 *
 * 2     3/02/98 5:15p Jason
 * added support for dynamically loadable dlls
 *
 * 1     3/02/98 5:15p Jason
 * header file for dynamically loadable dlls

*/

#ifndef __GLIDESYS_H__

#define __GLIDESYS_H__

/*

n** -----------------------------------------------------------------------

** COMPILER/ENVIRONMENT CONFIGURATION

** -----------------------------------------------------------------------

*/

/* Endianness is stored in bits [30:31] */

#define GLIDE_ENDIAN_SHIFT 30

#define GLIDE_ENDIAN_LITTLE (0x1 << GLIDE_ENDIAN_SHIFT)

#define GLIDE_ENDIAN_BIG (0x2 << GLIDE_ENDIAN_SHIFT)

/* OS is stored in bits [0:6] */

#define GLIDE_OS_SHIFT 0

#define GLIDE_OS_UNIX 0x1

#define GLIDE_OS_DOS32 0x2

#define GLIDE_OS_WIN32 0x4

#define GLIDE_OS_SYSTEM7 0x8

#define GLIDE_OS_OS2 0x10

#define GLIDE_OS_OTHER 0x20 /* For Proprietary Arcade HW */

/* Sim vs. Hardware is stored in bits [7:8] */

#define GLIDE_SST_SHIFT 7

#define GLIDE_SST_SIM (0x1 << GLIDE_SST_SHIFT)

#define GLIDE_SST_HW (0x2 << GLIDE_SST_SHIFT)

/* Hardware Type is stored in bits [9:12] */

#define GLIDE_HW_SHIFT 9

#define GLIDE_HW_SST1 (0x1 << GLIDE_HW_SHIFT)

#define GLIDE_HW_SST96 (0x2 << GLIDE_HW_SHIFT)

#define GLIDE_HW_SSTH3 (0x4 << GLIDE_HW_SHIFT)

#define GLIDE_HW_SST2 (0x8 << GLIDE_HW_SHIFT)

/*

** Make sure we handle all instances of WIN32

*/

#ifndef __WIN32__

#if defined(_WIN32) || defined(WIN32) || defined(__NT__)

#define __WIN32__

#endif

#endif

/* We need two checks on the OS: one for endian, the other for OS */

/* Check for endianness */

#if defined(__IRIX__) || defined(__sparc__) || defined(MACOS)

#define GLIDE_ENDIAN GLIDE_ENDIAN_BIG

#else

#define GLIDE_ENDIAN GLIDE_ENDIAN_LITTLE

#endif

/* Check for OS */

#if defined(__IRIX__) || defined(__sparc__) || defined(__linux__)

#define GLIDE_OS GLIDE_OS_UNIX

#elif defined(__DOS__)

#define GLIDE_OS GLIDE_OS_DOS32

#elif defined(__WIN32__)

#define GLIDE_OS GLIDE_OS_WIN32

#endif

/* Check for Simulator vs. Hardware */

#ifdef GLIDE_SIMULATOR

#define GLIDE_SST GLIDE_SST_SIM

#else

#define GLIDE_SST GLIDE_SST_HW

#endif

/* Check for type of hardware */

#ifdef SST96

#define GLIDE_HW GLIDE_HW_SST96

#elif defined(SSTH3)

#define GLIDE_HW GLIDE_HW_SSTH3

#elif defined(SST2)

#define GLIDE_HW GLIDE_HW_SST2

#else /* Default to SST1 */

#define GLIDE_HW GLIDE_HW_SST1

#endif

#define GLIDE_PLATFORM (GLIDE_ENDIAN | GLIDE_OS | GLIDE_SST | GLIDE_HW)

/*

** Control the number of TMUs

*/

#ifndef GLIDE_NUM_TMU

#define GLIDE_NUM_TMU 2

#endif

#if ((GLIDE_NUM_TMU < 0) && (GLIDE_NUM_TMU > 3))

#error "GLIDE_NUM_TMU set to an invalid value"

#endif

#endif /* __GLIDESYS_H__ */

#ifdef __cplusplus

extern "C" {

#endif

/*

** -----------------------------------------------------------------------

** TYPE DEFINITIONS

** -----------------------------------------------------------------------

*/

typedef FxU32 GrColor_t;

typedef FxU8 GrAlpha_t;

typedef FxU32 GrMipMapId_t;

typedef FxU8 GrFog_t;

/*

** -----------------------------------------------------------------------

** CONSTANTS AND TYPES

** -----------------------------------------------------------------------

*/

#define MAX_NUM_SST 4

#define MAX_MIPMAPS_PER_SST 1024

#define GR_FOG_TABLE_SIZE 64

#define GR_NULL_MIPMAP_HANDLE ((GrMipMapId_t)-1)

#define GR_ZDEPTHVALUE_NEAREST 0xFFFF

#define GR_ZDEPTHVALUE_FARTHEST 0x0000

#define GR_WDEPTHVALUE_NEAREST 0x0000

#define GR_WDEPTHVALUE_FARTHEST 0xFFFF

#define GR_MIPMAPLEVELMASK_EVEN FXBIT(0)

#define GR_MIPMAPLEVELMASK_ODD FXBIT(1)

#define GR_MIPMAPLEVELMASK_BOTH (GR_MIPMAPLEVELMASK_EVEN | GR_MIPMAPLEVELMASK_ODD)

#define GR_LODBIAS_BILINEAR 0.5

#define GR_LODBIAS_TRILINEAR 0.0

typedef FxI32 GrChipID_t;

#define GR_TMU0 0x0

#define GR_TMU1 0x1

#define GR_TMU2 0x2

#define GR_FBI 0x3

typedef FxI32 GrCombineFunction_t;

#define GR_COMBINE_FUNCTION_ZERO 0x0

#define GR_COMBINE_FUNCTION_NONE GR_COMBINE_FUNCTION_ZERO

#define GR_COMBINE_FUNCTION_LOCAL 0x1

#define GR_COMBINE_FUNCTION_LOCAL_ALPHA 0x2

#define GR_COMBINE_FUNCTION_SCALE_OTHER 0x3

#define GR_COMBINE_FUNCTION_BLEND_OTHER GR_COMBINE_FUNCTION_SCALE_OTHER

#define GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL 0x4

#define GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL_ALPHA 0x5

#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL 0x6

#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL 0x7

#define GR_COMBINE_FUNCTION_BLEND GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL

#define GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL_ADD_LOCAL_ALPHA 0x8

#define GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL 0x9

#define GR_COMBINE_FUNCTION_BLEND_LOCAL GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL

#define GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL_ALPHA 0x10

typedef FxI32 GrCombineFactor_t;

#define GR_COMBINE_FACTOR_ZERO 0x0

#define GR_COMBINE_FACTOR_NONE GR_COMBINE_FACTOR_ZERO

#define GR_COMBINE_FACTOR_LOCAL 0x1

#define GR_COMBINE_FACTOR_OTHER_ALPHA 0x2

#define GR_COMBINE_FACTOR_LOCAL_ALPHA 0x3

#define GR_COMBINE_FACTOR_TEXTURE_ALPHA 0x4

#define GR_COMBINE_FACTOR_DETAIL_FACTOR GR_COMBINE_FACTOR_TEXTURE_ALPHA

#define GR_COMBINE_FACTOR_LOD_FRACTION 0x5

#define GR_COMBINE_FACTOR_ONE 0x8

#define GR_COMBINE_FACTOR_ONE_MINUS_LOCAL 0x9

#define GR_COMBINE_FACTOR_ONE_MINUS_OTHER_ALPHA 0xa

#define GR_COMBINE_FACTOR_ONE_MINUS_LOCAL_ALPHA 0xb

#define GR_COMBINE_FACTOR_ONE_MINUS_TEXTURE_ALPHA 0xc

#define GR_COMBINE_FACTOR_ONE_MINUS_DETAIL_FACTOR GR_COMBINE_FACTOR_ONE_MINUS_TEXTURE_ALPHA

#define GR_COMBINE_FACTOR_ONE_MINUS_LOD_FRACTION 0xd

typedef FxI32 GrCombineLocal_t;

#define GR_COMBINE_LOCAL_ITERATED 0x0

#define GR_COMBINE_LOCAL_CONSTANT 0x1

#define GR_COMBINE_LOCAL_NONE GR_COMBINE_LOCAL_CONSTANT

#define GR_COMBINE_LOCAL_DEPTH 0x2

typedef FxI32 GrCombineOther_t;

#define GR_COMBINE_OTHER_ITERATED 0x0

#define GR_COMBINE_OTHER_TEXTURE 0x1

#define GR_COMBINE_OTHER_CONSTANT 0x2

#define GR_COMBINE_OTHER_NONE GR_COMBINE_OTHER_CONSTANT

typedef FxI32 GrAlphaSource_t;

#define GR_ALPHASOURCE_CC_ALPHA 0x0

#define GR_ALPHASOURCE_ITERATED_ALPHA 0x1

#define GR_ALPHASOURCE_TEXTURE_ALPHA 0x2

#define GR_ALPHASOURCE_TEXTURE_ALPHA_TIMES_ITERATED_ALPHA 0x3

typedef FxI32 GrColorCombineFnc_t;

#define GR_COLORCOMBINE_ZERO 0x0

#define GR_COLORCOMBINE_CCRGB 0x1

#define GR_COLORCOMBINE_ITRGB 0x2

#define GR_COLORCOMBINE_ITRGB_DELTA0 0x3

#define GR_COLORCOMBINE_DECAL_TEXTURE 0x4

#define GR_COLORCOMBINE_TEXTURE_TIMES_CCRGB 0x5

#define GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB 0x6

#define GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB_DELTA0 0x7

#define GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB_ADD_ALPHA 0x8

#define GR_COLORCOMBINE_TEXTURE_TIMES_ALPHA 0x9

#define GR_COLORCOMBINE_TEXTURE_TIMES_ALPHA_ADD_ITRGB 0xa

#define GR_COLORCOMBINE_TEXTURE_ADD_ITRGB 0xb

#define GR_COLORCOMBINE_TEXTURE_SUB_ITRGB 0xc

#define GR_COLORCOMBINE_CCRGB_BLEND_ITRGB_ON_TEXALPHA 0xd

#define GR_COLORCOMBINE_DIFF_SPEC_A 0xe

#define GR_COLORCOMBINE_DIFF_SPEC_B 0xf

#define GR_COLORCOMBINE_ONE 0x10

typedef FxI32 GrAlphaBlendFnc_t;

#define GR_BLEND_ZERO 0x0

#define GR_BLEND_SRC_ALPHA 0x1

#define GR_BLEND_SRC_COLOR 0x2

#define GR_BLEND_DST_COLOR GR_BLEND_SRC_COLOR

#define GR_BLEND_DST_ALPHA 0x3

#define GR_BLEND_ONE 0x4

#define GR_BLEND_ONE_MINUS_SRC_ALPHA 0x5

#define GR_BLEND_ONE_MINUS_SRC_COLOR 0x6

#define GR_BLEND_ONE_MINUS_DST_COLOR GR_BLEND_ONE_MINUS_SRC_COLOR

#define GR_BLEND_ONE_MINUS_DST_ALPHA 0x7

#define GR_BLEND_RESERVED_8 0x8

#define GR_BLEND_RESERVED_9 0x9

#define GR_BLEND_RESERVED_A 0xa

#define GR_BLEND_RESERVED_B 0xb

#define GR_BLEND_RESERVED_C 0xc

#define GR_BLEND_RESERVED_D 0xd

#define GR_BLEND_RESERVED_E 0xe

#define GR_BLEND_ALPHA_SATURATE 0xf

#define GR_BLEND_PREFOG_COLOR GR_BLEND_ALPHA_SATURATE

typedef FxI32 GrAspectRatio_t;

#define GR_ASPECT_8x1 0x0 /* 8W x 1H */

#define GR_ASPECT_4x1 0x1 /* 4W x 1H */

#define GR_ASPECT_2x1 0x2 /* 2W x 1H */

#define GR_ASPECT_1x1 0x3 /* 1W x 1H */

#define GR_ASPECT_1x2 0x4 /* 1W x 2H */

#define GR_ASPECT_1x4 0x5 /* 1W x 4H */

#define GR_ASPECT_1x8 0x6 /* 1W x 8H */

typedef FxI32 GrBuffer_t;

#define GR_BUFFER_FRONTBUFFER 0x0

#define GR_BUFFER_BACKBUFFER 0x1

#define GR_BUFFER_AUXBUFFER 0x2

#define GR_BUFFER_DEPTHBUFFER 0x3

#define GR_BUFFER_ALPHABUFFER 0x4

#define GR_BUFFER_TRIPLEBUFFER 0x5

typedef FxI32 GrChromakeyMode_t;

#define GR_CHROMAKEY_DISABLE 0x0

#define GR_CHROMAKEY_ENABLE 0x1

typedef FxI32 GrCmpFnc_t;

#define GR_CMP_NEVER 0x0

#define GR_CMP_LESS 0x1

#define GR_CMP_EQUAL 0x2

#define GR_CMP_LEQUAL 0x3

#define GR_CMP_GREATER 0x4

#define GR_CMP_NOTEQUAL 0x5

#define GR_CMP_GEQUAL 0x6

#define GR_CMP_ALWAYS 0x7

typedef FxI32 GrColorFormat_t;

#define GR_COLORFORMAT_ARGB 0x0

#define GR_COLORFORMAT_ABGR 0x1

#define GR_COLORFORMAT_RGBA 0x2

#define GR_COLORFORMAT_BGRA 0x3

typedef FxI32 GrCullMode_t;

#define GR_CULL_DISABLE 0x0

#define GR_CULL_NEGATIVE 0x1

#define GR_CULL_POSITIVE 0x2

typedef FxI32 GrDepthBufferMode_t;

#define GR_DEPTHBUFFER_DISABLE 0x0

#define GR_DEPTHBUFFER_ZBUFFER 0x1

#define GR_DEPTHBUFFER_WBUFFER 0x2

#define GR_DEPTHBUFFER_ZBUFFER_COMPARE_TO_BIAS 0x3

#define GR_DEPTHBUFFER_WBUFFER_COMPARE_TO_BIAS 0x4

typedef FxI32 GrDitherMode_t;

#define GR_DITHER_DISABLE 0x0

#define GR_DITHER_2x2 0x1

#define GR_DITHER_4x4 0x2

typedef FxI32 GrFogMode_t;

#define GR_FOG_DISABLE 0x0

#define GR_FOG_WITH_ITERATED_ALPHA 0x1

#define GR_FOG_WITH_TABLE 0x2

#define GR_FOG_MULT2 0x100

#define GR_FOG_ADD2 0x200

typedef FxU32 GrLock_t;

#define GR_LFB_READ_ONLY 0x00

#define GR_LFB_WRITE_ONLY 0x01

#define GR_LFB_IDLE 0x00

#define GR_LFB_NOIDLE 0x10

typedef FxI32 GrLfbBypassMode_t;

#define GR_LFBBYPASS_DISABLE 0x0

#define GR_LFBBYPASS_ENABLE 0x1

typedef FxI32 GrLfbWriteMode_t;

#define GR_LFBWRITEMODE_565 0x0 /* RGB:RGB */

#define GR_LFBWRITEMODE_555 0x1 /* RGB:RGB */

#define GR_LFBWRITEMODE_1555 0x2 /* ARGB:ARGB */

#define GR_LFBWRITEMODE_RESERVED1 0x3

#define GR_LFBWRITEMODE_888 0x4 /* RGB */

#define GR_LFBWRITEMODE_8888 0x5 /* ARGB */

#define GR_LFBWRITEMODE_RESERVED2 0x6

#define GR_LFBWRITEMODE_RESERVED3 0x7

#define GR_LFBWRITEMODE_RESERVED4 0x8

#define GR_LFBWRITEMODE_RESERVED5 0x9

#define GR_LFBWRITEMODE_RESERVED6 0xa

#define GR_LFBWRITEMODE_RESERVED7 0xb

#define GR_LFBWRITEMODE_565_DEPTH 0xc /* RGB:DEPTH */

#define GR_LFBWRITEMODE_555_DEPTH 0xd /* RGB:DEPTH */

#define GR_LFBWRITEMODE_1555_DEPTH 0xe /* ARGB:DEPTH */

#define GR_LFBWRITEMODE_ZA16 0xf /* DEPTH:DEPTH */

#define GR_LFBWRITEMODE_ANY 0xFF

typedef FxI32 GrOriginLocation_t;

#define GR_ORIGIN_UPPER_LEFT 0x0

#define GR_ORIGIN_LOWER_LEFT 0x1

#define GR_ORIGIN_ANY 0xFF

struct GrLfbInfo_t {

  int size;

  void *lfbPtr;

  FxU32 strideInBytes;

  GrLfbWriteMode_t writeMode;

  GrOriginLocation_t origin;

};

typedef FxI32 GrLOD_t;

#define GR_LOD_256 0x0

#define GR_LOD_128 0x1

#define GR_LOD_64 0x2

#define GR_LOD_32 0x3

#define GR_LOD_16 0x4

#define GR_LOD_8 0x5

#define GR_LOD_4 0x6

#define GR_LOD_2 0x7

#define GR_LOD_1 0x8

typedef FxI32 GrMipMapMode_t;

#define GR_MIPMAP_DISABLE 0x0 /* no mip mapping  */

#define GR_MIPMAP_NEAREST 0x1 /* use nearest mipmap */

#define GR_MIPMAP_NEAREST_DITHER 0x2 /* GR_MIPMAP_NEAREST + LOD dith */

typedef FxI32 GrSmoothingMode_t;

#define GR_SMOOTHING_DISABLE 0x0

#define GR_SMOOTHING_ENABLE 0x1

typedef FxI32 GrTextureClampMode_t;

#define GR_TEXTURECLAMP_WRAP 0x0

#define GR_TEXTURECLAMP_CLAMP 0x1

typedef FxI32 GrTextureCombineFnc_t;

#define GR_TEXTURECOMBINE_ZERO 0x0 /* texout = 0 */

#define GR_TEXTURECOMBINE_DECAL 0x1 /* texout = texthis */

#define GR_TEXTURECOMBINE_OTHER 0x2 /* this TMU in passthru mode */

#define GR_TEXTURECOMBINE_ADD 0x3 /* tout = tthis + t(this+1) */

#define GR_TEXTURECOMBINE_MULTIPLY 0x4 /* texout = tthis * t(this+1) */

#define GR_TEXTURECOMBINE_SUBTRACT 0x5 /* Sutract from upstream TMU */

#define GR_TEXTURECOMBINE_DETAIL 0x6 /* detail--detail on tthis */

#define GR_TEXTURECOMBINE_DETAIL_OTHER 0x7 /* detail--detail on tthis+1 */

#define GR_TEXTURECOMBINE_TRILINEAR_ODD 0x8 /* trilinear--odd levels tthis*/

#define GR_TEXTURECOMBINE_TRILINEAR_EVEN 0x9 /*trilinear--even levels tthis*/

#define GR_TEXTURECOMBINE_ONE 0xa /* texout = 0xFFFFFFFF */

typedef FxI32 GrTextureFilterMode_t;

#define GR_TEXTUREFILTER_POINT_SAMPLED 0x0

#define GR_TEXTUREFILTER_BILINEAR 0x1

typedef FxI32 GrTextureFormat_t;

#define GR_TEXFMT_8BIT 0x0

#define GR_TEXFMT_RGB_332 GR_TEXFMT_8BIT

#define GR_TEXFMT_YIQ_422 0x1

#define GR_TEXFMT_ALPHA_8 0x2 /* (0..0xFF) alpha     */

#define GR_TEXFMT_INTENSITY_8 0x3 /* (0..0xFF) intensity */

#define GR_TEXFMT_ALPHA_INTENSITY_44 0x4

#define GR_TEXFMT_P_8 0x5 /* 8-bit palette */

#define GR_TEXFMT_RSVD0 0x6

#define GR_TEXFMT_RSVD1 0x7

#define GR_TEXFMT_16BIT 0x8

#define GR_TEXFMT_ARGB_8332 GR_TEXFMT_16BIT

#define GR_TEXFMT_AYIQ_8422 0x9

#define GR_TEXFMT_RGB_565 0xa

#define GR_TEXFMT_ARGB_1555 0xb

#define GR_TEXFMT_ARGB_4444 0xc

#define GR_TEXFMT_ALPHA_INTENSITY_88 0xd

#define GR_TEXFMT_AP_88 0xe /* 8-bit alpha 8-bit palette */

#define GR_TEXFMT_RSVD2 0xf

typedef FxU32 GrTexTable_t;

#define GR_TEXTABLE_NCC0 0x0

#define GR_TEXTABLE_NCC1 0x1

#define GR_TEXTABLE_PALETTE 0x2

typedef FxU32 GrNCCTable_t;

#define GR_NCCTABLE_NCC0 0x0

#define GR_NCCTABLE_NCC1 0x1

typedef FxU32 GrTexBaseRange_t;

#define GR_TEXBASE_256 0x0

#define GR_TEXBASE_128 0x1

#define GR_TEXBASE_64 0x2

#define GR_TEXBASE_32_TO_1 0x3

#define GLIDE_STATE_PAD_SIZE 312

#ifdef GLIDE_LIB

struct _GrState_s GrState;

#else

struct GrState {

  char pad[GLIDE_STATE_PAD_SIZE];

};

#endif

/*

** -----------------------------------------------------------------------

** STRUCTURES

** -----------------------------------------------------------------------

*/

/*

** 3DF texture file structs

*/

struct Gu3dfHeader

{

  FxU32 width, height;

  int small_lod, large_lod;

  GrAspectRatio_t aspect_ratio;

  GrTextureFormat_t format;

};

struct GuNccTable

{

  FxU8 yRGB[16];

  FxI16 iRGB[4][3];

  FxI16 qRGB[4][3];

  FxU32 packed_data[12];

};

struct GuTexPalette {

  FxU32 data[256];

};

union GuTexTable{

  GuNccTable nccTable;

  GuTexPalette palette;

};

struct Gu3dfInfo

{

  Gu3dfHeader header;

  GuTexTable table;

  void *data;

  FxU32 mem_required; /* memory required for mip map in bytes. */

};

struct GrTexInfo {

  GrLOD_t smallLod;

  GrLOD_t largeLod;

  GrAspectRatio_t aspectRatio;

  GrTextureFormat_t format;

  void *data;

};

struct GrMipMapInfo

{

  int sst; /* SST where this texture map was stored  */

  FxBool valid; /* set when this table entry is allocated*/

  int width, height;

  GrAspectRatio_t aspect_ratio; /* aspect ratio of the mip map.  */

  void *data; /* actual texture data  */

  GrTextureFormat_t format; /* format of the texture table */

  GrMipMapMode_t mipmap_mode; /* mip map mode for this texture */

  GrTextureFilterMode_t magfilter_mode; /* filtering to be used when magnified */

  GrTextureFilterMode_t minfilter_mode; /* filtering to be used with minified  */

  GrTextureClampMode_t s_clamp_mode; /* how this texture should be clamped in s */

  GrTextureClampMode_t t_clamp_mode; /* how this texture should be clamped in t */

  FxU32 tLOD; /* Register value for tLOD register */

  FxU32 tTextureMode; /* Register value for tTextureMode register

                         not including non-texture specific bits */

  FxU32 lod_bias; /* LOD bias of the mip map in preshifted 4.2*/

  GrLOD_t lod_min, lod_max; /* largest and smallest levels of detail  */

  int tmu; /* tmu on which this texture resides */

  FxU32 odd_even_mask; /* mask specifying levels on this tmu  */

  FxU32 tmu_base_address; /* base addr (in TMU mem) of this texture */

  FxBool trilinear; /* should we blend by lod? */

  GuNccTable ncc_table; /* NCC compression table (optional) */

};

typedef int GrSstType;

#define GR_SSTTYPE_VOODOO 0

#define GR_SSTTYPE_SST96 1

#define GR_SSTTYPE_AT3D 2

struct GrTMUConfig_t {

  int tmuRev; /* Rev of Texelfx chip */

  int tmuRam; /* 1, 2, or 4 MB */

};

struct GrVoodooConfig_t {

  int fbRam; /* 1, 2, or 4 MB */

  int fbiRev; /* Rev of Pixelfx chip */

  int nTexelfx; /* How many texelFX chips are there? */

  FxBool sliDetect; /* Is it a scan-line interleaved board? */

  GrTMUConfig_t tmuConfig[GLIDE_NUM_TMU]; /* Configuration of the Texelfx chips */

};

struct GrSst96Config_t {

  int fbRam; /* How much? */

  int nTexelfx;

  GrTMUConfig_t tmuConfig;

};

struct GrAT3DConfig_t {

  int rev;

};

struct GrHwConfiguration {

  int num_sst; /* # of HW units in the system */

  struct {

    GrSstType type; /* Which hardware is it? */

    union SstBoard_u {

      GrVoodooConfig_t VoodooConfig;

      GrSst96Config_t SST96Config;

      GrAT3DConfig_t AT3DConfig;

    } sstBoard;

  } SSTs[MAX_NUM_SST]; /* configuration for each board */

};

struct GrSstPerfStats_t {

  FxU32 pixelsIn; /* # pixels processed (minus buffer clears) */

  FxU32 chromaFail; /* # pixels not drawn due to chroma key */

  FxU32 zFuncFail; /* # pixels not drawn due to Z comparison */

  FxU32 aFuncFail; /* # pixels not drawn due to alpha comparison */

  FxU32 pixelsOut; /* # pixels drawn (including buffer clears) */

};

struct GrTmuVertex {

  float sow; /* s texture ordinate (s over w) */

  float tow; /* t texture ordinate (t over w) */

  float oow; /* 1/w (used mipmapping - really 0xfff/w) */

};

/*

** GrVertex

** If these are changed the C & assembly language trisetup routines MUST

** be changed, for they will no longer work.

*/

struct GrVertex

{

  float x, y, z; /* X, Y, and Z of scrn space -- Z is ignored */

  float r, g, b; /* R, G, B, ([0..255.0]) */

  float ooz; /* 65535/Z (used for Z-buffering) */

  float a; /* Alpha [0..255.0] */

  float oow; /* 1/W (used for W-buffering, texturing) */

  GrTmuVertex tmuvtx[GLIDE_NUM_TMU];

};

/* For indexing GrVertex as a float *.

   CHANGE THESE IF THE VERTEX STRUCTURE CHANGES!

   */

#define GR_VERTEX_X_OFFSET 0

#define GR_VERTEX_Y_OFFSET 1

#define GR_VERTEX_Z_OFFSET 2

#define GR_VERTEX_R_OFFSET 3

#define GR_VERTEX_G_OFFSET 4

#define GR_VERTEX_B_OFFSET 5

#define GR_VERTEX_OOZ_OFFSET 6

#define GR_VERTEX_A_OFFSET 7

#define GR_VERTEX_OOW_OFFSET 8

#define GR_VERTEX_SOW_TMU0_OFFSET 9

#define GR_VERTEX_TOW_TMU0_OFFSET 10

#define GR_VERTEX_OOW_TMU0_OFFSET 11

#define GR_VERTEX_SOW_TMU1_OFFSET 12

#define GR_VERTEX_TOW_TMU1_OFFSET 13

#define GR_VERTEX_OOW_TMU1_OFFSET 14

#if (GLIDE_NUM_TMU > 2)

#define GR_VERTEX_SOW_TMU2_OFFSET 15

#define GR_VERTEX_TOW_TMU2_OFFSET 16

#define GR_VERTEX_OOW_TMU2_OFFSET 17

#endif

typedef FxU32 GrLfbSrcFmt_t;

#define GR_LFB_SRC_FMT_565 0x00

#define GR_LFB_SRC_FMT_555 0x01

#define GR_LFB_SRC_FMT_1555 0x02

#define GR_LFB_SRC_FMT_888 0x04

#define GR_LFB_SRC_FMT_8888 0x05

#define GR_LFB_SRC_FMT_565_DEPTH 0x0c

#define GR_LFB_SRC_FMT_555_DEPTH 0x0d

#define GR_LFB_SRC_FMT_1555_DEPTH 0x0e

#define GR_LFB_SRC_FMT_ZA16 0x0f

#define GR_LFB_SRC_FMT_RLE16 0x80

typedef FxI32 GrPassthruMode_t;

#define GR_PASSTHRU_SHOW_VGA 0x0

#define GR_PASSTHRU_SHOW_SST1 0x1

typedef FxU32 GrHint_t;

#define GR_HINTTYPE_MIN 0

#define GR_HINT_STWHINT 0

#define GR_HINT_FIFOCHECKHINT 1

#define GR_HINT_FPUPRECISION 2

#define GR_HINT_ALLOW_MIPMAP_DITHER 3

#define GR_HINTTYPE_MAX 3

typedef FxU32 GrSTWHint_t;

#define GR_STWHINT_W_DIFF_FBI FXBIT(0)

#define GR_STWHINT_W_DIFF_TMU0 FXBIT(1)

#define GR_STWHINT_ST_DIFF_TMU0 FXBIT(2)

#define GR_STWHINT_W_DIFF_TMU1 FXBIT(3)

#define GR_STWHINT_ST_DIFF_TMU1 FXBIT(4)

#define GR_STWHINT_W_DIFF_TMU2 FXBIT(5)

#define GR_STWHINT_ST_DIFF_TMU2 FXBIT(6)

typedef FxU32 GrControl_t;

#define GR_CONTROL_ACTIVATE 0x1

#define GR_CONTROL_DEACTIVATE 0x2

#define GR_CONTROL_RESIZE 0x3

#define GR_CONTROL_MOVE 0x4

#define GR_GENERATE_FIFOCHECK_HINT_MASK(swHWM, swLWM) (((swHWM & 0xffff) << 16) | (swLWM & 0xffff))

/*

** -----------------------------------------------------------------------

** FUNCTION PROTOTYPES

** -----------------------------------------------------------------------

*/

#ifndef FX_GLIDE_NO_FUNC_PROTO

/*

** rendering functions

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawLine_fpt)(const GrVertex *v1, const GrVertex *v2);

#else

FX_ENTRY void FX_CALL

grDrawLine(const GrVertex *v1, const GrVertex *v2);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawPlanarPolygon_fpt)(int nverts, const int ilist[], const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

grDrawPlanarPolygon(int nverts, const int ilist[], const GrVertex vlist[]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawPlanarPolygonVertexList_fpt)(int nverts, const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

grDrawPlanarPolygonVertexList(int nverts, const GrVertex vlist[]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawPoint_fpt)(const GrVertex *pt);

#else

FX_ENTRY void FX_CALL

grDrawPoint(const GrVertex *pt);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawPolygon_fpt)(int nverts, const int ilist[], const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

grDrawPolygon(int nverts, const int ilist[], const GrVertex vlist[]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawPolygonVertexList_fpt)(int nverts, const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

grDrawPolygonVertexList(int nverts, const GrVertex vlist[]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDrawTriangle_fpt)(const GrVertex *a, const GrVertex *b, const GrVertex *c);

#else

FX_ENTRY void FX_CALL

grDrawTriangle(const GrVertex *a, const GrVertex *b, const GrVertex *c);

#endif /* DYNAHEADER */

/*

** buffer management

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grBufferClear_fpt)(GrColor_t color, GrAlpha_t alpha, FxU16 depth);

#else

FX_ENTRY void FX_CALL

grBufferClear(GrColor_t color, GrAlpha_t alpha, FxU16 depth);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef int(FX_CALL *grBufferNumPending_fpt)(void);

#else

FX_ENTRY int FX_CALL

grBufferNumPending(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grBufferSwap_fpt)(int swap_interval);

#else

FX_ENTRY void FX_CALL

grBufferSwap(int swap_interval);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grRenderBuffer_fpt)(GrBuffer_t buffer);

#else

FX_ENTRY void FX_CALL

grRenderBuffer(GrBuffer_t buffer);

#endif /* DYNAHEADER */

/*

** error management

*/

typedef void (*GrErrorCallbackFnc_t)(const char *string, FxBool fatal);

#ifdef DYNAHEADER

typedef void(FX_CALL *grErrorSetCallback_fpt)(GrErrorCallbackFnc_t fnc);

#else

FX_ENTRY void FX_CALL

grErrorSetCallback(GrErrorCallbackFnc_t fnc);

#endif /* DYNAHEADER */

/*

** SST routines

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grSstIdle_fpt)(void);

#else

FX_ENTRY void FX_CALL

grSstIdle(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *grSstVideoLine_fpt)(void);

#else

FX_ENTRY FxU32 FX_CALL

grSstVideoLine(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grSstVRetraceOn_fpt)(void);

#else

FX_ENTRY FxBool FX_CALL

grSstVRetraceOn(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grSstIsBusy_fpt)(void);

#else

FX_ENTRY FxBool FX_CALL

grSstIsBusy(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grSstWinOpen_fpt)(FxU32 hWnd, GrScreenResolution_t screen_resolution,
                                          GrScreenRefresh_t refresh_rate, GrColorFormat_t color_format,
                                          GrOriginLocation_t origin_location, int nColBuffers, int nAuxBuffers);

#else

FX_ENTRY FxBool FX_CALL

grSstWinOpen(

    FxU32 hWnd,

    GrScreenResolution_t screen_resolution,

    GrScreenRefresh_t refresh_rate,

    GrColorFormat_t color_format,

    GrOriginLocation_t origin_location,

    int nColBuffers,

    int nAuxBuffers);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grSstWinClose_fpt)(void);

#else

FX_ENTRY void FX_CALL

grSstWinClose(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grSstControl_fpt)(FxU32 code);

#else

FX_ENTRY FxBool FX_CALL

grSstControl(FxU32 code);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grSstQueryHardware_fpt)(GrHwConfiguration *hwconfig);

#else

FX_ENTRY FxBool FX_CALL

grSstQueryHardware(GrHwConfiguration *hwconfig);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grSstQueryBoards_fpt)(GrHwConfiguration *hwconfig);

#else

FX_ENTRY FxBool FX_CALL

grSstQueryBoards(GrHwConfiguration *hwconfig);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grSstOrigin_fpt)(GrOriginLocation_t origin);

#else

FX_ENTRY void FX_CALL

grSstOrigin(GrOriginLocation_t origin);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grSstSelect_fpt)(int which_sst);

#else

FX_ENTRY void FX_CALL

grSstSelect(int which_sst);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef int(FX_CALL *grSstScreenHeight_fpt)(void);

#else

FX_ENTRY int FX_CALL

grSstScreenHeight(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef int(FX_CALL *grSstScreenWidth_fpt)(void);

#else

FX_ENTRY int FX_CALL

grSstScreenWidth(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *grSstStatus_fpt)(void);

#else

FX_ENTRY FxU32 FX_CALL

grSstStatus(void);

#endif /* DYNAHEADER */

/*

**  Drawing Statistics

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grSstPerfStats_fpt)(GrSstPerfStats_t *pStats);

#else

FX_ENTRY void FX_CALL

grSstPerfStats(GrSstPerfStats_t *pStats);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grSstResetPerfStats_fpt)(void);

#else

FX_ENTRY void FX_CALL

grSstResetPerfStats(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grResetTriStats_fpt)();

#else

FX_ENTRY void FX_CALL

grResetTriStats();

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTriStats_fpt)(FxU32 *trisProcessed, FxU32 *trisDrawn);

#else

FX_ENTRY void FX_CALL

grTriStats(FxU32 *trisProcessed, FxU32 *trisDrawn);

#endif /* DYNAHEADER */

/*

** Glide configuration and special effect maintenance functions

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grAlphaBlendFunction_fpt)(GrAlphaBlendFnc_t rgb_sf, GrAlphaBlendFnc_t rgb_df,
                                                GrAlphaBlendFnc_t alpha_sf, GrAlphaBlendFnc_t alpha_df);

#else

FX_ENTRY void FX_CALL

grAlphaBlendFunction(

    GrAlphaBlendFnc_t rgb_sf, GrAlphaBlendFnc_t rgb_df,

    GrAlphaBlendFnc_t alpha_sf, GrAlphaBlendFnc_t alpha_df

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAlphaCombine_fpt)(GrCombineFunction_t function, GrCombineFactor_t factor,
                                          GrCombineLocal_t local, GrCombineOther_t other, FxBool invert);

#else

FX_ENTRY void FX_CALL

grAlphaCombine(

    GrCombineFunction_t function, GrCombineFactor_t factor,

    GrCombineLocal_t local, GrCombineOther_t other,

    FxBool invert

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAlphaControlsITRGBLighting_fpt)(FxBool enable);

#else

FX_ENTRY void FX_CALL

grAlphaControlsITRGBLighting(FxBool enable);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAlphaTestFunction_fpt)(GrCmpFnc_t function);

#else

FX_ENTRY void FX_CALL

grAlphaTestFunction(GrCmpFnc_t function);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAlphaTestReferenceValue_fpt)(GrAlpha_t value);

#else

FX_ENTRY void FX_CALL

grAlphaTestReferenceValue(GrAlpha_t value);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grChromakeyMode_fpt)(GrChromakeyMode_t mode);

#else

FX_ENTRY void FX_CALL

grChromakeyMode(GrChromakeyMode_t mode);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grChromakeyValue_fpt)(GrColor_t value);

#else

FX_ENTRY void FX_CALL

grChromakeyValue(GrColor_t value);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grClipWindow_fpt)(int minx, int miny, int maxx, int maxy);

#else

FX_ENTRY void FX_CALL

grClipWindow(int minx, int miny, int maxx, int maxy);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grColorCombine_fpt)(GrCombineFunction_t function, GrCombineFactor_t factor,
                                          GrCombineLocal_t local, GrCombineOther_t other, FxBool invert);

#else

FX_ENTRY void FX_CALL

grColorCombine(

    GrCombineFunction_t function, GrCombineFactor_t factor,

    GrCombineLocal_t local, GrCombineOther_t other,

    FxBool invert);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grColorMask_fpt)(FxBool rgb, FxBool a);

#else

FX_ENTRY void FX_CALL

grColorMask(FxBool rgb, FxBool a);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grCullMode_fpt)(GrCullMode_t mode);

#else

FX_ENTRY void FX_CALL

grCullMode(GrCullMode_t mode);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grConstantColorValue_fpt)(GrColor_t value);

#else

FX_ENTRY void FX_CALL

grConstantColorValue(GrColor_t value);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grConstantColorValue4_fpt)(float a, float r, float g, float b);

#else

FX_ENTRY void FX_CALL

grConstantColorValue4(float a, float r, float g, float b);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDepthBiasLevel_fpt)(FxI16 level);

#else

FX_ENTRY void FX_CALL

grDepthBiasLevel(FxI16 level);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDepthBufferFunction_fpt)(GrCmpFnc_t function);

#else

FX_ENTRY void FX_CALL

grDepthBufferFunction(GrCmpFnc_t function);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDepthBufferMode_fpt)(GrDepthBufferMode_t mode);

#else

FX_ENTRY void FX_CALL

grDepthBufferMode(GrDepthBufferMode_t mode);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDepthMask_fpt)(FxBool mask);

#else

FX_ENTRY void FX_CALL

grDepthMask(FxBool mask);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDisableAllEffects_fpt)(void);

#else

FX_ENTRY void FX_CALL

grDisableAllEffects(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grDitherMode_fpt)(GrDitherMode_t mode);

#else

FX_ENTRY void FX_CALL

grDitherMode(GrDitherMode_t mode);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grFogColorValue_fpt)(GrColor_t fogcolor);

#else

FX_ENTRY void FX_CALL

grFogColorValue(GrColor_t fogcolor);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grFogMode_fpt)(GrFogMode_t mode);

#else

FX_ENTRY void FX_CALL

grFogMode(GrFogMode_t mode);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grFogTable_fpt)(const GrFog_t ft[GR_FOG_TABLE_SIZE]);

#else

FX_ENTRY void FX_CALL

grFogTable(const GrFog_t ft[GR_FOG_TABLE_SIZE]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grGammaCorrectionValue_fpt)(float value);

#else

FX_ENTRY void FX_CALL

grGammaCorrectionValue(float value);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grSplash_fpt)(float x, float y, float width, float height, FxU32 frame);

#else

FX_ENTRY void FX_CALL

grSplash(float x, float y, float width, float height, FxU32 frame);

#endif /* DYNAHEADER */

/*

** texture mapping control functions

*/

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *grTexCalcMemRequired_fpt)(GrLOD_t lodmin, GrLOD_t lodmax, GrAspectRatio_t aspect,
                                                 GrTextureFormat_t fmt);

#else

FX_ENTRY FxU32 FX_CALL

grTexCalcMemRequired(

    GrLOD_t lodmin, GrLOD_t lodmax,

    GrAspectRatio_t aspect, GrTextureFormat_t fmt);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *grTexTextureMemRequired_fpt)(FxU32 evenOdd, GrTexInfo *info);

#else

FX_ENTRY FxU32 FX_CALL

grTexTextureMemRequired(FxU32 evenOdd,

                        GrTexInfo *info);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *grTexMinAddress_fpt)(GrChipID_t tmu);

#else

FX_ENTRY FxU32 FX_CALL

grTexMinAddress(GrChipID_t tmu);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *grTexMaxAddress_fpt)(GrChipID_t tmu);

#else

FX_ENTRY FxU32 FX_CALL

grTexMaxAddress(GrChipID_t tmu);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexNCCTable_fpt)(GrChipID_t tmu, GrNCCTable_t table);

#else

FX_ENTRY void FX_CALL

grTexNCCTable(GrChipID_t tmu, GrNCCTable_t table);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexSource_fpt)(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo *info);

#else

FX_ENTRY void FX_CALL

grTexSource(GrChipID_t tmu,

            FxU32 startAddress,

            FxU32 evenOdd,

            GrTexInfo *info);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexClampMode_fpt)(GrChipID_t tmu, GrTextureClampMode_t s_clampmode,
                                          GrTextureClampMode_t t_clampmode);

#else

FX_ENTRY void FX_CALL

grTexClampMode(

    GrChipID_t tmu,

    GrTextureClampMode_t s_clampmode,

    GrTextureClampMode_t t_clampmode

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexCombine_fpt)(GrChipID_t tmu, GrCombineFunction_t rgb_function, GrCombineFactor_t rgb_factor,
                                        GrCombineFunction_t alpha_function, GrCombineFactor_t alpha_factor,
                                        FxBool rgb_invert, FxBool alpha_invert);

#else

FX_ENTRY void FX_CALL

grTexCombine(

    GrChipID_t tmu,

    GrCombineFunction_t rgb_function,

    GrCombineFactor_t rgb_factor,

    GrCombineFunction_t alpha_function,

    GrCombineFactor_t alpha_factor,

    FxBool rgb_invert,

    FxBool alpha_invert

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexCombineFunction_fpt)(GrChipID_t tmu, GrTextureCombineFnc_t fnc);

#else

FX_ENTRY void FX_CALL

grTexCombineFunction(

    GrChipID_t tmu,

    GrTextureCombineFnc_t fnc

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexDetailControl_fpt)(GrChipID_t tmu, int lod_bias, FxU8 detail_scale, float detail_max);

#else

FX_ENTRY void FX_CALL

grTexDetailControl(

    GrChipID_t tmu,

    int lod_bias,

    FxU8 detail_scale,

    float detail_max

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexFilterMode_fpt)(GrChipID_t tmu, GrTextureFilterMode_t minfilter_mode,
                                           GrTextureFilterMode_t magfilter_mode);

#else

FX_ENTRY void FX_CALL

grTexFilterMode(

    GrChipID_t tmu,

    GrTextureFilterMode_t minfilter_mode,

    GrTextureFilterMode_t magfilter_mode

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexLodBiasValue_fpt)(GrChipID_t tmu, float bias);

#else

FX_ENTRY void FX_CALL

grTexLodBiasValue(GrChipID_t tmu, float bias);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexDownloadMipMap_fpt)(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo *info);

#else

FX_ENTRY void FX_CALL

grTexDownloadMipMap(GrChipID_t tmu,

                    FxU32 startAddress,

                    FxU32 evenOdd,

                    GrTexInfo *info);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexDownloadMipMapLevel_fpt)(GrChipID_t tmu, FxU32 startAddress, GrLOD_t thisLod,
                                                    GrLOD_t largeLod, GrAspectRatio_t aspectRatio,
                                                    GrTextureFormat_t format, FxU32 evenOdd, void *data);

#else

FX_ENTRY void FX_CALL

grTexDownloadMipMapLevel(GrChipID_t tmu,

                         FxU32 startAddress,

                         GrLOD_t thisLod,

                         GrLOD_t largeLod,

                         GrAspectRatio_t aspectRatio,

                         GrTextureFormat_t format,

                         FxU32 evenOdd,

                         void *data);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexDownloadMipMapLevelPartial_fpt)(GrChipID_t tmu, FxU32 startAddress, GrLOD_t thisLod,
                                                           GrLOD_t largeLod, GrAspectRatio_t aspectRatio,
                                                           GrTextureFormat_t format, FxU32 evenOdd, void *data,
                                                           int start, int end);

#else

FX_ENTRY void FX_CALL

grTexDownloadMipMapLevelPartial(GrChipID_t tmu,

                                FxU32 startAddress,

                                GrLOD_t thisLod,

                                GrLOD_t largeLod,

                                GrAspectRatio_t aspectRatio,

                                GrTextureFormat_t format,

                                FxU32 evenOdd,

                                void *data,

                                int start,

                                int end);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *ConvertAndDownloadRle_fpt)(GrChipID_t tmu, FxU32 startAddress, GrLOD_t thisLod, GrLOD_t largeLod,
                                                 GrAspectRatio_t aspectRatio, GrTextureFormat_t format, FxU32 evenOdd,
                                                 FxU8 *bm_data, long bm_h, FxU32 u0, FxU32 v0, FxU32 width,
                                                 FxU32 height, FxU32 dest_width, FxU32 dest_height, FxU16 *tlut);

#else

FX_ENTRY void FX_CALL

ConvertAndDownloadRle(GrChipID_t tmu,

                      FxU32 startAddress,

                      GrLOD_t thisLod,

                      GrLOD_t largeLod,

                      GrAspectRatio_t aspectRatio,

                      GrTextureFormat_t format,

                      FxU32 evenOdd,

                      FxU8 *bm_data,

                      long bm_h,

                      FxU32 u0,

                      FxU32 v0,

                      FxU32 width,

                      FxU32 height,

                      FxU32 dest_width,

                      FxU32 dest_height,

                      FxU16 *tlut);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grCheckForRoom_fpt)(FxI32 n);

#else

FX_ENTRY void FX_CALL

grCheckForRoom(FxI32 n);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexDownloadTable_fpt)(GrChipID_t tmu, GrTexTable_t type, void *data);

#else

FX_ENTRY void FX_CALL

grTexDownloadTable(GrChipID_t tmu,

                   GrTexTable_t type,

                   void *data);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexDownloadTablePartial_fpt)(GrChipID_t tmu, GrTexTable_t type, void *data, int start, int end);

#else

FX_ENTRY void FX_CALL

grTexDownloadTablePartial(GrChipID_t tmu,

                          GrTexTable_t type,

                          void *data,

                          int start,

                          int end);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexMipMapMode_fpt)(GrChipID_t tmu, GrMipMapMode_t mode, FxBool lodBlend);

#else

FX_ENTRY void FX_CALL

grTexMipMapMode(GrChipID_t tmu,

                GrMipMapMode_t mode,

                FxBool lodBlend);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexMultibase_fpt)(GrChipID_t tmu, FxBool enable);

#else

FX_ENTRY void FX_CALL

grTexMultibase(GrChipID_t tmu,

               FxBool enable);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grTexMultibaseAddress_fpt)(GrChipID_t tmu, GrTexBaseRange_t range, FxU32 startAddress,
                                                 FxU32 evenOdd, GrTexInfo *info);

#else

FX_ENTRY void FX_CALL

grTexMultibaseAddress(GrChipID_t tmu,

                      GrTexBaseRange_t range,

                      FxU32 startAddress,

                      FxU32 evenOdd,

                      GrTexInfo *info);

#endif /* DYNAHEADER */

/*

** utility texture functions

*/

#ifdef DYNAHEADER

typedef GrMipMapId_t(FX_CALL *guTexAllocateMemory_fpt)(
    GrChipID_t tmu, FxU8 odd_even_mask, int width, int height, GrTextureFormat_t fmt, GrMipMapMode_t mm_mode,
    GrLOD_t smallest_lod, GrLOD_t largest_lod, GrAspectRatio_t aspect, GrTextureClampMode_t s_clamp_mode,
    GrTextureClampMode_t t_clamp_mode, GrTextureFilterMode_t minfilter_mode, GrTextureFilterMode_t magfilter_mode,
    float lod_bias, FxBool trilinear);

#else

FX_ENTRY GrMipMapId_t FX_CALL

guTexAllocateMemory(

    GrChipID_t tmu,

    FxU8 odd_even_mask,

    int width, int height,

    GrTextureFormat_t fmt,

    GrMipMapMode_t mm_mode,

    GrLOD_t smallest_lod, GrLOD_t largest_lod,

    GrAspectRatio_t aspect,

    GrTextureClampMode_t s_clamp_mode,

    GrTextureClampMode_t t_clamp_mode,

    GrTextureFilterMode_t minfilter_mode,

    GrTextureFilterMode_t magfilter_mode,

    float lod_bias,

    FxBool trilinear

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *guTexChangeAttributes_fpt)(GrMipMapId_t mmid, int width, int height, GrTextureFormat_t fmt,
                                                   GrMipMapMode_t mm_mode, GrLOD_t smallest_lod, GrLOD_t largest_lod,
                                                   GrAspectRatio_t aspect, GrTextureClampMode_t s_clamp_mode,
                                                   GrTextureClampMode_t t_clamp_mode,
                                                   GrTextureFilterMode_t minFilterMode,
                                                   GrTextureFilterMode_t magFilterMode);

#else

FX_ENTRY FxBool FX_CALL

guTexChangeAttributes(

    GrMipMapId_t mmid,

    int width, int height,

    GrTextureFormat_t fmt,

    GrMipMapMode_t mm_mode,

    GrLOD_t smallest_lod, GrLOD_t largest_lod,

    GrAspectRatio_t aspect,

    GrTextureClampMode_t s_clamp_mode,

    GrTextureClampMode_t t_clamp_mode,

    GrTextureFilterMode_t minFilterMode,

    GrTextureFilterMode_t magFilterMode

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guTexCombineFunction_fpt)(GrChipID_t tmu, GrTextureCombineFnc_t fnc);

#else

FX_ENTRY void FX_CALL

guTexCombineFunction(

    GrChipID_t tmu,

    GrTextureCombineFnc_t fnc

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef GrMipMapId_t(FX_CALL *guTexGetCurrentMipMap_fpt)(GrChipID_t tmu);

#else

FX_ENTRY GrMipMapId_t FX_CALL

guTexGetCurrentMipMap(GrChipID_t tmu);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef GrMipMapInfo *(FX_CALL *guTexGetMipMapInfo_fpt)(GrMipMapId_t mmid);

#else

FX_ENTRY GrMipMapInfo *FX_CALL

guTexGetMipMapInfo(GrMipMapId_t mmid);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *guTexMemQueryAvail_fpt)(GrChipID_t tmu);

#else

FX_ENTRY FxU32 FX_CALL

guTexMemQueryAvail(GrChipID_t tmu);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guTexMemReset_fpt)(void);

#else

FX_ENTRY void FX_CALL

guTexMemReset(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guTexDownloadMipMap_fpt)(GrMipMapId_t mmid, const void *src, const GuNccTable *table);

#else

FX_ENTRY void FX_CALL

guTexDownloadMipMap(

    GrMipMapId_t mmid,

    const void *src,

    const GuNccTable *table

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guTexDownloadMipMapLevel_fpt)(GrMipMapId_t mmid, GrLOD_t lod, const void **src);

#else

FX_ENTRY void FX_CALL

guTexDownloadMipMapLevel(

    GrMipMapId_t mmid,

    GrLOD_t lod,

    const void **src

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guTexSource_fpt)(GrMipMapId_t id);

#else

FX_ENTRY void FX_CALL

guTexSource(GrMipMapId_t id);

#endif /* DYNAHEADER */

/*

** linear frame buffer functions

*/

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grLfbLock_fpt)(GrLock_t type, GrBuffer_t buffer, GrLfbWriteMode_t writeMode,
                                       GrOriginLocation_t origin, FxBool pixelPipeline, GrLfbInfo_t *info);

#else

FX_ENTRY FxBool FX_CALL

grLfbLock(GrLock_t type, GrBuffer_t buffer, GrLfbWriteMode_t writeMode,

          GrOriginLocation_t origin, FxBool pixelPipeline,

          GrLfbInfo_t *info);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grLfbUnlock_fpt)(GrLock_t type, GrBuffer_t buffer);

#else

FX_ENTRY FxBool FX_CALL

grLfbUnlock(GrLock_t type, GrBuffer_t buffer);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grLfbConstantAlpha_fpt)(GrAlpha_t alpha);

#else

FX_ENTRY void FX_CALL

grLfbConstantAlpha(GrAlpha_t alpha);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grLfbConstantDepth_fpt)(FxU16 depth);

#else

FX_ENTRY void FX_CALL

grLfbConstantDepth(FxU16 depth);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grLfbWriteColorSwizzle_fpt)(FxBool swizzleBytes, FxBool swapWords);

#else

FX_ENTRY void FX_CALL

grLfbWriteColorSwizzle(FxBool swizzleBytes, FxBool swapWords);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grLfbWriteColorFormat_fpt)(GrColorFormat_t colorFormat);

#else

FX_ENTRY void FX_CALL

grLfbWriteColorFormat(GrColorFormat_t colorFormat);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grLfbWriteRegion_fpt)(GrBuffer_t dst_buffer, FxU32 dst_x, FxU32 dst_y, GrLfbSrcFmt_t src_format,
                                              FxU32 src_width, FxU32 src_height, FxI32 src_stride, void *src_data);

#else

FX_ENTRY FxBool FX_CALL

grLfbWriteRegion(GrBuffer_t dst_buffer,

                 FxU32 dst_x, FxU32 dst_y,

                 GrLfbSrcFmt_t src_format,

                 FxU32 src_width, FxU32 src_height,

                 FxI32 src_stride, void *src_data);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *grLfbReadRegion_fpt)(GrBuffer_t src_buffer, FxU32 src_x, FxU32 src_y, FxU32 src_width,
                                             FxU32 src_height, FxU32 dst_stride, void *dst_data);

#else

FX_ENTRY FxBool FX_CALL

grLfbReadRegion(GrBuffer_t src_buffer,

                FxU32 src_x, FxU32 src_y,

                FxU32 src_width, FxU32 src_height,

                FxU32 dst_stride, void *dst_data);

#endif /* DYNAHEADER */

/*

**  Antialiasing Functions

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grAADrawLine_fpt)(const GrVertex *v1, const GrVertex *v2);

#else

FX_ENTRY void FX_CALL

grAADrawLine(const GrVertex *v1, const GrVertex *v2);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAADrawPoint_fpt)(const GrVertex *pt);

#else

FX_ENTRY void FX_CALL

grAADrawPoint(const GrVertex *pt);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAADrawPolygon_fpt)(const int nverts, const int ilist[], const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

grAADrawPolygon(const int nverts, const int ilist[], const GrVertex vlist[]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAADrawPolygonVertexList_fpt)(const int nverts, const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

grAADrawPolygonVertexList(const int nverts, const GrVertex vlist[]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grAADrawTriangle_fpt)(const GrVertex *a, const GrVertex *b, const GrVertex *c,
                                            FxBool ab_antialias, FxBool bc_antialias, FxBool ca_antialias);

#else

FX_ENTRY void FX_CALL

grAADrawTriangle(

    const GrVertex *a, const GrVertex *b, const GrVertex *c,

    FxBool ab_antialias, FxBool bc_antialias, FxBool ca_antialias

);

#endif /* DYNAHEADER */

/*

** glide management functions

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *grGlideInit_fpt)(void);

#else

FX_ENTRY void FX_CALL

grGlideInit(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grGlideShutdown_fpt)(void);

#else

FX_ENTRY void FX_CALL

grGlideShutdown(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grGlideGetVersion_fpt)(char version[80]);

#else

FX_ENTRY void FX_CALL

grGlideGetVersion(char version[80]);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grGlideGetState_fpt)(GrState *state);

#else

FX_ENTRY void FX_CALL

grGlideGetState(GrState *state);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grGlideSetState_fpt)(const GrState *state);

#else

FX_ENTRY void FX_CALL

grGlideSetState(const GrState *state);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grGlideShamelessPlug_fpt)(const FxBool on);

#else

FX_ENTRY void FX_CALL

grGlideShamelessPlug(const FxBool on);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *grHints_fpt)(GrHint_t hintType, FxU32 hintMask);

#else

FX_ENTRY void FX_CALL

grHints(GrHint_t hintType, FxU32 hintMask);

#endif /* DYNAHEADER */

#endif /* FX_GLIDE_NO_FUNC_PROTO */

#ifdef __cplusplus
}

#endif

/* The following include has been replaced

 * by the processed text from the header file.

 * #include <glideutl.h>

 */

/*

** Copyright (c) 1995, 3Dfx Interactive, Inc.

** All Rights Reserved.

**

** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;

** the contents of this file may not be disclosed to third parties, copied or

** duplicated in any form, in whole or in part, without the prior written

** permission of 3Dfx Interactive, Inc.

**

** RESTRICTED RIGHTS LEGEND:

** Use, duplication or disclosure by the Government is subject to restrictions

** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data

** and Computer Software clause at DFARS 252.227-7013, and/or in similar or

** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -

** rights reserved under the Copyright Laws of the United States.

**

** $Header: /cvs/kevlar.net/descent3/Main/lib/linux/dyna_glide.h,v 1.1.1.1 2003/08/26 03:58:12 kevinb Exp $

** $Log: dyna_glide.h,v $
** Revision 1.1.1.1  2003/08/26 03:58:12  kevinb
** initial 1.5 import
**
 *
 * 2     7/14/99 6:43p Jeff
 * change to load module globally
 *
 * 1     6/22/99 7:02p Jeff
 *
 * 4     2/19/99 11:49a Jason
 * added more resolutions to glide
 *
 * 3     7/06/98 7:16p Jeff
 * LoadGlideDLL no longer windows specific, calls module library
 *
 * 3     7/06/98 10:46a Jeff
 * LoadGlideDLL uses the module library so it isn't Windows specific
 *
 * 2     3/02/98 5:15p Jason
 * added support for dynamically loadable dlls
 *
 * 1     3/02/98 5:15p Jason
 * header file for dynamically loadable dlls

 *

 * 4     3/05/97 9:36p Jdt

 * Removed guFbWriteRegion added guEncodeRLE16

 *

 * 3     1/16/97 3:45p Dow

 * Embedded fn protos in ifndef FX_GLIDE_NO_FUNC_PROTO

*/

/* Glide Utility routines */

#ifndef __GLIDEUTL_H__

#define __GLIDEUTL_H__

#ifdef __cplusplus

extern "C" {

#endif

#ifndef FX_GLIDE_NO_FUNC_PROTO

/*

** rendering functions

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *guAADrawTriangleWithClip_fpt)(const GrVertex *a, const GrVertex *b, const GrVertex *c);

#else

FX_ENTRY void FX_CALL

guAADrawTriangleWithClip(const GrVertex *a,
                         const GrVertex

                             *b,
                         const GrVertex *c);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guDrawTriangleWithClip_fpt)(const GrVertex *a, const GrVertex *b, const GrVertex *c);

#else

FX_ENTRY void FX_CALL

guDrawTriangleWithClip(

    const GrVertex *a,

    const GrVertex *b,

    const GrVertex *c

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guDrawPolygonVertexListWithClip_fpt)(int nverts, const GrVertex vlist[]);

#else

FX_ENTRY void FX_CALL

guDrawPolygonVertexListWithClip(int nverts, const GrVertex vlist[]);

#endif /* DYNAHEADER */

/*

** hi-level rendering utility functions

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *guAlphaSource_fpt)(GrAlphaSource_t mode);

#else

FX_ENTRY void FX_CALL

guAlphaSource(GrAlphaSource_t mode);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guColorCombineFunction_fpt)(GrColorCombineFnc_t fnc);

#else

FX_ENTRY void FX_CALL

guColorCombineFunction(GrColorCombineFnc_t fnc);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guFbReadRegion_fpt)(const int src_x, const int src_y, const int w, const int h, const void *dst,
                                          const int strideInBytes);

#else

FX_ENTRY void FX_CALL

guFbReadRegion(

    const int src_x, const int src_y,

    const int w, const int h, const void *dst,

    const int strideInBytes

);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef int(FX_CALL *guEncodeRLE16_fpt)(void *dst, void *src, FxU32 width, FxU32 height);

#else

FX_ENTRY int FX_CALL

guEncodeRLE16(void *dst,

              void *src,

              FxU32 width,

              FxU32 height);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU16 *(FX_CALL *guTexCreateColorMipMap_fpt)(void);

#else

FX_ENTRY FxU16 *FX_CALL

guTexCreateColorMipMap(void);

#endif /* DYNAHEADER */

#if (GLIDE_PLATFORM & GLIDE_SST_SIM)

/*

** movie capture stuff

*/

#ifdef DYNAHEADER

typedef void(FX_CALL *guMovieStart_fpt)(void);

#else

FX_ENTRY void

    FX_CALL
    guMovieStart(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guMovieStop_fpt)(void);

#else

FX_ENTRY void

    FX_CALL
    guMovieStop(void);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guMovieSetName_fpt)(const char *name);

#else

FX_ENTRY void

    FX_CALL
    guMovieSetName(const char *name);

#endif /* DYNAHEADER */

#endif

/*

** fog stuff

*/

#ifdef DYNAHEADER

typedef float(FX_CALL *guFogTableIndexToW_fpt)(int i);

#else

FX_ENTRY float FX_CALL

guFogTableIndexToW(int i);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guFogGenerateExp_fpt)(GrFog_t fogtable[GR_FOG_TABLE_SIZE], float density);

#else

FX_ENTRY void FX_CALL

guFogGenerateExp(GrFog_t fogtable[GR_FOG_TABLE_SIZE], float density);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guFogGenerateExp2_fpt)(GrFog_t fogtable[GR_FOG_TABLE_SIZE], float density);

#else

FX_ENTRY void FX_CALL

guFogGenerateExp2(GrFog_t fogtable[GR_FOG_TABLE_SIZE], float density);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef void(FX_CALL *guFogGenerateLinear_fpt)(GrFog_t fogtable[GR_FOG_TABLE_SIZE], float nearZ, float farZ);

#else

FX_ENTRY void FX_CALL

guFogGenerateLinear(

    GrFog_t fogtable[GR_FOG_TABLE_SIZE],

    float nearZ, float farZ);

#endif /* DYNAHEADER */

/*

** endian stuff

*/

#ifdef DYNAHEADER

typedef FxU32(FX_CALL *guEndianSwapWords_fpt)(FxU32 value);

#else

FX_ENTRY FxU32 FX_CALL

guEndianSwapWords(FxU32 value);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxU16(FX_CALL *guEndianSwapBytes_fpt)(FxU16 value);

#else

FX_ENTRY FxU16 FX_CALL

guEndianSwapBytes(FxU16 value);

#endif /* DYNAHEADER */

/*

** hi-level texture manipulation tools.

*/

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *gu3dfGetInfo_fpt)(const char *filename, Gu3dfInfo *info);

#else

FX_ENTRY FxBool FX_CALL

gu3dfGetInfo(const char *filename, Gu3dfInfo *info);

#endif /* DYNAHEADER */

#ifdef DYNAHEADER

typedef FxBool(FX_CALL *gu3dfLoad_fpt)(const char *filename, Gu3dfInfo *data);

#else

FX_ENTRY FxBool FX_CALL

gu3dfLoad(const char *filename, Gu3dfInfo *data);

#endif /* DYNAHEADER */

#endif /* FX_GLIDE_NO_FUNC_PROTO */

/*

** Glide structure-less primitive handling

*/

#define GU_PRIM_MAX_VERTICES 100

/* GMT: BUG what the hell is this!!! */

#if 0

extern GrVertex   __gu_prim_vertex_array[GU_PRIM_MAX_VERTICES];

extern GrVertex * __gu_prim_current_vtx;

extern int        __gu_prim_num_verts;

#define guPolygonBegin()                                                                                               \
  __gu_prim_current_vtx = &__gu_prim_vertex_array[0];                                                                  \
  __gu_prim_num_verts = 0;

#define guPolygonEnd()

#ifdef GLIDE_DEBUG

#define guPolygonDraw() grDrawPolygonVertexList(__gu_prim_num_verts, __gu_prim_vertex_array);

#define guPolygonDrawClipped() guDrawPolygonVertexListWithClip(__gu_prim_num_verts, __gu_prim_vertex_array);

#else

#define guPolygonDraw() if (__gu_prim_num_verts > GU_VTX_MAX_VERTICES) \

                            grErrorCallback( "guPolygonEnd (GLIDE.H) : GU_VTX_MAX_VERTICES exceed", FXTRUE ); \

                          if ( __gu_prim_num_verts < 3 ) \

                            grErrorCallback( "guPolygonEnd (GLIDE.H) : num_verts< 3", FXTRUE ); \

                          grDrawPolygonVertexList( __gu_prim_num_verts, __gu_prim_vertex_array );

#define guPolygonDrawClipped() if (__gu_prim_num_verts > GU_VTX_MAX_VERTICES) \

                                   grErrorCallback( "guPolygonEnd (GLIDE.H) : GU_VTX_MAX_VERTICES exceed", FXTRUE ); \

                                 if ( __gu_prim_num_verts < 3 ) \

                                   grErrorCallback( "guPolygonEnd (GLIDE.H) : num_verts< 3", FXTRUE ); \

                                 guDrawPolygonVertexListWithClip( __gu_prim_num_verts, __gu_prim_vertex_array );

#endif

#define guVertexBegin()

#define guVertexXY(x, y)                                                                                               \
  __gu_prim_current_vtx->x = x;                                                                                        \
  __gu_prim_current_vtx->y = y;

#define guVertexXYZ(x, y, z)                                                                                           \
  __gu_prim_current_vtx->x = x;                                                                                        \
  __gu_prim_current_vtx->y = y;                                                                                        \
  __gu_prim_current_vtx->ooz = z;

#define guVertexXYW(x, y, w)                                                                                           \
  __gu_prim_current_vtx->x = x;                                                                                        \
  __gu_prim_current_vtx->y = y;                                                                                        \
  __gu_prim_current_vtx->oow = w;

#define guVertexRGB(r, g, b)                                                                                           \
  __gu_prim_current_vtx->r = r;                                                                                        \
  __gu_prim_current_vtx->g = g;                                                                                        \
  __gu_prim_current_vtx->b = b;

#define guVertexRGBA(r, g, b, a)                                                                                       \
  __gu_prim_current_vtx->r = r;                                                                                        \
  __gu_prim_current_vtx->g = g;                                                                                        \
  __gu_prim_current_vtx->b = b;                                                                                        \
  __gu_prim_current_vtx->a = a;

#define guVertexA(a) __gu_prim_current_vtx->a = a;

#define guVertexSTW0(c, s, t, w) __gu_prim_current_vtx->tmuvtx[(c)]->sow = s; \

                                      __gu_prim_current_vtx->tmuvtx[(c)]->tow = t; \

                                      __gu_prim_current_vtx->tmuvtx[(c)]->oow = w;

#define guVertexEnd()                                                                                                  \
  __gu_prim_current_vtx++;                                                                                             \
  __gu_prim_num_verts++;

#endif

#ifdef __cplusplus
}

#endif

#endif /* __GLIDEUTL_H__ */

#ifdef DYNAHEADER_CREATE_STORAGE

#include "module.h"
static module glideDLLInst;

ConvertAndDownloadRle_fpt ConvertAndDownloadRle = NULL;

grAADrawLine_fpt grAADrawLine = NULL;

grAADrawPoint_fpt grAADrawPoint = NULL;

grAADrawPolygon_fpt grAADrawPolygon = NULL;

grAADrawPolygonVertexList_fpt grAADrawPolygonVertexList = NULL;

grAADrawTriangle_fpt grAADrawTriangle = NULL;

grAlphaBlendFunction_fpt grAlphaBlendFunction = NULL;

grAlphaCombine_fpt grAlphaCombine = NULL;

grAlphaControlsITRGBLighting_fpt grAlphaControlsITRGBLighting = NULL;

grAlphaTestFunction_fpt grAlphaTestFunction = NULL;

grAlphaTestReferenceValue_fpt grAlphaTestReferenceValue = NULL;

grBufferClear_fpt grBufferClear = NULL;

grBufferNumPending_fpt grBufferNumPending = NULL;

grBufferSwap_fpt grBufferSwap = NULL;

grCheckForRoom_fpt grCheckForRoom = NULL;

grChromakeyMode_fpt grChromakeyMode = NULL;

grChromakeyValue_fpt grChromakeyValue = NULL;

grClipWindow_fpt grClipWindow = NULL;

grColorCombine_fpt grColorCombine = NULL;

grColorMask_fpt grColorMask = NULL;

grConstantColorValue_fpt grConstantColorValue = NULL;

grConstantColorValue4_fpt grConstantColorValue4 = NULL;

grCullMode_fpt grCullMode = NULL;

grDepthBiasLevel_fpt grDepthBiasLevel = NULL;

grDepthBufferFunction_fpt grDepthBufferFunction = NULL;

grDepthBufferMode_fpt grDepthBufferMode = NULL;

grDepthMask_fpt grDepthMask = NULL;

grDisableAllEffects_fpt grDisableAllEffects = NULL;

grDitherMode_fpt grDitherMode = NULL;

grDrawLine_fpt grDrawLine = NULL;

grDrawPlanarPolygon_fpt grDrawPlanarPolygon = NULL;

grDrawPlanarPolygonVertexList_fpt grDrawPlanarPolygonVertexList = NULL;

grDrawPoint_fpt grDrawPoint = NULL;

grDrawPolygon_fpt grDrawPolygon = NULL;

grDrawPolygonVertexList_fpt grDrawPolygonVertexList = NULL;

grDrawTriangle_fpt grDrawTriangle = NULL;

grErrorSetCallback_fpt grErrorSetCallback = NULL;

grFogColorValue_fpt grFogColorValue = NULL;

grFogMode_fpt grFogMode = NULL;

grFogTable_fpt grFogTable = NULL;

grGammaCorrectionValue_fpt grGammaCorrectionValue = NULL;

grGlideGetState_fpt grGlideGetState = NULL;

grGlideGetVersion_fpt grGlideGetVersion = NULL;

grGlideInit_fpt grGlideInit = NULL;

grGlideSetState_fpt grGlideSetState = NULL;

grGlideShamelessPlug_fpt grGlideShamelessPlug = NULL;

grGlideShutdown_fpt grGlideShutdown = NULL;

grHints_fpt grHints = NULL;

grLfbConstantAlpha_fpt grLfbConstantAlpha = NULL;

grLfbConstantDepth_fpt grLfbConstantDepth = NULL;

grLfbLock_fpt grLfbLock = NULL;

grLfbReadRegion_fpt grLfbReadRegion = NULL;

grLfbUnlock_fpt grLfbUnlock = NULL;

grLfbWriteColorFormat_fpt grLfbWriteColorFormat = NULL;

grLfbWriteColorSwizzle_fpt grLfbWriteColorSwizzle = NULL;

grLfbWriteRegion_fpt grLfbWriteRegion = NULL;

grRenderBuffer_fpt grRenderBuffer = NULL;

grResetTriStats_fpt grResetTriStats = NULL;

grSplash_fpt grSplash = NULL;

grSstControl_fpt grSstControl = NULL;

grSstIdle_fpt grSstIdle = NULL;

grSstIsBusy_fpt grSstIsBusy = NULL;

grSstOrigin_fpt grSstOrigin = NULL;

grSstPerfStats_fpt grSstPerfStats = NULL;

grSstQueryBoards_fpt grSstQueryBoards = NULL;

grSstQueryHardware_fpt grSstQueryHardware = NULL;

grSstResetPerfStats_fpt grSstResetPerfStats = NULL;

grSstScreenHeight_fpt grSstScreenHeight = NULL;

grSstScreenWidth_fpt grSstScreenWidth = NULL;

grSstSelect_fpt grSstSelect = NULL;

grSstStatus_fpt grSstStatus = NULL;

grSstVRetraceOn_fpt grSstVRetraceOn = NULL;

grSstVideoLine_fpt grSstVideoLine = NULL;

grSstWinClose_fpt grSstWinClose = NULL;

grSstWinOpen_fpt grSstWinOpen = NULL;

grTexCalcMemRequired_fpt grTexCalcMemRequired = NULL;

grTexClampMode_fpt grTexClampMode = NULL;

grTexCombine_fpt grTexCombine = NULL;

grTexCombineFunction_fpt grTexCombineFunction = NULL;

grTexDetailControl_fpt grTexDetailControl = NULL;

grTexDownloadMipMap_fpt grTexDownloadMipMap = NULL;

grTexDownloadMipMapLevel_fpt grTexDownloadMipMapLevel = NULL;

grTexDownloadMipMapLevelPartial_fpt grTexDownloadMipMapLevelPartial = NULL;

grTexDownloadTable_fpt grTexDownloadTable = NULL;

grTexDownloadTablePartial_fpt grTexDownloadTablePartial = NULL;

grTexFilterMode_fpt grTexFilterMode = NULL;

grTexLodBiasValue_fpt grTexLodBiasValue = NULL;

grTexMaxAddress_fpt grTexMaxAddress = NULL;

grTexMinAddress_fpt grTexMinAddress = NULL;

grTexMipMapMode_fpt grTexMipMapMode = NULL;

grTexMultibase_fpt grTexMultibase = NULL;

grTexMultibaseAddress_fpt grTexMultibaseAddress = NULL;

grTexNCCTable_fpt grTexNCCTable = NULL;

grTexSource_fpt grTexSource = NULL;

grTexTextureMemRequired_fpt grTexTextureMemRequired = NULL;

grTriStats_fpt grTriStats = NULL;

gu3dfGetInfo_fpt gu3dfGetInfo = NULL;

gu3dfLoad_fpt gu3dfLoad = NULL;

guAADrawTriangleWithClip_fpt guAADrawTriangleWithClip = NULL;

guAlphaSource_fpt guAlphaSource = NULL;

guColorCombineFunction_fpt guColorCombineFunction = NULL;

guDrawPolygonVertexListWithClip_fpt guDrawPolygonVertexListWithClip = NULL;

guDrawTriangleWithClip_fpt guDrawTriangleWithClip = NULL;

guEncodeRLE16_fpt guEncodeRLE16 = NULL;

guEndianSwapBytes_fpt guEndianSwapBytes = NULL;

guEndianSwapWords_fpt guEndianSwapWords = NULL;
guFbReadRegion_fpt guFbReadRegion = NULL;
guFogGenerateExp_fpt guFogGenerateExp = NULL;
guFogGenerateExp2_fpt guFogGenerateExp2 = NULL;
guFogGenerateLinear_fpt guFogGenerateLinear = NULL;
guFogTableIndexToW_fpt guFogTableIndexToW = NULL;
guTexAllocateMemory_fpt guTexAllocateMemory = NULL;
guTexChangeAttributes_fpt guTexChangeAttributes = NULL;
guTexCombineFunction_fpt guTexCombineFunction = NULL;
guTexCreateColorMipMap_fpt guTexCreateColorMipMap = NULL;
guTexDownloadMipMap_fpt guTexDownloadMipMap = NULL;
guTexDownloadMipMapLevel_fpt guTexDownloadMipMapLevel = NULL;
guTexGetCurrentMipMap_fpt guTexGetCurrentMipMap = NULL;
guTexGetMipMapInfo_fpt guTexGetMipMapInfo = NULL;
guTexMemQueryAvail_fpt guTexMemQueryAvail = NULL;
guTexMemReset_fpt guTexMemReset = NULL;
guTexSource_fpt guTexSource = NULL;

module *LoadGlideDLL() {
  if (!mod_LoadModule(&glideDLLInst, "libglide2x.so", MODF_LAZY | MODF_GLOBAL)) {
    int err = mod_GetLastError();
    return NULL;
  }

#if defined(WIN32)
  ConvertAndDownloadRle = (ConvertAndDownloadRle_fpt)mod_GetSymbol(&glideDLLInst, "ConvertAndDownloadRle", 64);

  if (!ConvertAndDownloadRle)
    goto glide_load_dll_error;
#endif
  grAADrawLine = (grAADrawLine_fpt)mod_GetSymbol(&glideDLLInst, "grAADrawLine", 8);

  if (!grAADrawLine)
    goto glide_load_dll_error;

  grAADrawPoint = (grAADrawPoint_fpt)mod_GetSymbol(&glideDLLInst, "grAADrawPoint", 4);

  if (!grAADrawPoint)
    goto glide_load_dll_error;

  grAADrawPolygon = (grAADrawPolygon_fpt)mod_GetSymbol(&glideDLLInst, "grAADrawPolygon", 12);

  if (!grAADrawPolygon)
    goto glide_load_dll_error;

  grAADrawPolygonVertexList =
      (grAADrawPolygonVertexList_fpt)mod_GetSymbol(&glideDLLInst, "grAADrawPolygonVertexList", 8);

  if (!grAADrawPolygonVertexList)
    goto glide_load_dll_error;

  grAADrawTriangle = (grAADrawTriangle_fpt)mod_GetSymbol(&glideDLLInst, "grAADrawTriangle", 24);

  if (!grAADrawTriangle)
    goto glide_load_dll_error;

  grAlphaBlendFunction = (grAlphaBlendFunction_fpt)mod_GetSymbol(&glideDLLInst, "grAlphaBlendFunction", 16);

  if (!grAlphaBlendFunction)
    goto glide_load_dll_error;

  grAlphaCombine = (grAlphaCombine_fpt)mod_GetSymbol(&glideDLLInst, "grAlphaCombine", 20);

  if (!grAlphaCombine)
    goto glide_load_dll_error;

  grAlphaControlsITRGBLighting =
      (grAlphaControlsITRGBLighting_fpt)mod_GetSymbol(&glideDLLInst, "grAlphaControlsITRGBLighting", 4);

  if (!grAlphaControlsITRGBLighting)
    goto glide_load_dll_error;

  grAlphaTestFunction = (grAlphaTestFunction_fpt)mod_GetSymbol(&glideDLLInst, "grAlphaTestFunction", 4);

  if (!grAlphaTestFunction)
    goto glide_load_dll_error;

  grAlphaTestReferenceValue =
      (grAlphaTestReferenceValue_fpt)mod_GetSymbol(&glideDLLInst, "grAlphaTestReferenceValue", 4);

  if (!grAlphaTestReferenceValue)
    goto glide_load_dll_error;

  grBufferClear = (grBufferClear_fpt)mod_GetSymbol(&glideDLLInst, "grBufferClear", 12);

  if (!grBufferClear)
    goto glide_load_dll_error;

  grBufferNumPending = (grBufferNumPending_fpt)mod_GetSymbol(&glideDLLInst, "grBufferNumPending", 0);

  if (!grBufferNumPending)
    goto glide_load_dll_error;

  grBufferSwap = (grBufferSwap_fpt)mod_GetSymbol(&glideDLLInst, "grBufferSwap", 4);

  if (!grBufferSwap)
    goto glide_load_dll_error;

  grCheckForRoom = (grCheckForRoom_fpt)mod_GetSymbol(&glideDLLInst, "grCheckForRoom", 4);

  if (!grCheckForRoom)
    goto glide_load_dll_error;

  grChromakeyMode = (grChromakeyMode_fpt)mod_GetSymbol(&glideDLLInst, "grChromakeyMode", 4);

  if (!grChromakeyMode)
    goto glide_load_dll_error;

  grChromakeyValue = (grChromakeyValue_fpt)mod_GetSymbol(&glideDLLInst, "grChromakeyValue", 4);

  if (!grChromakeyValue)
    goto glide_load_dll_error;

  grClipWindow = (grClipWindow_fpt)mod_GetSymbol(&glideDLLInst, "grClipWindow", 16);

  if (!grClipWindow)
    goto glide_load_dll_error;

  grColorCombine = (grColorCombine_fpt)mod_GetSymbol(&glideDLLInst, "grColorCombine", 20);

  if (!grColorCombine)
    goto glide_load_dll_error;

  grColorMask = (grColorMask_fpt)mod_GetSymbol(&glideDLLInst, "grColorMask", 8);

  if (!grColorMask)
    goto glide_load_dll_error;

  grConstantColorValue = (grConstantColorValue_fpt)mod_GetSymbol(&glideDLLInst, "grConstantColorValue", 4);

  if (!grConstantColorValue)
    goto glide_load_dll_error;

  grConstantColorValue4 = (grConstantColorValue4_fpt)mod_GetSymbol(&glideDLLInst, "grConstantColorValue4", 16);

  if (!grConstantColorValue4)
    goto glide_load_dll_error;

  grCullMode = (grCullMode_fpt)mod_GetSymbol(&glideDLLInst, "grCullMode", 4);

  if (!grCullMode)
    goto glide_load_dll_error;

  grDepthBiasLevel = (grDepthBiasLevel_fpt)mod_GetSymbol(&glideDLLInst, "grDepthBiasLevel", 4);

  if (!grDepthBiasLevel)
    goto glide_load_dll_error;

  grDepthBufferFunction = (grDepthBufferFunction_fpt)mod_GetSymbol(&glideDLLInst, "grDepthBufferFunction", 4);

  if (!grDepthBufferFunction)
    goto glide_load_dll_error;

  grDepthBufferMode = (grDepthBufferMode_fpt)mod_GetSymbol(&glideDLLInst, "grDepthBufferMode", 4);

  if (!grDepthBufferMode)
    goto glide_load_dll_error;

  grDepthMask = (grDepthMask_fpt)mod_GetSymbol(&glideDLLInst, "grDepthMask", 4);

  if (!grDepthMask)
    goto glide_load_dll_error;

  grDisableAllEffects = (grDisableAllEffects_fpt)mod_GetSymbol(&glideDLLInst, "grDisableAllEffects", 0);

  if (!grDisableAllEffects)
    goto glide_load_dll_error;

  grDitherMode = (grDitherMode_fpt)mod_GetSymbol(&glideDLLInst, "grDitherMode", 4);

  if (!grDitherMode)
    goto glide_load_dll_error;

  grDrawLine = (grDrawLine_fpt)mod_GetSymbol(&glideDLLInst, "grDrawLine", 8);

  if (!grDrawLine)
    goto glide_load_dll_error;

  grDrawPlanarPolygon = (grDrawPlanarPolygon_fpt)mod_GetSymbol(&glideDLLInst, "grDrawPlanarPolygon", 12);

  if (!grDrawPlanarPolygon)
    goto glide_load_dll_error;

  grDrawPlanarPolygonVertexList =
      (grDrawPlanarPolygonVertexList_fpt)mod_GetSymbol(&glideDLLInst, "grDrawPlanarPolygonVertexList", 8);

  if (!grDrawPlanarPolygonVertexList)
    goto glide_load_dll_error;

  grDrawPoint = (grDrawPoint_fpt)mod_GetSymbol(&glideDLLInst, "grDrawPoint", 4);

  if (!grDrawPoint)
    goto glide_load_dll_error;

  grDrawPolygon = (grDrawPolygon_fpt)mod_GetSymbol(&glideDLLInst, "grDrawPolygon", 12);

  if (!grDrawPolygon)
    goto glide_load_dll_error;

  grDrawPolygonVertexList = (grDrawPolygonVertexList_fpt)mod_GetSymbol(&glideDLLInst, "grDrawPolygonVertexList", 8);

  if (!grDrawPolygonVertexList)
    goto glide_load_dll_error;

  grDrawTriangle = (grDrawTriangle_fpt)mod_GetSymbol(&glideDLLInst, "grDrawTriangle", 12);

  if (!grDrawTriangle)
    goto glide_load_dll_error;

  grErrorSetCallback = (grErrorSetCallback_fpt)mod_GetSymbol(&glideDLLInst, "grErrorSetCallback", 4);

  if (!grErrorSetCallback)
    goto glide_load_dll_error;

  grFogColorValue = (grFogColorValue_fpt)mod_GetSymbol(&glideDLLInst, "grFogColorValue", 4);

  if (!grFogColorValue)
    goto glide_load_dll_error;

  grFogMode = (grFogMode_fpt)mod_GetSymbol(&glideDLLInst, "grFogMode", 4);

  if (!grFogMode)
    goto glide_load_dll_error;

  grFogTable = (grFogTable_fpt)mod_GetSymbol(&glideDLLInst, "grFogTable", 4);

  if (!grFogTable)
    goto glide_load_dll_error;

  grGammaCorrectionValue = (grGammaCorrectionValue_fpt)mod_GetSymbol(&glideDLLInst, "grGammaCorrectionValue", 4);

  if (!grGammaCorrectionValue)
    goto glide_load_dll_error;

  grGlideGetState = (grGlideGetState_fpt)mod_GetSymbol(&glideDLLInst, "grGlideGetState", 4);

  if (!grGlideGetState)
    goto glide_load_dll_error;

  grGlideGetVersion = (grGlideGetVersion_fpt)mod_GetSymbol(&glideDLLInst, "grGlideGetVersion", 4);

  if (!grGlideGetVersion)
    goto glide_load_dll_error;

  grGlideInit = (grGlideInit_fpt)mod_GetSymbol(&glideDLLInst, "grGlideInit", 0);

  if (!grGlideInit)
    goto glide_load_dll_error;

  grGlideSetState = (grGlideSetState_fpt)mod_GetSymbol(&glideDLLInst, "grGlideSetState", 4);

  if (!grGlideSetState)
    goto glide_load_dll_error;

  grGlideShamelessPlug = (grGlideShamelessPlug_fpt)mod_GetSymbol(&glideDLLInst, "grGlideShamelessPlug", 4);

  if (!grGlideShamelessPlug)
    goto glide_load_dll_error;

  grGlideShutdown = (grGlideShutdown_fpt)mod_GetSymbol(&glideDLLInst, "grGlideShutdown", 0);

  if (!grGlideShutdown)
    goto glide_load_dll_error;

  grHints = (grHints_fpt)mod_GetSymbol(&glideDLLInst, "grHints", 8);

  if (!grHints)
    goto glide_load_dll_error;

  grLfbConstantAlpha = (grLfbConstantAlpha_fpt)mod_GetSymbol(&glideDLLInst, "grLfbConstantAlpha", 4);

  if (!grLfbConstantAlpha)
    goto glide_load_dll_error;

  grLfbConstantDepth = (grLfbConstantDepth_fpt)mod_GetSymbol(&glideDLLInst, "grLfbConstantDepth", 4);

  if (!grLfbConstantDepth)
    goto glide_load_dll_error;

  grLfbLock = (grLfbLock_fpt)mod_GetSymbol(&glideDLLInst, "grLfbLock", 24);

  if (!grLfbLock)
    goto glide_load_dll_error;

  grLfbReadRegion = (grLfbReadRegion_fpt)mod_GetSymbol(&glideDLLInst, "grLfbReadRegion", 28);

  if (!grLfbReadRegion)
    goto glide_load_dll_error;

  grLfbUnlock = (grLfbUnlock_fpt)mod_GetSymbol(&glideDLLInst, "grLfbUnlock", 8);

  if (!grLfbUnlock)
    goto glide_load_dll_error;

  grLfbWriteColorFormat = (grLfbWriteColorFormat_fpt)mod_GetSymbol(&glideDLLInst, "grLfbWriteColorFormat", 4);

  if (!grLfbWriteColorFormat)
    goto glide_load_dll_error;

  grLfbWriteColorSwizzle = (grLfbWriteColorSwizzle_fpt)mod_GetSymbol(&glideDLLInst, "grLfbWriteColorSwizzle", 8);

  if (!grLfbWriteColorSwizzle)
    goto glide_load_dll_error;

  grLfbWriteRegion = (grLfbWriteRegion_fpt)mod_GetSymbol(&glideDLLInst, "grLfbWriteRegion", 32);

  if (!grLfbWriteRegion)
    goto glide_load_dll_error;

  grRenderBuffer = (grRenderBuffer_fpt)mod_GetSymbol(&glideDLLInst, "grRenderBuffer", 4);

  if (!grRenderBuffer)
    goto glide_load_dll_error;

  grResetTriStats = (grResetTriStats_fpt)mod_GetSymbol(&glideDLLInst, "grResetTriStats", 0);

  if (!grResetTriStats)
    goto glide_load_dll_error;

  grSplash = (grSplash_fpt)mod_GetSymbol(&glideDLLInst, "grSplash", 20);

  if (!grSplash)
    goto glide_load_dll_error;

  grSstControl = (grSstControl_fpt)mod_GetSymbol(&glideDLLInst, "grSstControl", 4);

  if (!grSstControl)
    goto glide_load_dll_error;

  grSstIdle = (grSstIdle_fpt)mod_GetSymbol(&glideDLLInst, "grSstIdle", 0);

  if (!grSstIdle)
    goto glide_load_dll_error;

  grSstIsBusy = (grSstIsBusy_fpt)mod_GetSymbol(&glideDLLInst, "grSstIsBusy", 0);

  if (!grSstIsBusy)
    goto glide_load_dll_error;

  grSstOrigin = (grSstOrigin_fpt)mod_GetSymbol(&glideDLLInst, "grSstOrigin", 4);

  if (!grSstOrigin)
    goto glide_load_dll_error;

  grSstPerfStats = (grSstPerfStats_fpt)mod_GetSymbol(&glideDLLInst, "grSstPerfStats", 4);

  if (!grSstPerfStats)
    goto glide_load_dll_error;

  grSstQueryBoards = (grSstQueryBoards_fpt)mod_GetSymbol(&glideDLLInst, "grSstQueryBoards", 4);

  if (!grSstQueryBoards)
    goto glide_load_dll_error;

  grSstQueryHardware = (grSstQueryHardware_fpt)mod_GetSymbol(&glideDLLInst, "grSstQueryHardware", 4);

  if (!grSstQueryHardware)
    goto glide_load_dll_error;

  grSstResetPerfStats = (grSstResetPerfStats_fpt)mod_GetSymbol(&glideDLLInst, "grSstResetPerfStats", 0);

  if (!grSstResetPerfStats)
    goto glide_load_dll_error;

  grSstScreenHeight = (grSstScreenHeight_fpt)mod_GetSymbol(&glideDLLInst, "grSstScreenHeight", 0);

  if (!grSstScreenHeight)
    goto glide_load_dll_error;

  grSstScreenWidth = (grSstScreenWidth_fpt)mod_GetSymbol(&glideDLLInst, "grSstScreenWidth", 0);

  if (!grSstScreenWidth)
    goto glide_load_dll_error;

  grSstSelect = (grSstSelect_fpt)mod_GetSymbol(&glideDLLInst, "grSstSelect", 4);

  if (!grSstSelect)
    goto glide_load_dll_error;

  grSstStatus = (grSstStatus_fpt)mod_GetSymbol(&glideDLLInst, "grSstStatus", 0);

  if (!grSstStatus)
    goto glide_load_dll_error;

  grSstVRetraceOn = (grSstVRetraceOn_fpt)mod_GetSymbol(&glideDLLInst, "grSstVRetraceOn", 0);

  if (!grSstVRetraceOn)
    goto glide_load_dll_error;

  grSstVideoLine = (grSstVideoLine_fpt)mod_GetSymbol(&glideDLLInst, "grSstVideoLine", 0);

  if (!grSstVideoLine)
    goto glide_load_dll_error;

  grSstWinClose = (grSstWinClose_fpt)mod_GetSymbol(&glideDLLInst, "grSstWinClose", 0);

  if (!grSstWinClose)
    goto glide_load_dll_error;

  grSstWinOpen = (grSstWinOpen_fpt)mod_GetSymbol(&glideDLLInst, "grSstWinOpen", 28);

  if (!grSstWinOpen)
    goto glide_load_dll_error;

  grTexCalcMemRequired = (grTexCalcMemRequired_fpt)mod_GetSymbol(&glideDLLInst, "grTexCalcMemRequired", 16);

  if (!grTexCalcMemRequired)
    goto glide_load_dll_error;

  grTexClampMode = (grTexClampMode_fpt)mod_GetSymbol(&glideDLLInst, "grTexClampMode", 12);

  if (!grTexClampMode)
    goto glide_load_dll_error;

  grTexCombine = (grTexCombine_fpt)mod_GetSymbol(&glideDLLInst, "grTexCombine", 28);

  if (!grTexCombine)
    goto glide_load_dll_error;

  grTexCombineFunction = (grTexCombineFunction_fpt)mod_GetSymbol(&glideDLLInst, "grTexCombineFunction", 8);

  if (!grTexCombineFunction)
    goto glide_load_dll_error;

  grTexDetailControl = (grTexDetailControl_fpt)mod_GetSymbol(&glideDLLInst, "grTexDetailControl", 16);

  if (!grTexDetailControl)
    goto glide_load_dll_error;

  grTexDownloadMipMap = (grTexDownloadMipMap_fpt)mod_GetSymbol(&glideDLLInst, "grTexDownloadMipMap", 16);

  if (!grTexDownloadMipMap)
    goto glide_load_dll_error;

  grTexDownloadMipMapLevel = (grTexDownloadMipMapLevel_fpt)mod_GetSymbol(&glideDLLInst, "grTexDownloadMipMapLevel", 32);

  if (!grTexDownloadMipMapLevel)
    goto glide_load_dll_error;

  grTexDownloadMipMapLevelPartial =
      (grTexDownloadMipMapLevelPartial_fpt)mod_GetSymbol(&glideDLLInst, "grTexDownloadMipMapLevelPartial", 40);

  if (!grTexDownloadMipMapLevelPartial)
    goto glide_load_dll_error;

  grTexDownloadTable = (grTexDownloadTable_fpt)mod_GetSymbol(&glideDLLInst, "grTexDownloadTable", 12);

  if (!grTexDownloadTable)
    goto glide_load_dll_error;

  grTexDownloadTablePartial =
      (grTexDownloadTablePartial_fpt)mod_GetSymbol(&glideDLLInst, "grTexDownloadTablePartial", 20);

  if (!grTexDownloadTablePartial)
    goto glide_load_dll_error;

  grTexFilterMode = (grTexFilterMode_fpt)mod_GetSymbol(&glideDLLInst, "grTexFilterMode", 12);

  if (!grTexFilterMode)
    goto glide_load_dll_error;

  grTexLodBiasValue = (grTexLodBiasValue_fpt)mod_GetSymbol(&glideDLLInst, "grTexLodBiasValue", 8);

  if (!grTexLodBiasValue)
    goto glide_load_dll_error;

  grTexMaxAddress = (grTexMaxAddress_fpt)mod_GetSymbol(&glideDLLInst, "grTexMaxAddress", 4);

  if (!grTexMaxAddress)
    goto glide_load_dll_error;

  grTexMinAddress = (grTexMinAddress_fpt)mod_GetSymbol(&glideDLLInst, "grTexMinAddress", 4);

  if (!grTexMinAddress)
    goto glide_load_dll_error;

  grTexMipMapMode = (grTexMipMapMode_fpt)mod_GetSymbol(&glideDLLInst, "grTexMipMapMode", 12);

  if (!grTexMipMapMode)
    goto glide_load_dll_error;

  grTexMultibase = (grTexMultibase_fpt)mod_GetSymbol(&glideDLLInst, "grTexMultibase", 8);

  if (!grTexMultibase)
    goto glide_load_dll_error;

  grTexMultibaseAddress = (grTexMultibaseAddress_fpt)mod_GetSymbol(&glideDLLInst, "grTexMultibaseAddress", 20);

  if (!grTexMultibaseAddress)
    goto glide_load_dll_error;

  grTexNCCTable = (grTexNCCTable_fpt)mod_GetSymbol(&glideDLLInst, "grTexNCCTable", 8);

  if (!grTexNCCTable)
    goto glide_load_dll_error;

  grTexSource = (grTexSource_fpt)mod_GetSymbol(&glideDLLInst, "grTexSource", 16);

  if (!grTexSource)
    goto glide_load_dll_error;

  grTexTextureMemRequired = (grTexTextureMemRequired_fpt)mod_GetSymbol(&glideDLLInst, "grTexTextureMemRequired", 8);

  if (!grTexTextureMemRequired)
    goto glide_load_dll_error;

  grTriStats = (grTriStats_fpt)mod_GetSymbol(&glideDLLInst, "grTriStats", 8);

  if (!grTriStats)
    goto glide_load_dll_error;

  gu3dfGetInfo = (gu3dfGetInfo_fpt)mod_GetSymbol(&glideDLLInst, "gu3dfGetInfo", 8);

  if (!gu3dfGetInfo)
    goto glide_load_dll_error;

  gu3dfLoad = (gu3dfLoad_fpt)mod_GetSymbol(&glideDLLInst, "gu3dfLoad", 8);

  if (!gu3dfLoad)
    goto glide_load_dll_error;

  guAADrawTriangleWithClip = (guAADrawTriangleWithClip_fpt)mod_GetSymbol(&glideDLLInst, "guAADrawTriangleWithClip", 12);

  if (!guAADrawTriangleWithClip)
    goto glide_load_dll_error;

  guAlphaSource = (guAlphaSource_fpt)mod_GetSymbol(&glideDLLInst, "guAlphaSource", 4);

  if (!guAlphaSource)
    goto glide_load_dll_error;

  guColorCombineFunction = (guColorCombineFunction_fpt)mod_GetSymbol(&glideDLLInst, "guColorCombineFunction", 4);

  if (!guColorCombineFunction)
    goto glide_load_dll_error;

  guDrawPolygonVertexListWithClip =
      (guDrawPolygonVertexListWithClip_fpt)mod_GetSymbol(&glideDLLInst, "guDrawPolygonVertexListWithClip", 8);

  if (!guDrawPolygonVertexListWithClip)
    goto glide_load_dll_error;

  guDrawTriangleWithClip = (guDrawTriangleWithClip_fpt)mod_GetSymbol(&glideDLLInst, "guDrawTriangleWithClip", 12);

  if (!guDrawTriangleWithClip)
    goto glide_load_dll_error;

  guEncodeRLE16 = (guEncodeRLE16_fpt)mod_GetSymbol(&glideDLLInst, "guEncodeRLE16", 16);

  if (!guEncodeRLE16)
    goto glide_load_dll_error;

  guEndianSwapBytes = (guEndianSwapBytes_fpt)mod_GetSymbol(&glideDLLInst, "guEndianSwapBytes", 4);

  if (!guEndianSwapBytes)
    goto glide_load_dll_error;

  guEndianSwapWords = (guEndianSwapWords_fpt)mod_GetSymbol(&glideDLLInst, "guEndianSwapWords", 4);

  if (!guEndianSwapWords)
    goto glide_load_dll_error;

  guFogGenerateExp = (guFogGenerateExp_fpt)mod_GetSymbol(&glideDLLInst, "guFogGenerateExp", 8);

  if (!guFogGenerateExp)
    goto glide_load_dll_error;

  guFogGenerateExp2 = (guFogGenerateExp2_fpt)mod_GetSymbol(&glideDLLInst, "guFogGenerateExp2", 8);

  if (!guFogGenerateExp2)
    goto glide_load_dll_error;

  guFogGenerateLinear = (guFogGenerateLinear_fpt)mod_GetSymbol(&glideDLLInst, "guFogGenerateLinear", 12);

  if (!guFogGenerateLinear)
    goto glide_load_dll_error;

  guFogTableIndexToW = (guFogTableIndexToW_fpt)mod_GetSymbol(&glideDLLInst, "guFogTableIndexToW", 4);

  if (!guFogTableIndexToW)
    goto glide_load_dll_error;

  guTexAllocateMemory = (guTexAllocateMemory_fpt)mod_GetSymbol(&glideDLLInst, "guTexAllocateMemory", 60);

  if (!guTexAllocateMemory)
    goto glide_load_dll_error;

  guTexChangeAttributes = (guTexChangeAttributes_fpt)mod_GetSymbol(&glideDLLInst, "guTexChangeAttributes", 48);

  if (!guTexChangeAttributes)
    goto glide_load_dll_error;

  guTexCombineFunction = (guTexCombineFunction_fpt)mod_GetSymbol(&glideDLLInst, "guTexCombineFunction", 8);

  if (!guTexCombineFunction)
    goto glide_load_dll_error;

  guTexCreateColorMipMap = (guTexCreateColorMipMap_fpt)mod_GetSymbol(&glideDLLInst, "guTexCreateColorMipMap", 0);

  if (!guTexCreateColorMipMap)
    goto glide_load_dll_error;

  guTexDownloadMipMap = (guTexDownloadMipMap_fpt)mod_GetSymbol(&glideDLLInst, "guTexDownloadMipMap", 12);

  if (!guTexDownloadMipMap)
    goto glide_load_dll_error;

  guTexDownloadMipMapLevel = (guTexDownloadMipMapLevel_fpt)mod_GetSymbol(&glideDLLInst, "guTexDownloadMipMapLevel", 12);

  if (!guTexDownloadMipMapLevel)
    goto glide_load_dll_error;

  guTexGetCurrentMipMap = (guTexGetCurrentMipMap_fpt)mod_GetSymbol(&glideDLLInst, "guTexGetCurrentMipMap", 4);

  if (!guTexGetCurrentMipMap)
    goto glide_load_dll_error;

  guTexGetMipMapInfo = (guTexGetMipMapInfo_fpt)mod_GetSymbol(&glideDLLInst, "guTexGetMipMapInfo", 4);

  if (!guTexGetMipMapInfo)
    goto glide_load_dll_error;

  guTexMemQueryAvail = (guTexMemQueryAvail_fpt)mod_GetSymbol(&glideDLLInst, "guTexMemQueryAvail", 4);

  if (!guTexMemQueryAvail)
    goto glide_load_dll_error;

  guTexMemReset = (guTexMemReset_fpt)mod_GetSymbol(&glideDLLInst, "guTexMemReset", 0);

  if (!guTexMemReset)
    goto glide_load_dll_error;

  guTexSource = (guTexSource_fpt)mod_GetSymbol(&glideDLLInst, "guTexSource", 4);

  if (!guTexSource)
    goto glide_load_dll_error;

  return &glideDLLInst;

glide_load_dll_error:
  mod_FreeModule(&glideDLLInst);
  return NULL;
}
/* #endif   DYNAHEADER_CREATE_STORAGE */

#elif DYNAHEADER

extern ConvertAndDownloadRle_fpt ConvertAndDownloadRle;

extern grAADrawLine_fpt grAADrawLine;

extern grAADrawPoint_fpt grAADrawPoint;

extern grAADrawPolygon_fpt grAADrawPolygon;

extern grAADrawPolygonVertexList_fpt grAADrawPolygonVertexList;

extern grAADrawTriangle_fpt grAADrawTriangle;

extern grAlphaBlendFunction_fpt grAlphaBlendFunction;

extern grAlphaCombine_fpt grAlphaCombine;

extern grAlphaControlsITRGBLighting_fpt grAlphaControlsITRGBLighting;

extern grAlphaTestFunction_fpt grAlphaTestFunction;

extern grAlphaTestReferenceValue_fpt grAlphaTestReferenceValue;

extern grBufferClear_fpt grBufferClear;

extern grBufferNumPending_fpt grBufferNumPending;

extern grBufferSwap_fpt grBufferSwap;

extern grCheckForRoom_fpt grCheckForRoom;

extern grChromakeyMode_fpt grChromakeyMode;

extern grChromakeyValue_fpt grChromakeyValue;

extern grClipWindow_fpt grClipWindow;

extern grColorCombine_fpt grColorCombine;

extern grColorMask_fpt grColorMask;

extern grConstantColorValue_fpt grConstantColorValue;

extern grConstantColorValue4_fpt grConstantColorValue4;

extern grCullMode_fpt grCullMode;

extern grDepthBiasLevel_fpt grDepthBiasLevel;

extern grDepthBufferFunction_fpt grDepthBufferFunction;

extern grDepthBufferMode_fpt grDepthBufferMode;

extern grDepthMask_fpt grDepthMask;

extern grDisableAllEffects_fpt grDisableAllEffects;

extern grDitherMode_fpt grDitherMode;

extern grDrawLine_fpt grDrawLine;

extern grDrawPlanarPolygon_fpt grDrawPlanarPolygon;

extern grDrawPlanarPolygonVertexList_fpt grDrawPlanarPolygonVertexList;

extern grDrawPoint_fpt grDrawPoint;

extern grDrawPolygon_fpt grDrawPolygon;

extern grDrawPolygonVertexList_fpt grDrawPolygonVertexList;

extern grDrawTriangle_fpt grDrawTriangle;

extern grErrorSetCallback_fpt grErrorSetCallback;

extern grFogColorValue_fpt grFogColorValue;

extern grFogMode_fpt grFogMode;

extern grFogTable_fpt grFogTable;

extern grGammaCorrectionValue_fpt grGammaCorrectionValue;

extern grGlideGetState_fpt grGlideGetState;

extern grGlideGetVersion_fpt grGlideGetVersion;

extern grGlideInit_fpt grGlideInit;

extern grGlideSetState_fpt grGlideSetState;

extern grGlideShamelessPlug_fpt grGlideShamelessPlug;

extern grGlideShutdown_fpt grGlideShutdown;

extern grHints_fpt grHints;

extern grLfbConstantAlpha_fpt grLfbConstantAlpha;

extern grLfbConstantDepth_fpt grLfbConstantDepth;

extern grLfbLock_fpt grLfbLock;

extern grLfbReadRegion_fpt grLfbReadRegion;

extern grLfbUnlock_fpt grLfbUnlock;

extern grLfbWriteColorFormat_fpt grLfbWriteColorFormat;

extern grLfbWriteColorSwizzle_fpt grLfbWriteColorSwizzle;

extern grLfbWriteRegion_fpt grLfbWriteRegion;

extern grRenderBuffer_fpt grRenderBuffer;

extern grResetTriStats_fpt grResetTriStats;

extern grSplash_fpt grSplash;

extern grSstControl_fpt grSstControl;

extern grSstIdle_fpt grSstIdle;

extern grSstIsBusy_fpt grSstIsBusy;

extern grSstOrigin_fpt grSstOrigin;

extern grSstPerfStats_fpt grSstPerfStats;

extern grSstQueryBoards_fpt grSstQueryBoards;

extern grSstQueryHardware_fpt grSstQueryHardware;

extern grSstResetPerfStats_fpt grSstResetPerfStats;

extern grSstScreenHeight_fpt grSstScreenHeight;

extern grSstScreenWidth_fpt grSstScreenWidth;

extern grSstSelect_fpt grSstSelect;

extern grSstStatus_fpt grSstStatus;

extern grSstVRetraceOn_fpt grSstVRetraceOn;

extern grSstVideoLine_fpt grSstVideoLine;

extern grSstWinClose_fpt grSstWinClose;

extern grSstWinOpen_fpt grSstWinOpen;

extern grTexCalcMemRequired_fpt grTexCalcMemRequired;

extern grTexClampMode_fpt grTexClampMode;

extern grTexCombine_fpt grTexCombine;

extern grTexCombineFunction_fpt grTexCombineFunction;

extern grTexDetailControl_fpt grTexDetailControl;

extern grTexDownloadMipMap_fpt grTexDownloadMipMap;

extern grTexDownloadMipMapLevel_fpt grTexDownloadMipMapLevel;

extern grTexDownloadMipMapLevelPartial_fpt grTexDownloadMipMapLevelPartial;

extern grTexDownloadTable_fpt grTexDownloadTable;

extern grTexDownloadTablePartial_fpt grTexDownloadTablePartial;

extern grTexFilterMode_fpt grTexFilterMode;

extern grTexLodBiasValue_fpt grTexLodBiasValue;

extern grTexMaxAddress_fpt grTexMaxAddress;

extern grTexMinAddress_fpt grTexMinAddress;

extern grTexMipMapMode_fpt grTexMipMapMode;

extern grTexMultibase_fpt grTexMultibase;

extern grTexMultibaseAddress_fpt grTexMultibaseAddress;

extern grTexNCCTable_fpt grTexNCCTable;

extern grTexSource_fpt grTexSource;

extern grTexTextureMemRequired_fpt grTexTextureMemRequired;

extern grTriStats_fpt grTriStats;

extern gu3dfGetInfo_fpt gu3dfGetInfo;

extern gu3dfLoad_fpt gu3dfLoad;

extern guAADrawTriangleWithClip_fpt guAADrawTriangleWithClip;

extern guAlphaSource_fpt guAlphaSource;

extern guColorCombineFunction_fpt guColorCombineFunction;

extern guDrawPolygonVertexListWithClip_fpt guDrawPolygonVertexListWithClip;

extern guDrawTriangleWithClip_fpt guDrawTriangleWithClip;

extern guEncodeRLE16_fpt guEncodeRLE16;

extern guEndianSwapBytes_fpt guEndianSwapBytes;

extern guEndianSwapWords_fpt guEndianSwapWords;

extern guFbReadRegion_fpt guFbReadRegion;

extern guFogGenerateExp_fpt guFogGenerateExp;

extern guFogGenerateExp2_fpt guFogGenerateExp2;

extern guFogGenerateLinear_fpt guFogGenerateLinear;

extern guFogTableIndexToW_fpt guFogTableIndexToW;

extern guMovieSetName_fpt guMovieSetName;

extern guMovieStart_fpt guMovieStart;

extern guMovieStop_fpt guMovieStop;

extern guTexAllocateMemory_fpt guTexAllocateMemory;

extern guTexChangeAttributes_fpt guTexChangeAttributes;

extern guTexCombineFunction_fpt guTexCombineFunction;

extern guTexCreateColorMipMap_fpt guTexCreateColorMipMap;

extern guTexDownloadMipMap_fpt guTexDownloadMipMap;

extern guTexDownloadMipMapLevel_fpt guTexDownloadMipMapLevel;

extern guTexGetCurrentMipMap_fpt guTexGetCurrentMipMap;

extern guTexGetMipMapInfo_fpt guTexGetMipMapInfo;

extern guTexMemQueryAvail_fpt guTexMemQueryAvail;

extern guTexMemReset_fpt guTexMemReset;

extern guTexSource_fpt guTexSource;

#include "module.h"
extern module glideDLLInst = {NULL};

#endif /* DYNAHEADER */

#endif /* __GLIDE_H__ */
