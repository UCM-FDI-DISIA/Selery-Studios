#pragma once

#include "../utils/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../utils/Collision.h"

class InputComponent;

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

public:	
	ColliderTile(vector<Entity*> colisions);
	
	virtual ~ColliderTile();
	void initComponent();
	
	inline bool isActive() { return isActive_; }
	inline void setColliding(bool p) { isColliding_ = p; }
	
	void update();

	int chooseDirection();
	void DesbloqueoZona() {
		colisions.pop_back();
	}
};
