#include "ThrowableObject.h"
void ThrowableObject::initComponent() {
	imagePlayer = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	trPlayer = ent_->getComponent<Transform>(TRANSFORM_H);
	stone = new Entity();
	stone->setContext(mngr_);
	trStone = stone->addComponent<Transform>(TRANSFORM_H, trPlayer->getPos(), trPlayer->getW(), trPlayer->getH(), 1, 5);
	imageStone = stone->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("v1stone1"), 224, 192, 1, "earth");
	imageStone->setTexKey("v1stone1");
	stone->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	mngr_->addEntity(stone);
}

void ThrowableObject::update() {
	unsigned timer = clock();
	timeExecution = (double(timer) / CLOCKS_PER_SEC);

	Vector2D posPlayer = trPlayer->getPos();

	if (!thrown) {
		trStone->setPos(posPlayer - Vector2D(0, 20));
	}
	else
	{
		if (throwTime + 2 < timeExecution) {
			stone->setAlive(false);
			ent_->removeComponent(THROWABLEOBJECT_H);
		}
		else {
			trStone->setPos(trStone->getPos() + trStone->getDir() * trStone->getVel());
		}
	}
}

void ThrowableObject::render() {

}

void ThrowableObject::throwStone() {
	unsigned timer = clock();
	throwTime = (double(timer) / CLOCKS_PER_SEC);
	thrown = true;
	if (imagePlayer->getFlip() == SDL_FLIP_HORIZONTAL) {
		trStone->setDir(Vector2D(-1, 0));
	}
	else {
		trStone->setDir(Vector2D(1, 0));
	}
}