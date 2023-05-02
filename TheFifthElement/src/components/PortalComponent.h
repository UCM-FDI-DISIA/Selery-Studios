#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "FramedImage.h"
class PortalComponent : public Component
{
private:
	Transform* trPlayer_;
	Transform* trPortal;
	FramedImage* portalImage;
	FramedImage* fireObeliskImage;
	FramedImage* earthObeliskImage;
	FramedImage* waterObeliskImage;

	bool setEarth = false, setFire = false, setWater = false, setCheckCollision = false;
public:
	PortalComponent(Transform* trPlayer);
	void initComponent();
	void update();
	virtual ~PortalComponent() {};
	void Teleport(Vector2D newPlayerPos);


};

