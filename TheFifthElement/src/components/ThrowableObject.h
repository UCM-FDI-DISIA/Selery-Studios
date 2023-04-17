#pragma once
#ifndef THROWABLEOBJECT_H
#define THROWABLEOBJECT_H_
#include "../utils/Component.h"
#include "Transform.h"
#include "Image.h"
#include "FramedImage.h"
#include "AttackBoxComponent.h"
class ThrowableObject : public Component {
private:
	FramedImage* imagePlayer;
	FramedImage* imageStone;
	Transform* trPlayer;
	Transform* trStone;
	Entity* stone;
	Image* imStone;
	bool thrown = false;
	float timeExecution, throwTime;
public:
	ThrowableObject() {}
	virtual ~ThrowableObject() {}
	void initComponent();

	void update();

	void render();

	void throwStone();
};
#endif

