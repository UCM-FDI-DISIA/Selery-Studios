#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "RenderComponent.h"
class GameManager;
class Npc: public Entity {
private:
	//Component* componenete;
	Vector2D i, a;
	float b, c, d;
	Texture* t;
	GameManager* m;

public:
	Npc() : Entity() {
		m = GameManager::instance();
		cmpId_type z=int(TRANSFORM_H_);
	    addComponent<Transform>(z, i, a, b, c, d);
		//t=new Texture(m->getRenderer(),"./assets/NPCs")
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
	}
	~Npc(){

	}
};

