#pragma once
#ifndef SHOPCOMPONENT_H
#define SHOPCOMPONENT_H_
#include "../utils/Component.h"
class ShopComponent : public Component {

private:


public:
	ShopComponent();
	void initComponent();
	void update();
	void render();
};
#endif
