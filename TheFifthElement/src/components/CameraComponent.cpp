#pragma once
#include "CameraComponent.h"

using namespace std;
cmpId_type c = int(TRANSFORM_H);

CameraComponent::CameraComponent(PlayerTD* player) :Component()
{
	player_ = player;
}
void CameraComponent::initComponent() {

	playerTr_ = player_->getComponent<Transform>(c); //transform del player
	camTr_ = ent_->getComponent<Transform>(c); // transform de la c�mara

	camRect_.x = (playerTr_->getPos().getX() + 40) - WIN_WIDTH / 2; // player en el centro de la camara
	camRect_.y = (playerTr_->getPos().getY() + 40) - WIN_HEIGHT / 2;
	camRect_.h = WIN_HEIGHT;
	camRect_.w = WIN_WIDTH; 
}
void CameraComponent::update()
{
	camRect_.x = (playerTr_->getPos().getX()+40) - WIN_WIDTH / 2; 
	camRect_.y = (playerTr_->getPos().getY()+40) - WIN_HEIGHT / 2;
	// Clamp
	if (camRect_.x < 0) { 
		camRect_.x = 0;
	}
	if (camRect_.y < 0) {
		camRect_.y = 0;
	}
	/*if (camRect_.x > (camRect_.w)) {
		camRect_.x = camRect_.w;
	}
	if (camRect_.y > (camRect_.h)) {
		camRect_.y = camRect_.h;
	}*/

	camTr_->getPos().set(camRect_.x, camRect_.y); // seteo el transform de la c�mara seg�n la posici�n de camRect

}

void CameraComponent::render() {
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &camRect_);
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255);
}