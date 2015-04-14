#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "library.hpp"
#include "mover/TestPumpkin.hpp"


/***************************************************************************************
 * TestScene Class.
 ***************************************************************************************/
class TestScene : public Scene {
	TestPumpkin *mover2;
	Task *task;
	ParticleSystem *psys;
public:
	void setup();
	void draw();
	void update();
};
#endif
