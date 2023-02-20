#pragma once
#ifndef LIFECOMPONENT_H
#define LIFECOMPONENT_H_
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"

class LifeComponent : public Component
{
private:
	Texture* lifeBar;
	Texture* lifeBarBack;
	Texture* lifeBarBorder;
	Vector2D pos_;
	GameManager* gm_;
	Entity* entity_;
	Transform* trEntity;
	int nframes = 1, i = 0;
	float life_, maxLife_;
public:

	LifeComponent(GameManager* gm,  Transform* tr, float maxLife) {
		life_ = maxLife;
		maxLife_ = maxLife;
		gm_ = gm;
		trEntity = tr;
	}
	void initComponent() {
		lifeBar = new Texture(gm_->getRenderer(), "./assets/LifeBars/Horizontal/Bars/Bar2.png");
		lifeBarBack = new Texture(gm_->getRenderer(), "./assets/LifeBars/Horizontal/Backs/Back6.png");
		lifeBarBorder = new Texture(gm_->getRenderer(), "./assets/LifeBars/Horizontal/Boarders/Boarder2.png");
	}

	void update() {
		if (life_ > 0) {
			--life_;
		}
		else {
			life_ = maxLife_;
		}
	}

	void render() {
		SDL_Rect dest;
		dest.x = trEntity->getPos().getX();
		dest.y = trEntity->getPos().getY();
		dest.h = 20;
		dest.w = 100;
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = trEntity->getH();
		src.w = trEntity->getW();
		//lifeBar->render(trEntity->getPos().getX(), trEntity->getPos().getY() - 50);
		lifeBarBack->render(src, dest);
		lifeBarBorder->render(src, dest);
		SDL_Rect destL;
		destL.x = trEntity->getPos().getX();
		destL.y = trEntity->getPos().getY();
		destL.h = 20;
		destL.w = life_;
		lifeBar->render(src, destL);
	}
};
#endif

