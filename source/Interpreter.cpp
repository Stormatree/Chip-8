#include "Interpreter.hpp"
#include "Font.hpp"

void Interpreter::_tick(){
	if (ENTRY_POINT <= _pc + 2 && _pc < _program_len + ENTRY_POINT)
		_pc += 2;
}

void Interpreter::_skip(){
	if (ENTRY_POINT <= _pc + 4 && _pc + 4 < _program_len + ENTRY_POINT)
		_pc += 4;
}

void Interpreter::_jump(uint16_t& reg, uint16_t val){
	if (ENTRY_POINT <= val && val < _program_len + ENTRY_POINT)
		reg = val;
}

void Interpreter::reset(){
	std::fill(_memory, _memory + MEMORY_SIZE, 0x0);
	std::fill(_var, _var + VAR_SIZE, 0x0);
	std::fill(_screen, _screen + SCREEN_HEIGHT * SCREEN_WIDTH, 0x0);

	_delay = 0x0;
	_sound = 0x0;

	_pc = ENTRY_POINT;
	_sp = 0x0;
	_i = 0x0;
	
	_program_len = 0x0;

	for (int i = 0; i < FONT_LENGTH; i++)
		_memory[i] = Font8x5[i];
}

bool Interpreter::load(const char* filepath){
	reset();

	std::ifstream file(filepath, std::fstream::binary);
	
	if (file){
		int i = ENTRY_POINT;

		for (; file.peek() != EOF; i++){
			_memory[i] = file.get();
		}

		_program_len = i - ENTRY_POINT;

		return true;
	}
	else{
		printf("No such file '%s'!\n", filepath);
		return false;
	}
}

void Interpreter::input(uint16_t keys){
	//edit _keys
}

void Interpreter::update(){
	//update timers

	if (_pc < _program_len + ENTRY_POINT)
		op_auto(_memory[_pc], _memory[_pc + 1]);
}

void Interpreter::render(Screen& screen){
	screen.drawSprite(0 * 5, 0, _memory, 0x0);
	screen.drawSprite(1 * 5, 0, _memory, 0x1);
	screen.drawSprite(2 * 5, 0, _memory, 0x2);
	screen.drawSprite(3 * 5, 0, _memory, 0x3);
	screen.drawSprite(4 * 5, 0, _memory, 0x4);
	screen.drawSprite(5 * 5, 0, _memory, 0x5);
	screen.drawSprite(6 * 5, 0, _memory, 0x6);
	screen.drawSprite(7 * 5, 0, _memory, 0x7);
	screen.drawSprite(0 * 5, 1 * 6, _memory, 0x8);
	screen.drawSprite(1 * 5, 1 * 6, _memory, 0x9);
	screen.drawSprite(2 * 5, 1 * 6, _memory, 0xA);
	screen.drawSprite(3 * 5, 1 * 6, _memory, 0xB);
	screen.drawSprite(4 * 5, 1 * 6, _memory, 0xC);
	screen.drawSprite(5 * 5, 1 * 6, _memory, 0xD);
	screen.drawSprite(6 * 5, 1 * 6, _memory, 0xE);
	screen.drawSprite(7 * 5, 1 * 6, _memory, 0xF);
}

bool Interpreter::op_auto(uint8_t lower, uint8_t upper){
	uint8_t nibble_0 = lower >> 4;
	uint8_t nibble_1 = lower & 0xF;
	uint8_t nibble_2 = upper >> 4;
	uint8_t nibble_3 = upper & 0xF;

	uint16_t tail = (lower << 8) | upper & 0x0FFF;

	switch (nibble_0){
	case 0x0:
		switch (upper){
			case 0xE0: op_00E0(); return true;
			case 0xEE: op_00EE(); return true;
			default: op_0NNN(tail); return true;
		}

	case 0x1: op_1NNN(tail); return true;
	case 0x2: op_2NNN(tail); return true;
	case 0x3: op_3XNN(nibble_1, upper); return true;
	case 0x4: op_4XNN(nibble_1, upper); return true;
	case 0x5: op_5XY0(nibble_1, nibble_2); return true;
	case 0x6: op_6XNN(nibble_1, upper); return true;
	case 0x7: op_7XNN(nibble_1, upper); return true;

	case 0x8:
		switch (nibble_3){
			case 0x0: op_8XY0(nibble_1, nibble_2); return true;
			case 0x1: op_8XY1(nibble_1, nibble_2); return true;
			case 0x2: op_8XY2(nibble_1, nibble_2); return true;
			case 0x3: op_8XY3(nibble_1, nibble_2); return true;
			case 0x4: op_8XY4(nibble_1, nibble_2); return true;
			case 0x5: op_8XY5(nibble_1, nibble_2); return true;
			case 0x6: op_8XY6(nibble_1, nibble_2); return true;
			case 0x7: op_8XY7(nibble_1, nibble_2); return true;
			case 0xE: op_8XYE(nibble_1, nibble_2); return true;
			default: return false;
		}

	case 0x9: op_9XY0(nibble_1, nibble_2); return true;
	case 0xA: op_ANNN(tail); return true;
	case 0xB: op_BNNN(tail); return true;
	case 0xC: op_CXNN(nibble_1, upper); return true;
	case 0xD: op_DXYN(nibble_1, nibble_2, nibble_3); return true;

	case 0xE:
		switch (upper){
			case 0x9E: op_EX9E(nibble_1); return true;
			case 0xA1: op_EXA1(nibble_1); return true;
			default: return false;
		}

	case 0xF:
		switch (upper){
			case 0x07: op_FX07(nibble_1); return true;
			case 0x0A: op_FX0A(nibble_1); return true;
			case 0x15: op_FX15(nibble_1); return true;
			case 0x18: op_FX18(nibble_1); return true;
			case 0x1E: op_FX1E(nibble_1); return true;
			case 0x29: op_FX29(nibble_1); return true;
			case 0x33: op_FX33(nibble_1); return true;
			case 0x55: op_FX55(nibble_1); return true;
			case 0x65: op_FX65(nibble_1); return true;
			default: return false;
		}

	default:
		return false;
	}
}

void Interpreter::print(){
	for (int i = 0; i < MEMORY_SIZE; i++){
		if (i % 16 == 0)
			if (!i)
				printf("% 5d : ", i);
			else
				printf("\n% 5d : ", i);

		printf("%02X ", _memory[i]);
	}

	printf("\n");
}