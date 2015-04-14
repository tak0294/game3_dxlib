#ifndef TASK_H
#define TASK_H

#include "library.hpp"
class Task {
public:
	Task *prev;
	Task *next;
	Mover *mover;
	void update();
	void draw();
};

#endif
