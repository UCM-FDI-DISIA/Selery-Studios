#pragma once
#include "CameraComponent.h"
//#include "utils/Entity.h"
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

	camRect_.x = playerTr_->getPos().getX() - 600 / 2; // player en el centro de la camara
	camRect_.y = playerTr_->getPos().getY() - 400 / 2;
	camRect_.h = 400; //400
	camRect_.w = 600; //600
}
void CameraComponent::update()
{
	/*camRect_ = getRect();*/
	camRect_.x = playerTr_->getPos().getX() - 600 / 2;
	camRect_.y = playerTr_->getPos().getY() - 400 / 2;
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
	/*cout << camRect_.x;
	cout << camTr_->getPos().getX();*/
	//cout << camRect_.h;
}