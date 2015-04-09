#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <DxLib.h>
#include "library/Mover.hpp"

class Particle : public Mover {

	VECTOR m_size;
	float m_gravity;
	float m_friction;
	int m_lifeTime;
	int m_color;
	int m_sprite;
	VECTOR m_spriteSize;
	float m_angle;
	float m_rotateSpeed;

public:
	bool isActive;
	enum ParticleType {
		PARTICLE_CIRCLE = 0,
		PARTICLE_SQUARE = 1,
		PARTICLE_SPRITE = 2,
	};
	ParticleType m_particleType;
	Particle();
	Particle(ParticleType particleType);

	void setParticleType(ParticleType particleType);
	void setSprite(int sprite);
	void setColor(int cl);
	void update();
	void draw();
	void initialize(int x, int y, int size, float gravity, float friction, int maxSpeedX, int maxSpeedY, int lifeTime);

};

#endif
