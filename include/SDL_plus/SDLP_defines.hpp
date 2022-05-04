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
 *  \file SDLP_defines.cpp
 *
 *  SDL+ library type definitions.
 */

#ifdef __cplusplus
#ifndef SDLP_DEFINES_HPP
#define SDLP_DEFINES_HPP

#ifdef WINDOWS
 #include <windows.h>
#endif

#include <SDL2/SDL.h>

#include <SDL2/begin_code.h>
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef SDLPAPI
# if defined(WINDOWS) || defined(__CYGWIN__)
#  ifdef BUILDLIB_SDLP
#   define SDLPAPI __declspec(dllexport)
#  else
#   define SDLPAPI __declspec(dllimport)
#  endif
# elif defined(__OS2__)
#   ifdef BUILDLIB_SDLP
#    define SDLPAPI __declspec(dllexport)
#   else
#    define SDLPAPI __declspec(dllimport)
#   endif
# else
#  if defined(__GNUC__) && __GNUC__ >= 4
#   define SDLPAPI __attribute__ ((visibility("default")))
#  else
#   define SDLPAPI
#  endif
# endif
#endif

typedef       char     Uchar;
typedef const char*    Ustring;
typedef       wchar_t  Uwchar;
typedef const wchar_t* Uwstring;
#ifdef UNICODE
#define Utstring Uwstring
#else
#define Utstring Ustring
#endif
#ifndef TEXT
#ifdef UNICODE
#define TEXT(x)  L##x
#else
#define TEXT(x)  x
#endif // UNICODE
#endif // TEXT

typedef unsigned char  SDL_byte;
typedef unsigned short SDL_word;
typedef unsigned int   SDL_Uint;
typedef unsigned long  SDL_Ulong;
typedef unsigned long  SDL_dword;

#define BITMASK_PUT(bit, mask) bit = bit | mask
#define BITMASK_CLEAR(bit, mask) bit = bit & ~mask
#define BITMASK_FLIP(bit, mask) bit = bit ^ mask


#ifdef WINDOWS
typedef HINSTANCE Uinstance;
#else
typedef int Uinstance;
#endif

#ifdef __cplusplus
}
#endif
//#ifndef _begin_code_h
#include <SDL2/close_code.h>
//#endif

#endif // SDLP_DEFINES_HPP
#endif // __cplusplus
