#include <DxLib.h>
#include "library/Video.hpp"
#include "library/Mover.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpCmdLine, int nShowCmd)
{
    Video::initialize(640, 480);

	Mover *mover = new Mover();
	mover->setTexture("pumpkin064.png");
	mover->pos.x = 300;
	mover->pos.y = 250;
	mover->drawLayer = Video::SP_1;
	mover->scale.x = 4;
	mover->scale.y = 4;


	Video::tiledBgFromFile(Video::BG_1, "dirt2.jpg");
	Video::setBgScrollDirection(Video::BG_1, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
    Video::tiledBgFromFile(Video::BG_2, "Sprite-Logo.png");
	Video::setBgScrollDirection(Video::BG_2, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
	    
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
    	Video::clearSpriteLayer();

		mover->draw();

		Video::drawBGLayer();
		Video::drawSpriteLayer();
		Video::finishDrawLayer();
		Video::clearSpriteLayer();
		mover->rotation += 0.02f;

    }

    DxLib_End();
    return 0;
}
