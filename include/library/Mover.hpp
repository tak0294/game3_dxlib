#ifndef MOVER_H
#define MOVER_H
#include <string>
#include <DxLib.h>
#include "library/Video.hpp"

class Mover {

	int m_texture;
	VECTOR m_textureSize;
	void updateAngleToVel();

public:
	VECTOR speed;
	float axcel;
	float friction;
	VECTOR pos;
	VECTOR vel;
	VECTOR scale;
	Video::SpriteLayer drawLayer;
	float rotation;
	float angle;
	float destAngle;
	float angleFriction;

	Mover();
	void setTexture(std::string texture_filename);
	virtual void draw();
	virtual void update();
	void setAngle(float angle);
	void addAngle(float angle);
};

#endif
