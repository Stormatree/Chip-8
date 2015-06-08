#include "Screen.hpp"
#include "Interpreter.hpp"
#include "Font.hpp"

#undef main

int main(int argc, char* argv[]){
	printf("Chip-8 Emulator\n---------------\n");

	Interpreter interpreter;
	if (interpreter.load("../asset/game/TETRIS"))
		interpreter.print();

	printf("\n");

	Screen screen;
	screen.initiate();

	bool running = true;
	SDL_Event e;

	while (running){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		interpreter.input(0x0000);
		interpreter.execute();
		interpreter.render(screen);

		screen.render();
	}

	return 0;
}