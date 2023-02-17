#pragma once
#include "CameraComponent.h"
#include "utils/Entity.h"
using namespace std;
cmpId_type c = int(TRANSFORM_H);

CameraComponent::CameraComponent(GameManager* gm, PlayerTD* player) :Component()
{
	gm_ = gm;
	player_ = player;
}
void CameraComponent::initComponent() {

	playerTr_ = player_->getComponent<Transform>(c);
	camTr_ = ent_->getComponent<Transform>(c);

	camRect_.x = playerTr_->getPos().getX() - 600 / 2;
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

	/*pos_ = camTr_->getPos();*/
	camTr_->getPos().set(camRect_.x, camRect_.y);
	//pos_.set(camRect_.x, camRect_.y);
	/*cout << camRect_.x;*/
	//cout << camTr_->getPos().getX();
	//cout << camRect_.h;
}

void CameraComponent::render() {
	SDL_SetRenderDrawColor(gm_->getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(gm_->getRenderer(), &camRect_);
	SDL_SetRenderDrawColor(gm_->getRenderer(), 0, 0, 0, 255);
	
}