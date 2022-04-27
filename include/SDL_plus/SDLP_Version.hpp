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
 *  \file SDLP_Version.hpp
 *
 *  SDL+ version C++ header
 */

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
 *  \file SDLP_Version.hpp
 *
 *  SDL+ Version
 */

#ifdef __cplusplus
#ifndef SDLP_VERSION_HPP
#define SDLP_VERSION_HPP

#ifdef WINDOWS
 #include <windows.h>
#endif

#include <SDL2/SDL.h>

#include <SDL2/begin_code.h>
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Printable format: "%d.%d.%d", MAJOR, MINOR, PATCHLEVEL
*/
#define SDLP_MAJOR_VERSION 0
#define SDLP_MINOR_VERSION 0
#define SDLP_PATCHLEVEL    1

/* This macro can be used to fill a version structure with the compile-time
 * version of the SDL_plus library.
 */
#define SDLP_VERSION(X)            \
{                                  \
  (X)->major = SDLP_MAJOR_VERSION; \
  (X)->minor = SDLP_MINOR_VERSION; \
  (X)->patch = SDLP_PATCHLEVEL;    \
}

/**
 *  This is the version number macro for the current SDL+ version.
 */
#define SDLP_COMPILEDVERSION \
  SDLP_VERSIONNUM(SDLP_MAJOR_VERSION, SDLP_MINOR_VERSION, SDLP_PATCHLEVEL)

#define SDLP_VERSIONSTR(s) \
  sprintf(s, "SDL+ version %d.%d.%d", SDLP_MAJOR_VERSION, SDLP_MINOR_VERSION, SDLP_PATCHLEVEL)

#ifdef __cplusplus
}
#endif
//#ifndef _begin_code_h
#include <SDL2/close_code.h>
//#endif

#endif // SDLP_VERSION_HPP
#endif // __cplusplus
