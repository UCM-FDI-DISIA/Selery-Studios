#pragma once
#include "../utils/Component.h"
class PortalComponent : public Component
{
private:
	Vector2D portalPosition_{ 100, 400 };
	float portalWidth_ = 290, portalHeight_ = 192, portalRotation_ = 1,portalVel=0;
	Texture* t;

	Transform* trPlayer_;
	CheckCollision* ch;
	int nframes = 1;
	int elementsCollected = 0;
public:
	~PortalComponent() {}

	void update() {}

	void elementEarned(); // Metodo que se usará cuando se derrote un jefe y se recoja su elemento

	void Teleport(Vector2D newPlayerPos);
	void init() {
		//coge el transform del juegador
		mngr_->get
	}
	Portal(PlayerTD* player);

};
	trPlayer_ = player_->getComponent<Transform>(TRANSFORM_H);

void Portal::elementEarned() {
	++elementsCollected;
	cout << "Elemento recogido";
	if (elementsCollected == 3) {
		ch = addComponent<CheckCollision>(CHECKCOLLISION_H, player_, "portal");
	}
}

void Portal::Teleport(Vector2D newPlayerPos) {
	trPlayer_->setPos(newPlayerPos);
}