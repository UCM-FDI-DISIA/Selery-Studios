#pragma once
#include "../utils/Component.h"
#include "../GameManager.h"
#include "Transform.h"
#include "../utils/Collision.h"
#include "Image.h"
//#include "DialogueComponent.h"
//#include "ShopComponent.h"

class Button : public Component
{
private:
	string identifier;
	enum mouseState { MOUSE_OUT, MOUSE_OVER };
	Transform* buttonTransform;
	Image* im_;
	Vector2D mousePos;
	int mousePosX, mousePosY, mouseWidth = 1, mouseHeight = 1, currentPositionState;
	SDL_Rect mouseRect;
	float scale;

	bool isClicked_ = false; // utilizado para la tienda
	/*ShopComponent* shopComp_;*/
	/*DialogueComponent* dialog_;*/
	bool beucontrols = false;
	bool tdcontrols = false;
public:
	Button(string identier_) : identifier(identier_) { currentPositionState = MOUSE_OUT; };
	virtual ~Button() {};
	void update();
	void render();
	void handleEvent() {};
	void handleEvent(SDL_Event event);
	void initComponent();
	void updateMousePosition();
	bool getBool();
};

