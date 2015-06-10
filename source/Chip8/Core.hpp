#pragma once

#include <stdint.h>
#include <fstream>
#include "Render/Screen.hpp"

#define MEMORY_SIZE 0x1000

#define M_FONT 0x0
#define M_FONT_SIZE 32

#define M_VARS 0x40
#define M_VARS_SIZE 16

#define M_KEYS 0x70
#define M_KEYS_SIZE 16

#define M_PC 0xA0
#define M_PC_SIZE 2

#define M_SP 0xB0
#define M_SP_SIZE 2

#define M_I 0xC0
#define M_I_SIZE 2

#define M_DELAY 0xD0
#define M_DELAY_SIZE 2

#define M_SOUND 0xE0
#define M_SOUND_SIZE 2

#define M_SCREEN 0x100
#define M_SCREEN_SIZE 256

#define ENTRY_POINT 0x200

class Core{
	uint8_t _memory[MEMORY_SIZE];
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