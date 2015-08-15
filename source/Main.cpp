#include "Chip8/Core.hpp"
#include <chrono>
#include <thread>

#define DEFUALT_ROM "../asset/rom/MAZE.rom"
#define CLOCK_SPEED 500

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

	while (emulator.running()){
		// Timer start
		auto start = std::chrono::high_resolution_clock::now();

		emulator.input();
		emulator.update();
		emulator.output();

		// Timer end, and then speed control
		std::chrono::duration<double, std::milli> dt = std::chrono::high_resolution_clock::now() - start;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / CLOCK_SPEED - (int)dt.count()));
	}

	return 0;
}