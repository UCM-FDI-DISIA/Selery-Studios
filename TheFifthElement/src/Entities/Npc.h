#pragma once
#include "../components/CheckCollision.h"
#include "../components/ColliderComponent.h"
class Npc: public Entity {
private:
	//Component* componenete;
	//Vector2D NpcPosition_{10,0};
	float NpcWidth_ =476,NpcHeight_=120, NpcRotation_=1, npcSpeed=0;



	Transform* tr;
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
	Npc(PlayerTD* player, Vector2D NpcPosition_,Texture* t) : Entity() {
		cmpId_type z=int(TRANSFORM_H);
	    tr=addComponent<Transform>(z, NpcPosition_, NpcWidth_, NpcHeight_, NpcRotation_,npcSpeed, nframes, matrix_);
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H),t,nframes, nframes, fila_);
		//addComponent<RenderComponent>(x,t,tr, nframes, h, w);
		player_ = player;
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, lookingRange, lookingWidth, a);
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));
		addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(0, 0), NpcHeight_, NpcWidth_ / nframes);
	}
	~Npc(){

	}
};

