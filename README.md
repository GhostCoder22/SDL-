SDL+: Object-Oriented SDL
Copyright (C) 2022 Ghost Coder <ghostcoder22@gmail.com>

SDL+ is my object-oriented approach for wrapping SDL around the C++ language, but it's my hope that, one day, SDL+ will hopefully extend Sam Lantinga's SDL in such a way to provide drawn widget support, dynamic loading and usage of SDL2_image, SDL2_mixer, SDL2_net, and SDL2_ttf.

So far, SDL+ includes the following features:

1) Command line argument parsing.
2) Basic Command line Interpreter (CLI) stored in a linked list and parsed by walking through said linked list. SDL_test_main demostrates this.
3) SDL window creation (CSDL_Window::Create) stores in a window table (linked list).
4) Basic event processor (CSDL_EventManager::ProcessEvents) parses window table to correctly make calls to indevidual window method procedures (CSDL_Window::onKeyDown). SDL_test_window demostates this.
5) Display mode walking (emumerating) accomplished by CSDL_Video::WalkDisplayModes and CSDL_Video::WalkDisplayModesEx.
6) Nearly full implementation of SDL 2.x subsystems as C++ classes'
1) CSDL_Window -> SDL window
2) CSDL_Surface -> SDL surface
3) CSDL_OpenGL -> SDL OpenGL support
4) CSDL_Vulkan -> SDL Vulkan support
5) CSDL_Texture -> SDL texture **UNIMPLEMENTED**

Until I'm able to build an automated script or put together a batch file, the installation SDL 2.x development libraies will have to manually be accomplished with the following steps:

1) Uncompress SDL2-devel-2.x-mingw in a temporary folder and open it with an archiver.
2) Move <SDL2-2.x>/i686-w64-mingw32/include to <SDL_plus>/contrib/SDL2/include.
3) Move <SDL2-2.x>/i686-w64-mingw32/lib to <SDL_plus>/contrib/SDL2/lib/x32.
4) Move <SDL2-2.x>/i686-w64-mingw32/SDL2.dll to <SDL_plus>/contrib/SDL2/redist/x32 and copy that file to <SDL_plus>/bin/x32.
5) Move <SDL2-2.x>/x86_64-w64-mingw32 to <SDL_plus>/contrib/SDL2/lib/x64.
6) Move <SDL2-2.x>/x84_64-w64-mingw32/SDL2.dll to <SDL_plus>/contrib/SDL2/redist/x64 and copy that file to <SDL_plus>/bin/x64.

INSTALLATION LEGEND: <SDL2-2.x> refers to SDL 2's version folder within SDL2-devel-2.x-mingw. <SDL_plus> refers to SDL+ install folder.

At this time, Code::Blocks the only available project. Please note SDL+ is under active development by myself.

If anyone has any suggestions and/or ideas, please don't hesitate to contribute potential ideas to this project by emailing me, Ghost Coder, at ghostcoder22@gmail.com.
