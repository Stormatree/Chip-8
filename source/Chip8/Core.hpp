#pragma once

#include <stdint.h>
#include <fstream>
#include "Output/Screen.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Core{
	bool _running = true;

	static const uint16_t _entryPoint = 512;

	static const int _bufferHeight = 32;
	static const int _bufferWidth = 64;

	// Memory Containers
	uint8_t _memory[4096];
	uint8_t _buffer[_bufferHeight][_bufferWidth];
	uint8_t _var[16];
	uint8_t _key[16];
	uint16_t _stack[16];

	// Private Registers
	uint16_t _pc;
	uint16_t _i;
	uint8_t _sp;

	// Timers
	uint8_t _delay;
	uint8_t _sound;

	uint16_t _programLength;
	
	// Outputs
	Screen _screen;
	Mix_Music* _tone = 0;

	// Opcodes
	void _00E0();
	void _00EE();
	void _0NNN(uint16_t NNN){} //ignored
	void _1NNN(uint16_t NNN);
	void _2NNN(uint16_t NNN);
	void _3XNN(uint8_t VX, uint8_t NN);
	void _4XNN(uint8_t VX, uint8_t NN);
	void _5XY0(uint8_t VX, uint8_t VY);
	void _6XNN(uint8_t VX, uint8_t NN);
	void _7XNN(uint8_t VX, uint8_t NN);
	void _8XY0(uint8_t VX, uint8_t VY);
	void _8XY1(uint8_t VX, uint8_t VY);
	void _8XY2(uint8_t VX, uint8_t VY);
	void _8XY3(uint8_t VX, uint8_t VY);
	void _8XY4(uint8_t VX, uint8_t VY);
	void _8XY5(uint8_t VX, uint8_t VY);
	void _8XY6(uint8_t VX, uint8_t VY);
	void _8XY7(uint8_t VX, uint8_t VY);
	void _8XYE(uint8_t VX, uint8_t VY);
	void _9XY0(uint8_t VX, uint8_t VY);
	void _ANNN(uint16_t NNN);
	void _BNNN(uint16_t NNN);
	void _CXNN(uint8_t VX, uint8_t NN);
	void _DXYN(uint8_t VX, uint8_t VY, uint8_t N);
	void _EX9E(uint8_t VX);
	void _EXA1(uint8_t VX);
	void _FX07(uint8_t VX);
	void _FX0A(uint8_t VX);
	void _FX15(uint8_t VX);
	void _FX18(uint8_t VX);
	void _FX1E(uint8_t VX);
	void _FX29(uint8_t VX);
	void _FX33(uint8_t VX);
	void _FX55(uint8_t VX);
	void _FX65(uint8_t VX);

public:
	// Takes in location of chip-8.exe for asset reference
	Core(std::string exeLocation = "");
	~Core();
	
	// Resets all CPU parameters to default
	void reset();
	// Loads rom into memory
	bool load(const char* filepath);

	// Return if core is running
	bool running();

	// Game states
	void input();
	void update();
	void output();

	// Perform an opcode, returns true if valid
	bool operate(uint8_t lower, uint8_t upper);

	// Get screen object for setting parameters
	Screen& screen();

	// Print memory to console (Debug only)
	void print();
};