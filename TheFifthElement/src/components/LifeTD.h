#pragma once
#ifndef LIFETDCOMPONENT_H
#define LIFETDCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>
using namespace std;

class LifeTD : public Component {
private:
	Vector2D position = { 80,20 };
	Texture* heart = &SDLUtils::instance()->images().at("cora");
	int width = 25, height = 20;
	int img_width = 100, img_height = 67;
	vector<int> lives;
	int life = 20;

	Font* f = &SDLUtils::instance()->fonts().at("TCentury");
	string vida;
	SDL_Color color = { 50,50,0 };
public:
	LifeTD();
	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual ~LifeTD() {};
	int getLife() { return life; };
	inline void addLife(int i, int cuantity) { lives[0] += cuantity; }
};
#endif