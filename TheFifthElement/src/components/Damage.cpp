#include "Damage.h"
#include "../states/TopDownState.h"

Damage::Damage() {
	
}

void Damage::initComponent() {
	TopDownState* topdownstate = static_cast<TopDownState*>(mngr_);
	sk_ = topdownstate->getPlayerSkin();
	if (WIN_WIDTH / 900 == 1920 / 900)f = &SDLUtils::instance()->fonts().at("TCenturyScale");
	else f = &SDLUtils::instance()->fonts().at("TCentury");
}

void Damage::update() {
	
}

void Damage::render() {
	SDL_Rect dest = { position.getX() * WIN_WIDTH / 900,position.getY() * WIN_HEIGHT / 600,width * WIN_WIDTH / 900,
		height * WIN_HEIGHT / 600 };
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
	
	char chars[] = { fuerza[0], fuerza[1], fuerza[2]};
	int longitud = sizeof(chars) / sizeof(chars[0]);
	string str(chars, longitud);

	f->render(SDLUtils::instance()->renderer(), str, (position.getX() + 20) * WIN_WIDTH / 900, (position.getY() + 4) * WIN_HEIGHT / 600, color);
}