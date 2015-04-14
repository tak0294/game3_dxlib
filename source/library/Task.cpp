#include "library/Task.hpp"

void Task::draw() {
	this->mover->draw();
}

void Task::update() {
	this->mover->update();
}
