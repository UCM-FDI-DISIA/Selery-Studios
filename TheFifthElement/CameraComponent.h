#pragma once
#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_
#include "sdlutils/SDLUtils.h"
#include "Camera.h"

class CameraComponent : public Component {
	private:
		PlayerTD* player_;
		Transform* tr;		
		Vector2D pos_;
		float width_, height_;
		double scale_;
	
	public:
	
		CameraComponent(PlayerTD* player);
		void initComponent();
		void update();

		void Move(const Vector2D& newPos);
		void MoveDir(const Vector2D& newDir);
		void Lerp(const Vector2D& newPos, float i);

		Vector2D getCameraCenterPosition();
};
#endif
