#include "Interpreter.hpp"

// Descriptions and names sourced from CHIP-8 Wikipedia article
// http://en.wikipedia.org/wiki/CHIP-8

void Interpreter::op_00E0(){
	// Calls RCA 1802 program at address NNN.
	_tick();
}

void Interpreter::op_00EE(){
	// Clears the screen.
	_tick();
}

void Interpreter::op_0NNN(uint16_t NNN){
	// Returns from a subroutine.
	_tick();
}

void Interpreter::op_1NNN(uint16_t NNN){
	// Jumps to address NNN.
	_tick();
}

void Interpreter::op_2NNN(uint16_t NNN){
	// Calls subroutine at NNN.
	_tick();
}

void Interpreter::op_3XNN(uint8_t X, uint8_t NN){
	// Skips the next instruction if VX equals NN.
	_tick();
}

void Interpreter::op_4XNN(uint8_t X, uint8_t NN){
	// Skips the next instruction if VX doesn't equal NN.
	_tick();
}

void Interpreter::op_5XY0(uint8_t X, uint8_t Y){
	// Skips the next instruction if VX equals VY.
	_tick();
}

void Interpreter::op_6XNN(uint8_t X, uint8_t NN){
	// Sets VX to NN.
	_tick();
}

void Interpreter::op_7XNN(uint8_t X, uint8_t NN){
	// Adds NN to VX.
	_tick();
}

void Interpreter::op_8XY0(uint8_t X, uint8_t Y){
	// Sets VX to the value of VY.
	_tick();
}

void Interpreter::op_8XY1(uint8_t X, uint8_t Y){
	// Sets VX to VX or VY.
	_tick();
}

void Interpreter::op_8XY2(uint8_t X, uint8_t Y){
	// Sets VX to VX and VY.
	_tick();
}

void Interpreter::op_8XY3(uint8_t X, uint8_t Y){
	// Sets VX to VX xor VY.
	_tick();
}

void Interpreter::op_8XY4(uint8_t X, uint8_t Y){
	// Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
	_tick();
}

void Interpreter::op_8XY5(uint8_t X, uint8_t Y){
	// VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
	_tick();
}

void Interpreter::op_8XY6(uint8_t X, uint8_t Y){
	// Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
	_tick();
}

void Interpreter::op_8XY7(uint8_t X, uint8_t Y){
	// Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
	_tick();
}

void Interpreter::op_8XYE(uint8_t X, uint8_t Y){
	// Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.
	_tick();
}

void Interpreter::op_9XY0(uint8_t X, uint8_t Y){
	// Skips the next instruction if VX doesn't equal VY.
	_tick();
}

void Interpreter::op_ANNN(uint16_t NNN){
	// Sets I to the address NNN.
	_tick();
}

void Interpreter::op_BNNN(uint16_t NNN){
	// Jumps to the address NNN plus V0.
	_tick();
}

void Interpreter::op_CXNN(uint8_t X, uint8_t NN){
	// Sets VX to a random number, masked by NN.
	_tick();
}

void Interpreter::op_DXYN(uint8_t X, uint8_t Y, uint8_t N){
	// Sprites stored in memory at location in index register (I), maximum 8bits wide. Wraps around the screen. If when drawn, clears a pixel, register VF is set to 1 otherwise it is zero.
	_tick();
}

void Interpreter::op_EX9E(uint8_t X){
	// Skips the next instruction if the key stored in VX is pressed.
	_tick();
}

void Interpreter::op_EXA1(uint8_t X){
	// Skips the next instruction if the key stored in VX isn't pressed.
	_tick();
}

void Interpreter::op_FX07(uint8_t X){
	// Sets VX to the value of the delay timer.
	_tick();
}

void Interpreter::op_FX0A(uint8_t X){
	// A key press is awaited, and then stored in VX.
	_tick();
}

void Interpreter::op_FX15(uint8_t X){
	// Sets the delay timer to VX.
	_tick();
}

void Interpreter::op_FX18(uint8_t X){
	// Sets the sound timer to VX.
	_tick();
}

void Interpreter::op_FX1E(uint8_t X){
	// Adds VX to I.
	_tick();
}

void Interpreter::op_FX29(uint8_t X){
	// Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
	_tick();
}

void Interpreter::op_FX33(uint8_t X){
	// Stores the Binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. 
	_tick();
}

void Interpreter::op_FX55(uint8_t X){
	// Stores V0 to VX in memory starting at address I.
	_tick();
}

void Interpreter::op_FX65(uint8_t X){
	// Fills V0 to VX with values from memory starting at address I.
	_tick();
}