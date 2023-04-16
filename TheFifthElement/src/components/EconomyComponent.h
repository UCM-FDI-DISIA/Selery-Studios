#pragma once
#ifndef ECONOMYCOMPONENT_H
#define ECONOMYCOMPONENT_H_
#include "../utils/PropertiesManager.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>

using namespace std;

class EconomyComponent : public Component {
private:
	PropertiesManager* props_;
	Vector2D pos_ = { 130 * WIN_WIDTH / 900,50 * WIN_HEIGHT / 600 };
	Texture* coinTexture_ = &SDLUtils::instance()->images().at("coin");
	int width_ = 20 * WIN_WIDTH / 900, height_ = 20 * WIN_HEIGHT / 600;
	int imgWidth_ = 224, imgHeight_ = 16, row_ = 0, frames_ = 14;
	int currentMoney_;
	int offsetX_ = 20 * WIN_WIDTH / 900, offsetY_ = 2 * WIN_HEIGHT / 600;
	Font* f;
	string money_;
	SDL_Color color_ = { 50,50,0 };
	bool playAnim_ = true;
	inline void setAnim();
public:
	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual ~EconomyComponent() {};
#pragma region properties
	int getMoney() const;
	bool can_Substract(int cuantity);
	inline void addMoney(int cuantity);
#pragma endregion
};
#endif
