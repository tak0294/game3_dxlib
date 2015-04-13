#ifndef MOVER_H
#define MOVER_H
#include <string>
#include <DxLib.h>
#include "library/Video.hpp"

class Mover {

	int m_texture;
	VECTOR m_textureSize;

public:
	VECTOR speed;
	float axcel;
	float friction;
	VECTOR pos;
	VECTOR vel;
	VECTOR scale;
	Video::SpriteLayer drawLayer;
	float rotation;


	Mover();
	void setTexture(std::string texture_filename);
	void draw();
	void update();
};

#endif
