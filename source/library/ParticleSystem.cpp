#include "library/ParticleSystem.hpp"

ParticleSystem::ParticleSystem() {
	m_maxParticleNum = DEFAULT_PARTICLE_NUM;
	m_makeAtOnce = 5;
}

ParticleSystem::ParticleSystem(int maxParticleNum) {
	m_maxParticleNum = maxParticleNum;
	m_makeAtOnce = 5;
}

void ParticleSystem::initialize(int sprite) {
	
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		Particle *p = new Particle(Particle::PARTICLE_SPRITE);
		p->setSprite(sprite);
		m_particles.push_back(p);
	}
}

void ParticleSystem::initialize(Particle::ParticleType particleType) {
	
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		Particle *p = new Particle(particleType);
		m_particles.push_back(p);
	}
}

void ParticleSystem::initialize() {
	
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		Particle *p = new Particle();
		m_particles.push_back(p);
	}
}

void ParticleSystem::addColor(int cl) {
	m_colors.push_back(cl);
}

void ParticleSystem::setSprite(int sprite) {
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		m_particles.at(ii)->setSprite(sprite);
		m_particles.at(ii)->setParticleType(Particle::PARTICLE_SPRITE);
	}
}

void ParticleSystem::draw() {
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		if(m_particles.at(ii)->isActive) {
			m_particles.at(ii)->draw();
		}
	}
 }


void ParticleSystem::update() {
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		if(m_particles.at(ii)->isActive) {
			m_particles.at(ii)->update();
		}
	}
}

void ParticleSystem::setMakeAtOnceNum(int num) {
	m_makeAtOnce = num;
}

void ParticleSystem::add(int x, int y) {
	int makeCount = 0;
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		if(!m_particles.at(ii)->isActive) {
			m_particles.at(ii)->initialize(x, y);
			if(m_colors.size() > 0) {
				int color_key = rand() % m_colors.size();
				m_particles.at(ii)->setColor(m_colors[color_key]);
			}
			makeCount++;
			if(makeCount == m_makeAtOnce) {
				break;
			}
		}
	}
}
