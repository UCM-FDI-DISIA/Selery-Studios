#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"

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

	bool is_attaking = false;

public:
	PlayerBEU(GameManager* gm_);
	~PlayerBEU();
	int returnFramesTot() { return framesT_; }
	void setAttack(bool a);
	const bool getAttack() const;

};

