#include "Chip8/Core.hpp"

#define DEFUALT_ROM "../asset/rom/MAZE.rom"

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

	while (emulator.running()){
		emulator.input();
		emulator.update();
		emulator.output();
	}

	return 0;
}