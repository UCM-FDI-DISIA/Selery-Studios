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
	PlayerTD* player_;
	CheckCollision* ch;
	//cada npc va a tener un dialogo distinto, hay que pasarle en la contructora un array con los diaglogos
	//es decir tipo string y cada parte ser� un enter que se quiere hacer
public:
	Npc(GameManager* gm_, PlayerTD* player) : Entity() {
		cmpId_type z=int(TRANSFORM_H);
	    tr=addComponent<Transform>(z, NpcPosition_, NpcVelocity_, NpcWith_, NpcHeith_, NpcRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC1-Idle-Left.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		addComponent<Image>(int(IMAGE_H),t,nframes);
		//addComponent<RenderComponent>(x,t,tr, nframes, h, w);
		player_ = player;
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, gm_);
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
	}
	~Npc(){

	}
};

