#include "Interpreter.hpp"

bool Interpreter::load(const char* filepath){
	std::ifstream file(filepath);
	
	if (file){
		for (int i = ENTRY_POINT; file.peek() != EOF; i++){
			_memory[i] = file.get();
		}
		file.close();
		return true;
	}
	else{
		printf("No such file '%s'!\n", filepath);
		return false;
	}
}

void Interpreter::run(){
	for (int i = 0; i < MEMORY_SIZE; i++){
		printf("%02x", _memory[i]);
	}

	_tick();
}