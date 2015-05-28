#pragma once

#include <unordered_map>
#include <SDL_ttf.h>
#include <string>
#include "Screen.hpp"

class Console{
	typedef std::unordered_map<int, SDL_Surface*> SurfaceMap;

	std::unordered_map<int, SDL_Surface*> _text;
	TTF_Font* _font;
	int _size;

	const char* _file;

	int _padding;

	int _bottomLine;

public:
	Console();
	~Console();

	void font(const char* file);
	void size(int size);
	void padding(int padding);

	bool initiate();

	void print(const char* text, int line, float r = 0, float g = 1, float b = .5);

	void render(Screen* screen);
};