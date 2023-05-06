#include "ObjectsComponent.h"
#include "../states/BeatEmUpState.h"
void ObjectsComponent::initComponent() {
	trPlayer = static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<Transform>(TRANSFORM_H);
	trObject = ent_->getComponent<Transform>(TRANSFORM_H);
	e = &SDLUtils::instance()->images().at("E");
}
void ObjectsComponent::update() {
	Vector2D trPos = Vector2D(trPlayer->getPos().getX(), trPlayer->getPos().getY());
	if (Collision::collides(trObject->getPos(), trObject->getW(), trObject->getH(), trPos, trPlayer->getW(), trPlayer->getH())) {
		inRange = true;
		if (static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H)->getEarthStage3()) {
			draw = true;
		}
	}
	else {
		inRange = false;
		draw = false;
	}
}

void ObjectsComponent::render() {
	if (draw) {
		SDL_Rect dest1 = { trObject->getPos().getX() + trObject->getW() / 2 - mngr_->camRect_.x, trObject->getPos().getY(), 50 * WIN_WIDTH / 900, 50 * WIN_HEIGHT / 600 };
		SDL_Rect src = { 0, 0, 32, 32 };
		e->render(src, dest1);
	}
}