#include <stdio.h>
#include <math.h>
#include "Screen.hpp"

Screen::Screen(){
	_title = "Chip-8 Emulator";

	_windowWidth = 1024;
	_windowHeight = 512;

	_resolutionX = 64;
	_resolutionY = 32;

	_rOff = 0.f;
	_gOff = 0.f;
	_bOff = 0.f;

	_rOn = 1.f;
	_gOn = 1.f;
	_bOn = 1.f;
}

Screen::~Screen(){
	SDL_FreeSurface(_screen);
	SDL_DestroyWindow(_window);
}

void Screen::setTitle(const char* title){
	_title = title;
	SDL_SetWindowTitle(_window, title);
}

void Screen::setSize(int width, int height){
	_windowWidth = width;
	_windowHeight = height;

	initiate();
}

void Screen::setPixels(int width, int height){
	_resolutionX = width;
	_resolutionY = height;
}

void Screen::setColour(int rOff, int gOff, int bOff, int rOn, int gOn, int bOn){
	_rOff = rOff / (float)255;
	_gOff = gOff / (float)255;
	_bOff = bOff / (float)255;

	_rOn = rOn / (float)255;
	_gOn = gOn / (float)255;
	_bOn = bOn / (float)255;
}

bool Screen::initiate(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
#ifdef _DEBUG
		printf("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", SDL_GetError());
#endif
		return false;
	}
	
	// Destroy screen / window if running
	if (_screen)
		SDL_FreeSurface(_screen);

	if (_window)
		SDL_DestroyWindow(_window);

	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN);

	if (!_window){
#ifdef _DEBUG
		printf("%s! %s: %s\n", "Failed to create window", "SDL Error", SDL_GetError());
#endif
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
		x * (_windowWidth / _resolutionX),
		y * (_windowHeight / _resolutionY),
		(_windowWidth / _resolutionX),
		(_windowHeight / _resolutionY)
	};

	// Draw rect as pixel
	if (fill)
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, (int)round(_rOn * 255), (int)round(_gOn * 255), (int)round(_bOn * 255)));
	else
		SDL_FillRect(_screen, &pixel, SDL_MapRGB(_screen->format, (int)round(_rOff * 255), (int)round(_gOff * 255), (int)round(_bOff * 255)));
}