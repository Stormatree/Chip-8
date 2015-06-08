#include "Interpreter.hpp"

bool Interpreter::operate(uint8_t lower, uint8_t upper){
	uint8_t nibble_0 = lower >> 4;
	uint8_t nibble_1 = lower & 0xF;
	uint8_t nibble_2 = upper >> 4;
	uint8_t nibble_3 = upper & 0xF;

	uint16_t tail = (lower << 8) | (upper & 0x0FFF);

	switch (nibble_0){
	case 0x0:
		switch (upper){
		case 0xE0: _00E0(); return true;
		case 0xEE: _00EE(); return true;
		default: _0NNN(tail); return true;
		}

	case 0x1: _1NNN(tail); return true;
	case 0x2: _2NNN(tail); return true;
	case 0x3: _3XNN(nibble_1, upper); return true;
	case 0x4: _4XNN(nibble_1, upper); return true;
	case 0x5: _5XY0(nibble_1, nibble_2); return true;
	case 0x6: _6XNN(nibble_1, upper); return true;
	case 0x7: _7XNN(nibble_1, upper); return true;

	case 0x8:
		switch (nibble_3){
		case 0x0: _8XY0(nibble_1, nibble_2); return true;
		case 0x1: _8XY1(nibble_1, nibble_2); return true;
		case 0x2: _8XY2(nibble_1, nibble_2); return true;
		case 0x3: _8XY3(nibble_1, nibble_2); return true;
		case 0x4: _8XY4(nibble_1, nibble_2); return true;
		case 0x5: _8XY5(nibble_1, nibble_2); return true;
		case 0x6: _8XY6(nibble_1, nibble_2); return true;
		case 0x7: _8XY7(nibble_1, nibble_2); return true;
		case 0xE: _8XYE(nibble_1, nibble_2); return true;
		default: return false;
		}

	case 0x9: _9XY0(nibble_1, nibble_2); return true;
	case 0xA: _ANNN(tail); return true;
	case 0xB: _BNNN(tail); return true;
	case 0xC: _CXNN(nibble_1, upper); return true;
	case 0xD: _DXYN(nibble_1, nibble_2, nibble_3); return true;

	case 0xE:
		switch (upper){
		case 0x9E: _EX9E(nibble_1); return true;
		case 0xA1: _EXA1(nibble_1); return true;
		default: return false;
		}

	case 0xF:
		switch (upper){
		case 0x07: _FX07(nibble_1); return true;
		case 0x0A: _FX0A(nibble_1); return true;
		case 0x15: _FX15(nibble_1); return true;
		case 0x18: _FX18(nibble_1); return true;
		case 0x1E: _FX1E(nibble_1); return true;
		case 0x29: _FX29(nibble_1); return true;
		case 0x33: _FX33(nibble_1); return true;
		case 0x55: _FX55(nibble_1); return true;
		case 0x65: _FX65(nibble_1); return true;
		default: return false;
		}

	default:
		return false;
	}
}