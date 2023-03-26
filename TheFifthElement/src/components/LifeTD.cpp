#include "LifeTD.h"

LifeTD::LifeTD() {

}

void LifeTD::initComponent() {

}

void LifeTD::update() {

}

void LifeTD::render() {
	SDL_Rect dest = { position.getX(),position.getY(),width,height };
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = img_height;
	src.w = img_width;
	heart->render(src, dest);
	vida = std::to_string(life);
	f->render(SDLUtils::instance()->renderer(), vida, position.getX() + 20, position.getY() + 4, color);
}