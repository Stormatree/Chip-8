#pragma once

#include <SDL.h>

class Screen{
	const char* _title;

	int _w;
	int _h;

	int _x;
	int _y;

	SDL_Window* _window;
	SDL_Surface* _screen;

public:
	Screen();
	~Screen();

	void title(const char* title);
	void size(int width, int height);
	void pixels(int width, int height);

	bool initiate();

	void drawPixel(int x, int y, bool fill);

	void drawSurface(int x, int y, SDL_Surface* surface);

	void render();
};