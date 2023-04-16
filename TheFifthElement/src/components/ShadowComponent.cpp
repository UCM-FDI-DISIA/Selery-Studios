#include "ShadowComponent.h"

ShadowComponent::ShadowComponent() {
	
}
ShadowComponent::~ShadowComponent() {
	
}
void ShadowComponent::initComponent() {
	trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
	assert(trans_player != nullptr);
	Jump_player = ent_->getComponent<JumpComponent>(JUMP_H);
	assert(Jump_player != nullptr);
 }
void ShadowComponent::update() {

 }
void ShadowComponent::render() {
	if (Jump_player->isJumpEnabled()) {
		rect.x = trans_player->getPos().getX() - mngr_->camRect_.x + (trans_player->getW()*trans_player->getS()) / 2 
			- ((trans_player->getW()*trans_player->getS()) / 2) / 2;
		rect.y = trans_player->getPos().getY() - mngr_->camRect_.y + (trans_player->getH()*trans_player->getS())
			- src_width / 2;
		rect.h = src_width;
		rect.w = (trans_player->getW()*trans_player->getS()) / 2;
	}
	else {
		rect.x = (trans_player->getPos().getX() - mngr_->camRect_.x + (trans_player->getW()*trans_player->getS()) / 2
			- ((trans_player->getW()*trans_player->getS())/4) 
			+ ((10 * trans_player->getS()) + ((trans_player->getW()*trans_player->getS()) / 2 ) *
				(1 / abs(jump_poss_y - trans_player->getPos().getY())))+
			(src_width * trans_player->getS())/2);
		rect.y = (jump_poss_y - mngr_->camRect_.y + (trans_player->getH()*trans_player->getS()) -
			src_width / 2);
		rect.h = src_width;
		
		rect.w = ((10 * trans_player->getS()) +((trans_player->getW()*trans_player->getS()) / 2)*
			(1/abs(jump_poss_y-trans_player->getPos().getY())));
		if (rect.w < 20) {
			rect.w = 20;
			rect.x = trans_player->getPos().getX() - mngr_->camRect_.x + (trans_player->getW()*trans_player->getS()) / 2
				- ((trans_player->getW()*trans_player->getS()) / 4)
			+rect.w+src_width/2-5;
		}
	}
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = src_height;
	src.w = src_width;
	t->render(src, rect, 0, nullptr);
	
 }
void ShadowComponent::handleEvent(SDL_Event event) {

 }