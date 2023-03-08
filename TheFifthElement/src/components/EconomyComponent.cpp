#include "EconomyComponent.h"

void EconomyComponent::initComponent() {

 }
void EconomyComponent::update() {

 }
void EconomyComponent::render() {

	SDL_Rect dest = { position.getX(),position.getY(),width,height };
	if (playAnim) {
		SDL_Rect src;
		src.x = row * (img_width / frames);
		src.y = 0;
		src.h = img_height;
		src.w = img_width / frames;
		coin_texture->render(src, dest);
		
		if (row == frames-1) {
			playAnim = false;
		}
		row = (row + 1) % frames;
	}
	else {
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = img_height;
		src.w = img_width / frames;
		coin_texture->render(src, dest);
	}
	money = std::to_string(current_money);
	f->render(SDLUtils::instance()->renderer(), money, position.getY() + ofset_x, position.getY()+ofset_y,color);

 }

#pragma region properties

inline int EconomyComponent::getMoney() const {
	return current_money;
}
inline bool EconomyComponent::can_Substract(int cuantity) {
	if (cuantity < current_money) {
		current_money -= cuantity;
		return true;
	}
	return false;
}
inline void EconomyComponent::addMoney(int cuantity) {
	if (cuantity + current_money < 999) {
		gainMoney->play();
		current_money += cuantity;
		setAnim();
	}
}
inline void EconomyComponent::setAnim() {
	playAnim = true;
	row = 0;
}
