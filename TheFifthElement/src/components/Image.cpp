#include "Image.h"

Image::Image(Texture* tex) {
	tex_ = tex;
}

// Destructora
Image::~Image() {  }

void Image::initComponent() { 	// Inicializa el componente
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void Image::update() {

}

// Dibuja en escena
void Image::render() {
	Vector2D a = { tr_->getPos().getX() - mngr_->camRect_.x, tr_->getPos().getY() - mngr_->camRect_.y };
	SDL_Rect dest = build_sdlrect(a, (tr_->getW() * tr_->getSize() * WIN_WIDTH)/900, (tr_->getH() * tr_->getSize() * WIN_HEIGHT)/600);
	tex_->render(dest);
}
