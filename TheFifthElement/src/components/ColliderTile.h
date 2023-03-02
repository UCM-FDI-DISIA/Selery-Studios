#pragma once

#include "../utils/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../components/ColliderTileComponent.h"
#include "../Entities/PlayerTD.h"

class Game;

class ColliderTile : public Entity
{

private:

	Vector2D topLeft_, topRight_, bottomLeft_, bottomRight_;	//vamos a probar

	double margin_ = 5.0; // Margen para comprobar por qué lado se está haciendo la colisión
	Transform* trans;


	//Directions chooseDirection(PlayerTD* player);
public:
	ColliderTile(Game* g, Vector2D p, float w, float h,PlayerTD* player) : Entity() {	
		
		trans = addComponent<Transform>(TRANSFORM_H, p, w, h, 0, 0, 0, false);
		addComponent<ColliderTileComponent>(COLLIDERCOMPONENT_H,player);
		topLeft_ = p;
		topRight_ = { p.getX() + w, p.getY() };
		bottomLeft_ = { p.getX(), p.getY() + h };
		bottomRight_ = { p.getX() + w, p.getY() + h };
	};

	void update();
	void onPlayerCollision();
	void onPlayerCollisionExit();
	
};

