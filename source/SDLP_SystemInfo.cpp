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
 *  \file SDLP_SystemInfo.cpp
 *
 *  SDL+ system information C++ source
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL_plus/SDLP_Video.hpp>
#include <SDL_plus/SDLP_SystemInfo.hpp>

bool SDL_IF_VERSION(Uint8 x, Uint8 y, Uint8 z, const char* s)
{
  SDL_version lv; SDL_GetVersion(&lv);
  if (lv.major < x || lv.minor < y || lv.patch < z)
  {
    SDL_Log("SDL version %d.%d.%d or higher is required for function %s", x, y, z, s);
    return false; \
  }
  return true; \
}


void SDLP_GetVersion(SDL_version* version)
{
  SDLP_VERSION(version);
}

bool SDLP_IF_VERSION(Uint8 x, Uint8 y, Uint8 z, const char* s)
{
  SDL_version lv; SDLP_GetVersion(&lv);
  if (lv.major < x || lv.minor < y || lv.patch < z)
  {
    SDL_Log("SDL version %d.%d.%d or higher is required for function %s", x, y, z, s);
    return false;
  }
  return true;
}


bool SDLP_GetSystemInfo(SDLP_SystemInfo* systemInfo)
{
  if (systemInfo != nullptr)
  {
    if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
      SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* infoWindow = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
    if (infoWindow != nullptr)
    {
      SDL_SysWMinfo SysWMInfo; SDL_VERSION(&SysWMInfo.version);
      if (SDL_GetWindowWMInfo(infoWindow, &SysWMInfo))
      {
        systemInfo->SDL_Version.info.major = SysWMInfo.version.major;
        systemInfo->SDL_Version.info.minor = SysWMInfo.version.minor;
        systemInfo->SDL_Version.info.patch = SysWMInfo.version.patch;
        sprintf(systemInfo->SDL_Version.string, "SDL version %d.%d.%d",
                SysWMInfo.version.major, SysWMInfo.version.minor, SysWMInfo.version.patch);
        SDLP_VERSION(&systemInfo->SDLP_Version.info);
        sprintf(systemInfo->SDLP_Version.string,
                "SDL+ version %d.%d.%d", SDLP_MAJOR_VERSION, SDLP_MINOR_VERSION, SDLP_PATCHLEVEL);
        systemInfo->platform  = SDL_GetPlatform();
        systemInfo->subsystem = SysWMInfo.subsystem;

        systemInfo->CPU.count               = SDL_GetCPUCount();
        systemInfo->CPU.L1_cache_line_size  = SDL_GetCPUCacheLineSize();
        systemInfo->CPU.features.has3DNow   = (SDL_Has3DNow() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasMMX     = (SDL_HasMMX() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasSSE     = (SDL_HasSSE() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasSSE2    = (SDL_HasSSE2() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasSSE3    = (SDL_HasSSE3() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasSSE41   = (SDL_HasSSE41() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasSSE42   = (SDL_HasSSE42() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasAVX     = (SDL_HasAVX() == SDL_TRUE ? true : false);
       #if SDL_VERSION_ATLEAST(2,0,9)
        systemInfo->CPU.features.hasAVX2    = (SDL_HasAVX2() == SDL_TRUE ? true : false);
       #else
        systemInfo->CPU.features.hasAVX2    = false;
       #endif
       #if SDL_VERSION_ATLEAST(2,0,12)
        systemInfo->CPU.features.hasAVX512F = (SDL_HasAVX512F() == SDL_TRUE ? true : false);
       #else
        systemInfo->CPU.features.hasAVX512F = false;
       #endif
        systemInfo->CPU.features.hasAltiVec = (SDL_HasAltiVec() == SDL_TRUE ? true : false);
        systemInfo->CPU.features.hasRDTSC   = (SDL_HasRDTSC() == SDL_TRUE ? true : false);
       #if SDL_VERSION_ATLEAST(2,0,6)
        systemInfo->CPU.features.hasARMSIMD = (SDL_HasARMSIMD() == SDL_TRUE ? true : false);
       #else
        systemInfo->CPU.features.hasARMSIMD = false;
       #endif
        systemInfo->CPU.features.hasNEON    = (SDL_HasNEON() == SDL_TRUE ? true : false);

        systemInfo->RAM = SDL_GetSystemRAM();
        SDL_GetBatteryPower(&systemInfo->battery_power);
        systemInfo->endian = SDL_BYTEORDER;

        SDL_DestroyWindow(infoWindow);
        return true;
      }
    }
  }
  return false;
}


void SDL_GetBatteryPower(SDL_BatteryPower* batteryInfo)
{
  if (batteryInfo != nullptr)
    batteryInfo->state = SDL_GetPowerInfo(&batteryInfo->seconds, &batteryInfo->percentage);
}
