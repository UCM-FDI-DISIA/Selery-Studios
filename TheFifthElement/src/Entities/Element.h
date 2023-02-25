#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "../components/CheckCollision.h"
#include "PlayerTD.h"
#include "../components/ObjectsComponent.h"
#include "Portal.h"


class Element : public Entity
{
private:
	Vector2D elementPosition_;
	float elementWidth_ = 64 * 4, elementHeight_ = 64, elementRotation_ = 1, elementSpeed = 0;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	Portal* portal_;
	PlayerTD* player_;
	CheckCollision* ch;
	bool picked = false;
	int nframes = 4;
public:
	~Element() {}

	void update() {}
	inline bool GetPicked() {
		return picked;
	}

	inline void SetPicked(bool newValue) {
		picked = newValue;
		portal_->elementEarned();
	}

	Element(PlayerTD* player, Vector2D pos, Portal* portal) : Entity()
	{
		portal_ = portal;
		elementPosition_ = pos;
		player_ = player;
		tr = addComponent<Transform>(int(TRANSFORM_H), elementPosition_, elementWidth_, elementHeight_, elementRotation_,elementSpeed, nframes, true);
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		t = &SDLUtils::instance()->images().at("fireball");
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, 0);
		addComponent<ObjectsComponent>(int(OBJECTSCOMPONENT_H));
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, "element");
	}

};
