#include "library/ParticleSystem.hpp"

ParticleSystem::ParticleSystem() {
	m_maxParticleNum = DEFAULT_PARTICLE_NUM;
	initializeCommonValues();
}

ParticleSystem::ParticleSystem(int maxParticleNum) {
	m_maxParticleNum = maxParticleNum;
	initializeCommonValues();
}

void ParticleSystem::initializeCommonValues() {
	m_makeAtOnce = 5;
	m_minSize = 2;
	m_maxSize = 20;
	m_gravity = 0.1f;
	m_friction = 0.988f;
	m_maxSpeedX = 100;
	m_maxSpeedY = 100;
	m_lifeTime = 50;
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

void ParticleSystem::setMinSize(int minSize) {
	m_minSize = minSize;
}

void ParticleSystem::setMaxSize(int maxSize) {
	m_maxSize = maxSize;
}

void ParticleSystem::setGravity(float gravity) {
	m_gravity = gravity;
}

void ParticleSystem::setFriction(float friction) {
	m_friction = friction;
}

void ParticleSystem::setMaxSpeed(int x, int y) {
	m_maxSpeedX = x;
	m_maxSpeedY = y;
}

void ParticleSystem::setLifeTime(int lifeTime) {
	m_lifeTime = lifeTime;
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
			int size = rand()%m_maxSize + m_minSize;
			m_particles.at(ii)->initialize(x, y, size, m_gravity, m_friction, m_maxSpeedX, m_maxSpeedY, m_lifeTime);
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
