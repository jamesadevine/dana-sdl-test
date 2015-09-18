#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_syswm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <pthread.h>
#include <semaphore.h>

typedef int bool;
#define true 1
#define false 0

static unsigned int DX_NEW_WINDOW_EVENT = 0;
static unsigned int DX_SWAP_BUFFERS_EVENT = 0;
static unsigned int DX_SET_WINDOW_POSITION = 0;
static unsigned int DX_SET_WINDOW_TITLE = 0;
static unsigned int DX_MAXIMISE_WINDOW = 0;
static unsigned int DX_MINIMISE_WINDOW = 0;
static unsigned int DX_SHOW_WINDOW = 0;
static unsigned int DX_HIDE_WINDOW = 0;
static unsigned int DX_CLOSE_WINDOW = 0;
static unsigned int DX_GENERATE_TEXT_BITMAP = 0;
static unsigned int DX_GENERATE_BITMAP_SURFACE = 0;
static unsigned int DX_LOAD_FONT = 0;
static unsigned int DX_GET_TEXT_WIDTH = 0;

size_t windowX = 0;
size_t windowY = 0;

size_t windowWidth = 200;
size_t windowHeight = 200;

NSWindow *windowHandle;

int main(){

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_Window* win = SDL_CreateWindow( "SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN );
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

  printf("HERE\n");

  SDL_SetRenderDrawColor(renderer, 255, 240, 240, 100);
  SDL_Rect r;
  r.x = 10;
  r.y = windowHeight - 43;
  r.w = 300;
  r.h = 40;
  SDL_RenderFillRect(renderer, &r);

  SDL_SetRenderTarget(renderer, NULL);

  if(SDL_GetWindowWMInfo(win, &info)) {
    switch(info.subsystem) {
        case SDL_SYSWM_UNKNOWN:   break;
        #ifdef WINDOWS
        case SDL_SYSWM_WINDOWS:   windowHandle = info.info.win.window;
                      break;
        #endif
        #ifdef OSX
        case SDL_SYSWM_COCOA:		windowHandle = info.info.cocoa.window;
                      break;
        #else
        #ifdef LINUX
        case SDL_SYSWM_X11:       windowHandle = info.info.x11.window;
                      //myInstance -> displayHandle = info.info.x11.display;
                      break;
        #endif
        #endif
        case SDL_SYSWM_DIRECTFB:
                      break;
        case SDL_SYSWM_UIKIT:
                      break;
        default: break;
      }
    }
  printf("HERE2\n");
  DX_NEW_WINDOW_EVENT = SDL_RegisterEvents(1);
  DX_SWAP_BUFFERS_EVENT = SDL_RegisterEvents(1);
  DX_SET_WINDOW_POSITION = SDL_RegisterEvents(1);
  DX_SET_WINDOW_TITLE = SDL_RegisterEvents(1);
  DX_MAXIMISE_WINDOW = SDL_RegisterEvents(1);
  DX_MINIMISE_WINDOW = SDL_RegisterEvents(1);
  DX_SHOW_WINDOW = SDL_RegisterEvents(1);
  DX_HIDE_WINDOW = SDL_RegisterEvents(1);
  DX_CLOSE_WINDOW = SDL_RegisterEvents(1);
  DX_GENERATE_TEXT_BITMAP = SDL_RegisterEvents(1);
  DX_GENERATE_BITMAP_SURFACE = SDL_RegisterEvents(1);
  DX_LOAD_FONT = SDL_RegisterEvents(1);
  DX_GET_TEXT_WIDTH = SDL_RegisterEvents(1);

  SDL_Event e;

  bool quit = false;

  printf("HERE3\n");

  SDL_Surface* screenSurface;

  screenSurface = SDL_GetWindowSurface(win);

  //Fill the surface white
  //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

  while(!quit){
    if (SDL_WaitEvent(&e)){
      do{
        printf("%d\n",e.type);
        if(e.type == SDL_QUIT)
          quit = true;
      } while(SDL_PollEvent(&e)); //power through all other events to clear the queue
    }
  }
  SDL_Quit();
}
