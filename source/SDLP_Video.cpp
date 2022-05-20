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
 *  \file SDLP_kernel.cpp
 *
 *  Kernel C++ source for the SDL+ library
 */

#include <SDL_plus/SDLP_kernel.hpp>
#include "SDLP_internals.hpp"

struct SDLP_CLI_ENTRY
{
    SDLP_CLI_ENTRY*    next;
    SDLP_CLI_TYPE      type;
    Ustring            parameter;
    unsigned char      index;
    SDLP_CLI_ENTRY() { next = nullptr; }
};
SDLP_CLI_ENTRY* SDLP_CLI_TABLE;
unsigned char SDLP_CLI_ENTRIES;

SDLP   m_SDLP;
Uint32 m_SDLP_init;

CSDL::CSDL()
{
}

CSDL::~CSDL()
{
  if (SDLP_CLI_ENTRIES > 0)
  {
    SDLP_CLI_ENTRY** entry = &SDLP_CLI_TABLE;
    while (*entry)
    {
      SDLP_CLI_ENTRY* tempEntry = (*entry);
      (*entry) = (*entry)->next;
      delete tempEntry; tempEntry = nullptr;
      SDLP_CLI_ENTRIES--;
    }
    entry = &(*entry)->next;
    memset(&m_SDLP, 0, sizeof(SDLP));
  }
}

CSDL* CSDL::Interface() { return this; }


int CSDL::Main(CSDL* iface, Ustring appname, int argc, char** argv)
{
  if (m_SDLP.iface == nullptr)
  {
    memset(&m_SDLP, 0, sizeof(SDLP));
    m_SDLP.iface = this;
    m_SDLP.appname = appname;
    SDLP_CLI_ENTRIES = 0;
  }
  return 0;
}

int CSDL::Init(Uint32 flags)
{
  m_SDLP_init = SDL_Init(flags);
  if (m_SDLP_init == 0)
    m_SDLP.flags = flags;
  return m_SDLP_init;
}

void CSDL::Quit()
{
  return SDL_Quit();
}

int CSDL::InitSubSystem(Uint32 flags)
{
  int result = SDL_InitSubSystem(flags);
  if (result == 0)
    BITMASK_PUT(m_SDLP.flags, flags);
  return result;
}

void CSDL::QuitSubSystem(Uint32 flags)
{
  if (m_SDLP_init == 0)
  {
    SDL_QuitSubSystem(flags);
    BITMASK_CLEAR(m_SDLP.flags, flags);
  }
}


bool CSDL::onQuitEvent(CSDL* iface, CSDL_Window* window) { return true; }


Ustring CSDL::AppName()
{
  return m_SDLP.appname;
}


bool CSDL::CLI_Accept(Ustring parameter, SDLP_CLI_TYPE type)
{
  if ((type != CLI_ERROR) && (parameter != nullptr))
  {
    SDLP_CLI_ENTRY** newEntry = &SDLP_CLI_TABLE;
    while (*newEntry)
      newEntry = &(*newEntry)->next;

    *newEntry = new SDLP_CLI_ENTRY;
    if (*newEntry)
    {
      SDLP_CLI_ENTRIES++;
      (*newEntry)->parameter = parameter;
      (*newEntry)->type      = type;
      (*newEntry)->index     = SDLP_CLI_ENTRIES;
      (*newEntry)->next      = nullptr;
      return true;
    }
  }
  return false;
}

bool CSDL::CLI_Process
 (int argc, char** argv, bool (fnProcessor)(int argc, Ustring argv, Ustring next_argv))
{
  if (fnProcessor != nullptr)
  {
    bool result = false;
    for (int i = 0; i < argc; i++)
    {
      result = ((fnProcessor)(i, argv[i], (i+1 < argc ? argv[i+1] : nullptr)));
      if (!result)
        return false;
    }
  }
  return false;
}

// TODO: CSDL::CLI_Process: Implement parameter type detection and error handling
bool CSDL::CLI_Process
 (int argc, char** argv,
  bool (fnProcessor)(int argc, Ustring parameter, SDLP_CLI_TYPE type, Ustring nextArgV))
{
  if ((m_SDLP.iface != nullptr) && (SDLP_CLI_ENTRIES > 0) && (fnProcessor != nullptr) && (argc >= 1))
  {
    bool was_found = false;
    for (int i = 1; i <= argc; i++)
    {
      SDLP_CLI_ENTRY** entry = &SDLP_CLI_TABLE;
      while (*entry)
      {
        if (strcmp((*entry)->parameter, argv[i]) == 0)
        {
          was_found = true;
          bool result = ((fnProcessor)(i, (*entry)->parameter, (*entry)->type, argv[i+1]));
          if (!result)
            return false;
        }
        entry = &(*entry)->next;
      }
      if (!was_found)
      {
       // Error: Invalid parameter
        return false;
      }
    }
  }
  return false;
}





CSDL* SDLPAPI CSDL_GetInstance()
{
  return m_SDLP.iface;
}



#ifdef WINDOWS
// CommandLineArgvA is borrowed code from ReactOS at:
// https://github.com/reactos/reactos/blob/master/dll/win32/shell32/wine/shell32_main.c
// and modified for (A)scii equivalent of (W)ide character acceptance.
LPSTR* SDLPAPI CommandLineToArgvA(LPCSTR lpCmdline, int* numargs)
{
    DWORD argc;
    LPSTR  *argv;
    LPCSTR s;
    LPSTR d;
    LPSTR cmdline;
    int qcount,bcount;

    if(!numargs)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    if (*lpCmdline==0)
    {
        /* Return the path to the executable */
        DWORD len, deslen=MAX_PATH, size;

        size = sizeof(LPSTR)*2 + deslen*sizeof(char);
        for (;;)
        {
            if (!(argv = (LPSTR*) LocalAlloc(LMEM_FIXED, size))) return NULL;
            len = GetModuleFileNameA(0, (LPSTR)(argv+2), deslen);
            if (!len)
            {
                LocalFree(argv);
                return NULL;
            }
            if (len < deslen) break;
            deslen*=2;
            size = sizeof(LPSTR)*2 + deslen*sizeof(char);
            LocalFree( argv );
        }
        argv[0]=(LPSTR)(argv+2);
        argv[1]=NULL;
        *numargs=1;

        return argv;
    }

    /* --- First count the arguments */
    argc=1;
    s=lpCmdline;
    /* The first argument, the executable path, follows special rules */
    if (*s=='"')
    {
        /* The executable path ends at the next quote, no matter what */
        s++;
        while (*s)
            if (*s++=='"')
                break;
    }
    else
    {
        /* The executable path ends at the next space, no matter what */
        while (*s && *s!=' ' && *s!='\t')
            s++;
    }
    /* skip to the first argument, if any */
    while (*s==' ' || *s=='\t')
        s++;
    if (*s)
        argc++;

    /* Analyze the remaining arguments */
    qcount=bcount=0;
    while (*s)
    {
        if ((*s==' ' || *s=='\t') && qcount==0)
        {
            /* skip to the next argument and count it if any */
            while (*s==' ' || *s=='\t')
                s++;
            if (*s)
                argc++;
            bcount=0;
        }
        else if (*s=='\\')
        {
            /* '\', count them */
            bcount++;
            s++;
        }
        else if (*s=='"')
        {
            /* '"' */
            if ((bcount & 1)==0)
                qcount++; /* unescaped '"' */
            s++;
            bcount=0;
            /* consecutive quotes, see comment in copying code below */
            while (*s=='"')
            {
                qcount++;
                s++;
            }
            qcount=qcount % 3;
            if (qcount==2)
                qcount=0;
        }
        else
        {
            /* a regular character */
            bcount=0;
            s++;
        }
    }

    /* Allocate in a single lump, the string array, and the strings that go
     * with it. This way the caller can make a single LocalFree() call to free
     * both, as per MSDN.
     */
    argv= (LPSTR*) LocalAlloc(LMEM_FIXED, (argc+1)*sizeof(LPSTR)+(strlen(lpCmdline)+1)*sizeof(char));
    if (!argv)
        return NULL;
    cmdline=(LPSTR)(argv+argc+1);
    strcpy(cmdline, lpCmdline);

    /* --- Then split and copy the arguments */
    argv[0]=d=cmdline;
    argc=1;
    /* The first argument, the executable path, follows special rules */
    if (*d=='"')
    {
        /* The executable path ends at the next quote, no matter what */
        s=d+1;
        while (*s)
        {
            if (*s=='"')
            {
                s++;
                break;
            }
            *d++=*s++;
        }
    }
    else
    {
        /* The executable path ends at the next space, no matter what */
        while (*d && *d!=' ' && *d!='\t')
            d++;
        s=d;
        if (*s)
            s++;
    }
    /* close the executable path */
    *d++=0;
    /* skip to the first argument and initialize it if any */
    while (*s==' ' || *s=='\t')
        s++;
    if (!*s)
    {
        /* There are no parameters so we are all done */
        argv[argc]=NULL;
        *numargs=argc;
        return argv;
    }

    /* Split and copy the remaining arguments */
    argv[argc++]=d;
    qcount=bcount=0;
    while (*s)
    {
        if ((*s==' ' || *s=='\t') && qcount==0)
        {
            /* close the argument */
            *d++=0;
            bcount=0;

            /* skip to the next one and initialize it if any */
            do {
                s++;
            } while (*s==' ' || *s=='\t');
            if (*s)
                argv[argc++]=d;
        }
        else if (*s=='\\')
        {
            *d++=*s++;
            bcount++;
        }
        else if (*s=='"')
        {
            if ((bcount & 1)==0)
            {
                /* Preceded by an even number of '\', this is half that
                 * number of '\', plus a quote which we erase.
                 */
                d-=bcount/2;
                qcount++;
            }
            else
            {
                /* Preceded by an odd number of '\', this is half that
                 * number of '\' followed by a '"'
                 */
                d=d-bcount/2-1;
                *d++='"';
            }
            s++;
            bcount=0;
            /* Now count the number of consecutive quotes. Note that qcount
             * already takes into account the opening quote if any, as well as
             * the quote that lead us here.
             */
            while (*s=='"')
            {
                if (++qcount==3)
                {
                    *d++='"';
                    qcount=0;
                }
                s++;
            }
            if (qcount==2)
                qcount=0;
        }
        else
        {
            /* a regular character */
            *d++=*s++;
            bcount=0;
        }
    }
    *d='\0';
    argv[argc]=NULL;
    *numargs=argc;

    return argv;
}
#endif // WINDOWS
