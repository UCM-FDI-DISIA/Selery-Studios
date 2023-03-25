#pragma once
#ifndef DAMAGE_H
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>
using namespace std;
class Damage : public Component {
private:
	Vector2D position = { 100,50 };
	Texture* sword = &SDLUtils::instance()->images().at("espada");
	int width = 25, height = 20;
	int img_width = 100, img_height = 67;
	int damage = 20;
	Font* f = &SDLUtils::instance()->fonts().at("TCentury");
	string fuerza;
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
		sword->render(src, dest);
		fuerza = std::to_string(damage);
		f->render(SDLUtils::instance()->renderer(), fuerza, position.getX()+20, position.getY()+4, color);
	};
	virtual ~Damage() {};
	int getLife() const;
	inline void addLife(int cuantity);
};
#endif
