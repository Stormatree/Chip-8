#include "Core.hpp"

// Names and descriptions sourced from CHIP-8 Wikipedia article
// http://en.wikipedia.org/wiki/CHIP-8

void Core::_00E0(){
	// Calls RCA 1802 program at address NNN.
	_tick();
}

void Core::_00EE(){
	// Clears the screen.
	_tick();
}

void Core::_0NNN(uint16_t NNN){
	// Returns from a subroutine.
	_tick();
}

void Core::_1NNN(uint16_t NNN){
	// Jumps to address NNN.
	_tick();
}

void Core::_2NNN(uint16_t NNN){
	// Calls subroutine at NNN.
	_tick();
}

void Core::_3XNN(uint8_t VX, uint8_t NN){
	// Skips the next instruction if VX equals NN.
	_tick();
}

void Core::_4XNN(uint8_t VX, uint8_t NN){
	// Skips the next instruction if VX doesn't equal NN.
	_tick();
}

void Core::_5XY0(uint8_t VX, uint8_t VY){
	// Skips the next instruction if VX equals VY.
	_tick();
}

void Core::_6XNN(uint8_t VX, uint8_t NN){
	// Sets VX to NN.
	_tick();
}

void Core::_7XNN(uint8_t VX, uint8_t NN){
	// Adds NN to VX.
	_tick();
}

void Core::_8XY0(uint8_t VX, uint8_t VY){
	// Sets VX to the value of VY.
	_tick();
}

void Core::_8XY1(uint8_t VX, uint8_t VY){
	// Sets VX to VX or VY.
	_tick();
}

void Core::_8XY2(uint8_t VX, uint8_t VY){
	// Sets VX to VX and VY.
	_tick();
}

void Core::_8XY3(uint8_t VX, uint8_t VY){
	// Sets VX to VX xor VY.
	_tick();
}

void Core::_8XY4(uint8_t VX, uint8_t VY){
	// Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
	_tick();
}

void Core::_8XY5(uint8_t VX, uint8_t VY){
	// VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
	_tick();
}

void Core::_8XY6(uint8_t VX, uint8_t VY){
	// Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
	_tick();
}

void Core::_8XY7(uint8_t VX, uint8_t VY){
	// Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
	_tick();
}

void Core::_8XYE(uint8_t VX, uint8_t VY){
	// Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.
	_tick();
}

void Core::_9XY0(uint8_t VX, uint8_t VY){
	// Skips the next instruction if VX doesn't equal VY.
	_tick();
}

void Core::_ANNN(uint16_t NNN){
	// Sets I to the address NNN.
	_tick();
}

void Core::_BNNN(uint16_t NNN){
	// Jumps to the address NNN plus V0.
	_tick();
}

void Core::_CXNN(uint8_t VX, uint8_t NN){
	// Sets VX to a random number, masked by NN.
	_tick();
}

void Core::_DXYN(uint8_t VX, uint8_t VY, uint8_t N){
	// Sprites stored in memory at location in index register (I), maximum 8bits wide. Wraps around the screen. If when drawn, clears a pixel, register VF is set to 1 otherwise it is zero.
	_tick();
}

void Core::_EX9E(uint8_t VX){
	// Skips the next instruction if the key stored in VX is pressed.
	_tick();
}

void Core::_EXA1(uint8_t VX){
	// Skips the next instruction if the key stored in VX isn't pressed.
	_tick();
}

void Core::_FX07(uint8_t VX){
	// Sets VX to the value of the delay timer.
	_tick();
}

void Core::_FX0A(uint8_t VX){
	// A key press is awaited, and then stored in VX.
	_tick();
}

void Core::_FX15(uint8_t VX){
	// Sets the delay timer to VX.
	_tick();
}

void Core::_FX18(uint8_t VX){
	// Sets the sound timer to VX.
	_tick();
}

void Core::_FX1E(uint8_t VX){
	// Adds VX to I.
	_tick();
}

void Core::_FX29(uint8_t VX){
	// Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
	_tick();
}

void Core::_FX33(uint8_t VX){
	// Stores the Binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. 
	_tick();
}

void Core::_FX55(uint8_t VX){
	// Stores V0 to VX in memory starting at address I.
	_tick();
}

void Core::_FX65(uint8_t VX){
	// Fills V0 to VX with values from memory starting at address I.
	_tick();
}