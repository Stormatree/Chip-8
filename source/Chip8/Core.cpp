#include "Core.hpp"
#include "Font.hpp"

Core::Core(){
	reset();
}

void Core::reset(){
	std::fill(_memory, _memory + sizeof(_memory) / sizeof(uint8_t), 0x0);
	std::fill(_screen, _screen + sizeof(_screen) / sizeof(uint8_t), 0x0);
	std::fill(_font, _font + sizeof(_font) / sizeof(uint8_t), 0x0);
	std::fill(_var, _var + sizeof(_var) / sizeof(uint8_t), 0x0);
	std::fill(_key, _key + sizeof(_key) / sizeof(uint8_t), 0x0);

	uint16_t _pc = 0;
	uint16_t _sp = 0;
	uint16_t _i = 0;

	uint16_t _delay = 0;
	uint16_t _sound = 0;

	uint16_t _length = 0;

	for (int i = 0; i < FONT_LENGTH; i++)
		_font[i] = Font8x5[i];
}

bool Core::load(const char* filepath){
	std::ifstream file(filepath, std::fstream::binary);

	if (file){
		int i = 0;

		for (; file.peek() != EOF; i++){
			_memory[i] = file.get();
		}

		_length = i;

		return true;
	}
	else{
		printf("No such file '%s'!\n", filepath);
		return false;
	}
}

void Core::input(uint16_t keys){
	//Input keys
}

void Core::update(float dt){
	//Update timers
}

void Core::output(Screen& screen){
	//Output screen and buzzer
}

void Core::print(){
	for (int i = 0; i < sizeof(_memory) / sizeof(uint8_t); i++){
		if (i % 16 == 0)
			if (!i)
				printf("% 5d : ", i);
			else
				printf("\n% 5d : ", i);

		printf("%02X ", _memory[i]);
	}

	printf("\n");
}

bool Core::operate(uint8_t lower, uint8_t upper){
	uint8_t nibbles[4] = { lower >> 4, lower & 0xF, upper >> 4, upper & 0xF };
	uint16_t tail = (lower << 8) | (upper & 0x0FFF);

	switch (nibbles[0]){
	case 0x0:
		switch (upper){
		case 0xE0: _00E0(); return true;
		case 0xEE: _00EE(); return true;
		default: _0NNN(tail); return true;
		}

	case 0x1: _1NNN(tail); return true;
	case 0x2: _2NNN(tail); return true;
	case 0x3: _3XNN(nibbles[1], upper); return true;
	case 0x4: _4XNN(nibbles[1], upper); return true;
	case 0x5: _5XY0(nibbles[1], nibbles[2]); return true;
	case 0x6: _6XNN(nibbles[1], upper); return true;
	case 0x7: _7XNN(nibbles[1], upper); return true;

	case 0x8:
		switch (nibbles[3]){
		case 0x0: _8XY0(nibbles[1], nibbles[2]); return true;
		case 0x1: _8XY1(nibbles[1], nibbles[2]); return true;
		case 0x2: _8XY2(nibbles[1], nibbles[2]); return true;
		case 0x3: _8XY3(nibbles[1], nibbles[2]); return true;
		case 0x4: _8XY4(nibbles[1], nibbles[2]); return true;
		case 0x5: _8XY5(nibbles[1], nibbles[2]); return true;
		case 0x6: _8XY6(nibbles[1], nibbles[2]); return true;
		case 0x7: _8XY7(nibbles[1], nibbles[2]); return true;
		case 0xE: _8XYE(nibbles[1], nibbles[2]); return true;
		default: return false;
		}

	case 0x9: _9XY0(nibbles[1], nibbles[2]); return true;
	case 0xA: _ANNN(tail); return true;
	case 0xB: _BNNN(tail); return true;
	case 0xC: _CXNN(nibbles[1], upper); return true;
	case 0xD: _DXYN(nibbles[1], nibbles[2], nibbles[3]); return true;

	case 0xE:
		switch (upper){
		case 0x9E: _EX9E(nibbles[1]); return true;
		case 0xA1: _EXA1(nibbles[1]); return true;
		default: return false;
		}

	case 0xF:
		switch (upper){
		case 0x07: _FX07(nibbles[1]); return true;
		case 0x0A: _FX0A(nibbles[1]); return true;
		case 0x15: _FX15(nibbles[1]); return true;
		case 0x18: _FX18(nibbles[1]); return true;
		case 0x1E: _FX1E(nibbles[1]); return true;
		case 0x29: _FX29(nibbles[1]); return true;
		case 0x33: _FX33(nibbles[1]); return true;
		case 0x55: _FX55(nibbles[1]); return true;
		case 0x65: _FX65(nibbles[1]); return true;
		default: return false;
		}

	default:
		return false;
	}
}

void Core::_tick(){

}

void Core::_skip(){

}

void Core::_jump(uint16_t& reg, uint16_t val){

}