#include "Interpreter.hpp"

void Interpreter::_tick(){
	if (_pc < _length + ENTRY_POINT)
		_pc += 2;
}

void Interpreter::_jump(uint16_t pc){
	if (pc < _length + ENTRY_POINT)
		_pc = pc;
}

void Interpreter::op_00E0(uint16_t opcode){
	printf("00E0"); 
	_tick();
}

void Interpreter::op_00EE(uint16_t opcode){
	printf("00EE"); 
	_tick();
}

void Interpreter::op_0NNN(uint16_t opcode){
	printf("0NNN"); 
	_tick();
}

void Interpreter::op_1NNN(uint16_t opcode){
	printf("1NNN"); 
	_tick();
}

void Interpreter::op_2NNN(uint16_t opcode){
	printf("2NNN");
	_tick();
}

void Interpreter::op_3XNN(uint16_t opcode){
	printf("3XNN");
	_tick();
}
void Interpreter::op_4XNN(uint16_t opcode){
	printf("4XNN");
	_tick();
}

void Interpreter::op_5XY0(uint16_t opcode){
	printf("5XY0");
	_tick();
}

void Interpreter::op_6XNN(uint16_t opcode){
	printf("6XNN");
	_tick();
}

void Interpreter::op_7XNN(uint16_t opcode){
	printf("7XNN");
	_tick();
}

void Interpreter::op_8XY0(uint16_t opcode){
	printf("8XY0");
	_tick();
}

void Interpreter::op_8XY1(uint16_t opcode){
	printf("8XY1");
	_tick();
}

void Interpreter::op_8XY2(uint16_t opcode){
	printf("8XY2"); 
	_tick();
}

void Interpreter::op_8XY3(uint16_t opcode){
	printf("8XY3");
	_tick();
}

void Interpreter::op_8XY4(uint16_t opcode){
	printf("8XY4"); 
	_tick();
}

void Interpreter::op_8XY5(uint16_t opcode){
	printf("8XY5"); 
	_tick();
}

void Interpreter::op_8XY6(uint16_t opcode){
	printf("8XY6"); 
	_tick();
}

void Interpreter::op_8XY7(uint16_t opcode){
	printf("8XY7");
	_tick();
}

void Interpreter::op_8XYE(uint16_t opcode){
	printf("8XYE");
	_tick();
}

void Interpreter::op_9XY0(uint16_t opcode){
	printf("9XY0");
	_tick();
}

void Interpreter::op_ANNN(uint16_t opcode){
	printf("ANNN");
	_tick();
}

void Interpreter::op_BNNN(uint16_t opcode){
	printf("BNNN");
	_tick();
}

void Interpreter::op_CXNN(uint16_t opcode){
	printf("CXNN");
	_tick();
}

void Interpreter::op_DXYN(uint16_t opcode){
	printf("DXYN");
	_tick();
}

void Interpreter::op_EX9E(uint16_t opcode){
	printf("EX9E");
	_tick();
}

void Interpreter::op_EXA1(uint16_t opcode){
	printf("EXA1"); 
	_tick();
}

void Interpreter::op_FX07(uint16_t opcode){
	printf("FX07"); 
	_tick();
}

void Interpreter::op_FX0A(uint16_t opcode){
	printf("FX0A"); 
	_tick();
}

void Interpreter::op_FX15(uint16_t opcode){
	printf("FX15");
	_tick();
}

void Interpreter::op_FX18(uint16_t opcode){
	printf("FX18");
	_tick();
}

void Interpreter::op_FX1E(uint16_t opcode){
	printf("FX1E");
	_tick();
}

void Interpreter::op_FX29(uint16_t opcode){
	printf("FX29");
	_tick();
}

void Interpreter::op_FX33(uint16_t opcode){
	printf("FX33");
	_tick();
}

void Interpreter::op_FX55(uint16_t opcode){
	printf("FX55");
	_tick();
}

void Interpreter::op_FX65(uint16_t opcode){
	printf("FX65");
	_tick();
}

/*
void Interpreter::op_00EE(){
	printf("9XY0");
	_tick();
}

void Interpreter::op_0NNN(uint16_t NNN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_1NNN(uint16_t NNN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_2NNN(uint16_t NNN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_3XNN(uint8_t X, uint8_t NN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_4XNN(uint8_t X, uint8_t NN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_5XY0(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_6XNN(uint8_t X, uint8_t NN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_7XNN(uint8_t X, uint8_t NN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY0(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY1(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY2(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY3(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY4(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY5(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY6(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XY7(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_8XYE(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_9XY0(uint8_t X, uint8_t Y){
	printf("9XY0");
	_tick();
}

void Interpreter::op_ANNN(uint16_t NNN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_BNNN(uint16_t NNN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_CXNN(uint8_t NN){
	printf("9XY0");
	_tick();
}

void Interpreter::op_DXYN(uint8_t X, uint8_t Y, uint8_t N){
	printf("9XY0");
	_tick();
}

void Interpreter::op_EX9E(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_EXA1(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX07(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX0A(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX15(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX18(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX1E(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX29(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX33(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX55(uint8_t X){
	printf("9XY0");
	_tick();
}

void Interpreter::op_FX65(uint8_t X){
	printf("9XY0");
	_tick();
}
*/