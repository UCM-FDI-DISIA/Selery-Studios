#pragma once
#ifndef STONECOMPONENT_H
#define STONECOMPONENT_H_
#include "../utils/Component.h"
#include "Transform.h"
#include "ColliderComponent.h"
#include "Image.h"
class StoneComponent : public Component {
private:
	int stones = 6, bossStage;
	Image* imStone;
public:
	StoneComponent(int bossStage_);
	virtual ~StoneComponent() {}
	void initComponent();
	void stonePicked();
};
#endif
