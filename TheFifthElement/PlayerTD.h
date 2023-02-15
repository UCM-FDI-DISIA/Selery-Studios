#pragma once
#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "Image.h"
class PlayerTD : public Entity {
private:
	//Component* componenete;
	Vector2D PlayerPosition_{ 10,150 };
	Vector2D PlayerVelocity_{ 1,0 };
	float PlayerWidth_ = 476, PlayerHeigth_ = 120, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	GameManager* m;
	Vector2D dir;
	MovementComponent* mov = nullptr;
	int nframes = 7;
	int w = 68;
	int h = 120;
public:
	PlayerTD(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerVelocity_, PlayerWidth_, PlayerHeigth_, PlayerRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		//addComponent<RenderComponent>(x, t, tr, nframes, h, w);
		addComponent<Image>(int(IMAGE_H), t, nframes);

		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov = addComponent<MovementComponent>(s);
		cmpId_type w = int(INPUTCOMPONENT_H);
		addComponent<InputComponent>(w);
	
	}
	~PlayerTD() {

	}
};





