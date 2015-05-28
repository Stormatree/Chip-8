#include <stdio.h>
#include "Screen.hpp"

Screen::Screen(){
	_title = "Chip-8 Emulator";

	_w = 1024;
	_h = 512;

	_x = 64;
	_y = 32;
}

Screen::~Screen(){
	SDL_FreeSurface(_screen);
	SDL_DestroyWindow(_window);
}

void Screen::title(const char* title){
	_title = title;
}

void Screen::size(int width, int height){
	_w = width;
	_h = height;
}

void Screen::pixels(int width, int height){
	_x = width;
	_y = height;
}

bool Screen::initiate(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", SDL_GetError());
		return false;
	}

	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!_window){
		printf("%s! %s: %s\n", "Failed to create window", "SDL Error", SDL_GetError());
		return false;
	}

	_screen = SDL_GetWindowSurface(_window);

	return true;
}

void Screen::drawPixel(int x, int y, bool fill){
	SDL_Rect pixel = {
		x * (_w / _x),
		y * (_h / _y),
		(_w / _x),
		(_h / _y)
	};

	if (fill){
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, 255, 255, 255));
	}
	else{
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, 0, 0, 0));
	}
}

void Screen::drawSurface(int x, int y, SDL_Surface* surface){
	SDL_Rect dest = { x, y, surface->w, surface->h };
	SDL_BlitSurface(surface, 0, _screen, &dest);
}

void Screen::render(){
	SDL_UpdateWindowSurface(_window);
	SDL_FillRect(_screen, 0, 0);
}