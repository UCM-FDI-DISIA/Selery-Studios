#include "SkinComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/PlayerTD.h"

void SkinComponent::initComponent() {
}

void SkinComponent::update() {
	if (nextState_ != currentState_ || prevSkin_ != skin_) changeMov();
	if (!set_)
	{
		im_ = ent_->getComponent<Image>(IMAGE_H);
		set_ = true;
	}
}

void SkinComponent::changeMov() {

	currentState_ = nextState_;
	prevSkin_ = skin_;
	switch (currentState_)
	{
	case SkinComponent::Idle:
		setIdle();
		if (set_) im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Left:
		setLeft();
		if (set_) im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Right:
		setRight();
		if (set_) im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Up:
		setUp();
		if (set_) im_->setAnimTexture(t_, nframes_, w_);
		break;
	case SkinComponent::Down:
		setDown();
		if (set_) im_->setAnimTexture(t_, nframes_, w_);
		break;
	default:
		break;
	}

}

void SkinComponent::setIdle() {
	nframes_ = 7;
	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

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
	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

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
	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

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
	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

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

	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

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
