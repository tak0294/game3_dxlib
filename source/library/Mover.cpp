#include "library/Mover.hpp"
#include "library/Video.hpp"

Mover::Mover() {
	this->pos = VGet(0, 0, 0);
	this->vel = VGet(0, 0, 0);
	this->scale = VGet(1.0f, 1.0f, 1.0f);
	this->rotation = .0f;
	this->drawLayer = Video::SP_1;
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

}
