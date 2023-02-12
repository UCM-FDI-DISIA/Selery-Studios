#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "RenderComponent.h"
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

public:
	Npc(GameManager* gm_) : Entity() {
		cmpId_type z=int(_TRANSFORM_H_);
	    tr=addComponent<Transform>(z, NpcPosition_, NpcVelocity_, NpcWith_, NpcHeith_, NpcRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC1-Idle-Left.png");
		cmpId_type x = int(RENDERCOMPONENT_H_);
		//referencia al texture y al transform
		addComponent<RenderComponent>(x,t,tr, nframes);
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
	}
	~Npc(){

	}
};

