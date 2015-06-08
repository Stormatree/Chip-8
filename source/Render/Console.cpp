#include "Console.hpp"

#include <utility>

Uint32 Console::callback(Uint32 interval, void* param){
	((std::pair<Console*, int>*)param)->first->clear(((std::pair<Console*, int>*)param)->second);

	delete param;

	return 0;
}

Console::Console(){
	font("04b03.ttf");;
	size(8);
	padding(2);
}

Console::~Console(){
	for (SurfaceMap::iterator i = _text.begin(); i != _text.end(); i++){
		SDL_FreeSurface(i->second);
	}

	TTF_CloseFont(_font);
}

void Console::font(std::string file){
	_file = "../asset/" + file;
}

void Console::size(int size){
	_size = size;
}

void Console::padding(int padding){
	_padding = padding;
}

bool Console::initiate(){
	TTF_Init();

	_font = TTF_OpenFont(_file.c_str(), _size);

	if (!_font){
		printf("%s! %s: %s\n", "Failed to load font", "SDL Error", SDL_GetError());
		return false;
	}

	SDL_Init(SDL_INIT_TIMER);

	return true;
}

void Console::print(std::string text, int line, float r, float g, float b, int time){
	SDL_Color colour = { (int)round(r * 255), (int)round(g * 255), (int)round(b * 255), 1 };
	SDL_Surface* surface = TTF_RenderText_Solid(_font, text.c_str(), colour);

	if (line == -1){
		//_text[_firstAvLine()] = surface;
	}
	else if (!_text[line]){
		_text[line] = surface;
	}
	else{
		SDL_FreeSurface(_text[line]);
		_text[line] = surface;
	}

	if (time){
		std::pair<Console*, int>* data = new std::pair<Console*, int>({ this, line });
		SDL_AddTimer(time, Console::callback, data);
	}
}

void Console::clear(int line){
	if (_text[line]){
		SDL_FreeSurface(_text[line]);
		_text.erase(line);
	}
}

void Console::purge(){
	for (SurfaceMap::iterator i = _text.begin(); i != _text.end(); i++){
		SDL_FreeSurface(i->second);
	}

	_text.clear();
}

void Console::drawTo(Screen& screen){
	for (SurfaceMap::iterator i = _text.begin(); i != _text.end(); i++){
		screen.drawSurface(_padding, i->first * _size + _padding, i->second);
	}
}