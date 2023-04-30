#pragma once
#include "../sdlutils/Font.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../components/sliderComponent.h"
#include "../components/FramedImage.h"


class EndState : public Manager
{
private:

	//letra
	Font* font_;
	//color de letra
	SDL_Color color_;
	//texto de los creditos
	string creditos;
	//indica el numero de lineas
	int numlineas;
	//creditos con enters
	vector<string> conespacios;
	//botones 
	Entity* replay;
	Entity* exitButton;
	double x, y;
	//Entity* fondo;
	
public:
	//contructora y destructora
	EndState();
	virtual ~EndState();
	//geter de la id
	virtual string getStateID() { return "EndState"; }; // stringID
	//metodos del bucle
	void update();
	void handleEvents();
	void render();
	//creacion de los dos botones (replay-exit)
	void createButtons();
};

