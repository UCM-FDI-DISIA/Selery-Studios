#include "ShadowComponent.h"

ShadowComponent::ShadowComponent(Entity* player) {
	p = player;
	
}
ShadowComponent::~ShadowComponent() {
	
}
void ShadowComponent::initComponent() {
	trans_player = p->getComponent<Transform>(TRANSFORM_H);
	assert(trans_player != nullptr);
	Jump_player = p->getComponent<JumpComponent>(JUMP_H);
	assert(Jump_player != nullptr);
 }
void ShadowComponent::update() {

 }
void ShadowComponent::render() {
	if (Jump_player->isJumpEnabled()) {
		SDL_Rect rect;
		rect.x = trans_player->getPos().getX() - mngr_->camRect_.x + trans_player->getW() / 2 - (trans_player->getW() / 2 * trans_player->getS()) / 2;
		rect.y = trans_player->getPos().getY() - mngr_->camRect_.y + trans_player->getH() - src_width / 2;
		rect.h = src_width;
		rect.w = trans_player->getW() / 2 * trans_player->getS();
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = src_height;
		src.w = src_width;
		t->render(src, rect, 0, nullptr);
	}
	else {
		SDL_Rect rect;
		rect.x = trans_player->getPos().getX() - mngr_->camRect_.x + trans_player->getW() / 2
			- (trans_player->getW() / 2 * trans_player->getS()) / 2
			-((trans_player->getW() / 2 * trans_player->getS()) * (jump_poss_y - trans_player->getPos().getY()) / 100);
		rect.y = jump_poss_y - mngr_->camRect_.y + trans_player->getH() - src_width / 2;
		rect.h = src_width;
		rect.w = ((trans_player->getW() / 2 * trans_player->getS())*(jump_poss_y-trans_player->getPos().getY())/100);
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = src_height;
		src.w = src_width;
		t->render(src, rect, 0, nullptr);
	}
	
 }
void ShadowComponent::handleEvent(SDL_Event event) {

 }