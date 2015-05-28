#include <stdio.h>
#include <time.h>
#include "Screen.hpp"
#include "Console.hpp"

void pixels(Screen& screen, int x = 0, int y = 0);
void text(Console& console, int y = 0);

#undef main

int main(int argc, char* argv[]){
	printf("Chip-8 Emulator\n---------------\n");

	Screen screen;
	//screen.offColour(0.f, .15f, .05f);
	//screen.onColour(.1f, .75f, .25f);

	Console console;
	//console.font("perfect.ttf");
	//console.size(16);

	SDL_Event e;
	bool running;
		
	running = screen.initiate();
	running = console.initiate();

	text(console, 0);
	
	while (running){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		pixels(screen, 25, 12);

		console.drawTo(screen);

		screen.render();
	}

	return 0;
}

void text(Console& console, int y){
	console.print("60 FPS 22ms", 0 + y, 0.f, 1.f, 0.f);
	console.print("Game Started", 1 + y, 1.f, 1.f, 1.f, 5000);
	console.print("Fake Warning", 2 + y, 1.f, 0.f, 0.f, 2500);
}

void pixels(Screen& screen, int x, int y){
	screen.drawPixel(0 + x, 0 + y);

	screen.drawPixel(0 + x, 3 + y);
	screen.drawPixel(1 + x, 4 + y);
	screen.drawPixel(2 + x, 4 + y);
	screen.drawPixel(3 + x, 4 + y);
	screen.drawPixel(4 + x, 3 + y);

	screen.drawPixel(4 + x, 0 + y);

	screen.drawPixel(6 + x, 0 + y);
	screen.drawPixel(6 + x, 1 + y);
	screen.drawPixel(6 + x, 2 + y);
	screen.drawPixel(6 + x, 3 + y);
	screen.drawPixel(6 + x, 4 + y);

	screen.drawPixel(7 + x, 2 + y);
	screen.drawPixel(8 + x, 2 + y);

	screen.drawPixel(9 + x, 0 + y);
	screen.drawPixel(9 + x, 1 + y);
	screen.drawPixel(9 + x, 2 + y);
	screen.drawPixel(9 + x, 3 + y);
	screen.drawPixel(9 + x, 4 + y);

	screen.drawPixel(11 + x, 0 + y);

	screen.drawPixel(11 + x, 2 + y);
	screen.drawPixel(11 + x, 3 + y);
	screen.drawPixel(11 + x, 4 + y);
}