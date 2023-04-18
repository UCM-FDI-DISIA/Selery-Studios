#pragma once
#include "../components/Image.h"
#include "../components/InputComponent.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../utils/Entity.h"
#include "../components/LifeComponent.h"

class HUDTD
{
private:
	string skins_[4] = { "air","fire","water","earth" };
	Vector2D frontIcon_ = { 50,50 };
	Vector2D backIcon_ = { 50,50 };
	Vector2D leftIcon_ = { 50,50 };
	Vector2D rightIcon_ = { 50,50 };
	
public:
	//debería tener una constructora
	HUDTD() {}
	~HUDTD() {}
	void indexSkin(string skin);
	void rotateWheel(int index);
	void render();
	//debería generar al menos la lifebar
	//debe generar 4 iconos para los personajes
	//podría generar un espacio para escribir texto de las misiones
};

