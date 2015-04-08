#include "library/Particle.hpp"

///////////////////////////////////////////////////
// Particle初期化.
///////////////////////////////////////////////////
Particle::Particle() {
	m_particleType = Particle::PARTICLE_CIRCLE;
	isActive = false;
	m_color = GetColor(255, 255, 255);
}

Particle::Particle(ParticleType particleType) {
	m_particleType = particleType;
	isActive = false;
	m_color = GetColor(255, 255, 255);
}


///////////////////////////////////////////////////
// Particleセットアップ.
///////////////////////////////////////////////////
void Particle::initialize(int x, int y) {
	m_gravity = 0.1f;
	m_friction = 0.998f;
	float size = rand()%10 + 2;
	m_size.x = size;
	m_size.y = size;
//	m_shape.setSize(sf::Vector2f(size, size));
	//m_shape.setPosition(400, 400);
	pos.x = x;
	pos.y = y;
	vel.y = (rand()%100-50) * 0.1f;
	vel.x = (rand()%100-50) * 0.1f;
	isActive = true;
	m_lifeTime = 30 + (rand() % 50);
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
	
	//m_shape.setPosition(pos);
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
	DrawBox( pos.x , pos.y , pos.x + m_size.x , pos.y + m_size.y ,m_color , TRUE ) ;

}

///////////////////////////////////////////////////
//	Particle色設定.
///////////////////////////////////////////////////
void Particle::setColor(int cl) {
	m_color = cl;
}
