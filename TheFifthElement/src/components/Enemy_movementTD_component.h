#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "FramedImage.h"
class Enemy_movementTD_component :public Component {
private:
	string type_;
	string state_;
	FramedImage* im_;
public:
	Enemy_movementTD_component(string type);
	void initComponent();
	void changeState(Vector2D dir);
	string getState() { return state_; }
};