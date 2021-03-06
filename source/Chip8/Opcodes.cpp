#include "Core.hpp"

// Names and descriptions sourced from CHIP-8 Wikipedia article
// http://en.wikipedia.org/wiki/CHIP-8

void Core::_00E0(){
	// Clears the screen.
	for (int y = 0; y < _bufferHeight; y++){
		for (int x = 0; x < _bufferWidth; x++){
			_buffer[y][x] = 0;
		}
	}
}

void Core::_00EE(){
	// Returns from a subroutine.
	_sp--;
	_pc = _stack[_sp];
}

void Core::_1NNN(uint16_t NNN){
	// Jumps to address NNN.
	_pc = NNN;
}

void Core::_2NNN(uint16_t NNN){
	// Calls subroutine at NNN.
	_stack[_sp] = _pc;
	_sp++;
	_pc = NNN;
}

void Core::_3XNN(uint8_t VX, uint8_t NN){
	// Skips the next instruction if VX equals NN.
	if (_var[VX] == NN)
		_pc += 2;
}

void Core::_4XNN(uint8_t VX, uint8_t NN){
	// Skips the next instruction if VX doesn't equal NN.
	if (_var[VX] != NN)
		_pc += 2;
}

void Core::_5XY0(uint8_t VX, uint8_t VY){
	// Skips the next instruction if VX equals VY.
	if (_var[VX] == _var[VY])
		_pc += 2;
}

void Core::_6XNN(uint8_t VX, uint8_t NN){
	// Sets VX to NN.
	_var[VX] = NN;
}

void Core::_7XNN(uint8_t VX, uint8_t NN){
	// Adds NN to VX.
	_var[VX] = _var[VX] + NN;
}

void Core::_8XY0(uint8_t VX, uint8_t VY){
	// Sets VX to the value of VY.
	_var[VX] = _var[VY];
}

void Core::_8XY1(uint8_t VX, uint8_t VY){
	// Sets VX to VX or VY.
	_var[VX] = _var[VX] | _var[VY];
}

void Core::_8XY2(uint8_t VX, uint8_t VY){
	// Sets VX to VX and VY.
	_var[VX] = _var[VX] & _var[VY];
}

void Core::_8XY3(uint8_t VX, uint8_t VY){
	// Sets VX to VX xor VY.
	_var[VX] = _var[VX] ^ _var[VY];
}

void Core::_8XY4(uint8_t VX, uint8_t VY){
	// Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
	if (_var[VX] + _var[VY] > 0xFF)
		_var[0xF] = 1;
	else
		_var[0xF] = 0;

	_var[VX] = _var[VX] + _var[VY];
}

void Core::_8XY5(uint8_t VX, uint8_t VY){
	// VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
	if (_var[VX] >= _var[VY])
		_var[0xF] = 1;
	else
		_var[0xF] = 0;

	_var[VX] = _var[VX] - _var[VY];
}

void Core::_8XY6(uint8_t VX, uint8_t VY){
	// Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
	_var[0xF] = _var[0xF] & 0x01;
	_var[VX] = _var[VX] >> 1;
}

void Core::_8XY7(uint8_t VX, uint8_t VY){
	// Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
	if (_var[VX] <= _var[VY])
		_var[0xF] = 1;
	else
		_var[0xF] = 0;

	_var[VX] = _var[VY] - _var[VX];
}

void Core::_8XYE(uint8_t VX, uint8_t VY){
	// Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.
	_var[0xF] = (_var[VX] >> 7) & 0x01;
	_var[VX] = _var[VX] << 1;
}

void Core::_9XY0(uint8_t VX, uint8_t VY){
	// Skips the next instruction if VX doesn't equal VY.
	if (_var[VX] != _var[VY])
		_pc += 2;
}

void Core::_ANNN(uint16_t NNN){
	// Sets I to the address NNN.
	_i = NNN;
}

void Core::_BNNN(uint16_t NNN){
	// Jumps to the address NNN plus V0.
	_pc = NNN + _var[0];
}

void Core::_CXNN(uint8_t VX, uint8_t NN){
	// Sets VX to a random number, masked by NN.
	_var[VX] = (rand() % 255) & NN;
}

void Core::_DXYN(uint8_t VX, uint8_t VY, uint8_t N){
	// Sprites stored in memory at location in index register (I), maximum 8bits wide. Wraps around the screen. If when drawn, clears a pixel, register VF is set to 1 otherwise it is zero.
	_var[0xF] = 0;

	for (uint8_t y = 0; y < N; y++){
		uint8_t line = _memory[_i + y];

		for (uint8_t x = 0; x < 8; x++){
			if (line & (0x80 >> x)){
				uint8_t posX = (_var[VX] + x) % _bufferWidth;
				uint8_t posY = (_var[VY] + y) % _bufferHeight;

				if (_buffer[posY][posX] != 0)
					_var[0xF] = 1;

				_buffer[posY][posX] ^= 1;
			}
		}
	}
}

void Core::_EX9E(uint8_t VX){
	// Skips the next instruction if the key stored in VX is pressed.
	if (_key[_var[VX]])
		_pc += 2;
}

void Core::_EXA1(uint8_t VX){
	// Skips the next instruction if the key stored in VX isn't pressed.
	if (!_key[_var[VX]])
		_pc += 2;
}

void Core::_FX07(uint8_t VX){
	// Sets VX to the value of the delay timer.
	_var[VX] = _delay;
}

void Core::_FX0A(uint8_t VX){
	// A key press is awaited, and then stored in VX.
	_pc -= 2;

	for (int i = 0; i < 16; i++){
		if (_key[i]){
			_var[VX] = _key[i];
			_pc += 2;
		}
	}
}

void Core::_FX15(uint8_t VX){
	// Sets the delay timer to VX.
	_delay = _var[VX];
}

void Core::_FX18(uint8_t VX){
	// Sets the sound timer to VX.
	_sound = _var[VX] + 32;
}

void Core::_FX1E(uint8_t VX){
	// Adds VX to I.
	_i = _i + _var[VX];
}

void Core::_FX29(uint8_t VX){
	// Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
	_i = 5 * _var[VX];
}

void Core::_FX33(uint8_t VX){
	// Stores the Binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2.
	_memory[_i] = int(_var[VX] / 100);
	_memory[_i + 1] = int((_var[VX] - _memory[_i] * 100) / 10);
	_memory[_i + 2] = int(_var[VX] - _memory[_i] * 100 - _memory[_i + 1] * 10);
}

void Core::_FX55(uint8_t VX){
	// Stores V0 to VX in memory starting at address I.
	for (uint8_t i = 0; i <= VX; i++)
		_memory[_i + i] = _var[i];
}

void Core::_FX65(uint8_t VX){
	// Fills V0 to VX with values from memory starting at address I.
	for (uint8_t i = 0; i <= VX; i++)
		_var[i] = _memory[_i + i];
}