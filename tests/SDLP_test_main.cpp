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
 *  \file SDL_test_main.hpp
 *
 *  Main C++ test source for the SDL+ library
 */

#include <SDL_plus.hpp>

bool SDLP_test_cmdline(int argc, Ustring argv, Ustring next_argv)
{
  printf("argv[%d]: %s -> next_argv: ", argc, argv);
  if (next_argv != nullptr)
    printf("%s\n", next_argv);
  else
    printf("<nullptr>\n");
  return true;
}

bool SDLP_test_cli(int argc, Ustring argv, SDLP_CLI_TYPE type, Ustring next_argv)
{
  printf("argv[%d]: %s [CLI_", argc, argv);
  switch (type)
  {
    case CLI_STRING: printf("STRING"); break;
    case CLI_NUMBER: printf("NUMBER"); break;
    default:
      printf("UNKNOWN");
  }
  printf("] -> ");
  if (next_argv != nullptr)
    printf("%s\n", next_argv);
  else
    printf("<nullptr>\n");
  return true;
}

define_SDLP_app(SDLP_test_main)
{
  public:
    SDLP_test_main() {}
    ~SDLP_test_main() {}
    int Main(CSDL* iface, Ustring appname, int argc, char** argv)
    {
      printf("This test application, \'%s\', will conduct several tests.\n"
             "The first of these such tests will involve the command line.\n\n", appname);
      printf("argc: %d\n", argc);
      CLI_Process(argc, argv, &SDLP_test_cmdline);

      printf("\n\nThis next test will involve a smart command line\n\n");
      CLI_Accept("string", CLI_STRING);
      CLI_Accept("int", CLI_NUMBER);
      CLI_Process(argc, argv, &SDLP_test_cli);
      printf("\n");
      PAUSE;
      return 0;
    }
};
declare_SDLP_app(SDLP_test_main, "SDLP_test_main");

