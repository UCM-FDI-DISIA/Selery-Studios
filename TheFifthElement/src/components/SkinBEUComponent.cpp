#include "SkinBEUComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "LifeComponent.h"
SkinBEUComponent::SkinBEUComponent(string skin) {
	skin_ = skin;
	prevSkin_ = skin;
}

void SkinBEUComponent::initComponent() {
	t_ = "Player_BEU_" + skin_;
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	lifeC_ = ent_->getComponent<LifeComponent>(LIFECOMPONENT_H);
}

void SkinBEUComponent::update() {
	if (prevSkin_ != skin_) setTexture();
	changeMov();
}

void SkinBEUComponent::changeSkin(string skin)
{
	skin_ = skin;
	im_->setType(skin_);
	if (skin_ == "air") {
		lifeC_->chageType(props->instance()->getLives(0)); // segun el personaje tenemos una cantidad de vida (respecto a vida comprada en la tienda)
	}
	else if (skin_ == "fire") {
		lifeC_->chageType(props->instance()->getLives(1));
	}
	else if (skin_ == "water") {
		lifeC_->chageType(props->instance()->getLives(2));
	}
	else if (skin_ == "earth") {
		lifeC_->chageType(props->instance()->getLives(3));
	}
	
}

void SkinBEUComponent::setTexture() {
	prevSkin_ = skin_;
	t_ = "Player_BEU_" + skin_;
	if (skin_ == "earth") nframes_ = 6;
	else nframes_ = 8;
	im_->setAnim(t_, nframes_, false);
	////im_->setAnimTexture(t_, nframes_, PLAYERBEU_WIDTH_FRAME, 0);
	changeMov();
}

void SkinBEUComponent::changeMov() {

	if (currentState_ != nextState_) currentState_ = nextState_;
	switch (currentState_)
	{
	case SkinBEUComponent::Idle:
		setIdle();
		////im_->setAnim(false, fila_, nframes_, 0, nframes_);
		im_->setAnim(t_, nframes_, false);
		break;
	case SkinBEUComponent::Left:
		setLeft();
		////im_->setAnim(false, fila_, nframes_, 0, nframes_);
		im_->setAnim(t_, nframes_, false);
		break;
	case SkinBEUComponent::Right:
		setRight();
		////im_->setAnim(false, fila_, nframes_, 0, nframes_);
		im_->setAnim(t_, nframes_, false);
		break;
	case SkinBEUComponent::Vertical:
		setVertical();
		////im_->setAnim(false, fila_, nframes_, 0, nframes_);
		im_->setAnim(t_, nframes_, false);
		break;
	case SkinBEUComponent::Jump:
		setJump();
		////im_->setAnim(true, fila_, nframes_, 0, 100);
		im_->setAnim(t_, nframes_, false);
		break;
	case SkinBEUComponent::Hit:
		setHit();
		////im_->setAnim(true, fila_, nframes_, 0, nframes_);
		im_->setAnim(t_, nframes_, true);
		break;
	case SkinBEUComponent::Death:
		setDeath();
		////im_->setAnim(true, fila_, nframes_, 0, nframes_);
		im_->setAnim(t_, nframes_, true);
		break;
	default:
		break;
	}
	
}

void SkinBEUComponent::setIdle() {
	t_ = "Player_BEU_" + skin_ + "_idle";
	if (skin_ == "fire" || skin_ == "air" || skin_ == "water") {
		nframes_ = 8;
	}
	else if (skin_ == "earth") {
		nframes_ = 6;
	}
}

void SkinBEUComponent::setLeft() {
	im_->setFlip(SDL_FLIP_HORIZONTAL);
	t_ = "Player_BEU_" + skin_ + "_run";

	if (skin_ == "fire" || skin_ == "air" || skin_ == "earth") {
		nframes_ = 8;
	}
	else if (skin_ == "water") {
		nframes_ = 10;
	}
}

void SkinBEUComponent::setRight() {
	im_->setFlip(SDL_FLIP_NONE);
	t_ = "Player_BEU_" + skin_ + "_run";

	if (skin_ == "fire" || skin_ == "air" || skin_ == "earth") {
		nframes_ = 8;
	}
	else if (skin_ == "water") {
		nframes_ = 10;
	}
}

void SkinBEUComponent::setVertical() {
	t_ = "Player_BEU_" + skin_ + "_run";

	if (skin_ == "fire" || skin_ == "air" || skin_ == "earth") {
		nframes_ = 8;
	}
	else if (skin_ == "water") {
		nframes_ = 10;
	}
}

void SkinBEUComponent::setJump() {
	t_ = "Player_BEU_" + skin_ + "_jump";

	if (skin_ == "fire") { nframes_ = 20; }
	else if (skin_ == "air") { nframes_ = 31; }
	else if (skin_ == "water") { nframes_ = 26; }
	else if (skin_ == "earth") { nframes_ = 23; }
}

void SkinBEUComponent::setHit() {
	nextState_ = Idle;

	t_ = "Player_BEU_" + skin_ + "_hit";

	if (skin_ == "fire" || skin_ == "air" || skin_ == "earth") {
		nframes_ = 6;
	}
	else if (skin_ == "water") {
		nframes_ = 7;
	}
}

void SkinBEUComponent::setDeath() {
	nextState_ = Idle;

	t_ = "Player_BEU_" + skin_ + "_death";

	if (skin_ == "fire") { nframes_ = 13; }
	else if (skin_ == "air") { nframes_ = 19; }
	else if (skin_ == "water") { nframes_ = 16; }
	else if (skin_ == "earth") { nframes_ = 15; }
}