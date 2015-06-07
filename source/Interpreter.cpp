#include "Interpreter.hpp"

#include <time.h>

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
}

void Interpreter::print(){
	for (int i = ENTRY_POINT; i < MEMORY_SIZE; i++){
		if (i % 16 == 0)
			if (!i)
				printf("% 5d : ", i);
			else
				printf("\n% 5d : ", i);

		printf("%02X ", _memory[i]);
	}

	printf("\n");
}

void Interpreter::tick(){
	if (_pc < _length + ENTRY_POINT){
		_disassemble();
		_pc += 2;
	}
}

// Testing functions
void op_00E0(uint16_t opcode){ printf("00E0"); }
void op_00EE(uint16_t opcode){ printf("00EE"); }
void op_0NNN(uint16_t opcode){ printf("0NNN"); }
void op_1NNN(uint16_t opcode){ printf("1NNN"); }
void op_2NNN(uint16_t opcode){ printf("2NNN"); }
void op_3XNN(uint16_t opcode){ printf("3XNN"); }
void op_4XNN(uint16_t opcode){ printf("4XNN"); }
void op_5XY0(uint16_t opcode){ printf("5XY0"); }
void op_6XNN(uint16_t opcode){ printf("6XNN"); }
void op_7XNN(uint16_t opcode){ printf("7XNN"); }
void op_8XY0(uint16_t opcode){ printf("8XY0"); }
void op_8XY1(uint16_t opcode){ printf("8XY1"); }
void op_8XY2(uint16_t opcode){ printf("8XY2"); }
void op_8XY3(uint16_t opcode){ printf("8XY3"); }
void op_8XY4(uint16_t opcode){ printf("8XY4"); }
void op_8XY5(uint16_t opcode){ printf("8XY5"); }
void op_8XY6(uint16_t opcode){ printf("8XY6"); }
void op_8XY7(uint16_t opcode){ printf("8XY7"); }
void op_8XYE(uint16_t opcode){ printf("8XYE"); }
void op_9XY0(uint16_t opcode){ printf("9XY0"); }
void op_ANNN(uint16_t opcode){ printf("ANNN"); }
void op_BNNN(uint16_t opcode){ printf("BNNN"); }
void op_CXNN(uint16_t opcode){ printf("CXNN"); }
void op_DXYN(uint16_t opcode){ printf("DXYN"); }
void op_EX9E(uint16_t opcode){ printf("EX9E"); }
void op_EXA1(uint16_t opcode){ printf("EXA1"); }
void op_FX07(uint16_t opcode){ printf("FX07"); }
void op_FX0A(uint16_t opcode){ printf("FX0A"); }
void op_FX15(uint16_t opcode){ printf("FX15"); }
void op_FX18(uint16_t opcode){ printf("FX18"); }
void op_FX1E(uint16_t opcode){ printf("FX1E"); }
void op_FX29(uint16_t opcode){ printf("FX29"); }
void op_FX33(uint16_t opcode){ printf("FX33"); }
void op_FX55(uint16_t opcode){ printf("FX55"); }
void op_FX65(uint16_t opcode){ printf("FX65"); }

void Interpreter::_disassemble(){
	printf("% 5d : ", _pc);

	uint16_t opcode = (_memory[_pc] << 8) | (_memory[_pc + 1]);

	switch (opcode >> 12){
	case 0x0:
		switch (opcode & 0xFF){
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
		switch (opcode & 0xF){
		case 0x0: op_8XY0(opcode); break;
		case 0x1: op_8XY1(opcode); break;
		case 0x2: op_8XY2(opcode); break;
		case 0x3: op_8XY3(opcode); break;
		case 0x4: op_8XY4(opcode); break;
		case 0x5: op_8XY5(opcode); break;
		case 0x6: op_8XY6(opcode); break;
		case 0x7: op_8XY7(opcode); break;
		case 0xE: op_8XYE(opcode); break;
		default: ("8..."); break;
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
		default: ("E..."); break;
		}
		break;

	case 0xF:
		switch (opcode & 0xFF){
		case 0x07: op_FX07(opcode); break;
		case 0x0A: op_FX0A(opcode); break;
		case 0x15: op_FX15(opcode); break;
		case 0x18: op_FX18(opcode); break;
		case 0x1E: op_FX1E(opcode); break;
		case 0x29: op_FX29(opcode); break;
		case 0x33: op_FX33(opcode); break;
		case 0x55: op_FX55(opcode); break;
		case 0x65: op_FX65(opcode); break;
		default: ("F..."); break;
		}
		break;
	}

	printf(" - 0x%04X\n", opcode);
}