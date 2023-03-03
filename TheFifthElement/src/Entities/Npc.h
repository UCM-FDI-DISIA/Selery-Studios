#pragma once
#include "../components/CheckCollision.h"
#include "../components/ColliderComponent.h"
class Npc: public Entity {
private:
	//Component* componenete;
	//Vector2D NpcPosition_{10,0};
	float NpcWidth_ = NPC_WIDTH, NpcHeight_ = NPC_HEIGHT, NpcRotation_ = 1, npcSpeed = 0;
	Transform* tr;
	int nframes = 7;
	int fila_;
	PlayerTD* player_;
	CheckCollision* ch;
	bool matrix_ = false;
	//cada npc va a tener un dialogo distinto, hay que pasarle en la contructora un array con los diaglogos
	//es decir tipo string y cada parte será un enter que se quiere hacer
public:
	Npc(PlayerTD* player, Vector2D NpcPosition_, Texture* t, int a);
	virtual ~Npc() {}
};

