#include "PortalComponent.h"
#include "../states/TopDownState.h"
PortalComponent::PortalComponent() {

}
void PortalComponent::initComponent() {
	//coge el transform del juegador
	trPlayer_ = static_cast<TopDownState*> (mngr_)->getplayer()->getComponent<Transform>(TRANSFORM_H);
}



void PortalComponent::elementEarned() {
	++elementsCollected;
	cout << "Elemento recogido";
	if (elementsCollected == 3) {
		ent_->addComponent<CheckCollision>(CHECKCOLLISION_H, static_cast<TopDownState*> (mngr_)->getplayer(), "portal");
	}
}

void PortalComponent::Teleport(Vector2D newPlayerPos) {
	trPlayer_->setPos(newPlayerPos);
}