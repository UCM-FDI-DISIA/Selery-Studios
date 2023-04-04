#pragma once
#ifndef ECONOMYCOMPONENT_H
#define ECONOMYCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>
using namespace std;
class EconomyComponent : public Component {
private:
	Vector2D position = { 130 * WIN_WIDTH / 900,50 * WIN_HEIGHT / 600 };
	Texture* coin_texture = &SDLUtils::instance()->images().at("coin");
	int width = 20 * WIN_WIDTH / 900, height = 20 * WIN_HEIGHT / 600;
	int img_width = 224, img_height = 16, row = 0, frames = 14;
	int current_money = 200;
	const float max_money = 999;
	int ofset_x = 20 * WIN_WIDTH / 900, ofset_y = 2 * WIN_HEIGHT / 600;
	Font* f;
	string money;
	SDL_Color color = { 50,50,0 };
	bool playAnim = true;
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
