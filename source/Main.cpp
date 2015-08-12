#include "Output/Screen.hpp"
#include "Chip8/Core.hpp"

#define DEFUALT_ROM "../asset/rom/TEST.rom"

#undef main

int main(int argc, char* argv[]){
	// Emulator setup
	Core emulator;

	if (argc > 1 && emulator.load(argv[1])) // Load from args
		emulator.print();
	else if (argc > 1)
		return 1;
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
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		emulator.input(0x0000);
		emulator.update(0.f);
		emulator.output(screen);

		screen.render();
	}

	return 0;
}