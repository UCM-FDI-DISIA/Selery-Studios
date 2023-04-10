#pragma once
#ifndef STONECOMPONENT_H
#define STONECOMPONENT_H_
#include "../utils/Component.h"
#include "Transform.h"
#include "ColliderComponent.h"
#include "Image.h"
class StoneComponent : public Component {
private:
	int stones = 6;
	Image* imStone;
public:
	StoneComponent() {}
	virtual ~StoneComponent() {}
	void initComponent();

	void update() {}

	void render() {}

	void stonePicked();
};
#endif
