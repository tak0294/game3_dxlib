#include <DxLib.h>
#include "library/Video.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpCmdLine, int nShowCmd)
{
    Video::initialize(640, 480);
	Video::setup();

    int x = 0;
	Video::tiledBgFromFile(Video::BG_1, "pumpkin064.png");
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        //•`‰æ‰Â”\‰æ‘œ‚É‘Î‚µ‚Ä‘‚«‚İ
		//Video::drawSpriteToBg(test, x, 0);
		Video::drawBG();
		x+=2;
		
		
//		Video::clearBG();
    }

    DxLib_End();
    return 0;
}
