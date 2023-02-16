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
#include "SkinComponent.h"

class PlayerTD : public Entity {
private:
	//Component* componenete;
	Vector2D PlayerPosition_{ 10,150 };
	float speed_ = 1.0f;
	float PlayerWidth_ = 476, PlayerHeigth_ = 120, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	Vector2D dir;
	MovementComponent* mov = nullptr;
	SkinComponent* sk = nullptr;
	int nframes = 7;
	int fila_;
	int w = 68;
	int h = 120;
	bool matrix_ = false;
public:
	PlayerTD(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_, nframes, matrix_);
		/*t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);*/
		cmpId_type k = int(SKINCOMPONENT_H);
		sk = addComponent<SkinComponent>(k, gm_);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov = addComponent<MovementComponent>(s);
		cmpId_type w = int(INPUTCOMPONENT_H);
		addComponent<InputComponent>(w);
	
	}
	~PlayerTD() {

	}

	int returnFramesTot() { return 1; }
};





