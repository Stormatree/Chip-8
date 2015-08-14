#include <stdio.h>
#include <math.h>
#include "Screen.hpp"

Screen::Screen(){
	setTitle("Chip-8 Emulator");
	setSize(1024, 512);
	setPixels(64, 32);
	setColour(0.f, 0.f, 0.f, 1.f, 1.f, 1.f);
}

Screen::~Screen(){
	SDL_FreeSurface(_screen);
	SDL_DestroyWindow(_window);
}

void Screen::setTitle(const char* title){
	_title = title;
}

void Screen::setSize(int width, int height){
	_w = width;
	_h = height;
}

void Screen::setPixels(int width, int height){
	_x = width;
	_y = height;
}

void Screen::setColour(float rOff, float gOff, float bOff, float rOn, float gOn, float bOn){
	_rOff = rOff;
	_gOff = gOff;
	_bOff = bOff;

	_rOn = rOn;
	_gOn = gOn;
	_bOn = bOn;
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

	render();

	return true;
}

void Screen::render(){
	SDL_UpdateWindowSurface(_window);
	SDL_FillRect(_screen, 0, SDL_MapRGB(_screen->format, (int)round(_rOff * 255), (int)round(_gOff * 255), (int)round(_bOff * 255)));
}

void Screen::drawPixel(int x, int y, bool fill){
	SDL_Rect pixel = {
		x * (_w / _x),
		y * (_h / _y),
		(_w / _x),
		(_h / _y)
	};

	if (fill)
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, (int)round(_rOn * 255), (int)round(_gOn * 255), (int)round(_bOn * 255)));
	else
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, (int)round(_rOff * 255), (int)round(_gOff * 255), (int)round(_bOff * 255)));
}

void Screen::drawSurface(int x, int y, SDL_Surface* surface){
	SDL_Rect dest = { x, y, surface->w, surface->h };
	SDL_BlitSurface(surface, 0, _screen, &dest);
}