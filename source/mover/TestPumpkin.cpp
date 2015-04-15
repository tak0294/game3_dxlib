#include "mover/TestPumpkin.hpp"

void TestPumpkin::update() {
	Mover::update();
	this->rotation = this->angle * 3.141592/180;
} 

