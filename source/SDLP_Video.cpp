/*
  SDL+: Object-Oriented SDL
  Copyright (C) 2022 Ghost Coder <ghostcoder22@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDLP_Video.cpp
 *
 *  SDL+ Video Subsystem C++ source
 */

#include <SDL_plus/SDLP_Video.hpp>
#include <SDL_plus/SDLP_SystemInfo.hpp>
#include "SDLP_internals.hpp"

CSDL_Video::CSDL_Video() {}
CSDL_Video::~CSDL_Video() {}
CSDL_Video* CSDL_Video::Interface() { return this; }

int CSDL_Video::WalkDisplayModes(SDLP_DisplayModeWalker_t walker)
{
  if (walker == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Missing parameter.");
    return -1;
  }

  int displays = SDL_GetNumVideoDisplays();
  for (int displayIndex = 0; displayIndex < displays; displayIndex++)
  {
    int displayModes = SDL_GetNumDisplayModes(displayIndex);
    if (displayModes < 1)
      return displayModes;

    for (int i = 0; i < displayModes; i++)
    {
      SDL_DisplayMode displayMode;
      if (SDL_GetDisplayMode(displayIndex, i, &displayMode) == 0)
      {
        int result = (walker)(i, &displayMode, SDL_GetDisplayName(i));
        if (result < 0)
          return -1;
      }
    }
  }
  return 0;
}


int CSDL_Video::WalkVideoDrivers(SDLP_VideoDriverWalker_t walker)
{
  if (walker == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Missing parameter.");
    return -1;
  }

  int drivers = SDL_GetNumVideoDrivers();
  for (int i = 0; i < drivers; i++)
  {
    int result = (walker)(i, SDL_GetVideoDriver(i));
    if (result < 0)
      return -1;
  }
  return 0;
}

const char* CSDL_Video::GetCurrentVideoDriver()
{
  return SDL_GetCurrentVideoDriver();
}

const char* CSDL_Video::GetVideoDriver(int index)
{
  return SDL_GetVideoDriver(index);
}

int CSDL_Video::GetNumVideoDrivers()
{
  return SDL_GetNumVideoDrivers();
}


const char* CSDL_Video::GetDisplayName(int displayIndex)
{
  return SDL_GetDisplayName(displayIndex);
}

int CSDL_Video::GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode *mode)
{
  return SDL_GetCurrentDisplayMode(displayIndex, mode);
}

int CSDL_Video::GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode *mode)
{
  return SDL_GetDesktopDisplayMode(displayIndex, mode);
}

int CSDL_Video::GetDisplayBounds(int displayIndex, SDL_Rect *rect)
{
  return SDL_GetDisplayBounds(displayIndex, rect);
}

int CSDL_Video::GetDisplayUsableBounds(int displayIndex, SDL_Rect *rect)
{
  return SDL_GetDisplayUsableBounds(displayIndex, rect);
}

int CSDL_Video::WalkAllDisplayBounds(SDLP_WalkAllDisplayBounds_t procedure)
{
  if (procedure == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Missing parameter.");
    return -1;
  }

  int displays = SDL_GetNumVideoDisplays();
  for (int displayIndex = 0; displayIndex < displays; displayIndex++)
  {
    SDL_Rect boundingRect;
    int result = SDL_GetDisplayBounds(displayIndex, &boundingRect);
    if (result != 0)
      return result;
    result = (procedure)(displayIndex, &boundingRect);
    if (result < 0)
      return result;
  }
  return 0;
}

int CSDL_Video::GetNumVideoDisplays()
{
  return SDL_GetNumVideoDisplays();
}

int CSDL_Video::GetNumDisplayModes(int displayIndex)
{
  return SDL_GetNumDisplayModes(displayIndex);
}

int CSDL_Video::GetDisplayMode(int displayIndex, int modeIndex, SDL_DisplayMode *mode)
{
  return SDL_GetDisplayMode(displayIndex, modeIndex, mode);
}

SDL_DisplayMode* CSDL_Video::GetClosestDisplayMode
 (int displayIndex, const SDL_DisplayMode * mode, SDL_DisplayMode * closest)
{
  return SDL_GetClosestDisplayMode(displayIndex, mode, closest);
}

int CSDL_Video::GetDisplayDPI(int displayIndex, float * ddpi, float * hdpi, float * vdpi)
{
  return SDL_GetDisplayDPI(displayIndex, ddpi, hdpi, vdpi);
}





TList2W<CSDL_Window*> SDLP_WindowTable;
TNode2W<CSDL_Window*>** SDLP_WindowTablePtr()
{
  TNode2W<CSDL_Window*>** windowTable = SDLP_WindowTable.Head();
  return &(*windowTable);
}

TNodeID  SDLP_WindowRef = 0;
void CSDL_Window_AddRef() { SDLP_WindowRef++; }
void CSDL_Window_ReleaseRef() { SDLP_WindowRef--; }
TNodeID CSDL_Window_Ref() { return SDLP_WindowRef; }

CSDL_Window::CSDL_Window()
{
  m_SDL_Window = nullptr;
 #if SDL_VERSION_ATLEAST(2,0,5)
  m_CSDL_Window_model = nullptr;
 #endif
  m_SDLP_Icon   = nullptr;
  m_fFullscreen = 0;
}

CSDL_Window::~CSDL_Window()
{
  m_SDL_Window = nullptr;
 #if SDL_VERSION_ATLEAST(2,0,5)
  m_CSDL_Window_model = nullptr;
 #endif
  m_SDLP_Icon   = nullptr;
  m_fFullscreen = 0;
}

CSDL_Window* CSDL_Window::Interface()
{
  return this;
}


SDL_Window* CSDL_Window::Create(const char* title, int x, int y, int w, int h, Uint32 flags)
{
  if (m_SDL_Window == nullptr)
  {
    m_SDL_Window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (m_SDL_Window != nullptr)
    {
      CSDL_Surface::GetFromWindow(this);
      SDLP_WindowTable.Add(this); CSDL_Window_AddRef();
    }
  }
  return m_SDL_Window;
}

SDL_Window* CSDL_Window::CreateWithRenderer(const char* title, int width, int height, Uint32 window_flags, CSDL_Renderer* renderer)
{
  if (m_SDL_Window != nullptr)
    SDL_SetError("CSDL_Surface::CreateWithRenderer: Window surface already exists.");
  else
    if (renderer == nullptr)
      SDL_SetError("CSDL_Surface::CreateWithRenderer: Invalid parameter! Renderer not specified.");
    else
    {
      m_SDL_Window = Create(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
      SDL_Renderer* Renderer = renderer->Create(this, -1, 0);
      if (!Renderer)
        SDL_SetError("CSDL_Surface::CreateWithRenderer: Window created successfully\nbut renderer creation failed.");
    }
  return m_SDL_Window;
}

SDL_Window* CSDL_Window::CreateFrom(const void *data)
{
  if ((m_SDL_Window == nullptr) && (data != nullptr))
  {
    m_SDL_Window = SDL_CreateWindowFrom(data);
    if (m_SDL_Window != nullptr)
    {
      CSDL_Surface::GetFromWindow(this);
      SDLP_WindowTable.Add(this); CSDL_Window_AddRef();
    }
  }
  return m_SDL_Window;
}

void CSDL_Window::Destroy()
{
  if (m_SDL_Window != nullptr)
  {
    SDL_DestroyWindow(m_SDL_Window);
    CSDL_Window_ReleaseRef();
  }
}

SDL_Window* CSDL_Window::Handle()
{
  return m_SDL_Window;
}


bool CSDL_Window::IsVisible_OpenGL()
{
  if (SDL_GetWindowFlags(m_SDL_Window) & SDL_WINDOW_OPENGL)
    return true;
  return false;
}

bool CSDL_Window::IsVisible_Vulkan()
{
  if (SDL_GetWindowFlags(m_SDL_Window) & SDL_WINDOW_VULKAN)
    return true;
  return false;
}



CSDL_Surface* CSDL_Window::GetSurface()
{
  return CSDL_Surface::Interface();
}

int CSDL_Window::UpdateSurface()
{
  return SDL_UpdateWindowSurface(m_SDL_Window);
}

int CSDL_Window::UpdateSurfaceRects(const SDL_Rect *rects, int numrects)
{
  return SDL_UpdateWindowSurfaceRects(m_SDL_Window, rects, numrects);
}


void CSDL_Window::SetTitle(const char* title)
{
  SDL_SetWindowTitle(m_SDL_Window, title);
}

const char* CSDL_Window::GetTitle()
{
  return SDL_GetWindowTitle(m_SDL_Window);
}

void CSDL_Window::SetIcon(CSDL_Surface* surface)
{
  if (m_SDL_Window != nullptr)
  {
    if (surface == nullptr)
      SDL_Log("Invalid parameter");
    else
      if (surface->Handle() != nullptr)
      {
        SDL_SetWindowIcon(m_SDL_Window, surface->Handle());
        m_SDLP_Icon = surface;
      }
  }
}

CSDL_Surface* CSDL_Window::GetIcon()
{
  return m_SDLP_Icon;
}


bool CSDL_Window::SetGrab(bool grabbed)
{
  if (m_SDL_Window != nullptr)
    return false;
  SDL_SetWindowGrab(m_SDL_Window, (grabbed == true ? SDL_TRUE : SDL_FALSE));
  return true;
}

bool CSDL_Window::GetGrab()
{
  if (m_SDL_Window != nullptr)
    return false;
  return (SDL_GetWindowGrab(m_SDL_Window) == SDL_TRUE ? true : false);
}

bool CSDL_Window::IsGrabbed()
{
  if (m_SDL_Window != nullptr)
    return false;
  return (SDL_GetGrabbedWindow() == m_SDL_Window ? true : false);
}

int CSDL_Window::SetInputFocus()
{
  int result = SDL_SetWindowInputFocus(m_SDL_Window);
  if (result == 0)
    m_hasInputFocus = true;
  return result;
}

bool CSDL_Window::HasInputFocus()
{
  if (SDL_GetWindowFlags(m_SDL_Window) & SDL_WINDOW_INPUT_FOCUS)
    return true;
  return false;
}


int CSDL_Window::SetDisplayMode(const SDL_DisplayMode *mode)
{
  if ((m_SDL_Window != nullptr) && (mode != nullptr))
    return SDL_SetWindowDisplayMode(m_SDL_Window, mode);
  return -1;
}

int CSDL_Window::GetDisplayMode(SDL_DisplayMode *mode)
{
  if ((m_SDL_Window != nullptr) && (mode != nullptr))
    return SDL_GetWindowDisplayMode(m_SDL_Window, mode);
  return -1;
}

int CSDL_Window::SetFullscreenMode(Uint32 flags)
{
  if (m_SDL_Window != nullptr)
  {
    int result = SDL_SetWindowFullscreen(m_SDL_Window, flags);
    if (result == 0)
      m_fFullscreen = flags;
    return result;
  }
  return -1;
}

int CSDL_Window::GetFullscreenMode()
{
  return m_fFullscreen;
}

void CSDL_Window::Show()
{
  SDL_ShowWindow(m_SDL_Window);
}

bool CSDL_Window::IsShown()
{
  if (SDL_GetWindowFlags(m_SDL_Window) & SDL_WINDOW_SHOWN)
    return true;
  return false;
}

void CSDL_Window::Raise()
{
  SDL_RaiseWindow(m_SDL_Window);
}

void CSDL_Window::Hide()
{
  SDL_HideWindow(m_SDL_Window);
}

void CSDL_Window::Maximize()
{
  SDL_MaximizeWindow(m_SDL_Window);
}

void CSDL_Window::Minimize()
{
  SDL_MinimizeWindow(m_SDL_Window);
}

void CSDL_Window::Restore()
{
  SDL_RestoreWindow(m_SDL_Window);
}


void CSDL_Window::SetSize(int w, int h)
{
  SDL_SetWindowSize(m_SDL_Window, w, h);
}

void CSDL_Window::SetSize(SDL_Size* ws)
{
  if (m_SDL_Window != nullptr && ws != nullptr)
    SDL_GetWindowSize(m_SDL_Window, &ws->width, &ws->height);
}

void CSDL_Window::GetSize(int *w, int *h)
{
  SDL_GetWindowSize(m_SDL_Window, w, h);
}

void CSDL_Window::GetSize(SDL_Size* ws)
{
  if (m_SDL_Window != nullptr && ws != nullptr)
    SDL_GetWindowSize(m_SDL_Window, &ws->width, &ws->height);
}

void CSDL_Window::SetResizable(SDL_bool resizable)
{
  SDL_SetWindowResizable(m_SDL_Window, resizable);
}

SDL_bool CSDL_Window::GetResizable()
{
  if (SDL_GetWindowFlags(m_SDL_Window) & SDL_WINDOW_RESIZABLE)
    return SDL_TRUE;
  return SDL_FALSE;
}

void CSDL_Window::SetMaximumSize(int max_w, int max_h)
{
  SDL_SetWindowMaximumSize(m_SDL_Window, max_w, max_h);
}

void CSDL_Window::SetMaximumSize(SDL_Size *size)
{
  if (size == nullptr)
    SDL_SetWindowMaximumSize(m_SDL_Window, 1024, 600);
  SDL_SetWindowMaximumSize(m_SDL_Window, size->width, size->height);
}

void CSDL_Window::GetMaximumSize(int *max_w, int *max_h)
{
  SDL_GetWindowMaximumSize(m_SDL_Window, max_w, max_h);
}

void CSDL_Window::GetMaximumSize(SDL_Size *size)
{
  if (size != nullptr)
    SDL_GetWindowMaximumSize(m_SDL_Window, &size->width, &size->height);
}

void CSDL_Window::SetMinimumSize(int max_w, int max_h)
{
  SDL_SetWindowMinimumSize(m_SDL_Window, max_w, max_h);
}

void CSDL_Window::SetMinimumSize(SDL_Size *size)
{
  if (size == nullptr)
    SDL_SetWindowMinimumSize(m_SDL_Window, 800, 600);
  SDL_SetWindowMinimumSize(m_SDL_Window, size->width, size->height);
}

void CSDL_Window::GetMinimumSize(int *max_w, int *max_h)
{
  SDL_GetWindowMinimumSize(m_SDL_Window, max_w, max_h);
}

void CSDL_Window::GetMinimumSize(SDL_Size *size)
{
  if (size != nullptr)
    SDL_GetWindowMinimumSize(m_SDL_Window, &size->width, &size->height);
}

int CSDL_Window::GetBordersSize(int *top, int *left, int *bottom, int *right)
{
  return SDL_GetWindowBordersSize(m_SDL_Window, top, left, bottom, right);
}

int CSDL_Window::GetBordersSize(SDL_BordersSize* wbs)
{
  if (m_SDL_Window == nullptr || wbs == nullptr)
    return -1;
  return SDL_GetWindowBordersSize(m_SDL_Window, &wbs->top, &wbs->left, &wbs->bottom, &wbs->right);
}

bool CSDL_Window::IsBorderless()
{
  if (SDL_GetWindowFlags(m_SDL_Window) & SDL_WINDOW_BORDERLESS)
    return true;
  return false;
}

void CSDL_Window::SetPosition(int x, int y)
{
  SDL_SetWindowPosition(m_SDL_Window, x, y);
}

void CSDL_Window::SetPosition(SDL_Position *position)
{
  if (position == nullptr)
    SDL_SetWindowPosition(m_SDL_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  else
    SDL_SetWindowPosition(m_SDL_Window, position->x, position->y);
}

void CSDL_Window::GetPosition(int *x, int *y)
{
  SDL_GetWindowPosition(m_SDL_Window, x, y);
}

void CSDL_Window::GetPosition(SDL_Position *position)
{
  if (position != nullptr)
    SDL_GetWindowPosition(m_SDL_Window, &position->x, &position->y);
}


int CSDL_Window::SetGammaRamp(const Uint16 *red, const Uint16 *green, const Uint16 *blue)
{
  return SDL_SetWindowGammaRamp(m_SDL_Window, red, green, blue);
}

int CSDL_Window::SetGammaRamp(const SDL_GammaRamp *gammaramp)
{
  return (gammaramp == nullptr ? SDL_SetWindowGammaRamp(m_SDL_Window, 0, 0, 0) :
          SDL_SetWindowGammaRamp(m_SDL_Window, &gammaramp->red, &gammaramp->green, &gammaramp->blue));
}

int CSDL_Window::GetGammaRamp(Uint16 *red, Uint16 *green, Uint16 *blue)
{
  return SDL_GetWindowGammaRamp(m_SDL_Window, red, green, blue);
}

int CSDL_Window::GetGammaRamp(SDL_GammaRamp *gammaramp)
{
  if (gammaramp == nullptr)
    return -1;
  return SDL_GetWindowGammaRamp(m_SDL_Window, &gammaramp->red, &gammaramp->green, &gammaramp->blue);
}

int CSDL_Window::SetOpacity(float *opacity)
{
  return SDL_SetWindowOpacity(m_SDL_Window, *opacity);
}

int CSDL_Window::GetOpacity(float *opacity)
{
  return SDL_SetWindowOpacity(m_SDL_Window, *opacity);
}


int CSDL_Window::Flash(SDL_FlashOperation operation)
{
  return (SDL_IF_VERSION(2,0,16, "CSDL_Window::Flash") ? SDL_FlashWindow(m_SDL_Window, operation) : -1);
}

Uint32 CSDL_Window::GetPixelFormat()
{
  return SDL_GetWindowPixelFormat(m_SDL_Window);
}


Uint32 CSDL_Window::GetID()
{
  if (m_SDL_Window == nullptr)
    return -1;
  return SDL_GetWindowID(m_SDL_Window);
}

int CSDL_Window::GetDisplayIndex()
{
  if (m_SDL_Window == nullptr)
    return -1;
  return SDL_GetWindowDisplayIndex(m_SDL_Window);
}


void CSDL_Window::DisableScreenSaver() { SDL_DisableScreenSaver(); }
void CSDL_Window::EnableScreenSaver() { SDL_EnableScreenSaver(); }
bool CSDL_Window::IsScreenSaverEnabled() { return SDL_IsScreenSaverEnabled(); }

SDL_bool CSDL_Window::GetWindowWMInfo(SDL_SysWMinfo *info)
{
  return SDL_GetWindowWMInfo(m_SDL_Window, info);
}

const char* CSDL_Window::NameSubsystem()
{
  if (m_SDL_Window != nullptr)
  {
    SDL_SysWMinfo versionInfo; SDL_VERSION(&versionInfo.version);
    if (SDL_GetWindowWMInfo(m_SDL_Window, &versionInfo))
      switch (versionInfo.subsystem)
      {
        case SDL_SYSWM_UNKNOWN: return "<unknown>";              break;
        case SDL_SYSWM_WINDOWS: return "Microsoft Windows(TM)";  break;
        case SDL_SYSWM_OS2:     return "OS/2 Warp";              break;
        case SDL_SYSWM_X11:     return "X Window System";        break;
       #if SDL_VERSION_ATLEAST(2,0,3)
        case SDL_SYSWM_WINRT:   return "WinRT";                  break;
       #endif
        case SDL_SYSWM_DIRECTFB:return "DirectFB";               break;
        case SDL_SYSWM_COCOA:   return "Apple OS X";             break;
        case SDL_SYSWM_UIKIT:   return "UIKit";                  break;
       #if SDL_VERSION_ATLEAST(2,0,2)
        case SDL_SYSWM_WAYLAND: return "Wayland";                break;
        case SDL_SYSWM_MIR:     return "Mir";                    break;
       #endif
       #if SDL_VERSION_ATLEAST(2,0,4)
        case SDL_SYSWM_ANDROID: return "Android";                break;
       #endif
       #if SDL_VERSION_ATLEAST(2,0,5)
        case SDL_SYSWM_VIVANTE: return "Vivante";                break;
       #endif
        case SDL_SYSWM_HAIKU:   return "Haiku";                  break;
        case SDL_SYSWM_KMSDRM:  return "DRM/KMS";                break;
        case SDL_SYSWM_RISCOS:  return "RiscOS";                 break;
      }
  }
  return nullptr;
}


Uint32 CSDL_Window::GetFlags()
{
  return SDL_GetWindowFlags(m_SDL_Window);
}

void* CSDL_Window::SetData(const char *name, void *userdata)
{
  return SDL_SetWindowData(m_SDL_Window, name, userdata);
}

void* CSDL_Window::GetData(const char *name)
{
  return SDL_GetWindowData(m_SDL_Window, name);
}

int CSDL_Window::SetHitTest(SDL_HitTest callback, void *callback_data)
{
  return SDL_SetWindowHitTest(m_SDL_Window, callback, callback_data);
}


#if SDL_VERSION_ATLEAST(2,0,5)
int CSDL_Window::SetModelFor(CSDL_Window* model_window)
{
  int result = SDL_SetWindowModalFor(model_window->Handle(),  m_SDL_Window);
  if (result == 0)
    m_CSDL_Window_model = model_window;
  return result;
}

CSDL_Window* CSDL_Window::GetModelFor()
{
  return m_CSDL_Window_model;
}
#endif


// [Events]
bool CSDL_Window::onKeyDown(CSDL_Window* window, SDL_KeyboardEvent* event) { return true; }
bool CSDL_Window::onKeyUp(CSDL_Window* window, SDL_KeyboardEvent* event) { return true; }
bool CSDL_Window::onMouseButton(CSDL_Window* window, SDL_MouseButtonEvent* event) { return true; }
bool CSDL_Window::onMouseMotion(CSDL_Window* window, SDL_MouseMotionEvent* event) { return true; }
bool CSDL_Window::onMouseWheel(CSDL_Window* window, SDL_MouseWheelEvent* event) { return true; }


void SDLP_SetWindowGrab(CSDL_Window* window, SDL_bool grabWindow)
{
  if (window != nullptr && window->Handle() != nullptr)
    SDL_SetWindowGrab(window->Handle(), grabWindow);
}

SDL_bool SDLP_GetWindowGrab(CSDL_Window* window)
{
  if (window == nullptr || window->Handle() == nullptr)
    return SDL_FALSE;
  return SDL_GetWindowGrab(window->Handle());
}

CSDL_Window* SDLP_GetGrabbedWindow()
{
  TNode2W<CSDL_Window*>** windowTable = SDLP_WindowTable.Head();
  while (*windowTable)
  {
    CSDL_Window* window = (CSDL_Window*) (*windowTable)->data;
    if (window->Handle() == SDL_GetGrabbedWindow())
      return window;
    windowTable = &(*windowTable)->pNext;
  }
  return nullptr;
}

CSDL_Window* SDLPAPI SDLP_GetWindowFromID(Uint32 id)
{
  TNode2W<CSDL_Window*>** windowTable = SDLP_WindowTable.Head();
  while (*windowTable)
  {
    CSDL_Window* window = (CSDL_Window*) (*windowTable)->data;
    if (window->Handle() == SDL_GetWindowFromID(id))
      return window;
    windowTable = &(*windowTable)->pNext;
  }
  return nullptr;
}






CSDL_Surface::CSDL_Surface()
{
  m_SDL_Surface = nullptr;
  m_SDLP_Window  = nullptr;
}

CSDL_Surface::~CSDL_Surface()
{
  m_SDL_Surface = nullptr;
  m_SDLP_Window  = nullptr;
}

CSDL_Surface* CSDL_Surface::Interface()
{
  return this;
}


SDL_Surface* CSDL_Surface::Create()
{
  if (m_SDLP_Window != nullptr)
    SDL_SetError("CSDL_Surface::Create: Window surface already exists.");
  else
    if (m_SDL_Surface != nullptr)
      SDL_SetError("CSDL_Surface::Create: Surface already exists.");
    else
    {

    }
  return m_SDL_Surface;
}

SDL_Surface* CSDL_Surface::Handle()
{
  return m_SDL_Surface;
}

SDL_Surface* CSDL_Surface::GetFromWindow(CSDL_Window* window)
{
  if (m_SDLP_Window != nullptr)
    SDL_SetError("CSDL_Surface::GetFromWindow: Window surface already exists.");
  else
    if (window == nullptr)
      SDL_SetError("CSDL_Surface::GetFromWindow: Invalid parameter! Window pointer not specified.");
    else
    {
      m_SDL_Surface = SDL_GetWindowSurface(window->Handle());
      if (m_SDL_Surface != nullptr)
        m_SDLP_Window = window;
    }
  return m_SDL_Surface;
}

CSDL_Window* CSDL_Surface::FromWindow()
{
  return m_SDLP_Window;
}


int CSDL_Surface::SetBlendMode(SDL_BlendMode *blendMode)
{
  return SDL_SetSurfaceBlendMode(m_SDL_Surface, *blendMode);
}

int CSDL_Surface::GetBlendMode(SDL_BlendMode *blendMode)
{
  return SDL_GetSurfaceBlendMode(m_SDL_Surface, blendMode);
}




CSDL_Renderer::CSDL_Renderer()
{
  m_SDL_Renderer = nullptr;
}

CSDL_Renderer::~CSDL_Renderer()
{
  m_SDL_Renderer = nullptr;
}

CSDL_Renderer* CSDL_Renderer::Interface()
{
  return this;
}


SDL_Renderer* CSDL_Renderer::Create(CSDL_Window* window, int index, Uint32 flags)
{
  if (window != nullptr && window->Handle() != nullptr)
    m_SDL_Renderer = SDL_CreateRenderer(window->Handle(), index, flags);
  return m_SDL_Renderer;
}

SDL_Renderer* CSDL_Renderer::Handle()
{
  return m_SDL_Renderer;
}





SDL_word CSDL_OpenGL_ref;

CSDL_OpenGL::CSDL_OpenGL()
{
  m_SDL_GLContext = nullptr;
}

CSDL_OpenGL::~CSDL_OpenGL()
{
  m_SDL_GLContext = nullptr;
}

CSDL_OpenGL* CSDL_OpenGL::Interface()
{
  return this;
}


SDL_GLContext CSDL_OpenGL::CreateContext(CSDL_Window* window)
{
  SDL_GLContext result = nullptr;
  if ((window != nullptr) && (window->GetFlags() & SDL_WINDOW_OPENGL))
    result = SDL_GL_CreateContext(window->Handle());
  return result;
}

void CSDL_OpenGL::DeleteContext()
{
  SDL_GL_DeleteContext(m_SDL_GLContext);
}

SDL_GLContext CSDL_OpenGL::GetCurrentContext()
{
  return SDL_GL_GetCurrentContext();
}

int CSDL_OpenGL::SetCurrentWindow(CSDL_Window* window)
{
  return (window != nullptr ? SDL_GL_MakeCurrent(window->Handle(), m_SDL_GLContext) : -1);
}

CSDL_Window* CSDL_OpenGL::GetCurrentWindow()
{
  TNode2W<CSDL_Window*>** windowTable = SDLP_WindowTable.Head();
  while (*windowTable)
  {
    CSDL_Window* window = (CSDL_Window*) (*windowTable)->data;
    if (window->Handle() == SDL_GL_GetCurrentWindow())
      return window;
    windowTable = &(*windowTable)->pNext;
  }
  return nullptr;
}

int CSDL_OpenGL::MakeCurrent(CSDL_Window* window)
{
  return (window != nullptr ? SDL_GL_MakeCurrent(window->Handle(), m_SDL_GLContext) : -1);
}


int CSDL_OpenGL::LoadLibrary(const char* path)
{
  CSDL_OpenGL_ref++;
  return SDL_GL_LoadLibrary(path);
}

void CSDL_OpenGL::UnloadLibrary()
{
  CSDL_OpenGL_ref--;
  if (CSDL_OpenGL_ref == 0)
    SDL_GL_UnloadLibrary();
}

SDL_bool CSDL_OpenGL::ExtensionSupported(const char* extension)
{
  return SDL_GL_ExtensionSupported(extension);
}

void* CSDL_OpenGL::GetProcAddress(const char* proc)
{
  return (CSDL_OpenGL_ref >= 1 ? SDL_GL_GetProcAddress(proc) : nullptr);
}


void CSDL_OpenGL::GetDrawableSize(int *w, int *h)
{
  CSDL_Window* window = GetCurrentWindow();
  if (window != nullptr)
    SDL_GL_GetDrawableSize(window->Handle(), w, h);
}

void CSDL_OpenGL::GetDrawableSize(SDL_Size* size)
{
  if (size != nullptr)
  {
    CSDL_Window* window = GetCurrentWindow();
    if (window != nullptr)
      SDL_GL_GetDrawableSize(window->Handle(), &size->width, &size->height);
  }
}

int CSDL_OpenGL::SetAttribute(SDL_GLattr attr, int value)
{
  return SDL_GL_SetAttribute(attr, value);
}

int CSDL_OpenGL::GetAttribute(SDL_GLattr attr, int *value)
{
  return SDL_GL_GetAttribute(attr, value);
}

void CSDL_OpenGL::ResetAttributes()
{
  SDL_GL_ResetAttributes();
}

void CSDL_OpenGL::SwapWindow(CSDL_Window* window)
{
  if (window != nullptr)
    SDL_GL_SwapWindow(window->Handle());
}

void CSDL_OpenGL::SwapWindow()
{
  CSDL_Window* window = GetCurrentWindow();
  if (window != nullptr)
    SDL_GL_SwapWindow(window->Handle());
}

int CSDL_OpenGL::SetSwapInterval(int interval)
{
  return SDL_GL_SetSwapInterval(interval);
}

int CSDL_OpenGL::GetSwapInterval()
{
  return SDL_GL_GetSwapInterval();
}





SDL_word m_CSDL_Vulkan_ref;

CSDL_Vulkan::CSDL_Vulkan()
{
  m_CSDL_Window  = nullptr;
  m_VkInstance   = 0;
  m_VkSurfaceKHR = nullptr;
}


CSDL_Vulkan::~CSDL_Vulkan()
{
  m_CSDL_Window  = nullptr;
  m_VkInstance   = 0;
  m_VkSurfaceKHR = nullptr;
}

CSDL_Vulkan* CSDL_Vulkan::Interface()
{
  return this;
}


VkSurfaceKHR* CSDL_Vulkan::CreateSurface(CSDL_Window* window, VkInstance instance)
{
  VkSurfaceKHR* result = nullptr;
  if (m_VkSurfaceKHR == nullptr && window != nullptr)
  {
    if (window->GetFlags() & SDL_WINDOW_VULKAN)
      if (SDL_Vulkan_CreateSurface(window->Handle(), instance, &m_VkSurfaceKHR) == SDL_TRUE)
      {
        m_CSDL_Window = window;
        m_VkInstance  = instance;
        result = &m_VkSurfaceKHR;
      }
  }
  return result;
}

VkSurfaceKHR* CSDL_Vulkan::GetSurface()
{
  return &m_VkSurfaceKHR;
}

VkInstance CSDL_Vulkan::GetInstance()
{
  return m_VkInstance;
}


int CSDL_Vulkan::LoadLibrary(const char* path)
{
  m_CSDL_Vulkan_ref++;
  return SDL_Vulkan_LoadLibrary(path);
}

void* CSDL_Vulkan::GetInstanceProcAddr()
{
  return SDL_Vulkan_GetVkGetInstanceProcAddr();
}

SDL_bool CSDL_Vulkan::GetInstanceExtensions(unsigned int *pCount, const char **pNames)
{
  return (m_CSDL_Window != nullptr ? SDL_Vulkan_GetInstanceExtensions(m_CSDL_Window->Handle(), pCount, pNames) : SDL_FALSE);
}

void CSDL_Vulkan::UnloadLibrary()
{
  m_CSDL_Vulkan_ref--;
  if (m_CSDL_Vulkan_ref == 0)
    SDL_Vulkan_UnloadLibrary();
}


void CSDL_Vulkan::GetDrawableSize(int *w, int *h)
{
  if (m_CSDL_Window != nullptr)
    SDL_Vulkan_GetDrawableSize(m_CSDL_Window->Handle(), w, h);
}

void CSDL_Vulkan::GetDrawableSize(SDL_Size* size)
{
  if (size != nullptr && m_CSDL_Window != nullptr)
    SDL_Vulkan_GetDrawableSize(m_CSDL_Window->Handle(), &size->width, &size->height);
}





int SDLP_ShowMessageBox(const SDLP_MessageBoxData *messageboxdata, int *buttonid)
{
  if (messageboxdata == nullptr)
    return -1;

  SDL_MessageBoxData m_SDL_mbs;

  m_SDL_mbs.flags       = messageboxdata->flags;
  m_SDL_mbs.window      = (messageboxdata->window != nullptr ? messageboxdata->window->Handle() : nullptr);
  m_SDL_mbs.title       = messageboxdata->title;
  m_SDL_mbs.message     = messageboxdata->message;
  m_SDL_mbs.numbuttons  = messageboxdata->numbuttons;
  m_SDL_mbs.buttons     = messageboxdata->buttons;
  m_SDL_mbs.colorScheme = messageboxdata->colorScheme;

  return SDL_ShowMessageBox(&m_SDL_mbs, buttonid);
}

int SDLP_ShowSimpleMessageBox
 (Uint32 flags, const char *title, const char *message, CSDL_Window* window)
{
  return SDL_ShowSimpleMessageBox(flags, title, message, (window != nullptr ? window->Handle() : nullptr));
}
