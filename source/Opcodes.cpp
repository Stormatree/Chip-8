#include "Interpreter.hpp"

void Interpreter::_tick(){
	if (_pc < _length + ENTRY_POINT)
		_pc += 2;
}

void Interpreter::_jump(uint16_t pc){
	if (pc < _length + ENTRY_POINT)
		_pc = pc;
}

void Interpreter::op_00E0(){
	printf("9XY0");
	_tick();
}

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

void Interpreter::op_CXNN(uint8_t X, uint8_t NN){
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