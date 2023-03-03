#pragma once
#include "../components/CameraComponent.h"


class Camera : public Entity
{
private:
	Transform* camTr_;
	PlayerTD* player_;
	int width = 600;
	int height = 400;

public:
	Camera(PlayerTD* player) : Entity()
	{
		player_ = player;
		Vector2D p = player_->getComponent<Transform>(TRANSFORM_H)->getPos();

		camTr_ = addComponent<Transform>(TRANSFORM_H, p = { p.getX() - 300, p.getY() - 200 }, width, height, 0,0, 1, false); // transform de la cámara centrado en el player

		addComponent<CameraComponent>(CAMERACOMPONENT_H, player_);
	}

	~Camera()
	{

	}
	inline double getWidth() { return width; };
	inline double getHeight() { return height; };
};


