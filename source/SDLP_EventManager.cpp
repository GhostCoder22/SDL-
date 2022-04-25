/*
  SDL+: Object-Oriented SDL
  Copyright (C) 2022 Kris Houston <ghostcoder22@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no events will the authors be held liable for any damages
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
 *  \file SDLP_Event.cpp
 *
 *  SDL+ Event Subsystem C++ source
 */

#include <SDL_plus/SDLP_EventManager.hpp>
#include "SDLP_internals.hpp"

CSDL_EventManager::CSDL_EventManager()
{
}

CSDL_EventManager::~CSDL_EventManager()
{
}


bool CSDL_EventManager::ProcessEvents()
{
  bool result = true;
  SDL_Event events; bool quitEvent = false;
  while (!quitEvent)
  {
    while (SDL_PollEvent(&events))
    {
      TNode2W<CSDL_Window*>** windowTable = SDLP_WindowTablePtr();
      while (*windowTable)
      {
        CSDL_Window* window = (CSDL_Window*) (*windowTable)->data;
        switch (events.type)
        {
          case SDL_QUIT:
            quitEvent = true;
          return false;
          case SDL_WINDOWEVENT:
            switch (events.window.event)
            {
              case SDL_WINDOWEVENT_CLOSE:
              {
                quitEvent = true;
                return false;
              }
            }
          break;
          case SDL_KEYDOWN:
            result = window->onKeyDown(window, &events.key);
          break;
          case SDL_KEYUP:
            result = window->onKeyUp(window, &events.key);
          break;
          case SDL_MOUSEMOTION:
            result = window->onMouseMotion(window, &events.motion);
          break;
          case SDL_MOUSEBUTTONUP:
          case SDL_MOUSEBUTTONDOWN:
            result = window->onMouseButton(window, &events.button);
          break;
          case SDL_MOUSEWHEEL:
            result = window->onMouseWheel(window, &events.wheel);
          break;
        }
        if (!result)
          return false;
        windowTable = &(*windowTable)->pNext;
      }
    }
  }
  return result;
}
