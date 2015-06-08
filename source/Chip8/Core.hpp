#pragma once

#include <stdint.h>
#include <fstream>
#include "Render/Screen.hpp"

#define MEMORY_SIZE 4096

#define MEM_FONT 0
#define MEM_FONT_SIZE 32

#define MEM_VARS 64
#define MEM_VARS_SIZE 16

#define MEM_KEYS 128
#define MEM_KEYS_SIZE 16

#define MEM_SCREEN 256
#define MEM_SCREEN_SIZE 256

#define ENTRY_POINT 512

class Core{
	uint8_t _memory[MEMORY_SIZE];

	uint8_t _delay;
	uint8_t _sound;

	uint16_t _pc;
	uint16_t _sp;
	uint16_t _i;

	uint16_t _program_len;

protected:
	void _tick();
	void _skip();
	void _jump(uint16_t& reg, uint16_t val);

public:
	void reset();
	bool load(const char* filepath);

	void input(uint16_t keys);
	void update();
	void render(Screen& screen);

	virtual bool operate(uint8_t lower, uint8_t upper) = 0;

	void print();
};