#pragma once

#include <SDL.h>

class Screen{
	const char* _title;

	int _windowWidth, _windowHeight;
	int _resolutionX, _resolutionY;

	// Pixel off colour
	float _rOff, _gOff, _bOff;
	// Pixel on colour
	float _rOn, _gOn, _bOn;

	SDL_Window* _window = 0;
	SDL_Surface* _screen = 0;

public:
	Screen();
	~Screen();

	// Setters
	void setTitle(const char* title);
	void setSize(int width, int height);
	void setPixels(int width, int height);
	void setColour(int rOff, int gOff, int bOff, int rOn, int gOn, int bOn);

	// Initiate SDL and open window
	bool initiate();

	// Draw pixel at X Y
	void drawPixel(int x, int y, bool fill = true);

	// Flip and clear buffer
	void render();
};