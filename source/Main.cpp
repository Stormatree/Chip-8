#include <stdio.h>
#include "Screen.hpp"
#include "Console.hpp"

void face(Screen& screen);

#undef main

int main(int argc, char* argv[]){
	printf("Hello World!\n");

	Screen screen;
	Console console;

	bool running = screen.initiate();
	running = console.initiate();
	
	while (running){
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		face(screen);

		console.print("Hello World!", 0);

		console.render(&screen);
		screen.render();
	}

	return 0;
}

void face(Screen& screen){
	screen.drawPixel(1, 1, true);

	screen.drawPixel(1, 4, true);
	screen.drawPixel(2, 5, true);
	screen.drawPixel(3, 5, true);
	screen.drawPixel(4, 5, true);
	screen.drawPixel(5, 4, true);

	screen.drawPixel(5, 1, true);

	screen.drawPixel(7, 1, true);
	screen.drawPixel(7, 2, true);
	screen.drawPixel(7, 3, true);
	screen.drawPixel(7, 4, true);
	screen.drawPixel(7, 5, true);

	screen.drawPixel(8, 3, true);
	screen.drawPixel(9, 3, true);

	screen.drawPixel(10, 1, true);
	screen.drawPixel(10, 2, true);
	screen.drawPixel(10, 3, true);
	screen.drawPixel(10, 4, true);
	screen.drawPixel(10, 5, true);

	screen.drawPixel(12, 1, true);

	screen.drawPixel(12, 3, true);
	screen.drawPixel(12, 4, true);
	screen.drawPixel(12, 5, true);
}