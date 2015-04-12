#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <string>
#include <vector>
#include <DxLib.h>
#include "library/Particle.hpp"

const int DEFAULT_PARTICLE_NUM = 256;

class ParticleSystem {
private:
	int m_maxParticleNum;
	std::vector<Particle*> m_particles;
	std::vector<int> m_colors;
	int m_makeAtOnce;
	int m_minSize;
	int m_maxSize;
	float m_gravity;
	float m_friction;
	void initializeCommonValues();
	int m_maxSpeedX;
	int m_maxSpeedY;
	int m_lifeTime;

public:
	ParticleSystem();
	ParticleSystem(int maxParticleNum);
	void initialize();
	void initialize(int sprite);
	void initialize(Particle::ParticleType particleType);
	void addColor(int cl);
	void setSprite(int sprite);
	void draw();
	void update();
	void add(int x, int y);
	void setTexture(int sprite);
	void setMakeAtOnceNum(int num);
	void setMinSize(int minSize);
	void setMaxSize(int maxSize);
	void setGravity(float gravity);
	void setFriction(float friction);
	void setMaxSpeed(int x, int y);
	void setLifeTime(int lifeTime);
};

#endif
