#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include "utils/Vector2D.h"
#include "utils/Component.h"

class Transform : public Component {
public:
	Transform() {
	}
	// Constructora
	Transform( Vector2D pos, Vector2D vel, float w, float h, float r) : Component() {
		position_ = pos;
		velocity_ = vel;
		width_ = w;
		height_ = h;
		rotation_ = r;
	}
	// Destructora
	virtual ~Transform() { }
	// Devuelve su posicion
	inline Vector2D& getPos() { return position_; }
	// Devuelve su velocidad
	inline Vector2D& getVel() { return velocity_; }
	// Devuelve su ancho
	inline float getW() { return width_; }
	// Devuelve su altura
	inline float getH() { return height_; }
	// Devuelve su rotacion
	inline float getR() { return rotation_; }

	inline void setR(float valRot) { rotation_ = valRot; }

	inline void setH(float valHei) { height_ = valHei; }

	inline void setW(float valWid) { width_ = valWid; }

	inline void setPos(Vector2D Position) { position_ = Position; }

private:
	Vector2D position_, velocity_;
	float width_, height_, rotation_;
};
#endif