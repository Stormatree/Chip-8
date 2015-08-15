#include "Chip8/Core.hpp"
#include <chrono>
#include <thread>

#define DEFUALT_ROM "../asset/rom/MAZE.rom"
#define CLOCK_SPEED 200

#undef main

int main(int argc, char* argv[]){
	srand((unsigned int)time(0));

	// Emulator setup and loading ROM
	Core emulator(argv[0]);

	// Loading from arg, if not, then default
	if (argc > 1 && emulator.load(argv[1]))
		emulator.print();
	else if (emulator.load(DEFUALT_ROM))
		emulator.print();
	else
		return 1;

	emulator.screen().setColour(9, 18, 3, 53, 232, 13);

	while (emulator.running()){
		auto start = std::chrono::high_resolution_clock::now();

		emulator.input();
		emulator.update();
		emulator.output();

		std::chrono::duration<double, std::milli> dt = std::chrono::high_resolution_clock::now() - start;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / CLOCK_SPEED - (int)dt.count()));
	}

	return 0;
}