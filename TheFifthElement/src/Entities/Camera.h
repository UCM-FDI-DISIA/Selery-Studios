#pragma once
#include "../components/CameraComponent.h"


class Camera : public Entity
{
private:
	Transform* camTr_;
	PlayerTD* player_;

public:
	Camera(PlayerTD* player) : Entity()
	{
		player_ = player;
		Vector2D p = player_->getComponent<Transform>(TRANSFORM_H)->getPos();

		cmpId_type z = int(TRANSFORM_H);
		camTr_ = addComponent<Transform>(z, p = { p.getX() - 300, p.getY() - 200 }, 600, 400, 0,0, 1, false); // transform de la cámara centrado en el player

		cmpId_type k = int(CAMERACOMPONENT_H);
		addComponent<CameraComponent>(k, player_);
	}

	~Camera()
	{

	}
};


