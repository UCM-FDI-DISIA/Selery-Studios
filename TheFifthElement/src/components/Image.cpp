#include "Image.h"
#include "../Entities/EnemyBEU.h"

Image::Image(Texture* tex) {
	tex_ = tex;
}

// Destructora
Image::~Image() { }

void Image::initComponent() { 	// Inicializa el componente
	if (tr_ == nullptr) tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	assert(tr_ != nullptr);
}

void Image::update() {

}

// Dibuja en escena
void Image::render() {
	Vector2D a = {tr_->getPos().getX() - mngr_->camRect_.x, tr_->getPos().getY() - mngr_->camRect_.y};
	SDL_Rect dest = build_sdlrect(a, tr_->getW(), tr_->getH());
	tex_->render(dest);
}
