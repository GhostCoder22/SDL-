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
#include "SDLP_internals.hpp"

CSDL_Video::CSDL_Video() {}
CSDL_Video::~CSDL_Video() {}
CSDL_Video* CSDL_Video::Instance() { return this; }

int CSDL_Video::WalkDisplayModes(SDLP_DisplayModeWalker walker)
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


int CSDL_Video::WalkVideoDrivers(SDLP_VideoDriverWalker walker)
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
  m_pWindow = nullptr;
  m_szTitle = nullptr;
  m_fFullscreen = 0;
}

CSDL_Window::~CSDL_Window()
{
  m_pWindow = nullptr;
  m_szTitle = nullptr;
  m_fFullscreen = 0;
}

CSDL_Window* CSDL_Window::Instance()
{
  return this;
}


SDL_Window* CSDL_Window::Create(const char* title, int x, int y, int w, int h, Uint32 flags)
{
  if (m_pWindow == nullptr)
  {
    m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);
    if (m_pWindow != nullptr)
    {
      CSDL_Surface::GetFromWindow(this);
      m_szTitle = title;
      SDLP_WindowTable.Add(this);
      CSDL_Window_AddRef();
    }
  }
  return m_pWindow;
}

SDL_Window* CSDL_Window::CreateWithRenderer(const char* title, int width, int height, Uint32 window_flags, CSDL_Renderer* renderer)
{
  if (m_pWindow != nullptr)
    SDL_SetError("CSDL_Surface::CreateWithRenderer: Window surface already exists.");
  else
    if (renderer == nullptr)
      SDL_SetError("CSDL_Surface::CreateWithRenderer: Invalid parameter! Renderer not specified.");
    else
    {
      m_pWindow = Create(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
      SDL_Renderer* Renderer = renderer->Create(this, -1, 0);
      if (!Renderer)
        SDL_SetError("CSDL_Surface::CreateWithRenderer: Window created successfully\nbut renderer creation failed.");
    }
  return m_pWindow;
}

SDL_Window* CSDL_Window::CreateFrom(const void *data)
{
  if ((m_pWindow == nullptr) && (data != nullptr))
  {
    m_pWindow = SDL_CreateWindowFrom(data);
    if (m_pWindow != nullptr)
    {
      CSDL_Surface::GetFromWindow(this);
      m_szTitle = "CSDL_Window::CreateFrom";
      SDLP_WindowTable.Add(this);
      CSDL_Window_AddRef();
    }
  }
  return m_pWindow;
}

void CSDL_Window::Destroy()
{
  if (m_pWindow != nullptr)
  {
    SDL_DestroyWindow(m_pWindow);
    CSDL_Window_ReleaseRef();
  }
}

SDL_Window* CSDL_Window::Handle() { return m_pWindow; }

Ustring CSDL_Window::Title() { return m_szTitle; }


int CSDL_Window::SetDisplayMode(const SDL_DisplayMode *mode)
{
  if ((m_pWindow != nullptr) && (mode != nullptr))
    return SDL_SetWindowDisplayMode(m_pWindow, mode);
  return -1;
}

int CSDL_Window::GetDisplayMode(SDL_DisplayMode *mode)
{
  if ((m_pWindow != nullptr) && (mode != nullptr))
    return SDL_GetWindowDisplayMode(m_pWindow, mode);
  return -1;
}

int CSDL_Window::SetFullscreenMode(Uint32 flags)
{
  if (m_pWindow != nullptr)
  {
    int result = SDL_SetWindowFullscreen(m_pWindow, flags);
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


void CSDL_Window::DisableScreenSaver() { SDL_DisableScreenSaver(); }
void CSDL_Window::EnableScreenSaver() { SDL_EnableScreenSaver(); }
bool CSDL_Window::IsScreenSaverEnabled() { return SDL_IsScreenSaverEnabled(); }


// [Events]
bool CSDL_Window::onKeyDown(CSDL_Window* window, SDL_KeyboardEvent* event) { return true; }
bool CSDL_Window::onKeyUp(CSDL_Window* window, SDL_KeyboardEvent* event) { return true; }
bool CSDL_Window::onMouseButton(CSDL_Window* window, SDL_MouseButtonEvent* event) { return true; }
bool CSDL_Window::onMouseMotion(CSDL_Window* window, SDL_MouseMotionEvent* event) { return true; }
bool CSDL_Window::onMouseWheel(CSDL_Window* window, SDL_MouseWheelEvent* event) { return true; }



CSDL_Surface::CSDL_Surface()
{
  m_pSurface = nullptr;
  m_pWindow  = nullptr;
}

CSDL_Surface::~CSDL_Surface()
{
  m_pSurface = nullptr;
  m_pWindow  = nullptr;
}

CSDL_Surface* CSDL_Surface::Instance()
{
  return this;
}


SDL_Surface* CSDL_Surface::Create()
{
  if (m_pWindow != nullptr)
    SDL_SetError("CSDL_Surface::Create: Window surface already exists.");
  else
    if (m_pSurface != nullptr)
      SDL_SetError("CSDL_Surface::Create: Surface already exists.");
    else
    {

    }
  return m_pSurface;
}

SDL_Surface* CSDL_Surface::Handle()
{
  return m_pSurface;
}

SDL_Surface* CSDL_Surface::GetFromWindow(CSDL_Window* window)
{
  if (m_pWindow != nullptr)
    SDL_SetError("CSDL_Surface::GetFromWindow: Window surface already exists.");
  else
    if (window == nullptr)
      SDL_SetError("CSDL_Surface::GetFromWindow: Invalid parameter! Window pointer not specified.");
    else
    {
      m_pSurface = SDL_GetWindowSurface(window->Handle());
      if (m_pSurface != nullptr)
        m_pWindow = window;
    }
  return m_pSurface;
}

CSDL_Window* CSDL_Surface::FromWindow()
{
  return m_pWindow;
}





CSDL_Renderer::CSDL_Renderer()
{
  m_pRenderer = nullptr;
}

CSDL_Renderer::~CSDL_Renderer()
{
  m_pRenderer = nullptr;
}

CSDL_Renderer* CSDL_Renderer::Instance()
{
  return this;
}


SDL_Renderer* CSDL_Renderer::Create(CSDL_Window* window, int index, Uint32 flags)
{
  if (window != nullptr && window->Handle() != nullptr)
    m_pRenderer = SDL_CreateRenderer(window->Handle(), index, flags);
  return m_pRenderer;
}

SDL_Renderer* CSDL_Renderer::Handle()
{
  return m_pRenderer;
}
