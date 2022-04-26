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
 *  \file SDLP_Video.hpp
 *
 *  SDL+ Video Subsystem C++ header
 */

#ifdef __cplusplus
#ifndef SDLP_VIDEO_HPP
#define SDLP_VIDEO_HPP

#include <SDL_plus/SDLP_defines.hpp>
#include <SDL_plus/SDLP_Video.hpp>

#include <SDL2/begin_code.h>
/* Set up for C function definitions, even when using C++ */
//#ifdef __cplusplus
extern "C" {
//#endif

class CSDL_Window;

class SDLPAPI CSDL_Surface
{
  public:
    CSDL_Surface();
    ~CSDL_Surface();
    CSDL_Surface* Instance();

    SDL_Surface* Create();
    SDL_Surface* Handle();
    SDL_Surface* GetFromWindow(CSDL_Window* window);
    CSDL_Window* FromWindow();

  private:
    SDL_Surface* m_pSurface;
    CSDL_Window* m_pWindow;
};

class SDLPAPI CSDL_Renderer
{
  public:
    CSDL_Renderer();
    ~CSDL_Renderer();
    CSDL_Renderer* Instance();

    SDL_Renderer* Create(CSDL_Window* window, int index, Uint32 flags);
    SDL_Renderer* Handle();

  private:
    SDL_Renderer* m_pRenderer;
};

class SDLPAPI CSDL_Window: public CSDL_Surface
{
  public:
    CSDL_Window();
    ~CSDL_Window();
    CSDL_Window* Instance();

    SDL_Window* Create(const char* title, int x, int y, int w, int h, Uint32 flags);
    SDL_Window* CreateWithRenderer(const char* title, int width, int height, Uint32 window_flags, CSDL_Renderer* renderer);
    SDL_Window* Handle();

    int SetFullscreen(Uint32 flags);
    int GetFullscreen();
    int Fullscreen();


   // [Events]
    virtual bool onKeyDown(CSDL_Window* window, SDL_KeyboardEvent* event);
    virtual bool onKeyUp(CSDL_Window* window, SDL_KeyboardEvent* event);
    virtual bool onMouseButton(CSDL_Window* window, SDL_MouseButtonEvent* event);
    virtual bool onMouseMotion(CSDL_Window* window, SDL_MouseMotionEvent* event);
    virtual bool onMouseWheel(CSDL_Window* window, SDL_MouseWheelEvent* event);

  protected:
    SDL_Window* m_pWindow;
    int         m_fFullscreen;
};

//#ifdef __cplusplus
}
//#endif
#include <SDL2/close_code.h>

#endif // SDLP_VIDEO_HPP
#endif // __cplusplus
