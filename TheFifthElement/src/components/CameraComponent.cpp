#pragma once
#include "CameraComponent.h"

using namespace std;
cmpId_type c = int(TRANSFORM_H);

CameraComponent::CameraComponent(GameManager* gm, PlayerTD* player) :Component()
{
	gm_ = gm;
	player_ = player;
}
void CameraComponent::initComponent() {

	playerTr_ = player_->getComponent<Transform>(c); //transform del player
	camTr_ = ent_->getComponent<Transform>(c); // transform de la cámara

	camRect_.x = (playerTr_->getPos().getX() + 40) - 600 / 2; // player en el centro de la camara
	camRect_.y = (playerTr_->getPos().getY() + 40) - 400 / 2;
	camRect_.h = 400; // Cambiar por windowHeight
	camRect_.w = 600; // Cambiar por windowWidth
}
void CameraComponent::update()
{
	camRect_.x = (playerTr_->getPos().getX()+40) - 600 / 2; // cambiar variables por constantes de la pantalla y personaje
	camRect_.y = (playerTr_->getPos().getY()+40) - 400 / 2;
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

	camTr_->getPos().set(camRect_.x, camRect_.y); // seteo el transform de la cámara según la posición de camRect

}

void CameraComponent::render() {
	SDL_RenderDrawRect(gm_->getRenderer(), &camRect_);
	SDL_SetRenderDrawColor(gm_->getRenderer(), 0, 0, 0, 255);
}