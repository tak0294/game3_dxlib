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
	void setMakeAtOnceNum(int num);
};

#endif
