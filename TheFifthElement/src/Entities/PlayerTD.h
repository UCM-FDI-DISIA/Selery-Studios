#pragma once
#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "../components/InputComponent.h"
#include "../components/MovementComponent.h"
#include "../components/Image.h"
#include "../components/SkinComponent.h"


class PlayerTD : public Entity {
private:
	Vector2D PlayerPosition_{ 10,150 };
	float speed_ = 3.0f;
	float PlayerWidth_ = 476, PlayerHeigth_ = 120, PlayerRotation_ = 1;
	Texture* t_;
	Transform* tr;
	Vector2D dir;
	InputComponent* in_;
	MovementComponent* mov = nullptr;
	SkinComponent* sk = nullptr;
	Image* im_ = nullptr;
	int nframes_ = 7;
	int fila_;
	int collisionNPC;
	bool hascollision = false;
	bool matrix_ = false;
	bool set_ = false;
public:
	void setCollision(bool collision) {
		hascollision = collision;
	}
	bool hascol() {
		return hascollision;
	}
	void setCol(int col) {
		collisionNPC = col;
	}
	int getCol() {
		return collisionNPC;
	}
	PlayerTD(string skin, Manager* m) {
		//mngr_ = m;
		cmpId_type k = int(SKINCOMPONENT_H);
		sk = addComponent<SkinComponent>(k, skin);
		sk->changeState(SkinComponent::Idle);
		sk->changeMov();

		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_,speed_, nframes_, matrix_);

		
		fila_ = 0;
		im_ = addComponent<Image>(int(IMAGE_H), t_, nframes_, nframes_, fila_);

		mov = addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);

		in_ = addComponent<InputComponent>(INPUTCOMPONENT_H);
		in_->initComponent();
		in_->setContext(this, m);
		
		set_ = true;
	}
	PlayerTD() : Entity() {
	
	}
	~PlayerTD() {

	}

	void setAnim(float w, float h, int nframes, string skin)
	{
		PlayerWidth_ = w;
		PlayerHeigth_ = h;
		nframes_ = nframes;
		t_ = &SDLUtils::instance()->images().at(skin);
		if (set_) im_->setAnimTexture(skin, nframes_, w);
	}

	bool collide(SDL_Rect other) {
		
		SDL_Rect rect= build_sdlrect(tr->getPos(), tr->getW(), tr->getH());	
		return SDL_HasIntersection(&rect, &other);
	}

	int returnFramesTot() { return 1; }

};





