#pragma once
#ifndef OBJECTSCOMPONENT_H
#define OBJECTSCOMPONENT_H_
#include "../utils/Component.h"
class ObjectsComponent : public Component {
private:
	bool picked = false;
public:
	ObjectsComponent() {}

	void initComponent() {}

	void update() {}

	void render() {}

	inline bool getPicked() { return picked; }

	inline void setPicked(bool newValue) { picked = newValue; }
};
#endif

