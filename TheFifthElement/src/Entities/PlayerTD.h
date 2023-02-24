#pragma once
#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "../components/InputComponent.h"
#include "../components/MovementComponent.h"
#include "../components/Image.h"
#include "../components/SkinComponent.h"

class PlayerTD : public Entity {
private:
	//Component* componenete;
	Vector2D PlayerPosition_{ 10,150 };
	float speed_ = 3.0f;
	float PlayerWidth_ = 476, PlayerHeigth_ = 120, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	Vector2D dir;
	MovementComponent* mov = nullptr;
	SkinComponent* sk = nullptr;
	int nframes = 7;
	int fila_;
	int collisionNPC = -1;
	bool matrix_ = false;
public:
	void setCol(int col) {
		collisionNPC = col;
	}
	int getCol() {
		return collisionNPC;
	}
	void initEntity() {
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_, nframes, matrix_);
		/*t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);*/
		cmpId_type k = int(SKINCOMPONENT_H);
		sk = addComponent<SkinComponent>(k);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov = addComponent<MovementComponent>(s);
		cmpId_type w = int(INPUTCOMPONENT_H);
		addComponent<InputComponent>(w);
	}
	PlayerTD() : Entity() {
	
	}
	~PlayerTD() {

	}

	int returnFramesTot() { return 1; }
};





