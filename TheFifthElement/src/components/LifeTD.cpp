#include "LifeTD.h"
#include "../states/TopDownState.h"

LifeTD::LifeTD() {
	
}

void LifeTD::initComponent() {
	TopDownState* topdownstate = static_cast<TopDownState*>(mngr_);
	sk_ = topdownstate->getPlayerSkin();
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
	// renderizado de vida en HUD segun el player
	if (sk_->getSkinPlayer() == "air") {
		vida = std::to_string((int)props_->instance()->getLives(0));
	}
	else if (sk_->getSkinPlayer() == "fire") {
		vida = std::to_string((int)props_->instance()->getLives(1));
	}
	else if (sk_->getSkinPlayer() == "water") {
		vida = std::to_string((int)props_->instance()->getLives(2));
	}
	else if (sk_->getSkinPlayer() == "earth") {
		vida = std::to_string((int)props_->instance()->getLives(3));
	}

	f->render(SDLUtils::instance()->renderer(), vida, position.getX() + 20, position.getY() + 4, color);
}