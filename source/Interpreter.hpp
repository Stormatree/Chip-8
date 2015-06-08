#pragma once

#include <stdint.h>
#include <fstream>
#include "Screen.hpp"

#define MEMORY_SIZE 4096
#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define VAR_SIZE 16

#define ENTRY_POINT 0x200

class Interpreter{
	uint8_t _memory[MEMORY_SIZE];
	uint8_t _screen[SCREEN_HEIGHT * SCREEN_WIDTH];
	uint8_t _var[VAR_SIZE];

	uint16_t _keys;
	
	uint8_t _delay;
	uint8_t _sound;

	uint16_t _pc;
	uint16_t _sp;
	uint16_t _i;

	uint16_t _program_len;

	void _tick();
	void _skip();
	void _jump(uint16_t& reg, uint16_t val);

public:
	void reset();
	bool load(const char* filepath);
	
	void input(uint16_t keys);
	void update();
	void render(Screen& screen);

	bool op_auto(uint8_t lower, uint8_t upper);

	void op_00E0();
	void op_00EE();
	void op_0NNN(uint16_t NNN);
	void op_1NNN(uint16_t NNN);
	void op_2NNN(uint16_t NNN);
	void op_3XNN(uint8_t X, uint8_t NN);
	void op_4XNN(uint8_t X, uint8_t NN);
	void op_5XY0(uint8_t X, uint8_t Y);
	void op_6XNN(uint8_t X, uint8_t NN);
	void op_7XNN(uint8_t X, uint8_t NN);
	void op_8XY0(uint8_t X, uint8_t Y);
	void op_8XY1(uint8_t X, uint8_t Y);
	void op_8XY2(uint8_t X, uint8_t Y);
	void op_8XY3(uint8_t X, uint8_t Y);
	void op_8XY4(uint8_t X, uint8_t Y);
	void op_8XY5(uint8_t X, uint8_t Y);
	void op_8XY6(uint8_t X, uint8_t Y);
	void op_8XY7(uint8_t X, uint8_t Y);
	void op_8XYE(uint8_t X, uint8_t Y);
	void op_9XY0(uint8_t X, uint8_t Y);
	void op_ANNN(uint16_t NNN);
	void op_BNNN(uint16_t NNN);
	void op_CXNN(uint8_t X, uint8_t NN);
	void op_DXYN(uint8_t X, uint8_t Y, uint8_t N);
	void op_EX9E(uint8_t X);
	void op_EXA1(uint8_t X);
	void op_FX07(uint8_t X);
	void op_FX0A(uint8_t X);
	void op_FX15(uint8_t X);
	void op_FX18(uint8_t X);
	void op_FX1E(uint8_t X);
	void op_FX29(uint8_t X);
	void op_FX33(uint8_t X);
	void op_FX55(uint8_t X);
	void op_FX65(uint8_t X);

	void print();
};