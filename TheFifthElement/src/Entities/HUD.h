#pragma once
#include "../components/Image.h"
#include "../components/InputComponent.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../utils/Entity.h"
#include "../components/LifeComponent.h"

class HUD:public Entity
{
private:
	string skins_[4] = { "air","fire","water","earth" };
public:
	//debería tener una constructora
	HUD();
	void indexSkin(string skin);
	void rotateWheel(int index);
	//debería generar al menos la lifebar
	//debe generar 4 iconos para los personajes
	//podría generar un espacio para escribir texto de las misiones
};

