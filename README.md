SDL+: Object-Oriented SDL
Copyright (C) 2022 Kris Houston <ghostcoder22@gmail.com>

Until I'm able to build an automated script or put together a batch file, the installation SDL 2.x development libraies will have to manually be accomplished with the following steps:

1) Uncompress SDL2-devel-2.x-mingw in a temporary folder and open it with an archiver.
2) Move <SDL2-2.x>/i686-w64-mingw32/include to <SDL_plus>/contrib/SDL2/include.
3) Move <SDL2-2.x>/i686-w64-mingw32/lib to <SDL_plus>/contrib/SDL2/lib/x32.
4) Move <SDL2-2.x>/i686-w64-mingw32/SDL2.dll to <SDL_plus>/contrib/redist and copy that file to <SDL_plus>/bin/32.
5) Move <SDL2-2.x>/x86_64-w64-mingw32 to <SDL_plus>/contrib/SDL2/lib/x64.
6) Move <SDL2-2.x>/x84_64-w64-mingw32/SDL2.dll to <SDL_plus>/contrib/redist and copy that file to <SDL_plus>/bin/64.

INSTALLATION LEGEND: <SDL2-2.x> refers to SDL 2's version folder within SDL2-devel-2.x-mingw. <SDL_plus> refers to SDL+ install folder.
