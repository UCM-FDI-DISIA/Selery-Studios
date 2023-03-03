#include "SkinComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "Image.h"
#include "../Entities/PlayerTD.h"

void SkinComponent::initComponent() {
	//ent_->addComponent<Image>(int(IMAGE_H), fire, nframes, nframes, fila_);
}

void SkinComponent::update() {
	if (nextState_ != currentState_) changeMov();
	else;
	//cout << skin_ << endl;
}

void SkinComponent::changeMov() {
	
	currentState_ = nextState_;

	switch (currentState_)
	{
	case SkinComponent::Idle:
		setIdle();
		static_cast<PlayerTD*>(ent_)->setAnim(w_, h_, nframes_, t_);
		break;
	case SkinComponent::Left:
		setLeft();
		static_cast<PlayerTD*>(ent_)->setAnim(w_, h_, nframes_, t_);
		break;
	case SkinComponent::Right:
		setRight();
		static_cast<PlayerTD*>(ent_)->setAnim(w_, h_, nframes_, t_);
		break;
	case SkinComponent::Up:
		setUp();
		static_cast<PlayerTD*>(ent_)->setAnim(w_, h_, nframes_, t_);
		break;
	case SkinComponent::Down:
		setDown();
		static_cast<PlayerTD*>(ent_)->setAnim(w_, h_, nframes_, t_);
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

	else if (skin_ == "wind") {
		//t_ = "PTD_wind_idle";
	}

	else if (skin_ == "water") {
		//t_ = "PTD_water_idle";
	}

	else if (skin_ == "earth") {
		//t_ = "PTD_earth_idle";
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

	else if (skin_ == "wind") {
		//t_ = "PTD_wind_left";
	}

	else if (skin_ == "water") {
		//t_ = "PTD_water_left";
	}

	else if (skin_ == "earth") {
		//t_ = "PTD_earth_left";
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

	else if (skin_ == "wind") {
		//t_ = "PTD_wind_right";
	}

	else if (skin_ == "water") {
		//t_ = "PTD_water_right";
	}

	else if (skin_ == "earth") {
		//t_ = "PTD_earth_right";
	}
}

void SkinComponent::setUp() {
	nframes_ = 9;
	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		t_ = "PTD_fire_up";
	}

	else if (skin_ == "wind") {
		//t_ = "PTD_wind_up";
	}

	else if (skin_ == "water") {
		//t_ = "PTD_water_up";
	}

	else if (skin_ == "earth") {
		//t_ = "PTD_earth_up";
	}
}

void SkinComponent::setDown() {
	nframes_ = 9;
	w_ = PLAYERTD_WIDTH_FRAME;
	h_ = PLAYERTD_HEIGHT_FRAME;

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		t_ = "PTD_fire_down";
	}

	else if (skin_ == "wind") {
		//t_ = "PTD_wind_down";
	}

	else if (skin_ == "water") {
		//t_ = "PTD_water_down";
	}

	else if (skin_ == "earth") {
		//t_ = "PTD_earth_down";
	}
}

//void SkinComponent::changeSkin(string skin) {}
