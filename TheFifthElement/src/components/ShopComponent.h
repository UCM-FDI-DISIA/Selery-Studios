#pragma once
#ifndef SHOPCOMPONENT_H
#define SHOPCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../components/Button.h"

class ShopComponent : public Component {

private:
	Entity* upturnButton_;
	Transform* upturnButtonTr_;
	int upturnButtonWidth_, upturnButtonHeight_;
	Vector2D upturnButtonPos_;
public:
	ShopComponent(Entity* upturnButton);
	void initComponent();
	void update();
	void render();
};
#endif
