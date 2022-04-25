/*
  SDL+: Object-Oriented SDL
  Copyright (C) 2022 Kris Houston <ghostcoder22@gmail.com>

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
 *  \file SDLP_test_window.hpp
 *
 *  Window C++ test source for the SDL+ library
 */

#include <SDL_plus.hpp>
#include <stdarg.h>

int SDL_ShowSimpleMessageBoxV(Uint32 flags, const char *title, SDL_Window *window, const char *message, ...)
{
  va_list args;
  va_start(args, message);
  int r =  SDL_ShowSimpleMessageBox(flags, title, args, window);
  va_end(args);
  return r;
}

class SDLP_test_windowFrame: public CSDL_Window
{
  public:
    virtual bool onKeyDown(CSDL_Window* window, SDL_KeyboardEvent* event)
    {
      char key[14];
      if ((event->keysym.mod & KMOD_SHIFT) && (isalpha(event->keysym.sym)))
        sprintf(key, "%c (%s)", toupper(event->keysym.sym), SDL_GetKeyName(event->keysym.mod));
      else if (isalpha(event->keysym.sym))
        sprintf(key, "%c (%s)", tolower(event->keysym.sym), SDL_GetKeyName(event->keysym.mod));
      else
        sprintf(key, "%s", SDL_GetKeyName(event->keysym.sym));
      SDL_ShowSimpleMessageBox(0, "Keyboard", key, window->Handle());
      if (event->keysym.sym == SDLK_ESCAPE)
        return false;
      return true;
    }
};

define_SDLP_app(SDLP_test_window)
{
  public:
    SDLP_test_window() {}
    ~SDLP_test_window() {}
    int Main(CSDL* iface, Ustring appname, int argc, char** argv)
    {
      iface->Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

      SDLP_test_windowFrame window;
      window.Create(appname, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

      CSDL_EventManager events;
      events.ProcessEvents();

      iface->Quit();
      return 0;
    }
};
declare_SDLP_app(SDLP_test_window, "SDLP_test_window");

