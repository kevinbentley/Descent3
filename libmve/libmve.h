#ifndef _LIBMVE_H
#define _LIBMVE_H

#define MVE_ERR_EOF 1

typedef struct{
	int screenWidth;
	int screenHeight;
	int width;
	int height;
	int truecolor;
} MVE_videoSpec;

int  MVE_rmPrepMovie(void *stream, int x, int y, int track);
int  MVE_rmStepMovie(void);
void MVE_rmHoldMovie(void);
void MVE_rmEndMovie(void);

void MVE_getVideoSpec(MVE_videoSpec *vSpec);

void MVE_sndInit(int x);

typedef unsigned int (*mve_cb_Read)(void *stream,
                                    void *buffer,
                                    unsigned int count);

typedef void *(*mve_cb_Alloc)(unsigned int size);
typedef void (*mve_cb_Free)(void *ptr);

typedef void (*mve_cb_ShowFrame)(unsigned char *buffer,
                                 unsigned int bufw, unsigned int bufh,
                                 unsigned int sx, unsigned int sy,
                                 unsigned int w, unsigned int h,
                                 unsigned int dstx, unsigned int dsty);

typedef void (*mve_cb_SetPalette)(unsigned char *p,
                                  unsigned int start, unsigned int count);

void MVE_ioCallbacks(mve_cb_Read io_read);
void MVE_memCallbacks(mve_cb_Alloc mem_alloc, mve_cb_Free mem_free);
void MVE_sfCallbacks(mve_cb_ShowFrame showframe);
void MVE_palCallbacks(mve_cb_SetPalette setpalette);

#endif /* _LIBMVE_H */
