#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerTD.h"


class Portal : public Entity
{
private:
	Vector2D portalPosition_{ 200,150 };
	float portalWidth_ = 290, portalHeight_ = 192, portalRotation_ = 1;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	GameManager* m;
	PlayerTD* player_;
	CheckCollision* ch;
	int nframes = 1;
	int elementsCollected = 0;
public:



	~Portal()
	{

	}

	void update() {}

	void elementEarned(); // Metodo que se usará cuando se derrote un jefe y se recoja su elemento


	Portal(GameManager* gm_, PlayerTD* player) : Entity()
	{
		m = gm_;
		player_ = player;
		tr = addComponent<Transform>(int(TRANSFORM_H), portalPosition_, portalWidth_, portalHeight_, portalRotation_);
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		t = new Texture(gm_->getRenderer(), "./assets/MapAssets/AncientRuins/Props/portal.png");
		addComponent<Image>(int(IMAGE_H), t, nframes);

	}

};

