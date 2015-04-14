#include "mover/TestPumpkin.hpp"

void TestPumpkin::update() {
	Mover::update();
	this->rotation += 0.1f;
} 

