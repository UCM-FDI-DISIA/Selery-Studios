#include "Portal.h"
void Portal::elementEarned() {
	++elementsCollected;
	cout << "Elemento recogido";
	if (elementsCollected == 3) {
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, "portal");
	}
}

void Portal::Teleport(Vector2D newPlayerPos) {
	trPlayer_->setPos(newPlayerPos);
}