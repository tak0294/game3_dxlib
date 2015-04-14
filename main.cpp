#include <DxLib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "library.hpp"

#include "scene/TestScene.hpp"
#include "mover/TestPumpkin.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GameManager *gameManager;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpCmdLine, int nShowCmd)
{
	gameManager = new GameManager(WINDOW_WIDTH, WINDOW_HEIGHT);
	TestScene *s = new TestScene();
	s->setup();
	gameManager->setScene(s);
	gameManager->start();
	
    DxLib_End();
    return 0;
}
