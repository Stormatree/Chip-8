#pragma once

#include <stdint.h>
#include <fstream>

#define VAR_SIZE 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 64
#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define KEY_SIZE 16
#define ENTRY_POINT 0x200
#define NULL_VAL 0x00

class Interpreter{
	uint8_t _screen[SCREEN_HEIGHT * SCREEN_WIDTH];
	uint8_t _var[VAR_SIZE];
	uint8_t _memory[MEMORY_SIZE];
	uint8_t _stack[STACK_SIZE];
	uint8_t _keys[KEY_SIZE];
	
	uint16_t _i;
	uint8_t _delay;
	uint8_t _sound;

	uint16_t _pc;
	uint16_t _length;
	
	void _disassemble();

	//void _input();

public:
	bool load(const char* filepath);

	void reset();

	void print();

	void tick();
};

