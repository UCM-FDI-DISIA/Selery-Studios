#pragma once
#include "Camera.h"
#include "utils/Entity.h"

Camera::Camera(GameManager* g, const Vector2D initialPos, double camW, double camH)
{
	game_ = g;
	pos_ = initialPos;

	height_ = camH;
	width_ = camW;

	windowHeight_ = game_->getWindowHeight();
	windowWidth_ = game_->getWindowWidth();

	scale_ = windowWidth_ / width_;
}

Camera::~Camera()
{
	game_ = nullptr;
}



SDL_Rect Camera::renderRect()
{
	SDL_Rect r = SDL_Rect{ (int)round(pos_.getX()), (int)round(pos_.getY()), (int)width_, (int)height_ };
	return r;
}


