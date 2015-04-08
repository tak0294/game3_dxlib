#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <DxLib.h>

/***************************************************************************************
 * InputSystem Class.
 ***************************************************************************************/
class InputSystem {
private:

public:
	static bool isLeft;
	static bool isRight;
	static bool isUp;
	static bool isDown;
	static bool isA;
	static bool isB;
	static bool isESC;

	static void updateKeyState();
	static void initialize();
};

#endif
