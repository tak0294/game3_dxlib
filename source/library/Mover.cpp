#include "library/Mover.hpp"
#include "library/Video.hpp"
#include <cmath>

Mover::Mover() {
	this->pos = VGet(0, 0, 0);
	this->vel = VGet(0, 0, 0);
	this->speed = VGet(0, 0, 0);
	this->axcel = 2;
	this->scale = VGet(1.0f, 1.0f, 1.0f);
	this->rotation = .0f;
	this->friction = 0.7f;
	
	this->drawLayer = Video::SP_2;	//�`�悷�郌�C���[.
	
	////////////////////////////////////////
	// �i�s����p�x.
	////////////////////////////////////////
	this->angle 		= 0;	//���ۂ̊p�x 
	this->destAngle 	= 0;	//�ړI�̊p�x. 
	this->angleFriction = 0.2;	//�p�x��ύX����x����. 
	
}

void Mover::setTexture(std::string texture_filename) {
	m_texture = LoadGraph(texture_filename.c_str());
	int sp_w, sp_h;
	GetGraphSize(m_texture, &sp_w, &sp_h);
	m_textureSize.x = sp_w;
	m_textureSize.y = sp_h;
}

void Mover::draw() {
	Video::drawSprite(this->drawLayer, this->pos.x, this->pos.y, this->m_textureSize.x/2, this->m_textureSize.y/2, this->scale.x, this->scale.y, this->rotation, this->m_texture, FALSE);
}

void Mover::update() {
	
	//vel�x�N�g����P�ʃx�N�g���i���p�̂݁j�ɕϊ�����. 
	float vs = VSize(vel);
	if(vs != 0) {
		vel.x /= vs;
		vel.y /= vs;
		
		//�P�ʃx�N�g���ɑ��x��������. 
		speed.x += vel.x * axcel;
		speed.y += vel.y * axcel;
		vel.x = 0;
		vel.y = 0;
	}
			
	//���W���X�V����. 
	pos.x += speed.x;
	pos.y += speed.y;
	speed.x *= friction;
	speed.y *= friction;
}

void Mover::updateAngleToVel() {
	this->angle += (this->destAngle - this->angle) * this->angleFriction;
	float x = cos(0.01745329251 * (this->angle-90.0));
	float y = sin(0.01745329251 * (this->angle-90.0));
	vel.x = x;
	vel.y = y;
}

void Mover::setAngle(float angle) {
	this->destAngle = angle;
	if(abs(this->destAngle - this->angle) > 180) {
		this->angle += 360;
	}
	// �p�x����i�s�x�N�g�����X�V. 
	updateAngleToVel();
}

void Mover::addAngle(float angle) {
	this->destAngle += angle;
	// �p�x����i�s�x�N�g�����X�V. 
	updateAngleToVel();
	
}

