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
 *  \file SDLP_test_DisplayModeWalker.cpp
 *
 *  SDL+ Test: Display Mode Walker
 */

#include <SDL_plus.hpp>

int SDLP_test_WalkDisplayModes(int displayIndex, SDL_DisplayMode* displayMode)
{
  printf("[%d]: %dx%d %dHz\n", displayIndex, displayMode->w, displayMode->h,
                               displayMode->refresh_rate);
  return true;
}

define_SDLP_app(SDLP_test_WalkDisplay)
{
  public:
    int Main(CSDL* iface, Ustring appname, int argc, char** argv)
    {
      iface->Init(SDL_INIT_VIDEO);

      CSDL_Video videoInfo;
      videoInfo.WalkDisplayModes(SDLP_test_WalkDisplayModes);
      printf("\n");
      system("PAUSE");
      printf("\n");

      return 0;
    }
};
declare_SDLP_app(SDLP_test_WalkDisplay, "SDL+ Test: Display Mode Walker");
