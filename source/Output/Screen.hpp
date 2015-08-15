#pragma once

#include <SDL.h>

class Screen{
	const char* _title;

	int _w, _h;
	int _x, _y;

	float _rOff, _gOff, _bOff;
	float _rOn, _gOn, _bOn;

	SDL_Window* _window;
	SDL_Surface* _screen;

public:
	Screen();
	~Screen();

	void setTitle(const char* title);
	void setSize(int width, int height);
	void setPixels(int width, int height);
	void setColour(int rOff, int gOff, int bOff, int rOn, int gOn, int bOn);

	bool initiate();

	void drawPixel(int x, int y, bool fill = true);
	void drawSurface(int x, int y, SDL_Surface* surface);

	void render();
};