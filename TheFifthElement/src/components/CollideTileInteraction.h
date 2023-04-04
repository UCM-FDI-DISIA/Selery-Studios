#pragma once

#include "../utils/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include"../PuzzleCopas.h"


class ColliderTileInteraction : public Entity
{

private:

	Vector2D topLeft_, topRight_, bottomLeft_, bottomRight_;

	double margin_ = 5.0; // Margen para comprobar por qué lado se está haciendo la colisión
	PuzzleCopas* puzzle1;
	Entity* p;
	Transform* tr;
	bool isActive_ = true;
	bool isColliding_ = false;
	int id;


	//Directions chooseDirection(PlayerTD* player);
public:
	ColliderTileInteraction(Vector2D pos, float w, float h, Entity* player, int i, PuzzleCopas* puzzle1_) : Entity() {
		tr = addComponent<Transform>(TRANSFORM_H, pos, w, h, 0, 0, 0, false);
		topLeft_ = pos;
		topRight_ = { pos.getX() + w, pos.getY() };
		bottomLeft_ = { pos.getX(), pos.getY() + h };
		bottomRight_ = { pos.getX() + w, pos.getY() + h };
		p = player;
		id = i;
		puzzle1 = puzzle1_;
	};

	inline bool isActive() { return isActive_; }
	inline void setColliding(bool p) { isColliding_ = p; }

	void update() {
		//if (isActive_) {
		//	SDL_Rect rect = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());
		//	if (p->collide(rect)) {
		//		if (isColliding_==false)puzzle1->add(id);
		//		isColliding_ = true;
		//		onPlayerCollision();
		//	}
		//	else if (isColliding_) { // La colisión estaba activa pero ha parado

		//		isColliding_ = false;
		//		//onPlayerCollisionExit();
		//	}
		//}
	}
	void onPlayerCollision() {
		//int dir = chooseDirection();
	
	}
	void onPlayerCollisionExit() {

	}

	int chooseDirection() {
		Transform* tp = p->getComponent<Transform>(TRANSFORM_H);

		Vector2D pTopLeft = tp->getPos();
		Vector2D  pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + tp->getH() };
		Vector2D pTopRight = { pTopLeft.getX() + tp->getW(), pTopLeft.getY() };

		if (bottomLeft_.getY() <= pTopLeft.getY() + margin_) {
			return 0;
		}
		else if (topLeft_.getY() >= pBottomLeft.getY() - margin_) {
			return 2;
		}
		else if (topLeft_.getX() >= pTopRight.getX() - margin_) {
			return 1;
		}
		else { // if (topRight_.getX() <= pTopLeft().getX() + margin_)
			return 3;
		}
	}

};
