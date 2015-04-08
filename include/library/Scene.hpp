#ifndef SCENE_H
#define SCENE_H
#include <DxLib.h>

/***************************************************************************************
 * Scene Class.
 ***************************************************************************************/
class Scene {
public:
	int frame;
	void setup(){
		frame = 0;
	};
	virtual void draw() = 0;
	virtual void update() = 0;
};	

#endif
