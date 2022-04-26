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

TList2W<CSDL_Window*> SDLP_WindowTable;
TNode2W<CSDL_Window*>** SDLP_WindowTablePtr()
{
  TNode2W<CSDL_Window*>** windowTable = SDLP_WindowTable.Head();
  return &(*windowTable);
}


CSDL_Window::CSDL_Window()
{
  m_pWindow = nullptr;
  m_fFullscreen = 0;
}

CSDL_Window::~CSDL_Window()
{
  m_pWindow = nullptr;
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
      SDLP_WindowTable.Add(this);
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

SDL_Window* CSDL_Window::Handle()
{
  return m_pWindow;
}


int CSDL_Window::SetFullscreen(Uint32 flags)
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

int CSDL_Window::GetFullscreen()
{
  return m_fFullscreen;
}

int CSDL_Window::Fullscreen()
{
  int fullscreen = 0;
  if (m_fFullscreen == SDL_WINDOW_FULLSCREEN)
    fullscreen = 0;
  else
    fullscreen = SDL_WINDOW_FULLSCREEN;
  return SetFullscreen(fullscreen);
}



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
