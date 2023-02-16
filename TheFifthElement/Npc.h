#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "CheckCollision.h"
#include "Image.h"
#include "GameManager.h"
class Npc: public Entity {
private:
	//Component* componenete;
	Vector2D NpcPosition_{10,0};
	Vector2D NpcVelocity_{ 0,0 };
	float NpcWith_ =476,NpcHeith_=120, NpcRotation_=1;
	Texture* t;
	Transform* tr;
	GameManager* m;
	int nframes = 7;
	int fila_;
	PlayerTD* player_;
	CheckCollision* ch;
	float a = 1.0f;
	float lookingRange = 150.0f;
	float lookingWidth = 100.0f;
	bool matrix_ = false;
	//cada npc va a tener un dialogo distinto, hay que pasarle en la contructora un array con los diaglogos
	//es decir tipo string y cada parte será un enter que se quiere hacer
public:
	Npc(GameManager* gm_, PlayerTD* player) : Entity() {
		cmpId_type z=int(TRANSFORM_H);
	    tr=addComponent<Transform>(z, NpcPosition_, NpcWith_, NpcHeith_, NpcRotation_, nframes, matrix_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC1-Idle-Left.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H),t,nframes, nframes, fila_);
		//addComponent<RenderComponent>(x,t,tr, nframes, h, w);
		player_ = player;
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, gm_, lookingRange, lookingWidth, a);
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
	}
	~Npc(){

	}
};

