#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "../components/CheckCollision.h"
#include "PlayerTD.h"
#include "../components/ObjectsComponent.h"


class Portal : public Entity
{
private:
	Vector2D portalPosition_{ 100, 400 };
	float portalWidth_ = 290, portalHeight_ = 192, portalRotation_ = 1;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	PlayerTD* player_;
	CheckCollision* ch;
	int nframes = 1;
	int elementsCollected = 0;
public:
	~Portal() {}

	void update() {}

	void elementEarned(); // Metodo que se usará cuando se derrote un jefe y se recoja su elemento

	void Teleport(Vector2D newPlayerPos);

	Portal(PlayerTD* player) : Entity()
	{
		player_ = player;
		tr = addComponent<Transform>(int(TRANSFORM_H), portalPosition_, portalWidth_, portalHeight_, portalRotation_, nframes, false);
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		t = &SDLUtils::instance()->images().at("portal");
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, 0);
		addComponent<ObjectsComponent>(int(OBJECTSCOMPONENT_H));
	}

};

