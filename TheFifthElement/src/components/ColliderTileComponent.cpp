#include "ColliderTileComponent.h"
#include "../utils/Entity.h"
#include "../components/ColliderTile.h"





void ColliderTileComponent::initComponent() {
	tr=ent_->getComponent<Transform>(TRANSFORM_H);
			
}
void ColliderTileComponent::update(){

	if (isActive_) {
		SDL_Rect rect = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());		
		if (p->collide(rect)) {
			isColliding_=true;	
			//onPlayerCollision();

		}
		else if (isColliding_) { // La colisión estaba activa pero ha parado

			isColliding_ = false;
			//onPlayerCollisionExit();
		}
	}
}