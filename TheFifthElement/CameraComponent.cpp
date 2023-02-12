#pragma once
#include "CameraComponent.h"
cmpId_type c = int(_TRANSFORM_H_);
using namespace std;

CameraComponent::CameraComponent(PlayerTD* player) :Component()
{

}

void CameraComponent::initComponent() {
	tr = ent_->getComponent<Transform>(c);
}
void CameraComponent::update() {

	cout << "hola";
}
void CameraComponent::Move(const Vector2D& newPos)
{
	pos_ = newPos;
}

void CameraComponent::MoveDir(const Vector2D& newDir)
{
	pos_ = pos_ + newDir;
}

void CameraComponent::Lerp(const Vector2D& newPos, float i)
{
	auto n = newPos - Vector2D(WIN_HEIGHT / 2, WIN_HEIGHT / 2) + Vector2D(WIN_WIDTH - width_, WIN_HEIGHT - height_) / 2;
	if ((pos_ - n).magnitude() > 2)
		pos_ = pos_ + (newPos - pos_) * i;
}

Vector2D CameraComponent::getCameraCenterPosition()
{
	return pos_ + Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2) - Vector2D(WIN_WIDTH - width_, WIN_HEIGHT - height_) / 2;
}