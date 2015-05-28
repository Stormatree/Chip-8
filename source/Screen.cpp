#include <stdio.h>
#include <math.h>
#include "Screen.hpp"

Screen::Screen(){
	_title = "Chip-8 Emulator";

	size(1024, 512);

	pixels(64, 32);

	offColour(0.f, 0.f, 0.f);
	onColour(1.f, 1.f, 1.f);
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

void Screen::onColour(float r, float g, float b){
	_rOn = r;
	_gOn = g;
	_bOn = b;
}

void Screen::offColour(float r, float g, float b){
	_rOff = r;
	_gOff = g;
	_bOff = b;
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
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, (int)round(_rOn * 255), (int)round(_gOn * 255), (int)round(_bOn * 255)));
	}
	else{
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, (int)round(_rOff * 255), (int)round(_gOff * 255), (int)round(_bOff * 255)));
	}
}

void Screen::drawSurface(int x, int y, SDL_Surface* surface){
	SDL_Rect dest = { x, y, surface->w, surface->h };
	SDL_BlitSurface(surface, 0, _screen, &dest);
}

void Screen::render(){
	SDL_UpdateWindowSurface(_window);
	SDL_FillRect(_screen, 0, SDL_MapRGB(_screen->format, (int)round(_rOff * 255), (int)round(_gOff * 255), (int)round(_bOff * 255)));
}