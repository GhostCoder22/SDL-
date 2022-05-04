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
 *  \file SDLP_Video.hpp
 *
 *  SDL+ Video Subsystem C++ header
 */

#ifdef __cplusplus
#ifndef SDLP_VIDEO_HPP
#define SDLP_VIDEO_HPP

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_vulkan.h>

#include <SDL_plus/SDLP_defines.hpp>
#include <SDL_plus/SDLP_Video.hpp>

#include <SDL2/begin_code.h>
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

class CSDL_Window;

typedef struct SDL_Size
{
    int  width,height;
} SDL_Size;

typedef struct SDL_Position
{
    int  x,y;
} SDL_Position;

typedef struct SDL_BordersSize
{
    int  top,left;
    int  bottom,right;
} SDL_BordersSize;

typedef struct SDL_GammaRamp
{
    Uint16  red,green,blue;
} SDL_GammaRamp;


typedef struct SDL_DisplayDPI
{
    int    index;
    float  ddpi,hdpi,vdpi;
} SDL_DisplayDPI;


typedef int (*SDLP_DisplayModeWalker_t)(int displayIndex, SDL_DisplayMode* mode, const char* displayName);
typedef int (*SDLP_WalkAllDisplayBounds_t)(int driverIndex, SDL_Rect* boundingRect);
typedef int (*SDLP_VideoDriverWalker_t)(int driverIndex, const char* driverName);

class SDLPAPI CSDL_Video
{
  public:
    CSDL_Video();
    ~CSDL_Video();
    CSDL_Video* Interface();

    int WalkDisplayModes(SDLP_DisplayModeWalker_t walker);

    int         WalkVideoDrivers(SDLP_VideoDriverWalker_t walker);
    const char* GetCurrentVideoDriver();
    const char* GetVideoDriver(int index);
    int         GetNumVideoDrivers();

    const char* GetDisplayName(int displayIndex);

    int              GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode *mode);
    int              GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode *mode);
    int              GetDisplayBounds(int displayIndex, SDL_Rect *rect);
    int              GetDisplayUsableBounds(int displayIndex, SDL_Rect *rect);
    int              WalkAllDisplayBounds(SDLP_WalkAllDisplayBounds_t procedure);
    int              GetNumVideoDisplays();
    int              GetNumDisplayModes(int displayIndex);
    int              GetDisplayMode(int displayIndex, int modeIndex, SDL_DisplayMode *mode);
    SDL_DisplayMode* GetClosestDisplayMode(int displayIndex, const SDL_DisplayMode * mode, SDL_DisplayMode * closest);
    int              GetDisplayDPI(int displayIndex, float * ddpi, float * hdpi, float * vdpi);
};


class SDLPAPI CSDL_Surface
{
  public:
    CSDL_Surface();
    ~CSDL_Surface();
    CSDL_Surface* Interface();

    SDL_Surface* Create();
    SDL_Surface* Handle();
    SDL_Surface* GetFromWindow(CSDL_Window* window);
    CSDL_Window* FromWindow();

    int SetBlendMode(SDL_BlendMode *blendMode);
    int GetBlendMode(SDL_BlendMode *blendMode);

  private:
    SDL_Surface* m_SDL_Surface;
    CSDL_Window* m_SDLP_Window;
};


class SDLPAPI CSDL_Renderer
{
  public:
    CSDL_Renderer();
    ~CSDL_Renderer();
    CSDL_Renderer* Interface();

    SDL_Renderer* Create(CSDL_Window* window, int index, Uint32 flags);
    SDL_Renderer* Handle();

  private:
    SDL_Renderer* m_SDL_Renderer;
};


class SDLPAPI CSDL_Window: public CSDL_Surface
{
  public:
    CSDL_Window();
    ~CSDL_Window();
    CSDL_Window* Interface();

    SDL_Window* Create(const char* title, int x, int y, int w, int h, Uint32 flags);
    SDL_Window* CreateWithRenderer(const char* title, int width, int height, Uint32 window_flags, CSDL_Renderer* renderer);
    SDL_Window* CreateFrom(const void *data);
    void        Destroy();
    SDL_Window* Handle();

    bool IsVisible_OpenGL();
    bool IsVisible_Vulkan();

    CSDL_Surface* GetSurface();
    int           UpdateSurface();
    int           UpdateSurfaceRects(const SDL_Rect *rects, int numrects);

    void          SetTitle(const char* title);
    const char*   GetTitle();
    void          SetIcon(CSDL_Surface* surface);
    CSDL_Surface* GetIcon();

    bool SetGrab(bool grabbed);
    bool GetGrab();
    bool IsGrabbed();
    int  SetInputFocus();
    bool HasInputFocus();

    int SetDisplayMode(const SDL_DisplayMode *mode);
    int GetDisplayMode(SDL_DisplayMode *mode);
    int SetFullscreenMode(Uint32 flags);
    int GetFullscreenMode();

    void DisableScreenSaver();
    void EnableScreenSaver();
    bool IsScreenSaverEnabled();

    void Show();
    bool IsShown();
    void Raise();
    void Hide();
    void Maximize();
    void Minimize();
    void Restore();

    void     SetSize(int w, int h);
    void     SetSize(SDL_Size* ws);
    void     GetSize(int *w, int *h);
    void     GetSize(SDL_Size* ws);
    void     SetResizable(SDL_bool resizable);
    SDL_bool GetResizable();
    void     SetMaximumSize(int max_w, int max_h);
    void     SetMaximumSize(SDL_Size *size);
    void     GetMaximumSize(int *max_w, int *max_h);
    void     GetMaximumSize(SDL_Size *size);
    void     SetMinimumSize(int min_w, int min_h);
    void     SetMinimumSize(SDL_Size *size);
    void     GetMinimumSize(int *min_w, int *min_h);
    void     GetMinimumSize(SDL_Size *size);
    int      GetBordersSize(int *top, int *left, int *bottom, int *right);
    int      GetBordersSize(SDL_BordersSize* wbs);
    bool     IsBorderless();
    void     SetPosition(int x, int y);
    void     SetPosition(SDL_Position *position);
    void     GetPosition(int *x, int *y);
    void     GetPosition(SDL_Position *position);

    int SetGammaRamp(const Uint16 *red, const Uint16 *green, const Uint16 *blue);
    int SetGammaRamp(const SDL_GammaRamp *gammaramp);
    int GetGammaRamp(Uint16 *red, Uint16 *green, Uint16 *blue);
    int GetGammaRamp(SDL_GammaRamp *gammaramp);
    int SetOpacity(float *opacity);
    int GetOpacity(float *opacity);

    Uint32 GetPixelFormat();

    int Flash(SDL_FlashOperation operation);

    Uint32 GetID();
    int    GetDisplayIndex();

    SDL_bool    GetWindowWMInfo(SDL_SysWMinfo *info);
    const char* NameSubsystem();

    Uint32 GetFlags();
    void*  SetData(const char *name, void *userdata);
    void*  GetData(const char *name);
    int    SetHitTest(SDL_HitTest callback, void *callback_data);

   #if SDL_VERSION_ATLEAST(2,0,5)
    int          SetModelFor(CSDL_Window* model_window);
    CSDL_Window* GetModelFor();
   #endif


   // [Events]

    virtual bool onKeyDown(CSDL_Window* window, SDL_KeyboardEvent* event);
    virtual bool onKeyUp(CSDL_Window* window, SDL_KeyboardEvent* event);
    virtual bool onMouseButton(CSDL_Window* window, SDL_MouseButtonEvent* event);
    virtual bool onMouseMotion(CSDL_Window* window, SDL_MouseMotionEvent* event);
    virtual bool onMouseWheel(CSDL_Window* window, SDL_MouseWheelEvent* event);

  protected:
    SDL_Window* m_SDL_Window;
   #if SDL_VERSION_ATLEAST(2,0,5)
    CSDL_Window* m_CSDL_Window_model;
   #endif
    CSDL_Surface* m_SDLP_Icon;
    bool          m_hasInputFocus;
    int           m_fFullscreen;
};


class SDLPAPI CSDL_OpenGL
{
  public:
    CSDL_OpenGL();
    ~CSDL_OpenGL();
    CSDL_OpenGL* Interface();

    SDL_GLContext CreateContext(CSDL_Window* window);
    void          DeleteContext();
    SDL_GLContext GetCurrentContext();
    int           SetCurrentWindow(CSDL_Window* window);
    CSDL_Window*  GetCurrentWindow();
    int           MakeCurrent(CSDL_Window* window);

    int      LoadLibrary(const char* path);
    void     UnloadLibrary();
    SDL_bool ExtensionSupported(const char* extension);
    void*    GetProcAddress(const char* proc);

    void GetDrawableSize(int *w, int *h);
    void GetDrawableSize(SDL_Size* size);

    int  SetAttribute(SDL_GLattr attr, int value);
    int  GetAttribute(SDL_GLattr attr, int *value);
    void ResetAttributes();

    void SwapWindow(CSDL_Window* window);
    void SwapWindow();
    int  SetSwapInterval(int interval);
    int  GetSwapInterval();

  protected:
    SDL_GLContext m_SDL_GLContext;
};


class SDLPAPI CSDL_Vulkan
{
  public:
    CSDL_Vulkan();
    ~CSDL_Vulkan();
    CSDL_Vulkan* Interface();

    VkSurfaceKHR* CreateSurface(CSDL_Window* window, VkInstance instance);
    VkSurfaceKHR* GetSurface();
    VkInstance    GetInstance();

    int      LoadLibrary(const char* path);
    void*    GetInstanceProcAddr();
    SDL_bool GetInstanceExtensions(unsigned int *pCount, const char **pNames);
    void     UnloadLibrary();

    void GetDrawableSize(int *w, int *h);
    void GetDrawableSize(SDL_Size* size);

  protected:
    CSDL_Window* m_CSDL_Window;
    VkInstance   m_VkInstance;
    VkSurfaceKHR m_VkSurfaceKHR;
};



void         SDLPAPI SDLP_SetWindowGrab(CSDL_Window* window, SDL_bool grabWindow);
SDL_bool     SDLPAPI SDLP_GetWindowGrab(CSDL_Window* window);
CSDL_Window* SDLPAPI SDLP_GetGrabbedWindow();
CSDL_Window* SDLPAPI SDLP_GetWindowFromID(Uint32 id);


typedef struct SDLP_MessageBoxData
{
    Uint32                            flags;
    CSDL_Window*                      window;
    const char*                       title;
    const char*                       message;
    int                               numbuttons;
    const SDL_MessageBoxButtonData*   buttons;
    const SDL_MessageBoxColorScheme*  colorScheme;
} SDLP_MessageBoxData;

int SDLPAPI SDLP_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, int *buttonid);
int SDLPAPI SDLP_ShowSimpleMessageBox(Uint32 flags, const char *title, const char *message,
                                      CSDL_Window* window);

//#ifdef __cplusplus
}
//#endif
#include <SDL2/close_code.h>

#endif // SDLP_VIDEO_HPP
#endif // __cplusplus
