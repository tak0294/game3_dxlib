#include "library/Mover.hpp"
#include "library/Video.hpp"

Mover::Mover() {
	this->pos = VGet(0, 0, 0);
	this->vel = VGet(0, 0, 0);
	this->speed = 4;
	
	this->scale = VGet(1.0f, 1.0f, 1.0f);
	this->rotation = .0f;
	this->drawLayer = Video::SP_2;
	
	this->friction = 0.98f;
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
	
	//velベクトルを単位ベクトル（方角のみ）に変換する. 
	float vs = VSize(vel);
	if(vs != 0) {
		vel.x /= vs;
		vel.y /= vs;
	}
			
	//単位ベクトルに速度をかける. 
	vel.x *= speed;
	vel.y *= speed;
	
	//座標を更新する. 
	pos.x += vel.x;
	pos.y += vel.y;
	speed *= friction;
}
