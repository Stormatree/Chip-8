#include "Output/Screen.hpp"
#include "Chip8/Core.hpp"
#include <iostream>

#define DEFUALT_ROM "../asset/rom/FA.rom"

#undef main

int main(int argc, char* argv[]){
	// Emulator setup and loading ROM
	Core emulator;

	// Loading from arg, if not, then default
	if (argc > 1 && emulator.load(argv[1]))
		emulator.print();
	else if (emulator.load(DEFUALT_ROM))
		emulator.print();
	else
		return 1;

	// Output setup
	Screen screen;
	screen.initiate();

	// Main loop
	bool running = true;
	SDL_Event e;

	while (running){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
				running = false;
				return 0;
			}
		}

		emulator.input();
		emulator.update(0.f);
		emulator.output(screen);

		screen.render();
	}

	return 0;
}