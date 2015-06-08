#include "Interpreter.hpp"
#include "Font.hpp"

bool Interpreter::load(const char* filepath){
	reset();

	std::ifstream file(filepath, std::fstream::binary);
	
	if (file){
		int i = ENTRY_POINT;

		for (; file.peek() != EOF; i++){
			_memory[i] = file.get();
		}

		_length = i - ENTRY_POINT;

		return true;
	}
	else{
		printf("No such file '%s'!\n", filepath);
		return false;
	}
}

void Interpreter::reset(){
	std::fill(_memory, _memory + MEMORY_SIZE, NULL_VAL);
	std::fill(_var, _var + VAR_SIZE, NULL_VAL);
	std::fill(_stack, _stack + STACK_SIZE, NULL_VAL);
	std::fill(_keys, _keys + KEY_SIZE, NULL_VAL);
	std::fill(_screen, _screen + SCREEN_HEIGHT * SCREEN_WIDTH, NULL_VAL);

	_delay = NULL_VAL;
	_sound = NULL_VAL;
	_i = NULL_VAL;

	_pc = ENTRY_POINT;
	_length = NULL_VAL;

	for (int i = 0; i < FONT_LENGTH; i++)
		_memory[i] = Font8x5[i];
}

void Interpreter::input(uint16_t keys){

}

void Interpreter::execute(){
	if (_pc < _length + ENTRY_POINT)
		op_auto((_memory[_pc] << 8) | (_memory[_pc + 1]));
}

void Interpreter::render(Screen& screen){
	screen.drawSprite(0 * 5, 0, Font8x5, 0x0);
	screen.drawSprite(1 * 5, 0, Font8x5, 0x1);
	screen.drawSprite(2 * 5, 0, Font8x5, 0x2);
	screen.drawSprite(3 * 5, 0, Font8x5, 0x3);
	screen.drawSprite(4 * 5, 0, Font8x5, 0x4);
	screen.drawSprite(5 * 5, 0, Font8x5, 0x5);
	screen.drawSprite(6 * 5, 0, Font8x5, 0x6);
	screen.drawSprite(7 * 5, 0, Font8x5, 0x7);
	screen.drawSprite(0 * 5, 1 * 6, Font8x5, 0x8);
	screen.drawSprite(1 * 5, 1 * 6, Font8x5, 0x9);
	screen.drawSprite(2 * 5, 1 * 6, Font8x5, 0xA);
	screen.drawSprite(3 * 5, 1 * 6, Font8x5, 0xB);
	screen.drawSprite(4 * 5, 1 * 6, Font8x5, 0xC);
	screen.drawSprite(5 * 5, 1 * 6, Font8x5, 0xD);
	screen.drawSprite(6 * 5, 1 * 6, Font8x5, 0xE);
	screen.drawSprite(7 * 5, 1 * 6, Font8x5, 0xF);
}

void Interpreter::op_auto(uint16_t opcode){
	printf("% 5d : ", _pc);

	uint8_t lower = opcode >> 8;
	uint8_t upper = opcode & 0x00FF;

	uint8_t nibble_0 = lower >> 4;
	uint8_t nibble_1 = lower & 0x0F;
	uint8_t nibble_2 = upper >> 4;
	uint8_t nibble_3 = upper & 0x0F;

	uint16_t tail = opcode & 0x0FFF;

	switch (nibble_0){
	case 0x0:
		switch (upper){
			case 0xE0: op_00E0(opcode); break;
			case 0xEE: op_00EE(opcode); break;
			default: op_0NNN(opcode); break;
		}
		break;

	case 0x1: op_1NNN(opcode); break;
	case 0x2: op_2NNN(opcode); break;
	case 0x3: op_3XNN(opcode); break;
	case 0x4: op_4XNN(opcode); break;
	case 0x5: op_5XY0(opcode); break;
	case 0x6: op_6XNN(opcode); break;
	case 0x7: op_7XNN(opcode); break;

	case 0x8:
		switch (nibble_3){
			case 0x0: op_8XY0(opcode); break;
			case 0x1: op_8XY1(opcode); break;
			case 0x2: op_8XY2(opcode); break;
			case 0x3: op_8XY3(opcode); break;
			case 0x4: op_8XY4(opcode); break;
			case 0x5: op_8XY5(opcode); break;
			case 0x6: op_8XY6(opcode); break;
			case 0x7: op_8XY7(opcode); break;
			case 0xE: op_8XYE(opcode); break;
			default: printf("8..."); break;
		}
		break;

	case 0x9: op_9XY0(opcode); break;
	case 0xA: op_ANNN(opcode); break;
	case 0xB: op_BNNN(opcode); break;
	case 0xC: op_CXNN(opcode); break;
	case 0xD: op_DXYN(opcode); break;

	case 0xE:
		switch (opcode & 0xFF){
			case 0x9E: op_EX9E(opcode); break;
			case 0xA1: op_EXA1(opcode); break;
			default: printf("E..."); break;
		}
		break;

	case 0xF:
		switch (upper){
			case 0x07: op_FX07(opcode); break;
			case 0x0A: op_FX0A(opcode); break;
			case 0x15: op_FX15(opcode); break;
			case 0x18: op_FX18(opcode); break;
			case 0x1E: op_FX1E(opcode); break;
			case 0x29: op_FX29(opcode); break;
			case 0x33: op_FX33(opcode); break;
			case 0x55: op_FX55(opcode); break;
			case 0x65: op_FX65(opcode); break;
			default: printf("F..."); break;
		}
		break;
	}

	printf(" - 0x%04X\n", opcode);
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