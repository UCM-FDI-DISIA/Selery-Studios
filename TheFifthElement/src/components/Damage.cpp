#include "Damage.h"
#include "../states/TopDownState.h"

Damage::Damage() {
	
}

void Damage::initComponent() {
	TopDownState* topdownstate = static_cast<TopDownState*>(mngr_);
	sk_ = topdownstate->getPlayerSkin();
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
	// renderizado de fuerza en HUD segun el player
	if (sk_->getSkinPlayer() == "air") {
		fuerza = std::to_string(props_->instance()->getStrength(0));
	}
	else if (sk_->getSkinPlayer() == "fire") {
		fuerza = std::to_string(props_->instance()->getStrength(1));
	}
	else if (sk_->getSkinPlayer() == "water") {
		fuerza = std::to_string(props_->instance()->getStrength(2));
	}
	else if (sk_->getSkinPlayer() == "earth") {
		fuerza = std::to_string(props_->instance()->getStrength(3));
	}
	
	f->render(SDLUtils::instance()->renderer(), fuerza, position.getX() + 20, position.getY() + 4, color);
}