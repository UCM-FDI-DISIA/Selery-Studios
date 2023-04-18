#pragma once

#include "../utils/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../utils/Collision.h"
#include "../components/InputComponent.h"



class ColliderTile : public Component
{

private:

	Vector2D topLeft_, topRight_, bottomLeft_, bottomRight_;
	Vector2D pTopLeft, pBottonRight, pTopRight, pBottomLeft;

	double margin_ = 5.0; // Margen para comprobar por qué lado se está haciendo la colisión

	Transform* trans;
	
	bool isActive_ = true;
	bool isColliding_ = false;


	Transform* trans_player;
	Transform* trans_col;
	SDL_Rect* colision;
	SDL_Rect* player;
	SDL_Rect* area;
	vector<Entity*> colisions;
	InputComponent* input;
	int d = -1;

	//Directions chooseDirection(PlayerTD* player);
public:
	//ColliderTile(Vector2D pos, float w, float h) : Component() {
	//	//tr = addComponent<Transform>(TRANSFORM_H, pos, w, h, 0, 0, 0, false);
	//	
	//	trans = new Transform(pos, w, h);
	//	topLeft_ = pos;
	//	topRight_ = { pos.getX() + w, pos.getY() };
	//	bottomLeft_ = { pos.getX(), pos.getY() + h };
	//	bottomRight_ = { pos.getX() + w, pos.getY() + h };
	//	
	//};
	
	ColliderTile(vector<Entity*> colisions);
	
	void initComponent();
	
	inline bool isActive() { return isActive_; }
	inline void setColliding(bool p) { isColliding_ = p; }
	
	void update();
	//void onPlayerCollision() {
	//	int dir = chooseDirection();

	//}
	//void onPlayerCollisionExit() {

	//}

	int chooseDirection();

};
