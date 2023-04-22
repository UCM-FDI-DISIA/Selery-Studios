#pragma once
#ifndef OBJECTSCOMPONENT_H
#define OBJECTSCOMPONENT_H_
#include "../utils/Component.h"
#include "Transform.h"
#include "ColliderComponent.h"

class BeatEmUpState;
class ObjectsComponent : public Component {
private:
	bool inRange = false;
	bool picked = false;
	Transform* trPlayer;
	Transform* trObject;
public:
	ObjectsComponent() {}

	void initComponent();

	void update();

	void render() {}

	inline bool getPicked() { return picked; }

	inline void setPicked(bool newValue) { picked = newValue; }

	inline bool getInRange() { return inRange; }
};
#endif

