#include "SkinBEUComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "LifeComponent.h"

void SkinBEUComponent::initComponent() {
	t_ = "Player_BEU_" + skin_;
}

void SkinBEUComponent::update() {
	if (prevSkin_ != skin_) setTexture();
	changeMov();
	if (!set_)
	{
		im_ = ent_->getComponent<Image>(IMAGE_H);
		lifeC_ = ent_->getComponent<LifeComponent>(LIFECOMPONENT_H);
		set_ = true;
	}
}

void SkinBEUComponent::changeSkin(string skin)
{
	skin_ = skin;
	im_->setType(skin_);
	lifeC_->chageType(10);
}

void SkinBEUComponent::setTexture() {
	prevSkin_ = skin_;
	t_ = "Player_BEU_" + skin_;
	if (skin_ == "earth") nframes_ = 6;
	else nframes_ = 8;
	im_->setAnimTexture(t_, nframes_, PLAYERBEU_WIDTH_FRAME, 0);
	changeMov();
}

void SkinBEUComponent::changeMov() {

	if (currentState_ != nextState_) currentState_ = nextState_;
	switch (currentState_)
	{
	case SkinBEUComponent::Idle:
		setIdle();
		if (set_) im_->setAnim(false, fila_, nframes_, 0, nframes_);
		break;
	case SkinBEUComponent::Left:
		setLeft();
		if (set_) im_->setAnim(false, fila_, nframes_, 0, nframes_);
		break;
	case SkinBEUComponent::Right:
		setRight();
		if (set_) im_->setAnim(false, fila_, nframes_, 0, nframes_);
		break;
	case SkinBEUComponent::Vertical:
		setVertical();
		if (set_) im_->setAnim(false, fila_, nframes_, 0, nframes_);
		break;
	case SkinBEUComponent::Jump:
		setJump();
		if (set_) im_->setAnim(true, fila_, nframes_, 0, 100);
		break;
	case SkinBEUComponent::Hit:
		setJump();
		if (set_) im_->setAnim(true, fila_, nframes_, 0, nframes_);
		break;
	case SkinBEUComponent::Death:
		setJump();
		if (set_) im_->setAnim(true, fila_, nframes_, 0, nframes_);
		break;
	default:
		break;
	}

}

void SkinBEUComponent::setIdle() {

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		nframes_ = 8;
		fila_ = 0;
	}

	else if (skin_ == "air") {
		nframes_ = 8;
		fila_ = 0;
	}

	else if (skin_ == "water") {
		nframes_ = 8;
		fila_ = 0;
	}

	else if (skin_ == "earth") {
		nframes_ = 6;
		fila_ = 0;
	}
}

void SkinBEUComponent::setLeft() {
	im_->setFlip(SDL_FLIP_HORIZONTAL);
	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		nframes_ = 8;
		fila_ = 1;
	}

	else if (skin_ == "air") {
		nframes_ = 8;
		fila_ = 1;
	}

	else if (skin_ == "water") {
		nframes_ = 10;
		fila_ = 1;
	}

	else if (skin_ == "earth") {
		nframes_ = 8;
		fila_ = 1;
	}
}

void SkinBEUComponent::setRight() {
	im_->setFlip(SDL_FLIP_NONE);
	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		nframes_ = 8;
		fila_ = 1;
	}

	else if (skin_ == "air") {
		nframes_ = 8;
		fila_ = 1;
	}

	else if (skin_ == "water") {
		nframes_ = 10;
		fila_ = 1;
	}

	else if (skin_ == "earth") {
		nframes_ = 8;
		fila_ = 1;
	}
}

void SkinBEUComponent::setVertical() {

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		nframes_ = 8;
		fila_ = 1;
	}

	else if (skin_ == "air") {
		nframes_ = 8;
		fila_ = 1;
	}

	else if (skin_ == "water") {
		nframes_ = 10;
		fila_ = 1;
	}

	else if (skin_ == "earth") {
		nframes_ = 8;
		fila_ = 1;
	}
}

void SkinBEUComponent::setJump() {

	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/
	nframes_ = 15;

	if (skin_ == "fire") { fila_ = 4; }
	else if (skin_ == "air") { fila_ = 4; }
	else if (skin_ == "water") { fila_ = 6; }
	else if (skin_ == "earth") { fila_ = 10; }
}

void SkinBEUComponent::setHit() {
	nextState_ = Idle;
	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/
	if (skin_ == "fire") {
		nframes_ = 6;
		fila_ = 12;
	}

	else if (skin_ == "air") {
		nframes_ = 6;
		fila_ = 11;
	}

	else if (skin_ == "water") {
		nframes_ = 7;
		fila_ = 13;
	}

	else if (skin_ == "earth") {
		nframes_ = 6;
		fila_ = 12;
	}
}

void SkinBEUComponent::setDeath() {
	nextState_ = Idle;
	//offset_ = Vector2D(55, 55);
	/*ColHeight_ = EnemyHeight_ / 3;
	ColWidth_ = EnemyWidth_ / 25;*/

	if (skin_ == "fire") {
		nframes_ = 13;
		fila_ = 13;
	}

	else if (skin_ == "air") {
		nframes_ = 19;
		fila_ = 12;
	}

	else if (skin_ == "water") {
		nframes_ = 16;
		fila_ = 14;
	}

	else if (skin_ == "earth") {
		nframes_ = 15;
		fila_ = 13;
	}
}