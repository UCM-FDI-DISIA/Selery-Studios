#pragma once
#ifndef LIFETDCOMPONENT_H
#define  LIFETDCOMPONENT_H
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>
using namespace std;
class LifeTD : public Component {
private:
	Vector2D position = { 40,WIN_HEIGHT / 12 };
	Texture* heart = &SDLUtils::instance()->images().at("cora");
	int width = 20, height = 20;
	int img_width = 224, img_height = 16, row = 0, frames = 14;
	float max_money = 20;
	int ofset_x = 10, ofset_y = 2;/*
	Font* f = &SDLUtils::instance()->fonts().at("TCentury");
	string vida;
	SDL_Color color = { 50,50,0 };*/
	inline void setAnim();
public:
	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual ~LifeTD() {};
	int getLife() const;
	inline void addLife(int cuantity);
};
#endif
