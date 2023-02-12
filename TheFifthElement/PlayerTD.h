#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "RenderComponent.h"
#include "GameManager.h"
#include "InputComponent.h"
#include "MovementComponent.h"
class PlayerTD : public Entity {
private:
	//Component* componenete;
	Vector2D PlayerPosition_{ 10,0 };
	Vector2D PlayerVelocity_{ 0,0 };
	float PlayerWidth_ = 100, PlayerHeigth_ = 200, PlayerRotation_ = 1;
	Texture* t;
	Transform* tr;
	GameManager* m;
<<<<<<< Updated upstream
	MovementComponent* mov = nullptr;

public:
	PlayerTD(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H_);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerVelocity_, PlayerWidth_, PlayerHeigth_, PlayerRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire.png");
		cmpId_type x = int(RENDERCOMPONENT_H_);
		//referencia al texture y al transform
		addComponent<RenderComponent>(x, t, tr);
		
		cmpId_type s = int(MOVEMENTCOMPONENT_H_);
		mov =addComponent<MovementComponent>(s);
		cmpId_type w = int(INPUTCOMPONENT_H_);
		addComponent<InputComponent>(w, mov);
=======
	

public:
	PlayerTD(GameManager* gm_) : Entity() {
		cmpId_type z = int(_TRANSFORM_H_);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerVelocity_, PlayerWidth_, PlayerHeigth_, PlayerRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC1-Idle-Left.png");
		cmpId_type x = int(RENDERCOMPONENT_H_);
		//referencia al texture y al transform
		addComponent<RenderComponent>(x, t, tr);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		addComponent<MovementComponent>(MOVEMENTCOMPONENT_H, tr);
		cmpId_type w = int(INPUTCOMPONENT_H);
		addComponent<InputComponent>(w);
>>>>>>> Stashed changes
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
	}
	~PlayerTD() {

	}
};

<<<<<<< Updated upstream
#pragma once
#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "RenderComponent.h"
#include "GameManager.h"
class Npc : public Entity {
private:
	//Component* componenete;
	Vector2D NpcPosition_{ 10,0 };
	Vector2D NpcVelocity_{ 0,0 };
	float NpcWith_ = 100, NpcHeith_ = 200, NpcRotation_ = 1;
	Texture* t;
	Transform* tr;
	GameManager* m;

public:
	Npc(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H_);
		tr = addComponent<Transform>(z, NpcPosition_, NpcVelocity_, NpcWith_, NpcHeith_, NpcRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC1-Idle-Left.png");
		cmpId_type x = int(RENDERCOMPONENT_H_);
		//referencia al texture y al transform
		addComponent<RenderComponent>(x, t, tr);
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
	}
	~Npc() {

	}
};
=======

>>>>>>> Stashed changes

