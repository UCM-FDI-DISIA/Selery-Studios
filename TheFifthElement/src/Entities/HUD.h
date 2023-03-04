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
	Vector2D frontIcon_ = { 50,50 };
	Vector2D backIcon_ = { 50,50 };
	Vector2D leftIcon_ = { 50,50 };
	Vector2D rightIcon_ = { 50,50 };
	Vector2D iconPos_[4] = {frontIcon_,rightIcon_,backIcon_,leftIcon_}; //va a seer innecesario
public:
	//debería tener una constructora
	HUD();
	void indexSkin(string skin);
	void rotateWheel(int index);
	//debería generar al menos la lifebar
	//debe generar 4 iconos para los personajes
	//podría generar un espacio para escribir texto de las misiones
};

