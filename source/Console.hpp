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

	std::string _file;

	int _padding;

public:
	Console();
	~Console();

	void font(std::string file);
	void size(int size);
	void padding(int padding);

	bool initiate();

	void print(std::string text, int line, float r = 1.f, float g = 1.f, float b = 1.f, int time = 0);
	void clear(int line);

	static Uint32 callback(Uint32 interval, void* param);

	void purge();

	void drawTo(Screen& screen);
};