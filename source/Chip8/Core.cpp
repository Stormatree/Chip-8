#include "Core.hpp"
#include "Font.hpp"

void Core::_tick(){
	if (ENTRY_POINT <= _pc + 2 && _pc < _program_len + ENTRY_POINT)
		_pc += 2;
}

void Core::_skip(){
	if (ENTRY_POINT <= _pc + 4 && _pc + 4 < _program_len + ENTRY_POINT)
		_pc += 4;
}

void Core::_jump(uint16_t& reg, uint16_t val){
	if (ENTRY_POINT <= val && val < _program_len + ENTRY_POINT)
		reg = val;
}

void Core::reset(){
	std::fill(_memory, _memory + MEMORY_SIZE, 0x0);

	_delay = 0x0;
	_sound = 0x0;

	_pc = ENTRY_POINT;
	_sp = 0x0;
	_i = 0x0;

	_program_len = 0x0;

	for (int i = 0; i < FONT_LENGTH; i++)
		_memory[i] = Font8x5[i];
}

bool Core::load(const char* filepath){
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

void Core::input(uint16_t keys){
	//edit _keys
}

void Core::update(){
	//update timers

	if (_pc < _program_len + ENTRY_POINT)
		operate(_memory[_pc], _memory[_pc + 1]);
}

void Core::render(Screen& screen){
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

void Core::print(){
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