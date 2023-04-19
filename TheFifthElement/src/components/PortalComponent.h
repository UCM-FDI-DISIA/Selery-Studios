#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
class PortalComponent : public Component
{
private:
	Transform* trPlayer_;
	Transform* trPortal;
	FramedImage* portalImage;
public:
	PortalComponent(Transform* trPlayer);
	void initComponent();
	void update();
	virtual ~PortalComponent() {};
	void elementEarned();
	void Teleport(Vector2D newPlayerPos);


};

