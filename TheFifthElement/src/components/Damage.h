#pragma once
#ifndef DAMAGE_H
#define DAMAGE_H_
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "SkinComponent.h"
#include <string>
#include <iostream>
#include "../utils/PropertiesManager.h"

using namespace std;

class Damage : public Component {
private:
	Vector2D position = { 130,20 };
	Texture* sword = &SDLUtils::instance()->images().at("espada");
	int width = 25, height = 20;
	int img_width = 100, img_height = 67;

	Font* f;
	string fuerza;
	SDL_Color color = { 50,50,0 };

	SkinComponent* sk_;
	string type_;

	float totalCuantity;
	PropertiesManager* props_;
public:
	Damage();
	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual ~Damage() {};
	int getDamage(int i) { return props_->instance()->getStrength(i); }; // obtenemos valor en el vector strength de PropertiesManager
	inline void addDamage(int i,  float cuantity) { props_->instance()->setStrength(i, cuantity); }; // seteamos el valor que queremos dentro del vector
};
#endif
