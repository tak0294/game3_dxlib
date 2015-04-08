#include <DxLib.h>
#include "library/Video.hpp"
#include "library/Mover.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpCmdLine, int nShowCmd)
{
    Video::initialize(640, 480);
	Video::setup();

	Mover *mover = new Mover();
	mover->setTexture("pumpkin064.png");
	mover->pos.x = 100;
	mover->pos.y = 100;

    int x = 0;
	Video::tiledBgFromFile(Video::BG_1, "dirt2.jpg");
	Video::setBgScrollDirection(Video::BG_1, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
    Video::tiledBgFromFile(Video::BG_2, "Sprite-Logo.png");
	Video::setBgScrollDirection(Video::BG_2, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
	
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
    	Video::clearSpriteLayer();
        //•`‰æ‰Â”\‰æ‘œ‚É‘Î‚µ‚Ä‘‚«ž‚Ý
		//Video::drawSpriteToBg(test, x, 0);
		mover->draw();
		Video::drawSpriteLayer();
		Video::drawBGLayer();
		Video::finishDrawLayer();
		x+=2;
		
		
//		Video::clearBG();
    }

    DxLib_End();
    return 0;
}
