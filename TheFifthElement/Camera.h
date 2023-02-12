#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "Transform.h"
#include "sdlutils/SDLUtils.h"
#include "PlayerTD.h"
class Camera {

private:
	Vector2D pos_;
	double width_, height_; 
	double windowWidth_, windowHeight_;
	double scale_;

	GameManager* game_;
public:
	Camera(GameManager* g, const Vector2D initialPos, double camW, double camH);
	
	~Camera();

	inline Vector2D getCameraPosition() {
		return pos_;
	};
	

	inline double getWidth() { return width_; };
	inline double getHeight() { return height_; };

	inline void setScale(float newScale) {
		scale_ = newScale;
	};
	inline double getScale() {
		return scale_;
	};

	inline void setPos(Vector2D pos)
	{
		pos_ = pos;
	}

	SDL_Rect renderRect();

};
#endif
