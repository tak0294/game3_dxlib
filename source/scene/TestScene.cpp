#include "library.hpp"
#include "scene/TestScene.hpp"

void TestScene::setup() {
	Scene::setup();

	///////////////////////////////////////////////////////
	//	BG Layers.
	///////////////////////////////////////////////////////
	Video::tiledBgFromFile(Video::BG_1, "dirt2.jpg");
	Video::setBgScrollSpeed(Video::BG_1, 1);
	Video::setBgScrollDirection(Video::BG_1, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 200 ) ;
	Video::drawBox(Video::BG_2, 0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
	
	Video::drawBox(Video::BG_2, 200, 0, 400, 480, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;
	
	SetTransColor(255, 255, 255);
	int bg = LoadGraph("bg.png");
	int bg_div = DerivationGraph(0,0,270,240,bg);
    Video::bgFromGraph(Video::BG_3, bg_div, 0, 0, 540, 480);
	


	///////////////////////////////////////////////////////
	//  Make mover object.
	///////////////////////////////////////////////////////
	mover2 = new TestPumpkin();
	mover2->setTexture("pumpkin064.png");
	mover2->pos.y = 250;
	mover2->scale.x = mover2->scale.y = 1.5f;
	mover2->drawLayer = Video::SP_2;



	///////////////////////////////////////////////////////
	//	ParticleSystem setup.
	///////////////////////////////////////////////////////
	psys = new ParticleSystem(128);
	psys->initialize();
	
	task = new Task();
	task->mover = mover2;
}

void TestScene::draw() {
	Video::drawString(Video::UI_1, 100, 100, "�e�L�X�g", GetColor(255,255,255), 16);
	Video::drawBox(Video::UI_1, 0, 0, 638, 478, GetColor(255,255,255), FALSE);
	psys->draw();
	task->draw();
//	this->mover2->draw();

//	Video::drawText("TEXT!!", Video::FONT_NORMAL, 200, 400, 100);
}

void TestScene::update() {
	if(InputSystem::isRight) {
		mover2->setAngle(90);
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	if(InputSystem::isLeft) {
		mover2->setAngle(270);
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	if(InputSystem::isDown) {
		mover2->setAngle(180);
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	if(InputSystem::isUp) {
		mover2->setAngle(0);
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	
	if(InputSystem::isRight && InputSystem::isUp) {
		mover2->setAngle(45);
	}
	if(InputSystem::isRight && InputSystem::isDown) {
		mover2->setAngle(135);
	}
	if(InputSystem::isLeft && InputSystem::isUp) {
		mover2->setAngle(315);
	}
	if(InputSystem::isLeft && InputSystem::isDown) {
		mover2->setAngle(225);
	}
	
	if(InputSystem::isA) {
		psys->add(mover2->pos.x, mover2->pos.y);
		mover2->addAngle(10);
		//mover2->scale.x = mover2->scale.y = 7;
//		Video::clearBg(Video::BG_1);
	}
	psys->update();
//	mover2->update();
	task->update();
	frame++;
}
