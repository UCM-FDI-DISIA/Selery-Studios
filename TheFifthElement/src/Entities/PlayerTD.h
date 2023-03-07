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
#include "../components/EconomyComponent.h"

class PlayerTD : public Entity {
private:
	Vector2D PlayerPosition_;
	float speed_ = 3.0f;
	float PlayerWidth_ = PLAYERTD_WIDTH_FRAME, PlayerHeigth_ = PLAYERTD_HEIGHT_FRAME, PlayerRotation_ = 1;
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
	PlayerTD(string skin, Manager* m, Vector2D pos);
	PlayerTD() : Entity() {
	
	}
	~PlayerTD() {

	}
	bool collide(SDL_Rect other) {

		SDL_Rect rect = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());
		return SDL_HasIntersection(&rect, &other);
	}

	void setAnim(float w, float h, int nframes, string skin)
	{
		PlayerWidth_ = w;
		PlayerHeigth_ = h;
		nframes_ = nframes;
		t_ = &SDLUtils::instance()->images().at(skin);
		if (set_) im_->setAnimTexture(skin, nframes_, w);
	}

};





