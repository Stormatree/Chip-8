#include "Console.hpp"

Console::Console(){
	_file = "../asset/04b03.ttf";
	_size = 8;
	_padding = 2;
	_bottomLine = 0;
}

Console::~Console(){
	for (SurfaceMap::iterator i = _text.begin(); i != _text.end(); i++){
		SDL_FreeSurface(i->second);
	}

	TTF_CloseFont(_font);
}

void Console::font(const char* file){
	std::string path = "../asset/";

	_file = (path + file).c_str();
}

void Console::size(int size){
	_size = size;
}

void Console::padding(int padding){
	_padding = padding;
}

bool Console::initiate(){
	TTF_Init();

	_font = TTF_OpenFont(_file, _size);

	if (!_font){
		printf("%s! %s: %s\n", "Failed to load font", "SDL Error", SDL_GetError());
		return false;
	}

	return true;
}

void Console::print(const char* text, int line, float r, float g , float b){
	SDL_Color colour = { (int)round(r * 255), (int)round(g * 255), (int)round(b * 255), 1 };
	SDL_Surface* surface = TTF_RenderText_Solid(_font, text, colour);

	if (!_text[line]){
		_text[line] = surface;
	}
	else{
		SDL_FreeSurface(_text[line]);
		_text[line] = surface;
	}
}

void Console::render(Screen* screen){
	for (SurfaceMap::iterator i = _text.begin(); i != _text.end(); i++){
		screen->drawSurface(_padding, i->first * _size + _padding, i->second);
	}
}