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
 *  \file SDLP_intenals.hpp
 *
 *  SDL+ Internals C++ Header
 */

#ifdef __cplusplus
#ifndef SDLP_INTERNALS_HPP
#define SDLP_INTERNALS_HPP

#include <SDL_plus/SDLP_Video.hpp>
#include <SDL_plus/Containers/TList.hxx>

TNode2W<CSDL_Window*>** SDLP_WindowTablePtr();

#endif // SDLP_INTERNALS_HPP
#endif // __cplusplus
