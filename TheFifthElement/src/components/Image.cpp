#include "Image.h"

Image::Image(Texture* tex) {
	tex_ = tex;
}

// Destructora
Image::~Image() {  }

void Image::initComponent() { 	// Inicializa el componente
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

// Dibuja en escena
void Image::render() {
	Vector2D a = { tr_->getPos().getX() - mngr_->camRect_.x, tr_->getPos().getY() - mngr_->camRect_.y };
	SDL_Rect dest = build_sdlrect(a, tr_->getW(), tr_->getH());
	tex_->render(dest);
}
