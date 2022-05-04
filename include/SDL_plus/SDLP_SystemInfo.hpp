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
 *  \file SDLP_SystemInfo.hpp
 *
 *  SDL+ system information C++ header
 */

#ifdef __cplusplus
#ifndef SDLP_SYSTEMINFO_HPP
#define SDLP_SYSTEMINFO_HPP

#ifdef WINDOWS
 #include <windows.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_syswm.h>
#include <SDL_plus/SDLP_defines.hpp>

#ifndef _begin_code_h
#include <SDL2/begin_code.h>
#endif // _begin_code_h
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

bool SDLPAPI SDL_IF_VERSION(Uint8 x, Uint8 y, Uint8 z, const char* s);

void SDLPAPI SDLP_GetVersion(SDL_version* version);
bool SDLPAPI SDLP_IF_VERSION(Uint8 x, Uint8 y, Uint8 z, const char* s);


typedef struct SDL_BatteryPower
{
    SDL_PowerState  state;
    int             seconds, percentage;
} SDL_BatteryPower;

void SDLPAPI SDL_GetBatteryPower(SDL_BatteryPower* batteryInfo);

class CSDL_Window;
typedef struct SDLP_SystemInfo
{
    struct
    {
        SDL_version  info;
        char*        string;
    } SDL_Version, SDLP_Version;
    const char*     platform;
    SDL_SYSWM_TYPE  subsystem;
    struct
    {
        int  count;
        int  L1_cache_line_size;
        struct
        {
            bool  has3DNow, hasMMX, hasSSE,hasSSE2,hasSSE3,hasSSE41,hasSSE42;
            bool  hasAVX,hasAVX2,hasAVX512F, hasAltiVec, hasRDTSC, hasNEON;
            bool  hasARMSIMD;
        } features;
    } CPU;
    int               RAM;
    SDL_BatteryPower  battery_power;
    int               endian; // system byte order
} SDLP_SystemInfo;

bool SDLPAPI SDLP_GetSystemInfo(SDLP_SystemInfo* systemInfo);


#ifdef __cplusplus
}
#endif
#ifndef _begin_code_h
#include <SDL2/close_code.h>
#endif

#endif // SDLP_SYSTEMINFO_HPP
#endif // __cplusplus
