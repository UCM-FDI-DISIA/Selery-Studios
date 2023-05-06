#pragma once
#ifndef THROWABLEOBJECT_H
#define THROWABLEOBJECT_H_
#include "../utils/Component.h"
#include "Transform.h"
#include "Image.h"
#include "FramedImage.h"
#include "AttackBoxComponent.h"
class ThrowableObject : public Component { // Componente que se utiliza para lanzar la piedra
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

	void throwStone();

	inline bool getThrown() { return thrown; }
};
#endif

