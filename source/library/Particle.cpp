#include "library/Particle.hpp"

///////////////////////////////////////////////////
// Particle初期化.
///////////////////////////////////////////////////
Particle::Particle() {
	m_particleType = Particle::PARTICLE_CIRCLE;
	isActive = false;
	m_sprite = -1;
	m_color = GetColor(255, 255, 255);
}

Particle::Particle(ParticleType particleType) {
	m_particleType = particleType;
	isActive = false;
	m_sprite = -1;
	m_color = GetColor(255, 255, 255);
}


///////////////////////////////////////////////////
// Particleセットアップ.
///////////////////////////////////////////////////
void Particle::initialize(int x, int y, int size, float gravity, float friction, int maxSpeedX, int maxSpeedY, int lifeTime) {
	m_gravity = gravity;
	m_friction = friction;
	m_size.x = size;
	m_size.y = size;
	pos.x = x;
	pos.y = y;
	vel.y = (rand()%maxSpeedX-maxSpeedX/2) * 0.1f;
	vel.x = (rand()%maxSpeedY-maxSpeedY/2) * 0.1f;
	isActive = true;
	m_lifeTime = 30 + (rand() % lifeTime);
	m_angle = .0f;
	m_rotateSpeed = (rand()%10-5) / 20.0f;
}

///////////////////////////////////////////////////
// Particle更新.
///////////////////////////////////////////////////
void Particle::update() {
	pos.x+=vel.x;
	pos.y+=vel.y;
	vel.y += m_gravity;
	vel.x *= m_friction;
	vel.y *= m_friction;
	
	m_angle += m_rotateSpeed;
	m_lifeTime--;
	if(m_lifeTime == 0) {
		isActive = false;
	}
}


///////////////////////////////////////////////////
// Particle描画.
///////////////////////////////////////////////////
void Particle::draw() {
	//m_shape.setFillColor(m_color);
	//Video::drawSprite(Video::SP_1, m_shape);
	if(m_particleType == PARTICLE_SQUARE) {
		Video::drawBox( Video::SP_1, pos.x , pos.y , pos.x + m_size.x , pos.y + m_size.y ,m_color , TRUE ) ;
	}else if(m_particleType == PARTICLE_CIRCLE) {
		Video::drawCircle( Video::SP_1, pos.x , pos.y , m_size.x/2 ,m_color , TRUE ) ;
	}else if(m_particleType == PARTICLE_SPRITE) {
		if(m_sprite != -1) {
			Video::drawSprite(Video::SP_1, pos.x, pos.y, m_spriteSize.x/2, m_spriteSize.y/2, m_size.x/m_spriteSize.x, m_size.y/m_spriteSize.y, m_angle, m_sprite, FALSE);
		}
	}
}

///////////////////////////////////////////////////
//	Particleタイプ.
///////////////////////////////////////////////////
void Particle::setParticleType(ParticleType particleType) {
	m_particleType = particleType;
}


///////////////////////////////////////////////////
//	Particleスプライト設定.
///////////////////////////////////////////////////
void Particle::setSprite(int sprite) {
	m_sprite = sprite;
	int sp_w, sp_h;
	GetGraphSize(m_sprite, &sp_w, &sp_h);
	m_spriteSize.x = sp_w;
	m_spriteSize.y = sp_h;
}

///////////////////////////////////////////////////
//	Particle色設定.
///////////////////////////////////////////////////
void Particle::setColor(int cl) {
	m_color = cl;
}
