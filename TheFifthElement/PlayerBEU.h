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
	float PlayerWidth_ = 8064, PlayerHeigth_ = 128, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	GameManager* m;
	Vector2D dir;
	MovementComponent* mov = nullptr;
	int nframes = 7;
	int framesT_ = 28;
	int fila_;
	bool matrix_ = true;

public:
	PlayerBEU(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H);
		//int width = PlayerWidth_ / framesT_;
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_, framesT_, matrix_);
		t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/BeatEmUp/Fire/spritesheets/fireMatrix.png");
		//cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, framesT_, fila_);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov = addComponent<MovementComponent>(s, speed_);
		cmpId_type w = int(INPUTCOMPONENTBEU_H);
		addComponent<InputComponentBEU>(w);

	}
	~PlayerBEU() {

	}
	int returnFramesTot() { return framesT_; }
};

