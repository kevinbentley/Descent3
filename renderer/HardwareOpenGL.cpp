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

#include "byteswap.h"
#if defined(WIN32)
#include <windows.h>
#endif

#include "pserror.h"
#include "mono.h"
#include "3d.h"
#include "renderer.h"
#include "application.h"
#include "bitmap.h"
#include "lightmap.h"
#include "rend_opengl.h"
#include "grdefs.h"
#include "mem.h"
#include "config.h"
#include "rtperformance.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HardwareInternal.h"
#include "../Descent3/args.h"
#include "lnxscreenmode.h"
#include <SDL.h>

#include <NewBitmap.h>

#define DECLARE_OPENGL
#include "dyna_gl.h"

#if defined(WIN32)
#include "win/arb_extensions.h"
#endif

#include <algorithm>

int FindArg(const char *);
void rend_SetLightingState(light_state state);

// General renderer states
extern int gpu_Overlay_map;
int Bump_map = 0;
int Bumpmap_ready = 0;
extern uint8_t gpu_Overlay_type;
float Z_bias = 0.0f;
uint8_t Renderer_close_flag = 0;
extern uint8_t Renderer_initted;
renderer_type Renderer_type = RENDERER_OPENGL;
int WindowGL = 0;

extern matrix Unscaled_matrix;
extern vector View_position;

#ifndef GL_UNSIGNED_SHORT_5_5_5_1
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#endif

#ifndef GL_UNSIGNED_SHORT_4_4_4_4
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#endif

#define CHECK_ERROR(x)

SDL_Window *GSDLWindow = NULL;
SDL_GLContext GSDLGLContext = NULL;
char loadedLibrary[_MAX_PATH];

#define GET_WRAP_STATE(x) (x >> 4)
#define GET_FILTER_STATE(x) (x & 0x0f)

#define SET_WRAP_STATE(x, s)                                                                                           \
  {                                                                                                                    \
    x &= 0x0F;                                                                                                         \
    x |= (s << 4);                                                                                                     \
  }
#define SET_FILTER_STATE(x, s)                                                                                         \
  {                                                                                                                    \
    x &= 0xF0;                                                                                                         \
    x |= (s);                                                                                                          \
  }

//	OpenGL Stuff
static int OpenGL_window_initted = 0;
static int OpenGL_polys_drawn = 0;
static int OpenGL_verts_processed = 0;
static int OpenGL_uploads = 0;
static int OpenGL_sets_this_frame[10];
static int OpenGL_packed_pixels = 0;
static int Cur_texture_object_num = 1;
static int OpenGL_cache_initted = 0;
static int OpenGL_last_bound[2];
static int Last_texel_unit_set = -1;

extern int gpu_last_frame_polys_drawn;
extern int gpu_last_frame_verts_processed;
extern int gpu_last_uploaded;

extern float gpu_Alpha_factor;
extern float gpu_Alpha_multiplier;

#if defined(_USE_OGL_ACTIVE_TEXTURES)
PFNGLACTIVETEXTUREARBPROC oglActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC oglClientActiveTextureARB = NULL;
PFNGLMULTITEXCOORD4FARBPROC oglMultiTexCoord4f = NULL;
#endif

uint16_t *OpenGL_bitmap_remap = NULL;
uint16_t *OpenGL_lightmap_remap = NULL;
uint8_t *OpenGL_bitmap_states = NULL;
uint8_t *OpenGL_lightmap_states = NULL;

uint32_t *opengl_Upload_data = NULL;
uint32_t *opengl_Translate_table = NULL;
uint32_t *opengl_4444_translate_table = NULL;

uint16_t *opengl_packed_Upload_data = NULL;
uint16_t *opengl_packed_Translate_table = NULL;
uint16_t *opengl_packed_4444_translate_table = NULL;

extern rendering_state gpu_state;
extern renderer_preferred_state gpu_preferred_state;

bool OpenGL_multitexture_state = false;
module *OpenGLDLLHandle = NULL;
int Already_loaded = 0;
bool opengl_Blending_on = 0;

static oeApplication *ParentApplication = NULL;

/* framebuffer object for backbuffer, scale to window size without changing resolution.  --ryan, 2019. */
#define GL_DEPTH_COMPONENT16_EXT              0x81A5
#define GL_READ_FRAMEBUFFER_EXT               0x8CA8
#define GL_DRAW_FRAMEBUFFER_EXT               0x8CA9
#define GL_FRAMEBUFFER_COMPLETE_EXT           0x8CD5
#define GL_COLOR_ATTACHMENT0_EXT              0x8CE0
#define GL_DEPTH_ATTACHMENT_EXT               0x8D00
#define GL_STENCIL_ATTACHMENT_EXT             0x8D20
#define GL_FRAMEBUFFER_EXT                    0x8D40
#define GL_RENDERBUFFER_EXT                   0x8D41
static GLuint GOpenGLFBO = 0;
static GLuint GOpenGLRBOColor = 0;
static GLuint GOpenGLRBODepth = 0;
static GLuint GOpenGLFBOWidth = 0;
static GLuint GOpenGLFBOHeight = 0;


#if 0
int checkForGLErrors( const char *file, int line )
{
  /*
  int errors = 0 ;
  int counter = 0 ;
  static int errcnt = 0;
  if(!dglGetError)
    return 0;
  while ( counter < 1000 )
    {
      GLenum x = dglGetError() ;

      if ( x == GL_NO_ERROR )
        return errors ;

      printf( "%s:%d OpenGL error: %s [%08x]\n", file,line, gluErrorString ( x ), errcnt++ ) ;
      errors++ ;
      counter++ ;
    }
  */
  const char *sdlp = SDL_GetError();
  if(sdlp && *sdlp)
    mprintf(0,"SDL: %s",sdlp);
	return 1;
}
#endif

// Sets up multi-texturing using ARB extensions
void opengl_GetDLLFunctions(void) {
#if defined(WIN32)
  oglActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)dwglGetProcAddress("glActiveTextureARB");
  if (!oglActiveTextureARB)
    goto dll_error;

  oglClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)dwglGetProcAddress("glClientActiveTextureARB");
  if (!oglClientActiveTextureARB)
    goto dll_error;

  oglMultiTexCoord4f = (PFNGLMULTITEXCOORD4FARBPROC)dwglGetProcAddress("glMultiTexCoord4f");
  if (!oglMultiTexCoord4f)
    goto dll_error;
#else
#define mod_GetSymbol(x, funcStr, y) __SDL_mod_GetSymbol(funcStr)

  oglActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)mod_GetSymbol(OpenGLDLLHandle, "glActiveTextureARB", 255);
  oglClientActiveTextureARB =
      (PFNGLCLIENTACTIVETEXTUREARBPROC)mod_GetSymbol(OpenGLDLLHandle, "glClientActiveTextureARB", 255);
  oglMultiTexCoord4f = (PFNGLMULTITEXCOORD4FARBPROC)mod_GetSymbol(OpenGLDLLHandle, "glMultiTexCoord4f", 255);
  if (!oglMultiTexCoord4f) {
    oglMultiTexCoord4f = (PFNGLMULTITEXCOORD4FARBPROC)mod_GetSymbol(OpenGLDLLHandle, "glMultiTexCoord4fARB", 255);
  }
  if (oglActiveTextureARB == NULL || oglClientActiveTextureARB == NULL || oglMultiTexCoord4f == NULL) {
    goto dll_error;
  }

#undef mod_GetSymbol
#endif

  UseMultitexture = true;
  return;

dll_error:
  oglActiveTextureARB = NULL;
  oglClientActiveTextureARB = NULL;
  oglMultiTexCoord4f = NULL;
  UseMultitexture = false;
}

// returns true if the passed in extension name is supported
bool opengl_CheckExtension(const char *extName) {
  const char *p = (const char *)dglGetString(GL_EXTENSIONS);
  int extNameLen = strlen(extName);
  const char *end = p + strlen(p);

  while (p < end) {
    int n = strcspn(p, " ");
    if ((extNameLen == n) && (strncmp(extName, p, n) == 0))
      return true;

    p += (n + 1);
  }

  return false;
}

// Gets some specific information about this particular flavor of opengl
void opengl_GetInformation() {
  mprintf(0, "OpenGL Vendor: %s\n", dglGetString(GL_VENDOR));
  mprintf(0, "OpenGL Renderer: %s\n", dglGetString(GL_RENDERER));
  mprintf(0, "OpenGL Version: %s\n", dglGetString(GL_VERSION));
  mprintf(0, "OpenGL Extensions: %s\n", dglGetString(GL_EXTENSIONS));
}

int opengl_MakeTextureObject(int tn) {
  int num = Cur_texture_object_num;

  Cur_texture_object_num++;

  if (UseMultitexture && Last_texel_unit_set != tn) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
    oglActiveTextureARB(GL_TEXTURE0_ARB + tn);
    Last_texel_unit_set = tn;
#endif
  }

  dglBindTexture(GL_TEXTURE_2D, num);
  dglPixelStorei(GL_UNPACK_ALIGNMENT, 2);

  dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // glTexEnvf (GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

  CHECK_ERROR(2)

  return num;
}

int opengl_InitCache(void) {

  OpenGL_bitmap_remap = (uint16_t *)mem_malloc(MAX_BITMAPS * 2);
  ASSERT(OpenGL_bitmap_remap);
  OpenGL_lightmap_remap = (uint16_t *)mem_malloc(MAX_LIGHTMAPS * 2);
  ASSERT(OpenGL_lightmap_remap);

  OpenGL_bitmap_states = (uint8_t *)mem_malloc(MAX_BITMAPS);
  ASSERT(OpenGL_bitmap_states);
  OpenGL_lightmap_states = (uint8_t *)mem_malloc(MAX_LIGHTMAPS);
  ASSERT(OpenGL_lightmap_states);

  Cur_texture_object_num = 1;

  // Setup textures and cacheing
  int i;
  for (i = 0; i < MAX_BITMAPS; i++) {
    OpenGL_bitmap_remap[i] = 65535;
    OpenGL_bitmap_states[i] = 255;
    GameBitmaps[i].flags |= BF_CHANGED | BF_BRAND_NEW;
  }

  for (i = 0; i < MAX_LIGHTMAPS; i++) {
    OpenGL_lightmap_remap[i] = 65535;
    OpenGL_lightmap_states[i] = 255;
    GameLightmaps[i].flags |= LF_CHANGED | LF_BRAND_NEW;
  }

  dglTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  if (UseMultitexture) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
    oglActiveTextureARB(GL_TEXTURE0_ARB + 1);
    dglTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    oglActiveTextureARB(GL_TEXTURE0_ARB + 0);
#endif
  }

  CHECK_ERROR(3)

  OpenGL_cache_initted = 1;
  return 1;
}

// Sets default states for our renderer
void opengl_SetDefaults() {
  mprintf(0, "Setting states\n");

  gpu_state.cur_color = 0x00FFFFFF;
  gpu_state.cur_bilinear_state = -1;
  gpu_state.cur_zbuffer_state = -1;
  gpu_state.cur_texture_quality = -1;
  gpu_state.cur_light_state = LS_GOURAUD;
  gpu_state.cur_color_model = CM_MONO;
  gpu_state.cur_bilinear_state = -1;
  gpu_state.cur_alpha_type = AT_TEXTURE;

  // Enable some states
  dglAlphaFunc(GL_GREATER, 0);
  dglEnable(GL_ALPHA_TEST);
  dglEnable(GL_BLEND);
  dglEnable(GL_DITHER);
  opengl_Blending_on = true;

  rend_SetAlphaType(AT_ALWAYS);
  rend_SetAlphaValue(255);
  rend_SetFiltering(1);
  rend_SetLightingState(LS_NONE);
  rend_SetTextureType(TT_FLAT);
  rend_SetColorModel(CM_RGB);
  rend_SetZBufferState(1);
  rend_SetZValues(0, 3000);
  rend_SetGammaValue(gpu_preferred_state.gamma);
  OpenGL_last_bound[0] = 9999999;
  OpenGL_last_bound[1] = 9999999;
  Last_texel_unit_set = -1;
  OpenGL_multitexture_state = false;

  dglEnableClientState(GL_VERTEX_ARRAY);
  dglEnableClientState(GL_COLOR_ARRAY);
  dglEnableClientState(GL_TEXTURE_COORD_ARRAY);

  dglHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  dglHint(GL_FOG_HINT, GL_NICEST);
  dglEnable(GL_SCISSOR_TEST);
  dglScissor(0, 0, gpu_state.screen_width, gpu_state.screen_height);
  dglDisable(GL_SCISSOR_TEST);
  dglDepthRange(0.0f, 1.0f);

  if (UseMultitexture) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
    oglActiveTextureARB(GL_TEXTURE0_ARB + 1);
    oglClientActiveTextureARB(GL_TEXTURE0_ARB + 1);
    dglEnableClientState(GL_TEXTURE_COORD_ARRAY);
    dglHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    dglHint(GL_FOG_HINT, GL_NICEST);

    oglClientActiveTextureARB(GL_TEXTURE0_ARB + 0);

    dglDisable(GL_TEXTURE_2D);
    dglAlphaFunc(GL_GREATER, 0);
    dglEnable(GL_ALPHA_TEST);
    dglEnable(GL_BLEND);
    dglEnable(GL_DITHER);
    dglBlendFunc(GL_DST_COLOR, GL_ZERO);
    oglActiveTextureARB(GL_TEXTURE0_ARB + 0);
#endif
  }
}

extern bool linux_permit_gamma;
extern renderer_preferred_state Render_preferred_state;
extern bool ddio_mouseGrabbed;
int SDLCALL d3SDLEventFilter(void *userdata, SDL_Event *event);

int opengl_Setup(oeApplication *app, int *width, int *height) {
  int winw = Video_res_list[Game_video_resolution].width;
  int winh = Video_res_list[Game_video_resolution].height;

  // rcg09182000 don't need to quitsubsystem anymore...
  //    SDL_QuitSubSystem(SDL_INIT_VIDEO);  // here goes nothing...
  //    Already_loaded = false;
  SDL_ClearError();
  if (!SDL_WasInit(SDL_INIT_VIDEO)) {
    const int rc = SDL_Init(SDL_INIT_VIDEO);
    if (rc != 0) {
      char buffer[512];
      snprintf(buffer, sizeof(buffer), "SDL_GetError() reports \"%s\".\n", SDL_GetError());
      fprintf(stderr, "SDL: SDL_Init() failed! rc == (%d).\n", rc);
      fprintf(stderr, "%s", buffer);
      rend_SetErrorMessage(buffer);
      return (0);
    }
  }

  SDL_SetEventFilter(d3SDLEventFilter, NULL);

  bool fullscreen = true;

  if (FindArgChar("-fullscreen", 'f')) {
    fullscreen = true;
  } else if (FindArgChar("-windowed", 'w')) {
    fullscreen = false;
  }

  if (!Already_loaded) {
#define MAX_ARGS 30
#define MAX_CHARS_PER_ARG 100
    extern char GameArgs[MAX_ARGS][MAX_CHARS_PER_ARG];

    char gl_library[256];
    int arg;
    arg = FindArgChar("-gllibrary", 'g');
    if (arg != 0) {
      strcpy(gl_library, GameArgs[arg + 1]);
    } else {
        gl_library[0] = 0;
    }

    mprintf(0, "OpenGL: Attempting to use \"%s\" for OpenGL\n", gl_library[0] ? gl_library : "[system default library]");

    // ryan's adds. 04/18/2000...SDL stuff on 04/25/2000
    bool success = true;

    OpenGLDLLHandle = LoadOpenGLDLL("opengl32.dll");
    // OpenGLDLLHandle = LoadOpenGLDLL(gl_library);
    if (!(OpenGLDLLHandle)) {
      // rcg07072000 last ditch effort...
      OpenGLDLLHandle = LoadOpenGLDLL("libGL.so.1");
      if (!(OpenGLDLLHandle)) {
        success = false;
      }
    } // if

    if (success == false) {
      char buffer[512];
      snprintf(buffer, sizeof(buffer), "Failed to load library [%s].\n", gl_library);
      fprintf(stderr, "%s", buffer);
      rend_SetErrorMessage(buffer);
      return 0;
    } // if
  }

#ifdef __PERMIT_GL_LOGGING
  if (FindArg("-gllogging")) {
    printf("\n"
           "************************************************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "********   GL LOGGING ENABLED.   ***************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "************************************************************\n"
           "\n");
    DGL_EnableLogging(1);
    __glLog = true;
  } // if
#endif

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  Uint32 flags = SDL_WINDOW_OPENGL;

  if (fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if (!GSDLWindow) {
    GSDLWindow = SDL_CreateWindow("Descent 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winw, winh, flags);
    if (!GSDLWindow) {
      mprintf(0, "OpenGL: SDL window creation failed: %s", SDL_GetError());
      return 0;
    }
  } else {
    SDL_SetWindowSize(GSDLWindow, winw, winh);
    SDL_SetWindowFullscreen(GSDLWindow, flags);
  }

  if (!GSDLGLContext) {
    GSDLGLContext = SDL_GL_CreateContext(GSDLWindow);
    if (!GSDLGLContext) {
      mprintf(0, "OpenGL: OpenGL context creation failed: %s", SDL_GetError());
      SDL_DestroyWindow(GSDLWindow);
      GSDLWindow = NULL;
      return 0;
    }
  }

  // clear the window framebuffer to start.
  dglClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  dglClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapWindow(GSDLWindow);

  bool fbo_available = true;
  if (!SDL_GL_ExtensionSupported("GL_EXT_framebuffer_object")) {
    mprintf(0, "OpenGL: GL_EXT_framebuffer_object extension is not available");
    fbo_available = false;
  }

  if (!SDL_GL_ExtensionSupported("GL_EXT_framebuffer_blit")) {
      mprintf(0, "OpenGL: GL_EXT_framebuffer_blit extension is not available");
      fbo_available = false;
  }

  if (fbo_available) {
    #define LOOKUP_GL_SYM(x) \
      dgl##x = (gl##x##_fp) SDL_GL_GetProcAddress("gl" #x); \
      if (dgl##x == NULL) { \
        mprintf(0, "OpenGL: gl%s function not found!", #x); \
        fbo_available = false; \
      }
    LOOKUP_GL_SYM(GenFramebuffersEXT);
    LOOKUP_GL_SYM(GenRenderbuffersEXT);
    LOOKUP_GL_SYM(BindFramebufferEXT);
    LOOKUP_GL_SYM(BindRenderbufferEXT);
    LOOKUP_GL_SYM(RenderbufferStorageEXT);
    LOOKUP_GL_SYM(FramebufferRenderbufferEXT);
    LOOKUP_GL_SYM(CheckFramebufferStatusEXT);
    LOOKUP_GL_SYM(DeleteFramebuffersEXT);
    LOOKUP_GL_SYM(DeleteRenderbuffersEXT);
    LOOKUP_GL_SYM(BlitFramebufferEXT);
  }

  if (!fbo_available) {
    mprintf(0, "OpenGL: We need missing Framebuffer Object support, giving up");
    SDL_GL_DeleteContext(GSDLGLContext);
    SDL_DestroyWindow(GSDLWindow);
    GSDLGLContext = NULL;
    GSDLWindow = NULL;
    return 0;
  }

  /* Tear down the backbuffer and rebuild at new dimensions... */
  if (GOpenGLFBO) {
    dglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GOpenGLFBO);
    dglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, 0);
    dglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, 0);
    dglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    dglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    dglDeleteFramebuffersEXT(1, &GOpenGLFBO);
    dglDeleteRenderbuffersEXT(1, &GOpenGLRBOColor);
    dglDeleteRenderbuffersEXT(1, &GOpenGLRBODepth);
    GOpenGLFBOWidth = GOpenGLFBOHeight = GOpenGLFBO = GOpenGLRBOColor = GOpenGLRBODepth = 0;
  }

  const GLsizei w = (GLsizei) *width;
  const GLsizei h = (GLsizei) *height;

  GOpenGLFBOWidth = w;
  GOpenGLFBOHeight = h;

  dglGenFramebuffersEXT(1, &GOpenGLFBO);
  dglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GOpenGLFBO);

  dglGenRenderbuffersEXT(1, &GOpenGLRBOColor);
  dglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, GOpenGLRBOColor);
  dglRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB, w, h);
  dglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, GOpenGLRBOColor);

  dglGenRenderbuffersEXT(1, &GOpenGLRBODepth);
  dglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, GOpenGLRBODepth);
  dglRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT16_EXT, w, h);
  dglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, GOpenGLRBODepth);

  if (dglCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT) {
      mprintf(0, "OpenGL: our framebuffer object is incomplete, giving up");
      dglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, 0);
      dglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, 0);
      dglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
      dglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
      dglDeleteFramebuffersEXT(1, &GOpenGLFBO);
      dglDeleteRenderbuffersEXT(1, &GOpenGLRBOColor);
      dglDeleteRenderbuffersEXT(1, &GOpenGLRBODepth);
      GOpenGLFBO = GOpenGLRBOColor = GOpenGLRBODepth = 0;
      SDL_GL_DeleteContext(GSDLGLContext);
      SDL_DestroyWindow(GSDLWindow);
      GSDLGLContext = NULL;
      GSDLWindow = NULL;
      return 0;
  }

  if (!FindArg("-nomousegrab")) {
    ddio_mouseGrabbed = true;
  }

  SDL_SetRelativeMouseMode(ddio_mouseGrabbed ? SDL_TRUE : SDL_FALSE);

  // rcg09182000 gamma fun.
  // rcg01112000 --nogamma fun.
  if (FindArgChar("-nogamma", 'M')) {
    linux_permit_gamma = false;
  } else {
    Uint16 ramp[256];
    SDL_CalculateGammaRamp(Render_preferred_state.gamma, ramp);
    linux_permit_gamma = (SDL_SetWindowGammaRamp(GSDLWindow, ramp, ramp, ramp) == 0);
  } // else

  if (ParentApplication) {
    reinterpret_cast<oeLnxApplication *>(ParentApplication)->set_sizepos(0, 0, *width, *height);
  }

  Already_loaded = 1;
  return 1;
}

// Sets up our OpenGL rendering context
// Returns 1 if ok, 0 if something bad
int opengl_Init(oeApplication *app, renderer_preferred_state *pref_state) {
  int width, height;
  int retval = 1;
  int i;

  mprintf(0, "Setting up opengl mode!\n");

  if (pref_state) {
    gpu_preferred_state = *pref_state;
  }

  if (app != NULL) {
    ParentApplication = app;
  }

  int windowX = 0, windowY = 0;

  /***********************************************************
   *               LINUX OPENGL
   ***********************************************************
   */
  // Setup gpu_state.screen_width & gpu_state.screen_height & width & height
  width = gpu_preferred_state.width;
  height = gpu_preferred_state.height;

  if (!opengl_Setup(app, &width, &height)) {
    opengl_Close();
    return 0;
  }

  memset(&gpu_state, 0, sizeof(rendering_state));
  gpu_state.screen_width = width;
  gpu_state.screen_height = height;

  // Get some info
  opengl_GetInformation();

  mprintf(0, "Setting up multitexture...\n");

  // Determine if Multitexture is supported
  bool supportsMultiTexture = opengl_CheckExtension("GL_ARB_multitexture");
  if (!supportsMultiTexture) {
    supportsMultiTexture = opengl_CheckExtension("GL_SGIS_multitexture");
  }

  if (FindArg("-NoMultitexture")) {
    supportsMultiTexture = false;
  }

  if (supportsMultiTexture) {
    // attempt to grab Multitexture functions
    opengl_GetDLLFunctions();
  } else {
    // No multitexture at all
    UseMultitexture = false;
  }

  // Do we have packed pixel formats?
  OpenGL_packed_pixels = opengl_CheckExtension("GL_EXT_packed_pixels");

  opengl_InitCache();

  if (UseMultitexture) {
    mprintf(0, "Using multitexture.");
  } else {
    mprintf(0, "Not using multitexture.");
  }

  if (OpenGL_packed_pixels) {
    opengl_packed_Upload_data = (uint16_t *)mem_malloc(2048 * 2048 * 2);
    opengl_packed_Translate_table = (uint16_t *)mem_malloc(65536 * 2);
    opengl_packed_4444_translate_table = (uint16_t *)mem_malloc(65536 * 2);

    ASSERT(opengl_packed_Upload_data);
    ASSERT(opengl_packed_Translate_table);
    ASSERT(opengl_packed_4444_translate_table);

    mprintf(0, "Building packed OpenGL translate table...\n");

    for (i = 0; i < 65536; i++) {
      int r = (i >> 10) & 0x1f;
      int g = (i >> 5) & 0x1f;
      int b = i & 0x1f;

#ifdef BRIGHTNESS_HACK
      r *= BRIGHTNESS_HACK;
      g *= BRIGHTNESS_HACK;
      b *= BRIGHTNESS_HACK;
      if (r > 0x1F)
        r = 0x1F;
      if (g > 0x1F)
        g = 0x1F;
      if (b > 0x1F)
        b = 0x1F;
#endif

      uint16_t pix;

      if (!(i & OPAQUE_FLAG)) {
        pix = 0;
      } else {
        pix = (r << 11) | (g << 6) | (b << 1) | 1;
      }

      opengl_packed_Translate_table[i] = INTEL_INT(pix);

      // 4444 table
      int a = (i >> 12) & 0xf;
      r = (i >> 8) & 0xf;
      g = (i >> 4) & 0xf;
      b = i & 0xf;

      pix = (r << 12) | (g << 8) | (b << 4) | a;
      opengl_packed_4444_translate_table[i] = INTEL_INT(pix);
    }
  } else {
    opengl_Upload_data = (uint32_t *)mem_malloc(2048 * 2048 * 4);
    opengl_Translate_table = (uint32_t *)mem_malloc(65536 * 4);
    opengl_4444_translate_table = (uint32_t *)mem_malloc(65536 * 4);

    ASSERT(opengl_Upload_data);
    ASSERT(opengl_Translate_table);
    ASSERT(opengl_4444_translate_table);

    mprintf(0, "Building OpenGL translate table...\n");

    for (i = 0; i < 65536; i++) {
      uint32_t pix;
      int r = (i >> 10) & 0x1f;
      int g = (i >> 5) & 0x1f;
      int b = i & 0x1f;

#ifdef BRIGHTNESS_HACK
      r *= BRIGHTNESS_HACK;
      g *= BRIGHTNESS_HACK;
      b *= BRIGHTNESS_HACK;
      if (r > 0x1F)
        r = 0x1F;
      if (g > 0x1F)
        g = 0x1F;
      if (b > 0x1F)
        b = 0x1F;
#endif

      float fr = (float)r / 31.0f;
      float fg = (float)g / 31.0f;
      float fb = (float)b / 31.0f;

      r = 255 * fr;
      g = 255 * fg;
      b = 255 * fb;

      if (!(i & OPAQUE_FLAG)) {
        pix = 0;
      } else {
        pix = (255 << 24) | (b << 16) | (g << 8) | (r);
      }

      opengl_Translate_table[i] = INTEL_INT(pix);

      // Do 4444
      int a = (i >> 12) & 0xf;
      r = (i >> 8) & 0xf;
      g = (i >> 4) & 0xf;
      b = i & 0xf;

      float fa = (float)a / 15.0f;
      fr = (float)r / 15.0f;
      fg = (float)g / 15.0f;
      fb = (float)b / 15.0f;

      a = 255 * fa;
      r = 255 * fr;
      g = 255 * fg;
      b = 255 * fb;

      pix = (a << 24) | (b << 16) | (g << 8) | (r);

      opengl_4444_translate_table[i] = INTEL_INT(pix);
    }
  }

  opengl_SetDefaults();

  g3_ForceTransformRefresh();

  CHECK_ERROR(4)

  gpu_state.initted = 1;

  mprintf(0, "OpenGL initialization at %d x %d was successful.\n", width, height);

  return retval;
}

// Releases the rendering context
void opengl_Close(const bool just_resizing) {
  CHECK_ERROR(5)

  uint32_t *delete_list = (uint32_t *)mem_malloc(Cur_texture_object_num * sizeof(int));
  ASSERT(delete_list);
  for (int i = 1; i < Cur_texture_object_num; i++)
    delete_list[i] = i;

  if (Cur_texture_object_num > 1)
    dglDeleteTextures(Cur_texture_object_num, (const uint32_t *)delete_list);

  mem_free(delete_list);

  if (GSDLGLContext) {
      SDL_GL_MakeCurrent(NULL, NULL);
      SDL_GL_DeleteContext(GSDLGLContext);
      GSDLGLContext = NULL;
      GOpenGLFBOWidth = GOpenGLFBOHeight = GOpenGLFBO = GOpenGLRBOColor = GOpenGLRBODepth = 0;
  }

  if (!just_resizing && GSDLWindow) {
      SDL_DestroyWindow(GSDLWindow);
      GSDLWindow = NULL;
  }


  if (OpenGL_packed_pixels) {
    if (opengl_packed_Upload_data) {
      mem_free(opengl_packed_Upload_data);
    }
    if (opengl_packed_Translate_table) {
      mem_free(opengl_packed_Translate_table);
    }
    if (opengl_packed_4444_translate_table) {
      mem_free(opengl_packed_4444_translate_table);
    }
    opengl_packed_Upload_data = NULL;
    opengl_packed_Translate_table = NULL;
    opengl_packed_4444_translate_table = NULL;
  } else {
    if (opengl_Upload_data)
      mem_free(opengl_Upload_data);
    if (opengl_Translate_table)
      mem_free(opengl_Translate_table);
    if (opengl_4444_translate_table)
      mem_free(opengl_4444_translate_table);
    opengl_Upload_data = NULL;
    opengl_Translate_table = NULL;
    opengl_4444_translate_table = NULL;
  }

  if (OpenGL_cache_initted) {
    mem_free(OpenGL_lightmap_remap);
    mem_free(OpenGL_bitmap_remap);
    mem_free(OpenGL_lightmap_states);
    mem_free(OpenGL_bitmap_states);
    OpenGL_cache_initted = 0;
  }

  // mod_FreeModule (OpenGLDLLHandle);
  gpu_state.initted = 0;
}

// Takes our 16bit format and converts it into the memory scheme that OpenGL wants
void opengl_TranslateBitmapToOpenGL(int texnum, int bm_handle, int map_type, int replace, int tn) {
  uint16_t *bm_ptr;

  int w, h;
  int size;

  if (UseMultitexture && Last_texel_unit_set != tn) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
    oglActiveTextureARB(GL_TEXTURE0_ARB + tn);
    Last_texel_unit_set = tn;
#endif
  }

  if (map_type == MAP_TYPE_LIGHTMAP) {
    if (GameLightmaps[bm_handle].flags & LF_BRAND_NEW)
      replace = 0;

    bm_ptr = lm_data(bm_handle);
    GameLightmaps[bm_handle].flags &= ~(LF_CHANGED | LF_BRAND_NEW);

    w = lm_w(bm_handle);
    h = lm_h(bm_handle);
    size = GameLightmaps[bm_handle].square_res;
  } else {
    if (GameBitmaps[bm_handle].flags & BF_BRAND_NEW)
      replace = 0;

    bm_ptr = bm_data(bm_handle, 0);
    GameBitmaps[bm_handle].flags &= ~(BF_CHANGED | BF_BRAND_NEW);
    w = bm_w(bm_handle, 0);
    h = bm_h(bm_handle, 0);
    size = w;
  }

  if (OpenGL_last_bound[tn] != texnum) {
    dglBindTexture(GL_TEXTURE_2D, texnum);
    OpenGL_sets_this_frame[0]++;
    OpenGL_last_bound[tn] = texnum;
  }

  int i;

  if (OpenGL_packed_pixels) {
    if (map_type == MAP_TYPE_LIGHTMAP) {
      uint16_t *left_data = (uint16_t *)opengl_packed_Upload_data;
      int bm_left = 0;

      for (int i = 0; i < h; i++, left_data += size, bm_left += w) {
        uint16_t *dest_data = left_data;
        for (int t = 0; t < w; t++) {
          *dest_data++ = opengl_packed_Translate_table[bm_ptr[bm_left + t]];
        }
      }

      if (replace) {
        dglTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, size, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,
                         opengl_packed_Upload_data);
      } else {
        dglTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5_A1, size, size, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,
                      opengl_packed_Upload_data);
      }
    } else {
      int limit = 0;

      if (bm_mipped(bm_handle)) {
        limit = NUM_MIP_LEVELS + 3;
      } else {
        limit = 1;
      }

      for (int m = 0; m < limit; m++) {
        if (m < NUM_MIP_LEVELS) {
          bm_ptr = bm_data(bm_handle, m);
          w = bm_w(bm_handle, m);
          h = bm_h(bm_handle, m);
        } else {
          bm_ptr = bm_data(bm_handle, NUM_MIP_LEVELS - 1);
          w = bm_w(bm_handle, NUM_MIP_LEVELS - 1);
          h = bm_h(bm_handle, NUM_MIP_LEVELS - 1);

          w >>= m - (NUM_MIP_LEVELS - 1);
          h >>= m - (NUM_MIP_LEVELS - 1);

          if ((w < 1) || (h < 1))
            continue;
        }

        if (bm_format(bm_handle) == BITMAP_FORMAT_4444) {
          // Do 4444
          if (bm_mipped(bm_handle)) {
            for (i = 0; i < w * h; i++)
              opengl_packed_Upload_data[i] = 0xf | (opengl_packed_4444_translate_table[bm_ptr[i]]);
          } else {
            for (i = 0; i < w * h; i++)
              opengl_packed_Upload_data[i] = opengl_packed_4444_translate_table[bm_ptr[i]];
          }

          if (replace) {
            dglTexSubImage2D(GL_TEXTURE_2D, m, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4,
                             opengl_packed_Upload_data);
          } else {
            dglTexImage2D(GL_TEXTURE_2D, m, GL_RGBA4, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4,
                          opengl_packed_Upload_data);
          }
        } else {
          // Do 1555
          for (i = 0; i < w * h; i++) {
            opengl_packed_Upload_data[i] = opengl_packed_Translate_table[bm_ptr[i]];
          }

          if (replace) {
            dglTexSubImage2D(GL_TEXTURE_2D, m, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,
                             opengl_packed_Upload_data);
          } else {
            dglTexImage2D(GL_TEXTURE_2D, m, GL_RGB5_A1, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,
                          opengl_packed_Upload_data);
          }
        }
      }
    }
  } else {
    if (map_type == MAP_TYPE_LIGHTMAP) {
      uint32_t *left_data = (uint32_t *)opengl_Upload_data;
      int bm_left = 0;

      for (int i = 0; i < h; i++, left_data += size, bm_left += w) {
        uint32_t *dest_data = left_data;
        for (int t = 0; t < w; t++) {
          *dest_data++ = opengl_Translate_table[bm_ptr[bm_left + t]];
        }
      }
      if (size > 0) {
        if (replace) {
          dglTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, size, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
        } else {
          dglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
        }
      }
    } else {
      int limit = 0;

      if (bm_mipped(bm_handle)) {
        limit = NUM_MIP_LEVELS + 3; // ryan added +3.
      } else {
        limit = 1;
      }

      for (int m = 0; m < limit; m++) {
        bm_ptr = bm_data(bm_handle, m);
        w = bm_w(bm_handle, m);
        h = bm_h(bm_handle, m);

        if (bm_format(bm_handle) == BITMAP_FORMAT_4444) {
          // Do 4444

          if (bm_mipped(bm_handle)) {
            for (i = 0; i < w * h; i++)
              opengl_Upload_data[i] = INTEL_INT((255 << 24)) | opengl_4444_translate_table[bm_ptr[i]];
          } else {
            for (i = 0; i < w * h; i++)
              opengl_Upload_data[i] = opengl_4444_translate_table[bm_ptr[i]];
          }
        } else {
          // Do 1555

          for (i = 0; i < w * h; i++)
            opengl_Upload_data[i] = opengl_Translate_table[bm_ptr[i]];
        }

        // rcg06262000 my if wrapper.
        if ((w > 0) && (h > 0)) {
          if (replace) {
            dglTexSubImage2D(GL_TEXTURE_2D, m, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
          } else {
            dglTexImage2D(GL_TEXTURE_2D, m, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, opengl_Upload_data);
          }
        }
      }
    }
  }

  // mprintf(1,"Doing slow upload to opengl!\n");

  if (map_type == MAP_TYPE_LIGHTMAP) {
    GameLightmaps[bm_handle].flags &= ~LF_LIMITS;
  }

  CHECK_ERROR(6)
  OpenGL_uploads++;
}

extern bool Force_one_texture;

// Utilizes a LRU cacheing scheme to select/upload textures the opengl driver
int opengl_MakeBitmapCurrent(int handle, int map_type, int tn) {
  int w, h;
  int texnum;

  if (map_type == MAP_TYPE_LIGHTMAP) {
    w = GameLightmaps[handle].square_res;
    h = GameLightmaps[handle].square_res;
  } else {
    if (Force_one_texture) {
      handle = 0;
    }

    w = bm_w(handle, 0);
    h = bm_h(handle, 0);
  }

  if (w != h) {
    mprintf(0, "Can't use non-square textures with OpenGL!\n");
    return 0;
  }

  // See if the bitmaps is already in the cache
  if (map_type == MAP_TYPE_LIGHTMAP) {
    if (OpenGL_lightmap_remap[handle] == 65535) {
      texnum = opengl_MakeTextureObject(tn);
      SET_WRAP_STATE(OpenGL_lightmap_states[handle], 1);
      SET_FILTER_STATE(OpenGL_lightmap_states[handle], 0);
      OpenGL_lightmap_remap[handle] = texnum;
      opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 0, tn);
    } else {
      texnum = OpenGL_lightmap_remap[handle];
      if (GameLightmaps[handle].flags & LF_CHANGED)
        opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 1, tn);
    }
  } else {
    if (OpenGL_bitmap_remap[handle] == 65535) {
      texnum = opengl_MakeTextureObject(tn);
      SET_WRAP_STATE(OpenGL_bitmap_states[handle], 1);
      SET_FILTER_STATE(OpenGL_bitmap_states[handle], 0);
      OpenGL_bitmap_remap[handle] = texnum;
      opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 0, tn);
    } else {
      texnum = OpenGL_bitmap_remap[handle];
      if (GameBitmaps[handle].flags & BF_CHANGED) {
        opengl_TranslateBitmapToOpenGL(texnum, handle, map_type, 1, tn);
      }
    }
  }

  if (OpenGL_last_bound[tn] != texnum) {
    if (UseMultitexture && Last_texel_unit_set != tn) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
      oglActiveTextureARB(GL_TEXTURE0_ARB + tn);
      Last_texel_unit_set = tn;
#endif
    }

    dglBindTexture(GL_TEXTURE_2D, texnum);
    OpenGL_last_bound[tn] = texnum;
    OpenGL_sets_this_frame[0]++;
  }

  CHECK_ERROR(7)
  return 1;
}

// Sets up an appropriate wrap type for the current bound texture
void opengl_MakeWrapTypeCurrent(int handle, int map_type, int tn) {
  int uwrap;
  wrap_type dest_wrap;

  if (tn == 1)
    dest_wrap = WT_CLAMP;
  else
    dest_wrap = gpu_state.cur_wrap_type;

  if (map_type == MAP_TYPE_LIGHTMAP)
    uwrap = GET_WRAP_STATE(OpenGL_lightmap_states[handle]);
  else
    uwrap = GET_WRAP_STATE(OpenGL_bitmap_states[handle]);

  if (uwrap == dest_wrap)
    return;

  if (UseMultitexture && Last_texel_unit_set != tn) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
    oglActiveTextureARB(GL_TEXTURE0_ARB + tn);
    Last_texel_unit_set = tn;
#endif
  }

  OpenGL_sets_this_frame[1]++;

  if (gpu_state.cur_wrap_type == WT_CLAMP) {
    dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  } else if (gpu_state.cur_wrap_type == WT_WRAP_V) {
    dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  } else {
    dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }

  if (map_type == MAP_TYPE_LIGHTMAP) {
    SET_WRAP_STATE(OpenGL_lightmap_states[handle], dest_wrap);
  } else {
    SET_WRAP_STATE(OpenGL_bitmap_states[handle], dest_wrap);
  }

  CHECK_ERROR(8)
}

// Chooses the correct filter type for the currently bound texture
void opengl_MakeFilterTypeCurrent(int handle, int map_type, int tn) {
  int magf;
  int8_t dest_state;

  if (map_type == MAP_TYPE_LIGHTMAP) {
    magf = GET_FILTER_STATE(OpenGL_lightmap_states[handle]);
    dest_state = 1;
  } else {
    magf = GET_FILTER_STATE(OpenGL_bitmap_states[handle]);
    dest_state = gpu_preferred_state.filtering;
    if (!gpu_state.cur_bilinear_state)
      dest_state = 0;
  }

  if (magf == dest_state)
    return;
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
  if (UseMultitexture && Last_texel_unit_set != tn) {
    oglActiveTextureARB(GL_TEXTURE0_ARB + tn);
    Last_texel_unit_set = tn;
  }
#endif

  OpenGL_sets_this_frame[2]++;

  if (dest_state) {
    if (map_type == MAP_TYPE_BITMAP && bm_mipped(handle)) {
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    } else {
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
  } else {
    if (map_type == MAP_TYPE_BITMAP && bm_mipped(handle)) {
      // dglTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_NEAREST);
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    } else {
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      dglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
  }

  if (map_type == MAP_TYPE_LIGHTMAP) {
    SET_FILTER_STATE(OpenGL_lightmap_states[handle], dest_state);
  } else {
    SET_FILTER_STATE(OpenGL_bitmap_states[handle], dest_state);
  }

  CHECK_ERROR(9)
}

// Turns on/off multitexture blending
void gpu_SetMultitextureBlendMode(bool state) {
  if (OpenGL_multitexture_state == state)
    return;
  OpenGL_multitexture_state = state;

#if (defined(_USE_OGL_ACTIVE_TEXTURES))
  oglActiveTextureARB(GL_TEXTURE1_ARB);
  oglClientActiveTextureARB(GL_TEXTURE1_ARB);
  if (state) {
    dglEnableClientState(GL_TEXTURE_COORD_ARRAY);
    dglEnable(GL_TEXTURE_2D);
  } else {
    dglDisableClientState(GL_TEXTURE_COORD_ARRAY);
    dglDisable(GL_TEXTURE_2D);
  }
  oglActiveTextureARB(GL_TEXTURE0_ARB);
  oglClientActiveTextureARB(GL_TEXTURE0_ARB);
  Last_texel_unit_set = 0;
#endif
}

void gpu_DrawFlatPolygon3D(g3Point **p, int nv) {
  float fr, fg, fb;
  int i;

  if (UseMultitexture) {
    gpu_SetMultitextureBlendMode(false);
  }

  float alpha = gpu_Alpha_multiplier * gpu_Alpha_factor;

  fr = GR_COLOR_RED(gpu_state.cur_color);
  fg = GR_COLOR_GREEN(gpu_state.cur_color);
  fb = GR_COLOR_BLUE(gpu_state.cur_color);
  fr /= 255.0;
  fg /= 255.0;
  fb /= 255.0;

  // And draw!
  dglBegin(GL_POLYGON);
  for (i = 0; i < nv; i++) {
    g3Point *pnt = p[i];
    ASSERT(pnt->p3_flags & PF_ORIGPOINT);

    if (gpu_state.cur_alpha_type & ATF_VERTEX)
      alpha = pnt->p3_a * gpu_Alpha_multiplier * gpu_Alpha_factor;

    // If we have a lighting model, apply the correct lighting!
    if (gpu_state.cur_light_state != LS_NONE) {
      // Do lighting based on intesity (MONO) or colored (RGB)
      if (gpu_state.cur_color_model == CM_MONO)
        dglColor4f(pnt->p3_l, pnt->p3_l, pnt->p3_l, alpha);
      else {
        dglColor4f(pnt->p3_r, pnt->p3_g, pnt->p3_b, alpha);
      }

    } else {
      dglColor4f(fr, fg, fb, alpha);
    }

    /*
    // Finally, specify a vertex
    float z = std::max(0,std::min(1.0,1.0-(1.0/(pnt->p3_z+Z_bias))));
    dglVertex3f (pnt->p3_sx+x_add,pnt->p3_sy+y_add,-z);
    */
    dglVertex3f(pnt->p3_vecPreRot.x, pnt->p3_vecPreRot.y, pnt->p3_vecPreRot.z);
  }

  dglEnd();
  CHECK_ERROR(11)
  OpenGL_polys_drawn++;
  OpenGL_verts_processed += nv;
}

// Sets the gamma correction value
void rend_SetGammaValue(float val) {
  //	if( WindowGL )
  //		return;

  gpu_preferred_state.gamma = val;
  mprintf(0, "Setting gamma to %f\n", val);
}

// Resets the texture cache
void opengl_ResetCache(void) {
  if (OpenGL_cache_initted) {
    mem_free(OpenGL_lightmap_remap);
    mem_free(OpenGL_bitmap_remap);
    mem_free(OpenGL_lightmap_states);
    mem_free(OpenGL_bitmap_states);
    OpenGL_cache_initted = 0;
  }

  opengl_InitCache();
}

uint8_t opengl_Framebuffer_ready = 0;
chunked_bitmap opengl_Chunked_bitmap;

void opengl_ChangeChunkedBitmap(int bm_handle, chunked_bitmap *chunk) {
  int bw = bm_w(bm_handle, 0);
  int bh = bm_h(bm_handle, 0);

  // determine optimal size of the square bitmaps
  float fopt = 128.0f;
  int iopt;

  // find the smallest dimension and base off that
  int smallest = std::min(bw, bh);

  if (smallest <= 32)
    fopt = 32;
  else if (smallest <= 64)
    fopt = 64;
  else
    fopt = 128;

  iopt = (int)fopt;

  // Get how many pieces we need across and down
  float temp = bw / fopt;
  int how_many_across = temp;
  if ((temp - how_many_across) > 0)
    how_many_across++;

  temp = bh / fopt;
  int how_many_down = temp;
  if ((temp - how_many_down) > 0)
    how_many_down++;

  ASSERT(how_many_across > 0);
  ASSERT(how_many_down > 0);

  // Now go through our big bitmap and partition it into pieces
  uint16_t *src_data = bm_data(bm_handle, 0);
  uint16_t *sdata;
  uint16_t *ddata;

  int shift;
  switch (iopt) {
  case 32:
    shift = 5;
    break;
  case 64:
    shift = 6;
    break;
  case 128:
    shift = 7;
    break;
  default:
    Int3(); // Get Jeff
    break;
  }
  int maxx, maxy;
  int windex, hindex;
  int s_y, s_x, d_y, d_x;

  for (hindex = 0; hindex < how_many_down; hindex++) {
    for (windex = 0; windex < how_many_across; windex++) {
      // loop through the chunks
      // find end x and y
      if (windex < how_many_across - 1)
        maxx = iopt;
      else
        maxx = bw - (windex << shift);
      if (hindex < how_many_down - 1)
        maxy = iopt;
      else
        maxy = bh - (hindex << shift);

      // find the starting source x and y
      s_x = (windex << shift);
      s_y = (hindex << shift);

      // get the pointers pointing to the right spot
      ddata = bm_data(chunk->bm_array[hindex * how_many_across + windex], 0);
      GameBitmaps[chunk->bm_array[hindex * how_many_across + windex]].flags |= BF_CHANGED;
      sdata = &src_data[s_y * bw + s_x];

      // copy the data
      for (d_y = 0; d_y < maxy; d_y++) {
        for (d_x = 0; d_x < maxx; d_x++) {
          ddata[d_x] = sdata[d_x];
        } // end for d_x
        sdata += bw;
        ddata += iopt;
      } // end for d_y

    } // end for windex
  }   // end for hindex
}

// Tells the software renderer whether or not to use mipping
void rend_SetMipState(int8_t mipstate) {}

// Init our renderer
int rend_Init(renderer_type state, oeApplication *app, renderer_preferred_state *pref_state) {
#ifndef DEDICATED_ONLY
  int retval = 0;
  rend_SetRendererType(state);
  if (!Renderer_initted) {
    if (!Renderer_close_flag) {
      atexit(rend_Close);
      Renderer_close_flag = 1;
    }

    Renderer_initted = 1;
  }

  if (OpenGL_window_initted) {
    rend_CloseOpenGLWindow();
    OpenGL_window_initted = 0;
  }

  mprintf(0, "Renderer init is set to %d\n", Renderer_initted);

#ifndef OEM_V3
  int flags = app->flags();
  if (flags & OEAPP_WINDOWED) {
    // initialize for windowed
    retval = rend_InitOpenGLWindow(app, pref_state);
  } else {
    // initialize for full screen
    retval = opengl_Init(app, pref_state);
  }
#endif

  return retval;
#else
  return 0;
#endif // #ifdef DEDICATED_ONLY
}

void rend_Close(void) {
  mprintf(0, "CLOSE:Renderer init is set to %d\n", Renderer_initted);
  if (!Renderer_initted)
    return;

  if (OpenGL_window_initted) {
    if (Renderer_type == RENDERER_OPENGL) {
      rend_CloseOpenGLWindow();
    }
    OpenGL_window_initted = 0;
  }

  opengl_Close();

  Renderer_initted = 0;
}

void gpu_BindTexture(int handle, int map_type, int slot) {
  opengl_MakeBitmapCurrent(handle, map_type, slot);
  opengl_MakeWrapTypeCurrent(handle, map_type, slot);
  opengl_MakeFilterTypeCurrent(handle, map_type, slot);
}

void gpu_RenderPolygon(PosColorUVVertex *vData, uint32_t nv) {
  dglVertexPointer(3, GL_FLOAT, sizeof(*vData), &vData->pos);
  dglColorPointer(4, GL_FLOAT, sizeof(*vData), &vData->color);
  oglClientActiveTextureARB(GL_TEXTURE0_ARB + 0);
  dglTexCoordPointer(4, GL_FLOAT, sizeof(*vData), &vData->uv);

  if (gpu_state.cur_texture_quality == 0) {
    // force disable textures
    dglDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }

  oglClientActiveTextureARB(GL_TEXTURE0_ARB + 1);
  dglDisableClientState(GL_TEXTURE_COORD_ARRAY);

  // draw the data in the arrays
  dglDrawArrays(GL_POLYGON, 0, nv);

  if (gpu_state.cur_texture_quality == 0) {
    // re-enable textures
    oglClientActiveTextureARB(GL_TEXTURE0_ARB + 0);
    dglEnableClientState(GL_TEXTURE_COORD_ARRAY);
  }

  OpenGL_polys_drawn++;
  OpenGL_verts_processed += nv;
}

void gpu_RenderPolygonUV2(PosColorUV2Vertex *vData, uint32_t nv) {
  dglVertexPointer(3, GL_FLOAT, sizeof(*vData), &vData->pos);
  dglColorPointer(4, GL_FLOAT, sizeof(*vData), &vData->color);
  oglClientActiveTextureARB(GL_TEXTURE0_ARB + 0);
  dglTexCoordPointer(4, GL_FLOAT, sizeof(*vData), &vData->uv0);
  oglClientActiveTextureARB(GL_TEXTURE0_ARB + 1);
  dglEnableClientState(GL_TEXTURE_COORD_ARRAY);
  dglTexCoordPointer(4, GL_FLOAT, sizeof(*vData), &vData->uv1);

  dglDrawArrays(GL_POLYGON, 0, nv);
  OpenGL_polys_drawn++;
  OpenGL_verts_processed += nv;

  CHECK_ERROR(10)
}

void rend_SetFlatColor(ddgr_color color) { gpu_state.cur_color = color; }

// Sets the fog state to TRUE or FALSE
void rend_SetFogState(int8_t state) {
  if (state == gpu_state.cur_fog_state)
    return;

  gpu_state.cur_fog_state = state;
  if (state == 1) {
    dglEnable(GL_FOG);
  } else {
    dglDisable(GL_FOG);
  }
}

// Sets the near and far plane of fog
void rend_SetFogBorders(float nearz, float farz) {
  // Sets the near and far plane of fog
  float fogStart = nearz;
  float fogEnd = farz;

  gpu_state.cur_fog_start = fogStart;
  gpu_state.cur_fog_end = fogEnd;

  dglFogi(GL_FOG_MODE, GL_LINEAR);
  dglFogf(GL_FOG_START, fogStart);
  dglFogf(GL_FOG_END, fogEnd);
}

void rend_SetRendererType(renderer_type state) {
  Renderer_type = state;
  mprintf(0, "RendererType is set to %d.\n", state);
}

void rend_SetLighting(light_state state) {
  if (state == gpu_state.cur_light_state)
    return; // No redundant state setting
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
  if (UseMultitexture && Last_texel_unit_set != 0) {
    oglActiveTextureARB(GL_TEXTURE0_ARB + 0);
    Last_texel_unit_set = 0;
  }
#endif

  OpenGL_sets_this_frame[4]++;

  switch (state) {
  case LS_NONE:
    dglShadeModel(GL_SMOOTH);
    gpu_state.cur_light_state = LS_NONE;
    break;
  case LS_FLAT_GOURAUD:
    dglShadeModel(GL_SMOOTH);
    gpu_state.cur_light_state = LS_FLAT_GOURAUD;
    break;
  case LS_GOURAUD:
  case LS_PHONG:
    dglShadeModel(GL_SMOOTH);
    gpu_state.cur_light_state = LS_GOURAUD;
    break;
  default:
    Int3();
    break;
  }

  CHECK_ERROR(13)
}

void rend_SetColorModel(color_model state) {
  switch (state) {
  case CM_MONO:
    gpu_state.cur_color_model = CM_MONO;
    break;
  case CM_RGB:
    gpu_state.cur_color_model = CM_RGB;
    break;
  default:
    Int3();
    break;
  }
}

void rend_SetTextureType(texture_type state) {
  if (state == gpu_state.cur_texture_type)
    return; // No redundant state setting
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
  if (UseMultitexture && Last_texel_unit_set != 0) {
    oglActiveTextureARB(GL_TEXTURE0_ARB + 0);
    Last_texel_unit_set = 0;
  }
#endif
  OpenGL_sets_this_frame[3]++;

  switch (state) {
  case TT_FLAT:
    dglDisable(GL_TEXTURE_2D);
    gpu_state.cur_texture_quality = 0;
    break;
  case TT_LINEAR:
  case TT_LINEAR_SPECIAL:
  case TT_PERSPECTIVE:
  case TT_PERSPECTIVE_SPECIAL:
    dglEnable(GL_TEXTURE_2D);
    gpu_state.cur_texture_quality = 2;
    break;
  default:
    Int3(); // huh? Get Jason
    break;
  }

  CHECK_ERROR(12)
  gpu_state.cur_texture_type = state;
}

void rend_StartFrame(int x1, int y1, int x2, int y2, int clear_flags) {
  if (clear_flags & RF_CLEAR_ZBUFFER) {
    dglClear(GL_DEPTH_BUFFER_BIT);
  }
  gpu_state.clip_x1 = x1;
  gpu_state.clip_y1 = y1;
  gpu_state.clip_x2 = x2;
  gpu_state.clip_y2 = y2;
}


// Flips the screen
void rend_Flip(void) {
#ifndef RELEASE
  int i;

  RTP_INCRVALUE(texture_uploads, OpenGL_uploads);
  RTP_INCRVALUE(polys_drawn, OpenGL_polys_drawn);

  mprintf_at(1, 1, 0, "Uploads=%d    Polys=%d   Verts=%d   ", OpenGL_uploads, OpenGL_polys_drawn, OpenGL_verts_processed);
  mprintf_at(1, 2, 0, "Sets= 0:%d   1:%d   2:%d   3:%d   ", OpenGL_sets_this_frame[0], OpenGL_sets_this_frame[1],
              OpenGL_sets_this_frame[2], OpenGL_sets_this_frame[3]);
  mprintf_at(1, 3, 0, "Sets= 4:%d   5:%d  ", OpenGL_sets_this_frame[4], OpenGL_sets_this_frame[5]);
  for (i = 0; i < 10; i++) {
    OpenGL_sets_this_frame[i] = 0;
  }
#endif

  gpu_last_frame_polys_drawn = OpenGL_polys_drawn;
  gpu_last_frame_verts_processed = OpenGL_verts_processed;
  gpu_last_uploaded = OpenGL_uploads;

  OpenGL_uploads = 0;
  OpenGL_polys_drawn = 0;
  OpenGL_verts_processed = 0;

  // if we're rendering to an FBO, scale to the window framebuffer!
  if (GOpenGLFBO != 0) {
    int w, h;
    SDL_GL_GetDrawableSize(GSDLWindow, &w, &h);

    int scaledHeight, scaledWidth;
    if (w < h) {
      scaledWidth = w;
      scaledHeight = (int) (((((double)GOpenGLFBOHeight) / ((double)GOpenGLFBOWidth))) * ((double)w));
    } else {
      scaledHeight = h;
      scaledWidth = (int) (((((double)GOpenGLFBOWidth) / ((double)GOpenGLFBOHeight))) * ((double)h));
    }

    const int centeredX = (w - scaledWidth) / 2;
    const int centeredY = (h - scaledHeight) / 2;

    dglBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
    dglClearColor (0.0f, 0.0f, 0.0f, 1.0f);
    dglClear(GL_COLOR_BUFFER_BIT);  // in case the Steam Overlay wrote to places we don't blit over.
    dglBlitFramebufferEXT(0, 0, GOpenGLFBOWidth, GOpenGLFBOHeight,
                          centeredX, centeredY, centeredX + scaledWidth, centeredY + scaledHeight,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);
    dglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  }

  SDL_GL_SwapWindow(GSDLWindow);

  // go back to drawing on the FBO until we want to blit to the window framebuffer again.
  if (GOpenGLFBO != 0) {
    dglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GOpenGLFBO);
    dglViewport(0, 0, GOpenGLFBOWidth, GOpenGLFBOHeight);
    dglScissor(0, 0, GOpenGLFBOWidth, GOpenGLFBOHeight);
  }

#ifdef __PERMIT_GL_LOGGING
  if (__glLog == true) {
    DGL_LogNewFrame();
  }
#endif
}

void rend_EndFrame(void) {}

// Sets the state of z-buffering to on or off
void rend_SetZBufferState(int8_t state) {
  if (state == gpu_state.cur_zbuffer_state)
    return; // No redundant state setting

  OpenGL_sets_this_frame[5]++;
  gpu_state.cur_zbuffer_state = state;

  //	mprintf(0,"OPENGL: Setting zbuffer state to %d.\n",state);

  if (state) {
    dglEnable(GL_DEPTH_TEST);
    dglDepthFunc(GL_LEQUAL);
  } else {
    dglDisable(GL_DEPTH_TEST);
  }

  CHECK_ERROR(14)
}

// Clears the display to a specified color
void rend_ClearScreen(ddgr_color color) {
  int r = (color >> 16 & 0xFF);
  int g = (color >> 8 & 0xFF);
  int b = (color & 0xFF);

  dglClearColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 0);

  dglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Clears the zbuffer for the screen
void rend_ClearZBuffer(void) { dglClear(GL_DEPTH_BUFFER_BIT); }

// Clears the zbuffer for the screen
void rend_ResetCache(void) {
  mprintf(0, "Resetting texture cache!\n");
  opengl_ResetCache();
}

// Fills a rectangle on the display
void rend_FillRect(ddgr_color color, int x1, int y1, int x2, int y2) {
  int r = GR_COLOR_RED(color);
  int g = GR_COLOR_GREEN(color);
  int b = GR_COLOR_BLUE(color);

  int width = x2 - x1;
  int height = y2 - y1;

  x1 += gpu_state.clip_x1;
  y1 += gpu_state.clip_y1;

  dglEnable(GL_SCISSOR_TEST);
  dglScissor(x1, gpu_state.screen_height - (height + y1), width, height);
  dglClearColor((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, 0);
  dglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  width = gpu_state.clip_x2 - gpu_state.clip_x1;
  height = gpu_state.clip_y2 - gpu_state.clip_y1;

  dglScissor(gpu_state.clip_x1, gpu_state.screen_height - (gpu_state.clip_y1 + height), width, height);
  dglDisable(GL_SCISSOR_TEST);
}

// Sets a pixel on the display
void rend_SetPixel(ddgr_color color, int x, int y) {
  int r = (color >> 16 & 0xFF);
  int g = (color >> 8 & 0xFF);
  int b = (color & 0xFF);

  g3_RefreshTransforms(true);

  dglColor3ub(r, g, b);

  dglBegin(GL_POINTS);
  dglVertex2i(x, y);
  dglEnd();
}

// Sets a pixel on the display
ddgr_color rend_GetPixel(int x, int y) {
  ddgr_color color[4];
  dglReadPixels(x, (gpu_state.screen_height - 1) - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)color);
  return color[0];
}

// Draws a line
void rend_DrawLine(int x1, int y1, int x2, int y2) {
  int8_t atype;
  light_state ltype;
  texture_type ttype;
  int color = gpu_state.cur_color;

  g3_RefreshTransforms(true);

  int r = GR_COLOR_RED(color);
  int g = GR_COLOR_GREEN(color);
  int b = GR_COLOR_BLUE(color);

  atype = gpu_state.cur_alpha_type;
  ltype = gpu_state.cur_light_state;
  ttype = gpu_state.cur_texture_type;

  rend_SetAlphaType(AT_ALWAYS);
  rend_SetLighting(LS_NONE);
  rend_SetTextureType(TT_FLAT);

  // TODO: Generalize
  dglBegin(GL_LINES);
  dglColor4ub(r, g, b, 255);
  dglVertex2i(x1 + gpu_state.clip_x1, y1 + gpu_state.clip_y1);
  dglColor4ub(r, g, b, 255);
  dglVertex2i(x2 + gpu_state.clip_x1, y2 + gpu_state.clip_y1);
  dglEnd();

  rend_SetAlphaType(atype);
  rend_SetLighting(ltype);
  rend_SetTextureType(ttype);
}

// Sets the color of fog
void rend_SetFogColor(ddgr_color color) {
  if (color == gpu_state.cur_fog_color)
    return;

  float fc[4];
  fc[0] = GR_COLOR_RED(color);
  fc[1] = GR_COLOR_GREEN(color);
  fc[2] = GR_COLOR_BLUE(color);
  fc[3] = 1;

  fc[0] /= 255.0f;
  fc[1] /= 255.0f;
  fc[2] /= 255.0f;

  dglFogfv(GL_FOG_COLOR, fc);
}

// Sets the lighting state of opengl
void rend_SetLightingState(light_state state) {
  if (state == gpu_state.cur_light_state)
    return; // No redundant state setting

  if (UseMultitexture && Last_texel_unit_set != 0) {
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
    oglActiveTextureARB(GL_TEXTURE0_ARB + 0);
    Last_texel_unit_set = 0;
#endif
  }

  OpenGL_sets_this_frame[4]++;

  switch (state) {
  case LS_NONE:
    dglShadeModel(GL_SMOOTH);
    gpu_state.cur_light_state = LS_NONE;
    break;
  case LS_FLAT_GOURAUD:
    dglShadeModel(GL_SMOOTH);
    gpu_state.cur_light_state = LS_FLAT_GOURAUD;
    break;
  case LS_GOURAUD:
  case LS_PHONG:
    dglShadeModel(GL_SMOOTH);
    gpu_state.cur_light_state = LS_GOURAUD;
    break;
  default:
    Int3();
    break;
  }

  CHECK_ERROR(13)
}

void rend_SetAlphaType(int8_t atype) {
  if (atype == gpu_state.cur_alpha_type)
    return; // don't set it redundantly
#if (defined(_USE_OGL_ACTIVE_TEXTURES))
  if (UseMultitexture && Last_texel_unit_set != 0) {
    oglActiveTextureARB(GL_TEXTURE0_ARB + 0);
    Last_texel_unit_set = 0;
  }
#endif
  OpenGL_sets_this_frame[6]++;

  if (atype == AT_ALWAYS) {
    if (opengl_Blending_on) {
      dglDisable(GL_BLEND);
      opengl_Blending_on = false;
    }
  } else {
    if (!opengl_Blending_on) {
      dglEnable(GL_BLEND);
      opengl_Blending_on = true;
    }
  }

  switch (atype) {
  case AT_ALWAYS:
  case AT_TEXTURE:
    rend_SetAlphaValue(255);
    dglBlendFunc(GL_ONE, GL_ZERO);
    break;
  case AT_CONSTANT:
  case AT_CONSTANT_TEXTURE:
  case AT_VERTEX:
  case AT_CONSTANT_TEXTURE_VERTEX:
  case AT_CONSTANT_VERTEX:
  case AT_TEXTURE_VERTEX:
    dglBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    break;
  case AT_LIGHTMAP_BLEND:
    dglBlendFunc(GL_DST_COLOR, GL_ZERO);
    break;
  case AT_SATURATE_TEXTURE:
  case AT_LIGHTMAP_BLEND_SATURATE:
  case AT_SATURATE_VERTEX:
  case AT_SATURATE_CONSTANT_VERTEX:
  case AT_SATURATE_TEXTURE_VERTEX:
    dglBlendFunc(GL_SRC_ALPHA, GL_ONE);
    break;
  case AT_SPECULAR:
    break;
  default:
    Int3(); // no type defined,get jason
    break;
  }
  gpu_state.cur_alpha_type = atype;
  gpu_Alpha_multiplier = rend_GetAlphaMultiplier();
  CHECK_ERROR(15)
}

// Draws a line using the states of the renderer
void rend_DrawSpecialLine(g3Point *p0, g3Point *p1) {
  g3_RefreshTransforms(true);

  int x_add = gpu_state.clip_x1;
  int y_add = gpu_state.clip_y1;
  float fr, fg, fb, alpha;
  int i;

  fr = GR_COLOR_RED(gpu_state.cur_color);
  fg = GR_COLOR_GREEN(gpu_state.cur_color);
  fb = GR_COLOR_BLUE(gpu_state.cur_color);

  fr /= 255.0f;
  fg /= 255.0f;
  fb /= 255.0f;

  alpha = gpu_Alpha_multiplier * gpu_Alpha_factor;

  // And draw!
  dglBegin(GL_LINES);
  for (i = 0; i < 2; i++) {
    g3Point *pnt = p0;

    if (i == 1)
      pnt = p1;

    if (gpu_state.cur_alpha_type & ATF_VERTEX)
      alpha = pnt->p3_a * gpu_Alpha_multiplier * gpu_Alpha_factor;

    // If we have a lighting model, apply the correct lighting!
    if (gpu_state.cur_light_state != LS_NONE) {
      if (gpu_state.cur_light_state == LS_FLAT_GOURAUD) {
        dglColor4f(fr, fg, fb, alpha);
      } else {
        // Do lighting based on intesity (MONO) or colored (RGB)
        if (gpu_state.cur_color_model == CM_MONO)
          dglColor4f(pnt->p3_l, pnt->p3_l, pnt->p3_l, alpha);
        else {
          dglColor4f(pnt->p3_r, pnt->p3_g, pnt->p3_b, alpha);
        }
      }
    } else {
      dglColor4f(fr, fg, fb, alpha);
    }

    // Finally, specify a vertex
    float z = std::clamp(1.0 - (1.0 / (pnt->p3_z + Z_bias)), 0.0, 1.0);
    dglVertex3f(pnt->p3_sx + x_add, pnt->p3_sy + y_add, -z);
  }

  dglEnd();
}

// Takes a screenshot of the current frame and puts it into the handle passed
std::unique_ptr<NewBitmap> rend_Screenshot() {
  uint16_t *dest_data;
  uint32_t *temp_data;

  int total = gpu_state.screen_width * gpu_state.screen_height;
  auto result = std::make_unique<NewBitmap>(gpu_state.screen_width, gpu_state.screen_height, PixelDataFormat::RGBA32, true);

  if (!result || result->getData() == nullptr) {
    return nullptr;
  }

  dglReadPixels(0, 0, gpu_state.screen_width, gpu_state.screen_height, GL_RGBA, GL_UNSIGNED_BYTE,
                (GLvoid *)result->getData());

  return result;
}

// Takes a screenshot of the current frame and puts it into the handle passed
void rend_Screenshot(int bm_handle) {
  auto screenshot = rend_Screenshot();
  auto *temp_data = reinterpret_cast<uint32_t*>(screenshot->getData());

  uint32_t w, h;
  screenshot->getSize(w, h);

  ASSERT((bm_w(bm_handle, 0)) == gpu_state.screen_width);
  ASSERT((bm_h(bm_handle, 0)) == gpu_state.screen_height);

  uint16_t* dest_data = bm_data(bm_handle, 0);

  for (int i = 0; i < h; i++) {
    for (int t = 0; t < w; t++) {
      uint32_t spix = temp_data[i * w + t];

      int r = spix & 0xff;
      int g = (spix >> 8) & 0xff;
      int b = (spix >> 16) & 0xff;

      dest_data[(((h - 1) - i) * w) + t] = GR_RGB16(r, g, b);
    }
  }
}

// Enables/disables writes the depth buffer
void rend_SetZBufferWriteMask(int state) {
  OpenGL_sets_this_frame[5]++;
  if (state) {
    dglDepthMask(GL_TRUE);
  } else {
    dglDepthMask(GL_FALSE);
  }
}

int rend_ReInit() {
  opengl_Close(true);
  return opengl_Init(NULL, &gpu_preferred_state);
}

// Takes a bitmap and blits it to the screen using linear frame buffer stuff
// X and Y are the destination X,Y
void rend_CopyBitmapToFramebuffer(int bm_handle, int x, int y) {
  ASSERT(opengl_Framebuffer_ready);

  if (opengl_Framebuffer_ready == 1) {
    bm_CreateChunkedBitmap(bm_handle, &opengl_Chunked_bitmap);
    opengl_Framebuffer_ready = 2;
  } else {
    opengl_ChangeChunkedBitmap(bm_handle, &opengl_Chunked_bitmap);
  }

  rend_DrawChunkedBitmap(&opengl_Chunked_bitmap, 0, 0, 255);
}

// Gets a renderer ready for a framebuffer copy, or stops a framebuffer copy
void rend_SetFrameBufferCopyState(bool state) {
  if (state) {
    ASSERT(opengl_Framebuffer_ready == 0);
    opengl_Framebuffer_ready = 1;
  } else {
    ASSERT(opengl_Framebuffer_ready != 0);
    opengl_Framebuffer_ready = 0;

    if (opengl_Framebuffer_ready == 2) {
      bm_DestroyChunkedBitmap(&opengl_Chunked_bitmap);
      opengl_ResetCache();
    }
  }
}

// Gets OpenGL ready to work in a window
int rend_InitOpenGLWindow(oeApplication *app, renderer_preferred_state *pref_state) {
  WindowGL = 1;
  return opengl_Init(app, pref_state);
}

// Shuts down OpenGL in a window
void rend_CloseOpenGLWindow(void) {
  opengl_Close();
  WindowGL = 0;
  OpenGL_window_initted = 0;
  mprintf(1, "SHUTTING DOWN WINDOWED OPENGL!");
}

// Sets the hardware bias level for coplanar polygons
// This helps reduce z buffer artifacts
void rend_SetCoplanarPolygonOffset(float factor) {
  if (factor == 0.0f) {
    dglDisable(GL_POLYGON_OFFSET_FILL);
  } else {
    dglEnable(GL_POLYGON_OFFSET_FILL);
    dglPolygonOffset(-1.0f, -1.0f);
  }
}

// returns the direct draw object
void *rend_RetrieveDirectDrawObj(void **frontsurf, void **backsurf) {
  *frontsurf = NULL;
  *backsurf = NULL;
  return NULL;
}

void rend_TransformSetToPassthru(void) {
  int width = gpu_state.screen_width;
  int height = gpu_state.screen_height;

  // TODO: Generalize
  // Projection
  dglMatrixMode(GL_PROJECTION);
  dglLoadIdentity();
  dglOrtho((GLfloat)0.0f, (GLfloat)(width), (GLfloat)(height), (GLfloat)0.0f, 0.0f, 1.0f);

  // Viewport
  dglViewport(0, 0, width, height);
  dglScissor(0, 0, width, height);

  // ModelView
  dglMatrixMode(GL_MODELVIEW);
  dglLoadIdentity();
}

void rend_TransformSetViewport(int lx, int ty, int width, int height) {
  dglViewport(lx, gpu_state.screen_height - (ty + height - 1), width, height);
}

void rend_TransformSetProjection(float trans[4][4]) {
  dglMatrixMode(GL_PROJECTION);
  dglLoadMatrixf(&trans[0][0]);
}

void rend_TransformSetModelView(float trans[4][4]) {
  dglMatrixMode(GL_MODELVIEW);
  dglLoadMatrixf(&trans[0][0]);
}
