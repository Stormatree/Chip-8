#pragma once

#include "Core.hpp"

class Interpreter : public Core{
	void _00E0();
	void _00EE();
	void _0NNN(uint16_t NNN);
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
	bool operate(uint8_t lower, uint8_t upper);
};