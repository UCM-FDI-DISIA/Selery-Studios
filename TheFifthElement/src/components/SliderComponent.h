#pragma once
#include "../utils/Component.h"
#include "../GameManager.h"
#include "Transform.h"
#include "Image.h"
#include "../utils/Collision.h"
#include "brightSliderComponent.h"

class sliderComponent : public Component {
private:
	string identifier;
	enum mouseState { MOUSE_OUT, MOUSE_OVER };
	Transform* sliderTransform;
	Vector2D mousePos;
	Image* im_;
	int mousePosX, mousePosY, mouseWidth = 1, mouseHeight = 1, currentPositionState,topeDer,topeIzq;
	SDL_Rect mouseRect;
	float valor;
	bool clicked;
	bool set;

	brightSliderComponent* bright;

public:
	sliderComponent(){
		currentPositionState = MOUSE_OUT;
	};
	virtual ~sliderComponent() {};
	void update();
	void render();
	void handleEvent() {};
	void handleEvent(SDL_Event event);
	void initComponent();
	inline float getValue() { return valor; }
	void updateMousePosition();
};