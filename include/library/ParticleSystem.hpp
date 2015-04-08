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

public:
	ParticleSystem();
	ParticleSystem(int maxParticleNum);
	void initialize();
	void addColor(int cl);
	void draw();
	void update();
	void add(int x, int y);
};

#endif
