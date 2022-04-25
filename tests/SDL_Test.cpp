#include <windows.h>
#include <SDL2/SDL.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInst, LPSTR lpCmdLine, int nCmdShow)
{
  SDL_Window* window = SDL_CreateWindow("SDL Test", 200, 200, 640, 480, 0);
  if (window == nullptr)
    return -1;
  return 0;
}
