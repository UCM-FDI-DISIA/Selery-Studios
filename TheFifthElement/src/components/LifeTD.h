#pragma once
#ifndef LIFETDCOMPONENT_H
#define LIFETDCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "SkinComponent.h"
#include <string>
#include <iostream>
#include "../utils/PropertiesManager.h"

using namespace std;

class LifeTD : public Component {
private:
	Vector2D position = { 80,20 };
	Texture* heart = &SDLUtils::instance()->images().at("cora");
	int width = 25, height = 20;
	int img_width = 100, img_height = 67;

	Font* f;
	string vida;
	SDL_Color color = { 50,50,0 };

	SkinComponent* sk_;
	string type_;

	float totalCuantity;
	PropertiesManager* props_;
public:
	LifeTD();
	virtual void initComponent();
	virtual void render();
	virtual ~LifeTD() {};
	int getLife(int i) { return props_->instance()->getLives(i); };// obtenemos valor en el vector lives de PropertiesManager
	inline void addLife(int i, float cuantity) { props_->instance()->setLives(i, cuantity); };// seteamos el valor que queremos dentro del vector
};
#endif