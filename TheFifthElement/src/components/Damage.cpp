#include "Damage.h"

Damage::Damage() {
	for (int i = 0; i < 4; i++) {
		damages.push_back(damage);
	}
}

void Damage::initComponent() {

}

void Damage::update() {

}

void Damage::render() {
	SDL_Rect dest = { position.getX(),position.getY(),width,height };
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = img_height;
	src.w = img_width;
	sword->render(src, dest);
	fuerza = std::to_string(damage);
	f->render(SDLUtils::instance()->renderer(), fuerza, position.getX() + 20, position.getY() + 4, color);
}