#include "mover/TestPumpkin.hpp"

void TestPumpkin::update() {
	Mover::update();
	clsDx();
	printfDx("%f, %f", this->angle, this->destAngle);
	this->rotation = this->angle * 3.141592/180;
} 

