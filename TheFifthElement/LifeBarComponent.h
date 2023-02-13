#pragma once
#ifndef LIFEBARCOMPONENT_H
#define LIFEBARCOMPONENT_H_
#include "Transform.h"
#include "utils/Vector2D.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"

class LifeBarComponent : public Component
{
private:
	Texture* lifeBar;
	Vector2D pos_;
	GameManager* gm_;
	Entity* entity_;
	Transform* trEntity;
public:

	LifeBarComponent(GameManager* gm, Entity* entity) {
		gm_ = gm;
		entity_ = entity;
		trEntity = entity_->getComponent<Transform>(int(TRANSFORM_H));
	}
	void initComponent() {
		lifeBar = new Texture(gm_->getRenderer(), "./assets/LifeBars/Horizontal/Bars/Bar2.png");
	}

	void update() {
		setPos(trEntity->getPos());
	}
	
	inline void setPos(Vector2D pos) {
		pos_ = pos;
	}
};
#endif

