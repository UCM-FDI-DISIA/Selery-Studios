#pragma once

#include "../utils/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../utils/Collision.h"

class Trigger : public Component
{
private:

	Transform* trans_player;
	Transform* trans_col;
	SDL_Rect* colision;
	SDL_Rect* player;
	vector<Entity*> colisions;

public:
	Trigger();
	virtual ~Trigger();
	void initComponent();
	void update();
};
