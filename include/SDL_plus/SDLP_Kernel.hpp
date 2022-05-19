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
 *  \file SDLP_kernel.hpp
 *
 *  Kernel C++ header for the SDL+ library
 */


#ifdef __cplusplus
#ifndef SDLP_KERNEL_HPP
#define SDLP_KERNEL_HPP

#include <SDL_plus/SDLP_defines.hpp>

#ifdef __cplusplus
extern "C" {
#endif


typedef unsigned long SDLP_errorCode;
typedef const char*   SDLP_errorMessage;

class CSDL;
class CSDL_Window;

typedef struct SDLP
{
    CSDL*   iface;
    Ustring appname;
    Uint32  flags;
} SDLP;

enum SDLP_CLI_TYPE { CLI_ERROR,
                     CLI_FILE, CLI_RESPONSEFILE,
                     CLI_STRING, CLI_NUMBER,
                     CLI_IP, CLI_URL,  CLI_PASSWORD };

class SDLPAPI CSDL
{
  public:
    CSDL();
    ~CSDL();
    CSDL* Instance();

    int Main(CSDL* iface, Ustring appname, int argc, char** argv);

    int  Init(Uint32 flags);
    void Quit();
    int  InitSubSystem(Uint32 flags);
    void QuitSubSystem(Uint32 flags);

    // Events
    //
    virtual bool onQuitEvent(CSDL* iface, CSDL_Window* window);

    Ustring AppName();

    bool CLI_Accept(Ustring parameter, SDLP_CLI_TYPE type);
    bool CLI_Process(int argc, char** argv, bool (fnProcessor)(int argc, Ustring argv, Ustring next_argv));
    bool CLI_Process(int argc, char** argv, bool (fnProcessor)(int argc, Ustring parameter, SDLP_CLI_TYPE type,
                                                               Ustring nextArgV));
    bool CLI_ProcessResponseFile(int argc, char** argv, Ustring filename);
};
CSDL* SDLPAPI CSDL_GetInterface();

#ifdef WINDOWS
#include <windows.h>
LPSTR* SDLPAPI CommandLineToArgvA(LPCSTR lpCmdline, int* numargs);
#endif

 #ifndef BUILDLIB_SDLP
  #define define_SDLP_app(iface) class iface: public CSDL
 #ifdef WINDOWS
  #define declare_SDLP_app(iface, appname) \
   int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInst, LPSTR lpCmdLine, int nShowCmd) \
   { CSDL rEP; rEP.Main(&rEP, appname, 0, nullptr); \
     int argc = 0; char** argv = CommandLineToArgvA(GetCommandLine(), &argc); \
     iface EP; int result = EP.Main(&rEP, appname, argc, argv); \
     return result; }
 #else
  #define declare_SDLP_app(iface, appname) \
   int main(int argc, char** argv) \
   { CSDL rEP; rEP.Main(&rEP, appname, argc, argv); \
     iface EP; int result = EP.Main(&rEP, appname, argc, argv); \
     return result; }

 #endif // WINDOWS
 #endif // BUILDLIB_SDLP

#ifdef __cplusplus
}
#endif

#endif // SDLP_KERNEL_HPP
#endif // __cplusplus
