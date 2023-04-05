#include "SkinComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"

SkinComponent::SkinComponent(string skin) {
	skin_ = skin;
	prevSkin_ = skin;
}

void SkinComponent::initComponent() {
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
}

void SkinComponent::update() {
	if (nextState_ != currentState_ || prevSkin_ != skin_) changeMov();
}

void SkinComponent::changeMov() {

	if (set_) {
		if (currentState_ == Left && nextState_ == Idle) im_->setFlip(SDL_FLIP_HORIZONTAL);
		else im_->setFlip(SDL_FLIP_NONE);
	}

	currentState_ = nextState_;
	prevSkin_ = skin_;
	switch (currentState_)
	{
	case SkinComponent::Idle:
		setIdle();
		////im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Left:
		setLeft();
		/////im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Right:
		setRight();
		/////im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Up:
		setUp();
		////im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Down:
		setDown();
		/////im_->setAnimTexture(t_, nframes_, w_);
		break;
	default:
		break;
	}
	im_->setAnim(t_, nframes_, false);
}

void SkinComponent::setIdle() {
	nframes_ = 7;

	if (skin_ == "fire") {
		t_ = "PTD_fire_idle";
	}

	else if (skin_ == "air") {
		t_ = "PTD_air_idle";
	}

	else if (skin_ == "water") {
		t_ = "PTD_water_idle";
	}

	else if (skin_ == "earth") {
		t_ = "PTD_earth_idle";
	}
}

void SkinComponent::setLeft() {
	nframes_ = 7;

	if (skin_ == "fire") {
		t_ = "PTD_fire_left";
	}

	else if (skin_ == "air") {
		t_ = "PTD_air_left";
	}

	else if (skin_ == "water") {
		t_ = "PTD_water_left";
	}

	else if (skin_ == "earth") {
		t_ = "PTD_earth_left";
	}
}

void SkinComponent::setRight() {
	nframes_ = 7;
	if (skin_ == "fire") {
		t_ = "PTD_fire_right";
	}

	else if (skin_ == "air") {
		t_ = "PTD_air_right";
	}

	else if (skin_ == "water") {
		t_ = "PTD_water_right";
	}

	else if (skin_ == "earth") {
		t_ = "PTD_earth_right";
	}
}

void SkinComponent::setUp() {
	if (skin_ == "fire") {
		nframes_ = 9;
		t_ = "PTD_fire_up";
	}

	else if (skin_ == "air") {
		nframes_ = 7;
		t_ = "PTD_air_up";
	}

	else if (skin_ == "water") {
		nframes_ = 9;
		t_ = "PTD_water_up";
	}

	else if (skin_ == "earth") {
		nframes_ = 9;
		t_ = "PTD_earth_up";
	}
}

void SkinComponent::setDown() {
	if (skin_ == "fire") {
		nframes_ = 9;
		t_ = "PTD_fire_down";
	}

	else if (skin_ == "air") {
		nframes_ = 7;
		t_ = "PTD_air_down";
	}

	else if (skin_ == "water") {
		nframes_ = 9;
		t_ = "PTD_water_down";
	}

	else if (skin_ == "earth") {
		nframes_ = 9;
		t_ = "PTD_earth_down";
	}
}
