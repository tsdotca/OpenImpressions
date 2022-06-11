#include <cstdio>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

const int kScreenWidth = 640;
const int kScreenHeight = 480;
const char *kScreenWindowTitle = "OpenImpressions Engine Test";

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
    printf("error: SDL could not init: %s\n", SDL_GetError());
    return 1;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    fprintf(stderr, "error: SDL_image could not init: %s\n", IMG_GetError());
    return 1;
  }

  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
    fprintf(stderr, "error: SDL_mixer could not init: %s\n", Mix_GetError());
    return 1;
  }
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
    fprintf(stderr, "error: Mix_OpenAudio failed: %s\n", Mix_GetError());
    return 1;
  }
  Mix_AllocateChannels(16); // docs say we segfault if it fails 🙃

  SDL_Window *window = SDL_CreateWindow(
      kScreenWindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    fprintf(stderr, "error: window could not be created: %s\n", SDL_GetError());
    return 1;
  }

  // For some reason, SetWindowIcon doesn't always take effect.
  SDL_Surface *window_icon = IMG_Load("gfx/hand_logo.png");
  if (window_icon == nullptr) {
    fprintf(stderr, "error: can't get window icon: %s\n", IMG_GetError());
  } else {
    SDL_SetWindowIcon(window, window_icon);
    SDL_FreeSurface(window_icon);
  }

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);
  const auto screen_fill_colour =
      SDL_MapRGB(window_surface->format, 0x69, 0xFF, 0x69);

  bool keep_going = true;
  SDL_Event ev;

  while (keep_going) {
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
        keep_going = false;
      case SDL_WINDOWEVENT:
        if (ev.window.event == SDL_WINDOWEVENT_CLOSE &&
            ev.window.windowID == SDL_GetWindowID(window)) {
          keep_going = false;
        }
      }
    }

    if (!keep_going)
      break;

    SDL_FillRect(window_surface, nullptr, screen_fill_colour);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(15); // 15 => ~64hz refresh
  }

  SDL_DestroyWindow(window);
  Mix_CloseAudio();

  Mix_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
}