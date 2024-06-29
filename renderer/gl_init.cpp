/*
* Descent 3: Piccu Engine
* Copyright (C) 2024 Parallax Software
* Copyright (C) 2024 SaladBadger
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
#include "gl_local.h"
#include "args.h"
#include "config.h"

#define DECLARE_OPENGL
#include "dyna_gl.h"

#ifdef WIN32
#define NOMINMAX
#include <Windows.h>
#endif

renderer_preferred_state OpenGL_preferred_state = { 0,1,1.0 };
rendering_state OpenGL_state;

bool OpenGL_debugging_enabled;

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

#if defined(WIN32)
PFNWGLSWAPINTERVALEXTPROC dwglSwapIntervalEXT;
PFNWGLCREATECONTEXTATTRIBSARBPROC dwglCreateContextAttribsARB;

//	Moved from DDGR library
HWND hOpenGLWnd = NULL;
HDC hOpenGLDC = NULL;
HGLRC ResourceContext;
#elif defined(__LINUX__)
SDL_Window *GSDLWindow = NULL;
SDL_GLContext GSDLGLContext = NULL;
char loadedLibrary[_MAX_PATH];
#endif

bool Already_loaded = false;

// Sets default states for our renderer
void opengl_SetDefaults()
{
	mprintf((0, "Setting states\n"));

	OpenGL_state.cur_color = 0x00FFFFFF;
	OpenGL_state.cur_bilinear_state = -1;
	OpenGL_state.cur_zbuffer_state = -1;
	OpenGL_state.cur_texture_quality = -1;
	OpenGL_state.cur_light_state = LS_GOURAUD;
	OpenGL_state.cur_color_model = CM_MONO;
	OpenGL_state.cur_mip_state = -1;
	OpenGL_state.cur_alpha_type = AT_TEXTURE;

	// Enable some states
	//glAlphaFunc(GL_GREATER, 0);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	//glEnable(GL_DITHER);
	OpenGL_blending_on = true;

#ifndef RELEASE
	if (Fast_test_render)
	{
		//glDisable(GL_DITHER);
	}
#endif

	rend_SetAlphaType(AT_ALWAYS);
	rend_SetAlphaValue(255);
	rend_SetFiltering(1);
	rend_SetLightingState(LS_NONE);
	rend_SetTextureType(TT_FLAT);
	rend_SetColorModel(CM_RGB);
	rend_SetZBufferState(1);
	rend_SetZValues(0, 3000);
	OpenGL_last_bound[0] = 9999999;
	OpenGL_last_bound[1] = 9999999;
	Last_texel_unit_set = -1;
	OpenGL_multitexture_state = false;

	opengl_SetDrawDefaults();

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glHint(GL_FOG_HINT, GL_NICEST);
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, OpenGL_state.screen_width, OpenGL_state.screen_height);
	glDisable(GL_SCISSOR_TEST);
	//glDepthRange(0.0f, 1.0f);

	if (UseMultitexture)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		//glClientActiveTextureARB(GL_TEXTURE0 + 1);
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		//glHint(GL_FOG_HINT, GL_NICEST);

		//glClientActiveTextureARB(GL_TEXTURE0 + 0);

		//glDisable(GL_TEXTURE_2D);
		//glAlphaFunc(GL_GREATER, 0);
		//glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		//glEnable(GL_DITHER);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glActiveTexture(GL_TEXTURE0 + 0);
	}
}

#if defined(WIN32)
static HMODULE glDllhandle = nullptr;
static GLADapiproc opengl_GLADLoad(const char* name)
{
	if (!glDllhandle)
	{
		glDllhandle = LoadLibrary("opengl32.dll");
		if (!glDllhandle)
			Error("opengl_GLADLoad: failed to load opengl32.dll!");
	}
	void* ptr = wglGetProcAddress(name);
	//I love OpenGL btw
	if (!ptr)
	{
		ptr = GetProcAddress(glDllhandle, name);
	}
	return (GLADapiproc)ptr;
}

//Hack to allow loading wgl extensions.
//Credit to GZDoom for this bit of code
HWND InitDummy()
{
	HMODULE g_hInst = GetModuleHandle(NULL);
	HWND dummy;
	//Create a rect structure for the size/position of the window
	RECT windowRect;
	windowRect.left = 0;
	windowRect.right = 64;
	windowRect.top = 0;
	windowRect.bottom = 64;

	//Window class structure
	WNDCLASS wc;

	//Fill in window class struct
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("PiccuOpenGLDummyWindow");

	//Register window class
	if (!RegisterClass(&wc))
	{
		return 0;
	}

	//Set window style & extended style
	DWORD style, exStyle;
	exStyle = WS_EX_CLIENTEDGE;
	style = WS_SYSMENU | WS_BORDER | WS_CAPTION;// | WS_VISIBLE;

	//Adjust the window size so that client area is the size requested
	AdjustWindowRectEx(&windowRect, style, false, exStyle);

	//Create Window
	if (!(dummy = CreateWindowEx(exStyle,
		TEXT("PiccuOpenGLDummyWindow"),
		TEXT("PiccuEngine"),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style,
		0, 0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL, NULL,
		g_hInst,
		NULL)))
	{
		UnregisterClassW(L"PiccuOpenGLDummyWindow", g_hInst);
		return 0;
	}
	ShowWindow(dummy, SW_HIDE);

	return dummy;
}

void ShutdownDummy(HWND dummy)
{
	DestroyWindow(dummy);
	UnregisterClass(TEXT("PiccuOpenGLDummyWindow"), GetModuleHandle(NULL));
}

bool GL_GetWGLExtensionProcs()
{
	HWND DummyHWND = InitDummy();
	HDC DummyDC = GetDC(DummyHWND);

	// Finds an acceptable pixel format to render to
	PIXELFORMATDESCRIPTOR pfd, pfd_copy;
	int pf;
	bool ret = false;

	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
	pfd.iPixelType = PFD_TYPE_RGBA;

	// Find the user's "best match" PFD 
	pf = ChoosePixelFormat(DummyDC, &pfd);
	if (pf == 0)
	{
		Int3();
		//FreeLibrary(opengl_dll_handle);
		goto die;
	}

	mprintf((0, "Choose pixel format successful!\n"));

	// Try and set the new PFD
	if (SetPixelFormat(DummyDC, pf, &pfd) == FALSE)
	{
		DWORD ret = GetLastError();
		Int3();
		//FreeLibrary(opengl_dll_handle);
		goto die;
	}

	mprintf((0, "SetPixelFormat successful!\n"));

	// Get a copy of the newly set PFD
	if (DescribePixelFormat(DummyDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd_copy) == 0)
	{
		Int3();
		//FreeLibrary(opengl_dll_handle);
		goto die;
	}

	// Check the returned PFD to see if it is hardware accelerated
	if ((pfd_copy.dwFlags & PFD_GENERIC_ACCELERATED) == 0 && (pfd_copy.dwFlags & PFD_GENERIC_FORMAT) != 0)
	{
		Int3();
		//FreeLibrary(opengl_dll_handle);
		goto die;
	}

	// Create an OpenGL context, and make it the current context
	HGLRC DummyResourceContext = wglCreateContext(DummyDC);
	if (DummyResourceContext == nullptr)
	{
		DWORD ret = GetLastError();
		//FreeLibrary(opengl_dll_handle);
		Int3();
		goto die;
	}

	ASSERT(DummyResourceContext != nullptr);
	mprintf((0, "Making context current\n"));
	if (!wglMakeCurrent(DummyDC, DummyResourceContext))
	{
		Int3();
		goto die;
	}

	dwglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)opengl_GLADLoad("wglCreateContextAttribsARB");
	if (!dwglCreateContextAttribsARB)
	{
		Int3();
		goto die;
	}

	ret = true;

die:
	if (DummyResourceContext)
	{
		//OpenGL on Windows is lovely.
		//Delete this context so I can make a new one with wglCreateContextAttribsARB
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(DummyResourceContext);
		ReleaseDC(DummyHWND, DummyDC);
	}

	if (DummyHWND)
		ShutdownDummy(DummyHWND);

	return ret;
}

// Check for OpenGL support, 
int opengl_Setup(HDC glhdc)
{
	if (!GL_GetWGLExtensionProcs())
	{
		mprintf((0, "Dummy GL context failed!\n"));
		return 0;
	}

	// Finds an acceptable pixel format to render to
	PIXELFORMATDESCRIPTOR pfd, pfd_copy;
	int pf;

	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
	pfd.iPixelType = PFD_TYPE_RGBA;

	// Find the user's "best match" PFD 
	pf = ChoosePixelFormat(glhdc, &pfd);
	if (pf == 0)
	{
		Int3();
		//FreeLibrary(opengl_dll_handle);
		return NULL;
	}

	mprintf((0, "Choose pixel format successful!\n"));

	// Try and set the new PFD
	if (SetPixelFormat(glhdc, pf, &pfd) == FALSE)
	{
		DWORD ret = GetLastError();
		Int3();
		//FreeLibrary(opengl_dll_handle);
		return NULL;
	}

	mprintf((0, "SetPixelFormat successful!\n"));

	// Get a copy of the newly set PFD
	if (DescribePixelFormat(glhdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd_copy) == 0)
	{
		Int3();
		//FreeLibrary(opengl_dll_handle);
		return NULL;
	}

	// Check the returned PFD to see if it is hardware accelerated
	if ((pfd_copy.dwFlags & PFD_GENERIC_ACCELERATED) == 0 && (pfd_copy.dwFlags & PFD_GENERIC_FORMAT) != 0)
	{
		Int3();
		//FreeLibrary(opengl_dll_handle);
		return NULL;
	}

	GLint attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#if defined(GL_DEBUG) && !defined(NDEBUG)
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		#endif
		0
	};

	// Create an OpenGL context, and make it the current context
	//ResourceContext = wglCreateContext((HDC)glhdc);
	ResourceContext = dwglCreateContextAttribsARB((HDC)glhdc, nullptr, attribs);
	if (ResourceContext == NULL) 
	{
		DWORD ret = GetLastError();
		//FreeLibrary(opengl_dll_handle);
		Int3();
		return NULL;
	}

	ASSERT(ResourceContext != NULL);
	mprintf((0, "Making context current\n"));
	if (!wglMakeCurrent((HDC)glhdc, ResourceContext))
		Int3();

	dwglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)opengl_GLADLoad("wglCreateContextAttribsARB");
	if (!dwglCreateContextAttribsARB)
	{
		Error("Cannot load wglCreateContextAttribsARB!");
		return 0;
	}

	if (!Already_loaded)
	{
		if (!gladLoadGL(opengl_GLADLoad))
		{
			rend_SetErrorMessage("Failed to load opengl dll!\n");
			Int3();
			return 0;
		}
	}

	dwglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)opengl_GLADLoad("wglSwapIntervalEXT");

	Already_loaded = true;

	return 1;

}
#elif defined(__LINUX__)

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

    OpenGLDLLHandle = LoadOpenGLDLL(gl_library);
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
#endif

// Gets some specific information about this particular flavor of opengl
void opengl_GetInformation()
{
	mprintf((0, "OpenGL Vendor: %s\n", glGetString(GL_VENDOR)));
	mprintf((0, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER)));
	mprintf((0, "OpenGL Version: %s\n", glGetString(GL_VERSION)));
}

void GLAD_API_PTR GL_LogDebugMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* user)
{
	mprintf((0, "OpenGL debug msg %d: %s\n", id, msg));
}

// Sets up our OpenGL rendering context
// Returns 1 if ok, 0 if something bad
int opengl_Init(oeApplication* app, renderer_preferred_state* pref_state)
{
	//int width,height;
	int retval = 1;
	int i;

	mprintf((0, "Setting up opengl mode!\n"));

	if (pref_state)
	{
		OpenGL_preferred_state = *pref_state;
	}

	if (app != NULL)
	{
		ParentApplication = app;
	}

	int windowX = 0, windowY = 0;
#if defined(WIN32)
	/***********************************************************
	*               WINDOWS OPENGL
	***********************************************************
	*/
	static HWnd hwnd = NULL;
	if (ParentApplication != NULL)
	{
		hwnd = static_cast<HWnd>(reinterpret_cast<oeWin32Application*>(ParentApplication)->m_hWnd);
	}

	memset(&OpenGL_state, 0, sizeof(rendering_state));

	//	These values are set here - samir
	if (app != NULL)
	{
		hOpenGLWnd = (HWND)((oeWin32Application*)app)->m_hWnd;
	}

	hOpenGLDC = GetDC(hOpenGLWnd);

	opengl_InitImages();
	opengl_UpdateWindow();

	if (!opengl_Setup(hOpenGLDC))
	{
		opengl_Close();
		return 0;
	}

#if defined(GL_DEBUG) && !defined(NDEBUG)
	OpenGL_debugging_enabled = opengl_CheckExtension("GL_KHR_debug");
	if (OpenGL_debugging_enabled)
	{
		glDebugMessageCallback(GL_LogDebugMsg, nullptr);
	}
#else
	OpenGL_debugging_enabled = false;
#endif

#elif defined(__LINUX__)
	/***********************************************************
	*               LINUX OPENGL
	***********************************************************
	*/
	// Setup OpenGL_state.screen_width & OpenGL_state.screen_height & width & height
	auto width = OpenGL_preferred_state.width;
	auto height = OpenGL_preferred_state.height;

	if (!opengl_Setup(app, &width, &height))
	{
		opengl_Close();
		return 0;
	}

	memset(&OpenGL_state, 0, sizeof(rendering_state));
	OpenGL_state.screen_width = width;
	OpenGL_state.screen_height = height;
#else
	// Setup OpenGL_state.screen_width & OpenGL_state.screen_height & width & height

#endif
	// Get some info
	opengl_GetInformation();

	//Initialize the common buffer that will be shared across shaders. 
	opengl_InitCommonBuffer();

	// Update framebuffer
	opengl_UpdateFramebuffer();

	mprintf((0, "Setting up multitexture...\n"));

	//In this shader world, multitexture is always supported.
	UseMultitexture = true;
	//TODO: Need to use standard statement
	OpenGL_packed_pixels = false;

	opengl_InitCache();

	if (UseMultitexture)
		mprintf((0, "Using multitexture."));
	else
		mprintf((0, "Not using multitexture."));

	opengl_SetUploadBufferSize(256, 256);
	opengl_SetDefaults();

	// Default passthrough viewport. 
	opengl_SetViewport();

	//g3_ForceTransformRefresh();

	CHECK_ERROR(4);

	OpenGL_state.initted = 1;

	mprintf((0, "OpenGL initialization at %d x %d was successful.\n", OpenGL_state.screen_width, OpenGL_state.screen_height));

#ifdef WIN32
	if (dwglSwapIntervalEXT)
	{
		if (pref_state->vsync_on)
			dwglSwapIntervalEXT(1);
		else
			dwglSwapIntervalEXT(0);
	}
#endif

	return retval;
}

// Releases the rendering context
void opengl_Close()
{
	CHECK_ERROR(5);

	opengl_FreeImages();
	opengl_CloseFramebuffer();

#if defined(WIN32)
	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(ResourceContext);

#elif defined(__LINUX__)
	// SDL_Quit() handles this for us.
#else

#endif

	opengl_FreeUploadBuffers();

	opengl_FreeCache();

#if defined(WIN32)
	//	I'm freeing the DC here - samir
	ReleaseDC(hOpenGLWnd, hOpenGLDC);
#endif

	//mod_FreeModule (OpenGLDLLHandle);
	OpenGL_state.initted = 0;
}
