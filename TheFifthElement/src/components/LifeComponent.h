#pragma once
#include "../Entities/LifeBar.h"

class LifeComponent : public Component
{
private:
	LifeBar* lifeBar_;
	float life_, maxLife_;
public:

	LifeComponent(float maxLife, LifeBar* lifeBar);

	void update();
	void subLife(float damage);
	void resetLife() { life_ = maxLife_; }
	void render();
	//void render() {
	//	SDL_Rect dest;
	//	dest.x = trEntity->getPos().getX();
	//	dest.y = trEntity->getPos().getY();
	//	dest.h = 20;
	//	dest.w = 100;
	//	SDL_Rect src;
	//	src.x = 0;
	//	src.y = 0;
	//	src.h = trEntity->getH();
	//	src.w = trEntity->getW();
	//	//lifeBar->render(trEntity->getPos().getX(), trEntity->getPos().getY() - 50);
	//	lifeBarBack->render(src, dest);
	//	lifeBarBorder->render(src, dest);
	//	SDL_Rect destL;
	//	destL.x = trEntity->getPos().getX();
	//	destL.y = trEntity->getPos().getY();
	//	destL.h = 20;
	//	destL.w = life_;
	//	lifeBar->render(src, destL);
	//}
};

