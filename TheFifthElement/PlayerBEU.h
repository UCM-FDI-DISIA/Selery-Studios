#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "Image.h"
#include "GameManager.h"
#include "InputComponent.h"
#include "InputComponentBEU.h"
#include "MovementComponent.h"
class PlayerBEU : public Entity
{
private:
	//Component* componenete;
	Vector2D PlayerPosition_{ 30,300 };
	float speed_ = 1.0f;
	float PlayerWidth_ = 288, PlayerHeigth_ = 128, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	GameManager* m;
	Vector2D dir;
	MovementComponent* mov = nullptr;
	int nframes = 7;

public:
	PlayerBEU(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/BeatEmUp/Fire/png/fire_knight/02_run/run.png");
		//cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		addComponent<Image>(int(IMAGE_H), t, nframes);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov = addComponent<MovementComponent>(s, speed_);
		cmpId_type w = int(INPUTCOMPONENTBEU_H);
		addComponent<InputComponentBEU>(w);

	}
	~PlayerBEU() {

	}
};

