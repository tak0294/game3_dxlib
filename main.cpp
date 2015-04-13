#include <DxLib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "library/GameManager.hpp"
#include "library/Scene.hpp"
#include "library/Mover.hpp"
#include "library/ParticleSystem.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GameManager *gameManager;


/***************************************************************************************
 * TestPumpkin Class.
 ***************************************************************************************/
class TestPumpkin : public Mover {

public:
	void update();
};

void TestPumpkin::update() {
	Mover::update();
	this->rotation += 0.1f;
} 





/***************************************************************************************
 * TestScene Class.
 ***************************************************************************************/
class TestScene : public Scene {
	TestPumpkin *mover2;
	ParticleSystem *psys;
public:
	void setup();
	void draw();
	void update();
};

void TestScene::setup() {
	Scene::setup();

	///////////////////////////////////////////////////////
	//	BG Layers.
	///////////////////////////////////////////////////////
	Video::tiledBgFromFile(Video::BG_1, "dirt2.jpg");
	Video::setBgScrollSpeed(Video::BG_1, 1);
	Video::setBgScrollDirection(Video::BG_1, Video::DIRECTION_RIGHT | Video::DIRECTION_DOWN);
	
	Video::drawBox(Video::BG_2, 0, 0, 640, 460, GetColor(200, 200, 200), TRUE);
	SetTransColor(255, 255, 255);
	int bg = LoadGraph("bg.png");
	int bg_div = DerivationGraph(0,0,270,240,bg);
    Video::bgFromGraph(Video::BG_2, bg_div, 0, 0, 540, 480);
	
	mover2 = new TestPumpkin();
	mover2->setTexture("pumpkin064.png");
	mover2->pos.y = 250;
	mover2->scale.x = mover2->scale.y = 1.5f;
	mover2->drawLayer = Video::SP_2;

	int graph = LoadGraph("pumpkin064.png");

	///////////////////////////////////////////////////////
	//	ParticleSystem setup.
	///////////////////////////////////////////////////////
	psys = new ParticleSystem(128);
	psys->initialize();
}

void TestScene::draw() {
	Video::drawString(Video::UI_1, 100, 100, "テキスト", GetColor(255,255,255), 16);
	Video::drawBox(Video::UI_1, 0, 0, 638, 478, GetColor(255,255,255), FALSE);
	psys->draw();
	this->mover2->draw();
//	Video::drawText("TEXT!!", Video::FONT_NORMAL, 200, 400, 100);
}

void TestScene::update() {
	if(InputSystem::isRight) {
		mover2->vel.x = 1.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	if(InputSystem::isLeft) {
		mover2->vel.x = -1.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}
	if(InputSystem::isDown) {
		mover2->vel.y = 1.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}

	if(InputSystem::isUp) {
		mover2->vel.y = -1.0f;
		psys->add(mover2->pos.x, mover2->pos.y);
	}

	if(InputSystem::isA) {
		//mover2->scale.x = mover2->scale.y = 7;
//		Video::clearBg(Video::BG_1);
	}
	psys->update();
	mover2->update();
	frame++;
}




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
