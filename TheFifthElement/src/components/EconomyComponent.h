#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Constants.h"
#include <string>
#include <iostream>
using namespace std;
class EconomyComponent : public Component {
protected:
	Vector2D position = { 40,WIN_HEIGHT / 12 };
	Texture* coin_texture = &SDLUtils::instance()->images().at("coin");
	int width = 20, height = 20;
	int img_width = 224, img_height = 16, row = 0, frames = 14;
	int current_money = 200;
	const float max_money = 999;
	int ofset_x = 10, ofset_y = 2;
	Font* f = &SDLUtils::instance()->fonts().at("TCentury");
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
	inline int getMoney() const;
	inline bool can_Substract(int cuantity);
	inline void addMoney(int cuantity);
#pragma endregion
};