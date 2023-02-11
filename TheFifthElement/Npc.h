#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
class Npc: public Entity {
private:
	//Component* componenete;
	Vector2D i, a;
	float b, c, d;
	Texture* t;
public:
	Npc() : Entity() {
		cmpId_type z=int(TRANSFORM_H_);
		cmpId_type y = int(RENDERCOMP_);
	    addComponent<Transform>(z, i, a, b, c, d);
		Entity* q= this;
		addComponent<RenderComponent>(y,t,q);
	}
	~Npc(){

	}
};

