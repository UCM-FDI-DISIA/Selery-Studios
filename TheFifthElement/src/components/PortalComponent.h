#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
class PortalComponent : public Component
{
private:
	Transform* trPlayer_;
	int nframes = 1;
	int elementsCollected = 0;
public:
	PortalComponent(Transform* trPlayer);
	void initComponent();
	void update() {};
	virtual ~PortalComponent() {};
	void elementEarned();
	void Teleport(Vector2D newPlayerPos);


};

