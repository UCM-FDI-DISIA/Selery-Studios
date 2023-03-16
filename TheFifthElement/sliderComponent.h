#pragma once
#ifndef SLIDERCOMPONENT_H_
#define SLIDERCOMPONENT_H_
#include "src/utils/Component.h"
#include "src/GameManager.h"
#include "src/components/Transform.h"
#include "src/components/Image.h"
#include "src/utils/Collision.h"
class sliderComponent : public Component
{
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
public:
	sliderComponent(float valor_)
	{
		currentPositionState = MOUSE_OUT;
		valor = valor_;

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
#endif

