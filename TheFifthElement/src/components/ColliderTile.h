#pragma once

#include "../utils/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"



class ColliderTile : public Component
{

private:

	Vector2D topLeft_, topRight_, bottomLeft_, bottomRight_;

	double margin_ = 5.0; // Margen para comprobar por qué lado se está haciendo la colisión

	Transform* trans;
	
	bool isActive_ = true;
	bool isColliding_ = false;


	Transform* trans_player;
	vector<Entity*> colisions;

	//Directions chooseDirection(PlayerTD* player);
public:
	ColliderTile(Vector2D pos, float w, float h) : Component() {
		//tr = addComponent<Transform>(TRANSFORM_H, pos, w, h, 0, 0, 0, false);
		
		trans = new Transform(pos, w, h);
		topLeft_ = pos;
		topRight_ = { pos.getX() + w, pos.getY() };
		bottomLeft_ = { pos.getX(), pos.getY() + h };
		bottomRight_ = { pos.getX() + w, pos.getY() + h };
		
	};
	ColliderTile(vector<Entity*> colisions) :Component() {
		//trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
		this->colisions = colisions;
		
	}
	inline bool isActive() { return isActive_; }
	inline void setColliding(bool p) { isColliding_ = p; }

	void update() {

		/*for (int i = 0; colisions.size(); ++i) {

		}*/
		//if (isActive_) {
		//	SDL_Rect rect = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());
		//	if (p->collide(rect)) {
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
		int dir = chooseDirection();

	}
	void onPlayerCollisionExit() {

	}

	int chooseDirection() {


		Vector2D pTopLeft = trans_player->getPos();
		Vector2D  pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + trans_player->getH() };
		Vector2D pTopRight = { pTopLeft.getX() + trans_player->getW(), pTopLeft.getY() };
		int p = -1;

		if (bottomLeft_.getY() <= pTopLeft.getY() + margin_) {
			p = 0;
			return p;
		}
		else if (topLeft_.getY() >= pBottomLeft.getY() - margin_) {
			p = 2;
			return p;
		}
		else if (topLeft_.getX() >= pTopRight.getX() - margin_) {
			p = 1;
			return p;
		}
		else { // if (topRight_.getX() <= pTopLeft().getX() + margin_)
			p = 3;
			return p;
		}
		cout << p << endl;
	}

};
