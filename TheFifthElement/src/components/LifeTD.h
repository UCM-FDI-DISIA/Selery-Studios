#pragma once
#ifndef LIFETDCOMPONENT_H
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>
using namespace std;
class LifeTD : public Component {
private:
	Vector2D position = { 50,50 };
	Texture* heart = &SDLUtils::instance()->images().at("cora");
	int width = 25, height = 20;
	int img_width = 100, img_height = 67;
	int life = 20;

	Font* f = &SDLUtils::instance()->fonts().at("TCentury");
	string vida;
	SDL_Color color = { 50,50,0 };
public:
	virtual void initComponent() {};
	virtual void update() {};
	virtual void render() {
		SDL_Rect dest = { position.getX(),position.getY(),width,height };
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = img_height;
		src.w = img_width;
		heart->render(src, dest);
	vida = std::to_string(life);
	f->render(SDLUtils::instance()->renderer(), vida, position.getX()+ 20, position.getY()+4, color);
	}
	virtual ~LifeTD() {};
	int getLife() { return life; };
	inline void addLife(int cuantity) { life += cuantity; }
};
#endif