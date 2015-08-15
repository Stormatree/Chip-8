#include "Core.hpp"
#include "Font.hpp"
#include <stdio.h> 

Core::Core(std::string exeLocation){
	_screen.initiate();
	reset();

	Mix_Init(MIX_INIT_OGG);

	Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 4096);

	exeLocation = exeLocation.substr(0, exeLocation.find_last_of("\\") + 1);

	_tone = Mix_LoadMUS((exeLocation + "..\\asset\\squarewave.ogg").c_str());

	if (!_tone)
		printf("Audio disabled. %s\n", Mix_GetError());

	if (_tone){
		Mix_PlayMusic(_tone, -1);
		Mix_PauseMusic();
	}
}

Core::~Core(){
	Mix_FreeMusic(_tone);
}

void Core::reset(){
	std::fill(_memory, _memory + sizeof(_memory) / sizeof(uint8_t), 0);

	std::fill(_var, _var + sizeof(_var) / sizeof(uint8_t), 0);
	std::fill(_key, _key + sizeof(_key) / sizeof(uint8_t), 0);

	_00E0(); // Clear the screen

	std::fill(_stack, _stack + sizeof(_stack) / sizeof(uint16_t), 0);
	
	_pc = _entryPoint;
	_sp = 0;
	_i = 0;

	_delay = 0;
	_sound = 0;

	_length = 0;

	for (int i = 0; i < sizeof(Font4x5) / sizeof(uint8_t); i++)
		_memory[i] = Font4x5[i];
}

bool Core::load(const char* filepath){
	std::ifstream file(filepath, std::fstream::binary);

	if (file){
		int i = _entryPoint;

		for (; file.peek() != EOF; i++){
			_memory[i] = file.get();
		}

		_length = i - _entryPoint;

		return true;
	}
	else{
		printf("No such file '%s'!\n", filepath);
		return false;
	}
}

Screen& Core::screen(){
	return _screen;
}

// Keymapping
// 1234	   123C
// QWER == 456D
// ASDF == 789E
// ZXCV	   A0BF

void Core::input(){
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
			_running = false;
		}
	}

	std::fill(_key, _key + sizeof(_key) / sizeof(uint8_t), 0);

	const uint8_t* keyDown = SDL_GetKeyboardState(0);

	if (keyDown[SDL_SCANCODE_1])
		_key[1] = 0xFF;
	if (keyDown[SDL_SCANCODE_2])
		_key[2] = 0xFF;
	if (keyDown[SDL_SCANCODE_3])
		_key[3] = 0xFF;
	if (keyDown[SDL_SCANCODE_4])
		_key[0xC] = 0xFF;
	if (keyDown[SDL_SCANCODE_Q])
		_key[4] = 0xFF;
	if (keyDown[SDL_SCANCODE_W])
		_key[5] = 0xFF;
	if (keyDown[SDL_SCANCODE_E])
		_key[6] = 0xFF;
	if (keyDown[SDL_SCANCODE_R])
		_key[0xD] = 0xFF;
	if (keyDown[SDL_SCANCODE_A])
		_key[7] = 0xFF;
	if (keyDown[SDL_SCANCODE_S])
		_key[8] = 0xFF;
	if (keyDown[SDL_SCANCODE_D])
		_key[9] = 0xFF;
	if (keyDown[SDL_SCANCODE_F])
		_key[0xE] = 0xFF;
	if (keyDown[SDL_SCANCODE_Z])
		_key[0xA] = 0xFF;
	if (keyDown[SDL_SCANCODE_X])
		_key[0] = 0xFF;
	if (keyDown[SDL_SCANCODE_C])
		_key[0xB] = 0xFF;
	if (keyDown[SDL_SCANCODE_V])
		_key[0xF] = 0xFF;
}

void Core::update(){
	if (_running){
		//Update timers and pc
		if (_pc <= _entryPoint + _length)
			operate(_memory[_pc], _memory[_pc + 1]);
		else
			_running = false;

		if (_delay > 0)
			_delay--;

		if (_sound > 0)
			_sound--;
	}
}

bool Core::running(){
	return _running;
}

void Core::output(){
	//Output screen and buzzer
	for (int y = 0; y < _bufferHeight; y++){
		for (int x = 0; x < _bufferWidth; x++){
			if (_buffer[y][x])
				_screen.drawPixel(x, y);
			else
				_screen.drawPixel(x, y, false);
		}
	}

	_screen.render();

	if (_tone){
		if (_sound != 0)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
}

void Core::print(){
	for (int i = 0; i < sizeof(_memory) / sizeof(uint8_t); i++){
		if (i % 16 == 0)
			if (!i)
				printf("% 5d : ", i);
			else
				printf("\n% 5d : ", i);

		printf("%02X ", _memory[i]);
	}

	printf("\n");
}

bool Core::operate(uint8_t lower, uint8_t upper){
	uint8_t nibbles[4] = { lower >> 4, lower & 0xF, upper >> 4, upper & 0xF };
	uint16_t tail = ((lower << 8) | upper) & 0x0FFF;

	_pc += 2;

	switch (nibbles[0]){
	case 0x0:
		switch (upper){
		case 0xE0: _00E0(); return true;
			case 0xEE: _00EE(); return true;
			default: _0NNN(tail); return true;
		}

	case 0x1: _1NNN(tail); return true;
	case 0x2: _2NNN(tail); return true;
	case 0x3: _3XNN(nibbles[1], upper); return true;
	case 0x4: _4XNN(nibbles[1], upper); return true;
	case 0x5: _5XY0(nibbles[1], nibbles[2]); return true;
	case 0x6: _6XNN(nibbles[1], upper); return true;
	case 0x7: _7XNN(nibbles[1], upper); return true;

	case 0x8:
		switch (nibbles[3]){
			case 0x0: _8XY0(nibbles[1], nibbles[2]); return true;
			case 0x1: _8XY1(nibbles[1], nibbles[2]); return true;
			case 0x2: _8XY2(nibbles[1], nibbles[2]); return true;
			case 0x3: _8XY3(nibbles[1], nibbles[2]); return true;
			case 0x4: _8XY4(nibbles[1], nibbles[2]); return true;
			case 0x5: _8XY5(nibbles[1], nibbles[2]); return true;
			case 0x6: _8XY6(nibbles[1], nibbles[2]); return true;
			case 0x7: _8XY7(nibbles[1], nibbles[2]); return true;
			case 0xE: _8XYE(nibbles[1], nibbles[2]); return true;
			default: return false;
		}

	case 0x9: _9XY0(nibbles[1], nibbles[2]); return true;
	case 0xA: _ANNN(tail); return true;
	case 0xB: _BNNN(tail); return true;
	case 0xC: _CXNN(nibbles[1], upper); return true;
	case 0xD: _DXYN(nibbles[1], nibbles[2], nibbles[3]); return true;

	case 0xE:
		switch (upper){
			case 0x9E: _EX9E(nibbles[1]); return true;
			case 0xA1: _EXA1(nibbles[1]); return true;
			default: return false;
		}

	case 0xF:
		switch (upper){
			case 0x07: _FX07(nibbles[1]); return true;
			case 0x0A: _FX0A(nibbles[1]); return true;
			case 0x15: _FX15(nibbles[1]); return true;
			case 0x18: _FX18(nibbles[1]); return true;
			case 0x1E: _FX1E(nibbles[1]); return true;
			case 0x29: _FX29(nibbles[1]); return true;
			case 0x33: _FX33(nibbles[1]); return true;
			case 0x55: _FX55(nibbles[1]); return true;
			case 0x65: _FX65(nibbles[1]); return true;
			default: return false;
		}
	}


	printf("%02X%02X\n", upper, lower);
	return false;
}