
/*
** mvelibl.h
**
** Interplay Movie File (MVE) Player
**   Library Definitions (32-Bit Linux Version)
** Written by Paul Allen Edelstein, Interplay Productions.
** Partial Linux port by Jeff Slutter, Outrage Entertainment.
**
** (c) 1997 Interplay Productions.  All Rights Reserved.
** This file is confidential and consists of proprietary information
** of Interplay Productions.  This file and associated libraries
** may not, in whole or in part, be disclosed to third parties,
** incorporated into any software product which is not being created
** for Interplay Productions, copied or duplicated in any form,
** without the prior written permission of Interplay Productions.
** Further, you may not reverse engineer, decompile or otherwise
** attempt to derive source code of this material.
*/
#ifndef MVELIB_H_INCLUDED
#define MVELIB_H_INCLUDED

#include <cstdint>

#include "SystemInterfaces.h"
#include "lnxdsound.h"

// Call this function to provide hooks into your memory management.
typedef void *(mve_cb_alloc)(unsigned size);
typedef void(mve_cb_free)(void *p);
void MVE_memCallbacks(mve_cb_alloc *fn_alloc, mve_cb_free *fn_free);

// This function remains from the DOS version of mvelib.
// It allows you to provide a preallocated buffer for file I/O,
// but under Windows there's no real point to doing this.
void MVE_memIO(void *p, unsigned size);

// Call this function to provide hook into your file io.
typedef unsigned mve_cb_read(int handle, void *buf, unsigned count);
void MVE_ioCallbacks(mve_cb_read *fn_read);

// Call this function to provide hook into your digital sound driver.
// Call with NULL if no sound support is available (default).
void MVE_sndInit(ISoundDevice *lpDS);

// Volume controls.
// These functions are equivalent to the IDirectSoundBuffer
// SetVolume and SetPan functions.  They take effect immediately
// and do NOT reset when a new movie starts.
// Volume ranges from 0 (0 db, no volume change) to -10,000 (-100db, essentially silent).
// Pan ranges from -10,000 (left full volume, right -100db), thru 0 (both full),
// thru 10,000 (left -100db, right full volume).
// The default value for volume and pan is zero.
void MVE_dsbSetVolume(int32_t lVolume);
void MVE_dsbSetPan(int32_t lPan);

// Only call this function to configure software to work with a Super VGA
//  mode if you do not have VESA support.
// Restrictions/Assumptions:
//    64K >= WinSize >= WinGran
//    WinSize % WinGran == 0
//    WinGran of 64K is represented by 0
//    SetBank is address of function with following protocol:
//	bh:  0=Set window, 1=Get Window
//	bl:  Window number (0 or 1)
//	dx:  Window position in video memory in units of WinGran.
//     on return, registers AX and DX are destroyed.
//
//  Hicolor is 0 for 8-bit color, 1 for 15-bit rgb color, 2
//  for byte swapped 15-bit rgb color.
//
// Note: 16-bit WriteWinSeg replaced with 32-bit WriteWinPtr
//
// The functionality of the following function is reduced in the Windows
// version of the player.  Call it as follows:
//   MVE_sfSVGA(w,h,w,0,NULL,0,0,NULL,hicolor)
// where w and h are the width and height of your window,
// and hicolor is a boolean which indicates if the screen
// is operating in hi color, rather than 8-bit paletted color.
// Under windows, the information provided by this function
// is just used for window centering and for determining
// how and when to do palette callbacks.
void MVE_sfSVGA(unsigned w, unsigned h, unsigned LineWidth, unsigned WriteWin, uint8_t *WriteWinPtr,
                uint32_t WinSize, unsigned WinGran, void *SetBank, unsigned hicolor);

// This function alters the display from 640x480 or 640x400 to 640x350 resolution.
void MVE_ForceVres350(void);

// This function alters the display from 640x480/400/350 to  640x240/200/175.
void MVE_ForceVresHalf(void);

// **NOTE** There still need to be calls to restore original screen resolution
//          after using MVE_ForceVres350() or MVE_ForceVresHalf()!
// Only call this function to either
//   1.  Replace method of copying frame to screen (perhaps for a nonstandard
//	 screen format).
//   2.  Wrap your own code around the transfer of frame to screen
//	 or modify which portions of the screen are updated.
// This function replaces calls to the default MVE_ShowFrame function
//  with calls to your function, which can itself call MVE_ShowFrame.
typedef void (*mve_cb_ShowFrame)(uint8_t *buf, uint32_t bufw, uint32_t bufh, uint32_t sx,
                                 uint32_t sy, uint32_t w, uint32_t h, uint32_t dstx, uint32_t dsty,
                                 uint32_t hicolor);
void MVE_sfCallbacks(mve_cb_ShowFrame fn_ShowFrame);

typedef void mve_cb_SetPalette(uint8_t *p, unsigned start, unsigned count);
void MVE_palCallbacks(mve_cb_SetPalette *fn_SetPalette);

void MVE_SetPalette(uint8_t *p, unsigned start, unsigned count);

// Configure the software for a graphics mode, optionally setting the
//  display to that mode (see the MVE_GFX_xxx constants defined below).
bool MVE_gfxMode(int16_t mode);

// Reset the screen to text mode (usually done before exiting a program).
void MVE_gfxReset(void);

// Set line for split screen graphics
// {Use vbe_SetDisplayStart(x,y) to set vid buf for upper screen}
void MVE_gfxSetSplit(unsigned line);

// Setup double buffering
void MVE_gfxSetDoubleBuffer(unsigned y1, unsigned y2, unsigned vis);

// Get double buffering state
void MVE_gfxGetDoubleBuffer(unsigned *vis_y, unsigned *hid_y);

// Enable double buffering for auto screen modes
void MVE_sfAutoDoubleBuffer(unsigned on);

// Wait for video retrace off (0) or on (1)
void MVE_gfxWaitRetrace(unsigned state);

//---------------------------------------------
// Establish callback for user control of movie playback.
typedef int mve_cb_ctl(void);
void MVE_rmCallbacks(mve_cb_ctl *fn_ctl);

// Specify playback fastmode option (default is MVE_RM_NORMAL).
#define MVE_RM_NORMAL 0     // Normal playback
#define MVE_RM_HALF 1       // Half height (even lines only)
#define MVE_RM_DITHERED 2   // Half height (dither between lines)
#define MVE_RM_HALF_2 5     // Full height, even lines only
#define MVE_RM_DITHERED_2 6 // Full height, dither, even lines only

void MVE_rmFastMode(int mode);

// Specifying horizontal magnification:
//	3: 4/3 horizontal magnification
//  4: normal
void MVE_rmHScale(int hscale);

// Get frame count and number of dropped frames from last movie played.
void MVE_rmFrameCounts(unsigned *FrameCount, unsigned *FrameDropCount);

// Dump timing statistics (if enabled).
void MVE_logDumpStats(void);

// Run a compressed movie by reading data starting at the current
//  position in the file specified by handle hFile.
// The movie window is displaced by dx,dy from the upper left hand corner
//  or is centered if dx,dy is -1,-1.
// track specifies which audio track to play (usually 0 for a single
//  audio track).
//
// Returns an error/result code.
//
// Memory may be dynamically allocated while movie runs.
int MVE_RunMovie(int hFile, int dx, int dy, unsigned track);

// MVE_RunMovieContinue is the same as MVE_RunMovie except that it does not
// automatically call MVE_rmEndMovie().  This may improve the smoothness
// of immediately playing another movie afterwards.
int MVE_RunMovieContinue(int hFile, int dx, int dy, unsigned track);

// Alternative to using MVE_RunMovie() and MVE_rmCallbacks().
// Call MVE_rmPrepMovie() to prepare movie for playing.
// Call MVE_rmStepMovie() to display next frame of movie until nonzero
//  result is returned (MVE_ERR_EOF for no next frame or some other error).
// Call MVE_rmHoldMovie() to hold on current frame (and pause audio).
// Call MVE_rmEndMovie() to abort movie.
// All functions except MVE_rmEndMovie() return an error code.
int MVE_rmPrepMovie(int hFile, int dx, int dy, unsigned track);
int MVE_rmStepMovie(void);
int MVE_rmHoldMovie(void);
void MVE_rmEndMovie(void);

// Frame Reader Streams
//  This is a special interface to the movie system which
//  allows a movie file to be opened as a stream from which
//  its frames may be retrieved.  Audio and timing information
//  are ignored.  For 256-color screen applications, palette
//  information is also typically ignored, and movies with a common
//  predefined palette are used.  However, for hi-color screen
//  applications, an interface to obtain palette information has
//  been provided. This system is intended for use by video sprites
//  played off of the hard drive or out of memory.
typedef struct MVE_frStreamRec* MVE_frStream;

// MVE_frOpen
//  Before calling this function, be sure to call MVE_memCallbacks()
//   and MVE_rmDirectDraw().
//  fn_read specifies a file reader similar to the one
//    used by MVE_ioCallbacks().
//  handle specifies a file handle for an already opened
//    movie file.  It is used by the file reader and is similar
//    to hFile argument used by MVE_RunMovie() and MVE_rmPrepMovie().
//  fr_callback is normally NULL, but can be used to supply
//    a handler for user data which has been interleaved into
//    the movie stream.
//
//  If the movie file is invalid or the call otherwise fails,
//    NULL is returned.
MVE_frStream MVE_frOpen(unsigned (*fn_read)(int handle, void *buf, unsigned count), int handle,
                        int (*fr_callback)(unsigned op, unsigned subop, void *buf));

// MVE_frGet
//  Returns the next frame from the specified frame reader stream
//  a nonzero error code  {the same codes as returned by MVE_RunMovie()
//  and MVE_rmStepMovie()}.
//  If successful, MVE_frGet(frs, &buf, &w, &h) returns a pointer
//  to a surface containing the frame in pBuf,
//  and its width and height in w and h.
int MVE_frGet(MVE_frStream frs, uint8_t **pBuf, uint32_t *width, uint32_t *height, uint32_t *hicolor);

// MVE_frPal
//  After each successful call to MVE_frGet(), this call may be used to
//  obtain corresponding palette information.  It returns a pointer to the
//  entire current palette for the frame, and the subportion of the palette
//  which has changed this frame is identified by start and count (they will
//  both be zero on frames for which the palette has not changed).
//
//  Paltbl points to 256*3 bytes of 6-bit r,g,b triples.
//  Start ranges from 0 to 255.  Count from 0 to 256.
//
//  These conventions are similar to those used by the palette callback arguments
//  with the standard player interface, except that this interface requires
//  polling each frame instead, and must be passed pointers to the variables where
//  the values will be returned.
//
void MVE_frPal(MVE_frStream frs, uint8_t **pPaltbl, unsigned *pStart, unsigned *pCount);

// MVE_frClose
//  Closes the specified Frame Reader Stream frs.
//  Frees all storage associated with the stream.
//  The specified frs must not be used after this call.
//  Note that the open file handle specified in MVE_frOpen() is
//  not closed by this call...that is the caller's responsibility.
void MVE_frClose(MVE_frStream frs);

// Release any memory dynamically allocated by MVE_RunMovie.
void MVE_ReleaseMem(void);

// Return string corresponding to MVE_RunMovie result code.
const char *MVE_strerror(int code);

// RunMovie callback control code and result codes.
// Codes > 1 are user defined.
#define MVE_CTL_HOLD -1 // Returned by rmCtl() to hold current frame
#define MVE_CTL_EXIT 1  // Returned by rmCtl() to end movie

#define MVE_ERR_EOF -1      // Returned by StepMovie() for end of movie
#define MVE_ERR_IO -2       // File I/O error or unable to alloc memory.
#define MVE_ERR_SYNC -3     // Timer error.
#define MVE_ERR_SND -4      // Unable to allocate memory for sound
#define MVE_ERR_NF -5       // Unable to allocate memory for video
#define MVE_ERR_GFX_FIT -6  // Screen size too small for movie
#define MVE_ERR_GFX_FAIL -7 // Failed to set desired graphics mode
#define MVE_ERR_BADFMT -8   // Not a MVE file or unacceptable version
#define MVE_ERR_GFX_CLR -9  // Incorrect screen color mode
#define MVE_ERR_PREP -10    // StepMovie() without PrepMovie()
#define MVE_ERR_LD -11      // Unable to initialize Draw system (DirectDraw, etc)
#define MVE_ERR_LOST -12    // Direct Draw Surface Lost

#define MVE_ERR_LAST -12

#endif
