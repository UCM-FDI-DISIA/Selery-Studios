#pragma once
#include "../utils/Entity.h"
#include "../components/Image.h"
#include "../components/InputComponent.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"

class HUD : public Entity
{
private:

public:
	HUD(Manager* m)
	{

	}
	void changeRoulette(string dir);
};

