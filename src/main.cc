#include <cstdio>

#include "SDL.h"
#include "SDL_image.h"

const int kScreenWidth = 640;
const int kScreenHeight = 480;

int main(int argc, char **argv)
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("error: SDL could not init: %s\n", SDL_GetError());
		return 1;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("error: SDL_Image could not init: %s\n", IMG_GetError());
		return 1;
	}

	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		printf("error: window could not be created: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface* window_icon = IMG_Load("gfx/hand_logo.png");
	if (!window_icon) {
		printf("error: can't get window icon: %s", IMG_GetError());
	}
	else {
		SDL_SetWindowIcon(window, window_icon);
	}

	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

	if (window_icon) {
		SDL_FreeSurface(window_icon);
	}
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}