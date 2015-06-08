#include "Render/Screen.hpp"
#include "Chip8/Interpreter.hpp"

#undef main

int main(int argc, char* argv[]){
	Interpreter interpreter;

	Screen screen;
	screen.initiate();

	if (interpreter.load("../asset/game/TETRIS"))
		interpreter.print();

	bool running = true;
	SDL_Event e;

	while (running){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		interpreter.input(0x0000);
		interpreter.update();
		interpreter.render(screen);

		screen.render();
	}

	return 0;
}