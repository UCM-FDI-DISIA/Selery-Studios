#include "EconomyComponent.h"
void EconomyComponent::initComponent() {
	if(WIN_WIDTH/900 == 1920/900)f = &SDLUtils::instance()->fonts().at("TCenturyScale");
	else f = &SDLUtils::instance()->fonts().at("TCentury");
}

void EconomyComponent::update() {
}

void EconomyComponent::render() {
	SDL_Rect dest = { pos_.getX(), pos_.getY(), width_, height_ };
	if (playAnim_) {
		SDL_Rect src;
		src.x = row_ * (imgWidth_ / frames_);
		src.y = 0;
		src.h = imgHeight_;
		src.w = imgWidth_ / frames_;
		coinTexture_->render(src, dest);

		if (row_ == frames_ - 1) {
			playAnim_ = false;
		}
		row_ = (row_ + 1) % frames_;
	}
	else {
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = imgHeight_;
		src.w = imgWidth_ / frames_;
		coinTexture_->render(src, dest);
	}
	money_ = std::to_string((int)props_->instance()->getMoney());
	f->render(SDLUtils::instance()->renderer(), money_, pos_.getX() + offsetX_, pos_.getY() + offsetY_, color_);
}

int EconomyComponent::getMoney() const {
	return props_->instance()->getMoney();
}
bool EconomyComponent::can_Substract(int cuantity) {
	return props_->instance()->can_Substract(cuantity);
}
inline void EconomyComponent::addMoney(int cuantity) {
	if (cuantity + currentMoney_ < MAX_MONEY) {
		currentMoney_ += cuantity;
		setAnim();
	}
}
inline void EconomyComponent::setAnim() {
	playAnim_ = true;
	row_ = 0;
}