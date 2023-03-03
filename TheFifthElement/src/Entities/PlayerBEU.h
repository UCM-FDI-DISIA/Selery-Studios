#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"

#include "../GameManager.h"
#include "../components/InputComponentBEU.h"
#include "../components/MovementComponent.h"
#include "../components/AttackBoxComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/LimitBEU.h"

class PlayerBEU : public Entity {
private:
	//Component* componenete;
	Vector2D PlayerPosition_{ 30,300 };
	float speed_ = 1.0f;
	float PlayerWidth_ = 288, PlayerHeigth_ = 128, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	Vector2D dir;
	InputComponentBEU* in_;
	MovementComponent* mov = nullptr;
	int nframes = 7;
	int framesT_ = 28;
	int fila_;
	bool matrix_ = true;

public:
	PlayerBEU();
	virtual ~PlayerBEU();
	int returnFramesTot() { return framesT_; }
};

