#include "Portal.h"
void Portal::elementEarned() {
	++elementsCollected;
	if (elementsCollected == 3) {
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, m);
	}
}