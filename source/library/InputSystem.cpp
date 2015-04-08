#include "library/InputSystem.hpp"

/**
 * Declare real symbols.
 */
bool InputSystem::isLeft;
bool InputSystem::isRight;
bool InputSystem::isUp;
bool InputSystem::isDown;
bool InputSystem::isA;
bool InputSystem::isB;
bool InputSystem::isESC;

void InputSystem::initialize() {
	InputSystem::isLeft = false;
	InputSystem::isRight = false;
	InputSystem::isUp = false;
	InputSystem::isDown = false;
	InputSystem::isA = false;
	InputSystem::isB = false;
	InputSystem::isESC = false;
}

void InputSystem::updateKeyState() {

	char Buf[256];
	GetHitKeyStateAll(Buf);
	
	InputSystem::initialize();
	
	if(Buf[KEY_INPUT_UP] == 1) {
		isUp = true;
	}
	if(Buf[KEY_INPUT_DOWN] == 1) {
		isDown = true;
	}
	if(Buf[KEY_INPUT_LEFT] == 1) {
		isLeft = true;
	}
	if(Buf[KEY_INPUT_RIGHT] == 1) {
		isRight = true;
	}
	if(Buf[KEY_INPUT_Z] == 1) {
		isA = true;
	}
	if(Buf[KEY_INPUT_X] == 1) {
		isB = true;
	}
	if(Buf[KEY_INPUT_ESCAPE] == 1) {
		isESC = true;
	}
}
