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
	camRect_.x = playerTr_->getPos().getX();
	camRect_.y = playerTr_->getPos().getY();
	camRect_.h = 300;
	camRect_.w = 500;
}
void CameraComponent::update()
{
	camRect_.x = player_->getComponent<Transform>(c)->getPos().getX();
	camRect_.y = player_->getComponent<Transform>(c)->getPos().getY();

	/*pos_ = camTr_->getPos();

	playerTr_->getPos().set(pos_.getX(), pos_.getY());*/
}

//void CameraComponent::drawCollider()
//{
//
//	SDL_SetRenderDrawColor(gm->getRenderer(), 255, 0, 255, 0);
//	SDL_RenderDrawRect(gm->getRenderer(), &camRect_);
//
//
//	
//}