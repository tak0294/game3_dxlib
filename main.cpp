#include <DxLib.h>
#include "library/Video.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpCmdLine, int nShowCmd)
{
    Video::initialize(640, 480);
	Video::setup();

    int x = 0;
	Video::tiledBgFromFile(Video::BG_1, "dirt2.jpg");
	Video::setBgScrollDirection(Video::BG_1, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
    Video::tiledBgFromFile(Video::BG_2, "Sprite-Logo.png");
	Video::setBgScrollDirection(Video::BG_2, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        //ï`âÊâ¬î\âÊëúÇ…ëŒÇµÇƒèëÇ´çûÇ›
		//Video::drawSpriteToBg(test, x, 0);
		Video::drawBG();
		x+=2;
		
		
//		Video::clearBG();
    }

    DxLib_End();
    return 0;
}
