#include "Interpreter.hpp"

bool Interpreter::load(const char* filepath){
	reset();

	std::ifstream file(filepath, std::fstream::binary);
	
	if (file){
		for (int i = ENTRY_POINT; file.peek() != EOF; i++){
			_memory[i] = file.get();
		}
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

	_i = NULL_VAL;

	_delay = NULL_VAL;
	_sound = NULL_VAL;

	_pc = ENTRY_POINT;
}

void Interpreter::print(){
	for (int i = 0; i < MEMORY_SIZE; i++){
		if (i % 16 == 0)
			if (!i)
				printf("% 5d : ", i);
			else
				printf("\n% 5d : ", i);

		printf("%02x ", _memory[i]);
	}
}

void Interpreter::tick(){
	_disassemble();

	//_pc += 2;
}

void Interpreter::_disassemble(){
	uint16_t op = (_memory[_pc] << 8) | (_memory[_pc + 1]);
}